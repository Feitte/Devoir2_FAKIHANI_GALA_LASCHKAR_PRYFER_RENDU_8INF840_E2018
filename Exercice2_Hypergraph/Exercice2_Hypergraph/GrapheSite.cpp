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

	// Créér une liste de tous les sommets qui n'ont aucun lien
	int nbLien = 0;
	vector <Site> top_order;

	Site temp;
	list<Site>::iterator itr;
	while (top_order.size() < nbreSommet) {

		//temp = *findMinInDegreeList();
		int indegreeTemp = INT_MAX;
		
		
		for (itr = listSite->begin(); itr != listSite->end(); advance(itr, 1)) {
			if ((itr->getInDegreeNum()) < indegreeTemp) {
				cout <<itr->getId()<<": " << itr->getInDegreeNum() <<endl;
				indegreeTemp = itr->getInDegreeNum();
				temp = *itr;
			}
			if (indegreeTemp == 0) {
				break;
			}
		}
		top_order.push_back(temp);
		cout << endl;
		removeSite(temp);
	}

		
	// Afficher
	for (int i = 0; i<top_order.size(); i++)
		cout << top_order[i].getUrl() << endl;
	cout << endl;

}

void GrapheSite::pageRank(int iteration) {

	float d = 0.85;
	float diff = 0.001;
	float dp = 0;

	int i, j, k;
	list<Site>::iterator itr;
	list<Site>::iterator itrInlink;
	std::unordered_map<int, float> opg;
	std::unordered_map<int, float> npg;

	for (itr = listSite->begin(); itr != listSite->end(); advance(itr, 1)) {
		opg.insert({ itr->getId(), ((double)1 / (double)nbreSommet) });
		
	}

	while (iteration > 0) {
		dp = 0;

		for (itr = listSite->begin(); itr != listSite->end(); advance(itr,1)) {
			if (itr->getInDegreeNum() > 0) {
				dp += d * ((float)opg[itr->getId()]/(float)nbreSommet);
			}
		}

		for (itr = listSite->begin(); itr != listSite->end(); advance(itr, 1)) {
			npg.insert({ itr->getId(),dp + (float)(1 - d) / (float)nbreSommet });
			for (itrInlink = itr->inDegree->begin(); itrInlink != itr->inDegree->end(); advance(itrInlink, 1)) {
				npg[itr->getId()] += ((float)d * (float)opg[itrInlink->getId()] / (float)itrInlink->getOutDegreeNum());
			}
		}

		opg = npg;
		iteration--;
	}

	//affichage
	std::unordered_map<int, float>::iterator itrAffi = opg.begin();
	for (int i = 0; i < opg.size(); i++) {
		cout << itrAffi->first << " : " << itrAffi->second << endl;
		advance(itrAffi, 1);
	}
		
		

	


}






