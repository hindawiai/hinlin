<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/kernel/pj4-cp0.c
 *
 * PJ4 iWMMXt coprocessor context चयनing and handling
 *
 * Copyright (c) 2010 Marvell International Inc.
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/thपढ़ो_notअगरy.h>
#समावेश <यंत्र/cputype.h>

अटल पूर्णांक iwmmxt_करो(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ cmd, व्योम *t)
अणु
	काष्ठा thपढ़ो_info *thपढ़ो = t;

	चयन (cmd) अणु
	हाल THREAD_NOTIFY_FLUSH:
		/*
		 * flush_thपढ़ो() zeroes thपढ़ो->fpstate, so no need
		 * to करो anything here.
		 *
		 * FALLTHROUGH: Ensure we करोn't try to overग_लिखो our newly
		 * initialised state inक्रमmation on the first fault.
		 */

	हाल THREAD_NOTIFY_EXIT:
		iwmmxt_task_release(thपढ़ो);
		अवरोध;

	हाल THREAD_NOTIFY_SWITCH:
		iwmmxt_task_चयन(thपढ़ो);
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block __maybe_unused iwmmxt_notअगरier_block = अणु
	.notअगरier_call	= iwmmxt_करो,
पूर्ण;


अटल u32 __init pj4_cp_access_पढ़ो(व्योम)
अणु
	u32 value;

	__यंत्र__ __अस्थिर__ (
		"mrc	p15, 0, %0, c1, c0, 2\n\t"
		: "=r" (value));
	वापस value;
पूर्ण

अटल व्योम __init pj4_cp_access_ग_लिखो(u32 value)
अणु
	u32 temp;

	__यंत्र__ __अस्थिर__ (
		"mcr	p15, 0, %1, c1, c0, 2\n\t"
#अगर_घोषित CONFIG_THUMB2_KERNEL
		"isb\n\t"
#अन्यथा
		"mrc	p15, 0, %0, c1, c0, 2\n\t"
		"mov	%0, %0\n\t"
		"sub	pc, pc, #4\n\t"
#पूर्ण_अगर
		: "=r" (temp) : "r" (value));
पूर्ण

अटल पूर्णांक __init pj4_get_iwmmxt_version(व्योम)
अणु
	u32 cp_access, wcid;

	cp_access = pj4_cp_access_पढ़ो();
	pj4_cp_access_ग_लिखो(cp_access | 0xf);

	/* check अगर coprocessor 0 and 1 are available */
	अगर ((pj4_cp_access_पढ़ो() & 0xf) != 0xf) अणु
		pj4_cp_access_ग_लिखो(cp_access);
		वापस -ENODEV;
	पूर्ण

	/* पढ़ो iWMMXt coprocessor id रेजिस्टर p1, c0 */
	__यंत्र__ __अस्थिर__ ("mrc    p1, 0, %0, c0, c0, 0\n" : "=r" (wcid));

	pj4_cp_access_ग_लिखो(cp_access);

	/* iWMMXt v1 */
	अगर ((wcid & 0xffffff00) == 0x56051000)
		वापस 1;
	/* iWMMXt v2 */
	अगर ((wcid & 0xffffff00) == 0x56052000)
		वापस 2;

	वापस -EINVAL;
पूर्ण

/*
 * Disable CP0/CP1 on boot, and let call_fpe() and the iWMMXt lazy
 * चयन code handle iWMMXt context चयनing.
 */
अटल पूर्णांक __init pj4_cp0_init(व्योम)
अणु
	u32 __maybe_unused cp_access;
	पूर्णांक vers;

	अगर (!cpu_is_pj4())
		वापस 0;

	vers = pj4_get_iwmmxt_version();
	अगर (vers < 0)
		वापस 0;

#अगर_अघोषित CONFIG_IWMMXT
	pr_info("PJ4 iWMMXt coprocessor detected, but kernel support is missing.\n");
#अन्यथा
	cp_access = pj4_cp_access_पढ़ो() & ~0xf;
	pj4_cp_access_ग_लिखो(cp_access);

	pr_info("PJ4 iWMMXt v%d coprocessor enabled.\n", vers);
	elf_hwcap |= HWCAP_IWMMXT;
	thपढ़ो_रेजिस्टर_notअगरier(&iwmmxt_notअगरier_block);
#पूर्ण_अगर

	वापस 0;
पूर्ण

late_initcall(pj4_cp0_init);
