<शैली गुरु>
/*
 * Copyright 2012 Red Hat Inc.
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
#घोषणा gp100_mc(p) container_of((p), काष्ठा gp100_mc, base)
#समावेश "priv.h"

काष्ठा gp100_mc अणु
	काष्ठा nvkm_mc base;
	spinlock_t lock;
	bool पूर्णांकr;
	u32 mask;
पूर्ण;

अटल व्योम
gp100_mc_पूर्णांकr_update(काष्ठा gp100_mc *mc)
अणु
	काष्ठा nvkm_device *device = mc->base.subdev.device;
	u32 mask = mc->पूर्णांकr ? mc->mask : 0, i;
	क्रम (i = 0; i < 2; i++) अणु
		nvkm_wr32(device, 0x000180 + (i * 0x04), ~mask);
		nvkm_wr32(device, 0x000160 + (i * 0x04),  mask);
	पूर्ण
पूर्ण

व्योम
gp100_mc_पूर्णांकr_unarm(काष्ठा nvkm_mc *base)
अणु
	काष्ठा gp100_mc *mc = gp100_mc(base);
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&mc->lock, flags);
	mc->पूर्णांकr = false;
	gp100_mc_पूर्णांकr_update(mc);
	spin_unlock_irqrestore(&mc->lock, flags);
पूर्ण

व्योम
gp100_mc_पूर्णांकr_rearm(काष्ठा nvkm_mc *base)
अणु
	काष्ठा gp100_mc *mc = gp100_mc(base);
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&mc->lock, flags);
	mc->पूर्णांकr = true;
	gp100_mc_पूर्णांकr_update(mc);
	spin_unlock_irqrestore(&mc->lock, flags);
पूर्ण

व्योम
gp100_mc_पूर्णांकr_mask(काष्ठा nvkm_mc *base, u32 mask, u32 पूर्णांकr)
अणु
	काष्ठा gp100_mc *mc = gp100_mc(base);
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&mc->lock, flags);
	mc->mask = (mc->mask & ~mask) | पूर्णांकr;
	gp100_mc_पूर्णांकr_update(mc);
	spin_unlock_irqrestore(&mc->lock, flags);
पूर्ण

स्थिर काष्ठा nvkm_mc_map
gp100_mc_पूर्णांकr[] = अणु
	अणु 0x04000000, NVKM_ENGINE_DISP पूर्ण,
	अणु 0x00000100, NVKM_ENGINE_FIFO पूर्ण,
	अणु 0x00000200, NVKM_SUBDEV_FAULT पूर्ण,
	अणु 0x40000000, NVKM_SUBDEV_PRIVRING पूर्ण,
	अणु 0x10000000, NVKM_SUBDEV_BUS पूर्ण,
	अणु 0x08000000, NVKM_SUBDEV_FB पूर्ण,
	अणु 0x02000000, NVKM_SUBDEV_LTC पूर्ण,
	अणु 0x01000000, NVKM_SUBDEV_PMU पूर्ण,
	अणु 0x00200000, NVKM_SUBDEV_GPIO पूर्ण,
	अणु 0x00200000, NVKM_SUBDEV_I2C पूर्ण,
	अणु 0x00100000, NVKM_SUBDEV_TIMER पूर्ण,
	अणु 0x00040000, NVKM_SUBDEV_THERM पूर्ण,
	अणु 0x00002000, NVKM_SUBDEV_FB पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_mc_func
gp100_mc = अणु
	.init = nv50_mc_init,
	.पूर्णांकr = gp100_mc_पूर्णांकr,
	.पूर्णांकr_unarm = gp100_mc_पूर्णांकr_unarm,
	.पूर्णांकr_rearm = gp100_mc_पूर्णांकr_rearm,
	.पूर्णांकr_mask = gp100_mc_पूर्णांकr_mask,
	.पूर्णांकr_stat = gf100_mc_पूर्णांकr_stat,
	.reset = gk104_mc_reset,
पूर्ण;

पूर्णांक
gp100_mc_new_(स्थिर काष्ठा nvkm_mc_func *func, काष्ठा nvkm_device *device,
	      क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_mc **pmc)
अणु
	काष्ठा gp100_mc *mc;

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
gp100_mc_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_mc **pmc)
अणु
	वापस gp100_mc_new_(&gp100_mc, device, type, inst, pmc);
पूर्ण
