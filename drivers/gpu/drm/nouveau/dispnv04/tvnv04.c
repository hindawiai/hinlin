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

#समावेश "nouveau_drv.h"
#समावेश "nouveau_reg.h"
#समावेश "nouveau_encoder.h"
#समावेश "nouveau_connector.h"
#समावेश "nouveau_crtc.h"
#समावेश "hw.h"
#समावेश <drm/drm_crtc_helper.h>

#समावेश <drm/i2c/ch7006.h>

अटल काष्ठा nvkm_i2c_bus_probe nv04_tv_encoder_info[] = अणु
	अणु
		अणु
			I2C_BOARD_INFO("ch7006", 0x75),
			.platक्रमm_data = &(काष्ठा ch7006_encoder_params) अणु
				CH7006_FORMAT_RGB24m12I, CH7006_CLOCK_MASTER,
				0, 0, 0,
				CH7006_SYNC_SLAVE, CH7006_SYNC_SEPARATED,
				CH7006_POUT_3_3V, CH7006_ACTIVE_HSYNC
			पूर्ण
		पूर्ण,
		0
	पूर्ण,
	अणु पूर्ण
पूर्ण;

पूर्णांक nv04_tv_identअगरy(काष्ठा drm_device *dev, पूर्णांक i2c_index)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvkm_i2c *i2c = nvxx_i2c(&drm->client.device);
	काष्ठा nvkm_i2c_bus *bus = nvkm_i2c_bus_find(i2c, i2c_index);
	अगर (bus) अणु
		वापस nvkm_i2c_bus_probe(bus, "TV encoder",
					  nv04_tv_encoder_info,
					  शून्य, शून्य);
	पूर्ण
	वापस -ENODEV;
पूर्ण


#घोषणा PLLSEL_TV_CRTC1_MASK				\
	(NV_PRAMDAC_PLL_COEFF_SELECT_TV_VSCLK1		\
	 | NV_PRAMDAC_PLL_COEFF_SELECT_TV_PCLK1)
#घोषणा PLLSEL_TV_CRTC2_MASK				\
	(NV_PRAMDAC_PLL_COEFF_SELECT_TV_VSCLK2		\
	 | NV_PRAMDAC_PLL_COEFF_SELECT_TV_PCLK2)

अटल व्योम nv04_tv_dpms(काष्ठा drm_encoder *encoder, पूर्णांक mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nouveau_encoder *nv_encoder = nouveau_encoder(encoder);
	काष्ठा nv04_mode_state *state = &nv04_display(dev)->mode_reg;
	uपूर्णांक8_t crtc1A;

	NV_DEBUG(drm, "Setting dpms mode %d on TV encoder (output %d)\n",
		 mode, nv_encoder->dcb->index);

	state->pllsel &= ~(PLLSEL_TV_CRTC1_MASK | PLLSEL_TV_CRTC2_MASK);

	अगर (mode == DRM_MODE_DPMS_ON) अणु
		पूर्णांक head = nouveau_crtc(encoder->crtc)->index;
		crtc1A = NVReadVgaCrtc(dev, head, NV_CIO_CRE_RPC1_INDEX);

		state->pllsel |= head ? PLLSEL_TV_CRTC2_MASK :
					PLLSEL_TV_CRTC1_MASK;

		/* Inhibit hsync */
		crtc1A |= 0x80;

		NVWriteVgaCrtc(dev, head, NV_CIO_CRE_RPC1_INDEX, crtc1A);
	पूर्ण

	NVWriteRAMDAC(dev, 0, NV_PRAMDAC_PLL_COEFF_SELECT, state->pllsel);

	get_slave_funcs(encoder)->dpms(encoder, mode);
पूर्ण

अटल व्योम nv04_tv_bind(काष्ठा drm_device *dev, पूर्णांक head, bool bind)
अणु
	काष्ठा nv04_crtc_reg *state = &nv04_display(dev)->mode_reg.crtc_reg[head];

	state->tv_setup = 0;

	अगर (bind)
		state->CRTC[NV_CIO_CRE_49] |= 0x10;
	अन्यथा
		state->CRTC[NV_CIO_CRE_49] &= ~0x10;

	NVWriteVgaCrtc(dev, head, NV_CIO_CRE_LCD__INDEX,
		       state->CRTC[NV_CIO_CRE_LCD__INDEX]);
	NVWriteVgaCrtc(dev, head, NV_CIO_CRE_49,
		       state->CRTC[NV_CIO_CRE_49]);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_TV_SETUP,
		      state->tv_setup);
पूर्ण

अटल व्योम nv04_tv_prepare(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	पूर्णांक head = nouveau_crtc(encoder->crtc)->index;
	स्थिर काष्ठा drm_encoder_helper_funcs *helper = encoder->helper_निजी;

	helper->dpms(encoder, DRM_MODE_DPMS_OFF);

	nv04_dfp_disable(dev, head);

	अगर (nv_two_heads(dev))
		nv04_tv_bind(dev, head ^ 1, false);

	nv04_tv_bind(dev, head, true);
पूर्ण

अटल व्योम nv04_tv_mode_set(काष्ठा drm_encoder *encoder,
			     काष्ठा drm_display_mode *mode,
			     काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा nouveau_crtc *nv_crtc = nouveau_crtc(encoder->crtc);
	काष्ठा nv04_crtc_reg *regp = &nv04_display(dev)->mode_reg.crtc_reg[nv_crtc->index];

	regp->tv_htotal = adjusted_mode->htotal;
	regp->tv_vtotal = adjusted_mode->vtotal;

	/* These delay the TV संकेतs with respect to the VGA port,
	 * they might be useful अगर we ever allow a CRTC to drive
	 * multiple outमाला_दो.
	 */
	regp->tv_hskew = 1;
	regp->tv_hsync_delay = 1;
	regp->tv_hsync_delay2 = 64;
	regp->tv_vskew = 1;
	regp->tv_vsync_delay = 1;

	get_slave_funcs(encoder)->mode_set(encoder, mode, adjusted_mode);
पूर्ण

अटल व्योम nv04_tv_commit(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा nouveau_encoder *nv_encoder = nouveau_encoder(encoder);
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nouveau_crtc *nv_crtc = nouveau_crtc(encoder->crtc);
	स्थिर काष्ठा drm_encoder_helper_funcs *helper = encoder->helper_निजी;

	helper->dpms(encoder, DRM_MODE_DPMS_ON);

	NV_DEBUG(drm, "Output %s is running on CRTC %d using output %c\n",
		 nv04_encoder_get_connector(nv_encoder)->base.name,
		 nv_crtc->index, '@' + ffs(nv_encoder->dcb->or));
पूर्ण

अटल व्योम nv04_tv_destroy(काष्ठा drm_encoder *encoder)
अणु
	get_slave_funcs(encoder)->destroy(encoder);
	drm_encoder_cleanup(encoder);

	kमुक्त(encoder->helper_निजी);
	kमुक्त(nouveau_encoder(encoder));
पूर्ण

अटल स्थिर काष्ठा drm_encoder_funcs nv04_tv_funcs = अणु
	.destroy = nv04_tv_destroy,
पूर्ण;

अटल स्थिर काष्ठा drm_encoder_helper_funcs nv04_tv_helper_funcs = अणु
	.dpms = nv04_tv_dpms,
	.mode_fixup = drm_i2c_encoder_mode_fixup,
	.prepare = nv04_tv_prepare,
	.commit = nv04_tv_commit,
	.mode_set = nv04_tv_mode_set,
	.detect = drm_i2c_encoder_detect,
पूर्ण;

पूर्णांक
nv04_tv_create(काष्ठा drm_connector *connector, काष्ठा dcb_output *entry)
अणु
	काष्ठा nouveau_encoder *nv_encoder;
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvkm_i2c *i2c = nvxx_i2c(&drm->client.device);
	काष्ठा nvkm_i2c_bus *bus = nvkm_i2c_bus_find(i2c, entry->i2c_index);
	पूर्णांक type, ret;

	/* Ensure that we can talk to this encoder */
	type = nv04_tv_identअगरy(dev, entry->i2c_index);
	अगर (type < 0)
		वापस type;

	/* Allocate the necessary memory */
	nv_encoder = kzalloc(माप(*nv_encoder), GFP_KERNEL);
	अगर (!nv_encoder)
		वापस -ENOMEM;

	/* Initialize the common members */
	encoder = to_drm_encoder(nv_encoder);

	drm_encoder_init(dev, encoder, &nv04_tv_funcs, DRM_MODE_ENCODER_TVDAC,
			 शून्य);
	drm_encoder_helper_add(encoder, &nv04_tv_helper_funcs);

	nv_encoder->enc_save = drm_i2c_encoder_save;
	nv_encoder->enc_restore = drm_i2c_encoder_restore;

	encoder->possible_crtcs = entry->heads;
	encoder->possible_clones = 0;
	nv_encoder->dcb = entry;
	nv_encoder->or = ffs(entry->or) - 1;

	/* Run the slave-specअगरic initialization */
	ret = drm_i2c_encoder_init(dev, to_encoder_slave(encoder),
				   &bus->i2c,
				   &nv04_tv_encoder_info[type].dev);
	अगर (ret < 0)
		जाओ fail_cleanup;

	/* Attach it to the specअगरied connector. */
	get_slave_funcs(encoder)->create_resources(encoder, connector);
	drm_connector_attach_encoder(connector, encoder);

	वापस 0;

fail_cleanup:
	drm_encoder_cleanup(encoder);
	kमुक्त(nv_encoder);
	वापस ret;
पूर्ण
