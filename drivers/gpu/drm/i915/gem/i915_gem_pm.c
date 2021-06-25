<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश "gem/i915_gem_pm.h"
#समावेश "gt/intel_gt.h"
#समावेश "gt/intel_gt_pm.h"
#समावेश "gt/intel_gt_requests.h"

#समावेश "i915_drv.h"

#अगर defined(CONFIG_X86)
#समावेश <यंत्र/smp.h>
#अन्यथा
#घोषणा wbinvd_on_all_cpus() \
	pr_warn(DRIVER_NAME ": Missing cache flush in %s\n", __func__)
#पूर्ण_अगर

व्योम i915_gem_suspend(काष्ठा drm_i915_निजी *i915)
अणु
	GEM_TRACE("%s\n", dev_name(i915->drm.dev));

	पूर्णांकel_wakeref_स्वतः(&i915->ggtt.userfault_wakeref, 0);
	flush_workqueue(i915->wq);

	/*
	 * We have to flush all the executing contexts to मुख्य memory so
	 * that they can saved in the hibernation image. To ensure the last
	 * context image is coherent, we have to चयन away from it. That
	 * leaves the i915->kernel_context still active when
	 * we actually suspend, and its image in memory may not match the GPU
	 * state. Fortunately, the kernel_context is disposable and we करो
	 * not rely on its state.
	 */
	पूर्णांकel_gt_suspend_prepare(&i915->gt);

	i915_gem_drain_मुक्तd_objects(i915);
पूर्ण

व्योम i915_gem_suspend_late(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा list_head *phases[] = अणु
		&i915->mm.shrink_list,
		&i915->mm.purge_list,
		शून्य
	पूर्ण, **phase;
	अचिन्हित दीर्घ flags;
	bool flush = false;

	/*
	 * Neither the BIOS, ourselves or any other kernel
	 * expects the प्रणाली to be in execlists mode on startup,
	 * so we need to reset the GPU back to legacy mode. And the only
	 * known way to disable logical contexts is through a GPU reset.
	 *
	 * So in order to leave the प्रणाली in a known शेष configuration,
	 * always reset the GPU upon unload and suspend. Afterwards we then
	 * clean up the GEM state tracking, flushing off the requests and
	 * leaving the प्रणाली in a known idle state.
	 *
	 * Note that is of the upmost importance that the GPU is idle and
	 * all stray ग_लिखोs are flushed *beक्रमe* we dismantle the backing
	 * storage क्रम the pinned objects.
	 *
	 * However, since we are uncertain that resetting the GPU on older
	 * machines is a good idea, we करोn't - just in हाल it leaves the
	 * machine in an unusable condition.
	 */

	पूर्णांकel_gt_suspend_late(&i915->gt);

	spin_lock_irqsave(&i915->mm.obj_lock, flags);
	क्रम (phase = phases; *phase; phase++) अणु
		list_क्रम_each_entry(obj, *phase, mm.link) अणु
			अगर (!(obj->cache_coherent & I915_BO_CACHE_COHERENT_FOR_READ))
				flush |= (obj->पढ़ो_करोमुख्यs & I915_GEM_DOMAIN_CPU) == 0;
			__start_cpu_ग_लिखो(obj); /* presume स्वतः-hibernate */
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&i915->mm.obj_lock, flags);
	अगर (flush)
		wbinvd_on_all_cpus();
पूर्ण

पूर्णांक i915_gem_मुक्तze(काष्ठा drm_i915_निजी *i915)
अणु
	/* Discard all purgeable objects, let userspace recover those as
	 * required after resuming.
	 */
	i915_gem_shrink_all(i915);

	वापस 0;
पूर्ण

पूर्णांक i915_gem_मुक्तze_late(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा drm_i915_gem_object *obj;
	पूर्णांकel_wakeref_t wakeref;

	/*
	 * Called just beक्रमe we ग_लिखो the hibernation image.
	 *
	 * We need to update the करोमुख्य tracking to reflect that the CPU
	 * will be accessing all the pages to create and restore from the
	 * hibernation, and so upon restoration those pages will be in the
	 * CPU करोमुख्य.
	 *
	 * To make sure the hibernation image contains the latest state,
	 * we update that state just beक्रमe writing out the image.
	 *
	 * To try and reduce the hibernation image, we manually shrink
	 * the objects as well, see i915_gem_मुक्तze()
	 */

	with_पूर्णांकel_runसमय_pm(&i915->runसमय_pm, wakeref)
		i915_gem_shrink(शून्य, i915, -1UL, शून्य, ~0);
	i915_gem_drain_मुक्तd_objects(i915);

	wbinvd_on_all_cpus();
	list_क्रम_each_entry(obj, &i915->mm.shrink_list, mm.link)
		__start_cpu_ग_लिखो(obj);

	वापस 0;
पूर्ण

व्योम i915_gem_resume(काष्ठा drm_i915_निजी *i915)
अणु
	GEM_TRACE("%s\n", dev_name(i915->drm.dev));

	/*
	 * As we didn't flush the kernel context beक्रमe suspend, we cannot
	 * guarantee that the context image is complete. So let's just reset
	 * it and start again.
	 */
	पूर्णांकel_gt_resume(&i915->gt);
पूर्ण
