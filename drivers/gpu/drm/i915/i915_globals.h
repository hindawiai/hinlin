<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित _I915_GLOBALS_H_
#घोषणा _I915_GLOBALS_H_

#समावेश <linux/types.h>

प्रकार व्योम (*i915_global_func_t)(व्योम);

काष्ठा i915_global अणु
	काष्ठा list_head link;

	i915_global_func_t shrink;
	i915_global_func_t निकास;
पूर्ण;

व्योम i915_global_रेजिस्टर(काष्ठा i915_global *global);

पूर्णांक i915_globals_init(व्योम);
व्योम i915_globals_park(व्योम);
व्योम i915_globals_unpark(व्योम);
व्योम i915_globals_निकास(व्योम);

/* स्थिरructors */
पूर्णांक i915_global_active_init(व्योम);
पूर्णांक i915_global_buddy_init(व्योम);
पूर्णांक i915_global_context_init(व्योम);
पूर्णांक i915_global_gem_context_init(व्योम);
पूर्णांक i915_global_objects_init(व्योम);
पूर्णांक i915_global_request_init(व्योम);
पूर्णांक i915_global_scheduler_init(व्योम);
पूर्णांक i915_global_vma_init(व्योम);

#पूर्ण_अगर /* _I915_GLOBALS_H_ */
