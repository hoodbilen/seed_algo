//
//  main.c
//  seed_
//
//  Created by 이나연 on 2019/11/11.
//  Copyright © 2019 이나연. All rights reserved.
//

#include<stdio.h>

struct secret_Key{
    uint32_t secretKey[4];
}sk;

struct allKey{
    uint32_t allkey[32];
}ak;

static const uint32_t keyConstant[16]={
    0x9E3779B9, 0x3C6EF373, 0x78DDE6E6, 0xF1BBCDCC,
    0xE3779B99, 0xC6EF3733, 0x8DDE6E67, 0x1BBCDCCF,
    0x3779B99E, 0x6EF3733C, 0xDDE6E678, 0xBBCDCCF1,
    0x779B99E3, 0xEF3733C6, 0xDE6E678D, 0xBCDCCF1B
};

unsigned int rol(int32_t value1, int32_t value2) {
    return (value1 << 8) | (value2 >> 24);
}
unsigned int ror(int32_t value1, int32_t value2){
    return (value1 >> 8) | (value2 <<24);
}

void AddRoundKey(struct secret_Key sk, int round){
    //sk.secretKey[0] = A; sk.secretKey[1] = B;
    //sk.secretKey[2] = C; sk.secretKey[3] = D;
    printf("secretKey : %x %x %x %x\n", sk.secretKey[0], sk.secretKey[1],sk.secretKey[2],sk.secretKey[3]);
    
    uint32_t K0[16], K1[16];
        // K0=K(i,0) K1=K(i,1)
    uint32_t temp;
    uint32_t A = sk.secretKey[0];
    uint32_t B = sk.secretKey[1];
    uint32_t C = sk.secretKey[2];
    uint32_t D = sk.secretKey[3];
    
        for (int i = 1; i <= 16; i++) {
            K0[i - 1] = G(A + C - keyConstant[i - 1]); // G함수 추가
            ak.allkey[2*(i-1)] = K0[i-1];
            
            K1[i - 1] = G(B - D + keyConstant[i - 1]);
            ak.allkey[2*(i-1)+1] = K1[i-1];
            if (i % 2 == 1) {
                temp = rol(B,A);
                A =rol(A,B);
                B = temp;
                //printf("A: %x\n B: %x\n", A,B);
            }
            else{
                temp = ror(D,C);
                C = ror(C,D);
                D = temp;
                //printf("C:%x\n D: %x\n", C,D);
            }
        }
}

int main(){
    printf("enter your secretKey : ");
    scanf("%x %x %x %x",&sk.secretKey[0],&sk.secretKey[1]
          ,&sk.secretKey[2],&sk.secretKey[3]);

    //printf("%d %d %d %d\n", sk.secretKey[0], sk.secretKey[1],sk.secretKey[2],sk.secretKey[3]);
    for(int i = 0; i < 16; i++){
        //16라운드 구현
    }
    AddRoundKey(sk, 16);
    
    for(int i = 0; i < 16; i++){
        printf("%droundkey :  0x%08x 0x%08x\n", i+1, ak.allkey[i], ak.allkey[i+1]);
    }
// 라운드 구현

    return 0;
}
