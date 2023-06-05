#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>

#include <iostream>

using namespace std;

class Interpretador{
    private:
        map<string, string> opcodeMap = {
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
                                      // ta faltando 00001101
            {"lch"     , "00001110"}, // carrega constante nos 16b mais significativos
            {"lcl"     , "00001111"}, // carrega constante nos 16b menos significativos
            {"load"    , "00010000"}, // traz o dado da memória
            {"store"   , "00010001"}, // carrega o dado na memoria
            {"jal"     , "00010010"}, // 
            {"jr"      , "00010011"},
            {"beq"     , "00010101"},
            {"bne"     , "00010110"},
            {"j"       , "00010111"},


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
            // RaRc
            {"passnota" , "RaRc"},
            {"passa"    , "RaRc"},
            {"load"     , "RaRc"},
            {"store"    , "RaRc"},
            // Rc
            {"zeros" , "Rc"},
            {"jr"    , "Rc"},
            // RcConst
            {"lch"   , "RcConst"},
            {"lcl"   , "RcConst"},
            // RaRbEnd
            {"beq" , "RaRbEnd"},
            {"bne" , "RaRbEnd"},
            // R0Imme
            {"jal" , "R0Imme"},
            {"j"   , "R0Imme"},
        };

    public:
        Interpretador(){
            
        }

        Interpretador(string arquivo){
            converter(arquivo);
        }

        bool converter(string nomeArq){
            ifstream txt(nomeArq);
            ofstream bin("programa.bin", ios::binary);

            if(txt and bin){
                string linha;
                unsigned short pc = 0;

                while(getline(txt, linha)){
                    cout << pc << " -> " << linha << endl;

                    size_t separador = linha.find(' ');
                    string funcao = linha.substr(0, separador); // add, sub, ...
                    linha = linha.substr(separador+1);
                    linha.erase(remove(linha.begin(), linha.end(), ' '), linha.end());

                    string instrucaoBin = opcodeMap[funcao];

                    cout << pc << " -> ";

                    pc++;
                    
                    if(tipoInstrucaoMap[funcao] == "RaRbRc")
                        instrucaoBin = tipoRaRbRc(instrucaoBin, linha);
                    // else if(tipoInstrucaoMap[funcao] == "ALS")
                    //     tipoAritmeticaLogicaShamt(linhaB, linha);
                    // else if(tipoInstrucaoMap[funcao] == "IME")
                    //     tipoImediata(linhaB, linha);
                    // else if(tipoInstrucaoMap[funcao] == "MEM")
                    //     tipoMemoria(linhaB, linha);
                    // else if(tipoInstrucaoMap[funcao] == "DC")
                    //     tipoDesvioCondicional(linhaB, linha, pc);
                    // else if(tipoInstrucaoMap[funcao] == "DI")
                    //     tipoDesvioIncondicional(linhaB, linha);
                    else 
                        cout << "funcao nao reconhecida" << endl;
                    
                    bitset<32> instrBitset(instrucaoBin);
                    cout << instrBitset.to_string();
                    bin.write((const char *) &instrBitset, sizeof(bitset<32>));  
                }

                txt.close();
                bin.close();
                return true;
            }
            else
                return false;
        }

        string tipoRaRbRc(string instrucaoBin, string linha){
            cout << linha << endl;
            // size_t separador = linha.find(',');
            // 
            // int reg = stoi(linha.substr(1, separador-1));
            // bitset<32> rc(reg);
            // linha = linha.substr(separador+1);

            // separador = linha.find(',');
            // reg = stoi(linha.substr(1, separador-1));
            // bitset<32> ra(reg);
            // linha = linha.substr(separador+1);

            // reg = stoi(linha);
            // bitset<32> rb(reg);

            // cout << rc.to_string() << endl;
            // cout << ra.to_string() << endl;
            // cout << rb.to_string() << endl;

            return instrucaoBin;
        }
};