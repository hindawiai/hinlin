<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "tests.h"
#समावेश <मानकपन.स>
#समावेश "cpumap.h"
#समावेश "event.h"
#समावेश "util/synthetic-events.h"
#समावेश <माला.स>
#समावेश <linux/bitops.h>
#समावेश <perf/cpumap.h>
#समावेश "debug.h"

काष्ठा machine;

अटल पूर्णांक process_event_mask(काष्ठा perf_tool *tool __maybe_unused,
			 जोड़ perf_event *event,
			 काष्ठा perf_sample *sample __maybe_unused,
			 काष्ठा machine *machine __maybe_unused)
अणु
	काष्ठा perf_record_cpu_map *map_event = &event->cpu_map;
	काष्ठा perf_record_record_cpu_map *mask;
	काष्ठा perf_record_cpu_map_data *data;
	काष्ठा perf_cpu_map *map;
	पूर्णांक i;

	data = &map_event->data;

	TEST_ASSERT_VAL("wrong type", data->type == PERF_CPU_MAP__MASK);

	mask = (काष्ठा perf_record_record_cpu_map *)data->data;

	TEST_ASSERT_VAL("wrong nr",   mask->nr == 1);

	क्रम (i = 0; i < 20; i++) अणु
		TEST_ASSERT_VAL("wrong cpu", test_bit(i, mask->mask));
	पूर्ण

	map = cpu_map__new_data(data);
	TEST_ASSERT_VAL("wrong nr",  map->nr == 20);

	क्रम (i = 0; i < 20; i++) अणु
		TEST_ASSERT_VAL("wrong cpu", map->map[i] == i);
	पूर्ण

	perf_cpu_map__put(map);
	वापस 0;
पूर्ण

अटल पूर्णांक process_event_cpus(काष्ठा perf_tool *tool __maybe_unused,
			 जोड़ perf_event *event,
			 काष्ठा perf_sample *sample __maybe_unused,
			 काष्ठा machine *machine __maybe_unused)
अणु
	काष्ठा perf_record_cpu_map *map_event = &event->cpu_map;
	काष्ठा cpu_map_entries *cpus;
	काष्ठा perf_record_cpu_map_data *data;
	काष्ठा perf_cpu_map *map;

	data = &map_event->data;

	TEST_ASSERT_VAL("wrong type", data->type == PERF_CPU_MAP__CPUS);

	cpus = (काष्ठा cpu_map_entries *)data->data;

	TEST_ASSERT_VAL("wrong nr",   cpus->nr == 2);
	TEST_ASSERT_VAL("wrong cpu",  cpus->cpu[0] == 1);
	TEST_ASSERT_VAL("wrong cpu",  cpus->cpu[1] == 256);

	map = cpu_map__new_data(data);
	TEST_ASSERT_VAL("wrong nr",  map->nr == 2);
	TEST_ASSERT_VAL("wrong cpu", map->map[0] == 1);
	TEST_ASSERT_VAL("wrong cpu", map->map[1] == 256);
	TEST_ASSERT_VAL("wrong refcnt", refcount_पढ़ो(&map->refcnt) == 1);
	perf_cpu_map__put(map);
	वापस 0;
पूर्ण


पूर्णांक test__cpu_map_synthesize(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	काष्ठा perf_cpu_map *cpus;

	/* This one is better stores in mask. */
	cpus = perf_cpu_map__new("0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19");

	TEST_ASSERT_VAL("failed to synthesize map",
		!perf_event__synthesize_cpu_map(शून्य, cpus, process_event_mask, शून्य));

	perf_cpu_map__put(cpus);

	/* This one is better stores in cpu values. */
	cpus = perf_cpu_map__new("1,256");

	TEST_ASSERT_VAL("failed to synthesize map",
		!perf_event__synthesize_cpu_map(शून्य, cpus, process_event_cpus, शून्य));

	perf_cpu_map__put(cpus);
	वापस 0;
पूर्ण

अटल पूर्णांक cpu_map_prपूर्णांक(स्थिर अक्षर *str)
अणु
	काष्ठा perf_cpu_map *map = perf_cpu_map__new(str);
	अक्षर buf[100];

	अगर (!map)
		वापस -1;

	cpu_map__snprपूर्णांक(map, buf, माप(buf));
	perf_cpu_map__put(map);

	वापस !म_भेद(buf, str);
पूर्ण

पूर्णांक test__cpu_map_prपूर्णांक(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	TEST_ASSERT_VAL("failed to convert map", cpu_map_prपूर्णांक("1"));
	TEST_ASSERT_VAL("failed to convert map", cpu_map_prपूर्णांक("1,5"));
	TEST_ASSERT_VAL("failed to convert map", cpu_map_prपूर्णांक("1,3,5,7,9,11,13,15,17,19,21-40"));
	TEST_ASSERT_VAL("failed to convert map", cpu_map_prपूर्णांक("2-5"));
	TEST_ASSERT_VAL("failed to convert map", cpu_map_prपूर्णांक("1,3-6,8-10,24,35-37"));
	TEST_ASSERT_VAL("failed to convert map", cpu_map_prपूर्णांक("1,3-6,8-10,24,35-37"));
	TEST_ASSERT_VAL("failed to convert map", cpu_map_prपूर्णांक("1-10,12-20,22-30,32-40"));
	वापस 0;
पूर्ण

पूर्णांक test__cpu_map_merge(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	काष्ठा perf_cpu_map *a = perf_cpu_map__new("4,2,1");
	काष्ठा perf_cpu_map *b = perf_cpu_map__new("4,5,7");
	काष्ठा perf_cpu_map *c = perf_cpu_map__merge(a, b);
	अक्षर buf[100];

	TEST_ASSERT_VAL("failed to merge map: bad nr", c->nr == 5);
	cpu_map__snprपूर्णांक(c, buf, माप(buf));
	TEST_ASSERT_VAL("failed to merge map: bad result", !म_भेद(buf, "1-2,4-5,7"));
	perf_cpu_map__put(b);
	perf_cpu_map__put(c);
	वापस 0;
पूर्ण
