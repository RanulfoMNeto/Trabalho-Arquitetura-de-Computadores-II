#include "Processador.cpp"

int main(){
    string nomeArq;
    cout << "Digite o nome do arquivo: ";
    cin >> nomeArq;
    Processador proc = Processador(nomeArq);

    return 0;
}