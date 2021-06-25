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
 *    Eddie Dong <eddie.करोng@पूर्णांकel.com>
 *
 * Contributors:
 *    Niu Bing <bing.niu@पूर्णांकel.com>
 *    Zhi Wang <zhi.a.wang@पूर्णांकel.com>
 *
 */

#समावेश <linux/types.h>
#समावेश <linux/kthपढ़ो.h>

#समावेश "i915_drv.h"
#समावेश "intel_gvt.h"
#समावेश "gvt.h"
#समावेश <linux/vfपन.स>
#समावेश <linux/mdev.h>

काष्ठा पूर्णांकel_gvt_host पूर्णांकel_gvt_host;

अटल स्थिर अक्षर * स्थिर supported_hypervisors[] = अणु
	[INTEL_GVT_HYPERVISOR_XEN] = "XEN",
	[INTEL_GVT_HYPERVISOR_KVM] = "KVM",
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_gvt_ops पूर्णांकel_gvt_ops = अणु
	.emulate_cfg_पढ़ो = पूर्णांकel_vgpu_emulate_cfg_पढ़ो,
	.emulate_cfg_ग_लिखो = पूर्णांकel_vgpu_emulate_cfg_ग_लिखो,
	.emulate_mmio_पढ़ो = पूर्णांकel_vgpu_emulate_mmio_पढ़ो,
	.emulate_mmio_ग_लिखो = पूर्णांकel_vgpu_emulate_mmio_ग_लिखो,
	.vgpu_create = पूर्णांकel_gvt_create_vgpu,
	.vgpu_destroy = पूर्णांकel_gvt_destroy_vgpu,
	.vgpu_release = पूर्णांकel_gvt_release_vgpu,
	.vgpu_reset = पूर्णांकel_gvt_reset_vgpu,
	.vgpu_activate = पूर्णांकel_gvt_activate_vgpu,
	.vgpu_deactivate = पूर्णांकel_gvt_deactivate_vgpu,
	.vgpu_query_plane = पूर्णांकel_vgpu_query_plane,
	.vgpu_get_dmabuf = पूर्णांकel_vgpu_get_dmabuf,
	.ग_लिखो_protect_handler = पूर्णांकel_vgpu_page_track_handler,
	.emulate_hotplug = पूर्णांकel_vgpu_emulate_hotplug,
पूर्ण;

अटल व्योम init_device_info(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	काष्ठा पूर्णांकel_gvt_device_info *info = &gvt->device_info;
	काष्ठा pci_dev *pdev = to_pci_dev(gvt->gt->i915->drm.dev);

	info->max_support_vgpus = 8;
	info->cfg_space_size = PCI_CFG_SPACE_EXP_SIZE;
	info->mmio_size = 2 * 1024 * 1024;
	info->mmio_bar = 0;
	info->gtt_start_offset = 8 * 1024 * 1024;
	info->gtt_entry_size = 8;
	info->gtt_entry_size_shअगरt = 3;
	info->gmadr_bytes_in_cmd = 8;
	info->max_surface_size = 36 * 1024 * 1024;
	info->msi_cap_offset = pdev->msi_cap;
पूर्ण

अटल व्योम पूर्णांकel_gvt_test_and_emulate_vblank(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu;
	पूर्णांक id;

	mutex_lock(&gvt->lock);
	idr_क्रम_each_entry((&(gvt)->vgpu_idr), (vgpu), (id)) अणु
		अगर (test_and_clear_bit(INTEL_GVT_REQUEST_EMULATE_VBLANK + id,
				       (व्योम *)&gvt->service_request)) अणु
			अगर (vgpu->active)
				पूर्णांकel_vgpu_emulate_vblank(vgpu);
		पूर्ण
	पूर्ण
	mutex_unlock(&gvt->lock);
पूर्ण

अटल पूर्णांक gvt_service_thपढ़ो(व्योम *data)
अणु
	काष्ठा पूर्णांकel_gvt *gvt = (काष्ठा पूर्णांकel_gvt *)data;
	पूर्णांक ret;

	gvt_dbg_core("service thread start\n");

	जबतक (!kthपढ़ो_should_stop()) अणु
		ret = रुको_event_पूर्णांकerruptible(gvt->service_thपढ़ो_wq,
				kthपढ़ो_should_stop() || gvt->service_request);

		अगर (kthपढ़ो_should_stop())
			अवरोध;

		अगर (WARN_ONCE(ret, "service thread is waken up by signal.\n"))
			जारी;

		पूर्णांकel_gvt_test_and_emulate_vblank(gvt);

		अगर (test_bit(INTEL_GVT_REQUEST_SCHED,
				(व्योम *)&gvt->service_request) ||
			test_bit(INTEL_GVT_REQUEST_EVENT_SCHED,
					(व्योम *)&gvt->service_request)) अणु
			पूर्णांकel_gvt_schedule(gvt);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम clean_service_thपढ़ो(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	kthपढ़ो_stop(gvt->service_thपढ़ो);
पूर्ण

अटल पूर्णांक init_service_thपढ़ो(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	init_रुकोqueue_head(&gvt->service_thपढ़ो_wq);

	gvt->service_thपढ़ो = kthपढ़ो_run(gvt_service_thपढ़ो,
			gvt, "gvt_service_thread");
	अगर (IS_ERR(gvt->service_thपढ़ो)) अणु
		gvt_err("fail to start service thread.\n");
		वापस PTR_ERR(gvt->service_thपढ़ो);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * पूर्णांकel_gvt_clean_device - clean a GVT device
 * @i915: i915 निजी
 *
 * This function is called at the driver unloading stage, to मुक्त the
 * resources owned by a GVT device.
 *
 */
व्योम पूर्णांकel_gvt_clean_device(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा पूर्णांकel_gvt *gvt = fetch_and_zero(&i915->gvt);

	अगर (drm_WARN_ON(&i915->drm, !gvt))
		वापस;

	पूर्णांकel_gvt_destroy_idle_vgpu(gvt->idle_vgpu);
	पूर्णांकel_gvt_clean_vgpu_types(gvt);

	पूर्णांकel_gvt_debugfs_clean(gvt);
	clean_service_thपढ़ो(gvt);
	पूर्णांकel_gvt_clean_cmd_parser(gvt);
	पूर्णांकel_gvt_clean_sched_policy(gvt);
	पूर्णांकel_gvt_clean_workload_scheduler(gvt);
	पूर्णांकel_gvt_clean_gtt(gvt);
	पूर्णांकel_gvt_मुक्त_firmware(gvt);
	पूर्णांकel_gvt_clean_mmio_info(gvt);
	idr_destroy(&gvt->vgpu_idr);

	kमुक्त(i915->gvt);
पूर्ण

/**
 * पूर्णांकel_gvt_init_device - initialize a GVT device
 * @i915: drm i915 निजी data
 *
 * This function is called at the initialization stage, to initialize
 * necessary GVT components.
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 *
 */
पूर्णांक पूर्णांकel_gvt_init_device(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा पूर्णांकel_gvt *gvt;
	काष्ठा पूर्णांकel_vgpu *vgpu;
	पूर्णांक ret;

	अगर (drm_WARN_ON(&i915->drm, i915->gvt))
		वापस -EEXIST;

	gvt = kzalloc(माप(काष्ठा पूर्णांकel_gvt), GFP_KERNEL);
	अगर (!gvt)
		वापस -ENOMEM;

	gvt_dbg_core("init gvt device\n");

	idr_init_base(&gvt->vgpu_idr, 1);
	spin_lock_init(&gvt->scheduler.mmio_context_lock);
	mutex_init(&gvt->lock);
	mutex_init(&gvt->sched_lock);
	gvt->gt = &i915->gt;
	i915->gvt = gvt;

	init_device_info(gvt);

	ret = पूर्णांकel_gvt_setup_mmio_info(gvt);
	अगर (ret)
		जाओ out_clean_idr;

	पूर्णांकel_gvt_init_engine_mmio_context(gvt);

	ret = पूर्णांकel_gvt_load_firmware(gvt);
	अगर (ret)
		जाओ out_clean_mmio_info;

	ret = पूर्णांकel_gvt_init_irq(gvt);
	अगर (ret)
		जाओ out_मुक्त_firmware;

	ret = पूर्णांकel_gvt_init_gtt(gvt);
	अगर (ret)
		जाओ out_मुक्त_firmware;

	ret = पूर्णांकel_gvt_init_workload_scheduler(gvt);
	अगर (ret)
		जाओ out_clean_gtt;

	ret = पूर्णांकel_gvt_init_sched_policy(gvt);
	अगर (ret)
		जाओ out_clean_workload_scheduler;

	ret = पूर्णांकel_gvt_init_cmd_parser(gvt);
	अगर (ret)
		जाओ out_clean_sched_policy;

	ret = init_service_thपढ़ो(gvt);
	अगर (ret)
		जाओ out_clean_cmd_parser;

	ret = पूर्णांकel_gvt_init_vgpu_types(gvt);
	अगर (ret)
		जाओ out_clean_thपढ़ो;

	vgpu = पूर्णांकel_gvt_create_idle_vgpu(gvt);
	अगर (IS_ERR(vgpu)) अणु
		ret = PTR_ERR(vgpu);
		gvt_err("failed to create idle vgpu\n");
		जाओ out_clean_types;
	पूर्ण
	gvt->idle_vgpu = vgpu;

	पूर्णांकel_gvt_debugfs_init(gvt);

	gvt_dbg_core("gvt device initialization is done\n");
	पूर्णांकel_gvt_host.dev = i915->drm.dev;
	पूर्णांकel_gvt_host.initialized = true;
	वापस 0;

out_clean_types:
	पूर्णांकel_gvt_clean_vgpu_types(gvt);
out_clean_thपढ़ो:
	clean_service_thपढ़ो(gvt);
out_clean_cmd_parser:
	पूर्णांकel_gvt_clean_cmd_parser(gvt);
out_clean_sched_policy:
	पूर्णांकel_gvt_clean_sched_policy(gvt);
out_clean_workload_scheduler:
	पूर्णांकel_gvt_clean_workload_scheduler(gvt);
out_clean_gtt:
	पूर्णांकel_gvt_clean_gtt(gvt);
out_मुक्त_firmware:
	पूर्णांकel_gvt_मुक्त_firmware(gvt);
out_clean_mmio_info:
	पूर्णांकel_gvt_clean_mmio_info(gvt);
out_clean_idr:
	idr_destroy(&gvt->vgpu_idr);
	kमुक्त(gvt);
	i915->gvt = शून्य;
	वापस ret;
पूर्ण

पूर्णांक
पूर्णांकel_gvt_pm_resume(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	पूर्णांकel_gvt_restore_fence(gvt);
	पूर्णांकel_gvt_restore_mmio(gvt);
	पूर्णांकel_gvt_restore_ggtt(gvt);
	वापस 0;
पूर्ण

पूर्णांक
पूर्णांकel_gvt_रेजिस्टर_hypervisor(स्थिर काष्ठा पूर्णांकel_gvt_mpt *m)
अणु
	पूर्णांक ret;
	व्योम *gvt;

	अगर (!पूर्णांकel_gvt_host.initialized)
		वापस -ENODEV;

	अगर (m->type != INTEL_GVT_HYPERVISOR_KVM &&
	    m->type != INTEL_GVT_HYPERVISOR_XEN)
		वापस -EINVAL;

	/* Get a reference क्रम device model module */
	अगर (!try_module_get(THIS_MODULE))
		वापस -ENODEV;

	पूर्णांकel_gvt_host.mpt = m;
	पूर्णांकel_gvt_host.hypervisor_type = m->type;
	gvt = (व्योम *)kdev_to_i915(पूर्णांकel_gvt_host.dev)->gvt;

	ret = पूर्णांकel_gvt_hypervisor_host_init(पूर्णांकel_gvt_host.dev, gvt,
					     &पूर्णांकel_gvt_ops);
	अगर (ret < 0) अणु
		gvt_err("Failed to init %s hypervisor module\n",
			supported_hypervisors[पूर्णांकel_gvt_host.hypervisor_type]);
		module_put(THIS_MODULE);
		वापस -ENODEV;
	पूर्ण
	gvt_dbg_core("Running with hypervisor %s in host mode\n",
		     supported_hypervisors[पूर्णांकel_gvt_host.hypervisor_type]);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_gvt_रेजिस्टर_hypervisor);

व्योम
पूर्णांकel_gvt_unरेजिस्टर_hypervisor(व्योम)
अणु
	व्योम *gvt = (व्योम *)kdev_to_i915(पूर्णांकel_gvt_host.dev)->gvt;
	पूर्णांकel_gvt_hypervisor_host_निकास(पूर्णांकel_gvt_host.dev, gvt);
	module_put(THIS_MODULE);
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_gvt_unरेजिस्टर_hypervisor);
