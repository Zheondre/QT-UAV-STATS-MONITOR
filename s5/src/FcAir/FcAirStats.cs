using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace UpgenConsole.FcAir
{
    public class FcAirStats : BaseStats
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

            "",  //FuelCellState,
            "A",  //LoadCurrent,
            "V",  //HybridBusVoltage,
            "A",  //ConverterCurrent,
            "A",  //DC1Current,
            "A",  //DC2Current,
            "A",  //DC3Current,
            "C",  //CpuTemperature,
            "C",  //ConverterTemperature1,
            "C",  //ConverterTemperature2,
            "C",  //ConverterTemperature3,
            "V",  //BatteryVoltage,
            "A",  //BatteryInCurrent,
            "A",  //BatteryOutCurrent,
            "V",  //Supply18Voltage,
            "A",  //Supply18Current,
            "C",  //AmbientTemperature,
            "",  //StatusErrorMask,
            "",  //StatusWarningMask,		
		    "psi",//TankPsi,
            "g",//H2MassRemaining,
            "min",//TimeRemaining,

            "V",  //Stk1FuelCellVoltage,	// 100ths
            "A",  //Stk1FuelCellCurrent,
            "psi",  //Stk1HydrogenPressure,
            "psi",  //Stk1BallastPressure,
            "C",  //Stk1CoolantOutputTemp,
            "C",  //Stk1StackSurfaceTemp,
            "%",  //Stk1AirBlowerDriveSignal,
            "%",  //Stk1BypassDriveSignal,	
            "",  //Stk1StateMachineStatus,
            "",  //Stk1ErrorMask,
            "",  //Stk1WarningMask,
		
            "V",  //Stk2FuelCellVoltage,	// 100ths
            "A",  //Stk2FuelCellCurrent,
            "psi",  //Stk2HydrogenPressure,
            "psi",  //Stk2BallastPressure,
            "C",  //Stk2CoolantOutputTemp,
            "C",  //Stk2StackSurfaceTemp,
            "%",  //Stk2AirBlowerDriveSignal,
            "%",  //Stk2BypassDriveSignal,	
            "",  //Stk2StateMachineStatus,
            "",  //Stk2ErrorMask,
            "",  //Stk2WarningMask,
        };

        static public int[] m_Scale =
        {
            1,  //CalendarTime
            1,  //UpTime
            //                              ICD     ADCTask         Old ADC
            1,  //FuelCellState,
            100,  //LoadCurrent,            100     10              1
            100,  //HybridBusVoltage,       100     10              1
            100,  //ConverterCurrent,       100     Not Correct
            100,  //DC1Current,             100     Not Correct
            100,  //DC2Current,             100     Not Correct
            100,  //DC3Current,             100     Not Correct
            10,  //CpuTemperature,          10      1
            10,  //ConverterTemperature1,    10      Not Correct
            10,  //ConverterTemperature2,    10      Not Correct
            10,  //ConverterTemperature3,    10      Not Correct
            100,  //BatteryVoltage,         100     10              1
            100,  //BatteryInCurrent,       100     10
            100,  //BatteryOutCurrent,      100     10
            100,  //Supply18Voltage,         100     10              1
            100,  //Supply18Current,        100     10
            10,  //AmbientTemperature,      10      1
            1,  //StatusErrorMask,
            1,  //StatusWarningMask,
		    10, //TankPsi,
            1,  //H2MassRemaining,
            1,   //TimeRemaining,
		
            100,  //Stk1FuelCellVoltage,	100     10
            100,  //Stk1FuelCellCurrent,    100     10
            100,  //Stk1HydrogenPressure,   100     10              1
            100,  //Stk1BallastPressure,    100     10              1
            10,  //Stk1CoolantOutputTemp,   10      1
            10,  //Stk1StackSurfaceTemp,    10      1
            1,  //Stk1AirBlowerDriveSignal, 100     N/A
            1,  //Stk1BypassDriveSignal,	100     N/A
            1,  //Stk1StateMachineStatus,   
            1,  //Stk1ErrorMask,
            1,  //Stk1WarningMask,
		
            100,  //Stk2FuelCellVoltage,    100     10
            100,  //Stk2FuelCellCurrent,    100     10
            100,  //Stk2HydrogenPressure,   100     10              1
            100,  //Stk2BallastPressure,    100     10              1
            10,  //Stk2CoolantOutputTemp,   10      1
            10,  //Stk2StackSurfaceTemp,    10      1
            1,  //Stk2AirBlowerDriveSignal, 100     N/A
            1,  //Stk2BypassDriveSignal,	100     N/A
            1,  //Stk2StateMachineStatus,
            1,  //Stk2ErrorMask,
            1,  //Stk2WarningMask,
        };

        public enum ShortStats
        {
            CalendarTime,
            UpTime,

            FuelCellState,
            LoadCurrent,
            HybridBusVoltage,
            ConverterCurrent,
            DC1Current,
            DC2Current,
            DC3Current,
            CpuTemperature,
            ConverterTemperature1,
            ConverterTemperature2,
            ConverterTemperature3,
            BatteryVoltage,
            BatteryInCurrent,
            BatteryOutCurrent,
            Supply18Voltage,
            Supply18Current,
            AmbientTemperature,
            StatusErrorMask,
            StatusWarningMask,
		    TankPsi,
            H2MassRemaining,
            TimeRemaining,

            Stk1FuelCellVoltage,	// 100ths
            Stk1FuelCellCurrent,
            Stk1HydrogenPressure,
            Stk1BallastPressure,
            Stk1CoolantOutputTemp,
            Stk1StackSurfaceTemp,
            Stk1AirBlowerDriveSignal,
            Stk1BypassDriveSignal,
            Stk1StateMachineStatus,
            Stk1ErrorMask,
            Stk1WarningMask,

            Stk2FuelCellVoltage,	// 100ths
            Stk2FuelCellCurrent,
            Stk2HydrogenPressure,
            Stk2BallastPressure,
            Stk2CoolantOutputTemp,
            Stk2StackSurfaceTemp,
            Stk2AirBlowerDriveSignal,
            Stk2BypassDriveSignal,
            Stk2StateMachineStatus,
            Stk2ErrorMask,
            Stk2WarningMask,

            NumShortStats,
        };

        public FcAirStats()
            : base(StatsType.FcAir)
        {
            m_IntGroup = new Int32[(int)IntStats.NumIntStats];
            m_ShortGroup = new Int32[(int)ShortStats.NumShortStats];
        }

        public static FcAirStats deserialize(String Result)
        {
            FcAirStats stats = new FcAirStats();

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

        public static FcAirStats deserialize(byte[] pPkt)
        {
            FcAirStats stats = new FcAirStats();

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
