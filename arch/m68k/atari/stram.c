<शैली गुरु>
/*
 * Functions क्रम ST-RAM allocations
 *
 * Copyright 1994-97 Roman Hodek <Roman.Hodek@inक्रमmatik.uni-erlangen.de>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/major.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/memblock.h>
#समावेश <linux/mount.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/module.h>
#समावेश <linux/ioport.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/atarihw.h>
#समावेश <यंत्र/atari_stram.h>
#समावेश <यंत्र/पन.स>


/*
 * The ST-RAM allocator allocates memory from a pool of reserved ST-RAM of
 * configurable size, set aside on ST-RAM init.
 * As दीर्घ as this pool is not exhausted, allocation of real ST-RAM can be
 * guaranteed.
 */

/* set अगर kernel is in ST-RAM */
अटल पूर्णांक kernel_in_stram;

अटल काष्ठा resource stram_pool = अणु
	.name = "ST-RAM Pool"
पूर्ण;

अटल अचिन्हित दीर्घ pool_size = 1024*1024;

अटल अचिन्हित दीर्घ stram_virt_offset;

अटल पूर्णांक __init atari_stram_setup(अक्षर *arg)
अणु
	अगर (!MACH_IS_ATARI)
		वापस 0;

	pool_size = memparse(arg, शून्य);
	वापस 0;
पूर्ण

early_param("stram_pool", atari_stram_setup);


/*
 * This init function is called very early by atari/config.c
 * It initializes some पूर्णांकernal variables needed क्रम stram_alloc()
 */
व्योम __init atari_stram_init(व्योम)
अणु
	पूर्णांक i;

	/*
	 * determine whether kernel code resides in ST-RAM
	 * (then ST-RAM is the first memory block at भव 0x0)
	 */
	kernel_in_stram = (m68k_memory[0].addr == 0);

	क्रम (i = 0; i < m68k_num_memory; ++i) अणु
		अगर (m68k_memory[i].addr == 0) अणु
			वापस;
		पूर्ण
	पूर्ण

	/* Should never come here! (There is always ST-Ram!) */
	panic("atari_stram_init: no ST-RAM found!");
पूर्ण


/*
 * This function is called from setup_arch() to reserve the pages needed क्रम
 * ST-RAM management, अगर the kernel resides in ST-RAM.
 */
व्योम __init atari_stram_reserve_pages(व्योम *start_mem)
अणु
	अगर (kernel_in_stram) अणु
		pr_debug("atari_stram pool: kernel in ST-RAM, using alloc_bootmem!\n");
		stram_pool.start = (resource_माप_प्रकार)memblock_alloc_low(pool_size,
								       PAGE_SIZE);
		अगर (!stram_pool.start)
			panic("%s: Failed to allocate %lu bytes align=%lx\n",
			      __func__, pool_size, PAGE_SIZE);

		stram_pool.end = stram_pool.start + pool_size - 1;
		request_resource(&iomem_resource, &stram_pool);
		stram_virt_offset = 0;
		pr_debug("atari_stram pool: size = %lu bytes, resource = %pR\n",
			pool_size, &stram_pool);
		pr_debug("atari_stram pool: stram_virt_offset = %lx\n",
			stram_virt_offset);
	पूर्ण
पूर्ण


/*
 * This function is called as arch initcall to reserve the pages needed क्रम
 * ST-RAM management, अगर the kernel करोes not reside in ST-RAM.
 */
पूर्णांक __init atari_stram_map_pages(व्योम)
अणु
	अगर (!kernel_in_stram) अणु
		/*
		 * Skip page 0, as the fhe first 2 KiB are supervisor-only!
		 */
		pr_debug("atari_stram pool: kernel not in ST-RAM, using ioremap!\n");
		stram_pool.start = PAGE_SIZE;
		stram_pool.end = stram_pool.start + pool_size - 1;
		request_resource(&iomem_resource, &stram_pool);
		stram_virt_offset = (अचिन्हित दीर्घ) ioremap(stram_pool.start,
				resource_size(&stram_pool)) - stram_pool.start;
		pr_debug("atari_stram pool: size = %lu bytes, resource = %pR\n",
			pool_size, &stram_pool);
		pr_debug("atari_stram pool: stram_virt_offset = %lx\n",
			stram_virt_offset);
	पूर्ण
	वापस 0;
पूर्ण
arch_initcall(atari_stram_map_pages);


व्योम *atari_stram_to_virt(अचिन्हित दीर्घ phys)
अणु
	वापस (व्योम *)(phys + stram_virt_offset);
पूर्ण
EXPORT_SYMBOL(atari_stram_to_virt);


अचिन्हित दीर्घ atari_stram_to_phys(व्योम *virt)
अणु
	वापस (अचिन्हित दीर्घ)(virt - stram_virt_offset);
पूर्ण
EXPORT_SYMBOL(atari_stram_to_phys);


व्योम *atari_stram_alloc(अचिन्हित दीर्घ size, स्थिर अक्षर *owner)
अणु
	काष्ठा resource *res;
	पूर्णांक error;

	pr_debug("atari_stram_alloc: allocate %lu bytes\n", size);

	/* round up */
	size = PAGE_ALIGN(size);

	res = kzalloc(माप(काष्ठा resource), GFP_KERNEL);
	अगर (!res)
		वापस शून्य;

	res->name = owner;
	error = allocate_resource(&stram_pool, res, size, 0, अच_पूर्णांक_उच्च,
				  PAGE_SIZE, शून्य, शून्य);
	अगर (error < 0) अणु
		pr_err("atari_stram_alloc: allocate_resource() failed %d!\n",
		       error);
		kमुक्त(res);
		वापस शून्य;
	पूर्ण

	pr_debug("atari_stram_alloc: returning %pR\n", res);
	वापस atari_stram_to_virt(res->start);
पूर्ण
EXPORT_SYMBOL(atari_stram_alloc);


व्योम atari_stram_मुक्त(व्योम *addr)
अणु
	अचिन्हित दीर्घ start = atari_stram_to_phys(addr);
	काष्ठा resource *res;
	अचिन्हित दीर्घ size;

	res = lookup_resource(&stram_pool, start);
	अगर (!res) अणु
		pr_err("atari_stram_free: trying to free nonexistent region "
		       "at %p\n", addr);
		वापस;
	पूर्ण

	size = resource_size(res);
	pr_debug("atari_stram_free: free %lu bytes at %p\n", size, addr);
	release_resource(res);
	kमुक्त(res);
पूर्ण
EXPORT_SYMBOL(atari_stram_मुक्त);
