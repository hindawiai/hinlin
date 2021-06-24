<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
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
 */

#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_vblank.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_pm.h"
#समावेश "amdgpu_i2c.h"
#समावेश "cikd.h"
#समावेश "atom.h"
#समावेश "amdgpu_atombios.h"
#समावेश "atombios_crtc.h"
#समावेश "atombios_encoders.h"
#समावेश "amdgpu_pll.h"
#समावेश "amdgpu_connectors.h"
#समावेश "amdgpu_display.h"
#समावेश "dce_v8_0.h"

#समावेश "dce/dce_8_0_d.h"
#समावेश "dce/dce_8_0_sh_mask.h"

#समावेश "gca/gfx_7_2_enum.h"

#समावेश "gmc/gmc_7_1_d.h"
#समावेश "gmc/gmc_7_1_sh_mask.h"

#समावेश "oss/oss_2_0_d.h"
#समावेश "oss/oss_2_0_sh_mask.h"

अटल व्योम dce_v8_0_set_display_funcs(काष्ठा amdgpu_device *adev);
अटल व्योम dce_v8_0_set_irq_funcs(काष्ठा amdgpu_device *adev);

अटल स्थिर u32 crtc_offsets[6] =
अणु
	CRTC0_REGISTER_OFFSET,
	CRTC1_REGISTER_OFFSET,
	CRTC2_REGISTER_OFFSET,
	CRTC3_REGISTER_OFFSET,
	CRTC4_REGISTER_OFFSET,
	CRTC5_REGISTER_OFFSET
पूर्ण;

अटल स्थिर u32 hpd_offsets[] =
अणु
	HPD0_REGISTER_OFFSET,
	HPD1_REGISTER_OFFSET,
	HPD2_REGISTER_OFFSET,
	HPD3_REGISTER_OFFSET,
	HPD4_REGISTER_OFFSET,
	HPD5_REGISTER_OFFSET
पूर्ण;

अटल स्थिर uपूर्णांक32_t dig_offsets[] = अणु
	CRTC0_REGISTER_OFFSET,
	CRTC1_REGISTER_OFFSET,
	CRTC2_REGISTER_OFFSET,
	CRTC3_REGISTER_OFFSET,
	CRTC4_REGISTER_OFFSET,
	CRTC5_REGISTER_OFFSET,
	(0x13830 - 0x7030) >> 2,
पूर्ण;

अटल स्थिर काष्ठा अणु
	uपूर्णांक32_t	reg;
	uपूर्णांक32_t	vblank;
	uपूर्णांक32_t	vline;
	uपूर्णांक32_t	hpd;

पूर्ण पूर्णांकerrupt_status_offsets[6] = अणु अणु
	.reg = mmDISP_INTERRUPT_STATUS,
	.vblank = DISP_INTERRUPT_STATUS__LB_D1_VBLANK_INTERRUPT_MASK,
	.vline = DISP_INTERRUPT_STATUS__LB_D1_VLINE_INTERRUPT_MASK,
	.hpd = DISP_INTERRUPT_STATUS__DC_HPD1_INTERRUPT_MASK
पूर्ण, अणु
	.reg = mmDISP_INTERRUPT_STATUS_CONTINUE,
	.vblank = DISP_INTERRUPT_STATUS_CONTINUE__LB_D2_VBLANK_INTERRUPT_MASK,
	.vline = DISP_INTERRUPT_STATUS_CONTINUE__LB_D2_VLINE_INTERRUPT_MASK,
	.hpd = DISP_INTERRUPT_STATUS_CONTINUE__DC_HPD2_INTERRUPT_MASK
पूर्ण, अणु
	.reg = mmDISP_INTERRUPT_STATUS_CONTINUE2,
	.vblank = DISP_INTERRUPT_STATUS_CONTINUE2__LB_D3_VBLANK_INTERRUPT_MASK,
	.vline = DISP_INTERRUPT_STATUS_CONTINUE2__LB_D3_VLINE_INTERRUPT_MASK,
	.hpd = DISP_INTERRUPT_STATUS_CONTINUE2__DC_HPD3_INTERRUPT_MASK
पूर्ण, अणु
	.reg = mmDISP_INTERRUPT_STATUS_CONTINUE3,
	.vblank = DISP_INTERRUPT_STATUS_CONTINUE3__LB_D4_VBLANK_INTERRUPT_MASK,
	.vline = DISP_INTERRUPT_STATUS_CONTINUE3__LB_D4_VLINE_INTERRUPT_MASK,
	.hpd = DISP_INTERRUPT_STATUS_CONTINUE3__DC_HPD4_INTERRUPT_MASK
पूर्ण, अणु
	.reg = mmDISP_INTERRUPT_STATUS_CONTINUE4,
	.vblank = DISP_INTERRUPT_STATUS_CONTINUE4__LB_D5_VBLANK_INTERRUPT_MASK,
	.vline = DISP_INTERRUPT_STATUS_CONTINUE4__LB_D5_VLINE_INTERRUPT_MASK,
	.hpd = DISP_INTERRUPT_STATUS_CONTINUE4__DC_HPD5_INTERRUPT_MASK
पूर्ण, अणु
	.reg = mmDISP_INTERRUPT_STATUS_CONTINUE5,
	.vblank = DISP_INTERRUPT_STATUS_CONTINUE5__LB_D6_VBLANK_INTERRUPT_MASK,
	.vline = DISP_INTERRUPT_STATUS_CONTINUE5__LB_D6_VLINE_INTERRUPT_MASK,
	.hpd = DISP_INTERRUPT_STATUS_CONTINUE5__DC_HPD6_INTERRUPT_MASK
पूर्ण पूर्ण;

अटल u32 dce_v8_0_audio_endpt_rreg(काष्ठा amdgpu_device *adev,
				     u32 block_offset, u32 reg)
अणु
	अचिन्हित दीर्घ flags;
	u32 r;

	spin_lock_irqsave(&adev->audio_endpt_idx_lock, flags);
	WREG32(mmAZALIA_F0_CODEC_ENDPOINT_INDEX + block_offset, reg);
	r = RREG32(mmAZALIA_F0_CODEC_ENDPOINT_DATA + block_offset);
	spin_unlock_irqrestore(&adev->audio_endpt_idx_lock, flags);

	वापस r;
पूर्ण

अटल व्योम dce_v8_0_audio_endpt_wreg(काष्ठा amdgpu_device *adev,
				      u32 block_offset, u32 reg, u32 v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adev->audio_endpt_idx_lock, flags);
	WREG32(mmAZALIA_F0_CODEC_ENDPOINT_INDEX + block_offset, reg);
	WREG32(mmAZALIA_F0_CODEC_ENDPOINT_DATA + block_offset, v);
	spin_unlock_irqrestore(&adev->audio_endpt_idx_lock, flags);
पूर्ण

अटल u32 dce_v8_0_vblank_get_counter(काष्ठा amdgpu_device *adev, पूर्णांक crtc)
अणु
	अगर (crtc >= adev->mode_info.num_crtc)
		वापस 0;
	अन्यथा
		वापस RREG32(mmCRTC_STATUS_FRAME_COUNT + crtc_offsets[crtc]);
पूर्ण

अटल व्योम dce_v8_0_pageflip_पूर्णांकerrupt_init(काष्ठा amdgpu_device *adev)
अणु
	अचिन्हित i;

	/* Enable pflip पूर्णांकerrupts */
	क्रम (i = 0; i < adev->mode_info.num_crtc; i++)
		amdgpu_irq_get(adev, &adev->pageflip_irq, i);
पूर्ण

अटल व्योम dce_v8_0_pageflip_पूर्णांकerrupt_fini(काष्ठा amdgpu_device *adev)
अणु
	अचिन्हित i;

	/* Disable pflip पूर्णांकerrupts */
	क्रम (i = 0; i < adev->mode_info.num_crtc; i++)
		amdgpu_irq_put(adev, &adev->pageflip_irq, i);
पूर्ण

/**
 * dce_v8_0_page_flip - pageflip callback.
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @crtc_id: crtc to cleanup pageflip on
 * @crtc_base: new address of the crtc (GPU MC address)
 * @async: asynchronous flip
 *
 * Triggers the actual pageflip by updating the primary
 * surface base address.
 */
अटल व्योम dce_v8_0_page_flip(काष्ठा amdgpu_device *adev,
			       पूर्णांक crtc_id, u64 crtc_base, bool async)
अणु
	काष्ठा amdgpu_crtc *amdgpu_crtc = adev->mode_info.crtcs[crtc_id];
	काष्ठा drm_framebuffer *fb = amdgpu_crtc->base.primary->fb;

	/* flip at hsync क्रम async, शेष is vsync */
	WREG32(mmGRPH_FLIP_CONTROL + amdgpu_crtc->crtc_offset, async ?
	       GRPH_FLIP_CONTROL__GRPH_SURFACE_UPDATE_H_RETRACE_EN_MASK : 0);
	/* update pitch */
	WREG32(mmGRPH_PITCH + amdgpu_crtc->crtc_offset,
	       fb->pitches[0] / fb->क्रमmat->cpp[0]);
	/* update the primary scanout addresses */
	WREG32(mmGRPH_PRIMARY_SURFACE_ADDRESS_HIGH + amdgpu_crtc->crtc_offset,
	       upper_32_bits(crtc_base));
	/* writing to the low address triggers the update */
	WREG32(mmGRPH_PRIMARY_SURFACE_ADDRESS + amdgpu_crtc->crtc_offset,
	       lower_32_bits(crtc_base));
	/* post the ग_लिखो */
	RREG32(mmGRPH_PRIMARY_SURFACE_ADDRESS + amdgpu_crtc->crtc_offset);
पूर्ण

अटल पूर्णांक dce_v8_0_crtc_get_scanoutpos(काष्ठा amdgpu_device *adev, पूर्णांक crtc,
					u32 *vbl, u32 *position)
अणु
	अगर ((crtc < 0) || (crtc >= adev->mode_info.num_crtc))
		वापस -EINVAL;

	*vbl = RREG32(mmCRTC_V_BLANK_START_END + crtc_offsets[crtc]);
	*position = RREG32(mmCRTC_STATUS_POSITION + crtc_offsets[crtc]);

	वापस 0;
पूर्ण

/**
 * dce_v8_0_hpd_sense - hpd sense callback.
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @hpd: hpd (hotplug detect) pin
 *
 * Checks अगर a digital monitor is connected (evergreen+).
 * Returns true अगर connected, false अगर not connected.
 */
अटल bool dce_v8_0_hpd_sense(काष्ठा amdgpu_device *adev,
			       क्रमागत amdgpu_hpd_id hpd)
अणु
	bool connected = false;

	अगर (hpd >= adev->mode_info.num_hpd)
		वापस connected;

	अगर (RREG32(mmDC_HPD1_INT_STATUS + hpd_offsets[hpd]) &
	    DC_HPD1_INT_STATUS__DC_HPD1_SENSE_MASK)
		connected = true;

	वापस connected;
पूर्ण

/**
 * dce_v8_0_hpd_set_polarity - hpd set polarity callback.
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @hpd: hpd (hotplug detect) pin
 *
 * Set the polarity of the hpd pin (evergreen+).
 */
अटल व्योम dce_v8_0_hpd_set_polarity(काष्ठा amdgpu_device *adev,
				      क्रमागत amdgpu_hpd_id hpd)
अणु
	u32 पंचांगp;
	bool connected = dce_v8_0_hpd_sense(adev, hpd);

	अगर (hpd >= adev->mode_info.num_hpd)
		वापस;

	पंचांगp = RREG32(mmDC_HPD1_INT_CONTROL + hpd_offsets[hpd]);
	अगर (connected)
		पंचांगp &= ~DC_HPD1_INT_CONTROL__DC_HPD1_INT_POLARITY_MASK;
	अन्यथा
		पंचांगp |= DC_HPD1_INT_CONTROL__DC_HPD1_INT_POLARITY_MASK;
	WREG32(mmDC_HPD1_INT_CONTROL + hpd_offsets[hpd], पंचांगp);
पूर्ण

/**
 * dce_v8_0_hpd_init - hpd setup callback.
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Setup the hpd pins used by the card (evergreen+).
 * Enable the pin, set the polarity, and enable the hpd पूर्णांकerrupts.
 */
अटल व्योम dce_v8_0_hpd_init(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा drm_device *dev = adev_to_drm(adev);
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter iter;
	u32 पंचांगp;

	drm_connector_list_iter_begin(dev, &iter);
	drm_क्रम_each_connector_iter(connector, &iter) अणु
		काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);

		अगर (amdgpu_connector->hpd.hpd >= adev->mode_info.num_hpd)
			जारी;

		पंचांगp = RREG32(mmDC_HPD1_CONTROL + hpd_offsets[amdgpu_connector->hpd.hpd]);
		पंचांगp |= DC_HPD1_CONTROL__DC_HPD1_EN_MASK;
		WREG32(mmDC_HPD1_CONTROL + hpd_offsets[amdgpu_connector->hpd.hpd], पंचांगp);

		अगर (connector->connector_type == DRM_MODE_CONNECTOR_eDP ||
		    connector->connector_type == DRM_MODE_CONNECTOR_LVDS) अणु
			/* करोn't try to enable hpd on eDP or LVDS aव्योम अवरोधing the
			 * aux dp channel on imac and help (but not completely fix)
			 * https://bugzilla.redhat.com/show_bug.cgi?id=726143
			 * also aव्योम पूर्णांकerrupt storms during dpms.
			 */
			पंचांगp = RREG32(mmDC_HPD1_INT_CONTROL + hpd_offsets[amdgpu_connector->hpd.hpd]);
			पंचांगp &= ~DC_HPD1_INT_CONTROL__DC_HPD1_INT_EN_MASK;
			WREG32(mmDC_HPD1_INT_CONTROL + hpd_offsets[amdgpu_connector->hpd.hpd], पंचांगp);
			जारी;
		पूर्ण

		dce_v8_0_hpd_set_polarity(adev, amdgpu_connector->hpd.hpd);
		amdgpu_irq_get(adev, &adev->hpd_irq, amdgpu_connector->hpd.hpd);
	पूर्ण
	drm_connector_list_iter_end(&iter);
पूर्ण

/**
 * dce_v8_0_hpd_fini - hpd tear करोwn callback.
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Tear करोwn the hpd pins used by the card (evergreen+).
 * Disable the hpd पूर्णांकerrupts.
 */
अटल व्योम dce_v8_0_hpd_fini(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा drm_device *dev = adev_to_drm(adev);
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter iter;
	u32 पंचांगp;

	drm_connector_list_iter_begin(dev, &iter);
	drm_क्रम_each_connector_iter(connector, &iter) अणु
		काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);

		अगर (amdgpu_connector->hpd.hpd >= adev->mode_info.num_hpd)
			जारी;

		पंचांगp = RREG32(mmDC_HPD1_CONTROL + hpd_offsets[amdgpu_connector->hpd.hpd]);
		पंचांगp &= ~DC_HPD1_CONTROL__DC_HPD1_EN_MASK;
		WREG32(mmDC_HPD1_CONTROL + hpd_offsets[amdgpu_connector->hpd.hpd], 0);

		amdgpu_irq_put(adev, &adev->hpd_irq, amdgpu_connector->hpd.hpd);
	पूर्ण
	drm_connector_list_iter_end(&iter);
पूर्ण

अटल u32 dce_v8_0_hpd_get_gpio_reg(काष्ठा amdgpu_device *adev)
अणु
	वापस mmDC_GPIO_HPD_A;
पूर्ण

अटल bool dce_v8_0_is_display_hung(काष्ठा amdgpu_device *adev)
अणु
	u32 crtc_hung = 0;
	u32 crtc_status[6];
	u32 i, j, पंचांगp;

	क्रम (i = 0; i < adev->mode_info.num_crtc; i++) अणु
		अगर (RREG32(mmCRTC_CONTROL + crtc_offsets[i]) & CRTC_CONTROL__CRTC_MASTER_EN_MASK) अणु
			crtc_status[i] = RREG32(mmCRTC_STATUS_HV_COUNT + crtc_offsets[i]);
			crtc_hung |= (1 << i);
		पूर्ण
	पूर्ण

	क्रम (j = 0; j < 10; j++) अणु
		क्रम (i = 0; i < adev->mode_info.num_crtc; i++) अणु
			अगर (crtc_hung & (1 << i)) अणु
				पंचांगp = RREG32(mmCRTC_STATUS_HV_COUNT + crtc_offsets[i]);
				अगर (पंचांगp != crtc_status[i])
					crtc_hung &= ~(1 << i);
			पूर्ण
		पूर्ण
		अगर (crtc_hung == 0)
			वापस false;
		udelay(100);
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम dce_v8_0_set_vga_render_state(काष्ठा amdgpu_device *adev,
					  bool render)
अणु
	u32 पंचांगp;

	/* Lockout access through VGA aperture*/
	पंचांगp = RREG32(mmVGA_HDP_CONTROL);
	अगर (render)
		पंचांगp = REG_SET_FIELD(पंचांगp, VGA_HDP_CONTROL, VGA_MEMORY_DISABLE, 0);
	अन्यथा
		पंचांगp = REG_SET_FIELD(पंचांगp, VGA_HDP_CONTROL, VGA_MEMORY_DISABLE, 1);
	WREG32(mmVGA_HDP_CONTROL, पंचांगp);

	/* disable VGA render */
	पंचांगp = RREG32(mmVGA_RENDER_CONTROL);
	अगर (render)
		पंचांगp = REG_SET_FIELD(पंचांगp, VGA_RENDER_CONTROL, VGA_VSTATUS_CNTL, 1);
	अन्यथा
		पंचांगp = REG_SET_FIELD(पंचांगp, VGA_RENDER_CONTROL, VGA_VSTATUS_CNTL, 0);
	WREG32(mmVGA_RENDER_CONTROL, पंचांगp);
पूर्ण

अटल पूर्णांक dce_v8_0_get_num_crtc(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक num_crtc = 0;

	चयन (adev->asic_type) अणु
	हाल CHIP_BONAIRE:
	हाल CHIP_HAWAII:
		num_crtc = 6;
		अवरोध;
	हाल CHIP_KAVERI:
		num_crtc = 4;
		अवरोध;
	हाल CHIP_KABINI:
	हाल CHIP_MULLINS:
		num_crtc = 2;
		अवरोध;
	शेष:
		num_crtc = 0;
	पूर्ण
	वापस num_crtc;
पूर्ण

व्योम dce_v8_0_disable_dce(काष्ठा amdgpu_device *adev)
अणु
	/*Disable VGA render and enabled crtc, अगर has DCE engine*/
	अगर (amdgpu_atombios_has_dce_engine_info(adev)) अणु
		u32 पंचांगp;
		पूर्णांक crtc_enabled, i;

		dce_v8_0_set_vga_render_state(adev, false);

		/*Disable crtc*/
		क्रम (i = 0; i < dce_v8_0_get_num_crtc(adev); i++) अणु
			crtc_enabled = REG_GET_FIELD(RREG32(mmCRTC_CONTROL + crtc_offsets[i]),
									 CRTC_CONTROL, CRTC_MASTER_EN);
			अगर (crtc_enabled) अणु
				WREG32(mmCRTC_UPDATE_LOCK + crtc_offsets[i], 1);
				पंचांगp = RREG32(mmCRTC_CONTROL + crtc_offsets[i]);
				पंचांगp = REG_SET_FIELD(पंचांगp, CRTC_CONTROL, CRTC_MASTER_EN, 0);
				WREG32(mmCRTC_CONTROL + crtc_offsets[i], पंचांगp);
				WREG32(mmCRTC_UPDATE_LOCK + crtc_offsets[i], 0);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dce_v8_0_program_fmt(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(encoder->crtc);
	काष्ठा drm_connector *connector = amdgpu_get_connector_क्रम_encoder(encoder);
	पूर्णांक bpc = 0;
	u32 पंचांगp = 0;
	क्रमागत amdgpu_connector_dither dither = AMDGPU_FMT_DITHER_DISABLE;

	अगर (connector) अणु
		काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
		bpc = amdgpu_connector_get_monitor_bpc(connector);
		dither = amdgpu_connector->dither;
	पूर्ण

	/* LVDS/eDP FMT is set up by atom */
	अगर (amdgpu_encoder->devices & ATOM_DEVICE_LCD_SUPPORT)
		वापस;

	/* not needed क्रम analog */
	अगर ((amdgpu_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC1) ||
	    (amdgpu_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC2))
		वापस;

	अगर (bpc == 0)
		वापस;

	चयन (bpc) अणु
	हाल 6:
		अगर (dither == AMDGPU_FMT_DITHER_ENABLE)
			/* XXX sort out optimal dither settings */
			पंचांगp |= (FMT_BIT_DEPTH_CONTROL__FMT_FRAME_RANDOM_ENABLE_MASK |
				FMT_BIT_DEPTH_CONTROL__FMT_HIGHPASS_RANDOM_ENABLE_MASK |
				FMT_BIT_DEPTH_CONTROL__FMT_SPATIAL_DITHER_EN_MASK |
				(0 << FMT_BIT_DEPTH_CONTROL__FMT_SPATIAL_DITHER_DEPTH__SHIFT));
		अन्यथा
			पंचांगp |= (FMT_BIT_DEPTH_CONTROL__FMT_TRUNCATE_EN_MASK |
			(0 << FMT_BIT_DEPTH_CONTROL__FMT_TRUNCATE_DEPTH__SHIFT));
		अवरोध;
	हाल 8:
		अगर (dither == AMDGPU_FMT_DITHER_ENABLE)
			/* XXX sort out optimal dither settings */
			पंचांगp |= (FMT_BIT_DEPTH_CONTROL__FMT_FRAME_RANDOM_ENABLE_MASK |
				FMT_BIT_DEPTH_CONTROL__FMT_HIGHPASS_RANDOM_ENABLE_MASK |
				FMT_BIT_DEPTH_CONTROL__FMT_RGB_RANDOM_ENABLE_MASK |
				FMT_BIT_DEPTH_CONTROL__FMT_SPATIAL_DITHER_EN_MASK |
				(1 << FMT_BIT_DEPTH_CONTROL__FMT_SPATIAL_DITHER_DEPTH__SHIFT));
		अन्यथा
			पंचांगp |= (FMT_BIT_DEPTH_CONTROL__FMT_TRUNCATE_EN_MASK |
			(1 << FMT_BIT_DEPTH_CONTROL__FMT_TRUNCATE_DEPTH__SHIFT));
		अवरोध;
	हाल 10:
		अगर (dither == AMDGPU_FMT_DITHER_ENABLE)
			/* XXX sort out optimal dither settings */
			पंचांगp |= (FMT_BIT_DEPTH_CONTROL__FMT_FRAME_RANDOM_ENABLE_MASK |
				FMT_BIT_DEPTH_CONTROL__FMT_HIGHPASS_RANDOM_ENABLE_MASK |
				FMT_BIT_DEPTH_CONTROL__FMT_RGB_RANDOM_ENABLE_MASK |
				FMT_BIT_DEPTH_CONTROL__FMT_SPATIAL_DITHER_EN_MASK |
				(2 << FMT_BIT_DEPTH_CONTROL__FMT_SPATIAL_DITHER_DEPTH__SHIFT));
		अन्यथा
			पंचांगp |= (FMT_BIT_DEPTH_CONTROL__FMT_TRUNCATE_EN_MASK |
			(2 << FMT_BIT_DEPTH_CONTROL__FMT_TRUNCATE_DEPTH__SHIFT));
		अवरोध;
	शेष:
		/* not needed */
		अवरोध;
	पूर्ण

	WREG32(mmFMT_BIT_DEPTH_CONTROL + amdgpu_crtc->crtc_offset, पंचांगp);
पूर्ण


/* display watermark setup */
/**
 * dce_v8_0_line_buffer_adjust - Set up the line buffer
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @amdgpu_crtc: the selected display controller
 * @mode: the current display mode on the selected display
 * controller
 *
 * Setup up the line buffer allocation क्रम
 * the selected display controller (CIK).
 * Returns the line buffer size in pixels.
 */
अटल u32 dce_v8_0_line_buffer_adjust(काष्ठा amdgpu_device *adev,
				       काष्ठा amdgpu_crtc *amdgpu_crtc,
				       काष्ठा drm_display_mode *mode)
अणु
	u32 पंचांगp, buffer_alloc, i;
	u32 pipe_offset = amdgpu_crtc->crtc_id * 0x8;
	/*
	 * Line Buffer Setup
	 * There are 6 line buffers, one क्रम each display controllers.
	 * There are 3 partitions per LB. Select the number of partitions
	 * to enable based on the display width.  For display widths larger
	 * than 4096, you need use to use 2 display controllers and combine
	 * them using the stereo blender.
	 */
	अगर (amdgpu_crtc->base.enabled && mode) अणु
		अगर (mode->crtc_hdisplay < 1920) अणु
			पंचांगp = 1;
			buffer_alloc = 2;
		पूर्ण अन्यथा अगर (mode->crtc_hdisplay < 2560) अणु
			पंचांगp = 2;
			buffer_alloc = 2;
		पूर्ण अन्यथा अगर (mode->crtc_hdisplay < 4096) अणु
			पंचांगp = 0;
			buffer_alloc = (adev->flags & AMD_IS_APU) ? 2 : 4;
		पूर्ण अन्यथा अणु
			DRM_DEBUG_KMS("Mode too big for LB!\n");
			पंचांगp = 0;
			buffer_alloc = (adev->flags & AMD_IS_APU) ? 2 : 4;
		पूर्ण
	पूर्ण अन्यथा अणु
		पंचांगp = 1;
		buffer_alloc = 0;
	पूर्ण

	WREG32(mmLB_MEMORY_CTRL + amdgpu_crtc->crtc_offset,
	      (पंचांगp << LB_MEMORY_CTRL__LB_MEMORY_CONFIG__SHIFT) |
	      (0x6B0 << LB_MEMORY_CTRL__LB_MEMORY_SIZE__SHIFT));

	WREG32(mmPIPE0_DMIF_BUFFER_CONTROL + pipe_offset,
	       (buffer_alloc << PIPE0_DMIF_BUFFER_CONTROL__DMIF_BUFFERS_ALLOCATED__SHIFT));
	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		अगर (RREG32(mmPIPE0_DMIF_BUFFER_CONTROL + pipe_offset) &
		    PIPE0_DMIF_BUFFER_CONTROL__DMIF_BUFFERS_ALLOCATION_COMPLETED_MASK)
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (amdgpu_crtc->base.enabled && mode) अणु
		चयन (पंचांगp) अणु
		हाल 0:
		शेष:
			वापस 4096 * 2;
		हाल 1:
			वापस 1920 * 2;
		हाल 2:
			वापस 2560 * 2;
		पूर्ण
	पूर्ण

	/* controller not enabled, so no lb used */
	वापस 0;
पूर्ण

/**
 * cik_get_number_of_dram_channels - get the number of dram channels
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Look up the number of video ram channels (CIK).
 * Used क्रम display watermark bandwidth calculations
 * Returns the number of dram channels
 */
अटल u32 cik_get_number_of_dram_channels(काष्ठा amdgpu_device *adev)
अणु
	u32 पंचांगp = RREG32(mmMC_SHARED_CHMAP);

	चयन ((पंचांगp & MC_SHARED_CHMAP__NOOFCHAN_MASK) >> MC_SHARED_CHMAP__NOOFCHAN__SHIFT) अणु
	हाल 0:
	शेष:
		वापस 1;
	हाल 1:
		वापस 2;
	हाल 2:
		वापस 4;
	हाल 3:
		वापस 8;
	हाल 4:
		वापस 3;
	हाल 5:
		वापस 6;
	हाल 6:
		वापस 10;
	हाल 7:
		वापस 12;
	हाल 8:
		वापस 16;
	पूर्ण
पूर्ण

काष्ठा dce8_wm_params अणु
	u32 dram_channels; /* number of dram channels */
	u32 yclk;          /* bandwidth per dram data pin in kHz */
	u32 sclk;          /* engine घड़ी in kHz */
	u32 disp_clk;      /* display घड़ी in kHz */
	u32 src_width;     /* viewport width */
	u32 active_समय;   /* active display समय in ns */
	u32 blank_समय;    /* blank समय in ns */
	bool पूर्णांकerlaced;    /* mode is पूर्णांकerlaced */
	fixed20_12 vsc;    /* vertical scale ratio */
	u32 num_heads;     /* number of active crtcs */
	u32 bytes_per_pixel; /* bytes per pixel display + overlay */
	u32 lb_size;       /* line buffer allocated to pipe */
	u32 vtaps;         /* vertical scaler taps */
पूर्ण;

/**
 * dce_v8_0_dram_bandwidth - get the dram bandwidth
 *
 * @wm: watermark calculation data
 *
 * Calculate the raw dram bandwidth (CIK).
 * Used क्रम display watermark bandwidth calculations
 * Returns the dram bandwidth in MBytes/s
 */
अटल u32 dce_v8_0_dram_bandwidth(काष्ठा dce8_wm_params *wm)
अणु
	/* Calculate raw DRAM Bandwidth */
	fixed20_12 dram_efficiency; /* 0.7 */
	fixed20_12 yclk, dram_channels, bandwidth;
	fixed20_12 a;

	a.full = dfixed_स्थिर(1000);
	yclk.full = dfixed_स्थिर(wm->yclk);
	yclk.full = dfixed_भाग(yclk, a);
	dram_channels.full = dfixed_स्थिर(wm->dram_channels * 4);
	a.full = dfixed_स्थिर(10);
	dram_efficiency.full = dfixed_स्थिर(7);
	dram_efficiency.full = dfixed_भाग(dram_efficiency, a);
	bandwidth.full = dfixed_mul(dram_channels, yclk);
	bandwidth.full = dfixed_mul(bandwidth, dram_efficiency);

	वापस dfixed_trunc(bandwidth);
पूर्ण

/**
 * dce_v8_0_dram_bandwidth_क्रम_display - get the dram bandwidth क्रम display
 *
 * @wm: watermark calculation data
 *
 * Calculate the dram bandwidth used क्रम display (CIK).
 * Used क्रम display watermark bandwidth calculations
 * Returns the dram bandwidth क्रम display in MBytes/s
 */
अटल u32 dce_v8_0_dram_bandwidth_क्रम_display(काष्ठा dce8_wm_params *wm)
अणु
	/* Calculate DRAM Bandwidth and the part allocated to display. */
	fixed20_12 disp_dram_allocation; /* 0.3 to 0.7 */
	fixed20_12 yclk, dram_channels, bandwidth;
	fixed20_12 a;

	a.full = dfixed_स्थिर(1000);
	yclk.full = dfixed_स्थिर(wm->yclk);
	yclk.full = dfixed_भाग(yclk, a);
	dram_channels.full = dfixed_स्थिर(wm->dram_channels * 4);
	a.full = dfixed_स्थिर(10);
	disp_dram_allocation.full = dfixed_स्थिर(3); /* XXX worse हाल value 0.3 */
	disp_dram_allocation.full = dfixed_भाग(disp_dram_allocation, a);
	bandwidth.full = dfixed_mul(dram_channels, yclk);
	bandwidth.full = dfixed_mul(bandwidth, disp_dram_allocation);

	वापस dfixed_trunc(bandwidth);
पूर्ण

/**
 * dce_v8_0_data_वापस_bandwidth - get the data वापस bandwidth
 *
 * @wm: watermark calculation data
 *
 * Calculate the data वापस bandwidth used क्रम display (CIK).
 * Used क्रम display watermark bandwidth calculations
 * Returns the data वापस bandwidth in MBytes/s
 */
अटल u32 dce_v8_0_data_वापस_bandwidth(काष्ठा dce8_wm_params *wm)
अणु
	/* Calculate the display Data वापस Bandwidth */
	fixed20_12 वापस_efficiency; /* 0.8 */
	fixed20_12 sclk, bandwidth;
	fixed20_12 a;

	a.full = dfixed_स्थिर(1000);
	sclk.full = dfixed_स्थिर(wm->sclk);
	sclk.full = dfixed_भाग(sclk, a);
	a.full = dfixed_स्थिर(10);
	वापस_efficiency.full = dfixed_स्थिर(8);
	वापस_efficiency.full = dfixed_भाग(वापस_efficiency, a);
	a.full = dfixed_स्थिर(32);
	bandwidth.full = dfixed_mul(a, sclk);
	bandwidth.full = dfixed_mul(bandwidth, वापस_efficiency);

	वापस dfixed_trunc(bandwidth);
पूर्ण

/**
 * dce_v8_0_dmअगर_request_bandwidth - get the dmअगर bandwidth
 *
 * @wm: watermark calculation data
 *
 * Calculate the dmअगर bandwidth used क्रम display (CIK).
 * Used क्रम display watermark bandwidth calculations
 * Returns the dmअगर bandwidth in MBytes/s
 */
अटल u32 dce_v8_0_dmअगर_request_bandwidth(काष्ठा dce8_wm_params *wm)
अणु
	/* Calculate the DMIF Request Bandwidth */
	fixed20_12 disp_clk_request_efficiency; /* 0.8 */
	fixed20_12 disp_clk, bandwidth;
	fixed20_12 a, b;

	a.full = dfixed_स्थिर(1000);
	disp_clk.full = dfixed_स्थिर(wm->disp_clk);
	disp_clk.full = dfixed_भाग(disp_clk, a);
	a.full = dfixed_स्थिर(32);
	b.full = dfixed_mul(a, disp_clk);

	a.full = dfixed_स्थिर(10);
	disp_clk_request_efficiency.full = dfixed_स्थिर(8);
	disp_clk_request_efficiency.full = dfixed_भाग(disp_clk_request_efficiency, a);

	bandwidth.full = dfixed_mul(b, disp_clk_request_efficiency);

	वापस dfixed_trunc(bandwidth);
पूर्ण

/**
 * dce_v8_0_available_bandwidth - get the min available bandwidth
 *
 * @wm: watermark calculation data
 *
 * Calculate the min available bandwidth used क्रम display (CIK).
 * Used क्रम display watermark bandwidth calculations
 * Returns the min available bandwidth in MBytes/s
 */
अटल u32 dce_v8_0_available_bandwidth(काष्ठा dce8_wm_params *wm)
अणु
	/* Calculate the Available bandwidth. Display can use this temporarily but not in average. */
	u32 dram_bandwidth = dce_v8_0_dram_bandwidth(wm);
	u32 data_वापस_bandwidth = dce_v8_0_data_वापस_bandwidth(wm);
	u32 dmअगर_req_bandwidth = dce_v8_0_dmअगर_request_bandwidth(wm);

	वापस min(dram_bandwidth, min(data_वापस_bandwidth, dmअगर_req_bandwidth));
पूर्ण

/**
 * dce_v8_0_average_bandwidth - get the average available bandwidth
 *
 * @wm: watermark calculation data
 *
 * Calculate the average available bandwidth used क्रम display (CIK).
 * Used क्रम display watermark bandwidth calculations
 * Returns the average available bandwidth in MBytes/s
 */
अटल u32 dce_v8_0_average_bandwidth(काष्ठा dce8_wm_params *wm)
अणु
	/* Calculate the display mode Average Bandwidth
	 * DisplayMode should contain the source and destination dimensions,
	 * timing, etc.
	 */
	fixed20_12 bpp;
	fixed20_12 line_समय;
	fixed20_12 src_width;
	fixed20_12 bandwidth;
	fixed20_12 a;

	a.full = dfixed_स्थिर(1000);
	line_समय.full = dfixed_स्थिर(wm->active_समय + wm->blank_समय);
	line_समय.full = dfixed_भाग(line_समय, a);
	bpp.full = dfixed_स्थिर(wm->bytes_per_pixel);
	src_width.full = dfixed_स्थिर(wm->src_width);
	bandwidth.full = dfixed_mul(src_width, bpp);
	bandwidth.full = dfixed_mul(bandwidth, wm->vsc);
	bandwidth.full = dfixed_भाग(bandwidth, line_समय);

	वापस dfixed_trunc(bandwidth);
पूर्ण

/**
 * dce_v8_0_latency_watermark - get the latency watermark
 *
 * @wm: watermark calculation data
 *
 * Calculate the latency watermark (CIK).
 * Used क्रम display watermark bandwidth calculations
 * Returns the latency watermark in ns
 */
अटल u32 dce_v8_0_latency_watermark(काष्ठा dce8_wm_params *wm)
अणु
	/* First calculate the latency in ns */
	u32 mc_latency = 2000; /* 2000 ns. */
	u32 available_bandwidth = dce_v8_0_available_bandwidth(wm);
	u32 worst_chunk_वापस_समय = (512 * 8 * 1000) / available_bandwidth;
	u32 cursor_line_pair_वापस_समय = (128 * 4 * 1000) / available_bandwidth;
	u32 dc_latency = 40000000 / wm->disp_clk; /* dc pipe latency */
	u32 other_heads_data_वापस_समय = ((wm->num_heads + 1) * worst_chunk_वापस_समय) +
		(wm->num_heads * cursor_line_pair_वापस_समय);
	u32 latency = mc_latency + other_heads_data_वापस_समय + dc_latency;
	u32 max_src_lines_per_dst_line, lb_fill_bw, line_fill_समय;
	u32 पंचांगp, dmअगर_size = 12288;
	fixed20_12 a, b, c;

	अगर (wm->num_heads == 0)
		वापस 0;

	a.full = dfixed_स्थिर(2);
	b.full = dfixed_स्थिर(1);
	अगर ((wm->vsc.full > a.full) ||
	    ((wm->vsc.full > b.full) && (wm->vtaps >= 3)) ||
	    (wm->vtaps >= 5) ||
	    ((wm->vsc.full >= a.full) && wm->पूर्णांकerlaced))
		max_src_lines_per_dst_line = 4;
	अन्यथा
		max_src_lines_per_dst_line = 2;

	a.full = dfixed_स्थिर(available_bandwidth);
	b.full = dfixed_स्थिर(wm->num_heads);
	a.full = dfixed_भाग(a, b);
	पंचांगp = भाग_u64((u64) dmअगर_size * (u64) wm->disp_clk, mc_latency + 512);
	पंचांगp = min(dfixed_trunc(a), पंचांगp);

	lb_fill_bw = min(पंचांगp, wm->disp_clk * wm->bytes_per_pixel / 1000);

	a.full = dfixed_स्थिर(max_src_lines_per_dst_line * wm->src_width * wm->bytes_per_pixel);
	b.full = dfixed_स्थिर(1000);
	c.full = dfixed_स्थिर(lb_fill_bw);
	b.full = dfixed_भाग(c, b);
	a.full = dfixed_भाग(a, b);
	line_fill_समय = dfixed_trunc(a);

	अगर (line_fill_समय < wm->active_समय)
		वापस latency;
	अन्यथा
		वापस latency + (line_fill_समय - wm->active_समय);

पूर्ण

/**
 * dce_v8_0_average_bandwidth_vs_dram_bandwidth_क्रम_display - check
 * average and available dram bandwidth
 *
 * @wm: watermark calculation data
 *
 * Check अगर the display average bandwidth fits in the display
 * dram bandwidth (CIK).
 * Used क्रम display watermark bandwidth calculations
 * Returns true अगर the display fits, false अगर not.
 */
अटल bool dce_v8_0_average_bandwidth_vs_dram_bandwidth_क्रम_display(काष्ठा dce8_wm_params *wm)
अणु
	अगर (dce_v8_0_average_bandwidth(wm) <=
	    (dce_v8_0_dram_bandwidth_क्रम_display(wm) / wm->num_heads))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

/**
 * dce_v8_0_average_bandwidth_vs_available_bandwidth - check
 * average and available bandwidth
 *
 * @wm: watermark calculation data
 *
 * Check अगर the display average bandwidth fits in the display
 * available bandwidth (CIK).
 * Used क्रम display watermark bandwidth calculations
 * Returns true अगर the display fits, false अगर not.
 */
अटल bool dce_v8_0_average_bandwidth_vs_available_bandwidth(काष्ठा dce8_wm_params *wm)
अणु
	अगर (dce_v8_0_average_bandwidth(wm) <=
	    (dce_v8_0_available_bandwidth(wm) / wm->num_heads))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

/**
 * dce_v8_0_check_latency_hiding - check latency hiding
 *
 * @wm: watermark calculation data
 *
 * Check latency hiding (CIK).
 * Used क्रम display watermark bandwidth calculations
 * Returns true अगर the display fits, false अगर not.
 */
अटल bool dce_v8_0_check_latency_hiding(काष्ठा dce8_wm_params *wm)
अणु
	u32 lb_partitions = wm->lb_size / wm->src_width;
	u32 line_समय = wm->active_समय + wm->blank_समय;
	u32 latency_tolerant_lines;
	u32 latency_hiding;
	fixed20_12 a;

	a.full = dfixed_स्थिर(1);
	अगर (wm->vsc.full > a.full)
		latency_tolerant_lines = 1;
	अन्यथा अणु
		अगर (lb_partitions <= (wm->vtaps + 1))
			latency_tolerant_lines = 1;
		अन्यथा
			latency_tolerant_lines = 2;
	पूर्ण

	latency_hiding = (latency_tolerant_lines * line_समय + wm->blank_समय);

	अगर (dce_v8_0_latency_watermark(wm) <= latency_hiding)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

/**
 * dce_v8_0_program_watermarks - program display watermarks
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @amdgpu_crtc: the selected display controller
 * @lb_size: line buffer size
 * @num_heads: number of display controllers in use
 *
 * Calculate and program the display watermarks क्रम the
 * selected display controller (CIK).
 */
अटल व्योम dce_v8_0_program_watermarks(काष्ठा amdgpu_device *adev,
					काष्ठा amdgpu_crtc *amdgpu_crtc,
					u32 lb_size, u32 num_heads)
अणु
	काष्ठा drm_display_mode *mode = &amdgpu_crtc->base.mode;
	काष्ठा dce8_wm_params wm_low, wm_high;
	u32 active_समय;
	u32 line_समय = 0;
	u32 latency_watermark_a = 0, latency_watermark_b = 0;
	u32 पंचांगp, wm_mask, lb_vblank_lead_lines = 0;

	अगर (amdgpu_crtc->base.enabled && num_heads && mode) अणु
		active_समय = (u32) भाग_u64((u64)mode->crtc_hdisplay * 1000000,
					    (u32)mode->घड़ी);
		line_समय = (u32) भाग_u64((u64)mode->crtc_htotal * 1000000,
					  (u32)mode->घड़ी);
		line_समय = min(line_समय, (u32)65535);

		/* watermark क्रम high घड़ीs */
		अगर (adev->pm.dpm_enabled) अणु
			wm_high.yclk =
				amdgpu_dpm_get_mclk(adev, false) * 10;
			wm_high.sclk =
				amdgpu_dpm_get_sclk(adev, false) * 10;
		पूर्ण अन्यथा अणु
			wm_high.yclk = adev->pm.current_mclk * 10;
			wm_high.sclk = adev->pm.current_sclk * 10;
		पूर्ण

		wm_high.disp_clk = mode->घड़ी;
		wm_high.src_width = mode->crtc_hdisplay;
		wm_high.active_समय = active_समय;
		wm_high.blank_समय = line_समय - wm_high.active_समय;
		wm_high.पूर्णांकerlaced = false;
		अगर (mode->flags & DRM_MODE_FLAG_INTERLACE)
			wm_high.पूर्णांकerlaced = true;
		wm_high.vsc = amdgpu_crtc->vsc;
		wm_high.vtaps = 1;
		अगर (amdgpu_crtc->rmx_type != RMX_OFF)
			wm_high.vtaps = 2;
		wm_high.bytes_per_pixel = 4; /* XXX: get this from fb config */
		wm_high.lb_size = lb_size;
		wm_high.dram_channels = cik_get_number_of_dram_channels(adev);
		wm_high.num_heads = num_heads;

		/* set क्रम high घड़ीs */
		latency_watermark_a = min(dce_v8_0_latency_watermark(&wm_high), (u32)65535);

		/* possibly क्रमce display priority to high */
		/* should really करो this at mode validation समय... */
		अगर (!dce_v8_0_average_bandwidth_vs_dram_bandwidth_क्रम_display(&wm_high) ||
		    !dce_v8_0_average_bandwidth_vs_available_bandwidth(&wm_high) ||
		    !dce_v8_0_check_latency_hiding(&wm_high) ||
		    (adev->mode_info.disp_priority == 2)) अणु
			DRM_DEBUG_KMS("force priority to high\n");
		पूर्ण

		/* watermark क्रम low घड़ीs */
		अगर (adev->pm.dpm_enabled) अणु
			wm_low.yclk =
				amdgpu_dpm_get_mclk(adev, true) * 10;
			wm_low.sclk =
				amdgpu_dpm_get_sclk(adev, true) * 10;
		पूर्ण अन्यथा अणु
			wm_low.yclk = adev->pm.current_mclk * 10;
			wm_low.sclk = adev->pm.current_sclk * 10;
		पूर्ण

		wm_low.disp_clk = mode->घड़ी;
		wm_low.src_width = mode->crtc_hdisplay;
		wm_low.active_समय = active_समय;
		wm_low.blank_समय = line_समय - wm_low.active_समय;
		wm_low.पूर्णांकerlaced = false;
		अगर (mode->flags & DRM_MODE_FLAG_INTERLACE)
			wm_low.पूर्णांकerlaced = true;
		wm_low.vsc = amdgpu_crtc->vsc;
		wm_low.vtaps = 1;
		अगर (amdgpu_crtc->rmx_type != RMX_OFF)
			wm_low.vtaps = 2;
		wm_low.bytes_per_pixel = 4; /* XXX: get this from fb config */
		wm_low.lb_size = lb_size;
		wm_low.dram_channels = cik_get_number_of_dram_channels(adev);
		wm_low.num_heads = num_heads;

		/* set क्रम low घड़ीs */
		latency_watermark_b = min(dce_v8_0_latency_watermark(&wm_low), (u32)65535);

		/* possibly क्रमce display priority to high */
		/* should really करो this at mode validation समय... */
		अगर (!dce_v8_0_average_bandwidth_vs_dram_bandwidth_क्रम_display(&wm_low) ||
		    !dce_v8_0_average_bandwidth_vs_available_bandwidth(&wm_low) ||
		    !dce_v8_0_check_latency_hiding(&wm_low) ||
		    (adev->mode_info.disp_priority == 2)) अणु
			DRM_DEBUG_KMS("force priority to high\n");
		पूर्ण
		lb_vblank_lead_lines = DIV_ROUND_UP(lb_size, mode->crtc_hdisplay);
	पूर्ण

	/* select wm A */
	wm_mask = RREG32(mmDPG_WATERMARK_MASK_CONTROL + amdgpu_crtc->crtc_offset);
	पंचांगp = wm_mask;
	पंचांगp &= ~(3 << DPG_WATERMARK_MASK_CONTROL__URGENCY_WATERMARK_MASK__SHIFT);
	पंचांगp |= (1 << DPG_WATERMARK_MASK_CONTROL__URGENCY_WATERMARK_MASK__SHIFT);
	WREG32(mmDPG_WATERMARK_MASK_CONTROL + amdgpu_crtc->crtc_offset, पंचांगp);
	WREG32(mmDPG_PIPE_URGENCY_CONTROL + amdgpu_crtc->crtc_offset,
	       ((latency_watermark_a << DPG_PIPE_URGENCY_CONTROL__URGENCY_LOW_WATERMARK__SHIFT) |
		(line_समय << DPG_PIPE_URGENCY_CONTROL__URGENCY_HIGH_WATERMARK__SHIFT)));
	/* select wm B */
	पंचांगp = RREG32(mmDPG_WATERMARK_MASK_CONTROL + amdgpu_crtc->crtc_offset);
	पंचांगp &= ~(3 << DPG_WATERMARK_MASK_CONTROL__URGENCY_WATERMARK_MASK__SHIFT);
	पंचांगp |= (2 << DPG_WATERMARK_MASK_CONTROL__URGENCY_WATERMARK_MASK__SHIFT);
	WREG32(mmDPG_WATERMARK_MASK_CONTROL + amdgpu_crtc->crtc_offset, पंचांगp);
	WREG32(mmDPG_PIPE_URGENCY_CONTROL + amdgpu_crtc->crtc_offset,
	       ((latency_watermark_b << DPG_PIPE_URGENCY_CONTROL__URGENCY_LOW_WATERMARK__SHIFT) |
		(line_समय << DPG_PIPE_URGENCY_CONTROL__URGENCY_HIGH_WATERMARK__SHIFT)));
	/* restore original selection */
	WREG32(mmDPG_WATERMARK_MASK_CONTROL + amdgpu_crtc->crtc_offset, wm_mask);

	/* save values क्रम DPM */
	amdgpu_crtc->line_समय = line_समय;
	amdgpu_crtc->wm_high = latency_watermark_a;
	amdgpu_crtc->wm_low = latency_watermark_b;
	/* Save number of lines the linebuffer leads beक्रमe the scanout */
	amdgpu_crtc->lb_vblank_lead_lines = lb_vblank_lead_lines;
पूर्ण

/**
 * dce_v8_0_bandwidth_update - program display watermarks
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Calculate and program the display watermarks and line
 * buffer allocation (CIK).
 */
अटल व्योम dce_v8_0_bandwidth_update(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा drm_display_mode *mode = शून्य;
	u32 num_heads = 0, lb_size;
	पूर्णांक i;

	amdgpu_display_update_priority(adev);

	क्रम (i = 0; i < adev->mode_info.num_crtc; i++) अणु
		अगर (adev->mode_info.crtcs[i]->base.enabled)
			num_heads++;
	पूर्ण
	क्रम (i = 0; i < adev->mode_info.num_crtc; i++) अणु
		mode = &adev->mode_info.crtcs[i]->base.mode;
		lb_size = dce_v8_0_line_buffer_adjust(adev, adev->mode_info.crtcs[i], mode);
		dce_v8_0_program_watermarks(adev, adev->mode_info.crtcs[i],
					    lb_size, num_heads);
	पूर्ण
पूर्ण

अटल व्योम dce_v8_0_audio_get_connected_pins(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;
	u32 offset, पंचांगp;

	क्रम (i = 0; i < adev->mode_info.audio.num_pins; i++) अणु
		offset = adev->mode_info.audio.pin[i].offset;
		पंचांगp = RREG32_AUDIO_ENDPT(offset,
					 ixAZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_CONFIGURATION_DEFAULT);
		अगर (((पंचांगp &
		AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_CONFIGURATION_DEFAULT__PORT_CONNECTIVITY_MASK) >>
		AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_CONFIGURATION_DEFAULT__PORT_CONNECTIVITY__SHIFT) == 1)
			adev->mode_info.audio.pin[i].connected = false;
		अन्यथा
			adev->mode_info.audio.pin[i].connected = true;
	पूर्ण
पूर्ण

अटल काष्ठा amdgpu_audio_pin *dce_v8_0_audio_get_pin(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	dce_v8_0_audio_get_connected_pins(adev);

	क्रम (i = 0; i < adev->mode_info.audio.num_pins; i++) अणु
		अगर (adev->mode_info.audio.pin[i].connected)
			वापस &adev->mode_info.audio.pin[i];
	पूर्ण
	DRM_ERROR("No connected audio pins found!\n");
	वापस शून्य;
पूर्ण

अटल व्योम dce_v8_0_afmt_audio_select_pin(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा amdgpu_device *adev = drm_to_adev(encoder->dev);
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	काष्ठा amdgpu_encoder_atom_dig *dig = amdgpu_encoder->enc_priv;
	u32 offset;

	अगर (!dig || !dig->afmt || !dig->afmt->pin)
		वापस;

	offset = dig->afmt->offset;

	WREG32(mmAFMT_AUDIO_SRC_CONTROL + offset,
	       (dig->afmt->pin->id << AFMT_AUDIO_SRC_CONTROL__AFMT_AUDIO_SRC_SELECT__SHIFT));
पूर्ण

अटल व्योम dce_v8_0_audio_ग_लिखो_latency_fields(काष्ठा drm_encoder *encoder,
						काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	काष्ठा amdgpu_encoder_atom_dig *dig = amdgpu_encoder->enc_priv;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter iter;
	काष्ठा amdgpu_connector *amdgpu_connector = शून्य;
	u32 पंचांगp = 0, offset;

	अगर (!dig || !dig->afmt || !dig->afmt->pin)
		वापस;

	offset = dig->afmt->pin->offset;

	drm_connector_list_iter_begin(dev, &iter);
	drm_क्रम_each_connector_iter(connector, &iter) अणु
		अगर (connector->encoder == encoder) अणु
			amdgpu_connector = to_amdgpu_connector(connector);
			अवरोध;
		पूर्ण
	पूर्ण
	drm_connector_list_iter_end(&iter);

	अगर (!amdgpu_connector) अणु
		DRM_ERROR("Couldn't find encoder's connector\n");
		वापस;
	पूर्ण

	अगर (mode->flags & DRM_MODE_FLAG_INTERLACE) अणु
		अगर (connector->latency_present[1])
			पंचांगp =
			(connector->video_latency[1] <<
			 AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_LIPSYNC__VIDEO_LIPSYNC__SHIFT) |
			(connector->audio_latency[1] <<
			 AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_LIPSYNC__AUDIO_LIPSYNC__SHIFT);
		अन्यथा
			पंचांगp =
			(0 <<
			 AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_LIPSYNC__VIDEO_LIPSYNC__SHIFT) |
			(0 <<
			 AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_LIPSYNC__AUDIO_LIPSYNC__SHIFT);
	पूर्ण अन्यथा अणु
		अगर (connector->latency_present[0])
			पंचांगp =
			(connector->video_latency[0] <<
			 AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_LIPSYNC__VIDEO_LIPSYNC__SHIFT) |
			(connector->audio_latency[0] <<
			 AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_LIPSYNC__AUDIO_LIPSYNC__SHIFT);
		अन्यथा
			पंचांगp =
			(0 <<
			 AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_LIPSYNC__VIDEO_LIPSYNC__SHIFT) |
			(0 <<
			 AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_LIPSYNC__AUDIO_LIPSYNC__SHIFT);

	पूर्ण
	WREG32_AUDIO_ENDPT(offset, ixAZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_LIPSYNC, पंचांगp);
पूर्ण

अटल व्योम dce_v8_0_audio_ग_लिखो_speaker_allocation(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	काष्ठा amdgpu_encoder_atom_dig *dig = amdgpu_encoder->enc_priv;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter iter;
	काष्ठा amdgpu_connector *amdgpu_connector = शून्य;
	u32 offset, पंचांगp;
	u8 *sadb = शून्य;
	पूर्णांक sad_count;

	अगर (!dig || !dig->afmt || !dig->afmt->pin)
		वापस;

	offset = dig->afmt->pin->offset;

	drm_connector_list_iter_begin(dev, &iter);
	drm_क्रम_each_connector_iter(connector, &iter) अणु
		अगर (connector->encoder == encoder) अणु
			amdgpu_connector = to_amdgpu_connector(connector);
			अवरोध;
		पूर्ण
	पूर्ण
	drm_connector_list_iter_end(&iter);

	अगर (!amdgpu_connector) अणु
		DRM_ERROR("Couldn't find encoder's connector\n");
		वापस;
	पूर्ण

	sad_count = drm_edid_to_speaker_allocation(amdgpu_connector_edid(connector), &sadb);
	अगर (sad_count < 0) अणु
		DRM_ERROR("Couldn't read Speaker Allocation Data Block: %d\n", sad_count);
		sad_count = 0;
	पूर्ण

	/* program the speaker allocation */
	पंचांगp = RREG32_AUDIO_ENDPT(offset, ixAZALIA_F0_CODEC_PIN_CONTROL_CHANNEL_SPEAKER);
	पंचांगp &= ~(AZALIA_F0_CODEC_PIN_CONTROL_CHANNEL_SPEAKER__DP_CONNECTION_MASK |
		AZALIA_F0_CODEC_PIN_CONTROL_CHANNEL_SPEAKER__SPEAKER_ALLOCATION_MASK);
	/* set HDMI mode */
	पंचांगp |= AZALIA_F0_CODEC_PIN_CONTROL_CHANNEL_SPEAKER__HDMI_CONNECTION_MASK;
	अगर (sad_count)
		पंचांगp |= (sadb[0] << AZALIA_F0_CODEC_PIN_CONTROL_CHANNEL_SPEAKER__SPEAKER_ALLOCATION__SHIFT);
	अन्यथा
		पंचांगp |= (5 << AZALIA_F0_CODEC_PIN_CONTROL_CHANNEL_SPEAKER__SPEAKER_ALLOCATION__SHIFT); /* stereo */
	WREG32_AUDIO_ENDPT(offset, ixAZALIA_F0_CODEC_PIN_CONTROL_CHANNEL_SPEAKER, पंचांगp);

	kमुक्त(sadb);
पूर्ण

अटल व्योम dce_v8_0_audio_ग_लिखो_sad_regs(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	काष्ठा amdgpu_encoder_atom_dig *dig = amdgpu_encoder->enc_priv;
	u32 offset;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter iter;
	काष्ठा amdgpu_connector *amdgpu_connector = शून्य;
	काष्ठा cea_sad *sads;
	पूर्णांक i, sad_count;

	अटल स्थिर u16 eld_reg_to_type[][2] = अणु
		अणु ixAZALIA_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR0, HDMI_AUDIO_CODING_TYPE_PCM पूर्ण,
		अणु ixAZALIA_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR1, HDMI_AUDIO_CODING_TYPE_AC3 पूर्ण,
		अणु ixAZALIA_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR2, HDMI_AUDIO_CODING_TYPE_MPEG1 पूर्ण,
		अणु ixAZALIA_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR3, HDMI_AUDIO_CODING_TYPE_MP3 पूर्ण,
		अणु ixAZALIA_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR4, HDMI_AUDIO_CODING_TYPE_MPEG2 पूर्ण,
		अणु ixAZALIA_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR5, HDMI_AUDIO_CODING_TYPE_AAC_LC पूर्ण,
		अणु ixAZALIA_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR6, HDMI_AUDIO_CODING_TYPE_DTS पूर्ण,
		अणु ixAZALIA_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR7, HDMI_AUDIO_CODING_TYPE_ATRAC पूर्ण,
		अणु ixAZALIA_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR9, HDMI_AUDIO_CODING_TYPE_EAC3 पूर्ण,
		अणु ixAZALIA_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR10, HDMI_AUDIO_CODING_TYPE_DTS_HD पूर्ण,
		अणु ixAZALIA_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR11, HDMI_AUDIO_CODING_TYPE_MLP पूर्ण,
		अणु ixAZALIA_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR13, HDMI_AUDIO_CODING_TYPE_WMA_PRO पूर्ण,
	पूर्ण;

	अगर (!dig || !dig->afmt || !dig->afmt->pin)
		वापस;

	offset = dig->afmt->pin->offset;

	drm_connector_list_iter_begin(dev, &iter);
	drm_क्रम_each_connector_iter(connector, &iter) अणु
		अगर (connector->encoder == encoder) अणु
			amdgpu_connector = to_amdgpu_connector(connector);
			अवरोध;
		पूर्ण
	पूर्ण
	drm_connector_list_iter_end(&iter);

	अगर (!amdgpu_connector) अणु
		DRM_ERROR("Couldn't find encoder's connector\n");
		वापस;
	पूर्ण

	sad_count = drm_edid_to_sad(amdgpu_connector_edid(connector), &sads);
	अगर (sad_count < 0)
		DRM_ERROR("Couldn't read SADs: %d\n", sad_count);
	अगर (sad_count <= 0)
		वापस;
	BUG_ON(!sads);

	क्रम (i = 0; i < ARRAY_SIZE(eld_reg_to_type); i++) अणु
		u32 value = 0;
		u8 stereo_freqs = 0;
		पूर्णांक max_channels = -1;
		पूर्णांक j;

		क्रम (j = 0; j < sad_count; j++) अणु
			काष्ठा cea_sad *sad = &sads[j];

			अगर (sad->क्रमmat == eld_reg_to_type[i][1]) अणु
				अगर (sad->channels > max_channels) अणु
					value = (sad->channels <<
						 AZALIA_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR0__MAX_CHANNELS__SHIFT) |
					        (sad->byte2 <<
						 AZALIA_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR0__DESCRIPTOR_BYTE_2__SHIFT) |
					        (sad->freq <<
						 AZALIA_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR0__SUPPORTED_FREQUENCIES__SHIFT);
					max_channels = sad->channels;
				पूर्ण

				अगर (sad->क्रमmat == HDMI_AUDIO_CODING_TYPE_PCM)
					stereo_freqs |= sad->freq;
				अन्यथा
					अवरोध;
			पूर्ण
		पूर्ण

		value |= (stereo_freqs <<
			AZALIA_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR0__SUPPORTED_FREQUENCIES_STEREO__SHIFT);

		WREG32_AUDIO_ENDPT(offset, eld_reg_to_type[i][0], value);
	पूर्ण

	kमुक्त(sads);
पूर्ण

अटल व्योम dce_v8_0_audio_enable(काष्ठा amdgpu_device *adev,
				  काष्ठा amdgpu_audio_pin *pin,
				  bool enable)
अणु
	अगर (!pin)
		वापस;

	WREG32_AUDIO_ENDPT(pin->offset, ixAZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL,
		enable ? AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL__AUDIO_ENABLED_MASK : 0);
पूर्ण

अटल स्थिर u32 pin_offsets[7] =
अणु
	(0x1780 - 0x1780),
	(0x1786 - 0x1780),
	(0x178c - 0x1780),
	(0x1792 - 0x1780),
	(0x1798 - 0x1780),
	(0x179d - 0x1780),
	(0x17a4 - 0x1780),
पूर्ण;

अटल पूर्णांक dce_v8_0_audio_init(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	अगर (!amdgpu_audio)
		वापस 0;

	adev->mode_info.audio.enabled = true;

	अगर (adev->asic_type == CHIP_KAVERI) /* KV: 4 streams, 7 endpoपूर्णांकs */
		adev->mode_info.audio.num_pins = 7;
	अन्यथा अगर ((adev->asic_type == CHIP_KABINI) ||
		 (adev->asic_type == CHIP_MULLINS)) /* KB/ML: 2 streams, 3 endpoपूर्णांकs */
		adev->mode_info.audio.num_pins = 3;
	अन्यथा अगर ((adev->asic_type == CHIP_BONAIRE) ||
		 (adev->asic_type == CHIP_HAWAII))/* BN/HW: 6 streams, 7 endpoपूर्णांकs */
		adev->mode_info.audio.num_pins = 7;
	अन्यथा
		adev->mode_info.audio.num_pins = 3;

	क्रम (i = 0; i < adev->mode_info.audio.num_pins; i++) अणु
		adev->mode_info.audio.pin[i].channels = -1;
		adev->mode_info.audio.pin[i].rate = -1;
		adev->mode_info.audio.pin[i].bits_per_sample = -1;
		adev->mode_info.audio.pin[i].status_bits = 0;
		adev->mode_info.audio.pin[i].category_code = 0;
		adev->mode_info.audio.pin[i].connected = false;
		adev->mode_info.audio.pin[i].offset = pin_offsets[i];
		adev->mode_info.audio.pin[i].id = i;
		/* disable audio.  it will be set up later */
		/* XXX हटाओ once we चयन to ip funcs */
		dce_v8_0_audio_enable(adev, &adev->mode_info.audio.pin[i], false);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dce_v8_0_audio_fini(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	अगर (!amdgpu_audio)
		वापस;

	अगर (!adev->mode_info.audio.enabled)
		वापस;

	क्रम (i = 0; i < adev->mode_info.audio.num_pins; i++)
		dce_v8_0_audio_enable(adev, &adev->mode_info.audio.pin[i], false);

	adev->mode_info.audio.enabled = false;
पूर्ण

/*
 * update the N and CTS parameters क्रम a given pixel घड़ी rate
 */
अटल व्योम dce_v8_0_afmt_update_ACR(काष्ठा drm_encoder *encoder, uपूर्णांक32_t घड़ी)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_afmt_acr acr = amdgpu_afmt_acr(घड़ी);
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	काष्ठा amdgpu_encoder_atom_dig *dig = amdgpu_encoder->enc_priv;
	uपूर्णांक32_t offset = dig->afmt->offset;

	WREG32(mmHDMI_ACR_32_0 + offset, (acr.cts_32khz << HDMI_ACR_32_0__HDMI_ACR_CTS_32__SHIFT));
	WREG32(mmHDMI_ACR_32_1 + offset, acr.n_32khz);

	WREG32(mmHDMI_ACR_44_0 + offset, (acr.cts_44_1khz << HDMI_ACR_44_0__HDMI_ACR_CTS_44__SHIFT));
	WREG32(mmHDMI_ACR_44_1 + offset, acr.n_44_1khz);

	WREG32(mmHDMI_ACR_48_0 + offset, (acr.cts_48khz << HDMI_ACR_48_0__HDMI_ACR_CTS_48__SHIFT));
	WREG32(mmHDMI_ACR_48_1 + offset, acr.n_48khz);
पूर्ण

/*
 * build a HDMI Video Info Frame
 */
अटल व्योम dce_v8_0_afmt_update_avi_infoframe(काष्ठा drm_encoder *encoder,
					       व्योम *buffer, माप_प्रकार size)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	काष्ठा amdgpu_encoder_atom_dig *dig = amdgpu_encoder->enc_priv;
	uपूर्णांक32_t offset = dig->afmt->offset;
	uपूर्णांक8_t *frame = buffer + 3;
	uपूर्णांक8_t *header = buffer;

	WREG32(mmAFMT_AVI_INFO0 + offset,
		frame[0x0] | (frame[0x1] << 8) | (frame[0x2] << 16) | (frame[0x3] << 24));
	WREG32(mmAFMT_AVI_INFO1 + offset,
		frame[0x4] | (frame[0x5] << 8) | (frame[0x6] << 16) | (frame[0x7] << 24));
	WREG32(mmAFMT_AVI_INFO2 + offset,
		frame[0x8] | (frame[0x9] << 8) | (frame[0xA] << 16) | (frame[0xB] << 24));
	WREG32(mmAFMT_AVI_INFO3 + offset,
		frame[0xC] | (frame[0xD] << 8) | (header[1] << 24));
पूर्ण

अटल व्योम dce_v8_0_audio_set_dto(काष्ठा drm_encoder *encoder, u32 घड़ी)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	काष्ठा amdgpu_encoder_atom_dig *dig = amdgpu_encoder->enc_priv;
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(encoder->crtc);
	u32 dto_phase = 24 * 1000;
	u32 dto_modulo = घड़ी;

	अगर (!dig || !dig->afmt)
		वापस;

	/* XXX two dtos; generally use dto0 क्रम hdmi */
	/* Express [24MHz / target pixel घड़ी] as an exact rational
	 * number (coefficient of two पूर्णांकeger numbers.  DCCG_AUDIO_DTOx_PHASE
	 * is the numerator, DCCG_AUDIO_DTOx_MODULE is the denominator
	 */
	WREG32(mmDCCG_AUDIO_DTO_SOURCE, (amdgpu_crtc->crtc_id << DCCG_AUDIO_DTO_SOURCE__DCCG_AUDIO_DTO0_SOURCE_SEL__SHIFT));
	WREG32(mmDCCG_AUDIO_DTO0_PHASE, dto_phase);
	WREG32(mmDCCG_AUDIO_DTO0_MODULE, dto_modulo);
पूर्ण

/*
 * update the info frames with the data from the current display mode
 */
अटल व्योम dce_v8_0_afmt_seपंचांगode(काष्ठा drm_encoder *encoder,
				  काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	काष्ठा amdgpu_encoder_atom_dig *dig = amdgpu_encoder->enc_priv;
	काष्ठा drm_connector *connector = amdgpu_get_connector_क्रम_encoder(encoder);
	u8 buffer[HDMI_INFOFRAME_HEADER_SIZE + HDMI_AVI_INFOFRAME_SIZE];
	काष्ठा hdmi_avi_infoframe frame;
	uपूर्णांक32_t offset, val;
	sमाप_प्रकार err;
	पूर्णांक bpc = 8;

	अगर (!dig || !dig->afmt)
		वापस;

	/* Silent, r600_hdmi_enable will उठाओ WARN क्रम us */
	अगर (!dig->afmt->enabled)
		वापस;

	offset = dig->afmt->offset;

	/* hdmi deep color mode general control packets setup, अगर bpc > 8 */
	अगर (encoder->crtc) अणु
		काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(encoder->crtc);
		bpc = amdgpu_crtc->bpc;
	पूर्ण

	/* disable audio prior to setting up hw */
	dig->afmt->pin = dce_v8_0_audio_get_pin(adev);
	dce_v8_0_audio_enable(adev, dig->afmt->pin, false);

	dce_v8_0_audio_set_dto(encoder, mode->घड़ी);

	WREG32(mmHDMI_VBI_PACKET_CONTROL + offset,
	       HDMI_VBI_PACKET_CONTROL__HDMI_शून्य_SEND_MASK); /* send null packets when required */

	WREG32(mmAFMT_AUDIO_CRC_CONTROL + offset, 0x1000);

	val = RREG32(mmHDMI_CONTROL + offset);
	val &= ~HDMI_CONTROL__HDMI_DEEP_COLOR_ENABLE_MASK;
	val &= ~HDMI_CONTROL__HDMI_DEEP_COLOR_DEPTH_MASK;

	चयन (bpc) अणु
	हाल 0:
	हाल 6:
	हाल 8:
	हाल 16:
	शेष:
		DRM_DEBUG("%s: Disabling hdmi deep color for %d bpc.\n",
			  connector->name, bpc);
		अवरोध;
	हाल 10:
		val |= HDMI_CONTROL__HDMI_DEEP_COLOR_ENABLE_MASK;
		val |= 1 << HDMI_CONTROL__HDMI_DEEP_COLOR_DEPTH__SHIFT;
		DRM_DEBUG("%s: Enabling hdmi deep color 30 for 10 bpc.\n",
			  connector->name);
		अवरोध;
	हाल 12:
		val |= HDMI_CONTROL__HDMI_DEEP_COLOR_ENABLE_MASK;
		val |= 2 << HDMI_CONTROL__HDMI_DEEP_COLOR_DEPTH__SHIFT;
		DRM_DEBUG("%s: Enabling hdmi deep color 36 for 12 bpc.\n",
			  connector->name);
		अवरोध;
	पूर्ण

	WREG32(mmHDMI_CONTROL + offset, val);

	WREG32(mmHDMI_VBI_PACKET_CONTROL + offset,
	       HDMI_VBI_PACKET_CONTROL__HDMI_शून्य_SEND_MASK | /* send null packets when required */
	       HDMI_VBI_PACKET_CONTROL__HDMI_GC_SEND_MASK | /* send general control packets */
	       HDMI_VBI_PACKET_CONTROL__HDMI_GC_CONT_MASK); /* send general control packets every frame */

	WREG32(mmHDMI_INFOFRAME_CONTROL0 + offset,
	       HDMI_INFOFRAME_CONTROL0__HDMI_AUDIO_INFO_SEND_MASK | /* enable audio info frames (frames won't be set until audio is enabled) */
	       HDMI_INFOFRAME_CONTROL0__HDMI_AUDIO_INFO_CONT_MASK); /* required क्रम audio info values to be updated */

	WREG32(mmAFMT_INFOFRAME_CONTROL0 + offset,
	       AFMT_INFOFRAME_CONTROL0__AFMT_AUDIO_INFO_UPDATE_MASK); /* required क्रम audio info values to be updated */

	WREG32(mmHDMI_INFOFRAME_CONTROL1 + offset,
	       (2 << HDMI_INFOFRAME_CONTROL1__HDMI_AUDIO_INFO_LINE__SHIFT)); /* anything other than 0 */

	WREG32(mmHDMI_GC + offset, 0); /* unset HDMI_GC_AVMUTE */

	WREG32(mmHDMI_AUDIO_PACKET_CONTROL + offset,
	       (1 << HDMI_AUDIO_PACKET_CONTROL__HDMI_AUDIO_DELAY_EN__SHIFT) | /* set the शेष audio delay */
	       (3 << HDMI_AUDIO_PACKET_CONTROL__HDMI_AUDIO_PACKETS_PER_LINE__SHIFT)); /* should be suffient क्रम all audio modes and small enough क्रम all hblanks */

	WREG32(mmAFMT_AUDIO_PACKET_CONTROL + offset,
	       AFMT_AUDIO_PACKET_CONTROL__AFMT_60958_CS_UPDATE_MASK); /* allow 60958 channel status fields to be updated */

	/* fglrx clears sth in AFMT_AUDIO_PACKET_CONTROL2 here */

	अगर (bpc > 8)
		WREG32(mmHDMI_ACR_PACKET_CONTROL + offset,
		       HDMI_ACR_PACKET_CONTROL__HDMI_ACR_AUTO_SEND_MASK); /* allow hw to sent ACR packets when required */
	अन्यथा
		WREG32(mmHDMI_ACR_PACKET_CONTROL + offset,
		       HDMI_ACR_PACKET_CONTROL__HDMI_ACR_SOURCE_MASK | /* select SW CTS value */
		       HDMI_ACR_PACKET_CONTROL__HDMI_ACR_AUTO_SEND_MASK); /* allow hw to sent ACR packets when required */

	dce_v8_0_afmt_update_ACR(encoder, mode->घड़ी);

	WREG32(mmAFMT_60958_0 + offset,
	       (1 << AFMT_60958_0__AFMT_60958_CS_CHANNEL_NUMBER_L__SHIFT));

	WREG32(mmAFMT_60958_1 + offset,
	       (2 << AFMT_60958_1__AFMT_60958_CS_CHANNEL_NUMBER_R__SHIFT));

	WREG32(mmAFMT_60958_2 + offset,
	       (3 << AFMT_60958_2__AFMT_60958_CS_CHANNEL_NUMBER_2__SHIFT) |
	       (4 << AFMT_60958_2__AFMT_60958_CS_CHANNEL_NUMBER_3__SHIFT) |
	       (5 << AFMT_60958_2__AFMT_60958_CS_CHANNEL_NUMBER_4__SHIFT) |
	       (6 << AFMT_60958_2__AFMT_60958_CS_CHANNEL_NUMBER_5__SHIFT) |
	       (7 << AFMT_60958_2__AFMT_60958_CS_CHANNEL_NUMBER_6__SHIFT) |
	       (8 << AFMT_60958_2__AFMT_60958_CS_CHANNEL_NUMBER_7__SHIFT));

	dce_v8_0_audio_ग_लिखो_speaker_allocation(encoder);


	WREG32(mmAFMT_AUDIO_PACKET_CONTROL2 + offset,
	       (0xff << AFMT_AUDIO_PACKET_CONTROL2__AFMT_AUDIO_CHANNEL_ENABLE__SHIFT));

	dce_v8_0_afmt_audio_select_pin(encoder);
	dce_v8_0_audio_ग_लिखो_sad_regs(encoder);
	dce_v8_0_audio_ग_लिखो_latency_fields(encoder, mode);

	err = drm_hdmi_avi_infoframe_from_display_mode(&frame, connector, mode);
	अगर (err < 0) अणु
		DRM_ERROR("failed to setup AVI infoframe: %zd\n", err);
		वापस;
	पूर्ण

	err = hdmi_avi_infoframe_pack(&frame, buffer, माप(buffer));
	अगर (err < 0) अणु
		DRM_ERROR("failed to pack AVI infoframe: %zd\n", err);
		वापस;
	पूर्ण

	dce_v8_0_afmt_update_avi_infoframe(encoder, buffer, माप(buffer));

	WREG32_OR(mmHDMI_INFOFRAME_CONTROL0 + offset,
		  HDMI_INFOFRAME_CONTROL0__HDMI_AVI_INFO_SEND_MASK | /* enable AVI info frames */
		  HDMI_INFOFRAME_CONTROL0__HDMI_AVI_INFO_CONT_MASK); /* required क्रम audio info values to be updated */

	WREG32_P(mmHDMI_INFOFRAME_CONTROL1 + offset,
		 (2 << HDMI_INFOFRAME_CONTROL1__HDMI_AVI_INFO_LINE__SHIFT), /* anything other than 0 */
		 ~HDMI_INFOFRAME_CONTROL1__HDMI_AVI_INFO_LINE_MASK);

	WREG32_OR(mmAFMT_AUDIO_PACKET_CONTROL + offset,
		  AFMT_AUDIO_PACKET_CONTROL__AFMT_AUDIO_SAMPLE_SEND_MASK); /* send audio packets */

	WREG32(mmAFMT_RAMP_CONTROL0 + offset, 0x00FFFFFF);
	WREG32(mmAFMT_RAMP_CONTROL1 + offset, 0x007FFFFF);
	WREG32(mmAFMT_RAMP_CONTROL2 + offset, 0x00000001);
	WREG32(mmAFMT_RAMP_CONTROL3 + offset, 0x00000001);

	/* enable audio after setting up hw */
	dce_v8_0_audio_enable(adev, dig->afmt->pin, true);
पूर्ण

अटल व्योम dce_v8_0_afmt_enable(काष्ठा drm_encoder *encoder, bool enable)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	काष्ठा amdgpu_encoder_atom_dig *dig = amdgpu_encoder->enc_priv;

	अगर (!dig || !dig->afmt)
		वापस;

	/* Silent, r600_hdmi_enable will उठाओ WARN क्रम us */
	अगर (enable && dig->afmt->enabled)
		वापस;
	अगर (!enable && !dig->afmt->enabled)
		वापस;

	अगर (!enable && dig->afmt->pin) अणु
		dce_v8_0_audio_enable(adev, dig->afmt->pin, false);
		dig->afmt->pin = शून्य;
	पूर्ण

	dig->afmt->enabled = enable;

	DRM_DEBUG("%sabling AFMT interface @ 0x%04X for encoder 0x%x\n",
		  enable ? "En" : "Dis", dig->afmt->offset, amdgpu_encoder->encoder_id);
पूर्ण

अटल पूर्णांक dce_v8_0_afmt_init(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adev->mode_info.num_dig; i++)
		adev->mode_info.afmt[i] = शून्य;

	/* DCE8 has audio blocks tied to DIG encoders */
	क्रम (i = 0; i < adev->mode_info.num_dig; i++) अणु
		adev->mode_info.afmt[i] = kzalloc(माप(काष्ठा amdgpu_afmt), GFP_KERNEL);
		अगर (adev->mode_info.afmt[i]) अणु
			adev->mode_info.afmt[i]->offset = dig_offsets[i];
			adev->mode_info.afmt[i]->id = i;
		पूर्ण अन्यथा अणु
			पूर्णांक j;
			क्रम (j = 0; j < i; j++) अणु
				kमुक्त(adev->mode_info.afmt[j]);
				adev->mode_info.afmt[j] = शून्य;
			पूर्ण
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम dce_v8_0_afmt_fini(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adev->mode_info.num_dig; i++) अणु
		kमुक्त(adev->mode_info.afmt[i]);
		adev->mode_info.afmt[i] = शून्य;
	पूर्ण
पूर्ण

अटल स्थिर u32 vga_control_regs[6] =
अणु
	mmD1VGA_CONTROL,
	mmD2VGA_CONTROL,
	mmD3VGA_CONTROL,
	mmD4VGA_CONTROL,
	mmD5VGA_CONTROL,
	mmD6VGA_CONTROL,
पूर्ण;

अटल व्योम dce_v8_0_vga_enable(काष्ठा drm_crtc *crtc, bool enable)
अणु
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	u32 vga_control;

	vga_control = RREG32(vga_control_regs[amdgpu_crtc->crtc_id]) & ~1;
	अगर (enable)
		WREG32(vga_control_regs[amdgpu_crtc->crtc_id], vga_control | 1);
	अन्यथा
		WREG32(vga_control_regs[amdgpu_crtc->crtc_id], vga_control);
पूर्ण

अटल व्योम dce_v8_0_grph_enable(काष्ठा drm_crtc *crtc, bool enable)
अणु
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);

	अगर (enable)
		WREG32(mmGRPH_ENABLE + amdgpu_crtc->crtc_offset, 1);
	अन्यथा
		WREG32(mmGRPH_ENABLE + amdgpu_crtc->crtc_offset, 0);
पूर्ण

अटल पूर्णांक dce_v8_0_crtc_करो_set_base(काष्ठा drm_crtc *crtc,
				     काष्ठा drm_framebuffer *fb,
				     पूर्णांक x, पूर्णांक y, पूर्णांक atomic)
अणु
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा drm_framebuffer *target_fb;
	काष्ठा drm_gem_object *obj;
	काष्ठा amdgpu_bo *abo;
	uपूर्णांक64_t fb_location, tiling_flags;
	uपूर्णांक32_t fb_क्रमmat, fb_pitch_pixels;
	u32 fb_swap = (GRPH_ENDIAN_NONE << GRPH_SWAP_CNTL__GRPH_ENDIAN_SWAP__SHIFT);
	u32 pipe_config;
	u32 viewport_w, viewport_h;
	पूर्णांक r;
	bool bypass_lut = false;

	/* no fb bound */
	अगर (!atomic && !crtc->primary->fb) अणु
		DRM_DEBUG_KMS("No FB bound\n");
		वापस 0;
	पूर्ण

	अगर (atomic)
		target_fb = fb;
	अन्यथा
		target_fb = crtc->primary->fb;

	/* If atomic, assume fb object is pinned & idle & fenced and
	 * just update base poपूर्णांकers
	 */
	obj = target_fb->obj[0];
	abo = gem_to_amdgpu_bo(obj);
	r = amdgpu_bo_reserve(abo, false);
	अगर (unlikely(r != 0))
		वापस r;

	अगर (!atomic) अणु
		r = amdgpu_bo_pin(abo, AMDGPU_GEM_DOMAIN_VRAM);
		अगर (unlikely(r != 0)) अणु
			amdgpu_bo_unreserve(abo);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	fb_location = amdgpu_bo_gpu_offset(abo);

	amdgpu_bo_get_tiling_flags(abo, &tiling_flags);
	amdgpu_bo_unreserve(abo);

	pipe_config = AMDGPU_TILING_GET(tiling_flags, PIPE_CONFIG);

	चयन (target_fb->क्रमmat->क्रमmat) अणु
	हाल DRM_FORMAT_C8:
		fb_क्रमmat = ((GRPH_DEPTH_8BPP << GRPH_CONTROL__GRPH_DEPTH__SHIFT) |
			     (GRPH_FORMAT_INDEXED << GRPH_CONTROL__GRPH_FORMAT__SHIFT));
		अवरोध;
	हाल DRM_FORMAT_XRGB4444:
	हाल DRM_FORMAT_ARGB4444:
		fb_क्रमmat = ((GRPH_DEPTH_16BPP << GRPH_CONTROL__GRPH_DEPTH__SHIFT) |
			     (GRPH_FORMAT_ARGB4444 << GRPH_CONTROL__GRPH_FORMAT__SHIFT));
#अगर_घोषित __BIG_ENDIAN
		fb_swap = (GRPH_ENDIAN_8IN16 << GRPH_SWAP_CNTL__GRPH_ENDIAN_SWAP__SHIFT);
#पूर्ण_अगर
		अवरोध;
	हाल DRM_FORMAT_XRGB1555:
	हाल DRM_FORMAT_ARGB1555:
		fb_क्रमmat = ((GRPH_DEPTH_16BPP << GRPH_CONTROL__GRPH_DEPTH__SHIFT) |
			     (GRPH_FORMAT_ARGB1555 << GRPH_CONTROL__GRPH_FORMAT__SHIFT));
#अगर_घोषित __BIG_ENDIAN
		fb_swap = (GRPH_ENDIAN_8IN16 << GRPH_SWAP_CNTL__GRPH_ENDIAN_SWAP__SHIFT);
#पूर्ण_अगर
		अवरोध;
	हाल DRM_FORMAT_BGRX5551:
	हाल DRM_FORMAT_BGRA5551:
		fb_क्रमmat = ((GRPH_DEPTH_16BPP << GRPH_CONTROL__GRPH_DEPTH__SHIFT) |
			     (GRPH_FORMAT_BGRA5551 << GRPH_CONTROL__GRPH_FORMAT__SHIFT));
#अगर_घोषित __BIG_ENDIAN
		fb_swap = (GRPH_ENDIAN_8IN16 << GRPH_SWAP_CNTL__GRPH_ENDIAN_SWAP__SHIFT);
#पूर्ण_अगर
		अवरोध;
	हाल DRM_FORMAT_RGB565:
		fb_क्रमmat = ((GRPH_DEPTH_16BPP << GRPH_CONTROL__GRPH_DEPTH__SHIFT) |
			     (GRPH_FORMAT_ARGB565 << GRPH_CONTROL__GRPH_FORMAT__SHIFT));
#अगर_घोषित __BIG_ENDIAN
		fb_swap = (GRPH_ENDIAN_8IN16 << GRPH_SWAP_CNTL__GRPH_ENDIAN_SWAP__SHIFT);
#पूर्ण_अगर
		अवरोध;
	हाल DRM_FORMAT_XRGB8888:
	हाल DRM_FORMAT_ARGB8888:
		fb_क्रमmat = ((GRPH_DEPTH_32BPP << GRPH_CONTROL__GRPH_DEPTH__SHIFT) |
			     (GRPH_FORMAT_ARGB8888 << GRPH_CONTROL__GRPH_FORMAT__SHIFT));
#अगर_घोषित __BIG_ENDIAN
		fb_swap = (GRPH_ENDIAN_8IN32 << GRPH_SWAP_CNTL__GRPH_ENDIAN_SWAP__SHIFT);
#पूर्ण_अगर
		अवरोध;
	हाल DRM_FORMAT_XRGB2101010:
	हाल DRM_FORMAT_ARGB2101010:
		fb_क्रमmat = ((GRPH_DEPTH_32BPP << GRPH_CONTROL__GRPH_DEPTH__SHIFT) |
			     (GRPH_FORMAT_ARGB2101010 << GRPH_CONTROL__GRPH_FORMAT__SHIFT));
#अगर_घोषित __BIG_ENDIAN
		fb_swap = (GRPH_ENDIAN_8IN32 << GRPH_SWAP_CNTL__GRPH_ENDIAN_SWAP__SHIFT);
#पूर्ण_अगर
		/* Greater 8 bpc fb needs to bypass hw-lut to retain precision */
		bypass_lut = true;
		अवरोध;
	हाल DRM_FORMAT_BGRX1010102:
	हाल DRM_FORMAT_BGRA1010102:
		fb_क्रमmat = ((GRPH_DEPTH_32BPP << GRPH_CONTROL__GRPH_DEPTH__SHIFT) |
			     (GRPH_FORMAT_BGRA1010102 << GRPH_CONTROL__GRPH_FORMAT__SHIFT));
#अगर_घोषित __BIG_ENDIAN
		fb_swap = (GRPH_ENDIAN_8IN32 << GRPH_SWAP_CNTL__GRPH_ENDIAN_SWAP__SHIFT);
#पूर्ण_अगर
		/* Greater 8 bpc fb needs to bypass hw-lut to retain precision */
		bypass_lut = true;
		अवरोध;
	हाल DRM_FORMAT_XBGR8888:
	हाल DRM_FORMAT_ABGR8888:
		fb_क्रमmat = ((GRPH_DEPTH_32BPP << GRPH_CONTROL__GRPH_DEPTH__SHIFT) |
		             (GRPH_FORMAT_ARGB8888 << GRPH_CONTROL__GRPH_FORMAT__SHIFT));
		fb_swap = ((GRPH_RED_SEL_B << GRPH_SWAP_CNTL__GRPH_RED_CROSSBAR__SHIFT) |
		           (GRPH_BLUE_SEL_R << GRPH_SWAP_CNTL__GRPH_BLUE_CROSSBAR__SHIFT));
#अगर_घोषित __BIG_ENDIAN
		fb_swap |= (GRPH_ENDIAN_8IN32 << GRPH_SWAP_CNTL__GRPH_ENDIAN_SWAP__SHIFT);
#पूर्ण_अगर
		अवरोध;
	शेष:
		DRM_ERROR("Unsupported screen format %p4cc\n",
			  &target_fb->क्रमmat->क्रमmat);
		वापस -EINVAL;
	पूर्ण

	अगर (AMDGPU_TILING_GET(tiling_flags, ARRAY_MODE) == ARRAY_2D_TILED_THIN1) अणु
		अचिन्हित bankw, bankh, mtaspect, tile_split, num_banks;

		bankw = AMDGPU_TILING_GET(tiling_flags, BANK_WIDTH);
		bankh = AMDGPU_TILING_GET(tiling_flags, BANK_HEIGHT);
		mtaspect = AMDGPU_TILING_GET(tiling_flags, MACRO_TILE_ASPECT);
		tile_split = AMDGPU_TILING_GET(tiling_flags, TILE_SPLIT);
		num_banks = AMDGPU_TILING_GET(tiling_flags, NUM_BANKS);

		fb_क्रमmat |= (num_banks << GRPH_CONTROL__GRPH_NUM_BANKS__SHIFT);
		fb_क्रमmat |= (GRPH_ARRAY_2D_TILED_THIN1 << GRPH_CONTROL__GRPH_ARRAY_MODE__SHIFT);
		fb_क्रमmat |= (tile_split << GRPH_CONTROL__GRPH_TILE_SPLIT__SHIFT);
		fb_क्रमmat |= (bankw << GRPH_CONTROL__GRPH_BANK_WIDTH__SHIFT);
		fb_क्रमmat |= (bankh << GRPH_CONTROL__GRPH_BANK_HEIGHT__SHIFT);
		fb_क्रमmat |= (mtaspect << GRPH_CONTROL__GRPH_MACRO_TILE_ASPECT__SHIFT);
		fb_क्रमmat |= (DISPLAY_MICRO_TILING << GRPH_CONTROL__GRPH_MICRO_TILE_MODE__SHIFT);
	पूर्ण अन्यथा अगर (AMDGPU_TILING_GET(tiling_flags, ARRAY_MODE) == ARRAY_1D_TILED_THIN1) अणु
		fb_क्रमmat |= (GRPH_ARRAY_1D_TILED_THIN1 << GRPH_CONTROL__GRPH_ARRAY_MODE__SHIFT);
	पूर्ण

	fb_क्रमmat |= (pipe_config << GRPH_CONTROL__GRPH_PIPE_CONFIG__SHIFT);

	dce_v8_0_vga_enable(crtc, false);

	/* Make sure surface address is updated at vertical blank rather than
	 * horizontal blank
	 */
	WREG32(mmGRPH_FLIP_CONTROL + amdgpu_crtc->crtc_offset, 0);

	WREG32(mmGRPH_PRIMARY_SURFACE_ADDRESS_HIGH + amdgpu_crtc->crtc_offset,
	       upper_32_bits(fb_location));
	WREG32(mmGRPH_SECONDARY_SURFACE_ADDRESS_HIGH + amdgpu_crtc->crtc_offset,
	       upper_32_bits(fb_location));
	WREG32(mmGRPH_PRIMARY_SURFACE_ADDRESS + amdgpu_crtc->crtc_offset,
	       (u32)fb_location & GRPH_PRIMARY_SURFACE_ADDRESS__GRPH_PRIMARY_SURFACE_ADDRESS_MASK);
	WREG32(mmGRPH_SECONDARY_SURFACE_ADDRESS + amdgpu_crtc->crtc_offset,
	       (u32) fb_location & GRPH_SECONDARY_SURFACE_ADDRESS__GRPH_SECONDARY_SURFACE_ADDRESS_MASK);
	WREG32(mmGRPH_CONTROL + amdgpu_crtc->crtc_offset, fb_क्रमmat);
	WREG32(mmGRPH_SWAP_CNTL + amdgpu_crtc->crtc_offset, fb_swap);

	/*
	 * The LUT only has 256 slots क्रम indexing by a 8 bpc fb. Bypass the LUT
	 * क्रम > 8 bpc scanout to aव्योम truncation of fb indices to 8 msb's, to
	 * retain the full precision throughout the pipeline.
	 */
	WREG32_P(mmGRPH_LUT_10BIT_BYPASS_CONTROL + amdgpu_crtc->crtc_offset,
		 (bypass_lut ? LUT_10BIT_BYPASS_EN : 0),
		 ~LUT_10BIT_BYPASS_EN);

	अगर (bypass_lut)
		DRM_DEBUG_KMS("Bypassing hardware LUT due to 10 bit fb scanout.\n");

	WREG32(mmGRPH_SURFACE_OFFSET_X + amdgpu_crtc->crtc_offset, 0);
	WREG32(mmGRPH_SURFACE_OFFSET_Y + amdgpu_crtc->crtc_offset, 0);
	WREG32(mmGRPH_X_START + amdgpu_crtc->crtc_offset, 0);
	WREG32(mmGRPH_Y_START + amdgpu_crtc->crtc_offset, 0);
	WREG32(mmGRPH_X_END + amdgpu_crtc->crtc_offset, target_fb->width);
	WREG32(mmGRPH_Y_END + amdgpu_crtc->crtc_offset, target_fb->height);

	fb_pitch_pixels = target_fb->pitches[0] / target_fb->क्रमmat->cpp[0];
	WREG32(mmGRPH_PITCH + amdgpu_crtc->crtc_offset, fb_pitch_pixels);

	dce_v8_0_grph_enable(crtc, true);

	WREG32(mmLB_DESKTOP_HEIGHT + amdgpu_crtc->crtc_offset,
	       target_fb->height);

	x &= ~3;
	y &= ~1;
	WREG32(mmVIEWPORT_START + amdgpu_crtc->crtc_offset,
	       (x << 16) | y);
	viewport_w = crtc->mode.hdisplay;
	viewport_h = (crtc->mode.vdisplay + 1) & ~1;
	WREG32(mmVIEWPORT_SIZE + amdgpu_crtc->crtc_offset,
	       (viewport_w << 16) | viewport_h);

	/* set pageflip to happen anywhere in vblank पूर्णांकerval */
	WREG32(mmMASTER_UPDATE_MODE + amdgpu_crtc->crtc_offset, 0);

	अगर (!atomic && fb && fb != crtc->primary->fb) अणु
		abo = gem_to_amdgpu_bo(fb->obj[0]);
		r = amdgpu_bo_reserve(abo, true);
		अगर (unlikely(r != 0))
			वापस r;
		amdgpu_bo_unpin(abo);
		amdgpu_bo_unreserve(abo);
	पूर्ण

	/* Bytes per pixel may have changed */
	dce_v8_0_bandwidth_update(adev);

	वापस 0;
पूर्ण

अटल व्योम dce_v8_0_set_पूर्णांकerleave(काष्ठा drm_crtc *crtc,
				    काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);

	अगर (mode->flags & DRM_MODE_FLAG_INTERLACE)
		WREG32(mmLB_DATA_FORMAT + amdgpu_crtc->crtc_offset,
		       LB_DATA_FORMAT__INTERLEAVE_EN__SHIFT);
	अन्यथा
		WREG32(mmLB_DATA_FORMAT + amdgpu_crtc->crtc_offset, 0);
पूर्ण

अटल व्योम dce_v8_0_crtc_load_lut(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	u16 *r, *g, *b;
	पूर्णांक i;

	DRM_DEBUG_KMS("%d\n", amdgpu_crtc->crtc_id);

	WREG32(mmINPUT_CSC_CONTROL + amdgpu_crtc->crtc_offset,
	       ((INPUT_CSC_BYPASS << INPUT_CSC_CONTROL__INPUT_CSC_GRPH_MODE__SHIFT) |
		(INPUT_CSC_BYPASS << INPUT_CSC_CONTROL__INPUT_CSC_OVL_MODE__SHIFT)));
	WREG32(mmPRESCALE_GRPH_CONTROL + amdgpu_crtc->crtc_offset,
	       PRESCALE_GRPH_CONTROL__GRPH_PRESCALE_BYPASS_MASK);
	WREG32(mmPRESCALE_OVL_CONTROL + amdgpu_crtc->crtc_offset,
	       PRESCALE_OVL_CONTROL__OVL_PRESCALE_BYPASS_MASK);
	WREG32(mmINPUT_GAMMA_CONTROL + amdgpu_crtc->crtc_offset,
	       ((INPUT_GAMMA_USE_LUT << INPUT_GAMMA_CONTROL__GRPH_INPUT_GAMMA_MODE__SHIFT) |
		(INPUT_GAMMA_USE_LUT << INPUT_GAMMA_CONTROL__OVL_INPUT_GAMMA_MODE__SHIFT)));

	WREG32(mmDC_LUT_CONTROL + amdgpu_crtc->crtc_offset, 0);

	WREG32(mmDC_LUT_BLACK_OFFSET_BLUE + amdgpu_crtc->crtc_offset, 0);
	WREG32(mmDC_LUT_BLACK_OFFSET_GREEN + amdgpu_crtc->crtc_offset, 0);
	WREG32(mmDC_LUT_BLACK_OFFSET_RED + amdgpu_crtc->crtc_offset, 0);

	WREG32(mmDC_LUT_WHITE_OFFSET_BLUE + amdgpu_crtc->crtc_offset, 0xffff);
	WREG32(mmDC_LUT_WHITE_OFFSET_GREEN + amdgpu_crtc->crtc_offset, 0xffff);
	WREG32(mmDC_LUT_WHITE_OFFSET_RED + amdgpu_crtc->crtc_offset, 0xffff);

	WREG32(mmDC_LUT_RW_MODE + amdgpu_crtc->crtc_offset, 0);
	WREG32(mmDC_LUT_WRITE_EN_MASK + amdgpu_crtc->crtc_offset, 0x00000007);

	WREG32(mmDC_LUT_RW_INDEX + amdgpu_crtc->crtc_offset, 0);
	r = crtc->gamma_store;
	g = r + crtc->gamma_size;
	b = g + crtc->gamma_size;
	क्रम (i = 0; i < 256; i++) अणु
		WREG32(mmDC_LUT_30_COLOR + amdgpu_crtc->crtc_offset,
		       ((*r++ & 0xffc0) << 14) |
		       ((*g++ & 0xffc0) << 4) |
		       (*b++ >> 6));
	पूर्ण

	WREG32(mmDEGAMMA_CONTROL + amdgpu_crtc->crtc_offset,
	       ((DEGAMMA_BYPASS << DEGAMMA_CONTROL__GRPH_DEGAMMA_MODE__SHIFT) |
		(DEGAMMA_BYPASS << DEGAMMA_CONTROL__OVL_DEGAMMA_MODE__SHIFT) |
		(DEGAMMA_BYPASS << DEGAMMA_CONTROL__CURSOR_DEGAMMA_MODE__SHIFT)));
	WREG32(mmGAMUT_REMAP_CONTROL + amdgpu_crtc->crtc_offset,
	       ((GAMUT_REMAP_BYPASS << GAMUT_REMAP_CONTROL__GRPH_GAMUT_REMAP_MODE__SHIFT) |
		(GAMUT_REMAP_BYPASS << GAMUT_REMAP_CONTROL__OVL_GAMUT_REMAP_MODE__SHIFT)));
	WREG32(mmREGAMMA_CONTROL + amdgpu_crtc->crtc_offset,
	       ((REGAMMA_BYPASS << REGAMMA_CONTROL__GRPH_REGAMMA_MODE__SHIFT) |
		(REGAMMA_BYPASS << REGAMMA_CONTROL__OVL_REGAMMA_MODE__SHIFT)));
	WREG32(mmOUTPUT_CSC_CONTROL + amdgpu_crtc->crtc_offset,
	       ((OUTPUT_CSC_BYPASS << OUTPUT_CSC_CONTROL__OUTPUT_CSC_GRPH_MODE__SHIFT) |
		(OUTPUT_CSC_BYPASS << OUTPUT_CSC_CONTROL__OUTPUT_CSC_OVL_MODE__SHIFT)));
	/* XXX match this to the depth of the crtc fmt block, move to modeset? */
	WREG32(0x1a50 + amdgpu_crtc->crtc_offset, 0);
	/* XXX this only needs to be programmed once per crtc at startup,
	 * not sure where the best place क्रम it is
	 */
	WREG32(mmALPHA_CONTROL + amdgpu_crtc->crtc_offset,
	       ALPHA_CONTROL__CURSOR_ALPHA_BLND_ENA_MASK);
पूर्ण

अटल पूर्णांक dce_v8_0_pick_dig_encoder(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	काष्ठा amdgpu_encoder_atom_dig *dig = amdgpu_encoder->enc_priv;

	चयन (amdgpu_encoder->encoder_id) अणु
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
		अगर (dig->linkb)
			वापस 1;
		अन्यथा
			वापस 0;
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
		अगर (dig->linkb)
			वापस 3;
		अन्यथा
			वापस 2;
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
		अगर (dig->linkb)
			वापस 5;
		अन्यथा
			वापस 4;
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY3:
		वापस 6;
		अवरोध;
	शेष:
		DRM_ERROR("invalid encoder_id: 0x%x\n", amdgpu_encoder->encoder_id);
		वापस 0;
	पूर्ण
पूर्ण

/**
 * dce_v8_0_pick_pll - Allocate a PPLL क्रम use by the crtc.
 *
 * @crtc: drm crtc
 *
 * Returns the PPLL (Pixel PLL) to be used by the crtc.  For DP monitors
 * a single PPLL can be used क्रम all DP crtcs/encoders.  For non-DP
 * monitors a dedicated PPLL must be used.  If a particular board has
 * an बाह्यal DP PLL, वापस ATOM_PPLL_INVALID to skip PLL programming
 * as there is no need to program the PLL itself.  If we are not able to
 * allocate a PLL, वापस ATOM_PPLL_INVALID to skip PLL programming to
 * aव्योम messing up an existing monitor.
 *
 * Asic specअगरic PLL inक्रमmation
 *
 * DCE 8.x
 * KB/KV
 * - PPLL1, PPLL2 are available क्रम all UNIPHY (both DP and non-DP)
 * CI
 * - PPLL0, PPLL1, PPLL2 are available क्रम all UNIPHY (both DP and non-DP) and DAC
 *
 */
अटल u32 dce_v8_0_pick_pll(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	u32 pll_in_use;
	पूर्णांक pll;

	अगर (ENCODER_MODE_IS_DP(amdgpu_atombios_encoder_get_encoder_mode(amdgpu_crtc->encoder))) अणु
		अगर (adev->घड़ी.dp_extclk)
			/* skip PPLL programming अगर using ext घड़ी */
			वापस ATOM_PPLL_INVALID;
		अन्यथा अणु
			/* use the same PPLL क्रम all DP monitors */
			pll = amdgpu_pll_get_shared_dp_ppll(crtc);
			अगर (pll != ATOM_PPLL_INVALID)
				वापस pll;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* use the same PPLL क्रम all monitors with the same घड़ी */
		pll = amdgpu_pll_get_shared_nondp_ppll(crtc);
		अगर (pll != ATOM_PPLL_INVALID)
			वापस pll;
	पूर्ण
	/* otherwise, pick one of the plls */
	अगर ((adev->asic_type == CHIP_KABINI) ||
	    (adev->asic_type == CHIP_MULLINS)) अणु
		/* KB/ML has PPLL1 and PPLL2 */
		pll_in_use = amdgpu_pll_get_use_mask(crtc);
		अगर (!(pll_in_use & (1 << ATOM_PPLL2)))
			वापस ATOM_PPLL2;
		अगर (!(pll_in_use & (1 << ATOM_PPLL1)))
			वापस ATOM_PPLL1;
		DRM_ERROR("unable to allocate a PPLL\n");
		वापस ATOM_PPLL_INVALID;
	पूर्ण अन्यथा अणु
		/* CI/KV has PPLL0, PPLL1, and PPLL2 */
		pll_in_use = amdgpu_pll_get_use_mask(crtc);
		अगर (!(pll_in_use & (1 << ATOM_PPLL2)))
			वापस ATOM_PPLL2;
		अगर (!(pll_in_use & (1 << ATOM_PPLL1)))
			वापस ATOM_PPLL1;
		अगर (!(pll_in_use & (1 << ATOM_PPLL0)))
			वापस ATOM_PPLL0;
		DRM_ERROR("unable to allocate a PPLL\n");
		वापस ATOM_PPLL_INVALID;
	पूर्ण
	वापस ATOM_PPLL_INVALID;
पूर्ण

अटल व्योम dce_v8_0_lock_cursor(काष्ठा drm_crtc *crtc, bool lock)
अणु
	काष्ठा amdgpu_device *adev = drm_to_adev(crtc->dev);
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	uपूर्णांक32_t cur_lock;

	cur_lock = RREG32(mmCUR_UPDATE + amdgpu_crtc->crtc_offset);
	अगर (lock)
		cur_lock |= CUR_UPDATE__CURSOR_UPDATE_LOCK_MASK;
	अन्यथा
		cur_lock &= ~CUR_UPDATE__CURSOR_UPDATE_LOCK_MASK;
	WREG32(mmCUR_UPDATE + amdgpu_crtc->crtc_offset, cur_lock);
पूर्ण

अटल व्योम dce_v8_0_hide_cursor(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	काष्ठा amdgpu_device *adev = drm_to_adev(crtc->dev);

	WREG32(mmCUR_CONTROL + amdgpu_crtc->crtc_offset,
	       (CURSOR_24_8_PRE_MULT << CUR_CONTROL__CURSOR_MODE__SHIFT) |
	       (CURSOR_URGENT_1_2 << CUR_CONTROL__CURSOR_URGENT_CONTROL__SHIFT));
पूर्ण

अटल व्योम dce_v8_0_show_cursor(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	काष्ठा amdgpu_device *adev = drm_to_adev(crtc->dev);

	WREG32(mmCUR_SURFACE_ADDRESS_HIGH + amdgpu_crtc->crtc_offset,
	       upper_32_bits(amdgpu_crtc->cursor_addr));
	WREG32(mmCUR_SURFACE_ADDRESS + amdgpu_crtc->crtc_offset,
	       lower_32_bits(amdgpu_crtc->cursor_addr));

	WREG32(mmCUR_CONTROL + amdgpu_crtc->crtc_offset,
	       CUR_CONTROL__CURSOR_EN_MASK |
	       (CURSOR_24_8_PRE_MULT << CUR_CONTROL__CURSOR_MODE__SHIFT) |
	       (CURSOR_URGENT_1_2 << CUR_CONTROL__CURSOR_URGENT_CONTROL__SHIFT));
पूर्ण

अटल पूर्णांक dce_v8_0_cursor_move_locked(काष्ठा drm_crtc *crtc,
				       पूर्णांक x, पूर्णांक y)
अणु
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	काष्ठा amdgpu_device *adev = drm_to_adev(crtc->dev);
	पूर्णांक xorigin = 0, yorigin = 0;

	amdgpu_crtc->cursor_x = x;
	amdgpu_crtc->cursor_y = y;

	/* avivo cursor are offset पूर्णांकo the total surface */
	x += crtc->x;
	y += crtc->y;
	DRM_DEBUG("x %d y %d c->x %d c->y %d\n", x, y, crtc->x, crtc->y);

	अगर (x < 0) अणु
		xorigin = min(-x, amdgpu_crtc->max_cursor_width - 1);
		x = 0;
	पूर्ण
	अगर (y < 0) अणु
		yorigin = min(-y, amdgpu_crtc->max_cursor_height - 1);
		y = 0;
	पूर्ण

	WREG32(mmCUR_POSITION + amdgpu_crtc->crtc_offset, (x << 16) | y);
	WREG32(mmCUR_HOT_SPOT + amdgpu_crtc->crtc_offset, (xorigin << 16) | yorigin);
	WREG32(mmCUR_SIZE + amdgpu_crtc->crtc_offset,
	       ((amdgpu_crtc->cursor_width - 1) << 16) | (amdgpu_crtc->cursor_height - 1));

	वापस 0;
पूर्ण

अटल पूर्णांक dce_v8_0_crtc_cursor_move(काष्ठा drm_crtc *crtc,
				     पूर्णांक x, पूर्णांक y)
अणु
	पूर्णांक ret;

	dce_v8_0_lock_cursor(crtc, true);
	ret = dce_v8_0_cursor_move_locked(crtc, x, y);
	dce_v8_0_lock_cursor(crtc, false);

	वापस ret;
पूर्ण

अटल पूर्णांक dce_v8_0_crtc_cursor_set2(काष्ठा drm_crtc *crtc,
				     काष्ठा drm_file *file_priv,
				     uपूर्णांक32_t handle,
				     uपूर्णांक32_t width,
				     uपूर्णांक32_t height,
				     पूर्णांक32_t hot_x,
				     पूर्णांक32_t hot_y)
अणु
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	काष्ठा drm_gem_object *obj;
	काष्ठा amdgpu_bo *aobj;
	पूर्णांक ret;

	अगर (!handle) अणु
		/* turn off cursor */
		dce_v8_0_hide_cursor(crtc);
		obj = शून्य;
		जाओ unpin;
	पूर्ण

	अगर ((width > amdgpu_crtc->max_cursor_width) ||
	    (height > amdgpu_crtc->max_cursor_height)) अणु
		DRM_ERROR("bad cursor width or height %d x %d\n", width, height);
		वापस -EINVAL;
	पूर्ण

	obj = drm_gem_object_lookup(file_priv, handle);
	अगर (!obj) अणु
		DRM_ERROR("Cannot find cursor object %x for crtc %d\n", handle, amdgpu_crtc->crtc_id);
		वापस -ENOENT;
	पूर्ण

	aobj = gem_to_amdgpu_bo(obj);
	ret = amdgpu_bo_reserve(aobj, false);
	अगर (ret != 0) अणु
		drm_gem_object_put(obj);
		वापस ret;
	पूर्ण

	ret = amdgpu_bo_pin(aobj, AMDGPU_GEM_DOMAIN_VRAM);
	amdgpu_bo_unreserve(aobj);
	अगर (ret) अणु
		DRM_ERROR("Failed to pin new cursor BO (%d)\n", ret);
		drm_gem_object_put(obj);
		वापस ret;
	पूर्ण
	amdgpu_crtc->cursor_addr = amdgpu_bo_gpu_offset(aobj);

	dce_v8_0_lock_cursor(crtc, true);

	अगर (width != amdgpu_crtc->cursor_width ||
	    height != amdgpu_crtc->cursor_height ||
	    hot_x != amdgpu_crtc->cursor_hot_x ||
	    hot_y != amdgpu_crtc->cursor_hot_y) अणु
		पूर्णांक x, y;

		x = amdgpu_crtc->cursor_x + amdgpu_crtc->cursor_hot_x - hot_x;
		y = amdgpu_crtc->cursor_y + amdgpu_crtc->cursor_hot_y - hot_y;

		dce_v8_0_cursor_move_locked(crtc, x, y);

		amdgpu_crtc->cursor_width = width;
		amdgpu_crtc->cursor_height = height;
		amdgpu_crtc->cursor_hot_x = hot_x;
		amdgpu_crtc->cursor_hot_y = hot_y;
	पूर्ण

	dce_v8_0_show_cursor(crtc);
	dce_v8_0_lock_cursor(crtc, false);

unpin:
	अगर (amdgpu_crtc->cursor_bo) अणु
		काष्ठा amdgpu_bo *aobj = gem_to_amdgpu_bo(amdgpu_crtc->cursor_bo);
		ret = amdgpu_bo_reserve(aobj, true);
		अगर (likely(ret == 0)) अणु
			amdgpu_bo_unpin(aobj);
			amdgpu_bo_unreserve(aobj);
		पूर्ण
		drm_gem_object_put(amdgpu_crtc->cursor_bo);
	पूर्ण

	amdgpu_crtc->cursor_bo = obj;
	वापस 0;
पूर्ण

अटल व्योम dce_v8_0_cursor_reset(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);

	अगर (amdgpu_crtc->cursor_bo) अणु
		dce_v8_0_lock_cursor(crtc, true);

		dce_v8_0_cursor_move_locked(crtc, amdgpu_crtc->cursor_x,
					    amdgpu_crtc->cursor_y);

		dce_v8_0_show_cursor(crtc);

		dce_v8_0_lock_cursor(crtc, false);
	पूर्ण
पूर्ण

अटल पूर्णांक dce_v8_0_crtc_gamma_set(काष्ठा drm_crtc *crtc, u16 *red, u16 *green,
				   u16 *blue, uपूर्णांक32_t size,
				   काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	dce_v8_0_crtc_load_lut(crtc);

	वापस 0;
पूर्ण

अटल व्योम dce_v8_0_crtc_destroy(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);

	drm_crtc_cleanup(crtc);
	kमुक्त(amdgpu_crtc);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs dce_v8_0_crtc_funcs = अणु
	.cursor_set2 = dce_v8_0_crtc_cursor_set2,
	.cursor_move = dce_v8_0_crtc_cursor_move,
	.gamma_set = dce_v8_0_crtc_gamma_set,
	.set_config = amdgpu_display_crtc_set_config,
	.destroy = dce_v8_0_crtc_destroy,
	.page_flip_target = amdgpu_display_crtc_page_flip_target,
	.get_vblank_counter = amdgpu_get_vblank_counter_kms,
	.enable_vblank = amdgpu_enable_vblank_kms,
	.disable_vblank = amdgpu_disable_vblank_kms,
	.get_vblank_बारtamp = drm_crtc_vblank_helper_get_vblank_बारtamp,
पूर्ण;

अटल व्योम dce_v8_0_crtc_dpms(काष्ठा drm_crtc *crtc, पूर्णांक mode)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	अचिन्हित type;

	चयन (mode) अणु
	हाल DRM_MODE_DPMS_ON:
		amdgpu_crtc->enabled = true;
		amdgpu_atombios_crtc_enable(crtc, ATOM_ENABLE);
		dce_v8_0_vga_enable(crtc, true);
		amdgpu_atombios_crtc_blank(crtc, ATOM_DISABLE);
		dce_v8_0_vga_enable(crtc, false);
		/* Make sure VBLANK and PFLIP पूर्णांकerrupts are still enabled */
		type = amdgpu_display_crtc_idx_to_irq_type(adev,
						amdgpu_crtc->crtc_id);
		amdgpu_irq_update(adev, &adev->crtc_irq, type);
		amdgpu_irq_update(adev, &adev->pageflip_irq, type);
		drm_crtc_vblank_on(crtc);
		dce_v8_0_crtc_load_lut(crtc);
		अवरोध;
	हाल DRM_MODE_DPMS_STANDBY:
	हाल DRM_MODE_DPMS_SUSPEND:
	हाल DRM_MODE_DPMS_OFF:
		drm_crtc_vblank_off(crtc);
		अगर (amdgpu_crtc->enabled) अणु
			dce_v8_0_vga_enable(crtc, true);
			amdgpu_atombios_crtc_blank(crtc, ATOM_ENABLE);
			dce_v8_0_vga_enable(crtc, false);
		पूर्ण
		amdgpu_atombios_crtc_enable(crtc, ATOM_DISABLE);
		amdgpu_crtc->enabled = false;
		अवरोध;
	पूर्ण
	/* adjust pm to dpms */
	amdgpu_pm_compute_घड़ीs(adev);
पूर्ण

अटल व्योम dce_v8_0_crtc_prepare(काष्ठा drm_crtc *crtc)
अणु
	/* disable crtc pair घातer gating beक्रमe programming */
	amdgpu_atombios_crtc_घातergate(crtc, ATOM_DISABLE);
	amdgpu_atombios_crtc_lock(crtc, ATOM_ENABLE);
	dce_v8_0_crtc_dpms(crtc, DRM_MODE_DPMS_OFF);
पूर्ण

अटल व्योम dce_v8_0_crtc_commit(काष्ठा drm_crtc *crtc)
अणु
	dce_v8_0_crtc_dpms(crtc, DRM_MODE_DPMS_ON);
	amdgpu_atombios_crtc_lock(crtc, ATOM_DISABLE);
पूर्ण

अटल व्योम dce_v8_0_crtc_disable(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_atom_ss ss;
	पूर्णांक i;

	dce_v8_0_crtc_dpms(crtc, DRM_MODE_DPMS_OFF);
	अगर (crtc->primary->fb) अणु
		पूर्णांक r;
		काष्ठा amdgpu_bo *abo;

		abo = gem_to_amdgpu_bo(crtc->primary->fb->obj[0]);
		r = amdgpu_bo_reserve(abo, true);
		अगर (unlikely(r))
			DRM_ERROR("failed to reserve abo before unpin\n");
		अन्यथा अणु
			amdgpu_bo_unpin(abo);
			amdgpu_bo_unreserve(abo);
		पूर्ण
	पूर्ण
	/* disable the GRPH */
	dce_v8_0_grph_enable(crtc, false);

	amdgpu_atombios_crtc_घातergate(crtc, ATOM_ENABLE);

	क्रम (i = 0; i < adev->mode_info.num_crtc; i++) अणु
		अगर (adev->mode_info.crtcs[i] &&
		    adev->mode_info.crtcs[i]->enabled &&
		    i != amdgpu_crtc->crtc_id &&
		    amdgpu_crtc->pll_id == adev->mode_info.crtcs[i]->pll_id) अणु
			/* one other crtc is using this pll करोn't turn
			 * off the pll
			 */
			जाओ करोne;
		पूर्ण
	पूर्ण

	चयन (amdgpu_crtc->pll_id) अणु
	हाल ATOM_PPLL1:
	हाल ATOM_PPLL2:
		/* disable the ppll */
		amdgpu_atombios_crtc_program_pll(crtc, amdgpu_crtc->crtc_id, amdgpu_crtc->pll_id,
						 0, 0, ATOM_DISABLE, 0, 0, 0, 0, 0, false, &ss);
		अवरोध;
	हाल ATOM_PPLL0:
		/* disable the ppll */
		अगर ((adev->asic_type == CHIP_KAVERI) ||
		    (adev->asic_type == CHIP_BONAIRE) ||
		    (adev->asic_type == CHIP_HAWAII))
			amdgpu_atombios_crtc_program_pll(crtc, amdgpu_crtc->crtc_id, amdgpu_crtc->pll_id,
						  0, 0, ATOM_DISABLE, 0, 0, 0, 0, 0, false, &ss);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
करोne:
	amdgpu_crtc->pll_id = ATOM_PPLL_INVALID;
	amdgpu_crtc->adjusted_घड़ी = 0;
	amdgpu_crtc->encoder = शून्य;
	amdgpu_crtc->connector = शून्य;
पूर्ण

अटल पूर्णांक dce_v8_0_crtc_mode_set(काष्ठा drm_crtc *crtc,
				  काष्ठा drm_display_mode *mode,
				  काष्ठा drm_display_mode *adjusted_mode,
				  पूर्णांक x, पूर्णांक y, काष्ठा drm_framebuffer *old_fb)
अणु
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);

	अगर (!amdgpu_crtc->adjusted_घड़ी)
		वापस -EINVAL;

	amdgpu_atombios_crtc_set_pll(crtc, adjusted_mode);
	amdgpu_atombios_crtc_set_dtd_timing(crtc, adjusted_mode);
	dce_v8_0_crtc_करो_set_base(crtc, old_fb, x, y, 0);
	amdgpu_atombios_crtc_overscan_setup(crtc, mode, adjusted_mode);
	amdgpu_atombios_crtc_scaler_setup(crtc);
	dce_v8_0_cursor_reset(crtc);
	/* update the hw version fpr dpm */
	amdgpu_crtc->hw_mode = *adjusted_mode;

	वापस 0;
पूर्ण

अटल bool dce_v8_0_crtc_mode_fixup(काष्ठा drm_crtc *crtc,
				     स्थिर काष्ठा drm_display_mode *mode,
				     काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_encoder *encoder;

	/* assign the encoder to the amdgpu crtc to aव्योम repeated lookups later */
	list_क्रम_each_entry(encoder, &dev->mode_config.encoder_list, head) अणु
		अगर (encoder->crtc == crtc) अणु
			amdgpu_crtc->encoder = encoder;
			amdgpu_crtc->connector = amdgpu_get_connector_क्रम_encoder(encoder);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर ((amdgpu_crtc->encoder == शून्य) || (amdgpu_crtc->connector == शून्य)) अणु
		amdgpu_crtc->encoder = शून्य;
		amdgpu_crtc->connector = शून्य;
		वापस false;
	पूर्ण
	अगर (!amdgpu_display_crtc_scaling_mode_fixup(crtc, mode, adjusted_mode))
		वापस false;
	अगर (amdgpu_atombios_crtc_prepare_pll(crtc, adjusted_mode))
		वापस false;
	/* pick pll */
	amdgpu_crtc->pll_id = dce_v8_0_pick_pll(crtc);
	/* अगर we can't get a PPLL क्रम a non-DP encoder, fail */
	अगर ((amdgpu_crtc->pll_id == ATOM_PPLL_INVALID) &&
	    !ENCODER_MODE_IS_DP(amdgpu_atombios_encoder_get_encoder_mode(amdgpu_crtc->encoder)))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक dce_v8_0_crtc_set_base(काष्ठा drm_crtc *crtc, पूर्णांक x, पूर्णांक y,
				  काष्ठा drm_framebuffer *old_fb)
अणु
	वापस dce_v8_0_crtc_करो_set_base(crtc, old_fb, x, y, 0);
पूर्ण

अटल पूर्णांक dce_v8_0_crtc_set_base_atomic(काष्ठा drm_crtc *crtc,
					 काष्ठा drm_framebuffer *fb,
					 पूर्णांक x, पूर्णांक y, क्रमागत mode_set_atomic state)
अणु
	वापस dce_v8_0_crtc_करो_set_base(crtc, fb, x, y, 1);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_helper_funcs dce_v8_0_crtc_helper_funcs = अणु
	.dpms = dce_v8_0_crtc_dpms,
	.mode_fixup = dce_v8_0_crtc_mode_fixup,
	.mode_set = dce_v8_0_crtc_mode_set,
	.mode_set_base = dce_v8_0_crtc_set_base,
	.mode_set_base_atomic = dce_v8_0_crtc_set_base_atomic,
	.prepare = dce_v8_0_crtc_prepare,
	.commit = dce_v8_0_crtc_commit,
	.disable = dce_v8_0_crtc_disable,
	.get_scanout_position = amdgpu_crtc_get_scanout_position,
पूर्ण;

अटल पूर्णांक dce_v8_0_crtc_init(काष्ठा amdgpu_device *adev, पूर्णांक index)
अणु
	काष्ठा amdgpu_crtc *amdgpu_crtc;

	amdgpu_crtc = kzalloc(माप(काष्ठा amdgpu_crtc) +
			      (AMDGPUFB_CONN_LIMIT * माप(काष्ठा drm_connector *)), GFP_KERNEL);
	अगर (amdgpu_crtc == शून्य)
		वापस -ENOMEM;

	drm_crtc_init(adev_to_drm(adev), &amdgpu_crtc->base, &dce_v8_0_crtc_funcs);

	drm_mode_crtc_set_gamma_size(&amdgpu_crtc->base, 256);
	amdgpu_crtc->crtc_id = index;
	adev->mode_info.crtcs[index] = amdgpu_crtc;

	amdgpu_crtc->max_cursor_width = CIK_CURSOR_WIDTH;
	amdgpu_crtc->max_cursor_height = CIK_CURSOR_HEIGHT;
	adev_to_drm(adev)->mode_config.cursor_width = amdgpu_crtc->max_cursor_width;
	adev_to_drm(adev)->mode_config.cursor_height = amdgpu_crtc->max_cursor_height;

	amdgpu_crtc->crtc_offset = crtc_offsets[amdgpu_crtc->crtc_id];

	amdgpu_crtc->pll_id = ATOM_PPLL_INVALID;
	amdgpu_crtc->adjusted_घड़ी = 0;
	amdgpu_crtc->encoder = शून्य;
	amdgpu_crtc->connector = शून्य;
	drm_crtc_helper_add(&amdgpu_crtc->base, &dce_v8_0_crtc_helper_funcs);

	वापस 0;
पूर्ण

अटल पूर्णांक dce_v8_0_early_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	adev->audio_endpt_rreg = &dce_v8_0_audio_endpt_rreg;
	adev->audio_endpt_wreg = &dce_v8_0_audio_endpt_wreg;

	dce_v8_0_set_display_funcs(adev);

	adev->mode_info.num_crtc = dce_v8_0_get_num_crtc(adev);

	चयन (adev->asic_type) अणु
	हाल CHIP_BONAIRE:
	हाल CHIP_HAWAII:
		adev->mode_info.num_hpd = 6;
		adev->mode_info.num_dig = 6;
		अवरोध;
	हाल CHIP_KAVERI:
		adev->mode_info.num_hpd = 6;
		adev->mode_info.num_dig = 7;
		अवरोध;
	हाल CHIP_KABINI:
	हाल CHIP_MULLINS:
		adev->mode_info.num_hpd = 6;
		adev->mode_info.num_dig = 6; /* ? */
		अवरोध;
	शेष:
		/* FIXME: not supported yet */
		वापस -EINVAL;
	पूर्ण

	dce_v8_0_set_irq_funcs(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक dce_v8_0_sw_init(व्योम *handle)
अणु
	पूर्णांक r, i;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	क्रम (i = 0; i < adev->mode_info.num_crtc; i++) अणु
		r = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, i + 1, &adev->crtc_irq);
		अगर (r)
			वापस r;
	पूर्ण

	क्रम (i = 8; i < 20; i += 2) अणु
		r = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, i, &adev->pageflip_irq);
		अगर (r)
			वापस r;
	पूर्ण

	/* HPD hotplug */
	r = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, 42, &adev->hpd_irq);
	अगर (r)
		वापस r;

	adev_to_drm(adev)->mode_config.funcs = &amdgpu_mode_funcs;

	adev_to_drm(adev)->mode_config.async_page_flip = true;

	adev_to_drm(adev)->mode_config.max_width = 16384;
	adev_to_drm(adev)->mode_config.max_height = 16384;

	adev_to_drm(adev)->mode_config.preferred_depth = 24;
	adev_to_drm(adev)->mode_config.prefer_shaकरोw = 1;

	adev_to_drm(adev)->mode_config.fb_base = adev->gmc.aper_base;

	r = amdgpu_display_modeset_create_props(adev);
	अगर (r)
		वापस r;

	adev_to_drm(adev)->mode_config.max_width = 16384;
	adev_to_drm(adev)->mode_config.max_height = 16384;

	/* allocate crtcs */
	क्रम (i = 0; i < adev->mode_info.num_crtc; i++) अणु
		r = dce_v8_0_crtc_init(adev, i);
		अगर (r)
			वापस r;
	पूर्ण

	अगर (amdgpu_atombios_get_connector_info_from_object_table(adev))
		amdgpu_display_prपूर्णांक_display_setup(adev_to_drm(adev));
	अन्यथा
		वापस -EINVAL;

	/* setup afmt */
	r = dce_v8_0_afmt_init(adev);
	अगर (r)
		वापस r;

	r = dce_v8_0_audio_init(adev);
	अगर (r)
		वापस r;

	drm_kms_helper_poll_init(adev_to_drm(adev));

	adev->mode_info.mode_config_initialized = true;
	वापस 0;
पूर्ण

अटल पूर्णांक dce_v8_0_sw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	kमुक्त(adev->mode_info.bios_hardcoded_edid);

	drm_kms_helper_poll_fini(adev_to_drm(adev));

	dce_v8_0_audio_fini(adev);

	dce_v8_0_afmt_fini(adev);

	drm_mode_config_cleanup(adev_to_drm(adev));
	adev->mode_info.mode_config_initialized = false;

	वापस 0;
पूर्ण

अटल पूर्णांक dce_v8_0_hw_init(व्योम *handle)
अणु
	पूर्णांक i;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	/* disable vga render */
	dce_v8_0_set_vga_render_state(adev, false);
	/* init dig PHYs, disp eng pll */
	amdgpu_atombios_encoder_init_dig(adev);
	amdgpu_atombios_crtc_set_disp_eng_pll(adev, adev->घड़ी.शेष_dispclk);

	/* initialize hpd */
	dce_v8_0_hpd_init(adev);

	क्रम (i = 0; i < adev->mode_info.audio.num_pins; i++) अणु
		dce_v8_0_audio_enable(adev, &adev->mode_info.audio.pin[i], false);
	पूर्ण

	dce_v8_0_pageflip_पूर्णांकerrupt_init(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक dce_v8_0_hw_fini(व्योम *handle)
अणु
	पूर्णांक i;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	dce_v8_0_hpd_fini(adev);

	क्रम (i = 0; i < adev->mode_info.audio.num_pins; i++) अणु
		dce_v8_0_audio_enable(adev, &adev->mode_info.audio.pin[i], false);
	पूर्ण

	dce_v8_0_pageflip_पूर्णांकerrupt_fini(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक dce_v8_0_suspend(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक r;

	r = amdgpu_display_suspend_helper(adev);
	अगर (r)
		वापस r;

	adev->mode_info.bl_level =
		amdgpu_atombios_encoder_get_backlight_level_from_reg(adev);

	वापस dce_v8_0_hw_fini(handle);
पूर्ण

अटल पूर्णांक dce_v8_0_resume(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक ret;

	amdgpu_atombios_encoder_set_backlight_level_to_reg(adev,
							   adev->mode_info.bl_level);

	ret = dce_v8_0_hw_init(handle);

	/* turn on the BL */
	अगर (adev->mode_info.bl_encoder) अणु
		u8 bl_level = amdgpu_display_backlight_get_level(adev,
								  adev->mode_info.bl_encoder);
		amdgpu_display_backlight_set_level(adev, adev->mode_info.bl_encoder,
						    bl_level);
	पूर्ण
	अगर (ret)
		वापस ret;

	वापस amdgpu_display_resume_helper(adev);
पूर्ण

अटल bool dce_v8_0_is_idle(व्योम *handle)
अणु
	वापस true;
पूर्ण

अटल पूर्णांक dce_v8_0_रुको_क्रम_idle(व्योम *handle)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक dce_v8_0_soft_reset(व्योम *handle)
अणु
	u32 srbm_soft_reset = 0, पंचांगp;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (dce_v8_0_is_display_hung(adev))
		srbm_soft_reset |= SRBM_SOFT_RESET__SOFT_RESET_DC_MASK;

	अगर (srbm_soft_reset) अणु
		पंचांगp = RREG32(mmSRBM_SOFT_RESET);
		पंचांगp |= srbm_soft_reset;
		dev_info(adev->dev, "SRBM_SOFT_RESET=0x%08X\n", पंचांगp);
		WREG32(mmSRBM_SOFT_RESET, पंचांगp);
		पंचांगp = RREG32(mmSRBM_SOFT_RESET);

		udelay(50);

		पंचांगp &= ~srbm_soft_reset;
		WREG32(mmSRBM_SOFT_RESET, पंचांगp);
		पंचांगp = RREG32(mmSRBM_SOFT_RESET);

		/* Wait a little क्रम things to settle करोwn */
		udelay(50);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम dce_v8_0_set_crtc_vblank_पूर्णांकerrupt_state(काष्ठा amdgpu_device *adev,
						     पूर्णांक crtc,
						     क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	u32 reg_block, lb_पूर्णांकerrupt_mask;

	अगर (crtc >= adev->mode_info.num_crtc) अणु
		DRM_DEBUG("invalid crtc %d\n", crtc);
		वापस;
	पूर्ण

	चयन (crtc) अणु
	हाल 0:
		reg_block = CRTC0_REGISTER_OFFSET;
		अवरोध;
	हाल 1:
		reg_block = CRTC1_REGISTER_OFFSET;
		अवरोध;
	हाल 2:
		reg_block = CRTC2_REGISTER_OFFSET;
		अवरोध;
	हाल 3:
		reg_block = CRTC3_REGISTER_OFFSET;
		अवरोध;
	हाल 4:
		reg_block = CRTC4_REGISTER_OFFSET;
		अवरोध;
	हाल 5:
		reg_block = CRTC5_REGISTER_OFFSET;
		अवरोध;
	शेष:
		DRM_DEBUG("invalid crtc %d\n", crtc);
		वापस;
	पूर्ण

	चयन (state) अणु
	हाल AMDGPU_IRQ_STATE_DISABLE:
		lb_पूर्णांकerrupt_mask = RREG32(mmLB_INTERRUPT_MASK + reg_block);
		lb_पूर्णांकerrupt_mask &= ~LB_INTERRUPT_MASK__VBLANK_INTERRUPT_MASK_MASK;
		WREG32(mmLB_INTERRUPT_MASK + reg_block, lb_पूर्णांकerrupt_mask);
		अवरोध;
	हाल AMDGPU_IRQ_STATE_ENABLE:
		lb_पूर्णांकerrupt_mask = RREG32(mmLB_INTERRUPT_MASK + reg_block);
		lb_पूर्णांकerrupt_mask |= LB_INTERRUPT_MASK__VBLANK_INTERRUPT_MASK_MASK;
		WREG32(mmLB_INTERRUPT_MASK + reg_block, lb_पूर्णांकerrupt_mask);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम dce_v8_0_set_crtc_vline_पूर्णांकerrupt_state(काष्ठा amdgpu_device *adev,
						    पूर्णांक crtc,
						    क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	u32 reg_block, lb_पूर्णांकerrupt_mask;

	अगर (crtc >= adev->mode_info.num_crtc) अणु
		DRM_DEBUG("invalid crtc %d\n", crtc);
		वापस;
	पूर्ण

	चयन (crtc) अणु
	हाल 0:
		reg_block = CRTC0_REGISTER_OFFSET;
		अवरोध;
	हाल 1:
		reg_block = CRTC1_REGISTER_OFFSET;
		अवरोध;
	हाल 2:
		reg_block = CRTC2_REGISTER_OFFSET;
		अवरोध;
	हाल 3:
		reg_block = CRTC3_REGISTER_OFFSET;
		अवरोध;
	हाल 4:
		reg_block = CRTC4_REGISTER_OFFSET;
		अवरोध;
	हाल 5:
		reg_block = CRTC5_REGISTER_OFFSET;
		अवरोध;
	शेष:
		DRM_DEBUG("invalid crtc %d\n", crtc);
		वापस;
	पूर्ण

	चयन (state) अणु
	हाल AMDGPU_IRQ_STATE_DISABLE:
		lb_पूर्णांकerrupt_mask = RREG32(mmLB_INTERRUPT_MASK + reg_block);
		lb_पूर्णांकerrupt_mask &= ~LB_INTERRUPT_MASK__VLINE_INTERRUPT_MASK_MASK;
		WREG32(mmLB_INTERRUPT_MASK + reg_block, lb_पूर्णांकerrupt_mask);
		अवरोध;
	हाल AMDGPU_IRQ_STATE_ENABLE:
		lb_पूर्णांकerrupt_mask = RREG32(mmLB_INTERRUPT_MASK + reg_block);
		lb_पूर्णांकerrupt_mask |= LB_INTERRUPT_MASK__VLINE_INTERRUPT_MASK_MASK;
		WREG32(mmLB_INTERRUPT_MASK + reg_block, lb_पूर्णांकerrupt_mask);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक dce_v8_0_set_hpd_पूर्णांकerrupt_state(काष्ठा amdgpu_device *adev,
					    काष्ठा amdgpu_irq_src *src,
					    अचिन्हित type,
					    क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	u32 dc_hpd_पूर्णांक_cntl;

	अगर (type >= adev->mode_info.num_hpd) अणु
		DRM_DEBUG("invalid hdp %d\n", type);
		वापस 0;
	पूर्ण

	चयन (state) अणु
	हाल AMDGPU_IRQ_STATE_DISABLE:
		dc_hpd_पूर्णांक_cntl = RREG32(mmDC_HPD1_INT_CONTROL + hpd_offsets[type]);
		dc_hpd_पूर्णांक_cntl &= ~DC_HPD1_INT_CONTROL__DC_HPD1_INT_EN_MASK;
		WREG32(mmDC_HPD1_INT_CONTROL + hpd_offsets[type], dc_hpd_पूर्णांक_cntl);
		अवरोध;
	हाल AMDGPU_IRQ_STATE_ENABLE:
		dc_hpd_पूर्णांक_cntl = RREG32(mmDC_HPD1_INT_CONTROL + hpd_offsets[type]);
		dc_hpd_पूर्णांक_cntl |= DC_HPD1_INT_CONTROL__DC_HPD1_INT_EN_MASK;
		WREG32(mmDC_HPD1_INT_CONTROL + hpd_offsets[type], dc_hpd_पूर्णांक_cntl);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dce_v8_0_set_crtc_पूर्णांकerrupt_state(काष्ठा amdgpu_device *adev,
					     काष्ठा amdgpu_irq_src *src,
					     अचिन्हित type,
					     क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	चयन (type) अणु
	हाल AMDGPU_CRTC_IRQ_VBLANK1:
		dce_v8_0_set_crtc_vblank_पूर्णांकerrupt_state(adev, 0, state);
		अवरोध;
	हाल AMDGPU_CRTC_IRQ_VBLANK2:
		dce_v8_0_set_crtc_vblank_पूर्णांकerrupt_state(adev, 1, state);
		अवरोध;
	हाल AMDGPU_CRTC_IRQ_VBLANK3:
		dce_v8_0_set_crtc_vblank_पूर्णांकerrupt_state(adev, 2, state);
		अवरोध;
	हाल AMDGPU_CRTC_IRQ_VBLANK4:
		dce_v8_0_set_crtc_vblank_पूर्णांकerrupt_state(adev, 3, state);
		अवरोध;
	हाल AMDGPU_CRTC_IRQ_VBLANK5:
		dce_v8_0_set_crtc_vblank_पूर्णांकerrupt_state(adev, 4, state);
		अवरोध;
	हाल AMDGPU_CRTC_IRQ_VBLANK6:
		dce_v8_0_set_crtc_vblank_पूर्णांकerrupt_state(adev, 5, state);
		अवरोध;
	हाल AMDGPU_CRTC_IRQ_VLINE1:
		dce_v8_0_set_crtc_vline_पूर्णांकerrupt_state(adev, 0, state);
		अवरोध;
	हाल AMDGPU_CRTC_IRQ_VLINE2:
		dce_v8_0_set_crtc_vline_पूर्णांकerrupt_state(adev, 1, state);
		अवरोध;
	हाल AMDGPU_CRTC_IRQ_VLINE3:
		dce_v8_0_set_crtc_vline_पूर्णांकerrupt_state(adev, 2, state);
		अवरोध;
	हाल AMDGPU_CRTC_IRQ_VLINE4:
		dce_v8_0_set_crtc_vline_पूर्णांकerrupt_state(adev, 3, state);
		अवरोध;
	हाल AMDGPU_CRTC_IRQ_VLINE5:
		dce_v8_0_set_crtc_vline_पूर्णांकerrupt_state(adev, 4, state);
		अवरोध;
	हाल AMDGPU_CRTC_IRQ_VLINE6:
		dce_v8_0_set_crtc_vline_पूर्णांकerrupt_state(adev, 5, state);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dce_v8_0_crtc_irq(काष्ठा amdgpu_device *adev,
			     काष्ठा amdgpu_irq_src *source,
			     काष्ठा amdgpu_iv_entry *entry)
अणु
	अचिन्हित crtc = entry->src_id - 1;
	uपूर्णांक32_t disp_पूर्णांक = RREG32(पूर्णांकerrupt_status_offsets[crtc].reg);
	अचिन्हित पूर्णांक irq_type = amdgpu_display_crtc_idx_to_irq_type(adev,
								    crtc);

	चयन (entry->src_data[0]) अणु
	हाल 0: /* vblank */
		अगर (disp_पूर्णांक & पूर्णांकerrupt_status_offsets[crtc].vblank)
			WREG32(mmLB_VBLANK_STATUS + crtc_offsets[crtc], LB_VBLANK_STATUS__VBLANK_ACK_MASK);
		अन्यथा
			DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

		अगर (amdgpu_irq_enabled(adev, source, irq_type)) अणु
			drm_handle_vblank(adev_to_drm(adev), crtc);
		पूर्ण
		DRM_DEBUG("IH: D%d vblank\n", crtc + 1);
		अवरोध;
	हाल 1: /* vline */
		अगर (disp_पूर्णांक & पूर्णांकerrupt_status_offsets[crtc].vline)
			WREG32(mmLB_VLINE_STATUS + crtc_offsets[crtc], LB_VLINE_STATUS__VLINE_ACK_MASK);
		अन्यथा
			DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

		DRM_DEBUG("IH: D%d vline\n", crtc + 1);
		अवरोध;
	शेष:
		DRM_DEBUG("Unhandled interrupt: %d %d\n", entry->src_id, entry->src_data[0]);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dce_v8_0_set_pageflip_पूर्णांकerrupt_state(काष्ठा amdgpu_device *adev,
						 काष्ठा amdgpu_irq_src *src,
						 अचिन्हित type,
						 क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	u32 reg;

	अगर (type >= adev->mode_info.num_crtc) अणु
		DRM_ERROR("invalid pageflip crtc %d\n", type);
		वापस -EINVAL;
	पूर्ण

	reg = RREG32(mmGRPH_INTERRUPT_CONTROL + crtc_offsets[type]);
	अगर (state == AMDGPU_IRQ_STATE_DISABLE)
		WREG32(mmGRPH_INTERRUPT_CONTROL + crtc_offsets[type],
		       reg & ~GRPH_INTERRUPT_CONTROL__GRPH_PFLIP_INT_MASK_MASK);
	अन्यथा
		WREG32(mmGRPH_INTERRUPT_CONTROL + crtc_offsets[type],
		       reg | GRPH_INTERRUPT_CONTROL__GRPH_PFLIP_INT_MASK_MASK);

	वापस 0;
पूर्ण

अटल पूर्णांक dce_v8_0_pageflip_irq(काष्ठा amdgpu_device *adev,
				काष्ठा amdgpu_irq_src *source,
				काष्ठा amdgpu_iv_entry *entry)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित crtc_id;
	काष्ठा amdgpu_crtc *amdgpu_crtc;
	काष्ठा amdgpu_flip_work *works;

	crtc_id = (entry->src_id - 8) >> 1;
	amdgpu_crtc = adev->mode_info.crtcs[crtc_id];

	अगर (crtc_id >= adev->mode_info.num_crtc) अणु
		DRM_ERROR("invalid pageflip crtc %d\n", crtc_id);
		वापस -EINVAL;
	पूर्ण

	अगर (RREG32(mmGRPH_INTERRUPT_STATUS + crtc_offsets[crtc_id]) &
	    GRPH_INTERRUPT_STATUS__GRPH_PFLIP_INT_OCCURRED_MASK)
		WREG32(mmGRPH_INTERRUPT_STATUS + crtc_offsets[crtc_id],
		       GRPH_INTERRUPT_STATUS__GRPH_PFLIP_INT_CLEAR_MASK);

	/* IRQ could occur when in initial stage */
	अगर (amdgpu_crtc == शून्य)
		वापस 0;

	spin_lock_irqsave(&adev_to_drm(adev)->event_lock, flags);
	works = amdgpu_crtc->pflip_works;
	अगर (amdgpu_crtc->pflip_status != AMDGPU_FLIP_SUBMITTED)अणु
		DRM_DEBUG_DRIVER("amdgpu_crtc->pflip_status = %d != "
						"AMDGPU_FLIP_SUBMITTED(%d)\n",
						amdgpu_crtc->pflip_status,
						AMDGPU_FLIP_SUBMITTED);
		spin_unlock_irqrestore(&adev_to_drm(adev)->event_lock, flags);
		वापस 0;
	पूर्ण

	/* page flip completed. clean up */
	amdgpu_crtc->pflip_status = AMDGPU_FLIP_NONE;
	amdgpu_crtc->pflip_works = शून्य;

	/* wakeup usersapce */
	अगर (works->event)
		drm_crtc_send_vblank_event(&amdgpu_crtc->base, works->event);

	spin_unlock_irqrestore(&adev_to_drm(adev)->event_lock, flags);

	drm_crtc_vblank_put(&amdgpu_crtc->base);
	schedule_work(&works->unpin_work);

	वापस 0;
पूर्ण

अटल पूर्णांक dce_v8_0_hpd_irq(काष्ठा amdgpu_device *adev,
			    काष्ठा amdgpu_irq_src *source,
			    काष्ठा amdgpu_iv_entry *entry)
अणु
	uपूर्णांक32_t disp_पूर्णांक, mask, पंचांगp;
	अचिन्हित hpd;

	अगर (entry->src_data[0] >= adev->mode_info.num_hpd) अणु
		DRM_DEBUG("Unhandled interrupt: %d %d\n", entry->src_id, entry->src_data[0]);
		वापस 0;
	पूर्ण

	hpd = entry->src_data[0];
	disp_पूर्णांक = RREG32(पूर्णांकerrupt_status_offsets[hpd].reg);
	mask = पूर्णांकerrupt_status_offsets[hpd].hpd;

	अगर (disp_पूर्णांक & mask) अणु
		पंचांगp = RREG32(mmDC_HPD1_INT_CONTROL + hpd_offsets[hpd]);
		पंचांगp |= DC_HPD1_INT_CONTROL__DC_HPD1_INT_ACK_MASK;
		WREG32(mmDC_HPD1_INT_CONTROL + hpd_offsets[hpd], पंचांगp);
		schedule_work(&adev->hotplug_work);
		DRM_DEBUG("IH: HPD%d\n", hpd + 1);
	पूर्ण

	वापस 0;

पूर्ण

अटल पूर्णांक dce_v8_0_set_घड़ीgating_state(व्योम *handle,
					  क्रमागत amd_घड़ीgating_state state)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक dce_v8_0_set_घातergating_state(व्योम *handle,
					  क्रमागत amd_घातergating_state state)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा amd_ip_funcs dce_v8_0_ip_funcs = अणु
	.name = "dce_v8_0",
	.early_init = dce_v8_0_early_init,
	.late_init = शून्य,
	.sw_init = dce_v8_0_sw_init,
	.sw_fini = dce_v8_0_sw_fini,
	.hw_init = dce_v8_0_hw_init,
	.hw_fini = dce_v8_0_hw_fini,
	.suspend = dce_v8_0_suspend,
	.resume = dce_v8_0_resume,
	.is_idle = dce_v8_0_is_idle,
	.रुको_क्रम_idle = dce_v8_0_रुको_क्रम_idle,
	.soft_reset = dce_v8_0_soft_reset,
	.set_घड़ीgating_state = dce_v8_0_set_घड़ीgating_state,
	.set_घातergating_state = dce_v8_0_set_घातergating_state,
पूर्ण;

अटल व्योम
dce_v8_0_encoder_mode_set(काष्ठा drm_encoder *encoder,
			  काष्ठा drm_display_mode *mode,
			  काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);

	amdgpu_encoder->pixel_घड़ी = adjusted_mode->घड़ी;

	/* need to call this here rather than in prepare() since we need some crtc info */
	amdgpu_atombios_encoder_dpms(encoder, DRM_MODE_DPMS_OFF);

	/* set scaler clears this on some chips */
	dce_v8_0_set_पूर्णांकerleave(encoder->crtc, mode);

	अगर (amdgpu_atombios_encoder_get_encoder_mode(encoder) == ATOM_ENCODER_MODE_HDMI) अणु
		dce_v8_0_afmt_enable(encoder, true);
		dce_v8_0_afmt_seपंचांगode(encoder, adjusted_mode);
	पूर्ण
पूर्ण

अटल व्योम dce_v8_0_encoder_prepare(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा amdgpu_device *adev = drm_to_adev(encoder->dev);
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	काष्ठा drm_connector *connector = amdgpu_get_connector_क्रम_encoder(encoder);

	अगर ((amdgpu_encoder->active_device &
	     (ATOM_DEVICE_DFP_SUPPORT | ATOM_DEVICE_LCD_SUPPORT)) ||
	    (amdgpu_encoder_get_dp_bridge_encoder_id(encoder) !=
	     ENCODER_OBJECT_ID_NONE)) अणु
		काष्ठा amdgpu_encoder_atom_dig *dig = amdgpu_encoder->enc_priv;
		अगर (dig) अणु
			dig->dig_encoder = dce_v8_0_pick_dig_encoder(encoder);
			अगर (amdgpu_encoder->active_device & ATOM_DEVICE_DFP_SUPPORT)
				dig->afmt = adev->mode_info.afmt[dig->dig_encoder];
		पूर्ण
	पूर्ण

	amdgpu_atombios_scratch_regs_lock(adev, true);

	अगर (connector) अणु
		काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);

		/* select the घड़ी/data port अगर it uses a router */
		अगर (amdgpu_connector->router.cd_valid)
			amdgpu_i2c_router_select_cd_port(amdgpu_connector);

		/* turn eDP panel on क्रम mode set */
		अगर (connector->connector_type == DRM_MODE_CONNECTOR_eDP)
			amdgpu_atombios_encoder_set_edp_panel_घातer(connector,
							     ATOM_TRANSMITTER_ACTION_POWER_ON);
	पूर्ण

	/* this is needed क्रम the pll/ss setup to work correctly in some हालs */
	amdgpu_atombios_encoder_set_crtc_source(encoder);
	/* set up the FMT blocks */
	dce_v8_0_program_fmt(encoder);
पूर्ण

अटल व्योम dce_v8_0_encoder_commit(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);

	/* need to call this here as we need the crtc set up */
	amdgpu_atombios_encoder_dpms(encoder, DRM_MODE_DPMS_ON);
	amdgpu_atombios_scratch_regs_lock(adev, false);
पूर्ण

अटल व्योम dce_v8_0_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	काष्ठा amdgpu_encoder_atom_dig *dig;

	amdgpu_atombios_encoder_dpms(encoder, DRM_MODE_DPMS_OFF);

	अगर (amdgpu_atombios_encoder_is_digital(encoder)) अणु
		अगर (amdgpu_atombios_encoder_get_encoder_mode(encoder) == ATOM_ENCODER_MODE_HDMI)
			dce_v8_0_afmt_enable(encoder, false);
		dig = amdgpu_encoder->enc_priv;
		dig->dig_encoder = -1;
	पूर्ण
	amdgpu_encoder->active_device = 0;
पूर्ण

/* these are handled by the primary encoders */
अटल व्योम dce_v8_0_ext_prepare(काष्ठा drm_encoder *encoder)
अणु

पूर्ण

अटल व्योम dce_v8_0_ext_commit(काष्ठा drm_encoder *encoder)
अणु

पूर्ण

अटल व्योम
dce_v8_0_ext_mode_set(काष्ठा drm_encoder *encoder,
		      काष्ठा drm_display_mode *mode,
		      काष्ठा drm_display_mode *adjusted_mode)
अणु

पूर्ण

अटल व्योम dce_v8_0_ext_disable(काष्ठा drm_encoder *encoder)
अणु

पूर्ण

अटल व्योम
dce_v8_0_ext_dpms(काष्ठा drm_encoder *encoder, पूर्णांक mode)
अणु

पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs dce_v8_0_ext_helper_funcs = अणु
	.dpms = dce_v8_0_ext_dpms,
	.prepare = dce_v8_0_ext_prepare,
	.mode_set = dce_v8_0_ext_mode_set,
	.commit = dce_v8_0_ext_commit,
	.disable = dce_v8_0_ext_disable,
	/* no detect क्रम TMDS/LVDS yet */
पूर्ण;

अटल स्थिर काष्ठा drm_encoder_helper_funcs dce_v8_0_dig_helper_funcs = अणु
	.dpms = amdgpu_atombios_encoder_dpms,
	.mode_fixup = amdgpu_atombios_encoder_mode_fixup,
	.prepare = dce_v8_0_encoder_prepare,
	.mode_set = dce_v8_0_encoder_mode_set,
	.commit = dce_v8_0_encoder_commit,
	.disable = dce_v8_0_encoder_disable,
	.detect = amdgpu_atombios_encoder_dig_detect,
पूर्ण;

अटल स्थिर काष्ठा drm_encoder_helper_funcs dce_v8_0_dac_helper_funcs = अणु
	.dpms = amdgpu_atombios_encoder_dpms,
	.mode_fixup = amdgpu_atombios_encoder_mode_fixup,
	.prepare = dce_v8_0_encoder_prepare,
	.mode_set = dce_v8_0_encoder_mode_set,
	.commit = dce_v8_0_encoder_commit,
	.detect = amdgpu_atombios_encoder_dac_detect,
पूर्ण;

अटल व्योम dce_v8_0_encoder_destroy(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	अगर (amdgpu_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT))
		amdgpu_atombios_encoder_fini_backlight(amdgpu_encoder);
	kमुक्त(amdgpu_encoder->enc_priv);
	drm_encoder_cleanup(encoder);
	kमुक्त(amdgpu_encoder);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_funcs dce_v8_0_encoder_funcs = अणु
	.destroy = dce_v8_0_encoder_destroy,
पूर्ण;

अटल व्योम dce_v8_0_encoder_add(काष्ठा amdgpu_device *adev,
				 uपूर्णांक32_t encoder_क्रमागत,
				 uपूर्णांक32_t supported_device,
				 u16 caps)
अणु
	काष्ठा drm_device *dev = adev_to_drm(adev);
	काष्ठा drm_encoder *encoder;
	काष्ठा amdgpu_encoder *amdgpu_encoder;

	/* see अगर we alपढ़ोy added it */
	list_क्रम_each_entry(encoder, &dev->mode_config.encoder_list, head) अणु
		amdgpu_encoder = to_amdgpu_encoder(encoder);
		अगर (amdgpu_encoder->encoder_क्रमागत == encoder_क्रमागत) अणु
			amdgpu_encoder->devices |= supported_device;
			वापस;
		पूर्ण

	पूर्ण

	/* add a new one */
	amdgpu_encoder = kzalloc(माप(काष्ठा amdgpu_encoder), GFP_KERNEL);
	अगर (!amdgpu_encoder)
		वापस;

	encoder = &amdgpu_encoder->base;
	चयन (adev->mode_info.num_crtc) अणु
	हाल 1:
		encoder->possible_crtcs = 0x1;
		अवरोध;
	हाल 2:
	शेष:
		encoder->possible_crtcs = 0x3;
		अवरोध;
	हाल 4:
		encoder->possible_crtcs = 0xf;
		अवरोध;
	हाल 6:
		encoder->possible_crtcs = 0x3f;
		अवरोध;
	पूर्ण

	amdgpu_encoder->enc_priv = शून्य;

	amdgpu_encoder->encoder_क्रमागत = encoder_क्रमागत;
	amdgpu_encoder->encoder_id = (encoder_क्रमागत & OBJECT_ID_MASK) >> OBJECT_ID_SHIFT;
	amdgpu_encoder->devices = supported_device;
	amdgpu_encoder->rmx_type = RMX_OFF;
	amdgpu_encoder->underscan_type = UNDERSCAN_OFF;
	amdgpu_encoder->is_ext_encoder = false;
	amdgpu_encoder->caps = caps;

	चयन (amdgpu_encoder->encoder_id) अणु
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC1:
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC2:
		drm_encoder_init(dev, encoder, &dce_v8_0_encoder_funcs,
				 DRM_MODE_ENCODER_DAC, शून्य);
		drm_encoder_helper_add(encoder, &dce_v8_0_dac_helper_funcs);
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1:
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY3:
		अगर (amdgpu_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT)) अणु
			amdgpu_encoder->rmx_type = RMX_FULL;
			drm_encoder_init(dev, encoder, &dce_v8_0_encoder_funcs,
					 DRM_MODE_ENCODER_LVDS, शून्य);
			amdgpu_encoder->enc_priv = amdgpu_atombios_encoder_get_lcd_info(amdgpu_encoder);
		पूर्ण अन्यथा अगर (amdgpu_encoder->devices & (ATOM_DEVICE_CRT_SUPPORT)) अणु
			drm_encoder_init(dev, encoder, &dce_v8_0_encoder_funcs,
					 DRM_MODE_ENCODER_DAC, शून्य);
			amdgpu_encoder->enc_priv = amdgpu_atombios_encoder_get_dig_info(amdgpu_encoder);
		पूर्ण अन्यथा अणु
			drm_encoder_init(dev, encoder, &dce_v8_0_encoder_funcs,
					 DRM_MODE_ENCODER_TMDS, शून्य);
			amdgpu_encoder->enc_priv = amdgpu_atombios_encoder_get_dig_info(amdgpu_encoder);
		पूर्ण
		drm_encoder_helper_add(encoder, &dce_v8_0_dig_helper_funcs);
		अवरोध;
	हाल ENCODER_OBJECT_ID_SI170B:
	हाल ENCODER_OBJECT_ID_CH7303:
	हाल ENCODER_OBJECT_ID_EXTERNAL_SDVOA:
	हाल ENCODER_OBJECT_ID_EXTERNAL_SDVOB:
	हाल ENCODER_OBJECT_ID_TITFP513:
	हाल ENCODER_OBJECT_ID_VT1623:
	हाल ENCODER_OBJECT_ID_HDMI_SI1930:
	हाल ENCODER_OBJECT_ID_TRAVIS:
	हाल ENCODER_OBJECT_ID_NUTMEG:
		/* these are handled by the primary encoders */
		amdgpu_encoder->is_ext_encoder = true;
		अगर (amdgpu_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT))
			drm_encoder_init(dev, encoder, &dce_v8_0_encoder_funcs,
					 DRM_MODE_ENCODER_LVDS, शून्य);
		अन्यथा अगर (amdgpu_encoder->devices & (ATOM_DEVICE_CRT_SUPPORT))
			drm_encoder_init(dev, encoder, &dce_v8_0_encoder_funcs,
					 DRM_MODE_ENCODER_DAC, शून्य);
		अन्यथा
			drm_encoder_init(dev, encoder, &dce_v8_0_encoder_funcs,
					 DRM_MODE_ENCODER_TMDS, शून्य);
		drm_encoder_helper_add(encoder, &dce_v8_0_ext_helper_funcs);
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा amdgpu_display_funcs dce_v8_0_display_funcs = अणु
	.bandwidth_update = &dce_v8_0_bandwidth_update,
	.vblank_get_counter = &dce_v8_0_vblank_get_counter,
	.backlight_set_level = &amdgpu_atombios_encoder_set_backlight_level,
	.backlight_get_level = &amdgpu_atombios_encoder_get_backlight_level,
	.hpd_sense = &dce_v8_0_hpd_sense,
	.hpd_set_polarity = &dce_v8_0_hpd_set_polarity,
	.hpd_get_gpio_reg = &dce_v8_0_hpd_get_gpio_reg,
	.page_flip = &dce_v8_0_page_flip,
	.page_flip_get_scanoutpos = &dce_v8_0_crtc_get_scanoutpos,
	.add_encoder = &dce_v8_0_encoder_add,
	.add_connector = &amdgpu_connector_add,
पूर्ण;

अटल व्योम dce_v8_0_set_display_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->mode_info.funcs = &dce_v8_0_display_funcs;
पूर्ण

अटल स्थिर काष्ठा amdgpu_irq_src_funcs dce_v8_0_crtc_irq_funcs = अणु
	.set = dce_v8_0_set_crtc_पूर्णांकerrupt_state,
	.process = dce_v8_0_crtc_irq,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_irq_src_funcs dce_v8_0_pageflip_irq_funcs = अणु
	.set = dce_v8_0_set_pageflip_पूर्णांकerrupt_state,
	.process = dce_v8_0_pageflip_irq,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_irq_src_funcs dce_v8_0_hpd_irq_funcs = अणु
	.set = dce_v8_0_set_hpd_पूर्णांकerrupt_state,
	.process = dce_v8_0_hpd_irq,
पूर्ण;

अटल व्योम dce_v8_0_set_irq_funcs(काष्ठा amdgpu_device *adev)
अणु
	अगर (adev->mode_info.num_crtc > 0)
		adev->crtc_irq.num_types = AMDGPU_CRTC_IRQ_VLINE1 + adev->mode_info.num_crtc;
	अन्यथा
		adev->crtc_irq.num_types = 0;
	adev->crtc_irq.funcs = &dce_v8_0_crtc_irq_funcs;

	adev->pageflip_irq.num_types = adev->mode_info.num_crtc;
	adev->pageflip_irq.funcs = &dce_v8_0_pageflip_irq_funcs;

	adev->hpd_irq.num_types = adev->mode_info.num_hpd;
	adev->hpd_irq.funcs = &dce_v8_0_hpd_irq_funcs;
पूर्ण

स्थिर काष्ठा amdgpu_ip_block_version dce_v8_0_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_DCE,
	.major = 8,
	.minor = 0,
	.rev = 0,
	.funcs = &dce_v8_0_ip_funcs,
पूर्ण;

स्थिर काष्ठा amdgpu_ip_block_version dce_v8_1_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_DCE,
	.major = 8,
	.minor = 1,
	.rev = 0,
	.funcs = &dce_v8_0_ip_funcs,
पूर्ण;

स्थिर काष्ठा amdgpu_ip_block_version dce_v8_2_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_DCE,
	.major = 8,
	.minor = 2,
	.rev = 0,
	.funcs = &dce_v8_0_ip_funcs,
पूर्ण;

स्थिर काष्ठा amdgpu_ip_block_version dce_v8_3_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_DCE,
	.major = 8,
	.minor = 3,
	.rev = 0,
	.funcs = &dce_v8_0_ip_funcs,
पूर्ण;

स्थिर काष्ठा amdgpu_ip_block_version dce_v8_5_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_DCE,
	.major = 8,
	.minor = 5,
	.rev = 0,
	.funcs = &dce_v8_0_ip_funcs,
पूर्ण;
