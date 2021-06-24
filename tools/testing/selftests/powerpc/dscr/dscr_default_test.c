<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * POWER Data Stream Control Register (DSCR) शेष test
 *
 * This test modअगरies the प्रणाली wide शेष DSCR through
 * it's sysfs पूर्णांकerface and then verअगरies that all thपढ़ोs
 * see the correct changed DSCR value immediately.
 *
 * Copyright 2012, Anton Blanअक्षरd, IBM Corporation.
 * Copyright 2015, Anshuman Khandual, IBM Corporation.
 */
#समावेश "dscr.h"

अटल अचिन्हित दीर्घ dscr;		/* System DSCR शेष */
अटल अचिन्हित दीर्घ sequence;
अटल अचिन्हित दीर्घ result[THREADS];

अटल व्योम *करो_test(व्योम *in)
अणु
	अचिन्हित दीर्घ thपढ़ो = (अचिन्हित दीर्घ)in;
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < COUNT; i++) अणु
		अचिन्हित दीर्घ d, cur_dscr, cur_dscr_usr;
		अचिन्हित दीर्घ s1, s2;

		s1 = READ_ONCE(sequence);
		अगर (s1 & 1)
			जारी;
		rmb();

		d = dscr;
		cur_dscr = get_dscr();
		cur_dscr_usr = get_dscr_usr();

		rmb();
		s2 = sequence;

		अगर (s1 != s2)
			जारी;

		अगर (cur_dscr != d) अणु
			ख_लिखो(मानक_त्रुटि, "thread %ld kernel DSCR should be %ld "
				"but is %ld\n", thपढ़ो, d, cur_dscr);
			result[thपढ़ो] = 1;
			pthपढ़ो_निकास(&result[thपढ़ो]);
		पूर्ण

		अगर (cur_dscr_usr != d) अणु
			ख_लिखो(मानक_त्रुटि, "thread %ld user DSCR should be %ld "
				"but is %ld\n", thपढ़ो, d, cur_dscr_usr);
			result[thपढ़ो] = 1;
			pthपढ़ो_निकास(&result[thपढ़ो]);
		पूर्ण
	पूर्ण
	result[thपढ़ो] = 0;
	pthपढ़ो_निकास(&result[thपढ़ो]);
पूर्ण

पूर्णांक dscr_शेष(व्योम)
अणु
	pthपढ़ो_t thपढ़ोs[THREADS];
	अचिन्हित दीर्घ i, *status[THREADS];
	अचिन्हित दीर्घ orig_dscr_शेष;

	SKIP_IF(!have_hwcap2(PPC_FEATURE2_DSCR));

	orig_dscr_शेष = get_शेष_dscr();

	/* Initial DSCR शेष */
	dscr = 1;
	set_शेष_dscr(dscr);

	/* Spawn all testing thपढ़ोs */
	क्रम (i = 0; i < THREADS; i++) अणु
		अगर (pthपढ़ो_create(&thपढ़ोs[i], शून्य, करो_test, (व्योम *)i)) अणु
			लिखो_त्रुटि("pthread_create() failed");
			जाओ fail;
		पूर्ण
	पूर्ण

	बेक्रम(getpid());

	/* Keep changing the DSCR शेष */
	क्रम (i = 0; i < COUNT; i++) अणु
		द्विगुन ret = unअगरorm_deviate(अक्रम());

		अगर (ret < 0.0001) अणु
			sequence++;
			wmb();

			dscr++;
			अगर (dscr > DSCR_MAX)
				dscr = 0;

			set_शेष_dscr(dscr);

			wmb();
			sequence++;
		पूर्ण
	पूर्ण

	/* Inभागidual testing thपढ़ो निकास status */
	क्रम (i = 0; i < THREADS; i++) अणु
		अगर (pthपढ़ो_join(thपढ़ोs[i], (व्योम **)&(status[i]))) अणु
			लिखो_त्रुटि("pthread_join() failed");
			जाओ fail;
		पूर्ण

		अगर (*status[i]) अणु
			म_लिखो("%ldth thread failed to join with %ld status\n",
								i, *status[i]);
			जाओ fail;
		पूर्ण
	पूर्ण
	set_शेष_dscr(orig_dscr_शेष);
	वापस 0;
fail:
	set_शेष_dscr(orig_dscr_शेष);
	वापस 1;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	वापस test_harness(dscr_शेष, "dscr_default_test");
पूर्ण
