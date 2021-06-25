<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * यंत्रmacro.h: Assembler macros to make things easier to पढ़ो.
 *
 * Copyright (C) 1996 David S. Miller (davem@davemloft.net)
 * Copyright (C) 1998, 1999 Ralf Baechle
 * Copyright (C) 1999 Silicon Graphics, Inc.
 */
#अगर_अघोषित _ASM_ASMMACRO_64_H
#घोषणा _ASM_ASMMACRO_64_H

#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश <यंत्र/regdef.h>
#समावेश <यंत्र/fpregdef.h>
#समावेश <यंत्र/mipsregs.h>

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

#पूर्ण_अगर /* _ASM_ASMMACRO_64_H */
