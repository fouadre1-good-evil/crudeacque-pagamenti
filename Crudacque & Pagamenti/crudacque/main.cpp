#include <iostream>
#include <cstring>
#include <fstream>
#define MAX 300
#define MAX_NOME 100
#define ESC 27
#define ENTER 13
#define SU  72
#define DX  77
#define GIU  80
#define SX 75
#define R 114

using namespace std;

struct Archivio {
    char utente [MAX_NOME];
    char codiceFiscale [16];
    char indirizzo [MAX_NOME];
    double trimestreAttuale;
    double trimestrePrecedente;
    double bolletteNonPagate;
};

Archivio tab [MAX];
strcpy (tab[0].utente, "Rossi")
strcpy (tab[0].utente, "87GF43FD5GF")
strcpy (tab[0].utente, "Via degli uccelli 67");
tab[0].trimestreAttuale = 100;
tab[0].trimestreAttuale = 200;
tab[0].trimestreAttuale = 84.6;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void inputStringa (int maxval, char mex[], char s[]) {
    do {
        cout << mex;
        cin.getline (s, maxval);
    } while (strlen(s) == 0);
}

int inputInteroSenzaMax (int min, char mex[]) {
    int n;
    do {
        cout << mex;
        cin >> n;
    } while (n < min);
    return n;
}

Archivio inputVendite () {
    Archivio t;
    inputStringa (, "Dimmi il nome e il cognome ", t.utente);
    inputStringa (16, "Dimmi il codice fiscale ", t.codiceFiscale);
    inputStringa (MAX_NOME, "Dimmi l'indirizzo di casa ", t.indirizzo);
    t.trimestreAttuale = inputInteroSenzaMax (0, "Dimmi la lettura del contatore alla fine del trimestre attuale (in metri cubi)");
    t.trimestrePrecedente = inputInteroSenzaMax(0, "Dimmi la lettura del contatore alla fine del trimestre precedente (in metri cubi)");
    t.bolletteNonPagate = inputInteroSenzaMax(0, "Dimmi l'importo di eventuali bollette precedenti non pagate.");
    return t;
}

void inputTabella (Archivio tab [], int &n, int posAttuale) {
    for (int i = posAttuale; i < n; i++) {
        cout << "Inserisci i dati per l'elemento numero " << i << endl << ":";
        tab[i] = inputVendite ();
    }
}

void creaFile (int &n) {
    ofstream fTrimestre;
    fTrimestre.open("TRIMESTRE.bin", ios::binary);
    if (!fTrimestre.is_open()) {
        perror ("Errore nell'apertura del file: ");
    } else {
        for (int i=0; i<n; i++) {
            fTrimestre.write((char *)&tab[i], sizeof(Archivio));
        }
    }
    fTrimestre.close();
}

void modifica(fstream &fTrimestre, int posizione) {
    Archivio t;
    f.seekg((posizione-1)*sizeof(Archivio), ios::beg); //Rileggo il record di cui voglio modificare
    f.read((char *)&t, sizeof(Archivio));



    f.seekp((-1)*sizeof(Libro), ios::cur); //Si posizione alla posizione corrente
    f.write((char *)&lib, sizeof(Libro));

}

void hideCursor () {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(console, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(console, &cursorInfo);
}

void showCursor() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(console, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(console, &cursorInfo);
}
