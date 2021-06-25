<शैली गुरु>
/*
 * Copyright 2013 Red Hat Inc.
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
 * Authors: Ben Skeggs
 */
#समावेश "ramnv40.h"

#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/bit.h>
#समावेश <subdev/bios/init.h>
#समावेश <subdev/bios/pll.h>
#समावेश <subdev/clk/pll.h>
#समावेश <subdev/समयr.h>

अटल पूर्णांक
nv40_ram_calc(काष्ठा nvkm_ram *base, u32 freq)
अणु
	काष्ठा nv40_ram *ram = nv40_ram(base);
	काष्ठा nvkm_subdev *subdev = &ram->base.fb->subdev;
	काष्ठा nvkm_bios *bios = subdev->device->bios;
	काष्ठा nvbios_pll pll;
	पूर्णांक N1, M1, N2, M2;
	पूर्णांक log2P, ret;

	ret = nvbios_pll_parse(bios, 0x04, &pll);
	अगर (ret) अणु
		nvkm_error(subdev, "mclk pll data not found\n");
		वापस ret;
	पूर्ण

	ret = nv04_pll_calc(subdev, &pll, freq, &N1, &M1, &N2, &M2, &log2P);
	अगर (ret < 0)
		वापस ret;

	ram->ctrl  = 0x80000000 | (log2P << 16);
	ram->ctrl |= min(pll.bias_p + log2P, (पूर्णांक)pll.max_p) << 20;
	अगर (N2 == M2) अणु
		ram->ctrl |= 0x00000100;
		ram->coef  = (N1 << 8) | M1;
	पूर्ण अन्यथा अणु
		ram->ctrl |= 0x40000000;
		ram->coef  = (N2 << 24) | (M2 << 16) | (N1 << 8) | M1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nv40_ram_prog(काष्ठा nvkm_ram *base)
अणु
	काष्ठा nv40_ram *ram = nv40_ram(base);
	काष्ठा nvkm_subdev *subdev = &ram->base.fb->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_bios *bios = device->bios;
	काष्ठा bit_entry M;
	u32 crtc_mask = 0;
	u8  sr1[2];
	पूर्णांक i;

	/* determine which CRTCs are active, fetch VGA_SR1 क्रम each */
	क्रम (i = 0; i < 2; i++) अणु
		u32 vbl = nvkm_rd32(device, 0x600808 + (i * 0x2000));
		u32 cnt = 0;
		करो अणु
			अगर (vbl != nvkm_rd32(device, 0x600808 + (i * 0x2000))) अणु
				nvkm_wr08(device, 0x0c03c4 + (i * 0x2000), 0x01);
				sr1[i] = nvkm_rd08(device, 0x0c03c5 + (i * 0x2000));
				अगर (!(sr1[i] & 0x20))
					crtc_mask |= (1 << i);
				अवरोध;
			पूर्ण
			udelay(1);
		पूर्ण जबतक (cnt++ < 32);
	पूर्ण

	/* रुको क्रम vblank start on active crtcs, disable memory access */
	क्रम (i = 0; i < 2; i++) अणु
		अगर (!(crtc_mask & (1 << i)))
			जारी;

		nvkm_msec(device, 2000,
			u32 पंचांगp = nvkm_rd32(device, 0x600808 + (i * 0x2000));
			अगर (!(पंचांगp & 0x00010000))
				अवरोध;
		);

		nvkm_msec(device, 2000,
			u32 पंचांगp = nvkm_rd32(device, 0x600808 + (i * 0x2000));
			अगर ( (पंचांगp & 0x00010000))
				अवरोध;
		);

		nvkm_wr08(device, 0x0c03c4 + (i * 0x2000), 0x01);
		nvkm_wr08(device, 0x0c03c5 + (i * 0x2000), sr1[i] | 0x20);
	पूर्ण

	/* prepare ram क्रम reघड़ीing */
	nvkm_wr32(device, 0x1002d4, 0x00000001); /* preअक्षरge */
	nvkm_wr32(device, 0x1002d0, 0x00000001); /* refresh */
	nvkm_wr32(device, 0x1002d0, 0x00000001); /* refresh */
	nvkm_mask(device, 0x100210, 0x80000000, 0x00000000); /* no स्वतः refresh */
	nvkm_wr32(device, 0x1002dc, 0x00000001); /* enable self-refresh */

	/* change the PLL of each memory partition */
	nvkm_mask(device, 0x00c040, 0x0000c000, 0x00000000);
	चयन (device->chipset) अणु
	हाल 0x40:
	हाल 0x45:
	हाल 0x41:
	हाल 0x42:
	हाल 0x47:
		nvkm_mask(device, 0x004044, 0xc0771100, ram->ctrl);
		nvkm_mask(device, 0x00402c, 0xc0771100, ram->ctrl);
		nvkm_wr32(device, 0x004048, ram->coef);
		nvkm_wr32(device, 0x004030, ram->coef);
		fallthrough;
	हाल 0x43:
	हाल 0x49:
	हाल 0x4b:
		nvkm_mask(device, 0x004038, 0xc0771100, ram->ctrl);
		nvkm_wr32(device, 0x00403c, ram->coef);
		fallthrough;
	शेष:
		nvkm_mask(device, 0x004020, 0xc0771100, ram->ctrl);
		nvkm_wr32(device, 0x004024, ram->coef);
		अवरोध;
	पूर्ण
	udelay(100);
	nvkm_mask(device, 0x00c040, 0x0000c000, 0x0000c000);

	/* re-enable normal operation of memory controller */
	nvkm_wr32(device, 0x1002dc, 0x00000000);
	nvkm_mask(device, 0x100210, 0x80000000, 0x80000000);
	udelay(100);

	/* execute memory reset script from vbios */
	अगर (!bit_entry(bios, 'M', &M))
		nvbios_init(subdev, nvbios_rd16(bios, M.offset + 0x00));

	/* make sure we're in vblank (hopefully the same one as beक्रमe), and
	 * then re-enable crtc memory access
	 */
	क्रम (i = 0; i < 2; i++) अणु
		अगर (!(crtc_mask & (1 << i)))
			जारी;

		nvkm_msec(device, 2000,
			u32 पंचांगp = nvkm_rd32(device, 0x600808 + (i * 0x2000));
			अगर ( (पंचांगp & 0x00010000))
				अवरोध;
		);

		nvkm_wr08(device, 0x0c03c4 + (i * 0x2000), 0x01);
		nvkm_wr08(device, 0x0c03c5 + (i * 0x2000), sr1[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
nv40_ram_tidy(काष्ठा nvkm_ram *base)
अणु
पूर्ण

अटल स्थिर काष्ठा nvkm_ram_func
nv40_ram_func = अणु
	.calc = nv40_ram_calc,
	.prog = nv40_ram_prog,
	.tidy = nv40_ram_tidy,
पूर्ण;

पूर्णांक
nv40_ram_new_(काष्ठा nvkm_fb *fb, क्रमागत nvkm_ram_type type, u64 size,
	      काष्ठा nvkm_ram **pram)
अणु
	काष्ठा nv40_ram *ram;
	अगर (!(ram = kzalloc(माप(*ram), GFP_KERNEL)))
		वापस -ENOMEM;
	*pram = &ram->base;
	वापस nvkm_ram_ctor(&nv40_ram_func, fb, type, size, &ram->base);
पूर्ण

पूर्णांक
nv40_ram_new(काष्ठा nvkm_fb *fb, काष्ठा nvkm_ram **pram)
अणु
	काष्ठा nvkm_device *device = fb->subdev.device;
	u32 pbus1218 = nvkm_rd32(device, 0x001218);
	u32     size = nvkm_rd32(device, 0x10020c) & 0xff000000;
	क्रमागत nvkm_ram_type type = NVKM_RAM_TYPE_UNKNOWN;
	पूर्णांक ret;

	चयन (pbus1218 & 0x00000300) अणु
	हाल 0x00000000: type = NVKM_RAM_TYPE_SDRAM; अवरोध;
	हाल 0x00000100: type = NVKM_RAM_TYPE_DDR1 ; अवरोध;
	हाल 0x00000200: type = NVKM_RAM_TYPE_GDDR3; अवरोध;
	हाल 0x00000300: type = NVKM_RAM_TYPE_DDR2 ; अवरोध;
	पूर्ण

	ret = nv40_ram_new_(fb, type, size, pram);
	अगर (ret)
		वापस ret;

	(*pram)->parts = (nvkm_rd32(device, 0x100200) & 0x00000003) + 1;
	वापस 0;
पूर्ण
