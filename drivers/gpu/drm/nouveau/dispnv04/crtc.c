<शैली गुरु>
/*
 * Copyright 1993-2003 NVIDIA, Corporation
 * Copyright 2006 Dave Airlie
 * Copyright 2007 Maarten Maathuis
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
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "nouveau_drv.h"
#समावेश "nouveau_reg.h"
#समावेश "nouveau_ttm.h"
#समावेश "nouveau_bo.h"
#समावेश "nouveau_gem.h"
#समावेश "nouveau_encoder.h"
#समावेश "nouveau_connector.h"
#समावेश "nouveau_crtc.h"
#समावेश "hw.h"
#समावेश "nvreg.h"
#समावेश "nouveau_fbcon.h"
#समावेश "disp.h"
#समावेश "nouveau_dma.h"

#समावेश <subdev/bios/pll.h>
#समावेश <subdev/clk.h>

#समावेश <nvअगर/push006c.h>

#समावेश <nvअगर/event.h>
#समावेश <nvअगर/cl0046.h>

अटल पूर्णांक
nv04_crtc_mode_set_base(काष्ठा drm_crtc *crtc, पूर्णांक x, पूर्णांक y,
			काष्ठा drm_framebuffer *old_fb);

अटल व्योम
crtc_wr_cio_state(काष्ठा drm_crtc *crtc, काष्ठा nv04_crtc_reg *crtcstate, पूर्णांक index)
अणु
	NVWriteVgaCrtc(crtc->dev, nouveau_crtc(crtc)->index, index,
		       crtcstate->CRTC[index]);
पूर्ण

अटल व्योम nv_crtc_set_digital_vibrance(काष्ठा drm_crtc *crtc, पूर्णांक level)
अणु
	काष्ठा nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा nv04_crtc_reg *regp = &nv04_display(dev)->mode_reg.crtc_reg[nv_crtc->index];

	regp->CRTC[NV_CIO_CRE_CSB] = nv_crtc->saturation = level;
	अगर (nv_crtc->saturation && nv_gf4_disp_arch(crtc->dev)) अणु
		regp->CRTC[NV_CIO_CRE_CSB] = 0x80;
		regp->CRTC[NV_CIO_CRE_5B] = nv_crtc->saturation << 2;
		crtc_wr_cio_state(crtc, regp, NV_CIO_CRE_5B);
	पूर्ण
	crtc_wr_cio_state(crtc, regp, NV_CIO_CRE_CSB);
पूर्ण

अटल व्योम nv_crtc_set_image_sharpening(काष्ठा drm_crtc *crtc, पूर्णांक level)
अणु
	काष्ठा nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा nv04_crtc_reg *regp = &nv04_display(dev)->mode_reg.crtc_reg[nv_crtc->index];

	nv_crtc->sharpness = level;
	अगर (level < 0)	/* blur is in hw range 0x3f -> 0x20 */
		level += 0x40;
	regp->ramdac_634 = level;
	NVWriteRAMDAC(crtc->dev, nv_crtc->index, NV_PRAMDAC_634, regp->ramdac_634);
पूर्ण

#घोषणा PLLSEL_VPLL1_MASK				\
	(NV_PRAMDAC_PLL_COEFF_SELECT_SOURCE_PROG_VPLL	\
	 | NV_PRAMDAC_PLL_COEFF_SELECT_VCLK_RATIO_DB2)
#घोषणा PLLSEL_VPLL2_MASK				\
	(NV_PRAMDAC_PLL_COEFF_SELECT_PLL_SOURCE_VPLL2		\
	 | NV_PRAMDAC_PLL_COEFF_SELECT_VCLK2_RATIO_DB2)
#घोषणा PLLSEL_TV_MASK					\
	(NV_PRAMDAC_PLL_COEFF_SELECT_TV_VSCLK1		\
	 | NV_PRAMDAC_PLL_COEFF_SELECT_TV_PCLK1		\
	 | NV_PRAMDAC_PLL_COEFF_SELECT_TV_VSCLK2	\
	 | NV_PRAMDAC_PLL_COEFF_SELECT_TV_PCLK2)

/* NV4x 0x40.. pll notes:
 * gpu pll: 0x4000 + 0x4004
 * ?gpu? pll: 0x4008 + 0x400c
 * vpll1: 0x4010 + 0x4014
 * vpll2: 0x4018 + 0x401c
 * mpll: 0x4020 + 0x4024
 * mpll: 0x4038 + 0x403c
 *
 * the first रेजिस्टर of each pair has some unknown details:
 * bits 0-7: redirected values from अन्यथाwhere? (similar to PLL_SETUP_CONTROL?)
 * bits 20-23: (mpll) something to करो with post भागider?
 * bits 28-31: related to single stage mode? (bit 8/12)
 */

अटल व्योम nv_crtc_calc_state_ext(काष्ठा drm_crtc *crtc, काष्ठा drm_display_mode * mode, पूर्णांक करोt_घड़ी)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvkm_bios *bios = nvxx_bios(&drm->client.device);
	काष्ठा nvkm_clk *clk = nvxx_clk(&drm->client.device);
	काष्ठा nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
	काष्ठा nv04_mode_state *state = &nv04_display(dev)->mode_reg;
	काष्ठा nv04_crtc_reg *regp = &state->crtc_reg[nv_crtc->index];
	काष्ठा nvkm_pll_vals *pv = &regp->pllvals;
	काष्ठा nvbios_pll pll_lim;

	अगर (nvbios_pll_parse(bios, nv_crtc->index ? PLL_VPLL1 : PLL_VPLL0,
			    &pll_lim))
		वापस;

	/* NM2 == 0 is used to determine single stage mode on two stage plls */
	pv->NM2 = 0;

	/* क्रम newer nv4x the blob uses only the first stage of the vpll below a
	 * certain घड़ी.  क्रम a certain nv4b this is 150MHz.  since the max
	 * output frequency of the first stage क्रम this card is 300MHz, it is
	 * assumed the threshold is given by vco1 maxfreq/2
	 */
	/* क्रम early nv4x, specअगरically nv40 and *some* nv43 (devids 0 and 6,
	 * not 8, others unknown), the blob always uses both plls.  no problem
	 * has yet been observed in allowing the use a single stage pll on all
	 * nv43 however.  the behaviour of single stage use is untested on nv40
	 */
	अगर (drm->client.device.info.chipset > 0x40 && करोt_घड़ी <= (pll_lim.vco1.max_freq / 2))
		स_रखो(&pll_lim.vco2, 0, माप(pll_lim.vco2));


	अगर (!clk->pll_calc(clk, &pll_lim, करोt_घड़ी, pv))
		वापस;

	state->pllsel &= PLLSEL_VPLL1_MASK | PLLSEL_VPLL2_MASK | PLLSEL_TV_MASK;

	/* The blob uses this always, so let's करो the same */
	अगर (drm->client.device.info.family == NV_DEVICE_INFO_V0_CURIE)
		state->pllsel |= NV_PRAMDAC_PLL_COEFF_SELECT_USE_VPLL2_TRUE;
	/* again nv40 and some nv43 act more like nv3x as described above */
	अगर (drm->client.device.info.chipset < 0x41)
		state->pllsel |= NV_PRAMDAC_PLL_COEFF_SELECT_SOURCE_PROG_MPLL |
				 NV_PRAMDAC_PLL_COEFF_SELECT_SOURCE_PROG_NVPLL;
	state->pllsel |= nv_crtc->index ? PLLSEL_VPLL2_MASK : PLLSEL_VPLL1_MASK;

	अगर (pv->NM2)
		NV_DEBUG(drm, "vpll: n1 %d n2 %d m1 %d m2 %d log2p %d\n",
			 pv->N1, pv->N2, pv->M1, pv->M2, pv->log2P);
	अन्यथा
		NV_DEBUG(drm, "vpll: n %d m %d log2p %d\n",
			 pv->N1, pv->M1, pv->log2P);

	nv_crtc->cursor.set_offset(nv_crtc, nv_crtc->cursor.offset);
पूर्ण

अटल व्योम
nv_crtc_dpms(काष्ठा drm_crtc *crtc, पूर्णांक mode)
अणु
	काष्ठा nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	अचिन्हित अक्षर seq1 = 0, crtc17 = 0;
	अचिन्हित अक्षर crtc1A;

	NV_DEBUG(drm, "Setting dpms mode %d on CRTC %d\n", mode,
							nv_crtc->index);

	अगर (nv_crtc->last_dpms == mode) /* Don't करो unnecessary mode changes. */
		वापस;

	nv_crtc->last_dpms = mode;

	अगर (nv_two_heads(dev))
		NVSetOwner(dev, nv_crtc->index);

	/* nv4ref indicates these two RPC1 bits inhibit h/v sync */
	crtc1A = NVReadVgaCrtc(dev, nv_crtc->index,
					NV_CIO_CRE_RPC1_INDEX) & ~0xC0;
	चयन (mode) अणु
	हाल DRM_MODE_DPMS_STANDBY:
		/* Screen: Off; HSync: Off, VSync: On -- Not Supported */
		seq1 = 0x20;
		crtc17 = 0x80;
		crtc1A |= 0x80;
		अवरोध;
	हाल DRM_MODE_DPMS_SUSPEND:
		/* Screen: Off; HSync: On, VSync: Off -- Not Supported */
		seq1 = 0x20;
		crtc17 = 0x80;
		crtc1A |= 0x40;
		अवरोध;
	हाल DRM_MODE_DPMS_OFF:
		/* Screen: Off; HSync: Off, VSync: Off */
		seq1 = 0x20;
		crtc17 = 0x00;
		crtc1A |= 0xC0;
		अवरोध;
	हाल DRM_MODE_DPMS_ON:
	शेष:
		/* Screen: On; HSync: On, VSync: On */
		seq1 = 0x00;
		crtc17 = 0x80;
		अवरोध;
	पूर्ण

	NVVgaSeqReset(dev, nv_crtc->index, true);
	/* Each head has it's own sequencer, so we can turn it off when we want */
	seq1 |= (NVReadVgaSeq(dev, nv_crtc->index, NV_VIO_SR_CLOCK_INDEX) & ~0x20);
	NVWriteVgaSeq(dev, nv_crtc->index, NV_VIO_SR_CLOCK_INDEX, seq1);
	crtc17 |= (NVReadVgaCrtc(dev, nv_crtc->index, NV_CIO_CR_MODE_INDEX) & ~0x80);
	mdelay(10);
	NVWriteVgaCrtc(dev, nv_crtc->index, NV_CIO_CR_MODE_INDEX, crtc17);
	NVVgaSeqReset(dev, nv_crtc->index, false);

	NVWriteVgaCrtc(dev, nv_crtc->index, NV_CIO_CRE_RPC1_INDEX, crtc1A);
पूर्ण

अटल व्योम
nv_crtc_mode_set_vga(काष्ठा drm_crtc *crtc, काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
	काष्ठा nv04_crtc_reg *regp = &nv04_display(dev)->mode_reg.crtc_reg[nv_crtc->index];
	काष्ठा drm_framebuffer *fb = crtc->primary->fb;

	/* Calculate our timings */
	पूर्णांक horizDisplay	= (mode->crtc_hdisplay >> 3)		- 1;
	पूर्णांक horizStart		= (mode->crtc_hsync_start >> 3) 	+ 1;
	पूर्णांक horizEnd		= (mode->crtc_hsync_end >> 3)		+ 1;
	पूर्णांक horizTotal		= (mode->crtc_htotal >> 3)		- 5;
	पूर्णांक horizBlankStart	= (mode->crtc_hdisplay >> 3)		- 1;
	पूर्णांक horizBlankEnd	= (mode->crtc_htotal >> 3)		- 1;
	पूर्णांक vertDisplay		= mode->crtc_vdisplay			- 1;
	पूर्णांक vertStart		= mode->crtc_vsync_start 		- 1;
	पूर्णांक vertEnd		= mode->crtc_vsync_end			- 1;
	पूर्णांक vertTotal		= mode->crtc_vtotal 			- 2;
	पूर्णांक vertBlankStart	= mode->crtc_vdisplay 			- 1;
	पूर्णांक vertBlankEnd	= mode->crtc_vtotal			- 1;

	काष्ठा drm_encoder *encoder;
	bool fp_output = false;

	list_क्रम_each_entry(encoder, &dev->mode_config.encoder_list, head) अणु
		काष्ठा nouveau_encoder *nv_encoder = nouveau_encoder(encoder);

		अगर (encoder->crtc == crtc &&
		    (nv_encoder->dcb->type == DCB_OUTPUT_LVDS ||
		     nv_encoder->dcb->type == DCB_OUTPUT_TMDS))
			fp_output = true;
	पूर्ण

	अगर (fp_output) अणु
		vertStart = vertTotal - 3;
		vertEnd = vertTotal - 2;
		vertBlankStart = vertStart;
		horizStart = horizTotal - 5;
		horizEnd = horizTotal - 2;
		horizBlankEnd = horizTotal + 4;
#अगर 0
		अगर (dev->overlayAdaptor && drm->client.device.info.family >= NV_DEVICE_INFO_V0_CELSIUS)
			/* This reportedly works around some video overlay bandwidth problems */
			horizTotal += 2;
#पूर्ण_अगर
	पूर्ण

	अगर (mode->flags & DRM_MODE_FLAG_INTERLACE)
		vertTotal |= 1;

#अगर 0
	ErrorF("horizDisplay: 0x%X \n", horizDisplay);
	ErrorF("horizStart: 0x%X \n", horizStart);
	ErrorF("horizEnd: 0x%X \n", horizEnd);
	ErrorF("horizTotal: 0x%X \n", horizTotal);
	ErrorF("horizBlankStart: 0x%X \n", horizBlankStart);
	ErrorF("horizBlankEnd: 0x%X \n", horizBlankEnd);
	ErrorF("vertDisplay: 0x%X \n", vertDisplay);
	ErrorF("vertStart: 0x%X \n", vertStart);
	ErrorF("vertEnd: 0x%X \n", vertEnd);
	ErrorF("vertTotal: 0x%X \n", vertTotal);
	ErrorF("vertBlankStart: 0x%X \n", vertBlankStart);
	ErrorF("vertBlankEnd: 0x%X \n", vertBlankEnd);
#पूर्ण_अगर

	/*
	* compute correct Hsync & Vsync polarity
	*/
	अगर ((mode->flags & (DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NHSYNC))
		&& (mode->flags & (DRM_MODE_FLAG_PVSYNC | DRM_MODE_FLAG_NVSYNC))) अणु

		regp->MiscOutReg = 0x23;
		अगर (mode->flags & DRM_MODE_FLAG_NHSYNC)
			regp->MiscOutReg |= 0x40;
		अगर (mode->flags & DRM_MODE_FLAG_NVSYNC)
			regp->MiscOutReg |= 0x80;
	पूर्ण अन्यथा अणु
		पूर्णांक vdisplay = mode->vdisplay;
		अगर (mode->flags & DRM_MODE_FLAG_DBLSCAN)
			vdisplay *= 2;
		अगर (mode->vscan > 1)
			vdisplay *= mode->vscan;
		अगर (vdisplay < 400)
			regp->MiscOutReg = 0xA3;	/* +hsync -vsync */
		अन्यथा अगर (vdisplay < 480)
			regp->MiscOutReg = 0x63;	/* -hsync +vsync */
		अन्यथा अगर (vdisplay < 768)
			regp->MiscOutReg = 0xE3;	/* -hsync -vsync */
		अन्यथा
			regp->MiscOutReg = 0x23;	/* +hsync +vsync */
	पूर्ण

	/*
	 * Time Sequencer
	 */
	regp->Sequencer[NV_VIO_SR_RESET_INDEX] = 0x00;
	/* 0x20 disables the sequencer */
	अगर (mode->flags & DRM_MODE_FLAG_CLKDIV2)
		regp->Sequencer[NV_VIO_SR_CLOCK_INDEX] = 0x29;
	अन्यथा
		regp->Sequencer[NV_VIO_SR_CLOCK_INDEX] = 0x21;
	regp->Sequencer[NV_VIO_SR_PLANE_MASK_INDEX] = 0x0F;
	regp->Sequencer[NV_VIO_SR_CHAR_MAP_INDEX] = 0x00;
	regp->Sequencer[NV_VIO_SR_MEM_MODE_INDEX] = 0x0E;

	/*
	 * CRTC
	 */
	regp->CRTC[NV_CIO_CR_HDT_INDEX] = horizTotal;
	regp->CRTC[NV_CIO_CR_HDE_INDEX] = horizDisplay;
	regp->CRTC[NV_CIO_CR_HBS_INDEX] = horizBlankStart;
	regp->CRTC[NV_CIO_CR_HBE_INDEX] = (1 << 7) |
					  XLATE(horizBlankEnd, 0, NV_CIO_CR_HBE_4_0);
	regp->CRTC[NV_CIO_CR_HRS_INDEX] = horizStart;
	regp->CRTC[NV_CIO_CR_HRE_INDEX] = XLATE(horizBlankEnd, 5, NV_CIO_CR_HRE_HBE_5) |
					  XLATE(horizEnd, 0, NV_CIO_CR_HRE_4_0);
	regp->CRTC[NV_CIO_CR_VDT_INDEX] = vertTotal;
	regp->CRTC[NV_CIO_CR_OVL_INDEX] = XLATE(vertStart, 9, NV_CIO_CR_OVL_VRS_9) |
					  XLATE(vertDisplay, 9, NV_CIO_CR_OVL_VDE_9) |
					  XLATE(vertTotal, 9, NV_CIO_CR_OVL_VDT_9) |
					  (1 << 4) |
					  XLATE(vertBlankStart, 8, NV_CIO_CR_OVL_VBS_8) |
					  XLATE(vertStart, 8, NV_CIO_CR_OVL_VRS_8) |
					  XLATE(vertDisplay, 8, NV_CIO_CR_OVL_VDE_8) |
					  XLATE(vertTotal, 8, NV_CIO_CR_OVL_VDT_8);
	regp->CRTC[NV_CIO_CR_RSAL_INDEX] = 0x00;
	regp->CRTC[NV_CIO_CR_CELL_HT_INDEX] = ((mode->flags & DRM_MODE_FLAG_DBLSCAN) ? MASK(NV_CIO_CR_CELL_HT_SCANDBL) : 0) |
					      1 << 6 |
					      XLATE(vertBlankStart, 9, NV_CIO_CR_CELL_HT_VBS_9);
	regp->CRTC[NV_CIO_CR_CURS_ST_INDEX] = 0x00;
	regp->CRTC[NV_CIO_CR_CURS_END_INDEX] = 0x00;
	regp->CRTC[NV_CIO_CR_SA_HI_INDEX] = 0x00;
	regp->CRTC[NV_CIO_CR_SA_LO_INDEX] = 0x00;
	regp->CRTC[NV_CIO_CR_TCOFF_HI_INDEX] = 0x00;
	regp->CRTC[NV_CIO_CR_TCOFF_LO_INDEX] = 0x00;
	regp->CRTC[NV_CIO_CR_VRS_INDEX] = vertStart;
	regp->CRTC[NV_CIO_CR_VRE_INDEX] = 1 << 5 | XLATE(vertEnd, 0, NV_CIO_CR_VRE_3_0);
	regp->CRTC[NV_CIO_CR_VDE_INDEX] = vertDisplay;
	/* framebuffer can be larger than crtc scanout area. */
	regp->CRTC[NV_CIO_CR_OFFSET_INDEX] = fb->pitches[0] / 8;
	regp->CRTC[NV_CIO_CR_ULINE_INDEX] = 0x00;
	regp->CRTC[NV_CIO_CR_VBS_INDEX] = vertBlankStart;
	regp->CRTC[NV_CIO_CR_VBE_INDEX] = vertBlankEnd;
	regp->CRTC[NV_CIO_CR_MODE_INDEX] = 0x43;
	regp->CRTC[NV_CIO_CR_LCOMP_INDEX] = 0xff;

	/*
	 * Some extended CRTC रेजिस्टरs (they are not saved with the rest of the vga regs).
	 */

	/* framebuffer can be larger than crtc scanout area. */
	regp->CRTC[NV_CIO_CRE_RPC0_INDEX] =
		XLATE(fb->pitches[0] / 8, 8, NV_CIO_CRE_RPC0_OFFSET_10_8);
	regp->CRTC[NV_CIO_CRE_42] =
		XLATE(fb->pitches[0] / 8, 11, NV_CIO_CRE_42_OFFSET_11);
	regp->CRTC[NV_CIO_CRE_RPC1_INDEX] = mode->crtc_hdisplay < 1280 ?
					    MASK(NV_CIO_CRE_RPC1_LARGE) : 0x00;
	regp->CRTC[NV_CIO_CRE_LSR_INDEX] = XLATE(horizBlankEnd, 6, NV_CIO_CRE_LSR_HBE_6) |
					   XLATE(vertBlankStart, 10, NV_CIO_CRE_LSR_VBS_10) |
					   XLATE(vertStart, 10, NV_CIO_CRE_LSR_VRS_10) |
					   XLATE(vertDisplay, 10, NV_CIO_CRE_LSR_VDE_10) |
					   XLATE(vertTotal, 10, NV_CIO_CRE_LSR_VDT_10);
	regp->CRTC[NV_CIO_CRE_HEB__INDEX] = XLATE(horizStart, 8, NV_CIO_CRE_HEB_HRS_8) |
					    XLATE(horizBlankStart, 8, NV_CIO_CRE_HEB_HBS_8) |
					    XLATE(horizDisplay, 8, NV_CIO_CRE_HEB_HDE_8) |
					    XLATE(horizTotal, 8, NV_CIO_CRE_HEB_HDT_8);
	regp->CRTC[NV_CIO_CRE_EBR_INDEX] = XLATE(vertBlankStart, 11, NV_CIO_CRE_EBR_VBS_11) |
					   XLATE(vertStart, 11, NV_CIO_CRE_EBR_VRS_11) |
					   XLATE(vertDisplay, 11, NV_CIO_CRE_EBR_VDE_11) |
					   XLATE(vertTotal, 11, NV_CIO_CRE_EBR_VDT_11);

	अगर (mode->flags & DRM_MODE_FLAG_INTERLACE) अणु
		horizTotal = (horizTotal >> 1) & ~1;
		regp->CRTC[NV_CIO_CRE_ILACE__INDEX] = horizTotal;
		regp->CRTC[NV_CIO_CRE_HEB__INDEX] |= XLATE(horizTotal, 8, NV_CIO_CRE_HEB_ILC_8);
	पूर्ण अन्यथा
		regp->CRTC[NV_CIO_CRE_ILACE__INDEX] = 0xff;  /* पूर्णांकerlace off */

	/*
	* Graphics Display Controller
	*/
	regp->Graphics[NV_VIO_GX_SR_INDEX] = 0x00;
	regp->Graphics[NV_VIO_GX_SREN_INDEX] = 0x00;
	regp->Graphics[NV_VIO_GX_CCOMP_INDEX] = 0x00;
	regp->Graphics[NV_VIO_GX_ROP_INDEX] = 0x00;
	regp->Graphics[NV_VIO_GX_READ_MAP_INDEX] = 0x00;
	regp->Graphics[NV_VIO_GX_MODE_INDEX] = 0x40; /* 256 color mode */
	regp->Graphics[NV_VIO_GX_MISC_INDEX] = 0x05; /* map 64k mem + graphic mode */
	regp->Graphics[NV_VIO_GX_DONT_CARE_INDEX] = 0x0F;
	regp->Graphics[NV_VIO_GX_BIT_MASK_INDEX] = 0xFF;

	regp->Attribute[0]  = 0x00; /* standard colormap translation */
	regp->Attribute[1]  = 0x01;
	regp->Attribute[2]  = 0x02;
	regp->Attribute[3]  = 0x03;
	regp->Attribute[4]  = 0x04;
	regp->Attribute[5]  = 0x05;
	regp->Attribute[6]  = 0x06;
	regp->Attribute[7]  = 0x07;
	regp->Attribute[8]  = 0x08;
	regp->Attribute[9]  = 0x09;
	regp->Attribute[10] = 0x0A;
	regp->Attribute[11] = 0x0B;
	regp->Attribute[12] = 0x0C;
	regp->Attribute[13] = 0x0D;
	regp->Attribute[14] = 0x0E;
	regp->Attribute[15] = 0x0F;
	regp->Attribute[NV_CIO_AR_MODE_INDEX] = 0x01; /* Enable graphic mode */
	/* Non-vga */
	regp->Attribute[NV_CIO_AR_OSCAN_INDEX] = 0x00;
	regp->Attribute[NV_CIO_AR_PLANE_INDEX] = 0x0F; /* enable all color planes */
	regp->Attribute[NV_CIO_AR_HPP_INDEX] = 0x00;
	regp->Attribute[NV_CIO_AR_CSEL_INDEX] = 0x00;
पूर्ण

/**
 * Sets up रेजिस्टरs क्रम the given mode/adjusted_mode pair.
 *
 * The घड़ीs, CRTCs and outमाला_दो attached to this CRTC must be off.
 *
 * This shouldn't enable any घड़ीs, CRTCs, or outमाला_दो, but they should
 * be easily turned on/off after this.
 */
अटल व्योम
nv_crtc_mode_set_regs(काष्ठा drm_crtc *crtc, काष्ठा drm_display_mode * mode)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
	काष्ठा nv04_crtc_reg *regp = &nv04_display(dev)->mode_reg.crtc_reg[nv_crtc->index];
	काष्ठा nv04_crtc_reg *savep = &nv04_display(dev)->saved_reg.crtc_reg[nv_crtc->index];
	स्थिर काष्ठा drm_framebuffer *fb = crtc->primary->fb;
	काष्ठा drm_encoder *encoder;
	bool lvds_output = false, पंचांगds_output = false, tv_output = false,
		off_chip_digital = false;

	list_क्रम_each_entry(encoder, &dev->mode_config.encoder_list, head) अणु
		काष्ठा nouveau_encoder *nv_encoder = nouveau_encoder(encoder);
		bool digital = false;

		अगर (encoder->crtc != crtc)
			जारी;

		अगर (nv_encoder->dcb->type == DCB_OUTPUT_LVDS)
			digital = lvds_output = true;
		अगर (nv_encoder->dcb->type == DCB_OUTPUT_TV)
			tv_output = true;
		अगर (nv_encoder->dcb->type == DCB_OUTPUT_TMDS)
			digital = पंचांगds_output = true;
		अगर (nv_encoder->dcb->location != DCB_LOC_ON_CHIP && digital)
			off_chip_digital = true;
	पूर्ण

	/* Registers not directly related to the (s)vga mode */

	/* What is the meaning of this रेजिस्टर? */
	/* A few popular values are 0x18, 0x1c, 0x38, 0x3c */
	regp->CRTC[NV_CIO_CRE_ENH_INDEX] = savep->CRTC[NV_CIO_CRE_ENH_INDEX] & ~(1<<5);

	regp->crtc_eng_ctrl = 0;
	/* Except क्रम rare conditions I2C is enabled on the primary crtc */
	अगर (nv_crtc->index == 0)
		regp->crtc_eng_ctrl |= NV_CRTC_FSEL_I2C;
#अगर 0
	/* Set overlay to desired crtc. */
	अगर (dev->overlayAdaptor) अणु
		NVPortPrivPtr pPriv = GET_OVERLAY_PRIVATE(dev);
		अगर (pPriv->overlayCRTC == nv_crtc->index)
			regp->crtc_eng_ctrl |= NV_CRTC_FSEL_OVERLAY;
	पूर्ण
#पूर्ण_अगर

	/* ADDRESS_SPACE_PNVM is the same as setting HCUR_ASI */
	regp->cursor_cfg = NV_PCRTC_CURSOR_CONFIG_CUR_LINES_64 |
			     NV_PCRTC_CURSOR_CONFIG_CUR_PIXELS_64 |
			     NV_PCRTC_CURSOR_CONFIG_ADDRESS_SPACE_PNVM;
	अगर (drm->client.device.info.chipset >= 0x11)
		regp->cursor_cfg |= NV_PCRTC_CURSOR_CONFIG_CUR_BPP_32;
	अगर (mode->flags & DRM_MODE_FLAG_DBLSCAN)
		regp->cursor_cfg |= NV_PCRTC_CURSOR_CONFIG_DOUBLE_SCAN_ENABLE;

	/* Unblock some timings */
	regp->CRTC[NV_CIO_CRE_53] = 0;
	regp->CRTC[NV_CIO_CRE_54] = 0;

	/* 0x00 is disabled, 0x11 is lvds, 0x22 crt and 0x88 पंचांगds */
	अगर (lvds_output)
		regp->CRTC[NV_CIO_CRE_SCRATCH3__INDEX] = 0x11;
	अन्यथा अगर (पंचांगds_output)
		regp->CRTC[NV_CIO_CRE_SCRATCH3__INDEX] = 0x88;
	अन्यथा
		regp->CRTC[NV_CIO_CRE_SCRATCH3__INDEX] = 0x22;

	/* These values seem to vary */
	/* This रेजिस्टर seems to be used by the bios to make certain decisions on some G70 cards? */
	regp->CRTC[NV_CIO_CRE_SCRATCH4__INDEX] = savep->CRTC[NV_CIO_CRE_SCRATCH4__INDEX];

	nv_crtc_set_digital_vibrance(crtc, nv_crtc->saturation);

	/* probably a scratch reg, but kept क्रम cargo-cult purposes:
	 * bit0: crtc0?, head A
	 * bit6: lvds, head A
	 * bit7: (only in X), head A
	 */
	अगर (nv_crtc->index == 0)
		regp->CRTC[NV_CIO_CRE_4B] = savep->CRTC[NV_CIO_CRE_4B] | 0x80;

	/* The blob seems to take the current value from crtc 0, add 4 to that
	 * and reuse the old value क्रम crtc 1 */
	regp->CRTC[NV_CIO_CRE_TVOUT_LATENCY] = nv04_display(dev)->saved_reg.crtc_reg[0].CRTC[NV_CIO_CRE_TVOUT_LATENCY];
	अगर (!nv_crtc->index)
		regp->CRTC[NV_CIO_CRE_TVOUT_LATENCY] += 4;

	/* the blob someबार sets |= 0x10 (which is the same as setting |=
	 * 1 << 30 on 0x60.830), क्रम no apparent reason */
	regp->CRTC[NV_CIO_CRE_59] = off_chip_digital;

	अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_RANKINE)
		regp->CRTC[0x9f] = off_chip_digital ? 0x11 : 0x1;

	regp->crtc_830 = mode->crtc_vdisplay - 3;
	regp->crtc_834 = mode->crtc_vdisplay - 1;

	अगर (drm->client.device.info.family == NV_DEVICE_INFO_V0_CURIE)
		/* This is what the blob करोes */
		regp->crtc_850 = NVReadCRTC(dev, 0, NV_PCRTC_850);

	अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_RANKINE)
		regp->gpio_ext = NVReadCRTC(dev, 0, NV_PCRTC_GPIO_EXT);

	अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_CELSIUS)
		regp->crtc_cfg = NV10_PCRTC_CONFIG_START_ADDRESS_HSYNC;
	अन्यथा
		regp->crtc_cfg = NV04_PCRTC_CONFIG_START_ADDRESS_HSYNC;

	/* Some misc regs */
	अगर (drm->client.device.info.family == NV_DEVICE_INFO_V0_CURIE) अणु
		regp->CRTC[NV_CIO_CRE_85] = 0xFF;
		regp->CRTC[NV_CIO_CRE_86] = 0x1;
	पूर्ण

	regp->CRTC[NV_CIO_CRE_PIXEL_INDEX] = (fb->क्रमmat->depth + 1) / 8;
	/* Enable slaved mode (called MODE_TV in nv4ref.h) */
	अगर (lvds_output || पंचांगds_output || tv_output)
		regp->CRTC[NV_CIO_CRE_PIXEL_INDEX] |= (1 << 7);

	/* Generic PRAMDAC regs */

	अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_CELSIUS)
		/* Only bit that bios and blob set. */
		regp->nv10_cursync = (1 << 25);

	regp->ramdac_gen_ctrl = NV_PRAMDAC_GENERAL_CONTROL_BPC_8BITS |
				NV_PRAMDAC_GENERAL_CONTROL_VGA_STATE_SEL |
				NV_PRAMDAC_GENERAL_CONTROL_PIXMIX_ON;
	अगर (fb->क्रमmat->depth == 16)
		regp->ramdac_gen_ctrl |= NV_PRAMDAC_GENERAL_CONTROL_ALT_MODE_SEL;
	अगर (drm->client.device.info.chipset >= 0x11)
		regp->ramdac_gen_ctrl |= NV_PRAMDAC_GENERAL_CONTROL_PIPE_LONG;

	regp->ramdac_630 = 0; /* turn off green mode (tv test pattern?) */
	regp->tv_setup = 0;

	nv_crtc_set_image_sharpening(crtc, nv_crtc->sharpness);

	/* Some values the blob sets */
	regp->ramdac_8c0 = 0x100;
	regp->ramdac_a20 = 0x0;
	regp->ramdac_a24 = 0xfffff;
	regp->ramdac_a34 = 0x1;
पूर्ण

अटल पूर्णांक
nv_crtc_swap_fbs(काष्ठा drm_crtc *crtc, काष्ठा drm_framebuffer *old_fb)
अणु
	काष्ठा nv04_display *disp = nv04_display(crtc->dev);
	काष्ठा drm_framebuffer *fb = crtc->primary->fb;
	काष्ठा nouveau_bo *nvbo = nouveau_gem_object(fb->obj[0]);
	काष्ठा nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
	पूर्णांक ret;

	ret = nouveau_bo_pin(nvbo, NOUVEAU_GEM_DOMAIN_VRAM, false);
	अगर (ret == 0) अणु
		अगर (disp->image[nv_crtc->index])
			nouveau_bo_unpin(disp->image[nv_crtc->index]);
		nouveau_bo_ref(nvbo, &disp->image[nv_crtc->index]);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * Sets up रेजिस्टरs क्रम the given mode/adjusted_mode pair.
 *
 * The घड़ीs, CRTCs and outमाला_दो attached to this CRTC must be off.
 *
 * This shouldn't enable any घड़ीs, CRTCs, or outमाला_दो, but they should
 * be easily turned on/off after this.
 */
अटल पूर्णांक
nv_crtc_mode_set(काष्ठा drm_crtc *crtc, काष्ठा drm_display_mode *mode,
		 काष्ठा drm_display_mode *adjusted_mode,
		 पूर्णांक x, पूर्णांक y, काष्ठा drm_framebuffer *old_fb)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	पूर्णांक ret;

	NV_DEBUG(drm, "CTRC mode on CRTC %d:\n", nv_crtc->index);
	drm_mode_debug_prपूर्णांकmodeline(adjusted_mode);

	ret = nv_crtc_swap_fbs(crtc, old_fb);
	अगर (ret)
		वापस ret;

	/* unlock must come after turning off FP_TG_CONTROL in output_prepare */
	nv_lock_vga_crtc_shaकरोw(dev, nv_crtc->index, -1);

	nv_crtc_mode_set_vga(crtc, adjusted_mode);
	/* calculated in nv04_dfp_prepare, nv40 needs it written beक्रमe calculating PLLs */
	अगर (drm->client.device.info.family == NV_DEVICE_INFO_V0_CURIE)
		NVWriteRAMDAC(dev, 0, NV_PRAMDAC_SEL_CLK, nv04_display(dev)->mode_reg.sel_clk);
	nv_crtc_mode_set_regs(crtc, adjusted_mode);
	nv_crtc_calc_state_ext(crtc, mode, adjusted_mode->घड़ी);
	वापस 0;
पूर्ण

अटल व्योम nv_crtc_save(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा nv04_mode_state *state = &nv04_display(dev)->mode_reg;
	काष्ठा nv04_crtc_reg *crtc_state = &state->crtc_reg[nv_crtc->index];
	काष्ठा nv04_mode_state *saved = &nv04_display(dev)->saved_reg;
	काष्ठा nv04_crtc_reg *crtc_saved = &saved->crtc_reg[nv_crtc->index];

	अगर (nv_two_heads(crtc->dev))
		NVSetOwner(crtc->dev, nv_crtc->index);

	nouveau_hw_save_state(crtc->dev, nv_crtc->index, saved);

	/* init some state to saved value */
	state->sel_clk = saved->sel_clk & ~(0x5 << 16);
	crtc_state->CRTC[NV_CIO_CRE_LCD__INDEX] = crtc_saved->CRTC[NV_CIO_CRE_LCD__INDEX];
	state->pllsel = saved->pllsel & ~(PLLSEL_VPLL1_MASK | PLLSEL_VPLL2_MASK | PLLSEL_TV_MASK);
	crtc_state->gpio_ext = crtc_saved->gpio_ext;
पूर्ण

अटल व्योम nv_crtc_restore(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	पूर्णांक head = nv_crtc->index;
	uपूर्णांक8_t saved_cr21 = nv04_display(dev)->saved_reg.crtc_reg[head].CRTC[NV_CIO_CRE_21];

	अगर (nv_two_heads(crtc->dev))
		NVSetOwner(crtc->dev, head);

	nouveau_hw_load_state(crtc->dev, head, &nv04_display(dev)->saved_reg);
	nv_lock_vga_crtc_shaकरोw(crtc->dev, head, saved_cr21);

	nv_crtc->last_dpms = NV_DPMS_CLEARED;
पूर्ण

अटल व्योम nv_crtc_prepare(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
	स्थिर काष्ठा drm_crtc_helper_funcs *funcs = crtc->helper_निजी;

	अगर (nv_two_heads(dev))
		NVSetOwner(dev, nv_crtc->index);

	drm_crtc_vblank_off(crtc);
	funcs->dpms(crtc, DRM_MODE_DPMS_OFF);

	NVBlankScreen(dev, nv_crtc->index, true);

	/* Some more preparation. */
	NVWriteCRTC(dev, nv_crtc->index, NV_PCRTC_CONFIG, NV_PCRTC_CONFIG_START_ADDRESS_NON_VGA);
	अगर (drm->client.device.info.family == NV_DEVICE_INFO_V0_CURIE) अणु
		uपूर्णांक32_t reg900 = NVReadRAMDAC(dev, nv_crtc->index, NV_PRAMDAC_900);
		NVWriteRAMDAC(dev, nv_crtc->index, NV_PRAMDAC_900, reg900 & ~0x10000);
	पूर्ण
पूर्ण

अटल व्योम nv_crtc_commit(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	स्थिर काष्ठा drm_crtc_helper_funcs *funcs = crtc->helper_निजी;
	काष्ठा nouveau_crtc *nv_crtc = nouveau_crtc(crtc);

	nouveau_hw_load_state(dev, nv_crtc->index, &nv04_display(dev)->mode_reg);
	nv04_crtc_mode_set_base(crtc, crtc->x, crtc->y, शून्य);

#अगर_घोषित __BIG_ENDIAN
	/* turn on LFB swapping */
	अणु
		uपूर्णांक8_t पंचांगp = NVReadVgaCrtc(dev, nv_crtc->index, NV_CIO_CRE_RCR);
		पंचांगp |= MASK(NV_CIO_CRE_RCR_ENDIAN_BIG);
		NVWriteVgaCrtc(dev, nv_crtc->index, NV_CIO_CRE_RCR, पंचांगp);
	पूर्ण
#पूर्ण_अगर

	funcs->dpms(crtc, DRM_MODE_DPMS_ON);
	drm_crtc_vblank_on(crtc);
पूर्ण

अटल व्योम nv_crtc_destroy(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा nv04_display *disp = nv04_display(crtc->dev);
	काष्ठा nouveau_crtc *nv_crtc = nouveau_crtc(crtc);

	अगर (!nv_crtc)
		वापस;

	drm_crtc_cleanup(crtc);

	अगर (disp->image[nv_crtc->index])
		nouveau_bo_unpin(disp->image[nv_crtc->index]);
	nouveau_bo_ref(शून्य, &disp->image[nv_crtc->index]);

	nouveau_bo_unmap(nv_crtc->cursor.nvbo);
	nouveau_bo_unpin(nv_crtc->cursor.nvbo);
	nouveau_bo_ref(शून्य, &nv_crtc->cursor.nvbo);
	nvअगर_notअगरy_dtor(&nv_crtc->vblank);
	kमुक्त(nv_crtc);
पूर्ण

अटल व्योम
nv_crtc_gamma_load(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
	काष्ठा drm_device *dev = nv_crtc->base.dev;
	काष्ठा rgb अणु uपूर्णांक8_t r, g, b; पूर्ण __attribute__((packed)) *rgbs;
	u16 *r, *g, *b;
	पूर्णांक i;

	rgbs = (काष्ठा rgb *)nv04_display(dev)->mode_reg.crtc_reg[nv_crtc->index].DAC;
	r = crtc->gamma_store;
	g = r + crtc->gamma_size;
	b = g + crtc->gamma_size;

	क्रम (i = 0; i < 256; i++) अणु
		rgbs[i].r = *r++ >> 8;
		rgbs[i].g = *g++ >> 8;
		rgbs[i].b = *b++ >> 8;
	पूर्ण

	nouveau_hw_load_state_palette(dev, nv_crtc->index, &nv04_display(dev)->mode_reg);
पूर्ण

अटल व्योम
nv_crtc_disable(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा nv04_display *disp = nv04_display(crtc->dev);
	काष्ठा nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
	अगर (disp->image[nv_crtc->index])
		nouveau_bo_unpin(disp->image[nv_crtc->index]);
	nouveau_bo_ref(शून्य, &disp->image[nv_crtc->index]);
पूर्ण

अटल पूर्णांक
nv_crtc_gamma_set(काष्ठा drm_crtc *crtc, u16 *r, u16 *g, u16 *b,
		  uपूर्णांक32_t size,
		  काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा nouveau_crtc *nv_crtc = nouveau_crtc(crtc);

	/* We need to know the depth beक्रमe we upload, but it's possible to
	 * get called beक्रमe a framebuffer is bound.  If this is the हाल,
	 * mark the lut values as dirty by setting depth==0, and it'll be
	 * uploaded on the first mode_set_base()
	 */
	अगर (!nv_crtc->base.primary->fb) अणु
		nv_crtc->lut.depth = 0;
		वापस 0;
	पूर्ण

	nv_crtc_gamma_load(crtc);

	वापस 0;
पूर्ण

अटल पूर्णांक
nv04_crtc_करो_mode_set_base(काष्ठा drm_crtc *crtc,
			   काष्ठा drm_framebuffer *passed_fb,
			   पूर्णांक x, पूर्णांक y, bool atomic)
अणु
	काष्ठा nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nv04_crtc_reg *regp = &nv04_display(dev)->mode_reg.crtc_reg[nv_crtc->index];
	काष्ठा nouveau_bo *nvbo;
	काष्ठा drm_framebuffer *drm_fb;
	पूर्णांक arb_burst, arb_lwm;

	NV_DEBUG(drm, "index %d\n", nv_crtc->index);

	/* no fb bound */
	अगर (!atomic && !crtc->primary->fb) अणु
		NV_DEBUG(drm, "No FB bound\n");
		वापस 0;
	पूर्ण

	/* If atomic, we want to चयन to the fb we were passed, so
	 * now we update poपूर्णांकers to करो that.
	 */
	अगर (atomic) अणु
		drm_fb = passed_fb;
	पूर्ण अन्यथा अणु
		drm_fb = crtc->primary->fb;
	पूर्ण

	nvbo = nouveau_gem_object(drm_fb->obj[0]);
	nv_crtc->fb.offset = nvbo->offset;

	अगर (nv_crtc->lut.depth != drm_fb->क्रमmat->depth) अणु
		nv_crtc->lut.depth = drm_fb->क्रमmat->depth;
		nv_crtc_gamma_load(crtc);
	पूर्ण

	/* Update the framebuffer क्रमmat. */
	regp->CRTC[NV_CIO_CRE_PIXEL_INDEX] &= ~3;
	regp->CRTC[NV_CIO_CRE_PIXEL_INDEX] |= (drm_fb->क्रमmat->depth + 1) / 8;
	regp->ramdac_gen_ctrl &= ~NV_PRAMDAC_GENERAL_CONTROL_ALT_MODE_SEL;
	अगर (drm_fb->क्रमmat->depth == 16)
		regp->ramdac_gen_ctrl |= NV_PRAMDAC_GENERAL_CONTROL_ALT_MODE_SEL;
	crtc_wr_cio_state(crtc, regp, NV_CIO_CRE_PIXEL_INDEX);
	NVWriteRAMDAC(dev, nv_crtc->index, NV_PRAMDAC_GENERAL_CONTROL,
		      regp->ramdac_gen_ctrl);

	regp->CRTC[NV_CIO_CR_OFFSET_INDEX] = drm_fb->pitches[0] >> 3;
	regp->CRTC[NV_CIO_CRE_RPC0_INDEX] =
		XLATE(drm_fb->pitches[0] >> 3, 8, NV_CIO_CRE_RPC0_OFFSET_10_8);
	regp->CRTC[NV_CIO_CRE_42] =
		XLATE(drm_fb->pitches[0] / 8, 11, NV_CIO_CRE_42_OFFSET_11);
	crtc_wr_cio_state(crtc, regp, NV_CIO_CRE_RPC0_INDEX);
	crtc_wr_cio_state(crtc, regp, NV_CIO_CR_OFFSET_INDEX);
	crtc_wr_cio_state(crtc, regp, NV_CIO_CRE_42);

	/* Update the framebuffer location. */
	regp->fb_start = nv_crtc->fb.offset & ~3;
	regp->fb_start += (y * drm_fb->pitches[0]) + (x * drm_fb->क्रमmat->cpp[0]);
	nv_set_crtc_base(dev, nv_crtc->index, regp->fb_start);

	/* Update the arbitration parameters. */
	nouveau_calc_arb(dev, crtc->mode.घड़ी, drm_fb->क्रमmat->cpp[0] * 8,
			 &arb_burst, &arb_lwm);

	regp->CRTC[NV_CIO_CRE_FF_INDEX] = arb_burst;
	regp->CRTC[NV_CIO_CRE_FFLWM__INDEX] = arb_lwm & 0xff;
	crtc_wr_cio_state(crtc, regp, NV_CIO_CRE_FF_INDEX);
	crtc_wr_cio_state(crtc, regp, NV_CIO_CRE_FFLWM__INDEX);

	अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_KELVIN) अणु
		regp->CRTC[NV_CIO_CRE_47] = arb_lwm >> 8;
		crtc_wr_cio_state(crtc, regp, NV_CIO_CRE_47);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nv04_crtc_mode_set_base(काष्ठा drm_crtc *crtc, पूर्णांक x, पूर्णांक y,
			काष्ठा drm_framebuffer *old_fb)
अणु
	पूर्णांक ret = nv_crtc_swap_fbs(crtc, old_fb);
	अगर (ret)
		वापस ret;
	वापस nv04_crtc_करो_mode_set_base(crtc, old_fb, x, y, false);
पूर्ण

अटल पूर्णांक
nv04_crtc_mode_set_base_atomic(काष्ठा drm_crtc *crtc,
			       काष्ठा drm_framebuffer *fb,
			       पूर्णांक x, पूर्णांक y, क्रमागत mode_set_atomic state)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(crtc->dev);
	काष्ठा drm_device *dev = drm->dev;

	अगर (state == ENTER_ATOMIC_MODE_SET)
		nouveau_fbcon_accel_save_disable(dev);
	अन्यथा
		nouveau_fbcon_accel_restore(dev);

	वापस nv04_crtc_करो_mode_set_base(crtc, fb, x, y, true);
पूर्ण

अटल व्योम nv04_cursor_upload(काष्ठा drm_device *dev, काष्ठा nouveau_bo *src,
			       काष्ठा nouveau_bo *dst)
अणु
	पूर्णांक width = nv_cursor_width(dev);
	uपूर्णांक32_t pixel;
	पूर्णांक i, j;

	क्रम (i = 0; i < width; i++) अणु
		क्रम (j = 0; j < width; j++) अणु
			pixel = nouveau_bo_rd32(src, i*64 + j);

			nouveau_bo_wr16(dst, i*width + j, (pixel & 0x80000000) >> 16
				     | (pixel & 0xf80000) >> 9
				     | (pixel & 0xf800) >> 6
				     | (pixel & 0xf8) >> 3);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम nv11_cursor_upload(काष्ठा drm_device *dev, काष्ठा nouveau_bo *src,
			       काष्ठा nouveau_bo *dst)
अणु
	uपूर्णांक32_t pixel;
	पूर्णांक alpha, i;

	/* nv11+ supports premultiplied (PM), or non-premultiplied (NPM) alpha
	 * cursors (though NPM in combination with fp dithering may not work on
	 * nv11, from "nv" driver history)
	 * NPM mode needs NV_PCRTC_CURSOR_CONFIG_ALPHA_BLEND set and is what the
	 * blob uses, however we get given PM cursors so we use PM mode
	 */
	क्रम (i = 0; i < 64 * 64; i++) अणु
		pixel = nouveau_bo_rd32(src, i);

		/* hw माला_लो unhappy अगर alpha <= rgb values.  क्रम a PM image "less
		 * than" shouldn't happen; fix "equal to" हाल by adding one to
		 * alpha channel (slightly inaccurate, but so is attempting to
		 * get back to NPM images, due to limits of पूर्णांकeger precision)
		 */
		alpha = pixel >> 24;
		अगर (alpha > 0 && alpha < 255)
			pixel = (pixel & 0x00ffffff) | ((alpha + 1) << 24);

#अगर_घोषित __BIG_ENDIAN
		अणु
			काष्ठा nouveau_drm *drm = nouveau_drm(dev);

			अगर (drm->client.device.info.chipset == 0x11) अणु
				pixel = ((pixel & 0x000000ff) << 24) |
					((pixel & 0x0000ff00) << 8) |
					((pixel & 0x00ff0000) >> 8) |
					((pixel & 0xff000000) >> 24);
			पूर्ण
		पूर्ण
#पूर्ण_अगर

		nouveau_bo_wr32(dst, i, pixel);
	पूर्ण
पूर्ण

अटल पूर्णांक
nv04_crtc_cursor_set(काष्ठा drm_crtc *crtc, काष्ठा drm_file *file_priv,
		     uपूर्णांक32_t buffer_handle, uपूर्णांक32_t width, uपूर्णांक32_t height)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(crtc->dev);
	काष्ठा drm_device *dev = drm->dev;
	काष्ठा nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
	काष्ठा nouveau_bo *cursor = शून्य;
	काष्ठा drm_gem_object *gem;
	पूर्णांक ret = 0;

	अगर (!buffer_handle) अणु
		nv_crtc->cursor.hide(nv_crtc, true);
		वापस 0;
	पूर्ण

	अगर (width != 64 || height != 64)
		वापस -EINVAL;

	gem = drm_gem_object_lookup(file_priv, buffer_handle);
	अगर (!gem)
		वापस -ENOENT;
	cursor = nouveau_gem_object(gem);

	ret = nouveau_bo_map(cursor);
	अगर (ret)
		जाओ out;

	अगर (drm->client.device.info.chipset >= 0x11)
		nv11_cursor_upload(dev, cursor, nv_crtc->cursor.nvbo);
	अन्यथा
		nv04_cursor_upload(dev, cursor, nv_crtc->cursor.nvbo);

	nouveau_bo_unmap(cursor);
	nv_crtc->cursor.offset = nv_crtc->cursor.nvbo->offset;
	nv_crtc->cursor.set_offset(nv_crtc, nv_crtc->cursor.offset);
	nv_crtc->cursor.show(nv_crtc, true);
out:
	drm_gem_object_put(gem);
	वापस ret;
पूर्ण

अटल पूर्णांक
nv04_crtc_cursor_move(काष्ठा drm_crtc *crtc, पूर्णांक x, पूर्णांक y)
अणु
	काष्ठा nouveau_crtc *nv_crtc = nouveau_crtc(crtc);

	nv_crtc->cursor.set_pos(nv_crtc, x, y);
	वापस 0;
पूर्ण

काष्ठा nv04_page_flip_state अणु
	काष्ठा list_head head;
	काष्ठा drm_pending_vblank_event *event;
	काष्ठा drm_crtc *crtc;
	पूर्णांक bpp, pitch;
	u64 offset;
पूर्ण;

अटल पूर्णांक
nv04_finish_page_flip(काष्ठा nouveau_channel *chan,
		      काष्ठा nv04_page_flip_state *ps)
अणु
	काष्ठा nouveau_fence_chan *fctx = chan->fence;
	काष्ठा nouveau_drm *drm = chan->drm;
	काष्ठा drm_device *dev = drm->dev;
	काष्ठा nv04_page_flip_state *s;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->event_lock, flags);

	अगर (list_empty(&fctx->flip)) अणु
		NV_ERROR(drm, "unexpected pageflip\n");
		spin_unlock_irqrestore(&dev->event_lock, flags);
		वापस -EINVAL;
	पूर्ण

	s = list_first_entry(&fctx->flip, काष्ठा nv04_page_flip_state, head);
	अगर (s->event) अणु
		drm_crtc_arm_vblank_event(s->crtc, s->event);
	पूर्ण अन्यथा अणु
		/* Give up ownership of vblank क्रम page-flipped crtc */
		drm_crtc_vblank_put(s->crtc);
	पूर्ण

	list_del(&s->head);
	अगर (ps)
		*ps = *s;
	kमुक्त(s);

	spin_unlock_irqrestore(&dev->event_lock, flags);
	वापस 0;
पूर्ण

पूर्णांक
nv04_flip_complete(काष्ठा nvअगर_notअगरy *notअगरy)
अणु
	काष्ठा nouveau_cli *cli = (व्योम *)notअगरy->object->client;
	काष्ठा nouveau_drm *drm = cli->drm;
	काष्ठा nouveau_channel *chan = drm->channel;
	काष्ठा nv04_page_flip_state state;

	अगर (!nv04_finish_page_flip(chan, &state)) अणु
		nv_set_crtc_base(drm->dev, drm_crtc_index(state.crtc),
				 state.offset + state.crtc->y *
				 state.pitch + state.crtc->x *
				 state.bpp / 8);
	पूर्ण

	वापस NVIF_NOTIFY_KEEP;
पूर्ण

अटल पूर्णांक
nv04_page_flip_emit(काष्ठा nouveau_channel *chan,
		    काष्ठा nouveau_bo *old_bo,
		    काष्ठा nouveau_bo *new_bo,
		    काष्ठा nv04_page_flip_state *s,
		    काष्ठा nouveau_fence **pfence)
अणु
	काष्ठा nouveau_fence_chan *fctx = chan->fence;
	काष्ठा nouveau_drm *drm = chan->drm;
	काष्ठा drm_device *dev = drm->dev;
	काष्ठा nvअगर_push *push = chan->chan.push;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/* Queue it to the pending list */
	spin_lock_irqsave(&dev->event_lock, flags);
	list_add_tail(&s->head, &fctx->flip);
	spin_unlock_irqrestore(&dev->event_lock, flags);

	/* Synchronize with the old framebuffer */
	ret = nouveau_fence_sync(old_bo, chan, false, false);
	अगर (ret)
		जाओ fail;

	/* Emit the pageflip */
	ret = PUSH_WAIT(push, 2);
	अगर (ret)
		जाओ fail;

	PUSH_NVSQ(push, NV_SW, NV_SW_PAGE_FLIP, 0x00000000);
	PUSH_KICK(push);

	ret = nouveau_fence_new(chan, false, pfence);
	अगर (ret)
		जाओ fail;

	वापस 0;
fail:
	spin_lock_irqsave(&dev->event_lock, flags);
	list_del(&s->head);
	spin_unlock_irqrestore(&dev->event_lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक
nv04_crtc_page_flip(काष्ठा drm_crtc *crtc, काष्ठा drm_framebuffer *fb,
		    काष्ठा drm_pending_vblank_event *event, u32 flags,
		    काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	स्थिर पूर्णांक swap_पूर्णांकerval = (flags & DRM_MODE_PAGE_FLIP_ASYNC) ? 0 : 1;
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा drm_framebuffer *old_fb = crtc->primary->fb;
	काष्ठा nouveau_bo *old_bo = nouveau_gem_object(old_fb->obj[0]);
	काष्ठा nouveau_bo *new_bo = nouveau_gem_object(fb->obj[0]);
	काष्ठा nv04_page_flip_state *s;
	काष्ठा nouveau_channel *chan;
	काष्ठा nouveau_cli *cli;
	काष्ठा nouveau_fence *fence;
	काष्ठा nv04_display *dispnv04 = nv04_display(dev);
	काष्ठा nvअगर_push *push;
	पूर्णांक head = nouveau_crtc(crtc)->index;
	पूर्णांक ret;

	chan = drm->channel;
	अगर (!chan)
		वापस -ENODEV;
	cli = (व्योम *)chan->user.client;
	push = chan->chan.push;

	s = kzalloc(माप(*s), GFP_KERNEL);
	अगर (!s)
		वापस -ENOMEM;

	अगर (new_bo != old_bo) अणु
		ret = nouveau_bo_pin(new_bo, NOUVEAU_GEM_DOMAIN_VRAM, true);
		अगर (ret)
			जाओ fail_मुक्त;
	पूर्ण

	mutex_lock(&cli->mutex);
	ret = tपंचांग_bo_reserve(&new_bo->bo, true, false, शून्य);
	अगर (ret)
		जाओ fail_unpin;

	/* synchronise rendering channel with the kernel's channel */
	ret = nouveau_fence_sync(new_bo, chan, false, true);
	अगर (ret) अणु
		tपंचांग_bo_unreserve(&new_bo->bo);
		जाओ fail_unpin;
	पूर्ण

	अगर (new_bo != old_bo) अणु
		tपंचांग_bo_unreserve(&new_bo->bo);

		ret = tपंचांग_bo_reserve(&old_bo->bo, true, false, शून्य);
		अगर (ret)
			जाओ fail_unpin;
	पूर्ण

	/* Initialize a page flip काष्ठा */
	*s = (काष्ठा nv04_page_flip_state)
		अणु अणु पूर्ण, event, crtc, fb->क्रमmat->cpp[0] * 8, fb->pitches[0],
		  new_bo->offset पूर्ण;

	/* Keep vblanks on during flip, क्रम the target crtc of this flip */
	drm_crtc_vblank_get(crtc);

	/* Emit a page flip */
	अगर (swap_पूर्णांकerval) अणु
		ret = PUSH_WAIT(push, 8);
		अगर (ret)
			जाओ fail_unreserve;

		PUSH_NVSQ(push, NV05F, 0x012c, 0);
		PUSH_NVSQ(push, NV05F, 0x0134, head);
		PUSH_NVSQ(push, NV05F, 0x0100, 0);
		PUSH_NVSQ(push, NV05F, 0x0130, 0);
	पूर्ण

	nouveau_bo_ref(new_bo, &dispnv04->image[head]);

	ret = nv04_page_flip_emit(chan, old_bo, new_bo, s, &fence);
	अगर (ret)
		जाओ fail_unreserve;
	mutex_unlock(&cli->mutex);

	/* Update the crtc काष्ठा and cleanup */
	crtc->primary->fb = fb;

	nouveau_bo_fence(old_bo, fence, false);
	tपंचांग_bo_unreserve(&old_bo->bo);
	अगर (old_bo != new_bo)
		nouveau_bo_unpin(old_bo);
	nouveau_fence_unref(&fence);
	वापस 0;

fail_unreserve:
	drm_crtc_vblank_put(crtc);
	tपंचांग_bo_unreserve(&old_bo->bo);
fail_unpin:
	mutex_unlock(&cli->mutex);
	अगर (old_bo != new_bo)
		nouveau_bo_unpin(new_bo);
fail_मुक्त:
	kमुक्त(s);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs nv04_crtc_funcs = अणु
	.cursor_set = nv04_crtc_cursor_set,
	.cursor_move = nv04_crtc_cursor_move,
	.gamma_set = nv_crtc_gamma_set,
	.set_config = drm_crtc_helper_set_config,
	.page_flip = nv04_crtc_page_flip,
	.destroy = nv_crtc_destroy,
	.enable_vblank = nouveau_display_vblank_enable,
	.disable_vblank = nouveau_display_vblank_disable,
	.get_vblank_बारtamp = drm_crtc_vblank_helper_get_vblank_बारtamp,
पूर्ण;

अटल स्थिर काष्ठा drm_crtc_helper_funcs nv04_crtc_helper_funcs = अणु
	.dpms = nv_crtc_dpms,
	.prepare = nv_crtc_prepare,
	.commit = nv_crtc_commit,
	.mode_set = nv_crtc_mode_set,
	.mode_set_base = nv04_crtc_mode_set_base,
	.mode_set_base_atomic = nv04_crtc_mode_set_base_atomic,
	.disable = nv_crtc_disable,
	.get_scanout_position = nouveau_display_scanoutpos,
पूर्ण;

अटल स्थिर uपूर्णांक32_t modeset_क्रमmats[] = अणु
        DRM_FORMAT_XRGB8888,
        DRM_FORMAT_RGB565,
        DRM_FORMAT_XRGB1555,
पूर्ण;

अटल काष्ठा drm_plane *
create_primary_plane(काष्ठा drm_device *dev)
अणु
        काष्ठा drm_plane *primary;
        पूर्णांक ret;

        primary = kzalloc(माप(*primary), GFP_KERNEL);
        अगर (primary == शून्य) अणु
                DRM_DEBUG_KMS("Failed to allocate primary plane\n");
                वापस शून्य;
        पूर्ण

        /* possible_crtc's will be filled in later by crtc_init */
        ret = drm_universal_plane_init(dev, primary, 0,
                                       &drm_primary_helper_funcs,
                                       modeset_क्रमmats,
                                       ARRAY_SIZE(modeset_क्रमmats), शून्य,
                                       DRM_PLANE_TYPE_PRIMARY, शून्य);
        अगर (ret) अणु
                kमुक्त(primary);
                primary = शून्य;
        पूर्ण

        वापस primary;
पूर्ण

अटल पूर्णांक nv04_crtc_vblank_handler(काष्ठा nvअगर_notअगरy *notअगरy)
अणु
	काष्ठा nouveau_crtc *nv_crtc =
		container_of(notअगरy, काष्ठा nouveau_crtc, vblank);

	drm_crtc_handle_vblank(&nv_crtc->base);
	वापस NVIF_NOTIFY_KEEP;
पूर्ण

पूर्णांक
nv04_crtc_create(काष्ठा drm_device *dev, पूर्णांक crtc_num)
अणु
	काष्ठा nouveau_display *disp = nouveau_display(dev);
	काष्ठा nouveau_crtc *nv_crtc;
	पूर्णांक ret;

	nv_crtc = kzalloc(माप(*nv_crtc), GFP_KERNEL);
	अगर (!nv_crtc)
		वापस -ENOMEM;

	nv_crtc->lut.depth = 0;

	nv_crtc->index = crtc_num;
	nv_crtc->last_dpms = NV_DPMS_CLEARED;

	nv_crtc->save = nv_crtc_save;
	nv_crtc->restore = nv_crtc_restore;

	drm_crtc_init_with_planes(dev, &nv_crtc->base,
                                  create_primary_plane(dev), शून्य,
                                  &nv04_crtc_funcs, शून्य);
	drm_crtc_helper_add(&nv_crtc->base, &nv04_crtc_helper_funcs);
	drm_mode_crtc_set_gamma_size(&nv_crtc->base, 256);

	ret = nouveau_bo_new(&nouveau_drm(dev)->client, 64*64*4, 0x100,
			     NOUVEAU_GEM_DOMAIN_VRAM, 0, 0x0000, शून्य, शून्य,
			     &nv_crtc->cursor.nvbo);
	अगर (!ret) अणु
		ret = nouveau_bo_pin(nv_crtc->cursor.nvbo,
				     NOUVEAU_GEM_DOMAIN_VRAM, false);
		अगर (!ret) अणु
			ret = nouveau_bo_map(nv_crtc->cursor.nvbo);
			अगर (ret)
				nouveau_bo_unpin(nv_crtc->cursor.nvbo);
		पूर्ण
		अगर (ret)
			nouveau_bo_ref(शून्य, &nv_crtc->cursor.nvbo);
	पूर्ण

	nv04_cursor_init(nv_crtc);

	ret = nvअगर_notअगरy_ctor(&disp->disp.object, "kmsVbl", nv04_crtc_vblank_handler,
			       false, NV04_DISP_NTFY_VBLANK,
			       &(काष्ठा nvअगर_notअगरy_head_req_v0) अणु
				    .head = nv_crtc->index,
			       पूर्ण,
			       माप(काष्ठा nvअगर_notअगरy_head_req_v0),
			       माप(काष्ठा nvअगर_notअगरy_head_rep_v0),
			       &nv_crtc->vblank);

	वापस ret;
पूर्ण
