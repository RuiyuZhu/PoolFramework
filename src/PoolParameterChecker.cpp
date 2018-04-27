#include <stdio.h>
#include <math.h>
#include <gmp.h>
#include <stdlib.h>
mpq_t zero,one;
void Cmn(mpq_t dst,long long m,long long n)
{
    mpq_set_ui(dst,1,1);
    mpq_t x;//m
    mpq_t y;//1
    mpq_inits(x,y,NULL);
    mpq_set_ui(x,m,1);
    mpq_set_ui(y,1,1);
    
    for(long long i=0;i<n;i++)
    {
        mpq_mul(dst,dst,x);
        mpq_div(dst,dst,y);
        mpq_sub(x,x,one);
        mpq_add(y,y,one);
    }
}
bool Checker(long long PoolSize,double r,long long BucketSize,long long s)
{
    mpq_t p;
    mpq_t p0,p1,tr;
    mpq_t base;
    mpq_inits(zero,one,p,p0,p1,tr,base,NULL);
    mpq_set_ui(zero,0,1);
    mpq_set_ui(one,1,1);
    mpq_set_ui(p,1,1);
    mpq_div_2exp(p0,one,s);
    mpq_set_d(tr,r);
    mpq_sub(tr,one,tr);
    long long UpperB=40/(log2(1-r)*-1);
    mpq_t rate[UpperB+1];
    for(long long i=0;i<BucketSize;i++)
    {
        mpq_init(rate[i]);
        mpq_set_ui(rate[i],0,1);
    }
    Cmn(base,PoolSize,BucketSize);
    for(long long i=BucketSize;i<UpperB+1;i++)
    {
        mpq_init(rate[i]);
        mpq_set_ui(rate[i],0,1);
        for(long long j=1;j<BucketSize;j++)
        {
         //   rate[i]+=rate[j]*Cmn(PoolSize-i,i-j)*Cmn(i,BucketSize-(i-j));
            mpq_t tmp1,tmp2,tmp3;
            mpq_inits(tmp1,tmp2,tmp3,NULL);
            
            Cmn(tmp1,PoolSize-i,BucketSize-j);
            Cmn(tmp2,i,j);
            mpq_mul(tmp3,tmp1,tmp2);
            mpq_mul(tmp3,tmp3,rate[i-j]);
            mpq_add(rate[i],rate[i],tmp3);
            mpq_clear(tmp1);
            mpq_clear(tmp2);
            mpq_clear(tmp3);
        }
        mpq_t tmp,base1;
        mpq_inits(tmp,base1,NULL);
        Cmn(tmp,i,BucketSize);
        Cmn(base1,PoolSize-i,BucketSize);
        mpq_sub(base1,base,base1);
        mpq_add(rate[i],rate[i],tmp);
        mpq_clear(tmp);
        mpq_div(rate[i],rate[i],base1);
    }
    for(long long i=0;i<UpperB;i++)
    {
        //p1=p*rate[i]
        mpq_mul(p1,p,rate[i]);
        if(mpq_cmp(p1,p0)>=0)
            return false;
        //p=p*(1-r);
        mpq_mul(p,p,tr);
    }
    return true;
}
int main(int argc, char**argv)
{
    long long PoolSize=atoi(argv[1]);
    double r=atof(argv[2]);
    long long BucketSize=atoi(argv[3]);
    printf("%d\n",Checker(PoolSize,r,BucketSize,40));
}
