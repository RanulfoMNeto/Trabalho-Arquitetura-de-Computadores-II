#ifndef _CABECALHO_H
	#include "cabecalho.hpp"
#endif
#include "interpretadorDeInstrucoes.cpp"

int main(){
    BancoRegistradores *rb = new BancoRegistradores();
    CacheL1Dados *dados = new CacheL1Dados();
    CacheL1Instrucoes *instrucoes = new CacheL1Instrucoes();
    Interpretador("codigo.txt", instrucoes);

    cout << instrucoes->getRegistrador(5) << endl;

    return 0;
}