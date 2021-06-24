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
gf108_ram_probe_fbp_amount(स्थिर काष्ठा nvkm_ram_func *func, u32 fbpao,
			   काष्ठा nvkm_device *device, पूर्णांक fbp, पूर्णांक *pltcs)
अणु
	u32 fbpt  = nvkm_rd32(device, 0x022438);
	u32 fbpat = nvkm_rd32(device, 0x02243c);
	u32 fbpas = fbpat / fbpt;
	u32 fbpa  = fbp * fbpas;
	u32 size  = 0;
	जबतक (fbpas--) अणु
		अगर (!(fbpao & BIT(fbpa)))
			size += func->probe_fbpa_amount(device, fbpa);
		fbpa++;
	पूर्ण
	*pltcs = 1;
	वापस size;
पूर्ण

अटल स्थिर काष्ठा nvkm_ram_func
gf108_ram = अणु
	.upper = 0x0200000000ULL,
	.probe_fbp = gf100_ram_probe_fbp,
	.probe_fbp_amount = gf108_ram_probe_fbp_amount,
	.probe_fbpa_amount = gf100_ram_probe_fbpa_amount,
	.init = gf100_ram_init,
	.calc = gf100_ram_calc,
	.prog = gf100_ram_prog,
	.tidy = gf100_ram_tidy,
पूर्ण;

पूर्णांक
gf108_ram_new(काष्ठा nvkm_fb *fb, काष्ठा nvkm_ram **pram)
अणु
	वापस gf100_ram_new_(&gf108_ram, fb, pram);
पूर्ण
