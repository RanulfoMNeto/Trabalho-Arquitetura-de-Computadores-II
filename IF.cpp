#ifndef _CABECALHO_H
	#include "cabecalho.hpp"
#endif

class IF{
    public:
        IF(){}

        bitset<32> buscarInstrucao(CacheL1Instrucoes* instrucoes, unsigned short &pc){
            bitset<32> instrucao = instrucoes->getRegistrador(pc);
            pc++;
            return instrucao;
        }
    
};