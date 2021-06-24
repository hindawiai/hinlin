<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Test support क्रम libpfm4 event encodings.
 *
 * Copyright 2020 Google LLC.
 */
#समावेश "tests.h"
#समावेश "util/debug.h"
#समावेश "util/evlist.h"
#समावेश "util/pfm.h"

#समावेश <linux/kernel.h>

#अगर_घोषित HAVE_LIBPFM
अटल पूर्णांक test__pfm_events(व्योम);
अटल पूर्णांक test__pfm_group(व्योम);
#पूर्ण_अगर

अटल स्थिर काष्ठा अणु
	पूर्णांक (*func)(व्योम);
	स्थिर अक्षर *desc;
पूर्ण pfm_testहाल_table[] = अणु
#अगर_घोषित HAVE_LIBPFM
	अणु
		.func = test__pfm_events,
		.desc = "test of individual --pfm-events",
	पूर्ण,
	अणु
		.func = test__pfm_group,
		.desc = "test groups of --pfm-events",
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित HAVE_LIBPFM
अटल पूर्णांक count_pfm_events(काष्ठा perf_evlist *evlist)
अणु
	काष्ठा perf_evsel *evsel;
	पूर्णांक count = 0;

	perf_evlist__क्रम_each_entry(evlist, evsel) अणु
		count++;
	पूर्ण
	वापस count;
पूर्ण

अटल पूर्णांक test__pfm_events(व्योम)
अणु
	काष्ठा evlist *evlist;
	काष्ठा option opt;
	माप_प्रकार i;
	स्थिर काष्ठा अणु
		स्थिर अक्षर *events;
		पूर्णांक nr_events;
	पूर्ण table[] = अणु
		अणु
			.events = "",
			.nr_events = 0,
		पूर्ण,
		अणु
			.events = "instructions",
			.nr_events = 1,
		पूर्ण,
		अणु
			.events = "instructions,cycles",
			.nr_events = 2,
		पूर्ण,
		अणु
			.events = "stereolab",
			.nr_events = 0,
		पूर्ण,
		अणु
			.events = "instructions,instructions",
			.nr_events = 2,
		पूर्ण,
		अणु
			.events = "stereolab,instructions",
			.nr_events = 0,
		पूर्ण,
		अणु
			.events = "instructions,stereolab",
			.nr_events = 1,
		पूर्ण,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(table); i++) अणु
		evlist = evlist__new();
		अगर (evlist == शून्य)
			वापस -ENOMEM;

		opt.value = evlist;
		parse_libpfm_events_option(&opt,
					table[i].events,
					0);
		TEST_ASSERT_EQUAL(table[i].events,
				count_pfm_events(&evlist->core),
				table[i].nr_events);
		TEST_ASSERT_EQUAL(table[i].events,
				evlist->nr_groups,
				0);

		evlist__delete(evlist);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक test__pfm_group(व्योम)
अणु
	काष्ठा evlist *evlist;
	काष्ठा option opt;
	माप_प्रकार i;
	स्थिर काष्ठा अणु
		स्थिर अक्षर *events;
		पूर्णांक nr_events;
		पूर्णांक nr_groups;
	पूर्ण table[] = अणु
		अणु
			.events = "{},",
			.nr_events = 0,
			.nr_groups = 0,
		पूर्ण,
		अणु
			.events = "{instructions}",
			.nr_events = 1,
			.nr_groups = 1,
		पूर्ण,
		अणु
			.events = "{instructions},{}",
			.nr_events = 1,
			.nr_groups = 1,
		पूर्ण,
		अणु
			.events = "{},{instructions}",
			.nr_events = 1,
			.nr_groups = 1,
		पूर्ण,
		अणु
			.events = "{instructions},{instructions}",
			.nr_events = 2,
			.nr_groups = 2,
		पूर्ण,
		अणु
			.events = "{instructions,cycles},{instructions,cycles}",
			.nr_events = 4,
			.nr_groups = 2,
		पूर्ण,
		अणु
			.events = "{stereolab}",
			.nr_events = 0,
			.nr_groups = 0,
		पूर्ण,
		अणु
			.events =
			"{instructions,cycles},{instructions,stereolab}",
			.nr_events = 3,
			.nr_groups = 1,
		पूर्ण,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(table); i++) अणु
		evlist = evlist__new();
		अगर (evlist == शून्य)
			वापस -ENOMEM;

		opt.value = evlist;
		parse_libpfm_events_option(&opt,
					table[i].events,
					0);
		TEST_ASSERT_EQUAL(table[i].events,
				count_pfm_events(&evlist->core),
				table[i].nr_events);
		TEST_ASSERT_EQUAL(table[i].events,
				evlist->nr_groups,
				table[i].nr_groups);

		evlist__delete(evlist);
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

स्थिर अक्षर *test__pfm_subtest_get_desc(पूर्णांक i)
अणु
	अगर (i < 0 || i >= (पूर्णांक)ARRAY_SIZE(pfm_testहाल_table))
		वापस शून्य;
	वापस pfm_testहाल_table[i].desc;
पूर्ण

पूर्णांक test__pfm_subtest_get_nr(व्योम)
अणु
	वापस (पूर्णांक)ARRAY_SIZE(pfm_testहाल_table);
पूर्ण

पूर्णांक test__pfm(काष्ठा test *test __maybe_unused, पूर्णांक i __maybe_unused)
अणु
#अगर_घोषित HAVE_LIBPFM
	अगर (i < 0 || i >= (पूर्णांक)ARRAY_SIZE(pfm_testहाल_table))
		वापस TEST_FAIL;
	वापस pfm_testहाल_table[i].func();
#अन्यथा
	वापस TEST_SKIP;
#पूर्ण_अगर
पूर्ण
