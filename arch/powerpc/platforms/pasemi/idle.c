<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2006-2007 PA Semi, Inc
 *
 * Maपूर्णांकained by: Olof Johansson <olof@lixom.net>
 */

#अघोषित DEBUG

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/irq.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/smp.h>

#समावेश "pasemi.h"

काष्ठा sleep_mode अणु
	अक्षर *name;
	व्योम (*entry)(व्योम);
पूर्ण;

अटल काष्ठा sleep_mode modes[] = अणु
	अणु .name = "spin", .entry = &idle_spin पूर्ण,
	अणु .name = "doze", .entry = &idle_करोze पूर्ण,
पूर्ण;

अटल पूर्णांक current_mode = 0;

अटल पूर्णांक pasemi_प्रणाली_reset_exception(काष्ठा pt_regs *regs)
अणु
	/* If we were woken up from घातer savings, we need to वापस
	 * to the calling function, since nip is not saved across
	 * all modes.
	 */

	अगर (regs->msr & SRR1_WAKEMASK)
		regs->nip = regs->link;

	चयन (regs->msr & SRR1_WAKEMASK) अणु
	हाल SRR1_WAKEDEC:
		set_dec(1);
	हाल SRR1_WAKEEE:
		/*
		 * Handle these when पूर्णांकerrupts get re-enabled and we take
		 * them as regular exceptions. We are in an NMI context
		 * and can't handle these here.
		 */
		अवरोध;
	शेष:
		/* करो प्रणाली reset */
		वापस 0;
	पूर्ण

	/* Set higher astate since we come out of घातer savings at 0 */
	restore_astate(hard_smp_processor_id());

	/* everything handled */
	regs->msr |= MSR_RI;
	वापस 1;
पूर्ण

अटल पूर्णांक __init pasemi_idle_init(व्योम)
अणु
#अगर_अघोषित CONFIG_PPC_PASEMI_CPUFREQ
	pr_warn("No cpufreq driver, powersavings modes disabled\n");
	current_mode = 0;
#पूर्ण_अगर

	ppc_md.प्रणाली_reset_exception = pasemi_प्रणाली_reset_exception;
	ppc_md.घातer_save = modes[current_mode].entry;
	pr_info("Using PA6T idle loop (%s)\n", modes[current_mode].name);

	वापस 0;
पूर्ण
machine_late_initcall(pasemi, pasemi_idle_init);

अटल पूर्णांक __init idle_param(अक्षर *p)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < ARRAY_SIZE(modes); i++) अणु
		अगर (!म_भेद(modes[i].name, p)) अणु
			current_mode = i;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

early_param("idle", idle_param);
