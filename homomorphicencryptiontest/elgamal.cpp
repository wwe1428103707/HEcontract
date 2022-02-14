#include<NTL/ZZ.h>
#include<iostream>
#include<ctime>
#include <chrono>
using namespace std;
using namespace NTL;
pair<ZZ,ZZ> encrypt(ZZ x, ZZ alpha, ZZ beta,ZZ p){
	ZZ k;
	SetSeed(to_ZZ(time(NULL)));
	k=RandomBnd(p);
	while(k<2){
		k=RandomBnd(p);
	}
	ZZ y1,y2;
	PowerMod(y1,alpha,k,p);
	PowerMod(y2,beta,k,p);
	y2=MulMod(y2,x,p);
	return make_pair(y1,y2);
}
ZZ decrypt(pair<ZZ,ZZ> ctxt,ZZ a,ZZ p){
	ZZ t;
	t=PowerMod(ctxt.first,a,p);
	t=InvMod(t,p);
	t=MulMod(t,ctxt.second,p);
	return t;
}
pair<ZZ,ZZ> ctxtMul(const pair<ZZ,ZZ> &c1,const pair<ZZ,ZZ>& c2,ZZ& p){
	pair<ZZ,ZZ> res;
	res.first=MulMod(c1.first,c2.first,p);
	res.second=MulMod(c1.second,c2.second,p);
	return res;
}
int main(){

    using chrono::high_resolution_clock;
    using chrono::duration_cast;
    using chrono::duration;
    using chrono::milliseconds;

	ZZ p,alpha,a,beta;
	p=2579;
	alpha=2;
	a=765;
	beta=949;
	pair<ZZ,ZZ> ctxt1,ctxt2,ctxt3;
//	cout<<"Input the plaintext x1:"<<endl;
	ZZ x1 = ZZ(100);
//	cin>>x1;
    auto  t1 = high_resolution_clock::now();
	ctxt1=encrypt(x1,alpha,beta,p);
    auto  t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double_enc = t2-t1;
    cout << "elgamal encryption costs" << ms_double_enc.count() << "ms" << endl;
//	cout<<"The ciphertext of x1 is:"<<endl;
//	cout<<"y1:"<<ctxt1.first<<endl;
//	cout<<"y2:"<<ctxt1.second<<endl;

//	cout<<"Input the plaintext x2:"<<endl;
	ZZ x2 = ZZ(2);
//	cin>>x2;
	ctxt2=encrypt(x2,alpha,beta,p);
//	cout<<"The ciphertext of x2 is:"<<endl;
//	cout<<"y1:"<<ctxt2.first<<endl;
//	cout<<"y2:"<<ctxt2.second<<endl;

	ZZ x3;
	x3=x1*x2%p;
	cout<<"x1*x2 is "<<x3<<endl;

    t1 = high_resolution_clock::now();
	ctxt3=ctxtMul(ctxt1,ctxt2,p);
    t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double_mul = t2-t1;
    cout << "elgamal addition costs" << ms_double_mul.count() << "ms" << endl;
//	cout<<"The ciphertext of ctxt1*ctxt2 is:"<<endl;
//	cout<<"y1:"<<ctxt3.first<<endl;
//	cout<<"y2:"<<ctxt3.second<<endl;

	ZZ result;
    t1 = high_resolution_clock::now();
	result=decrypt(ctxt3,a,p);
    t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double_dec = t2-t1;
    cout << "elgamal decryption costs" << ms_double_dec.count() << "ms" << endl;
	cout<<"Decrypted:"<<result<<endl;
	return 0;
}