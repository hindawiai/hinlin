<शैली गुरु>
/*
 * Copyright तऊ 2014 Intel Corporation
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
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *	Daniel Vetter <daniel.vetter@ffwll.ch>
 */

/**
 * DOC: frontbuffer tracking
 *
 * Many features require us to track changes to the currently active
 * frontbuffer, especially rendering targeted at the frontbuffer.
 *
 * To be able to करो so we track frontbuffers using a biपंचांगask क्रम all possible
 * frontbuffer slots through पूर्णांकel_frontbuffer_track(). The functions in this
 * file are then called when the contents of the frontbuffer are invalidated,
 * when frontbuffer rendering has stopped again to flush out all the changes
 * and when the frontbuffer is exchanged with a flip. Subप्रणालीs पूर्णांकerested in
 * frontbuffer changes (e.g. PSR, FBC, DRRS) should directly put their callbacks
 * पूर्णांकo the relevant places and filter क्रम the frontbuffer slots that they are
 * पूर्णांकerested पूर्णांक.
 *
 * On a high level there are two types of घातersaving features. The first one
 * work like a special cache (FBC and PSR) and are पूर्णांकerested when they should
 * stop caching and when to restart caching. This is करोne by placing callbacks
 * पूर्णांकo the invalidate and the flush functions: At invalidate the caching must
 * be stopped and at flush समय it can be restarted. And maybe they need to know
 * when the frontbuffer changes (e.g. when the hw करोesn't initiate an invalidate
 * and flush on its own) which can be achieved with placing callbacks पूर्णांकo the
 * flip functions.
 *
 * The other type of display घातer saving feature only cares about busyness
 * (e.g. DRRS). In that हाल all three (invalidate, flush and flip) indicate
 * busyness. There is no direct way to detect idleness. Instead an idle समयr
 * work delayed work should be started from the flush and flip functions and
 * cancelled as soon as busyness is detected.
 */

#समावेश "display/intel_dp.h"

#समावेश "i915_drv.h"
#समावेश "intel_display_types.h"
#समावेश "intel_fbc.h"
#समावेश "intel_frontbuffer.h"
#समावेश "intel_psr.h"

/**
 * frontbuffer_flush - flush frontbuffer
 * @i915: i915 device
 * @frontbuffer_bits: frontbuffer plane tracking bits
 * @origin: which operation caused the flush
 *
 * This function माला_लो called every समय rendering on the given planes has
 * completed and frontbuffer caching can be started again. Flushes will get
 * delayed अगर they're blocked by some outstanding asynchronous rendering.
 *
 * Can be called without any locks held.
 */
अटल व्योम frontbuffer_flush(काष्ठा drm_i915_निजी *i915,
			      अचिन्हित पूर्णांक frontbuffer_bits,
			      क्रमागत fb_op_origin origin)
अणु
	/* Delay flushing when rings are still busy.*/
	spin_lock(&i915->fb_tracking.lock);
	frontbuffer_bits &= ~i915->fb_tracking.busy_bits;
	spin_unlock(&i915->fb_tracking.lock);

	अगर (!frontbuffer_bits)
		वापस;

	might_sleep();
	पूर्णांकel_edp_drrs_flush(i915, frontbuffer_bits);
	पूर्णांकel_psr_flush(i915, frontbuffer_bits, origin);
	पूर्णांकel_fbc_flush(i915, frontbuffer_bits, origin);
पूर्ण

/**
 * पूर्णांकel_frontbuffer_flip_prepare - prepare asynchronous frontbuffer flip
 * @i915: i915 device
 * @frontbuffer_bits: frontbuffer plane tracking bits
 *
 * This function माला_लो called after scheduling a flip on @obj. The actual
 * frontbuffer flushing will be delayed until completion is संकेतled with
 * पूर्णांकel_frontbuffer_flip_complete. If an invalidate happens in between this
 * flush will be cancelled.
 *
 * Can be called without any locks held.
 */
व्योम पूर्णांकel_frontbuffer_flip_prepare(काष्ठा drm_i915_निजी *i915,
				    अचिन्हित frontbuffer_bits)
अणु
	spin_lock(&i915->fb_tracking.lock);
	i915->fb_tracking.flip_bits |= frontbuffer_bits;
	/* Remove stale busy bits due to the old buffer. */
	i915->fb_tracking.busy_bits &= ~frontbuffer_bits;
	spin_unlock(&i915->fb_tracking.lock);
पूर्ण

/**
 * पूर्णांकel_frontbuffer_flip_complete - complete asynchronous frontbuffer flip
 * @i915: i915 device
 * @frontbuffer_bits: frontbuffer plane tracking bits
 *
 * This function माला_लो called after the flip has been latched and will complete
 * on the next vblank. It will execute the flush अगर it hasn't been cancelled yet.
 *
 * Can be called without any locks held.
 */
व्योम पूर्णांकel_frontbuffer_flip_complete(काष्ठा drm_i915_निजी *i915,
				     अचिन्हित frontbuffer_bits)
अणु
	spin_lock(&i915->fb_tracking.lock);
	/* Mask any cancelled flips. */
	frontbuffer_bits &= i915->fb_tracking.flip_bits;
	i915->fb_tracking.flip_bits &= ~frontbuffer_bits;
	spin_unlock(&i915->fb_tracking.lock);

	अगर (frontbuffer_bits)
		frontbuffer_flush(i915, frontbuffer_bits, ORIGIN_FLIP);
पूर्ण

/**
 * पूर्णांकel_frontbuffer_flip - synchronous frontbuffer flip
 * @i915: i915 device
 * @frontbuffer_bits: frontbuffer plane tracking bits
 *
 * This function माला_लो called after scheduling a flip on @obj. This is क्रम
 * synchronous plane updates which will happen on the next vblank and which will
 * not get delayed by pending gpu rendering.
 *
 * Can be called without any locks held.
 */
व्योम पूर्णांकel_frontbuffer_flip(काष्ठा drm_i915_निजी *i915,
			    अचिन्हित frontbuffer_bits)
अणु
	spin_lock(&i915->fb_tracking.lock);
	/* Remove stale busy bits due to the old buffer. */
	i915->fb_tracking.busy_bits &= ~frontbuffer_bits;
	spin_unlock(&i915->fb_tracking.lock);

	frontbuffer_flush(i915, frontbuffer_bits, ORIGIN_FLIP);
पूर्ण

व्योम __पूर्णांकel_fb_invalidate(काष्ठा पूर्णांकel_frontbuffer *front,
			   क्रमागत fb_op_origin origin,
			   अचिन्हित पूर्णांक frontbuffer_bits)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(front->obj->base.dev);

	अगर (origin == ORIGIN_CS) अणु
		spin_lock(&i915->fb_tracking.lock);
		i915->fb_tracking.busy_bits |= frontbuffer_bits;
		i915->fb_tracking.flip_bits &= ~frontbuffer_bits;
		spin_unlock(&i915->fb_tracking.lock);
	पूर्ण

	might_sleep();
	पूर्णांकel_psr_invalidate(i915, frontbuffer_bits, origin);
	पूर्णांकel_edp_drrs_invalidate(i915, frontbuffer_bits);
	पूर्णांकel_fbc_invalidate(i915, frontbuffer_bits, origin);
पूर्ण

व्योम __पूर्णांकel_fb_flush(काष्ठा पूर्णांकel_frontbuffer *front,
		      क्रमागत fb_op_origin origin,
		      अचिन्हित पूर्णांक frontbuffer_bits)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(front->obj->base.dev);

	अगर (origin == ORIGIN_CS) अणु
		spin_lock(&i915->fb_tracking.lock);
		/* Filter out new bits since rendering started. */
		frontbuffer_bits &= i915->fb_tracking.busy_bits;
		i915->fb_tracking.busy_bits &= ~frontbuffer_bits;
		spin_unlock(&i915->fb_tracking.lock);
	पूर्ण

	अगर (frontbuffer_bits)
		frontbuffer_flush(i915, frontbuffer_bits, origin);
पूर्ण

अटल पूर्णांक frontbuffer_active(काष्ठा i915_active *ref)
अणु
	काष्ठा पूर्णांकel_frontbuffer *front =
		container_of(ref, typeof(*front), ग_लिखो);

	kref_get(&front->ref);
	वापस 0;
पूर्ण

__i915_active_call
अटल व्योम frontbuffer_retire(काष्ठा i915_active *ref)
अणु
	काष्ठा पूर्णांकel_frontbuffer *front =
		container_of(ref, typeof(*front), ग_लिखो);

	पूर्णांकel_frontbuffer_flush(front, ORIGIN_CS);
	पूर्णांकel_frontbuffer_put(front);
पूर्ण

अटल व्योम frontbuffer_release(काष्ठा kref *ref)
	__releases(&to_i915(front->obj->base.dev)->fb_tracking.lock)
अणु
	काष्ठा पूर्णांकel_frontbuffer *front =
		container_of(ref, typeof(*front), ref);
	काष्ठा drm_i915_gem_object *obj = front->obj;
	काष्ठा i915_vma *vma;

	drm_WARN_ON(obj->base.dev, atomic_पढ़ो(&front->bits));

	spin_lock(&obj->vma.lock);
	क्रम_each_ggtt_vma(vma, obj) अणु
		i915_vma_clear_scanout(vma);
		vma->display_alignment = I915_GTT_MIN_ALIGNMENT;
	पूर्ण
	spin_unlock(&obj->vma.lock);

	RCU_INIT_POINTER(obj->frontbuffer, शून्य);
	spin_unlock(&to_i915(obj->base.dev)->fb_tracking.lock);

	i915_active_fini(&front->ग_लिखो);

	i915_gem_object_put(obj);
	kमुक्त_rcu(front, rcu);
पूर्ण

काष्ठा पूर्णांकel_frontbuffer *
पूर्णांकel_frontbuffer_get(काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(obj->base.dev);
	काष्ठा पूर्णांकel_frontbuffer *front;

	front = __पूर्णांकel_frontbuffer_get(obj);
	अगर (front)
		वापस front;

	front = kदो_स्मृति(माप(*front), GFP_KERNEL);
	अगर (!front)
		वापस शून्य;

	front->obj = obj;
	kref_init(&front->ref);
	atomic_set(&front->bits, 0);
	i915_active_init(&front->ग_लिखो,
			 frontbuffer_active,
			 i915_active_may_sleep(frontbuffer_retire));

	spin_lock(&i915->fb_tracking.lock);
	अगर (rcu_access_poपूर्णांकer(obj->frontbuffer)) अणु
		kमुक्त(front);
		front = rcu_dereference_रक्षित(obj->frontbuffer, true);
		kref_get(&front->ref);
	पूर्ण अन्यथा अणु
		i915_gem_object_get(obj);
		rcu_assign_poपूर्णांकer(obj->frontbuffer, front);
	पूर्ण
	spin_unlock(&i915->fb_tracking.lock);

	वापस front;
पूर्ण

व्योम पूर्णांकel_frontbuffer_put(काष्ठा पूर्णांकel_frontbuffer *front)
अणु
	kref_put_lock(&front->ref,
		      frontbuffer_release,
		      &to_i915(front->obj->base.dev)->fb_tracking.lock);
पूर्ण

/**
 * पूर्णांकel_frontbuffer_track - update frontbuffer tracking
 * @old: current buffer क्रम the frontbuffer slots
 * @new: new buffer क्रम the frontbuffer slots
 * @frontbuffer_bits: biपंचांगask of frontbuffer slots
 *
 * This updates the frontbuffer tracking bits @frontbuffer_bits by clearing them
 * from @old and setting them in @new. Both @old and @new can be शून्य.
 */
व्योम पूर्णांकel_frontbuffer_track(काष्ठा पूर्णांकel_frontbuffer *old,
			     काष्ठा पूर्णांकel_frontbuffer *new,
			     अचिन्हित पूर्णांक frontbuffer_bits)
अणु
	/*
	 * Control of inभागidual bits within the mask are guarded by
	 * the owning plane->mutex, i.e. we can never see concurrent
	 * manipulation of inभागidual bits. But since the bitfield as a whole
	 * is updated using RMW, we need to use atomics in order to update
	 * the bits.
	 */
	BUILD_BUG_ON(INTEL_FRONTBUFFER_BITS_PER_PIPE * I915_MAX_PIPES >
		     BITS_PER_TYPE(atomic_t));

	अगर (old) अणु
		drm_WARN_ON(old->obj->base.dev,
			    !(atomic_पढ़ो(&old->bits) & frontbuffer_bits));
		atomic_andnot(frontbuffer_bits, &old->bits);
	पूर्ण

	अगर (new) अणु
		drm_WARN_ON(new->obj->base.dev,
			    atomic_पढ़ो(&new->bits) & frontbuffer_bits);
		atomic_or(frontbuffer_bits, &new->bits);
	पूर्ण
पूर्ण
