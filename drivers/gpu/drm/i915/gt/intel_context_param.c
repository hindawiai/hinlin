<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश "i915_active.h"
#समावेश "intel_context.h"
#समावेश "intel_context_param.h"
#समावेश "intel_ring.h"

पूर्णांक पूर्णांकel_context_set_ring_size(काष्ठा पूर्णांकel_context *ce, दीर्घ sz)
अणु
	पूर्णांक err;

	अगर (पूर्णांकel_context_lock_pinned(ce))
		वापस -EINTR;

	err = i915_active_रुको(&ce->active);
	अगर (err < 0)
		जाओ unlock;

	अगर (पूर्णांकel_context_is_pinned(ce)) अणु
		err = -EBUSY; /* In active use, come back later! */
		जाओ unlock;
	पूर्ण

	अगर (test_bit(CONTEXT_ALLOC_BIT, &ce->flags)) अणु
		काष्ठा पूर्णांकel_ring *ring;

		/* Replace the existing ringbuffer */
		ring = पूर्णांकel_engine_create_ring(ce->engine, sz);
		अगर (IS_ERR(ring)) अणु
			err = PTR_ERR(ring);
			जाओ unlock;
		पूर्ण

		पूर्णांकel_ring_put(ce->ring);
		ce->ring = ring;

		/* Context image will be updated on next pin */
	पूर्ण अन्यथा अणु
		ce->ring = __पूर्णांकel_context_ring_size(sz);
	पूर्ण

unlock:
	पूर्णांकel_context_unlock_pinned(ce);
	वापस err;
पूर्ण

दीर्घ पूर्णांकel_context_get_ring_size(काष्ठा पूर्णांकel_context *ce)
अणु
	दीर्घ sz = (अचिन्हित दीर्घ)READ_ONCE(ce->ring);

	अगर (test_bit(CONTEXT_ALLOC_BIT, &ce->flags)) अणु
		अगर (पूर्णांकel_context_lock_pinned(ce))
			वापस -EINTR;

		sz = ce->ring->size;
		पूर्णांकel_context_unlock_pinned(ce);
	पूर्ण

	वापस sz;
पूर्ण
