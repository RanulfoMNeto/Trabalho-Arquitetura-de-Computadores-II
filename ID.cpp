#ifndef _CABECALHO_H
#include "cabecalho.hpp"
#endif

struct ControlUnit
{
    // inicialização da unidade de controle
    bool jump = false;
    bool branch = false;
    bool mem_read = false;
    bool mem_to_reg = false;
    bool mem_write = false;
    bool alu_src = false;
    bool reg_write = false;
    bool reg_dst = false;

    bitset<5> alu_op;

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
    00000 - adição
    00001 - subtração
    00010 - zero
    00011 - xor
    00100 - or
    00101 - passnota
    00110 - and
    00111 - shiftAritE
    01000 - shiftAritD
    01001 - shiftLogE
    01010 - shiftLogD
    01011 - Copiar
    01100 - lch
    01101 - lcl
    01110 - load
    01111 - store
    10000 - jal
    10001 - jr
    10010 - beq
    10011 - bne
    10100 - j

*/

/*
    Problemas para resolver:
    - Replicação de codigo (opcional)
    - Talvez criar uma classe para o control unit com construtor inicializando os sinais de controle seja melhor

    Duvidas:
    - O passnota precisa fazer extensão do sinal?
    - não entendi muito bem o lch e lcl

*/

void ControlUnit::setControlUnit(bitset<8> opcode)
{
    // Instruções ALU
    alu_op = recorte5(opcode, 0);

    if (opcode == bitset<8>("00000001"))
    {
        // soma de inteiros
        reg_write = true;
        reg_dst = true;
        imprimirID();
    }
    else if (opcode == bitset<8>("00000010"))
    {
        // subtração
        reg_write = true;
        reg_dst = true;
        imprimirID();
    }
    else if (opcode == bitset<8>("00000011"))
    {
        // zerar
        reg_write = true;
        reg_dst = true;
    }
    else if (opcode == bitset<8>("00000100"))
    {
        // XOR
        reg_write = true;
        reg_dst = true;
    }
    else if (opcode == bitset<8>("00000101"))
    {
        // OR
        reg_write = true;
        reg_dst = true;
    }
    else if (opcode == bitset<8>("00000110"))
    {
        // passnota
        reg_write = true;
        reg_dst = true;
        // alu_op = bitset<5>("00101");
        imprimirID();
    }
    else if (opcode == bitset<8>("00000111"))
    {
        // AND
        reg_write = true;
        reg_dst = true;
        // alu_op = bitset<5>("00110");
        imprimirID();
    }
    else if (opcode == bitset<8>("00001000"))
    {
        // shift aritimetico esquerda
        reg_write = true;
        reg_dst = true;
        // alu_src = true;
        // alu_op = bitset<5>("00111");
        imprimirID();
    }
    else if (opcode == bitset<8>("00001001"))
    {
        // Shift aritmetico direita
        reg_write = true;
        reg_dst = true;
        // alu_src = true;
        // alu_op = bitset<5>("01000");
        imprimirID();
    }
    else if (opcode == bitset<8>("00001010"))
    {
        // Shift logico esquerda
        reg_write = true;
        reg_dst = true;
        // alu_src = true;
        // alu_op = bitset<5>("01001");
        imprimirID();
    }
    else if (opcode == bitset<8>("00001011"))
    {
        // Shift logico direita
        reg_write = true;
        reg_dst = true;
        // alu_src = true;
        // alu_op = bitset<5>("01010");
        imprimirID();
    }
    else if (opcode == bitset<8>("00001100"))
    {
        // Copiar
        reg_write = true;
        reg_dst = true;
        // alu_op = bitset<5>("01011");
        imprimirID();
    }

    else if (opcode == bitset<8>("00001110"))
    {
        // lch
        reg_write = true;
        reg_dst = true;
        alu_src = true;
        // alu_op = bitset<5>("01100");
        imprimirID();
    }

    else if (opcode == bitset<8>("00001111"))
    {
        // lcl
        reg_write = true;
        reg_dst = true;
        alu_src = true;
        // alu_op = bitset<5>("01101");
        imprimirID();
    }

    else if (opcode == bitset<8>("00010000"))
    {
        // load

        mem_read = true;
        mem_to_reg = true;
        alu_src = true;
        reg_write = true;
        // alu_op = bitset<5>("01110");

        imprimirID();
    }

    else if (opcode == bitset<8>("00010001"))
    {
        // store
        mem_write = true;
        alu_src = true;
        // alu_op = bitset<5>("01111");
        imprimirID();
    }

    else if (opcode == bitset<8>("00010010"))
    {
        // jal
        jump = true;
        // alu_op = bitset<5>("10000");
        imprimirID();
    }

    else if (opcode == bitset<8>("00010011"))
    {
        // jr
        jump = true;
        // alu_op = bitset<5>("10001");
        imprimirID();
    }

    else if (opcode == bitset<8>("00010101"))
    {
        // beq
        branch = true;
        // alu_op = bitset<5>("10010");
        imprimirID();
    }

    else if (opcode == bitset<8>("00010110"))
    {
        // bne
        branch = true;
        // alu_op = bitset<5>("10011");
        imprimirID();
    }

    else if (opcode == bitset<8>("00010111"))
    {
        // j
        jump = true;
        // alu_op = bitset<5>("10100");
        imprimirID();
    }
}

class ID : public ControlUnit
{
    public:
        bitset<32> value_Ra;
        bitset<32> value_Rb;
        bitset<8> Write_Adrr;
        bitset<16> endereco;

    ID() {}

    void executar(bitset<32> instrucao, BancoRegistradores &BR)
    {
        // preciso verificar se ta pegando certo isso aqui
        bitset<8> opcode = recorte8(instrucao, 24);
        bitset<8> ra = recorte8(instrucao, 16);
        bitset<8> rb = recorte8(instrucao, 8);
        bitset<8> rc = recorte8(instrucao, 0);

        setControlUnit(opcode);
        value_Ra = BR.getRegistrador(ra);
        value_Rb = BR.getRegistrador(rb);
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