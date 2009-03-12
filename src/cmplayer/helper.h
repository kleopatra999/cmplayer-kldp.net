#ifndef HELPER_H
#define HELPER_H

class QString;

class Helper {
public:
	~Helper();
	static const QString &configFile();
	static const QString &recentFile();
	static const QString &stateFile();
	static const char *version() {return "0.3.0";}
	static QString mediaExtensionFilter();
private:
	static Helper *get() {static Helper obj; return &obj;}
	struct Data;
	friend struct Data;
	Helper();
	Data *d;
};

#endif