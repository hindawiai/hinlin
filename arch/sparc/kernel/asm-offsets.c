<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This program is used to generate definitions needed by
 * assembly language modules.
 *
 * We use the technique used in the OSF Mach kernel code:
 * generate यंत्र statements containing #घोषणाs,
 * compile this file to assembler, and then extract the
 * #घोषणाs from the assembly-language output.
 *
 * On sparc, thपढ़ो_info data is अटल and TI_XXX offsets are computed by hand.
 */

#समावेश <linux/sched.h>
#समावेश <linux/mm_types.h>
// #समावेश <linux/mm.h>
#समावेश <linux/kbuild.h>

#समावेश <यंत्र/hibernate.h>

#अगर_घोषित CONFIG_SPARC32
पूर्णांक sparc32_foo(व्योम)
अणु
	DEFINE(AOFF_thपढ़ो_विभाजन_kpsr,
			दुरत्व(काष्ठा thपढ़ो_काष्ठा, विभाजन_kpsr));
	वापस 0;
पूर्ण
#अन्यथा
पूर्णांक sparc64_foo(व्योम)
अणु
#अगर_घोषित CONFIG_HIBERNATION
	BLANK();
	OFFSET(SC_REG_FP, saved_context, fp);
	OFFSET(SC_REG_CWP, saved_context, cwp);
	OFFSET(SC_REG_WSTATE, saved_context, wstate);

	OFFSET(SC_REG_TICK, saved_context, tick);
	OFFSET(SC_REG_PSTATE, saved_context, pstate);

	OFFSET(SC_REG_G4, saved_context, g4);
	OFFSET(SC_REG_G5, saved_context, g5);
	OFFSET(SC_REG_G6, saved_context, g6);
#पूर्ण_अगर
	वापस 0;
पूर्ण
#पूर्ण_अगर

पूर्णांक foo(व्योम)
अणु
	BLANK();
	DEFINE(AOFF_task_thपढ़ो, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो));
	BLANK();
	DEFINE(AOFF_mm_context, दुरत्व(काष्ठा mm_काष्ठा, context));
	BLANK();
	DEFINE(VMA_VM_MM,    दुरत्व(काष्ठा vm_area_काष्ठा, vm_mm));

	/* DEFINE(NUM_USER_SEGMENTS, TASK_SIZE>>28); */
	वापस 0;
पूर्ण

