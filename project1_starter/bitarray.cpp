#include "bitarray.hpp"
#include <cmath>
#include <stdexcept>

BitArray::BitArray() {
    numbits=8; //8 in a byte
    point= new uint8_t[1];
    *point=0;
    Valid=true;

}

BitArray::BitArray(intmax_t size) {
    // TODO
    Valid=size>0;
    if(Valid){
        numbits=size;
        intmax_t size1=(numbits-1)/8+1;
        point = new uint8_t[size1];
        for(intmax_t i=0; i<size1;i++)
        *(point+i)=0;
    }
}

BitArray::BitArray(const std::string & value) {
    // TODO
    numbits=value.length();
    intmax_t size1=(numbits-1)/8+1;
    point=new uint8_t[size1];
    Valid=true;

    for(intmax_t i=0; i<size1;i++){
        *(point+i)=0;
    for(intmax_t i=0;i<8*size1;i++){
        if(i>=8-((numbits-1)%8+1)){
            int val=value[i+(numbits-1)%8-7]-48;
            Valid=Valid && (val==0||val==1);
            *(point+i/8)+=val*std::pow(2,7-i%8);

    }
        }
    }
}

BitArray::~BitArray() {
    // TODO
    delete[] point;

}

// TODO: other methods
intmax_t BitArray::size() const {
    return numbits;
}

bool BitArray::good()const{
    return Valid;
    }

std::string BitArray::asString()const{
    
    intmax_t size1=(numbits-1)/8+1;
    std::string returnstrng="";
    for (intmax_t i=0; i<size1;i++){
        uint8_t val=point[i];
        int bits=8;
        if(i==0&& numbits%8 !=0){
            bits=numbits %8;
        }

        for(int j=bits-1;j>=0;--j){
            int bitval=(val/static_cast<int>(std::pow(2,j)))%2;
            if(bitval==1){
                returnstrng+='1';

            }else{
                returnstrng+='0';
            }
        }
    }
    return returnstrng;

}

void BitArray::reset(intmax_t index){

    Valid=Valid&& (index<numbits||index>=0);

    intmax_t size1=(numbits-1)/8+1;
    std::string bitString=asString();
    bitString.replace(index,1,"0");

    for(intmax_t i=0;i<size1;i++)
    *(point+i)=0;
    
    for ( intmax_t i=1;i<size1;i++){
        if (i>=8-((numbits-1)%8+1)){
            int val=bitString[i+(numbits-1)%8-7]-48;
            *(point+i/8)+=val *std::pow(2,7-i%8);
        }
    }

}



void BitArray::toggle(intmax_t index){

    if (test(index)){
        reset(index);
    }else{
        set(index);
    }

}


bool BitArray::test(intmax_t index){

    Valid=Valid&&(index>=0|| index< numbits);
    std::string bitString =asString();
    return Valid && bitString[index]=='1';
}


void BitArray::set(intmax_t index)
{
    Valid = Valid && (index >= 0 || index < numbits);
    intmax_t size1 = (numbits-1) / 8 + 1;
    std::string bitString = asString();
    bitString.replace(index,1,"1");
    for(intmax_t i = 0; i < size1; i++)
        *(point+i) = 0;

    for(intmax_t i = 0; i < 8*size1; i++)
    {
        if(i >= 8-((numbits-1)%8 + 1)) 
        {
            int val = bitString[i + (numbits-1)%8 - 7] - 48;
            *(point+i/8) += val * std::pow(2,7-i%8);
        }
    }
}


