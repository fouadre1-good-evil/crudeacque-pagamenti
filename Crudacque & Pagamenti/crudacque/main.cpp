#include <iostream>
#include <cstring>
#define MAX 1000
#define MAX_NOME 100
#define ESC 27
#define ENTER 13
#define SU  72
#define DX  77
#define GIU  80
#define SX 75
#define R 114

using namespace std;

struct Archivio () {
    char utente [MAX_NOME];
    char codiceFiscale [16];
    char indirizzo [MAX_NOME];
    double trimestreAttuale;
    double trimestrePrecedente;
    double bolletteNonPagate;
};

Archivio tab [MAX];

int main()
{

}

Archivio inputVendite () {
    Archivio t;
    do {
        cout << "Dimmi il nome e il cognome " << endl;
        cin.getline (t.utente, MAX_NOME);
    } while (strlen(t.utente) == 0);
    do {
        cout << "Dimmi il codice fiscale " << endl;
        cin.getline (t.codiceFiscale, 16);
    } while (strlen(t.codiceFiscale) == 0);
    do {
        cout << "Dimmi l'indirizzo di casa" << endl;
        cin.getline (t.indirizzo, MAX_NOME);
    } while (strlen(t.indirizzo) == 0);
    do {
        cout << "Dimmi la lettura del contatore alla fine del trimestre attuale (in metri cubi)" << endl;
        cin >> t.trimestreAttuale;
    } while (t.trimestreAttuale < 0);
    do {
        cout << "Dimmi la lettura del contatore alla fine del trimestre precedente (in metri cubi)" << endl;
        cin >> t.trimestrePrecedente;
    } while (t.trimestrePrecedente < 0);
    do {
        cout << "Dimmi l'importo di eventuali bollette precedenti non pagate." << endl;
        cin >> t.bolletteNonPagate;
    } while (t.bolletteNonPagate < 0);
    return t;
}

void inputTabella (Archivio tab [], int n, int posAttuale) {
    for (int i = posAttuale; i < n; i++) {
        cout << "Inserisci i dati per l'elemento numero " << i << endl << ":";
        tab[i] = inputVendite ();
    }
}
