// Exercice 2.cpp : définit le point d'entrée pour l'application console.
//
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "GrapheSite.h"
#include <string>
using namespace std;
const vector<string> explode(const string& s, const char& c);
int main()
{
	ifstream flux_nodes("eu-2005.nodes.txt", ios::in);
	ifstream flux_edges("eu-2005.edges.txt", ios::in);
	GrapheSite g = GrapheSite();
	if (flux_nodes) 
	{
		string ligne;
		string ligneCourante;
		long id;
		long NbOutDegree;
		getline(flux_nodes, ligne);
		int nbLigne = stoi(ligne);
		getline(flux_nodes, ligne);
		cout << "DEBUT CREATION DE SITE" << endl;
		for (long i = 0; i <= nbLigne; i++) {
			cout << "CREATION DE SITE" <<i << endl;
			getline(flux_nodes, ligne);
			ligneCourante = ligne;
			vector<string> v{ explode(ligneCourante, ' ') };
			int id = stoi(v[0]);
			int NbOutDegree = stoi(v[1]);
			string url = v[2];
			g.addSite(Site(id, NbOutDegree, url));
		}
		cout << "FIN CREATION DES NOEUDS" << endl;
		flux_nodes.close();
	}
	else 
		cerr << "Impossible d'ouvrir le fichier !" << endl;

	if (flux_edges)  
	{  
		long id1;
		long id2;
		string ligne_edges;
		string ligneCourante_edges;
		getline(flux_edges, ligne_edges);
		int nbLigne_edges = stoi(ligne_edges);
		cout << "nbLigne" << nbLigne_edges << endl;
		getline(flux_edges, ligne_edges);
		for (long i = 0; i <= nbLigne_edges; i++) {
			getline(flux_edges, ligne_edges);
			ligneCourante_edges = ligne_edges;
			vector<string> v{ explode(ligneCourante_edges, ' ') };
			int id1 = stoi(v[0]);
			int id2 = stoi(v[1]);
			g.addOutDegree(g.getSiteById(id1),g.getSiteById(id2));
			cout << "Arc ajouté " << endl;
		}
		cout << "FIN CREATION DES ARCS" << endl;
		flux_edges.close();
	}
	else
		cerr << "Impossible d'ouvrir le fichier !" << endl;





	//Début Tri Topologique

	cout << "Début du PageRank avec 50 itérations" << endl;
	g.pageRank(50);
	cout << "Fin du PageRank" << endl<<endl;


	cout << "Début du Tri Topologique" << endl;
	g.triTopologique();
	cout << "Fin du Tri Topologique" << endl;

	//Début Tri Topologique

	
	//g.triTopologique();
	cout << "Termine";
	
	
	getchar();

	return 0;
}

const vector<string> explode(const string& s, const char& c)
{
	string buff{ "" };
	vector<string> v;

	for (auto n : s)
	{
		if (n != c) buff += n; else
			if (n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if (buff != "") v.push_back(buff);

	return v;
}