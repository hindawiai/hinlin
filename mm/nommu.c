<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/mm/nommu.c
 *
 *  Replacement code क्रम mm functions to support CPU's that don't
 *  have any क्रमm of memory management unit (thus no भव memory).
 *
 *  See Documentation/admin-guide/mm/nommu-mmap.rst
 *
 *  Copyright (c) 2004-2008 David Howells <dhowells@redhat.com>
 *  Copyright (c) 2000-2003 David McCullough <davidm@snapgear.com>
 *  Copyright (c) 2000-2001 D Jeff Dionne <jeff@uClinux.org>
 *  Copyright (c) 2002      Greg Ungerer <gerg@snapgear.com>
 *  Copyright (c) 2007-2010 Paul Mundt <lethal@linux-sh.org>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/export.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/vmacache.h>
#समावेश <linux/mman.h>
#समावेश <linux/swap.h>
#समावेश <linux/file.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/compiler.h>
#समावेश <linux/mount.h>
#समावेश <linux/personality.h>
#समावेश <linux/security.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/audit.h>
#समावेश <linux/prपूर्णांकk.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश "internal.h"

व्योम *high_memory;
EXPORT_SYMBOL(high_memory);
काष्ठा page *mem_map;
अचिन्हित दीर्घ max_mapnr;
EXPORT_SYMBOL(max_mapnr);
अचिन्हित दीर्घ highest_memmap_pfn;
पूर्णांक sysctl_nr_trim_pages = CONFIG_NOMMU_INITIAL_TRIM_EXCESS;
पूर्णांक heap_stack_gap = 0;

atomic_दीर्घ_t mmap_pages_allocated;

EXPORT_SYMBOL(mem_map);

/* list of mapped, potentially shareable regions */
अटल काष्ठा kmem_cache *vm_region_jar;
काष्ठा rb_root nommu_region_tree = RB_ROOT;
DECLARE_RWSEM(nommu_region_sem);

स्थिर काष्ठा vm_operations_काष्ठा generic_file_vm_ops = अणु
पूर्ण;

/*
 * Return the total memory allocated क्रम this poपूर्णांकer, not
 * just what the caller asked क्रम.
 *
 * Doesn't have to be accurate, i.e. may have races.
 */
अचिन्हित पूर्णांक kobjsize(स्थिर व्योम *objp)
अणु
	काष्ठा page *page;

	/*
	 * If the object we have should not have ksize perक्रमmed on it,
	 * वापस size of 0
	 */
	अगर (!objp || !virt_addr_valid(objp))
		वापस 0;

	page = virt_to_head_page(objp);

	/*
	 * If the allocator sets PageSlab, we know the poपूर्णांकer came from
	 * kदो_स्मृति().
	 */
	अगर (PageSlab(page))
		वापस ksize(objp);

	/*
	 * If it's not a compound page, see अगर we have a matching VMA
	 * region. This test is पूर्णांकentionally करोne in reverse order,
	 * so अगर there's no VMA, we still fall through and hand back
	 * PAGE_SIZE क्रम 0-order pages.
	 */
	अगर (!PageCompound(page)) अणु
		काष्ठा vm_area_काष्ठा *vma;

		vma = find_vma(current->mm, (अचिन्हित दीर्घ)objp);
		अगर (vma)
			वापस vma->vm_end - vma->vm_start;
	पूर्ण

	/*
	 * The ksize() function is only guaranteed to work क्रम poपूर्णांकers
	 * वापसed by kदो_स्मृति(). So handle arbitrary poपूर्णांकers here.
	 */
	वापस page_size(page);
पूर्ण

/**
 * follow_pfn - look up PFN at a user भव address
 * @vma: memory mapping
 * @address: user भव address
 * @pfn: location to store found PFN
 *
 * Only IO mappings and raw PFN mappings are allowed.
 *
 * Returns zero and the pfn at @pfn on success, -ve otherwise.
 */
पूर्णांक follow_pfn(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
	अचिन्हित दीर्घ *pfn)
अणु
	अगर (!(vma->vm_flags & (VM_IO | VM_PFNMAP)))
		वापस -EINVAL;

	*pfn = address >> PAGE_SHIFT;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(follow_pfn);

LIST_HEAD(vmap_area_list);

व्योम vमुक्त(स्थिर व्योम *addr)
अणु
	kमुक्त(addr);
पूर्ण
EXPORT_SYMBOL(vमुक्त);

व्योम *__vदो_स्मृति(अचिन्हित दीर्घ size, gfp_t gfp_mask)
अणु
	/*
	 *  You can't specअगरy __GFP_HIGHMEM with kदो_स्मृति() since kदो_स्मृति()
	 * वापसs only a logical address.
	 */
	वापस kदो_स्मृति(size, (gfp_mask | __GFP_COMP) & ~__GFP_HIGHMEM);
पूर्ण
EXPORT_SYMBOL(__vदो_स्मृति);

व्योम *__vदो_स्मृति_node_range(अचिन्हित दीर्घ size, अचिन्हित दीर्घ align,
		अचिन्हित दीर्घ start, अचिन्हित दीर्घ end, gfp_t gfp_mask,
		pgprot_t prot, अचिन्हित दीर्घ vm_flags, पूर्णांक node,
		स्थिर व्योम *caller)
अणु
	वापस __vदो_स्मृति(size, gfp_mask);
पूर्ण

व्योम *__vदो_स्मृति_node(अचिन्हित दीर्घ size, अचिन्हित दीर्घ align, gfp_t gfp_mask,
		पूर्णांक node, स्थिर व्योम *caller)
अणु
	वापस __vदो_स्मृति(size, gfp_mask);
पूर्ण

अटल व्योम *__vदो_स्मृति_user_flags(अचिन्हित दीर्घ size, gfp_t flags)
अणु
	व्योम *ret;

	ret = __vदो_स्मृति(size, flags);
	अगर (ret) अणु
		काष्ठा vm_area_काष्ठा *vma;

		mmap_ग_लिखो_lock(current->mm);
		vma = find_vma(current->mm, (अचिन्हित दीर्घ)ret);
		अगर (vma)
			vma->vm_flags |= VM_USERMAP;
		mmap_ग_लिखो_unlock(current->mm);
	पूर्ण

	वापस ret;
पूर्ण

व्योम *vदो_स्मृति_user(अचिन्हित दीर्घ size)
अणु
	वापस __vदो_स्मृति_user_flags(size, GFP_KERNEL | __GFP_ZERO);
पूर्ण
EXPORT_SYMBOL(vदो_स्मृति_user);

काष्ठा page *vदो_स्मृति_to_page(स्थिर व्योम *addr)
अणु
	वापस virt_to_page(addr);
पूर्ण
EXPORT_SYMBOL(vदो_स्मृति_to_page);

अचिन्हित दीर्घ vदो_स्मृति_to_pfn(स्थिर व्योम *addr)
अणु
	वापस page_to_pfn(virt_to_page(addr));
पूर्ण
EXPORT_SYMBOL(vदो_स्मृति_to_pfn);

दीर्घ vपढ़ो(अक्षर *buf, अक्षर *addr, अचिन्हित दीर्घ count)
अणु
	/* Don't allow overflow */
	अगर ((अचिन्हित दीर्घ) buf + count < count)
		count = -(अचिन्हित दीर्घ) buf;

	स_नकल(buf, addr, count);
	वापस count;
पूर्ण

/*
 *	vदो_स्मृति  -  allocate भवly contiguous memory
 *
 *	@size:		allocation size
 *
 *	Allocate enough pages to cover @size from the page level
 *	allocator and map them पूर्णांकo contiguous kernel भव space.
 *
 *	For tight control over page level allocator and protection flags
 *	use __vदो_स्मृति() instead.
 */
व्योम *vदो_स्मृति(अचिन्हित दीर्घ size)
अणु
       वापस __vदो_स्मृति(size, GFP_KERNEL | __GFP_HIGHMEM);
पूर्ण
EXPORT_SYMBOL(vदो_स्मृति);

/*
 *	vzalloc - allocate भवly contiguous memory with zero fill
 *
 *	@size:		allocation size
 *
 *	Allocate enough pages to cover @size from the page level
 *	allocator and map them पूर्णांकo contiguous kernel भव space.
 *	The memory allocated is set to zero.
 *
 *	For tight control over page level allocator and protection flags
 *	use __vदो_स्मृति() instead.
 */
व्योम *vzalloc(अचिन्हित दीर्घ size)
अणु
	वापस __vदो_स्मृति(size, GFP_KERNEL | __GFP_HIGHMEM | __GFP_ZERO);
पूर्ण
EXPORT_SYMBOL(vzalloc);

/**
 * vदो_स्मृति_node - allocate memory on a specअगरic node
 * @size:	allocation size
 * @node:	numa node
 *
 * Allocate enough pages to cover @size from the page level
 * allocator and map them पूर्णांकo contiguous kernel भव space.
 *
 * For tight control over page level allocator and protection flags
 * use __vदो_स्मृति() instead.
 */
व्योम *vदो_स्मृति_node(अचिन्हित दीर्घ size, पूर्णांक node)
अणु
	वापस vदो_स्मृति(size);
पूर्ण
EXPORT_SYMBOL(vदो_स्मृति_node);

/**
 * vzalloc_node - allocate memory on a specअगरic node with zero fill
 * @size:	allocation size
 * @node:	numa node
 *
 * Allocate enough pages to cover @size from the page level
 * allocator and map them पूर्णांकo contiguous kernel भव space.
 * The memory allocated is set to zero.
 *
 * For tight control over page level allocator and protection flags
 * use __vदो_स्मृति() instead.
 */
व्योम *vzalloc_node(अचिन्हित दीर्घ size, पूर्णांक node)
अणु
	वापस vzalloc(size);
पूर्ण
EXPORT_SYMBOL(vzalloc_node);

/**
 * vदो_स्मृति_32  -  allocate भवly contiguous memory (32bit addressable)
 *	@size:		allocation size
 *
 *	Allocate enough 32bit PA addressable pages to cover @size from the
 *	page level allocator and map them पूर्णांकo contiguous kernel भव space.
 */
व्योम *vदो_स्मृति_32(अचिन्हित दीर्घ size)
अणु
	वापस __vदो_स्मृति(size, GFP_KERNEL);
पूर्ण
EXPORT_SYMBOL(vदो_स्मृति_32);

/**
 * vदो_स्मृति_32_user - allocate zeroed भवly contiguous 32bit memory
 *	@size:		allocation size
 *
 * The resulting memory area is 32bit addressable and zeroed so it can be
 * mapped to userspace without leaking data.
 *
 * VM_USERMAP is set on the corresponding VMA so that subsequent calls to
 * remap_vदो_स्मृति_range() are permissible.
 */
व्योम *vदो_स्मृति_32_user(अचिन्हित दीर्घ size)
अणु
	/*
	 * We'll have to sort out the ZONE_DMA bits क्रम 64-bit,
	 * but क्रम now this can simply use vदो_स्मृति_user() directly.
	 */
	वापस vदो_स्मृति_user(size);
पूर्ण
EXPORT_SYMBOL(vदो_स्मृति_32_user);

व्योम *vmap(काष्ठा page **pages, अचिन्हित पूर्णांक count, अचिन्हित दीर्घ flags, pgprot_t prot)
अणु
	BUG();
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(vmap);

व्योम vunmap(स्थिर व्योम *addr)
अणु
	BUG();
पूर्ण
EXPORT_SYMBOL(vunmap);

व्योम *vm_map_ram(काष्ठा page **pages, अचिन्हित पूर्णांक count, पूर्णांक node)
अणु
	BUG();
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(vm_map_ram);

व्योम vm_unmap_ram(स्थिर व्योम *mem, अचिन्हित पूर्णांक count)
अणु
	BUG();
पूर्ण
EXPORT_SYMBOL(vm_unmap_ram);

व्योम vm_unmap_aliases(व्योम)
अणु
पूर्ण
EXPORT_SYMBOL_GPL(vm_unmap_aliases);

व्योम मुक्त_vm_area(काष्ठा vm_काष्ठा *area)
अणु
	BUG();
पूर्ण
EXPORT_SYMBOL_GPL(मुक्त_vm_area);

पूर्णांक vm_insert_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
		   काष्ठा page *page)
अणु
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(vm_insert_page);

पूर्णांक vm_map_pages(काष्ठा vm_area_काष्ठा *vma, काष्ठा page **pages,
			अचिन्हित दीर्घ num)
अणु
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(vm_map_pages);

पूर्णांक vm_map_pages_zero(काष्ठा vm_area_काष्ठा *vma, काष्ठा page **pages,
				अचिन्हित दीर्घ num)
अणु
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(vm_map_pages_zero);

/*
 *  sys_brk() क्रम the most part करोesn't need the global kernel
 *  lock, except when an application is करोing something nasty
 *  like trying to un-brk an area that has alपढ़ोy been mapped
 *  to a regular file.  in this हाल, the unmapping will need
 *  to invoke file प्रणाली routines that need the global lock.
 */
SYSCALL_DEFINE1(brk, अचिन्हित दीर्घ, brk)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;

	अगर (brk < mm->start_brk || brk > mm->context.end_brk)
		वापस mm->brk;

	अगर (mm->brk == brk)
		वापस mm->brk;

	/*
	 * Always allow shrinking brk
	 */
	अगर (brk <= mm->brk) अणु
		mm->brk = brk;
		वापस brk;
	पूर्ण

	/*
	 * Ok, looks good - let it rip.
	 */
	flush_icache_user_range(mm->brk, brk);
	वापस mm->brk = brk;
पूर्ण

/*
 * initialise the percpu counter क्रम VM and region record sद_असल
 */
व्योम __init mmap_init(व्योम)
अणु
	पूर्णांक ret;

	ret = percpu_counter_init(&vm_committed_as, 0, GFP_KERNEL);
	VM_BUG_ON(ret);
	vm_region_jar = KMEM_CACHE(vm_region, SLAB_PANIC|SLAB_ACCOUNT);
पूर्ण

/*
 * validate the region tree
 * - the caller must hold the region lock
 */
#अगर_घोषित CONFIG_DEBUG_NOMMU_REGIONS
अटल noअंतरभूत व्योम validate_nommu_regions(व्योम)
अणु
	काष्ठा vm_region *region, *last;
	काष्ठा rb_node *p, *lastp;

	lastp = rb_first(&nommu_region_tree);
	अगर (!lastp)
		वापस;

	last = rb_entry(lastp, काष्ठा vm_region, vm_rb);
	BUG_ON(last->vm_end <= last->vm_start);
	BUG_ON(last->vm_top < last->vm_end);

	जबतक ((p = rb_next(lastp))) अणु
		region = rb_entry(p, काष्ठा vm_region, vm_rb);
		last = rb_entry(lastp, काष्ठा vm_region, vm_rb);

		BUG_ON(region->vm_end <= region->vm_start);
		BUG_ON(region->vm_top < region->vm_end);
		BUG_ON(region->vm_start < last->vm_top);

		lastp = p;
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम validate_nommu_regions(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

/*
 * add a region पूर्णांकo the global tree
 */
अटल व्योम add_nommu_region(काष्ठा vm_region *region)
अणु
	काष्ठा vm_region *pregion;
	काष्ठा rb_node **p, *parent;

	validate_nommu_regions();

	parent = शून्य;
	p = &nommu_region_tree.rb_node;
	जबतक (*p) अणु
		parent = *p;
		pregion = rb_entry(parent, काष्ठा vm_region, vm_rb);
		अगर (region->vm_start < pregion->vm_start)
			p = &(*p)->rb_left;
		अन्यथा अगर (region->vm_start > pregion->vm_start)
			p = &(*p)->rb_right;
		अन्यथा अगर (pregion == region)
			वापस;
		अन्यथा
			BUG();
	पूर्ण

	rb_link_node(&region->vm_rb, parent, p);
	rb_insert_color(&region->vm_rb, &nommu_region_tree);

	validate_nommu_regions();
पूर्ण

/*
 * delete a region from the global tree
 */
अटल व्योम delete_nommu_region(काष्ठा vm_region *region)
अणु
	BUG_ON(!nommu_region_tree.rb_node);

	validate_nommu_regions();
	rb_erase(&region->vm_rb, &nommu_region_tree);
	validate_nommu_regions();
पूर्ण

/*
 * मुक्त a contiguous series of pages
 */
अटल व्योम मुक्त_page_series(अचिन्हित दीर्घ from, अचिन्हित दीर्घ to)
अणु
	क्रम (; from < to; from += PAGE_SIZE) अणु
		काष्ठा page *page = virt_to_page(from);

		atomic_दीर्घ_dec(&mmap_pages_allocated);
		put_page(page);
	पूर्ण
पूर्ण

/*
 * release a reference to a region
 * - the caller must hold the region semaphore क्रम writing, which this releases
 * - the region may not have been added to the tree yet, in which हाल vm_top
 *   will equal vm_start
 */
अटल व्योम __put_nommu_region(काष्ठा vm_region *region)
	__releases(nommu_region_sem)
अणु
	BUG_ON(!nommu_region_tree.rb_node);

	अगर (--region->vm_usage == 0) अणु
		अगर (region->vm_top > region->vm_start)
			delete_nommu_region(region);
		up_ग_लिखो(&nommu_region_sem);

		अगर (region->vm_file)
			fput(region->vm_file);

		/* IO memory and memory shared directly out of the pagecache
		 * from ramfs/पंचांगpfs mustn't be released here */
		अगर (region->vm_flags & VM_MAPPED_COPY)
			मुक्त_page_series(region->vm_start, region->vm_top);
		kmem_cache_मुक्त(vm_region_jar, region);
	पूर्ण अन्यथा अणु
		up_ग_लिखो(&nommu_region_sem);
	पूर्ण
पूर्ण

/*
 * release a reference to a region
 */
अटल व्योम put_nommu_region(काष्ठा vm_region *region)
अणु
	करोwn_ग_लिखो(&nommu_region_sem);
	__put_nommu_region(region);
पूर्ण

/*
 * add a VMA पूर्णांकo a process's mm_काष्ठा in the appropriate place in the list
 * and tree and add to the address space's page tree also अगर not an anonymous
 * page
 * - should be called with mm->mmap_lock held ग_लिखोlocked
 */
अटल व्योम add_vma_to_mm(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा vm_area_काष्ठा *pvma, *prev;
	काष्ठा address_space *mapping;
	काष्ठा rb_node **p, *parent, *rb_prev;

	BUG_ON(!vma->vm_region);

	mm->map_count++;
	vma->vm_mm = mm;

	/* add the VMA to the mapping */
	अगर (vma->vm_file) अणु
		mapping = vma->vm_file->f_mapping;

		i_mmap_lock_ग_लिखो(mapping);
		flush_dcache_mmap_lock(mapping);
		vma_पूर्णांकerval_tree_insert(vma, &mapping->i_mmap);
		flush_dcache_mmap_unlock(mapping);
		i_mmap_unlock_ग_लिखो(mapping);
	पूर्ण

	/* add the VMA to the tree */
	parent = rb_prev = शून्य;
	p = &mm->mm_rb.rb_node;
	जबतक (*p) अणु
		parent = *p;
		pvma = rb_entry(parent, काष्ठा vm_area_काष्ठा, vm_rb);

		/* sort by: start addr, end addr, VMA काष्ठा addr in that order
		 * (the latter is necessary as we may get identical VMAs) */
		अगर (vma->vm_start < pvma->vm_start)
			p = &(*p)->rb_left;
		अन्यथा अगर (vma->vm_start > pvma->vm_start) अणु
			rb_prev = parent;
			p = &(*p)->rb_right;
		पूर्ण अन्यथा अगर (vma->vm_end < pvma->vm_end)
			p = &(*p)->rb_left;
		अन्यथा अगर (vma->vm_end > pvma->vm_end) अणु
			rb_prev = parent;
			p = &(*p)->rb_right;
		पूर्ण अन्यथा अगर (vma < pvma)
			p = &(*p)->rb_left;
		अन्यथा अगर (vma > pvma) अणु
			rb_prev = parent;
			p = &(*p)->rb_right;
		पूर्ण अन्यथा
			BUG();
	पूर्ण

	rb_link_node(&vma->vm_rb, parent, p);
	rb_insert_color(&vma->vm_rb, &mm->mm_rb);

	/* add VMA to the VMA list also */
	prev = शून्य;
	अगर (rb_prev)
		prev = rb_entry(rb_prev, काष्ठा vm_area_काष्ठा, vm_rb);

	__vma_link_list(mm, vma, prev);
पूर्ण

/*
 * delete a VMA from its owning mm_काष्ठा and address space
 */
अटल व्योम delete_vma_from_mm(काष्ठा vm_area_काष्ठा *vma)
अणु
	पूर्णांक i;
	काष्ठा address_space *mapping;
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	काष्ठा task_काष्ठा *curr = current;

	mm->map_count--;
	क्रम (i = 0; i < VMACACHE_SIZE; i++) अणु
		/* अगर the vma is cached, invalidate the entire cache */
		अगर (curr->vmacache.vmas[i] == vma) अणु
			vmacache_invalidate(mm);
			अवरोध;
		पूर्ण
	पूर्ण

	/* हटाओ the VMA from the mapping */
	अगर (vma->vm_file) अणु
		mapping = vma->vm_file->f_mapping;

		i_mmap_lock_ग_लिखो(mapping);
		flush_dcache_mmap_lock(mapping);
		vma_पूर्णांकerval_tree_हटाओ(vma, &mapping->i_mmap);
		flush_dcache_mmap_unlock(mapping);
		i_mmap_unlock_ग_लिखो(mapping);
	पूर्ण

	/* हटाओ from the MM's tree and list */
	rb_erase(&vma->vm_rb, &mm->mm_rb);

	__vma_unlink_list(mm, vma);
पूर्ण

/*
 * destroy a VMA record
 */
अटल व्योम delete_vma(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (vma->vm_ops && vma->vm_ops->बंद)
		vma->vm_ops->बंद(vma);
	अगर (vma->vm_file)
		fput(vma->vm_file);
	put_nommu_region(vma->vm_region);
	vm_area_मुक्त(vma);
पूर्ण

/*
 * look up the first VMA in which addr resides, शून्य अगर none
 * - should be called with mm->mmap_lock at least held पढ़ोlocked
 */
काष्ठा vm_area_काष्ठा *find_vma(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	काष्ठा vm_area_काष्ठा *vma;

	/* check the cache first */
	vma = vmacache_find(mm, addr);
	अगर (likely(vma))
		वापस vma;

	/* trawl the list (there may be multiple mappings in which addr
	 * resides) */
	क्रम (vma = mm->mmap; vma; vma = vma->vm_next) अणु
		अगर (vma->vm_start > addr)
			वापस शून्य;
		अगर (vma->vm_end > addr) अणु
			vmacache_update(addr, vma);
			वापस vma;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(find_vma);

/*
 * find a VMA
 * - we करोn't extend stack VMAs under NOMMU conditions
 */
काष्ठा vm_area_काष्ठा *find_extend_vma(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	वापस find_vma(mm, addr);
पूर्ण

/*
 * expand a stack to a given address
 * - not supported under NOMMU conditions
 */
पूर्णांक expand_stack(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address)
अणु
	वापस -ENOMEM;
पूर्ण

/*
 * look up the first VMA exactly that exactly matches addr
 * - should be called with mm->mmap_lock at least held पढ़ोlocked
 */
अटल काष्ठा vm_area_काष्ठा *find_vma_exact(काष्ठा mm_काष्ठा *mm,
					     अचिन्हित दीर्घ addr,
					     अचिन्हित दीर्घ len)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ end = addr + len;

	/* check the cache first */
	vma = vmacache_find_exact(mm, addr, end);
	अगर (vma)
		वापस vma;

	/* trawl the list (there may be multiple mappings in which addr
	 * resides) */
	क्रम (vma = mm->mmap; vma; vma = vma->vm_next) अणु
		अगर (vma->vm_start < addr)
			जारी;
		अगर (vma->vm_start > addr)
			वापस शून्य;
		अगर (vma->vm_end == end) अणु
			vmacache_update(addr, vma);
			वापस vma;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * determine whether a mapping should be permitted and, अगर so, what sort of
 * mapping we're capable of supporting
 */
अटल पूर्णांक validate_mmap_request(काष्ठा file *file,
				 अचिन्हित दीर्घ addr,
				 अचिन्हित दीर्घ len,
				 अचिन्हित दीर्घ prot,
				 अचिन्हित दीर्घ flags,
				 अचिन्हित दीर्घ pgoff,
				 अचिन्हित दीर्घ *_capabilities)
अणु
	अचिन्हित दीर्घ capabilities, rlen;
	पूर्णांक ret;

	/* करो the simple checks first */
	अगर (flags & MAP_FIXED)
		वापस -EINVAL;

	अगर ((flags & MAP_TYPE) != MAP_PRIVATE &&
	    (flags & MAP_TYPE) != MAP_SHARED)
		वापस -EINVAL;

	अगर (!len)
		वापस -EINVAL;

	/* Careful about overflows.. */
	rlen = PAGE_ALIGN(len);
	अगर (!rlen || rlen > TASK_SIZE)
		वापस -ENOMEM;

	/* offset overflow? */
	अगर ((pgoff + (rlen >> PAGE_SHIFT)) < pgoff)
		वापस -EOVERFLOW;

	अगर (file) अणु
		/* files must support mmap */
		अगर (!file->f_op->mmap)
			वापस -ENODEV;

		/* work out अगर what we've got could possibly be shared
		 * - we support अक्षरdevs that provide their own "memory"
		 * - we support files/blockdevs that are memory backed
		 */
		अगर (file->f_op->mmap_capabilities) अणु
			capabilities = file->f_op->mmap_capabilities(file);
		पूर्ण अन्यथा अणु
			/* no explicit capabilities set, so assume some
			 * शेषs */
			चयन (file_inode(file)->i_mode & S_IFMT) अणु
			हाल S_IFREG:
			हाल S_IFBLK:
				capabilities = NOMMU_MAP_COPY;
				अवरोध;

			हाल S_IFCHR:
				capabilities =
					NOMMU_MAP_सूचीECT |
					NOMMU_MAP_READ |
					NOMMU_MAP_WRITE;
				अवरोध;

			शेष:
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		/* eliminate any capabilities that we can't support on this
		 * device */
		अगर (!file->f_op->get_unmapped_area)
			capabilities &= ~NOMMU_MAP_सूचीECT;
		अगर (!(file->f_mode & FMODE_CAN_READ))
			capabilities &= ~NOMMU_MAP_COPY;

		/* The file shall have been खोलोed with पढ़ो permission. */
		अगर (!(file->f_mode & FMODE_READ))
			वापस -EACCES;

		अगर (flags & MAP_SHARED) अणु
			/* करो checks क्रम writing, appending and locking */
			अगर ((prot & PROT_WRITE) &&
			    !(file->f_mode & FMODE_WRITE))
				वापस -EACCES;

			अगर (IS_APPEND(file_inode(file)) &&
			    (file->f_mode & FMODE_WRITE))
				वापस -EACCES;

			अगर (locks_verअगरy_locked(file))
				वापस -EAGAIN;

			अगर (!(capabilities & NOMMU_MAP_सूचीECT))
				वापस -ENODEV;

			/* we mustn't privatise shared mappings */
			capabilities &= ~NOMMU_MAP_COPY;
		पूर्ण अन्यथा अणु
			/* we're going to पढ़ो the file पूर्णांकo निजी memory we
			 * allocate */
			अगर (!(capabilities & NOMMU_MAP_COPY))
				वापस -ENODEV;

			/* we करोn't permit a निजी writable mapping to be
			 * shared with the backing device */
			अगर (prot & PROT_WRITE)
				capabilities &= ~NOMMU_MAP_सूचीECT;
		पूर्ण

		अगर (capabilities & NOMMU_MAP_सूचीECT) अणु
			अगर (((prot & PROT_READ)  && !(capabilities & NOMMU_MAP_READ))  ||
			    ((prot & PROT_WRITE) && !(capabilities & NOMMU_MAP_WRITE)) ||
			    ((prot & PROT_EXEC)  && !(capabilities & NOMMU_MAP_EXEC))
			    ) अणु
				capabilities &= ~NOMMU_MAP_सूचीECT;
				अगर (flags & MAP_SHARED) अणु
					pr_warn("MAP_SHARED not completely supported on !MMU\n");
					वापस -EINVAL;
				पूर्ण
			पूर्ण
		पूर्ण

		/* handle executable mappings and implied executable
		 * mappings */
		अगर (path_noexec(&file->f_path)) अणु
			अगर (prot & PROT_EXEC)
				वापस -EPERM;
		पूर्ण अन्यथा अगर ((prot & PROT_READ) && !(prot & PROT_EXEC)) अणु
			/* handle implication of PROT_EXEC by PROT_READ */
			अगर (current->personality & READ_IMPLIES_EXEC) अणु
				अगर (capabilities & NOMMU_MAP_EXEC)
					prot |= PROT_EXEC;
			पूर्ण
		पूर्ण अन्यथा अगर ((prot & PROT_READ) &&
			 (prot & PROT_EXEC) &&
			 !(capabilities & NOMMU_MAP_EXEC)
			 ) अणु
			/* backing file is not executable, try to copy */
			capabilities &= ~NOMMU_MAP_सूचीECT;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* anonymous mappings are always memory backed and can be
		 * निजीly mapped
		 */
		capabilities = NOMMU_MAP_COPY;

		/* handle PROT_EXEC implication by PROT_READ */
		अगर ((prot & PROT_READ) &&
		    (current->personality & READ_IMPLIES_EXEC))
			prot |= PROT_EXEC;
	पूर्ण

	/* allow the security API to have its say */
	ret = security_mmap_addr(addr);
	अगर (ret < 0)
		वापस ret;

	/* looks okay */
	*_capabilities = capabilities;
	वापस 0;
पूर्ण

/*
 * we've determined that we can make the mapping, now translate what we
 * now know पूर्णांकo VMA flags
 */
अटल अचिन्हित दीर्घ determine_vm_flags(काष्ठा file *file,
					अचिन्हित दीर्घ prot,
					अचिन्हित दीर्घ flags,
					अचिन्हित दीर्घ capabilities)
अणु
	अचिन्हित दीर्घ vm_flags;

	vm_flags = calc_vm_prot_bits(prot, 0) | calc_vm_flag_bits(flags);
	/* vm_flags |= mm->def_flags; */

	अगर (!(capabilities & NOMMU_MAP_सूचीECT)) अणु
		/* attempt to share पढ़ो-only copies of mapped file chunks */
		vm_flags |= VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC;
		अगर (file && !(prot & PROT_WRITE))
			vm_flags |= VM_MAYSHARE;
	पूर्ण अन्यथा अणु
		/* overlay a shareable mapping on the backing device or inode
		 * अगर possible - used क्रम अक्षरdevs, ramfs/पंचांगpfs/shmfs and
		 * romfs/cramfs */
		vm_flags |= VM_MAYSHARE | (capabilities & NOMMU_VMFLAGS);
		अगर (flags & MAP_SHARED)
			vm_flags |= VM_SHARED;
	पूर्ण

	/* refuse to let anyone share निजी mappings with this process अगर
	 * it's being traced - otherwise अवरोधpoपूर्णांकs set in it may पूर्णांकerfere
	 * with another untraced process
	 */
	अगर ((flags & MAP_PRIVATE) && current->ptrace)
		vm_flags &= ~VM_MAYSHARE;

	वापस vm_flags;
पूर्ण

/*
 * set up a shared mapping on a file (the driver or fileप्रणाली provides and
 * pins the storage)
 */
अटल पूर्णांक करो_mmap_shared_file(काष्ठा vm_area_काष्ठा *vma)
अणु
	पूर्णांक ret;

	ret = call_mmap(vma->vm_file, vma);
	अगर (ret == 0) अणु
		vma->vm_region->vm_top = vma->vm_region->vm_end;
		वापस 0;
	पूर्ण
	अगर (ret != -ENOSYS)
		वापस ret;

	/* getting -ENOSYS indicates that direct mmap isn't possible (as
	 * opposed to tried but failed) so we can only give a suitable error as
	 * it's not possible to make a निजी copy अगर MAP_SHARED was given */
	वापस -ENODEV;
पूर्ण

/*
 * set up a निजी mapping or an anonymous shared mapping
 */
अटल पूर्णांक करो_mmap_निजी(काष्ठा vm_area_काष्ठा *vma,
			   काष्ठा vm_region *region,
			   अचिन्हित दीर्घ len,
			   अचिन्हित दीर्घ capabilities)
अणु
	अचिन्हित दीर्घ total, poपूर्णांक;
	व्योम *base;
	पूर्णांक ret, order;

	/* invoke the file's mapping function so that it can keep track of
	 * shared mappings on devices or memory
	 * - VM_MAYSHARE will be set अगर it may attempt to share
	 */
	अगर (capabilities & NOMMU_MAP_सूचीECT) अणु
		ret = call_mmap(vma->vm_file, vma);
		अगर (ret == 0) अणु
			/* shouldn't return success if we're not sharing */
			BUG_ON(!(vma->vm_flags & VM_MAYSHARE));
			vma->vm_region->vm_top = vma->vm_region->vm_end;
			वापस 0;
		पूर्ण
		अगर (ret != -ENOSYS)
			वापस ret;

		/* getting an ENOSYS error indicates that direct mmap isn't
		 * possible (as opposed to tried but failed) so we'll try to
		 * make a निजी copy of the data and map that instead */
	पूर्ण


	/* allocate some memory to hold the mapping
	 * - note that this may not वापस a page-aligned address अगर the object
	 *   we're allocating is smaller than a page
	 */
	order = get_order(len);
	total = 1 << order;
	poपूर्णांक = len >> PAGE_SHIFT;

	/* we करोn't want to allocate a घातer-of-2 sized page set */
	अगर (sysctl_nr_trim_pages && total - poपूर्णांक >= sysctl_nr_trim_pages)
		total = poपूर्णांक;

	base = alloc_pages_exact(total << PAGE_SHIFT, GFP_KERNEL);
	अगर (!base)
		जाओ enomem;

	atomic_दीर्घ_add(total, &mmap_pages_allocated);

	region->vm_flags = vma->vm_flags |= VM_MAPPED_COPY;
	region->vm_start = (अचिन्हित दीर्घ) base;
	region->vm_end   = region->vm_start + len;
	region->vm_top   = region->vm_start + (total << PAGE_SHIFT);

	vma->vm_start = region->vm_start;
	vma->vm_end   = region->vm_start + len;

	अगर (vma->vm_file) अणु
		/* पढ़ो the contents of a file पूर्णांकo the copy */
		loff_t fpos;

		fpos = vma->vm_pgoff;
		fpos <<= PAGE_SHIFT;

		ret = kernel_पढ़ो(vma->vm_file, base, len, &fpos);
		अगर (ret < 0)
			जाओ error_मुक्त;

		/* clear the last little bit */
		अगर (ret < len)
			स_रखो(base + ret, 0, len - ret);

	पूर्ण अन्यथा अणु
		vma_set_anonymous(vma);
	पूर्ण

	वापस 0;

error_मुक्त:
	मुक्त_page_series(region->vm_start, region->vm_top);
	region->vm_start = vma->vm_start = 0;
	region->vm_end   = vma->vm_end = 0;
	region->vm_top   = 0;
	वापस ret;

enomem:
	pr_err("Allocation of length %lu from process %d (%s) failed\n",
	       len, current->pid, current->comm);
	show_मुक्त_areas(0, शून्य);
	वापस -ENOMEM;
पूर्ण

/*
 * handle mapping creation क्रम uClinux
 */
अचिन्हित दीर्घ करो_mmap(काष्ठा file *file,
			अचिन्हित दीर्घ addr,
			अचिन्हित दीर्घ len,
			अचिन्हित दीर्घ prot,
			अचिन्हित दीर्घ flags,
			अचिन्हित दीर्घ pgoff,
			अचिन्हित दीर्घ *populate,
			काष्ठा list_head *uf)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा vm_region *region;
	काष्ठा rb_node *rb;
	vm_flags_t vm_flags;
	अचिन्हित दीर्घ capabilities, result;
	पूर्णांक ret;

	*populate = 0;

	/* decide whether we should attempt the mapping, and अगर so what sort of
	 * mapping */
	ret = validate_mmap_request(file, addr, len, prot, flags, pgoff,
				    &capabilities);
	अगर (ret < 0)
		वापस ret;

	/* we ignore the address hपूर्णांक */
	addr = 0;
	len = PAGE_ALIGN(len);

	/* we've determined that we can make the mapping, now translate what we
	 * now know पूर्णांकo VMA flags */
	vm_flags = determine_vm_flags(file, prot, flags, capabilities);

	/* we're going to need to record the mapping */
	region = kmem_cache_zalloc(vm_region_jar, GFP_KERNEL);
	अगर (!region)
		जाओ error_getting_region;

	vma = vm_area_alloc(current->mm);
	अगर (!vma)
		जाओ error_getting_vma;

	region->vm_usage = 1;
	region->vm_flags = vm_flags;
	region->vm_pgoff = pgoff;

	vma->vm_flags = vm_flags;
	vma->vm_pgoff = pgoff;

	अगर (file) अणु
		region->vm_file = get_file(file);
		vma->vm_file = get_file(file);
	पूर्ण

	करोwn_ग_लिखो(&nommu_region_sem);

	/* अगर we want to share, we need to check क्रम regions created by other
	 * mmap() calls that overlap with our proposed mapping
	 * - we can only share with a superset match on most regular files
	 * - shared mappings on अक्षरacter devices and memory backed files are
	 *   permitted to overlap inexactly as far as we are concerned क्रम in
	 *   these हालs, sharing is handled in the driver or fileप्रणाली rather
	 *   than here
	 */
	अगर (vm_flags & VM_MAYSHARE) अणु
		काष्ठा vm_region *pregion;
		अचिन्हित दीर्घ pglen, rpglen, pgend, rpgend, start;

		pglen = (len + PAGE_SIZE - 1) >> PAGE_SHIFT;
		pgend = pgoff + pglen;

		क्रम (rb = rb_first(&nommu_region_tree); rb; rb = rb_next(rb)) अणु
			pregion = rb_entry(rb, काष्ठा vm_region, vm_rb);

			अगर (!(pregion->vm_flags & VM_MAYSHARE))
				जारी;

			/* search क्रम overlapping mappings on the same file */
			अगर (file_inode(pregion->vm_file) !=
			    file_inode(file))
				जारी;

			अगर (pregion->vm_pgoff >= pgend)
				जारी;

			rpglen = pregion->vm_end - pregion->vm_start;
			rpglen = (rpglen + PAGE_SIZE - 1) >> PAGE_SHIFT;
			rpgend = pregion->vm_pgoff + rpglen;
			अगर (pgoff >= rpgend)
				जारी;

			/* handle inexactly overlapping matches between
			 * mappings */
			अगर ((pregion->vm_pgoff != pgoff || rpglen != pglen) &&
			    !(pgoff >= pregion->vm_pgoff && pgend <= rpgend)) अणु
				/* new mapping is not a subset of the region */
				अगर (!(capabilities & NOMMU_MAP_सूचीECT))
					जाओ sharing_violation;
				जारी;
			पूर्ण

			/* we've found a region we can share */
			pregion->vm_usage++;
			vma->vm_region = pregion;
			start = pregion->vm_start;
			start += (pgoff - pregion->vm_pgoff) << PAGE_SHIFT;
			vma->vm_start = start;
			vma->vm_end = start + len;

			अगर (pregion->vm_flags & VM_MAPPED_COPY)
				vma->vm_flags |= VM_MAPPED_COPY;
			अन्यथा अणु
				ret = करो_mmap_shared_file(vma);
				अगर (ret < 0) अणु
					vma->vm_region = शून्य;
					vma->vm_start = 0;
					vma->vm_end = 0;
					pregion->vm_usage--;
					pregion = शून्य;
					जाओ error_just_मुक्त;
				पूर्ण
			पूर्ण
			fput(region->vm_file);
			kmem_cache_मुक्त(vm_region_jar, region);
			region = pregion;
			result = start;
			जाओ share;
		पूर्ण

		/* obtain the address at which to make a shared mapping
		 * - this is the hook क्रम quasi-memory अक्षरacter devices to
		 *   tell us the location of a shared mapping
		 */
		अगर (capabilities & NOMMU_MAP_सूचीECT) अणु
			addr = file->f_op->get_unmapped_area(file, addr, len,
							     pgoff, flags);
			अगर (IS_ERR_VALUE(addr)) अणु
				ret = addr;
				अगर (ret != -ENOSYS)
					जाओ error_just_मुक्त;

				/* the driver refused to tell us where to site
				 * the mapping so we'll have to attempt to copy
				 * it */
				ret = -ENODEV;
				अगर (!(capabilities & NOMMU_MAP_COPY))
					जाओ error_just_मुक्त;

				capabilities &= ~NOMMU_MAP_सूचीECT;
			पूर्ण अन्यथा अणु
				vma->vm_start = region->vm_start = addr;
				vma->vm_end = region->vm_end = addr + len;
			पूर्ण
		पूर्ण
	पूर्ण

	vma->vm_region = region;

	/* set up the mapping
	 * - the region is filled in अगर NOMMU_MAP_सूचीECT is still set
	 */
	अगर (file && vma->vm_flags & VM_SHARED)
		ret = करो_mmap_shared_file(vma);
	अन्यथा
		ret = करो_mmap_निजी(vma, region, len, capabilities);
	अगर (ret < 0)
		जाओ error_just_मुक्त;
	add_nommu_region(region);

	/* clear anonymous mappings that करोn't ask क्रम uninitialized data */
	अगर (!vma->vm_file &&
	    (!IS_ENABLED(CONFIG_MMAP_ALLOW_UNINITIALIZED) ||
	     !(flags & MAP_UNINITIALIZED)))
		स_रखो((व्योम *)region->vm_start, 0,
		       region->vm_end - region->vm_start);

	/* okay... we have a mapping; now we have to रेजिस्टर it */
	result = vma->vm_start;

	current->mm->total_vm += len >> PAGE_SHIFT;

share:
	add_vma_to_mm(current->mm, vma);

	/* we flush the region from the icache only when the first executable
	 * mapping of it is made  */
	अगर (vma->vm_flags & VM_EXEC && !region->vm_icache_flushed) अणु
		flush_icache_user_range(region->vm_start, region->vm_end);
		region->vm_icache_flushed = true;
	पूर्ण

	up_ग_लिखो(&nommu_region_sem);

	वापस result;

error_just_मुक्त:
	up_ग_लिखो(&nommu_region_sem);
error:
	अगर (region->vm_file)
		fput(region->vm_file);
	kmem_cache_मुक्त(vm_region_jar, region);
	अगर (vma->vm_file)
		fput(vma->vm_file);
	vm_area_मुक्त(vma);
	वापस ret;

sharing_violation:
	up_ग_लिखो(&nommu_region_sem);
	pr_warn("Attempt to share mismatched mappings\n");
	ret = -EINVAL;
	जाओ error;

error_getting_vma:
	kmem_cache_मुक्त(vm_region_jar, region);
	pr_warn("Allocation of vma for %lu byte allocation from process %d failed\n",
			len, current->pid);
	show_मुक्त_areas(0, शून्य);
	वापस -ENOMEM;

error_getting_region:
	pr_warn("Allocation of vm region for %lu byte allocation from process %d failed\n",
			len, current->pid);
	show_मुक्त_areas(0, शून्य);
	वापस -ENOMEM;
पूर्ण

अचिन्हित दीर्घ ksys_mmap_pgoff(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
			      अचिन्हित दीर्घ prot, अचिन्हित दीर्घ flags,
			      अचिन्हित दीर्घ fd, अचिन्हित दीर्घ pgoff)
अणु
	काष्ठा file *file = शून्य;
	अचिन्हित दीर्घ retval = -EBADF;

	audit_mmap_fd(fd, flags);
	अगर (!(flags & MAP_ANONYMOUS)) अणु
		file = fget(fd);
		अगर (!file)
			जाओ out;
	पूर्ण

	flags &= ~(MAP_EXECUTABLE | MAP_DENYWRITE);

	retval = vm_mmap_pgoff(file, addr, len, prot, flags, pgoff);

	अगर (file)
		fput(file);
out:
	वापस retval;
पूर्ण

SYSCALL_DEFINE6(mmap_pgoff, अचिन्हित दीर्घ, addr, अचिन्हित दीर्घ, len,
		अचिन्हित दीर्घ, prot, अचिन्हित दीर्घ, flags,
		अचिन्हित दीर्घ, fd, अचिन्हित दीर्घ, pgoff)
अणु
	वापस ksys_mmap_pgoff(addr, len, prot, flags, fd, pgoff);
पूर्ण

#अगर_घोषित __ARCH_WANT_SYS_OLD_MMAP
काष्ठा mmap_arg_काष्ठा अणु
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ len;
	अचिन्हित दीर्घ prot;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ fd;
	अचिन्हित दीर्घ offset;
पूर्ण;

SYSCALL_DEFINE1(old_mmap, काष्ठा mmap_arg_काष्ठा __user *, arg)
अणु
	काष्ठा mmap_arg_काष्ठा a;

	अगर (copy_from_user(&a, arg, माप(a)))
		वापस -EFAULT;
	अगर (offset_in_page(a.offset))
		वापस -EINVAL;

	वापस ksys_mmap_pgoff(a.addr, a.len, a.prot, a.flags, a.fd,
			       a.offset >> PAGE_SHIFT);
पूर्ण
#पूर्ण_अगर /* __ARCH_WANT_SYS_OLD_MMAP */

/*
 * split a vma पूर्णांकo two pieces at address 'addr', a new vma is allocated either
 * क्रम the first part or the tail.
 */
पूर्णांक split_vma(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma,
	      अचिन्हित दीर्घ addr, पूर्णांक new_below)
अणु
	काष्ठा vm_area_काष्ठा *new;
	काष्ठा vm_region *region;
	अचिन्हित दीर्घ npages;

	/* we're only permitted to split anonymous regions (these should have
	 * only a single usage on the region) */
	अगर (vma->vm_file)
		वापस -ENOMEM;

	अगर (mm->map_count >= sysctl_max_map_count)
		वापस -ENOMEM;

	region = kmem_cache_alloc(vm_region_jar, GFP_KERNEL);
	अगर (!region)
		वापस -ENOMEM;

	new = vm_area_dup(vma);
	अगर (!new) अणु
		kmem_cache_मुक्त(vm_region_jar, region);
		वापस -ENOMEM;
	पूर्ण

	/* most fields are the same, copy all, and then fixup */
	*region = *vma->vm_region;
	new->vm_region = region;

	npages = (addr - vma->vm_start) >> PAGE_SHIFT;

	अगर (new_below) अणु
		region->vm_top = region->vm_end = new->vm_end = addr;
	पूर्ण अन्यथा अणु
		region->vm_start = new->vm_start = addr;
		region->vm_pgoff = new->vm_pgoff += npages;
	पूर्ण

	अगर (new->vm_ops && new->vm_ops->खोलो)
		new->vm_ops->खोलो(new);

	delete_vma_from_mm(vma);
	करोwn_ग_लिखो(&nommu_region_sem);
	delete_nommu_region(vma->vm_region);
	अगर (new_below) अणु
		vma->vm_region->vm_start = vma->vm_start = addr;
		vma->vm_region->vm_pgoff = vma->vm_pgoff += npages;
	पूर्ण अन्यथा अणु
		vma->vm_region->vm_end = vma->vm_end = addr;
		vma->vm_region->vm_top = addr;
	पूर्ण
	add_nommu_region(vma->vm_region);
	add_nommu_region(new->vm_region);
	up_ग_लिखो(&nommu_region_sem);
	add_vma_to_mm(mm, vma);
	add_vma_to_mm(mm, new);
	वापस 0;
पूर्ण

/*
 * shrink a VMA by removing the specअगरied chunk from either the beginning or
 * the end
 */
अटल पूर्णांक shrink_vma(काष्ठा mm_काष्ठा *mm,
		      काष्ठा vm_area_काष्ठा *vma,
		      अचिन्हित दीर्घ from, अचिन्हित दीर्घ to)
अणु
	काष्ठा vm_region *region;

	/* adjust the VMA's pointers, which may reposition it in the MM's tree
	 * and list */
	delete_vma_from_mm(vma);
	अगर (from > vma->vm_start)
		vma->vm_end = from;
	अन्यथा
		vma->vm_start = to;
	add_vma_to_mm(mm, vma);

	/* cut the backing region करोwn to size */
	region = vma->vm_region;
	BUG_ON(region->vm_usage != 1);

	करोwn_ग_लिखो(&nommu_region_sem);
	delete_nommu_region(region);
	अगर (from > region->vm_start) अणु
		to = region->vm_top;
		region->vm_top = region->vm_end = from;
	पूर्ण अन्यथा अणु
		region->vm_start = to;
	पूर्ण
	add_nommu_region(region);
	up_ग_लिखो(&nommu_region_sem);

	मुक्त_page_series(from, to);
	वापस 0;
पूर्ण

/*
 * release a mapping
 * - under NOMMU conditions the chunk to be unmapped must be backed by a single
 *   VMA, though it need not cover the whole VMA
 */
पूर्णांक करो_munmap(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ start, माप_प्रकार len, काष्ठा list_head *uf)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ end;
	पूर्णांक ret;

	len = PAGE_ALIGN(len);
	अगर (len == 0)
		वापस -EINVAL;

	end = start + len;

	/* find the first potentially overlapping VMA */
	vma = find_vma(mm, start);
	अगर (!vma) अणु
		अटल पूर्णांक limit;
		अगर (limit < 5) अणु
			pr_warn("munmap of memory not mmapped by process %d (%s): 0x%lx-0x%lx\n",
					current->pid, current->comm,
					start, start + len - 1);
			limit++;
		पूर्ण
		वापस -EINVAL;
	पूर्ण

	/* we're allowed to split an anonymous VMA but not a file-backed one */
	अगर (vma->vm_file) अणु
		करो अणु
			अगर (start > vma->vm_start)
				वापस -EINVAL;
			अगर (end == vma->vm_end)
				जाओ erase_whole_vma;
			vma = vma->vm_next;
		पूर्ण जबतक (vma);
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		/* the chunk must be a subset of the VMA found */
		अगर (start == vma->vm_start && end == vma->vm_end)
			जाओ erase_whole_vma;
		अगर (start < vma->vm_start || end > vma->vm_end)
			वापस -EINVAL;
		अगर (offset_in_page(start))
			वापस -EINVAL;
		अगर (end != vma->vm_end && offset_in_page(end))
			वापस -EINVAL;
		अगर (start != vma->vm_start && end != vma->vm_end) अणु
			ret = split_vma(mm, vma, start, 1);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
		वापस shrink_vma(mm, vma, start, end);
	पूर्ण

erase_whole_vma:
	delete_vma_from_mm(vma);
	delete_vma(mm, vma);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(करो_munmap);

पूर्णांक vm_munmap(अचिन्हित दीर्घ addr, माप_प्रकार len)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	पूर्णांक ret;

	mmap_ग_लिखो_lock(mm);
	ret = करो_munmap(mm, addr, len, शून्य);
	mmap_ग_लिखो_unlock(mm);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(vm_munmap);

SYSCALL_DEFINE2(munmap, अचिन्हित दीर्घ, addr, माप_प्रकार, len)
अणु
	वापस vm_munmap(addr, len);
पूर्ण

/*
 * release all the mappings made in a process's VM space
 */
व्योम निकास_mmap(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा vm_area_काष्ठा *vma;

	अगर (!mm)
		वापस;

	mm->total_vm = 0;

	जबतक ((vma = mm->mmap)) अणु
		mm->mmap = vma->vm_next;
		delete_vma_from_mm(vma);
		delete_vma(mm, vma);
		cond_resched();
	पूर्ण
पूर्ण

पूर्णांक vm_brk(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len)
अणु
	वापस -ENOMEM;
पूर्ण

/*
 * expand (or shrink) an existing mapping, potentially moving it at the same
 * समय (controlled by the MREMAP_MAYMOVE flag and available VM space)
 *
 * under NOMMU conditions, we only permit changing a mapping's size, and only
 * as दीर्घ as it stays within the region allocated by करो_mmap_निजी() and the
 * block is not shareable
 *
 * MREMAP_FIXED is not supported under NOMMU conditions
 */
अटल अचिन्हित दीर्घ करो_mremap(अचिन्हित दीर्घ addr,
			अचिन्हित दीर्घ old_len, अचिन्हित दीर्घ new_len,
			अचिन्हित दीर्घ flags, अचिन्हित दीर्घ new_addr)
अणु
	काष्ठा vm_area_काष्ठा *vma;

	/* insanity checks first */
	old_len = PAGE_ALIGN(old_len);
	new_len = PAGE_ALIGN(new_len);
	अगर (old_len == 0 || new_len == 0)
		वापस (अचिन्हित दीर्घ) -EINVAL;

	अगर (offset_in_page(addr))
		वापस -EINVAL;

	अगर (flags & MREMAP_FIXED && new_addr != addr)
		वापस (अचिन्हित दीर्घ) -EINVAL;

	vma = find_vma_exact(current->mm, addr, old_len);
	अगर (!vma)
		वापस (अचिन्हित दीर्घ) -EINVAL;

	अगर (vma->vm_end != vma->vm_start + old_len)
		वापस (अचिन्हित दीर्घ) -EFAULT;

	अगर (vma->vm_flags & VM_MAYSHARE)
		वापस (अचिन्हित दीर्घ) -EPERM;

	अगर (new_len > vma->vm_region->vm_end - vma->vm_region->vm_start)
		वापस (अचिन्हित दीर्घ) -ENOMEM;

	/* all checks complete - करो it */
	vma->vm_end = vma->vm_start + new_len;
	वापस vma->vm_start;
पूर्ण

SYSCALL_DEFINE5(mremap, अचिन्हित दीर्घ, addr, अचिन्हित दीर्घ, old_len,
		अचिन्हित दीर्घ, new_len, अचिन्हित दीर्घ, flags,
		अचिन्हित दीर्घ, new_addr)
अणु
	अचिन्हित दीर्घ ret;

	mmap_ग_लिखो_lock(current->mm);
	ret = करो_mremap(addr, old_len, new_len, flags, new_addr);
	mmap_ग_लिखो_unlock(current->mm);
	वापस ret;
पूर्ण

काष्ठा page *follow_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
			 अचिन्हित पूर्णांक foll_flags)
अणु
	वापस शून्य;
पूर्ण

पूर्णांक remap_pfn_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
		अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ size, pgprot_t prot)
अणु
	अगर (addr != (pfn << PAGE_SHIFT))
		वापस -EINVAL;

	vma->vm_flags |= VM_IO | VM_PFNMAP | VM_DONTEXPAND | VM_DONTDUMP;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(remap_pfn_range);

पूर्णांक vm_iomap_memory(काष्ठा vm_area_काष्ठा *vma, phys_addr_t start, अचिन्हित दीर्घ len)
अणु
	अचिन्हित दीर्घ pfn = start >> PAGE_SHIFT;
	अचिन्हित दीर्घ vm_len = vma->vm_end - vma->vm_start;

	pfn += vma->vm_pgoff;
	वापस io_remap_pfn_range(vma, vma->vm_start, pfn, vm_len, vma->vm_page_prot);
पूर्ण
EXPORT_SYMBOL(vm_iomap_memory);

पूर्णांक remap_vदो_स्मृति_range(काष्ठा vm_area_काष्ठा *vma, व्योम *addr,
			अचिन्हित दीर्घ pgoff)
अणु
	अचिन्हित पूर्णांक size = vma->vm_end - vma->vm_start;

	अगर (!(vma->vm_flags & VM_USERMAP))
		वापस -EINVAL;

	vma->vm_start = (अचिन्हित दीर्घ)(addr + (pgoff << PAGE_SHIFT));
	vma->vm_end = vma->vm_start + size;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(remap_vदो_स्मृति_range);

अचिन्हित दीर्घ arch_get_unmapped_area(काष्ठा file *file, अचिन्हित दीर्घ addr,
	अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags)
अणु
	वापस -ENOMEM;
पूर्ण

vm_fault_t filemap_fault(काष्ठा vm_fault *vmf)
अणु
	BUG();
	वापस 0;
पूर्ण
EXPORT_SYMBOL(filemap_fault);

vm_fault_t filemap_map_pages(काष्ठा vm_fault *vmf,
		pgoff_t start_pgoff, pgoff_t end_pgoff)
अणु
	BUG();
	वापस 0;
पूर्ण
EXPORT_SYMBOL(filemap_map_pages);

पूर्णांक __access_remote_vm(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr, व्योम *buf,
		       पूर्णांक len, अचिन्हित पूर्णांक gup_flags)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	पूर्णांक ग_लिखो = gup_flags & FOLL_WRITE;

	अगर (mmap_पढ़ो_lock_समाप्तable(mm))
		वापस 0;

	/* the access must start within one of the target process's mappings */
	vma = find_vma(mm, addr);
	अगर (vma) अणु
		/* करोn't overrun this mapping */
		अगर (addr + len >= vma->vm_end)
			len = vma->vm_end - addr;

		/* only पढ़ो or ग_लिखो mappings where it is permitted */
		अगर (ग_लिखो && vma->vm_flags & VM_MAYWRITE)
			copy_to_user_page(vma, शून्य, addr,
					 (व्योम *) addr, buf, len);
		अन्यथा अगर (!ग_लिखो && vma->vm_flags & VM_MAYREAD)
			copy_from_user_page(vma, शून्य, addr,
					    buf, (व्योम *) addr, len);
		अन्यथा
			len = 0;
	पूर्ण अन्यथा अणु
		len = 0;
	पूर्ण

	mmap_पढ़ो_unlock(mm);

	वापस len;
पूर्ण

/**
 * access_remote_vm - access another process' address space
 * @mm:		the mm_काष्ठा of the target address space
 * @addr:	start address to access
 * @buf:	source or destination buffer
 * @len:	number of bytes to transfer
 * @gup_flags:	flags modअगरying lookup behaviour
 *
 * The caller must hold a reference on @mm.
 */
पूर्णांक access_remote_vm(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		व्योम *buf, पूर्णांक len, अचिन्हित पूर्णांक gup_flags)
अणु
	वापस __access_remote_vm(mm, addr, buf, len, gup_flags);
पूर्ण

/*
 * Access another process' address space.
 * - source/target buffer must be kernel space
 */
पूर्णांक access_process_vm(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ addr, व्योम *buf, पूर्णांक len,
		अचिन्हित पूर्णांक gup_flags)
अणु
	काष्ठा mm_काष्ठा *mm;

	अगर (addr + len < addr)
		वापस 0;

	mm = get_task_mm(tsk);
	अगर (!mm)
		वापस 0;

	len = __access_remote_vm(mm, addr, buf, len, gup_flags);

	mmput(mm);
	वापस len;
पूर्ण
EXPORT_SYMBOL_GPL(access_process_vm);

/**
 * nommu_shrink_inode_mappings - Shrink the shared mappings on an inode
 * @inode: The inode to check
 * @size: The current filesize of the inode
 * @newsize: The proposed filesize of the inode
 *
 * Check the shared mappings on an inode on behalf of a shrinking truncate to
 * make sure that any outstanding VMAs aren't broken and then shrink the
 * vm_regions that extend beyond so that करो_mmap() करोesn't
 * स्वतःmatically grant mappings that are too large.
 */
पूर्णांक nommu_shrink_inode_mappings(काष्ठा inode *inode, माप_प्रकार size,
				माप_प्रकार newsize)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा vm_region *region;
	pgoff_t low, high;
	माप_प्रकार r_size, r_top;

	low = newsize >> PAGE_SHIFT;
	high = (size + PAGE_SIZE - 1) >> PAGE_SHIFT;

	करोwn_ग_लिखो(&nommu_region_sem);
	i_mmap_lock_पढ़ो(inode->i_mapping);

	/* search क्रम VMAs that fall within the dead zone */
	vma_पूर्णांकerval_tree_क्रमeach(vma, &inode->i_mapping->i_mmap, low, high) अणु
		/* found one - only पूर्णांकerested अगर it's shared out of the page
		 * cache */
		अगर (vma->vm_flags & VM_SHARED) अणु
			i_mmap_unlock_पढ़ो(inode->i_mapping);
			up_ग_लिखो(&nommu_region_sem);
			वापस -ETXTBSY; /* not quite true, but near enough */
		पूर्ण
	पूर्ण

	/* reduce any regions that overlap the dead zone - अगर in existence,
	 * these will be poपूर्णांकed to by VMAs that करोn't overlap the dead zone
	 *
	 * we करोn't check क्रम any regions that start beyond the खातापूर्ण as there
	 * shouldn't be any
	 */
	vma_पूर्णांकerval_tree_क्रमeach(vma, &inode->i_mapping->i_mmap, 0, अच_दीर्घ_उच्च) अणु
		अगर (!(vma->vm_flags & VM_SHARED))
			जारी;

		region = vma->vm_region;
		r_size = region->vm_top - region->vm_start;
		r_top = (region->vm_pgoff << PAGE_SHIFT) + r_size;

		अगर (r_top > newsize) अणु
			region->vm_top -= r_top - newsize;
			अगर (region->vm_end > region->vm_top)
				region->vm_end = region->vm_top;
		पूर्ण
	पूर्ण

	i_mmap_unlock_पढ़ो(inode->i_mapping);
	up_ग_लिखो(&nommu_region_sem);
	वापस 0;
पूर्ण

/*
 * Initialise sysctl_user_reserve_kbytes.
 *
 * This is पूर्णांकended to prevent a user from starting a single memory hogging
 * process, such that they cannot recover (समाप्त the hog) in OVERCOMMIT_NEVER
 * mode.
 *
 * The शेष value is min(3% of मुक्त memory, 128MB)
 * 128MB is enough to recover with sshd/login, bash, and top/समाप्त.
 */
अटल पूर्णांक __meminit init_user_reserve(व्योम)
अणु
	अचिन्हित दीर्घ मुक्त_kbytes;

	मुक्त_kbytes = global_zone_page_state(NR_FREE_PAGES) << (PAGE_SHIFT - 10);

	sysctl_user_reserve_kbytes = min(मुक्त_kbytes / 32, 1UL << 17);
	वापस 0;
पूर्ण
subsys_initcall(init_user_reserve);

/*
 * Initialise sysctl_admin_reserve_kbytes.
 *
 * The purpose of sysctl_admin_reserve_kbytes is to allow the sys admin
 * to log in and समाप्त a memory hogging process.
 *
 * Systems with more than 256MB will reserve 8MB, enough to recover
 * with sshd, bash, and top in OVERCOMMIT_GUESS. Smaller प्रणालीs will
 * only reserve 3% of मुक्त pages by शेष.
 */
अटल पूर्णांक __meminit init_admin_reserve(व्योम)
अणु
	अचिन्हित दीर्घ मुक्त_kbytes;

	मुक्त_kbytes = global_zone_page_state(NR_FREE_PAGES) << (PAGE_SHIFT - 10);

	sysctl_admin_reserve_kbytes = min(मुक्त_kbytes / 32, 1UL << 13);
	वापस 0;
पूर्ण
subsys_initcall(init_admin_reserve);
