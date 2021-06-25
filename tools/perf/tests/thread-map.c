<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/types.h>
#समावेश <unistd.h>
#समावेश <sys/prctl.h>
#समावेश "tests.h"
#समावेश "thread_map.h"
#समावेश "debug.h"
#समावेश "event.h"
#समावेश "util/synthetic-events.h"
#समावेश <linux/zभाग.स>
#समावेश <perf/event.h>

काष्ठा perf_sample;
काष्ठा perf_tool;
काष्ठा machine;

#घोषणा NAME	(स्थिर अक्षर *) "perf"
#घोषणा NAMEUL	(अचिन्हित दीर्घ) NAME

पूर्णांक test__thपढ़ो_map(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	काष्ठा perf_thपढ़ो_map *map;

	TEST_ASSERT_VAL("failed to set process name",
			!prctl(PR_SET_NAME, NAMEUL, 0, 0, 0));

	/* test map on current pid */
	map = thपढ़ो_map__new_by_pid(getpid());
	TEST_ASSERT_VAL("failed to alloc map", map);

	thपढ़ो_map__पढ़ो_comms(map);

	TEST_ASSERT_VAL("wrong nr", map->nr == 1);
	TEST_ASSERT_VAL("wrong pid",
			perf_thपढ़ो_map__pid(map, 0) == getpid());
	TEST_ASSERT_VAL("wrong comm",
			perf_thपढ़ो_map__comm(map, 0) &&
			!म_भेद(perf_thपढ़ो_map__comm(map, 0), NAME));
	TEST_ASSERT_VAL("wrong refcnt",
			refcount_पढ़ो(&map->refcnt) == 1);
	perf_thपढ़ो_map__put(map);

	/* test dummy pid */
	map = perf_thपढ़ो_map__new_dummy();
	TEST_ASSERT_VAL("failed to alloc map", map);

	thपढ़ो_map__पढ़ो_comms(map);

	TEST_ASSERT_VAL("wrong nr", map->nr == 1);
	TEST_ASSERT_VAL("wrong pid", perf_thपढ़ो_map__pid(map, 0) == -1);
	TEST_ASSERT_VAL("wrong comm",
			perf_thपढ़ो_map__comm(map, 0) &&
			!म_भेद(perf_thपढ़ो_map__comm(map, 0), "dummy"));
	TEST_ASSERT_VAL("wrong refcnt",
			refcount_पढ़ो(&map->refcnt) == 1);
	perf_thपढ़ो_map__put(map);
	वापस 0;
पूर्ण

अटल पूर्णांक process_event(काष्ठा perf_tool *tool __maybe_unused,
			 जोड़ perf_event *event,
			 काष्ठा perf_sample *sample __maybe_unused,
			 काष्ठा machine *machine __maybe_unused)
अणु
	काष्ठा perf_record_thपढ़ो_map *map = &event->thपढ़ो_map;
	काष्ठा perf_thपढ़ो_map *thपढ़ोs;

	TEST_ASSERT_VAL("wrong nr",   map->nr == 1);
	TEST_ASSERT_VAL("wrong pid",  map->entries[0].pid == (u64) getpid());
	TEST_ASSERT_VAL("wrong comm", !म_भेद(map->entries[0].comm, NAME));

	thपढ़ोs = thपढ़ो_map__new_event(&event->thपढ़ो_map);
	TEST_ASSERT_VAL("failed to alloc map", thपढ़ोs);

	TEST_ASSERT_VAL("wrong nr", thपढ़ोs->nr == 1);
	TEST_ASSERT_VAL("wrong pid",
			perf_thपढ़ो_map__pid(thपढ़ोs, 0) == getpid());
	TEST_ASSERT_VAL("wrong comm",
			perf_thपढ़ो_map__comm(thपढ़ोs, 0) &&
			!म_भेद(perf_thपढ़ो_map__comm(thपढ़ोs, 0), NAME));
	TEST_ASSERT_VAL("wrong refcnt",
			refcount_पढ़ो(&thपढ़ोs->refcnt) == 1);
	perf_thपढ़ो_map__put(thपढ़ोs);
	वापस 0;
पूर्ण

पूर्णांक test__thपढ़ो_map_synthesize(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	काष्ठा perf_thपढ़ो_map *thपढ़ोs;

	TEST_ASSERT_VAL("failed to set process name",
			!prctl(PR_SET_NAME, NAMEUL, 0, 0, 0));

	/* test map on current pid */
	thपढ़ोs = thपढ़ो_map__new_by_pid(getpid());
	TEST_ASSERT_VAL("failed to alloc map", thपढ़ोs);

	thपढ़ो_map__पढ़ो_comms(thपढ़ोs);

	TEST_ASSERT_VAL("failed to synthesize map",
		!perf_event__syntheमाप_प्रकारhपढ़ो_map2(शून्य, thपढ़ोs, process_event, शून्य));

	perf_thपढ़ो_map__put(thपढ़ोs);
	वापस 0;
पूर्ण

पूर्णांक test__thपढ़ो_map_हटाओ(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	काष्ठा perf_thपढ़ो_map *thपढ़ोs;
	अक्षर *str;

	TEST_ASSERT_VAL("failed to allocate map string",
			aप्र_लिखो(&str, "%d,%d", getpid(), getppid()) >= 0);

	thपढ़ोs = thपढ़ो_map__new_str(str, शून्य, 0, false);
	मुक्त(str);

	TEST_ASSERT_VAL("failed to allocate thread_map",
			thपढ़ोs);

	अगर (verbose > 0)
		thपढ़ो_map__ख_लिखो(thपढ़ोs, मानक_त्रुटि);

	TEST_ASSERT_VAL("failed to remove thread",
			!thपढ़ो_map__हटाओ(thपढ़ोs, 0));

	TEST_ASSERT_VAL("thread_map count != 1", thपढ़ोs->nr == 1);

	अगर (verbose > 0)
		thपढ़ो_map__ख_लिखो(thपढ़ोs, मानक_त्रुटि);

	TEST_ASSERT_VAL("failed to remove thread",
			!thपढ़ो_map__हटाओ(thपढ़ोs, 0));

	TEST_ASSERT_VAL("thread_map count != 0", thपढ़ोs->nr == 0);

	अगर (verbose > 0)
		thपढ़ो_map__ख_लिखो(thपढ़ोs, मानक_त्रुटि);

	TEST_ASSERT_VAL("failed to not remove thread",
			thपढ़ो_map__हटाओ(thपढ़ोs, 0));

	perf_thपढ़ो_map__put(thपढ़ोs);
	वापस 0;
पूर्ण
