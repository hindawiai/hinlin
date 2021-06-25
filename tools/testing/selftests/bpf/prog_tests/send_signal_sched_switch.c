<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <sys/mman.h>
#समावेश <pthपढ़ो.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश "test_send_signal_kern.skel.h"

अटल व्योम sigusr1_handler(पूर्णांक signum)
अणु
पूर्ण

#घोषणा THREAD_COUNT 100

अटल व्योम *worker(व्योम *p)
अणु
	पूर्णांक i;

	क्रम ( i = 0; i < 1000; i++)
		usleep(1);

	वापस शून्य;
पूर्ण

व्योम test_send_संकेत_sched_चयन(व्योम)
अणु
	काष्ठा test_send_संकेत_kern *skel;
	pthपढ़ो_t thपढ़ोs[THREAD_COUNT];
	u32 duration = 0;
	पूर्णांक i, err;

	संकेत(SIGUSR1, sigusr1_handler);

	skel = test_send_संकेत_kern__खोलो_and_load();
	अगर (CHECK(!skel, "skel_open_and_load", "skeleton open_and_load failed\n"))
		वापस;

	skel->bss->pid = getpid();
	skel->bss->sig = SIGUSR1;

	err = test_send_संकेत_kern__attach(skel);
	अगर (CHECK(err, "skel_attach", "skeleton attach failed\n"))
		जाओ destroy_skel;

	क्रम (i = 0; i < THREAD_COUNT; i++) अणु
		err = pthपढ़ो_create(thपढ़ोs + i, शून्य, worker, शून्य);
		अगर (CHECK(err, "pthread_create", "Error creating thread, %s\n",
			  म_त्रुटि(त्रुटि_सं)))
			जाओ destroy_skel;
	पूर्ण

	क्रम (i = 0; i < THREAD_COUNT; i++)
		pthपढ़ो_join(thपढ़ोs[i], शून्य);

destroy_skel:
	test_send_संकेत_kern__destroy(skel);
पूर्ण
