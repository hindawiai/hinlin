<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* smp.c: Sparc64 SMP support.
 *
 * Copyright (C) 1997, 2007, 2008 David S. Miller (davem@davemloft.net)
 */

#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/hotplug.h>
#समावेश <linux/mm.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/smp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/cache.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/profile.h>
#समावेश <linux/memblock.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/cpu.h>
#समावेश <linux/slab.h>
#समावेश <linux/kgdb.h>

#समावेश <यंत्र/head.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/cpudata.h>
#समावेश <यंत्र/hvtramp.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/समयr.h>
#समावेश <यंत्र/setup.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/irq_regs.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/oplib.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/starfire.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/mdesc.h>
#समावेश <यंत्र/ldc.h>
#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/pcr.h>

#समावेश "cpumap.h"
#समावेश "kernel.h"

DEFINE_PER_CPU(cpumask_t, cpu_sibling_map) = CPU_MASK_NONE;
cpumask_t cpu_core_map[NR_CPUS] __पढ़ो_mostly =
	अणु [0 ... NR_CPUS-1] = CPU_MASK_NONE पूर्ण;

cpumask_t cpu_core_sib_map[NR_CPUS] __पढ़ो_mostly = अणु
	[0 ... NR_CPUS-1] = CPU_MASK_NONE पूर्ण;

cpumask_t cpu_core_sib_cache_map[NR_CPUS] __पढ़ो_mostly = अणु
	[0 ... NR_CPUS - 1] = CPU_MASK_NONE पूर्ण;

EXPORT_PER_CPU_SYMBOL(cpu_sibling_map);
EXPORT_SYMBOL(cpu_core_map);
EXPORT_SYMBOL(cpu_core_sib_map);
EXPORT_SYMBOL(cpu_core_sib_cache_map);

अटल cpumask_t smp_commenced_mask;

अटल DEFINE_PER_CPU(bool, poke);
अटल bool cpu_poke;

व्योम smp_info(काष्ठा seq_file *m)
अणु
	पूर्णांक i;
	
	seq_म_लिखो(m, "State:\n");
	क्रम_each_online_cpu(i)
		seq_म_लिखो(m, "CPU%d:\t\tonline\n", i);
पूर्ण

व्योम smp_bogo(काष्ठा seq_file *m)
अणु
	पूर्णांक i;
	
	क्रम_each_online_cpu(i)
		seq_म_लिखो(m,
			   "Cpu%dClkTck\t: %016lx\n",
			   i, cpu_data(i).घड़ी_प्रकारick);
पूर्ण

बाह्य व्योम setup_sparc64_समयr(व्योम);

अटल अस्थिर अचिन्हित दीर्घ callin_flag = 0;

व्योम smp_callin(व्योम)
अणु
	पूर्णांक cpuid = hard_smp_processor_id();

	__local_per_cpu_offset = __per_cpu_offset(cpuid);

	अगर (tlb_type == hypervisor)
		sun4v_ktsb_रेजिस्टर();

	__flush_tlb_all();

	setup_sparc64_समयr();

	अगर (cheetah_pcache_क्रमced_on)
		cheetah_enable_pcache();

	callin_flag = 1;
	__यंत्र__ __अस्थिर__("membar #Sync\n\t"
			     "flush  %%g6" : : : "memory");

	/* Clear this or we will die instantly when we
	 * schedule back to this idler...
	 */
	current_thपढ़ो_info()->new_child = 0;

	/* Attach to the address space of init_task. */
	mmgrab(&init_mm);
	current->active_mm = &init_mm;

	/* inक्रमm the notअगरiers about the new cpu */
	notअगरy_cpu_starting(cpuid);

	जबतक (!cpumask_test_cpu(cpuid, &smp_commenced_mask))
		rmb();

	set_cpu_online(cpuid, true);

	/* idle thपढ़ो is expected to have preempt disabled */
	preempt_disable();

	local_irq_enable();

	cpu_startup_entry(CPUHP_AP_ONLINE_IDLE);
पूर्ण

व्योम cpu_panic(व्योम)
अणु
	prपूर्णांकk("CPU[%d]: Returns from cpu_idle!\n", smp_processor_id());
	panic("SMP bolixed\n");
पूर्ण

/* This tick रेजिस्टर synchronization scheme is taken entirely from
 * the ia64 port, see arch/ia64/kernel/smpboot.c क्रम details and credit.
 *
 * The only change I've made is to rework it so that the master
 * initiates the synchonization instead of the slave. -DaveM
 */

#घोषणा MASTER	0
#घोषणा SLAVE	(SMP_CACHE_BYTES/माप(अचिन्हित दीर्घ))

#घोषणा NUM_ROUNDS	64	/* magic value */
#घोषणा NUM_ITERS	5	/* likewise */

अटल DEFINE_RAW_SPINLOCK(itc_sync_lock);
अटल अचिन्हित दीर्घ go[SLAVE + 1];

#घोषणा DEBUG_TICK_SYNC	0

अटल अंतरभूत दीर्घ get_delta (दीर्घ *rt, दीर्घ *master)
अणु
	अचिन्हित दीर्घ best_t0 = 0, best_t1 = ~0UL, best_पंचांग = 0;
	अचिन्हित दीर्घ tcenter, t0, t1, पंचांग;
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < NUM_ITERS; i++) अणु
		t0 = tick_ops->get_tick();
		go[MASTER] = 1;
		membar_safe("#StoreLoad");
		जबतक (!(पंचांग = go[SLAVE]))
			rmb();
		go[SLAVE] = 0;
		wmb();
		t1 = tick_ops->get_tick();

		अगर (t1 - t0 < best_t1 - best_t0)
			best_t0 = t0, best_t1 = t1, best_पंचांग = पंचांग;
	पूर्ण

	*rt = best_t1 - best_t0;
	*master = best_पंचांग - best_t0;

	/* average best_t0 and best_t1 without overflow: */
	tcenter = (best_t0/2 + best_t1/2);
	अगर (best_t0 % 2 + best_t1 % 2 == 2)
		tcenter++;
	वापस tcenter - best_पंचांग;
पूर्ण

व्योम smp_synchronize_tick_client(व्योम)
अणु
	दीर्घ i, delta, adj, adjust_latency = 0, करोne = 0;
	अचिन्हित दीर्घ flags, rt, master_समय_stamp;
#अगर DEBUG_TICK_SYNC
	काष्ठा अणु
		दीर्घ rt;	/* roundtrip समय */
		दीर्घ master;	/* master's बारtamp */
		दीर्घ dअगरf;	/* dअगरference between midpoपूर्णांक and master's बारtamp */
		दीर्घ lat;	/* estimate of itc adjusपंचांगent latency */
	पूर्ण t[NUM_ROUNDS];
#पूर्ण_अगर

	go[MASTER] = 1;

	जबतक (go[MASTER])
		rmb();

	local_irq_save(flags);
	अणु
		क्रम (i = 0; i < NUM_ROUNDS; i++) अणु
			delta = get_delta(&rt, &master_समय_stamp);
			अगर (delta == 0)
				करोne = 1;	/* let's lock on to this... */

			अगर (!करोne) अणु
				अगर (i > 0) अणु
					adjust_latency += -delta;
					adj = -delta + adjust_latency/4;
				पूर्ण अन्यथा
					adj = -delta;

				tick_ops->add_tick(adj);
			पूर्ण
#अगर DEBUG_TICK_SYNC
			t[i].rt = rt;
			t[i].master = master_समय_stamp;
			t[i].dअगरf = delta;
			t[i].lat = adjust_latency/4;
#पूर्ण_अगर
		पूर्ण
	पूर्ण
	local_irq_restore(flags);

#अगर DEBUG_TICK_SYNC
	क्रम (i = 0; i < NUM_ROUNDS; i++)
		prपूर्णांकk("rt=%5ld master=%5ld diff=%5ld adjlat=%5ld\n",
		       t[i].rt, t[i].master, t[i].dअगरf, t[i].lat);
#पूर्ण_अगर

	prपूर्णांकk(KERN_INFO "CPU %d: synchronized TICK with master CPU "
	       "(last diff %ld cycles, maxerr %lu cycles)\n",
	       smp_processor_id(), delta, rt);
पूर्ण

अटल व्योम smp_start_sync_tick_client(पूर्णांक cpu);

अटल व्योम smp_synchronize_one_tick(पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ flags, i;

	go[MASTER] = 0;

	smp_start_sync_tick_client(cpu);

	/* रुको क्रम client to be पढ़ोy */
	जबतक (!go[MASTER])
		rmb();

	/* now let the client proceed पूर्णांकo his loop */
	go[MASTER] = 0;
	membar_safe("#StoreLoad");

	raw_spin_lock_irqsave(&itc_sync_lock, flags);
	अणु
		क्रम (i = 0; i < NUM_ROUNDS*NUM_ITERS; i++) अणु
			जबतक (!go[MASTER])
				rmb();
			go[MASTER] = 0;
			wmb();
			go[SLAVE] = tick_ops->get_tick();
			membar_safe("#StoreLoad");
		पूर्ण
	पूर्ण
	raw_spin_unlock_irqrestore(&itc_sync_lock, flags);
पूर्ण

#अगर defined(CONFIG_SUN_LDOMS) && defined(CONFIG_HOTPLUG_CPU)
अटल व्योम lकरोm_startcpu_cpuid(अचिन्हित पूर्णांक cpu, अचिन्हित दीर्घ thपढ़ो_reg,
				व्योम **descrp)
अणु
	बाह्य अचिन्हित दीर्घ sparc64_ttable_tl0;
	बाह्य अचिन्हित दीर्घ kern_locked_tte_data;
	काष्ठा hvtramp_descr *hdesc;
	अचिन्हित दीर्घ trampoline_ra;
	काष्ठा trap_per_cpu *tb;
	u64 tte_vaddr, tte_data;
	अचिन्हित दीर्घ hv_err;
	पूर्णांक i;

	hdesc = kzalloc(माप(*hdesc) +
			(माप(काष्ठा hvtramp_mapping) *
			 num_kernel_image_mappings - 1),
			GFP_KERNEL);
	अगर (!hdesc) अणु
		prपूर्णांकk(KERN_ERR "ldom_startcpu_cpuid: Cannot allocate "
		       "hvtramp_descr.\n");
		वापस;
	पूर्ण
	*descrp = hdesc;

	hdesc->cpu = cpu;
	hdesc->num_mappings = num_kernel_image_mappings;

	tb = &trap_block[cpu];

	hdesc->fault_info_va = (अचिन्हित दीर्घ) &tb->fault_info;
	hdesc->fault_info_pa = kimage_addr_to_ra(&tb->fault_info);

	hdesc->thपढ़ो_reg = thपढ़ो_reg;

	tte_vaddr = (अचिन्हित दीर्घ) KERNBASE;
	tte_data = kern_locked_tte_data;

	क्रम (i = 0; i < hdesc->num_mappings; i++) अणु
		hdesc->maps[i].vaddr = tte_vaddr;
		hdesc->maps[i].tte   = tte_data;
		tte_vaddr += 0x400000;
		tte_data  += 0x400000;
	पूर्ण

	trampoline_ra = kimage_addr_to_ra(hv_cpu_startup);

	hv_err = sun4v_cpu_start(cpu, trampoline_ra,
				 kimage_addr_to_ra(&sparc64_ttable_tl0),
				 __pa(hdesc));
	अगर (hv_err)
		prपूर्णांकk(KERN_ERR "ldom_startcpu_cpuid: sun4v_cpu_start() "
		       "gives error %lu\n", hv_err);
पूर्ण
#पूर्ण_अगर

बाह्य अचिन्हित दीर्घ sparc64_cpu_startup;

/* The OBP cpu startup callback truncates the 3rd arg cookie to
 * 32-bits (I think) so to be safe we have it पढ़ो the poपूर्णांकer
 * contained here so we work on >4GB machines. -DaveM
 */
अटल काष्ठा thपढ़ो_info *cpu_new_thपढ़ो = शून्य;

अटल पूर्णांक smp_boot_one_cpu(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	अचिन्हित दीर्घ entry =
		(अचिन्हित दीर्घ)(&sparc64_cpu_startup);
	अचिन्हित दीर्घ cookie =
		(अचिन्हित दीर्घ)(&cpu_new_thपढ़ो);
	व्योम *descr = शून्य;
	पूर्णांक समयout, ret;

	callin_flag = 0;
	cpu_new_thपढ़ो = task_thपढ़ो_info(idle);

	अगर (tlb_type == hypervisor) अणु
#अगर defined(CONFIG_SUN_LDOMS) && defined(CONFIG_HOTPLUG_CPU)
		अगर (lकरोm_करोमुख्यing_enabled)
			lकरोm_startcpu_cpuid(cpu,
					    (अचिन्हित दीर्घ) cpu_new_thपढ़ो,
					    &descr);
		अन्यथा
#पूर्ण_अगर
			prom_startcpu_cpuid(cpu, entry, cookie);
	पूर्ण अन्यथा अणु
		काष्ठा device_node *dp = of_find_node_by_cpuid(cpu);

		prom_startcpu(dp->phandle, entry, cookie);
	पूर्ण

	क्रम (समयout = 0; समयout < 50000; समयout++) अणु
		अगर (callin_flag)
			अवरोध;
		udelay(100);
	पूर्ण

	अगर (callin_flag) अणु
		ret = 0;
	पूर्ण अन्यथा अणु
		prपूर्णांकk("Processor %d is stuck.\n", cpu);
		ret = -ENODEV;
	पूर्ण
	cpu_new_thपढ़ो = शून्य;

	kमुक्त(descr);

	वापस ret;
पूर्ण

अटल व्योम spitfire_xcall_helper(u64 data0, u64 data1, u64 data2, u64 pstate, अचिन्हित दीर्घ cpu)
अणु
	u64 result, target;
	पूर्णांक stuck, पंचांगp;

	अगर (this_is_starfire) अणु
		/* map to real upaid */
		cpu = (((cpu & 0x3c) << 1) |
			((cpu & 0x40) >> 4) |
			(cpu & 0x3));
	पूर्ण

	target = (cpu << 14) | 0x70;
again:
	/* Ok, this is the real Spitfire Errata #54.
	 * One must पढ़ो back from a UDB पूर्णांकernal रेजिस्टर
	 * after ग_लिखोs to the UDB पूर्णांकerrupt dispatch, but
	 * beक्रमe the membar Sync क्रम that ग_लिखो.
	 * So we use the high UDB control रेजिस्टर (ASI 0x7f,
	 * ADDR 0x20) क्रम the dummy पढ़ो. -DaveM
	 */
	पंचांगp = 0x40;
	__यंत्र__ __अस्थिर__(
	"wrpr	%1, %2, %%pstate\n\t"
	"stxa	%4, [%0] %3\n\t"
	"stxa	%5, [%0+%8] %3\n\t"
	"add	%0, %8, %0\n\t"
	"stxa	%6, [%0+%8] %3\n\t"
	"membar	#Sync\n\t"
	"stxa	%%g0, [%7] %3\n\t"
	"membar	#Sync\n\t"
	"mov	0x20, %%g1\n\t"
	"ldxa	[%%g1] 0x7f, %%g0\n\t"
	"membar	#Sync"
	: "=r" (पंचांगp)
	: "r" (pstate), "i" (PSTATE_IE), "i" (ASI_INTR_W),
	  "r" (data0), "r" (data1), "r" (data2), "r" (target),
	  "r" (0x10), "0" (पंचांगp)
        : "g1");

	/* NOTE: PSTATE_IE is still clear. */
	stuck = 100000;
	करो अणु
		__यंत्र__ __अस्थिर__("ldxa [%%g0] %1, %0"
			: "=r" (result)
			: "i" (ASI_INTR_DISPATCH_STAT));
		अगर (result == 0) अणु
			__यंत्र__ __अस्थिर__("wrpr %0, 0x0, %%pstate"
					     : : "r" (pstate));
			वापस;
		पूर्ण
		stuck -= 1;
		अगर (stuck == 0)
			अवरोध;
	पूर्ण जबतक (result & 0x1);
	__यंत्र__ __अस्थिर__("wrpr %0, 0x0, %%pstate"
			     : : "r" (pstate));
	अगर (stuck == 0) अणु
		prपूर्णांकk("CPU[%d]: mondo stuckage result[%016llx]\n",
		       smp_processor_id(), result);
	पूर्ण अन्यथा अणु
		udelay(2);
		जाओ again;
	पूर्ण
पूर्ण

अटल व्योम spitfire_xcall_deliver(काष्ठा trap_per_cpu *tb, पूर्णांक cnt)
अणु
	u64 *monकरो, data0, data1, data2;
	u16 *cpu_list;
	u64 pstate;
	पूर्णांक i;

	__यंत्र__ __अस्थिर__("rdpr %%pstate, %0" : "=r" (pstate));
	cpu_list = __va(tb->cpu_list_pa);
	monकरो = __va(tb->cpu_monकरो_block_pa);
	data0 = monकरो[0];
	data1 = monकरो[1];
	data2 = monकरो[2];
	क्रम (i = 0; i < cnt; i++)
		spitfire_xcall_helper(data0, data1, data2, pstate, cpu_list[i]);
पूर्ण

/* Cheetah now allows to send the whole 64-bytes of data in the पूर्णांकerrupt
 * packet, but we have no use क्रम that.  However we करो take advantage of
 * the new pipelining feature (ie. dispatch to multiple cpus simultaneously).
 */
अटल व्योम cheetah_xcall_deliver(काष्ठा trap_per_cpu *tb, पूर्णांक cnt)
अणु
	पूर्णांक nack_busy_id, is_jbus, need_more;
	u64 *monकरो, pstate, ver, busy_mask;
	u16 *cpu_list;

	cpu_list = __va(tb->cpu_list_pa);
	monकरो = __va(tb->cpu_monकरो_block_pa);

	/* Unक्रमtunately, someone at Sun had the brilliant idea to make the
	 * busy/nack fields hard-coded by ITID number क्रम this Ultra-III
	 * derivative processor.
	 */
	__यंत्र__ ("rdpr %%ver, %0" : "=r" (ver));
	is_jbus = ((ver >> 32) == __JALAPENO_ID ||
		   (ver >> 32) == __SERRANO_ID);

	__यंत्र__ __अस्थिर__("rdpr %%pstate, %0" : "=r" (pstate));

retry:
	need_more = 0;
	__यंत्र__ __अस्थिर__("wrpr %0, %1, %%pstate\n\t"
			     : : "r" (pstate), "i" (PSTATE_IE));

	/* Setup the dispatch data रेजिस्टरs. */
	__यंत्र__ __अस्थिर__("stxa	%0, [%3] %6\n\t"
			     "stxa	%1, [%4] %6\n\t"
			     "stxa	%2, [%5] %6\n\t"
			     "membar	#Sync\n\t"
			     : /* no outमाला_दो */
			     : "r" (monकरो[0]), "r" (monकरो[1]), "r" (monकरो[2]),
			       "r" (0x40), "r" (0x50), "r" (0x60),
			       "i" (ASI_INTR_W));

	nack_busy_id = 0;
	busy_mask = 0;
	अणु
		पूर्णांक i;

		क्रम (i = 0; i < cnt; i++) अणु
			u64 target, nr;

			nr = cpu_list[i];
			अगर (nr == 0xffff)
				जारी;

			target = (nr << 14) | 0x70;
			अगर (is_jbus) अणु
				busy_mask |= (0x1UL << (nr * 2));
			पूर्ण अन्यथा अणु
				target |= (nack_busy_id << 24);
				busy_mask |= (0x1UL <<
					      (nack_busy_id * 2));
			पूर्ण
			__यंत्र__ __अस्थिर__(
				"stxa	%%g0, [%0] %1\n\t"
				"membar	#Sync\n\t"
				: /* no outमाला_दो */
				: "r" (target), "i" (ASI_INTR_W));
			nack_busy_id++;
			अगर (nack_busy_id == 32) अणु
				need_more = 1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Now, poll क्रम completion. */
	अणु
		u64 dispatch_stat, nack_mask;
		दीर्घ stuck;

		stuck = 100000 * nack_busy_id;
		nack_mask = busy_mask << 1;
		करो अणु
			__यंत्र__ __अस्थिर__("ldxa	[%%g0] %1, %0"
					     : "=r" (dispatch_stat)
					     : "i" (ASI_INTR_DISPATCH_STAT));
			अगर (!(dispatch_stat & (busy_mask | nack_mask))) अणु
				__यंत्र__ __अस्थिर__("wrpr %0, 0x0, %%pstate"
						     : : "r" (pstate));
				अगर (unlikely(need_more)) अणु
					पूर्णांक i, this_cnt = 0;
					क्रम (i = 0; i < cnt; i++) अणु
						अगर (cpu_list[i] == 0xffff)
							जारी;
						cpu_list[i] = 0xffff;
						this_cnt++;
						अगर (this_cnt == 32)
							अवरोध;
					पूर्ण
					जाओ retry;
				पूर्ण
				वापस;
			पूर्ण
			अगर (!--stuck)
				अवरोध;
		पूर्ण जबतक (dispatch_stat & busy_mask);

		__यंत्र__ __अस्थिर__("wrpr %0, 0x0, %%pstate"
				     : : "r" (pstate));

		अगर (dispatch_stat & busy_mask) अणु
			/* Busy bits will not clear, जारी instead
			 * of मुक्तzing up on this cpu.
			 */
			prपूर्णांकk("CPU[%d]: mondo stuckage result[%016llx]\n",
			       smp_processor_id(), dispatch_stat);
		पूर्ण अन्यथा अणु
			पूर्णांक i, this_busy_nack = 0;

			/* Delay some अक्रमom समय with पूर्णांकerrupts enabled
			 * to prevent deadlock.
			 */
			udelay(2 * nack_busy_id);

			/* Clear out the mask bits क्रम cpus which did not
			 * NACK us.
			 */
			क्रम (i = 0; i < cnt; i++) अणु
				u64 check_mask, nr;

				nr = cpu_list[i];
				अगर (nr == 0xffff)
					जारी;

				अगर (is_jbus)
					check_mask = (0x2UL << (2*nr));
				अन्यथा
					check_mask = (0x2UL <<
						      this_busy_nack);
				अगर ((dispatch_stat & check_mask) == 0)
					cpu_list[i] = 0xffff;
				this_busy_nack += 2;
				अगर (this_busy_nack == 64)
					अवरोध;
			पूर्ण

			जाओ retry;
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा	CPU_MONDO_COUNTER(cpuid)	(cpu_monकरो_counter[cpuid])
#घोषणा	MONDO_USEC_WAIT_MIN		2
#घोषणा	MONDO_USEC_WAIT_MAX		100
#घोषणा	MONDO_RETRY_LIMIT		500000

/* Multi-cpu list version.
 *
 * Deliver xcalls to 'cnt' number of cpus in 'cpu_list'.
 * Someबार not all cpus receive the monकरो, requiring us to re-send
 * the monकरो until all cpus have received, or cpus are truly stuck
 * unable to receive monकरो, and we समयout.
 * Occasionally a target cpu stअक्रम is borrowed briefly by hypervisor to
 * perक्रमm guest service, such as PCIe error handling. Consider the
 * service समय, 1 second overall रुको is reasonable क्रम 1 cpu.
 * Here two in-between monकरो check रुको समय are defined: 2 usec क्रम
 * single cpu quick turn around and up to 100usec क्रम large cpu count.
 * Deliver monकरो to large number of cpus could take दीर्घer, we adjusts
 * the retry count as दीर्घ as target cpus are making क्रमward progress.
 */
अटल व्योम hypervisor_xcall_deliver(काष्ठा trap_per_cpu *tb, पूर्णांक cnt)
अणु
	पूर्णांक this_cpu, tot_cpus, prev_sent, i, rem;
	पूर्णांक usec_रुको, retries, tot_retries;
	u16 first_cpu = 0xffff;
	अचिन्हित दीर्घ xc_rcvd = 0;
	अचिन्हित दीर्घ status;
	पूर्णांक ecpuerror_id = 0;
	पूर्णांक enocpu_id = 0;
	u16 *cpu_list;
	u16 cpu;

	this_cpu = smp_processor_id();
	cpu_list = __va(tb->cpu_list_pa);
	usec_रुको = cnt * MONDO_USEC_WAIT_MIN;
	अगर (usec_रुको > MONDO_USEC_WAIT_MAX)
		usec_रुको = MONDO_USEC_WAIT_MAX;
	retries = tot_retries = 0;
	tot_cpus = cnt;
	prev_sent = 0;

	करो अणु
		पूर्णांक n_sent, monकरो_delivered, target_cpu_busy;

		status = sun4v_cpu_monकरो_send(cnt,
					      tb->cpu_list_pa,
					      tb->cpu_monकरो_block_pa);

		/* HV_EOK means all cpus received the xcall, we're करोne.  */
		अगर (likely(status == HV_EOK))
			जाओ xcall_करोne;

		/* If not these non-fatal errors, panic */
		अगर (unlikely((status != HV_EWOULDBLOCK) &&
			(status != HV_ECPUERROR) &&
			(status != HV_ENOCPU)))
			जाओ fatal_errors;

		/* First, see अगर we made any क्रमward progress.
		 *
		 * Go through the cpu_list, count the target cpus that have
		 * received our monकरो (n_sent), and those that did not (rem).
		 * Re-pack cpu_list with the cpus reमुख्य to be retried in the
		 * front - this simplअगरies tracking the truly stalled cpus.
		 *
		 * The hypervisor indicates successful sends by setting
		 * cpu list entries to the value 0xffff.
		 *
		 * EWOULDBLOCK means some target cpus did not receive the
		 * monकरो and retry usually helps.
		 *
		 * ECPUERROR means at least one target cpu is in error state,
		 * it's usually safe to skip the faulty cpu and retry.
		 *
		 * ENOCPU means one of the target cpu करोesn't beदीर्घ to the
		 * करोमुख्य, perhaps offlined which is unexpected, but not
		 * fatal and it's okay to skip the offlined cpu.
		 */
		rem = 0;
		n_sent = 0;
		क्रम (i = 0; i < cnt; i++) अणु
			cpu = cpu_list[i];
			अगर (likely(cpu == 0xffff)) अणु
				n_sent++;
			पूर्ण अन्यथा अगर ((status == HV_ECPUERROR) &&
				(sun4v_cpu_state(cpu) == HV_CPU_STATE_ERROR)) अणु
				ecpuerror_id = cpu + 1;
			पूर्ण अन्यथा अगर (status == HV_ENOCPU && !cpu_online(cpu)) अणु
				enocpu_id = cpu + 1;
			पूर्ण अन्यथा अणु
				cpu_list[rem++] = cpu;
			पूर्ण
		पूर्ण

		/* No cpu reमुख्यed, we're करोne. */
		अगर (rem == 0)
			अवरोध;

		/* Otherwise, update the cpu count क्रम retry. */
		cnt = rem;

		/* Record the overall number of monकरोs received by the
		 * first of the reमुख्यing cpus.
		 */
		अगर (first_cpu != cpu_list[0]) अणु
			first_cpu = cpu_list[0];
			xc_rcvd = CPU_MONDO_COUNTER(first_cpu);
		पूर्ण

		/* Was any monकरो delivered successfully? */
		monकरो_delivered = (n_sent > prev_sent);
		prev_sent = n_sent;

		/* or, was any target cpu busy processing other monकरोs? */
		target_cpu_busy = (xc_rcvd < CPU_MONDO_COUNTER(first_cpu));
		xc_rcvd = CPU_MONDO_COUNTER(first_cpu);

		/* Retry count is क्रम no progress. If we're making progress,
		 * reset the retry count.
		 */
		अगर (likely(monकरो_delivered || target_cpu_busy)) अणु
			tot_retries += retries;
			retries = 0;
		पूर्ण अन्यथा अगर (unlikely(retries > MONDO_RETRY_LIMIT)) अणु
			जाओ fatal_monकरो_समयout;
		पूर्ण

		/* Delay a little bit to let other cpus catch up on
		 * their cpu monकरो queue work.
		 */
		अगर (!monकरो_delivered)
			udelay(usec_रुको);

		retries++;
	पूर्ण जबतक (1);

xcall_करोne:
	अगर (unlikely(ecpuerror_id > 0)) अणु
		pr_crit("CPU[%d]: SUN4V mondo cpu error, target cpu(%d) was in error state\n",
		       this_cpu, ecpuerror_id - 1);
	पूर्ण अन्यथा अगर (unlikely(enocpu_id > 0)) अणु
		pr_crit("CPU[%d]: SUN4V mondo cpu error, target cpu(%d) does not belong to the domain\n",
		       this_cpu, enocpu_id - 1);
	पूर्ण
	वापस;

fatal_errors:
	/* fatal errors include bad alignment, etc */
	pr_crit("CPU[%d]: Args were cnt(%d) cpulist_pa(%lx) mondo_block_pa(%lx)\n",
	       this_cpu, tot_cpus, tb->cpu_list_pa, tb->cpu_monकरो_block_pa);
	panic("Unexpected SUN4V mondo error %lu\n", status);

fatal_monकरो_समयout:
	/* some cpus being non-responsive to the cpu monकरो */
	pr_crit("CPU[%d]: SUN4V mondo timeout, cpu(%d) made no forward progress after %d retries. Total target cpus(%d).\n",
	       this_cpu, first_cpu, (tot_retries + retries), tot_cpus);
	panic("SUN4V mondo timeout panic\n");
पूर्ण

अटल व्योम (*xcall_deliver_impl)(काष्ठा trap_per_cpu *, पूर्णांक);

अटल व्योम xcall_deliver(u64 data0, u64 data1, u64 data2, स्थिर cpumask_t *mask)
अणु
	काष्ठा trap_per_cpu *tb;
	पूर्णांक this_cpu, i, cnt;
	अचिन्हित दीर्घ flags;
	u16 *cpu_list;
	u64 *monकरो;

	/* We have to करो this whole thing with पूर्णांकerrupts fully disabled.
	 * Otherwise अगर we send an xcall from पूर्णांकerrupt context it will
	 * corrupt both our monकरो block and cpu list state.
	 *
	 * One consequence of this is that we cannot use समयout mechanisms
	 * that depend upon पूर्णांकerrupts being delivered locally.  So, क्रम
	 * example, we cannot sample jअगरfies and expect it to advance.
	 *
	 * Fortunately, udelay() uses %stick/%tick so we can use that.
	 */
	local_irq_save(flags);

	this_cpu = smp_processor_id();
	tb = &trap_block[this_cpu];

	monकरो = __va(tb->cpu_monकरो_block_pa);
	monकरो[0] = data0;
	monकरो[1] = data1;
	monकरो[2] = data2;
	wmb();

	cpu_list = __va(tb->cpu_list_pa);

	/* Setup the initial cpu list.  */
	cnt = 0;
	क्रम_each_cpu(i, mask) अणु
		अगर (i == this_cpu || !cpu_online(i))
			जारी;
		cpu_list[cnt++] = i;
	पूर्ण

	अगर (cnt)
		xcall_deliver_impl(tb, cnt);

	local_irq_restore(flags);
पूर्ण

/* Send cross call to all processors mentioned in MASK_P
 * except self.  Really, there are only two हालs currently,
 * "cpu_online_mask" and "mm_cpumask(mm)".
 */
अटल व्योम smp_cross_call_masked(अचिन्हित दीर्घ *func, u32 ctx, u64 data1, u64 data2, स्थिर cpumask_t *mask)
अणु
	u64 data0 = (((u64)ctx)<<32 | (((u64)func) & 0xffffffff));

	xcall_deliver(data0, data1, data2, mask);
पूर्ण

/* Send cross call to all processors except self. */
अटल व्योम smp_cross_call(अचिन्हित दीर्घ *func, u32 ctx, u64 data1, u64 data2)
अणु
	smp_cross_call_masked(func, ctx, data1, data2, cpu_online_mask);
पूर्ण

बाह्य अचिन्हित दीर्घ xcall_sync_tick;

अटल व्योम smp_start_sync_tick_client(पूर्णांक cpu)
अणु
	xcall_deliver((u64) &xcall_sync_tick, 0, 0,
		      cpumask_of(cpu));
पूर्ण

बाह्य अचिन्हित दीर्घ xcall_call_function;

व्योम arch_send_call_function_ipi_mask(स्थिर काष्ठा cpumask *mask)
अणु
	xcall_deliver((u64) &xcall_call_function, 0, 0, mask);
पूर्ण

बाह्य अचिन्हित दीर्घ xcall_call_function_single;

व्योम arch_send_call_function_single_ipi(पूर्णांक cpu)
अणु
	xcall_deliver((u64) &xcall_call_function_single, 0, 0,
		      cpumask_of(cpu));
पूर्ण

व्योम __irq_entry smp_call_function_client(पूर्णांक irq, काष्ठा pt_regs *regs)
अणु
	clear_softपूर्णांक(1 << irq);
	irq_enter();
	generic_smp_call_function_पूर्णांकerrupt();
	irq_निकास();
पूर्ण

व्योम __irq_entry smp_call_function_single_client(पूर्णांक irq, काष्ठा pt_regs *regs)
अणु
	clear_softपूर्णांक(1 << irq);
	irq_enter();
	generic_smp_call_function_single_पूर्णांकerrupt();
	irq_निकास();
पूर्ण

अटल व्योम tsb_sync(व्योम *info)
अणु
	काष्ठा trap_per_cpu *tp = &trap_block[raw_smp_processor_id()];
	काष्ठा mm_काष्ठा *mm = info;

	/* It is not valid to test "current->active_mm == mm" here.
	 *
	 * The value of "current" is not changed atomically with
	 * चयन_mm().  But that's OK, we just need to check the
	 * current cpu's trap block PGD physical address.
	 */
	अगर (tp->pgd_paddr == __pa(mm->pgd))
		tsb_context_चयन(mm);
पूर्ण

व्योम smp_tsb_sync(काष्ठा mm_काष्ठा *mm)
अणु
	smp_call_function_many(mm_cpumask(mm), tsb_sync, mm, 1);
पूर्ण

बाह्य अचिन्हित दीर्घ xcall_flush_tlb_mm;
बाह्य अचिन्हित दीर्घ xcall_flush_tlb_page;
बाह्य अचिन्हित दीर्घ xcall_flush_tlb_kernel_range;
बाह्य अचिन्हित दीर्घ xcall_fetch_glob_regs;
बाह्य अचिन्हित दीर्घ xcall_fetch_glob_pmu;
बाह्य अचिन्हित दीर्घ xcall_fetch_glob_pmu_n4;
बाह्य अचिन्हित दीर्घ xcall_receive_संकेत;
बाह्य अचिन्हित दीर्घ xcall_new_mmu_context_version;
#अगर_घोषित CONFIG_KGDB
बाह्य अचिन्हित दीर्घ xcall_kgdb_capture;
#पूर्ण_अगर

#अगर_घोषित DCACHE_ALIASING_POSSIBLE
बाह्य अचिन्हित दीर्घ xcall_flush_dcache_page_cheetah;
#पूर्ण_अगर
बाह्य अचिन्हित दीर्घ xcall_flush_dcache_page_spitfire;

अटल अंतरभूत व्योम __local_flush_dcache_page(काष्ठा page *page)
अणु
#अगर_घोषित DCACHE_ALIASING_POSSIBLE
	__flush_dcache_page(page_address(page),
			    ((tlb_type == spitfire) &&
			     page_mapping_file(page) != शून्य));
#अन्यथा
	अगर (page_mapping_file(page) != शून्य &&
	    tlb_type == spitfire)
		__flush_icache_page(__pa(page_address(page)));
#पूर्ण_अगर
पूर्ण

व्योम smp_flush_dcache_page_impl(काष्ठा page *page, पूर्णांक cpu)
अणु
	पूर्णांक this_cpu;

	अगर (tlb_type == hypervisor)
		वापस;

#अगर_घोषित CONFIG_DEBUG_DCFLUSH
	atomic_inc(&dcpage_flushes);
#पूर्ण_अगर

	this_cpu = get_cpu();

	अगर (cpu == this_cpu) अणु
		__local_flush_dcache_page(page);
	पूर्ण अन्यथा अगर (cpu_online(cpu)) अणु
		व्योम *pg_addr = page_address(page);
		u64 data0 = 0;

		अगर (tlb_type == spitfire) अणु
			data0 = ((u64)&xcall_flush_dcache_page_spitfire);
			अगर (page_mapping_file(page) != शून्य)
				data0 |= ((u64)1 << 32);
		पूर्ण अन्यथा अगर (tlb_type == cheetah || tlb_type == cheetah_plus) अणु
#अगर_घोषित DCACHE_ALIASING_POSSIBLE
			data0 =	((u64)&xcall_flush_dcache_page_cheetah);
#पूर्ण_अगर
		पूर्ण
		अगर (data0) अणु
			xcall_deliver(data0, __pa(pg_addr),
				      (u64) pg_addr, cpumask_of(cpu));
#अगर_घोषित CONFIG_DEBUG_DCFLUSH
			atomic_inc(&dcpage_flushes_xcall);
#पूर्ण_अगर
		पूर्ण
	पूर्ण

	put_cpu();
पूर्ण

व्योम flush_dcache_page_all(काष्ठा mm_काष्ठा *mm, काष्ठा page *page)
अणु
	व्योम *pg_addr;
	u64 data0;

	अगर (tlb_type == hypervisor)
		वापस;

	preempt_disable();

#अगर_घोषित CONFIG_DEBUG_DCFLUSH
	atomic_inc(&dcpage_flushes);
#पूर्ण_अगर
	data0 = 0;
	pg_addr = page_address(page);
	अगर (tlb_type == spitfire) अणु
		data0 = ((u64)&xcall_flush_dcache_page_spitfire);
		अगर (page_mapping_file(page) != शून्य)
			data0 |= ((u64)1 << 32);
	पूर्ण अन्यथा अगर (tlb_type == cheetah || tlb_type == cheetah_plus) अणु
#अगर_घोषित DCACHE_ALIASING_POSSIBLE
		data0 = ((u64)&xcall_flush_dcache_page_cheetah);
#पूर्ण_अगर
	पूर्ण
	अगर (data0) अणु
		xcall_deliver(data0, __pa(pg_addr),
			      (u64) pg_addr, cpu_online_mask);
#अगर_घोषित CONFIG_DEBUG_DCFLUSH
		atomic_inc(&dcpage_flushes_xcall);
#पूर्ण_अगर
	पूर्ण
	__local_flush_dcache_page(page);

	preempt_enable();
पूर्ण

#अगर_घोषित CONFIG_KGDB
व्योम kgdb_roundup_cpus(व्योम)
अणु
	smp_cross_call(&xcall_kgdb_capture, 0, 0, 0);
पूर्ण
#पूर्ण_अगर

व्योम smp_fetch_global_regs(व्योम)
अणु
	smp_cross_call(&xcall_fetch_glob_regs, 0, 0, 0);
पूर्ण

व्योम smp_fetch_global_pmu(व्योम)
अणु
	अगर (tlb_type == hypervisor &&
	    sun4v_chip_type >= SUN4V_CHIP_NIAGARA4)
		smp_cross_call(&xcall_fetch_glob_pmu_n4, 0, 0, 0);
	अन्यथा
		smp_cross_call(&xcall_fetch_glob_pmu, 0, 0, 0);
पूर्ण

/* We know that the winकरोw frames of the user have been flushed
 * to the stack beक्रमe we get here because all callers of us
 * are flush_tlb_*() routines, and these run after flush_cache_*()
 * which perक्रमms the flushw.
 *
 * mm->cpu_vm_mask is a bit mask of which cpus an address
 * space has (potentially) executed on, this is the heuristic
 * we use to limit cross calls.
 */

/* This currently is only used by the hugetlb arch pre-fault
 * hook on UltraSPARC-III+ and later when changing the pagesize
 * bits of the context रेजिस्टर क्रम an address space.
 */
व्योम smp_flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	u32 ctx = CTX_HWBITS(mm->context);

	get_cpu();

	smp_cross_call_masked(&xcall_flush_tlb_mm,
			      ctx, 0, 0,
			      mm_cpumask(mm));

	__flush_tlb_mm(ctx, SECONDARY_CONTEXT);

	put_cpu();
पूर्ण

काष्ठा tlb_pending_info अणु
	अचिन्हित दीर्घ ctx;
	अचिन्हित दीर्घ nr;
	अचिन्हित दीर्घ *vaddrs;
पूर्ण;

अटल व्योम tlb_pending_func(व्योम *info)
अणु
	काष्ठा tlb_pending_info *t = info;

	__flush_tlb_pending(t->ctx, t->nr, t->vaddrs);
पूर्ण

व्योम smp_flush_tlb_pending(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ nr, अचिन्हित दीर्घ *vaddrs)
अणु
	u32 ctx = CTX_HWBITS(mm->context);
	काष्ठा tlb_pending_info info;

	get_cpu();

	info.ctx = ctx;
	info.nr = nr;
	info.vaddrs = vaddrs;

	smp_call_function_many(mm_cpumask(mm), tlb_pending_func,
			       &info, 1);

	__flush_tlb_pending(ctx, nr, vaddrs);

	put_cpu();
पूर्ण

व्योम smp_flush_tlb_page(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vaddr)
अणु
	अचिन्हित दीर्घ context = CTX_HWBITS(mm->context);

	get_cpu();

	smp_cross_call_masked(&xcall_flush_tlb_page,
			      context, vaddr, 0,
			      mm_cpumask(mm));

	__flush_tlb_page(context, vaddr);

	put_cpu();
पूर्ण

व्योम smp_flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	start &= PAGE_MASK;
	end    = PAGE_ALIGN(end);
	अगर (start != end) अणु
		smp_cross_call(&xcall_flush_tlb_kernel_range,
			       0, start, end);

		__flush_tlb_kernel_range(start, end);
	पूर्ण
पूर्ण

/* CPU capture. */
/* #घोषणा CAPTURE_DEBUG */
बाह्य अचिन्हित दीर्घ xcall_capture;

अटल atomic_t smp_capture_depth = ATOMIC_INIT(0);
अटल atomic_t smp_capture_registry = ATOMIC_INIT(0);
अटल अचिन्हित दीर्घ penguins_are_करोing_समय;

व्योम smp_capture(व्योम)
अणु
	पूर्णांक result = atomic_add_वापस(1, &smp_capture_depth);

	अगर (result == 1) अणु
		पूर्णांक ncpus = num_online_cpus();

#अगर_घोषित CAPTURE_DEBUG
		prपूर्णांकk("CPU[%d]: Sending penguins to jail...",
		       smp_processor_id());
#पूर्ण_अगर
		penguins_are_करोing_समय = 1;
		atomic_inc(&smp_capture_registry);
		smp_cross_call(&xcall_capture, 0, 0, 0);
		जबतक (atomic_पढ़ो(&smp_capture_registry) != ncpus)
			rmb();
#अगर_घोषित CAPTURE_DEBUG
		prपूर्णांकk("done\n");
#पूर्ण_अगर
	पूर्ण
पूर्ण

व्योम smp_release(व्योम)
अणु
	अगर (atomic_dec_and_test(&smp_capture_depth)) अणु
#अगर_घोषित CAPTURE_DEBUG
		prपूर्णांकk("CPU[%d]: Giving pardon to "
		       "imprisoned penguins\n",
		       smp_processor_id());
#पूर्ण_अगर
		penguins_are_करोing_समय = 0;
		membar_safe("#StoreLoad");
		atomic_dec(&smp_capture_registry);
	पूर्ण
पूर्ण

/* Imprisoned penguins run with %pil == PIL_NORMAL_MAX, but PSTATE_IE
 * set, so they can service tlb flush xcalls...
 */
बाह्य व्योम prom_world(पूर्णांक);

व्योम __irq_entry smp_penguin_jailcell(पूर्णांक irq, काष्ठा pt_regs *regs)
अणु
	clear_softपूर्णांक(1 << irq);

	preempt_disable();

	__यंत्र__ __अस्थिर__("flushw");
	prom_world(1);
	atomic_inc(&smp_capture_registry);
	membar_safe("#StoreLoad");
	जबतक (penguins_are_करोing_समय)
		rmb();
	atomic_dec(&smp_capture_registry);
	prom_world(0);

	preempt_enable();
पूर्ण

/* /proc/profile ग_लिखोs can call this, करोn't __init it please. */
पूर्णांक setup_profiling_समयr(अचिन्हित पूर्णांक multiplier)
अणु
	वापस -EINVAL;
पूर्ण

व्योम __init smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
पूर्ण

व्योम smp_prepare_boot_cpu(व्योम)
अणु
पूर्ण

व्योम __init smp_setup_processor_id(व्योम)
अणु
	अगर (tlb_type == spitfire)
		xcall_deliver_impl = spitfire_xcall_deliver;
	अन्यथा अगर (tlb_type == cheetah || tlb_type == cheetah_plus)
		xcall_deliver_impl = cheetah_xcall_deliver;
	अन्यथा
		xcall_deliver_impl = hypervisor_xcall_deliver;
पूर्ण

व्योम __init smp_fill_in_cpu_possible_map(व्योम)
अणु
	पूर्णांक possible_cpus = num_possible_cpus();
	पूर्णांक i;

	अगर (possible_cpus > nr_cpu_ids)
		possible_cpus = nr_cpu_ids;

	क्रम (i = 0; i < possible_cpus; i++)
		set_cpu_possible(i, true);
	क्रम (; i < NR_CPUS; i++)
		set_cpu_possible(i, false);
पूर्ण

व्योम smp_fill_in_sib_core_maps(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	क्रम_each_present_cpu(i) अणु
		अचिन्हित पूर्णांक j;

		cpumask_clear(&cpu_core_map[i]);
		अगर (cpu_data(i).core_id == 0) अणु
			cpumask_set_cpu(i, &cpu_core_map[i]);
			जारी;
		पूर्ण

		क्रम_each_present_cpu(j) अणु
			अगर (cpu_data(i).core_id ==
			    cpu_data(j).core_id)
				cpumask_set_cpu(j, &cpu_core_map[i]);
		पूर्ण
	पूर्ण

	क्रम_each_present_cpu(i)  अणु
		अचिन्हित पूर्णांक j;

		क्रम_each_present_cpu(j)  अणु
			अगर (cpu_data(i).max_cache_id ==
			    cpu_data(j).max_cache_id)
				cpumask_set_cpu(j, &cpu_core_sib_cache_map[i]);

			अगर (cpu_data(i).sock_id == cpu_data(j).sock_id)
				cpumask_set_cpu(j, &cpu_core_sib_map[i]);
		पूर्ण
	पूर्ण

	क्रम_each_present_cpu(i) अणु
		अचिन्हित पूर्णांक j;

		cpumask_clear(&per_cpu(cpu_sibling_map, i));
		अगर (cpu_data(i).proc_id == -1) अणु
			cpumask_set_cpu(i, &per_cpu(cpu_sibling_map, i));
			जारी;
		पूर्ण

		क्रम_each_present_cpu(j) अणु
			अगर (cpu_data(i).proc_id ==
			    cpu_data(j).proc_id)
				cpumask_set_cpu(j, &per_cpu(cpu_sibling_map, i));
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक __cpu_up(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *tidle)
अणु
	पूर्णांक ret = smp_boot_one_cpu(cpu, tidle);

	अगर (!ret) अणु
		cpumask_set_cpu(cpu, &smp_commenced_mask);
		जबतक (!cpu_online(cpu))
			mb();
		अगर (!cpu_online(cpu)) अणु
			ret = -ENODEV;
		पूर्ण अन्यथा अणु
			/* On SUN4V, ग_लिखोs to %tick and %stick are
			 * not allowed.
			 */
			अगर (tlb_type != hypervisor)
				smp_synchronize_one_tick(cpu);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
व्योम cpu_play_dead(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();
	अचिन्हित दीर्घ pstate;

	idle_task_निकास();

	अगर (tlb_type == hypervisor) अणु
		काष्ठा trap_per_cpu *tb = &trap_block[cpu];

		sun4v_cpu_qconf(HV_CPU_QUEUE_CPU_MONDO,
				tb->cpu_monकरो_pa, 0);
		sun4v_cpu_qconf(HV_CPU_QUEUE_DEVICE_MONDO,
				tb->dev_monकरो_pa, 0);
		sun4v_cpu_qconf(HV_CPU_QUEUE_RES_ERROR,
				tb->resum_monकरो_pa, 0);
		sun4v_cpu_qconf(HV_CPU_QUEUE_NONRES_ERROR,
				tb->nonresum_monकरो_pa, 0);
	पूर्ण

	cpumask_clear_cpu(cpu, &smp_commenced_mask);
	membar_safe("#Sync");

	local_irq_disable();

	__यंत्र__ __अस्थिर__(
		"rdpr	%%pstate, %0\n\t"
		"wrpr	%0, %1, %%pstate"
		: "=r" (pstate)
		: "i" (PSTATE_IE));

	जबतक (1)
		barrier();
पूर्ण

पूर्णांक __cpu_disable(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();
	cpuinfo_sparc *c;
	पूर्णांक i;

	क्रम_each_cpu(i, &cpu_core_map[cpu])
		cpumask_clear_cpu(cpu, &cpu_core_map[i]);
	cpumask_clear(&cpu_core_map[cpu]);

	क्रम_each_cpu(i, &per_cpu(cpu_sibling_map, cpu))
		cpumask_clear_cpu(cpu, &per_cpu(cpu_sibling_map, i));
	cpumask_clear(&per_cpu(cpu_sibling_map, cpu));

	c = &cpu_data(cpu);

	c->core_id = 0;
	c->proc_id = -1;

	smp_wmb();

	/* Make sure no पूर्णांकerrupts poपूर्णांक to this cpu.  */
	fixup_irqs();

	local_irq_enable();
	mdelay(1);
	local_irq_disable();

	set_cpu_online(cpu, false);

	cpu_map_rebuild();

	वापस 0;
पूर्ण

व्योम __cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 100; i++) अणु
		smp_rmb();
		अगर (!cpumask_test_cpu(cpu, &smp_commenced_mask))
			अवरोध;
		msleep(100);
	पूर्ण
	अगर (cpumask_test_cpu(cpu, &smp_commenced_mask)) अणु
		prपूर्णांकk(KERN_ERR "CPU %u didn't die...\n", cpu);
	पूर्ण अन्यथा अणु
#अगर defined(CONFIG_SUN_LDOMS)
		अचिन्हित दीर्घ hv_err;
		पूर्णांक limit = 100;

		करो अणु
			hv_err = sun4v_cpu_stop(cpu);
			अगर (hv_err == HV_EOK) अणु
				set_cpu_present(cpu, false);
				अवरोध;
			पूर्ण
		पूर्ण जबतक (--limit > 0);
		अगर (limit <= 0) अणु
			prपूर्णांकk(KERN_ERR "sun4v_cpu_stop() fails err=%lu\n",
			       hv_err);
		पूर्ण
#पूर्ण_अगर
	पूर्ण
पूर्ण
#पूर्ण_अगर

व्योम __init smp_cpus_करोne(अचिन्हित पूर्णांक max_cpus)
अणु
पूर्ण

अटल व्योम send_cpu_ipi(पूर्णांक cpu)
अणु
	xcall_deliver((u64) &xcall_receive_संकेत,
			0, 0, cpumask_of(cpu));
पूर्ण

व्योम scheduler_poke(व्योम)
अणु
	अगर (!cpu_poke)
		वापस;

	अगर (!__this_cpu_पढ़ो(poke))
		वापस;

	__this_cpu_ग_लिखो(poke, false);
	set_softपूर्णांक(1 << PIL_SMP_RECEIVE_SIGNAL);
पूर्ण

अटल अचिन्हित दीर्घ send_cpu_poke(पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ hv_err;

	per_cpu(poke, cpu) = true;
	hv_err = sun4v_cpu_poke(cpu);
	अगर (hv_err != HV_EOK) अणु
		per_cpu(poke, cpu) = false;
		pr_err_ratelimited("%s: sun4v_cpu_poke() fails err=%lu\n",
				    __func__, hv_err);
	पूर्ण

	वापस hv_err;
पूर्ण

व्योम smp_send_reschedule(पूर्णांक cpu)
अणु
	अगर (cpu == smp_processor_id()) अणु
		WARN_ON_ONCE(preemptible());
		set_softपूर्णांक(1 << PIL_SMP_RECEIVE_SIGNAL);
		वापस;
	पूर्ण

	/* Use cpu poke to resume idle cpu अगर supported. */
	अगर (cpu_poke && idle_cpu(cpu)) अणु
		अचिन्हित दीर्घ ret;

		ret = send_cpu_poke(cpu);
		अगर (ret == HV_EOK)
			वापस;
	पूर्ण

	/* Use IPI in following हालs:
	 * - cpu poke not supported
	 * - cpu not idle
	 * - send_cpu_poke() वापसs with error
	 */
	send_cpu_ipi(cpu);
पूर्ण

व्योम smp_init_cpu_poke(व्योम)
अणु
	अचिन्हित दीर्घ major;
	अचिन्हित दीर्घ minor;
	पूर्णांक ret;

	अगर (tlb_type != hypervisor)
		वापस;

	ret = sun4v_hvapi_get(HV_GRP_CORE, &major, &minor);
	अगर (ret) अणु
		pr_debug("HV_GRP_CORE is not registered\n");
		वापस;
	पूर्ण

	अगर (major == 1 && minor >= 6) अणु
		/* CPU POKE is रेजिस्टरed. */
		cpu_poke = true;
		वापस;
	पूर्ण

	pr_debug("CPU_POKE not supported\n");
पूर्ण

व्योम __irq_entry smp_receive_संकेत_client(पूर्णांक irq, काष्ठा pt_regs *regs)
अणु
	clear_softपूर्णांक(1 << irq);
	scheduler_ipi();
पूर्ण

अटल व्योम stop_this_cpu(व्योम *dummy)
अणु
	set_cpu_online(smp_processor_id(), false);
	prom_stopself();
पूर्ण

व्योम smp_send_stop(व्योम)
अणु
	पूर्णांक cpu;

	अगर (tlb_type == hypervisor) अणु
		पूर्णांक this_cpu = smp_processor_id();
#अगर_घोषित CONFIG_SERIAL_SUNHV
		sunhv_migrate_hvcons_irq(this_cpu);
#पूर्ण_अगर
		क्रम_each_online_cpu(cpu) अणु
			अगर (cpu == this_cpu)
				जारी;

			set_cpu_online(cpu, false);
#अगर_घोषित CONFIG_SUN_LDOMS
			अगर (lकरोm_करोमुख्यing_enabled) अणु
				अचिन्हित दीर्घ hv_err;
				hv_err = sun4v_cpu_stop(cpu);
				अगर (hv_err)
					prपूर्णांकk(KERN_ERR "sun4v_cpu_stop() "
					       "failed err=%lu\n", hv_err);
			पूर्ण अन्यथा
#पूर्ण_अगर
				prom_stopcpu_cpuid(cpu);
		पूर्ण
	पूर्ण अन्यथा
		smp_call_function(stop_this_cpu, शून्य, 0);
पूर्ण

/**
 * pcpu_alloc_booपंचांगem - NUMA मित्रly alloc_booपंचांगem wrapper क्रम percpu
 * @cpu: cpu to allocate क्रम
 * @size: size allocation in bytes
 * @align: alignment
 *
 * Allocate @size bytes aligned at @align क्रम cpu @cpu.  This wrapper
 * करोes the right thing क्रम NUMA regardless of the current
 * configuration.
 *
 * RETURNS:
 * Poपूर्णांकer to the allocated area on success, शून्य on failure.
 */
अटल व्योम * __init pcpu_alloc_booपंचांगem(अचिन्हित पूर्णांक cpu, माप_प्रकार size,
					माप_प्रकार align)
अणु
	स्थिर अचिन्हित दीर्घ goal = __pa(MAX_DMA_ADDRESS);
#अगर_घोषित CONFIG_NEED_MULTIPLE_NODES
	पूर्णांक node = cpu_to_node(cpu);
	व्योम *ptr;

	अगर (!node_online(node) || !NODE_DATA(node)) अणु
		ptr = memblock_alloc_from(size, align, goal);
		pr_info("cpu %d has no node %d or node-local memory\n",
			cpu, node);
		pr_debug("per cpu data for cpu%d %lu bytes at %016lx\n",
			 cpu, size, __pa(ptr));
	पूर्ण अन्यथा अणु
		ptr = memblock_alloc_try_nid(size, align, goal,
					     MEMBLOCK_ALLOC_ACCESSIBLE, node);
		pr_debug("per cpu data for cpu%d %lu bytes on node%d at "
			 "%016lx\n", cpu, size, node, __pa(ptr));
	पूर्ण
	वापस ptr;
#अन्यथा
	वापस memblock_alloc_from(size, align, goal);
#पूर्ण_अगर
पूर्ण

अटल व्योम __init pcpu_मुक्त_booपंचांगem(व्योम *ptr, माप_प्रकार size)
अणु
	memblock_मुक्त(__pa(ptr), size);
पूर्ण

अटल पूर्णांक __init pcpu_cpu_distance(अचिन्हित पूर्णांक from, अचिन्हित पूर्णांक to)
अणु
	अगर (cpu_to_node(from) == cpu_to_node(to))
		वापस LOCAL_DISTANCE;
	अन्यथा
		वापस REMOTE_DISTANCE;
पूर्ण

अटल व्योम __init pcpu_populate_pte(अचिन्हित दीर्घ addr)
अणु
	pgd_t *pgd = pgd_offset_k(addr);
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;

	अगर (pgd_none(*pgd)) अणु
		pud_t *new;

		new = memblock_alloc_from(PAGE_SIZE, PAGE_SIZE, PAGE_SIZE);
		अगर (!new)
			जाओ err_alloc;
		pgd_populate(&init_mm, pgd, new);
	पूर्ण

	p4d = p4d_offset(pgd, addr);
	अगर (p4d_none(*p4d)) अणु
		pud_t *new;

		new = memblock_alloc_from(PAGE_SIZE, PAGE_SIZE, PAGE_SIZE);
		अगर (!new)
			जाओ err_alloc;
		p4d_populate(&init_mm, p4d, new);
	पूर्ण

	pud = pud_offset(p4d, addr);
	अगर (pud_none(*pud)) अणु
		pmd_t *new;

		new = memblock_alloc_from(PAGE_SIZE, PAGE_SIZE, PAGE_SIZE);
		अगर (!new)
			जाओ err_alloc;
		pud_populate(&init_mm, pud, new);
	पूर्ण

	pmd = pmd_offset(pud, addr);
	अगर (!pmd_present(*pmd)) अणु
		pte_t *new;

		new = memblock_alloc_from(PAGE_SIZE, PAGE_SIZE, PAGE_SIZE);
		अगर (!new)
			जाओ err_alloc;
		pmd_populate_kernel(&init_mm, pmd, new);
	पूर्ण

	वापस;

err_alloc:
	panic("%s: Failed to allocate %lu bytes align=%lx from=%lx\n",
	      __func__, PAGE_SIZE, PAGE_SIZE, PAGE_SIZE);
पूर्ण

व्योम __init setup_per_cpu_areas(व्योम)
अणु
	अचिन्हित दीर्घ delta;
	अचिन्हित पूर्णांक cpu;
	पूर्णांक rc = -EINVAL;

	अगर (pcpu_chosen_fc != PCPU_FC_PAGE) अणु
		rc = pcpu_embed_first_chunk(PERCPU_MODULE_RESERVE,
					    PERCPU_DYNAMIC_RESERVE, 4 << 20,
					    pcpu_cpu_distance,
					    pcpu_alloc_booपंचांगem,
					    pcpu_मुक्त_booपंचांगem);
		अगर (rc)
			pr_warn("PERCPU: %s allocator failed (%d), "
				"falling back to page size\n",
				pcpu_fc_names[pcpu_chosen_fc], rc);
	पूर्ण
	अगर (rc < 0)
		rc = pcpu_page_first_chunk(PERCPU_MODULE_RESERVE,
					   pcpu_alloc_booपंचांगem,
					   pcpu_मुक्त_booपंचांगem,
					   pcpu_populate_pte);
	अगर (rc < 0)
		panic("cannot initialize percpu area (err=%d)", rc);

	delta = (अचिन्हित दीर्घ)pcpu_base_addr - (अचिन्हित दीर्घ)__per_cpu_start;
	क्रम_each_possible_cpu(cpu)
		__per_cpu_offset(cpu) = delta + pcpu_unit_offsets[cpu];

	/* Setup %g5 क्रम the boot cpu.  */
	__local_per_cpu_offset = __per_cpu_offset(smp_processor_id());

	of_fill_in_cpu_data();
	अगर (tlb_type == hypervisor)
		mdesc_fill_in_cpu_data(cpu_all_mask);
पूर्ण
