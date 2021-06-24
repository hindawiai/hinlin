<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ASSUME_H
#घोषणा ASSUME_H

/* Provide an assumption macro that can be disabled क्रम gcc. */
#अगर_घोषित RUN
#घोषणा assume(x) \
	करो अणु \
		/* Evaluate x to suppress warnings. */ \
		(व्योम) (x); \
	पूर्ण जबतक (0)

#अन्यथा
#घोषणा assume(x) __CPROVER_assume(x)
#पूर्ण_अगर

#पूर्ण_अगर
