<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#अगर_अघोषित __PERF_EVSEL_CONFIG_H
#घोषणा __PERF_EVSEL_CONFIG_H 1

#समावेश <linux/types.h>
#समावेश <stdbool.h>

/*
 * The 'struct evsel_config_term' is used to pass event
 * specअगरic configuration data to evsel__config routine.
 * It is allocated within event parsing and attached to
 * evsel::config_terms list head.
*/
क्रमागत evsel_term_type अणु
	EVSEL__CONFIG_TERM_PERIOD,
	EVSEL__CONFIG_TERM_FREQ,
	EVSEL__CONFIG_TERM_TIME,
	EVSEL__CONFIG_TERM_CALLGRAPH,
	EVSEL__CONFIG_TERM_STACK_USER,
	EVSEL__CONFIG_TERM_INHERIT,
	EVSEL__CONFIG_TERM_MAX_STACK,
	EVSEL__CONFIG_TERM_MAX_EVENTS,
	EVSEL__CONFIG_TERM_OVERWRITE,
	EVSEL__CONFIG_TERM_DRV_CFG,
	EVSEL__CONFIG_TERM_BRANCH,
	EVSEL__CONFIG_TERM_PERCORE,
	EVSEL__CONFIG_TERM_AUX_OUTPUT,
	EVSEL__CONFIG_TERM_AUX_SAMPLE_SIZE,
	EVSEL__CONFIG_TERM_CFG_CHG,
पूर्ण;

काष्ठा evsel_config_term अणु
	काष्ठा list_head      list;
	क्रमागत evsel_term_type  type;
	bool		      मुक्त_str;
	जोड़ अणु
		u64	      period;
		u64	      freq;
		bool	      समय;
		u64	      stack_user;
		पूर्णांक	      max_stack;
		bool	      inherit;
		bool	      overग_लिखो;
		अचिन्हित दीर्घ max_events;
		bool	      percore;
		bool	      aux_output;
		u32	      aux_sample_size;
		u64	      cfg_chg;
		अक्षर	      *str;
	पूर्ण val;
	bool weak;
पूर्ण;

काष्ठा evsel;

काष्ठा evsel_config_term *__evsel__get_config_term(काष्ठा evsel *evsel, क्रमागत evsel_term_type type);

#घोषणा evsel__get_config_term(evsel, type) \
	__evsel__get_config_term(evsel, EVSEL__CONFIG_TERM_ ## type)

#पूर्ण_अगर // __PERF_EVSEL_CONFIG_H
