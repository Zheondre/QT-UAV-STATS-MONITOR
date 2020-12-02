#include "fcairstats.h"

const QString FcAirStats::m_Names [NumShortStats] ={
    "CalTime",
    "UpTime",

    "FuelCellState",
    "Load_I",
    "HybrdBusV",
    "Converter_I",
    "DC1_I",
    "DC2_I",
    "DC3_I",
    "CpuTemp",
    "Cnvrtr_T1",
    "Cnvrtr_T2",
    "Cnvrtr_T3",
    "Bat_V",
    "Bat_In_I",
    "Bat_Out_I",
    "Supply18V",
    "Supply18I",
    "Amb_T",
    "StatErrrMsk",
    "StatsWrningMsk",
    "TankPsi",
    "H2MassRemaining",
    "TimeRemaining",

    "Stk1_FC_V",	// 100ths
    "Stk1_FC_I",
    "Stk1_H2_Psi",
    "Stk1BallastPsi",
    "Stk1_Cool_Out_T",
    "Stk1SurfaceTemp",
    "Stk1AirBlowerDriveSignal",
    "Stk1BypassDriveSignal",
    "Stk1StateMachineStatus",
    "Stk1ErrMsk",
    "Stk1WrngMsk",

    "Stk2FuelCellVoltage",	// 100ths
    "Stk2FuelCellCurrent",
    "Stk2HydrogenPressure",
    "Stk2BallastPressure",
    "Stk2CoolantOutputTemp",
    "Stk2StackSurfaceTemp",
    "Stk2AirBlowerDriveSignal",
    "Stk2BypassDriveSignal",
    "Stk2StateMachineStatus",
    "Stk2ErrorMask",
    "Stk2WarningMask"

};

const QString FcAirStats::m_Units[NumShortStats] =
{
   "sec",  //CalendarTime
   "sec",  //UpTime

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

FcAirStats::FcAirStats()
 : BaseStats(StatsType::FcAir)
{
    for(int i = 0; i <NumShortStats; i++){
        //mItems.append(new StatsItem(StatsType::FcAir,i)) ;
        StatsItem *t = new StatsItem(StatsType::FcAir,i);
        t->m_nValue = 0;
        mItems.append(t);
    }
}

QString FcAirStats::getName(int idx) const{
    return m_Names[idx];
}
QString FcAirStats::getUnit(int idx) const{
    return m_Units[idx];
}

void FcAirStats::setFav(bool val, int idx)
{
    if(mItems.size() > idx){
      //if(mItems.at(idx)->m_bFav != val){
        mItems.at(idx)->m_bFav = val;
       // emit favChanged(this, idx);
        /*
        if(mItems.at(idx)->m_bFav)
          emit favAdded(this,idx);
        else
          emit favRemoved(this,idx);*/
      //}
    }
}
void FcAirStats::setForce(bool val, int idx)
{
    if(mItems.size() > idx){
        mItems.at(idx)-> m_bForce = val;
    }
}
void FcAirStats::setPlot(bool val, int idx)
{
    if(mItems.size() > idx){
        mItems.at(idx)->m_bPlot = val;
        if(mItems.at(idx)->m_bPlot)
          emit graphAdded(this,idx);
        else
          emit graphRemoved(this,idx);
    }
}

FcAirStats* FcAirStats::getFcStatsInstance() {
    return this;
}
