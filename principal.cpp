#ifndef _CABECALHO_H
	#include "cabecalho.hpp"
#endif
#include "interpretadorDeInstrucoes.cpp"
#include "IF.cpp"
#include "ID.cpp"

int main(){
    BancoRegistradores *rb = new BancoRegistradores();
    CacheL1Dados *dados = new CacheL1Dados();
    CacheL1Instrucoes *instrucoes = new CacheL1Instrucoes();
    Interpretador("codigo.txt", instrucoes);

    unsigned short pc = 0;

    IF iF = IF();
    ID id = ID();
    // EXMEM exmem = EXMEM();
    // 

    while(iF.executar(instrucoes, pc)){
        // ID
        id.executar(iF.instrucao, *rb);
        // EXE/MEM
        // ID(instrucao, rb);
        // EX(ID().value_ra, ID().)
        // // WB
    }

    return 0;
}