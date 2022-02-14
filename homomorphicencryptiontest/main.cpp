#include <iostream>
#include <algorithm>
#include <chrono>
#include "paillier/paillier.h"

using namespace std;
using namespace NTL;

ZZ lcm(ZZ x, ZZ y){
    ZZ ans = (x * y) / NTL::GCD(x,y);
    return ans;
}

void paillier_enc_test(){

    using chrono::high_resolution_clock;
    using chrono::duration_cast;
    using chrono::duration;
    using chrono::milliseconds;

//    ZZ p = ZZ(43);
//    ZZ q = ZZ(41);
//    ZZ lambda = lcm(p-1,q-1);

    auto  t1 = high_resolution_clock::now();
    Paillier paillier;
    auto  t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double_keygen = t2-t1;
    cout << "paillier key generation costs" << ms_double_keygen.count() << "ms" << endl;

    ZZ m = ZZ(10000000);
//    ZZ n = p*q;

    t1 = high_resolution_clock::now();
    ZZ c = paillier.encrypt(m);
    t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double_enc = t2-t1;
    cout << "paillier encryption costs" << ms_double_enc.count() << "ms" << endl;

    ZZ c2 = paillier.encrypt(ZZ(1));

    t1 = high_resolution_clock::now();
    c = paillier.addition(c,c2);
    t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double_add = t2-t1;
    cout << "paillier addition costs" << ms_double_add.count() << "ms" << endl;

    t1 = high_resolution_clock::now();
    ZZ m2 = paillier.decrypt(c);
    t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double_dec = t2-t1;
    cout << "paillier decryption costs" << ms_double_dec.count() << "ms" << endl;

    cout << "m2 = " << m2 << endl;
}

void elgamal_enc_test(){

}

void helib_bgv_enc_test(){

}

void helib_ckks_enc_test(){

}

void seal_bfv_enc_test(){

}

void seal_ckks_enc_test(){

}

void tfhe_enc_test(){

}

int main() {
//    std::cout << "Hello, World!" << std::endl;

//    using chrono::high_resolution_clock;
//    using chrono::duration_cast;
//    using chrono::duration;
//    using chrono::milliseconds;

//    auto  t1 = high_resolution_clock::now();
    paillier_enc_test();
//    auto  t2 = high_resolution_clock::now();

//    duration<double, std::milli> ms_double = t2-t1;

//    cout << ms_double.count() << "ms";

    return 0;
}
