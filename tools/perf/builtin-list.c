<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * builtin-list.c
 *
 * Builtin list command: list all event types
 *
 * Copyright (C) 2009, Thomas Gleixner <tglx@linutronix.de>
 * Copyright (C) 2008-2009, Red Hat Inc, Ingo Molnar <mingo@redhat.com>
 * Copyright (C) 2011, Red Hat Inc, Arnalकरो Carvalho de Melo <acme@redhat.com>
 */
#समावेश "builtin.h"

#समावेश "util/parse-events.h"
#समावेश "util/pmu.h"
#समावेश "util/debug.h"
#समावेश "util/metricgroup.h"
#समावेश <subcmd/pager.h>
#समावेश <subcmd/parse-options.h>
#समावेश <मानकपन.स>

अटल bool desc_flag = true;
अटल bool details_flag;

पूर्णांक cmd_list(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	पूर्णांक i;
	bool raw_dump = false;
	bool दीर्घ_desc_flag = false;
	bool deprecated = false;
	काष्ठा option list_options[] = अणु
		OPT_BOOLEAN(0, "raw-dump", &raw_dump, "Dump raw events"),
		OPT_BOOLEAN('d', "desc", &desc_flag,
			    "Print extra event descriptions. --no-desc to not print."),
		OPT_BOOLEAN('v', "long-desc", &दीर्घ_desc_flag,
			    "Print longer event descriptions."),
		OPT_BOOLEAN(0, "details", &details_flag,
			    "Print information on the perf event names and expressions used internally by events."),
		OPT_BOOLEAN(0, "deprecated", &deprecated,
			    "Print deprecated events."),
		OPT_INCR(0, "debug", &verbose,
			     "Enable debugging output"),
		OPT_END()
	पूर्ण;
	स्थिर अक्षर * स्थिर list_usage[] = अणु
		"perf list [<options>] [hw|sw|cache|tracepoint|pmu|sdt|metric|metricgroup|event_glob]",
		शून्य
	पूर्ण;

	set_option_flag(list_options, 0, "raw-dump", PARSE_OPT_HIDDEN);

	argc = parse_options(argc, argv, list_options, list_usage,
			     PARSE_OPT_STOP_AT_NON_OPTION);

	setup_pager();

	अगर (!raw_dump && pager_in_use())
		म_लिखो("\nList of pre-defined events (to be used in -e):\n\n");

	अगर (argc == 0) अणु
		prपूर्णांक_events(शून्य, raw_dump, !desc_flag, दीर्घ_desc_flag,
				details_flag, deprecated);
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < argc; ++i) अणु
		अक्षर *sep, *s;

		अगर (म_भेद(argv[i], "tracepoint") == 0)
			prपूर्णांक_tracepoपूर्णांक_events(शून्य, शून्य, raw_dump);
		अन्यथा अगर (म_भेद(argv[i], "hw") == 0 ||
			 म_भेद(argv[i], "hardware") == 0)
			prपूर्णांक_symbol_events(शून्य, PERF_TYPE_HARDWARE,
					event_symbols_hw, PERF_COUNT_HW_MAX, raw_dump);
		अन्यथा अगर (म_भेद(argv[i], "sw") == 0 ||
			 म_भेद(argv[i], "software") == 0) अणु
			prपूर्णांक_symbol_events(शून्य, PERF_TYPE_SOFTWARE,
					event_symbols_sw, PERF_COUNT_SW_MAX, raw_dump);
			prपूर्णांक_tool_events(शून्य, raw_dump);
		पूर्ण अन्यथा अगर (म_भेद(argv[i], "cache") == 0 ||
			 म_भेद(argv[i], "hwcache") == 0)
			prपूर्णांक_hwcache_events(शून्य, raw_dump);
		अन्यथा अगर (म_भेद(argv[i], "pmu") == 0)
			prपूर्णांक_pmu_events(शून्य, raw_dump, !desc_flag,
						दीर्घ_desc_flag, details_flag,
						deprecated);
		अन्यथा अगर (म_भेद(argv[i], "sdt") == 0)
			prपूर्णांक_sdt_events(शून्य, शून्य, raw_dump);
		अन्यथा अगर (म_भेद(argv[i], "metric") == 0 || म_भेद(argv[i], "metrics") == 0)
			metricgroup__prपूर्णांक(true, false, शून्य, raw_dump, details_flag);
		अन्यथा अगर (म_भेद(argv[i], "metricgroup") == 0 || म_भेद(argv[i], "metricgroups") == 0)
			metricgroup__prपूर्णांक(false, true, शून्य, raw_dump, details_flag);
		अन्यथा अगर ((sep = म_अक्षर(argv[i], ':')) != शून्य) अणु
			पूर्णांक sep_idx;

			sep_idx = sep - argv[i];
			s = strdup(argv[i]);
			अगर (s == शून्य)
				वापस -1;

			s[sep_idx] = '\0';
			prपूर्णांक_tracepoपूर्णांक_events(s, s + sep_idx + 1, raw_dump);
			prपूर्णांक_sdt_events(s, s + sep_idx + 1, raw_dump);
			metricgroup__prपूर्णांक(true, true, s, raw_dump, details_flag);
			मुक्त(s);
		पूर्ण अन्यथा अणु
			अगर (aप्र_लिखो(&s, "*%s*", argv[i]) < 0) अणु
				म_लिखो("Critical: Not enough memory! Trying to continue...\n");
				जारी;
			पूर्ण
			prपूर्णांक_symbol_events(s, PERF_TYPE_HARDWARE,
					    event_symbols_hw, PERF_COUNT_HW_MAX, raw_dump);
			prपूर्णांक_symbol_events(s, PERF_TYPE_SOFTWARE,
					    event_symbols_sw, PERF_COUNT_SW_MAX, raw_dump);
			prपूर्णांक_tool_events(s, raw_dump);
			prपूर्णांक_hwcache_events(s, raw_dump);
			prपूर्णांक_pmu_events(s, raw_dump, !desc_flag,
						दीर्घ_desc_flag,
						details_flag,
						deprecated);
			prपूर्णांक_tracepoपूर्णांक_events(शून्य, s, raw_dump);
			prपूर्णांक_sdt_events(शून्य, s, raw_dump);
			metricgroup__prपूर्णांक(true, true, s, raw_dump, details_flag);
			मुक्त(s);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
