<शैली गुरु>
/* thपढ़ोtest.c
 *		by: john stultz (johnstul@us.ibm.com)
 *		(C) Copyright IBM 2004, 2005, 2006, 2012
 *		Licensed under the GPLv2
 *
 *  To build:
 *	$ gcc thपढ़ोtest.c -o thपढ़ोtest -lrt
 *
 *   This program is मुक्त software: you can redistribute it and/or modअगरy
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License क्रम more details.
 */
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <sys/समय.स>
#समावेश <pthपढ़ो.h>
#समावेश "../kselftest.h"

/* serializes shared list access */
pthपढ़ो_mutex_t list_lock = PTHREAD_MUTEX_INITIALIZER;
/* serializes console output */
pthपढ़ो_mutex_t prपूर्णांक_lock = PTHREAD_MUTEX_INITIALIZER;


#घोषणा MAX_THREADS 128
#घोषणा LISTSIZE 128

पूर्णांक करोne = 0;

काष्ठा बारpec global_list[LISTSIZE];
पूर्णांक listcount = 0;


व्योम checklist(काष्ठा बारpec *list, पूर्णांक size)
अणु
	पूर्णांक i, j;
	काष्ठा बारpec *a, *b;

	/* scan the list */
	क्रम (i = 0; i < size-1; i++) अणु
		a = &list[i];
		b = &list[i+1];

		/* look क्रम any समय inconsistencies */
		अगर ((b->tv_sec <= a->tv_sec) &&
			(b->tv_nsec < a->tv_nsec)) अणु

			/* flag other thपढ़ोs */
			करोne = 1;

			/*serialize prपूर्णांकing to aव्योम junky output*/
			pthपढ़ो_mutex_lock(&prपूर्णांक_lock);

			/* dump the list */
			म_लिखो("\n");
			क्रम (j = 0; j < size; j++) अणु
				अगर (j == i)
					म_लिखो("---------------\n");
				म_लिखो("%lu:%lu\n", list[j].tv_sec, list[j].tv_nsec);
				अगर (j == i+1)
					म_लिखो("---------------\n");
			पूर्ण
			म_लिखो("[FAILED]\n");

			pthपढ़ो_mutex_unlock(&prपूर्णांक_lock);
		पूर्ण
	पूर्ण
पूर्ण

/* The shared thपढ़ो shares a global list
 * that each thपढ़ो fills जबतक holding the lock.
 * This stresses घड़ी synchronization across cpus.
 */
व्योम *shared_thपढ़ो(व्योम *arg)
अणु
	जबतक (!करोne) अणु
		/* protect the list */
		pthपढ़ो_mutex_lock(&list_lock);

		/* see अगर we're पढ़ोy to check the list */
		अगर (listcount >= LISTSIZE) अणु
			checklist(global_list, LISTSIZE);
			listcount = 0;
		पूर्ण
		घड़ी_समय_लो(CLOCK_MONOTONIC, &global_list[listcount++]);

		pthपढ़ो_mutex_unlock(&list_lock);
	पूर्ण
	वापस शून्य;
पूर्ण


/* Each independent thपढ़ो fills in its own
 * list. This stresses घड़ी_समय_लो() lock contention.
 */
व्योम *independent_thपढ़ो(व्योम *arg)
अणु
	काष्ठा बारpec my_list[LISTSIZE];
	पूर्णांक count;

	जबतक (!करोne) अणु
		/* fill the list */
		क्रम (count = 0; count < LISTSIZE; count++)
			घड़ी_समय_लो(CLOCK_MONOTONIC, &my_list[count]);
		checklist(my_list, LISTSIZE);
	पूर्ण
	वापस शून्य;
पूर्ण

#घोषणा DEFAULT_THREAD_COUNT 8
#घोषणा DEFAULT_RUNTIME 30

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक thपढ़ो_count, i;
	समय_प्रकार start, now, runसमय;
	अक्षर buf[255];
	pthपढ़ो_t pth[MAX_THREADS];
	पूर्णांक opt;
	व्योम *tret;
	पूर्णांक ret = 0;
	व्योम *(*thपढ़ो)(व्योम *) = shared_thपढ़ो;

	thपढ़ो_count = DEFAULT_THREAD_COUNT;
	runसमय = DEFAULT_RUNTIME;

	/* Process arguments */
	जबतक ((opt = getopt(argc, argv, "t:n:i")) != -1) अणु
		चयन (opt) अणु
		हाल 't':
			runसमय = म_से_प(optarg);
			अवरोध;
		हाल 'n':
			thपढ़ो_count = म_से_प(optarg);
			अवरोध;
		हाल 'i':
			thपढ़ो = independent_thपढ़ो;
			म_लिखो("using independent threads\n");
			अवरोध;
		शेष:
			म_लिखो("Usage: %s [-t <secs>] [-n <numthreads>] [-i]\n", argv[0]);
			म_लिखो("	-t: time to run\n");
			म_लिखो("	-n: number of threads\n");
			म_लिखो("	-i: use independent threads\n");
			वापस -1;
		पूर्ण
	पूर्ण

	अगर (thपढ़ो_count > MAX_THREADS)
		thपढ़ो_count = MAX_THREADS;


	रखो_बफ(मानक_निकास, शून्य);

	start = समय(0);
	स_माला(buf, 255, "%a, %d %b %Y %T %z", स_स्थानीय(&start));
	म_लिखो("%s\n", buf);
	म_लिखो("Testing consistency with %i threads for %ld seconds: ", thपढ़ो_count, runसमय);
	ख_साफ(मानक_निकास);

	/* spawn */
	क्रम (i = 0; i < thपढ़ो_count; i++)
		pthपढ़ो_create(&pth[i], 0, thपढ़ो, 0);

	जबतक (समय(&now) < start + runसमय) अणु
		sleep(1);
		अगर (करोne) अणु
			ret = 1;
			स_माला(buf, 255, "%a, %d %b %Y %T %z", स_स्थानीय(&now));
			म_लिखो("%s\n", buf);
			जाओ out;
		पूर्ण
	पूर्ण
	म_लिखो("[OK]\n");
	करोne = 1;

out:
	/* रुको */
	क्रम (i = 0; i < thपढ़ो_count; i++)
		pthपढ़ो_join(pth[i], &tret);

	/* die */
	अगर (ret)
		ksft_निकास_fail();
	वापस ksft_निकास_pass();
पूर्ण
