#include <iostream>
#include <cstring>
#include <fstream>
#include <conio.h>
#include <windows.h>
#define MAX 300
#define MAX_NOME 120
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

//Prototipi
void inputStringa (int maxval, char mex[], char s[]);
int inputInteroSenzaMax (int min, char mex[]);
Archivio inputVendite ();
void inputTabella (Archivio tab [], int &n, int posAttuale);
void creaFile (int &n);
int lunghezzaNumero(double n);
void menuModificaUI(Archivio &t);

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    /*
    USATA PER FARE PROVE PER LA MODIFICA
    Archivio t;
    strcpy (tab[0].utente, "LAFORESTADICAZZIVOLANTINELLONELLONELLONELLONELLONELLO");
    strcpy (tab[0].codiceFiscale, "87GF43FD5GF");
    strcpy (tab[0].indirizzo, "Via degli uccelli 67");
    tab[0].trimestreAttuale = 100;
    tab[0].trimestrePrecedente = 200;
    tab[0].bolletteNonPagate = 84.6;
    t = tab[0];
    menuModificaUI(t);
    */
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
    inputStringa (MAX_NOME, "Dimmi il nome e il cognome ", t.utente);
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

/*
QUESTA PARTE VA NEL MENU, DA COPIARE E INCOLLARE
void modifica(fstream &fTrimestre, int posizione) {
    Archivio t;
    f.seekg((posizione-1)*sizeof(Archivio), ios::beg);
    f.read((char *)&t, sizeof(Archivio));
    menuModificaUI(t)
    f.seekp((-1)*sizeof(Archivio), ios::cur);
    f.write((char *)&t, sizeof(Archivio));

}
*/

int lunghezzaNumero(double n) {
    int len = 0;
    int intero = (int)n;

    if (intero == 0) {
        len = 1;
    } else {
        int temp = intero;
        while (temp > 0) {
            len++;
            temp /= 10;
        }
    }

    if (n - intero > 0) {
        len += 2;
    }
    return len;
}

void menuModificaUI(Archivio &t) {

    int scelta = 0;
    bool inMenu = true;

    while (inMenu) {
        system("cls");
        cout << "Cosa vuoi modificare? Usa le frecce SU/GIU e premi INVIO.\n";
        cout << "Premi ESC per uscire.\n\n";

        //Calcolo della lunghezza di ogni singola riga
        int lunghezze[6];
        lunghezze[0] = 12 + strlen(t.utente);
        lunghezze[1] = 20 + strlen(t.codiceFiscale);
        lunghezze[2] = 15 + strlen(t.indirizzo);
        lunghezze[3] = 38 + lunghezzaNumero(t.trimestreAttuale);
        lunghezze[4] = 41 + lunghezzaNumero(t.trimestrePrecedente);
        lunghezze[5] = 44 + lunghezzaNumero(t.bolletteNonPagate);

        //Trovo qualle piu grande
        int maxLen = lunghezze[0];
        for (int i = 1; i < 6; i++) {
            if (lunghezze[i] > maxLen) {
                maxLen = lunghezze[i];
            }
        }

        cout << "┌";
        for(int j = 0; j < maxLen + 6; j++) {
            cout << "─";
        }
        cout << "┐\n";

        for (int i = 0; i < 6; i++) {
            cout << "│ ";

            if (i == scelta) {
                cout << "─>  ";
            } else {
                cout << "    ";
            }

            if (i == 0) {
                cout << "- Utente: [" << t.utente << "]";
            } else if (i == 1) {
                cout << "- Codice Fiscale: [" << t.codiceFiscale << "]";
            } else if (i == 2) {
                cout << "- Indirizzo: [" << t.indirizzo << "]";
            } else if (i == 3) {
                cout << "- Lettura del trimestre attuale: [" << t.trimestreAttuale << "] mq";
            } else if (i == 4) {
                cout << "- Lettura del trimestre precedente: [" << t.trimestrePrecedente << "] mq";
            } else if (i == 5) {
                cout << "- Importo delle bollette non pagate: [" << t.bolletteNonPagate << "] euro";
            }

            int spaziMancanti = maxLen - lunghezze[i];
            for(int j = 0; j < spaziMancanti; j++) {
                cout << " ";
            }
            cout << " │\n";
        }

        cout << "└";
        for(int j = 0; j < maxLen + 6; j++) {
            cout << "─";
        }
        cout << "┘\n";

        char tasto = _getch();

        if (tasto == ESC) {
            inMenu = false;
        } else if (tasto == -32 || tasto == 224) {
            tasto = _getch();
            if (tasto == SU && scelta > 0) {
                scelta--;
            }
            if (tasto == GIU && scelta < 5) {
                scelta++;
            }
        }
        else if (tasto == ENTER) {
            system("cls");
            cin.sync();
            switch (scelta) {
                case 0:
                    inputStringa(MAX_NOME, "Inserisci il nuovo utente: ", t.utente);
                    break;
                case 1:
                    inputStringa(16, "Inserisci il nuovo CF: ", t.codiceFiscale);
                    break;
                case 2:
                    inputStringa(MAX_NOME, "Inserisci il nuovo indirizzo: ", t.indirizzo);
                    break;
                case 3:
                    t.trimestreAttuale = inputInteroSenzaMax(0, "Nuova lettura attuale (mq): ");
                    break;
                case 4:
                    t.trimestrePrecedente = inputInteroSenzaMax(0, "Nuova lettura precedente (mq): ");
                    break;
                case 5:
                    t.bolletteNonPagate = inputInteroSenzaMax(0, "Nuovo importo bollette (euro): ");
                    break;
            }
        }
    }
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
