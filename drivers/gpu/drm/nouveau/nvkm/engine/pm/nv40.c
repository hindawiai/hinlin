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
#समावेश "nv40.h"

अटल व्योम
nv40_perfctr_init(काष्ठा nvkm_pm *pm, काष्ठा nvkm_perfकरोm *करोm,
		  काष्ठा nvkm_perfctr *ctr)
अणु
	काष्ठा nvkm_device *device = pm->engine.subdev.device;
	u32 log = ctr->logic_op;
	u32 src = 0x00000000;
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++)
		src |= ctr->संकेत[i] << (i * 8);

	nvkm_wr32(device, 0x00a7c0 + करोm->addr, 0x00000001 | (करोm->mode << 4));
	nvkm_wr32(device, 0x00a400 + करोm->addr + (ctr->slot * 0x40), src);
	nvkm_wr32(device, 0x00a420 + करोm->addr + (ctr->slot * 0x40), log);
पूर्ण

अटल व्योम
nv40_perfctr_पढ़ो(काष्ठा nvkm_pm *pm, काष्ठा nvkm_perfकरोm *करोm,
		  काष्ठा nvkm_perfctr *ctr)
अणु
	काष्ठा nvkm_device *device = pm->engine.subdev.device;

	चयन (ctr->slot) अणु
	हाल 0: ctr->ctr = nvkm_rd32(device, 0x00a700 + करोm->addr); अवरोध;
	हाल 1: ctr->ctr = nvkm_rd32(device, 0x00a6c0 + करोm->addr); अवरोध;
	हाल 2: ctr->ctr = nvkm_rd32(device, 0x00a680 + करोm->addr); अवरोध;
	हाल 3: ctr->ctr = nvkm_rd32(device, 0x00a740 + करोm->addr); अवरोध;
	पूर्ण
	करोm->clk = nvkm_rd32(device, 0x00a600 + करोm->addr);
पूर्ण

अटल व्योम
nv40_perfctr_next(काष्ठा nvkm_pm *pm, काष्ठा nvkm_perfकरोm *करोm)
अणु
	काष्ठा nvkm_device *device = pm->engine.subdev.device;
	काष्ठा nv40_pm *nv40pm = container_of(pm, काष्ठा nv40_pm, base);

	अगर (nv40pm->sequence != pm->sequence) अणु
		nvkm_wr32(device, 0x400084, 0x00000020);
		nv40pm->sequence = pm->sequence;
	पूर्ण
पूर्ण

स्थिर काष्ठा nvkm_funcकरोm
nv40_perfctr_func = अणु
	.init = nv40_perfctr_init,
	.पढ़ो = nv40_perfctr_पढ़ो,
	.next = nv40_perfctr_next,
पूर्ण;

अटल स्थिर काष्ठा nvkm_pm_func
nv40_pm_ = अणु
पूर्ण;

पूर्णांक
nv40_pm_new_(स्थिर काष्ठा nvkm_specकरोm *करोms, काष्ठा nvkm_device *device,
	     क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_pm **ppm)
अणु
	काष्ठा nv40_pm *pm;
	पूर्णांक ret;

	अगर (!(pm = kzalloc(माप(*pm), GFP_KERNEL)))
		वापस -ENOMEM;
	*ppm = &pm->base;

	ret = nvkm_pm_ctor(&nv40_pm_, device, type, inst, &pm->base);
	अगर (ret)
		वापस ret;

	वापस nvkm_perfकरोm_new(&pm->base, "pc", 0, 0, 0, 4, करोms);
पूर्ण

अटल स्थिर काष्ठा nvkm_specकरोm
nv40_pm[] = अणु
	अणु 0x20, (स्थिर काष्ठा nvkm_specsig[]) अणु
			अणुपूर्ण
		पूर्ण, &nv40_perfctr_func पूर्ण,
	अणु 0x20, (स्थिर काष्ठा nvkm_specsig[]) अणु
			अणुपूर्ण
		पूर्ण, &nv40_perfctr_func पूर्ण,
	अणु 0x20, (स्थिर काष्ठा nvkm_specsig[]) अणु
			अणुपूर्ण
		पूर्ण, &nv40_perfctr_func पूर्ण,
	अणु 0x20, (स्थिर काष्ठा nvkm_specsig[]) अणु
			अणुपूर्ण
		पूर्ण, &nv40_perfctr_func पूर्ण,
	अणु 0x20, (स्थिर काष्ठा nvkm_specsig[]) अणु
			अणुपूर्ण
		पूर्ण, &nv40_perfctr_func पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक
nv40_pm_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_pm **ppm)
अणु
	वापस nv40_pm_new_(nv40_pm, device, type, inst, ppm);
पूर्ण
