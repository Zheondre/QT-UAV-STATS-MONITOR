//#include <QTextStream> // debug
#include <QDebug>

#include "statsModel.h"
//#include "C:\Source\QT\s5\src\FcAir\fcairstats.h"


statsModel::statsModel(QObject *parent)
    : QAbstractListModel(parent)\
, m_pList(nullptr)
{
}

int statsModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !m_pList)
        return 0;

    return m_pList->getNumStats();
}

void statsModel::update(const int pos, const int role){
    //qDebug() << "FcStatsModel: trying dataChanged slot";
    emit dataChanged(index(pos,0), index(pos,0), QVector<int>() << role);
}

QVariant statsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    //qDebug() << "Testing getData";

  switch(role){
    case FCSTAT_FAV:
        return QVariant(m_pList->getFav(index.row()));
    case FCSTAT_PLOT:
        return QVariant(m_pList->getPlot(index.row()));
    case FCSTAT_NAME:
        return QVariant(m_pList->getName(index.row()));
    case FCSTAT_VALUE:{
      int temp;
         //return QVariant(m_pList->getValue(index.row()));

    temp = m_pList->getValue(index.row());
    return QVariant(temp);
  }
    case FCSTAT_UNIT:
         return QVariant(m_pList->getUnit(index.row()));
    case FCSTAT_FORCE:
        return QVariant(m_pList->getForce(index.row()));
    //case FCSTAT_UINPUT:
   //      return QVariant(item.getInput());
    }
    return QVariant();
}

bool statsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
     //qDebug() << "StatsModel: Testing setData";

    if(!m_pList)
        return false;

    switch(role){
       case FCSTAT_FAV:
        m_pList->setFav(value.toBool(), index.row());
        break;

        case FCSTAT_PLOT:
            m_pList->setPlot(value.toBool(), index.row());
        break;
        case FCSTAT_NAME:
            m_pList->setName(value.toString(), index.row());
            break;
        case FCSTAT_VALUE:
            //m_pList->setValue(value.toInt(), index.row());
            break;
        case FCSTAT_UNIT:
            m_pList->setUnit(value.toString(), index.row());
            break;
        case FCSTAT_FORCE:
            m_pList->setForce(value.toBool(), index.row());
            break;
        case FCSTAT_UINPUT:
             m_pList->setInput(value.toString(), index.row());
             break;
    }

    emit dataChanged(index, index, QVector<int>() << role);
    return true;
}

Qt::ItemFlags statsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> statsModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[FCSTAT_FAV]   ="fav";
    names[FCSTAT_PLOT]  ="plot";
    names[FCSTAT_NAME]  ="name";
    names[FCSTAT_VALUE] ="value";
    names[FCSTAT_UNIT]  ="unit";
    names[FCSTAT_FORCE] ="force";
    names[FCSTAT_UINPUT]="userInput";
    return names;
}

BaseStats *statsModel::getList() const{ return m_pList; }

void statsModel::setList(BaseStats *list){

    beginResetModel();

    if(m_pList)
        m_pList->disconnect(this);
/*
    //might not need this ///temp
    if(list){
        switch(list->getStatsType()){
            case BaseStats::StatsType::Sofc:
            break;
            case BaseStats::StatsType::Rws:
            break;
            case BaseStats::StatsType::FcAir:
                m_pList = (FcAirStats*)list;
            break;
            case BaseStats::StatsType::BMS:
            break;
            case BaseStats::StatsType::FcDiags:
            break;
            case BaseStats::StatsType::Custom:
            break;
            case BaseStats::StatsType::Any:
            break;
        }
    }
    // temp temp temp
    */
    m_pList = list;

    if(m_pList){
       //load model list data change notification connections
       connect(m_pList, SIGNAL(dataChanged(const int,const int)), this, SLOT(update(const int, const int)));

/*
       connect(m_pList, &BaseStats::preItemAppended, this, [=](){
       const int index = m_pList->getNumStats();
       beginInsertRows(QModelIndex(), index, index);
       });

       connect(m_pList, &BaseStats::postItemAppended, this, [=](){
        endInsertRows();
        });
*/


    }

    endResetModel();
}

