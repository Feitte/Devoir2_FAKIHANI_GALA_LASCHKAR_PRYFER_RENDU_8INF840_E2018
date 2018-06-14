#include "stdafx.h"
#include "Site.h"

using namespace std;

Site::Site()
{
	this->id = 0;
	this->url = "";
}

Site::Site(long id, string url)
{
	this->id = id;
	this->url = url;
}

Site::~Site()
{
}

long Site::getId()
{
	return this->id;
}



void Site::setId(long id)
{
	this->id = id;
}

string Site::getUrl()
{
	return this->url;
}

void Site::setUrl(string url)
{
	this->url = url;
}

bool Site::operator==(Site const & site)
{
	return id == site.id;
}



