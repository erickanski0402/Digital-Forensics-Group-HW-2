#include"mp3recovery.h"

VOID main(INT4 argc, CHAR** argv){
  //Ensures the user has given a device to read
  if(argc < 2){
    printf("Please include desired device as command line arguments\n");
    return;
  }

  //If a device has been provided it is passed through the initalize function
  CHAR *pDev = argv[1];
  Mp3RecoveryInit(pDev);
}
