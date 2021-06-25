<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SMP boot-related support
 *
 * Copyright (C) 1998-2003, 2005 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 * Copyright (C) 2001, 2004-2005 Intel Corp
 * 	Rohit Seth <rohit.seth@पूर्णांकel.com>
 * 	Suresh Siddha <suresh.b.siddha@पूर्णांकel.com>
 * 	Gorकरोn Jin <gorकरोn.jin@पूर्णांकel.com>
 *	Ashok Raj  <ashok.raj@पूर्णांकel.com>
 *
 * 01/05/16 Rohit Seth <rohit.seth@पूर्णांकel.com>	Moved SMP booting functions from smp.c to here.
 * 01/04/27 David Mosberger <davidm@hpl.hp.com>	Added ITC synching code.
 * 02/07/31 David Mosberger <davidm@hpl.hp.com>	Switch over to hotplug-CPU boot-sequence.
 *						smp_boot_cpus()/smp_commence() is replaced by
 *						smp_prepare_cpus()/__cpu_up()/smp_cpus_करोne().
 * 04/06/21 Ashok Raj		<ashok.raj@पूर्णांकel.com> Added CPU Hotplug Support
 * 04/12/26 Jin Gorकरोn <gorकरोn.jin@पूर्णांकel.com>
 * 04/12/26 Rohit Seth <rohit.seth@पूर्णांकel.com>
 *						Add multi-thपढ़ोing and multi-core detection
 * 05/01/30 Suresh Siddha <suresh.b.siddha@पूर्णांकel.com>
 *						Setup cpu_sibling_map and cpu_core_map
 */

#समावेश <linux/module.h>
#समावेश <linux/acpi.h>
#समावेश <linux/memblock.h>
#समावेश <linux/cpu.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/mm.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/smp.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/efi.h>
#समावेश <linux/percpu.h>
#समावेश <linux/bitops.h>

#समावेश <linux/atomic.h>
#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/current.h>
#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/efi.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mca.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/sal.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/unistd.h>

#घोषणा SMP_DEBUG 0

#अगर SMP_DEBUG
#घोषणा Dprपूर्णांकk(x...)  prपूर्णांकk(x)
#अन्यथा
#घोषणा Dprपूर्णांकk(x...)
#पूर्ण_अगर

#अगर_घोषित CONFIG_HOTPLUG_CPU
#अगर_घोषित CONFIG_PERMIT_BSP_REMOVE
#घोषणा bsp_हटाओ_ok	1
#अन्यथा
#घोषणा bsp_हटाओ_ok	0
#पूर्ण_अगर

/*
 * Global array allocated क्रम NR_CPUS at boot समय
 */
काष्ठा sal_to_os_boot sal_boot_rendez_state[NR_CPUS];

/*
 * start_ap in head.S uses this to store current booting cpu
 * info.
 */
काष्ठा sal_to_os_boot *sal_state_क्रम_booting_cpu = &sal_boot_rendez_state[0];

#घोषणा set_brendez_area(x) (sal_state_क्रम_booting_cpu = &sal_boot_rendez_state[(x)]);

#अन्यथा
#घोषणा set_brendez_area(x)
#पूर्ण_अगर


/*
 * ITC synchronization related stuff:
 */
#घोषणा MASTER	(0)
#घोषणा SLAVE	(SMP_CACHE_BYTES/8)

#घोषणा NUM_ROUNDS	64	/* magic value */
#घोषणा NUM_ITERS	5	/* likewise */

अटल DEFINE_SPINLOCK(itc_sync_lock);
अटल अस्थिर अचिन्हित दीर्घ go[SLAVE + 1];

#घोषणा DEBUG_ITC_SYNC	0

बाह्य व्योम start_ap (व्योम);
बाह्य अचिन्हित दीर्घ ia64_iobase;

काष्ठा task_काष्ठा *task_क्रम_booting_cpu;

/*
 * State क्रम each CPU
 */
DEFINE_PER_CPU(पूर्णांक, cpu_state);

cpumask_t cpu_core_map[NR_CPUS] __cacheline_aligned;
EXPORT_SYMBOL(cpu_core_map);
DEFINE_PER_CPU_SHARED_ALIGNED(cpumask_t, cpu_sibling_map);
EXPORT_PER_CPU_SYMBOL(cpu_sibling_map);

पूर्णांक smp_num_siblings = 1;

/* which logical CPU number maps to which CPU (physical APIC ID) */
अस्थिर पूर्णांक ia64_cpu_to_sapicid[NR_CPUS];
EXPORT_SYMBOL(ia64_cpu_to_sapicid);

अटल cpumask_t cpu_callin_map;

काष्ठा smp_boot_data smp_boot_data __initdata;

अचिन्हित दीर्घ ap_wakeup_vector = -1; /* External Int use to wakeup APs */

अक्षर __initdata no_पूर्णांक_routing;

अचिन्हित अक्षर smp_पूर्णांक_redirect; /* are INT and IPI redirectable by the chipset? */

#अगर_घोषित CONFIG_FORCE_CPEI_RETARGET
#घोषणा CPEI_OVERRIDE_DEFAULT	(1)
#अन्यथा
#घोषणा CPEI_OVERRIDE_DEFAULT	(0)
#पूर्ण_अगर

अचिन्हित पूर्णांक क्रमce_cpei_retarget = CPEI_OVERRIDE_DEFAULT;

अटल पूर्णांक __init
cmdl_क्रमce_cpei(अक्षर *str)
अणु
	पूर्णांक value=0;

	get_option (&str, &value);
	क्रमce_cpei_retarget = value;

	वापस 1;
पूर्ण

__setup("force_cpei=", cmdl_क्रमce_cpei);

अटल पूर्णांक __init
noपूर्णांकroute (अक्षर *str)
अणु
	no_पूर्णांक_routing = 1;
	prपूर्णांकk ("no_int_routing on\n");
	वापस 1;
पूर्ण

__setup("nointroute", noपूर्णांकroute);

अटल व्योम fix_b0_क्रम_bsp(व्योम)
अणु
#अगर_घोषित CONFIG_HOTPLUG_CPU
	पूर्णांक cpuid;
	अटल पूर्णांक fix_bsp_b0 = 1;

	cpuid = smp_processor_id();

	/*
	 * Cache the b0 value on the first AP that comes up
	 */
	अगर (!(fix_bsp_b0 && cpuid))
		वापस;

	sal_boot_rendez_state[0].br[0] = sal_boot_rendez_state[cpuid].br[0];
	prपूर्णांकk ("Fixed BSP b0 value from CPU %d\n", cpuid);

	fix_bsp_b0 = 0;
#पूर्ण_अगर
पूर्ण

व्योम
sync_master (व्योम *arg)
अणु
	अचिन्हित दीर्घ flags, i;

	go[MASTER] = 0;

	local_irq_save(flags);
	अणु
		क्रम (i = 0; i < NUM_ROUNDS*NUM_ITERS; ++i) अणु
			जबतक (!go[MASTER])
				cpu_relax();
			go[MASTER] = 0;
			go[SLAVE] = ia64_get_itc();
		पूर्ण
	पूर्ण
	local_irq_restore(flags);
पूर्ण

/*
 * Return the number of cycles by which our itc dअगरfers from the itc on the master
 * (समय-keeper) CPU.  A positive number indicates our itc is ahead of the master,
 * negative that it is behind.
 */
अटल अंतरभूत दीर्घ
get_delta (दीर्घ *rt, दीर्घ *master)
अणु
	अचिन्हित दीर्घ best_t0 = 0, best_t1 = ~0UL, best_पंचांग = 0;
	अचिन्हित दीर्घ tcenter, t0, t1, पंचांग;
	दीर्घ i;

	क्रम (i = 0; i < NUM_ITERS; ++i) अणु
		t0 = ia64_get_itc();
		go[MASTER] = 1;
		जबतक (!(पंचांग = go[SLAVE]))
			cpu_relax();
		go[SLAVE] = 0;
		t1 = ia64_get_itc();

		अगर (t1 - t0 < best_t1 - best_t0)
			best_t0 = t0, best_t1 = t1, best_पंचांग = पंचांग;
	पूर्ण

	*rt = best_t1 - best_t0;
	*master = best_पंचांग - best_t0;

	/* average best_t0 and best_t1 without overflow: */
	tcenter = (best_t0/2 + best_t1/2);
	अगर (best_t0 % 2 + best_t1 % 2 == 2)
		++tcenter;
	वापस tcenter - best_पंचांग;
पूर्ण

/*
 * Synchronize ar.itc of the current (slave) CPU with the ar.itc of the MASTER CPU
 * (normally the समय-keeper CPU).  We use a बंदd loop to eliminate the possibility of
 * unaccounted-क्रम errors (such as getting a machine check in the middle of a calibration
 * step).  The basic idea is क्रम the slave to ask the master what itc value it has and to
 * पढ़ो its own itc beक्रमe and after the master responds.  Each iteration gives us three
 * बारtamps:
 *
 *	slave		master
 *
 *	t0 ---\
 *             ---\
 *		   --->
 *			पंचांग
 *		   /---
 *	       /---
 *	t1 <---
 *
 *
 * The goal is to adjust the slave's ar.itc such that पंचांग falls exactly half-way between t0
 * and t1.  If we achieve this, the घड़ीs are synchronized provided the पूर्णांकerconnect
 * between the slave and the master is symmetric.  Even अगर the पूर्णांकerconnect were
 * asymmetric, we would still know that the synchronization error is smaller than the
 * roundtrip latency (t0 - t1).
 *
 * When the पूर्णांकerconnect is quiet and symmetric, this lets us synchronize the itc to
 * within one or two cycles.  However, we can only *guarantee* that the synchronization is
 * accurate to within a round-trip समय, which is typically in the range of several
 * hundred cycles (e.g., ~500 cycles).  In practice, this means that the itc's are usually
 * almost perfectly synchronized, but we shouldn't assume that the accuracy is much better
 * than half a micro second or so.
 */
व्योम
ia64_sync_itc (अचिन्हित पूर्णांक master)
अणु
	दीर्घ i, delta, adj, adjust_latency = 0, करोne = 0;
	अचिन्हित दीर्घ flags, rt, master_समय_stamp, bound;
#अगर DEBUG_ITC_SYNC
	काष्ठा अणु
		दीर्घ rt;	/* roundtrip समय */
		दीर्घ master;	/* master's बारtamp */
		दीर्घ dअगरf;	/* dअगरference between midpoपूर्णांक and master's बारtamp */
		दीर्घ lat;	/* estimate of itc adjusपंचांगent latency */
	पूर्ण t[NUM_ROUNDS];
#पूर्ण_अगर

	/*
	 * Make sure local समयr ticks are disabled जबतक we sync.  If
	 * they were enabled, we'd have to worry about nasty issues
	 * like setting the ITC ahead of (or a दीर्घ समय beक्रमe) the
	 * next scheduled tick.
	 */
	BUG_ON((ia64_get_itv() & (1 << 16)) == 0);

	go[MASTER] = 1;

	अगर (smp_call_function_single(master, sync_master, शून्य, 0) < 0) अणु
		prपूर्णांकk(KERN_ERR "sync_itc: failed to get attention of CPU %u!\n", master);
		वापस;
	पूर्ण

	जबतक (go[MASTER])
		cpu_relax();	/* रुको क्रम master to be पढ़ोy */

	spin_lock_irqsave(&itc_sync_lock, flags);
	अणु
		क्रम (i = 0; i < NUM_ROUNDS; ++i) अणु
			delta = get_delta(&rt, &master_समय_stamp);
			अगर (delta == 0) अणु
				करोne = 1;	/* let's lock on to this... */
				bound = rt;
			पूर्ण

			अगर (!करोne) अणु
				अगर (i > 0) अणु
					adjust_latency += -delta;
					adj = -delta + adjust_latency/4;
				पूर्ण अन्यथा
					adj = -delta;

				ia64_set_itc(ia64_get_itc() + adj);
			पूर्ण
#अगर DEBUG_ITC_SYNC
			t[i].rt = rt;
			t[i].master = master_समय_stamp;
			t[i].dअगरf = delta;
			t[i].lat = adjust_latency/4;
#पूर्ण_अगर
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&itc_sync_lock, flags);

#अगर DEBUG_ITC_SYNC
	क्रम (i = 0; i < NUM_ROUNDS; ++i)
		prपूर्णांकk("rt=%5ld master=%5ld diff=%5ld adjlat=%5ld\n",
		       t[i].rt, t[i].master, t[i].dअगरf, t[i].lat);
#पूर्ण_अगर

	prपूर्णांकk(KERN_INFO "CPU %d: synchronized ITC with CPU %u (last diff %ld cycles, "
	       "maxerr %lu cycles)\n", smp_processor_id(), master, delta, rt);
पूर्ण

/*
 * Ideally sets up per-cpu profiling hooks.  Doesn't करो much now...
 */
अटल अंतरभूत व्योम smp_setup_percpu_समयr(व्योम)
अणु
पूर्ण

अटल व्योम
smp_callin (व्योम)
अणु
	पूर्णांक cpuid, phys_id, itc_master;
	काष्ठा cpuinfo_ia64 *last_cpuinfo, *this_cpuinfo;
	बाह्य व्योम ia64_init_iपंचांग(व्योम);
	बाह्य अस्थिर पूर्णांक समय_keeper_id;

	cpuid = smp_processor_id();
	phys_id = hard_smp_processor_id();
	itc_master = समय_keeper_id;

	अगर (cpu_online(cpuid)) अणु
		prपूर्णांकk(KERN_ERR "huh, phys CPU#0x%x, CPU#0x%x already present??\n",
		       phys_id, cpuid);
		BUG();
	पूर्ण

	fix_b0_क्रम_bsp();

	/*
	 * numa_node_id() works after this.
	 */
	set_numa_node(cpu_to_node_map[cpuid]);
	set_numa_mem(local_memory_node(cpu_to_node_map[cpuid]));

	spin_lock(&vector_lock);
	/* Setup the per cpu irq handling data काष्ठाures */
	__setup_vector_irq(cpuid);
	notअगरy_cpu_starting(cpuid);
	set_cpu_online(cpuid, true);
	per_cpu(cpu_state, cpuid) = CPU_ONLINE;
	spin_unlock(&vector_lock);

	smp_setup_percpu_समयr();

	ia64_mca_cmc_vector_setup();	/* Setup vector on AP */

	local_irq_enable();

	अगर (!(sal_platक्रमm_features & IA64_SAL_PLATFORM_FEATURE_ITC_DRIFT)) अणु
		/*
		 * Synchronize the ITC with the BP.  Need to करो this after irqs are
		 * enabled because ia64_sync_itc() calls smp_call_function_single(), which
		 * calls spin_unlock_bh(), which calls spin_unlock_bh(), which calls
		 * local_bh_enable(), which bugs out अगर irqs are not enabled...
		 */
		Dprपूर्णांकk("Going to syncup ITC with ITC Master.\n");
		ia64_sync_itc(itc_master);
	पूर्ण

	/*
	 * Get our bogomips.
	 */
	ia64_init_iपंचांग();

	/*
	 * Delay calibration can be skipped अगर new processor is identical to the
	 * previous processor.
	 */
	last_cpuinfo = cpu_data(cpuid - 1);
	this_cpuinfo = local_cpu_data;
	अगर (last_cpuinfo->itc_freq != this_cpuinfo->itc_freq ||
	    last_cpuinfo->proc_freq != this_cpuinfo->proc_freq ||
	    last_cpuinfo->features != this_cpuinfo->features ||
	    last_cpuinfo->revision != this_cpuinfo->revision ||
	    last_cpuinfo->family != this_cpuinfo->family ||
	    last_cpuinfo->archrev != this_cpuinfo->archrev ||
	    last_cpuinfo->model != this_cpuinfo->model)
		calibrate_delay();
	local_cpu_data->loops_per_jअगरfy = loops_per_jअगरfy;

	/*
	 * Allow the master to जारी.
	 */
	cpumask_set_cpu(cpuid, &cpu_callin_map);
	Dprपूर्णांकk("Stack on CPU %d at about %p\n",cpuid, &cpuid);
पूर्ण


/*
 * Activate a secondary processor.  head.S calls this.
 */
पूर्णांक
start_secondary (व्योम *unused)
अणु
	/* Early console may use I/O ports */
	ia64_set_kr(IA64_KR_IO_BASE, __pa(ia64_iobase));
#अगर_अघोषित CONFIG_PRINTK_TIME
	Dprपूर्णांकk("start_secondary: starting CPU 0x%x\n", hard_smp_processor_id());
#पूर्ण_अगर
	efi_map_pal_code();
	cpu_init();
	preempt_disable();
	smp_callin();

	cpu_startup_entry(CPUHP_AP_ONLINE_IDLE);
	वापस 0;
पूर्ण

अटल पूर्णांक
करो_boot_cpu (पूर्णांक sapicid, पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	पूर्णांक समयout;

	task_क्रम_booting_cpu = idle;
	Dprपूर्णांकk("Sending wakeup vector %lu to AP 0x%x/0x%x.\n", ap_wakeup_vector, cpu, sapicid);

	set_brendez_area(cpu);
	ia64_send_ipi(cpu, ap_wakeup_vector, IA64_IPI_DM_INT, 0);

	/*
	 * Wait 10s total क्रम the AP to start
	 */
	Dprपूर्णांकk("Waiting on callin_map ...");
	क्रम (समयout = 0; समयout < 100000; समयout++) अणु
		अगर (cpumask_test_cpu(cpu, &cpu_callin_map))
			अवरोध;  /* It has booted */
		barrier(); /* Make sure we re-पढ़ो cpu_callin_map */
		udelay(100);
	पूर्ण
	Dprपूर्णांकk("\n");

	अगर (!cpumask_test_cpu(cpu, &cpu_callin_map)) अणु
		prपूर्णांकk(KERN_ERR "Processor 0x%x/0x%x is stuck.\n", cpu, sapicid);
		ia64_cpu_to_sapicid[cpu] = -1;
		set_cpu_online(cpu, false);  /* was set in smp_callin() */
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init
decay (अक्षर *str)
अणु
	पूर्णांक ticks;
	get_option (&str, &ticks);
	वापस 1;
पूर्ण

__setup("decay=", decay);

/*
 * Initialize the logical CPU number to SAPICID mapping
 */
व्योम __init
smp_build_cpu_map (व्योम)
अणु
	पूर्णांक sapicid, cpu, i;
	पूर्णांक boot_cpu_id = hard_smp_processor_id();

	क्रम (cpu = 0; cpu < NR_CPUS; cpu++) अणु
		ia64_cpu_to_sapicid[cpu] = -1;
	पूर्ण

	ia64_cpu_to_sapicid[0] = boot_cpu_id;
	init_cpu_present(cpumask_of(0));
	set_cpu_possible(0, true);
	क्रम (cpu = 1, i = 0; i < smp_boot_data.cpu_count; i++) अणु
		sapicid = smp_boot_data.cpu_phys_id[i];
		अगर (sapicid == boot_cpu_id)
			जारी;
		set_cpu_present(cpu, true);
		set_cpu_possible(cpu, true);
		ia64_cpu_to_sapicid[cpu] = sapicid;
		cpu++;
	पूर्ण
पूर्ण

/*
 * Cycle through the APs sending Wakeup IPIs to boot each.
 */
व्योम __init
smp_prepare_cpus (अचिन्हित पूर्णांक max_cpus)
अणु
	पूर्णांक boot_cpu_id = hard_smp_processor_id();

	/*
	 * Initialize the per-CPU profiling counter/multiplier
	 */

	smp_setup_percpu_समयr();

	cpumask_set_cpu(0, &cpu_callin_map);

	local_cpu_data->loops_per_jअगरfy = loops_per_jअगरfy;
	ia64_cpu_to_sapicid[0] = boot_cpu_id;

	prपूर्णांकk(KERN_INFO "Boot processor id 0x%x/0x%x\n", 0, boot_cpu_id);

	current_thपढ़ो_info()->cpu = 0;

	/*
	 * If SMP should be disabled, then really disable it!
	 */
	अगर (!max_cpus) अणु
		prपूर्णांकk(KERN_INFO "SMP mode deactivated.\n");
		init_cpu_online(cpumask_of(0));
		init_cpu_present(cpumask_of(0));
		init_cpu_possible(cpumask_of(0));
		वापस;
	पूर्ण
पूर्ण

व्योम smp_prepare_boot_cpu(व्योम)
अणु
	set_cpu_online(smp_processor_id(), true);
	cpumask_set_cpu(smp_processor_id(), &cpu_callin_map);
	set_numa_node(cpu_to_node_map[smp_processor_id()]);
	per_cpu(cpu_state, smp_processor_id()) = CPU_ONLINE;
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल अंतरभूत व्योम
clear_cpu_sibling_map(पूर्णांक cpu)
अणु
	पूर्णांक i;

	क्रम_each_cpu(i, &per_cpu(cpu_sibling_map, cpu))
		cpumask_clear_cpu(cpu, &per_cpu(cpu_sibling_map, i));
	क्रम_each_cpu(i, &cpu_core_map[cpu])
		cpumask_clear_cpu(cpu, &cpu_core_map[i]);

	per_cpu(cpu_sibling_map, cpu) = cpu_core_map[cpu] = CPU_MASK_NONE;
पूर्ण

अटल व्योम
हटाओ_siblinginfo(पूर्णांक cpu)
अणु
	पूर्णांक last = 0;

	अगर (cpu_data(cpu)->thपढ़ोs_per_core == 1 &&
	    cpu_data(cpu)->cores_per_socket == 1) अणु
		cpumask_clear_cpu(cpu, &cpu_core_map[cpu]);
		cpumask_clear_cpu(cpu, &per_cpu(cpu_sibling_map, cpu));
		वापस;
	पूर्ण

	last = (cpumask_weight(&cpu_core_map[cpu]) == 1 ? 1 : 0);

	/* हटाओ it from all sibling map's */
	clear_cpu_sibling_map(cpu);
पूर्ण

बाह्य व्योम fixup_irqs(व्योम);

पूर्णांक migrate_platक्रमm_irqs(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक new_cpei_cpu;
	काष्ठा irq_data *data = शून्य;
	स्थिर काष्ठा cpumask *mask;
	पूर्णांक 		retval = 0;

	/*
	 * करोnt permit CPEI target to हटाओd.
	 */
	अगर (cpe_vector > 0 && is_cpu_cpei_target(cpu)) अणु
		prपूर्णांकk ("CPU (%d) is CPEI Target\n", cpu);
		अगर (can_cpei_retarget()) अणु
			/*
			 * Now re-target the CPEI to a dअगरferent processor
			 */
			new_cpei_cpu = cpumask_any(cpu_online_mask);
			mask = cpumask_of(new_cpei_cpu);
			set_cpei_target_cpu(new_cpei_cpu);
			data = irq_get_irq_data(ia64_cpe_irq);
			/*
			 * Switch क्रम now, immediately, we need to करो fake पूर्णांकr
			 * as other पूर्णांकerrupts, but need to study CPEI behaviour with
			 * polling beक्रमe making changes.
			 */
			अगर (data && data->chip) अणु
				data->chip->irq_disable(data);
				data->chip->irq_set_affinity(data, mask, false);
				data->chip->irq_enable(data);
				prपूर्णांकk ("Re-targeting CPEI to cpu %d\n", new_cpei_cpu);
			पूर्ण
		पूर्ण
		अगर (!data) अणु
			prपूर्णांकk ("Unable to retarget CPEI, offline cpu [%d] failed\n", cpu);
			retval = -EBUSY;
		पूर्ण
	पूर्ण
	वापस retval;
पूर्ण

/* must be called with cpucontrol mutex held */
पूर्णांक __cpu_disable(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();

	/*
	 * करोnt permit boot processor क्रम now
	 */
	अगर (cpu == 0 && !bsp_हटाओ_ok) अणु
		prपूर्णांकk ("Your platform does not support removal of BSP\n");
		वापस (-EBUSY);
	पूर्ण

	set_cpu_online(cpu, false);

	अगर (migrate_platक्रमm_irqs(cpu)) अणु
		set_cpu_online(cpu, true);
		वापस -EBUSY;
	पूर्ण

	हटाओ_siblinginfo(cpu);
	fixup_irqs();
	local_flush_tlb_all();
	cpumask_clear_cpu(cpu, &cpu_callin_map);
	वापस 0;
पूर्ण

व्योम __cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < 100; i++) अणु
		/* They ack this in play_dead by setting CPU_DEAD */
		अगर (per_cpu(cpu_state, cpu) == CPU_DEAD)
		अणु
			prपूर्णांकk ("CPU %d is now offline\n", cpu);
			वापस;
		पूर्ण
		msleep(100);
	पूर्ण
 	prपूर्णांकk(KERN_ERR "CPU %u didn't die...\n", cpu);
पूर्ण
#पूर्ण_अगर /* CONFIG_HOTPLUG_CPU */

व्योम
smp_cpus_करोne (अचिन्हित पूर्णांक dummy)
अणु
	पूर्णांक cpu;
	अचिन्हित दीर्घ bogosum = 0;

	/*
	 * Allow the user to impress मित्रs.
	 */

	क्रम_each_online_cpu(cpu) अणु
		bogosum += cpu_data(cpu)->loops_per_jअगरfy;
	पूर्ण

	prपूर्णांकk(KERN_INFO "Total of %d processors activated (%lu.%02lu BogoMIPS).\n",
	       (पूर्णांक)num_online_cpus(), bogosum/(500000/HZ), (bogosum/(5000/HZ))%100);
पूर्ण

अटल अंतरभूत व्योम set_cpu_sibling_map(पूर्णांक cpu)
अणु
	पूर्णांक i;

	क्रम_each_online_cpu(i) अणु
		अगर ((cpu_data(cpu)->socket_id == cpu_data(i)->socket_id)) अणु
			cpumask_set_cpu(i, &cpu_core_map[cpu]);
			cpumask_set_cpu(cpu, &cpu_core_map[i]);
			अगर (cpu_data(cpu)->core_id == cpu_data(i)->core_id) अणु
				cpumask_set_cpu(i,
						&per_cpu(cpu_sibling_map, cpu));
				cpumask_set_cpu(cpu,
						&per_cpu(cpu_sibling_map, i));
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक
__cpu_up(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *tidle)
अणु
	पूर्णांक ret;
	पूर्णांक sapicid;

	sapicid = ia64_cpu_to_sapicid[cpu];
	अगर (sapicid == -1)
		वापस -EINVAL;

	/*
	 * Alपढ़ोy booted cpu? not valid anymore since we करोnt
	 * करो idle loop tightspin anymore.
	 */
	अगर (cpumask_test_cpu(cpu, &cpu_callin_map))
		वापस -EINVAL;

	per_cpu(cpu_state, cpu) = CPU_UP_PREPARE;
	/* Processor goes to start_secondary(), sets online flag */
	ret = करो_boot_cpu(sapicid, cpu, tidle);
	अगर (ret < 0)
		वापस ret;

	अगर (cpu_data(cpu)->thपढ़ोs_per_core == 1 &&
	    cpu_data(cpu)->cores_per_socket == 1) अणु
		cpumask_set_cpu(cpu, &per_cpu(cpu_sibling_map, cpu));
		cpumask_set_cpu(cpu, &cpu_core_map[cpu]);
		वापस 0;
	पूर्ण

	set_cpu_sibling_map(cpu);

	वापस 0;
पूर्ण

/*
 * Assume that CPUs have been discovered by some platक्रमm-dependent पूर्णांकerface.  For
 * SoftSDV/Lion, that would be ACPI.
 *
 * Setup of the IPI irq handler is करोne in irq.c:init_IRQ_SMP().
 */
व्योम __init
init_smp_config(व्योम)
अणु
	काष्ठा fptr अणु
		अचिन्हित दीर्घ fp;
		अचिन्हित दीर्घ gp;
	पूर्ण *ap_startup;
	दीर्घ sal_ret;

	/* Tell SAL where to drop the APs.  */
	ap_startup = (काष्ठा fptr *) start_ap;
	sal_ret = ia64_sal_set_vectors(SAL_VECTOR_OS_BOOT_RENDEZ,
				       ia64_tpa(ap_startup->fp), ia64_tpa(ap_startup->gp), 0, 0, 0, 0);
	अगर (sal_ret < 0)
		prपूर्णांकk(KERN_ERR "SMP: Can't set SAL AP Boot Rendezvous: %s\n",
		       ia64_sal_म_त्रुटि(sal_ret));
पूर्ण

/*
 * identअगरy_siblings(cpu) माला_लो called from identअगरy_cpu. This populates the 
 * inक्रमmation related to logical execution units in per_cpu_data काष्ठाure.
 */
व्योम identअगरy_siblings(काष्ठा cpuinfo_ia64 *c)
अणु
	दीर्घ status;
	u16 pltid;
	pal_logical_to_physical_t info;

	status = ia64_pal_logical_to_phys(-1, &info);
	अगर (status != PAL_STATUS_SUCCESS) अणु
		अगर (status != PAL_STATUS_UNIMPLEMENTED) अणु
			prपूर्णांकk(KERN_ERR
				"ia64_pal_logical_to_phys failed with %ld\n",
				status);
			वापस;
		पूर्ण

		info.overview_ppid = 0;
		info.overview_cpp  = 1;
		info.overview_tpc  = 1;
	पूर्ण

	status = ia64_sal_physical_id_info(&pltid);
	अगर (status != PAL_STATUS_SUCCESS) अणु
		अगर (status != PAL_STATUS_UNIMPLEMENTED)
			prपूर्णांकk(KERN_ERR
				"ia64_sal_pltid failed with %ld\n",
				status);
		वापस;
	पूर्ण

	c->socket_id =  (pltid << 8) | info.overview_ppid;

	अगर (info.overview_cpp == 1 && info.overview_tpc == 1)
		वापस;

	c->cores_per_socket = info.overview_cpp;
	c->thपढ़ोs_per_core = info.overview_tpc;
	c->num_log = info.overview_num_log;

	c->core_id = info.log1_cid;
	c->thपढ़ो_id = info.log1_tid;
पूर्ण

/*
 * वापसs non zero, अगर multi-thपढ़ोing is enabled
 * on at least one physical package. Due to hotplug cpu
 * and (maxcpus=), all thपढ़ोs may not necessarily be enabled
 * even though the processor supports multi-thपढ़ोing.
 */
पूर्णांक is_multithपढ़ोing_enabled(व्योम)
अणु
	पूर्णांक i, j;

	क्रम_each_present_cpu(i) अणु
		क्रम_each_present_cpu(j) अणु
			अगर (j == i)
				जारी;
			अगर ((cpu_data(j)->socket_id == cpu_data(i)->socket_id)) अणु
				अगर (cpu_data(j)->core_id == cpu_data(i)->core_id)
					वापस 1;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(is_multithपढ़ोing_enabled);
