using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace UpgenConsole.FcAir
{
    public class FcAirSettings
    {
        public enum Items
        {
            ChargeVoltageAt25C,	//	Top charge voltage
            DeadVoltage,			//	Dead Voltage
            MaxChargeTemp,		//	Max Charge Temp,
            MinChargeTemp,		//	Min charge Temp,
            ChargeVoltageAt0C, //	Top Charge Temp Compensation Slope MilliVoltsPer Degrees C (Nominal = 25),
            MaxChargeCurrent,	// battery limit on charge current
            MaxBatteryVoltage,	// battery limit on voltage

            BlockCS,

            NumItems
        };

        int[] m_Items;

        int m_nPacketSize;

        public FcAirSettings()
        {
            m_Items = new int[(int)Items.NumItems];
        }

        public static FcAirSettings deserialize(byte[] pPkt)
        {
            FcAirSettings status = new FcAirSettings();

            int nOffset = 2;
            for (int i = 0; i < (int)Items.NumItems; i++)
            {
                status.m_Items[i] = SerialBinaryCommand.getIntFromStream(pPkt, ref nOffset);
            }

            status.m_nPacketSize = nOffset;

            byte[] test = status.serialize(0, 0);
            for (int i = 2; i < status.m_nPacketSize; i++)
            {
                if (test[i] != pPkt[i])
                    break;
            }

            return status;
        }

        public byte[] serialize(byte nCmd, byte nSubCmd)
        {
            byte[] packet = new byte[m_nPacketSize];

            packet[0] = nCmd;
            packet[1] = nSubCmd;
            int nOffset = 2;
            for (int i = 0; i < (int)Items.NumItems; i++)
            {
                SerialBinaryCommand.addIntToStream(ref packet, m_Items[i], ref nOffset);
            }

            return packet;
        }

        private double getScale(Items item)
        {
            double nScale = 1000.0;
            switch (item)
            {
                default:
                    break;
                case Items.MaxChargeTemp:
                case Items.MinChargeTemp:
                    nScale = 10.0;
                    break;
            }
            return nScale;
        }

        public double getValue(Items item)
        {
            int nVal = m_Items[(int)item];
            return (double)nVal / getScale(item);
        }

        public void setValue(Items item, double nVal)
        {
            m_Items[(int)item] = (int)(nVal * getScale(item));
        }
    }
}
