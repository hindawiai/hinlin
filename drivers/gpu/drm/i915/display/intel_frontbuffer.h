<शैली गुरु>
/*
 * Copyright (c) 2014-2016 Intel Corporation
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
 */

#अगर_अघोषित __INTEL_FRONTBUFFER_H__
#घोषणा __INTEL_FRONTBUFFER_H__

#समावेश <linux/atomic.h>
#समावेश <linux/kref.h>

#समावेश "gem/i915_gem_object_types.h"
#समावेश "i915_active.h"

काष्ठा drm_i915_निजी;

क्रमागत fb_op_origin अणु
	ORIGIN_GTT,
	ORIGIN_CPU,
	ORIGIN_CS,
	ORIGIN_FLIP,
	ORIGIN_सूचीTYFB,
पूर्ण;

काष्ठा पूर्णांकel_frontbuffer अणु
	काष्ठा kref ref;
	atomic_t bits;
	काष्ठा i915_active ग_लिखो;
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा rcu_head rcu;
पूर्ण;

व्योम पूर्णांकel_frontbuffer_flip_prepare(काष्ठा drm_i915_निजी *i915,
				    अचिन्हित frontbuffer_bits);
व्योम पूर्णांकel_frontbuffer_flip_complete(काष्ठा drm_i915_निजी *i915,
				     अचिन्हित frontbuffer_bits);
व्योम पूर्णांकel_frontbuffer_flip(काष्ठा drm_i915_निजी *i915,
			    अचिन्हित frontbuffer_bits);

व्योम पूर्णांकel_frontbuffer_put(काष्ठा पूर्णांकel_frontbuffer *front);

अटल अंतरभूत काष्ठा पूर्णांकel_frontbuffer *
__पूर्णांकel_frontbuffer_get(स्थिर काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा पूर्णांकel_frontbuffer *front;

	अगर (likely(!rcu_access_poपूर्णांकer(obj->frontbuffer)))
		वापस शून्य;

	rcu_पढ़ो_lock();
	करो अणु
		front = rcu_dereference(obj->frontbuffer);
		अगर (!front)
			अवरोध;

		अगर (unlikely(!kref_get_unless_zero(&front->ref)))
			जारी;

		अगर (likely(front == rcu_access_poपूर्णांकer(obj->frontbuffer)))
			अवरोध;

		पूर्णांकel_frontbuffer_put(front);
	पूर्ण जबतक (1);
	rcu_पढ़ो_unlock();

	वापस front;
पूर्ण

काष्ठा पूर्णांकel_frontbuffer *
पूर्णांकel_frontbuffer_get(काष्ठा drm_i915_gem_object *obj);

व्योम __पूर्णांकel_fb_invalidate(काष्ठा पूर्णांकel_frontbuffer *front,
			   क्रमागत fb_op_origin origin,
			   अचिन्हित पूर्णांक frontbuffer_bits);

/**
 * पूर्णांकel_frontbuffer_invalidate - invalidate frontbuffer object
 * @front: GEM object to invalidate
 * @origin: which operation caused the invalidation
 *
 * This function माला_लो called every समय rendering on the given object starts and
 * frontbuffer caching (fbc, low refresh rate क्रम DRRS, panel self refresh) must
 * be invalidated. For ORIGIN_CS any subsequent invalidation will be delayed
 * until the rendering completes or a flip on this frontbuffer plane is
 * scheduled.
 */
अटल अंतरभूत bool पूर्णांकel_frontbuffer_invalidate(काष्ठा पूर्णांकel_frontbuffer *front,
						क्रमागत fb_op_origin origin)
अणु
	अचिन्हित पूर्णांक frontbuffer_bits;

	अगर (!front)
		वापस false;

	frontbuffer_bits = atomic_पढ़ो(&front->bits);
	अगर (!frontbuffer_bits)
		वापस false;

	__पूर्णांकel_fb_invalidate(front, origin, frontbuffer_bits);
	वापस true;
पूर्ण

व्योम __पूर्णांकel_fb_flush(काष्ठा पूर्णांकel_frontbuffer *front,
		      क्रमागत fb_op_origin origin,
		      अचिन्हित पूर्णांक frontbuffer_bits);

/**
 * पूर्णांकel_frontbuffer_flush - flush frontbuffer object
 * @front: GEM object to flush
 * @origin: which operation caused the flush
 *
 * This function माला_लो called every समय rendering on the given object has
 * completed and frontbuffer caching can be started again.
 */
अटल अंतरभूत व्योम पूर्णांकel_frontbuffer_flush(काष्ठा पूर्णांकel_frontbuffer *front,
					   क्रमागत fb_op_origin origin)
अणु
	अचिन्हित पूर्णांक frontbuffer_bits;

	अगर (!front)
		वापस;

	frontbuffer_bits = atomic_पढ़ो(&front->bits);
	अगर (!frontbuffer_bits)
		वापस;

	__पूर्णांकel_fb_flush(front, origin, frontbuffer_bits);
पूर्ण

व्योम पूर्णांकel_frontbuffer_track(काष्ठा पूर्णांकel_frontbuffer *old,
			     काष्ठा पूर्णांकel_frontbuffer *new,
			     अचिन्हित पूर्णांक frontbuffer_bits);

#पूर्ण_अगर /* __INTEL_FRONTBUFFER_H__ */
