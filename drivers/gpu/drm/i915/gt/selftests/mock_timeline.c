<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2017-2018 Intel Corporation
 */

#समावेश "../intel_timeline.h"

#समावेश "mock_timeline.h"

व्योम mock_समयline_init(काष्ठा पूर्णांकel_समयline *समयline, u64 context)
अणु
	समयline->gt = शून्य;
	समयline->fence_context = context;

	mutex_init(&समयline->mutex);

	INIT_ACTIVE_FENCE(&समयline->last_request);
	INIT_LIST_HEAD(&समयline->requests);

	i915_syncmap_init(&समयline->sync);

	INIT_LIST_HEAD(&समयline->link);
पूर्ण

व्योम mock_समयline_fini(काष्ठा पूर्णांकel_समयline *समयline)
अणु
	i915_syncmap_मुक्त(&समयline->sync);
पूर्ण
