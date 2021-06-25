<शैली गुरु>
/*
 * Copyright (C) 2010 Francisco Jerez.
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
#समावेश "nv04.h"
#समावेश "fbmem.h"

#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/init.h>
#समावेश <subdev/bios/pll.h>
#समावेश <subdev/clk/pll.h>
#समावेश <subdev/vga.h>

अटल व्योम
nv04_devinit_meminit(काष्ठा nvkm_devinit *init)
अणु
	काष्ठा nvkm_subdev *subdev = &init->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 patt = 0xdeadbeef;
	काष्ठा io_mapping *fb;
	पूर्णांक i;

	/* Map the framebuffer aperture */
	fb = fbmem_init(device);
	अगर (!fb) अणु
		nvkm_error(subdev, "failed to map fb\n");
		वापस;
	पूर्ण

	/* Sequencer and refresh off */
	nvkm_wrvgas(device, 0, 1, nvkm_rdvgas(device, 0, 1) | 0x20);
	nvkm_mask(device, NV04_PFB_DEBUG_0, 0, NV04_PFB_DEBUG_0_REFRESH_OFF);

	nvkm_mask(device, NV04_PFB_BOOT_0, ~0,
		      NV04_PFB_BOOT_0_RAM_AMOUNT_16MB |
		      NV04_PFB_BOOT_0_RAM_WIDTH_128 |
		      NV04_PFB_BOOT_0_RAM_TYPE_SGRAM_16MBIT);

	क्रम (i = 0; i < 4; i++)
		fbmem_poke(fb, 4 * i, patt);

	fbmem_poke(fb, 0x400000, patt + 1);

	अगर (fbmem_peek(fb, 0) == patt + 1) अणु
		nvkm_mask(device, NV04_PFB_BOOT_0,
			      NV04_PFB_BOOT_0_RAM_TYPE,
			      NV04_PFB_BOOT_0_RAM_TYPE_SDRAM_16MBIT);
		nvkm_mask(device, NV04_PFB_DEBUG_0,
			      NV04_PFB_DEBUG_0_REFRESH_OFF, 0);

		क्रम (i = 0; i < 4; i++)
			fbmem_poke(fb, 4 * i, patt);

		अगर ((fbmem_peek(fb, 0xc) & 0xffff) != (patt & 0xffff))
			nvkm_mask(device, NV04_PFB_BOOT_0,
				      NV04_PFB_BOOT_0_RAM_WIDTH_128 |
				      NV04_PFB_BOOT_0_RAM_AMOUNT,
				      NV04_PFB_BOOT_0_RAM_AMOUNT_8MB);
	पूर्ण अन्यथा
	अगर ((fbmem_peek(fb, 0xc) & 0xffff0000) != (patt & 0xffff0000)) अणु
		nvkm_mask(device, NV04_PFB_BOOT_0,
			      NV04_PFB_BOOT_0_RAM_WIDTH_128 |
			      NV04_PFB_BOOT_0_RAM_AMOUNT,
			      NV04_PFB_BOOT_0_RAM_AMOUNT_4MB);
	पूर्ण अन्यथा
	अगर (fbmem_peek(fb, 0) != patt) अणु
		अगर (fbmem_पढ़ोback(fb, 0x800000, patt))
			nvkm_mask(device, NV04_PFB_BOOT_0,
				      NV04_PFB_BOOT_0_RAM_AMOUNT,
				      NV04_PFB_BOOT_0_RAM_AMOUNT_8MB);
		अन्यथा
			nvkm_mask(device, NV04_PFB_BOOT_0,
				      NV04_PFB_BOOT_0_RAM_AMOUNT,
				      NV04_PFB_BOOT_0_RAM_AMOUNT_4MB);

		nvkm_mask(device, NV04_PFB_BOOT_0, NV04_PFB_BOOT_0_RAM_TYPE,
			      NV04_PFB_BOOT_0_RAM_TYPE_SGRAM_8MBIT);
	पूर्ण अन्यथा
	अगर (!fbmem_पढ़ोback(fb, 0x800000, patt)) अणु
		nvkm_mask(device, NV04_PFB_BOOT_0, NV04_PFB_BOOT_0_RAM_AMOUNT,
			      NV04_PFB_BOOT_0_RAM_AMOUNT_8MB);

	पूर्ण

	/* Refresh on, sequencer on */
	nvkm_mask(device, NV04_PFB_DEBUG_0, NV04_PFB_DEBUG_0_REFRESH_OFF, 0);
	nvkm_wrvgas(device, 0, 1, nvkm_rdvgas(device, 0, 1) & ~0x20);
	fbmem_fini(fb);
पूर्ण

अटल पूर्णांक
घातerctrl_1_shअगरt(पूर्णांक chip_version, पूर्णांक reg)
अणु
	पूर्णांक shअगरt = -4;

	अगर (chip_version < 0x17 || chip_version == 0x1a || chip_version == 0x20)
		वापस shअगरt;

	चयन (reg) अणु
	हाल 0x680520:
		shअगरt += 4; fallthrough;
	हाल 0x680508:
		shअगरt += 4; fallthrough;
	हाल 0x680504:
		shअगरt += 4; fallthrough;
	हाल 0x680500:
		shअगरt += 4;
	पूर्ण

	/*
	 * the shअगरt क्रम vpll regs is only used क्रम nv3x chips with a single
	 * stage pll
	 */
	अगर (shअगरt > 4 && (chip_version < 0x32 || chip_version == 0x35 ||
			  chip_version == 0x36 || chip_version >= 0x40))
		shअगरt = -4;

	वापस shअगरt;
पूर्ण

व्योम
setPLL_single(काष्ठा nvkm_devinit *init, u32 reg,
	      काष्ठा nvkm_pll_vals *pv)
अणु
	काष्ठा nvkm_device *device = init->subdev.device;
	पूर्णांक chip_version = device->bios->version.chip;
	uपूर्णांक32_t oldpll = nvkm_rd32(device, reg);
	पूर्णांक oldN = (oldpll >> 8) & 0xff, oldM = oldpll & 0xff;
	uपूर्णांक32_t pll = (oldpll & 0xfff80000) | pv->log2P << 16 | pv->NM1;
	uपूर्णांक32_t saved_घातerctrl_1 = 0;
	पूर्णांक shअगरt_घातerctrl_1 = घातerctrl_1_shअगरt(chip_version, reg);

	अगर (oldpll == pll)
		वापस;	/* alपढ़ोy set */

	अगर (shअगरt_घातerctrl_1 >= 0) अणु
		saved_घातerctrl_1 = nvkm_rd32(device, 0x001584);
		nvkm_wr32(device, 0x001584,
			(saved_घातerctrl_1 & ~(0xf << shअगरt_घातerctrl_1)) |
			1 << shअगरt_घातerctrl_1);
	पूर्ण

	अगर (oldM && pv->M1 && (oldN / oldM < pv->N1 / pv->M1))
		/* upघड़ी -- ग_लिखो new post भागider first */
		nvkm_wr32(device, reg, pv->log2P << 16 | (oldpll & 0xffff));
	अन्यथा
		/* करोwnघड़ी -- ग_लिखो new NM first */
		nvkm_wr32(device, reg, (oldpll & 0xffff0000) | pv->NM1);

	अगर ((chip_version < 0x17 || chip_version == 0x1a) &&
	    chip_version != 0x11)
		/* रुको a bit on older chips */
		msleep(64);
	nvkm_rd32(device, reg);

	/* then ग_लिखो the other half as well */
	nvkm_wr32(device, reg, pll);

	अगर (shअगरt_घातerctrl_1 >= 0)
		nvkm_wr32(device, 0x001584, saved_घातerctrl_1);
पूर्ण

अटल uपूर्णांक32_t
new_ramdac580(uपूर्णांक32_t reg1, bool ss, uपूर्णांक32_t ramdac580)
अणु
	bool head_a = (reg1 == 0x680508);

	अगर (ss)	/* single stage pll mode */
		ramdac580 |= head_a ? 0x00000100 : 0x10000000;
	अन्यथा
		ramdac580 &= head_a ? 0xfffffeff : 0xefffffff;

	वापस ramdac580;
पूर्ण

व्योम
setPLL_द्विगुन_highregs(काष्ठा nvkm_devinit *init, u32 reg1,
		       काष्ठा nvkm_pll_vals *pv)
अणु
	काष्ठा nvkm_device *device = init->subdev.device;
	पूर्णांक chip_version = device->bios->version.chip;
	bool nv3035 = chip_version == 0x30 || chip_version == 0x35;
	uपूर्णांक32_t reg2 = reg1 + ((reg1 == 0x680520) ? 0x5c : 0x70);
	uपूर्णांक32_t oldpll1 = nvkm_rd32(device, reg1);
	uपूर्णांक32_t oldpll2 = !nv3035 ? nvkm_rd32(device, reg2) : 0;
	uपूर्णांक32_t pll1 = (oldpll1 & 0xfff80000) | pv->log2P << 16 | pv->NM1;
	uपूर्णांक32_t pll2 = (oldpll2 & 0x7fff0000) | 1 << 31 | pv->NM2;
	uपूर्णांक32_t oldramdac580 = 0, ramdac580 = 0;
	bool single_stage = !pv->NM2 || pv->N2 == pv->M2;	/* nv41+ only */
	uपूर्णांक32_t saved_घातerctrl_1 = 0, savedc040 = 0;
	पूर्णांक shअगरt_घातerctrl_1 = घातerctrl_1_shअगरt(chip_version, reg1);

	/* model specअगरic additions to generic pll1 and pll2 set up above */
	अगर (nv3035) अणु
		pll1 = (pll1 & 0xfcc7ffff) | (pv->N2 & 0x18) << 21 |
		       (pv->N2 & 0x7) << 19 | 8 << 4 | (pv->M2 & 7) << 4;
		pll2 = 0;
	पूर्ण
	अगर (chip_version > 0x40 && reg1 >= 0x680508) अणु /* !nv40 */
		oldramdac580 = nvkm_rd32(device, 0x680580);
		ramdac580 = new_ramdac580(reg1, single_stage, oldramdac580);
		अगर (oldramdac580 != ramdac580)
			oldpll1 = ~0;	/* क्रमce mismatch */
		अगर (single_stage)
			/* magic value used by nvidia in single stage mode */
			pll2 |= 0x011f;
	पूर्ण
	अगर (chip_version > 0x70)
		/* magic bits set by the blob (but not the bios) on g71-73 */
		pll1 = (pll1 & 0x7fffffff) | (single_stage ? 0x4 : 0xc) << 28;

	अगर (oldpll1 == pll1 && oldpll2 == pll2)
		वापस;	/* alपढ़ोy set */

	अगर (shअगरt_घातerctrl_1 >= 0) अणु
		saved_घातerctrl_1 = nvkm_rd32(device, 0x001584);
		nvkm_wr32(device, 0x001584,
			(saved_घातerctrl_1 & ~(0xf << shअगरt_घातerctrl_1)) |
			1 << shअगरt_घातerctrl_1);
	पूर्ण

	अगर (chip_version >= 0x40) अणु
		पूर्णांक shअगरt_c040 = 14;

		चयन (reg1) अणु
		हाल 0x680504:
			shअगरt_c040 += 2; fallthrough;
		हाल 0x680500:
			shअगरt_c040 += 2; fallthrough;
		हाल 0x680520:
			shअगरt_c040 += 2; fallthrough;
		हाल 0x680508:
			shअगरt_c040 += 2;
		पूर्ण

		savedc040 = nvkm_rd32(device, 0xc040);
		अगर (shअगरt_c040 != 14)
			nvkm_wr32(device, 0xc040, savedc040 & ~(3 << shअगरt_c040));
	पूर्ण

	अगर (oldramdac580 != ramdac580)
		nvkm_wr32(device, 0x680580, ramdac580);

	अगर (!nv3035)
		nvkm_wr32(device, reg2, pll2);
	nvkm_wr32(device, reg1, pll1);

	अगर (shअगरt_घातerctrl_1 >= 0)
		nvkm_wr32(device, 0x001584, saved_घातerctrl_1);
	अगर (chip_version >= 0x40)
		nvkm_wr32(device, 0xc040, savedc040);
पूर्ण

व्योम
setPLL_द्विगुन_lowregs(काष्ठा nvkm_devinit *init, u32 NMNMreg,
		      काष्ठा nvkm_pll_vals *pv)
अणु
	/* When setting PLLs, there is a merry game of disabling and enabling
	 * various bits of hardware during the process. This function is a
	 * synthesis of six nv4x traces, nearly each card करोing a subtly
	 * dअगरferent thing. With luck all the necessary bits क्रम each card are
	 * combined herein. Without luck it deviates from each card's क्रमmula
	 * so as to not work on any :)
	 */
	काष्ठा nvkm_device *device = init->subdev.device;
	uपूर्णांक32_t Preg = NMNMreg - 4;
	bool mpll = Preg == 0x4020;
	uपूर्णांक32_t oldPval = nvkm_rd32(device, Preg);
	uपूर्णांक32_t NMNM = pv->NM2 << 16 | pv->NM1;
	uपूर्णांक32_t Pval = (oldPval & (mpll ? ~(0x77 << 16) : ~(7 << 16))) |
			0xc << 28 | pv->log2P << 16;
	uपूर्णांक32_t saved4600 = 0;
	/* some cards have dअगरferent maskc040s */
	uपूर्णांक32_t maskc040 = ~(3 << 14), savedc040;
	bool single_stage = !pv->NM2 || pv->N2 == pv->M2;

	अगर (nvkm_rd32(device, NMNMreg) == NMNM && (oldPval & 0xc0070000) == Pval)
		वापस;

	अगर (Preg == 0x4000)
		maskc040 = ~0x333;
	अगर (Preg == 0x4058)
		maskc040 = ~(0xc << 24);

	अगर (mpll) अणु
		काष्ठा nvbios_pll info;
		uपूर्णांक8_t Pval2;

		अगर (nvbios_pll_parse(device->bios, Preg, &info))
			वापस;

		Pval2 = pv->log2P + info.bias_p;
		अगर (Pval2 > info.max_p)
			Pval2 = info.max_p;
		Pval |= 1 << 28 | Pval2 << 20;

		saved4600 = nvkm_rd32(device, 0x4600);
		nvkm_wr32(device, 0x4600, saved4600 | 8 << 28);
	पूर्ण
	अगर (single_stage)
		Pval |= mpll ? 1 << 12 : 1 << 8;

	nvkm_wr32(device, Preg, oldPval | 1 << 28);
	nvkm_wr32(device, Preg, Pval & ~(4 << 28));
	अगर (mpll) अणु
		Pval |= 8 << 20;
		nvkm_wr32(device, 0x4020, Pval & ~(0xc << 28));
		nvkm_wr32(device, 0x4038, Pval & ~(0xc << 28));
	पूर्ण

	savedc040 = nvkm_rd32(device, 0xc040);
	nvkm_wr32(device, 0xc040, savedc040 & maskc040);

	nvkm_wr32(device, NMNMreg, NMNM);
	अगर (NMNMreg == 0x4024)
		nvkm_wr32(device, 0x403c, NMNM);

	nvkm_wr32(device, Preg, Pval);
	अगर (mpll) अणु
		Pval &= ~(8 << 20);
		nvkm_wr32(device, 0x4020, Pval);
		nvkm_wr32(device, 0x4038, Pval);
		nvkm_wr32(device, 0x4600, saved4600);
	पूर्ण

	nvkm_wr32(device, 0xc040, savedc040);

	अगर (mpll) अणु
		nvkm_wr32(device, 0x4020, Pval & ~(1 << 28));
		nvkm_wr32(device, 0x4038, Pval & ~(1 << 28));
	पूर्ण
पूर्ण

पूर्णांक
nv04_devinit_pll_set(काष्ठा nvkm_devinit *devinit, u32 type, u32 freq)
अणु
	काष्ठा nvkm_subdev *subdev = &devinit->subdev;
	काष्ठा nvkm_bios *bios = subdev->device->bios;
	काष्ठा nvkm_pll_vals pv;
	काष्ठा nvbios_pll info;
	पूर्णांक cv = bios->version.chip;
	पूर्णांक N1, M1, N2, M2, P;
	पूर्णांक ret;

	ret = nvbios_pll_parse(bios, type > 0x405c ? type : type - 4, &info);
	अगर (ret)
		वापस ret;

	ret = nv04_pll_calc(subdev, &info, freq, &N1, &M1, &N2, &M2, &P);
	अगर (!ret)
		वापस -EINVAL;

	pv.refclk = info.refclk;
	pv.N1 = N1;
	pv.M1 = M1;
	pv.N2 = N2;
	pv.M2 = M2;
	pv.log2P = P;

	अगर (cv == 0x30 || cv == 0x31 || cv == 0x35 || cv == 0x36 ||
	    cv >= 0x40) अणु
		अगर (type > 0x405c)
			setPLL_द्विगुन_highregs(devinit, type, &pv);
		अन्यथा
			setPLL_द्विगुन_lowregs(devinit, type, &pv);
	पूर्ण अन्यथा
		setPLL_single(devinit, type, &pv);

	वापस 0;
पूर्ण

पूर्णांक
nv04_devinit_post(काष्ठा nvkm_devinit *init, bool execute)
अणु
	वापस nvbios_post(&init->subdev, execute);
पूर्ण

व्योम
nv04_devinit_preinit(काष्ठा nvkm_devinit *base)
अणु
	काष्ठा nv04_devinit *init = nv04_devinit(base);
	काष्ठा nvkm_subdev *subdev = &init->base.subdev;
	काष्ठा nvkm_device *device = subdev->device;

	/* make i2c busses accessible */
	nvkm_mask(device, 0x000200, 0x00000001, 0x00000001);

	/* unslave crtcs */
	अगर (init->owner < 0)
		init->owner = nvkm_rdvgaowner(device);
	nvkm_wrvgaowner(device, 0);

	अगर (!init->base.post) अणु
		u32 htotal = nvkm_rdvgac(device, 0, 0x06);
		htotal |= (nvkm_rdvgac(device, 0, 0x07) & 0x01) << 8;
		htotal |= (nvkm_rdvgac(device, 0, 0x07) & 0x20) << 4;
		htotal |= (nvkm_rdvgac(device, 0, 0x25) & 0x01) << 10;
		htotal |= (nvkm_rdvgac(device, 0, 0x41) & 0x01) << 11;
		अगर (!htotal) अणु
			nvkm_debug(subdev, "adaptor not initialised\n");
			init->base.post = true;
		पूर्ण
	पूर्ण
पूर्ण

व्योम *
nv04_devinit_dtor(काष्ठा nvkm_devinit *base)
अणु
	काष्ठा nv04_devinit *init = nv04_devinit(base);
	/* restore vga owner saved at first init */
	nvkm_wrvgaowner(init->base.subdev.device, init->owner);
	वापस init;
पूर्ण

पूर्णांक
nv04_devinit_new_(स्थिर काष्ठा nvkm_devinit_func *func, काष्ठा nvkm_device *device,
		  क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_devinit **pinit)
अणु
	काष्ठा nv04_devinit *init;

	अगर (!(init = kzalloc(माप(*init), GFP_KERNEL)))
		वापस -ENOMEM;
	*pinit = &init->base;

	nvkm_devinit_ctor(func, device, type, inst, &init->base);
	init->owner = -1;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_devinit_func
nv04_devinit = अणु
	.dtor = nv04_devinit_dtor,
	.preinit = nv04_devinit_preinit,
	.post = nv04_devinit_post,
	.meminit = nv04_devinit_meminit,
	.pll_set = nv04_devinit_pll_set,
पूर्ण;

पूर्णांक
nv04_devinit_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
		 काष्ठा nvkm_devinit **pinit)
अणु
	वापस nv04_devinit_new_(&nv04_devinit, device, type, inst, pinit);
पूर्ण
