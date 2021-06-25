<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश <pthपढ़ो.h>

pthपढ़ो_mutex_t a = PTHREAD_MUTEX_INITIALIZER;
pthपढ़ो_mutex_t b = PTHREAD_MUTEX_INITIALIZER;
pthपढ़ो_barrier_t bar;

व्योम *ba_lock(व्योम *arg)
अणु
	पूर्णांक ret, i;

	pthपढ़ो_mutex_lock(&b);

	अगर (pthपढ़ो_barrier_रुको(&bar) == PTHREAD_BARRIER_SERIAL_THREAD)
		pthपढ़ो_barrier_destroy(&bar);

	pthपढ़ो_mutex_lock(&a);

	pthपढ़ो_mutex_unlock(&a);
	pthपढ़ो_mutex_unlock(&b);
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	pthपढ़ो_t t;

	pthपढ़ो_barrier_init(&bar, शून्य, 2);

	अगर (pthपढ़ो_create(&t, शून्य, ba_lock, शून्य)) अणु
		ख_लिखो(मानक_त्रुटि, "pthread_create() failed\n");
		वापस 1;
	पूर्ण
	pthपढ़ो_mutex_lock(&a);

	अगर (pthपढ़ो_barrier_रुको(&bar) == PTHREAD_BARRIER_SERIAL_THREAD)
		pthपढ़ो_barrier_destroy(&bar);

	pthपढ़ो_mutex_lock(&b);

	pthपढ़ो_mutex_unlock(&b);
	pthपढ़ो_mutex_unlock(&a);

	pthपढ़ो_join(t, शून्य);

	वापस 0;
पूर्ण
