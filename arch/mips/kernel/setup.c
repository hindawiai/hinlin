<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1995 Linus Torvalds
 * Copyright (C) 1995 Walकरोrf Electronics
 * Copyright (C) 1994, 95, 96, 97, 98, 99, 2000, 01, 02, 03  Ralf Baechle
 * Copyright (C) 1996 Stoned Elipot
 * Copyright (C) 1999 Silicon Graphics, Inc.
 * Copyright (C) 2000, 2001, 2002, 2007	 Maciej W. Rozycki
 */
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/export.h>
#समावेश <linux/screen_info.h>
#समावेश <linux/memblock.h>
#समावेश <linux/initrd.h>
#समावेश <linux/root_dev.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/console.h>
#समावेश <linux/pfn.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/kexec.h>
#समावेश <linux/sizes.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/decompress/generic.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/dmi.h>
#समावेश <linux/crash_dump.h>

#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/bugs.h>
#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/cdmm.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/smp-ops.h>
#समावेश <यंत्र/prom.h>

#अगर_घोषित CONFIG_MIPS_ELF_APPENDED_DTB
अक्षर __section(".appended_dtb") __appended_dtb[0x100000];
#पूर्ण_अगर /* CONFIG_MIPS_ELF_APPENDED_DTB */

काष्ठा cpuinfo_mips cpu_data[NR_CPUS] __पढ़ो_mostly;

EXPORT_SYMBOL(cpu_data);

#अगर_घोषित CONFIG_VT
काष्ठा screen_info screen_info;
#पूर्ण_अगर

/*
 * Setup inक्रमmation
 *
 * These are initialized so they are in the .data section
 */
अचिन्हित दीर्घ mips_machtype __पढ़ो_mostly = MACH_UNKNOWN;

EXPORT_SYMBOL(mips_machtype);

अटल अक्षर __initdata command_line[COMMAND_LINE_SIZE];
अक्षर __initdata arcs_cmdline[COMMAND_LINE_SIZE];

#अगर_घोषित CONFIG_CMDLINE_BOOL
अटल स्थिर अक्षर builtin_cmdline[] __initस्थिर = CONFIG_CMDLINE;
#अन्यथा
अटल स्थिर अक्षर builtin_cmdline[] __initस्थिर = "";
#पूर्ण_अगर

/*
 * mips_io_port_base is the begin of the address space to which x86 style
 * I/O ports are mapped.
 */
अचिन्हित दीर्घ mips_io_port_base = -1;
EXPORT_SYMBOL(mips_io_port_base);

अटल काष्ठा resource code_resource = अणु .name = "Kernel code", पूर्ण;
अटल काष्ठा resource data_resource = अणु .name = "Kernel data", पूर्ण;
अटल काष्ठा resource bss_resource = अणु .name = "Kernel bss", पूर्ण;

अचिन्हित दीर्घ __kaslr_offset __ro_after_init;
EXPORT_SYMBOL(__kaslr_offset);

अटल व्योम *detect_magic __initdata = detect_memory_region;

#अगर_घोषित CONFIG_MIPS_AUTO_PFN_OFFSET
अचिन्हित दीर्घ ARCH_PFN_OFFSET;
EXPORT_SYMBOL(ARCH_PFN_OFFSET);
#पूर्ण_अगर

व्योम __init detect_memory_region(phys_addr_t start, phys_addr_t sz_min, phys_addr_t sz_max)
अणु
	व्योम *dm = &detect_magic;
	phys_addr_t size;

	क्रम (size = sz_min; size < sz_max; size <<= 1) अणु
		अगर (!स_भेद(dm, dm + size, माप(detect_magic)))
			अवरोध;
	पूर्ण

	pr_debug("Memory: %lluMB of RAM detected at 0x%llx (min: %lluMB, max: %lluMB)\n",
		((अचिन्हित दीर्घ दीर्घ) size) / SZ_1M,
		(अचिन्हित दीर्घ दीर्घ) start,
		((अचिन्हित दीर्घ दीर्घ) sz_min) / SZ_1M,
		((अचिन्हित दीर्घ दीर्घ) sz_max) / SZ_1M);

	memblock_add(start, size);
पूर्ण

/*
 * Manage initrd
 */
#अगर_घोषित CONFIG_BLK_DEV_INITRD

अटल पूर्णांक __init rd_start_early(अक्षर *p)
अणु
	अचिन्हित दीर्घ start = memparse(p, &p);

#अगर_घोषित CONFIG_64BIT
	/* Guess अगर the sign extension was क्रमgotten by bootloader */
	अगर (start < XKPHYS)
		start = (पूर्णांक)start;
#पूर्ण_अगर
	initrd_start = start;
	initrd_end += start;
	वापस 0;
पूर्ण
early_param("rd_start", rd_start_early);

अटल पूर्णांक __init rd_size_early(अक्षर *p)
अणु
	initrd_end += memparse(p, &p);
	वापस 0;
पूर्ण
early_param("rd_size", rd_size_early);

/* it वापसs the next मुक्त pfn after initrd */
अटल अचिन्हित दीर्घ __init init_initrd(व्योम)
अणु
	अचिन्हित दीर्घ end;

	/*
	 * Board specअगरic code or command line parser should have
	 * alपढ़ोy set up initrd_start and initrd_end. In these हालs
	 * perfom sanity checks and use them अगर all looks good.
	 */
	अगर (!initrd_start || initrd_end <= initrd_start)
		जाओ disable;

	अगर (initrd_start & ~PAGE_MASK) अणु
		pr_err("initrd start must be page aligned\n");
		जाओ disable;
	पूर्ण
	अगर (initrd_start < PAGE_OFFSET) अणु
		pr_err("initrd start < PAGE_OFFSET\n");
		जाओ disable;
	पूर्ण

	/*
	 * Sanitize initrd addresses. For example firmware
	 * can't guess अगर they need to pass them through
	 * 64-bits values अगर the kernel has been built in pure
	 * 32-bit. We need also to चयन from KSEG0 to XKPHYS
	 * addresses now, so the code can now safely use __pa().
	 */
	end = __pa(initrd_end);
	initrd_end = (अचिन्हित दीर्घ)__va(end);
	initrd_start = (अचिन्हित दीर्घ)__va(__pa(initrd_start));

	ROOT_DEV = Root_RAM0;
	वापस PFN_UP(end);
disable:
	initrd_start = 0;
	initrd_end = 0;
	वापस 0;
पूर्ण

/* In some conditions (e.g. big endian bootloader with a little endian
   kernel), the initrd might appear byte swapped.  Try to detect this and
   byte swap it अगर needed.  */
अटल व्योम __init maybe_bswap_initrd(व्योम)
अणु
#अगर defined(CONFIG_CPU_CAVIUM_OCTEON)
	u64 buf;

	/* Check क्रम CPIO signature */
	अगर (!स_भेद((व्योम *)initrd_start, "070701", 6))
		वापस;

	/* Check क्रम compressed initrd */
	अगर (decompress_method((अचिन्हित अक्षर *)initrd_start, 8, शून्य))
		वापस;

	/* Try again with a byte swapped header */
	buf = swab64p((u64 *)initrd_start);
	अगर (!स_भेद(&buf, "070701", 6) ||
	    decompress_method((अचिन्हित अक्षर *)(&buf), 8, शून्य)) अणु
		अचिन्हित दीर्घ i;

		pr_info("Byteswapped initrd detected\n");
		क्रम (i = initrd_start; i < ALIGN(initrd_end, 8); i += 8)
			swab64s((u64 *)i);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम __init finalize_initrd(व्योम)
अणु
	अचिन्हित दीर्घ size = initrd_end - initrd_start;

	अगर (size == 0) अणु
		prपूर्णांकk(KERN_INFO "Initrd not found or empty");
		जाओ disable;
	पूर्ण
	अगर (__pa(initrd_end) > PFN_PHYS(max_low_pfn)) अणु
		prपूर्णांकk(KERN_ERR "Initrd extends beyond end of memory");
		जाओ disable;
	पूर्ण

	maybe_bswap_initrd();

	memblock_reserve(__pa(initrd_start), size);
	initrd_below_start_ok = 1;

	pr_info("Initial ramdisk at: 0x%lx (%lu bytes)\n",
		initrd_start, size);
	वापस;
disable:
	prपूर्णांकk(KERN_CONT " - disabling initrd\n");
	initrd_start = 0;
	initrd_end = 0;
पूर्ण

#अन्यथा  /* !CONFIG_BLK_DEV_INITRD */

अटल अचिन्हित दीर्घ __init init_initrd(व्योम)
अणु
	वापस 0;
पूर्ण

#घोषणा finalize_initrd()	करो अणुपूर्ण जबतक (0)

#पूर्ण_अगर

/*
 * Initialize the booपंचांगem allocator. It also setup initrd related data
 * अगर needed.
 */
#अगर defined(CONFIG_SGI_IP27) || (defined(CONFIG_CPU_LOONGSON64) && defined(CONFIG_NUMA))

अटल व्योम __init booपंचांगem_init(व्योम)
अणु
	init_initrd();
	finalize_initrd();
पूर्ण

#अन्यथा  /* !CONFIG_SGI_IP27 */

अटल व्योम __init booपंचांगem_init(व्योम)
अणु
	phys_addr_t ramstart, ramend;
	अचिन्हित दीर्घ start, end;
	पूर्णांक i;

	ramstart = memblock_start_of_DRAM();
	ramend = memblock_end_of_DRAM();

	/*
	 * Sanity check any INITRD first. We करोn't take it पूर्णांकo account
	 * क्रम booपंचांगem setup initially, rely on the end-of-kernel-code
	 * as our memory range starting poपूर्णांक. Once booपंचांगem is inited we
	 * will reserve the area used क्रम the initrd.
	 */
	init_initrd();

	/* Reserve memory occupied by kernel. */
	memblock_reserve(__pa_symbol(&_text),
			__pa_symbol(&_end) - __pa_symbol(&_text));

	/* max_low_pfn is not a number of pages but the end pfn of low mem */

#अगर_घोषित CONFIG_MIPS_AUTO_PFN_OFFSET
	ARCH_PFN_OFFSET = PFN_UP(ramstart);
#अन्यथा
	/*
	 * Reserve any memory between the start of RAM and PHYS_OFFSET
	 */
	अगर (ramstart > PHYS_OFFSET)
		memblock_reserve(PHYS_OFFSET, ramstart - PHYS_OFFSET);

	अगर (PFN_UP(ramstart) > ARCH_PFN_OFFSET) अणु
		pr_info("Wasting %lu bytes for tracking %lu unused pages\n",
			(अचिन्हित दीर्घ)((PFN_UP(ramstart) - ARCH_PFN_OFFSET) * माप(काष्ठा page)),
			(अचिन्हित दीर्घ)(PFN_UP(ramstart) - ARCH_PFN_OFFSET));
	पूर्ण
#पूर्ण_अगर

	min_low_pfn = ARCH_PFN_OFFSET;
	max_pfn = PFN_DOWN(ramend);
	क्रम_each_mem_pfn_range(i, MAX_NUMNODES, &start, &end, शून्य) अणु
		/*
		 * Skip highmem here so we get an accurate max_low_pfn अगर low
		 * memory stops लघु of high memory.
		 * If the region overlaps HIGHMEM_START, end is clipped so
		 * max_pfn excludes the highmem portion.
		 */
		अगर (start >= PFN_DOWN(HIGHMEM_START))
			जारी;
		अगर (end > PFN_DOWN(HIGHMEM_START))
			end = PFN_DOWN(HIGHMEM_START);
		अगर (end > max_low_pfn)
			max_low_pfn = end;
	पूर्ण

	अगर (min_low_pfn >= max_low_pfn)
		panic("Incorrect memory mapping !!!");

	अगर (max_pfn > PFN_DOWN(HIGHMEM_START)) अणु
#अगर_घोषित CONFIG_HIGHMEM
		highstart_pfn = PFN_DOWN(HIGHMEM_START);
		highend_pfn = max_pfn;
#अन्यथा
		max_low_pfn = PFN_DOWN(HIGHMEM_START);
		max_pfn = max_low_pfn;
#पूर्ण_अगर
	पूर्ण

	/*
	 * Reserve initrd memory अगर needed.
	 */
	finalize_initrd();
पूर्ण

#पूर्ण_अगर	/* CONFIG_SGI_IP27 */

अटल पूर्णांक usermem __initdata;

अटल पूर्णांक __init early_parse_mem(अक्षर *p)
अणु
	phys_addr_t start, size;

	/*
	 * If a user specअगरies memory size, we
	 * blow away any स्वतःmatically generated
	 * size.
	 */
	अगर (usermem == 0) अणु
		usermem = 1;
		memblock_हटाओ(memblock_start_of_DRAM(),
			memblock_end_of_DRAM() - memblock_start_of_DRAM());
	पूर्ण
	start = 0;
	size = memparse(p, &p);
	अगर (*p == '@')
		start = memparse(p + 1, &p);

	memblock_add(start, size);

	वापस 0;
पूर्ण
early_param("mem", early_parse_mem);

अटल पूर्णांक __init early_parse_memmap(अक्षर *p)
अणु
	अक्षर *oldp;
	u64 start_at, mem_size;

	अगर (!p)
		वापस -EINVAL;

	अगर (!म_भेदन(p, "exactmap", 8)) अणु
		pr_err("\"memmap=exactmap\" invalid on MIPS\n");
		वापस 0;
	पूर्ण

	oldp = p;
	mem_size = memparse(p, &p);
	अगर (p == oldp)
		वापस -EINVAL;

	अगर (*p == '@') अणु
		start_at = memparse(p+1, &p);
		memblock_add(start_at, mem_size);
	पूर्ण अन्यथा अगर (*p == '#') अणु
		pr_err("\"memmap=nn#ss\" (force ACPI data) invalid on MIPS\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (*p == '$') अणु
		start_at = memparse(p+1, &p);
		memblock_add(start_at, mem_size);
		memblock_reserve(start_at, mem_size);
	पूर्ण अन्यथा अणु
		pr_err("\"memmap\" invalid format!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (*p == '\0') अणु
		usermem = 1;
		वापस 0;
	पूर्ण अन्यथा
		वापस -EINVAL;
पूर्ण
early_param("memmap", early_parse_memmap);

अटल व्योम __init mips_reserve_vmcore(व्योम)
अणु
#अगर_घोषित CONFIG_PROC_VMCORE
	phys_addr_t start, end;
	u64 i;

	अगर (!elfcorehdr_size) अणु
		क्रम_each_mem_range(i, &start, &end) अणु
			अगर (elfcorehdr_addr >= start && elfcorehdr_addr < end) अणु
				/*
				 * Reserve from the elf core header to the end of
				 * the memory segment, that should all be kdump
				 * reserved memory.
				 */
				elfcorehdr_size = end - elfcorehdr_addr;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	pr_info("Reserving %ldKB of memory at %ldKB for kdump\n",
		(अचिन्हित दीर्घ)elfcorehdr_size >> 10, (अचिन्हित दीर्घ)elfcorehdr_addr >> 10);

	memblock_reserve(elfcorehdr_addr, elfcorehdr_size);
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_KEXEC

/* 64M alignment क्रम crash kernel regions */
#घोषणा CRASH_ALIGN	SZ_64M
#घोषणा CRASH_ADDR_MAX	SZ_512M

अटल व्योम __init mips_parse_crashkernel(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ total_mem;
	अचिन्हित दीर्घ दीर्घ crash_size, crash_base;
	पूर्णांक ret;

	total_mem = memblock_phys_mem_size();
	ret = parse_crashkernel(boot_command_line, total_mem,
				&crash_size, &crash_base);
	अगर (ret != 0 || crash_size <= 0)
		वापस;

	अगर (crash_base <= 0) अणु
		crash_base = memblock_find_in_range(CRASH_ALIGN, CRASH_ADDR_MAX,
							crash_size, CRASH_ALIGN);
		अगर (!crash_base) अणु
			pr_warn("crashkernel reservation failed - No suitable area found.\n");
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ दीर्घ start;

		start = memblock_find_in_range(crash_base, crash_base + crash_size,
						crash_size, 1);
		अगर (start != crash_base) अणु
			pr_warn("Invalid memory region reserved for crash kernel\n");
			वापस;
		पूर्ण
	पूर्ण

	crashk_res.start = crash_base;
	crashk_res.end	 = crash_base + crash_size - 1;
पूर्ण

अटल व्योम __init request_crashkernel(काष्ठा resource *res)
अणु
	पूर्णांक ret;

	अगर (crashk_res.start == crashk_res.end)
		वापस;

	ret = request_resource(res, &crashk_res);
	अगर (!ret)
		pr_info("Reserving %ldMB of memory at %ldMB for crashkernel\n",
			(अचिन्हित दीर्घ)(resource_size(&crashk_res) >> 20),
			(अचिन्हित दीर्घ)(crashk_res.start  >> 20));
पूर्ण
#अन्यथा /* !defined(CONFIG_KEXEC)		*/
अटल व्योम __init mips_parse_crashkernel(व्योम)
अणु
पूर्ण

अटल व्योम __init request_crashkernel(काष्ठा resource *res)
अणु
पूर्ण
#पूर्ण_अगर /* !defined(CONFIG_KEXEC)  */

अटल व्योम __init check_kernel_sections_mem(व्योम)
अणु
	phys_addr_t start = __pa_symbol(&_text);
	phys_addr_t size = __pa_symbol(&_end) - start;

	अगर (!memblock_is_region_memory(start, size)) अणु
		pr_info("Kernel sections are not in the memory maps\n");
		memblock_add(start, size);
	पूर्ण
पूर्ण

अटल व्योम __init bootcmdline_append(स्थिर अक्षर *s, माप_प्रकार max)
अणु
	अगर (!s[0] || !max)
		वापस;

	अगर (boot_command_line[0])
		strlcat(boot_command_line, " ", COMMAND_LINE_SIZE);

	strlcat(boot_command_line, s, max);
पूर्ण

#अगर_घोषित CONFIG_OF_EARLY_FLATTREE

अटल पूर्णांक __init bootcmdline_scan_chosen(अचिन्हित दीर्घ node, स्थिर अक्षर *uname,
					  पूर्णांक depth, व्योम *data)
अणु
	bool *dt_bootargs = data;
	स्थिर अक्षर *p;
	पूर्णांक l;

	अगर (depth != 1 || !data ||
	    (म_भेद(uname, "chosen") != 0 && म_भेद(uname, "chosen@0") != 0))
		वापस 0;

	p = of_get_flat_dt_prop(node, "bootargs", &l);
	अगर (p != शून्य && l > 0) अणु
		bootcmdline_append(p, min(l, COMMAND_LINE_SIZE));
		*dt_bootargs = true;
	पूर्ण

	वापस 1;
पूर्ण

#पूर्ण_अगर /* CONFIG_OF_EARLY_FLATTREE */

अटल व्योम __init bootcmdline_init(व्योम)
अणु
	bool dt_bootargs = false;

	/*
	 * If CMDLINE_OVERRIDE is enabled then initializing the command line is
	 * trivial - we simply use the built-in command line unconditionally &
	 * unmodअगरied.
	 */
	अगर (IS_ENABLED(CONFIG_CMDLINE_OVERRIDE)) अणु
		strlcpy(boot_command_line, builtin_cmdline, COMMAND_LINE_SIZE);
		वापस;
	पूर्ण

	/*
	 * If the user specअगरied a built-in command line &
	 * MIPS_CMDLINE_BUILTIN_EXTEND, then the built-in command line is
	 * prepended to arguments from the bootloader or DT so we'll copy them
	 * to the start of boot_command_line here. Otherwise, empty
	 * boot_command_line to unकरो anything early_init_dt_scan_chosen() did.
	 */
	अगर (IS_ENABLED(CONFIG_MIPS_CMDLINE_BUILTIN_EXTEND))
		strlcpy(boot_command_line, builtin_cmdline, COMMAND_LINE_SIZE);
	अन्यथा
		boot_command_line[0] = 0;

#अगर_घोषित CONFIG_OF_EARLY_FLATTREE
	/*
	 * If we're configured to take boot arguments from DT, look क्रम those
	 * now.
	 */
	अगर (IS_ENABLED(CONFIG_MIPS_CMDLINE_FROM_DTB) ||
	    IS_ENABLED(CONFIG_MIPS_CMDLINE_DTB_EXTEND))
		of_scan_flat_dt(bootcmdline_scan_chosen, &dt_bootargs);
#पूर्ण_अगर

	/*
	 * If we didn't get any arguments from DT (regardless of whether that's
	 * because we weren't configured to look क्रम them, or because we looked
	 * & found none) then we'll take arguments from the bootloader.
	 * plat_mem_setup() should have filled arcs_cmdline with arguments from
	 * the bootloader.
	 */
	अगर (IS_ENABLED(CONFIG_MIPS_CMDLINE_DTB_EXTEND) || !dt_bootargs)
		bootcmdline_append(arcs_cmdline, COMMAND_LINE_SIZE);

	/*
	 * If the user specअगरied a built-in command line & we didn't alपढ़ोy
	 * prepend it, we append it to boot_command_line here.
	 */
	अगर (IS_ENABLED(CONFIG_CMDLINE_BOOL) &&
	    !IS_ENABLED(CONFIG_MIPS_CMDLINE_BUILTIN_EXTEND))
		bootcmdline_append(builtin_cmdline, COMMAND_LINE_SIZE);
पूर्ण

/*
 * arch_mem_init - initialize memory management subप्रणाली
 *
 *  o plat_mem_setup() detects the memory configuration and will record detected
 *    memory areas using memblock_add.
 *
 * At this stage the memory configuration of the प्रणाली is known to the
 * kernel but generic memory management प्रणाली is still entirely uninitialized.
 *
 *  o booपंचांगem_init()
 *  o sparse_init()
 *  o paging_init()
 *  o dma_contiguous_reserve()
 *
 * At this stage the booपंचांगem allocator is पढ़ोy to use.
 *
 * NOTE: historically plat_mem_setup did the entire platक्रमm initialization.
 *	 This was rather impractical because it meant plat_mem_setup had to
 * get away without any kind of memory allocator.  To keep old code from
 * अवरोधing plat_setup was just नामd to plat_mem_setup and a second platक्रमm
 * initialization hook क्रम anything अन्यथा was पूर्णांकroduced.
 */
अटल व्योम __init arch_mem_init(अक्षर **cmdline_p)
अणु
	/* call board setup routine */
	plat_mem_setup();
	memblock_set_bottom_up(true);

	bootcmdline_init();
	strlcpy(command_line, boot_command_line, COMMAND_LINE_SIZE);
	*cmdline_p = command_line;

	parse_early_param();

	अगर (usermem)
		pr_info("User-defined physical RAM map overwrite\n");

	check_kernel_sections_mem();

	early_init_fdt_reserve_self();
	early_init_fdt_scan_reserved_mem();

#अगर_अघोषित CONFIG_NUMA
	memblock_set_node(0, PHYS_ADDR_MAX, &memblock.memory, 0);
#पूर्ण_अगर
	booपंचांगem_init();

	/*
	 * Prevent memblock from allocating high memory.
	 * This cannot be करोne beक्रमe max_low_pfn is detected, so up
	 * to this poपूर्णांक is possible to only reserve physical memory
	 * with memblock_reserve; memblock_alloc* can be used
	 * only after this poपूर्णांक
	 */
	memblock_set_current_limit(PFN_PHYS(max_low_pfn));

	mips_reserve_vmcore();

	mips_parse_crashkernel();
#अगर_घोषित CONFIG_KEXEC
	अगर (crashk_res.start != crashk_res.end)
		memblock_reserve(crashk_res.start, resource_size(&crashk_res));
#पूर्ण_अगर
	device_tree_init();

	/*
	 * In order to reduce the possibility of kernel panic when failed to
	 * get IO TLB memory under CONFIG_SWIOTLB, it is better to allocate
	 * low memory as small as possible beक्रमe plat_swiotlb_setup(), so
	 * make sparse_init() using top-करोwn allocation.
	 */
	memblock_set_bottom_up(false);
	sparse_init();
	memblock_set_bottom_up(true);

	plat_swiotlb_setup();

	dma_contiguous_reserve(PFN_PHYS(max_low_pfn));

	/* Reserve क्रम hibernation. */
	memblock_reserve(__pa_symbol(&__nosave_begin),
		__pa_symbol(&__nosave_end) - __pa_symbol(&__nosave_begin));

	early_memtest(PFN_PHYS(ARCH_PFN_OFFSET), PFN_PHYS(max_low_pfn));
पूर्ण

अटल व्योम __init resource_init(व्योम)
अणु
	phys_addr_t start, end;
	u64 i;

	अगर (UNCAC_BASE != IO_BASE)
		वापस;

	code_resource.start = __pa_symbol(&_text);
	code_resource.end = __pa_symbol(&_etext) - 1;
	data_resource.start = __pa_symbol(&_etext);
	data_resource.end = __pa_symbol(&_edata) - 1;
	bss_resource.start = __pa_symbol(&__bss_start);
	bss_resource.end = __pa_symbol(&__bss_stop) - 1;

	क्रम_each_mem_range(i, &start, &end) अणु
		काष्ठा resource *res;

		res = memblock_alloc(माप(काष्ठा resource), SMP_CACHE_BYTES);
		अगर (!res)
			panic("%s: Failed to allocate %zu bytes\n", __func__,
			      माप(काष्ठा resource));

		res->start = start;
		/*
		 * In memblock, end poपूर्णांकs to the first byte after the
		 * range जबतक in resourses, end poपूर्णांकs to the last byte in
		 * the range.
		 */
		res->end = end - 1;
		res->flags = IORESOURCE_SYSTEM_RAM | IORESOURCE_BUSY;
		res->name = "System RAM";

		request_resource(&iomem_resource, res);

		/*
		 *  We करोn't know which RAM region contains kernel data,
		 *  so we try it repeatedly and let the resource manager
		 *  test it.
		 */
		request_resource(res, &code_resource);
		request_resource(res, &data_resource);
		request_resource(res, &bss_resource);
		request_crashkernel(res);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल व्योम __init prefill_possible_map(व्योम)
अणु
	पूर्णांक i, possible = num_possible_cpus();

	अगर (possible > nr_cpu_ids)
		possible = nr_cpu_ids;

	क्रम (i = 0; i < possible; i++)
		set_cpu_possible(i, true);
	क्रम (; i < NR_CPUS; i++)
		set_cpu_possible(i, false);

	nr_cpu_ids = possible;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम prefill_possible_map(व्योम) अणुपूर्ण
#पूर्ण_अगर

व्योम __init setup_arch(अक्षर **cmdline_p)
अणु
	cpu_probe();
	mips_cm_probe();
	prom_init();

	setup_early_fdc_console();
#अगर_घोषित CONFIG_EARLY_PRINTK
	setup_early_prपूर्णांकk();
#पूर्ण_अगर
	cpu_report();
	check_bugs_early();

#अगर defined(CONFIG_VT)
#अगर defined(CONFIG_VGA_CONSOLE)
	conचयनp = &vga_con;
#पूर्ण_अगर
#पूर्ण_अगर

	arch_mem_init(cmdline_p);
	dmi_setup();

	resource_init();
	plat_smp_setup();
	prefill_possible_map();

	cpu_cache_init();
	paging_init();

	memblock_dump_all();
पूर्ण

अचिन्हित दीर्घ kernelsp[NR_CPUS];
अचिन्हित दीर्घ fw_arg0, fw_arg1, fw_arg2, fw_arg3;

#अगर_घोषित CONFIG_DEBUG_FS
काष्ठा dentry *mips_debugfs_dir;
अटल पूर्णांक __init debugfs_mips(व्योम)
अणु
	mips_debugfs_dir = debugfs_create_dir("mips", शून्य);
	वापस 0;
पूर्ण
arch_initcall(debugfs_mips);
#पूर्ण_अगर

#अगर_घोषित CONFIG_DMA_NONCOHERENT
अटल पूर्णांक __init setcoherentio(अक्षर *str)
अणु
	dma_शेष_coherent = true;
	pr_info("Hardware DMA cache coherency (command line)\n");
	वापस 0;
पूर्ण
early_param("coherentio", setcoherentio);

अटल पूर्णांक __init setnocoherentio(अक्षर *str)
अणु
	dma_शेष_coherent = true;
	pr_info("Software DMA cache coherency (command line)\n");
	वापस 0;
पूर्ण
early_param("nocoherentio", setnocoherentio);
#पूर्ण_अगर
