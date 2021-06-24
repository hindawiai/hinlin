<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/compiler.h>
#समावेश <perf/cpumap.h>
#समावेश <माला.स>
#समावेश "cpumap.h"
#समावेश "evlist.h"
#समावेश "evsel.h"
#समावेश "header.h"
#समावेश "machine.h"
#समावेश "util/synthetic-events.h"
#समावेश "tool.h"
#समावेश "tests.h"
#समावेश "debug.h"

अटल पूर्णांक process_event_unit(काष्ठा perf_tool *tool __maybe_unused,
			      जोड़ perf_event *event,
			      काष्ठा perf_sample *sample __maybe_unused,
			      काष्ठा machine *machine __maybe_unused)
अणु
	काष्ठा perf_record_event_update *ev = (काष्ठा perf_record_event_update *)event;

	TEST_ASSERT_VAL("wrong id", ev->id == 123);
	TEST_ASSERT_VAL("wrong id", ev->type == PERF_EVENT_UPDATE__UNIT);
	TEST_ASSERT_VAL("wrong unit", !म_भेद(ev->data, "KRAVA"));
	वापस 0;
पूर्ण

अटल पूर्णांक process_event_scale(काष्ठा perf_tool *tool __maybe_unused,
			       जोड़ perf_event *event,
			       काष्ठा perf_sample *sample __maybe_unused,
			       काष्ठा machine *machine __maybe_unused)
अणु
	काष्ठा perf_record_event_update *ev = (काष्ठा perf_record_event_update *)event;
	काष्ठा perf_record_event_update_scale *ev_data;

	ev_data = (काष्ठा perf_record_event_update_scale *)ev->data;

	TEST_ASSERT_VAL("wrong id", ev->id == 123);
	TEST_ASSERT_VAL("wrong id", ev->type == PERF_EVENT_UPDATE__SCALE);
	TEST_ASSERT_VAL("wrong scale", ev_data->scale == 0.123);
	वापस 0;
पूर्ण

काष्ठा event_name अणु
	काष्ठा perf_tool tool;
	स्थिर अक्षर *name;
पूर्ण;

अटल पूर्णांक process_event_name(काष्ठा perf_tool *tool,
			      जोड़ perf_event *event,
			      काष्ठा perf_sample *sample __maybe_unused,
			      काष्ठा machine *machine __maybe_unused)
अणु
	काष्ठा event_name *पंचांगp = container_of(tool, काष्ठा event_name, tool);
	काष्ठा perf_record_event_update *ev = (काष्ठा perf_record_event_update *)event;

	TEST_ASSERT_VAL("wrong id", ev->id == 123);
	TEST_ASSERT_VAL("wrong id", ev->type == PERF_EVENT_UPDATE__NAME);
	TEST_ASSERT_VAL("wrong name", !म_भेद(ev->data, पंचांगp->name));
	वापस 0;
पूर्ण

अटल पूर्णांक process_event_cpus(काष्ठा perf_tool *tool __maybe_unused,
			      जोड़ perf_event *event,
			      काष्ठा perf_sample *sample __maybe_unused,
			      काष्ठा machine *machine __maybe_unused)
अणु
	काष्ठा perf_record_event_update *ev = (काष्ठा perf_record_event_update *)event;
	काष्ठा perf_record_event_update_cpus *ev_data;
	काष्ठा perf_cpu_map *map;

	ev_data = (काष्ठा perf_record_event_update_cpus *) ev->data;

	map = cpu_map__new_data(&ev_data->cpus);

	TEST_ASSERT_VAL("wrong id", ev->id == 123);
	TEST_ASSERT_VAL("wrong type", ev->type == PERF_EVENT_UPDATE__CPUS);
	TEST_ASSERT_VAL("wrong cpus", map->nr == 3);
	TEST_ASSERT_VAL("wrong cpus", map->map[0] == 1);
	TEST_ASSERT_VAL("wrong cpus", map->map[1] == 2);
	TEST_ASSERT_VAL("wrong cpus", map->map[2] == 3);
	perf_cpu_map__put(map);
	वापस 0;
पूर्ण

पूर्णांक test__event_update(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	काष्ठा evsel *evsel;
	काष्ठा event_name पंचांगp;
	काष्ठा evlist *evlist = evlist__new_शेष();

	TEST_ASSERT_VAL("failed to get evlist", evlist);

	evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("failed to allocate ids",
			!perf_evsel__alloc_id(&evsel->core, 1, 1));

	perf_evlist__id_add(&evlist->core, &evsel->core, 0, 0, 123);

	evsel->unit = strdup("KRAVA");

	TEST_ASSERT_VAL("failed to synthesize attr update unit",
			!perf_event__synthesize_event_update_unit(शून्य, evsel, process_event_unit));

	evsel->scale = 0.123;

	TEST_ASSERT_VAL("failed to synthesize attr update scale",
			!perf_event__synthesize_event_update_scale(शून्य, evsel, process_event_scale));

	पंचांगp.name = evsel__name(evsel);

	TEST_ASSERT_VAL("failed to synthesize attr update name",
			!perf_event__synthesize_event_update_name(&पंचांगp.tool, evsel, process_event_name));

	evsel->core.own_cpus = perf_cpu_map__new("1,2,3");

	TEST_ASSERT_VAL("failed to synthesize attr update cpus",
			!perf_event__synthesize_event_update_cpus(&पंचांगp.tool, evsel, process_event_cpus));

	perf_cpu_map__put(evsel->core.own_cpus);
	वापस 0;
पूर्ण
