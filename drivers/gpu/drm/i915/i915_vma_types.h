<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
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

#अगर_अघोषित __I915_VMA_TYPES_H__
#घोषणा __I915_VMA_TYPES_H__

#समावेश <linux/rbtree.h>

#समावेश <drm/drm_mm.h>

#समावेश "gem/i915_gem_object_types.h"

क्रमागत i915_cache_level;

/**
 * DOC: Global GTT views
 *
 * Background and previous state
 *
 * Historically objects could exists (be bound) in global GTT space only as
 * singular instances with a view representing all of the object's backing pages
 * in a linear fashion. This view will be called a normal view.
 *
 * To support multiple views of the same object, where the number of mapped
 * pages is not equal to the backing store, or where the layout of the pages
 * is not linear, concept of a GGTT view was added.
 *
 * One example of an alternative view is a stereo display driven by a single
 * image. In this हाल we would have a framebuffer looking like this
 * (2x2 pages):
 *
 *    12
 *    34
 *
 * Above would represent a normal GGTT view as normally mapped क्रम GPU or CPU
 * rendering. In contrast, fed to the display engine would be an alternative
 * view which could look something like this:
 *
 *   1212
 *   3434
 *
 * In this example both the size and layout of pages in the alternative view is
 * dअगरferent from the normal view.
 *
 * Implementation and usage
 *
 * GGTT views are implemented using VMAs and are distinguished via क्रमागत
 * i915_ggtt_view_type and काष्ठा i915_ggtt_view.
 *
 * A new flavour of core GEM functions which work with GGTT bound objects were
 * added with the _ggtt_ infix, and someबार with _view postfix to aव्योम
 * renaming  in large amounts of code. They take the काष्ठा i915_ggtt_view
 * parameter encapsulating all metadata required to implement a view.
 *
 * As a helper क्रम callers which are only पूर्णांकerested in the normal view,
 * globally स्थिर i915_ggtt_view_normal singleton instance exists. All old core
 * GEM API functions, the ones not taking the view parameter, are operating on,
 * or with the normal GGTT view.
 *
 * Code wanting to add or use a new GGTT view needs to:
 *
 * 1. Add a new क्रमागत with a suitable name.
 * 2. Extend the metadata in the i915_ggtt_view काष्ठाure अगर required.
 * 3. Add support to i915_get_vma_pages().
 *
 * New views are required to build a scatter-gather table from within the
 * i915_get_vma_pages function. This table is stored in the vma.ggtt_view and
 * exists क्रम the lअगरeसमय of an VMA.
 *
 * Core API is deचिन्हित to have copy semantics which means that passed in
 * काष्ठा i915_ggtt_view करोes not need to be persistent (left around after
 * calling the core API functions).
 *
 */

काष्ठा पूर्णांकel_remapped_plane_info अणु
	/* in gtt pages */
	u32 offset;
	u16 width;
	u16 height;
	u16 src_stride;
	u16 dst_stride;
पूर्ण __packed;

काष्ठा पूर्णांकel_remapped_info अणु
	काष्ठा पूर्णांकel_remapped_plane_info plane[2];
	u32 unused_mbz;
पूर्ण __packed;

काष्ठा पूर्णांकel_rotation_info अणु
	काष्ठा पूर्णांकel_remapped_plane_info plane[2];
पूर्ण __packed;

काष्ठा पूर्णांकel_partial_info अणु
	u64 offset;
	अचिन्हित पूर्णांक size;
पूर्ण __packed;

क्रमागत i915_ggtt_view_type अणु
	I915_GGTT_VIEW_NORMAL = 0,
	I915_GGTT_VIEW_ROTATED = माप(काष्ठा पूर्णांकel_rotation_info),
	I915_GGTT_VIEW_PARTIAL = माप(काष्ठा पूर्णांकel_partial_info),
	I915_GGTT_VIEW_REMAPPED = माप(काष्ठा पूर्णांकel_remapped_info),
पूर्ण;

अटल अंतरभूत व्योम निश्चित_i915_gem_gtt_types(व्योम)
अणु
	BUILD_BUG_ON(माप(काष्ठा पूर्णांकel_rotation_info) != 2 * माप(u32) + 8 * माप(u16));
	BUILD_BUG_ON(माप(काष्ठा पूर्णांकel_partial_info) != माप(u64) + माप(अचिन्हित पूर्णांक));
	BUILD_BUG_ON(माप(काष्ठा पूर्णांकel_remapped_info) != 3 * माप(u32) + 8 * माप(u16));

	/* Check that rotation/remapped shares offsets क्रम simplicity */
	BUILD_BUG_ON(दुरत्व(काष्ठा पूर्णांकel_remapped_info, plane[0]) !=
		     दुरत्व(काष्ठा पूर्णांकel_rotation_info, plane[0]));
	BUILD_BUG_ON(दुरत्वend(काष्ठा पूर्णांकel_remapped_info, plane[1]) !=
		     दुरत्वend(काष्ठा पूर्णांकel_rotation_info, plane[1]));

	/* As we encode the size of each branch inside the जोड़ पूर्णांकo its type,
	 * we have to be careful that each branch has a unique size.
	 */
	चयन ((क्रमागत i915_ggtt_view_type)0) अणु
	हाल I915_GGTT_VIEW_NORMAL:
	हाल I915_GGTT_VIEW_PARTIAL:
	हाल I915_GGTT_VIEW_ROTATED:
	हाल I915_GGTT_VIEW_REMAPPED:
		/* gcc complains अगर these are identical हालs */
		अवरोध;
	पूर्ण
पूर्ण

काष्ठा i915_ggtt_view अणु
	क्रमागत i915_ggtt_view_type type;
	जोड़ अणु
		/* Members need to contain no holes/padding */
		काष्ठा पूर्णांकel_partial_info partial;
		काष्ठा पूर्णांकel_rotation_info rotated;
		काष्ठा पूर्णांकel_remapped_info remapped;
	पूर्ण;
पूर्ण;

/**
 * DOC: Virtual Memory Address
 *
 * A VMA represents a GEM BO that is bound पूर्णांकo an address space. Thereक्रमe, a
 * VMA's presence cannot be guaranteed beक्रमe binding, or after unbinding the
 * object पूर्णांकo/from the address space.
 *
 * To make things as simple as possible (ie. no refcounting), a VMA's lअगरeसमय
 * will always be <= an objects lअगरeसमय. So object refcounting should cover us.
 */
काष्ठा i915_vma अणु
	काष्ठा drm_mm_node node;

	काष्ठा i915_address_space *vm;
	स्थिर काष्ठा i915_vma_ops *ops;

	काष्ठा drm_i915_gem_object *obj;
	काष्ठा dma_resv *resv; /** Alias of obj->resv */

	काष्ठा sg_table *pages;
	व्योम __iomem *iomap;
	व्योम *निजी; /* owned by creator */

	काष्ठा i915_fence_reg *fence;

	u64 size;
	u64 display_alignment;
	काष्ठा i915_page_sizes page_sizes;

	/* mmap-offset associated with fencing क्रम this vma */
	काष्ठा i915_mmap_offset	*mmo;

	u32 fence_size;
	u32 fence_alignment;

	/**
	 * Count of the number of बार this vma has been खोलोed by dअगरferent
	 * handles (but same file) क्रम execbuf, i.e. the number of aliases
	 * that exist in the ctx->handle_vmas LUT क्रम this vma.
	 */
	काष्ठा kref ref;
	atomic_t खोलो_count;
	atomic_t flags;
	/**
	 * How many users have pinned this object in GTT space.
	 *
	 * This is a tightly bound, fairly small number of users, so we
	 * stuff inside the flags field so that we can both check क्रम overflow
	 * and detect a no-op i915_vma_pin() in a single check, जबतक also
	 * pinning the vma.
	 *
	 * The worst हाल display setup would have the same vma pinned क्रम
	 * use on each plane on each crtc, जबतक also building the next atomic
	 * state and holding a pin क्रम the length of the cleanup queue. In the
	 * future, the flip queue may be increased from 1.
	 * Estimated worst हाल: 3 [qlen] * 4 [max crtcs] * 7 [max planes] = 84
	 *
	 * For GEM, the number of concurrent users क्रम pग_लिखो/pपढ़ो is
	 * unbounded. For execbuffer, it is currently one but will in future
	 * be extended to allow multiple clients to pin vma concurrently.
	 *
	 * We also use suballocated pages, with each suballocation claiming
	 * its own pin on the shared vma. At present, this is limited to
	 * exclusive cachelines of a single page, so a maximum of 64 possible
	 * users.
	 */
#घोषणा I915_VMA_PIN_MASK 0x3ff
#घोषणा I915_VMA_OVERFLOW 0x200

	/** Flags and address space this VMA is bound to */
#घोषणा I915_VMA_GLOBAL_BIND_BIT 10
#घोषणा I915_VMA_LOCAL_BIND_BIT  11

#घोषणा I915_VMA_GLOBAL_BIND	((पूर्णांक)BIT(I915_VMA_GLOBAL_BIND_BIT))
#घोषणा I915_VMA_LOCAL_BIND	((पूर्णांक)BIT(I915_VMA_LOCAL_BIND_BIT))

#घोषणा I915_VMA_BIND_MASK (I915_VMA_GLOBAL_BIND | I915_VMA_LOCAL_BIND)

#घोषणा I915_VMA_ALLOC_BIT	12

#घोषणा I915_VMA_ERROR_BIT	13
#घोषणा I915_VMA_ERROR		((पूर्णांक)BIT(I915_VMA_ERROR_BIT))

#घोषणा I915_VMA_GGTT_BIT	14
#घोषणा I915_VMA_CAN_FENCE_BIT	15
#घोषणा I915_VMA_USERFAULT_BIT	16
#घोषणा I915_VMA_GGTT_WRITE_BIT	17

#घोषणा I915_VMA_GGTT		((पूर्णांक)BIT(I915_VMA_GGTT_BIT))
#घोषणा I915_VMA_CAN_FENCE	((पूर्णांक)BIT(I915_VMA_CAN_FENCE_BIT))
#घोषणा I915_VMA_USERFAULT	((पूर्णांक)BIT(I915_VMA_USERFAULT_BIT))
#घोषणा I915_VMA_GGTT_WRITE	((पूर्णांक)BIT(I915_VMA_GGTT_WRITE_BIT))

#घोषणा I915_VMA_SCANOUT_BIT	18
#घोषणा I915_VMA_SCANOUT	((पूर्णांक)BIT(I915_VMA_SCANOUT_BIT))

	काष्ठा i915_active active;

#घोषणा I915_VMA_PAGES_BIAS 24
#घोषणा I915_VMA_PAGES_ACTIVE (BIT(24) | 1)
	atomic_t pages_count; /* number of active binds to the pages */
	काष्ठा mutex pages_mutex; /* protect acquire/release of backing pages */

	/**
	 * Support dअगरferent GGTT views पूर्णांकo the same object.
	 * This means there can be multiple VMA mappings per object and per VM.
	 * i915_ggtt_view_type is used to distinguish between those entries.
	 * The शेष one of zero (I915_GGTT_VIEW_NORMAL) is शेष and also
	 * assumed in GEM functions which take no ggtt view parameter.
	 */
	काष्ठा i915_ggtt_view ggtt_view;

	/** This object's place on the active/inactive lists */
	काष्ठा list_head vm_link;

	काष्ठा list_head obj_link; /* Link in the object's VMA list */
	काष्ठा rb_node obj_node;
	काष्ठा hlist_node obj_hash;

	/** This vma's place in the eviction list */
	काष्ठा list_head evict_link;

	काष्ठा list_head बंदd_link;
पूर्ण;

#पूर्ण_अगर

