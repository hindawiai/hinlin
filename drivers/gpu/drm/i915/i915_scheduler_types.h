<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2018 Intel Corporation
 */

#अगर_अघोषित _I915_SCHEDULER_TYPES_H_
#घोषणा _I915_SCHEDULER_TYPES_H_

#समावेश <linux/list.h>

#समावेश "gt/intel_engine_types.h"
#समावेश "i915_priolist_types.h"

काष्ठा drm_i915_निजी;
काष्ठा i915_request;
काष्ठा पूर्णांकel_engine_cs;

काष्ठा i915_sched_attr अणु
	/**
	 * @priority: execution and service priority
	 *
	 * All clients are equal, but some are more equal than others!
	 *
	 * Requests from a context with a greater (more positive) value of
	 * @priority will be executed beक्रमe those with a lower @priority
	 * value, क्रमming a simple QoS.
	 *
	 * The &drm_i915_निजी.kernel_context is asचिन्हित the lowest priority.
	 */
	पूर्णांक priority;
पूर्ण;

/*
 * "People assume that समय is a strict progression of cause to effect, but
 * actually, from a nonlinear, non-subjective viewpoपूर्णांक, it's more like a big
 * ball of wibbly-wobbly, समयy-wimey ... stuff." -The Doctor, 2015
 *
 * Requests exist in a complex web of पूर्णांकerdependencies. Each request
 * has to रुको क्रम some other request to complete beक्रमe it is पढ़ोy to be run
 * (e.g. we have to रुको until the pixels have been rendering पूर्णांकo a texture
 * beक्रमe we can copy from it). We track the पढ़ोiness of a request in terms
 * of fences, but we also need to keep the dependency tree क्रम the lअगरeसमय
 * of the request (beyond the lअगरe of an inभागidual fence). We use the tree
 * at various poपूर्णांकs to reorder the requests whilst keeping the requests
 * in order with respect to their various dependencies.
 *
 * There is no active component to the "scheduler". As we know the dependency
 * DAG of each request, we are able to insert it पूर्णांकo a sorted queue when it
 * is पढ़ोy, and are able to reorder its portion of the graph to accommodate
 * dynamic priority changes.
 *
 * Ok, there is now one active element to the "scheduler" in the backends.
 * We let a new context run क्रम a small amount of समय beक्रमe re-evaluating
 * the run order. As we re-evaluate, we मुख्यtain the strict ordering of
 * dependencies, but attempt to rotate the active contexts (the current context
 * is put to the back of its priority queue, then reshuffling its dependents).
 * This provides minimal बारlicing and prevents a userspace hog (e.g.
 * something रुकोing on a user semaphore [VkEvent]) from denying service to
 * others.
 */
काष्ठा i915_sched_node अणु
	काष्ठा list_head संकेतers_list; /* those beक्रमe us, we depend upon */
	काष्ठा list_head रुकोers_list; /* those after us, they depend upon us */
	काष्ठा list_head link;
	काष्ठा i915_sched_attr attr;
	अचिन्हित पूर्णांक flags;
#घोषणा I915_SCHED_HAS_EXTERNAL_CHAIN	BIT(0)
	पूर्णांकel_engine_mask_t semaphores;
पूर्ण;

काष्ठा i915_dependency अणु
	काष्ठा i915_sched_node *संकेतer;
	काष्ठा i915_sched_node *रुकोer;
	काष्ठा list_head संकेत_link;
	काष्ठा list_head रुको_link;
	काष्ठा list_head dfs_link;
	अचिन्हित दीर्घ flags;
#घोषणा I915_DEPENDENCY_ALLOC		BIT(0)
#घोषणा I915_DEPENDENCY_EXTERNAL	BIT(1)
#घोषणा I915_DEPENDENCY_WEAK		BIT(2)
पूर्ण;

#घोषणा क्रम_each_रुकोer(p__, rq__) \
	list_क्रम_each_entry_lockless(p__, \
				     &(rq__)->sched.रुकोers_list, \
				     रुको_link)

#घोषणा क्रम_each_संकेतer(p__, rq__) \
	list_क्रम_each_entry_rcu(p__, \
				&(rq__)->sched.संकेतers_list, \
				संकेत_link)

#पूर्ण_अगर /* _I915_SCHEDULER_TYPES_H_ */
