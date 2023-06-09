#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

#define _CABECALHO_H

using namespace std;

bool overflow = false;

int bitsetToInt(bitset<32> b){
	int retorno = b.to_ulong();
	return retorno;
}

int bitsetToInt(bitset<5> b){
	int retorno = b.to_ulong();
	return retorno;
}

bitset<32> operator+(bitset<32> b1, bitset<32> b2){
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
	}

	if((b1[31] == b2[31]) and (b2[31] != result[31]))
		overflow = true;
	else
		overflow = false;

	return result;
}

bitset<32> operator-(bitset<32> b1, bitset<32> b2){
	b2.flip();
	bitset<32> aux(1);
	b2 = b2 + aux;
	bitset<32> result = b1 + b2;
	return result;
}

bitset<32> operator<(bitset<32> b1, bitset<32> b2){
	bitset<32> aux = b1 - b2;
	bitset<32> result;
	result = bitset<32>(aux[31]);
	return result;
}

bitset<32> operator^(bitset<32> b1, bitset<32> b2){
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