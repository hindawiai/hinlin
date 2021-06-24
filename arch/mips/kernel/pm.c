<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2014 Imagination Technologies Ltd.
 *
 * CPU PM notअगरiers क्रम saving/restoring general CPU state.
 */

#समावेश <linux/cpu_pm.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/dsp.h>
#समावेश <यंत्र/fpu.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/pm.h>
#समावेश <यंत्र/watch.h>

/* Used by PM helper macros in यंत्र/pm.h */
काष्ठा mips_अटल_suspend_state mips_अटल_suspend_state;

/**
 * mips_cpu_save() - Save general CPU state.
 * Ensures that general CPU context is saved, notably FPU and DSP.
 */
अटल पूर्णांक mips_cpu_save(व्योम)
अणु
	/* Save FPU state */
	lose_fpu(1);

	/* Save DSP state */
	save_dsp(current);

	वापस 0;
पूर्ण

/**
 * mips_cpu_restore() - Restore general CPU state.
 * Restores important CPU context.
 */
अटल व्योम mips_cpu_restore(व्योम)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	/* Restore ASID */
	अगर (current->mm)
		ग_लिखो_c0_entryhi(cpu_asid(cpu, current->mm));

	/* Restore DSP state */
	restore_dsp(current);

	/* Restore UserLocal */
	अगर (cpu_has_userlocal)
		ग_लिखो_c0_userlocal(current_thपढ़ो_info()->tp_value);

	/* Restore watch रेजिस्टरs */
	__restore_watch(current);
पूर्ण

/**
 * mips_pm_notअगरier() - Notअगरier क्रम preserving general CPU context.
 * @self:	Notअगरier block.
 * @cmd:	CPU PM event.
 * @v:		Private data (unused).
 *
 * This is called when a CPU घातer management event occurs, and is used to
 * ensure that important CPU context is preserved across a CPU घातer करोwn.
 */
अटल पूर्णांक mips_pm_notअगरier(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ cmd,
			    व्योम *v)
अणु
	पूर्णांक ret;

	चयन (cmd) अणु
	हाल CPU_PM_ENTER:
		ret = mips_cpu_save();
		अगर (ret)
			वापस NOTIFY_STOP;
		अवरोध;
	हाल CPU_PM_ENTER_FAILED:
	हाल CPU_PM_EXIT:
		mips_cpu_restore();
		अवरोध;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block mips_pm_notअगरier_block = अणु
	.notअगरier_call = mips_pm_notअगरier,
पूर्ण;

अटल पूर्णांक __init mips_pm_init(व्योम)
अणु
	वापस cpu_pm_रेजिस्टर_notअगरier(&mips_pm_notअगरier_block);
पूर्ण
arch_initcall(mips_pm_init);
