<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/err.h>
#समावेश <linux/zभाग.स>
#समावेश <त्रुटिसं.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <sys/param.h>
#समावेश "evlist.h"
#समावेश "evsel.h"
#समावेश "parse-events.h"
#समावेश "parse-events-hybrid.h"
#समावेश "debug.h"
#समावेश "pmu.h"
#समावेश "pmu-hybrid.h"
#समावेश "perf.h"

अटल व्योम config_hybrid_attr(काष्ठा perf_event_attr *attr,
			       पूर्णांक type, पूर्णांक pmu_type)
अणु
	/*
	 * attr.config layout क्रम type PERF_TYPE_HARDWARE and
	 * PERF_TYPE_HW_CACHE
	 *
	 * PERF_TYPE_HARDWARE:                 0xEEEEEEEE000000AA
	 *                                     AA: hardware event ID
	 *                                     EEEEEEEE: PMU type ID
	 * PERF_TYPE_HW_CACHE:                 0xEEEEEEEE00DDCCBB
	 *                                     BB: hardware cache ID
	 *                                     CC: hardware cache op ID
	 *                                     DD: hardware cache op result ID
	 *                                     EEEEEEEE: PMU type ID
	 * If the PMU type ID is 0, the PERF_TYPE_RAW will be applied.
	 */
	attr->type = type;
	attr->config = attr->config | ((__u64)pmu_type << PERF_PMU_TYPE_SHIFT);
पूर्ण

अटल पूर्णांक create_event_hybrid(__u32 config_type, पूर्णांक *idx,
			       काष्ठा list_head *list,
			       काष्ठा perf_event_attr *attr, अक्षर *name,
			       काष्ठा list_head *config_terms,
			       काष्ठा perf_pmu *pmu)
अणु
	काष्ठा evsel *evsel;
	__u32 type = attr->type;
	__u64 config = attr->config;

	config_hybrid_attr(attr, config_type, pmu->type);
	evsel = parse_events__add_event_hybrid(list, idx, attr, name,
					       pmu, config_terms);
	अगर (evsel)
		evsel->pmu_name = strdup(pmu->name);
	अन्यथा
		वापस -ENOMEM;

	attr->type = type;
	attr->config = config;
	वापस 0;
पूर्ण

अटल पूर्णांक pmu_cmp(काष्ठा parse_events_state *parse_state,
		   काष्ठा perf_pmu *pmu)
अणु
	अगर (!parse_state->hybrid_pmu_name)
		वापस 0;

	वापस म_भेद(parse_state->hybrid_pmu_name, pmu->name);
पूर्ण

अटल पूर्णांक add_hw_hybrid(काष्ठा parse_events_state *parse_state,
			 काष्ठा list_head *list, काष्ठा perf_event_attr *attr,
			 अक्षर *name, काष्ठा list_head *config_terms)
अणु
	काष्ठा perf_pmu *pmu;
	पूर्णांक ret;

	perf_pmu__क्रम_each_hybrid_pmu(pmu) अणु
		अगर (pmu_cmp(parse_state, pmu))
			जारी;

		ret = create_event_hybrid(PERF_TYPE_HARDWARE,
					  &parse_state->idx, list, attr, name,
					  config_terms, pmu);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक create_raw_event_hybrid(पूर्णांक *idx, काष्ठा list_head *list,
				   काष्ठा perf_event_attr *attr, अक्षर *name,
				   काष्ठा list_head *config_terms,
				   काष्ठा perf_pmu *pmu)
अणु
	काष्ठा evsel *evsel;

	attr->type = pmu->type;
	evsel = parse_events__add_event_hybrid(list, idx, attr, name,
					       pmu, config_terms);
	अगर (evsel)
		evsel->pmu_name = strdup(pmu->name);
	अन्यथा
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक add_raw_hybrid(काष्ठा parse_events_state *parse_state,
			  काष्ठा list_head *list, काष्ठा perf_event_attr *attr,
			  अक्षर *name, काष्ठा list_head *config_terms)
अणु
	काष्ठा perf_pmu *pmu;
	पूर्णांक ret;

	perf_pmu__क्रम_each_hybrid_pmu(pmu) अणु
		अगर (pmu_cmp(parse_state, pmu))
			जारी;

		ret = create_raw_event_hybrid(&parse_state->idx, list, attr,
					      name, config_terms, pmu);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक parse_events__add_numeric_hybrid(काष्ठा parse_events_state *parse_state,
				     काष्ठा list_head *list,
				     काष्ठा perf_event_attr *attr,
				     अक्षर *name, काष्ठा list_head *config_terms,
				     bool *hybrid)
अणु
	*hybrid = false;
	अगर (attr->type == PERF_TYPE_SOFTWARE)
		वापस 0;

	अगर (!perf_pmu__has_hybrid())
		वापस 0;

	*hybrid = true;
	अगर (attr->type != PERF_TYPE_RAW) अणु
		वापस add_hw_hybrid(parse_state, list, attr, name,
				     config_terms);
	पूर्ण

	वापस add_raw_hybrid(parse_state, list, attr, name,
			      config_terms);
पूर्ण

पूर्णांक parse_events__add_cache_hybrid(काष्ठा list_head *list, पूर्णांक *idx,
				   काष्ठा perf_event_attr *attr, अक्षर *name,
				   काष्ठा list_head *config_terms,
				   bool *hybrid,
				   काष्ठा parse_events_state *parse_state)
अणु
	काष्ठा perf_pmu *pmu;
	पूर्णांक ret;

	*hybrid = false;
	अगर (!perf_pmu__has_hybrid())
		वापस 0;

	*hybrid = true;
	perf_pmu__क्रम_each_hybrid_pmu(pmu) अणु
		अगर (pmu_cmp(parse_state, pmu))
			जारी;

		ret = create_event_hybrid(PERF_TYPE_HW_CACHE, idx, list,
					  attr, name, config_terms, pmu);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
