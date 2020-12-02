#ifndef FCAIRSTATS_H
#define FCAIRSTATS_H

#include "C:\Source\QT\s5\basestats.h"

class FcAirStats : public BaseStats
{
public:

    enum IntStats {
       CalTime,
       SystemUptime,

       NumIntStats,
    };
    enum ShortStats
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
    static const QString m_Names[NumShortStats];
    static const QString m_Units[NumShortStats];
    //static const constexpr char* const m_Units[46] ;

    static const constexpr int m_Scale[NumShortStats] =
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

     FcAirStats();

     QString getName(int idx) const;
     QString getUnit(int idx) const;

     void setFav(bool val, int idx);
     void setForce(bool val, int idx);
     void setPlot(bool val, int idx);

     FcAirStats* getFcStatsInstance();
};

#endif // FCAIRSTATS_H
