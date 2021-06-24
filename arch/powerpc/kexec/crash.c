<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Architecture specअगरic (PPC64) functions क्रम kexec based crash dumps.
 *
 * Copyright (C) 2005, IBM Corp.
 *
 * Created by: Haren Myneni
 */

#समावेश <linux/kernel.h>
#समावेश <linux/smp.h>
#समावेश <linux/reboot.h>
#समावेश <linux/kexec.h>
#समावेश <linux/export.h>
#समावेश <linux/crash_dump.h>
#समावेश <linux/delay.h>
#समावेश <linux/irq.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/kexec.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/समलाँघ.स>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/पूर्णांकerrupt.h>

/*
 * The primary CPU रुकोs a जबतक क्रम all secondary CPUs to enter. This is to
 * aव्योम sending an IPI अगर the secondary CPUs are entering
 * crash_kexec_secondary on their own (eg via a प्रणाली reset).
 *
 * The secondary समयout has to be दीर्घer than the primary. Both समयouts are
 * in milliseconds.
 */
#घोषणा PRIMARY_TIMEOUT		500
#घोषणा SECONDARY_TIMEOUT	1000

#घोषणा IPI_TIMEOUT		10000
#घोषणा REAL_MODE_TIMEOUT	10000

अटल पूर्णांक समय_प्रकारo_dump;
/*
 * crash_wake_offline should be set to 1 by platक्रमms that पूर्णांकend to wake
 * up offline cpus prior to jumping to a kdump kernel. Currently घातernv
 * sets it to 1, since we want to aव्योम things from happening when an
 * offline CPU wakes up due to something like an HMI (malfunction error),
 * which propagates to all thपढ़ोs.
 */
पूर्णांक crash_wake_offline;

#घोषणा CRASH_HANDLER_MAX 3
/* List of shutकरोwn handles */
अटल crash_shutकरोwn_t crash_shutकरोwn_handles[CRASH_HANDLER_MAX];
अटल DEFINE_SPINLOCK(crash_handlers_lock);

अटल अचिन्हित दीर्घ crash_shutकरोwn_buf[JMP_BUF_LEN];
अटल पूर्णांक crash_shutकरोwn_cpu = -1;

अटल पूर्णांक handle_fault(काष्ठा pt_regs *regs)
अणु
	अगर (crash_shutकरोwn_cpu == smp_processor_id())
		दीर्घ_लाँघ(crash_shutकरोwn_buf, 1);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SMP

अटल atomic_t cpus_in_crash;
व्योम crash_ipi_callback(काष्ठा pt_regs *regs)
अणु
	अटल cpumask_t cpus_state_saved = CPU_MASK_NONE;

	पूर्णांक cpu = smp_processor_id();

	hard_irq_disable();
	अगर (!cpumask_test_cpu(cpu, &cpus_state_saved)) अणु
		crash_save_cpu(regs, cpu);
		cpumask_set_cpu(cpu, &cpus_state_saved);
	पूर्ण

	atomic_inc(&cpus_in_crash);
	smp_mb__after_atomic();

	/*
	 * Starting the kdump boot.
	 * This barrier is needed to make sure that all CPUs are stopped.
	 */
	जबतक (!समय_प्रकारo_dump)
		cpu_relax();

	अगर (ppc_md.kexec_cpu_करोwn)
		ppc_md.kexec_cpu_करोwn(1, 1);

#अगर_घोषित CONFIG_PPC64
	kexec_smp_रुको();
#अन्यथा
	क्रम (;;);	/* FIXME */
#पूर्ण_अगर

	/* NOTREACHED */
पूर्ण

अटल व्योम crash_kexec_prepare_cpus(पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक msecs;
	अचिन्हित पूर्णांक ncpus = num_online_cpus() - 1;/* Excluding the panic cpu */
	पूर्णांक tries = 0;
	पूर्णांक (*old_handler)(काष्ठा pt_regs *regs);

	prपूर्णांकk(KERN_EMERG "Sending IPI to other CPUs\n");

	अगर (crash_wake_offline)
		ncpus = num_present_cpus() - 1;

	crash_send_ipi(crash_ipi_callback);
	smp_wmb();

again:
	/*
	 * FIXME: Until we will have the way to stop other CPUs reliably,
	 * the crash CPU will send an IPI and रुको क्रम other CPUs to
	 * respond.
	 */
	msecs = IPI_TIMEOUT;
	जबतक ((atomic_पढ़ो(&cpus_in_crash) < ncpus) && (--msecs > 0))
		mdelay(1);

	/* Would it be better to replace the trap vector here? */

	अगर (atomic_पढ़ो(&cpus_in_crash) >= ncpus) अणु
		prपूर्णांकk(KERN_EMERG "IPI complete\n");
		वापस;
	पूर्ण

	prपूर्णांकk(KERN_EMERG "ERROR: %d cpu(s) not responding\n",
		ncpus - atomic_पढ़ो(&cpus_in_crash));

	/*
	 * If we have a panic समयout set then we can't रुको indefinitely
	 * क्रम someone to activate प्रणाली reset. We also give up on the
	 * second समय through अगर प्रणाली reset fail to work.
	 */
	अगर ((panic_समयout > 0) || (tries > 0))
		वापस;

	/*
	 * A प्रणाली reset will cause all CPUs to take an 0x100 exception.
	 * The primary CPU वापसs here via बनाओ_लाँघ, and the secondary
	 * CPUs reexecute the crash_kexec_secondary path.
	 */
	old_handler = __debugger;
	__debugger = handle_fault;
	crash_shutकरोwn_cpu = smp_processor_id();

	अगर (बनाओ_लाँघ(crash_shutकरोwn_buf) == 0) अणु
		prपूर्णांकk(KERN_EMERG "Activate system reset (dumprestart) "
				  "to stop other cpu(s)\n");

		/*
		 * A प्रणाली reset will क्रमce all CPUs to execute the
		 * crash code again. We need to reset cpus_in_crash so we
		 * रुको क्रम everyone to करो this.
		 */
		atomic_set(&cpus_in_crash, 0);
		smp_mb();

		जबतक (atomic_पढ़ो(&cpus_in_crash) < ncpus)
			cpu_relax();
	पूर्ण

	crash_shutकरोwn_cpu = -1;
	__debugger = old_handler;

	tries++;
	जाओ again;
पूर्ण

/*
 * This function will be called by secondary cpus.
 */
व्योम crash_kexec_secondary(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक msecs = SECONDARY_TIMEOUT;

	local_irq_save(flags);

	/* Wait क्रम the primary crash CPU to संकेत its progress */
	जबतक (crashing_cpu < 0) अणु
		अगर (--msecs < 0) अणु
			/* No response, kdump image may not have been loaded */
			local_irq_restore(flags);
			वापस;
		पूर्ण

		mdelay(1);
	पूर्ण

	crash_ipi_callback(regs);
पूर्ण

#अन्यथा	/* ! CONFIG_SMP */

अटल व्योम crash_kexec_prepare_cpus(पूर्णांक cpu)
अणु
	/*
	 * move the secondaries to us so that we can copy
	 * the new kernel 0-0x100 safely
	 *
	 * करो this अगर kexec in setup.c ?
	 */
#अगर_घोषित CONFIG_PPC64
	smp_release_cpus();
#अन्यथा
	/* FIXME */
#पूर्ण_अगर
पूर्ण

व्योम crash_kexec_secondary(काष्ठा pt_regs *regs)
अणु
पूर्ण
#पूर्ण_अगर	/* CONFIG_SMP */

/* रुको क्रम all the CPUs to hit real mode but समयout अगर they करोn't come in */
#अगर defined(CONFIG_SMP) && defined(CONFIG_PPC64)
अटल व्योम __maybe_unused crash_kexec_रुको_realmode(पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक msecs;
	पूर्णांक i;

	msecs = REAL_MODE_TIMEOUT;
	क्रम (i=0; i < nr_cpu_ids && msecs > 0; i++) अणु
		अगर (i == cpu)
			जारी;

		जबतक (paca_ptrs[i]->kexec_state < KEXEC_STATE_REAL_MODE) अणु
			barrier();
			अगर (!cpu_possible(i) || !cpu_online(i) || (msecs <= 0))
				अवरोध;
			msecs--;
			mdelay(1);
		पूर्ण
	पूर्ण
	mb();
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम crash_kexec_रुको_realmode(पूर्णांक cpu) अणुपूर्ण
#पूर्ण_अगर	/* CONFIG_SMP && CONFIG_PPC64 */

/*
 * Register a function to be called on shutकरोwn.  Only use this अगर you
 * can't reset your device in the second kernel.
 */
पूर्णांक crash_shutकरोwn_रेजिस्टर(crash_shutकरोwn_t handler)
अणु
	अचिन्हित पूर्णांक i, rc;

	spin_lock(&crash_handlers_lock);
	क्रम (i = 0 ; i < CRASH_HANDLER_MAX; i++)
		अगर (!crash_shutकरोwn_handles[i]) अणु
			/* Insert handle at first empty entry */
			crash_shutकरोwn_handles[i] = handler;
			rc = 0;
			अवरोध;
		पूर्ण

	अगर (i == CRASH_HANDLER_MAX) अणु
		prपूर्णांकk(KERN_ERR "Crash shutdown handles full, "
		       "not registered.\n");
		rc = 1;
	पूर्ण

	spin_unlock(&crash_handlers_lock);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(crash_shutकरोwn_रेजिस्टर);

पूर्णांक crash_shutकरोwn_unरेजिस्टर(crash_shutकरोwn_t handler)
अणु
	अचिन्हित पूर्णांक i, rc;

	spin_lock(&crash_handlers_lock);
	क्रम (i = 0 ; i < CRASH_HANDLER_MAX; i++)
		अगर (crash_shutकरोwn_handles[i] == handler)
			अवरोध;

	अगर (i == CRASH_HANDLER_MAX) अणु
		prपूर्णांकk(KERN_ERR "Crash shutdown handle not found\n");
		rc = 1;
	पूर्ण अन्यथा अणु
		/* Shअगरt handles करोwn */
		क्रम (; i < (CRASH_HANDLER_MAX - 1); i++)
			crash_shutकरोwn_handles[i] =
				crash_shutकरोwn_handles[i+1];
		/*
		 * Reset last entry to शून्य now that it has been shअगरted करोwn,
		 * this will allow new handles to be added here.
		 */
		crash_shutकरोwn_handles[i] = शून्य;
		rc = 0;
	पूर्ण

	spin_unlock(&crash_handlers_lock);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(crash_shutकरोwn_unरेजिस्टर);

व्योम शेष_machine_crash_shutकरोwn(काष्ठा pt_regs *regs)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक (*old_handler)(काष्ठा pt_regs *regs);

	/* Aव्योम hardlocking with irresponsive CPU holding logbuf_lock */
	prपूर्णांकk_nmi_enter();

	/*
	 * This function is only called after the प्रणाली
	 * has panicked or is otherwise in a critical state.
	 * The minimum amount of code to allow a kexec'd kernel
	 * to run successfully needs to happen here.
	 *
	 * In practice this means stopping other cpus in
	 * an SMP प्रणाली.
	 * The kernel is broken so disable पूर्णांकerrupts.
	 */
	hard_irq_disable();

	/*
	 * Make a note of crashing cpu. Will be used in machine_kexec
	 * such that another IPI will not be sent.
	 */
	crashing_cpu = smp_processor_id();

	/*
	 * If we came in via प्रणाली reset, रुको a जबतक क्रम the secondary
	 * CPUs to enter.
	 */
	अगर (TRAP(regs) == INTERRUPT_SYSTEM_RESET)
		mdelay(PRIMARY_TIMEOUT);

	crash_kexec_prepare_cpus(crashing_cpu);

	crash_save_cpu(regs, crashing_cpu);

	समय_प्रकारo_dump = 1;

	crash_kexec_रुको_realmode(crashing_cpu);

	machine_kexec_mask_पूर्णांकerrupts();

	/*
	 * Call रेजिस्टरed shutकरोwn routines safely.  Swap out
	 * __debugger_fault_handler, and replace on निकास.
	 */
	old_handler = __debugger_fault_handler;
	__debugger_fault_handler = handle_fault;
	crash_shutकरोwn_cpu = smp_processor_id();
	क्रम (i = 0; i < CRASH_HANDLER_MAX && crash_shutकरोwn_handles[i]; i++) अणु
		अगर (बनाओ_लाँघ(crash_shutकरोwn_buf) == 0) अणु
			/*
			 * Insert syncs and delay to ensure
			 * inकाष्ठाions in the dangerous region करोn't
			 * leak away from this रक्षित region.
			 */
			यंत्र अस्थिर("sync; isync");
			/* dangerous region */
			crash_shutकरोwn_handles[i]();
			यंत्र अस्थिर("sync; isync");
		पूर्ण
	पूर्ण
	crash_shutकरोwn_cpu = -1;
	__debugger_fault_handler = old_handler;

	अगर (ppc_md.kexec_cpu_करोwn)
		ppc_md.kexec_cpu_करोwn(1, 0);
पूर्ण
