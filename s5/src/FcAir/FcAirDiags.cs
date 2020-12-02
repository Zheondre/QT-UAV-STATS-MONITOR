using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace UpgenConsole.FcAir
{
    public class FcAirDiags : BaseStats
    {
	    public int [] m_IntGroup;
        public int [] m_ShortGroup;
        public int m_TickCount;

        public enum IntStats {
            CalendarTime,
            SystemUptime,

            NumIntStats,
        };

        static public String [] m_Units =
        {
            "secs",  //CalendarTime
            "secs",  //UpTime

		    "A",  //_5VoutIsns,
		    "V",  //BopVsns,
		    "A",  //BopIsns,
		    "C",  //Stk1CoolantInputTemp,
		    "C",  //Stk2CoolantInputTemp,

		    "V",  //HeatHum1Vsns,
		    "A",  //HeatHum1Isns,
		    "V",  //HeatFC1Vsns,
		    "A",  //HeatFC1Isns,
		    "A",  //PrgA1Isns,
		    "A",  //PrgB1Isns,
		    "A",  //PrgC1Isns,
		    "V",  //CP1Vsns,
		    "A",  //CP1Isns,
		
		    "V",  //HeatHum2Vsns,
		    "A",  //HeatHum2Isns,
		    "V",  //HeatFC2Vsns,
		    "A",  //HeatFC2Isns,
		    "A",  //PrgA2Isns,
		    "A",  //PrgB2Isns,
		    "A",  //PrgC2Isns,
		    "V",  //CP2Vsns,
		    "A",  //CP2Isns,

		    "V",  //CP3Vsns,
		    "A",  //CP3Isns,
		    "A",  //Start5V0Isns,
		    "PSI",  //TankPsi,
		    "V",  //_12V0Vsns,
		    "A",  //_12V0Isns,
		
		    "C",  //Hum2Tsns,
		    "C",  //Hum1Tsns,
		
		    "V",  //HeatBattVsns,	// 1, 1000
		    "A",  //HeatBattIsns,	// 1, 1000
		    "C",  //BattTsns,	// 1, 1000
		    "PSI",//SparePsi,	// 1, 1000		

		    "",  //ControlsMask,
        };

        static public int[] m_Scale =
        {
            1,  //CalendarTime
            1,  //UpTime

		    1000, //_5VoutIsns,
		    100, //BopVsns,	// 10, 100
		    1000, //BopIsns,	// 1, 1000
		    10, //Stk1CoolantInputTemp, // 1, 10
		    10, //Stk2CoolantInputTemp,	// 1, 10

		    1000, //HeatHum1Vsns,	// 1, 1000
		    1000, //HeatHum1Isns,	// 1, 1000
			1000, //HeatFC1Vsns,	// 1, 1000
			1000, //HeatFC1Isns,	// 1, 1000
			1000, //PrgA1Isns,	// 1, 1000
			1000, //PrgB1Isns,	// 1, 1000
			1000, //PrgC1Isns,	// 1, 1000
			1000, //CP1Vsns,	// 1, 1000
			1000, //CP1Isns,	// 1, 1000
		
			1000, //HeatHum2Vsns,	// 1, 1000
			1000, //HeatHum2Isns,	// 1, 1000
			1000, //HeatFC2Vsns,	// 1, 1000
			1000, //HeatFC2Isns,	// 1, 1000
			1000, //PrgA2Isns,	// 1, 1000
			1000, //PrgB2Isns,	// 1, 1000
			1000, //PrgC2Isns,	// 1, 1000
			1000, //CP2Vsns,	// 1, 1000
			1000, //CP2Isns,	// 1, 1000

			1000, //CP3Vsns,	// 1, 1000
			1000, //CP3Isns,	// 1, 1000
			1000, //Start5V0Isns, // 1, 1000
			1, //TankPsi,	// 1000, 1
			1000, //_12V0Vsns,  // 1, 1000
			1000, //_12V0Isns,  // 1, 1000
		
			10, //Hum2Tsns,	// 1, 10
			10, //Hum1Tsns,	// 1, 10

		    1000,  //HeatBattVsns,	// 1, 1000
		    1000,  //HeatBattIsns,	// 1, 1000
		    10,  //BattTsns,	// 1, 1000
		    10,//SparePsi,	// 1, 1000		

            1,  //ControlsMask,
        };

        public enum ShortStats
        {
            CalendarTime,
            UpTime,

            _5VoutIsns,
            BopVsns,
            BopIsns,
            Stk1CoolantInputTemp,
            Stk2CoolantInputTemp,

            HeatHum1Vsns,
            HeatHum1Isns,
            HeatFC1Vsns,
            HeatFC1Isns,
            PrgA1Isns,
            PrgB1Isns,
            PrgC1Isns,
            CP1Vsns,
            CP1Isns,

            HeatHum2Vsns,
            HeatHum2Isns,
            HeatFC2Vsns,
            HeatFC2Isns,
            PrgA2Isns,
            PrgB2Isns,
            PrgC2Isns,
            CP2Vsns,
            CP2Isns,

            CP3Vsns,
            CP3Isns,
            Start5V0Isns,
            TankPsi,
            _12V0Vsns,
            _12V0Isns,

            Hum2Tsns,
            Hum1Tsns,

            HeatBattVsns,
            HeatBattIsns,
            BattTsns,
            SparePsi,

            ControlsMask,

            NumShortStats,
        };

        public FcAirDiags()
            : base(StatsType.FcDiags)
        {
            m_IntGroup = new Int32[(int)IntStats.NumIntStats];
            m_ShortGroup = new Int32[(int)ShortStats.NumShortStats];
        }

        public static FcAirDiags deserialize(String Result)
        {
            FcAirDiags stats = new FcAirDiags();

            stats.m_TickCount = System.Environment.TickCount;

            char[] sDelim = { '*' };
            string[] sNoCs = Result.Split(sDelim);

            char[] sDelim2 = { ',' };
            string[] sArgs = sNoCs[0].Split(sDelim2);
            int nSkip = 5;
            double nVal;
            int nStatsSkip = 2;

            for (int i = nSkip; i < sArgs.Length; i++)
            {
                nVal = 0;
                try
                {
                    if (sArgs[i] != "")
                        nVal = Convert.ToDouble(sArgs[i]);

                }
                catch { }

                stats.m_ShortGroup[i - nSkip + nStatsSkip] = Convert.ToInt32(nVal * (double)m_Scale[i - nSkip + nStatsSkip]);
                if (i - nSkip + nStatsSkip + 1 >= stats.getNumStats())
                    break;
            }


            return stats;
        }

        public static FcAirDiags deserialize(byte[] pPkt)
        {
            FcAirDiags stats = new FcAirDiags();

            stats.m_TickCount = System.Environment.TickCount;

            int nOffset = 2;
            for (int i = 0; i < 2; i++)
            {
                int nVal = SerialBinaryCommand.getIntFromStream(pPkt, ref nOffset);
                stats.m_ShortGroup[i] = nVal;
            }
            for (int i = 2; i < stats.m_ShortGroup.Length; i++)
            {
                short shVal = SerialBinaryCommand.getShortFromStream(pPkt, ref nOffset);
                stats.m_ShortGroup[i] = (int)shVal;
            }

            return stats;
        }

        private int getShortValue(int idx)
        {
            return m_ShortGroup[idx];
        }

        private int getShortScale(int idx)
        {
            return m_Scale[idx];
        }

        public override double getDoubleValue(int item)
        {
            double val = (double)getShortValue(item);
            val /= (double)getShortScale(item);
            return val;
        }

        public override String getStatLabel(int idx)
        {
            return m_Type.ToString() + "." + ((ShortStats)idx).ToString();
        }
        public override String getUnitsLabel(int idx)
        {
            return m_Units[idx];
        }

        public override int getNumStats()
        {
            return (int)m_ShortGroup.Length;
        }

        public override int getTickCount()
        {
            return m_TickCount;
        }

        public override int getSystemUptime()
        {
            return m_IntGroup[(int)IntStats.SystemUptime];
        }
    }
}
