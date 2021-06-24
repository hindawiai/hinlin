<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Christian Kथघnig
 */

#समावेश "amdgpu.h"

अटल अंतरभूत काष्ठा amdgpu_gtt_mgr *to_gtt_mgr(काष्ठा tपंचांग_resource_manager *man)
अणु
	वापस container_of(man, काष्ठा amdgpu_gtt_mgr, manager);
पूर्ण

काष्ठा amdgpu_gtt_node अणु
	काष्ठा drm_mm_node node;
	काष्ठा tपंचांग_buffer_object *tbo;
पूर्ण;

/**
 * DOC: mem_info_gtt_total
 *
 * The amdgpu driver provides a sysfs API क्रम reporting current total size of
 * the GTT.
 * The file mem_info_gtt_total is used क्रम this, and वापसs the total size of
 * the GTT block, in bytes
 */
अटल sमाप_प्रकार amdgpu_mem_info_gtt_total_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);
	काष्ठा tपंचांग_resource_manager *man = tपंचांग_manager_type(&adev->mman.bdev, TTM_PL_TT);

	वापस sysfs_emit(buf, "%llu\n", man->size * PAGE_SIZE);
पूर्ण

/**
 * DOC: mem_info_gtt_used
 *
 * The amdgpu driver provides a sysfs API क्रम reporting current total amount of
 * used GTT.
 * The file mem_info_gtt_used is used क्रम this, and वापसs the current used
 * size of the GTT block, in bytes
 */
अटल sमाप_प्रकार amdgpu_mem_info_gtt_used_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);
	काष्ठा tपंचांग_resource_manager *man = tपंचांग_manager_type(&adev->mman.bdev, TTM_PL_TT);

	वापस sysfs_emit(buf, "%llu\n", amdgpu_gtt_mgr_usage(man));
पूर्ण

अटल DEVICE_ATTR(mem_info_gtt_total, S_IRUGO,
	           amdgpu_mem_info_gtt_total_show, शून्य);
अटल DEVICE_ATTR(mem_info_gtt_used, S_IRUGO,
	           amdgpu_mem_info_gtt_used_show, शून्य);

अटल स्थिर काष्ठा tपंचांग_resource_manager_func amdgpu_gtt_mgr_func;
/**
 * amdgpu_gtt_mgr_init - init GTT manager and DRM MM
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @gtt_size: maximum size of GTT
 *
 * Allocate and initialize the GTT manager.
 */
पूर्णांक amdgpu_gtt_mgr_init(काष्ठा amdgpu_device *adev, uपूर्णांक64_t gtt_size)
अणु
	काष्ठा amdgpu_gtt_mgr *mgr = &adev->mman.gtt_mgr;
	काष्ठा tपंचांग_resource_manager *man = &mgr->manager;
	uपूर्णांक64_t start, size;
	पूर्णांक ret;

	man->use_tt = true;
	man->func = &amdgpu_gtt_mgr_func;

	tपंचांग_resource_manager_init(man, gtt_size >> PAGE_SHIFT);

	start = AMDGPU_GTT_MAX_TRANSFER_SIZE * AMDGPU_GTT_NUM_TRANSFER_WINDOWS;
	size = (adev->gmc.gart_size >> PAGE_SHIFT) - start;
	drm_mm_init(&mgr->mm, start, size);
	spin_lock_init(&mgr->lock);
	atomic64_set(&mgr->available, gtt_size >> PAGE_SHIFT);

	ret = device_create_file(adev->dev, &dev_attr_mem_info_gtt_total);
	अगर (ret) अणु
		DRM_ERROR("Failed to create device file mem_info_gtt_total\n");
		वापस ret;
	पूर्ण
	ret = device_create_file(adev->dev, &dev_attr_mem_info_gtt_used);
	अगर (ret) अणु
		DRM_ERROR("Failed to create device file mem_info_gtt_used\n");
		वापस ret;
	पूर्ण

	tपंचांग_set_driver_manager(&adev->mman.bdev, TTM_PL_TT, &mgr->manager);
	tपंचांग_resource_manager_set_used(man, true);
	वापस 0;
पूर्ण

/**
 * amdgpu_gtt_mgr_fini - मुक्त and destroy GTT manager
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Destroy and मुक्त the GTT manager, वापसs -EBUSY अगर ranges are still
 * allocated inside it.
 */
व्योम amdgpu_gtt_mgr_fini(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_gtt_mgr *mgr = &adev->mman.gtt_mgr;
	काष्ठा tपंचांग_resource_manager *man = &mgr->manager;
	पूर्णांक ret;

	tपंचांग_resource_manager_set_used(man, false);

	ret = tपंचांग_resource_manager_evict_all(&adev->mman.bdev, man);
	अगर (ret)
		वापस;

	spin_lock(&mgr->lock);
	drm_mm_takeकरोwn(&mgr->mm);
	spin_unlock(&mgr->lock);

	device_हटाओ_file(adev->dev, &dev_attr_mem_info_gtt_total);
	device_हटाओ_file(adev->dev, &dev_attr_mem_info_gtt_used);

	tपंचांग_resource_manager_cleanup(man);
	tपंचांग_set_driver_manager(&adev->mman.bdev, TTM_PL_TT, शून्य);
पूर्ण

/**
 * amdgpu_gtt_mgr_has_gart_addr - Check अगर mem has address space
 *
 * @mem: the mem object to check
 *
 * Check अगर a mem object has alपढ़ोy address space allocated.
 */
bool amdgpu_gtt_mgr_has_gart_addr(काष्ठा tपंचांग_resource *mem)
अणु
	वापस mem->mm_node != शून्य;
पूर्ण

/**
 * amdgpu_gtt_mgr_new - allocate a new node
 *
 * @man: TTM memory type manager
 * @tbo: TTM BO we need this range क्रम
 * @place: placement flags and restrictions
 * @mem: the resulting mem object
 *
 * Dummy, allocate the node but no space क्रम it yet.
 */
अटल पूर्णांक amdgpu_gtt_mgr_new(काष्ठा tपंचांग_resource_manager *man,
			      काष्ठा tपंचांग_buffer_object *tbo,
			      स्थिर काष्ठा tपंचांग_place *place,
			      काष्ठा tपंचांग_resource *mem)
अणु
	काष्ठा amdgpu_gtt_mgr *mgr = to_gtt_mgr(man);
	काष्ठा amdgpu_gtt_node *node;
	पूर्णांक r;

	spin_lock(&mgr->lock);
	अगर ((&tbo->mem == mem || tbo->mem.mem_type != TTM_PL_TT) &&
	    atomic64_पढ़ो(&mgr->available) < mem->num_pages) अणु
		spin_unlock(&mgr->lock);
		वापस -ENOSPC;
	पूर्ण
	atomic64_sub(mem->num_pages, &mgr->available);
	spin_unlock(&mgr->lock);

	अगर (!place->lpfn) अणु
		mem->mm_node = शून्य;
		mem->start = AMDGPU_BO_INVALID_OFFSET;
		वापस 0;
	पूर्ण

	node = kzalloc(माप(*node), GFP_KERNEL);
	अगर (!node) अणु
		r = -ENOMEM;
		जाओ err_out;
	पूर्ण

	node->tbo = tbo;

	spin_lock(&mgr->lock);
	r = drm_mm_insert_node_in_range(&mgr->mm, &node->node, mem->num_pages,
					mem->page_alignment, 0, place->fpfn,
					place->lpfn, DRM_MM_INSERT_BEST);
	spin_unlock(&mgr->lock);

	अगर (unlikely(r))
		जाओ err_मुक्त;

	mem->mm_node = node;
	mem->start = node->node.start;

	वापस 0;

err_मुक्त:
	kमुक्त(node);

err_out:
	atomic64_add(mem->num_pages, &mgr->available);

	वापस r;
पूर्ण

/**
 * amdgpu_gtt_mgr_del - मुक्त ranges
 *
 * @man: TTM memory type manager
 * @mem: TTM memory object
 *
 * Free the allocated GTT again.
 */
अटल व्योम amdgpu_gtt_mgr_del(काष्ठा tपंचांग_resource_manager *man,
			       काष्ठा tपंचांग_resource *mem)
अणु
	काष्ठा amdgpu_gtt_mgr *mgr = to_gtt_mgr(man);
	काष्ठा amdgpu_gtt_node *node = mem->mm_node;

	अगर (node) अणु
		spin_lock(&mgr->lock);
		drm_mm_हटाओ_node(&node->node);
		spin_unlock(&mgr->lock);
		kमुक्त(node);
	पूर्ण

	atomic64_add(mem->num_pages, &mgr->available);
पूर्ण

/**
 * amdgpu_gtt_mgr_usage - वापस usage of GTT करोमुख्य
 *
 * @man: TTM memory type manager
 *
 * Return how many bytes are used in the GTT करोमुख्य
 */
uपूर्णांक64_t amdgpu_gtt_mgr_usage(काष्ठा tपंचांग_resource_manager *man)
अणु
	काष्ठा amdgpu_gtt_mgr *mgr = to_gtt_mgr(man);
	s64 result = man->size - atomic64_पढ़ो(&mgr->available);

	वापस (result > 0 ? result : 0) * PAGE_SIZE;
पूर्ण

पूर्णांक amdgpu_gtt_mgr_recover(काष्ठा tपंचांग_resource_manager *man)
अणु
	काष्ठा amdgpu_gtt_mgr *mgr = to_gtt_mgr(man);
	काष्ठा amdgpu_gtt_node *node;
	काष्ठा drm_mm_node *mm_node;
	पूर्णांक r = 0;

	spin_lock(&mgr->lock);
	drm_mm_क्रम_each_node(mm_node, &mgr->mm) अणु
		node = container_of(mm_node, काष्ठा amdgpu_gtt_node, node);
		r = amdgpu_tपंचांग_recover_gart(node->tbo);
		अगर (r)
			अवरोध;
	पूर्ण
	spin_unlock(&mgr->lock);

	वापस r;
पूर्ण

/**
 * amdgpu_gtt_mgr_debug - dump VRAM table
 *
 * @man: TTM memory type manager
 * @prपूर्णांकer: DRM prपूर्णांकer to use
 *
 * Dump the table content using prपूर्णांकk.
 */
अटल व्योम amdgpu_gtt_mgr_debug(काष्ठा tपंचांग_resource_manager *man,
				 काष्ठा drm_prपूर्णांकer *prपूर्णांकer)
अणु
	काष्ठा amdgpu_gtt_mgr *mgr = to_gtt_mgr(man);

	spin_lock(&mgr->lock);
	drm_mm_prपूर्णांक(&mgr->mm, prपूर्णांकer);
	spin_unlock(&mgr->lock);

	drm_म_लिखो(prपूर्णांकer, "man size:%llu pages, gtt available:%lld pages, usage:%lluMB\n",
		   man->size, (u64)atomic64_पढ़ो(&mgr->available),
		   amdgpu_gtt_mgr_usage(man) >> 20);
पूर्ण

अटल स्थिर काष्ठा tपंचांग_resource_manager_func amdgpu_gtt_mgr_func = अणु
	.alloc = amdgpu_gtt_mgr_new,
	.मुक्त = amdgpu_gtt_mgr_del,
	.debug = amdgpu_gtt_mgr_debug
पूर्ण;
