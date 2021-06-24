<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
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
 * Authors: AMD
 *
 */

/* The caprices of the preprocessor require that this be declared right here */
#घोषणा CREATE_TRACE_POINTS

#समावेश "dm_services_types.h"
#समावेश "dc.h"
#समावेश "dc/inc/core_types.h"
#समावेश "dal_asic_id.h"
#समावेश "dmub/dmub_srv.h"
#समावेश "dc/inc/hw/dmcu.h"
#समावेश "dc/inc/hw/abm.h"
#समावेश "dc/dc_dmub_srv.h"
#समावेश "dc/dc_edid_parser.h"
#समावेश "amdgpu_dm_trace.h"

#समावेश "vid.h"
#समावेश "amdgpu.h"
#समावेश "amdgpu_display.h"
#समावेश "amdgpu_ucode.h"
#समावेश "atom.h"
#समावेश "amdgpu_dm.h"
#अगर_घोषित CONFIG_DRM_AMD_DC_HDCP
#समावेश "amdgpu_dm_hdcp.h"
#समावेश <drm/drm_hdcp.h>
#पूर्ण_अगर
#समावेश "amdgpu_pm.h"

#समावेश "amd_shared.h"
#समावेश "amdgpu_dm_irq.h"
#समावेश "dm_helpers.h"
#समावेश "amdgpu_dm_mst_types.h"
#अगर defined(CONFIG_DEBUG_FS)
#समावेश "amdgpu_dm_debugfs.h"
#पूर्ण_अगर

#समावेश "ivsrcid/ivsrcid_vislands30.h"

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pci.h>
#समावेश <linux/firmware.h>
#समावेश <linux/component.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_uapi.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_dp_mst_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_vblank.h>
#समावेश <drm/drm_audio_component.h>

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
#समावेश "ivsrcid/dcn/irqsrcs_dcn_1_0.h"

#समावेश "dcn/dcn_1_0_offset.h"
#समावेश "dcn/dcn_1_0_sh_mask.h"
#समावेश "soc15_hw_ip.h"
#समावेश "vega10_ip_offset.h"

#समावेश "soc15_common.h"
#पूर्ण_अगर

#समावेश "modules/inc/mod_freesync.h"
#समावेश "modules/power/power_helpers.h"
#समावेश "modules/inc/mod_info_packet.h"

#घोषणा FIRMWARE_RENOIR_DMUB "amdgpu/renoir_dmcub.bin"
MODULE_FIRMWARE(FIRMWARE_RENOIR_DMUB);
#घोषणा FIRMWARE_SIENNA_CICHLID_DMUB "amdgpu/sienna_cichlid_dmcub.bin"
MODULE_FIRMWARE(FIRMWARE_SIENNA_CICHLID_DMUB);
#घोषणा FIRMWARE_NAVY_FLOUNDER_DMUB "amdgpu/navy_flounder_dmcub.bin"
MODULE_FIRMWARE(FIRMWARE_NAVY_FLOUNDER_DMUB);
#घोषणा FIRMWARE_GREEN_SARDINE_DMUB "amdgpu/green_sardine_dmcub.bin"
MODULE_FIRMWARE(FIRMWARE_GREEN_SARDINE_DMUB);
#घोषणा FIRMWARE_VANGOGH_DMUB "amdgpu/vangogh_dmcub.bin"
MODULE_FIRMWARE(FIRMWARE_VANGOGH_DMUB);
#घोषणा FIRMWARE_DIMGREY_CAVEFISH_DMUB "amdgpu/dimgrey_cavefish_dmcub.bin"
MODULE_FIRMWARE(FIRMWARE_DIMGREY_CAVEFISH_DMUB);

#घोषणा FIRMWARE_RAVEN_DMCU		"amdgpu/raven_dmcu.bin"
MODULE_FIRMWARE(FIRMWARE_RAVEN_DMCU);

#घोषणा FIRMWARE_NAVI12_DMCU            "amdgpu/navi12_dmcu.bin"
MODULE_FIRMWARE(FIRMWARE_NAVI12_DMCU);

/* Number of bytes in PSP header क्रम firmware. */
#घोषणा PSP_HEADER_BYTES 0x100

/* Number of bytes in PSP footer क्रम firmware. */
#घोषणा PSP_FOOTER_BYTES 0x100

/**
 * DOC: overview
 *
 * The AMDgpu display manager, **amdgpu_dm** (or even simpler,
 * **dm**) sits between DRM and DC. It acts as a liaison, converting DRM
 * requests पूर्णांकo DC requests, and DC responses पूर्णांकo DRM responses.
 *
 * The root control काष्ठाure is &काष्ठा amdgpu_display_manager.
 */

/* basic init/fini API */
अटल पूर्णांक amdgpu_dm_init(काष्ठा amdgpu_device *adev);
अटल व्योम amdgpu_dm_fini(काष्ठा amdgpu_device *adev);
अटल bool is_मुक्तsync_video_mode(स्थिर काष्ठा drm_display_mode *mode, काष्ठा amdgpu_dm_connector *aconnector);

अटल क्रमागत drm_mode_subconnector get_subconnector_type(काष्ठा dc_link *link)
अणु
	चयन (link->dpcd_caps.करोngle_type) अणु
	हाल DISPLAY_DONGLE_NONE:
		वापस DRM_MODE_SUBCONNECTOR_Native;
	हाल DISPLAY_DONGLE_DP_VGA_CONVERTER:
		वापस DRM_MODE_SUBCONNECTOR_VGA;
	हाल DISPLAY_DONGLE_DP_DVI_CONVERTER:
	हाल DISPLAY_DONGLE_DP_DVI_DONGLE:
		वापस DRM_MODE_SUBCONNECTOR_DVID;
	हाल DISPLAY_DONGLE_DP_HDMI_CONVERTER:
	हाल DISPLAY_DONGLE_DP_HDMI_DONGLE:
		वापस DRM_MODE_SUBCONNECTOR_HDMIA;
	हाल DISPLAY_DONGLE_DP_HDMI_MISMATCHED_DONGLE:
	शेष:
		वापस DRM_MODE_SUBCONNECTOR_Unknown;
	पूर्ण
पूर्ण

अटल व्योम update_subconnector_property(काष्ठा amdgpu_dm_connector *aconnector)
अणु
	काष्ठा dc_link *link = aconnector->dc_link;
	काष्ठा drm_connector *connector = &aconnector->base;
	क्रमागत drm_mode_subconnector subconnector = DRM_MODE_SUBCONNECTOR_Unknown;

	अगर (connector->connector_type != DRM_MODE_CONNECTOR_DisplayPort)
		वापस;

	अगर (aconnector->dc_sink)
		subconnector = get_subconnector_type(link);

	drm_object_property_set_value(&connector->base,
			connector->dev->mode_config.dp_subconnector_property,
			subconnector);
पूर्ण

/*
 * initializes drm_device display related काष्ठाures, based on the inक्रमmation
 * provided by DAL. The drm strcutures are: drm_crtc, drm_connector,
 * drm_encoder, drm_mode_config
 *
 * Returns 0 on success
 */
अटल पूर्णांक amdgpu_dm_initialize_drm_device(काष्ठा amdgpu_device *adev);
/* हटाओs and deallocates the drm काष्ठाures, created by the above function */
अटल व्योम amdgpu_dm_destroy_drm_device(काष्ठा amdgpu_display_manager *dm);

अटल पूर्णांक amdgpu_dm_plane_init(काष्ठा amdgpu_display_manager *dm,
				काष्ठा drm_plane *plane,
				अचिन्हित दीर्घ possible_crtcs,
				स्थिर काष्ठा dc_plane_cap *plane_cap);
अटल पूर्णांक amdgpu_dm_crtc_init(काष्ठा amdgpu_display_manager *dm,
			       काष्ठा drm_plane *plane,
			       uपूर्णांक32_t link_index);
अटल पूर्णांक amdgpu_dm_connector_init(काष्ठा amdgpu_display_manager *dm,
				    काष्ठा amdgpu_dm_connector *amdgpu_dm_connector,
				    uपूर्णांक32_t link_index,
				    काष्ठा amdgpu_encoder *amdgpu_encoder);
अटल पूर्णांक amdgpu_dm_encoder_init(काष्ठा drm_device *dev,
				  काष्ठा amdgpu_encoder *aencoder,
				  uपूर्णांक32_t link_index);

अटल पूर्णांक amdgpu_dm_connector_get_modes(काष्ठा drm_connector *connector);

अटल व्योम amdgpu_dm_atomic_commit_tail(काष्ठा drm_atomic_state *state);

अटल पूर्णांक amdgpu_dm_atomic_check(काष्ठा drm_device *dev,
				  काष्ठा drm_atomic_state *state);

अटल व्योम handle_cursor_update(काष्ठा drm_plane *plane,
				 काष्ठा drm_plane_state *old_plane_state);

अटल व्योम amdgpu_dm_set_psr_caps(काष्ठा dc_link *link);
अटल bool amdgpu_dm_psr_enable(काष्ठा dc_stream_state *stream);
अटल bool amdgpu_dm_link_setup_psr(काष्ठा dc_stream_state *stream);
अटल bool amdgpu_dm_psr_disable(काष्ठा dc_stream_state *stream);
अटल bool amdgpu_dm_psr_disable_all(काष्ठा amdgpu_display_manager *dm);

अटल स्थिर काष्ठा drm_क्रमmat_info *
amd_get_क्रमmat_info(स्थिर काष्ठा drm_mode_fb_cmd2 *cmd);

अटल bool
is_timing_unchanged_क्रम_मुक्तsync(काष्ठा drm_crtc_state *old_crtc_state,
				 काष्ठा drm_crtc_state *new_crtc_state);
/*
 * dm_vblank_get_counter
 *
 * @brief
 * Get counter क्रम number of vertical blanks
 *
 * @param
 * काष्ठा amdgpu_device *adev - [in] desired amdgpu device
 * पूर्णांक disp_idx - [in] which CRTC to get the counter from
 *
 * @वापस
 * Counter क्रम vertical blanks
 */
अटल u32 dm_vblank_get_counter(काष्ठा amdgpu_device *adev, पूर्णांक crtc)
अणु
	अगर (crtc >= adev->mode_info.num_crtc)
		वापस 0;
	अन्यथा अणु
		काष्ठा amdgpu_crtc *acrtc = adev->mode_info.crtcs[crtc];

		अगर (acrtc->dm_irq_params.stream == शून्य) अणु
			DRM_ERROR("dc_stream_state is NULL for crtc '%d'!\n",
				  crtc);
			वापस 0;
		पूर्ण

		वापस dc_stream_get_vblank_counter(acrtc->dm_irq_params.stream);
	पूर्ण
पूर्ण

अटल पूर्णांक dm_crtc_get_scanoutpos(काष्ठा amdgpu_device *adev, पूर्णांक crtc,
				  u32 *vbl, u32 *position)
अणु
	uपूर्णांक32_t v_blank_start, v_blank_end, h_position, v_position;

	अगर ((crtc < 0) || (crtc >= adev->mode_info.num_crtc))
		वापस -EINVAL;
	अन्यथा अणु
		काष्ठा amdgpu_crtc *acrtc = adev->mode_info.crtcs[crtc];

		अगर (acrtc->dm_irq_params.stream ==  शून्य) अणु
			DRM_ERROR("dc_stream_state is NULL for crtc '%d'!\n",
				  crtc);
			वापस 0;
		पूर्ण

		/*
		 * TODO rework base driver to use values directly.
		 * क्रम now parse it back पूर्णांकo reg-क्रमmat
		 */
		dc_stream_get_scanoutpos(acrtc->dm_irq_params.stream,
					 &v_blank_start,
					 &v_blank_end,
					 &h_position,
					 &v_position);

		*position = v_position | (h_position << 16);
		*vbl = v_blank_start | (v_blank_end << 16);
	पूर्ण

	वापस 0;
पूर्ण

अटल bool dm_is_idle(व्योम *handle)
अणु
	/* XXX toकरो */
	वापस true;
पूर्ण

अटल पूर्णांक dm_रुको_क्रम_idle(व्योम *handle)
अणु
	/* XXX toकरो */
	वापस 0;
पूर्ण

अटल bool dm_check_soft_reset(व्योम *handle)
अणु
	वापस false;
पूर्ण

अटल पूर्णांक dm_soft_reset(व्योम *handle)
अणु
	/* XXX toकरो */
	वापस 0;
पूर्ण

अटल काष्ठा amdgpu_crtc *
get_crtc_by_otg_inst(काष्ठा amdgpu_device *adev,
		     पूर्णांक otg_inst)
अणु
	काष्ठा drm_device *dev = adev_to_drm(adev);
	काष्ठा drm_crtc *crtc;
	काष्ठा amdgpu_crtc *amdgpu_crtc;

	अगर (otg_inst == -1) अणु
		WARN_ON(1);
		वापस adev->mode_info.crtcs[0];
	पूर्ण

	list_क्रम_each_entry(crtc, &dev->mode_config.crtc_list, head) अणु
		amdgpu_crtc = to_amdgpu_crtc(crtc);

		अगर (amdgpu_crtc->otg_inst == otg_inst)
			वापस amdgpu_crtc;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अंतरभूत bool amdgpu_dm_vrr_active_irq(काष्ठा amdgpu_crtc *acrtc)
अणु
	वापस acrtc->dm_irq_params.मुक्तsync_config.state ==
		       VRR_STATE_ACTIVE_VARIABLE ||
	       acrtc->dm_irq_params.मुक्तsync_config.state ==
		       VRR_STATE_ACTIVE_FIXED;
पूर्ण

अटल अंतरभूत bool amdgpu_dm_vrr_active(काष्ठा dm_crtc_state *dm_state)
अणु
	वापस dm_state->मुक्तsync_config.state == VRR_STATE_ACTIVE_VARIABLE ||
	       dm_state->मुक्तsync_config.state == VRR_STATE_ACTIVE_FIXED;
पूर्ण

अटल अंतरभूत bool is_dc_timing_adjust_needed(काष्ठा dm_crtc_state *old_state,
					      काष्ठा dm_crtc_state *new_state)
अणु
	अगर (new_state->मुक्तsync_config.state ==  VRR_STATE_ACTIVE_FIXED)
		वापस true;
	अन्यथा अगर (amdgpu_dm_vrr_active(old_state) != amdgpu_dm_vrr_active(new_state))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

/**
 * dm_pflip_high_irq() - Handle pageflip पूर्णांकerrupt
 * @पूर्णांकerrupt_params: ignored
 *
 * Handles the pageflip पूर्णांकerrupt by notअगरying all पूर्णांकerested parties
 * that the pageflip has been completed.
 */
अटल व्योम dm_pflip_high_irq(व्योम *पूर्णांकerrupt_params)
अणु
	काष्ठा amdgpu_crtc *amdgpu_crtc;
	काष्ठा common_irq_params *irq_params = पूर्णांकerrupt_params;
	काष्ठा amdgpu_device *adev = irq_params->adev;
	अचिन्हित दीर्घ flags;
	काष्ठा drm_pending_vblank_event *e;
	uपूर्णांक32_t vpos, hpos, v_blank_start, v_blank_end;
	bool vrr_active;

	amdgpu_crtc = get_crtc_by_otg_inst(adev, irq_params->irq_src - IRQ_TYPE_PFLIP);

	/* IRQ could occur when in initial stage */
	/* TODO work and BO cleanup */
	अगर (amdgpu_crtc == शून्य) अणु
		DC_LOG_PFLIP("CRTC is null, returning.\n");
		वापस;
	पूर्ण

	spin_lock_irqsave(&adev_to_drm(adev)->event_lock, flags);

	अगर (amdgpu_crtc->pflip_status != AMDGPU_FLIP_SUBMITTED)अणु
		DC_LOG_PFLIP("amdgpu_crtc->pflip_status = %d !=AMDGPU_FLIP_SUBMITTED(%d) on crtc:%d[%p] \n",
						 amdgpu_crtc->pflip_status,
						 AMDGPU_FLIP_SUBMITTED,
						 amdgpu_crtc->crtc_id,
						 amdgpu_crtc);
		spin_unlock_irqrestore(&adev_to_drm(adev)->event_lock, flags);
		वापस;
	पूर्ण

	/* page flip completed. */
	e = amdgpu_crtc->event;
	amdgpu_crtc->event = शून्य;

	अगर (!e)
		WARN_ON(1);

	vrr_active = amdgpu_dm_vrr_active_irq(amdgpu_crtc);

	/* Fixed refresh rate, or VRR scanout position outside front-porch? */
	अगर (!vrr_active ||
	    !dc_stream_get_scanoutpos(amdgpu_crtc->dm_irq_params.stream, &v_blank_start,
				      &v_blank_end, &hpos, &vpos) ||
	    (vpos < v_blank_start)) अणु
		/* Update to correct count and vblank बारtamp अगर racing with
		 * vblank irq. This also updates to the correct vblank बारtamp
		 * even in VRR mode, as scanout is past the front-porch aपंचांग.
		 */
		drm_crtc_accurate_vblank_count(&amdgpu_crtc->base);

		/* Wake up userspace by sending the pageflip event with proper
		 * count and बारtamp of vblank of flip completion.
		 */
		अगर (e) अणु
			drm_crtc_send_vblank_event(&amdgpu_crtc->base, e);

			/* Event sent, so करोne with vblank क्रम this flip */
			drm_crtc_vblank_put(&amdgpu_crtc->base);
		पूर्ण
	पूर्ण अन्यथा अगर (e) अणु
		/* VRR active and inside front-porch: vblank count and
		 * बारtamp क्रम pageflip event will only be up to date after
		 * drm_crtc_handle_vblank() has been executed from late vblank
		 * irq handler after start of back-porch (vline 0). We queue the
		 * pageflip event क्रम send-out by drm_crtc_handle_vblank() with
		 * updated बारtamp and count, once it runs after us.
		 *
		 * We need to खोलो-code this instead of using the helper
		 * drm_crtc_arm_vblank_event(), as that helper would
		 * call drm_crtc_accurate_vblank_count(), which we must
		 * not call in VRR mode जबतक we are in front-porch!
		 */

		/* sequence will be replaced by real count during send-out. */
		e->sequence = drm_crtc_vblank_count(&amdgpu_crtc->base);
		e->pipe = amdgpu_crtc->crtc_id;

		list_add_tail(&e->base.link, &adev_to_drm(adev)->vblank_event_list);
		e = शून्य;
	पूर्ण

	/* Keep track of vblank of this flip क्रम flip throttling. We use the
	 * cooked hw counter, as that one incremented at start of this vblank
	 * of pageflip completion, so last_flip_vblank is the क्रमbidden count
	 * क्रम queueing new pageflips अगर vsync + VRR is enabled.
	 */
	amdgpu_crtc->dm_irq_params.last_flip_vblank =
		amdgpu_get_vblank_counter_kms(&amdgpu_crtc->base);

	amdgpu_crtc->pflip_status = AMDGPU_FLIP_NONE;
	spin_unlock_irqrestore(&adev_to_drm(adev)->event_lock, flags);

	DC_LOG_PFLIP("crtc:%d[%p], pflip_stat:AMDGPU_FLIP_NONE, vrr[%d]-fp %d\n",
		     amdgpu_crtc->crtc_id, amdgpu_crtc,
		     vrr_active, (पूर्णांक) !e);
पूर्ण

अटल व्योम dm_vupdate_high_irq(व्योम *पूर्णांकerrupt_params)
अणु
	काष्ठा common_irq_params *irq_params = पूर्णांकerrupt_params;
	काष्ठा amdgpu_device *adev = irq_params->adev;
	काष्ठा amdgpu_crtc *acrtc;
	काष्ठा drm_device *drm_dev;
	काष्ठा drm_vblank_crtc *vblank;
	kसमय_प्रकार frame_duration_ns, previous_बारtamp;
	अचिन्हित दीर्घ flags;
	पूर्णांक vrr_active;

	acrtc = get_crtc_by_otg_inst(adev, irq_params->irq_src - IRQ_TYPE_VUPDATE);

	अगर (acrtc) अणु
		vrr_active = amdgpu_dm_vrr_active_irq(acrtc);
		drm_dev = acrtc->base.dev;
		vblank = &drm_dev->vblank[acrtc->base.index];
		previous_बारtamp = atomic64_पढ़ो(&irq_params->previous_बारtamp);
		frame_duration_ns = vblank->समय - previous_बारtamp;

		अगर (frame_duration_ns > 0) अणु
			trace_amdgpu_refresh_rate_track(acrtc->base.index,
						frame_duration_ns,
						kसमय_भागns(NSEC_PER_SEC, frame_duration_ns));
			atomic64_set(&irq_params->previous_बारtamp, vblank->समय);
		पूर्ण

		DC_LOG_VBLANK("crtc:%d, vupdate-vrr:%d\n",
			      acrtc->crtc_id,
			      vrr_active);

		/* Core vblank handling is करोne here after end of front-porch in
		 * vrr mode, as vblank बारtamping will give valid results
		 * जबतक now करोne after front-porch. This will also deliver
		 * page-flip completion events that have been queued to us
		 * अगर a pageflip happened inside front-porch.
		 */
		अगर (vrr_active) अणु
			drm_crtc_handle_vblank(&acrtc->base);

			/* BTR processing क्रम pre-DCE12 ASICs */
			अगर (acrtc->dm_irq_params.stream &&
			    adev->family < AMDGPU_FAMILY_AI) अणु
				spin_lock_irqsave(&adev_to_drm(adev)->event_lock, flags);
				mod_मुक्तsync_handle_v_update(
				    adev->dm.मुक्तsync_module,
				    acrtc->dm_irq_params.stream,
				    &acrtc->dm_irq_params.vrr_params);

				dc_stream_adjust_vmin_vmax(
				    adev->dm.dc,
				    acrtc->dm_irq_params.stream,
				    &acrtc->dm_irq_params.vrr_params.adjust);
				spin_unlock_irqrestore(&adev_to_drm(adev)->event_lock, flags);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/**
 * dm_crtc_high_irq() - Handles CRTC पूर्णांकerrupt
 * @पूर्णांकerrupt_params: used क्रम determining the CRTC instance
 *
 * Handles the CRTC/VSYNC पूर्णांकerrupt by notfying DRM's VBLANK
 * event handler.
 */
अटल व्योम dm_crtc_high_irq(व्योम *पूर्णांकerrupt_params)
अणु
	काष्ठा common_irq_params *irq_params = पूर्णांकerrupt_params;
	काष्ठा amdgpu_device *adev = irq_params->adev;
	काष्ठा amdgpu_crtc *acrtc;
	अचिन्हित दीर्घ flags;
	पूर्णांक vrr_active;

	acrtc = get_crtc_by_otg_inst(adev, irq_params->irq_src - IRQ_TYPE_VBLANK);
	अगर (!acrtc)
		वापस;

	vrr_active = amdgpu_dm_vrr_active_irq(acrtc);

	DC_LOG_VBLANK("crtc:%d, vupdate-vrr:%d, planes:%d\n", acrtc->crtc_id,
		      vrr_active, acrtc->dm_irq_params.active_planes);

	/**
	 * Core vblank handling at start of front-porch is only possible
	 * in non-vrr mode, as only there vblank बारtamping will give
	 * valid results जबतक करोne in front-porch. Otherwise defer it
	 * to dm_vupdate_high_irq after end of front-porch.
	 */
	अगर (!vrr_active)
		drm_crtc_handle_vblank(&acrtc->base);

	/**
	 * Following stuff must happen at start of vblank, क्रम crc
	 * computation and below-the-range btr support in vrr mode.
	 */
	amdgpu_dm_crtc_handle_crc_irq(&acrtc->base);

	/* BTR updates need to happen beक्रमe VUPDATE on Vega and above. */
	अगर (adev->family < AMDGPU_FAMILY_AI)
		वापस;

	spin_lock_irqsave(&adev_to_drm(adev)->event_lock, flags);

	अगर (acrtc->dm_irq_params.stream &&
	    acrtc->dm_irq_params.vrr_params.supported &&
	    acrtc->dm_irq_params.मुक्तsync_config.state ==
		    VRR_STATE_ACTIVE_VARIABLE) अणु
		mod_मुक्तsync_handle_v_update(adev->dm.मुक्तsync_module,
					     acrtc->dm_irq_params.stream,
					     &acrtc->dm_irq_params.vrr_params);

		dc_stream_adjust_vmin_vmax(adev->dm.dc, acrtc->dm_irq_params.stream,
					   &acrtc->dm_irq_params.vrr_params.adjust);
	पूर्ण

	/*
	 * If there aren't any active_planes then DCH HUBP may be घड़ी-gated.
	 * In that हाल, pageflip completion पूर्णांकerrupts won't fire and pageflip
	 * completion events won't get delivered. Prevent this by sending
	 * pending pageflip events from here अगर a flip is still pending.
	 *
	 * If any planes are enabled, use dm_pflip_high_irq() instead, to
	 * aव्योम race conditions between flip programming and completion,
	 * which could cause too early flip completion events.
	 */
	अगर (adev->family >= AMDGPU_FAMILY_RV &&
	    acrtc->pflip_status == AMDGPU_FLIP_SUBMITTED &&
	    acrtc->dm_irq_params.active_planes == 0) अणु
		अगर (acrtc->event) अणु
			drm_crtc_send_vblank_event(&acrtc->base, acrtc->event);
			acrtc->event = शून्य;
			drm_crtc_vblank_put(&acrtc->base);
		पूर्ण
		acrtc->pflip_status = AMDGPU_FLIP_NONE;
	पूर्ण

	spin_unlock_irqrestore(&adev_to_drm(adev)->event_lock, flags);
पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
/**
 * dm_dcn_vertical_पूर्णांकerrupt0_high_irq() - Handles OTG Vertical पूर्णांकerrupt0 क्रम
 * DCN generation ASICs
 * @पूर्णांकerrupt params - पूर्णांकerrupt parameters
 *
 * Used to set crc winकरोw/पढ़ो out crc value at vertical line 0 position
 */
#अगर defined(CONFIG_DRM_AMD_SECURE_DISPLAY)
अटल व्योम dm_dcn_vertical_पूर्णांकerrupt0_high_irq(व्योम *पूर्णांकerrupt_params)
अणु
	काष्ठा common_irq_params *irq_params = पूर्णांकerrupt_params;
	काष्ठा amdgpu_device *adev = irq_params->adev;
	काष्ठा amdgpu_crtc *acrtc;

	acrtc = get_crtc_by_otg_inst(adev, irq_params->irq_src - IRQ_TYPE_VLINE0);

	अगर (!acrtc)
		वापस;

	amdgpu_dm_crtc_handle_crc_winकरोw_irq(&acrtc->base);
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

अटल पूर्णांक dm_set_घड़ीgating_state(व्योम *handle,
		  क्रमागत amd_घड़ीgating_state state)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक dm_set_घातergating_state(व्योम *handle,
		  क्रमागत amd_घातergating_state state)
अणु
	वापस 0;
पूर्ण

/* Prototypes of निजी functions */
अटल पूर्णांक dm_early_init(व्योम* handle);

/* Allocate memory क्रम FBC compressed data  */
अटल व्योम amdgpu_dm_fbc_init(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा dm_compressor_info *compressor = &adev->dm.compressor;
	काष्ठा amdgpu_dm_connector *aconn = to_amdgpu_dm_connector(connector);
	काष्ठा drm_display_mode *mode;
	अचिन्हित दीर्घ max_size = 0;

	अगर (adev->dm.dc->fbc_compressor == शून्य)
		वापस;

	अगर (aconn->dc_link->connector_संकेत != SIGNAL_TYPE_EDP)
		वापस;

	अगर (compressor->bo_ptr)
		वापस;


	list_क्रम_each_entry(mode, &connector->modes, head) अणु
		अगर (max_size < mode->htotal * mode->vtotal)
			max_size = mode->htotal * mode->vtotal;
	पूर्ण

	अगर (max_size) अणु
		पूर्णांक r = amdgpu_bo_create_kernel(adev, max_size * 4, PAGE_SIZE,
			    AMDGPU_GEM_DOMAIN_GTT, &compressor->bo_ptr,
			    &compressor->gpu_addr, &compressor->cpu_addr);

		अगर (r)
			DRM_ERROR("DM: Failed to initialize FBC\n");
		अन्यथा अणु
			adev->dm.dc->ctx->fbc_gpu_addr = compressor->gpu_addr;
			DRM_INFO("DM: FBC alloc %lu\n", max_size*4);
		पूर्ण

	पूर्ण

पूर्ण

अटल पूर्णांक amdgpu_dm_audio_component_get_eld(काष्ठा device *kdev, पूर्णांक port,
					  पूर्णांक pipe, bool *enabled,
					  अचिन्हित अक्षर *buf, पूर्णांक max_bytes)
अणु
	काष्ठा drm_device *dev = dev_get_drvdata(kdev);
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;
	काष्ठा amdgpu_dm_connector *aconnector;
	पूर्णांक ret = 0;

	*enabled = false;

	mutex_lock(&adev->dm.audio_lock);

	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter) अणु
		aconnector = to_amdgpu_dm_connector(connector);
		अगर (aconnector->audio_inst != port)
			जारी;

		*enabled = true;
		ret = drm_eld_size(connector->eld);
		स_नकल(buf, connector->eld, min(max_bytes, ret));

		अवरोध;
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	mutex_unlock(&adev->dm.audio_lock);

	DRM_DEBUG_KMS("Get ELD : idx=%d ret=%d en=%d\n", port, ret, *enabled);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा drm_audio_component_ops amdgpu_dm_audio_component_ops = अणु
	.get_eld = amdgpu_dm_audio_component_get_eld,
पूर्ण;

अटल पूर्णांक amdgpu_dm_audio_component_bind(काष्ठा device *kdev,
				       काष्ठा device *hda_kdev, व्योम *data)
अणु
	काष्ठा drm_device *dev = dev_get_drvdata(kdev);
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा drm_audio_component *acomp = data;

	acomp->ops = &amdgpu_dm_audio_component_ops;
	acomp->dev = kdev;
	adev->dm.audio_component = acomp;

	वापस 0;
पूर्ण

अटल व्योम amdgpu_dm_audio_component_unbind(काष्ठा device *kdev,
					  काष्ठा device *hda_kdev, व्योम *data)
अणु
	काष्ठा drm_device *dev = dev_get_drvdata(kdev);
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा drm_audio_component *acomp = data;

	acomp->ops = शून्य;
	acomp->dev = शून्य;
	adev->dm.audio_component = शून्य;
पूर्ण

अटल स्थिर काष्ठा component_ops amdgpu_dm_audio_component_bind_ops = अणु
	.bind	= amdgpu_dm_audio_component_bind,
	.unbind	= amdgpu_dm_audio_component_unbind,
पूर्ण;

अटल पूर्णांक amdgpu_dm_audio_init(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i, ret;

	अगर (!amdgpu_audio)
		वापस 0;

	adev->mode_info.audio.enabled = true;

	adev->mode_info.audio.num_pins = adev->dm.dc->res_pool->audio_count;

	क्रम (i = 0; i < adev->mode_info.audio.num_pins; i++) अणु
		adev->mode_info.audio.pin[i].channels = -1;
		adev->mode_info.audio.pin[i].rate = -1;
		adev->mode_info.audio.pin[i].bits_per_sample = -1;
		adev->mode_info.audio.pin[i].status_bits = 0;
		adev->mode_info.audio.pin[i].category_code = 0;
		adev->mode_info.audio.pin[i].connected = false;
		adev->mode_info.audio.pin[i].id =
			adev->dm.dc->res_pool->audios[i]->inst;
		adev->mode_info.audio.pin[i].offset = 0;
	पूर्ण

	ret = component_add(adev->dev, &amdgpu_dm_audio_component_bind_ops);
	अगर (ret < 0)
		वापस ret;

	adev->dm.audio_रेजिस्टरed = true;

	वापस 0;
पूर्ण

अटल व्योम amdgpu_dm_audio_fini(काष्ठा amdgpu_device *adev)
अणु
	अगर (!amdgpu_audio)
		वापस;

	अगर (!adev->mode_info.audio.enabled)
		वापस;

	अगर (adev->dm.audio_रेजिस्टरed) अणु
		component_del(adev->dev, &amdgpu_dm_audio_component_bind_ops);
		adev->dm.audio_रेजिस्टरed = false;
	पूर्ण

	/* TODO: Disable audio? */

	adev->mode_info.audio.enabled = false;
पूर्ण

अटल  व्योम amdgpu_dm_audio_eld_notअगरy(काष्ठा amdgpu_device *adev, पूर्णांक pin)
अणु
	काष्ठा drm_audio_component *acomp = adev->dm.audio_component;

	अगर (acomp && acomp->audio_ops && acomp->audio_ops->pin_eld_notअगरy) अणु
		DRM_DEBUG_KMS("Notify ELD: %d\n", pin);

		acomp->audio_ops->pin_eld_notअगरy(acomp->audio_ops->audio_ptr,
						 pin, -1);
	पूर्ण
पूर्ण

अटल पूर्णांक dm_dmub_hw_init(काष्ठा amdgpu_device *adev)
अणु
	स्थिर काष्ठा dmcub_firmware_header_v1_0 *hdr;
	काष्ठा dmub_srv *dmub_srv = adev->dm.dmub_srv;
	काष्ठा dmub_srv_fb_info *fb_info = adev->dm.dmub_fb_info;
	स्थिर काष्ठा firmware *dmub_fw = adev->dm.dmub_fw;
	काष्ठा dmcu *dmcu = adev->dm.dc->res_pool->dmcu;
	काष्ठा abm *abm = adev->dm.dc->res_pool->abm;
	काष्ठा dmub_srv_hw_params hw_params;
	क्रमागत dmub_status status;
	स्थिर अचिन्हित अक्षर *fw_inst_स्थिर, *fw_bss_data;
	uपूर्णांक32_t i, fw_inst_स्थिर_size, fw_bss_data_size;
	bool has_hw_support;

	अगर (!dmub_srv)
		/* DMUB isn't supported on the ASIC. */
		वापस 0;

	अगर (!fb_info) अणु
		DRM_ERROR("No framebuffer info for DMUB service.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!dmub_fw) अणु
		/* Firmware required क्रम DMUB support. */
		DRM_ERROR("No firmware provided for DMUB.\n");
		वापस -EINVAL;
	पूर्ण

	status = dmub_srv_has_hw_support(dmub_srv, &has_hw_support);
	अगर (status != DMUB_STATUS_OK) अणु
		DRM_ERROR("Error checking HW support for DMUB: %d\n", status);
		वापस -EINVAL;
	पूर्ण

	अगर (!has_hw_support) अणु
		DRM_INFO("DMUB unsupported on ASIC\n");
		वापस 0;
	पूर्ण

	hdr = (स्थिर काष्ठा dmcub_firmware_header_v1_0 *)dmub_fw->data;

	fw_inst_स्थिर = dmub_fw->data +
			le32_to_cpu(hdr->header.ucode_array_offset_bytes) +
			PSP_HEADER_BYTES;

	fw_bss_data = dmub_fw->data +
		      le32_to_cpu(hdr->header.ucode_array_offset_bytes) +
		      le32_to_cpu(hdr->inst_स्थिर_bytes);

	/* Copy firmware and bios info पूर्णांकo FB memory. */
	fw_inst_स्थिर_size = le32_to_cpu(hdr->inst_स्थिर_bytes) -
			     PSP_HEADER_BYTES - PSP_FOOTER_BYTES;

	fw_bss_data_size = le32_to_cpu(hdr->bss_data_bytes);

	/* अगर adev->firmware.load_type == AMDGPU_FW_LOAD_PSP,
	 * amdgpu_ucode_init_single_fw will load dmub firmware
	 * fw_inst_स्थिर part to cw0; otherwise, the firmware back करोor load
	 * will be करोne by dm_dmub_hw_init
	 */
	अगर (adev->firmware.load_type != AMDGPU_FW_LOAD_PSP) अणु
		स_नकल(fb_info->fb[DMUB_WINDOW_0_INST_CONST].cpu_addr, fw_inst_स्थिर,
				fw_inst_स्थिर_size);
	पूर्ण

	अगर (fw_bss_data_size)
		स_नकल(fb_info->fb[DMUB_WINDOW_2_BSS_DATA].cpu_addr,
		       fw_bss_data, fw_bss_data_size);

	/* Copy firmware bios info पूर्णांकo FB memory. */
	स_नकल(fb_info->fb[DMUB_WINDOW_3_VBIOS].cpu_addr, adev->bios,
	       adev->bios_size);

	/* Reset regions that need to be reset. */
	स_रखो(fb_info->fb[DMUB_WINDOW_4_MAILBOX].cpu_addr, 0,
	fb_info->fb[DMUB_WINDOW_4_MAILBOX].size);

	स_रखो(fb_info->fb[DMUB_WINDOW_5_TRACEBUFF].cpu_addr, 0,
	       fb_info->fb[DMUB_WINDOW_5_TRACEBUFF].size);

	स_रखो(fb_info->fb[DMUB_WINDOW_6_FW_STATE].cpu_addr, 0,
	       fb_info->fb[DMUB_WINDOW_6_FW_STATE].size);

	/* Initialize hardware. */
	स_रखो(&hw_params, 0, माप(hw_params));
	hw_params.fb_base = adev->gmc.fb_start;
	hw_params.fb_offset = adev->gmc.aper_base;

	/* backकरोor load firmware and trigger dmub running */
	अगर (adev->firmware.load_type != AMDGPU_FW_LOAD_PSP)
		hw_params.load_inst_स्थिर = true;

	अगर (dmcu)
		hw_params.psp_version = dmcu->psp_version;

	क्रम (i = 0; i < fb_info->num_fb; ++i)
		hw_params.fb[i] = &fb_info->fb[i];

	status = dmub_srv_hw_init(dmub_srv, &hw_params);
	अगर (status != DMUB_STATUS_OK) अणु
		DRM_ERROR("Error initializing DMUB HW: %d\n", status);
		वापस -EINVAL;
	पूर्ण

	/* Wait क्रम firmware load to finish. */
	status = dmub_srv_रुको_क्रम_स्वतः_load(dmub_srv, 100000);
	अगर (status != DMUB_STATUS_OK)
		DRM_WARN("Wait for DMUB auto-load failed: %d\n", status);

	/* Init DMCU and ABM अगर available. */
	अगर (dmcu && abm) अणु
		dmcu->funcs->dmcu_init(dmcu);
		abm->dmcu_is_running = dmcu->funcs->is_dmcu_initialized(dmcu);
	पूर्ण

	अगर (!adev->dm.dc->ctx->dmub_srv)
		adev->dm.dc->ctx->dmub_srv = dc_dmub_srv_create(adev->dm.dc, dmub_srv);
	अगर (!adev->dm.dc->ctx->dmub_srv) अणु
		DRM_ERROR("Couldn't allocate DC DMUB server!\n");
		वापस -ENOMEM;
	पूर्ण

	DRM_INFO("DMUB hardware initialized: version=0x%08X\n",
		 adev->dm.dmcub_fw_version);

	वापस 0;
पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
#घोषणा DMUB_TRACE_MAX_READ 64
अटल व्योम dm_dmub_trace_high_irq(व्योम *पूर्णांकerrupt_params)
अणु
	काष्ठा common_irq_params *irq_params = पूर्णांकerrupt_params;
	काष्ठा amdgpu_device *adev = irq_params->adev;
	काष्ठा amdgpu_display_manager *dm = &adev->dm;
	काष्ठा dmcub_trace_buf_entry entry = अणु 0 पूर्ण;
	uपूर्णांक32_t count = 0;

	करो अणु
		अगर (dc_dmub_srv_get_dmub_outbox0_msg(dm->dc, &entry)) अणु
			trace_amdgpu_dmub_trace_high_irq(entry.trace_code, entry.tick_count,
							entry.param0, entry.param1);

			DRM_DEBUG_DRIVER("trace_code:%u, tick_count:%u, param0:%u, param1:%u\n",
				 entry.trace_code, entry.tick_count, entry.param0, entry.param1);
		पूर्ण अन्यथा
			अवरोध;

		count++;

	पूर्ण जबतक (count <= DMUB_TRACE_MAX_READ);

	ASSERT(count <= DMUB_TRACE_MAX_READ);
पूर्ण

अटल व्योम mmhub_पढ़ो_प्रणाली_context(काष्ठा amdgpu_device *adev, काष्ठा dc_phy_addr_space_config *pa_config)
अणु
	uपूर्णांक64_t pt_base;
	uपूर्णांक32_t logical_addr_low;
	uपूर्णांक32_t logical_addr_high;
	uपूर्णांक32_t agp_base, agp_bot, agp_top;
	PHYSICAL_ADDRESS_LOC page_table_start, page_table_end, page_table_base;

	logical_addr_low  = min(adev->gmc.fb_start, adev->gmc.agp_start) >> 18;
	pt_base = amdgpu_gmc_pd_addr(adev->gart.bo);

	अगर (adev->apu_flags & AMD_APU_IS_RAVEN2)
		/*
		 * Raven2 has a HW issue that it is unable to use the vram which
		 * is out of MC_VM_SYSTEM_APERTURE_HIGH_ADDR. So here is the
		 * workaround that increase प्रणाली aperture high address (add 1)
		 * to get rid of the VM fault and hardware hang.
		 */
		logical_addr_high = max((adev->gmc.fb_end >> 18) + 0x1, adev->gmc.agp_end >> 18);
	अन्यथा
		logical_addr_high = max(adev->gmc.fb_end, adev->gmc.agp_end) >> 18;

	agp_base = 0;
	agp_bot = adev->gmc.agp_start >> 24;
	agp_top = adev->gmc.agp_end >> 24;


	page_table_start.high_part = (u32)(adev->gmc.gart_start >> 44) & 0xF;
	page_table_start.low_part = (u32)(adev->gmc.gart_start >> 12);
	page_table_end.high_part = (u32)(adev->gmc.gart_end >> 44) & 0xF;
	page_table_end.low_part = (u32)(adev->gmc.gart_end >> 12);
	page_table_base.high_part = upper_32_bits(pt_base) & 0xF;
	page_table_base.low_part = lower_32_bits(pt_base);

	pa_config->प्रणाली_aperture.start_addr = (uपूर्णांक64_t)logical_addr_low << 18;
	pa_config->प्रणाली_aperture.end_addr = (uपूर्णांक64_t)logical_addr_high << 18;

	pa_config->प्रणाली_aperture.agp_base = (uपूर्णांक64_t)agp_base << 24 ;
	pa_config->प्रणाली_aperture.agp_bot = (uपूर्णांक64_t)agp_bot << 24;
	pa_config->प्रणाली_aperture.agp_top = (uपूर्णांक64_t)agp_top << 24;

	pa_config->प्रणाली_aperture.fb_base = adev->gmc.fb_start;
	pa_config->प्रणाली_aperture.fb_offset = adev->gmc.aper_base;
	pa_config->प्रणाली_aperture.fb_top = adev->gmc.fb_end;

	pa_config->gart_config.page_table_start_addr = page_table_start.quad_part << 12;
	pa_config->gart_config.page_table_end_addr = page_table_end.quad_part << 12;
	pa_config->gart_config.page_table_base_addr = page_table_base.quad_part;

	pa_config->is_hvm_enabled = 0;

पूर्ण
#पूर्ण_अगर
#अगर defined(CONFIG_DRM_AMD_DC_DCN)
अटल व्योम event_mall_stutter(काष्ठा work_काष्ठा *work)
अणु

	काष्ठा vblank_workqueue *vblank_work = container_of(work, काष्ठा vblank_workqueue, mall_work);
	काष्ठा amdgpu_display_manager *dm = vblank_work->dm;

	mutex_lock(&dm->dc_lock);

	अगर (vblank_work->enable)
		dm->active_vblank_irq_count++;
	अन्यथा अगर(dm->active_vblank_irq_count)
		dm->active_vblank_irq_count--;

	dc_allow_idle_optimizations(dm->dc, dm->active_vblank_irq_count == 0);

	DRM_DEBUG_KMS("Allow idle optimizations (MALL): %d\n", dm->active_vblank_irq_count == 0);

	mutex_unlock(&dm->dc_lock);
पूर्ण

अटल काष्ठा vblank_workqueue *vblank_create_workqueue(काष्ठा amdgpu_device *adev, काष्ठा dc *dc)
अणु

	पूर्णांक max_caps = dc->caps.max_links;
	काष्ठा vblank_workqueue *vblank_work;
	पूर्णांक i = 0;

	vblank_work = kसुस्मृति(max_caps, माप(*vblank_work), GFP_KERNEL);
	अगर (ZERO_OR_शून्य_PTR(vblank_work)) अणु
		kमुक्त(vblank_work);
		वापस शून्य;
	पूर्ण

	क्रम (i = 0; i < max_caps; i++)
		INIT_WORK(&vblank_work[i].mall_work, event_mall_stutter);

	वापस vblank_work;
पूर्ण
#पूर्ण_अगर
अटल पूर्णांक amdgpu_dm_init(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा dc_init_data init_data;
#अगर_घोषित CONFIG_DRM_AMD_DC_HDCP
	काष्ठा dc_callback_init init_params;
#पूर्ण_अगर
	पूर्णांक r;

	adev->dm.ddev = adev_to_drm(adev);
	adev->dm.adev = adev;

	/* Zero all the fields */
	स_रखो(&init_data, 0, माप(init_data));
#अगर_घोषित CONFIG_DRM_AMD_DC_HDCP
	स_रखो(&init_params, 0, माप(init_params));
#पूर्ण_अगर

	mutex_init(&adev->dm.dc_lock);
	mutex_init(&adev->dm.audio_lock);
#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	spin_lock_init(&adev->dm.vblank_lock);
#पूर्ण_अगर

	अगर(amdgpu_dm_irq_init(adev)) अणु
		DRM_ERROR("amdgpu: failed to initialize DM IRQ support.\n");
		जाओ error;
	पूर्ण

	init_data.asic_id.chip_family = adev->family;

	init_data.asic_id.pci_revision_id = adev->pdev->revision;
	init_data.asic_id.hw_पूर्णांकernal_rev = adev->बाह्यal_rev_id;

	init_data.asic_id.vram_width = adev->gmc.vram_width;
	/* TODO: initialize init_data.asic_id.vram_type here!!!! */
	init_data.asic_id.atombios_base_address =
		adev->mode_info.atom_context->bios;

	init_data.driver = adev;

	adev->dm.cgs_device = amdgpu_cgs_create_device(adev);

	अगर (!adev->dm.cgs_device) अणु
		DRM_ERROR("amdgpu: failed to create cgs device.\n");
		जाओ error;
	पूर्ण

	init_data.cgs_device = adev->dm.cgs_device;

	init_data.dce_environment = DCE_ENV_PRODUCTION_DRV;

	चयन (adev->asic_type) अणु
	हाल CHIP_CARRIZO:
	हाल CHIP_STONEY:
	हाल CHIP_RAVEN:
	हाल CHIP_RENOIR:
		init_data.flags.gpu_vm_support = true;
		अगर (ASICREV_IS_GREEN_SARDINE(adev->बाह्यal_rev_id))
			init_data.flags.disable_dmcu = true;
		अवरोध;
#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	हाल CHIP_VANGOGH:
		init_data.flags.gpu_vm_support = true;
		अवरोध;
#पूर्ण_अगर
	शेष:
		अवरोध;
	पूर्ण

	अगर (amdgpu_dc_feature_mask & DC_FBC_MASK)
		init_data.flags.fbc_support = true;

	अगर (amdgpu_dc_feature_mask & DC_MULTI_MON_PP_MCLK_SWITCH_MASK)
		init_data.flags.multi_mon_pp_mclk_चयन = true;

	अगर (amdgpu_dc_feature_mask & DC_DISABLE_FRACTIONAL_PWM_MASK)
		init_data.flags.disable_fractional_pwm = true;

	init_data.flags.घातer_करोwn_display_on_boot = true;

	INIT_LIST_HEAD(&adev->dm.da_list);
	/* Display Core create. */
	adev->dm.dc = dc_create(&init_data);

	अगर (adev->dm.dc) अणु
		DRM_INFO("Display Core initialized with v%s!\n", DC_VER);
	पूर्ण अन्यथा अणु
		DRM_INFO("Display Core failed to initialize with v%s!\n", DC_VER);
		जाओ error;
	पूर्ण

	अगर (amdgpu_dc_debug_mask & DC_DISABLE_PIPE_SPLIT) अणु
		adev->dm.dc->debug.क्रमce_single_disp_pipe_split = false;
		adev->dm.dc->debug.pipe_split_policy = MPC_SPLIT_AVOID;
	पूर्ण

	अगर (adev->asic_type != CHIP_CARRIZO && adev->asic_type != CHIP_STONEY)
		adev->dm.dc->debug.disable_stutter = amdgpu_pp_feature_mask & PP_STUTTER_MODE ? false : true;

	अगर (amdgpu_dc_debug_mask & DC_DISABLE_STUTTER)
		adev->dm.dc->debug.disable_stutter = true;

	अगर (amdgpu_dc_debug_mask & DC_DISABLE_DSC)
		adev->dm.dc->debug.disable_dsc = true;

	अगर (amdgpu_dc_debug_mask & DC_DISABLE_CLOCK_GATING)
		adev->dm.dc->debug.disable_घड़ी_gate = true;

	r = dm_dmub_hw_init(adev);
	अगर (r) अणु
		DRM_ERROR("DMUB interface failed to initialize: status=%d\n", r);
		जाओ error;
	पूर्ण

	dc_hardware_init(adev->dm.dc);

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	अगर (adev->apu_flags) अणु
		काष्ठा dc_phy_addr_space_config pa_config;

		mmhub_पढ़ो_प्रणाली_context(adev, &pa_config);

		// Call the DC init_memory func
		dc_setup_प्रणाली_context(adev->dm.dc, &pa_config);
	पूर्ण
#पूर्ण_अगर

	adev->dm.मुक्तsync_module = mod_मुक्तsync_create(adev->dm.dc);
	अगर (!adev->dm.मुक्तsync_module) अणु
		DRM_ERROR(
		"amdgpu: failed to initialize freesync_module.\n");
	पूर्ण अन्यथा
		DRM_DEBUG_DRIVER("amdgpu: freesync_module init done %p.\n",
				adev->dm.मुक्तsync_module);

	amdgpu_dm_init_color_mod();

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	अगर (adev->dm.dc->caps.max_links > 0) अणु
		adev->dm.vblank_workqueue = vblank_create_workqueue(adev, adev->dm.dc);

		अगर (!adev->dm.vblank_workqueue)
			DRM_ERROR("amdgpu: failed to initialize vblank_workqueue.\n");
		अन्यथा
			DRM_DEBUG_DRIVER("amdgpu: vblank_workqueue init done %p.\n", adev->dm.vblank_workqueue);
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_DRM_AMD_DC_HDCP
	अगर (adev->dm.dc->caps.max_links > 0 && adev->asic_type >= CHIP_RAVEN) अणु
		adev->dm.hdcp_workqueue = hdcp_create_workqueue(adev, &init_params.cp_psp, adev->dm.dc);

		अगर (!adev->dm.hdcp_workqueue)
			DRM_ERROR("amdgpu: failed to initialize hdcp_workqueue.\n");
		अन्यथा
			DRM_DEBUG_DRIVER("amdgpu: hdcp_workqueue init done %p.\n", adev->dm.hdcp_workqueue);

		dc_init_callbacks(adev->dm.dc, &init_params);
	पूर्ण
#पूर्ण_अगर
#अगर defined(CONFIG_DRM_AMD_SECURE_DISPLAY)
	adev->dm.crc_rd_wrk = amdgpu_dm_crtc_secure_display_create_work();
#पूर्ण_अगर
	अगर (amdgpu_dm_initialize_drm_device(adev)) अणु
		DRM_ERROR(
		"amdgpu: failed to initialize sw for display support.\n");
		जाओ error;
	पूर्ण

	/* create fake encoders क्रम MST */
	dm_dp_create_fake_mst_encoders(adev);

	/* TODO: Add_display_info? */

	/* TODO use dynamic cursor width */
	adev_to_drm(adev)->mode_config.cursor_width = adev->dm.dc->caps.max_cursor_size;
	adev_to_drm(adev)->mode_config.cursor_height = adev->dm.dc->caps.max_cursor_size;

	अगर (drm_vblank_init(adev_to_drm(adev), adev->dm.display_indexes_num)) अणु
		DRM_ERROR(
		"amdgpu: failed to initialize sw for display support.\n");
		जाओ error;
	पूर्ण


	DRM_DEBUG_DRIVER("KMS initialized.\n");

	वापस 0;
error:
	amdgpu_dm_fini(adev);

	वापस -EINVAL;
पूर्ण

अटल व्योम amdgpu_dm_fini(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adev->dm.display_indexes_num; i++) अणु
		drm_encoder_cleanup(&adev->dm.mst_encoders[i].base);
	पूर्ण

	amdgpu_dm_audio_fini(adev);

	amdgpu_dm_destroy_drm_device(&adev->dm);

#अगर defined(CONFIG_DRM_AMD_SECURE_DISPLAY)
	अगर (adev->dm.crc_rd_wrk) अणु
		flush_work(&adev->dm.crc_rd_wrk->notअगरy_ta_work);
		kमुक्त(adev->dm.crc_rd_wrk);
		adev->dm.crc_rd_wrk = शून्य;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_DRM_AMD_DC_HDCP
	अगर (adev->dm.hdcp_workqueue) अणु
		hdcp_destroy(&adev->dev->kobj, adev->dm.hdcp_workqueue);
		adev->dm.hdcp_workqueue = शून्य;
	पूर्ण

	अगर (adev->dm.dc)
		dc_deinit_callbacks(adev->dm.dc);
#पूर्ण_अगर

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	अगर (adev->dm.vblank_workqueue) अणु
		adev->dm.vblank_workqueue->dm = शून्य;
		kमुक्त(adev->dm.vblank_workqueue);
		adev->dm.vblank_workqueue = शून्य;
	पूर्ण
#पूर्ण_अगर

	अगर (adev->dm.dc->ctx->dmub_srv) अणु
		dc_dmub_srv_destroy(&adev->dm.dc->ctx->dmub_srv);
		adev->dm.dc->ctx->dmub_srv = शून्य;
	पूर्ण

	अगर (adev->dm.dmub_bo)
		amdgpu_bo_मुक्त_kernel(&adev->dm.dmub_bo,
				      &adev->dm.dmub_bo_gpu_addr,
				      &adev->dm.dmub_bo_cpu_addr);

	/* DC Destroy TODO: Replace destroy DAL */
	अगर (adev->dm.dc)
		dc_destroy(&adev->dm.dc);
	/*
	 * TODO: pageflip, vlank पूर्णांकerrupt
	 *
	 * amdgpu_dm_irq_fini(adev);
	 */

	अगर (adev->dm.cgs_device) अणु
		amdgpu_cgs_destroy_device(adev->dm.cgs_device);
		adev->dm.cgs_device = शून्य;
	पूर्ण
	अगर (adev->dm.मुक्तsync_module) अणु
		mod_मुक्तsync_destroy(adev->dm.मुक्तsync_module);
		adev->dm.मुक्तsync_module = शून्य;
	पूर्ण

	mutex_destroy(&adev->dm.audio_lock);
	mutex_destroy(&adev->dm.dc_lock);

	वापस;
पूर्ण

अटल पूर्णांक load_dmcu_fw(काष्ठा amdgpu_device *adev)
अणु
	स्थिर अक्षर *fw_name_dmcu = शून्य;
	पूर्णांक r;
	स्थिर काष्ठा dmcu_firmware_header_v1_0 *hdr;

	चयन(adev->asic_type) अणु
#अगर defined(CONFIG_DRM_AMD_DC_SI)
	हाल CHIP_TAHITI:
	हाल CHIP_PITCAIRN:
	हाल CHIP_VERDE:
	हाल CHIP_OLAND:
#पूर्ण_अगर
	हाल CHIP_BONAIRE:
	हाल CHIP_HAWAII:
	हाल CHIP_KAVERI:
	हाल CHIP_KABINI:
	हाल CHIP_MULLINS:
	हाल CHIP_TONGA:
	हाल CHIP_FIJI:
	हाल CHIP_CARRIZO:
	हाल CHIP_STONEY:
	हाल CHIP_POLARIS11:
	हाल CHIP_POLARIS10:
	हाल CHIP_POLARIS12:
	हाल CHIP_VEGAM:
	हाल CHIP_VEGA10:
	हाल CHIP_VEGA12:
	हाल CHIP_VEGA20:
	हाल CHIP_NAVI10:
	हाल CHIP_NAVI14:
	हाल CHIP_RENOIR:
	हाल CHIP_SIENNA_CICHLID:
	हाल CHIP_NAVY_FLOUNDER:
	हाल CHIP_DIMGREY_CAVEFISH:
	हाल CHIP_VANGOGH:
		वापस 0;
	हाल CHIP_NAVI12:
		fw_name_dmcu = FIRMWARE_NAVI12_DMCU;
		अवरोध;
	हाल CHIP_RAVEN:
		अगर (ASICREV_IS_PICASSO(adev->बाह्यal_rev_id))
			fw_name_dmcu = FIRMWARE_RAVEN_DMCU;
		अन्यथा अगर (ASICREV_IS_RAVEN2(adev->बाह्यal_rev_id))
			fw_name_dmcu = FIRMWARE_RAVEN_DMCU;
		अन्यथा
			वापस 0;
		अवरोध;
	शेष:
		DRM_ERROR("Unsupported ASIC type: 0x%X\n", adev->asic_type);
		वापस -EINVAL;
	पूर्ण

	अगर (adev->firmware.load_type != AMDGPU_FW_LOAD_PSP) अणु
		DRM_DEBUG_KMS("dm: DMCU firmware not supported on direct or SMU loading\n");
		वापस 0;
	पूर्ण

	r = request_firmware_direct(&adev->dm.fw_dmcu, fw_name_dmcu, adev->dev);
	अगर (r == -ENOENT) अणु
		/* DMCU firmware is not necessary, so करोn't raise a fuss if it's missing */
		DRM_DEBUG_KMS("dm: DMCU firmware not found\n");
		adev->dm.fw_dmcu = शून्य;
		वापस 0;
	पूर्ण
	अगर (r) अणु
		dev_err(adev->dev, "amdgpu_dm: Can't load firmware \"%s\"\n",
			fw_name_dmcu);
		वापस r;
	पूर्ण

	r = amdgpu_ucode_validate(adev->dm.fw_dmcu);
	अगर (r) अणु
		dev_err(adev->dev, "amdgpu_dm: Can't validate firmware \"%s\"\n",
			fw_name_dmcu);
		release_firmware(adev->dm.fw_dmcu);
		adev->dm.fw_dmcu = शून्य;
		वापस r;
	पूर्ण

	hdr = (स्थिर काष्ठा dmcu_firmware_header_v1_0 *)adev->dm.fw_dmcu->data;
	adev->firmware.ucode[AMDGPU_UCODE_ID_DMCU_ERAM].ucode_id = AMDGPU_UCODE_ID_DMCU_ERAM;
	adev->firmware.ucode[AMDGPU_UCODE_ID_DMCU_ERAM].fw = adev->dm.fw_dmcu;
	adev->firmware.fw_size +=
		ALIGN(le32_to_cpu(hdr->header.ucode_size_bytes) - le32_to_cpu(hdr->पूर्णांकv_size_bytes), PAGE_SIZE);

	adev->firmware.ucode[AMDGPU_UCODE_ID_DMCU_INTV].ucode_id = AMDGPU_UCODE_ID_DMCU_INTV;
	adev->firmware.ucode[AMDGPU_UCODE_ID_DMCU_INTV].fw = adev->dm.fw_dmcu;
	adev->firmware.fw_size +=
		ALIGN(le32_to_cpu(hdr->पूर्णांकv_size_bytes), PAGE_SIZE);

	adev->dm.dmcu_fw_version = le32_to_cpu(hdr->header.ucode_version);

	DRM_DEBUG_KMS("PSP loading DMCU firmware\n");

	वापस 0;
पूर्ण

अटल uपूर्णांक32_t amdgpu_dm_dmub_reg_पढ़ो(व्योम *ctx, uपूर्णांक32_t address)
अणु
	काष्ठा amdgpu_device *adev = ctx;

	वापस dm_पढ़ो_reg(adev->dm.dc->ctx, address);
पूर्ण

अटल व्योम amdgpu_dm_dmub_reg_ग_लिखो(व्योम *ctx, uपूर्णांक32_t address,
				     uपूर्णांक32_t value)
अणु
	काष्ठा amdgpu_device *adev = ctx;

	वापस dm_ग_लिखो_reg(adev->dm.dc->ctx, address, value);
पूर्ण

अटल पूर्णांक dm_dmub_sw_init(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा dmub_srv_create_params create_params;
	काष्ठा dmub_srv_region_params region_params;
	काष्ठा dmub_srv_region_info region_info;
	काष्ठा dmub_srv_fb_params fb_params;
	काष्ठा dmub_srv_fb_info *fb_info;
	काष्ठा dmub_srv *dmub_srv;
	स्थिर काष्ठा dmcub_firmware_header_v1_0 *hdr;
	स्थिर अक्षर *fw_name_dmub;
	क्रमागत dmub_asic dmub_asic;
	क्रमागत dmub_status status;
	पूर्णांक r;

	चयन (adev->asic_type) अणु
	हाल CHIP_RENOIR:
		dmub_asic = DMUB_ASIC_DCN21;
		fw_name_dmub = FIRMWARE_RENOIR_DMUB;
		अगर (ASICREV_IS_GREEN_SARDINE(adev->बाह्यal_rev_id))
			fw_name_dmub = FIRMWARE_GREEN_SARDINE_DMUB;
		अवरोध;
	हाल CHIP_SIENNA_CICHLID:
		dmub_asic = DMUB_ASIC_DCN30;
		fw_name_dmub = FIRMWARE_SIENNA_CICHLID_DMUB;
		अवरोध;
	हाल CHIP_NAVY_FLOUNDER:
		dmub_asic = DMUB_ASIC_DCN30;
		fw_name_dmub = FIRMWARE_NAVY_FLOUNDER_DMUB;
		अवरोध;
	हाल CHIP_VANGOGH:
		dmub_asic = DMUB_ASIC_DCN301;
		fw_name_dmub = FIRMWARE_VANGOGH_DMUB;
		अवरोध;
	हाल CHIP_DIMGREY_CAVEFISH:
		dmub_asic = DMUB_ASIC_DCN302;
		fw_name_dmub = FIRMWARE_DIMGREY_CAVEFISH_DMUB;
		अवरोध;

	शेष:
		/* ASIC करोesn't support DMUB. */
		वापस 0;
	पूर्ण

	r = request_firmware_direct(&adev->dm.dmub_fw, fw_name_dmub, adev->dev);
	अगर (r) अणु
		DRM_ERROR("DMUB firmware loading failed: %d\n", r);
		वापस 0;
	पूर्ण

	r = amdgpu_ucode_validate(adev->dm.dmub_fw);
	अगर (r) अणु
		DRM_ERROR("Couldn't validate DMUB firmware: %d\n", r);
		वापस 0;
	पूर्ण

	hdr = (स्थिर काष्ठा dmcub_firmware_header_v1_0 *)adev->dm.dmub_fw->data;

	अगर (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) अणु
		adev->firmware.ucode[AMDGPU_UCODE_ID_DMCUB].ucode_id =
			AMDGPU_UCODE_ID_DMCUB;
		adev->firmware.ucode[AMDGPU_UCODE_ID_DMCUB].fw =
			adev->dm.dmub_fw;
		adev->firmware.fw_size +=
			ALIGN(le32_to_cpu(hdr->inst_स्थिर_bytes), PAGE_SIZE);

		DRM_INFO("Loading DMUB firmware via PSP: version=0x%08X\n",
			 adev->dm.dmcub_fw_version);
	पूर्ण

	adev->dm.dmcub_fw_version = le32_to_cpu(hdr->header.ucode_version);

	adev->dm.dmub_srv = kzalloc(माप(*adev->dm.dmub_srv), GFP_KERNEL);
	dmub_srv = adev->dm.dmub_srv;

	अगर (!dmub_srv) अणु
		DRM_ERROR("Failed to allocate DMUB service!\n");
		वापस -ENOMEM;
	पूर्ण

	स_रखो(&create_params, 0, माप(create_params));
	create_params.user_ctx = adev;
	create_params.funcs.reg_पढ़ो = amdgpu_dm_dmub_reg_पढ़ो;
	create_params.funcs.reg_ग_लिखो = amdgpu_dm_dmub_reg_ग_लिखो;
	create_params.asic = dmub_asic;

	/* Create the DMUB service. */
	status = dmub_srv_create(dmub_srv, &create_params);
	अगर (status != DMUB_STATUS_OK) अणु
		DRM_ERROR("Error creating DMUB service: %d\n", status);
		वापस -EINVAL;
	पूर्ण

	/* Calculate the size of all the regions क्रम the DMUB service. */
	स_रखो(&region_params, 0, माप(region_params));

	region_params.inst_स्थिर_size = le32_to_cpu(hdr->inst_स्थिर_bytes) -
					PSP_HEADER_BYTES - PSP_FOOTER_BYTES;
	region_params.bss_data_size = le32_to_cpu(hdr->bss_data_bytes);
	region_params.vbios_size = adev->bios_size;
	region_params.fw_bss_data = region_params.bss_data_size ?
		adev->dm.dmub_fw->data +
		le32_to_cpu(hdr->header.ucode_array_offset_bytes) +
		le32_to_cpu(hdr->inst_स्थिर_bytes) : शून्य;
	region_params.fw_inst_स्थिर =
		adev->dm.dmub_fw->data +
		le32_to_cpu(hdr->header.ucode_array_offset_bytes) +
		PSP_HEADER_BYTES;

	status = dmub_srv_calc_region_info(dmub_srv, &region_params,
					   &region_info);

	अगर (status != DMUB_STATUS_OK) अणु
		DRM_ERROR("Error calculating DMUB region info: %d\n", status);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Allocate a framebuffer based on the total size of all the regions.
	 * TODO: Move this पूर्णांकo GART.
	 */
	r = amdgpu_bo_create_kernel(adev, region_info.fb_size, PAGE_SIZE,
				    AMDGPU_GEM_DOMAIN_VRAM, &adev->dm.dmub_bo,
				    &adev->dm.dmub_bo_gpu_addr,
				    &adev->dm.dmub_bo_cpu_addr);
	अगर (r)
		वापस r;

	/* Rebase the regions on the framebuffer address. */
	स_रखो(&fb_params, 0, माप(fb_params));
	fb_params.cpu_addr = adev->dm.dmub_bo_cpu_addr;
	fb_params.gpu_addr = adev->dm.dmub_bo_gpu_addr;
	fb_params.region_info = &region_info;

	adev->dm.dmub_fb_info =
		kzalloc(माप(*adev->dm.dmub_fb_info), GFP_KERNEL);
	fb_info = adev->dm.dmub_fb_info;

	अगर (!fb_info) अणु
		DRM_ERROR(
			"Failed to allocate framebuffer info for DMUB service!\n");
		वापस -ENOMEM;
	पूर्ण

	status = dmub_srv_calc_fb_info(dmub_srv, &fb_params, fb_info);
	अगर (status != DMUB_STATUS_OK) अणु
		DRM_ERROR("Error calculating DMUB FB info: %d\n", status);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dm_sw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक r;

	r = dm_dmub_sw_init(adev);
	अगर (r)
		वापस r;

	वापस load_dmcu_fw(adev);
पूर्ण

अटल पूर्णांक dm_sw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	kमुक्त(adev->dm.dmub_fb_info);
	adev->dm.dmub_fb_info = शून्य;

	अगर (adev->dm.dmub_srv) अणु
		dmub_srv_destroy(adev->dm.dmub_srv);
		adev->dm.dmub_srv = शून्य;
	पूर्ण

	release_firmware(adev->dm.dmub_fw);
	adev->dm.dmub_fw = शून्य;

	release_firmware(adev->dm.fw_dmcu);
	adev->dm.fw_dmcu = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक detect_mst_link_क्रम_all_connectors(काष्ठा drm_device *dev)
अणु
	काष्ठा amdgpu_dm_connector *aconnector;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter iter;
	पूर्णांक ret = 0;

	drm_connector_list_iter_begin(dev, &iter);
	drm_क्रम_each_connector_iter(connector, &iter) अणु
		aconnector = to_amdgpu_dm_connector(connector);
		अगर (aconnector->dc_link->type == dc_connection_mst_branch &&
		    aconnector->mst_mgr.aux) अणु
			DRM_DEBUG_DRIVER("DM_MST: starting TM on aconnector: %p [id: %d]\n",
					 aconnector,
					 aconnector->base.base.id);

			ret = drm_dp_mst_topology_mgr_set_mst(&aconnector->mst_mgr, true);
			अगर (ret < 0) अणु
				DRM_ERROR("DM_MST: Failed to start MST\n");
				aconnector->dc_link->type =
					dc_connection_single;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	drm_connector_list_iter_end(&iter);

	वापस ret;
पूर्ण

अटल पूर्णांक dm_late_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	काष्ठा dmcu_iram_parameters params;
	अचिन्हित पूर्णांक linear_lut[16];
	पूर्णांक i;
	काष्ठा dmcu *dmcu = शून्य;
	bool ret = true;

	dmcu = adev->dm.dc->res_pool->dmcu;

	क्रम (i = 0; i < 16; i++)
		linear_lut[i] = 0xFFFF * i / 15;

	params.set = 0;
	params.backlight_ramping_start = 0xCCCC;
	params.backlight_ramping_reduction = 0xCCCCCCCC;
	params.backlight_lut_array_size = 16;
	params.backlight_lut_array = linear_lut;

	/* Min backlight level after ABM reduction,  Don't allow below 1%
	 * 0xFFFF x 0.01 = 0x28F
	 */
	params.min_abm_backlight = 0x28F;

	/* In the हाल where abm is implemented on dmcub,
	 * dmcu object will be null.
	 * ABM 2.4 and up are implemented on dmcub.
	 */
	अगर (dmcu)
		ret = dmcu_load_iram(dmcu, params);
	अन्यथा अगर (adev->dm.dc->ctx->dmub_srv)
		ret = dmub_init_abm_config(adev->dm.dc->res_pool, params);

	अगर (!ret)
		वापस -EINVAL;

	वापस detect_mst_link_क्रम_all_connectors(adev_to_drm(adev));
पूर्ण

अटल व्योम s3_handle_mst(काष्ठा drm_device *dev, bool suspend)
अणु
	काष्ठा amdgpu_dm_connector *aconnector;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter iter;
	काष्ठा drm_dp_mst_topology_mgr *mgr;
	पूर्णांक ret;
	bool need_hotplug = false;

	drm_connector_list_iter_begin(dev, &iter);
	drm_क्रम_each_connector_iter(connector, &iter) अणु
		aconnector = to_amdgpu_dm_connector(connector);
		अगर (aconnector->dc_link->type != dc_connection_mst_branch ||
		    aconnector->mst_port)
			जारी;

		mgr = &aconnector->mst_mgr;

		अगर (suspend) अणु
			drm_dp_mst_topology_mgr_suspend(mgr);
		पूर्ण अन्यथा अणु
			ret = drm_dp_mst_topology_mgr_resume(mgr, true);
			अगर (ret < 0) अणु
				drm_dp_mst_topology_mgr_set_mst(mgr, false);
				need_hotplug = true;
			पूर्ण
		पूर्ण
	पूर्ण
	drm_connector_list_iter_end(&iter);

	अगर (need_hotplug)
		drm_kms_helper_hotplug_event(dev);
पूर्ण

अटल पूर्णांक amdgpu_dm_smu_ग_लिखो_watermarks_table(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा smu_context *smu = &adev->smu;
	पूर्णांक ret = 0;

	अगर (!is_support_sw_smu(adev))
		वापस 0;

	/* This पूर्णांकerface is क्रम dGPU Navi1x.Linux dc-pplib पूर्णांकerface depends
	 * on winकरोw driver dc implementation.
	 * For Navi1x, घड़ी settings of dcn watermarks are fixed. the settings
	 * should be passed to smu during boot up and resume from s3.
	 * boot up: dc calculate dcn watermark घड़ी settings within dc_create,
	 * dcn20_resource_स्थिरruct
	 * then call pplib functions below to pass the settings to smu:
	 * smu_set_watermarks_क्रम_घड़ी_ranges
	 * smu_set_watermarks_table
	 * navi10_set_watermarks_table
	 * smu_ग_लिखो_watermarks_table
	 *
	 * For Renoir, घड़ी settings of dcn watermark are also fixed values.
	 * dc has implemented dअगरferent flow क्रम winकरोw driver:
	 * dc_hardware_init / dc_set_घातer_state
	 * dcn10_init_hw
	 * notअगरy_wm_ranges
	 * set_wm_ranges
	 * -- Linux
	 * smu_set_watermarks_क्रम_घड़ी_ranges
	 * renoir_set_watermarks_table
	 * smu_ग_लिखो_watermarks_table
	 *
	 * For Linux,
	 * dc_hardware_init -> amdgpu_dm_init
	 * dc_set_घातer_state --> dm_resume
	 *
	 * thereक्रमe, this function apply to navi10/12/14 but not Renoir
	 * *
	 */
	चयन(adev->asic_type) अणु
	हाल CHIP_NAVI10:
	हाल CHIP_NAVI14:
	हाल CHIP_NAVI12:
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	ret = smu_ग_लिखो_watermarks_table(smu);
	अगर (ret) अणु
		DRM_ERROR("Failed to update WMTABLE!\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * dm_hw_init() - Initialize DC device
 * @handle: The base driver device containing the amdgpu_dm device.
 *
 * Initialize the &काष्ठा amdgpu_display_manager device. This involves calling
 * the initializers of each DM component, then populating the काष्ठा with them.
 *
 * Although the function implies hardware initialization, both hardware and
 * software are initialized here. Splitting them out to their relevant init
 * hooks is a future TODO item.
 *
 * Some notable things that are initialized here:
 *
 * - Display Core, both software and hardware
 * - DC modules that we need (मुक्तsync and color management)
 * - DRM software states
 * - Interrupt sources and handlers
 * - Vblank support
 * - Debug FS entries, अगर enabled
 */
अटल पूर्णांक dm_hw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	/* Create DAL display manager */
	amdgpu_dm_init(adev);
	amdgpu_dm_hpd_init(adev);

	वापस 0;
पूर्ण

/**
 * dm_hw_fini() - Tearकरोwn DC device
 * @handle: The base driver device containing the amdgpu_dm device.
 *
 * Tearकरोwn components within &काष्ठा amdgpu_display_manager that require
 * cleanup. This involves cleaning up the DRM device, DC, and any modules that
 * were loaded. Also flush IRQ workqueues and disable them.
 */
अटल पूर्णांक dm_hw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	amdgpu_dm_hpd_fini(adev);

	amdgpu_dm_irq_fini(adev);
	amdgpu_dm_fini(adev);
	वापस 0;
पूर्ण


अटल पूर्णांक dm_enable_vblank(काष्ठा drm_crtc *crtc);
अटल व्योम dm_disable_vblank(काष्ठा drm_crtc *crtc);

अटल व्योम dm_gpureset_toggle_पूर्णांकerrupts(काष्ठा amdgpu_device *adev,
				 काष्ठा dc_state *state, bool enable)
अणु
	क्रमागत dc_irq_source irq_source;
	काष्ठा amdgpu_crtc *acrtc;
	पूर्णांक rc = -EBUSY;
	पूर्णांक i = 0;

	क्रम (i = 0; i < state->stream_count; i++) अणु
		acrtc = get_crtc_by_otg_inst(
				adev, state->stream_status[i].primary_otg_inst);

		अगर (acrtc && state->stream_status[i].plane_count != 0) अणु
			irq_source = IRQ_TYPE_PFLIP + acrtc->otg_inst;
			rc = dc_पूर्णांकerrupt_set(adev->dm.dc, irq_source, enable) ? 0 : -EBUSY;
			DRM_DEBUG_VBL("crtc %d - vupdate irq %sabling: r=%d\n",
				      acrtc->crtc_id, enable ? "en" : "dis", rc);
			अगर (rc)
				DRM_WARN("Failed to %s pflip interrupts\n",
					 enable ? "enable" : "disable");

			अगर (enable) अणु
				rc = dm_enable_vblank(&acrtc->base);
				अगर (rc)
					DRM_WARN("Failed to enable vblank interrupts\n");
			पूर्ण अन्यथा अणु
				dm_disable_vblank(&acrtc->base);
			पूर्ण

		पूर्ण
	पूर्ण

पूर्ण

अटल क्रमागत dc_status amdgpu_dm_commit_zero_streams(काष्ठा dc *dc)
अणु
	काष्ठा dc_state *context = शून्य;
	क्रमागत dc_status res = DC_ERROR_UNEXPECTED;
	पूर्णांक i;
	काष्ठा dc_stream_state *del_streams[MAX_PIPES];
	पूर्णांक del_streams_count = 0;

	स_रखो(del_streams, 0, माप(del_streams));

	context = dc_create_state(dc);
	अगर (context == शून्य)
		जाओ context_alloc_fail;

	dc_resource_state_copy_स्थिरruct_current(dc, context);

	/* First हटाओ from context all streams */
	क्रम (i = 0; i < context->stream_count; i++) अणु
		काष्ठा dc_stream_state *stream = context->streams[i];

		del_streams[del_streams_count++] = stream;
	पूर्ण

	/* Remove all planes क्रम हटाओd streams and then हटाओ the streams */
	क्रम (i = 0; i < del_streams_count; i++) अणु
		अगर (!dc_rem_all_planes_क्रम_stream(dc, del_streams[i], context)) अणु
			res = DC_FAIL_DETACH_SURFACES;
			जाओ fail;
		पूर्ण

		res = dc_हटाओ_stream_from_ctx(dc, context, del_streams[i]);
		अगर (res != DC_OK)
			जाओ fail;
	पूर्ण


	res = dc_validate_global_state(dc, context, false);

	अगर (res != DC_OK) अणु
		DRM_ERROR("%s:resource validation failed, dc_status:%d\n", __func__, res);
		जाओ fail;
	पूर्ण

	res = dc_commit_state(dc, context);

fail:
	dc_release_state(context);

context_alloc_fail:
	वापस res;
पूर्ण

अटल पूर्णांक dm_suspend(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = handle;
	काष्ठा amdgpu_display_manager *dm = &adev->dm;
	पूर्णांक ret = 0;

	अगर (amdgpu_in_reset(adev)) अणु
		mutex_lock(&dm->dc_lock);

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
		dc_allow_idle_optimizations(adev->dm.dc, false);
#पूर्ण_अगर

		dm->cached_dc_state = dc_copy_state(dm->dc->current_state);

		dm_gpureset_toggle_पूर्णांकerrupts(adev, dm->cached_dc_state, false);

		amdgpu_dm_commit_zero_streams(dm->dc);

		amdgpu_dm_irq_suspend(adev);

		वापस ret;
	पूर्ण

#अगर_घोषित CONFIG_DRM_AMD_SECURE_DISPLAY
	amdgpu_dm_crtc_secure_display_suspend(adev);
#पूर्ण_अगर
	WARN_ON(adev->dm.cached_state);
	adev->dm.cached_state = drm_atomic_helper_suspend(adev_to_drm(adev));

	s3_handle_mst(adev_to_drm(adev), true);

	amdgpu_dm_irq_suspend(adev);

	dc_set_घातer_state(dm->dc, DC_ACPI_CM_POWER_STATE_D3);

	वापस 0;
पूर्ण

अटल काष्ठा amdgpu_dm_connector *
amdgpu_dm_find_first_crtc_matching_connector(काष्ठा drm_atomic_state *state,
					     काष्ठा drm_crtc *crtc)
अणु
	uपूर्णांक32_t i;
	काष्ठा drm_connector_state *new_con_state;
	काष्ठा drm_connector *connector;
	काष्ठा drm_crtc *crtc_from_state;

	क्रम_each_new_connector_in_state(state, connector, new_con_state, i) अणु
		crtc_from_state = new_con_state->crtc;

		अगर (crtc_from_state == crtc)
			वापस to_amdgpu_dm_connector(connector);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम emulated_link_detect(काष्ठा dc_link *link)
अणु
	काष्ठा dc_sink_init_data sink_init_data = अणु 0 पूर्ण;
	काष्ठा display_sink_capability sink_caps = अणु 0 पूर्ण;
	क्रमागत dc_edid_status edid_status;
	काष्ठा dc_context *dc_ctx = link->ctx;
	काष्ठा dc_sink *sink = शून्य;
	काष्ठा dc_sink *prev_sink = शून्य;

	link->type = dc_connection_none;
	prev_sink = link->local_sink;

	अगर (prev_sink)
		dc_sink_release(prev_sink);

	चयन (link->connector_संकेत) अणु
	हाल SIGNAL_TYPE_HDMI_TYPE_A: अणु
		sink_caps.transaction_type = DDC_TRANSACTION_TYPE_I2C;
		sink_caps.संकेत = SIGNAL_TYPE_HDMI_TYPE_A;
		अवरोध;
	पूर्ण

	हाल SIGNAL_TYPE_DVI_SINGLE_LINK: अणु
		sink_caps.transaction_type = DDC_TRANSACTION_TYPE_I2C;
		sink_caps.संकेत = SIGNAL_TYPE_DVI_SINGLE_LINK;
		अवरोध;
	पूर्ण

	हाल SIGNAL_TYPE_DVI_DUAL_LINK: अणु
		sink_caps.transaction_type = DDC_TRANSACTION_TYPE_I2C;
		sink_caps.संकेत = SIGNAL_TYPE_DVI_DUAL_LINK;
		अवरोध;
	पूर्ण

	हाल SIGNAL_TYPE_LVDS: अणु
		sink_caps.transaction_type = DDC_TRANSACTION_TYPE_I2C;
		sink_caps.संकेत = SIGNAL_TYPE_LVDS;
		अवरोध;
	पूर्ण

	हाल SIGNAL_TYPE_EDP: अणु
		sink_caps.transaction_type =
			DDC_TRANSACTION_TYPE_I2C_OVER_AUX;
		sink_caps.संकेत = SIGNAL_TYPE_EDP;
		अवरोध;
	पूर्ण

	हाल SIGNAL_TYPE_DISPLAY_PORT: अणु
		sink_caps.transaction_type =
			DDC_TRANSACTION_TYPE_I2C_OVER_AUX;
		sink_caps.संकेत = SIGNAL_TYPE_VIRTUAL;
		अवरोध;
	पूर्ण

	शेष:
		DC_ERROR("Invalid connector type! signal:%d\n",
			link->connector_संकेत);
		वापस;
	पूर्ण

	sink_init_data.link = link;
	sink_init_data.sink_संकेत = sink_caps.संकेत;

	sink = dc_sink_create(&sink_init_data);
	अगर (!sink) अणु
		DC_ERROR("Failed to create sink!\n");
		वापस;
	पूर्ण

	/* dc_sink_create वापसs a new reference */
	link->local_sink = sink;

	edid_status = dm_helpers_पढ़ो_local_edid(
			link->ctx,
			link,
			sink);

	अगर (edid_status != EDID_OK)
		DC_ERROR("Failed to read EDID");

पूर्ण

अटल व्योम dm_gpureset_commit_state(काष्ठा dc_state *dc_state,
				     काष्ठा amdgpu_display_manager *dm)
अणु
	काष्ठा अणु
		काष्ठा dc_surface_update surface_updates[MAX_SURFACES];
		काष्ठा dc_plane_info plane_infos[MAX_SURFACES];
		काष्ठा dc_scaling_info scaling_infos[MAX_SURFACES];
		काष्ठा dc_flip_addrs flip_addrs[MAX_SURFACES];
		काष्ठा dc_stream_update stream_update;
	पूर्ण * bundle;
	पूर्णांक k, m;

	bundle = kzalloc(माप(*bundle), GFP_KERNEL);

	अगर (!bundle) अणु
		dm_error("Failed to allocate update bundle\n");
		जाओ cleanup;
	पूर्ण

	क्रम (k = 0; k < dc_state->stream_count; k++) अणु
		bundle->stream_update.stream = dc_state->streams[k];

		क्रम (m = 0; m < dc_state->stream_status->plane_count; m++) अणु
			bundle->surface_updates[m].surface =
				dc_state->stream_status->plane_states[m];
			bundle->surface_updates[m].surface->क्रमce_full_update =
				true;
		पूर्ण
		dc_commit_updates_क्रम_stream(
			dm->dc, bundle->surface_updates,
			dc_state->stream_status->plane_count,
			dc_state->streams[k], &bundle->stream_update, dc_state);
	पूर्ण

cleanup:
	kमुक्त(bundle);

	वापस;
पूर्ण

अटल व्योम dm_set_dpms_off(काष्ठा dc_link *link)
अणु
	काष्ठा dc_stream_state *stream_state;
	काष्ठा amdgpu_dm_connector *aconnector = link->priv;
	काष्ठा amdgpu_device *adev = drm_to_adev(aconnector->base.dev);
	काष्ठा dc_stream_update stream_update;
	bool dpms_off = true;

	स_रखो(&stream_update, 0, माप(stream_update));
	stream_update.dpms_off = &dpms_off;

	mutex_lock(&adev->dm.dc_lock);
	stream_state = dc_stream_find_from_link(link);

	अगर (stream_state == शून्य) अणु
		DRM_DEBUG_DRIVER("Error finding stream state associated with link!\n");
		mutex_unlock(&adev->dm.dc_lock);
		वापस;
	पूर्ण

	stream_update.stream = stream_state;
	dc_commit_updates_क्रम_stream(stream_state->ctx->dc, शून्य, 0,
				     stream_state, &stream_update,
				     stream_state->ctx->dc->current_state);
	mutex_unlock(&adev->dm.dc_lock);
पूर्ण

अटल पूर्णांक dm_resume(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = handle;
	काष्ठा drm_device *ddev = adev_to_drm(adev);
	काष्ठा amdgpu_display_manager *dm = &adev->dm;
	काष्ठा amdgpu_dm_connector *aconnector;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter iter;
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *new_crtc_state;
	काष्ठा dm_crtc_state *dm_new_crtc_state;
	काष्ठा drm_plane *plane;
	काष्ठा drm_plane_state *new_plane_state;
	काष्ठा dm_plane_state *dm_new_plane_state;
	काष्ठा dm_atomic_state *dm_state = to_dm_atomic_state(dm->atomic_obj.state);
	क्रमागत dc_connection_type new_connection_type = dc_connection_none;
	काष्ठा dc_state *dc_state;
	पूर्णांक i, r, j;

	अगर (amdgpu_in_reset(adev)) अणु
		dc_state = dm->cached_dc_state;

		r = dm_dmub_hw_init(adev);
		अगर (r)
			DRM_ERROR("DMUB interface failed to initialize: status=%d\n", r);

		dc_set_घातer_state(dm->dc, DC_ACPI_CM_POWER_STATE_D0);
		dc_resume(dm->dc);

		amdgpu_dm_irq_resume_early(adev);

		क्रम (i = 0; i < dc_state->stream_count; i++) अणु
			dc_state->streams[i]->mode_changed = true;
			क्रम (j = 0; j < dc_state->stream_status->plane_count; j++) अणु
				dc_state->stream_status->plane_states[j]->update_flags.raw
					= 0xffffffff;
			पूर्ण
		पूर्ण

		WARN_ON(!dc_commit_state(dm->dc, dc_state));

		dm_gpureset_commit_state(dm->cached_dc_state, dm);

		dm_gpureset_toggle_पूर्णांकerrupts(adev, dm->cached_dc_state, true);

		dc_release_state(dm->cached_dc_state);
		dm->cached_dc_state = शून्य;

		amdgpu_dm_irq_resume_late(adev);

		mutex_unlock(&dm->dc_lock);

		वापस 0;
	पूर्ण
	/* Recreate dc_state - DC invalidates it when setting घातer state to S3. */
	dc_release_state(dm_state->context);
	dm_state->context = dc_create_state(dm->dc);
	/* TODO: Remove dc_state->dccg, use dc->dccg directly. */
	dc_resource_state_स्थिरruct(dm->dc, dm_state->context);

	/* Beक्रमe घातering on DC we need to re-initialize DMUB. */
	r = dm_dmub_hw_init(adev);
	अगर (r)
		DRM_ERROR("DMUB interface failed to initialize: status=%d\n", r);

	/* घातer on hardware */
	dc_set_घातer_state(dm->dc, DC_ACPI_CM_POWER_STATE_D0);

	/* program HPD filter */
	dc_resume(dm->dc);

	/*
	 * early enable HPD Rx IRQ, should be करोne beक्रमe set mode as लघु
	 * pulse पूर्णांकerrupts are used क्रम MST
	 */
	amdgpu_dm_irq_resume_early(adev);

	/* On resume we need to reग_लिखो the MSTM control bits to enable MST*/
	s3_handle_mst(ddev, false);

	/* Do detection*/
	drm_connector_list_iter_begin(ddev, &iter);
	drm_क्रम_each_connector_iter(connector, &iter) अणु
		aconnector = to_amdgpu_dm_connector(connector);

		/*
		 * this is the हाल when traversing through alपढ़ोy created
		 * MST connectors, should be skipped
		 */
		अगर (aconnector->mst_port)
			जारी;

		mutex_lock(&aconnector->hpd_lock);
		अगर (!dc_link_detect_sink(aconnector->dc_link, &new_connection_type))
			DRM_ERROR("KMS: Failed to detect connector\n");

		अगर (aconnector->base.क्रमce && new_connection_type == dc_connection_none)
			emulated_link_detect(aconnector->dc_link);
		अन्यथा
			dc_link_detect(aconnector->dc_link, DETECT_REASON_HPD);

		अगर (aconnector->fake_enable && aconnector->dc_link->local_sink)
			aconnector->fake_enable = false;

		अगर (aconnector->dc_sink)
			dc_sink_release(aconnector->dc_sink);
		aconnector->dc_sink = शून्य;
		amdgpu_dm_update_connector_after_detect(aconnector);
		mutex_unlock(&aconnector->hpd_lock);
	पूर्ण
	drm_connector_list_iter_end(&iter);

	/* Force mode set in atomic commit */
	क्रम_each_new_crtc_in_state(dm->cached_state, crtc, new_crtc_state, i)
		new_crtc_state->active_changed = true;

	/*
	 * atomic_check is expected to create the dc states. We need to release
	 * them here, since they were duplicated as part of the suspend
	 * procedure.
	 */
	क्रम_each_new_crtc_in_state(dm->cached_state, crtc, new_crtc_state, i) अणु
		dm_new_crtc_state = to_dm_crtc_state(new_crtc_state);
		अगर (dm_new_crtc_state->stream) अणु
			WARN_ON(kref_पढ़ो(&dm_new_crtc_state->stream->refcount) > 1);
			dc_stream_release(dm_new_crtc_state->stream);
			dm_new_crtc_state->stream = शून्य;
		पूर्ण
	पूर्ण

	क्रम_each_new_plane_in_state(dm->cached_state, plane, new_plane_state, i) अणु
		dm_new_plane_state = to_dm_plane_state(new_plane_state);
		अगर (dm_new_plane_state->dc_state) अणु
			WARN_ON(kref_पढ़ो(&dm_new_plane_state->dc_state->refcount) > 1);
			dc_plane_state_release(dm_new_plane_state->dc_state);
			dm_new_plane_state->dc_state = शून्य;
		पूर्ण
	पूर्ण

	drm_atomic_helper_resume(ddev, dm->cached_state);

	dm->cached_state = शून्य;

#अगर_घोषित CONFIG_DRM_AMD_SECURE_DISPLAY
	amdgpu_dm_crtc_secure_display_resume(adev);
#पूर्ण_अगर

	amdgpu_dm_irq_resume_late(adev);

	amdgpu_dm_smu_ग_लिखो_watermarks_table(adev);

	वापस 0;
पूर्ण

/**
 * DOC: DM Lअगरecycle
 *
 * DM (and consequently DC) is रेजिस्टरed in the amdgpu base driver as a IP
 * block. When CONFIG_DRM_AMD_DC is enabled, the DM device IP block is added to
 * the base driver's device list to be initialized and torn करोwn accordingly.
 *
 * The functions to करो so are provided as hooks in &काष्ठा amd_ip_funcs.
 */

अटल स्थिर काष्ठा amd_ip_funcs amdgpu_dm_funcs = अणु
	.name = "dm",
	.early_init = dm_early_init,
	.late_init = dm_late_init,
	.sw_init = dm_sw_init,
	.sw_fini = dm_sw_fini,
	.hw_init = dm_hw_init,
	.hw_fini = dm_hw_fini,
	.suspend = dm_suspend,
	.resume = dm_resume,
	.is_idle = dm_is_idle,
	.रुको_क्रम_idle = dm_रुको_क्रम_idle,
	.check_soft_reset = dm_check_soft_reset,
	.soft_reset = dm_soft_reset,
	.set_घड़ीgating_state = dm_set_घड़ीgating_state,
	.set_घातergating_state = dm_set_घातergating_state,
पूर्ण;

स्थिर काष्ठा amdgpu_ip_block_version dm_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_DCE,
	.major = 1,
	.minor = 0,
	.rev = 0,
	.funcs = &amdgpu_dm_funcs,
पूर्ण;


/**
 * DOC: atomic
 *
 * *WIP*
 */

अटल स्थिर काष्ठा drm_mode_config_funcs amdgpu_dm_mode_funcs = अणु
	.fb_create = amdgpu_display_user_framebuffer_create,
	.get_क्रमmat_info = amd_get_क्रमmat_info,
	.output_poll_changed = drm_fb_helper_output_poll_changed,
	.atomic_check = amdgpu_dm_atomic_check,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

अटल काष्ठा drm_mode_config_helper_funcs amdgpu_dm_mode_config_helperfuncs = अणु
	.atomic_commit_tail = amdgpu_dm_atomic_commit_tail
पूर्ण;

अटल व्योम update_connector_ext_caps(काष्ठा amdgpu_dm_connector *aconnector)
अणु
	u32 max_cll, min_cll, max, min, q, r;
	काष्ठा amdgpu_dm_backlight_caps *caps;
	काष्ठा amdgpu_display_manager *dm;
	काष्ठा drm_connector *conn_base;
	काष्ठा amdgpu_device *adev;
	काष्ठा dc_link *link = शून्य;
	अटल स्थिर u8 pre_computed_values[] = अणु
		50, 51, 52, 53, 55, 56, 57, 58, 59, 61, 62, 63, 65, 66, 68, 69,
		71, 72, 74, 75, 77, 79, 81, 82, 84, 86, 88, 90, 92, 94, 96, 98पूर्ण;

	अगर (!aconnector || !aconnector->dc_link)
		वापस;

	link = aconnector->dc_link;
	अगर (link->connector_संकेत != SIGNAL_TYPE_EDP)
		वापस;

	conn_base = &aconnector->base;
	adev = drm_to_adev(conn_base->dev);
	dm = &adev->dm;
	caps = &dm->backlight_caps;
	caps->ext_caps = &aconnector->dc_link->dpcd_sink_ext_caps;
	caps->aux_support = false;
	max_cll = conn_base->hdr_sink_metadata.hdmi_type1.max_cll;
	min_cll = conn_base->hdr_sink_metadata.hdmi_type1.min_cll;

	अगर (caps->ext_caps->bits.oled == 1 ||
	    caps->ext_caps->bits.sdr_aux_backlight_control == 1 ||
	    caps->ext_caps->bits.hdr_aux_backlight_control == 1)
		caps->aux_support = true;

	अगर (amdgpu_backlight == 0)
		caps->aux_support = false;
	अन्यथा अगर (amdgpu_backlight == 1)
		caps->aux_support = true;

	/* From the specअगरication (CTA-861-G), क्रम calculating the maximum
	 * luminance we need to use:
	 *	Luminance = 50*2**(CV/32)
	 * Where CV is a one-byte value.
	 * For calculating this expression we may need भग्न poपूर्णांक precision;
	 * to aव्योम this complनिकासy level, we take advantage that CV is भागided
	 * by a स्थिरant. From the Euclids भागision algorithm, we know that CV
	 * can be written as: CV = 32*q + r. Next, we replace CV in the
	 * Luminance expression and get 50*(2**q)*(2**(r/32)), hence we just
	 * need to pre-compute the value of r/32. For pre-computing the values
	 * We just used the following Ruby line:
	 *	(0...32).each अणु|cv| माला_दो (50*2**(cv/32.0)).roundपूर्ण
	 * The results of the above expressions can be verअगरied at
	 * pre_computed_values.
	 */
	q = max_cll >> 5;
	r = max_cll % 32;
	max = (1 << q) * pre_computed_values[r];

	// min luminance: maxLum * (CV/255)^2 / 100
	q = DIV_ROUND_CLOSEST(min_cll, 255);
	min = max * DIV_ROUND_CLOSEST((q * q), 100);

	caps->aux_max_input_संकेत = max;
	caps->aux_min_input_संकेत = min;
पूर्ण

व्योम amdgpu_dm_update_connector_after_detect(
		काष्ठा amdgpu_dm_connector *aconnector)
अणु
	काष्ठा drm_connector *connector = &aconnector->base;
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा dc_sink *sink;

	/* MST handled by drm_mst framework */
	अगर (aconnector->mst_mgr.mst_state == true)
		वापस;

	sink = aconnector->dc_link->local_sink;
	अगर (sink)
		dc_sink_retain(sink);

	/*
	 * Edid mgmt connector माला_लो first update only in mode_valid hook and then
	 * the connector sink is set to either fake or physical sink depends on link status.
	 * Skip अगर alपढ़ोy करोne during boot.
	 */
	अगर (aconnector->base.क्रमce != DRM_FORCE_UNSPECIFIED
			&& aconnector->dc_em_sink) अणु

		/*
		 * For S3 resume with headless use eml_sink to fake stream
		 * because on resume connector->sink is set to शून्य
		 */
		mutex_lock(&dev->mode_config.mutex);

		अगर (sink) अणु
			अगर (aconnector->dc_sink) अणु
				amdgpu_dm_update_मुक्तsync_caps(connector, शून्य);
				/*
				 * retain and release below are used to
				 * bump up refcount क्रम sink because the link करोesn't poपूर्णांक
				 * to it anymore after disconnect, so on next crtc to connector
				 * reshuffle by UMD we will get पूर्णांकo unwanted dc_sink release
				 */
				dc_sink_release(aconnector->dc_sink);
			पूर्ण
			aconnector->dc_sink = sink;
			dc_sink_retain(aconnector->dc_sink);
			amdgpu_dm_update_मुक्तsync_caps(connector,
					aconnector->edid);
		पूर्ण अन्यथा अणु
			amdgpu_dm_update_मुक्तsync_caps(connector, शून्य);
			अगर (!aconnector->dc_sink) अणु
				aconnector->dc_sink = aconnector->dc_em_sink;
				dc_sink_retain(aconnector->dc_sink);
			पूर्ण
		पूर्ण

		mutex_unlock(&dev->mode_config.mutex);

		अगर (sink)
			dc_sink_release(sink);
		वापस;
	पूर्ण

	/*
	 * TODO: temporary guard to look क्रम proper fix
	 * अगर this sink is MST sink, we should not करो anything
	 */
	अगर (sink && sink->sink_संकेत == SIGNAL_TYPE_DISPLAY_PORT_MST) अणु
		dc_sink_release(sink);
		वापस;
	पूर्ण

	अगर (aconnector->dc_sink == sink) अणु
		/*
		 * We got a DP लघु pulse (Link Loss, DP CTS, etc...).
		 * Do nothing!!
		 */
		DRM_DEBUG_DRIVER("DCHPD: connector_id=%d: dc_sink didn't change.\n",
				aconnector->connector_id);
		अगर (sink)
			dc_sink_release(sink);
		वापस;
	पूर्ण

	DRM_DEBUG_DRIVER("DCHPD: connector_id=%d: Old sink=%p New sink=%p\n",
		aconnector->connector_id, aconnector->dc_sink, sink);

	mutex_lock(&dev->mode_config.mutex);

	/*
	 * 1. Update status of the drm connector
	 * 2. Send an event and let userspace tell us what to करो
	 */
	अगर (sink) अणु
		/*
		 * TODO: check अगर we still need the S3 mode update workaround.
		 * If yes, put it here.
		 */
		अगर (aconnector->dc_sink) अणु
			amdgpu_dm_update_मुक्तsync_caps(connector, शून्य);
			dc_sink_release(aconnector->dc_sink);
		पूर्ण

		aconnector->dc_sink = sink;
		dc_sink_retain(aconnector->dc_sink);
		अगर (sink->dc_edid.length == 0) अणु
			aconnector->edid = शून्य;
			अगर (aconnector->dc_link->aux_mode) अणु
				drm_dp_cec_unset_edid(
					&aconnector->dm_dp_aux.aux);
			पूर्ण
		पूर्ण अन्यथा अणु
			aconnector->edid =
				(काष्ठा edid *)sink->dc_edid.raw_edid;

			drm_connector_update_edid_property(connector,
							   aconnector->edid);
			अगर (aconnector->dc_link->aux_mode)
				drm_dp_cec_set_edid(&aconnector->dm_dp_aux.aux,
						    aconnector->edid);
		पूर्ण

		amdgpu_dm_update_मुक्तsync_caps(connector, aconnector->edid);
		update_connector_ext_caps(aconnector);
	पूर्ण अन्यथा अणु
		drm_dp_cec_unset_edid(&aconnector->dm_dp_aux.aux);
		amdgpu_dm_update_मुक्तsync_caps(connector, शून्य);
		drm_connector_update_edid_property(connector, शून्य);
		aconnector->num_modes = 0;
		dc_sink_release(aconnector->dc_sink);
		aconnector->dc_sink = शून्य;
		aconnector->edid = शून्य;
#अगर_घोषित CONFIG_DRM_AMD_DC_HDCP
		/* Set CP to DESIRED अगर it was ENABLED, so we can re-enable it again on hotplug */
		अगर (connector->state->content_protection == DRM_MODE_CONTENT_PROTECTION_ENABLED)
			connector->state->content_protection = DRM_MODE_CONTENT_PROTECTION_DESIRED;
#पूर्ण_अगर
	पूर्ण

	mutex_unlock(&dev->mode_config.mutex);

	update_subconnector_property(aconnector);

	अगर (sink)
		dc_sink_release(sink);
पूर्ण

अटल व्योम handle_hpd_irq(व्योम *param)
अणु
	काष्ठा amdgpu_dm_connector *aconnector = (काष्ठा amdgpu_dm_connector *)param;
	काष्ठा drm_connector *connector = &aconnector->base;
	काष्ठा drm_device *dev = connector->dev;
	क्रमागत dc_connection_type new_connection_type = dc_connection_none;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
#अगर_घोषित CONFIG_DRM_AMD_DC_HDCP
	काष्ठा dm_connector_state *dm_con_state = to_dm_connector_state(connector->state);
#पूर्ण_अगर

	अगर (adev->dm.disable_hpd_irq)
		वापस;

	/*
	 * In हाल of failure or MST no need to update connector status or notअगरy the OS
	 * since (क्रम MST हाल) MST करोes this in its own context.
	 */
	mutex_lock(&aconnector->hpd_lock);

#अगर_घोषित CONFIG_DRM_AMD_DC_HDCP
	अगर (adev->dm.hdcp_workqueue) अणु
		hdcp_reset_display(adev->dm.hdcp_workqueue, aconnector->dc_link->link_index);
		dm_con_state->update_hdcp = true;
	पूर्ण
#पूर्ण_अगर
	अगर (aconnector->fake_enable)
		aconnector->fake_enable = false;

	अगर (!dc_link_detect_sink(aconnector->dc_link, &new_connection_type))
		DRM_ERROR("KMS: Failed to detect connector\n");

	अगर (aconnector->base.क्रमce && new_connection_type == dc_connection_none) अणु
		emulated_link_detect(aconnector->dc_link);


		drm_modeset_lock_all(dev);
		dm_restore_drm_connector_state(dev, connector);
		drm_modeset_unlock_all(dev);

		अगर (aconnector->base.क्रमce == DRM_FORCE_UNSPECIFIED)
			drm_kms_helper_hotplug_event(dev);

	पूर्ण अन्यथा अगर (dc_link_detect(aconnector->dc_link, DETECT_REASON_HPD)) अणु
		अगर (new_connection_type == dc_connection_none &&
		    aconnector->dc_link->type == dc_connection_none)
			dm_set_dpms_off(aconnector->dc_link);

		amdgpu_dm_update_connector_after_detect(aconnector);

		drm_modeset_lock_all(dev);
		dm_restore_drm_connector_state(dev, connector);
		drm_modeset_unlock_all(dev);

		अगर (aconnector->base.क्रमce == DRM_FORCE_UNSPECIFIED)
			drm_kms_helper_hotplug_event(dev);
	पूर्ण
	mutex_unlock(&aconnector->hpd_lock);

पूर्ण

अटल व्योम dm_handle_hpd_rx_irq(काष्ठा amdgpu_dm_connector *aconnector)
अणु
	uपूर्णांक8_t esi[DP_PSR_ERROR_STATUS - DP_SINK_COUNT_ESI] = अणु 0 पूर्ण;
	uपूर्णांक8_t dret;
	bool new_irq_handled = false;
	पूर्णांक dpcd_addr;
	पूर्णांक dpcd_bytes_to_पढ़ो;

	स्थिर पूर्णांक max_process_count = 30;
	पूर्णांक process_count = 0;

	स्थिर काष्ठा dc_link_status *link_status = dc_link_get_status(aconnector->dc_link);

	अगर (link_status->dpcd_caps->dpcd_rev.raw < 0x12) अणु
		dpcd_bytes_to_पढ़ो = DP_LANE0_1_STATUS - DP_SINK_COUNT;
		/* DPCD 0x200 - 0x201 क्रम करोwnstream IRQ */
		dpcd_addr = DP_SINK_COUNT;
	पूर्ण अन्यथा अणु
		dpcd_bytes_to_पढ़ो = DP_PSR_ERROR_STATUS - DP_SINK_COUNT_ESI;
		/* DPCD 0x2002 - 0x2005 क्रम करोwnstream IRQ */
		dpcd_addr = DP_SINK_COUNT_ESI;
	पूर्ण

	dret = drm_dp_dpcd_पढ़ो(
		&aconnector->dm_dp_aux.aux,
		dpcd_addr,
		esi,
		dpcd_bytes_to_पढ़ो);

	जबतक (dret == dpcd_bytes_to_पढ़ो &&
		process_count < max_process_count) अणु
		uपूर्णांक8_t retry;
		dret = 0;

		process_count++;

		DRM_DEBUG_DRIVER("ESI %02x %02x %02x\n", esi[0], esi[1], esi[2]);
		/* handle HPD लघु pulse irq */
		अगर (aconnector->mst_mgr.mst_state)
			drm_dp_mst_hpd_irq(
				&aconnector->mst_mgr,
				esi,
				&new_irq_handled);

		अगर (new_irq_handled) अणु
			/* ACK at DPCD to notअगरy करोwn stream */
			स्थिर पूर्णांक ack_dpcd_bytes_to_ग_लिखो =
				dpcd_bytes_to_पढ़ो - 1;

			क्रम (retry = 0; retry < 3; retry++) अणु
				uपूर्णांक8_t wret;

				wret = drm_dp_dpcd_ग_लिखो(
					&aconnector->dm_dp_aux.aux,
					dpcd_addr + 1,
					&esi[1],
					ack_dpcd_bytes_to_ग_लिखो);
				अगर (wret == ack_dpcd_bytes_to_ग_लिखो)
					अवरोध;
			पूर्ण

			/* check अगर there is new irq to be handled */
			dret = drm_dp_dpcd_पढ़ो(
				&aconnector->dm_dp_aux.aux,
				dpcd_addr,
				esi,
				dpcd_bytes_to_पढ़ो);

			new_irq_handled = false;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (process_count == max_process_count)
		DRM_DEBUG_DRIVER("Loop exceeded max iterations\n");
पूर्ण

अटल व्योम handle_hpd_rx_irq(व्योम *param)
अणु
	काष्ठा amdgpu_dm_connector *aconnector = (काष्ठा amdgpu_dm_connector *)param;
	काष्ठा drm_connector *connector = &aconnector->base;
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा dc_link *dc_link = aconnector->dc_link;
	bool is_mst_root_connector = aconnector->mst_mgr.mst_state;
	bool result = false;
	क्रमागत dc_connection_type new_connection_type = dc_connection_none;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	जोड़ hpd_irq_data hpd_irq_data;

	स_रखो(&hpd_irq_data, 0, माप(hpd_irq_data));

	अगर (adev->dm.disable_hpd_irq)
		वापस;


	/*
	 * TODO:Temporary add mutex to protect hpd पूर्णांकerrupt not have a gpio
	 * conflict, after implement i2c helper, this mutex should be
	 * retired.
	 */
	अगर (dc_link->type != dc_connection_mst_branch)
		mutex_lock(&aconnector->hpd_lock);

	पढ़ो_hpd_rx_irq_data(dc_link, &hpd_irq_data);

	अगर ((dc_link->cur_link_settings.lane_count != LANE_COUNT_UNKNOWN) ||
		(dc_link->type == dc_connection_mst_branch)) अणु
		अगर (hpd_irq_data.bytes.device_service_irq.bits.UP_REQ_MSG_RDY) अणु
			result = true;
			dm_handle_hpd_rx_irq(aconnector);
			जाओ out;
		पूर्ण अन्यथा अगर (hpd_irq_data.bytes.device_service_irq.bits.DOWN_REP_MSG_RDY) अणु
			result = false;
			dm_handle_hpd_rx_irq(aconnector);
			जाओ out;
		पूर्ण
	पूर्ण

	mutex_lock(&adev->dm.dc_lock);
#अगर_घोषित CONFIG_DRM_AMD_DC_HDCP
	result = dc_link_handle_hpd_rx_irq(dc_link, &hpd_irq_data, शून्य);
#अन्यथा
	result = dc_link_handle_hpd_rx_irq(dc_link, शून्य, शून्य);
#पूर्ण_अगर
	mutex_unlock(&adev->dm.dc_lock);

out:
	अगर (result && !is_mst_root_connector) अणु
		/* Downstream Port status changed. */
		अगर (!dc_link_detect_sink(dc_link, &new_connection_type))
			DRM_ERROR("KMS: Failed to detect connector\n");

		अगर (aconnector->base.क्रमce && new_connection_type == dc_connection_none) अणु
			emulated_link_detect(dc_link);

			अगर (aconnector->fake_enable)
				aconnector->fake_enable = false;

			amdgpu_dm_update_connector_after_detect(aconnector);


			drm_modeset_lock_all(dev);
			dm_restore_drm_connector_state(dev, connector);
			drm_modeset_unlock_all(dev);

			drm_kms_helper_hotplug_event(dev);
		पूर्ण अन्यथा अगर (dc_link_detect(dc_link, DETECT_REASON_HPDRX)) अणु

			अगर (aconnector->fake_enable)
				aconnector->fake_enable = false;

			amdgpu_dm_update_connector_after_detect(aconnector);


			drm_modeset_lock_all(dev);
			dm_restore_drm_connector_state(dev, connector);
			drm_modeset_unlock_all(dev);

			drm_kms_helper_hotplug_event(dev);
		पूर्ण
	पूर्ण
#अगर_घोषित CONFIG_DRM_AMD_DC_HDCP
	अगर (hpd_irq_data.bytes.device_service_irq.bits.CP_IRQ) अणु
		अगर (adev->dm.hdcp_workqueue)
			hdcp_handle_cpirq(adev->dm.hdcp_workqueue,  aconnector->base.index);
	पूर्ण
#पूर्ण_अगर

	अगर (dc_link->type != dc_connection_mst_branch) अणु
		drm_dp_cec_irq(&aconnector->dm_dp_aux.aux);
		mutex_unlock(&aconnector->hpd_lock);
	पूर्ण
पूर्ण

अटल व्योम रेजिस्टर_hpd_handlers(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा drm_device *dev = adev_to_drm(adev);
	काष्ठा drm_connector *connector;
	काष्ठा amdgpu_dm_connector *aconnector;
	स्थिर काष्ठा dc_link *dc_link;
	काष्ठा dc_पूर्णांकerrupt_params पूर्णांक_params = अणु0पूर्ण;

	पूर्णांक_params.requested_polarity = INTERRUPT_POLARITY_DEFAULT;
	पूर्णांक_params.current_polarity = INTERRUPT_POLARITY_DEFAULT;

	list_क्रम_each_entry(connector,
			&dev->mode_config.connector_list, head)	अणु

		aconnector = to_amdgpu_dm_connector(connector);
		dc_link = aconnector->dc_link;

		अगर (DC_IRQ_SOURCE_INVALID != dc_link->irq_source_hpd) अणु
			पूर्णांक_params.पूर्णांक_context = INTERRUPT_LOW_IRQ_CONTEXT;
			पूर्णांक_params.irq_source = dc_link->irq_source_hpd;

			amdgpu_dm_irq_रेजिस्टर_पूर्णांकerrupt(adev, &पूर्णांक_params,
					handle_hpd_irq,
					(व्योम *) aconnector);
		पूर्ण

		अगर (DC_IRQ_SOURCE_INVALID != dc_link->irq_source_hpd_rx) अणु

			/* Also रेजिस्टर क्रम DP लघु pulse (hpd_rx). */
			पूर्णांक_params.पूर्णांक_context = INTERRUPT_LOW_IRQ_CONTEXT;
			पूर्णांक_params.irq_source =	dc_link->irq_source_hpd_rx;

			amdgpu_dm_irq_रेजिस्टर_पूर्णांकerrupt(adev, &पूर्णांक_params,
					handle_hpd_rx_irq,
					(व्योम *) aconnector);
		पूर्ण
	पूर्ण
पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_SI)
/* Register IRQ sources and initialize IRQ callbacks */
अटल पूर्णांक dce60_रेजिस्टर_irq_handlers(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा dc *dc = adev->dm.dc;
	काष्ठा common_irq_params *c_irq_params;
	काष्ठा dc_पूर्णांकerrupt_params पूर्णांक_params = अणु0पूर्ण;
	पूर्णांक r;
	पूर्णांक i;
	अचिन्हित client_id = AMDGPU_IRQ_CLIENTID_LEGACY;

	पूर्णांक_params.requested_polarity = INTERRUPT_POLARITY_DEFAULT;
	पूर्णांक_params.current_polarity = INTERRUPT_POLARITY_DEFAULT;

	/*
	 * Actions of amdgpu_irq_add_id():
	 * 1. Register a set() function with base driver.
	 *    Base driver will call set() function to enable/disable an
	 *    पूर्णांकerrupt in DC hardware.
	 * 2. Register amdgpu_dm_irq_handler().
	 *    Base driver will call amdgpu_dm_irq_handler() क्रम ALL पूर्णांकerrupts
	 *    coming from DC hardware.
	 *    amdgpu_dm_irq_handler() will re-direct the पूर्णांकerrupt to DC
	 *    क्रम acknowledging and handling. */

	/* Use VBLANK पूर्णांकerrupt */
	क्रम (i = 0; i < adev->mode_info.num_crtc; i++) अणु
		r = amdgpu_irq_add_id(adev, client_id, i+1 , &adev->crtc_irq);
		अगर (r) अणु
			DRM_ERROR("Failed to add crtc irq id!\n");
			वापस r;
		पूर्ण

		पूर्णांक_params.पूर्णांक_context = INTERRUPT_HIGH_IRQ_CONTEXT;
		पूर्णांक_params.irq_source =
			dc_पूर्णांकerrupt_to_irq_source(dc, i+1 , 0);

		c_irq_params = &adev->dm.vblank_params[पूर्णांक_params.irq_source - DC_IRQ_SOURCE_VBLANK1];

		c_irq_params->adev = adev;
		c_irq_params->irq_src = पूर्णांक_params.irq_source;

		amdgpu_dm_irq_रेजिस्टर_पूर्णांकerrupt(adev, &पूर्णांक_params,
				dm_crtc_high_irq, c_irq_params);
	पूर्ण

	/* Use GRPH_PFLIP पूर्णांकerrupt */
	क्रम (i = VISLANDS30_IV_SRCID_D1_GRPH_PFLIP;
			i <= VISLANDS30_IV_SRCID_D6_GRPH_PFLIP; i += 2) अणु
		r = amdgpu_irq_add_id(adev, client_id, i, &adev->pageflip_irq);
		अगर (r) अणु
			DRM_ERROR("Failed to add page flip irq id!\n");
			वापस r;
		पूर्ण

		पूर्णांक_params.पूर्णांक_context = INTERRUPT_HIGH_IRQ_CONTEXT;
		पूर्णांक_params.irq_source =
			dc_पूर्णांकerrupt_to_irq_source(dc, i, 0);

		c_irq_params = &adev->dm.pflip_params[पूर्णांक_params.irq_source - DC_IRQ_SOURCE_PFLIP_FIRST];

		c_irq_params->adev = adev;
		c_irq_params->irq_src = पूर्णांक_params.irq_source;

		amdgpu_dm_irq_रेजिस्टर_पूर्णांकerrupt(adev, &पूर्णांक_params,
				dm_pflip_high_irq, c_irq_params);

	पूर्ण

	/* HPD */
	r = amdgpu_irq_add_id(adev, client_id,
			VISLANDS30_IV_SRCID_HOTPLUG_DETECT_A, &adev->hpd_irq);
	अगर (r) अणु
		DRM_ERROR("Failed to add hpd irq id!\n");
		वापस r;
	पूर्ण

	रेजिस्टर_hpd_handlers(adev);

	वापस 0;
पूर्ण
#पूर्ण_अगर

/* Register IRQ sources and initialize IRQ callbacks */
अटल पूर्णांक dce110_रेजिस्टर_irq_handlers(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा dc *dc = adev->dm.dc;
	काष्ठा common_irq_params *c_irq_params;
	काष्ठा dc_पूर्णांकerrupt_params पूर्णांक_params = अणु0पूर्ण;
	पूर्णांक r;
	पूर्णांक i;
	अचिन्हित client_id = AMDGPU_IRQ_CLIENTID_LEGACY;

	अगर (adev->asic_type >= CHIP_VEGA10)
		client_id = SOC15_IH_CLIENTID_DCE;

	पूर्णांक_params.requested_polarity = INTERRUPT_POLARITY_DEFAULT;
	पूर्णांक_params.current_polarity = INTERRUPT_POLARITY_DEFAULT;

	/*
	 * Actions of amdgpu_irq_add_id():
	 * 1. Register a set() function with base driver.
	 *    Base driver will call set() function to enable/disable an
	 *    पूर्णांकerrupt in DC hardware.
	 * 2. Register amdgpu_dm_irq_handler().
	 *    Base driver will call amdgpu_dm_irq_handler() क्रम ALL पूर्णांकerrupts
	 *    coming from DC hardware.
	 *    amdgpu_dm_irq_handler() will re-direct the पूर्णांकerrupt to DC
	 *    क्रम acknowledging and handling. */

	/* Use VBLANK पूर्णांकerrupt */
	क्रम (i = VISLANDS30_IV_SRCID_D1_VERTICAL_INTERRUPT0; i <= VISLANDS30_IV_SRCID_D6_VERTICAL_INTERRUPT0; i++) अणु
		r = amdgpu_irq_add_id(adev, client_id, i, &adev->crtc_irq);
		अगर (r) अणु
			DRM_ERROR("Failed to add crtc irq id!\n");
			वापस r;
		पूर्ण

		पूर्णांक_params.पूर्णांक_context = INTERRUPT_HIGH_IRQ_CONTEXT;
		पूर्णांक_params.irq_source =
			dc_पूर्णांकerrupt_to_irq_source(dc, i, 0);

		c_irq_params = &adev->dm.vblank_params[पूर्णांक_params.irq_source - DC_IRQ_SOURCE_VBLANK1];

		c_irq_params->adev = adev;
		c_irq_params->irq_src = पूर्णांक_params.irq_source;

		amdgpu_dm_irq_रेजिस्टर_पूर्णांकerrupt(adev, &पूर्णांक_params,
				dm_crtc_high_irq, c_irq_params);
	पूर्ण

	/* Use VUPDATE पूर्णांकerrupt */
	क्रम (i = VISLANDS30_IV_SRCID_D1_V_UPDATE_INT; i <= VISLANDS30_IV_SRCID_D6_V_UPDATE_INT; i += 2) अणु
		r = amdgpu_irq_add_id(adev, client_id, i, &adev->vupdate_irq);
		अगर (r) अणु
			DRM_ERROR("Failed to add vupdate irq id!\n");
			वापस r;
		पूर्ण

		पूर्णांक_params.पूर्णांक_context = INTERRUPT_HIGH_IRQ_CONTEXT;
		पूर्णांक_params.irq_source =
			dc_पूर्णांकerrupt_to_irq_source(dc, i, 0);

		c_irq_params = &adev->dm.vupdate_params[पूर्णांक_params.irq_source - DC_IRQ_SOURCE_VUPDATE1];

		c_irq_params->adev = adev;
		c_irq_params->irq_src = पूर्णांक_params.irq_source;

		amdgpu_dm_irq_रेजिस्टर_पूर्णांकerrupt(adev, &पूर्णांक_params,
				dm_vupdate_high_irq, c_irq_params);
	पूर्ण

	/* Use GRPH_PFLIP पूर्णांकerrupt */
	क्रम (i = VISLANDS30_IV_SRCID_D1_GRPH_PFLIP;
			i <= VISLANDS30_IV_SRCID_D6_GRPH_PFLIP; i += 2) अणु
		r = amdgpu_irq_add_id(adev, client_id, i, &adev->pageflip_irq);
		अगर (r) अणु
			DRM_ERROR("Failed to add page flip irq id!\n");
			वापस r;
		पूर्ण

		पूर्णांक_params.पूर्णांक_context = INTERRUPT_HIGH_IRQ_CONTEXT;
		पूर्णांक_params.irq_source =
			dc_पूर्णांकerrupt_to_irq_source(dc, i, 0);

		c_irq_params = &adev->dm.pflip_params[पूर्णांक_params.irq_source - DC_IRQ_SOURCE_PFLIP_FIRST];

		c_irq_params->adev = adev;
		c_irq_params->irq_src = पूर्णांक_params.irq_source;

		amdgpu_dm_irq_रेजिस्टर_पूर्णांकerrupt(adev, &पूर्णांक_params,
				dm_pflip_high_irq, c_irq_params);

	पूर्ण

	/* HPD */
	r = amdgpu_irq_add_id(adev, client_id,
			VISLANDS30_IV_SRCID_HOTPLUG_DETECT_A, &adev->hpd_irq);
	अगर (r) अणु
		DRM_ERROR("Failed to add hpd irq id!\n");
		वापस r;
	पूर्ण

	रेजिस्टर_hpd_handlers(adev);

	वापस 0;
पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
/* Register IRQ sources and initialize IRQ callbacks */
अटल पूर्णांक dcn10_रेजिस्टर_irq_handlers(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा dc *dc = adev->dm.dc;
	काष्ठा common_irq_params *c_irq_params;
	काष्ठा dc_पूर्णांकerrupt_params पूर्णांक_params = अणु0पूर्ण;
	पूर्णांक r;
	पूर्णांक i;
#अगर defined(CONFIG_DRM_AMD_SECURE_DISPLAY)
	अटल स्थिर अचिन्हित पूर्णांक vrtl_पूर्णांक_srcid[] = अणु
		DCN_1_0__SRCID__OTG1_VERTICAL_INTERRUPT0_CONTROL,
		DCN_1_0__SRCID__OTG2_VERTICAL_INTERRUPT0_CONTROL,
		DCN_1_0__SRCID__OTG3_VERTICAL_INTERRUPT0_CONTROL,
		DCN_1_0__SRCID__OTG4_VERTICAL_INTERRUPT0_CONTROL,
		DCN_1_0__SRCID__OTG5_VERTICAL_INTERRUPT0_CONTROL,
		DCN_1_0__SRCID__OTG6_VERTICAL_INTERRUPT0_CONTROL
	पूर्ण;
#पूर्ण_अगर

	पूर्णांक_params.requested_polarity = INTERRUPT_POLARITY_DEFAULT;
	पूर्णांक_params.current_polarity = INTERRUPT_POLARITY_DEFAULT;

	/*
	 * Actions of amdgpu_irq_add_id():
	 * 1. Register a set() function with base driver.
	 *    Base driver will call set() function to enable/disable an
	 *    पूर्णांकerrupt in DC hardware.
	 * 2. Register amdgpu_dm_irq_handler().
	 *    Base driver will call amdgpu_dm_irq_handler() क्रम ALL पूर्णांकerrupts
	 *    coming from DC hardware.
	 *    amdgpu_dm_irq_handler() will re-direct the पूर्णांकerrupt to DC
	 *    क्रम acknowledging and handling.
	 */

	/* Use VSTARTUP पूर्णांकerrupt */
	क्रम (i = DCN_1_0__SRCID__DC_D1_OTG_VSTARTUP;
			i <= DCN_1_0__SRCID__DC_D1_OTG_VSTARTUP + adev->mode_info.num_crtc - 1;
			i++) अणु
		r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_DCE, i, &adev->crtc_irq);

		अगर (r) अणु
			DRM_ERROR("Failed to add crtc irq id!\n");
			वापस r;
		पूर्ण

		पूर्णांक_params.पूर्णांक_context = INTERRUPT_HIGH_IRQ_CONTEXT;
		पूर्णांक_params.irq_source =
			dc_पूर्णांकerrupt_to_irq_source(dc, i, 0);

		c_irq_params = &adev->dm.vblank_params[पूर्णांक_params.irq_source - DC_IRQ_SOURCE_VBLANK1];

		c_irq_params->adev = adev;
		c_irq_params->irq_src = पूर्णांक_params.irq_source;

		amdgpu_dm_irq_रेजिस्टर_पूर्णांकerrupt(
			adev, &पूर्णांक_params, dm_crtc_high_irq, c_irq_params);
	पूर्ण

	/* Use otg vertical line पूर्णांकerrupt */
#अगर defined(CONFIG_DRM_AMD_SECURE_DISPLAY)
	क्रम (i = 0; i <= adev->mode_info.num_crtc - 1; i++) अणु
		r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_DCE,
				vrtl_पूर्णांक_srcid[i], &adev->vline0_irq);

		अगर (r) अणु
			DRM_ERROR("Failed to add vline0 irq id!\n");
			वापस r;
		पूर्ण

		पूर्णांक_params.पूर्णांक_context = INTERRUPT_HIGH_IRQ_CONTEXT;
		पूर्णांक_params.irq_source =
			dc_पूर्णांकerrupt_to_irq_source(dc, vrtl_पूर्णांक_srcid[i], 0);

		अगर (पूर्णांक_params.irq_source == DC_IRQ_SOURCE_INVALID) अणु
			DRM_ERROR("Failed to register vline0 irq %d!\n", vrtl_पूर्णांक_srcid[i]);
			अवरोध;
		पूर्ण

		c_irq_params = &adev->dm.vline0_params[पूर्णांक_params.irq_source
					- DC_IRQ_SOURCE_DC1_VLINE0];

		c_irq_params->adev = adev;
		c_irq_params->irq_src = पूर्णांक_params.irq_source;

		amdgpu_dm_irq_रेजिस्टर_पूर्णांकerrupt(adev, &पूर्णांक_params,
				dm_dcn_vertical_पूर्णांकerrupt0_high_irq, c_irq_params);
	पूर्ण
#पूर्ण_अगर

	/* Use VUPDATE_NO_LOCK पूर्णांकerrupt on DCN, which seems to correspond to
	 * the regular VUPDATE पूर्णांकerrupt on DCE. We want DC_IRQ_SOURCE_VUPDATEx
	 * to trigger at end of each vblank, regardless of state of the lock,
	 * matching DCE behaviour.
	 */
	क्रम (i = DCN_1_0__SRCID__OTG0_IHC_V_UPDATE_NO_LOCK_INTERRUPT;
	     i <= DCN_1_0__SRCID__OTG0_IHC_V_UPDATE_NO_LOCK_INTERRUPT + adev->mode_info.num_crtc - 1;
	     i++) अणु
		r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_DCE, i, &adev->vupdate_irq);

		अगर (r) अणु
			DRM_ERROR("Failed to add vupdate irq id!\n");
			वापस r;
		पूर्ण

		पूर्णांक_params.पूर्णांक_context = INTERRUPT_HIGH_IRQ_CONTEXT;
		पूर्णांक_params.irq_source =
			dc_पूर्णांकerrupt_to_irq_source(dc, i, 0);

		c_irq_params = &adev->dm.vupdate_params[पूर्णांक_params.irq_source - DC_IRQ_SOURCE_VUPDATE1];

		c_irq_params->adev = adev;
		c_irq_params->irq_src = पूर्णांक_params.irq_source;

		amdgpu_dm_irq_रेजिस्टर_पूर्णांकerrupt(adev, &पूर्णांक_params,
				dm_vupdate_high_irq, c_irq_params);
	पूर्ण

	/* Use GRPH_PFLIP पूर्णांकerrupt */
	क्रम (i = DCN_1_0__SRCID__HUBP0_FLIP_INTERRUPT;
			i <= DCN_1_0__SRCID__HUBP0_FLIP_INTERRUPT + adev->mode_info.num_crtc - 1;
			i++) अणु
		r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_DCE, i, &adev->pageflip_irq);
		अगर (r) अणु
			DRM_ERROR("Failed to add page flip irq id!\n");
			वापस r;
		पूर्ण

		पूर्णांक_params.पूर्णांक_context = INTERRUPT_HIGH_IRQ_CONTEXT;
		पूर्णांक_params.irq_source =
			dc_पूर्णांकerrupt_to_irq_source(dc, i, 0);

		c_irq_params = &adev->dm.pflip_params[पूर्णांक_params.irq_source - DC_IRQ_SOURCE_PFLIP_FIRST];

		c_irq_params->adev = adev;
		c_irq_params->irq_src = पूर्णांक_params.irq_source;

		amdgpu_dm_irq_रेजिस्टर_पूर्णांकerrupt(adev, &पूर्णांक_params,
				dm_pflip_high_irq, c_irq_params);

	पूर्ण

	अगर (dc->ctx->dmub_srv) अणु
		i = DCN_1_0__SRCID__DMCUB_OUTBOX_HIGH_PRIORITY_READY_INT;
		r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_DCE, i, &adev->dmub_trace_irq);

		अगर (r) अणु
			DRM_ERROR("Failed to add dmub trace irq id!\n");
			वापस r;
		पूर्ण

		पूर्णांक_params.पूर्णांक_context = INTERRUPT_HIGH_IRQ_CONTEXT;
		पूर्णांक_params.irq_source =
			dc_पूर्णांकerrupt_to_irq_source(dc, i, 0);

		c_irq_params = &adev->dm.dmub_trace_params[0];

		c_irq_params->adev = adev;
		c_irq_params->irq_src = पूर्णांक_params.irq_source;

		amdgpu_dm_irq_रेजिस्टर_पूर्णांकerrupt(adev, &पूर्णांक_params,
				dm_dmub_trace_high_irq, c_irq_params);
	पूर्ण

	/* HPD */
	r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_DCE, DCN_1_0__SRCID__DC_HPD1_INT,
			&adev->hpd_irq);
	अगर (r) अणु
		DRM_ERROR("Failed to add hpd irq id!\n");
		वापस r;
	पूर्ण

	रेजिस्टर_hpd_handlers(adev);

	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * Acquires the lock क्रम the atomic state object and वापसs
 * the new atomic state.
 *
 * This should only be called during atomic check.
 */
अटल पूर्णांक dm_atomic_get_state(काष्ठा drm_atomic_state *state,
			       काष्ठा dm_atomic_state **dm_state)
अणु
	काष्ठा drm_device *dev = state->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_display_manager *dm = &adev->dm;
	काष्ठा drm_निजी_state *priv_state;

	अगर (*dm_state)
		वापस 0;

	priv_state = drm_atomic_get_निजी_obj_state(state, &dm->atomic_obj);
	अगर (IS_ERR(priv_state))
		वापस PTR_ERR(priv_state);

	*dm_state = to_dm_atomic_state(priv_state);

	वापस 0;
पूर्ण

अटल काष्ठा dm_atomic_state *
dm_atomic_get_new_state(काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_device *dev = state->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_display_manager *dm = &adev->dm;
	काष्ठा drm_निजी_obj *obj;
	काष्ठा drm_निजी_state *new_obj_state;
	पूर्णांक i;

	क्रम_each_new_निजी_obj_in_state(state, obj, new_obj_state, i) अणु
		अगर (obj->funcs == dm->atomic_obj.funcs)
			वापस to_dm_atomic_state(new_obj_state);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा drm_निजी_state *
dm_atomic_duplicate_state(काष्ठा drm_निजी_obj *obj)
अणु
	काष्ठा dm_atomic_state *old_state, *new_state;

	new_state = kzalloc(माप(*new_state), GFP_KERNEL);
	अगर (!new_state)
		वापस शून्य;

	__drm_atomic_helper_निजी_obj_duplicate_state(obj, &new_state->base);

	old_state = to_dm_atomic_state(obj->state);

	अगर (old_state && old_state->context)
		new_state->context = dc_copy_state(old_state->context);

	अगर (!new_state->context) अणु
		kमुक्त(new_state);
		वापस शून्य;
	पूर्ण

	वापस &new_state->base;
पूर्ण

अटल व्योम dm_atomic_destroy_state(काष्ठा drm_निजी_obj *obj,
				    काष्ठा drm_निजी_state *state)
अणु
	काष्ठा dm_atomic_state *dm_state = to_dm_atomic_state(state);

	अगर (dm_state && dm_state->context)
		dc_release_state(dm_state->context);

	kमुक्त(dm_state);
पूर्ण

अटल काष्ठा drm_निजी_state_funcs dm_atomic_state_funcs = अणु
	.atomic_duplicate_state = dm_atomic_duplicate_state,
	.atomic_destroy_state = dm_atomic_destroy_state,
पूर्ण;

अटल पूर्णांक amdgpu_dm_mode_config_init(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा dm_atomic_state *state;
	पूर्णांक r;

	adev->mode_info.mode_config_initialized = true;

	adev_to_drm(adev)->mode_config.funcs = (व्योम *)&amdgpu_dm_mode_funcs;
	adev_to_drm(adev)->mode_config.helper_निजी = &amdgpu_dm_mode_config_helperfuncs;

	adev_to_drm(adev)->mode_config.max_width = 16384;
	adev_to_drm(adev)->mode_config.max_height = 16384;

	adev_to_drm(adev)->mode_config.preferred_depth = 24;
	adev_to_drm(adev)->mode_config.prefer_shaकरोw = 1;
	/* indicates support क्रम immediate flip */
	adev_to_drm(adev)->mode_config.async_page_flip = true;

	adev_to_drm(adev)->mode_config.fb_base = adev->gmc.aper_base;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस -ENOMEM;

	state->context = dc_create_state(adev->dm.dc);
	अगर (!state->context) अणु
		kमुक्त(state);
		वापस -ENOMEM;
	पूर्ण

	dc_resource_state_copy_स्थिरruct_current(adev->dm.dc, state->context);

	drm_atomic_निजी_obj_init(adev_to_drm(adev),
				    &adev->dm.atomic_obj,
				    &state->base,
				    &dm_atomic_state_funcs);

	r = amdgpu_display_modeset_create_props(adev);
	अगर (r) अणु
		dc_release_state(state->context);
		kमुक्त(state);
		वापस r;
	पूर्ण

	r = amdgpu_dm_audio_init(adev);
	अगर (r) अणु
		dc_release_state(state->context);
		kमुक्त(state);
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा AMDGPU_DM_DEFAULT_MIN_BACKLIGHT 12
#घोषणा AMDGPU_DM_DEFAULT_MAX_BACKLIGHT 255
#घोषणा AUX_BL_DEFAULT_TRANSITION_TIME_MS 50

#अगर defined(CONFIG_BACKLIGHT_CLASS_DEVICE) ||\
	defined(CONFIG_BACKLIGHT_CLASS_DEVICE_MODULE)

अटल व्योम amdgpu_dm_update_backlight_caps(काष्ठा amdgpu_display_manager *dm)
अणु
#अगर defined(CONFIG_ACPI)
	काष्ठा amdgpu_dm_backlight_caps caps;

	स_रखो(&caps, 0, माप(caps));

	अगर (dm->backlight_caps.caps_valid)
		वापस;

	amdgpu_acpi_get_backlight_caps(dm->adev, &caps);
	अगर (caps.caps_valid) अणु
		dm->backlight_caps.caps_valid = true;
		अगर (caps.aux_support)
			वापस;
		dm->backlight_caps.min_input_संकेत = caps.min_input_संकेत;
		dm->backlight_caps.max_input_संकेत = caps.max_input_संकेत;
	पूर्ण अन्यथा अणु
		dm->backlight_caps.min_input_संकेत =
				AMDGPU_DM_DEFAULT_MIN_BACKLIGHT;
		dm->backlight_caps.max_input_संकेत =
				AMDGPU_DM_DEFAULT_MAX_BACKLIGHT;
	पूर्ण
#अन्यथा
	अगर (dm->backlight_caps.aux_support)
		वापस;

	dm->backlight_caps.min_input_संकेत = AMDGPU_DM_DEFAULT_MIN_BACKLIGHT;
	dm->backlight_caps.max_input_संकेत = AMDGPU_DM_DEFAULT_MAX_BACKLIGHT;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक get_brightness_range(स्थिर काष्ठा amdgpu_dm_backlight_caps *caps,
				अचिन्हित *min, अचिन्हित *max)
अणु
	अगर (!caps)
		वापस 0;

	अगर (caps->aux_support) अणु
		// Firmware limits are in nits, DC API wants millinits.
		*max = 1000 * caps->aux_max_input_संकेत;
		*min = 1000 * caps->aux_min_input_संकेत;
	पूर्ण अन्यथा अणु
		// Firmware limits are 8-bit, PWM control is 16-bit.
		*max = 0x101 * caps->max_input_संकेत;
		*min = 0x101 * caps->min_input_संकेत;
	पूर्ण
	वापस 1;
पूर्ण

अटल u32 convert_brightness_from_user(स्थिर काष्ठा amdgpu_dm_backlight_caps *caps,
					uपूर्णांक32_t brightness)
अणु
	अचिन्हित min, max;

	अगर (!get_brightness_range(caps, &min, &max))
		वापस brightness;

	// Rescale 0..255 to min..max
	वापस min + DIV_ROUND_CLOSEST((max - min) * brightness,
				       AMDGPU_MAX_BL_LEVEL);
पूर्ण

अटल u32 convert_brightness_to_user(स्थिर काष्ठा amdgpu_dm_backlight_caps *caps,
				      uपूर्णांक32_t brightness)
अणु
	अचिन्हित min, max;

	अगर (!get_brightness_range(caps, &min, &max))
		वापस brightness;

	अगर (brightness < min)
		वापस 0;
	// Rescale min..max to 0..255
	वापस DIV_ROUND_CLOSEST(AMDGPU_MAX_BL_LEVEL * (brightness - min),
				 max - min);
पूर्ण

अटल पूर्णांक amdgpu_dm_backlight_update_status(काष्ठा backlight_device *bd)
अणु
	काष्ठा amdgpu_display_manager *dm = bl_get_data(bd);
	काष्ठा amdgpu_dm_backlight_caps caps;
	काष्ठा dc_link *link = शून्य;
	u32 brightness;
	bool rc;

	amdgpu_dm_update_backlight_caps(dm);
	caps = dm->backlight_caps;

	link = (काष्ठा dc_link *)dm->backlight_link;

	brightness = convert_brightness_from_user(&caps, bd->props.brightness);
	// Change brightness based on AUX property
	अगर (caps.aux_support)
		rc = dc_link_set_backlight_level_nits(link, true, brightness,
						      AUX_BL_DEFAULT_TRANSITION_TIME_MS);
	अन्यथा
		rc = dc_link_set_backlight_level(dm->backlight_link, brightness, 0);

	वापस rc ? 0 : 1;
पूर्ण

अटल पूर्णांक amdgpu_dm_backlight_get_brightness(काष्ठा backlight_device *bd)
अणु
	काष्ठा amdgpu_display_manager *dm = bl_get_data(bd);
	काष्ठा amdgpu_dm_backlight_caps caps;

	amdgpu_dm_update_backlight_caps(dm);
	caps = dm->backlight_caps;

	अगर (caps.aux_support) अणु
		काष्ठा dc_link *link = (काष्ठा dc_link *)dm->backlight_link;
		u32 avg, peak;
		bool rc;

		rc = dc_link_get_backlight_level_nits(link, &avg, &peak);
		अगर (!rc)
			वापस bd->props.brightness;
		वापस convert_brightness_to_user(&caps, avg);
	पूर्ण अन्यथा अणु
		पूर्णांक ret = dc_link_get_backlight_level(dm->backlight_link);

		अगर (ret == DC_ERROR_UNEXPECTED)
			वापस bd->props.brightness;
		वापस convert_brightness_to_user(&caps, ret);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा backlight_ops amdgpu_dm_backlight_ops = अणु
	.options = BL_CORE_SUSPENDRESUME,
	.get_brightness = amdgpu_dm_backlight_get_brightness,
	.update_status	= amdgpu_dm_backlight_update_status,
पूर्ण;

अटल व्योम
amdgpu_dm_रेजिस्टर_backlight_device(काष्ठा amdgpu_display_manager *dm)
अणु
	अक्षर bl_name[16];
	काष्ठा backlight_properties props = अणु 0 पूर्ण;

	amdgpu_dm_update_backlight_caps(dm);

	props.max_brightness = AMDGPU_MAX_BL_LEVEL;
	props.brightness = AMDGPU_MAX_BL_LEVEL;
	props.type = BACKLIGHT_RAW;

	snम_लिखो(bl_name, माप(bl_name), "amdgpu_bl%d",
		 adev_to_drm(dm->adev)->primary->index);

	dm->backlight_dev = backlight_device_रेजिस्टर(bl_name,
						      adev_to_drm(dm->adev)->dev,
						      dm,
						      &amdgpu_dm_backlight_ops,
						      &props);

	अगर (IS_ERR(dm->backlight_dev))
		DRM_ERROR("DM: Backlight registration failed!\n");
	अन्यथा
		DRM_DEBUG_DRIVER("DM: Registered Backlight device: %s\n", bl_name);
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक initialize_plane(काष्ठा amdgpu_display_manager *dm,
			    काष्ठा amdgpu_mode_info *mode_info, पूर्णांक plane_id,
			    क्रमागत drm_plane_type plane_type,
			    स्थिर काष्ठा dc_plane_cap *plane_cap)
अणु
	काष्ठा drm_plane *plane;
	अचिन्हित दीर्घ possible_crtcs;
	पूर्णांक ret = 0;

	plane = kzalloc(माप(काष्ठा drm_plane), GFP_KERNEL);
	अगर (!plane) अणु
		DRM_ERROR("KMS: Failed to allocate plane\n");
		वापस -ENOMEM;
	पूर्ण
	plane->type = plane_type;

	/*
	 * HACK: IGT tests expect that the primary plane क्रम a CRTC
	 * can only have one possible CRTC. Only expose support क्रम
	 * any CRTC अगर they're not going to be used as a primary plane
	 * क्रम a CRTC - like overlay or underlay planes.
	 */
	possible_crtcs = 1 << plane_id;
	अगर (plane_id >= dm->dc->caps.max_streams)
		possible_crtcs = 0xff;

	ret = amdgpu_dm_plane_init(dm, plane, possible_crtcs, plane_cap);

	अगर (ret) अणु
		DRM_ERROR("KMS: Failed to initialize plane\n");
		kमुक्त(plane);
		वापस ret;
	पूर्ण

	अगर (mode_info)
		mode_info->planes[plane_id] = plane;

	वापस ret;
पूर्ण


अटल व्योम रेजिस्टर_backlight_device(काष्ठा amdgpu_display_manager *dm,
				      काष्ठा dc_link *link)
अणु
#अगर defined(CONFIG_BACKLIGHT_CLASS_DEVICE) ||\
	defined(CONFIG_BACKLIGHT_CLASS_DEVICE_MODULE)

	अगर ((link->connector_संकेत & (SIGNAL_TYPE_EDP | SIGNAL_TYPE_LVDS)) &&
	    link->type != dc_connection_none) अणु
		/*
		 * Event अगर registration failed, we should जारी with
		 * DM initialization because not having a backlight control
		 * is better then a black screen.
		 */
		amdgpu_dm_रेजिस्टर_backlight_device(dm);

		अगर (dm->backlight_dev)
			dm->backlight_link = link;
	पूर्ण
#पूर्ण_अगर
पूर्ण


/*
 * In this architecture, the association
 * connector -> encoder -> crtc
 * id not really requried. The crtc and connector will hold the
 * display_index as an असलtraction to use with DAL component
 *
 * Returns 0 on success
 */
अटल पूर्णांक amdgpu_dm_initialize_drm_device(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_display_manager *dm = &adev->dm;
	पूर्णांक32_t i;
	काष्ठा amdgpu_dm_connector *aconnector = शून्य;
	काष्ठा amdgpu_encoder *aencoder = शून्य;
	काष्ठा amdgpu_mode_info *mode_info = &adev->mode_info;
	uपूर्णांक32_t link_cnt;
	पूर्णांक32_t primary_planes;
	क्रमागत dc_connection_type new_connection_type = dc_connection_none;
	स्थिर काष्ठा dc_plane_cap *plane;

	dm->display_indexes_num = dm->dc->caps.max_streams;
	/* Update the actual used number of crtc */
	adev->mode_info.num_crtc = adev->dm.display_indexes_num;

	link_cnt = dm->dc->caps.max_links;
	अगर (amdgpu_dm_mode_config_init(dm->adev)) अणु
		DRM_ERROR("DM: Failed to initialize mode config\n");
		वापस -EINVAL;
	पूर्ण

	/* There is one primary plane per CRTC */
	primary_planes = dm->dc->caps.max_streams;
	ASSERT(primary_planes <= AMDGPU_MAX_PLANES);

	/*
	 * Initialize primary planes, implicit planes क्रम legacy IOCTLS.
	 * Order is reversed to match iteration order in atomic check.
	 */
	क्रम (i = (primary_planes - 1); i >= 0; i--) अणु
		plane = &dm->dc->caps.planes[i];

		अगर (initialize_plane(dm, mode_info, i,
				     DRM_PLANE_TYPE_PRIMARY, plane)) अणु
			DRM_ERROR("KMS: Failed to initialize primary plane\n");
			जाओ fail;
		पूर्ण
	पूर्ण

	/*
	 * Initialize overlay planes, index starting after primary planes.
	 * These planes have a higher DRM index than the primary planes since
	 * they should be considered as having a higher z-order.
	 * Order is reversed to match iteration order in atomic check.
	 *
	 * Only support DCN क्रम now, and only expose one so we करोn't encourage
	 * userspace to use up all the pipes.
	 */
	क्रम (i = 0; i < dm->dc->caps.max_planes; ++i) अणु
		काष्ठा dc_plane_cap *plane = &dm->dc->caps.planes[i];

		अगर (plane->type != DC_PLANE_TYPE_DCN_UNIVERSAL)
			जारी;

		अगर (!plane->blends_with_above || !plane->blends_with_below)
			जारी;

		अगर (!plane->pixel_क्रमmat_support.argb8888)
			जारी;

		अगर (initialize_plane(dm, शून्य, primary_planes + i,
				     DRM_PLANE_TYPE_OVERLAY, plane)) अणु
			DRM_ERROR("KMS: Failed to initialize overlay plane\n");
			जाओ fail;
		पूर्ण

		/* Only create one overlay plane. */
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < dm->dc->caps.max_streams; i++)
		अगर (amdgpu_dm_crtc_init(dm, mode_info->planes[i], i)) अणु
			DRM_ERROR("KMS: Failed to initialize crtc\n");
			जाओ fail;
		पूर्ण

	/* loops over all connectors on the board */
	क्रम (i = 0; i < link_cnt; i++) अणु
		काष्ठा dc_link *link = शून्य;

		अगर (i > AMDGPU_DM_MAX_DISPLAY_INDEX) अणु
			DRM_ERROR(
				"KMS: Cannot support more than %d display indexes\n",
					AMDGPU_DM_MAX_DISPLAY_INDEX);
			जारी;
		पूर्ण

		aconnector = kzalloc(माप(*aconnector), GFP_KERNEL);
		अगर (!aconnector)
			जाओ fail;

		aencoder = kzalloc(माप(*aencoder), GFP_KERNEL);
		अगर (!aencoder)
			जाओ fail;

		अगर (amdgpu_dm_encoder_init(dm->ddev, aencoder, i)) अणु
			DRM_ERROR("KMS: Failed to initialize encoder\n");
			जाओ fail;
		पूर्ण

		अगर (amdgpu_dm_connector_init(dm, aconnector, i, aencoder)) अणु
			DRM_ERROR("KMS: Failed to initialize connector\n");
			जाओ fail;
		पूर्ण

		link = dc_get_link_at_index(dm->dc, i);

		अगर (!dc_link_detect_sink(link, &new_connection_type))
			DRM_ERROR("KMS: Failed to detect connector\n");

		अगर (aconnector->base.क्रमce && new_connection_type == dc_connection_none) अणु
			emulated_link_detect(link);
			amdgpu_dm_update_connector_after_detect(aconnector);

		पूर्ण अन्यथा अगर (dc_link_detect(link, DETECT_REASON_BOOT)) अणु
			amdgpu_dm_update_connector_after_detect(aconnector);
			रेजिस्टर_backlight_device(dm, link);
			अगर (amdgpu_dc_feature_mask & DC_PSR_MASK)
				amdgpu_dm_set_psr_caps(link);
		पूर्ण


	पूर्ण

	/* Software is initialized. Now we can रेजिस्टर पूर्णांकerrupt handlers. */
	चयन (adev->asic_type) अणु
#अगर defined(CONFIG_DRM_AMD_DC_SI)
	हाल CHIP_TAHITI:
	हाल CHIP_PITCAIRN:
	हाल CHIP_VERDE:
	हाल CHIP_OLAND:
		अगर (dce60_रेजिस्टर_irq_handlers(dm->adev)) अणु
			DRM_ERROR("DM: Failed to initialize IRQ\n");
			जाओ fail;
		पूर्ण
		अवरोध;
#पूर्ण_अगर
	हाल CHIP_BONAIRE:
	हाल CHIP_HAWAII:
	हाल CHIP_KAVERI:
	हाल CHIP_KABINI:
	हाल CHIP_MULLINS:
	हाल CHIP_TONGA:
	हाल CHIP_FIJI:
	हाल CHIP_CARRIZO:
	हाल CHIP_STONEY:
	हाल CHIP_POLARIS11:
	हाल CHIP_POLARIS10:
	हाल CHIP_POLARIS12:
	हाल CHIP_VEGAM:
	हाल CHIP_VEGA10:
	हाल CHIP_VEGA12:
	हाल CHIP_VEGA20:
		अगर (dce110_रेजिस्टर_irq_handlers(dm->adev)) अणु
			DRM_ERROR("DM: Failed to initialize IRQ\n");
			जाओ fail;
		पूर्ण
		अवरोध;
#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	हाल CHIP_RAVEN:
	हाल CHIP_NAVI12:
	हाल CHIP_NAVI10:
	हाल CHIP_NAVI14:
	हाल CHIP_RENOIR:
	हाल CHIP_SIENNA_CICHLID:
	हाल CHIP_NAVY_FLOUNDER:
	हाल CHIP_DIMGREY_CAVEFISH:
	हाल CHIP_VANGOGH:
		अगर (dcn10_रेजिस्टर_irq_handlers(dm->adev)) अणु
			DRM_ERROR("DM: Failed to initialize IRQ\n");
			जाओ fail;
		पूर्ण
		अवरोध;
#पूर्ण_अगर
	शेष:
		DRM_ERROR("Unsupported ASIC type: 0x%X\n", adev->asic_type);
		जाओ fail;
	पूर्ण

	वापस 0;
fail:
	kमुक्त(aencoder);
	kमुक्त(aconnector);

	वापस -EINVAL;
पूर्ण

अटल व्योम amdgpu_dm_destroy_drm_device(काष्ठा amdgpu_display_manager *dm)
अणु
	drm_mode_config_cleanup(dm->ddev);
	drm_atomic_निजी_obj_fini(&dm->atomic_obj);
	वापस;
पूर्ण

/******************************************************************************
 * amdgpu_display_funcs functions
 *****************************************************************************/

/*
 * dm_bandwidth_update - program display watermarks
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Calculate and program the display watermarks and line buffer allocation.
 */
अटल व्योम dm_bandwidth_update(काष्ठा amdgpu_device *adev)
अणु
	/* TODO: implement later */
पूर्ण

अटल स्थिर काष्ठा amdgpu_display_funcs dm_display_funcs = अणु
	.bandwidth_update = dm_bandwidth_update, /* called unconditionally */
	.vblank_get_counter = dm_vblank_get_counter,/* called unconditionally */
	.backlight_set_level = शून्य, /* never called क्रम DC */
	.backlight_get_level = शून्य, /* never called क्रम DC */
	.hpd_sense = शून्य,/* called unconditionally */
	.hpd_set_polarity = शून्य, /* called unconditionally */
	.hpd_get_gpio_reg = शून्य, /* VBIOS parsing. DAL करोes it. */
	.page_flip_get_scanoutpos =
		dm_crtc_get_scanoutpos,/* called unconditionally */
	.add_encoder = शून्य, /* VBIOS parsing. DAL करोes it. */
	.add_connector = शून्य, /* VBIOS parsing. DAL करोes it. */
पूर्ण;

#अगर defined(CONFIG_DEBUG_KERNEL_DC)

अटल sमाप_प्रकार s3_debug_store(काष्ठा device *device,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	पूर्णांक ret;
	पूर्णांक s3_state;
	काष्ठा drm_device *drm_dev = dev_get_drvdata(device);
	काष्ठा amdgpu_device *adev = drm_to_adev(drm_dev);

	ret = kstrtoपूर्णांक(buf, 0, &s3_state);

	अगर (ret == 0) अणु
		अगर (s3_state) अणु
			dm_resume(adev);
			drm_kms_helper_hotplug_event(adev_to_drm(adev));
		पूर्ण अन्यथा
			dm_suspend(adev);
	पूर्ण

	वापस ret == 0 ? count : 0;
पूर्ण

DEVICE_ATTR_WO(s3_debug);

#पूर्ण_अगर

अटल पूर्णांक dm_early_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	चयन (adev->asic_type) अणु
#अगर defined(CONFIG_DRM_AMD_DC_SI)
	हाल CHIP_TAHITI:
	हाल CHIP_PITCAIRN:
	हाल CHIP_VERDE:
		adev->mode_info.num_crtc = 6;
		adev->mode_info.num_hpd = 6;
		adev->mode_info.num_dig = 6;
		अवरोध;
	हाल CHIP_OLAND:
		adev->mode_info.num_crtc = 2;
		adev->mode_info.num_hpd = 2;
		adev->mode_info.num_dig = 2;
		अवरोध;
#पूर्ण_अगर
	हाल CHIP_BONAIRE:
	हाल CHIP_HAWAII:
		adev->mode_info.num_crtc = 6;
		adev->mode_info.num_hpd = 6;
		adev->mode_info.num_dig = 6;
		अवरोध;
	हाल CHIP_KAVERI:
		adev->mode_info.num_crtc = 4;
		adev->mode_info.num_hpd = 6;
		adev->mode_info.num_dig = 7;
		अवरोध;
	हाल CHIP_KABINI:
	हाल CHIP_MULLINS:
		adev->mode_info.num_crtc = 2;
		adev->mode_info.num_hpd = 6;
		adev->mode_info.num_dig = 6;
		अवरोध;
	हाल CHIP_FIJI:
	हाल CHIP_TONGA:
		adev->mode_info.num_crtc = 6;
		adev->mode_info.num_hpd = 6;
		adev->mode_info.num_dig = 7;
		अवरोध;
	हाल CHIP_CARRIZO:
		adev->mode_info.num_crtc = 3;
		adev->mode_info.num_hpd = 6;
		adev->mode_info.num_dig = 9;
		अवरोध;
	हाल CHIP_STONEY:
		adev->mode_info.num_crtc = 2;
		adev->mode_info.num_hpd = 6;
		adev->mode_info.num_dig = 9;
		अवरोध;
	हाल CHIP_POLARIS11:
	हाल CHIP_POLARIS12:
		adev->mode_info.num_crtc = 5;
		adev->mode_info.num_hpd = 5;
		adev->mode_info.num_dig = 5;
		अवरोध;
	हाल CHIP_POLARIS10:
	हाल CHIP_VEGAM:
		adev->mode_info.num_crtc = 6;
		adev->mode_info.num_hpd = 6;
		adev->mode_info.num_dig = 6;
		अवरोध;
	हाल CHIP_VEGA10:
	हाल CHIP_VEGA12:
	हाल CHIP_VEGA20:
		adev->mode_info.num_crtc = 6;
		adev->mode_info.num_hpd = 6;
		adev->mode_info.num_dig = 6;
		अवरोध;
#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	हाल CHIP_RAVEN:
	हाल CHIP_RENOIR:
	हाल CHIP_VANGOGH:
		adev->mode_info.num_crtc = 4;
		adev->mode_info.num_hpd = 4;
		adev->mode_info.num_dig = 4;
		अवरोध;
	हाल CHIP_NAVI10:
	हाल CHIP_NAVI12:
	हाल CHIP_SIENNA_CICHLID:
	हाल CHIP_NAVY_FLOUNDER:
		adev->mode_info.num_crtc = 6;
		adev->mode_info.num_hpd = 6;
		adev->mode_info.num_dig = 6;
		अवरोध;
	हाल CHIP_NAVI14:
	हाल CHIP_DIMGREY_CAVEFISH:
		adev->mode_info.num_crtc = 5;
		adev->mode_info.num_hpd = 5;
		adev->mode_info.num_dig = 5;
		अवरोध;
#पूर्ण_अगर
	शेष:
		DRM_ERROR("Unsupported ASIC type: 0x%X\n", adev->asic_type);
		वापस -EINVAL;
	पूर्ण

	amdgpu_dm_set_irq_funcs(adev);

	अगर (adev->mode_info.funcs == शून्य)
		adev->mode_info.funcs = &dm_display_funcs;

	/*
	 * Note: Do NOT change adev->audio_endpt_rreg and
	 * adev->audio_endpt_wreg because they are initialised in
	 * amdgpu_device_init()
	 */
#अगर defined(CONFIG_DEBUG_KERNEL_DC)
	device_create_file(
		adev_to_drm(adev)->dev,
		&dev_attr_s3_debug);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल bool modeset_required(काष्ठा drm_crtc_state *crtc_state,
			     काष्ठा dc_stream_state *new_stream,
			     काष्ठा dc_stream_state *old_stream)
अणु
	वापस crtc_state->active && drm_atomic_crtc_needs_modeset(crtc_state);
पूर्ण

अटल bool modereset_required(काष्ठा drm_crtc_state *crtc_state)
अणु
	वापस !crtc_state->active && drm_atomic_crtc_needs_modeset(crtc_state);
पूर्ण

अटल व्योम amdgpu_dm_encoder_destroy(काष्ठा drm_encoder *encoder)
अणु
	drm_encoder_cleanup(encoder);
	kमुक्त(encoder);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_funcs amdgpu_dm_encoder_funcs = अणु
	.destroy = amdgpu_dm_encoder_destroy,
पूर्ण;


अटल व्योम get_min_max_dc_plane_scaling(काष्ठा drm_device *dev,
					 काष्ठा drm_framebuffer *fb,
					 पूर्णांक *min_करोwnscale, पूर्णांक *max_upscale)
अणु
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा dc *dc = adev->dm.dc;
	/* Caps क्रम all supported planes are the same on DCE and DCN 1 - 3 */
	काष्ठा dc_plane_cap *plane_cap = &dc->caps.planes[0];

	चयन (fb->क्रमmat->क्रमmat) अणु
	हाल DRM_FORMAT_P010:
	हाल DRM_FORMAT_NV12:
	हाल DRM_FORMAT_NV21:
		*max_upscale = plane_cap->max_upscale_factor.nv12;
		*min_करोwnscale = plane_cap->max_करोwnscale_factor.nv12;
		अवरोध;

	हाल DRM_FORMAT_XRGB16161616F:
	हाल DRM_FORMAT_ARGB16161616F:
	हाल DRM_FORMAT_XBGR16161616F:
	हाल DRM_FORMAT_ABGR16161616F:
		*max_upscale = plane_cap->max_upscale_factor.fp16;
		*min_करोwnscale = plane_cap->max_करोwnscale_factor.fp16;
		अवरोध;

	शेष:
		*max_upscale = plane_cap->max_upscale_factor.argb8888;
		*min_करोwnscale = plane_cap->max_करोwnscale_factor.argb8888;
		अवरोध;
	पूर्ण

	/*
	 * A factor of 1 in the plane_cap means to not allow scaling, ie. use a
	 * scaling factor of 1.0 == 1000 units.
	 */
	अगर (*max_upscale == 1)
		*max_upscale = 1000;

	अगर (*min_करोwnscale == 1)
		*min_करोwnscale = 1000;
पूर्ण


अटल पूर्णांक fill_dc_scaling_info(स्थिर काष्ठा drm_plane_state *state,
				काष्ठा dc_scaling_info *scaling_info)
अणु
	पूर्णांक scale_w, scale_h, min_करोwnscale, max_upscale;

	स_रखो(scaling_info, 0, माप(*scaling_info));

	/* Source is fixed 16.16 but we ignore mantissa क्रम now... */
	scaling_info->src_rect.x = state->src_x >> 16;
	scaling_info->src_rect.y = state->src_y >> 16;

	/*
	 * For reasons we करोn't (yet) fully understand a non-zero
	 * src_y coordinate पूर्णांकo an NV12 buffer can cause a
	 * प्रणाली hang. To aव्योम hangs (and maybe be overly cautious)
	 * let's reject both non-zero src_x and src_y.
	 *
	 * We currently know of only one use-हाल to reproduce a
	 * scenario with non-zero src_x and src_y क्रम NV12, which
	 * is to gesture the YouTube Android app पूर्णांकo full screen
	 * on ChromeOS.
	 */
	अगर (state->fb &&
	    state->fb->क्रमmat->क्रमmat == DRM_FORMAT_NV12 &&
	    (scaling_info->src_rect.x != 0 ||
	     scaling_info->src_rect.y != 0))
		वापस -EINVAL;

	scaling_info->src_rect.width = state->src_w >> 16;
	अगर (scaling_info->src_rect.width == 0)
		वापस -EINVAL;

	scaling_info->src_rect.height = state->src_h >> 16;
	अगर (scaling_info->src_rect.height == 0)
		वापस -EINVAL;

	scaling_info->dst_rect.x = state->crtc_x;
	scaling_info->dst_rect.y = state->crtc_y;

	अगर (state->crtc_w == 0)
		वापस -EINVAL;

	scaling_info->dst_rect.width = state->crtc_w;

	अगर (state->crtc_h == 0)
		वापस -EINVAL;

	scaling_info->dst_rect.height = state->crtc_h;

	/* DRM करोesn't specअगरy clipping on destination output. */
	scaling_info->clip_rect = scaling_info->dst_rect;

	/* Validate scaling per-क्रमmat with DC plane caps */
	अगर (state->plane && state->plane->dev && state->fb) अणु
		get_min_max_dc_plane_scaling(state->plane->dev, state->fb,
					     &min_करोwnscale, &max_upscale);
	पूर्ण अन्यथा अणु
		min_करोwnscale = 250;
		max_upscale = 16000;
	पूर्ण

	scale_w = scaling_info->dst_rect.width * 1000 /
		  scaling_info->src_rect.width;

	अगर (scale_w < min_करोwnscale || scale_w > max_upscale)
		वापस -EINVAL;

	scale_h = scaling_info->dst_rect.height * 1000 /
		  scaling_info->src_rect.height;

	अगर (scale_h < min_करोwnscale || scale_h > max_upscale)
		वापस -EINVAL;

	/*
	 * The "scaling_quality" can be ignored क्रम now, quality = 0 has DC
	 * assume reasonable शेषs based on the क्रमmat.
	 */

	वापस 0;
पूर्ण

अटल व्योम
fill_gfx8_tiling_info_from_flags(जोड़ dc_tiling_info *tiling_info,
				 uपूर्णांक64_t tiling_flags)
अणु
	/* Fill GFX8 params */
	अगर (AMDGPU_TILING_GET(tiling_flags, ARRAY_MODE) == DC_ARRAY_2D_TILED_THIN1) अणु
		अचिन्हित पूर्णांक bankw, bankh, mtaspect, tile_split, num_banks;

		bankw = AMDGPU_TILING_GET(tiling_flags, BANK_WIDTH);
		bankh = AMDGPU_TILING_GET(tiling_flags, BANK_HEIGHT);
		mtaspect = AMDGPU_TILING_GET(tiling_flags, MACRO_TILE_ASPECT);
		tile_split = AMDGPU_TILING_GET(tiling_flags, TILE_SPLIT);
		num_banks = AMDGPU_TILING_GET(tiling_flags, NUM_BANKS);

		/* XXX fix me क्रम VI */
		tiling_info->gfx8.num_banks = num_banks;
		tiling_info->gfx8.array_mode =
				DC_ARRAY_2D_TILED_THIN1;
		tiling_info->gfx8.tile_split = tile_split;
		tiling_info->gfx8.bank_width = bankw;
		tiling_info->gfx8.bank_height = bankh;
		tiling_info->gfx8.tile_aspect = mtaspect;
		tiling_info->gfx8.tile_mode =
				DC_ADDR_SURF_MICRO_TILING_DISPLAY;
	पूर्ण अन्यथा अगर (AMDGPU_TILING_GET(tiling_flags, ARRAY_MODE)
			== DC_ARRAY_1D_TILED_THIN1) अणु
		tiling_info->gfx8.array_mode = DC_ARRAY_1D_TILED_THIN1;
	पूर्ण

	tiling_info->gfx8.pipe_config =
			AMDGPU_TILING_GET(tiling_flags, PIPE_CONFIG);
पूर्ण

अटल व्योम
fill_gfx9_tiling_info_from_device(स्थिर काष्ठा amdgpu_device *adev,
				  जोड़ dc_tiling_info *tiling_info)
अणु
	tiling_info->gfx9.num_pipes =
		adev->gfx.config.gb_addr_config_fields.num_pipes;
	tiling_info->gfx9.num_banks =
		adev->gfx.config.gb_addr_config_fields.num_banks;
	tiling_info->gfx9.pipe_पूर्णांकerleave =
		adev->gfx.config.gb_addr_config_fields.pipe_पूर्णांकerleave_size;
	tiling_info->gfx9.num_shader_engines =
		adev->gfx.config.gb_addr_config_fields.num_se;
	tiling_info->gfx9.max_compressed_frags =
		adev->gfx.config.gb_addr_config_fields.max_compress_frags;
	tiling_info->gfx9.num_rb_per_se =
		adev->gfx.config.gb_addr_config_fields.num_rb_per_se;
	tiling_info->gfx9.shaderEnable = 1;
	अगर (adev->asic_type == CHIP_SIENNA_CICHLID ||
	    adev->asic_type == CHIP_NAVY_FLOUNDER ||
	    adev->asic_type == CHIP_DIMGREY_CAVEFISH ||
	    adev->asic_type == CHIP_VANGOGH)
		tiling_info->gfx9.num_pkrs = adev->gfx.config.gb_addr_config_fields.num_pkrs;
पूर्ण

अटल पूर्णांक
validate_dcc(काष्ठा amdgpu_device *adev,
	     स्थिर क्रमागत surface_pixel_क्रमmat क्रमmat,
	     स्थिर क्रमागत dc_rotation_angle rotation,
	     स्थिर जोड़ dc_tiling_info *tiling_info,
	     स्थिर काष्ठा dc_plane_dcc_param *dcc,
	     स्थिर काष्ठा dc_plane_address *address,
	     स्थिर काष्ठा plane_size *plane_size)
अणु
	काष्ठा dc *dc = adev->dm.dc;
	काष्ठा dc_dcc_surface_param input;
	काष्ठा dc_surface_dcc_cap output;

	स_रखो(&input, 0, माप(input));
	स_रखो(&output, 0, माप(output));

	अगर (!dcc->enable)
		वापस 0;

	अगर (क्रमmat >= SURFACE_PIXEL_FORMAT_VIDEO_BEGIN ||
	    !dc->cap_funcs.get_dcc_compression_cap)
		वापस -EINVAL;

	input.क्रमmat = क्रमmat;
	input.surface_size.width = plane_size->surface_size.width;
	input.surface_size.height = plane_size->surface_size.height;
	input.swizzle_mode = tiling_info->gfx9.swizzle;

	अगर (rotation == ROTATION_ANGLE_0 || rotation == ROTATION_ANGLE_180)
		input.scan = SCAN_सूचीECTION_HORIZONTAL;
	अन्यथा अगर (rotation == ROTATION_ANGLE_90 || rotation == ROTATION_ANGLE_270)
		input.scan = SCAN_सूचीECTION_VERTICAL;

	अगर (!dc->cap_funcs.get_dcc_compression_cap(dc, &input, &output))
		वापस -EINVAL;

	अगर (!output.capable)
		वापस -EINVAL;

	अगर (dcc->independent_64b_blks == 0 &&
	    output.grph.rgb.independent_64b_blks != 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल bool
modअगरier_has_dcc(uपूर्णांक64_t modअगरier)
अणु
	वापस IS_AMD_FMT_MOD(modअगरier) && AMD_FMT_MOD_GET(DCC, modअगरier);
पूर्ण

अटल अचिन्हित
modअगरier_gfx9_swizzle_mode(uपूर्णांक64_t modअगरier)
अणु
	अगर (modअगरier == DRM_FORMAT_MOD_LINEAR)
		वापस 0;

	वापस AMD_FMT_MOD_GET(TILE, modअगरier);
पूर्ण

अटल स्थिर काष्ठा drm_क्रमmat_info *
amd_get_क्रमmat_info(स्थिर काष्ठा drm_mode_fb_cmd2 *cmd)
अणु
	वापस amdgpu_lookup_क्रमmat_info(cmd->pixel_क्रमmat, cmd->modअगरier[0]);
पूर्ण

अटल व्योम
fill_gfx9_tiling_info_from_modअगरier(स्थिर काष्ठा amdgpu_device *adev,
				    जोड़ dc_tiling_info *tiling_info,
				    uपूर्णांक64_t modअगरier)
अणु
	अचिन्हित पूर्णांक mod_bank_xor_bits = AMD_FMT_MOD_GET(BANK_XOR_BITS, modअगरier);
	अचिन्हित पूर्णांक mod_pipe_xor_bits = AMD_FMT_MOD_GET(PIPE_XOR_BITS, modअगरier);
	अचिन्हित पूर्णांक pkrs_log2 = AMD_FMT_MOD_GET(PACKERS, modअगरier);
	अचिन्हित पूर्णांक pipes_log2 = min(4u, mod_pipe_xor_bits);

	fill_gfx9_tiling_info_from_device(adev, tiling_info);

	अगर (!IS_AMD_FMT_MOD(modअगरier))
		वापस;

	tiling_info->gfx9.num_pipes = 1u << pipes_log2;
	tiling_info->gfx9.num_shader_engines = 1u << (mod_pipe_xor_bits - pipes_log2);

	अगर (adev->family >= AMDGPU_FAMILY_NV) अणु
		tiling_info->gfx9.num_pkrs = 1u << pkrs_log2;
	पूर्ण अन्यथा अणु
		tiling_info->gfx9.num_banks = 1u << mod_bank_xor_bits;

		/* क्रम DCC we know it isn't rb aligned, so rb_per_se doesn't matter. */
	पूर्ण
पूर्ण

क्रमागत dm_micro_swizzle अणु
	MICRO_SWIZZLE_Z = 0,
	MICRO_SWIZZLE_S = 1,
	MICRO_SWIZZLE_D = 2,
	MICRO_SWIZZLE_R = 3
पूर्ण;

अटल bool dm_plane_क्रमmat_mod_supported(काष्ठा drm_plane *plane,
					  uपूर्णांक32_t क्रमmat,
					  uपूर्णांक64_t modअगरier)
अणु
	काष्ठा amdgpu_device *adev = drm_to_adev(plane->dev);
	स्थिर काष्ठा drm_क्रमmat_info *info = drm_क्रमmat_info(क्रमmat);
	पूर्णांक i;

	क्रमागत dm_micro_swizzle microtile = modअगरier_gfx9_swizzle_mode(modअगरier) & 3;

	अगर (!info)
		वापस false;

	/*
	 * We always have to allow these modअगरiers:
	 * 1. Core DRM checks क्रम LINEAR support अगर userspace करोes not provide modअगरiers.
	 * 2. Not passing any modअगरiers is the same as explicitly passing INVALID.
	 */
	अगर (modअगरier == DRM_FORMAT_MOD_LINEAR ||
	    modअगरier == DRM_FORMAT_MOD_INVALID) अणु
		वापस true;
	पूर्ण

	/* Check that the modअगरier is on the list of the plane's supported modअगरiers. */
	क्रम (i = 0; i < plane->modअगरier_count; i++) अणु
		अगर (modअगरier == plane->modअगरiers[i])
			अवरोध;
	पूर्ण
	अगर (i == plane->modअगरier_count)
		वापस false;

	/*
	 * For D swizzle the canonical modअगरier depends on the bpp, so check
	 * it here.
	 */
	अगर (AMD_FMT_MOD_GET(TILE_VERSION, modअगरier) == AMD_FMT_MOD_TILE_VER_GFX9 &&
	    adev->family >= AMDGPU_FAMILY_NV) अणु
		अगर (microtile == MICRO_SWIZZLE_D && info->cpp[0] == 4)
			वापस false;
	पूर्ण

	अगर (adev->family >= AMDGPU_FAMILY_RV && microtile == MICRO_SWIZZLE_D &&
	    info->cpp[0] < 8)
		वापस false;

	अगर (modअगरier_has_dcc(modअगरier)) अणु
		/* Per radeonsi comments 16/64 bpp are more complicated. */
		अगर (info->cpp[0] != 4)
			वापस false;
		/* We support multi-planar क्रमmats, but not when combined with
		 * additional DCC metadata planes. */
		अगर (info->num_planes > 1)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम
add_modअगरier(uपूर्णांक64_t **mods, uपूर्णांक64_t *size, uपूर्णांक64_t *cap, uपूर्णांक64_t mod)
अणु
	अगर (!*mods)
		वापस;

	अगर (*cap - *size < 1) अणु
		uपूर्णांक64_t new_cap = *cap * 2;
		uपूर्णांक64_t *new_mods = kदो_स्मृति(new_cap * माप(uपूर्णांक64_t), GFP_KERNEL);

		अगर (!new_mods) अणु
			kमुक्त(*mods);
			*mods = शून्य;
			वापस;
		पूर्ण

		स_नकल(new_mods, *mods, माप(uपूर्णांक64_t) * *size);
		kमुक्त(*mods);
		*mods = new_mods;
		*cap = new_cap;
	पूर्ण

	(*mods)[*size] = mod;
	*size += 1;
पूर्ण

अटल व्योम
add_gfx9_modअगरiers(स्थिर काष्ठा amdgpu_device *adev,
		   uपूर्णांक64_t **mods, uपूर्णांक64_t *size, uपूर्णांक64_t *capacity)
अणु
	पूर्णांक pipes = ilog2(adev->gfx.config.gb_addr_config_fields.num_pipes);
	पूर्णांक pipe_xor_bits = min(8, pipes +
				ilog2(adev->gfx.config.gb_addr_config_fields.num_se));
	पूर्णांक bank_xor_bits = min(8 - pipe_xor_bits,
				ilog2(adev->gfx.config.gb_addr_config_fields.num_banks));
	पूर्णांक rb = ilog2(adev->gfx.config.gb_addr_config_fields.num_se) +
		 ilog2(adev->gfx.config.gb_addr_config_fields.num_rb_per_se);


	अगर (adev->family == AMDGPU_FAMILY_RV) अणु
		/* Raven2 and later */
		bool has_स्थिरant_encode = adev->asic_type > CHIP_RAVEN || adev->बाह्यal_rev_id >= 0x81;

		/*
		 * No _D DCC swizzles yet because we only allow 32bpp, which
		 * करोesn't support _D on DCN
		 */

		अगर (has_स्थिरant_encode) अणु
			add_modअगरier(mods, size, capacity, AMD_FMT_MOD |
				    AMD_FMT_MOD_SET(TILE, AMD_FMT_MOD_TILE_GFX9_64K_S_X) |
				    AMD_FMT_MOD_SET(TILE_VERSION, AMD_FMT_MOD_TILE_VER_GFX9) |
				    AMD_FMT_MOD_SET(PIPE_XOR_BITS, pipe_xor_bits) |
				    AMD_FMT_MOD_SET(BANK_XOR_BITS, bank_xor_bits) |
				    AMD_FMT_MOD_SET(DCC, 1) |
				    AMD_FMT_MOD_SET(DCC_INDEPENDENT_64B, 1) |
				    AMD_FMT_MOD_SET(DCC_MAX_COMPRESSED_BLOCK, AMD_FMT_MOD_DCC_BLOCK_64B) |
				    AMD_FMT_MOD_SET(DCC_CONSTANT_ENCODE, 1));
		पूर्ण

		add_modअगरier(mods, size, capacity, AMD_FMT_MOD |
			    AMD_FMT_MOD_SET(TILE, AMD_FMT_MOD_TILE_GFX9_64K_S_X) |
			    AMD_FMT_MOD_SET(TILE_VERSION, AMD_FMT_MOD_TILE_VER_GFX9) |
			    AMD_FMT_MOD_SET(PIPE_XOR_BITS, pipe_xor_bits) |
			    AMD_FMT_MOD_SET(BANK_XOR_BITS, bank_xor_bits) |
			    AMD_FMT_MOD_SET(DCC, 1) |
			    AMD_FMT_MOD_SET(DCC_INDEPENDENT_64B, 1) |
			    AMD_FMT_MOD_SET(DCC_MAX_COMPRESSED_BLOCK, AMD_FMT_MOD_DCC_BLOCK_64B) |
			    AMD_FMT_MOD_SET(DCC_CONSTANT_ENCODE, 0));

		अगर (has_स्थिरant_encode) अणु
			add_modअगरier(mods, size, capacity, AMD_FMT_MOD |
				    AMD_FMT_MOD_SET(TILE, AMD_FMT_MOD_TILE_GFX9_64K_S_X) |
				    AMD_FMT_MOD_SET(TILE_VERSION, AMD_FMT_MOD_TILE_VER_GFX9) |
				    AMD_FMT_MOD_SET(PIPE_XOR_BITS, pipe_xor_bits) |
				    AMD_FMT_MOD_SET(BANK_XOR_BITS, bank_xor_bits) |
				    AMD_FMT_MOD_SET(DCC, 1) |
				    AMD_FMT_MOD_SET(DCC_RETILE, 1) |
				    AMD_FMT_MOD_SET(DCC_INDEPENDENT_64B, 1) |
				    AMD_FMT_MOD_SET(DCC_MAX_COMPRESSED_BLOCK, AMD_FMT_MOD_DCC_BLOCK_64B) |

				    AMD_FMT_MOD_SET(DCC_CONSTANT_ENCODE, 1) |
				    AMD_FMT_MOD_SET(RB, rb) |
				    AMD_FMT_MOD_SET(PIPE, pipes));
		पूर्ण

		add_modअगरier(mods, size, capacity, AMD_FMT_MOD |
			    AMD_FMT_MOD_SET(TILE, AMD_FMT_MOD_TILE_GFX9_64K_S_X) |
			    AMD_FMT_MOD_SET(TILE_VERSION, AMD_FMT_MOD_TILE_VER_GFX9) |
			    AMD_FMT_MOD_SET(PIPE_XOR_BITS, pipe_xor_bits) |
			    AMD_FMT_MOD_SET(BANK_XOR_BITS, bank_xor_bits) |
			    AMD_FMT_MOD_SET(DCC, 1) |
			    AMD_FMT_MOD_SET(DCC_RETILE, 1) |
			    AMD_FMT_MOD_SET(DCC_INDEPENDENT_64B, 1) |
			    AMD_FMT_MOD_SET(DCC_MAX_COMPRESSED_BLOCK, AMD_FMT_MOD_DCC_BLOCK_64B) |
			    AMD_FMT_MOD_SET(DCC_CONSTANT_ENCODE, 0) |
			    AMD_FMT_MOD_SET(RB, rb) |
			    AMD_FMT_MOD_SET(PIPE, pipes));
	पूर्ण

	/*
	 * Only supported क्रम 64bpp on Raven, will be filtered on क्रमmat in
	 * dm_plane_क्रमmat_mod_supported.
	 */
	add_modअगरier(mods, size, capacity, AMD_FMT_MOD |
		    AMD_FMT_MOD_SET(TILE, AMD_FMT_MOD_TILE_GFX9_64K_D_X) |
		    AMD_FMT_MOD_SET(TILE_VERSION, AMD_FMT_MOD_TILE_VER_GFX9) |
		    AMD_FMT_MOD_SET(PIPE_XOR_BITS, pipe_xor_bits) |
		    AMD_FMT_MOD_SET(BANK_XOR_BITS, bank_xor_bits));

	अगर (adev->family == AMDGPU_FAMILY_RV) अणु
		add_modअगरier(mods, size, capacity, AMD_FMT_MOD |
			    AMD_FMT_MOD_SET(TILE, AMD_FMT_MOD_TILE_GFX9_64K_S_X) |
			    AMD_FMT_MOD_SET(TILE_VERSION, AMD_FMT_MOD_TILE_VER_GFX9) |
			    AMD_FMT_MOD_SET(PIPE_XOR_BITS, pipe_xor_bits) |
			    AMD_FMT_MOD_SET(BANK_XOR_BITS, bank_xor_bits));
	पूर्ण

	/*
	 * Only supported क्रम 64bpp on Raven, will be filtered on क्रमmat in
	 * dm_plane_क्रमmat_mod_supported.
	 */
	add_modअगरier(mods, size, capacity, AMD_FMT_MOD |
		    AMD_FMT_MOD_SET(TILE, AMD_FMT_MOD_TILE_GFX9_64K_D) |
		    AMD_FMT_MOD_SET(TILE_VERSION, AMD_FMT_MOD_TILE_VER_GFX9));

	अगर (adev->family == AMDGPU_FAMILY_RV) अणु
		add_modअगरier(mods, size, capacity, AMD_FMT_MOD |
			    AMD_FMT_MOD_SET(TILE, AMD_FMT_MOD_TILE_GFX9_64K_S) |
			    AMD_FMT_MOD_SET(TILE_VERSION, AMD_FMT_MOD_TILE_VER_GFX9));
	पूर्ण
पूर्ण

अटल व्योम
add_gfx10_1_modअगरiers(स्थिर काष्ठा amdgpu_device *adev,
		      uपूर्णांक64_t **mods, uपूर्णांक64_t *size, uपूर्णांक64_t *capacity)
अणु
	पूर्णांक pipe_xor_bits = ilog2(adev->gfx.config.gb_addr_config_fields.num_pipes);

	add_modअगरier(mods, size, capacity, AMD_FMT_MOD |
		    AMD_FMT_MOD_SET(TILE, AMD_FMT_MOD_TILE_GFX9_64K_R_X) |
		    AMD_FMT_MOD_SET(TILE_VERSION, AMD_FMT_MOD_TILE_VER_GFX10) |
		    AMD_FMT_MOD_SET(PIPE_XOR_BITS, pipe_xor_bits) |
		    AMD_FMT_MOD_SET(DCC, 1) |
		    AMD_FMT_MOD_SET(DCC_CONSTANT_ENCODE, 1) |
		    AMD_FMT_MOD_SET(DCC_INDEPENDENT_64B, 1) |
		    AMD_FMT_MOD_SET(DCC_MAX_COMPRESSED_BLOCK, AMD_FMT_MOD_DCC_BLOCK_64B));

	add_modअगरier(mods, size, capacity, AMD_FMT_MOD |
		    AMD_FMT_MOD_SET(TILE, AMD_FMT_MOD_TILE_GFX9_64K_R_X) |
		    AMD_FMT_MOD_SET(TILE_VERSION, AMD_FMT_MOD_TILE_VER_GFX10) |
		    AMD_FMT_MOD_SET(PIPE_XOR_BITS, pipe_xor_bits) |
		    AMD_FMT_MOD_SET(DCC, 1) |
		    AMD_FMT_MOD_SET(DCC_RETILE, 1) |
		    AMD_FMT_MOD_SET(DCC_CONSTANT_ENCODE, 1) |
		    AMD_FMT_MOD_SET(DCC_INDEPENDENT_64B, 1) |
		    AMD_FMT_MOD_SET(DCC_MAX_COMPRESSED_BLOCK, AMD_FMT_MOD_DCC_BLOCK_64B));

	add_modअगरier(mods, size, capacity, AMD_FMT_MOD |
		    AMD_FMT_MOD_SET(TILE, AMD_FMT_MOD_TILE_GFX9_64K_R_X) |
		    AMD_FMT_MOD_SET(TILE_VERSION, AMD_FMT_MOD_TILE_VER_GFX10) |
		    AMD_FMT_MOD_SET(PIPE_XOR_BITS, pipe_xor_bits));

	add_modअगरier(mods, size, capacity, AMD_FMT_MOD |
		    AMD_FMT_MOD_SET(TILE, AMD_FMT_MOD_TILE_GFX9_64K_S_X) |
		    AMD_FMT_MOD_SET(TILE_VERSION, AMD_FMT_MOD_TILE_VER_GFX10) |
		    AMD_FMT_MOD_SET(PIPE_XOR_BITS, pipe_xor_bits));


	/* Only supported क्रम 64bpp, will be filtered in dm_plane_क्रमmat_mod_supported */
	add_modअगरier(mods, size, capacity, AMD_FMT_MOD |
		    AMD_FMT_MOD_SET(TILE, AMD_FMT_MOD_TILE_GFX9_64K_D) |
		    AMD_FMT_MOD_SET(TILE_VERSION, AMD_FMT_MOD_TILE_VER_GFX9));

	add_modअगरier(mods, size, capacity, AMD_FMT_MOD |
		    AMD_FMT_MOD_SET(TILE, AMD_FMT_MOD_TILE_GFX9_64K_S) |
		    AMD_FMT_MOD_SET(TILE_VERSION, AMD_FMT_MOD_TILE_VER_GFX9));
पूर्ण

अटल व्योम
add_gfx10_3_modअगरiers(स्थिर काष्ठा amdgpu_device *adev,
		      uपूर्णांक64_t **mods, uपूर्णांक64_t *size, uपूर्णांक64_t *capacity)
अणु
	पूर्णांक pipe_xor_bits = ilog2(adev->gfx.config.gb_addr_config_fields.num_pipes);
	पूर्णांक pkrs = ilog2(adev->gfx.config.gb_addr_config_fields.num_pkrs);

	add_modअगरier(mods, size, capacity, AMD_FMT_MOD |
		    AMD_FMT_MOD_SET(TILE, AMD_FMT_MOD_TILE_GFX9_64K_R_X) |
		    AMD_FMT_MOD_SET(TILE_VERSION, AMD_FMT_MOD_TILE_VER_GFX10_RBPLUS) |
		    AMD_FMT_MOD_SET(PIPE_XOR_BITS, pipe_xor_bits) |
		    AMD_FMT_MOD_SET(PACKERS, pkrs) |
		    AMD_FMT_MOD_SET(DCC, 1) |
		    AMD_FMT_MOD_SET(DCC_CONSTANT_ENCODE, 1) |
		    AMD_FMT_MOD_SET(DCC_INDEPENDENT_64B, 1) |
		    AMD_FMT_MOD_SET(DCC_INDEPENDENT_128B, 1) |
		    AMD_FMT_MOD_SET(DCC_MAX_COMPRESSED_BLOCK, AMD_FMT_MOD_DCC_BLOCK_64B));

	add_modअगरier(mods, size, capacity, AMD_FMT_MOD |
		    AMD_FMT_MOD_SET(TILE, AMD_FMT_MOD_TILE_GFX9_64K_R_X) |
		    AMD_FMT_MOD_SET(TILE_VERSION, AMD_FMT_MOD_TILE_VER_GFX10_RBPLUS) |
		    AMD_FMT_MOD_SET(PIPE_XOR_BITS, pipe_xor_bits) |
		    AMD_FMT_MOD_SET(PACKERS, pkrs) |
		    AMD_FMT_MOD_SET(DCC, 1) |
		    AMD_FMT_MOD_SET(DCC_RETILE, 1) |
		    AMD_FMT_MOD_SET(DCC_CONSTANT_ENCODE, 1) |
		    AMD_FMT_MOD_SET(DCC_INDEPENDENT_64B, 1) |
		    AMD_FMT_MOD_SET(DCC_INDEPENDENT_128B, 1) |
		    AMD_FMT_MOD_SET(DCC_MAX_COMPRESSED_BLOCK, AMD_FMT_MOD_DCC_BLOCK_64B));

	add_modअगरier(mods, size, capacity, AMD_FMT_MOD |
		    AMD_FMT_MOD_SET(TILE, AMD_FMT_MOD_TILE_GFX9_64K_R_X) |
		    AMD_FMT_MOD_SET(TILE_VERSION, AMD_FMT_MOD_TILE_VER_GFX10_RBPLUS) |
		    AMD_FMT_MOD_SET(PIPE_XOR_BITS, pipe_xor_bits) |
		    AMD_FMT_MOD_SET(PACKERS, pkrs));

	add_modअगरier(mods, size, capacity, AMD_FMT_MOD |
		    AMD_FMT_MOD_SET(TILE, AMD_FMT_MOD_TILE_GFX9_64K_S_X) |
		    AMD_FMT_MOD_SET(TILE_VERSION, AMD_FMT_MOD_TILE_VER_GFX10_RBPLUS) |
		    AMD_FMT_MOD_SET(PIPE_XOR_BITS, pipe_xor_bits) |
		    AMD_FMT_MOD_SET(PACKERS, pkrs));

	/* Only supported क्रम 64bpp, will be filtered in dm_plane_क्रमmat_mod_supported */
	add_modअगरier(mods, size, capacity, AMD_FMT_MOD |
		    AMD_FMT_MOD_SET(TILE, AMD_FMT_MOD_TILE_GFX9_64K_D) |
		    AMD_FMT_MOD_SET(TILE_VERSION, AMD_FMT_MOD_TILE_VER_GFX9));

	add_modअगरier(mods, size, capacity, AMD_FMT_MOD |
		    AMD_FMT_MOD_SET(TILE, AMD_FMT_MOD_TILE_GFX9_64K_S) |
		    AMD_FMT_MOD_SET(TILE_VERSION, AMD_FMT_MOD_TILE_VER_GFX9));
पूर्ण

अटल पूर्णांक
get_plane_modअगरiers(स्थिर काष्ठा amdgpu_device *adev, अचिन्हित पूर्णांक plane_type, uपूर्णांक64_t **mods)
अणु
	uपूर्णांक64_t size = 0, capacity = 128;
	*mods = शून्य;

	/* We have not hooked up any pre-GFX9 modअगरiers. */
	अगर (adev->family < AMDGPU_FAMILY_AI)
		वापस 0;

	*mods = kदो_स्मृति(capacity * माप(uपूर्णांक64_t), GFP_KERNEL);

	अगर (plane_type == DRM_PLANE_TYPE_CURSOR) अणु
		add_modअगरier(mods, &size, &capacity, DRM_FORMAT_MOD_LINEAR);
		add_modअगरier(mods, &size, &capacity, DRM_FORMAT_MOD_INVALID);
		वापस *mods ? 0 : -ENOMEM;
	पूर्ण

	चयन (adev->family) अणु
	हाल AMDGPU_FAMILY_AI:
	हाल AMDGPU_FAMILY_RV:
		add_gfx9_modअगरiers(adev, mods, &size, &capacity);
		अवरोध;
	हाल AMDGPU_FAMILY_NV:
	हाल AMDGPU_FAMILY_VGH:
		अगर (adev->asic_type >= CHIP_SIENNA_CICHLID)
			add_gfx10_3_modअगरiers(adev, mods, &size, &capacity);
		अन्यथा
			add_gfx10_1_modअगरiers(adev, mods, &size, &capacity);
		अवरोध;
	पूर्ण

	add_modअगरier(mods, &size, &capacity, DRM_FORMAT_MOD_LINEAR);

	/* INVALID marks the end of the list. */
	add_modअगरier(mods, &size, &capacity, DRM_FORMAT_MOD_INVALID);

	अगर (!*mods)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक
fill_gfx9_plane_attributes_from_modअगरiers(काष्ठा amdgpu_device *adev,
					  स्थिर काष्ठा amdgpu_framebuffer *afb,
					  स्थिर क्रमागत surface_pixel_क्रमmat क्रमmat,
					  स्थिर क्रमागत dc_rotation_angle rotation,
					  स्थिर काष्ठा plane_size *plane_size,
					  जोड़ dc_tiling_info *tiling_info,
					  काष्ठा dc_plane_dcc_param *dcc,
					  काष्ठा dc_plane_address *address,
					  स्थिर bool क्रमce_disable_dcc)
अणु
	स्थिर uपूर्णांक64_t modअगरier = afb->base.modअगरier;
	पूर्णांक ret;

	fill_gfx9_tiling_info_from_modअगरier(adev, tiling_info, modअगरier);
	tiling_info->gfx9.swizzle = modअगरier_gfx9_swizzle_mode(modअगरier);

	अगर (modअगरier_has_dcc(modअगरier) && !क्रमce_disable_dcc) अणु
		uपूर्णांक64_t dcc_address = afb->address + afb->base.offsets[1];

		dcc->enable = 1;
		dcc->meta_pitch = afb->base.pitches[1];
		dcc->independent_64b_blks = AMD_FMT_MOD_GET(DCC_INDEPENDENT_64B, modअगरier);

		address->grph.meta_addr.low_part = lower_32_bits(dcc_address);
		address->grph.meta_addr.high_part = upper_32_bits(dcc_address);
	पूर्ण

	ret = validate_dcc(adev, क्रमmat, rotation, tiling_info, dcc, address, plane_size);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक
fill_plane_buffer_attributes(काष्ठा amdgpu_device *adev,
			     स्थिर काष्ठा amdgpu_framebuffer *afb,
			     स्थिर क्रमागत surface_pixel_क्रमmat क्रमmat,
			     स्थिर क्रमागत dc_rotation_angle rotation,
			     स्थिर uपूर्णांक64_t tiling_flags,
			     जोड़ dc_tiling_info *tiling_info,
			     काष्ठा plane_size *plane_size,
			     काष्ठा dc_plane_dcc_param *dcc,
			     काष्ठा dc_plane_address *address,
			     bool पंचांगz_surface,
			     bool क्रमce_disable_dcc)
अणु
	स्थिर काष्ठा drm_framebuffer *fb = &afb->base;
	पूर्णांक ret;

	स_रखो(tiling_info, 0, माप(*tiling_info));
	स_रखो(plane_size, 0, माप(*plane_size));
	स_रखो(dcc, 0, माप(*dcc));
	स_रखो(address, 0, माप(*address));

	address->पंचांगz_surface = पंचांगz_surface;

	अगर (क्रमmat < SURFACE_PIXEL_FORMAT_VIDEO_BEGIN) अणु
		uपूर्णांक64_t addr = afb->address + fb->offsets[0];

		plane_size->surface_size.x = 0;
		plane_size->surface_size.y = 0;
		plane_size->surface_size.width = fb->width;
		plane_size->surface_size.height = fb->height;
		plane_size->surface_pitch =
			fb->pitches[0] / fb->क्रमmat->cpp[0];

		address->type = PLN_ADDR_TYPE_GRAPHICS;
		address->grph.addr.low_part = lower_32_bits(addr);
		address->grph.addr.high_part = upper_32_bits(addr);
	पूर्ण अन्यथा अगर (क्रमmat < SURFACE_PIXEL_FORMAT_INVALID) अणु
		uपूर्णांक64_t luma_addr = afb->address + fb->offsets[0];
		uपूर्णांक64_t chroma_addr = afb->address + fb->offsets[1];

		plane_size->surface_size.x = 0;
		plane_size->surface_size.y = 0;
		plane_size->surface_size.width = fb->width;
		plane_size->surface_size.height = fb->height;
		plane_size->surface_pitch =
			fb->pitches[0] / fb->क्रमmat->cpp[0];

		plane_size->chroma_size.x = 0;
		plane_size->chroma_size.y = 0;
		/* TODO: set these based on surface क्रमmat */
		plane_size->chroma_size.width = fb->width / 2;
		plane_size->chroma_size.height = fb->height / 2;

		plane_size->chroma_pitch =
			fb->pitches[1] / fb->क्रमmat->cpp[1];

		address->type = PLN_ADDR_TYPE_VIDEO_PROGRESSIVE;
		address->video_progressive.luma_addr.low_part =
			lower_32_bits(luma_addr);
		address->video_progressive.luma_addr.high_part =
			upper_32_bits(luma_addr);
		address->video_progressive.chroma_addr.low_part =
			lower_32_bits(chroma_addr);
		address->video_progressive.chroma_addr.high_part =
			upper_32_bits(chroma_addr);
	पूर्ण

	अगर (adev->family >= AMDGPU_FAMILY_AI) अणु
		ret = fill_gfx9_plane_attributes_from_modअगरiers(adev, afb, क्रमmat,
								rotation, plane_size,
								tiling_info, dcc,
								address,
								क्रमce_disable_dcc);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		fill_gfx8_tiling_info_from_flags(tiling_info, tiling_flags);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
fill_blending_from_plane_state(स्थिर काष्ठा drm_plane_state *plane_state,
			       bool *per_pixel_alpha, bool *global_alpha,
			       पूर्णांक *global_alpha_value)
अणु
	*per_pixel_alpha = false;
	*global_alpha = false;
	*global_alpha_value = 0xff;

	अगर (plane_state->plane->type != DRM_PLANE_TYPE_OVERLAY)
		वापस;

	अगर (plane_state->pixel_blend_mode == DRM_MODE_BLEND_PREMULTI) अणु
		अटल स्थिर uपूर्णांक32_t alpha_क्रमmats[] = अणु
			DRM_FORMAT_ARGB8888,
			DRM_FORMAT_RGBA8888,
			DRM_FORMAT_ABGR8888,
		पूर्ण;
		uपूर्णांक32_t क्रमmat = plane_state->fb->क्रमmat->क्रमmat;
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; i < ARRAY_SIZE(alpha_क्रमmats); ++i) अणु
			अगर (क्रमmat == alpha_क्रमmats[i]) अणु
				*per_pixel_alpha = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (plane_state->alpha < 0xffff) अणु
		*global_alpha = true;
		*global_alpha_value = plane_state->alpha >> 8;
	पूर्ण
पूर्ण

अटल पूर्णांक
fill_plane_color_attributes(स्थिर काष्ठा drm_plane_state *plane_state,
			    स्थिर क्रमागत surface_pixel_क्रमmat क्रमmat,
			    क्रमागत dc_color_space *color_space)
अणु
	bool full_range;

	*color_space = COLOR_SPACE_SRGB;

	/* DRM color properties only affect non-RGB क्रमmats. */
	अगर (क्रमmat < SURFACE_PIXEL_FORMAT_VIDEO_BEGIN)
		वापस 0;

	full_range = (plane_state->color_range == DRM_COLOR_YCBCR_FULL_RANGE);

	चयन (plane_state->color_encoding) अणु
	हाल DRM_COLOR_YCBCR_BT601:
		अगर (full_range)
			*color_space = COLOR_SPACE_YCBCR601;
		अन्यथा
			*color_space = COLOR_SPACE_YCBCR601_LIMITED;
		अवरोध;

	हाल DRM_COLOR_YCBCR_BT709:
		अगर (full_range)
			*color_space = COLOR_SPACE_YCBCR709;
		अन्यथा
			*color_space = COLOR_SPACE_YCBCR709_LIMITED;
		अवरोध;

	हाल DRM_COLOR_YCBCR_BT2020:
		अगर (full_range)
			*color_space = COLOR_SPACE_2020_YCBCR;
		अन्यथा
			वापस -EINVAL;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
fill_dc_plane_info_and_addr(काष्ठा amdgpu_device *adev,
			    स्थिर काष्ठा drm_plane_state *plane_state,
			    स्थिर uपूर्णांक64_t tiling_flags,
			    काष्ठा dc_plane_info *plane_info,
			    काष्ठा dc_plane_address *address,
			    bool पंचांगz_surface,
			    bool क्रमce_disable_dcc)
अणु
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->fb;
	स्थिर काष्ठा amdgpu_framebuffer *afb =
		to_amdgpu_framebuffer(plane_state->fb);
	पूर्णांक ret;

	स_रखो(plane_info, 0, माप(*plane_info));

	चयन (fb->क्रमmat->क्रमmat) अणु
	हाल DRM_FORMAT_C8:
		plane_info->क्रमmat =
			SURFACE_PIXEL_FORMAT_GRPH_PALETA_256_COLORS;
		अवरोध;
	हाल DRM_FORMAT_RGB565:
		plane_info->क्रमmat = SURFACE_PIXEL_FORMAT_GRPH_RGB565;
		अवरोध;
	हाल DRM_FORMAT_XRGB8888:
	हाल DRM_FORMAT_ARGB8888:
		plane_info->क्रमmat = SURFACE_PIXEL_FORMAT_GRPH_ARGB8888;
		अवरोध;
	हाल DRM_FORMAT_XRGB2101010:
	हाल DRM_FORMAT_ARGB2101010:
		plane_info->क्रमmat = SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010;
		अवरोध;
	हाल DRM_FORMAT_XBGR2101010:
	हाल DRM_FORMAT_ABGR2101010:
		plane_info->क्रमmat = SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010;
		अवरोध;
	हाल DRM_FORMAT_XBGR8888:
	हाल DRM_FORMAT_ABGR8888:
		plane_info->क्रमmat = SURFACE_PIXEL_FORMAT_GRPH_ABGR8888;
		अवरोध;
	हाल DRM_FORMAT_NV21:
		plane_info->क्रमmat = SURFACE_PIXEL_FORMAT_VIDEO_420_YCbCr;
		अवरोध;
	हाल DRM_FORMAT_NV12:
		plane_info->क्रमmat = SURFACE_PIXEL_FORMAT_VIDEO_420_YCrCb;
		अवरोध;
	हाल DRM_FORMAT_P010:
		plane_info->क्रमmat = SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCrCb;
		अवरोध;
	हाल DRM_FORMAT_XRGB16161616F:
	हाल DRM_FORMAT_ARGB16161616F:
		plane_info->क्रमmat = SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616F;
		अवरोध;
	हाल DRM_FORMAT_XBGR16161616F:
	हाल DRM_FORMAT_ABGR16161616F:
		plane_info->क्रमmat = SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F;
		अवरोध;
	शेष:
		DRM_ERROR(
			"Unsupported screen format %p4cc\n",
			&fb->क्रमmat->क्रमmat);
		वापस -EINVAL;
	पूर्ण

	चयन (plane_state->rotation & DRM_MODE_ROTATE_MASK) अणु
	हाल DRM_MODE_ROTATE_0:
		plane_info->rotation = ROTATION_ANGLE_0;
		अवरोध;
	हाल DRM_MODE_ROTATE_90:
		plane_info->rotation = ROTATION_ANGLE_90;
		अवरोध;
	हाल DRM_MODE_ROTATE_180:
		plane_info->rotation = ROTATION_ANGLE_180;
		अवरोध;
	हाल DRM_MODE_ROTATE_270:
		plane_info->rotation = ROTATION_ANGLE_270;
		अवरोध;
	शेष:
		plane_info->rotation = ROTATION_ANGLE_0;
		अवरोध;
	पूर्ण

	plane_info->visible = true;
	plane_info->stereo_क्रमmat = PLANE_STEREO_FORMAT_NONE;

	plane_info->layer_index = 0;

	ret = fill_plane_color_attributes(plane_state, plane_info->क्रमmat,
					  &plane_info->color_space);
	अगर (ret)
		वापस ret;

	ret = fill_plane_buffer_attributes(adev, afb, plane_info->क्रमmat,
					   plane_info->rotation, tiling_flags,
					   &plane_info->tiling_info,
					   &plane_info->plane_size,
					   &plane_info->dcc, address, पंचांगz_surface,
					   क्रमce_disable_dcc);
	अगर (ret)
		वापस ret;

	fill_blending_from_plane_state(
		plane_state, &plane_info->per_pixel_alpha,
		&plane_info->global_alpha, &plane_info->global_alpha_value);

	वापस 0;
पूर्ण

अटल पूर्णांक fill_dc_plane_attributes(काष्ठा amdgpu_device *adev,
				    काष्ठा dc_plane_state *dc_plane_state,
				    काष्ठा drm_plane_state *plane_state,
				    काष्ठा drm_crtc_state *crtc_state)
अणु
	काष्ठा dm_crtc_state *dm_crtc_state = to_dm_crtc_state(crtc_state);
	काष्ठा amdgpu_framebuffer *afb = (काष्ठा amdgpu_framebuffer *)plane_state->fb;
	काष्ठा dc_scaling_info scaling_info;
	काष्ठा dc_plane_info plane_info;
	पूर्णांक ret;
	bool क्रमce_disable_dcc = false;

	ret = fill_dc_scaling_info(plane_state, &scaling_info);
	अगर (ret)
		वापस ret;

	dc_plane_state->src_rect = scaling_info.src_rect;
	dc_plane_state->dst_rect = scaling_info.dst_rect;
	dc_plane_state->clip_rect = scaling_info.clip_rect;
	dc_plane_state->scaling_quality = scaling_info.scaling_quality;

	क्रमce_disable_dcc = adev->asic_type == CHIP_RAVEN && adev->in_suspend;
	ret = fill_dc_plane_info_and_addr(adev, plane_state,
					  afb->tiling_flags,
					  &plane_info,
					  &dc_plane_state->address,
					  afb->पंचांगz_surface,
					  क्रमce_disable_dcc);
	अगर (ret)
		वापस ret;

	dc_plane_state->क्रमmat = plane_info.क्रमmat;
	dc_plane_state->color_space = plane_info.color_space;
	dc_plane_state->क्रमmat = plane_info.क्रमmat;
	dc_plane_state->plane_size = plane_info.plane_size;
	dc_plane_state->rotation = plane_info.rotation;
	dc_plane_state->horizontal_mirror = plane_info.horizontal_mirror;
	dc_plane_state->stereo_क्रमmat = plane_info.stereo_क्रमmat;
	dc_plane_state->tiling_info = plane_info.tiling_info;
	dc_plane_state->visible = plane_info.visible;
	dc_plane_state->per_pixel_alpha = plane_info.per_pixel_alpha;
	dc_plane_state->global_alpha = plane_info.global_alpha;
	dc_plane_state->global_alpha_value = plane_info.global_alpha_value;
	dc_plane_state->dcc = plane_info.dcc;
	dc_plane_state->layer_index = plane_info.layer_index; // Always वापसs 0
	dc_plane_state->flip_पूर्णांक_enabled = true;

	/*
	 * Always set input transfer function, since plane state is refreshed
	 * every समय.
	 */
	ret = amdgpu_dm_update_plane_color_mgmt(dm_crtc_state, dc_plane_state);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम update_stream_scaling_settings(स्थिर काष्ठा drm_display_mode *mode,
					   स्थिर काष्ठा dm_connector_state *dm_state,
					   काष्ठा dc_stream_state *stream)
अणु
	क्रमागत amdgpu_rmx_type rmx_type;

	काष्ठा rect src = अणु 0 पूर्ण; /* viewport in composition space*/
	काष्ठा rect dst = अणु 0 पूर्ण; /* stream addressable area */

	/* no mode. nothing to be करोne */
	अगर (!mode)
		वापस;

	/* Full screen scaling by शेष */
	src.width = mode->hdisplay;
	src.height = mode->vdisplay;
	dst.width = stream->timing.h_addressable;
	dst.height = stream->timing.v_addressable;

	अगर (dm_state) अणु
		rmx_type = dm_state->scaling;
		अगर (rmx_type == RMX_ASPECT || rmx_type == RMX_OFF) अणु
			अगर (src.width * dst.height <
					src.height * dst.width) अणु
				/* height needs less upscaling/more करोwnscaling */
				dst.width = src.width *
						dst.height / src.height;
			पूर्ण अन्यथा अणु
				/* width needs less upscaling/more करोwnscaling */
				dst.height = src.height *
						dst.width / src.width;
			पूर्ण
		पूर्ण अन्यथा अगर (rmx_type == RMX_CENTER) अणु
			dst = src;
		पूर्ण

		dst.x = (stream->timing.h_addressable - dst.width) / 2;
		dst.y = (stream->timing.v_addressable - dst.height) / 2;

		अगर (dm_state->underscan_enable) अणु
			dst.x += dm_state->underscan_hborder / 2;
			dst.y += dm_state->underscan_vborder / 2;
			dst.width -= dm_state->underscan_hborder;
			dst.height -= dm_state->underscan_vborder;
		पूर्ण
	पूर्ण

	stream->src = src;
	stream->dst = dst;

	DRM_DEBUG_KMS("Destination Rectangle x:%d  y:%d  width:%d  height:%d\n",
		      dst.x, dst.y, dst.width, dst.height);

पूर्ण

अटल क्रमागत dc_color_depth
convert_color_depth_from_display_info(स्थिर काष्ठा drm_connector *connector,
				      bool is_y420, पूर्णांक requested_bpc)
अणु
	uपूर्णांक8_t bpc;

	अगर (is_y420) अणु
		bpc = 8;

		/* Cap display bpc based on HDMI 2.0 HF-VSDB */
		अगर (connector->display_info.hdmi.y420_dc_modes & DRM_EDID_YCBCR420_DC_48)
			bpc = 16;
		अन्यथा अगर (connector->display_info.hdmi.y420_dc_modes & DRM_EDID_YCBCR420_DC_36)
			bpc = 12;
		अन्यथा अगर (connector->display_info.hdmi.y420_dc_modes & DRM_EDID_YCBCR420_DC_30)
			bpc = 10;
	पूर्ण अन्यथा अणु
		bpc = (uपूर्णांक8_t)connector->display_info.bpc;
		/* Assume 8 bpc by शेष अगर no bpc is specअगरied. */
		bpc = bpc ? bpc : 8;
	पूर्ण

	अगर (requested_bpc > 0) अणु
		/*
		 * Cap display bpc based on the user requested value.
		 *
		 * The value क्रम state->max_bpc may not correctly updated
		 * depending on when the connector माला_लो added to the state
		 * or अगर this was called outside of atomic check, so it
		 * can't be used directly.
		 */
		bpc = min_t(u8, bpc, requested_bpc);

		/* Round करोwn to the nearest even number. */
		bpc = bpc - (bpc & 1);
	पूर्ण

	चयन (bpc) अणु
	हाल 0:
		/*
		 * Temporary Work around, DRM करोesn't parse color depth क्रम
		 * EDID revision beक्रमe 1.4
		 * TODO: Fix edid parsing
		 */
		वापस COLOR_DEPTH_888;
	हाल 6:
		वापस COLOR_DEPTH_666;
	हाल 8:
		वापस COLOR_DEPTH_888;
	हाल 10:
		वापस COLOR_DEPTH_101010;
	हाल 12:
		वापस COLOR_DEPTH_121212;
	हाल 14:
		वापस COLOR_DEPTH_141414;
	हाल 16:
		वापस COLOR_DEPTH_161616;
	शेष:
		वापस COLOR_DEPTH_UNDEFINED;
	पूर्ण
पूर्ण

अटल क्रमागत dc_aspect_ratio
get_aspect_ratio(स्थिर काष्ठा drm_display_mode *mode_in)
अणु
	/* 1-1 mapping, since both क्रमागतs follow the HDMI spec. */
	वापस (क्रमागत dc_aspect_ratio) mode_in->picture_aspect_ratio;
पूर्ण

अटल क्रमागत dc_color_space
get_output_color_space(स्थिर काष्ठा dc_crtc_timing *dc_crtc_timing)
अणु
	क्रमागत dc_color_space color_space = COLOR_SPACE_SRGB;

	चयन (dc_crtc_timing->pixel_encoding)	अणु
	हाल PIXEL_ENCODING_YCBCR422:
	हाल PIXEL_ENCODING_YCBCR444:
	हाल PIXEL_ENCODING_YCBCR420:
	अणु
		/*
		 * 27030khz is the separation poपूर्णांक between HDTV and SDTV
		 * according to HDMI spec, we use YCbCr709 and YCbCr601
		 * respectively
		 */
		अगर (dc_crtc_timing->pix_clk_100hz > 270300) अणु
			अगर (dc_crtc_timing->flags.Y_ONLY)
				color_space =
					COLOR_SPACE_YCBCR709_LIMITED;
			अन्यथा
				color_space = COLOR_SPACE_YCBCR709;
		पूर्ण अन्यथा अणु
			अगर (dc_crtc_timing->flags.Y_ONLY)
				color_space =
					COLOR_SPACE_YCBCR601_LIMITED;
			अन्यथा
				color_space = COLOR_SPACE_YCBCR601;
		पूर्ण

	पूर्ण
	अवरोध;
	हाल PIXEL_ENCODING_RGB:
		color_space = COLOR_SPACE_SRGB;
		अवरोध;

	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण

	वापस color_space;
पूर्ण

अटल bool adjust_colour_depth_from_display_info(
	काष्ठा dc_crtc_timing *timing_out,
	स्थिर काष्ठा drm_display_info *info)
अणु
	क्रमागत dc_color_depth depth = timing_out->display_color_depth;
	पूर्णांक normalized_clk;
	करो अणु
		normalized_clk = timing_out->pix_clk_100hz / 10;
		/* YCbCr 4:2:0 requires additional adjusपंचांगent of 1/2 */
		अगर (timing_out->pixel_encoding == PIXEL_ENCODING_YCBCR420)
			normalized_clk /= 2;
		/* Adjusting pix घड़ी following on HDMI spec based on colour depth */
		चयन (depth) अणु
		हाल COLOR_DEPTH_888:
			अवरोध;
		हाल COLOR_DEPTH_101010:
			normalized_clk = (normalized_clk * 30) / 24;
			अवरोध;
		हाल COLOR_DEPTH_121212:
			normalized_clk = (normalized_clk * 36) / 24;
			अवरोध;
		हाल COLOR_DEPTH_161616:
			normalized_clk = (normalized_clk * 48) / 24;
			अवरोध;
		शेष:
			/* The above depths are the only ones valid क्रम HDMI. */
			वापस false;
		पूर्ण
		अगर (normalized_clk <= info->max_पंचांगds_घड़ी) अणु
			timing_out->display_color_depth = depth;
			वापस true;
		पूर्ण
	पूर्ण जबतक (--depth > COLOR_DEPTH_666);
	वापस false;
पूर्ण

अटल व्योम fill_stream_properties_from_drm_display_mode(
	काष्ठा dc_stream_state *stream,
	स्थिर काष्ठा drm_display_mode *mode_in,
	स्थिर काष्ठा drm_connector *connector,
	स्थिर काष्ठा drm_connector_state *connector_state,
	स्थिर काष्ठा dc_stream_state *old_stream,
	पूर्णांक requested_bpc)
अणु
	काष्ठा dc_crtc_timing *timing_out = &stream->timing;
	स्थिर काष्ठा drm_display_info *info = &connector->display_info;
	काष्ठा amdgpu_dm_connector *aconnector = to_amdgpu_dm_connector(connector);
	काष्ठा hdmi_venकरोr_infoframe hv_frame;
	काष्ठा hdmi_avi_infoframe avi_frame;

	स_रखो(&hv_frame, 0, माप(hv_frame));
	स_रखो(&avi_frame, 0, माप(avi_frame));

	timing_out->h_border_left = 0;
	timing_out->h_border_right = 0;
	timing_out->v_border_top = 0;
	timing_out->v_border_bottom = 0;
	/* TODO: un-hardcode */
	अगर (drm_mode_is_420_only(info, mode_in)
			&& stream->संकेत == SIGNAL_TYPE_HDMI_TYPE_A)
		timing_out->pixel_encoding = PIXEL_ENCODING_YCBCR420;
	अन्यथा अगर (drm_mode_is_420_also(info, mode_in)
			&& aconnector->क्रमce_yuv420_output)
		timing_out->pixel_encoding = PIXEL_ENCODING_YCBCR420;
	अन्यथा अगर ((connector->display_info.color_क्रमmats & DRM_COLOR_FORMAT_YCRCB444)
			&& stream->संकेत == SIGNAL_TYPE_HDMI_TYPE_A)
		timing_out->pixel_encoding = PIXEL_ENCODING_YCBCR444;
	अन्यथा
		timing_out->pixel_encoding = PIXEL_ENCODING_RGB;

	timing_out->timing_3d_क्रमmat = TIMING_3D_FORMAT_NONE;
	timing_out->display_color_depth = convert_color_depth_from_display_info(
		connector,
		(timing_out->pixel_encoding == PIXEL_ENCODING_YCBCR420),
		requested_bpc);
	timing_out->scan_type = SCANNING_TYPE_NODATA;
	timing_out->hdmi_vic = 0;

	अगर(old_stream) अणु
		timing_out->vic = old_stream->timing.vic;
		timing_out->flags.HSYNC_POSITIVE_POLARITY = old_stream->timing.flags.HSYNC_POSITIVE_POLARITY;
		timing_out->flags.VSYNC_POSITIVE_POLARITY = old_stream->timing.flags.VSYNC_POSITIVE_POLARITY;
	पूर्ण अन्यथा अणु
		timing_out->vic = drm_match_cea_mode(mode_in);
		अगर (mode_in->flags & DRM_MODE_FLAG_PHSYNC)
			timing_out->flags.HSYNC_POSITIVE_POLARITY = 1;
		अगर (mode_in->flags & DRM_MODE_FLAG_PVSYNC)
			timing_out->flags.VSYNC_POSITIVE_POLARITY = 1;
	पूर्ण

	अगर (stream->संकेत == SIGNAL_TYPE_HDMI_TYPE_A) अणु
		drm_hdmi_avi_infoframe_from_display_mode(&avi_frame, (काष्ठा drm_connector *)connector, mode_in);
		timing_out->vic = avi_frame.video_code;
		drm_hdmi_venकरोr_infoframe_from_display_mode(&hv_frame, (काष्ठा drm_connector *)connector, mode_in);
		timing_out->hdmi_vic = hv_frame.vic;
	पूर्ण

	अगर (is_मुक्तsync_video_mode(mode_in, aconnector)) अणु
		timing_out->h_addressable = mode_in->hdisplay;
		timing_out->h_total = mode_in->htotal;
		timing_out->h_sync_width = mode_in->hsync_end - mode_in->hsync_start;
		timing_out->h_front_porch = mode_in->hsync_start - mode_in->hdisplay;
		timing_out->v_total = mode_in->vtotal;
		timing_out->v_addressable = mode_in->vdisplay;
		timing_out->v_front_porch = mode_in->vsync_start - mode_in->vdisplay;
		timing_out->v_sync_width = mode_in->vsync_end - mode_in->vsync_start;
		timing_out->pix_clk_100hz = mode_in->घड़ी * 10;
	पूर्ण अन्यथा अणु
		timing_out->h_addressable = mode_in->crtc_hdisplay;
		timing_out->h_total = mode_in->crtc_htotal;
		timing_out->h_sync_width = mode_in->crtc_hsync_end - mode_in->crtc_hsync_start;
		timing_out->h_front_porch = mode_in->crtc_hsync_start - mode_in->crtc_hdisplay;
		timing_out->v_total = mode_in->crtc_vtotal;
		timing_out->v_addressable = mode_in->crtc_vdisplay;
		timing_out->v_front_porch = mode_in->crtc_vsync_start - mode_in->crtc_vdisplay;
		timing_out->v_sync_width = mode_in->crtc_vsync_end - mode_in->crtc_vsync_start;
		timing_out->pix_clk_100hz = mode_in->crtc_घड़ी * 10;
	पूर्ण

	timing_out->aspect_ratio = get_aspect_ratio(mode_in);

	stream->output_color_space = get_output_color_space(timing_out);

	stream->out_transfer_func->type = TF_TYPE_PREDEFINED;
	stream->out_transfer_func->tf = TRANSFER_FUNCTION_SRGB;
	अगर (stream->संकेत == SIGNAL_TYPE_HDMI_TYPE_A) अणु
		अगर (!adjust_colour_depth_from_display_info(timing_out, info) &&
		    drm_mode_is_420_also(info, mode_in) &&
		    timing_out->pixel_encoding != PIXEL_ENCODING_YCBCR420) अणु
			timing_out->pixel_encoding = PIXEL_ENCODING_YCBCR420;
			adjust_colour_depth_from_display_info(timing_out, info);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम fill_audio_info(काष्ठा audio_info *audio_info,
			    स्थिर काष्ठा drm_connector *drm_connector,
			    स्थिर काष्ठा dc_sink *dc_sink)
अणु
	पूर्णांक i = 0;
	पूर्णांक cea_revision = 0;
	स्थिर काष्ठा dc_edid_caps *edid_caps = &dc_sink->edid_caps;

	audio_info->manufacture_id = edid_caps->manufacturer_id;
	audio_info->product_id = edid_caps->product_id;

	cea_revision = drm_connector->display_info.cea_rev;

	strscpy(audio_info->display_name,
		edid_caps->display_name,
		AUDIO_INFO_DISPLAY_NAME_SIZE_IN_CHARS);

	अगर (cea_revision >= 3) अणु
		audio_info->mode_count = edid_caps->audio_mode_count;

		क्रम (i = 0; i < audio_info->mode_count; ++i) अणु
			audio_info->modes[i].क्रमmat_code =
					(क्रमागत audio_क्रमmat_code)
					(edid_caps->audio_modes[i].क्रमmat_code);
			audio_info->modes[i].channel_count =
					edid_caps->audio_modes[i].channel_count;
			audio_info->modes[i].sample_rates.all =
					edid_caps->audio_modes[i].sample_rate;
			audio_info->modes[i].sample_size =
					edid_caps->audio_modes[i].sample_size;
		पूर्ण
	पूर्ण

	audio_info->flags.all = edid_caps->speaker_flags;

	/* TODO: We only check क्रम the progressive mode, check क्रम पूर्णांकerlace mode too */
	अगर (drm_connector->latency_present[0]) अणु
		audio_info->video_latency = drm_connector->video_latency[0];
		audio_info->audio_latency = drm_connector->audio_latency[0];
	पूर्ण

	/* TODO: For DP, video and audio latency should be calculated from DPCD caps */

पूर्ण

अटल व्योम
copy_crtc_timing_क्रम_drm_display_mode(स्थिर काष्ठा drm_display_mode *src_mode,
				      काष्ठा drm_display_mode *dst_mode)
अणु
	dst_mode->crtc_hdisplay = src_mode->crtc_hdisplay;
	dst_mode->crtc_vdisplay = src_mode->crtc_vdisplay;
	dst_mode->crtc_घड़ी = src_mode->crtc_घड़ी;
	dst_mode->crtc_hblank_start = src_mode->crtc_hblank_start;
	dst_mode->crtc_hblank_end = src_mode->crtc_hblank_end;
	dst_mode->crtc_hsync_start =  src_mode->crtc_hsync_start;
	dst_mode->crtc_hsync_end = src_mode->crtc_hsync_end;
	dst_mode->crtc_htotal = src_mode->crtc_htotal;
	dst_mode->crtc_hskew = src_mode->crtc_hskew;
	dst_mode->crtc_vblank_start = src_mode->crtc_vblank_start;
	dst_mode->crtc_vblank_end = src_mode->crtc_vblank_end;
	dst_mode->crtc_vsync_start = src_mode->crtc_vsync_start;
	dst_mode->crtc_vsync_end = src_mode->crtc_vsync_end;
	dst_mode->crtc_vtotal = src_mode->crtc_vtotal;
पूर्ण

अटल व्योम
decide_crtc_timing_क्रम_drm_display_mode(काष्ठा drm_display_mode *drm_mode,
					स्थिर काष्ठा drm_display_mode *native_mode,
					bool scale_enabled)
अणु
	अगर (scale_enabled) अणु
		copy_crtc_timing_क्रम_drm_display_mode(native_mode, drm_mode);
	पूर्ण अन्यथा अगर (native_mode->घड़ी == drm_mode->घड़ी &&
			native_mode->htotal == drm_mode->htotal &&
			native_mode->vtotal == drm_mode->vtotal) अणु
		copy_crtc_timing_क्रम_drm_display_mode(native_mode, drm_mode);
	पूर्ण अन्यथा अणु
		/* no scaling nor amdgpu inserted, no need to patch */
	पूर्ण
पूर्ण

अटल काष्ठा dc_sink *
create_fake_sink(काष्ठा amdgpu_dm_connector *aconnector)
अणु
	काष्ठा dc_sink_init_data sink_init_data = अणु 0 पूर्ण;
	काष्ठा dc_sink *sink = शून्य;
	sink_init_data.link = aconnector->dc_link;
	sink_init_data.sink_संकेत = aconnector->dc_link->connector_संकेत;

	sink = dc_sink_create(&sink_init_data);
	अगर (!sink) अणु
		DRM_ERROR("Failed to create sink!\n");
		वापस शून्य;
	पूर्ण
	sink->sink_संकेत = SIGNAL_TYPE_VIRTUAL;

	वापस sink;
पूर्ण

अटल व्योम set_multisync_trigger_params(
		काष्ठा dc_stream_state *stream)
अणु
	काष्ठा dc_stream_state *master = शून्य;

	अगर (stream->triggered_crtc_reset.enabled) अणु
		master = stream->triggered_crtc_reset.event_source;
		stream->triggered_crtc_reset.event =
			master->timing.flags.VSYNC_POSITIVE_POLARITY ?
			CRTC_EVENT_VSYNC_RISING : CRTC_EVENT_VSYNC_FALLING;
		stream->triggered_crtc_reset.delay = TRIGGER_DELAY_NEXT_PIXEL;
	पूर्ण
पूर्ण

अटल व्योम set_master_stream(काष्ठा dc_stream_state *stream_set[],
			      पूर्णांक stream_count)
अणु
	पूर्णांक j, highest_rfr = 0, master_stream = 0;

	क्रम (j = 0;  j < stream_count; j++) अणु
		अगर (stream_set[j] && stream_set[j]->triggered_crtc_reset.enabled) अणु
			पूर्णांक refresh_rate = 0;

			refresh_rate = (stream_set[j]->timing.pix_clk_100hz*100)/
				(stream_set[j]->timing.h_total*stream_set[j]->timing.v_total);
			अगर (refresh_rate > highest_rfr) अणु
				highest_rfr = refresh_rate;
				master_stream = j;
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम (j = 0;  j < stream_count; j++) अणु
		अगर (stream_set[j])
			stream_set[j]->triggered_crtc_reset.event_source = stream_set[master_stream];
	पूर्ण
पूर्ण

अटल व्योम dm_enable_per_frame_crtc_master_sync(काष्ठा dc_state *context)
अणु
	पूर्णांक i = 0;
	काष्ठा dc_stream_state *stream;

	अगर (context->stream_count < 2)
		वापस;
	क्रम (i = 0; i < context->stream_count ; i++) अणु
		अगर (!context->streams[i])
			जारी;
		/*
		 * TODO: add a function to पढ़ो AMD VSDB bits and set
		 * crtc_sync_master.multi_sync_enabled flag
		 * For now it's set to false
		 */
	पूर्ण

	set_master_stream(context->streams, context->stream_count);

	क्रम (i = 0; i < context->stream_count ; i++) अणु
		stream = context->streams[i];

		अगर (!stream)
			जारी;

		set_multisync_trigger_params(stream);
	पूर्ण
पूर्ण

अटल काष्ठा drm_display_mode *
get_highest_refresh_rate_mode(काष्ठा amdgpu_dm_connector *aconnector,
			  bool use_probed_modes)
अणु
	काष्ठा drm_display_mode *m, *m_pref = शून्य;
	u16 current_refresh, highest_refresh;
	काष्ठा list_head *list_head = use_probed_modes ?
						    &aconnector->base.probed_modes :
						    &aconnector->base.modes;

	अगर (aconnector->मुक्तsync_vid_base.घड़ी != 0)
		वापस &aconnector->मुक्तsync_vid_base;

	/* Find the preferred mode */
	list_क्रम_each_entry (m, list_head, head) अणु
		अगर (m->type & DRM_MODE_TYPE_PREFERRED) अणु
			m_pref = m;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!m_pref) अणु
		/* Probably an EDID with no preferred mode. Fallback to first entry */
		m_pref = list_first_entry_or_null(
			&aconnector->base.modes, काष्ठा drm_display_mode, head);
		अगर (!m_pref) अणु
			DRM_DEBUG_DRIVER("No preferred mode found in EDID\n");
			वापस शून्य;
		पूर्ण
	पूर्ण

	highest_refresh = drm_mode_vrefresh(m_pref);

	/*
	 * Find the mode with highest refresh rate with same resolution.
	 * For some monitors, preferred mode is not the mode with highest
	 * supported refresh rate.
	 */
	list_क्रम_each_entry (m, list_head, head) अणु
		current_refresh  = drm_mode_vrefresh(m);

		अगर (m->hdisplay == m_pref->hdisplay &&
		    m->vdisplay == m_pref->vdisplay &&
		    highest_refresh < current_refresh) अणु
			highest_refresh = current_refresh;
			m_pref = m;
		पूर्ण
	पूर्ण

	aconnector->मुक्तsync_vid_base = *m_pref;
	वापस m_pref;
पूर्ण

अटल bool is_मुक्तsync_video_mode(स्थिर काष्ठा drm_display_mode *mode,
				   काष्ठा amdgpu_dm_connector *aconnector)
अणु
	काष्ठा drm_display_mode *high_mode;
	पूर्णांक timing_dअगरf;

	high_mode = get_highest_refresh_rate_mode(aconnector, false);
	अगर (!high_mode || !mode)
		वापस false;

	timing_dअगरf = high_mode->vtotal - mode->vtotal;

	अगर (high_mode->घड़ी == 0 || high_mode->घड़ी != mode->घड़ी ||
	    high_mode->hdisplay != mode->hdisplay ||
	    high_mode->vdisplay != mode->vdisplay ||
	    high_mode->hsync_start != mode->hsync_start ||
	    high_mode->hsync_end != mode->hsync_end ||
	    high_mode->htotal != mode->htotal ||
	    high_mode->hskew != mode->hskew ||
	    high_mode->vscan != mode->vscan ||
	    high_mode->vsync_start - mode->vsync_start != timing_dअगरf ||
	    high_mode->vsync_end - mode->vsync_end != timing_dअगरf)
		वापस false;
	अन्यथा
		वापस true;
पूर्ण

अटल काष्ठा dc_stream_state *
create_stream_क्रम_sink(काष्ठा amdgpu_dm_connector *aconnector,
		       स्थिर काष्ठा drm_display_mode *drm_mode,
		       स्थिर काष्ठा dm_connector_state *dm_state,
		       स्थिर काष्ठा dc_stream_state *old_stream,
		       पूर्णांक requested_bpc)
अणु
	काष्ठा drm_display_mode *preferred_mode = शून्य;
	काष्ठा drm_connector *drm_connector;
	स्थिर काष्ठा drm_connector_state *con_state =
		dm_state ? &dm_state->base : शून्य;
	काष्ठा dc_stream_state *stream = शून्य;
	काष्ठा drm_display_mode mode = *drm_mode;
	काष्ठा drm_display_mode saved_mode;
	काष्ठा drm_display_mode *मुक्तsync_mode = शून्य;
	bool native_mode_found = false;
	bool recalculate_timing = false;
	bool scale = dm_state ? (dm_state->scaling != RMX_OFF) : false;
	पूर्णांक mode_refresh;
	पूर्णांक preferred_refresh = 0;
#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	काष्ठा dsc_dec_dpcd_caps dsc_caps;
	uपूर्णांक32_t link_bandwidth_kbps;
#पूर्ण_अगर
	काष्ठा dc_sink *sink = शून्य;

	स_रखो(&saved_mode, 0, माप(saved_mode));

	अगर (aconnector == शून्य) अणु
		DRM_ERROR("aconnector is NULL!\n");
		वापस stream;
	पूर्ण

	drm_connector = &aconnector->base;

	अगर (!aconnector->dc_sink) अणु
		sink = create_fake_sink(aconnector);
		अगर (!sink)
			वापस stream;
	पूर्ण अन्यथा अणु
		sink = aconnector->dc_sink;
		dc_sink_retain(sink);
	पूर्ण

	stream = dc_create_stream_क्रम_sink(sink);

	अगर (stream == शून्य) अणु
		DRM_ERROR("Failed to create stream for sink!\n");
		जाओ finish;
	पूर्ण

	stream->dm_stream_context = aconnector;

	stream->timing.flags.LTE_340MCSC_SCRAMBLE =
		drm_connector->display_info.hdmi.scdc.scrambling.low_rates;

	list_क्रम_each_entry(preferred_mode, &aconnector->base.modes, head) अणु
		/* Search क्रम preferred mode */
		अगर (preferred_mode->type & DRM_MODE_TYPE_PREFERRED) अणु
			native_mode_found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!native_mode_found)
		preferred_mode = list_first_entry_or_null(
				&aconnector->base.modes,
				काष्ठा drm_display_mode,
				head);

	mode_refresh = drm_mode_vrefresh(&mode);

	अगर (preferred_mode == शून्य) अणु
		/*
		 * This may not be an error, the use हाल is when we have no
		 * usermode calls to reset and set mode upon hotplug. In this
		 * हाल, we call set mode ourselves to restore the previous mode
		 * and the modelist may not be filled in in समय.
		 */
		DRM_DEBUG_DRIVER("No preferred mode found\n");
	पूर्ण अन्यथा अणु
		recalculate_timing = amdgpu_मुक्तsync_vid_mode &&
				 is_मुक्तsync_video_mode(&mode, aconnector);
		अगर (recalculate_timing) अणु
			मुक्तsync_mode = get_highest_refresh_rate_mode(aconnector, false);
			saved_mode = mode;
			mode = *मुक्तsync_mode;
		पूर्ण अन्यथा अणु
			decide_crtc_timing_क्रम_drm_display_mode(
				&mode, preferred_mode, scale);

			preferred_refresh = drm_mode_vrefresh(preferred_mode);
		पूर्ण
	पूर्ण

	अगर (recalculate_timing)
		drm_mode_set_crtcinfo(&saved_mode, 0);
	अन्यथा अगर (!dm_state)
		drm_mode_set_crtcinfo(&mode, 0);

       /*
	* If scaling is enabled and refresh rate didn't change
	* we copy the vic and polarities of the old timings
	*/
	अगर (!scale || mode_refresh != preferred_refresh)
		fill_stream_properties_from_drm_display_mode(
			stream, &mode, &aconnector->base, con_state, शून्य,
			requested_bpc);
	अन्यथा
		fill_stream_properties_from_drm_display_mode(
			stream, &mode, &aconnector->base, con_state, old_stream,
			requested_bpc);

	stream->timing.flags.DSC = 0;

	अगर (aconnector->dc_link && sink->sink_संकेत == SIGNAL_TYPE_DISPLAY_PORT) अणु
#अगर defined(CONFIG_DRM_AMD_DC_DCN)
		dc_dsc_parse_dsc_dpcd(aconnector->dc_link->ctx->dc,
				      aconnector->dc_link->dpcd_caps.dsc_caps.dsc_basic_caps.raw,
				      aconnector->dc_link->dpcd_caps.dsc_caps.dsc_branch_decoder_caps.raw,
				      &dsc_caps);
		link_bandwidth_kbps = dc_link_bandwidth_kbps(aconnector->dc_link,
							     dc_link_get_link_cap(aconnector->dc_link));

		अगर (aconnector->dsc_settings.dsc_क्रमce_enable != DSC_CLK_FORCE_DISABLE && dsc_caps.is_dsc_supported) अणु
			/* Set DSC policy according to dsc_घड़ी_en */
			dc_dsc_policy_set_enable_dsc_when_not_needed(
				aconnector->dsc_settings.dsc_क्रमce_enable == DSC_CLK_FORCE_ENABLE);

			अगर (dc_dsc_compute_config(aconnector->dc_link->ctx->dc->res_pool->dscs[0],
						  &dsc_caps,
						  aconnector->dc_link->ctx->dc->debug.dsc_min_slice_height_override,
						  0,
						  link_bandwidth_kbps,
						  &stream->timing,
						  &stream->timing.dsc_cfg))
				stream->timing.flags.DSC = 1;
			/* Overग_लिखो the stream flag अगर DSC is enabled through debugfs */
			अगर (aconnector->dsc_settings.dsc_क्रमce_enable == DSC_CLK_FORCE_ENABLE)
				stream->timing.flags.DSC = 1;

			अगर (stream->timing.flags.DSC && aconnector->dsc_settings.dsc_num_slices_h)
				stream->timing.dsc_cfg.num_slices_h = aconnector->dsc_settings.dsc_num_slices_h;

			अगर (stream->timing.flags.DSC && aconnector->dsc_settings.dsc_num_slices_v)
				stream->timing.dsc_cfg.num_slices_v = aconnector->dsc_settings.dsc_num_slices_v;

			अगर (stream->timing.flags.DSC && aconnector->dsc_settings.dsc_bits_per_pixel)
				stream->timing.dsc_cfg.bits_per_pixel = aconnector->dsc_settings.dsc_bits_per_pixel;
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	update_stream_scaling_settings(&mode, dm_state, stream);

	fill_audio_info(
		&stream->audio_info,
		drm_connector,
		sink);

	update_stream_संकेत(stream, sink);

	अगर (stream->संकेत == SIGNAL_TYPE_HDMI_TYPE_A)
		mod_build_hf_vsअगर_infopacket(stream, &stream->vsp_infopacket);

	अगर (stream->link->psr_settings.psr_feature_enabled) अणु
		//
		// should decide stream support vsc sdp colorimetry capability
		// beक्रमe building vsc info packet
		//
		stream->use_vsc_sdp_क्रम_colorimetry = false;
		अगर (aconnector->dc_sink->sink_संकेत == SIGNAL_TYPE_DISPLAY_PORT_MST) अणु
			stream->use_vsc_sdp_क्रम_colorimetry =
				aconnector->dc_sink->is_vsc_sdp_colorimetry_supported;
		पूर्ण अन्यथा अणु
			अगर (stream->link->dpcd_caps.dprx_feature.bits.VSC_SDP_COLORIMETRY_SUPPORTED)
				stream->use_vsc_sdp_क्रम_colorimetry = true;
		पूर्ण
		mod_build_vsc_infopacket(stream, &stream->vsc_infopacket);
	पूर्ण
finish:
	dc_sink_release(sink);

	वापस stream;
पूर्ण

अटल व्योम amdgpu_dm_crtc_destroy(काष्ठा drm_crtc *crtc)
अणु
	drm_crtc_cleanup(crtc);
	kमुक्त(crtc);
पूर्ण

अटल व्योम dm_crtc_destroy_state(काष्ठा drm_crtc *crtc,
				  काष्ठा drm_crtc_state *state)
अणु
	काष्ठा dm_crtc_state *cur = to_dm_crtc_state(state);

	/* TODO Destroy dc_stream objects are stream object is flattened */
	अगर (cur->stream)
		dc_stream_release(cur->stream);


	__drm_atomic_helper_crtc_destroy_state(state);


	kमुक्त(state);
पूर्ण

अटल व्योम dm_crtc_reset_state(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा dm_crtc_state *state;

	अगर (crtc->state)
		dm_crtc_destroy_state(crtc, crtc->state);

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (WARN_ON(!state))
		वापस;

	__drm_atomic_helper_crtc_reset(crtc, &state->base);
पूर्ण

अटल काष्ठा drm_crtc_state *
dm_crtc_duplicate_state(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा dm_crtc_state *state, *cur;

	cur = to_dm_crtc_state(crtc->state);

	अगर (WARN_ON(!crtc->state))
		वापस शून्य;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	__drm_atomic_helper_crtc_duplicate_state(crtc, &state->base);

	अगर (cur->stream) अणु
		state->stream = cur->stream;
		dc_stream_retain(state->stream);
	पूर्ण

	state->active_planes = cur->active_planes;
	state->vrr_infopacket = cur->vrr_infopacket;
	state->abm_level = cur->abm_level;
	state->vrr_supported = cur->vrr_supported;
	state->मुक्तsync_config = cur->मुक्तsync_config;
	state->cm_has_degamma = cur->cm_has_degamma;
	state->cm_is_degamma_srgb = cur->cm_is_degamma_srgb;
	/* TODO Duplicate dc_stream after objects are stream object is flattened */

	वापस &state->base;
पूर्ण

#अगर_घोषित CONFIG_DRM_AMD_SECURE_DISPLAY
अटल पूर्णांक amdgpu_dm_crtc_late_रेजिस्टर(काष्ठा drm_crtc *crtc)
अणु
	crtc_debugfs_init(crtc);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक dm_set_vupdate_irq(काष्ठा drm_crtc *crtc, bool enable)
अणु
	क्रमागत dc_irq_source irq_source;
	काष्ठा amdgpu_crtc *acrtc = to_amdgpu_crtc(crtc);
	काष्ठा amdgpu_device *adev = drm_to_adev(crtc->dev);
	पूर्णांक rc;

	irq_source = IRQ_TYPE_VUPDATE + acrtc->otg_inst;

	rc = dc_पूर्णांकerrupt_set(adev->dm.dc, irq_source, enable) ? 0 : -EBUSY;

	DRM_DEBUG_VBL("crtc %d - vupdate irq %sabling: r=%d\n",
		      acrtc->crtc_id, enable ? "en" : "dis", rc);
	वापस rc;
पूर्ण

अटल अंतरभूत पूर्णांक dm_set_vblank(काष्ठा drm_crtc *crtc, bool enable)
अणु
	क्रमागत dc_irq_source irq_source;
	काष्ठा amdgpu_crtc *acrtc = to_amdgpu_crtc(crtc);
	काष्ठा amdgpu_device *adev = drm_to_adev(crtc->dev);
	काष्ठा dm_crtc_state *acrtc_state = to_dm_crtc_state(crtc->state);
#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	काष्ठा amdgpu_display_manager *dm = &adev->dm;
	अचिन्हित दीर्घ flags;
#पूर्ण_अगर
	पूर्णांक rc = 0;

	अगर (enable) अणु
		/* vblank irq on -> Only need vupdate irq in vrr mode */
		अगर (amdgpu_dm_vrr_active(acrtc_state))
			rc = dm_set_vupdate_irq(crtc, true);
	पूर्ण अन्यथा अणु
		/* vblank irq off -> vupdate irq off */
		rc = dm_set_vupdate_irq(crtc, false);
	पूर्ण

	अगर (rc)
		वापस rc;

	irq_source = IRQ_TYPE_VBLANK + acrtc->otg_inst;

	अगर (!dc_पूर्णांकerrupt_set(adev->dm.dc, irq_source, enable))
		वापस -EBUSY;

	अगर (amdgpu_in_reset(adev))
		वापस 0;

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	spin_lock_irqsave(&dm->vblank_lock, flags);
	dm->vblank_workqueue->dm = dm;
	dm->vblank_workqueue->otg_inst = acrtc->otg_inst;
	dm->vblank_workqueue->enable = enable;
	spin_unlock_irqrestore(&dm->vblank_lock, flags);
	schedule_work(&dm->vblank_workqueue->mall_work);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक dm_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	वापस dm_set_vblank(crtc, true);
पूर्ण

अटल व्योम dm_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	dm_set_vblank(crtc, false);
पूर्ण

/* Implemented only the options currently availible क्रम the driver */
अटल स्थिर काष्ठा drm_crtc_funcs amdgpu_dm_crtc_funcs = अणु
	.reset = dm_crtc_reset_state,
	.destroy = amdgpu_dm_crtc_destroy,
	.set_config = drm_atomic_helper_set_config,
	.page_flip = drm_atomic_helper_page_flip,
	.atomic_duplicate_state = dm_crtc_duplicate_state,
	.atomic_destroy_state = dm_crtc_destroy_state,
	.set_crc_source = amdgpu_dm_crtc_set_crc_source,
	.verअगरy_crc_source = amdgpu_dm_crtc_verअगरy_crc_source,
	.get_crc_sources = amdgpu_dm_crtc_get_crc_sources,
	.get_vblank_counter = amdgpu_get_vblank_counter_kms,
	.enable_vblank = dm_enable_vblank,
	.disable_vblank = dm_disable_vblank,
	.get_vblank_बारtamp = drm_crtc_vblank_helper_get_vblank_बारtamp,
#अगर defined(CONFIG_DRM_AMD_SECURE_DISPLAY)
	.late_रेजिस्टर = amdgpu_dm_crtc_late_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

अटल क्रमागत drm_connector_status
amdgpu_dm_connector_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	bool connected;
	काष्ठा amdgpu_dm_connector *aconnector = to_amdgpu_dm_connector(connector);

	/*
	 * Notes:
	 * 1. This पूर्णांकerface is NOT called in context of HPD irq.
	 * 2. This पूर्णांकerface *is called* in context of user-mode ioctl. Which
	 * makes it a bad place क्रम *any* MST-related activity.
	 */

	अगर (aconnector->base.क्रमce == DRM_FORCE_UNSPECIFIED &&
	    !aconnector->fake_enable)
		connected = (aconnector->dc_sink != शून्य);
	अन्यथा
		connected = (aconnector->base.क्रमce == DRM_FORCE_ON);

	update_subconnector_property(aconnector);

	वापस (connected ? connector_status_connected :
			connector_status_disconnected);
पूर्ण

पूर्णांक amdgpu_dm_connector_atomic_set_property(काष्ठा drm_connector *connector,
					    काष्ठा drm_connector_state *connector_state,
					    काष्ठा drm_property *property,
					    uपूर्णांक64_t val)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा dm_connector_state *dm_old_state =
		to_dm_connector_state(connector->state);
	काष्ठा dm_connector_state *dm_new_state =
		to_dm_connector_state(connector_state);

	पूर्णांक ret = -EINVAL;

	अगर (property == dev->mode_config.scaling_mode_property) अणु
		क्रमागत amdgpu_rmx_type rmx_type;

		चयन (val) अणु
		हाल DRM_MODE_SCALE_CENTER:
			rmx_type = RMX_CENTER;
			अवरोध;
		हाल DRM_MODE_SCALE_ASPECT:
			rmx_type = RMX_ASPECT;
			अवरोध;
		हाल DRM_MODE_SCALE_FULLSCREEN:
			rmx_type = RMX_FULL;
			अवरोध;
		हाल DRM_MODE_SCALE_NONE:
		शेष:
			rmx_type = RMX_OFF;
			अवरोध;
		पूर्ण

		अगर (dm_old_state->scaling == rmx_type)
			वापस 0;

		dm_new_state->scaling = rmx_type;
		ret = 0;
	पूर्ण अन्यथा अगर (property == adev->mode_info.underscan_hborder_property) अणु
		dm_new_state->underscan_hborder = val;
		ret = 0;
	पूर्ण अन्यथा अगर (property == adev->mode_info.underscan_vborder_property) अणु
		dm_new_state->underscan_vborder = val;
		ret = 0;
	पूर्ण अन्यथा अगर (property == adev->mode_info.underscan_property) अणु
		dm_new_state->underscan_enable = val;
		ret = 0;
	पूर्ण अन्यथा अगर (property == adev->mode_info.abm_level_property) अणु
		dm_new_state->abm_level = val;
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक amdgpu_dm_connector_atomic_get_property(काष्ठा drm_connector *connector,
					    स्थिर काष्ठा drm_connector_state *state,
					    काष्ठा drm_property *property,
					    uपूर्णांक64_t *val)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा dm_connector_state *dm_state =
		to_dm_connector_state(state);
	पूर्णांक ret = -EINVAL;

	अगर (property == dev->mode_config.scaling_mode_property) अणु
		चयन (dm_state->scaling) अणु
		हाल RMX_CENTER:
			*val = DRM_MODE_SCALE_CENTER;
			अवरोध;
		हाल RMX_ASPECT:
			*val = DRM_MODE_SCALE_ASPECT;
			अवरोध;
		हाल RMX_FULL:
			*val = DRM_MODE_SCALE_FULLSCREEN;
			अवरोध;
		हाल RMX_OFF:
		शेष:
			*val = DRM_MODE_SCALE_NONE;
			अवरोध;
		पूर्ण
		ret = 0;
	पूर्ण अन्यथा अगर (property == adev->mode_info.underscan_hborder_property) अणु
		*val = dm_state->underscan_hborder;
		ret = 0;
	पूर्ण अन्यथा अगर (property == adev->mode_info.underscan_vborder_property) अणु
		*val = dm_state->underscan_vborder;
		ret = 0;
	पूर्ण अन्यथा अगर (property == adev->mode_info.underscan_property) अणु
		*val = dm_state->underscan_enable;
		ret = 0;
	पूर्ण अन्यथा अगर (property == adev->mode_info.abm_level_property) अणु
		*val = dm_state->abm_level;
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम amdgpu_dm_connector_unरेजिस्टर(काष्ठा drm_connector *connector)
अणु
	काष्ठा amdgpu_dm_connector *amdgpu_dm_connector = to_amdgpu_dm_connector(connector);

	drm_dp_aux_unरेजिस्टर(&amdgpu_dm_connector->dm_dp_aux.aux);
पूर्ण

अटल व्योम amdgpu_dm_connector_destroy(काष्ठा drm_connector *connector)
अणु
	काष्ठा amdgpu_dm_connector *aconnector = to_amdgpu_dm_connector(connector);
	स्थिर काष्ठा dc_link *link = aconnector->dc_link;
	काष्ठा amdgpu_device *adev = drm_to_adev(connector->dev);
	काष्ठा amdgpu_display_manager *dm = &adev->dm;

	/*
	 * Call only अगर mst_mgr was iniitalized beक्रमe since it's not करोne
	 * क्रम all connector types.
	 */
	अगर (aconnector->mst_mgr.dev)
		drm_dp_mst_topology_mgr_destroy(&aconnector->mst_mgr);

#अगर defined(CONFIG_BACKLIGHT_CLASS_DEVICE) ||\
	defined(CONFIG_BACKLIGHT_CLASS_DEVICE_MODULE)

	अगर ((link->connector_संकेत & (SIGNAL_TYPE_EDP | SIGNAL_TYPE_LVDS)) &&
	    link->type != dc_connection_none &&
	    dm->backlight_dev) अणु
		backlight_device_unरेजिस्टर(dm->backlight_dev);
		dm->backlight_dev = शून्य;
	पूर्ण
#पूर्ण_अगर

	अगर (aconnector->dc_em_sink)
		dc_sink_release(aconnector->dc_em_sink);
	aconnector->dc_em_sink = शून्य;
	अगर (aconnector->dc_sink)
		dc_sink_release(aconnector->dc_sink);
	aconnector->dc_sink = शून्य;

	drm_dp_cec_unरेजिस्टर_connector(&aconnector->dm_dp_aux.aux);
	drm_connector_unरेजिस्टर(connector);
	drm_connector_cleanup(connector);
	अगर (aconnector->i2c) अणु
		i2c_del_adapter(&aconnector->i2c->base);
		kमुक्त(aconnector->i2c);
	पूर्ण
	kमुक्त(aconnector->dm_dp_aux.aux.name);

	kमुक्त(connector);
पूर्ण

व्योम amdgpu_dm_connector_funcs_reset(काष्ठा drm_connector *connector)
अणु
	काष्ठा dm_connector_state *state =
		to_dm_connector_state(connector->state);

	अगर (connector->state)
		__drm_atomic_helper_connector_destroy_state(connector->state);

	kमुक्त(state);

	state = kzalloc(माप(*state), GFP_KERNEL);

	अगर (state) अणु
		state->scaling = RMX_OFF;
		state->underscan_enable = false;
		state->underscan_hborder = 0;
		state->underscan_vborder = 0;
		state->base.max_requested_bpc = 8;
		state->vcpi_slots = 0;
		state->pbn = 0;
		अगर (connector->connector_type == DRM_MODE_CONNECTOR_eDP)
			state->abm_level = amdgpu_dm_abm_level;

		__drm_atomic_helper_connector_reset(connector, &state->base);
	पूर्ण
पूर्ण

काष्ठा drm_connector_state *
amdgpu_dm_connector_atomic_duplicate_state(काष्ठा drm_connector *connector)
अणु
	काष्ठा dm_connector_state *state =
		to_dm_connector_state(connector->state);

	काष्ठा dm_connector_state *new_state =
			kmemdup(state, माप(*state), GFP_KERNEL);

	अगर (!new_state)
		वापस शून्य;

	__drm_atomic_helper_connector_duplicate_state(connector, &new_state->base);

	new_state->मुक्तsync_capable = state->मुक्तsync_capable;
	new_state->abm_level = state->abm_level;
	new_state->scaling = state->scaling;
	new_state->underscan_enable = state->underscan_enable;
	new_state->underscan_hborder = state->underscan_hborder;
	new_state->underscan_vborder = state->underscan_vborder;
	new_state->vcpi_slots = state->vcpi_slots;
	new_state->pbn = state->pbn;
	वापस &new_state->base;
पूर्ण

अटल पूर्णांक
amdgpu_dm_connector_late_रेजिस्टर(काष्ठा drm_connector *connector)
अणु
	काष्ठा amdgpu_dm_connector *amdgpu_dm_connector =
		to_amdgpu_dm_connector(connector);
	पूर्णांक r;

	अगर ((connector->connector_type == DRM_MODE_CONNECTOR_DisplayPort) ||
	    (connector->connector_type == DRM_MODE_CONNECTOR_eDP)) अणु
		amdgpu_dm_connector->dm_dp_aux.aux.dev = connector->kdev;
		r = drm_dp_aux_रेजिस्टर(&amdgpu_dm_connector->dm_dp_aux.aux);
		अगर (r)
			वापस r;
	पूर्ण

#अगर defined(CONFIG_DEBUG_FS)
	connector_debugfs_init(amdgpu_dm_connector);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs amdgpu_dm_connector_funcs = अणु
	.reset = amdgpu_dm_connector_funcs_reset,
	.detect = amdgpu_dm_connector_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = amdgpu_dm_connector_destroy,
	.atomic_duplicate_state = amdgpu_dm_connector_atomic_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
	.atomic_set_property = amdgpu_dm_connector_atomic_set_property,
	.atomic_get_property = amdgpu_dm_connector_atomic_get_property,
	.late_रेजिस्टर = amdgpu_dm_connector_late_रेजिस्टर,
	.early_unरेजिस्टर = amdgpu_dm_connector_unरेजिस्टर
पूर्ण;

अटल पूर्णांक get_modes(काष्ठा drm_connector *connector)
अणु
	वापस amdgpu_dm_connector_get_modes(connector);
पूर्ण

अटल व्योम create_eml_sink(काष्ठा amdgpu_dm_connector *aconnector)
अणु
	काष्ठा dc_sink_init_data init_params = अणु
			.link = aconnector->dc_link,
			.sink_संकेत = SIGNAL_TYPE_VIRTUAL
	पूर्ण;
	काष्ठा edid *edid;

	अगर (!aconnector->base.edid_blob_ptr) अणु
		DRM_ERROR("No EDID firmware found on connector: %s ,forcing to OFF!\n",
				aconnector->base.name);

		aconnector->base.क्रमce = DRM_FORCE_OFF;
		aconnector->base.override_edid = false;
		वापस;
	पूर्ण

	edid = (काष्ठा edid *) aconnector->base.edid_blob_ptr->data;

	aconnector->edid = edid;

	aconnector->dc_em_sink = dc_link_add_remote_sink(
		aconnector->dc_link,
		(uपूर्णांक8_t *)edid,
		(edid->extensions + 1) * EDID_LENGTH,
		&init_params);

	अगर (aconnector->base.क्रमce == DRM_FORCE_ON) अणु
		aconnector->dc_sink = aconnector->dc_link->local_sink ?
		aconnector->dc_link->local_sink :
		aconnector->dc_em_sink;
		dc_sink_retain(aconnector->dc_sink);
	पूर्ण
पूर्ण

अटल व्योम handle_edid_mgmt(काष्ठा amdgpu_dm_connector *aconnector)
अणु
	काष्ठा dc_link *link = (काष्ठा dc_link *)aconnector->dc_link;

	/*
	 * In हाल of headless boot with क्रमce on क्रम DP managed connector
	 * Those settings have to be != 0 to get initial modeset
	 */
	अगर (link->connector_संकेत == SIGNAL_TYPE_DISPLAY_PORT) अणु
		link->verअगरied_link_cap.lane_count = LANE_COUNT_FOUR;
		link->verअगरied_link_cap.link_rate = LINK_RATE_HIGH2;
	पूर्ण


	aconnector->base.override_edid = true;
	create_eml_sink(aconnector);
पूर्ण

अटल काष्ठा dc_stream_state *
create_validate_stream_क्रम_sink(काष्ठा amdgpu_dm_connector *aconnector,
				स्थिर काष्ठा drm_display_mode *drm_mode,
				स्थिर काष्ठा dm_connector_state *dm_state,
				स्थिर काष्ठा dc_stream_state *old_stream)
अणु
	काष्ठा drm_connector *connector = &aconnector->base;
	काष्ठा amdgpu_device *adev = drm_to_adev(connector->dev);
	काष्ठा dc_stream_state *stream;
	स्थिर काष्ठा drm_connector_state *drm_state = dm_state ? &dm_state->base : शून्य;
	पूर्णांक requested_bpc = drm_state ? drm_state->max_requested_bpc : 8;
	क्रमागत dc_status dc_result = DC_OK;

	करो अणु
		stream = create_stream_क्रम_sink(aconnector, drm_mode,
						dm_state, old_stream,
						requested_bpc);
		अगर (stream == शून्य) अणु
			DRM_ERROR("Failed to create stream for sink!\n");
			अवरोध;
		पूर्ण

		dc_result = dc_validate_stream(adev->dm.dc, stream);

		अगर (dc_result != DC_OK) अणु
			DRM_DEBUG_KMS("Mode %dx%d (clk %d) failed DC validation with error %d (%s)\n",
				      drm_mode->hdisplay,
				      drm_mode->vdisplay,
				      drm_mode->घड़ी,
				      dc_result,
				      dc_status_to_str(dc_result));

			dc_stream_release(stream);
			stream = शून्य;
			requested_bpc -= 2; /* lower bpc to retry validation */
		पूर्ण

	पूर्ण जबतक (stream == शून्य && requested_bpc >= 6);

	अगर (dc_result == DC_FAIL_ENC_VALIDATE && !aconnector->क्रमce_yuv420_output) अणु
		DRM_DEBUG_KMS("Retry forcing YCbCr420 encoding\n");

		aconnector->क्रमce_yuv420_output = true;
		stream = create_validate_stream_क्रम_sink(aconnector, drm_mode,
						dm_state, old_stream);
		aconnector->क्रमce_yuv420_output = false;
	पूर्ण

	वापस stream;
पूर्ण

क्रमागत drm_mode_status amdgpu_dm_connector_mode_valid(काष्ठा drm_connector *connector,
				   काष्ठा drm_display_mode *mode)
अणु
	पूर्णांक result = MODE_ERROR;
	काष्ठा dc_sink *dc_sink;
	/* TODO: Unhardcode stream count */
	काष्ठा dc_stream_state *stream;
	काष्ठा amdgpu_dm_connector *aconnector = to_amdgpu_dm_connector(connector);

	अगर ((mode->flags & DRM_MODE_FLAG_INTERLACE) ||
			(mode->flags & DRM_MODE_FLAG_DBLSCAN))
		वापस result;

	/*
	 * Only run this the first समय mode_valid is called to initilialize
	 * EDID mgmt
	 */
	अगर (aconnector->base.क्रमce != DRM_FORCE_UNSPECIFIED &&
		!aconnector->dc_em_sink)
		handle_edid_mgmt(aconnector);

	dc_sink = to_amdgpu_dm_connector(connector)->dc_sink;

	अगर (dc_sink == शून्य && aconnector->base.क्रमce != DRM_FORCE_ON_DIGITAL &&
				aconnector->base.क्रमce != DRM_FORCE_ON) अणु
		DRM_ERROR("dc_sink is NULL!\n");
		जाओ fail;
	पूर्ण

	stream = create_validate_stream_क्रम_sink(aconnector, mode, शून्य, शून्य);
	अगर (stream) अणु
		dc_stream_release(stream);
		result = MODE_OK;
	पूर्ण

fail:
	/* TODO: error handling*/
	वापस result;
पूर्ण

अटल पूर्णांक fill_hdr_info_packet(स्थिर काष्ठा drm_connector_state *state,
				काष्ठा dc_info_packet *out)
अणु
	काष्ठा hdmi_drm_infoframe frame;
	अचिन्हित अक्षर buf[30]; /* 26 + 4 */
	sमाप_प्रकार len;
	पूर्णांक ret, i;

	स_रखो(out, 0, माप(*out));

	अगर (!state->hdr_output_metadata)
		वापस 0;

	ret = drm_hdmi_infoframe_set_hdr_metadata(&frame, state);
	अगर (ret)
		वापस ret;

	len = hdmi_drm_infoframe_pack_only(&frame, buf, माप(buf));
	अगर (len < 0)
		वापस (पूर्णांक)len;

	/* Static metadata is a fixed 26 bytes + 4 byte header. */
	अगर (len != 30)
		वापस -EINVAL;

	/* Prepare the infopacket क्रम DC. */
	चयन (state->connector->connector_type) अणु
	हाल DRM_MODE_CONNECTOR_HDMIA:
		out->hb0 = 0x87; /* type */
		out->hb1 = 0x01; /* version */
		out->hb2 = 0x1A; /* length */
		out->sb[0] = buf[3]; /* checksum */
		i = 1;
		अवरोध;

	हाल DRM_MODE_CONNECTOR_DisplayPort:
	हाल DRM_MODE_CONNECTOR_eDP:
		out->hb0 = 0x00; /* sdp id, zero */
		out->hb1 = 0x87; /* type */
		out->hb2 = 0x1D; /* payload len - 1 */
		out->hb3 = (0x13 << 2); /* sdp version */
		out->sb[0] = 0x01; /* version */
		out->sb[1] = 0x1A; /* length */
		i = 2;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	स_नकल(&out->sb[i], &buf[4], 26);
	out->valid = true;

	prपूर्णांक_hex_dump(KERN_DEBUG, "HDR SB:", DUMP_PREFIX_NONE, 16, 1, out->sb,
		       माप(out->sb), false);

	वापस 0;
पूर्ण

अटल bool
is_hdr_metadata_dअगरferent(स्थिर काष्ठा drm_connector_state *old_state,
			  स्थिर काष्ठा drm_connector_state *new_state)
अणु
	काष्ठा drm_property_blob *old_blob = old_state->hdr_output_metadata;
	काष्ठा drm_property_blob *new_blob = new_state->hdr_output_metadata;

	अगर (old_blob != new_blob) अणु
		अगर (old_blob && new_blob &&
		    old_blob->length == new_blob->length)
			वापस स_भेद(old_blob->data, new_blob->data,
				      old_blob->length);

		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक
amdgpu_dm_connector_atomic_check(काष्ठा drm_connector *conn,
				 काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_connector_state *new_con_state =
		drm_atomic_get_new_connector_state(state, conn);
	काष्ठा drm_connector_state *old_con_state =
		drm_atomic_get_old_connector_state(state, conn);
	काष्ठा drm_crtc *crtc = new_con_state->crtc;
	काष्ठा drm_crtc_state *new_crtc_state;
	पूर्णांक ret;

	trace_amdgpu_dm_connector_atomic_check(new_con_state);

	अगर (!crtc)
		वापस 0;

	अगर (is_hdr_metadata_dअगरferent(old_con_state, new_con_state)) अणु
		काष्ठा dc_info_packet hdr_infopacket;

		ret = fill_hdr_info_packet(new_con_state, &hdr_infopacket);
		अगर (ret)
			वापस ret;

		new_crtc_state = drm_atomic_get_crtc_state(state, crtc);
		अगर (IS_ERR(new_crtc_state))
			वापस PTR_ERR(new_crtc_state);

		/*
		 * DC considers the stream backends changed अगर the
		 * अटल metadata changes. Forcing the modeset also
		 * gives a simple way क्रम userspace to चयन from
		 * 8bpc to 10bpc when setting the metadata to enter
		 * or निकास HDR.
		 *
		 * Changing the अटल metadata after it's been
		 * set is permissible, however. So only क्रमce a
		 * modeset अगर we're entering or निकासing HDR.
		 */
		new_crtc_state->mode_changed =
			!old_con_state->hdr_output_metadata ||
			!new_con_state->hdr_output_metadata;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs
amdgpu_dm_connector_helper_funcs = अणु
	/*
	 * If hotplugging a second bigger display in FB Con mode, bigger resolution
	 * modes will be filtered by drm_mode_validate_size(), and those modes
	 * are missing after user start lightdm. So we need to renew modes list.
	 * in get_modes call back, not just वापस the modes count
	 */
	.get_modes = get_modes,
	.mode_valid = amdgpu_dm_connector_mode_valid,
	.atomic_check = amdgpu_dm_connector_atomic_check,
पूर्ण;

अटल व्योम dm_crtc_helper_disable(काष्ठा drm_crtc *crtc)
अणु
पूर्ण

अटल पूर्णांक count_crtc_active_planes(काष्ठा drm_crtc_state *new_crtc_state)
अणु
	काष्ठा drm_atomic_state *state = new_crtc_state->state;
	काष्ठा drm_plane *plane;
	पूर्णांक num_active = 0;

	drm_क्रम_each_plane_mask(plane, state->dev, new_crtc_state->plane_mask) अणु
		काष्ठा drm_plane_state *new_plane_state;

		/* Cursor planes are "fake". */
		अगर (plane->type == DRM_PLANE_TYPE_CURSOR)
			जारी;

		new_plane_state = drm_atomic_get_new_plane_state(state, plane);

		अगर (!new_plane_state) अणु
			/*
			 * The plane is enable on the CRTC and hasn't changed
			 * state. This means that it previously passed
			 * validation and is thereक्रमe enabled.
			 */
			num_active += 1;
			जारी;
		पूर्ण

		/* We need a framebuffer to be considered enabled. */
		num_active += (new_plane_state->fb != शून्य);
	पूर्ण

	वापस num_active;
पूर्ण

अटल व्योम dm_update_crtc_active_planes(काष्ठा drm_crtc *crtc,
					 काष्ठा drm_crtc_state *new_crtc_state)
अणु
	काष्ठा dm_crtc_state *dm_new_crtc_state =
		to_dm_crtc_state(new_crtc_state);

	dm_new_crtc_state->active_planes = 0;

	अगर (!dm_new_crtc_state->stream)
		वापस;

	dm_new_crtc_state->active_planes =
		count_crtc_active_planes(new_crtc_state);
पूर्ण

अटल पूर्णांक dm_crtc_helper_atomic_check(काष्ठा drm_crtc *crtc,
				       काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state = drm_atomic_get_new_crtc_state(state,
									  crtc);
	काष्ठा amdgpu_device *adev = drm_to_adev(crtc->dev);
	काष्ठा dc *dc = adev->dm.dc;
	काष्ठा dm_crtc_state *dm_crtc_state = to_dm_crtc_state(crtc_state);
	पूर्णांक ret = -EINVAL;

	trace_amdgpu_dm_crtc_atomic_check(crtc_state);

	dm_update_crtc_active_planes(crtc, crtc_state);

	अगर (unlikely(!dm_crtc_state->stream &&
		     modeset_required(crtc_state, शून्य, dm_crtc_state->stream))) अणु
		WARN_ON(1);
		वापस ret;
	पूर्ण

	/*
	 * We require the primary plane to be enabled whenever the CRTC is, otherwise
	 * drm_mode_cursor_universal may end up trying to enable the cursor plane जबतक all other
	 * planes are disabled, which is not supported by the hardware. And there is legacy
	 * userspace which stops using the HW cursor altogether in response to the resulting EINVAL.
	 */
	अगर (crtc_state->enable &&
	    !(crtc_state->plane_mask & drm_plane_mask(crtc->primary))) अणु
		DRM_DEBUG_ATOMIC("Can't enable a CRTC without enabling the primary plane\n");
		वापस -EINVAL;
	पूर्ण

	/* In some use हालs, like reset, no stream is attached */
	अगर (!dm_crtc_state->stream)
		वापस 0;

	अगर (dc_validate_stream(dc, dm_crtc_state->stream) == DC_OK)
		वापस 0;

	DRM_DEBUG_ATOMIC("Failed DC stream validation\n");
	वापस ret;
पूर्ण

अटल bool dm_crtc_helper_mode_fixup(काष्ठा drm_crtc *crtc,
				      स्थिर काष्ठा drm_display_mode *mode,
				      काष्ठा drm_display_mode *adjusted_mode)
अणु
	वापस true;
पूर्ण

अटल स्थिर काष्ठा drm_crtc_helper_funcs amdgpu_dm_crtc_helper_funcs = अणु
	.disable = dm_crtc_helper_disable,
	.atomic_check = dm_crtc_helper_atomic_check,
	.mode_fixup = dm_crtc_helper_mode_fixup,
	.get_scanout_position = amdgpu_crtc_get_scanout_position,
पूर्ण;

अटल व्योम dm_encoder_helper_disable(काष्ठा drm_encoder *encoder)
अणु

पूर्ण

अटल पूर्णांक convert_dc_color_depth_पूर्णांकo_bpc (क्रमागत dc_color_depth display_color_depth)
अणु
	चयन (display_color_depth) अणु
		हाल COLOR_DEPTH_666:
			वापस 6;
		हाल COLOR_DEPTH_888:
			वापस 8;
		हाल COLOR_DEPTH_101010:
			वापस 10;
		हाल COLOR_DEPTH_121212:
			वापस 12;
		हाल COLOR_DEPTH_141414:
			वापस 14;
		हाल COLOR_DEPTH_161616:
			वापस 16;
		शेष:
			अवरोध;
		पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dm_encoder_helper_atomic_check(काष्ठा drm_encoder *encoder,
					  काष्ठा drm_crtc_state *crtc_state,
					  काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_atomic_state *state = crtc_state->state;
	काष्ठा drm_connector *connector = conn_state->connector;
	काष्ठा amdgpu_dm_connector *aconnector = to_amdgpu_dm_connector(connector);
	काष्ठा dm_connector_state *dm_new_connector_state = to_dm_connector_state(conn_state);
	स्थिर काष्ठा drm_display_mode *adjusted_mode = &crtc_state->adjusted_mode;
	काष्ठा drm_dp_mst_topology_mgr *mst_mgr;
	काष्ठा drm_dp_mst_port *mst_port;
	क्रमागत dc_color_depth color_depth;
	पूर्णांक घड़ी, bpp = 0;
	bool is_y420 = false;

	अगर (!aconnector->port || !aconnector->dc_sink)
		वापस 0;

	mst_port = aconnector->port;
	mst_mgr = &aconnector->mst_port->mst_mgr;

	अगर (!crtc_state->connectors_changed && !crtc_state->mode_changed)
		वापस 0;

	अगर (!state->duplicated) अणु
		पूर्णांक max_bpc = conn_state->max_requested_bpc;
		is_y420 = drm_mode_is_420_also(&connector->display_info, adjusted_mode) &&
				aconnector->क्रमce_yuv420_output;
		color_depth = convert_color_depth_from_display_info(connector,
								    is_y420,
								    max_bpc);
		bpp = convert_dc_color_depth_पूर्णांकo_bpc(color_depth) * 3;
		घड़ी = adjusted_mode->घड़ी;
		dm_new_connector_state->pbn = drm_dp_calc_pbn_mode(घड़ी, bpp, false);
	पूर्ण
	dm_new_connector_state->vcpi_slots = drm_dp_atomic_find_vcpi_slots(state,
									   mst_mgr,
									   mst_port,
									   dm_new_connector_state->pbn,
									   dm_mst_get_pbn_भागider(aconnector->dc_link));
	अगर (dm_new_connector_state->vcpi_slots < 0) अणु
		DRM_DEBUG_ATOMIC("failed finding vcpi slots: %d\n", (पूर्णांक)dm_new_connector_state->vcpi_slots);
		वापस dm_new_connector_state->vcpi_slots;
	पूर्ण
	वापस 0;
पूर्ण

स्थिर काष्ठा drm_encoder_helper_funcs amdgpu_dm_encoder_helper_funcs = अणु
	.disable = dm_encoder_helper_disable,
	.atomic_check = dm_encoder_helper_atomic_check
पूर्ण;

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
अटल पूर्णांक dm_update_mst_vcpi_slots_क्रम_dsc(काष्ठा drm_atomic_state *state,
					    काष्ठा dc_state *dc_state)
अणु
	काष्ठा dc_stream_state *stream = शून्य;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_state *new_con_state, *old_con_state;
	काष्ठा amdgpu_dm_connector *aconnector;
	काष्ठा dm_connector_state *dm_conn_state;
	पूर्णांक i, j, घड़ी, bpp;
	पूर्णांक vcpi, pbn_भाग, pbn = 0;

	क्रम_each_oldnew_connector_in_state(state, connector, old_con_state, new_con_state, i) अणु

		aconnector = to_amdgpu_dm_connector(connector);

		अगर (!aconnector->port)
			जारी;

		अगर (!new_con_state || !new_con_state->crtc)
			जारी;

		dm_conn_state = to_dm_connector_state(new_con_state);

		क्रम (j = 0; j < dc_state->stream_count; j++) अणु
			stream = dc_state->streams[j];
			अगर (!stream)
				जारी;

			अगर ((काष्ठा amdgpu_dm_connector*)stream->dm_stream_context == aconnector)
				अवरोध;

			stream = शून्य;
		पूर्ण

		अगर (!stream)
			जारी;

		अगर (stream->timing.flags.DSC != 1) अणु
			drm_dp_mst_atomic_enable_dsc(state,
						     aconnector->port,
						     dm_conn_state->pbn,
						     0,
						     false);
			जारी;
		पूर्ण

		pbn_भाग = dm_mst_get_pbn_भागider(stream->link);
		bpp = stream->timing.dsc_cfg.bits_per_pixel;
		घड़ी = stream->timing.pix_clk_100hz / 10;
		pbn = drm_dp_calc_pbn_mode(घड़ी, bpp, true);
		vcpi = drm_dp_mst_atomic_enable_dsc(state,
						    aconnector->port,
						    pbn, pbn_भाग,
						    true);
		अगर (vcpi < 0)
			वापस vcpi;

		dm_conn_state->pbn = pbn;
		dm_conn_state->vcpi_slots = vcpi;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम dm_drm_plane_reset(काष्ठा drm_plane *plane)
अणु
	काष्ठा dm_plane_state *amdgpu_state = शून्य;

	अगर (plane->state)
		plane->funcs->atomic_destroy_state(plane, plane->state);

	amdgpu_state = kzalloc(माप(*amdgpu_state), GFP_KERNEL);
	WARN_ON(amdgpu_state == शून्य);

	अगर (amdgpu_state)
		__drm_atomic_helper_plane_reset(plane, &amdgpu_state->base);
पूर्ण

अटल काष्ठा drm_plane_state *
dm_drm_plane_duplicate_state(काष्ठा drm_plane *plane)
अणु
	काष्ठा dm_plane_state *dm_plane_state, *old_dm_plane_state;

	old_dm_plane_state = to_dm_plane_state(plane->state);
	dm_plane_state = kzalloc(माप(*dm_plane_state), GFP_KERNEL);
	अगर (!dm_plane_state)
		वापस शून्य;

	__drm_atomic_helper_plane_duplicate_state(plane, &dm_plane_state->base);

	अगर (old_dm_plane_state->dc_state) अणु
		dm_plane_state->dc_state = old_dm_plane_state->dc_state;
		dc_plane_state_retain(dm_plane_state->dc_state);
	पूर्ण

	वापस &dm_plane_state->base;
पूर्ण

अटल व्योम dm_drm_plane_destroy_state(काष्ठा drm_plane *plane,
				काष्ठा drm_plane_state *state)
अणु
	काष्ठा dm_plane_state *dm_plane_state = to_dm_plane_state(state);

	अगर (dm_plane_state->dc_state)
		dc_plane_state_release(dm_plane_state->dc_state);

	drm_atomic_helper_plane_destroy_state(plane, state);
पूर्ण

अटल स्थिर काष्ठा drm_plane_funcs dm_plane_funcs = अणु
	.update_plane	= drm_atomic_helper_update_plane,
	.disable_plane	= drm_atomic_helper_disable_plane,
	.destroy	= drm_primary_helper_destroy,
	.reset = dm_drm_plane_reset,
	.atomic_duplicate_state = dm_drm_plane_duplicate_state,
	.atomic_destroy_state = dm_drm_plane_destroy_state,
	.क्रमmat_mod_supported = dm_plane_क्रमmat_mod_supported,
पूर्ण;

अटल पूर्णांक dm_plane_helper_prepare_fb(काष्ठा drm_plane *plane,
				      काष्ठा drm_plane_state *new_state)
अणु
	काष्ठा amdgpu_framebuffer *afb;
	काष्ठा drm_gem_object *obj;
	काष्ठा amdgpu_device *adev;
	काष्ठा amdgpu_bo *rbo;
	काष्ठा dm_plane_state *dm_plane_state_new, *dm_plane_state_old;
	काष्ठा list_head list;
	काष्ठा tपंचांग_validate_buffer tv;
	काष्ठा ww_acquire_ctx ticket;
	uपूर्णांक32_t करोमुख्य;
	पूर्णांक r;

	अगर (!new_state->fb) अणु
		DRM_DEBUG_KMS("No FB bound\n");
		वापस 0;
	पूर्ण

	afb = to_amdgpu_framebuffer(new_state->fb);
	obj = new_state->fb->obj[0];
	rbo = gem_to_amdgpu_bo(obj);
	adev = amdgpu_tपंचांग_adev(rbo->tbo.bdev);
	INIT_LIST_HEAD(&list);

	tv.bo = &rbo->tbo;
	tv.num_shared = 1;
	list_add(&tv.head, &list);

	r = tपंचांग_eu_reserve_buffers(&ticket, &list, false, शून्य);
	अगर (r) अणु
		dev_err(adev->dev, "fail to reserve bo (%d)\n", r);
		वापस r;
	पूर्ण

	अगर (plane->type != DRM_PLANE_TYPE_CURSOR)
		करोमुख्य = amdgpu_display_supported_करोमुख्यs(adev, rbo->flags);
	अन्यथा
		करोमुख्य = AMDGPU_GEM_DOMAIN_VRAM;

	r = amdgpu_bo_pin(rbo, करोमुख्य);
	अगर (unlikely(r != 0)) अणु
		अगर (r != -ERESTARTSYS)
			DRM_ERROR("Failed to pin framebuffer with error %d\n", r);
		tपंचांग_eu_backoff_reservation(&ticket, &list);
		वापस r;
	पूर्ण

	r = amdgpu_tपंचांग_alloc_gart(&rbo->tbo);
	अगर (unlikely(r != 0)) अणु
		amdgpu_bo_unpin(rbo);
		tपंचांग_eu_backoff_reservation(&ticket, &list);
		DRM_ERROR("%p bind failed\n", rbo);
		वापस r;
	पूर्ण

	tपंचांग_eu_backoff_reservation(&ticket, &list);

	afb->address = amdgpu_bo_gpu_offset(rbo);

	amdgpu_bo_ref(rbo);

	/**
	 * We करोn't करो surface updates on planes that have been newly created,
	 * but we also करोn't have the afb->address during atomic check.
	 *
	 * Fill in buffer attributes depending on the address here, but only on
	 * newly created planes since they're not being used by DC yet and this
	 * won't modअगरy global state.
	 */
	dm_plane_state_old = to_dm_plane_state(plane->state);
	dm_plane_state_new = to_dm_plane_state(new_state);

	अगर (dm_plane_state_new->dc_state &&
	    dm_plane_state_old->dc_state != dm_plane_state_new->dc_state) अणु
		काष्ठा dc_plane_state *plane_state =
			dm_plane_state_new->dc_state;
		bool क्रमce_disable_dcc = !plane_state->dcc.enable;

		fill_plane_buffer_attributes(
			adev, afb, plane_state->क्रमmat, plane_state->rotation,
			afb->tiling_flags,
			&plane_state->tiling_info, &plane_state->plane_size,
			&plane_state->dcc, &plane_state->address,
			afb->पंचांगz_surface, क्रमce_disable_dcc);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dm_plane_helper_cleanup_fb(काष्ठा drm_plane *plane,
				       काष्ठा drm_plane_state *old_state)
अणु
	काष्ठा amdgpu_bo *rbo;
	पूर्णांक r;

	अगर (!old_state->fb)
		वापस;

	rbo = gem_to_amdgpu_bo(old_state->fb->obj[0]);
	r = amdgpu_bo_reserve(rbo, false);
	अगर (unlikely(r)) अणु
		DRM_ERROR("failed to reserve rbo before unpin\n");
		वापस;
	पूर्ण

	amdgpu_bo_unpin(rbo);
	amdgpu_bo_unreserve(rbo);
	amdgpu_bo_unref(&rbo);
पूर्ण

अटल पूर्णांक dm_plane_helper_check_state(काष्ठा drm_plane_state *state,
				       काष्ठा drm_crtc_state *new_crtc_state)
अणु
	काष्ठा drm_framebuffer *fb = state->fb;
	पूर्णांक min_करोwnscale, max_upscale;
	पूर्णांक min_scale = 0;
	पूर्णांक max_scale = पूर्णांक_उच्च;

	/* Plane enabled? Validate viewport and get scaling factors from plane caps. */
	अगर (fb && state->crtc) अणु
		/* Validate viewport to cover the हाल when only the position changes */
		अगर (state->plane->type != DRM_PLANE_TYPE_CURSOR) अणु
			पूर्णांक viewport_width = state->crtc_w;
			पूर्णांक viewport_height = state->crtc_h;

			अगर (state->crtc_x < 0)
				viewport_width += state->crtc_x;
			अन्यथा अगर (state->crtc_x + state->crtc_w > new_crtc_state->mode.crtc_hdisplay)
				viewport_width = new_crtc_state->mode.crtc_hdisplay - state->crtc_x;

			अगर (state->crtc_y < 0)
				viewport_height += state->crtc_y;
			अन्यथा अगर (state->crtc_y + state->crtc_h > new_crtc_state->mode.crtc_vdisplay)
				viewport_height = new_crtc_state->mode.crtc_vdisplay - state->crtc_y;

			अगर (viewport_width < 0 || viewport_height < 0) अणु
				DRM_DEBUG_ATOMIC("Plane completely outside of screen\n");
				वापस -EINVAL;
			पूर्ण अन्यथा अगर (viewport_width < MIN_VIEWPORT_SIZE*2) अणु /* x2 क्रम width is because of pipe-split. */
				DRM_DEBUG_ATOMIC("Viewport width %d smaller than %d\n", viewport_width, MIN_VIEWPORT_SIZE*2);
				वापस -EINVAL;
			पूर्ण अन्यथा अगर (viewport_height < MIN_VIEWPORT_SIZE) अणु
				DRM_DEBUG_ATOMIC("Viewport height %d smaller than %d\n", viewport_height, MIN_VIEWPORT_SIZE);
				वापस -EINVAL;
			पूर्ण

		पूर्ण

		/* Get min/max allowed scaling factors from plane caps. */
		get_min_max_dc_plane_scaling(state->crtc->dev, fb,
					     &min_करोwnscale, &max_upscale);
		/*
		 * Convert to drm convention: 16.16 fixed poपूर्णांक, instead of dc's
		 * 1.0 == 1000. Also drm scaling is src/dst instead of dc's
		 * dst/src, so min_scale = 1.0 / max_upscale, etc.
		 */
		min_scale = (1000 << 16) / max_upscale;
		max_scale = (1000 << 16) / min_करोwnscale;
	पूर्ण

	वापस drm_atomic_helper_check_plane_state(
		state, new_crtc_state, min_scale, max_scale, true, true);
पूर्ण

अटल पूर्णांक dm_plane_atomic_check(काष्ठा drm_plane *plane,
				 काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा amdgpu_device *adev = drm_to_adev(plane->dev);
	काष्ठा dc *dc = adev->dm.dc;
	काष्ठा dm_plane_state *dm_plane_state;
	काष्ठा dc_scaling_info scaling_info;
	काष्ठा drm_crtc_state *new_crtc_state;
	पूर्णांक ret;

	trace_amdgpu_dm_plane_atomic_check(new_plane_state);

	dm_plane_state = to_dm_plane_state(new_plane_state);

	अगर (!dm_plane_state->dc_state)
		वापस 0;

	new_crtc_state =
		drm_atomic_get_new_crtc_state(state,
					      new_plane_state->crtc);
	अगर (!new_crtc_state)
		वापस -EINVAL;

	ret = dm_plane_helper_check_state(new_plane_state, new_crtc_state);
	अगर (ret)
		वापस ret;

	ret = fill_dc_scaling_info(new_plane_state, &scaling_info);
	अगर (ret)
		वापस ret;

	अगर (dc_validate_plane(dc, dm_plane_state->dc_state) == DC_OK)
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक dm_plane_atomic_async_check(काष्ठा drm_plane *plane,
				       काष्ठा drm_atomic_state *state)
अणु
	/* Only support async updates on cursor planes. */
	अगर (plane->type != DRM_PLANE_TYPE_CURSOR)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम dm_plane_atomic_async_update(काष्ठा drm_plane *plane,
					 काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा drm_plane_state *old_state =
		drm_atomic_get_old_plane_state(state, plane);

	trace_amdgpu_dm_atomic_update_cursor(new_state);

	swap(plane->state->fb, new_state->fb);

	plane->state->src_x = new_state->src_x;
	plane->state->src_y = new_state->src_y;
	plane->state->src_w = new_state->src_w;
	plane->state->src_h = new_state->src_h;
	plane->state->crtc_x = new_state->crtc_x;
	plane->state->crtc_y = new_state->crtc_y;
	plane->state->crtc_w = new_state->crtc_w;
	plane->state->crtc_h = new_state->crtc_h;

	handle_cursor_update(plane, old_state);
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs dm_plane_helper_funcs = अणु
	.prepare_fb = dm_plane_helper_prepare_fb,
	.cleanup_fb = dm_plane_helper_cleanup_fb,
	.atomic_check = dm_plane_atomic_check,
	.atomic_async_check = dm_plane_atomic_async_check,
	.atomic_async_update = dm_plane_atomic_async_update
पूर्ण;

/*
 * TODO: these are currently initialized to rgb क्रमmats only.
 * For future use हालs we should either initialize them dynamically based on
 * plane capabilities, or initialize this array to all क्रमmats, so पूर्णांकernal drm
 * check will succeed, and let DC implement proper check
 */
अटल स्थिर uपूर्णांक32_t rgb_क्रमmats[] = अणु
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_RGBA8888,
	DRM_FORMAT_XRGB2101010,
	DRM_FORMAT_XBGR2101010,
	DRM_FORMAT_ARGB2101010,
	DRM_FORMAT_ABGR2101010,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_ABGR8888,
	DRM_FORMAT_RGB565,
पूर्ण;

अटल स्थिर uपूर्णांक32_t overlay_क्रमmats[] = अणु
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_RGBA8888,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_ABGR8888,
	DRM_FORMAT_RGB565
पूर्ण;

अटल स्थिर u32 cursor_क्रमmats[] = अणु
	DRM_FORMAT_ARGB8888
पूर्ण;

अटल पूर्णांक get_plane_क्रमmats(स्थिर काष्ठा drm_plane *plane,
			     स्थिर काष्ठा dc_plane_cap *plane_cap,
			     uपूर्णांक32_t *क्रमmats, पूर्णांक max_क्रमmats)
अणु
	पूर्णांक i, num_क्रमmats = 0;

	/*
	 * TODO: Query support क्रम each group of क्रमmats directly from
	 * DC plane caps. This will require adding more क्रमmats to the
	 * caps list.
	 */

	चयन (plane->type) अणु
	हाल DRM_PLANE_TYPE_PRIMARY:
		क्रम (i = 0; i < ARRAY_SIZE(rgb_क्रमmats); ++i) अणु
			अगर (num_क्रमmats >= max_क्रमmats)
				अवरोध;

			क्रमmats[num_क्रमmats++] = rgb_क्रमmats[i];
		पूर्ण

		अगर (plane_cap && plane_cap->pixel_क्रमmat_support.nv12)
			क्रमmats[num_क्रमmats++] = DRM_FORMAT_NV12;
		अगर (plane_cap && plane_cap->pixel_क्रमmat_support.p010)
			क्रमmats[num_क्रमmats++] = DRM_FORMAT_P010;
		अगर (plane_cap && plane_cap->pixel_क्रमmat_support.fp16) अणु
			क्रमmats[num_क्रमmats++] = DRM_FORMAT_XRGB16161616F;
			क्रमmats[num_क्रमmats++] = DRM_FORMAT_ARGB16161616F;
			क्रमmats[num_क्रमmats++] = DRM_FORMAT_XBGR16161616F;
			क्रमmats[num_क्रमmats++] = DRM_FORMAT_ABGR16161616F;
		पूर्ण
		अवरोध;

	हाल DRM_PLANE_TYPE_OVERLAY:
		क्रम (i = 0; i < ARRAY_SIZE(overlay_क्रमmats); ++i) अणु
			अगर (num_क्रमmats >= max_क्रमmats)
				अवरोध;

			क्रमmats[num_क्रमmats++] = overlay_क्रमmats[i];
		पूर्ण
		अवरोध;

	हाल DRM_PLANE_TYPE_CURSOR:
		क्रम (i = 0; i < ARRAY_SIZE(cursor_क्रमmats); ++i) अणु
			अगर (num_क्रमmats >= max_क्रमmats)
				अवरोध;

			क्रमmats[num_क्रमmats++] = cursor_क्रमmats[i];
		पूर्ण
		अवरोध;
	पूर्ण

	वापस num_क्रमmats;
पूर्ण

अटल पूर्णांक amdgpu_dm_plane_init(काष्ठा amdgpu_display_manager *dm,
				काष्ठा drm_plane *plane,
				अचिन्हित दीर्घ possible_crtcs,
				स्थिर काष्ठा dc_plane_cap *plane_cap)
अणु
	uपूर्णांक32_t क्रमmats[32];
	पूर्णांक num_क्रमmats;
	पूर्णांक res = -EPERM;
	अचिन्हित पूर्णांक supported_rotations;
	uपूर्णांक64_t *modअगरiers = शून्य;

	num_क्रमmats = get_plane_क्रमmats(plane, plane_cap, क्रमmats,
					ARRAY_SIZE(क्रमmats));

	res = get_plane_modअगरiers(dm->adev, plane->type, &modअगरiers);
	अगर (res)
		वापस res;

	res = drm_universal_plane_init(adev_to_drm(dm->adev), plane, possible_crtcs,
				       &dm_plane_funcs, क्रमmats, num_क्रमmats,
				       modअगरiers, plane->type, शून्य);
	kमुक्त(modअगरiers);
	अगर (res)
		वापस res;

	अगर (plane->type == DRM_PLANE_TYPE_OVERLAY &&
	    plane_cap && plane_cap->per_pixel_alpha) अणु
		अचिन्हित पूर्णांक blend_caps = BIT(DRM_MODE_BLEND_PIXEL_NONE) |
					  BIT(DRM_MODE_BLEND_PREMULTI);

		drm_plane_create_alpha_property(plane);
		drm_plane_create_blend_mode_property(plane, blend_caps);
	पूर्ण

	अगर (plane->type == DRM_PLANE_TYPE_PRIMARY &&
	    plane_cap &&
	    (plane_cap->pixel_क्रमmat_support.nv12 ||
	     plane_cap->pixel_क्रमmat_support.p010)) अणु
		/* This only affects YUV क्रमmats. */
		drm_plane_create_color_properties(
			plane,
			BIT(DRM_COLOR_YCBCR_BT601) |
			BIT(DRM_COLOR_YCBCR_BT709) |
			BIT(DRM_COLOR_YCBCR_BT2020),
			BIT(DRM_COLOR_YCBCR_LIMITED_RANGE) |
			BIT(DRM_COLOR_YCBCR_FULL_RANGE),
			DRM_COLOR_YCBCR_BT709, DRM_COLOR_YCBCR_LIMITED_RANGE);
	पूर्ण

	supported_rotations =
		DRM_MODE_ROTATE_0 | DRM_MODE_ROTATE_90 |
		DRM_MODE_ROTATE_180 | DRM_MODE_ROTATE_270;

	अगर (dm->adev->asic_type >= CHIP_BONAIRE &&
	    plane->type != DRM_PLANE_TYPE_CURSOR)
		drm_plane_create_rotation_property(plane, DRM_MODE_ROTATE_0,
						   supported_rotations);

	drm_plane_helper_add(plane, &dm_plane_helper_funcs);

	/* Create (reset) the plane state */
	अगर (plane->funcs->reset)
		plane->funcs->reset(plane);

	वापस 0;
पूर्ण

अटल पूर्णांक amdgpu_dm_crtc_init(काष्ठा amdgpu_display_manager *dm,
			       काष्ठा drm_plane *plane,
			       uपूर्णांक32_t crtc_index)
अणु
	काष्ठा amdgpu_crtc *acrtc = शून्य;
	काष्ठा drm_plane *cursor_plane;

	पूर्णांक res = -ENOMEM;

	cursor_plane = kzalloc(माप(*cursor_plane), GFP_KERNEL);
	अगर (!cursor_plane)
		जाओ fail;

	cursor_plane->type = DRM_PLANE_TYPE_CURSOR;
	res = amdgpu_dm_plane_init(dm, cursor_plane, 0, शून्य);

	acrtc = kzalloc(माप(काष्ठा amdgpu_crtc), GFP_KERNEL);
	अगर (!acrtc)
		जाओ fail;

	res = drm_crtc_init_with_planes(
			dm->ddev,
			&acrtc->base,
			plane,
			cursor_plane,
			&amdgpu_dm_crtc_funcs, शून्य);

	अगर (res)
		जाओ fail;

	drm_crtc_helper_add(&acrtc->base, &amdgpu_dm_crtc_helper_funcs);

	/* Create (reset) the plane state */
	अगर (acrtc->base.funcs->reset)
		acrtc->base.funcs->reset(&acrtc->base);

	acrtc->max_cursor_width = dm->adev->dm.dc->caps.max_cursor_size;
	acrtc->max_cursor_height = dm->adev->dm.dc->caps.max_cursor_size;

	acrtc->crtc_id = crtc_index;
	acrtc->base.enabled = false;
	acrtc->otg_inst = -1;

	dm->adev->mode_info.crtcs[crtc_index] = acrtc;
	drm_crtc_enable_color_mgmt(&acrtc->base, MAX_COLOR_LUT_ENTRIES,
				   true, MAX_COLOR_LUT_ENTRIES);
	drm_mode_crtc_set_gamma_size(&acrtc->base, MAX_COLOR_LEGACY_LUT_ENTRIES);

	वापस 0;

fail:
	kमुक्त(acrtc);
	kमुक्त(cursor_plane);
	वापस res;
पूर्ण


अटल पूर्णांक to_drm_connector_type(क्रमागत संकेत_type st)
अणु
	चयन (st) अणु
	हाल SIGNAL_TYPE_HDMI_TYPE_A:
		वापस DRM_MODE_CONNECTOR_HDMIA;
	हाल SIGNAL_TYPE_EDP:
		वापस DRM_MODE_CONNECTOR_eDP;
	हाल SIGNAL_TYPE_LVDS:
		वापस DRM_MODE_CONNECTOR_LVDS;
	हाल SIGNAL_TYPE_RGB:
		वापस DRM_MODE_CONNECTOR_VGA;
	हाल SIGNAL_TYPE_DISPLAY_PORT:
	हाल SIGNAL_TYPE_DISPLAY_PORT_MST:
		वापस DRM_MODE_CONNECTOR_DisplayPort;
	हाल SIGNAL_TYPE_DVI_DUAL_LINK:
	हाल SIGNAL_TYPE_DVI_SINGLE_LINK:
		वापस DRM_MODE_CONNECTOR_DVID;
	हाल SIGNAL_TYPE_VIRTUAL:
		वापस DRM_MODE_CONNECTOR_VIRTUAL;

	शेष:
		वापस DRM_MODE_CONNECTOR_Unknown;
	पूर्ण
पूर्ण

अटल काष्ठा drm_encoder *amdgpu_dm_connector_to_encoder(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_encoder *encoder;

	/* There is only one encoder per connector */
	drm_connector_क्रम_each_possible_encoder(connector, encoder)
		वापस encoder;

	वापस शून्य;
पूर्ण

अटल व्योम amdgpu_dm_get_native_mode(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_encoder *encoder;
	काष्ठा amdgpu_encoder *amdgpu_encoder;

	encoder = amdgpu_dm_connector_to_encoder(connector);

	अगर (encoder == शून्य)
		वापस;

	amdgpu_encoder = to_amdgpu_encoder(encoder);

	amdgpu_encoder->native_mode.घड़ी = 0;

	अगर (!list_empty(&connector->probed_modes)) अणु
		काष्ठा drm_display_mode *preferred_mode = शून्य;

		list_क्रम_each_entry(preferred_mode,
				    &connector->probed_modes,
				    head) अणु
			अगर (preferred_mode->type & DRM_MODE_TYPE_PREFERRED)
				amdgpu_encoder->native_mode = *preferred_mode;

			अवरोध;
		पूर्ण

	पूर्ण
पूर्ण

अटल काष्ठा drm_display_mode *
amdgpu_dm_create_common_mode(काष्ठा drm_encoder *encoder,
			     अक्षर *name,
			     पूर्णांक hdisplay, पूर्णांक vdisplay)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	काष्ठा drm_display_mode *mode = शून्य;
	काष्ठा drm_display_mode *native_mode = &amdgpu_encoder->native_mode;

	mode = drm_mode_duplicate(dev, native_mode);

	अगर (mode == शून्य)
		वापस शून्य;

	mode->hdisplay = hdisplay;
	mode->vdisplay = vdisplay;
	mode->type &= ~DRM_MODE_TYPE_PREFERRED;
	strscpy(mode->name, name, DRM_DISPLAY_MODE_LEN);

	वापस mode;

पूर्ण

अटल व्योम amdgpu_dm_connector_add_common_modes(काष्ठा drm_encoder *encoder,
						 काष्ठा drm_connector *connector)
अणु
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	काष्ठा drm_display_mode *mode = शून्य;
	काष्ठा drm_display_mode *native_mode = &amdgpu_encoder->native_mode;
	काष्ठा amdgpu_dm_connector *amdgpu_dm_connector =
				to_amdgpu_dm_connector(connector);
	पूर्णांक i;
	पूर्णांक n;
	काष्ठा mode_size अणु
		अक्षर name[DRM_DISPLAY_MODE_LEN];
		पूर्णांक w;
		पूर्णांक h;
	पूर्ण common_modes[] = अणु
		अणु  "640x480",  640,  480पूर्ण,
		अणु  "800x600",  800,  600पूर्ण,
		अणु "1024x768", 1024,  768पूर्ण,
		अणु "1280x720", 1280,  720पूर्ण,
		अणु "1280x800", 1280,  800पूर्ण,
		अणु"1280x1024", 1280, 1024पूर्ण,
		अणु "1440x900", 1440,  900पूर्ण,
		अणु"1680x1050", 1680, 1050पूर्ण,
		अणु"1600x1200", 1600, 1200पूर्ण,
		अणु"1920x1080", 1920, 1080पूर्ण,
		अणु"1920x1200", 1920, 1200पूर्ण
	पूर्ण;

	n = ARRAY_SIZE(common_modes);

	क्रम (i = 0; i < n; i++) अणु
		काष्ठा drm_display_mode *curmode = शून्य;
		bool mode_existed = false;

		अगर (common_modes[i].w > native_mode->hdisplay ||
		    common_modes[i].h > native_mode->vdisplay ||
		   (common_modes[i].w == native_mode->hdisplay &&
		    common_modes[i].h == native_mode->vdisplay))
			जारी;

		list_क्रम_each_entry(curmode, &connector->probed_modes, head) अणु
			अगर (common_modes[i].w == curmode->hdisplay &&
			    common_modes[i].h == curmode->vdisplay) अणु
				mode_existed = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (mode_existed)
			जारी;

		mode = amdgpu_dm_create_common_mode(encoder,
				common_modes[i].name, common_modes[i].w,
				common_modes[i].h);
		drm_mode_probed_add(connector, mode);
		amdgpu_dm_connector->num_modes++;
	पूर्ण
पूर्ण

अटल व्योम amdgpu_dm_connector_ddc_get_modes(काष्ठा drm_connector *connector,
					      काष्ठा edid *edid)
अणु
	काष्ठा amdgpu_dm_connector *amdgpu_dm_connector =
			to_amdgpu_dm_connector(connector);

	अगर (edid) अणु
		/* empty probed_modes */
		INIT_LIST_HEAD(&connector->probed_modes);
		amdgpu_dm_connector->num_modes =
				drm_add_edid_modes(connector, edid);

		/* sorting the probed modes beक्रमe calling function
		 * amdgpu_dm_get_native_mode() since EDID can have
		 * more than one preferred mode. The modes that are
		 * later in the probed mode list could be of higher
		 * and preferred resolution. For example, 3840x2160
		 * resolution in base EDID preferred timing and 4096x2160
		 * preferred resolution in DID extension block later.
		 */
		drm_mode_sort(&connector->probed_modes);
		amdgpu_dm_get_native_mode(connector);

		/* Freesync capabilities are reset by calling
		 * drm_add_edid_modes() and need to be
		 * restored here.
		 */
		amdgpu_dm_update_मुक्तsync_caps(connector, edid);
	पूर्ण अन्यथा अणु
		amdgpu_dm_connector->num_modes = 0;
	पूर्ण
पूर्ण

अटल bool is_duplicate_mode(काष्ठा amdgpu_dm_connector *aconnector,
			      काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_display_mode *m;

	list_क्रम_each_entry (m, &aconnector->base.probed_modes, head) अणु
		अगर (drm_mode_equal(m, mode))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल uपूर्णांक add_fs_modes(काष्ठा amdgpu_dm_connector *aconnector)
अणु
	स्थिर काष्ठा drm_display_mode *m;
	काष्ठा drm_display_mode *new_mode;
	uपूर्णांक i;
	uपूर्णांक32_t new_modes_count = 0;

	/* Standard FPS values
	 *
	 * 23.976   - TV/NTSC
	 * 24 	    - Cinema
	 * 25 	    - TV/PAL
	 * 29.97    - TV/NTSC
	 * 30 	    - TV/NTSC
	 * 48 	    - Cinema HFR
	 * 50 	    - TV/PAL
	 * 60 	    - Commonly used
	 * 48,72,96 - Multiples of 24
	 */
	स्थिर uपूर्णांक32_t common_rates[] = अणु 23976, 24000, 25000, 29970, 30000,
					 48000, 50000, 60000, 72000, 96000 पूर्ण;

	/*
	 * Find mode with highest refresh rate with the same resolution
	 * as the preferred mode. Some monitors report a preferred mode
	 * with lower resolution than the highest refresh rate supported.
	 */

	m = get_highest_refresh_rate_mode(aconnector, true);
	अगर (!m)
		वापस 0;

	क्रम (i = 0; i < ARRAY_SIZE(common_rates); i++) अणु
		uपूर्णांक64_t target_vtotal, target_vtotal_dअगरf;
		uपूर्णांक64_t num, den;

		अगर (drm_mode_vrefresh(m) * 1000 < common_rates[i])
			जारी;

		अगर (common_rates[i] < aconnector->min_vfreq * 1000 ||
		    common_rates[i] > aconnector->max_vfreq * 1000)
			जारी;

		num = (अचिन्हित दीर्घ दीर्घ)m->घड़ी * 1000 * 1000;
		den = common_rates[i] * (अचिन्हित दीर्घ दीर्घ)m->htotal;
		target_vtotal = भाग_u64(num, den);
		target_vtotal_dअगरf = target_vtotal - m->vtotal;

		/* Check क्रम illegal modes */
		अगर (m->vsync_start + target_vtotal_dअगरf < m->vdisplay ||
		    m->vsync_end + target_vtotal_dअगरf < m->vsync_start ||
		    m->vtotal + target_vtotal_dअगरf < m->vsync_end)
			जारी;

		new_mode = drm_mode_duplicate(aconnector->base.dev, m);
		अगर (!new_mode)
			जाओ out;

		new_mode->vtotal += (u16)target_vtotal_dअगरf;
		new_mode->vsync_start += (u16)target_vtotal_dअगरf;
		new_mode->vsync_end += (u16)target_vtotal_dअगरf;
		new_mode->type &= ~DRM_MODE_TYPE_PREFERRED;
		new_mode->type |= DRM_MODE_TYPE_DRIVER;

		अगर (!is_duplicate_mode(aconnector, new_mode)) अणु
			drm_mode_probed_add(&aconnector->base, new_mode);
			new_modes_count += 1;
		पूर्ण अन्यथा
			drm_mode_destroy(aconnector->base.dev, new_mode);
	पूर्ण
 out:
	वापस new_modes_count;
पूर्ण

अटल व्योम amdgpu_dm_connector_add_मुक्तsync_modes(काष्ठा drm_connector *connector,
						   काष्ठा edid *edid)
अणु
	काष्ठा amdgpu_dm_connector *amdgpu_dm_connector =
		to_amdgpu_dm_connector(connector);

	अगर (!(amdgpu_मुक्तsync_vid_mode && edid))
		वापस;

	अगर (amdgpu_dm_connector->max_vfreq - amdgpu_dm_connector->min_vfreq > 10)
		amdgpu_dm_connector->num_modes +=
			add_fs_modes(amdgpu_dm_connector);
पूर्ण

अटल पूर्णांक amdgpu_dm_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा amdgpu_dm_connector *amdgpu_dm_connector =
			to_amdgpu_dm_connector(connector);
	काष्ठा drm_encoder *encoder;
	काष्ठा edid *edid = amdgpu_dm_connector->edid;

	encoder = amdgpu_dm_connector_to_encoder(connector);

	अगर (!drm_edid_is_valid(edid)) अणु
		amdgpu_dm_connector->num_modes =
				drm_add_modes_noedid(connector, 640, 480);
	पूर्ण अन्यथा अणु
		amdgpu_dm_connector_ddc_get_modes(connector, edid);
		amdgpu_dm_connector_add_common_modes(encoder, connector);
		amdgpu_dm_connector_add_मुक्तsync_modes(connector, edid);
	पूर्ण
	amdgpu_dm_fbc_init(connector);

	वापस amdgpu_dm_connector->num_modes;
पूर्ण

व्योम amdgpu_dm_connector_init_helper(काष्ठा amdgpu_display_manager *dm,
				     काष्ठा amdgpu_dm_connector *aconnector,
				     पूर्णांक connector_type,
				     काष्ठा dc_link *link,
				     पूर्णांक link_index)
अणु
	काष्ठा amdgpu_device *adev = drm_to_adev(dm->ddev);

	/*
	 * Some of the properties below require access to state, like bpc.
	 * Allocate some शेष initial connector state with our reset helper.
	 */
	अगर (aconnector->base.funcs->reset)
		aconnector->base.funcs->reset(&aconnector->base);

	aconnector->connector_id = link_index;
	aconnector->dc_link = link;
	aconnector->base.पूर्णांकerlace_allowed = false;
	aconnector->base.द्विगुनscan_allowed = false;
	aconnector->base.stereo_allowed = false;
	aconnector->base.dpms = DRM_MODE_DPMS_OFF;
	aconnector->hpd.hpd = AMDGPU_HPD_NONE; /* not used */
	aconnector->audio_inst = -1;
	mutex_init(&aconnector->hpd_lock);

	/*
	 * configure support HPD hot plug connector_>polled शेष value is 0
	 * which means HPD hot plug not supported
	 */
	चयन (connector_type) अणु
	हाल DRM_MODE_CONNECTOR_HDMIA:
		aconnector->base.polled = DRM_CONNECTOR_POLL_HPD;
		aconnector->base.ycbcr_420_allowed =
			link->link_enc->features.hdmi_ycbcr420_supported ? true : false;
		अवरोध;
	हाल DRM_MODE_CONNECTOR_DisplayPort:
		aconnector->base.polled = DRM_CONNECTOR_POLL_HPD;
		aconnector->base.ycbcr_420_allowed =
			link->link_enc->features.dp_ycbcr420_supported ? true : false;
		अवरोध;
	हाल DRM_MODE_CONNECTOR_DVID:
		aconnector->base.polled = DRM_CONNECTOR_POLL_HPD;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	drm_object_attach_property(&aconnector->base.base,
				dm->ddev->mode_config.scaling_mode_property,
				DRM_MODE_SCALE_NONE);

	drm_object_attach_property(&aconnector->base.base,
				adev->mode_info.underscan_property,
				UNDERSCAN_OFF);
	drm_object_attach_property(&aconnector->base.base,
				adev->mode_info.underscan_hborder_property,
				0);
	drm_object_attach_property(&aconnector->base.base,
				adev->mode_info.underscan_vborder_property,
				0);

	अगर (!aconnector->mst_port)
		drm_connector_attach_max_bpc_property(&aconnector->base, 8, 16);

	/* This शेषs to the max in the range, but we want 8bpc क्रम non-edp. */
	aconnector->base.state->max_bpc = (connector_type == DRM_MODE_CONNECTOR_eDP) ? 16 : 8;
	aconnector->base.state->max_requested_bpc = aconnector->base.state->max_bpc;

	अगर (connector_type == DRM_MODE_CONNECTOR_eDP &&
	    (dc_is_dmcu_initialized(adev->dm.dc) || adev->dm.dc->ctx->dmub_srv)) अणु
		drm_object_attach_property(&aconnector->base.base,
				adev->mode_info.abm_level_property, 0);
	पूर्ण

	अगर (connector_type == DRM_MODE_CONNECTOR_HDMIA ||
	    connector_type == DRM_MODE_CONNECTOR_DisplayPort ||
	    connector_type == DRM_MODE_CONNECTOR_eDP) अणु
		drm_object_attach_property(
			&aconnector->base.base,
			dm->ddev->mode_config.hdr_output_metadata_property, 0);

		अगर (!aconnector->mst_port)
			drm_connector_attach_vrr_capable_property(&aconnector->base);

#अगर_घोषित CONFIG_DRM_AMD_DC_HDCP
		अगर (adev->dm.hdcp_workqueue)
			drm_connector_attach_content_protection_property(&aconnector->base, true);
#पूर्ण_अगर
	पूर्ण
पूर्ण

अटल पूर्णांक amdgpu_dm_i2c_xfer(काष्ठा i2c_adapter *i2c_adap,
			      काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा amdgpu_i2c_adapter *i2c = i2c_get_adapdata(i2c_adap);
	काष्ठा ddc_service *ddc_service = i2c->ddc_service;
	काष्ठा i2c_command cmd;
	पूर्णांक i;
	पूर्णांक result = -EIO;

	cmd.payloads = kसुस्मृति(num, माप(काष्ठा i2c_payload), GFP_KERNEL);

	अगर (!cmd.payloads)
		वापस result;

	cmd.number_of_payloads = num;
	cmd.engine = I2C_COMMAND_ENGINE_DEFAULT;
	cmd.speed = 100;

	क्रम (i = 0; i < num; i++) अणु
		cmd.payloads[i].ग_लिखो = !(msgs[i].flags & I2C_M_RD);
		cmd.payloads[i].address = msgs[i].addr;
		cmd.payloads[i].length = msgs[i].len;
		cmd.payloads[i].data = msgs[i].buf;
	पूर्ण

	अगर (dc_submit_i2c(
			ddc_service->ctx->dc,
			ddc_service->ddc_pin->hw_info.ddc_channel,
			&cmd))
		result = num;

	kमुक्त(cmd.payloads);
	वापस result;
पूर्ण

अटल u32 amdgpu_dm_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm amdgpu_dm_i2c_algo = अणु
	.master_xfer = amdgpu_dm_i2c_xfer,
	.functionality = amdgpu_dm_i2c_func,
पूर्ण;

अटल काष्ठा amdgpu_i2c_adapter *
create_i2c(काष्ठा ddc_service *ddc_service,
	   पूर्णांक link_index,
	   पूर्णांक *res)
अणु
	काष्ठा amdgpu_device *adev = ddc_service->ctx->driver_context;
	काष्ठा amdgpu_i2c_adapter *i2c;

	i2c = kzalloc(माप(काष्ठा amdgpu_i2c_adapter), GFP_KERNEL);
	अगर (!i2c)
		वापस शून्य;
	i2c->base.owner = THIS_MODULE;
	i2c->base.class = I2C_CLASS_DDC;
	i2c->base.dev.parent = &adev->pdev->dev;
	i2c->base.algo = &amdgpu_dm_i2c_algo;
	snम_लिखो(i2c->base.name, माप(i2c->base.name), "AMDGPU DM i2c hw bus %d", link_index);
	i2c_set_adapdata(&i2c->base, i2c);
	i2c->ddc_service = ddc_service;
	i2c->ddc_service->ddc_pin->hw_info.ddc_channel = link_index;

	वापस i2c;
पूर्ण


/*
 * Note: this function assumes that dc_link_detect() was called क्रम the
 * dc_link which will be represented by this aconnector.
 */
अटल पूर्णांक amdgpu_dm_connector_init(काष्ठा amdgpu_display_manager *dm,
				    काष्ठा amdgpu_dm_connector *aconnector,
				    uपूर्णांक32_t link_index,
				    काष्ठा amdgpu_encoder *aencoder)
अणु
	पूर्णांक res = 0;
	पूर्णांक connector_type;
	काष्ठा dc *dc = dm->dc;
	काष्ठा dc_link *link = dc_get_link_at_index(dc, link_index);
	काष्ठा amdgpu_i2c_adapter *i2c;

	link->priv = aconnector;

	DRM_DEBUG_DRIVER("%s()\n", __func__);

	i2c = create_i2c(link->ddc, link->link_index, &res);
	अगर (!i2c) अणु
		DRM_ERROR("Failed to create i2c adapter data\n");
		वापस -ENOMEM;
	पूर्ण

	aconnector->i2c = i2c;
	res = i2c_add_adapter(&i2c->base);

	अगर (res) अणु
		DRM_ERROR("Failed to register hw i2c %d\n", link->link_index);
		जाओ out_मुक्त;
	पूर्ण

	connector_type = to_drm_connector_type(link->connector_संकेत);

	res = drm_connector_init_with_ddc(
			dm->ddev,
			&aconnector->base,
			&amdgpu_dm_connector_funcs,
			connector_type,
			&i2c->base);

	अगर (res) अणु
		DRM_ERROR("connector_init failed\n");
		aconnector->connector_id = -1;
		जाओ out_मुक्त;
	पूर्ण

	drm_connector_helper_add(
			&aconnector->base,
			&amdgpu_dm_connector_helper_funcs);

	amdgpu_dm_connector_init_helper(
		dm,
		aconnector,
		connector_type,
		link,
		link_index);

	drm_connector_attach_encoder(
		&aconnector->base, &aencoder->base);

	अगर (connector_type == DRM_MODE_CONNECTOR_DisplayPort
		|| connector_type == DRM_MODE_CONNECTOR_eDP)
		amdgpu_dm_initialize_dp_connector(dm, aconnector, link->link_index);

out_मुक्त:
	अगर (res) अणु
		kमुक्त(i2c);
		aconnector->i2c = शून्य;
	पूर्ण
	वापस res;
पूर्ण

पूर्णांक amdgpu_dm_get_encoder_crtc_mask(काष्ठा amdgpu_device *adev)
अणु
	चयन (adev->mode_info.num_crtc) अणु
	हाल 1:
		वापस 0x1;
	हाल 2:
		वापस 0x3;
	हाल 3:
		वापस 0x7;
	हाल 4:
		वापस 0xf;
	हाल 5:
		वापस 0x1f;
	हाल 6:
	शेष:
		वापस 0x3f;
	पूर्ण
पूर्ण

अटल पूर्णांक amdgpu_dm_encoder_init(काष्ठा drm_device *dev,
				  काष्ठा amdgpu_encoder *aencoder,
				  uपूर्णांक32_t link_index)
अणु
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);

	पूर्णांक res = drm_encoder_init(dev,
				   &aencoder->base,
				   &amdgpu_dm_encoder_funcs,
				   DRM_MODE_ENCODER_TMDS,
				   शून्य);

	aencoder->base.possible_crtcs = amdgpu_dm_get_encoder_crtc_mask(adev);

	अगर (!res)
		aencoder->encoder_id = link_index;
	अन्यथा
		aencoder->encoder_id = -1;

	drm_encoder_helper_add(&aencoder->base, &amdgpu_dm_encoder_helper_funcs);

	वापस res;
पूर्ण

अटल व्योम manage_dm_पूर्णांकerrupts(काष्ठा amdgpu_device *adev,
				 काष्ठा amdgpu_crtc *acrtc,
				 bool enable)
अणु
	/*
	 * We have no guarantee that the frontend index maps to the same
	 * backend index - some even map to more than one.
	 *
	 * TODO: Use a dअगरferent पूर्णांकerrupt or check DC itself क्रम the mapping.
	 */
	पूर्णांक irq_type =
		amdgpu_display_crtc_idx_to_irq_type(
			adev,
			acrtc->crtc_id);

	अगर (enable) अणु
		drm_crtc_vblank_on(&acrtc->base);
		amdgpu_irq_get(
			adev,
			&adev->pageflip_irq,
			irq_type);
#अगर defined(CONFIG_DRM_AMD_SECURE_DISPLAY)
		amdgpu_irq_get(
			adev,
			&adev->vline0_irq,
			irq_type);
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
#अगर defined(CONFIG_DRM_AMD_SECURE_DISPLAY)
		amdgpu_irq_put(
			adev,
			&adev->vline0_irq,
			irq_type);
#पूर्ण_अगर
		amdgpu_irq_put(
			adev,
			&adev->pageflip_irq,
			irq_type);
		drm_crtc_vblank_off(&acrtc->base);
	पूर्ण
पूर्ण

अटल व्योम dm_update_pflip_irq_state(काष्ठा amdgpu_device *adev,
				      काष्ठा amdgpu_crtc *acrtc)
अणु
	पूर्णांक irq_type =
		amdgpu_display_crtc_idx_to_irq_type(adev, acrtc->crtc_id);

	/**
	 * This पढ़ोs the current state क्रम the IRQ and क्रमce reapplies
	 * the setting to hardware.
	 */
	amdgpu_irq_update(adev, &adev->pageflip_irq, irq_type);
पूर्ण

अटल bool
is_scaling_state_dअगरferent(स्थिर काष्ठा dm_connector_state *dm_state,
			   स्थिर काष्ठा dm_connector_state *old_dm_state)
अणु
	अगर (dm_state->scaling != old_dm_state->scaling)
		वापस true;
	अगर (!dm_state->underscan_enable && old_dm_state->underscan_enable) अणु
		अगर (old_dm_state->underscan_hborder != 0 && old_dm_state->underscan_vborder != 0)
			वापस true;
	पूर्ण अन्यथा  अगर (dm_state->underscan_enable && !old_dm_state->underscan_enable) अणु
		अगर (dm_state->underscan_hborder != 0 && dm_state->underscan_vborder != 0)
			वापस true;
	पूर्ण अन्यथा अगर (dm_state->underscan_hborder != old_dm_state->underscan_hborder ||
		   dm_state->underscan_vborder != old_dm_state->underscan_vborder)
		वापस true;
	वापस false;
पूर्ण

#अगर_घोषित CONFIG_DRM_AMD_DC_HDCP
अटल bool is_content_protection_dअगरferent(काष्ठा drm_connector_state *state,
					    स्थिर काष्ठा drm_connector_state *old_state,
					    स्थिर काष्ठा drm_connector *connector, काष्ठा hdcp_workqueue *hdcp_w)
अणु
	काष्ठा amdgpu_dm_connector *aconnector = to_amdgpu_dm_connector(connector);
	काष्ठा dm_connector_state *dm_con_state = to_dm_connector_state(connector->state);

	/* Handle: Type0/1 change */
	अगर (old_state->hdcp_content_type != state->hdcp_content_type &&
	    state->content_protection != DRM_MODE_CONTENT_PROTECTION_UNDESIRED) अणु
		state->content_protection = DRM_MODE_CONTENT_PROTECTION_DESIRED;
		वापस true;
	पूर्ण

	/* CP is being re enabled, ignore this
	 *
	 * Handles:	ENABLED -> DESIRED
	 */
	अगर (old_state->content_protection == DRM_MODE_CONTENT_PROTECTION_ENABLED &&
	    state->content_protection == DRM_MODE_CONTENT_PROTECTION_DESIRED) अणु
		state->content_protection = DRM_MODE_CONTENT_PROTECTION_ENABLED;
		वापस false;
	पूर्ण

	/* S3 resume हाल, since old state will always be 0 (UNDESIRED) and the restored state will be ENABLED
	 *
	 * Handles:	UNDESIRED -> ENABLED
	 */
	अगर (old_state->content_protection == DRM_MODE_CONTENT_PROTECTION_UNDESIRED &&
	    state->content_protection == DRM_MODE_CONTENT_PROTECTION_ENABLED)
		state->content_protection = DRM_MODE_CONTENT_PROTECTION_DESIRED;

	/* Check अगर something is connected/enabled, otherwise we start hdcp but nothing is connected/enabled
	 * hot-plug, headless s3, dpms
	 *
	 * Handles:	DESIRED -> DESIRED (Special हाल)
	 */
	अगर (dm_con_state->update_hdcp && state->content_protection == DRM_MODE_CONTENT_PROTECTION_DESIRED &&
	    connector->dpms == DRM_MODE_DPMS_ON && aconnector->dc_sink != शून्य) अणु
		dm_con_state->update_hdcp = false;
		वापस true;
	पूर्ण

	/*
	 * Handles:	UNDESIRED -> UNDESIRED
	 *		DESIRED -> DESIRED
	 *		ENABLED -> ENABLED
	 */
	अगर (old_state->content_protection == state->content_protection)
		वापस false;

	/*
	 * Handles:	UNDESIRED -> DESIRED
	 *		DESIRED -> UNDESIRED
	 *		ENABLED -> UNDESIRED
	 */
	अगर (state->content_protection != DRM_MODE_CONTENT_PROTECTION_ENABLED)
		वापस true;

	/*
	 * Handles:	DESIRED -> ENABLED
	 */
	वापस false;
पूर्ण

#पूर्ण_अगर
अटल व्योम हटाओ_stream(काष्ठा amdgpu_device *adev,
			  काष्ठा amdgpu_crtc *acrtc,
			  काष्ठा dc_stream_state *stream)
अणु
	/* this is the update mode हाल */

	acrtc->otg_inst = -1;
	acrtc->enabled = false;
पूर्ण

अटल पूर्णांक get_cursor_position(काष्ठा drm_plane *plane, काष्ठा drm_crtc *crtc,
			       काष्ठा dc_cursor_position *position)
अणु
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	पूर्णांक x, y;
	पूर्णांक xorigin = 0, yorigin = 0;

	अगर (!crtc || !plane->state->fb)
		वापस 0;

	अगर ((plane->state->crtc_w > amdgpu_crtc->max_cursor_width) ||
	    (plane->state->crtc_h > amdgpu_crtc->max_cursor_height)) अणु
		DRM_ERROR("%s: bad cursor width or height %d x %d\n",
			  __func__,
			  plane->state->crtc_w,
			  plane->state->crtc_h);
		वापस -EINVAL;
	पूर्ण

	x = plane->state->crtc_x;
	y = plane->state->crtc_y;

	अगर (x <= -amdgpu_crtc->max_cursor_width ||
	    y <= -amdgpu_crtc->max_cursor_height)
		वापस 0;

	अगर (x < 0) अणु
		xorigin = min(-x, amdgpu_crtc->max_cursor_width - 1);
		x = 0;
	पूर्ण
	अगर (y < 0) अणु
		yorigin = min(-y, amdgpu_crtc->max_cursor_height - 1);
		y = 0;
	पूर्ण
	position->enable = true;
	position->translate_by_source = true;
	position->x = x;
	position->y = y;
	position->x_hotspot = xorigin;
	position->y_hotspot = yorigin;

	वापस 0;
पूर्ण

अटल व्योम handle_cursor_update(काष्ठा drm_plane *plane,
				 काष्ठा drm_plane_state *old_plane_state)
अणु
	काष्ठा amdgpu_device *adev = drm_to_adev(plane->dev);
	काष्ठा amdgpu_framebuffer *afb = to_amdgpu_framebuffer(plane->state->fb);
	काष्ठा drm_crtc *crtc = afb ? plane->state->crtc : old_plane_state->crtc;
	काष्ठा dm_crtc_state *crtc_state = crtc ? to_dm_crtc_state(crtc->state) : शून्य;
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	uपूर्णांक64_t address = afb ? afb->address : 0;
	काष्ठा dc_cursor_position position = अणु0पूर्ण;
	काष्ठा dc_cursor_attributes attributes;
	पूर्णांक ret;

	अगर (!plane->state->fb && !old_plane_state->fb)
		वापस;

	DC_LOG_CURSOR("%s: crtc_id=%d with size %d to %d\n",
		      __func__,
		      amdgpu_crtc->crtc_id,
		      plane->state->crtc_w,
		      plane->state->crtc_h);

	ret = get_cursor_position(plane, crtc, &position);
	अगर (ret)
		वापस;

	अगर (!position.enable) अणु
		/* turn off cursor */
		अगर (crtc_state && crtc_state->stream) अणु
			mutex_lock(&adev->dm.dc_lock);
			dc_stream_set_cursor_position(crtc_state->stream,
						      &position);
			mutex_unlock(&adev->dm.dc_lock);
		पूर्ण
		वापस;
	पूर्ण

	amdgpu_crtc->cursor_width = plane->state->crtc_w;
	amdgpu_crtc->cursor_height = plane->state->crtc_h;

	स_रखो(&attributes, 0, माप(attributes));
	attributes.address.high_part = upper_32_bits(address);
	attributes.address.low_part  = lower_32_bits(address);
	attributes.width             = plane->state->crtc_w;
	attributes.height            = plane->state->crtc_h;
	attributes.color_क्रमmat      = CURSOR_MODE_COLOR_PRE_MULTIPLIED_ALPHA;
	attributes.rotation_angle    = 0;
	attributes.attribute_flags.value = 0;

	attributes.pitch = afb->base.pitches[0] / afb->base.क्रमmat->cpp[0];

	अगर (crtc_state->stream) अणु
		mutex_lock(&adev->dm.dc_lock);
		अगर (!dc_stream_set_cursor_attributes(crtc_state->stream,
							 &attributes))
			DRM_ERROR("DC failed to set cursor attributes\n");

		अगर (!dc_stream_set_cursor_position(crtc_state->stream,
						   &position))
			DRM_ERROR("DC failed to set cursor position\n");
		mutex_unlock(&adev->dm.dc_lock);
	पूर्ण
पूर्ण

अटल व्योम prepare_flip_isr(काष्ठा amdgpu_crtc *acrtc)
अणु

	निश्चित_spin_locked(&acrtc->base.dev->event_lock);
	WARN_ON(acrtc->event);

	acrtc->event = acrtc->base.state->event;

	/* Set the flip status */
	acrtc->pflip_status = AMDGPU_FLIP_SUBMITTED;

	/* Mark this event as consumed */
	acrtc->base.state->event = शून्य;

	DC_LOG_PFLIP("crtc:%d, pflip_stat:AMDGPU_FLIP_SUBMITTED\n",
		     acrtc->crtc_id);
पूर्ण

अटल व्योम update_मुक्तsync_state_on_stream(
	काष्ठा amdgpu_display_manager *dm,
	काष्ठा dm_crtc_state *new_crtc_state,
	काष्ठा dc_stream_state *new_stream,
	काष्ठा dc_plane_state *surface,
	u32 flip_बारtamp_in_us)
अणु
	काष्ठा mod_vrr_params vrr_params;
	काष्ठा dc_info_packet vrr_infopacket = अणु0पूर्ण;
	काष्ठा amdgpu_device *adev = dm->adev;
	काष्ठा amdgpu_crtc *acrtc = to_amdgpu_crtc(new_crtc_state->base.crtc);
	अचिन्हित दीर्घ flags;
	bool pack_sdp_v1_3 = false;

	अगर (!new_stream)
		वापस;

	/*
	 * TODO: Determine why min/max totals and vrefresh can be 0 here.
	 * For now it's sufficient to just guard against these conditions.
	 */

	अगर (!new_stream->timing.h_total || !new_stream->timing.v_total)
		वापस;

	spin_lock_irqsave(&adev_to_drm(adev)->event_lock, flags);
        vrr_params = acrtc->dm_irq_params.vrr_params;

	अगर (surface) अणु
		mod_मुक्तsync_handle_preflip(
			dm->मुक्तsync_module,
			surface,
			new_stream,
			flip_बारtamp_in_us,
			&vrr_params);

		अगर (adev->family < AMDGPU_FAMILY_AI &&
		    amdgpu_dm_vrr_active(new_crtc_state)) अणु
			mod_मुक्तsync_handle_v_update(dm->मुक्तsync_module,
						     new_stream, &vrr_params);

			/* Need to call this beक्रमe the frame ends. */
			dc_stream_adjust_vmin_vmax(dm->dc,
						   new_crtc_state->stream,
						   &vrr_params.adjust);
		पूर्ण
	पूर्ण

	mod_मुक्तsync_build_vrr_infopacket(
		dm->मुक्तsync_module,
		new_stream,
		&vrr_params,
		PACKET_TYPE_VRR,
		TRANSFER_FUNC_UNKNOWN,
		&vrr_infopacket,
		pack_sdp_v1_3);

	new_crtc_state->मुक्तsync_timing_changed |=
		(स_भेद(&acrtc->dm_irq_params.vrr_params.adjust,
			&vrr_params.adjust,
			माप(vrr_params.adjust)) != 0);

	new_crtc_state->मुक्तsync_vrr_info_changed |=
		(स_भेद(&new_crtc_state->vrr_infopacket,
			&vrr_infopacket,
			माप(vrr_infopacket)) != 0);

	acrtc->dm_irq_params.vrr_params = vrr_params;
	new_crtc_state->vrr_infopacket = vrr_infopacket;

	new_stream->adjust = acrtc->dm_irq_params.vrr_params.adjust;
	new_stream->vrr_infopacket = vrr_infopacket;

	अगर (new_crtc_state->मुक्तsync_vrr_info_changed)
		DRM_DEBUG_KMS("VRR packet update: crtc=%u enabled=%d state=%d",
			      new_crtc_state->base.crtc->base.id,
			      (पूर्णांक)new_crtc_state->base.vrr_enabled,
			      (पूर्णांक)vrr_params.state);

	spin_unlock_irqrestore(&adev_to_drm(adev)->event_lock, flags);
पूर्ण

अटल व्योम update_stream_irq_parameters(
	काष्ठा amdgpu_display_manager *dm,
	काष्ठा dm_crtc_state *new_crtc_state)
अणु
	काष्ठा dc_stream_state *new_stream = new_crtc_state->stream;
	काष्ठा mod_vrr_params vrr_params;
	काष्ठा mod_मुक्तsync_config config = new_crtc_state->मुक्तsync_config;
	काष्ठा amdgpu_device *adev = dm->adev;
	काष्ठा amdgpu_crtc *acrtc = to_amdgpu_crtc(new_crtc_state->base.crtc);
	अचिन्हित दीर्घ flags;

	अगर (!new_stream)
		वापस;

	/*
	 * TODO: Determine why min/max totals and vrefresh can be 0 here.
	 * For now it's sufficient to just guard against these conditions.
	 */
	अगर (!new_stream->timing.h_total || !new_stream->timing.v_total)
		वापस;

	spin_lock_irqsave(&adev_to_drm(adev)->event_lock, flags);
	vrr_params = acrtc->dm_irq_params.vrr_params;

	अगर (new_crtc_state->vrr_supported &&
	    config.min_refresh_in_uhz &&
	    config.max_refresh_in_uhz) अणु
		/*
		 * अगर मुक्तsync compatible mode was set, config.state will be set
		 * in atomic check
		 */
		अगर (config.state == VRR_STATE_ACTIVE_FIXED && config.fixed_refresh_in_uhz &&
		    (!drm_atomic_crtc_needs_modeset(&new_crtc_state->base) ||
		     new_crtc_state->मुक्तsync_config.state == VRR_STATE_ACTIVE_FIXED)) अणु
			vrr_params.max_refresh_in_uhz = config.max_refresh_in_uhz;
			vrr_params.min_refresh_in_uhz = config.min_refresh_in_uhz;
			vrr_params.fixed_refresh_in_uhz = config.fixed_refresh_in_uhz;
			vrr_params.state = VRR_STATE_ACTIVE_FIXED;
		पूर्ण अन्यथा अणु
			config.state = new_crtc_state->base.vrr_enabled ?
						     VRR_STATE_ACTIVE_VARIABLE :
						     VRR_STATE_INACTIVE;
		पूर्ण
	पूर्ण अन्यथा अणु
		config.state = VRR_STATE_UNSUPPORTED;
	पूर्ण

	mod_मुक्तsync_build_vrr_params(dm->मुक्तsync_module,
				      new_stream,
				      &config, &vrr_params);

	new_crtc_state->मुक्तsync_timing_changed |=
		(स_भेद(&acrtc->dm_irq_params.vrr_params.adjust,
			&vrr_params.adjust, माप(vrr_params.adjust)) != 0);

	new_crtc_state->मुक्तsync_config = config;
	/* Copy state क्रम access from DM IRQ handler */
	acrtc->dm_irq_params.मुक्तsync_config = config;
	acrtc->dm_irq_params.active_planes = new_crtc_state->active_planes;
	acrtc->dm_irq_params.vrr_params = vrr_params;
	spin_unlock_irqrestore(&adev_to_drm(adev)->event_lock, flags);
पूर्ण

अटल व्योम amdgpu_dm_handle_vrr_transition(काष्ठा dm_crtc_state *old_state,
					    काष्ठा dm_crtc_state *new_state)
अणु
	bool old_vrr_active = amdgpu_dm_vrr_active(old_state);
	bool new_vrr_active = amdgpu_dm_vrr_active(new_state);

	अगर (!old_vrr_active && new_vrr_active) अणु
		/* Transition VRR inactive -> active:
		 * While VRR is active, we must not disable vblank irq, as a
		 * reenable after disable would compute bogus vblank/pflip
		 * बारtamps अगर it likely happened inside display front-porch.
		 *
		 * We also need vupdate irq क्रम the actual core vblank handling
		 * at end of vblank.
		 */
		dm_set_vupdate_irq(new_state->base.crtc, true);
		drm_crtc_vblank_get(new_state->base.crtc);
		DRM_DEBUG_DRIVER("%s: crtc=%u VRR off->on: Get vblank ref\n",
				 __func__, new_state->base.crtc->base.id);
	पूर्ण अन्यथा अगर (old_vrr_active && !new_vrr_active) अणु
		/* Transition VRR active -> inactive:
		 * Allow vblank irq disable again क्रम fixed refresh rate.
		 */
		dm_set_vupdate_irq(new_state->base.crtc, false);
		drm_crtc_vblank_put(new_state->base.crtc);
		DRM_DEBUG_DRIVER("%s: crtc=%u VRR on->off: Drop vblank ref\n",
				 __func__, new_state->base.crtc->base.id);
	पूर्ण
पूर्ण

अटल व्योम amdgpu_dm_commit_cursors(काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane *plane;
	काष्ठा drm_plane_state *old_plane_state, *new_plane_state;
	पूर्णांक i;

	/*
	 * TODO: Make this per-stream so we करोn't issue redundant updates क्रम
	 * commits with multiple streams.
	 */
	क्रम_each_oldnew_plane_in_state(state, plane, old_plane_state,
				       new_plane_state, i)
		अगर (plane->type == DRM_PLANE_TYPE_CURSOR)
			handle_cursor_update(plane, old_plane_state);
पूर्ण

अटल व्योम amdgpu_dm_commit_planes(काष्ठा drm_atomic_state *state,
				    काष्ठा dc_state *dc_state,
				    काष्ठा drm_device *dev,
				    काष्ठा amdgpu_display_manager *dm,
				    काष्ठा drm_crtc *pcrtc,
				    bool रुको_क्रम_vblank)
अणु
	uपूर्णांक32_t i;
	uपूर्णांक64_t बारtamp_ns;
	काष्ठा drm_plane *plane;
	काष्ठा drm_plane_state *old_plane_state, *new_plane_state;
	काष्ठा amdgpu_crtc *acrtc_attach = to_amdgpu_crtc(pcrtc);
	काष्ठा drm_crtc_state *new_pcrtc_state =
			drm_atomic_get_new_crtc_state(state, pcrtc);
	काष्ठा dm_crtc_state *acrtc_state = to_dm_crtc_state(new_pcrtc_state);
	काष्ठा dm_crtc_state *dm_old_crtc_state =
			to_dm_crtc_state(drm_atomic_get_old_crtc_state(state, pcrtc));
	पूर्णांक planes_count = 0, vpos, hpos;
	दीर्घ r;
	अचिन्हित दीर्घ flags;
	काष्ठा amdgpu_bo *abo;
	uपूर्णांक32_t target_vblank, last_flip_vblank;
	bool vrr_active = amdgpu_dm_vrr_active(acrtc_state);
	bool pflip_present = false;
	काष्ठा अणु
		काष्ठा dc_surface_update surface_updates[MAX_SURFACES];
		काष्ठा dc_plane_info plane_infos[MAX_SURFACES];
		काष्ठा dc_scaling_info scaling_infos[MAX_SURFACES];
		काष्ठा dc_flip_addrs flip_addrs[MAX_SURFACES];
		काष्ठा dc_stream_update stream_update;
	पूर्ण *bundle;

	bundle = kzalloc(माप(*bundle), GFP_KERNEL);

	अगर (!bundle) अणु
		dm_error("Failed to allocate update bundle\n");
		जाओ cleanup;
	पूर्ण

	/*
	 * Disable the cursor first अगर we're disabling all the planes.
	 * It'll reमुख्य on the screen after the planes are re-enabled
	 * अगर we करोn't.
	 */
	अगर (acrtc_state->active_planes == 0)
		amdgpu_dm_commit_cursors(state);

	/* update planes when needed */
	क्रम_each_oldnew_plane_in_state(state, plane, old_plane_state, new_plane_state, i) अणु
		काष्ठा drm_crtc *crtc = new_plane_state->crtc;
		काष्ठा drm_crtc_state *new_crtc_state;
		काष्ठा drm_framebuffer *fb = new_plane_state->fb;
		काष्ठा amdgpu_framebuffer *afb = (काष्ठा amdgpu_framebuffer *)fb;
		bool plane_needs_flip;
		काष्ठा dc_plane_state *dc_plane;
		काष्ठा dm_plane_state *dm_new_plane_state = to_dm_plane_state(new_plane_state);

		/* Cursor plane is handled after stream updates */
		अगर (plane->type == DRM_PLANE_TYPE_CURSOR)
			जारी;

		अगर (!fb || !crtc || pcrtc != crtc)
			जारी;

		new_crtc_state = drm_atomic_get_new_crtc_state(state, crtc);
		अगर (!new_crtc_state->active)
			जारी;

		dc_plane = dm_new_plane_state->dc_state;

		bundle->surface_updates[planes_count].surface = dc_plane;
		अगर (new_pcrtc_state->color_mgmt_changed) अणु
			bundle->surface_updates[planes_count].gamma = dc_plane->gamma_correction;
			bundle->surface_updates[planes_count].in_transfer_func = dc_plane->in_transfer_func;
			bundle->surface_updates[planes_count].gamut_remap_matrix = &dc_plane->gamut_remap_matrix;
		पूर्ण

		fill_dc_scaling_info(new_plane_state,
				     &bundle->scaling_infos[planes_count]);

		bundle->surface_updates[planes_count].scaling_info =
			&bundle->scaling_infos[planes_count];

		plane_needs_flip = old_plane_state->fb && new_plane_state->fb;

		pflip_present = pflip_present || plane_needs_flip;

		अगर (!plane_needs_flip) अणु
			planes_count += 1;
			जारी;
		पूर्ण

		abo = gem_to_amdgpu_bo(fb->obj[0]);

		/*
		 * Wait क्रम all fences on this FB. Do limited रुको to aव्योम
		 * deadlock during GPU reset when this fence will not संकेत
		 * but we hold reservation lock क्रम the BO.
		 */
		r = dma_resv_रुको_समयout_rcu(abo->tbo.base.resv, true,
							false,
							msecs_to_jअगरfies(5000));
		अगर (unlikely(r <= 0))
			DRM_ERROR("Waiting for fences timed out!");

		fill_dc_plane_info_and_addr(
			dm->adev, new_plane_state,
			afb->tiling_flags,
			&bundle->plane_infos[planes_count],
			&bundle->flip_addrs[planes_count].address,
			afb->पंचांगz_surface, false);

		DRM_DEBUG_ATOMIC("plane: id=%d dcc_en=%d\n",
				 new_plane_state->plane->index,
				 bundle->plane_infos[planes_count].dcc.enable);

		bundle->surface_updates[planes_count].plane_info =
			&bundle->plane_infos[planes_count];

		/*
		 * Only allow immediate flips क्रम fast updates that करोn't
		 * change FB pitch, DCC state, rotation or mirroing.
		 */
		bundle->flip_addrs[planes_count].flip_immediate =
			crtc->state->async_flip &&
			acrtc_state->update_type == UPDATE_TYPE_FAST;

		बारtamp_ns = kसमय_get_ns();
		bundle->flip_addrs[planes_count].flip_बारtamp_in_us = भाग_u64(बारtamp_ns, 1000);
		bundle->surface_updates[planes_count].flip_addr = &bundle->flip_addrs[planes_count];
		bundle->surface_updates[planes_count].surface = dc_plane;

		अगर (!bundle->surface_updates[planes_count].surface) अणु
			DRM_ERROR("No surface for CRTC: id=%d\n",
					acrtc_attach->crtc_id);
			जारी;
		पूर्ण

		अगर (plane == pcrtc->primary)
			update_मुक्तsync_state_on_stream(
				dm,
				acrtc_state,
				acrtc_state->stream,
				dc_plane,
				bundle->flip_addrs[planes_count].flip_बारtamp_in_us);

		DRM_DEBUG_ATOMIC("%s Flipping to hi: 0x%x, low: 0x%x\n",
				 __func__,
				 bundle->flip_addrs[planes_count].address.grph.addr.high_part,
				 bundle->flip_addrs[planes_count].address.grph.addr.low_part);

		planes_count += 1;

	पूर्ण

	अगर (pflip_present) अणु
		अगर (!vrr_active) अणु
			/* Use old throttling in non-vrr fixed refresh rate mode
			 * to keep flip scheduling based on target vblank counts
			 * working in a backwards compatible way, e.g., क्रम
			 * clients using the GLX_OML_sync_control extension or
			 * DRI3/Present extension with defined target_msc.
			 */
			last_flip_vblank = amdgpu_get_vblank_counter_kms(pcrtc);
		पूर्ण
		अन्यथा अणु
			/* For variable refresh rate mode only:
			 * Get vblank of last completed flip to aव्योम > 1 vrr
			 * flips per video frame by use of throttling, but allow
			 * flip programming anywhere in the possibly large
			 * variable vrr vblank पूर्णांकerval क्रम fine-grained flip
			 * timing control and more opportunity to aव्योम stutter
			 * on late submission of flips.
			 */
			spin_lock_irqsave(&pcrtc->dev->event_lock, flags);
			last_flip_vblank = acrtc_attach->dm_irq_params.last_flip_vblank;
			spin_unlock_irqrestore(&pcrtc->dev->event_lock, flags);
		पूर्ण

		target_vblank = last_flip_vblank + रुको_क्रम_vblank;

		/*
		 * Wait until we're out of the vertical blank period beक्रमe the one
		 * targeted by the flip
		 */
		जबतक ((acrtc_attach->enabled &&
			(amdgpu_display_get_crtc_scanoutpos(dm->ddev, acrtc_attach->crtc_id,
							    0, &vpos, &hpos, शून्य,
							    शून्य, &pcrtc->hwmode)
			 & (DRM_SCANOUTPOS_VALID | DRM_SCANOUTPOS_IN_VBLANK)) ==
			(DRM_SCANOUTPOS_VALID | DRM_SCANOUTPOS_IN_VBLANK) &&
			(पूर्णांक)(target_vblank -
			  amdgpu_get_vblank_counter_kms(pcrtc)) > 0)) अणु
			usleep_range(1000, 1100);
		पूर्ण

		/**
		 * Prepare the flip event क्रम the pageflip पूर्णांकerrupt to handle.
		 *
		 * This only works in the हाल where we've alपढ़ोy turned on the
		 * appropriate hardware blocks (eg. HUBP) so in the transition हाल
		 * from 0 -> n planes we have to skip a hardware generated event
		 * and rely on sending it from software.
		 */
		अगर (acrtc_attach->base.state->event &&
		    acrtc_state->active_planes > 0) अणु
			drm_crtc_vblank_get(pcrtc);

			spin_lock_irqsave(&pcrtc->dev->event_lock, flags);

			WARN_ON(acrtc_attach->pflip_status != AMDGPU_FLIP_NONE);
			prepare_flip_isr(acrtc_attach);

			spin_unlock_irqrestore(&pcrtc->dev->event_lock, flags);
		पूर्ण

		अगर (acrtc_state->stream) अणु
			अगर (acrtc_state->मुक्तsync_vrr_info_changed)
				bundle->stream_update.vrr_infopacket =
					&acrtc_state->stream->vrr_infopacket;
		पूर्ण
	पूर्ण

	/* Update the planes अगर changed or disable अगर we करोn't have any. */
	अगर ((planes_count || acrtc_state->active_planes == 0) &&
		acrtc_state->stream) अणु
		bundle->stream_update.stream = acrtc_state->stream;
		अगर (new_pcrtc_state->mode_changed) अणु
			bundle->stream_update.src = acrtc_state->stream->src;
			bundle->stream_update.dst = acrtc_state->stream->dst;
		पूर्ण

		अगर (new_pcrtc_state->color_mgmt_changed) अणु
			/*
			 * TODO: This isn't fully correct since we've actually
			 * alपढ़ोy modअगरied the stream in place.
			 */
			bundle->stream_update.gamut_remap =
				&acrtc_state->stream->gamut_remap_matrix;
			bundle->stream_update.output_csc_transक्रमm =
				&acrtc_state->stream->csc_color_matrix;
			bundle->stream_update.out_transfer_func =
				acrtc_state->stream->out_transfer_func;
		पूर्ण

		acrtc_state->stream->abm_level = acrtc_state->abm_level;
		अगर (acrtc_state->abm_level != dm_old_crtc_state->abm_level)
			bundle->stream_update.abm_level = &acrtc_state->abm_level;

		/*
		 * If FreeSync state on the stream has changed then we need to
		 * re-adjust the min/max bounds now that DC करोesn't handle this
		 * as part of commit.
		 */
		अगर (is_dc_timing_adjust_needed(dm_old_crtc_state, acrtc_state)) अणु
			spin_lock_irqsave(&pcrtc->dev->event_lock, flags);
			dc_stream_adjust_vmin_vmax(
				dm->dc, acrtc_state->stream,
				&acrtc_attach->dm_irq_params.vrr_params.adjust);
			spin_unlock_irqrestore(&pcrtc->dev->event_lock, flags);
		पूर्ण
		mutex_lock(&dm->dc_lock);
		अगर ((acrtc_state->update_type > UPDATE_TYPE_FAST) &&
				acrtc_state->stream->link->psr_settings.psr_allow_active)
			amdgpu_dm_psr_disable(acrtc_state->stream);

		dc_commit_updates_क्रम_stream(dm->dc,
						     bundle->surface_updates,
						     planes_count,
						     acrtc_state->stream,
						     &bundle->stream_update,
						     dc_state);

		/**
		 * Enable or disable the पूर्णांकerrupts on the backend.
		 *
		 * Most pipes are put पूर्णांकo घातer gating when unused.
		 *
		 * When घातer gating is enabled on a pipe we lose the
		 * पूर्णांकerrupt enablement state when घातer gating is disabled.
		 *
		 * So we need to update the IRQ control state in hardware
		 * whenever the pipe turns on (since it could be previously
		 * घातer gated) or off (since some pipes can't be घातer gated
		 * on some ASICs).
		 */
		अगर (dm_old_crtc_state->active_planes != acrtc_state->active_planes)
			dm_update_pflip_irq_state(drm_to_adev(dev),
						  acrtc_attach);

		अगर ((acrtc_state->update_type > UPDATE_TYPE_FAST) &&
				acrtc_state->stream->link->psr_settings.psr_version != DC_PSR_VERSION_UNSUPPORTED &&
				!acrtc_state->stream->link->psr_settings.psr_feature_enabled)
			amdgpu_dm_link_setup_psr(acrtc_state->stream);
		अन्यथा अगर ((acrtc_state->update_type == UPDATE_TYPE_FAST) &&
				acrtc_state->stream->link->psr_settings.psr_feature_enabled &&
				!acrtc_state->stream->link->psr_settings.psr_allow_active) अणु
			amdgpu_dm_psr_enable(acrtc_state->stream);
		पूर्ण

		mutex_unlock(&dm->dc_lock);
	पूर्ण

	/*
	 * Update cursor state *after* programming all the planes.
	 * This aव्योमs redundant programming in the हाल where we're going
	 * to be disabling a single plane - those pipes are being disabled.
	 */
	अगर (acrtc_state->active_planes)
		amdgpu_dm_commit_cursors(state);

cleanup:
	kमुक्त(bundle);
पूर्ण

अटल व्योम amdgpu_dm_commit_audio(काष्ठा drm_device *dev,
				   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_dm_connector *aconnector;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_state *old_con_state, *new_con_state;
	काष्ठा drm_crtc_state *new_crtc_state;
	काष्ठा dm_crtc_state *new_dm_crtc_state;
	स्थिर काष्ठा dc_stream_status *status;
	पूर्णांक i, inst;

	/* Notअगरy device removals. */
	क्रम_each_oldnew_connector_in_state(state, connector, old_con_state, new_con_state, i) अणु
		अगर (old_con_state->crtc != new_con_state->crtc) अणु
			/* CRTC changes require notअगरication. */
			जाओ notअगरy;
		पूर्ण

		अगर (!new_con_state->crtc)
			जारी;

		new_crtc_state = drm_atomic_get_new_crtc_state(
			state, new_con_state->crtc);

		अगर (!new_crtc_state)
			जारी;

		अगर (!drm_atomic_crtc_needs_modeset(new_crtc_state))
			जारी;

	notअगरy:
		aconnector = to_amdgpu_dm_connector(connector);

		mutex_lock(&adev->dm.audio_lock);
		inst = aconnector->audio_inst;
		aconnector->audio_inst = -1;
		mutex_unlock(&adev->dm.audio_lock);

		amdgpu_dm_audio_eld_notअगरy(adev, inst);
	पूर्ण

	/* Notअगरy audio device additions. */
	क्रम_each_new_connector_in_state(state, connector, new_con_state, i) अणु
		अगर (!new_con_state->crtc)
			जारी;

		new_crtc_state = drm_atomic_get_new_crtc_state(
			state, new_con_state->crtc);

		अगर (!new_crtc_state)
			जारी;

		अगर (!drm_atomic_crtc_needs_modeset(new_crtc_state))
			जारी;

		new_dm_crtc_state = to_dm_crtc_state(new_crtc_state);
		अगर (!new_dm_crtc_state->stream)
			जारी;

		status = dc_stream_get_status(new_dm_crtc_state->stream);
		अगर (!status)
			जारी;

		aconnector = to_amdgpu_dm_connector(connector);

		mutex_lock(&adev->dm.audio_lock);
		inst = status->audio_inst;
		aconnector->audio_inst = inst;
		mutex_unlock(&adev->dm.audio_lock);

		amdgpu_dm_audio_eld_notअगरy(adev, inst);
	पूर्ण
पूर्ण

/*
 * amdgpu_dm_crtc_copy_transient_flags - copy mirrored flags from DRM to DC
 * @crtc_state: the DRM CRTC state
 * @stream_state: the DC stream state.
 *
 * Copy the mirrored transient state flags from DRM, to DC. It is used to bring
 * a dc_stream_state's flags in sync with a drm_crtc_state's flags.
 */
अटल व्योम amdgpu_dm_crtc_copy_transient_flags(काष्ठा drm_crtc_state *crtc_state,
						काष्ठा dc_stream_state *stream_state)
अणु
	stream_state->mode_changed = drm_atomic_crtc_needs_modeset(crtc_state);
पूर्ण

/**
 * amdgpu_dm_atomic_commit_tail() - AMDgpu DM's commit tail implementation.
 * @state: The atomic state to commit
 *
 * This will tell DC to commit the स्थिरructed DC state from atomic_check,
 * programming the hardware. Any failures here implies a hardware failure, since
 * atomic check should have filtered anything non-kosher.
 */
अटल व्योम amdgpu_dm_atomic_commit_tail(काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_device *dev = state->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_display_manager *dm = &adev->dm;
	काष्ठा dm_atomic_state *dm_state;
	काष्ठा dc_state *dc_state = शून्य, *dc_state_temp = शून्य;
	uपूर्णांक32_t i, j;
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *old_crtc_state, *new_crtc_state;
	अचिन्हित दीर्घ flags;
	bool रुको_क्रम_vblank = true;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_state *old_con_state, *new_con_state;
	काष्ठा dm_crtc_state *dm_old_crtc_state, *dm_new_crtc_state;
	पूर्णांक crtc_disable_count = 0;
	bool mode_set_reset_required = false;

	trace_amdgpu_dm_atomic_commit_tail_begin(state);

	drm_atomic_helper_update_legacy_modeset_state(dev, state);

	dm_state = dm_atomic_get_new_state(state);
	अगर (dm_state && dm_state->context) अणु
		dc_state = dm_state->context;
	पूर्ण अन्यथा अणु
		/* No state changes, retain current state. */
		dc_state_temp = dc_create_state(dm->dc);
		ASSERT(dc_state_temp);
		dc_state = dc_state_temp;
		dc_resource_state_copy_स्थिरruct_current(dm->dc, dc_state);
	पूर्ण

	क्रम_each_oldnew_crtc_in_state (state, crtc, old_crtc_state,
				       new_crtc_state, i) अणु
		काष्ठा amdgpu_crtc *acrtc = to_amdgpu_crtc(crtc);

		dm_old_crtc_state = to_dm_crtc_state(old_crtc_state);

		अगर (old_crtc_state->active &&
		    (!new_crtc_state->active ||
		     drm_atomic_crtc_needs_modeset(new_crtc_state))) अणु
			manage_dm_पूर्णांकerrupts(adev, acrtc, false);
			dc_stream_release(dm_old_crtc_state->stream);
		पूर्ण
	पूर्ण

	drm_atomic_helper_calc_बारtamping_स्थिरants(state);

	/* update changed items */
	क्रम_each_oldnew_crtc_in_state(state, crtc, old_crtc_state, new_crtc_state, i) अणु
		काष्ठा amdgpu_crtc *acrtc = to_amdgpu_crtc(crtc);

		dm_new_crtc_state = to_dm_crtc_state(new_crtc_state);
		dm_old_crtc_state = to_dm_crtc_state(old_crtc_state);

		DRM_DEBUG_ATOMIC(
			"amdgpu_crtc id:%d crtc_state_flags: enable:%d, active:%d, "
			"planes_changed:%d, mode_changed:%d,active_changed:%d,"
			"connectors_changed:%d\n",
			acrtc->crtc_id,
			new_crtc_state->enable,
			new_crtc_state->active,
			new_crtc_state->planes_changed,
			new_crtc_state->mode_changed,
			new_crtc_state->active_changed,
			new_crtc_state->connectors_changed);

		/* Disable cursor अगर disabling crtc */
		अगर (old_crtc_state->active && !new_crtc_state->active) अणु
			काष्ठा dc_cursor_position position;

			स_रखो(&position, 0, माप(position));
			mutex_lock(&dm->dc_lock);
			dc_stream_set_cursor_position(dm_old_crtc_state->stream, &position);
			mutex_unlock(&dm->dc_lock);
		पूर्ण

		/* Copy all transient state flags पूर्णांकo dc state */
		अगर (dm_new_crtc_state->stream) अणु
			amdgpu_dm_crtc_copy_transient_flags(&dm_new_crtc_state->base,
							    dm_new_crtc_state->stream);
		पूर्ण

		/* handles headless hotplug हाल, updating new_state and
		 * aconnector as needed
		 */

		अगर (modeset_required(new_crtc_state, dm_new_crtc_state->stream, dm_old_crtc_state->stream)) अणु

			DRM_DEBUG_ATOMIC("Atomic commit: SET crtc id %d: [%p]\n", acrtc->crtc_id, acrtc);

			अगर (!dm_new_crtc_state->stream) अणु
				/*
				 * this could happen because of issues with
				 * userspace notअगरications delivery.
				 * In this हाल userspace tries to set mode on
				 * display which is disconnected in fact.
				 * dc_sink is शून्य in this हाल on aconnector.
				 * We expect reset mode will come soon.
				 *
				 * This can also happen when unplug is करोne
				 * during resume sequence ended
				 *
				 * In this हाल, we want to pretend we still
				 * have a sink to keep the pipe running so that
				 * hw state is consistent with the sw state
				 */
				DRM_DEBUG_DRIVER("%s: Failed to create new stream for crtc %d\n",
						__func__, acrtc->base.base.id);
				जारी;
			पूर्ण

			अगर (dm_old_crtc_state->stream)
				हटाओ_stream(adev, acrtc, dm_old_crtc_state->stream);

			pm_runसमय_get_noresume(dev->dev);

			acrtc->enabled = true;
			acrtc->hw_mode = new_crtc_state->mode;
			crtc->hwmode = new_crtc_state->mode;
			mode_set_reset_required = true;
		पूर्ण अन्यथा अगर (modereset_required(new_crtc_state)) अणु
			DRM_DEBUG_ATOMIC("Atomic commit: RESET. crtc id %d:[%p]\n", acrtc->crtc_id, acrtc);
			/* i.e. reset mode */
			अगर (dm_old_crtc_state->stream)
				हटाओ_stream(adev, acrtc, dm_old_crtc_state->stream);

			mode_set_reset_required = true;
		पूर्ण
	पूर्ण /* क्रम_each_crtc_in_state() */

	अगर (dc_state) अणु
		/* अगर there mode set or reset, disable eDP PSR */
		अगर (mode_set_reset_required)
			amdgpu_dm_psr_disable_all(dm);

		dm_enable_per_frame_crtc_master_sync(dc_state);
		mutex_lock(&dm->dc_lock);
		WARN_ON(!dc_commit_state(dm->dc, dc_state));
#अगर defined(CONFIG_DRM_AMD_DC_DCN)
               /* Allow idle optimization when vblank count is 0 क्रम display off */
               अगर (dm->active_vblank_irq_count == 0)
                   dc_allow_idle_optimizations(dm->dc,true);
#पूर्ण_अगर
		mutex_unlock(&dm->dc_lock);
	पूर्ण

	क्रम_each_new_crtc_in_state(state, crtc, new_crtc_state, i) अणु
		काष्ठा amdgpu_crtc *acrtc = to_amdgpu_crtc(crtc);

		dm_new_crtc_state = to_dm_crtc_state(new_crtc_state);

		अगर (dm_new_crtc_state->stream != शून्य) अणु
			स्थिर काष्ठा dc_stream_status *status =
					dc_stream_get_status(dm_new_crtc_state->stream);

			अगर (!status)
				status = dc_stream_get_status_from_state(dc_state,
									 dm_new_crtc_state->stream);
			अगर (!status)
				DC_ERR("got no status for stream %p on acrtc%p\n", dm_new_crtc_state->stream, acrtc);
			अन्यथा
				acrtc->otg_inst = status->primary_otg_inst;
		पूर्ण
	पूर्ण
#अगर_घोषित CONFIG_DRM_AMD_DC_HDCP
	क्रम_each_oldnew_connector_in_state(state, connector, old_con_state, new_con_state, i) अणु
		काष्ठा dm_connector_state *dm_new_con_state = to_dm_connector_state(new_con_state);
		काष्ठा amdgpu_crtc *acrtc = to_amdgpu_crtc(dm_new_con_state->base.crtc);
		काष्ठा amdgpu_dm_connector *aconnector = to_amdgpu_dm_connector(connector);

		new_crtc_state = शून्य;

		अगर (acrtc)
			new_crtc_state = drm_atomic_get_new_crtc_state(state, &acrtc->base);

		dm_new_crtc_state = to_dm_crtc_state(new_crtc_state);

		अगर (dm_new_crtc_state && dm_new_crtc_state->stream == शून्य &&
		    connector->state->content_protection == DRM_MODE_CONTENT_PROTECTION_ENABLED) अणु
			hdcp_reset_display(adev->dm.hdcp_workqueue, aconnector->dc_link->link_index);
			new_con_state->content_protection = DRM_MODE_CONTENT_PROTECTION_DESIRED;
			dm_new_con_state->update_hdcp = true;
			जारी;
		पूर्ण

		अगर (is_content_protection_dअगरferent(new_con_state, old_con_state, connector, adev->dm.hdcp_workqueue))
			hdcp_update_display(
				adev->dm.hdcp_workqueue, aconnector->dc_link->link_index, aconnector,
				new_con_state->hdcp_content_type,
				new_con_state->content_protection == DRM_MODE_CONTENT_PROTECTION_DESIRED);
	पूर्ण
#पूर्ण_अगर

	/* Handle connector state changes */
	क्रम_each_oldnew_connector_in_state(state, connector, old_con_state, new_con_state, i) अणु
		काष्ठा dm_connector_state *dm_new_con_state = to_dm_connector_state(new_con_state);
		काष्ठा dm_connector_state *dm_old_con_state = to_dm_connector_state(old_con_state);
		काष्ठा amdgpu_crtc *acrtc = to_amdgpu_crtc(dm_new_con_state->base.crtc);
		काष्ठा dc_surface_update dummy_updates[MAX_SURFACES];
		काष्ठा dc_stream_update stream_update;
		काष्ठा dc_info_packet hdr_packet;
		काष्ठा dc_stream_status *status = शून्य;
		bool abm_changed, hdr_changed, scaling_changed;

		स_रखो(&dummy_updates, 0, माप(dummy_updates));
		स_रखो(&stream_update, 0, माप(stream_update));

		अगर (acrtc) अणु
			new_crtc_state = drm_atomic_get_new_crtc_state(state, &acrtc->base);
			old_crtc_state = drm_atomic_get_old_crtc_state(state, &acrtc->base);
		पूर्ण

		/* Skip any modesets/resets */
		अगर (!acrtc || drm_atomic_crtc_needs_modeset(new_crtc_state))
			जारी;

		dm_new_crtc_state = to_dm_crtc_state(new_crtc_state);
		dm_old_crtc_state = to_dm_crtc_state(old_crtc_state);

		scaling_changed = is_scaling_state_dअगरferent(dm_new_con_state,
							     dm_old_con_state);

		abm_changed = dm_new_crtc_state->abm_level !=
			      dm_old_crtc_state->abm_level;

		hdr_changed =
			is_hdr_metadata_dअगरferent(old_con_state, new_con_state);

		अगर (!scaling_changed && !abm_changed && !hdr_changed)
			जारी;

		stream_update.stream = dm_new_crtc_state->stream;
		अगर (scaling_changed) अणु
			update_stream_scaling_settings(&dm_new_con_state->base.crtc->mode,
					dm_new_con_state, dm_new_crtc_state->stream);

			stream_update.src = dm_new_crtc_state->stream->src;
			stream_update.dst = dm_new_crtc_state->stream->dst;
		पूर्ण

		अगर (abm_changed) अणु
			dm_new_crtc_state->stream->abm_level = dm_new_crtc_state->abm_level;

			stream_update.abm_level = &dm_new_crtc_state->abm_level;
		पूर्ण

		अगर (hdr_changed) अणु
			fill_hdr_info_packet(new_con_state, &hdr_packet);
			stream_update.hdr_अटल_metadata = &hdr_packet;
		पूर्ण

		status = dc_stream_get_status(dm_new_crtc_state->stream);
		WARN_ON(!status);
		WARN_ON(!status->plane_count);

		/*
		 * TODO: DC refuses to perक्रमm stream updates without a dc_surface_update.
		 * Here we create an empty update on each plane.
		 * To fix this, DC should permit updating only stream properties.
		 */
		क्रम (j = 0; j < status->plane_count; j++)
			dummy_updates[j].surface = status->plane_states[0];


		mutex_lock(&dm->dc_lock);
		dc_commit_updates_क्रम_stream(dm->dc,
						     dummy_updates,
						     status->plane_count,
						     dm_new_crtc_state->stream,
						     &stream_update,
						     dc_state);
		mutex_unlock(&dm->dc_lock);
	पूर्ण

	/* Count number of newly disabled CRTCs क्रम dropping PM refs later. */
	क्रम_each_oldnew_crtc_in_state(state, crtc, old_crtc_state,
				      new_crtc_state, i) अणु
		अगर (old_crtc_state->active && !new_crtc_state->active)
			crtc_disable_count++;

		dm_new_crtc_state = to_dm_crtc_state(new_crtc_state);
		dm_old_crtc_state = to_dm_crtc_state(old_crtc_state);

		/* For मुक्तsync config update on crtc state and params क्रम irq */
		update_stream_irq_parameters(dm, dm_new_crtc_state);

		/* Handle vrr on->off / off->on transitions */
		amdgpu_dm_handle_vrr_transition(dm_old_crtc_state,
						dm_new_crtc_state);
	पूर्ण

	/**
	 * Enable पूर्णांकerrupts क्रम CRTCs that are newly enabled or went through
	 * a modeset. It was पूर्णांकentionally deferred until after the front end
	 * state was modअगरied to रुको until the OTG was on and so the IRQ
	 * handlers didn't access stale or invalid state.
	 */
	क्रम_each_oldnew_crtc_in_state(state, crtc, old_crtc_state, new_crtc_state, i) अणु
		काष्ठा amdgpu_crtc *acrtc = to_amdgpu_crtc(crtc);
#अगर_घोषित CONFIG_DEBUG_FS
		bool configure_crc = false;
		क्रमागत amdgpu_dm_pipe_crc_source cur_crc_src;
#पूर्ण_अगर
		dm_new_crtc_state = to_dm_crtc_state(new_crtc_state);

		अगर (new_crtc_state->active &&
		    (!old_crtc_state->active ||
		     drm_atomic_crtc_needs_modeset(new_crtc_state))) अणु
			dc_stream_retain(dm_new_crtc_state->stream);
			acrtc->dm_irq_params.stream = dm_new_crtc_state->stream;
			manage_dm_पूर्णांकerrupts(adev, acrtc, true);

#अगर_घोषित CONFIG_DEBUG_FS
			/**
			 * Frontend may have changed so reapply the CRC capture
			 * settings क्रम the stream.
			 */
			dm_new_crtc_state = to_dm_crtc_state(new_crtc_state);
			spin_lock_irqsave(&adev_to_drm(adev)->event_lock, flags);
			cur_crc_src = acrtc->dm_irq_params.crc_src;
			spin_unlock_irqrestore(&adev_to_drm(adev)->event_lock, flags);

			अगर (amdgpu_dm_is_valid_crc_source(cur_crc_src)) अणु
				configure_crc = true;
#अगर defined(CONFIG_DRM_AMD_SECURE_DISPLAY)
				अगर (amdgpu_dm_crc_winकरोw_is_activated(crtc))
					configure_crc = false;
#पूर्ण_अगर
			पूर्ण

			अगर (configure_crc)
				amdgpu_dm_crtc_configure_crc_source(
					crtc, dm_new_crtc_state, cur_crc_src);
#पूर्ण_अगर
		पूर्ण
	पूर्ण

	क्रम_each_new_crtc_in_state(state, crtc, new_crtc_state, j)
		अगर (new_crtc_state->async_flip)
			रुको_क्रम_vblank = false;

	/* update planes when needed per crtc*/
	क्रम_each_new_crtc_in_state(state, crtc, new_crtc_state, j) अणु
		dm_new_crtc_state = to_dm_crtc_state(new_crtc_state);

		अगर (dm_new_crtc_state->stream)
			amdgpu_dm_commit_planes(state, dc_state, dev,
						dm, crtc, रुको_क्रम_vblank);
	पूर्ण

	/* Update audio instances क्रम each connector. */
	amdgpu_dm_commit_audio(dev, state);

	/*
	 * send vblank event on all events not handled in flip and
	 * mark consumed event क्रम drm_atomic_helper_commit_hw_करोne
	 */
	spin_lock_irqsave(&adev_to_drm(adev)->event_lock, flags);
	क्रम_each_new_crtc_in_state(state, crtc, new_crtc_state, i) अणु

		अगर (new_crtc_state->event)
			drm_send_event_locked(dev, &new_crtc_state->event->base);

		new_crtc_state->event = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&adev_to_drm(adev)->event_lock, flags);

	/* Signal HW programming completion */
	drm_atomic_helper_commit_hw_करोne(state);

	अगर (रुको_क्रम_vblank)
		drm_atomic_helper_रुको_क्रम_flip_करोne(dev, state);

	drm_atomic_helper_cleanup_planes(dev, state);

	/* वापस the stolen vga memory back to VRAM */
	अगर (!adev->mman.keep_stolen_vga_memory)
		amdgpu_bo_मुक्त_kernel(&adev->mman.stolen_vga_memory, शून्य, शून्य);
	amdgpu_bo_मुक्त_kernel(&adev->mman.stolen_extended_memory, शून्य, शून्य);

	/*
	 * Finally, drop a runसमय PM reference क्रम each newly disabled CRTC,
	 * so we can put the GPU पूर्णांकo runसमय suspend अगर we're not driving any
	 * displays anymore
	 */
	क्रम (i = 0; i < crtc_disable_count; i++)
		pm_runसमय_put_स्वतःsuspend(dev->dev);
	pm_runसमय_mark_last_busy(dev->dev);

	अगर (dc_state_temp)
		dc_release_state(dc_state_temp);
पूर्ण


अटल पूर्णांक dm_क्रमce_atomic_commit(काष्ठा drm_connector *connector)
अणु
	पूर्णांक ret = 0;
	काष्ठा drm_device *ddev = connector->dev;
	काष्ठा drm_atomic_state *state = drm_atomic_state_alloc(ddev);
	काष्ठा amdgpu_crtc *disconnected_acrtc = to_amdgpu_crtc(connector->encoder->crtc);
	काष्ठा drm_plane *plane = disconnected_acrtc->base.primary;
	काष्ठा drm_connector_state *conn_state;
	काष्ठा drm_crtc_state *crtc_state;
	काष्ठा drm_plane_state *plane_state;

	अगर (!state)
		वापस -ENOMEM;

	state->acquire_ctx = ddev->mode_config.acquire_ctx;

	/* Conकाष्ठा an atomic state to restore previous display setting */

	/*
	 * Attach connectors to drm_atomic_state
	 */
	conn_state = drm_atomic_get_connector_state(state, connector);

	ret = PTR_ERR_OR_ZERO(conn_state);
	अगर (ret)
		जाओ out;

	/* Attach crtc to drm_atomic_state*/
	crtc_state = drm_atomic_get_crtc_state(state, &disconnected_acrtc->base);

	ret = PTR_ERR_OR_ZERO(crtc_state);
	अगर (ret)
		जाओ out;

	/* क्रमce a restore */
	crtc_state->mode_changed = true;

	/* Attach plane to drm_atomic_state */
	plane_state = drm_atomic_get_plane_state(state, plane);

	ret = PTR_ERR_OR_ZERO(plane_state);
	अगर (ret)
		जाओ out;

	/* Call commit पूर्णांकernally with the state we just स्थिरructed */
	ret = drm_atomic_commit(state);

out:
	drm_atomic_state_put(state);
	अगर (ret)
		DRM_ERROR("Restoring old state failed with %i\n", ret);

	वापस ret;
पूर्ण

/*
 * This function handles all हालs when set mode करोes not come upon hotplug.
 * This includes when a display is unplugged then plugged back पूर्णांकo the
 * same port and when running without usermode desktop manager supprot
 */
व्योम dm_restore_drm_connector_state(काष्ठा drm_device *dev,
				    काष्ठा drm_connector *connector)
अणु
	काष्ठा amdgpu_dm_connector *aconnector = to_amdgpu_dm_connector(connector);
	काष्ठा amdgpu_crtc *disconnected_acrtc;
	काष्ठा dm_crtc_state *acrtc_state;

	अगर (!aconnector->dc_sink || !connector->state || !connector->encoder)
		वापस;

	disconnected_acrtc = to_amdgpu_crtc(connector->encoder->crtc);
	अगर (!disconnected_acrtc)
		वापस;

	acrtc_state = to_dm_crtc_state(disconnected_acrtc->base.state);
	अगर (!acrtc_state->stream)
		वापस;

	/*
	 * If the previous sink is not released and dअगरferent from the current,
	 * we deduce we are in a state where we can not rely on usermode call
	 * to turn on the display, so we करो it here
	 */
	अगर (acrtc_state->stream->sink != aconnector->dc_sink)
		dm_क्रमce_atomic_commit(&aconnector->base);
पूर्ण

/*
 * Grअसल all modesetting locks to serialize against any blocking commits,
 * Waits क्रम completion of all non blocking commits.
 */
अटल पूर्णांक करो_aquire_global_lock(काष्ठा drm_device *dev,
				 काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_commit *commit;
	दीर्घ ret;

	/*
	 * Adding all modeset locks to aquire_ctx will
	 * ensure that when the framework release it the
	 * extra locks we are locking here will get released to
	 */
	ret = drm_modeset_lock_all_ctx(dev, state->acquire_ctx);
	अगर (ret)
		वापस ret;

	list_क्रम_each_entry(crtc, &dev->mode_config.crtc_list, head) अणु
		spin_lock(&crtc->commit_lock);
		commit = list_first_entry_or_null(&crtc->commit_list,
				काष्ठा drm_crtc_commit, commit_entry);
		अगर (commit)
			drm_crtc_commit_get(commit);
		spin_unlock(&crtc->commit_lock);

		अगर (!commit)
			जारी;

		/*
		 * Make sure all pending HW programming completed and
		 * page flips करोne
		 */
		ret = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&commit->hw_करोne, 10*HZ);

		अगर (ret > 0)
			ret = रुको_क्रम_completion_पूर्णांकerruptible_समयout(
					&commit->flip_करोne, 10*HZ);

		अगर (ret == 0)
			DRM_ERROR("[CRTC:%d:%s] hw_done or flip_done "
				  "timed out\n", crtc->base.id, crtc->name);

		drm_crtc_commit_put(commit);
	पूर्ण

	वापस ret < 0 ? ret : 0;
पूर्ण

अटल व्योम get_मुक्तsync_config_क्रम_crtc(
	काष्ठा dm_crtc_state *new_crtc_state,
	काष्ठा dm_connector_state *new_con_state)
अणु
	काष्ठा mod_मुक्तsync_config config = अणु0पूर्ण;
	काष्ठा amdgpu_dm_connector *aconnector =
			to_amdgpu_dm_connector(new_con_state->base.connector);
	काष्ठा drm_display_mode *mode = &new_crtc_state->base.mode;
	पूर्णांक vrefresh = drm_mode_vrefresh(mode);
	bool fs_vid_mode = false;

	new_crtc_state->vrr_supported = new_con_state->मुक्तsync_capable &&
					vrefresh >= aconnector->min_vfreq &&
					vrefresh <= aconnector->max_vfreq;

	अगर (new_crtc_state->vrr_supported) अणु
		new_crtc_state->stream->ignore_msa_timing_param = true;
		fs_vid_mode = new_crtc_state->मुक्तsync_config.state == VRR_STATE_ACTIVE_FIXED;

		config.min_refresh_in_uhz = aconnector->min_vfreq * 1000000;
		config.max_refresh_in_uhz = aconnector->max_vfreq * 1000000;
		config.vsअगर_supported = true;
		config.btr = true;

		अगर (fs_vid_mode) अणु
			config.state = VRR_STATE_ACTIVE_FIXED;
			config.fixed_refresh_in_uhz = new_crtc_state->मुक्तsync_config.fixed_refresh_in_uhz;
			जाओ out;
		पूर्ण अन्यथा अगर (new_crtc_state->base.vrr_enabled) अणु
			config.state = VRR_STATE_ACTIVE_VARIABLE;
		पूर्ण अन्यथा अणु
			config.state = VRR_STATE_INACTIVE;
		पूर्ण
	पूर्ण
out:
	new_crtc_state->मुक्तsync_config = config;
पूर्ण

अटल व्योम reset_मुक्तsync_config_क्रम_crtc(
	काष्ठा dm_crtc_state *new_crtc_state)
अणु
	new_crtc_state->vrr_supported = false;

	स_रखो(&new_crtc_state->vrr_infopacket, 0,
	       माप(new_crtc_state->vrr_infopacket));
पूर्ण

अटल bool
is_timing_unchanged_क्रम_मुक्तsync(काष्ठा drm_crtc_state *old_crtc_state,
				 काष्ठा drm_crtc_state *new_crtc_state)
अणु
	काष्ठा drm_display_mode old_mode, new_mode;

	अगर (!old_crtc_state || !new_crtc_state)
		वापस false;

	old_mode = old_crtc_state->mode;
	new_mode = new_crtc_state->mode;

	अगर (old_mode.घड़ी       == new_mode.घड़ी &&
	    old_mode.hdisplay    == new_mode.hdisplay &&
	    old_mode.vdisplay    == new_mode.vdisplay &&
	    old_mode.htotal      == new_mode.htotal &&
	    old_mode.vtotal      != new_mode.vtotal &&
	    old_mode.hsync_start == new_mode.hsync_start &&
	    old_mode.vsync_start != new_mode.vsync_start &&
	    old_mode.hsync_end   == new_mode.hsync_end &&
	    old_mode.vsync_end   != new_mode.vsync_end &&
	    old_mode.hskew       == new_mode.hskew &&
	    old_mode.vscan       == new_mode.vscan &&
	    (old_mode.vsync_end - old_mode.vsync_start) ==
	    (new_mode.vsync_end - new_mode.vsync_start))
		वापस true;

	वापस false;
पूर्ण

अटल व्योम set_मुक्तsync_fixed_config(काष्ठा dm_crtc_state *dm_new_crtc_state) अणु
	uपूर्णांक64_t num, den, res;
	काष्ठा drm_crtc_state *new_crtc_state = &dm_new_crtc_state->base;

	dm_new_crtc_state->मुक्तsync_config.state = VRR_STATE_ACTIVE_FIXED;

	num = (अचिन्हित दीर्घ दीर्घ)new_crtc_state->mode.घड़ी * 1000 * 1000000;
	den = (अचिन्हित दीर्घ दीर्घ)new_crtc_state->mode.htotal *
	      (अचिन्हित दीर्घ दीर्घ)new_crtc_state->mode.vtotal;

	res = भाग_u64(num, den);
	dm_new_crtc_state->मुक्तsync_config.fixed_refresh_in_uhz = res;
पूर्ण

अटल पूर्णांक dm_update_crtc_state(काष्ठा amdgpu_display_manager *dm,
				काष्ठा drm_atomic_state *state,
				काष्ठा drm_crtc *crtc,
				काष्ठा drm_crtc_state *old_crtc_state,
				काष्ठा drm_crtc_state *new_crtc_state,
				bool enable,
				bool *lock_and_validation_needed)
अणु
	काष्ठा dm_atomic_state *dm_state = शून्य;
	काष्ठा dm_crtc_state *dm_old_crtc_state, *dm_new_crtc_state;
	काष्ठा dc_stream_state *new_stream;
	पूर्णांक ret = 0;

	/*
	 * TODO Move this code पूर्णांकo dm_crtc_atomic_check once we get rid of dc_validation_set
	 * update changed items
	 */
	काष्ठा amdgpu_crtc *acrtc = शून्य;
	काष्ठा amdgpu_dm_connector *aconnector = शून्य;
	काष्ठा drm_connector_state *drm_new_conn_state = शून्य, *drm_old_conn_state = शून्य;
	काष्ठा dm_connector_state *dm_new_conn_state = शून्य, *dm_old_conn_state = शून्य;

	new_stream = शून्य;

	dm_old_crtc_state = to_dm_crtc_state(old_crtc_state);
	dm_new_crtc_state = to_dm_crtc_state(new_crtc_state);
	acrtc = to_amdgpu_crtc(crtc);
	aconnector = amdgpu_dm_find_first_crtc_matching_connector(state, crtc);

	/* TODO This hack should go away */
	अगर (aconnector && enable) अणु
		/* Make sure fake sink is created in plug-in scenario */
		drm_new_conn_state = drm_atomic_get_new_connector_state(state,
							    &aconnector->base);
		drm_old_conn_state = drm_atomic_get_old_connector_state(state,
							    &aconnector->base);

		अगर (IS_ERR(drm_new_conn_state)) अणु
			ret = PTR_ERR_OR_ZERO(drm_new_conn_state);
			जाओ fail;
		पूर्ण

		dm_new_conn_state = to_dm_connector_state(drm_new_conn_state);
		dm_old_conn_state = to_dm_connector_state(drm_old_conn_state);

		अगर (!drm_atomic_crtc_needs_modeset(new_crtc_state))
			जाओ skip_modeset;

		new_stream = create_validate_stream_क्रम_sink(aconnector,
							     &new_crtc_state->mode,
							     dm_new_conn_state,
							     dm_old_crtc_state->stream);

		/*
		 * we can have no stream on ACTION_SET अगर a display
		 * was disconnected during S3, in this हाल it is not an
		 * error, the OS will be updated after detection, and
		 * will करो the right thing on next atomic commit
		 */

		अगर (!new_stream) अणु
			DRM_DEBUG_DRIVER("%s: Failed to create new stream for crtc %d\n",
					__func__, acrtc->base.base.id);
			ret = -ENOMEM;
			जाओ fail;
		पूर्ण

		/*
		 * TODO: Check VSDB bits to decide whether this should
		 * be enabled or not.
		 */
		new_stream->triggered_crtc_reset.enabled =
			dm->क्रमce_timing_sync;

		dm_new_crtc_state->abm_level = dm_new_conn_state->abm_level;

		ret = fill_hdr_info_packet(drm_new_conn_state,
					   &new_stream->hdr_अटल_metadata);
		अगर (ret)
			जाओ fail;

		/*
		 * If we alपढ़ोy हटाओd the old stream from the context
		 * (and set the new stream to शून्य) then we can't reuse
		 * the old stream even अगर the stream and scaling are unchanged.
		 * We'll hit the BUG_ON and black screen.
		 *
		 * TODO: Refactor this function to allow this check to work
		 * in all conditions.
		 */
		अगर (amdgpu_मुक्तsync_vid_mode &&
		    dm_new_crtc_state->stream &&
		    is_timing_unchanged_क्रम_मुक्तsync(new_crtc_state, old_crtc_state))
			जाओ skip_modeset;

		अगर (dm_new_crtc_state->stream &&
		    dc_is_stream_unchanged(new_stream, dm_old_crtc_state->stream) &&
		    dc_is_stream_scaling_unchanged(new_stream, dm_old_crtc_state->stream)) अणु
			new_crtc_state->mode_changed = false;
			DRM_DEBUG_DRIVER("Mode change not required, setting mode_changed to %d",
					 new_crtc_state->mode_changed);
		पूर्ण
	पूर्ण

	/* mode_changed flag may get updated above, need to check again */
	अगर (!drm_atomic_crtc_needs_modeset(new_crtc_state))
		जाओ skip_modeset;

	DRM_DEBUG_ATOMIC(
		"amdgpu_crtc id:%d crtc_state_flags: enable:%d, active:%d, "
		"planes_changed:%d, mode_changed:%d,active_changed:%d,"
		"connectors_changed:%d\n",
		acrtc->crtc_id,
		new_crtc_state->enable,
		new_crtc_state->active,
		new_crtc_state->planes_changed,
		new_crtc_state->mode_changed,
		new_crtc_state->active_changed,
		new_crtc_state->connectors_changed);

	/* Remove stream क्रम any changed/disabled CRTC */
	अगर (!enable) अणु

		अगर (!dm_old_crtc_state->stream)
			जाओ skip_modeset;

		अगर (amdgpu_मुक्तsync_vid_mode && dm_new_crtc_state->stream &&
		    is_timing_unchanged_क्रम_मुक्तsync(new_crtc_state,
						     old_crtc_state)) अणु
			new_crtc_state->mode_changed = false;
			DRM_DEBUG_DRIVER(
				"Mode change not required for front porch change, "
				"setting mode_changed to %d",
				new_crtc_state->mode_changed);

			set_मुक्तsync_fixed_config(dm_new_crtc_state);

			जाओ skip_modeset;
		पूर्ण अन्यथा अगर (amdgpu_मुक्तsync_vid_mode && aconnector &&
			   is_मुक्तsync_video_mode(&new_crtc_state->mode,
						  aconnector)) अणु
			set_मुक्तsync_fixed_config(dm_new_crtc_state);
		पूर्ण

		ret = dm_atomic_get_state(state, &dm_state);
		अगर (ret)
			जाओ fail;

		DRM_DEBUG_DRIVER("Disabling DRM crtc: %d\n",
				crtc->base.id);

		/* i.e. reset mode */
		अगर (dc_हटाओ_stream_from_ctx(
				dm->dc,
				dm_state->context,
				dm_old_crtc_state->stream) != DC_OK) अणु
			ret = -EINVAL;
			जाओ fail;
		पूर्ण

		dc_stream_release(dm_old_crtc_state->stream);
		dm_new_crtc_state->stream = शून्य;

		reset_मुक्तsync_config_क्रम_crtc(dm_new_crtc_state);

		*lock_and_validation_needed = true;

	पूर्ण अन्यथा अणु/* Add stream क्रम any updated/enabled CRTC */
		/*
		 * Quick fix to prevent शून्य poपूर्णांकer on new_stream when
		 * added MST connectors not found in existing crtc_state in the chained mode
		 * TODO: need to dig out the root cause of that
		 */
		अगर (!aconnector || (!aconnector->dc_sink && aconnector->mst_port))
			जाओ skip_modeset;

		अगर (modereset_required(new_crtc_state))
			जाओ skip_modeset;

		अगर (modeset_required(new_crtc_state, new_stream,
				     dm_old_crtc_state->stream)) अणु

			WARN_ON(dm_new_crtc_state->stream);

			ret = dm_atomic_get_state(state, &dm_state);
			अगर (ret)
				जाओ fail;

			dm_new_crtc_state->stream = new_stream;

			dc_stream_retain(new_stream);

			DRM_DEBUG_ATOMIC("Enabling DRM crtc: %d\n",
					 crtc->base.id);

			अगर (dc_add_stream_to_ctx(
					dm->dc,
					dm_state->context,
					dm_new_crtc_state->stream) != DC_OK) अणु
				ret = -EINVAL;
				जाओ fail;
			पूर्ण

			*lock_and_validation_needed = true;
		पूर्ण
	पूर्ण

skip_modeset:
	/* Release extra reference */
	अगर (new_stream)
		 dc_stream_release(new_stream);

	/*
	 * We want to करो dc stream updates that करो not require a
	 * full modeset below.
	 */
	अगर (!(enable && aconnector && new_crtc_state->active))
		वापस 0;
	/*
	 * Given above conditions, the dc state cannot be शून्य because:
	 * 1. We're in the process of enabling CRTCs (just been added
	 *    to the dc context, or alपढ़ोy is on the context)
	 * 2. Has a valid connector attached, and
	 * 3. Is currently active and enabled.
	 * => The dc stream state currently exists.
	 */
	BUG_ON(dm_new_crtc_state->stream == शून्य);

	/* Scaling or underscan settings */
	अगर (is_scaling_state_dअगरferent(dm_old_conn_state, dm_new_conn_state))
		update_stream_scaling_settings(
			&new_crtc_state->mode, dm_new_conn_state, dm_new_crtc_state->stream);

	/* ABM settings */
	dm_new_crtc_state->abm_level = dm_new_conn_state->abm_level;

	/*
	 * Color management settings. We also update color properties
	 * when a modeset is needed, to ensure it माला_लो reprogrammed.
	 */
	अगर (dm_new_crtc_state->base.color_mgmt_changed ||
	    drm_atomic_crtc_needs_modeset(new_crtc_state)) अणु
		ret = amdgpu_dm_update_crtc_color_mgmt(dm_new_crtc_state);
		अगर (ret)
			जाओ fail;
	पूर्ण

	/* Update Freesync settings. */
	get_मुक्तsync_config_क्रम_crtc(dm_new_crtc_state,
				     dm_new_conn_state);

	वापस ret;

fail:
	अगर (new_stream)
		dc_stream_release(new_stream);
	वापस ret;
पूर्ण

अटल bool should_reset_plane(काष्ठा drm_atomic_state *state,
			       काष्ठा drm_plane *plane,
			       काष्ठा drm_plane_state *old_plane_state,
			       काष्ठा drm_plane_state *new_plane_state)
अणु
	काष्ठा drm_plane *other;
	काष्ठा drm_plane_state *old_other_state, *new_other_state;
	काष्ठा drm_crtc_state *new_crtc_state;
	पूर्णांक i;

	/*
	 * TODO: Remove this hack once the checks below are sufficient
	 * enough to determine when we need to reset all the planes on
	 * the stream.
	 */
	अगर (state->allow_modeset)
		वापस true;

	/* Exit early अगर we know that we're adding or removing the plane. */
	अगर (old_plane_state->crtc != new_plane_state->crtc)
		वापस true;

	/* old crtc == new_crtc == शून्य, plane not in context. */
	अगर (!new_plane_state->crtc)
		वापस false;

	new_crtc_state =
		drm_atomic_get_new_crtc_state(state, new_plane_state->crtc);

	अगर (!new_crtc_state)
		वापस true;

	/* CRTC Degamma changes currently require us to recreate planes. */
	अगर (new_crtc_state->color_mgmt_changed)
		वापस true;

	अगर (drm_atomic_crtc_needs_modeset(new_crtc_state))
		वापस true;

	/*
	 * If there are any new primary or overlay planes being added or
	 * हटाओd then the z-order can potentially change. To ensure
	 * correct z-order and pipe acquisition the current DC architecture
	 * requires us to हटाओ and recreate all existing planes.
	 *
	 * TODO: Come up with a more elegant solution क्रम this.
	 */
	क्रम_each_oldnew_plane_in_state(state, other, old_other_state, new_other_state, i) अणु
		काष्ठा amdgpu_framebuffer *old_afb, *new_afb;
		अगर (other->type == DRM_PLANE_TYPE_CURSOR)
			जारी;

		अगर (old_other_state->crtc != new_plane_state->crtc &&
		    new_other_state->crtc != new_plane_state->crtc)
			जारी;

		अगर (old_other_state->crtc != new_other_state->crtc)
			वापस true;

		/* Src/dst size and scaling updates. */
		अगर (old_other_state->src_w != new_other_state->src_w ||
		    old_other_state->src_h != new_other_state->src_h ||
		    old_other_state->crtc_w != new_other_state->crtc_w ||
		    old_other_state->crtc_h != new_other_state->crtc_h)
			वापस true;

		/* Rotation / mirroring updates. */
		अगर (old_other_state->rotation != new_other_state->rotation)
			वापस true;

		/* Blending updates. */
		अगर (old_other_state->pixel_blend_mode !=
		    new_other_state->pixel_blend_mode)
			वापस true;

		/* Alpha updates. */
		अगर (old_other_state->alpha != new_other_state->alpha)
			वापस true;

		/* Colorspace changes. */
		अगर (old_other_state->color_range != new_other_state->color_range ||
		    old_other_state->color_encoding != new_other_state->color_encoding)
			वापस true;

		/* Framebuffer checks fall at the end. */
		अगर (!old_other_state->fb || !new_other_state->fb)
			जारी;

		/* Pixel क्रमmat changes can require bandwidth updates. */
		अगर (old_other_state->fb->क्रमmat != new_other_state->fb->क्रमmat)
			वापस true;

		old_afb = (काष्ठा amdgpu_framebuffer *)old_other_state->fb;
		new_afb = (काष्ठा amdgpu_framebuffer *)new_other_state->fb;

		/* Tiling and DCC changes also require bandwidth updates. */
		अगर (old_afb->tiling_flags != new_afb->tiling_flags ||
		    old_afb->base.modअगरier != new_afb->base.modअगरier)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक dm_check_cursor_fb(काष्ठा amdgpu_crtc *new_acrtc,
			      काष्ठा drm_plane_state *new_plane_state,
			      काष्ठा drm_framebuffer *fb)
अणु
	काष्ठा amdgpu_device *adev = drm_to_adev(new_acrtc->base.dev);
	काष्ठा amdgpu_framebuffer *afb = to_amdgpu_framebuffer(fb);
	अचिन्हित पूर्णांक pitch;
	bool linear;

	अगर (fb->width > new_acrtc->max_cursor_width ||
	    fb->height > new_acrtc->max_cursor_height) अणु
		DRM_DEBUG_ATOMIC("Bad cursor FB size %dx%d\n",
				 new_plane_state->fb->width,
				 new_plane_state->fb->height);
		वापस -EINVAL;
	पूर्ण
	अगर (new_plane_state->src_w != fb->width << 16 ||
	    new_plane_state->src_h != fb->height << 16) अणु
		DRM_DEBUG_ATOMIC("Cropping not supported for cursor plane\n");
		वापस -EINVAL;
	पूर्ण

	/* Pitch in pixels */
	pitch = fb->pitches[0] / fb->क्रमmat->cpp[0];

	अगर (fb->width != pitch) अणु
		DRM_DEBUG_ATOMIC("Cursor FB width %d doesn't match pitch %d",
				 fb->width, pitch);
		वापस -EINVAL;
	पूर्ण

	चयन (pitch) अणु
	हाल 64:
	हाल 128:
	हाल 256:
		/* FB pitch is supported by cursor plane */
		अवरोध;
	शेष:
		DRM_DEBUG_ATOMIC("Bad cursor FB pitch %d px\n", pitch);
		वापस -EINVAL;
	पूर्ण

	/* Core DRM takes care of checking FB modअगरiers, so we only need to
	 * check tiling flags when the FB करोesn't have a modअगरier. */
	अगर (!(fb->flags & DRM_MODE_FB_MODIFIERS)) अणु
		अगर (adev->family < AMDGPU_FAMILY_AI) अणु
			linear = AMDGPU_TILING_GET(afb->tiling_flags, ARRAY_MODE) != DC_ARRAY_2D_TILED_THIN1 &&
			         AMDGPU_TILING_GET(afb->tiling_flags, ARRAY_MODE) != DC_ARRAY_1D_TILED_THIN1 &&
				 AMDGPU_TILING_GET(afb->tiling_flags, MICRO_TILE_MODE) == 0;
		पूर्ण अन्यथा अणु
			linear = AMDGPU_TILING_GET(afb->tiling_flags, SWIZZLE_MODE) == 0;
		पूर्ण
		अगर (!linear) अणु
			DRM_DEBUG_ATOMIC("Cursor FB not linear");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dm_update_plane_state(काष्ठा dc *dc,
				 काष्ठा drm_atomic_state *state,
				 काष्ठा drm_plane *plane,
				 काष्ठा drm_plane_state *old_plane_state,
				 काष्ठा drm_plane_state *new_plane_state,
				 bool enable,
				 bool *lock_and_validation_needed)
अणु

	काष्ठा dm_atomic_state *dm_state = शून्य;
	काष्ठा drm_crtc *new_plane_crtc, *old_plane_crtc;
	काष्ठा drm_crtc_state *old_crtc_state, *new_crtc_state;
	काष्ठा dm_crtc_state *dm_new_crtc_state, *dm_old_crtc_state;
	काष्ठा dm_plane_state *dm_new_plane_state, *dm_old_plane_state;
	काष्ठा amdgpu_crtc *new_acrtc;
	bool needs_reset;
	पूर्णांक ret = 0;


	new_plane_crtc = new_plane_state->crtc;
	old_plane_crtc = old_plane_state->crtc;
	dm_new_plane_state = to_dm_plane_state(new_plane_state);
	dm_old_plane_state = to_dm_plane_state(old_plane_state);

	अगर (plane->type == DRM_PLANE_TYPE_CURSOR) अणु
		अगर (!enable || !new_plane_crtc ||
			drm_atomic_plane_disabling(plane->state, new_plane_state))
			वापस 0;

		new_acrtc = to_amdgpu_crtc(new_plane_crtc);

		अगर (new_plane_state->src_x != 0 || new_plane_state->src_y != 0) अणु
			DRM_DEBUG_ATOMIC("Cropping not supported for cursor plane\n");
			वापस -EINVAL;
		पूर्ण

		अगर (new_plane_state->fb) अणु
			ret = dm_check_cursor_fb(new_acrtc, new_plane_state,
						 new_plane_state->fb);
			अगर (ret)
				वापस ret;
		पूर्ण

		वापस 0;
	पूर्ण

	needs_reset = should_reset_plane(state, plane, old_plane_state,
					 new_plane_state);

	/* Remove any changed/हटाओd planes */
	अगर (!enable) अणु
		अगर (!needs_reset)
			वापस 0;

		अगर (!old_plane_crtc)
			वापस 0;

		old_crtc_state = drm_atomic_get_old_crtc_state(
				state, old_plane_crtc);
		dm_old_crtc_state = to_dm_crtc_state(old_crtc_state);

		अगर (!dm_old_crtc_state->stream)
			वापस 0;

		DRM_DEBUG_ATOMIC("Disabling DRM plane: %d on DRM crtc %d\n",
				plane->base.id, old_plane_crtc->base.id);

		ret = dm_atomic_get_state(state, &dm_state);
		अगर (ret)
			वापस ret;

		अगर (!dc_हटाओ_plane_from_context(
				dc,
				dm_old_crtc_state->stream,
				dm_old_plane_state->dc_state,
				dm_state->context)) अणु

			वापस -EINVAL;
		पूर्ण


		dc_plane_state_release(dm_old_plane_state->dc_state);
		dm_new_plane_state->dc_state = शून्य;

		*lock_and_validation_needed = true;

	पूर्ण अन्यथा अणु /* Add new planes */
		काष्ठा dc_plane_state *dc_new_plane_state;

		अगर (drm_atomic_plane_disabling(plane->state, new_plane_state))
			वापस 0;

		अगर (!new_plane_crtc)
			वापस 0;

		new_crtc_state = drm_atomic_get_new_crtc_state(state, new_plane_crtc);
		dm_new_crtc_state = to_dm_crtc_state(new_crtc_state);

		अगर (!dm_new_crtc_state->stream)
			वापस 0;

		अगर (!needs_reset)
			वापस 0;

		ret = dm_plane_helper_check_state(new_plane_state, new_crtc_state);
		अगर (ret)
			वापस ret;

		WARN_ON(dm_new_plane_state->dc_state);

		dc_new_plane_state = dc_create_plane_state(dc);
		अगर (!dc_new_plane_state)
			वापस -ENOMEM;

		DRM_DEBUG_ATOMIC("Enabling DRM plane: %d on DRM crtc %d\n",
				 plane->base.id, new_plane_crtc->base.id);

		ret = fill_dc_plane_attributes(
			drm_to_adev(new_plane_crtc->dev),
			dc_new_plane_state,
			new_plane_state,
			new_crtc_state);
		अगर (ret) अणु
			dc_plane_state_release(dc_new_plane_state);
			वापस ret;
		पूर्ण

		ret = dm_atomic_get_state(state, &dm_state);
		अगर (ret) अणु
			dc_plane_state_release(dc_new_plane_state);
			वापस ret;
		पूर्ण

		/*
		 * Any atomic check errors that occur after this will
		 * not need a release. The plane state will be attached
		 * to the stream, and thereक्रमe part of the atomic
		 * state. It'll be released when the atomic state is
		 * cleaned.
		 */
		अगर (!dc_add_plane_to_context(
				dc,
				dm_new_crtc_state->stream,
				dc_new_plane_state,
				dm_state->context)) अणु

			dc_plane_state_release(dc_new_plane_state);
			वापस -EINVAL;
		पूर्ण

		dm_new_plane_state->dc_state = dc_new_plane_state;

		/* Tell DC to करो a full surface update every समय there
		 * is a plane change. Inefficient, but works क्रम now.
		 */
		dm_new_plane_state->dc_state->update_flags.bits.full_update = 1;

		*lock_and_validation_needed = true;
	पूर्ण


	वापस ret;
पूर्ण

अटल पूर्णांक dm_check_crtc_cursor(काष्ठा drm_atomic_state *state,
				काष्ठा drm_crtc *crtc,
				काष्ठा drm_crtc_state *new_crtc_state)
अणु
	काष्ठा drm_plane_state *new_cursor_state, *new_primary_state;
	पूर्णांक cursor_scale_w, cursor_scale_h, primary_scale_w, primary_scale_h;

	/* On DCE and DCN there is no dedicated hardware cursor plane. We get a
	 * cursor per pipe but it's going to inherit the scaling and
	 * positioning from the underlying pipe. Check the cursor plane's
	 * blending properties match the primary plane's. */

	new_cursor_state = drm_atomic_get_new_plane_state(state, crtc->cursor);
	new_primary_state = drm_atomic_get_new_plane_state(state, crtc->primary);
	अगर (!new_cursor_state || !new_primary_state ||
	    !new_cursor_state->fb || !new_primary_state->fb) अणु
		वापस 0;
	पूर्ण

	cursor_scale_w = new_cursor_state->crtc_w * 1000 /
			 (new_cursor_state->src_w >> 16);
	cursor_scale_h = new_cursor_state->crtc_h * 1000 /
			 (new_cursor_state->src_h >> 16);

	primary_scale_w = new_primary_state->crtc_w * 1000 /
			 (new_primary_state->src_w >> 16);
	primary_scale_h = new_primary_state->crtc_h * 1000 /
			 (new_primary_state->src_h >> 16);

	अगर (cursor_scale_w != primary_scale_w ||
	    cursor_scale_h != primary_scale_h) अणु
		drm_dbg_atomic(crtc->dev, "Cursor plane scaling doesn't match primary plane\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
अटल पूर्णांक add_affected_mst_dsc_crtcs(काष्ठा drm_atomic_state *state, काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_state *conn_state;
	काष्ठा amdgpu_dm_connector *aconnector = शून्य;
	पूर्णांक i;
	क्रम_each_new_connector_in_state(state, connector, conn_state, i) अणु
		अगर (conn_state->crtc != crtc)
			जारी;

		aconnector = to_amdgpu_dm_connector(connector);
		अगर (!aconnector->port || !aconnector->mst_port)
			aconnector = शून्य;
		अन्यथा
			अवरोध;
	पूर्ण

	अगर (!aconnector)
		वापस 0;

	वापस drm_dp_mst_add_affected_dsc_crtcs(state, &aconnector->mst_port->mst_mgr);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक validate_overlay(काष्ठा drm_atomic_state *state)
अणु
	पूर्णांक i;
	काष्ठा drm_plane *plane;
	काष्ठा drm_plane_state *old_plane_state, *new_plane_state;
	काष्ठा drm_plane_state *primary_state, *cursor_state, *overlay_state = शून्य;

	/* Check अगर primary plane is contained inside overlay */
	क्रम_each_oldnew_plane_in_state_reverse(state, plane, old_plane_state, new_plane_state, i) अणु
		अगर (plane->type == DRM_PLANE_TYPE_OVERLAY) अणु
			अगर (drm_atomic_plane_disabling(plane->state, new_plane_state))
				वापस 0;

			overlay_state = new_plane_state;
			जारी;
		पूर्ण
	पूर्ण

	/* check अगर we're making changes to the overlay plane */
	अगर (!overlay_state)
		वापस 0;

	/* check अगर overlay plane is enabled */
	अगर (!overlay_state->crtc)
		वापस 0;

	/* find the primary plane क्रम the CRTC that the overlay is enabled on */
	primary_state = drm_atomic_get_plane_state(state, overlay_state->crtc->primary);
	अगर (IS_ERR(primary_state))
		वापस PTR_ERR(primary_state);

	/* check अगर primary plane is enabled */
	अगर (!primary_state->crtc)
		वापस 0;

	/* check अगर cursor plane is enabled */
	cursor_state = drm_atomic_get_plane_state(state, overlay_state->crtc->cursor);
	अगर (IS_ERR(cursor_state))
		वापस PTR_ERR(cursor_state);

	अगर (drm_atomic_plane_disabling(plane->state, cursor_state))
		वापस 0;

	/* Perक्रमm the bounds check to ensure the overlay plane covers the primary */
	अगर (primary_state->crtc_x < overlay_state->crtc_x ||
	    primary_state->crtc_y < overlay_state->crtc_y ||
	    primary_state->crtc_x + primary_state->crtc_w > overlay_state->crtc_x + overlay_state->crtc_w ||
	    primary_state->crtc_y + primary_state->crtc_h > overlay_state->crtc_y + overlay_state->crtc_h) अणु
		DRM_DEBUG_ATOMIC("Overlay plane is enabled with hardware cursor but does not fully cover primary plane\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * amdgpu_dm_atomic_check() - Atomic check implementation क्रम AMDgpu DM.
 * @dev: The DRM device
 * @state: The atomic state to commit
 *
 * Validate that the given atomic state is programmable by DC पूर्णांकo hardware.
 * This involves स्थिरructing a &काष्ठा dc_state reflecting the new hardware
 * state we wish to commit, then querying DC to see अगर it is programmable. It's
 * important not to modअगरy the existing DC state. Otherwise, atomic_check
 * may unexpectedly commit hardware changes.
 *
 * When validating the DC state, it's important that the right locks are
 * acquired. For full updates हाल which हटाओs/adds/updates streams on one
 * CRTC जबतक flipping on another CRTC, acquiring global lock will guarantee
 * that any such full update commit will रुको क्रम completion of any outstanding
 * flip using DRMs synchronization events.
 *
 * Note that DM adds the affected connectors क्रम all CRTCs in state, when that
 * might not seem necessary. This is because DC stream creation requires the
 * DC sink, which is tied to the DRM connector state. Cleaning this up should
 * be possible but non-trivial - a possible TODO item.
 *
 * Return: -Error code अगर validation failed.
 */
अटल पूर्णांक amdgpu_dm_atomic_check(काष्ठा drm_device *dev,
				  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा dm_atomic_state *dm_state = शून्य;
	काष्ठा dc *dc = adev->dm.dc;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_state *old_con_state, *new_con_state;
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *old_crtc_state, *new_crtc_state;
	काष्ठा drm_plane *plane;
	काष्ठा drm_plane_state *old_plane_state, *new_plane_state;
	क्रमागत dc_status status;
	पूर्णांक ret, i;
	bool lock_and_validation_needed = false;
	काष्ठा dm_crtc_state *dm_old_crtc_state;

	trace_amdgpu_dm_atomic_check_begin(state);

	ret = drm_atomic_helper_check_modeset(dev, state);
	अगर (ret)
		जाओ fail;

	/* Check connector changes */
	क्रम_each_oldnew_connector_in_state(state, connector, old_con_state, new_con_state, i) अणु
		काष्ठा dm_connector_state *dm_old_con_state = to_dm_connector_state(old_con_state);
		काष्ठा dm_connector_state *dm_new_con_state = to_dm_connector_state(new_con_state);

		/* Skip connectors that are disabled or part of modeset alपढ़ोy. */
		अगर (!old_con_state->crtc && !new_con_state->crtc)
			जारी;

		अगर (!new_con_state->crtc)
			जारी;

		new_crtc_state = drm_atomic_get_crtc_state(state, new_con_state->crtc);
		अगर (IS_ERR(new_crtc_state)) अणु
			ret = PTR_ERR(new_crtc_state);
			जाओ fail;
		पूर्ण

		अगर (dm_old_con_state->abm_level !=
		    dm_new_con_state->abm_level)
			new_crtc_state->connectors_changed = true;
	पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	अगर (dc_resource_is_dsc_encoding_supported(dc)) अणु
		क्रम_each_oldnew_crtc_in_state(state, crtc, old_crtc_state, new_crtc_state, i) अणु
			अगर (drm_atomic_crtc_needs_modeset(new_crtc_state)) अणु
				ret = add_affected_mst_dsc_crtcs(state, crtc);
				अगर (ret)
					जाओ fail;
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	क्रम_each_oldnew_crtc_in_state(state, crtc, old_crtc_state, new_crtc_state, i) अणु
		dm_old_crtc_state = to_dm_crtc_state(old_crtc_state);

		अगर (!drm_atomic_crtc_needs_modeset(new_crtc_state) &&
		    !new_crtc_state->color_mgmt_changed &&
		    old_crtc_state->vrr_enabled == new_crtc_state->vrr_enabled &&
			dm_old_crtc_state->dsc_क्रमce_changed == false)
			जारी;

		अगर (!new_crtc_state->enable)
			जारी;

		ret = drm_atomic_add_affected_connectors(state, crtc);
		अगर (ret)
			वापस ret;

		ret = drm_atomic_add_affected_planes(state, crtc);
		अगर (ret)
			जाओ fail;

		अगर (dm_old_crtc_state->dsc_क्रमce_changed)
			new_crtc_state->mode_changed = true;
	पूर्ण

	/*
	 * Add all primary and overlay planes on the CRTC to the state
	 * whenever a plane is enabled to मुख्यtain correct z-ordering
	 * and to enable fast surface updates.
	 */
	drm_क्रम_each_crtc(crtc, dev) अणु
		bool modअगरied = false;

		क्रम_each_oldnew_plane_in_state(state, plane, old_plane_state, new_plane_state, i) अणु
			अगर (plane->type == DRM_PLANE_TYPE_CURSOR)
				जारी;

			अगर (new_plane_state->crtc == crtc ||
			    old_plane_state->crtc == crtc) अणु
				modअगरied = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!modअगरied)
			जारी;

		drm_क्रम_each_plane_mask(plane, state->dev, crtc->state->plane_mask) अणु
			अगर (plane->type == DRM_PLANE_TYPE_CURSOR)
				जारी;

			new_plane_state =
				drm_atomic_get_plane_state(state, plane);

			अगर (IS_ERR(new_plane_state)) अणु
				ret = PTR_ERR(new_plane_state);
				जाओ fail;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Remove निकासing planes अगर they are modअगरied */
	क्रम_each_oldnew_plane_in_state_reverse(state, plane, old_plane_state, new_plane_state, i) अणु
		ret = dm_update_plane_state(dc, state, plane,
					    old_plane_state,
					    new_plane_state,
					    false,
					    &lock_and_validation_needed);
		अगर (ret)
			जाओ fail;
	पूर्ण

	/* Disable all crtcs which require disable */
	क्रम_each_oldnew_crtc_in_state(state, crtc, old_crtc_state, new_crtc_state, i) अणु
		ret = dm_update_crtc_state(&adev->dm, state, crtc,
					   old_crtc_state,
					   new_crtc_state,
					   false,
					   &lock_and_validation_needed);
		अगर (ret)
			जाओ fail;
	पूर्ण

	/* Enable all crtcs which require enable */
	क्रम_each_oldnew_crtc_in_state(state, crtc, old_crtc_state, new_crtc_state, i) अणु
		ret = dm_update_crtc_state(&adev->dm, state, crtc,
					   old_crtc_state,
					   new_crtc_state,
					   true,
					   &lock_and_validation_needed);
		अगर (ret)
			जाओ fail;
	पूर्ण

	ret = validate_overlay(state);
	अगर (ret)
		जाओ fail;

	/* Add new/modअगरied planes */
	क्रम_each_oldnew_plane_in_state_reverse(state, plane, old_plane_state, new_plane_state, i) अणु
		ret = dm_update_plane_state(dc, state, plane,
					    old_plane_state,
					    new_plane_state,
					    true,
					    &lock_and_validation_needed);
		अगर (ret)
			जाओ fail;
	पूर्ण

	/* Run this here since we want to validate the streams we created */
	ret = drm_atomic_helper_check_planes(dev, state);
	अगर (ret)
		जाओ fail;

	/* Check cursor planes scaling */
	क्रम_each_new_crtc_in_state(state, crtc, new_crtc_state, i) अणु
		ret = dm_check_crtc_cursor(state, crtc, new_crtc_state);
		अगर (ret)
			जाओ fail;
	पूर्ण

	अगर (state->legacy_cursor_update) अणु
		/*
		 * This is a fast cursor update coming from the plane update
		 * helper, check अगर it can be करोne asynchronously क्रम better
		 * perक्रमmance.
		 */
		state->async_update =
			!drm_atomic_helper_async_check(dev, state);

		/*
		 * Skip the reमुख्यing global validation अगर this is an async
		 * update. Cursor updates can be करोne without affecting
		 * state or bandwidth calcs and this aव्योमs the perक्रमmance
		 * penalty of locking the निजी state object and
		 * allocating a new dc_state.
		 */
		अगर (state->async_update)
			वापस 0;
	पूर्ण

	/* Check scaling and underscan changes*/
	/* TODO Removed scaling changes validation due to inability to commit
	 * new stream पूर्णांकo context w\o causing full reset. Need to
	 * decide how to handle.
	 */
	क्रम_each_oldnew_connector_in_state(state, connector, old_con_state, new_con_state, i) अणु
		काष्ठा dm_connector_state *dm_old_con_state = to_dm_connector_state(old_con_state);
		काष्ठा dm_connector_state *dm_new_con_state = to_dm_connector_state(new_con_state);
		काष्ठा amdgpu_crtc *acrtc = to_amdgpu_crtc(dm_new_con_state->base.crtc);

		/* Skip any modesets/resets */
		अगर (!acrtc || drm_atomic_crtc_needs_modeset(
				drm_atomic_get_new_crtc_state(state, &acrtc->base)))
			जारी;

		/* Skip any thing not scale or underscan changes */
		अगर (!is_scaling_state_dअगरferent(dm_new_con_state, dm_old_con_state))
			जारी;

		lock_and_validation_needed = true;
	पूर्ण

	/**
	 * Streams and planes are reset when there are changes that affect
	 * bandwidth. Anything that affects bandwidth needs to go through
	 * DC global validation to ensure that the configuration can be applied
	 * to hardware.
	 *
	 * We have to currently stall out here in atomic_check क्रम outstanding
	 * commits to finish in this हाल because our IRQ handlers reference
	 * DRM state directly - we can end up disabling पूर्णांकerrupts too early
	 * अगर we करोn't.
	 *
	 * TODO: Remove this stall and drop DM state निजी objects.
	 */
	अगर (lock_and_validation_needed) अणु
		ret = dm_atomic_get_state(state, &dm_state);
		अगर (ret)
			जाओ fail;

		ret = करो_aquire_global_lock(dev, state);
		अगर (ret)
			जाओ fail;

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
		अगर (!compute_mst_dsc_configs_क्रम_state(state, dm_state->context))
			जाओ fail;

		ret = dm_update_mst_vcpi_slots_क्रम_dsc(state, dm_state->context);
		अगर (ret)
			जाओ fail;
#पूर्ण_अगर

		/*
		 * Perक्रमm validation of MST topology in the state:
		 * We need to perक्रमm MST atomic check beक्रमe calling
		 * dc_validate_global_state(), or there is a chance
		 * to get stuck in an infinite loop and hang eventually.
		 */
		ret = drm_dp_mst_atomic_check(state);
		अगर (ret)
			जाओ fail;
		status = dc_validate_global_state(dc, dm_state->context, false);
		अगर (status != DC_OK) अणु
			DC_LOG_WARNING("DC global validation failure: %s (%d)",
				       dc_status_to_str(status), status);
			ret = -EINVAL;
			जाओ fail;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * The commit is a fast update. Fast updates shouldn't change
		 * the DC context, affect global validation, and can have their
		 * commit work करोne in parallel with other commits not touching
		 * the same resource. If we have a new DC context as part of
		 * the DM atomic state from validation we need to मुक्त it and
		 * retain the existing one instead.
		 *
		 * Furthermore, since the DM atomic state only contains the DC
		 * context and can safely be annulled, we can मुक्त the state
		 * and clear the associated निजी object now to मुक्त
		 * some memory and aव्योम a possible use-after-मुक्त later.
		 */

		क्रम (i = 0; i < state->num_निजी_objs; i++) अणु
			काष्ठा drm_निजी_obj *obj = state->निजी_objs[i].ptr;

			अगर (obj->funcs == adev->dm.atomic_obj.funcs) अणु
				पूर्णांक j = state->num_निजी_objs-1;

				dm_atomic_destroy_state(obj,
						state->निजी_objs[i].state);

				/* If i is not at the end of the array then the
				 * last element needs to be moved to where i was
				 * beक्रमe the array can safely be truncated.
				 */
				अगर (i != j)
					state->निजी_objs[i] =
						state->निजी_objs[j];

				state->निजी_objs[j].ptr = शून्य;
				state->निजी_objs[j].state = शून्य;
				state->निजी_objs[j].old_state = शून्य;
				state->निजी_objs[j].new_state = शून्य;

				state->num_निजी_objs = j;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Store the overall update type क्रम use later in atomic check. */
	क्रम_each_new_crtc_in_state (state, crtc, new_crtc_state, i) अणु
		काष्ठा dm_crtc_state *dm_new_crtc_state =
			to_dm_crtc_state(new_crtc_state);

		dm_new_crtc_state->update_type = lock_and_validation_needed ?
							 UPDATE_TYPE_FULL :
							 UPDATE_TYPE_FAST;
	पूर्ण

	/* Must be success */
	WARN_ON(ret);

	trace_amdgpu_dm_atomic_check_finish(state, ret);

	वापस ret;

fail:
	अगर (ret == -EDEADLK)
		DRM_DEBUG_DRIVER("Atomic check stopped to avoid deadlock.\n");
	अन्यथा अगर (ret == -EINTR || ret == -EAGAIN || ret == -ERESTARTSYS)
		DRM_DEBUG_DRIVER("Atomic check stopped due to signal.\n");
	अन्यथा
		DRM_DEBUG_DRIVER("Atomic check failed with err: %d \n", ret);

	trace_amdgpu_dm_atomic_check_finish(state, ret);

	वापस ret;
पूर्ण

अटल bool is_dp_capable_without_timing_msa(काष्ठा dc *dc,
					     काष्ठा amdgpu_dm_connector *amdgpu_dm_connector)
अणु
	uपूर्णांक8_t dpcd_data;
	bool capable = false;

	अगर (amdgpu_dm_connector->dc_link &&
		dm_helpers_dp_पढ़ो_dpcd(
				शून्य,
				amdgpu_dm_connector->dc_link,
				DP_DOWN_STREAM_PORT_COUNT,
				&dpcd_data,
				माप(dpcd_data))) अणु
		capable = (dpcd_data & DP_MSA_TIMING_PAR_IGNORED) ? true:false;
	पूर्ण

	वापस capable;
पूर्ण

अटल bool parse_edid_cea(काष्ठा amdgpu_dm_connector *aconnector,
		uपूर्णांक8_t *edid_ext, पूर्णांक len,
		काष्ठा amdgpu_hdmi_vsdb_info *vsdb_info)
अणु
	पूर्णांक i;
	काष्ठा amdgpu_device *adev = drm_to_adev(aconnector->base.dev);
	काष्ठा dc *dc = adev->dm.dc;

	/* send extension block to DMCU क्रम parsing */
	क्रम (i = 0; i < len; i += 8) अणु
		bool res;
		पूर्णांक offset;

		/* send 8 bytes a समय */
		अगर (!dc_edid_parser_send_cea(dc, i, len, &edid_ext[i], 8))
			वापस false;

		अगर (i+8 == len) अणु
			/* EDID block sent completed, expect result */
			पूर्णांक version, min_rate, max_rate;

			res = dc_edid_parser_recv_amd_vsdb(dc, &version, &min_rate, &max_rate);
			अगर (res) अणु
				/* amd vsdb found */
				vsdb_info->मुक्तsync_supported = 1;
				vsdb_info->amd_vsdb_version = version;
				vsdb_info->min_refresh_rate_hz = min_rate;
				vsdb_info->max_refresh_rate_hz = max_rate;
				वापस true;
			पूर्ण
			/* not amd vsdb */
			वापस false;
		पूर्ण

		/* check क्रम ack*/
		res = dc_edid_parser_recv_cea_ack(dc, &offset);
		अगर (!res)
			वापस false;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक parse_hdmi_amd_vsdb(काष्ठा amdgpu_dm_connector *aconnector,
		काष्ठा edid *edid, काष्ठा amdgpu_hdmi_vsdb_info *vsdb_info)
अणु
	uपूर्णांक8_t *edid_ext = शून्य;
	पूर्णांक i;
	bool valid_vsdb_found = false;

	/*----- drm_find_cea_extension() -----*/
	/* No EDID or EDID extensions */
	अगर (edid == शून्य || edid->extensions == 0)
		वापस -ENODEV;

	/* Find CEA extension */
	क्रम (i = 0; i < edid->extensions; i++) अणु
		edid_ext = (uपूर्णांक8_t *)edid + EDID_LENGTH * (i + 1);
		अगर (edid_ext[0] == CEA_EXT)
			अवरोध;
	पूर्ण

	अगर (i == edid->extensions)
		वापस -ENODEV;

	/*----- cea_db_offsets() -----*/
	अगर (edid_ext[0] != CEA_EXT)
		वापस -ENODEV;

	valid_vsdb_found = parse_edid_cea(aconnector, edid_ext, EDID_LENGTH, vsdb_info);

	वापस valid_vsdb_found ? i : -ENODEV;
पूर्ण

व्योम amdgpu_dm_update_मुक्तsync_caps(काष्ठा drm_connector *connector,
					काष्ठा edid *edid)
अणु
	पूर्णांक i = 0;
	काष्ठा detailed_timing *timing;
	काष्ठा detailed_non_pixel *data;
	काष्ठा detailed_data_monitor_range *range;
	काष्ठा amdgpu_dm_connector *amdgpu_dm_connector =
			to_amdgpu_dm_connector(connector);
	काष्ठा dm_connector_state *dm_con_state = शून्य;

	काष्ठा drm_device *dev = connector->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	bool मुक्तsync_capable = false;
	काष्ठा amdgpu_hdmi_vsdb_info vsdb_info = अणु0पूर्ण;

	अगर (!connector->state) अणु
		DRM_ERROR("%s - Connector has no state", __func__);
		जाओ update;
	पूर्ण

	अगर (!edid) अणु
		dm_con_state = to_dm_connector_state(connector->state);

		amdgpu_dm_connector->min_vfreq = 0;
		amdgpu_dm_connector->max_vfreq = 0;
		amdgpu_dm_connector->pixel_घड़ी_mhz = 0;

		जाओ update;
	पूर्ण

	dm_con_state = to_dm_connector_state(connector->state);

	अगर (!amdgpu_dm_connector->dc_sink) अणु
		DRM_ERROR("dc_sink NULL, could not add free_sync module.\n");
		जाओ update;
	पूर्ण
	अगर (!adev->dm.मुक्तsync_module)
		जाओ update;


	अगर (amdgpu_dm_connector->dc_sink->sink_संकेत == SIGNAL_TYPE_DISPLAY_PORT
		|| amdgpu_dm_connector->dc_sink->sink_संकेत == SIGNAL_TYPE_EDP) अणु
		bool edid_check_required = false;

		अगर (edid) अणु
			edid_check_required = is_dp_capable_without_timing_msa(
						adev->dm.dc,
						amdgpu_dm_connector);
		पूर्ण

		अगर (edid_check_required == true && (edid->version > 1 ||
		   (edid->version == 1 && edid->revision > 1))) अणु
			क्रम (i = 0; i < 4; i++) अणु

				timing	= &edid->detailed_timings[i];
				data	= &timing->data.other_data;
				range	= &data->data.range;
				/*
				 * Check अगर monitor has continuous frequency mode
				 */
				अगर (data->type != EDID_DETAIL_MONITOR_RANGE)
					जारी;
				/*
				 * Check क्रम flag range limits only. If flag == 1 then
				 * no additional timing inक्रमmation provided.
				 * Default GTF, GTF Secondary curve and CVT are not
				 * supported
				 */
				अगर (range->flags != 1)
					जारी;

				amdgpu_dm_connector->min_vfreq = range->min_vfreq;
				amdgpu_dm_connector->max_vfreq = range->max_vfreq;
				amdgpu_dm_connector->pixel_घड़ी_mhz =
					range->pixel_घड़ी_mhz * 10;

				connector->display_info.monitor_range.min_vfreq = range->min_vfreq;
				connector->display_info.monitor_range.max_vfreq = range->max_vfreq;

				अवरोध;
			पूर्ण

			अगर (amdgpu_dm_connector->max_vfreq -
			    amdgpu_dm_connector->min_vfreq > 10) अणु

				मुक्तsync_capable = true;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (edid && amdgpu_dm_connector->dc_sink->sink_संकेत == SIGNAL_TYPE_HDMI_TYPE_A) अणु
		i = parse_hdmi_amd_vsdb(amdgpu_dm_connector, edid, &vsdb_info);
		अगर (i >= 0 && vsdb_info.मुक्तsync_supported) अणु
			timing  = &edid->detailed_timings[i];
			data    = &timing->data.other_data;

			amdgpu_dm_connector->min_vfreq = vsdb_info.min_refresh_rate_hz;
			amdgpu_dm_connector->max_vfreq = vsdb_info.max_refresh_rate_hz;
			अगर (amdgpu_dm_connector->max_vfreq - amdgpu_dm_connector->min_vfreq > 10)
				मुक्तsync_capable = true;

			connector->display_info.monitor_range.min_vfreq = vsdb_info.min_refresh_rate_hz;
			connector->display_info.monitor_range.max_vfreq = vsdb_info.max_refresh_rate_hz;
		पूर्ण
	पूर्ण

update:
	अगर (dm_con_state)
		dm_con_state->मुक्तsync_capable = मुक्तsync_capable;

	अगर (connector->vrr_capable_property)
		drm_connector_set_vrr_capable_property(connector,
						       मुक्तsync_capable);
पूर्ण

अटल व्योम amdgpu_dm_set_psr_caps(काष्ठा dc_link *link)
अणु
	uपूर्णांक8_t dpcd_data[EDP_PSR_RECEIVER_CAP_SIZE];

	अगर (!(link->connector_संकेत & SIGNAL_TYPE_EDP))
		वापस;
	अगर (link->type == dc_connection_none)
		वापस;
	अगर (dm_helpers_dp_पढ़ो_dpcd(शून्य, link, DP_PSR_SUPPORT,
					dpcd_data, माप(dpcd_data))) अणु
		link->dpcd_caps.psr_caps.psr_version = dpcd_data[0];

		अगर (dpcd_data[0] == 0) अणु
			link->psr_settings.psr_version = DC_PSR_VERSION_UNSUPPORTED;
			link->psr_settings.psr_feature_enabled = false;
		पूर्ण अन्यथा अणु
			link->psr_settings.psr_version = DC_PSR_VERSION_1;
			link->psr_settings.psr_feature_enabled = true;
		पूर्ण

		DRM_INFO("PSR support:%d\n", link->psr_settings.psr_feature_enabled);
	पूर्ण
पूर्ण

/*
 * amdgpu_dm_link_setup_psr() - configure psr link
 * @stream: stream state
 *
 * Return: true अगर success
 */
अटल bool amdgpu_dm_link_setup_psr(काष्ठा dc_stream_state *stream)
अणु
	काष्ठा dc_link *link = शून्य;
	काष्ठा psr_config psr_config = अणु0पूर्ण;
	काष्ठा psr_context psr_context = अणु0पूर्ण;
	bool ret = false;

	अगर (stream == शून्य)
		वापस false;

	link = stream->link;

	psr_config.psr_version = link->dpcd_caps.psr_caps.psr_version;

	अगर (psr_config.psr_version > 0) अणु
		psr_config.psr_निकास_link_training_required = 0x1;
		psr_config.psr_frame_capture_indication_req = 0;
		psr_config.psr_rfb_setup_समय = 0x37;
		psr_config.psr_sdp_transmit_line_num_deadline = 0x20;
		psr_config.allow_smu_optimizations = 0x0;

		ret = dc_link_setup_psr(link, stream, &psr_config, &psr_context);

	पूर्ण
	DRM_DEBUG_DRIVER("PSR link: %d\n",	link->psr_settings.psr_feature_enabled);

	वापस ret;
पूर्ण

/*
 * amdgpu_dm_psr_enable() - enable psr f/w
 * @stream: stream state
 *
 * Return: true अगर success
 */
bool amdgpu_dm_psr_enable(काष्ठा dc_stream_state *stream)
अणु
	काष्ठा dc_link *link = stream->link;
	अचिन्हित पूर्णांक vsync_rate_hz = 0;
	काष्ठा dc_अटल_screen_params params = अणु0पूर्ण;
	/* Calculate number of अटल frames beक्रमe generating पूर्णांकerrupt to
	 * enter PSR.
	 */
	// Init fail safe of 2 frames अटल
	अचिन्हित पूर्णांक num_frames_अटल = 2;

	DRM_DEBUG_DRIVER("Enabling psr...\n");

	vsync_rate_hz = भाग64_u64(भाग64_u64((
			stream->timing.pix_clk_100hz * 100),
			stream->timing.v_total),
			stream->timing.h_total);

	/* Round up
	 * Calculate number of frames such that at least 30 ms of समय has
	 * passed.
	 */
	अगर (vsync_rate_hz != 0) अणु
		अचिन्हित पूर्णांक frame_समय_microsec = 1000000 / vsync_rate_hz;
		num_frames_अटल = (30000 / frame_समय_microsec) + 1;
	पूर्ण

	params.triggers.cursor_update = true;
	params.triggers.overlay_update = true;
	params.triggers.surface_update = true;
	params.num_frames = num_frames_अटल;

	dc_stream_set_अटल_screen_params(link->ctx->dc,
					   &stream, 1,
					   &params);

	वापस dc_link_set_psr_allow_active(link, true, false, false);
पूर्ण

/*
 * amdgpu_dm_psr_disable() - disable psr f/w
 * @stream:  stream state
 *
 * Return: true अगर success
 */
अटल bool amdgpu_dm_psr_disable(काष्ठा dc_stream_state *stream)
अणु

	DRM_DEBUG_DRIVER("Disabling psr...\n");

	वापस dc_link_set_psr_allow_active(stream->link, false, true, false);
पूर्ण

/*
 * amdgpu_dm_psr_disable() - disable psr f/w
 * अगर psr is enabled on any stream
 *
 * Return: true अगर success
 */
अटल bool amdgpu_dm_psr_disable_all(काष्ठा amdgpu_display_manager *dm)
अणु
	DRM_DEBUG_DRIVER("Disabling psr if psr is enabled on any stream\n");
	वापस dc_set_psr_allow_active(dm->dc, false);
पूर्ण

व्योम amdgpu_dm_trigger_timing_sync(काष्ठा drm_device *dev)
अणु
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा dc *dc = adev->dm.dc;
	पूर्णांक i;

	mutex_lock(&adev->dm.dc_lock);
	अगर (dc->current_state) अणु
		क्रम (i = 0; i < dc->current_state->stream_count; ++i)
			dc->current_state->streams[i]
				->triggered_crtc_reset.enabled =
				adev->dm.क्रमce_timing_sync;

		dm_enable_per_frame_crtc_master_sync(dc->current_state);
		dc_trigger_sync(dc, dc->current_state);
	पूर्ण
	mutex_unlock(&adev->dm.dc_lock);
पूर्ण

व्योम dm_ग_लिखो_reg_func(स्थिर काष्ठा dc_context *ctx, uपूर्णांक32_t address,
		       uपूर्णांक32_t value, स्थिर अक्षर *func_name)
अणु
#अगर_घोषित DM_CHECK_ADDR_0
	अगर (address == 0) अणु
		DC_ERR("invalid register write. address = 0");
		वापस;
	पूर्ण
#पूर्ण_अगर
	cgs_ग_लिखो_रेजिस्टर(ctx->cgs_device, address, value);
	trace_amdgpu_dc_wreg(&ctx->perf_trace->ग_लिखो_count, address, value);
पूर्ण

uपूर्णांक32_t dm_पढ़ो_reg_func(स्थिर काष्ठा dc_context *ctx, uपूर्णांक32_t address,
			  स्थिर अक्षर *func_name)
अणु
	uपूर्णांक32_t value;
#अगर_घोषित DM_CHECK_ADDR_0
	अगर (address == 0) अणु
		DC_ERR("invalid register read; address = 0\n");
		वापस 0;
	पूर्ण
#पूर्ण_अगर

	अगर (ctx->dmub_srv &&
	    ctx->dmub_srv->reg_helper_offload.gather_in_progress &&
	    !ctx->dmub_srv->reg_helper_offload.should_burst_ग_लिखो) अणु
		ASSERT(false);
		वापस 0;
	पूर्ण

	value = cgs_पढ़ो_रेजिस्टर(ctx->cgs_device, address);

	trace_amdgpu_dc_rreg(&ctx->perf_trace->पढ़ो_count, address, value);

	वापस value;
पूर्ण
