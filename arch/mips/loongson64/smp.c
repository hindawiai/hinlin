<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2010, 2011, 2012, Lemote, Inc.
 * Author: Chen Huacai, chenhc@lemote.com
 */

#समावेश <irq.h>
#समावेश <linux/init.h>
#समावेश <linux/cpu.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/hotplug.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/smp.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/kexec.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <loongson.h>
#समावेश <loongson_regs.h>
#समावेश <workarounds.h>

#समावेश "smp.h"

DEFINE_PER_CPU(पूर्णांक, cpu_state);

#घोषणा LS_IPI_IRQ (MIPS_CPU_IRQ_BASE + 6)

अटल व्योम *ipi_set0_regs[16];
अटल व्योम *ipi_clear0_regs[16];
अटल व्योम *ipi_status0_regs[16];
अटल व्योम *ipi_en0_regs[16];
अटल व्योम *ipi_mailbox_buf[16];
अटल uपूर्णांक32_t core0_c0count[NR_CPUS];

/* पढ़ो a 32bit value from ipi रेजिस्टर */
#घोषणा loongson3_ipi_पढ़ो32(addr) पढ़ोl(addr)
/* पढ़ो a 64bit value from ipi रेजिस्टर */
#घोषणा loongson3_ipi_पढ़ो64(addr) पढ़ोq(addr)
/* ग_लिखो a 32bit value to ipi रेजिस्टर */
#घोषणा loongson3_ipi_ग_लिखो32(action, addr)	\
	करो अणु					\
		ग_लिखोl(action, addr);		\
		__wbflush();			\
	पूर्ण जबतक (0)
/* ग_लिखो a 64bit value to ipi रेजिस्टर */
#घोषणा loongson3_ipi_ग_लिखो64(action, addr)	\
	करो अणु					\
		ग_लिखोq(action, addr);		\
		__wbflush();			\
	पूर्ण जबतक (0)

u32 (*ipi_पढ़ो_clear)(पूर्णांक cpu);
व्योम (*ipi_ग_लिखो_action)(पूर्णांक cpu, u32 action);
व्योम (*ipi_ग_लिखो_enable)(पूर्णांक cpu);
व्योम (*ipi_clear_buf)(पूर्णांक cpu);
व्योम (*ipi_ग_लिखो_buf)(पूर्णांक cpu, काष्ठा task_काष्ठा *idle);

/* send mail via Mail_Send रेजिस्टर क्रम 3A4000+ CPU */
अटल व्योम csr_mail_send(uपूर्णांक64_t data, पूर्णांक cpu, पूर्णांक mailbox)
अणु
	uपूर्णांक64_t val;

	/* send high 32 bits */
	val = CSR_MAIL_SEND_BLOCK;
	val |= (CSR_MAIL_SEND_BOX_HIGH(mailbox) << CSR_MAIL_SEND_BOX_SHIFT);
	val |= (cpu << CSR_MAIL_SEND_CPU_SHIFT);
	val |= (data & CSR_MAIL_SEND_H32_MASK);
	csr_ग_लिखोq(val, LOONGSON_CSR_MAIL_SEND);

	/* send low 32 bits */
	val = CSR_MAIL_SEND_BLOCK;
	val |= (CSR_MAIL_SEND_BOX_LOW(mailbox) << CSR_MAIL_SEND_BOX_SHIFT);
	val |= (cpu << CSR_MAIL_SEND_CPU_SHIFT);
	val |= (data << CSR_MAIL_SEND_BUF_SHIFT);
	csr_ग_लिखोq(val, LOONGSON_CSR_MAIL_SEND);
पूर्ण;

अटल u32 csr_ipi_पढ़ो_clear(पूर्णांक cpu)
अणु
	u32 action;

	/* Load the ipi रेजिस्टर to figure out what we're supposed to करो */
	action = csr_पढ़ोl(LOONGSON_CSR_IPI_STATUS);
	/* Clear the ipi रेजिस्टर to clear the पूर्णांकerrupt */
	csr_ग_लिखोl(action, LOONGSON_CSR_IPI_CLEAR);

	वापस action;
पूर्ण

अटल व्योम csr_ipi_ग_लिखो_action(पूर्णांक cpu, u32 action)
अणु
	अचिन्हित पूर्णांक irq = 0;

	जबतक ((irq = ffs(action))) अणु
		uपूर्णांक32_t val = CSR_IPI_SEND_BLOCK;
		val |= (irq - 1);
		val |= (cpu << CSR_IPI_SEND_CPU_SHIFT);
		csr_ग_लिखोl(val, LOONGSON_CSR_IPI_SEND);
		action &= ~BIT(irq - 1);
	पूर्ण
पूर्ण

अटल व्योम csr_ipi_ग_लिखो_enable(पूर्णांक cpu)
अणु
	csr_ग_लिखोl(0xffffffff, LOONGSON_CSR_IPI_EN);
पूर्ण

अटल व्योम csr_ipi_clear_buf(पूर्णांक cpu)
अणु
	csr_ग_लिखोq(0, LOONGSON_CSR_MAIL_BUF0);
पूर्ण

अटल व्योम csr_ipi_ग_लिखो_buf(पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	अचिन्हित दीर्घ startargs[4];

	/* startargs[] are initial PC, SP and GP क्रम secondary CPU */
	startargs[0] = (अचिन्हित दीर्घ)&smp_bootstrap;
	startargs[1] = (अचिन्हित दीर्घ)__KSTK_TOS(idle);
	startargs[2] = (अचिन्हित दीर्घ)task_thपढ़ो_info(idle);
	startargs[3] = 0;

	pr_debug("CPU#%d, func_pc=%lx, sp=%lx, gp=%lx\n",
		cpu, startargs[0], startargs[1], startargs[2]);

	csr_mail_send(startargs[3], cpu_logical_map(cpu), 3);
	csr_mail_send(startargs[2], cpu_logical_map(cpu), 2);
	csr_mail_send(startargs[1], cpu_logical_map(cpu), 1);
	csr_mail_send(startargs[0], cpu_logical_map(cpu), 0);
पूर्ण

अटल u32 legacy_ipi_पढ़ो_clear(पूर्णांक cpu)
अणु
	u32 action;

	/* Load the ipi रेजिस्टर to figure out what we're supposed to करो */
	action = loongson3_ipi_पढ़ो32(ipi_status0_regs[cpu_logical_map(cpu)]);
	/* Clear the ipi रेजिस्टर to clear the पूर्णांकerrupt */
	loongson3_ipi_ग_लिखो32(action, ipi_clear0_regs[cpu_logical_map(cpu)]);

	वापस action;
पूर्ण

अटल व्योम legacy_ipi_ग_लिखो_action(पूर्णांक cpu, u32 action)
अणु
	loongson3_ipi_ग_लिखो32((u32)action, ipi_set0_regs[cpu]);
पूर्ण

अटल व्योम legacy_ipi_ग_लिखो_enable(पूर्णांक cpu)
अणु
	loongson3_ipi_ग_लिखो32(0xffffffff, ipi_en0_regs[cpu_logical_map(cpu)]);
पूर्ण

अटल व्योम legacy_ipi_clear_buf(पूर्णांक cpu)
अणु
	loongson3_ipi_ग_लिखो64(0, ipi_mailbox_buf[cpu_logical_map(cpu)] + 0x0);
पूर्ण

अटल व्योम legacy_ipi_ग_लिखो_buf(पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	अचिन्हित दीर्घ startargs[4];

	/* startargs[] are initial PC, SP and GP क्रम secondary CPU */
	startargs[0] = (अचिन्हित दीर्घ)&smp_bootstrap;
	startargs[1] = (अचिन्हित दीर्घ)__KSTK_TOS(idle);
	startargs[2] = (अचिन्हित दीर्घ)task_thपढ़ो_info(idle);
	startargs[3] = 0;

	pr_debug("CPU#%d, func_pc=%lx, sp=%lx, gp=%lx\n",
			cpu, startargs[0], startargs[1], startargs[2]);

	loongson3_ipi_ग_लिखो64(startargs[3],
			ipi_mailbox_buf[cpu_logical_map(cpu)] + 0x18);
	loongson3_ipi_ग_लिखो64(startargs[2],
			ipi_mailbox_buf[cpu_logical_map(cpu)] + 0x10);
	loongson3_ipi_ग_लिखो64(startargs[1],
			ipi_mailbox_buf[cpu_logical_map(cpu)] + 0x8);
	loongson3_ipi_ग_लिखो64(startargs[0],
			ipi_mailbox_buf[cpu_logical_map(cpu)] + 0x0);
पूर्ण

अटल व्योम csr_ipi_probe(व्योम)
अणु
	अगर (cpu_has_csr() && csr_पढ़ोl(LOONGSON_CSR_FEATURES) & LOONGSON_CSRF_IPI) अणु
		ipi_पढ़ो_clear = csr_ipi_पढ़ो_clear;
		ipi_ग_लिखो_action = csr_ipi_ग_लिखो_action;
		ipi_ग_लिखो_enable = csr_ipi_ग_लिखो_enable;
		ipi_clear_buf = csr_ipi_clear_buf;
		ipi_ग_लिखो_buf = csr_ipi_ग_लिखो_buf;
	पूर्ण अन्यथा अणु
		ipi_पढ़ो_clear = legacy_ipi_पढ़ो_clear;
		ipi_ग_लिखो_action = legacy_ipi_ग_लिखो_action;
		ipi_ग_लिखो_enable = legacy_ipi_ग_लिखो_enable;
		ipi_clear_buf = legacy_ipi_clear_buf;
		ipi_ग_लिखो_buf = legacy_ipi_ग_लिखो_buf;
	पूर्ण
पूर्ण

अटल व्योम ipi_set0_regs_init(व्योम)
अणु
	ipi_set0_regs[0] = (व्योम *)
		(SMP_CORE_GROUP0_BASE + SMP_CORE0_OFFSET + SET0);
	ipi_set0_regs[1] = (व्योम *)
		(SMP_CORE_GROUP0_BASE + SMP_CORE1_OFFSET + SET0);
	ipi_set0_regs[2] = (व्योम *)
		(SMP_CORE_GROUP0_BASE + SMP_CORE2_OFFSET + SET0);
	ipi_set0_regs[3] = (व्योम *)
		(SMP_CORE_GROUP0_BASE + SMP_CORE3_OFFSET + SET0);
	ipi_set0_regs[4] = (व्योम *)
		(SMP_CORE_GROUP1_BASE + SMP_CORE0_OFFSET + SET0);
	ipi_set0_regs[5] = (व्योम *)
		(SMP_CORE_GROUP1_BASE + SMP_CORE1_OFFSET + SET0);
	ipi_set0_regs[6] = (व्योम *)
		(SMP_CORE_GROUP1_BASE + SMP_CORE2_OFFSET + SET0);
	ipi_set0_regs[7] = (व्योम *)
		(SMP_CORE_GROUP1_BASE + SMP_CORE3_OFFSET + SET0);
	ipi_set0_regs[8] = (व्योम *)
		(SMP_CORE_GROUP2_BASE + SMP_CORE0_OFFSET + SET0);
	ipi_set0_regs[9] = (व्योम *)
		(SMP_CORE_GROUP2_BASE + SMP_CORE1_OFFSET + SET0);
	ipi_set0_regs[10] = (व्योम *)
		(SMP_CORE_GROUP2_BASE + SMP_CORE2_OFFSET + SET0);
	ipi_set0_regs[11] = (व्योम *)
		(SMP_CORE_GROUP2_BASE + SMP_CORE3_OFFSET + SET0);
	ipi_set0_regs[12] = (व्योम *)
		(SMP_CORE_GROUP3_BASE + SMP_CORE0_OFFSET + SET0);
	ipi_set0_regs[13] = (व्योम *)
		(SMP_CORE_GROUP3_BASE + SMP_CORE1_OFFSET + SET0);
	ipi_set0_regs[14] = (व्योम *)
		(SMP_CORE_GROUP3_BASE + SMP_CORE2_OFFSET + SET0);
	ipi_set0_regs[15] = (व्योम *)
		(SMP_CORE_GROUP3_BASE + SMP_CORE3_OFFSET + SET0);
पूर्ण

अटल व्योम ipi_clear0_regs_init(व्योम)
अणु
	ipi_clear0_regs[0] = (व्योम *)
		(SMP_CORE_GROUP0_BASE + SMP_CORE0_OFFSET + CLEAR0);
	ipi_clear0_regs[1] = (व्योम *)
		(SMP_CORE_GROUP0_BASE + SMP_CORE1_OFFSET + CLEAR0);
	ipi_clear0_regs[2] = (व्योम *)
		(SMP_CORE_GROUP0_BASE + SMP_CORE2_OFFSET + CLEAR0);
	ipi_clear0_regs[3] = (व्योम *)
		(SMP_CORE_GROUP0_BASE + SMP_CORE3_OFFSET + CLEAR0);
	ipi_clear0_regs[4] = (व्योम *)
		(SMP_CORE_GROUP1_BASE + SMP_CORE0_OFFSET + CLEAR0);
	ipi_clear0_regs[5] = (व्योम *)
		(SMP_CORE_GROUP1_BASE + SMP_CORE1_OFFSET + CLEAR0);
	ipi_clear0_regs[6] = (व्योम *)
		(SMP_CORE_GROUP1_BASE + SMP_CORE2_OFFSET + CLEAR0);
	ipi_clear0_regs[7] = (व्योम *)
		(SMP_CORE_GROUP1_BASE + SMP_CORE3_OFFSET + CLEAR0);
	ipi_clear0_regs[8] = (व्योम *)
		(SMP_CORE_GROUP2_BASE + SMP_CORE0_OFFSET + CLEAR0);
	ipi_clear0_regs[9] = (व्योम *)
		(SMP_CORE_GROUP2_BASE + SMP_CORE1_OFFSET + CLEAR0);
	ipi_clear0_regs[10] = (व्योम *)
		(SMP_CORE_GROUP2_BASE + SMP_CORE2_OFFSET + CLEAR0);
	ipi_clear0_regs[11] = (व्योम *)
		(SMP_CORE_GROUP2_BASE + SMP_CORE3_OFFSET + CLEAR0);
	ipi_clear0_regs[12] = (व्योम *)
		(SMP_CORE_GROUP3_BASE + SMP_CORE0_OFFSET + CLEAR0);
	ipi_clear0_regs[13] = (व्योम *)
		(SMP_CORE_GROUP3_BASE + SMP_CORE1_OFFSET + CLEAR0);
	ipi_clear0_regs[14] = (व्योम *)
		(SMP_CORE_GROUP3_BASE + SMP_CORE2_OFFSET + CLEAR0);
	ipi_clear0_regs[15] = (व्योम *)
		(SMP_CORE_GROUP3_BASE + SMP_CORE3_OFFSET + CLEAR0);
पूर्ण

अटल व्योम ipi_status0_regs_init(व्योम)
अणु
	ipi_status0_regs[0] = (व्योम *)
		(SMP_CORE_GROUP0_BASE + SMP_CORE0_OFFSET + STATUS0);
	ipi_status0_regs[1] = (व्योम *)
		(SMP_CORE_GROUP0_BASE + SMP_CORE1_OFFSET + STATUS0);
	ipi_status0_regs[2] = (व्योम *)
		(SMP_CORE_GROUP0_BASE + SMP_CORE2_OFFSET + STATUS0);
	ipi_status0_regs[3] = (व्योम *)
		(SMP_CORE_GROUP0_BASE + SMP_CORE3_OFFSET + STATUS0);
	ipi_status0_regs[4] = (व्योम *)
		(SMP_CORE_GROUP1_BASE + SMP_CORE0_OFFSET + STATUS0);
	ipi_status0_regs[5] = (व्योम *)
		(SMP_CORE_GROUP1_BASE + SMP_CORE1_OFFSET + STATUS0);
	ipi_status0_regs[6] = (व्योम *)
		(SMP_CORE_GROUP1_BASE + SMP_CORE2_OFFSET + STATUS0);
	ipi_status0_regs[7] = (व्योम *)
		(SMP_CORE_GROUP1_BASE + SMP_CORE3_OFFSET + STATUS0);
	ipi_status0_regs[8] = (व्योम *)
		(SMP_CORE_GROUP2_BASE + SMP_CORE0_OFFSET + STATUS0);
	ipi_status0_regs[9] = (व्योम *)
		(SMP_CORE_GROUP2_BASE + SMP_CORE1_OFFSET + STATUS0);
	ipi_status0_regs[10] = (व्योम *)
		(SMP_CORE_GROUP2_BASE + SMP_CORE2_OFFSET + STATUS0);
	ipi_status0_regs[11] = (व्योम *)
		(SMP_CORE_GROUP2_BASE + SMP_CORE3_OFFSET + STATUS0);
	ipi_status0_regs[12] = (व्योम *)
		(SMP_CORE_GROUP3_BASE + SMP_CORE0_OFFSET + STATUS0);
	ipi_status0_regs[13] = (व्योम *)
		(SMP_CORE_GROUP3_BASE + SMP_CORE1_OFFSET + STATUS0);
	ipi_status0_regs[14] = (व्योम *)
		(SMP_CORE_GROUP3_BASE + SMP_CORE2_OFFSET + STATUS0);
	ipi_status0_regs[15] = (व्योम *)
		(SMP_CORE_GROUP3_BASE + SMP_CORE3_OFFSET + STATUS0);
पूर्ण

अटल व्योम ipi_en0_regs_init(व्योम)
अणु
	ipi_en0_regs[0] = (व्योम *)
		(SMP_CORE_GROUP0_BASE + SMP_CORE0_OFFSET + EN0);
	ipi_en0_regs[1] = (व्योम *)
		(SMP_CORE_GROUP0_BASE + SMP_CORE1_OFFSET + EN0);
	ipi_en0_regs[2] = (व्योम *)
		(SMP_CORE_GROUP0_BASE + SMP_CORE2_OFFSET + EN0);
	ipi_en0_regs[3] = (व्योम *)
		(SMP_CORE_GROUP0_BASE + SMP_CORE3_OFFSET + EN0);
	ipi_en0_regs[4] = (व्योम *)
		(SMP_CORE_GROUP1_BASE + SMP_CORE0_OFFSET + EN0);
	ipi_en0_regs[5] = (व्योम *)
		(SMP_CORE_GROUP1_BASE + SMP_CORE1_OFFSET + EN0);
	ipi_en0_regs[6] = (व्योम *)
		(SMP_CORE_GROUP1_BASE + SMP_CORE2_OFFSET + EN0);
	ipi_en0_regs[7] = (व्योम *)
		(SMP_CORE_GROUP1_BASE + SMP_CORE3_OFFSET + EN0);
	ipi_en0_regs[8] = (व्योम *)
		(SMP_CORE_GROUP2_BASE + SMP_CORE0_OFFSET + EN0);
	ipi_en0_regs[9] = (व्योम *)
		(SMP_CORE_GROUP2_BASE + SMP_CORE1_OFFSET + EN0);
	ipi_en0_regs[10] = (व्योम *)
		(SMP_CORE_GROUP2_BASE + SMP_CORE2_OFFSET + EN0);
	ipi_en0_regs[11] = (व्योम *)
		(SMP_CORE_GROUP2_BASE + SMP_CORE3_OFFSET + EN0);
	ipi_en0_regs[12] = (व्योम *)
		(SMP_CORE_GROUP3_BASE + SMP_CORE0_OFFSET + EN0);
	ipi_en0_regs[13] = (व्योम *)
		(SMP_CORE_GROUP3_BASE + SMP_CORE1_OFFSET + EN0);
	ipi_en0_regs[14] = (व्योम *)
		(SMP_CORE_GROUP3_BASE + SMP_CORE2_OFFSET + EN0);
	ipi_en0_regs[15] = (व्योम *)
		(SMP_CORE_GROUP3_BASE + SMP_CORE3_OFFSET + EN0);
पूर्ण

अटल व्योम ipi_mailbox_buf_init(व्योम)
अणु
	ipi_mailbox_buf[0] = (व्योम *)
		(SMP_CORE_GROUP0_BASE + SMP_CORE0_OFFSET + BUF);
	ipi_mailbox_buf[1] = (व्योम *)
		(SMP_CORE_GROUP0_BASE + SMP_CORE1_OFFSET + BUF);
	ipi_mailbox_buf[2] = (व्योम *)
		(SMP_CORE_GROUP0_BASE + SMP_CORE2_OFFSET + BUF);
	ipi_mailbox_buf[3] = (व्योम *)
		(SMP_CORE_GROUP0_BASE + SMP_CORE3_OFFSET + BUF);
	ipi_mailbox_buf[4] = (व्योम *)
		(SMP_CORE_GROUP1_BASE + SMP_CORE0_OFFSET + BUF);
	ipi_mailbox_buf[5] = (व्योम *)
		(SMP_CORE_GROUP1_BASE + SMP_CORE1_OFFSET + BUF);
	ipi_mailbox_buf[6] = (व्योम *)
		(SMP_CORE_GROUP1_BASE + SMP_CORE2_OFFSET + BUF);
	ipi_mailbox_buf[7] = (व्योम *)
		(SMP_CORE_GROUP1_BASE + SMP_CORE3_OFFSET + BUF);
	ipi_mailbox_buf[8] = (व्योम *)
		(SMP_CORE_GROUP2_BASE + SMP_CORE0_OFFSET + BUF);
	ipi_mailbox_buf[9] = (व्योम *)
		(SMP_CORE_GROUP2_BASE + SMP_CORE1_OFFSET + BUF);
	ipi_mailbox_buf[10] = (व्योम *)
		(SMP_CORE_GROUP2_BASE + SMP_CORE2_OFFSET + BUF);
	ipi_mailbox_buf[11] = (व्योम *)
		(SMP_CORE_GROUP2_BASE + SMP_CORE3_OFFSET + BUF);
	ipi_mailbox_buf[12] = (व्योम *)
		(SMP_CORE_GROUP3_BASE + SMP_CORE0_OFFSET + BUF);
	ipi_mailbox_buf[13] = (व्योम *)
		(SMP_CORE_GROUP3_BASE + SMP_CORE1_OFFSET + BUF);
	ipi_mailbox_buf[14] = (व्योम *)
		(SMP_CORE_GROUP3_BASE + SMP_CORE2_OFFSET + BUF);
	ipi_mailbox_buf[15] = (व्योम *)
		(SMP_CORE_GROUP3_BASE + SMP_CORE3_OFFSET + BUF);
पूर्ण

/*
 * Simple enough, just poke the appropriate ipi रेजिस्टर
 */
अटल व्योम loongson3_send_ipi_single(पूर्णांक cpu, अचिन्हित पूर्णांक action)
अणु
	ipi_ग_लिखो_action(cpu_logical_map(cpu), (u32)action);
पूर्ण

अटल व्योम
loongson3_send_ipi_mask(स्थिर काष्ठा cpumask *mask, अचिन्हित पूर्णांक action)
अणु
	अचिन्हित पूर्णांक i;

	क्रम_each_cpu(i, mask)
		ipi_ग_लिखो_action(cpu_logical_map(i), (u32)action);
पूर्ण


अटल irqवापस_t loongson3_ipi_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	पूर्णांक i, cpu = smp_processor_id();
	अचिन्हित पूर्णांक action, c0count;

	action = ipi_पढ़ो_clear(cpu);

	अगर (action & SMP_RESCHEDULE_YOURSELF)
		scheduler_ipi();

	अगर (action & SMP_CALL_FUNCTION) अणु
		irq_enter();
		generic_smp_call_function_पूर्णांकerrupt();
		irq_निकास();
	पूर्ण

	अगर (action & SMP_ASK_C0COUNT) अणु
		BUG_ON(cpu != 0);
		c0count = पढ़ो_c0_count();
		c0count = c0count ? c0count : 1;
		क्रम (i = 1; i < nr_cpu_ids; i++)
			core0_c0count[i] = c0count;
		__wbflush(); /* Let others see the result ASAP */
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

#घोषणा MAX_LOOPS 800
/*
 * SMP init and finish on secondary CPUs
 */
अटल व्योम loongson3_init_secondary(व्योम)
अणु
	पूर्णांक i;
	uपूर्णांक32_t initcount;
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	अचिन्हित पूर्णांक imask = STATUSF_IP7 | STATUSF_IP6 |
			     STATUSF_IP3 | STATUSF_IP2;

	/* Set पूर्णांकerrupt mask, but करोn't enable */
	change_c0_status(ST0_IM, imask);
	ipi_ग_लिखो_enable(cpu);

	per_cpu(cpu_state, cpu) = CPU_ONLINE;
	cpu_set_core(&cpu_data[cpu],
		     cpu_logical_map(cpu) % loongson_sysconf.cores_per_package);
	cpu_data[cpu].package =
		cpu_logical_map(cpu) / loongson_sysconf.cores_per_package;

	i = 0;
	core0_c0count[cpu] = 0;
	loongson3_send_ipi_single(0, SMP_ASK_C0COUNT);
	जबतक (!core0_c0count[cpu]) अणु
		i++;
		cpu_relax();
	पूर्ण

	अगर (i > MAX_LOOPS)
		i = MAX_LOOPS;
	अगर (cpu_data[cpu].package)
		initcount = core0_c0count[cpu] + i;
	अन्यथा /* Local access is faster क्रम loops */
		initcount = core0_c0count[cpu] + i/2;

	ग_लिखो_c0_count(initcount);
पूर्ण

अटल व्योम loongson3_smp_finish(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();

	ग_लिखो_c0_compare(पढ़ो_c0_count() + mips_hpt_frequency/HZ);
	local_irq_enable();
	ipi_clear_buf(cpu);

	pr_info("CPU#%d finished, CP0_ST=%x\n",
			smp_processor_id(), पढ़ो_c0_status());
पूर्ण

अटल व्योम __init loongson3_smp_setup(व्योम)
अणु
	पूर्णांक i = 0, num = 0; /* i: physical id, num: logical id */

	init_cpu_possible(cpu_none_mask);

	/* For unअगरied kernel, NR_CPUS is the maximum possible value,
	 * loongson_sysconf.nr_cpus is the really present value
	 */
	जबतक (i < loongson_sysconf.nr_cpus) अणु
		अगर (loongson_sysconf.reserved_cpus_mask & (1<<i)) अणु
			/* Reserved physical CPU cores */
			__cpu_number_map[i] = -1;
		पूर्ण अन्यथा अणु
			__cpu_number_map[i] = num;
			__cpu_logical_map[num] = i;
			set_cpu_possible(num, true);
			/* Loongson processors are always grouped by 4 */
			cpu_set_cluster(&cpu_data[num], i / 4);
			num++;
		पूर्ण
		i++;
	पूर्ण
	pr_info("Detected %i available CPU(s)\n", num);

	जबतक (num < loongson_sysconf.nr_cpus) अणु
		__cpu_logical_map[num] = -1;
		num++;
	पूर्ण

	csr_ipi_probe();
	ipi_set0_regs_init();
	ipi_clear0_regs_init();
	ipi_status0_regs_init();
	ipi_en0_regs_init();
	ipi_mailbox_buf_init();
	ipi_ग_लिखो_enable(0);

	cpu_set_core(&cpu_data[0],
		     cpu_logical_map(0) % loongson_sysconf.cores_per_package);
	cpu_data[0].package = cpu_logical_map(0) / loongson_sysconf.cores_per_package;
पूर्ण

अटल व्योम __init loongson3_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	अगर (request_irq(LS_IPI_IRQ, loongson3_ipi_पूर्णांकerrupt,
			IRQF_PERCPU | IRQF_NO_SUSPEND, "SMP_IPI", शून्य))
		pr_err("Failed to request IPI IRQ\n");
	init_cpu_present(cpu_possible_mask);
	per_cpu(cpu_state, smp_processor_id()) = CPU_ONLINE;
पूर्ण

/*
 * Setup the PC, SP, and GP of a secondary processor and start it runing!
 */
अटल पूर्णांक loongson3_boot_secondary(पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	pr_info("Booting CPU#%d...\n", cpu);

	ipi_ग_लिखो_buf(cpu, idle);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU

अटल पूर्णांक loongson3_cpu_disable(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	set_cpu_online(cpu, false);
	calculate_cpu_क्रमeign_map();
	local_irq_save(flags);
	irq_cpu_offline();
	clear_c0_status(ST0_IM);
	local_irq_restore(flags);
	local_flush_tlb_all();

	वापस 0;
पूर्ण


अटल व्योम loongson3_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	जबतक (per_cpu(cpu_state, cpu) != CPU_DEAD)
		cpu_relax();

	mb();
पूर्ण

/* To shutकरोwn a core in Loongson 3, the target core should go to CKSEG1 and
 * flush all L1 entries at first. Then, another core (usually Core 0) can
 * safely disable the घड़ी of the target core. loongson3_play_dead() is
 * called via CKSEG1 (uncached and unmmaped)
 */
अटल व्योम loongson3_type1_play_dead(पूर्णांक *state_addr)
अणु
	रेजिस्टर पूर्णांक val;
	रेजिस्टर दीर्घ cpuid, core, node, count;
	रेजिस्टर व्योम *addr, *base, *initfunc;

	__यंत्र__ __अस्थिर__(
		"   .set push                     \n"
		"   .set noreorder                \n"
		"   li %[addr], 0x80000000        \n" /* KSEG0 */
		"1: cache 0, 0(%[addr])           \n" /* flush L1 ICache */
		"   cache 0, 1(%[addr])           \n"
		"   cache 0, 2(%[addr])           \n"
		"   cache 0, 3(%[addr])           \n"
		"   cache 1, 0(%[addr])           \n" /* flush L1 DCache */
		"   cache 1, 1(%[addr])           \n"
		"   cache 1, 2(%[addr])           \n"
		"   cache 1, 3(%[addr])           \n"
		"   addiu %[sets], %[sets], -1    \n"
		"   bnez  %[sets], 1b             \n"
		"   addiu %[addr], %[addr], 0x20  \n"
		"   li    %[val], 0x7             \n" /* *state_addr = CPU_DEAD; */
		"   sw    %[val], (%[state_addr]) \n"
		"   sync                          \n"
		"   cache 21, (%[state_addr])     \n" /* flush entry of *state_addr */
		"   .set pop                      \n"
		: [addr] "=&r" (addr), [val] "=&r" (val)
		: [state_addr] "r" (state_addr),
		  [sets] "r" (cpu_data[smp_processor_id()].dcache.sets));

	__यंत्र__ __अस्थिर__(
		"   .set push                         \n"
		"   .set noreorder                    \n"
		"   .set mips64                       \n"
		"   mfc0  %[cpuid], $15, 1            \n"
		"   andi  %[cpuid], 0x3ff             \n"
		"   dli   %[base], 0x900000003ff01000 \n"
		"   andi  %[core], %[cpuid], 0x3      \n"
		"   sll   %[core], 8                  \n" /* get core id */
		"   or    %[base], %[base], %[core]   \n"
		"   andi  %[node], %[cpuid], 0xc      \n"
		"   dsll  %[node], 42                 \n" /* get node id */
		"   or    %[base], %[base], %[node]   \n"
		"1: li    %[count], 0x100             \n" /* रुको क्रम init loop */
		"2: bnez  %[count], 2b                \n" /* limit mailbox access */
		"   addiu %[count], -1                \n"
		"   ld    %[initfunc], 0x20(%[base])  \n" /* get PC via mailbox */
		"   beqz  %[initfunc], 1b             \n"
		"   nop                               \n"
		"   ld    $sp, 0x28(%[base])          \n" /* get SP via mailbox */
		"   ld    $gp, 0x30(%[base])          \n" /* get GP via mailbox */
		"   ld    $a1, 0x38(%[base])          \n"
		"   jr    %[initfunc]                 \n" /* jump to initial PC */
		"   nop                               \n"
		"   .set pop                          \n"
		: [core] "=&r" (core), [node] "=&r" (node),
		  [base] "=&r" (base), [cpuid] "=&r" (cpuid),
		  [count] "=&r" (count), [initfunc] "=&r" (initfunc)
		: /* No Input */
		: "a1");
पूर्ण

अटल व्योम loongson3_type2_play_dead(पूर्णांक *state_addr)
अणु
	रेजिस्टर पूर्णांक val;
	रेजिस्टर दीर्घ cpuid, core, node, count;
	रेजिस्टर व्योम *addr, *base, *initfunc;

	__यंत्र__ __अस्थिर__(
		"   .set push                     \n"
		"   .set noreorder                \n"
		"   li %[addr], 0x80000000        \n" /* KSEG0 */
		"1: cache 0, 0(%[addr])           \n" /* flush L1 ICache */
		"   cache 0, 1(%[addr])           \n"
		"   cache 0, 2(%[addr])           \n"
		"   cache 0, 3(%[addr])           \n"
		"   cache 1, 0(%[addr])           \n" /* flush L1 DCache */
		"   cache 1, 1(%[addr])           \n"
		"   cache 1, 2(%[addr])           \n"
		"   cache 1, 3(%[addr])           \n"
		"   addiu %[sets], %[sets], -1    \n"
		"   bnez  %[sets], 1b             \n"
		"   addiu %[addr], %[addr], 0x20  \n"
		"   li    %[val], 0x7             \n" /* *state_addr = CPU_DEAD; */
		"   sw    %[val], (%[state_addr]) \n"
		"   sync                          \n"
		"   cache 21, (%[state_addr])     \n" /* flush entry of *state_addr */
		"   .set pop                      \n"
		: [addr] "=&r" (addr), [val] "=&r" (val)
		: [state_addr] "r" (state_addr),
		  [sets] "r" (cpu_data[smp_processor_id()].dcache.sets));

	__यंत्र__ __अस्थिर__(
		"   .set push                         \n"
		"   .set noreorder                    \n"
		"   .set mips64                       \n"
		"   mfc0  %[cpuid], $15, 1            \n"
		"   andi  %[cpuid], 0x3ff             \n"
		"   dli   %[base], 0x900000003ff01000 \n"
		"   andi  %[core], %[cpuid], 0x3      \n"
		"   sll   %[core], 8                  \n" /* get core id */
		"   or    %[base], %[base], %[core]   \n"
		"   andi  %[node], %[cpuid], 0xc      \n"
		"   dsll  %[node], 42                 \n" /* get node id */
		"   or    %[base], %[base], %[node]   \n"
		"   dsrl  %[node], 30                 \n" /* 15:14 */
		"   or    %[base], %[base], %[node]   \n"
		"1: li    %[count], 0x100             \n" /* रुको क्रम init loop */
		"2: bnez  %[count], 2b                \n" /* limit mailbox access */
		"   addiu %[count], -1                \n"
		"   ld    %[initfunc], 0x20(%[base])  \n" /* get PC via mailbox */
		"   beqz  %[initfunc], 1b             \n"
		"   nop                               \n"
		"   ld    $sp, 0x28(%[base])          \n" /* get SP via mailbox */
		"   ld    $gp, 0x30(%[base])          \n" /* get GP via mailbox */
		"   ld    $a1, 0x38(%[base])          \n"
		"   jr    %[initfunc]                 \n" /* jump to initial PC */
		"   nop                               \n"
		"   .set pop                          \n"
		: [core] "=&r" (core), [node] "=&r" (node),
		  [base] "=&r" (base), [cpuid] "=&r" (cpuid),
		  [count] "=&r" (count), [initfunc] "=&r" (initfunc)
		: /* No Input */
		: "a1");
पूर्ण

अटल व्योम loongson3_type3_play_dead(पूर्णांक *state_addr)
अणु
	रेजिस्टर पूर्णांक val;
	रेजिस्टर दीर्घ cpuid, core, node, count;
	रेजिस्टर व्योम *addr, *base, *initfunc;

	__यंत्र__ __अस्थिर__(
		"   .set push                     \n"
		"   .set noreorder                \n"
		"   li %[addr], 0x80000000        \n" /* KSEG0 */
		"1: cache 0, 0(%[addr])           \n" /* flush L1 ICache */
		"   cache 0, 1(%[addr])           \n"
		"   cache 0, 2(%[addr])           \n"
		"   cache 0, 3(%[addr])           \n"
		"   cache 1, 0(%[addr])           \n" /* flush L1 DCache */
		"   cache 1, 1(%[addr])           \n"
		"   cache 1, 2(%[addr])           \n"
		"   cache 1, 3(%[addr])           \n"
		"   addiu %[sets], %[sets], -1    \n"
		"   bnez  %[sets], 1b             \n"
		"   addiu %[addr], %[addr], 0x40  \n"
		"   li %[addr], 0x80000000        \n" /* KSEG0 */
		"2: cache 2, 0(%[addr])           \n" /* flush L1 VCache */
		"   cache 2, 1(%[addr])           \n"
		"   cache 2, 2(%[addr])           \n"
		"   cache 2, 3(%[addr])           \n"
		"   cache 2, 4(%[addr])           \n"
		"   cache 2, 5(%[addr])           \n"
		"   cache 2, 6(%[addr])           \n"
		"   cache 2, 7(%[addr])           \n"
		"   cache 2, 8(%[addr])           \n"
		"   cache 2, 9(%[addr])           \n"
		"   cache 2, 10(%[addr])          \n"
		"   cache 2, 11(%[addr])          \n"
		"   cache 2, 12(%[addr])          \n"
		"   cache 2, 13(%[addr])          \n"
		"   cache 2, 14(%[addr])          \n"
		"   cache 2, 15(%[addr])          \n"
		"   addiu %[vsets], %[vsets], -1  \n"
		"   bnez  %[vsets], 2b            \n"
		"   addiu %[addr], %[addr], 0x40  \n"
		"   li    %[val], 0x7             \n" /* *state_addr = CPU_DEAD; */
		"   sw    %[val], (%[state_addr]) \n"
		"   sync                          \n"
		"   cache 21, (%[state_addr])     \n" /* flush entry of *state_addr */
		"   .set pop                      \n"
		: [addr] "=&r" (addr), [val] "=&r" (val)
		: [state_addr] "r" (state_addr),
		  [sets] "r" (cpu_data[smp_processor_id()].dcache.sets),
		  [vsets] "r" (cpu_data[smp_processor_id()].vcache.sets));

	__यंत्र__ __अस्थिर__(
		"   .set push                         \n"
		"   .set noreorder                    \n"
		"   .set mips64                       \n"
		"   mfc0  %[cpuid], $15, 1            \n"
		"   andi  %[cpuid], 0x3ff             \n"
		"   dli   %[base], 0x900000003ff01000 \n"
		"   andi  %[core], %[cpuid], 0x3      \n"
		"   sll   %[core], 8                  \n" /* get core id */
		"   or    %[base], %[base], %[core]   \n"
		"   andi  %[node], %[cpuid], 0xc      \n"
		"   dsll  %[node], 42                 \n" /* get node id */
		"   or    %[base], %[base], %[node]   \n"
		"1: li    %[count], 0x100             \n" /* रुको क्रम init loop */
		"2: bnez  %[count], 2b                \n" /* limit mailbox access */
		"   addiu %[count], -1                \n"
		"   lw    %[initfunc], 0x20(%[base])  \n" /* check lower 32-bit as jump indicator */
		"   beqz  %[initfunc], 1b             \n"
		"   nop                               \n"
		"   ld    %[initfunc], 0x20(%[base])  \n" /* get PC (whole 64-bit) via mailbox */
		"   ld    $sp, 0x28(%[base])          \n" /* get SP via mailbox */
		"   ld    $gp, 0x30(%[base])          \n" /* get GP via mailbox */
		"   ld    $a1, 0x38(%[base])          \n"
		"   jr    %[initfunc]                 \n" /* jump to initial PC */
		"   nop                               \n"
		"   .set pop                          \n"
		: [core] "=&r" (core), [node] "=&r" (node),
		  [base] "=&r" (base), [cpuid] "=&r" (cpuid),
		  [count] "=&r" (count), [initfunc] "=&r" (initfunc)
		: /* No Input */
		: "a1");
पूर्ण

व्योम play_dead(व्योम)
अणु
	पूर्णांक prid_imp, prid_rev, *state_addr;
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	व्योम (*play_dead_at_ckseg1)(पूर्णांक *);

	idle_task_निकास();

	prid_imp = पढ़ो_c0_prid() & PRID_IMP_MASK;
	prid_rev = पढ़ो_c0_prid() & PRID_REV_MASK;

	अगर (prid_imp == PRID_IMP_LOONGSON_64G) अणु
		play_dead_at_ckseg1 =
			(व्योम *)CKSEG1ADDR((अचिन्हित दीर्घ)loongson3_type3_play_dead);
		जाओ out;
	पूर्ण

	चयन (prid_rev) अणु
	हाल PRID_REV_LOONGSON3A_R1:
	शेष:
		play_dead_at_ckseg1 =
			(व्योम *)CKSEG1ADDR((अचिन्हित दीर्घ)loongson3_type1_play_dead);
		अवरोध;
	हाल PRID_REV_LOONGSON3B_R1:
	हाल PRID_REV_LOONGSON3B_R2:
		play_dead_at_ckseg1 =
			(व्योम *)CKSEG1ADDR((अचिन्हित दीर्घ)loongson3_type2_play_dead);
		अवरोध;
	हाल PRID_REV_LOONGSON3A_R2_0:
	हाल PRID_REV_LOONGSON3A_R2_1:
	हाल PRID_REV_LOONGSON3A_R3_0:
	हाल PRID_REV_LOONGSON3A_R3_1:
		play_dead_at_ckseg1 =
			(व्योम *)CKSEG1ADDR((अचिन्हित दीर्घ)loongson3_type3_play_dead);
		अवरोध;
	पूर्ण

out:
	state_addr = &per_cpu(cpu_state, cpu);
	mb();
	play_dead_at_ckseg1(state_addr);
पूर्ण

अटल पूर्णांक loongson3_disable_घड़ी(अचिन्हित पूर्णांक cpu)
अणु
	uपूर्णांक64_t core_id = cpu_core(&cpu_data[cpu]);
	uपूर्णांक64_t package_id = cpu_data[cpu].package;

	अगर ((पढ़ो_c0_prid() & PRID_REV_MASK) == PRID_REV_LOONGSON3A_R1) अणु
		LOONGSON_CHIPCFG(package_id) &= ~(1 << (12 + core_id));
	पूर्ण अन्यथा अणु
		अगर (!(loongson_sysconf.workarounds & WORKAROUND_CPUHOTPLUG))
			LOONGSON_FREQCTRL(package_id) &= ~(1 << (core_id * 4 + 3));
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक loongson3_enable_घड़ी(अचिन्हित पूर्णांक cpu)
अणु
	uपूर्णांक64_t core_id = cpu_core(&cpu_data[cpu]);
	uपूर्णांक64_t package_id = cpu_data[cpu].package;

	अगर ((पढ़ो_c0_prid() & PRID_REV_MASK) == PRID_REV_LOONGSON3A_R1) अणु
		LOONGSON_CHIPCFG(package_id) |= 1 << (12 + core_id);
	पूर्ण अन्यथा अणु
		अगर (!(loongson_sysconf.workarounds & WORKAROUND_CPUHOTPLUG))
			LOONGSON_FREQCTRL(package_id) |= 1 << (core_id * 4 + 3);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक रेजिस्टर_loongson3_notअगरier(व्योम)
अणु
	वापस cpuhp_setup_state_nocalls(CPUHP_MIPS_SOC_PREPARE,
					 "mips/loongson:prepare",
					 loongson3_enable_घड़ी,
					 loongson3_disable_घड़ी);
पूर्ण
early_initcall(रेजिस्टर_loongson3_notअगरier);

#पूर्ण_अगर

स्थिर काष्ठा plat_smp_ops loongson3_smp_ops = अणु
	.send_ipi_single = loongson3_send_ipi_single,
	.send_ipi_mask = loongson3_send_ipi_mask,
	.init_secondary = loongson3_init_secondary,
	.smp_finish = loongson3_smp_finish,
	.boot_secondary = loongson3_boot_secondary,
	.smp_setup = loongson3_smp_setup,
	.prepare_cpus = loongson3_prepare_cpus,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_disable = loongson3_cpu_disable,
	.cpu_die = loongson3_cpu_die,
#पूर्ण_अगर
#अगर_घोषित CONFIG_KEXEC
	.kexec_nonboot_cpu = kexec_nonboot_cpu_jump,
#पूर्ण_अगर
पूर्ण;
