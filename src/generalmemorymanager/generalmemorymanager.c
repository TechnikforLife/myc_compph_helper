#include "generalmemorymanager.h"
#include <stdlib.h>
#include <stdio.h>

//macros:
#define ERROR(message) fprintf(stderr,"%s : %s in %s (Line: %d)\n",\
                                (message),__func__,__FILE__,__LINE__)
void* mem_init(void){
      return mem_backbone (MEM_INITIALIZE,NULL,0);
}

void* mem_alloc(size_t size){
      return mem_backbone (MEM_ALLOCATION,NULL,size);
}

void* mem_realloc(void* pointer,size_t size){
      return mem_backbone (MEM_REALLOCATION,pointer,size);
}

void mem_free(void* pointer){
      mem_backbone (MEM_FREE,pointer,0);
      return ;
}

void mem_free_all(void){
      mem_backbone (MEM_FREEALL,NULL,0);
      return;
}

void* mem_backbone(const mem_instruction_t instruction,void* pointer2process,
                   size_t size){
      //Declarations:
      static int memory_len;//length of all_mem_blocks
      static int amount_elements;//actual amount of elements in all_mem_blocks
      static void** all_mem_blocks;//List of all allocated memory blocks
      int exitcode=0;//saves the exitcode of lower tiers to pass it onto the top level
      int try=0;//counts how many tries the action took
      void * retpointer=NULL; //Pointer to be returned

      do{
            //check what todo
            try++;
            switch (instruction)
            {
            case MEM_INITIALIZE:
                  mem_backinit(&memory_len,&amount_elements,
                                                &all_mem_blocks,&exitcode);
                  retpointer=all_mem_blocks;
                  break;
            case MEM_ALLOCATION:

                  break;
            case MEM_REALLOCATION:

                  break;
            case MEM_FREE:

                  break;
            case MEM_FREEALL:

                  break;
            }
      }while(exitcode&&(try<5));
      if(try>=5){
            ERROR("Could not resolve previous Error!");
            exit(exitcode);
      }


      return retpointer;
}

void mem_backinit(int* memory_len,int* amount_elements,
                  void*** all_mem_blocks,int* exitcode){
      *memory_len=1;
      *amount_elements=1;
      *all_mem_blocks=malloc(sizeof (void*)*(*memory_len));
      if(*all_mem_blocks==NULL){
            ERROR("Memory allocation error for all_mem_blocks");
            *exitcode=1;
            return ;
      }
      //include itself
      //(it will stay the first element of itself
      // until mem_free is called)
      (*all_mem_blocks)[0]=*all_mem_blocks;
      return ;
}

void* mem_backalloc(int* memory_len,int* amount_elements,
                    void*** all_mem_blocks,int* exitcode,size_t size){
      return NULL;
}
