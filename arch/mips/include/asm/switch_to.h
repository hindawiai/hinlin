<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1994, 95, 96, 97, 98, 99, 2003, 06 by Ralf Baechle
 * Copyright (C) 1996 by Paul M. Antoine
 * Copyright (C) 1999 Silicon Graphics
 * Kevin D. Kissell, kevink@mips.org and Carsten Langgaard, carstenl@mips.com
 * Copyright (C) 2000 MIPS Technologies, Inc.
 */
#अगर_अघोषित _ASM_SWITCH_TO_H
#घोषणा _ASM_SWITCH_TO_H

#समावेश <यंत्र/cpu-features.h>
#समावेश <यंत्र/watch.h>
#समावेश <यंत्र/dsp.h>
#समावेश <यंत्र/cop2.h>
#समावेश <यंत्र/fpu.h>

काष्ठा task_काष्ठा;

/**
 * resume - resume execution of a task
 * @prev:	The task previously executed.
 * @next:	The task to begin executing.
 * @next_ti:	task_thपढ़ो_info(next).
 *
 * This function is used whilst scheduling to save the context of prev & load
 * the context of next. Returns prev.
 */
बाह्य यंत्रlinkage काष्ठा task_काष्ठा *resume(काष्ठा task_काष्ठा *prev,
		काष्ठा task_काष्ठा *next, काष्ठा thपढ़ो_info *next_ti);

बाह्य अचिन्हित पूर्णांक ll_bit;
बाह्य काष्ठा task_काष्ठा *ll_task;

#अगर_घोषित CONFIG_MIPS_MT_FPAFF

/*
 * Handle the scheduler resume end of FPU affinity management.	We करो this
 * अंतरभूत to try to keep the overhead करोwn. If we have been क्रमced to run on
 * a "CPU" with an FPU because of a previous high level of FP computation,
 * but did not actually use the FPU during the most recent समय-slice (CU1
 * isn't set), we unकरो the restriction on cpus_mask.
 *
 * We're not calling set_cpus_allowed() here, because we have no need to
 * क्रमce prompt migration - we're alपढ़ोy चयनing the current CPU to a
 * dअगरferent thपढ़ो.
 */

#घोषणा __mips_mt_fpaff_चयन_to(prev)					\
करो अणु									\
	काष्ठा thपढ़ो_info *__prev_ti = task_thपढ़ो_info(prev);		\
									\
	अगर (cpu_has_fpu &&						\
	    test_ti_thपढ़ो_flag(__prev_ti, TIF_FPUBOUND) &&		\
	    (!(KSTK_STATUS(prev) & ST0_CU1))) अणु				\
		clear_ti_thपढ़ो_flag(__prev_ti, TIF_FPUBOUND);		\
		prev->cpus_mask = prev->thपढ़ो.user_cpus_allowed;	\
	पूर्ण								\
	next->thपढ़ो.emulated_fp = 0;					\
पूर्ण जबतक(0)

#अन्यथा
#घोषणा __mips_mt_fpaff_चयन_to(prev) करो अणु (व्योम) (prev); पूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * Clear LLBit during context चयनes on MIPSr5+ such that eretnc can be used
 * unconditionally when वापसing to userland in entry.S.
 */
#घोषणा __clear_r5_hw_ll_bit() करो अणु					\
	अगर (cpu_has_mips_r5 || cpu_has_mips_r6)				\
		ग_लिखो_c0_lladdr(0);					\
पूर्ण जबतक (0)

#घोषणा __clear_software_ll_bit() करो अणु					\
	अगर (!__builtin_स्थिरant_p(cpu_has_llsc) || !cpu_has_llsc)	\
		ll_bit = 0;						\
पूर्ण जबतक (0)

/*
 * Check FCSR क्रम any unmasked exceptions pending set with `ptrace',
 * clear them and send a संकेत.
 */
#अगर_घोषित CONFIG_MIPS_FP_SUPPORT
# define __sanitize_fcr31(next)						\
करो अणु									\
	अचिन्हित दीर्घ fcr31 = mask_fcr31_x(next->thपढ़ो.fpu.fcr31);	\
	व्योम __user *pc;						\
									\
	अगर (unlikely(fcr31)) अणु						\
		pc = (व्योम __user *)task_pt_regs(next)->cp0_epc;	\
		next->thपढ़ो.fpu.fcr31 &= ~fcr31;			\
		क्रमce_fcr31_sig(fcr31, pc, next);			\
	पूर्ण								\
पूर्ण जबतक (0)
#अन्यथा
# define __sanitize_fcr31(next)
#पूर्ण_अगर

/*
 * For newly created kernel thपढ़ोs चयन_to() will वापस to
 * ret_from_kernel_thपढ़ो, newly created user thपढ़ोs to ret_from_विभाजन.
 * That is, everything following resume() will be skipped क्रम new thपढ़ोs.
 * So everything that matters to new thपढ़ोs should be placed beक्रमe resume().
 */
#घोषणा चयन_to(prev, next, last)					\
करो अणु									\
	__mips_mt_fpaff_चयन_to(prev);				\
	lose_fpu_inatomic(1, prev);					\
	अगर (tsk_used_math(next))					\
		__sanitize_fcr31(next);					\
	अगर (cpu_has_dsp) अणु						\
		__save_dsp(prev);					\
		__restore_dsp(next);					\
	पूर्ण								\
	अगर (cop2_present) अणु						\
		u32 status = पढ़ो_c0_status();				\
									\
		set_c0_status(ST0_CU2);					\
		अगर ((KSTK_STATUS(prev) & ST0_CU2)) अणु			\
			अगर (cop2_lazy_restore)				\
				KSTK_STATUS(prev) &= ~ST0_CU2;		\
			cop2_save(prev);				\
		पूर्ण							\
		अगर (KSTK_STATUS(next) & ST0_CU2 &&			\
		    !cop2_lazy_restore) अणु				\
			cop2_restore(next);				\
		पूर्ण							\
		ग_लिखो_c0_status(status);				\
	पूर्ण								\
	__clear_r5_hw_ll_bit();						\
	__clear_software_ll_bit();					\
	अगर (cpu_has_userlocal)						\
		ग_लिखो_c0_userlocal(task_thपढ़ो_info(next)->tp_value);	\
	__restore_watch(next);						\
	(last) = resume(prev, next, task_thपढ़ो_info(next));		\
पूर्ण जबतक (0)

#पूर्ण_अगर /* _ASM_SWITCH_TO_H */
