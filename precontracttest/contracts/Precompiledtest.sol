// SPDX-License-Identifier: MIT

pragma solidity >=0.7.0 <=0.8.11;

contract Precompiledtest {
    string message;

    constructor(string memory myMessage){
        message = myMessage;
    }

    function getMessage() public view returns(string memory) {
        return message;
    }

}