<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2005 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_SWITCH_TO_H
#घोषणा _XTENSA_SWITCH_TO_H

/* * चयन_to(n) should चयन tasks to task nr n, first
 * checking that n isn't the current task, in which हाल it करोes nothing.
 */
बाह्य व्योम *_चयन_to(व्योम *last, व्योम *next);

#घोषणा चयन_to(prev,next,last)		\
करो अणु						\
	(last) = _चयन_to(prev, next);	\
पूर्ण जबतक(0)

#पूर्ण_अगर /* _XTENSA_SWITCH_TO_H */
