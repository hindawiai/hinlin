<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "util/iostat.h"
#समावेश "util/debug.h"

क्रमागत iostat_mode_t iostat_mode = IOSTAT_NONE;

__weak पूर्णांक iostat_prepare(काष्ठा evlist *evlist __maybe_unused,
			  काष्ठा perf_stat_config *config __maybe_unused)
अणु
	वापस -1;
पूर्ण

__weak पूर्णांक iostat_parse(स्थिर काष्ठा option *opt __maybe_unused,
			 स्थिर अक्षर *str __maybe_unused,
			 पूर्णांक unset __maybe_unused)
अणु
	pr_err("iostat mode is not supported on current platform\n");
	वापस -1;
पूर्ण

__weak व्योम iostat_list(काष्ठा evlist *evlist __maybe_unused,
		       काष्ठा perf_stat_config *config __maybe_unused)
अणु
पूर्ण

__weak व्योम iostat_release(काष्ठा evlist *evlist __maybe_unused)
अणु
पूर्ण

__weak व्योम iostat_prपूर्णांक_header_prefix(काष्ठा perf_stat_config *config __maybe_unused)
अणु
पूर्ण

__weak व्योम iostat_prपूर्णांक_metric(काष्ठा perf_stat_config *config __maybe_unused,
				काष्ठा evsel *evsel __maybe_unused,
				काष्ठा perf_stat_output_ctx *out __maybe_unused)
अणु
पूर्ण

__weak व्योम iostat_prefix(काष्ठा evlist *evlist __maybe_unused,
			  काष्ठा perf_stat_config *config __maybe_unused,
			  अक्षर *prefix __maybe_unused,
			  काष्ठा बारpec *ts __maybe_unused)
अणु
पूर्ण

__weak व्योम iostat_prपूर्णांक_counters(काष्ठा evlist *evlist __maybe_unused,
				  काष्ठा perf_stat_config *config __maybe_unused,
				  काष्ठा बारpec *ts __maybe_unused,
				  अक्षर *prefix __maybe_unused,
				  iostat_prपूर्णांक_counter_t prपूर्णांक_cnt_cb __maybe_unused)
अणु
पूर्ण
