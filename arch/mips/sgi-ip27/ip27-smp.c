<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file "COPYING" in the मुख्य directory of this
 * archive क्रम more details.
 *
 * Copyright (C) 2000 - 2001 by Kanoj Sarcar (kanoj@sgi.com)
 * Copyright (C) 2000 - 2001 by Silicon Graphics, Inc.
 */
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/topology.h>
#समावेश <linux/nodemask.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/sn/agent.h>
#समावेश <यंत्र/sn/arch.h>
#समावेश <यंत्र/sn/gda.h>
#समावेश <यंत्र/sn/पूर्णांकr.h>
#समावेश <यंत्र/sn/klconfig.h>
#समावेश <यंत्र/sn/launch.h>
#समावेश <यंत्र/sn/mapped_kernel.h>
#समावेश <यंत्र/sn/types.h>

#समावेश "ip27-common.h"

अटल पूर्णांक node_scan_cpus(nasid_t nasid, पूर्णांक highest)
अणु
	अटल पूर्णांक cpus_found;
	lboard_t *brd;
	klcpu_t *acpu;
	cpuid_t cpuid;

	brd = find_lboard((lboard_t *)KL_CONFIG_INFO(nasid), KLTYPE_IP27);

	करो अणु
		acpu = (klcpu_t *)find_first_component(brd, KLSTRUCT_CPU);
		जबतक (acpu) अणु
			cpuid = acpu->cpu_info.virtid;
			/* Only let it join in अगर it's marked enabled */
			अगर ((acpu->cpu_info.flags & KLINFO_ENABLE) &&
			    (cpus_found != NR_CPUS)) अणु
				अगर (cpuid > highest)
					highest = cpuid;
				set_cpu_possible(cpuid, true);
				cputonasid(cpus_found) = nasid;
				cputoslice(cpus_found) = acpu->cpu_info.physid;
				sn_cpu_info[cpus_found].p_speed =
							acpu->cpu_speed;
				cpus_found++;
			पूर्ण
			acpu = (klcpu_t *)find_component(brd, (klinfo_t *)acpu,
								KLSTRUCT_CPU);
		पूर्ण
		brd = KLCF_NEXT(brd);
		अगर (!brd)
			अवरोध;

		brd = find_lboard(brd, KLTYPE_IP27);
	पूर्ण जबतक (brd);

	वापस highest;
पूर्ण

व्योम cpu_node_probe(व्योम)
अणु
	पूर्णांक i, highest = 0;
	gda_t *gdap = GDA;

	nodes_clear(node_online_map);
	क्रम (i = 0; i < MAX_NUMNODES; i++) अणु
		nasid_t nasid = gdap->g_nasidtable[i];
		अगर (nasid == INVALID_NASID)
			अवरोध;
		node_set_online(nasid);
		highest = node_scan_cpus(nasid, highest);
	पूर्ण

	prपूर्णांकk("Discovered %d cpus on %d nodes\n", highest + 1, num_online_nodes());
पूर्ण

अटल __init व्योम पूर्णांकr_clear_all(nasid_t nasid)
अणु
	पूर्णांक i;

	REMOTE_HUB_S(nasid, PI_INT_MASK0_A, 0);
	REMOTE_HUB_S(nasid, PI_INT_MASK0_B, 0);
	REMOTE_HUB_S(nasid, PI_INT_MASK1_A, 0);
	REMOTE_HUB_S(nasid, PI_INT_MASK1_B, 0);

	क्रम (i = 0; i < 128; i++)
		REMOTE_HUB_CLR_INTR(nasid, i);
पूर्ण

अटल व्योम ip27_send_ipi_single(पूर्णांक destid, अचिन्हित पूर्णांक action)
अणु
	पूर्णांक irq;

	चयन (action) अणु
	हाल SMP_RESCHEDULE_YOURSELF:
		irq = CPU_RESCHED_A_IRQ;
		अवरोध;
	हाल SMP_CALL_FUNCTION:
		irq = CPU_CALL_A_IRQ;
		अवरोध;
	शेष:
		panic("sendintr");
	पूर्ण

	irq += cputoslice(destid);

	/*
	 * Set the पूर्णांकerrupt bit associated with the CPU we want to
	 * send the पूर्णांकerrupt to.
	 */
	REMOTE_HUB_SEND_INTR(cpu_to_node(destid), irq);
पूर्ण

अटल व्योम ip27_send_ipi_mask(स्थिर काष्ठा cpumask *mask, अचिन्हित पूर्णांक action)
अणु
	अचिन्हित पूर्णांक i;

	क्रम_each_cpu(i, mask)
		ip27_send_ipi_single(i, action);
पूर्ण

अटल व्योम ip27_init_cpu(व्योम)
अणु
	per_cpu_init();
पूर्ण

अटल व्योम ip27_smp_finish(व्योम)
अणु
	hub_rt_घड़ी_event_init();
	local_irq_enable();
पूर्ण

/*
 * Launch a slave पूर्णांकo smp_bootstrap().	 It करोesn't take an argument, and we
 * set sp to the kernel stack of the newly created idle process, gp to the proc
 * काष्ठा so that current_thपढ़ो_info() will work.
 */
अटल पूर्णांक ip27_boot_secondary(पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	अचिन्हित दीर्घ gp = (अचिन्हित दीर्घ)task_thपढ़ो_info(idle);
	अचिन्हित दीर्घ sp = __KSTK_TOS(idle);

	LAUNCH_SLAVE(cputonasid(cpu), cputoslice(cpu),
		(launch_proc_t)MAPPED_KERN_RW_TO_K0(smp_bootstrap),
		0, (व्योम *) sp, (व्योम *) gp);
	वापस 0;
पूर्ण

अटल व्योम __init ip27_smp_setup(व्योम)
अणु
	nasid_t nasid;

	क्रम_each_online_node(nasid) अणु
		अगर (nasid == 0)
			जारी;
		पूर्णांकr_clear_all(nasid);
	पूर्ण

	replicate_kernel_text();

	/*
	 * PROM sets up प्रणाली, that boot cpu is always first CPU on nasid 0
	 */
	cputonasid(0) = 0;
	cputoslice(0) = LOCAL_HUB_L(PI_CPU_NUM);
पूर्ण

अटल व्योम __init ip27_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	/* We alपढ़ोy did everything necessary earlier */
पूर्ण

स्थिर काष्ठा plat_smp_ops ip27_smp_ops = अणु
	.send_ipi_single	= ip27_send_ipi_single,
	.send_ipi_mask		= ip27_send_ipi_mask,
	.init_secondary		= ip27_init_cpu,
	.smp_finish		= ip27_smp_finish,
	.boot_secondary		= ip27_boot_secondary,
	.smp_setup		= ip27_smp_setup,
	.prepare_cpus		= ip27_prepare_cpus,
	.prepare_boot_cpu	= ip27_init_cpu,
पूर्ण;
