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
gf119_sor_dp_watermark(काष्ठा nvkm_ior *sor, पूर्णांक head, u8 watermark)
अणु
	काष्ठा nvkm_device *device = sor->disp->engine.subdev.device;
	स्थिर u32 hoff = head * 0x800;
	nvkm_mask(device, 0x616610 + hoff, 0x0800003f, 0x08000000 | watermark);
पूर्ण

व्योम
gf119_sor_dp_audio_sym(काष्ठा nvkm_ior *sor, पूर्णांक head, u16 h, u32 v)
अणु
	काष्ठा nvkm_device *device = sor->disp->engine.subdev.device;
	स्थिर u32 hoff = head * 0x800;
	nvkm_mask(device, 0x616620 + hoff, 0x0000ffff, h);
	nvkm_mask(device, 0x616624 + hoff, 0x00ffffff, v);
पूर्ण

व्योम
gf119_sor_dp_audio(काष्ठा nvkm_ior *sor, पूर्णांक head, bool enable)
अणु
	काष्ठा nvkm_device *device = sor->disp->engine.subdev.device;
	स्थिर u32 hoff = 0x800 * head;
	स्थिर u32 data = 0x80000000 | (0x00000001 * enable);
	स्थिर u32 mask = 0x8000000d;
	nvkm_mask(device, 0x616618 + hoff, mask, data);
	nvkm_msec(device, 2000,
		अगर (!(nvkm_rd32(device, 0x616618 + hoff) & 0x80000000))
			अवरोध;
	);
पूर्ण

व्योम
gf119_sor_dp_vcpi(काष्ठा nvkm_ior *sor, पूर्णांक head,
		  u8 slot, u8 slot_nr, u16 pbn, u16 aligned)
अणु
	काष्ठा nvkm_device *device = sor->disp->engine.subdev.device;
	स्थिर u32 hoff = head * 0x800;

	nvkm_mask(device, 0x616588 + hoff, 0x00003f3f, (slot_nr << 8) | slot);
	nvkm_mask(device, 0x61658c + hoff, 0xffffffff, (aligned << 16) | pbn);
पूर्ण

व्योम
gf119_sor_dp_drive(काष्ठा nvkm_ior *sor, पूर्णांक ln, पूर्णांक pc, पूर्णांक dc, पूर्णांक pe, पूर्णांक pu)
अणु
	काष्ठा nvkm_device *device = sor->disp->engine.subdev.device;
	स्थिर u32  loff = nv50_sor_link(sor);
	स्थिर u32 shअगरt = sor->func->dp.lanes[ln] * 8;
	u32 data[4];

	data[0] = nvkm_rd32(device, 0x61c118 + loff) & ~(0x000000ff << shअगरt);
	data[1] = nvkm_rd32(device, 0x61c120 + loff) & ~(0x000000ff << shअगरt);
	data[2] = nvkm_rd32(device, 0x61c130 + loff);
	अगर ((data[2] & 0x0000ff00) < (pu << 8) || ln == 0)
		data[2] = (data[2] & ~0x0000ff00) | (pu << 8);
	nvkm_wr32(device, 0x61c118 + loff, data[0] | (dc << shअगरt));
	nvkm_wr32(device, 0x61c120 + loff, data[1] | (pe << shअगरt));
	nvkm_wr32(device, 0x61c130 + loff, data[2]);
	data[3] = nvkm_rd32(device, 0x61c13c + loff) & ~(0x000000ff << shअगरt);
	nvkm_wr32(device, 0x61c13c + loff, data[3] | (pc << shअगरt));
पूर्ण

व्योम
gf119_sor_dp_pattern(काष्ठा nvkm_ior *sor, पूर्णांक pattern)
अणु
	काष्ठा nvkm_device *device = sor->disp->engine.subdev.device;
	स्थिर u32 soff = nv50_ior_base(sor);
	nvkm_mask(device, 0x61c110 + soff, 0x0f0f0f0f, 0x01010101 * pattern);
पूर्ण

पूर्णांक
gf119_sor_dp_links(काष्ठा nvkm_ior *sor, काष्ठा nvkm_i2c_aux *aux)
अणु
	काष्ठा nvkm_device *device = sor->disp->engine.subdev.device;
	स्थिर u32 soff = nv50_ior_base(sor);
	स्थिर u32 loff = nv50_sor_link(sor);
	u32 dpctrl = 0x00000000;
	u32 clksor = 0x00000000;

	clksor |= sor->dp.bw << 18;
	dpctrl |= ((1 << sor->dp.nr) - 1) << 16;
	अगर (sor->dp.mst)
		dpctrl |= 0x40000000;
	अगर (sor->dp.ef)
		dpctrl |= 0x00004000;

	nvkm_mask(device, 0x612300 + soff, 0x007c0000, clksor);
	nvkm_mask(device, 0x61c10c + loff, 0x401f4000, dpctrl);
	वापस 0;
पूर्ण

व्योम
gf119_sor_घड़ी(काष्ठा nvkm_ior *sor)
अणु
	काष्ठा nvkm_device *device = sor->disp->engine.subdev.device;
	स्थिर u32 soff = nv50_ior_base(sor);
	u32 भाग1 = sor->asy.link == 3;
	u32 भाग2 = sor->asy.link == 3;
	अगर (sor->asy.proto == TMDS) अणु
		स्थिर u32 speed = sor->पंचांगds.high_speed ? 0x14 : 0x0a;
		nvkm_mask(device, 0x612300 + soff, 0x007c0000, speed << 18);
		अगर (sor->पंचांगds.high_speed)
			भाग2 = 1;
	पूर्ण
	nvkm_mask(device, 0x612300 + soff, 0x00000707, (भाग2 << 8) | भाग1);
पूर्ण

व्योम
gf119_sor_state(काष्ठा nvkm_ior *sor, काष्ठा nvkm_ior_state *state)
अणु
	काष्ठा nvkm_device *device = sor->disp->engine.subdev.device;
	स्थिर u32 coff = (state == &sor->asy) * 0x20000 + sor->id * 0x20;
	u32 ctrl = nvkm_rd32(device, 0x640200 + coff);

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

	state->head = ctrl & 0x0000000f;
पूर्ण

अटल स्थिर काष्ठा nvkm_ior_func
gf119_sor = अणु
	.state = gf119_sor_state,
	.घातer = nv50_sor_घातer,
	.घड़ी = gf119_sor_घड़ी,
	.hdmi = अणु
		.ctrl = gf119_hdmi_ctrl,
	पूर्ण,
	.dp = अणु
		.lanes = अणु 2, 1, 0, 3 पूर्ण,
		.links = gf119_sor_dp_links,
		.घातer = g94_sor_dp_घातer,
		.pattern = gf119_sor_dp_pattern,
		.drive = gf119_sor_dp_drive,
		.vcpi = gf119_sor_dp_vcpi,
		.audio = gf119_sor_dp_audio,
		.audio_sym = gf119_sor_dp_audio_sym,
		.watermark = gf119_sor_dp_watermark,
	पूर्ण,
	.hda = अणु
		.hpd = gf119_hda_hpd,
		.eld = gf119_hda_eld,
		.device_entry = gf119_hda_device_entry,
	पूर्ण,
पूर्ण;

पूर्णांक
gf119_sor_new(काष्ठा nvkm_disp *disp, पूर्णांक id)
अणु
	वापस nvkm_ior_new_(&gf119_sor, disp, SOR, id);
पूर्ण

पूर्णांक
gf119_sor_cnt(काष्ठा nvkm_disp *disp, अचिन्हित दीर्घ *pmask)
अणु
	काष्ठा nvkm_device *device = disp->engine.subdev.device;
	*pmask = (nvkm_rd32(device, 0x612004) & 0x0000ff00) >> 8;
	वापस 8;
पूर्ण
