<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2002 MontaVista Software Inc.
 * Author: Jun Sun, jsun@mvista.com or jsun@junsun.net
 */
#अगर_अघोषित _ASM_FPU_H
#घोषणा _ASM_FPU_H

#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/thपढ़ो_info.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cpu-features.h>
#समावेश <यंत्र/fpu_emulator.h>
#समावेश <यंत्र/hazards.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/current.h>
#समावेश <यंत्र/msa.h>

#अगर_घोषित CONFIG_MIPS_MT_FPAFF
#समावेश <यंत्र/mips_mt.h>
#पूर्ण_अगर

/*
 * This क्रमागत specअगरies a mode in which we want the FPU to operate, क्रम cores
 * which implement the Status.FR bit. Note that the bottom bit of the value
 * purposefully matches the desired value of the Status.FR bit.
 */
क्रमागत fpu_mode अणु
	FPU_32BIT = 0,		/* FR = 0 */
	FPU_64BIT,		/* FR = 1, FRE = 0 */
	FPU_AS_IS,
	FPU_HYBRID,		/* FR = 1, FRE = 1 */

#घोषणा FPU_FR_MASK		0x1
पूर्ण;

#अगर_घोषित CONFIG_MIPS_FP_SUPPORT

बाह्य व्योम _save_fp(काष्ठा task_काष्ठा *);
बाह्य व्योम _restore_fp(काष्ठा task_काष्ठा *);

#घोषणा __disable_fpu()							\
करो अणु									\
	clear_c0_status(ST0_CU1);					\
	disable_fpu_hazard();						\
पूर्ण जबतक (0)

अटल अंतरभूत पूर्णांक __enable_fpu(क्रमागत fpu_mode mode)
अणु
	पूर्णांक fr;

	चयन (mode) अणु
	हाल FPU_AS_IS:
		/* just enable the FPU in its current mode */
		set_c0_status(ST0_CU1);
		enable_fpu_hazard();
		वापस 0;

	हाल FPU_HYBRID:
		अगर (!cpu_has_fre)
			वापस संक_भ_त्रुटि;

		/* set FRE */
		set_c0_config5(MIPS_CONF5_FRE);
		जाओ fr_common;

	हाल FPU_64BIT:
#अगर !(defined(CONFIG_CPU_MIPSR2) || defined(CONFIG_CPU_MIPSR5) || \
      defined(CONFIG_CPU_MIPSR6) || defined(CONFIG_64BIT))
		/* we only have a 32-bit FPU */
		वापस संक_भ_त्रुटि;
#पूर्ण_अगर
		fallthrough;
	हाल FPU_32BIT:
		अगर (cpu_has_fre) अणु
			/* clear FRE */
			clear_c0_config5(MIPS_CONF5_FRE);
		पूर्ण
fr_common:
		/* set CU1 & change FR appropriately */
		fr = (पूर्णांक)mode & FPU_FR_MASK;
		change_c0_status(ST0_CU1 | ST0_FR, ST0_CU1 | (fr ? ST0_FR : 0));
		enable_fpu_hazard();

		/* check FR has the desired value */
		अगर (!!(पढ़ो_c0_status() & ST0_FR) == !!fr)
			वापस 0;

		/* unsupported FR value */
		__disable_fpu();
		वापस संक_भ_त्रुटि;

	शेष:
		BUG();
	पूर्ण

	वापस संक_भ_त्रुटि;
पूर्ण

#घोषणा clear_fpu_owner()	clear_thपढ़ो_flag(TIF_USEDFPU)

अटल अंतरभूत पूर्णांक __is_fpu_owner(व्योम)
अणु
	वापस test_thपढ़ो_flag(TIF_USEDFPU);
पूर्ण

अटल अंतरभूत पूर्णांक is_fpu_owner(व्योम)
अणु
	वापस cpu_has_fpu && __is_fpu_owner();
पूर्ण

अटल अंतरभूत पूर्णांक __own_fpu(व्योम)
अणु
	क्रमागत fpu_mode mode;
	पूर्णांक ret;

	अगर (test_thपढ़ो_flag(TIF_HYBRID_FPREGS))
		mode = FPU_HYBRID;
	अन्यथा
		mode = !test_thपढ़ो_flag(TIF_32BIT_FPREGS);

	ret = __enable_fpu(mode);
	अगर (ret)
		वापस ret;

	KSTK_STATUS(current) |= ST0_CU1;
	अगर (mode == FPU_64BIT || mode == FPU_HYBRID)
		KSTK_STATUS(current) |= ST0_FR;
	अन्यथा /* mode == FPU_32BIT */
		KSTK_STATUS(current) &= ~ST0_FR;

	set_thपढ़ो_flag(TIF_USEDFPU);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक own_fpu_inatomic(पूर्णांक restore)
अणु
	पूर्णांक ret = 0;

	अगर (cpu_has_fpu && !__is_fpu_owner()) अणु
		ret = __own_fpu();
		अगर (restore && !ret)
			_restore_fp(current);
	पूर्ण
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक own_fpu(पूर्णांक restore)
अणु
	पूर्णांक ret;

	preempt_disable();
	ret = own_fpu_inatomic(restore);
	preempt_enable();
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम lose_fpu_inatomic(पूर्णांक save, काष्ठा task_काष्ठा *tsk)
अणु
	अगर (is_msa_enabled()) अणु
		अगर (save) अणु
			save_msa(tsk);
			tsk->thपढ़ो.fpu.fcr31 =
					पढ़ो_32bit_cp1_रेजिस्टर(CP1_STATUS);
		पूर्ण
		disable_msa();
		clear_tsk_thपढ़ो_flag(tsk, TIF_USEDMSA);
		__disable_fpu();
	पूर्ण अन्यथा अगर (is_fpu_owner()) अणु
		अगर (save)
			_save_fp(tsk);
		__disable_fpu();
	पूर्ण अन्यथा अणु
		/* FPU should not have been left enabled with no owner */
		WARN(पढ़ो_c0_status() & ST0_CU1,
		     "Orphaned FPU left enabled");
	पूर्ण
	KSTK_STATUS(tsk) &= ~ST0_CU1;
	clear_tsk_thपढ़ो_flag(tsk, TIF_USEDFPU);
पूर्ण

अटल अंतरभूत व्योम lose_fpu(पूर्णांक save)
अणु
	preempt_disable();
	lose_fpu_inatomic(save, current);
	preempt_enable();
पूर्ण

/**
 * init_fp_ctx() - Initialize task FP context
 * @target: The task whose FP context should be initialized.
 *
 * Initializes the FP context of the target task to sane शेष values अगर that
 * target task करोes not alपढ़ोy have valid FP context. Once the context has
 * been initialized, the task will be marked as having used FP & thus having
 * valid FP context.
 *
 * Returns: true अगर context is initialized, अन्यथा false.
 */
अटल अंतरभूत bool init_fp_ctx(काष्ठा task_काष्ठा *target)
अणु
	/* If FP has been used then the target alपढ़ोy has context */
	अगर (tsk_used_math(target))
		वापस false;

	/* Begin with data रेजिस्टरs set to all 1s... */
	स_रखो(&target->thपढ़ो.fpu.fpr, ~0, माप(target->thपढ़ो.fpu.fpr));

	/* FCSR has been preset by `mips_set_personality_nan'.  */

	/*
	 * Record that the target has "used" math, such that the context
	 * just initialised, and any modअगरications made by the caller,
	 * aren't discarded.
	 */
	set_stopped_child_used_math(target);

	वापस true;
पूर्ण

अटल अंतरभूत व्योम save_fp(काष्ठा task_काष्ठा *tsk)
अणु
	अगर (cpu_has_fpu)
		_save_fp(tsk);
पूर्ण

अटल अंतरभूत व्योम restore_fp(काष्ठा task_काष्ठा *tsk)
अणु
	अगर (cpu_has_fpu)
		_restore_fp(tsk);
पूर्ण

अटल अंतरभूत जोड़ fpureg *get_fpu_regs(काष्ठा task_काष्ठा *tsk)
अणु
	अगर (tsk == current) अणु
		preempt_disable();
		अगर (is_fpu_owner())
			_save_fp(current);
		preempt_enable();
	पूर्ण

	वापस tsk->thपढ़ो.fpu.fpr;
पूर्ण

#अन्यथा /* !CONFIG_MIPS_FP_SUPPORT */

/*
 * When FP support is disabled we provide only a minimal set of stub functions
 * to aव्योम callers needing to care too much about CONFIG_MIPS_FP_SUPPORT.
 */

अटल अंतरभूत पूर्णांक __enable_fpu(क्रमागत fpu_mode mode)
अणु
	वापस संक_अवैध;
पूर्ण

अटल अंतरभूत व्योम __disable_fpu(व्योम)
अणु
	/* no-op */
पूर्ण


अटल अंतरभूत पूर्णांक is_fpu_owner(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम clear_fpu_owner(व्योम)
अणु
	/* no-op */
पूर्ण

अटल अंतरभूत पूर्णांक own_fpu_inatomic(पूर्णांक restore)
अणु
	वापस संक_अवैध;
पूर्ण

अटल अंतरभूत पूर्णांक own_fpu(पूर्णांक restore)
अणु
	वापस संक_अवैध;
पूर्ण

अटल अंतरभूत व्योम lose_fpu_inatomic(पूर्णांक save, काष्ठा task_काष्ठा *tsk)
अणु
	/* no-op */
पूर्ण

अटल अंतरभूत व्योम lose_fpu(पूर्णांक save)
अणु
	/* no-op */
पूर्ण

अटल अंतरभूत bool init_fp_ctx(काष्ठा task_काष्ठा *target)
अणु
	वापस false;
पूर्ण

/*
 * The following functions should only be called in paths where we know that FP
 * support is enabled, typically a path where own_fpu() or __enable_fpu() have
 * वापसed successfully. When CONFIG_MIPS_FP_SUPPORT=n it is known at compile
 * समय that this should never happen, so calls to these functions should be
 * optimized away & never actually be emitted.
 */

बाह्य व्योम save_fp(काष्ठा task_काष्ठा *tsk)
	__compileसमय_error("save_fp() should not be called when CONFIG_MIPS_FP_SUPPORT=n");

बाह्य व्योम _save_fp(काष्ठा task_काष्ठा *)
	__compileसमय_error("_save_fp() should not be called when CONFIG_MIPS_FP_SUPPORT=n");

बाह्य व्योम restore_fp(काष्ठा task_काष्ठा *tsk)
	__compileसमय_error("restore_fp() should not be called when CONFIG_MIPS_FP_SUPPORT=n");

बाह्य व्योम _restore_fp(काष्ठा task_काष्ठा *)
	__compileसमय_error("_restore_fp() should not be called when CONFIG_MIPS_FP_SUPPORT=n");

बाह्य जोड़ fpureg *get_fpu_regs(काष्ठा task_काष्ठा *tsk)
	__compileसमय_error("get_fpu_regs() should not be called when CONFIG_MIPS_FP_SUPPORT=n");

#पूर्ण_अगर /* !CONFIG_MIPS_FP_SUPPORT */
#पूर्ण_अगर /* _ASM_FPU_H */
