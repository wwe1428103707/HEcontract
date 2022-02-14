#include <iostream>

#include <helib/helib.h>

using namespace std;

int main() {

    using chrono::high_resolution_clock;
    using chrono::duration_cast;
    using chrono::duration;
    using chrono::milliseconds;


//    long p = 1021;
//    long r = 1;
//    long L = 16;
//    long c = 3;
//    long w = 64;
//    long d = 0;
//    long k = 128;
//    long s = 0;
//    long m = helib::FindM(k, L, c, p, d, s, false);
//    helib::Context context = helib::ContextBuilder<helib::BGV>()
//            .m(m)
//            .p(p)
//            .r(r)
//            .bits(L)
//            .c(c)
//            .build();
//    NTL::ZZX G = context.getAlMod().getFactorsOverZZ()[0];
//    helib::SecKey secKey(context);
//    secKey.GenSecKey();

//    unsigned long p = 4999;
    unsigned long p = 6113173061495177;
    unsigned long m = 32109;
    unsigned long r = 1;
    unsigned long bits = 2048;
    unsigned long c = 2;
    auto  t1 = high_resolution_clock::now();
    helib::Context context = helib::ContextBuilder<helib::BGV>()
            .m(m)
            .p(p)
            .r(r)
            .bits(bits)
            .c(c)
            .build();

    helib::SecKey secKey(context);
    secKey.GenSecKey();
    auto  t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double_keygen = t2-t1;
    cout << "helib key generation costs" << ms_double_keygen.count() << "ms" << endl;

//    std::cout << secKey << std::endl;

    const helib::PubKey& pubKey = secKey;

//    std::cout << pubKey << std::endl;

    helib::Ctxt ctxt1(pubKey);
    helib::Ctxt ctxt2(pubKey);

    std::cout << "Security: " << context.securityLevel() << std::endl;

    t1 = high_resolution_clock::now();
    pubKey.Encrypt(ctxt1, NTL::to_ZZX(100000));
    t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double_enc = t2-t1;
    cout << "helib encryption costs" << ms_double_enc.count() << "ms" << endl;

    pubKey.Encrypt(ctxt2, NTL::to_ZZX(7));

    t1 = high_resolution_clock::now();
    helib::Ctxt sum = ctxt1;
    sum += ctxt1;
    t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double_add = t2-t1;
    cout << "helib addition costs" << ms_double_add.count() << "ms" << endl;

    t1 = high_resolution_clock::now();
    helib::Ctxt mul = ctxt1;
    mul *= ctxt1;
    t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double_mul = t2-t1;
    cout << "helib multi costs" << ms_double_mul.count() << "ms" << endl;

    t1 = high_resolution_clock::now();
    NTL::ZZX ptsum;
    secKey.Decrypt(ptsum, sum);
    t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double_dec = t2-t1;
    cout << "helib decryption costs" << ms_double_dec.count() << "ms" << endl;

    std::cout << ptsum << std::endl;

    secKey.Decrypt(ptsum, mul);
    std::cout << ptsum << std::endl;
    return 0;
}
