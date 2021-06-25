<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित CEPH_CRUSH_MAPPER_H
#घोषणा CEPH_CRUSH_MAPPER_H

/*
 * CRUSH functions क्रम find rules and then mapping an input to an
 * output set.
 *
 * LGPL2
 */

#समावेश "crush.h"

बाह्य पूर्णांक crush_find_rule(स्थिर काष्ठा crush_map *map, पूर्णांक ruleset, पूर्णांक type, पूर्णांक size);
पूर्णांक crush_करो_rule(स्थिर काष्ठा crush_map *map,
		  पूर्णांक ruleno, पूर्णांक x, पूर्णांक *result, पूर्णांक result_max,
		  स्थिर __u32 *weight, पूर्णांक weight_max,
		  व्योम *cwin, स्थिर काष्ठा crush_choose_arg *choose_args);

/*
 * Returns the exact amount of workspace that will need to be used
 * क्रम a given combination of crush_map and result_max. The caller can
 * then allocate this much on its own, either on the stack, in a
 * per-thपढ़ो दीर्घ-lived buffer, or however it likes.
 */
अटल अंतरभूत माप_प्रकार crush_work_size(स्थिर काष्ठा crush_map *map,
				     पूर्णांक result_max)
अणु
	वापस map->working_size + result_max * 3 * माप(__u32);
पूर्ण

व्योम crush_init_workspace(स्थिर काष्ठा crush_map *map, व्योम *v);

#पूर्ण_अगर
