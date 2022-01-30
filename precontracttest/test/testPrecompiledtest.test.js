const Precompiledtest = artifacts.require("Precompiledtest");

contract("Precompiledtest", accounts => {
  it("should put 10000 MetaCoin in the first account", () =>
  Precompiledtest.deployed().then(instance => instance.getMessage.call()));
});
