<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015 Anton Ivanov (aivanov@अणुbrocade.com,kot-begemot.co.ukपूर्ण)
 * Copyright (C) 2015 Thomas Meyer (thomas@m3y3r.de)
 * Copyright (C) 2012-2014 Cisco Systems
 * Copyright (C) 2000 - 2007 Jeff Dike (jdikeअणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <मानकघोष.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <संकेत.स>
#समावेश <समय.स>
#समावेश <sys/समय.स>
#समावेश <kern_util.h>
#समावेश <os.h>
#समावेश <माला.स>

अटल समयr_t event_high_res_समयr = 0;

अटल अंतरभूत दीर्घ दीर्घ समयval_to_ns(स्थिर काष्ठा समयval *tv)
अणु
	वापस ((दीर्घ दीर्घ) tv->tv_sec * UM_NSEC_PER_SEC) +
		tv->tv_usec * UM_NSEC_PER_USEC;
पूर्ण

अटल अंतरभूत दीर्घ दीर्घ बारpec_to_ns(स्थिर काष्ठा बारpec *ts)
अणु
	वापस ((दीर्घ दीर्घ) ts->tv_sec * UM_NSEC_PER_SEC) + ts->tv_nsec;
पूर्ण

दीर्घ दीर्घ os_persistent_घड़ी_emulation(व्योम)
अणु
	काष्ठा बारpec realसमय_प्रकारp;

	घड़ी_समय_लो(CLOCK_REALTIME, &realसमय_प्रकारp);
	वापस बारpec_to_ns(&realसमय_प्रकारp);
पूर्ण

/**
 * os_समयr_create() - create an new posix (पूर्णांकerval) समयr
 */
पूर्णांक os_समयr_create(व्योम)
अणु
	समयr_t *t = &event_high_res_समयr;

	अगर (समयr_create(CLOCK_MONOTONIC, शून्य, t) == -1)
		वापस -1;

	वापस 0;
पूर्ण

पूर्णांक os_समयr_set_पूर्णांकerval(अचिन्हित दीर्घ दीर्घ nsecs)
अणु
	काष्ठा iसमयrspec its;

	its.it_value.tv_sec = nsecs / UM_NSEC_PER_SEC;
	its.it_value.tv_nsec = nsecs % UM_NSEC_PER_SEC;

	its.it_पूर्णांकerval.tv_sec = nsecs / UM_NSEC_PER_SEC;
	its.it_पूर्णांकerval.tv_nsec = nsecs % UM_NSEC_PER_SEC;

	अगर (समयr_समय_रखो(event_high_res_समयr, 0, &its, शून्य) == -1)
		वापस -त्रुटि_सं;

	वापस 0;
पूर्ण

पूर्णांक os_समयr_one_shot(अचिन्हित दीर्घ दीर्घ nsecs)
अणु
	काष्ठा iसमयrspec its = अणु
		.it_value.tv_sec = nsecs / UM_NSEC_PER_SEC,
		.it_value.tv_nsec = nsecs % UM_NSEC_PER_SEC,

		.it_पूर्णांकerval.tv_sec = 0,
		.it_पूर्णांकerval.tv_nsec = 0, // we cheat here
	पूर्ण;

	समयr_समय_रखो(event_high_res_समयr, 0, &its, शून्य);
	वापस 0;
पूर्ण

/**
 * os_समयr_disable() - disable the posix (पूर्णांकerval) समयr
 */
व्योम os_समयr_disable(व्योम)
अणु
	काष्ठा iसमयrspec its;

	स_रखो(&its, 0, माप(काष्ठा iसमयrspec));
	समयr_समय_रखो(event_high_res_समयr, 0, &its, शून्य);
पूर्ण

दीर्घ दीर्घ os_nsecs(व्योम)
अणु
	काष्ठा बारpec ts;

	घड़ी_समय_लो(CLOCK_MONOTONIC,&ts);
	वापस बारpec_to_ns(&ts);
पूर्ण

/**
 * os_idle_sleep() - sleep until पूर्णांकerrupted
 */
व्योम os_idle_sleep(व्योम)
अणु
	काष्ठा iसमयrspec its;
	sigset_t set, old;

	/* block SIGALRM जबतक we analyze the समयr state */
	sigemptyset(&set);
	sigaddset(&set, SIGALRM);
	sigprocmask(SIG_BLOCK, &set, &old);

	/* check the समयr, and अगर it'll fire then रुको क्रम it */
	समयr_समय_लो(event_high_res_समयr, &its);
	अगर (its.it_value.tv_sec || its.it_value.tv_nsec)
		संक_रोको(&old);
	/* either way, restore the संकेत mask */
	sigprocmask(SIG_UNBLOCK, &set, शून्य);
पूर्ण
