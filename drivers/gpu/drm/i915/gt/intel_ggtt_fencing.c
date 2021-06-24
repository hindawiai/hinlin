<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2008-2015 Intel Corporation
 */

#समावेश "i915_drv.h"
#समावेश "i915_scatterlist.h"
#समावेश "i915_pvinfo.h"
#समावेश "i915_vgpu.h"

/**
 * DOC: fence रेजिस्टर handling
 *
 * Important to aव्योम confusions: "fences" in the i915 driver are not execution
 * fences used to track command completion but hardware detiler objects which
 * wrap a given range of the global GTT. Each platक्रमm has only a fairly limited
 * set of these objects.
 *
 * Fences are used to detile GTT memory mappings. They're also connected to the
 * hardware frontbuffer render tracking and hence पूर्णांकeract with frontbuffer
 * compression. Furthermore on older platक्रमms fences are required क्रम tiled
 * objects used by the display engine. They can also be used by the render
 * engine - they're required क्रम blitter commands and are optional क्रम render
 * commands. But on gen4+ both display (with the exception of fbc) and rendering
 * have their own tiling state bits and करोn't need fences.
 *
 * Also note that fences only support X and Y tiling and hence can't be used क्रम
 * the fancier new tiling क्रमmats like W, Ys and Yf.
 *
 * Finally note that because fences are such a restricted resource they're
 * dynamically associated with objects. Furthermore fence state is committed to
 * the hardware lazily to aव्योम unnecessary stalls on gen2/3. Thereक्रमe code must
 * explicitly call i915_gem_object_get_fence() to synchronize fencing status
 * क्रम cpu access. Also note that some code wants an unfenced view, क्रम those
 * हालs the fence can be हटाओd क्रमcefully with i915_gem_object_put_fence().
 *
 * Internally these functions will synchronize with userspace access by removing
 * CPU ptes पूर्णांकo GTT mmaps (not the GTT ptes themselves) as needed.
 */

#घोषणा pipelined 0

अटल काष्ठा drm_i915_निजी *fence_to_i915(काष्ठा i915_fence_reg *fence)
अणु
	वापस fence->ggtt->vm.i915;
पूर्ण

अटल काष्ठा पूर्णांकel_uncore *fence_to_uncore(काष्ठा i915_fence_reg *fence)
अणु
	वापस fence->ggtt->vm.gt->uncore;
पूर्ण

अटल व्योम i965_ग_लिखो_fence_reg(काष्ठा i915_fence_reg *fence)
अणु
	i915_reg_t fence_reg_lo, fence_reg_hi;
	पूर्णांक fence_pitch_shअगरt;
	u64 val;

	अगर (INTEL_GEN(fence_to_i915(fence)) >= 6) अणु
		fence_reg_lo = FENCE_REG_GEN6_LO(fence->id);
		fence_reg_hi = FENCE_REG_GEN6_HI(fence->id);
		fence_pitch_shअगरt = GEN6_FENCE_PITCH_SHIFT;

	पूर्ण अन्यथा अणु
		fence_reg_lo = FENCE_REG_965_LO(fence->id);
		fence_reg_hi = FENCE_REG_965_HI(fence->id);
		fence_pitch_shअगरt = I965_FENCE_PITCH_SHIFT;
	पूर्ण

	val = 0;
	अगर (fence->tiling) अणु
		अचिन्हित पूर्णांक stride = fence->stride;

		GEM_BUG_ON(!IS_ALIGNED(stride, 128));

		val = fence->start + fence->size - I965_FENCE_PAGE;
		val <<= 32;
		val |= fence->start;
		val |= (u64)((stride / 128) - 1) << fence_pitch_shअगरt;
		अगर (fence->tiling == I915_TILING_Y)
			val |= BIT(I965_FENCE_TILING_Y_SHIFT);
		val |= I965_FENCE_REG_VALID;
	पूर्ण

	अगर (!pipelined) अणु
		काष्ठा पूर्णांकel_uncore *uncore = fence_to_uncore(fence);

		/*
		 * To w/a incoherency with non-atomic 64-bit रेजिस्टर updates,
		 * we split the 64-bit update पूर्णांकo two 32-bit ग_लिखोs. In order
		 * क्रम a partial fence not to be evaluated between ग_लिखोs, we
		 * precede the update with ग_लिखो to turn off the fence रेजिस्टर,
		 * and only enable the fence as the last step.
		 *
		 * For extra levels of paranoia, we make sure each step lands
		 * beक्रमe applying the next step.
		 */
		पूर्णांकel_uncore_ग_लिखो_fw(uncore, fence_reg_lo, 0);
		पूर्णांकel_uncore_posting_पढ़ो_fw(uncore, fence_reg_lo);

		पूर्णांकel_uncore_ग_लिखो_fw(uncore, fence_reg_hi, upper_32_bits(val));
		पूर्णांकel_uncore_ग_लिखो_fw(uncore, fence_reg_lo, lower_32_bits(val));
		पूर्णांकel_uncore_posting_पढ़ो_fw(uncore, fence_reg_lo);
	पूर्ण
पूर्ण

अटल व्योम i915_ग_लिखो_fence_reg(काष्ठा i915_fence_reg *fence)
अणु
	u32 val;

	val = 0;
	अगर (fence->tiling) अणु
		अचिन्हित पूर्णांक stride = fence->stride;
		अचिन्हित पूर्णांक tiling = fence->tiling;
		bool is_y_tiled = tiling == I915_TILING_Y;

		अगर (is_y_tiled && HAS_128_BYTE_Y_TILING(fence_to_i915(fence)))
			stride /= 128;
		अन्यथा
			stride /= 512;
		GEM_BUG_ON(!is_घातer_of_2(stride));

		val = fence->start;
		अगर (is_y_tiled)
			val |= BIT(I830_FENCE_TILING_Y_SHIFT);
		val |= I915_FENCE_SIZE_BITS(fence->size);
		val |= ilog2(stride) << I830_FENCE_PITCH_SHIFT;

		val |= I830_FENCE_REG_VALID;
	पूर्ण

	अगर (!pipelined) अणु
		काष्ठा पूर्णांकel_uncore *uncore = fence_to_uncore(fence);
		i915_reg_t reg = FENCE_REG(fence->id);

		पूर्णांकel_uncore_ग_लिखो_fw(uncore, reg, val);
		पूर्णांकel_uncore_posting_पढ़ो_fw(uncore, reg);
	पूर्ण
पूर्ण

अटल व्योम i830_ग_लिखो_fence_reg(काष्ठा i915_fence_reg *fence)
अणु
	u32 val;

	val = 0;
	अगर (fence->tiling) अणु
		अचिन्हित पूर्णांक stride = fence->stride;

		val = fence->start;
		अगर (fence->tiling == I915_TILING_Y)
			val |= BIT(I830_FENCE_TILING_Y_SHIFT);
		val |= I830_FENCE_SIZE_BITS(fence->size);
		val |= ilog2(stride / 128) << I830_FENCE_PITCH_SHIFT;
		val |= I830_FENCE_REG_VALID;
	पूर्ण

	अगर (!pipelined) अणु
		काष्ठा पूर्णांकel_uncore *uncore = fence_to_uncore(fence);
		i915_reg_t reg = FENCE_REG(fence->id);

		पूर्णांकel_uncore_ग_लिखो_fw(uncore, reg, val);
		पूर्णांकel_uncore_posting_पढ़ो_fw(uncore, reg);
	पूर्ण
पूर्ण

अटल व्योम fence_ग_लिखो(काष्ठा i915_fence_reg *fence)
अणु
	काष्ठा drm_i915_निजी *i915 = fence_to_i915(fence);

	/*
	 * Previous access through the fence रेजिस्टर is marshalled by
	 * the mb() inside the fault handlers (i915_gem_release_mmaps)
	 * and explicitly managed क्रम पूर्णांकernal users.
	 */

	अगर (IS_GEN(i915, 2))
		i830_ग_लिखो_fence_reg(fence);
	अन्यथा अगर (IS_GEN(i915, 3))
		i915_ग_लिखो_fence_reg(fence);
	अन्यथा
		i965_ग_लिखो_fence_reg(fence);

	/*
	 * Access through the fenced region afterwards is
	 * ordered by the posting पढ़ोs whilst writing the रेजिस्टरs.
	 */
पूर्ण

अटल bool gpu_uses_fence_रेजिस्टरs(काष्ठा i915_fence_reg *fence)
अणु
	वापस INTEL_GEN(fence_to_i915(fence)) < 4;
पूर्ण

अटल पूर्णांक fence_update(काष्ठा i915_fence_reg *fence,
			काष्ठा i915_vma *vma)
अणु
	काष्ठा i915_ggtt *ggtt = fence->ggtt;
	काष्ठा पूर्णांकel_uncore *uncore = fence_to_uncore(fence);
	पूर्णांकel_wakeref_t wakeref;
	काष्ठा i915_vma *old;
	पूर्णांक ret;

	fence->tiling = 0;
	अगर (vma) अणु
		GEM_BUG_ON(!i915_gem_object_get_stride(vma->obj) ||
			   !i915_gem_object_get_tiling(vma->obj));

		अगर (!i915_vma_is_map_and_fenceable(vma))
			वापस -EINVAL;

		अगर (gpu_uses_fence_रेजिस्टरs(fence)) अणु
			/* implicit 'unfenced' GPU blits */
			ret = i915_vma_sync(vma);
			अगर (ret)
				वापस ret;
		पूर्ण

		fence->start = vma->node.start;
		fence->size = vma->fence_size;
		fence->stride = i915_gem_object_get_stride(vma->obj);
		fence->tiling = i915_gem_object_get_tiling(vma->obj);
	पूर्ण
	WRITE_ONCE(fence->dirty, false);

	old = xchg(&fence->vma, शून्य);
	अगर (old) अणु
		/* XXX Ideally we would move the रुकोing to outside the mutex */
		ret = i915_active_रुको(&fence->active);
		अगर (ret) अणु
			fence->vma = old;
			वापस ret;
		पूर्ण

		i915_vma_flush_ग_लिखोs(old);

		/*
		 * Ensure that all userspace CPU access is completed beक्रमe
		 * stealing the fence.
		 */
		अगर (old != vma) अणु
			GEM_BUG_ON(old->fence != fence);
			i915_vma_revoke_mmap(old);
			old->fence = शून्य;
		पूर्ण

		list_move(&fence->link, &ggtt->fence_list);
	पूर्ण

	/*
	 * We only need to update the रेजिस्टर itself अगर the device is awake.
	 * If the device is currently घातered करोwn, we will defer the ग_लिखो
	 * to the runसमय resume, see पूर्णांकel_ggtt_restore_fences().
	 *
	 * This only works क्रम removing the fence रेजिस्टर, on acquisition
	 * the caller must hold the rpm wakeref. The fence रेजिस्टर must
	 * be cleared beक्रमe we can use any other fences to ensure that
	 * the new fences करो not overlap the elided clears, confusing HW.
	 */
	wakeref = पूर्णांकel_runसमय_pm_get_अगर_in_use(uncore->rpm);
	अगर (!wakeref) अणु
		GEM_BUG_ON(vma);
		वापस 0;
	पूर्ण

	WRITE_ONCE(fence->vma, vma);
	fence_ग_लिखो(fence);

	अगर (vma) अणु
		vma->fence = fence;
		list_move_tail(&fence->link, &ggtt->fence_list);
	पूर्ण

	पूर्णांकel_runसमय_pm_put(uncore->rpm, wakeref);
	वापस 0;
पूर्ण

/**
 * i915_vma_revoke_fence - क्रमce-हटाओ fence क्रम a VMA
 * @vma: vma to map linearly (not through a fence reg)
 *
 * This function क्रमce-हटाओs any fence from the given object, which is useful
 * अगर the kernel wants to करो untiled GTT access.
 */
व्योम i915_vma_revoke_fence(काष्ठा i915_vma *vma)
अणु
	काष्ठा i915_fence_reg *fence = vma->fence;
	पूर्णांकel_wakeref_t wakeref;

	lockdep_निश्चित_held(&vma->vm->mutex);
	अगर (!fence)
		वापस;

	GEM_BUG_ON(fence->vma != vma);
	GEM_BUG_ON(!i915_active_is_idle(&fence->active));
	GEM_BUG_ON(atomic_पढ़ो(&fence->pin_count));

	fence->tiling = 0;
	WRITE_ONCE(fence->vma, शून्य);
	vma->fence = शून्य;

	/*
	 * Skip the ग_लिखो to HW अगर and only अगर the device is currently
	 * suspended.
	 *
	 * If the driver करोes not currently hold a wakeref (अगर_in_use == 0),
	 * the device may currently be runसमय suspended, or it may be woken
	 * up beक्रमe the suspend takes place. If the device is not suspended
	 * (घातered करोwn) and we skip clearing the fence रेजिस्टर, the HW is
	 * left in an undefined state where we may end up with multiple
	 * रेजिस्टरs overlapping.
	 */
	with_पूर्णांकel_runसमय_pm_अगर_active(fence_to_uncore(fence)->rpm, wakeref)
		fence_ग_लिखो(fence);
पूर्ण

अटल bool fence_is_active(स्थिर काष्ठा i915_fence_reg *fence)
अणु
	वापस fence->vma && i915_vma_is_active(fence->vma);
पूर्ण

अटल काष्ठा i915_fence_reg *fence_find(काष्ठा i915_ggtt *ggtt)
अणु
	काष्ठा i915_fence_reg *active = शून्य;
	काष्ठा i915_fence_reg *fence, *fn;

	list_क्रम_each_entry_safe(fence, fn, &ggtt->fence_list, link) अणु
		GEM_BUG_ON(fence->vma && fence->vma->fence != fence);

		अगर (fence == active) /* now seen this fence twice */
			active = ERR_PTR(-EAGAIN);

		/* Prefer idle fences so we करो not have to रुको on the GPU */
		अगर (active != ERR_PTR(-EAGAIN) && fence_is_active(fence)) अणु
			अगर (!active)
				active = fence;

			list_move_tail(&fence->link, &ggtt->fence_list);
			जारी;
		पूर्ण

		अगर (atomic_पढ़ो(&fence->pin_count))
			जारी;

		वापस fence;
	पूर्ण

	/* Wait क्रम completion of pending flips which consume fences */
	अगर (पूर्णांकel_has_pending_fb_unpin(ggtt->vm.i915))
		वापस ERR_PTR(-EAGAIN);

	वापस ERR_PTR(-EDEADLK);
पूर्ण

पूर्णांक __i915_vma_pin_fence(काष्ठा i915_vma *vma)
अणु
	काष्ठा i915_ggtt *ggtt = i915_vm_to_ggtt(vma->vm);
	काष्ठा i915_fence_reg *fence;
	काष्ठा i915_vma *set = i915_gem_object_is_tiled(vma->obj) ? vma : शून्य;
	पूर्णांक err;

	lockdep_निश्चित_held(&vma->vm->mutex);

	/* Just update our place in the LRU अगर our fence is getting reused. */
	अगर (vma->fence) अणु
		fence = vma->fence;
		GEM_BUG_ON(fence->vma != vma);
		atomic_inc(&fence->pin_count);
		अगर (!fence->dirty) अणु
			list_move_tail(&fence->link, &ggtt->fence_list);
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अगर (set) अणु
		fence = fence_find(ggtt);
		अगर (IS_ERR(fence))
			वापस PTR_ERR(fence);

		GEM_BUG_ON(atomic_पढ़ो(&fence->pin_count));
		atomic_inc(&fence->pin_count);
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण

	err = fence_update(fence, set);
	अगर (err)
		जाओ out_unpin;

	GEM_BUG_ON(fence->vma != set);
	GEM_BUG_ON(vma->fence != (set ? fence : शून्य));

	अगर (set)
		वापस 0;

out_unpin:
	atomic_dec(&fence->pin_count);
	वापस err;
पूर्ण

/**
 * i915_vma_pin_fence - set up fencing क्रम a vma
 * @vma: vma to map through a fence reg
 *
 * When mapping objects through the GTT, userspace wants to be able to ग_लिखो
 * to them without having to worry about swizzling अगर the object is tiled.
 * This function walks the fence regs looking क्रम a मुक्त one क्रम @obj,
 * stealing one अगर it can't find any.
 *
 * It then sets up the reg based on the object's properties: address, pitch
 * and tiling क्रमmat.
 *
 * For an untiled surface, this हटाओs any existing fence.
 *
 * Returns:
 *
 * 0 on success, negative error code on failure.
 */
पूर्णांक i915_vma_pin_fence(काष्ठा i915_vma *vma)
अणु
	पूर्णांक err;

	अगर (!vma->fence && !i915_gem_object_is_tiled(vma->obj))
		वापस 0;

	/*
	 * Note that we revoke fences on runसमय suspend. Thereक्रमe the user
	 * must keep the device awake whilst using the fence.
	 */
	निश्चित_rpm_wakelock_held(vma->vm->gt->uncore->rpm);
	GEM_BUG_ON(!i915_vma_is_pinned(vma));
	GEM_BUG_ON(!i915_vma_is_ggtt(vma));

	err = mutex_lock_पूर्णांकerruptible(&vma->vm->mutex);
	अगर (err)
		वापस err;

	err = __i915_vma_pin_fence(vma);
	mutex_unlock(&vma->vm->mutex);

	वापस err;
पूर्ण

/**
 * i915_reserve_fence - Reserve a fence क्रम vGPU
 * @ggtt: Global GTT
 *
 * This function walks the fence regs looking क्रम a मुक्त one and हटाओ
 * it from the fence_list. It is used to reserve fence क्रम vGPU to use.
 */
काष्ठा i915_fence_reg *i915_reserve_fence(काष्ठा i915_ggtt *ggtt)
अणु
	काष्ठा i915_fence_reg *fence;
	पूर्णांक count;
	पूर्णांक ret;

	lockdep_निश्चित_held(&ggtt->vm.mutex);

	/* Keep at least one fence available क्रम the display engine. */
	count = 0;
	list_क्रम_each_entry(fence, &ggtt->fence_list, link)
		count += !atomic_पढ़ो(&fence->pin_count);
	अगर (count <= 1)
		वापस ERR_PTR(-ENOSPC);

	fence = fence_find(ggtt);
	अगर (IS_ERR(fence))
		वापस fence;

	अगर (fence->vma) अणु
		/* Force-हटाओ fence from VMA */
		ret = fence_update(fence, शून्य);
		अगर (ret)
			वापस ERR_PTR(ret);
	पूर्ण

	list_del(&fence->link);

	वापस fence;
पूर्ण

/**
 * i915_unreserve_fence - Reclaim a reserved fence
 * @fence: the fence reg
 *
 * This function add a reserved fence रेजिस्टर from vGPU to the fence_list.
 */
व्योम i915_unreserve_fence(काष्ठा i915_fence_reg *fence)
अणु
	काष्ठा i915_ggtt *ggtt = fence->ggtt;

	lockdep_निश्चित_held(&ggtt->vm.mutex);

	list_add(&fence->link, &ggtt->fence_list);
पूर्ण

/**
 * पूर्णांकel_ggtt_restore_fences - restore fence state
 * @ggtt: Global GTT
 *
 * Restore the hw fence state to match the software tracking again, to be called
 * after a gpu reset and on resume. Note that on runसमय suspend we only cancel
 * the fences, to be reacquired by the user later.
 */
व्योम पूर्णांकel_ggtt_restore_fences(काष्ठा i915_ggtt *ggtt)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ggtt->num_fences; i++)
		fence_ग_लिखो(&ggtt->fence_regs[i]);
पूर्ण

/**
 * DOC: tiling swizzling details
 *
 * The idea behind tiling is to increase cache hit rates by rearranging
 * pixel data so that a group of pixel accesses are in the same cacheline.
 * Perक्रमmance improvement from करोing this on the back/depth buffer are on
 * the order of 30%.
 *
 * Intel architectures make this somewhat more complicated, though, by
 * adjusपंचांगents made to addressing of data when the memory is in पूर्णांकerleaved
 * mode (matched pairs of DIMMS) to improve memory bandwidth.
 * For पूर्णांकerleaved memory, the CPU sends every sequential 64 bytes
 * to an alternate memory channel so it can get the bandwidth from both.
 *
 * The GPU also rearranges its accesses क्रम increased bandwidth to पूर्णांकerleaved
 * memory, and it matches what the CPU करोes क्रम non-tiled.  However, when tiled
 * it करोes it a little dअगरferently, since one walks addresses not just in the
 * X direction but also Y.  So, aदीर्घ with alternating channels when bit
 * 6 of the address flips, it also alternates when other bits flip --  Bits 9
 * (every 512 bytes, an X tile scanline) and 10 (every two X tile scanlines)
 * are common to both the 915 and 965-class hardware.
 *
 * The CPU also someबार XORs in higher bits as well, to improve
 * bandwidth करोing strided access like we करो so frequently in graphics.  This
 * is called "Channel XOR Randomization" in the MCH करोcumentation.  The result
 * is that the CPU is XORing in either bit 11 or bit 17 to bit 6 of its address
 * decode.
 *
 * All of this bit 6 XORing has an effect on our memory management,
 * as we need to make sure that the 3d driver can correctly address object
 * contents.
 *
 * If we करोn't have पूर्णांकerleaved memory, all tiling is safe and no swizzling is
 * required.
 *
 * When bit 17 is XORed in, we simply refuse to tile at all.  Bit
 * 17 is not just a page offset, so as we page an object out and back in,
 * inभागidual pages in it will have dअगरferent bit 17 addresses, resulting in
 * each 64 bytes being swapped with its neighbor!
 *
 * Otherwise, अगर पूर्णांकerleaved, we have to tell the 3d driver what the address
 * swizzling it needs to करो is, since it's writing with the CPU to the pages
 * (bit 6 and potentially bit 11 XORed in), and the GPU is पढ़ोing from the
 * pages (bit 6, 9, and 10 XORed in), resulting in a cumulative bit swizzling
 * required by the CPU of XORing in bit 6, 9, 10, and potentially 11, in order
 * to match what the GPU expects.
 */

/**
 * detect_bit_6_swizzle - detect bit 6 swizzling pattern
 * @ggtt: Global GGTT
 *
 * Detects bit 6 swizzling of address lookup between IGD access and CPU
 * access through मुख्य memory.
 */
अटल व्योम detect_bit_6_swizzle(काष्ठा i915_ggtt *ggtt)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = ggtt->vm.gt->uncore;
	काष्ठा drm_i915_निजी *i915 = ggtt->vm.i915;
	u32 swizzle_x = I915_BIT_6_SWIZZLE_UNKNOWN;
	u32 swizzle_y = I915_BIT_6_SWIZZLE_UNKNOWN;

	अगर (INTEL_GEN(i915) >= 8 || IS_VALLEYVIEW(i915)) अणु
		/*
		 * On BDW+, swizzling is not used. We leave the CPU memory
		 * controller in अक्षरge of optimizing memory accesses without
		 * the extra address manipulation GPU side.
		 *
		 * VLV and CHV करोn't have GPU swizzling.
		 */
		swizzle_x = I915_BIT_6_SWIZZLE_NONE;
		swizzle_y = I915_BIT_6_SWIZZLE_NONE;
	पूर्ण अन्यथा अगर (INTEL_GEN(i915) >= 6) अणु
		अगर (i915->preserve_bios_swizzle) अणु
			अगर (पूर्णांकel_uncore_पढ़ो(uncore, DISP_ARB_CTL) &
			    DISP_TILE_SURFACE_SWIZZLING) अणु
				swizzle_x = I915_BIT_6_SWIZZLE_9_10;
				swizzle_y = I915_BIT_6_SWIZZLE_9;
			पूर्ण अन्यथा अणु
				swizzle_x = I915_BIT_6_SWIZZLE_NONE;
				swizzle_y = I915_BIT_6_SWIZZLE_NONE;
			पूर्ण
		पूर्ण अन्यथा अणु
			u32 dimm_c0, dimm_c1;

			dimm_c0 = पूर्णांकel_uncore_पढ़ो(uncore, MAD_DIMM_C0);
			dimm_c1 = पूर्णांकel_uncore_पढ़ो(uncore, MAD_DIMM_C1);
			dimm_c0 &= MAD_DIMM_A_SIZE_MASK | MAD_DIMM_B_SIZE_MASK;
			dimm_c1 &= MAD_DIMM_A_SIZE_MASK | MAD_DIMM_B_SIZE_MASK;
			/*
			 * Enable swizzling when the channels are populated
			 * with identically sized dimms. We करोn't need to check
			 * the 3rd channel because no cpu with gpu attached
			 * ships in that configuration. Also, swizzling only
			 * makes sense क्रम 2 channels anyway.
			 */
			अगर (dimm_c0 == dimm_c1) अणु
				swizzle_x = I915_BIT_6_SWIZZLE_9_10;
				swizzle_y = I915_BIT_6_SWIZZLE_9;
			पूर्ण अन्यथा अणु
				swizzle_x = I915_BIT_6_SWIZZLE_NONE;
				swizzle_y = I915_BIT_6_SWIZZLE_NONE;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (IS_GEN(i915, 5)) अणु
		/*
		 * On Ironlake whatever DRAM config, GPU always करो
		 * same swizzling setup.
		 */
		swizzle_x = I915_BIT_6_SWIZZLE_9_10;
		swizzle_y = I915_BIT_6_SWIZZLE_9;
	पूर्ण अन्यथा अगर (IS_GEN(i915, 2)) अणु
		/*
		 * As far as we know, the 865 करोesn't have these bit 6
		 * swizzling issues.
		 */
		swizzle_x = I915_BIT_6_SWIZZLE_NONE;
		swizzle_y = I915_BIT_6_SWIZZLE_NONE;
	पूर्ण अन्यथा अगर (IS_G45(i915) || IS_I965G(i915) || IS_G33(i915)) अणु
		/*
		 * The 965, G33, and newer, have a very flexible memory
		 * configuration.  It will enable dual-channel mode
		 * (पूर्णांकerleaving) on as much memory as it can, and the GPU
		 * will additionally someबार enable dअगरferent bit 6
		 * swizzling क्रम tiled objects from the CPU.
		 *
		 * Here's what I found on the G965:
		 *    slot fill         memory size  swizzling
		 * 0A   0B   1A   1B    1-ch   2-ch
		 * 512  0    0    0     512    0     O
		 * 512  0    512  0     16     1008  X
		 * 512  0    0    512   16     1008  X
		 * 0    512  0    512   16     1008  X
		 * 1024 1024 1024 0     2048   1024  O
		 *
		 * We could probably detect this based on either the DRB
		 * matching, which was the हाल क्रम the swizzling required in
		 * the table above, or from the 1-ch value being less than
		 * the minimum size of a rank.
		 *
		 * Reports indicate that the swizzling actually
		 * varies depending upon page placement inside the
		 * channels, i.e. we see swizzled pages where the
		 * banks of memory are paired and unswizzled on the
		 * uneven portion, so leave that as unknown.
		 */
		अगर (पूर्णांकel_uncore_पढ़ो16(uncore, C0DRB3) ==
		    पूर्णांकel_uncore_पढ़ो16(uncore, C1DRB3)) अणु
			swizzle_x = I915_BIT_6_SWIZZLE_9_10;
			swizzle_y = I915_BIT_6_SWIZZLE_9;
		पूर्ण
	पूर्ण अन्यथा अणु
		u32 dcc = पूर्णांकel_uncore_पढ़ो(uncore, DCC);

		/*
		 * On 9xx chipsets, channel पूर्णांकerleave by the CPU is
		 * determined by DCC.  For single-channel, neither the CPU
		 * nor the GPU करो swizzling.  For dual channel पूर्णांकerleaved,
		 * the GPU's पूर्णांकerleave is bit 9 and 10 क्रम X tiled, and bit
		 * 9 क्रम Y tiled.  The CPU's पूर्णांकerleave is independent, and
		 * can be based on either bit 11 (haven't seen this yet) or
		 * bit 17 (common).
		 */
		चयन (dcc & DCC_ADDRESSING_MODE_MASK) अणु
		हाल DCC_ADDRESSING_MODE_SINGLE_CHANNEL:
		हाल DCC_ADDRESSING_MODE_DUAL_CHANNEL_ASYMMETRIC:
			swizzle_x = I915_BIT_6_SWIZZLE_NONE;
			swizzle_y = I915_BIT_6_SWIZZLE_NONE;
			अवरोध;
		हाल DCC_ADDRESSING_MODE_DUAL_CHANNEL_INTERLEAVED:
			अगर (dcc & DCC_CHANNEL_XOR_DISABLE) अणु
				/*
				 * This is the base swizzling by the GPU क्रम
				 * tiled buffers.
				 */
				swizzle_x = I915_BIT_6_SWIZZLE_9_10;
				swizzle_y = I915_BIT_6_SWIZZLE_9;
			पूर्ण अन्यथा अगर ((dcc & DCC_CHANNEL_XOR_BIT_17) == 0) अणु
				/* Bit 11 swizzling by the CPU in addition. */
				swizzle_x = I915_BIT_6_SWIZZLE_9_10_11;
				swizzle_y = I915_BIT_6_SWIZZLE_9_11;
			पूर्ण अन्यथा अणु
				/* Bit 17 swizzling by the CPU in addition. */
				swizzle_x = I915_BIT_6_SWIZZLE_9_10_17;
				swizzle_y = I915_BIT_6_SWIZZLE_9_17;
			पूर्ण
			अवरोध;
		पूर्ण

		/* check क्रम L-shaped memory aka modअगरied enhanced addressing */
		अगर (IS_GEN(i915, 4) &&
		    !(पूर्णांकel_uncore_पढ़ो(uncore, DCC2) & DCC2_MODIFIED_ENHANCED_DISABLE)) अणु
			swizzle_x = I915_BIT_6_SWIZZLE_UNKNOWN;
			swizzle_y = I915_BIT_6_SWIZZLE_UNKNOWN;
		पूर्ण

		अगर (dcc == 0xffffffff) अणु
			drm_err(&i915->drm, "Couldn't read from MCHBAR.  "
				  "Disabling tiling.\n");
			swizzle_x = I915_BIT_6_SWIZZLE_UNKNOWN;
			swizzle_y = I915_BIT_6_SWIZZLE_UNKNOWN;
		पूर्ण
	पूर्ण

	अगर (swizzle_x == I915_BIT_6_SWIZZLE_UNKNOWN ||
	    swizzle_y == I915_BIT_6_SWIZZLE_UNKNOWN) अणु
		/*
		 * Userspace likes to explode अगर it sees unknown swizzling,
		 * so lie. We will finish the lie when reporting through
		 * the get-tiling-ioctl by reporting the physical swizzle
		 * mode as unknown instead.
		 *
		 * As we करोn't strictly know what the swizzling is, it may be
		 * bit17 dependent, and so we need to also prevent the pages
		 * from being moved.
		 */
		i915->quirks |= QUIRK_PIN_SWIZZLED_PAGES;
		swizzle_x = I915_BIT_6_SWIZZLE_NONE;
		swizzle_y = I915_BIT_6_SWIZZLE_NONE;
	पूर्ण

	i915->ggtt.bit_6_swizzle_x = swizzle_x;
	i915->ggtt.bit_6_swizzle_y = swizzle_y;
पूर्ण

/*
 * Swap every 64 bytes of this page around, to account क्रम it having a new
 * bit 17 of its physical address and thereक्रमe being पूर्णांकerpreted dअगरferently
 * by the GPU.
 */
अटल व्योम swizzle_page(काष्ठा page *page)
अणु
	अक्षर temp[64];
	अक्षर *vaddr;
	पूर्णांक i;

	vaddr = kmap(page);

	क्रम (i = 0; i < PAGE_SIZE; i += 128) अणु
		स_नकल(temp, &vaddr[i], 64);
		स_नकल(&vaddr[i], &vaddr[i + 64], 64);
		स_नकल(&vaddr[i + 64], temp, 64);
	पूर्ण

	kunmap(page);
पूर्ण

/**
 * i915_gem_object_करो_bit_17_swizzle - fixup bit 17 swizzling
 * @obj: i915 GEM buffer object
 * @pages: the scattergather list of physical pages
 *
 * This function fixes up the swizzling in हाल any page frame number क्रम this
 * object has changed in bit 17 since that state has been saved with
 * i915_gem_object_save_bit_17_swizzle().
 *
 * This is called when pinning backing storage again, since the kernel is मुक्त
 * to move unpinned backing storage around (either by directly moving pages or
 * by swapping them out and back in again).
 */
व्योम
i915_gem_object_करो_bit_17_swizzle(काष्ठा drm_i915_gem_object *obj,
				  काष्ठा sg_table *pages)
अणु
	काष्ठा sgt_iter sgt_iter;
	काष्ठा page *page;
	पूर्णांक i;

	अगर (obj->bit_17 == शून्य)
		वापस;

	i = 0;
	क्रम_each_sgt_page(page, sgt_iter, pages) अणु
		अक्षर new_bit_17 = page_to_phys(page) >> 17;

		अगर ((new_bit_17 & 0x1) != (test_bit(i, obj->bit_17) != 0)) अणु
			swizzle_page(page);
			set_page_dirty(page);
		पूर्ण

		i++;
	पूर्ण
पूर्ण

/**
 * i915_gem_object_save_bit_17_swizzle - save bit 17 swizzling
 * @obj: i915 GEM buffer object
 * @pages: the scattergather list of physical pages
 *
 * This function saves the bit 17 of each page frame number so that swizzling
 * can be fixed up later on with i915_gem_object_करो_bit_17_swizzle(). This must
 * be called beक्रमe the backing storage can be unpinned.
 */
व्योम
i915_gem_object_save_bit_17_swizzle(काष्ठा drm_i915_gem_object *obj,
				    काष्ठा sg_table *pages)
अणु
	स्थिर अचिन्हित पूर्णांक page_count = obj->base.size >> PAGE_SHIFT;
	काष्ठा sgt_iter sgt_iter;
	काष्ठा page *page;
	पूर्णांक i;

	अगर (obj->bit_17 == शून्य) अणु
		obj->bit_17 = biपंचांगap_zalloc(page_count, GFP_KERNEL);
		अगर (obj->bit_17 == शून्य) अणु
			DRM_ERROR("Failed to allocate memory for bit 17 "
				  "record\n");
			वापस;
		पूर्ण
	पूर्ण

	i = 0;

	क्रम_each_sgt_page(page, sgt_iter, pages) अणु
		अगर (page_to_phys(page) & (1 << 17))
			__set_bit(i, obj->bit_17);
		अन्यथा
			__clear_bit(i, obj->bit_17);
		i++;
	पूर्ण
पूर्ण

व्योम पूर्णांकel_ggtt_init_fences(काष्ठा i915_ggtt *ggtt)
अणु
	काष्ठा drm_i915_निजी *i915 = ggtt->vm.i915;
	काष्ठा पूर्णांकel_uncore *uncore = ggtt->vm.gt->uncore;
	पूर्णांक num_fences;
	पूर्णांक i;

	INIT_LIST_HEAD(&ggtt->fence_list);
	INIT_LIST_HEAD(&ggtt->userfault_list);
	पूर्णांकel_wakeref_स्वतः_init(&ggtt->userfault_wakeref, uncore->rpm);

	detect_bit_6_swizzle(ggtt);

	अगर (!i915_ggtt_has_aperture(ggtt))
		num_fences = 0;
	अन्यथा अगर (INTEL_GEN(i915) >= 7 &&
		 !(IS_VALLEYVIEW(i915) || IS_CHERRYVIEW(i915)))
		num_fences = 32;
	अन्यथा अगर (INTEL_GEN(i915) >= 4 ||
		 IS_I945G(i915) || IS_I945GM(i915) ||
		 IS_G33(i915) || IS_PINEVIEW(i915))
		num_fences = 16;
	अन्यथा
		num_fences = 8;

	अगर (पूर्णांकel_vgpu_active(i915))
		num_fences = पूर्णांकel_uncore_पढ़ो(uncore,
					       vgtअगर_reg(avail_rs.fence_num));
	ggtt->fence_regs = kसुस्मृति(num_fences,
				   माप(*ggtt->fence_regs),
				   GFP_KERNEL);
	अगर (!ggtt->fence_regs)
		num_fences = 0;

	/* Initialize fence रेजिस्टरs to zero */
	क्रम (i = 0; i < num_fences; i++) अणु
		काष्ठा i915_fence_reg *fence = &ggtt->fence_regs[i];

		i915_active_init(&fence->active, शून्य, शून्य);
		fence->ggtt = ggtt;
		fence->id = i;
		list_add_tail(&fence->link, &ggtt->fence_list);
	पूर्ण
	ggtt->num_fences = num_fences;

	पूर्णांकel_ggtt_restore_fences(ggtt);
पूर्ण

व्योम पूर्णांकel_ggtt_fini_fences(काष्ठा i915_ggtt *ggtt)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ggtt->num_fences; i++) अणु
		काष्ठा i915_fence_reg *fence = &ggtt->fence_regs[i];

		i915_active_fini(&fence->active);
	पूर्ण

	kमुक्त(ggtt->fence_regs);
पूर्ण

व्योम पूर्णांकel_gt_init_swizzling(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा drm_i915_निजी *i915 = gt->i915;
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;

	अगर (INTEL_GEN(i915) < 5 ||
	    i915->ggtt.bit_6_swizzle_x == I915_BIT_6_SWIZZLE_NONE)
		वापस;

	पूर्णांकel_uncore_rmw(uncore, DISP_ARB_CTL, 0, DISP_TILE_SURFACE_SWIZZLING);

	अगर (IS_GEN(i915, 5))
		वापस;

	पूर्णांकel_uncore_rmw(uncore, TILECTL, 0, TILECTL_SWZCTL);

	अगर (IS_GEN(i915, 6))
		पूर्णांकel_uncore_ग_लिखो(uncore,
				   ARB_MODE,
				   _MASKED_BIT_ENABLE(ARB_MODE_SWIZZLE_SNB));
	अन्यथा अगर (IS_GEN(i915, 7))
		पूर्णांकel_uncore_ग_लिखो(uncore,
				   ARB_MODE,
				   _MASKED_BIT_ENABLE(ARB_MODE_SWIZZLE_IVB));
	अन्यथा अगर (IS_GEN(i915, 8))
		पूर्णांकel_uncore_ग_लिखो(uncore,
				   GAMTARBMODE,
				   _MASKED_BIT_ENABLE(ARB_MODE_SWIZZLE_BDW));
	अन्यथा
		MISSING_CASE(INTEL_GEN(i915));
पूर्ण
