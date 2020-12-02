using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.IO;
using System.Xml.Serialization;

namespace UpgenConsole.FcAir
{
    public class FcAirAppConfig : BaseAppConfig
    {
        public enum GraphGroups
        {
            FuelCell,
            Temperature,
            DutyCycle,
            Power,
            Other,
        };

        public GraphItem[] m_ItemTempList = 
        { 
	        new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.CpuTemperature),
	        new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.ConverterTemperature1),
	        new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.ConverterTemperature2),
	        new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.ConverterTemperature3),
	        new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.AmbientTemperature),	
	        new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.Stk1CoolantOutputTemp),	
	        new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.Stk1StackSurfaceTemp),	
	        new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.Stk2CoolantOutputTemp),	
	        new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.Stk2StackSurfaceTemp),	
        };

        public GraphItem[] m_ItemDutyCycleList = 
        { 
	        new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.Stk1AirBlowerDriveSignal),
	        new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.Stk1BypassDriveSignal),
	        new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.Stk2AirBlowerDriveSignal),
	        new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.Stk2BypassDriveSignal),
        };

        public GraphItem[] m_ItemFuelCellList = 
        { 
	        new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.FuelCellState),
	        new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.Stk1FuelCellCurrent),
	        new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.Stk1FuelCellVoltage),
	        new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.Stk1HydrogenPressure),
	        new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.Stk1BallastPressure),
	        new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.Stk2FuelCellCurrent),
	        new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.Stk2FuelCellVoltage),
	        new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.Stk2HydrogenPressure),
	        new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.Stk2BallastPressure),
        };

        public GraphItem[] m_ItemPowerList = 
        { 
	        new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.LoadCurrent),
	        new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.HybridBusVoltage),
	        new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.ConverterCurrent),
	        new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.DC1Current),
	        new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.DC2Current),
	        new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.DC3Current),
	        new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.BatteryVoltage),
	        new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.BatteryInCurrent),
	        new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.BatteryOutCurrent),
	        new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.Supply18Voltage),
	        new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.Supply18Current),
        };

        public GraphItem[] m_ItemOtherList = 
        { 
            new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.StatusErrorMask),
            new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.StatusWarningMask),
            new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.Stk1StateMachineStatus),
            new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.Stk1ErrorMask),
            new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.Stk1WarningMask),
            new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.Stk2StateMachineStatus),
		    new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.Stk2ErrorMask),
		    new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.Stk2WarningMask),
		    new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.CalendarTime),
		    new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.UpTime),
            new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.TankPsi),
            new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.H2MassRemaining),
            new GraphItem( BaseStats.StatsType.FcAir, (int)FcAirStats.ShortStats.TimeRemaining),
        };

        public GraphItem[][] m_GraphItemsGroups;

        public override String GroupLabelFromIndex(int idx)
        {
            return ((GraphGroups)idx).ToString();
        }
        public override int NumStats()
        {
            return (int)FcAirStats.ShortStats.NumShortStats;
        }

        public override String UnitsFromIndex(int idx)
        {
            return FcAirStats.m_Units[idx];
        }
        public override String LabelFromIndex(int idx)
        {
            return ((FcAirStats.ShortStats)idx).ToString();
        }
        public override int ScaleFromIndex(int idx)
        {
            return FcAirStats.m_Scale[idx];
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
            return SerialBinaryCommand.StatsSubCommand.FcAir;
        }

        public FcAirAppConfig()
            : base(BaseStats.StatsType.FcAir)
        {
            GraphItem[][] GraphItemGroups = 
            {
                m_ItemFuelCellList,
                m_ItemTempList,
                m_ItemDutyCycleList,
                m_ItemPowerList,
                m_ItemOtherList,
            };

            m_GraphItemsGroups = GraphItemGroups;
        }
    }
}
