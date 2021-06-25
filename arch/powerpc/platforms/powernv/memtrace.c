<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) IBM Corporation, 2014, 2017
 * Anton Blanअक्षरd, Rashmica Gupta.
 */

#घोषणा pr_fmt(fmt) "memtrace: " fmt

#समावेश <linux/bitops.h>
#समावेश <linux/माला.स>
#समावेश <linux/memblock.h>
#समावेश <linux/init.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/fs.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/slab.h>
#समावेश <linux/memory.h>
#समावेश <linux/memory_hotplug.h>
#समावेश <linux/numa.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/debugfs.h>
#समावेश <यंत्र/cacheflush.h>

/* This enables us to keep track of the memory हटाओd from each node. */
काष्ठा memtrace_entry अणु
	व्योम *mem;
	u64 start;
	u64 size;
	u32 nid;
	काष्ठा dentry *dir;
	अक्षर name[16];
पूर्ण;

अटल DEFINE_MUTEX(memtrace_mutex);
अटल u64 memtrace_size;

अटल काष्ठा memtrace_entry *memtrace_array;
अटल अचिन्हित पूर्णांक memtrace_array_nr;


अटल sमाप_प्रकार memtrace_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
			     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा memtrace_entry *ent = filp->निजी_data;

	वापस simple_पढ़ो_from_buffer(ubuf, count, ppos, ent->mem, ent->size);
पूर्ण

अटल पूर्णांक memtrace_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा memtrace_entry *ent = filp->निजी_data;

	अगर (ent->size < vma->vm_end - vma->vm_start)
		वापस -EINVAL;

	अगर (vma->vm_pgoff << PAGE_SHIFT >= ent->size)
		वापस -EINVAL;

	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	वापस remap_pfn_range(vma, vma->vm_start, PHYS_PFN(ent->start) + vma->vm_pgoff,
			       vma->vm_end - vma->vm_start, vma->vm_page_prot);
पूर्ण

अटल स्थिर काष्ठा file_operations memtrace_fops = अणु
	.llseek = शेष_llseek,
	.पढ़ो	= memtrace_पढ़ो,
	.खोलो	= simple_खोलो,
	.mmap   = memtrace_mmap,
पूर्ण;

#घोषणा FLUSH_CHUNK_SIZE SZ_1G
/**
 * flush_dcache_range_chunked(): Write any modअगरied data cache blocks out to
 * memory and invalidate them, in chunks of up to FLUSH_CHUNK_SIZE
 * Does not invalidate the corresponding inकाष्ठाion cache blocks.
 *
 * @start: the start address
 * @stop: the stop address (exclusive)
 * @chunk: the max size of the chunks
 */
अटल व्योम flush_dcache_range_chunked(अचिन्हित दीर्घ start, अचिन्हित दीर्घ stop,
				       अचिन्हित दीर्घ chunk)
अणु
	अचिन्हित दीर्घ i;

	क्रम (i = start; i < stop; i += chunk) अणु
		flush_dcache_range(i, min(stop, i + chunk));
		cond_resched();
	पूर्ण
पूर्ण

अटल व्योम memtrace_clear_range(अचिन्हित दीर्घ start_pfn,
				 अचिन्हित दीर्घ nr_pages)
अणु
	अचिन्हित दीर्घ pfn;

	/* As HIGHMEM करोes not apply, use clear_page() directly. */
	क्रम (pfn = start_pfn; pfn < start_pfn + nr_pages; pfn++) अणु
		अगर (IS_ALIGNED(pfn, PAGES_PER_SECTION))
			cond_resched();
		clear_page(__va(PFN_PHYS(pfn)));
	पूर्ण
	/*
	 * Beक्रमe we go ahead and use this range as cache inhibited range
	 * flush the cache.
	 */
	flush_dcache_range_chunked((अचिन्हित दीर्घ)pfn_to_kaddr(start_pfn),
				   (अचिन्हित दीर्घ)pfn_to_kaddr(start_pfn + nr_pages),
				   FLUSH_CHUNK_SIZE);
पूर्ण

अटल u64 memtrace_alloc_node(u32 nid, u64 size)
अणु
	स्थिर अचिन्हित दीर्घ nr_pages = PHYS_PFN(size);
	अचिन्हित दीर्घ pfn, start_pfn;
	काष्ठा page *page;

	/*
	 * Trace memory needs to be aligned to the size, which is guaranteed
	 * by alloc_contig_pages().
	 */
	page = alloc_contig_pages(nr_pages, GFP_KERNEL | __GFP_THISNODE |
				  __GFP_NOWARN, nid, शून्य);
	अगर (!page)
		वापस 0;
	start_pfn = page_to_pfn(page);

	/*
	 * Clear the range जबतक we still have a linear mapping.
	 *
	 * TODO: use __GFP_ZERO with alloc_contig_pages() once supported.
	 */
	memtrace_clear_range(start_pfn, nr_pages);

	/*
	 * Set pages PageOffline(), to indicate that nobody (e.g., hibernation,
	 * dumping, ...) should be touching these pages.
	 */
	क्रम (pfn = start_pfn; pfn < start_pfn + nr_pages; pfn++)
		__SetPageOffline(pfn_to_page(pfn));

	arch_हटाओ_linear_mapping(PFN_PHYS(start_pfn), size);

	वापस PFN_PHYS(start_pfn);
पूर्ण

अटल पूर्णांक memtrace_init_regions_runसमय(u64 size)
अणु
	u32 nid;
	u64 m;

	memtrace_array = kसुस्मृति(num_online_nodes(),
				माप(काष्ठा memtrace_entry), GFP_KERNEL);
	अगर (!memtrace_array) अणु
		pr_err("Failed to allocate memtrace_array\n");
		वापस -EINVAL;
	पूर्ण

	क्रम_each_online_node(nid) अणु
		m = memtrace_alloc_node(nid, size);

		/*
		 * A node might not have any local memory, so warn but
		 * जारी on.
		 */
		अगर (!m) अणु
			pr_err("Failed to allocate trace memory on node %d\n", nid);
			जारी;
		पूर्ण

		pr_info("Allocated trace memory on node %d at 0x%016llx\n", nid, m);

		memtrace_array[memtrace_array_nr].start = m;
		memtrace_array[memtrace_array_nr].size = size;
		memtrace_array[memtrace_array_nr].nid = nid;
		memtrace_array_nr++;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा dentry *memtrace_debugfs_dir;

अटल पूर्णांक memtrace_init_debugfs(व्योम)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i;

	क्रम (i = 0; i < memtrace_array_nr; i++) अणु
		काष्ठा dentry *dir;
		काष्ठा memtrace_entry *ent = &memtrace_array[i];

		ent->mem = ioremap(ent->start, ent->size);
		/* Warn but जारी on */
		अगर (!ent->mem) अणु
			pr_err("Failed to map trace memory at 0x%llx\n",
				 ent->start);
			ret = -1;
			जारी;
		पूर्ण

		snम_लिखो(ent->name, 16, "%08x", ent->nid);
		dir = debugfs_create_dir(ent->name, memtrace_debugfs_dir);

		ent->dir = dir;
		debugfs_create_file_unsafe("trace", 0600, dir, ent, &memtrace_fops);
		debugfs_create_x64("start", 0400, dir, &ent->start);
		debugfs_create_x64("size", 0400, dir, &ent->size);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक memtrace_मुक्त(पूर्णांक nid, u64 start, u64 size)
अणु
	काष्ठा mhp_params params = अणु .pgprot = PAGE_KERNEL पूर्ण;
	स्थिर अचिन्हित दीर्घ nr_pages = PHYS_PFN(size);
	स्थिर अचिन्हित दीर्घ start_pfn = PHYS_PFN(start);
	अचिन्हित दीर्घ pfn;
	पूर्णांक ret;

	ret = arch_create_linear_mapping(nid, start, size, &params);
	अगर (ret)
		वापस ret;

	क्रम (pfn = start_pfn; pfn < start_pfn + nr_pages; pfn++)
		__ClearPageOffline(pfn_to_page(pfn));

	मुक्त_contig_range(start_pfn, nr_pages);
	वापस 0;
पूर्ण

/*
 * Iterate through the chunks of memory we allocated and attempt to expose
 * them back to the kernel.
 */
अटल पूर्णांक memtrace_मुक्त_regions(व्योम)
अणु
	पूर्णांक i, ret = 0;
	काष्ठा memtrace_entry *ent;

	क्रम (i = memtrace_array_nr - 1; i >= 0; i--) अणु
		ent = &memtrace_array[i];

		/* We have मुक्तd this chunk previously */
		अगर (ent->nid == NUMA_NO_NODE)
			जारी;

		/* Remove from io mappings */
		अगर (ent->mem) अणु
			iounmap(ent->mem);
			ent->mem = 0;
		पूर्ण

		अगर (memtrace_मुक्त(ent->nid, ent->start, ent->size)) अणु
			pr_err("Failed to free trace memory on node %d\n",
				ent->nid);
			ret += 1;
			जारी;
		पूर्ण

		/*
		 * Memory was मुक्तd successfully so clean up references to it
		 * so on reentry we can tell that this chunk was मुक्तd.
		 */
		debugfs_हटाओ_recursive(ent->dir);
		pr_info("Freed trace memory back on node %d\n", ent->nid);
		ent->size = ent->start = ent->nid = NUMA_NO_NODE;
	पूर्ण
	अगर (ret)
		वापस ret;

	/* If all chunks of memory were मुक्तd successfully, reset globals */
	kमुक्त(memtrace_array);
	memtrace_array = शून्य;
	memtrace_size = 0;
	memtrace_array_nr = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक memtrace_enable_set(व्योम *data, u64 val)
अणु
	पूर्णांक rc = -EAGAIN;
	u64 bytes;

	/*
	 * Don't attempt to do anything if size isn't aligned to a memory
	 * block or equal to zero.
	 */
	bytes = memory_block_size_bytes();
	अगर (val & (bytes - 1)) अणु
		pr_err("Value must be aligned with 0x%llx\n", bytes);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&memtrace_mutex);

	/* Free all previously allocated memory. */
	अगर (memtrace_size && memtrace_मुक्त_regions())
		जाओ out_unlock;

	अगर (!val) अणु
		rc = 0;
		जाओ out_unlock;
	पूर्ण

	/* Allocate memory. */
	अगर (memtrace_init_regions_runसमय(val))
		जाओ out_unlock;

	अगर (memtrace_init_debugfs())
		जाओ out_unlock;

	memtrace_size = val;
	rc = 0;
out_unlock:
	mutex_unlock(&memtrace_mutex);
	वापस rc;
पूर्ण

अटल पूर्णांक memtrace_enable_get(व्योम *data, u64 *val)
अणु
	*val = memtrace_size;
	वापस 0;
पूर्ण

DEFINE_SIMPLE_ATTRIBUTE(memtrace_init_fops, memtrace_enable_get,
					memtrace_enable_set, "0x%016llx\n");

अटल पूर्णांक memtrace_init(व्योम)
अणु
	memtrace_debugfs_dir = debugfs_create_dir("memtrace",
						  घातerpc_debugfs_root);

	debugfs_create_file("enable", 0600, memtrace_debugfs_dir,
			    शून्य, &memtrace_init_fops);

	वापस 0;
पूर्ण
machine_device_initcall(घातernv, memtrace_init);
