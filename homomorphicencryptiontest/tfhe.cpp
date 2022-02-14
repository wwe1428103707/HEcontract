#include "MDLToolkit/ciphertext.hpp"
#include "MDLToolkit/fake_ctxt.hpp"
#include "MDLToolkit/tfhe_ctxt.hpp"
#include "MDLToolkit/Integer.hpp"

#include <tfhe/tfhe_core.h>
#include <tfhe/tfhe.h>
#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;

int main() {

    using chrono::high_resolution_clock;
    using chrono::duration_cast;
    using chrono::duration;
    using chrono::milliseconds;

    auto  t1 = high_resolution_clock::now();

    const int minimum_lambda = 110;
    auto params = new_default_gate_bootstrapping_parameters(minimum_lambda);
    uint32_t seed[] = { 314, 1592, 657 };
    tfhe_random_generator_setSeed(seed, 3);
    auto key = new_random_gate_bootstrapping_secret_keyset(params);

    mdl::TFHEEncryptor encryptor(key);
    mdl::TFHEDecryptor decryptor(key->lwe_key);

    Integer<TFHECtxt> a(32), b(32);

    auto  t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double_keygen = t2-t1;
    cout << "tfhe key generation costs" << ms_double_keygen.count() << "ms" << endl;

    t1 = high_resolution_clock::now();
    a.encrypt(100000, &encryptor);
    t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double_enc = t2-t1;
    cout << "tfhe encryption costs" << ms_double_enc.count() << "ms" << endl;
    b.encrypt(7, &encryptor);

    t1 = high_resolution_clock::now();
    a.add(a);
    t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double_add = t2-t1;
    cout << "tfhe addition costs" << ms_double_add.count() << "ms" << endl;
    a.sub(b);

    t1 = high_resolution_clock::now();
    a.mul(b);
    t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double_mul = t2-t1;
    cout << "tfhe addition costs" << ms_double_mul.count() << "ms" << endl;

    t1 = high_resolution_clock::now();
    std::cout << a.decrypt(&decryptor) << "\n";
    t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double_dec = t2-t1;
    cout << "tfhe addition costs" << ms_double_dec.count() << "ms" << endl;
    std::cout << b.decrypt(&decryptor) << "\n";

    delete_gate_bootstrapping_secret_keyset(key);
    delete_gate_bootstrapping_parameters(params);
    return 0;
}
