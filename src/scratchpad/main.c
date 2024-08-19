#include <stdio.h>
#include <stdalign.h>

typedef struct {
    int value; // aligns on a 4-byte boundary. There will be 28 bytes of padding between value and alignas
    alignas(32) char alignedMemory[32]; // assuming a 32 byte friendly cache alignment
} cacheFriendly; // this struct will be 32-byte aligned because alignedMemory is 32-byte aligned and is the largest alignment specified in the struct


typedef struct {
    int value; // aligns on a 4-byte boundary. There will be 28 bytes of padding between value and alignas
    alignas(16) char alignedMemory[16]; // assuming a 32 byte friendly cache alignment
} cacheFriendly16; // this struct will be 32-byte aligned because alignedMemory is 32-byte aligned and is the largest alignment specified in the struct

int main()
{

    cacheFriendly a;
    cacheFriendly16 b;

    printf("sizeof(cacheFriendly): %ld\n", sizeof(cacheFriendly)); // 4 bytes for int value + 32 bytes for alignedMemory[] + padding to ensure  alignment
    printf("alignof(cacheFriendly): %ld\n", alignof(cacheFriendly)); // 32 because alignedMemory[] is aligned on a 32-byte boundary
    printf("sizeof(cacheFriendly16): %ld\n", sizeof(cacheFriendly16)); // 4 bytes for int value + 32 bytes for alignedMemory[] + padding to ensure  alignment
    printf("alignof(cacheFriendly16): %ld\n", alignof(cacheFriendly16)); // 32 because alignedMemory[] is aligned on a 32-byte boundary

}