#ifndef _CABECALHO_H
	#include "cabecalho.hpp"
#endif

class WR {
    void exceutar(bool reg_write, bool mem_to_reg, bitset<8> reg_dst, CacheL1Dados * dados, bitset<32> result){
        if (reg_write) {
            if (mem_to_reg) {
                dados->setRegistrador(signalExtension(reg_dst), result);
                cout << "Valor do sinal de memoria para registrador (Mem2Reg): 1" << endl;
            } else {
                dados->setRegistrador(signalExtension(reg_dst), result);
                cout << "Valor do sinal de memoria para registrador (Mem2Reg): 0" << endl;
            }
            cout << "Endereco do registrador de destino (RegDst): " << reg_dst.to_ulong() << endl;
            cout << "Valor do dado a ser escrito no registrador (Dado): " << bitsetToInt(dados->getRegistrador(signalExtension(reg_dst))) << endl;
        }
    }
};