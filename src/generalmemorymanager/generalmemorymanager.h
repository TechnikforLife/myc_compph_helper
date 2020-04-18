/**
 *  @file generalmemorymanager.h
 *  @brief Provides a general framework for memorymanagment
 *  @author Dichter nd@nocoffeetech.de
 *
 *
 *
 *	@date 18.04.2020  First Implementation of:
 *						        mem_init,mem_alloc,mem_realloc,
 *                    mem_free,mem_free_all,mem_backbone,
 *                    mem_backinit
 *                    Prototyp of:
 *                    mem_backalloc
 *
 *
 *  @todo add function to allocate memory block and split it into sections
 *
 *  @test ./test_generalmemorymanager.c
 *
 *  @bug No known bugs
 *
 *  @version 0.1
 */

#ifndef GENERALMEMORYMANAGER_H
#define GENERALMEMORYMANAGER_H
#include <stdlib.h>


/**
 * @typedef typedef enum file_error_t
 * @brief Typedefinition of a enum to respresent the \
 * instructions given to mem_backbone
 */
typedef enum mem_instruction_t {
  MEM_INITIALIZE = 0,
  MEM_ALLOCATION = 1,
  MEM_REALLOCATION = 2,
  MEM_FREE = 3,
  MEM_FREEALL = 4
} mem_instruction_t;



/**
 * @fn int mem_init(void);
 * @brief Initializes the memorymanager
 *
 * Calls mem_backbone to initialize the memory manager.
 * In particular the array of
 * pointers to allocated memory blocks gets initialized.
 *
 *
 * @return Pointer to array of Pointers to allocated memory blocks
 *
 */
void* mem_init(void);



/**
 * @fn void* mem_alloc(size_t size);
 * @brief Allocates "size" sized memory block
 *
 * Calls mem_backbone,which calls mem_backalloc to allocate
 * a memory block and make it known to the memory manager.
 *
 * @param size Size of memory block to be allocated (in Byte)
 *
 * @return Pointer to the allocated memory block
 *
 */
void* mem_alloc(size_t size);



/**
 * @fn void* mem_realloc(void* pointer,size_t size);
 * @brief Reallocates memory at "pointer" to size "size"
 *
 * Calls mem_backbone,which calls mem_backrealloc to reallocate
 * the memory block at "pointer" and
 * make it known to the memory manager if the address changed.
 *
 * @param size Size of memory block to be reallocated (in Byte)
 * @param pointer Pointer to existing memory block
 *
 * @return Pointer to the reallocated memory block
 *
 */
void* mem_realloc(void* pointer,size_t size);



/**
 * @fn void mem_free(void* pointer);
 * @brief Frees memory at "pointer"
 *
 * Calls mem_backbone,which calls mem_backfree to free
 * the memory block at "pointer" and
 * make it known to the memory manager.
 *
 * @param pointer Pointer to existing memory block to be freed
 *
 */
void mem_free(void* pointer);



/**
 * @fn void mem_free_all(void);
 * @brief Frees all memory blocks
 *
 * Calls mem_backbone,which calls mem_backfree_all to free
 * all the memory blocks saved in all_mem_blocks.(including itself)
 * Afterwards mem_init needs to be called again to use the memorymanager
 *
 */
void mem_free_all(void);



/**
 * @fn void* mem_backbone(const mem_instruction_t instruction,\
 *                void* pointer, size_t size);
 * @brief Handles all memory interactions (should never be called directly)
 *
 * Handles all memory interactions and hands them off to mem_backinit,
 * mem_backalloc, mem_backrealloc, mem_backfree, mem_backfree_all.
 *
 * @param instruction Tells, which functionality is needed
 * @param pointer2process Pointer to be processed
 * @param size Size of the needed memory block
 *
 * @return Pointer to the (re)allocated memory block \
 *          /array of pointers to all memory blocks
 */
void* mem_backbone(const mem_instruction_t instruction,void* pointer2process,
                   size_t size);



/**
 * @fn void mem_backinit(int* memory_len,int* amount_elements,\
                  void*** all_mem_blocks,int* exitcode);
 * @brief Initializes the array of pointers to allocated memory blocks
 *
 * The array of
 * pointers to allocated memory blocks gets initialized.
 *
 * @param memory_len Current len of all_mem_blocks in the memory \
 *                    in units of sizeof(void*)
 * @param amount_elements Amount of memory blocks currently allocated
 * @param all_mem_blocks Array of all memory block pointers
 * @param exitcode Exitcode address (needed in later error processing)
 */
void mem_backinit(int* memory_len,int* amount_elements,
                  void*** all_mem_blocks,int* exitcode);



/**
 * @fn void* mem_backalloc(int* memory_len,int* amount_elements,
                    void*** all_mem_blocks,int* exitcode,size_t size);
 * @brief Allocates a memory block of size "size"
 *
 * Allocates a memory block of size "size" and stores its address in
 * all_mem_blocks.
 *
 * @param memory_len Current len of all_mem_blocks in the memory \
 *                    in units of sizeof(void*)
 * @param amount_elements Amount of memory blocks currently allocated
 * @param all_mem_blocks Array of all memory block pointers
 * @param exitcode Exitcode address (needed in later error processing)
 * @param size Size of the memory block to be allocated in bytes
 *
 * @return Pointer to the allocated memory block
 */
void* mem_backalloc(int* memory_len,int* amount_elements,
                    void*** all_mem_blocks,int* exitcode,size_t size);






















#endif //ifndef GENERALMEMORYMANAGER_H
