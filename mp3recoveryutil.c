#include"mp3recovery.h"

INT4 Mp3RecoveryUtilReadBlock(){
  //Total blocks in partition is read in from primary super block
  UINT4 numBlocks = Mp3RecoveryUtilGetTotalBlocks();
  UINT8 mp3Byte = 0;
  //Moves the file pointer to the beginning of the device
  fseek(gpPartition, 0, SEEK_SET);

  UINT2 currentGroup;
  //Iterates through every block group calculated to be on the device
  for(currentGroup = 0; currentGroup < (numBlocks / (BLOCK_GROUP)); currentGroup++){
    //Reads an entire block group into the array
    fread(gpBlockArray, BLOCK_SIZE * BLOCK_GROUP, 1, gpPartition);
    //Passes the block group being searched in to determine if there is an MP3 file located in it
    mp3Byte = Mp3RecoveryUtilCheckForTag(currentGroup);
  }
}

INT8 Mp3RecoveryUtilCheckForTag(UINT4 currentGroup){
  UINT4 currentBlock;
  //Reads the first four bytes in each block in the group
  for(currentBlock = 0; currentBlock < (BLOCK_GROUP); currentBlock++){
    UINT4 currentByte = BLOCK_SIZE * currentBlock;
    //If the proper values are found in the right order it is more or less safe to assume an ID3 tag has been located
    if(gpBlockArray[currentByte] == ID_1 && gpBlockArray[(currentByte) + 1] == ID_2 && gpBlockArray[currentByte + 2] == ID_3 && (gpBlockArray[currentByte + 3] == ID_4_v3 || gpBlockArray[currentByte + 3] == ID_4_v4)){
      //Byte address is calculated and printed for the user
      printf("Mp3 ID3 tag found at block address: %02x\n", (BLOCK_GROUP * BLOCK_SIZE * currentGroup + currentByte));
    }
  }

  return BLOCK_FAILURE;
}

UINT4 Mp3RecoveryUtilGetTotalBlocks(){
  UINT4 numBlocks = 0;
  //Seeks the position in the primary superblock where the value of the total blocks is stored
  fseek(gpPartition, 1028, SEEK_SET);
  //Reads the 4 byte value
  fread(&numBlocks, 1, 4, gpPartition);
  //returns it for use
  return numBlocks;
}
