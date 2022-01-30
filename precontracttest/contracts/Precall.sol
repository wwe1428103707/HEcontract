// SPDX-License-Identifier: MIT

pragma solidity >=0.7.0 <=0.8.11;

contract Precall {

    bytes32 public expectedHash = 0x7f83b1657ff1fc53b92dc18148a1d65dfc2d4b1fa3d677284addd200126d9069;
    bytes20 public expectedHash2 = hex'8476ee4631b9b30ac2754b0ee0c47e161d3f724c';

    function ecrecovertest() public pure returns(bool) {
        address addressTest = 0x12Cb274aAD8251C875c0bf6872b67d9983E53fDd;
        bytes32 msgHash = 0xc51dac836bc7841a01c4b631fa620904fc8724d7f9f1d3c420f0e02adf229d50;
        uint8 v = 0x1b;
        bytes32 r = 0x44287513919034a471a7dc2b2ed121f95984ae23b20f9637ba8dff471b6719ef;
        bytes32 s = 0x7d7dc30309a3baffbfd9342b97d0e804092c0aeb5821319aa732bc09146eafb4;
        // Use ECRECOVER to verify address
        return (ecrecover(msgHash, v, r, s) == (addressTest));
    }

    function calculateHash() public pure returns (bytes32) {
        string memory word = 'Hello World!';
        bytes32 hash = sha256(bytes (word));

        return hash;        
    }

    function checkHash() public view returns(bool) {
        return (calculateHash() == expectedHash);
    }

    function sha3fips(bytes memory data) public view returns (bytes32) {
        bytes32[1] memory h;
        assembly {
            if iszero(
                staticcall(200000, 0x400, add(data, 32), mload(data), h, 32)
            ) {
                invalid()
            }
        }
        return h[0];
    }

    function calculateHash160() public pure returns (bytes20) {
        string memory word = 'Hello World!';
        bytes20 hash = ripemd160(bytes (word));

        return hash;        
    }

    function checkHash160() public view returns(bool) {
        return (calculateHash() == expectedHash2);
    }

    function callBn256Add() public returns (bytes32[2] memory result) {
        bytes32[4] memory input;
        input[0] = 0x0000000000000000000000000000000000000000000000000000000000000000;
        input[1] = 0x0000000000000000000000000000000000000000000000000000000000000000;
        input[2] = 0x0000000000000000000000000000000000000000000000000000000000000000;
        input[3] = 0x0000000000000000000000000000000000000000000000000000000000000000;
        assembly {
            let success := call(200000, 0x06, 0, input, 0x80, result, 0x40)
            switch success
            case 0 {
                revert(0,0)
            }
        }
    }

    function callBn256ScalarMul() public returns (bytes32[2] memory result) {
        bytes32[3] memory input;
        input[0] = 0x0000000000000000000000000000000000000000000000000000000000000000;
        input[1] = 0x0000000000000000000000000000000000000000000000000000000000000000;
        input[2] = 0x0200000000000000000000000000000000000000000000000000000000000000;
        assembly {
            let success := call(200000, 0x07, 0, input, 0x60, result, 0x40)
            switch success
            case 0 {
                revert(0,0)
            }
        }
    }

    function callBn256Pairing() public returns (bytes32 result) {
        // input is a serialized bytes stream of (a1, b1, a2, b2, ..., ak, bk) from (G_1 x G_2)^k
        bytes memory input = hex'2eca0c7238bf16e83e7a1e6c5d49540685ff51380f309842a98561558019fc0203d3260361bb8451de5ff5ecd17f010ff22f5c31cdf184e9020b06fa5997db841213d2149b006137fcfb23036606f848d638d576a120ca981b5b1a5f9300b3ee2276cf730cf493cd95d64677bbb75fc42db72513a4c1e387b476d056f80aa75f21ee6226d31426322afcda621464d0611d226783262e21bb3bc86b537e986237096df1f82dff337dd5972e32a8ad43e28a78a96a823ef1cd4debe12b6552ea5f06967a1237ebfeca9aaae0d6d0bab8e28c198c5a339ef8a2407e31cdac516db922160fa257a5fd5b280642ff47b65eca77e626cb685c84fa6d3b6882a283ddd1198e9393920d483a7260bfb731fb5d25f1aa493335a9e71297e485b7aef312c21800deef121f1e76426a00665e5c4479674322d4f75edadd46debd5cd992f6ed090689d0585ff075ec9e99ad690c3395bc4b313370b38ef355acdadcd122975b12c85ea5db8c6deb4aab71808dcb408fe3d1e7690c43d37b4ce6cc0166fa7daa';
        uint256 len = input.length;
        require(len % 192 == 0);
        assembly {
            let memPtr := mload(0x40)
            let success := call(200000, 0x08, 0, add(input, 0x20), len, memPtr, 0x20)
            switch success
            case 0 {
                revert(0,0)
            } default {
                result := mload(memPtr)
            }
        }
    }

    bytes public memoryStored;

    function callDatacopy(bytes memory data) public returns (bytes memory) {
    bytes memory result = new bytes(data.length);
    assembly {
        let len := mload(data)
        if iszero(call(200000, 0x04, 0, add(data, 0x20), len, add(result,0x20), len)) {
            invalid()
        }
    }

    memoryStored = result;

    return result;
    }

    uint public checkResult;

    // Function to Verify ModExp Result
    function modVerify( uint _base, uint _exp, uint _modulus) public {
        checkResult = modExp(_base, _exp, _modulus);
    }

    function modExp(uint256 _b, uint256 _e, uint256 _m) public returns (uint256 result) {
        assembly {
            // Free memory pointer
            let pointer := mload(0x40)
            // Define length of base, exponent and modulus. 0x20 == 32 bytes
            mstore(pointer, 0x20)
            mstore(add(pointer, 0x20), 0x20)
            mstore(add(pointer, 0x40), 0x20)
            // Define variables base, exponent and modulus
            mstore(add(pointer, 0x60), _b)
            mstore(add(pointer, 0x80), _e)
            mstore(add(pointer, 0xa0), _m)
            // Store the result
            let value := mload(0xc0)
            // Call the precompiled contract 0x05 = bigModExp
            if iszero(call(20000, 0x05, 0, pointer, 0xc0, value, 0x20)) {
                revert(0, 0)
            }
            result := mload(value)
        }
    }

    function F(uint32 rounds, bytes32[2] memory h, bytes32[4] memory m, bytes8[2] memory t, bool f) public view returns (bytes32[2] memory) {
        bytes32[2] memory output;

        bytes memory args = abi.encodePacked(rounds, h[0], h[1], m[0], m[1], m[2], m[3], t[0], t[1], f);

        assembly {
            if iszero(staticcall(20000, 0x09, add(args, 32), 0xd5, output, 0x40)) {
            revert(0, 0)
            }
        }

        return output;
    }

    function callF() public view returns (bytes32[2] memory) {
        uint32 rounds = 12;

        bytes32[2] memory h;
        h[0] = hex"48c9bdf267e6096a3ba7ca8485ae67bb2bf894fe72f36e3cf1361d5f3af54fa5";
        h[1] = hex"d182e6ad7f520e511f6c3e2b8c68059b6bbd41fbabd9831f79217e1319cde05b";

        bytes32[4] memory m;
        m[0] = hex"6162630000000000000000000000000000000000000000000000000000000000";
        m[1] = hex"0000000000000000000000000000000000000000000000000000000000000000";
        m[2] = hex"0000000000000000000000000000000000000000000000000000000000000000";
        m[3] = hex"0000000000000000000000000000000000000000000000000000000000000000";

        bytes8[2] memory t;
        t[0] = hex"03000000";
        t[1] = hex"00000000";

        bool f = true;

        // Expected output:
        // ba80a53f981c4d0d6a2797b69f12f6e94c212f14685ac4b74b12bb6fdbffa2d1
        // 7d87c5392aab792dc252d5de4533cc9518d38aa8dbf1925ab92386edd4009923
        return F(rounds, h, m, t, f);
    }

}