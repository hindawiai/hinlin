<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SH-X3 SMP
 *
 *  Copyright (C) 2007 - 2010  Paul Mundt
 *  Copyright (C) 2007  Magnus Damm
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/smp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/cpu.h>
#समावेश <यंत्र/sections.h>

#घोषणा STBCR_REG(phys_id) (0xfe400004 | (phys_id << 12))
#घोषणा RESET_REG(phys_id) (0xfe400008 | (phys_id << 12))

#घोषणा STBCR_MSTP	0x00000001
#घोषणा STBCR_RESET	0x00000002
#घोषणा STBCR_SLEEP	0x00000004
#घोषणा STBCR_LTSLP	0x80000000

अटल irqवापस_t ipi_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *arg)
अणु
	अचिन्हित पूर्णांक message = (अचिन्हित पूर्णांक)(दीर्घ)arg;
	अचिन्हित पूर्णांक cpu = hard_smp_processor_id();
	अचिन्हित पूर्णांक offs = 4 * cpu;
	अचिन्हित पूर्णांक x;

	x = __raw_पढ़ोl(0xfe410070 + offs); /* C0INITICI..CnINTICI */
	x &= (1 << (message << 2));
	__raw_ग_लिखोl(x, 0xfe410080 + offs); /* C0INTICICLR..CnINTICICLR */

	smp_message_recv(message);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम shx3_smp_setup(व्योम)
अणु
	अचिन्हित पूर्णांक cpu = 0;
	पूर्णांक i, num;

	init_cpu_possible(cpumask_of(cpu));

	/* Enable light sleep क्रम the boot CPU */
	__raw_ग_लिखोl(__raw_पढ़ोl(STBCR_REG(cpu)) | STBCR_LTSLP, STBCR_REG(cpu));

	__cpu_number_map[0] = 0;
	__cpu_logical_map[0] = 0;

	/*
	 * Do this stupidly क्रम now.. we करोn't have an easy way to probe
	 * क्रम the total number of cores.
	 */
	क्रम (i = 1, num = 0; i < NR_CPUS; i++) अणु
		set_cpu_possible(i, true);
		__cpu_number_map[i] = ++num;
		__cpu_logical_map[num] = i;
	पूर्ण

        prपूर्णांकk(KERN_INFO "Detected %i available secondary CPU(s)\n", num);
पूर्ण

अटल व्योम shx3_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	पूर्णांक i;

	BUILD_BUG_ON(SMP_MSG_NR >= 8);

	क्रम (i = 0; i < SMP_MSG_NR; i++)
		request_irq(104 + i, ipi_पूर्णांकerrupt_handler,
			    IRQF_PERCPU, "IPI", (व्योम *)(दीर्घ)i);

	क्रम (i = 0; i < max_cpus; i++)
		set_cpu_present(i, true);
पूर्ण

अटल व्योम shx3_start_cpu(अचिन्हित पूर्णांक cpu, अचिन्हित दीर्घ entry_poपूर्णांक)
अणु
	अगर (__in_29bit_mode())
		__raw_ग_लिखोl(entry_poपूर्णांक, RESET_REG(cpu));
	अन्यथा
		__raw_ग_लिखोl(virt_to_phys(entry_poपूर्णांक), RESET_REG(cpu));

	अगर (!(__raw_पढ़ोl(STBCR_REG(cpu)) & STBCR_MSTP))
		__raw_ग_लिखोl(STBCR_MSTP, STBCR_REG(cpu));

	जबतक (!(__raw_पढ़ोl(STBCR_REG(cpu)) & STBCR_MSTP))
		cpu_relax();

	/* Start up secondary processor by sending a reset */
	__raw_ग_लिखोl(STBCR_RESET | STBCR_LTSLP, STBCR_REG(cpu));
पूर्ण

अटल अचिन्हित पूर्णांक shx3_smp_processor_id(व्योम)
अणु
	वापस __raw_पढ़ोl(0xff000048); /* CPIDR */
पूर्ण

अटल व्योम shx3_send_ipi(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक message)
अणु
	अचिन्हित दीर्घ addr = 0xfe410070 + (cpu * 4);

	BUG_ON(cpu >= 4);

	__raw_ग_लिखोl(1 << (message << 2), addr); /* C0INTICI..CnINTICI */
पूर्ण

अटल व्योम shx3_update_boot_vector(अचिन्हित पूर्णांक cpu)
अणु
	__raw_ग_लिखोl(STBCR_MSTP, STBCR_REG(cpu));
	जबतक (!(__raw_पढ़ोl(STBCR_REG(cpu)) & STBCR_MSTP))
		cpu_relax();
	__raw_ग_लिखोl(STBCR_RESET, STBCR_REG(cpu));
पूर्ण

अटल पूर्णांक shx3_cpu_prepare(अचिन्हित पूर्णांक cpu)
अणु
	shx3_update_boot_vector(cpu);
	वापस 0;
पूर्ण

अटल पूर्णांक रेजिस्टर_shx3_cpu_notअगरier(व्योम)
अणु
	cpuhp_setup_state_nocalls(CPUHP_SH_SH3X_PREPARE, "sh/shx3:prepare",
				  shx3_cpu_prepare, शून्य);
	वापस 0;
पूर्ण
late_initcall(रेजिस्टर_shx3_cpu_notअगरier);

काष्ठा plat_smp_ops shx3_smp_ops = अणु
	.smp_setup		= shx3_smp_setup,
	.prepare_cpus		= shx3_prepare_cpus,
	.start_cpu		= shx3_start_cpu,
	.smp_processor_id	= shx3_smp_processor_id,
	.send_ipi		= shx3_send_ipi,
	.cpu_die		= native_cpu_die,
	.cpu_disable		= native_cpu_disable,
	.play_dead		= native_play_dead,
पूर्ण;
