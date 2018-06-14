#pragma once
#include <list>
#include "Site.h";

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
	Site *getSiteById(long id);

public:
	GrapheSite(long nbreSommet);
	~GrapheSite();
	void addOutDegree(Site a, Site b);
	void triTopologique();
};

