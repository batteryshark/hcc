# hcc - HookCallChain POC

This library acts as a baseboard shim to allow layers of arbitrary hooks with a fairly simplistic format of callchain context globals to call the next function in the chain, call the original, skip around in the chain, etc.

I've used it several times now to implement filesystem redirection by hooking all the libc file IO path stuff, and then putting additional layers on top of that for custom hardware or other patching.

Anyway, have fun - I'll probably add Windows soon as well.



