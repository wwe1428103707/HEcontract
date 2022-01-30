// SPDX-License-Identifier: GPL-3.0

pragma solidity >=0.7.0 <=0.8.11;

contract Precompiledtest {
    bytes32 message;

    constructor(bytes32 myMessage){
        message = myMessage;
    }

    function getMessage() public view returns(bytes32) {
        return message;
    }

}