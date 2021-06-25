<शैली गुरु>
/*
 * Copyright 2003 NVIDIA, Corporation
 * Copyright 2006 Dave Airlie
 * Copyright 2007 Maarten Maathuis
 * Copyright 2007-2009 Stuart Bennett
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
 */

#समावेश <drm/drm_crtc_helper.h>

#समावेश "nouveau_drv.h"
#समावेश "nouveau_encoder.h"
#समावेश "nouveau_connector.h"
#समावेश "nouveau_crtc.h"
#समावेश "hw.h"
#समावेश "nvreg.h"

#समावेश <subdev/bios/gpपन.स>
#समावेश <subdev/gpपन.स>

#समावेश <nvअगर/समयr.h>

पूर्णांक nv04_dac_output_offset(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा dcb_output *dcb = nouveau_encoder(encoder)->dcb;
	पूर्णांक offset = 0;

	अगर (dcb->or & (8 | DCB_OUTPUT_C))
		offset += 0x68;
	अगर (dcb->or & (8 | DCB_OUTPUT_B))
		offset += 0x2000;

	वापस offset;
पूर्ण

/*
 * arbitrary limit to number of sense oscillations tolerated in one sample
 * period (observed to be at least 13 in "nvidia")
 */
#घोषणा MAX_HBLANK_OSC 20

/*
 * arbitrary limit to number of conflicting sample pairs to tolerate at a
 * voltage step (observed to be at least 5 in "nvidia")
 */
#घोषणा MAX_SAMPLE_PAIRS 10

अटल पूर्णांक sample_load_twice(काष्ठा drm_device *dev, bool sense[2])
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvअगर_object *device = &drm->client.device.object;
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++) अणु
		bool sense_a, sense_b, sense_b_prime;
		पूर्णांक j = 0;

		/*
		 * रुको क्रम bit 0 clear -- out of hblank -- (say reg value 0x4),
		 * then रुको क्रम transition 0x4->0x5->0x4: enter hblank, leave
		 * hblank again
		 * use a 10ms समयout (guards against crtc being inactive, in
		 * which हाल blank state would never change)
		 */
		अगर (nvअगर_msec(&drm->client.device, 10,
			अगर (!(nvअगर_rd32(device, NV_PRMCIO_INP0__COLOR) & 1))
				अवरोध;
		) < 0)
			वापस -EBUSY;

		अगर (nvअगर_msec(&drm->client.device, 10,
			अगर ( (nvअगर_rd32(device, NV_PRMCIO_INP0__COLOR) & 1))
				अवरोध;
		) < 0)
			वापस -EBUSY;

		अगर (nvअगर_msec(&drm->client.device, 10,
			अगर (!(nvअगर_rd32(device, NV_PRMCIO_INP0__COLOR) & 1))
				अवरोध;
		) < 0)
			वापस -EBUSY;

		udelay(100);
		/* when level triggers, sense is _LO_ */
		sense_a = nvअगर_rd08(device, NV_PRMCIO_INP0) & 0x10;

		/* take another पढ़ोing until it agrees with sense_a... */
		करो अणु
			udelay(100);
			sense_b = nvअगर_rd08(device, NV_PRMCIO_INP0) & 0x10;
			अगर (sense_a != sense_b) अणु
				sense_b_prime =
					nvअगर_rd08(device, NV_PRMCIO_INP0) & 0x10;
				अगर (sense_b == sense_b_prime) अणु
					/* ... unless two consecutive subsequent
					 * samples agree; sense_a is replaced */
					sense_a = sense_b;
					/* क्रमce mis-match so we loop */
					sense_b = !sense_a;
				पूर्ण
			पूर्ण
		पूर्ण जबतक ((sense_a != sense_b) && ++j < MAX_HBLANK_OSC);

		अगर (j == MAX_HBLANK_OSC)
			/* with so much oscillation, शेष to sense:LO */
			sense[i] = false;
		अन्यथा
			sense[i] = sense_a;
	पूर्ण

	वापस 0;
पूर्ण

अटल क्रमागत drm_connector_status nv04_dac_detect(काष्ठा drm_encoder *encoder,
						 काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा nvअगर_object *device = &nouveau_drm(dev)->client.device.object;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	uपूर्णांक8_t saved_seq1, saved_pi, saved_rpc1, saved_cr_mode;
	uपूर्णांक8_t saved_palette0[3], saved_palette_mask;
	uपूर्णांक32_t saved_rtest_ctrl, saved_rgen_ctrl;
	पूर्णांक i;
	uपूर्णांक8_t blue;
	bool sense = true;

	/*
	 * क्रम this detection to work, there needs to be a mode set up on the
	 * CRTC.  this is presumed to be the हाल
	 */

	अगर (nv_two_heads(dev))
		/* only implemented क्रम head A क्रम now */
		NVSetOwner(dev, 0);

	saved_cr_mode = NVReadVgaCrtc(dev, 0, NV_CIO_CR_MODE_INDEX);
	NVWriteVgaCrtc(dev, 0, NV_CIO_CR_MODE_INDEX, saved_cr_mode | 0x80);

	saved_seq1 = NVReadVgaSeq(dev, 0, NV_VIO_SR_CLOCK_INDEX);
	NVWriteVgaSeq(dev, 0, NV_VIO_SR_CLOCK_INDEX, saved_seq1 & ~0x20);

	saved_rtest_ctrl = NVReadRAMDAC(dev, 0, NV_PRAMDAC_TEST_CONTROL);
	NVWriteRAMDAC(dev, 0, NV_PRAMDAC_TEST_CONTROL,
		      saved_rtest_ctrl & ~NV_PRAMDAC_TEST_CONTROL_PWRDWN_DAC_OFF);

	msleep(10);

	saved_pi = NVReadVgaCrtc(dev, 0, NV_CIO_CRE_PIXEL_INDEX);
	NVWriteVgaCrtc(dev, 0, NV_CIO_CRE_PIXEL_INDEX,
		       saved_pi & ~(0x80 | MASK(NV_CIO_CRE_PIXEL_FORMAT)));
	saved_rpc1 = NVReadVgaCrtc(dev, 0, NV_CIO_CRE_RPC1_INDEX);
	NVWriteVgaCrtc(dev, 0, NV_CIO_CRE_RPC1_INDEX, saved_rpc1 & ~0xc0);

	nvअगर_wr08(device, NV_PRMDIO_READ_MODE_ADDRESS, 0x0);
	क्रम (i = 0; i < 3; i++)
		saved_palette0[i] = nvअगर_rd08(device, NV_PRMDIO_PALETTE_DATA);
	saved_palette_mask = nvअगर_rd08(device, NV_PRMDIO_PIXEL_MASK);
	nvअगर_wr08(device, NV_PRMDIO_PIXEL_MASK, 0);

	saved_rgen_ctrl = NVReadRAMDAC(dev, 0, NV_PRAMDAC_GENERAL_CONTROL);
	NVWriteRAMDAC(dev, 0, NV_PRAMDAC_GENERAL_CONTROL,
		      (saved_rgen_ctrl & ~(NV_PRAMDAC_GENERAL_CONTROL_BPC_8BITS |
					   NV_PRAMDAC_GENERAL_CONTROL_TERMINATION_75OHM)) |
		      NV_PRAMDAC_GENERAL_CONTROL_PIXMIX_ON);

	blue = 8;	/* start of test range */

	करो अणु
		bool sense_pair[2];

		nvअगर_wr08(device, NV_PRMDIO_WRITE_MODE_ADDRESS, 0);
		nvअगर_wr08(device, NV_PRMDIO_PALETTE_DATA, 0);
		nvअगर_wr08(device, NV_PRMDIO_PALETTE_DATA, 0);
		/* testing blue won't find monochrome monitors.  I don't care */
		nvअगर_wr08(device, NV_PRMDIO_PALETTE_DATA, blue);

		i = 0;
		/* take sample pairs until both samples in the pair agree */
		करो अणु
			अगर (sample_load_twice(dev, sense_pair))
				जाओ out;
		पूर्ण जबतक ((sense_pair[0] != sense_pair[1]) &&
							++i < MAX_SAMPLE_PAIRS);

		अगर (i == MAX_SAMPLE_PAIRS)
			/* too much oscillation शेषs to LO */
			sense = false;
		अन्यथा
			sense = sense_pair[0];

	/*
	 * अगर sense goes LO beक्रमe blue ramps to 0x18, monitor is not connected.
	 * ergo, अगर blue माला_लो to 0x18, monitor must be connected
	 */
	पूर्ण जबतक (++blue < 0x18 && sense);

out:
	nvअगर_wr08(device, NV_PRMDIO_PIXEL_MASK, saved_palette_mask);
	NVWriteRAMDAC(dev, 0, NV_PRAMDAC_GENERAL_CONTROL, saved_rgen_ctrl);
	nvअगर_wr08(device, NV_PRMDIO_WRITE_MODE_ADDRESS, 0);
	क्रम (i = 0; i < 3; i++)
		nvअगर_wr08(device, NV_PRMDIO_PALETTE_DATA, saved_palette0[i]);
	NVWriteRAMDAC(dev, 0, NV_PRAMDAC_TEST_CONTROL, saved_rtest_ctrl);
	NVWriteVgaCrtc(dev, 0, NV_CIO_CRE_PIXEL_INDEX, saved_pi);
	NVWriteVgaCrtc(dev, 0, NV_CIO_CRE_RPC1_INDEX, saved_rpc1);
	NVWriteVgaSeq(dev, 0, NV_VIO_SR_CLOCK_INDEX, saved_seq1);
	NVWriteVgaCrtc(dev, 0, NV_CIO_CR_MODE_INDEX, saved_cr_mode);

	अगर (blue == 0x18) अणु
		NV_DEBUG(drm, "Load detected on head A\n");
		वापस connector_status_connected;
	पूर्ण

	वापस connector_status_disconnected;
पूर्ण

uपूर्णांक32_t nv17_dac_sample_load(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvअगर_object *device = &nouveau_drm(dev)->client.device.object;
	काष्ठा nvkm_gpio *gpio = nvxx_gpio(&drm->client.device);
	काष्ठा dcb_output *dcb = nouveau_encoder(encoder)->dcb;
	uपूर्णांक32_t sample, testval, regoffset = nv04_dac_output_offset(encoder);
	uपूर्णांक32_t saved_घातerctrl_2 = 0, saved_घातerctrl_4 = 0, saved_routput,
		saved_rtest_ctrl, saved_gpio0 = 0, saved_gpio1 = 0, temp, routput;
	पूर्णांक head;

#घोषणा RGB_TEST_DATA(r, g, b) (r << 0 | g << 10 | b << 20)
	अगर (dcb->type == DCB_OUTPUT_TV) अणु
		testval = RGB_TEST_DATA(0xa0, 0xa0, 0xa0);

		अगर (drm->vbios.tvdactestval)
			testval = drm->vbios.tvdactestval;
	पूर्ण अन्यथा अणु
		testval = RGB_TEST_DATA(0x140, 0x140, 0x140); /* 0x94050140 */

		अगर (drm->vbios.dactestval)
			testval = drm->vbios.dactestval;
	पूर्ण

	saved_rtest_ctrl = NVReadRAMDAC(dev, 0, NV_PRAMDAC_TEST_CONTROL + regoffset);
	NVWriteRAMDAC(dev, 0, NV_PRAMDAC_TEST_CONTROL + regoffset,
		      saved_rtest_ctrl & ~NV_PRAMDAC_TEST_CONTROL_PWRDWN_DAC_OFF);

	saved_घातerctrl_2 = nvअगर_rd32(device, NV_PBUS_POWERCTRL_2);

	nvअगर_wr32(device, NV_PBUS_POWERCTRL_2, saved_घातerctrl_2 & 0xd7ffffff);
	अगर (regoffset == 0x68) अणु
		saved_घातerctrl_4 = nvअगर_rd32(device, NV_PBUS_POWERCTRL_4);
		nvअगर_wr32(device, NV_PBUS_POWERCTRL_4, saved_घातerctrl_4 & 0xffffffcf);
	पूर्ण

	अगर (gpio) अणु
		saved_gpio1 = nvkm_gpio_get(gpio, 0, DCB_GPIO_TVDAC1, 0xff);
		saved_gpio0 = nvkm_gpio_get(gpio, 0, DCB_GPIO_TVDAC0, 0xff);
		nvkm_gpio_set(gpio, 0, DCB_GPIO_TVDAC1, 0xff, dcb->type == DCB_OUTPUT_TV);
		nvkm_gpio_set(gpio, 0, DCB_GPIO_TVDAC0, 0xff, dcb->type == DCB_OUTPUT_TV);
	पूर्ण

	msleep(4);

	saved_routput = NVReadRAMDAC(dev, 0, NV_PRAMDAC_DACCLK + regoffset);
	head = (saved_routput & 0x100) >> 8;

	/* अगर there's a spare crtc, using it will minimise flicker */
	अगर (!(NVReadVgaCrtc(dev, head, NV_CIO_CRE_RPC1_INDEX) & 0xC0))
		head ^= 1;

	/* nv driver and nv31 use 0xfffffeee, nv34 and 6600 use 0xfffffece */
	routput = (saved_routput & 0xfffffece) | head << 8;

	अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_CURIE) अणु
		अगर (dcb->type == DCB_OUTPUT_TV)
			routput |= 0x1a << 16;
		अन्यथा
			routput &= ~(0x1a << 16);
	पूर्ण

	NVWriteRAMDAC(dev, 0, NV_PRAMDAC_DACCLK + regoffset, routput);
	msleep(1);

	temp = NVReadRAMDAC(dev, 0, NV_PRAMDAC_DACCLK + regoffset);
	NVWriteRAMDAC(dev, 0, NV_PRAMDAC_DACCLK + regoffset, temp | 1);

	NVWriteRAMDAC(dev, head, NV_PRAMDAC_TESTPOINT_DATA,
		      NV_PRAMDAC_TESTPOINT_DATA_NOTBLANK | testval);
	temp = NVReadRAMDAC(dev, head, NV_PRAMDAC_TEST_CONTROL);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_TEST_CONTROL,
		      temp | NV_PRAMDAC_TEST_CONTROL_TP_INS_EN_ASSERTED);
	msleep(5);

	sample = NVReadRAMDAC(dev, 0, NV_PRAMDAC_TEST_CONTROL + regoffset);
	/* करो it again just in हाल it's a residual current */
	sample &= NVReadRAMDAC(dev, 0, NV_PRAMDAC_TEST_CONTROL + regoffset);

	temp = NVReadRAMDAC(dev, head, NV_PRAMDAC_TEST_CONTROL);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_TEST_CONTROL,
		      temp & ~NV_PRAMDAC_TEST_CONTROL_TP_INS_EN_ASSERTED);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_TESTPOINT_DATA, 0);

	/* bios करोes something more complex क्रम restoring, but I think this is good enough */
	NVWriteRAMDAC(dev, 0, NV_PRAMDAC_DACCLK + regoffset, saved_routput);
	NVWriteRAMDAC(dev, 0, NV_PRAMDAC_TEST_CONTROL + regoffset, saved_rtest_ctrl);
	अगर (regoffset == 0x68)
		nvअगर_wr32(device, NV_PBUS_POWERCTRL_4, saved_घातerctrl_4);
	nvअगर_wr32(device, NV_PBUS_POWERCTRL_2, saved_घातerctrl_2);

	अगर (gpio) अणु
		nvkm_gpio_set(gpio, 0, DCB_GPIO_TVDAC1, 0xff, saved_gpio1);
		nvkm_gpio_set(gpio, 0, DCB_GPIO_TVDAC0, 0xff, saved_gpio0);
	पूर्ण

	वापस sample;
पूर्ण

अटल क्रमागत drm_connector_status
nv17_dac_detect(काष्ठा drm_encoder *encoder, काष्ठा drm_connector *connector)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(encoder->dev);
	काष्ठा dcb_output *dcb = nouveau_encoder(encoder)->dcb;

	अगर (nv04_dac_in_use(encoder))
		वापस connector_status_disconnected;

	अगर (nv17_dac_sample_load(encoder) &
	    NV_PRAMDAC_TEST_CONTROL_SENSEB_ALLHI) अणु
		NV_DEBUG(drm, "Load detected on output %c\n",
			 '@' + ffs(dcb->or));
		वापस connector_status_connected;
	पूर्ण अन्यथा अणु
		वापस connector_status_disconnected;
	पूर्ण
पूर्ण

अटल bool nv04_dac_mode_fixup(काष्ठा drm_encoder *encoder,
				स्थिर काष्ठा drm_display_mode *mode,
				काष्ठा drm_display_mode *adjusted_mode)
अणु
	अगर (nv04_dac_in_use(encoder))
		वापस false;

	वापस true;
पूर्ण

अटल व्योम nv04_dac_prepare(काष्ठा drm_encoder *encoder)
अणु
	स्थिर काष्ठा drm_encoder_helper_funcs *helper = encoder->helper_निजी;
	काष्ठा drm_device *dev = encoder->dev;
	पूर्णांक head = nouveau_crtc(encoder->crtc)->index;

	helper->dpms(encoder, DRM_MODE_DPMS_OFF);

	nv04_dfp_disable(dev, head);
पूर्ण

अटल व्योम nv04_dac_mode_set(काष्ठा drm_encoder *encoder,
			      काष्ठा drm_display_mode *mode,
			      काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	पूर्णांक head = nouveau_crtc(encoder->crtc)->index;

	अगर (nv_gf4_disp_arch(dev)) अणु
		काष्ठा drm_encoder *rebind;
		uपूर्णांक32_t dac_offset = nv04_dac_output_offset(encoder);
		uपूर्णांक32_t otherdac;

		/* bit 16-19 are bits that are set on some G70 cards,
		 * but करोn't seem to have much effect */
		NVWriteRAMDAC(dev, 0, NV_PRAMDAC_DACCLK + dac_offset,
			      head << 8 | NV_PRAMDAC_DACCLK_SEL_DACCLK);
		/* क्रमce any other vga encoders to bind to the other crtc */
		list_क्रम_each_entry(rebind, &dev->mode_config.encoder_list, head) अणु
			अगर (rebind == encoder
			    || nouveau_encoder(rebind)->dcb->type != DCB_OUTPUT_ANALOG)
				जारी;

			dac_offset = nv04_dac_output_offset(rebind);
			otherdac = NVReadRAMDAC(dev, 0, NV_PRAMDAC_DACCLK + dac_offset);
			NVWriteRAMDAC(dev, 0, NV_PRAMDAC_DACCLK + dac_offset,
				      (otherdac & ~0x0100) | (head ^ 1) << 8);
		पूर्ण
	पूर्ण

	/* This could use refinement क्रम flatpanels, but it should work this way */
	अगर (drm->client.device.info.chipset < 0x44)
		NVWriteRAMDAC(dev, 0, NV_PRAMDAC_TEST_CONTROL + nv04_dac_output_offset(encoder), 0xf0000000);
	अन्यथा
		NVWriteRAMDAC(dev, 0, NV_PRAMDAC_TEST_CONTROL + nv04_dac_output_offset(encoder), 0x00100000);
पूर्ण

अटल व्योम nv04_dac_commit(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा nouveau_encoder *nv_encoder = nouveau_encoder(encoder);
	काष्ठा nouveau_drm *drm = nouveau_drm(encoder->dev);
	काष्ठा nouveau_crtc *nv_crtc = nouveau_crtc(encoder->crtc);
	स्थिर काष्ठा drm_encoder_helper_funcs *helper = encoder->helper_निजी;

	helper->dpms(encoder, DRM_MODE_DPMS_ON);

	NV_DEBUG(drm, "Output %s is running on CRTC %d using output %c\n",
		 nv04_encoder_get_connector(nv_encoder)->base.name,
		 nv_crtc->index, '@' + ffs(nv_encoder->dcb->or));
पूर्ण

व्योम nv04_dac_update_dacclk(काष्ठा drm_encoder *encoder, bool enable)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा dcb_output *dcb = nouveau_encoder(encoder)->dcb;

	अगर (nv_gf4_disp_arch(dev)) अणु
		uपूर्णांक32_t *dac_users = &nv04_display(dev)->dac_users[ffs(dcb->or) - 1];
		पूर्णांक dacclk_off = NV_PRAMDAC_DACCLK + nv04_dac_output_offset(encoder);
		uपूर्णांक32_t dacclk = NVReadRAMDAC(dev, 0, dacclk_off);

		अगर (enable) अणु
			*dac_users |= 1 << dcb->index;
			NVWriteRAMDAC(dev, 0, dacclk_off, dacclk | NV_PRAMDAC_DACCLK_SEL_DACCLK);

		पूर्ण अन्यथा अणु
			*dac_users &= ~(1 << dcb->index);
			अगर (!*dac_users)
				NVWriteRAMDAC(dev, 0, dacclk_off,
					dacclk & ~NV_PRAMDAC_DACCLK_SEL_DACCLK);
		पूर्ण
	पूर्ण
पूर्ण

/* Check अगर the DAC corresponding to 'encoder' is being used by
 * someone अन्यथा. */
bool nv04_dac_in_use(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा dcb_output *dcb = nouveau_encoder(encoder)->dcb;

	वापस nv_gf4_disp_arch(encoder->dev) &&
		(nv04_display(dev)->dac_users[ffs(dcb->or) - 1] & ~(1 << dcb->index));
पूर्ण

अटल व्योम nv04_dac_dpms(काष्ठा drm_encoder *encoder, पूर्णांक mode)
अणु
	काष्ठा nouveau_encoder *nv_encoder = nouveau_encoder(encoder);
	काष्ठा nouveau_drm *drm = nouveau_drm(encoder->dev);

	अगर (nv_encoder->last_dpms == mode)
		वापस;
	nv_encoder->last_dpms = mode;

	NV_DEBUG(drm, "Setting dpms mode %d on vga encoder (output %d)\n",
		 mode, nv_encoder->dcb->index);

	nv04_dac_update_dacclk(encoder, mode == DRM_MODE_DPMS_ON);
पूर्ण

अटल व्योम nv04_dac_save(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा nouveau_encoder *nv_encoder = nouveau_encoder(encoder);
	काष्ठा drm_device *dev = encoder->dev;

	अगर (nv_gf4_disp_arch(dev))
		nv_encoder->restore.output = NVReadRAMDAC(dev, 0, NV_PRAMDAC_DACCLK +
							  nv04_dac_output_offset(encoder));
पूर्ण

अटल व्योम nv04_dac_restore(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा nouveau_encoder *nv_encoder = nouveau_encoder(encoder);
	काष्ठा drm_device *dev = encoder->dev;

	अगर (nv_gf4_disp_arch(dev))
		NVWriteRAMDAC(dev, 0, NV_PRAMDAC_DACCLK + nv04_dac_output_offset(encoder),
			      nv_encoder->restore.output);

	nv_encoder->last_dpms = NV_DPMS_CLEARED;
पूर्ण

अटल व्योम nv04_dac_destroy(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा nouveau_encoder *nv_encoder = nouveau_encoder(encoder);

	drm_encoder_cleanup(encoder);
	kमुक्त(nv_encoder);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs nv04_dac_helper_funcs = अणु
	.dpms = nv04_dac_dpms,
	.mode_fixup = nv04_dac_mode_fixup,
	.prepare = nv04_dac_prepare,
	.commit = nv04_dac_commit,
	.mode_set = nv04_dac_mode_set,
	.detect = nv04_dac_detect
पूर्ण;

अटल स्थिर काष्ठा drm_encoder_helper_funcs nv17_dac_helper_funcs = अणु
	.dpms = nv04_dac_dpms,
	.mode_fixup = nv04_dac_mode_fixup,
	.prepare = nv04_dac_prepare,
	.commit = nv04_dac_commit,
	.mode_set = nv04_dac_mode_set,
	.detect = nv17_dac_detect
पूर्ण;

अटल स्थिर काष्ठा drm_encoder_funcs nv04_dac_funcs = अणु
	.destroy = nv04_dac_destroy,
पूर्ण;

पूर्णांक
nv04_dac_create(काष्ठा drm_connector *connector, काष्ठा dcb_output *entry)
अणु
	स्थिर काष्ठा drm_encoder_helper_funcs *helper;
	काष्ठा nouveau_encoder *nv_encoder = शून्य;
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_encoder *encoder;

	nv_encoder = kzalloc(माप(*nv_encoder), GFP_KERNEL);
	अगर (!nv_encoder)
		वापस -ENOMEM;

	encoder = to_drm_encoder(nv_encoder);

	nv_encoder->dcb = entry;
	nv_encoder->or = ffs(entry->or) - 1;

	nv_encoder->enc_save = nv04_dac_save;
	nv_encoder->enc_restore = nv04_dac_restore;

	अगर (nv_gf4_disp_arch(dev))
		helper = &nv17_dac_helper_funcs;
	अन्यथा
		helper = &nv04_dac_helper_funcs;

	drm_encoder_init(dev, encoder, &nv04_dac_funcs, DRM_MODE_ENCODER_DAC,
			 शून्य);
	drm_encoder_helper_add(encoder, helper);

	encoder->possible_crtcs = entry->heads;
	encoder->possible_clones = 0;

	drm_connector_attach_encoder(connector, encoder);
	वापस 0;
पूर्ण
