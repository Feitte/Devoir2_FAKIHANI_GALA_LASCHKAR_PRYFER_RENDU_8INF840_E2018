#include "stdafx.h"
#include "GrapheSite.h"
#include "Site.h"
#include <queue>
#include <iostream>
#include <unordered_map>

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

GrapheSite::GrapheSite()
{
	nbreSommet =0;
	adj = new list<Site>[nbreSommet];
	listSite = new list<Site>();
	
}



GrapheSite::~GrapheSite()
{
}

GrapheSite* GrapheSite::clone()
{
	return new GrapheSite(*this);
}

long GrapheSite::getNbreSommet()
{
	return nbreSommet;
}

void GrapheSite::addSite(Site a)
{
	listSite->push_back(a);
	nbreSommet++; 
}



void GrapheSite::addOutDegree(Site a, Site b)
{
	a.addOutDegree(b);
	b.addInDegree(a);
	if (!siteExiste(a)) {
		addSite(a);
	}
		
	if (!siteExiste(b)) {
		addSite(b);
	}
		
}

void GrapheSite::removeSite(Site a)
{


	if (siteExiste(a)) {

		list<Site>::iterator itr;

		int i;
		itr = a.outDegree->begin();
		for (i = 0; i < a.getOutDegreeNum(); i++) {
			Site b = *itr;
			++itr;
			removeOutDegree(a, b);
			
		}

		itr = a.inDegree->begin();
		for (i = 0; i < a.getInDegreeNum(); i++) {
			Site b = *itr;
			++itr;
			removeOutDegree(b, a);

		}
		for (itr = listSite->begin(); itr != listSite->end(); advance(itr, 1)) {
			if (itr->getId() == a.getId()) {
				listSite->remove(*itr);
				break;
			}
		}
	}
	



}

void GrapheSite::removeOutDegree(Site a, Site b)
{
	a.delOutDegree(b);
	b.delInDegree(a);
}

void GrapheSite::triTopologique()
{
	long nbSommet = this->nbreSommet;
	// Creation d'un vecteur pour enregistrer les liaisons
	// A l'initialisation, mettre les liaisons à 0
	vector<long> in_degree(nbSommet, 0);
	list<Site>::iterator itrSite;
	list<Site>::iterator itrAdj;

	// Parcourir les listes adjacentes pour mettre à jour les npmbres de liaisons
	for (itrSite = listSite->begin(); itrSite != listSite->end(); advance(itrSite,1))
	{
		
		/*for (itr = itrSite->inDegree->begin(); itr != adj[u].end(); itr++)
			in_degree[itr->getId()]++;*/
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

void GrapheSite::pageRank(int iteration) {

	double d = 0.85;
	double diff = 0.001;
	double dp = 0;

	int i, j, k;
	list<Site>::iterator itr;

	std::unordered_map<int, float> opg;
	std::unordered_map<int, float> npg;

	for (itr = listSite->begin(); itr != listSite->end(); advance(itr, 1)) {
		opg.insert({ itr->getId(), ((float)1 / (float)nbreSommet) });
		cout << opg[itr->getId()] << endl;
	}

	while (iteration > 0) {
		dp = 0;
		for (itr = listSite->begin(); itr != listSite->end(); advance(itr,1)) {
			if (itr->getInDegreeNum() > 0) {
				dp += d * ((double)opg[itr->getId()]/(double)nbreSommet);
			}
		}


		iteration--;
	}

}






