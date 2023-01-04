#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <random>
#include <algorithm>
#include "Pixel.h"
using namespace std;

void genererPixels(vector<Pixel>& v);
int menu();
void afficherPixels(vector<Pixel>& v);
void afficherOccurences(vector<Pixel>& v);
void rechercherPixel(vector<Pixel>& v);
void modifierTeinte(vector<Pixel>& v);
void insererPixel(vector<Pixel>& v);

int main()
{
	vector<Pixel> v;
	int choix = -1;
	srand(time(NULL));

	genererPixels(v);
	while (choix != 0)
	{
		choix = menu();
		switch (choix)
		{
		case 1: afficherPixels(v);
			break;
		case 2: afficherOccurences(v);
			break;
		case 3: rechercherPixel(v);
			break;
		case 4: modifierTeinte(v);
			break;
		case 5: insererPixel(v);
			break;
		}
	}
	// fuite de m�moire ici mais ne pas consid�rer pour ce travail
	return 0;
}

int menu()
{
	int choix = -1;

	cout << "*** MENU ***" << endl;
	cout << " 0 - Quitter" << endl;
	cout << " 1 - Afficher les pixels" << endl;
	cout << " 2 - Afficher les occurences" << endl;
	cout << " 3 - Rechercher un pixel" << endl;
	cout << " 4 - Modifier une teinte" << endl;
	cout << " 5 - Inserer un nouveau pixel" << endl;
	cout << " Votre choix? ";

	cin >> choix;
	cout << endl;

	return choix;
}

///////  SECTION A COMPLETER  /////////

/*
	Demande le nombre de pixels
	G�n�rer (au hasard) et ajoute n pixels dans le vecteur
	Consignes
	- Utiliser la m�thode "push_back" pour l'insertion
*/
void genererPixels(vector<Pixel>& v)
{
	int nbrPixel = -1;
	cout << "*** GENERATIONS DES PIXELS ***" << endl;
	cout << "nombre de pixels? ";
	cin >> nbrPixel;
	random_device rd;
	default_random_engine eng(rd());
	uniform_int_distribution<int> distr(0, 255);

	for (int n = 0; n < nbrPixel; ++n)
	{
		v.push_back(Pixel(distr(eng), distr(eng), distr(eng)));
	}

}


/*
	Affiche tous les pixels du vecteur
	Consignes
	- Utiliser un it�rateur constant
	- Ne pas utiliser les op�rateurs []
*/
void afficherPixels(vector<Pixel>& v)
{
	cout << "*** AFFICHER LES PIXELS ***" << endl;
	vector<Pixel>::const_iterator ci;
	for (ci = v.begin(); ci < v.end(); ci++)
	{
		cout << *ci << endl;
	}
}

/*
	Compte et affiche le nombre de couleurs PURES
		(255, 0, 0), (0, 255, 0) et (0, 0, 255)
	Consignes
	- Utiliser un it�rateur constant
	- Ne pas utiliser les op�rateurs []
*/
void afficherOccurences(vector<Pixel>& v)
{
	cout << "*** AFFICHER LES OCCURENCES ***" << endl;
	int nbrRouge = 0;
	int nbrVert = 0;
	int nbrBleu = 0;

	vector<Pixel>::const_iterator ci;
	for (ci = v.begin(); ci < v.end(); ci++)
	{
		if (ci->getRouge() == 255 && ci->getVert() == 0 && ci->getBleu() == 0)
		{
			nbrRouge++;
		}
		if (ci->getRouge() == 0 && ci->getVert() == 255 && ci->getBleu() == 0)
		{
			nbrVert++;
		}
		if (ci->getRouge() == 0 && ci->getVert() == 0 && ci->getBleu() == 255)
		{
			nbrBleu++;
		}
	}
	cout << "nombre de rouges : " << nbrRouge << endl;
	cout << "nombre de verts : " << nbrVert << endl;
	cout << "nombre de bleus : " << nbrBleu << endl;
	cout << endl;
}

/*
	Recherche une couleur en particulier
	On affiche la position de chaque pixel trouv� correspondant � la recherche
	Consignes
	- Ne pas utiliser d'it�rateur
	- Utiliser les op�rateurs []
*/
void rechercherPixel(vector<Pixel>& v)
{
	int rouge, vert, bleu = -1;

	cout << "*** RECHERCHE UN PIXEL ***" << endl;

	cout << "Rouge (0-255) : ";
	cin >> rouge;
	cout << "Vert (0-255) : ";
	cin >> vert;
	cout << "Bleu (0-255) : ";
	cin >> bleu;

	Pixel comp(rouge, vert, bleu);
	auto fit = find(v.begin(), v.end(), comp);

	if (v[fit - v.begin()] == comp)
	{
		cout << "Position du pixel recherche : " << fit - v.begin() << endl;
	}
	else
	{
		cout << "Pixel non trouve !!" << endl;
	}

	cout << endl; 

}

/*
	Choisir une couleur (r/v/b)
	Choisir la quantit� de "couleur" � ajouter
	Pour chaque pixel, ajouter la quantit� de couleur
	Consignes
	- Utiliser un it�rateur (pas constant... �videmment)
	- Ne pas utiliser les op�rateurs []
	- utiliser les m�thodes "ajusterXXX" de l'objet Pixel
*/
void modifierTeinte(vector<Pixel>& v)
{
	char couleur;
	int qtiteCouleur = 0;
	cout << "*** MODIFIER LA TEINTE ***" << endl;

	cout << "Quelle couleur (r/v/b) ? ";
	cin >> couleur; 

	cout << "Modification de couleur ? ";
	cin >> qtiteCouleur;
	switch (couleur)
	{
		case 'r':
			for (auto i : v)
			{
				i.ajusterRouge(qtiteCouleur);
			}
			break;
		case 'v':
			for (auto i : v)
			{
				i.ajusterVert(qtiteCouleur);
			}
			break;
		case 'b':
			for (auto i : v)
			{
				i.ajusterBleu(qtiteCouleur);
			}
			break;
		default:
			cout << "Attention mauvaise entree! " << endl;
			break;

	}

}

/*
	cr�er un pixel
	Choisir une position
	Si la position est superieur � la taille du vecteur
		Ajouter � la fin du vecteur
	Autrement
		D�placer un it�rateur � la bonne position
		Ins�rer le pixel (m�thode insert de vector)
*/
void insererPixel(vector<Pixel>& v)
{
	cout << "*** INSERER UN PIXEL ***" << endl;
	int rouge, vert, bleu = -1;
	int position = -1;
	cout << "Rouge (0-255) : ";
	cin >> rouge;
	cout << "Vert (0-255) : ";
	cin >> vert;
	cout << "Bleu (0-255) : ";
	cin >> bleu;
	cout << "Position 0-" << v.size() << " :";
	cin >> position;
	Pixel nouveau(rouge, vert, bleu);
	if (position > v.size())
	{
		v.push_back(nouveau);
	}
	else if(position < v.size())
	{
		if (position < 0)
		{
			position = 0;
		}
		v.insert(v.begin()+position,nouveau);
	}

}