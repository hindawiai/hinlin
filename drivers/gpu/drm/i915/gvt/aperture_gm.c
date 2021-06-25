<शैली गुरु>
/*
 * Copyright(c) 2011-2016 Intel Corporation. All rights reserved.
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
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Authors:
 *    Kevin Tian <kevin.tian@पूर्णांकel.com>
 *    Dexuan Cui
 *
 * Contributors:
 *    Pei Zhang <pei.zhang@पूर्णांकel.com>
 *    Min He <min.he@पूर्णांकel.com>
 *    Niu Bing <bing.niu@पूर्णांकel.com>
 *    Yulei Zhang <yulei.zhang@पूर्णांकel.com>
 *    Zhenyu Wang <zhenyuw@linux.पूर्णांकel.com>
 *    Zhi Wang <zhi.a.wang@पूर्णांकel.com>
 *
 */

#समावेश "i915_drv.h"
#समावेश "gt/intel_ggtt_fencing.h"
#समावेश "gvt.h"

अटल पूर्णांक alloc_gm(काष्ठा पूर्णांकel_vgpu *vgpu, bool high_gm)
अणु
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	काष्ठा पूर्णांकel_gt *gt = gvt->gt;
	अचिन्हित पूर्णांक flags;
	u64 start, end, size;
	काष्ठा drm_mm_node *node;
	पूर्णांक ret;

	अगर (high_gm) अणु
		node = &vgpu->gm.high_gm_node;
		size = vgpu_hidden_sz(vgpu);
		start = ALIGN(gvt_hidden_gmadr_base(gvt), I915_GTT_PAGE_SIZE);
		end = ALIGN(gvt_hidden_gmadr_end(gvt), I915_GTT_PAGE_SIZE);
		flags = PIN_HIGH;
	पूर्ण अन्यथा अणु
		node = &vgpu->gm.low_gm_node;
		size = vgpu_aperture_sz(vgpu);
		start = ALIGN(gvt_aperture_gmadr_base(gvt), I915_GTT_PAGE_SIZE);
		end = ALIGN(gvt_aperture_gmadr_end(gvt), I915_GTT_PAGE_SIZE);
		flags = PIN_MAPPABLE;
	पूर्ण

	mutex_lock(&gt->ggtt->vm.mutex);
	mmio_hw_access_pre(gt);
	ret = i915_gem_gtt_insert(&gt->ggtt->vm, node,
				  size, I915_GTT_PAGE_SIZE,
				  I915_COLOR_UNEVICTABLE,
				  start, end, flags);
	mmio_hw_access_post(gt);
	mutex_unlock(&gt->ggtt->vm.mutex);
	अगर (ret)
		gvt_err("fail to alloc %s gm space from host\n",
			high_gm ? "high" : "low");

	वापस ret;
पूर्ण

अटल पूर्णांक alloc_vgpu_gm(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	काष्ठा पूर्णांकel_gt *gt = gvt->gt;
	पूर्णांक ret;

	ret = alloc_gm(vgpu, false);
	अगर (ret)
		वापस ret;

	ret = alloc_gm(vgpu, true);
	अगर (ret)
		जाओ out_मुक्त_aperture;

	gvt_dbg_core("vgpu%d: alloc low GM start %llx size %llx\n", vgpu->id,
		     vgpu_aperture_offset(vgpu), vgpu_aperture_sz(vgpu));

	gvt_dbg_core("vgpu%d: alloc high GM start %llx size %llx\n", vgpu->id,
		     vgpu_hidden_offset(vgpu), vgpu_hidden_sz(vgpu));

	वापस 0;
out_मुक्त_aperture:
	mutex_lock(&gt->ggtt->vm.mutex);
	drm_mm_हटाओ_node(&vgpu->gm.low_gm_node);
	mutex_unlock(&gt->ggtt->vm.mutex);
	वापस ret;
पूर्ण

अटल व्योम मुक्त_vgpu_gm(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	काष्ठा पूर्णांकel_gt *gt = gvt->gt;

	mutex_lock(&gt->ggtt->vm.mutex);
	drm_mm_हटाओ_node(&vgpu->gm.low_gm_node);
	drm_mm_हटाओ_node(&vgpu->gm.high_gm_node);
	mutex_unlock(&gt->ggtt->vm.mutex);
पूर्ण

/**
 * पूर्णांकel_vgpu_ग_लिखो_fence - ग_लिखो fence रेजिस्टरs owned by a vGPU
 * @vgpu: vGPU instance
 * @fence: vGPU fence रेजिस्टर number
 * @value: Fence रेजिस्टर value to be written
 *
 * This function is used to ग_लिखो fence रेजिस्टरs owned by a vGPU. The vGPU
 * fence रेजिस्टर number will be translated पूर्णांकo HW fence रेजिस्टर number.
 *
 */
व्योम पूर्णांकel_vgpu_ग_लिखो_fence(काष्ठा पूर्णांकel_vgpu *vgpu,
		u32 fence, u64 value)
अणु
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	काष्ठा drm_i915_निजी *i915 = gvt->gt->i915;
	काष्ठा पूर्णांकel_uncore *uncore = gvt->gt->uncore;
	काष्ठा i915_fence_reg *reg;
	i915_reg_t fence_reg_lo, fence_reg_hi;

	निश्चित_rpm_wakelock_held(uncore->rpm);

	अगर (drm_WARN_ON(&i915->drm, fence >= vgpu_fence_sz(vgpu)))
		वापस;

	reg = vgpu->fence.regs[fence];
	अगर (drm_WARN_ON(&i915->drm, !reg))
		वापस;

	fence_reg_lo = FENCE_REG_GEN6_LO(reg->id);
	fence_reg_hi = FENCE_REG_GEN6_HI(reg->id);

	पूर्णांकel_uncore_ग_लिखो(uncore, fence_reg_lo, 0);
	पूर्णांकel_uncore_posting_पढ़ो(uncore, fence_reg_lo);

	पूर्णांकel_uncore_ग_लिखो(uncore, fence_reg_hi, upper_32_bits(value));
	पूर्णांकel_uncore_ग_लिखो(uncore, fence_reg_lo, lower_32_bits(value));
	पूर्णांकel_uncore_posting_पढ़ो(uncore, fence_reg_lo);
पूर्ण

अटल व्योम _clear_vgpu_fence(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < vgpu_fence_sz(vgpu); i++)
		पूर्णांकel_vgpu_ग_लिखो_fence(vgpu, i, 0);
पूर्ण

अटल व्योम मुक्त_vgpu_fence(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	काष्ठा पूर्णांकel_uncore *uncore = gvt->gt->uncore;
	काष्ठा i915_fence_reg *reg;
	पूर्णांकel_wakeref_t wakeref;
	u32 i;

	अगर (drm_WARN_ON(&gvt->gt->i915->drm, !vgpu_fence_sz(vgpu)))
		वापस;

	wakeref = पूर्णांकel_runसमय_pm_get(uncore->rpm);

	mutex_lock(&gvt->gt->ggtt->vm.mutex);
	_clear_vgpu_fence(vgpu);
	क्रम (i = 0; i < vgpu_fence_sz(vgpu); i++) अणु
		reg = vgpu->fence.regs[i];
		i915_unreserve_fence(reg);
		vgpu->fence.regs[i] = शून्य;
	पूर्ण
	mutex_unlock(&gvt->gt->ggtt->vm.mutex);

	पूर्णांकel_runसमय_pm_put(uncore->rpm, wakeref);
पूर्ण

अटल पूर्णांक alloc_vgpu_fence(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	काष्ठा पूर्णांकel_uncore *uncore = gvt->gt->uncore;
	काष्ठा i915_fence_reg *reg;
	पूर्णांकel_wakeref_t wakeref;
	पूर्णांक i;

	wakeref = पूर्णांकel_runसमय_pm_get(uncore->rpm);

	/* Request fences from host */
	mutex_lock(&gvt->gt->ggtt->vm.mutex);

	क्रम (i = 0; i < vgpu_fence_sz(vgpu); i++) अणु
		reg = i915_reserve_fence(gvt->gt->ggtt);
		अगर (IS_ERR(reg))
			जाओ out_मुक्त_fence;

		vgpu->fence.regs[i] = reg;
	पूर्ण

	_clear_vgpu_fence(vgpu);

	mutex_unlock(&gvt->gt->ggtt->vm.mutex);
	पूर्णांकel_runसमय_pm_put(uncore->rpm, wakeref);
	वापस 0;

out_मुक्त_fence:
	gvt_vgpu_err("Failed to alloc fences\n");
	/* Return fences to host, अगर fail */
	क्रम (i = 0; i < vgpu_fence_sz(vgpu); i++) अणु
		reg = vgpu->fence.regs[i];
		अगर (!reg)
			जारी;
		i915_unreserve_fence(reg);
		vgpu->fence.regs[i] = शून्य;
	पूर्ण
	mutex_unlock(&gvt->gt->ggtt->vm.mutex);
	पूर्णांकel_runसमय_pm_put_unchecked(uncore->rpm);
	वापस -ENOSPC;
पूर्ण

अटल व्योम मुक्त_resource(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;

	gvt->gm.vgpu_allocated_low_gm_size -= vgpu_aperture_sz(vgpu);
	gvt->gm.vgpu_allocated_high_gm_size -= vgpu_hidden_sz(vgpu);
	gvt->fence.vgpu_allocated_fence_num -= vgpu_fence_sz(vgpu);
पूर्ण

अटल पूर्णांक alloc_resource(काष्ठा पूर्णांकel_vgpu *vgpu,
		काष्ठा पूर्णांकel_vgpu_creation_params *param)
अणु
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	अचिन्हित दीर्घ request, avail, max, taken;
	स्थिर अक्षर *item;

	अगर (!param->low_gm_sz || !param->high_gm_sz || !param->fence_sz) अणु
		gvt_vgpu_err("Invalid vGPU creation params\n");
		वापस -EINVAL;
	पूर्ण

	item = "low GM space";
	max = gvt_aperture_sz(gvt) - HOST_LOW_GM_SIZE;
	taken = gvt->gm.vgpu_allocated_low_gm_size;
	avail = max - taken;
	request = MB_TO_BYTES(param->low_gm_sz);

	अगर (request > avail)
		जाओ no_enough_resource;

	vgpu_aperture_sz(vgpu) = ALIGN(request, I915_GTT_PAGE_SIZE);

	item = "high GM space";
	max = gvt_hidden_sz(gvt) - HOST_HIGH_GM_SIZE;
	taken = gvt->gm.vgpu_allocated_high_gm_size;
	avail = max - taken;
	request = MB_TO_BYTES(param->high_gm_sz);

	अगर (request > avail)
		जाओ no_enough_resource;

	vgpu_hidden_sz(vgpu) = ALIGN(request, I915_GTT_PAGE_SIZE);

	item = "fence";
	max = gvt_fence_sz(gvt) - HOST_FENCE;
	taken = gvt->fence.vgpu_allocated_fence_num;
	avail = max - taken;
	request = param->fence_sz;

	अगर (request > avail)
		जाओ no_enough_resource;

	vgpu_fence_sz(vgpu) = request;

	gvt->gm.vgpu_allocated_low_gm_size += MB_TO_BYTES(param->low_gm_sz);
	gvt->gm.vgpu_allocated_high_gm_size += MB_TO_BYTES(param->high_gm_sz);
	gvt->fence.vgpu_allocated_fence_num += param->fence_sz;
	वापस 0;

no_enough_resource:
	gvt_err("fail to allocate resource %s\n", item);
	gvt_err("request %luMB avail %luMB max %luMB taken %luMB\n",
		BYTES_TO_MB(request), BYTES_TO_MB(avail),
		BYTES_TO_MB(max), BYTES_TO_MB(taken));
	वापस -ENOSPC;
पूर्ण

/**
 * पूर्णांकe_gvt_मुक्त_vgpu_resource - मुक्त HW resource owned by a vGPU
 * @vgpu: a vGPU
 *
 * This function is used to मुक्त the HW resource owned by a vGPU.
 *
 */
व्योम पूर्णांकel_vgpu_मुक्त_resource(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	मुक्त_vgpu_gm(vgpu);
	मुक्त_vgpu_fence(vgpu);
	मुक्त_resource(vgpu);
पूर्ण

/**
 * पूर्णांकel_vgpu_reset_resource - reset resource state owned by a vGPU
 * @vgpu: a vGPU
 *
 * This function is used to reset resource state owned by a vGPU.
 *
 */
व्योम पूर्णांकel_vgpu_reset_resource(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	पूर्णांकel_wakeref_t wakeref;

	with_पूर्णांकel_runसमय_pm(gvt->gt->uncore->rpm, wakeref)
		_clear_vgpu_fence(vgpu);
पूर्ण

/**
 * पूर्णांकel_alloc_vgpu_resource - allocate HW resource क्रम a vGPU
 * @vgpu: vGPU
 * @param: vGPU creation params
 *
 * This function is used to allocate HW resource क्रम a vGPU. User specअगरies
 * the resource configuration through the creation params.
 *
 * Returns:
 * zero on success, negative error code अगर failed.
 *
 */
पूर्णांक पूर्णांकel_vgpu_alloc_resource(काष्ठा पूर्णांकel_vgpu *vgpu,
		काष्ठा पूर्णांकel_vgpu_creation_params *param)
अणु
	पूर्णांक ret;

	ret = alloc_resource(vgpu, param);
	अगर (ret)
		वापस ret;

	ret = alloc_vgpu_gm(vgpu);
	अगर (ret)
		जाओ out_मुक्त_resource;

	ret = alloc_vgpu_fence(vgpu);
	अगर (ret)
		जाओ out_मुक्त_vgpu_gm;

	वापस 0;

out_मुक्त_vgpu_gm:
	मुक्त_vgpu_gm(vgpu);
out_मुक्त_resource:
	मुक्त_resource(vgpu);
	वापस ret;
पूर्ण
