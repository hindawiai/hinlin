<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/mman.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/percpu.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/swap.h>
#समावेश <linux/vmस्थिति.स>
#समावेश <linux/atomic.h>
#समावेश <linux/vदो_स्मृति.h>
#अगर_घोषित CONFIG_CMA
#समावेश <linux/cma.h>
#पूर्ण_अगर
#समावेश <यंत्र/page.h>
#समावेश "internal.h"

व्योम __attribute__((weak)) arch_report_meminfo(काष्ठा seq_file *m)
अणु
पूर्ण

अटल व्योम show_val_kb(काष्ठा seq_file *m, स्थिर अक्षर *s, अचिन्हित दीर्घ num)
अणु
	seq_put_decimal_ull_width(m, s, num << (PAGE_SHIFT - 10), 8);
	seq_ग_लिखो(m, " kB\n", 4);
पूर्ण

अटल पूर्णांक meminfo_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा sysinfo i;
	अचिन्हित दीर्घ committed;
	दीर्घ cached;
	दीर्घ available;
	अचिन्हित दीर्घ pages[NR_LRU_LISTS];
	अचिन्हित दीर्घ sreclaimable, sunreclaim;
	पूर्णांक lru;

	si_meminfo(&i);
	si_swapinfo(&i);
	committed = vm_memory_committed();

	cached = global_node_page_state(NR_खाता_PAGES) -
			total_swapcache_pages() - i.bufferram;
	अगर (cached < 0)
		cached = 0;

	क्रम (lru = LRU_BASE; lru < NR_LRU_LISTS; lru++)
		pages[lru] = global_node_page_state(NR_LRU_BASE + lru);

	available = si_mem_available();
	sreclaimable = global_node_page_state_pages(NR_SLAB_RECLAIMABLE_B);
	sunreclaim = global_node_page_state_pages(NR_SLAB_UNRECLAIMABLE_B);

	show_val_kb(m, "MemTotal:       ", i.totalram);
	show_val_kb(m, "MemFree:        ", i.मुक्तram);
	show_val_kb(m, "MemAvailable:   ", available);
	show_val_kb(m, "Buffers:        ", i.bufferram);
	show_val_kb(m, "Cached:         ", cached);
	show_val_kb(m, "SwapCached:     ", total_swapcache_pages());
	show_val_kb(m, "Active:         ", pages[LRU_ACTIVE_ANON] +
					   pages[LRU_ACTIVE_खाता]);
	show_val_kb(m, "Inactive:       ", pages[LRU_INACTIVE_ANON] +
					   pages[LRU_INACTIVE_खाता]);
	show_val_kb(m, "Active(anon):   ", pages[LRU_ACTIVE_ANON]);
	show_val_kb(m, "Inactive(anon): ", pages[LRU_INACTIVE_ANON]);
	show_val_kb(m, "Active(file):   ", pages[LRU_ACTIVE_खाता]);
	show_val_kb(m, "Inactive(file): ", pages[LRU_INACTIVE_खाता]);
	show_val_kb(m, "Unevictable:    ", pages[LRU_UNEVICTABLE]);
	show_val_kb(m, "Mlocked:        ", global_zone_page_state(NR_MLOCK));

#अगर_घोषित CONFIG_HIGHMEM
	show_val_kb(m, "HighTotal:      ", i.totalhigh);
	show_val_kb(m, "HighFree:       ", i.मुक्तhigh);
	show_val_kb(m, "LowTotal:       ", i.totalram - i.totalhigh);
	show_val_kb(m, "LowFree:        ", i.मुक्तram - i.मुक्तhigh);
#पूर्ण_अगर

#अगर_अघोषित CONFIG_MMU
	show_val_kb(m, "MmapCopy:       ",
		    (अचिन्हित दीर्घ)atomic_दीर्घ_पढ़ो(&mmap_pages_allocated));
#पूर्ण_अगर

	show_val_kb(m, "SwapTotal:      ", i.totalswap);
	show_val_kb(m, "SwapFree:       ", i.मुक्तswap);
	show_val_kb(m, "Dirty:          ",
		    global_node_page_state(NR_खाता_सूचीTY));
	show_val_kb(m, "Writeback:      ",
		    global_node_page_state(NR_WRITEBACK));
	show_val_kb(m, "AnonPages:      ",
		    global_node_page_state(NR_ANON_MAPPED));
	show_val_kb(m, "Mapped:         ",
		    global_node_page_state(NR_खाता_MAPPED));
	show_val_kb(m, "Shmem:          ", i.sharedram);
	show_val_kb(m, "KReclaimable:   ", sreclaimable +
		    global_node_page_state(NR_KERNEL_MISC_RECLAIMABLE));
	show_val_kb(m, "Slab:           ", sreclaimable + sunreclaim);
	show_val_kb(m, "SReclaimable:   ", sreclaimable);
	show_val_kb(m, "SUnreclaim:     ", sunreclaim);
	seq_म_लिखो(m, "KernelStack:    %8lu kB\n",
		   global_node_page_state(NR_KERNEL_STACK_KB));
#अगर_घोषित CONFIG_SHADOW_CALL_STACK
	seq_म_लिखो(m, "ShadowCallStack:%8lu kB\n",
		   global_node_page_state(NR_KERNEL_SCS_KB));
#पूर्ण_अगर
	show_val_kb(m, "PageTables:     ",
		    global_node_page_state(NR_PAGETABLE));

	show_val_kb(m, "NFS_Unstable:   ", 0);
	show_val_kb(m, "Bounce:         ",
		    global_zone_page_state(NR_BOUNCE));
	show_val_kb(m, "WritebackTmp:   ",
		    global_node_page_state(NR_WRITEBACK_TEMP));
	show_val_kb(m, "CommitLimit:    ", vm_commit_limit());
	show_val_kb(m, "Committed_AS:   ", committed);
	seq_म_लिखो(m, "VmallocTotal:   %8lu kB\n",
		   (अचिन्हित दीर्घ)VMALLOC_TOTAL >> 10);
	show_val_kb(m, "VmallocUsed:    ", vदो_स्मृति_nr_pages());
	show_val_kb(m, "VmallocChunk:   ", 0ul);
	show_val_kb(m, "Percpu:         ", pcpu_nr_pages());

#अगर_घोषित CONFIG_MEMORY_FAILURE
	seq_म_लिखो(m, "HardwareCorrupted: %5lu kB\n",
		   atomic_दीर्घ_पढ़ो(&num_poisoned_pages) << (PAGE_SHIFT - 10));
#पूर्ण_अगर

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
	show_val_kb(m, "AnonHugePages:  ",
		    global_node_page_state(NR_ANON_THPS));
	show_val_kb(m, "ShmemHugePages: ",
		    global_node_page_state(NR_SHMEM_THPS));
	show_val_kb(m, "ShmemPmdMapped: ",
		    global_node_page_state(NR_SHMEM_PMDMAPPED));
	show_val_kb(m, "FileHugePages:  ",
		    global_node_page_state(NR_खाता_THPS));
	show_val_kb(m, "FilePmdMapped:  ",
		    global_node_page_state(NR_खाता_PMDMAPPED));
#पूर्ण_अगर

#अगर_घोषित CONFIG_CMA
	show_val_kb(m, "CmaTotal:       ", totalcma_pages);
	show_val_kb(m, "CmaFree:        ",
		    global_zone_page_state(NR_FREE_CMA_PAGES));
#पूर्ण_अगर

	hugetlb_report_meminfo(m);

	arch_report_meminfo(m);

	वापस 0;
पूर्ण

अटल पूर्णांक __init proc_meminfo_init(व्योम)
अणु
	proc_create_single("meminfo", 0, शून्य, meminfo_proc_show);
	वापस 0;
पूर्ण
fs_initcall(proc_meminfo_init);
