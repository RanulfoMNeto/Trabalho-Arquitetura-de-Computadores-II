#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

#define _CABECALHO_H

using namespace std;

int bitsetToInt(bitset<32> b){
	int retorno = b.to_ulong();
	return retorno;
}

int bitsetToInt(bitset<5> b){
	int retorno = b.to_ulong();
	return retorno;
}

bitset<32> somaBitset32(bitset<32> b1, bitset<32> b2, bool &overflow, bool &carry){
	bitset<32> result;
	bool vai1 = 0;
	for(int i=0; i<32; i++){
		if(b1[i] and b2[i] and vai1){
			result.set(i);
			vai1 = 1;
		}
		else if((b1[i] and b2[i]) or (b1[i] and vai1) or (b2[i] and vai1)){
			vai1 = 1;
		}
		else if(b1[i] or b2[i] or vai1){
			result.set(i);
			vai1 = 0;
		}
		else{
			vai1 = 0;
		}

		if(i == 30){
			overflow = vai1;
		}
	}

	if(b1[31] == b2[31] and vai1 != overflow)
		overflow = true;
	else
		overflow = false;

	carry = vai1;

	return result;
}

bitset<32> complemento2(bitset<32> b1, bool &overflow, bool &carry){
	b1.flip();
	return somaBitset32(b1, bitset<32>(1), overflow, carry);
}

bitset<32> subtracaoBitset32(bitset<32> b1, bitset<32> b2, bool &overflow, bool &carry){ // subtracao de bitset 32b
	b2 = complemento2(b2, overflow, carry);
	bitset<32> result = somaBitset32(b1, b2, overflow, carry);
	return result;
}

bitset<32> multiplicacaoBitset32(bitset<32> b1, bitset<32> b2, bool &overflow, bool &carry){
	bitset<32> result(0);

	bool neg = b2[31];

	if(b2[31])
		b2 = complemento2(b2, overflow, carry);

	for(int i=0; i<b2.to_ulong() and !overflow; i++){
		result = somaBitset32(result, b1, overflow, carry);
	}

	if(neg)
		result[31] = !result[31];
	
	return result;
}

bitset<32> operator^(bitset<32> b1, bitset<32> b2){ // xor de bitset 32b
    bitset<32> result;
	for(int i=0; i<32; i++){
        if(b1[i] == b2[i])
            result[i] = 0;
        else
            result[i] = 1;
    }
    return result;
}

bitset<16> recorte16(bitset<32> linha, int inicio){ // recorta de tras pra frente  16<-inicio
	bitset<16> retorno;
	for(int i=0; i<16; i++)
		retorno.set(i, linha[i+inicio]);

	return retorno;
}

bitset<8> recorte8(bitset<32> linha, int inicio){
	bitset<8> retorno;
	for(int i=0; i<8; i++)
		retorno.set(i, linha[i+inicio]);

	return retorno;
}

bitset<5> recorte5(bitset<8> linha, int inicio){
	bitset<5> retorno;
	for(int i=0; i<5; i++)
		retorno.set(i, linha[i+inicio]);

	return retorno;
}

bitset<32> signalExtension(bitset<16> endereco){
	bitset<32> extendido;
	for(int i=0; i<16; i++)
		extendido.set(i, endereco[i]);
	for(int i=16; i<32; i++)
		extendido.set(i, endereco[15]);
	return extendido;
}

bitset<16> signalExtension(bitset<8> endereco){
	bitset<16> extendido;
	for(int i=0; i<8; i++)
		extendido.set(i, endereco[i]);
	for(int i=8; i<16; i++)
		extendido.set(i, endereco[7]);
	return extendido;
}



class BancoRegistradores{
    private:
        bitset<32> *registradores;
		int tamanho;
    
    public:
        BancoRegistradores(){
			tamanho = 32;
            registradores = new bitset<32>[tamanho];
            clear();
        }
        ~BancoRegistradores(){
            delete [] registradores;
        }
        void clear(){
            for(int i=0; i<tamanho; i++)
                registradores[i] = bitset<32>(0);
        }
        bitset<32> getRegistrador(bitset<8> endereco){
            return registradores[endereco.to_ulong()];
        }
        void setRegistrador(bitset<8> endereco, bitset<32> valor){
			if(endereco.to_ulong() != 0)
            	registradores[endereco.to_ulong()] = valor;
        }
};

class CacheL1Dados{
    private:
        bitset<32> *memoria;
		int tamanho;
    
    public:
        CacheL1Dados(){
			tamanho = 64*1024;
            memoria = new bitset<32>[tamanho];
            clear();
        }
        ~CacheL1Dados(){
            delete [] memoria;
        }
        void clear(){
            for(int i=0; i<tamanho; i++)
                memoria[i] = bitset<32>(0);
        }
        bitset<32> getRegistrador(bitset<16> endereco){
            return memoria[endereco.to_ulong()];
        }
        void setRegistrador(bitset<16> endereco, bitset<32> valor){
            memoria[endereco.to_ulong()] = valor;
        }
};

class CacheL1Instrucoes{
    private:
        bitset<32> *memoria;
		int tamanho;
    
    public:
        CacheL1Instrucoes(){
			tamanho = 64*1024;
            memoria = new bitset<32>[tamanho];
            clear();
        }
        ~CacheL1Instrucoes(){
            delete [] memoria;
        }
        void clear(){
            for(int i=0; i<tamanho; i++)
                memoria[i] = bitset<32>(0);
        }
        bitset<32> getRegistrador(bitset<16> endereco){
            return memoria[endereco.to_ulong()];
        }
        void setRegistrador(unsigned short endereco, bitset<32> valor){
            memoria[endereco] = valor;
        }
};