<शैली गुरु>
/*
 * Copyright तऊ 2017 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */

#समावेश "lib_sw_fence.h"

/* Small library of dअगरferent fence types useful क्रम writing tests */

अटल पूर्णांक __i915_sw_fence_call
nop_fence_notअगरy(काष्ठा i915_sw_fence *fence, क्रमागत i915_sw_fence_notअगरy state)
अणु
	वापस NOTIFY_DONE;
पूर्ण

व्योम __onstack_fence_init(काष्ठा i915_sw_fence *fence,
			  स्थिर अक्षर *name,
			  काष्ठा lock_class_key *key)
अणु
	debug_fence_init_onstack(fence);

	__init_रुकोqueue_head(&fence->रुको, name, key);
	atomic_set(&fence->pending, 1);
	fence->error = 0;
	fence->flags = (अचिन्हित दीर्घ)nop_fence_notअगरy;
पूर्ण

व्योम onstack_fence_fini(काष्ठा i915_sw_fence *fence)
अणु
	अगर (!fence->flags)
		वापस;

	i915_sw_fence_commit(fence);
	i915_sw_fence_fini(fence);
पूर्ण

अटल व्योम समयd_fence_wake(काष्ठा समयr_list *t)
अणु
	काष्ठा समयd_fence *tf = from_समयr(tf, t, समयr);

	i915_sw_fence_commit(&tf->fence);
पूर्ण

व्योम समयd_fence_init(काष्ठा समयd_fence *tf, अचिन्हित दीर्घ expires)
अणु
	onstack_fence_init(&tf->fence);

	समयr_setup_on_stack(&tf->समयr, समयd_fence_wake, 0);

	अगर (समय_after(expires, jअगरfies))
		mod_समयr(&tf->समयr, expires);
	अन्यथा
		i915_sw_fence_commit(&tf->fence);
पूर्ण

व्योम समयd_fence_fini(काष्ठा समयd_fence *tf)
अणु
	अगर (del_समयr_sync(&tf->समयr))
		i915_sw_fence_commit(&tf->fence);

	destroy_समयr_on_stack(&tf->समयr);
	i915_sw_fence_fini(&tf->fence);
पूर्ण

काष्ठा heap_fence अणु
	काष्ठा i915_sw_fence fence;
	जोड़ अणु
		काष्ठा kref ref;
		काष्ठा rcu_head rcu;
	पूर्ण;
पूर्ण;

अटल पूर्णांक __i915_sw_fence_call
heap_fence_notअगरy(काष्ठा i915_sw_fence *fence, क्रमागत i915_sw_fence_notअगरy state)
अणु
	काष्ठा heap_fence *h = container_of(fence, typeof(*h), fence);

	चयन (state) अणु
	हाल FENCE_COMPLETE:
		अवरोध;

	हाल FENCE_FREE:
		heap_fence_put(&h->fence);
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

काष्ठा i915_sw_fence *heap_fence_create(gfp_t gfp)
अणु
	काष्ठा heap_fence *h;

	h = kदो_स्मृति(माप(*h), gfp);
	अगर (!h)
		वापस शून्य;

	i915_sw_fence_init(&h->fence, heap_fence_notअगरy);
	refcount_set(&h->ref.refcount, 2);

	वापस &h->fence;
पूर्ण

अटल व्योम heap_fence_release(काष्ठा kref *ref)
अणु
	काष्ठा heap_fence *h = container_of(ref, typeof(*h), ref);

	i915_sw_fence_fini(&h->fence);

	kमुक्त_rcu(h, rcu);
पूर्ण

व्योम heap_fence_put(काष्ठा i915_sw_fence *fence)
अणु
	काष्ठा heap_fence *h = container_of(fence, typeof(*h), fence);

	kref_put(&h->ref, heap_fence_release);
पूर्ण
