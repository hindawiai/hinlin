<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MIPS idle loop and WAIT inकाष्ठाion support.
 *
 * Copyright (C) xxxx  the Anonymous
 * Copyright (C) 1994 - 2006 Ralf Baechle
 * Copyright (C) 2003, 2004  Maciej W. Rozycki
 * Copyright (C) 2001, 2004, 2011, 2012	 MIPS Technologies, Inc.
 */
#समावेश <linux/cpu.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/sched.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cpu-info.h>
#समावेश <यंत्र/cpu-type.h>
#समावेश <यंत्र/idle.h>
#समावेश <यंत्र/mipsregs.h>

/*
 * Not all of the MIPS CPUs have the "wait" inकाष्ठाion available. Moreover,
 * the implementation of the "wait" feature dअगरfers between CPU families. This
 * poपूर्णांकs to the function that implements CPU specअगरic रुको.
 * The रुको inकाष्ठाion stops the pipeline and reduces the घातer consumption of
 * the CPU very much.
 */
व्योम (*cpu_रुको)(व्योम);
EXPORT_SYMBOL(cpu_रुको);

अटल व्योम __cpuidle r3081_रुको(व्योम)
अणु
	अचिन्हित दीर्घ cfg = पढ़ो_c0_conf();
	ग_लिखो_c0_conf(cfg | R30XX_CONF_HALT);
	raw_local_irq_enable();
पूर्ण

अटल व्योम __cpuidle r39xx_रुको(व्योम)
अणु
	अगर (!need_resched())
		ग_लिखो_c0_conf(पढ़ो_c0_conf() | TX39_CONF_HALT);
	raw_local_irq_enable();
पूर्ण

व्योम __cpuidle r4k_रुको(व्योम)
अणु
	raw_local_irq_enable();
	__r4k_रुको();
पूर्ण

/*
 * This variant is preferable as it allows testing need_resched and going to
 * sleep depending on the outcome atomically.  Unक्रमtunately the "It is
 * implementation-dependent whether the pipeline restarts when a non-enabled
 * पूर्णांकerrupt is requested" restriction in the MIPS32/MIPS64 architecture makes
 * using this version a gamble.
 */
व्योम __cpuidle r4k_रुको_irqoff(व्योम)
अणु
	अगर (!need_resched())
		__यंत्र__(
		"	.set	push		\n"
		"	.set	arch=r4000	\n"
		"	wait			\n"
		"	.set	pop		\n");
	raw_local_irq_enable();
पूर्ण

/*
 * The RM7000 variant has to handle erratum 38.	 The workaround is to not
 * have any pending stores when the WAIT inकाष्ठाion is executed.
 */
अटल व्योम __cpuidle rm7k_रुको_irqoff(व्योम)
अणु
	अगर (!need_resched())
		__यंत्र__(
		"	.set	push					\n"
		"	.set	arch=r4000				\n"
		"	.set	noat					\n"
		"	mfc0	$1, $12					\n"
		"	sync						\n"
		"	mtc0	$1, $12		# stalls until W stage	\n"
		"	wait						\n"
		"	mtc0	$1, $12		# stalls until W stage	\n"
		"	.set	pop					\n");
	raw_local_irq_enable();
पूर्ण

/*
 * Au1 'wait' is only useful when the 32kHz counter is used as समयr,
 * since coreघड़ी (and the cp0 counter) stops upon executing it. Only an
 * पूर्णांकerrupt can wake it, so they must be enabled beक्रमe entering idle modes.
 */
अटल व्योम __cpuidle au1k_रुको(व्योम)
अणु
	अचिन्हित दीर्घ c0status = पढ़ो_c0_status() | 1;	/* irqs on */

	__यंत्र__(
	"	.set	push			\n"
	"	.set	arch=r4000		\n"
	"	cache	0x14, 0(%0)		\n"
	"	cache	0x14, 32(%0)		\n"
	"	sync				\n"
	"	mtc0	%1, $12			\n" /* wr c0status */
	"	wait				\n"
	"	nop				\n"
	"	nop				\n"
	"	nop				\n"
	"	nop				\n"
	"	.set	pop			\n"
	: : "r" (au1k_रुको), "r" (c0status));
पूर्ण

अटल पूर्णांक __initdata noरुको;

अटल पूर्णांक __init रुको_disable(अक्षर *s)
अणु
	noरुको = 1;

	वापस 1;
पूर्ण

__setup("nowait", रुको_disable);

व्योम __init check_रुको(व्योम)
अणु
	काष्ठा cpuinfo_mips *c = &current_cpu_data;

	अगर (noरुको) अणु
		prपूर्णांकk("Wait instruction disabled.\n");
		वापस;
	पूर्ण

	/*
	 * MIPSr6 specअगरies that masked पूर्णांकerrupts should unblock an executing
	 * रुको inकाष्ठाion, and thus that it is safe क्रम us to use
	 * r4k_रुको_irqoff. Yippee!
	 */
	अगर (cpu_has_mips_r6) अणु
		cpu_रुको = r4k_रुको_irqoff;
		वापस;
	पूर्ण

	चयन (current_cpu_type()) अणु
	हाल CPU_R3081:
	हाल CPU_R3081E:
		cpu_रुको = r3081_रुको;
		अवरोध;
	हाल CPU_TX3927:
		cpu_रुको = r39xx_रुको;
		अवरोध;
	हाल CPU_R4200:
/*	हाल CPU_R4300: */
	हाल CPU_R4600:
	हाल CPU_R4640:
	हाल CPU_R4650:
	हाल CPU_R4700:
	हाल CPU_R5000:
	हाल CPU_R5500:
	हाल CPU_NEVADA:
	हाल CPU_4KC:
	हाल CPU_4KEC:
	हाल CPU_4KSC:
	हाल CPU_5KC:
	हाल CPU_5KE:
	हाल CPU_25KF:
	हाल CPU_PR4450:
	हाल CPU_BMIPS3300:
	हाल CPU_BMIPS4350:
	हाल CPU_BMIPS4380:
	हाल CPU_CAVIUM_OCTEON:
	हाल CPU_CAVIUM_OCTEON_PLUS:
	हाल CPU_CAVIUM_OCTEON2:
	हाल CPU_CAVIUM_OCTEON3:
	हाल CPU_XBURST:
	हाल CPU_LOONGSON32:
	हाल CPU_XLR:
	हाल CPU_XLP:
		cpu_रुको = r4k_रुको;
		अवरोध;
	हाल CPU_LOONGSON64:
		अगर ((c->processor_id & (PRID_IMP_MASK | PRID_REV_MASK)) >=
				(PRID_IMP_LOONGSON_64C | PRID_REV_LOONGSON3A_R2_0) ||
				(c->processor_id & PRID_IMP_MASK) == PRID_IMP_LOONGSON_64R)
			cpu_रुको = r4k_रुको;
		अवरोध;

	हाल CPU_BMIPS5000:
		cpu_रुको = r4k_रुको_irqoff;
		अवरोध;
	हाल CPU_RM7000:
		cpu_रुको = rm7k_रुको_irqoff;
		अवरोध;

	हाल CPU_PROAPTIV:
	हाल CPU_P5600:
		/*
		 * Incoming Fast Debug Channel (FDC) data during a रुको
		 * inकाष्ठाion causes the रुको never to resume, even अगर an
		 * पूर्णांकerrupt is received. Aव्योम using रुको at all अगर FDC data is
		 * likely to be received.
		 */
		अगर (IS_ENABLED(CONFIG_MIPS_EJTAG_FDC_TTY))
			अवरोध;
		fallthrough;
	हाल CPU_M14KC:
	हाल CPU_M14KEC:
	हाल CPU_24K:
	हाल CPU_34K:
	हाल CPU_1004K:
	हाल CPU_1074K:
	हाल CPU_INTERAPTIV:
	हाल CPU_M5150:
	हाल CPU_QEMU_GENERIC:
		cpu_रुको = r4k_रुको;
		अगर (पढ़ो_c0_config7() & MIPS_CONF7_WII)
			cpu_रुको = r4k_रुको_irqoff;
		अवरोध;

	हाल CPU_74K:
		cpu_रुको = r4k_रुको;
		अगर ((c->processor_id & 0xff) >= PRID_REV_ENCODE_332(2, 1, 0))
			cpu_रुको = r4k_रुको_irqoff;
		अवरोध;

	हाल CPU_TX49XX:
		cpu_रुको = r4k_रुको_irqoff;
		अवरोध;
	हाल CPU_ALCHEMY:
		cpu_रुको = au1k_रुको;
		अवरोध;
	हाल CPU_20KC:
		/*
		 * WAIT on Rev1.0 has E1, E2, E3 and E16.
		 * WAIT on Rev2.0 and Rev3.0 has E16.
		 * Rev3.1 WAIT is nop, why bother
		 */
		अगर ((c->processor_id & 0xff) <= 0x64)
			अवरोध;

		/*
		 * Another rev is incremeting c0_count at a reduced घड़ी
		 * rate जबतक in WAIT mode.  So we basically have the choice
		 * between using the cp0 समयr as घड़ीsource or aव्योमing
		 * the WAIT inकाष्ठाion.  Until more details are known,
		 * disable the use of WAIT क्रम 20Kc entirely.
		   cpu_रुको = r4k_रुको;
		 */
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम arch_cpu_idle(व्योम)
अणु
	अगर (cpu_रुको)
		cpu_रुको();
	अन्यथा
		raw_local_irq_enable();
पूर्ण

#अगर_घोषित CONFIG_CPU_IDLE

पूर्णांक mips_cpuidle_रुको_enter(काष्ठा cpuidle_device *dev,
			    काष्ठा cpuidle_driver *drv, पूर्णांक index)
अणु
	arch_cpu_idle();
	वापस index;
पूर्ण

#पूर्ण_अगर
