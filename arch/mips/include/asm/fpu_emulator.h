<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * Further निजी data क्रम which no space exists in mips_fpu_काष्ठा.
 * This should be subsumed पूर्णांकo the mips_fpu_काष्ठा काष्ठाure as
 * defined in processor.h as soon as the असलurd wired असलolute assembler
 * offsets become dynamic at compile समय.
 *
 * Kevin D. Kissell, kevink@mips.com and Carsten Langgaard, carstenl@mips.com
 * Copyright (C) 2000 MIPS Technologies, Inc.  All rights reserved.
 */
#अगर_अघोषित _ASM_FPU_EMULATOR_H
#घोषणा _ASM_FPU_EMULATOR_H

#समावेश <linux/sched.h>
#समावेश <यंत्र/dsemul.h>
#समावेश <यंत्र/thपढ़ो_info.h>
#समावेश <यंत्र/inst.h>
#समावेश <यंत्र/local.h>
#समावेश <यंत्र/processor.h>

#अगर_घोषित CONFIG_DEBUG_FS

काष्ठा mips_fpu_emulator_stats अणु
	अचिन्हित दीर्घ emulated;
	अचिन्हित दीर्घ loads;
	अचिन्हित दीर्घ stores;
	अचिन्हित दीर्घ branches;
	अचिन्हित दीर्घ cp1ops;
	अचिन्हित दीर्घ cp1xops;
	अचिन्हित दीर्घ errors;
	अचिन्हित दीर्घ ieee754_inexact;
	अचिन्हित दीर्घ ieee754_underflow;
	अचिन्हित दीर्घ ieee754_overflow;
	अचिन्हित दीर्घ ieee754_zeroभाग;
	अचिन्हित दीर्घ ieee754_invaliकरोp;
	अचिन्हित दीर्घ ds_emul;

	अचिन्हित दीर्घ असल_s;
	अचिन्हित दीर्घ असल_d;
	अचिन्हित दीर्घ add_s;
	अचिन्हित दीर्घ add_d;
	अचिन्हित दीर्घ bc1eqz;
	अचिन्हित दीर्घ bc1nez;
	अचिन्हित दीर्घ उच्चमान_w_s;
	अचिन्हित दीर्घ उच्चमान_w_d;
	अचिन्हित दीर्घ उच्चमान_l_s;
	अचिन्हित दीर्घ उच्चमान_l_d;
	अचिन्हित दीर्घ class_s;
	अचिन्हित दीर्घ class_d;
	अचिन्हित दीर्घ cmp_af_s;
	अचिन्हित दीर्घ cmp_af_d;
	अचिन्हित दीर्घ cmp_eq_s;
	अचिन्हित दीर्घ cmp_eq_d;
	अचिन्हित दीर्घ cmp_le_s;
	अचिन्हित दीर्घ cmp_le_d;
	अचिन्हित दीर्घ cmp_lt_s;
	अचिन्हित दीर्घ cmp_lt_d;
	अचिन्हित दीर्घ cmp_ne_s;
	अचिन्हित दीर्घ cmp_ne_d;
	अचिन्हित दीर्घ cmp_or_s;
	अचिन्हित दीर्घ cmp_or_d;
	अचिन्हित दीर्घ cmp_ueq_s;
	अचिन्हित दीर्घ cmp_ueq_d;
	अचिन्हित दीर्घ cmp_ule_s;
	अचिन्हित दीर्घ cmp_ule_d;
	अचिन्हित दीर्घ cmp_ult_s;
	अचिन्हित दीर्घ cmp_ult_d;
	अचिन्हित दीर्घ cmp_un_s;
	अचिन्हित दीर्घ cmp_un_d;
	अचिन्हित दीर्घ cmp_une_s;
	अचिन्हित दीर्घ cmp_une_d;
	अचिन्हित दीर्घ cmp_saf_s;
	अचिन्हित दीर्घ cmp_saf_d;
	अचिन्हित दीर्घ cmp_seq_s;
	अचिन्हित दीर्घ cmp_seq_d;
	अचिन्हित दीर्घ cmp_sle_s;
	अचिन्हित दीर्घ cmp_sle_d;
	अचिन्हित दीर्घ cmp_slt_s;
	अचिन्हित दीर्घ cmp_slt_d;
	अचिन्हित दीर्घ cmp_sne_s;
	अचिन्हित दीर्घ cmp_sne_d;
	अचिन्हित दीर्घ cmp_sor_s;
	अचिन्हित दीर्घ cmp_sor_d;
	अचिन्हित दीर्घ cmp_sueq_s;
	अचिन्हित दीर्घ cmp_sueq_d;
	अचिन्हित दीर्घ cmp_sule_s;
	अचिन्हित दीर्घ cmp_sule_d;
	अचिन्हित दीर्घ cmp_sult_s;
	अचिन्हित दीर्घ cmp_sult_d;
	अचिन्हित दीर्घ cmp_sun_s;
	अचिन्हित दीर्घ cmp_sun_d;
	अचिन्हित दीर्घ cmp_sune_s;
	अचिन्हित दीर्घ cmp_sune_d;
	अचिन्हित दीर्घ cvt_d_l;
	अचिन्हित दीर्घ cvt_d_s;
	अचिन्हित दीर्घ cvt_d_w;
	अचिन्हित दीर्घ cvt_l_s;
	अचिन्हित दीर्घ cvt_l_d;
	अचिन्हित दीर्घ cvt_s_d;
	अचिन्हित दीर्घ cvt_s_l;
	अचिन्हित दीर्घ cvt_s_w;
	अचिन्हित दीर्घ cvt_w_s;
	अचिन्हित दीर्घ cvt_w_d;
	अचिन्हित दीर्घ भाग_s;
	अचिन्हित दीर्घ भाग_d;
	अचिन्हित दीर्घ न्यूनमान_w_s;
	अचिन्हित दीर्घ न्यूनमान_w_d;
	अचिन्हित दीर्घ न्यूनमान_l_s;
	अचिन्हित दीर्घ न्यूनमान_l_d;
	अचिन्हित दीर्घ maddf_s;
	अचिन्हित दीर्घ maddf_d;
	अचिन्हित दीर्घ max_s;
	अचिन्हित दीर्घ max_d;
	अचिन्हित दीर्घ maxa_s;
	अचिन्हित दीर्घ maxa_d;
	अचिन्हित दीर्घ min_s;
	अचिन्हित दीर्घ min_d;
	अचिन्हित दीर्घ mina_s;
	अचिन्हित दीर्घ mina_d;
	अचिन्हित दीर्घ mov_s;
	अचिन्हित दीर्घ mov_d;
	अचिन्हित दीर्घ msubf_s;
	अचिन्हित दीर्घ msubf_d;
	अचिन्हित दीर्घ mul_s;
	अचिन्हित दीर्घ mul_d;
	अचिन्हित दीर्घ neg_s;
	अचिन्हित दीर्घ neg_d;
	अचिन्हित दीर्घ recip_s;
	अचिन्हित दीर्घ recip_d;
	अचिन्हित दीर्घ rपूर्णांक_s;
	अचिन्हित दीर्घ rपूर्णांक_d;
	अचिन्हित दीर्घ round_w_s;
	अचिन्हित दीर्घ round_w_d;
	अचिन्हित दीर्घ round_l_s;
	अचिन्हित दीर्घ round_l_d;
	अचिन्हित दीर्घ rवर्ग_मूल_s;
	अचिन्हित दीर्घ rवर्ग_मूल_d;
	अचिन्हित दीर्घ sel_s;
	अचिन्हित दीर्घ sel_d;
	अचिन्हित दीर्घ seleqz_s;
	अचिन्हित दीर्घ seleqz_d;
	अचिन्हित दीर्घ selnez_s;
	अचिन्हित दीर्घ selnez_d;
	अचिन्हित दीर्घ वर्ग_मूल_s;
	अचिन्हित दीर्घ वर्ग_मूल_d;
	अचिन्हित दीर्घ sub_s;
	अचिन्हित दीर्घ sub_d;
	अचिन्हित दीर्घ trunc_w_s;
	अचिन्हित दीर्घ trunc_w_d;
	अचिन्हित दीर्घ trunc_l_s;
	अचिन्हित दीर्घ trunc_l_d;
पूर्ण;

DECLARE_PER_CPU(काष्ठा mips_fpu_emulator_stats, fpuemustats);

#घोषणा MIPS_FPU_EMU_INC_STATS(M)					\
करो अणु									\
	preempt_disable();						\
	__this_cpu_inc(fpuemustats.M);					\
	preempt_enable();						\
पूर्ण जबतक (0)

#अन्यथा
#घोषणा MIPS_FPU_EMU_INC_STATS(M) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

बाह्य पूर्णांक fpu_emulator_cop1Handler(काष्ठा pt_regs *xcp,
				    काष्ठा mips_fpu_काष्ठा *ctx, पूर्णांक has_fpu,
				    व्योम __user **fault_addr);
व्योम क्रमce_fcr31_sig(अचिन्हित दीर्घ fcr31, व्योम __user *fault_addr,
		     काष्ठा task_काष्ठा *tsk);
पूर्णांक process_fpemu_वापस(पूर्णांक sig, व्योम __user *fault_addr,
			 अचिन्हित दीर्घ fcr31);

/*
 * Mask the FCSR Cause bits according to the Enable bits, observing
 * that Unimplemented is always enabled.
 */
अटल अंतरभूत अचिन्हित दीर्घ mask_fcr31_x(अचिन्हित दीर्घ fcr31)
अणु
	वापस fcr31 & (FPU_CSR_UNI_X |
			((fcr31 & FPU_CSR_ALL_E) <<
			 (ffs(FPU_CSR_ALL_X) - ffs(FPU_CSR_ALL_E))));
पूर्ण

#पूर्ण_अगर /* _ASM_FPU_EMULATOR_H */
