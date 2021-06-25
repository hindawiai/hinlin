<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Common घातerpc suspend code क्रम 32 and 64 bits
 *
 * Copyright 2007	Johannes Berg <johannes@sipsolutions.net>
 */

#समावेश <linux/sched.h>
#समावेश <linux/suspend.h>
#समावेश <यंत्र/current.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/चयन_to.h>

व्योम save_processor_state(व्योम)
अणु
	/*
	 * flush out all the special रेजिस्टरs so we करोn't need
	 * to save them in the snapshot
	 */
	flush_all_to_thपढ़ो(current);

#अगर_घोषित CONFIG_PPC64
	hard_irq_disable();
#पूर्ण_अगर

पूर्ण

व्योम restore_processor_state(व्योम)
अणु
#अगर_घोषित CONFIG_PPC32
	चयन_mmu_context(current->active_mm, current->active_mm, शून्य);
#पूर्ण_अगर
पूर्ण
