<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SMP support क्रम J2 processor
 *
 * Copyright (C) 2015-2016 Smart Energy Instruments, Inc.
 */

#समावेश <linux/smp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <यंत्र/cmpxchg.h>

DEFINE_PER_CPU(अचिन्हित, j2_ipi_messages);

बाह्य u32 *sh2_cpuid_addr;
अटल u32 *j2_ipi_trigger;
अटल पूर्णांक j2_ipi_irq;

अटल irqवापस_t j2_ipi_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *arg)
अणु
	अचिन्हित cpu = hard_smp_processor_id();
	अस्थिर अचिन्हित *pmsg = &per_cpu(j2_ipi_messages, cpu);
	अचिन्हित messages, i;

	करो messages = *pmsg;
	जबतक (cmpxchg(pmsg, messages, 0) != messages);

	अगर (!messages) वापस IRQ_NONE;

	क्रम (i=0; i<SMP_MSG_NR; i++)
		अगर (messages & (1U<<i))
			smp_message_recv(i);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम j2_smp_setup(व्योम)
अणु
पूर्ण

अटल व्योम j2_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	काष्ठा device_node *np;
	अचिन्हित i, max = 1;

	np = of_find_compatible_node(शून्य, शून्य, "jcore,ipi-controller");
	अगर (!np)
		जाओ out;

	j2_ipi_irq = irq_of_parse_and_map(np, 0);
	j2_ipi_trigger = of_iomap(np, 0);
	अगर (!j2_ipi_irq || !j2_ipi_trigger)
		जाओ out;

	np = of_find_compatible_node(शून्य, शून्य, "jcore,cpuid-mmio");
	अगर (!np)
		जाओ out;

	sh2_cpuid_addr = of_iomap(np, 0);
	अगर (!sh2_cpuid_addr)
		जाओ out;

	अगर (request_irq(j2_ipi_irq, j2_ipi_पूर्णांकerrupt_handler, IRQF_PERCPU,
			"ipi", (व्योम *)j2_ipi_पूर्णांकerrupt_handler) != 0)
		जाओ out;

	max = max_cpus;
out:
	/* Disable any cpus past max_cpus, or all secondaries अगर we didn't
	 * get the necessary resources to support SMP. */
	क्रम (i=max; i<NR_CPUS; i++) अणु
		set_cpu_possible(i, false);
		set_cpu_present(i, false);
	पूर्ण
पूर्ण

अटल व्योम j2_start_cpu(अचिन्हित पूर्णांक cpu, अचिन्हित दीर्घ entry_poपूर्णांक)
अणु
	काष्ठा device_node *np;
	u32 regs[2];
	व्योम __iomem *release, *initpc;

	अगर (!cpu) वापस;

	np = of_get_cpu_node(cpu, शून्य);
	अगर (!np) वापस;

	अगर (of_property_पढ़ो_u32_array(np, "cpu-release-addr", regs, 2)) वापस;
	release = ioremap(regs[0], माप(u32));
	initpc = ioremap(regs[1], माप(u32));

	__raw_ग_लिखोl(entry_poपूर्णांक, initpc);
	__raw_ग_लिखोl(1, release);

	iounmap(initpc);
	iounmap(release);

	pr_info("J2 SMP: requested start of cpu %u\n", cpu);
पूर्ण

अटल अचिन्हित पूर्णांक j2_smp_processor_id(व्योम)
अणु
	वापस __raw_पढ़ोl(sh2_cpuid_addr);
पूर्ण

अटल व्योम j2_send_ipi(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक message)
अणु
	अस्थिर अचिन्हित *pmsg;
	अचिन्हित old;
	अचिन्हित दीर्घ val;

	/* There is only one IPI पूर्णांकerrupt shared by all messages, so
	 * we keep a separate पूर्णांकerrupt flag per message type in sw. */
	pmsg = &per_cpu(j2_ipi_messages, cpu);
	करो old = *pmsg;
	जबतक (cmpxchg(pmsg, old, old|(1U<<message)) != old);

	/* Generate the actual पूर्णांकerrupt by writing to CCRn bit 28. */
	val = __raw_पढ़ोl(j2_ipi_trigger + cpu);
	__raw_ग_लिखोl(val | (1U<<28), j2_ipi_trigger + cpu);
पूर्ण

अटल काष्ठा plat_smp_ops j2_smp_ops = अणु
	.smp_setup		= j2_smp_setup,
	.prepare_cpus		= j2_prepare_cpus,
	.start_cpu		= j2_start_cpu,
	.smp_processor_id	= j2_smp_processor_id,
	.send_ipi		= j2_send_ipi,
	.cpu_die		= native_cpu_die,
	.cpu_disable		= native_cpu_disable,
	.play_dead		= native_play_dead,
पूर्ण;

CPU_METHOD_OF_DECLARE(j2_cpu_method, "jcore,spin-table", &j2_smp_ops);
