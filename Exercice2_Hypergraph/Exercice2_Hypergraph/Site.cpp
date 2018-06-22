#include "stdafx.h"
#include "Site.h"
#include <iostream>
using namespace std;

Site::Site()
{
	this->id = 0;
	this->nbOutDegree = 0;
	this->url = "";
	inDegree = new list<Site>();
	outDegree = new list<Site>();
}

Site::Site(long id, long nbOutDegree, string url)
{
	this->id = id;
	this->nbOutDegree = nbOutDegree;
	this->url = url;
	inDegree = new list<Site>();
	outDegree = new list<Site>();
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
long Site::getNbOutDegree()
{
	return this->nbOutDegree;
}

void Site::setNbOutDegree(long nbOutDegree)
{
	this->nbOutDegree = nbOutDegree;
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

void Site::addOutDegree(Site site)
{
	

	this->outDegree->push_back(site);
	cout << this->getId() << ": "<< outDegree->size() << endl;
}

void Site::addInDegree(Site site)
{
	this->inDegree->push_back(site);
	cout << this->getId() << ": " << inDegree->size() << endl;
}

void Site::delOutDegree(Site site)
{


	(*outDegree).remove(site);
	

}
void Site::delInDegree(Site site)
{

	(*inDegree).remove(site);

}


int Site::getOutDegreeNum()
{
	return outDegree->size();
}

int Site::getInDegreeNum()
{
	return inDegree->size();
}




