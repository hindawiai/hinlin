<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* leon_pmc.c: LEON Power-करोwn cpu_idle() handler
 *
 * Copyright (C) 2011 Daniel Hellstrom (daniel@gaisler.com) Aeroflex Gaisler AB
 */

#समावेश <linux/init.h>
#समावेश <linux/pm.h>

#समावेश <यंत्र/leon_amba.h>
#समावेश <यंत्र/cpu_type.h>
#समावेश <यंत्र/leon.h>
#समावेश <यंत्र/processor.h>

/* List of Systems that need fixup inकाष्ठाions around घातer-करोwn inकाष्ठाion */
अटल अचिन्हित पूर्णांक pmc_leon_fixup_ids[] = अणु
	AEROFLEX_UT699,
	GAISLER_GR712RC,
	LEON4_NEXTREME1,
	0
पूर्ण;

अटल पूर्णांक pmc_leon_need_fixup(व्योम)
अणु
	अचिन्हित पूर्णांक प्रणालीid = amba_प्रणाली_id >> 16;
	अचिन्हित पूर्णांक *id;

	id = &pmc_leon_fixup_ids[0];
	जबतक (*id != 0) अणु
		अगर (*id == प्रणालीid)
			वापस 1;
		id++;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * CPU idle callback function क्रम प्रणालीs that need some extra handling
 * See .../arch/sparc/kernel/process.c
 */
अटल व्योम pmc_leon_idle_fixup(व्योम)
अणु
	/* Prepare an address to a non-cachable region. APB is always
	 * none-cachable. One inकाष्ठाion is executed after the Sleep
	 * inकाष्ठाion, we make sure to पढ़ो the bus and throw away the
	 * value by accessing a non-cachable area, also we make sure the
	 * MMU करोes not get a TLB miss here by using the MMU BYPASS ASI.
	 */
	रेजिस्टर अचिन्हित पूर्णांक address = (अचिन्हित पूर्णांक)leon3_irqctrl_regs;

	/* Interrupts need to be enabled to not hang the CPU */
	raw_local_irq_enable();

	__यंत्र__ __अस्थिर__ (
		"wr	%%g0, %%asr19\n"
		"lda	[%0] %1, %%g0\n"
		:
		: "r"(address), "i"(ASI_LEON_BYPASS));
पूर्ण

/*
 * CPU idle callback function
 * See .../arch/sparc/kernel/process.c
 */
अटल व्योम pmc_leon_idle(व्योम)
अणु
	/* Interrupts need to be enabled to not hang the CPU */
	raw_local_irq_enable();

	/* For प्रणालीs without घातer-करोwn, this will be no-op */
	__यंत्र__ __अस्थिर__ ("wr	%g0, %asr19\n\t");
पूर्ण

/* Install LEON Power Down function */
अटल पूर्णांक __init leon_pmc_install(व्योम)
अणु
	अगर (sparc_cpu_model == sparc_leon) अणु
		/* Assign घातer management IDLE handler */
		अगर (pmc_leon_need_fixup())
			sparc_idle = pmc_leon_idle_fixup;
		अन्यथा
			sparc_idle = pmc_leon_idle;

		prपूर्णांकk(KERN_INFO "leon: power management initialized\n");
	पूर्ण

	वापस 0;
पूर्ण

/* This driver is not critical to the boot process, करोn't care
 * अगर initialized late.
 */
late_initcall(leon_pmc_install);
