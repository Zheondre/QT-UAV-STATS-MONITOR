#ifndef FCAIRSTATS_H
#define FCAIRSTATS_H

#include "C:\Source\QT\QTGITREPO\s5\basestats.h"
#include "statsEntry.h"

class FcAirStats : public BaseStats
{

    Q_OBJECT
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

    static const StatsEntry s_StatsEntries[NumShortStats]; // double check this

     FcAirStats();

     QString getFavName(int idx) const;
     QString getFavUnit(int idx) const;

     QString getName(int idx) const;
     QString getUnit(int idx) const;

     void setFav(bool val, int idx);
     void setForce(bool val, int idx);
     //void setPlot(bool val, int idx);

     FcAirStats* getFcStatsInstance();

signals:
    void  btrun();

     public slots:
        void deserialize(const QString &Data);
};

#endif // FCAIRSTATS_H
