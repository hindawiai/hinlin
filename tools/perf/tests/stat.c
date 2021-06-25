<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/compiler.h>
#समावेश "event.h"
#समावेश "tests.h"
#समावेश "stat.h"
#समावेश "counts.h"
#समावेश "debug.h"
#समावेश "util/synthetic-events.h"

अटल bool has_term(काष्ठा perf_record_stat_config *config,
		     u64 tag, u64 val)
अणु
	अचिन्हित i;

	क्रम (i = 0; i < config->nr; i++) अणु
		अगर ((config->data[i].tag == tag) &&
		    (config->data[i].val == val))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक process_stat_config_event(काष्ठा perf_tool *tool __maybe_unused,
				     जोड़ perf_event *event,
				     काष्ठा perf_sample *sample __maybe_unused,
				     काष्ठा machine *machine __maybe_unused)
अणु
	काष्ठा perf_record_stat_config *config = &event->stat_config;
	काष्ठा perf_stat_config stat_config;

#घोषणा HAS(term, val) \
	has_term(config, PERF_STAT_CONFIG_TERM__##term, val)

	TEST_ASSERT_VAL("wrong nr",        config->nr == PERF_STAT_CONFIG_TERM__MAX);
	TEST_ASSERT_VAL("wrong aggr_mode", HAS(AGGR_MODE, AGGR_CORE));
	TEST_ASSERT_VAL("wrong scale",     HAS(SCALE, 1));
	TEST_ASSERT_VAL("wrong interval",  HAS(INTERVAL, 1));

#अघोषित HAS

	perf_event__पढ़ो_stat_config(&stat_config, config);

	TEST_ASSERT_VAL("wrong aggr_mode", stat_config.aggr_mode == AGGR_CORE);
	TEST_ASSERT_VAL("wrong scale",     stat_config.scale == 1);
	TEST_ASSERT_VAL("wrong interval",  stat_config.पूर्णांकerval == 1);
	वापस 0;
पूर्ण

पूर्णांक test__synthesize_stat_config(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	काष्ठा perf_stat_config stat_config = अणु
		.aggr_mode	= AGGR_CORE,
		.scale		= 1,
		.पूर्णांकerval	= 1,
	पूर्ण;

	TEST_ASSERT_VAL("failed to synthesize stat_config",
		!perf_event__synthesize_stat_config(शून्य, &stat_config, process_stat_config_event, शून्य));

	वापस 0;
पूर्ण

अटल पूर्णांक process_stat_event(काष्ठा perf_tool *tool __maybe_unused,
			      जोड़ perf_event *event,
			      काष्ठा perf_sample *sample __maybe_unused,
			      काष्ठा machine *machine __maybe_unused)
अणु
	काष्ठा perf_record_stat *st = &event->stat;

	TEST_ASSERT_VAL("wrong cpu",    st->cpu    == 1);
	TEST_ASSERT_VAL("wrong thread", st->thपढ़ो == 2);
	TEST_ASSERT_VAL("wrong id",     st->id     == 3);
	TEST_ASSERT_VAL("wrong val",    st->val    == 100);
	TEST_ASSERT_VAL("wrong run",    st->ena    == 200);
	TEST_ASSERT_VAL("wrong ena",    st->run    == 300);
	वापस 0;
पूर्ण

पूर्णांक test__synthesize_stat(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	काष्ठा perf_counts_values count;

	count.val = 100;
	count.ena = 200;
	count.run = 300;

	TEST_ASSERT_VAL("failed to synthesize stat_config",
		!perf_event__synthesize_stat(शून्य, 1, 2, 3, &count, process_stat_event, शून्य));

	वापस 0;
पूर्ण

अटल पूर्णांक process_stat_round_event(काष्ठा perf_tool *tool __maybe_unused,
				    जोड़ perf_event *event,
				    काष्ठा perf_sample *sample __maybe_unused,
				    काष्ठा machine *machine __maybe_unused)
अणु
	काष्ठा perf_record_stat_round *stat_round = &event->stat_round;

	TEST_ASSERT_VAL("wrong time", stat_round->समय == 0xdeadbeef);
	TEST_ASSERT_VAL("wrong type", stat_round->type == PERF_STAT_ROUND_TYPE__INTERVAL);
	वापस 0;
पूर्ण

पूर्णांक test__synthesize_stat_round(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	TEST_ASSERT_VAL("failed to synthesize stat_config",
		!perf_event__synthesize_stat_round(शून्य, 0xdeadbeef, PERF_STAT_ROUND_TYPE__INTERVAL,
						   process_stat_round_event, शून्य));

	वापस 0;
पूर्ण
