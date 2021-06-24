<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * Basic test coverage क्रम critical regions and rseq_current_cpu().
 */

#घोषणा _GNU_SOURCE
#समावेश <निश्चित.स>
#समावेश <sched.h>
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <sys/समय.स>

#समावेश "rseq.h"

व्योम test_cpu_poपूर्णांकer(व्योम)
अणु
	cpu_set_t affinity, test_affinity;
	पूर्णांक i;

	sched_getaffinity(0, माप(affinity), &affinity);
	CPU_ZERO(&test_affinity);
	क्रम (i = 0; i < CPU_SETSIZE; i++) अणु
		अगर (CPU_ISSET(i, &affinity)) अणु
			CPU_SET(i, &test_affinity);
			sched_setaffinity(0, माप(test_affinity),
					&test_affinity);
			निश्चित(sched_अ_लोpu() == i);
			निश्चित(rseq_current_cpu() == i);
			निश्चित(rseq_current_cpu_raw() == i);
			निश्चित(rseq_cpu_start() == i);
			CPU_CLR(i, &test_affinity);
		पूर्ण
	पूर्ण
	sched_setaffinity(0, माप(affinity), &affinity);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	अगर (rseq_रेजिस्टर_current_thपढ़ो()) अणु
		ख_लिखो(मानक_त्रुटि, "Error: rseq_register_current_thread(...) failed(%d): %s\n",
			त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
		जाओ init_thपढ़ो_error;
	पूर्ण
	म_लिखो("testing current cpu\n");
	test_cpu_poपूर्णांकer();
	अगर (rseq_unरेजिस्टर_current_thपढ़ो()) अणु
		ख_लिखो(मानक_त्रुटि, "Error: rseq_unregister_current_thread(...) failed(%d): %s\n",
			त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
		जाओ init_thपढ़ो_error;
	पूर्ण
	वापस 0;

init_thपढ़ो_error:
	वापस -1;
पूर्ण
