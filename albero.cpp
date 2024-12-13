#include <iostream>
using namespace std;

template <typename Tipo>
class AlberoBin {
private:
    Tipo valori[50];
    bool nodiEsistenti[50];
    int contaNodi;

public:
    AlberoBin() {
        contaNodi = 0;
        for (int indice = 0; indice < 50; ++indice) {
            nodiEsistenti[indice] = false;
        }
    }

    bool vuoto() const {
        return contaNodi == 0;
    }

    void inserisciRadice(const Tipo& valore) {
        if (contaNodi < 50) {
            valori[0] = valore;
            nodiEsistenti[0] = true;
            contaNodi = 1;
        }
    }

    Tipo leggiRadice() const {
        return vuoto() ? Tipo() : valori[0];
    }

    bool nodoFoglia(int posizione) const {
        if (!nodiEsistenti[posizione]) return false;
        int sinistro = 2 * posizione + 1;
        int destro = 2 * posizione + 2;
        return (sinistro >= 50 || !nodiEsistenti[sinistro]) && (destro >= 50 || !nodiEsistenti[destro]);
    }

    int indiceSinistro(int posizione) const {
        int sinistro = 2 * posizione + 1;
        return (sinistro < 50 && nodiEsistenti[sinistro]) ? sinistro : -1;
    }

    int indiceDestro(int posizione) const {
        int destro = 2 * posizione + 2;
        return (destro < 50 && nodiEsistenti[destro]) ? destro : -1;
    }

    void aggiungiSinistro(int posizione, const Tipo& valore) {
        int sinistro = 2 * posizione + 1;
        if (sinistro < 50 && nodiEsistenti[posizione] && !nodiEsistenti[sinistro]) {
            valori[sinistro] = valore;
            nodiEsistenti[sinistro] = true;
            ++contaNodi;
        }
    }

    void aggiungiDestro(int posizione, const Tipo& valore) {
        int destro = 2 * posizione + 2;
        if (destro < 50 && nodiEsistenti[posizione] && !nodiEsistenti[destro]) {
            valori[destro] = valore;
            nodiEsistenti[destro] = true;
            ++contaNodi;
        }
    }

    void eliminaNodo(int posizione) {
        if (posizione < 50 && nodiEsistenti[posizione]) {
            if (nodoFoglia(posizione)) {
                nodiEsistenti[posizione] = false;
                --contaNodi;
            } else {
                int sinistro = 2 * posizione + 1;
                int destro = 2 * posizione + 2;

                if (sinistro < 50 && nodiEsistenti[sinistro]) {
                    nodiEsistenti[sinistro] = false;
                    --contaNodi;
                }

                if (destro < 50 && nodiEsistenti[destro]) {
                    nodiEsistenti[destro] = false;
                    --contaNodi;
                }

                nodiEsistenti[posizione] = false;
                --contaNodi;
            }
        }
    }

    void mostraAlbero() const {
        for (int indice = 0; indice < 50; ++indice) {
            if (nodiEsistenti[indice]) {
                cout << "Nodo " << indice << ": " << valori[indice] << endl;

                int sinistro = indiceSinistro(indice);
                int destro = indiceDestro(indice);
                
                if (sinistro != -1 && nodiEsistenti[sinistro]) {
                    cout << "  Figlio sinistro: " << valori[sinistro] << endl;
                } else {
                    cout << "  Figlio sinistro: /" << endl;
                }

                if (destro != -1 && nodiEsistenti[destro]) {
                    cout << "  Figlio destro: " << valori[destro] << endl;
                } else {
                    cout << "  Figlio destro: /" << endl;
                }
            }
        }
    }
};
