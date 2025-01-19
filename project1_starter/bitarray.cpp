#include "bitarray.hpp"
#include <cmath>
#include <stdexcept>

//Talked with TA Elyse for help identifying errors and possible memory leaks when submitting with autograder
//When encountering an unknown error, searched it on GPT to see possible reasons as to why the error was occuring. Through extensive reading
//reasons from GPT and revisting my code to debug, errors were solved and code functions as it should. 

BitArray::BitArray():numbits(8),point(new uint8_t[1]{0}),Valid(true) {}

BitArray::BitArray(intmax_t size) {
    // TODO
    
    if(size<=0){
        numbits=0;
        point=nullptr;
        Valid=false;
        return;


    }
    numbits=size;
    intmax_t size1=(numbits+7)/8;
    point=new uint8_t[size1]();
    Valid=true;
}

BitArray::BitArray(const std::string & value) {
    // TODO
    numbits=value.length();
    Valid=true;
    intmax_t size1 = (numbits+7)/8;
    point=new uint8_t[size1]();


    for(intmax_t i=0; i<numbits;i++){
        if(value[i]!='0'&& value[i]!='1'){
            Valid=false;
            break;

        }
        if (value[i]=='1'){
            point[i/8]|=(1<<(7-(i%8)));
        }
    }

}

BitArray::~BitArray() {
    // TODO
    delete[] point;
    point=nullptr;

}

// TODO: other methods
intmax_t BitArray::size() const {
    return numbits;
}

bool BitArray::good()const{
    return Valid;
    }

std::string BitArray::asString()const{
    
    std::string result;
    for (intmax_t i = 0; i < numbits; ++i) {
        bool bit = (point[i / 8] & (1 << (7 - (i % 8)))) != 0;
        result += (bit ? '1' : '0');
    }

    return result;
}

void BitArray::reset(intmax_t index){

    if(index>=0&& index<numbits){
        point[index/8]&=~(1<<(7-(index%8)));

    }else{
        Valid=false;
    }
}



void BitArray::toggle(intmax_t index){

    if(index >=0 && index< numbits){
        point[index/8]^=(1<<(7-(index%8)));
    }
    else{
        Valid=false;
    }

}


bool BitArray::test(intmax_t index){
    if(index>=0&& index<numbits){
        return(point[index/8]&(1<<(7-(index%8))))!=0;

    }

    Valid=false;;
}


void BitArray::set(intmax_t index)
{
    if(index>=0&& index<numbits){
        point[index/8]|=(1<<(7-(index%8)));

    } else{
        Valid=false;
    }
}


