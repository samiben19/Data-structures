#pragma once

#define NULL_TELEM -1
typedef int TElem;

class IteratorMultime;

class Multime {
	friend class IteratorMultime;

    private:
		/* aici e reprezentarea */
		int cap;		// capacitatea
		int lg;			// numarul de elemente din multime
		TElem* e;		// vectorul dimamic care retine elementele multimii
		int* urm;		// vectorul dimanic de legaturi

		int prim;		// pozitia primului element din multime
		int primLiber;	// pozitia primului element liber din multime

		int aloca();									// Theta(1)					Best case = Worst case = Average case = Theta(1)
		void dealoca(int i);							// Theta(1)					Best case = Worst case = Average case = Theta(1)
		int creeazaNod(TElem e);						// Theta(1)	amortizat		Best case = Worst case = Average case = Theta(1)
		void redim();									// Theta(n)					Best case = Worst case = Average case = Theta(n) unde n nr de elemente din multime
    public:
 		//constructorul implicit
		Multime();										// Theta(1)			Best case = Worst case = Average case = Theta(1)

		//adauga un element in multime
		//returneaza adevarat daca elementul a fost adaugat (nu exista deja in multime)
		bool adauga(TElem e);							// O(n)	amortizat	Best case:		Theta(1)	- daca TElem e exista deja pe prima pozitie
														//					Worst case:		Theta(n)	- daca TElem e nu exista
														//					Average case:	Theta(n)	= (1 + 2 + 3 +..+ n)/n = (n+1)/2

		//sterge un element din multime
		//returneaza adevarat daca elementul a existat si a fost sters
		bool sterge(TElem e);							// O(n)				Best case:		Theta(1)	- daca TElem e exista deja pe prima pozitie
														//					Worst case:		Theta(n)	- daca TElem e nu exista
														//					Average case:	Theta(n)	= (1 + 2 + 3 +..+ n)/n = (n+1)/2

		//verifica daca un element se afla in multime
		bool cauta(TElem elem) const;					// O(n)				Best case:		Theta(1)	- daca TElem elem exista deja pe prima pozitie
														//					Worst case:		Theta(n)	- daca TElem elem nu exista
														//					Average case:	Theta(n)	= (1 + 2 + 3 +..+ n)/n = (n+1)/2

		//intoarce numarul de elemente din multime;
		int dim() const;								// Theta(1)			Best case = Worst case = Average case = Theta(1)

		//verifica daca multimea e vida;
		bool vida() const;								// Theta(1)			Best case = Worst case = Average case = Theta(1)

		//returneaza un iterator pe multime
		IteratorMultime iterator() const;				// Theta(1)			Best case = Worst case = Average case = Theta(1)

		// destructorul multimii
		~Multime();										// Theta(1)			Best case = Worst case = Average case = Theta(1)

		// adauga toate elementele din multimea b in multimea curenta 
		void reuniune(const Multime& b);
		/*
		* Complexitate:	Best case = Worst case = Average case = Theta(m) unde m este nr de elemente din multime
		* preconditii:	m apartine Multime,
		*				b apartine Multime
		* postconditii: m' = m reunit b
		*
		SubAlgoritm reuniune(m,b)
			curentB <- b.prim
			CatTimp curentB <> -1 executa
				[m].adauga(b.e[curentB])
				curentB <- b.urm[curentB]
			sf_catTimp
		sf_subAlg
		*/
};




