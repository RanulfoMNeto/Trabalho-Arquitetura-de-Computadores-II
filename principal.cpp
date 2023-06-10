#ifndef _CABECALHO_H
	#include "cabecalho.hpp"
#endif
#include "interpretadorDeInstrucoes.cpp"
#include "IF.cpp"
#include "ID.cpp"
#include "EXMEM.cpp"
#include "WR.cpp"

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
    WR wr = WR();

    while(iF.executar(instrucoes, pc)){
        
        cout << "------------- INSTRUCTION DECODER --------------" << endl;
        id.executar(iF.instrucao, *rb);

        cout << "-------------------- EX/MEM --------------------" << endl;
        exMem.executar(id.value_Ra, id.value_Rb, id.endereco, id.alu_op, id.alu_src, id.branch, id.jump, pc, id.mem_read, id.mem_write, dados);
        
        cout << "------------------ WRITE BACK ------------------" << endl;
        wr.executar(id.reg_write, id.Write_Adrr, rb, exMem.result);

        system("pause");
        cout << endl;
    }

    return 0;
}