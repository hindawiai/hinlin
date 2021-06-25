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
#समावेश "head.h"

#समावेश <subdev/i2c.h>
#समावेश <subdev/समयr.h>

अटल व्योम
nv50_pior_घड़ी(काष्ठा nvkm_ior *pior)
अणु
	काष्ठा nvkm_device *device = pior->disp->engine.subdev.device;
	स्थिर u32 poff = nv50_ior_base(pior);
	nvkm_mask(device, 0x614380 + poff, 0x00000707, 0x00000001);
पूर्ण

अटल पूर्णांक
nv50_pior_dp_links(काष्ठा nvkm_ior *pior, काष्ठा nvkm_i2c_aux *aux)
अणु
	पूर्णांक ret = nvkm_i2c_aux_lnk_ctl(aux, pior->dp.nr, pior->dp.bw,
					    pior->dp.ef);
	अगर (ret)
		वापस ret;
	वापस 1;
पूर्ण

अटल व्योम
nv50_pior_घातer_रुको(काष्ठा nvkm_device *device, u32 poff)
अणु
	nvkm_msec(device, 2000,
		अगर (!(nvkm_rd32(device, 0x61e004 + poff) & 0x80000000))
			अवरोध;
	);
पूर्ण

अटल व्योम
nv50_pior_घातer(काष्ठा nvkm_ior *pior, bool normal, bool pu,
	       bool data, bool vsync, bool hsync)
अणु
	काष्ठा nvkm_device *device = pior->disp->engine.subdev.device;
	स्थिर u32  poff = nv50_ior_base(pior);
	स्थिर u32 shअगरt = normal ? 0 : 16;
	स्थिर u32 state = 0x80000000 | (0x00000001 * !!pu) << shअगरt;
	स्थिर u32 field = 0x80000000 | (0x00000101 << shअगरt);

	nv50_pior_घातer_रुको(device, poff);
	nvkm_mask(device, 0x61e004 + poff, field, state);
	nv50_pior_घातer_रुको(device, poff);
पूर्ण

व्योम
nv50_pior_depth(काष्ठा nvkm_ior *ior, काष्ठा nvkm_ior_state *state, u32 ctrl)
अणु
	/* GF119 moves this inक्रमmation to per-head methods, which is
	 * a lot more convenient, and where our shared code expect it.
	 */
	अगर (state->head && state == &ior->asy) अणु
		काष्ठा nvkm_head *head =
			nvkm_head_find(ior->disp, __ffs(state->head));
		अगर (!WARN_ON(!head)) अणु
			काष्ठा nvkm_head_state *state = &head->asy;
			चयन ((ctrl & 0x000f0000) >> 16) अणु
			हाल 6: state->or.depth = 30; अवरोध;
			हाल 5: state->or.depth = 24; अवरोध;
			हाल 2: state->or.depth = 18; अवरोध;
			हाल 0: state->or.depth = 18; अवरोध; /*XXX*/
			शेष:
				state->or.depth = 18;
				WARN_ON(1);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
nv50_pior_state(काष्ठा nvkm_ior *pior, काष्ठा nvkm_ior_state *state)
अणु
	काष्ठा nvkm_device *device = pior->disp->engine.subdev.device;
	स्थिर u32 coff = pior->id * 8 + (state == &pior->arm) * 4;
	u32 ctrl = nvkm_rd32(device, 0x610b80 + coff);

	state->proto_evo = (ctrl & 0x00000f00) >> 8;
	state->rgभाग = 1;
	चयन (state->proto_evo) अणु
	हाल 0: state->proto = TMDS; अवरोध;
	शेष:
		state->proto = UNKNOWN;
		अवरोध;
	पूर्ण

	state->head = ctrl & 0x00000003;
	nv50_pior_depth(pior, state, ctrl);
पूर्ण

अटल स्थिर काष्ठा nvkm_ior_func
nv50_pior = अणु
	.state = nv50_pior_state,
	.घातer = nv50_pior_घातer,
	.घड़ी = nv50_pior_घड़ी,
	.dp = अणु
		.links = nv50_pior_dp_links,
	पूर्ण,
पूर्ण;

पूर्णांक
nv50_pior_new(काष्ठा nvkm_disp *disp, पूर्णांक id)
अणु
	वापस nvkm_ior_new_(&nv50_pior, disp, PIOR, id);
पूर्ण

पूर्णांक
nv50_pior_cnt(काष्ठा nvkm_disp *disp, अचिन्हित दीर्घ *pmask)
अणु
	काष्ठा nvkm_device *device = disp->engine.subdev.device;
	*pmask = (nvkm_rd32(device, 0x610184) & 0x70000000) >> 28;
	वापस 3;
पूर्ण
