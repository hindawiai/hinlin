<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * perf iostat
 *
 * Copyright (C) 2020, Intel Corporation
 *
 * Authors: Alexander Antonov <alexander.antonov@linux.पूर्णांकel.com>
 */

#अगर_अघोषित _IOSTAT_H
#घोषणा _IOSTAT_H

#समावेश <subcmd/parse-options.h>
#समावेश "util/stat.h"
#समावेश "util/parse-events.h"
#समावेश "util/evlist.h"

काष्ठा option;
काष्ठा perf_stat_config;
काष्ठा evlist;
काष्ठा बारpec;

क्रमागत iostat_mode_t अणु
	IOSTAT_NONE		= -1,
	IOSTAT_RUN		= 0,
	IOSTAT_LIST		= 1
पूर्ण;

बाह्य क्रमागत iostat_mode_t iostat_mode;

प्रकार व्योम (*iostat_prपूर्णांक_counter_t)(काष्ठा perf_stat_config *, काष्ठा evsel *, अक्षर *);

पूर्णांक iostat_prepare(काष्ठा evlist *evlist, काष्ठा perf_stat_config *config);
पूर्णांक iostat_parse(स्थिर काष्ठा option *opt, स्थिर अक्षर *str,
		 पूर्णांक unset __maybe_unused);
व्योम iostat_list(काष्ठा evlist *evlist, काष्ठा perf_stat_config *config);
व्योम iostat_release(काष्ठा evlist *evlist);
व्योम iostat_prefix(काष्ठा evlist *evlist, काष्ठा perf_stat_config *config,
		   अक्षर *prefix, काष्ठा बारpec *ts);
व्योम iostat_prपूर्णांक_header_prefix(काष्ठा perf_stat_config *config);
व्योम iostat_prपूर्णांक_metric(काष्ठा perf_stat_config *config, काष्ठा evsel *evsel,
			 काष्ठा perf_stat_output_ctx *out);
व्योम iostat_prपूर्णांक_counters(काष्ठा evlist *evlist,
			   काष्ठा perf_stat_config *config, काष्ठा बारpec *ts,
			   अक्षर *prefix, iostat_prपूर्णांक_counter_t prपूर्णांक_cnt_cb);

#पूर्ण_अगर /* _IOSTAT_H */
