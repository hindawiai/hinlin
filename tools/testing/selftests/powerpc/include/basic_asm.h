<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SELFTESTS_POWERPC_BASIC_ASM_H
#घोषणा _SELFTESTS_POWERPC_BASIC_ASM_H

#समावेश <ppc-यंत्र.h>
#समावेश <यंत्र/unistd.h>

#घोषणा LOAD_REG_IMMEDIATE(reg, expr) \
	lis	reg, (expr)@highest;	\
	ori	reg, reg, (expr)@higher;	\
	rldicr	reg, reg, 32, 31;	\
	oris	reg, reg, (expr)@high;	\
	ori	reg, reg, (expr)@l;

/*
 * Note: These macros assume that variables being stored on the stack are
 * द्विगुनwords, जबतक this is usually the हाल it may not always be the
 * हाल क्रम each use हाल.
 */
#अगर defined(_CALL_ELF) && _CALL_ELF == 2
#घोषणा STACK_FRAME_MIN_SIZE 32
#घोषणा STACK_FRAME_TOC_POS  24
#घोषणा __STACK_FRAME_PARAM(_param)  (32 + ((_param)*8))
#घोषणा __STACK_FRAME_LOCAL(_num_params, _var_num)  \
	((STACK_FRAME_PARAM(_num_params)) + ((_var_num)*8))
#अन्यथा
#घोषणा STACK_FRAME_MIN_SIZE 112
#घोषणा STACK_FRAME_TOC_POS  40
#घोषणा __STACK_FRAME_PARAM(i)  (48 + ((i)*8))

/*
 * Caveat: अगर a function passed more than 8 द्विगुनwords, the caller will have
 * made more space... which would render the 112 incorrect.
 */
#घोषणा __STACK_FRAME_LOCAL(_num_params, _var_num)  \
	(112 + ((_var_num)*8))
#पूर्ण_अगर

/* Parameter x saved to the stack */
#घोषणा STACK_FRAME_PARAM(var)    __STACK_FRAME_PARAM(var)

/* Local variable x saved to the stack after x parameters */
#घोषणा STACK_FRAME_LOCAL(num_params, var)    \
	__STACK_FRAME_LOCAL(num_params, var)
#घोषणा STACK_FRAME_LR_POS   16
#घोषणा STACK_FRAME_CR_POS   8

/*
 * It is very important to note here that _extra is the extra amount of
 * stack space needed. This space can be accessed using STACK_FRAME_PARAM()
 * or STACK_FRAME_LOCAL() macros.
 *
 * r1 and r2 are not defined in ppc-यंत्र.h (instead they are defined as sp
 * and toc). Kernel programmers tend to prefer rX even क्रम r1 and r2, hence
 * %1 and %r2. r0 is defined in ppc-यंत्र.h and thereक्रमe %r0 माला_लो
 * preprocessed incorrectly, hence r0.
 */
#घोषणा PUSH_BASIC_STACK(_extra) \
	mflr	r0; \
	std	r0, STACK_FRAME_LR_POS(%r1); \
	stdu	%r1, -(_extra + STACK_FRAME_MIN_SIZE)(%r1); \
	mfcr	r0; \
	stw	r0, STACK_FRAME_CR_POS(%r1); \
	std	%r2, STACK_FRAME_TOC_POS(%r1);

#घोषणा POP_BASIC_STACK(_extra) \
	ld	%r2, STACK_FRAME_TOC_POS(%r1); \
	lwz	r0, STACK_FRAME_CR_POS(%r1); \
	mtcr	r0; \
	addi	%r1, %r1, (_extra + STACK_FRAME_MIN_SIZE); \
	ld	r0, STACK_FRAME_LR_POS(%r1); \
	mtlr	r0;

#पूर्ण_अगर /* _SELFTESTS_POWERPC_BASIC_ASM_H */
