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
#समावेश <subdev/bios/dcb.h>
#समावेश <subdev/bios/disp.h>
#समावेश <subdev/bios/init.h>
#समावेश <subdev/bios/pll.h>
#समावेश <subdev/clk/pll.h>
#समावेश <subdev/vga.h>

पूर्णांक
nv50_devinit_pll_set(काष्ठा nvkm_devinit *init, u32 type, u32 freq)
अणु
	काष्ठा nvkm_subdev *subdev = &init->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_bios *bios = device->bios;
	काष्ठा nvbios_pll info;
	पूर्णांक N1, M1, N2, M2, P;
	पूर्णांक ret;

	ret = nvbios_pll_parse(bios, type, &info);
	अगर (ret) अणु
		nvkm_error(subdev, "failed to retrieve pll data, %d\n", ret);
		वापस ret;
	पूर्ण

	ret = nv04_pll_calc(subdev, &info, freq, &N1, &M1, &N2, &M2, &P);
	अगर (!ret) अणु
		nvkm_error(subdev, "failed pll calculation\n");
		वापस -EINVAL;
	पूर्ण

	चयन (info.type) अणु
	हाल PLL_VPLL0:
	हाल PLL_VPLL1:
		nvkm_wr32(device, info.reg + 0, 0x10000611);
		nvkm_mask(device, info.reg + 4, 0x00ff00ff, (M1 << 16) | N1);
		nvkm_mask(device, info.reg + 8, 0x7fff00ff, (P  << 28) |
							    (M2 << 16) | N2);
		अवरोध;
	हाल PLL_MEMORY:
		nvkm_mask(device, info.reg + 0, 0x01ff0000,
					        (P << 22) |
						(info.bias_p << 19) |
						(P << 16));
		nvkm_wr32(device, info.reg + 4, (N1 << 8) | M1);
		अवरोध;
	शेष:
		nvkm_mask(device, info.reg + 0, 0x00070000, (P << 16));
		nvkm_wr32(device, info.reg + 4, (N1 << 8) | M1);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल u64
nv50_devinit_disable(काष्ठा nvkm_devinit *init)
अणु
	काष्ठा nvkm_device *device = init->subdev.device;
	u32 r001540 = nvkm_rd32(device, 0x001540);
	u64 disable = 0ULL;

	अगर (!(r001540 & 0x40000000))
		nvkm_subdev_disable(device, NVKM_ENGINE_MPEG, 0);

	वापस disable;
पूर्ण

व्योम
nv50_devinit_preinit(काष्ठा nvkm_devinit *base)
अणु
	काष्ठा nvkm_subdev *subdev = &base->subdev;
	काष्ठा nvkm_device *device = subdev->device;

	/* our heuristics can't detect whether the board has had its
	 * devinit scripts executed or not अगर the display engine is
	 * missing, assume it's a secondary gpu which requires post
	 */
	अगर (!base->post) अणु
		nvkm_devinit_disable(base);
		अगर (!device->disp)
			base->post = true;
	पूर्ण

	/* magic to detect whether or not x86 vbios code has executed
	 * the devinit scripts to initialise the board
	 */
	अगर (!base->post) अणु
		अगर (!nvkm_rdvgac(device, 0, 0x00) &&
		    !nvkm_rdvgac(device, 0, 0x1a)) अणु
			nvkm_debug(subdev, "adaptor not initialised\n");
			base->post = true;
		पूर्ण
	पूर्ण
पूर्ण

व्योम
nv50_devinit_init(काष्ठा nvkm_devinit *base)
अणु
	काष्ठा nv50_devinit *init = nv50_devinit(base);
	काष्ठा nvkm_subdev *subdev = &init->base.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_bios *bios = device->bios;
	काष्ठा nvbios_outp info;
	काष्ठा dcb_output outp;
	u8  ver = 0xff, hdr, cnt, len;
	पूर्णांक i = 0;

	/* अगर we ran the init tables, we have to execute the first script
	 * poपूर्णांकer of each dcb entry's display encoder table in order
	 * to properly initialise each encoder.
	 */
	जबतक (init->base.post && dcb_outp_parse(bios, i, &ver, &hdr, &outp)) अणु
		अगर (nvbios_outp_match(bios, outp.hasht, outp.hashm,
				      &ver, &hdr, &cnt, &len, &info)) अणु
			nvbios_init(subdev, info.script[0],
				init.outp = &outp;
				init.or   = ffs(outp.or) - 1;
				init.link = outp.sorconf.link == 2;
			);
		पूर्ण
		i++;
	पूर्ण
पूर्ण

पूर्णांक
nv50_devinit_new_(स्थिर काष्ठा nvkm_devinit_func *func, काष्ठा nvkm_device *device,
		  क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_devinit **pinit)
अणु
	काष्ठा nv50_devinit *init;

	अगर (!(init = kzalloc(माप(*init), GFP_KERNEL)))
		वापस -ENOMEM;
	*pinit = &init->base;

	nvkm_devinit_ctor(func, device, type, inst, &init->base);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_devinit_func
nv50_devinit = अणु
	.preinit = nv50_devinit_preinit,
	.init = nv50_devinit_init,
	.post = nv04_devinit_post,
	.pll_set = nv50_devinit_pll_set,
	.disable = nv50_devinit_disable,
पूर्ण;

पूर्णांक
nv50_devinit_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
		 काष्ठा nvkm_devinit **pinit)
अणु
	वापस nv50_devinit_new_(&nv50_devinit, device, type, inst, pinit);
पूर्ण
