<शैली गुरु>
/*
 * Copyright 2008 Stuart Bennett
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

#अगर_अघोषित __NOUVEAU_HW_H__
#घोषणा __NOUVEAU_HW_H__

#समावेश "disp.h"
#समावेश "nvreg.h"

#समावेश <subdev/bios/pll.h>

#घोषणा MASK(field) ( \
	(0xffffffff >> (31 - ((1 ? field) - (0 ? field)))) << (0 ? field))

#घोषणा XLATE(src, srclowbit, outfield) ( \
	(((src) >> (srclowbit)) << (0 ? outfield)) & MASK(outfield))

व्योम NVWriteVgaSeq(काष्ठा drm_device *, पूर्णांक head, uपूर्णांक8_t index, uपूर्णांक8_t value);
uपूर्णांक8_t NVReadVgaSeq(काष्ठा drm_device *, पूर्णांक head, uपूर्णांक8_t index);
व्योम NVWriteVgaGr(काष्ठा drm_device *, पूर्णांक head, uपूर्णांक8_t index, uपूर्णांक8_t value);
uपूर्णांक8_t NVReadVgaGr(काष्ठा drm_device *, पूर्णांक head, uपूर्णांक8_t index);
व्योम NVSetOwner(काष्ठा drm_device *, पूर्णांक owner);
व्योम NVBlankScreen(काष्ठा drm_device *, पूर्णांक head, bool blank);
पूर्णांक nouveau_hw_get_pllvals(काष्ठा drm_device *, क्रमागत nvbios_pll_type plltype,
			   काष्ठा nvkm_pll_vals *pllvals);
पूर्णांक nouveau_hw_pllvals_to_clk(काष्ठा nvkm_pll_vals *pllvals);
पूर्णांक nouveau_hw_get_घड़ी(काष्ठा drm_device *, क्रमागत nvbios_pll_type plltype);
व्योम nouveau_hw_save_vga_fonts(काष्ठा drm_device *, bool save);
व्योम nouveau_hw_save_state(काष्ठा drm_device *, पूर्णांक head,
			   काष्ठा nv04_mode_state *state);
व्योम nouveau_hw_load_state(काष्ठा drm_device *, पूर्णांक head,
			   काष्ठा nv04_mode_state *state);
व्योम nouveau_hw_load_state_palette(काष्ठा drm_device *, पूर्णांक head,
				   काष्ठा nv04_mode_state *state);

/* nouveau_calc.c */
बाह्य व्योम nouveau_calc_arb(काष्ठा drm_device *, पूर्णांक vclk, पूर्णांक bpp,
			     पूर्णांक *burst, पूर्णांक *lwm);

अटल अंतरभूत uपूर्णांक32_t NVReadCRTC(काष्ठा drm_device *dev,
					पूर्णांक head, uपूर्णांक32_t reg)
अणु
	काष्ठा nvअगर_object *device = &nouveau_drm(dev)->client.device.object;
	uपूर्णांक32_t val;
	अगर (head)
		reg += NV_PCRTC0_SIZE;
	val = nvअगर_rd32(device, reg);
	वापस val;
पूर्ण

अटल अंतरभूत व्योम NVWriteCRTC(काष्ठा drm_device *dev,
					पूर्णांक head, uपूर्णांक32_t reg, uपूर्णांक32_t val)
अणु
	काष्ठा nvअगर_object *device = &nouveau_drm(dev)->client.device.object;
	अगर (head)
		reg += NV_PCRTC0_SIZE;
	nvअगर_wr32(device, reg, val);
पूर्ण

अटल अंतरभूत uपूर्णांक32_t NVReadRAMDAC(काष्ठा drm_device *dev,
					पूर्णांक head, uपूर्णांक32_t reg)
अणु
	काष्ठा nvअगर_object *device = &nouveau_drm(dev)->client.device.object;
	uपूर्णांक32_t val;
	अगर (head)
		reg += NV_PRAMDAC0_SIZE;
	val = nvअगर_rd32(device, reg);
	वापस val;
पूर्ण

अटल अंतरभूत व्योम NVWriteRAMDAC(काष्ठा drm_device *dev,
					पूर्णांक head, uपूर्णांक32_t reg, uपूर्णांक32_t val)
अणु
	काष्ठा nvअगर_object *device = &nouveau_drm(dev)->client.device.object;
	अगर (head)
		reg += NV_PRAMDAC0_SIZE;
	nvअगर_wr32(device, reg, val);
पूर्ण

अटल अंतरभूत uपूर्णांक8_t nv_पढ़ो_पंचांगds(काष्ठा drm_device *dev,
					पूर्णांक or, पूर्णांक dl, uपूर्णांक8_t address)
अणु
	पूर्णांक ramdac = (or & DCB_OUTPUT_C) >> 2;

	NVWriteRAMDAC(dev, ramdac, NV_PRAMDAC_FP_TMDS_CONTROL + dl * 8,
	NV_PRAMDAC_FP_TMDS_CONTROL_WRITE_DISABLE | address);
	वापस NVReadRAMDAC(dev, ramdac, NV_PRAMDAC_FP_TMDS_DATA + dl * 8);
पूर्ण

अटल अंतरभूत व्योम nv_ग_लिखो_पंचांगds(काष्ठा drm_device *dev,
					पूर्णांक or, पूर्णांक dl, uपूर्णांक8_t address,
					uपूर्णांक8_t data)
अणु
	पूर्णांक ramdac = (or & DCB_OUTPUT_C) >> 2;

	NVWriteRAMDAC(dev, ramdac, NV_PRAMDAC_FP_TMDS_DATA + dl * 8, data);
	NVWriteRAMDAC(dev, ramdac, NV_PRAMDAC_FP_TMDS_CONTROL + dl * 8, address);
पूर्ण

अटल अंतरभूत व्योम NVWriteVgaCrtc(काष्ठा drm_device *dev,
					पूर्णांक head, uपूर्णांक8_t index, uपूर्णांक8_t value)
अणु
	काष्ठा nvअगर_object *device = &nouveau_drm(dev)->client.device.object;
	nvअगर_wr08(device, NV_PRMCIO_CRX__COLOR + head * NV_PRMCIO_SIZE, index);
	nvअगर_wr08(device, NV_PRMCIO_CR__COLOR + head * NV_PRMCIO_SIZE, value);
पूर्ण

अटल अंतरभूत uपूर्णांक8_t NVReadVgaCrtc(काष्ठा drm_device *dev,
					पूर्णांक head, uपूर्णांक8_t index)
अणु
	काष्ठा nvअगर_object *device = &nouveau_drm(dev)->client.device.object;
	uपूर्णांक8_t val;
	nvअगर_wr08(device, NV_PRMCIO_CRX__COLOR + head * NV_PRMCIO_SIZE, index);
	val = nvअगर_rd08(device, NV_PRMCIO_CR__COLOR + head * NV_PRMCIO_SIZE);
	वापस val;
पूर्ण

/* CR57 and CR58 are a fun pair of regs. CR57 provides an index (0-0xf) क्रम CR58
 * I suspect they in fact करो nothing, but are merely a way to carry useful
 * per-head variables around
 *
 * Known uses:
 * CR57		CR58
 * 0x00		index to the appropriate dcb entry (or 7f क्रम inactive)
 * 0x02		dcb entry's "or" value (or 00 क्रम inactive)
 * 0x03		bit0 set क्रम dual link (LVDS, possibly अन्यथाwhere too)
 * 0x08 or 0x09	pxclk in MHz
 * 0x0f		laptop panel info -	low nibble क्रम PEXTDEV_BOOT_0 strap
 * 					high nibble क्रम xlat strap value
 */

अटल अंतरभूत व्योम
NVWriteVgaCrtc5758(काष्ठा drm_device *dev, पूर्णांक head, uपूर्णांक8_t index, uपूर्णांक8_t value)
अणु
	NVWriteVgaCrtc(dev, head, NV_CIO_CRE_57, index);
	NVWriteVgaCrtc(dev, head, NV_CIO_CRE_58, value);
पूर्ण

अटल अंतरभूत uपूर्णांक8_t NVReadVgaCrtc5758(काष्ठा drm_device *dev, पूर्णांक head, uपूर्णांक8_t index)
अणु
	NVWriteVgaCrtc(dev, head, NV_CIO_CRE_57, index);
	वापस NVReadVgaCrtc(dev, head, NV_CIO_CRE_58);
पूर्ण

अटल अंतरभूत uपूर्णांक8_t NVReadPRMVIO(काष्ठा drm_device *dev,
					पूर्णांक head, uपूर्णांक32_t reg)
अणु
	काष्ठा nvअगर_object *device = &nouveau_drm(dev)->client.device.object;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	uपूर्णांक8_t val;

	/* Only NV4x have two pvio ranges; other twoHeads cards MUST call
	 * NVSetOwner क्रम the relevant head to be programmed */
	अगर (head && drm->client.device.info.family == NV_DEVICE_INFO_V0_CURIE)
		reg += NV_PRMVIO_SIZE;

	val = nvअगर_rd08(device, reg);
	वापस val;
पूर्ण

अटल अंतरभूत व्योम NVWritePRMVIO(काष्ठा drm_device *dev,
					पूर्णांक head, uपूर्णांक32_t reg, uपूर्णांक8_t value)
अणु
	काष्ठा nvअगर_object *device = &nouveau_drm(dev)->client.device.object;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);

	/* Only NV4x have two pvio ranges; other twoHeads cards MUST call
	 * NVSetOwner क्रम the relevant head to be programmed */
	अगर (head && drm->client.device.info.family == NV_DEVICE_INFO_V0_CURIE)
		reg += NV_PRMVIO_SIZE;

	nvअगर_wr08(device, reg, value);
पूर्ण

अटल अंतरभूत व्योम NVSetEnablePalette(काष्ठा drm_device *dev, पूर्णांक head, bool enable)
अणु
	काष्ठा nvअगर_object *device = &nouveau_drm(dev)->client.device.object;
	nvअगर_rd08(device, NV_PRMCIO_INP0__COLOR + head * NV_PRMCIO_SIZE);
	nvअगर_wr08(device, NV_PRMCIO_ARX + head * NV_PRMCIO_SIZE, enable ? 0 : 0x20);
पूर्ण

अटल अंतरभूत bool NVGetEnablePalette(काष्ठा drm_device *dev, पूर्णांक head)
अणु
	काष्ठा nvअगर_object *device = &nouveau_drm(dev)->client.device.object;
	nvअगर_rd08(device, NV_PRMCIO_INP0__COLOR + head * NV_PRMCIO_SIZE);
	वापस !(nvअगर_rd08(device, NV_PRMCIO_ARX + head * NV_PRMCIO_SIZE) & 0x20);
पूर्ण

अटल अंतरभूत व्योम NVWriteVgaAttr(काष्ठा drm_device *dev,
					पूर्णांक head, uपूर्णांक8_t index, uपूर्णांक8_t value)
अणु
	काष्ठा nvअगर_object *device = &nouveau_drm(dev)->client.device.object;
	अगर (NVGetEnablePalette(dev, head))
		index &= ~0x20;
	अन्यथा
		index |= 0x20;

	nvअगर_rd08(device, NV_PRMCIO_INP0__COLOR + head * NV_PRMCIO_SIZE);
	nvअगर_wr08(device, NV_PRMCIO_ARX + head * NV_PRMCIO_SIZE, index);
	nvअगर_wr08(device, NV_PRMCIO_AR__WRITE + head * NV_PRMCIO_SIZE, value);
पूर्ण

अटल अंतरभूत uपूर्णांक8_t NVReadVgaAttr(काष्ठा drm_device *dev,
					पूर्णांक head, uपूर्णांक8_t index)
अणु
	काष्ठा nvअगर_object *device = &nouveau_drm(dev)->client.device.object;
	uपूर्णांक8_t val;
	अगर (NVGetEnablePalette(dev, head))
		index &= ~0x20;
	अन्यथा
		index |= 0x20;

	nvअगर_rd08(device, NV_PRMCIO_INP0__COLOR + head * NV_PRMCIO_SIZE);
	nvअगर_wr08(device, NV_PRMCIO_ARX + head * NV_PRMCIO_SIZE, index);
	val = nvअगर_rd08(device, NV_PRMCIO_AR__READ + head * NV_PRMCIO_SIZE);
	वापस val;
पूर्ण

अटल अंतरभूत व्योम NVVgaSeqReset(काष्ठा drm_device *dev, पूर्णांक head, bool start)
अणु
	NVWriteVgaSeq(dev, head, NV_VIO_SR_RESET_INDEX, start ? 0x1 : 0x3);
पूर्ण

अटल अंतरभूत व्योम NVVgaProtect(काष्ठा drm_device *dev, पूर्णांक head, bool protect)
अणु
	uपूर्णांक8_t seq1 = NVReadVgaSeq(dev, head, NV_VIO_SR_CLOCK_INDEX);

	अगर (protect) अणु
		NVVgaSeqReset(dev, head, true);
		NVWriteVgaSeq(dev, head, NV_VIO_SR_CLOCK_INDEX, seq1 | 0x20);
	पूर्ण अन्यथा अणु
		/* Reenable sequencer, then turn on screen */
		NVWriteVgaSeq(dev, head, NV_VIO_SR_CLOCK_INDEX, seq1 & ~0x20);   /* reenable display */
		NVVgaSeqReset(dev, head, false);
	पूर्ण
	NVSetEnablePalette(dev, head, protect);
पूर्ण

अटल अंतरभूत bool
nv_heads_tied(काष्ठा drm_device *dev)
अणु
	काष्ठा nvअगर_object *device = &nouveau_drm(dev)->client.device.object;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);

	अगर (drm->client.device.info.chipset == 0x11)
		वापस !!(nvअगर_rd32(device, NV_PBUS_DEBUG_1) & (1 << 28));

	वापस NVReadVgaCrtc(dev, 0, NV_CIO_CRE_44) & 0x4;
पूर्ण

/* makes cr0-7 on the specअगरied head पढ़ो-only */
अटल अंतरभूत bool
nv_lock_vga_crtc_base(काष्ठा drm_device *dev, पूर्णांक head, bool lock)
अणु
	uपूर्णांक8_t cr11 = NVReadVgaCrtc(dev, head, NV_CIO_CR_VRE_INDEX);
	bool waslocked = cr11 & 0x80;

	अगर (lock)
		cr11 |= 0x80;
	अन्यथा
		cr11 &= ~0x80;
	NVWriteVgaCrtc(dev, head, NV_CIO_CR_VRE_INDEX, cr11);

	वापस waslocked;
पूर्ण

अटल अंतरभूत व्योम
nv_lock_vga_crtc_shaकरोw(काष्ठा drm_device *dev, पूर्णांक head, पूर्णांक lock)
अणु
	/* shaकरोw lock: connects 0x60?3d? regs to "real" 0x3d? regs
	 * bit7: unlocks HDT, HBS, HBE, HRS, HRE, HEB
	 * bit6: seems to have some effect on CR09 (द्विगुन scan, VBS_9)
	 * bit5: unlocks HDE
	 * bit4: unlocks VDE
	 * bit3: unlocks VDT, OVL, VRS, ?VRE?, VBS, VBE, LSR, EBR
	 * bit2: same as bit 1 of 0x60?804
	 * bit0: same as bit 0 of 0x60?804
	 */

	uपूर्णांक8_t cr21 = lock;

	अगर (lock < 0)
		/* 0xfa is generic "unlock all" mask */
		cr21 = NVReadVgaCrtc(dev, head, NV_CIO_CRE_21) | 0xfa;

	NVWriteVgaCrtc(dev, head, NV_CIO_CRE_21, cr21);
पूर्ण

/* renders the extended crtc regs (cr19+) on all crtcs impervious:
 * immutable and unपढ़ोable
 */
अटल अंतरभूत bool
NVLockVgaCrtcs(काष्ठा drm_device *dev, bool lock)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	bool waslocked = !NVReadVgaCrtc(dev, 0, NV_CIO_SR_LOCK_INDEX);

	NVWriteVgaCrtc(dev, 0, NV_CIO_SR_LOCK_INDEX,
		       lock ? NV_CIO_SR_LOCK_VALUE : NV_CIO_SR_UNLOCK_RW_VALUE);
	/* NV11 has independently lockable extended crtcs, except when tied */
	अगर (drm->client.device.info.chipset == 0x11 && !nv_heads_tied(dev))
		NVWriteVgaCrtc(dev, 1, NV_CIO_SR_LOCK_INDEX,
			       lock ? NV_CIO_SR_LOCK_VALUE :
				      NV_CIO_SR_UNLOCK_RW_VALUE);

	वापस waslocked;
पूर्ण

/* nv04 cursor max dimensions of 32x32 (A1R5G5B5) */
#घोषणा NV04_CURSOR_SIZE 32
/* limit nv10 cursors to 64x64 (ARGB8) (we could go to 64x255) */
#घोषणा NV10_CURSOR_SIZE 64

अटल अंतरभूत पूर्णांक nv_cursor_width(काष्ठा drm_device *dev)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);

	वापस drm->client.device.info.family >= NV_DEVICE_INFO_V0_CELSIUS ? NV10_CURSOR_SIZE : NV04_CURSOR_SIZE;
पूर्ण

अटल अंतरभूत व्योम
nv_fix_nv40_hw_cursor(काष्ठा drm_device *dev, पूर्णांक head)
अणु
	/* on some nv40 (such as the "true" (in the NV_PFB_BOOT_0 sense) nv40,
	 * the gf6800gt) a hardware bug requires a ग_लिखो to PRAMDAC_CURSOR_POS
	 * क्रम changes to the CRTC CURCTL regs to take effect, whether changing
	 * the pixmap location, or just showing/hiding the cursor
	 */
	uपूर्णांक32_t curpos = NVReadRAMDAC(dev, head, NV_PRAMDAC_CU_START_POS);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_CU_START_POS, curpos);
पूर्ण

अटल अंतरभूत व्योम
nv_set_crtc_base(काष्ठा drm_device *dev, पूर्णांक head, uपूर्णांक32_t offset)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);

	NVWriteCRTC(dev, head, NV_PCRTC_START, offset);

	अगर (drm->client.device.info.family == NV_DEVICE_INFO_V0_TNT) अणु
		/*
		 * Hilarious, the 24th bit करोesn't want to stick to
		 * PCRTC_START...
		 */
		पूर्णांक cre_heb = NVReadVgaCrtc(dev, head, NV_CIO_CRE_HEB__INDEX);

		NVWriteVgaCrtc(dev, head, NV_CIO_CRE_HEB__INDEX,
			       (cre_heb & ~0x40) | ((offset >> 18) & 0x40));
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
nv_show_cursor(काष्ठा drm_device *dev, पूर्णांक head, bool show)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	uपूर्णांक8_t *curctl1 =
		&nv04_display(dev)->mode_reg.crtc_reg[head].CRTC[NV_CIO_CRE_HCUR_ADDR1_INDEX];

	अगर (show)
		*curctl1 |= MASK(NV_CIO_CRE_HCUR_ADDR1_ENABLE);
	अन्यथा
		*curctl1 &= ~MASK(NV_CIO_CRE_HCUR_ADDR1_ENABLE);
	NVWriteVgaCrtc(dev, head, NV_CIO_CRE_HCUR_ADDR1_INDEX, *curctl1);

	अगर (drm->client.device.info.family == NV_DEVICE_INFO_V0_CURIE)
		nv_fix_nv40_hw_cursor(dev, head);
पूर्ण

अटल अंतरभूत uपूर्णांक32_t
nv_pitch_align(काष्ठा drm_device *dev, uपूर्णांक32_t width, पूर्णांक bpp)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	पूर्णांक mask;

	अगर (bpp == 15)
		bpp = 16;
	अगर (bpp == 24)
		bpp = 8;

	/* Alignment requirements taken from the Haiku driver */
	अगर (drm->client.device.info.family == NV_DEVICE_INFO_V0_TNT)
		mask = 128 / bpp - 1;
	अन्यथा
		mask = 512 / bpp - 1;

	वापस (width + mask) & ~mask;
पूर्ण

#पूर्ण_अगर	/* __NOUVEAU_HW_H__ */
