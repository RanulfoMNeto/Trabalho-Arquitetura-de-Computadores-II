#ifndef _CABECALHO_H
	#include "cabecalho.hpp"
#endif
#include "interpretadorDeInstrucoes.cpp"
#include "IF.cpp"

int main(){
    BancoRegistradores *rb = new BancoRegistradores();
    CacheL1Dados *dados = new CacheL1Dados();
    CacheL1Instrucoes *instrucoes = new CacheL1Instrucoes();
    Interpretador("codigo.txt", instrucoes);

    unsigned short pc = 0;

    bitset<32> instrucao = IF().buscarInstrucao(instrucoes, pc);

    while(instrucao.to_string() != "11111111"){
        // ID
        // EXE/MEM
        // WB
        instrucao = IF().buscarInstrucao(instrucoes, pc);
    }

    return 0;
}