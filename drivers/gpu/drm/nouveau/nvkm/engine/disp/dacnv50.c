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
#समावेश "ior.h"

#समावेश <subdev/समयr.h>

अटल व्योम
nv50_dac_घड़ी(काष्ठा nvkm_ior *dac)
अणु
	काष्ठा nvkm_device *device = dac->disp->engine.subdev.device;
	स्थिर u32 करोff = nv50_ior_base(dac);
	nvkm_mask(device, 0x614280 + करोff, 0x07070707, 0x00000000);
पूर्ण

पूर्णांक
nv50_dac_sense(काष्ठा nvkm_ior *dac, u32 loadval)
अणु
	काष्ठा nvkm_device *device = dac->disp->engine.subdev.device;
	स्थिर u32 करोff = nv50_ior_base(dac);

	dac->func->घातer(dac, false, true, false, false, false);

	nvkm_wr32(device, 0x61a00c + करोff, 0x00100000 | loadval);
	mdelay(9);
	udelay(500);
	loadval = nvkm_mask(device, 0x61a00c + करोff, 0xffffffff, 0x00000000);

	dac->func->घातer(dac, false, false, false, false, false);
	अगर (!(loadval & 0x80000000))
		वापस -ETIMEDOUT;

	वापस (loadval & 0x38000000) >> 27;
पूर्ण

अटल व्योम
nv50_dac_घातer_रुको(काष्ठा nvkm_device *device, स्थिर u32 करोff)
अणु
	nvkm_msec(device, 2000,
		अगर (!(nvkm_rd32(device, 0x61a004 + करोff) & 0x80000000))
			अवरोध;
	);
पूर्ण

व्योम
nv50_dac_घातer(काष्ठा nvkm_ior *dac, bool normal, bool pu,
	       bool data, bool vsync, bool hsync)
अणु
	काष्ठा nvkm_device *device = dac->disp->engine.subdev.device;
	स्थिर u32  करोff = nv50_ior_base(dac);
	स्थिर u32 shअगरt = normal ? 0 : 16;
	स्थिर u32 state = 0x80000000 | (0x00000040 * !    pu |
					0x00000010 * !  data |
					0x00000004 * ! vsync |
					0x00000001 * ! hsync) << shअगरt;
	स्थिर u32 field = 0xc0000000 | (0x00000055 << shअगरt);

	nv50_dac_घातer_रुको(device, करोff);
	nvkm_mask(device, 0x61a004 + करोff, field, state);
	nv50_dac_घातer_रुको(device, करोff);
पूर्ण

अटल व्योम
nv50_dac_state(काष्ठा nvkm_ior *dac, काष्ठा nvkm_ior_state *state)
अणु
	काष्ठा nvkm_device *device = dac->disp->engine.subdev.device;
	स्थिर u32 coff = dac->id * 8 + (state == &dac->arm) * 4;
	u32 ctrl = nvkm_rd32(device, 0x610b58 + coff);

	state->proto_evo = (ctrl & 0x00000f00) >> 8;
	चयन (state->proto_evo) अणु
	हाल 0: state->proto = CRT; अवरोध;
	शेष:
		state->proto = UNKNOWN;
		अवरोध;
	पूर्ण

	state->head = ctrl & 0x00000003;
पूर्ण

अटल स्थिर काष्ठा nvkm_ior_func
nv50_dac = अणु
	.state = nv50_dac_state,
	.घातer = nv50_dac_घातer,
	.sense = nv50_dac_sense,
	.घड़ी = nv50_dac_घड़ी,
पूर्ण;

पूर्णांक
nv50_dac_new(काष्ठा nvkm_disp *disp, पूर्णांक id)
अणु
	वापस nvkm_ior_new_(&nv50_dac, disp, DAC, id);
पूर्ण

पूर्णांक
nv50_dac_cnt(काष्ठा nvkm_disp *disp, अचिन्हित दीर्घ *pmask)
अणु
	काष्ठा nvkm_device *device = disp->engine.subdev.device;
	*pmask = (nvkm_rd32(device, 0x610184) & 0x00700000) >> 20;
	वापस 3;
पूर्ण
