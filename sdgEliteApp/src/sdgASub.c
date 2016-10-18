/* file: sdgASub.c
 * Collection of aSub subroutines...
 *----------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <dbDefs.h>
#include <alarm.h>
#include <registryFunction.h>
#include "aSubRecord.h"
#include <epicsExport.h>
#include <stdlib.h>

#define SIZE(x)               (sizeof(x)/sizeof(x[0]))

typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned int uint;


/*------------------------------------------------------------------------------
 * Breaks up a comma delimited waveform into its fields and converts the values. 
 * The input waveform is of the form:
 *  "a1,a2,a3,a4,a5,a6,a7,a8,b1,b2,b3,b4,b5,b6,b7,b8,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u", where
 *  a1-a8	status bit for each channel
 *  b1-b8	delay values for each channel
 *  c		trigger divisor,
 *  d		RF divisor
 *  e,f		error status integers
 *  g,h,i,j Pockels Cell HV and current
 *  k		BWD error status bit 
 *  l1,l2   BWD photodiode threshold level
 *  m       current RF freq
 *  n       last RF freq
 *  o       current trig freq
 *  p       trigger source
 *  q       run mode
 *  r       gating
 *  s       BWD mode
 *  t       BWD signal level
 *  u       firmware version (8-bit hex)
 *----------------------------------------------------------------------------*/

static long asChan( aSubRecord* pr){
    #define N 8
    char* p = (char*)pr->a;
    char tstr[N][16];
    int* pp[N];
    char* pch;
    int i=0; 
    
    pp[ 0]=(int*)pr->vala; pp[ 1]=(int*)pr->valb; pp[ 2]=(int*)pr->valc;
    pp[ 3]=(int*)pr->vald; pp[ 4]=(int*)pr->vale; pp[ 5]=(int*)pr->valf;
    pp[ 6]=(int*)pr->valg; pp[ 7]=(int*)pr->valh;

    pch = strtok(p,",");
    
    for (i=0; i<N; i++){
        if (pch != NULL){
            strncpy( tstr[i],pch,15); tstr[i][15]=0;
            pch = strtok(NULL, ",");            
        }
    
    }
    
    for( i=0;i<N;i++){
        *pp[i]=atoi( tstr[i]);
    }
    
    return(0);
}

/**************************************************************************/

static long asDelay( aSubRecord* pr){
    #define N 8
    char* p = (char*)pr->a;
    char tstr[16][16];
    float* pp[N];
    char* pch;
    int i=0;
    pp[ 0]=(float*)pr->vala; pp[ 1]=(float*)pr->valb; pp[ 2]=(float*)pr->valc;
    pp[ 3]=(float*)pr->vald; pp[ 4]=(float*)pr->vale; pp[ 5]=(float*)pr->valf;
    pp[ 6]=(float*)pr->valg; pp[ 7]=(float*)pr->valh;

    pch = strtok(p,",");

    for (i=0; i<16; i++){
        if (pch != NULL){
            strncpy( tstr[i],pch,15); tstr[i][15]=0;
            pch = strtok(NULL, ",");
        }

    }

    for( i=0;i<8;i++){
        *pp[i]=atof( tstr[i+8]);
    }

    return(0);
}

/**************************************************************************/

static long asInfo( aSubRecord* pr){
    #define N 36
    char* p = (char*)pr->a;
    char tstr[N][16];
    int* ppi[12];
    float* ppf[8];
    char* pch;
    int i=0;
    ppi[0]=(int*)pr->vala; ppi[1]=(int*)pr->valb; ppi[2]=(int*)pr->valc;
    ppi[3]=(int*)pr->vald; ppi[4]=(int*)pr->vali; ppi[5]=(int*)pr->valj;
    ppi[6]=(int*)pr->valk; ppi[7]=(int*)pr->valo; ppi[8]=(int*)pr->valp;
    ppi[9]=(int*)pr->valq; ppi[10]=(int*)pr->valr; ppi[11]=(int*)pr->valt;
    ppf[0]=(float*)pr->vale; ppf[1]=(float*)pr->valf; ppf[2]=(float*)pr->valg; 
    ppf[3]=(float*)pr->valh; ppf[4]=(float*)pr->vall; ppf[5]=(float*)pr->valm;
    ppf[6]=(float*)pr->valn; ppf[7]=(float*)pr->vals;

    pch = strtok(p,",");

    for (i=0; i<N; i++){
        if (pch != NULL){
            strncpy( tstr[i],pch,15); tstr[i][15]=0;
            pch = strtok(NULL, ",");
        }

    }

    for( i=0; i<4; i++){
        *ppi[i] = atoi(tstr[i+16]);
        *ppf[i] = atof(tstr[i+20]);
        *ppi[i+7] = atoi(tstr[i+30]);
    }

    for( i=0; i<3; i++){
        *ppi[i+4] = atoi(tstr[i+24]);
        *ppf[i+4] = atof(tstr[i+27]);
    }
    
    *ppf[7] = atof(tstr[34]);
    *ppi[11] = atoi(tstr[35]);
     
    return(0);
}



epicsRegisterFunction(asChan);
epicsRegisterFunction(asDelay);
epicsRegisterFunction(asInfo);
