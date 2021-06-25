<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_CSKY_TRAPS_H
#घोषणा __ASM_CSKY_TRAPS_H

#घोषणा VEC_RESET	0
#घोषणा VEC_ALIGN	1
#घोषणा VEC_ACCESS	2
#घोषणा VEC_ZERODIV	3
#घोषणा VEC_ILLEGAL	4
#घोषणा VEC_PRIV	5
#घोषणा VEC_TRACE	6
#घोषणा VEC_BREAKPOINT	7
#घोषणा VEC_UNRECOVER	8
#घोषणा VEC_SOFTRESET	9
#घोषणा VEC_AUTOVEC	10
#घोषणा VEC_FAUTOVEC	11
#घोषणा VEC_HWACCEL	12

#घोषणा	VEC_TLBMISS	14
#घोषणा	VEC_TLBMODIFIED	15

#घोषणा VEC_TRAP0	16
#घोषणा VEC_TRAP1	17
#घोषणा VEC_TRAP2	18
#घोषणा VEC_TRAP3	19

#घोषणा	VEC_TLBINVALIDL	20
#घोषणा	VEC_TLBINVALIDS	21

#घोषणा VEC_PRFL	29
#घोषणा VEC_FPE		30

बाह्य व्योम *vec_base[];

#घोषणा VEC_INIT(i, func) \
करो अणु \
	vec_base[i] = (व्योम *)func; \
पूर्ण जबतक (0)

व्योम csky_alignment(काष्ठा pt_regs *regs);

#पूर्ण_अगर /* __ASM_CSKY_TRAPS_H */
