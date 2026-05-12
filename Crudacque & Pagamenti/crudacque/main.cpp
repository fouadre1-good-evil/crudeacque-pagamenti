#include <iostream>
#include <cstring>
#include <fstream>
#include <conio.h>
#include <windows.h>
#define MAX 500
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
Archivio inputVendite ();

void inputStringa (int maxval, char mex[], char s[]);
void inputTabella (Archivio tab [], int &n, int posAttuale);
void creaFile (int &n);
void modificaMenu(Archivio &t);
void gotoXY(int x, int y);
void graficaMenu (Archivio t, int b, int bp, bool inserimento);
void hideCursor();
void showCursor();
void menu(int &n);

int lunghezzaNumero(double n);
int inputInteroSenzaMax (int min, char mex[]);
int inputIntero (int min, int max, char mex[]);

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    system("color B0");
    int n;
    menu(n);


    Archivio t;
    strcpy (tab[0].utente, "PROVA");
    strcpy (tab[0].codiceFiscale, "87GF43FD5GF");
    strcpy (tab[0].indirizzo, "Via degli uccelli 67");
    tab[0].trimestreAttuale = 100;
    tab[0].trimestrePrecedente = 200;
    tab[0].bolletteNonPagate = 84.6;
    t = tab[0];
    modificaMenu(t);
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

int inputIntero (int min, int max, char mex[]) {
    int n;
    do {
        cout << mex;
        cin >> n;
    } while (n < min || n >= max);
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
    n = inputIntero (0, MAX, "Quanti utenze totali ci sono, massimo 500");
    for (int i = posAttuale; i < n; i++) {
        cout << "Inserisci i dati per l'utente numero " << i << endl << ":";
        tab[i] = inputVendite ();
    }
}

void creaFile (int &n) {
    ofstream fTrimestre;
    fTrimestre.open("TRIMESTRE.bin", ios::binary);
    if (!fTrimestre.is_open()) {
        perror ("Errore nell'apertura del file: ");
    }
    fTrimestre.close();
}

void menu(int &n) {
    int i=0;
    int ip;
    bool inMenu = true;
    while (inMenu) {
        hideCursor();
        gotoXY(1,1);
        cout << "Selezione come vuoi procedere. Usa le frecce SU/GIU e premi INVIO.\n";
        gotoXY(1,2);
        cout << "Premi ESC per uscire.\n\n";
        gotoXY(2,3);
        cout << "┌───────────────────────────┐";
        for (int i=0; i<4; i++) {
            gotoXY(2,4+i);
            cout << "│";
            gotoXY(30, 4+i);
            cout << "│";
        }
        gotoXY(2,8);
        cout << "└───────────────────────────┘";
        gotoXY(3,4);
        cout << "- ";
        if (i == 0) {
            SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        }
        gotoXY(5,4);
        cout << "Inserire un nuovo utente";
        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        gotoXY(3,5);
        cout << "- ";
        if (i == 1) {
            SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        }
        gotoXY(5,5);
        cout << "Modificare un utente";
        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        gotoXY(3,6);
        cout << "- ";
        if (i == 2) {
            SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        }
        gotoXY(5,6);
        cout << "Cancellare un utente";
        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        gotoXY(3,7);
        cout << "- ";
        if (i == 3) {
            SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        }
        gotoXY(5,7);
        cout << "Visualizzare gli utenti";
        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);

        gotoXY(0,ip+4);
        cout << "  ";
        gotoXY(0,i+4);
        cout <<"->";

        ip = i;
        char tasto = _getch();
        if (tasto == ESC) {
            inMenu = false;
        }
        if (tasto == SU) {
            if(i == 0) {
                i = 3;
            } else {
                i-=1;
            }
        }
        if (tasto == GIU) {
            if(i == 3) {
                i = 0;
            } else {
                i+=1;
            }
        }
        if (tasto == ENTER) {
            cin.sync();
            showCursor();
            system("cls");
            switch (scelta) {
            case 0:
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            default:
                break;
            }

    }
}

/*
QUESTA PARTE VA NEL MENU, DA COPIARE E INCOLLARE
    Archivio t;
    f.seekg((posizione-1)*sizeof(Archivio), ios::beg);
    f.read((char *)&t, sizeof(Archivio));
    modificaMenu(t)
    f.seekp((-1)*sizeof(Archivio), ios::cur);
    f.write((char *)&t, sizeof(Archivio));

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

void modificaMenu(Archivio &t) {
    int b = 4;
    int bp = b;
    bool inMenu = true;
    while (inMenu) {
        hideCursor();
        graficaMenu(t, b, bp, false);
        bp = b;
        char tasto = _getch();
        if (tasto == ESC) {
            inMenu = false;
        }
        if (tasto == SU) {
            if(b == 4) {
                b = 9;
            } else {
                b-=1;
            }
        }
        if (tasto == GIU) {
            if(b == 9) {
                b = 4;
            } else {
                b+=1;
            }
        }
        if (tasto == ENTER) {
            cin.sync();
            showCursor();
            system("cls");
            switch (b) {
            case 4:
                strcpy (t.utente, "");
                graficaMenu(t, b, bp, true);
                gotoXY(2, 10);
                cout << endl;
                cout << "Inserisci il nuovo utente";
                gotoXY(13, 4);
                inputStringa(MAX_NOME, "", t.utente);
                break;
            case 5:
                strcpy (t.codiceFiscale, "");
                graficaMenu(t, b, bp, true);
                gotoXY(2, 10);
                cout << endl;
                cout << "Inserisci il nuovo Codice Fiscale";
                gotoXY(21, 5);
                inputStringa(16, "", t.codiceFiscale);
                break;
            case 6:
                strcpy (t.indirizzo, "");
                graficaMenu(t, b, bp, true);
                gotoXY(2, 10);
                cout << endl;
                cout << "Inserisci il nuovo indirizzo";
                gotoXY(16, 6);
                inputStringa(MAX_NOME, "", t.indirizzo);
                break;
            case 7:
                graficaMenu(t, b, bp, true);
                for (int i=0; i<lunghezzaNumero(t.trimestreAttuale)+3; i++) { // Quel +3 è per far cancellare anche il " mq"
                    gotoXY(36+i, 7);
                    cout << " ";
                }
                gotoXY(2, 10);
                cout << endl;
                cout << "Nuova lettura attuale (mq)";
                gotoXY(36, 7);
                t.trimestreAttuale = inputInteroSenzaMax(0, "");
                break;
            case 8:
                graficaMenu(t, b, bp, true);
                for (int i=0; i<lunghezzaNumero(t.trimestrePrecedente)+3; i++) { // Quel +3 è per far cancellare anche il " mq"
                    gotoXY(39+i, 8);
                    cout << " ";
                }
                gotoXY(2, 10);
                cout << endl;
                cout << "Nuova lettura precedente (mq)";
                gotoXY(39, 8);
                t.trimestrePrecedente = inputInteroSenzaMax(0, "");
                break;
            case 9:
                graficaMenu(t, b, bp, true);
                for (int i=0; i<lunghezzaNumero(t.bolletteNonPagate)+5; i++) { // Quel +5 è per far cancellare anche il " euro"
                    gotoXY(40+i, 9);
                    cout << " ";
                }
                gotoXY(2, 10);
                cout << endl;
                cout << "Nuovo importo bollette (euro)";
                gotoXY(40, 9);
                t.bolletteNonPagate = inputInteroSenzaMax(0, "");
                break;
            }
        }
    }
}

void graficaMenu (Archivio t, int b, int bp, bool inserimento) {
    gotoXY(1,1);
    cout << "Cosa vuoi modificare? Usa le frecce SU/GIU e premi INVIO.\n";
    gotoXY(1,2);
    cout << "Premi ESC per uscire.\n\n";
    //Calcolo della lunghezza di ogni singola riga
    int lunghezze[6];
    lunghezze[0] = 5  + strlen(t.utente);
    lunghezze[1] = 13 + strlen(t.codiceFiscale);
    lunghezze[2] = 8  + strlen(t.indirizzo);
    lunghezze[3] = 31 + lunghezzaNumero(t.trimestreAttuale);
    lunghezze[4] = 34 + lunghezzaNumero(t.trimestrePrecedente);
    lunghezze[5] = 37 + lunghezzaNumero(t.bolletteNonPagate);

    //Trovo qualle piu grande
    int maxLen = lunghezze[0];
    for (int i = 1; i < 6; i++) {
        if (lunghezze[i] > maxLen) {
            maxLen = lunghezze[i];
        }
    }
    gotoXY(2,3);
    cout << "┌";
    for(int j = 0; j < maxLen + 6; j++) {
        cout << "─";
    }
    cout << "┐\n";

    for (int i = 0; i < 6; i++) {
        gotoXY(2,4+i);
        cout << "│";

        if (i == 0) {
            gotoXY(3,4);
            cout << "- ";
            if (b == 4) {
                SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            }
            gotoXY(5,4);
            cout << "Utente: " << t.utente << "";
            SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        } else if (i == 1) {
            gotoXY(3,5);
            cout << "- ";
            if (b == 5) {
                SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            }
            gotoXY(5,5);
            cout << "Codice Fiscale: " << t.codiceFiscale << "";
            SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        } else if (i == 2) {
            gotoXY(3,6);
            cout << "- ";
            if (b == 6) {
                SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            }
            gotoXY(5,6);
            cout << "Indirizzo: " << t.indirizzo << "";
            SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        } else if (i == 3) {
            gotoXY(3,7);
            cout << "- ";
            if (b == 7) {
                SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            }
            gotoXY(5,7);
            cout << "Lettura del trimestre attuale: " << t.trimestreAttuale << " mq";
            SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        } else if (i == 4) {
            gotoXY(3,8);
            cout << "- ";
            if (b == 8) {
                SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            }
            gotoXY(5,8);
            cout << "Lettura del trimestre precedente: " << t.trimestrePrecedente << " mq";
            SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        } else if (i == 5) {
            gotoXY(3,9);
            cout << "- ";
            if (b == 9) {
                SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            }
            gotoXY(5,9);
            cout << "Importo delle bollette non pagate: " << t.bolletteNonPagate << " euro";
            SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        }

        int spaziMancanti = maxLen - lunghezze[i];
        for(int j = 0; j < spaziMancanti; j++) {
            cout << " ";
        }
        if (!inserimento) {
            cout << " │\n";
        }

    }
    gotoXY(0,bp);
    cout << "  ";
    gotoXY(0,b);
    cout <<"->";
    gotoXY(2,10);
    cout << "└";
    for(int j = 0; j < maxLen + 6; j++) {
        cout << "─";
    }
    cout << "┘\n";
}

void gotoXY(int x, int y) {
    COORD coordinate;
    coordinate.X = x;
    coordinate.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
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
