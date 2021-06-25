<शैली गुरु>
/*
 * Copyright तऊ 2006-2007 Intel Corporation
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
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *	Eric Anholt <eric@anholt.net>
 */

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "cdv_device.h"
#समावेश "intel_bios.h"
#समावेश "power.h"
#समावेश "psb_drv.h"
#समावेश "psb_intel_drv.h"
#समावेश "psb_intel_reg.h"


अटल व्योम cdv_पूर्णांकel_crt_dpms(काष्ठा drm_encoder *encoder, पूर्णांक mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	u32 temp, reg;
	reg = ADPA;

	temp = REG_READ(reg);
	temp &= ~(ADPA_HSYNC_CNTL_DISABLE | ADPA_VSYNC_CNTL_DISABLE);
	temp &= ~ADPA_DAC_ENABLE;

	चयन (mode) अणु
	हाल DRM_MODE_DPMS_ON:
		temp |= ADPA_DAC_ENABLE;
		अवरोध;
	हाल DRM_MODE_DPMS_STANDBY:
		temp |= ADPA_DAC_ENABLE | ADPA_HSYNC_CNTL_DISABLE;
		अवरोध;
	हाल DRM_MODE_DPMS_SUSPEND:
		temp |= ADPA_DAC_ENABLE | ADPA_VSYNC_CNTL_DISABLE;
		अवरोध;
	हाल DRM_MODE_DPMS_OFF:
		temp |= ADPA_HSYNC_CNTL_DISABLE | ADPA_VSYNC_CNTL_DISABLE;
		अवरोध;
	पूर्ण

	REG_WRITE(reg, temp);
पूर्ण

अटल क्रमागत drm_mode_status cdv_पूर्णांकel_crt_mode_valid(काष्ठा drm_connector *connector,
				काष्ठा drm_display_mode *mode)
अणु
	अगर (mode->flags & DRM_MODE_FLAG_DBLSCAN)
		वापस MODE_NO_DBLESCAN;

	/* The lowest घड़ी क्रम CDV is 20000KHz */
	अगर (mode->घड़ी < 20000)
		वापस MODE_CLOCK_LOW;

	/* The max घड़ी क्रम CDV is 355 instead of 400 */
	अगर (mode->घड़ी > 355000)
		वापस MODE_CLOCK_HIGH;

	वापस MODE_OK;
पूर्ण

अटल व्योम cdv_पूर्णांकel_crt_mode_set(काष्ठा drm_encoder *encoder,
			       काष्ठा drm_display_mode *mode,
			       काष्ठा drm_display_mode *adjusted_mode)
अणु

	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा drm_crtc *crtc = encoder->crtc;
	काष्ठा gma_crtc *gma_crtc = to_gma_crtc(crtc);
	पूर्णांक dpll_md_reg;
	u32 adpa, dpll_md;
	u32 adpa_reg;

	अगर (gma_crtc->pipe == 0)
		dpll_md_reg = DPLL_A_MD;
	अन्यथा
		dpll_md_reg = DPLL_B_MD;

	adpa_reg = ADPA;

	/*
	 * Disable separate mode multiplier used when cloning SDVO to CRT
	 * XXX this needs to be adjusted when we really are cloning
	 */
	अणु
		dpll_md = REG_READ(dpll_md_reg);
		REG_WRITE(dpll_md_reg,
			   dpll_md & ~DPLL_MD_UDI_MULTIPLIER_MASK);
	पूर्ण

	adpa = 0;
	अगर (adjusted_mode->flags & DRM_MODE_FLAG_PHSYNC)
		adpa |= ADPA_HSYNC_ACTIVE_HIGH;
	अगर (adjusted_mode->flags & DRM_MODE_FLAG_PVSYNC)
		adpa |= ADPA_VSYNC_ACTIVE_HIGH;

	अगर (gma_crtc->pipe == 0)
		adpa |= ADPA_PIPE_A_SELECT;
	अन्यथा
		adpa |= ADPA_PIPE_B_SELECT;

	REG_WRITE(adpa_reg, adpa);
पूर्ण


/*
 * Uses CRT_HOTPLUG_EN and CRT_HOTPLUG_STAT to detect CRT presence.
 *
 * \लeturn true अगर CRT is connected.
 * \लeturn false अगर CRT is disconnected.
 */
अटल bool cdv_पूर्णांकel_crt_detect_hotplug(काष्ठा drm_connector *connector,
								bool क्रमce)
अणु
	काष्ठा drm_device *dev = connector->dev;
	u32 hotplug_en;
	पूर्णांक i, tries = 0, ret = false;
	u32 orig;

	/*
	 * On a CDV thep, CRT detect sequence need to be करोne twice
	 * to get a reliable result.
	 */
	tries = 2;

	orig = hotplug_en = REG_READ(PORT_HOTPLUG_EN);
	hotplug_en &= ~(CRT_HOTPLUG_DETECT_MASK);
	hotplug_en |= CRT_HOTPLUG_FORCE_DETECT;

	hotplug_en |= CRT_HOTPLUG_ACTIVATION_PERIOD_64;
	hotplug_en |= CRT_HOTPLUG_VOLTAGE_COMPARE_50;

	क्रम (i = 0; i < tries ; i++) अणु
		अचिन्हित दीर्घ समयout;
		/* turn on the FORCE_DETECT */
		REG_WRITE(PORT_HOTPLUG_EN, hotplug_en);
		समयout = jअगरfies + msecs_to_jअगरfies(1000);
		/* रुको क्रम FORCE_DETECT to go off */
		करो अणु
			अगर (!(REG_READ(PORT_HOTPLUG_EN) &
					CRT_HOTPLUG_FORCE_DETECT))
				अवरोध;
			msleep(1);
		पूर्ण जबतक (समय_after(समयout, jअगरfies));
	पूर्ण

	अगर ((REG_READ(PORT_HOTPLUG_STAT) & CRT_HOTPLUG_MONITOR_MASK) !=
	    CRT_HOTPLUG_MONITOR_NONE)
		ret = true;

	 /* clear the पूर्णांकerrupt we just generated, अगर any */
	REG_WRITE(PORT_HOTPLUG_STAT, CRT_HOTPLUG_INT_STATUS);

	/* and put the bits back */
	REG_WRITE(PORT_HOTPLUG_EN, orig);
	वापस ret;
पूर्ण

अटल क्रमागत drm_connector_status cdv_पूर्णांकel_crt_detect(
				काष्ठा drm_connector *connector, bool क्रमce)
अणु
	अगर (cdv_पूर्णांकel_crt_detect_hotplug(connector, क्रमce))
		वापस connector_status_connected;
	अन्यथा
		वापस connector_status_disconnected;
पूर्ण

अटल व्योम cdv_पूर्णांकel_crt_destroy(काष्ठा drm_connector *connector)
अणु
	काष्ठा gma_encoder *gma_encoder = gma_attached_encoder(connector);

	psb_पूर्णांकel_i2c_destroy(gma_encoder->ddc_bus);
	drm_connector_unरेजिस्टर(connector);
	drm_connector_cleanup(connector);
	kमुक्त(connector);
पूर्ण

अटल पूर्णांक cdv_पूर्णांकel_crt_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा gma_encoder *gma_encoder = gma_attached_encoder(connector);
	वापस psb_पूर्णांकel_ddc_get_modes(connector,
				       &gma_encoder->ddc_bus->adapter);
पूर्ण

अटल पूर्णांक cdv_पूर्णांकel_crt_set_property(काष्ठा drm_connector *connector,
				  काष्ठा drm_property *property,
				  uपूर्णांक64_t value)
अणु
	वापस 0;
पूर्ण

/*
 * Routines क्रम controlling stuff on the analog port
 */

अटल स्थिर काष्ठा drm_encoder_helper_funcs cdv_पूर्णांकel_crt_helper_funcs = अणु
	.dpms = cdv_पूर्णांकel_crt_dpms,
	.prepare = gma_encoder_prepare,
	.commit = gma_encoder_commit,
	.mode_set = cdv_पूर्णांकel_crt_mode_set,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs cdv_पूर्णांकel_crt_connector_funcs = अणु
	.dpms = drm_helper_connector_dpms,
	.detect = cdv_पूर्णांकel_crt_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = cdv_पूर्णांकel_crt_destroy,
	.set_property = cdv_पूर्णांकel_crt_set_property,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_helper_funcs
				cdv_पूर्णांकel_crt_connector_helper_funcs = अणु
	.mode_valid = cdv_पूर्णांकel_crt_mode_valid,
	.get_modes = cdv_पूर्णांकel_crt_get_modes,
	.best_encoder = gma_best_encoder,
पूर्ण;

व्योम cdv_पूर्णांकel_crt_init(काष्ठा drm_device *dev,
			काष्ठा psb_पूर्णांकel_mode_device *mode_dev)
अणु

	काष्ठा gma_connector *gma_connector;
	काष्ठा gma_encoder *gma_encoder;
	काष्ठा drm_connector *connector;
	काष्ठा drm_encoder *encoder;

	gma_encoder = kzalloc(माप(काष्ठा gma_encoder), GFP_KERNEL);
	अगर (!gma_encoder)
		वापस;

	gma_connector = kzalloc(माप(काष्ठा gma_connector), GFP_KERNEL);
	अगर (!gma_connector)
		जाओ failed_connector;

	connector = &gma_connector->base;
	connector->polled = DRM_CONNECTOR_POLL_HPD;
	drm_connector_init(dev, connector,
		&cdv_पूर्णांकel_crt_connector_funcs, DRM_MODE_CONNECTOR_VGA);

	encoder = &gma_encoder->base;
	drm_simple_encoder_init(dev, encoder, DRM_MODE_ENCODER_DAC);

	gma_connector_attach_encoder(gma_connector, gma_encoder);

	/* Set up the DDC bus. */
	gma_encoder->ddc_bus = psb_पूर्णांकel_i2c_create(dev, GPIOA, "CRTDDC_A");
	अगर (!gma_encoder->ddc_bus) अणु
		dev_prपूर्णांकk(KERN_ERR, dev->dev, "DDC bus registration failed.\n");
		जाओ failed_ddc;
	पूर्ण

	gma_encoder->type = INTEL_OUTPUT_ANALOG;
	connector->पूर्णांकerlace_allowed = 0;
	connector->द्विगुनscan_allowed = 0;

	drm_encoder_helper_add(encoder, &cdv_पूर्णांकel_crt_helper_funcs);
	drm_connector_helper_add(connector,
					&cdv_पूर्णांकel_crt_connector_helper_funcs);

	drm_connector_रेजिस्टर(connector);

	वापस;
failed_ddc:
	drm_encoder_cleanup(&gma_encoder->base);
	drm_connector_cleanup(&gma_connector->base);
	kमुक्त(gma_connector);
failed_connector:
	kमुक्त(gma_encoder);
	वापस;
पूर्ण
