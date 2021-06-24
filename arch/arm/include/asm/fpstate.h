<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/fpstate.h
 *
 *  Copyright (C) 1995 Russell King
 */

#अगर_अघोषित __ASM_ARM_FPSTATE_H
#घोषणा __ASM_ARM_FPSTATE_H


#अगर_अघोषित __ASSEMBLY__

/*
 * VFP storage area has:
 *  - FPEXC, FPSCR, FPINST and FPINST2.
 *  - 16 or 32 द्विगुन precision data रेजिस्टरs
 *  - an implementation-dependent word of state क्रम FLDMX/FSTMX (pre-ARMv6)
 * 
 *  FPEXC will always be non-zero once the VFP has been used in this process.
 */

काष्ठा vfp_hard_काष्ठा अणु
#अगर_घोषित CONFIG_VFPv3
	__u64 fpregs[32];
#अन्यथा
	__u64 fpregs[16];
#पूर्ण_अगर
#अगर __LINUX_ARM_ARCH__ < 6
	__u32 fpmx_state;
#पूर्ण_अगर
	__u32 fpexc;
	__u32 fpscr;
	/*
	 * VFP implementation specअगरic state
	 */
	__u32 fpinst;
	__u32 fpinst2;

#अगर_घोषित CONFIG_SMP
	__u32 cpu;
#पूर्ण_अगर
पूर्ण;

जोड़ vfp_state अणु
	काष्ठा vfp_hard_काष्ठा	hard;
पूर्ण;

बाह्य व्योम vfp_flush_thपढ़ो(जोड़ vfp_state *);
बाह्य व्योम vfp_release_thपढ़ो(जोड़ vfp_state *);

#घोषणा FP_HARD_SIZE 35

काष्ठा fp_hard_काष्ठा अणु
	अचिन्हित पूर्णांक save[FP_HARD_SIZE];		/* as yet undefined */
पूर्ण;

#घोषणा FP_SOFT_SIZE 35

काष्ठा fp_soft_काष्ठा अणु
	अचिन्हित पूर्णांक save[FP_SOFT_SIZE];		/* undefined inक्रमmation */
पूर्ण;

#घोषणा IWMMXT_SIZE	0x98

काष्ठा iwmmxt_काष्ठा अणु
	अचिन्हित पूर्णांक save[IWMMXT_SIZE / माप(अचिन्हित पूर्णांक)];
पूर्ण;

जोड़ fp_state अणु
	काष्ठा fp_hard_काष्ठा	hard;
	काष्ठा fp_soft_काष्ठा	soft;
#अगर_घोषित CONFIG_IWMMXT
	काष्ठा iwmmxt_काष्ठा	iwmmxt;
#पूर्ण_अगर
पूर्ण;

#घोषणा FP_SIZE (माप(जोड़ fp_state) / माप(पूर्णांक))

काष्ठा crunch_state अणु
	अचिन्हित पूर्णांक	mvdx[16][2];
	अचिन्हित पूर्णांक	mvax[4][3];
	अचिन्हित पूर्णांक	dspsc[2];
पूर्ण;

#घोषणा CRUNCH_SIZE	माप(काष्ठा crunch_state)

#पूर्ण_अगर

#पूर्ण_अगर
