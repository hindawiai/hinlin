<शैली गुरु>
/*
 * Copyright(c) 2011-2015 Intel Corporation. All rights reserved.
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
 */

#समावेश "i915_drv.h"
#समावेश "i915_pvinfo.h"
#समावेश "i915_vgpu.h"

/**
 * DOC: Intel GVT-g guest support
 *
 * Intel GVT-g is a graphics भवization technology which shares the
 * GPU among multiple भव machines on a समय-sharing basis. Each
 * भव machine is presented a भव GPU (vGPU), which has equivalent
 * features as the underlying physical GPU (pGPU), so i915 driver can run
 * seamlessly in a भव machine. This file provides vGPU specअगरic
 * optimizations when running in a भव machine, to reduce the complनिकासy
 * of vGPU emulation and to improve the overall perक्रमmance.
 *
 * A primary function पूर्णांकroduced here is so-called "address space ballooning"
 * technique. Intel GVT-g partitions global graphics memory among multiple VMs,
 * so each VM can directly access a portion of the memory without hypervisor's
 * पूर्णांकervention, e.g. filling textures or queuing commands. However with the
 * partitioning an unmodअगरied i915 driver would assume a smaller graphics
 * memory starting from address ZERO, then requires vGPU emulation module to
 * translate the graphics address between 'guest view' and 'host view', क्रम
 * all रेजिस्टरs and command opcodes which contain a graphics memory address.
 * To reduce the complनिकासy, Intel GVT-g पूर्णांकroduces "address space ballooning",
 * by telling the exact partitioning knowledge to each guest i915 driver, which
 * then reserves and prevents non-allocated portions from allocation. Thus vGPU
 * emulation module only needs to scan and validate graphics addresses without
 * complनिकासy of address translation.
 *
 */

/**
 * पूर्णांकel_vgpu_detect - detect भव GPU
 * @dev_priv: i915 device निजी
 *
 * This function is called at the initialization stage, to detect whether
 * running on a vGPU.
 */
व्योम पूर्णांकel_vgpu_detect(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_priv->drm.dev);
	u64 magic;
	u16 version_major;
	व्योम __iomem *shared_area;

	BUILD_BUG_ON(माप(काष्ठा vgt_अगर) != VGT_PVINFO_SIZE);

	/*
	 * This is called beक्रमe we setup the मुख्य MMIO BAR mappings used via
	 * the uncore काष्ठाure, so we need to access the BAR directly. Since
	 * we करो not support VGT on older gens, वापस early so we करोn't have
	 * to consider dअगरferently numbered or sized MMIO bars
	 */
	अगर (INTEL_GEN(dev_priv) < 6)
		वापस;

	shared_area = pci_iomap_range(pdev, 0, VGT_PVINFO_PAGE, VGT_PVINFO_SIZE);
	अगर (!shared_area) अणु
		drm_err(&dev_priv->drm,
			"failed to map MMIO bar to check for VGT\n");
		वापस;
	पूर्ण

	magic = पढ़ोq(shared_area + vgtअगर_offset(magic));
	अगर (magic != VGT_MAGIC)
		जाओ out;

	version_major = पढ़ोw(shared_area + vgtअगर_offset(version_major));
	अगर (version_major < VGT_VERSION_MAJOR) अणु
		drm_info(&dev_priv->drm, "VGT interface version mismatch!\n");
		जाओ out;
	पूर्ण

	dev_priv->vgpu.caps = पढ़ोl(shared_area + vgtअगर_offset(vgt_caps));

	dev_priv->vgpu.active = true;
	mutex_init(&dev_priv->vgpu.lock);
	drm_info(&dev_priv->drm, "Virtual GPU for Intel GVT-g detected.\n");

out:
	pci_iounmap(pdev, shared_area);
पूर्ण

व्योम पूर्णांकel_vgpu_रेजिस्टर(काष्ठा drm_i915_निजी *i915)
अणु
	/*
	 * Notअगरy a valid surface after modesetting, when running inside a VM.
	 */
	अगर (पूर्णांकel_vgpu_active(i915))
		पूर्णांकel_uncore_ग_लिखो(&i915->uncore, vgtअगर_reg(display_पढ़ोy),
				   VGT_DRV_DISPLAY_READY);
पूर्ण

bool पूर्णांकel_vgpu_active(काष्ठा drm_i915_निजी *dev_priv)
अणु
	वापस dev_priv->vgpu.active;
पूर्ण

bool पूर्णांकel_vgpu_has_full_ppgtt(काष्ठा drm_i915_निजी *dev_priv)
अणु
	वापस dev_priv->vgpu.caps & VGT_CAPS_FULL_PPGTT;
पूर्ण

bool पूर्णांकel_vgpu_has_hwsp_emulation(काष्ठा drm_i915_निजी *dev_priv)
अणु
	वापस dev_priv->vgpu.caps & VGT_CAPS_HWSP_EMULATION;
पूर्ण

bool पूर्णांकel_vgpu_has_huge_gtt(काष्ठा drm_i915_निजी *dev_priv)
अणु
	वापस dev_priv->vgpu.caps & VGT_CAPS_HUGE_GTT;
पूर्ण

काष्ठा _balloon_info_ अणु
	/*
	 * There are up to 2 regions per mappable/unmappable graphic
	 * memory that might be ballooned. Here, index 0/1 is क्रम mappable
	 * graphic memory, 2/3 क्रम unmappable graphic memory.
	 */
	काष्ठा drm_mm_node space[4];
पूर्ण;

अटल काष्ठा _balloon_info_ bl_info;

अटल व्योम vgt_deballoon_space(काष्ठा i915_ggtt *ggtt,
				काष्ठा drm_mm_node *node)
अणु
	काष्ठा drm_i915_निजी *dev_priv = ggtt->vm.i915;
	अगर (!drm_mm_node_allocated(node))
		वापस;

	drm_dbg(&dev_priv->drm,
		"deballoon space: range [0x%llx - 0x%llx] %llu KiB.\n",
		node->start,
		node->start + node->size,
		node->size / 1024);

	ggtt->vm.reserved -= node->size;
	drm_mm_हटाओ_node(node);
पूर्ण

/**
 * पूर्णांकel_vgt_deballoon - deballoon reserved graphics address trunks
 * @ggtt: the global GGTT from which we reserved earlier
 *
 * This function is called to deallocate the ballooned-out graphic memory, when
 * driver is unloaded or when ballooning fails.
 */
व्योम पूर्णांकel_vgt_deballoon(काष्ठा i915_ggtt *ggtt)
अणु
	काष्ठा drm_i915_निजी *dev_priv = ggtt->vm.i915;
	पूर्णांक i;

	अगर (!पूर्णांकel_vgpu_active(ggtt->vm.i915))
		वापस;

	drm_dbg(&dev_priv->drm, "VGT deballoon.\n");

	क्रम (i = 0; i < 4; i++)
		vgt_deballoon_space(ggtt, &bl_info.space[i]);
पूर्ण

अटल पूर्णांक vgt_balloon_space(काष्ठा i915_ggtt *ggtt,
			     काष्ठा drm_mm_node *node,
			     अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	काष्ठा drm_i915_निजी *dev_priv = ggtt->vm.i915;
	अचिन्हित दीर्घ size = end - start;
	पूर्णांक ret;

	अगर (start >= end)
		वापस -EINVAL;

	drm_info(&dev_priv->drm,
		 "balloon space: range [ 0x%lx - 0x%lx ] %lu KiB.\n",
		 start, end, size / 1024);
	ret = i915_gem_gtt_reserve(&ggtt->vm, node,
				   size, start, I915_COLOR_UNEVICTABLE,
				   0);
	अगर (!ret)
		ggtt->vm.reserved += size;

	वापस ret;
पूर्ण

/**
 * पूर्णांकel_vgt_balloon - balloon out reserved graphics address trunks
 * @ggtt: the global GGTT from which to reserve
 *
 * This function is called at the initialization stage, to balloon out the
 * graphic address space allocated to other vGPUs, by marking these spaces as
 * reserved. The ballooning related knowledge(starting address and size of
 * the mappable/unmappable graphic memory) is described in the vgt_अगर काष्ठाure
 * in a reserved mmio range.
 *
 * To give an example, the drawing below depicts one typical scenario after
 * ballooning. Here the vGPU1 has 2 pieces of graphic address spaces ballooned
 * out each क्रम the mappable and the non-mappable part. From the vGPU1 poपूर्णांक of
 * view, the total size is the same as the physical one, with the start address
 * of its graphic space being zero. Yet there are some portions ballooned out(
 * the shaकरोw part, which are marked as reserved by drm allocator). From the
 * host poपूर्णांक of view, the graphic address space is partitioned by multiple
 * vGPUs in dअगरferent VMs. ::
 *
 *                         vGPU1 view         Host view
 *              0 ------> +-----------+     +-----------+
 *                ^       |###########|     |   vGPU3   |
 *                |       |###########|     +-----------+
 *                |       |###########|     |   vGPU2   |
 *                |       +-----------+     +-----------+
 *         mappable GM    | available | ==> |   vGPU1   |
 *                |       +-----------+     +-----------+
 *                |       |###########|     |           |
 *                v       |###########|     |   Host    |
 *                +=======+===========+     +===========+
 *                ^       |###########|     |   vGPU3   |
 *                |       |###########|     +-----------+
 *                |       |###########|     |   vGPU2   |
 *                |       +-----------+     +-----------+
 *       unmappable GM    | available | ==> |   vGPU1   |
 *                |       +-----------+     +-----------+
 *                |       |###########|     |           |
 *                |       |###########|     |   Host    |
 *                v       |###########|     |           |
 *  total GM size ------> +-----------+     +-----------+
 *
 * Returns:
 * zero on success, non-zero अगर configuration invalid or ballooning failed
 */
पूर्णांक पूर्णांकel_vgt_balloon(काष्ठा i915_ggtt *ggtt)
अणु
	काष्ठा drm_i915_निजी *dev_priv = ggtt->vm.i915;
	काष्ठा पूर्णांकel_uncore *uncore = &dev_priv->uncore;
	अचिन्हित दीर्घ ggtt_end = ggtt->vm.total;

	अचिन्हित दीर्घ mappable_base, mappable_size, mappable_end;
	अचिन्हित दीर्घ unmappable_base, unmappable_size, unmappable_end;
	पूर्णांक ret;

	अगर (!पूर्णांकel_vgpu_active(ggtt->vm.i915))
		वापस 0;

	mappable_base =
	  पूर्णांकel_uncore_पढ़ो(uncore, vgtअगर_reg(avail_rs.mappable_gmadr.base));
	mappable_size =
	  पूर्णांकel_uncore_पढ़ो(uncore, vgtअगर_reg(avail_rs.mappable_gmadr.size));
	unmappable_base =
	  पूर्णांकel_uncore_पढ़ो(uncore, vgtअगर_reg(avail_rs.nonmappable_gmadr.base));
	unmappable_size =
	  पूर्णांकel_uncore_पढ़ो(uncore, vgtअगर_reg(avail_rs.nonmappable_gmadr.size));

	mappable_end = mappable_base + mappable_size;
	unmappable_end = unmappable_base + unmappable_size;

	drm_info(&dev_priv->drm, "VGT ballooning configuration:\n");
	drm_info(&dev_priv->drm,
		 "Mappable graphic memory: base 0x%lx size %ldKiB\n",
		 mappable_base, mappable_size / 1024);
	drm_info(&dev_priv->drm,
		 "Unmappable graphic memory: base 0x%lx size %ldKiB\n",
		 unmappable_base, unmappable_size / 1024);

	अगर (mappable_end > ggtt->mappable_end ||
	    unmappable_base < ggtt->mappable_end ||
	    unmappable_end > ggtt_end) अणु
		drm_err(&dev_priv->drm, "Invalid ballooning configuration!\n");
		वापस -EINVAL;
	पूर्ण

	/* Unmappable graphic memory ballooning */
	अगर (unmappable_base > ggtt->mappable_end) अणु
		ret = vgt_balloon_space(ggtt, &bl_info.space[2],
					ggtt->mappable_end, unmappable_base);

		अगर (ret)
			जाओ err;
	पूर्ण

	अगर (unmappable_end < ggtt_end) अणु
		ret = vgt_balloon_space(ggtt, &bl_info.space[3],
					unmappable_end, ggtt_end);
		अगर (ret)
			जाओ err_upon_mappable;
	पूर्ण

	/* Mappable graphic memory ballooning */
	अगर (mappable_base) अणु
		ret = vgt_balloon_space(ggtt, &bl_info.space[0],
					0, mappable_base);

		अगर (ret)
			जाओ err_upon_unmappable;
	पूर्ण

	अगर (mappable_end < ggtt->mappable_end) अणु
		ret = vgt_balloon_space(ggtt, &bl_info.space[1],
					mappable_end, ggtt->mappable_end);

		अगर (ret)
			जाओ err_below_mappable;
	पूर्ण

	drm_info(&dev_priv->drm, "VGT balloon successfully\n");
	वापस 0;

err_below_mappable:
	vgt_deballoon_space(ggtt, &bl_info.space[0]);
err_upon_unmappable:
	vgt_deballoon_space(ggtt, &bl_info.space[3]);
err_upon_mappable:
	vgt_deballoon_space(ggtt, &bl_info.space[2]);
err:
	drm_err(&dev_priv->drm, "VGT balloon fail\n");
	वापस ret;
पूर्ण
