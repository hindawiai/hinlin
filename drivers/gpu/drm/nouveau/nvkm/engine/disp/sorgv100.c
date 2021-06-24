<शैली गुरु>
/*
 * Copyright 2018 Red Hat Inc.
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

#समावेश <subdev/समयr.h>

व्योम
gv100_sor_dp_watermark(काष्ठा nvkm_ior *sor, पूर्णांक head, u8 watermark)
अणु
	काष्ठा nvkm_device *device = sor->disp->engine.subdev.device;
	स्थिर u32 hoff = head * 0x800;
	nvkm_mask(device, 0x616550 + hoff, 0x0c00003f, 0x08000000 | watermark);
पूर्ण

व्योम
gv100_sor_dp_audio_sym(काष्ठा nvkm_ior *sor, पूर्णांक head, u16 h, u32 v)
अणु
	काष्ठा nvkm_device *device = sor->disp->engine.subdev.device;
	स्थिर u32 hoff = head * 0x800;
	nvkm_mask(device, 0x616568 + hoff, 0x0000ffff, h);
	nvkm_mask(device, 0x61656c + hoff, 0x00ffffff, v);
पूर्ण

व्योम
gv100_sor_dp_audio(काष्ठा nvkm_ior *sor, पूर्णांक head, bool enable)
अणु
	काष्ठा nvkm_device *device = sor->disp->engine.subdev.device;
	स्थिर u32 hoff = 0x800 * head;
	स्थिर u32 data = 0x80000000 | (0x00000001 * enable);
	स्थिर u32 mask = 0x8000000d;
	nvkm_mask(device, 0x616560 + hoff, mask, data);
	nvkm_msec(device, 2000,
		अगर (!(nvkm_rd32(device, 0x616560 + hoff) & 0x80000000))
			अवरोध;
	);
पूर्ण

व्योम
gv100_sor_state(काष्ठा nvkm_ior *sor, काष्ठा nvkm_ior_state *state)
अणु
	काष्ठा nvkm_device *device = sor->disp->engine.subdev.device;
	स्थिर u32 coff = (state == &sor->arm) * 0x8000 + sor->id * 0x20;
	u32 ctrl = nvkm_rd32(device, 0x680300 + coff);

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

	state->head = ctrl & 0x000000ff;
पूर्ण

अटल स्थिर काष्ठा nvkm_ior_func
gv100_sor_hda = अणु
	.route = अणु
		.get = gm200_sor_route_get,
		.set = gm200_sor_route_set,
	पूर्ण,
	.state = gv100_sor_state,
	.घातer = nv50_sor_घातer,
	.घड़ी = gf119_sor_घड़ी,
	.hdmi = अणु
		.ctrl = gv100_hdmi_ctrl,
		.scdc = gm200_hdmi_scdc,
	पूर्ण,
	.dp = अणु
		.lanes = अणु 0, 1, 2, 3 पूर्ण,
		.links = gf119_sor_dp_links,
		.घातer = g94_sor_dp_घातer,
		.pattern = gm107_sor_dp_pattern,
		.drive = gm200_sor_dp_drive,
		.audio = gv100_sor_dp_audio,
		.audio_sym = gv100_sor_dp_audio_sym,
		.watermark = gv100_sor_dp_watermark,
	पूर्ण,
	.hda = अणु
		.hpd = gf119_hda_hpd,
		.eld = gf119_hda_eld,
		.device_entry = gv100_hda_device_entry,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_ior_func
gv100_sor = अणु
	.route = अणु
		.get = gm200_sor_route_get,
		.set = gm200_sor_route_set,
	पूर्ण,
	.state = gv100_sor_state,
	.घातer = nv50_sor_घातer,
	.घड़ी = gf119_sor_घड़ी,
	.hdmi = अणु
		.ctrl = gv100_hdmi_ctrl,
		.scdc = gm200_hdmi_scdc,
	पूर्ण,
	.dp = अणु
		.lanes = अणु 0, 1, 2, 3 पूर्ण,
		.links = gf119_sor_dp_links,
		.घातer = g94_sor_dp_घातer,
		.pattern = gm107_sor_dp_pattern,
		.drive = gm200_sor_dp_drive,
		.audio = gv100_sor_dp_audio,
		.audio_sym = gv100_sor_dp_audio_sym,
		.watermark = gv100_sor_dp_watermark,
	पूर्ण,
पूर्ण;

पूर्णांक
gv100_sor_new(काष्ठा nvkm_disp *disp, पूर्णांक id)
अणु
	काष्ठा nvkm_device *device = disp->engine.subdev.device;
	u32 hda;

	अगर (!((hda = nvkm_rd32(device, 0x08a15c)) & 0x40000000))
		hda = nvkm_rd32(device, 0x118fb0) >> 8;

	अगर (hda & BIT(id))
		वापस nvkm_ior_new_(&gv100_sor_hda, disp, SOR, id);
	वापस nvkm_ior_new_(&gv100_sor, disp, SOR, id);
पूर्ण

पूर्णांक
gv100_sor_cnt(काष्ठा nvkm_disp *disp, अचिन्हित दीर्घ *pmask)
अणु
	काष्ठा nvkm_device *device = disp->engine.subdev.device;
	*pmask = (nvkm_rd32(device, 0x610060) & 0x0000ff00) >> 8;
	वापस (nvkm_rd32(device, 0x610074) & 0x00000f00) >> 8;
पूर्ण
