<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/smp.c
 *
 *      2001-07-09 Phil Ezolt (Phillip.Ezolt@compaq.com)
 *            Renamed modअगरied smp_call_function to smp_call_function_on_cpu()
 *            Created an function that conक्रमms to the old calling convention
 *            of smp_call_function().
 *
 *            This is helpful क्रम DCPI.
 *
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/module.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/mm.h>
#समावेश <linux/err.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/smp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/irq.h>
#समावेश <linux/cache.h>
#समावेश <linux/profile.h>
#समावेश <linux/bitops.h>
#समावेश <linux/cpu.h>

#समावेश <यंत्र/hwrpb.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <linux/atomic.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश "proto.h"
#समावेश "irq_impl.h"


#घोषणा DEBUG_SMP 0
#अगर DEBUG_SMP
#घोषणा DBGS(args)	prपूर्णांकk args
#अन्यथा
#घोषणा DBGS(args)
#पूर्ण_अगर

/* A collection of per-processor data.  */
काष्ठा cpuinfo_alpha cpu_data[NR_CPUS];
EXPORT_SYMBOL(cpu_data);

/* A collection of single bit ipi messages.  */
अटल काष्ठा अणु
	अचिन्हित दीर्घ bits ____cacheline_aligned;
पूर्ण ipi_data[NR_CPUS] __cacheline_aligned;

क्रमागत ipi_message_type अणु
	IPI_RESCHEDULE,
	IPI_CALL_FUNC,
	IPI_CPU_STOP,
पूर्ण;

/* Set to a secondary's cpuid when it comes online.  */
अटल पूर्णांक smp_secondary_alive = 0;

पूर्णांक smp_num_probed;		/* Internal processor count */
पूर्णांक smp_num_cpus = 1;		/* Number that came online.  */
EXPORT_SYMBOL(smp_num_cpus);

/*
 * Called by both boot and secondaries to move global data पूर्णांकo
 *  per-processor storage.
 */
अटल अंतरभूत व्योम __init
smp_store_cpu_info(पूर्णांक cpuid)
अणु
	cpu_data[cpuid].loops_per_jअगरfy = loops_per_jअगरfy;
	cpu_data[cpuid].last_asn = ASN_FIRST_VERSION;
	cpu_data[cpuid].need_new_asn = 0;
	cpu_data[cpuid].asn_lock = 0;
पूर्ण

/*
 * Ideally sets up per-cpu profiling hooks.  Doesn't करो much now...
 */
अटल अंतरभूत व्योम __init
smp_setup_percpu_समयr(पूर्णांक cpuid)
अणु
	cpu_data[cpuid].prof_counter = 1;
	cpu_data[cpuid].prof_multiplier = 1;
पूर्ण

अटल व्योम __init
रुको_boot_cpu_to_stop(पूर्णांक cpuid)
अणु
	अचिन्हित दीर्घ stop = jअगरfies + 10*HZ;

	जबतक (समय_beक्रमe(jअगरfies, stop)) अणु
	        अगर (!smp_secondary_alive)
			वापस;
		barrier();
	पूर्ण

	prपूर्णांकk("wait_boot_cpu_to_stop: FAILED on CPU %d, hanging now\n", cpuid);
	क्रम (;;)
		barrier();
पूर्ण

/*
 * Where secondaries begin a lअगरe of C.
 */
व्योम __init
smp_callin(व्योम)
अणु
	पूर्णांक cpuid = hard_smp_processor_id();

	अगर (cpu_online(cpuid)) अणु
		prपूर्णांकk("??, cpu 0x%x already present??\n", cpuid);
		BUG();
	पूर्ण
	set_cpu_online(cpuid, true);

	/* Turn on machine checks.  */
	wrmces(7);

	/* Set trap vectors.  */
	trap_init();

	/* Set पूर्णांकerrupt vector.  */
	wrent(entInt, 0);

	/* Get our local ticker going. */
	smp_setup_percpu_समयr(cpuid);
	init_घड़ीevent();

	/* Call platक्रमm-specअगरic callin, अगर specअगरied */
	अगर (alpha_mv.smp_callin)
		alpha_mv.smp_callin();

	/* All kernel thपढ़ोs share the same mm context.  */
	mmgrab(&init_mm);
	current->active_mm = &init_mm;

	/* inक्रमm the notअगरiers about the new cpu */
	notअगरy_cpu_starting(cpuid);

	/* Must have completely accurate bogos.  */
	local_irq_enable();

	/* Wait boot CPU to stop with irq enabled beक्रमe running
	   calibrate_delay. */
	रुको_boot_cpu_to_stop(cpuid);
	mb();
	calibrate_delay();

	smp_store_cpu_info(cpuid);
	/* Allow master to जारी only after we written loops_per_jअगरfy.  */
	wmb();
	smp_secondary_alive = 1;

	DBGS(("smp_callin: commencing CPU %d current %p active_mm %p\n",
	      cpuid, current, current->active_mm));

	preempt_disable();
	cpu_startup_entry(CPUHP_AP_ONLINE_IDLE);
पूर्ण

/* Wait until hwrpb->txrdy is clear क्रम cpu.  Return -1 on समयout.  */
अटल पूर्णांक
रुको_क्रम_txrdy (अचिन्हित दीर्घ cpumask)
अणु
	अचिन्हित दीर्घ समयout;

	अगर (!(hwrpb->txrdy & cpumask))
		वापस 0;

	समयout = jअगरfies + 10*HZ;
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		अगर (!(hwrpb->txrdy & cpumask))
			वापस 0;
		udelay(10);
		barrier();
	पूर्ण

	वापस -1;
पूर्ण

/*
 * Send a message to a secondary's console.  "START" is one such
 * पूर्णांकeresting message.  ;-)
 */
अटल व्योम
send_secondary_console_msg(अक्षर *str, पूर्णांक cpuid)
अणु
	काष्ठा percpu_काष्ठा *cpu;
	रेजिस्टर अक्षर *cp1, *cp2;
	अचिन्हित दीर्घ cpumask;
	माप_प्रकार len;

	cpu = (काष्ठा percpu_काष्ठा *)
		((अक्षर*)hwrpb
		 + hwrpb->processor_offset
		 + cpuid * hwrpb->processor_size);

	cpumask = (1UL << cpuid);
	अगर (रुको_क्रम_txrdy(cpumask))
		जाओ समयout;

	cp2 = str;
	len = म_माप(cp2);
	*(अचिन्हित पूर्णांक *)&cpu->ipc_buffer[0] = len;
	cp1 = (अक्षर *) &cpu->ipc_buffer[1];
	स_नकल(cp1, cp2, len);

	/* atomic test and set */
	wmb();
	set_bit(cpuid, &hwrpb->rxrdy);

	अगर (रुको_क्रम_txrdy(cpumask))
		जाओ समयout;
	वापस;

 समयout:
	prपूर्णांकk("Processor %x not ready\n", cpuid);
पूर्ण

/*
 * A secondary console wants to send a message.  Receive it.
 */
अटल व्योम
recv_secondary_console_msg(व्योम)
अणु
	पूर्णांक mycpu, i, cnt;
	अचिन्हित दीर्घ txrdy = hwrpb->txrdy;
	अक्षर *cp1, *cp2, buf[80];
	काष्ठा percpu_काष्ठा *cpu;

	DBGS(("recv_secondary_console_msg: TXRDY 0x%lx.\n", txrdy));

	mycpu = hard_smp_processor_id();

	क्रम (i = 0; i < NR_CPUS; i++) अणु
		अगर (!(txrdy & (1UL << i)))
			जारी;

		DBGS(("recv_secondary_console_msg: "
		      "TXRDY contains CPU %d.\n", i));

		cpu = (काष्ठा percpu_काष्ठा *)
		  ((अक्षर*)hwrpb
		   + hwrpb->processor_offset
		   + i * hwrpb->processor_size);

 		DBGS(("recv_secondary_console_msg: on %d from %d"
		      " HALT_REASON 0x%lx FLAGS 0x%lx\n",
		      mycpu, i, cpu->halt_reason, cpu->flags));

		cnt = cpu->ipc_buffer[0] >> 32;
		अगर (cnt <= 0 || cnt >= 80)
			म_नकल(buf, "<<< BOGUS MSG >>>");
		अन्यथा अणु
			cp1 = (अक्षर *) &cpu->ipc_buffer[1];
			cp2 = buf;
			स_नकल(cp2, cp1, cnt);
			cp2[cnt] = '\0';
			
			जबतक ((cp2 = म_अक्षर(cp2, '\r')) != 0) अणु
				*cp2 = ' ';
				अगर (cp2[1] == '\n')
					cp2[1] = ' ';
			पूर्ण
		पूर्ण

		DBGS((KERN_INFO "recv_secondary_console_msg: on %d "
		      "message is '%s'\n", mycpu, buf));
	पूर्ण

	hwrpb->txrdy = 0;
पूर्ण

/*
 * Convince the console to have a secondary cpu begin execution.
 */
अटल पूर्णांक
secondary_cpu_start(पूर्णांक cpuid, काष्ठा task_काष्ठा *idle)
अणु
	काष्ठा percpu_काष्ठा *cpu;
	काष्ठा pcb_काष्ठा *hwpcb, *ipcb;
	अचिन्हित दीर्घ समयout;
	  
	cpu = (काष्ठा percpu_काष्ठा *)
		((अक्षर*)hwrpb
		 + hwrpb->processor_offset
		 + cpuid * hwrpb->processor_size);
	hwpcb = (काष्ठा pcb_काष्ठा *) cpu->hwpcb;
	ipcb = &task_thपढ़ो_info(idle)->pcb;

	/* Initialize the CPU's HWPCB to something just good enough क्रम
	   us to get started.  Immediately after starting, we'll swpctx
	   to the target idle task's pcb.  Reuse the stack in the mean
	   समय.  Precalculate the target PCBB.  */
	hwpcb->ksp = (अचिन्हित दीर्घ)ipcb + माप(जोड़ thपढ़ो_जोड़) - 16;
	hwpcb->usp = 0;
	hwpcb->ptbr = ipcb->ptbr;
	hwpcb->pcc = 0;
	hwpcb->asn = 0;
	hwpcb->unique = virt_to_phys(ipcb);
	hwpcb->flags = ipcb->flags;
	hwpcb->res1 = hwpcb->res2 = 0;

#अगर 0
	DBGS(("KSP 0x%lx PTBR 0x%lx VPTBR 0x%lx UNIQUE 0x%lx\n",
	      hwpcb->ksp, hwpcb->ptbr, hwrpb->vptb, hwpcb->unique));
#पूर्ण_अगर
	DBGS(("Starting secondary cpu %d: state 0x%lx pal_flags 0x%lx\n",
	      cpuid, idle->state, ipcb->flags));

	/* Setup HWRPB fields that SRM uses to activate secondary CPU */
	hwrpb->CPU_restart = __smp_callin;
	hwrpb->CPU_restart_data = (अचिन्हित दीर्घ) __smp_callin;

	/* Recalculate and update the HWRPB checksum */
	hwrpb_update_checksum(hwrpb);

	/*
	 * Send a "start" command to the specअगरied processor.
	 */

	/* SRM III 3.4.1.3 */
	cpu->flags |= 0x22;	/* turn on Context Valid and Restart Capable */
	cpu->flags &= ~1;	/* turn off Bootstrap In Progress */
	wmb();

	send_secondary_console_msg("START\r\n", cpuid);

	/* Wait 10 seconds क्रम an ACK from the console.  */
	समयout = jअगरfies + 10*HZ;
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		अगर (cpu->flags & 1)
			जाओ started;
		udelay(10);
		barrier();
	पूर्ण
	prपूर्णांकk(KERN_ERR "SMP: Processor %d failed to start.\n", cpuid);
	वापस -1;

 started:
	DBGS(("secondary_cpu_start: SUCCESS for CPU %d!!!\n", cpuid));
	वापस 0;
पूर्ण

/*
 * Bring one cpu online.
 */
अटल पूर्णांक
smp_boot_one_cpu(पूर्णांक cpuid, काष्ठा task_काष्ठा *idle)
अणु
	अचिन्हित दीर्घ समयout;

	/* Signal the secondary to रुको a moment.  */
	smp_secondary_alive = -1;

	/* Whirrr, whirrr, whirrrrrrrrr... */
	अगर (secondary_cpu_start(cpuid, idle))
		वापस -1;

	/* Notअगरy the secondary CPU it can run calibrate_delay.  */
	mb();
	smp_secondary_alive = 0;

	/* We've been acked by the console; रुको one second क्रम
	   the task to start up क्रम real.  */
	समयout = jअगरfies + 1*HZ;
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		अगर (smp_secondary_alive == 1)
			जाओ alive;
		udelay(10);
		barrier();
	पूर्ण

	/* We failed to boot the CPU.  */

	prपूर्णांकk(KERN_ERR "SMP: Processor %d is stuck.\n", cpuid);
	वापस -1;

 alive:
	/* Another "Red Snapper". */
	वापस 0;
पूर्ण

/*
 * Called from setup_arch.  Detect an SMP प्रणाली and which processors
 * are present.
 */
व्योम __init
setup_smp(व्योम)
अणु
	काष्ठा percpu_काष्ठा *cpubase, *cpu;
	अचिन्हित दीर्घ i;

	अगर (boot_cpuid != 0) अणु
		prपूर्णांकk(KERN_WARNING "SMP: Booting off cpu %d instead of 0?\n",
		       boot_cpuid);
	पूर्ण

	अगर (hwrpb->nr_processors > 1) अणु
		पूर्णांक boot_cpu_palrev;

		DBGS(("setup_smp: nr_processors %ld\n",
		      hwrpb->nr_processors));

		cpubase = (काष्ठा percpu_काष्ठा *)
			((अक्षर*)hwrpb + hwrpb->processor_offset);
		boot_cpu_palrev = cpubase->pal_revision;

		क्रम (i = 0; i < hwrpb->nr_processors; i++) अणु
			cpu = (काष्ठा percpu_काष्ठा *)
				((अक्षर *)cpubase + i*hwrpb->processor_size);
			अगर ((cpu->flags & 0x1cc) == 0x1cc) अणु
				smp_num_probed++;
				set_cpu_possible(i, true);
				set_cpu_present(i, true);
				cpu->pal_revision = boot_cpu_palrev;
			पूर्ण

			DBGS(("setup_smp: CPU %d: flags 0x%lx type 0x%lx\n",
			      i, cpu->flags, cpu->type));
			DBGS(("setup_smp: CPU %d: PAL rev 0x%lx\n",
			      i, cpu->pal_revision));
		पूर्ण
	पूर्ण अन्यथा अणु
		smp_num_probed = 1;
	पूर्ण

	prपूर्णांकk(KERN_INFO "SMP: %d CPUs probed -- cpu_present_mask = %lx\n",
	       smp_num_probed, cpumask_bits(cpu_present_mask)[0]);
पूर्ण

/*
 * Called by smp_init prepare the secondaries
 */
व्योम __init
smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	/* Take care of some initial bookkeeping.  */
	स_रखो(ipi_data, 0, माप(ipi_data));

	current_thपढ़ो_info()->cpu = boot_cpuid;

	smp_store_cpu_info(boot_cpuid);
	smp_setup_percpu_समयr(boot_cpuid);

	/* Nothing to करो on a UP box, or when told not to.  */
	अगर (smp_num_probed == 1 || max_cpus == 0) अणु
		init_cpu_possible(cpumask_of(boot_cpuid));
		init_cpu_present(cpumask_of(boot_cpuid));
		prपूर्णांकk(KERN_INFO "SMP mode deactivated.\n");
		वापस;
	पूर्ण

	prपूर्णांकk(KERN_INFO "SMP starting up secondaries.\n");

	smp_num_cpus = smp_num_probed;
पूर्ण

व्योम
smp_prepare_boot_cpu(व्योम)
अणु
पूर्ण

पूर्णांक
__cpu_up(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *tidle)
अणु
	smp_boot_one_cpu(cpu, tidle);

	वापस cpu_online(cpu) ? 0 : -ENOSYS;
पूर्ण

व्योम __init
smp_cpus_करोne(अचिन्हित पूर्णांक max_cpus)
अणु
	पूर्णांक cpu;
	अचिन्हित दीर्घ bogosum = 0;

	क्रम(cpu = 0; cpu < NR_CPUS; cpu++) 
		अगर (cpu_online(cpu))
			bogosum += cpu_data[cpu].loops_per_jअगरfy;
	
	prपूर्णांकk(KERN_INFO "SMP: Total of %d processors activated "
	       "(%lu.%02lu BogoMIPS).\n",
	       num_online_cpus(), 
	       (bogosum + 2500) / (500000/HZ),
	       ((bogosum + 2500) / (5000/HZ)) % 100);
पूर्ण

पूर्णांक
setup_profiling_समयr(अचिन्हित पूर्णांक multiplier)
अणु
	वापस -EINVAL;
पूर्ण

अटल व्योम
send_ipi_message(स्थिर काष्ठा cpumask *to_whom, क्रमागत ipi_message_type operation)
अणु
	पूर्णांक i;

	mb();
	क्रम_each_cpu(i, to_whom)
		set_bit(operation, &ipi_data[i].bits);

	mb();
	क्रम_each_cpu(i, to_whom)
		wripir(i);
पूर्ण

व्योम
handle_ipi(काष्ठा pt_regs *regs)
अणु
	पूर्णांक this_cpu = smp_processor_id();
	अचिन्हित दीर्घ *pending_ipis = &ipi_data[this_cpu].bits;
	अचिन्हित दीर्घ ops;

#अगर 0
	DBGS(("handle_ipi: on CPU %d ops 0x%lx PC 0x%lx\n",
	      this_cpu, *pending_ipis, regs->pc));
#पूर्ण_अगर

	mb();	/* Order पूर्णांकerrupt and bit testing. */
	जबतक ((ops = xchg(pending_ipis, 0)) != 0) अणु
	  mb();	/* Order bit clearing and data access. */
	  करो अणु
		अचिन्हित दीर्घ which;

		which = ops & -ops;
		ops &= ~which;
		which = __ffs(which);

		चयन (which) अणु
		हाल IPI_RESCHEDULE:
			scheduler_ipi();
			अवरोध;

		हाल IPI_CALL_FUNC:
			generic_smp_call_function_पूर्णांकerrupt();
			अवरोध;

		हाल IPI_CPU_STOP:
			halt();

		शेष:
			prपूर्णांकk(KERN_CRIT "Unknown IPI on CPU %d: %lu\n",
			       this_cpu, which);
			अवरोध;
		पूर्ण
	  पूर्ण जबतक (ops);

	  mb();	/* Order data access and bit testing. */
	पूर्ण

	cpu_data[this_cpu].ipi_count++;

	अगर (hwrpb->txrdy)
		recv_secondary_console_msg();
पूर्ण

व्योम
smp_send_reschedule(पूर्णांक cpu)
अणु
#अगर_घोषित DEBUG_IPI_MSG
	अगर (cpu == hard_smp_processor_id())
		prपूर्णांकk(KERN_WARNING
		       "smp_send_reschedule: Sending IPI to self.\n");
#पूर्ण_अगर
	send_ipi_message(cpumask_of(cpu), IPI_RESCHEDULE);
पूर्ण

व्योम
smp_send_stop(व्योम)
अणु
	cpumask_t to_whom;
	cpumask_copy(&to_whom, cpu_possible_mask);
	cpumask_clear_cpu(smp_processor_id(), &to_whom);
#अगर_घोषित DEBUG_IPI_MSG
	अगर (hard_smp_processor_id() != boot_cpu_id)
		prपूर्णांकk(KERN_WARNING "smp_send_stop: Not on boot cpu.\n");
#पूर्ण_अगर
	send_ipi_message(&to_whom, IPI_CPU_STOP);
पूर्ण

व्योम arch_send_call_function_ipi_mask(स्थिर काष्ठा cpumask *mask)
अणु
	send_ipi_message(mask, IPI_CALL_FUNC);
पूर्ण

व्योम arch_send_call_function_single_ipi(पूर्णांक cpu)
अणु
	send_ipi_message(cpumask_of(cpu), IPI_CALL_FUNC);
पूर्ण

अटल व्योम
ipi_imb(व्योम *ignored)
अणु
	imb();
पूर्ण

व्योम
smp_imb(व्योम)
अणु
	/* Must रुको other processors to flush their icache beक्रमe जारी. */
	on_each_cpu(ipi_imb, शून्य, 1);
पूर्ण
EXPORT_SYMBOL(smp_imb);

अटल व्योम
ipi_flush_tlb_all(व्योम *ignored)
अणु
	tbia();
पूर्ण

व्योम
flush_tlb_all(व्योम)
अणु
	/* Although we करोn't have any data to pass, we करो want to
	   synchronize with the other processors.  */
	on_each_cpu(ipi_flush_tlb_all, शून्य, 1);
पूर्ण

#घोषणा asn_locked() (cpu_data[smp_processor_id()].asn_lock)

अटल व्योम
ipi_flush_tlb_mm(व्योम *x)
अणु
	काष्ठा mm_काष्ठा *mm = (काष्ठा mm_काष्ठा *) x;
	अगर (mm == current->active_mm && !asn_locked())
		flush_tlb_current(mm);
	अन्यथा
		flush_tlb_other(mm);
पूर्ण

व्योम
flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	preempt_disable();

	अगर (mm == current->active_mm) अणु
		flush_tlb_current(mm);
		अगर (atomic_पढ़ो(&mm->mm_users) <= 1) अणु
			पूर्णांक cpu, this_cpu = smp_processor_id();
			क्रम (cpu = 0; cpu < NR_CPUS; cpu++) अणु
				अगर (!cpu_online(cpu) || cpu == this_cpu)
					जारी;
				अगर (mm->context[cpu])
					mm->context[cpu] = 0;
			पूर्ण
			preempt_enable();
			वापस;
		पूर्ण
	पूर्ण

	smp_call_function(ipi_flush_tlb_mm, mm, 1);

	preempt_enable();
पूर्ण
EXPORT_SYMBOL(flush_tlb_mm);

काष्ठा flush_tlb_page_काष्ठा अणु
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा mm_काष्ठा *mm;
	अचिन्हित दीर्घ addr;
पूर्ण;

अटल व्योम
ipi_flush_tlb_page(व्योम *x)
अणु
	काष्ठा flush_tlb_page_काष्ठा *data = (काष्ठा flush_tlb_page_काष्ठा *)x;
	काष्ठा mm_काष्ठा * mm = data->mm;

	अगर (mm == current->active_mm && !asn_locked())
		flush_tlb_current_page(mm, data->vma, data->addr);
	अन्यथा
		flush_tlb_other(mm);
पूर्ण

व्योम
flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr)
अणु
	काष्ठा flush_tlb_page_काष्ठा data;
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;

	preempt_disable();

	अगर (mm == current->active_mm) अणु
		flush_tlb_current_page(mm, vma, addr);
		अगर (atomic_पढ़ो(&mm->mm_users) <= 1) अणु
			पूर्णांक cpu, this_cpu = smp_processor_id();
			क्रम (cpu = 0; cpu < NR_CPUS; cpu++) अणु
				अगर (!cpu_online(cpu) || cpu == this_cpu)
					जारी;
				अगर (mm->context[cpu])
					mm->context[cpu] = 0;
			पूर्ण
			preempt_enable();
			वापस;
		पूर्ण
	पूर्ण

	data.vma = vma;
	data.mm = mm;
	data.addr = addr;

	smp_call_function(ipi_flush_tlb_page, &data, 1);

	preempt_enable();
पूर्ण
EXPORT_SYMBOL(flush_tlb_page);

व्योम
flush_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	/* On the Alpha we always flush the whole user tlb.  */
	flush_tlb_mm(vma->vm_mm);
पूर्ण
EXPORT_SYMBOL(flush_tlb_range);

अटल व्योम
ipi_flush_icache_page(व्योम *x)
अणु
	काष्ठा mm_काष्ठा *mm = (काष्ठा mm_काष्ठा *) x;
	अगर (mm == current->active_mm && !asn_locked())
		__load_new_mm_context(mm);
	अन्यथा
		flush_tlb_other(mm);
पूर्ण

व्योम
flush_icache_user_page(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page,
			अचिन्हित दीर्घ addr, पूर्णांक len)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;

	अगर ((vma->vm_flags & VM_EXEC) == 0)
		वापस;

	preempt_disable();

	अगर (mm == current->active_mm) अणु
		__load_new_mm_context(mm);
		अगर (atomic_पढ़ो(&mm->mm_users) <= 1) अणु
			पूर्णांक cpu, this_cpu = smp_processor_id();
			क्रम (cpu = 0; cpu < NR_CPUS; cpu++) अणु
				अगर (!cpu_online(cpu) || cpu == this_cpu)
					जारी;
				अगर (mm->context[cpu])
					mm->context[cpu] = 0;
			पूर्ण
			preempt_enable();
			वापस;
		पूर्ण
	पूर्ण

	smp_call_function(ipi_flush_icache_page, mm, 1);

	preempt_enable();
पूर्ण
