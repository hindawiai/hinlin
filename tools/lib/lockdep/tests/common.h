<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LIBLOCKDEP_TEST_COMMON_H
#घोषणा _LIBLOCKDEP_TEST_COMMON_H

#घोषणा LOCK_UNLOCK_2(a, b)			\
	करो अणु					\
		pthपढ़ो_mutex_lock(&(a));	\
		pthपढ़ो_mutex_lock(&(b));	\
		pthपढ़ो_mutex_unlock(&(b));	\
		pthपढ़ो_mutex_unlock(&(a));	\
	पूर्ण जबतक(0)

#पूर्ण_अगर
