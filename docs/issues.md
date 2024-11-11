# Today I Learned 
So here's a running list of fun debugging issues we ran into that and wanted to document for future sake. 


## QEMU 4GB of RAM issue 
**Commit:** caf258f64ed5f6ca7645d6c0aec9a6ad365d091f 

**Fix Commit:**  997c7e6317e5c33961f18dfe540eeee77c07f98f

**Issue:** When we initally setup page tables in 32-bit mode we didn't create valid page table entries for all of the memory space as we only setup 4MB of memory.

[x32/src/paging.c#L31](https://github.com/ex4722/chinchilla/blob/ffcedf7c452fdf973693d692e9b44111cbea3983/x32/src/paging.c#L31)
```c 
void * init_page_table(){
    void * p4d = get_new_page();
    void * pud = get_new_page();
    // addresses for 0-2MB 
    void * pmd_1 = get_new_page();
    // addresses for 2MB-4MB
    void * pmd_2 = get_new_page();

    WRITE64(pgdir, PG_ENTRY(p4d));
    WRITE64(p4d, PG_ENTRY(pud));
    WRITE64(pud, PG_ENTRY(pmd_1));
    WRITE64(pud+sizeof(u64), PG_ENTRY(pmd_2));

    // map first 2MB of pages 
    for(u64 addr = 0, idx = 0; addr < TWO_M; addr+= PAGE_SIZE, idx+= 8){
        WRITE64(pmd_1+idx, PG_ENTRY(addr));
    }
    // map the next 2MB of memory
    for(u64 addr = TWO_M, idx = 0; addr < TWO_M*2; addr+= PAGE_SIZE, idx+= 8){
        WRITE64(pmd_2+idx, PG_ENTRY(addr));
    }

    return pgdir;
}
```
Once we entered 64-bit mode we ended up accessin more memory than 4MB when we try to initialize the page_structs when looping over all the entires of multiboot memory at [x64/src/buddy.c#init_memory](https://github.com/ex4722/chinchilla/blob/cc8707def4f926e0981c55d7c3fefd1033c934e0/x64/src/buddy.c#L92)
This triggers a page fault of some sort as we try to access memory outside the 4MB range but don't have valid page table entires setup for it.

*Solution: * 
Cry. Major skill issue. Instead of trying to figure out how to setup paging without a dynamic memory allocator we just use block addressing. Block addressing allows us to increase the size of each entry page table entry so they address a gigabyte of memory instead of just a page. This allows us to index the entire memory space with even less page table entries so we end up saving even more memory.
