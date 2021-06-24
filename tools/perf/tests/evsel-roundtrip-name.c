<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "evlist.h"
#समावेश "evsel.h"
#समावेश "parse-events.h"
#समावेश "tests.h"
#समावेश "debug.h"
#समावेश "pmu.h"
#समावेश <त्रुटिसं.स>
#समावेश <linux/kernel.h>

अटल पूर्णांक perf_evsel__roundtrip_cache_name_test(व्योम)
अणु
	अक्षर name[128];
	पूर्णांक type, op, err = 0, ret = 0, i, idx;
	काष्ठा evsel *evsel;
	काष्ठा evlist *evlist = evlist__new();

        अगर (evlist == शून्य)
                वापस -ENOMEM;

	क्रम (type = 0; type < PERF_COUNT_HW_CACHE_MAX; type++) अणु
		क्रम (op = 0; op < PERF_COUNT_HW_CACHE_OP_MAX; op++) अणु
			/* skip invalid cache type */
			अगर (!evsel__is_cache_op_valid(type, op))
				जारी;

			क्रम (i = 0; i < PERF_COUNT_HW_CACHE_RESULT_MAX; i++) अणु
				__evsel__hw_cache_type_op_res_name(type, op, i, name, माप(name));
				err = parse_events(evlist, name, शून्य);
				अगर (err)
					ret = err;
			पूर्ण
		पूर्ण
	पूर्ण

	idx = 0;
	evsel = evlist__first(evlist);

	क्रम (type = 0; type < PERF_COUNT_HW_CACHE_MAX; type++) अणु
		क्रम (op = 0; op < PERF_COUNT_HW_CACHE_OP_MAX; op++) अणु
			/* skip invalid cache type */
			अगर (!evsel__is_cache_op_valid(type, op))
				जारी;

			क्रम (i = 0; i < PERF_COUNT_HW_CACHE_RESULT_MAX; i++) अणु
				__evsel__hw_cache_type_op_res_name(type, op, i, name, माप(name));
				अगर (evsel->idx != idx)
					जारी;

				++idx;

				अगर (म_भेद(evsel__name(evsel), name)) अणु
					pr_debug("%s != %s\n", evsel__name(evsel), name);
					ret = -1;
				पूर्ण

				evsel = evsel__next(evsel);
			पूर्ण
		पूर्ण
	पूर्ण

	evlist__delete(evlist);
	वापस ret;
पूर्ण

अटल पूर्णांक __perf_evsel__name_array_test(स्थिर अक्षर *names[], पूर्णांक nr_names,
					 पूर्णांक distance)
अणु
	पूर्णांक i, err;
	काष्ठा evsel *evsel;
	काष्ठा evlist *evlist = evlist__new();

        अगर (evlist == शून्य)
                वापस -ENOMEM;

	क्रम (i = 0; i < nr_names; ++i) अणु
		err = parse_events(evlist, names[i], शून्य);
		अगर (err) अणु
			pr_debug("failed to parse event '%s', err %d\n",
				 names[i], err);
			जाओ out_delete_evlist;
		पूर्ण
	पूर्ण

	err = 0;
	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (म_भेद(evsel__name(evsel), names[evsel->idx / distance])) अणु
			--err;
			pr_debug("%s != %s\n", evsel__name(evsel), names[evsel->idx / distance]);
		पूर्ण
	पूर्ण

out_delete_evlist:
	evlist__delete(evlist);
	वापस err;
पूर्ण

#घोषणा perf_evsel__name_array_test(names, distance) \
	__perf_evsel__name_array_test(names, ARRAY_SIZE(names), distance)

पूर्णांक test__perf_evsel__roundtrip_name_test(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	पूर्णांक err = 0, ret = 0;

	अगर (perf_pmu__has_hybrid())
		वापस perf_evsel__name_array_test(evsel__hw_names, 2);

	err = perf_evsel__name_array_test(evsel__hw_names, 1);
	अगर (err)
		ret = err;

	err = __perf_evsel__name_array_test(evsel__sw_names, PERF_COUNT_SW_DUMMY + 1, 1);
	अगर (err)
		ret = err;

	err = perf_evsel__roundtrip_cache_name_test();
	अगर (err)
		ret = err;

	वापस ret;
पूर्ण
