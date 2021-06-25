<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PMU_H
#घोषणा __PMU_H

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/compiler.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/list.h>
#समावेश <stdbool.h>
#समावेश "parse-events.h"
#समावेश "pmu-events/pmu-events.h"

काष्ठा evsel_config_term;

क्रमागत अणु
	PERF_PMU_FORMAT_VALUE_CONFIG,
	PERF_PMU_FORMAT_VALUE_CONFIG1,
	PERF_PMU_FORMAT_VALUE_CONFIG2,
पूर्ण;

#घोषणा PERF_PMU_FORMAT_BITS 64
#घोषणा EVENT_SOURCE_DEVICE_PATH "/bus/event_source/devices/"
#घोषणा CPUS_TEMPLATE_CPU	"%s/bus/event_source/devices/%s/cpus"

काष्ठा perf_event_attr;

काष्ठा perf_pmu_caps अणु
	अक्षर *name;
	अक्षर *value;
	काष्ठा list_head list;
पूर्ण;

काष्ठा perf_pmu अणु
	अक्षर *name;
	अक्षर *id;
	__u32 type;
	bool selectable;
	bool is_uncore;
	bool is_hybrid;
	bool auxtrace;
	पूर्णांक max_precise;
	काष्ठा perf_event_attr *शेष_config;
	काष्ठा perf_cpu_map *cpus;
	काष्ठा list_head क्रमmat;  /* HEAD काष्ठा perf_pmu_क्रमmat -> list */
	काष्ठा list_head aliases; /* HEAD काष्ठा perf_pmu_alias -> list */
	काष्ठा list_head caps;    /* HEAD काष्ठा perf_pmu_caps -> list */
	काष्ठा list_head list;    /* ELEM */
	काष्ठा list_head hybrid_list;
पूर्ण;

बाह्य काष्ठा perf_pmu perf_pmu__fake;

काष्ठा perf_pmu_info अणु
	स्थिर अक्षर *unit;
	स्थिर अक्षर *metric_expr;
	स्थिर अक्षर *metric_name;
	द्विगुन scale;
	bool per_pkg;
	bool snapshot;
पूर्ण;

#घोषणा UNIT_MAX_LEN	31 /* max length क्रम event unit name */

काष्ठा perf_pmu_alias अणु
	अक्षर *name;
	अक्षर *desc;
	अक्षर *दीर्घ_desc;
	अक्षर *topic;
	अक्षर *str;
	काष्ठा list_head terms; /* HEAD काष्ठा parse_events_term -> list */
	काष्ठा list_head list;  /* ELEM */
	अक्षर unit[UNIT_MAX_LEN+1];
	द्विगुन scale;
	bool per_pkg;
	bool snapshot;
	bool deprecated;
	अक्षर *metric_expr;
	अक्षर *metric_name;
	अक्षर *pmu_name;
पूर्ण;

काष्ठा perf_pmu *perf_pmu__find(स्थिर अक्षर *name);
काष्ठा perf_pmu *perf_pmu__find_by_type(अचिन्हित पूर्णांक type);
पूर्णांक perf_pmu__config(काष्ठा perf_pmu *pmu, काष्ठा perf_event_attr *attr,
		     काष्ठा list_head *head_terms,
		     काष्ठा parse_events_error *error);
पूर्णांक perf_pmu__config_terms(स्थिर अक्षर *pmu_name, काष्ठा list_head *क्रमmats,
			   काष्ठा perf_event_attr *attr,
			   काष्ठा list_head *head_terms,
			   bool zero, काष्ठा parse_events_error *error);
__u64 perf_pmu__क्रमmat_bits(काष्ठा list_head *क्रमmats, स्थिर अक्षर *name);
पूर्णांक perf_pmu__क्रमmat_type(काष्ठा list_head *क्रमmats, स्थिर अक्षर *name);
पूर्णांक perf_pmu__check_alias(काष्ठा perf_pmu *pmu, काष्ठा list_head *head_terms,
			  काष्ठा perf_pmu_info *info);
काष्ठा list_head *perf_pmu__alias(काष्ठा perf_pmu *pmu,
				  काष्ठा list_head *head_terms);
व्योम perf_pmu_error(काष्ठा list_head *list, अक्षर *name, अक्षर स्थिर *msg);

पूर्णांक perf_pmu__new_क्रमmat(काष्ठा list_head *list, अक्षर *name,
			 पूर्णांक config, अचिन्हित दीर्घ *bits);
व्योम perf_pmu__set_क्रमmat(अचिन्हित दीर्घ *bits, दीर्घ from, दीर्घ to);
पूर्णांक perf_pmu__क्रमmat_parse(अक्षर *dir, काष्ठा list_head *head);
व्योम perf_pmu__del_क्रमmats(काष्ठा list_head *क्रमmats);

काष्ठा perf_pmu *perf_pmu__scan(काष्ठा perf_pmu *pmu);

bool is_pmu_core(स्थिर अक्षर *name);
व्योम prपूर्णांक_pmu_events(स्थिर अक्षर *event_glob, bool name_only, bool quiet,
		      bool दीर्घ_desc, bool details_flag,
		      bool deprecated);
bool pmu_have_event(स्थिर अक्षर *pname, स्थिर अक्षर *name);

पूर्णांक perf_pmu__scan_file(काष्ठा perf_pmu *pmu, स्थिर अक्षर *name, स्थिर अक्षर *fmt, ...) __म_पूछो(3, 4);

पूर्णांक perf_pmu__test(व्योम);

काष्ठा perf_event_attr *perf_pmu__get_शेष_config(काष्ठा perf_pmu *pmu);
व्योम pmu_add_cpu_aliases_map(काष्ठा list_head *head, काष्ठा perf_pmu *pmu,
			     काष्ठा pmu_events_map *map);

काष्ठा pmu_events_map *perf_pmu__find_map(काष्ठा perf_pmu *pmu);
काष्ठा pmu_events_map *pmu_events_map__find(व्योम);
bool pmu_uncore_alias_match(स्थिर अक्षर *pmu_name, स्थिर अक्षर *name);
व्योम perf_pmu_मुक्त_alias(काष्ठा perf_pmu_alias *alias);

प्रकार पूर्णांक (*pmu_sys_event_iter_fn)(काष्ठा pmu_event *pe, व्योम *data);
व्योम pmu_क्रम_each_sys_event(pmu_sys_event_iter_fn fn, व्योम *data);
पूर्णांक perf_pmu__convert_scale(स्थिर अक्षर *scale, अक्षर **end, द्विगुन *sval);

पूर्णांक perf_pmu__caps_parse(काष्ठा perf_pmu *pmu);

व्योम perf_pmu__warn_invalid_config(काष्ठा perf_pmu *pmu, __u64 config,
				   अक्षर *name);

bool perf_pmu__has_hybrid(व्योम);

#पूर्ण_अगर /* __PMU_H */
