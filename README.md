# hcc - HookCallChain POC

This library acts as a baseboard shim to allow layers of arbitrary hooks with a fairly simplistic format of callchain context globals to call the next function in the chain, call the original, skip around in the chain, etc.

I've used it several times now to implement filesystem redirection by hooking all the libc file IO path stuff, and then putting additional layers on top of that for custom hardware or other patching.

Anyway, have fun - I'll probably add Windows soon as well.


Example:
```c
// Hooks Required for MicroDog 3.4
int md34_open(const char *pathname, int flags) {
    // If this is a request to open our microdog, we're just going to return with a fake handle.
    if(!strcmp(pathname,MD34_PATH_USB)){
        return MD34_FAKE_FD;
    }    

    open_func_t n_open = HCC_GetNextAddr(open_callchain, md34_open);
    return n_open(pathname, flags);
}
...
HCC_AddLink(open_callchain, md34_open);
```