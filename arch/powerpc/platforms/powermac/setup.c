<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Powermac setup and early boot code plus other अक्रमom bits.
 *
 *  PowerPC version
 *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)
 *
 *  Adapted क्रम Power Macपूर्णांकosh by Paul Mackerras
 *    Copyright (C) 1996 Paul Mackerras (paulus@samba.org)
 *
 *  Derived from "arch/alpha/kernel/setup.c"
 *    Copyright (C) 1995 Linus Torvalds
 *
 *  Maपूर्णांकained by Benjamin Herrenschmidt (benh@kernel.crashing.org)
 */

/*
 * bootup setup stuff..
 */

#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/unistd.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/export.h>
#समावेश <linux/user.h>
#समावेश <linux/tty.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/major.h>
#समावेश <linux/initrd.h>
#समावेश <linux/vt_kern.h>
#समावेश <linux/console.h>
#समावेश <linux/pci.h>
#समावेश <linux/adb.h>
#समावेश <linux/cuda.h>
#समावेश <linux/pmu.h>
#समावेश <linux/irq.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/root_dev.h>
#समावेश <linux/bitops.h>
#समावेश <linux/suspend.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/ohare.h>
#समावेश <यंत्र/mediabay.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/btext.h>
#समावेश <यंत्र/pmac_feature.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/smu.h>
#समावेश <यंत्र/pmc.h>
#समावेश <यंत्र/udbg.h>

#समावेश "pmac.h"

#अघोषित SHOW_GATWICK_IRQS

पूर्णांक ppc_override_l2cr = 0;
पूर्णांक ppc_override_l2cr_value;
पूर्णांक has_l2cache = 0;

पूर्णांक pmac_newworld;

अटल पूर्णांक current_root_goodness = -1;

बाह्य काष्ठा machdep_calls pmac_md;

#घोषणा DEFAULT_ROOT_DEVICE Root_SDA1	/* sda1 - slightly silly choice */

#अगर_घोषित CONFIG_PPC64
पूर्णांक sccdbg;
#पूर्ण_अगर

sys_ctrler_t sys_ctrler = SYS_CTRLER_UNKNOWN;
EXPORT_SYMBOL(sys_ctrler);

अटल व्योम pmac_show_cpuinfo(काष्ठा seq_file *m)
अणु
	काष्ठा device_node *np;
	स्थिर अक्षर *pp;
	पूर्णांक plen;
	पूर्णांक mbmodel;
	अचिन्हित पूर्णांक mbflags;
	अक्षर* mbname;

	mbmodel = pmac_call_feature(PMAC_FTR_GET_MB_INFO, शून्य,
				    PMAC_MB_INFO_MODEL, 0);
	mbflags = pmac_call_feature(PMAC_FTR_GET_MB_INFO, शून्य,
				    PMAC_MB_INFO_FLAGS, 0);
	अगर (pmac_call_feature(PMAC_FTR_GET_MB_INFO, शून्य, PMAC_MB_INFO_NAME,
			      (दीर्घ) &mbname) != 0)
		mbname = "Unknown";

	/* find motherboard type */
	seq_म_लिखो(m, "machine\t\t: ");
	np = of_find_node_by_path("/");
	अगर (np != शून्य) अणु
		pp = of_get_property(np, "model", शून्य);
		अगर (pp != शून्य)
			seq_म_लिखो(m, "%s\n", pp);
		अन्यथा
			seq_म_लिखो(m, "PowerMac\n");
		pp = of_get_property(np, "compatible", &plen);
		अगर (pp != शून्य) अणु
			seq_म_लिखो(m, "motherboard\t:");
			जबतक (plen > 0) अणु
				पूर्णांक l = म_माप(pp) + 1;
				seq_म_लिखो(m, " %s", pp);
				plen -= l;
				pp += l;
			पूर्ण
			seq_म_लिखो(m, "\n");
		पूर्ण
		of_node_put(np);
	पूर्ण अन्यथा
		seq_म_लिखो(m, "PowerMac\n");

	/* prपूर्णांक parsed model */
	seq_म_लिखो(m, "detected as\t: %d (%s)\n", mbmodel, mbname);
	seq_म_लिखो(m, "pmac flags\t: %08x\n", mbflags);

	/* find l2 cache info */
	np = of_find_node_by_name(शून्य, "l2-cache");
	अगर (np == शून्य)
		np = of_find_node_by_type(शून्य, "cache");
	अगर (np != शून्य) अणु
		स्थिर अचिन्हित पूर्णांक *ic =
			of_get_property(np, "i-cache-size", शून्य);
		स्थिर अचिन्हित पूर्णांक *dc =
			of_get_property(np, "d-cache-size", शून्य);
		seq_म_लिखो(m, "L2 cache\t:");
		has_l2cache = 1;
		अगर (of_get_property(np, "cache-unified", शून्य) && dc) अणु
			seq_म_लिखो(m, " %dK unified", *dc / 1024);
		पूर्ण अन्यथा अणु
			अगर (ic)
				seq_म_लिखो(m, " %dK instruction", *ic / 1024);
			अगर (dc)
				seq_म_लिखो(m, "%s %dK data",
					   (ic? " +": ""), *dc / 1024);
		पूर्ण
		pp = of_get_property(np, "ram-type", शून्य);
		अगर (pp)
			seq_म_लिखो(m, " %s", pp);
		seq_म_लिखो(m, "\n");
		of_node_put(np);
	पूर्ण

	/* Indicate newworld/oldworld */
	seq_म_लिखो(m, "pmac-generation\t: %s\n",
		   pmac_newworld ? "NewWorld" : "OldWorld");
पूर्ण

#अगर_अघोषित CONFIG_ADB_CUDA
पूर्णांक find_via_cuda(व्योम)
अणु
	काष्ठा device_node *dn = of_find_node_by_name(शून्य, "via-cuda");

	अगर (!dn)
		वापस 0;
	of_node_put(dn);
	prपूर्णांकk("WARNING ! Your machine is CUDA-based but your kernel\n");
	prपूर्णांकk("          wasn't compiled with CONFIG_ADB_CUDA option !\n");
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित CONFIG_ADB_PMU
पूर्णांक find_via_pmu(व्योम)
अणु
	काष्ठा device_node *dn = of_find_node_by_name(शून्य, "via-pmu");

	अगर (!dn)
		वापस 0;
	of_node_put(dn);
	prपूर्णांकk("WARNING ! Your machine is PMU-based but your kernel\n");
	prपूर्णांकk("          wasn't compiled with CONFIG_ADB_PMU option !\n");
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित CONFIG_PMAC_SMU
पूर्णांक smu_init(व्योम)
अणु
	/* should check and warn अगर SMU is present */
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC32
अटल अस्थिर u32 *sysctrl_regs;

अटल व्योम __init ohare_init(व्योम)
अणु
	काष्ठा device_node *dn;

	/* this area has the CPU identअगरication रेजिस्टर
	   and some रेजिस्टरs used by smp boards */
	sysctrl_regs = (अस्थिर u32 *) ioremap(0xf8000000, 0x1000);

	/*
	 * Turn on the L2 cache.
	 * We assume that we have a PSX memory controller अगरf
	 * we have an ohare I/O controller.
	 */
	dn = of_find_node_by_name(शून्य, "ohare");
	अगर (dn) अणु
		of_node_put(dn);
		अगर (((sysctrl_regs[2] >> 24) & 0xf) >= 3) अणु
			अगर (sysctrl_regs[4] & 0x10)
				sysctrl_regs[4] |= 0x04000020;
			अन्यथा
				sysctrl_regs[4] |= 0x04000000;
			अगर(has_l2cache)
				prपूर्णांकk(KERN_INFO "Level 2 cache enabled\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __init l2cr_init(व्योम)
अणु
	/* Checks "l2cr-value" property in the registry */
	अगर (cpu_has_feature(CPU_FTR_L2CR)) अणु
		काष्ठा device_node *np;

		क्रम_each_of_cpu_node(np) अणु
			स्थिर अचिन्हित पूर्णांक *l2cr =
				of_get_property(np, "l2cr-value", शून्य);
			अगर (l2cr) अणु
				ppc_override_l2cr = 1;
				ppc_override_l2cr_value = *l2cr;
				_set_L2CR(0);
				_set_L2CR(ppc_override_l2cr_value);
			पूर्ण
			of_node_put(np);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ppc_override_l2cr)
		prपूर्णांकk(KERN_INFO "L2CR overridden (0x%x), "
		       "backside cache is %s\n",
		       ppc_override_l2cr_value,
		       (ppc_override_l2cr_value & 0x80000000)
				? "enabled" : "disabled");
पूर्ण
#पूर्ण_अगर

अटल व्योम __init pmac_setup_arch(व्योम)
अणु
	काष्ठा device_node *cpu, *ic;
	स्थिर पूर्णांक *fp;
	अचिन्हित दीर्घ pvr;

	pvr = PVR_VER(mfspr(SPRN_PVR));

	/* Set loops_per_jअगरfy to a half-way reasonable value,
	   क्रम use until calibrate_delay माला_लो called. */
	loops_per_jअगरfy = 50000000 / HZ;

	क्रम_each_of_cpu_node(cpu) अणु
		fp = of_get_property(cpu, "clock-frequency", शून्य);
		अगर (fp != शून्य) अणु
			अगर (pvr >= 0x30 && pvr < 0x80)
				/* PPC970 etc. */
				loops_per_jअगरfy = *fp / (3 * HZ);
			अन्यथा अगर (pvr == 4 || pvr >= 8)
				/* 604, G3, G4 etc. */
				loops_per_jअगरfy = *fp / HZ;
			अन्यथा
				/* 603, etc. */
				loops_per_jअगरfy = *fp / (2 * HZ);
			of_node_put(cpu);
			अवरोध;
		पूर्ण
	पूर्ण

	/* See अगर newworld or oldworld */
	ic = of_find_node_with_property(शून्य, "interrupt-controller");
	अगर (ic) अणु
		pmac_newworld = 1;
		of_node_put(ic);
	पूर्ण

#अगर_घोषित CONFIG_PPC32
	ohare_init();
	l2cr_init();
#पूर्ण_अगर /* CONFIG_PPC32 */

	find_via_cuda();
	find_via_pmu();
	smu_init();

#अगर IS_ENABLED(CONFIG_NVRAM)
	pmac_nvram_init();
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC32
#अगर_घोषित CONFIG_BLK_DEV_INITRD
	अगर (initrd_start)
		ROOT_DEV = Root_RAM0;
	अन्यथा
#पूर्ण_अगर
		ROOT_DEV = DEFAULT_ROOT_DEVICE;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ADB
	अगर (म_माला(boot_command_line, "adb_sync")) अणु
		बाह्य पूर्णांक __adb_probe_sync;
		__adb_probe_sync = 1;
	पूर्ण
#पूर्ण_अगर /* CONFIG_ADB */
पूर्ण

#अगर_घोषित CONFIG_SCSI
व्योम note_scsi_host(काष्ठा device_node *node, व्योम *host)
अणु
पूर्ण
EXPORT_SYMBOL(note_scsi_host);
#पूर्ण_अगर

अटल पूर्णांक initializing = 1;

अटल पूर्णांक pmac_late_init(व्योम)
अणु
	initializing = 0;
	वापस 0;
पूर्ण
machine_late_initcall(घातermac, pmac_late_init);

व्योम note_bootable_part(dev_t dev, पूर्णांक part, पूर्णांक goodness);
/*
 * This is __ref because we check क्रम "initializing" beक्रमe
 * touching any of the __init sensitive things and "initializing"
 * will be false after __init समय. This can't be __init because it
 * can be called whenever a disk is first accessed.
 */
व्योम __ref note_bootable_part(dev_t dev, पूर्णांक part, पूर्णांक goodness)
अणु
	अक्षर *p;

	अगर (!initializing)
		वापस;
	अगर ((goodness <= current_root_goodness) &&
	    ROOT_DEV != DEFAULT_ROOT_DEVICE)
		वापस;
	p = म_माला(boot_command_line, "root=");
	अगर (p != शून्य && (p == boot_command_line || p[-1] == ' '))
		वापस;

	ROOT_DEV = dev + part;
	current_root_goodness = goodness;
पूर्ण

#अगर_घोषित CONFIG_ADB_CUDA
अटल व्योम __noवापस cuda_restart(व्योम)
अणु
	काष्ठा adb_request req;

	cuda_request(&req, शून्य, 2, CUDA_PACKET, CUDA_RESET_SYSTEM);
	क्रम (;;)
		cuda_poll();
पूर्ण

अटल व्योम __noवापस cuda_shutकरोwn(व्योम)
अणु
	काष्ठा adb_request req;

	cuda_request(&req, शून्य, 2, CUDA_PACKET, CUDA_POWERDOWN);
	क्रम (;;)
		cuda_poll();
पूर्ण

#अन्यथा
#घोषणा cuda_restart()
#घोषणा cuda_shutकरोwn()
#पूर्ण_अगर

#अगर_अघोषित CONFIG_ADB_PMU
#घोषणा pmu_restart()
#घोषणा pmu_shutकरोwn()
#पूर्ण_अगर

#अगर_अघोषित CONFIG_PMAC_SMU
#घोषणा smu_restart()
#घोषणा smu_shutकरोwn()
#पूर्ण_अगर

अटल व्योम __noवापस pmac_restart(अक्षर *cmd)
अणु
	चयन (sys_ctrler) अणु
	हाल SYS_CTRLER_CUDA:
		cuda_restart();
		अवरोध;
	हाल SYS_CTRLER_PMU:
		pmu_restart();
		अवरोध;
	हाल SYS_CTRLER_SMU:
		smu_restart();
		अवरोध;
	शेष: ;
	पूर्ण
	जबतक (1) ;
पूर्ण

अटल व्योम __noवापस pmac_घातer_off(व्योम)
अणु
	चयन (sys_ctrler) अणु
	हाल SYS_CTRLER_CUDA:
		cuda_shutकरोwn();
		अवरोध;
	हाल SYS_CTRLER_PMU:
		pmu_shutकरोwn();
		अवरोध;
	हाल SYS_CTRLER_SMU:
		smu_shutकरोwn();
		अवरोध;
	शेष: ;
	पूर्ण
	जबतक (1) ;
पूर्ण

अटल व्योम __noवापस
pmac_halt(व्योम)
अणु
	pmac_घातer_off();
पूर्ण

/* 
 * Early initialization.
 */
अटल व्योम __init pmac_init(व्योम)
अणु
	/* Enable early btext debug अगर requested */
	अगर (म_माला(boot_command_line, "btextdbg")) अणु
		udbg_adb_init_early();
		रेजिस्टर_early_udbg_console();
	पूर्ण

	/* Probe motherboard chipset */
	pmac_feature_init();

	/* Initialize debug stuff */
	udbg_scc_init(!!म_माला(boot_command_line, "sccdbg"));
	udbg_adb_init(!!म_माला(boot_command_line, "btextdbg"));

#अगर_घोषित CONFIG_PPC64
	iommu_init_early_dart(&pmac_pci_controller_ops);
#पूर्ण_अगर

	/* SMP Init has to be करोne early as we need to patch up
	 * cpu_possible_mask beक्रमe पूर्णांकerrupt stacks are allocated
	 * or kaboom...
	 */
#अगर_घोषित CONFIG_SMP
	pmac_setup_smp();
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक __init pmac_declare_of_platक्रमm_devices(व्योम)
अणु
	काष्ठा device_node *np;

	np = of_find_node_by_name(शून्य, "valkyrie");
	अगर (np) अणु
		of_platक्रमm_device_create(np, "valkyrie", शून्य);
		of_node_put(np);
	पूर्ण
	np = of_find_node_by_name(शून्य, "platinum");
	अगर (np) अणु
		of_platक्रमm_device_create(np, "platinum", शून्य);
		of_node_put(np);
	पूर्ण
        np = of_find_node_by_type(शून्य, "smu");
        अगर (np) अणु
		of_platक्रमm_device_create(np, "smu", शून्य);
		of_node_put(np);
	पूर्ण
	np = of_find_node_by_type(शून्य, "fcu");
	अगर (np == शून्य) अणु
		/* Some machines have strangely broken device-tree */
		np = of_find_node_by_path("/u3@0,f8000000/i2c@f8001000/fan@15e");
	पूर्ण
	अगर (np) अणु
		of_platक्रमm_device_create(np, "temperature", शून्य);
		of_node_put(np);
	पूर्ण

	वापस 0;
पूर्ण
machine_device_initcall(घातermac, pmac_declare_of_platक्रमm_devices);

#अगर_घोषित CONFIG_SERIAL_PMACZILOG_CONSOLE
/*
 * This is called very early, as part of console_init() (typically just after
 * समय_init()). This function is respondible क्रम trying to find a good
 * शेष console on serial ports. It tries to match the खोलो firmware
 * शेष output with one of the available serial console drivers.
 */
अटल पूर्णांक __init check_pmac_serial_console(व्योम)
अणु
	काष्ठा device_node *prom_मानक_निकास = शून्य;
	पूर्णांक offset = 0;
	स्थिर अक्षर *name;
#अगर_घोषित CONFIG_SERIAL_PMACZILOG_TTYS
	अक्षर *devname = "ttyS";
#अन्यथा
	अक्षर *devname = "ttyPZ";
#पूर्ण_अगर

	pr_debug(" -> check_pmac_serial_console()\n");

	/* The user has requested a console so this is alपढ़ोy set up. */
	अगर (म_माला(boot_command_line, "console=")) अणु
		pr_debug(" console was specified !\n");
		वापस -EBUSY;
	पूर्ण

	अगर (!of_chosen) अणु
		pr_debug(" of_chosen is NULL !\n");
		वापस -ENODEV;
	पूर्ण

	/* We are getting a weird phandle from OF ... */
	/* ... So use the full path instead */
	name = of_get_property(of_chosen, "linux,stdout-path", शून्य);
	अगर (name == शून्य) अणु
		pr_debug(" no linux,stdout-path !\n");
		वापस -ENODEV;
	पूर्ण
	prom_मानक_निकास = of_find_node_by_path(name);
	अगर (!prom_मानक_निकास) अणु
		pr_debug(" can't find stdout package %s !\n", name);
		वापस -ENODEV;
	पूर्ण
	pr_debug("stdout is %pOF\n", prom_मानक_निकास);

	अगर (of_node_name_eq(prom_मानक_निकास, "ch-a"))
		offset = 0;
	अन्यथा अगर (of_node_name_eq(prom_मानक_निकास, "ch-b"))
		offset = 1;
	अन्यथा
		जाओ not_found;
	of_node_put(prom_मानक_निकास);

	pr_debug("Found serial console at %s%d\n", devname, offset);

	वापस add_preferred_console(devname, offset, शून्य);

 not_found:
	pr_debug("No preferred console found !\n");
	of_node_put(prom_मानक_निकास);
	वापस -ENODEV;
पूर्ण
console_initcall(check_pmac_serial_console);

#पूर्ण_अगर /* CONFIG_SERIAL_PMACZILOG_CONSOLE */

/*
 * Called very early, MMU is off, device-tree isn't unflattened
 */
अटल पूर्णांक __init pmac_probe(व्योम)
अणु
	अगर (!of_machine_is_compatible("Power Macintosh") &&
	    !of_machine_is_compatible("MacRISC"))
		वापस 0;

#अगर_घोषित CONFIG_PPC32
	/* isa_io_base माला_लो set in pmac_pci_init */
	DMA_MODE_READ = 1;
	DMA_MODE_WRITE = 2;
#पूर्ण_अगर /* CONFIG_PPC32 */

	pm_घातer_off = pmac_घातer_off;

	pmac_init();

	वापस 1;
पूर्ण

define_machine(घातermac) अणु
	.name			= "PowerMac",
	.probe			= pmac_probe,
	.setup_arch		= pmac_setup_arch,
	.discover_phbs		= pmac_pci_init,
	.show_cpuinfo		= pmac_show_cpuinfo,
	.init_IRQ		= pmac_pic_init,
	.get_irq		= शून्य,	/* changed later */
	.pci_irq_fixup		= pmac_pci_irq_fixup,
	.restart		= pmac_restart,
	.halt			= pmac_halt,
	.समय_init		= pmac_समय_init,
	.get_boot_समय		= pmac_get_boot_समय,
	.set_rtc_समय		= pmac_set_rtc_समय,
	.get_rtc_समय		= pmac_get_rtc_समय,
	.calibrate_decr		= pmac_calibrate_decr,
	.feature_call		= pmac_करो_feature_call,
	.progress		= udbg_progress,
#अगर_घोषित CONFIG_PPC64
	.घातer_save		= घातer4_idle,
	.enable_pmcs		= घातer4_enable_pmcs,
#पूर्ण_अगर /* CONFIG_PPC64 */
#अगर_घोषित CONFIG_PPC32
	.pcibios_after_init	= pmac_pcibios_after_init,
	.phys_mem_access_prot	= pci_phys_mem_access_prot,
#पूर्ण_अगर
पूर्ण;
