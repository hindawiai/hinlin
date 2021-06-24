<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/pm.h>
#समावेश <linux/kexec.h>
#समावेश <linux/kernel.h>
#समावेश <linux/reboot.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/watchकरोg.h>
#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/traps.h>

व्योम (*pm_घातer_off)(व्योम);
EXPORT_SYMBOL(pm_घातer_off);

अटल व्योम watchकरोg_trigger_immediate(व्योम)
अणु
	sh_wdt_ग_लिखो_cnt(0xFF);
	sh_wdt_ग_लिखो_csr(0xC2);
पूर्ण

अटल व्योम native_machine_restart(अक्षर * __unused)
अणु
	local_irq_disable();

	/* Destroy all of the TLBs in preparation क्रम reset by MMU */
	__flush_tlb_global();

	/* Address error with SR.BL=1 first. */
	trigger_address_error();

	/* If that fails or is unsupported, go क्रम the watchकरोg next. */
	watchकरोg_trigger_immediate();

	/*
	 * Give up and sleep.
	 */
	जबतक (1)
		cpu_sleep();
पूर्ण

अटल व्योम native_machine_shutकरोwn(व्योम)
अणु
	smp_send_stop();
पूर्ण

अटल व्योम native_machine_घातer_off(व्योम)
अणु
	अगर (pm_घातer_off)
		pm_घातer_off();
पूर्ण

अटल व्योम native_machine_halt(व्योम)
अणु
	/* stop other cpus */
	machine_shutकरोwn();

	/* stop this cpu */
	stop_this_cpu(शून्य);
पूर्ण

काष्ठा machine_ops machine_ops = अणु
	.घातer_off	= native_machine_घातer_off,
	.shutकरोwn	= native_machine_shutकरोwn,
	.restart	= native_machine_restart,
	.halt		= native_machine_halt,
#अगर_घोषित CONFIG_KEXEC
	.crash_shutकरोwn = native_machine_crash_shutकरोwn,
#पूर्ण_अगर
पूर्ण;

व्योम machine_घातer_off(व्योम)
अणु
	machine_ops.घातer_off();
पूर्ण

व्योम machine_shutकरोwn(व्योम)
अणु
	machine_ops.shutकरोwn();
पूर्ण

व्योम machine_restart(अक्षर *cmd)
अणु
	machine_ops.restart(cmd);
पूर्ण

व्योम machine_halt(व्योम)
अणु
	machine_ops.halt();
पूर्ण

#अगर_घोषित CONFIG_KEXEC
व्योम machine_crash_shutकरोwn(काष्ठा pt_regs *regs)
अणु
	machine_ops.crash_shutकरोwn(regs);
पूर्ण
#पूर्ण_अगर
