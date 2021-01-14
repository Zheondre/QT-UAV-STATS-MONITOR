#include "fcairstats.h"

 // Name, command, detUntil, scale, Unit
 const StatsEntry FcAirStats::s_StatsEntries[NumShortStats] =
{
    { "CalTime","Time", "Other", 1, "", StatsEntry::DecodeCalendar  },
    { "UpTime","Uptime", "Other", 1, "", StatsEntry::DecodeUptime  },

    { "FuelCellState", "FuelCellState", "Other", 1, "", StatsEntry::DecodeNormal  },
    { "Load_I", "LoadCurrent", "Power", 100, "A", StatsEntry::DecodeNormal  },
    { "HybrdBusV", "HybridBusVoltage", "Power", 100, "V", StatsEntry::DecodeNormal  },
    { "Converter_I", "ConverterCurrent", "Power", 100, "A", StatsEntry::DecodeNormal  },
    { "DC1_I", "DC1Current", "Power", 100, "A", StatsEntry::DecodeNormal  },
    { "DC2_I", "DC2Current", "Power", 100, "A", StatsEntry::DecodeNormal  },
    { "DC3_I", "DC3Current", "Power", 100, "A", StatsEntry::DecodeNormal  },
    { "CpuTemp", "CpuTemperature", "Temperature", 10, "C", StatsEntry::DecodeNormal  },
    { "Cnvrtr_T1", "ConverterTemperature1", "Temperature", 10, "C", StatsEntry::DecodeNormal  },
    { "Cnvrtr_T2", "ConverterTemperature2", "Temperature", 10, "C", StatsEntry::DecodeNormal  },
    { "Cnvrtr_T3", "ConverterTemperature3", "Temperature", 10, "C", StatsEntry::DecodeNormal  },
    { "Bat_V", "BatteryVoltage", "Power", 100, "V", StatsEntry::DecodeNormal  },
    { "Bat_In_I", "BatteryCurrent", "Power", 100, "A", StatsEntry::DecodeNormal  },
    { "Bat_Out_I", "BatteryOutCurrent", "Power", 100, "A", StatsEntry::DecodeNormal  },
    { "Supply18V", "Supply18Voltage", "Other", 100, "V", StatsEntry::DecodeNormal  },
    { "Supply18I", "Supply18Current", "Other", 100, "A", StatsEntry::DecodeNormal  },
    { "Amb_T", "Ambient", "Temperature", 10, "C", StatsEntry::DecodeNormal  },
    { "ErrrMsk", "MasterErrorMask", "Other", 1, "", StatsEntry::DecodeHex  },
    { "WrningMsk","MasterWarningMask", "Other", 1, "", StatsEntry::DecodeHex  },

    { "Stk1_V", "fc1Vsns", "Power", 100, "V", StatsEntry::DecodeNormal  },
    { "Stk1_I", "fc1Isns", "Power", 100, "A", StatsEntry::DecodeNormal  },
    { "Stk1_H2_Psi","Stk1-FuelPressure", "Other", 100, "PSI", StatsEntry::DecodeNormal },
    { "Stk1BallastPsi", "Stk1-BallastPressure", "Other", 100, "PSI", StatsEntry::DecodeNormal },
    { "Stk1CoolantOut", "Stk1-CoolantOut", "Temperature", 10, "C", StatsEntry::DecodeNormal  },
    { "Stk1SurfaceTmp", "Stk1-StackSurface", "Temperature", 10, "C", StatsEntry::DecodeNormal  },
    { "Stk1FanDC", "Stk1-AirBlowerDC", "DutyCycle", 100, "%", StatsEntry::DecodeNormal  },
    { "Stk1DiverterDC", "Stk1-DiverterDC", "DutyCycle", 100, "%", StatsEntry::DecodeNormal  },
    { "Stk1StateMachine", "Stk1-StateMachine", "Other", 1, "", StatsEntry::DecodeNormal  },
    { "Stk1ErrMsk", "Stk1-ErrorMask", "Other", 1, "", StatsEntry::DecodeHex  },
    { "Stk1WrngMsk", "Stk1-WarningMask", "Other", 1, "", StatsEntry::DecodeHex  },

    { "Stk2-V", "fc2Vsns", "Power", 100, "V", StatsEntry::DecodeNormal  },
    { "Stk2-I", "fc2Isns", "Power", 100, "A", StatsEntry::DecodeNormal  },
    { "Stk2H2Psi", "Stk2-FuelPressure", "Other", 100, "PSI", StatsEntry::DecodeNormal },
    { "Stk2BallastPsi", "Stk2-BallastPressure", "Other", 100, "PSI", StatsEntry::DecodeNormal },
    { "Stk2CoolantOut", "Stk2-CoolantOut", "Temperature", 10, "C", StatsEntry::DecodeNormal  },
    { "Stk2SurfaceTmp", "Stk2-StackSurface", "Temperature", 10, "C", StatsEntry::DecodeNormal  },
    { "Stk2FanDC", "Stk2-AirBlowerDC", "DutyCycle", 100, "%", StatsEntry::DecodeNormal  },
    { "Stk2DiverterDC", "Stk2-DiverterDC", "DutyCycle", 100, "%", StatsEntry::DecodeNormal  },
    { "Stk2StateMachine", "Stk2-StateMachine", "Other", 1, "", StatsEntry::DecodeNormal  },
    { "Stk2ErrMsk", "Stk2-ErrorMask", "Other", 1, "", StatsEntry::DecodeHex  },
    { "Stk2WrngMsk", "Stk2-WarningMask", "Other", 1, "", StatsEntry::DecodeHex  },
};

FcAirStats::FcAirStats()
 : BaseStats(StatsType::FcAir)
{
    for(int i = 0; i <NumShortStats; i++){
        //mItems.append(new StatsItem(StatsType::FcAir,i)) ;
        StatsItem *t = new StatsItem(StatsType::FcAir,i);

        #ifdef Q_OS_WIN || Q_OS_LINUX
        t->m_nValue = 11;
#else
        t->m_nValue = 0;
#endif
        mItems.append(t);
    }
}

void FcAirStats::deserialize(const QString &Data){//make this to const ref
// get tick count or time count when data comes in
    char sDelim = { '*' };
     QStringList sNoCs = Data.split(sDelim);

     char sDelim2 = { ',' };
     QStringList sArgs = sNoCs[0].split(sDelim2);
     int nSkip = 5;
     double nVal;
     int nStatsSkip = 2;

     for (int i = nSkip; i < sArgs.size(); i++)
     {
         nVal = 0;
         //try
         //{
             if (sArgs[i] != "")
                 nVal = sArgs[i].toDouble();
         //}
        // catch { }

         mItems[i - nSkip + nStatsSkip]->m_nValue = (int)(nVal * (double)s_StatsEntries[i - nSkip + nStatsSkip].nScale);
         if (i - nSkip + nStatsSkip + 1 >= NumShortStats)
             break;
     }
     //emit conversionComplete();
}

QString FcAirStats::getFavName(int idx) const
{
  if(m_pfavList.size() > idx)
    return s_StatsEntries[m_pfavList.at(idx)->m_npos].name; // what if we have fcstats and rwsstats come in ?
  else
      return "items ERROR";
}

QString FcAirStats::getFavUnit(int idx) const
{
    if(m_pfavList.size() > idx)
        return s_StatsEntries[m_pfavList.at(idx)->m_npos].unit;  // what if we have fcstats and rwsstats come in ?
    else
        return "Index ERROR";
}

QString FcAirStats::getName(int idx) const{
      if((mItems.size() > idx) && (idx >= 0)){
          return s_StatsEntries[idx].name;
      }
    return QString("%");
}
QString FcAirStats::getUnit(int idx) const{
    if((mItems.size() > idx) && (idx >= 0)){
        return s_StatsEntries[idx].unit;
    }
    return QString(" ");
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
          emit favRemoved(this,idx);
          */
      //}
    }
}

void FcAirStats::setForce(bool val, int idx)
{// should we expect for a reply ?
    if(mItems.size() > idx){
        mItems.at(idx)->m_bForce = val;
        if(mItems.at(idx)->m_bForce)
           emit sendForceCommand("force " + s_StatsEntries[idx].command);
        else
           emit sendForceCommand("clear " + s_StatsEntries[idx].command);
    }
}

FcAirStats* FcAirStats::getFcStatsInstance() {
    return this;
}
