#pragma once
#include <string>
#include <list>
using namespace std;
class Site
{
public:
	Site();
	Site(long id, string url);
	~Site();
	long getId();
	void setId(long id);
	string getUrl();
	void setUrl(string url);
	bool operator == (Site const& site);

	void addOutDegree(Site site);
	void addInDegree(Site site);

	void delOutDegree(Site site);
	void delInDegree(Site site);

	int getOutDegreeNum();
	int getInDegreeNum();

	list<Site> *outDegree;
	list<Site> *inDegree;


private:
	long id;
	string url;

	
};

