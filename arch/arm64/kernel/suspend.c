<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/ftrace.h>
#समावेश <linux/percpu.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/daअगरflags.h>
#समावेश <यंत्र/debug-monitors.h>
#समावेश <यंत्र/exec.h>
#समावेश <यंत्र/mte.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/suspend.h>

/*
 * This is allocated by cpu_suspend_init(), and used to store a poपूर्णांकer to
 * the 'struct sleep_stack_data' the contains a particular CPUs state.
 */
अचिन्हित दीर्घ *sleep_save_stash;

/*
 * This hook is provided so that cpu_suspend code can restore HW
 * अवरोधpoपूर्णांकs as early as possible in the resume path, beक्रमe reenabling
 * debug exceptions. Code cannot be run from a CPU PM notअगरier since by the
 * समय the notअगरier runs debug exceptions might have been enabled alपढ़ोy,
 * with HW अवरोधpoपूर्णांकs रेजिस्टरs content still in an unknown state.
 */
अटल पूर्णांक (*hw_अवरोधpoपूर्णांक_restore)(अचिन्हित पूर्णांक);
व्योम __init cpu_suspend_set_dbg_restorer(पूर्णांक (*hw_bp_restore)(अचिन्हित पूर्णांक))
अणु
	/* Prevent multiple restore hook initializations */
	अगर (WARN_ON(hw_अवरोधpoपूर्णांक_restore))
		वापस;
	hw_अवरोधpoपूर्णांक_restore = hw_bp_restore;
पूर्ण

व्योम notrace __cpu_suspend_निकास(व्योम)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	/*
	 * We are resuming from reset with the idmap active in TTBR0_EL1.
	 * We must uninstall the idmap and restore the expected MMU
	 * state beक्रमe we can possibly वापस to userspace.
	 */
	cpu_uninstall_idmap();

	/* Restore CnP bit in TTBR1_EL1 */
	अगर (प्रणाली_supports_cnp())
		cpu_replace_ttbr1(lm_alias(swapper_pg_dir));

	/*
	 * PSTATE was not saved over suspend/resume, re-enable any detected
	 * features that might not have been set correctly.
	 */
	__uaccess_enable_hw_pan();

	/*
	 * Restore HW अवरोधpoपूर्णांक रेजिस्टरs to sane values
	 * beक्रमe debug exceptions are possibly reenabled
	 * by cpu_suspend()s local_daअगर_restore() call.
	 */
	अगर (hw_अवरोधpoपूर्णांक_restore)
		hw_अवरोधpoपूर्णांक_restore(cpu);

	/*
	 * On resume, firmware implementing dynamic mitigation will
	 * have turned the mitigation on. If the user has क्रमcefully
	 * disabled it, make sure their wishes are obeyed.
	 */
	spectre_v4_enable_mitigation(शून्य);

	/* Restore additional feature-specअगरic configuration */
	mte_suspend_निकास();
	ptrauth_suspend_निकास();
पूर्ण

/*
 * cpu_suspend
 *
 * arg: argument to pass to the finisher function
 * fn: finisher function poपूर्णांकer
 *
 */
पूर्णांक cpu_suspend(अचिन्हित दीर्घ arg, पूर्णांक (*fn)(अचिन्हित दीर्घ))
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा sleep_stack_data state;

	/* Report any MTE async fault beक्रमe going to suspend */
	mte_suspend_enter();

	/*
	 * From this poपूर्णांक debug exceptions are disabled to prevent
	 * updates to mdscr रेजिस्टर (saved and restored aदीर्घ with
	 * general purpose रेजिस्टरs) from kernel debuggers.
	 */
	flags = local_daअगर_save();

	/*
	 * Function graph tracer state माला_लो incosistent when the kernel
	 * calls functions that never वापस (aka suspend finishers) hence
	 * disable graph tracing during their execution.
	 */
	छोड़ो_graph_tracing();

	अगर (__cpu_suspend_enter(&state)) अणु
		/* Call the suspend finisher */
		ret = fn(arg);

		/*
		 * Never माला_लो here, unless the suspend finisher fails.
		 * Successful cpu_suspend() should वापस from cpu_resume(),
		 * वापसing through this code path is considered an error
		 * If the वापस value is set to 0 क्रमce ret = -EOPNOTSUPP
		 * to make sure a proper error condition is propagated
		 */
		अगर (!ret)
			ret = -EOPNOTSUPP;
	पूर्ण अन्यथा अणु
		RCU_NONIDLE(__cpu_suspend_निकास());
	पूर्ण

	unछोड़ो_graph_tracing();

	/*
	 * Restore pstate flags. OS lock and mdscr have been alपढ़ोy
	 * restored, so from this poपूर्णांक onwards, debugging is fully
	 * renabled अगर it was enabled when core started shutकरोwn.
	 */
	local_daअगर_restore(flags);

	वापस ret;
पूर्ण

अटल पूर्णांक __init cpu_suspend_init(व्योम)
अणु
	/* ctx_ptr is an array of physical addresses */
	sleep_save_stash = kसुस्मृति(mpidr_hash_size(), माप(*sleep_save_stash),
				   GFP_KERNEL);

	अगर (WARN_ON(!sleep_save_stash))
		वापस -ENOMEM;

	वापस 0;
पूर्ण
early_initcall(cpu_suspend_init);
