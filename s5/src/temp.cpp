class ballardItem : public QObject{ 

	bool m_bFav; 
	bool m_bForce; 
	bool m_bPlot;

	QString m_sName; 
	QString m_sValue;
	QString m_sUnit;	
	QString m_sInput; 

public:

	ballardItem(QObject *parent): QObject(parent){ 
	
	} 
	
	Q_OBJECT
	
    Q_PROPERTY(QString getName  READ getName  WRITE setName  NOTIFY nameChanged)
	Q_PROPERTY(QString getValue READ getValue WRITE setValue NOTIFY valueChanged)
	Q_PROPERTY(QString getUnit  READ getUnit  WRITE setUnit  NOTIFY UnitChanged)
	Q_PROPERTY(QString getInput READ getInput WRITE setInput NOTIFY inputChanged)
	
	Q_PROPERTY(bool getFav   READ getFav   WRITE setFav  NOTIFY favChanged)
	Q_PROPERTY(bool getForce READ getForce WRITE setForce NOTIFY forceChanged)
	Q_PROPERTY(bool getPlot  READ getPlot  WRITE setPlot  NOTIFY plotChanged)

	QString getName(); 
	QString getValue(); 
	QString getInput();
	QString getUnit();
	
	bool getFav(); 
	bool getForce(); 
	bool getPlot();

	void setName(const QString &name);
	void setValue(const QString &val);
	void setInput(const QString &userinput);	
	void setInput(const QString &unit); 
	
	void setFav(const bool &val); 
	void setForce(const bool &val); 
	void setPlot(const bool &val); 
	
	signals:
	
	void nameChanged(); 
	void valueChanged(); 
	void inputChanged();
	void favChanged(); 
	void forceChanged(); 
	void plotChanged(); 
};

class backEnd : public QObject{ 

	QList<ballardItem *> bItems;

	Q_OBJECT
	Q_PROPERTY(QQmlListProperty<ballardItem> getBItems READ getBItems)
	
	public:
	
	enum sysEnv { 
		MOBILE_IOS, 
		MOBILE_AND, 
		DESKTOP
	};
	enum sysState { 
		DEBUG, 
		TESTING, 
		NODATA, 
		CONNECTED, 
		WARNING, 
		ERROR
	};
	
	QQmlListProperty<ballardItem> bItems();
	
	//initList() // data list came in so load the ballard list
	bool initList() //loads names values to 0, and unts
	bool refreshList() //2 times a second ? //updates value 
	bool removeList(const &int ref); 
};