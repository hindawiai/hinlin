<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _M68K_SWITCH_TO_H
#घोषणा _M68K_SWITCH_TO_H

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
 * pass prev in a0, next in a1
 */
यंत्रlinkage व्योम resume(व्योम);
#घोषणा चयन_to(prev,next,last) करो अणु \
  रेजिस्टर व्योम *_prev __यंत्र__ ("a0") = (prev); \
  रेजिस्टर व्योम *_next __यंत्र__ ("a1") = (next); \
  रेजिस्टर व्योम *_last __यंत्र__ ("d1"); \
  __यंत्र__ __अस्थिर__("jbsr resume" \
		       : "=a" (_prev), "=a" (_next), "=d" (_last) \
		       : "0" (_prev), "1" (_next) \
		       : "d0", "d2", "d3", "d4", "d5"); \
  (last) = _last; \
पूर्ण जबतक (0)

#पूर्ण_अगर /* _M68K_SWITCH_TO_H */
