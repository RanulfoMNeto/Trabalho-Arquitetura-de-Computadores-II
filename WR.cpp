#ifndef _CABECALHO_H
	#include "cabecalho.hpp"
#endif

class WR {
    public:
        void executar(bool reg_write, bitset<8> reg_dst, BancoRegistradores *rb, bitset<32> result){
            if (reg_write) {
                rb->setRegistrador(reg_dst, result);
                cout << "BancoRegistradores[" << reg_dst.to_ulong() << "] = " << bitsetToInt(rb->getRegistrador(reg_dst)) << endl;
            }
        }
};