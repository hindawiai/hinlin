<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * POWER Data Stream Control Register (DSCR) sysfs thपढ़ो test
 *
 * This test updates the प्रणाली wide DSCR शेष value through
 * sysfs पूर्णांकerface which should then update all the CPU specअगरic
 * DSCR शेष values which must also be then visible to thपढ़ोs
 * executing on inभागidual CPUs on the प्रणाली.
 *
 * Copyright 2015, Anshuman Khandual, IBM Corporation.
 */
#घोषणा _GNU_SOURCE
#समावेश "dscr.h"

अटल पूर्णांक test_thपढ़ो_dscr(अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ cur_dscr, cur_dscr_usr;

	cur_dscr = get_dscr();
	cur_dscr_usr = get_dscr_usr();

	अगर (val != cur_dscr) अणु
		म_लिखो("[cpu %d] Kernel DSCR should be %ld but is %ld\n",
					sched_अ_लोpu(), val, cur_dscr);
		वापस 1;
	पूर्ण

	अगर (val != cur_dscr_usr) अणु
		म_लिखो("[cpu %d] User DSCR should be %ld but is %ld\n",
					sched_अ_लोpu(), val, cur_dscr_usr);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक check_cpu_dscr_thपढ़ो(अचिन्हित दीर्घ val)
अणु
	cpu_set_t mask;
	पूर्णांक cpu;

	क्रम (cpu = 0; cpu < CPU_SETSIZE; cpu++) अणु
		CPU_ZERO(&mask);
		CPU_SET(cpu, &mask);
		अगर (sched_setaffinity(0, माप(mask), &mask))
			जारी;

		अगर (test_thपढ़ो_dscr(val))
			वापस 1;
	पूर्ण
	वापस 0;

पूर्ण

पूर्णांक dscr_sysfs_thपढ़ो(व्योम)
अणु
	अचिन्हित दीर्घ orig_dscr_शेष;
	पूर्णांक i, j;

	SKIP_IF(!have_hwcap2(PPC_FEATURE2_DSCR));

	orig_dscr_शेष = get_शेष_dscr();
	क्रम (i = 0; i < COUNT; i++) अणु
		क्रम (j = 0; j < DSCR_MAX; j++) अणु
			set_शेष_dscr(j);
			अगर (check_cpu_dscr_thपढ़ो(j))
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
	वापस test_harness(dscr_sysfs_thपढ़ो, "dscr_sysfs_thread_test");
पूर्ण
