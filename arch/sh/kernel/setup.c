<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/setup.c
 *
 * This file handles the architecture-dependent parts of initialization
 *
 *  Copyright (C) 1999  Niibe Yutaka
 *  Copyright (C) 2002 - 2010 Paul Mundt
 */
#समावेश <linux/screen_info.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/initrd.h>
#समावेश <linux/console.h>
#समावेश <linux/root_dev.h>
#समावेश <linux/utsname.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/cpu.h>
#समावेश <linux/pfn.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/kexec.h>
#समावेश <linux/module.h>
#समावेश <linux/smp.h>
#समावेश <linux/err.h>
#समावेश <linux/crash_dump.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/memblock.h>
#समावेश <linux/of.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/uaccess.h>
#समावेश <uapi/linux/mount.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/elf.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/घड़ी.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/mmzone.h>
#समावेश <यंत्र/sparseस्मृति.स>
#समावेश <यंत्र/platक्रमm_early.h>

/*
 * Initialize loops_per_jअगरfy as 10000000 (1000MIPS).
 * This value will be used at the very early stage of serial setup.
 * The bigger value means no problem.
 */
काष्ठा sh_cpuinfo cpu_data[NR_CPUS] __पढ़ो_mostly = अणु
	[0] = अणु
		.type			= CPU_SH_NONE,
		.family			= CPU_FAMILY_UNKNOWN,
		.loops_per_jअगरfy	= 10000000,
		.phys_bits		= MAX_PHYSMEM_BITS,
	पूर्ण,
पूर्ण;
EXPORT_SYMBOL(cpu_data);

/*
 * The machine vector. First entry in .machvec.init, or clobbered by
 * sh_mv= on the command line, prior to .machvec.init tearकरोwn.
 */
काष्ठा sh_machine_vector sh_mv = अणु .mv_name = "generic", पूर्ण;
EXPORT_SYMBOL(sh_mv);

#अगर_घोषित CONFIG_VT
काष्ठा screen_info screen_info;
#पूर्ण_अगर

बाह्य पूर्णांक root_mountflags;

#घोषणा RAMDISK_IMAGE_START_MASK	0x07FF
#घोषणा RAMDISK_PROMPT_FLAG		0x8000
#घोषणा RAMDISK_LOAD_FLAG		0x4000

अटल अक्षर __initdata command_line[COMMAND_LINE_SIZE] = अणु 0, पूर्ण;

अटल काष्ठा resource code_resource = अणु
	.name = "Kernel code",
	.flags = IORESOURCE_BUSY | IORESOURCE_SYSTEM_RAM,
पूर्ण;

अटल काष्ठा resource data_resource = अणु
	.name = "Kernel data",
	.flags = IORESOURCE_BUSY | IORESOURCE_SYSTEM_RAM,
पूर्ण;

अटल काष्ठा resource bss_resource = अणु
	.name	= "Kernel bss",
	.flags	= IORESOURCE_BUSY | IORESOURCE_SYSTEM_RAM,
पूर्ण;

अचिन्हित दीर्घ memory_start;
EXPORT_SYMBOL(memory_start);
अचिन्हित दीर्घ memory_end = 0;
EXPORT_SYMBOL(memory_end);
अचिन्हित दीर्घ memory_limit = 0;

अटल काष्ठा resource mem_resources[MAX_NUMNODES];

पूर्णांक l1i_cache_shape, l1d_cache_shape, l2_cache_shape;

अटल पूर्णांक __init early_parse_mem(अक्षर *p)
अणु
	अगर (!p)
		वापस 1;

	memory_limit = PAGE_ALIGN(memparse(p, &p));

	pr_notice("Memory limited to %ldMB\n", memory_limit >> 20);

	वापस 0;
पूर्ण
early_param("mem", early_parse_mem);

व्योम __init check_क्रम_initrd(व्योम)
अणु
#अगर_घोषित CONFIG_BLK_DEV_INITRD
	अचिन्हित दीर्घ start, end;

	/*
	 * Check क्रम the rare हालs where boot loaders adhere to the boot
	 * ABI.
	 */
	अगर (!LOADER_TYPE || !INITRD_START || !INITRD_SIZE)
		जाओ disable;

	start = INITRD_START + __MEMORY_START;
	end = start + INITRD_SIZE;

	अगर (unlikely(end <= start))
		जाओ disable;
	अगर (unlikely(start & ~PAGE_MASK)) अणु
		pr_err("initrd must be page aligned\n");
		जाओ disable;
	पूर्ण

	अगर (unlikely(start < __MEMORY_START)) अणु
		pr_err("initrd start (%08lx) < __MEMORY_START(%x)\n",
			start, __MEMORY_START);
		जाओ disable;
	पूर्ण

	अगर (unlikely(end > memblock_end_of_DRAM())) अणु
		pr_err("initrd extends beyond end of memory "
		       "(0x%08lx > 0x%08lx)\ndisabling initrd\n",
		       end, (अचिन्हित दीर्घ)memblock_end_of_DRAM());
		जाओ disable;
	पूर्ण

	/*
	 * If we got this far in spite of the boot loader's best efक्रमts
	 * to the contrary, assume we actually have a valid initrd and
	 * fix up the root dev.
	 */
	ROOT_DEV = Root_RAM0;

	/*
	 * Address sanitization
	 */
	initrd_start = (अचिन्हित दीर्घ)__va(start);
	initrd_end = initrd_start + INITRD_SIZE;

	memblock_reserve(__pa(initrd_start), INITRD_SIZE);

	वापस;

disable:
	pr_info("initrd disabled\n");
	initrd_start = initrd_end = 0;
#पूर्ण_अगर
पूर्ण

#अगर_अघोषित CONFIG_GENERIC_CALIBRATE_DELAY
व्योम calibrate_delay(व्योम)
अणु
	काष्ठा clk *clk = clk_get(शून्य, "cpu_clk");

	अगर (IS_ERR(clk))
		panic("Need a sane CPU clock definition!");

	loops_per_jअगरfy = (clk_get_rate(clk) >> 1) / HZ;

	prपूर्णांकk(KERN_INFO "Calibrating delay loop (skipped)... "
			 "%lu.%02lu BogoMIPS PRESET (lpj=%lu)\n",
			 loops_per_jअगरfy/(500000/HZ),
			 (loops_per_jअगरfy/(5000/HZ)) % 100,
			 loops_per_jअगरfy);
पूर्ण
#पूर्ण_अगर

व्योम __init __add_active_range(अचिन्हित पूर्णांक nid, अचिन्हित दीर्घ start_pfn,
						अचिन्हित दीर्घ end_pfn)
अणु
	काष्ठा resource *res = &mem_resources[nid];
	अचिन्हित दीर्घ start, end;

	WARN_ON(res->name); /* max one active range per node क्रम now */

	start = start_pfn << PAGE_SHIFT;
	end = end_pfn << PAGE_SHIFT;

	res->name = "System RAM";
	res->start = start;
	res->end = end - 1;
	res->flags = IORESOURCE_SYSTEM_RAM | IORESOURCE_BUSY;

	अगर (request_resource(&iomem_resource, res)) अणु
		pr_err("unable to request memory_resource 0x%lx 0x%lx\n",
		       start_pfn, end_pfn);
		वापस;
	पूर्ण

	/*
	 * We करोn't know which RAM region contains kernel data or
	 * the reserved crashkernel region, so try it repeatedly
	 * and let the resource manager test it.
	 */
	request_resource(res, &code_resource);
	request_resource(res, &data_resource);
	request_resource(res, &bss_resource);
#अगर_घोषित CONFIG_KEXEC
	request_resource(res, &crashk_res);
#पूर्ण_अगर

	/*
	 * Also make sure that there is a PMB mapping that covers this
	 * range beक्रमe we attempt to activate it, to aव्योम reset by MMU.
	 * We can hit this path with NUMA or memory hot-add.
	 */
	pmb_bolt_mapping((अचिन्हित दीर्घ)__va(start), start, end - start,
			 PAGE_KERNEL);

	memblock_set_node(PFN_PHYS(start_pfn), PFN_PHYS(end_pfn - start_pfn),
			  &memblock.memory, nid);
पूर्ण

व्योम __init __weak plat_early_device_setup(व्योम)
अणु
पूर्ण

#अगर_घोषित CONFIG_OF_FLATTREE
व्योम __ref sh_fdt_init(phys_addr_t dt_phys)
अणु
	अटल पूर्णांक करोne = 0;
	व्योम *dt_virt;

	/* Aव्योम calling an __init function on secondary cpus. */
	अगर (करोne) वापस;

#अगर_घोषित CONFIG_USE_BUILTIN_DTB
	dt_virt = __dtb_start;
#अन्यथा
	dt_virt = phys_to_virt(dt_phys);
#पूर्ण_अगर

	अगर (!dt_virt || !early_init_dt_scan(dt_virt)) अणु
		pr_crit("Error: invalid device tree blob"
			" at physical address %p\n", (व्योम *)dt_phys);

		जबतक (true)
			cpu_relax();
	पूर्ण

	करोne = 1;
पूर्ण
#पूर्ण_अगर

व्योम __init setup_arch(अक्षर **cmdline_p)
अणु
	enable_mmu();

	ROOT_DEV = old_decode_dev(ORIG_ROOT_DEV);

	prपूर्णांकk(KERN_NOTICE "Boot params:\n"
			   "... MOUNT_ROOT_RDONLY - %08lx\n"
			   "... RAMDISK_FLAGS     - %08lx\n"
			   "... ORIG_ROOT_DEV     - %08lx\n"
			   "... LOADER_TYPE       - %08lx\n"
			   "... INITRD_START      - %08lx\n"
			   "... INITRD_SIZE       - %08lx\n",
			   MOUNT_ROOT_RDONLY, RAMDISK_FLAGS,
			   ORIG_ROOT_DEV, LOADER_TYPE,
			   INITRD_START, INITRD_SIZE);

#अगर_घोषित CONFIG_BLK_DEV_RAM
	rd_image_start = RAMDISK_FLAGS & RAMDISK_IMAGE_START_MASK;
#पूर्ण_अगर

	अगर (!MOUNT_ROOT_RDONLY)
		root_mountflags &= ~MS_RDONLY;
	init_mm.start_code = (अचिन्हित दीर्घ) _text;
	init_mm.end_code = (अचिन्हित दीर्घ) _etext;
	init_mm.end_data = (अचिन्हित दीर्घ) _edata;
	init_mm.brk = (अचिन्हित दीर्घ) _end;

	code_resource.start = virt_to_phys(_text);
	code_resource.end = virt_to_phys(_etext)-1;
	data_resource.start = virt_to_phys(_etext);
	data_resource.end = virt_to_phys(_edata)-1;
	bss_resource.start = virt_to_phys(__bss_start);
	bss_resource.end = virt_to_phys(__bss_stop)-1;

#अगर_घोषित CONFIG_CMDLINE_OVERWRITE
	strlcpy(command_line, CONFIG_CMDLINE, माप(command_line));
#अन्यथा
	strlcpy(command_line, COMMAND_LINE, माप(command_line));
#अगर_घोषित CONFIG_CMDLINE_EXTEND
	strlcat(command_line, " ", माप(command_line));
	strlcat(command_line, CONFIG_CMDLINE, माप(command_line));
#पूर्ण_अगर
#पूर्ण_अगर

	/* Save unparsed command line copy क्रम /proc/cmdline */
	स_नकल(boot_command_line, command_line, COMMAND_LINE_SIZE);
	*cmdline_p = command_line;

	parse_early_param();

	plat_early_device_setup();

	sh_mv_setup();

	/* Let earlyprपूर्णांकk output early console messages */
	sh_early_platक्रमm_driver_probe("earlyprintk", 1, 1);

#अगर_घोषित CONFIG_OF_FLATTREE
#अगर_घोषित CONFIG_USE_BUILTIN_DTB
	unflatten_and_copy_device_tree();
#अन्यथा
	unflatten_device_tree();
#पूर्ण_अगर
#पूर्ण_अगर

	paging_init();

	/* Perक्रमm the machine specअगरic initialisation */
	अगर (likely(sh_mv.mv_setup))
		sh_mv.mv_setup(cmdline_p);

	plat_smp_setup();
पूर्ण

/* processor boot mode configuration */
पूर्णांक generic_mode_pins(व्योम)
अणु
	pr_warn("generic_mode_pins(): missing mode pin configuration\n");
	वापस 0;
पूर्ण

पूर्णांक test_mode_pin(पूर्णांक pin)
अणु
	वापस sh_mv.mv_mode_pins() & pin;
पूर्ण
