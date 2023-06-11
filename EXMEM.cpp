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

        void executar(bitset<32> dadoRa, bitset<32> dadoRb, bitset<16> endereco, bitset<5> ALUOp, bool ALUSrc, bool branch, bool jump, unsigned short &pc, bool mem_read, bool mem_write,  CacheL1Dados *dados ){
            resetar();
            execucao(dadoRa, dadoRb, endereco, ALUOp, ALUSrc, branch, jump, pc);
            memoria(mem_read, mem_write, dadoRa, dadoRb, dados);
            definirFlags();
            exibirDados(dadoRa, dadoRb);
        }

        void resetar(){
            ovf = false;
            Zero = false;
            carry = false;
            neg = false;
            result = bitset<32>(0);
        }

        void exibirDados(bitset<32> dadoRa, bitset<32> dadoRb){
            cout << "FLAGS:\nOverflow: " << ovf << endl;
            cout << "Zero: " << Zero << endl;
            cout << "Carry: " << carry << endl;
            cout << "Negativo: " << neg << endl;
            cout << "Dado Ra:   " << dadoRa << " = " << bitsetToInt(dadoRa) << endl;
            cout << "Dado Rb:   " << dadoRb << " = " << bitsetToInt(dadoRb) << endl;
            cout << "Resultado: " << result << " = " << bitsetToInt(result) << endl;
        }

        void definirFlags(){
            neg = result[31];
            ovf = overflow;
        }

        void execucao(bitset<32> &dadoRa, bitset<32> &dadoRb, bitset<16> &endereco, bitset<5> ALUOp, bool ALUSrc, bool branch, bool jump, unsigned short &pc){
            if(ALUSrc)
                dadoRb = signalExtension(endereco);
            
            ALU(dadoRa, dadoRb, ALUOp);

            if(jump){
                if(ALUOp == bitset<5>("10010")){ // jal
                    cout << "JUMP AND LINK" << endl;
                    cout << "BancoRegistradores[31] = " << pc << endl;
                    cout << "PC = " << endereco.to_ulong() << endl;
                    result = pc;
                    pc = endereco.to_ulong();
                }
                else if(ALUOp == bitset<5>("10011")){ // jr
                    cout << "JUMP REGISTER" << endl;
                    cout << "PC = " << dadoRa.to_ulong() << endl;
                    pc = dadoRa.to_ulong();
                }
                else if(ALUOp == bitset<5>("10111")){ // j
                    cout << "JUMP" << endl;
                    cout << "PC = " << endereco.to_ulong() << endl;
                    pc = endereco.to_ulong();
                }
            }

            Zero = !result.any();
            if(branch){
                if(ALUOp == bitset<5>("10101")){ // beq
                    cout << "BRANCH IF EQUAL" << endl;
                    cout << dadoRa.to_ulong() << " == " << dadoRb.to_ulong() << endl;
                    if(Zero)
                        pc += endereco.to_ulong();
                }
                else if(ALUOp == bitset<5>("10110") and !Zero){ // bne
                    cout << "BRANCH IF NOT EQUAL" << endl;
                    cout << dadoRa.to_ulong() << " != " << dadoRb.to_ulong() << endl;
                    if(!Zero)
                        pc += endereco.to_ulong();
                }
                else if(ALUOp == bitset<5>("11100")){ // bgt
                    cout << "BRANCH IF GREATER THAN" << endl;
                    cout << dadoRa.to_ulong() << " > " << dadoRb.to_ulong() << endl;
                    if(bitsetToInt(result) > 0)
                        pc += endereco.to_ulong();
                }
                else if(ALUOp == bitset<5>("11101")){ // blt
                    cout << "BRANCH IF LESS THAN" << endl;
                    cout << dadoRa.to_ulong() << " < " << dadoRb.to_ulong() << endl;
                    if(bitsetToInt(result) < 0)
                        pc += endereco.to_ulong();
                }
            }
        }

        void ALU(bitset<32> &dadoRa, bitset<32> &dadoRb, bitset<5> ALUOp){
            if(ALUOp == bitset<5>("00001") or ALUOp == bitset<5>("00000")){ // add
                result = dadoRa + dadoRb;
		        cout << "ADD" << endl;
            }
            else if(ALUOp == bitset<5>("00010") or ALUOp == bitset<5>("11000")){ // sub
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
                bool aux = dadoRa[31];
                result = dadoRa << dadoRb.to_ulong();
                result.set(31, aux);
		        cout << "ASL" << endl;
            }
            else if(ALUOp == bitset<5>("01001")){ // asr
                bool aux = dadoRa[31];
                result = dadoRa >> dadoRb.to_ulong();
                result[31] = aux;
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
            else if(ALUOp == bitset<5>("01111")){ // lcl
                result = dadoRb;
		        cout << "LCL" << endl;
            }
            else if(ALUOp == bitset<5>("10101") or ALUOp == bitset<5>("10110") or ALUOp == bitset<5>("11100") or ALUOp == bitset<5>("11101")){ // branch
                result = dadoRa - dadoRb;
            }
            else if(ALUOp == bitset<5>("11000")){ // subi
                result = dadoRa - dadoRb;
		        cout << "SUBI" << endl;
            }
            else if(ALUOp == bitset<5>("11001")){ // mul
                result = dadoRa * dadoRb;
		        cout << "MUL" << endl;
            }
            else if(ALUOp == bitset<5>("11010")){ // div
                result = dadoRa / dadoRb;
		        cout << "DIV" << endl;
            }
            else if(ALUOp == bitset<5>("11110")){ // nand
                result = dadoRa & dadoRb;
                result = result.flip();
		        cout << "NAND" << endl;
            }
        }

        void memoria(bool mem_read, bool mem_write, bitset<32> dadoRa, bitset<32> dadoRb, CacheL1Dados *dados ){
            if (mem_read) {
                bitset<16> endereco = recorte16(dadoRa, 0);
                result = dados->getRegistrador(endereco);
                cout << "LOAD" << endl;
                cout << dados->getRegistrador(endereco).to_ulong() << " = CacheL1Dados[" << endereco.to_ulong() << "]" << endl;
            }

            // Escreve na memória se MemWrite estiver ativado
            if (mem_write) {
                bitset<16>endereco = recorte16(dadoRb, 0);
                dados->setRegistrador(endereco, dadoRa);
                cout << "STORE" << endl;
                cout << "CacheL1Dados[" << endereco.to_ulong() << "] = " << dados->getRegistrador(endereco).to_ulong() << endl;
            }
        }
};