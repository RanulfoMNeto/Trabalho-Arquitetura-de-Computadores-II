#ifndef _CABECALHO_H
#include "cabecalho.hpp"
#endif

struct ControlUnit
{
    // inicialização da unidade de controle
    bool jump = false;
    bitset<2> branch;
    bool mem_read = false;
    bool mem_to_reg = false;
    bool mem_write = false;
    bool alu_src = false;
    bool reg_write = false;
    bool reg_dst = false;

    bitset<4> alu_op;

    void setControlUnit(bitset<8> opcode); // retirei a funct por enquanto
    void imprimirID()
    {
        cout << "jump: " << jump << endl
             << "branch: " << branch << endl
             << "mem_read: " << mem_read << endl
             << "mem_to_reg: " << mem_to_reg << endl
             << "mem_write: " << mem_write << endl
             << "alu_src: " << alu_src << endl
             << "reg_write: " << reg_write << endl
             << "reg_dst: " << reg_dst << endl
             << "alu_op: " << alu_op << endl;
    }
};

/*
    Tabela dos valores para ALU
    0000 - adição
    0001 - subtração
    0010 - zero
    0011 - xor
    0100 - or
    0101 - and
    0110 - shiftAritE
    0111 - shiftAritD
    1000 - shiftLogE
    1001 - shiftLogD
    1010 - Copy
*/

/*
    Problemas para resolver:
    - Replicação de codigo (opcional)
    -


*/

void ControlUnit::setControlUnit(bitset<8> opcode) // retirei a funct por enquanto
{
    // Instruções ALU
    if (opcode == bitset<8>("00000001"))
    {
        // soma de inteiros
        reg_write = true;
        reg_dst = true;

        // retorno pra AlUCtr
        alu_op = bitset<4>("0000"); // sinal para faze adição
        imprimirID();
    }
    else if (opcode == bitset<8>("00000010"))
    {
        // subtração
        reg_write = true;
        reg_dst = true;

        alu_op = bitset<4>("0001");
        imprimirID();
    }
    else if (opcode == bitset<8>("00000011"))
    {
        // zerar
        reg_write = true;
        reg_dst = true;
        alu_op = bitset<4>("0010");
    }
    else if (opcode == bitset<8>("00000100"))
    {
        // XOR
        reg_write = true;
        reg_dst = true;
        alu_op = bitset<4>("0011");
    }
    else if (opcode == bitset<8>("00000101"))
    {
        // OR
        reg_write = true;
        reg_dst = true;
        alu_op = bitset<4>("0100");
    }
    else if (opcode == bitset<8>("00000110"))
    {
        // passnota
    }
    else if (opcode == bitset<8>("00000111"))
    {
        // AND
    }
    else if (opcode == bitset<8>("00001000"))
    {
        // shift aritimetico esquerda
    }
    else if (opcode == bitset<8>("00001001"))
    {
        // Shift aritmetico direita
    }
    else if (opcode == bitset<8>("00001010"))
    {
        // Shift logico esquerda
    }
    else if (opcode == bitset<8>("00001011"))
    {
        // Shift logico direita
    }
    else if (opcode == bitset<8>("00001100"))
    {
        // Copiar
    }

    else if (opcode == bitset<8>("00001110"))
    {
        // lch
    }

    else if (opcode == bitset<8>("00001111"))
    {
        // lcl
    }

    else if (opcode == bitset<8>("00010000"))
    {
        // load

        mem_read = true;
        mem_to_reg = true;
        alu_src = true;
        reg_write = true;

        imprimirID();
    }

    else if (opcode == bitset<8>("00010001"))
    {
        // store
        mem_write = true;
        alu_src = true;
    }

    else if (opcode == bitset<8>("00010010"))
    {
        // jal
    }

    else if (opcode == bitset<8>("00010011"))
    {
        // jr
    }

    else if (opcode == bitset<8>("00010101"))
    {
        // beq
    }

    else if (opcode == bitset<8>("00010110"))
    {
        // bne
    }

    else if (opcode == bitset<8>("00010111"))
    {
        // j
    }

    else if (opcode == bitset<8>("00010001"))

        //         // Instruções tipo branch (beq / bne / bge):
        //         else if (opcode == bitset<8>("000100") or opcode == bitset<8>("000101") or opcode == bitset<8>("000110"))
        //         {
        //             if (opcode == bitset<8>("000101")) // bne
        //                 branch = bitset<2>("10");

        //             else if (opcode == bitset<8>("000110")) // bge
        //                 branch = bitset<2>("11");
        //             else
        //             {
        //                 branch = bitset<2>("01");
        //             }

        //             // alu_op = bitset<2>("01");

        //             imprimirID();
        //         }
        //     // Instruções tipo J

        //     else if (opcode == bitset<8>("000010") or opcode == bitset<8>("000011") or (opcode == bitset<8>("000000"))) // retirei a funct por enquanto
        //     {
        //         jump = true;
        //         imprimirID();
        //     }

        //     // Instrução Load Word
        //     else if (opcode == bitset<8>("100011"))
        //     {

        //         // alu_op = bitset<2>("00");
        //     }

        //     else if (opcode == bitset<8>("101011")) // Instrução Save Word
        //     {

        //         // alu_op = bitset<2>("00");
        //         imprimirID();
        //     }

        //     else
        //     // Instrução tipo I:
        //     {
        //         alu_src = true;
        //         reg_write = true;

        //         // alu_op = bitset<2>("00");
        //         imprimirID();
        //     }
        // }

        // // flag bne

        // //  funct

        class ID : public ControlUnit
        {
        public:
            bitset<32> value_Ra;
            bitset<32> value_Rb;
            bitset<8> Write_Adrr;

            ID(bitset<8> opcode, bitset<8> ra, bitset<8> rb, bitset<8> rc, BancoRegistradores &BR)
            {
                // falta entender isso aqui, saber oque pegar e como retornar o conteudo do registrador
                setControlUnit(opcode);
                // value_Ra = BR.getRegistrador(ra); //tirar comentário quando o get aceitar 8 bits
                // value_Rb = BR.getRegistrador(rb); //tirar comentário quando o get aceitar 8 bits
                if (reg_dst)
                {
                    Write_Adrr = rc;
                }

                else
                {
                    Write_Adrr = rb;
                }
            }
        };