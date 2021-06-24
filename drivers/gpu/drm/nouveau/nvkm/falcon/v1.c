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

#समावेश <core/gpuobj.h>
#समावेश <core/memory.h>
#समावेश <subdev/समयr.h>

व्योम
nvkm_falcon_v1_load_imem(काष्ठा nvkm_falcon *falcon, व्योम *data, u32 start,
			 u32 size, u16 tag, u8 port, bool secure)
अणु
	u8 rem = size % 4;
	u32 reg;
	पूर्णांक i;

	size -= rem;

	reg = start | BIT(24) | (secure ? BIT(28) : 0);
	nvkm_falcon_wr32(falcon, 0x180 + (port * 16), reg);
	क्रम (i = 0; i < size / 4; i++) अणु
		/* ग_लिखो new tag every 256B */
		अगर ((i & 0x3f) == 0)
			nvkm_falcon_wr32(falcon, 0x188 + (port * 16), tag++);
		nvkm_falcon_wr32(falcon, 0x184 + (port * 16), ((u32 *)data)[i]);
	पूर्ण

	/*
	 * If size is not a multiple of 4, mask the last work to ensure garbage
	 * करोes not get written
	 */
	अगर (rem) अणु
		u32 extra = ((u32 *)data)[i];

		/* ग_लिखो new tag every 256B */
		अगर ((i & 0x3f) == 0)
			nvkm_falcon_wr32(falcon, 0x188 + (port * 16), tag++);
		nvkm_falcon_wr32(falcon, 0x184 + (port * 16),
				 extra & (BIT(rem * 8) - 1));
		++i;
	पूर्ण

	/* code must be padded to 0x40 words */
	क्रम (; i & 0x3f; i++)
		nvkm_falcon_wr32(falcon, 0x184 + (port * 16), 0);
पूर्ण

अटल व्योम
nvkm_falcon_v1_load_emem(काष्ठा nvkm_falcon *falcon, व्योम *data, u32 start,
			 u32 size, u8 port)
अणु
	u8 rem = size % 4;
	पूर्णांक i;

	size -= rem;

	nvkm_falcon_wr32(falcon, 0xac0 + (port * 8), start | (0x1 << 24));
	क्रम (i = 0; i < size / 4; i++)
		nvkm_falcon_wr32(falcon, 0xac4 + (port * 8), ((u32 *)data)[i]);

	/*
	 * If size is not a multiple of 4, mask the last word to ensure garbage
	 * करोes not get written
	 */
	अगर (rem) अणु
		u32 extra = ((u32 *)data)[i];

		nvkm_falcon_wr32(falcon, 0xac4 + (port * 8),
				 extra & (BIT(rem * 8) - 1));
	पूर्ण
पूर्ण

व्योम
nvkm_falcon_v1_load_dmem(काष्ठा nvkm_falcon *falcon, व्योम *data, u32 start,
			 u32 size, u8 port)
अणु
	स्थिर काष्ठा nvkm_falcon_func *func = falcon->func;
	u8 rem = size % 4;
	पूर्णांक i;

	अगर (func->emem_addr && start >= func->emem_addr)
		वापस nvkm_falcon_v1_load_emem(falcon, data,
						start - func->emem_addr, size,
						port);

	size -= rem;

	nvkm_falcon_wr32(falcon, 0x1c0 + (port * 8), start | (0x1 << 24));
	क्रम (i = 0; i < size / 4; i++)
		nvkm_falcon_wr32(falcon, 0x1c4 + (port * 8), ((u32 *)data)[i]);

	/*
	 * If size is not a multiple of 4, mask the last word to ensure garbage
	 * करोes not get written
	 */
	अगर (rem) अणु
		u32 extra = ((u32 *)data)[i];

		nvkm_falcon_wr32(falcon, 0x1c4 + (port * 8),
				 extra & (BIT(rem * 8) - 1));
	पूर्ण
पूर्ण

अटल व्योम
nvkm_falcon_v1_पढ़ो_emem(काष्ठा nvkm_falcon *falcon, u32 start, u32 size,
			 u8 port, व्योम *data)
अणु
	u8 rem = size % 4;
	पूर्णांक i;

	size -= rem;

	nvkm_falcon_wr32(falcon, 0xac0 + (port * 8), start | (0x1 << 25));
	क्रम (i = 0; i < size / 4; i++)
		((u32 *)data)[i] = nvkm_falcon_rd32(falcon, 0xac4 + (port * 8));

	/*
	 * If size is not a multiple of 4, mask the last word to ensure garbage
	 * करोes not get पढ़ो
	 */
	अगर (rem) अणु
		u32 extra = nvkm_falcon_rd32(falcon, 0xac4 + (port * 8));

		क्रम (i = size; i < size + rem; i++) अणु
			((u8 *)data)[i] = (u8)(extra & 0xff);
			extra >>= 8;
		पूर्ण
	पूर्ण
पूर्ण

व्योम
nvkm_falcon_v1_पढ़ो_dmem(काष्ठा nvkm_falcon *falcon, u32 start, u32 size,
			 u8 port, व्योम *data)
अणु
	स्थिर काष्ठा nvkm_falcon_func *func = falcon->func;
	u8 rem = size % 4;
	पूर्णांक i;

	अगर (func->emem_addr && start >= func->emem_addr)
		वापस nvkm_falcon_v1_पढ़ो_emem(falcon, start - func->emem_addr,
						size, port, data);

	size -= rem;

	nvkm_falcon_wr32(falcon, 0x1c0 + (port * 8), start | (0x1 << 25));
	क्रम (i = 0; i < size / 4; i++)
		((u32 *)data)[i] = nvkm_falcon_rd32(falcon, 0x1c4 + (port * 8));

	/*
	 * If size is not a multiple of 4, mask the last word to ensure garbage
	 * करोes not get पढ़ो
	 */
	अगर (rem) अणु
		u32 extra = nvkm_falcon_rd32(falcon, 0x1c4 + (port * 8));

		क्रम (i = size; i < size + rem; i++) अणु
			((u8 *)data)[i] = (u8)(extra & 0xff);
			extra >>= 8;
		पूर्ण
	पूर्ण
पूर्ण

व्योम
nvkm_falcon_v1_bind_context(काष्ठा nvkm_falcon *falcon, काष्ठा nvkm_memory *ctx)
अणु
	स्थिर u32 fbअगर = falcon->func->fbअगर;
	u32 inst_loc;

	/* disable instance block binding */
	अगर (ctx == शून्य) अणु
		nvkm_falcon_wr32(falcon, 0x10c, 0x0);
		वापस;
	पूर्ण

	nvkm_falcon_wr32(falcon, 0x10c, 0x1);

	/* setup apertures - भव */
	nvkm_falcon_wr32(falcon, fbअगर + 4 * FALCON_DMAIDX_UCODE, 0x4);
	nvkm_falcon_wr32(falcon, fbअगर + 4 * FALCON_DMAIDX_VIRT, 0x0);
	/* setup apertures - physical */
	nvkm_falcon_wr32(falcon, fbअगर + 4 * FALCON_DMAIDX_PHYS_VID, 0x4);
	nvkm_falcon_wr32(falcon, fbअगर + 4 * FALCON_DMAIDX_PHYS_SYS_COH, 0x5);
	nvkm_falcon_wr32(falcon, fbअगर + 4 * FALCON_DMAIDX_PHYS_SYS_NCOH, 0x6);

	/* Set context */
	चयन (nvkm_memory_target(ctx)) अणु
	हाल NVKM_MEM_TARGET_VRAM: inst_loc = 0; अवरोध;
	हाल NVKM_MEM_TARGET_HOST: inst_loc = 2; अवरोध;
	हाल NVKM_MEM_TARGET_NCOH: inst_loc = 3; अवरोध;
	शेष:
		WARN_ON(1);
		वापस;
	पूर्ण

	/* Enable context */
	nvkm_falcon_mask(falcon, 0x048, 0x1, 0x1);
	nvkm_falcon_wr32(falcon, 0x054,
			 ((nvkm_memory_addr(ctx) >> 12) & 0xfffffff) |
			 (inst_loc << 28) | (1 << 30));

	nvkm_falcon_mask(falcon, 0x090, 0x10000, 0x10000);
	nvkm_falcon_mask(falcon, 0x0a4, 0x8, 0x8);
पूर्ण

व्योम
nvkm_falcon_v1_set_start_addr(काष्ठा nvkm_falcon *falcon, u32 start_addr)
अणु
	nvkm_falcon_wr32(falcon, 0x104, start_addr);
पूर्ण

व्योम
nvkm_falcon_v1_start(काष्ठा nvkm_falcon *falcon)
अणु
	u32 reg = nvkm_falcon_rd32(falcon, 0x100);

	अगर (reg & BIT(6))
		nvkm_falcon_wr32(falcon, 0x130, 0x2);
	अन्यथा
		nvkm_falcon_wr32(falcon, 0x100, 0x2);
पूर्ण

पूर्णांक
nvkm_falcon_v1_रुको_क्रम_halt(काष्ठा nvkm_falcon *falcon, u32 ms)
अणु
	काष्ठा nvkm_device *device = falcon->owner->device;
	पूर्णांक ret;

	ret = nvkm_रुको_msec(device, ms, falcon->addr + 0x100, 0x10, 0x10);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक
nvkm_falcon_v1_clear_पूर्णांकerrupt(काष्ठा nvkm_falcon *falcon, u32 mask)
अणु
	काष्ठा nvkm_device *device = falcon->owner->device;
	पूर्णांक ret;

	/* clear पूर्णांकerrupt(s) */
	nvkm_falcon_mask(falcon, 0x004, mask, mask);
	/* रुको until पूर्णांकerrupts are cleared */
	ret = nvkm_रुको_msec(device, 10, falcon->addr + 0x008, mask, 0x0);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक
falcon_v1_रुको_idle(काष्ठा nvkm_falcon *falcon)
अणु
	काष्ठा nvkm_device *device = falcon->owner->device;
	पूर्णांक ret;

	ret = nvkm_रुको_msec(device, 10, falcon->addr + 0x04c, 0xffff, 0x0);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक
nvkm_falcon_v1_enable(काष्ठा nvkm_falcon *falcon)
अणु
	काष्ठा nvkm_device *device = falcon->owner->device;
	पूर्णांक ret;

	ret = nvkm_रुको_msec(device, 10, falcon->addr + 0x10c, 0x6, 0x0);
	अगर (ret < 0) अणु
		nvkm_error(falcon->user, "Falcon mem scrubbing timeout\n");
		वापस ret;
	पूर्ण

	ret = falcon_v1_रुको_idle(falcon);
	अगर (ret)
		वापस ret;

	/* enable IRQs */
	nvkm_falcon_wr32(falcon, 0x010, 0xff);

	वापस 0;
पूर्ण

व्योम
nvkm_falcon_v1_disable(काष्ठा nvkm_falcon *falcon)
अणु
	/* disable IRQs and रुको क्रम any previous code to complete */
	nvkm_falcon_wr32(falcon, 0x014, 0xff);
	falcon_v1_रुको_idle(falcon);
पूर्ण

अटल स्थिर काष्ठा nvkm_falcon_func
nvkm_falcon_v1 = अणु
	.load_imem = nvkm_falcon_v1_load_imem,
	.load_dmem = nvkm_falcon_v1_load_dmem,
	.पढ़ो_dmem = nvkm_falcon_v1_पढ़ो_dmem,
	.bind_context = nvkm_falcon_v1_bind_context,
	.start = nvkm_falcon_v1_start,
	.रुको_क्रम_halt = nvkm_falcon_v1_रुको_क्रम_halt,
	.clear_पूर्णांकerrupt = nvkm_falcon_v1_clear_पूर्णांकerrupt,
	.enable = nvkm_falcon_v1_enable,
	.disable = nvkm_falcon_v1_disable,
	.set_start_addr = nvkm_falcon_v1_set_start_addr,
पूर्ण;

पूर्णांक
nvkm_falcon_v1_new(काष्ठा nvkm_subdev *owner, स्थिर अक्षर *name, u32 addr,
		   काष्ठा nvkm_falcon **pfalcon)
अणु
	काष्ठा nvkm_falcon *falcon;
	अगर (!(falcon = *pfalcon = kzalloc(माप(*falcon), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_falcon_ctor(&nvkm_falcon_v1, owner, name, addr, falcon);
	वापस 0;
पूर्ण
