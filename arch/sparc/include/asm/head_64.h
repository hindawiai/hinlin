<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC64_HEAD_H
#घोषणा _SPARC64_HEAD_H

#समावेश <यंत्र/pstate.h>

	/* wrpr	%g0, val, %gl */
#घोषणा SET_GL(val)	\
	.word	0xa1902000 | val

	/* rdpr %gl, %gN */
#घोषणा GET_GL_GLOBAL(N)	\
	.word	0x81540000 | (N << 25)

#घोषणा KERNBASE	0x400000

#घोषणा	PTREGS_OFF	(STACK_BIAS + STACKFRAME_SZ)

#घोषणा	RTRAP_PSTATE		(PSTATE_TSO|PSTATE_PEF|PSTATE_PRIV|PSTATE_IE)
#घोषणा	RTRAP_PSTATE_IRQOFF	(PSTATE_TSO|PSTATE_PEF|PSTATE_PRIV)
#घोषणा RTRAP_PSTATE_AG_IRQOFF	(PSTATE_TSO|PSTATE_PEF|PSTATE_PRIV|PSTATE_AG)

#घोषणा __CHEETAH_ID	0x003e0014
#घोषणा __JALAPENO_ID	0x003e0016
#घोषणा __SERRANO_ID	0x003e0022

#घोषणा CHEETAH_MANUF		0x003e
#घोषणा CHEETAH_IMPL		0x0014 /* Ultra-III   */
#घोषणा CHEETAH_PLUS_IMPL	0x0015 /* Ultra-III+  */
#घोषणा JALAPENO_IMPL		0x0016 /* Ultra-IIIi  */
#घोषणा JAGUAR_IMPL		0x0018 /* Ultra-IV    */
#घोषणा PANTHER_IMPL		0x0019 /* Ultra-IV+   */
#घोषणा SERRANO_IMPL		0x0022 /* Ultra-IIIi+ */

#घोषणा BRANCH_IF_SUN4V(पंचांगp1,label)		\
	sethi	%hi(is_sun4v), %पंचांगp1;		\
	lduw	[%पंचांगp1 + %lo(is_sun4v)], %पंचांगp1; \
	brnz,pn	%पंचांगp1, label;			\
	 nop

#घोषणा BRANCH_IF_CHEETAH_BASE(पंचांगp1,पंचांगp2,label)	\
	rdpr	%ver, %पंचांगp1;			\
	sethi	%hi(__CHEETAH_ID), %पंचांगp2;	\
	srlx	%पंचांगp1, 32, %पंचांगp1;		\
	or	%पंचांगp2, %lo(__CHEETAH_ID), %पंचांगp2;\
	cmp	%पंचांगp1, %पंचांगp2;			\
	be,pn	%icc, label;			\
	 nop;

#घोषणा BRANCH_IF_JALAPENO(पंचांगp1,पंचांगp2,label)	\
	rdpr	%ver, %पंचांगp1;			\
	sethi	%hi(__JALAPENO_ID), %पंचांगp2;	\
	srlx	%पंचांगp1, 32, %पंचांगp1;		\
	or	%पंचांगp2, %lo(__JALAPENO_ID), %पंचांगp2;\
	cmp	%पंचांगp1, %पंचांगp2;			\
	be,pn	%icc, label;			\
	 nop;

#घोषणा BRANCH_IF_CHEETAH_PLUS_OR_FOLLOWON(पंचांगp1,पंचांगp2,label)	\
	rdpr	%ver, %पंचांगp1;			\
	srlx	%पंचांगp1, (32 + 16), %पंचांगp2;	\
	cmp	%पंचांगp2, CHEETAH_MANUF;		\
	bne,pt	%xcc, 99f;			\
	 sllx	%पंचांगp1, 16, %पंचांगp1;		\
	srlx	%पंचांगp1, (32 + 16), %पंचांगp2;	\
	cmp	%पंचांगp2, CHEETAH_PLUS_IMPL;	\
	bgeu,pt	%xcc, label;			\
99:	 nop;

#घोषणा BRANCH_IF_ANY_CHEETAH(पंचांगp1,पंचांगp2,label)	\
	rdpr	%ver, %पंचांगp1;			\
	srlx	%पंचांगp1, (32 + 16), %पंचांगp2;	\
	cmp	%पंचांगp2, CHEETAH_MANUF;		\
	bne,pt	%xcc, 99f;			\
	 sllx	%पंचांगp1, 16, %पंचांगp1;		\
	srlx	%पंचांगp1, (32 + 16), %पंचांगp2;	\
	cmp	%पंचांगp2, CHEETAH_IMPL;		\
	bgeu,pt	%xcc, label;			\
99:	 nop;

#पूर्ण_अगर /* !(_SPARC64_HEAD_H) */
