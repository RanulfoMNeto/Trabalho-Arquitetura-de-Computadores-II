#include "Processador.cpp"

int main(){
    string nomeArq;
    cin >> nomeArq;
    Processador proc = Processador(nomeArq);
    proc.rb->getRegistrador(bitset<8>(6));
    proc.dados->getRegistrador()

    return 0;
}