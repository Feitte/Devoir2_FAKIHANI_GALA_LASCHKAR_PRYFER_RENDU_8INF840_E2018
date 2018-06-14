#include "stdafx.h"
#include "GrapheSite.h"
#include "Site.h";
#include <queue>;
#include <iostream>

using namespace std;

bool GrapheSite::siteExiste(Site currentSite)
{
	list<Site>::iterator it = listSite->begin();
	for (long i = 0; i < listSite->size(); i++) {
		if (it->getId() == currentSite.getId())
			return true;
		advance(it, 1);
	}
	return false;
}

Site* GrapheSite::getSiteById(long id)
{
	list<Site>::iterator it = listSite->begin();
	for (long i = 0; i < listSite->size(); i++) {
		if (it->getId() == id)
			return &(*it);
		advance(it, 1);
	}

	return new Site();
}

GrapheSite::GrapheSite(long nbreSommet = 10)
{
	this->nbreSommet = nbreSommet;
	adj = new list<Site>[nbreSommet];
	listSite = new list<Site>();
	
}



GrapheSite::~GrapheSite()
{
}

void GrapheSite::addOutDegree(Site a, Site b)
{
	adj[a.getId()].push_back(b);
	if (!siteExiste(a))
		listSite->push_back(a);
	if (!siteExiste(b))
		listSite->push_back(b);
}

void GrapheSite::triTopologique()
{
	long nbSommet = this->nbreSommet;
	// Creation d'un vecteur pour enregistrer les liaisons
	// A l'initialisation, mettre les liaisons à 0
	vector<long> in_degree(nbSommet, 0);

	// Parcourir les listes adjacentes pour mettre à jour les npmbres de liaisons
	for (int u = 0; u<nbSommet; u++)
	{
		list<Site>::iterator itr;
		for (itr = adj[u].begin(); itr != adj[u].end(); itr++)
			in_degree[itr->getId()]++;
	}

	// Créér une liste de tous les sommets qui n'ont aucun lien
	int nbLien = 0;
	vector <Site> top_order;

	while ( top_order.size() < nbreSommet) {

		queue<Site> q;
		for (int i = 0; i < nbSommet; i++)
			if (in_degree[i] == nbLien)
				q.push(*getSiteById(i));

		// Initialiser un compteur pour les éléments parcourus précédemment
		int cnt = 0;

		// Créér un vecteur pour enregistrer le résultat

		// Parcouris un a un les éléments
		while (!q.empty())
		{
			// Retirer le premier element de la liste 
			Site u = q.front();
			q.pop();
			top_order.push_back(u);

			// Itérer tous les noeuds voisins de l'élément rétirer et supprimer les liaisons de -1
			list<Site>::iterator itr;
			for (itr = adj[u.getId()].begin(); itr != adj[u.getId()].end(); itr++)

				// If in-degree becomes zero, add it to queue
				if (--in_degree[itr->getId()] == nbLien)
					q.push(*itr);

			cnt++;
		}

		
		nbLien++;

	}
	

	

	// Afficher
	for (int i = 0; i<top_order.size(); i++)
		cout << top_order[i].getUrl() << " \n";
	cout << endl;

}
