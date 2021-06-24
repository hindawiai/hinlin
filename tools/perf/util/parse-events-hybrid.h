<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_PARSE_EVENTS_HYBRID_H
#घोषणा __PERF_PARSE_EVENTS_HYBRID_H

#समावेश <linux/list.h>
#समावेश <stdbool.h>
#समावेश <linux/types.h>
#समावेश <linux/perf_event.h>
#समावेश <माला.स>

पूर्णांक parse_events__add_numeric_hybrid(काष्ठा parse_events_state *parse_state,
				     काष्ठा list_head *list,
				     काष्ठा perf_event_attr *attr,
				     अक्षर *name, काष्ठा list_head *config_terms,
				     bool *hybrid);

पूर्णांक parse_events__add_cache_hybrid(काष्ठा list_head *list, पूर्णांक *idx,
				   काष्ठा perf_event_attr *attr, अक्षर *name,
				   काष्ठा list_head *config_terms,
				   bool *hybrid,
				   काष्ठा parse_events_state *parse_state);

#पूर्ण_अगर /* __PERF_PARSE_EVENTS_HYBRID_H */
