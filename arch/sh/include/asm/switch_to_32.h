<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_SWITCH_TO_32_H
#घोषणा __ASM_SH_SWITCH_TO_32_H

#अगर_घोषित CONFIG_SH_DSP

#घोषणा is_dsp_enabled(tsk)						\
	(!!(tsk->thपढ़ो.dsp_status.status & SR_DSP))

#घोषणा __restore_dsp(tsk)						\
करो अणु									\
	रेजिस्टर u32 *__ts2 __यंत्र__ ("r2") =				\
			(u32 *)&tsk->thपढ़ो.dsp_status;			\
	__यंत्र__ __अस्थिर__ (						\
		".balign 4\n\t"						\
		"movs.l	@r2+, a0\n\t"					\
		"movs.l	@r2+, a1\n\t"					\
		"movs.l	@r2+, a0g\n\t"					\
		"movs.l	@r2+, a1g\n\t"					\
		"movs.l	@r2+, m0\n\t"					\
		"movs.l	@r2+, m1\n\t"					\
		"movs.l	@r2+, x0\n\t"					\
		"movs.l	@r2+, x1\n\t"					\
		"movs.l	@r2+, y0\n\t"					\
		"movs.l	@r2+, y1\n\t"					\
		"lds.l	@r2+, dsr\n\t"					\
		"ldc.l	@r2+, rs\n\t"					\
		"ldc.l	@r2+, re\n\t"					\
		"ldc.l	@r2+, mod\n\t"					\
		: : "r" (__ts2));					\
पूर्ण जबतक (0)

#घोषणा __save_dsp(tsk)							\
करो अणु									\
	रेजिस्टर u32 *__ts2 __यंत्र__ ("r2") =				\
			(u32 *)&tsk->thपढ़ो.dsp_status + 14;		\
									\
	__यंत्र__ __अस्थिर__ (						\
		".balign 4\n\t"						\
		"stc.l	mod, @-r2\n\t"					\
		"stc.l	re, @-r2\n\t"					\
		"stc.l	rs, @-r2\n\t"					\
		"sts.l	dsr, @-r2\n\t"					\
		"movs.l	y1, @-r2\n\t"					\
		"movs.l	y0, @-r2\n\t"					\
		"movs.l	x1, @-r2\n\t"					\
		"movs.l	x0, @-r2\n\t"					\
		"movs.l	m1, @-r2\n\t"					\
		"movs.l	m0, @-r2\n\t"					\
		"movs.l	a1g, @-r2\n\t"					\
		"movs.l	a0g, @-r2\n\t"					\
		"movs.l	a1, @-r2\n\t"					\
		"movs.l	a0, @-r2\n\t"					\
		: : "r" (__ts2));					\
पूर्ण जबतक (0)

#अन्यथा

#घोषणा is_dsp_enabled(tsk)	(0)
#घोषणा __save_dsp(tsk)		करो अणु पूर्ण जबतक (0)
#घोषणा __restore_dsp(tsk)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

काष्ठा task_काष्ठा *__चयन_to(काष्ठा task_काष्ठा *prev,
				काष्ठा task_काष्ठा *next);

/*
 *	चयन_to() should चयन tasks to task nr n, first
 */
#घोषणा चयन_to(prev, next, last)				\
करो अणु								\
	रेजिस्टर u32 *__ts1 __यंत्र__ ("r1");			\
	रेजिस्टर u32 *__ts2 __यंत्र__ ("r2");			\
	रेजिस्टर u32 *__ts4 __यंत्र__ ("r4");			\
	रेजिस्टर u32 *__ts5 __यंत्र__ ("r5");			\
	रेजिस्टर u32 *__ts6 __यंत्र__ ("r6");			\
	रेजिस्टर u32 __ts7 __यंत्र__ ("r7");			\
	काष्ठा task_काष्ठा *__last;				\
								\
	अगर (is_dsp_enabled(prev))				\
		__save_dsp(prev);				\
	अगर (is_dsp_enabled(next))				\
		__restore_dsp(next);				\
								\
	__ts1 = (u32 *)&prev->thपढ़ो.sp;			\
	__ts2 = (u32 *)&prev->thपढ़ो.pc;			\
	__ts4 = (u32 *)prev;					\
	__ts5 = (u32 *)next;					\
	__ts6 = (u32 *)&next->thपढ़ो.sp;			\
	__ts7 = next->thपढ़ो.pc;				\
								\
	__यंत्र__ __अस्थिर__ (					\
		".balign 4\n\t"					\
		"stc.l	gbr, @-r15\n\t"				\
		"sts.l	pr, @-r15\n\t"				\
		"mov.l	r8, @-r15\n\t"				\
		"mov.l	r9, @-r15\n\t"				\
		"mov.l	r10, @-r15\n\t"				\
		"mov.l	r11, @-r15\n\t"				\
		"mov.l	r12, @-r15\n\t"				\
		"mov.l	r13, @-r15\n\t"				\
		"mov.l	r14, @-r15\n\t"				\
		"mov.l	r15, @r1\t! save SP\n\t"		\
		"mov.l	@r6, r15\t! change to new stack\n\t"	\
		"mova	1f, %0\n\t"				\
		"mov.l	%0, @r2\t! save PC\n\t"			\
		"mov.l	2f, %0\n\t"				\
		"jmp	@%0\t! call __switch_to\n\t"		\
		" lds	r7, pr\t!  with return to new PC\n\t"	\
		".balign	4\n"				\
		"2:\n\t"					\
		".long	__switch_to\n"				\
		"1:\n\t"					\
		"mov.l	@r15+, r14\n\t"				\
		"mov.l	@r15+, r13\n\t"				\
		"mov.l	@r15+, r12\n\t"				\
		"mov.l	@r15+, r11\n\t"				\
		"mov.l	@r15+, r10\n\t"				\
		"mov.l	@r15+, r9\n\t"				\
		"mov.l	@r15+, r8\n\t"				\
		"lds.l	@r15+, pr\n\t"				\
		"ldc.l	@r15+, gbr\n\t"				\
		: "=z" (__last)					\
		: "r" (__ts1), "r" (__ts2), "r" (__ts4),	\
		  "r" (__ts5), "r" (__ts6), "r" (__ts7)		\
		: "r3", "t");					\
								\
	last = __last;						\
पूर्ण जबतक (0)

#पूर्ण_अगर /* __ASM_SH_SWITCH_TO_32_H */
