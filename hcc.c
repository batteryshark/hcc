// Functionality Governing HookCallChain and Links
#include <stdio.h>
#include <sys/types.h>
#include <dlfcn.h>
#include <stdlib.h>

#include "hcc.h"



// Get Next Link Address in Call Chain
void* HCC_GetNextAddr(PHookCallChain call_chain, void* current_link_address){
    PHookLink clink = call_chain->head;
    while(clink != NULL){               
        // We'll check for the current caller to determine the next link, or NULL if 
        // the call originates from the wrapper base.
        if(clink->addr != NULL && current_link_address == NULL){
            //printf("[HCC_GetNextAddr] Calling First Function Address\n");
            return clink->addr;
        }
        if(clink->addr == current_link_address){            
            clink = clink->next;
            break;
        }
        clink = clink->next;
    }
    if(clink == NULL){
        //printf("[HCC_GetNextAddr] Out of Links - Calling Original Function Address\n");
        return call_chain->original_function_address;
    }
    //printf("[HCC_GetNextAddr] Calling Next Function Address\n");
    return clink->addr;
}

void HCC_AddLink(PHookCallChain call_chain, void* new_link_address){
    PHookLink new_link = malloc(sizeof(HookLink));
    new_link->addr = new_link_address;
    new_link->next = call_chain->head;    
    call_chain->head = new_link;
}

void HCC_RemoveLink(PHookCallChain call_chain, void* target_link_address){
    PHookLink clink = call_chain->head;
    PHookLink plink = NULL;
    while(clink != NULL){        
        if(clink->addr == target_link_address){                        
            break;
        }
        plink = clink;
        clink = clink->next;        
    }
    // We didn't find the target so there's nothing to do.
    if(clink == NULL){return;} 
    // If our link was the first, we have to wipe the head and attach the next if there was one.
    if(clink == call_chain->head){
        call_chain->head = clink->next;        
    }
    // If we had a previous link in the chain, it now has to connect to the next link.
    if(plink != NULL){
        plink->next = clink->next;
    }
    // Now we can free our link.
    free(clink);
}

unsigned int HCC_GetNumLinks(PHookCallChain call_chain){
    unsigned int num_links;
    PHookLink clink = call_chain->head;
    
    while(clink != NULL){  
        num_links++;
        clink = clink->next;
    } 
    return num_links;
}

void* HCC_GetFuncAddrAtIndex(PHookCallChain call_chain, int index){
    PHookLink clink = call_chain->head;
    int cur_index = 0;    
    while(clink != NULL){  
        clink = clink->next;
        if(cur_index == index){
            return clink->addr;
        }
        cur_index++;
    }   
    // We didn't find the index or it was invalid.
    return NULL;
}

PHookCallChain HCC_CreateCallChain(void* lib_name, void* func_name){
    PHookCallChain call_chain = calloc(1,sizeof(HookCallChain));
    void* lib_handle = dlopen(lib_name,RTLD_NOW);
    call_chain->original_function_address = dlsym(lib_handle,func_name);
    if(call_chain->original_function_address == NULL){
        printf("Error: %s:%s Not Resolved!\n",(const char*)lib_name,(const char*)func_name);
        exit(-1);
    }
    call_chain->head = NULL;
    return call_chain;
}

void HCC_DestroyCallChain(PHookCallChain call_chain){
    PHookLink clink = call_chain->head;    
    while(clink != NULL){
        PHookLink nlink = clink->next;
        free(clink);
        clink = nlink;
    }    
    free(call_chain);
    return;
}
