<शैली गुरु>
/*
 * Copyright 2003-2011 NetLogic Microप्रणालीs, Inc. (NetLogic). All rights
 * reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the NetLogic
 * license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY NETLOGIC ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL NETLOGIC OR CONTRIBUTORS BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/smp.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/mmu_context.h>

#समावेश <यंत्र/netlogic/पूर्णांकerrupt.h>
#समावेश <यंत्र/netlogic/mips-extns.h>
#समावेश <यंत्र/netlogic/haldefs.h>
#समावेश <यंत्र/netlogic/common.h>

#अगर defined(CONFIG_CPU_XLP)
#समावेश <यंत्र/netlogic/xlp-hal/iomap.h>
#समावेश <यंत्र/netlogic/xlp-hal/xlp.h>
#समावेश <यंत्र/netlogic/xlp-hal/pic.h>
#या_अगर defined(CONFIG_CPU_XLR)
#समावेश <यंत्र/netlogic/xlr/iomap.h>
#समावेश <यंत्र/netlogic/xlr/pic.h>
#समावेश <यंत्र/netlogic/xlr/xlr.h>
#अन्यथा
#त्रुटि "Unknown CPU"
#पूर्ण_अगर

व्योम nlm_send_ipi_single(पूर्णांक logical_cpu, अचिन्हित पूर्णांक action)
अणु
	अचिन्हित पूर्णांक hwtid;
	uपूर्णांक64_t picbase;

	/* node id is part of hwtid, and needed क्रम send_ipi */
	hwtid = cpu_logical_map(logical_cpu);
	picbase = nlm_get_node(nlm_hwtid_to_node(hwtid))->picbase;

	अगर (action & SMP_CALL_FUNCTION)
		nlm_pic_send_ipi(picbase, hwtid, IRQ_IPI_SMP_FUNCTION, 0);
	अगर (action & SMP_RESCHEDULE_YOURSELF)
		nlm_pic_send_ipi(picbase, hwtid, IRQ_IPI_SMP_RESCHEDULE, 0);
पूर्ण

व्योम nlm_send_ipi_mask(स्थिर काष्ठा cpumask *mask, अचिन्हित पूर्णांक action)
अणु
	पूर्णांक cpu;

	क्रम_each_cpu(cpu, mask) अणु
		nlm_send_ipi_single(cpu, action);
	पूर्ण
पूर्ण

/* IRQ_IPI_SMP_FUNCTION Handler */
व्योम nlm_smp_function_ipi_handler(काष्ठा irq_desc *desc)
अणु
	अचिन्हित पूर्णांक irq = irq_desc_get_irq(desc);
	clear_c0_eimr(irq);
	ack_c0_eirr(irq);
	generic_smp_call_function_पूर्णांकerrupt();
	set_c0_eimr(irq);
पूर्ण

/* IRQ_IPI_SMP_RESCHEDULE  handler */
व्योम nlm_smp_resched_ipi_handler(काष्ठा irq_desc *desc)
अणु
	अचिन्हित पूर्णांक irq = irq_desc_get_irq(desc);
	clear_c0_eimr(irq);
	ack_c0_eirr(irq);
	scheduler_ipi();
	set_c0_eimr(irq);
पूर्ण

/*
 * Called beक्रमe going पूर्णांकo mips code, early cpu init
 */
व्योम nlm_early_init_secondary(पूर्णांक cpu)
अणु
	change_c0_config(CONF_CM_CMASK, 0x3);
#अगर_घोषित CONFIG_CPU_XLP
	xlp_mmu_init();
#पूर्ण_अगर
	ग_लिखो_c0_ebase(nlm_current_node()->ebase);
पूर्ण

/*
 * Code to run on secondary just after probing the CPU
 */
अटल व्योम nlm_init_secondary(व्योम)
अणु
	पूर्णांक hwtid;

	hwtid = hard_smp_processor_id();
	cpu_set_core(&current_cpu_data, hwtid / NLM_THREADS_PER_CORE);
	current_cpu_data.package = nlm_nodeid();
	nlm_percpu_init(hwtid);
	nlm_smp_irq_init(hwtid);
पूर्ण

व्योम nlm_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	/* declare we are SMT capable */
	smp_num_siblings = nlm_thपढ़ोs_per_core;
पूर्ण

व्योम nlm_smp_finish(व्योम)
अणु
	local_irq_enable();
पूर्ण

/*
 * Boot all other cpus in the प्रणाली, initialize them, and bring them पूर्णांकo
 * the boot function
 */
अचिन्हित दीर्घ nlm_next_gp;
अचिन्हित दीर्घ nlm_next_sp;
अटल cpumask_t phys_cpu_present_mask;

पूर्णांक nlm_boot_secondary(पूर्णांक logical_cpu, काष्ठा task_काष्ठा *idle)
अणु
	uपूर्णांक64_t picbase;
	पूर्णांक hwtid;

	hwtid = cpu_logical_map(logical_cpu);
	picbase = nlm_get_node(nlm_hwtid_to_node(hwtid))->picbase;

	nlm_next_sp = (अचिन्हित दीर्घ)__KSTK_TOS(idle);
	nlm_next_gp = (अचिन्हित दीर्घ)task_thपढ़ो_info(idle);

	/* barrier क्रम sp/gp store above */
	__sync();
	nlm_pic_send_ipi(picbase, hwtid, 1, 1);  /* NMI */

	वापस 0;
पूर्ण

व्योम __init nlm_smp_setup(व्योम)
अणु
	अचिन्हित पूर्णांक boot_cpu;
	पूर्णांक num_cpus, i, ncore, node;
	अस्थिर u32 *cpu_पढ़ोy = nlm_get_boot_data(BOOT_CPU_READY);

	boot_cpu = hard_smp_processor_id();
	cpumask_clear(&phys_cpu_present_mask);

	cpumask_set_cpu(boot_cpu, &phys_cpu_present_mask);
	__cpu_number_map[boot_cpu] = 0;
	__cpu_logical_map[0] = boot_cpu;
	set_cpu_possible(0, true);

	num_cpus = 1;
	क्रम (i = 0; i < NR_CPUS; i++) अणु
		/*
		 * cpu_पढ़ोy array is not set क्रम the boot_cpu,
		 * it is only set क्रम ASPs (see smpboot.S)
		 */
		अगर (cpu_पढ़ोy[i]) अणु
			cpumask_set_cpu(i, &phys_cpu_present_mask);
			__cpu_number_map[i] = num_cpus;
			__cpu_logical_map[num_cpus] = i;
			set_cpu_possible(num_cpus, true);
			node = nlm_hwtid_to_node(i);
			cpumask_set_cpu(num_cpus, &nlm_get_node(node)->cpumask);
			++num_cpus;
		पूर्ण
	पूर्ण

	pr_info("Physical CPU mask: %*pb\n",
		cpumask_pr_args(&phys_cpu_present_mask));
	pr_info("Possible CPU mask: %*pb\n",
		cpumask_pr_args(cpu_possible_mask));

	/* check with the cores we have woken up */
	क्रम (ncore = 0, i = 0; i < NLM_NR_NODES; i++)
		ncore += hweight32(nlm_get_node(i)->coremask);

	pr_info("Detected (%dc%dt) %d Slave CPU(s)\n", ncore,
		nlm_thपढ़ोs_per_core, num_cpus);

	/* चयन NMI handler to boot CPUs */
	nlm_set_nmi_handler(nlm_boot_secondary_cpus);
पूर्ण

अटल पूर्णांक nlm_parse_cpumask(cpumask_t *wakeup_mask)
अणु
	uपूर्णांक32_t core0_thr_mask, core_thr_mask;
	पूर्णांक thपढ़ोmode, i, j;

	core0_thr_mask = 0;
	क्रम (i = 0; i < NLM_THREADS_PER_CORE; i++)
		अगर (cpumask_test_cpu(i, wakeup_mask))
			core0_thr_mask |= (1 << i);
	चयन (core0_thr_mask) अणु
	हाल 1:
		nlm_thपढ़ोs_per_core = 1;
		thपढ़ोmode = 0;
		अवरोध;
	हाल 3:
		nlm_thपढ़ोs_per_core = 2;
		thपढ़ोmode = 2;
		अवरोध;
	हाल 0xf:
		nlm_thपढ़ोs_per_core = 4;
		thपढ़ोmode = 3;
		अवरोध;
	शेष:
		जाओ unsupp;
	पूर्ण

	/* Verअगरy other cores CPU masks */
	क्रम (i = 0; i < NR_CPUS; i += NLM_THREADS_PER_CORE) अणु
		core_thr_mask = 0;
		क्रम (j = 0; j < NLM_THREADS_PER_CORE; j++)
			अगर (cpumask_test_cpu(i + j, wakeup_mask))
				core_thr_mask |= (1 << j);
		अगर (core_thr_mask != 0 && core_thr_mask != core0_thr_mask)
				जाओ unsupp;
	पूर्ण
	वापस thपढ़ोmode;

unsupp:
	panic("Unsupported CPU mask %*pb", cpumask_pr_args(wakeup_mask));
	वापस 0;
पूर्ण

पूर्णांक nlm_wakeup_secondary_cpus(व्योम)
अणु
	u32 *reset_data;
	पूर्णांक thपढ़ोmode;

	/* verअगरy the mask and setup core config variables */
	thपढ़ोmode = nlm_parse_cpumask(&nlm_cpumask);

	/* Setup CPU init parameters */
	reset_data = nlm_get_boot_data(BOOT_THREAD_MODE);
	*reset_data = thपढ़ोmode;

#अगर_घोषित CONFIG_CPU_XLP
	xlp_wakeup_secondary_cpus();
#अन्यथा
	xlr_wakeup_secondary_cpus();
#पूर्ण_अगर
	वापस 0;
पूर्ण

स्थिर काष्ठा plat_smp_ops nlm_smp_ops = अणु
	.send_ipi_single	= nlm_send_ipi_single,
	.send_ipi_mask		= nlm_send_ipi_mask,
	.init_secondary		= nlm_init_secondary,
	.smp_finish		= nlm_smp_finish,
	.boot_secondary		= nlm_boot_secondary,
	.smp_setup		= nlm_smp_setup,
	.prepare_cpus		= nlm_prepare_cpus,
पूर्ण;
