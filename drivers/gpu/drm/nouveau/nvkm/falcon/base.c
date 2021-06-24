<शैली गुरु>
/*
 * Copyright (c) 2016, NVIDIA CORPORATION. All rights reserved.
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
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#समावेश "priv.h"

#समावेश <subdev/mc.h>
#समावेश <subdev/top.h>

व्योम
nvkm_falcon_load_imem(काष्ठा nvkm_falcon *falcon, व्योम *data, u32 start,
		      u32 size, u16 tag, u8 port, bool secure)
अणु
	अगर (secure && !falcon->secret) अणु
		nvkm_warn(falcon->user,
			  "writing with secure tag on a non-secure falcon!\n");
		वापस;
	पूर्ण

	falcon->func->load_imem(falcon, data, start, size, tag, port,
				secure);
पूर्ण

व्योम
nvkm_falcon_load_dmem(काष्ठा nvkm_falcon *falcon, व्योम *data, u32 start,
		      u32 size, u8 port)
अणु
	mutex_lock(&falcon->dmem_mutex);

	falcon->func->load_dmem(falcon, data, start, size, port);

	mutex_unlock(&falcon->dmem_mutex);
पूर्ण

व्योम
nvkm_falcon_पढ़ो_dmem(काष्ठा nvkm_falcon *falcon, u32 start, u32 size, u8 port,
		      व्योम *data)
अणु
	mutex_lock(&falcon->dmem_mutex);

	falcon->func->पढ़ो_dmem(falcon, start, size, port, data);

	mutex_unlock(&falcon->dmem_mutex);
पूर्ण

व्योम
nvkm_falcon_bind_context(काष्ठा nvkm_falcon *falcon, काष्ठा nvkm_memory *inst)
अणु
	अगर (!falcon->func->bind_context) अणु
		nvkm_error(falcon->user,
			   "Context binding not supported on this falcon!\n");
		वापस;
	पूर्ण

	falcon->func->bind_context(falcon, inst);
पूर्ण

व्योम
nvkm_falcon_set_start_addr(काष्ठा nvkm_falcon *falcon, u32 start_addr)
अणु
	falcon->func->set_start_addr(falcon, start_addr);
पूर्ण

व्योम
nvkm_falcon_start(काष्ठा nvkm_falcon *falcon)
अणु
	falcon->func->start(falcon);
पूर्ण

पूर्णांक
nvkm_falcon_enable(काष्ठा nvkm_falcon *falcon)
अणु
	काष्ठा nvkm_device *device = falcon->owner->device;
	पूर्णांक ret;

	nvkm_mc_enable(device, falcon->owner->type, falcon->owner->inst);
	ret = falcon->func->enable(falcon);
	अगर (ret) अणु
		nvkm_mc_disable(device, falcon->owner->type, falcon->owner->inst);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

व्योम
nvkm_falcon_disable(काष्ठा nvkm_falcon *falcon)
अणु
	काष्ठा nvkm_device *device = falcon->owner->device;

	/* alपढ़ोy disabled, वापस or रुको_idle will समयout */
	अगर (!nvkm_mc_enabled(device, falcon->owner->type, falcon->owner->inst))
		वापस;

	falcon->func->disable(falcon);

	nvkm_mc_disable(device, falcon->owner->type, falcon->owner->inst);
पूर्ण

पूर्णांक
nvkm_falcon_reset(काष्ठा nvkm_falcon *falcon)
अणु
	nvkm_falcon_disable(falcon);
	वापस nvkm_falcon_enable(falcon);
पूर्ण

पूर्णांक
nvkm_falcon_रुको_क्रम_halt(काष्ठा nvkm_falcon *falcon, u32 ms)
अणु
	वापस falcon->func->रुको_क्रम_halt(falcon, ms);
पूर्ण

पूर्णांक
nvkm_falcon_clear_पूर्णांकerrupt(काष्ठा nvkm_falcon *falcon, u32 mask)
अणु
	वापस falcon->func->clear_पूर्णांकerrupt(falcon, mask);
पूर्ण

अटल पूर्णांक
nvkm_falcon_oneinit(काष्ठा nvkm_falcon *falcon)
अणु
	स्थिर काष्ठा nvkm_falcon_func *func = falcon->func;
	स्थिर काष्ठा nvkm_subdev *subdev = falcon->owner;
	u32 reg;

	अगर (!falcon->addr) अणु
		falcon->addr = nvkm_top_addr(subdev->device, subdev->type, subdev->inst);
		अगर (WARN_ON(!falcon->addr))
			वापस -ENODEV;
	पूर्ण

	reg = nvkm_falcon_rd32(falcon, 0x12c);
	falcon->version = reg & 0xf;
	falcon->secret = (reg >> 4) & 0x3;
	falcon->code.ports = (reg >> 8) & 0xf;
	falcon->data.ports = (reg >> 12) & 0xf;

	reg = nvkm_falcon_rd32(falcon, 0x108);
	falcon->code.limit = (reg & 0x1ff) << 8;
	falcon->data.limit = (reg & 0x3fe00) >> 1;

	अगर (func->debug) अणु
		u32 val = nvkm_falcon_rd32(falcon, func->debug);
		falcon->debug = (val >> 20) & 0x1;
	पूर्ण

	वापस 0;
पूर्ण

व्योम
nvkm_falcon_put(काष्ठा nvkm_falcon *falcon, स्थिर काष्ठा nvkm_subdev *user)
अणु
	अगर (unlikely(!falcon))
		वापस;

	mutex_lock(&falcon->mutex);
	अगर (falcon->user == user) अणु
		nvkm_debug(falcon->user, "released %s falcon\n", falcon->name);
		falcon->user = शून्य;
	पूर्ण
	mutex_unlock(&falcon->mutex);
पूर्ण

पूर्णांक
nvkm_falcon_get(काष्ठा nvkm_falcon *falcon, स्थिर काष्ठा nvkm_subdev *user)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&falcon->mutex);
	अगर (falcon->user) अणु
		nvkm_error(user, "%s falcon already acquired by %s!\n",
			   falcon->name, falcon->user->name);
		mutex_unlock(&falcon->mutex);
		वापस -EBUSY;
	पूर्ण

	nvkm_debug(user, "acquired %s falcon\n", falcon->name);
	अगर (!falcon->oneinit)
		ret = nvkm_falcon_oneinit(falcon);
	falcon->user = user;
	mutex_unlock(&falcon->mutex);
	वापस ret;
पूर्ण

व्योम
nvkm_falcon_dtor(काष्ठा nvkm_falcon *falcon)
अणु
पूर्ण

पूर्णांक
nvkm_falcon_ctor(स्थिर काष्ठा nvkm_falcon_func *func,
		 काष्ठा nvkm_subdev *subdev, स्थिर अक्षर *name, u32 addr,
		 काष्ठा nvkm_falcon *falcon)
अणु
	falcon->func = func;
	falcon->owner = subdev;
	falcon->name = name;
	falcon->addr = addr;
	mutex_init(&falcon->mutex);
	mutex_init(&falcon->dmem_mutex);
	वापस 0;
पूर्ण

व्योम
nvkm_falcon_del(काष्ठा nvkm_falcon **pfalcon)
अणु
	अगर (*pfalcon) अणु
		nvkm_falcon_dtor(*pfalcon);
		kमुक्त(*pfalcon);
		*pfalcon = शून्य;
	पूर्ण
पूर्ण
