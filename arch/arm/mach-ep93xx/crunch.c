<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/kernel/crunch.c
 * Cirrus MaverickCrunch context चयनing and handling
 *
 * Copyright (C) 2006 Lennert Buytenhek <buytenh@wantstofly.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/thपढ़ो_notअगरy.h>

#समावेश "soc.h"

काष्ठा crunch_state *crunch_owner;

व्योम crunch_task_release(काष्ठा thपढ़ो_info *thपढ़ो)
अणु
	local_irq_disable();
	अगर (crunch_owner == &thपढ़ो->crunchstate)
		crunch_owner = शून्य;
	local_irq_enable();
पूर्ण

अटल पूर्णांक crunch_enabled(u32 devcfg)
अणु
	वापस !!(devcfg & EP93XX_SYSCON_DEVCFG_CPENA);
पूर्ण

अटल पूर्णांक crunch_करो(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ cmd, व्योम *t)
अणु
	काष्ठा thपढ़ो_info *thपढ़ो = (काष्ठा thपढ़ो_info *)t;
	काष्ठा crunch_state *crunch_state;
	u32 devcfg;

	crunch_state = &thपढ़ो->crunchstate;

	चयन (cmd) अणु
	हाल THREAD_NOTIFY_FLUSH:
		स_रखो(crunch_state, 0, माप(*crunch_state));

		/*
		 * FALLTHROUGH: Ensure we करोn't try to overग_लिखो our newly
		 * initialised state inक्रमmation on the first fault.
		 */
		fallthrough;

	हाल THREAD_NOTIFY_EXIT:
		crunch_task_release(thपढ़ो);
		अवरोध;

	हाल THREAD_NOTIFY_SWITCH:
		devcfg = __raw_पढ़ोl(EP93XX_SYSCON_DEVCFG);
		अगर (crunch_enabled(devcfg) || crunch_owner == crunch_state) अणु
			/*
			 * We करोn't use ep93xx_syscon_swlocked_ग_लिखो() here
			 * because we are on the context चयन path and
			 * preemption is alपढ़ोy disabled.
			 */
			devcfg ^= EP93XX_SYSCON_DEVCFG_CPENA;
			__raw_ग_लिखोl(0xaa, EP93XX_SYSCON_SWLOCK);
			__raw_ग_लिखोl(devcfg, EP93XX_SYSCON_DEVCFG);
		पूर्ण
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block crunch_notअगरier_block = अणु
	.notअगरier_call	= crunch_करो,
पूर्ण;

पूर्णांक __init crunch_init(व्योम)
अणु
	thपढ़ो_रेजिस्टर_notअगरier(&crunch_notअगरier_block);
	elf_hwcap |= HWCAP_CRUNCH;

	वापस 0;
पूर्ण
