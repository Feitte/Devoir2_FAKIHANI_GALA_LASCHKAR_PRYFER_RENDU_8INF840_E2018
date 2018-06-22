// Exercice 2.cpp : définit le point d'entrée pour l'application console.
//
#include "stdafx.h"
#include <iostream>
#include "GrapheSite.h"

using namespace std;


int main()
{
	GrapheSite g = GrapheSite();
	Site a = Site(0, "Site 0");
	Site b = Site(1, "Site 1");
	Site c = Site(2, "Site 2");
	Site d = Site(3, "Site 3");
	Site e = Site(4, "Site 4");
	Site f = Site(5, "Site 5");
	Site h = Site(6, "Site 6");
	g.addSite(a);
	g.addSite(b);
	
	g.addOutDegree(f, b);
	g.addOutDegree(a, f);
	g.addOutDegree(b, f);
	g.addOutDegree(d, f);
	g.addOutDegree(f, d);
	g.addOutDegree(e, f);
	g.addOutDegree(d, b);
	g.addOutDegree(c, a);
	g.addOutDegree(c, f);
	g.addOutDegree(c, e);

	g.addOutDegree(f, h);

	
	//g.addOutDegree(Site(5, "Site 5"), Site(2, "Site 2"));

	//g.addOutDegree(Site(0, "Site 0"), Site(5, "Site 5"));
	//g.addOutDegree(Site(1, "Site 1"), Site(5, "Site 5"));
	//g.addOutDegree(Site(5, "Site 5"), Site(3, "Site 3"));
	//g.addOutDegree(Site(4, "Site 4"), Site(5, "Site 5"));
	////g.addOutDegree(Site(4, "Site 4"), Site(0, "Site 0"));
	////g.addOutDegree(Site(4, "Site 4"), Site(1, "Site 1"));
	////g.addOutDegree(Site(0, "Site 0"), Site(5, "Site 5"));
	//g.addOutDegree(Site(3, "Site 3"), Site(1, "Site 1"));
	//g.addOutDegree(Site(3, "Site 3"), Site(5, "Site 5"));
	cout << "Tri: " << endl;
	//g.triTopologique();
	g.pageRank(5);

	cout << "Termine";
	
	
	getchar();

	return 0;
}

