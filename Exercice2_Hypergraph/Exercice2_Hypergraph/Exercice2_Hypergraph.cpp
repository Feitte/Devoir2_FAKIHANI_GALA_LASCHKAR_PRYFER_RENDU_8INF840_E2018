// Exercice 2.cpp : définit le point d'entrée pour l'application console.
//
#include "stdafx.h"
#include <iostream>
#include "GrapheSite.h"

using namespace std;


int main()
{
	GrapheSite g(6);
	g.addOutDegree(Site(5, "Site 5"), Site(2, "Site 2"));

	g.addOutDegree(Site(0, "Site 0"), Site(5, "Site 5"));
	g.addOutDegree(Site(1, "Site 1"), Site(5, "Site 5"));
	g.addOutDegree(Site(5, "Site 5"), Site(3, "Site 3"));
	g.addOutDegree(Site(4, "Site 4"), Site(5, "Site 5"));
	//g.addOutDegree(Site(4, "Site 4"), Site(0, "Site 0"));
	//g.addOutDegree(Site(4, "Site 4"), Site(1, "Site 1"));
	//g.addOutDegree(Site(0, "Site 0"), Site(5, "Site 5"));
	g.addOutDegree(Site(3, "Site 3"), Site(1, "Site 1"));
	g.addOutDegree(Site(3, "Site 3"), Site(5, "Site 5"));
	cout << "Tri: \n";
	g.triTopologique();
	cout << "Termine";
	cin.get();
	return 0;
}

