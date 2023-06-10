#ifndef _CABECALHO_H
	#include "cabecalho.hpp"
#endif

class IF{
    public:
        bitset<32> instrucao;

        bool executar(CacheL1Instrucoes* instrucoes, unsigned short &pc){
            instrucao = instrucoes->getRegistrador(pc);
            pc++;
            cout << "-------------- INSTRUCTION FETCH ---------------" << endl;
            cout << "Instrucao: " << instrucao << endl;
            if(instrucao == bitset<32>("11111111111111111111111111111111"))
                return false;
            return true;
        }
    
};