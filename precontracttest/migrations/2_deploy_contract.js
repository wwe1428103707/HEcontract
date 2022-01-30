var Precompiledtest = artifacts.require("Precompiledtest");
module.exports = function(deployer) {
  deployer.deploy(Precompiledtest, 'hello world');
};