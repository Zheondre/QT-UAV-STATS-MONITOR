#ifndef BASESTATS_H
#define BASESTATS_H

#include <QObject>

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
            Custom,
            Any
    };

    explicit BaseStats(QObject *parent = nullptr);
     BaseStats(StatsType typ); 
    BaseStats(StatsType type,BaseStats* fl);

    // ~BaseStats(){
     //make sure to destroy all objects in vector
     //m}


    QVector<StatsItem*> getStatItems();
    StatsType getStatsType()const;

    virtual int getSystemUptime();
    virtual int getNumStats();
    //virtual  double getValue(int item);
    //virtual int getTickCount();

    virtual int getValue(int idx) const;
    virtual QString getName(int idx) const;
    virtual QString getUnit(int idx) const;

     void setName(const QString &val, int idx);
     //void setValue(const int val, int idx);
     void setUnit(const QString &val, int idx);
     void setInput(const QString &val, int idx);

    bool getFav(int idx) const;
    bool getForce(int idx) const;
    bool getPlot(int idx) const;

    virtual void setFav(bool val, int idx);
    void setForce(bool val, int idx);
    virtual void setPlot(bool val, int idx);

    void setValue(const int val, bool update, int idx);

    //void setFav(bool val,  bool update, int idx);
    //void setForce(bool val,  bool update, int idx);
    //void setPlot(bool val,  bool update, int idx);

    //void setName(const QString &val,  bool update, int idx);
    //void setInput(const QString &val,  bool update, int idx);
    //void setInput(const QString &val,  bool update, int idx);
    //void setUnit(const QString &val,  bool update, int idx);

    //static bool s_bIncludeFcAir;
public slots:
    void updateFavList(StatsItem *obj, int rowIndex);
    //void removeFav();
    //void addFav();

signals:
    void dataChanged(const int rowIndex, const int modelRole);
    void favChanged(const BaseStats *inst, const int modelRole, const bool val);
    void graphAdded(BaseStats *inst, int rowIndex);
    void graphRemoved(BaseStats *inst, int rowIndex);

protected:
    QVector<StatsItem*> mItems;
    StatsType m_Type;

private:
     //static BaseStats factory(BaseStats::StatsType typ);
BaseStats* m_pfavList;


};


struct StatsItem
{
    BaseStats::StatsType m_Type;

    bool m_bFav;
    bool m_bForce;
    bool m_bPlot;

    QString m_sName;
    int m_nValue;
    QString m_sUnit;
    QString m_sInput;

    int m_npos;

    StatsItem(BaseStats::StatsType type, int idx)  {
        m_Type = type;

        m_bFav = false;
        m_bForce =false;
        m_bPlot = true;

        QString m_sName = "";
        int m_nValue = 0;
        QString m_sUnit= "";
        QString m_sInput= "";

        m_npos = idx;
    };

    StatsItem(int idx){
        m_Type = BaseStats::StatsType::Custom;

        m_bFav = false;
        m_bForce =false;
        m_bPlot = false;

        QString m_sName = "";
        int m_nValue= 0;
        QString m_sUnit= "";
        QString m_sInput= "";

        m_npos = idx;
    };
};
#endif // BASESTATS_H
