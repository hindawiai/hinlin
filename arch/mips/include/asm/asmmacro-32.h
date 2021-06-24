<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * यंत्रmacro.h: Assembler macros to make things easier to पढ़ो.
 *
 * Copyright (C) 1996 David S. Miller (davem@davemloft.net)
 * Copyright (C) 1998, 1999, 2003 Ralf Baechle
 */
#अगर_अघोषित _ASM_ASMMACRO_32_H
#घोषणा _ASM_ASMMACRO_32_H

#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश <यंत्र/regdef.h>
#समावेश <यंत्र/fpregdef.h>
#समावेश <यंत्र/mipsregs.h>

	.macro	fpu_save_single thपढ़ो पंचांगp=t0
	.set push
	SET_HARDFLOAT
	cfc1	\टmp,  fcr31
	s.d	$f0,  THREAD_FPR0(\टhपढ़ो)
	s.d	$f2,  THREAD_FPR2(\टhपढ़ो)
	s.d	$f4,  THREAD_FPR4(\टhपढ़ो)
	s.d	$f6,  THREAD_FPR6(\टhपढ़ो)
	s.d	$f8,  THREAD_FPR8(\टhपढ़ो)
	s.d	$f10, THREAD_FPR10(\टhपढ़ो)
	s.d	$f12, THREAD_FPR12(\टhपढ़ो)
	s.d	$f14, THREAD_FPR14(\टhपढ़ो)
	s.d	$f16, THREAD_FPR16(\टhपढ़ो)
	s.d	$f18, THREAD_FPR18(\टhपढ़ो)
	s.d	$f20, THREAD_FPR20(\टhपढ़ो)
	s.d	$f22, THREAD_FPR22(\टhपढ़ो)
	s.d	$f24, THREAD_FPR24(\टhपढ़ो)
	s.d	$f26, THREAD_FPR26(\टhपढ़ो)
	s.d	$f28, THREAD_FPR28(\टhपढ़ो)
	s.d	$f30, THREAD_FPR30(\टhपढ़ो)
	sw	\टmp, THREAD_FCR31(\टhपढ़ो)
	.set pop
	.endm

	.macro	fpu_restore_single thपढ़ो पंचांगp=t0
	.set push
	SET_HARDFLOAT
	lw	\टmp, THREAD_FCR31(\टhपढ़ो)
	l.d	$f0,  THREAD_FPR0(\टhपढ़ो)
	l.d	$f2,  THREAD_FPR2(\टhपढ़ो)
	l.d	$f4,  THREAD_FPR4(\टhपढ़ो)
	l.d	$f6,  THREAD_FPR6(\टhपढ़ो)
	l.d	$f8,  THREAD_FPR8(\टhपढ़ो)
	l.d	$f10, THREAD_FPR10(\टhपढ़ो)
	l.d	$f12, THREAD_FPR12(\टhपढ़ो)
	l.d	$f14, THREAD_FPR14(\टhपढ़ो)
	l.d	$f16, THREAD_FPR16(\टhपढ़ो)
	l.d	$f18, THREAD_FPR18(\टhपढ़ो)
	l.d	$f20, THREAD_FPR20(\टhपढ़ो)
	l.d	$f22, THREAD_FPR22(\टhपढ़ो)
	l.d	$f24, THREAD_FPR24(\टhपढ़ो)
	l.d	$f26, THREAD_FPR26(\टhपढ़ो)
	l.d	$f28, THREAD_FPR28(\टhपढ़ो)
	l.d	$f30, THREAD_FPR30(\टhपढ़ो)
	ctc1	\टmp, fcr31
	.set pop
	.endm

	.macro	cpu_save_nonscratch thपढ़ो
	LONG_S	s0, THREAD_REG16(\टhपढ़ो)
	LONG_S	s1, THREAD_REG17(\टhपढ़ो)
	LONG_S	s2, THREAD_REG18(\टhपढ़ो)
	LONG_S	s3, THREAD_REG19(\टhपढ़ो)
	LONG_S	s4, THREAD_REG20(\टhपढ़ो)
	LONG_S	s5, THREAD_REG21(\टhपढ़ो)
	LONG_S	s6, THREAD_REG22(\टhपढ़ो)
	LONG_S	s7, THREAD_REG23(\टhपढ़ो)
	LONG_S	sp, THREAD_REG29(\टhपढ़ो)
	LONG_S	fp, THREAD_REG30(\टhपढ़ो)
	.endm

	.macro	cpu_restore_nonscratch thपढ़ो
	LONG_L	s0, THREAD_REG16(\टhपढ़ो)
	LONG_L	s1, THREAD_REG17(\टhपढ़ो)
	LONG_L	s2, THREAD_REG18(\टhपढ़ो)
	LONG_L	s3, THREAD_REG19(\टhपढ़ो)
	LONG_L	s4, THREAD_REG20(\टhपढ़ो)
	LONG_L	s5, THREAD_REG21(\टhपढ़ो)
	LONG_L	s6, THREAD_REG22(\टhपढ़ो)
	LONG_L	s7, THREAD_REG23(\टhपढ़ो)
	LONG_L	sp, THREAD_REG29(\टhपढ़ो)
	LONG_L	fp, THREAD_REG30(\टhपढ़ो)
	LONG_L	ra, THREAD_REG31(\टhपढ़ो)
	.endm

#पूर्ण_अगर /* _ASM_ASMMACRO_32_H */
