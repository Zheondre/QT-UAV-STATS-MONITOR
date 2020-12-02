#ifndef FCSTATSMODEL_H
#define FCSTATSMODEL_H

#include <QAbstractListModel>
//#include "statslist.h"
#include "basestats.h"
//#include "C:\Source\QT\s5\src\FcAir\fcairstats.h"

class statsModel : public QAbstractListModel
{
    Q_OBJECT
    //Q_PROPERTY(StatsList *list READ getList WRITE setList)
    Q_PROPERTY(BaseStats *list READ getList WRITE setList)

    BaseStats *m_pList;

public:
    explicit statsModel(QObject *parent = nullptr);

    enum {
     FCSTAT_FAV = Qt::UserRole,
     FCSTAT_PLOT,
     FCSTAT_NAME,
     FCSTAT_VALUE,
     FCSTAT_UNIT,
     FCSTAT_FORCE,
     FCSTAT_UINPUT
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    BaseStats *getList() const;
    void setList(BaseStats *list);

    public slots:
        void update(const int, const int);

};

#endif // FCSTATSMODEL_H
