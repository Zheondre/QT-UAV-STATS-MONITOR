#include "basestats.h"

/*
BaseStats::BaseStats(StatsType type,BaseStats* fl) : QObject(nullptr), m_Type(type), m_pfavList(fl)
{
     connect(this,SIGNAL(favChanged(StatsItem *obj, int rowIndex)),
    m_pfavList,SLOT(addFavorite(StatsItem *obj, int rowIndex)));
}
*/

QVector<StatsItem*> BaseStats::m_pfavList; //make this a hash map instead ?

BaseStats::BaseStats(QObject *parent) : QObject(parent), m_Type(Custom){
}

BaseStats::BaseStats(StatsType type) : QObject(nullptr), m_Type(type)
{
    //connect(this,SIGNAL(favChanged(StatsItem *obj, int rowIndex)),
   //m_pfavList,SLOT(addFavorite(StatsItem *obj, int rowIndex)));

}

void BaseStats::deserialize(QString Data){
;
}

QVector<StatsItem*> BaseStats::getStatItems(){ return mItems; }

void BaseStats::updateFavList(StatsItem *obj, int rowIndex){
    if(obj->m_bFav){
        if(!mItems.contains(obj))
            mItems.append(obj);
    }else
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
//#ifdef TRUE

  /*
  double BaseStats::getValue(int item)
{
    return mItem.at(item).m_sValue;
}
*/
//#ifdef true
 int BaseStats::getFavValue(int idx) const
{
      if(m_pfavList.size() > idx)
         return m_pfavList.at(idx)->m_nValue;
      else
         return -1;
}

  QString BaseStats::getFavName(int idx) const
{
      return "";
}

  QString BaseStats::getFavUnit(int idx) const
{
      return "";
}

void BaseStats::setFavInput(const QString &val, int idx){

    if(m_pfavList.at(idx)->m_bForce){
        if(m_pfavList.at(idx)->m_sInput != val){
            m_pfavList.at(idx)->m_sInput = val;
         //send message out to the world about the update
        }
    }
}

bool BaseStats::getFavFav(int idx) const
{
    if(m_pfavList.size() > idx)
        return m_pfavList.at(idx)->m_bFav;
    else
        return false;
}


bool BaseStats::getFavForce(int idx) const
{
    if(m_pfavList.size() > idx)
        return m_pfavList.at(idx)->m_bForce;
    else
        return false;

}
bool BaseStats::getFavPlot(int idx) const
{
    if(m_pfavList.size() > idx)
        return m_pfavList.at(idx)->m_bPlot;
    else
        return false;
}


void BaseStats::setFavFav(bool val, int idx)
{//fav list only show items that are selected
    if(m_pfavList.size() > idx){
      m_pfavList.at(idx)->m_bFav = val;

      int j = 0, l = 0;

      for(auto i: m_pfavList){
          if(i == m_pfavList.at(j)){

              for(auto k: mItems){
               if(i == k)
                   break;
                j++;
              }

             // emit preItemRemove();

              m_pfavList.remove(l);
                break;

             // emit postItemRemove();
          }
          l++;
      }

      emit dataChanged( j, FCSTAT_FAV);
    }

}
void BaseStats::setFavForce(bool val, int idx)
{
    if(m_pfavList.size() > idx)
        m_pfavList.at(idx)-> m_bForce = val;
}
void BaseStats::setFavPlot(bool val, int idx)
{
    if(m_pfavList.size() > idx)
        m_pfavList.at(idx)->m_bPlot = val;
}
// have worker thread call function bellow

void BaseStats::setFavValue(const int val, bool update, int idx)
{
    if(m_pfavList.size() > idx){
        if(m_pfavList.at(idx)->m_nValue != val){
          m_pfavList.at(idx)->m_nValue = val;
          if(update)
            emit dataChanged(idx,FCSTAT_VALUE);
        }
    }
}

//#endif
  int BaseStats::getValue(int idx) const
{
      if(mItems.size() > idx)
         return mItems.at(idx)->m_nValue;
      else
         return -1;
}

  QString BaseStats::getName(int idx) const
{
    return "";
}

  QString BaseStats::getUnit(int idx) const
{
    return "";
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

      if(mItems.at(idx)->m_bFav){
          if(!m_pfavList.contains(mItems.at(idx ))){
              emit preItemAppend();
              m_pfavList.append(mItems.at(idx));
              emit postItemAppended();
            //emit favChanged(m_pfavList.size());
          }
      }else
          if(m_pfavList.contains(mItems.at(idx))){
              int j  =0;
              for(auto i: m_pfavList){
                  if(i == m_pfavList.at(j)){
                      emit preItemRemoved(j);
                      m_pfavList.remove(j);
                      emit postItemRemoved();
                        break;
                  }
                   j++;
              }

          }
       //emit favchanged(t/f, idx );
      //emit favChanged(this, idx, val);
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

/*int BaseStats::getTickCount(){return 0;}*/

int BaseStats::getSystemUptime(){  return 0;}
