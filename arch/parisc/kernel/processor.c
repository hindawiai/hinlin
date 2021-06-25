<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *    Initial setup-routines क्रम HP 9000 based hardware.
 *
 *    Copyright (C) 1991, 1992, 1995  Linus Torvalds
 *    Modअगरications क्रम PA-RISC (C) 1999-2008 Helge Deller <deller@gmx.de>
 *    Modअगरications copyright 1999 SuSE GmbH (Philipp Rumpf)
 *    Modअगरications copyright 2000 Martin K. Petersen <mkp@mkp.net>
 *    Modअगरications copyright 2000 Philipp Rumpf <prumpf@tux.org>
 *    Modअगरications copyright 2001 Ryan Bradetich <rbradetich@uswest.net>
 *
 *    Initial PA-RISC Version: 04-23-1999 by Helge Deller
 */
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>
#समावेश <linux/cpu.h>
#समावेश <यंत्र/param.h>
#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/hardware.h>	/* क्रम रेजिस्टर_parisc_driver() stuff */
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/pdc.h>
#समावेश <यंत्र/pdcpat.h>
#समावेश <यंत्र/irq.h>		/* क्रम काष्ठा irq_region */
#समावेश <यंत्र/parisc-device.h>

काष्ठा प्रणाली_cpuinfo_parisc boot_cpu_data __ro_after_init;
EXPORT_SYMBOL(boot_cpu_data);
#अगर_घोषित CONFIG_PA8X00
पूर्णांक _parisc_requires_coherency __ro_after_init;
EXPORT_SYMBOL(_parisc_requires_coherency);
#पूर्ण_अगर

DEFINE_PER_CPU(काष्ठा cpuinfo_parisc, cpu_data);

/*
**  	PARISC CPU driver - claim "device" and initialize CPU data काष्ठाures.
**
** Consolidate per CPU initialization पूर्णांकo (mostly) one module.
** Monarch CPU will initialize boot_cpu_data which shouldn't
** change once the प्रणाली has booted.
**
** The callback *should* करो per-instance initialization of
** everything including the monarch. "Per CPU" init code in
** setup.c:start_parisc() has migrated here and start_parisc()
** will call रेजिस्टर_parisc_driver(&cpu_driver) beक्रमe calling करो_inventory().
**
** The goal of consolidating CPU initialization पूर्णांकo one place is
** to make sure all CPUs get initialized the same way.
** The code path not shared is how PDC hands control of the CPU to the OS.
** The initialization of OS data काष्ठाures is the same (करोne below).
*/

/**
 * init_cpu_profiler - enable/setup per cpu profiling hooks.
 * @cpunum: The processor instance.
 *
 * FIXME: करोesn't करो much yet...
 */
अटल व्योम
init_percpu_prof(अचिन्हित दीर्घ cpunum)
अणु
पूर्ण


/**
 * processor_probe - Determine अगर processor driver should claim this device.
 * @dev: The device which has been found.
 *
 * Determine अगर processor driver should claim this chip (वापस 0) or not 
 * (वापस 1).  If so, initialize the chip and tell other partners in crime 
 * they have work to करो.
 */
अटल पूर्णांक __init processor_probe(काष्ठा parisc_device *dev)
अणु
	अचिन्हित दीर्घ txn_addr;
	अचिन्हित दीर्घ cpuid;
	काष्ठा cpuinfo_parisc *p;
	काष्ठा pdc_pat_cpu_num cpu_info = अणु पूर्ण;

#अगर_घोषित CONFIG_SMP
	अगर (num_online_cpus() >= nr_cpu_ids) अणु
		prपूर्णांकk(KERN_INFO "num_online_cpus() >= nr_cpu_ids\n");
		वापस 1;
	पूर्ण
#अन्यथा
	अगर (boot_cpu_data.cpu_count > 0) अणु
		prपूर्णांकk(KERN_INFO "CONFIG_SMP=n  ignoring additional CPUs\n");
		वापस 1;
	पूर्ण
#पूर्ण_अगर

	/* logical CPU ID and update global counter
	 * May get overwritten by PAT code.
	 */
	cpuid = boot_cpu_data.cpu_count;
	txn_addr = dev->hpa.start;	/* क्रम legacy PDC */
	cpu_info.cpu_num = cpu_info.cpu_loc = cpuid;

#अगर_घोषित CONFIG_64BIT
	अगर (is_pdc_pat()) अणु
		uदीर्घ status;
		अचिन्हित दीर्घ bytecnt;
	        pdc_pat_cell_mod_maddr_block_t *pa_pdc_cell;

		pa_pdc_cell = kदो_स्मृति(माप (*pa_pdc_cell), GFP_KERNEL);
		अगर (!pa_pdc_cell)
			panic("couldn't allocate memory for PDC_PAT_CELL!");

		status = pdc_pat_cell_module(&bytecnt, dev->pcell_loc,
			dev->mod_index, PA_VIEW, pa_pdc_cell);

		BUG_ON(PDC_OK != status);

		/* verअगरy it's the same as what करो_pat_inventory() found */
		BUG_ON(dev->mod_info != pa_pdc_cell->mod_info);
		BUG_ON(dev->pmod_loc != pa_pdc_cell->mod_location);

		txn_addr = pa_pdc_cell->mod[0];   /* id_eid क्रम IO sapic */

		kमुक्त(pa_pdc_cell);

		/* get the cpu number */
		status = pdc_pat_cpu_get_number(&cpu_info, dev->hpa.start);
		BUG_ON(PDC_OK != status);

		pr_info("Logical CPU #%lu is physical cpu #%lu at location "
			"0x%lx with hpa %pa\n",
			cpuid, cpu_info.cpu_num, cpu_info.cpu_loc,
			&dev->hpa.start);

#अघोषित USE_PAT_CPUID
#अगर_घोषित USE_PAT_CPUID
/* We need contiguous numbers क्रम cpuid. Firmware's notion
 * of cpuid is क्रम physical CPUs and we just करोn't care yet.
 * We'll care when we need to query PAT PDC about a CPU *after*
 * boot समय (ie shutकरोwn a CPU from an OS perspective).
 */
		अगर (cpu_info.cpu_num >= NR_CPUS) अणु
			prपूर्णांकk(KERN_WARNING "IGNORING CPU at %pa,"
				" cpu_slot_id > NR_CPUS"
				" (%ld > %d)\n",
				&dev->hpa.start, cpu_info.cpu_num, NR_CPUS);
			/* Ignore CPU since it will only crash */
			boot_cpu_data.cpu_count--;
			वापस 1;
		पूर्ण अन्यथा अणु
			cpuid = cpu_info.cpu_num;
		पूर्ण
#पूर्ण_अगर
	पूर्ण
#पूर्ण_अगर

	p = &per_cpu(cpu_data, cpuid);
	boot_cpu_data.cpu_count++;

	/* initialize counters - CPU 0 माला_लो it_value set in समय_init() */
	अगर (cpuid)
		स_रखो(p, 0, माप(काष्ठा cpuinfo_parisc));

	p->dev = dev;		/* Save IODC data in हाल we need it */
	p->hpa = dev->hpa.start;	/* save CPU hpa */
	p->cpuid = cpuid;	/* save CPU id */
	p->txn_addr = txn_addr;	/* save CPU IRQ address */
	p->cpu_num = cpu_info.cpu_num;
	p->cpu_loc = cpu_info.cpu_loc;

	store_cpu_topology(cpuid);

#अगर_घोषित CONFIG_SMP
	/*
	** FIXME: review अगर any other initialization is clobbered
	**	  क्रम boot_cpu by the above स_रखो().
	*/
	init_percpu_prof(cpuid);
#पूर्ण_अगर

	/*
	** CONFIG_SMP: init_smp_config() will attempt to get CPUs पूर्णांकo
	** OS control. RENDEZVOUS is the शेष state - see mem_set above.
	**	p->state = STATE_RENDEZVOUS;
	*/

#अगर 0
	/* CPU 0 IRQ table is अटलally allocated/initialized */
	अगर (cpuid) अणु
		काष्ठा irqaction actions[];

		/*
		** iसमयr and ipi IRQ handlers are अटलally initialized in
		** arch/parisc/kernel/irq.c. ie Don't need to रेजिस्टर them.
		*/
		actions = kदो_स्मृति(माप(काष्ठा irqaction)*MAX_CPU_IRQ, GFP_ATOMIC);
		अगर (!actions) अणु
			/* not getting it's own table, share with monarch */
			actions = cpu_irq_actions[0];
		पूर्ण

		cpu_irq_actions[cpuid] = actions;
	पूर्ण
#पूर्ण_अगर

	/* 
	 * Bring this CPU up now! (ignore bootstrap cpuid == 0)
	 */
#अगर_घोषित CONFIG_SMP
	अगर (cpuid) अणु
		set_cpu_present(cpuid, true);
		add_cpu(cpuid);
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

/**
 * collect_boot_cpu_data - Fill the boot_cpu_data काष्ठाure.
 *
 * This function collects and stores the generic processor inक्रमmation
 * in the boot_cpu_data काष्ठाure.
 */
व्योम __init collect_boot_cpu_data(व्योम)
अणु
	अचिन्हित दीर्घ cr16_seed;
	अक्षर orig_prod_num[64], current_prod_num[64], serial_no[64];

	स_रखो(&boot_cpu_data, 0, माप(boot_cpu_data));

	cr16_seed = get_cycles();
	add_device_अक्रमomness(&cr16_seed, माप(cr16_seed));

	boot_cpu_data.cpu_hz = 100 * PAGE0->mem_10msec; /* Hz of this PARISC */

	/* get CPU-Model Inक्रमmation... */
#घोषणा p ((अचिन्हित दीर्घ *)&boot_cpu_data.pdc.model)
	अगर (pdc_model_info(&boot_cpu_data.pdc.model) == PDC_OK) अणु
		prपूर्णांकk(KERN_INFO 
			"model %08lx %08lx %08lx %08lx %08lx %08lx %08lx %08lx %08lx\n",
			p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);

		add_device_अक्रमomness(&boot_cpu_data.pdc.model,
			माप(boot_cpu_data.pdc.model));
	पूर्ण
#अघोषित p

	अगर (pdc_model_versions(&boot_cpu_data.pdc.versions, 0) == PDC_OK) अणु
		prपूर्णांकk(KERN_INFO "vers  %08lx\n", 
			boot_cpu_data.pdc.versions);

		add_device_अक्रमomness(&boot_cpu_data.pdc.versions,
			माप(boot_cpu_data.pdc.versions));
	पूर्ण

	अगर (pdc_model_cpuid(&boot_cpu_data.pdc.cpuid) == PDC_OK) अणु
		prपूर्णांकk(KERN_INFO "CPUID vers %ld rev %ld (0x%08lx)\n",
			(boot_cpu_data.pdc.cpuid >> 5) & 127,
			boot_cpu_data.pdc.cpuid & 31,
			boot_cpu_data.pdc.cpuid);

		add_device_अक्रमomness(&boot_cpu_data.pdc.cpuid,
			माप(boot_cpu_data.pdc.cpuid));
	पूर्ण

	अगर (pdc_model_capabilities(&boot_cpu_data.pdc.capabilities) == PDC_OK)
		prपूर्णांकk(KERN_INFO "capabilities 0x%lx\n",
			boot_cpu_data.pdc.capabilities);

	अगर (pdc_model_sysmodel(boot_cpu_data.pdc.sys_model_name) == PDC_OK)
		prपूर्णांकk(KERN_INFO "model %s\n",
			boot_cpu_data.pdc.sys_model_name);

	dump_stack_set_arch_desc("%s", boot_cpu_data.pdc.sys_model_name);

	boot_cpu_data.hversion =  boot_cpu_data.pdc.model.hversion;
	boot_cpu_data.sversion =  boot_cpu_data.pdc.model.sversion;

	boot_cpu_data.cpu_type = parisc_get_cpu_type(boot_cpu_data.hversion);
	boot_cpu_data.cpu_name = cpu_name_version[boot_cpu_data.cpu_type][0];
	boot_cpu_data.family_name = cpu_name_version[boot_cpu_data.cpu_type][1];

#अगर_घोषित CONFIG_PA8X00
	_parisc_requires_coherency = (boot_cpu_data.cpu_type == mako) ||
				(boot_cpu_data.cpu_type == mako2);
#पूर्ण_अगर

	अगर (pdc_model_platक्रमm_info(orig_prod_num, current_prod_num, serial_no) == PDC_OK) अणु
		prपूर्णांकk(KERN_INFO "product %s, original product %s, S/N: %s\n",
			current_prod_num[0] ? current_prod_num : "n/a",
			orig_prod_num, serial_no);
		add_device_अक्रमomness(orig_prod_num, म_माप(orig_prod_num));
		add_device_अक्रमomness(current_prod_num, म_माप(current_prod_num));
		add_device_अक्रमomness(serial_no, म_माप(serial_no));
	पूर्ण
पूर्ण


/**
 * init_per_cpu - Handle inभागidual processor initializations.
 * @cpunum: logical processor number.
 *
 * This function handles initialization क्रम *every* CPU
 * in the प्रणाली:
 *
 * o Set "default" CPU width क्रम trap handlers
 *
 * o Enable FP coprocessor
 *   REVISIT: this could be करोne in the "code 22" trap handler.
 *	(frowands idea - that way we know which processes need FP
 *	रेजिस्टरs saved on the पूर्णांकerrupt stack.)
 *   NEWS FLASH: wide kernels need FP coprocessor enabled to handle
 *	क्रमmatted prपूर्णांकing of %lx क्रम example (द्विगुन भागides I think)
 *
 * o Enable CPU profiling hooks.
 */
पूर्णांक __init init_per_cpu(पूर्णांक cpunum)
अणु
	पूर्णांक ret;
	काष्ठा pdc_coproc_cfg coproc_cfg;

	set_firmware_width();
	ret = pdc_coproc_cfg(&coproc_cfg);

	store_cpu_topology(cpunum);

	अगर(ret >= 0 && coproc_cfg.ccr_functional) अणु
		mtctl(coproc_cfg.ccr_functional, 10);  /* 10 == Coprocessor Control Reg */

		/* FWIW, FP rev/model is a more accurate way to determine
		** CPU type. CPU rev/model has some ambiguous हालs.
		*/
		per_cpu(cpu_data, cpunum).fp_rev = coproc_cfg.revision;
		per_cpu(cpu_data, cpunum).fp_model = coproc_cfg.model;

		अगर (cpunum == 0)
			prपूर्णांकk(KERN_INFO  "FP[%d] enabled: Rev %ld Model %ld\n",
				cpunum, coproc_cfg.revision, coproc_cfg.model);

		/*
		** store status रेजिस्टर to stack (hopefully aligned)
		** and clear the T-bit.
		*/
		यंत्र अस्थिर ("fstd    %fr0,8(%sp)");

	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_WARNING  "WARNING: No FP CoProcessor?!"
			" (coproc_cfg.ccr_functional == 0x%lx, expected 0xc0)\n"
#अगर_घोषित CONFIG_64BIT
			"Halting Machine - FP required\n"
#पूर्ण_अगर
			, coproc_cfg.ccr_functional);
#अगर_घोषित CONFIG_64BIT
		mdelay(100);	/* previous अक्षरs get pushed to console */
		panic("FP CoProc not reported");
#पूर्ण_अगर
	पूर्ण

	/* FUTURE: Enable Perक्रमmance Monitor : ccr bit 0x20 */
	init_percpu_prof(cpunum);

	वापस ret;
पूर्ण

/*
 * Display CPU info क्रम all CPUs.
 */
पूर्णांक
show_cpuinfo (काष्ठा seq_file *m, व्योम *v)
अणु
	अचिन्हित दीर्घ cpu;

	क्रम_each_online_cpu(cpu) अणु
		स्थिर काष्ठा cpuinfo_parisc *cpuinfo = &per_cpu(cpu_data, cpu);
#अगर_घोषित CONFIG_SMP
		अगर (0 == cpuinfo->hpa)
			जारी;
#पूर्ण_अगर
		seq_म_लिखो(m, "processor\t: %lu\n"
				"cpu family\t: PA-RISC %s\n",
				 cpu, boot_cpu_data.family_name);

		seq_म_लिखो(m, "cpu\t\t: %s\n",  boot_cpu_data.cpu_name );

		/* cpu MHz */
		seq_म_लिखो(m, "cpu MHz\t\t: %d.%06d\n",
				 boot_cpu_data.cpu_hz / 1000000,
				 boot_cpu_data.cpu_hz % 1000000  );

#अगर_घोषित CONFIG_PARISC_CPU_TOPOLOGY
		seq_म_लिखो(m, "physical id\t: %d\n",
				topology_physical_package_id(cpu));
		seq_म_लिखो(m, "siblings\t: %d\n",
				cpumask_weight(topology_core_cpumask(cpu)));
		seq_म_लिखो(m, "core id\t\t: %d\n", topology_core_id(cpu));
#पूर्ण_अगर

		seq_म_लिखो(m, "capabilities\t:");
		अगर (boot_cpu_data.pdc.capabilities & PDC_MODEL_OS32)
			seq_माला_दो(m, " os32");
		अगर (boot_cpu_data.pdc.capabilities & PDC_MODEL_OS64)
			seq_माला_दो(m, " os64");
		अगर (boot_cpu_data.pdc.capabilities & PDC_MODEL_IOPसूची_FDC)
			seq_माला_दो(m, " iopdir_fdc");
		चयन (boot_cpu_data.pdc.capabilities & PDC_MODEL_NVA_MASK) अणु
		हाल PDC_MODEL_NVA_SUPPORTED:
			seq_माला_दो(m, " nva_supported");
			अवरोध;
		हाल PDC_MODEL_NVA_SLOW:
			seq_माला_दो(m, " nva_slow");
			अवरोध;
		हाल PDC_MODEL_NVA_UNSUPPORTED:
			seq_माला_दो(m, " needs_equivalent_aliasing");
			अवरोध;
		पूर्ण
		seq_म_लिखो(m, " (0x%02lx)\n", boot_cpu_data.pdc.capabilities);

		seq_म_लिखो(m, "model\t\t: %s\n"
				"model name\t: %s\n",
				 boot_cpu_data.pdc.sys_model_name,
				 cpuinfo->dev ?
				 cpuinfo->dev->name : "Unknown");

		seq_म_लिखो(m, "hversion\t: 0x%08x\n"
			        "sversion\t: 0x%08x\n",
				 boot_cpu_data.hversion,
				 boot_cpu_data.sversion );

		/* prपूर्णांक cachesize info */
		show_cache_info(m);

		seq_म_लिखो(m, "bogomips\t: %lu.%02lu\n",
			     loops_per_jअगरfy / (500000 / HZ),
			     loops_per_jअगरfy / (5000 / HZ) % 100);

		seq_म_लिखो(m, "software id\t: %ld\n\n",
				boot_cpu_data.pdc.model.sw_id);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा parisc_device_id processor_tbl[] __initस्थिर = अणु
	अणु HPHW_NPROC, HVERSION_REV_ANY_ID, HVERSION_ANY_ID, SVERSION_ANY_ID पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

अटल काष्ठा parisc_driver cpu_driver __refdata = अणु
	.name		= "CPU",
	.id_table	= processor_tbl,
	.probe		= processor_probe
पूर्ण;

/**
 * processor_init - Processor initialization procedure.
 *
 * Register this driver.
 */
व्योम __init processor_init(व्योम)
अणु
	रेजिस्टर_parisc_driver(&cpu_driver);
पूर्ण
