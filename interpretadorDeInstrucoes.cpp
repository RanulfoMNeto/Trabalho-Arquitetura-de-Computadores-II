#ifndef _CABECALHO_H
	#include "cabecalho.hpp"
#endif
#include <fstream>
#include <string>
#include <map>
#include <algorithm>

class Interpretador{
    private:
        map<string, string> opcodeMap = {
            {"addi"    , "00000000"}, // soma com imediato ********
            {"add"     , "00000001"}, // soma
            {"sub"     , "00000010"}, // subtração
            {"zeros"   , "00000011"}, // zerar
            {"xor"     , "00000100"}, // xor bit-a-bit
            {"or"      , "00000101"}, // ou bit-a-bit
            {"passnota", "00000110"}, // complemento de ra
            {"and"     , "00000111"}, // and bit-a-bit
            {"asl"     , "00001000"}, // shift aritmetico pra esquerda
            {"asr"     , "00001001"}, // shift aritmetico pra direita
            {"lsl"     , "00001010"}, // shift lógico pra esquerda
            {"lsr"     , "00001011"}, // shift lógico pra direita
            {"passa"   , "00001100"}, // copia ra pra rc
            {"nor"     , "00001101"}, // ou bit-a-bit depois not(passnota) ********
            {"lch"     , "00001110"}, // carrega constante nos 16b mais significativos
            {"lcl"     , "00001111"}, // carrega constante nos 16b menos significativos
            {"load"    , "00010000"}, // traz o dado da memória
            {"store"   , "00010001"}, // carrega o dado na memoria
            {"jal"     , "00010010"}, // 
            {"jr"      , "00010011"},
            {"beq"     , "00010101"},
            {"bne"     , "00010110"},
            {"j"       , "00010111"},
            {"subi"    , "00011000"}, // sub com imediato ********
            {"mul"     , "00011001"}, // multiplicação inteira ********
            {"div"     , "00011010"}, // divisão inteira ********
            {"storei"  , "00011011"}, // store imediato ********
            {"bgt"     , "00011100"}, // branch greater than ********
            {"blt"     , "00011101"}, // branch less than ********
            {"nand"    , "00011110"}, // and bit-a-bit depois not(passnota) ********
            {"halt"    , "11111111"}  // final
            // addi
            // subi
            // mul
            // div
            // storei
            // final -> 11111111

        };
        
        map<string, string> tipoInstrucaoMap = {
            // RaRbRc
            {"add" , "RaRbRc"},
            {"sub" , "RaRbRc"},
            {"xor" , "RaRbRc"},
            {"or"  , "RaRbRc"},
            {"and" , "RaRbRc"},
            {"asl" , "RaRbRc"},
            {"asr" , "RaRbRc"},
            {"lsl" , "RaRbRc"},
            {"lsr" , "RaRbRc"},
            {"mul" , "RaRbRc"},
            {"div" , "RaRbRc"},
            {"nor" , "RaRbRc"},
            {"nand", "RaRbRc"},
            // RaRc
            {"passnota" , "RaRc"},
            {"passa"    , "RaRc"},
            {"load"     , "RaRc"},
            // Store
            {"store"    , "Store"},
            // Rc
            {"zeros" , "Rc"},
            // Ra
            {"jr"    , "Ra"},
            // RcConst
            {"lch"   , "RcConst"},
            {"lcl"   , "RcConst"},
            // RaRbEnd
            {"beq" , "RaRbEnd"},
            {"bne" , "RaRbEnd"},
            {"bgt" , "RaRbEnd"},
            {"blt" , "RaRbEnd"},
            // R0Imme
            {"jal" , "R0Imme"},
            {"j"   , "R0Imme"},
            // RcRaImm
            {"addi" , "RcRaImm"},
            {"subi" , "RcRaImm"},
            // StoreImm
            {"storei" , "StoreImm"},
        };

    public:
        Interpretador(string arquivo, CacheL1Instrucoes* &instr){
            converter(arquivo, instr);
        }

        bool converter(string nomeArq, CacheL1Instrucoes* &instr){
            ifstream txt(nomeArq);

            if(txt){
                string linha;
                unsigned short pc = 0;

                while(getline(txt, linha)){
                    cout << pc << " -> " << linha << endl;

                    size_t separador = linha.find(' ');
                    string funcao = linha.substr(0, separador);
                    linha = linha.substr(separador+1);
                    linha.erase(remove(linha.begin(), linha.end(), ' '), linha.end());

                    string instrucaoBin = opcodeMap[funcao];

                    cout << pc << " -> ";
                    
                    if(tipoInstrucaoMap[funcao] == "RaRbRc")
                        instrucaoBin = tipoRaRbRc(instrucaoBin, linha);
                    else if(tipoInstrucaoMap[funcao] == "RaRc")
                        instrucaoBin = tipoRaRc(instrucaoBin, linha);
                    else if(tipoInstrucaoMap[funcao] == "Store")
                        instrucaoBin = tipoStore(instrucaoBin, linha);
                    else if(tipoInstrucaoMap[funcao] == "StoreImm")
                        instrucaoBin = tipoStoreImm(instrucaoBin, linha);
                    else if(tipoInstrucaoMap[funcao] == "Rc")
                        instrucaoBin = tipoRc(instrucaoBin, linha);
                    else if(tipoInstrucaoMap[funcao] == "Ra")
                        instrucaoBin = tipoRa(instrucaoBin, linha);
                    else if(tipoInstrucaoMap[funcao] == "RcConst")
                        instrucaoBin = tipoRcConst(instrucaoBin, linha);
                    else if(tipoInstrucaoMap[funcao] == "RaRbEnd")
                        instrucaoBin = tipoRaRbEnd(instrucaoBin, linha);
                    else if(tipoInstrucaoMap[funcao] == "R0Imme")
                        instrucaoBin = tipoR0Imme(instrucaoBin, linha);
                    else if(tipoInstrucaoMap[funcao] == "RcRaImm")
                        instrucaoBin = tipoRcRaImm(instrucaoBin, linha);
                    else if(funcao == "halt")
                        instrucaoBin += "111111111111111111111111";
                    else{
                        cout << "funcao nao reconhecida" << endl;
                        return false;
                    }
                    
                    bitset<32> instrBitset(instrucaoBin);
                    cout << instrBitset.to_string() << endl;

                    instr->setRegistrador(pc, instrBitset);

                    pc++;
                }

                txt.close();
                return true;
            }
            else
                return false;
        }

        int retornaNumLinha(string &linha){
            try{
                size_t separador = linha.find(',');
                int reg = stoi(linha.substr(1, separador-1));
                linha = linha.substr(separador+1);
                return reg;
            }
            catch(const std::invalid_argument& ia){
                cout << "Invalid argument: " << ia.what() << endl;
                return -1;
            }
        }

        string tipoRaRbRc(string instrucaoBin, string linha){
            bitset<8> rc(retornaNumLinha(linha));

            bitset<8> ra(retornaNumLinha(linha));

            int reg = stoi(linha.substr(1));
	        bitset<8> rb(reg);

            instrucaoBin += ra.to_string() + rb.to_string() + rc.to_string();

            return instrucaoBin;
        }

        string tipoRaRc(string instrucaoBin, string linha){
            bitset<8> rc(retornaNumLinha(linha));

            int reg = stoi(linha.substr(1));
	        bitset<8> ra(reg);

            bitset<8> rb(0);

            instrucaoBin += ra.to_string() + rb.to_string() + rc.to_string();

            return instrucaoBin;
        }

        string tipoStore(string instrucaoBin, string linha){
            bitset<8> rb(retornaNumLinha(linha));

            int reg = stoi(linha.substr(1));
	        bitset<8> ra(reg);

            bitset<8> rc(0);

            instrucaoBin += ra.to_string() + rb.to_string() + rc.to_string();

            return instrucaoBin;
        }

        string tipoRc(string instrucaoBin, string linha){
            int reg = stoi(linha.substr(1));
	        bitset<8> rc(reg);

            bitset<8> ra(0);
            bitset<8> rb(0);

            instrucaoBin += ra.to_string() + rb.to_string() + rc.to_string();

            return instrucaoBin;
        }

        string tipoRa(string instrucaoBin, string linha){
            int reg = stoi(linha.substr(1));
	        bitset<8> ra(reg);

            bitset<8> rb(0);
            bitset<8> rc(0);

            instrucaoBin += ra.to_string() + rb.to_string() + rc.to_string();

            return instrucaoBin;
        }

        string tipoRcConst(string instrucaoBin, string linha){
            bitset<8> rc(retornaNumLinha(linha));

            int reg = stoi(linha);
            bitset<16> const16(reg);

            instrucaoBin += const16.to_string() + rc.to_string();

            return instrucaoBin;
        }

        string tipoRaRbEnd(string instrucaoBin, string linha){
            bitset<8> ra(retornaNumLinha(linha));

            bitset<8> rb(retornaNumLinha(linha));

            int reg = stoi(linha);
	        bitset<8> end(reg);

            instrucaoBin += ra.to_string() + rb.to_string() + end.to_string();

            return instrucaoBin;
        }

        string tipoR0Imme(string instrucaoBin, string linha){
            int reg = stoi(linha.substr(1));
	        bitset<24> end(reg);

            instrucaoBin += end.to_string();

            return instrucaoBin;
        }

        string tipoRcRaImm(string instrucaoBin, string linha){
            bitset<8> rc(retornaNumLinha(linha));

            bitset<8> ra(retornaNumLinha(linha));

            int reg = stoi(linha);
	        bitset<8> imm(reg);

            instrucaoBin += ra.to_string() + imm.to_string() + rc.to_string();

            return instrucaoBin;
        }

        string tipoStoreImm(string instrucaoBin, string linha){
            bitset<8> rb(retornaNumLinha(linha));

            int reg = stoi(linha);
	        bitset<8> ra(reg);
            bitset<8> rc(0);

            instrucaoBin += ra.to_string() + rb.to_string() + rc.to_string();

            return instrucaoBin;
        }
};