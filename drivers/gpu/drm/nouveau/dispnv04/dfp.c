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
#समावेश <drm/drm_fourcc.h>

#समावेश "nouveau_drv.h"
#समावेश "nouveau_reg.h"
#समावेश "nouveau_encoder.h"
#समावेश "nouveau_connector.h"
#समावेश "nouveau_crtc.h"
#समावेश "hw.h"
#समावेश "nvreg.h"

#समावेश <drm/i2c/sil164.h>

#समावेश <subdev/i2c.h>

#घोषणा FP_TG_CONTROL_ON  (NV_PRAMDAC_FP_TG_CONTROL_DISPEN_POS |	\
			   NV_PRAMDAC_FP_TG_CONTROL_HSYNC_POS |		\
			   NV_PRAMDAC_FP_TG_CONTROL_VSYNC_POS)
#घोषणा FP_TG_CONTROL_OFF (NV_PRAMDAC_FP_TG_CONTROL_DISPEN_DISABLE |	\
			   NV_PRAMDAC_FP_TG_CONTROL_HSYNC_DISABLE |	\
			   NV_PRAMDAC_FP_TG_CONTROL_VSYNC_DISABLE)

अटल अंतरभूत bool is_fpc_off(uपूर्णांक32_t fpc)
अणु
	वापस ((fpc & (FP_TG_CONTROL_ON | FP_TG_CONTROL_OFF)) ==
			FP_TG_CONTROL_OFF);
पूर्ण

पूर्णांक nv04_dfp_get_bound_head(काष्ठा drm_device *dev, काष्ठा dcb_output *dcbent)
अणु
	/* special हाल of nv_पढ़ो_पंचांगds to find crtc associated with an output.
	 * this करोes not give a correct answer क्रम off-chip dvi, but there's no
	 * use क्रम such an answer anyway
	 */
	पूर्णांक ramdac = (dcbent->or & DCB_OUTPUT_C) >> 2;

	NVWriteRAMDAC(dev, ramdac, NV_PRAMDAC_FP_TMDS_CONTROL,
	NV_PRAMDAC_FP_TMDS_CONTROL_WRITE_DISABLE | 0x4);
	वापस ((NVReadRAMDAC(dev, ramdac, NV_PRAMDAC_FP_TMDS_DATA) & 0x8) >> 3) ^ ramdac;
पूर्ण

व्योम nv04_dfp_bind_head(काष्ठा drm_device *dev, काष्ठा dcb_output *dcbent,
			पूर्णांक head, bool dl)
अणु
	/* The BIOS scripts करोn't करो this क्रम us, sadly
	 * Luckily we करो know the values ;-)
	 *
	 * head < 0 indicates we wish to क्रमce a setting with the overrideval
	 * (क्रम VT restore etc.)
	 */

	पूर्णांक ramdac = (dcbent->or & DCB_OUTPUT_C) >> 2;
	uपूर्णांक8_t पंचांगds04 = 0x80;

	अगर (head != ramdac)
		पंचांगds04 = 0x88;

	अगर (dcbent->type == DCB_OUTPUT_LVDS)
		पंचांगds04 |= 0x01;

	nv_ग_लिखो_पंचांगds(dev, dcbent->or, 0, 0x04, पंचांगds04);

	अगर (dl)	/* dual link */
		nv_ग_लिखो_पंचांगds(dev, dcbent->or, 1, 0x04, पंचांगds04 ^ 0x08);
पूर्ण

व्योम nv04_dfp_disable(काष्ठा drm_device *dev, पूर्णांक head)
अणु
	काष्ठा nv04_crtc_reg *crtcstate = nv04_display(dev)->mode_reg.crtc_reg;

	अगर (NVReadRAMDAC(dev, head, NV_PRAMDAC_FP_TG_CONTROL) &
	    FP_TG_CONTROL_ON) अणु
		/* digital remnants must be cleaned beक्रमe new crtc
		 * values programmed.  delay is समय क्रम the vga stuff
		 * to realise it's in control again
		 */
		NVWriteRAMDAC(dev, head, NV_PRAMDAC_FP_TG_CONTROL,
			      FP_TG_CONTROL_OFF);
		msleep(50);
	पूर्ण
	/* करोn't inadvertently turn it on when state written later */
	crtcstate[head].fp_control = FP_TG_CONTROL_OFF;
	crtcstate[head].CRTC[NV_CIO_CRE_LCD__INDEX] &=
		~NV_CIO_CRE_LCD_ROUTE_MASK;
पूर्ण

व्योम nv04_dfp_update_fp_control(काष्ठा drm_encoder *encoder, पूर्णांक mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा drm_crtc *crtc;
	काष्ठा nouveau_crtc *nv_crtc;
	uपूर्णांक32_t *fpc;

	अगर (mode == DRM_MODE_DPMS_ON) अणु
		nv_crtc = nouveau_crtc(encoder->crtc);
		fpc = &nv04_display(dev)->mode_reg.crtc_reg[nv_crtc->index].fp_control;

		अगर (is_fpc_off(*fpc)) अणु
			/* using saved value is ok, as (is_digital && dpms_on &&
			 * fp_control==OFF) is (at present) *only* true when
			 * fpc's most recent change was by below "off" code
			 */
			*fpc = nv_crtc->dpms_saved_fp_control;
		पूर्ण

		nv_crtc->fp_users |= 1 << nouveau_encoder(encoder)->dcb->index;
		NVWriteRAMDAC(dev, nv_crtc->index, NV_PRAMDAC_FP_TG_CONTROL, *fpc);
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry(crtc, &dev->mode_config.crtc_list, head) अणु
			nv_crtc = nouveau_crtc(crtc);
			fpc = &nv04_display(dev)->mode_reg.crtc_reg[nv_crtc->index].fp_control;

			nv_crtc->fp_users &= ~(1 << nouveau_encoder(encoder)->dcb->index);
			अगर (!is_fpc_off(*fpc) && !nv_crtc->fp_users) अणु
				nv_crtc->dpms_saved_fp_control = *fpc;
				/* cut the FP output */
				*fpc &= ~FP_TG_CONTROL_ON;
				*fpc |= FP_TG_CONTROL_OFF;
				NVWriteRAMDAC(dev, nv_crtc->index,
					      NV_PRAMDAC_FP_TG_CONTROL, *fpc);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा drm_encoder *get_पंचांगds_slave(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा dcb_output *dcb = nouveau_encoder(encoder)->dcb;
	काष्ठा drm_encoder *slave;

	अगर (dcb->type != DCB_OUTPUT_TMDS || dcb->location == DCB_LOC_ON_CHIP)
		वापस शून्य;

	/* Some BIOSes (e.g. the one in a Quadro FX1000) report several
	 * TMDS transmitters at the same I2C address, in the same I2C
	 * bus. This can still work because in that हाल one of them is
	 * always hard-wired to a reasonable configuration using straps,
	 * and the other one needs to be programmed.
	 *
	 * I करोn't think there's a way to know which is which, even the
	 * blob programs the one exposed via I2C क्रम *both* heads, so
	 * let's करो the same.
	 */
	list_क्रम_each_entry(slave, &dev->mode_config.encoder_list, head) अणु
		काष्ठा dcb_output *slave_dcb = nouveau_encoder(slave)->dcb;

		अगर (slave_dcb->type == DCB_OUTPUT_TMDS && get_slave_funcs(slave) &&
		    slave_dcb->पंचांगdsconf.slave_addr == dcb->पंचांगdsconf.slave_addr)
			वापस slave;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल bool nv04_dfp_mode_fixup(काष्ठा drm_encoder *encoder,
				स्थिर काष्ठा drm_display_mode *mode,
				काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा nouveau_encoder *nv_encoder = nouveau_encoder(encoder);
	काष्ठा nouveau_connector *nv_connector =
		nv04_encoder_get_connector(nv_encoder);

	अगर (!nv_connector->native_mode ||
	    nv_connector->scaling_mode == DRM_MODE_SCALE_NONE ||
	    mode->hdisplay > nv_connector->native_mode->hdisplay ||
	    mode->vdisplay > nv_connector->native_mode->vdisplay) अणु
		nv_encoder->mode = *adjusted_mode;

	पूर्ण अन्यथा अणु
		nv_encoder->mode = *nv_connector->native_mode;
		adjusted_mode->घड़ी = nv_connector->native_mode->घड़ी;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम nv04_dfp_prepare_sel_clk(काष्ठा drm_device *dev,
				     काष्ठा nouveau_encoder *nv_encoder, पूर्णांक head)
अणु
	काष्ठा nv04_mode_state *state = &nv04_display(dev)->mode_reg;
	uपूर्णांक32_t bits1618 = nv_encoder->dcb->or & DCB_OUTPUT_A ? 0x10000 : 0x40000;

	अगर (nv_encoder->dcb->location != DCB_LOC_ON_CHIP)
		वापस;

	/* SEL_CLK is only used on the primary ramdac
	 * It toggles spपढ़ो spectrum PLL output and sets the bindings of PLLs
	 * to heads on digital outमाला_दो
	 */
	अगर (head)
		state->sel_clk |= bits1618;
	अन्यथा
		state->sel_clk &= ~bits1618;

	/* nv30:
	 *	bit 0		NVClk spपढ़ो spectrum on/off
	 *	bit 2		MemClk spपढ़ो spectrum on/off
	 * 	bit 4		PixClk1 spपढ़ो spectrum on/off toggle
	 * 	bit 6		PixClk2 spपढ़ो spectrum on/off toggle
	 *
	 * nv40 (observations from bios behaviour and mmio traces):
	 * 	bits 4&6	as क्रम nv30
	 * 	bits 5&7	head dependent as क्रम bits 4&6, but करो not appear with 4&6;
	 * 			maybe a dअगरferent spपढ़ो mode
	 * 	bits 8&10	seen on dual-link dvi outमाला_दो, purpose unknown (set by POST scripts)
	 * 	The logic behind turning spपढ़ो spectrum on/off in the first place,
	 * 	and which bit-pair to use, is unclear on nv40 (क्रम earlier cards, the fp table
	 * 	entry has the necessary info)
	 */
	अगर (nv_encoder->dcb->type == DCB_OUTPUT_LVDS && nv04_display(dev)->saved_reg.sel_clk & 0xf0) अणु
		पूर्णांक shअगरt = (nv04_display(dev)->saved_reg.sel_clk & 0x50) ? 0 : 1;

		state->sel_clk &= ~0xf0;
		state->sel_clk |= (head ? 0x40 : 0x10) << shअगरt;
	पूर्ण
पूर्ण

अटल व्योम nv04_dfp_prepare(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा nouveau_encoder *nv_encoder = nouveau_encoder(encoder);
	स्थिर काष्ठा drm_encoder_helper_funcs *helper = encoder->helper_निजी;
	काष्ठा drm_device *dev = encoder->dev;
	पूर्णांक head = nouveau_crtc(encoder->crtc)->index;
	काष्ठा nv04_crtc_reg *crtcstate = nv04_display(dev)->mode_reg.crtc_reg;
	uपूर्णांक8_t *cr_lcd = &crtcstate[head].CRTC[NV_CIO_CRE_LCD__INDEX];
	uपूर्णांक8_t *cr_lcd_oth = &crtcstate[head ^ 1].CRTC[NV_CIO_CRE_LCD__INDEX];

	helper->dpms(encoder, DRM_MODE_DPMS_OFF);

	nv04_dfp_prepare_sel_clk(dev, nv_encoder, head);

	*cr_lcd = (*cr_lcd & ~NV_CIO_CRE_LCD_ROUTE_MASK) | 0x3;

	अगर (nv_two_heads(dev)) अणु
		अगर (nv_encoder->dcb->location == DCB_LOC_ON_CHIP)
			*cr_lcd |= head ? 0x0 : 0x8;
		अन्यथा अणु
			*cr_lcd |= (nv_encoder->dcb->or << 4) & 0x30;
			अगर (nv_encoder->dcb->type == DCB_OUTPUT_LVDS)
				*cr_lcd |= 0x30;
			अगर ((*cr_lcd & 0x30) == (*cr_lcd_oth & 0x30)) अणु
				/* aव्योम being connected to both crtcs */
				*cr_lcd_oth &= ~0x30;
				NVWriteVgaCrtc(dev, head ^ 1,
					       NV_CIO_CRE_LCD__INDEX,
					       *cr_lcd_oth);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण


अटल व्योम nv04_dfp_mode_set(काष्ठा drm_encoder *encoder,
			      काष्ठा drm_display_mode *mode,
			      काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा nvअगर_object *device = &nouveau_drm(dev)->client.device.object;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nouveau_crtc *nv_crtc = nouveau_crtc(encoder->crtc);
	काष्ठा nv04_crtc_reg *regp = &nv04_display(dev)->mode_reg.crtc_reg[nv_crtc->index];
	काष्ठा nv04_crtc_reg *savep = &nv04_display(dev)->saved_reg.crtc_reg[nv_crtc->index];
	काष्ठा nouveau_connector *nv_connector = nouveau_crtc_connector_get(nv_crtc);
	काष्ठा nouveau_encoder *nv_encoder = nouveau_encoder(encoder);
	काष्ठा drm_display_mode *output_mode = &nv_encoder->mode;
	काष्ठा drm_connector *connector = &nv_connector->base;
	स्थिर काष्ठा drm_framebuffer *fb = encoder->crtc->primary->fb;
	uपूर्णांक32_t mode_ratio, panel_ratio;

	NV_DEBUG(drm, "Output mode on CRTC %d:\n", nv_crtc->index);
	drm_mode_debug_prपूर्णांकmodeline(output_mode);

	/* Initialize the FP रेजिस्टरs in this CRTC. */
	regp->fp_horiz_regs[FP_DISPLAY_END] = output_mode->hdisplay - 1;
	regp->fp_horiz_regs[FP_TOTAL] = output_mode->htotal - 1;
	अगर (!nv_gf4_disp_arch(dev) ||
	    (output_mode->hsync_start - output_mode->hdisplay) >=
					drm->vbios.digital_min_front_porch)
		regp->fp_horiz_regs[FP_CRTC] = output_mode->hdisplay;
	अन्यथा
		regp->fp_horiz_regs[FP_CRTC] = output_mode->hsync_start - drm->vbios.digital_min_front_porch - 1;
	regp->fp_horiz_regs[FP_SYNC_START] = output_mode->hsync_start - 1;
	regp->fp_horiz_regs[FP_SYNC_END] = output_mode->hsync_end - 1;
	regp->fp_horiz_regs[FP_VALID_START] = output_mode->hskew;
	regp->fp_horiz_regs[FP_VALID_END] = output_mode->hdisplay - 1;

	regp->fp_vert_regs[FP_DISPLAY_END] = output_mode->vdisplay - 1;
	regp->fp_vert_regs[FP_TOTAL] = output_mode->vtotal - 1;
	regp->fp_vert_regs[FP_CRTC] = output_mode->vtotal - 5 - 1;
	regp->fp_vert_regs[FP_SYNC_START] = output_mode->vsync_start - 1;
	regp->fp_vert_regs[FP_SYNC_END] = output_mode->vsync_end - 1;
	regp->fp_vert_regs[FP_VALID_START] = 0;
	regp->fp_vert_regs[FP_VALID_END] = output_mode->vdisplay - 1;

	/* bit26: a bit seen on some g7x, no as yet discernable purpose */
	regp->fp_control = NV_PRAMDAC_FP_TG_CONTROL_DISPEN_POS |
			   (savep->fp_control & (1 << 26 | NV_PRAMDAC_FP_TG_CONTROL_READ_PROG));
	/* Deal with vsync/hsync polarity */
	/* LVDS screens करो set this, but modes with +ve syncs are very rare */
	अगर (output_mode->flags & DRM_MODE_FLAG_PVSYNC)
		regp->fp_control |= NV_PRAMDAC_FP_TG_CONTROL_VSYNC_POS;
	अगर (output_mode->flags & DRM_MODE_FLAG_PHSYNC)
		regp->fp_control |= NV_PRAMDAC_FP_TG_CONTROL_HSYNC_POS;
	/* panel scaling first, as native would get set otherwise */
	अगर (nv_connector->scaling_mode == DRM_MODE_SCALE_NONE ||
	    nv_connector->scaling_mode == DRM_MODE_SCALE_CENTER)	/* panel handles it */
		regp->fp_control |= NV_PRAMDAC_FP_TG_CONTROL_MODE_CENTER;
	अन्यथा अगर (adjusted_mode->hdisplay == output_mode->hdisplay &&
		 adjusted_mode->vdisplay == output_mode->vdisplay) /* native mode */
		regp->fp_control |= NV_PRAMDAC_FP_TG_CONTROL_MODE_NATIVE;
	अन्यथा /* gpu needs to scale */
		regp->fp_control |= NV_PRAMDAC_FP_TG_CONTROL_MODE_SCALE;
	अगर (nvअगर_rd32(device, NV_PEXTDEV_BOOT_0) & NV_PEXTDEV_BOOT_0_STRAP_FP_IFACE_12BIT)
		regp->fp_control |= NV_PRAMDAC_FP_TG_CONTROL_WIDTH_12;
	अगर (nv_encoder->dcb->location != DCB_LOC_ON_CHIP &&
	    output_mode->घड़ी > 165000)
		regp->fp_control |= (2 << 24);
	अगर (nv_encoder->dcb->type == DCB_OUTPUT_LVDS) अणु
		bool duallink = false, dummy;
		अगर (nv_connector->edid &&
		    nv_connector->type == DCB_CONNECTOR_LVDS_SPWG) अणु
			duallink = (((u8 *)nv_connector->edid)[121] == 2);
		पूर्ण अन्यथा अणु
			nouveau_bios_parse_lvds_table(dev, output_mode->घड़ी,
						      &duallink, &dummy);
		पूर्ण

		अगर (duallink)
			regp->fp_control |= (8 << 28);
	पूर्ण अन्यथा
	अगर (output_mode->घड़ी > 165000)
		regp->fp_control |= (8 << 28);

	regp->fp_debug_0 = NV_PRAMDAC_FP_DEBUG_0_YWEIGHT_ROUND |
			   NV_PRAMDAC_FP_DEBUG_0_XWEIGHT_ROUND |
			   NV_PRAMDAC_FP_DEBUG_0_YINTERP_BILINEAR |
			   NV_PRAMDAC_FP_DEBUG_0_XINTERP_BILINEAR |
			   NV_RAMDAC_FP_DEBUG_0_TMDS_ENABLED |
			   NV_PRAMDAC_FP_DEBUG_0_YSCALE_ENABLE |
			   NV_PRAMDAC_FP_DEBUG_0_XSCALE_ENABLE;

	/* We want स्वतःmatic scaling */
	regp->fp_debug_1 = 0;
	/* This can override HTOTAL and VTOTAL */
	regp->fp_debug_2 = 0;

	/* Use 20.12 fixed poपूर्णांक क्रमmat to aव्योम भग्नs */
	mode_ratio = (1 << 12) * adjusted_mode->hdisplay / adjusted_mode->vdisplay;
	panel_ratio = (1 << 12) * output_mode->hdisplay / output_mode->vdisplay;
	/* अगर ratios are equal, SCALE_ASPECT will स्वतःmatically (and correctly)
	 * get treated the same as SCALE_FULLSCREEN */
	अगर (nv_connector->scaling_mode == DRM_MODE_SCALE_ASPECT &&
	    mode_ratio != panel_ratio) अणु
		uपूर्णांक32_t dअगरf, scale;
		bool भागide_by_2 = nv_gf4_disp_arch(dev);

		अगर (mode_ratio < panel_ratio) अणु
			/* vertical needs to expand to glass size (स्वतःmatic)
			 * horizontal needs to be scaled at vertical scale factor
			 * to मुख्यtain aspect */

			scale = (1 << 12) * adjusted_mode->vdisplay / output_mode->vdisplay;
			regp->fp_debug_1 = NV_PRAMDAC_FP_DEBUG_1_XSCALE_TESTMODE_ENABLE |
					   XLATE(scale, भागide_by_2, NV_PRAMDAC_FP_DEBUG_1_XSCALE_VALUE);

			/* restrict area of screen used, horizontally */
			dअगरf = output_mode->hdisplay -
			       output_mode->vdisplay * mode_ratio / (1 << 12);
			regp->fp_horiz_regs[FP_VALID_START] += dअगरf / 2;
			regp->fp_horiz_regs[FP_VALID_END] -= dअगरf / 2;
		पूर्ण

		अगर (mode_ratio > panel_ratio) अणु
			/* horizontal needs to expand to glass size (स्वतःmatic)
			 * vertical needs to be scaled at horizontal scale factor
			 * to मुख्यtain aspect */

			scale = (1 << 12) * adjusted_mode->hdisplay / output_mode->hdisplay;
			regp->fp_debug_1 = NV_PRAMDAC_FP_DEBUG_1_YSCALE_TESTMODE_ENABLE |
					   XLATE(scale, भागide_by_2, NV_PRAMDAC_FP_DEBUG_1_YSCALE_VALUE);

			/* restrict area of screen used, vertically */
			dअगरf = output_mode->vdisplay -
			       (1 << 12) * output_mode->hdisplay / mode_ratio;
			regp->fp_vert_regs[FP_VALID_START] += dअगरf / 2;
			regp->fp_vert_regs[FP_VALID_END] -= dअगरf / 2;
		पूर्ण
	पूर्ण

	/* Output property. */
	अगर ((nv_connector->dithering_mode == DITHERING_MODE_ON) ||
	    (nv_connector->dithering_mode == DITHERING_MODE_AUTO &&
	     fb->क्रमmat->depth > connector->display_info.bpc * 3)) अणु
		अगर (drm->client.device.info.chipset == 0x11)
			regp->dither = savep->dither | 0x00010000;
		अन्यथा अणु
			पूर्णांक i;
			regp->dither = savep->dither | 0x00000001;
			क्रम (i = 0; i < 3; i++) अणु
				regp->dither_regs[i] = 0xe4e4e4e4;
				regp->dither_regs[i + 3] = 0x44444444;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (drm->client.device.info.chipset != 0x11) अणु
			/* reset them */
			पूर्णांक i;
			क्रम (i = 0; i < 3; i++) अणु
				regp->dither_regs[i] = savep->dither_regs[i];
				regp->dither_regs[i + 3] = savep->dither_regs[i + 3];
			पूर्ण
		पूर्ण
		regp->dither = savep->dither;
	पूर्ण

	regp->fp_margin_color = 0;
पूर्ण

अटल व्योम nv04_dfp_commit(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	स्थिर काष्ठा drm_encoder_helper_funcs *helper = encoder->helper_निजी;
	काष्ठा nouveau_crtc *nv_crtc = nouveau_crtc(encoder->crtc);
	काष्ठा nouveau_encoder *nv_encoder = nouveau_encoder(encoder);
	काष्ठा dcb_output *dcbe = nv_encoder->dcb;
	पूर्णांक head = nouveau_crtc(encoder->crtc)->index;
	काष्ठा drm_encoder *slave_encoder;

	अगर (dcbe->type == DCB_OUTPUT_TMDS)
		run_पंचांगds_table(dev, dcbe, head, nv_encoder->mode.घड़ी);
	अन्यथा अगर (dcbe->type == DCB_OUTPUT_LVDS)
		call_lvds_script(dev, dcbe, head, LVDS_RESET, nv_encoder->mode.घड़ी);

	/* update fp_control state क्रम any changes made by scripts,
	 * so correct value is written at DPMS on */
	nv04_display(dev)->mode_reg.crtc_reg[head].fp_control =
		NVReadRAMDAC(dev, head, NV_PRAMDAC_FP_TG_CONTROL);

	/* This could use refinement क्रम flatpanels, but it should work this way */
	अगर (drm->client.device.info.chipset < 0x44)
		NVWriteRAMDAC(dev, 0, NV_PRAMDAC_TEST_CONTROL + nv04_dac_output_offset(encoder), 0xf0000000);
	अन्यथा
		NVWriteRAMDAC(dev, 0, NV_PRAMDAC_TEST_CONTROL + nv04_dac_output_offset(encoder), 0x00100000);

	/* Init बाह्यal transmitters */
	slave_encoder = get_पंचांगds_slave(encoder);
	अगर (slave_encoder)
		get_slave_funcs(slave_encoder)->mode_set(
			slave_encoder, &nv_encoder->mode, &nv_encoder->mode);

	helper->dpms(encoder, DRM_MODE_DPMS_ON);

	NV_DEBUG(drm, "Output %s is running on CRTC %d using output %c\n",
		 nv04_encoder_get_connector(nv_encoder)->base.name,
		 nv_crtc->index, '@' + ffs(nv_encoder->dcb->or));
पूर्ण

अटल व्योम nv04_dfp_update_backlight(काष्ठा drm_encoder *encoder, पूर्णांक mode)
अणु
#अगर_घोषित __घातerpc__
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा nvअगर_object *device = &nouveau_drm(dev)->client.device.object;
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);

	/* BIOS scripts usually take care of the backlight, thanks
	 * Apple क्रम your consistency.
	 */
	अगर (pdev->device == 0x0174 || pdev->device == 0x0179 ||
	    pdev->device == 0x0189 || pdev->device == 0x0329) अणु
		अगर (mode == DRM_MODE_DPMS_ON) अणु
			nvअगर_mask(device, NV_PBUS_DEBUG_DUALHEAD_CTL, 1 << 31, 1 << 31);
			nvअगर_mask(device, NV_PCRTC_GPIO_EXT, 3, 1);
		पूर्ण अन्यथा अणु
			nvअगर_mask(device, NV_PBUS_DEBUG_DUALHEAD_CTL, 1 << 31, 0);
			nvअगर_mask(device, NV_PCRTC_GPIO_EXT, 3, 0);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत bool is_घातersaving_dpms(पूर्णांक mode)
अणु
	वापस mode != DRM_MODE_DPMS_ON && mode != NV_DPMS_CLEARED;
पूर्ण

अटल व्योम nv04_lvds_dpms(काष्ठा drm_encoder *encoder, पूर्णांक mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा drm_crtc *crtc = encoder->crtc;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nouveau_encoder *nv_encoder = nouveau_encoder(encoder);
	bool was_घातersaving = is_घातersaving_dpms(nv_encoder->last_dpms);

	अगर (nv_encoder->last_dpms == mode)
		वापस;
	nv_encoder->last_dpms = mode;

	NV_DEBUG(drm, "Setting dpms mode %d on lvds encoder (output %d)\n",
		 mode, nv_encoder->dcb->index);

	अगर (was_घातersaving && is_घातersaving_dpms(mode))
		वापस;

	अगर (nv_encoder->dcb->lvdsconf.use_घातer_scripts) अणु
		/* when removing an output, crtc may not be set, but PANEL_OFF
		 * must still be run
		 */
		पूर्णांक head = crtc ? nouveau_crtc(crtc)->index :
			   nv04_dfp_get_bound_head(dev, nv_encoder->dcb);

		अगर (mode == DRM_MODE_DPMS_ON) अणु
			call_lvds_script(dev, nv_encoder->dcb, head,
					 LVDS_PANEL_ON, nv_encoder->mode.घड़ी);
		पूर्ण अन्यथा
			/* pxclk of 0 is fine क्रम PANEL_OFF, and क्रम a
			 * disconnected LVDS encoder there is no native_mode
			 */
			call_lvds_script(dev, nv_encoder->dcb, head,
					 LVDS_PANEL_OFF, 0);
	पूर्ण

	nv04_dfp_update_backlight(encoder, mode);
	nv04_dfp_update_fp_control(encoder, mode);

	अगर (mode == DRM_MODE_DPMS_ON)
		nv04_dfp_prepare_sel_clk(dev, nv_encoder, nouveau_crtc(crtc)->index);
	अन्यथा अणु
		nv04_display(dev)->mode_reg.sel_clk = NVReadRAMDAC(dev, 0, NV_PRAMDAC_SEL_CLK);
		nv04_display(dev)->mode_reg.sel_clk &= ~0xf0;
	पूर्ण
	NVWriteRAMDAC(dev, 0, NV_PRAMDAC_SEL_CLK, nv04_display(dev)->mode_reg.sel_clk);
पूर्ण

अटल व्योम nv04_पंचांगds_dpms(काष्ठा drm_encoder *encoder, पूर्णांक mode)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(encoder->dev);
	काष्ठा nouveau_encoder *nv_encoder = nouveau_encoder(encoder);

	अगर (nv_encoder->last_dpms == mode)
		वापस;
	nv_encoder->last_dpms = mode;

	NV_DEBUG(drm, "Setting dpms mode %d on tmds encoder (output %d)\n",
		 mode, nv_encoder->dcb->index);

	nv04_dfp_update_backlight(encoder, mode);
	nv04_dfp_update_fp_control(encoder, mode);
पूर्ण

अटल व्योम nv04_dfp_save(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा nouveau_encoder *nv_encoder = nouveau_encoder(encoder);
	काष्ठा drm_device *dev = encoder->dev;

	अगर (nv_two_heads(dev))
		nv_encoder->restore.head =
			nv04_dfp_get_bound_head(dev, nv_encoder->dcb);
पूर्ण

अटल व्योम nv04_dfp_restore(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा nouveau_encoder *nv_encoder = nouveau_encoder(encoder);
	काष्ठा drm_device *dev = encoder->dev;
	पूर्णांक head = nv_encoder->restore.head;

	अगर (nv_encoder->dcb->type == DCB_OUTPUT_LVDS) अणु
		काष्ठा nouveau_connector *connector =
			nv04_encoder_get_connector(nv_encoder);

		अगर (connector && connector->native_mode)
			call_lvds_script(dev, nv_encoder->dcb, head,
					 LVDS_PANEL_ON,
					 connector->native_mode->घड़ी);

	पूर्ण अन्यथा अगर (nv_encoder->dcb->type == DCB_OUTPUT_TMDS) अणु
		पूर्णांक घड़ी = nouveau_hw_pllvals_to_clk
					(&nv04_display(dev)->saved_reg.crtc_reg[head].pllvals);

		run_पंचांगds_table(dev, nv_encoder->dcb, head, घड़ी);
	पूर्ण

	nv_encoder->last_dpms = NV_DPMS_CLEARED;
पूर्ण

अटल व्योम nv04_dfp_destroy(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा nouveau_encoder *nv_encoder = nouveau_encoder(encoder);

	अगर (get_slave_funcs(encoder))
		get_slave_funcs(encoder)->destroy(encoder);

	drm_encoder_cleanup(encoder);
	kमुक्त(nv_encoder);
पूर्ण

अटल व्योम nv04_पंचांगds_slave_init(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा dcb_output *dcb = nouveau_encoder(encoder)->dcb;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvkm_i2c *i2c = nvxx_i2c(&drm->client.device);
	काष्ठा nvkm_i2c_bus *bus = nvkm_i2c_bus_find(i2c, NVKM_I2C_BUS_PRI);
	काष्ठा nvkm_i2c_bus_probe info[] = अणु
		अणु
		    अणु
		        .type = "sil164",
		        .addr = (dcb->पंचांगdsconf.slave_addr == 0x7 ? 0x3a : 0x38),
		        .platक्रमm_data = &(काष्ठा sil164_encoder_params) अणु
		            SIL164_INPUT_EDGE_RISING
		         पूर्ण
		    पूर्ण, 0
		पूर्ण,
		अणु पूर्ण
	पूर्ण;
	पूर्णांक type;

	अगर (!nv_gf4_disp_arch(dev) || !bus || get_पंचांगds_slave(encoder))
		वापस;

	type = nvkm_i2c_bus_probe(bus, "TMDS transmitter", info, शून्य, शून्य);
	अगर (type < 0)
		वापस;

	drm_i2c_encoder_init(dev, to_encoder_slave(encoder),
			     &bus->i2c, &info[type].dev);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs nv04_lvds_helper_funcs = अणु
	.dpms = nv04_lvds_dpms,
	.mode_fixup = nv04_dfp_mode_fixup,
	.prepare = nv04_dfp_prepare,
	.commit = nv04_dfp_commit,
	.mode_set = nv04_dfp_mode_set,
	.detect = शून्य,
पूर्ण;

अटल स्थिर काष्ठा drm_encoder_helper_funcs nv04_पंचांगds_helper_funcs = अणु
	.dpms = nv04_पंचांगds_dpms,
	.mode_fixup = nv04_dfp_mode_fixup,
	.prepare = nv04_dfp_prepare,
	.commit = nv04_dfp_commit,
	.mode_set = nv04_dfp_mode_set,
	.detect = शून्य,
पूर्ण;

अटल स्थिर काष्ठा drm_encoder_funcs nv04_dfp_funcs = अणु
	.destroy = nv04_dfp_destroy,
पूर्ण;

पूर्णांक
nv04_dfp_create(काष्ठा drm_connector *connector, काष्ठा dcb_output *entry)
अणु
	स्थिर काष्ठा drm_encoder_helper_funcs *helper;
	काष्ठा nouveau_encoder *nv_encoder = शून्य;
	काष्ठा drm_encoder *encoder;
	पूर्णांक type;

	चयन (entry->type) अणु
	हाल DCB_OUTPUT_TMDS:
		type = DRM_MODE_ENCODER_TMDS;
		helper = &nv04_पंचांगds_helper_funcs;
		अवरोध;
	हाल DCB_OUTPUT_LVDS:
		type = DRM_MODE_ENCODER_LVDS;
		helper = &nv04_lvds_helper_funcs;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	nv_encoder = kzalloc(माप(*nv_encoder), GFP_KERNEL);
	अगर (!nv_encoder)
		वापस -ENOMEM;

	nv_encoder->enc_save = nv04_dfp_save;
	nv_encoder->enc_restore = nv04_dfp_restore;

	encoder = to_drm_encoder(nv_encoder);

	nv_encoder->dcb = entry;
	nv_encoder->or = ffs(entry->or) - 1;

	drm_encoder_init(connector->dev, encoder, &nv04_dfp_funcs, type, शून्य);
	drm_encoder_helper_add(encoder, helper);

	encoder->possible_crtcs = entry->heads;
	encoder->possible_clones = 0;

	अगर (entry->type == DCB_OUTPUT_TMDS &&
	    entry->location != DCB_LOC_ON_CHIP)
		nv04_पंचांगds_slave_init(encoder);

	drm_connector_attach_encoder(connector, encoder);
	वापस 0;
पूर्ण
