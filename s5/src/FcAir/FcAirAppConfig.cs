using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.IO;
using System.Xml.Serialization;

namespace UpgenConsole.FcAir
{
    public class FcDiagsAppConfig : BaseAppConfig
    {
        public enum GraphGroups
        {
            FuelCell1,
            FuelCell2,
            Bop,
            Other,
        };

        public GraphItem[] m_ItemFc1List = 
        { 
	        new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats.HeatFC1Vsns),
	        new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats.HeatFC1Isns),
	        new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats.HeatHum1Vsns),	
	        new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats.HeatHum1Isns),	
	        new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats.PrgA1Isns),	
	        new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats.PrgB1Isns),	
	        new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats.PrgC1Isns),	
	        new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats.CP1Vsns),	
	        new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats.CP1Isns),	
	        new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats.Stk1CoolantInputTemp),	
        };

        public GraphItem[] m_ItemFc2List = 
        { 
	        new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats.HeatFC2Vsns),
	        new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats.HeatFC2Isns),
	        new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats.HeatHum2Vsns),	
	        new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats.HeatHum2Isns),	
	        new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats.PrgA2Isns),	
	        new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats.PrgB2Isns),	
	        new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats.PrgC2Isns),	
	        new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats.CP2Vsns),	
	        new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats.CP2Isns),	
	        new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats.Stk2CoolantInputTemp),	
        };

        public GraphItem[] m_ItemBopList = 
        { 
	        new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats._5VoutIsns),
	        new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats.BopVsns),
	        new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats.BopIsns),
	        new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats.CP3Vsns),
	        new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats.CP3Isns),
	        new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats.Start5V0Isns),
	        new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats._12V0Vsns),
	        new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats._12V0Isns),
        };

        public GraphItem[] m_ItemOtherList = 
        { 
            new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats.TankPsi),
            new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats.Hum2Tsns),
            new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats.Hum1Tsns),
		    new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats.CalendarTime),
		    new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats.UpTime),

            new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats.HeatBattVsns),
            new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats.HeatBattIsns),
            new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats.BattTsns),
            new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats.SparePsi),
            new GraphItem( BaseStats.StatsType.FcDiags, (int)FcAirDiags.ShortStats.ControlsMask),
        };

        public GraphItem[][] m_GraphItemsGroups;

        public override String GroupLabelFromIndex(int idx)
        {
            return ((GraphGroups)idx).ToString();
        }
        public override int NumStats()
        {
            return (int)FcAirDiags.ShortStats.NumShortStats;
        }

        public override String UnitsFromIndex(int idx)
        {
            return FcAirDiags.m_Units[idx];
        }
        public override String LabelFromIndex(int idx)
        {
            return ((FcAirDiags.ShortStats)idx).ToString();
        }
        public override int ScaleFromIndex(int idx)
        {
            return FcAirDiags.m_Scale[idx];
        }
        public override GraphItem[][] getGraphItemsGroups()
        {
            return m_GraphItemsGroups;
        }

        public override SerialBinaryCommand.ConfigSubCommand GetSettingPollCmd()
        {
            return SerialBinaryCommand.ConfigSubCommand.GetFcAirSettings;
        }
        public override SerialBinaryCommand.ConfigSubCommand GetLimitsPollCmd()
        {
            return SerialBinaryCommand.ConfigSubCommand.GetFcAirLimits;
        }
        public override SerialBinaryCommand.ConfigSubCommand GetSettingUpdateCmd()
        {
            return SerialBinaryCommand.ConfigSubCommand.SetFcAirSettings;
        }
        public override SerialBinaryCommand.ConfigSubCommand GetLimitsUpdateCmd()
        {
            return SerialBinaryCommand.ConfigSubCommand.SetFcAirLimits;
        }
        public override SerialBinaryCommand.StatsSubCommand GetStatsPollCmd()
        {
            return SerialBinaryCommand.StatsSubCommand.Diags;
        }

        public FcDiagsAppConfig()
            : base(BaseStats.StatsType.FcDiags)
        {
            GraphItem[][] GraphItemGroups = 
            {
                m_ItemFc1List,
                m_ItemFc2List,
                m_ItemBopList,
                m_ItemOtherList,
            };

            m_GraphItemsGroups = GraphItemGroups;
        }
    }
}
