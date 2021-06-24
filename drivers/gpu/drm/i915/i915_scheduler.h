<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2018 Intel Corporation
 */

#अगर_अघोषित _I915_SCHEDULER_H_
#घोषणा _I915_SCHEDULER_H_

#समावेश <linux/bitops.h>
#समावेश <linux/list.h>
#समावेश <linux/kernel.h>

#समावेश "i915_scheduler_types.h"

काष्ठा drm_prपूर्णांकer;

#घोषणा priolist_क्रम_each_request(it, plist) \
	list_क्रम_each_entry(it, &(plist)->requests, sched.link)

#घोषणा priolist_क्रम_each_request_consume(it, n, plist) \
	list_क्रम_each_entry_safe(it, n, &(plist)->requests, sched.link)

व्योम i915_sched_node_init(काष्ठा i915_sched_node *node);
व्योम i915_sched_node_reinit(काष्ठा i915_sched_node *node);

bool __i915_sched_node_add_dependency(काष्ठा i915_sched_node *node,
				      काष्ठा i915_sched_node *संकेत,
				      काष्ठा i915_dependency *dep,
				      अचिन्हित दीर्घ flags);

पूर्णांक i915_sched_node_add_dependency(काष्ठा i915_sched_node *node,
				   काष्ठा i915_sched_node *संकेत,
				   अचिन्हित दीर्घ flags);

व्योम i915_sched_node_fini(काष्ठा i915_sched_node *node);

व्योम i915_schedule(काष्ठा i915_request *request,
		   स्थिर काष्ठा i915_sched_attr *attr);

काष्ठा list_head *
i915_sched_lookup_priolist(काष्ठा पूर्णांकel_engine_cs *engine, पूर्णांक prio);

व्योम __i915_priolist_मुक्त(काष्ठा i915_priolist *p);
अटल अंतरभूत व्योम i915_priolist_मुक्त(काष्ठा i915_priolist *p)
अणु
	अगर (p->priority != I915_PRIORITY_NORMAL)
		__i915_priolist_मुक्त(p);
पूर्ण

व्योम i915_request_show_with_schedule(काष्ठा drm_prपूर्णांकer *m,
				     स्थिर काष्ठा i915_request *rq,
				     स्थिर अक्षर *prefix,
				     पूर्णांक indent);

#पूर्ण_अगर /* _I915_SCHEDULER_H_ */
