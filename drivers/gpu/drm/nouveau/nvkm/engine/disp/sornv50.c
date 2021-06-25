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

व्योम
nv50_sor_घड़ी(काष्ठा nvkm_ior *sor)
अणु
	काष्ठा nvkm_device *device = sor->disp->engine.subdev.device;
	स्थिर पूर्णांक  भाग = sor->asy.link == 3;
	स्थिर u32 soff = nv50_ior_base(sor);
	nvkm_mask(device, 0x614300 + soff, 0x00000707, (भाग << 8) | भाग);
पूर्ण

अटल व्योम
nv50_sor_घातer_रुको(काष्ठा nvkm_device *device, u32 soff)
अणु
	nvkm_msec(device, 2000,
		अगर (!(nvkm_rd32(device, 0x61c004 + soff) & 0x80000000))
			अवरोध;
	);
पूर्ण

व्योम
nv50_sor_घातer(काष्ठा nvkm_ior *sor, bool normal, bool pu,
	       bool data, bool vsync, bool hsync)
अणु
	काष्ठा nvkm_device *device = sor->disp->engine.subdev.device;
	स्थिर u32  soff = nv50_ior_base(sor);
	स्थिर u32 shअगरt = normal ? 0 : 16;
	स्थिर u32 state = 0x80000000 | (0x00000001 * !!pu) << shअगरt;
	स्थिर u32 field = 0x80000000 | (0x00000001 << shअगरt);

	nv50_sor_घातer_रुको(device, soff);
	nvkm_mask(device, 0x61c004 + soff, field, state);
	nv50_sor_घातer_रुको(device, soff);

	nvkm_msec(device, 2000,
		अगर (!(nvkm_rd32(device, 0x61c030 + soff) & 0x10000000))
			अवरोध;
	);
पूर्ण

व्योम
nv50_sor_state(काष्ठा nvkm_ior *sor, काष्ठा nvkm_ior_state *state)
अणु
	काष्ठा nvkm_device *device = sor->disp->engine.subdev.device;
	स्थिर u32 coff = sor->id * 8 + (state == &sor->arm) * 4;
	u32 ctrl = nvkm_rd32(device, 0x610b70 + coff);

	state->proto_evo = (ctrl & 0x00000f00) >> 8;
	चयन (state->proto_evo) अणु
	हाल 0: state->proto = LVDS; state->link = 1; अवरोध;
	हाल 1: state->proto = TMDS; state->link = 1; अवरोध;
	हाल 2: state->proto = TMDS; state->link = 2; अवरोध;
	हाल 5: state->proto = TMDS; state->link = 3; अवरोध;
	शेष:
		state->proto = UNKNOWN;
		अवरोध;
	पूर्ण

	state->head = ctrl & 0x00000003;
पूर्ण

अटल स्थिर काष्ठा nvkm_ior_func
nv50_sor = अणु
	.state = nv50_sor_state,
	.घातer = nv50_sor_घातer,
	.घड़ी = nv50_sor_घड़ी,
पूर्ण;

पूर्णांक
nv50_sor_new(काष्ठा nvkm_disp *disp, पूर्णांक id)
अणु
	वापस nvkm_ior_new_(&nv50_sor, disp, SOR, id);
पूर्ण

पूर्णांक
nv50_sor_cnt(काष्ठा nvkm_disp *disp, अचिन्हित दीर्घ *pmask)
अणु
	काष्ठा nvkm_device *device = disp->engine.subdev.device;
	*pmask = (nvkm_rd32(device, 0x610184) & 0x03000000) >> 24;
	वापस 2;
पूर्ण
