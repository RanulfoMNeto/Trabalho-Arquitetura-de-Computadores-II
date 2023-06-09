#ifndef _CABECALHO_H
#include "cabecalho.hpp"
#endif

class EXMEM{
    public:
        bool ovf;
		bool Zero;
        bool carry;
        bool neg;
		bitset<32> result;

        void executar(bitset<32> dadoRa, bitset<32> dadoRb, bitset<16> endereco, bitset<5> ALUOp, bool ALUSrc, bool branch, bool jump, unsigned short &pc){
            execucao(dadoRa, dadoRb, endereco, ALUOp, ALUSrc, branch, jump, pc);
            exibirDados(dadoRa, dadoRb);
        }

        void execucao(bitset<32> dadoRa, bitset<32> dadoRb, bitset<16> endereco, bitset<5> ALUOp, bool ALUSrc, bool branch, bool jump, unsigned short &pc){
            if(ALUSrc)
                dadoRb = signalExtension(endereco);
            
            ALU(dadoRa, dadoRb, ALUOp);

            if(jump){
                if(ALUOp == bitset<5>("10010")){ // jal
                    result = pc;
                    pc = endereco.to_ulong();
                }
                else if(ALUOp == bitset<5>("10011")){
                    pc = dadoRa.to_ulong();
                }
                else if(ALUOp == bitset<5>("10111")){

                }
            }

            Zero = !result.any();
            if(branch){
                if(ALUOp == bitset<5>("10101") and Zero){ // beq
                    pc += endereco.to_ulong();
                }
                else if(ALUOp == bitset<5>("10110") and !Zero){
                    pc += endereco.to_ulong();
                }
                else if(ALUOp == bitset<5>("11100") and bitsetToInt(result) > 0){
                    pc += endereco.to_ulong();
                }
                else if(ALUOp == bitset<5>("11101") and bitsetToInt(result) < 0){
                    pc += endereco.to_ulong();
                }
            }
        }

        void ALU(bitset<32> dadoRa, bitset<32> dadoRb, bitset<5> ALUOp){
            if(ALUOp == bitset<5>("00001")){ // add
                result = dadoRa + dadoRb;
		        cout << "ADD" << endl;
            }
            else if(ALUOp == bitset<5>("00010")){ // sub
                result = dadoRa - dadoRb;
		        cout << "SUB" << endl;
            }
            else if(ALUOp == bitset<5>("00011")){ // zeros
                result = 0;
		        cout << "ZEROS" << endl;
            }
            else if(ALUOp == bitset<5>("00100")){ // xor
                result = dadoRa ^ dadoRb;
		        cout << "XOR" << endl;
            }
            else if(ALUOp == bitset<5>("00101")){ // or
                result = dadoRa | dadoRb;
		        cout << "OR" << endl;
            }
            else if(ALUOp == bitset<5>("00110")){ // not/passnota
                result = dadoRa.flip();
		        cout << "PASSNOTA" << endl;
            }
            else if(ALUOp == bitset<5>("00111")){ // and
                result = dadoRa & dadoRb;
		        cout << "AND" << endl;
            }
            else if(ALUOp == bitset<5>("01000")){ // asl
                bool aux = dadoRa[0];
                result = dadoRa << dadoRb.to_ulong();
                result[0] = aux;
		        cout << "ASL" << endl;
            }
            else if(ALUOp == bitset<5>("01001")){ // asr
                bool aux = dadoRa[0];
                result = dadoRa >> dadoRb.to_ulong();
                result[0] = aux;
		        cout << "ASR" << endl;
            }
            else if(ALUOp == bitset<5>("01010")){ // lsl
                result = dadoRa << dadoRb.to_ulong();
		        cout << "LSL" << endl;
            }
            else if(ALUOp == bitset<5>("01011")){ // lsr
                result = dadoRa >> dadoRb.to_ulong();
		        cout << "LSR" << endl;
            }
            else if(ALUOp == bitset<5>("01100")){ // copia/passa
                result = dadoRa;
		        cout << "PASSA" << endl;
            }
            else if(ALUOp == bitset<5>("01101")){ // nor
                result = dadoRa | dadoRb;
                result = result.flip();
		        cout << "NOR" << endl;
            }
            else if(ALUOp == bitset<5>("01110")){ // lch
                result = dadoRb << 16;
		        cout << "LCH" << endl;
            }
            else if(ALUOp == bitset<5>("01110")){ // lcl
                result = dadoRb;
		        cout << "LCL" << endl;
            }
            else if(ALUOp == bitset<5>("10101") or ALUOp == bitset<5>("10110") or ALUOp == bitset<5>("11100") or ALUOp == bitset<5>("11101")){ // branch
                result = dadoRa - dadoRb;
		        cout << "BRANCH" << endl;
            }
            else if(ALUOp == bitset<5>("11000")){ // subi
                result = dadoRa - dadoRb;
		        cout << "SUBI" << endl;
            }
            else if(ALUOp == bitset<5>("11001")){ // mul
                // result = dadoRa * dadoRb;
		        cout << "MUL" << endl;
            }
            else if(ALUOp == bitset<5>("11010")){ // div
                // result = dadoRa / dadoRb;
		        cout << "DIV" << endl;
            }
            else if(ALUOp == bitset<5>("11110")){ // nand
                result = dadoRa & dadoRb;
                result = result.flip();
		        cout << "NAND" << endl;
            }
        }

        void exibirDados(bitset<32> dadoRa, bitset<32> dadoRb){
            cout << "Dado Ra: " << bitsetToInt(dadoRa) << endl;
            cout << "Dado Rb: " << bitsetToInt(dadoRb) << endl;
            cout << "Resultado: " << bitsetToInt(result) << endl;
        }
};