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

#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/iommu.h>

#समावेश <drm/drm_managed.h>

#समावेश "gt/intel_gt.h"
#समावेश "gt/intel_gt_requests.h"
#समावेश "gt/mock_engine.h"
#समावेश "intel_memory_region.h"

#समावेश "mock_request.h"
#समावेश "mock_gem_device.h"
#समावेश "mock_gtt.h"
#समावेश "mock_uncore.h"
#समावेश "mock_region.h"

#समावेश "gem/selftests/mock_context.h"
#समावेश "gem/selftests/mock_gem_object.h"

व्योम mock_device_flush(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा पूर्णांकel_gt *gt = &i915->gt;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;

	करो अणु
		क्रम_each_engine(engine, gt, id)
			mock_engine_flush(engine);
	पूर्ण जबतक (पूर्णांकel_gt_retire_requests_समयout(gt, MAX_SCHEDULE_TIMEOUT));
पूर्ण

अटल व्योम mock_device_release(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dev);

	अगर (!i915->करो_release)
		जाओ out;

	mock_device_flush(i915);
	पूर्णांकel_gt_driver_हटाओ(&i915->gt);

	i915_gem_drain_workqueue(i915);
	i915_gem_drain_मुक्तd_objects(i915);

	mock_fini_ggtt(&i915->ggtt);
	destroy_workqueue(i915->wq);

	पूर्णांकel_gt_driver_late_release(&i915->gt);
	पूर्णांकel_memory_regions_driver_release(i915);

	drm_mode_config_cleanup(&i915->drm);

out:
	i915_params_मुक्त(&i915->params);
पूर्ण

अटल स्थिर काष्ठा drm_driver mock_driver = अणु
	.name = "mock",
	.driver_features = DRIVER_GEM,
	.release = mock_device_release,
पूर्ण;

अटल व्योम release_dev(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);

	kमुक्त(pdev);
पूर्ण

अटल पूर्णांक pm_करोमुख्य_resume(काष्ठा device *dev)
अणु
	वापस pm_generic_runसमय_resume(dev);
पूर्ण

अटल पूर्णांक pm_करोमुख्य_suspend(काष्ठा device *dev)
अणु
	वापस pm_generic_runसमय_suspend(dev);
पूर्ण

अटल काष्ठा dev_pm_करोमुख्य pm_करोमुख्य = अणु
	.ops = अणु
		.runसमय_suspend = pm_करोमुख्य_suspend,
		.runसमय_resume = pm_करोमुख्य_resume,
	पूर्ण,
पूर्ण;

काष्ठा drm_i915_निजी *mock_gem_device(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_IOMMU_API) && defined(CONFIG_INTEL_IOMMU)
	अटल काष्ठा dev_iommu fake_iommu = अणु .priv = (व्योम *)-1 पूर्ण;
#पूर्ण_अगर
	काष्ठा drm_i915_निजी *i915;
	काष्ठा pci_dev *pdev;

	pdev = kzalloc(माप(*pdev), GFP_KERNEL);
	अगर (!pdev)
		वापस शून्य;
	device_initialize(&pdev->dev);
	pdev->class = PCI_BASE_CLASS_DISPLAY << 16;
	pdev->dev.release = release_dev;
	dev_set_name(&pdev->dev, "mock");
	dma_coerce_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));

#अगर IS_ENABLED(CONFIG_IOMMU_API) && defined(CONFIG_INTEL_IOMMU)
	/* HACK to disable iommu क्रम the fake device; क्रमce identity mapping */
	pdev->dev.iommu = &fake_iommu;
#पूर्ण_अगर
	अगर (!devres_खोलो_group(&pdev->dev, शून्य, GFP_KERNEL)) अणु
		put_device(&pdev->dev);
		वापस शून्य;
	पूर्ण

	i915 = devm_drm_dev_alloc(&pdev->dev, &mock_driver,
				  काष्ठा drm_i915_निजी, drm);
	अगर (IS_ERR(i915)) अणु
		pr_err("Failed to allocate mock GEM device: err=%ld\n", PTR_ERR(i915));
		devres_release_group(&pdev->dev, शून्य);
		put_device(&pdev->dev);

		वापस शून्य;
	पूर्ण

	pci_set_drvdata(pdev, i915);
	i915->drm.pdev = pdev;

	dev_pm_करोमुख्य_set(&pdev->dev, &pm_करोमुख्य);
	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_करोnt_use_स्वतःsuspend(&pdev->dev);
	अगर (pm_runसमय_enabled(&pdev->dev))
		WARN_ON(pm_runसमय_get_sync(&pdev->dev));


	i915_params_copy(&i915->params, &i915_modparams);

	पूर्णांकel_runसमय_pm_init_early(&i915->runसमय_pm);

	/* Using the global GTT may ask questions about KMS users, so prepare */
	drm_mode_config_init(&i915->drm);

	mkग_लिखो_device_info(i915)->gen = -1;

	mkग_लिखो_device_info(i915)->page_sizes =
		I915_GTT_PAGE_SIZE_4K |
		I915_GTT_PAGE_SIZE_64K |
		I915_GTT_PAGE_SIZE_2M;

	mkग_लिखो_device_info(i915)->memory_regions = REGION_SMEM;
	पूर्णांकel_memory_regions_hw_probe(i915);

	mock_uncore_init(&i915->uncore, i915);

	i915_gem_init__mm(i915);
	पूर्णांकel_gt_init_early(&i915->gt, i915);
	atomic_inc(&i915->gt.wakeref.count); /* disable; no hw support */
	i915->gt.awake = -ENODEV;

	i915->wq = alloc_ordered_workqueue("mock", 0);
	अगर (!i915->wq)
		जाओ err_drv;

	mock_init_contexts(i915);

	mock_init_ggtt(i915, &i915->ggtt);
	i915->gt.vm = i915_vm_get(&i915->ggtt.vm);

	mkग_लिखो_device_info(i915)->platक्रमm_engine_mask = BIT(0);
	i915->gt.info.engine_mask = BIT(0);

	i915->gt.engine[RCS0] = mock_engine(i915, "mock", RCS0);
	अगर (!i915->gt.engine[RCS0])
		जाओ err_unlock;

	अगर (mock_engine_init(i915->gt.engine[RCS0]))
		जाओ err_context;

	__clear_bit(I915_WEDGED, &i915->gt.reset.flags);
	पूर्णांकel_engines_driver_रेजिस्टर(i915);

	i915->करो_release = true;

	वापस i915;

err_context:
	पूर्णांकel_gt_driver_हटाओ(&i915->gt);
err_unlock:
	destroy_workqueue(i915->wq);
err_drv:
	पूर्णांकel_gt_driver_late_release(&i915->gt);
	पूर्णांकel_memory_regions_driver_release(i915);
	drm_mode_config_cleanup(&i915->drm);
	mock_destroy_device(i915);

	वापस शून्य;
पूर्ण

व्योम mock_destroy_device(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा device *dev = i915->drm.dev;

	devres_release_group(dev, शून्य);
	put_device(dev);
पूर्ण
