#pragma once
#include <string>

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

private:
	long id;
	string url;
};

