#ifndef FAVSTATSMODEL_H
#define FAVSTATSMODEL_H

#include "statsModel.h"

class favStatsModel : public statsModel
{
public:
    favStatsModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    void setList(BaseStats* l);
};

#endif // FAVSTATSMODEL_H
