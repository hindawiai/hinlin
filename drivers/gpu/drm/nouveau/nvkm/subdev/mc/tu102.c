<शैली गुरु>
/*
 * Copyright 2018 Red Hat Inc.
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
 */
#घोषणा tu102_mc(p) container_of((p), काष्ठा tu102_mc, base)
#समावेश "priv.h"

काष्ठा tu102_mc अणु
	काष्ठा nvkm_mc base;
	spinlock_t lock;
	bool पूर्णांकr;
	u32 mask;
पूर्ण;

अटल व्योम
tu102_mc_पूर्णांकr_update(काष्ठा tu102_mc *mc)
अणु
	काष्ठा nvkm_device *device = mc->base.subdev.device;
	u32 mask = mc->पूर्णांकr ? mc->mask : 0, i;

	क्रम (i = 0; i < 2; i++) अणु
		nvkm_wr32(device, 0x000180 + (i * 0x04), ~mask);
		nvkm_wr32(device, 0x000160 + (i * 0x04),  mask);
	पूर्ण

	अगर (mask & 0x00000200)
		nvkm_wr32(device, 0xb81608, 0x6);
	अन्यथा
		nvkm_wr32(device, 0xb81610, 0x6);
पूर्ण

व्योम
tu102_mc_पूर्णांकr_unarm(काष्ठा nvkm_mc *base)
अणु
	काष्ठा tu102_mc *mc = tu102_mc(base);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mc->lock, flags);
	mc->पूर्णांकr = false;
	tu102_mc_पूर्णांकr_update(mc);
	spin_unlock_irqrestore(&mc->lock, flags);
पूर्ण

व्योम
tu102_mc_पूर्णांकr_rearm(काष्ठा nvkm_mc *base)
अणु
	काष्ठा tu102_mc *mc = tu102_mc(base);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mc->lock, flags);
	mc->पूर्णांकr = true;
	tu102_mc_पूर्णांकr_update(mc);
	spin_unlock_irqrestore(&mc->lock, flags);
पूर्ण

व्योम
tu102_mc_पूर्णांकr_mask(काष्ठा nvkm_mc *base, u32 mask, u32 पूर्णांकr)
अणु
	काष्ठा tu102_mc *mc = tu102_mc(base);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mc->lock, flags);
	mc->mask = (mc->mask & ~mask) | पूर्णांकr;
	tu102_mc_पूर्णांकr_update(mc);
	spin_unlock_irqrestore(&mc->lock, flags);
पूर्ण

अटल u32
tu102_mc_पूर्णांकr_stat(काष्ठा nvkm_mc *mc)
अणु
	काष्ठा nvkm_device *device = mc->subdev.device;
	u32 पूर्णांकr0 = nvkm_rd32(device, 0x000100);
	u32 पूर्णांकr1 = nvkm_rd32(device, 0x000104);
	u32 पूर्णांकr_top = nvkm_rd32(device, 0xb81600);

	/* Turing and above route the MMU fault पूर्णांकerrupts via a dअगरferent
	 * पूर्णांकerrupt tree with dअगरferent control रेजिस्टरs. For the moment remap
	 * them back to the old PMC vector.
	 */
	अगर (पूर्णांकr_top & 0x00000006)
		पूर्णांकr0 |= 0x00000200;

	वापस पूर्णांकr0 | पूर्णांकr1;
पूर्ण


अटल स्थिर काष्ठा nvkm_mc_func
tu102_mc = अणु
	.init = nv50_mc_init,
	.पूर्णांकr = gp100_mc_पूर्णांकr,
	.पूर्णांकr_unarm = tu102_mc_पूर्णांकr_unarm,
	.पूर्णांकr_rearm = tu102_mc_पूर्णांकr_rearm,
	.पूर्णांकr_mask = tu102_mc_पूर्णांकr_mask,
	.पूर्णांकr_stat = tu102_mc_पूर्णांकr_stat,
	.reset = gk104_mc_reset,
पूर्ण;

अटल पूर्णांक
tu102_mc_new_(स्थिर काष्ठा nvkm_mc_func *func, काष्ठा nvkm_device *device,
	      क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_mc **pmc)
अणु
	काष्ठा tu102_mc *mc;

	अगर (!(mc = kzalloc(माप(*mc), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_mc_ctor(func, device, type, inst, &mc->base);
	*pmc = &mc->base;

	spin_lock_init(&mc->lock);
	mc->पूर्णांकr = false;
	mc->mask = 0x7fffffff;
	वापस 0;
पूर्ण

पूर्णांक
tu102_mc_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_mc **pmc)
अणु
	वापस tu102_mc_new_(&tu102_mc, device, type, inst, pmc);
पूर्ण
