#ifndef _CABECALHO_H
	#include "cabecalho.hpp"
#endif
#include "interpretadorDeInstrucoes.cpp"
#include "IF.cpp"
#include "ID.cpp"
#include "EXMEM.cpp"

int main(){
    BancoRegistradores *rb = new BancoRegistradores();
    CacheL1Dados *dados = new CacheL1Dados();
    CacheL1Instrucoes *instrucoes = new CacheL1Instrucoes();
    Interpretador("codigo.txt", instrucoes);

    system("pause");

    unsigned short pc = 0;

    IF iF = IF();
    ID id = ID();
    EXMEM exMem = EXMEM();
    // EXMEM exmem = EXMEM();
    // 
    rb->setRegistrador(bitset<8>(1), bitset<32>(20));
    rb->setRegistrador(bitset<8>(2), bitset<32>(10));

    while(iF.executar(instrucoes, pc)){
        // ID
        id.executar(iF.instrucao, *rb);
        // EXE/MEM
        exMem.executar(id.value_Ra, id.value_Rb, id.endereco, id.alu_op, id.alu_src, id.branch, id.jump, pc);
        // WB
        system("pause");
    }

    return 0;
}