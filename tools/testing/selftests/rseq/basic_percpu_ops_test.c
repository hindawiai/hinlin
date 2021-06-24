<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
#घोषणा _GNU_SOURCE
#समावेश <निश्चित.स>
#समावेश <pthपढ़ो.h>
#समावेश <sched.h>
#समावेश <मानक_निवेशt.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <मानकघोष.स>

#समावेश "rseq.h"

#घोषणा ARRAY_SIZE(arr)	(माप(arr) / माप((arr)[0]))

काष्ठा percpu_lock_entry अणु
	पूर्णांकptr_t v;
पूर्ण __attribute__((aligned(128)));

काष्ठा percpu_lock अणु
	काष्ठा percpu_lock_entry c[CPU_SETSIZE];
पूर्ण;

काष्ठा test_data_entry अणु
	पूर्णांकptr_t count;
पूर्ण __attribute__((aligned(128)));

काष्ठा spinlock_test_data अणु
	काष्ठा percpu_lock lock;
	काष्ठा test_data_entry c[CPU_SETSIZE];
	पूर्णांक reps;
पूर्ण;

काष्ठा percpu_list_node अणु
	पूर्णांकptr_t data;
	काष्ठा percpu_list_node *next;
पूर्ण;

काष्ठा percpu_list_entry अणु
	काष्ठा percpu_list_node *head;
पूर्ण __attribute__((aligned(128)));

काष्ठा percpu_list अणु
	काष्ठा percpu_list_entry c[CPU_SETSIZE];
पूर्ण;

/* A simple percpu spinlock.  Returns the cpu lock was acquired on. */
पूर्णांक rseq_this_cpu_lock(काष्ठा percpu_lock *lock)
अणु
	पूर्णांक cpu;

	क्रम (;;) अणु
		पूर्णांक ret;

		cpu = rseq_cpu_start();
		ret = rseq_cmpeqv_storev(&lock->c[cpu].v,
					 0, 1, cpu);
		अगर (rseq_likely(!ret))
			अवरोध;
		/* Retry अगर comparison fails or rseq पातs. */
	पूर्ण
	/*
	 * Acquire semantic when taking lock after control dependency.
	 * Matches rseq_smp_store_release().
	 */
	rseq_smp_acquire__after_ctrl_dep();
	वापस cpu;
पूर्ण

व्योम rseq_percpu_unlock(काष्ठा percpu_lock *lock, पूर्णांक cpu)
अणु
	निश्चित(lock->c[cpu].v == 1);
	/*
	 * Release lock, with release semantic. Matches
	 * rseq_smp_acquire__after_ctrl_dep().
	 */
	rseq_smp_store_release(&lock->c[cpu].v, 0);
पूर्ण

व्योम *test_percpu_spinlock_thपढ़ो(व्योम *arg)
अणु
	काष्ठा spinlock_test_data *data = arg;
	पूर्णांक i, cpu;

	अगर (rseq_रेजिस्टर_current_thपढ़ो()) अणु
		ख_लिखो(मानक_त्रुटि, "Error: rseq_register_current_thread(...) failed(%d): %s\n",
			त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
		पात();
	पूर्ण
	क्रम (i = 0; i < data->reps; i++) अणु
		cpu = rseq_this_cpu_lock(&data->lock);
		data->c[cpu].count++;
		rseq_percpu_unlock(&data->lock, cpu);
	पूर्ण
	अगर (rseq_unरेजिस्टर_current_thपढ़ो()) अणु
		ख_लिखो(मानक_त्रुटि, "Error: rseq_unregister_current_thread(...) failed(%d): %s\n",
			त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
		पात();
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * A simple test which implements a sharded counter using a per-cpu
 * lock.  Obviously real applications might prefer to simply use a
 * per-cpu increment; however, this is reasonable क्रम a test and the
 * lock can be extended to synchronize more complicated operations.
 */
व्योम test_percpu_spinlock(व्योम)
अणु
	स्थिर पूर्णांक num_thपढ़ोs = 200;
	पूर्णांक i;
	uपूर्णांक64_t sum;
	pthपढ़ो_t test_thपढ़ोs[num_thपढ़ोs];
	काष्ठा spinlock_test_data data;

	स_रखो(&data, 0, माप(data));
	data.reps = 5000;

	क्रम (i = 0; i < num_thपढ़ोs; i++)
		pthपढ़ो_create(&test_thपढ़ोs[i], शून्य,
			       test_percpu_spinlock_thपढ़ो, &data);

	क्रम (i = 0; i < num_thपढ़ोs; i++)
		pthपढ़ो_join(test_thपढ़ोs[i], शून्य);

	sum = 0;
	क्रम (i = 0; i < CPU_SETSIZE; i++)
		sum += data.c[i].count;

	निश्चित(sum == (uपूर्णांक64_t)data.reps * num_thपढ़ोs);
पूर्ण

व्योम this_cpu_list_push(काष्ठा percpu_list *list,
			काष्ठा percpu_list_node *node,
			पूर्णांक *_cpu)
अणु
	पूर्णांक cpu;

	क्रम (;;) अणु
		पूर्णांकptr_t *targetptr, newval, expect;
		पूर्णांक ret;

		cpu = rseq_cpu_start();
		/* Load list->c[cpu].head with single-copy atomicity. */
		expect = (पूर्णांकptr_t)RSEQ_READ_ONCE(list->c[cpu].head);
		newval = (पूर्णांकptr_t)node;
		targetptr = (पूर्णांकptr_t *)&list->c[cpu].head;
		node->next = (काष्ठा percpu_list_node *)expect;
		ret = rseq_cmpeqv_storev(targetptr, expect, newval, cpu);
		अगर (rseq_likely(!ret))
			अवरोध;
		/* Retry अगर comparison fails or rseq पातs. */
	पूर्ण
	अगर (_cpu)
		*_cpu = cpu;
पूर्ण

/*
 * Unlike a traditional lock-less linked list; the availability of a
 * rseq primitive allows us to implement pop without concerns over
 * ABA-type races.
 */
काष्ठा percpu_list_node *this_cpu_list_pop(काष्ठा percpu_list *list,
					   पूर्णांक *_cpu)
अणु
	क्रम (;;) अणु
		काष्ठा percpu_list_node *head;
		पूर्णांकptr_t *targetptr, expectnot, *load;
		off_t offset;
		पूर्णांक ret, cpu;

		cpu = rseq_cpu_start();
		targetptr = (पूर्णांकptr_t *)&list->c[cpu].head;
		expectnot = (पूर्णांकptr_t)शून्य;
		offset = दुरत्व(काष्ठा percpu_list_node, next);
		load = (पूर्णांकptr_t *)&head;
		ret = rseq_cmpnev_storeoffp_load(targetptr, expectnot,
						 offset, load, cpu);
		अगर (rseq_likely(!ret)) अणु
			अगर (_cpu)
				*_cpu = cpu;
			वापस head;
		पूर्ण
		अगर (ret > 0)
			वापस शून्य;
		/* Retry अगर rseq पातs. */
	पूर्ण
पूर्ण

/*
 * __percpu_list_pop is not safe against concurrent accesses. Should
 * only be used on lists that are not concurrently modअगरied.
 */
काष्ठा percpu_list_node *__percpu_list_pop(काष्ठा percpu_list *list, पूर्णांक cpu)
अणु
	काष्ठा percpu_list_node *node;

	node = list->c[cpu].head;
	अगर (!node)
		वापस शून्य;
	list->c[cpu].head = node->next;
	वापस node;
पूर्ण

व्योम *test_percpu_list_thपढ़ो(व्योम *arg)
अणु
	पूर्णांक i;
	काष्ठा percpu_list *list = (काष्ठा percpu_list *)arg;

	अगर (rseq_रेजिस्टर_current_thपढ़ो()) अणु
		ख_लिखो(मानक_त्रुटि, "Error: rseq_register_current_thread(...) failed(%d): %s\n",
			त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
		पात();
	पूर्ण

	क्रम (i = 0; i < 100000; i++) अणु
		काष्ठा percpu_list_node *node;

		node = this_cpu_list_pop(list, शून्य);
		sched_yield();  /* encourage shuffling */
		अगर (node)
			this_cpu_list_push(list, node, शून्य);
	पूर्ण

	अगर (rseq_unरेजिस्टर_current_thपढ़ो()) अणु
		ख_लिखो(मानक_त्रुटि, "Error: rseq_unregister_current_thread(...) failed(%d): %s\n",
			त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
		पात();
	पूर्ण

	वापस शून्य;
पूर्ण

/* Simultaneous modअगरication to a per-cpu linked list from many thपढ़ोs.  */
व्योम test_percpu_list(व्योम)
अणु
	पूर्णांक i, j;
	uपूर्णांक64_t sum = 0, expected_sum = 0;
	काष्ठा percpu_list list;
	pthपढ़ो_t test_thपढ़ोs[200];
	cpu_set_t allowed_cpus;

	स_रखो(&list, 0, माप(list));

	/* Generate list entries क्रम every usable cpu. */
	sched_getaffinity(0, माप(allowed_cpus), &allowed_cpus);
	क्रम (i = 0; i < CPU_SETSIZE; i++) अणु
		अगर (!CPU_ISSET(i, &allowed_cpus))
			जारी;
		क्रम (j = 1; j <= 100; j++) अणु
			काष्ठा percpu_list_node *node;

			expected_sum += j;

			node = दो_स्मृति(माप(*node));
			निश्चित(node);
			node->data = j;
			node->next = list.c[i].head;
			list.c[i].head = node;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 200; i++)
		pthपढ़ो_create(&test_thपढ़ोs[i], शून्य,
		       test_percpu_list_thपढ़ो, &list);

	क्रम (i = 0; i < 200; i++)
		pthपढ़ो_join(test_thपढ़ोs[i], शून्य);

	क्रम (i = 0; i < CPU_SETSIZE; i++) अणु
		काष्ठा percpu_list_node *node;

		अगर (!CPU_ISSET(i, &allowed_cpus))
			जारी;

		जबतक ((node = __percpu_list_pop(&list, i))) अणु
			sum += node->data;
			मुक्त(node);
		पूर्ण
	पूर्ण

	/*
	 * All entries should now be accounted क्रम (unless some बाह्यal
	 * actor is पूर्णांकerfering with our allowed affinity जबतक this
	 * test is running).
	 */
	निश्चित(sum == expected_sum);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	अगर (rseq_रेजिस्टर_current_thपढ़ो()) अणु
		ख_लिखो(मानक_त्रुटि, "Error: rseq_register_current_thread(...) failed(%d): %s\n",
			त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
		जाओ error;
	पूर्ण
	म_लिखो("spinlock\n");
	test_percpu_spinlock();
	म_लिखो("percpu_list\n");
	test_percpu_list();
	अगर (rseq_unरेजिस्टर_current_thपढ़ो()) अणु
		ख_लिखो(मानक_त्रुटि, "Error: rseq_unregister_current_thread(...) failed(%d): %s\n",
			त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
		जाओ error;
	पूर्ण
	वापस 0;

error:
	वापस -1;
पूर्ण
