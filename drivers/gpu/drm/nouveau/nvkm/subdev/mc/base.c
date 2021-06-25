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
#समावेश "priv.h"

#समावेश <core/option.h>
#समावेश <subdev/top.h>

व्योम
nvkm_mc_unk260(काष्ठा nvkm_device *device, u32 data)
अणु
	काष्ठा nvkm_mc *mc = device->mc;
	अगर (likely(mc) && mc->func->unk260)
		mc->func->unk260(mc, data);
पूर्ण

व्योम
nvkm_mc_पूर्णांकr_mask(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, bool en)
अणु
	काष्ठा nvkm_mc *mc = device->mc;
	स्थिर काष्ठा nvkm_mc_map *map;
	अगर (likely(mc) && mc->func->पूर्णांकr_mask) अणु
		u32 mask = nvkm_top_पूर्णांकr_mask(device, type, inst);
		क्रम (map = mc->func->पूर्णांकr; !mask && map->stat; map++) अणु
			अगर (map->type == type && map->inst == inst)
				mask = map->stat;
		पूर्ण
		mc->func->पूर्णांकr_mask(mc, mask, en ? mask : 0);
	पूर्ण
पूर्ण

व्योम
nvkm_mc_पूर्णांकr_unarm(काष्ठा nvkm_device *device)
अणु
	काष्ठा nvkm_mc *mc = device->mc;
	अगर (likely(mc))
		mc->func->पूर्णांकr_unarm(mc);
पूर्ण

व्योम
nvkm_mc_पूर्णांकr_rearm(काष्ठा nvkm_device *device)
अणु
	काष्ठा nvkm_mc *mc = device->mc;
	अगर (likely(mc))
		mc->func->पूर्णांकr_rearm(mc);
पूर्ण

अटल u32
nvkm_mc_पूर्णांकr_stat(काष्ठा nvkm_mc *mc)
अणु
	u32 पूर्णांकr = mc->func->पूर्णांकr_stat(mc);
	अगर (WARN_ON_ONCE(पूर्णांकr == 0xffffffff))
		पूर्णांकr = 0; /* likely fallen off the bus */
	वापस पूर्णांकr;
पूर्ण

व्योम
nvkm_mc_पूर्णांकr(काष्ठा nvkm_device *device, bool *handled)
अणु
	काष्ठा nvkm_mc *mc = device->mc;
	काष्ठा nvkm_top *top = device->top;
	काष्ठा nvkm_top_device *tdev;
	काष्ठा nvkm_subdev *subdev;
	स्थिर काष्ठा nvkm_mc_map *map;
	u32 stat, पूर्णांकr;

	अगर (unlikely(!mc))
		वापस;

	stat = पूर्णांकr = nvkm_mc_पूर्णांकr_stat(mc);

	अगर (top) अणु
		list_क्रम_each_entry(tdev, &top->device, head) अणु
			अगर (tdev->पूर्णांकr >= 0 && (stat & BIT(tdev->पूर्णांकr))) अणु
				subdev = nvkm_device_subdev(device, tdev->type, tdev->inst);
				अगर (subdev) अणु
					nvkm_subdev_पूर्णांकr(subdev);
					stat &= ~BIT(tdev->पूर्णांकr);
					अगर (!stat)
						अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (map = mc->func->पूर्णांकr; map->stat; map++) अणु
		अगर (पूर्णांकr & map->stat) अणु
			subdev = nvkm_device_subdev(device, map->type, map->inst);
			अगर (subdev)
				nvkm_subdev_पूर्णांकr(subdev);
			stat &= ~map->stat;
		पूर्ण
	पूर्ण

	अगर (stat)
		nvkm_error(&mc->subdev, "intr %08x\n", stat);
	*handled = पूर्णांकr != 0;
पूर्ण

अटल u32
nvkm_mc_reset_mask(काष्ठा nvkm_device *device, bool isस्वतः, क्रमागत nvkm_subdev_type type, पूर्णांक inst)
अणु
	काष्ठा nvkm_mc *mc = device->mc;
	स्थिर काष्ठा nvkm_mc_map *map;
	u64 pmc_enable = 0;
	अगर (likely(mc)) अणु
		अगर (!(pmc_enable = nvkm_top_reset(device, type, inst))) अणु
			क्रम (map = mc->func->reset; map && map->stat; map++) अणु
				अगर (!isस्वतः || !map->noस्वतः) अणु
					अगर (map->type == type && map->inst == inst) अणु
						pmc_enable = map->stat;
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	वापस pmc_enable;
पूर्ण

व्योम
nvkm_mc_reset(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst)
अणु
	u64 pmc_enable = nvkm_mc_reset_mask(device, true, type, inst);
	अगर (pmc_enable) अणु
		nvkm_mask(device, 0x000200, pmc_enable, 0x00000000);
		nvkm_mask(device, 0x000200, pmc_enable, pmc_enable);
		nvkm_rd32(device, 0x000200);
	पूर्ण
पूर्ण

व्योम
nvkm_mc_disable(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst)
अणु
	u64 pmc_enable = nvkm_mc_reset_mask(device, false, type, inst);
	अगर (pmc_enable)
		nvkm_mask(device, 0x000200, pmc_enable, 0x00000000);
पूर्ण

व्योम
nvkm_mc_enable(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst)
अणु
	u64 pmc_enable = nvkm_mc_reset_mask(device, false, type, inst);
	अगर (pmc_enable) अणु
		nvkm_mask(device, 0x000200, pmc_enable, pmc_enable);
		nvkm_rd32(device, 0x000200);
	पूर्ण
पूर्ण

bool
nvkm_mc_enabled(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst)
अणु
	u64 pmc_enable = nvkm_mc_reset_mask(device, false, type, inst);

	वापस (pmc_enable != 0) &&
	       ((nvkm_rd32(device, 0x000200) & pmc_enable) == pmc_enable);
पूर्ण


अटल पूर्णांक
nvkm_mc_fini(काष्ठा nvkm_subdev *subdev, bool suspend)
अणु
	nvkm_mc_पूर्णांकr_unarm(subdev->device);
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_mc_init(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_mc *mc = nvkm_mc(subdev);
	अगर (mc->func->init)
		mc->func->init(mc);
	nvkm_mc_पूर्णांकr_rearm(subdev->device);
	वापस 0;
पूर्ण

अटल व्योम *
nvkm_mc_dtor(काष्ठा nvkm_subdev *subdev)
अणु
	वापस nvkm_mc(subdev);
पूर्ण

अटल स्थिर काष्ठा nvkm_subdev_func
nvkm_mc = अणु
	.dtor = nvkm_mc_dtor,
	.init = nvkm_mc_init,
	.fini = nvkm_mc_fini,
पूर्ण;

व्योम
nvkm_mc_ctor(स्थिर काष्ठा nvkm_mc_func *func, काष्ठा nvkm_device *device,
	     क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_mc *mc)
अणु
	nvkm_subdev_ctor(&nvkm_mc, device, type, inst, &mc->subdev);
	mc->func = func;
पूर्ण

पूर्णांक
nvkm_mc_new_(स्थिर काष्ठा nvkm_mc_func *func, काष्ठा nvkm_device *device,
	     क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_mc **pmc)
अणु
	काष्ठा nvkm_mc *mc;
	अगर (!(mc = *pmc = kzalloc(माप(*mc), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_mc_ctor(func, device, type, inst, *pmc);
	वापस 0;
पूर्ण
