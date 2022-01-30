const Precall = artifacts.require("Precall");

contract("Precall", accounts => {

  it("ecrecover test",() => 
    Precall.deployed().then(instance => instance.ecrecovertest.call()));

//   it("sha256 test",() => 
//     Precall.deployed().then(instance => instance.calculateHash.call()));

  it("checkHash test(not precompiled contract)",() => 
    Precall.deployed().then(instance => instance.checkHash.call()));

  it("sha3-256 test",() => 
    Precall.deployed().then(instance => instance.sha3fips.call(0x68656c6c6f)));

//   it("Hash160 test",() => 
//     Precall.deployed().then(instance => instance.calculateHash160.call()));

  it("checkHash160 test(not precompiled contract)",() => 
    Precall.deployed().then(instance => instance.checkHash160.call()));

  it("BN256Add test",() => 
    Precall.deployed().then(instance => instance.callBn256Add.call()));

  it("Bn256ScalarMul test",() => 
    Precall.deployed().then(instance => instance.callBn256ScalarMul.call()));

  it("Bn256Pairing test",() => 
    Precall.deployed().then(instance => instance.callBn256Pairing.call()));

  it("Datacopy test",() => 
    Precall.deployed().then(instance => instance.callDatacopy.call(0x68656c6c6f77)));

  it("modExp test",() => 
    Precall.deployed().then(instance => instance.modExp.call(1,1,1)));

  it("BLAKE2 test",() => 
    Precall.deployed().then(instance => instance.callF.call()));

});
