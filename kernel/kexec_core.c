<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * kexec.c - kexec प्रणाली call core code.
 * Copyright (C) 2002-2004 Eric Biederman  <ebiederm@xmission.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/capability.h>
#समावेश <linux/mm.h>
#समावेश <linux/file.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/kexec.h>
#समावेश <linux/mutex.h>
#समावेश <linux/list.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/syscalls.h>
#समावेश <linux/reboot.h>
#समावेश <linux/ioport.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/elf.h>
#समावेश <linux/elfcore.h>
#समावेश <linux/utsname.h>
#समावेश <linux/numa.h>
#समावेश <linux/suspend.h>
#समावेश <linux/device.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/pm.h>
#समावेश <linux/cpu.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>
#समावेश <linux/console.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/swap.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/compiler.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/objtool.h>
#समावेश <linux/kmsg_dump.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/sections.h>

#समावेश <crypto/hash.h>
#समावेश "kexec_internal.h"

DEFINE_MUTEX(kexec_mutex);

/* Per cpu memory क्रम storing cpu states in हाल of प्रणाली crash. */
note_buf_t __percpu *crash_notes;

/* Flag to indicate we are going to kexec a new kernel */
bool kexec_in_progress = false;


/* Location of the reserved area क्रम the crash kernel */
काष्ठा resource crashk_res = अणु
	.name  = "Crash kernel",
	.start = 0,
	.end   = 0,
	.flags = IORESOURCE_BUSY | IORESOURCE_SYSTEM_RAM,
	.desc  = IORES_DESC_CRASH_KERNEL
पूर्ण;
काष्ठा resource crashk_low_res = अणु
	.name  = "Crash kernel",
	.start = 0,
	.end   = 0,
	.flags = IORESOURCE_BUSY | IORESOURCE_SYSTEM_RAM,
	.desc  = IORES_DESC_CRASH_KERNEL
पूर्ण;

पूर्णांक kexec_should_crash(काष्ठा task_काष्ठा *p)
अणु
	/*
	 * If crash_kexec_post_notअगरiers is enabled, करोn't run
	 * crash_kexec() here yet, which must be run after panic
	 * notअगरiers in panic().
	 */
	अगर (crash_kexec_post_notअगरiers)
		वापस 0;
	/*
	 * There are 4 panic() calls in करो_निकास() path, each of which
	 * corresponds to each of these 4 conditions.
	 */
	अगर (in_पूर्णांकerrupt() || !p->pid || is_global_init(p) || panic_on_oops)
		वापस 1;
	वापस 0;
पूर्ण

पूर्णांक kexec_crash_loaded(व्योम)
अणु
	वापस !!kexec_crash_image;
पूर्ण
EXPORT_SYMBOL_GPL(kexec_crash_loaded);

/*
 * When kexec transitions to the new kernel there is a one-to-one
 * mapping between physical and भव addresses.  On processors
 * where you can disable the MMU this is trivial, and easy.  For
 * others it is still a simple predictable page table to setup.
 *
 * In that environment kexec copies the new kernel to its final
 * resting place.  This means I can only support memory whose
 * physical address can fit in an अचिन्हित दीर्घ.  In particular
 * addresses where (pfn << PAGE_SHIFT) > अच_दीर्घ_उच्च cannot be handled.
 * If the assembly stub has more restrictive requirements
 * KEXEC_SOURCE_MEMORY_LIMIT and KEXEC_DEST_MEMORY_LIMIT can be
 * defined more restrictively in <यंत्र/kexec.h>.
 *
 * The code क्रम the transition from the current kernel to the
 * new kernel is placed in the control_code_buffer, whose size
 * is given by KEXEC_CONTROL_PAGE_SIZE.  In the best हाल only a single
 * page of memory is necessary, but some architectures require more.
 * Because this memory must be identity mapped in the transition from
 * भव to physical addresses it must live in the range
 * 0 - TASK_SIZE, as only the user space mappings are arbitrarily
 * modअगरiable.
 *
 * The assembly stub in the control code buffer is passed a linked list
 * of descriptor pages detailing the source pages of the new kernel,
 * and the destination addresses of those source pages.  As this data
 * काष्ठाure is not used in the context of the current OS, it must
 * be self-contained.
 *
 * The code has been made to work with highmem pages and will use a
 * destination page in its final resting place (अगर it happens
 * to allocate it).  The end product of this is that most of the
 * physical address space, and most of RAM can be used.
 *
 * Future directions include:
 *  - allocating a page table with the control code buffer identity
 *    mapped, to simplअगरy machine_kexec and make kexec_on_panic more
 *    reliable.
 */

/*
 * KIMAGE_NO_DEST is an impossible destination address..., क्रम
 * allocating pages whose destination address we करो not care about.
 */
#घोषणा KIMAGE_NO_DEST (-1UL)
#घोषणा PAGE_COUNT(x) (((x) + PAGE_SIZE - 1) >> PAGE_SHIFT)

अटल काष्ठा page *kimage_alloc_page(काष्ठा kimage *image,
				       gfp_t gfp_mask,
				       अचिन्हित दीर्घ dest);

पूर्णांक sanity_check_segment_list(काष्ठा kimage *image)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ nr_segments = image->nr_segments;
	अचिन्हित दीर्घ total_pages = 0;
	अचिन्हित दीर्घ nr_pages = totalram_pages();

	/*
	 * Verअगरy we have good destination addresses.  The caller is
	 * responsible क्रम making certain we करोn't attempt to load
	 * the new image पूर्णांकo invalid or reserved areas of RAM.  This
	 * just verअगरies it is an address we can use.
	 *
	 * Since the kernel करोes everything in page size chunks ensure
	 * the destination addresses are page aligned.  Too many
	 * special हालs crop of when we करोn't करो this.  The most
	 * insidious is getting overlapping destination addresses
	 * simply because addresses are changed to page size
	 * granularity.
	 */
	क्रम (i = 0; i < nr_segments; i++) अणु
		अचिन्हित दीर्घ mstart, mend;

		mstart = image->segment[i].mem;
		mend   = mstart + image->segment[i].memsz;
		अगर (mstart > mend)
			वापस -EADDRNOTAVAIL;
		अगर ((mstart & ~PAGE_MASK) || (mend & ~PAGE_MASK))
			वापस -EADDRNOTAVAIL;
		अगर (mend >= KEXEC_DESTINATION_MEMORY_LIMIT)
			वापस -EADDRNOTAVAIL;
	पूर्ण

	/* Verअगरy our destination addresses करो not overlap.
	 * If we alloed overlapping destination addresses
	 * through very weird things can happen with no
	 * easy explanation as one segment stops on another.
	 */
	क्रम (i = 0; i < nr_segments; i++) अणु
		अचिन्हित दीर्घ mstart, mend;
		अचिन्हित दीर्घ j;

		mstart = image->segment[i].mem;
		mend   = mstart + image->segment[i].memsz;
		क्रम (j = 0; j < i; j++) अणु
			अचिन्हित दीर्घ pstart, pend;

			pstart = image->segment[j].mem;
			pend   = pstart + image->segment[j].memsz;
			/* Do the segments overlap ? */
			अगर ((mend > pstart) && (mstart < pend))
				वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Ensure our buffer sizes are strictly less than
	 * our memory sizes.  This should always be the हाल,
	 * and it is easier to check up front than to be surprised
	 * later on.
	 */
	क्रम (i = 0; i < nr_segments; i++) अणु
		अगर (image->segment[i].bufsz > image->segment[i].memsz)
			वापस -EINVAL;
	पूर्ण

	/*
	 * Verअगरy that no more than half of memory will be consumed. If the
	 * request from userspace is too large, a large amount of समय will be
	 * wasted allocating pages, which can cause a soft lockup.
	 */
	क्रम (i = 0; i < nr_segments; i++) अणु
		अगर (PAGE_COUNT(image->segment[i].memsz) > nr_pages / 2)
			वापस -EINVAL;

		total_pages += PAGE_COUNT(image->segment[i].memsz);
	पूर्ण

	अगर (total_pages > nr_pages / 2)
		वापस -EINVAL;

	/*
	 * Verअगरy we have good destination addresses.  Normally
	 * the caller is responsible क्रम making certain we करोn't
	 * attempt to load the new image पूर्णांकo invalid or reserved
	 * areas of RAM.  But crash kernels are preloaded पूर्णांकo a
	 * reserved area of ram.  We must ensure the addresses
	 * are in the reserved area otherwise preloading the
	 * kernel could corrupt things.
	 */

	अगर (image->type == KEXEC_TYPE_CRASH) अणु
		क्रम (i = 0; i < nr_segments; i++) अणु
			अचिन्हित दीर्घ mstart, mend;

			mstart = image->segment[i].mem;
			mend = mstart + image->segment[i].memsz - 1;
			/* Ensure we are within the crash kernel limits */
			अगर ((mstart < phys_to_boot_phys(crashk_res.start)) ||
			    (mend > phys_to_boot_phys(crashk_res.end)))
				वापस -EADDRNOTAVAIL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा kimage *करो_kimage_alloc_init(व्योम)
अणु
	काष्ठा kimage *image;

	/* Allocate a controlling काष्ठाure */
	image = kzalloc(माप(*image), GFP_KERNEL);
	अगर (!image)
		वापस शून्य;

	image->head = 0;
	image->entry = &image->head;
	image->last_entry = &image->head;
	image->control_page = ~0; /* By शेष this करोes not apply */
	image->type = KEXEC_TYPE_DEFAULT;

	/* Initialize the list of control pages */
	INIT_LIST_HEAD(&image->control_pages);

	/* Initialize the list of destination pages */
	INIT_LIST_HEAD(&image->dest_pages);

	/* Initialize the list of unusable pages */
	INIT_LIST_HEAD(&image->unusable_pages);

	वापस image;
पूर्ण

पूर्णांक kimage_is_destination_range(काष्ठा kimage *image,
					अचिन्हित दीर्घ start,
					अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < image->nr_segments; i++) अणु
		अचिन्हित दीर्घ mstart, mend;

		mstart = image->segment[i].mem;
		mend = mstart + image->segment[i].memsz;
		अगर ((end > mstart) && (start < mend))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा page *kimage_alloc_pages(gfp_t gfp_mask, अचिन्हित पूर्णांक order)
अणु
	काष्ठा page *pages;

	अगर (fatal_संकेत_pending(current))
		वापस शून्य;
	pages = alloc_pages(gfp_mask & ~__GFP_ZERO, order);
	अगर (pages) अणु
		अचिन्हित पूर्णांक count, i;

		pages->mapping = शून्य;
		set_page_निजी(pages, order);
		count = 1 << order;
		क्रम (i = 0; i < count; i++)
			SetPageReserved(pages + i);

		arch_kexec_post_alloc_pages(page_address(pages), count,
					    gfp_mask);

		अगर (gfp_mask & __GFP_ZERO)
			क्रम (i = 0; i < count; i++)
				clear_highpage(pages + i);
	पूर्ण

	वापस pages;
पूर्ण

अटल व्योम kimage_मुक्त_pages(काष्ठा page *page)
अणु
	अचिन्हित पूर्णांक order, count, i;

	order = page_निजी(page);
	count = 1 << order;

	arch_kexec_pre_मुक्त_pages(page_address(page), count);

	क्रम (i = 0; i < count; i++)
		ClearPageReserved(page + i);
	__मुक्त_pages(page, order);
पूर्ण

व्योम kimage_मुक्त_page_list(काष्ठा list_head *list)
अणु
	काष्ठा page *page, *next;

	list_क्रम_each_entry_safe(page, next, list, lru) अणु
		list_del(&page->lru);
		kimage_मुक्त_pages(page);
	पूर्ण
पूर्ण

अटल काष्ठा page *kimage_alloc_normal_control_pages(काष्ठा kimage *image,
							अचिन्हित पूर्णांक order)
अणु
	/* Control pages are special, they are the पूर्णांकermediaries
	 * that are needed जबतक we copy the rest of the pages
	 * to their final resting place.  As such they must
	 * not conflict with either the destination addresses
	 * or memory the kernel is alपढ़ोy using.
	 *
	 * The only हाल where we really need more than one of
	 * these are क्रम architectures where we cannot disable
	 * the MMU and must instead generate an identity mapped
	 * page table क्रम all of the memory.
	 *
	 * At worst this runs in O(N) of the image size.
	 */
	काष्ठा list_head extra_pages;
	काष्ठा page *pages;
	अचिन्हित पूर्णांक count;

	count = 1 << order;
	INIT_LIST_HEAD(&extra_pages);

	/* Loop जबतक I can allocate a page and the page allocated
	 * is a destination page.
	 */
	करो अणु
		अचिन्हित दीर्घ pfn, epfn, addr, eaddr;

		pages = kimage_alloc_pages(KEXEC_CONTROL_MEMORY_GFP, order);
		अगर (!pages)
			अवरोध;
		pfn   = page_to_boot_pfn(pages);
		epfn  = pfn + count;
		addr  = pfn << PAGE_SHIFT;
		eaddr = epfn << PAGE_SHIFT;
		अगर ((epfn >= (KEXEC_CONTROL_MEMORY_LIMIT >> PAGE_SHIFT)) ||
			      kimage_is_destination_range(image, addr, eaddr)) अणु
			list_add(&pages->lru, &extra_pages);
			pages = शून्य;
		पूर्ण
	पूर्ण जबतक (!pages);

	अगर (pages) अणु
		/* Remember the allocated page... */
		list_add(&pages->lru, &image->control_pages);

		/* Because the page is alपढ़ोy in it's destination
		 * location we will never allocate another page at
		 * that address.  Thereक्रमe kimage_alloc_pages
		 * will not वापस it (again) and we करोn't need
		 * to give it an entry in image->segment[].
		 */
	पूर्ण
	/* Deal with the destination pages I have inadvertently allocated.
	 *
	 * Ideally I would convert multi-page allocations पूर्णांकo single
	 * page allocations, and add everything to image->dest_pages.
	 *
	 * For now it is simpler to just मुक्त the pages.
	 */
	kimage_मुक्त_page_list(&extra_pages);

	वापस pages;
पूर्ण

अटल काष्ठा page *kimage_alloc_crash_control_pages(काष्ठा kimage *image,
						      अचिन्हित पूर्णांक order)
अणु
	/* Control pages are special, they are the पूर्णांकermediaries
	 * that are needed जबतक we copy the rest of the pages
	 * to their final resting place.  As such they must
	 * not conflict with either the destination addresses
	 * or memory the kernel is alपढ़ोy using.
	 *
	 * Control pages are also the only pags we must allocate
	 * when loading a crash kernel.  All of the other pages
	 * are specअगरied by the segments and we just स_नकल
	 * पूर्णांकo them directly.
	 *
	 * The only हाल where we really need more than one of
	 * these are क्रम architectures where we cannot disable
	 * the MMU and must instead generate an identity mapped
	 * page table क्रम all of the memory.
	 *
	 * Given the low demand this implements a very simple
	 * allocator that finds the first hole of the appropriate
	 * size in the reserved memory region, and allocates all
	 * of the memory up to and including the hole.
	 */
	अचिन्हित दीर्घ hole_start, hole_end, size;
	काष्ठा page *pages;

	pages = शून्य;
	size = (1 << order) << PAGE_SHIFT;
	hole_start = (image->control_page + (size - 1)) & ~(size - 1);
	hole_end   = hole_start + size - 1;
	जबतक (hole_end <= crashk_res.end) अणु
		अचिन्हित दीर्घ i;

		cond_resched();

		अगर (hole_end > KEXEC_CRASH_CONTROL_MEMORY_LIMIT)
			अवरोध;
		/* See अगर I overlap any of the segments */
		क्रम (i = 0; i < image->nr_segments; i++) अणु
			अचिन्हित दीर्घ mstart, mend;

			mstart = image->segment[i].mem;
			mend   = mstart + image->segment[i].memsz - 1;
			अगर ((hole_end >= mstart) && (hole_start <= mend)) अणु
				/* Advance the hole to the end of the segment */
				hole_start = (mend + (size - 1)) & ~(size - 1);
				hole_end   = hole_start + size - 1;
				अवरोध;
			पूर्ण
		पूर्ण
		/* If I करोn't overlap any segments I have found my hole! */
		अगर (i == image->nr_segments) अणु
			pages = pfn_to_page(hole_start >> PAGE_SHIFT);
			image->control_page = hole_end;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Ensure that these pages are decrypted अगर SME is enabled. */
	अगर (pages)
		arch_kexec_post_alloc_pages(page_address(pages), 1 << order, 0);

	वापस pages;
पूर्ण


काष्ठा page *kimage_alloc_control_pages(काष्ठा kimage *image,
					 अचिन्हित पूर्णांक order)
अणु
	काष्ठा page *pages = शून्य;

	चयन (image->type) अणु
	हाल KEXEC_TYPE_DEFAULT:
		pages = kimage_alloc_normal_control_pages(image, order);
		अवरोध;
	हाल KEXEC_TYPE_CRASH:
		pages = kimage_alloc_crash_control_pages(image, order);
		अवरोध;
	पूर्ण

	वापस pages;
पूर्ण

पूर्णांक kimage_crash_copy_vmcoreinfo(काष्ठा kimage *image)
अणु
	काष्ठा page *vmcoreinfo_page;
	व्योम *safecopy;

	अगर (image->type != KEXEC_TYPE_CRASH)
		वापस 0;

	/*
	 * For kdump, allocate one vmcoreinfo safe copy from the
	 * crash memory. as we have arch_kexec_protect_crashkres()
	 * after kexec syscall, we naturally protect it from ग_लिखो
	 * (even पढ़ो) access under kernel direct mapping. But on
	 * the other hand, we still need to operate it when crash
	 * happens to generate vmcoreinfo note, hereby we rely on
	 * vmap क्रम this purpose.
	 */
	vmcoreinfo_page = kimage_alloc_control_pages(image, 0);
	अगर (!vmcoreinfo_page) अणु
		pr_warn("Could not allocate vmcoreinfo buffer\n");
		वापस -ENOMEM;
	पूर्ण
	safecopy = vmap(&vmcoreinfo_page, 1, VM_MAP, PAGE_KERNEL);
	अगर (!safecopy) अणु
		pr_warn("Could not vmap vmcoreinfo buffer\n");
		वापस -ENOMEM;
	पूर्ण

	image->vmcoreinfo_data_copy = safecopy;
	crash_update_vmcoreinfo_safecopy(safecopy);

	वापस 0;
पूर्ण

अटल पूर्णांक kimage_add_entry(काष्ठा kimage *image, kimage_entry_t entry)
अणु
	अगर (*image->entry != 0)
		image->entry++;

	अगर (image->entry == image->last_entry) अणु
		kimage_entry_t *ind_page;
		काष्ठा page *page;

		page = kimage_alloc_page(image, GFP_KERNEL, KIMAGE_NO_DEST);
		अगर (!page)
			वापस -ENOMEM;

		ind_page = page_address(page);
		*image->entry = virt_to_boot_phys(ind_page) | IND_INसूचीECTION;
		image->entry = ind_page;
		image->last_entry = ind_page +
				      ((PAGE_SIZE/माप(kimage_entry_t)) - 1);
	पूर्ण
	*image->entry = entry;
	image->entry++;
	*image->entry = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक kimage_set_destination(काष्ठा kimage *image,
				   अचिन्हित दीर्घ destination)
अणु
	पूर्णांक result;

	destination &= PAGE_MASK;
	result = kimage_add_entry(image, destination | IND_DESTINATION);

	वापस result;
पूर्ण


अटल पूर्णांक kimage_add_page(काष्ठा kimage *image, अचिन्हित दीर्घ page)
अणु
	पूर्णांक result;

	page &= PAGE_MASK;
	result = kimage_add_entry(image, page | IND_SOURCE);

	वापस result;
पूर्ण


अटल व्योम kimage_मुक्त_extra_pages(काष्ठा kimage *image)
अणु
	/* Walk through and मुक्त any extra destination pages I may have */
	kimage_मुक्त_page_list(&image->dest_pages);

	/* Walk through and मुक्त any unusable pages I have cached */
	kimage_मुक्त_page_list(&image->unusable_pages);

पूर्ण

पूर्णांक __weak machine_kexec_post_load(काष्ठा kimage *image)
अणु
	वापस 0;
पूर्ण

व्योम kimage_terminate(काष्ठा kimage *image)
अणु
	अगर (*image->entry != 0)
		image->entry++;

	*image->entry = IND_DONE;
पूर्ण

#घोषणा क्रम_each_kimage_entry(image, ptr, entry) \
	क्रम (ptr = &image->head; (entry = *ptr) && !(entry & IND_DONE); \
		ptr = (entry & IND_INसूचीECTION) ? \
			boot_phys_to_virt((entry & PAGE_MASK)) : ptr + 1)

अटल व्योम kimage_मुक्त_entry(kimage_entry_t entry)
अणु
	काष्ठा page *page;

	page = boot_pfn_to_page(entry >> PAGE_SHIFT);
	kimage_मुक्त_pages(page);
पूर्ण

व्योम kimage_मुक्त(काष्ठा kimage *image)
अणु
	kimage_entry_t *ptr, entry;
	kimage_entry_t ind = 0;

	अगर (!image)
		वापस;

	अगर (image->vmcoreinfo_data_copy) अणु
		crash_update_vmcoreinfo_safecopy(शून्य);
		vunmap(image->vmcoreinfo_data_copy);
	पूर्ण

	kimage_मुक्त_extra_pages(image);
	क्रम_each_kimage_entry(image, ptr, entry) अणु
		अगर (entry & IND_INसूचीECTION) अणु
			/* Free the previous indirection page */
			अगर (ind & IND_INसूचीECTION)
				kimage_मुक्त_entry(ind);
			/* Save this indirection page until we are
			 * करोne with it.
			 */
			ind = entry;
		पूर्ण अन्यथा अगर (entry & IND_SOURCE)
			kimage_मुक्त_entry(entry);
	पूर्ण
	/* Free the final indirection page */
	अगर (ind & IND_INसूचीECTION)
		kimage_मुक्त_entry(ind);

	/* Handle any machine specअगरic cleanup */
	machine_kexec_cleanup(image);

	/* Free the kexec control pages... */
	kimage_मुक्त_page_list(&image->control_pages);

	/*
	 * Free up any temporary buffers allocated. This might hit अगर
	 * error occurred much later after buffer allocation.
	 */
	अगर (image->file_mode)
		kimage_file_post_load_cleanup(image);

	kमुक्त(image);
पूर्ण

अटल kimage_entry_t *kimage_dst_used(काष्ठा kimage *image,
					अचिन्हित दीर्घ page)
अणु
	kimage_entry_t *ptr, entry;
	अचिन्हित दीर्घ destination = 0;

	क्रम_each_kimage_entry(image, ptr, entry) अणु
		अगर (entry & IND_DESTINATION)
			destination = entry & PAGE_MASK;
		अन्यथा अगर (entry & IND_SOURCE) अणु
			अगर (page == destination)
				वापस ptr;
			destination += PAGE_SIZE;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा page *kimage_alloc_page(काष्ठा kimage *image,
					gfp_t gfp_mask,
					अचिन्हित दीर्घ destination)
अणु
	/*
	 * Here we implement safeguards to ensure that a source page
	 * is not copied to its destination page beक्रमe the data on
	 * the destination page is no दीर्घer useful.
	 *
	 * To करो this we मुख्यtain the invariant that a source page is
	 * either its own destination page, or it is not a
	 * destination page at all.
	 *
	 * That is slightly stronger than required, but the proof
	 * that no problems will not occur is trivial, and the
	 * implementation is simply to verअगरy.
	 *
	 * When allocating all pages normally this algorithm will run
	 * in O(N) समय, but in the worst हाल it will run in O(N^2)
	 * समय.   If the runसमय is a problem the data काष्ठाures can
	 * be fixed.
	 */
	काष्ठा page *page;
	अचिन्हित दीर्घ addr;

	/*
	 * Walk through the list of destination pages, and see अगर I
	 * have a match.
	 */
	list_क्रम_each_entry(page, &image->dest_pages, lru) अणु
		addr = page_to_boot_pfn(page) << PAGE_SHIFT;
		अगर (addr == destination) अणु
			list_del(&page->lru);
			वापस page;
		पूर्ण
	पूर्ण
	page = शून्य;
	जबतक (1) अणु
		kimage_entry_t *old;

		/* Allocate a page, अगर we run out of memory give up */
		page = kimage_alloc_pages(gfp_mask, 0);
		अगर (!page)
			वापस शून्य;
		/* If the page cannot be used file it away */
		अगर (page_to_boot_pfn(page) >
				(KEXEC_SOURCE_MEMORY_LIMIT >> PAGE_SHIFT)) अणु
			list_add(&page->lru, &image->unusable_pages);
			जारी;
		पूर्ण
		addr = page_to_boot_pfn(page) << PAGE_SHIFT;

		/* If it is the destination page we want use it */
		अगर (addr == destination)
			अवरोध;

		/* If the page is not a destination page use it */
		अगर (!kimage_is_destination_range(image, addr,
						  addr + PAGE_SIZE))
			अवरोध;

		/*
		 * I know that the page is someones destination page.
		 * See अगर there is alपढ़ोy a source page क्रम this
		 * destination page.  And अगर so swap the source pages.
		 */
		old = kimage_dst_used(image, addr);
		अगर (old) अणु
			/* If so move it */
			अचिन्हित दीर्घ old_addr;
			काष्ठा page *old_page;

			old_addr = *old & PAGE_MASK;
			old_page = boot_pfn_to_page(old_addr >> PAGE_SHIFT);
			copy_highpage(page, old_page);
			*old = addr | (*old & ~PAGE_MASK);

			/* The old page I have found cannot be a
			 * destination page, so वापस it अगर it's
			 * gfp_flags honor the ones passed in.
			 */
			अगर (!(gfp_mask & __GFP_HIGHMEM) &&
			    PageHighMem(old_page)) अणु
				kimage_मुक्त_pages(old_page);
				जारी;
			पूर्ण
			addr = old_addr;
			page = old_page;
			अवरोध;
		पूर्ण
		/* Place the page on the destination list, to be used later */
		list_add(&page->lru, &image->dest_pages);
	पूर्ण

	वापस page;
पूर्ण

अटल पूर्णांक kimage_load_normal_segment(काष्ठा kimage *image,
					 काष्ठा kexec_segment *segment)
अणु
	अचिन्हित दीर्घ maddr;
	माप_प्रकार ubytes, mbytes;
	पूर्णांक result;
	अचिन्हित अक्षर __user *buf = शून्य;
	अचिन्हित अक्षर *kbuf = शून्य;

	result = 0;
	अगर (image->file_mode)
		kbuf = segment->kbuf;
	अन्यथा
		buf = segment->buf;
	ubytes = segment->bufsz;
	mbytes = segment->memsz;
	maddr = segment->mem;

	result = kimage_set_destination(image, maddr);
	अगर (result < 0)
		जाओ out;

	जबतक (mbytes) अणु
		काष्ठा page *page;
		अक्षर *ptr;
		माप_प्रकार uchunk, mchunk;

		page = kimage_alloc_page(image, GFP_HIGHUSER, maddr);
		अगर (!page) अणु
			result  = -ENOMEM;
			जाओ out;
		पूर्ण
		result = kimage_add_page(image, page_to_boot_pfn(page)
								<< PAGE_SHIFT);
		अगर (result < 0)
			जाओ out;

		ptr = kmap(page);
		/* Start with a clear page */
		clear_page(ptr);
		ptr += maddr & ~PAGE_MASK;
		mchunk = min_t(माप_प्रकार, mbytes,
				PAGE_SIZE - (maddr & ~PAGE_MASK));
		uchunk = min(ubytes, mchunk);

		/* For file based kexec, source pages are in kernel memory */
		अगर (image->file_mode)
			स_नकल(ptr, kbuf, uchunk);
		अन्यथा
			result = copy_from_user(ptr, buf, uchunk);
		kunmap(page);
		अगर (result) अणु
			result = -EFAULT;
			जाओ out;
		पूर्ण
		ubytes -= uchunk;
		maddr  += mchunk;
		अगर (image->file_mode)
			kbuf += mchunk;
		अन्यथा
			buf += mchunk;
		mbytes -= mchunk;

		cond_resched();
	पूर्ण
out:
	वापस result;
पूर्ण

अटल पूर्णांक kimage_load_crash_segment(काष्ठा kimage *image,
					काष्ठा kexec_segment *segment)
अणु
	/* For crash dumps kernels we simply copy the data from
	 * user space to it's destination.
	 * We करो things a page at a समय क्रम the sake of kmap.
	 */
	अचिन्हित दीर्घ maddr;
	माप_प्रकार ubytes, mbytes;
	पूर्णांक result;
	अचिन्हित अक्षर __user *buf = शून्य;
	अचिन्हित अक्षर *kbuf = शून्य;

	result = 0;
	अगर (image->file_mode)
		kbuf = segment->kbuf;
	अन्यथा
		buf = segment->buf;
	ubytes = segment->bufsz;
	mbytes = segment->memsz;
	maddr = segment->mem;
	जबतक (mbytes) अणु
		काष्ठा page *page;
		अक्षर *ptr;
		माप_प्रकार uchunk, mchunk;

		page = boot_pfn_to_page(maddr >> PAGE_SHIFT);
		अगर (!page) अणु
			result  = -ENOMEM;
			जाओ out;
		पूर्ण
		arch_kexec_post_alloc_pages(page_address(page), 1, 0);
		ptr = kmap(page);
		ptr += maddr & ~PAGE_MASK;
		mchunk = min_t(माप_प्रकार, mbytes,
				PAGE_SIZE - (maddr & ~PAGE_MASK));
		uchunk = min(ubytes, mchunk);
		अगर (mchunk > uchunk) अणु
			/* Zero the trailing part of the page */
			स_रखो(ptr + uchunk, 0, mchunk - uchunk);
		पूर्ण

		/* For file based kexec, source pages are in kernel memory */
		अगर (image->file_mode)
			स_नकल(ptr, kbuf, uchunk);
		अन्यथा
			result = copy_from_user(ptr, buf, uchunk);
		kexec_flush_icache_page(page);
		kunmap(page);
		arch_kexec_pre_मुक्त_pages(page_address(page), 1);
		अगर (result) अणु
			result = -EFAULT;
			जाओ out;
		पूर्ण
		ubytes -= uchunk;
		maddr  += mchunk;
		अगर (image->file_mode)
			kbuf += mchunk;
		अन्यथा
			buf += mchunk;
		mbytes -= mchunk;

		cond_resched();
	पूर्ण
out:
	वापस result;
पूर्ण

पूर्णांक kimage_load_segment(काष्ठा kimage *image,
				काष्ठा kexec_segment *segment)
अणु
	पूर्णांक result = -ENOMEM;

	चयन (image->type) अणु
	हाल KEXEC_TYPE_DEFAULT:
		result = kimage_load_normal_segment(image, segment);
		अवरोध;
	हाल KEXEC_TYPE_CRASH:
		result = kimage_load_crash_segment(image, segment);
		अवरोध;
	पूर्ण

	वापस result;
पूर्ण

काष्ठा kimage *kexec_image;
काष्ठा kimage *kexec_crash_image;
पूर्णांक kexec_load_disabled;

/*
 * No panic_cpu check version of crash_kexec().  This function is called
 * only when panic_cpu holds the current CPU number; this is the only CPU
 * which processes crash_kexec routines.
 */
व्योम __noclone __crash_kexec(काष्ठा pt_regs *regs)
अणु
	/* Take the kexec_mutex here to prevent sys_kexec_load
	 * running on one cpu from replacing the crash kernel
	 * we are using after a panic on a dअगरferent cpu.
	 *
	 * If the crash kernel was not located in a fixed area
	 * of memory the xchg(&kexec_crash_image) would be
	 * sufficient.  But since I reuse the memory...
	 */
	अगर (mutex_trylock(&kexec_mutex)) अणु
		अगर (kexec_crash_image) अणु
			काष्ठा pt_regs fixed_regs;

			crash_setup_regs(&fixed_regs, regs);
			crash_save_vmcoreinfo();
			machine_crash_shutकरोwn(&fixed_regs);
			machine_kexec(kexec_crash_image);
		पूर्ण
		mutex_unlock(&kexec_mutex);
	पूर्ण
पूर्ण
STACK_FRAME_NON_STANDARD(__crash_kexec);

व्योम crash_kexec(काष्ठा pt_regs *regs)
अणु
	पूर्णांक old_cpu, this_cpu;

	/*
	 * Only one CPU is allowed to execute the crash_kexec() code as with
	 * panic().  Otherwise parallel calls of panic() and crash_kexec()
	 * may stop each other.  To exclude them, we use panic_cpu here too.
	 */
	this_cpu = raw_smp_processor_id();
	old_cpu = atomic_cmpxchg(&panic_cpu, PANIC_CPU_INVALID, this_cpu);
	अगर (old_cpu == PANIC_CPU_INVALID) अणु
		/* This is the 1st CPU which comes here, so go ahead. */
		prपूर्णांकk_safe_flush_on_panic();
		__crash_kexec(regs);

		/*
		 * Reset panic_cpu to allow another panic()/crash_kexec()
		 * call.
		 */
		atomic_set(&panic_cpu, PANIC_CPU_INVALID);
	पूर्ण
पूर्ण

माप_प्रकार crash_get_memory_size(व्योम)
अणु
	माप_प्रकार size = 0;

	mutex_lock(&kexec_mutex);
	अगर (crashk_res.end != crashk_res.start)
		size = resource_size(&crashk_res);
	mutex_unlock(&kexec_mutex);
	वापस size;
पूर्ण

व्योम __weak crash_मुक्त_reserved_phys_range(अचिन्हित दीर्घ begin,
					   अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ addr;

	क्रम (addr = begin; addr < end; addr += PAGE_SIZE)
		मुक्त_reserved_page(boot_pfn_to_page(addr >> PAGE_SHIFT));
पूर्ण

पूर्णांक crash_shrink_memory(अचिन्हित दीर्घ new_size)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ start, end;
	अचिन्हित दीर्घ old_size;
	काष्ठा resource *ram_res;

	mutex_lock(&kexec_mutex);

	अगर (kexec_crash_image) अणु
		ret = -ENOENT;
		जाओ unlock;
	पूर्ण
	start = crashk_res.start;
	end = crashk_res.end;
	old_size = (end == 0) ? 0 : end - start + 1;
	अगर (new_size >= old_size) अणु
		ret = (new_size == old_size) ? 0 : -EINVAL;
		जाओ unlock;
	पूर्ण

	ram_res = kzalloc(माप(*ram_res), GFP_KERNEL);
	अगर (!ram_res) अणु
		ret = -ENOMEM;
		जाओ unlock;
	पूर्ण

	start = roundup(start, KEXEC_CRASH_MEM_ALIGN);
	end = roundup(start + new_size, KEXEC_CRASH_MEM_ALIGN);

	crash_मुक्त_reserved_phys_range(end, crashk_res.end);

	अगर ((start == end) && (crashk_res.parent != शून्य))
		release_resource(&crashk_res);

	ram_res->start = end;
	ram_res->end = crashk_res.end;
	ram_res->flags = IORESOURCE_BUSY | IORESOURCE_SYSTEM_RAM;
	ram_res->name = "System RAM";

	crashk_res.end = end - 1;

	insert_resource(&iomem_resource, ram_res);

unlock:
	mutex_unlock(&kexec_mutex);
	वापस ret;
पूर्ण

व्योम crash_save_cpu(काष्ठा pt_regs *regs, पूर्णांक cpu)
अणु
	काष्ठा elf_prstatus prstatus;
	u32 *buf;

	अगर ((cpu < 0) || (cpu >= nr_cpu_ids))
		वापस;

	/* Using ELF notes here is opportunistic.
	 * I need a well defined काष्ठाure क्रमmat
	 * क्रम the data I pass, and I need tags
	 * on the data to indicate what inक्रमmation I have
	 * squirrelled away.  ELF notes happen to provide
	 * all of that, so there is no need to invent something new.
	 */
	buf = (u32 *)per_cpu_ptr(crash_notes, cpu);
	अगर (!buf)
		वापस;
	स_रखो(&prstatus, 0, माप(prstatus));
	prstatus.common.pr_pid = current->pid;
	elf_core_copy_kernel_regs(&prstatus.pr_reg, regs);
	buf = append_elf_note(buf, KEXEC_CORE_NOTE_NAME, NT_PRSTATUS,
			      &prstatus, माप(prstatus));
	final_note(buf);
पूर्ण

अटल पूर्णांक __init crash_notes_memory_init(व्योम)
अणु
	/* Allocate memory क्रम saving cpu रेजिस्टरs. */
	माप_प्रकार size, align;

	/*
	 * crash_notes could be allocated across 2 vदो_स्मृति pages when percpu
	 * is vदो_स्मृति based . vदो_स्मृति करोesn't guarantee 2 continuous vदो_स्मृति
	 * pages are also on 2 continuous physical pages. In this हाल the
	 * 2nd part of crash_notes in 2nd page could be lost since only the
	 * starting address and size of crash_notes are exported through sysfs.
	 * Here round up the size of crash_notes to the nearest घातer of two
	 * and pass it to __alloc_percpu as align value. This can make sure
	 * crash_notes is allocated inside one physical page.
	 */
	size = माप(note_buf_t);
	align = min(roundup_घात_of_two(माप(note_buf_t)), PAGE_SIZE);

	/*
	 * Break compile अगर size is bigger than PAGE_SIZE since crash_notes
	 * definitely will be in 2 pages with that.
	 */
	BUILD_BUG_ON(size > PAGE_SIZE);

	crash_notes = __alloc_percpu(size, align);
	अगर (!crash_notes) अणु
		pr_warn("Memory allocation for saving cpu register states failed\n");
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण
subsys_initcall(crash_notes_memory_init);


/*
 * Move पूर्णांकo place and start executing a preloaded standalone
 * executable.  If nothing was preloaded वापस an error.
 */
पूर्णांक kernel_kexec(व्योम)
अणु
	पूर्णांक error = 0;

	अगर (!mutex_trylock(&kexec_mutex))
		वापस -EBUSY;
	अगर (!kexec_image) अणु
		error = -EINVAL;
		जाओ Unlock;
	पूर्ण

#अगर_घोषित CONFIG_KEXEC_JUMP
	अगर (kexec_image->preserve_context) अणु
		pm_prepare_console();
		error = मुक्तze_processes();
		अगर (error) अणु
			error = -EBUSY;
			जाओ Restore_console;
		पूर्ण
		suspend_console();
		error = dpm_suspend_start(PMSG_FREEZE);
		अगर (error)
			जाओ Resume_console;
		/* At this poपूर्णांक, dpm_suspend_start() has been called,
		 * but *not* dpm_suspend_end(). We *must* call
		 * dpm_suspend_end() now.  Otherwise, drivers क्रम
		 * some devices (e.g. पूर्णांकerrupt controllers) become
		 * desynchronized with the actual state of the
		 * hardware at resume समय, and evil weirdness ensues.
		 */
		error = dpm_suspend_end(PMSG_FREEZE);
		अगर (error)
			जाओ Resume_devices;
		error = suspend_disable_secondary_cpus();
		अगर (error)
			जाओ Enable_cpus;
		local_irq_disable();
		error = syscore_suspend();
		अगर (error)
			जाओ Enable_irqs;
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		kexec_in_progress = true;
		kernel_restart_prepare("kexec reboot");
		migrate_to_reboot_cpu();

		/*
		 * migrate_to_reboot_cpu() disables CPU hotplug assuming that
		 * no further code needs to use CPU hotplug (which is true in
		 * the reboot हाल). However, the kexec path depends on using
		 * CPU hotplug again; so re-enable it here.
		 */
		cpu_hotplug_enable();
		pr_notice("Starting new kernel\n");
		machine_shutकरोwn();
	पूर्ण

	kmsg_dump(KMSG_DUMP_SHUTDOWN);
	machine_kexec(kexec_image);

#अगर_घोषित CONFIG_KEXEC_JUMP
	अगर (kexec_image->preserve_context) अणु
		syscore_resume();
 Enable_irqs:
		local_irq_enable();
 Enable_cpus:
		suspend_enable_secondary_cpus();
		dpm_resume_start(PMSG_RESTORE);
 Resume_devices:
		dpm_resume_end(PMSG_RESTORE);
 Resume_console:
		resume_console();
		thaw_processes();
 Restore_console:
		pm_restore_console();
	पूर्ण
#पूर्ण_अगर

 Unlock:
	mutex_unlock(&kexec_mutex);
	वापस error;
पूर्ण

/*
 * Protection mechanism क्रम crashkernel reserved memory after
 * the kdump kernel is loaded.
 *
 * Provide an empty शेष implementation here -- architecture
 * code may override this
 */
व्योम __weak arch_kexec_protect_crashkres(व्योम)
अणुपूर्ण

व्योम __weak arch_kexec_unprotect_crashkres(व्योम)
अणुपूर्ण
