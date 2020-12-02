#include "basestats.h"

BaseStats::BaseStats(QObject *parent) : QObject(parent), m_Type(Custom), m_pfavList(NULL){
}

BaseStats::BaseStats(StatsType type) : QObject(nullptr), m_Type(type), m_pfavList(NULL)
{}

BaseStats::BaseStats(StatsType type,BaseStats* fl) : QObject(nullptr), m_Type(type), m_pfavList(fl)
{
     connect(this,SIGNAL(favChanged(StatsItem *obj, int rowIndex)),
    m_pfavList,SLOT(addFavorite(StatsItem *obj, int rowIndex)));

}

QVector<StatsItem*> BaseStats::getStatItems(){ return mItems; }


void BaseStats::updateFavList(StatsItem *obj, int rowIndex){
    if(obj->m_bFav)
        if(!mItems.contains(obj))
            mItems.append(obj);
    else
        if(mItems.contains(obj)){
            //if custom update front end
            //emit preItemRemove
            mItems.remove( mItems.indexOf(obj,0));
            //if custom update front end
            //emit postItemRemove
        }
}


BaseStats::StatsType BaseStats::getStatsType() const
{
    return m_Type;
}

  int BaseStats::getNumStats()
{
    return mItems.size();
}
/*
  double BaseStats::getValue(int item)
{
    return mItem.at(item).m_sValue;
}
*/
  int BaseStats::getValue(int idx) const
{
      if(mItems.size() > idx)
         return mItems.at(idx)->m_nValue;
      else
         return -1;
}

  QString BaseStats::getName(int idx) const
{
    if(mItems.size() > idx)
        return mItems.at(idx)->m_sName;
    else
        return "Index ERROR";
}

  QString BaseStats::getUnit(int idx) const
{
    if(mItems.size() > idx)
        return mItems.at(idx)->m_sUnit;
    else
        return "Index ERROR";
}

void BaseStats::setName(const QString &val, int idx)
{
    mItems.at(idx)->m_sName = val;
    emit dataChanged(idx,FCSTAT_NAME);
}
/*
void BaseStats::setValue(const int val, int idx)
{
    mItems.at(idx)->m_nValue = val;
    emit dataChanged(idx,FCSTAT_VALUE);
}
*/
void BaseStats::setUnit(const QString &val, int idx){
    mItems.at(idx)->m_sUnit = val;
}

void BaseStats::setInput(const QString &val, int idx){

    if(mItems.at(idx)->m_bForce){
        if(mItems.at(idx)->m_sInput != val){
            mItems.at(idx)->m_sInput = val;
         //send message out to the world about the update
        }
    }
}

bool BaseStats::getFav(int idx) const
{
    if(mItems.size() > idx)
        return mItems.at(idx)->m_bFav;
    else
        return false;
}
bool BaseStats::getForce(int idx) const
{
    if(mItems.size() > idx)
        return mItems.at(idx)->m_bForce;
    else
        return false;

}
bool BaseStats::getPlot(int idx) const
{
    if(mItems.size() > idx)
        return mItems.at(idx)->m_bPlot;
    else
        return false;
}

void BaseStats::setFav(bool val, int idx)
{
    if(mItems.size() > idx){
      mItems.at(idx)->m_bFav = val;
      emit favChanged(this, idx, val);
    }

}
void BaseStats::setForce(bool val, int idx)
{
    if(mItems.size() > idx)
        mItems.at(idx)-> m_bForce = val;
}
void BaseStats::setPlot(bool val, int idx)
{
    if(mItems.size() > idx)
        mItems.at(idx)->m_bPlot = val;
}
// have worker thread call function bellow
void BaseStats::setValue(const int val, bool update, int idx)
{
    if(mItems.size() > idx){
        if(mItems.at(idx)->m_nValue != val){
          mItems.at(idx)->m_nValue = val;
          if(update)
            emit dataChanged(idx,FCSTAT_VALUE);
        }
    }
}

//void BaseStats::setForce(bool val,  bool update, int idx){}
//void BaseStats::setPlot(bool val,  bool update, int idx){}

/*int BaseStats::getTickCount(){return 0;}*/

int BaseStats::getSystemUptime(){  return 0;}
/*
 BaseStats BaseStats::factory(BaseStats::StatsType typ)
{
    switch (typ)
    {
        case StatsType::Sofc:
            {
               // SofcStats s = new SofcStats();
                return s;
            }
    case StatsType::Rws:
            {
                Rws.RwsStats s = new Rws.RwsStats();
                return s;
            }
    case StatsType::FcAir:
            {
                FcAir::FcAirStats s = new FcAir.FcAirStats();
                return s;
            }
    case StatsType::BMS:
            {
                Bms.BmsStats s = new Bms.BmsStats();
                return s;
            }
    case StatsType::FcDiags:
            {
                FcAir.FcAirDiags s = new FcAir.FcAirDiags();
                return s;
            }
    }


    return ;
}
*/
/*
 int BaseStats::GetNumStats(BaseStats::StatsType typ)
{
    BaseStats a = factory(typ);
    return a.getNumStats();
}

StatsItem[] BaseStats::GetStatsItems()
{
    // use this to enable what works here
    //
    if (s_bIncludeFcAir)
    {
        StatsItem[] s = new StatsItem[5];
        s[0] = new StatsItem(BaseStats.StatsType.Sofc, "Sofc");
        s[1] = new StatsItem(BaseStats.StatsType.Rws, "Rws");
        s[2] = new StatsItem(BaseStats.StatsType.BMS, "Bms");
        s[3] = new StatsItem(BaseStats.StatsType.FcAir, "FcAir");
        s[4] = new StatsItem(BaseStats.StatsType.FcDiags, "FcDiags");

        return s;
    }
    else
    {
        StatsItem[] s = new StatsItem[1];
        s[0] = new StatsItem(BaseStats.StatsType.Sofc, "Sofc");
        return s;
    }
}
GraphItem[] BaseStats::GetGraphItems()
{
    int cnt = 0;
    StatsItem[] its = GetStatsItems();
    for (int i = 0; i < its.Length; i++)
    {
        BaseStats a = factory(its[i].m_Type);
        cnt += a.getNumStats();
    }

    GraphItem[] Items = new GraphItem[cnt];

    int outcnt = 0;

    for (int i = 0; i < its.Length; i++)
    {
        BaseStats a = factory(its[i].m_Type);
        for (int k = 0; k < a.getNumStats(); k++)
        {
            Items[outcnt++] = new GraphItem(its[i].m_Type, k);
        }
    }

    return Items;
}

public static int GetNumStats(BaseStats.StatsType typ)
{
    BaseStats a = factory(typ);
    return a.getNumStats();
}

*
    static String GetLabelFromGraphItem(GraphItem item)
   {
       BaseStats s = factory(item.m_Type);
       if (s != null)
           return s.getStatLabel(item.m_DataIndex);
       return "???";
   }

   public static String GetUnitsFromGraphItem(GraphItem item)
   {
       BaseStats s = factory(item.m_Type);
       if (s != null)
           return s.getUnitsLabel(item.m_DataIndex);
       return "???";
   }
   */
