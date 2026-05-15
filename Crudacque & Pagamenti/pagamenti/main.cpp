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

int main() {
    ifstream fLettura("../TRIMESTRE.bin", ios::binary);

    if (!fLettura.is_open()) {
        cout << "Errore: file binario non trovato." << endl;
    } else {
        creazioneBolletta(fLettura);
        fLettura.close();
        cout << "Elaborazione terminata." << endl;
    }
    return 0;
}

void creazioneBolletta (ifstream &fLettura) {
    Archivio t;
    char nomeFile[25];

    while (fLettura.read((char *)&t, sizeof(Archivio))) {

        if (t.attivo) {
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
                cout << "File creato: " << nomeFile << endl;
            }
        }
    }
}
