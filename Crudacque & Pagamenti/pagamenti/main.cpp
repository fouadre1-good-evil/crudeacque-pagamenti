#include <iostream>
#include <cstring>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <iomanip>

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

#define MAX_NOME 120

struct Archivio {
    char utente [MAX_NOME];
    char codiceFiscale [16];
    char indirizzo [MAX_NOME];
    double trimestreAttuale;
    double trimestrePrecedente;
    double bolletteNonPagate;
    bool attivo;
};

void creazioneBolletta (ifstream &fLettura);
void caricamento();
void gotoXY(int x, int y);
void hideCursor ();

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

int main() {
    keybd_event(VK_MENU, 0x36,0,0);                  // ---------|
    keybd_event(VK_RETURN, 0x1c,0,0);                //          | ------> Per mettere lo
    keybd_event(VK_RETURN, 0x1c,KEYEVENTF_KEYUP,0);  //          | ------> schermo intero all'avvio
    keybd_event(VK_MENU, 0x38,KEYEVENTF_KEYUP,0);    // ---------|
    SetConsoleOutputCP(CP_UTF8); // ------> Per i simboli
    SetConsoleCP(CP_UTF8);       // ------> delle carte
    system("color B0");
    hideCursor();
    ifstream fLettura("../TRIMESTRE.bin", ios::binary);
    if (!fLettura.is_open()) {
        gotoXY(2, 2);
        cout << "Errore: file binario non trovato." << endl;
    } else {
        creazioneBolletta(fLettura);
        fLettura.close();
        caricamento();
    }
    return 0;
}

void caricamento() {
    gotoXY(0,10);
    cout << R"(
                                                                 ___   ___   _____ _____ _____ ___  _  _ ___       ___       ___       _
                                                                / __| /_\ \ / / __|_   _|_   _/ _ \| \| |_ _|     / __|     | _ \     | |
                                                               | (_ |/ _ \ V /| _|  | |   | || (_) | .` || |      \__ \  _  |   /  _  | |__
                                                                \___/_/ \_\_/ |___| |_|   |_| \___/|_|\_|___|     |___/ (_) |_|_\ (_) |____|



                                                                           ___   _   ___ ___ ___   _   __  __ ___ _  _ _____ ___
                                                                          / __| /_\ | _ \_ _/ __| /_\ |  \/  | __| \| |_   _/ _ \
                                                                         | (__ / _ \|   /| | (__ / _ \| |\/| | _|| .` | | || (_) |
                                                                          \___/_/ \_\_|_\___\___/_/ \_\_|  |_|___|_|\_| |_| \___/


)";
gotoXY(0,30);
cout << R"(
                                                                                                    ___
                                                                                                ,--[___]--,
                                                                                               /           \
                                                                                              |,.--'```'--.,|
                                                                                              |'-.,_____,.-'|
                                                                                              |'-.,_____,.-'|
                                                                                              |             |
                                                                                              |  W A T E R  |
                                                                                              |             |
                                                                                              |'-.,_____,.-'|
                                                                                              `'-.,_____,.-''
    )";
    gotoXY(70,23);
    cout << "┌────────────────────────────────────────────────────────────┐";
    gotoXY(70,24);
    cout << "│                                                            │";
    gotoXY(70,25);
    cout << "└────────────────────────────────────────────────────────────┘";
    for (int i = 0; i < 60 ; i++) {
        if(i <= 20) {
            SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_INTENSITY);
        } else if(i <= 40) {
            for (int j = 0 ;j<=i;j++){
                SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
                gotoXY(71+j,24);
                cout<<" ";
            }
            SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
        } else {
            for (int j = 0 ;j<=i;j++){
                SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_INTENSITY);
                gotoXY(71+j,24);
                cout<<" ";
            }
            SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_INTENSITY);
        }
        gotoXY(71+i,24);
        cout << " ";
        Sleep(100);
    }
    SetConsoleTextAttribute(h, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
    int x;
    for (int i = 0; i < 20; i++) {
        if (_kbhit()) {
            gotoXY(0,54);
            cin >> x;
            break;
        }
        Sleep(100);
    }
    if (x==67){
        system("cls");
        cout << R"(

)";
        gotoXY(188,54);
        cout << "┌───────────────────┐";
        Sleep(500);
        gotoXY(188,54);
        cout << "                          ";
        gotoXY(188,54);
        cout << "│Achievement unlocked│";
        gotoXY(188,53);
        cout << "┌────────────────────┐";
        Sleep(500);
        gotoXY(188,54);
        cout << "                         ";
        gotoXY(188,52);
        cout << "                          ";
        gotoXY(188,54);
        cout << "│Name:???            │";
        gotoXY(188,52);
        cout << "┌────────────────────┐";
        gotoXY(188,53);
        cout << "│Achievement unlocked│";
        Sleep(500);
        gotoXY(187,51);
        cout << "                          ";
        gotoXY(187,52);
        cout << "                          ";
        gotoXY(187,54);
        cout << "                          ";
        gotoXY(187,53);
        cout << "                          ";
        gotoXY(187,52);
        cout << "                          ";
        gotoXY(187,53);
        cout << "│Name:???            │";
        gotoXY(187,51);
        cout << "┌────────────────────┐";
        gotoXY(187,52);
        cout << "│Achievement unlocked│";
        gotoXY(187,54);
        cout << "│Description:67      │";
        Sleep(500);
        gotoXY(187,54);
        cout << "                         ";
        gotoXY(187,53);
        cout << "                          ";
        gotoXY(187,52);
        cout << "                         ";
        gotoXY(187,51);
        cout << "                          ";
        gotoXY(187,50);
        cout << "                          ";
        gotoXY(187,49);
        cout << "                          ";
        gotoXY(187,52);
        cout << "│Name:???            │";
        gotoXY(187,50);
        cout << "┌────────────────────┐";
        gotoXY(187,51);
        cout << "│Achievement unlocked│";
        gotoXY(187,53);
        cout << "│Description:67      │";
        gotoXY(187,54);
        cout << "└────────────────────┘";
        gotoXY(0, 10);
        cout << R"(
                                                                                                     /$$$$$$  /$$$$$$$$
                                                                                                     /$$__  $$|_____ $$/
                                                                                                    | $$  \__/     /$$/
                                                                                                    | $$$$$$$     /$$/
                                                                                                    | $$__  $$   /$$/
                                                                                                    | $$  \ $$  /$$/
                                                                                                    |  $$$$$$/ /$$/
                                                                                                     \______/ |__/



    )";
    Sleep(700);
    gotoXY(0, 10);
        cout << R"(
                                                                                                     $$$$$$\  $$$$$$$$\
                                                                                                    $$  __$$\ \____$$  |
                                                                                                    $$ /  \__|    $$  /
                                                                                                    $$$$$$$\     $$  /
                                                                                                    $$  __$$\   $$  /
                                                                                                    $$ /  $$ | $$  /
                                                                                                     $$$$$$  |$$  /
                                                                                                     \______/ \__/



    )";
    Sleep(700);
    gotoXY(0, 10);
        cout << R"(
                                                                                                      ______   ________
                                                                                                     /      \ |        \
                                                                                                    |  $$$$$$\ \$$$$$$$$
                                                                                                    | $$___\$$    /  $$
                                                                                                    | $$    \    /  $$
                                                                                                    | $$$$$$$\  /  $$
                                                                                                    | $$__/ $$ /  $$
                                                                                                     \$$    $$|  $$
                                                                                                      \$$$$$$  \$$

    )";
    Sleep(700);
    gotoXY(0, 10);
        cout << R"(
                                                                                                      ______   ________
                                                                                                     /      \ /        |
                                                                                                    /$$$$$$  |$$$$$$$$/
                                                                                                    $$ \__$$/     /$$/
                                                                                                    $$      \    /$$/
                                                                                                    $$$$$$$  |  /$$/
                                                                                                    $$ \__$$ | /$$/
                                                                                                    $$    $$/ /$$/
                                                                                                     $$$$$$/  $$/


    )";
    Sleep(700);
    exit(0);
    } else {
        gotoXY(70, 26);
        cout << " Elaborazione completata. Chiusura in corso...";
        Sleep(2000);
        exit(0);
    }
}

void creazioneBolletta (ifstream &fLettura) {
    Archivio t;
    char nomeFile[25];
    while (fLettura.read((char *)&t, sizeof(Archivio))) {
        if (!t.attivo) {
            double consumiPeriodo = t.trimestreAttuale - t.trimestrePrecedente;
            double quotaFissa = 25.00;
            double quotaVariabile = consumiPeriodo * 2.80;
            double mora = 0.00;
            double bollettePrecedenti = 0.00;

            if (t.bolletteNonPagate > 0) {
                mora = 15.00;
                bollettePrecedenti = t.bolletteNonPagate;
            }
            double totaleDaPagare = quotaFissa + quotaVariabile + mora + bollettePrecedenti;

            strcpy(nomeFile, "../");
            strcat(nomeFile, t.codiceFiscale);
            strcat(nomeFile, ".TXT");
            ofstream fBolletta(nomeFile);
            if (fBolletta.is_open()) {
                fBolletta << fixed << setprecision(2);
                fBolletta << "Nome:                         " << t.utente << endl;
                fBolletta << "Codice Fiscale:               " << t.codiceFiscale << endl;
                fBolletta << "Indirizzo:                    " << t.indirizzo << endl;
                fBolletta << "Importo bollette precedenti:  " << bollettePrecedenti << endl;
                fBolletta << "Mora:                         " << mora << endl;
                fBolletta << "Consumi periodo (mc):         " << consumiPeriodo << endl;
                fBolletta << "Quota fissa:                  " << quotaFissa << endl;
                fBolletta << "Quota variabile:              " << quotaVariabile << endl;
                fBolletta << "Totale da pagare:             " << totaleDaPagare << endl;
                fBolletta.close();
            }
        }
    }
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
