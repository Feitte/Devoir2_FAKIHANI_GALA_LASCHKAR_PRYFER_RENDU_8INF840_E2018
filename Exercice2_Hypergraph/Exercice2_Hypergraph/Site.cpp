#include "stdafx.h"
#include "Site.h"
#include <iostream>
using namespace std;

Site::Site()
{
	this->id = 0;
	this->url = "";
	inDegree = new list<Site>();
	outDegree = new list<Site>();
}

Site::Site(long id, string url)
{
	this->id = id;
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
	
	/*list<Site>::iterator *itr ;
	
	for (&itr = outDegree->begin(); *itr != outDegree->end(); ) {
		if ((itr)->getId() == site.getId()) {
			itr = outDegree->erase(itr);
			break;
		}
		++itr;
		
	}*/
		
		
	
}
void Site::delInDegree(Site site)
{

	(*inDegree).remove(site);

	/*list<Site>::iterator *itr;
	
	for (*itr = inDegree->begin(); *itr != inDegree->end(); ) {
		if ((*itr)->getId() == site.getId()) {
			//*itr = inDegree->erase(*itr);
			break;
		}
		++*itr;
	}*/
}


int Site::getOutDegreeNum()
{
	return outDegree->size();
}

int Site::getInDegreeNum()
{
	return inDegree->size();
}




