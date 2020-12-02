using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace UpgenConsole.FcAir
{
    public class FcAirLimits
    {
        public enum Items
        {
            MaxExternalStackTemp,
            MaxInternalStackTemp,
            MaxBoardTemp,
            MaxConverterTemp,
            TempErrorFaultTime,

            StackMinimumVoltage,
            MaxStackCurrent,

            MaxH2Pressure,
            HighPressureErrorRemediateTime,
            HighPressureErrorFaultTime,

            MinH2Pressure,
            LowPressureErrorFaultTime,

            BlockCS,

            NumItems
        };

        int[] m_Items;

        int m_nPacketSize;

        public FcAirLimits()
        {
            m_Items = new int[(int)Items.NumItems];
        }

        public static FcAirLimits deserialize(byte[] pPkt)
        {
            FcAirLimits status = new FcAirLimits();

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
            double nScale = 1.0;
            switch (item)
            {
                default:
                    break;
                case Items.TempErrorFaultTime:
                case Items.MaxH2Pressure:
                case Items.MinH2Pressure:
                case Items.HighPressureErrorRemediateTime:
                case Items.HighPressureErrorFaultTime:
                case Items.LowPressureErrorFaultTime:
                case Items.StackMinimumVoltage:
                case Items.MaxStackCurrent:
                    nScale = 1000.0;
                    break;
                case Items.MaxBoardTemp:
                case Items.MaxExternalStackTemp:
                case Items.MaxInternalStackTemp:
                case Items.MaxConverterTemp:
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
