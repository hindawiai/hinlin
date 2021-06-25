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
g94_sor_dp_watermark(काष्ठा nvkm_ior *sor, पूर्णांक head, u8 watermark)
अणु
	काष्ठा nvkm_device *device = sor->disp->engine.subdev.device;
	स्थिर u32 loff = nv50_sor_link(sor);
	nvkm_mask(device, 0x61c128 + loff, 0x0000003f, watermark);
पूर्ण

व्योम
g94_sor_dp_activesym(काष्ठा nvkm_ior *sor, पूर्णांक head,
		     u8 TU, u8 VTUa, u8 VTUf, u8 VTUi)
अणु
	काष्ठा nvkm_device *device = sor->disp->engine.subdev.device;
	स्थिर u32 loff = nv50_sor_link(sor);
	nvkm_mask(device, 0x61c10c + loff, 0x000001fc, TU << 2);
	nvkm_mask(device, 0x61c128 + loff, 0x010f7f00, VTUa << 24 |
						       VTUf << 16 |
						       VTUi << 8);
पूर्ण

व्योम
g94_sor_dp_audio_sym(काष्ठा nvkm_ior *sor, पूर्णांक head, u16 h, u32 v)
अणु
	काष्ठा nvkm_device *device = sor->disp->engine.subdev.device;
	स्थिर u32 soff = nv50_ior_base(sor);
	nvkm_mask(device, 0x61c1e8 + soff, 0x0000ffff, h);
	nvkm_mask(device, 0x61c1ec + soff, 0x00ffffff, v);
पूर्ण

व्योम
g94_sor_dp_drive(काष्ठा nvkm_ior *sor, पूर्णांक ln, पूर्णांक pc, पूर्णांक dc, पूर्णांक pe, पूर्णांक pu)
अणु
	काष्ठा nvkm_device *device = sor->disp->engine.subdev.device;
	स्थिर u32  loff = nv50_sor_link(sor);
	स्थिर u32 shअगरt = sor->func->dp.lanes[ln] * 8;
	u32 data[3];

	data[0] = nvkm_rd32(device, 0x61c118 + loff) & ~(0x000000ff << shअगरt);
	data[1] = nvkm_rd32(device, 0x61c120 + loff) & ~(0x000000ff << shअगरt);
	data[2] = nvkm_rd32(device, 0x61c130 + loff);
	अगर ((data[2] & 0x0000ff00) < (pu << 8) || ln == 0)
		data[2] = (data[2] & ~0x0000ff00) | (pu << 8);
	nvkm_wr32(device, 0x61c118 + loff, data[0] | (dc << shअगरt));
	nvkm_wr32(device, 0x61c120 + loff, data[1] | (pe << shअगरt));
	nvkm_wr32(device, 0x61c130 + loff, data[2]);
पूर्ण

व्योम
g94_sor_dp_pattern(काष्ठा nvkm_ior *sor, पूर्णांक pattern)
अणु
	काष्ठा nvkm_device *device = sor->disp->engine.subdev.device;
	स्थिर u32 loff = nv50_sor_link(sor);
	nvkm_mask(device, 0x61c10c + loff, 0x0f000000, pattern << 24);
पूर्ण

व्योम
g94_sor_dp_घातer(काष्ठा nvkm_ior *sor, पूर्णांक nr)
अणु
	काष्ठा nvkm_device *device = sor->disp->engine.subdev.device;
	स्थिर u32 soff = nv50_ior_base(sor);
	स्थिर u32 loff = nv50_sor_link(sor);
	u32 mask = 0, i;

	क्रम (i = 0; i < nr; i++)
		mask |= 1 << sor->func->dp.lanes[i];

	nvkm_mask(device, 0x61c130 + loff, 0x0000000f, mask);
	nvkm_mask(device, 0x61c034 + soff, 0x80000000, 0x80000000);
	nvkm_msec(device, 2000,
		अगर (!(nvkm_rd32(device, 0x61c034 + soff) & 0x80000000))
			अवरोध;
	);
पूर्ण

पूर्णांक
g94_sor_dp_links(काष्ठा nvkm_ior *sor, काष्ठा nvkm_i2c_aux *aux)
अणु
	काष्ठा nvkm_device *device = sor->disp->engine.subdev.device;
	स्थिर u32 soff = nv50_ior_base(sor);
	स्थिर u32 loff = nv50_sor_link(sor);
	u32 dpctrl = 0x00000000;
	u32 clksor = 0x00000000;

	dpctrl |= ((1 << sor->dp.nr) - 1) << 16;
	अगर (sor->dp.ef)
		dpctrl |= 0x00004000;
	अगर (sor->dp.bw > 0x06)
		clksor |= 0x00040000;

	nvkm_mask(device, 0x614300 + soff, 0x000c0000, clksor);
	nvkm_mask(device, 0x61c10c + loff, 0x001f4000, dpctrl);
	वापस 0;
पूर्ण

अटल bool
g94_sor_war_needed(काष्ठा nvkm_ior *sor)
अणु
	काष्ठा nvkm_device *device = sor->disp->engine.subdev.device;
	स्थिर u32 soff = nv50_ior_base(sor);
	अगर (sor->asy.proto == TMDS) अणु
		चयन (nvkm_rd32(device, 0x614300 + soff) & 0x00030000) अणु
		हाल 0x00000000:
		हाल 0x00030000:
			वापस true;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम
g94_sor_war_update_sppll1(काष्ठा nvkm_disp *disp)
अणु
	काष्ठा nvkm_device *device = disp->engine.subdev.device;
	काष्ठा nvkm_ior *ior;
	bool used = false;
	u32 clksor;

	list_क्रम_each_entry(ior, &disp->ior, head) अणु
		अगर (ior->type != SOR)
			जारी;

		clksor = nvkm_rd32(device, 0x614300 + nv50_ior_base(ior));
		चयन (clksor & 0x03000000) अणु
		हाल 0x02000000:
		हाल 0x03000000:
			used = true;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (used)
		वापस;

	nvkm_mask(device, 0x00e840, 0x80000000, 0x00000000);
पूर्ण

अटल व्योम
g94_sor_war_3(काष्ठा nvkm_ior *sor)
अणु
	काष्ठा nvkm_device *device = sor->disp->engine.subdev.device;
	स्थिर u32 soff = nv50_ior_base(sor);
	u32 sorpwr;

	अगर (!g94_sor_war_needed(sor))
		वापस;

	sorpwr = nvkm_rd32(device, 0x61c004 + soff);
	अगर (sorpwr & 0x00000001) अणु
		u32 seqctl = nvkm_rd32(device, 0x61c030 + soff);
		u32  pd_pc = (seqctl & 0x00000f00) >> 8;
		u32  pu_pc =  seqctl & 0x0000000f;

		nvkm_wr32(device, 0x61c040 + soff + pd_pc * 4, 0x1f008000);

		nvkm_msec(device, 2000,
			अगर (!(nvkm_rd32(device, 0x61c030 + soff) & 0x10000000))
				अवरोध;
		);
		nvkm_mask(device, 0x61c004 + soff, 0x80000001, 0x80000000);
		nvkm_msec(device, 2000,
			अगर (!(nvkm_rd32(device, 0x61c030 + soff) & 0x10000000))
				अवरोध;
		);

		nvkm_wr32(device, 0x61c040 + soff + pd_pc * 4, 0x00002000);
		nvkm_wr32(device, 0x61c040 + soff + pu_pc * 4, 0x1f000000);
	पूर्ण

	nvkm_mask(device, 0x61c10c + soff, 0x00000001, 0x00000000);
	nvkm_mask(device, 0x614300 + soff, 0x03000000, 0x00000000);

	अगर (sorpwr & 0x00000001) अणु
		nvkm_mask(device, 0x61c004 + soff, 0x80000001, 0x80000001);
	पूर्ण

	g94_sor_war_update_sppll1(sor->disp);
पूर्ण

अटल व्योम
g94_sor_war_2(काष्ठा nvkm_ior *sor)
अणु
	काष्ठा nvkm_device *device = sor->disp->engine.subdev.device;
	स्थिर u32 soff = nv50_ior_base(sor);

	अगर (!g94_sor_war_needed(sor))
		वापस;

	nvkm_mask(device, 0x00e840, 0x80000000, 0x80000000);
	nvkm_mask(device, 0x614300 + soff, 0x03000000, 0x03000000);
	nvkm_mask(device, 0x61c10c + soff, 0x00000001, 0x00000001);

	nvkm_mask(device, 0x61c00c + soff, 0x0f000000, 0x00000000);
	nvkm_mask(device, 0x61c008 + soff, 0xff000000, 0x14000000);
	nvkm_usec(device, 400, NVKM_DELAY);
	nvkm_mask(device, 0x61c008 + soff, 0xff000000, 0x00000000);
	nvkm_mask(device, 0x61c00c + soff, 0x0f000000, 0x01000000);

	अगर (nvkm_rd32(device, 0x61c004 + soff) & 0x00000001) अणु
		u32 seqctl = nvkm_rd32(device, 0x61c030 + soff);
		u32  pu_pc = seqctl & 0x0000000f;
		nvkm_wr32(device, 0x61c040 + soff + pu_pc * 4, 0x1f008000);
	पूर्ण
पूर्ण

व्योम
g94_sor_state(काष्ठा nvkm_ior *sor, काष्ठा nvkm_ior_state *state)
अणु
	काष्ठा nvkm_device *device = sor->disp->engine.subdev.device;
	स्थिर u32 coff = sor->id * 8 + (state == &sor->arm) * 4;
	u32 ctrl = nvkm_rd32(device, 0x610794 + coff);

	state->proto_evo = (ctrl & 0x00000f00) >> 8;
	चयन (state->proto_evo) अणु
	हाल 0: state->proto = LVDS; state->link = 1; अवरोध;
	हाल 1: state->proto = TMDS; state->link = 1; अवरोध;
	हाल 2: state->proto = TMDS; state->link = 2; अवरोध;
	हाल 5: state->proto = TMDS; state->link = 3; अवरोध;
	हाल 8: state->proto =   DP; state->link = 1; अवरोध;
	हाल 9: state->proto =   DP; state->link = 2; अवरोध;
	शेष:
		state->proto = UNKNOWN;
		अवरोध;
	पूर्ण

	state->head = ctrl & 0x00000003;
	nv50_pior_depth(sor, state, ctrl);
पूर्ण

अटल स्थिर काष्ठा nvkm_ior_func
g94_sor = अणु
	.state = g94_sor_state,
	.घातer = nv50_sor_घातer,
	.घड़ी = nv50_sor_घड़ी,
	.war_2 = g94_sor_war_2,
	.war_3 = g94_sor_war_3,
	.dp = अणु
		.lanes = अणु 2, 1, 0, 3पूर्ण,
		.links = g94_sor_dp_links,
		.घातer = g94_sor_dp_घातer,
		.pattern = g94_sor_dp_pattern,
		.drive = g94_sor_dp_drive,
		.audio_sym = g94_sor_dp_audio_sym,
		.activesym = g94_sor_dp_activesym,
		.watermark = g94_sor_dp_watermark,
	पूर्ण,
पूर्ण;

पूर्णांक
g94_sor_new(काष्ठा nvkm_disp *disp, पूर्णांक id)
अणु
	वापस nvkm_ior_new_(&g94_sor, disp, SOR, id);
पूर्ण

पूर्णांक
g94_sor_cnt(काष्ठा nvkm_disp *disp, अचिन्हित दीर्घ *pmask)
अणु
	काष्ठा nvkm_device *device = disp->engine.subdev.device;
	*pmask = (nvkm_rd32(device, 0x610184) & 0x0f000000) >> 24;
	वापस 4;
पूर्ण
