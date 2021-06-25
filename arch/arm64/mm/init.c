<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Based on arch/arm/mm/init.c
 *
 * Copyright (C) 1995-2005 Russell King
 * Copyright (C) 2012 ARM Ltd.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/swap.h>
#समावेश <linux/init.h>
#समावेश <linux/cache.h>
#समावेश <linux/mman.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/initrd.h>
#समावेश <linux/gfp.h>
#समावेश <linux/memblock.h>
#समावेश <linux/sort.h>
#समावेश <linux/of.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/dma-direct.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/efi.h>
#समावेश <linux/swiotlb.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mm.h>
#समावेश <linux/kexec.h>
#समावेश <linux/crash_dump.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/acpi_iort.h>

#समावेश <यंत्र/boot.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/kasan.h>
#समावेश <यंत्र/kernel-pgtable.h>
#समावेश <यंत्र/kvm_host.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/numa.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/setup.h>
#समावेश <linux/sizes.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/xen/swiotlb-xen.h>

/*
 * We need to be able to catch inadvertent references to memstart_addr
 * that occur (potentially in generic code) beक्रमe arm64_memblock_init()
 * executes, which assigns it its actual value. So use a शेष value
 * that cannot be mistaken क्रम a real physical address.
 */
s64 memstart_addr __ro_after_init = -1;
EXPORT_SYMBOL(memstart_addr);

/*
 * If the corresponding config options are enabled, we create both ZONE_DMA
 * and ZONE_DMA32. By शेष ZONE_DMA covers the 32-bit addressable memory
 * unless restricted on specअगरic platक्रमms (e.g. 30-bit on Raspberry Pi 4).
 * In such हाल, ZONE_DMA32 covers the rest of the 32-bit addressable memory,
 * otherwise it is empty.
 */
phys_addr_t arm64_dma_phys_limit __ro_after_init;

#अगर_घोषित CONFIG_KEXEC_CORE
/*
 * reserve_crashkernel() - reserves memory क्रम crash kernel
 *
 * This function reserves memory area given in "crashkernel=" kernel command
 * line parameter. The memory reserved is used by dump capture kernel when
 * primary kernel is crashing.
 */
अटल व्योम __init reserve_crashkernel(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ crash_base, crash_size;
	पूर्णांक ret;

	ret = parse_crashkernel(boot_command_line, memblock_phys_mem_size(),
				&crash_size, &crash_base);
	/* no crashkernel= or invalid value specअगरied */
	अगर (ret || !crash_size)
		वापस;

	crash_size = PAGE_ALIGN(crash_size);

	अगर (crash_base == 0) अणु
		/* Current arm64 boot protocol requires 2MB alignment */
		crash_base = memblock_find_in_range(0, arm64_dma_phys_limit,
				crash_size, SZ_2M);
		अगर (crash_base == 0) अणु
			pr_warn("cannot allocate crashkernel (size:0x%llx)\n",
				crash_size);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* User specअगरies base address explicitly. */
		अगर (!memblock_is_region_memory(crash_base, crash_size)) अणु
			pr_warn("cannot reserve crashkernel: region is not memory\n");
			वापस;
		पूर्ण

		अगर (memblock_is_region_reserved(crash_base, crash_size)) अणु
			pr_warn("cannot reserve crashkernel: region overlaps reserved memory\n");
			वापस;
		पूर्ण

		अगर (!IS_ALIGNED(crash_base, SZ_2M)) अणु
			pr_warn("cannot reserve crashkernel: base address is not 2MB aligned\n");
			वापस;
		पूर्ण
	पूर्ण
	memblock_reserve(crash_base, crash_size);

	pr_info("crashkernel reserved: 0x%016llx - 0x%016llx (%lld MB)\n",
		crash_base, crash_base + crash_size, crash_size >> 20);

	crashk_res.start = crash_base;
	crashk_res.end = crash_base + crash_size - 1;
पूर्ण
#अन्यथा
अटल व्योम __init reserve_crashkernel(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_KEXEC_CORE */

#अगर_घोषित CONFIG_CRASH_DUMP
अटल पूर्णांक __init early_init_dt_scan_elfcorehdr(अचिन्हित दीर्घ node,
		स्थिर अक्षर *uname, पूर्णांक depth, व्योम *data)
अणु
	स्थिर __be32 *reg;
	पूर्णांक len;

	अगर (depth != 1 || म_भेद(uname, "chosen") != 0)
		वापस 0;

	reg = of_get_flat_dt_prop(node, "linux,elfcorehdr", &len);
	अगर (!reg || (len < (dt_root_addr_cells + dt_root_size_cells)))
		वापस 1;

	elfcorehdr_addr = dt_mem_next_cell(dt_root_addr_cells, &reg);
	elfcorehdr_size = dt_mem_next_cell(dt_root_size_cells, &reg);

	वापस 1;
पूर्ण

/*
 * reserve_elfcorehdr() - reserves memory क्रम elf core header
 *
 * This function reserves the memory occupied by an elf core header
 * described in the device tree. This region contains all the
 * inक्रमmation about primary kernel's core image and is used by a dump
 * capture kernel to access the प्रणाली memory on primary kernel.
 */
अटल व्योम __init reserve_elfcorehdr(व्योम)
अणु
	of_scan_flat_dt(early_init_dt_scan_elfcorehdr, शून्य);

	अगर (!elfcorehdr_size)
		वापस;

	अगर (memblock_is_region_reserved(elfcorehdr_addr, elfcorehdr_size)) अणु
		pr_warn("elfcorehdr is overlapped\n");
		वापस;
	पूर्ण

	memblock_reserve(elfcorehdr_addr, elfcorehdr_size);

	pr_info("Reserving %lldKB of memory at 0x%llx for elfcorehdr\n",
		elfcorehdr_size >> 10, elfcorehdr_addr);
पूर्ण
#अन्यथा
अटल व्योम __init reserve_elfcorehdr(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_CRASH_DUMP */

/*
 * Return the maximum physical address क्रम a zone accessible by the given bits
 * limit. If DRAM starts above 32-bit, expand the zone to the maximum
 * available memory, otherwise cap it at 32-bit.
 */
अटल phys_addr_t __init max_zone_phys(अचिन्हित पूर्णांक zone_bits)
अणु
	phys_addr_t zone_mask = DMA_BIT_MASK(zone_bits);
	phys_addr_t phys_start = memblock_start_of_DRAM();

	अगर (phys_start > U32_MAX)
		zone_mask = PHYS_ADDR_MAX;
	अन्यथा अगर (phys_start > zone_mask)
		zone_mask = U32_MAX;

	वापस min(zone_mask, memblock_end_of_DRAM() - 1) + 1;
पूर्ण

अटल व्योम __init zone_sizes_init(अचिन्हित दीर्घ min, अचिन्हित दीर्घ max)
अणु
	अचिन्हित दीर्घ max_zone_pfns[MAX_NR_ZONES]  = अणु0पूर्ण;
	अचिन्हित पूर्णांक __maybe_unused acpi_zone_dma_bits;
	अचिन्हित पूर्णांक __maybe_unused dt_zone_dma_bits;
	phys_addr_t __maybe_unused dma32_phys_limit = max_zone_phys(32);

#अगर_घोषित CONFIG_ZONE_DMA
	acpi_zone_dma_bits = fls64(acpi_iort_dma_get_max_cpu_address());
	dt_zone_dma_bits = fls64(of_dma_get_max_cpu_address(शून्य));
	zone_dma_bits = min3(32U, dt_zone_dma_bits, acpi_zone_dma_bits);
	arm64_dma_phys_limit = max_zone_phys(zone_dma_bits);
	max_zone_pfns[ZONE_DMA] = PFN_DOWN(arm64_dma_phys_limit);
#पूर्ण_अगर
#अगर_घोषित CONFIG_ZONE_DMA32
	max_zone_pfns[ZONE_DMA32] = PFN_DOWN(dma32_phys_limit);
	अगर (!arm64_dma_phys_limit)
		arm64_dma_phys_limit = dma32_phys_limit;
#पूर्ण_अगर
	अगर (!arm64_dma_phys_limit)
		arm64_dma_phys_limit = PHYS_MASK + 1;
	max_zone_pfns[ZONE_NORMAL] = max;

	मुक्त_area_init(max_zone_pfns);
पूर्ण

पूर्णांक pfn_valid(अचिन्हित दीर्घ pfn)
अणु
	phys_addr_t addr = PFN_PHYS(pfn);
	काष्ठा mem_section *ms;

	/*
	 * Ensure the upper PAGE_SHIFT bits are clear in the
	 * pfn. Else it might lead to false positives when
	 * some of the upper bits are set, but the lower bits
	 * match a valid pfn.
	 */
	अगर (PHYS_PFN(addr) != pfn)
		वापस 0;

	अगर (pfn_to_section_nr(pfn) >= NR_MEM_SECTIONS)
		वापस 0;

	ms = __pfn_to_section(pfn);
	अगर (!valid_section(ms))
		वापस 0;

	/*
	 * ZONE_DEVICE memory करोes not have the memblock entries.
	 * memblock_is_map_memory() check क्रम ZONE_DEVICE based
	 * addresses will always fail. Even the normal hotplugged
	 * memory will never have MEMBLOCK_NOMAP flag set in their
	 * memblock entries. Skip memblock search क्रम all non early
	 * memory sections covering all of hotplug memory including
	 * both normal and ZONE_DEVICE based.
	 */
	अगर (!early_section(ms))
		वापस pfn_section_valid(ms, pfn);

	वापस memblock_is_map_memory(addr);
पूर्ण
EXPORT_SYMBOL(pfn_valid);

अटल phys_addr_t memory_limit = PHYS_ADDR_MAX;

/*
 * Limit the memory size that was specअगरied via FDT.
 */
अटल पूर्णांक __init early_mem(अक्षर *p)
अणु
	अगर (!p)
		वापस 1;

	memory_limit = memparse(p, &p) & PAGE_MASK;
	pr_notice("Memory limited to %lldMB\n", memory_limit >> 20);

	वापस 0;
पूर्ण
early_param("mem", early_mem);

अटल पूर्णांक __init early_init_dt_scan_usablemem(अचिन्हित दीर्घ node,
		स्थिर अक्षर *uname, पूर्णांक depth, व्योम *data)
अणु
	काष्ठा memblock_region *usablemem = data;
	स्थिर __be32 *reg;
	पूर्णांक len;

	अगर (depth != 1 || म_भेद(uname, "chosen") != 0)
		वापस 0;

	reg = of_get_flat_dt_prop(node, "linux,usable-memory-range", &len);
	अगर (!reg || (len < (dt_root_addr_cells + dt_root_size_cells)))
		वापस 1;

	usablemem->base = dt_mem_next_cell(dt_root_addr_cells, &reg);
	usablemem->size = dt_mem_next_cell(dt_root_size_cells, &reg);

	वापस 1;
पूर्ण

अटल व्योम __init fdt_enक्रमce_memory_region(व्योम)
अणु
	काष्ठा memblock_region reg = अणु
		.size = 0,
	पूर्ण;

	of_scan_flat_dt(early_init_dt_scan_usablemem, &reg);

	अगर (reg.size)
		memblock_cap_memory_range(reg.base, reg.size);
पूर्ण

व्योम __init arm64_memblock_init(व्योम)
अणु
	स्थिर s64 linear_region_size = PAGE_END - _PAGE_OFFSET(vabits_actual);

	/* Handle linux,usable-memory-range property */
	fdt_enक्रमce_memory_region();

	/* Remove memory above our supported physical address size */
	memblock_हटाओ(1ULL << PHYS_MASK_SHIFT, ULदीर्घ_उच्च);

	/*
	 * Select a suitable value क्रम the base of physical memory.
	 */
	memstart_addr = round_करोwn(memblock_start_of_DRAM(),
				   ARM64_MEMSTART_ALIGN);

	अगर ((memblock_end_of_DRAM() - memstart_addr) > linear_region_size)
		pr_warn("Memory doesn't fit in the linear mapping, VA_BITS too small\n");

	/*
	 * Remove the memory that we will not be able to cover with the
	 * linear mapping. Take care not to clip the kernel which may be
	 * high in memory.
	 */
	memblock_हटाओ(max_t(u64, memstart_addr + linear_region_size,
			__pa_symbol(_end)), ULदीर्घ_उच्च);
	अगर (memstart_addr + linear_region_size < memblock_end_of_DRAM()) अणु
		/* ensure that memstart_addr reमुख्यs sufficiently aligned */
		memstart_addr = round_up(memblock_end_of_DRAM() - linear_region_size,
					 ARM64_MEMSTART_ALIGN);
		memblock_हटाओ(0, memstart_addr);
	पूर्ण

	/*
	 * If we are running with a 52-bit kernel VA config on a प्रणाली that
	 * करोes not support it, we have to place the available physical
	 * memory in the 48-bit addressable part of the linear region, i.e.,
	 * we have to move it upward. Since memstart_addr represents the
	 * physical address of PAGE_OFFSET, we have to *subtract* from it.
	 */
	अगर (IS_ENABLED(CONFIG_ARM64_VA_BITS_52) && (vabits_actual != 52))
		memstart_addr -= _PAGE_OFFSET(48) - _PAGE_OFFSET(52);

	/*
	 * Apply the memory limit अगर it was set. Since the kernel may be loaded
	 * high up in memory, add back the kernel region that must be accessible
	 * via the linear mapping.
	 */
	अगर (memory_limit != PHYS_ADDR_MAX) अणु
		memblock_mem_limit_हटाओ_map(memory_limit);
		memblock_add(__pa_symbol(_text), (u64)(_end - _text));
	पूर्ण

	अगर (IS_ENABLED(CONFIG_BLK_DEV_INITRD) && phys_initrd_size) अणु
		/*
		 * Add back the memory we just हटाओd अगर it results in the
		 * initrd to become inaccessible via the linear mapping.
		 * Otherwise, this is a no-op
		 */
		u64 base = phys_initrd_start & PAGE_MASK;
		u64 size = PAGE_ALIGN(phys_initrd_start + phys_initrd_size) - base;

		/*
		 * We can only add back the initrd memory अगर we करोn't end up
		 * with more memory than we can address via the linear mapping.
		 * It is up to the bootloader to position the kernel and the
		 * initrd reasonably बंद to each other (i.e., within 32 GB of
		 * each other) so that all granule/#levels combinations can
		 * always access both.
		 */
		अगर (WARN(base < memblock_start_of_DRAM() ||
			 base + size > memblock_start_of_DRAM() +
				       linear_region_size,
			"initrd not fully accessible via the linear mapping -- please check your bootloader ...\n")) अणु
			phys_initrd_size = 0;
		पूर्ण अन्यथा अणु
			memblock_हटाओ(base, size); /* clear MEMBLOCK_ flags */
			memblock_add(base, size);
			memblock_reserve(base, size);
		पूर्ण
	पूर्ण

	अगर (IS_ENABLED(CONFIG_RANDOMIZE_BASE)) अणु
		बाह्य u16 memstart_offset_seed;
		u64 mmfr0 = पढ़ो_cpuid(ID_AA64MMFR0_EL1);
		पूर्णांक parange = cpuid_feature_extract_अचिन्हित_field(
					mmfr0, ID_AA64MMFR0_PARANGE_SHIFT);
		s64 range = linear_region_size -
			    BIT(id_aa64mmfr0_parange_to_phys_shअगरt(parange));

		/*
		 * If the size of the linear region exceeds, by a sufficient
		 * margin, the size of the region that the physical memory can
		 * span, अक्रमomize the linear region as well.
		 */
		अगर (memstart_offset_seed > 0 && range >= (s64)ARM64_MEMSTART_ALIGN) अणु
			range /= ARM64_MEMSTART_ALIGN;
			memstart_addr -= ARM64_MEMSTART_ALIGN *
					 ((range * memstart_offset_seed) >> 16);
		पूर्ण
	पूर्ण

	/*
	 * Register the kernel text, kernel data, initrd, and initial
	 * pagetables with memblock.
	 */
	memblock_reserve(__pa_symbol(_stext), _end - _stext);
	अगर (IS_ENABLED(CONFIG_BLK_DEV_INITRD) && phys_initrd_size) अणु
		/* the generic initrd code expects भव addresses */
		initrd_start = __phys_to_virt(phys_initrd_start);
		initrd_end = initrd_start + phys_initrd_size;
	पूर्ण

	early_init_fdt_scan_reserved_mem();

	reserve_elfcorehdr();

	high_memory = __va(memblock_end_of_DRAM() - 1) + 1;
पूर्ण

व्योम __init booपंचांगem_init(व्योम)
अणु
	अचिन्हित दीर्घ min, max;

	min = PFN_UP(memblock_start_of_DRAM());
	max = PFN_DOWN(memblock_end_of_DRAM());

	early_memtest(min << PAGE_SHIFT, max << PAGE_SHIFT);

	max_pfn = max_low_pfn = max;
	min_low_pfn = min;

	arch_numa_init();

	/*
	 * must be करोne after arch_numa_init() which calls numa_init() to
	 * initialize node_online_map that माला_लो used in hugetlb_cma_reserve()
	 * जबतक allocating required CMA size across online nodes.
	 */
#अगर defined(CONFIG_HUGETLB_PAGE) && defined(CONFIG_CMA)
	arm64_hugetlb_cma_reserve();
#पूर्ण_अगर

	dma_pernuma_cma_reserve();

	kvm_hyp_reserve();

	/*
	 * sparse_init() tries to allocate memory from memblock, so must be
	 * करोne after the fixed reservations
	 */
	sparse_init();
	zone_sizes_init(min, max);

	/*
	 * Reserve the CMA area after arm64_dma_phys_limit was initialised.
	 */
	dma_contiguous_reserve(arm64_dma_phys_limit);

	/*
	 * request_standard_resources() depends on crashkernel's memory being
	 * reserved, so करो it here.
	 */
	reserve_crashkernel();

	memblock_dump_all();
पूर्ण

/*
 * mem_init() marks the मुक्त areas in the mem_map and tells us how much memory
 * is मुक्त.  This is करोne after various parts of the प्रणाली have claimed their
 * memory after the kernel image.
 */
व्योम __init mem_init(व्योम)
अणु
	अगर (swiotlb_क्रमce == SWIOTLB_FORCE ||
	    max_pfn > PFN_DOWN(arm64_dma_phys_limit))
		swiotlb_init(1);
	अन्यथा अगर (!xen_swiotlb_detect())
		swiotlb_क्रमce = SWIOTLB_NO_FORCE;

	set_max_mapnr(max_pfn - PHYS_PFN_OFFSET);

	/* this will put all unused low memory onto the मुक्तlists */
	memblock_मुक्त_all();

	/*
	 * Check boundaries twice: Some fundamental inconsistencies can be
	 * detected at build समय alपढ़ोy.
	 */
#अगर_घोषित CONFIG_COMPAT
	BUILD_BUG_ON(TASK_SIZE_32 > DEFAULT_MAP_WINDOW_64);
#पूर्ण_अगर

	अगर (PAGE_SIZE >= 16384 && get_num_physpages() <= 128) अणु
		बाह्य पूर्णांक sysctl_overcommit_memory;
		/*
		 * On a machine this small we won't get anywhere without
		 * overcommit, so turn it on by शेष.
		 */
		sysctl_overcommit_memory = OVERCOMMIT_ALWAYS;
	पूर्ण
पूर्ण

व्योम मुक्त_iniपंचांगem(व्योम)
अणु
	मुक्त_reserved_area(lm_alias(__init_begin),
			   lm_alias(__init_end),
			   POISON_FREE_INITMEM, "unused kernel");
	/*
	 * Unmap the __init region but leave the VM area in place. This
	 * prevents the region from being reused क्रम kernel modules, which
	 * is not supported by kallsyms.
	 */
	vunmap_range((u64)__init_begin, (u64)__init_end);
पूर्ण

व्योम dump_mem_limit(व्योम)
अणु
	अगर (memory_limit != PHYS_ADDR_MAX) अणु
		pr_emerg("Memory Limit: %llu MB\n", memory_limit >> 20);
	पूर्ण अन्यथा अणु
		pr_emerg("Memory Limit: none\n");
	पूर्ण
पूर्ण
