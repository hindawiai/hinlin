<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <kunit/test.h>
#समावेश <linux/glob.h>
#समावेश <linux/moduleparam.h>

/*
 * These symbols poपूर्णांक to the .kunit_test_suites section and are defined in
 * include/यंत्र-generic/vmlinux.lds.h, and consequently must be बाह्य.
 */
बाह्य काष्ठा kunit_suite * स्थिर * स्थिर __kunit_suites_start[];
बाह्य काष्ठा kunit_suite * स्थिर * स्थिर __kunit_suites_end[];

#अगर IS_BUILTIN(CONFIG_KUNIT)

अटल अक्षर *filter_glob;
module_param(filter_glob, अक्षरp, 0);
MODULE_PARM_DESC(filter_glob,
		"Filter which KUnit test suites run at boot-time, e.g. list*");

अटल काष्ठा kunit_suite * स्थिर *
kunit_filter_subsuite(काष्ठा kunit_suite * स्थिर * स्थिर subsuite)
अणु
	पूर्णांक i, n = 0;
	काष्ठा kunit_suite **filtered;

	n = 0;
	क्रम (i = 0; subsuite[i] != शून्य; ++i) अणु
		अगर (glob_match(filter_glob, subsuite[i]->name))
			++n;
	पूर्ण

	अगर (n == 0)
		वापस शून्य;

	filtered = kदो_स्मृति_array(n + 1, माप(*filtered), GFP_KERNEL);
	अगर (!filtered)
		वापस शून्य;

	n = 0;
	क्रम (i = 0; subsuite[i] != शून्य; ++i) अणु
		अगर (glob_match(filter_glob, subsuite[i]->name))
			filtered[n++] = subsuite[i];
	पूर्ण
	filtered[n] = शून्य;

	वापस filtered;
पूर्ण

काष्ठा suite_set अणु
	काष्ठा kunit_suite * स्थिर * स्थिर *start;
	काष्ठा kunit_suite * स्थिर * स्थिर *end;
पूर्ण;

अटल काष्ठा suite_set kunit_filter_suites(व्योम)
अणु
	पूर्णांक i;
	काष्ठा kunit_suite * स्थिर **copy, * स्थिर *filtered_subsuite;
	काष्ठा suite_set filtered;

	स्थिर माप_प्रकार max = __kunit_suites_end - __kunit_suites_start;

	अगर (!filter_glob) अणु
		filtered.start = __kunit_suites_start;
		filtered.end = __kunit_suites_end;
		वापस filtered;
	पूर्ण

	copy = kदो_स्मृति_array(max, माप(*filtered.start), GFP_KERNEL);
	filtered.start = copy;
	अगर (!copy) अणु /* won't be able to run anything, वापस an empty set */
		filtered.end = copy;
		वापस filtered;
	पूर्ण

	क्रम (i = 0; i < max; ++i) अणु
		filtered_subsuite = kunit_filter_subsuite(__kunit_suites_start[i]);
		अगर (filtered_subsuite)
			*copy++ = filtered_subsuite;
	पूर्ण
	filtered.end = copy;
	वापस filtered;
पूर्ण

अटल व्योम kunit_prपूर्णांक_tap_header(काष्ठा suite_set *suite_set)
अणु
	काष्ठा kunit_suite * स्थिर * स्थिर *suites, * स्थिर *subsuite;
	पूर्णांक num_of_suites = 0;

	क्रम (suites = suite_set->start; suites < suite_set->end; suites++)
		क्रम (subsuite = *suites; *subsuite != शून्य; subsuite++)
			num_of_suites++;

	pr_info("TAP version 14\n");
	pr_info("1..%d\n", num_of_suites);
पूर्ण

पूर्णांक kunit_run_all_tests(व्योम)
अणु
	काष्ठा kunit_suite * स्थिर * स्थिर *suites;

	काष्ठा suite_set suite_set = kunit_filter_suites();

	kunit_prपूर्णांक_tap_header(&suite_set);

	क्रम (suites = suite_set.start; suites < suite_set.end; suites++)
		__kunit_test_suites_init(*suites);

	अगर (filter_glob) अणु /* a copy was made of each array */
		क्रम (suites = suite_set.start; suites < suite_set.end; suites++)
			kमुक्त(*suites);
		kमुक्त(suite_set.start);
	पूर्ण

	वापस 0;
पूर्ण

#पूर्ण_अगर /* IS_BUILTIN(CONFIG_KUNIT) */
