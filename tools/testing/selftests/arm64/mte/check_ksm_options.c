<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2020 ARM Limited

#घोषणा _GNU_SOURCE

#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <ucontext.h>
#समावेश <sys/mman.h>

#समावेश "kselftest.h"
#समावेश "mte_common_util.h"
#समावेश "mte_def.h"

#घोषणा TEST_UNIT	10
#घोषणा PATH_KSM	"/sys/kernel/mm/ksm/"
#घोषणा MAX_LOOP	4

अटल माप_प्रकार page_sz;
अटल अचिन्हित दीर्घ ksm_sysfs[5];

अटल अचिन्हित दीर्घ पढ़ो_sysfs(अक्षर *str)
अणु
	खाता *f;
	अचिन्हित दीर्घ val = 0;

	f = ख_खोलो(str, "r");
	अगर (!f) अणु
		ksft_prपूर्णांक_msg("ERR: missing %s\n", str);
		वापस 0;
	पूर्ण
	अगर (ख_पूछो(f, "%lu", &val) != 1) अणु
		ksft_prपूर्णांक_msg("ERR: parsing %s\n", str);
		val = 0;
	पूर्ण
	ख_बंद(f);
	वापस val;
पूर्ण

अटल व्योम ग_लिखो_sysfs(अक्षर *str, अचिन्हित दीर्घ val)
अणु
	खाता *f;

	f = ख_खोलो(str, "w");
	अगर (!f) अणु
		ksft_prपूर्णांक_msg("ERR: missing %s\n", str);
		वापस;
	पूर्ण
	ख_लिखो(f, "%lu", val);
	ख_बंद(f);
पूर्ण

अटल व्योम mte_ksm_setup(व्योम)
अणु
	ksm_sysfs[0] = पढ़ो_sysfs(PATH_KSM "merge_across_nodes");
	ग_लिखो_sysfs(PATH_KSM "merge_across_nodes", 1);
	ksm_sysfs[1] = पढ़ो_sysfs(PATH_KSM "sleep_millisecs");
	ग_लिखो_sysfs(PATH_KSM "sleep_millisecs", 0);
	ksm_sysfs[2] = पढ़ो_sysfs(PATH_KSM "run");
	ग_लिखो_sysfs(PATH_KSM "run", 1);
	ksm_sysfs[3] = पढ़ो_sysfs(PATH_KSM "max_page_sharing");
	ग_लिखो_sysfs(PATH_KSM "max_page_sharing", ksm_sysfs[3] + TEST_UNIT);
	ksm_sysfs[4] = पढ़ो_sysfs(PATH_KSM "pages_to_scan");
	ग_लिखो_sysfs(PATH_KSM "pages_to_scan", ksm_sysfs[4] + TEST_UNIT);
पूर्ण

अटल व्योम mte_ksm_restore(व्योम)
अणु
	ग_लिखो_sysfs(PATH_KSM "merge_across_nodes", ksm_sysfs[0]);
	ग_लिखो_sysfs(PATH_KSM "sleep_millisecs", ksm_sysfs[1]);
	ग_लिखो_sysfs(PATH_KSM "run", ksm_sysfs[2]);
	ग_लिखो_sysfs(PATH_KSM "max_page_sharing", ksm_sysfs[3]);
	ग_लिखो_sysfs(PATH_KSM "pages_to_scan", ksm_sysfs[4]);
पूर्ण

अटल व्योम mte_ksm_scan(व्योम)
अणु
	पूर्णांक cur_count = पढ़ो_sysfs(PATH_KSM "full_scans");
	पूर्णांक scan_count = cur_count + 1;
	पूर्णांक max_loop_count = MAX_LOOP;

	जबतक ((cur_count < scan_count) && max_loop_count) अणु
		sleep(1);
		cur_count = पढ़ो_sysfs(PATH_KSM "full_scans");
		max_loop_count--;
	पूर्ण
#अगर_घोषित DEBUG
	ksft_prपूर्णांक_msg("INFO: pages_shared=%lu pages_sharing=%lu\n",
			पढ़ो_sysfs(PATH_KSM "pages_shared"),
			पढ़ो_sysfs(PATH_KSM "pages_sharing"));
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक check_madvise_options(पूर्णांक mem_type, पूर्णांक mode, पूर्णांक mapping)
अणु
	अक्षर *ptr;
	पूर्णांक err, ret;

	err = KSFT_FAIL;
	अगर (access(PATH_KSM, F_OK) == -1) अणु
		ksft_prपूर्णांक_msg("ERR: Kernel KSM config not enabled\n");
		वापस err;
	पूर्ण

	mte_चयन_mode(mode, MTE_ALLOW_NON_ZERO_TAG);
	ptr = mte_allocate_memory(TEST_UNIT * page_sz, mem_type, mapping, true);
	अगर (check_allocated_memory(ptr, TEST_UNIT * page_sz, mem_type, false) != KSFT_PASS)
		वापस KSFT_FAIL;

	/* Insert same data in all the pages */
	स_रखो(ptr, 'A', TEST_UNIT * page_sz);
	ret = madvise(ptr, TEST_UNIT * page_sz, MADV_MERGEABLE);
	अगर (ret) अणु
		ksft_prपूर्णांक_msg("ERR: madvise failed to set MADV_UNMERGEABLE\n");
		जाओ madvise_err;
	पूर्ण
	mte_ksm_scan();
	/* Tagged pages should not merge */
	अगर ((पढ़ो_sysfs(PATH_KSM "pages_shared") < 1) ||
	    (पढ़ो_sysfs(PATH_KSM "pages_sharing") < (TEST_UNIT - 1)))
		err = KSFT_PASS;
madvise_err:
	mte_मुक्त_memory(ptr, TEST_UNIT * page_sz, mem_type, true);
	वापस err;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक err;

	err = mte_शेष_setup();
	अगर (err)
		वापस err;
	page_sz = getpagesize();
	अगर (!page_sz) अणु
		ksft_prपूर्णांक_msg("ERR: Unable to get page size\n");
		वापस KSFT_FAIL;
	पूर्ण
	/* Register संकेत handlers */
	mte_रेजिस्टर_संकेत(SIGBUS, mte_शेष_handler);
	mte_रेजिस्टर_संकेत(संक_अंश, mte_शेष_handler);

	/* Set test plan */
	ksft_set_plan(4);

	/* Enable KSM */
	mte_ksm_setup();

	evaluate_test(check_madvise_options(USE_MMAP, MTE_SYNC_ERR, MAP_PRIVATE),
		"Check KSM mte page merge for private mapping, sync mode and mmap memory\n");
	evaluate_test(check_madvise_options(USE_MMAP, MTE_ASYNC_ERR, MAP_PRIVATE),
		"Check KSM mte page merge for private mapping, async mode and mmap memory\n");
	evaluate_test(check_madvise_options(USE_MMAP, MTE_SYNC_ERR, MAP_SHARED),
		"Check KSM mte page merge for shared mapping, sync mode and mmap memory\n");
	evaluate_test(check_madvise_options(USE_MMAP, MTE_ASYNC_ERR, MAP_SHARED),
		"Check KSM mte page merge for shared mapping, async mode and mmap memory\n");

	mte_ksm_restore();
	mte_restore_setup();
	ksft_prपूर्णांक_cnts();
	वापस ksft_get_fail_cnt() == 0 ? KSFT_PASS : KSFT_FAIL;
पूर्ण
