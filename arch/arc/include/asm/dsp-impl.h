<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2020 Synopsys, Inc. (www.synopsys.com)
 *
 * Author: Eugeniy Paltsev <Eugeniy.Paltsev@synopsys.com>
 */
#अगर_अघोषित __ASM_ARC_DSP_IMPL_H
#घोषणा __ASM_ARC_DSP_IMPL_H

#समावेश <यंत्र/dsp.h>

#घोषणा DSP_CTRL_DISABLED_ALL		0

#अगर_घोषित __ASSEMBLY__

/* clobbers r5 रेजिस्टर */
.macro DSP_EARLY_INIT
#अगर_घोषित CONFIG_ISA_ARCV2
	lr	r5, [ARC_AUX_DSP_BUILD]
	bmsk	r5, r5, 7
	breq    r5, 0, 1f
	mov	r5, DSP_CTRL_DISABLED_ALL
	sr	r5, [ARC_AUX_DSP_CTRL]
1:
#पूर्ण_अगर
.endm

/* clobbers r10, r11 रेजिस्टरs pair */
.macro DSP_SAVE_REGखाता_IRQ
#अगर defined(CONFIG_ARC_DSP_KERNEL)
	/*
	 * Drop any changes to DSP_CTRL made by userspace so userspace won't be
	 * able to अवरोध kernel - reset it to DSP_CTRL_DISABLED_ALL value
	 */
	mov	r10, DSP_CTRL_DISABLED_ALL
	sr	r10, [ARC_AUX_DSP_CTRL]

#या_अगर defined(CONFIG_ARC_DSP_SAVE_RESTORE_REGS)
	/*
	 * Save DSP_CTRL रेजिस्टर and reset it to value suitable क्रम kernel
	 * (DSP_CTRL_DISABLED_ALL)
	 */
	mov	r10, DSP_CTRL_DISABLED_ALL
	aex	r10, [ARC_AUX_DSP_CTRL]
	st	r10, [sp, PT_DSP_CTRL]

#पूर्ण_अगर
.endm

/* clobbers r10, r11 रेजिस्टरs pair */
.macro DSP_RESTORE_REGखाता_IRQ
#अगर defined(CONFIG_ARC_DSP_SAVE_RESTORE_REGS)
	ld	r10, [sp, PT_DSP_CTRL]
	sr	r10, [ARC_AUX_DSP_CTRL]

#पूर्ण_अगर
.endm

#अन्यथा /* __ASEMBLY__ */

#समावेश <linux/sched.h>
#समावेश <यंत्र/निश्चितs.h>
#समावेश <यंत्र/चयन_to.h>

#अगर_घोषित CONFIG_ARC_DSP_SAVE_RESTORE_REGS

/*
 * As we save new and restore old AUX रेजिस्टर value in the same place we
 * can optimize a bit and use AEX inकाष्ठाion (swap contents of an auxiliary
 * रेजिस्टर with a core रेजिस्टर) instead of LR + SR pair.
 */
#घोषणा AUX_SAVE_RESTORE(_saveto, _पढ़ोfrom, _offt, _aux)		\
करो अणु									\
	दीर्घ अचिन्हित पूर्णांक _scratch;					\
									\
	__यंत्र__ __अस्थिर__(						\
		"ld	%0, [%2, %4]			\n"		\
		"aex	%0, [%3]			\n"		\
		"st	%0, [%1, %4]			\n"		\
		:							\
		  "=&r" (_scratch)	/* must be early clobber */	\
		:							\
		   "r" (_saveto),					\
		   "r" (_पढ़ोfrom),					\
		   "Ir" (_aux),						\
		   "Ir" (_offt)						\
		:							\
		  "memory"						\
	);								\
पूर्ण जबतक (0)

#घोषणा DSP_AUX_SAVE_RESTORE(_saveto, _पढ़ोfrom, _aux)			\
	AUX_SAVE_RESTORE(_saveto, _पढ़ोfrom,				\
		दुरत्व(काष्ठा dsp_callee_regs, _aux),			\
		ARC_AUX_##_aux)

अटल अंतरभूत व्योम dsp_save_restore(काष्ठा task_काष्ठा *prev,
					काष्ठा task_काष्ठा *next)
अणु
	दीर्घ अचिन्हित पूर्णांक *saveto = &prev->thपढ़ो.dsp.ACC0_GLO;
	दीर्घ अचिन्हित पूर्णांक *पढ़ोfrom = &next->thपढ़ो.dsp.ACC0_GLO;

	DSP_AUX_SAVE_RESTORE(saveto, पढ़ोfrom, ACC0_GLO);
	DSP_AUX_SAVE_RESTORE(saveto, पढ़ोfrom, ACC0_GHI);

	DSP_AUX_SAVE_RESTORE(saveto, पढ़ोfrom, DSP_BFLY0);
	DSP_AUX_SAVE_RESTORE(saveto, पढ़ोfrom, DSP_FFT_CTRL);

#अगर_घोषित CONFIG_ARC_DSP_AGU_USERSPACE
	DSP_AUX_SAVE_RESTORE(saveto, पढ़ोfrom, AGU_AP0);
	DSP_AUX_SAVE_RESTORE(saveto, पढ़ोfrom, AGU_AP1);
	DSP_AUX_SAVE_RESTORE(saveto, पढ़ोfrom, AGU_AP2);
	DSP_AUX_SAVE_RESTORE(saveto, पढ़ोfrom, AGU_AP3);

	DSP_AUX_SAVE_RESTORE(saveto, पढ़ोfrom, AGU_OS0);
	DSP_AUX_SAVE_RESTORE(saveto, पढ़ोfrom, AGU_OS1);

	DSP_AUX_SAVE_RESTORE(saveto, पढ़ोfrom, AGU_MOD0);
	DSP_AUX_SAVE_RESTORE(saveto, पढ़ोfrom, AGU_MOD1);
	DSP_AUX_SAVE_RESTORE(saveto, पढ़ोfrom, AGU_MOD2);
	DSP_AUX_SAVE_RESTORE(saveto, पढ़ोfrom, AGU_MOD3);
#पूर्ण_अगर /* CONFIG_ARC_DSP_AGU_USERSPACE */
पूर्ण

#अन्यथा /* !CONFIG_ARC_DSP_SAVE_RESTORE_REGS */
#घोषणा dsp_save_restore(p, n)
#पूर्ण_अगर /* CONFIG_ARC_DSP_SAVE_RESTORE_REGS */

अटल अंतरभूत bool dsp_exist(व्योम)
अणु
	काष्ठा bcr_generic bcr;

	READ_BCR(ARC_AUX_DSP_BUILD, bcr);
	वापस !!bcr.ver;
पूर्ण

अटल अंतरभूत bool agu_exist(व्योम)
अणु
	काष्ठा bcr_generic bcr;

	READ_BCR(ARC_AUX_AGU_BUILD, bcr);
	वापस !!bcr.ver;
पूर्ण

अटल अंतरभूत व्योम dsp_config_check(व्योम)
अणु
	CHK_OPT_STRICT(CONFIG_ARC_DSP_HANDLED, dsp_exist());
	CHK_OPT_WEAK(CONFIG_ARC_DSP_AGU_USERSPACE, agu_exist());
पूर्ण

#पूर्ण_अगर /* __ASEMBLY__ */
#पूर्ण_अगर /* __ASM_ARC_DSP_IMPL_H */
