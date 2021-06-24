<शैली गुरु>
/*
 * Copyright 2007-8 Advanced Micro Devices, Inc.
 * Copyright 2008 Red Hat Inc.
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
 * Authors: Dave Airlie
 *          Alex Deucher
 */

#समावेश <drm/amdgpu_drm.h>
#समावेश "amdgpu.h"
#समावेश "amdgpu_i2c.h"
#समावेश "atom.h"
#समावेश "amdgpu_connectors.h"
#समावेश "amdgpu_display.h"
#समावेश <यंत्र/भाग64.h>

#समावेश <linux/pci.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_vblank.h>

अटल व्योम amdgpu_display_flip_callback(काष्ठा dma_fence *f,
					 काष्ठा dma_fence_cb *cb)
अणु
	काष्ठा amdgpu_flip_work *work =
		container_of(cb, काष्ठा amdgpu_flip_work, cb);

	dma_fence_put(f);
	schedule_work(&work->flip_work.work);
पूर्ण

अटल bool amdgpu_display_flip_handle_fence(काष्ठा amdgpu_flip_work *work,
					     काष्ठा dma_fence **f)
अणु
	काष्ठा dma_fence *fence= *f;

	अगर (fence == शून्य)
		वापस false;

	*f = शून्य;

	अगर (!dma_fence_add_callback(fence, &work->cb,
				    amdgpu_display_flip_callback))
		वापस true;

	dma_fence_put(fence);
	वापस false;
पूर्ण

अटल व्योम amdgpu_display_flip_work_func(काष्ठा work_काष्ठा *__work)
अणु
	काष्ठा delayed_work *delayed_work =
		container_of(__work, काष्ठा delayed_work, work);
	काष्ठा amdgpu_flip_work *work =
		container_of(delayed_work, काष्ठा amdgpu_flip_work, flip_work);
	काष्ठा amdgpu_device *adev = work->adev;
	काष्ठा amdgpu_crtc *amdgpu_crtc = adev->mode_info.crtcs[work->crtc_id];

	काष्ठा drm_crtc *crtc = &amdgpu_crtc->base;
	अचिन्हित दीर्घ flags;
	अचिन्हित i;
	पूर्णांक vpos, hpos;

	अगर (amdgpu_display_flip_handle_fence(work, &work->excl))
		वापस;

	क्रम (i = 0; i < work->shared_count; ++i)
		अगर (amdgpu_display_flip_handle_fence(work, &work->shared[i]))
			वापस;

	/* Wait until we're out of the vertical blank period beक्रमe the one
	 * targeted by the flip
	 */
	अगर (amdgpu_crtc->enabled &&
	    (amdgpu_display_get_crtc_scanoutpos(adev_to_drm(adev), work->crtc_id, 0,
						&vpos, &hpos, शून्य, शून्य,
						&crtc->hwmode)
	     & (DRM_SCANOUTPOS_VALID | DRM_SCANOUTPOS_IN_VBLANK)) ==
	    (DRM_SCANOUTPOS_VALID | DRM_SCANOUTPOS_IN_VBLANK) &&
	    (पूर्णांक)(work->target_vblank -
		  amdgpu_get_vblank_counter_kms(crtc)) > 0) अणु
		schedule_delayed_work(&work->flip_work, usecs_to_jअगरfies(1000));
		वापस;
	पूर्ण

	/* We borrow the event spin lock क्रम protecting flip_status */
	spin_lock_irqsave(&crtc->dev->event_lock, flags);

	/* Do the flip (mmio) */
	adev->mode_info.funcs->page_flip(adev, work->crtc_id, work->base, work->async);

	/* Set the flip status */
	amdgpu_crtc->pflip_status = AMDGPU_FLIP_SUBMITTED;
	spin_unlock_irqrestore(&crtc->dev->event_lock, flags);


	DRM_DEBUG_DRIVER("crtc:%d[%p], pflip_stat:AMDGPU_FLIP_SUBMITTED, work: %p,\n",
					 amdgpu_crtc->crtc_id, amdgpu_crtc, work);

पूर्ण

/*
 * Handle unpin events outside the पूर्णांकerrupt handler proper.
 */
अटल व्योम amdgpu_display_unpin_work_func(काष्ठा work_काष्ठा *__work)
अणु
	काष्ठा amdgpu_flip_work *work =
		container_of(__work, काष्ठा amdgpu_flip_work, unpin_work);
	पूर्णांक r;

	/* unpin of the old buffer */
	r = amdgpu_bo_reserve(work->old_abo, true);
	अगर (likely(r == 0)) अणु
		amdgpu_bo_unpin(work->old_abo);
		amdgpu_bo_unreserve(work->old_abo);
	पूर्ण अन्यथा
		DRM_ERROR("failed to reserve buffer after flip\n");

	amdgpu_bo_unref(&work->old_abo);
	kमुक्त(work->shared);
	kमुक्त(work);
पूर्ण

पूर्णांक amdgpu_display_crtc_page_flip_target(काष्ठा drm_crtc *crtc,
				काष्ठा drm_framebuffer *fb,
				काष्ठा drm_pending_vblank_event *event,
				uपूर्णांक32_t page_flip_flags, uपूर्णांक32_t target,
				काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	काष्ठा drm_gem_object *obj;
	काष्ठा amdgpu_flip_work *work;
	काष्ठा amdgpu_bo *new_abo;
	अचिन्हित दीर्घ flags;
	u64 tiling_flags;
	पूर्णांक i, r;

	work = kzalloc(माप *work, GFP_KERNEL);
	अगर (work == शून्य)
		वापस -ENOMEM;

	INIT_DELAYED_WORK(&work->flip_work, amdgpu_display_flip_work_func);
	INIT_WORK(&work->unpin_work, amdgpu_display_unpin_work_func);

	work->event = event;
	work->adev = adev;
	work->crtc_id = amdgpu_crtc->crtc_id;
	work->async = (page_flip_flags & DRM_MODE_PAGE_FLIP_ASYNC) != 0;

	/* schedule unpin of the old buffer */
	obj = crtc->primary->fb->obj[0];

	/* take a reference to the old object */
	work->old_abo = gem_to_amdgpu_bo(obj);
	amdgpu_bo_ref(work->old_abo);

	obj = fb->obj[0];
	new_abo = gem_to_amdgpu_bo(obj);

	/* pin the new buffer */
	r = amdgpu_bo_reserve(new_abo, false);
	अगर (unlikely(r != 0)) अणु
		DRM_ERROR("failed to reserve new abo buffer before flip\n");
		जाओ cleanup;
	पूर्ण

	अगर (!adev->enable_भव_display) अणु
		r = amdgpu_bo_pin(new_abo,
				  amdgpu_display_supported_करोमुख्यs(adev, new_abo->flags));
		अगर (unlikely(r != 0)) अणु
			DRM_ERROR("failed to pin new abo buffer before flip\n");
			जाओ unreserve;
		पूर्ण
	पूर्ण

	r = amdgpu_tपंचांग_alloc_gart(&new_abo->tbo);
	अगर (unlikely(r != 0)) अणु
		DRM_ERROR("%p bind failed\n", new_abo);
		जाओ unpin;
	पूर्ण

	r = dma_resv_get_fences_rcu(new_abo->tbo.base.resv, &work->excl,
					      &work->shared_count,
					      &work->shared);
	अगर (unlikely(r != 0)) अणु
		DRM_ERROR("failed to get fences for buffer\n");
		जाओ unpin;
	पूर्ण

	amdgpu_bo_get_tiling_flags(new_abo, &tiling_flags);
	amdgpu_bo_unreserve(new_abo);

	अगर (!adev->enable_भव_display)
		work->base = amdgpu_bo_gpu_offset(new_abo);
	work->target_vblank = target - (uपूर्णांक32_t)drm_crtc_vblank_count(crtc) +
		amdgpu_get_vblank_counter_kms(crtc);

	/* we borrow the event spin lock क्रम protecting flip_wrok */
	spin_lock_irqsave(&crtc->dev->event_lock, flags);
	अगर (amdgpu_crtc->pflip_status != AMDGPU_FLIP_NONE) अणु
		DRM_DEBUG_DRIVER("flip queue: crtc already busy\n");
		spin_unlock_irqrestore(&crtc->dev->event_lock, flags);
		r = -EBUSY;
		जाओ pflip_cleanup;
	पूर्ण

	amdgpu_crtc->pflip_status = AMDGPU_FLIP_PENDING;
	amdgpu_crtc->pflip_works = work;


	DRM_DEBUG_DRIVER("crtc:%d[%p], pflip_stat:AMDGPU_FLIP_PENDING, work: %p,\n",
					 amdgpu_crtc->crtc_id, amdgpu_crtc, work);
	/* update crtc fb */
	crtc->primary->fb = fb;
	spin_unlock_irqrestore(&crtc->dev->event_lock, flags);
	amdgpu_display_flip_work_func(&work->flip_work.work);
	वापस 0;

pflip_cleanup:
	अगर (unlikely(amdgpu_bo_reserve(new_abo, false) != 0)) अणु
		DRM_ERROR("failed to reserve new abo in error path\n");
		जाओ cleanup;
	पूर्ण
unpin:
	अगर (!adev->enable_भव_display)
		amdgpu_bo_unpin(new_abo);

unreserve:
	amdgpu_bo_unreserve(new_abo);

cleanup:
	amdgpu_bo_unref(&work->old_abo);
	dma_fence_put(work->excl);
	क्रम (i = 0; i < work->shared_count; ++i)
		dma_fence_put(work->shared[i]);
	kमुक्त(work->shared);
	kमुक्त(work);

	वापस r;
पूर्ण

पूर्णांक amdgpu_display_crtc_set_config(काष्ठा drm_mode_set *set,
				   काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा drm_device *dev;
	काष्ठा amdgpu_device *adev;
	काष्ठा drm_crtc *crtc;
	bool active = false;
	पूर्णांक ret;

	अगर (!set || !set->crtc)
		वापस -EINVAL;

	dev = set->crtc->dev;

	ret = pm_runसमय_get_sync(dev->dev);
	अगर (ret < 0)
		जाओ out;

	ret = drm_crtc_helper_set_config(set, ctx);

	list_क्रम_each_entry(crtc, &dev->mode_config.crtc_list, head)
		अगर (crtc->enabled)
			active = true;

	pm_runसमय_mark_last_busy(dev->dev);

	adev = drm_to_adev(dev);
	/* अगर we have active crtcs and we करोn't have a घातer ref,
	   take the current one */
	अगर (active && !adev->have_disp_घातer_ref) अणु
		adev->have_disp_घातer_ref = true;
		वापस ret;
	पूर्ण
	/* अगर we have no active crtcs, then drop the घातer ref
	   we got beक्रमe */
	अगर (!active && adev->have_disp_घातer_ref) अणु
		pm_runसमय_put_स्वतःsuspend(dev->dev);
		adev->have_disp_घातer_ref = false;
	पूर्ण

out:
	/* drop the घातer reference we got coming in here */
	pm_runसमय_put_स्वतःsuspend(dev->dev);
	वापस ret;
पूर्ण

अटल स्थिर अक्षर *encoder_names[41] = अणु
	"NONE",
	"INTERNAL_LVDS",
	"INTERNAL_TMDS1",
	"INTERNAL_TMDS2",
	"INTERNAL_DAC1",
	"INTERNAL_DAC2",
	"INTERNAL_SDVOA",
	"INTERNAL_SDVOB",
	"SI170B",
	"CH7303",
	"CH7301",
	"INTERNAL_DVO1",
	"EXTERNAL_SDVOA",
	"EXTERNAL_SDVOB",
	"TITFP513",
	"INTERNAL_LVTM1",
	"VT1623",
	"HDMI_SI1930",
	"HDMI_INTERNAL",
	"INTERNAL_KLDSCP_TMDS1",
	"INTERNAL_KLDSCP_DVO1",
	"INTERNAL_KLDSCP_DAC1",
	"INTERNAL_KLDSCP_DAC2",
	"SI178",
	"MVPU_FPGA",
	"INTERNAL_DDI",
	"VT1625",
	"HDMI_SI1932",
	"DP_AN9801",
	"DP_DP501",
	"INTERNAL_UNIPHY",
	"INTERNAL_KLDSCP_LVTMA",
	"INTERNAL_UNIPHY1",
	"INTERNAL_UNIPHY2",
	"NUTMEG",
	"TRAVIS",
	"INTERNAL_VCE",
	"INTERNAL_UNIPHY3",
	"HDMI_ANX9805",
	"INTERNAL_AMCLK",
	"VIRTUAL",
पूर्ण;

अटल स्थिर अक्षर *hpd_names[6] = अणु
	"HPD1",
	"HPD2",
	"HPD3",
	"HPD4",
	"HPD5",
	"HPD6",
पूर्ण;

व्योम amdgpu_display_prपूर्णांक_display_setup(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_connector *connector;
	काष्ठा amdgpu_connector *amdgpu_connector;
	काष्ठा drm_encoder *encoder;
	काष्ठा amdgpu_encoder *amdgpu_encoder;
	काष्ठा drm_connector_list_iter iter;
	uपूर्णांक32_t devices;
	पूर्णांक i = 0;

	drm_connector_list_iter_begin(dev, &iter);
	DRM_INFO("AMDGPU Display Connectors\n");
	drm_क्रम_each_connector_iter(connector, &iter) अणु
		amdgpu_connector = to_amdgpu_connector(connector);
		DRM_INFO("Connector %d:\n", i);
		DRM_INFO("  %s\n", connector->name);
		अगर (amdgpu_connector->hpd.hpd != AMDGPU_HPD_NONE)
			DRM_INFO("  %s\n", hpd_names[amdgpu_connector->hpd.hpd]);
		अगर (amdgpu_connector->ddc_bus) अणु
			DRM_INFO("  DDC: 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n",
				 amdgpu_connector->ddc_bus->rec.mask_clk_reg,
				 amdgpu_connector->ddc_bus->rec.mask_data_reg,
				 amdgpu_connector->ddc_bus->rec.a_clk_reg,
				 amdgpu_connector->ddc_bus->rec.a_data_reg,
				 amdgpu_connector->ddc_bus->rec.en_clk_reg,
				 amdgpu_connector->ddc_bus->rec.en_data_reg,
				 amdgpu_connector->ddc_bus->rec.y_clk_reg,
				 amdgpu_connector->ddc_bus->rec.y_data_reg);
			अगर (amdgpu_connector->router.ddc_valid)
				DRM_INFO("  DDC Router 0x%x/0x%x\n",
					 amdgpu_connector->router.ddc_mux_control_pin,
					 amdgpu_connector->router.ddc_mux_state);
			अगर (amdgpu_connector->router.cd_valid)
				DRM_INFO("  Clock/Data Router 0x%x/0x%x\n",
					 amdgpu_connector->router.cd_mux_control_pin,
					 amdgpu_connector->router.cd_mux_state);
		पूर्ण अन्यथा अणु
			अगर (connector->connector_type == DRM_MODE_CONNECTOR_VGA ||
			    connector->connector_type == DRM_MODE_CONNECTOR_DVII ||
			    connector->connector_type == DRM_MODE_CONNECTOR_DVID ||
			    connector->connector_type == DRM_MODE_CONNECTOR_DVIA ||
			    connector->connector_type == DRM_MODE_CONNECTOR_HDMIA ||
			    connector->connector_type == DRM_MODE_CONNECTOR_HDMIB)
				DRM_INFO("  DDC: no ddc bus - possible BIOS bug - please report to xorg-driver-ati@lists.x.org\n");
		पूर्ण
		DRM_INFO("  Encoders:\n");
		list_क्रम_each_entry(encoder, &dev->mode_config.encoder_list, head) अणु
			amdgpu_encoder = to_amdgpu_encoder(encoder);
			devices = amdgpu_encoder->devices & amdgpu_connector->devices;
			अगर (devices) अणु
				अगर (devices & ATOM_DEVICE_CRT1_SUPPORT)
					DRM_INFO("    CRT1: %s\n", encoder_names[amdgpu_encoder->encoder_id]);
				अगर (devices & ATOM_DEVICE_CRT2_SUPPORT)
					DRM_INFO("    CRT2: %s\n", encoder_names[amdgpu_encoder->encoder_id]);
				अगर (devices & ATOM_DEVICE_LCD1_SUPPORT)
					DRM_INFO("    LCD1: %s\n", encoder_names[amdgpu_encoder->encoder_id]);
				अगर (devices & ATOM_DEVICE_DFP1_SUPPORT)
					DRM_INFO("    DFP1: %s\n", encoder_names[amdgpu_encoder->encoder_id]);
				अगर (devices & ATOM_DEVICE_DFP2_SUPPORT)
					DRM_INFO("    DFP2: %s\n", encoder_names[amdgpu_encoder->encoder_id]);
				अगर (devices & ATOM_DEVICE_DFP3_SUPPORT)
					DRM_INFO("    DFP3: %s\n", encoder_names[amdgpu_encoder->encoder_id]);
				अगर (devices & ATOM_DEVICE_DFP4_SUPPORT)
					DRM_INFO("    DFP4: %s\n", encoder_names[amdgpu_encoder->encoder_id]);
				अगर (devices & ATOM_DEVICE_DFP5_SUPPORT)
					DRM_INFO("    DFP5: %s\n", encoder_names[amdgpu_encoder->encoder_id]);
				अगर (devices & ATOM_DEVICE_DFP6_SUPPORT)
					DRM_INFO("    DFP6: %s\n", encoder_names[amdgpu_encoder->encoder_id]);
				अगर (devices & ATOM_DEVICE_TV1_SUPPORT)
					DRM_INFO("    TV1: %s\n", encoder_names[amdgpu_encoder->encoder_id]);
				अगर (devices & ATOM_DEVICE_CV_SUPPORT)
					DRM_INFO("    CV: %s\n", encoder_names[amdgpu_encoder->encoder_id]);
			पूर्ण
		पूर्ण
		i++;
	पूर्ण
	drm_connector_list_iter_end(&iter);
पूर्ण

bool amdgpu_display_ddc_probe(काष्ठा amdgpu_connector *amdgpu_connector,
			      bool use_aux)
अणु
	u8 out = 0x0;
	u8 buf[8];
	पूर्णांक ret;
	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr = DDC_ADDR,
			.flags = 0,
			.len = 1,
			.buf = &out,
		पूर्ण,
		अणु
			.addr = DDC_ADDR,
			.flags = I2C_M_RD,
			.len = 8,
			.buf = buf,
		पूर्ण
	पूर्ण;

	/* on hw with routers, select right port */
	अगर (amdgpu_connector->router.ddc_valid)
		amdgpu_i2c_router_select_ddc_port(amdgpu_connector);

	अगर (use_aux) अणु
		ret = i2c_transfer(&amdgpu_connector->ddc_bus->aux.ddc, msgs, 2);
	पूर्ण अन्यथा अणु
		ret = i2c_transfer(&amdgpu_connector->ddc_bus->adapter, msgs, 2);
	पूर्ण

	अगर (ret != 2)
		/* Couldn't find an accessible DDC on this connector */
		वापस false;
	/* Probe also क्रम valid EDID header
	 * EDID header starts with:
	 * 0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00.
	 * Only the first 6 bytes must be valid as
	 * drm_edid_block_valid() can fix the last 2 bytes */
	अगर (drm_edid_header_is_valid(buf) < 6) अणु
		/* Couldn't find an accessible EDID on this
		 * connector */
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल स्थिर काष्ठा drm_framebuffer_funcs amdgpu_fb_funcs = अणु
	.destroy = drm_gem_fb_destroy,
	.create_handle = drm_gem_fb_create_handle,
पूर्ण;

uपूर्णांक32_t amdgpu_display_supported_करोमुख्यs(काष्ठा amdgpu_device *adev,
					  uपूर्णांक64_t bo_flags)
अणु
	uपूर्णांक32_t करोमुख्य = AMDGPU_GEM_DOMAIN_VRAM;

#अगर defined(CONFIG_DRM_AMD_DC)
	/*
	 * अगर amdgpu_bo_support_uswc वापसs false it means that USWC mappings
	 * is not supported क्रम this board. But this mapping is required
	 * to aव्योम hang caused by placement of scanout BO in GTT on certain
	 * APUs. So क्रमce the BO placement to VRAM in हाल this architecture
	 * will not allow USWC mappings.
	 * Also, करोn't allow GTT domain if the BO doesn't have USWC flag set.
	 */
	अगर ((bo_flags & AMDGPU_GEM_CREATE_CPU_GTT_USWC) &&
	    amdgpu_bo_support_uswc(bo_flags) &&
	    amdgpu_device_asic_has_dc_support(adev->asic_type)) अणु
		चयन (adev->asic_type) अणु
		हाल CHIP_CARRIZO:
		हाल CHIP_STONEY:
			करोमुख्य |= AMDGPU_GEM_DOMAIN_GTT;
			अवरोध;
		हाल CHIP_RAVEN:
			/* enable S/G on PCO and RV2 */
			अगर ((adev->apu_flags & AMD_APU_IS_RAVEN2) ||
			    (adev->apu_flags & AMD_APU_IS_PICASSO))
				करोमुख्य |= AMDGPU_GEM_DOMAIN_GTT;
			अवरोध;
		हाल CHIP_RENOIR:
		हाल CHIP_VANGOGH:
			करोमुख्य |= AMDGPU_GEM_DOMAIN_GTT;
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	वापस करोमुख्य;
पूर्ण

अटल स्थिर काष्ठा drm_क्रमmat_info dcc_क्रमmats[] = अणु
	अणु .क्रमmat = DRM_FORMAT_XRGB8888, .depth = 24, .num_planes = 2,
	  .cpp = अणु 4, 0, पूर्ण, .block_w = अणु1, 1, 1पूर्ण, .block_h = अणु1, 1, 1पूर्ण, .hsub = 1, .vsub = 1, पूर्ण,
	 अणु .क्रमmat = DRM_FORMAT_XBGR8888, .depth = 24, .num_planes = 2,
	  .cpp = अणु 4, 0, पूर्ण, .block_w = अणु1, 1, 1पूर्ण, .block_h = अणु1, 1, 1पूर्ण, .hsub = 1, .vsub = 1, पूर्ण,
	अणु .क्रमmat = DRM_FORMAT_ARGB8888, .depth = 32, .num_planes = 2,
	  .cpp = अणु 4, 0, पूर्ण, .block_w = अणु1, 1, 1पूर्ण, .block_h = अणु1, 1, 1पूर्ण, .hsub = 1, .vsub = 1,
	   .has_alpha = true, पूर्ण,
	अणु .क्रमmat = DRM_FORMAT_ABGR8888, .depth = 32, .num_planes = 2,
	  .cpp = अणु 4, 0, पूर्ण, .block_w = अणु1, 1, 1पूर्ण, .block_h = अणु1, 1, 1पूर्ण, .hsub = 1, .vsub = 1,
	  .has_alpha = true, पूर्ण,
	अणु .क्रमmat = DRM_FORMAT_BGRA8888, .depth = 32, .num_planes = 2,
	  .cpp = अणु 4, 0, पूर्ण, .block_w = अणु1, 1, 1पूर्ण, .block_h = अणु1, 1, 1पूर्ण, .hsub = 1, .vsub = 1,
	  .has_alpha = true, पूर्ण,
	अणु .क्रमmat = DRM_FORMAT_XRGB2101010, .depth = 30, .num_planes = 2,
	  .cpp = अणु 4, 0, पूर्ण, .block_w = अणु1, 1, 1पूर्ण, .block_h = अणु1, 1, 1पूर्ण, .hsub = 1, .vsub = 1, पूर्ण,
	अणु .क्रमmat = DRM_FORMAT_XBGR2101010, .depth = 30, .num_planes = 2,
	  .cpp = अणु 4, 0, पूर्ण, .block_w = अणु1, 1, 1पूर्ण, .block_h = अणु1, 1, 1पूर्ण, .hsub = 1, .vsub = 1, पूर्ण,
	अणु .क्रमmat = DRM_FORMAT_ARGB2101010, .depth = 30, .num_planes = 2,
	  .cpp = अणु 4, 0, पूर्ण, .block_w = अणु1, 1, 1पूर्ण, .block_h = अणु1, 1, 1पूर्ण, .hsub = 1, .vsub = 1,
	  .has_alpha = true, पूर्ण,
	अणु .क्रमmat = DRM_FORMAT_ABGR2101010, .depth = 30, .num_planes = 2,
	  .cpp = अणु 4, 0, पूर्ण, .block_w = अणु1, 1, 1पूर्ण, .block_h = अणु1, 1, 1पूर्ण, .hsub = 1, .vsub = 1,
	  .has_alpha = true, पूर्ण,
	अणु .क्रमmat = DRM_FORMAT_RGB565, .depth = 16, .num_planes = 2,
	  .cpp = अणु 2, 0, पूर्ण, .block_w = अणु1, 1, 1पूर्ण, .block_h = अणु1, 1, 1पूर्ण, .hsub = 1, .vsub = 1, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_क्रमmat_info dcc_retile_क्रमmats[] = अणु
	अणु .क्रमmat = DRM_FORMAT_XRGB8888, .depth = 24, .num_planes = 3,
	  .cpp = अणु 4, 0, 0 पूर्ण, .block_w = अणु1, 1, 1पूर्ण, .block_h = अणु1, 1, 1पूर्ण, .hsub = 1, .vsub = 1, पूर्ण,
	 अणु .क्रमmat = DRM_FORMAT_XBGR8888, .depth = 24, .num_planes = 3,
	  .cpp = अणु 4, 0, 0 पूर्ण, .block_w = अणु1, 1, 1पूर्ण, .block_h = अणु1, 1, 1पूर्ण, .hsub = 1, .vsub = 1, पूर्ण,
	अणु .क्रमmat = DRM_FORMAT_ARGB8888, .depth = 32, .num_planes = 3,
	  .cpp = अणु 4, 0, 0 पूर्ण, .block_w = अणु1, 1, 1पूर्ण, .block_h = अणु1, 1, 1पूर्ण, .hsub = 1, .vsub = 1,
	   .has_alpha = true, पूर्ण,
	अणु .क्रमmat = DRM_FORMAT_ABGR8888, .depth = 32, .num_planes = 3,
	  .cpp = अणु 4, 0, 0 पूर्ण, .block_w = अणु1, 1, 1पूर्ण, .block_h = अणु1, 1, 1पूर्ण, .hsub = 1, .vsub = 1,
	  .has_alpha = true, पूर्ण,
	अणु .क्रमmat = DRM_FORMAT_BGRA8888, .depth = 32, .num_planes = 3,
	  .cpp = अणु 4, 0, 0 पूर्ण, .block_w = अणु1, 1, 1पूर्ण, .block_h = अणु1, 1, 1पूर्ण, .hsub = 1, .vsub = 1,
	  .has_alpha = true, पूर्ण,
	अणु .क्रमmat = DRM_FORMAT_XRGB2101010, .depth = 30, .num_planes = 3,
	  .cpp = अणु 4, 0, 0 पूर्ण, .block_w = अणु1, 1, 1पूर्ण, .block_h = अणु1, 1, 1पूर्ण, .hsub = 1, .vsub = 1, पूर्ण,
	अणु .क्रमmat = DRM_FORMAT_XBGR2101010, .depth = 30, .num_planes = 3,
	  .cpp = अणु 4, 0, 0 पूर्ण, .block_w = अणु1, 1, 1पूर्ण, .block_h = अणु1, 1, 1पूर्ण, .hsub = 1, .vsub = 1, पूर्ण,
	अणु .क्रमmat = DRM_FORMAT_ARGB2101010, .depth = 30, .num_planes = 3,
	  .cpp = अणु 4, 0, 0 पूर्ण, .block_w = अणु1, 1, 1पूर्ण, .block_h = अणु1, 1, 1पूर्ण, .hsub = 1, .vsub = 1,
	  .has_alpha = true, पूर्ण,
	अणु .क्रमmat = DRM_FORMAT_ABGR2101010, .depth = 30, .num_planes = 3,
	  .cpp = अणु 4, 0, 0 पूर्ण, .block_w = अणु1, 1, 1पूर्ण, .block_h = अणु1, 1, 1पूर्ण, .hsub = 1, .vsub = 1,
	  .has_alpha = true, पूर्ण,
	अणु .क्रमmat = DRM_FORMAT_RGB565, .depth = 16, .num_planes = 3,
	  .cpp = अणु 2, 0, 0 पूर्ण, .block_w = अणु1, 1, 1पूर्ण, .block_h = अणु1, 1, 1पूर्ण, .hsub = 1, .vsub = 1, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_क्रमmat_info *
lookup_क्रमmat_info(स्थिर काष्ठा drm_क्रमmat_info क्रमmats[],
		  पूर्णांक num_क्रमmats, u32 क्रमmat)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_क्रमmats; i++) अणु
		अगर (क्रमmats[i].क्रमmat == क्रमmat)
			वापस &क्रमmats[i];
	पूर्ण

	वापस शून्य;
पूर्ण

स्थिर काष्ठा drm_क्रमmat_info *
amdgpu_lookup_क्रमmat_info(u32 क्रमmat, uपूर्णांक64_t modअगरier)
अणु
	अगर (!IS_AMD_FMT_MOD(modअगरier))
		वापस शून्य;

	अगर (AMD_FMT_MOD_GET(DCC_RETILE, modअगरier))
		वापस lookup_क्रमmat_info(dcc_retile_क्रमmats,
					  ARRAY_SIZE(dcc_retile_क्रमmats),
					  क्रमmat);

	अगर (AMD_FMT_MOD_GET(DCC, modअगरier))
		वापस lookup_क्रमmat_info(dcc_क्रमmats, ARRAY_SIZE(dcc_क्रमmats),
					  क्रमmat);

	/* वापसing शून्य will cause the शेष क्रमmat काष्ठाs to be used. */
	वापस शून्य;
पूर्ण


/*
 * Tries to extract the renderable DCC offset from the opaque metadata attached
 * to the buffer.
 */
अटल पूर्णांक
extract_render_dcc_offset(काष्ठा amdgpu_device *adev,
			  काष्ठा drm_gem_object *obj,
			  uपूर्णांक64_t *offset)
अणु
	काष्ठा amdgpu_bo *rbo;
	पूर्णांक r = 0;
	uपूर्णांक32_t metadata[10]; /* Something that fits a descriptor + header. */
	uपूर्णांक32_t size;

	rbo = gem_to_amdgpu_bo(obj);
	r = amdgpu_bo_reserve(rbo, false);

	अगर (unlikely(r)) अणु
		/* Don't show error message when वापसing -ERESTARTSYS */
		अगर (r != -ERESTARTSYS)
			DRM_ERROR("Unable to reserve buffer: %d\n", r);
		वापस r;
	पूर्ण

	r = amdgpu_bo_get_metadata(rbo, metadata, माप(metadata), &size, शून्य);
	amdgpu_bo_unreserve(rbo);

	अगर (r)
		वापस r;

	/*
	 * The first word is the metadata version, and we need space क्रम at least
	 * the version + pci venकरोr+device id + 8 words क्रम a descriptor.
	 */
	अगर (size < 40  || metadata[0] != 1)
		वापस -EINVAL;

	अगर (adev->family >= AMDGPU_FAMILY_NV) अणु
		/* resource word 6/7 META_DATA_ADDRESSअणु_LOपूर्ण */
		*offset = ((u64)metadata[9] << 16u) |
			  ((metadata[8] & 0xFF000000u) >> 16);
	पूर्ण अन्यथा अणु
		/* resource word 5/7 META_DATA_ADDRESS */
		*offset = ((u64)metadata[9] << 8u) |
			  ((u64)(metadata[7] & 0x1FE0000u) << 23);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक convert_tiling_flags_to_modअगरier(काष्ठा amdgpu_framebuffer *afb)
अणु
	काष्ठा amdgpu_device *adev = drm_to_adev(afb->base.dev);
	uपूर्णांक64_t modअगरier = 0;

	अगर (!afb->tiling_flags || !AMDGPU_TILING_GET(afb->tiling_flags, SWIZZLE_MODE)) अणु
		modअगरier = DRM_FORMAT_MOD_LINEAR;
	पूर्ण अन्यथा अणु
		पूर्णांक swizzle = AMDGPU_TILING_GET(afb->tiling_flags, SWIZZLE_MODE);
		bool has_xor = swizzle >= 16;
		पूर्णांक block_size_bits;
		पूर्णांक version;
		पूर्णांक pipe_xor_bits = 0;
		पूर्णांक bank_xor_bits = 0;
		पूर्णांक packers = 0;
		पूर्णांक rb = 0;
		पूर्णांक pipes = ilog2(adev->gfx.config.gb_addr_config_fields.num_pipes);
		uपूर्णांक32_t dcc_offset = AMDGPU_TILING_GET(afb->tiling_flags, DCC_OFFSET_256B);

		चयन (swizzle >> 2) अणु
		हाल 0: /* 256B */
			block_size_bits = 8;
			अवरोध;
		हाल 1: /* 4KiB */
		हाल 5: /* 4KiB _X */
			block_size_bits = 12;
			अवरोध;
		हाल 2: /* 64KiB */
		हाल 4: /* 64 KiB _T */
		हाल 6: /* 64 KiB _X */
			block_size_bits = 16;
			अवरोध;
		शेष:
			/* RESERVED or VAR */
			वापस -EINVAL;
		पूर्ण

		अगर (adev->asic_type >= CHIP_SIENNA_CICHLID)
			version = AMD_FMT_MOD_TILE_VER_GFX10_RBPLUS;
		अन्यथा अगर (adev->family == AMDGPU_FAMILY_NV)
			version = AMD_FMT_MOD_TILE_VER_GFX10;
		अन्यथा
			version = AMD_FMT_MOD_TILE_VER_GFX9;

		चयन (swizzle & 3) अणु
		हाल 0: /* Z microtiling */
			वापस -EINVAL;
		हाल 1: /* S microtiling */
			अगर (!has_xor)
				version = AMD_FMT_MOD_TILE_VER_GFX9;
			अवरोध;
		हाल 2:
			अगर (!has_xor && afb->base.क्रमmat->cpp[0] != 4)
				version = AMD_FMT_MOD_TILE_VER_GFX9;
			अवरोध;
		हाल 3:
			अवरोध;
		पूर्ण

		अगर (has_xor) अणु
			चयन (version) अणु
			हाल AMD_FMT_MOD_TILE_VER_GFX10_RBPLUS:
				pipe_xor_bits = min(block_size_bits - 8, pipes);
				packers = min(block_size_bits - 8 - pipe_xor_bits,
					      ilog2(adev->gfx.config.gb_addr_config_fields.num_pkrs));
				अवरोध;
			हाल AMD_FMT_MOD_TILE_VER_GFX10:
				pipe_xor_bits = min(block_size_bits - 8, pipes);
				अवरोध;
			हाल AMD_FMT_MOD_TILE_VER_GFX9:
				rb = ilog2(adev->gfx.config.gb_addr_config_fields.num_se) +
				     ilog2(adev->gfx.config.gb_addr_config_fields.num_rb_per_se);
				pipe_xor_bits = min(block_size_bits - 8, pipes +
						    ilog2(adev->gfx.config.gb_addr_config_fields.num_se));
				bank_xor_bits = min(block_size_bits - 8 - pipe_xor_bits,
						    ilog2(adev->gfx.config.gb_addr_config_fields.num_banks));
				अवरोध;
			पूर्ण
		पूर्ण

		modअगरier = AMD_FMT_MOD |
			   AMD_FMT_MOD_SET(TILE, AMDGPU_TILING_GET(afb->tiling_flags, SWIZZLE_MODE)) |
			   AMD_FMT_MOD_SET(TILE_VERSION, version) |
			   AMD_FMT_MOD_SET(PIPE_XOR_BITS, pipe_xor_bits) |
			   AMD_FMT_MOD_SET(BANK_XOR_BITS, bank_xor_bits) |
			   AMD_FMT_MOD_SET(PACKERS, packers);

		अगर (dcc_offset != 0) अणु
			bool dcc_i64b = AMDGPU_TILING_GET(afb->tiling_flags, DCC_INDEPENDENT_64B) != 0;
			bool dcc_i128b = version >= AMD_FMT_MOD_TILE_VER_GFX10_RBPLUS;
			स्थिर काष्ठा drm_क्रमmat_info *क्रमmat_info;
			u64 render_dcc_offset;

			/* Enable स्थिरant encode on RAVEN2 and later. */
			bool dcc_स्थिरant_encode = adev->asic_type > CHIP_RAVEN ||
						   (adev->asic_type == CHIP_RAVEN &&
						    adev->बाह्यal_rev_id >= 0x81);

			पूर्णांक max_cblock_size = dcc_i64b ? AMD_FMT_MOD_DCC_BLOCK_64B :
					      dcc_i128b ? AMD_FMT_MOD_DCC_BLOCK_128B :
					      AMD_FMT_MOD_DCC_BLOCK_256B;

			modअगरier |= AMD_FMT_MOD_SET(DCC, 1) |
				    AMD_FMT_MOD_SET(DCC_CONSTANT_ENCODE, dcc_स्थिरant_encode) |
				    AMD_FMT_MOD_SET(DCC_INDEPENDENT_64B, dcc_i64b) |
				    AMD_FMT_MOD_SET(DCC_INDEPENDENT_128B, dcc_i128b) |
				    AMD_FMT_MOD_SET(DCC_MAX_COMPRESSED_BLOCK, max_cblock_size);

			afb->base.offsets[1] = dcc_offset * 256 + afb->base.offsets[0];
			afb->base.pitches[1] =
				AMDGPU_TILING_GET(afb->tiling_flags, DCC_PITCH_MAX) + 1;

			/*
			 * If the userspace driver uses retiling the tiling flags करो not contain
			 * info on the renderable DCC buffer. Luckily the opaque metadata contains
			 * the info so we can try to extract it. The kernel करोes not use this info
			 * but we should convert it to a modअगरier plane क्रम getfb2, so the
			 * userspace driver that माला_लो it करोesn't have to juggle around another DCC
			 * plane पूर्णांकernally.
			 */
			अगर (extract_render_dcc_offset(adev, afb->base.obj[0],
						      &render_dcc_offset) == 0 &&
			    render_dcc_offset != 0 &&
			    render_dcc_offset != afb->base.offsets[1] &&
			    render_dcc_offset < अच_पूर्णांक_उच्च) अणु
				uपूर्णांक32_t dcc_block_bits;  /* of base surface data */

				modअगरier |= AMD_FMT_MOD_SET(DCC_RETILE, 1);
				afb->base.offsets[2] = render_dcc_offset;

				अगर (adev->family >= AMDGPU_FAMILY_NV) अणु
					पूर्णांक extra_pipe = 0;

					अगर (adev->asic_type >= CHIP_SIENNA_CICHLID &&
					    pipes == packers && pipes > 1)
						extra_pipe = 1;

					dcc_block_bits = max(20, 16 + pipes + extra_pipe);
				पूर्ण अन्यथा अणु
					modअगरier |= AMD_FMT_MOD_SET(RB, rb) |
						    AMD_FMT_MOD_SET(PIPE, pipes);
					dcc_block_bits = max(20, 18 + rb);
				पूर्ण

				dcc_block_bits -= ilog2(afb->base.क्रमmat->cpp[0]);
				afb->base.pitches[2] = ALIGN(afb->base.width,
							     1u << ((dcc_block_bits + 1) / 2));
			पूर्ण
			क्रमmat_info = amdgpu_lookup_क्रमmat_info(afb->base.क्रमmat->क्रमmat,
								modअगरier);
			अगर (!क्रमmat_info)
				वापस -EINVAL;

			afb->base.क्रमmat = क्रमmat_info;
		पूर्ण
	पूर्ण

	afb->base.modअगरier = modअगरier;
	afb->base.flags |= DRM_MODE_FB_MODIFIERS;
	वापस 0;
पूर्ण

अटल व्योम get_block_dimensions(अचिन्हित पूर्णांक block_log2, अचिन्हित पूर्णांक cpp,
				 अचिन्हित पूर्णांक *width, अचिन्हित पूर्णांक *height)
अणु
	अचिन्हित पूर्णांक cpp_log2 = ilog2(cpp);
	अचिन्हित पूर्णांक pixel_log2 = block_log2 - cpp_log2;
	अचिन्हित पूर्णांक width_log2 = (pixel_log2 + 1) / 2;
	अचिन्हित पूर्णांक height_log2 = pixel_log2 - width_log2;

	*width = 1 << width_log2;
	*height = 1 << height_log2;
पूर्ण

अटल अचिन्हित पूर्णांक get_dcc_block_size(uपूर्णांक64_t modअगरier, bool rb_aligned,
				       bool pipe_aligned)
अणु
	अचिन्हित पूर्णांक ver = AMD_FMT_MOD_GET(TILE_VERSION, modअगरier);

	चयन (ver) अणु
	हाल AMD_FMT_MOD_TILE_VER_GFX9: अणु
		/*
		 * TODO: क्रम pipe aligned we may need to check the alignment of the
		 * total size of the surface, which may need to be bigger than the
		 * natural alignment due to some HW workarounds
		 */
		वापस max(10 + (rb_aligned ? (पूर्णांक)AMD_FMT_MOD_GET(RB, modअगरier) : 0), 12);
	पूर्ण
	हाल AMD_FMT_MOD_TILE_VER_GFX10:
	हाल AMD_FMT_MOD_TILE_VER_GFX10_RBPLUS: अणु
		पूर्णांक pipes_log2 = AMD_FMT_MOD_GET(PIPE_XOR_BITS, modअगरier);

		अगर (ver == AMD_FMT_MOD_TILE_VER_GFX10_RBPLUS && pipes_log2 > 1 &&
		    AMD_FMT_MOD_GET(PACKERS, modअगरier) == pipes_log2)
			++pipes_log2;

		वापस max(8 + (pipe_aligned ? pipes_log2 : 0), 12);
	पूर्ण
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक amdgpu_display_verअगरy_plane(काष्ठा amdgpu_framebuffer *rfb, पूर्णांक plane,
				       स्थिर काष्ठा drm_क्रमmat_info *क्रमmat,
				       अचिन्हित पूर्णांक block_width, अचिन्हित पूर्णांक block_height,
				       अचिन्हित पूर्णांक block_size_log2)
अणु
	अचिन्हित पूर्णांक width = rfb->base.width /
		((plane && plane < क्रमmat->num_planes) ? क्रमmat->hsub : 1);
	अचिन्हित पूर्णांक height = rfb->base.height /
		((plane && plane < क्रमmat->num_planes) ? क्रमmat->vsub : 1);
	अचिन्हित पूर्णांक cpp = plane < क्रमmat->num_planes ? क्रमmat->cpp[plane] : 1;
	अचिन्हित पूर्णांक block_pitch = block_width * cpp;
	अचिन्हित पूर्णांक min_pitch = ALIGN(width * cpp, block_pitch);
	अचिन्हित पूर्णांक block_size = 1 << block_size_log2;
	uपूर्णांक64_t size;

	अगर (rfb->base.pitches[plane] % block_pitch) अणु
		drm_dbg_kms(rfb->base.dev,
			    "pitch %d for plane %d is not a multiple of block pitch %d\n",
			    rfb->base.pitches[plane], plane, block_pitch);
		वापस -EINVAL;
	पूर्ण
	अगर (rfb->base.pitches[plane] < min_pitch) अणु
		drm_dbg_kms(rfb->base.dev,
			    "pitch %d for plane %d is less than minimum pitch %d\n",
			    rfb->base.pitches[plane], plane, min_pitch);
		वापस -EINVAL;
	पूर्ण

	/* Force at least natural alignment. */
	अगर (rfb->base.offsets[plane] % block_size) अणु
		drm_dbg_kms(rfb->base.dev,
			    "offset 0x%x for plane %d is not a multiple of block pitch 0x%x\n",
			    rfb->base.offsets[plane], plane, block_size);
		वापस -EINVAL;
	पूर्ण

	size = rfb->base.offsets[plane] +
		(uपूर्णांक64_t)rfb->base.pitches[plane] / block_pitch *
		block_size * DIV_ROUND_UP(height, block_height);

	अगर (rfb->base.obj[0]->size < size) अणु
		drm_dbg_kms(rfb->base.dev,
			    "BO size 0x%zx is less than 0x%llx required for plane %d\n",
			    rfb->base.obj[0]->size, size, plane);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक amdgpu_display_verअगरy_sizes(काष्ठा amdgpu_framebuffer *rfb)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *क्रमmat_info = drm_क्रमmat_info(rfb->base.क्रमmat->क्रमmat);
	uपूर्णांक64_t modअगरier = rfb->base.modअगरier;
	पूर्णांक ret;
	अचिन्हित पूर्णांक i, block_width, block_height, block_size_log2;

	अगर (!rfb->base.dev->mode_config.allow_fb_modअगरiers)
		वापस 0;

	क्रम (i = 0; i < क्रमmat_info->num_planes; ++i) अणु
		अगर (modअगरier == DRM_FORMAT_MOD_LINEAR) अणु
			block_width = 256 / क्रमmat_info->cpp[i];
			block_height = 1;
			block_size_log2 = 8;
		पूर्ण अन्यथा अणु
			पूर्णांक swizzle = AMD_FMT_MOD_GET(TILE, modअगरier);

			चयन ((swizzle & ~3) + 1) अणु
			हाल DC_SW_256B_S:
				block_size_log2 = 8;
				अवरोध;
			हाल DC_SW_4KB_S:
			हाल DC_SW_4KB_S_X:
				block_size_log2 = 12;
				अवरोध;
			हाल DC_SW_64KB_S:
			हाल DC_SW_64KB_S_T:
			हाल DC_SW_64KB_S_X:
				block_size_log2 = 16;
				अवरोध;
			शेष:
				drm_dbg_kms(rfb->base.dev,
					    "Swizzle mode with unknown block size: %d\n", swizzle);
				वापस -EINVAL;
			पूर्ण

			get_block_dimensions(block_size_log2, क्रमmat_info->cpp[i],
					     &block_width, &block_height);
		पूर्ण

		ret = amdgpu_display_verअगरy_plane(rfb, i, क्रमmat_info,
						  block_width, block_height, block_size_log2);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (AMD_FMT_MOD_GET(DCC, modअगरier)) अणु
		अगर (AMD_FMT_MOD_GET(DCC_RETILE, modअगरier)) अणु
			block_size_log2 = get_dcc_block_size(modअगरier, false, false);
			get_block_dimensions(block_size_log2 + 8, क्रमmat_info->cpp[0],
					     &block_width, &block_height);
			ret = amdgpu_display_verअगरy_plane(rfb, i, क्रमmat_info,
							  block_width, block_height,
							  block_size_log2);
			अगर (ret)
				वापस ret;

			++i;
			block_size_log2 = get_dcc_block_size(modअगरier, true, true);
		पूर्ण अन्यथा अणु
			bool pipe_aligned = AMD_FMT_MOD_GET(DCC_PIPE_ALIGN, modअगरier);

			block_size_log2 = get_dcc_block_size(modअगरier, true, pipe_aligned);
		पूर्ण
		get_block_dimensions(block_size_log2 + 8, क्रमmat_info->cpp[0],
				     &block_width, &block_height);
		ret = amdgpu_display_verअगरy_plane(rfb, i, क्रमmat_info,
						  block_width, block_height, block_size_log2);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक amdgpu_display_get_fb_info(स्थिर काष्ठा amdgpu_framebuffer *amdgpu_fb,
				      uपूर्णांक64_t *tiling_flags, bool *पंचांगz_surface)
अणु
	काष्ठा amdgpu_bo *rbo;
	पूर्णांक r;

	अगर (!amdgpu_fb) अणु
		*tiling_flags = 0;
		*पंचांगz_surface = false;
		वापस 0;
	पूर्ण

	rbo = gem_to_amdgpu_bo(amdgpu_fb->base.obj[0]);
	r = amdgpu_bo_reserve(rbo, false);

	अगर (unlikely(r)) अणु
		/* Don't show error message when वापसing -ERESTARTSYS */
		अगर (r != -ERESTARTSYS)
			DRM_ERROR("Unable to reserve buffer: %d\n", r);
		वापस r;
	पूर्ण

	अगर (tiling_flags)
		amdgpu_bo_get_tiling_flags(rbo, tiling_flags);

	अगर (पंचांगz_surface)
		*पंचांगz_surface = amdgpu_bo_encrypted(rbo);

	amdgpu_bo_unreserve(rbo);

	वापस r;
पूर्ण

पूर्णांक amdgpu_display_gem_fb_init(काष्ठा drm_device *dev,
			       काष्ठा amdgpu_framebuffer *rfb,
			       स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd,
			       काष्ठा drm_gem_object *obj)
अणु
	पूर्णांक ret;

	rfb->base.obj[0] = obj;
	drm_helper_mode_fill_fb_काष्ठा(dev, &rfb->base, mode_cmd);
	ret = drm_framebuffer_init(dev, &rfb->base, &amdgpu_fb_funcs);
	अगर (ret)
		जाओ err;

	ret = amdgpu_display_framebuffer_init(dev, rfb, mode_cmd, obj);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	drm_dbg_kms(dev, "Failed to init gem fb: %d\n", ret);
	rfb->base.obj[0] = शून्य;
	वापस ret;
पूर्ण

पूर्णांक amdgpu_display_gem_fb_verअगरy_and_init(
	काष्ठा drm_device *dev, काष्ठा amdgpu_framebuffer *rfb,
	काष्ठा drm_file *file_priv, स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd,
	काष्ठा drm_gem_object *obj)
अणु
	पूर्णांक ret;

	rfb->base.obj[0] = obj;
	drm_helper_mode_fill_fb_काष्ठा(dev, &rfb->base, mode_cmd);
	ret = drm_framebuffer_init(dev, &rfb->base, &amdgpu_fb_funcs);
	अगर (ret)
		जाओ err;
	/* Verअगरy that the modअगरier is supported. */
	अगर (!drm_any_plane_has_क्रमmat(dev, mode_cmd->pixel_क्रमmat,
				      mode_cmd->modअगरier[0])) अणु
		काष्ठा drm_क्रमmat_name_buf क्रमmat_name;
		drm_dbg_kms(dev,
			    "unsupported pixel format %s / modifier 0x%llx\n",
			    drm_get_क्रमmat_name(mode_cmd->pixel_क्रमmat,
						&क्रमmat_name),
			    mode_cmd->modअगरier[0]);

		ret = -EINVAL;
		जाओ err;
	पूर्ण

	ret = amdgpu_display_framebuffer_init(dev, rfb, mode_cmd, obj);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	drm_dbg_kms(dev, "Failed to verify and init gem fb: %d\n", ret);
	rfb->base.obj[0] = शून्य;
	वापस ret;
पूर्ण

पूर्णांक amdgpu_display_framebuffer_init(काष्ठा drm_device *dev,
				    काष्ठा amdgpu_framebuffer *rfb,
				    स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd,
				    काष्ठा drm_gem_object *obj)
अणु
	पूर्णांक ret, i;

	/*
	 * This needs to happen beक्रमe modअगरier conversion as that might change
	 * the number of planes.
	 */
	क्रम (i = 1; i < rfb->base.क्रमmat->num_planes; ++i) अणु
		अगर (mode_cmd->handles[i] != mode_cmd->handles[0]) अणु
			drm_dbg_kms(dev, "Plane 0 and %d have different BOs: %u vs. %u\n",
				    i, mode_cmd->handles[0], mode_cmd->handles[i]);
			ret = -EINVAL;
			वापस ret;
		पूर्ण
	पूर्ण

	ret = amdgpu_display_get_fb_info(rfb, &rfb->tiling_flags, &rfb->पंचांगz_surface);
	अगर (ret)
		वापस ret;

	अगर (dev->mode_config.allow_fb_modअगरiers &&
	    !(rfb->base.flags & DRM_MODE_FB_MODIFIERS)) अणु
		ret = convert_tiling_flags_to_modअगरier(rfb);
		अगर (ret) अणु
			drm_dbg_kms(dev, "Failed to convert tiling flags 0x%llX to a modifier",
				    rfb->tiling_flags);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = amdgpu_display_verअगरy_sizes(rfb);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < rfb->base.क्रमmat->num_planes; ++i) अणु
		drm_gem_object_get(rfb->base.obj[0]);
		rfb->base.obj[i] = rfb->base.obj[0];
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा drm_framebuffer *
amdgpu_display_user_framebuffer_create(काष्ठा drm_device *dev,
				       काष्ठा drm_file *file_priv,
				       स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd)
अणु
	काष्ठा amdgpu_framebuffer *amdgpu_fb;
	काष्ठा drm_gem_object *obj;
	काष्ठा amdgpu_bo *bo;
	uपूर्णांक32_t करोमुख्यs;
	पूर्णांक ret;

	obj = drm_gem_object_lookup(file_priv, mode_cmd->handles[0]);
	अगर (obj ==  शून्य) अणु
		drm_dbg_kms(dev, "No GEM object associated to handle 0x%08X, "
			    "can't create framebuffer\n", mode_cmd->handles[0]);
		वापस ERR_PTR(-ENOENT);
	पूर्ण

	/* Handle is imported dma-buf, so cannot be migrated to VRAM क्रम scanout */
	bo = gem_to_amdgpu_bo(obj);
	करोमुख्यs = amdgpu_display_supported_करोमुख्यs(drm_to_adev(dev), bo->flags);
	अगर (obj->import_attach && !(करोमुख्यs & AMDGPU_GEM_DOMAIN_GTT)) अणु
		drm_dbg_kms(dev, "Cannot create framebuffer from imported dma_buf\n");
		drm_gem_object_put(obj);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	amdgpu_fb = kzalloc(माप(*amdgpu_fb), GFP_KERNEL);
	अगर (amdgpu_fb == शून्य) अणु
		drm_gem_object_put(obj);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	ret = amdgpu_display_gem_fb_verअगरy_and_init(dev, amdgpu_fb, file_priv,
						    mode_cmd, obj);
	अगर (ret) अणु
		kमुक्त(amdgpu_fb);
		drm_gem_object_put(obj);
		वापस ERR_PTR(ret);
	पूर्ण

	drm_gem_object_put(obj);
	वापस &amdgpu_fb->base;
पूर्ण

स्थिर काष्ठा drm_mode_config_funcs amdgpu_mode_funcs = अणु
	.fb_create = amdgpu_display_user_framebuffer_create,
	.output_poll_changed = drm_fb_helper_output_poll_changed,
पूर्ण;

अटल स्थिर काष्ठा drm_prop_क्रमागत_list amdgpu_underscan_क्रमागत_list[] =
अणु	अणु UNDERSCAN_OFF, "off" पूर्ण,
	अणु UNDERSCAN_ON, "on" पूर्ण,
	अणु UNDERSCAN_AUTO, "auto" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_prop_क्रमागत_list amdgpu_audio_क्रमागत_list[] =
अणु	अणु AMDGPU_AUDIO_DISABLE, "off" पूर्ण,
	अणु AMDGPU_AUDIO_ENABLE, "on" पूर्ण,
	अणु AMDGPU_AUDIO_AUTO, "auto" पूर्ण,
पूर्ण;

/* XXX support dअगरferent dither options? spatial, temporal, both, etc. */
अटल स्थिर काष्ठा drm_prop_क्रमागत_list amdgpu_dither_क्रमागत_list[] =
अणु	अणु AMDGPU_FMT_DITHER_DISABLE, "off" पूर्ण,
	अणु AMDGPU_FMT_DITHER_ENABLE, "on" पूर्ण,
पूर्ण;

पूर्णांक amdgpu_display_modeset_create_props(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक sz;

	adev->mode_info.coherent_mode_property =
		drm_property_create_range(adev_to_drm(adev), 0, "coherent", 0, 1);
	अगर (!adev->mode_info.coherent_mode_property)
		वापस -ENOMEM;

	adev->mode_info.load_detect_property =
		drm_property_create_range(adev_to_drm(adev), 0, "load detection", 0, 1);
	अगर (!adev->mode_info.load_detect_property)
		वापस -ENOMEM;

	drm_mode_create_scaling_mode_property(adev_to_drm(adev));

	sz = ARRAY_SIZE(amdgpu_underscan_क्रमागत_list);
	adev->mode_info.underscan_property =
		drm_property_create_क्रमागत(adev_to_drm(adev), 0,
					 "underscan",
					 amdgpu_underscan_क्रमागत_list, sz);

	adev->mode_info.underscan_hborder_property =
		drm_property_create_range(adev_to_drm(adev), 0,
					  "underscan hborder", 0, 128);
	अगर (!adev->mode_info.underscan_hborder_property)
		वापस -ENOMEM;

	adev->mode_info.underscan_vborder_property =
		drm_property_create_range(adev_to_drm(adev), 0,
					  "underscan vborder", 0, 128);
	अगर (!adev->mode_info.underscan_vborder_property)
		वापस -ENOMEM;

	sz = ARRAY_SIZE(amdgpu_audio_क्रमागत_list);
	adev->mode_info.audio_property =
		drm_property_create_क्रमागत(adev_to_drm(adev), 0,
					 "audio",
					 amdgpu_audio_क्रमागत_list, sz);

	sz = ARRAY_SIZE(amdgpu_dither_क्रमागत_list);
	adev->mode_info.dither_property =
		drm_property_create_क्रमागत(adev_to_drm(adev), 0,
					 "dither",
					 amdgpu_dither_क्रमागत_list, sz);

	अगर (amdgpu_device_has_dc_support(adev)) अणु
		adev->mode_info.abm_level_property =
			drm_property_create_range(adev_to_drm(adev), 0,
						  "abm level", 0, 4);
		अगर (!adev->mode_info.abm_level_property)
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

व्योम amdgpu_display_update_priority(काष्ठा amdgpu_device *adev)
अणु
	/* adjusपंचांगent options क्रम the display watermarks */
	अगर ((amdgpu_disp_priority == 0) || (amdgpu_disp_priority > 2))
		adev->mode_info.disp_priority = 0;
	अन्यथा
		adev->mode_info.disp_priority = amdgpu_disp_priority;

पूर्ण

अटल bool amdgpu_display_is_hdtv_mode(स्थिर काष्ठा drm_display_mode *mode)
अणु
	/* try and guess अगर this is a tv or a monitor */
	अगर ((mode->vdisplay == 480 && mode->hdisplay == 720) || /* 480p */
	    (mode->vdisplay == 576) || /* 576p */
	    (mode->vdisplay == 720) || /* 720p */
	    (mode->vdisplay == 1080)) /* 1080p */
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

bool amdgpu_display_crtc_scaling_mode_fixup(काष्ठा drm_crtc *crtc,
					स्थिर काष्ठा drm_display_mode *mode,
					काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_encoder *encoder;
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	काष्ठा amdgpu_encoder *amdgpu_encoder;
	काष्ठा drm_connector *connector;
	u32 src_v = 1, dst_v = 1;
	u32 src_h = 1, dst_h = 1;

	amdgpu_crtc->h_border = 0;
	amdgpu_crtc->v_border = 0;

	list_क्रम_each_entry(encoder, &dev->mode_config.encoder_list, head) अणु
		अगर (encoder->crtc != crtc)
			जारी;
		amdgpu_encoder = to_amdgpu_encoder(encoder);
		connector = amdgpu_get_connector_क्रम_encoder(encoder);

		/* set scaling */
		अगर (amdgpu_encoder->rmx_type == RMX_OFF)
			amdgpu_crtc->rmx_type = RMX_OFF;
		अन्यथा अगर (mode->hdisplay < amdgpu_encoder->native_mode.hdisplay ||
			 mode->vdisplay < amdgpu_encoder->native_mode.vdisplay)
			amdgpu_crtc->rmx_type = amdgpu_encoder->rmx_type;
		अन्यथा
			amdgpu_crtc->rmx_type = RMX_OFF;
		/* copy native mode */
		स_नकल(&amdgpu_crtc->native_mode,
		       &amdgpu_encoder->native_mode,
		       माप(काष्ठा drm_display_mode));
		src_v = crtc->mode.vdisplay;
		dst_v = amdgpu_crtc->native_mode.vdisplay;
		src_h = crtc->mode.hdisplay;
		dst_h = amdgpu_crtc->native_mode.hdisplay;

		/* fix up क्रम overscan on hdmi */
		अगर ((!(mode->flags & DRM_MODE_FLAG_INTERLACE)) &&
		    ((amdgpu_encoder->underscan_type == UNDERSCAN_ON) ||
		     ((amdgpu_encoder->underscan_type == UNDERSCAN_AUTO) &&
		      drm_detect_hdmi_monitor(amdgpu_connector_edid(connector)) &&
		      amdgpu_display_is_hdtv_mode(mode)))) अणु
			अगर (amdgpu_encoder->underscan_hborder != 0)
				amdgpu_crtc->h_border = amdgpu_encoder->underscan_hborder;
			अन्यथा
				amdgpu_crtc->h_border = (mode->hdisplay >> 5) + 16;
			अगर (amdgpu_encoder->underscan_vborder != 0)
				amdgpu_crtc->v_border = amdgpu_encoder->underscan_vborder;
			अन्यथा
				amdgpu_crtc->v_border = (mode->vdisplay >> 5) + 16;
			amdgpu_crtc->rmx_type = RMX_FULL;
			src_v = crtc->mode.vdisplay;
			dst_v = crtc->mode.vdisplay - (amdgpu_crtc->v_border * 2);
			src_h = crtc->mode.hdisplay;
			dst_h = crtc->mode.hdisplay - (amdgpu_crtc->h_border * 2);
		पूर्ण
	पूर्ण
	अगर (amdgpu_crtc->rmx_type != RMX_OFF) अणु
		fixed20_12 a, b;
		a.full = dfixed_स्थिर(src_v);
		b.full = dfixed_स्थिर(dst_v);
		amdgpu_crtc->vsc.full = dfixed_भाग(a, b);
		a.full = dfixed_स्थिर(src_h);
		b.full = dfixed_स्थिर(dst_h);
		amdgpu_crtc->hsc.full = dfixed_भाग(a, b);
	पूर्ण अन्यथा अणु
		amdgpu_crtc->vsc.full = dfixed_स्थिर(1);
		amdgpu_crtc->hsc.full = dfixed_स्थिर(1);
	पूर्ण
	वापस true;
पूर्ण

/*
 * Retrieve current video scanout position of crtc on a given gpu, and
 * an optional accurate बारtamp of when query happened.
 *
 * \param dev Device to query.
 * \param pipe Crtc to query.
 * \param flags Flags from caller (DRM_CALLED_FROM_VBLIRQ or 0).
 *              For driver पूर्णांकernal use only also supports these flags:
 *
 *              USE_REAL_VBLANKSTART to use the real start of vblank instead
 *              of a fudged earlier start of vblank.
 *
 *              GET_DISTANCE_TO_VBLANKSTART to वापस distance to the
 *              fudged earlier start of vblank in *vpos and the distance
 *              to true start of vblank in *hpos.
 *
 * \param *vpos Location where vertical scanout position should be stored.
 * \param *hpos Location where horizontal scanout position should go.
 * \param *sसमय Target location क्रम बारtamp taken immediately beक्रमe
 *               scanout position query. Can be शून्य to skip बारtamp.
 * \param *eसमय Target location क्रम बारtamp taken immediately after
 *               scanout position query. Can be शून्य to skip बारtamp.
 *
 * Returns vpos as a positive number जबतक in active scanout area.
 * Returns vpos as a negative number inside vblank, counting the number
 * of scanlines to go until end of vblank, e.g., -1 means "one scanline
 * until start of active scanout / end of vblank."
 *
 * \लeturn Flags, or'ed together as follows:
 *
 * DRM_SCANOUTPOS_VALID = Query successful.
 * DRM_SCANOUTPOS_INVBL = Inside vblank.
 * DRM_SCANOUTPOS_ACCURATE = Returned position is accurate. A lack of
 * this flag means that वापसed position may be offset by a स्थिरant but
 * unknown small number of scanlines wrt. real scanout position.
 *
 */
पूर्णांक amdgpu_display_get_crtc_scanoutpos(काष्ठा drm_device *dev,
			अचिन्हित पूर्णांक pipe, अचिन्हित पूर्णांक flags, पूर्णांक *vpos,
			पूर्णांक *hpos, kसमय_प्रकार *sसमय, kसमय_प्रकार *eसमय,
			स्थिर काष्ठा drm_display_mode *mode)
अणु
	u32 vbl = 0, position = 0;
	पूर्णांक vbl_start, vbl_end, vtotal, ret = 0;
	bool in_vbl = true;

	काष्ठा amdgpu_device *adev = drm_to_adev(dev);

	/* preempt_disable_rt() should go right here in PREEMPT_RT patchset. */

	/* Get optional प्रणाली बारtamp beक्रमe query. */
	अगर (sसमय)
		*sसमय = kसमय_get();

	अगर (amdgpu_display_page_flip_get_scanoutpos(adev, pipe, &vbl, &position) == 0)
		ret |= DRM_SCANOUTPOS_VALID;

	/* Get optional प्रणाली बारtamp after query. */
	अगर (eसमय)
		*eसमय = kसमय_get();

	/* preempt_enable_rt() should go right here in PREEMPT_RT patchset. */

	/* Decode पूर्णांकo vertical and horizontal scanout position. */
	*vpos = position & 0x1fff;
	*hpos = (position >> 16) & 0x1fff;

	/* Valid vblank area boundaries from gpu retrieved? */
	अगर (vbl > 0) अणु
		/* Yes: Decode. */
		ret |= DRM_SCANOUTPOS_ACCURATE;
		vbl_start = vbl & 0x1fff;
		vbl_end = (vbl >> 16) & 0x1fff;
	पूर्ण
	अन्यथा अणु
		/* No: Fake something reasonable which gives at least ok results. */
		vbl_start = mode->crtc_vdisplay;
		vbl_end = 0;
	पूर्ण

	/* Called from driver पूर्णांकernal vblank counter query code? */
	अगर (flags & GET_DISTANCE_TO_VBLANKSTART) अणु
	    /* Caller wants distance from real vbl_start in *hpos */
	    *hpos = *vpos - vbl_start;
	पूर्ण

	/* Fudge vblank to start a few scanlines earlier to handle the
	 * problem that vblank irqs fire a few scanlines beक्रमe start
	 * of vblank. Some driver पूर्णांकernal callers need the true vblank
	 * start to be used and संकेत this via the USE_REAL_VBLANKSTART flag.
	 *
	 * The cause of the "early" vblank irq is that the irq is triggered
	 * by the line buffer logic when the line buffer पढ़ो position enters
	 * the vblank, whereas our crtc scanout position naturally lags the
	 * line buffer पढ़ो position.
	 */
	अगर (!(flags & USE_REAL_VBLANKSTART))
		vbl_start -= adev->mode_info.crtcs[pipe]->lb_vblank_lead_lines;

	/* Test scanout position against vblank region. */
	अगर ((*vpos < vbl_start) && (*vpos >= vbl_end))
		in_vbl = false;

	/* In vblank? */
	अगर (in_vbl)
	    ret |= DRM_SCANOUTPOS_IN_VBLANK;

	/* Called from driver पूर्णांकernal vblank counter query code? */
	अगर (flags & GET_DISTANCE_TO_VBLANKSTART) अणु
		/* Caller wants distance from fudged earlier vbl_start */
		*vpos -= vbl_start;
		वापस ret;
	पूर्ण

	/* Check अगर inside vblank area and apply corrective offsets:
	 * vpos will then be >=0 in video scanout area, but negative
	 * within vblank area, counting करोwn the number of lines until
	 * start of scanout.
	 */

	/* Inside "upper part" of vblank area? Apply corrective offset अगर so: */
	अगर (in_vbl && (*vpos >= vbl_start)) अणु
		vtotal = mode->crtc_vtotal;

		/* With variable refresh rate displays the vpos can exceed
		 * the vtotal value. Clamp to 0 to वापस -vbl_end instead
		 * of guessing the reमुख्यing number of lines until scanout.
		 */
		*vpos = (*vpos < vtotal) ? (*vpos - vtotal) : 0;
	पूर्ण

	/* Correct क्रम shअगरted end of vbl at vbl_end. */
	*vpos = *vpos - vbl_end;

	वापस ret;
पूर्ण

पूर्णांक amdgpu_display_crtc_idx_to_irq_type(काष्ठा amdgpu_device *adev, पूर्णांक crtc)
अणु
	अगर (crtc < 0 || crtc >= adev->mode_info.num_crtc)
		वापस AMDGPU_CRTC_IRQ_NONE;

	चयन (crtc) अणु
	हाल 0:
		वापस AMDGPU_CRTC_IRQ_VBLANK1;
	हाल 1:
		वापस AMDGPU_CRTC_IRQ_VBLANK2;
	हाल 2:
		वापस AMDGPU_CRTC_IRQ_VBLANK3;
	हाल 3:
		वापस AMDGPU_CRTC_IRQ_VBLANK4;
	हाल 4:
		वापस AMDGPU_CRTC_IRQ_VBLANK5;
	हाल 5:
		वापस AMDGPU_CRTC_IRQ_VBLANK6;
	शेष:
		वापस AMDGPU_CRTC_IRQ_NONE;
	पूर्ण
पूर्ण

bool amdgpu_crtc_get_scanout_position(काष्ठा drm_crtc *crtc,
			bool in_vblank_irq, पूर्णांक *vpos,
			पूर्णांक *hpos, kसमय_प्रकार *sसमय, kसमय_प्रकार *eसमय,
			स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	अचिन्हित पूर्णांक pipe = crtc->index;

	वापस amdgpu_display_get_crtc_scanoutpos(dev, pipe, 0, vpos, hpos,
						  sसमय, eसमय, mode);
पूर्ण

पूर्णांक amdgpu_display_suspend_helper(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा drm_device *dev = adev_to_drm(adev);
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter iter;
	पूर्णांक r;

	/* turn off display hw */
	drm_modeset_lock_all(dev);
	drm_connector_list_iter_begin(dev, &iter);
	drm_क्रम_each_connector_iter(connector, &iter)
		drm_helper_connector_dpms(connector,
					  DRM_MODE_DPMS_OFF);
	drm_connector_list_iter_end(&iter);
	drm_modeset_unlock_all(dev);
	/* unpin the front buffers and cursors */
	list_क्रम_each_entry(crtc, &dev->mode_config.crtc_list, head) अणु
		काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
		काष्ठा drm_framebuffer *fb = crtc->primary->fb;
		काष्ठा amdgpu_bo *robj;

		अगर (amdgpu_crtc->cursor_bo && !adev->enable_भव_display) अणु
			काष्ठा amdgpu_bo *aobj = gem_to_amdgpu_bo(amdgpu_crtc->cursor_bo);
			r = amdgpu_bo_reserve(aobj, true);
			अगर (r == 0) अणु
				amdgpu_bo_unpin(aobj);
				amdgpu_bo_unreserve(aobj);
			पूर्ण
		पूर्ण

		अगर (fb == शून्य || fb->obj[0] == शून्य) अणु
			जारी;
		पूर्ण
		robj = gem_to_amdgpu_bo(fb->obj[0]);
		/* करोn't unpin kernel fb objects */
		अगर (!amdgpu_fbdev_robj_is_fb(adev, robj)) अणु
			r = amdgpu_bo_reserve(robj, true);
			अगर (r == 0) अणु
				amdgpu_bo_unpin(robj);
				amdgpu_bo_unreserve(robj);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक amdgpu_display_resume_helper(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा drm_device *dev = adev_to_drm(adev);
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter iter;
	काष्ठा drm_crtc *crtc;
	पूर्णांक r;

	/* pin cursors */
	list_क्रम_each_entry(crtc, &dev->mode_config.crtc_list, head) अणु
		काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);

		अगर (amdgpu_crtc->cursor_bo && !adev->enable_भव_display) अणु
			काष्ठा amdgpu_bo *aobj = gem_to_amdgpu_bo(amdgpu_crtc->cursor_bo);
			r = amdgpu_bo_reserve(aobj, true);
			अगर (r == 0) अणु
				r = amdgpu_bo_pin(aobj, AMDGPU_GEM_DOMAIN_VRAM);
				अगर (r != 0)
					dev_err(adev->dev, "Failed to pin cursor BO (%d)\n", r);
				amdgpu_crtc->cursor_addr = amdgpu_bo_gpu_offset(aobj);
				amdgpu_bo_unreserve(aobj);
			पूर्ण
		पूर्ण
	पूर्ण

	drm_helper_resume_क्रमce_mode(dev);

	/* turn on display hw */
	drm_modeset_lock_all(dev);

	drm_connector_list_iter_begin(dev, &iter);
	drm_क्रम_each_connector_iter(connector, &iter)
		drm_helper_connector_dpms(connector,
					  DRM_MODE_DPMS_ON);
	drm_connector_list_iter_end(&iter);

	drm_modeset_unlock_all(dev);

	वापस 0;
पूर्ण

