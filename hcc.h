#ifndef __HCC_H
#define __HCC_H

typedef struct _HOOK_LINK{
    void* addr; // Our Calling Address
    void* next; // Pointer to Next Hook Link
}HookLink,*PHookLink;

typedef struct _HOOK_CALL_CHAIN{
    PHookLink head;
    void* original_function_address;
}HookCallChain,*PHookCallChain;


void* HCC_GetNextAddr(PHookCallChain call_chain, void* current_link_address);
void HCC_AddLink(PHookCallChain call_chain, void* new_link_address);
void HCC_RemoveLink(PHookCallChain call_chain, void* target_link_address);
unsigned int HCC_GetNumLinks(PHookCallChain call_chain);
void* HCC_GetFuncAddrAtIndex(PHookCallChain call_chain, int index);
PHookCallChain HCC_CreateCallChain(void* lib_name, void* func_name);
void HCC_DestroyCallChain(PHookCallChain call_chain);


#endif