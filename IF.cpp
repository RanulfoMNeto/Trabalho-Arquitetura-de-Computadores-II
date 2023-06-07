#ifndef _CABECALHO_H
	#include "cabecalho.hpp"
#endif

class IF{
    public:
        bitset<32> instrucao;

        IF(){

        }

        bool executar(CacheL1Instrucoes* instrucoes, unsigned short &pc){
            instrucao = instrucoes->getRegistrador(pc);
            pc++;
            if(instrucao == bitset<32>("11111111000000000000000000000000"))
                return false;
            return true;
        }
    
};