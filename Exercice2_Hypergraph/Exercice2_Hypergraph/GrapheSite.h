#pragma once
#include <list>
#include "Site.h"

using namespace std;

class GrapheSite
{
	//Nombre de sommet
	long nbreSommet;
	//Liste des sommets adjacents
	list<Site> *adj;
	//Liste de tous les sommets
	list<Site> *listSite;
	bool siteExiste(Site currentSite);
	

public:
	GrapheSite();
	~GrapheSite();
	GrapheSite* clone();

	long getNbreSommet();
	Site *getSiteById(long id);

	void addSite(Site a);
	void addOutDegree(Site a, Site b);
	void removeSite(Site a);
	void removeOutDegree(Site a, Site b);

	void triTopologique();
	void pageRank(int iteration);
};

