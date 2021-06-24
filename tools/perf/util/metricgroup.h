<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#अगर_अघोषित METRICGROUP_H
#घोषणा METRICGROUP_H 1

#समावेश <linux/list.h>
#समावेश <linux/rbtree.h>
#समावेश <stdbool.h>
#समावेश "pmu-events/pmu-events.h"

काष्ठा evlist;
काष्ठा evsel;
काष्ठा option;
काष्ठा rblist;
काष्ठा pmu_events_map;
काष्ठा cgroup;

काष्ठा metric_event अणु
	काष्ठा rb_node nd;
	काष्ठा evsel *evsel;
	काष्ठा list_head head; /* list of metric_expr */
पूर्ण;

काष्ठा metric_ref अणु
	स्थिर अक्षर *metric_name;
	स्थिर अक्षर *metric_expr;
पूर्ण;

काष्ठा metric_expr अणु
	काष्ठा list_head nd;
	स्थिर अक्षर *metric_expr;
	स्थिर अक्षर *metric_name;
	स्थिर अक्षर *metric_unit;
	काष्ठा evsel **metric_events;
	काष्ठा metric_ref *metric_refs;
	पूर्णांक runसमय;
पूर्ण;

काष्ठा metric_event *metricgroup__lookup(काष्ठा rblist *metric_events,
					 काष्ठा evsel *evsel,
					 bool create);
पूर्णांक metricgroup__parse_groups(स्थिर काष्ठा option *opt,
			      स्थिर अक्षर *str,
			      bool metric_no_group,
			      bool metric_no_merge,
			      काष्ठा rblist *metric_events);
काष्ठा pmu_event *metricgroup__find_metric(स्थिर अक्षर *metric,
					   काष्ठा pmu_events_map *map);
पूर्णांक metricgroup__parse_groups_test(काष्ठा evlist *evlist,
				   काष्ठा pmu_events_map *map,
				   स्थिर अक्षर *str,
				   bool metric_no_group,
				   bool metric_no_merge,
				   काष्ठा rblist *metric_events);

व्योम metricgroup__prपूर्णांक(bool metrics, bool groups, अक्षर *filter,
			bool raw, bool details);
bool metricgroup__has_metric(स्थिर अक्षर *metric);
पूर्णांक arch_get_runसमयparam(काष्ठा pmu_event *pe __maybe_unused);
व्योम metricgroup__rblist_निकास(काष्ठा rblist *metric_events);

पूर्णांक metricgroup__copy_metric_events(काष्ठा evlist *evlist, काष्ठा cgroup *cgrp,
				    काष्ठा rblist *new_metric_events,
				    काष्ठा rblist *old_metric_events);
#पूर्ण_अगर
