<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001, 06 by Ralf Baechle (ralf@linux-mips.org)
 * Copyright (C) 2001 MIPS Technologies, Inc.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/pm.h>
#समावेश <linux/types.h>
#समावेश <linux/reboot.h>
#समावेश <linux/delay.h>

#समावेश <यंत्र/compiler.h>
#समावेश <यंत्र/idle.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/reboot.h>

/*
 * Urgs ...  Too many MIPS machines to handle this in a generic way.
 * So handle all using function poपूर्णांकers to machine specअगरic
 * functions.
 */
व्योम (*_machine_restart)(अक्षर *command);
व्योम (*_machine_halt)(व्योम);
व्योम (*pm_घातer_off)(व्योम);

EXPORT_SYMBOL(pm_घातer_off);

अटल व्योम machine_hang(व्योम)
अणु
	/*
	 * We're hanging the system so we don't want to be पूर्णांकerrupted anymore.
	 * Any पूर्णांकerrupt handlers that ran would at best be useless & at worst
	 * go awry because the प्रणाली isn't in a functional state.
	 */
	local_irq_disable();

	/*
	 * Mask all पूर्णांकerrupts, giving us a better chance of reमुख्यing in the
	 * low घातer रुको state.
	 */
	clear_c0_status(ST0_IM);

	जबतक (true) अणु
		अगर (cpu_has_mips_r) अणु
			/*
			 * We know that the रुको inकाष्ठाion is supported so
			 * make use of it directly, leaving पूर्णांकerrupts
			 * disabled.
			 */
			यंत्र अस्थिर(
				".set	push\n\t"
				".set	" MIPS_ISA_ARCH_LEVEL "\n\t"
				"wait\n\t"
				".set	pop");
		पूर्ण अन्यथा अगर (cpu_रुको) अणु
			/*
			 * Try the cpu_रुको() callback. This isn't ideal since
			 * it'll re-enable पूर्णांकerrupts, but that ought to be
			 * harmless given that they're all masked.
			 */
			cpu_रुको();
			local_irq_disable();
		पूर्ण अन्यथा अणु
			/*
			 * We're going to burn some घातer running round the
			 * loop, but we करोn't really have a choice. This isn't
			 * a path we should expect to run क्रम दीर्घ during
			 * typical use anyway.
			 */
		पूर्ण

		/*
		 * In most modern MIPS CPUs पूर्णांकerrupts will cause the रुको
		 * inकाष्ठाion to graduate even when disabled, and in some
		 * हालs even when masked. In order to prevent a समयr
		 * पूर्णांकerrupt from continuously taking us out of the low घातer
		 * रुको state, we clear any pending समयr पूर्णांकerrupt here.
		 */
		अगर (cpu_has_counter)
			ग_लिखो_c0_compare(0);
	पूर्ण
पूर्ण

व्योम machine_restart(अक्षर *command)
अणु
	अगर (_machine_restart)
		_machine_restart(command);

#अगर_घोषित CONFIG_SMP
	preempt_disable();
	smp_send_stop();
#पूर्ण_अगर
	करो_kernel_restart(command);
	mdelay(1000);
	pr_emerg("Reboot failed -- System halted\n");
	machine_hang();
पूर्ण

व्योम machine_halt(व्योम)
अणु
	अगर (_machine_halt)
		_machine_halt();

#अगर_घोषित CONFIG_SMP
	preempt_disable();
	smp_send_stop();
#पूर्ण_अगर
	machine_hang();
पूर्ण

व्योम machine_घातer_off(व्योम)
अणु
	अगर (pm_घातer_off)
		pm_घातer_off();

#अगर_घोषित CONFIG_SMP
	preempt_disable();
	smp_send_stop();
#पूर्ण_अगर
	machine_hang();
पूर्ण
