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
#समावेश "ram.h"

u32
gm107_ram_probe_fbp(स्थिर काष्ठा nvkm_ram_func *func,
		    काष्ठा nvkm_device *device, पूर्णांक fbp, पूर्णांक *pltcs)
अणु
	u32 fbpao = nvkm_rd32(device, 0x021c14);
	वापस func->probe_fbp_amount(func, fbpao, device, fbp, pltcs);
पूर्ण

अटल स्थिर काष्ठा nvkm_ram_func
gm107_ram = अणु
	.upper = 0x1000000000ULL,
	.probe_fbp = gm107_ram_probe_fbp,
	.probe_fbp_amount = gf108_ram_probe_fbp_amount,
	.probe_fbpa_amount = gf100_ram_probe_fbpa_amount,
	.dtor = gk104_ram_dtor,
	.init = gk104_ram_init,
	.calc = gk104_ram_calc,
	.prog = gk104_ram_prog,
	.tidy = gk104_ram_tidy,
पूर्ण;

पूर्णांक
gm107_ram_new(काष्ठा nvkm_fb *fb, काष्ठा nvkm_ram **pram)
अणु
	वापस gk104_ram_new_(&gm107_ram, fb, pram);
पूर्ण
