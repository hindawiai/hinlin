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
 */
#समावेश "ior.h"

अटल व्योम
gf119_dac_घड़ी(काष्ठा nvkm_ior *dac)
अणु
	काष्ठा nvkm_device *device = dac->disp->engine.subdev.device;
	स्थिर u32 करोff = nv50_ior_base(dac);
	nvkm_mask(device, 0x612280 + करोff, 0x07070707, 0x00000000);
पूर्ण

अटल व्योम
gf119_dac_state(काष्ठा nvkm_ior *dac, काष्ठा nvkm_ior_state *state)
अणु
	काष्ठा nvkm_device *device = dac->disp->engine.subdev.device;
	स्थिर u32 coff = (state == &dac->asy) * 0x20000 + dac->id * 0x20;
	u32 ctrl = nvkm_rd32(device, 0x640180 + coff);

	state->proto_evo = (ctrl & 0x00000f00) >> 8;
	चयन (state->proto_evo) अणु
	हाल 0: state->proto = CRT; अवरोध;
	शेष:
		state->proto = UNKNOWN;
		अवरोध;
	पूर्ण

	state->head = ctrl & 0x0000000f;
पूर्ण

अटल स्थिर काष्ठा nvkm_ior_func
gf119_dac = अणु
	.state = gf119_dac_state,
	.घातer = nv50_dac_घातer,
	.sense = nv50_dac_sense,
	.घड़ी = gf119_dac_घड़ी,
पूर्ण;

पूर्णांक
gf119_dac_new(काष्ठा nvkm_disp *disp, पूर्णांक id)
अणु
	वापस nvkm_ior_new_(&gf119_dac, disp, DAC, id);
पूर्ण

पूर्णांक
gf119_dac_cnt(काष्ठा nvkm_disp *disp, अचिन्हित दीर्घ *pmask)
अणु
	काष्ठा nvkm_device *device = disp->engine.subdev.device;
	*pmask = (nvkm_rd32(device, 0x612004) & 0x000000f0) >> 4;
	वापस 4;
पूर्ण
