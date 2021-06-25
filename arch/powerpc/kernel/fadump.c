<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Firmware Assisted dump: A robust mechanism to get reliable kernel crash
 * dump with assistance from firmware. This approach करोes not use kexec,
 * instead firmware assists in booting the kdump kernel जबतक preserving
 * memory contents. The most of the code implementation has been adapted
 * from phyp assisted dump implementation written by Linas Vepstas and
 * Manish Ahuja
 *
 * Copyright 2011 IBM Corporation
 * Author: Mahesh Salgaonkar <mahesh@linux.vnet.ibm.com>
 */

#अघोषित DEBUG
#घोषणा pr_fmt(fmt) "fadump: " fmt

#समावेश <linux/माला.स>
#समावेश <linux/memblock.h>
#समावेश <linux/delay.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/crash_dump.h>
#समावेश <linux/kobject.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/slab.h>
#समावेश <linux/cma.h>
#समावेश <linux/hugetlb.h>

#समावेश <यंत्र/debugfs.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/fadump.h>
#समावेश <यंत्र/fadump-पूर्णांकernal.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/पूर्णांकerrupt.h>

/*
 * The CPU who acquired the lock to trigger the fadump crash should
 * रुको क्रम other CPUs to enter.
 *
 * The समयout is in milliseconds.
 */
#घोषणा CRASH_TIMEOUT		500

अटल काष्ठा fw_dump fw_dump;

अटल व्योम __init fadump_reserve_crash_area(u64 base);

#अगर_अघोषित CONFIG_PRESERVE_FA_DUMP

अटल काष्ठा kobject *fadump_kobj;

अटल atomic_t cpus_in_fadump;
अटल DEFINE_MUTEX(fadump_mutex);

अटल काष्ठा fadump_mrange_info crash_mrange_info = अणु "crash", शून्य, 0, 0, 0, false पूर्ण;

#घोषणा RESERVED_RNGS_SZ	16384 /* 16K - 128 entries */
#घोषणा RESERVED_RNGS_CNT	(RESERVED_RNGS_SZ / \
				 माप(काष्ठा fadump_memory_range))
अटल काष्ठा fadump_memory_range rngs[RESERVED_RNGS_CNT];
अटल काष्ठा fadump_mrange_info
reserved_mrange_info = अणु "reserved", rngs, RESERVED_RNGS_SZ, 0, RESERVED_RNGS_CNT, true पूर्ण;

अटल व्योम __init early_init_dt_scan_reserved_ranges(अचिन्हित दीर्घ node);

#अगर_घोषित CONFIG_CMA
अटल काष्ठा cma *fadump_cma;

/*
 * fadump_cma_init() - Initialize CMA area from a fadump reserved memory
 *
 * This function initializes CMA area from fadump reserved memory.
 * The total size of fadump reserved memory covers क्रम boot memory size
 * + cpu data size + hpte size and metadata.
 * Initialize only the area equivalent to boot memory size क्रम CMA use.
 * The reamining portion of fadump reserved memory will be not given
 * to CMA and pages क्रम thoes will stay reserved. boot memory size is
 * aligned per CMA requirement to satisy cma_init_reserved_mem() call.
 * But क्रम some reason even अगर it fails we still have the memory reservation
 * with us and we can still जारी करोing fadump.
 */
अटल पूर्णांक __init fadump_cma_init(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ base, size;
	पूर्णांक rc;

	अगर (!fw_dump.fadump_enabled)
		वापस 0;

	/*
	 * Do not use CMA अगर user has provided fadump=nocma kernel parameter.
	 * Return 1 to जारी with fadump old behaviour.
	 */
	अगर (fw_dump.nocma)
		वापस 1;

	base = fw_dump.reserve_dump_area_start;
	size = fw_dump.boot_memory_size;

	अगर (!size)
		वापस 0;

	rc = cma_init_reserved_mem(base, size, 0, "fadump_cma", &fadump_cma);
	अगर (rc) अणु
		pr_err("Failed to init cma area for firmware-assisted dump,%d\n", rc);
		/*
		 * Though the CMA init has failed we still have memory
		 * reservation with us. The reserved memory will be
		 * blocked from production प्रणाली usage.  Hence वापस 1,
		 * so that we can जारी with fadump.
		 */
		वापस 1;
	पूर्ण

	/*
	 * So we now have successfully initialized cma area क्रम fadump.
	 */
	pr_info("Initialized 0x%lx bytes cma area at %ldMB from 0x%lx "
		"bytes of memory reserved for firmware-assisted dump\n",
		cma_get_size(fadump_cma),
		(अचिन्हित दीर्घ)cma_get_base(fadump_cma) >> 20,
		fw_dump.reserve_dump_area_size);
	वापस 1;
पूर्ण
#अन्यथा
अटल पूर्णांक __init fadump_cma_init(व्योम) अणु वापस 1; पूर्ण
#पूर्ण_अगर /* CONFIG_CMA */

/* Scan the Firmware Assisted dump configuration details. */
पूर्णांक __init early_init_dt_scan_fw_dump(अचिन्हित दीर्घ node, स्थिर अक्षर *uname,
				      पूर्णांक depth, व्योम *data)
अणु
	अगर (depth == 0) अणु
		early_init_dt_scan_reserved_ranges(node);
		वापस 0;
	पूर्ण

	अगर (depth != 1)
		वापस 0;

	अगर (म_भेद(uname, "rtas") == 0) अणु
		rtas_fadump_dt_scan(&fw_dump, node);
		वापस 1;
	पूर्ण

	अगर (म_भेद(uname, "ibm,opal") == 0) अणु
		opal_fadump_dt_scan(&fw_dump, node);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * If fadump is रेजिस्टरed, check अगर the memory provided
 * falls within boot memory area and reserved memory area.
 */
पूर्णांक is_fadump_memory_area(u64 addr, अचिन्हित दीर्घ size)
अणु
	u64 d_start, d_end;

	अगर (!fw_dump.dump_रेजिस्टरed)
		वापस 0;

	अगर (!size)
		वापस 0;

	d_start = fw_dump.reserve_dump_area_start;
	d_end = d_start + fw_dump.reserve_dump_area_size;
	अगर (((addr + size) > d_start) && (addr <= d_end))
		वापस 1;

	वापस (addr <= fw_dump.boot_mem_top);
पूर्ण

पूर्णांक should_fadump_crash(व्योम)
अणु
	अगर (!fw_dump.dump_रेजिस्टरed || !fw_dump.fadumphdr_addr)
		वापस 0;
	वापस 1;
पूर्ण

पूर्णांक is_fadump_active(व्योम)
अणु
	वापस fw_dump.dump_active;
पूर्ण

/*
 * Returns true, अगर there are no holes in memory area between d_start to d_end,
 * false otherwise.
 */
अटल bool is_fadump_mem_area_contiguous(u64 d_start, u64 d_end)
अणु
	phys_addr_t reg_start, reg_end;
	bool ret = false;
	u64 i, start, end;

	क्रम_each_mem_range(i, &reg_start, &reg_end) अणु
		start = max_t(u64, d_start, reg_start);
		end = min_t(u64, d_end, reg_end);
		अगर (d_start < end) अणु
			/* Memory hole from d_start to start */
			अगर (start > d_start)
				अवरोध;

			अगर (end == d_end) अणु
				ret = true;
				अवरोध;
			पूर्ण

			d_start = end + 1;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Returns true, अगर there are no holes in boot memory area,
 * false otherwise.
 */
bool is_fadump_boot_mem_contiguous(व्योम)
अणु
	अचिन्हित दीर्घ d_start, d_end;
	bool ret = false;
	पूर्णांक i;

	क्रम (i = 0; i < fw_dump.boot_mem_regs_cnt; i++) अणु
		d_start = fw_dump.boot_mem_addr[i];
		d_end   = d_start + fw_dump.boot_mem_sz[i];

		ret = is_fadump_mem_area_contiguous(d_start, d_end);
		अगर (!ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Returns true, अगर there are no holes in reserved memory area,
 * false otherwise.
 */
bool is_fadump_reserved_mem_contiguous(व्योम)
अणु
	u64 d_start, d_end;

	d_start	= fw_dump.reserve_dump_area_start;
	d_end	= d_start + fw_dump.reserve_dump_area_size;
	वापस is_fadump_mem_area_contiguous(d_start, d_end);
पूर्ण

/* Prपूर्णांक firmware assisted dump configurations क्रम debugging purpose. */
अटल व्योम fadump_show_config(व्योम)
अणु
	पूर्णांक i;

	pr_debug("Support for firmware-assisted dump (fadump): %s\n",
			(fw_dump.fadump_supported ? "present" : "no support"));

	अगर (!fw_dump.fadump_supported)
		वापस;

	pr_debug("Fadump enabled    : %s\n",
				(fw_dump.fadump_enabled ? "yes" : "no"));
	pr_debug("Dump Active       : %s\n",
				(fw_dump.dump_active ? "yes" : "no"));
	pr_debug("Dump section sizes:\n");
	pr_debug("    CPU state data size: %lx\n", fw_dump.cpu_state_data_size);
	pr_debug("    HPTE region size   : %lx\n", fw_dump.hpte_region_size);
	pr_debug("    Boot memory size   : %lx\n", fw_dump.boot_memory_size);
	pr_debug("    Boot memory top    : %llx\n", fw_dump.boot_mem_top);
	pr_debug("Boot memory regions cnt: %llx\n", fw_dump.boot_mem_regs_cnt);
	क्रम (i = 0; i < fw_dump.boot_mem_regs_cnt; i++) अणु
		pr_debug("[%03d] base = %llx, size = %llx\n", i,
			 fw_dump.boot_mem_addr[i], fw_dump.boot_mem_sz[i]);
	पूर्ण
पूर्ण

/**
 * fadump_calculate_reserve_size(): reserve variable boot area 5% of System RAM
 *
 * Function to find the largest memory size we need to reserve during early
 * boot process. This will be the size of the memory that is required क्रम a
 * kernel to boot successfully.
 *
 * This function has been taken from phyp-assisted dump feature implementation.
 *
 * वापसs larger of 256MB or 5% rounded करोwn to multiples of 256MB.
 *
 * TODO: Come up with better approach to find out more accurate memory size
 * that is required क्रम a kernel to boot successfully.
 *
 */
अटल __init u64 fadump_calculate_reserve_size(व्योम)
अणु
	u64 base, size, booपंचांगem_min;
	पूर्णांक ret;

	अगर (fw_dump.reserve_bootvar)
		pr_warn("'fadump_reserve_mem=' parameter is deprecated in favor of 'crashkernel=' parameter.\n");

	/*
	 * Check अगर the size is specअगरied through crashkernel= cmdline
	 * option. If yes, then use that but ignore base as fadump reserves
	 * memory at a predefined offset.
	 */
	ret = parse_crashkernel(boot_command_line, memblock_phys_mem_size(),
				&size, &base);
	अगर (ret == 0 && size > 0) अणु
		अचिन्हित दीर्घ max_size;

		अगर (fw_dump.reserve_bootvar)
			pr_info("Using 'crashkernel=' parameter for memory reservation.\n");

		fw_dump.reserve_bootvar = (अचिन्हित दीर्घ)size;

		/*
		 * Adjust अगर the boot memory size specअगरied is above
		 * the upper limit.
		 */
		max_size = memblock_phys_mem_size() / MAX_BOOT_MEM_RATIO;
		अगर (fw_dump.reserve_bootvar > max_size) अणु
			fw_dump.reserve_bootvar = max_size;
			pr_info("Adjusted boot memory size to %luMB\n",
				(fw_dump.reserve_bootvar >> 20));
		पूर्ण

		वापस fw_dump.reserve_bootvar;
	पूर्ण अन्यथा अगर (fw_dump.reserve_bootvar) अणु
		/*
		 * 'fadump_reserve_mem=' is being used to reserve memory
		 * क्रम firmware-assisted dump.
		 */
		वापस fw_dump.reserve_bootvar;
	पूर्ण

	/* भागide by 20 to get 5% of value */
	size = memblock_phys_mem_size() / 20;

	/* round it करोwn in multiples of 256 */
	size = size & ~0x0FFFFFFFUL;

	/* Truncate to memory_limit. We करोn't want to over reserve the memory.*/
	अगर (memory_limit && size > memory_limit)
		size = memory_limit;

	booपंचांगem_min = fw_dump.ops->fadump_get_booपंचांगem_min();
	वापस (size > booपंचांगem_min ? size : booपंचांगem_min);
पूर्ण

/*
 * Calculate the total memory size required to be reserved क्रम
 * firmware-assisted dump registration.
 */
अटल अचिन्हित दीर्घ get_fadump_area_size(व्योम)
अणु
	अचिन्हित दीर्घ size = 0;

	size += fw_dump.cpu_state_data_size;
	size += fw_dump.hpte_region_size;
	size += fw_dump.boot_memory_size;
	size += माप(काष्ठा fadump_crash_info_header);
	size += माप(काष्ठा elfhdr); /* ELF core header.*/
	size += माप(काष्ठा elf_phdr); /* place holder क्रम cpu notes */
	/* Program headers क्रम crash memory regions. */
	size += माप(काष्ठा elf_phdr) * (memblock_num_regions(memory) + 2);

	size = PAGE_ALIGN(size);

	/* This is to hold kernel metadata on platक्रमms that support it */
	size += (fw_dump.ops->fadump_get_metadata_size ?
		 fw_dump.ops->fadump_get_metadata_size() : 0);
	वापस size;
पूर्ण

अटल पूर्णांक __init add_boot_mem_region(अचिन्हित दीर्घ rstart,
				      अचिन्हित दीर्घ rsize)
अणु
	पूर्णांक i = fw_dump.boot_mem_regs_cnt++;

	अगर (fw_dump.boot_mem_regs_cnt > FADUMP_MAX_MEM_REGS) अणु
		fw_dump.boot_mem_regs_cnt = FADUMP_MAX_MEM_REGS;
		वापस 0;
	पूर्ण

	pr_debug("Added boot memory range[%d] [%#016lx-%#016lx)\n",
		 i, rstart, (rstart + rsize));
	fw_dump.boot_mem_addr[i] = rstart;
	fw_dump.boot_mem_sz[i] = rsize;
	वापस 1;
पूर्ण

/*
 * Firmware usually has a hard limit on the data it can copy per region.
 * Honour that by splitting a memory range पूर्णांकo multiple regions.
 */
अटल पूर्णांक __init add_boot_mem_regions(अचिन्हित दीर्घ mstart,
				       अचिन्हित दीर्घ msize)
अणु
	अचिन्हित दीर्घ rstart, rsize, max_size;
	पूर्णांक ret = 1;

	rstart = mstart;
	max_size = fw_dump.max_copy_size ? fw_dump.max_copy_size : msize;
	जबतक (msize) अणु
		अगर (msize > max_size)
			rsize = max_size;
		अन्यथा
			rsize = msize;

		ret = add_boot_mem_region(rstart, rsize);
		अगर (!ret)
			अवरोध;

		msize -= rsize;
		rstart += rsize;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __init fadump_get_boot_mem_regions(व्योम)
अणु
	अचिन्हित दीर्घ size, cur_size, hole_size, last_end;
	अचिन्हित दीर्घ mem_size = fw_dump.boot_memory_size;
	phys_addr_t reg_start, reg_end;
	पूर्णांक ret = 1;
	u64 i;

	fw_dump.boot_mem_regs_cnt = 0;

	last_end = 0;
	hole_size = 0;
	cur_size = 0;
	क्रम_each_mem_range(i, &reg_start, &reg_end) अणु
		size = reg_end - reg_start;
		hole_size += (reg_start - last_end);

		अगर ((cur_size + size) >= mem_size) अणु
			size = (mem_size - cur_size);
			ret = add_boot_mem_regions(reg_start, size);
			अवरोध;
		पूर्ण

		mem_size -= size;
		cur_size += size;
		ret = add_boot_mem_regions(reg_start, size);
		अगर (!ret)
			अवरोध;

		last_end = reg_end;
	पूर्ण
	fw_dump.boot_mem_top = PAGE_ALIGN(fw_dump.boot_memory_size + hole_size);

	वापस ret;
पूर्ण

/*
 * Returns true, अगर the given range overlaps with reserved memory ranges
 * starting at idx. Also, updates idx to index of overlapping memory range
 * with the given memory range.
 * False, otherwise.
 */
अटल bool overlaps_reserved_ranges(u64 base, u64 end, पूर्णांक *idx)
अणु
	bool ret = false;
	पूर्णांक i;

	क्रम (i = *idx; i < reserved_mrange_info.mem_range_cnt; i++) अणु
		u64 rbase = reserved_mrange_info.mem_ranges[i].base;
		u64 rend = rbase + reserved_mrange_info.mem_ranges[i].size;

		अगर (end <= rbase)
			अवरोध;

		अगर ((end > rbase) &&  (base < rend)) अणु
			*idx = i;
			ret = true;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Locate a suitable memory area to reserve memory क्रम FADump. While at it,
 * lookup reserved-ranges & aव्योम overlap with them, as they are used by F/W.
 */
अटल u64 __init fadump_locate_reserve_mem(u64 base, u64 size)
अणु
	काष्ठा fadump_memory_range *mrngs;
	phys_addr_t mstart, mend;
	पूर्णांक idx = 0;
	u64 i, ret = 0;

	mrngs = reserved_mrange_info.mem_ranges;
	क्रम_each_मुक्त_mem_range(i, NUMA_NO_NODE, MEMBLOCK_NONE,
				&mstart, &mend, शून्य) अणु
		pr_debug("%llu) mstart: %llx, mend: %llx, base: %llx\n",
			 i, mstart, mend, base);

		अगर (mstart > base)
			base = PAGE_ALIGN(mstart);

		जबतक ((mend > base) && ((mend - base) >= size)) अणु
			अगर (!overlaps_reserved_ranges(base, base+size, &idx)) अणु
				ret = base;
				जाओ out;
			पूर्ण

			base = mrngs[idx].base + mrngs[idx].size;
			base = PAGE_ALIGN(base);
		पूर्ण
	पूर्ण

out:
	वापस ret;
पूर्ण

पूर्णांक __init fadump_reserve_mem(व्योम)
अणु
	u64 base, size, mem_boundary, booपंचांगem_min;
	पूर्णांक ret = 1;

	अगर (!fw_dump.fadump_enabled)
		वापस 0;

	अगर (!fw_dump.fadump_supported) अणु
		pr_info("Firmware-Assisted Dump is not supported on this hardware\n");
		जाओ error_out;
	पूर्ण

	/*
	 * Initialize boot memory size
	 * If dump is active then we have alपढ़ोy calculated the size during
	 * first kernel.
	 */
	अगर (!fw_dump.dump_active) अणु
		fw_dump.boot_memory_size =
			PAGE_ALIGN(fadump_calculate_reserve_size());
#अगर_घोषित CONFIG_CMA
		अगर (!fw_dump.nocma) अणु
			fw_dump.boot_memory_size =
				ALIGN(fw_dump.boot_memory_size,
				      FADUMP_CMA_ALIGNMENT);
		पूर्ण
#पूर्ण_अगर

		booपंचांगem_min = fw_dump.ops->fadump_get_booपंचांगem_min();
		अगर (fw_dump.boot_memory_size < booपंचांगem_min) अणु
			pr_err("Can't enable fadump with boot memory size (0x%lx) less than 0x%llx\n",
			       fw_dump.boot_memory_size, booपंचांगem_min);
			जाओ error_out;
		पूर्ण

		अगर (!fadump_get_boot_mem_regions()) अणु
			pr_err("Too many holes in boot memory area to enable fadump\n");
			जाओ error_out;
		पूर्ण
	पूर्ण

	/*
	 * Calculate the memory boundary.
	 * If memory_limit is less than actual memory boundary then reserve
	 * the memory क्रम fadump beyond the memory_limit and adjust the
	 * memory_limit accordingly, so that the running kernel can run with
	 * specअगरied memory_limit.
	 */
	अगर (memory_limit && memory_limit < memblock_end_of_DRAM()) अणु
		size = get_fadump_area_size();
		अगर ((memory_limit + size) < memblock_end_of_DRAM())
			memory_limit += size;
		अन्यथा
			memory_limit = memblock_end_of_DRAM();
		prपूर्णांकk(KERN_INFO "Adjusted memory_limit for firmware-assisted"
				" dump, now %#016llx\n", memory_limit);
	पूर्ण
	अगर (memory_limit)
		mem_boundary = memory_limit;
	अन्यथा
		mem_boundary = memblock_end_of_DRAM();

	base = fw_dump.boot_mem_top;
	size = get_fadump_area_size();
	fw_dump.reserve_dump_area_size = size;
	अगर (fw_dump.dump_active) अणु
		pr_info("Firmware-assisted dump is active.\n");

#अगर_घोषित CONFIG_HUGETLB_PAGE
		/*
		 * FADump capture kernel करोesn't care much about hugepages.
		 * In fact, handling hugepages in capture kernel is asking क्रम
		 * trouble. So, disable HugeTLB support when fadump is active.
		 */
		hugetlb_disabled = true;
#पूर्ण_अगर
		/*
		 * If last boot has crashed then reserve all the memory
		 * above boot memory size so that we करोn't touch it until
		 * dump is written to disk by userspace tool. This memory
		 * can be released क्रम general use by invalidating fadump.
		 */
		fadump_reserve_crash_area(base);

		pr_debug("fadumphdr_addr = %#016lx\n", fw_dump.fadumphdr_addr);
		pr_debug("Reserve dump area start address: 0x%lx\n",
			 fw_dump.reserve_dump_area_start);
	पूर्ण अन्यथा अणु
		/*
		 * Reserve memory at an offset बंदr to bottom of the RAM to
		 * minimize the impact of memory hot-हटाओ operation.
		 */
		base = fadump_locate_reserve_mem(base, size);

		अगर (!base || (base + size > mem_boundary)) अणु
			pr_err("Failed to find memory chunk for reservation!\n");
			जाओ error_out;
		पूर्ण
		fw_dump.reserve_dump_area_start = base;

		/*
		 * Calculate the kernel metadata address and रेजिस्टर it with
		 * f/w अगर the platक्रमm supports.
		 */
		अगर (fw_dump.ops->fadump_setup_metadata &&
		    (fw_dump.ops->fadump_setup_metadata(&fw_dump) < 0))
			जाओ error_out;

		अगर (memblock_reserve(base, size)) अणु
			pr_err("Failed to reserve memory!\n");
			जाओ error_out;
		पूर्ण

		pr_info("Reserved %lldMB of memory at %#016llx (System RAM: %lldMB)\n",
			(size >> 20), base, (memblock_phys_mem_size() >> 20));

		ret = fadump_cma_init();
	पूर्ण

	वापस ret;
error_out:
	fw_dump.fadump_enabled = 0;
	वापस 0;
पूर्ण

/* Look क्रम fadump= cmdline option. */
अटल पूर्णांक __init early_fadump_param(अक्षर *p)
अणु
	अगर (!p)
		वापस 1;

	अगर (म_भेदन(p, "on", 2) == 0)
		fw_dump.fadump_enabled = 1;
	अन्यथा अगर (म_भेदन(p, "off", 3) == 0)
		fw_dump.fadump_enabled = 0;
	अन्यथा अगर (म_भेदन(p, "nocma", 5) == 0) अणु
		fw_dump.fadump_enabled = 1;
		fw_dump.nocma = 1;
	पूर्ण

	वापस 0;
पूर्ण
early_param("fadump", early_fadump_param);

/*
 * Look क्रम fadump_reserve_mem= cmdline option
 * TODO: Remove references to 'fadump_reserve_mem=' parameter,
 *       the sooner 'crashkernel=' parameter is accustomed to.
 */
अटल पूर्णांक __init early_fadump_reserve_mem(अक्षर *p)
अणु
	अगर (p)
		fw_dump.reserve_bootvar = memparse(p, &p);
	वापस 0;
पूर्ण
early_param("fadump_reserve_mem", early_fadump_reserve_mem);

व्योम crash_fadump(काष्ठा pt_regs *regs, स्थिर अक्षर *str)
अणु
	अचिन्हित पूर्णांक msecs;
	काष्ठा fadump_crash_info_header *fdh = शून्य;
	पूर्णांक old_cpu, this_cpu;
	/* Do not include first CPU */
	अचिन्हित पूर्णांक ncpus = num_online_cpus() - 1;

	अगर (!should_fadump_crash())
		वापस;

	/*
	 * old_cpu == -1 means this is the first CPU which has come here,
	 * go ahead and trigger fadump.
	 *
	 * old_cpu != -1 means some other CPU has alपढ़ोy on it's way
	 * to trigger fadump, just keep looping here.
	 */
	this_cpu = smp_processor_id();
	old_cpu = cmpxchg(&crashing_cpu, -1, this_cpu);

	अगर (old_cpu != -1) अणु
		atomic_inc(&cpus_in_fadump);

		/*
		 * We can't loop here indefinitely. Wait as दीर्घ as fadump
		 * is in क्रमce. If we race with fadump un-registration this
		 * loop will अवरोध and then we go करोwn to normal panic path
		 * and reboot. If fadump is in क्रमce the first crashing
		 * cpu will definitely trigger fadump.
		 */
		जबतक (fw_dump.dump_रेजिस्टरed)
			cpu_relax();
		वापस;
	पूर्ण

	fdh = __va(fw_dump.fadumphdr_addr);
	fdh->crashing_cpu = crashing_cpu;
	crash_save_vmcoreinfo();

	अगर (regs)
		fdh->regs = *regs;
	अन्यथा
		ppc_save_regs(&fdh->regs);

	fdh->online_mask = *cpu_online_mask;

	/*
	 * If we came in via प्रणाली reset, रुको a जबतक क्रम the secondary
	 * CPUs to enter.
	 */
	अगर (TRAP(&(fdh->regs)) == INTERRUPT_SYSTEM_RESET) अणु
		msecs = CRASH_TIMEOUT;
		जबतक ((atomic_पढ़ो(&cpus_in_fadump) < ncpus) && (--msecs > 0))
			mdelay(1);
	पूर्ण

	fw_dump.ops->fadump_trigger(fdh, str);
पूर्ण

u32 *fadump_regs_to_elf_notes(u32 *buf, काष्ठा pt_regs *regs)
अणु
	काष्ठा elf_prstatus prstatus;

	स_रखो(&prstatus, 0, माप(prstatus));
	/*
	 * FIXME: How करो i get PID? Do I really need it?
	 * prstatus.pr_pid = ????
	 */
	elf_core_copy_kernel_regs(&prstatus.pr_reg, regs);
	buf = append_elf_note(buf, CRASH_CORE_NOTE_NAME, NT_PRSTATUS,
			      &prstatus, माप(prstatus));
	वापस buf;
पूर्ण

व्योम fadump_update_elfcore_header(अक्षर *bufp)
अणु
	काष्ठा elf_phdr *phdr;

	bufp += माप(काष्ठा elfhdr);

	/* First note is a place holder क्रम cpu notes info. */
	phdr = (काष्ठा elf_phdr *)bufp;

	अगर (phdr->p_type == PT_NOTE) अणु
		phdr->p_paddr	= __pa(fw_dump.cpu_notes_buf_vaddr);
		phdr->p_offset	= phdr->p_paddr;
		phdr->p_filesz	= fw_dump.cpu_notes_buf_size;
		phdr->p_memsz = fw_dump.cpu_notes_buf_size;
	पूर्ण
	वापस;
पूर्ण

अटल व्योम *fadump_alloc_buffer(अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ count, i;
	काष्ठा page *page;
	व्योम *vaddr;

	vaddr = alloc_pages_exact(size, GFP_KERNEL | __GFP_ZERO);
	अगर (!vaddr)
		वापस शून्य;

	count = PAGE_ALIGN(size) / PAGE_SIZE;
	page = virt_to_page(vaddr);
	क्रम (i = 0; i < count; i++)
		mark_page_reserved(page + i);
	वापस vaddr;
पूर्ण

अटल व्योम fadump_मुक्त_buffer(अचिन्हित दीर्घ vaddr, अचिन्हित दीर्घ size)
अणु
	मुक्त_reserved_area((व्योम *)vaddr, (व्योम *)(vaddr + size), -1, शून्य);
पूर्ण

s32 fadump_setup_cpu_notes_buf(u32 num_cpus)
अणु
	/* Allocate buffer to hold cpu crash notes. */
	fw_dump.cpu_notes_buf_size = num_cpus * माप(note_buf_t);
	fw_dump.cpu_notes_buf_size = PAGE_ALIGN(fw_dump.cpu_notes_buf_size);
	fw_dump.cpu_notes_buf_vaddr =
		(अचिन्हित दीर्घ)fadump_alloc_buffer(fw_dump.cpu_notes_buf_size);
	अगर (!fw_dump.cpu_notes_buf_vaddr) अणु
		pr_err("Failed to allocate %ld bytes for CPU notes buffer\n",
		       fw_dump.cpu_notes_buf_size);
		वापस -ENOMEM;
	पूर्ण

	pr_debug("Allocated buffer for cpu notes of size %ld at 0x%lx\n",
		 fw_dump.cpu_notes_buf_size,
		 fw_dump.cpu_notes_buf_vaddr);
	वापस 0;
पूर्ण

व्योम fadump_मुक्त_cpu_notes_buf(व्योम)
अणु
	अगर (!fw_dump.cpu_notes_buf_vaddr)
		वापस;

	fadump_मुक्त_buffer(fw_dump.cpu_notes_buf_vaddr,
			   fw_dump.cpu_notes_buf_size);
	fw_dump.cpu_notes_buf_vaddr = 0;
	fw_dump.cpu_notes_buf_size = 0;
पूर्ण

अटल व्योम fadump_मुक्त_mem_ranges(काष्ठा fadump_mrange_info *mrange_info)
अणु
	अगर (mrange_info->is_अटल) अणु
		mrange_info->mem_range_cnt = 0;
		वापस;
	पूर्ण

	kमुक्त(mrange_info->mem_ranges);
	स_रखो((व्योम *)((u64)mrange_info + RNG_NAME_SZ), 0,
	       (माप(काष्ठा fadump_mrange_info) - RNG_NAME_SZ));
पूर्ण

/*
 * Allocate or पुनः_स्मृतिate mem_ranges array in incremental units
 * of PAGE_SIZE.
 */
अटल पूर्णांक fadump_alloc_mem_ranges(काष्ठा fadump_mrange_info *mrange_info)
अणु
	काष्ठा fadump_memory_range *new_array;
	u64 new_size;

	new_size = mrange_info->mem_ranges_sz + PAGE_SIZE;
	pr_debug("Allocating %llu bytes of memory for %s memory ranges\n",
		 new_size, mrange_info->name);

	new_array = kपुनः_स्मृति(mrange_info->mem_ranges, new_size, GFP_KERNEL);
	अगर (new_array == शून्य) अणु
		pr_err("Insufficient memory for setting up %s memory ranges\n",
		       mrange_info->name);
		fadump_मुक्त_mem_ranges(mrange_info);
		वापस -ENOMEM;
	पूर्ण

	mrange_info->mem_ranges = new_array;
	mrange_info->mem_ranges_sz = new_size;
	mrange_info->max_mem_ranges = (new_size /
				       माप(काष्ठा fadump_memory_range));
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक fadump_add_mem_range(काष्ठा fadump_mrange_info *mrange_info,
				       u64 base, u64 end)
अणु
	काष्ठा fadump_memory_range *mem_ranges = mrange_info->mem_ranges;
	bool is_adjacent = false;
	u64 start, size;

	अगर (base == end)
		वापस 0;

	/*
	 * Fold adjacent memory ranges to bring करोwn the memory ranges/
	 * PT_LOAD segments count.
	 */
	अगर (mrange_info->mem_range_cnt) अणु
		start = mem_ranges[mrange_info->mem_range_cnt - 1].base;
		size  = mem_ranges[mrange_info->mem_range_cnt - 1].size;

		अगर ((start + size) == base)
			is_adjacent = true;
	पूर्ण
	अगर (!is_adjacent) अणु
		/* resize the array on reaching the limit */
		अगर (mrange_info->mem_range_cnt == mrange_info->max_mem_ranges) अणु
			पूर्णांक ret;

			अगर (mrange_info->is_अटल) अणु
				pr_err("Reached array size limit for %s memory ranges\n",
				       mrange_info->name);
				वापस -ENOSPC;
			पूर्ण

			ret = fadump_alloc_mem_ranges(mrange_info);
			अगर (ret)
				वापस ret;

			/* Update to the new resized array */
			mem_ranges = mrange_info->mem_ranges;
		पूर्ण

		start = base;
		mem_ranges[mrange_info->mem_range_cnt].base = start;
		mrange_info->mem_range_cnt++;
	पूर्ण

	mem_ranges[mrange_info->mem_range_cnt - 1].size = (end - start);
	pr_debug("%s_memory_range[%d] [%#016llx-%#016llx], %#llx bytes\n",
		 mrange_info->name, (mrange_info->mem_range_cnt - 1),
		 start, end - 1, (end - start));
	वापस 0;
पूर्ण

अटल पूर्णांक fadump_exclude_reserved_area(u64 start, u64 end)
अणु
	u64 ra_start, ra_end;
	पूर्णांक ret = 0;

	ra_start = fw_dump.reserve_dump_area_start;
	ra_end = ra_start + fw_dump.reserve_dump_area_size;

	अगर ((ra_start < end) && (ra_end > start)) अणु
		अगर ((start < ra_start) && (end > ra_end)) अणु
			ret = fadump_add_mem_range(&crash_mrange_info,
						   start, ra_start);
			अगर (ret)
				वापस ret;

			ret = fadump_add_mem_range(&crash_mrange_info,
						   ra_end, end);
		पूर्ण अन्यथा अगर (start < ra_start) अणु
			ret = fadump_add_mem_range(&crash_mrange_info,
						   start, ra_start);
		पूर्ण अन्यथा अगर (ra_end < end) अणु
			ret = fadump_add_mem_range(&crash_mrange_info,
						   ra_end, end);
		पूर्ण
	पूर्ण अन्यथा
		ret = fadump_add_mem_range(&crash_mrange_info, start, end);

	वापस ret;
पूर्ण

अटल पूर्णांक fadump_init_elfcore_header(अक्षर *bufp)
अणु
	काष्ठा elfhdr *elf;

	elf = (काष्ठा elfhdr *) bufp;
	bufp += माप(काष्ठा elfhdr);
	स_नकल(elf->e_ident, ELFMAG, SELFMAG);
	elf->e_ident[EI_CLASS] = ELF_CLASS;
	elf->e_ident[EI_DATA] = ELF_DATA;
	elf->e_ident[EI_VERSION] = EV_CURRENT;
	elf->e_ident[EI_OSABI] = ELF_OSABI;
	स_रखो(elf->e_ident+EI_PAD, 0, EI_NIDENT-EI_PAD);
	elf->e_type = ET_CORE;
	elf->e_machine = ELF_ARCH;
	elf->e_version = EV_CURRENT;
	elf->e_entry = 0;
	elf->e_phoff = माप(काष्ठा elfhdr);
	elf->e_shoff = 0;
#अगर defined(_CALL_ELF)
	elf->e_flags = _CALL_ELF;
#अन्यथा
	elf->e_flags = 0;
#पूर्ण_अगर
	elf->e_ehsize = माप(काष्ठा elfhdr);
	elf->e_phentsize = माप(काष्ठा elf_phdr);
	elf->e_phnum = 0;
	elf->e_shentsize = 0;
	elf->e_shnum = 0;
	elf->e_shstrndx = 0;

	वापस 0;
पूर्ण

/*
 * Traverse through memblock काष्ठाure and setup crash memory ranges. These
 * ranges will be used create PT_LOAD program headers in elfcore header.
 */
अटल पूर्णांक fadump_setup_crash_memory_ranges(व्योम)
अणु
	u64 i, start, end;
	पूर्णांक ret;

	pr_debug("Setup crash memory ranges.\n");
	crash_mrange_info.mem_range_cnt = 0;

	/*
	 * Boot memory region(s) रेजिस्टरed with firmware are moved to
	 * dअगरferent location at the समय of crash. Create separate program
	 * header(s) क्रम this memory chunk(s) with the correct offset.
	 */
	क्रम (i = 0; i < fw_dump.boot_mem_regs_cnt; i++) अणु
		start = fw_dump.boot_mem_addr[i];
		end = start + fw_dump.boot_mem_sz[i];
		ret = fadump_add_mem_range(&crash_mrange_info, start, end);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम_each_mem_range(i, &start, &end) अणु
		/*
		 * skip the memory chunk that is alपढ़ोy added
		 * (0 through boot_memory_top).
		 */
		अगर (start < fw_dump.boot_mem_top) अणु
			अगर (end > fw_dump.boot_mem_top)
				start = fw_dump.boot_mem_top;
			अन्यथा
				जारी;
		पूर्ण

		/* add this range excluding the reserved dump area. */
		ret = fadump_exclude_reserved_area(start, end);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * If the given physical address falls within the boot memory region then
 * वापस the relocated address that poपूर्णांकs to the dump region reserved
 * क्रम saving initial boot memory contents.
 */
अटल अंतरभूत अचिन्हित दीर्घ fadump_relocate(अचिन्हित दीर्घ paddr)
अणु
	अचिन्हित दीर्घ raddr, rstart, rend, rlast, hole_size;
	पूर्णांक i;

	hole_size = 0;
	rlast = 0;
	raddr = paddr;
	क्रम (i = 0; i < fw_dump.boot_mem_regs_cnt; i++) अणु
		rstart = fw_dump.boot_mem_addr[i];
		rend = rstart + fw_dump.boot_mem_sz[i];
		hole_size += (rstart - rlast);

		अगर (paddr >= rstart && paddr < rend) अणु
			raddr += fw_dump.boot_mem_dest_addr - hole_size;
			अवरोध;
		पूर्ण

		rlast = rend;
	पूर्ण

	pr_debug("vmcoreinfo: paddr = 0x%lx, raddr = 0x%lx\n", paddr, raddr);
	वापस raddr;
पूर्ण

अटल पूर्णांक fadump_create_elfcore_headers(अक्षर *bufp)
अणु
	अचिन्हित दीर्घ दीर्घ raddr, offset;
	काष्ठा elf_phdr *phdr;
	काष्ठा elfhdr *elf;
	पूर्णांक i, j;

	fadump_init_elfcore_header(bufp);
	elf = (काष्ठा elfhdr *)bufp;
	bufp += माप(काष्ठा elfhdr);

	/*
	 * setup ELF PT_NOTE, place holder क्रम cpu notes info. The notes info
	 * will be populated during second kernel boot after crash. Hence
	 * this PT_NOTE will always be the first elf note.
	 *
	 * NOTE: Any new ELF note addition should be placed after this note.
	 */
	phdr = (काष्ठा elf_phdr *)bufp;
	bufp += माप(काष्ठा elf_phdr);
	phdr->p_type = PT_NOTE;
	phdr->p_flags = 0;
	phdr->p_vaddr = 0;
	phdr->p_align = 0;

	phdr->p_offset = 0;
	phdr->p_paddr = 0;
	phdr->p_filesz = 0;
	phdr->p_memsz = 0;

	(elf->e_phnum)++;

	/* setup ELF PT_NOTE क्रम vmcoreinfo */
	phdr = (काष्ठा elf_phdr *)bufp;
	bufp += माप(काष्ठा elf_phdr);
	phdr->p_type	= PT_NOTE;
	phdr->p_flags	= 0;
	phdr->p_vaddr	= 0;
	phdr->p_align	= 0;

	phdr->p_paddr	= fadump_relocate(paddr_vmcoreinfo_note());
	phdr->p_offset	= phdr->p_paddr;
	phdr->p_memsz	= phdr->p_filesz = VMCOREINFO_NOTE_SIZE;

	/* Increment number of program headers. */
	(elf->e_phnum)++;

	/* setup PT_LOAD sections. */
	j = 0;
	offset = 0;
	raddr = fw_dump.boot_mem_addr[0];
	क्रम (i = 0; i < crash_mrange_info.mem_range_cnt; i++) अणु
		u64 mbase, msize;

		mbase = crash_mrange_info.mem_ranges[i].base;
		msize = crash_mrange_info.mem_ranges[i].size;
		अगर (!msize)
			जारी;

		phdr = (काष्ठा elf_phdr *)bufp;
		bufp += माप(काष्ठा elf_phdr);
		phdr->p_type	= PT_LOAD;
		phdr->p_flags	= PF_R|PF_W|PF_X;
		phdr->p_offset	= mbase;

		अगर (mbase == raddr) अणु
			/*
			 * The entire real memory region will be moved by
			 * firmware to the specअगरied destination_address.
			 * Hence set the correct offset.
			 */
			phdr->p_offset = fw_dump.boot_mem_dest_addr + offset;
			अगर (j < (fw_dump.boot_mem_regs_cnt - 1)) अणु
				offset += fw_dump.boot_mem_sz[j];
				raddr = fw_dump.boot_mem_addr[++j];
			पूर्ण
		पूर्ण

		phdr->p_paddr = mbase;
		phdr->p_vaddr = (अचिन्हित दीर्घ)__va(mbase);
		phdr->p_filesz = msize;
		phdr->p_memsz = msize;
		phdr->p_align = 0;

		/* Increment number of program headers. */
		(elf->e_phnum)++;
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ init_fadump_header(अचिन्हित दीर्घ addr)
अणु
	काष्ठा fadump_crash_info_header *fdh;

	अगर (!addr)
		वापस 0;

	fdh = __va(addr);
	addr += माप(काष्ठा fadump_crash_info_header);

	स_रखो(fdh, 0, माप(काष्ठा fadump_crash_info_header));
	fdh->magic_number = FADUMP_CRASH_INFO_MAGIC;
	fdh->elfcorehdr_addr = addr;
	/* We will set the crashing cpu id in crash_fadump() during crash. */
	fdh->crashing_cpu = FADUMP_CPU_UNKNOWN;

	वापस addr;
पूर्ण

अटल पूर्णांक रेजिस्टर_fadump(व्योम)
अणु
	अचिन्हित दीर्घ addr;
	व्योम *vaddr;
	पूर्णांक ret;

	/*
	 * If no memory is reserved then we can not रेजिस्टर क्रम firmware-
	 * assisted dump.
	 */
	अगर (!fw_dump.reserve_dump_area_size)
		वापस -ENODEV;

	ret = fadump_setup_crash_memory_ranges();
	अगर (ret)
		वापस ret;

	addr = fw_dump.fadumphdr_addr;

	/* Initialize fadump crash info header. */
	addr = init_fadump_header(addr);
	vaddr = __va(addr);

	pr_debug("Creating ELF core headers at %#016lx\n", addr);
	fadump_create_elfcore_headers(vaddr);

	/* रेजिस्टर the future kernel dump with firmware. */
	pr_debug("Registering for firmware-assisted kernel dump...\n");
	वापस fw_dump.ops->fadump_रेजिस्टर(&fw_dump);
पूर्ण

व्योम fadump_cleanup(व्योम)
अणु
	अगर (!fw_dump.fadump_supported)
		वापस;

	/* Invalidate the registration only अगर dump is active. */
	अगर (fw_dump.dump_active) अणु
		pr_debug("Invalidating firmware-assisted dump registration\n");
		fw_dump.ops->fadump_invalidate(&fw_dump);
	पूर्ण अन्यथा अगर (fw_dump.dump_रेजिस्टरed) अणु
		/* Un-रेजिस्टर Firmware-assisted dump अगर it was रेजिस्टरed. */
		fw_dump.ops->fadump_unरेजिस्टर(&fw_dump);
		fadump_मुक्त_mem_ranges(&crash_mrange_info);
	पूर्ण

	अगर (fw_dump.ops->fadump_cleanup)
		fw_dump.ops->fadump_cleanup(&fw_dump);
पूर्ण

अटल व्योम fadump_मुक्त_reserved_memory(अचिन्हित दीर्घ start_pfn,
					अचिन्हित दीर्घ end_pfn)
अणु
	अचिन्हित दीर्घ pfn;
	अचिन्हित दीर्घ समय_limit = jअगरfies + HZ;

	pr_info("freeing reserved memory (0x%llx - 0x%llx)\n",
		PFN_PHYS(start_pfn), PFN_PHYS(end_pfn));

	क्रम (pfn = start_pfn; pfn < end_pfn; pfn++) अणु
		मुक्त_reserved_page(pfn_to_page(pfn));

		अगर (समय_after(jअगरfies, समय_limit)) अणु
			cond_resched();
			समय_limit = jअगरfies + HZ;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Skip memory holes and मुक्त memory that was actually reserved.
 */
अटल व्योम fadump_release_reserved_area(u64 start, u64 end)
अणु
	अचिन्हित दीर्घ reg_spfn, reg_epfn;
	u64 tstart, tend, spfn, epfn;
	पूर्णांक i;

	spfn = PHYS_PFN(start);
	epfn = PHYS_PFN(end);

	क्रम_each_mem_pfn_range(i, MAX_NUMNODES, &reg_spfn, &reg_epfn, शून्य) अणु
		tstart = max_t(u64, spfn, reg_spfn);
		tend   = min_t(u64, epfn, reg_epfn);

		अगर (tstart < tend) अणु
			fadump_मुक्त_reserved_memory(tstart, tend);

			अगर (tend == epfn)
				अवरोध;

			spfn = tend;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Sort the mem ranges in-place and merge adjacent ranges
 * to minimize the memory ranges count.
 */
अटल व्योम sort_and_merge_mem_ranges(काष्ठा fadump_mrange_info *mrange_info)
अणु
	काष्ठा fadump_memory_range *mem_ranges;
	काष्ठा fadump_memory_range पंचांगp_range;
	u64 base, size;
	पूर्णांक i, j, idx;

	अगर (!reserved_mrange_info.mem_range_cnt)
		वापस;

	/* Sort the memory ranges */
	mem_ranges = mrange_info->mem_ranges;
	क्रम (i = 0; i < mrange_info->mem_range_cnt; i++) अणु
		idx = i;
		क्रम (j = (i + 1); j < mrange_info->mem_range_cnt; j++) अणु
			अगर (mem_ranges[idx].base > mem_ranges[j].base)
				idx = j;
		पूर्ण
		अगर (idx != i) अणु
			पंचांगp_range = mem_ranges[idx];
			mem_ranges[idx] = mem_ranges[i];
			mem_ranges[i] = पंचांगp_range;
		पूर्ण
	पूर्ण

	/* Merge adjacent reserved ranges */
	idx = 0;
	क्रम (i = 1; i < mrange_info->mem_range_cnt; i++) अणु
		base = mem_ranges[i-1].base;
		size = mem_ranges[i-1].size;
		अगर (mem_ranges[i].base == (base + size))
			mem_ranges[idx].size += mem_ranges[i].size;
		अन्यथा अणु
			idx++;
			अगर (i == idx)
				जारी;

			mem_ranges[idx] = mem_ranges[i];
		पूर्ण
	पूर्ण
	mrange_info->mem_range_cnt = idx + 1;
पूर्ण

/*
 * Scan reserved-ranges to consider them जबतक reserving/releasing
 * memory क्रम FADump.
 */
अटल व्योम __init early_init_dt_scan_reserved_ranges(अचिन्हित दीर्घ node)
अणु
	स्थिर __be32 *prop;
	पूर्णांक len, ret = -1;
	अचिन्हित दीर्घ i;

	/* reserved-ranges alपढ़ोy scanned */
	अगर (reserved_mrange_info.mem_range_cnt != 0)
		वापस;

	prop = of_get_flat_dt_prop(node, "reserved-ranges", &len);
	अगर (!prop)
		वापस;

	/*
	 * Each reserved range is an (address,size) pair, 2 cells each,
	 * totalling 4 cells per range.
	 */
	क्रम (i = 0; i < len / (माप(*prop) * 4); i++) अणु
		u64 base, size;

		base = of_पढ़ो_number(prop + (i * 4) + 0, 2);
		size = of_पढ़ो_number(prop + (i * 4) + 2, 2);

		अगर (size) अणु
			ret = fadump_add_mem_range(&reserved_mrange_info,
						   base, base + size);
			अगर (ret < 0) अणु
				pr_warn("some reserved ranges are ignored!\n");
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Compact reserved ranges */
	sort_and_merge_mem_ranges(&reserved_mrange_info);
पूर्ण

/*
 * Release the memory that was reserved during early boot to preserve the
 * crash'ed kernel's memory contents except reserved dump area (permanent
 * reservation) and reserved ranges used by F/W. The released memory will
 * be available क्रम general use.
 */
अटल व्योम fadump_release_memory(u64 begin, u64 end)
अणु
	u64 ra_start, ra_end, tstart;
	पूर्णांक i, ret;

	ra_start = fw_dump.reserve_dump_area_start;
	ra_end = ra_start + fw_dump.reserve_dump_area_size;

	/*
	 * If reserved ranges array limit is hit, overग_लिखो the last reserved
	 * memory range with reserved dump area to ensure it is excluded from
	 * the memory being released (reused क्रम next FADump registration).
	 */
	अगर (reserved_mrange_info.mem_range_cnt ==
	    reserved_mrange_info.max_mem_ranges)
		reserved_mrange_info.mem_range_cnt--;

	ret = fadump_add_mem_range(&reserved_mrange_info, ra_start, ra_end);
	अगर (ret != 0)
		वापस;

	/* Get the reserved ranges list in order first. */
	sort_and_merge_mem_ranges(&reserved_mrange_info);

	/* Exclude reserved ranges and release reमुख्यing memory */
	tstart = begin;
	क्रम (i = 0; i < reserved_mrange_info.mem_range_cnt; i++) अणु
		ra_start = reserved_mrange_info.mem_ranges[i].base;
		ra_end = ra_start + reserved_mrange_info.mem_ranges[i].size;

		अगर (tstart >= ra_end)
			जारी;

		अगर (tstart < ra_start)
			fadump_release_reserved_area(tstart, ra_start);
		tstart = ra_end;
	पूर्ण

	अगर (tstart < end)
		fadump_release_reserved_area(tstart, end);
पूर्ण

अटल व्योम fadump_invalidate_release_mem(व्योम)
अणु
	mutex_lock(&fadump_mutex);
	अगर (!fw_dump.dump_active) अणु
		mutex_unlock(&fadump_mutex);
		वापस;
	पूर्ण

	fadump_cleanup();
	mutex_unlock(&fadump_mutex);

	fadump_release_memory(fw_dump.boot_mem_top, memblock_end_of_DRAM());
	fadump_मुक्त_cpu_notes_buf();

	/*
	 * Setup kernel metadata and initialize the kernel dump
	 * memory काष्ठाure क्रम FADump re-registration.
	 */
	अगर (fw_dump.ops->fadump_setup_metadata &&
	    (fw_dump.ops->fadump_setup_metadata(&fw_dump) < 0))
		pr_warn("Failed to setup kernel metadata!\n");
	fw_dump.ops->fadump_init_mem_काष्ठा(&fw_dump);
पूर्ण

अटल sमाप_प्रकार release_mem_store(काष्ठा kobject *kobj,
				 काष्ठा kobj_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक input = -1;

	अगर (!fw_dump.dump_active)
		वापस -EPERM;

	अगर (kstrtoपूर्णांक(buf, 0, &input))
		वापस -EINVAL;

	अगर (input == 1) अणु
		/*
		 * Take away the '/proc/vmcore'. We are releasing the dump
		 * memory, hence it will not be valid anymore.
		 */
#अगर_घोषित CONFIG_PROC_VMCORE
		vmcore_cleanup();
#पूर्ण_अगर
		fadump_invalidate_release_mem();

	पूर्ण अन्यथा
		वापस -EINVAL;
	वापस count;
पूर्ण

/* Release the reserved memory and disable the FADump */
अटल व्योम unरेजिस्टर_fadump(व्योम)
अणु
	fadump_cleanup();
	fadump_release_memory(fw_dump.reserve_dump_area_start,
			      fw_dump.reserve_dump_area_size);
	fw_dump.fadump_enabled = 0;
	kobject_put(fadump_kobj);
पूर्ण

अटल sमाप_प्रकार enabled_show(काष्ठा kobject *kobj,
			    काष्ठा kobj_attribute *attr,
			    अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", fw_dump.fadump_enabled);
पूर्ण

अटल sमाप_प्रकार mem_reserved_show(काष्ठा kobject *kobj,
				 काष्ठा kobj_attribute *attr,
				 अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%ld\n", fw_dump.reserve_dump_area_size);
पूर्ण

अटल sमाप_प्रकार रेजिस्टरed_show(काष्ठा kobject *kobj,
			       काष्ठा kobj_attribute *attr,
			       अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", fw_dump.dump_रेजिस्टरed);
पूर्ण

अटल sमाप_प्रकार रेजिस्टरed_store(काष्ठा kobject *kobj,
				काष्ठा kobj_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret = 0;
	पूर्णांक input = -1;

	अगर (!fw_dump.fadump_enabled || fw_dump.dump_active)
		वापस -EPERM;

	अगर (kstrtoपूर्णांक(buf, 0, &input))
		वापस -EINVAL;

	mutex_lock(&fadump_mutex);

	चयन (input) अणु
	हाल 0:
		अगर (fw_dump.dump_रेजिस्टरed == 0) अणु
			जाओ unlock_out;
		पूर्ण

		/* Un-रेजिस्टर Firmware-assisted dump */
		pr_debug("Un-register firmware-assisted dump\n");
		fw_dump.ops->fadump_unरेजिस्टर(&fw_dump);
		अवरोध;
	हाल 1:
		अगर (fw_dump.dump_रेजिस्टरed == 1) अणु
			/* Un-रेजिस्टर Firmware-assisted dump */
			fw_dump.ops->fadump_unरेजिस्टर(&fw_dump);
		पूर्ण
		/* Register Firmware-assisted dump */
		ret = रेजिस्टर_fadump();
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

unlock_out:
	mutex_unlock(&fadump_mutex);
	वापस ret < 0 ? ret : count;
पूर्ण

अटल पूर्णांक fadump_region_show(काष्ठा seq_file *m, व्योम *निजी)
अणु
	अगर (!fw_dump.fadump_enabled)
		वापस 0;

	mutex_lock(&fadump_mutex);
	fw_dump.ops->fadump_region_show(&fw_dump, m);
	mutex_unlock(&fadump_mutex);
	वापस 0;
पूर्ण

अटल काष्ठा kobj_attribute release_attr = __ATTR_WO(release_mem);
अटल काष्ठा kobj_attribute enable_attr = __ATTR_RO(enabled);
अटल काष्ठा kobj_attribute रेजिस्टर_attr = __ATTR_RW(रेजिस्टरed);
अटल काष्ठा kobj_attribute mem_reserved_attr = __ATTR_RO(mem_reserved);

अटल काष्ठा attribute *fadump_attrs[] = अणु
	&enable_attr.attr,
	&रेजिस्टर_attr.attr,
	&mem_reserved_attr.attr,
	शून्य,
पूर्ण;

ATTRIBUTE_GROUPS(fadump);

DEFINE_SHOW_ATTRIBUTE(fadump_region);

अटल व्योम fadump_init_files(व्योम)
अणु
	पूर्णांक rc = 0;

	fadump_kobj = kobject_create_and_add("fadump", kernel_kobj);
	अगर (!fadump_kobj) अणु
		pr_err("failed to create fadump kobject\n");
		वापस;
	पूर्ण

	debugfs_create_file("fadump_region", 0444, घातerpc_debugfs_root, शून्य,
			    &fadump_region_fops);

	अगर (fw_dump.dump_active) अणु
		rc = sysfs_create_file(fadump_kobj, &release_attr.attr);
		अगर (rc)
			pr_err("unable to create release_mem sysfs file (%d)\n",
			       rc);
	पूर्ण

	rc = sysfs_create_groups(fadump_kobj, fadump_groups);
	अगर (rc) अणु
		pr_err("sysfs group creation failed (%d), unregistering FADump",
		       rc);
		unरेजिस्टर_fadump();
		वापस;
	पूर्ण

	/*
	 * The FADump sysfs are moved from kernel_kobj to fadump_kobj need to
	 * create symlink at old location to मुख्यtain backward compatibility.
	 *
	 *      - fadump_enabled -> fadump/enabled
	 *      - fadump_रेजिस्टरed -> fadump/रेजिस्टरed
	 *      - fadump_release_mem -> fadump/release_mem
	 */
	rc = compat_only_sysfs_link_entry_to_kobj(kernel_kobj, fadump_kobj,
						  "enabled", "fadump_enabled");
	अगर (rc) अणु
		pr_err("unable to create fadump_enabled symlink (%d)", rc);
		वापस;
	पूर्ण

	rc = compat_only_sysfs_link_entry_to_kobj(kernel_kobj, fadump_kobj,
						  "registered",
						  "fadump_registered");
	अगर (rc) अणु
		pr_err("unable to create fadump_registered symlink (%d)", rc);
		sysfs_हटाओ_link(kernel_kobj, "fadump_enabled");
		वापस;
	पूर्ण

	अगर (fw_dump.dump_active) अणु
		rc = compat_only_sysfs_link_entry_to_kobj(kernel_kobj,
							  fadump_kobj,
							  "release_mem",
							  "fadump_release_mem");
		अगर (rc)
			pr_err("unable to create fadump_release_mem symlink (%d)",
			       rc);
	पूर्ण
	वापस;
पूर्ण

/*
 * Prepare क्रम firmware-assisted dump.
 */
पूर्णांक __init setup_fadump(व्योम)
अणु
	अगर (!fw_dump.fadump_supported)
		वापस 0;

	fadump_init_files();
	fadump_show_config();

	अगर (!fw_dump.fadump_enabled)
		वापस 1;

	/*
	 * If dump data is available then see अगर it is valid and prepare क्रम
	 * saving it to the disk.
	 */
	अगर (fw_dump.dump_active) अणु
		/*
		 * अगर dump process fails then invalidate the registration
		 * and release memory beक्रमe proceeding क्रम re-registration.
		 */
		अगर (fw_dump.ops->fadump_process(&fw_dump) < 0)
			fadump_invalidate_release_mem();
	पूर्ण
	/* Initialize the kernel dump memory काष्ठाure क्रम FAD registration. */
	अन्यथा अगर (fw_dump.reserve_dump_area_size)
		fw_dump.ops->fadump_init_mem_काष्ठा(&fw_dump);

	वापस 1;
पूर्ण
subsys_initcall(setup_fadump);
#अन्यथा /* !CONFIG_PRESERVE_FA_DUMP */

/* Scan the Firmware Assisted dump configuration details. */
पूर्णांक __init early_init_dt_scan_fw_dump(अचिन्हित दीर्घ node, स्थिर अक्षर *uname,
				      पूर्णांक depth, व्योम *data)
अणु
	अगर ((depth != 1) || (म_भेद(uname, "ibm,opal") != 0))
		वापस 0;

	opal_fadump_dt_scan(&fw_dump, node);
	वापस 1;
पूर्ण

/*
 * When dump is active but PRESERVE_FA_DUMP is enabled on the kernel,
 * preserve crash data. The subsequent memory preserving kernel boot
 * is likely to process this crash data.
 */
पूर्णांक __init fadump_reserve_mem(व्योम)
अणु
	अगर (fw_dump.dump_active) अणु
		/*
		 * If last boot has crashed then reserve all the memory
		 * above boot memory to preserve crash data.
		 */
		pr_info("Preserving crash data for processing in next boot.\n");
		fadump_reserve_crash_area(fw_dump.boot_mem_top);
	पूर्ण अन्यथा
		pr_debug("FADump-aware kernel..\n");

	वापस 1;
पूर्ण
#पूर्ण_अगर /* CONFIG_PRESERVE_FA_DUMP */

/* Preserve everything above the base address */
अटल व्योम __init fadump_reserve_crash_area(u64 base)
अणु
	u64 i, mstart, mend, msize;

	क्रम_each_mem_range(i, &mstart, &mend) अणु
		msize  = mend - mstart;

		अगर ((mstart + msize) < base)
			जारी;

		अगर (mstart < base) अणु
			msize -= (base - mstart);
			mstart = base;
		पूर्ण

		pr_info("Reserving %lluMB of memory at %#016llx for preserving crash data",
			(msize >> 20), mstart);
		memblock_reserve(mstart, msize);
	पूर्ण
पूर्ण

अचिन्हित दीर्घ __init arch_reserved_kernel_pages(व्योम)
अणु
	वापस memblock_reserved_size() / PAGE_SIZE;
पूर्ण
