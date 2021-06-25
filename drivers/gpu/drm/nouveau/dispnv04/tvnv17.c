<शैली गुरु>
/*
 * Copyright (C) 2009 Francisco Jerez.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining
 * a copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE COPYRIGHT OWNER(S) AND/OR ITS SUPPLIERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश "nouveau_drv.h"
#समावेश "nouveau_reg.h"
#समावेश "nouveau_encoder.h"
#समावेश "nouveau_connector.h"
#समावेश "nouveau_crtc.h"
#समावेश "hw.h"
#समावेश "tvnv17.h"

MODULE_PARM_DESC(tv_norm, "Default TV norm.\n"
		 "\t\tSupported: PAL, PAL-M, PAL-N, PAL-Nc, NTSC-M, NTSC-J,\n"
		 "\t\t\thd480i, hd480p, hd576i, hd576p, hd720p, hd1080i.\n"
		 "\t\tDefault: PAL\n"
		 "\t\t*NOTE* Ignored for cards with external TV encoders.");
अटल अक्षर *nouveau_tv_norm;
module_param_named(tv_norm, nouveau_tv_norm, अक्षरp, 0400);

अटल uपूर्णांक32_t nv42_tv_sample_load(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvkm_gpio *gpio = nvxx_gpio(&drm->client.device);
	uपूर्णांक32_t testval, regoffset = nv04_dac_output_offset(encoder);
	uपूर्णांक32_t gpio0, gpio1, fp_htotal, fp_hsync_start, fp_hsync_end,
		fp_control, test_ctrl, dacclk, ctv_14, ctv_1c, ctv_6c;
	uपूर्णांक32_t sample = 0;
	पूर्णांक head;

#घोषणा RGB_TEST_DATA(r, g, b) (r << 0 | g << 10 | b << 20)
	testval = RGB_TEST_DATA(0x82, 0xeb, 0x82);
	अगर (drm->vbios.tvdactestval)
		testval = drm->vbios.tvdactestval;

	dacclk = NVReadRAMDAC(dev, 0, NV_PRAMDAC_DACCLK + regoffset);
	head = (dacclk & 0x100) >> 8;

	/* Save the previous state. */
	gpio1 = nvkm_gpio_get(gpio, 0, DCB_GPIO_TVDAC1, 0xff);
	gpio0 = nvkm_gpio_get(gpio, 0, DCB_GPIO_TVDAC0, 0xff);
	fp_htotal = NVReadRAMDAC(dev, head, NV_PRAMDAC_FP_HTOTAL);
	fp_hsync_start = NVReadRAMDAC(dev, head, NV_PRAMDAC_FP_HSYNC_START);
	fp_hsync_end = NVReadRAMDAC(dev, head, NV_PRAMDAC_FP_HSYNC_END);
	fp_control = NVReadRAMDAC(dev, head, NV_PRAMDAC_FP_TG_CONTROL);
	test_ctrl = NVReadRAMDAC(dev, 0, NV_PRAMDAC_TEST_CONTROL + regoffset);
	ctv_1c = NVReadRAMDAC(dev, head, 0x680c1c);
	ctv_14 = NVReadRAMDAC(dev, head, 0x680c14);
	ctv_6c = NVReadRAMDAC(dev, head, 0x680c6c);

	/* Prepare the DAC क्रम load detection.  */
	nvkm_gpio_set(gpio, 0, DCB_GPIO_TVDAC1, 0xff, true);
	nvkm_gpio_set(gpio, 0, DCB_GPIO_TVDAC0, 0xff, true);

	NVWriteRAMDAC(dev, head, NV_PRAMDAC_FP_HTOTAL, 1343);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_FP_HSYNC_START, 1047);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_FP_HSYNC_END, 1183);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_FP_TG_CONTROL,
		      NV_PRAMDAC_FP_TG_CONTROL_DISPEN_POS |
		      NV_PRAMDAC_FP_TG_CONTROL_WIDTH_12 |
		      NV_PRAMDAC_FP_TG_CONTROL_READ_PROG |
		      NV_PRAMDAC_FP_TG_CONTROL_HSYNC_POS |
		      NV_PRAMDAC_FP_TG_CONTROL_VSYNC_POS);

	NVWriteRAMDAC(dev, 0, NV_PRAMDAC_TEST_CONTROL + regoffset, 0);

	NVWriteRAMDAC(dev, 0, NV_PRAMDAC_DACCLK + regoffset,
		      (dacclk & ~0xff) | 0x22);
	msleep(1);
	NVWriteRAMDAC(dev, 0, NV_PRAMDAC_DACCLK + regoffset,
		      (dacclk & ~0xff) | 0x21);

	NVWriteRAMDAC(dev, head, 0x680c1c, 1 << 20);
	NVWriteRAMDAC(dev, head, 0x680c14, 4 << 16);

	/* Sample pin 0x4 (usually S-video luma). */
	NVWriteRAMDAC(dev, head, 0x680c6c, testval >> 10 & 0x3ff);
	msleep(20);
	sample |= NVReadRAMDAC(dev, 0, NV_PRAMDAC_TEST_CONTROL + regoffset)
		& 0x4 << 28;

	/* Sample the reमुख्यing pins. */
	NVWriteRAMDAC(dev, head, 0x680c6c, testval & 0x3ff);
	msleep(20);
	sample |= NVReadRAMDAC(dev, 0, NV_PRAMDAC_TEST_CONTROL + regoffset)
		& 0xa << 28;

	/* Restore the previous state. */
	NVWriteRAMDAC(dev, head, 0x680c1c, ctv_1c);
	NVWriteRAMDAC(dev, head, 0x680c14, ctv_14);
	NVWriteRAMDAC(dev, head, 0x680c6c, ctv_6c);
	NVWriteRAMDAC(dev, 0, NV_PRAMDAC_DACCLK + regoffset, dacclk);
	NVWriteRAMDAC(dev, 0, NV_PRAMDAC_TEST_CONTROL + regoffset, test_ctrl);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_FP_TG_CONTROL, fp_control);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_FP_HSYNC_END, fp_hsync_end);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_FP_HSYNC_START, fp_hsync_start);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_FP_HTOTAL, fp_htotal);
	nvkm_gpio_set(gpio, 0, DCB_GPIO_TVDAC1, 0xff, gpio1);
	nvkm_gpio_set(gpio, 0, DCB_GPIO_TVDAC0, 0xff, gpio0);

	वापस sample;
पूर्ण

अटल bool
get_tv_detect_quirks(काष्ठा drm_device *dev, uपूर्णांक32_t *pin_mask)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvkm_device *device = nvxx_device(&drm->client.device);

	अगर (device->quirk && device->quirk->tv_pin_mask) अणु
		*pin_mask = device->quirk->tv_pin_mask;
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल क्रमागत drm_connector_status
nv17_tv_detect(काष्ठा drm_encoder *encoder, काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा drm_mode_config *conf = &dev->mode_config;
	काष्ठा nv17_tv_encoder *tv_enc = to_tv_enc(encoder);
	काष्ठा dcb_output *dcb = tv_enc->base.dcb;
	bool reliable = get_tv_detect_quirks(dev, &tv_enc->pin_mask);

	अगर (nv04_dac_in_use(encoder))
		वापस connector_status_disconnected;

	अगर (reliable) अणु
		अगर (drm->client.device.info.chipset == 0x42 ||
		    drm->client.device.info.chipset == 0x43)
			tv_enc->pin_mask =
				nv42_tv_sample_load(encoder) >> 28 & 0xe;
		अन्यथा
			tv_enc->pin_mask =
				nv17_dac_sample_load(encoder) >> 28 & 0xe;
	पूर्ण

	चयन (tv_enc->pin_mask) अणु
	हाल 0x2:
	हाल 0x4:
		tv_enc->subconnector = DRM_MODE_SUBCONNECTOR_Composite;
		अवरोध;
	हाल 0xc:
		tv_enc->subconnector = DRM_MODE_SUBCONNECTOR_SVIDEO;
		अवरोध;
	हाल 0xe:
		अगर (dcb->tvconf.has_component_output)
			tv_enc->subconnector = DRM_MODE_SUBCONNECTOR_Component;
		अन्यथा
			tv_enc->subconnector = DRM_MODE_SUBCONNECTOR_SCART;
		अवरोध;
	शेष:
		tv_enc->subconnector = DRM_MODE_SUBCONNECTOR_Unknown;
		अवरोध;
	पूर्ण

	drm_object_property_set_value(&connector->base,
					 conf->tv_subconnector_property,
					 tv_enc->subconnector);

	अगर (!reliable) अणु
		वापस connector_status_unknown;
	पूर्ण अन्यथा अगर (tv_enc->subconnector) अणु
		NV_INFO(drm, "Load detected on output %c\n",
			'@' + ffs(dcb->or));
		वापस connector_status_connected;
	पूर्ण अन्यथा अणु
		वापस connector_status_disconnected;
	पूर्ण
पूर्ण

अटल पूर्णांक nv17_tv_get_ld_modes(काष्ठा drm_encoder *encoder,
				काष्ठा drm_connector *connector)
अणु
	काष्ठा nv17_tv_norm_params *tv_norm = get_tv_norm(encoder);
	स्थिर काष्ठा drm_display_mode *tv_mode;
	पूर्णांक n = 0;

	क्रम (tv_mode = nv17_tv_modes; tv_mode->hdisplay; tv_mode++) अणु
		काष्ठा drm_display_mode *mode;

		mode = drm_mode_duplicate(encoder->dev, tv_mode);

		mode->घड़ी = tv_norm->tv_enc_mode.vrefresh *
			mode->htotal / 1000 *
			mode->vtotal / 1000;

		अगर (mode->flags & DRM_MODE_FLAG_DBLSCAN)
			mode->घड़ी *= 2;

		अगर (mode->hdisplay == tv_norm->tv_enc_mode.hdisplay &&
		    mode->vdisplay == tv_norm->tv_enc_mode.vdisplay)
			mode->type |= DRM_MODE_TYPE_PREFERRED;

		drm_mode_probed_add(connector, mode);
		n++;
	पूर्ण

	वापस n;
पूर्ण

अटल पूर्णांक nv17_tv_get_hd_modes(काष्ठा drm_encoder *encoder,
				काष्ठा drm_connector *connector)
अणु
	काष्ठा nv17_tv_norm_params *tv_norm = get_tv_norm(encoder);
	काष्ठा drm_display_mode *output_mode = &tv_norm->ctv_enc_mode.mode;
	काष्ठा drm_display_mode *mode;
	स्थिर काष्ठा अणु
		पूर्णांक hdisplay;
		पूर्णांक vdisplay;
	पूर्ण modes[] = अणु
		अणु 640, 400 पूर्ण,
		अणु 640, 480 पूर्ण,
		अणु 720, 480 पूर्ण,
		अणु 720, 576 पूर्ण,
		अणु 800, 600 पूर्ण,
		अणु 1024, 768 पूर्ण,
		अणु 1280, 720 पूर्ण,
		अणु 1280, 1024 पूर्ण,
		अणु 1920, 1080 पूर्ण
	पूर्ण;
	पूर्णांक i, n = 0;

	क्रम (i = 0; i < ARRAY_SIZE(modes); i++) अणु
		अगर (modes[i].hdisplay > output_mode->hdisplay ||
		    modes[i].vdisplay > output_mode->vdisplay)
			जारी;

		अगर (modes[i].hdisplay == output_mode->hdisplay &&
		    modes[i].vdisplay == output_mode->vdisplay) अणु
			mode = drm_mode_duplicate(encoder->dev, output_mode);
			mode->type |= DRM_MODE_TYPE_PREFERRED;

		पूर्ण अन्यथा अणु
			mode = drm_cvt_mode(encoder->dev, modes[i].hdisplay,
					    modes[i].vdisplay, 60, false,
					    (output_mode->flags &
					     DRM_MODE_FLAG_INTERLACE), false);
		पूर्ण

		/* CVT modes are someबार unsuitable... */
		अगर (output_mode->hdisplay <= 720
		    || output_mode->hdisplay >= 1920) अणु
			mode->htotal = output_mode->htotal;
			mode->hsync_start = (mode->hdisplay + (mode->htotal
					     - mode->hdisplay) * 9 / 10) & ~7;
			mode->hsync_end = mode->hsync_start + 8;
		पूर्ण

		अगर (output_mode->vdisplay >= 1024) अणु
			mode->vtotal = output_mode->vtotal;
			mode->vsync_start = output_mode->vsync_start;
			mode->vsync_end = output_mode->vsync_end;
		पूर्ण

		mode->type |= DRM_MODE_TYPE_DRIVER;
		drm_mode_probed_add(connector, mode);
		n++;
	पूर्ण

	वापस n;
पूर्ण

अटल पूर्णांक nv17_tv_get_modes(काष्ठा drm_encoder *encoder,
			     काष्ठा drm_connector *connector)
अणु
	काष्ठा nv17_tv_norm_params *tv_norm = get_tv_norm(encoder);

	अगर (tv_norm->kind == CTV_ENC_MODE)
		वापस nv17_tv_get_hd_modes(encoder, connector);
	अन्यथा
		वापस nv17_tv_get_ld_modes(encoder, connector);
पूर्ण

अटल पूर्णांक nv17_tv_mode_valid(काष्ठा drm_encoder *encoder,
			      काष्ठा drm_display_mode *mode)
अणु
	काष्ठा nv17_tv_norm_params *tv_norm = get_tv_norm(encoder);

	अगर (tv_norm->kind == CTV_ENC_MODE) अणु
		काष्ठा drm_display_mode *output_mode =
						&tv_norm->ctv_enc_mode.mode;

		अगर (mode->घड़ी > 400000)
			वापस MODE_CLOCK_HIGH;

		अगर (mode->hdisplay > output_mode->hdisplay ||
		    mode->vdisplay > output_mode->vdisplay)
			वापस MODE_BAD;

		अगर ((mode->flags & DRM_MODE_FLAG_INTERLACE) !=
		    (output_mode->flags & DRM_MODE_FLAG_INTERLACE))
			वापस MODE_NO_INTERLACE;

		अगर (mode->flags & DRM_MODE_FLAG_DBLSCAN)
			वापस MODE_NO_DBLESCAN;

	पूर्ण अन्यथा अणु
		स्थिर पूर्णांक vsync_tolerance = 600;

		अगर (mode->घड़ी > 70000)
			वापस MODE_CLOCK_HIGH;

		अगर (असल(drm_mode_vrefresh(mode) * 1000 -
			tv_norm->tv_enc_mode.vrefresh) > vsync_tolerance)
			वापस MODE_VSYNC;

		/* The encoder takes care of the actual पूर्णांकerlacing */
		अगर (mode->flags & DRM_MODE_FLAG_INTERLACE)
			वापस MODE_NO_INTERLACE;
	पूर्ण

	वापस MODE_OK;
पूर्ण

अटल bool nv17_tv_mode_fixup(काष्ठा drm_encoder *encoder,
			       स्थिर काष्ठा drm_display_mode *mode,
			       काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा nv17_tv_norm_params *tv_norm = get_tv_norm(encoder);

	अगर (nv04_dac_in_use(encoder))
		वापस false;

	अगर (tv_norm->kind == CTV_ENC_MODE)
		adjusted_mode->घड़ी = tv_norm->ctv_enc_mode.mode.घड़ी;
	अन्यथा
		adjusted_mode->घड़ी = 90000;

	वापस true;
पूर्ण

अटल व्योम  nv17_tv_dpms(काष्ठा drm_encoder *encoder, पूर्णांक mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvkm_gpio *gpio = nvxx_gpio(&drm->client.device);
	काष्ठा nv17_tv_state *regs = &to_tv_enc(encoder)->state;
	काष्ठा nv17_tv_norm_params *tv_norm = get_tv_norm(encoder);

	अगर (nouveau_encoder(encoder)->last_dpms == mode)
		वापस;
	nouveau_encoder(encoder)->last_dpms = mode;

	NV_INFO(drm, "Setting dpms mode %d on TV encoder (output %d)\n",
		 mode, nouveau_encoder(encoder)->dcb->index);

	regs->ptv_200 &= ~1;

	अगर (tv_norm->kind == CTV_ENC_MODE) अणु
		nv04_dfp_update_fp_control(encoder, mode);

	पूर्ण अन्यथा अणु
		nv04_dfp_update_fp_control(encoder, DRM_MODE_DPMS_OFF);

		अगर (mode == DRM_MODE_DPMS_ON)
			regs->ptv_200 |= 1;
	पूर्ण

	nv_load_ptv(dev, regs, 200);

	nvkm_gpio_set(gpio, 0, DCB_GPIO_TVDAC1, 0xff, mode == DRM_MODE_DPMS_ON);
	nvkm_gpio_set(gpio, 0, DCB_GPIO_TVDAC0, 0xff, mode == DRM_MODE_DPMS_ON);

	nv04_dac_update_dacclk(encoder, mode == DRM_MODE_DPMS_ON);
पूर्ण

अटल व्योम nv17_tv_prepare(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	स्थिर काष्ठा drm_encoder_helper_funcs *helper = encoder->helper_निजी;
	काष्ठा nv17_tv_norm_params *tv_norm = get_tv_norm(encoder);
	पूर्णांक head = nouveau_crtc(encoder->crtc)->index;
	uपूर्णांक8_t *cr_lcd = &nv04_display(dev)->mode_reg.crtc_reg[head].CRTC[
							NV_CIO_CRE_LCD__INDEX];
	uपूर्णांक32_t dacclk_off = NV_PRAMDAC_DACCLK +
					nv04_dac_output_offset(encoder);
	uपूर्णांक32_t dacclk;

	helper->dpms(encoder, DRM_MODE_DPMS_OFF);

	nv04_dfp_disable(dev, head);

	/* Unbind any FP encoders from this head अगर we need the FP
	 * stuff enabled. */
	अगर (tv_norm->kind == CTV_ENC_MODE) अणु
		काष्ठा drm_encoder *enc;

		list_क्रम_each_entry(enc, &dev->mode_config.encoder_list, head) अणु
			काष्ठा dcb_output *dcb = nouveau_encoder(enc)->dcb;

			अगर ((dcb->type == DCB_OUTPUT_TMDS ||
			     dcb->type == DCB_OUTPUT_LVDS) &&
			     !enc->crtc &&
			     nv04_dfp_get_bound_head(dev, dcb) == head) अणु
				nv04_dfp_bind_head(dev, dcb, head ^ 1,
						drm->vbios.fp.dual_link);
			पूर्ण
		पूर्ण

	पूर्ण

	अगर (tv_norm->kind == CTV_ENC_MODE)
		*cr_lcd |= 0x1 | (head ? 0x0 : 0x8);

	/* Set the DACCLK रेजिस्टर */
	dacclk = (NVReadRAMDAC(dev, 0, dacclk_off) & ~0x30) | 0x1;

	अगर (drm->client.device.info.family == NV_DEVICE_INFO_V0_CURIE)
		dacclk |= 0x1a << 16;

	अगर (tv_norm->kind == CTV_ENC_MODE) अणु
		dacclk |=  0x20;

		अगर (head)
			dacclk |= 0x100;
		अन्यथा
			dacclk &= ~0x100;

	पूर्ण अन्यथा अणु
		dacclk |= 0x10;

	पूर्ण

	NVWriteRAMDAC(dev, 0, dacclk_off, dacclk);
पूर्ण

अटल व्योम nv17_tv_mode_set(काष्ठा drm_encoder *encoder,
			     काष्ठा drm_display_mode *drm_mode,
			     काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	पूर्णांक head = nouveau_crtc(encoder->crtc)->index;
	काष्ठा nv04_crtc_reg *regs = &nv04_display(dev)->mode_reg.crtc_reg[head];
	काष्ठा nv17_tv_state *tv_regs = &to_tv_enc(encoder)->state;
	काष्ठा nv17_tv_norm_params *tv_norm = get_tv_norm(encoder);
	पूर्णांक i;

	regs->CRTC[NV_CIO_CRE_53] = 0x40; /* FP_HTIMING */
	regs->CRTC[NV_CIO_CRE_54] = 0; /* FP_VTIMING */
	regs->ramdac_630 = 0x2; /* turn off green mode (tv test pattern?) */
	regs->tv_setup = 1;
	regs->ramdac_8c0 = 0x0;

	अगर (tv_norm->kind == TV_ENC_MODE) अणु
		tv_regs->ptv_200 = 0x13111100;
		अगर (head)
			tv_regs->ptv_200 |= 0x10;

		tv_regs->ptv_20c = 0x808010;
		tv_regs->ptv_304 = 0x2d00000;
		tv_regs->ptv_600 = 0x0;
		tv_regs->ptv_60c = 0x0;
		tv_regs->ptv_610 = 0x1e00000;

		अगर (tv_norm->tv_enc_mode.vdisplay == 576) अणु
			tv_regs->ptv_508 = 0x1200000;
			tv_regs->ptv_614 = 0x33;

		पूर्ण अन्यथा अगर (tv_norm->tv_enc_mode.vdisplay == 480) अणु
			tv_regs->ptv_508 = 0xf00000;
			tv_regs->ptv_614 = 0x13;
		पूर्ण

		अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_RANKINE) अणु
			tv_regs->ptv_500 = 0xe8e0;
			tv_regs->ptv_504 = 0x1710;
			tv_regs->ptv_604 = 0x0;
			tv_regs->ptv_608 = 0x0;
		पूर्ण अन्यथा अणु
			अगर (tv_norm->tv_enc_mode.vdisplay == 576) अणु
				tv_regs->ptv_604 = 0x20;
				tv_regs->ptv_608 = 0x10;
				tv_regs->ptv_500 = 0x19710;
				tv_regs->ptv_504 = 0x68f0;

			पूर्ण अन्यथा अगर (tv_norm->tv_enc_mode.vdisplay == 480) अणु
				tv_regs->ptv_604 = 0x10;
				tv_regs->ptv_608 = 0x20;
				tv_regs->ptv_500 = 0x4b90;
				tv_regs->ptv_504 = 0x1b480;
			पूर्ण
		पूर्ण

		क्रम (i = 0; i < 0x40; i++)
			tv_regs->tv_enc[i] = tv_norm->tv_enc_mode.tv_enc[i];

	पूर्ण अन्यथा अणु
		काष्ठा drm_display_mode *output_mode =
						&tv_norm->ctv_enc_mode.mode;

		/* The रेजिस्टरs in PRAMDAC+0xc00 control some timings and CSC
		 * parameters क्रम the CTV encoder (It's only used क्रम "HD" TV
		 * modes, I करोn't think I have enough working to guess what
		 * they exactly mean...), it's probably connected at the
		 * output of the FP encoder, but it also needs the analog
		 * encoder in its OR enabled and routed to the head it's
		 * using. It's enabled with the DACCLK रेजिस्टर, bits [5:4].
		 */
		क्रम (i = 0; i < 38; i++)
			regs->ctv_regs[i] = tv_norm->ctv_enc_mode.ctv_regs[i];

		regs->fp_horiz_regs[FP_DISPLAY_END] = output_mode->hdisplay - 1;
		regs->fp_horiz_regs[FP_TOTAL] = output_mode->htotal - 1;
		regs->fp_horiz_regs[FP_SYNC_START] =
						output_mode->hsync_start - 1;
		regs->fp_horiz_regs[FP_SYNC_END] = output_mode->hsync_end - 1;
		regs->fp_horiz_regs[FP_CRTC] = output_mode->hdisplay +
			max((output_mode->hdisplay-600)/40 - 1, 1);

		regs->fp_vert_regs[FP_DISPLAY_END] = output_mode->vdisplay - 1;
		regs->fp_vert_regs[FP_TOTAL] = output_mode->vtotal - 1;
		regs->fp_vert_regs[FP_SYNC_START] =
						output_mode->vsync_start - 1;
		regs->fp_vert_regs[FP_SYNC_END] = output_mode->vsync_end - 1;
		regs->fp_vert_regs[FP_CRTC] = output_mode->vdisplay - 1;

		regs->fp_control = NV_PRAMDAC_FP_TG_CONTROL_DISPEN_POS |
			NV_PRAMDAC_FP_TG_CONTROL_READ_PROG |
			NV_PRAMDAC_FP_TG_CONTROL_WIDTH_12;

		अगर (output_mode->flags & DRM_MODE_FLAG_PVSYNC)
			regs->fp_control |= NV_PRAMDAC_FP_TG_CONTROL_VSYNC_POS;
		अगर (output_mode->flags & DRM_MODE_FLAG_PHSYNC)
			regs->fp_control |= NV_PRAMDAC_FP_TG_CONTROL_HSYNC_POS;

		regs->fp_debug_0 = NV_PRAMDAC_FP_DEBUG_0_YWEIGHT_ROUND |
			NV_PRAMDAC_FP_DEBUG_0_XWEIGHT_ROUND |
			NV_PRAMDAC_FP_DEBUG_0_YINTERP_BILINEAR |
			NV_PRAMDAC_FP_DEBUG_0_XINTERP_BILINEAR |
			NV_RAMDAC_FP_DEBUG_0_TMDS_ENABLED |
			NV_PRAMDAC_FP_DEBUG_0_YSCALE_ENABLE |
			NV_PRAMDAC_FP_DEBUG_0_XSCALE_ENABLE;

		regs->fp_debug_2 = 0;

		regs->fp_margin_color = 0x801080;

	पूर्ण
पूर्ण

अटल व्योम nv17_tv_commit(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nouveau_crtc *nv_crtc = nouveau_crtc(encoder->crtc);
	काष्ठा nouveau_encoder *nv_encoder = nouveau_encoder(encoder);
	स्थिर काष्ठा drm_encoder_helper_funcs *helper = encoder->helper_निजी;

	अगर (get_tv_norm(encoder)->kind == TV_ENC_MODE) अणु
		nv17_tv_update_rescaler(encoder);
		nv17_tv_update_properties(encoder);
	पूर्ण अन्यथा अणु
		nv17_ctv_update_rescaler(encoder);
	पूर्ण

	nv17_tv_state_load(dev, &to_tv_enc(encoder)->state);

	/* This could use refinement क्रम flatpanels, but it should work */
	अगर (drm->client.device.info.chipset < 0x44)
		NVWriteRAMDAC(dev, 0, NV_PRAMDAC_TEST_CONTROL +
					nv04_dac_output_offset(encoder),
					0xf0000000);
	अन्यथा
		NVWriteRAMDAC(dev, 0, NV_PRAMDAC_TEST_CONTROL +
					nv04_dac_output_offset(encoder),
					0x00100000);

	helper->dpms(encoder, DRM_MODE_DPMS_ON);

	NV_INFO(drm, "Output %s is running on CRTC %d using output %c\n",
		nv04_encoder_get_connector(nv_encoder)->base.name,
		nv_crtc->index, '@' + ffs(nv_encoder->dcb->or));
पूर्ण

अटल व्योम nv17_tv_save(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा nv17_tv_encoder *tv_enc = to_tv_enc(encoder);

	nouveau_encoder(encoder)->restore.output =
					NVReadRAMDAC(dev, 0,
					NV_PRAMDAC_DACCLK +
					nv04_dac_output_offset(encoder));

	nv17_tv_state_save(dev, &tv_enc->saved_state);

	tv_enc->state.ptv_200 = tv_enc->saved_state.ptv_200;
पूर्ण

अटल व्योम nv17_tv_restore(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;

	NVWriteRAMDAC(dev, 0, NV_PRAMDAC_DACCLK +
				nv04_dac_output_offset(encoder),
				nouveau_encoder(encoder)->restore.output);

	nv17_tv_state_load(dev, &to_tv_enc(encoder)->saved_state);

	nouveau_encoder(encoder)->last_dpms = NV_DPMS_CLEARED;
पूर्ण

अटल पूर्णांक nv17_tv_create_resources(काष्ठा drm_encoder *encoder,
				    काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा drm_mode_config *conf = &dev->mode_config;
	काष्ठा nv17_tv_encoder *tv_enc = to_tv_enc(encoder);
	काष्ठा dcb_output *dcb = nouveau_encoder(encoder)->dcb;
	पूर्णांक num_tv_norms = dcb->tvconf.has_component_output ? NUM_TV_NORMS :
							NUM_LD_TV_NORMS;
	पूर्णांक i;

	अगर (nouveau_tv_norm) अणु
		i = match_string(nv17_tv_norm_names, num_tv_norms,
				 nouveau_tv_norm);
		अगर (i < 0)
			NV_WARN(drm, "Invalid TV norm setting \"%s\"\n",
				nouveau_tv_norm);
		अन्यथा
			tv_enc->tv_norm = i;
	पूर्ण

	drm_mode_create_tv_properties(dev, num_tv_norms, nv17_tv_norm_names);

	drm_object_attach_property(&connector->base,
					conf->tv_select_subconnector_property,
					tv_enc->select_subconnector);
	drm_object_attach_property(&connector->base,
					conf->tv_subconnector_property,
					tv_enc->subconnector);
	drm_object_attach_property(&connector->base,
					conf->tv_mode_property,
					tv_enc->tv_norm);
	drm_object_attach_property(&connector->base,
					conf->tv_flicker_reduction_property,
					tv_enc->flicker);
	drm_object_attach_property(&connector->base,
					conf->tv_saturation_property,
					tv_enc->saturation);
	drm_object_attach_property(&connector->base,
					conf->tv_hue_property,
					tv_enc->hue);
	drm_object_attach_property(&connector->base,
					conf->tv_overscan_property,
					tv_enc->overscan);

	वापस 0;
पूर्ण

अटल पूर्णांक nv17_tv_set_property(काष्ठा drm_encoder *encoder,
				काष्ठा drm_connector *connector,
				काष्ठा drm_property *property,
				uपूर्णांक64_t val)
अणु
	काष्ठा drm_mode_config *conf = &encoder->dev->mode_config;
	काष्ठा drm_crtc *crtc = encoder->crtc;
	काष्ठा nv17_tv_encoder *tv_enc = to_tv_enc(encoder);
	काष्ठा nv17_tv_norm_params *tv_norm = get_tv_norm(encoder);
	bool modes_changed = false;

	अगर (property == conf->tv_overscan_property) अणु
		tv_enc->overscan = val;
		अगर (encoder->crtc) अणु
			अगर (tv_norm->kind == CTV_ENC_MODE)
				nv17_ctv_update_rescaler(encoder);
			अन्यथा
				nv17_tv_update_rescaler(encoder);
		पूर्ण

	पूर्ण अन्यथा अगर (property == conf->tv_saturation_property) अणु
		अगर (tv_norm->kind != TV_ENC_MODE)
			वापस -EINVAL;

		tv_enc->saturation = val;
		nv17_tv_update_properties(encoder);

	पूर्ण अन्यथा अगर (property == conf->tv_hue_property) अणु
		अगर (tv_norm->kind != TV_ENC_MODE)
			वापस -EINVAL;

		tv_enc->hue = val;
		nv17_tv_update_properties(encoder);

	पूर्ण अन्यथा अगर (property == conf->tv_flicker_reduction_property) अणु
		अगर (tv_norm->kind != TV_ENC_MODE)
			वापस -EINVAL;

		tv_enc->flicker = val;
		अगर (encoder->crtc)
			nv17_tv_update_rescaler(encoder);

	पूर्ण अन्यथा अगर (property == conf->tv_mode_property) अणु
		अगर (connector->dpms != DRM_MODE_DPMS_OFF)
			वापस -EINVAL;

		tv_enc->tv_norm = val;

		modes_changed = true;

	पूर्ण अन्यथा अगर (property == conf->tv_select_subconnector_property) अणु
		अगर (tv_norm->kind != TV_ENC_MODE)
			वापस -EINVAL;

		tv_enc->select_subconnector = val;
		nv17_tv_update_properties(encoder);

	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	अगर (modes_changed) अणु
		drm_helper_probe_single_connector_modes(connector, 0, 0);

		/* Disable the crtc to ensure a full modeset is
		 * perक्रमmed whenever it's turned on again. */
		अगर (crtc)
			drm_crtc_helper_set_mode(crtc, &crtc->mode,
						 crtc->x, crtc->y,
						 crtc->primary->fb);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम nv17_tv_destroy(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा nv17_tv_encoder *tv_enc = to_tv_enc(encoder);

	drm_encoder_cleanup(encoder);
	kमुक्त(tv_enc);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs nv17_tv_helper_funcs = अणु
	.dpms = nv17_tv_dpms,
	.mode_fixup = nv17_tv_mode_fixup,
	.prepare = nv17_tv_prepare,
	.commit = nv17_tv_commit,
	.mode_set = nv17_tv_mode_set,
	.detect = nv17_tv_detect,
पूर्ण;

अटल स्थिर काष्ठा drm_encoder_slave_funcs nv17_tv_slave_funcs = अणु
	.get_modes = nv17_tv_get_modes,
	.mode_valid = nv17_tv_mode_valid,
	.create_resources = nv17_tv_create_resources,
	.set_property = nv17_tv_set_property,
पूर्ण;

अटल स्थिर काष्ठा drm_encoder_funcs nv17_tv_funcs = अणु
	.destroy = nv17_tv_destroy,
पूर्ण;

पूर्णांक
nv17_tv_create(काष्ठा drm_connector *connector, काष्ठा dcb_output *entry)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_encoder *encoder;
	काष्ठा nv17_tv_encoder *tv_enc = शून्य;

	tv_enc = kzalloc(माप(*tv_enc), GFP_KERNEL);
	अगर (!tv_enc)
		वापस -ENOMEM;

	tv_enc->overscan = 50;
	tv_enc->flicker = 50;
	tv_enc->saturation = 50;
	tv_enc->hue = 0;
	tv_enc->tv_norm = TV_NORM_PAL;
	tv_enc->subconnector = DRM_MODE_SUBCONNECTOR_Unknown;
	tv_enc->select_subconnector = DRM_MODE_SUBCONNECTOR_Automatic;
	tv_enc->pin_mask = 0;

	encoder = to_drm_encoder(&tv_enc->base);

	tv_enc->base.dcb = entry;
	tv_enc->base.or = ffs(entry->or) - 1;

	drm_encoder_init(dev, encoder, &nv17_tv_funcs, DRM_MODE_ENCODER_TVDAC,
			 शून्य);
	drm_encoder_helper_add(encoder, &nv17_tv_helper_funcs);
	to_encoder_slave(encoder)->slave_funcs = &nv17_tv_slave_funcs;

	tv_enc->base.enc_save = nv17_tv_save;
	tv_enc->base.enc_restore = nv17_tv_restore;

	encoder->possible_crtcs = entry->heads;
	encoder->possible_clones = 0;

	nv17_tv_create_resources(encoder, connector);
	drm_connector_attach_encoder(connector, encoder);
	वापस 0;
पूर्ण
