<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *    Initial setup-routines क्रम HP 9000 based hardware.
 *
 *    Copyright (C) 1991, 1992, 1995  Linus Torvalds
 *    Modअगरications क्रम PA-RISC (C) 1999 Helge Deller <deller@gmx.de>
 *    Modअगरications copyright 1999 SuSE GmbH (Philipp Rumpf)
 *    Modअगरications copyright 2000 Martin K. Petersen <mkp@mkp.net>
 *    Modअगरications copyright 2000 Philipp Rumpf <prumpf@tux.org>
 *    Modअगरications copyright 2001 Ryan Bradetich <rbradetich@uswest.net>
 *
 *    Initial PA-RISC Version: 04-23-1999 by Helge Deller
 */

#समावेश <linux/kernel.h>
#समावेश <linux/initrd.h>
#समावेश <linux/init.h>
#समावेश <linux/console.h>
#समावेश <linux/seq_file.h>
#घोषणा PCI_DEBUG
#समावेश <linux/pci.h>
#अघोषित PCI_DEBUG
#समावेश <linux/proc_fs.h>
#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/start_kernel.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/pdc.h>
#समावेश <यंत्र/led.h>
#समावेश <यंत्र/machdep.h>	/* क्रम pa7300lc_init() proto */
#समावेश <यंत्र/pdc_chassis.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/unwind.h>
#समावेश <यंत्र/smp.h>

अटल अक्षर __initdata command_line[COMMAND_LINE_SIZE];

/* Intended क्रम ccio/sba/cpu statistics under /proc/bus/अणुrunway|gscपूर्ण */
काष्ठा proc_dir_entry * proc_runway_root __पढ़ो_mostly = शून्य;
काष्ठा proc_dir_entry * proc_gsc_root __पढ़ो_mostly = शून्य;
काष्ठा proc_dir_entry * proc_mckinley_root __पढ़ो_mostly = शून्य;

व्योम __init setup_cmdline(अक्षर **cmdline_p)
अणु
	बाह्य अचिन्हित पूर्णांक boot_args[];

	/* Collect stuff passed in from the boot loader */

	/* boot_args[0] is मुक्त-mem start, boot_args[1] is ptr to command line */
	अगर (boot_args[0] < 64) अणु
		/* called from hpux boot loader */
		boot_command_line[0] = '\0';
	पूर्ण अन्यथा अणु
		strlcpy(boot_command_line, (अक्षर *)__va(boot_args[1]),
			COMMAND_LINE_SIZE);

#अगर_घोषित CONFIG_BLK_DEV_INITRD
		अगर (boot_args[2] != 0) /* did palo pass us a ramdisk? */
		अणु
		    initrd_start = (अचिन्हित दीर्घ)__va(boot_args[2]);
		    initrd_end = (अचिन्हित दीर्घ)__va(boot_args[3]);
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	म_नकल(command_line, boot_command_line);
	*cmdline_p = command_line;
पूर्ण

#अगर_घोषित CONFIG_PA11
व्योम __init dma_ops_init(व्योम)
अणु
	चयन (boot_cpu_data.cpu_type) अणु
	हाल pcx:
		/*
		 * We've got way too many dependencies on 1.1 semantics
		 * to support 1.0 boxes at this poपूर्णांक.
		 */
		panic(	"PA-RISC Linux currently only supports machines that conform to\n"
			"the PA-RISC 1.1 or 2.0 architecture specification.\n");

	हाल pcxl2:
		pa7300lc_init();
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण
#पूर्ण_अगर

बाह्य व्योम collect_boot_cpu_data(व्योम);

व्योम __init setup_arch(अक्षर **cmdline_p)
अणु
#अगर_घोषित CONFIG_64BIT
	बाह्य पूर्णांक parisc_narrow_firmware;
#पूर्ण_अगर
	unwind_init();

	init_per_cpu(smp_processor_id());	/* Set Modes & Enable FP */

#अगर_घोषित CONFIG_64BIT
	prपूर्णांकk(KERN_INFO "The 64-bit Kernel has started...\n");
#अन्यथा
	prपूर्णांकk(KERN_INFO "The 32-bit Kernel has started...\n");
#पूर्ण_अगर

	prपूर्णांकk(KERN_INFO "Kernel default page size is %d KB. Huge pages ",
		(पूर्णांक)(PAGE_SIZE / 1024));
#अगर_घोषित CONFIG_HUGETLB_PAGE
	prपूर्णांकk(KERN_CONT "enabled with %d MB physical and %d MB virtual size",
		 1 << (REAL_HPAGE_SHIFT - 20), 1 << (HPAGE_SHIFT - 20));
#अन्यथा
	prपूर्णांकk(KERN_CONT "disabled");
#पूर्ण_अगर
	prपूर्णांकk(KERN_CONT ".\n");

	/*
	 * Check अगर initial kernel page mappings are sufficient.
	 * panic early अगर not, अन्यथा we may access kernel functions
	 * and variables which can't be reached.
	 */
	अगर (__pa((अचिन्हित दीर्घ) &_end) >= KERNEL_INITIAL_SIZE)
		panic("KERNEL_INITIAL_ORDER too small!");

	pdc_console_init();

#अगर_घोषित CONFIG_64BIT
	अगर(parisc_narrow_firmware) अणु
		prपूर्णांकk(KERN_INFO "Kernel is using PDC in 32-bit mode.\n");
	पूर्ण
#पूर्ण_अगर
	setup_pdc();
	setup_cmdline(cmdline_p);
	collect_boot_cpu_data();
	करो_memory_inventory();  /* probe क्रम physical memory */
	parisc_cache_init();
	paging_init();

#अगर_घोषित CONFIG_CHASSIS_LCD_LED
	/* initialize the LCD/LED after boot_cpu_data is available ! */
	led_init();		/* LCD/LED initialization */
#पूर्ण_अगर

#अगर_घोषित CONFIG_PA11
	dma_ops_init();
#पूर्ण_अगर

	clear_sched_घड़ी_stable();
पूर्ण

/*
 * Display CPU info क्रम all CPUs.
 * क्रम parisc this is in processor.c
 */
बाह्य पूर्णांक show_cpuinfo (काष्ठा seq_file *m, व्योम *v);

अटल व्योम *
c_start (काष्ठा seq_file *m, loff_t *pos)
अणु
    	/* Looks like the caller will call repeatedly until we वापस
	 * 0, संकेतing खातापूर्ण perhaps.  This could be used to sequence
	 * through CPUs क्रम example.  Since we prपूर्णांक all cpu info in our
	 * show_cpuinfo() disregarding 'pos' (which I assume is 'v' above)
	 * we only allow क्रम one "position".  */
	वापस ((दीर्घ)*pos < 1) ? (व्योम *)1 : शून्य;
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
	.start	= c_start,
	.next	= c_next,
	.stop	= c_stop,
	.show	= show_cpuinfo
पूर्ण;

अटल व्योम __init parisc_proc_सूची_गढ़ो(व्योम)
अणु
	/*
	** Can't call proc_सूची_गढ़ो() until after proc_root_init() has been
	** called by start_kernel(). In other words, this code can't
	** live in arch/.../setup.c because start_parisc() calls
	** start_kernel().
	*/
	चयन (boot_cpu_data.cpu_type) अणु
	हाल pcxl:
	हाल pcxl2:
		अगर (शून्य == proc_gsc_root)
		अणु
			proc_gsc_root = proc_सूची_गढ़ो("bus/gsc", शून्य);
		पूर्ण
		अवरोध;
        हाल pcxt_:
        हाल pcxu:
        हाल pcxu_:
        हाल pcxw:
        हाल pcxw_:
        हाल pcxw2:
                अगर (शून्य == proc_runway_root)
                अणु
                        proc_runway_root = proc_सूची_गढ़ो("bus/runway", शून्य);
                पूर्ण
                अवरोध;
	हाल mako:
	हाल mako2:
                अगर (शून्य == proc_mckinley_root)
                अणु
                        proc_mckinley_root = proc_सूची_गढ़ो("bus/mckinley", शून्य);
                पूर्ण
                अवरोध;
	शेष:
		/* FIXME: this was added to prevent the compiler 
		 * complaining about missing pcx, pcxs and pcxt
		 * I'm assuming they have neither gsc nor runway */
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा resource central_bus = अणु
	.name	= "Central Bus",
	.start	= F_EXTEND(0xfff80000),
	.end    = F_EXTEND(0xfffaffff),
	.flags	= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा resource local_broadcast = अणु
	.name	= "Local Broadcast",
	.start	= F_EXTEND(0xfffb0000),
	.end	= F_EXTEND(0xfffdffff),
	.flags	= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा resource global_broadcast = अणु
	.name	= "Global Broadcast",
	.start	= F_EXTEND(0xfffe0000),
	.end	= F_EXTEND(0xffffffff),
	.flags	= IORESOURCE_MEM,
पूर्ण;

अटल पूर्णांक __init parisc_init_resources(व्योम)
अणु
	पूर्णांक result;

	result = request_resource(&iomem_resource, &central_bus);
	अगर (result < 0) अणु
		prपूर्णांकk(KERN_ERR 
		       "%s: failed to claim %s address space!\n", 
		       __खाता__, central_bus.name);
		वापस result;
	पूर्ण

	result = request_resource(&iomem_resource, &local_broadcast);
	अगर (result < 0) अणु
		prपूर्णांकk(KERN_ERR 
		       "%s: failed to claim %s address space!\n",
		       __खाता__, local_broadcast.name);
		वापस result;
	पूर्ण

	result = request_resource(&iomem_resource, &global_broadcast);
	अगर (result < 0) अणु
		prपूर्णांकk(KERN_ERR 
		       "%s: failed to claim %s address space!\n", 
		       __खाता__, global_broadcast.name);
		वापस result;
	पूर्ण

	वापस 0;
पूर्ण

बाह्य व्योम gsc_init(व्योम);
बाह्य व्योम processor_init(व्योम);
बाह्य व्योम ccio_init(व्योम);
बाह्य व्योम hppb_init(व्योम);
बाह्य व्योम dino_init(व्योम);
बाह्य व्योम iosapic_init(व्योम);
बाह्य व्योम lba_init(व्योम);
बाह्य व्योम sba_init(व्योम);
बाह्य व्योम eisa_init(व्योम);

अटल पूर्णांक __init parisc_init(व्योम)
अणु
	u32 osid = (OS_ID_LINUX << 16);

	parisc_proc_सूची_गढ़ो();
	parisc_init_resources();
	करो_device_inventory();                  /* probe क्रम hardware */

	parisc_pdc_chassis_init();
	
	/* set up a new led state on प्रणालीs shipped LED State panel */
	pdc_chassis_send_status(PDC_CHASSIS_सूचीECT_BSTART);

	/* tell PDC we're Linux. Nevermind failure. */
	pdc_stable_ग_लिखो(0x40, &osid, माप(osid));
	
	/* start with known state */
	flush_cache_all_local();
	flush_tlb_all_local(शून्य);

	processor_init();
#अगर_घोषित CONFIG_SMP
	pr_info("CPU(s): %d out of %d %s at %d.%06d MHz online\n",
		num_online_cpus(), num_present_cpus(),
#अन्यथा
	pr_info("CPU(s): 1 x %s at %d.%06d MHz\n",
#पूर्ण_अगर
			boot_cpu_data.cpu_name,
			boot_cpu_data.cpu_hz / 1000000,
			boot_cpu_data.cpu_hz % 1000000	);

#अगर defined(CONFIG_64BIT) && defined(CONFIG_SMP)
	/* Don't serialize TLB flushes अगर we run on one CPU only. */
	अगर (num_online_cpus() == 1)
		pa_serialize_tlb_flushes = 0;
#पूर्ण_अगर

	apply_alternatives_all();
	parisc_setup_cache_timing();

	/* These are in a non-obvious order, will fix when we have an iotree */
#अगर defined(CONFIG_IOSAPIC)
	iosapic_init();
#पूर्ण_अगर
#अगर defined(CONFIG_IOMMU_SBA)
	sba_init();
#पूर्ण_अगर
#अगर defined(CONFIG_PCI_LBA)
	lba_init();
#पूर्ण_अगर

	/* CCIO beक्रमe any potential subdevices */
#अगर defined(CONFIG_IOMMU_CCIO)
	ccio_init();
#पूर्ण_अगर

	/*
	 * Need to रेजिस्टर Asp & Wax beक्रमe the EISA adapters क्रम the IRQ
	 * regions.  EISA must come beक्रमe PCI to be sure it माला_लो IRQ region
	 * 0.
	 */
#अगर defined(CONFIG_GSC_LASI) || defined(CONFIG_GSC_WAX)
	gsc_init();
#पूर्ण_अगर
#अगर_घोषित CONFIG_EISA
	eisa_init();
#पूर्ण_अगर

#अगर defined(CONFIG_HPPB)
	hppb_init();
#पूर्ण_अगर

#अगर defined(CONFIG_GSC_DINO)
	dino_init();
#पूर्ण_अगर

#अगर_घोषित CONFIG_CHASSIS_LCD_LED
	रेजिस्टर_led_regions();	/* रेजिस्टर LED port info in procfs */
#पूर्ण_अगर

	वापस 0;
पूर्ण
arch_initcall(parisc_init);

व्योम __init start_parisc(व्योम)
अणु
	बाह्य व्योम early_trap_init(व्योम);

	पूर्णांक ret, cpunum;
	काष्ठा pdc_coproc_cfg coproc_cfg;

	/* check QEMU/SeaBIOS marker in PAGE0 */
	running_on_qemu = (स_भेद(&PAGE0->pad0, "SeaBIOS", 8) == 0);

	cpunum = smp_processor_id();

	init_cpu_topology();

	set_firmware_width_unlocked();

	ret = pdc_coproc_cfg_unlocked(&coproc_cfg);
	अगर (ret >= 0 && coproc_cfg.ccr_functional) अणु
		mtctl(coproc_cfg.ccr_functional, 10);

		per_cpu(cpu_data, cpunum).fp_rev = coproc_cfg.revision;
		per_cpu(cpu_data, cpunum).fp_model = coproc_cfg.model;

		यंत्र अस्थिर ("fstd	%fr0,8(%sp)");
	पूर्ण अन्यथा अणु
		panic("must have an fpu to boot linux");
	पूर्ण

	early_trap_init(); /* initialize checksum of fault_vector */

	start_kernel();
	// not reached
पूर्ण
