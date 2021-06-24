<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <linux/module.h>
#समावेश <linux/memblock.h>
#समावेश <linux/mm.h>
#समावेश <linux/pfn.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/sections.h>
#समावेश <as-layout.h>
#समावेश <init.h>
#समावेश <kern.h>
#समावेश <mem_user.h>
#समावेश <os.h>

अटल पूर्णांक physmem_fd = -1;

/* Changed during early boot */
अचिन्हित दीर्घ high_physmem;
EXPORT_SYMBOL(high_physmem);

बाह्य अचिन्हित दीर्घ दीर्घ physmem_size;

व्योम __init mem_total_pages(अचिन्हित दीर्घ physmem, अचिन्हित दीर्घ iomem,
		     अचिन्हित दीर्घ highmem)
अणु
	अचिन्हित दीर्घ phys_pages, highmem_pages;
	अचिन्हित दीर्घ iomem_pages, total_pages;

	phys_pages    = physmem >> PAGE_SHIFT;
	iomem_pages   = iomem   >> PAGE_SHIFT;
	highmem_pages = highmem >> PAGE_SHIFT;

	total_pages   = phys_pages + iomem_pages + highmem_pages;

	max_mapnr = total_pages;
पूर्ण

व्योम map_memory(अचिन्हित दीर्घ virt, अचिन्हित दीर्घ phys, अचिन्हित दीर्घ len,
		पूर्णांक r, पूर्णांक w, पूर्णांक x)
अणु
	__u64 offset;
	पूर्णांक fd, err;

	fd = phys_mapping(phys, &offset);
	err = os_map_memory((व्योम *) virt, fd, offset, len, r, w, x);
	अगर (err) अणु
		अगर (err == -ENOMEM)
			prपूर्णांकk(KERN_ERR "try increasing the host's "
			       "/proc/sys/vm/max_map_count to <physical "
			       "memory size>/4096\n");
		panic("map_memory(0x%lx, %d, 0x%llx, %ld, %d, %d, %d) failed, "
		      "err = %d\n", virt, fd, offset, len, r, w, x, err);
	पूर्ण
पूर्ण

/**
 * setup_physmem() - Setup physical memory क्रम UML
 * @start:	Start address of the physical kernel memory,
 *		i.e start address of the executable image.
 * @reserve_end:	end address of the physical kernel memory.
 * @len:	Length of total physical memory that should be mapped/made
 *		available, in bytes.
 * @highmem:	Number of highmem bytes that should be mapped/made available.
 *
 * Creates an unlinked temporary file of size (len + highmem) and memory maps
 * it on the last executable image address (uml_reserved).
 *
 * The offset is needed as the length of the total physical memory
 * (len + highmem) includes the size of the memory used be the executable image,
 * but the mapped-to address is the last address of the executable image
 * (uml_reserved == end address of executable image).
 *
 * The memory mapped memory of the temporary file is used as backing memory
 * of all user space processes/kernel tasks.
 */
व्योम __init setup_physmem(अचिन्हित दीर्घ start, अचिन्हित दीर्घ reserve_end,
			  अचिन्हित दीर्घ len, अचिन्हित दीर्घ दीर्घ highmem)
अणु
	अचिन्हित दीर्घ reserve = reserve_end - start;
	दीर्घ map_size = len - reserve;
	पूर्णांक err;

	अगर(map_size <= 0) अणु
		os_warn("Too few physical memory! Needed=%lu, given=%lu\n",
			reserve, len);
		निकास(1);
	पूर्ण

	physmem_fd = create_mem_file(len + highmem);

	err = os_map_memory((व्योम *) reserve_end, physmem_fd, reserve,
			    map_size, 1, 1, 1);
	अगर (err < 0) अणु
		os_warn("setup_physmem - mapping %ld bytes of memory at 0x%p "
			"failed - errno = %d\n", map_size,
			(व्योम *) reserve_end, err);
		निकास(1);
	पूर्ण

	/*
	 * Special kludge - This page will be mapped in to userspace processes
	 * from physmem_fd, so it needs to be written out there.
	 */
	os_seek_file(physmem_fd, __pa(__syscall_stub_start));
	os_ग_लिखो_file(physmem_fd, __syscall_stub_start, PAGE_SIZE);
	os_fsync_file(physmem_fd);

	memblock_add(__pa(start), len + highmem);
	memblock_reserve(__pa(start), reserve);

	min_low_pfn = PFN_UP(__pa(reserve_end));
	max_low_pfn = min_low_pfn + (map_size >> PAGE_SHIFT);
पूर्ण

पूर्णांक phys_mapping(अचिन्हित दीर्घ phys, अचिन्हित दीर्घ दीर्घ *offset_out)
अणु
	पूर्णांक fd = -1;

	अगर (phys < physmem_size) अणु
		fd = physmem_fd;
		*offset_out = phys;
	पूर्ण
	अन्यथा अगर (phys < __pa(end_iomem)) अणु
		काष्ठा iomem_region *region = iomem_regions;

		जबतक (region != शून्य) अणु
			अगर ((phys >= region->phys) &&
			    (phys < region->phys + region->size)) अणु
				fd = region->fd;
				*offset_out = phys - region->phys;
				अवरोध;
			पूर्ण
			region = region->next;
		पूर्ण
	पूर्ण
	अन्यथा अगर (phys < __pa(end_iomem) + highmem) अणु
		fd = physmem_fd;
		*offset_out = phys - iomem_size;
	पूर्ण

	वापस fd;
पूर्ण
EXPORT_SYMBOL(phys_mapping);

अटल पूर्णांक __init uml_mem_setup(अक्षर *line, पूर्णांक *add)
अणु
	अक्षर *retptr;
	physmem_size = memparse(line,&retptr);
	वापस 0;
पूर्ण
__uml_setup("mem=", uml_mem_setup,
"mem=<Amount of desired ram>\n"
"    This controls how much \"physical\" memory the kernel allocates\n"
"    for the system. The size is specified as a number followed by\n"
"    one of 'k', 'K', 'm', 'M', which have the obvious meanings.\n"
"    This is not related to the amount of memory in the host.  It can\n"
"    be more, and the excess, if it's ever used, will just be swapped out.\n"
"	Example: mem=64M\n\n"
);

बाह्य पूर्णांक __init parse_iomem(अक्षर *str, पूर्णांक *add);

__uml_setup("iomem=", parse_iomem,
"iomem=<name>,<file>\n"
"    Configure <file> as an IO memory region named <name>.\n\n"
);

/*
 * This list is स्थिरructed in parse_iomem and addresses filled in in
 * setup_iomem, both of which run during early boot.  Afterwards, it's
 * unchanged.
 */
काष्ठा iomem_region *iomem_regions;

/* Initialized in parse_iomem and unchanged thereafter */
पूर्णांक iomem_size;

अचिन्हित दीर्घ find_iomem(अक्षर *driver, अचिन्हित दीर्घ *len_out)
अणु
	काष्ठा iomem_region *region = iomem_regions;

	जबतक (region != शून्य) अणु
		अगर (!म_भेद(region->driver, driver)) अणु
			*len_out = region->size;
			वापस region->virt;
		पूर्ण

		region = region->next;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(find_iomem);

अटल पूर्णांक setup_iomem(व्योम)
अणु
	काष्ठा iomem_region *region = iomem_regions;
	अचिन्हित दीर्घ iomem_start = high_physmem + PAGE_SIZE;
	पूर्णांक err;

	जबतक (region != शून्य) अणु
		err = os_map_memory((व्योम *) iomem_start, region->fd, 0,
				    region->size, 1, 1, 0);
		अगर (err)
			prपूर्णांकk(KERN_ERR "Mapping iomem region for driver '%s' "
			       "failed, errno = %d\n", region->driver, -err);
		अन्यथा अणु
			region->virt = iomem_start;
			region->phys = __pa(region->virt);
		पूर्ण

		iomem_start += region->size + PAGE_SIZE;
		region = region->next;
	पूर्ण

	वापस 0;
पूर्ण

__initcall(setup_iomem);
