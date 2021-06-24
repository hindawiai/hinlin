<शैली गुरु>
/*
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
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश "nouveau_drv.h"
#समावेश "hw.h"

#समावेश <subdev/bios/pll.h>
#समावेश <nvअगर/समयr.h>

#घोषणा CHIPSET_NFORCE 0x01a0
#घोषणा CHIPSET_NFORCE2 0x01f0

/*
 * misc hw access wrappers/control functions
 */

व्योम
NVWriteVgaSeq(काष्ठा drm_device *dev, पूर्णांक head, uपूर्णांक8_t index, uपूर्णांक8_t value)
अणु
	NVWritePRMVIO(dev, head, NV_PRMVIO_SRX, index);
	NVWritePRMVIO(dev, head, NV_PRMVIO_SR, value);
पूर्ण

uपूर्णांक8_t
NVReadVgaSeq(काष्ठा drm_device *dev, पूर्णांक head, uपूर्णांक8_t index)
अणु
	NVWritePRMVIO(dev, head, NV_PRMVIO_SRX, index);
	वापस NVReadPRMVIO(dev, head, NV_PRMVIO_SR);
पूर्ण

व्योम
NVWriteVgaGr(काष्ठा drm_device *dev, पूर्णांक head, uपूर्णांक8_t index, uपूर्णांक8_t value)
अणु
	NVWritePRMVIO(dev, head, NV_PRMVIO_GRX, index);
	NVWritePRMVIO(dev, head, NV_PRMVIO_GX, value);
पूर्ण

uपूर्णांक8_t
NVReadVgaGr(काष्ठा drm_device *dev, पूर्णांक head, uपूर्णांक8_t index)
अणु
	NVWritePRMVIO(dev, head, NV_PRMVIO_GRX, index);
	वापस NVReadPRMVIO(dev, head, NV_PRMVIO_GX);
पूर्ण

/* CR44 takes values 0 (head A), 3 (head B) and 4 (heads tied)
 * it affects only the 8 bit vga io regs, which we access using mmio at
 * 0xcअणु0,2पूर्ण3c*, 0x60अणु1,3पूर्ण3*, and 0x68अणु1,3पूर्ण3d*
 * in general, the set value of cr44 करोes not matter: reg access works as
 * expected and values can be set क्रम the appropriate head by using a 0x2000
 * offset as required
 * however:
 * a) pre nv40, the head B range of PRMVIO regs at 0xc23c* was not exposed and
 *    cr44 must be set to 0 or 3 क्रम accessing values on the correct head
 *    through the common 0xc03c* addresses
 * b) in tied mode (4) head B is programmed to the values set on head A, and
 *    access using the head B addresses can have strange results, ergo we leave
 *    tied mode in init once we know to what cr44 should be restored on निकास
 *
 * the owner parameter is slightly abused:
 * 0 and 1 are treated as head values and so the set value is (owner * 3)
 * other values are treated as literal values to set
 */
व्योम
NVSetOwner(काष्ठा drm_device *dev, पूर्णांक owner)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);

	अगर (owner == 1)
		owner *= 3;

	अगर (drm->client.device.info.chipset == 0x11) अणु
		/* This might seem stupid, but the blob करोes it and
		 * omitting it often locks the प्रणाली up.
		 */
		NVReadVgaCrtc(dev, 0, NV_CIO_SR_LOCK_INDEX);
		NVReadVgaCrtc(dev, 1, NV_CIO_SR_LOCK_INDEX);
	पूर्ण

	/* CR44 is always changed on CRTC0 */
	NVWriteVgaCrtc(dev, 0, NV_CIO_CRE_44, owner);

	अगर (drm->client.device.info.chipset == 0x11) अणु	/* set me harder */
		NVWriteVgaCrtc(dev, 0, NV_CIO_CRE_2E, owner);
		NVWriteVgaCrtc(dev, 0, NV_CIO_CRE_2E, owner);
	पूर्ण
पूर्ण

व्योम
NVBlankScreen(काष्ठा drm_device *dev, पूर्णांक head, bool blank)
अणु
	अचिन्हित अक्षर seq1;

	अगर (nv_two_heads(dev))
		NVSetOwner(dev, head);

	seq1 = NVReadVgaSeq(dev, head, NV_VIO_SR_CLOCK_INDEX);

	NVVgaSeqReset(dev, head, true);
	अगर (blank)
		NVWriteVgaSeq(dev, head, NV_VIO_SR_CLOCK_INDEX, seq1 | 0x20);
	अन्यथा
		NVWriteVgaSeq(dev, head, NV_VIO_SR_CLOCK_INDEX, seq1 & ~0x20);
	NVVgaSeqReset(dev, head, false);
पूर्ण

/*
 * PLL getting
 */

अटल व्योम
nouveau_hw_decode_pll(काष्ठा drm_device *dev, uपूर्णांक32_t reg1, uपूर्णांक32_t pll1,
		      uपूर्णांक32_t pll2, काष्ठा nvkm_pll_vals *pllvals)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);

	/* to क्रमce parsing as single stage (i.e. nv40 vplls) pass pll2 as 0 */

	/* log2P is & 0x7 as never more than 7, and nv30/35 only uses 3 bits */
	pllvals->log2P = (pll1 >> 16) & 0x7;
	pllvals->N2 = pllvals->M2 = 1;

	अगर (reg1 <= 0x405c) अणु
		pllvals->NM1 = pll2 & 0xffff;
		/* single stage NVPLL and VPLLs use 1 << 8, MPLL uses 1 << 12 */
		अगर (!(pll1 & 0x1100))
			pllvals->NM2 = pll2 >> 16;
	पूर्ण अन्यथा अणु
		pllvals->NM1 = pll1 & 0xffff;
		अगर (nv_two_reg_pll(dev) && pll2 & NV31_RAMDAC_ENABLE_VCO2)
			pllvals->NM2 = pll2 & 0xffff;
		अन्यथा अगर (drm->client.device.info.chipset == 0x30 || drm->client.device.info.chipset == 0x35) अणु
			pllvals->M1 &= 0xf; /* only 4 bits */
			अगर (pll1 & NV30_RAMDAC_ENABLE_VCO2) अणु
				pllvals->M2 = (pll1 >> 4) & 0x7;
				pllvals->N2 = ((pll1 >> 21) & 0x18) |
					      ((pll1 >> 19) & 0x7);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक
nouveau_hw_get_pllvals(काष्ठा drm_device *dev, क्रमागत nvbios_pll_type plltype,
		       काष्ठा nvkm_pll_vals *pllvals)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvअगर_object *device = &drm->client.device.object;
	काष्ठा nvkm_bios *bios = nvxx_bios(&drm->client.device);
	uपूर्णांक32_t reg1, pll1, pll2 = 0;
	काष्ठा nvbios_pll pll_lim;
	पूर्णांक ret;

	ret = nvbios_pll_parse(bios, plltype, &pll_lim);
	अगर (ret || !(reg1 = pll_lim.reg))
		वापस -ENOENT;

	pll1 = nvअगर_rd32(device, reg1);
	अगर (reg1 <= 0x405c)
		pll2 = nvअगर_rd32(device, reg1 + 4);
	अन्यथा अगर (nv_two_reg_pll(dev)) अणु
		uपूर्णांक32_t reg2 = reg1 + (reg1 == NV_RAMDAC_VPLL2 ? 0x5c : 0x70);

		pll2 = nvअगर_rd32(device, reg2);
	पूर्ण

	अगर (drm->client.device.info.family == NV_DEVICE_INFO_V0_CELSIUS && reg1 >= NV_PRAMDAC_VPLL_COEFF) अणु
		uपूर्णांक32_t ramdac580 = NVReadRAMDAC(dev, 0, NV_PRAMDAC_580);

		/* check whether vpll has been क्रमced पूर्णांकo single stage mode */
		अगर (reg1 == NV_PRAMDAC_VPLL_COEFF) अणु
			अगर (ramdac580 & NV_RAMDAC_580_VPLL1_ACTIVE)
				pll2 = 0;
		पूर्ण अन्यथा
			अगर (ramdac580 & NV_RAMDAC_580_VPLL2_ACTIVE)
				pll2 = 0;
	पूर्ण

	nouveau_hw_decode_pll(dev, reg1, pll1, pll2, pllvals);
	pllvals->refclk = pll_lim.refclk;
	वापस 0;
पूर्ण

पूर्णांक
nouveau_hw_pllvals_to_clk(काष्ठा nvkm_pll_vals *pv)
अणु
	/* Aव्योम भागide by zero अगर called at an inappropriate समय */
	अगर (!pv->M1 || !pv->M2)
		वापस 0;

	वापस pv->N1 * pv->N2 * pv->refclk / (pv->M1 * pv->M2) >> pv->log2P;
पूर्ण

पूर्णांक
nouveau_hw_get_घड़ी(काष्ठा drm_device *dev, क्रमागत nvbios_pll_type plltype)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	काष्ठा nvkm_pll_vals pllvals;
	पूर्णांक ret;
	पूर्णांक करोमुख्य;

	करोमुख्य = pci_करोमुख्य_nr(pdev->bus);

	अगर (plltype == PLL_MEMORY &&
	    (pdev->device & 0x0ff0) == CHIPSET_NFORCE) अणु
		uपूर्णांक32_t mpllP;
		pci_पढ़ो_config_dword(pci_get_करोमुख्य_bus_and_slot(करोमुख्य, 0, 3),
				      0x6c, &mpllP);
		mpllP = (mpllP >> 8) & 0xf;
		अगर (!mpllP)
			mpllP = 4;

		वापस 400000 / mpllP;
	पूर्ण अन्यथा
	अगर (plltype == PLL_MEMORY &&
	    (pdev->device & 0xff0) == CHIPSET_NFORCE2) अणु
		uपूर्णांक32_t घड़ी;

		pci_पढ़ो_config_dword(pci_get_करोमुख्य_bus_and_slot(करोमुख्य, 0, 5),
				      0x4c, &घड़ी);
		वापस घड़ी / 1000;
	पूर्ण

	ret = nouveau_hw_get_pllvals(dev, plltype, &pllvals);
	अगर (ret)
		वापस ret;

	वापस nouveau_hw_pllvals_to_clk(&pllvals);
पूर्ण

अटल व्योम
nouveau_hw_fix_bad_vpll(काष्ठा drm_device *dev, पूर्णांक head)
अणु
	/* the vpll on an unused head can come up with a अक्रमom value, way
	 * beyond the pll limits.  क्रम some reason this causes the chip to
	 * lock up when पढ़ोing the dac palette regs, so set a valid pll here
	 * when such a condition detected.  only seen on nv11 to date
	 */

	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvअगर_device *device = &drm->client.device;
	काष्ठा nvkm_clk *clk = nvxx_clk(device);
	काष्ठा nvkm_bios *bios = nvxx_bios(device);
	काष्ठा nvbios_pll pll_lim;
	काष्ठा nvkm_pll_vals pv;
	क्रमागत nvbios_pll_type pll = head ? PLL_VPLL1 : PLL_VPLL0;

	अगर (nvbios_pll_parse(bios, pll, &pll_lim))
		वापस;
	nouveau_hw_get_pllvals(dev, pll, &pv);

	अगर (pv.M1 >= pll_lim.vco1.min_m && pv.M1 <= pll_lim.vco1.max_m &&
	    pv.N1 >= pll_lim.vco1.min_n && pv.N1 <= pll_lim.vco1.max_n &&
	    pv.log2P <= pll_lim.max_p)
		वापस;

	NV_WARN(drm, "VPLL %d outwith limits, attempting to fix\n", head + 1);

	/* set lowest घड़ी within अटल limits */
	pv.M1 = pll_lim.vco1.max_m;
	pv.N1 = pll_lim.vco1.min_n;
	pv.log2P = pll_lim.max_p_usable;
	clk->pll_prog(clk, pll_lim.reg, &pv);
पूर्ण

/*
 * vga font save/restore
 */

अटल व्योम nouveau_vga_font_io(काष्ठा drm_device *dev,
				व्योम __iomem *iovram,
				bool save, अचिन्हित plane)
अणु
	अचिन्हित i;

	NVWriteVgaSeq(dev, 0, NV_VIO_SR_PLANE_MASK_INDEX, 1 << plane);
	NVWriteVgaGr(dev, 0, NV_VIO_GX_READ_MAP_INDEX, plane);
	क्रम (i = 0; i < 16384; i++) अणु
		अगर (save) अणु
			nv04_display(dev)->saved_vga_font[plane][i] =
					ioपढ़ो32_native(iovram + i * 4);
		पूर्ण अन्यथा अणु
			ioग_लिखो32_native(nv04_display(dev)->saved_vga_font[plane][i],
							iovram + i * 4);
		पूर्ण
	पूर्ण
पूर्ण

व्योम
nouveau_hw_save_vga_fonts(काष्ठा drm_device *dev, bool save)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	uपूर्णांक8_t misc, gr4, gr5, gr6, seq2, seq4;
	bool graphicsmode;
	अचिन्हित plane;
	व्योम __iomem *iovram;

	अगर (nv_two_heads(dev))
		NVSetOwner(dev, 0);

	NVSetEnablePalette(dev, 0, true);
	graphicsmode = NVReadVgaAttr(dev, 0, NV_CIO_AR_MODE_INDEX) & 1;
	NVSetEnablePalette(dev, 0, false);

	अगर (graphicsmode) /* graphics mode => framebuffer => no need to save */
		वापस;

	NV_INFO(drm, "%sing VGA fonts\n", save ? "Sav" : "Restor");

	/* map first 64KiB of VRAM, holds VGA fonts etc */
	iovram = ioremap(pci_resource_start(pdev, 1), 65536);
	अगर (!iovram) अणु
		NV_ERROR(drm, "Failed to map VRAM, "
					"cannot save/restore VGA fonts.\n");
		वापस;
	पूर्ण

	अगर (nv_two_heads(dev))
		NVBlankScreen(dev, 1, true);
	NVBlankScreen(dev, 0, true);

	/* save control regs */
	misc = NVReadPRMVIO(dev, 0, NV_PRMVIO_MISC__READ);
	seq2 = NVReadVgaSeq(dev, 0, NV_VIO_SR_PLANE_MASK_INDEX);
	seq4 = NVReadVgaSeq(dev, 0, NV_VIO_SR_MEM_MODE_INDEX);
	gr4 = NVReadVgaGr(dev, 0, NV_VIO_GX_READ_MAP_INDEX);
	gr5 = NVReadVgaGr(dev, 0, NV_VIO_GX_MODE_INDEX);
	gr6 = NVReadVgaGr(dev, 0, NV_VIO_GX_MISC_INDEX);

	NVWritePRMVIO(dev, 0, NV_PRMVIO_MISC__WRITE, 0x67);
	NVWriteVgaSeq(dev, 0, NV_VIO_SR_MEM_MODE_INDEX, 0x6);
	NVWriteVgaGr(dev, 0, NV_VIO_GX_MODE_INDEX, 0x0);
	NVWriteVgaGr(dev, 0, NV_VIO_GX_MISC_INDEX, 0x5);

	/* store font in planes 0..3 */
	क्रम (plane = 0; plane < 4; plane++)
		nouveau_vga_font_io(dev, iovram, save, plane);

	/* restore control regs */
	NVWritePRMVIO(dev, 0, NV_PRMVIO_MISC__WRITE, misc);
	NVWriteVgaGr(dev, 0, NV_VIO_GX_READ_MAP_INDEX, gr4);
	NVWriteVgaGr(dev, 0, NV_VIO_GX_MODE_INDEX, gr5);
	NVWriteVgaGr(dev, 0, NV_VIO_GX_MISC_INDEX, gr6);
	NVWriteVgaSeq(dev, 0, NV_VIO_SR_PLANE_MASK_INDEX, seq2);
	NVWriteVgaSeq(dev, 0, NV_VIO_SR_MEM_MODE_INDEX, seq4);

	अगर (nv_two_heads(dev))
		NVBlankScreen(dev, 1, false);
	NVBlankScreen(dev, 0, false);

	iounmap(iovram);
पूर्ण

/*
 * mode state save/load
 */

अटल व्योम
rd_cio_state(काष्ठा drm_device *dev, पूर्णांक head,
	     काष्ठा nv04_crtc_reg *crtcstate, पूर्णांक index)
अणु
	crtcstate->CRTC[index] = NVReadVgaCrtc(dev, head, index);
पूर्ण

अटल व्योम
wr_cio_state(काष्ठा drm_device *dev, पूर्णांक head,
	     काष्ठा nv04_crtc_reg *crtcstate, पूर्णांक index)
अणु
	NVWriteVgaCrtc(dev, head, index, crtcstate->CRTC[index]);
पूर्ण

अटल व्योम
nv_save_state_ramdac(काष्ठा drm_device *dev, पूर्णांक head,
		     काष्ठा nv04_mode_state *state)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nv04_crtc_reg *regp = &state->crtc_reg[head];
	पूर्णांक i;

	अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_CELSIUS)
		regp->nv10_cursync = NVReadRAMDAC(dev, head, NV_RAMDAC_NV10_CURSYNC);

	nouveau_hw_get_pllvals(dev, head ? PLL_VPLL1 : PLL_VPLL0, &regp->pllvals);
	state->pllsel = NVReadRAMDAC(dev, 0, NV_PRAMDAC_PLL_COEFF_SELECT);
	अगर (nv_two_heads(dev))
		state->sel_clk = NVReadRAMDAC(dev, 0, NV_PRAMDAC_SEL_CLK);
	अगर (drm->client.device.info.chipset == 0x11)
		regp->dither = NVReadRAMDAC(dev, head, NV_RAMDAC_DITHER_NV11);

	regp->ramdac_gen_ctrl = NVReadRAMDAC(dev, head, NV_PRAMDAC_GENERAL_CONTROL);

	अगर (nv_gf4_disp_arch(dev))
		regp->ramdac_630 = NVReadRAMDAC(dev, head, NV_PRAMDAC_630);
	अगर (drm->client.device.info.chipset >= 0x30)
		regp->ramdac_634 = NVReadRAMDAC(dev, head, NV_PRAMDAC_634);

	regp->tv_setup = NVReadRAMDAC(dev, head, NV_PRAMDAC_TV_SETUP);
	regp->tv_vtotal = NVReadRAMDAC(dev, head, NV_PRAMDAC_TV_VTOTAL);
	regp->tv_vskew = NVReadRAMDAC(dev, head, NV_PRAMDAC_TV_VSKEW);
	regp->tv_vsync_delay = NVReadRAMDAC(dev, head, NV_PRAMDAC_TV_VSYNC_DELAY);
	regp->tv_htotal = NVReadRAMDAC(dev, head, NV_PRAMDAC_TV_HTOTAL);
	regp->tv_hskew = NVReadRAMDAC(dev, head, NV_PRAMDAC_TV_HSKEW);
	regp->tv_hsync_delay = NVReadRAMDAC(dev, head, NV_PRAMDAC_TV_HSYNC_DELAY);
	regp->tv_hsync_delay2 = NVReadRAMDAC(dev, head, NV_PRAMDAC_TV_HSYNC_DELAY2);

	क्रम (i = 0; i < 7; i++) अणु
		uपूर्णांक32_t ramdac_reg = NV_PRAMDAC_FP_VDISPLAY_END + (i * 4);
		regp->fp_vert_regs[i] = NVReadRAMDAC(dev, head, ramdac_reg);
		regp->fp_horiz_regs[i] = NVReadRAMDAC(dev, head, ramdac_reg + 0x20);
	पूर्ण

	अगर (nv_gf4_disp_arch(dev)) अणु
		regp->dither = NVReadRAMDAC(dev, head, NV_RAMDAC_FP_DITHER);
		क्रम (i = 0; i < 3; i++) अणु
			regp->dither_regs[i] = NVReadRAMDAC(dev, head, NV_PRAMDAC_850 + i * 4);
			regp->dither_regs[i + 3] = NVReadRAMDAC(dev, head, NV_PRAMDAC_85C + i * 4);
		पूर्ण
	पूर्ण

	regp->fp_control = NVReadRAMDAC(dev, head, NV_PRAMDAC_FP_TG_CONTROL);
	regp->fp_debug_0 = NVReadRAMDAC(dev, head, NV_PRAMDAC_FP_DEBUG_0);
	अगर (!nv_gf4_disp_arch(dev) && head == 0) अणु
		/* early chips करोn't allow access to PRAMDAC_TMDS_* without
		 * the head A FPCLK on (nv11 even locks up) */
		NVWriteRAMDAC(dev, 0, NV_PRAMDAC_FP_DEBUG_0, regp->fp_debug_0 &
			      ~NV_PRAMDAC_FP_DEBUG_0_PWRDOWN_FPCLK);
	पूर्ण
	regp->fp_debug_1 = NVReadRAMDAC(dev, head, NV_PRAMDAC_FP_DEBUG_1);
	regp->fp_debug_2 = NVReadRAMDAC(dev, head, NV_PRAMDAC_FP_DEBUG_2);

	regp->fp_margin_color = NVReadRAMDAC(dev, head, NV_PRAMDAC_FP_MARGIN_COLOR);

	अगर (nv_gf4_disp_arch(dev))
		regp->ramdac_8c0 = NVReadRAMDAC(dev, head, NV_PRAMDAC_8C0);

	अगर (drm->client.device.info.family == NV_DEVICE_INFO_V0_CURIE) अणु
		regp->ramdac_a20 = NVReadRAMDAC(dev, head, NV_PRAMDAC_A20);
		regp->ramdac_a24 = NVReadRAMDAC(dev, head, NV_PRAMDAC_A24);
		regp->ramdac_a34 = NVReadRAMDAC(dev, head, NV_PRAMDAC_A34);

		क्रम (i = 0; i < 38; i++)
			regp->ctv_regs[i] = NVReadRAMDAC(dev, head,
							 NV_PRAMDAC_CTV + 4*i);
	पूर्ण
पूर्ण

अटल व्योम
nv_load_state_ramdac(काष्ठा drm_device *dev, पूर्णांक head,
		     काष्ठा nv04_mode_state *state)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvkm_clk *clk = nvxx_clk(&drm->client.device);
	काष्ठा nv04_crtc_reg *regp = &state->crtc_reg[head];
	uपूर्णांक32_t pllreg = head ? NV_RAMDAC_VPLL2 : NV_PRAMDAC_VPLL_COEFF;
	पूर्णांक i;

	अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_CELSIUS)
		NVWriteRAMDAC(dev, head, NV_RAMDAC_NV10_CURSYNC, regp->nv10_cursync);

	clk->pll_prog(clk, pllreg, &regp->pllvals);
	NVWriteRAMDAC(dev, 0, NV_PRAMDAC_PLL_COEFF_SELECT, state->pllsel);
	अगर (nv_two_heads(dev))
		NVWriteRAMDAC(dev, 0, NV_PRAMDAC_SEL_CLK, state->sel_clk);
	अगर (drm->client.device.info.chipset == 0x11)
		NVWriteRAMDAC(dev, head, NV_RAMDAC_DITHER_NV11, regp->dither);

	NVWriteRAMDAC(dev, head, NV_PRAMDAC_GENERAL_CONTROL, regp->ramdac_gen_ctrl);

	अगर (nv_gf4_disp_arch(dev))
		NVWriteRAMDAC(dev, head, NV_PRAMDAC_630, regp->ramdac_630);
	अगर (drm->client.device.info.chipset >= 0x30)
		NVWriteRAMDAC(dev, head, NV_PRAMDAC_634, regp->ramdac_634);

	NVWriteRAMDAC(dev, head, NV_PRAMDAC_TV_SETUP, regp->tv_setup);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_TV_VTOTAL, regp->tv_vtotal);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_TV_VSKEW, regp->tv_vskew);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_TV_VSYNC_DELAY, regp->tv_vsync_delay);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_TV_HTOTAL, regp->tv_htotal);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_TV_HSKEW, regp->tv_hskew);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_TV_HSYNC_DELAY, regp->tv_hsync_delay);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_TV_HSYNC_DELAY2, regp->tv_hsync_delay2);

	क्रम (i = 0; i < 7; i++) अणु
		uपूर्णांक32_t ramdac_reg = NV_PRAMDAC_FP_VDISPLAY_END + (i * 4);

		NVWriteRAMDAC(dev, head, ramdac_reg, regp->fp_vert_regs[i]);
		NVWriteRAMDAC(dev, head, ramdac_reg + 0x20, regp->fp_horiz_regs[i]);
	पूर्ण

	अगर (nv_gf4_disp_arch(dev)) अणु
		NVWriteRAMDAC(dev, head, NV_RAMDAC_FP_DITHER, regp->dither);
		क्रम (i = 0; i < 3; i++) अणु
			NVWriteRAMDAC(dev, head, NV_PRAMDAC_850 + i * 4, regp->dither_regs[i]);
			NVWriteRAMDAC(dev, head, NV_PRAMDAC_85C + i * 4, regp->dither_regs[i + 3]);
		पूर्ण
	पूर्ण

	NVWriteRAMDAC(dev, head, NV_PRAMDAC_FP_TG_CONTROL, regp->fp_control);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_FP_DEBUG_0, regp->fp_debug_0);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_FP_DEBUG_1, regp->fp_debug_1);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_FP_DEBUG_2, regp->fp_debug_2);

	NVWriteRAMDAC(dev, head, NV_PRAMDAC_FP_MARGIN_COLOR, regp->fp_margin_color);

	अगर (nv_gf4_disp_arch(dev))
		NVWriteRAMDAC(dev, head, NV_PRAMDAC_8C0, regp->ramdac_8c0);

	अगर (drm->client.device.info.family == NV_DEVICE_INFO_V0_CURIE) अणु
		NVWriteRAMDAC(dev, head, NV_PRAMDAC_A20, regp->ramdac_a20);
		NVWriteRAMDAC(dev, head, NV_PRAMDAC_A24, regp->ramdac_a24);
		NVWriteRAMDAC(dev, head, NV_PRAMDAC_A34, regp->ramdac_a34);

		क्रम (i = 0; i < 38; i++)
			NVWriteRAMDAC(dev, head,
				      NV_PRAMDAC_CTV + 4*i, regp->ctv_regs[i]);
	पूर्ण
पूर्ण

अटल व्योम
nv_save_state_vga(काष्ठा drm_device *dev, पूर्णांक head,
		  काष्ठा nv04_mode_state *state)
अणु
	काष्ठा nv04_crtc_reg *regp = &state->crtc_reg[head];
	पूर्णांक i;

	regp->MiscOutReg = NVReadPRMVIO(dev, head, NV_PRMVIO_MISC__READ);

	क्रम (i = 0; i < 25; i++)
		rd_cio_state(dev, head, regp, i);

	NVSetEnablePalette(dev, head, true);
	क्रम (i = 0; i < 21; i++)
		regp->Attribute[i] = NVReadVgaAttr(dev, head, i);
	NVSetEnablePalette(dev, head, false);

	क्रम (i = 0; i < 9; i++)
		regp->Graphics[i] = NVReadVgaGr(dev, head, i);

	क्रम (i = 0; i < 5; i++)
		regp->Sequencer[i] = NVReadVgaSeq(dev, head, i);
पूर्ण

अटल व्योम
nv_load_state_vga(काष्ठा drm_device *dev, पूर्णांक head,
		  काष्ठा nv04_mode_state *state)
अणु
	काष्ठा nv04_crtc_reg *regp = &state->crtc_reg[head];
	पूर्णांक i;

	NVWritePRMVIO(dev, head, NV_PRMVIO_MISC__WRITE, regp->MiscOutReg);

	क्रम (i = 0; i < 5; i++)
		NVWriteVgaSeq(dev, head, i, regp->Sequencer[i]);

	nv_lock_vga_crtc_base(dev, head, false);
	क्रम (i = 0; i < 25; i++)
		wr_cio_state(dev, head, regp, i);
	nv_lock_vga_crtc_base(dev, head, true);

	क्रम (i = 0; i < 9; i++)
		NVWriteVgaGr(dev, head, i, regp->Graphics[i]);

	NVSetEnablePalette(dev, head, true);
	क्रम (i = 0; i < 21; i++)
		NVWriteVgaAttr(dev, head, i, regp->Attribute[i]);
	NVSetEnablePalette(dev, head, false);
पूर्ण

अटल व्योम
nv_save_state_ext(काष्ठा drm_device *dev, पूर्णांक head,
		  काष्ठा nv04_mode_state *state)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nv04_crtc_reg *regp = &state->crtc_reg[head];
	पूर्णांक i;

	rd_cio_state(dev, head, regp, NV_CIO_CRE_LCD__INDEX);
	rd_cio_state(dev, head, regp, NV_CIO_CRE_RPC0_INDEX);
	rd_cio_state(dev, head, regp, NV_CIO_CRE_RPC1_INDEX);
	rd_cio_state(dev, head, regp, NV_CIO_CRE_LSR_INDEX);
	rd_cio_state(dev, head, regp, NV_CIO_CRE_PIXEL_INDEX);
	rd_cio_state(dev, head, regp, NV_CIO_CRE_HEB__INDEX);
	rd_cio_state(dev, head, regp, NV_CIO_CRE_ENH_INDEX);

	rd_cio_state(dev, head, regp, NV_CIO_CRE_FF_INDEX);
	rd_cio_state(dev, head, regp, NV_CIO_CRE_FFLWM__INDEX);
	rd_cio_state(dev, head, regp, NV_CIO_CRE_21);

	अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_KELVIN)
		rd_cio_state(dev, head, regp, NV_CIO_CRE_47);

	अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_RANKINE)
		rd_cio_state(dev, head, regp, 0x9f);

	rd_cio_state(dev, head, regp, NV_CIO_CRE_49);
	rd_cio_state(dev, head, regp, NV_CIO_CRE_HCUR_ADDR0_INDEX);
	rd_cio_state(dev, head, regp, NV_CIO_CRE_HCUR_ADDR1_INDEX);
	rd_cio_state(dev, head, regp, NV_CIO_CRE_HCUR_ADDR2_INDEX);
	rd_cio_state(dev, head, regp, NV_CIO_CRE_ILACE__INDEX);

	अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_CELSIUS) अणु
		regp->crtc_830 = NVReadCRTC(dev, head, NV_PCRTC_830);
		regp->crtc_834 = NVReadCRTC(dev, head, NV_PCRTC_834);

		अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_RANKINE)
			regp->gpio_ext = NVReadCRTC(dev, head, NV_PCRTC_GPIO_EXT);

		अगर (drm->client.device.info.family == NV_DEVICE_INFO_V0_CURIE)
			regp->crtc_850 = NVReadCRTC(dev, head, NV_PCRTC_850);

		अगर (nv_two_heads(dev))
			regp->crtc_eng_ctrl = NVReadCRTC(dev, head, NV_PCRTC_ENGINE_CTRL);
		regp->cursor_cfg = NVReadCRTC(dev, head, NV_PCRTC_CURSOR_CONFIG);
	पूर्ण

	regp->crtc_cfg = NVReadCRTC(dev, head, NV_PCRTC_CONFIG);

	rd_cio_state(dev, head, regp, NV_CIO_CRE_SCRATCH3__INDEX);
	rd_cio_state(dev, head, regp, NV_CIO_CRE_SCRATCH4__INDEX);
	अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_CELSIUS) अणु
		rd_cio_state(dev, head, regp, NV_CIO_CRE_EBR_INDEX);
		rd_cio_state(dev, head, regp, NV_CIO_CRE_CSB);
		rd_cio_state(dev, head, regp, NV_CIO_CRE_4B);
		rd_cio_state(dev, head, regp, NV_CIO_CRE_TVOUT_LATENCY);
	पूर्ण
	/* NV11 and NV20 करोn't have this, they stop at 0x52. */
	अगर (nv_gf4_disp_arch(dev)) अणु
		rd_cio_state(dev, head, regp, NV_CIO_CRE_42);
		rd_cio_state(dev, head, regp, NV_CIO_CRE_53);
		rd_cio_state(dev, head, regp, NV_CIO_CRE_54);

		क्रम (i = 0; i < 0x10; i++)
			regp->CR58[i] = NVReadVgaCrtc5758(dev, head, i);
		rd_cio_state(dev, head, regp, NV_CIO_CRE_59);
		rd_cio_state(dev, head, regp, NV_CIO_CRE_5B);

		rd_cio_state(dev, head, regp, NV_CIO_CRE_85);
		rd_cio_state(dev, head, regp, NV_CIO_CRE_86);
	पूर्ण

	regp->fb_start = NVReadCRTC(dev, head, NV_PCRTC_START);
पूर्ण

अटल व्योम
nv_load_state_ext(काष्ठा drm_device *dev, पूर्णांक head,
		  काष्ठा nv04_mode_state *state)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvअगर_object *device = &drm->client.device.object;
	काष्ठा nv04_crtc_reg *regp = &state->crtc_reg[head];
	uपूर्णांक32_t reg900;
	पूर्णांक i;

	अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_CELSIUS) अणु
		अगर (nv_two_heads(dev))
			/* setting ENGINE_CTRL (EC) *must* come beक्रमe
			 * CIO_CRE_LCD, as writing CRE_LCD sets bits 16 & 17 in
			 * EC that should not be overwritten by writing stale EC
			 */
			NVWriteCRTC(dev, head, NV_PCRTC_ENGINE_CTRL, regp->crtc_eng_ctrl);

		nvअगर_wr32(device, NV_PVIDEO_STOP, 1);
		nvअगर_wr32(device, NV_PVIDEO_INTR_EN, 0);
		nvअगर_wr32(device, NV_PVIDEO_OFFSET_BUFF(0), 0);
		nvअगर_wr32(device, NV_PVIDEO_OFFSET_BUFF(1), 0);
		nvअगर_wr32(device, NV_PVIDEO_LIMIT(0), drm->client.device.info.ram_size - 1);
		nvअगर_wr32(device, NV_PVIDEO_LIMIT(1), drm->client.device.info.ram_size - 1);
		nvअगर_wr32(device, NV_PVIDEO_UVPLANE_LIMIT(0), drm->client.device.info.ram_size - 1);
		nvअगर_wr32(device, NV_PVIDEO_UVPLANE_LIMIT(1), drm->client.device.info.ram_size - 1);
		nvअगर_wr32(device, NV_PBUS_POWERCTRL_2, 0);

		NVWriteCRTC(dev, head, NV_PCRTC_CURSOR_CONFIG, regp->cursor_cfg);
		NVWriteCRTC(dev, head, NV_PCRTC_830, regp->crtc_830);
		NVWriteCRTC(dev, head, NV_PCRTC_834, regp->crtc_834);

		अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_RANKINE)
			NVWriteCRTC(dev, head, NV_PCRTC_GPIO_EXT, regp->gpio_ext);

		अगर (drm->client.device.info.family == NV_DEVICE_INFO_V0_CURIE) अणु
			NVWriteCRTC(dev, head, NV_PCRTC_850, regp->crtc_850);

			reg900 = NVReadRAMDAC(dev, head, NV_PRAMDAC_900);
			अगर (regp->crtc_cfg == NV10_PCRTC_CONFIG_START_ADDRESS_HSYNC)
				NVWriteRAMDAC(dev, head, NV_PRAMDAC_900, reg900 | 0x10000);
			अन्यथा
				NVWriteRAMDAC(dev, head, NV_PRAMDAC_900, reg900 & ~0x10000);
		पूर्ण
	पूर्ण

	NVWriteCRTC(dev, head, NV_PCRTC_CONFIG, regp->crtc_cfg);

	wr_cio_state(dev, head, regp, NV_CIO_CRE_RPC0_INDEX);
	wr_cio_state(dev, head, regp, NV_CIO_CRE_RPC1_INDEX);
	wr_cio_state(dev, head, regp, NV_CIO_CRE_LSR_INDEX);
	wr_cio_state(dev, head, regp, NV_CIO_CRE_PIXEL_INDEX);
	wr_cio_state(dev, head, regp, NV_CIO_CRE_LCD__INDEX);
	wr_cio_state(dev, head, regp, NV_CIO_CRE_HEB__INDEX);
	wr_cio_state(dev, head, regp, NV_CIO_CRE_ENH_INDEX);
	wr_cio_state(dev, head, regp, NV_CIO_CRE_FF_INDEX);
	wr_cio_state(dev, head, regp, NV_CIO_CRE_FFLWM__INDEX);

	अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_KELVIN)
		wr_cio_state(dev, head, regp, NV_CIO_CRE_47);

	अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_RANKINE)
		wr_cio_state(dev, head, regp, 0x9f);

	wr_cio_state(dev, head, regp, NV_CIO_CRE_49);
	wr_cio_state(dev, head, regp, NV_CIO_CRE_HCUR_ADDR0_INDEX);
	wr_cio_state(dev, head, regp, NV_CIO_CRE_HCUR_ADDR1_INDEX);
	wr_cio_state(dev, head, regp, NV_CIO_CRE_HCUR_ADDR2_INDEX);
	अगर (drm->client.device.info.family == NV_DEVICE_INFO_V0_CURIE)
		nv_fix_nv40_hw_cursor(dev, head);
	wr_cio_state(dev, head, regp, NV_CIO_CRE_ILACE__INDEX);

	wr_cio_state(dev, head, regp, NV_CIO_CRE_SCRATCH3__INDEX);
	wr_cio_state(dev, head, regp, NV_CIO_CRE_SCRATCH4__INDEX);
	अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_CELSIUS) अणु
		wr_cio_state(dev, head, regp, NV_CIO_CRE_EBR_INDEX);
		wr_cio_state(dev, head, regp, NV_CIO_CRE_CSB);
		wr_cio_state(dev, head, regp, NV_CIO_CRE_4B);
		wr_cio_state(dev, head, regp, NV_CIO_CRE_TVOUT_LATENCY);
	पूर्ण
	/* NV11 and NV20 stop at 0x52. */
	अगर (nv_gf4_disp_arch(dev)) अणु
		अगर (drm->client.device.info.family < NV_DEVICE_INFO_V0_KELVIN) अणु
			/* Not रुकोing क्रम vertical retrace beक्रमe modअगरying
			   CRE_53/CRE_54 causes lockups. */
			nvअगर_msec(&drm->client.device, 650,
				अगर ( (nvअगर_rd32(device, NV_PRMCIO_INP0__COLOR) & 8))
					अवरोध;
			);
			nvअगर_msec(&drm->client.device, 650,
				अगर (!(nvअगर_rd32(device, NV_PRMCIO_INP0__COLOR) & 8))
					अवरोध;
			);
		पूर्ण

		wr_cio_state(dev, head, regp, NV_CIO_CRE_42);
		wr_cio_state(dev, head, regp, NV_CIO_CRE_53);
		wr_cio_state(dev, head, regp, NV_CIO_CRE_54);

		क्रम (i = 0; i < 0x10; i++)
			NVWriteVgaCrtc5758(dev, head, i, regp->CR58[i]);
		wr_cio_state(dev, head, regp, NV_CIO_CRE_59);
		wr_cio_state(dev, head, regp, NV_CIO_CRE_5B);

		wr_cio_state(dev, head, regp, NV_CIO_CRE_85);
		wr_cio_state(dev, head, regp, NV_CIO_CRE_86);
	पूर्ण

	NVWriteCRTC(dev, head, NV_PCRTC_START, regp->fb_start);
पूर्ण

अटल व्योम
nv_save_state_palette(काष्ठा drm_device *dev, पूर्णांक head,
		      काष्ठा nv04_mode_state *state)
अणु
	काष्ठा nvअगर_object *device = &nouveau_drm(dev)->client.device.object;
	पूर्णांक head_offset = head * NV_PRMDIO_SIZE, i;

	nvअगर_wr08(device, NV_PRMDIO_PIXEL_MASK + head_offset,
				NV_PRMDIO_PIXEL_MASK_MASK);
	nvअगर_wr08(device, NV_PRMDIO_READ_MODE_ADDRESS + head_offset, 0x0);

	क्रम (i = 0; i < 768; i++) अणु
		state->crtc_reg[head].DAC[i] = nvअगर_rd08(device,
				NV_PRMDIO_PALETTE_DATA + head_offset);
	पूर्ण

	NVSetEnablePalette(dev, head, false);
पूर्ण

व्योम
nouveau_hw_load_state_palette(काष्ठा drm_device *dev, पूर्णांक head,
			      काष्ठा nv04_mode_state *state)
अणु
	काष्ठा nvअगर_object *device = &nouveau_drm(dev)->client.device.object;
	पूर्णांक head_offset = head * NV_PRMDIO_SIZE, i;

	nvअगर_wr08(device, NV_PRMDIO_PIXEL_MASK + head_offset,
				NV_PRMDIO_PIXEL_MASK_MASK);
	nvअगर_wr08(device, NV_PRMDIO_WRITE_MODE_ADDRESS + head_offset, 0x0);

	क्रम (i = 0; i < 768; i++) अणु
		nvअगर_wr08(device, NV_PRMDIO_PALETTE_DATA + head_offset,
				state->crtc_reg[head].DAC[i]);
	पूर्ण

	NVSetEnablePalette(dev, head, false);
पूर्ण

व्योम nouveau_hw_save_state(काष्ठा drm_device *dev, पूर्णांक head,
			   काष्ठा nv04_mode_state *state)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);

	अगर (drm->client.device.info.chipset == 0x11)
		/* NB: no attempt is made to restore the bad pll later on */
		nouveau_hw_fix_bad_vpll(dev, head);
	nv_save_state_ramdac(dev, head, state);
	nv_save_state_vga(dev, head, state);
	nv_save_state_palette(dev, head, state);
	nv_save_state_ext(dev, head, state);
पूर्ण

व्योम nouveau_hw_load_state(काष्ठा drm_device *dev, पूर्णांक head,
			   काष्ठा nv04_mode_state *state)
अणु
	NVVgaProtect(dev, head, true);
	nv_load_state_ramdac(dev, head, state);
	nv_load_state_ext(dev, head, state);
	nouveau_hw_load_state_palette(dev, head, state);
	nv_load_state_vga(dev, head, state);
	NVVgaProtect(dev, head, false);
पूर्ण
