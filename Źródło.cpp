#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

ofstream file("Huffmann.txt");


int ALFABET[128][2];
string KODY[128];

/**
*	Funkcja sortujaca
*	W sposob nierosnacy
*	Czestotliwosci znakow w alfabecie
**/
void sortuj(int licz){
    for(int j=0; j<127; j++)
        for(int i=0; i<127; i++) {
            if(ALFABET[i][1] > ALFABET[i+1][1]) {
                swap(ALFABET[i][1], ALFABET[i+1][1]);
                swap(ALFABET[i][0], ALFABET[i+1][0]);

            }
        }
}

/**
*	Funkcja wypisujaca czestotliwosci
*	Podanych na wejsciu znakow
**/
void wypisz() {
    cout << "CZESTOTLIWOSC: " << endl;
    file << "CZESTOTLIWOSC: " << endl;
    for(int i=0; i<128; i++)
    {
        if(ALFABET[i][1] != 0)
        {
             cout << (char)ALFABET[i][0] << " - " << ALFABET[i][1] << endl;
            file << (char)ALFABET[i][0] << " - " << ALFABET[i][1] << endl;
        }
    }
        //if(ALFABET[i][1] != 0)
           //cout << (char)ALFABET[i][0] << " - " << ALFABET[i][1] << endl;
            //file << (char)ALFABET[i][0] << " - " << ALFABET[i][1] << endl;
    cout << endl;
    file << endl;
}

/**
*	Funkcja zwracajaca minimalna wartosc
*	tablicy z podanego na wejsciu zakresu
**/
int minimum(int P[], int a, int b, int L[]) {
    int i;
    int min = RAND_MAX, minw = 0;
    for(i=a; i<b; i++) {
        if(P[i] < min && L[i] == 0) {
            min = P[i];
            minw = i;
        }
    }
    return minw;
}

/**
*	Funkcja odwracajaca string podany
*	na wejsciu
**/
string reverse(string t1){
	string t2;
	for(int i=t1.size()-1; i>=0; i--)
		t2 += t1[i];
	return t2;
}

/**
*	Funkcja wykonujaca szyfrowanie Huffmana
*	W sposob tablicowy
**/
void Huffman(int licz) {
    int *L = new int [2*licz-1]{};
    int *P = new int [2*licz-1]{};
    int i;

    for(i=0; i<2*licz-1; i++)
        L[i] = 0;
    for(i=0; i<licz; i++)
        P[i] = ALFABET[i][1];
    int a, b;
    a = 0; b = 1;
    for(int j=0; j<(2*licz-2); j++) {
        if(L[j]==0)
        {
            a = j;
            b = minimum(P, a+1, i, L);
            P[i] = P[a] + P[b];
            P[a] = 0;
            P[b] = 1;
            L[a] = L[b] = i;
            i++;
        }
    }
    int k = 128-licz;
    string kod;
    cout<<endl;
    file<<endl;
    cout<<"KODY SZYFROWE:"<<endl;
    file<<"KODY SZYFROWE:"<<endl;
    for(i=0; i<licz; i++)
    {
        cout <<(char)ALFABET[k][0] <<  " - ";
        file<<(char)ALFABET[k][0] <<  " - ";
        b = ALFABET[k][0];
        a = i;
        while(L[a]!=0)
        {
            if(P[a] == 0) kod+= "0";
            if(P[a] == 1) kod+= "1";
            a = L[a];
        }
        kod = reverse(kod);
        cout << kod << endl;
        file << kod << endl;
        KODY[b] = kod;
        kod="";
        k++;
    }

}

/**
*	Funkcja zliczajaca znaki
*	I wyznaczajaca ich czestotliwosc
**/
void zliczaj(string text) {
    int i, licz=0;
    for(i=0; i<text.size(); i++) {
        int k = (int)text[i];
        ALFABET[k][1]++;
        if(ALFABET[k][1]==1) licz++;
        ALFABET[k][0] = k;
    }
    sortuj(licz);
    wypisz();
    Huffman(licz);
}

/**
*	Funkcja szyfrujaca podany tekst
*	Za pomoca szyfru Huffmana
**/
void szyfruj(string text){
	int K;
    for(int i=0; i<text.size(); i++)
    {
        K = (int)text[i];
        cout << KODY[K];
        file << KODY[K];
    }
}


int main() {
    string text;
    int w;
    string nazwa;
	cout << "Program wykonujacy szyfrowanie Huffmana." << endl;
    file << "Program wykonujacy szyfrowanie Huffmana." << endl;
    cout<<"*********************************************"<<endl;
    file<<"*********************************************"<<endl;
    cout <<"Wczytanie tekstu z klawiatury. "<<endl;
    file <<"Wczytanie tekstu z klawiatury. "<<endl;
	file<<endl;
	cout << "Podaj tekst: " ;
    file << "Podaj tekst: " ;
    cin >> text;
    file<<text;
    cout<<endl;
    file<<endl;
    zliczaj(text);
    cout<<endl;
    file<<endl;
    cout<<"ZASZYFROWANY TEKST:"<<endl;
    file<<"ZASZYFROWANY TEKST:"<<endl;
    szyfruj(text);
    file.close();
    cout<<endl;
    cout<<"************************************************"<<endl;
    cout<<"Dane sa zapisywane do pliku Huffmann.txt!"<<endl;
    cout<<"************************************************"<<endl;
    return 0;
}

