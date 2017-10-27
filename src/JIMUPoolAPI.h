//
//  JIMUPoolAPI.h
//  
//
//  Created by Sourgroup on 9/25/17.
//


#ifndef JIMUPoolAPI_h
#define JIMUPoolAPI_h
#include"PoolScheme.h"
#include "PoolWarpper.h"

/*! \file JIMUPoolAPI.h */


ServiceConfig Service; /**< The global Service variable */
uint64_t L; /**< Width of the Mux gadget*/

#define And_Pool_Size 1024 /**< AndPool Parameter*/
#define And_Pool_BufferSize 1024 /**< AndPool Parameter*/
#define And_Pool_Checkrate 0.15 /**< AndPool Parameter*/
#define And_Pool_BucketSize 4 /**< AndPool Parameter*/

#define Mux_Width 32 /**< MuxPool Parameter*/
#define Mux_Pool_Size 1024 /**< MuxPool Parameter*/
#define Mux_Pool_BufferSize 1024 /**< MuxPool Parameter*/
#define Mux_Pool_Checkrate 0.15 /**< MuxPool Parameter*/
#define Mux_Pool_BucketSize 4 /**< MuxPool Parameter*/

/*! \fn void JIMUPoolSetup()
 \brief Setup Warpper, detailed configurations are in the macros
 */
static void JIMUPoolSetup()
{
    block key=_mm_set_epi32(1,2,3,4);
    SetupService(&Service,
                 Extsize,
                 Extsetup,
                 Alice_Input_For_Service,
                 Bob_Input_For_Service,
                 Alice_Output_For_Service,
                 Bob_Output_For_Service,
                 Xor_For_Pool,
                 Not_For_Pool);
    L=Mux_Width;
    Service.Mux_Pool.ext[1]=&L;
    SetupPool(&(Service.And_Pool),And_Pool_Size,And_Pool_BufferSize,And_Pool_Checkrate,And_Pool_BucketSize,And_Gate_Pointer_Size,And_Bucket_Pointer_Size,1024,key,
              Batch_Gates_Generation_For_And_Pool,
              Gate_Check_For_And_Pool,
              Gate_Copy_For_And_Pool,
              Bucket_Build_For_And_Pool,
              Evaluation_For_And_Pool,
              Malloc_Gate_Pointer_For_And_Pool,
              Malloc_Bucket_Pointer_For_And_Pool,
              Refresh_Seed);
    SetupPool(&(Service.Mux_Pool),Mux_Pool_Size,Mux_Pool_BufferSize,Mux_Pool_Checkrate,Mux_Pool_BucketSize,Mux_Gate_Pointer_Size,Mux_Bucket_Pointer_Size,1024,key,
              Batch_Gates_Generation_For_Mux_Pool,
              Gate_Check_For_Mux_Pool,
              Gate_Copy_For_Mux_Pool,
              Bucket_Build_For_Mux_Pool,
              Evaluation_For_Mux_Pool,
              Malloc_Gate_Pointer_For_Mux_Pool,
              Malloc_Bucket_Pointer_For_Mux_Pool,
              Refresh_Seed);
}


/*! \fn  void JIMUFileScanner(FILE *F,OblivBit *W)
 \brief File Scanner, scan a file and excute the documented circuit
 \param F the file pointer
 \param W an array of OblivBits, needs to be allocated, it must contain enough entries for the circuit in the file to use.
 */
static void JIMUFileScanner(FILE *F,OblivBit *W)
{
    int Ngate,Nwire;
    int Ninputx,Ninputy,Noutput;
    fscanf(F,"%d %d",&Ngate,&Nwire);
    fscanf(F,"%d %d %d",&Ninputx,&Ninputy,&Noutput);
  
    int Ow,i;
    int nin,nout,lw,rw;
    char name[4];
    for(i=0;i<Ngate;i++)
    {
        fscanf(F,"%d %d ",&nin,&nout);
        if(nin==1)
            fscanf(F,"%d %d %s",&lw,&Ow,name);
        else fscanf(F,"%d %d %d %s",&lw,&rw,&Ow,name);
        if(strcmp(name,"AND")==0)
            Pool_Evaluation(&(W[Ow]),&(W[lw]),&(W[rw]),&(Service.And_Pool));
        if(strcmp(name,"XOR")==0)
            (*(Service.Xor)) (&(W[Ow]),&(W[lw]),&(W[rw]),Service.ext);
        if(strcmp(name,"INV")==0)
            (*(Service.Not))(&(W[Ow]),&(W[lw]),Service.ext);
        lw=-1;
        rw=-1;
        Ow=-1;
    }
}
#endif /* JIMUPoolAPI_h */
