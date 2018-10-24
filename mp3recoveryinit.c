#include"mp3recovery.h"
#include<errno.h>

VOID Mp3RecoveryInit(CHAR *pDev){
  //Appropriate values are set and the array containing block groups is preallocated
  gBlocksize = BLOCK_SIZE;
  gpBlockArray = (UINT1*)calloc(BLOCK_SIZE * BLOCK_GROUP, sizeof(UINT1));

  //Attempts to open given device as read only
  gpPartition = fopen(pDev, "r");

  //If attempt to open device fails the user is notified and the program exits
  if(gpPartition == NULL){
    printf("Cannot open specified device: %s\n", pDev);
    exit(1);
  }

  //Assuming the device has been properly opened for reading the blocks are then read in
  Mp3RecoveryUtilReadBlock();
}
