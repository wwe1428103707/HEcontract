# HEcontract: A privacy-preserving system for blockchain smart contract based on homomorphic encryption

This project is the main experimental code for the paper of the same name.

## Usage of Ethereum native precompiled contract evaluation

The test follows the ethereum standard, please download truffle, ganache.

### truffle installation

#### nodejs

```bash
curl -sL https://deb.nodesource.com/setup_16.x | sudo -E bash -
sudo apt-get install -y nodejs
```

#### npm or cnpm(for Chinese users)

```bash
sudo apt-get install npm
```

if your npm is not up to date, pls upgrade it use

```bash
sudo npm install -g npm
```

if you want to install cnpm, use

```bash
sudo npm install -g cnpm --registry=https://registry.npm.taobao.org
```

#### truffle

```bash
sudo npm install -g truffle
#or
sudo cnpm install -g truffle
```

### ganache installation

We recommend using ganache gui client, it is very intuitive and easy to use, here is the download [link](https://trufflesuite.com/ganache/).

## evaluation

open the ganache, and do as the fig show. Click the new worspace bottom to create a new Ethereum test network.

![image-20220130230523188](https://s2.loli.net/2022/01/30/faclzILuETQ8oRr.png)

then, name the workspace as you like. Click the **ADD PROJECT**, and choose the **truffle-config.js** in the **precontracttest** directory. Click the Open button finally.

![image-20220130230833615](https://s2.loli.net/2022/01/30/KatQwlDgehJMxAp.png)

Now you have created a test network, you can also tweak the details of the network, please refer to the ganache documentation.

Open a terminal and make sure it is in the **precontracttest** directory.

Please execute the following command.

```bash
truffle migrate

truffle test
#or
truffle test ./test/testPrecall.test.js
```

You should now see output that looks like this

```bash
Using network 'development'.


Compiling your contracts...
===========================
> Compiling ./contracts/Precall.sol
> Artifacts written to /tmp/test--11340-qiCLFN6HJ7dM
> Compiled successfully using:
   - solc: 0.8.11+commit.d7f03943.Emscripten.clang



  Contract: Precall
    ✓ ecrecover test (339ms)
    ✓ checkHash test(not precompiled contract) (313ms)
    ✓ sha3-256 test (192ms)
    ✓ checkHash160 test(not precompiled contract) (235ms)
    ✓ BN256Add test (593ms)
    ✓ Bn256ScalarMul test (373ms)
    ✓ Bn256Pairing test (9004ms)
    ✓ Datacopy test (454ms)
    ✓ modExp test (312ms)
    ✓ BLAKE2 test (376ms)


  11 passing (14s)
```

If an error occurs, make sure that both ganache and truffle are using the same port. Truffle config file is **truffle-config.js**.

![image-20220130232039024](https://s2.loli.net/2022/01/30/ngBdzHRkamfrlEb.png)

## Additional information
We will continue to organize the system code and upload it. If you have any questions, you can raise issues or contact us yufaji@std.uestc.edu.cn.