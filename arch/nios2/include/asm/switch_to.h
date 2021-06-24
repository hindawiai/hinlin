<शैली गुरु>
/*
 * Copyright (C) 2004 Microtronix Datacom Ltd.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#अगर_अघोषित _ASM_NIOS2_SWITCH_TO_H
#घोषणा _ASM_NIOS2_SWITCH_TO_H

/*
 * चयन_to(n) should चयन tasks to task ptr, first checking that
 * ptr isn't the current task, in which हाल it करोes nothing.  This
 * also clears the TS-flag अगर the task we चयनed to has used the
 * math co-processor latest.
 */
#घोषणा चयन_to(prev, next, last)			\
अणु							\
	व्योम *_last;					\
	__यंत्र__ __अस्थिर__ (				\
		"mov	r4, %1\n"			\
		"mov	r5, %2\n"			\
		"call	resume\n"			\
		"mov	%0,r4\n"			\
		: "=r" (_last)				\
		: "r" (prev), "r" (next)		\
		: "r4", "r5", "r7", "r8", "ra");	\
	(last) = _last;					\
पूर्ण

#पूर्ण_अगर /* _ASM_NIOS2_SWITCH_TO_H */
