<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _H8300_SWITCH_TO_H
#घोषणा _H8300_SWITCH_TO_H

/*
 * चयन_to(n) should चयन tasks to task ptr, first checking that
 * ptr isn't the current task, in which हाल it करोes nothing.  This
 * also clears the TS-flag अगर the task we चयनed to has used the
 * math co-processor latest.
 */
/*
 * चयन_to() saves the extra रेजिस्टरs, that are not saved
 * स्वतःmatically by SAVE_SWITCH_STACK in resume(), ie. d0-d5 and
 * a0-a1. Some of these are used by schedule() and its predecessors
 * and so we might get see unexpected behaviors when a task वापसs
 * with unexpected रेजिस्टर values.
 *
 * syscall stores these रेजिस्टरs itself and none of them are used
 * by syscall after the function in the syscall has been called.
 *
 * Beware that resume now expects *next to be in d1 and the offset of
 * tss to be in a1. This saves a few inकाष्ठाions as we no दीर्घer have
 * to push them onto the stack and पढ़ो them back right after.
 *
 * 02/17/96 - Jes Sorensen (jds@kom.auc.dk)
 *
 * Changed 96/09/19 by Andreas Schwab
 * pass prev in a0, next in a1, offset of tss in d1, and whether
 * the mm काष्ठाures are shared in d2 (to aव्योम atc flushing).
 *
 * H8/300 Porting 2002/09/04 Yoshinori Sato
 */

यंत्रlinkage व्योम resume(व्योम);
#घोषणा चयन_to(prev, next, last) \
करो अणु			     \
	व्योम *_last;					    \
	__यंत्र__ __अस्थिर__(				    \
		"mov.l	%1, er0\n\t"			    \
		"mov.l	%2, er1\n\t"			    \
		"mov.l	%3, er2\n\t"			    \
		"jsr @_resume\n\t"			    \
		"mov.l	er2,%0\n\t"			    \
		: "=r" (_last)				    \
		: "r" (&(prev->thपढ़ो)),		    \
		  "r" (&(next->thपढ़ो)),		    \
		  "g" (prev)				    \
		: "cc", "er0", "er1", "er2", "er3");	    \
	(last) = _last;					    \
पूर्ण जबतक (0)

#पूर्ण_अगर /* _H8300_SWITCH_TO_H */
