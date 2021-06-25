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

#समावेश <linux/prime_numbers.h>

#समावेश "gem/i915_gem_context.h"
#समावेश "gem/selftests/mock_context.h"

#समावेश "i915_scatterlist.h"
#समावेश "i915_selftest.h"

#समावेश "mock_gem_device.h"
#समावेश "mock_gtt.h"

अटल bool निश्चित_vma(काष्ठा i915_vma *vma,
		       काष्ठा drm_i915_gem_object *obj,
		       काष्ठा i915_gem_context *ctx)
अणु
	bool ok = true;

	अगर (vma->vm != rcu_access_poपूर्णांकer(ctx->vm)) अणु
		pr_err("VMA created with wrong VM\n");
		ok = false;
	पूर्ण

	अगर (vma->size != obj->base.size) अणु
		pr_err("VMA created with wrong size, found %llu, expected %zu\n",
		       vma->size, obj->base.size);
		ok = false;
	पूर्ण

	अगर (vma->ggtt_view.type != I915_GGTT_VIEW_NORMAL) अणु
		pr_err("VMA created with wrong type [%d]\n",
		       vma->ggtt_view.type);
		ok = false;
	पूर्ण

	वापस ok;
पूर्ण

अटल काष्ठा i915_vma *
checked_vma_instance(काष्ठा drm_i915_gem_object *obj,
		     काष्ठा i915_address_space *vm,
		     स्थिर काष्ठा i915_ggtt_view *view)
अणु
	काष्ठा i915_vma *vma;
	bool ok = true;

	vma = i915_vma_instance(obj, vm, view);
	अगर (IS_ERR(vma))
		वापस vma;

	/* Manual checks, will be reinक्रमced by i915_vma_compare! */
	अगर (vma->vm != vm) अणु
		pr_err("VMA's vm [%p] does not match request [%p]\n",
		       vma->vm, vm);
		ok = false;
	पूर्ण

	अगर (i915_is_ggtt(vm) != i915_vma_is_ggtt(vma)) अणु
		pr_err("VMA ggtt status [%d] does not match parent [%d]\n",
		       i915_vma_is_ggtt(vma), i915_is_ggtt(vm));
		ok = false;
	पूर्ण

	अगर (i915_vma_compare(vma, vm, view)) अणु
		pr_err("i915_vma_compare failed with create parameters!\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (i915_vma_compare(vma, vma->vm,
			     i915_vma_is_ggtt(vma) ? &vma->ggtt_view : शून्य)) अणु
		pr_err("i915_vma_compare failed with itself\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (!ok) अणु
		pr_err("i915_vma_compare failed to detect the difference!\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस vma;
पूर्ण

अटल पूर्णांक create_vmas(काष्ठा drm_i915_निजी *i915,
		       काष्ठा list_head *objects,
		       काष्ठा list_head *contexts)
अणु
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_gem_context *ctx;
	पूर्णांक pinned;

	list_क्रम_each_entry(obj, objects, st_link) अणु
		क्रम (pinned = 0; pinned <= 1; pinned++) अणु
			list_क्रम_each_entry(ctx, contexts, link) अणु
				काष्ठा i915_address_space *vm;
				काष्ठा i915_vma *vma;
				पूर्णांक err;

				vm = i915_gem_context_get_vm_rcu(ctx);
				vma = checked_vma_instance(obj, vm, शून्य);
				i915_vm_put(vm);
				अगर (IS_ERR(vma))
					वापस PTR_ERR(vma);

				अगर (!निश्चित_vma(vma, obj, ctx)) अणु
					pr_err("VMA lookup/create failed\n");
					वापस -EINVAL;
				पूर्ण

				अगर (!pinned) अणु
					err = i915_vma_pin(vma, 0, 0, PIN_USER);
					अगर (err) अणु
						pr_err("Failed to pin VMA\n");
						वापस err;
					पूर्ण
				पूर्ण अन्यथा अणु
					i915_vma_unpin(vma);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक igt_vma_create(व्योम *arg)
अणु
	काष्ठा i915_ggtt *ggtt = arg;
	काष्ठा drm_i915_निजी *i915 = ggtt->vm.i915;
	काष्ठा drm_i915_gem_object *obj, *on;
	काष्ठा i915_gem_context *ctx, *cn;
	अचिन्हित दीर्घ num_obj, num_ctx;
	अचिन्हित दीर्घ no, nc;
	IGT_TIMEOUT(end_समय);
	LIST_HEAD(contexts);
	LIST_HEAD(objects);
	पूर्णांक err = -ENOMEM;

	/* Exercise creating many vma amonst many objections, checking the
	 * vma creation and lookup routines.
	 */

	no = 0;
	क्रम_each_prime_number(num_obj, अच_दीर्घ_उच्च - 1) अणु
		क्रम (; no < num_obj; no++) अणु
			obj = i915_gem_object_create_पूर्णांकernal(i915, PAGE_SIZE);
			अगर (IS_ERR(obj))
				जाओ out;

			list_add(&obj->st_link, &objects);
		पूर्ण

		nc = 0;
		क्रम_each_prime_number(num_ctx, 2 * BITS_PER_LONG) अणु
			क्रम (; nc < num_ctx; nc++) अणु
				ctx = mock_context(i915, "mock");
				अगर (!ctx)
					जाओ out;

				list_move(&ctx->link, &contexts);
			पूर्ण

			err = create_vmas(i915, &objects, &contexts);
			अगर (err)
				जाओ out;

			अगर (igt_समयout(end_समय,
					"%s timed out: after %lu objects in %lu contexts\n",
					__func__, no, nc))
				जाओ end;
		पूर्ण

		list_क्रम_each_entry_safe(ctx, cn, &contexts, link) अणु
			list_del_init(&ctx->link);
			mock_context_बंद(ctx);
		पूर्ण

		cond_resched();
	पूर्ण

end:
	/* Final pass to lookup all created contexts */
	err = create_vmas(i915, &objects, &contexts);
out:
	list_क्रम_each_entry_safe(ctx, cn, &contexts, link) अणु
		list_del_init(&ctx->link);
		mock_context_बंद(ctx);
	पूर्ण

	list_क्रम_each_entry_safe(obj, on, &objects, st_link)
		i915_gem_object_put(obj);
	वापस err;
पूर्ण

काष्ठा pin_mode अणु
	u64 size;
	u64 flags;
	bool (*निश्चित)(स्थिर काष्ठा i915_vma *,
		       स्थिर काष्ठा pin_mode *mode,
		       पूर्णांक result);
	स्थिर अक्षर *string;
पूर्ण;

अटल bool निश्चित_pin_valid(स्थिर काष्ठा i915_vma *vma,
			     स्थिर काष्ठा pin_mode *mode,
			     पूर्णांक result)
अणु
	अगर (result)
		वापस false;

	अगर (i915_vma_misplaced(vma, mode->size, 0, mode->flags))
		वापस false;

	वापस true;
पूर्ण

__maybe_unused
अटल bool निश्चित_pin_enospc(स्थिर काष्ठा i915_vma *vma,
			      स्थिर काष्ठा pin_mode *mode,
			      पूर्णांक result)
अणु
	वापस result == -ENOSPC;
पूर्ण

__maybe_unused
अटल bool निश्चित_pin_einval(स्थिर काष्ठा i915_vma *vma,
			      स्थिर काष्ठा pin_mode *mode,
			      पूर्णांक result)
अणु
	वापस result == -EINVAL;
पूर्ण

अटल पूर्णांक igt_vma_pin1(व्योम *arg)
अणु
	काष्ठा i915_ggtt *ggtt = arg;
	स्थिर काष्ठा pin_mode modes[] = अणु
#घोषणा VALID(sz, fl) अणु .size = (sz), .flags = (fl), .निश्चित = निश्चित_pin_valid, .string = #sz ", " #fl ", (valid) " पूर्ण
#घोषणा __INVALID(sz, fl, check, eval) अणु .size = (sz), .flags = (fl), .निश्चित = (check), .string = #sz ", " #fl ", (invalid " #eval ")" पूर्ण
#घोषणा INVALID(sz, fl) __INVALID(sz, fl, निश्चित_pin_einval, EINVAL)
#घोषणा NOSPACE(sz, fl) __INVALID(sz, fl, निश्चित_pin_enospc, ENOSPC)
		VALID(0, PIN_GLOBAL),
		VALID(0, PIN_GLOBAL | PIN_MAPPABLE),

		VALID(0, PIN_GLOBAL | PIN_OFFSET_BIAS | 4096),
		VALID(0, PIN_GLOBAL | PIN_OFFSET_BIAS | 8192),
		VALID(0, PIN_GLOBAL | PIN_OFFSET_BIAS | (ggtt->mappable_end - 4096)),
		VALID(0, PIN_GLOBAL | PIN_MAPPABLE | PIN_OFFSET_BIAS | (ggtt->mappable_end - 4096)),
		VALID(0, PIN_GLOBAL | PIN_OFFSET_BIAS | (ggtt->vm.total - 4096)),

		VALID(0, PIN_GLOBAL | PIN_MAPPABLE | PIN_OFFSET_FIXED | (ggtt->mappable_end - 4096)),
		INVALID(0, PIN_GLOBAL | PIN_MAPPABLE | PIN_OFFSET_FIXED | ggtt->mappable_end),
		VALID(0, PIN_GLOBAL | PIN_OFFSET_FIXED | (ggtt->vm.total - 4096)),
		INVALID(0, PIN_GLOBAL | PIN_OFFSET_FIXED | ggtt->vm.total),
		INVALID(0, PIN_GLOBAL | PIN_OFFSET_FIXED | round_करोwn(U64_MAX, PAGE_SIZE)),

		VALID(4096, PIN_GLOBAL),
		VALID(8192, PIN_GLOBAL),
		VALID(ggtt->mappable_end - 4096, PIN_GLOBAL | PIN_MAPPABLE),
		VALID(ggtt->mappable_end, PIN_GLOBAL | PIN_MAPPABLE),
		NOSPACE(ggtt->mappable_end + 4096, PIN_GLOBAL | PIN_MAPPABLE),
		VALID(ggtt->vm.total - 4096, PIN_GLOBAL),
		VALID(ggtt->vm.total, PIN_GLOBAL),
		NOSPACE(ggtt->vm.total + 4096, PIN_GLOBAL),
		NOSPACE(round_करोwn(U64_MAX, PAGE_SIZE), PIN_GLOBAL),
		INVALID(8192, PIN_GLOBAL | PIN_MAPPABLE | PIN_OFFSET_FIXED | (ggtt->mappable_end - 4096)),
		INVALID(8192, PIN_GLOBAL | PIN_OFFSET_FIXED | (ggtt->vm.total - 4096)),
		INVALID(8192, PIN_GLOBAL | PIN_OFFSET_FIXED | (round_करोwn(U64_MAX, PAGE_SIZE) - 4096)),

		VALID(8192, PIN_GLOBAL | PIN_OFFSET_BIAS | (ggtt->mappable_end - 4096)),

#अगर !IS_ENABLED(CONFIG_DRM_I915_DEBUG_GEM)
		/* Misusing BIAS is a programming error (it is not controllable
		 * from userspace) so when debugging is enabled, it explodes.
		 * However, the tests are still quite पूर्णांकeresting क्रम checking
		 * variable start, end and size.
		 */
		NOSPACE(0, PIN_GLOBAL | PIN_MAPPABLE | PIN_OFFSET_BIAS | ggtt->mappable_end),
		NOSPACE(0, PIN_GLOBAL | PIN_OFFSET_BIAS | ggtt->vm.total),
		NOSPACE(8192, PIN_GLOBAL | PIN_MAPPABLE | PIN_OFFSET_BIAS | (ggtt->mappable_end - 4096)),
		NOSPACE(8192, PIN_GLOBAL | PIN_OFFSET_BIAS | (ggtt->vm.total - 4096)),
#पूर्ण_अगर
		अणु पूर्ण,
#अघोषित NOSPACE
#अघोषित INVALID
#अघोषित __INVALID
#अघोषित VALID
	पूर्ण, *m;
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_vma *vma;
	पूर्णांक err = -EINVAL;

	/* Exercise all the weird and wonderful i915_vma_pin requests,
	 * focusing on error handling of boundary conditions.
	 */

	GEM_BUG_ON(!drm_mm_clean(&ggtt->vm.mm));

	obj = i915_gem_object_create_पूर्णांकernal(ggtt->vm.i915, PAGE_SIZE);
	अगर (IS_ERR(obj))
		वापस PTR_ERR(obj);

	vma = checked_vma_instance(obj, &ggtt->vm, शून्य);
	अगर (IS_ERR(vma))
		जाओ out;

	क्रम (m = modes; m->निश्चित; m++) अणु
		err = i915_vma_pin(vma, m->size, 0, m->flags);
		अगर (!m->निश्चित(vma, m, err)) अणु
			pr_err("%s to pin single page into GGTT with mode[%d:%s]: size=%llx flags=%llx, err=%d\n",
			       m->निश्चित == निश्चित_pin_valid ? "Failed" : "Unexpectedly succeeded",
			       (पूर्णांक)(m - modes), m->string, m->size, m->flags,
			       err);
			अगर (!err)
				i915_vma_unpin(vma);
			err = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (!err) अणु
			i915_vma_unpin(vma);
			err = i915_vma_unbind(vma);
			अगर (err) अणु
				pr_err("Failed to unbind single page from GGTT, err=%d\n", err);
				जाओ out;
			पूर्ण
		पूर्ण

		cond_resched();
	पूर्ण

	err = 0;
out:
	i915_gem_object_put(obj);
	वापस err;
पूर्ण

अटल अचिन्हित दीर्घ rotated_index(स्थिर काष्ठा पूर्णांकel_rotation_info *r,
				   अचिन्हित पूर्णांक n,
				   अचिन्हित पूर्णांक x,
				   अचिन्हित पूर्णांक y)
अणु
	वापस (r->plane[n].src_stride * (r->plane[n].height - y - 1) +
		r->plane[n].offset + x);
पूर्ण

अटल काष्ठा scatterlist *
निश्चित_rotated(काष्ठा drm_i915_gem_object *obj,
	       स्थिर काष्ठा पूर्णांकel_rotation_info *r, अचिन्हित पूर्णांक n,
	       काष्ठा scatterlist *sg)
अणु
	अचिन्हित पूर्णांक x, y;

	क्रम (x = 0; x < r->plane[n].width; x++) अणु
		अचिन्हित पूर्णांक left;

		क्रम (y = 0; y < r->plane[n].height; y++) अणु
			अचिन्हित दीर्घ src_idx;
			dma_addr_t src;

			अगर (!sg) अणु
				pr_err("Invalid sg table: too short at plane %d, (%d, %d)!\n",
				       n, x, y);
				वापस ERR_PTR(-EINVAL);
			पूर्ण

			src_idx = rotated_index(r, n, x, y);
			src = i915_gem_object_get_dma_address(obj, src_idx);

			अगर (sg_dma_len(sg) != PAGE_SIZE) अणु
				pr_err("Invalid sg.length, found %d, expected %lu for rotated page (%d, %d) [src index %lu]\n",
				       sg_dma_len(sg), PAGE_SIZE,
				       x, y, src_idx);
				वापस ERR_PTR(-EINVAL);
			पूर्ण

			अगर (sg_dma_address(sg) != src) अणु
				pr_err("Invalid address for rotated page (%d, %d) [src index %lu]\n",
				       x, y, src_idx);
				वापस ERR_PTR(-EINVAL);
			पूर्ण

			sg = sg_next(sg);
		पूर्ण

		left = (r->plane[n].dst_stride - y) * PAGE_SIZE;

		अगर (!left)
			जारी;

		अगर (!sg) अणु
			pr_err("Invalid sg table: too short at plane %d, (%d, %d)!\n",
			       n, x, y);
			वापस ERR_PTR(-EINVAL);
		पूर्ण

		अगर (sg_dma_len(sg) != left) अणु
			pr_err("Invalid sg.length, found %d, expected %u for rotated page (%d, %d)\n",
			       sg_dma_len(sg), left, x, y);
			वापस ERR_PTR(-EINVAL);
		पूर्ण

		अगर (sg_dma_address(sg) != 0) अणु
			pr_err("Invalid address, found %pad, expected 0 for remapped page (%d, %d)\n",
			       &sg_dma_address(sg), x, y);
			वापस ERR_PTR(-EINVAL);
		पूर्ण

		sg = sg_next(sg);
	पूर्ण

	वापस sg;
पूर्ण

अटल अचिन्हित दीर्घ remapped_index(स्थिर काष्ठा पूर्णांकel_remapped_info *r,
				    अचिन्हित पूर्णांक n,
				    अचिन्हित पूर्णांक x,
				    अचिन्हित पूर्णांक y)
अणु
	वापस (r->plane[n].src_stride * y +
		r->plane[n].offset + x);
पूर्ण

अटल काष्ठा scatterlist *
निश्चित_remapped(काष्ठा drm_i915_gem_object *obj,
		स्थिर काष्ठा पूर्णांकel_remapped_info *r, अचिन्हित पूर्णांक n,
		काष्ठा scatterlist *sg)
अणु
	अचिन्हित पूर्णांक x, y;
	अचिन्हित पूर्णांक left = 0;
	अचिन्हित पूर्णांक offset;

	क्रम (y = 0; y < r->plane[n].height; y++) अणु
		क्रम (x = 0; x < r->plane[n].width; x++) अणु
			अचिन्हित दीर्घ src_idx;
			dma_addr_t src;

			अगर (!sg) अणु
				pr_err("Invalid sg table: too short at plane %d, (%d, %d)!\n",
				       n, x, y);
				वापस ERR_PTR(-EINVAL);
			पूर्ण
			अगर (!left) अणु
				offset = 0;
				left = sg_dma_len(sg);
			पूर्ण

			src_idx = remapped_index(r, n, x, y);
			src = i915_gem_object_get_dma_address(obj, src_idx);

			अगर (left < PAGE_SIZE || left & (PAGE_SIZE-1)) अणु
				pr_err("Invalid sg.length, found %d, expected %lu for remapped page (%d, %d) [src index %lu]\n",
				       sg_dma_len(sg), PAGE_SIZE,
				       x, y, src_idx);
				वापस ERR_PTR(-EINVAL);
			पूर्ण

			अगर (sg_dma_address(sg) + offset != src) अणु
				pr_err("Invalid address for remapped page (%d, %d) [src index %lu]\n",
				       x, y, src_idx);
				वापस ERR_PTR(-EINVAL);
			पूर्ण

			left -= PAGE_SIZE;
			offset += PAGE_SIZE;


			अगर (!left)
				sg = sg_next(sg);
		पूर्ण

		अगर (left) अणु
			pr_err("Unexpected sg tail with %d size for remapped page (%d, %d)\n",
			       left,
			       x, y);
			वापस ERR_PTR(-EINVAL);
		पूर्ण

		left = (r->plane[n].dst_stride - r->plane[n].width) * PAGE_SIZE;

		अगर (!left)
			जारी;

		अगर (!sg) अणु
			pr_err("Invalid sg table: too short at plane %d, (%d, %d)!\n",
			       n, x, y);
			वापस ERR_PTR(-EINVAL);
		पूर्ण

		अगर (sg_dma_len(sg) != left) अणु
			pr_err("Invalid sg.length, found %u, expected %u for remapped page (%d, %d)\n",
			       sg_dma_len(sg), left,
			       x, y);
			वापस ERR_PTR(-EINVAL);
		पूर्ण

		अगर (sg_dma_address(sg) != 0) अणु
			pr_err("Invalid address, found %pad, expected 0 for remapped page (%d, %d)\n",
			       &sg_dma_address(sg),
			       x, y);
			वापस ERR_PTR(-EINVAL);
		पूर्ण

		sg = sg_next(sg);
		left = 0;
	पूर्ण

	वापस sg;
पूर्ण

अटल अचिन्हित पूर्णांक remapped_size(क्रमागत i915_ggtt_view_type view_type,
				  स्थिर काष्ठा पूर्णांकel_remapped_plane_info *a,
				  स्थिर काष्ठा पूर्णांकel_remapped_plane_info *b)
अणु

	अगर (view_type == I915_GGTT_VIEW_ROTATED)
		वापस a->dst_stride * a->width + b->dst_stride * b->width;
	अन्यथा
		वापस a->dst_stride * a->height + b->dst_stride * b->height;
पूर्ण

अटल पूर्णांक igt_vma_rotate_remap(व्योम *arg)
अणु
	काष्ठा i915_ggtt *ggtt = arg;
	काष्ठा i915_address_space *vm = &ggtt->vm;
	काष्ठा drm_i915_gem_object *obj;
	स्थिर काष्ठा पूर्णांकel_remapped_plane_info planes[] = अणु
		अणु .width = 1, .height = 1, .src_stride = 1 पूर्ण,
		अणु .width = 2, .height = 2, .src_stride = 2 पूर्ण,
		अणु .width = 4, .height = 4, .src_stride = 4 पूर्ण,
		अणु .width = 8, .height = 8, .src_stride = 8 पूर्ण,

		अणु .width = 3, .height = 5, .src_stride = 3 पूर्ण,
		अणु .width = 3, .height = 5, .src_stride = 4 पूर्ण,
		अणु .width = 3, .height = 5, .src_stride = 5 पूर्ण,

		अणु .width = 5, .height = 3, .src_stride = 5 पूर्ण,
		अणु .width = 5, .height = 3, .src_stride = 7 पूर्ण,
		अणु .width = 5, .height = 3, .src_stride = 9 पूर्ण,

		अणु .width = 4, .height = 6, .src_stride = 6 पूर्ण,
		अणु .width = 6, .height = 4, .src_stride = 6 पूर्ण,

		अणु .width = 2, .height = 2, .src_stride = 2, .dst_stride = 2 पूर्ण,
		अणु .width = 3, .height = 3, .src_stride = 3, .dst_stride = 4 पूर्ण,
		अणु .width = 5, .height = 6, .src_stride = 7, .dst_stride = 8 पूर्ण,

		अणु पूर्ण
	पूर्ण, *a, *b;
	क्रमागत i915_ggtt_view_type types[] = अणु
		I915_GGTT_VIEW_ROTATED,
		I915_GGTT_VIEW_REMAPPED,
		0,
	पूर्ण, *t;
	स्थिर अचिन्हित पूर्णांक max_pages = 64;
	पूर्णांक err = -ENOMEM;

	/* Create VMA क्रम many dअगरferent combinations of planes and check
	 * that the page layout within the rotated VMA match our expectations.
	 */

	obj = i915_gem_object_create_पूर्णांकernal(vm->i915, max_pages * PAGE_SIZE);
	अगर (IS_ERR(obj))
		जाओ out;

	क्रम (t = types; *t; t++) अणु
	क्रम (a = planes; a->width; a++) अणु
		क्रम (b = planes + ARRAY_SIZE(planes); b-- != planes; ) अणु
			काष्ठा i915_ggtt_view view = अणु
				.type = *t,
				.remapped.plane[0] = *a,
				.remapped.plane[1] = *b,
			पूर्ण;
			काष्ठा पूर्णांकel_remapped_plane_info *plane_info = view.remapped.plane;
			अचिन्हित पूर्णांक n, max_offset;

			max_offset = max(plane_info[0].src_stride * plane_info[0].height,
					 plane_info[1].src_stride * plane_info[1].height);
			GEM_BUG_ON(max_offset > max_pages);
			max_offset = max_pages - max_offset;

			अगर (!plane_info[0].dst_stride)
				plane_info[0].dst_stride = view.type == I915_GGTT_VIEW_ROTATED ?
									plane_info[0].height :
									plane_info[0].width;
			अगर (!plane_info[1].dst_stride)
				plane_info[1].dst_stride = view.type == I915_GGTT_VIEW_ROTATED ?
									plane_info[1].height :
									plane_info[1].width;

			क्रम_each_prime_number_from(plane_info[0].offset, 0, max_offset) अणु
				क्रम_each_prime_number_from(plane_info[1].offset, 0, max_offset) अणु
					काष्ठा scatterlist *sg;
					काष्ठा i915_vma *vma;
					अचिन्हित पूर्णांक expected_pages;

					vma = checked_vma_instance(obj, vm, &view);
					अगर (IS_ERR(vma)) अणु
						err = PTR_ERR(vma);
						जाओ out_object;
					पूर्ण

					err = i915_vma_pin(vma, 0, 0, PIN_GLOBAL);
					अगर (err) अणु
						pr_err("Failed to pin VMA, err=%d\n", err);
						जाओ out_object;
					पूर्ण

					expected_pages = remapped_size(view.type, &plane_info[0], &plane_info[1]);

					अगर (view.type == I915_GGTT_VIEW_ROTATED &&
					    vma->size != expected_pages * PAGE_SIZE) अणु
						pr_err("VMA is wrong size, expected %lu, found %llu\n",
						       PAGE_SIZE * expected_pages, vma->size);
						err = -EINVAL;
						जाओ out_object;
					पूर्ण

					अगर (view.type == I915_GGTT_VIEW_REMAPPED &&
					    vma->size > expected_pages * PAGE_SIZE) अणु
						pr_err("VMA is wrong size, expected %lu, found %llu\n",
						       PAGE_SIZE * expected_pages, vma->size);
						err = -EINVAL;
						जाओ out_object;
					पूर्ण

					अगर (vma->pages->nents > expected_pages) अणु
						pr_err("sg table is wrong sizeo, expected %u, found %u nents\n",
						       expected_pages, vma->pages->nents);
						err = -EINVAL;
						जाओ out_object;
					पूर्ण

					अगर (vma->node.size < vma->size) अणु
						pr_err("VMA binding too small, expected %llu, found %llu\n",
						       vma->size, vma->node.size);
						err = -EINVAL;
						जाओ out_object;
					पूर्ण

					अगर (vma->pages == obj->mm.pages) अणु
						pr_err("VMA using unrotated object pages!\n");
						err = -EINVAL;
						जाओ out_object;
					पूर्ण

					sg = vma->pages->sgl;
					क्रम (n = 0; n < ARRAY_SIZE(view.rotated.plane); n++) अणु
						अगर (view.type == I915_GGTT_VIEW_ROTATED)
							sg = निश्चित_rotated(obj, &view.rotated, n, sg);
						अन्यथा
							sg = निश्चित_remapped(obj, &view.remapped, n, sg);
						अगर (IS_ERR(sg)) अणु
							pr_err("Inconsistent %s VMA pages for plane %d: [(%d, %d, %d, %d, %d), (%d, %d, %d, %d, %d)]\n",
							       view.type == I915_GGTT_VIEW_ROTATED ?
							       "rotated" : "remapped", n,
							       plane_info[0].width,
							       plane_info[0].height,
							       plane_info[0].src_stride,
							       plane_info[0].dst_stride,
							       plane_info[0].offset,
							       plane_info[1].width,
							       plane_info[1].height,
							       plane_info[1].src_stride,
							       plane_info[1].dst_stride,
							       plane_info[1].offset);
							err = -EINVAL;
							जाओ out_object;
						पूर्ण
					पूर्ण

					i915_vma_unpin(vma);

					cond_resched();
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	पूर्ण

out_object:
	i915_gem_object_put(obj);
out:
	वापस err;
पूर्ण

अटल bool निश्चित_partial(काष्ठा drm_i915_gem_object *obj,
			   काष्ठा i915_vma *vma,
			   अचिन्हित दीर्घ offset,
			   अचिन्हित दीर्घ size)
अणु
	काष्ठा sgt_iter sgt;
	dma_addr_t dma;

	क्रम_each_sgt_daddr(dma, sgt, vma->pages) अणु
		dma_addr_t src;

		अगर (!size) अणु
			pr_err("Partial scattergather list too long\n");
			वापस false;
		पूर्ण

		src = i915_gem_object_get_dma_address(obj, offset);
		अगर (src != dma) अणु
			pr_err("DMA mismatch for partial page offset %lu\n",
			       offset);
			वापस false;
		पूर्ण

		offset++;
		size--;
	पूर्ण

	वापस true;
पूर्ण

अटल bool निश्चित_pin(काष्ठा i915_vma *vma,
		       काष्ठा i915_ggtt_view *view,
		       u64 size,
		       स्थिर अक्षर *name)
अणु
	bool ok = true;

	अगर (vma->size != size) अणु
		pr_err("(%s) VMA is wrong size, expected %llu, found %llu\n",
		       name, size, vma->size);
		ok = false;
	पूर्ण

	अगर (vma->node.size < vma->size) अणु
		pr_err("(%s) VMA binding too small, expected %llu, found %llu\n",
		       name, vma->size, vma->node.size);
		ok = false;
	पूर्ण

	अगर (view && view->type != I915_GGTT_VIEW_NORMAL) अणु
		अगर (स_भेद(&vma->ggtt_view, view, माप(*view))) अणु
			pr_err("(%s) VMA mismatch upon creation!\n",
			       name);
			ok = false;
		पूर्ण

		अगर (vma->pages == vma->obj->mm.pages) अणु
			pr_err("(%s) VMA using original object pages!\n",
			       name);
			ok = false;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (vma->ggtt_view.type != I915_GGTT_VIEW_NORMAL) अणु
			pr_err("Not the normal ggtt view! Found %d\n",
			       vma->ggtt_view.type);
			ok = false;
		पूर्ण

		अगर (vma->pages != vma->obj->mm.pages) अणु
			pr_err("VMA not using object pages!\n");
			ok = false;
		पूर्ण
	पूर्ण

	वापस ok;
पूर्ण

अटल पूर्णांक igt_vma_partial(व्योम *arg)
अणु
	काष्ठा i915_ggtt *ggtt = arg;
	काष्ठा i915_address_space *vm = &ggtt->vm;
	स्थिर अचिन्हित पूर्णांक npages = 1021; /* prime! */
	काष्ठा drm_i915_gem_object *obj;
	स्थिर काष्ठा phase अणु
		स्थिर अक्षर *name;
	पूर्ण phases[] = अणु
		अणु "create" पूर्ण,
		अणु "lookup" पूर्ण,
		अणु पूर्ण,
	पूर्ण, *p;
	अचिन्हित पूर्णांक sz, offset;
	काष्ठा i915_vma *vma;
	पूर्णांक err = -ENOMEM;

	/* Create lots of dअगरferent VMA क्रम the object and check that
	 * we are वापसed the same VMA when we later request the same range.
	 */

	obj = i915_gem_object_create_पूर्णांकernal(vm->i915, npages * PAGE_SIZE);
	अगर (IS_ERR(obj))
		जाओ out;

	क्रम (p = phases; p->name; p++) अणु /* exercise both create/lookup */
		अचिन्हित पूर्णांक count, nvma;

		nvma = 0;
		क्रम_each_prime_number_from(sz, 1, npages) अणु
			क्रम_each_prime_number_from(offset, 0, npages - sz) अणु
				काष्ठा i915_ggtt_view view;

				view.type = I915_GGTT_VIEW_PARTIAL;
				view.partial.offset = offset;
				view.partial.size = sz;

				अगर (sz == npages)
					view.type = I915_GGTT_VIEW_NORMAL;

				vma = checked_vma_instance(obj, vm, &view);
				अगर (IS_ERR(vma)) अणु
					err = PTR_ERR(vma);
					जाओ out_object;
				पूर्ण

				err = i915_vma_pin(vma, 0, 0, PIN_GLOBAL);
				अगर (err)
					जाओ out_object;

				अगर (!निश्चित_pin(vma, &view, sz*PAGE_SIZE, p->name)) अणु
					pr_err("(%s) Inconsistent partial pinning for (offset=%d, size=%d)\n",
					       p->name, offset, sz);
					err = -EINVAL;
					जाओ out_object;
				पूर्ण

				अगर (!निश्चित_partial(obj, vma, offset, sz)) अणु
					pr_err("(%s) Inconsistent partial pages for (offset=%d, size=%d)\n",
					       p->name, offset, sz);
					err = -EINVAL;
					जाओ out_object;
				पूर्ण

				i915_vma_unpin(vma);
				nvma++;

				cond_resched();
			पूर्ण
		पूर्ण

		count = 0;
		list_क्रम_each_entry(vma, &obj->vma.list, obj_link)
			count++;
		अगर (count != nvma) अणु
			pr_err("(%s) All partial vma were not recorded on the obj->vma_list: found %u, expected %u\n",
			       p->name, count, nvma);
			err = -EINVAL;
			जाओ out_object;
		पूर्ण

		/* Check that we did create the whole object mapping */
		vma = checked_vma_instance(obj, vm, शून्य);
		अगर (IS_ERR(vma)) अणु
			err = PTR_ERR(vma);
			जाओ out_object;
		पूर्ण

		err = i915_vma_pin(vma, 0, 0, PIN_GLOBAL);
		अगर (err)
			जाओ out_object;

		अगर (!निश्चित_pin(vma, शून्य, obj->base.size, p->name)) अणु
			pr_err("(%s) inconsistent full pin\n", p->name);
			err = -EINVAL;
			जाओ out_object;
		पूर्ण

		i915_vma_unpin(vma);

		count = 0;
		list_क्रम_each_entry(vma, &obj->vma.list, obj_link)
			count++;
		अगर (count != nvma) अणु
			pr_err("(%s) allocated an extra full vma!\n", p->name);
			err = -EINVAL;
			जाओ out_object;
		पूर्ण
	पूर्ण

out_object:
	i915_gem_object_put(obj);
out:
	वापस err;
पूर्ण

पूर्णांक i915_vma_mock_selftests(व्योम)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(igt_vma_create),
		SUBTEST(igt_vma_pin1),
		SUBTEST(igt_vma_rotate_remap),
		SUBTEST(igt_vma_partial),
	पूर्ण;
	काष्ठा drm_i915_निजी *i915;
	काष्ठा i915_ggtt *ggtt;
	पूर्णांक err;

	i915 = mock_gem_device();
	अगर (!i915)
		वापस -ENOMEM;

	ggtt = kदो_स्मृति(माप(*ggtt), GFP_KERNEL);
	अगर (!ggtt) अणु
		err = -ENOMEM;
		जाओ out_put;
	पूर्ण
	mock_init_ggtt(i915, ggtt);

	err = i915_subtests(tests, ggtt);

	mock_device_flush(i915);
	i915_gem_drain_मुक्तd_objects(i915);
	mock_fini_ggtt(ggtt);
	kमुक्त(ggtt);
out_put:
	mock_destroy_device(i915);
	वापस err;
पूर्ण

अटल पूर्णांक igt_vma_remapped_gtt(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	स्थिर काष्ठा पूर्णांकel_remapped_plane_info planes[] = अणु
		अणु .width = 1, .height = 1, .src_stride = 1 पूर्ण,
		अणु .width = 2, .height = 2, .src_stride = 2 पूर्ण,
		अणु .width = 4, .height = 4, .src_stride = 4 पूर्ण,
		अणु .width = 8, .height = 8, .src_stride = 8 पूर्ण,

		अणु .width = 3, .height = 5, .src_stride = 3 पूर्ण,
		अणु .width = 3, .height = 5, .src_stride = 4 पूर्ण,
		अणु .width = 3, .height = 5, .src_stride = 5 पूर्ण,

		अणु .width = 5, .height = 3, .src_stride = 5 पूर्ण,
		अणु .width = 5, .height = 3, .src_stride = 7 पूर्ण,
		अणु .width = 5, .height = 3, .src_stride = 9 पूर्ण,

		अणु .width = 4, .height = 6, .src_stride = 6 पूर्ण,
		अणु .width = 6, .height = 4, .src_stride = 6 पूर्ण,

		अणु .width = 2, .height = 2, .src_stride = 2, .dst_stride = 2 पूर्ण,
		अणु .width = 3, .height = 3, .src_stride = 3, .dst_stride = 4 पूर्ण,
		अणु .width = 5, .height = 6, .src_stride = 7, .dst_stride = 8 पूर्ण,

		अणु पूर्ण
	पूर्ण, *p;
	क्रमागत i915_ggtt_view_type types[] = अणु
		I915_GGTT_VIEW_ROTATED,
		I915_GGTT_VIEW_REMAPPED,
		0,
	पूर्ण, *t;
	काष्ठा drm_i915_gem_object *obj;
	पूर्णांकel_wakeref_t wakeref;
	पूर्णांक err = 0;

	obj = i915_gem_object_create_पूर्णांकernal(i915, 10 * 10 * PAGE_SIZE);
	अगर (IS_ERR(obj))
		वापस PTR_ERR(obj);

	wakeref = पूर्णांकel_runसमय_pm_get(&i915->runसमय_pm);

	क्रम (t = types; *t; t++) अणु
		क्रम (p = planes; p->width; p++) अणु
			काष्ठा i915_ggtt_view view = अणु
				.type = *t,
				.rotated.plane[0] = *p,
			पूर्ण;
			काष्ठा पूर्णांकel_remapped_plane_info *plane_info = view.rotated.plane;
			काष्ठा i915_vma *vma;
			u32 __iomem *map;
			अचिन्हित पूर्णांक x, y;

			i915_gem_object_lock(obj, शून्य);
			err = i915_gem_object_set_to_gtt_करोमुख्य(obj, true);
			i915_gem_object_unlock(obj);
			अगर (err)
				जाओ out;

			अगर (!plane_info[0].dst_stride)
				plane_info[0].dst_stride = *t == I915_GGTT_VIEW_ROTATED ?
								 p->height : p->width;

			vma = i915_gem_object_ggtt_pin(obj, &view, 0, 0, PIN_MAPPABLE);
			अगर (IS_ERR(vma)) अणु
				err = PTR_ERR(vma);
				जाओ out;
			पूर्ण

			GEM_BUG_ON(vma->ggtt_view.type != *t);

			map = i915_vma_pin_iomap(vma);
			i915_vma_unpin(vma);
			अगर (IS_ERR(map)) अणु
				err = PTR_ERR(map);
				जाओ out;
			पूर्ण

			क्रम (y = 0 ; y < plane_info[0].height; y++) अणु
				क्रम (x = 0 ; x < plane_info[0].width; x++) अणु
					अचिन्हित पूर्णांक offset;
					u32 val = y << 16 | x;

					अगर (*t == I915_GGTT_VIEW_ROTATED)
						offset = (x * plane_info[0].dst_stride + y) * PAGE_SIZE;
					अन्यथा
						offset = (y * plane_info[0].dst_stride + x) * PAGE_SIZE;

					ioग_लिखो32(val, &map[offset / माप(*map)]);
				पूर्ण
			पूर्ण

			i915_vma_unpin_iomap(vma);

			vma = i915_gem_object_ggtt_pin(obj, शून्य, 0, 0, PIN_MAPPABLE);
			अगर (IS_ERR(vma)) अणु
				err = PTR_ERR(vma);
				जाओ out;
			पूर्ण

			GEM_BUG_ON(vma->ggtt_view.type != I915_GGTT_VIEW_NORMAL);

			map = i915_vma_pin_iomap(vma);
			i915_vma_unpin(vma);
			अगर (IS_ERR(map)) अणु
				err = PTR_ERR(map);
				जाओ out;
			पूर्ण

			क्रम (y = 0 ; y < plane_info[0].height; y++) अणु
				क्रम (x = 0 ; x < plane_info[0].width; x++) अणु
					अचिन्हित पूर्णांक offset, src_idx;
					u32 exp = y << 16 | x;
					u32 val;

					अगर (*t == I915_GGTT_VIEW_ROTATED)
						src_idx = rotated_index(&view.rotated, 0, x, y);
					अन्यथा
						src_idx = remapped_index(&view.remapped, 0, x, y);
					offset = src_idx * PAGE_SIZE;

					val = ioपढ़ो32(&map[offset / माप(*map)]);
					अगर (val != exp) अणु
						pr_err("%s VMA write test failed, expected 0x%x, found 0x%x\n",
						       *t == I915_GGTT_VIEW_ROTATED ? "Rotated" : "Remapped",
						       exp, val);
						i915_vma_unpin_iomap(vma);
						err = -EINVAL;
						जाओ out;
					पूर्ण
				पूर्ण
			पूर्ण
			i915_vma_unpin_iomap(vma);

			cond_resched();
		पूर्ण
	पूर्ण

out:
	पूर्णांकel_runसमय_pm_put(&i915->runसमय_pm, wakeref);
	i915_gem_object_put(obj);

	वापस err;
पूर्ण

पूर्णांक i915_vma_live_selftests(काष्ठा drm_i915_निजी *i915)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(igt_vma_remapped_gtt),
	पूर्ण;

	वापस i915_subtests(tests, i915);
पूर्ण
