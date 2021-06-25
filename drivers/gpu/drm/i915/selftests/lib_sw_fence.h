<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * lib_sw_fence.h - library routines क्रम testing N:M synchronisation poपूर्णांकs
 *
 * Copyright (C) 2017 Intel Corporation
 */

#अगर_अघोषित _LIB_SW_FENCE_H_
#घोषणा _LIB_SW_FENCE_H_

#समावेश <linux/समयr.h>

#समावेश "../i915_sw_fence.h"

#अगर_घोषित CONFIG_LOCKDEP
#घोषणा onstack_fence_init(fence)				\
करो अणु								\
	अटल काष्ठा lock_class_key __key;			\
								\
	__onstack_fence_init((fence), #fence, &__key);	\
पूर्ण जबतक (0)
#अन्यथा
#घोषणा onstack_fence_init(fence)				\
	__onstack_fence_init((fence), शून्य, शून्य)
#पूर्ण_अगर

व्योम __onstack_fence_init(काष्ठा i915_sw_fence *fence,
			  स्थिर अक्षर *name,
			  काष्ठा lock_class_key *key);
व्योम onstack_fence_fini(काष्ठा i915_sw_fence *fence);

काष्ठा समयd_fence अणु
	काष्ठा i915_sw_fence fence;
	काष्ठा समयr_list समयr;
पूर्ण;

व्योम समयd_fence_init(काष्ठा समयd_fence *tf, अचिन्हित दीर्घ expires);
व्योम समयd_fence_fini(काष्ठा समयd_fence *tf);

काष्ठा i915_sw_fence *heap_fence_create(gfp_t gfp);
व्योम heap_fence_put(काष्ठा i915_sw_fence *fence);

#पूर्ण_अगर /* _LIB_SW_FENCE_H_ */
