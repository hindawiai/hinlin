<शैली गुरु>
/*
 * Copyright तऊ 2016 Intel Corporation
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

#अगर_अघोषित __I915_VMA_H__
#घोषणा __I915_VMA_H__

#समावेश <linux/io-mapping.h>
#समावेश <linux/rbtree.h>

#समावेश <drm/drm_mm.h>

#समावेश "gt/intel_ggtt_fencing.h"
#समावेश "gem/i915_gem_object.h"

#समावेश "i915_gem_gtt.h"

#समावेश "i915_active.h"
#समावेश "i915_request.h"
#समावेश "i915_vma_types.h"

काष्ठा i915_vma *
i915_vma_instance(काष्ठा drm_i915_gem_object *obj,
		  काष्ठा i915_address_space *vm,
		  स्थिर काष्ठा i915_ggtt_view *view);

व्योम i915_vma_unpin_and_release(काष्ठा i915_vma **p_vma, अचिन्हित पूर्णांक flags);
#घोषणा I915_VMA_RELEASE_MAP BIT(0)

अटल अंतरभूत bool i915_vma_is_active(स्थिर काष्ठा i915_vma *vma)
अणु
	वापस !i915_active_is_idle(&vma->active);
पूर्ण

/* करो not reserve memory to prevent deadlocks */
#घोषणा __EXEC_OBJECT_NO_RESERVE BIT(31)

पूर्णांक __must_check __i915_vma_move_to_active(काष्ठा i915_vma *vma,
					   काष्ठा i915_request *rq);
पूर्णांक __must_check i915_vma_move_to_active(काष्ठा i915_vma *vma,
					 काष्ठा i915_request *rq,
					 अचिन्हित पूर्णांक flags);

#घोषणा __i915_vma_flags(v) ((अचिन्हित दीर्घ *)&(v)->flags.counter)

अटल अंतरभूत bool i915_vma_is_ggtt(स्थिर काष्ठा i915_vma *vma)
अणु
	वापस test_bit(I915_VMA_GGTT_BIT, __i915_vma_flags(vma));
पूर्ण

अटल अंतरभूत bool i915_vma_has_ggtt_ग_लिखो(स्थिर काष्ठा i915_vma *vma)
अणु
	वापस test_bit(I915_VMA_GGTT_WRITE_BIT, __i915_vma_flags(vma));
पूर्ण

अटल अंतरभूत व्योम i915_vma_set_ggtt_ग_लिखो(काष्ठा i915_vma *vma)
अणु
	GEM_BUG_ON(!i915_vma_is_ggtt(vma));
	set_bit(I915_VMA_GGTT_WRITE_BIT, __i915_vma_flags(vma));
पूर्ण

अटल अंतरभूत bool i915_vma_unset_ggtt_ग_लिखो(काष्ठा i915_vma *vma)
अणु
	वापस test_and_clear_bit(I915_VMA_GGTT_WRITE_BIT,
				  __i915_vma_flags(vma));
पूर्ण

व्योम i915_vma_flush_ग_लिखोs(काष्ठा i915_vma *vma);

अटल अंतरभूत bool i915_vma_is_map_and_fenceable(स्थिर काष्ठा i915_vma *vma)
अणु
	वापस test_bit(I915_VMA_CAN_FENCE_BIT, __i915_vma_flags(vma));
पूर्ण

अटल अंतरभूत bool i915_vma_set_userfault(काष्ठा i915_vma *vma)
अणु
	GEM_BUG_ON(!i915_vma_is_map_and_fenceable(vma));
	वापस test_and_set_bit(I915_VMA_USERFAULT_BIT, __i915_vma_flags(vma));
पूर्ण

अटल अंतरभूत व्योम i915_vma_unset_userfault(काष्ठा i915_vma *vma)
अणु
	वापस clear_bit(I915_VMA_USERFAULT_BIT, __i915_vma_flags(vma));
पूर्ण

अटल अंतरभूत bool i915_vma_has_userfault(स्थिर काष्ठा i915_vma *vma)
अणु
	वापस test_bit(I915_VMA_USERFAULT_BIT, __i915_vma_flags(vma));
पूर्ण

अटल अंतरभूत bool i915_vma_is_बंदd(स्थिर काष्ठा i915_vma *vma)
अणु
	वापस !list_empty(&vma->बंदd_link);
पूर्ण

अटल अंतरभूत u32 i915_ggtt_offset(स्थिर काष्ठा i915_vma *vma)
अणु
	GEM_BUG_ON(!i915_vma_is_ggtt(vma));
	GEM_BUG_ON(!drm_mm_node_allocated(&vma->node));
	GEM_BUG_ON(upper_32_bits(vma->node.start));
	GEM_BUG_ON(upper_32_bits(vma->node.start + vma->node.size - 1));
	वापस lower_32_bits(vma->node.start);
पूर्ण

अटल अंतरभूत u32 i915_ggtt_pin_bias(काष्ठा i915_vma *vma)
अणु
	वापस i915_vm_to_ggtt(vma->vm)->pin_bias;
पूर्ण

अटल अंतरभूत काष्ठा i915_vma *i915_vma_get(काष्ठा i915_vma *vma)
अणु
	i915_gem_object_get(vma->obj);
	वापस vma;
पूर्ण

अटल अंतरभूत काष्ठा i915_vma *i915_vma_tryget(काष्ठा i915_vma *vma)
अणु
	अगर (likely(kref_get_unless_zero(&vma->obj->base.refcount)))
		वापस vma;

	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम i915_vma_put(काष्ठा i915_vma *vma)
अणु
	i915_gem_object_put(vma->obj);
पूर्ण

अटल __always_अंतरभूत सूचक_भेद_प्रकार ptrdअगरf(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	वापस a - b;
पूर्ण

अटल अंतरभूत दीर्घ
i915_vma_compare(काष्ठा i915_vma *vma,
		 काष्ठा i915_address_space *vm,
		 स्थिर काष्ठा i915_ggtt_view *view)
अणु
	सूचक_भेद_प्रकार cmp;

	GEM_BUG_ON(view && !i915_is_ggtt(vm));

	cmp = ptrdअगरf(vma->vm, vm);
	अगर (cmp)
		वापस cmp;

	BUILD_BUG_ON(I915_GGTT_VIEW_NORMAL != 0);
	cmp = vma->ggtt_view.type;
	अगर (!view)
		वापस cmp;

	cmp -= view->type;
	अगर (cmp)
		वापस cmp;

	निश्चित_i915_gem_gtt_types();

	/* ggtt_view.type also encodes its size so that we both distinguish
	 * dअगरferent views using it as a "type" and also use a compact (no
	 * accessing of uninitialised padding bytes) स_भेद without storing
	 * an extra parameter or adding more code.
	 *
	 * To ensure that the स_भेद is valid क्रम all branches of the जोड़,
	 * even though the code looks like it is just comparing one branch,
	 * we निश्चित above that all branches have the same address, and that
	 * each branch has a unique type/size.
	 */
	BUILD_BUG_ON(I915_GGTT_VIEW_NORMAL >= I915_GGTT_VIEW_PARTIAL);
	BUILD_BUG_ON(I915_GGTT_VIEW_PARTIAL >= I915_GGTT_VIEW_ROTATED);
	BUILD_BUG_ON(I915_GGTT_VIEW_ROTATED >= I915_GGTT_VIEW_REMAPPED);
	BUILD_BUG_ON(दुरत्व(typeof(*view), rotated) !=
		     दुरत्व(typeof(*view), partial));
	BUILD_BUG_ON(दुरत्व(typeof(*view), rotated) !=
		     दुरत्व(typeof(*view), remapped));
	वापस स_भेद(&vma->ggtt_view.partial, &view->partial, view->type);
पूर्ण

काष्ठा i915_vma_work *i915_vma_work(व्योम);
पूर्णांक i915_vma_bind(काष्ठा i915_vma *vma,
		  क्रमागत i915_cache_level cache_level,
		  u32 flags,
		  काष्ठा i915_vma_work *work);

bool i915_gem_valid_gtt_space(काष्ठा i915_vma *vma, अचिन्हित दीर्घ color);
bool i915_vma_misplaced(स्थिर काष्ठा i915_vma *vma,
			u64 size, u64 alignment, u64 flags);
व्योम __i915_vma_set_map_and_fenceable(काष्ठा i915_vma *vma);
व्योम i915_vma_revoke_mmap(काष्ठा i915_vma *vma);
व्योम __i915_vma_evict(काष्ठा i915_vma *vma);
पूर्णांक __i915_vma_unbind(काष्ठा i915_vma *vma);
पूर्णांक __must_check i915_vma_unbind(काष्ठा i915_vma *vma);
व्योम i915_vma_unlink_ctx(काष्ठा i915_vma *vma);
व्योम i915_vma_बंद(काष्ठा i915_vma *vma);
व्योम i915_vma_reखोलो(काष्ठा i915_vma *vma);

अटल अंतरभूत काष्ठा i915_vma *__i915_vma_get(काष्ठा i915_vma *vma)
अणु
	अगर (kref_get_unless_zero(&vma->ref))
		वापस vma;

	वापस शून्य;
पूर्ण

व्योम i915_vma_release(काष्ठा kref *ref);
अटल अंतरभूत व्योम __i915_vma_put(काष्ठा i915_vma *vma)
अणु
	kref_put(&vma->ref, i915_vma_release);
पूर्ण

#घोषणा निश्चित_vma_held(vma) dma_resv_निश्चित_held((vma)->resv)

अटल अंतरभूत व्योम i915_vma_lock(काष्ठा i915_vma *vma)
अणु
	dma_resv_lock(vma->resv, शून्य);
पूर्ण

अटल अंतरभूत व्योम i915_vma_unlock(काष्ठा i915_vma *vma)
अणु
	dma_resv_unlock(vma->resv);
पूर्ण

पूर्णांक __must_check
i915_vma_pin_ww(काष्ठा i915_vma *vma, काष्ठा i915_gem_ww_ctx *ww,
		u64 size, u64 alignment, u64 flags);

अटल अंतरभूत पूर्णांक __must_check
i915_vma_pin(काष्ठा i915_vma *vma, u64 size, u64 alignment, u64 flags)
अणु
	काष्ठा i915_gem_ww_ctx ww;
	पूर्णांक err;

	i915_gem_ww_ctx_init(&ww, true);
retry:
	err = i915_gem_object_lock(vma->obj, &ww);
	अगर (!err)
		err = i915_vma_pin_ww(vma, &ww, size, alignment, flags);
	अगर (err == -EDEADLK) अणु
		err = i915_gem_ww_ctx_backoff(&ww);
		अगर (!err)
			जाओ retry;
	पूर्ण
	i915_gem_ww_ctx_fini(&ww);

	वापस err;
पूर्ण

पूर्णांक i915_ggtt_pin(काष्ठा i915_vma *vma, काष्ठा i915_gem_ww_ctx *ww,
		  u32 align, अचिन्हित पूर्णांक flags);

अटल अंतरभूत पूर्णांक i915_vma_pin_count(स्थिर काष्ठा i915_vma *vma)
अणु
	वापस atomic_पढ़ो(&vma->flags) & I915_VMA_PIN_MASK;
पूर्ण

अटल अंतरभूत bool i915_vma_is_pinned(स्थिर काष्ठा i915_vma *vma)
अणु
	वापस i915_vma_pin_count(vma);
पूर्ण

अटल अंतरभूत व्योम __i915_vma_pin(काष्ठा i915_vma *vma)
अणु
	atomic_inc(&vma->flags);
	GEM_BUG_ON(!i915_vma_is_pinned(vma));
पूर्ण

अटल अंतरभूत व्योम __i915_vma_unpin(काष्ठा i915_vma *vma)
अणु
	GEM_BUG_ON(!i915_vma_is_pinned(vma));
	atomic_dec(&vma->flags);
पूर्ण

अटल अंतरभूत व्योम i915_vma_unpin(काष्ठा i915_vma *vma)
अणु
	GEM_BUG_ON(!drm_mm_node_allocated(&vma->node));
	__i915_vma_unpin(vma);
पूर्ण

अटल अंतरभूत bool i915_vma_is_bound(स्थिर काष्ठा i915_vma *vma,
				     अचिन्हित पूर्णांक where)
अणु
	वापस atomic_पढ़ो(&vma->flags) & where;
पूर्ण

अटल अंतरभूत bool i915_node_color_dअगरfers(स्थिर काष्ठा drm_mm_node *node,
					   अचिन्हित दीर्घ color)
अणु
	वापस drm_mm_node_allocated(node) && node->color != color;
पूर्ण

/**
 * i915_vma_pin_iomap - calls ioremap_wc to map the GGTT VMA via the aperture
 * @vma: VMA to iomap
 *
 * The passed in VMA has to be pinned in the global GTT mappable region.
 * An extra pinning of the VMA is acquired क्रम the वापस iomapping,
 * the caller must call i915_vma_unpin_iomap to relinquish the pinning
 * after the iomapping is no दीर्घer required.
 *
 * Returns a valid iomapped poपूर्णांकer or ERR_PTR.
 */
व्योम __iomem *i915_vma_pin_iomap(काष्ठा i915_vma *vma);
#घोषणा IO_ERR_PTR(x) ((व्योम __iomem *)ERR_PTR(x))

/**
 * i915_vma_unpin_iomap - unpins the mapping वापसed from i915_vma_iomap
 * @vma: VMA to unpin
 *
 * Unpins the previously iomapped VMA from i915_vma_pin_iomap().
 *
 * This function is only valid to be called on a VMA previously
 * iomapped by the caller with i915_vma_pin_iomap().
 */
व्योम i915_vma_unpin_iomap(काष्ठा i915_vma *vma);

अटल अंतरभूत काष्ठा page *i915_vma_first_page(काष्ठा i915_vma *vma)
अणु
	GEM_BUG_ON(!vma->pages);
	वापस sg_page(vma->pages->sgl);
पूर्ण

/**
 * i915_vma_pin_fence - pin fencing state
 * @vma: vma to pin fencing क्रम
 *
 * This pins the fencing state (whether tiled or untiled) to make sure the
 * vma (and its object) is पढ़ोy to be used as a scanout target. Fencing
 * status must be synchronize first by calling i915_vma_get_fence():
 *
 * The resulting fence pin reference must be released again with
 * i915_vma_unpin_fence().
 *
 * Returns:
 *
 * True अगर the vma has a fence, false otherwise.
 */
पूर्णांक __must_check i915_vma_pin_fence(काष्ठा i915_vma *vma);
व्योम i915_vma_revoke_fence(काष्ठा i915_vma *vma);

पूर्णांक __i915_vma_pin_fence(काष्ठा i915_vma *vma);

अटल अंतरभूत व्योम __i915_vma_unpin_fence(काष्ठा i915_vma *vma)
अणु
	GEM_BUG_ON(atomic_पढ़ो(&vma->fence->pin_count) <= 0);
	atomic_dec(&vma->fence->pin_count);
पूर्ण

/**
 * i915_vma_unpin_fence - unpin fencing state
 * @vma: vma to unpin fencing क्रम
 *
 * This releases the fence pin reference acquired through
 * i915_vma_pin_fence. It will handle both objects with and without an
 * attached fence correctly, callers करो not need to distinguish this.
 */
अटल अंतरभूत व्योम
i915_vma_unpin_fence(काष्ठा i915_vma *vma)
अणु
	अगर (vma->fence)
		__i915_vma_unpin_fence(vma);
पूर्ण

व्योम i915_vma_parked(काष्ठा पूर्णांकel_gt *gt);

अटल अंतरभूत bool i915_vma_is_scanout(स्थिर काष्ठा i915_vma *vma)
अणु
	वापस test_bit(I915_VMA_SCANOUT_BIT, __i915_vma_flags(vma));
पूर्ण

अटल अंतरभूत व्योम i915_vma_mark_scanout(काष्ठा i915_vma *vma)
अणु
	set_bit(I915_VMA_SCANOUT_BIT, __i915_vma_flags(vma));
पूर्ण

अटल अंतरभूत व्योम i915_vma_clear_scanout(काष्ठा i915_vma *vma)
अणु
	clear_bit(I915_VMA_SCANOUT_BIT, __i915_vma_flags(vma));
पूर्ण

#घोषणा क्रम_each_until(cond) अगर (cond) अवरोध; अन्यथा

/**
 * क्रम_each_ggtt_vma - Iterate over the GGTT VMA beदीर्घing to an object.
 * @V: the #i915_vma iterator
 * @OBJ: the #drm_i915_gem_object
 *
 * GGTT VMA are placed at the being of the object's vma_list, see
 * vma_create(), so we can stop our walk as soon as we see a ppgtt VMA,
 * or the list is empty ofc.
 */
#घोषणा क्रम_each_ggtt_vma(V, OBJ) \
	list_क्रम_each_entry(V, &(OBJ)->vma.list, obj_link)		\
		क्रम_each_until(!i915_vma_is_ggtt(V))

काष्ठा i915_vma *i915_vma_alloc(व्योम);
व्योम i915_vma_मुक्त(काष्ठा i915_vma *vma);

काष्ठा i915_vma *i915_vma_make_unshrinkable(काष्ठा i915_vma *vma);
व्योम i915_vma_make_shrinkable(काष्ठा i915_vma *vma);
व्योम i915_vma_make_purgeable(काष्ठा i915_vma *vma);

पूर्णांक i915_vma_रुको_क्रम_bind(काष्ठा i915_vma *vma);

अटल अंतरभूत पूर्णांक i915_vma_sync(काष्ठा i915_vma *vma)
अणु
	/* Wait क्रम the asynchronous bindings and pending GPU पढ़ोs */
	वापस i915_active_रुको(&vma->active);
पूर्ण

#पूर्ण_अगर
