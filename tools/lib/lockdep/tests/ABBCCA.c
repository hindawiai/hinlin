<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <liblockdep/mutex.h>
#समावेश "common.h"

व्योम मुख्य(व्योम)
अणु
	pthपढ़ो_mutex_t a, b, c;

	pthपढ़ो_mutex_init(&a, शून्य);
	pthपढ़ो_mutex_init(&b, शून्य);
	pthपढ़ो_mutex_init(&c, शून्य);

	LOCK_UNLOCK_2(a, b);
	LOCK_UNLOCK_2(b, c);
	LOCK_UNLOCK_2(c, a);

	pthपढ़ो_mutex_destroy(&c);
	pthपढ़ो_mutex_destroy(&b);
	pthपढ़ो_mutex_destroy(&a);
पूर्ण
