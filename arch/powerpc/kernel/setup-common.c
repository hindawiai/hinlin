<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Common boot and setup code क्रम both 32-bit and 64-bit.
 * Extracted from arch/घातerpc/kernel/setup_64.c.
 *
 * Copyright (C) 2001 PPC64 Team, IBM Corp
 */

#अघोषित DEBUG

#समावेश <linux/export.h>
#समावेश <linux/माला.स>
#समावेश <linux/sched.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/reboot.h>
#समावेश <linux/delay.h>
#समावेश <linux/initrd.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/ioport.h>
#समावेश <linux/console.h>
#समावेश <linux/screen_info.h>
#समावेश <linux/root_dev.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/cpu.h>
#समावेश <linux/unistd.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/percpu.h>
#समावेश <linux/memblock.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/debugfs.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/paca.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/vdso_datapage.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/elf.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/btext.h>
#समावेश <यंत्र/nvram.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/serial.h>
#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/xmon.h>
#समावेश <यंत्र/cputhपढ़ोs.h>
#समावेश <mm/mmu_decl.h>
#समावेश <यंत्र/fadump.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/hugetlb.h>
#समावेश <यंत्र/livepatch.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/cpu_has_feature.h>
#समावेश <यंत्र/kasan.h>
#समावेश <यंत्र/mce.h>

#समावेश "setup.h"

#अगर_घोषित DEBUG
#घोषणा DBG(fmt...) udbg_म_लिखो(fmt)
#अन्यथा
#घोषणा DBG(fmt...)
#पूर्ण_अगर

/* The मुख्य machine-dep calls काष्ठाure
 */
काष्ठा machdep_calls ppc_md;
EXPORT_SYMBOL(ppc_md);
काष्ठा machdep_calls *machine_id;
EXPORT_SYMBOL(machine_id);

पूर्णांक boot_cpuid = -1;
EXPORT_SYMBOL_GPL(boot_cpuid);

/*
 * These are used in binfmt_elf.c to put aux entries on the stack
 * क्रम each elf executable being started.
 */
पूर्णांक dcache_bsize;
पूर्णांक icache_bsize;

अचिन्हित दीर्घ klimit = (अचिन्हित दीर्घ) _end;

/*
 * This still seems to be needed... -- paulus
 */ 
काष्ठा screen_info screen_info = अणु
	.orig_x = 0,
	.orig_y = 25,
	.orig_video_cols = 80,
	.orig_video_lines = 25,
	.orig_video_isVGA = 1,
	.orig_video_poपूर्णांकs = 16
पूर्ण;
#अगर defined(CONFIG_FB_VGA16_MODULE)
EXPORT_SYMBOL(screen_info);
#पूर्ण_अगर

/* Variables required to store legacy IO irq routing */
पूर्णांक of_i8042_kbd_irq;
EXPORT_SYMBOL_GPL(of_i8042_kbd_irq);
पूर्णांक of_i8042_aux_irq;
EXPORT_SYMBOL_GPL(of_i8042_aux_irq);

#अगर_घोषित __DO_IRQ_CANON
/* XXX should go अन्यथाwhere eventually */
पूर्णांक ppc_करो_canonicalize_irqs;
EXPORT_SYMBOL(ppc_करो_canonicalize_irqs);
#पूर्ण_अगर

#अगर_घोषित CONFIG_CRASH_CORE
/* This keeps a track of which one is the crashing cpu. */
पूर्णांक crashing_cpu = -1;
#पूर्ण_अगर

/* also used by kexec */
व्योम machine_shutकरोwn(व्योम)
अणु
	/*
	 * अगर fadump is active, cleanup the fadump registration beक्रमe we
	 * shutकरोwn.
	 */
	fadump_cleanup();

	अगर (ppc_md.machine_shutकरोwn)
		ppc_md.machine_shutकरोwn();
पूर्ण

अटल व्योम machine_hang(व्योम)
अणु
	pr_emerg("System Halted, OK to turn off power\n");
	local_irq_disable();
	जबतक (1)
		;
पूर्ण

व्योम machine_restart(अक्षर *cmd)
अणु
	machine_shutकरोwn();
	अगर (ppc_md.restart)
		ppc_md.restart(cmd);

	smp_send_stop();

	करो_kernel_restart(cmd);
	mdelay(1000);

	machine_hang();
पूर्ण

व्योम machine_घातer_off(व्योम)
अणु
	machine_shutकरोwn();
	अगर (pm_घातer_off)
		pm_घातer_off();

	smp_send_stop();
	machine_hang();
पूर्ण
/* Used by the G5 thermal driver */
EXPORT_SYMBOL_GPL(machine_घातer_off);

व्योम (*pm_घातer_off)(व्योम);
EXPORT_SYMBOL_GPL(pm_घातer_off);

व्योम machine_halt(व्योम)
अणु
	machine_shutकरोwn();
	अगर (ppc_md.halt)
		ppc_md.halt();

	smp_send_stop();
	machine_hang();
पूर्ण

#अगर_घोषित CONFIG_SMP
DEFINE_PER_CPU(अचिन्हित पूर्णांक, cpu_pvr);
#पूर्ण_अगर

अटल व्योम show_cpuinfo_summary(काष्ठा seq_file *m)
अणु
	काष्ठा device_node *root;
	स्थिर अक्षर *model = शून्य;
	अचिन्हित दीर्घ bogosum = 0;
	पूर्णांक i;

	अगर (IS_ENABLED(CONFIG_SMP) && IS_ENABLED(CONFIG_PPC32)) अणु
		क्रम_each_online_cpu(i)
			bogosum += loops_per_jअगरfy;
		seq_म_लिखो(m, "total bogomips\t: %lu.%02lu\n",
			   bogosum / (500000 / HZ), bogosum / (5000 / HZ) % 100);
	पूर्ण
	seq_म_लिखो(m, "timebase\t: %lu\n", ppc_tb_freq);
	अगर (ppc_md.name)
		seq_म_लिखो(m, "platform\t: %s\n", ppc_md.name);
	root = of_find_node_by_path("/");
	अगर (root)
		model = of_get_property(root, "model", शून्य);
	अगर (model)
		seq_म_लिखो(m, "model\t\t: %s\n", model);
	of_node_put(root);

	अगर (ppc_md.show_cpuinfo != शून्य)
		ppc_md.show_cpuinfo(m);

	/* Display the amount of memory */
	अगर (IS_ENABLED(CONFIG_PPC32))
		seq_म_लिखो(m, "Memory\t\t: %d MB\n",
			   (अचिन्हित पूर्णांक)(total_memory / (1024 * 1024)));
पूर्ण

अटल पूर्णांक show_cpuinfo(काष्ठा seq_file *m, व्योम *v)
अणु
	अचिन्हित दीर्घ cpu_id = (अचिन्हित दीर्घ)v - 1;
	अचिन्हित पूर्णांक pvr;
	अचिन्हित दीर्घ proc_freq;
	अचिन्हित लघु maj;
	अचिन्हित लघु min;

#अगर_घोषित CONFIG_SMP
	pvr = per_cpu(cpu_pvr, cpu_id);
#अन्यथा
	pvr = mfspr(SPRN_PVR);
#पूर्ण_अगर
	maj = (pvr >> 8) & 0xFF;
	min = pvr & 0xFF;

	seq_म_लिखो(m, "processor\t: %lu\ncpu\t\t: ", cpu_id);

	अगर (cur_cpu_spec->pvr_mask && cur_cpu_spec->cpu_name)
		seq_माला_दो(m, cur_cpu_spec->cpu_name);
	अन्यथा
		seq_म_लिखो(m, "unknown (%08x)", pvr);

	अगर (cpu_has_feature(CPU_FTR_ALTIVEC))
		seq_माला_दो(m, ", altivec supported");

	seq_अ_दो(m, '\n');

#अगर_घोषित CONFIG_TAU
	अगर (cpu_has_feature(CPU_FTR_TAU)) अणु
		अगर (IS_ENABLED(CONFIG_TAU_AVERAGE)) अणु
			/* more straightक्रमward, but potentially misleading */
			seq_म_लिखो(m,  "temperature \t: %u C (uncalibrated)\n",
				   cpu_temp(cpu_id));
		पूर्ण अन्यथा अणु
			/* show the actual temp sensor range */
			u32 temp;
			temp = cpu_temp_both(cpu_id);
			seq_म_लिखो(m, "temperature \t: %u-%u C (uncalibrated)\n",
				   temp & 0xff, temp >> 16);
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_TAU */

	/*
	 * Platक्रमms that have variable घड़ी rates, should implement
	 * the method ppc_md.get_proc_freq() that reports the घड़ी
	 * rate of a given cpu. The rest can use ppc_proc_freq to
	 * report the घड़ी rate that is same across all cpus.
	 */
	अगर (ppc_md.get_proc_freq)
		proc_freq = ppc_md.get_proc_freq(cpu_id);
	अन्यथा
		proc_freq = ppc_proc_freq;

	अगर (proc_freq)
		seq_म_लिखो(m, "clock\t\t: %lu.%06luMHz\n",
			   proc_freq / 1000000, proc_freq % 1000000);

	अगर (ppc_md.show_percpuinfo != शून्य)
		ppc_md.show_percpuinfo(m, cpu_id);

	/* If we are a Freescale core करो a simple check so
	 * we करोnt have to keep adding हालs in the future */
	अगर (PVR_VER(pvr) & 0x8000) अणु
		चयन (PVR_VER(pvr)) अणु
		हाल 0x8000:	/* 7441/7450/7451, Voyager */
		हाल 0x8001:	/* 7445/7455, Apollo 6 */
		हाल 0x8002:	/* 7447/7457, Apollo 7 */
		हाल 0x8003:	/* 7447A, Apollo 7 PM */
		हाल 0x8004:	/* 7448, Apollo 8 */
		हाल 0x800c:	/* 7410, Nitro */
			maj = ((pvr >> 8) & 0xF);
			min = PVR_MIN(pvr);
			अवरोध;
		शेष:	/* e500/book-e */
			maj = PVR_MAJ(pvr);
			min = PVR_MIN(pvr);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (PVR_VER(pvr)) अणु
			हाल 0x1008:	/* 740P/750P ?? */
				maj = ((pvr >> 8) & 0xFF) - 1;
				min = pvr & 0xFF;
				अवरोध;
			हाल 0x004e: /* POWER9 bits 12-15 give chip type */
			हाल 0x0080: /* POWER10 bit 12 gives SMT8/4 */
				maj = (pvr >> 8) & 0x0F;
				min = pvr & 0xFF;
				अवरोध;
			शेष:
				maj = (pvr >> 8) & 0xFF;
				min = pvr & 0xFF;
				अवरोध;
		पूर्ण
	पूर्ण

	seq_म_लिखो(m, "revision\t: %hd.%hd (pvr %04x %04x)\n",
		   maj, min, PVR_VER(pvr), PVR_REV(pvr));

	अगर (IS_ENABLED(CONFIG_PPC32))
		seq_म_लिखो(m, "bogomips\t: %lu.%02lu\n", loops_per_jअगरfy / (500000 / HZ),
			   (loops_per_jअगरfy / (5000 / HZ)) % 100);

	seq_अ_दो(m, '\n');

	/* If this is the last cpu, prपूर्णांक the summary */
	अगर (cpumask_next(cpu_id, cpu_online_mask) >= nr_cpu_ids)
		show_cpuinfo_summary(m);

	वापस 0;
पूर्ण

अटल व्योम *c_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	अगर (*pos == 0)	/* just in हाल, cpu 0 is not the first */
		*pos = cpumask_first(cpu_online_mask);
	अन्यथा
		*pos = cpumask_next(*pos - 1, cpu_online_mask);
	अगर ((*pos) < nr_cpu_ids)
		वापस (व्योम *)(अचिन्हित दीर्घ)(*pos + 1);
	वापस शून्य;
पूर्ण

अटल व्योम *c_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	(*pos)++;
	वापस c_start(m, pos);
पूर्ण

अटल व्योम c_stop(काष्ठा seq_file *m, व्योम *v)
अणु
पूर्ण

स्थिर काष्ठा seq_operations cpuinfo_op = अणु
	.start	= c_start,
	.next	= c_next,
	.stop	= c_stop,
	.show	= show_cpuinfo,
पूर्ण;

व्योम __init check_क्रम_initrd(व्योम)
अणु
#अगर_घोषित CONFIG_BLK_DEV_INITRD
	DBG(" -> check_for_initrd()  initrd_start=0x%lx  initrd_end=0x%lx\n",
	    initrd_start, initrd_end);

	/* If we were passed an initrd, set the ROOT_DEV properly अगर the values
	 * look sensible. If not, clear initrd reference.
	 */
	अगर (is_kernel_addr(initrd_start) && is_kernel_addr(initrd_end) &&
	    initrd_end > initrd_start)
		ROOT_DEV = Root_RAM0;
	अन्यथा
		initrd_start = initrd_end = 0;

	अगर (initrd_start)
		pr_info("Found initrd at 0x%lx:0x%lx\n", initrd_start, initrd_end);

	DBG(" <- check_for_initrd()\n");
#पूर्ण_अगर /* CONFIG_BLK_DEV_INITRD */
पूर्ण

#अगर_घोषित CONFIG_SMP

पूर्णांक thपढ़ोs_per_core, thपढ़ोs_per_subcore, thपढ़ोs_shअगरt __पढ़ो_mostly;
cpumask_t thपढ़ोs_core_mask __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(thपढ़ोs_per_core);
EXPORT_SYMBOL_GPL(thपढ़ोs_per_subcore);
EXPORT_SYMBOL_GPL(thपढ़ोs_shअगरt);
EXPORT_SYMBOL_GPL(thपढ़ोs_core_mask);

अटल व्योम __init cpu_init_thपढ़ो_core_maps(पूर्णांक tpc)
अणु
	पूर्णांक i;

	thपढ़ोs_per_core = tpc;
	thपढ़ोs_per_subcore = tpc;
	cpumask_clear(&thपढ़ोs_core_mask);

	/* This implementation only supports घातer of 2 number of thपढ़ोs
	 * क्रम simplicity and perक्रमmance
	 */
	thपढ़ोs_shअगरt = ilog2(tpc);
	BUG_ON(tpc != (1 << thपढ़ोs_shअगरt));

	क्रम (i = 0; i < tpc; i++)
		cpumask_set_cpu(i, &thपढ़ोs_core_mask);

	prपूर्णांकk(KERN_INFO "CPU maps initialized for %d thread%s per core\n",
	       tpc, tpc > 1 ? "s" : "");
	prपूर्णांकk(KERN_DEBUG " (thread shift is %d)\n", thपढ़ोs_shअगरt);
पूर्ण


u32 *cpu_to_phys_id = शून्य;

/**
 * setup_cpu_maps - initialize the following cpu maps:
 *                  cpu_possible_mask
 *                  cpu_present_mask
 *
 * Having the possible map set up early allows us to restrict allocations
 * of things like irqstacks to nr_cpu_ids rather than NR_CPUS.
 *
 * We करो not initialize the online map here; cpus set their own bits in
 * cpu_online_mask as they come up.
 *
 * This function is valid only क्रम Open Firmware प्रणालीs.  finish_device_tree
 * must be called beक्रमe using this.
 *
 * While we're here, we may as well set the "physical" cpu ids in the paca.
 *
 * NOTE: This must match the parsing करोne in early_init_dt_scan_cpus.
 */
व्योम __init smp_setup_cpu_maps(व्योम)
अणु
	काष्ठा device_node *dn;
	पूर्णांक cpu = 0;
	पूर्णांक nthपढ़ोs = 1;

	DBG("smp_setup_cpu_maps()\n");

	cpu_to_phys_id = memblock_alloc(nr_cpu_ids * माप(u32),
					__alignof__(u32));
	अगर (!cpu_to_phys_id)
		panic("%s: Failed to allocate %zu bytes align=0x%zx\n",
		      __func__, nr_cpu_ids * माप(u32), __alignof__(u32));

	क्रम_each_node_by_type(dn, "cpu") अणु
		स्थिर __be32 *पूर्णांकserv;
		__be32 cpu_be;
		पूर्णांक j, len;

		DBG("  * %pOF...\n", dn);

		पूर्णांकserv = of_get_property(dn, "ibm,ppc-interrupt-server#s",
				&len);
		अगर (पूर्णांकserv) अणु
			DBG("    ibm,ppc-interrupt-server#s -> %d threads\n",
			    nthपढ़ोs);
		पूर्ण अन्यथा अणु
			DBG("    no ibm,ppc-interrupt-server#s -> 1 thread\n");
			पूर्णांकserv = of_get_property(dn, "reg", &len);
			अगर (!पूर्णांकserv) अणु
				cpu_be = cpu_to_be32(cpu);
				/* XXX: what is this? uninitialized?? */
				पूर्णांकserv = &cpu_be;	/* assume logical == phys */
				len = 4;
			पूर्ण
		पूर्ण

		nthपढ़ोs = len / माप(पूर्णांक);

		क्रम (j = 0; j < nthपढ़ोs && cpu < nr_cpu_ids; j++) अणु
			bool avail;

			DBG("    thread %d -> cpu %d (hard id %d)\n",
			    j, cpu, be32_to_cpu(पूर्णांकserv[j]));

			avail = of_device_is_available(dn);
			अगर (!avail)
				avail = !of_property_match_string(dn,
						"enable-method", "spin-table");

			set_cpu_present(cpu, avail);
			set_cpu_possible(cpu, true);
			cpu_to_phys_id[cpu] = be32_to_cpu(पूर्णांकserv[j]);
			cpu++;
		पूर्ण

		अगर (cpu >= nr_cpu_ids) अणु
			of_node_put(dn);
			अवरोध;
		पूर्ण
	पूर्ण

	/* If no SMT supported, nthपढ़ोs is क्रमced to 1 */
	अगर (!cpu_has_feature(CPU_FTR_SMT)) अणु
		DBG("  SMT disabled ! nthreads forced to 1\n");
		nthपढ़ोs = 1;
	पूर्ण

#अगर_घोषित CONFIG_PPC64
	/*
	 * On pSeries LPAR, we need to know how many cpus
	 * could possibly be added to this partition.
	 */
	अगर (firmware_has_feature(FW_FEATURE_LPAR) &&
	    (dn = of_find_node_by_path("/rtas"))) अणु
		पूर्णांक num_addr_cell, num_size_cell, maxcpus;
		स्थिर __be32 *ireg;

		num_addr_cell = of_n_addr_cells(dn);
		num_size_cell = of_n_size_cells(dn);

		ireg = of_get_property(dn, "ibm,lrdr-capacity", शून्य);

		अगर (!ireg)
			जाओ out;

		maxcpus = be32_to_cpup(ireg + num_addr_cell + num_size_cell);

		/* Double maxcpus क्रम processors which have SMT capability */
		अगर (cpu_has_feature(CPU_FTR_SMT))
			maxcpus *= nthपढ़ोs;

		अगर (maxcpus > nr_cpu_ids) अणु
			prपूर्णांकk(KERN_WARNING
			       "Partition configured for %d cpus, "
			       "operating system maximum is %u.\n",
			       maxcpus, nr_cpu_ids);
			maxcpus = nr_cpu_ids;
		पूर्ण अन्यथा
			prपूर्णांकk(KERN_INFO "Partition configured for %d cpus.\n",
			       maxcpus);

		क्रम (cpu = 0; cpu < maxcpus; cpu++)
			set_cpu_possible(cpu, true);
	out:
		of_node_put(dn);
	पूर्ण
	vdso_data->processorCount = num_present_cpus();
#पूर्ण_अगर /* CONFIG_PPC64 */

        /* Initialize CPU <=> thपढ़ो mapping/
	 *
	 * WARNING: We assume that the number of thपढ़ोs is the same क्रम
	 * every CPU in the प्रणाली. If that is not the हाल, then some code
	 * here will have to be reworked
	 */
	cpu_init_thपढ़ो_core_maps(nthपढ़ोs);

	/* Now that possible cpus are set, set nr_cpu_ids क्रम later use */
	setup_nr_cpu_ids();

	मुक्त_unused_pacas();
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

#अगर_घोषित CONFIG_PCSPKR_PLATFORM
अटल __init पूर्णांक add_pcspkr(व्योम)
अणु
	काष्ठा device_node *np;
	काष्ठा platक्रमm_device *pd;
	पूर्णांक ret;

	np = of_find_compatible_node(शून्य, शून्य, "pnpPNP,100");
	of_node_put(np);
	अगर (!np)
		वापस -ENODEV;

	pd = platक्रमm_device_alloc("pcspkr", -1);
	अगर (!pd)
		वापस -ENOMEM;

	ret = platक्रमm_device_add(pd);
	अगर (ret)
		platक्रमm_device_put(pd);

	वापस ret;
पूर्ण
device_initcall(add_pcspkr);
#पूर्ण_अगर	/* CONFIG_PCSPKR_PLATFORM */

व्योम probe_machine(व्योम)
अणु
	बाह्य काष्ठा machdep_calls __machine_desc_start;
	बाह्य काष्ठा machdep_calls __machine_desc_end;
	अचिन्हित पूर्णांक i;

	/*
	 * Iterate all ppc_md काष्ठाures until we find the proper
	 * one क्रम the current machine type
	 */
	DBG("Probing machine type ...\n");

	/*
	 * Check ppc_md is empty, अगर not we have a bug, ie, we setup an
	 * entry beक्रमe probe_machine() which will be overwritten
	 */
	क्रम (i = 0; i < (माप(ppc_md) / माप(व्योम *)); i++) अणु
		अगर (((व्योम **)&ppc_md)[i]) अणु
			prपूर्णांकk(KERN_ERR "Entry %d in ppc_md non empty before"
			       " machine probe !\n", i);
		पूर्ण
	पूर्ण

	क्रम (machine_id = &__machine_desc_start;
	     machine_id < &__machine_desc_end;
	     machine_id++) अणु
		DBG("  %s ...", machine_id->name);
		स_नकल(&ppc_md, machine_id, माप(काष्ठा machdep_calls));
		अगर (ppc_md.probe()) अणु
			DBG(" match !\n");
			अवरोध;
		पूर्ण
		DBG("\n");
	पूर्ण
	/* What can we करो अगर we didn't find ? */
	अगर (machine_id >= &__machine_desc_end) अणु
		pr_err("No suitable machine description found !\n");
		क्रम (;;);
	पूर्ण

	prपूर्णांकk(KERN_INFO "Using %s machine description\n", ppc_md.name);
पूर्ण

/* Match a class of boards, not a specअगरic device configuration. */
पूर्णांक check_legacy_ioport(अचिन्हित दीर्घ base_port)
अणु
	काष्ठा device_node *parent, *np = शून्य;
	पूर्णांक ret = -ENODEV;

	चयन(base_port) अणु
	हाल I8042_DATA_REG:
		अगर (!(np = of_find_compatible_node(शून्य, शून्य, "pnpPNP,303")))
			np = of_find_compatible_node(शून्य, शून्य, "pnpPNP,f03");
		अगर (np) अणु
			parent = of_get_parent(np);

			of_i8042_kbd_irq = irq_of_parse_and_map(parent, 0);
			अगर (!of_i8042_kbd_irq)
				of_i8042_kbd_irq = 1;

			of_i8042_aux_irq = irq_of_parse_and_map(parent, 1);
			अगर (!of_i8042_aux_irq)
				of_i8042_aux_irq = 12;

			of_node_put(np);
			np = parent;
			अवरोध;
		पूर्ण
		np = of_find_node_by_type(शून्य, "8042");
		/* Pegasos has no device_type on its 8042 node, look क्रम the
		 * name instead */
		अगर (!np)
			np = of_find_node_by_name(शून्य, "8042");
		अगर (np) अणु
			of_i8042_kbd_irq = 1;
			of_i8042_aux_irq = 12;
		पूर्ण
		अवरोध;
	हाल FDC_BASE: /* FDC1 */
		np = of_find_node_by_type(शून्य, "fdc");
		अवरोध;
	शेष:
		/* ipmi is supposed to fail here */
		अवरोध;
	पूर्ण
	अगर (!np)
		वापस ret;
	parent = of_get_parent(np);
	अगर (parent) अणु
		अगर (of_node_is_type(parent, "isa"))
			ret = 0;
		of_node_put(parent);
	पूर्ण
	of_node_put(np);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(check_legacy_ioport);

अटल पूर्णांक ppc_panic_event(काष्ठा notअगरier_block *this,
                             अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	/*
	 * panic करोes a local_irq_disable, but we really
	 * want पूर्णांकerrupts to be hard disabled.
	 */
	hard_irq_disable();

	/*
	 * If firmware-assisted dump has been रेजिस्टरed then trigger
	 * firmware-assisted dump and let firmware handle everything अन्यथा.
	 */
	crash_fadump(शून्य, ptr);
	अगर (ppc_md.panic)
		ppc_md.panic(ptr);  /* May not वापस */
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block ppc_panic_block = अणु
	.notअगरier_call = ppc_panic_event,
	.priority = पूर्णांक_न्यून /* may not वापस; must be करोne last */
पूर्ण;

/*
 * Dump out kernel offset inक्रमmation on panic.
 */
अटल पूर्णांक dump_kernel_offset(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ v,
			      व्योम *p)
अणु
	pr_emerg("Kernel Offset: 0x%lx from 0x%lx\n",
		 kaslr_offset(), KERNELBASE);

	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block kernel_offset_notअगरier = अणु
	.notअगरier_call = dump_kernel_offset
पूर्ण;

व्योम __init setup_panic(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_RANDOMIZE_BASE) && kaslr_offset() > 0)
		atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list,
					       &kernel_offset_notअगरier);

	/* PPC64 always करोes a hard irq disable in its panic handler */
	अगर (!IS_ENABLED(CONFIG_PPC64) && !ppc_md.panic)
		वापस;
	atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list, &ppc_panic_block);
पूर्ण

#अगर_घोषित CONFIG_CHECK_CACHE_COHERENCY
/*
 * For platक्रमms that have configurable cache-coherency.  This function
 * checks that the cache coherency setting of the kernel matches the setting
 * left by the firmware, as indicated in the device tree.  Since a mismatch
 * will eventually result in DMA failures, we prपूर्णांक * and error and call
 * BUG() in that हाल.
 */

#घोषणा KERNEL_COHERENCY	(!IS_ENABLED(CONFIG_NOT_COHERENT_CACHE))

अटल पूर्णांक __init check_cache_coherency(व्योम)
अणु
	काष्ठा device_node *np;
	स्थिर व्योम *prop;
	bool devtree_coherency;

	np = of_find_node_by_path("/");
	prop = of_get_property(np, "coherency-off", शून्य);
	of_node_put(np);

	devtree_coherency = prop ? false : true;

	अगर (devtree_coherency != KERNEL_COHERENCY) अणु
		prपूर्णांकk(KERN_ERR
			"kernel coherency:%s != device tree_coherency:%s\n",
			KERNEL_COHERENCY ? "on" : "off",
			devtree_coherency ? "on" : "off");
		BUG();
	पूर्ण

	वापस 0;
पूर्ण

late_initcall(check_cache_coherency);
#पूर्ण_अगर /* CONFIG_CHECK_CACHE_COHERENCY */

#अगर_घोषित CONFIG_DEBUG_FS
काष्ठा dentry *घातerpc_debugfs_root;
EXPORT_SYMBOL(घातerpc_debugfs_root);

अटल पूर्णांक घातerpc_debugfs_init(व्योम)
अणु
	घातerpc_debugfs_root = debugfs_create_dir("powerpc", शून्य);
	वापस 0;
पूर्ण
arch_initcall(घातerpc_debugfs_init);
#पूर्ण_अगर

व्योम ppc_prपूर्णांकk_progress(अक्षर *s, अचिन्हित लघु hex)
अणु
	pr_info("%s\n", s);
पूर्ण

अटल __init व्योम prपूर्णांक_प्रणाली_info(व्योम)
अणु
	pr_info("-----------------------------------------------------\n");
	pr_info("phys_mem_size     = 0x%llx\n",
		(अचिन्हित दीर्घ दीर्घ)memblock_phys_mem_size());

	pr_info("dcache_bsize      = 0x%x\n", dcache_bsize);
	pr_info("icache_bsize      = 0x%x\n", icache_bsize);

	pr_info("cpu_features      = 0x%016lx\n", cur_cpu_spec->cpu_features);
	pr_info("  possible        = 0x%016lx\n",
		(अचिन्हित दीर्घ)CPU_FTRS_POSSIBLE);
	pr_info("  always          = 0x%016lx\n",
		(अचिन्हित दीर्घ)CPU_FTRS_ALWAYS);
	pr_info("cpu_user_features = 0x%08x 0x%08x\n",
		cur_cpu_spec->cpu_user_features,
		cur_cpu_spec->cpu_user_features2);
	pr_info("mmu_features      = 0x%08x\n", cur_cpu_spec->mmu_features);
#अगर_घोषित CONFIG_PPC64
	pr_info("firmware_features = 0x%016lx\n", घातerpc_firmware_features);
#अगर_घोषित CONFIG_PPC_BOOK3S
	pr_info("vmalloc start     = 0x%lx\n", KERN_VIRT_START);
	pr_info("IO start          = 0x%lx\n", KERN_IO_START);
	pr_info("vmemmap start     = 0x%lx\n", (अचिन्हित दीर्घ)vmemmap);
#पूर्ण_अगर
#पूर्ण_अगर

	अगर (!early_radix_enabled())
		prपूर्णांक_प्रणाली_hash_info();

	अगर (PHYSICAL_START > 0)
		pr_info("physical_start    = 0x%llx\n",
		       (अचिन्हित दीर्घ दीर्घ)PHYSICAL_START);
	pr_info("-----------------------------------------------------\n");
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल व्योम __init smp_setup_pacas(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		अगर (cpu == smp_processor_id())
			जारी;
		allocate_paca(cpu);
		set_hard_smp_processor_id(cpu, cpu_to_phys_id[cpu]);
	पूर्ण

	memblock_मुक्त(__pa(cpu_to_phys_id), nr_cpu_ids * माप(u32));
	cpu_to_phys_id = शून्य;
पूर्ण
#पूर्ण_अगर

/*
 * Called पूर्णांकo from start_kernel this initializes memblock, which is used
 * to manage page allocation until mem_init is called.
 */
व्योम __init setup_arch(अक्षर **cmdline_p)
अणु
	kasan_init();

	*cmdline_p = boot_command_line;

	/* Set a half-reasonable शेष so udelay करोes something sensible */
	loops_per_jअगरfy = 500000000 / HZ;

	/* Unflatten the device-tree passed by prom_init or kexec */
	unflatten_device_tree();

	/*
	 * Initialize cache line/block info from device-tree (on ppc64) or
	 * just cputable (on ppc32).
	 */
	initialize_cache_info();

	/* Initialize RTAS अगर available. */
	rtas_initialize();

	/* Check अगर we have an initrd provided via the device-tree. */
	check_क्रम_initrd();

	/* Probe the machine type, establish ppc_md. */
	probe_machine();

	/* Setup panic notअगरier अगर requested by the platक्रमm. */
	setup_panic();

	/*
	 * Configure ppc_md.घातer_save (ppc32 only, 64-bit machines करो
	 * it from their respective probe() function.
	 */
	setup_घातer_save();

	/* Discover standard serial ports. */
	find_legacy_serial_ports();

	/* Register early console with the prपूर्णांकk subप्रणाली. */
	रेजिस्टर_early_udbg_console();

	/* Setup the various CPU maps based on the device-tree. */
	smp_setup_cpu_maps();

	/* Initialize xmon. */
	xmon_setup();

	/* Check the SMT related command line arguments (ppc64). */
	check_smt_enabled();

	/* Parse memory topology */
	mem_topology_setup();

	/*
	 * Release secondary cpus out of their spinloops at 0x60 now that
	 * we can map physical -> logical CPU ids.
	 *
	 * Freescale Book3e parts spin in a loop provided by firmware,
	 * so smp_release_cpus() करोes nothing क्रम them.
	 */
#अगर_घोषित CONFIG_SMP
	smp_setup_pacas();

	/* On BookE, setup per-core TLB data काष्ठाures. */
	setup_tlb_core_data();
#पूर्ण_अगर

	/* Prपूर्णांक various info about the machine that has been gathered so far. */
	prपूर्णांक_प्रणाली_info();

	/* Reserve large chunks of memory क्रम use by CMA क्रम KVM. */
	kvm_cma_reserve();

	/*  Reserve large chunks of memory क्रम us by CMA क्रम hugetlb */
	gigantic_hugetlb_cma_reserve();

	klp_init_thपढ़ो_info(&init_task);

	init_mm.start_code = (अचिन्हित दीर्घ)_stext;
	init_mm.end_code = (अचिन्हित दीर्घ) _etext;
	init_mm.end_data = (अचिन्हित दीर्घ) _edata;
	init_mm.brk = klimit;

	mm_iommu_init(&init_mm);
	irqstack_early_init();
	exc_lvl_early_init();
	emergency_stack_init();

	mce_init();
	smp_release_cpus();

	iniपंचांगem_init();

	early_memtest(min_low_pfn << PAGE_SHIFT, max_low_pfn << PAGE_SHIFT);

	अगर (ppc_md.setup_arch)
		ppc_md.setup_arch();

	setup_barrier_nospec();
	setup_spectre_v2();

	paging_init();

	/* Initialize the MMU context management stuff. */
	mmu_context_init();

	/* Interrupt code needs to be 64K-aligned. */
	अगर (IS_ENABLED(CONFIG_PPC64) && (अचिन्हित दीर्घ)_stext & 0xffff)
		panic("Kernelbase not 64K-aligned (0x%lx)!\n",
		      (अचिन्हित दीर्घ)_stext);
पूर्ण
