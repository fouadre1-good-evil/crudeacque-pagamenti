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
    bool attivo = false;
};

Archivio tab [MAX];
Archivio inputArchivio ();
Archivio Cancellare;

void inputStringa (int maxval, char mex[], char s[], int x, int &y);
void inputTabella (Archivio tab [], int &posAttuale);
void creaFile ();
void modificaMenu(Archivio &t);
void gotoXY(int x, int y);
void graficaMenu (Archivio t, int b, int bp, bool inserimento);
void hideCursor();
void showCursor();
void menu(int &n);
void cancellaUtente(int &posAttuale,int &contanti,fstream &fTrimestre);
void visuallizzaUtenti(int posAttuale,fstream &fTrimestre);

int lunghezzaNumero(double n);
int inputInteroSenzaMax (int min, char mex[], int x, int &y);
int inputIntero (int min, int max, char mex[]);

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

int main() {
    //keybd_event(VK_MENU, 0x36,0,0);                  // ---------|
    //keybd_event(VK_RETURN, 0x1c,0,0);                //          | ------> Per mettere lo
    //keybd_event(VK_RETURN, 0x1c,KEYEVENTF_KEYUP,0);  //          | ------> schermo intero all'avvio
    //keybd_event(VK_MENU, 0x38,KEYEVENTF_KEYUP,0);    // ---------|
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    system("color B0");
    ifstream fLettura("TRIMESTRE.bin", ios::binary | ios::ate);
    int posAttuale = 0;
    if (!fLettura.is_open()) {
        creaFile();
    } else {
        long dimensioneFile = fLettura.tellg();
        posAttuale = dimensioneFile / sizeof(Archivio);
        fLettura.seekg(0, ios::beg);
        for (int i = 0; i < posAttuale; i++) {
            fLettura.read((char *)&tab[i], sizeof(Archivio));
        }
        fLettura.close();
    }
    system("cls");
    menu(posAttuale);
}

void inputStringa (int maxval, char mex[], char s[], int x, int &y) {
    do {
        y++;
        gotoXY(x, y);
        cout << mex;
        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
        }
        cin.getline (s, maxval);
        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    } while (strlen(s) == 0 || strlen(s) > maxval);
}

int inputInteroSenzaMax (int min, char mex[], int x, int &y) {
    int n;
    bool valido = false;
    do {
        y++;
        gotoXY(x, y);
        cout << mex;
        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        if (!(cin >> n)) {
            cin.clear();
            cin.ignore(1000, '\n');
            n = min - 1;
        } else {
            cin.ignore(1000, '\n');
            if (n >= min) {
                valido = true;
            }
        }
        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    } while (!valido);

    return n;
}

int inputIntero (int min, int max, char mex[]) {
    int n;
    do {
        cout << mex << endl;
        SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        cin >> n;
        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    } while (n < min || n >= max);
    return n;
}

Archivio inputArchivio () {
    int x = 14;
    int y = 9;
    Archivio t;
    inputStringa (MAX_NOME, " Digitare il nome e il cognome: ", t.utente, x, y);
    inputStringa (16, " Digitare il codice fiscale: ", t.codiceFiscale, x, y);
    inputStringa (MAX_NOME, " Digitare l'indirizzo di casa: ", t.indirizzo, x, y);
    t.trimestreAttuale = inputInteroSenzaMax (0, " Digitare la lettura del contatore alla fine del trimestre attuale (in metri cubi): ", x, y);
    t.trimestrePrecedente = inputInteroSenzaMax(0, " Digitare la lettura del contatore alla fine del trimestre precedente (in metri cubi): ", x, y);
    t.bolletteNonPagate = inputInteroSenzaMax(0, " Digitare l'importo di eventuali bollette precedenti non pagate: ", x, y);
    t.attivo = false;
    return t;
}

void inputTabella (Archivio tab [], int &posAttuale) {
    for (int i = posAttuale; i < posAttuale+1; i++) {
        gotoXY(40, 8);
        cout << " Inserisci i dati per l'utente numero " << i+1 << ":";
        tab[i] = inputArchivio ();
    }
}

void creaFile () {
    ofstream fTrimestre;
    fTrimestre.open("TRIMESTRE.bin", ios::binary);
    if (!fTrimestre.is_open()) {
        perror ("Errore nell'apertura del file: ");
    }
    fTrimestre.close();
}

void menu(int &posAttuale) {
    int i = 0;
    int contanti = 0;
    fstream fTrimestre;
    int ip;
    bool inMenu = true;
    while (inMenu) {
        hideCursor();
        gotoXY(28, 8);
        cout << "Selezione come vuoi procedere. Usa le frecce SU/GIU e premi INVIO.\n";
        gotoXY(49, 17);
        cout << "Premi ESC per uscire.\n\n";
        gotoXY(45, 10);
        cout << "┌───────────────────────────┐";
        for (int i = 0; i < 4; i++) {
            gotoXY(45, 11 + i);
            cout << "│";
            gotoXY(73, 11 + i);
            cout << "│";
        }
        gotoXY(45, 15);
        cout << "└───────────────────────────┘";
        gotoXY(46, 11);
        cout << "- ";
        if (i == 0) {
            SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        }
        gotoXY(48, 11);
        cout << "Inserire un nuovo utente";
        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        gotoXY(46, 12);
        cout << "- ";
        if (i == 1) {
            SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        }
        gotoXY(48, 12);
        cout << "Modificare un utente";
        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        gotoXY(46, 13);
        cout << "- ";
        if (i == 2) {
            SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        }
        gotoXY(48, 13);
        cout << "Cancellare un utente";
        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        gotoXY(46, 14);
        cout << "- ";
        if (i == 3) {
            SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        }
        gotoXY(48, 14);
        cout << "Visualizzare gli utenti";
        SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);

        gotoXY(42, ip + 11);
        cout << "  ";
        gotoXY(42, i + 11);
        cout << "->";

        ip = i;
        char tasto = _getch();
        if (tasto == ESC) {
            inMenu = false;
        }
        if (tasto == SU) {
            if (i == 0) {
                i = 3;
            } else {
                i -= 1;
            }
        }
        if (tasto == GIU) {
            if (i == 3) {
                i = 0;
            } else {
                i += 1;
            }
        }
        if (tasto == ENTER) {
            cin.sync();
            showCursor();
            system("cls");
            switch (i) {
            case 0: {
                bool reinserimento = true;
                char risposta;
                int x = 1;
                int px = x;
                char s;
                fTrimestre.open("TRIMESTRE.bin", ios::binary | ios::out | ios::app);
                if (!fTrimestre.is_open()) {
                    perror("Errore:");
                } else {
                    while (reinserimento) {
                        showCursor();
                        system("cls");
                        cin.sync();
                        inputTabella(tab, posAttuale);
                        fTrimestre.write((char *)&tab[posAttuale], sizeof(Archivio));
                        posAttuale++;
                        cout << endl;
                        system("cls");
                        while (true) {
                            hideCursor();
                            gotoXY(40, 8);
                            cout << "Si vuole aggiungere un altro utente?";
                            gotoXY(56, 10);
                            if (x == 1) {
                                SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            cout << "Si";
                            SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            gotoXY(56, 11);
                            if (x == 2) {
                                SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            }
                            cout << "No";
                            SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            gotoXY(53, px+9);
                            cout << "  ";
                            gotoXY(53, x+9);
                            cout << "->";
                            px = x;
                            s = _getch();
                            if (s == GIU) {
                                if (x == 2) {
                                    x = 1;
                                } else {
                                    x += 1;
                                }
                            }
                            if (s == SU) {
                                if (x == 1) {
                                    x = 2;
                                } else {
                                    x -= 1;
                                }
                            }
                            if (s == ENTER) {
                                if (x == 1) {
                                    reinserimento = true;
                                } else {
                                    reinserimento = false;
                                }
                                break;
                            }
                        }
                        system("cls");
                    }
                    fTrimestre.close();
                }
                break;
            }
            case 1: {
                fTrimestre.open("TRIMESTRE.bin", ios::binary | ios::in | ios::out);
                if (!fTrimestre.is_open()) {
                    perror("Errore:");
                } else {
                    if (posAttuale < 1) {
                        system("cls");
                        gotoXY(30, 8);
                        cout << "Non ci sono utenti nel sistema! Aggiungi altri utenti prima di poterli modificare";
                        Sleep(4000);
                        system("cls");
                    } else {
                        int posScelta;
                        system("cls");
                        gotoXY(37, 8);
                        cout << "Quale utente si vuole modificare? (da 1 a " << posAttuale << ")" << endl;
                        gotoXY(53, 10);
                        cout << "-> ";
                        cin >> posScelta;
                        cin.ignore(100, '\n');
                        Archivio t;
                        fTrimestre.seekg((posScelta - 1) * sizeof(Archivio), ios::beg);
                        if (fTrimestre.read((char *)&t, sizeof(Archivio))) {
                            system("cls");
                            modificaMenu(t);
                            system("cls");
                            fTrimestre.seekp((-1) * (int)sizeof(Archivio), ios::cur);
                            fTrimestre.write((char *)&t, sizeof(Archivio));
                            tab[posScelta - 1] = t;
                            hideCursor();
                            gotoXY(1, 1);
                            cout << "Modifica salvata sul file!";
                            Sleep(1500);
                        } else {
                            hideCursor();
                            gotoXY(1, 4);
                            SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            cout << "Utente non trovato!";
                            Sleep(2000);
                            SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            system("cls");
                        }
                    }
                }
                fTrimestre.close();
                i = 0;
                break;
            }
            case 2: {
                fTrimestre.open("TRIMESTRE.bin", ios::binary | ios::in | ios::out);
                if (!fTrimestre.is_open()) {
                    perror("Errore:");
                } else {
                    if (posAttuale < 1) {
                        system("cls");
                        cout << "non ci sono utenti nel sistema aggiungi altri utenti prima di cancellarne";
                        Sleep(4000);
                        system("cls");
                    } else {
                        cancellaUtente(posAttuale, contanti, fTrimestre);
                    }
                    fTrimestre.close();
                }
                i = 0;
                break;
            }
            case 3: {
                system("cls");
                if (posAttuale < 1) {
                    cout << "Nessun utente trovato aggiungine alti prima di procedere alla stampa a schermo";
                    Sleep(4000);
                } else {
                    visuallizzaUtenti(posAttuale,fTrimestre);
                }
                system("cls");
                i = 0;
                break;
            }
            }
        }
    }
}

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
            case 4: {
                strcpy (t.utente, "");
                graficaMenu(t, b, bp, true);
                gotoXY(2, 10);
                cout << endl;
                cout << "Inserisci il nuovo utente";
                //gotoXY(13, 4);
                int x = 12, y=4;
                inputStringa(MAX_NOME, "", t.utente, x, y);
            }
            break;
            case 5: {
                strcpy (t.codiceFiscale, "");
                graficaMenu(t, b, bp, true);
                gotoXY(2, 10);
                cout << endl;
                cout << "Inserisci il nuovo Codice Fiscale";
                //gotoXY(21, 5);
                int x = 20, y=4;
                inputStringa(16, "", t.codiceFiscale, x, y);
            }
            break;
            case 6: {
                strcpy (t.indirizzo, "");
                graficaMenu(t, b, bp, true);
                gotoXY(2, 10);
                cout << endl;
                cout << "Inserisci il nuovo indirizzo";
                //gotoXY(16, 6);
                int x = 15, y=5;
                inputStringa(MAX_NOME, "", t.indirizzo, x, y);
            }
            break;
            case 7: {
                graficaMenu(t, b, bp, true);
                for (int i=0; i<lunghezzaNumero(t.trimestreAttuale)+3; i++) { // Quel +3 è per far cancellare anche il " mq"
                    gotoXY(36+i, 7);
                    cout << " ";
                }
                gotoXY(2, 10);
                cout << endl;
                cout << "Nuova lettura attuale (mq)";
                //gotoXY(36, 7);
                int x = 35, y=6;
                t.trimestreAttuale = inputInteroSenzaMax(0, "", x, y);
            }
            break;
            case 8: {
                graficaMenu(t, b, bp, true);
                for (int i=0; i<lunghezzaNumero(t.trimestrePrecedente)+3; i++) { // Quel +3 è per far cancellare anche il " mq"
                    gotoXY(39+i, 8);
                    cout << " ";
                }
                gotoXY(2, 10);
                cout << endl;
                cout << "Nuova lettura precedente (mq)";
                //gotoXY(39, 8);
                int x = 38, y=7;
                t.trimestrePrecedente = inputInteroSenzaMax(0, "", x, y);
            }
            break;
            case 9: {
                graficaMenu(t, b, bp, true);
                for (int i=0; i<lunghezzaNumero(t.bolletteNonPagate)+5; i++) { // Quel +5 è per far cancellare anche il " euro"
                    gotoXY(40+i, 9);
                    cout << " ";
                }
                gotoXY(2, 10);
                cout << endl;
                cout << "Nuovo importo bollette (euro)";
                //gotoXY(40, 9);
                int x = 39, y=8;
                t.bolletteNonPagate = inputInteroSenzaMax(0, "", x, y);
            }
            break;
            }
        }
    }
}

void graficaMenu (Archivio t, int b, int bp, bool inserimento) {
    gotoXY(2,2);
    cout << "Cosa vuoi modificare? Usa le frecce SU/GIU e premi INVIO.\n";
    gotoXY(2,3);
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
    gotoXY(3,4);
    cout << "┌";
    for(int j = 0; j < maxLen + 6; j++) {
        cout << "─";
    }
    cout << "┐\n";

    for (int i = 0; i < 6; i++) {
        gotoXY(3,5+i);
        cout << "│";

        if (i == 0) {
            gotoXY(4,5);
            cout << "- ";
            if (b == 4) {
                SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            }
            gotoXY(6,5);
            cout << "Utente: " << t.utente << "";
            SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        } else if (i == 1) {
            gotoXY(4,6);
            cout << "- ";
            if (b == 5) {
                SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            }
            gotoXY(6,6);
            cout << "Codice Fiscale: " << t.codiceFiscale << "";
            SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        } else if (i == 2) {
            gotoXY(4,7);
            cout << "- ";
            if (b == 6) {
                SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            }
            gotoXY(6,7);
            cout << "Indirizzo: " << t.indirizzo << "";
            SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        } else if (i == 3) {
            gotoXY(4,8);
            cout << "- ";
            if (b == 7) {
                SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            }
            gotoXY(6,8);
            cout << "Lettura del trimestre attuale: " << t.trimestreAttuale << " mq";
            SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        } else if (i == 4) {
            gotoXY(4,9);
            cout << "- ";
            if (b == 8) {
                SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            }
            gotoXY(6,9);
            cout << "Lettura del trimestre precedente: " << t.trimestrePrecedente << " mq";
            SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        } else if (i == 5) {
            gotoXY(4,10);
            cout << "- ";
            if (b == 9) {
                SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            }
            gotoXY(6,10);
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
    gotoXY(0,bp+1);
    cout << "  ";
    gotoXY(0,b+1);
    cout <<"->";
    gotoXY(3,11);
    cout << "└";
    for(int j = 0; j < maxLen + 6; j++) {
        cout << "─";
    }
    cout << "┘\n";
}

void cancellaUtente(int &posAttuale, int &contanti, fstream &fTrimestre) {
    bool continuaCancellazione = true;

    while (continuaCancellazione) {
        int n = 0;
        int x = 1;
        int px = x;
        char s;

        while (n < 1 || n > posAttuale) {
            system("cls");
            gotoXY(36, 8);
            cout << "Quale utente si vuole cancellare? (da 1 a " << posAttuale << ")";
            gotoXY(56, 10);
            if (!(cin >> n)) {
                cin.clear();
                cin.ignore(1000, '\n');
                n = 0;
            }
        }

        bool conferma = false;
        system("cls");
        while (true) {
            hideCursor();
            gotoXY(35, 8);
            cout << "Sei sicuro di voler cancellare l'utente: " << tab[n - 1].utente;

            gotoXY(55, 10);
            if (x == 1) {
                SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            }
            cout << "Si";
            SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);

            gotoXY(55, 11);
            if (x == 2) {
                SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            }
            cout << "No";
            SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);

            gotoXY(51, px + 9);
            cout << "  ";
            gotoXY(51, x + 9);
            cout << "->";

            px = x;
            s = _getch();
            if (s == GIU) {
                if(x == 2) {
                    x = 1;
                } else {
                    x += 1;
                }
            }
            if (s == SU) {
                if(x == 1) {
                    x = 2;
                } else {
                    x -= 1;
                }
            }
            if (s == ENTER) {
                if (x == 1) {
                    conferma = true;
                }
                break;
            }
        }

        if (conferma) {
            for (int i = n - 1; i < posAttuale - 1; i++) {
                tab[i] = tab[i + 1];
            }
            posAttuale--;
            Archivio trye;
            trye.attivo = true;
            fTrimestre.close();
            fTrimestre.open("TRIMESTRE.bin", ios::binary | ios::out);
            for (int i = 0; i < posAttuale; i++) {
                fTrimestre.write((char*)&tab[i], sizeof(Archivio));
            }
            fTrimestre.seekp(posAttuale - 1* sizeof(Archivio),ios::beg);
            fTrimestre.write((char*)&trye,sizeof(Archivio));
            fTrimestre.close();

            fTrimestre.open("TRIMESTRE.bin", ios::binary | ios::in | ios::out);
            system("cls");
            gotoXY(40, 8);
            cout << "Utente eliminato con successo!";
            Sleep(1500);
        }

        if (posAttuale == 0) {
            continuaCancellazione = false;
        } else {
            x = 1;
            px = x;
            system("cls");
            while (true) {
                hideCursor();
                gotoXY(40, 8);
                cout << "Si vuole cancellare un altro utente?";

                gotoXY(57, 10);
                if (x == 1) {
                    SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                }
                cout << "Si";
                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);

                gotoXY(57, 11);
                if (x == 2) {
                    SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                }
                cout << "No";
                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);

                gotoXY(53, px + 9);
                cout << "  ";
                gotoXY(53, x + 9);
                cout << "->";

                px = x;
                s = _getch();
                if (s == GIU) {
                    if(x == 2) {
                        x = 1;
                    } else {
                        x += 1;
                    }
                }
                if (s == SU) {
                    if(x == 1) {
                        x = 2;
                    } else {
                        x -= 1;
                    }
                }
                if (s == ENTER) {
                    if (x == 2) {
                        continuaCancellazione = false;
                    }
                    break;
                }
            }
        }
    }
    system("cls");
}

void visuallizzaUtenti(int posAttuale, fstream &fTrimestre) {
    Archivio uscita;
    char s;
    fTrimestre.open("TRIMESTRE.bin", ios::binary | ios::in);
    for (int i = 0; i < posAttuale; i++) {
        if(!uscita.attivo) {
            fTrimestre.read((char*)&uscita,sizeof(Archivio));
            cout << "Utente n'"<<i+1<<":"<<uscita.utente<<endl;
            cout << "Codice fiscale:"<<uscita.codiceFiscale<<endl;
            cout << "Indirizzo:"<<uscita.indirizzo<<endl;
            cout << "Trimestre attuale:"<<uscita.trimestreAttuale<<endl;
            cout << "Trimestre precedente:"<<uscita.trimestrePrecedente<<endl;
            cout << "Bollette non pagate:"<<uscita.bolletteNonPagate<<endl;
            cout <<endl;
        }
    }
    s = _getch();
    fTrimestre.close();
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
