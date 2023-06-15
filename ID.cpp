#ifndef _CABECALHO_H
#include "cabecalho.hpp"
#endif

struct ControlUnit
{
    // inicialização da unidade de controle
    bool jump = false;
    bool branch = false;
    bool mem_read = false;
    bool mem_write = false;
    bool alu_src = false;
    bool reg_write = false;
    bool reg_dst = false;

    bitset<5> alu_op;
    bitset<16> endereco;

    

    void setControlUnit(bitset<8> opcode, bitset<32> instrucaoCompleta); // instrução aqui pq preciso dela completa pra recortar
    bool verificaTipoR(bitset<8> opcode);
    bool verificaTipoB(bitset<8> opcode);

    void resetarControles() {
        jump = false;
        branch = false;
        mem_read = false;
        mem_write = false;
        alu_src = false;
        reg_write = false;
        reg_dst = false;
    }
    
    void imprimirID()
    {
        cout << "jump: " << jump << endl
             << "branch: " << branch << endl
             << "mem_read: " << mem_read << endl
             << "mem_write: " << mem_write << endl
             << "alu_src: " << alu_src << endl
             << "reg_write: " << reg_write << endl
             << "reg_dst: " << reg_dst << endl
             << "alu_op: " << alu_op << endl;
    }
};

/*
    Problemas para resolver:
    - Replicação de codigo (opcional)
    - Talvez criar uma classe para o control unit com construtor inicializando os sinais de controle seja melhor

    Duvidas:
    - O passnota precisa fazer extensão do sinal?
    - não entendi muito bem o lch e lcl

    - Peguei a instrução e joguei como parametro pro setControlUnit (instrucaoCompleta) pq precisava manipular ela aqui dentro
    e o recorte16 e recorte 8 precisavam de um 
    - 

*/

bool ControlUnit::verificaTipoR(bitset<8> opcode) {
    if (opcode == bitset<8>("00000001")) {return true;}
    if (opcode == bitset<8>("00000010")) {return true;}
    if (opcode == bitset<8>("00000011")) {return true;}
    if (opcode == bitset<8>("00000100")) {return true;}
    if (opcode == bitset<8>("00000101")) {return true;}
    if (opcode == bitset<8>("00000110")) {return true;}
    if (opcode == bitset<8>("00000111")) {return true;}
    if (opcode == bitset<8>("00001000")) {return true;}
    if (opcode == bitset<8>("00001001")) {return true;}
    if (opcode == bitset<8>("00001010")) {return true;}
    if (opcode == bitset<8>("00001011")) {return true;}
    if (opcode == bitset<8>("00001100")) {return true;}
    if (opcode == bitset<8>("00001101")) {return true;}
    if (opcode == bitset<8>("00011110")) {return true;}
    if (opcode == bitset<8>("00011111")) {return true;}

    else {return false;}
}

bool ControlUnit::verificaTipoB(bitset<8> opcode) {
    if (opcode == bitset<8>("00010101")) {return true;}
    if (opcode == bitset<8>("00010110")) {return true;}
    if (opcode == bitset<8>("00011100")) {return true;}
    if (opcode == bitset<8>("00011101")) {return true;}
    if (opcode == bitset<8>("00011001")) {return true;}
    if (opcode == bitset<8>("00011010")) {return true;}
    
    else {return false;}
}

void ControlUnit::setControlUnit(bitset<8> opcode, bitset<32> instrucaoCompleta)
{
    // Instruções ALU
    alu_op = recorte5(opcode, 0);
    

    if (verificaTipoR(opcode))
    {
        
        // Instruções Padrão R
        reg_write = true;
        reg_dst = true;
        imprimirID();
    }

    else if (opcode == bitset<8>("00001110") or opcode == bitset<8>("00001111"))
    {
        
        // lch ou lcl
        reg_write = true;
        reg_dst = true;
        alu_src = true;
        endereco = recorte16(instrucaoCompleta, 8);
        imprimirID();
    }

    else if (opcode == bitset<8>("00000000") or opcode == bitset<8>("00011000")) // addi e subi
    {
        // addi ou subi
        reg_write = true;
        reg_dst = true;
        alu_src = true;
        endereco = signalExtension(recorte8(instrucaoCompleta, 8));
        imprimirID();
    }

    else if (opcode == bitset<8>("00010000"))
    {
        // load

        mem_read = true;
        reg_write = true;
        reg_dst = true;
        imprimirID();
    }

    else if (opcode == bitset<8>("00010001") or opcode == bitset<8>("00011011"))
    {
        // store ou storei
        mem_write = true;
        imprimirID();
    }

    else if (opcode == bitset<8>("00010010") or opcode == bitset<8>("00010111"))
    {
        // jal ou j
        endereco = recorte16(instrucaoCompleta, 0);
        jump = true;
        imprimirID();
    }

    else if (opcode == bitset<8>("00010011")) {
        //jr
        jump = true;
    }

    

    else if (verificaTipoB(opcode))
    {
        // beq ou bne
        branch = true;
        endereco = signalExtension(recorte8(instrucaoCompleta, 0));
        imprimirID();
    }
}

class ID : public ControlUnit
{
public:
    bitset<32> value_Ra;
    bitset<32> value_Rb;
    bitset<8> Write_Adrr;
    

    ID() {}

    void executar(bitset<32> instrucao, BancoRegistradores &BR)
    {
        bitset<8> opcode = recorte8(instrucao, 24);
        bitset<8> ra = recorte8(instrucao, 16);
        bitset<8> rb = recorte8(instrucao, 8);
        bitset<8> rc = recorte8(instrucao, 0);
        bitset<32> instCompleta = instrucao;

        resetarControles();
        setControlUnit(opcode, instCompleta);
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

        if(opcode == bitset<8>("00010010")){
            Write_Adrr = bitset<8>(31);
            reg_write = true;
        }

        if(opcode == bitset<8>("00011011")){
            value_Ra = signalExtension(signalExtension(ra));
        }
    }
};