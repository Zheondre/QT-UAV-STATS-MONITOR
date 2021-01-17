#ifndef BASESTATS_H
#define BASESTATS_H

#include <QObject>
#include <QVector>
struct StatsItem;

class BaseStats: public QObject
{
    Q_OBJECT
public:

    enum {
        FCSTAT_FAV = Qt::UserRole,
        FCSTAT_PLOT,
        FCSTAT_NAME,
        FCSTAT_VALUE,
        FCSTAT_UNIT,
        FCSTAT_FORCE,
        FCSTAT_UINPUT
    };

    enum StatsType {
        Sofc,
        Rws,
        FcAir,
        BMS,
        FcDiags,
        Custom
    };

    explicit BaseStats(QObject *parent = nullptr);
    BaseStats(StatsType typ);

    // ~BaseStats(){
    //make sure to destroy all objects in vector
    //m}

    virtual void deserialize(QString Data);
    static QVector<StatsItem*> m_pfavList;

    QVector<StatsItem*> getStatItems();
    StatsType getStatsType()const;

    virtual int getSystemUptime();
    virtual int getNumStats();
    //virtual  double getValue(int item);
    //virtual int getTickCount();

    virtual int getFavValue(int idx) const;
    virtual QString getFavName(int idx) const;
    virtual QString getFavUnit(int idx) const;

    void setFavInput(const QString &val, int idx);

    bool getFavFav(int idx) const;
    bool getFavForce(int idx) const;
    bool getFavPlot(int idx) const;

    void setFavFav(bool val, int idx);
    void setFavForce(bool val, int idx);
    void setFavPlot(bool val, int idx);

    void setFavValue(const int val, bool update, int idx);

    int getValue(int idx) const;
    virtual QString getName(int idx) const;
    virtual QString getUnit(int idx) const;

    void setInput(const QString &val, int idx);

    bool getFav(int idx) const;
    bool getForce(int idx) const;
    bool getPlot(int idx) const;

    virtual void setFav(bool val, int idx);
    virtual void setForce(bool val, int idx);
    void setPlot(bool val, int idx);

    void setValue(const int val, bool update, int idx);

public slots:
    void updateFavList(StatsItem *obj, int rowIndex);

signals:
    void sendForceCommand(const QString &result);
    void preItemAppend();
    void postItemAppended();
    void preItemRemoved(int index);
    void postItemRemoved();

    void dataChanged(const int rowIndex, const int modelRole);
    void favChanged(const BaseStats *inst, const int modelRole, const bool val);
    void graphAdded(BaseStats *inst, int rowIndex);
    void graphRemoved(BaseStats *inst, int rowIndex);

protected:
    QVector<StatsItem*> mItems;
    StatsType m_Type;

private:

};

struct StatsItem {

    BaseStats::StatsType m_Type;

    bool m_bFav;
    bool m_bForce;
    bool m_bPlot;

    int m_nValue;
    int m_npos;
    QString m_sInput;

    StatsItem(BaseStats::StatsType type, int idx)  {
        m_Type = type;

        m_bFav = false;
        m_bForce =false;
        m_bPlot = true;

        int m_nValue = 0;
        QString m_sInput= "";

        m_npos = idx;
    };
};

struct CustomItem : StatsItem
{
    QString m_sName;
    QString m_sUnit;

    CustomItem(int idx) : StatsItem(BaseStats::StatsType::Custom, idx) {
        QString m_sUnit= "";
        QString m_sInput= "";
    };

};
#endif // BASESTATS_H
