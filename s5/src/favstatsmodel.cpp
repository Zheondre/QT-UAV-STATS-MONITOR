#include "favstatsmodel.h"

favStatsModel::favStatsModel()
{
}

int favStatsModel::rowCount(const QModelIndex &parent) const
{
 if (parent.isValid() || !m_pList)
        return 0;

    return m_pList->m_pfavList.size();
}

QVariant favStatsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    //qDebug() << "Testing getData";

  switch(role){
    case FCSTAT_FAV:
        return QVariant( m_pList->getFavFav(index.row()));
    case FCSTAT_PLOT:
        return QVariant(m_pList->getFavPlot(index.row()));
    case FCSTAT_NAME:
        return QVariant(m_pList->getFavName(index.row()));
    case FCSTAT_VALUE:
         return QVariant(m_pList->getFavValue(index.row()));
    case FCSTAT_UNIT:
         return QVariant(m_pList->getFavUnit(index.row()));
    case FCSTAT_FORCE:
        return QVariant(m_pList->getFavForce(index.row()));
    //case FCSTAT_UINPUT:
   //      return QVariant(item.getInput());
    }

    return QVariant();
}


bool favStatsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
     //qDebug() << "StatsModel: Testing setData";

    if(!m_pList)
        return false;

    switch(role){
       case FCSTAT_FAV:
        m_pList->setFavFav(value.toBool(), index.row());
        break;

        case FCSTAT_PLOT:
            m_pList->setFavPlot(value.toBool(), index.row());
        break;
        case FCSTAT_NAME:
            //m_pList->setName(value.toString(), index.row(), m_pList->m_pfavList);
            break;
        case FCSTAT_VALUE:
            m_pList->setFavValue(value.toInt(),true, index.row());
            break;
        case FCSTAT_UNIT:
            //m_pList->setFavUnit(value.toString(), index.row());
            break;
        case FCSTAT_FORCE:
            m_pList->setFavForce(value.toBool(), index.row());
            break;
        case FCSTAT_UINPUT:
             m_pList->setFavInput(value.toString(), index.row());
             break;
    }

    emit dataChanged(index, index, QVector<int>() << role);
    return true;
}


void favStatsModel::setList(BaseStats *list){

    beginResetModel();

    if(m_pList)
        m_pList->disconnect(this);

    m_pList = list;

    if(m_pList){

       //load model list data change notification connections
        connect(m_pList, SIGNAL(dataChanged(const int,const int)), this, SLOT(update(const int, const int)));

        connect( m_pList, &BaseStats::preItemAppend, this, [=](){
           const int index = list->m_pfavList.size();
           beginInsertRows(QModelIndex(), index, index);
        });

        connect( m_pList, &BaseStats::postItemAppended, this, [=](){
            endInsertRows();
        });

       connect( m_pList, &BaseStats::preItemRemoved, this, [=](int index){
           beginRemoveRows(QModelIndex(), index, index);
        });

        connect( m_pList, &BaseStats::postItemRemoved, this, [=](){
           endRemoveRows();
        });

    }

    endResetModel();
}

