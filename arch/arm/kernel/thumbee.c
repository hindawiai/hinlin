<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/kernel/thumbee.c
 *
 * Copyright (C) 2008 ARM Limited
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/प्रणाली_info.h>
#समावेश <यंत्र/thपढ़ो_notअगरy.h>

/*
 * Access to the ThumbEE Handler Base रेजिस्टर
 */
अटल अंतरभूत अचिन्हित दीर्घ teehbr_पढ़ो(व्योम)
अणु
	अचिन्हित दीर्घ v;
	यंत्र("mrc	p14, 6, %0, c1, c0, 0\n" : "=r" (v));
	वापस v;
पूर्ण

अटल अंतरभूत व्योम teehbr_ग_लिखो(अचिन्हित दीर्घ v)
अणु
	यंत्र("mcr	p14, 6, %0, c1, c0, 0\n" : : "r" (v));
पूर्ण

अटल पूर्णांक thumbee_notअगरier(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ cmd, व्योम *t)
अणु
	काष्ठा thपढ़ो_info *thपढ़ो = t;

	चयन (cmd) अणु
	हाल THREAD_NOTIFY_FLUSH:
		teehbr_ग_लिखो(0);
		अवरोध;
	हाल THREAD_NOTIFY_SWITCH:
		current_thपढ़ो_info()->thumbee_state = teehbr_पढ़ो();
		teehbr_ग_लिखो(thपढ़ो->thumbee_state);
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block thumbee_notअगरier_block = अणु
	.notअगरier_call	= thumbee_notअगरier,
पूर्ण;

अटल पूर्णांक __init thumbee_init(व्योम)
अणु
	अचिन्हित दीर्घ pfr0;
	अचिन्हित पूर्णांक cpu_arch = cpu_architecture();

	अगर (cpu_arch < CPU_ARCH_ARMv7)
		वापस 0;

	pfr0 = पढ़ो_cpuid_ext(CPUID_EXT_PFR0);
	अगर ((pfr0 & 0x0000f000) != 0x00001000)
		वापस 0;

	pr_info("ThumbEE CPU extension supported.\n");
	elf_hwcap |= HWCAP_THUMBEE;
	thपढ़ो_रेजिस्टर_notअगरier(&thumbee_notअगरier_block);

	वापस 0;
पूर्ण

late_initcall(thumbee_init);
