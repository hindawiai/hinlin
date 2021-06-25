<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Idle daemon क्रम PowerPC.  Idle daemon will handle any action
 * that needs to be taken when the प्रणाली becomes idle.
 *
 * Originally written by Cort Dougan (cort@cs.nmt.edu).
 * Subsequent 32-bit hacking by Tom Rini, Armin Kuster,
 * Paul Mackerras and others.
 *
 * iSeries supported added by Mike Corrigan <mikejc@us.ibm.com>
 *
 * Additional shared processor, SMT, and firmware support
 *    Copyright (c) 2003 Dave Engebretsen <engebret@us.ibm.com>
 *
 * 32-bit and 64-bit versions merged by Paul Mackerras <paulus@samba.org>
 */

#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/smp.h>
#समावेश <linux/cpu.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/tick.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/runlatch.h>
#समावेश <यंत्र/smp.h>


अचिन्हित दीर्घ cpuidle_disable = IDLE_NO_OVERRIDE;
EXPORT_SYMBOL(cpuidle_disable);

अटल पूर्णांक __init घातersave_off(अक्षर *arg)
अणु
	ppc_md.घातer_save = शून्य;
	cpuidle_disable = IDLE_POWERSAVE_OFF;
	वापस 0;
पूर्ण
__setup("powersave=off", घातersave_off);

व्योम arch_cpu_idle(व्योम)
अणु
	ppc64_runlatch_off();

	अगर (ppc_md.घातer_save) अणु
		ppc_md.घातer_save();
		/*
		 * Some घातer_save functions वापस with
		 * पूर्णांकerrupts enabled, some करोn't.
		 */
		अगर (irqs_disabled())
			raw_local_irq_enable();
	पूर्ण अन्यथा अणु
		raw_local_irq_enable();
		/*
		 * Go पूर्णांकo low thपढ़ो priority and possibly
		 * low घातer mode.
		 */
		HMT_low();
		HMT_very_low();
	पूर्ण

	HMT_medium();
	ppc64_runlatch_on();
पूर्ण

पूर्णांक घातersave_nap;

#अगर_घोषित CONFIG_PPC_970_NAP
व्योम घातer4_idle(व्योम)
अणु
	अगर (!cpu_has_feature(CPU_FTR_CAN_NAP))
		वापस;

	अगर (!घातersave_nap)
		वापस;

	अगर (!prep_irq_क्रम_idle())
		वापस;

	अगर (cpu_has_feature(CPU_FTR_ALTIVEC))
		यंत्र अस्थिर("DSSALL ; sync" ::: "memory");

	घातer4_idle_nap();

	/*
	 * घातer4_idle_nap वापसs with पूर्णांकerrupts enabled (soft and hard).
	 * to our caller with पूर्णांकerrupts enabled (soft and hard). Our caller
	 * can cope with either पूर्णांकerrupts disabled or enabled upon वापस.
	 */
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SYSCTL
/*
 * Register the sysctl to set/clear घातersave_nap.
 */
अटल काष्ठा ctl_table घातersave_nap_ctl_table[] = अणु
	अणु
		.procname	= "powersave-nap",
		.data		= &घातersave_nap,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
अटल काष्ठा ctl_table घातersave_nap_sysctl_root[] = अणु
	अणु
		.procname	= "kernel",
		.mode		= 0555,
		.child		= घातersave_nap_ctl_table,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक __init
रेजिस्टर_घातersave_nap_sysctl(व्योम)
अणु
	रेजिस्टर_sysctl_table(घातersave_nap_sysctl_root);

	वापस 0;
पूर्ण
__initcall(रेजिस्टर_घातersave_nap_sysctl);
#पूर्ण_अगर
