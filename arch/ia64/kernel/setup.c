<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Architecture-specअगरic setup.
 *
 * Copyright (C) 1998-2001, 2003-2004 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 *	Stephane Eranian <eranian@hpl.hp.com>
 * Copyright (C) 2000, 2004 Intel Corp
 * 	Rohit Seth <rohit.seth@पूर्णांकel.com>
 * 	Suresh Siddha <suresh.b.siddha@पूर्णांकel.com>
 * 	Gorकरोn Jin <gorकरोn.jin@पूर्णांकel.com>
 * Copyright (C) 1999 VA Linux Systems
 * Copyright (C) 1999 Walt Drummond <drummond@valinux.com>
 *
 * 12/26/04 S.Siddha, G.Jin, R.Seth
 *			Add multi-thपढ़ोing and multi-core detection
 * 11/12/01 D.Mosberger Convert get_cpuinfo() to seq_file based show_cpuinfo().
 * 04/04/00 D.Mosberger नामd cpu_initialized to cpu_online_map
 * 03/31/00 R.Seth	cpu_initialized and current->processor fixes
 * 02/04/00 D.Mosberger	some more get_cpuinfo fixes...
 * 02/01/00 R.Seth	fixed get_cpuinfo क्रम SMP
 * 01/07/99 S.Eranian	added the support क्रम command line argument
 * 06/24/99 W.Drummond	added boot_cpu_data.
 * 05/28/05 Z. Menyhart	Dynamic stride size क्रम "flush_icache_range()"
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/pgtable.h>

#समावेश <linux/acpi.h>
#समावेश <linux/console.h>
#समावेश <linux/delay.h>
#समावेश <linux/cpu.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/kernel.h>
#समावेश <linux/memblock.h>
#समावेश <linux/reboot.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/माला.स>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/screen_info.h>
#समावेश <linux/dmi.h>
#समावेश <linux/root_dev.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/efi.h>
#समावेश <linux/initrd.h>
#समावेश <linux/pm.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/kexec.h>
#समावेश <linux/crash_dump.h>

#समावेश <यंत्र/mca.h>
#समावेश <यंत्र/meminit.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/patch.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/sal.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/uv/uv.h>
#समावेश <यंत्र/xtp.h>

#अगर defined(CONFIG_SMP) && (IA64_CPU_SIZE > PAGE_SIZE)
# error "struct cpuinfo_ia64 too big!"
#पूर्ण_अगर

अक्षर ia64_platक्रमm_name[64];

#अगर_घोषित CONFIG_SMP
अचिन्हित दीर्घ __per_cpu_offset[NR_CPUS];
EXPORT_SYMBOL(__per_cpu_offset);
#पूर्ण_अगर

DEFINE_PER_CPU(काष्ठा cpuinfo_ia64, ia64_cpu_info);
EXPORT_SYMBOL(ia64_cpu_info);
DEFINE_PER_CPU(अचिन्हित दीर्घ, local_per_cpu_offset);
#अगर_घोषित CONFIG_SMP
EXPORT_SYMBOL(local_per_cpu_offset);
#पूर्ण_अगर
अचिन्हित दीर्घ ia64_cycles_per_usec;
काष्ठा ia64_boot_param *ia64_boot_param;
काष्ठा screen_info screen_info;
अचिन्हित दीर्घ vga_console_iobase;
अचिन्हित दीर्घ vga_console_membase;

अटल काष्ठा resource data_resource = अणु
	.name	= "Kernel data",
	.flags	= IORESOURCE_BUSY | IORESOURCE_SYSTEM_RAM
पूर्ण;

अटल काष्ठा resource code_resource = अणु
	.name	= "Kernel code",
	.flags	= IORESOURCE_BUSY | IORESOURCE_SYSTEM_RAM
पूर्ण;

अटल काष्ठा resource bss_resource = अणु
	.name	= "Kernel bss",
	.flags	= IORESOURCE_BUSY | IORESOURCE_SYSTEM_RAM
पूर्ण;

अचिन्हित दीर्घ ia64_max_cacheline_size;

अचिन्हित दीर्घ ia64_iobase;	/* भव address क्रम I/O accesses */
EXPORT_SYMBOL(ia64_iobase);
काष्ठा io_space io_space[MAX_IO_SPACES];
EXPORT_SYMBOL(io_space);
अचिन्हित पूर्णांक num_io_spaces;

/*
 * "flush_icache_range()" needs to know what processor dependent stride size to use
 * when it makes i-cache(s) coherent with d-caches.
 */
#घोषणा	I_CACHE_STRIDE_SHIFT	5	/* Safest way to go: 32 bytes by 32 bytes */
अचिन्हित दीर्घ ia64_i_cache_stride_shअगरt = ~0;
/*
 * "clflush_cache_range()" needs to know what processor dependent stride size to
 * use when it flushes cache lines including both d-cache and i-cache.
 */
/* Safest way to go: 32 bytes by 32 bytes */
#घोषणा	CACHE_STRIDE_SHIFT	5
अचिन्हित दीर्घ ia64_cache_stride_shअगरt = ~0;

/*
 * We use a special marker क्रम the end of memory and it uses the extra (+1) slot
 */
काष्ठा rsvd_region rsvd_region[IA64_MAX_RSVD_REGIONS + 1] __initdata;
पूर्णांक num_rsvd_regions __initdata;


/*
 * Filter incoming memory segments based on the primitive map created from the boot
 * parameters. Segments contained in the map are हटाओd from the memory ranges. A
 * caller-specअगरied function is called with the memory ranges that reमुख्य after filtering.
 * This routine करोes not assume the incoming segments are sorted.
 */
पूर्णांक __init
filter_rsvd_memory (u64 start, u64 end, व्योम *arg)
अणु
	u64 range_start, range_end, prev_start;
	व्योम (*func)(अचिन्हित दीर्घ, अचिन्हित दीर्घ, पूर्णांक);
	पूर्णांक i;

#अगर IGNORE_PFN0
	अगर (start == PAGE_OFFSET) अणु
		prपूर्णांकk(KERN_WARNING "warning: skipping physical page 0\n");
		start += PAGE_SIZE;
		अगर (start >= end) वापस 0;
	पूर्ण
#पूर्ण_अगर
	/*
	 * lowest possible address(walker uses भव)
	 */
	prev_start = PAGE_OFFSET;
	func = arg;

	क्रम (i = 0; i < num_rsvd_regions; ++i) अणु
		range_start = max(start, prev_start);
		range_end   = min(end, rsvd_region[i].start);

		अगर (range_start < range_end)
			call_pernode_memory(__pa(range_start), range_end - range_start, func);

		/* nothing more available in this segment */
		अगर (range_end == end) वापस 0;

		prev_start = rsvd_region[i].end;
	पूर्ण
	/* end of memory marker allows full processing inside loop body */
	वापस 0;
पूर्ण

/*
 * Similar to "filter_rsvd_memory()", but the reserved memory ranges
 * are not filtered out.
 */
पूर्णांक __init
filter_memory(u64 start, u64 end, व्योम *arg)
अणु
	व्योम (*func)(अचिन्हित दीर्घ, अचिन्हित दीर्घ, पूर्णांक);

#अगर IGNORE_PFN0
	अगर (start == PAGE_OFFSET) अणु
		prपूर्णांकk(KERN_WARNING "warning: skipping physical page 0\n");
		start += PAGE_SIZE;
		अगर (start >= end)
			वापस 0;
	पूर्ण
#पूर्ण_अगर
	func = arg;
	अगर (start < end)
		call_pernode_memory(__pa(start), end - start, func);
	वापस 0;
पूर्ण

अटल व्योम __init
sort_regions (काष्ठा rsvd_region *rsvd_region, पूर्णांक max)
अणु
	पूर्णांक j;

	/* simple bubble sorting */
	जबतक (max--) अणु
		क्रम (j = 0; j < max; ++j) अणु
			अगर (rsvd_region[j].start > rsvd_region[j+1].start) अणु
				काष्ठा rsvd_region पंचांगp;
				पंचांगp = rsvd_region[j];
				rsvd_region[j] = rsvd_region[j + 1];
				rsvd_region[j + 1] = पंचांगp;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/* merge overlaps */
अटल पूर्णांक __init
merge_regions (काष्ठा rsvd_region *rsvd_region, पूर्णांक max)
अणु
	पूर्णांक i;
	क्रम (i = 1; i < max; ++i) अणु
		अगर (rsvd_region[i].start >= rsvd_region[i-1].end)
			जारी;
		अगर (rsvd_region[i].end > rsvd_region[i-1].end)
			rsvd_region[i-1].end = rsvd_region[i].end;
		--max;
		स_हटाओ(&rsvd_region[i], &rsvd_region[i+1],
			(max - i) * माप(काष्ठा rsvd_region));
	पूर्ण
	वापस max;
पूर्ण

/*
 * Request address space क्रम all standard resources
 */
अटल पूर्णांक __init रेजिस्टर_memory(व्योम)
अणु
	code_resource.start = ia64_tpa(_text);
	code_resource.end   = ia64_tpa(_etext) - 1;
	data_resource.start = ia64_tpa(_etext);
	data_resource.end   = ia64_tpa(_edata) - 1;
	bss_resource.start  = ia64_tpa(__bss_start);
	bss_resource.end    = ia64_tpa(_end) - 1;
	efi_initialize_iomem_resources(&code_resource, &data_resource,
			&bss_resource);

	वापस 0;
पूर्ण

__initcall(रेजिस्टर_memory);


#अगर_घोषित CONFIG_KEXEC

/*
 * This function checks अगर the reserved crashkernel is allowed on the specअगरic
 * IA64 machine flavour. Machines without an IO TLB use swiotlb and require
 * some memory below 4 GB (i.e. in 32 bit area), see the implementation of
 * kernel/dma/swiotlb.c. The hpzx1 architecture has an IO TLB but cannot use that
 * in kdump हाल. See the comment in sba_init() in sba_iommu.c.
 *
 * So, the only machvec that really supports loading the kdump kernel
 * over 4 GB is "uv".
 */
अटल पूर्णांक __init check_crashkernel_memory(अचिन्हित दीर्घ pbase, माप_प्रकार size)
अणु
	अगर (is_uv_प्रणाली())
		वापस 1;
	अन्यथा
		वापस pbase < (1UL << 32);
पूर्ण

अटल व्योम __init setup_crashkernel(अचिन्हित दीर्घ total, पूर्णांक *n)
अणु
	अचिन्हित दीर्घ दीर्घ base = 0, size = 0;
	पूर्णांक ret;

	ret = parse_crashkernel(boot_command_line, total,
			&size, &base);
	अगर (ret == 0 && size > 0) अणु
		अगर (!base) अणु
			sort_regions(rsvd_region, *n);
			*n = merge_regions(rsvd_region, *n);
			base = kdump_find_rsvd_region(size,
					rsvd_region, *n);
		पूर्ण

		अगर (!check_crashkernel_memory(base, size)) अणु
			pr_warn("crashkernel: There would be kdump memory "
				"at %ld GB but this is unusable because it "
				"must\nbe below 4 GB. Change the memory "
				"configuration of the machine.\n",
				(अचिन्हित दीर्घ)(base >> 30));
			वापस;
		पूर्ण

		अगर (base != ~0UL) अणु
			prपूर्णांकk(KERN_INFO "Reserving %ldMB of memory at %ldMB "
					"for crashkernel (System RAM: %ldMB)\n",
					(अचिन्हित दीर्घ)(size >> 20),
					(अचिन्हित दीर्घ)(base >> 20),
					(अचिन्हित दीर्घ)(total >> 20));
			rsvd_region[*n].start =
				(अचिन्हित दीर्घ)__va(base);
			rsvd_region[*n].end =
				(अचिन्हित दीर्घ)__va(base + size);
			(*n)++;
			crashk_res.start = base;
			crashk_res.end = base + size - 1;
		पूर्ण
	पूर्ण
	efi_memmap_res.start = ia64_boot_param->efi_memmap;
	efi_memmap_res.end = efi_memmap_res.start +
		ia64_boot_param->efi_memmap_size;
	boot_param_res.start = __pa(ia64_boot_param);
	boot_param_res.end = boot_param_res.start +
		माप(*ia64_boot_param);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम __init setup_crashkernel(अचिन्हित दीर्घ total, पूर्णांक *n)
अणुपूर्ण
#पूर्ण_अगर

/**
 * reserve_memory - setup reserved memory areas
 *
 * Setup the reserved memory areas set aside क्रम the boot parameters,
 * initrd, etc.  There are currently %IA64_MAX_RSVD_REGIONS defined,
 * see arch/ia64/include/यंत्र/meminit.h अगर you need to define more.
 */
व्योम __init
reserve_memory (व्योम)
अणु
	पूर्णांक n = 0;
	अचिन्हित दीर्घ total_memory;

	/*
	 * none of the entries in this table overlap
	 */
	rsvd_region[n].start = (अचिन्हित दीर्घ) ia64_boot_param;
	rsvd_region[n].end   = rsvd_region[n].start + माप(*ia64_boot_param);
	n++;

	rsvd_region[n].start = (अचिन्हित दीर्घ) __va(ia64_boot_param->efi_memmap);
	rsvd_region[n].end   = rsvd_region[n].start + ia64_boot_param->efi_memmap_size;
	n++;

	rsvd_region[n].start = (अचिन्हित दीर्घ) __va(ia64_boot_param->command_line);
	rsvd_region[n].end   = (rsvd_region[n].start
				+ म_माप(__va(ia64_boot_param->command_line)) + 1);
	n++;

	rsvd_region[n].start = (अचिन्हित दीर्घ) ia64_imva((व्योम *)KERNEL_START);
	rsvd_region[n].end   = (अचिन्हित दीर्घ) ia64_imva(_end);
	n++;

#अगर_घोषित CONFIG_BLK_DEV_INITRD
	अगर (ia64_boot_param->initrd_start) अणु
		rsvd_region[n].start = (अचिन्हित दीर्घ)__va(ia64_boot_param->initrd_start);
		rsvd_region[n].end   = rsvd_region[n].start + ia64_boot_param->initrd_size;
		n++;
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_CRASH_DUMP
	अगर (reserve_elfcorehdr(&rsvd_region[n].start,
			       &rsvd_region[n].end) == 0)
		n++;
#पूर्ण_अगर

	total_memory = efi_memmap_init(&rsvd_region[n].start, &rsvd_region[n].end);
	n++;

	setup_crashkernel(total_memory, &n);

	/* end of memory marker */
	rsvd_region[n].start = ~0UL;
	rsvd_region[n].end   = ~0UL;
	n++;

	num_rsvd_regions = n;
	BUG_ON(IA64_MAX_RSVD_REGIONS + 1 < n);

	sort_regions(rsvd_region, num_rsvd_regions);
	num_rsvd_regions = merge_regions(rsvd_region, num_rsvd_regions);

	/* reserve all regions except the end of memory marker with memblock */
	क्रम (n = 0; n < num_rsvd_regions - 1; n++) अणु
		काष्ठा rsvd_region *region = &rsvd_region[n];
		phys_addr_t addr = __pa(region->start);
		phys_addr_t size = region->end - region->start;

		memblock_reserve(addr, size);
	पूर्ण
पूर्ण

/**
 * find_initrd - get initrd parameters from the boot parameter काष्ठाure
 *
 * Grab the initrd start and end from the boot parameter काष्ठा given us by
 * the boot loader.
 */
व्योम __init
find_initrd (व्योम)
अणु
#अगर_घोषित CONFIG_BLK_DEV_INITRD
	अगर (ia64_boot_param->initrd_start) अणु
		initrd_start = (अचिन्हित दीर्घ)__va(ia64_boot_param->initrd_start);
		initrd_end   = initrd_start+ia64_boot_param->initrd_size;

		prपूर्णांकk(KERN_INFO "Initial ramdisk at: 0x%lx (%llu bytes)\n",
		       initrd_start, ia64_boot_param->initrd_size);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम __init
io_port_init (व्योम)
अणु
	अचिन्हित दीर्घ phys_iobase;

	/*
	 * Set `iobase' based on the EFI memory map or, failing that, the
	 * value firmware left in ar.k0.
	 *
	 * Note that in ia32 mode, IN/OUT inकाष्ठाions use ar.k0 to compute
	 * the port's भव address, so ia32_load_state() loads it with a
	 * user भव address.  But in ia64 mode, glibc uses the
	 * *physical* address in ar.k0 to mmap the appropriate area from
	 * /dev/mem, and the inX()/outX() पूर्णांकerfaces use MMIO.  In both
	 * हालs, user-mode can only use the legacy 0-64K I/O port space.
	 *
	 * ar.k0 is not involved in kernel I/O port accesses, which can use
	 * any of the I/O port spaces and are करोne via MMIO using the
	 * भव mmio_base from the appropriate io_space[].
	 */
	phys_iobase = efi_get_iobase();
	अगर (!phys_iobase) अणु
		phys_iobase = ia64_get_kr(IA64_KR_IO_BASE);
		prपूर्णांकk(KERN_INFO "No I/O port range found in EFI memory map, "
			"falling back to AR.KR0 (0x%lx)\n", phys_iobase);
	पूर्ण
	ia64_iobase = (अचिन्हित दीर्घ) ioremap(phys_iobase, 0);
	ia64_set_kr(IA64_KR_IO_BASE, __pa(ia64_iobase));

	/* setup legacy IO port space */
	io_space[0].mmio_base = ia64_iobase;
	io_space[0].sparse = 1;
	num_io_spaces = 1;
पूर्ण

/**
 * early_console_setup - setup debugging console
 *
 * Consoles started here require little enough setup that we can start using
 * them very early in the boot process, either right after the machine
 * vector initialization, or even beक्रमe अगर the drivers can detect their hw.
 *
 * Returns non-zero अगर a console couldn't be setup.
 */
अटल अंतरभूत पूर्णांक __init
early_console_setup (अक्षर *cmdline)
अणु
#अगर_घोषित CONFIG_EFI_PCDP
	अगर (!efi_setup_pcdp_console(cmdline))
		वापस 0;
#पूर्ण_अगर
	वापस -1;
पूर्ण

अटल व्योम __init
screen_info_setup(व्योम)
अणु
	अचिन्हित पूर्णांक orig_x, orig_y, num_cols, num_rows, font_height;

	स_रखो(&screen_info, 0, माप(screen_info));

	अगर (!ia64_boot_param->console_info.num_rows ||
	    !ia64_boot_param->console_info.num_cols) अणु
		prपूर्णांकk(KERN_WARNING "invalid screen-info, guessing 80x25\n");
		orig_x = 0;
		orig_y = 0;
		num_cols = 80;
		num_rows = 25;
		font_height = 16;
	पूर्ण अन्यथा अणु
		orig_x = ia64_boot_param->console_info.orig_x;
		orig_y = ia64_boot_param->console_info.orig_y;
		num_cols = ia64_boot_param->console_info.num_cols;
		num_rows = ia64_boot_param->console_info.num_rows;
		font_height = 400 / num_rows;
	पूर्ण

	screen_info.orig_x = orig_x;
	screen_info.orig_y = orig_y;
	screen_info.orig_video_cols  = num_cols;
	screen_info.orig_video_lines = num_rows;
	screen_info.orig_video_poपूर्णांकs = font_height;
	screen_info.orig_video_mode = 3;	/* XXX fake */
	screen_info.orig_video_isVGA = 1;	/* XXX fake */
	screen_info.orig_video_ega_bx = 3;	/* XXX fake */
पूर्ण

अटल अंतरभूत व्योम
mark_bsp_online (व्योम)
अणु
#अगर_घोषित CONFIG_SMP
	/* If we रेजिस्टर an early console, allow CPU 0 to prपूर्णांकk */
	set_cpu_online(smp_processor_id(), true);
#पूर्ण_अगर
पूर्ण

अटल __initdata पूर्णांक nomca;
अटल __init पूर्णांक setup_nomca(अक्षर *s)
अणु
	nomca = 1;
	वापस 0;
पूर्ण
early_param("nomca", setup_nomca);

#अगर_घोषित CONFIG_CRASH_DUMP
पूर्णांक __init reserve_elfcorehdr(u64 *start, u64 *end)
अणु
	u64 length;

	/* We get the address using the kernel command line,
	 * but the size is extracted from the EFI tables.
	 * Both address and size are required क्रम reservation
	 * to work properly.
	 */

	अगर (!is_vmcore_usable())
		वापस -EINVAL;

	अगर ((length = vmcore_find_descriptor_size(elfcorehdr_addr)) == 0) अणु
		vmcore_unusable();
		वापस -EINVAL;
	पूर्ण

	*start = (अचिन्हित दीर्घ)__va(elfcorehdr_addr);
	*end = *start + length;
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_PROC_VMCORE */

व्योम __init
setup_arch (अक्षर **cmdline_p)
अणु
	unw_init();

	ia64_patch_vtop((u64) __start___vtop_patchlist, (u64) __end___vtop_patchlist);

	*cmdline_p = __va(ia64_boot_param->command_line);
	strlcpy(boot_command_line, *cmdline_p, COMMAND_LINE_SIZE);

	efi_init();
	io_port_init();

	uv_probe_प्रणाली_type();
	parse_early_param();

	अगर (early_console_setup(*cmdline_p) == 0)
		mark_bsp_online();

	/* Initialize the ACPI boot-समय table parser */
	acpi_table_init();
	early_acpi_boot_init();
#अगर_घोषित CONFIG_ACPI_NUMA
	acpi_numa_init();
	acpi_numa_fixup();
#अगर_घोषित CONFIG_ACPI_HOTPLUG_CPU
	prefill_possible_map();
#पूर्ण_अगर
	per_cpu_scan_finalize((cpumask_weight(&early_cpu_possible_map) == 0 ?
		32 : cpumask_weight(&early_cpu_possible_map)),
		additional_cpus > 0 ? additional_cpus : 0);
#पूर्ण_अगर /* CONFIG_ACPI_NUMA */

#अगर_घोषित CONFIG_SMP
	smp_build_cpu_map();
#पूर्ण_अगर
	find_memory();

	/* process SAL प्रणाली table: */
	ia64_sal_init(__va(sal_systab_phys));

#अगर_घोषित CONFIG_ITANIUM
	ia64_patch_rse((u64) __start___rse_patchlist, (u64) __end___rse_patchlist);
#अन्यथा
	अणु
		अचिन्हित दीर्घ num_phys_stacked;

		अगर (ia64_pal_rse_info(&num_phys_stacked, 0) == 0 && num_phys_stacked > 96)
			ia64_patch_rse((u64) __start___rse_patchlist, (u64) __end___rse_patchlist);
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP
	cpu_physical_id(0) = hard_smp_processor_id();
#पूर्ण_अगर

	cpu_init();	/* initialize the bootstrap CPU */
	mmu_context_init();	/* initialize context_id biपंचांगap */

#अगर_घोषित CONFIG_VT
	अगर (!conचयनp) अणु
# अगर defined(CONFIG_VGA_CONSOLE)
		/*
		 * Non-legacy प्रणालीs may route legacy VGA MMIO range to प्रणाली
		 * memory.  vga_con probes the MMIO hole, so memory looks like
		 * a VGA device to it.  The EFI memory map can tell us अगर it's
		 * memory so we can aव्योम this problem.
		 */
		अगर (efi_mem_type(0xA0000) != EFI_CONVENTIONAL_MEMORY)
			conचयनp = &vga_con;
# endअगर
	पूर्ण
#पूर्ण_अगर

	/* enable IA-64 Machine Check Abort Handling unless disabled */
	अगर (!nomca)
		ia64_mca_init();

	/*
	 * Default to /dev/sda2.  This assumes that the EFI partition
	 * is physical disk 1 partition 1 and the Linux root disk is
	 * physical disk 1 partition 2.
	 */
	ROOT_DEV = Root_SDA2;		/* शेष to second partition on first drive */

	अगर (is_uv_प्रणाली())
		uv_setup(cmdline_p);
#अगर_घोषित CONFIG_SMP
	अन्यथा
		init_smp_config();
#पूर्ण_अगर

	screen_info_setup();
	paging_init();

	clear_sched_घड़ी_stable();
पूर्ण

/*
 * Display cpu info क्रम all CPUs.
 */
अटल पूर्णांक
show_cpuinfo (काष्ठा seq_file *m, व्योम *v)
अणु
#अगर_घोषित CONFIG_SMP
#	define lpj	c->loops_per_jअगरfy
#	define cpunum	c->cpu
#अन्यथा
#	define lpj	loops_per_jअगरfy
#	define cpunum	0
#पूर्ण_अगर
	अटल काष्ठा अणु
		अचिन्हित दीर्घ mask;
		स्थिर अक्षर *feature_name;
	पूर्ण feature_bits[] = अणु
		अणु 1UL << 0, "branchlong" पूर्ण,
		अणु 1UL << 1, "spontaneous deferral"पूर्ण,
		अणु 1UL << 2, "16-byte atomic ops" पूर्ण
	पूर्ण;
	अक्षर features[128], *cp, *sep;
	काष्ठा cpuinfo_ia64 *c = v;
	अचिन्हित दीर्घ mask;
	अचिन्हित दीर्घ proc_freq;
	पूर्णांक i, size;

	mask = c->features;

	/* build the feature string: */
	स_नकल(features, "standard", 9);
	cp = features;
	size = माप(features);
	sep = "";
	क्रम (i = 0; i < ARRAY_SIZE(feature_bits) && size > 1; ++i) अणु
		अगर (mask & feature_bits[i].mask) अणु
			cp += snम_लिखो(cp, size, "%s%s", sep,
				       feature_bits[i].feature_name),
			sep = ", ";
			mask &= ~feature_bits[i].mask;
			size = माप(features) - (cp - features);
		पूर्ण
	पूर्ण
	अगर (mask && size > 1) अणु
		/* prपूर्णांक unknown features as a hex value */
		snम_लिखो(cp, size, "%s0x%lx", sep, mask);
	पूर्ण

	proc_freq = cpufreq_quick_get(cpunum);
	अगर (!proc_freq)
		proc_freq = c->proc_freq / 1000;

	seq_म_लिखो(m,
		   "processor  : %d\n"
		   "vendor     : %s\n"
		   "arch       : IA-64\n"
		   "family     : %u\n"
		   "model      : %u\n"
		   "model name : %s\n"
		   "revision   : %u\n"
		   "archrev    : %u\n"
		   "features   : %s\n"
		   "cpu number : %lu\n"
		   "cpu regs   : %u\n"
		   "cpu MHz    : %lu.%03lu\n"
		   "itc MHz    : %lu.%06lu\n"
		   "BogoMIPS   : %lu.%02lu\n",
		   cpunum, c->venकरोr, c->family, c->model,
		   c->model_name, c->revision, c->archrev,
		   features, c->ppn, c->number,
		   proc_freq / 1000, proc_freq % 1000,
		   c->itc_freq / 1000000, c->itc_freq % 1000000,
		   lpj*HZ/500000, (lpj*HZ/5000) % 100);
#अगर_घोषित CONFIG_SMP
	seq_म_लिखो(m, "siblings   : %u\n",
		   cpumask_weight(&cpu_core_map[cpunum]));
	अगर (c->socket_id != -1)
		seq_म_लिखो(m, "physical id: %u\n", c->socket_id);
	अगर (c->thपढ़ोs_per_core > 1 || c->cores_per_socket > 1)
		seq_म_लिखो(m,
			   "core id    : %u\n"
			   "thread id  : %u\n",
			   c->core_id, c->thपढ़ो_id);
#पूर्ण_अगर
	seq_म_लिखो(m,"\n");

	वापस 0;
पूर्ण

अटल व्योम *
c_start (काष्ठा seq_file *m, loff_t *pos)
अणु
#अगर_घोषित CONFIG_SMP
	जबतक (*pos < nr_cpu_ids && !cpu_online(*pos))
		++*pos;
#पूर्ण_अगर
	वापस *pos < nr_cpu_ids ? cpu_data(*pos) : शून्य;
पूर्ण

अटल व्योम *
c_next (काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	++*pos;
	वापस c_start(m, pos);
पूर्ण

अटल व्योम
c_stop (काष्ठा seq_file *m, व्योम *v)
अणु
पूर्ण

स्थिर काष्ठा seq_operations cpuinfo_op = अणु
	.start =	c_start,
	.next =		c_next,
	.stop =		c_stop,
	.show =		show_cpuinfo
पूर्ण;

#घोषणा MAX_BRANDS	8
अटल अक्षर bअक्रमname[MAX_BRANDS][128];

अटल अक्षर *
get_model_name(__u8 family, __u8 model)
अणु
	अटल पूर्णांक overflow;
	अक्षर bअक्रम[128];
	पूर्णांक i;

	स_नकल(bअक्रम, "Unknown", 8);
	अगर (ia64_pal_get_bअक्रम_info(bअक्रम)) अणु
		अगर (family == 0x7)
			स_नकल(bअक्रम, "Merced", 7);
		अन्यथा अगर (family == 0x1f) चयन (model) अणु
			हाल 0: स_नकल(bअक्रम, "McKinley", 9); अवरोध;
			हाल 1: स_नकल(bअक्रम, "Madison", 8); अवरोध;
			हाल 2: स_नकल(bअक्रम, "Madison up to 9M cache", 23); अवरोध;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < MAX_BRANDS; i++)
		अगर (म_भेद(bअक्रमname[i], bअक्रम) == 0)
			वापस bअक्रमname[i];
	क्रम (i = 0; i < MAX_BRANDS; i++)
		अगर (bअक्रमname[i][0] == '\0')
			वापस म_नकल(bअक्रमname[i], bअक्रम);
	अगर (overflow++ == 0)
		prपूर्णांकk(KERN_ERR
		       "%s: Table overflow. Some processor model information will be missing\n",
		       __func__);
	वापस "Unknown";
पूर्ण

अटल व्योम
identअगरy_cpu (काष्ठा cpuinfo_ia64 *c)
अणु
	जोड़ अणु
		अचिन्हित दीर्घ bits[5];
		काष्ठा अणु
			/* id 0 & 1: */
			अक्षर venकरोr[16];

			/* id 2 */
			u64 ppn;		/* processor serial number */

			/* id 3: */
			अचिन्हित number		:  8;
			अचिन्हित revision	:  8;
			अचिन्हित model		:  8;
			अचिन्हित family		:  8;
			अचिन्हित archrev	:  8;
			अचिन्हित reserved	: 24;

			/* id 4: */
			u64 features;
		पूर्ण field;
	पूर्ण cpuid;
	pal_vm_info_1_u_t vm1;
	pal_vm_info_2_u_t vm2;
	pal_status_t status;
	अचिन्हित दीर्घ impl_va_msb = 50, phys_addr_size = 44;	/* Itanium शेषs */
	पूर्णांक i;
	क्रम (i = 0; i < 5; ++i)
		cpuid.bits[i] = ia64_get_cpuid(i);

	स_नकल(c->venकरोr, cpuid.field.venकरोr, 16);
#अगर_घोषित CONFIG_SMP
	c->cpu = smp_processor_id();

	/* below शेष values will be overwritten  by identअगरy_siblings() 
	 * क्रम Multi-Thपढ़ोing/Multi-Core capable CPUs
	 */
	c->thपढ़ोs_per_core = c->cores_per_socket = c->num_log = 1;
	c->socket_id = -1;

	identअगरy_siblings(c);

	अगर (c->thपढ़ोs_per_core > smp_num_siblings)
		smp_num_siblings = c->thपढ़ोs_per_core;
#पूर्ण_अगर
	c->ppn = cpuid.field.ppn;
	c->number = cpuid.field.number;
	c->revision = cpuid.field.revision;
	c->model = cpuid.field.model;
	c->family = cpuid.field.family;
	c->archrev = cpuid.field.archrev;
	c->features = cpuid.field.features;
	c->model_name = get_model_name(c->family, c->model);

	status = ia64_pal_vm_summary(&vm1, &vm2);
	अगर (status == PAL_STATUS_SUCCESS) अणु
		impl_va_msb = vm2.pal_vm_info_2_s.impl_va_msb;
		phys_addr_size = vm1.pal_vm_info_1_s.phys_add_size;
	पूर्ण
	c->unimpl_va_mask = ~((7L<<61) | ((1L << (impl_va_msb + 1)) - 1));
	c->unimpl_pa_mask = ~((1L<<63) | ((1L << phys_addr_size) - 1));
पूर्ण

/*
 * Do the following calculations:
 *
 * 1. the max. cache line size.
 * 2. the minimum of the i-cache stride sizes क्रम "flush_icache_range()".
 * 3. the minimum of the cache stride sizes क्रम "clflush_cache_range()".
 */
अटल व्योम
get_cache_info(व्योम)
अणु
	अचिन्हित दीर्घ line_size, max = 1;
	अचिन्हित दीर्घ l, levels, unique_caches;
	pal_cache_config_info_t cci;
	दीर्घ status;

        status = ia64_pal_cache_summary(&levels, &unique_caches);
        अगर (status != 0) अणु
                prपूर्णांकk(KERN_ERR "%s: ia64_pal_cache_summary() failed (status=%ld)\n",
                       __func__, status);
                max = SMP_CACHE_BYTES;
		/* Safest setup क्रम "flush_icache_range()" */
		ia64_i_cache_stride_shअगरt = I_CACHE_STRIDE_SHIFT;
		/* Safest setup क्रम "clflush_cache_range()" */
		ia64_cache_stride_shअगरt = CACHE_STRIDE_SHIFT;
		जाओ out;
        पूर्ण

	क्रम (l = 0; l < levels; ++l) अणु
		/* cache_type (data_or_unअगरied)=2 */
		status = ia64_pal_cache_config_info(l, 2, &cci);
		अगर (status != 0) अणु
			prपूर्णांकk(KERN_ERR "%s: ia64_pal_cache_config_info"
				"(l=%lu, 2) failed (status=%ld)\n",
				__func__, l, status);
			max = SMP_CACHE_BYTES;
			/* The safest setup क्रम "flush_icache_range()" */
			cci.pcci_stride = I_CACHE_STRIDE_SHIFT;
			/* The safest setup क्रम "clflush_cache_range()" */
			ia64_cache_stride_shअगरt = CACHE_STRIDE_SHIFT;
			cci.pcci_unअगरied = 1;
		पूर्ण अन्यथा अणु
			अगर (cci.pcci_stride < ia64_cache_stride_shअगरt)
				ia64_cache_stride_shअगरt = cci.pcci_stride;

			line_size = 1 << cci.pcci_line_size;
			अगर (line_size > max)
				max = line_size;
		पूर्ण

		अगर (!cci.pcci_unअगरied) अणु
			/* cache_type (inकाष्ठाion)=1*/
			status = ia64_pal_cache_config_info(l, 1, &cci);
			अगर (status != 0) अणु
				prपूर्णांकk(KERN_ERR "%s: ia64_pal_cache_config_info"
					"(l=%lu, 1) failed (status=%ld)\n",
					__func__, l, status);
				/* The safest setup क्रम flush_icache_range() */
				cci.pcci_stride = I_CACHE_STRIDE_SHIFT;
			पूर्ण
		पूर्ण
		अगर (cci.pcci_stride < ia64_i_cache_stride_shअगरt)
			ia64_i_cache_stride_shअगरt = cci.pcci_stride;
	पूर्ण
  out:
	अगर (max > ia64_max_cacheline_size)
		ia64_max_cacheline_size = max;
पूर्ण

/*
 * cpu_init() initializes state that is per-CPU.  This function acts
 * as a 'CPU state barrier', nothing should get across.
 */
व्योम
cpu_init (व्योम)
अणु
	बाह्य व्योम ia64_mmu_init(व्योम *);
	अटल अचिन्हित दीर्घ max_num_phys_stacked = IA64_NUM_PHYS_STACK_REG;
	अचिन्हित दीर्घ num_phys_stacked;
	pal_vm_info_2_u_t vmi;
	अचिन्हित पूर्णांक max_ctx;
	काष्ठा cpuinfo_ia64 *cpu_info;
	व्योम *cpu_data;

	cpu_data = per_cpu_init();
#अगर_घोषित CONFIG_SMP
	/*
	 * insert boot cpu पूर्णांकo sibling and core mapes
	 * (must be करोne after per_cpu area is setup)
	 */
	अगर (smp_processor_id() == 0) अणु
		cpumask_set_cpu(0, &per_cpu(cpu_sibling_map, 0));
		cpumask_set_cpu(0, &cpu_core_map[0]);
	पूर्ण अन्यथा अणु
		/*
		 * Set ar.k3 so that assembly code in MCA handler can compute
		 * physical addresses of per cpu variables with a simple:
		 *   phys = ar.k3 + &per_cpu_var
		 * and the alt-dtlb-miss handler can set per-cpu mapping पूर्णांकo
		 * the TLB when needed. head.S alपढ़ोy did this क्रम cpu0.
		 */
		ia64_set_kr(IA64_KR_PER_CPU_DATA,
			    ia64_tpa(cpu_data) - (दीर्घ) __per_cpu_start);
	पूर्ण
#पूर्ण_अगर

	get_cache_info();

	/*
	 * We can't pass "local_cpu_data" to identify_cpu() because we haven't called
	 * ia64_mmu_init() yet.  And we can't call ia64_mmu_init() first because it
	 * depends on the data वापसed by identअगरy_cpu().  We अवरोध the dependency by
	 * accessing cpu_data() through the canonical per-CPU address.
	 */
	cpu_info = cpu_data + ((अक्षर *) &__ia64_per_cpu_var(ia64_cpu_info) - __per_cpu_start);
	identअगरy_cpu(cpu_info);

#अगर_घोषित CONFIG_MCKINLEY
	अणु
#		define FEATURE_SET 16
		काष्ठा ia64_pal_retval iprv;

		अगर (cpu_info->family == 0x1f) अणु
			PAL_CALL_PHYS(iprv, PAL_PROC_GET_FEATURES, 0, FEATURE_SET, 0);
			अगर ((iprv.status == 0) && (iprv.v0 & 0x80) && (iprv.v2 & 0x80))
				PAL_CALL_PHYS(iprv, PAL_PROC_SET_FEATURES,
				              (iprv.v1 | 0x80), FEATURE_SET, 0);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/* Clear the stack memory reserved क्रम pt_regs: */
	स_रखो(task_pt_regs(current), 0, माप(काष्ठा pt_regs));

	ia64_set_kr(IA64_KR_FPU_OWNER, 0);

	/*
	 * Initialize the page-table base रेजिस्टर to a global
	 * directory with all zeroes.  This ensure that we can handle
	 * TLB-misses to user address-space even beक्रमe we created the
	 * first user address-space.  This may happen, e.g., due to
	 * aggressive use of lfetch.fault.
	 */
	ia64_set_kr(IA64_KR_PT_BASE, __pa(ia64_imva(empty_zero_page)));

	/*
	 * Initialize शेष control रेजिस्टर to defer speculative faults except
	 * क्रम those arising from TLB misses, which are not deferred.  The
	 * kernel MUST NOT depend on a particular setting of these bits (in other words,
	 * the kernel must have recovery code क्रम all speculative accesses).  Turn on
	 * dcr.lc as per recommendation by the architecture team.  Most IA-32 apps
	 * shouldn't be affected by this (moral: keep your ia32 locks aligned and you'll
	 * be fine).
	 */
	ia64_setreg(_IA64_REG_CR_DCR,  (  IA64_DCR_DP | IA64_DCR_DK | IA64_DCR_DX | IA64_DCR_DR
					| IA64_DCR_DA | IA64_DCR_DD | IA64_DCR_LC));
	mmgrab(&init_mm);
	current->active_mm = &init_mm;
	BUG_ON(current->mm);

	ia64_mmu_init(ia64_imva(cpu_data));
	ia64_mca_cpu_init(ia64_imva(cpu_data));

	/* Clear ITC to eliminate sched_घड़ी() overflows in human समय.  */
	ia64_set_itc(0);

	/* disable all local पूर्णांकerrupt sources: */
	ia64_set_itv(1 << 16);
	ia64_set_lrr0(1 << 16);
	ia64_set_lrr1(1 << 16);
	ia64_setreg(_IA64_REG_CR_PMV, 1 << 16);
	ia64_setreg(_IA64_REG_CR_CMCV, 1 << 16);

	/* clear TPR & XTP to enable all पूर्णांकerrupt classes: */
	ia64_setreg(_IA64_REG_CR_TPR, 0);

	/* Clear any pending पूर्णांकerrupts left by SAL/EFI */
	जबतक (ia64_get_ivr() != IA64_SPURIOUS_INT_VECTOR)
		ia64_eoi();

#अगर_घोषित CONFIG_SMP
	normal_xtp();
#पूर्ण_अगर

	/* set ia64_ctx.max_rid to the maximum RID that is supported by all CPUs: */
	अगर (ia64_pal_vm_summary(शून्य, &vmi) == 0) अणु
		max_ctx = (1U << (vmi.pal_vm_info_2_s.rid_size - 3)) - 1;
		setup_ptcg_sem(vmi.pal_vm_info_2_s.max_purges, NPTCG_FROM_PAL);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_WARNING "cpu_init: PAL VM summary failed, assuming 18 RID bits\n");
		max_ctx = (1U << 15) - 1;	/* use architected minimum */
	पूर्ण
	जबतक (max_ctx < ia64_ctx.max_ctx) अणु
		अचिन्हित पूर्णांक old = ia64_ctx.max_ctx;
		अगर (cmpxchg(&ia64_ctx.max_ctx, old, max_ctx) == old)
			अवरोध;
	पूर्ण

	अगर (ia64_pal_rse_info(&num_phys_stacked, शून्य) != 0) अणु
		prपूर्णांकk(KERN_WARNING "cpu_init: PAL RSE info failed; assuming 96 physical "
		       "stacked regs\n");
		num_phys_stacked = 96;
	पूर्ण
	/* size of physical stacked रेजिस्टर partition plus 8 bytes: */
	अगर (num_phys_stacked > max_num_phys_stacked) अणु
		ia64_patch_phys_stack_reg(num_phys_stacked*8 + 8);
		max_num_phys_stacked = num_phys_stacked;
	पूर्ण
पूर्ण

व्योम __init
check_bugs (व्योम)
अणु
	ia64_patch_mckinley_e9((अचिन्हित दीर्घ) __start___mckinley_e9_bundles,
			       (अचिन्हित दीर्घ) __end___mckinley_e9_bundles);
पूर्ण

अटल पूर्णांक __init run_dmi_scan(व्योम)
अणु
	dmi_setup();
	वापस 0;
पूर्ण
core_initcall(run_dmi_scan);
