<शैली गुरु>
/*
 * Copyright 2017 Red Hat Inc.
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
 * Authors: Ben Skeggs <bskeggs@redhat.com>
 */
#समावेश "ram.h"

u32
gm200_ram_probe_fbp_amount(स्थिर काष्ठा nvkm_ram_func *func, u32 fbpao,
			   काष्ठा nvkm_device *device, पूर्णांक fbp, पूर्णांक *pltcs)
अणु
	u32 ltcs  = nvkm_rd32(device, 0x022450);
	u32 fbpas = nvkm_rd32(device, 0x022458);
	u32 fbpa  = fbp * fbpas;
	u32 size  = 0;
	अगर (!(nvkm_rd32(device, 0x021d38) & BIT(fbp))) अणु
		u32 ltco = nvkm_rd32(device, 0x021d70 + (fbp * 4));
		u32 ltcm = ~ltco & ((1 << ltcs) - 1);

		जबतक (fbpas--) अणु
			अगर (!(fbpao & (1 << fbpa)))
				size += func->probe_fbpa_amount(device, fbpa);
			fbpa++;
		पूर्ण

		*pltcs = hweight32(ltcm);
	पूर्ण
	वापस size;
पूर्ण

अटल स्थिर काष्ठा nvkm_ram_func
gm200_ram = अणु
	.upper = 0x1000000000ULL,
	.probe_fbp = gm107_ram_probe_fbp,
	.probe_fbp_amount = gm200_ram_probe_fbp_amount,
	.probe_fbpa_amount = gf100_ram_probe_fbpa_amount,
	.dtor = gk104_ram_dtor,
	.init = gk104_ram_init,
	.calc = gk104_ram_calc,
	.prog = gk104_ram_prog,
	.tidy = gk104_ram_tidy,
पूर्ण;

पूर्णांक
gm200_ram_new(काष्ठा nvkm_fb *fb, काष्ठा nvkm_ram **pram)
अणु
	वापस gk104_ram_new_(&gm200_ram, fb, pram);
पूर्ण
