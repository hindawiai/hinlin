<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Based on arch/arm/kernel/setup.c
 *
 * Copyright (C) 1995-2001 Russell King
 * Copyright (C) 2012 ARM Ltd.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/initrd.h>
#समावेश <linux/console.h>
#समावेश <linux/cache.h>
#समावेश <linux/screen_info.h>
#समावेश <linux/init.h>
#समावेश <linux/kexec.h>
#समावेश <linux/root_dev.h>
#समावेश <linux/cpu.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/smp.h>
#समावेश <linux/fs.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/memblock.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/efi.h>
#समावेश <linux/psci.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/acpi.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/daअगरflags.h>
#समावेश <यंत्र/elf.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/cpu_ops.h>
#समावेश <यंत्र/kasan.h>
#समावेश <यंत्र/numa.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/efi.h>
#समावेश <यंत्र/xen/hypervisor.h>
#समावेश <यंत्र/mmu_context.h>

अटल पूर्णांक num_standard_resources;
अटल काष्ठा resource *standard_resources;

phys_addr_t __fdt_poपूर्णांकer __initdata;

/*
 * Standard memory resources
 */
अटल काष्ठा resource mem_res[] = अणु
	अणु
		.name = "Kernel code",
		.start = 0,
		.end = 0,
		.flags = IORESOURCE_SYSTEM_RAM
	पूर्ण,
	अणु
		.name = "Kernel data",
		.start = 0,
		.end = 0,
		.flags = IORESOURCE_SYSTEM_RAM
	पूर्ण
पूर्ण;

#घोषणा kernel_code mem_res[0]
#घोषणा kernel_data mem_res[1]

/*
 * The recorded values of x0 .. x3 upon kernel entry.
 */
u64 __cacheline_aligned boot_args[4];

व्योम __init smp_setup_processor_id(व्योम)
अणु
	u64 mpidr = पढ़ो_cpuid_mpidr() & MPIDR_HWID_BITMASK;
	set_cpu_logical_map(0, mpidr);

	/*
	 * clear __my_cpu_offset on boot CPU to aव्योम hang caused by
	 * using percpu variable early, क्रम example, lockdep will
	 * access percpu variable inside lock_release
	 */
	set_my_cpu_offset(0);
	pr_info("Booting Linux on physical CPU 0x%010lx [0x%08x]\n",
		(अचिन्हित दीर्घ)mpidr, पढ़ो_cpuid_id());
पूर्ण

bool arch_match_cpu_phys_id(पूर्णांक cpu, u64 phys_id)
अणु
	वापस phys_id == cpu_logical_map(cpu);
पूर्ण

काष्ठा mpidr_hash mpidr_hash;
/**
 * smp_build_mpidr_hash - Pre-compute shअगरts required at each affinity
 *			  level in order to build a linear index from an
 *			  MPIDR value. Resulting algorithm is a collision
 *			  मुक्त hash carried out through shअगरting and ORing
 */
अटल व्योम __init smp_build_mpidr_hash(व्योम)
अणु
	u32 i, affinity, fs[4], bits[4], ls;
	u64 mask = 0;
	/*
	 * Pre-scan the list of MPIDRS and filter out bits that करो
	 * not contribute to affinity levels, ie they never toggle.
	 */
	क्रम_each_possible_cpu(i)
		mask |= (cpu_logical_map(i) ^ cpu_logical_map(0));
	pr_debug("mask of set bits %#llx\n", mask);
	/*
	 * Find and stash the last and first bit set at all affinity levels to
	 * check how many bits are required to represent them.
	 */
	क्रम (i = 0; i < 4; i++) अणु
		affinity = MPIDR_AFFINITY_LEVEL(mask, i);
		/*
		 * Find the MSB bit and LSB bits position
		 * to determine how many bits are required
		 * to express the affinity level.
		 */
		ls = fls(affinity);
		fs[i] = affinity ? ffs(affinity) - 1 : 0;
		bits[i] = ls - fs[i];
	पूर्ण
	/*
	 * An index can be created from the MPIDR_EL1 by isolating the
	 * signअगरicant bits at each affinity level and by shअगरting
	 * them in order to compress the 32 bits values space to a
	 * compressed set of values. This is equivalent to hashing
	 * the MPIDR_EL1 through shअगरting and ORing. It is a collision मुक्त
	 * hash though not minimal since some levels might contain a number
	 * of CPUs that is not an exact घातer of 2 and their bit
	 * representation might contain holes, eg MPIDR_EL1[7:0] = अणु0x2, 0x80पूर्ण.
	 */
	mpidr_hash.shअगरt_aff[0] = MPIDR_LEVEL_SHIFT(0) + fs[0];
	mpidr_hash.shअगरt_aff[1] = MPIDR_LEVEL_SHIFT(1) + fs[1] - bits[0];
	mpidr_hash.shअगरt_aff[2] = MPIDR_LEVEL_SHIFT(2) + fs[2] -
						(bits[1] + bits[0]);
	mpidr_hash.shअगरt_aff[3] = MPIDR_LEVEL_SHIFT(3) +
				  fs[3] - (bits[2] + bits[1] + bits[0]);
	mpidr_hash.mask = mask;
	mpidr_hash.bits = bits[3] + bits[2] + bits[1] + bits[0];
	pr_debug("MPIDR hash: aff0[%u] aff1[%u] aff2[%u] aff3[%u] mask[%#llx] bits[%u]\n",
		mpidr_hash.shअगरt_aff[0],
		mpidr_hash.shअगरt_aff[1],
		mpidr_hash.shअगरt_aff[2],
		mpidr_hash.shअगरt_aff[3],
		mpidr_hash.mask,
		mpidr_hash.bits);
	/*
	 * 4x is an arbitrary value used to warn on a hash table much bigger
	 * than expected on most प्रणालीs.
	 */
	अगर (mpidr_hash_size() > 4 * num_possible_cpus())
		pr_warn("Large number of MPIDR hash buckets detected\n");
पूर्ण

अटल व्योम *early_fdt_ptr __initdata;

व्योम __init *get_early_fdt_ptr(व्योम)
अणु
	वापस early_fdt_ptr;
पूर्ण

यंत्रlinkage व्योम __init early_fdt_map(u64 dt_phys)
अणु
	पूर्णांक fdt_size;

	early_fixmap_init();
	early_fdt_ptr = fixmap_remap_fdt(dt_phys, &fdt_size, PAGE_KERNEL);
पूर्ण

अटल व्योम __init setup_machine_fdt(phys_addr_t dt_phys)
अणु
	पूर्णांक size;
	व्योम *dt_virt = fixmap_remap_fdt(dt_phys, &size, PAGE_KERNEL);
	स्थिर अक्षर *name;

	अगर (dt_virt)
		memblock_reserve(dt_phys, size);

	अगर (!dt_virt || !early_init_dt_scan(dt_virt)) अणु
		pr_crit("\n"
			"Error: invalid device tree blob at physical address %pa (virtual address 0x%p)\n"
			"The dtb must be 8-byte aligned and must not exceed 2 MB in size\n"
			"\nPlease check your bootloader.",
			&dt_phys, dt_virt);

		जबतक (true)
			cpu_relax();
	पूर्ण

	/* Early fixups are करोne, map the FDT as पढ़ो-only now */
	fixmap_remap_fdt(dt_phys, &size, PAGE_KERNEL_RO);

	name = of_flat_dt_get_machine_name();
	अगर (!name)
		वापस;

	pr_info("Machine model: %s\n", name);
	dump_stack_set_arch_desc("%s (DT)", name);
पूर्ण

अटल व्योम __init request_standard_resources(व्योम)
अणु
	काष्ठा memblock_region *region;
	काष्ठा resource *res;
	अचिन्हित दीर्घ i = 0;
	माप_प्रकार res_size;

	kernel_code.start   = __pa_symbol(_stext);
	kernel_code.end     = __pa_symbol(__init_begin - 1);
	kernel_data.start   = __pa_symbol(_sdata);
	kernel_data.end     = __pa_symbol(_end - 1);

	num_standard_resources = memblock.memory.cnt;
	res_size = num_standard_resources * माप(*standard_resources);
	standard_resources = memblock_alloc(res_size, SMP_CACHE_BYTES);
	अगर (!standard_resources)
		panic("%s: Failed to allocate %zu bytes\n", __func__, res_size);

	क्रम_each_mem_region(region) अणु
		res = &standard_resources[i++];
		अगर (memblock_is_nomap(region)) अणु
			res->name  = "reserved";
			res->flags = IORESOURCE_MEM;
		पूर्ण अन्यथा अणु
			res->name  = "System RAM";
			res->flags = IORESOURCE_SYSTEM_RAM | IORESOURCE_BUSY;
		पूर्ण
		res->start = __pfn_to_phys(memblock_region_memory_base_pfn(region));
		res->end = __pfn_to_phys(memblock_region_memory_end_pfn(region)) - 1;

		request_resource(&iomem_resource, res);

		अगर (kernel_code.start >= res->start &&
		    kernel_code.end <= res->end)
			request_resource(res, &kernel_code);
		अगर (kernel_data.start >= res->start &&
		    kernel_data.end <= res->end)
			request_resource(res, &kernel_data);
#अगर_घोषित CONFIG_KEXEC_CORE
		/* Userspace will find "Crash kernel" region in /proc/iomem. */
		अगर (crashk_res.end && crashk_res.start >= res->start &&
		    crashk_res.end <= res->end)
			request_resource(res, &crashk_res);
#पूर्ण_अगर
	पूर्ण
पूर्ण

अटल पूर्णांक __init reserve_memblock_reserved_regions(व्योम)
अणु
	u64 i, j;

	क्रम (i = 0; i < num_standard_resources; ++i) अणु
		काष्ठा resource *mem = &standard_resources[i];
		phys_addr_t r_start, r_end, mem_size = resource_size(mem);

		अगर (!memblock_is_region_reserved(mem->start, mem_size))
			जारी;

		क्रम_each_reserved_mem_range(j, &r_start, &r_end) अणु
			resource_माप_प्रकार start, end;

			start = max(PFN_PHYS(PFN_DOWN(r_start)), mem->start);
			end = min(PFN_PHYS(PFN_UP(r_end)) - 1, mem->end);

			अगर (start > mem->end || end < mem->start)
				जारी;

			reserve_region_with_split(mem, start, end, "reserved");
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
arch_initcall(reserve_memblock_reserved_regions);

u64 __cpu_logical_map[NR_CPUS] = अणु [0 ... NR_CPUS-1] = INVALID_HWID पूर्ण;

u64 cpu_logical_map(अचिन्हित पूर्णांक cpu)
अणु
	वापस __cpu_logical_map[cpu];
पूर्ण

व्योम __init __no_sanitize_address setup_arch(अक्षर **cmdline_p)
अणु
	init_mm.start_code = (अचिन्हित दीर्घ) _stext;
	init_mm.end_code   = (अचिन्हित दीर्घ) _etext;
	init_mm.end_data   = (अचिन्हित दीर्घ) _edata;
	init_mm.brk	   = (अचिन्हित दीर्घ) _end;

	*cmdline_p = boot_command_line;

	/*
	 * If know now we are going to need KPTI then use non-global
	 * mappings from the start, aव्योमing the cost of rewriting
	 * everything later.
	 */
	arm64_use_ng_mappings = kaslr_requires_kpti();

	early_fixmap_init();
	early_ioremap_init();

	setup_machine_fdt(__fdt_poपूर्णांकer);

	/*
	 * Initialise the अटल keys early as they may be enabled by the
	 * cpufeature code and early parameters.
	 */
	jump_label_init();
	parse_early_param();

	/*
	 * Unmask asynchronous पातs and fiq after bringing up possible
	 * earlycon. (Report possible System Errors once we can report this
	 * occurred).
	 */
	local_daअगर_restore(DAIF_PROCCTX_NOIRQ);

	/*
	 * TTBR0 is only used क्रम the identity mapping at this stage. Make it
	 * poपूर्णांक to zero page to aव्योम speculatively fetching new entries.
	 */
	cpu_uninstall_idmap();

	xen_early_init();
	efi_init();

	अगर (!efi_enabled(EFI_BOOT) && ((u64)_text % MIN_KIMG_ALIGN) != 0)
	     pr_warn(FW_BUG "Kernel image misaligned at boot, please fix your bootloader!");

	arm64_memblock_init();

	paging_init();

	acpi_table_upgrade();

	/* Parse the ACPI tables क्रम possible boot-समय configuration */
	acpi_boot_table_init();

	अगर (acpi_disabled)
		unflatten_device_tree();

	booपंचांगem_init();

	kasan_init();

	request_standard_resources();

	early_ioremap_reset();

	अगर (acpi_disabled)
		psci_dt_init();
	अन्यथा
		psci_acpi_init();

	init_bootcpu_ops();
	smp_init_cpus();
	smp_build_mpidr_hash();

	/* Init percpu seeds क्रम अक्रमom tags after cpus are set up. */
	kasan_init_sw_tags();

#अगर_घोषित CONFIG_ARM64_SW_TTBR0_PAN
	/*
	 * Make sure init_thपढ़ो_info.ttbr0 always generates translation
	 * faults in हाल uaccess_enable() is inadvertently called by the init
	 * thपढ़ो.
	 */
	init_task.thपढ़ो_info.ttbr0 = __pa_symbol(reserved_pg_dir);
#पूर्ण_अगर

	अगर (boot_args[1] || boot_args[2] || boot_args[3]) अणु
		pr_err("WARNING: x1-x3 nonzero in violation of boot protocol:\n"
			"\tx1: %016llx\n\tx2: %016llx\n\tx3: %016llx\n"
			"This indicates a broken bootloader or old kernel\n",
			boot_args[1], boot_args[2], boot_args[3]);
	पूर्ण
पूर्ण

अटल अंतरभूत bool cpu_can_disable(अचिन्हित पूर्णांक cpu)
अणु
#अगर_घोषित CONFIG_HOTPLUG_CPU
	स्थिर काष्ठा cpu_operations *ops = get_cpu_ops(cpu);

	अगर (ops && ops->cpu_can_disable)
		वापस ops->cpu_can_disable(cpu);
#पूर्ण_अगर
	वापस false;
पूर्ण

अटल पूर्णांक __init topology_init(व्योम)
अणु
	पूर्णांक i;

	क्रम_each_online_node(i)
		रेजिस्टर_one_node(i);

	क्रम_each_possible_cpu(i) अणु
		काष्ठा cpu *cpu = &per_cpu(cpu_data.cpu, i);
		cpu->hotpluggable = cpu_can_disable(i);
		रेजिस्टर_cpu(cpu, i);
	पूर्ण

	वापस 0;
पूर्ण
subsys_initcall(topology_init);

अटल व्योम dump_kernel_offset(व्योम)
अणु
	स्थिर अचिन्हित दीर्घ offset = kaslr_offset();

	अगर (IS_ENABLED(CONFIG_RANDOMIZE_BASE) && offset > 0) अणु
		pr_emerg("Kernel Offset: 0x%lx from 0x%lx\n",
			 offset, KIMAGE_VADDR);
		pr_emerg("PHYS_OFFSET: 0x%llx\n", PHYS_OFFSET);
	पूर्ण अन्यथा अणु
		pr_emerg("Kernel Offset: disabled\n");
	पूर्ण
पूर्ण

अटल पूर्णांक arm64_panic_block_dump(काष्ठा notअगरier_block *self,
				  अचिन्हित दीर्घ v, व्योम *p)
अणु
	dump_kernel_offset();
	dump_cpu_features();
	dump_mem_limit();
	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block arm64_panic_block = अणु
	.notअगरier_call = arm64_panic_block_dump
पूर्ण;

अटल पूर्णांक __init रेजिस्टर_arm64_panic_block(व्योम)
अणु
	atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list,
				       &arm64_panic_block);
	वापस 0;
पूर्ण
device_initcall(रेजिस्टर_arm64_panic_block);
