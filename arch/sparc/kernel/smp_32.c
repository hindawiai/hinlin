<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* smp.c: Sparc SMP support.
 *
 * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)
 * Copyright (C) 1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 * Copyright (C) 2004 Keith M Wesolowski (wesolows@foobazco.org)
 */

#समावेश <यंत्र/head.h>

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/smp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mm.h>
#समावेश <linux/fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/cache.h>
#समावेश <linux/delay.h>
#समावेश <linux/profile.h>
#समावेश <linux/cpu.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <linux/atomic.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/cpudata.h>
#समावेश <यंत्र/समयr.h>
#समावेश <यंत्र/leon.h>

#समावेश "kernel.h"
#समावेश "irq.h"

अस्थिर अचिन्हित दीर्घ cpu_callin_map[NR_CPUS] = अणु0,पूर्ण;

cpumask_t smp_commenced_mask = CPU_MASK_NONE;

स्थिर काष्ठा sparc32_ipi_ops *sparc32_ipi_ops;

/* The only guaranteed locking primitive available on all Sparc
 * processors is 'ldstub [%reg + immediate], %dest_reg' which atomically
 * places the current byte at the effective address पूर्णांकo dest_reg and
 * places 0xff there afterwards.  Pretty lame locking primitive
 * compared to the Alpha and the Intel no?  Most Sparcs have 'swap'
 * inकाष्ठाion which is much better...
 */

व्योम smp_store_cpu_info(पूर्णांक id)
अणु
	पूर्णांक cpu_node;
	पूर्णांक mid;

	cpu_data(id).udelay_val = loops_per_jअगरfy;

	cpu_find_by_mid(id, &cpu_node);
	cpu_data(id).घड़ी_प्रकारick = prom_getपूर्णांकशेष(cpu_node,
						     "clock-frequency", 0);
	cpu_data(id).prom_node = cpu_node;
	mid = cpu_get_hwmid(cpu_node);

	अगर (mid < 0) अणु
		prपूर्णांकk(KERN_NOTICE "No MID found for CPU%d at node 0x%08x", id, cpu_node);
		mid = 0;
	पूर्ण
	cpu_data(id).mid = mid;
पूर्ण

व्योम __init smp_cpus_करोne(अचिन्हित पूर्णांक max_cpus)
अणु
	अचिन्हित दीर्घ bogosum = 0;
	पूर्णांक cpu, num = 0;

	क्रम_each_online_cpu(cpu) अणु
		num++;
		bogosum += cpu_data(cpu).udelay_val;
	पूर्ण

	prपूर्णांकk("Total of %d processors activated (%lu.%02lu BogoMIPS).\n",
		num, bogosum/(500000/HZ),
		(bogosum/(5000/HZ))%100);

	चयन(sparc_cpu_model) अणु
	हाल sun4m:
		smp4m_smp_करोne();
		अवरोध;
	हाल sun4d:
		smp4d_smp_करोne();
		अवरोध;
	हाल sparc_leon:
		leon_smp_करोne();
		अवरोध;
	हाल sun4e:
		prपूर्णांकk("SUN4E\n");
		BUG();
		अवरोध;
	हाल sun4u:
		prपूर्णांकk("SUN4U\n");
		BUG();
		अवरोध;
	शेष:
		prपूर्णांकk("UNKNOWN!\n");
		BUG();
		अवरोध;
	पूर्ण
पूर्ण

व्योम cpu_panic(व्योम)
अणु
	prपूर्णांकk("CPU[%d]: Returns from cpu_idle!\n", smp_processor_id());
	panic("SMP bolixed\n");
पूर्ण

काष्ठा linux_prom_रेजिस्टरs smp_penguin_ctable = अणु 0 पूर्ण;

व्योम smp_send_reschedule(पूर्णांक cpu)
अणु
	/*
	 * CPU model dependent way of implementing IPI generation targeting
	 * a single CPU. The trap handler needs only to करो trap entry/वापस
	 * to call schedule.
	 */
	sparc32_ipi_ops->resched(cpu);
पूर्ण

व्योम smp_send_stop(व्योम)
अणु
पूर्ण

व्योम arch_send_call_function_single_ipi(पूर्णांक cpu)
अणु
	/* trigger one IPI single call on one CPU */
	sparc32_ipi_ops->single(cpu);
पूर्ण

व्योम arch_send_call_function_ipi_mask(स्थिर काष्ठा cpumask *mask)
अणु
	पूर्णांक cpu;

	/* trigger IPI mask call on each CPU */
	क्रम_each_cpu(cpu, mask)
		sparc32_ipi_ops->mask_one(cpu);
पूर्ण

व्योम smp_resched_पूर्णांकerrupt(व्योम)
अणु
	irq_enter();
	scheduler_ipi();
	local_cpu_data().irq_resched_count++;
	irq_निकास();
	/* re-schedule routine called by पूर्णांकerrupt वापस code. */
पूर्ण

व्योम smp_call_function_single_पूर्णांकerrupt(व्योम)
अणु
	irq_enter();
	generic_smp_call_function_single_पूर्णांकerrupt();
	local_cpu_data().irq_call_count++;
	irq_निकास();
पूर्ण

व्योम smp_call_function_पूर्णांकerrupt(व्योम)
अणु
	irq_enter();
	generic_smp_call_function_पूर्णांकerrupt();
	local_cpu_data().irq_call_count++;
	irq_निकास();
पूर्ण

पूर्णांक setup_profiling_समयr(अचिन्हित पूर्णांक multiplier)
अणु
	वापस -EINVAL;
पूर्ण

व्योम __init smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	पूर्णांक i, cpuid, extra;

	prपूर्णांकk("Entering SMP Mode...\n");

	extra = 0;
	क्रम (i = 0; !cpu_find_by_instance(i, शून्य, &cpuid); i++) अणु
		अगर (cpuid >= NR_CPUS)
			extra++;
	पूर्ण
	/* i = number of cpus */
	अगर (extra && max_cpus > i - extra)
		prपूर्णांकk("Warning: NR_CPUS is too low to start all cpus\n");

	smp_store_cpu_info(boot_cpu_id);

	चयन(sparc_cpu_model) अणु
	हाल sun4m:
		smp4m_boot_cpus();
		अवरोध;
	हाल sun4d:
		smp4d_boot_cpus();
		अवरोध;
	हाल sparc_leon:
		leon_boot_cpus();
		अवरोध;
	हाल sun4e:
		prपूर्णांकk("SUN4E\n");
		BUG();
		अवरोध;
	हाल sun4u:
		prपूर्णांकk("SUN4U\n");
		BUG();
		अवरोध;
	शेष:
		prपूर्णांकk("UNKNOWN!\n");
		BUG();
		अवरोध;
	पूर्ण
पूर्ण

/* Set this up early so that things like the scheduler can init
 * properly.  We use the same cpu mask क्रम both the present and
 * possible cpu map.
 */
व्योम __init smp_setup_cpu_possible_map(व्योम)
अणु
	पूर्णांक instance, mid;

	instance = 0;
	जबतक (!cpu_find_by_instance(instance, शून्य, &mid)) अणु
		अगर (mid < NR_CPUS) अणु
			set_cpu_possible(mid, true);
			set_cpu_present(mid, true);
		पूर्ण
		instance++;
	पूर्ण
पूर्ण

व्योम __init smp_prepare_boot_cpu(व्योम)
अणु
	पूर्णांक cpuid = hard_smp_processor_id();

	अगर (cpuid >= NR_CPUS) अणु
		prom_म_लिखो("Serious problem, boot cpu id >= NR_CPUS\n");
		prom_halt();
	पूर्ण
	अगर (cpuid != 0)
		prपूर्णांकk("boot cpu id != 0, this could work but is untested\n");

	current_thपढ़ो_info()->cpu = cpuid;
	set_cpu_online(cpuid, true);
	set_cpu_possible(cpuid, true);
पूर्ण

पूर्णांक __cpu_up(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *tidle)
अणु
	पूर्णांक ret=0;

	चयन(sparc_cpu_model) अणु
	हाल sun4m:
		ret = smp4m_boot_one_cpu(cpu, tidle);
		अवरोध;
	हाल sun4d:
		ret = smp4d_boot_one_cpu(cpu, tidle);
		अवरोध;
	हाल sparc_leon:
		ret = leon_boot_one_cpu(cpu, tidle);
		अवरोध;
	हाल sun4e:
		prपूर्णांकk("SUN4E\n");
		BUG();
		अवरोध;
	हाल sun4u:
		prपूर्णांकk("SUN4U\n");
		BUG();
		अवरोध;
	शेष:
		prपूर्णांकk("UNKNOWN!\n");
		BUG();
		अवरोध;
	पूर्ण

	अगर (!ret) अणु
		cpumask_set_cpu(cpu, &smp_commenced_mask);
		जबतक (!cpu_online(cpu))
			mb();
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम arch_cpu_pre_starting(व्योम *arg)
अणु
	local_ops->cache_all();
	local_ops->tlb_all();

	चयन(sparc_cpu_model) अणु
	हाल sun4m:
		sun4m_cpu_pre_starting(arg);
		अवरोध;
	हाल sun4d:
		sun4d_cpu_pre_starting(arg);
		अवरोध;
	हाल sparc_leon:
		leon_cpu_pre_starting(arg);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल व्योम arch_cpu_pre_online(व्योम *arg)
अणु
	अचिन्हित पूर्णांक cpuid = hard_smp_processor_id();

	रेजिस्टर_percpu_ce(cpuid);

	calibrate_delay();
	smp_store_cpu_info(cpuid);

	local_ops->cache_all();
	local_ops->tlb_all();

	चयन(sparc_cpu_model) अणु
	हाल sun4m:
		sun4m_cpu_pre_online(arg);
		अवरोध;
	हाल sun4d:
		sun4d_cpu_pre_online(arg);
		अवरोध;
	हाल sparc_leon:
		leon_cpu_pre_online(arg);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल व्योम sparc_start_secondary(व्योम *arg)
अणु
	अचिन्हित पूर्णांक cpu;

	/*
	 * SMP booting is extremely fragile in some architectures. So run
	 * the cpu initialization code first beक्रमe anything अन्यथा.
	 */
	arch_cpu_pre_starting(arg);

	preempt_disable();
	cpu = smp_processor_id();

	notअगरy_cpu_starting(cpu);
	arch_cpu_pre_online(arg);

	/* Set the CPU in the cpu_online_mask */
	set_cpu_online(cpu, true);

	/* Enable local पूर्णांकerrupts now */
	local_irq_enable();

	wmb();
	cpu_startup_entry(CPUHP_AP_ONLINE_IDLE);

	/* We should never reach here! */
	BUG();
पूर्ण

व्योम smp_callin(व्योम)
अणु
	sparc_start_secondary(शून्य);
पूर्ण

व्योम smp_bogo(काष्ठा seq_file *m)
अणु
	पूर्णांक i;
	
	क्रम_each_online_cpu(i) अणु
		seq_म_लिखो(m,
			   "Cpu%dBogo\t: %lu.%02lu\n",
			   i,
			   cpu_data(i).udelay_val/(500000/HZ),
			   (cpu_data(i).udelay_val/(5000/HZ))%100);
	पूर्ण
पूर्ण

व्योम smp_info(काष्ठा seq_file *m)
अणु
	पूर्णांक i;

	seq_म_लिखो(m, "State:\n");
	क्रम_each_online_cpu(i)
		seq_म_लिखो(m, "CPU%d\t\t: online\n", i);
पूर्ण
