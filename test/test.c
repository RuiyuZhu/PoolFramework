//
//  test.c
//  
//
//  Created by Sourgroup on 9/7/17.
//
//


#include "JIMUPoolAPI.h"
int N=10000;
int main(int argc, char ** argv)
{
    int c;
    c=atoi(argv[1]);
    opensocket(c);
    JIMUPoolSetup();

    OblivBit W[66];
    unsigned char bit[32];
    int i;
    for(i=0;i<32;i++)
        bit[i]=i%2;
    (*(Service.Alice_Input))(W,bit,16,Service.ext);
    (*(Service.Bob_Input))(&(W[16]),&(bit[16]),16,(Service.ext));
    
    for(i=0;i<32;i++)
    {
        printf("%u ",(*(Service.Alice_Output))(&(W[i]),(Service.ext)));
    }
    printf("\n");
    for(i=0;i<32;i++)
    {
        printf("%u ",(*(Service.Bob_Output))(&(W[i]),(Service.ext)));
    }
    printf("\n");
    int j;
    unsigned long long t0,t1;
    t0=wallClock();
    for(j=0;j<N;j+=16)
    {
    for(i=32;i<48;i++)
        Pool_Evaluation(&(W[i]),&(W[i-32]),&(W[i-16]),&(Service.And_Pool));
    }
    t1=wallClock();
    printf("GateSpeed: %lf Gates/s in %lf s\n",N*1.0/((t1-t0)*1.0/1000000),((t1-t0)*1.0/1000000));
    for(i=32;i<48;i++)
    {
        printf("%u ",(*(Service.Alice_Output))(&(W[i]),(Service.ext)));
    }
    printf("\n");
    for(i=32;i<48;i++)
    {
        printf("%u ",(*(Service.Bob_Output))(&(W[i]),(Service.ext)));
    }
    printf("\n");
    
    for(i=0;i<100;i++)
        Pool_Evaluation(&(W[34]),&(W[0]),&(W[33]),&(Service.Mux_Pool));
  
    for(i=33;i<65;i++)
    {
        printf("%u ",(*(Service.Bob_Output))(&(W[i]),(Service.ext)));
    }
    printf("\n");
    for(i=33;i<65;i++)
    {
        Service_Not(&(W[i]),&(W[i-33]),&(Service));
    }

    for(i=33;i<65;i++)
    {
        printf("%u ",(*(Service.Bob_Output))(&(W[i-33]),(Service.ext)));
    }
    printf("\n");

    for(i=33;i<65;i++)
    {
        printf("%u ",(*(Service.Bob_Output))(&(W[i]),(Service.ext)));
    }
    printf("\n");
}
