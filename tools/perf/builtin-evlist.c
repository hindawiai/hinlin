<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Builtin evlist command: Show the list of event selectors present
 * in a perf.data file.
 */
#समावेश "builtin.h"

#समावेश <linux/list.h>

#समावेश "perf.h"
#समावेश "util/evlist.h"
#समावेश "util/evsel.h"
#समावेश "util/evsel_fprintf.h"
#समावेश "util/parse-events.h"
#समावेश <subcmd/parse-options.h>
#समावेश "util/session.h"
#समावेश "util/data.h"
#समावेश "util/debug.h"
#समावेश <linux/err.h>
#समावेश "util/tool.h"

अटल पूर्णांक process_header_feature(काष्ठा perf_session *session __maybe_unused,
				  जोड़ perf_event *event __maybe_unused)
अणु
	session_करोne = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक __cmd_evlist(स्थिर अक्षर *file_name, काष्ठा perf_attr_details *details)
अणु
	काष्ठा perf_session *session;
	काष्ठा evsel *pos;
	काष्ठा perf_data data = अणु
		.path      = file_name,
		.mode      = PERF_DATA_MODE_READ,
		.क्रमce     = details->क्रमce,
	पूर्ण;
	काष्ठा perf_tool tool = अणु
		/* only needed क्रम pipe mode */
		.attr = perf_event__process_attr,
		.feature = process_header_feature,
	पूर्ण;
	bool has_tracepoपूर्णांक = false;

	session = perf_session__new(&data, 0, &tool);
	अगर (IS_ERR(session))
		वापस PTR_ERR(session);

	अगर (data.is_pipe)
		perf_session__process_events(session);

	evlist__क्रम_each_entry(session->evlist, pos) अणु
		evsel__ख_लिखो(pos, details, मानक_निकास);

		अगर (pos->core.attr.type == PERF_TYPE_TRACEPOINT)
			has_tracepoपूर्णांक = true;
	पूर्ण

	अगर (has_tracepoपूर्णांक && !details->trace_fields)
		म_लिखो("# Tip: use 'perf evlist --trace-fields' to show fields for tracepoint events\n");

	perf_session__delete(session);
	वापस 0;
पूर्ण

पूर्णांक cmd_evlist(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	काष्ठा perf_attr_details details = अणु .verbose = false, पूर्ण;
	स्थिर काष्ठा option options[] = अणु
	OPT_STRING('i', "input", &input_name, "file", "Input file name"),
	OPT_BOOLEAN('F', "freq", &details.freq, "Show the sample frequency"),
	OPT_BOOLEAN('v', "verbose", &details.verbose,
		    "Show all event attr details"),
	OPT_BOOLEAN('g', "group", &details.event_group,
		    "Show event group information"),
	OPT_BOOLEAN('f', "force", &details.force, "don't complain, करो it"),
	OPT_BOOLEAN(0, "trace-fields", &details.trace_fields, "Show tracepoint fields"),
	OPT_END()
	पूर्ण;
	स्थिर अक्षर * स्थिर evlist_usage[] = अणु
		"perf evlist [<options>]",
		शून्य
	पूर्ण;

	argc = parse_options(argc, argv, options, evlist_usage, 0);
	अगर (argc)
		usage_with_options(evlist_usage, options);

	अगर (details.event_group && (details.verbose || details.freq)) अणु
		usage_with_options_msg(evlist_usage, options,
			"--group option is not compatible with other options\n");
	पूर्ण

	वापस __cmd_evlist(input_name, &details);
पूर्ण
