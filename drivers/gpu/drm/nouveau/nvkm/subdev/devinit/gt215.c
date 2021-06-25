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
#समावेश "nv50.h"

#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/init.h>
#समावेश <subdev/bios/pll.h>
#समावेश <subdev/clk/pll.h>

पूर्णांक
gt215_devinit_pll_set(काष्ठा nvkm_devinit *init, u32 type, u32 freq)
अणु
	काष्ठा nvkm_subdev *subdev = &init->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvbios_pll info;
	पूर्णांक N, fN, M, P;
	पूर्णांक ret;

	ret = nvbios_pll_parse(device->bios, type, &info);
	अगर (ret)
		वापस ret;

	ret = gt215_pll_calc(subdev, &info, freq, &N, &fN, &M, &P);
	अगर (ret < 0)
		वापस ret;

	चयन (info.type) अणु
	हाल PLL_VPLL0:
	हाल PLL_VPLL1:
		nvkm_wr32(device, info.reg + 0, 0x50000610);
		nvkm_mask(device, info.reg + 4, 0x003fffff,
						(P << 16) | (M << 8) | N);
		nvkm_wr32(device, info.reg + 8, fN);
		अवरोध;
	शेष:
		nvkm_warn(subdev, "%08x/%dKhz unimplemented\n", type, freq);
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल u64
gt215_devinit_disable(काष्ठा nvkm_devinit *init)
अणु
	काष्ठा nvkm_device *device = init->subdev.device;
	u32 r001540 = nvkm_rd32(device, 0x001540);
	u32 r00154c = nvkm_rd32(device, 0x00154c);
	u64 disable = 0ULL;

	अगर (!(r001540 & 0x40000000)) अणु
		nvkm_subdev_disable(device, NVKM_ENGINE_MSPDEC, 0);
		nvkm_subdev_disable(device, NVKM_ENGINE_MSPPP, 0);
	पूर्ण

	अगर (!(r00154c & 0x00000004))
		nvkm_subdev_disable(device, NVKM_ENGINE_DISP, 0);
	अगर (!(r00154c & 0x00000020))
		nvkm_subdev_disable(device, NVKM_ENGINE_MSVLD, 0);
	अगर (!(r00154c & 0x00000200))
		nvkm_subdev_disable(device, NVKM_ENGINE_CE, 0);

	वापस disable;
पूर्ण

अटल u32
gt215_devinit_mmio_part[] = अणु
	0x100720, 0x1008bc, 4,
	0x100a20, 0x100adc, 4,
	0x100d80, 0x100ddc, 4,
	0x110000, 0x110f9c, 4,
	0x111000, 0x11103c, 8,
	0x111080, 0x1110fc, 4,
	0x111120, 0x1111fc, 4,
	0x111300, 0x1114bc, 4,
	0,
पूर्ण;

अटल u32
gt215_devinit_mmio(काष्ठा nvkm_devinit *base, u32 addr)
अणु
	काष्ठा nv50_devinit *init = nv50_devinit(base);
	काष्ठा nvkm_device *device = init->base.subdev.device;
	u32 *mmio = gt215_devinit_mmio_part;

	/* the init tables on some boards have INIT_RAM_RESTRICT_ZM_REG_GROUP
	 * inकाष्ठाions which touch रेजिस्टरs that may not even exist on
	 * some configurations (Quadro 400), which causes the रेजिस्टर
	 * पूर्णांकerface to screw up क्रम some amount of समय after attempting to
	 * ग_लिखो to one of these, and results in all sorts of things going
	 * horribly wrong.
	 *
	 * the binary driver aव्योमs touching these रेजिस्टरs at all, however,
	 * the video bios करोesn't care and does what the scripts say.  it's
	 * presumed that the io-port access to init रेजिस्टरs isn't effected
	 * by the screw-up bug mentioned above.
	 *
	 * really, a new opcode should've been invented to handle these
	 * requirements, but whatever, it's too late क्रम that now.
	 */
	जबतक (mmio[0]) अणु
		अगर (addr >= mmio[0] && addr <= mmio[1]) अणु
			u32 part = (addr / mmio[2]) & 7;
			अगर (!init->r001540)
				init->r001540 = nvkm_rd32(device, 0x001540);
			अगर (part >= hweight8((init->r001540 >> 16) & 0xff))
				वापस ~0;
			वापस addr;
		पूर्ण
		mmio += 3;
	पूर्ण

	वापस addr;
पूर्ण

अटल स्थिर काष्ठा nvkm_devinit_func
gt215_devinit = अणु
	.preinit = nv50_devinit_preinit,
	.init = nv50_devinit_init,
	.post = nv04_devinit_post,
	.mmio = gt215_devinit_mmio,
	.pll_set = gt215_devinit_pll_set,
	.disable = gt215_devinit_disable,
पूर्ण;

पूर्णांक
gt215_devinit_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
		  काष्ठा nvkm_devinit **pinit)
अणु
	वापस nv50_devinit_new_(&gt215_devinit, device, type, inst, pinit);
पूर्ण
