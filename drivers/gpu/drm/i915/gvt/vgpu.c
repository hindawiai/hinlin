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
 *    Eddie Dong <eddie.करोng@पूर्णांकel.com>
 *    Kevin Tian <kevin.tian@पूर्णांकel.com>
 *
 * Contributors:
 *    Ping Gao <ping.a.gao@पूर्णांकel.com>
 *    Zhi Wang <zhi.a.wang@पूर्णांकel.com>
 *    Bing Niu <bing.niu@पूर्णांकel.com>
 *
 */

#समावेश "i915_drv.h"
#समावेश "gvt.h"
#समावेश "i915_pvinfo.h"

व्योम populate_pvinfo_page(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा drm_i915_निजी *i915 = vgpu->gvt->gt->i915;
	/* setup the ballooning inक्रमmation */
	vgpu_vreg64_t(vgpu, vgtअगर_reg(magic)) = VGT_MAGIC;
	vgpu_vreg_t(vgpu, vgtअगर_reg(version_major)) = 1;
	vgpu_vreg_t(vgpu, vgtअगर_reg(version_minor)) = 0;
	vgpu_vreg_t(vgpu, vgtअगर_reg(display_पढ़ोy)) = 0;
	vgpu_vreg_t(vgpu, vgtअगर_reg(vgt_id)) = vgpu->id;

	vgpu_vreg_t(vgpu, vgtअगर_reg(vgt_caps)) = VGT_CAPS_FULL_PPGTT;
	vgpu_vreg_t(vgpu, vgtअगर_reg(vgt_caps)) |= VGT_CAPS_HWSP_EMULATION;
	vgpu_vreg_t(vgpu, vgtअगर_reg(vgt_caps)) |= VGT_CAPS_HUGE_GTT;

	vgpu_vreg_t(vgpu, vgtअगर_reg(avail_rs.mappable_gmadr.base)) =
		vgpu_aperture_gmadr_base(vgpu);
	vgpu_vreg_t(vgpu, vgtअगर_reg(avail_rs.mappable_gmadr.size)) =
		vgpu_aperture_sz(vgpu);
	vgpu_vreg_t(vgpu, vgtअगर_reg(avail_rs.nonmappable_gmadr.base)) =
		vgpu_hidden_gmadr_base(vgpu);
	vgpu_vreg_t(vgpu, vgtअगर_reg(avail_rs.nonmappable_gmadr.size)) =
		vgpu_hidden_sz(vgpu);

	vgpu_vreg_t(vgpu, vgtअगर_reg(avail_rs.fence_num)) = vgpu_fence_sz(vgpu);

	vgpu_vreg_t(vgpu, vgtअगर_reg(cursor_x_hot)) = अच_पूर्णांक_उच्च;
	vgpu_vreg_t(vgpu, vgtअगर_reg(cursor_y_hot)) = अच_पूर्णांक_उच्च;

	gvt_dbg_core("Populate PVINFO PAGE for vGPU %d\n", vgpu->id);
	gvt_dbg_core("aperture base [GMADR] 0x%llx size 0x%llx\n",
		vgpu_aperture_gmadr_base(vgpu), vgpu_aperture_sz(vgpu));
	gvt_dbg_core("hidden base [GMADR] 0x%llx size=0x%llx\n",
		vgpu_hidden_gmadr_base(vgpu), vgpu_hidden_sz(vgpu));
	gvt_dbg_core("fence size %d\n", vgpu_fence_sz(vgpu));

	drm_WARN_ON(&i915->drm, माप(काष्ठा vgt_अगर) != VGT_PVINFO_SIZE);
पूर्ण

#घोषणा VGPU_MAX_WEIGHT 16
#घोषणा VGPU_WEIGHT(vgpu_num)	\
	(VGPU_MAX_WEIGHT / (vgpu_num))

अटल काष्ठा अणु
	अचिन्हित पूर्णांक low_mm;
	अचिन्हित पूर्णांक high_mm;
	अचिन्हित पूर्णांक fence;

	/* A vGPU with a weight of 8 will get twice as much GPU as a vGPU
	 * with a weight of 4 on a contended host, dअगरferent vGPU type has
	 * dअगरferent weight set. Legal weights range from 1 to 16.
	 */
	अचिन्हित पूर्णांक weight;
	क्रमागत पूर्णांकel_vgpu_edid edid;
	अक्षर *name;
पूर्ण vgpu_types[] = अणु
/* Fixed vGPU type table */
	अणु MB_TO_BYTES(64), MB_TO_BYTES(384), 4, VGPU_WEIGHT(8), GVT_EDID_1024_768, "8" पूर्ण,
	अणु MB_TO_BYTES(128), MB_TO_BYTES(512), 4, VGPU_WEIGHT(4), GVT_EDID_1920_1200, "4" पूर्ण,
	अणु MB_TO_BYTES(256), MB_TO_BYTES(1024), 4, VGPU_WEIGHT(2), GVT_EDID_1920_1200, "2" पूर्ण,
	अणु MB_TO_BYTES(512), MB_TO_BYTES(2048), 4, VGPU_WEIGHT(1), GVT_EDID_1920_1200, "1" पूर्ण,
पूर्ण;

/**
 * पूर्णांकel_gvt_init_vgpu_types - initialize vGPU type list
 * @gvt : GVT device
 *
 * Initialize vGPU type list based on available resource.
 *
 */
पूर्णांक पूर्णांकel_gvt_init_vgpu_types(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	अचिन्हित पूर्णांक num_types;
	अचिन्हित पूर्णांक i, low_avail, high_avail;
	अचिन्हित पूर्णांक min_low;

	/* vGPU type name is defined as GVTg_Vx_y which contains
	 * physical GPU generation type (e.g V4 as BDW server, V5 as
	 * SKL server).
	 *
	 * Depend on physical SKU resource, might see vGPU types like
	 * GVTg_V4_8, GVTg_V4_4, GVTg_V4_2, etc. We can create
	 * dअगरferent types of vGPU on same physical GPU depending on
	 * available resource. Each vGPU type will have "avail_instance"
	 * to indicate how many vGPU instance can be created क्रम this
	 * type.
	 *
	 */
	low_avail = gvt_aperture_sz(gvt) - HOST_LOW_GM_SIZE;
	high_avail = gvt_hidden_sz(gvt) - HOST_HIGH_GM_SIZE;
	num_types = ARRAY_SIZE(vgpu_types);

	gvt->types = kसुस्मृति(num_types, माप(काष्ठा पूर्णांकel_vgpu_type),
			     GFP_KERNEL);
	अगर (!gvt->types)
		वापस -ENOMEM;

	min_low = MB_TO_BYTES(32);
	क्रम (i = 0; i < num_types; ++i) अणु
		अगर (low_avail / vgpu_types[i].low_mm == 0)
			अवरोध;

		gvt->types[i].low_gm_size = vgpu_types[i].low_mm;
		gvt->types[i].high_gm_size = vgpu_types[i].high_mm;
		gvt->types[i].fence = vgpu_types[i].fence;

		अगर (vgpu_types[i].weight < 1 ||
					vgpu_types[i].weight > VGPU_MAX_WEIGHT)
			वापस -EINVAL;

		gvt->types[i].weight = vgpu_types[i].weight;
		gvt->types[i].resolution = vgpu_types[i].edid;
		gvt->types[i].avail_instance = min(low_avail / vgpu_types[i].low_mm,
						   high_avail / vgpu_types[i].high_mm);

		अगर (IS_GEN(gvt->gt->i915, 8))
			प्र_लिखो(gvt->types[i].name, "GVTg_V4_%s",
				vgpu_types[i].name);
		अन्यथा अगर (IS_GEN(gvt->gt->i915, 9))
			प्र_लिखो(gvt->types[i].name, "GVTg_V5_%s",
				vgpu_types[i].name);

		gvt_dbg_core("type[%d]: %s avail %u low %u high %u fence %u weight %u res %s\n",
			     i, gvt->types[i].name,
			     gvt->types[i].avail_instance,
			     gvt->types[i].low_gm_size,
			     gvt->types[i].high_gm_size, gvt->types[i].fence,
			     gvt->types[i].weight,
			     vgpu_edid_str(gvt->types[i].resolution));
	पूर्ण

	gvt->num_types = i;
	वापस 0;
पूर्ण

व्योम पूर्णांकel_gvt_clean_vgpu_types(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	kमुक्त(gvt->types);
पूर्ण

अटल व्योम पूर्णांकel_gvt_update_vgpu_types(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक low_gm_avail, high_gm_avail, fence_avail;
	अचिन्हित पूर्णांक low_gm_min, high_gm_min, fence_min;

	/* Need to depend on maxium hw resource size but keep on
	 * अटल config क्रम now.
	 */
	low_gm_avail = gvt_aperture_sz(gvt) - HOST_LOW_GM_SIZE -
		gvt->gm.vgpu_allocated_low_gm_size;
	high_gm_avail = gvt_hidden_sz(gvt) - HOST_HIGH_GM_SIZE -
		gvt->gm.vgpu_allocated_high_gm_size;
	fence_avail = gvt_fence_sz(gvt) - HOST_FENCE -
		gvt->fence.vgpu_allocated_fence_num;

	क्रम (i = 0; i < gvt->num_types; i++) अणु
		low_gm_min = low_gm_avail / gvt->types[i].low_gm_size;
		high_gm_min = high_gm_avail / gvt->types[i].high_gm_size;
		fence_min = fence_avail / gvt->types[i].fence;
		gvt->types[i].avail_instance = min(min(low_gm_min, high_gm_min),
						   fence_min);

		gvt_dbg_core("update type[%d]: %s avail %u low %u high %u fence %u\n",
		       i, gvt->types[i].name,
		       gvt->types[i].avail_instance, gvt->types[i].low_gm_size,
		       gvt->types[i].high_gm_size, gvt->types[i].fence);
	पूर्ण
पूर्ण

/**
 * पूर्णांकel_gvt_active_vgpu - activate a भव GPU
 * @vgpu: भव GPU
 *
 * This function is called when user wants to activate a भव GPU.
 *
 */
व्योम पूर्णांकel_gvt_activate_vgpu(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	mutex_lock(&vgpu->vgpu_lock);
	vgpu->active = true;
	mutex_unlock(&vgpu->vgpu_lock);
पूर्ण

/**
 * पूर्णांकel_gvt_deactive_vgpu - deactivate a भव GPU
 * @vgpu: भव GPU
 *
 * This function is called when user wants to deactivate a भव GPU.
 * The भव GPU will be stopped.
 *
 */
व्योम पूर्णांकel_gvt_deactivate_vgpu(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	mutex_lock(&vgpu->vgpu_lock);

	vgpu->active = false;

	अगर (atomic_पढ़ो(&vgpu->submission.running_workload_num)) अणु
		mutex_unlock(&vgpu->vgpu_lock);
		पूर्णांकel_gvt_रुको_vgpu_idle(vgpu);
		mutex_lock(&vgpu->vgpu_lock);
	पूर्ण

	पूर्णांकel_vgpu_stop_schedule(vgpu);

	mutex_unlock(&vgpu->vgpu_lock);
पूर्ण

/**
 * पूर्णांकel_gvt_release_vgpu - release a भव GPU
 * @vgpu: भव GPU
 *
 * This function is called when user wants to release a भव GPU.
 * The भव GPU will be stopped and all runसमय inक्रमmation will be
 * destroyed.
 *
 */
व्योम पूर्णांकel_gvt_release_vgpu(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	पूर्णांकel_gvt_deactivate_vgpu(vgpu);

	mutex_lock(&vgpu->vgpu_lock);
	vgpu->d3_entered = false;
	पूर्णांकel_vgpu_clean_workloads(vgpu, ALL_ENGINES);
	पूर्णांकel_vgpu_dmabuf_cleanup(vgpu);
	mutex_unlock(&vgpu->vgpu_lock);
पूर्ण

/**
 * पूर्णांकel_gvt_destroy_vgpu - destroy a भव GPU
 * @vgpu: भव GPU
 *
 * This function is called when user wants to destroy a भव GPU.
 *
 */
व्योम पूर्णांकel_gvt_destroy_vgpu(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	काष्ठा drm_i915_निजी *i915 = gvt->gt->i915;

	drm_WARN(&i915->drm, vgpu->active, "vGPU is still active!\n");

	/*
	 * हटाओ idr first so later clean can judge अगर need to stop
	 * service अगर no active vgpu.
	 */
	mutex_lock(&gvt->lock);
	idr_हटाओ(&gvt->vgpu_idr, vgpu->id);
	mutex_unlock(&gvt->lock);

	mutex_lock(&vgpu->vgpu_lock);
	पूर्णांकel_gvt_debugfs_हटाओ_vgpu(vgpu);
	पूर्णांकel_vgpu_clean_sched_policy(vgpu);
	पूर्णांकel_vgpu_clean_submission(vgpu);
	पूर्णांकel_vgpu_clean_display(vgpu);
	पूर्णांकel_vgpu_clean_opregion(vgpu);
	पूर्णांकel_vgpu_reset_ggtt(vgpu, true);
	पूर्णांकel_vgpu_clean_gtt(vgpu);
	पूर्णांकel_gvt_hypervisor_detach_vgpu(vgpu);
	पूर्णांकel_vgpu_मुक्त_resource(vgpu);
	पूर्णांकel_vgpu_clean_mmio(vgpu);
	पूर्णांकel_vgpu_dmabuf_cleanup(vgpu);
	mutex_unlock(&vgpu->vgpu_lock);

	mutex_lock(&gvt->lock);
	पूर्णांकel_gvt_update_vgpu_types(gvt);
	mutex_unlock(&gvt->lock);

	vमुक्त(vgpu);
पूर्ण

#घोषणा IDLE_VGPU_IDR 0

/**
 * पूर्णांकel_gvt_create_idle_vgpu - create an idle भव GPU
 * @gvt: GVT device
 *
 * This function is called when user wants to create an idle भव GPU.
 *
 * Returns:
 * poपूर्णांकer to पूर्णांकel_vgpu, error poपूर्णांकer अगर failed.
 */
काष्ठा पूर्णांकel_vgpu *पूर्णांकel_gvt_create_idle_vgpu(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu;
	क्रमागत पूर्णांकel_engine_id i;
	पूर्णांक ret;

	vgpu = vzalloc(माप(*vgpu));
	अगर (!vgpu)
		वापस ERR_PTR(-ENOMEM);

	vgpu->id = IDLE_VGPU_IDR;
	vgpu->gvt = gvt;
	mutex_init(&vgpu->vgpu_lock);

	क्रम (i = 0; i < I915_NUM_ENGINES; i++)
		INIT_LIST_HEAD(&vgpu->submission.workload_q_head[i]);

	ret = पूर्णांकel_vgpu_init_sched_policy(vgpu);
	अगर (ret)
		जाओ out_मुक्त_vgpu;

	vgpu->active = false;

	वापस vgpu;

out_मुक्त_vgpu:
	vमुक्त(vgpu);
	वापस ERR_PTR(ret);
पूर्ण

/**
 * पूर्णांकel_gvt_destroy_vgpu - destroy an idle भव GPU
 * @vgpu: भव GPU
 *
 * This function is called when user wants to destroy an idle भव GPU.
 *
 */
व्योम पूर्णांकel_gvt_destroy_idle_vgpu(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	mutex_lock(&vgpu->vgpu_lock);
	पूर्णांकel_vgpu_clean_sched_policy(vgpu);
	mutex_unlock(&vgpu->vgpu_lock);

	vमुक्त(vgpu);
पूर्ण

अटल काष्ठा पूर्णांकel_vgpu *__पूर्णांकel_gvt_create_vgpu(काष्ठा पूर्णांकel_gvt *gvt,
		काष्ठा पूर्णांकel_vgpu_creation_params *param)
अणु
	काष्ठा drm_i915_निजी *dev_priv = gvt->gt->i915;
	काष्ठा पूर्णांकel_vgpu *vgpu;
	पूर्णांक ret;

	gvt_dbg_core("handle %llu low %llu MB high %llu MB fence %llu\n",
			param->handle, param->low_gm_sz, param->high_gm_sz,
			param->fence_sz);

	vgpu = vzalloc(माप(*vgpu));
	अगर (!vgpu)
		वापस ERR_PTR(-ENOMEM);

	ret = idr_alloc(&gvt->vgpu_idr, vgpu, IDLE_VGPU_IDR + 1, GVT_MAX_VGPU,
		GFP_KERNEL);
	अगर (ret < 0)
		जाओ out_मुक्त_vgpu;

	vgpu->id = ret;
	vgpu->handle = param->handle;
	vgpu->gvt = gvt;
	vgpu->sched_ctl.weight = param->weight;
	mutex_init(&vgpu->vgpu_lock);
	mutex_init(&vgpu->dmabuf_lock);
	INIT_LIST_HEAD(&vgpu->dmabuf_obj_list_head);
	INIT_RADIX_TREE(&vgpu->page_track_tree, GFP_KERNEL);
	idr_init_base(&vgpu->object_idr, 1);
	पूर्णांकel_vgpu_init_cfg_space(vgpu, param->primary);
	vgpu->d3_entered = false;

	ret = पूर्णांकel_vgpu_init_mmio(vgpu);
	अगर (ret)
		जाओ out_clean_idr;

	ret = पूर्णांकel_vgpu_alloc_resource(vgpu, param);
	अगर (ret)
		जाओ out_clean_vgpu_mmio;

	populate_pvinfo_page(vgpu);

	ret = पूर्णांकel_gvt_hypervisor_attach_vgpu(vgpu);
	अगर (ret)
		जाओ out_clean_vgpu_resource;

	ret = पूर्णांकel_vgpu_init_gtt(vgpu);
	अगर (ret)
		जाओ out_detach_hypervisor_vgpu;

	ret = पूर्णांकel_vgpu_init_opregion(vgpu);
	अगर (ret)
		जाओ out_clean_gtt;

	ret = पूर्णांकel_vgpu_init_display(vgpu, param->resolution);
	अगर (ret)
		जाओ out_clean_opregion;

	ret = पूर्णांकel_vgpu_setup_submission(vgpu);
	अगर (ret)
		जाओ out_clean_display;

	ret = पूर्णांकel_vgpu_init_sched_policy(vgpu);
	अगर (ret)
		जाओ out_clean_submission;

	पूर्णांकel_gvt_debugfs_add_vgpu(vgpu);

	ret = पूर्णांकel_gvt_hypervisor_set_opregion(vgpu);
	अगर (ret)
		जाओ out_clean_sched_policy;

	अगर (IS_BROADWELL(dev_priv) || IS_BROXTON(dev_priv))
		ret = पूर्णांकel_gvt_hypervisor_set_edid(vgpu, PORT_B);
	अन्यथा
		ret = पूर्णांकel_gvt_hypervisor_set_edid(vgpu, PORT_D);
	अगर (ret)
		जाओ out_clean_sched_policy;

	वापस vgpu;

out_clean_sched_policy:
	पूर्णांकel_vgpu_clean_sched_policy(vgpu);
out_clean_submission:
	पूर्णांकel_vgpu_clean_submission(vgpu);
out_clean_display:
	पूर्णांकel_vgpu_clean_display(vgpu);
out_clean_opregion:
	पूर्णांकel_vgpu_clean_opregion(vgpu);
out_clean_gtt:
	पूर्णांकel_vgpu_clean_gtt(vgpu);
out_detach_hypervisor_vgpu:
	पूर्णांकel_gvt_hypervisor_detach_vgpu(vgpu);
out_clean_vgpu_resource:
	पूर्णांकel_vgpu_मुक्त_resource(vgpu);
out_clean_vgpu_mmio:
	पूर्णांकel_vgpu_clean_mmio(vgpu);
out_clean_idr:
	idr_हटाओ(&gvt->vgpu_idr, vgpu->id);
out_मुक्त_vgpu:
	vमुक्त(vgpu);
	वापस ERR_PTR(ret);
पूर्ण

/**
 * पूर्णांकel_gvt_create_vgpu - create a भव GPU
 * @gvt: GVT device
 * @type: type of the vGPU to create
 *
 * This function is called when user wants to create a भव GPU.
 *
 * Returns:
 * poपूर्णांकer to पूर्णांकel_vgpu, error poपूर्णांकer अगर failed.
 */
काष्ठा पूर्णांकel_vgpu *पूर्णांकel_gvt_create_vgpu(काष्ठा पूर्णांकel_gvt *gvt,
				काष्ठा पूर्णांकel_vgpu_type *type)
अणु
	काष्ठा पूर्णांकel_vgpu_creation_params param;
	काष्ठा पूर्णांकel_vgpu *vgpu;

	param.handle = 0;
	param.primary = 1;
	param.low_gm_sz = type->low_gm_size;
	param.high_gm_sz = type->high_gm_size;
	param.fence_sz = type->fence;
	param.weight = type->weight;
	param.resolution = type->resolution;

	/* XXX current param based on MB */
	param.low_gm_sz = BYTES_TO_MB(param.low_gm_sz);
	param.high_gm_sz = BYTES_TO_MB(param.high_gm_sz);

	mutex_lock(&gvt->lock);
	vgpu = __पूर्णांकel_gvt_create_vgpu(gvt, &param);
	अगर (!IS_ERR(vgpu)) अणु
		/* calculate left instance change क्रम types */
		पूर्णांकel_gvt_update_vgpu_types(gvt);
		पूर्णांकel_gvt_update_reg_whitelist(vgpu);
	पूर्ण
	mutex_unlock(&gvt->lock);

	वापस vgpu;
पूर्ण

/**
 * पूर्णांकel_gvt_reset_vgpu_locked - reset a भव GPU by DMLR or GT reset
 * @vgpu: भव GPU
 * @dmlr: vGPU Device Model Level Reset or GT Reset
 * @engine_mask: engines to reset क्रम GT reset
 *
 * This function is called when user wants to reset a भव GPU through
 * device model reset or GT reset. The caller should hold the vgpu lock.
 *
 * vGPU Device Model Level Reset (DMLR) simulates the PCI level reset to reset
 * the whole vGPU to शेष state as when it is created. This vGPU function
 * is required both क्रम functionary and security concerns.The ultimate goal
 * of vGPU FLR is that reuse a vGPU instance by भव machines. When we
 * assign a vGPU to a भव machine we must isse such reset first.
 *
 * Full GT Reset and Per-Engine GT Reset are soft reset flow क्रम GPU engines
 * (Render, Blitter, Video, Video Enhancement). It is defined by GPU Spec.
 * Unlike the FLR, GT reset only reset particular resource of a vGPU per
 * the reset request. Guest driver can issue a GT reset by programming the
 * भव GDRST रेजिस्टर to reset specअगरic भव GPU engine or all
 * engines.
 *
 * The parameter dev_level is to identअगरy अगर we will करो DMLR or GT reset.
 * The parameter engine_mask is to specअगरic the engines that need to be
 * resetted. If value ALL_ENGINES is given क्रम engine_mask, it means
 * the caller requests a full GT reset that we will reset all भव
 * GPU engines. For FLR, engine_mask is ignored.
 */
व्योम पूर्णांकel_gvt_reset_vgpu_locked(काष्ठा पूर्णांकel_vgpu *vgpu, bool dmlr,
				 पूर्णांकel_engine_mask_t engine_mask)
अणु
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	काष्ठा पूर्णांकel_gvt_workload_scheduler *scheduler = &gvt->scheduler;
	पूर्णांकel_engine_mask_t resetting_eng = dmlr ? ALL_ENGINES : engine_mask;

	gvt_dbg_core("------------------------------------------\n");
	gvt_dbg_core("resseting vgpu%d, dmlr %d, engine_mask %08x\n",
		     vgpu->id, dmlr, engine_mask);

	vgpu->resetting_eng = resetting_eng;

	पूर्णांकel_vgpu_stop_schedule(vgpu);
	/*
	 * The current_vgpu will set to शून्य after stopping the
	 * scheduler when the reset is triggered by current vgpu.
	 */
	अगर (scheduler->current_vgpu == शून्य) अणु
		mutex_unlock(&vgpu->vgpu_lock);
		पूर्णांकel_gvt_रुको_vgpu_idle(vgpu);
		mutex_lock(&vgpu->vgpu_lock);
	पूर्ण

	पूर्णांकel_vgpu_reset_submission(vgpu, resetting_eng);
	/* full GPU reset or device model level reset */
	अगर (engine_mask == ALL_ENGINES || dmlr) अणु
		पूर्णांकel_vgpu_select_submission_ops(vgpu, ALL_ENGINES, 0);
		अगर (engine_mask == ALL_ENGINES)
			पूर्णांकel_vgpu_invalidate_ppgtt(vgpu);
		/*fence will not be reset during भव reset */
		अगर (dmlr) अणु
			अगर(!vgpu->d3_entered) अणु
				पूर्णांकel_vgpu_invalidate_ppgtt(vgpu);
				पूर्णांकel_vgpu_destroy_all_ppgtt_mm(vgpu);
			पूर्ण
			पूर्णांकel_vgpu_reset_ggtt(vgpu, true);
			पूर्णांकel_vgpu_reset_resource(vgpu);
		पूर्ण

		पूर्णांकel_vgpu_reset_mmio(vgpu, dmlr);
		populate_pvinfo_page(vgpu);

		अगर (dmlr) अणु
			पूर्णांकel_vgpu_reset_display(vgpu);
			पूर्णांकel_vgpu_reset_cfg_space(vgpu);
			/* only reset the failsafe mode when dmlr reset */
			vgpu->failsafe = false;
			/*
			 * PCI_D0 is set beक्रमe dmlr, so reset d3_entered here
			 * after करोne using.
			 */
			अगर(vgpu->d3_entered)
				vgpu->d3_entered = false;
			अन्यथा
				vgpu->pv_notअगरied = false;
		पूर्ण
	पूर्ण

	vgpu->resetting_eng = 0;
	gvt_dbg_core("reset vgpu%d done\n", vgpu->id);
	gvt_dbg_core("------------------------------------------\n");
पूर्ण

/**
 * पूर्णांकel_gvt_reset_vgpu - reset a भव GPU (Function Level)
 * @vgpu: भव GPU
 *
 * This function is called when user wants to reset a भव GPU.
 *
 */
व्योम पूर्णांकel_gvt_reset_vgpu(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	mutex_lock(&vgpu->vgpu_lock);
	पूर्णांकel_gvt_reset_vgpu_locked(vgpu, true, 0);
	mutex_unlock(&vgpu->vgpu_lock);
पूर्ण
