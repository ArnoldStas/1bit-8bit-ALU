#include <iostream>
#include <string>
#include <cstring>
using namespace std;

bool NAND(bool signal_1, bool signal_2);
bool NOR(bool signal_1, bool signal_2);
bool NOT(bool signal);
bool OR(bool signal_1, bool signal_2);
bool AND(bool signal_1, bool signal_2);
bool XOR(bool signal_1, bool signal_2);
void LOGICAL_UNIT(bool a, bool b, bool &INV_A, bool &INV_B, bool &A_XOR_B);
bool ONE_bit_HALF_ADDER_SUM(bool signal_1, bool signal_2);
bool ONE_bit_HALF_ADDER_CARRY(bool signal_1, bool signal_2);
void ONE_bit_FULL_ADDER(bool a, bool b, bool &CARRY_OUT, bool &SUM);
bool MUX(bool INV_A, bool INV_B, bool A_XOR_B, bool SUM, bool M0, bool M1);

bool ONE_bit_ALU(bool bool_A, bool bool_B, bool D1, bool D2);

int main()
{
    int to_choose;
    cout <<"If you want to realize 1-bit ALU: enter - {1}, to realize 8-bit ALU: enter - {8}" <<endl;
    cout <<"Enter: ";
    cin >> to_choose;
    cout <<endl;

    if (to_choose == 1)
    {

        cout <<"----------------------|1-bit ALU|----------------------" <<endl <<endl;

        bool a, b, ENA, ENB, OUTPUT;

        cout <<"Please enter a: ";
        cin >> a;

        cout <<"Please enter b: ";
        cin >> b;
        cout <<endl;

        cout <<"|To enable signal - 1, to disable - 0|" <<endl <<endl;

        cout <<"ENA: ";
        cin >> ENA;

        cout <<"ENB: ";
        cin >> ENB;
        cout <<endl;

        a = AND(a, ENA);
        b = AND(b, ENB);

        /*cout <<"a: " << a <<endl;
        cout <<"b: " << b;*/

        /*cout <<"NAND: " << NAND(a, b) <<endl;
        cout <<"NOR: " << NOR(a, b) <<endl;
        cout <<"NOT: " << NOT(a) <<endl;
        cout <<"OR: " << OR(a, b) <<endl;
        cout <<"AND: " << AND(a, b) <<endl;
        cout <<"XOR: " << XOR(a, b);*/

        bool INV_A, INV_B, A_XOR_B;
        LOGICAL_UNIT(a, b, INV_A, INV_B, A_XOR_B);

        /*cout <<"INV_A: " << INV_A <<endl;
        cout <<"INV_B: " << INV_B <<endl;
        cout <<"A_XOR_B: " << A_XOR_B;*/

        bool CARRY_OUT, SUM;
        ONE_bit_FULL_ADDER(a, b, CARRY_OUT, SUM);

        //cout << CARRY_OUT << SUM;

        string M0_M1;
        bool M0, M1;

        cout <<"Please enter [M0][M1]: ";
        cin >> M0_M1;
        M0 = M0_M1[0] - '0';
        M1 = M0_M1[1] - '0';
        cout <<endl;

        OUTPUT = MUX(INV_A, INV_B, A_XOR_B, SUM, M0, M1);
        cout <<"Out: " << OUTPUT;

        return 15;

    }
    else {

        cout <<"----------------------|8-bit ALU|----------------------" <<endl <<endl;

        string A, B;
        bool boolas_A[8], boolas_B[8];

        cout <<"Please enter A: ";
        cin >> A;

        cout <<"Please enter B: ";
        cin >> B;

        for (int i = 0; i < 8; i++)
        {
            if (A[i] != '0' && A[i] != '1')
            {
                cout <<endl;
                cout <<"Program has detected issue with number: {" << A[i] <<"}" <<endl;
                cout <<"You can only enter 8 bits combined with 0 and 1!";
                return 1;
            }
            else {
                boolas_A[i] = A[i] - '0';
            }
            if (B[i] != '0' && B[i] != '1')
            {
                cout <<endl;
                cout <<"Program has detected issue with number: {" << B[i] <<"}" <<endl;
                cout <<"You can only enter 8 bits combined with 0 and 1!";
                return 1;
            }
            else {
                boolas_B[i] = B[i] - '0';
            }
        }

        //DECODERIS

        string D0_D1_D2;
        bool D0, D1, D2;
        cout <<endl;
        cout <<"Please enter [D0][D1][D2]: ";
        cin >> D0_D1_D2;
        D0 = D0_D1_D2[0] - '0';
        D1 = D0_D1_D2[1] - '0';
        D2 = D0_D1_D2[2] - '0';
        cout <<endl;

        bool dec_output[8];
        dec_output[0] = AND(AND(NOT(D2), NOT(D1)), AND(NOT(D1), NOT(D0))); //000
        dec_output[1] = AND(AND(NOT(D2), NOT(D1)), AND(NOT(D1), D0)); //100
        dec_output[2] = AND(AND(NOT(D2), D1), AND(D1, NOT(D0))); //010
        dec_output[3] = AND(AND(NOT(D2), D1), AND(D1, D0)); //110
        dec_output[4] = AND(AND(D2, NOT(D1)), AND(NOT(D1), NOT(D0))); //001
        dec_output[5] = AND(AND(D2, NOT(D1)), AND(D1, NOT(D0))); //101
        dec_output[6] = AND(AND(D2, D1), AND(D1, NOT(D0))); //011
        dec_output[7] = AND(AND(D2, D1), AND(D1, D0)); //111

        /*for (int i = 0; i < 8; i++)
        {
            if (dec_output[i] == 1)
            {
                cout << i;
                return 1;
            }
        }*/

        if (dec_output[0] == 1) //000
        {
            cout <<"Operation is not valid due to combination {" << D0_D1_D2 <<"}. Program stopped.";
            return 1;
        }

        if (dec_output[4] == 1) //001
        {
            int positive = 0, negative = 0;
            if (boolas_A[0] == 1) negative++;
                else positive++;
    
            for (int i = 7; i >= 0; i--)
            {
                boolas_A[i] = ONE_bit_ALU(boolas_A[i], boolas_B[i], D1, D2);
            }
            for (int i = 7; i >= 0; i--)
            {
                if (boolas_A[i] == 0)
                {
                    boolas_A[i] = ONE_bit_ALU(boolas_A[i], boolas_B[i], D1, D2);
                    break;
                }
            }
            if (positive == 1)
            {
                cout <<"A negative number of A = {" << A <<"} is {";
                for (int i = 0; i < 8; i++)
                {
                    cout << boolas_A[i];
                }
                cout <<"}." <<endl;
            }
            else 
            {
                cout <<"A positive number of A = {" << A <<"} is {";
                for (int i = 0; i < 8; i++)
                {
                    cout << boolas_A[i];
                }
                cout <<"}." <<endl;
            }
            cout <<"Program has been succesfully stopped.";
            return 1;
        }

        if (dec_output[2] == 1) //010
        {
            bool out[8];
            bool result;
            for (int i = 0; i < 8; i++)
            {
                out[i] = ONE_bit_ALU(boolas_A[i], boolas_B[i], D1, D2);
            }
            for (int i = 0; i < 8; i++)
            {  
                if (out[i] == 0)
                {
                    cout <<"A is not equal to B {A != B}: {";
                    result = false;
                    for (int i = 0; i < 8; i++)
                    {
                        cout << out[i];
                    }
                    cout <<"}"<<endl;
                    cout <<"F = " << result <<endl;
                    cout <<"Program has been succesfully stopped.";
                    return 1;
                }
                if (i == 7 && out[i] == 1)
                {
                    cout <<"A is equal to B {A == B}: {";
                    result = true;
                    for (int i = 0; i < 8; i++)
                    {
                        cout << out[i];
                    }
                    cout <<"}"<<endl;
                    cout <<"F = " << result <<endl;
                    cout <<"Program has been succesfully stopped.";
                    return 1;
                }
            }
        }




        return 15;
    }

}

bool NAND(bool signal_1, bool signal_2)
{
    if (signal_1 * signal_2 == 0) return 1;
        else return 0;
}

bool NOR(bool signal_1, bool signal_2)
{
    if (signal_1 + signal_2 == 0) return 1;
        else return 0;
}

bool NOT(bool signal)
{
    return NAND(signal, signal);
}

bool OR(bool signal_1, bool signal_2)
{
    bool rt_signal_1;
    bool rt_signal_2;

    rt_signal_1 = NAND(signal_1, signal_1);
    rt_signal_2 = NAND(signal_2, signal_2);

    return NAND(rt_signal_1, rt_signal_2);
}

bool AND(bool signal_1, bool signal_2)
{
    bool rt_signal;

    rt_signal = NAND(signal_1, signal_2);

    return NAND(rt_signal, rt_signal);
}

bool XOR(bool signal_1, bool signal_2)
{
    bool rt_signal_main;
    bool rt_signal_1;
    bool rt_signal_2;

    rt_signal_main = NAND(signal_1, signal_2);

    rt_signal_1 = NAND(rt_signal_main, signal_1);
    rt_signal_2 = NAND(rt_signal_main, signal_2);

    return NAND(rt_signal_1, rt_signal_2);
}

void LOGICAL_UNIT(bool a, bool b, bool &INV_A, bool &INV_B, bool &A_XOR_B)
{
    INV_A = NOT(a);
    INV_B = NOT(b);
    A_XOR_B = XOR(a, b);
}

bool ONE_bit_HALF_ADDER_SUM(bool signal_1, bool signal_2)
{
    return XOR(signal_1, signal_2);
}

bool ONE_bit_HALF_ADDER_CARRY(bool signal_1, bool signal_2)
{
    return AND(signal_1, signal_2);
}

void ONE_bit_FULL_ADDER(bool a, bool b, bool &CARRY_OUT, bool &SUM)
{
    bool CARRY_IN = 0;
    bool CARRY_1, CARRY_2, SUM_1;

    CARRY_1 = ONE_bit_HALF_ADDER_CARRY(a, b);
    SUM_1 = ONE_bit_HALF_ADDER_SUM(a, b);

    CARRY_2 = ONE_bit_HALF_ADDER_CARRY(SUM_1, CARRY_IN);

    SUM = ONE_bit_HALF_ADDER_SUM(SUM_1, CARRY_IN);
    CARRY_OUT = OR(CARRY_1, CARRY_2);
}

bool MUX(bool INV_A, bool INV_B, bool A_XOR_B, bool SUM, bool M0, bool M1)
{
    //PER NAND
    /*bool x0, x1, x2, x3;

    x0 = NAND(INV_A, M0);
    x1 = NAND(INV_B, NAND(M0, M0));
    x2 = NAND(A_XOR_B, M0);
    x3 = NAND(SUM, NAND(M0, M0));

    bool x0_1, x2_3;

    x0_1 = NAND(x0, x1);
    x2_3 = NAND(x2, x3);

    return NAND(NAND(x0_1, M1), NAND(x2_3, NAND(M1, M1)));*/

    //PAPRASTAS
    bool x0, x1, x2, x3;

    x0 = AND(AND(INV_A, NOT(M0)), AND(NOT(M0), NOT(M1)));
    x1 = AND(AND(INV_B, NOT(M0)), AND(NOT(M0), M1));
    x2 = AND(AND(A_XOR_B, M0), AND(M0, NOT(M1)));
    x3 = AND(AND(SUM, M0), AND(M0, M1));

    return OR(OR(x0, x1), OR(x2, x3));
}
bool ONE_bit_ALU(bool bool_A, bool bool_B, bool D1, bool D2)
{

        bool INV_A, INV_B, A_XOR_B, OUT;
        LOGICAL_UNIT(bool_A, bool_B, INV_A, INV_B, A_XOR_B);

        bool CARRY_OUT, SUM;
        ONE_bit_FULL_ADDER(bool_A, bool_B, CARRY_OUT, SUM);

        bool M0, M1;
        M0 = D1;
        M1 = D2;

        if (M0 == 0 && M1 == 1) M1 = 0; // A

        OUT = MUX(INV_A, INV_B, A_XOR_B, SUM, M0, M1);

        return OUT;
}