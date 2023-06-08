#ifndef _CABECALHO_H
#include "cabecalho.hpp"
#endif

class EXMEM{
    public:
        bool ovf;
		bool Zero;
		bitset<32> endeExtended;
		bitset<32> result;

        void executar(bitset<32> value_Ra, bitset<32> value_Rb, bitset<16> enderecoLabel, bitset<6> funct, bitset<5> shamt, bitset<2> ALUOp, bool ALUSrc, bitset<2> branch, bool jump, unsigned short &pc){
            
        }

        void execucao(){

        }

};