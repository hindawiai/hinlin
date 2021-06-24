<शैली गुरु>
/*
 * Copyright 2021 Red Hat Inc.
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

अटल पूर्णांक
ga102_sor_dp_links(काष्ठा nvkm_ior *sor, काष्ठा nvkm_i2c_aux *aux)
अणु
	काष्ठा nvkm_device *device = sor->disp->engine.subdev.device;
	स्थिर u32 soff = nv50_ior_base(sor);
	स्थिर u32 loff = nv50_sor_link(sor);
	u32 dpctrl = 0x00000000;
	u32 clksor = 0x00000000;

	चयन (sor->dp.bw) अणु
	हाल 0x06: clksor |= 0x00000000; अवरोध;
	हाल 0x0a: clksor |= 0x00040000; अवरोध;
	हाल 0x14: clksor |= 0x00080000; अवरोध;
	हाल 0x1e: clksor |= 0x000c0000; अवरोध;
	शेष:
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	dpctrl |= ((1 << sor->dp.nr) - 1) << 16;
	अगर (sor->dp.mst)
		dpctrl |= 0x40000000;
	अगर (sor->dp.ef)
		dpctrl |= 0x00004000;

	nvkm_mask(device, 0x612300 + soff, 0x007c0000, clksor);

	/*XXX*/
	nvkm_msec(device, 40, NVKM_DELAY);
	nvkm_mask(device, 0x612300 + soff, 0x00030000, 0x00010000);
	nvkm_mask(device, 0x61c10c + loff, 0x00000003, 0x00000001);

	nvkm_mask(device, 0x61c10c + loff, 0x401f4000, dpctrl);
	वापस 0;
पूर्ण

अटल व्योम
ga102_sor_घड़ी(काष्ठा nvkm_ior *sor)
अणु
	काष्ठा nvkm_device *device = sor->disp->engine.subdev.device;
	u32 भाग2 = 0;
	अगर (sor->asy.proto == TMDS) अणु
		अगर (sor->पंचांगds.high_speed)
			भाग2 = 1;
	पूर्ण
	nvkm_wr32(device, 0x00ec08 + (sor->id * 0x10), 0x00000000);
	nvkm_wr32(device, 0x00ec04 + (sor->id * 0x10), भाग2);
पूर्ण

अटल स्थिर काष्ठा nvkm_ior_func
ga102_sor_hda = अणु
	.route = अणु
		.get = gm200_sor_route_get,
		.set = gm200_sor_route_set,
	पूर्ण,
	.state = gv100_sor_state,
	.घातer = nv50_sor_घातer,
	.घड़ी = ga102_sor_घड़ी,
	.hdmi = अणु
		.ctrl = gv100_hdmi_ctrl,
		.scdc = gm200_hdmi_scdc,
	पूर्ण,
	.dp = अणु
		.lanes = अणु 0, 1, 2, 3 पूर्ण,
		.links = ga102_sor_dp_links,
		.घातer = g94_sor_dp_घातer,
		.pattern = gm107_sor_dp_pattern,
		.drive = gm200_sor_dp_drive,
		.vcpi = tu102_sor_dp_vcpi,
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
ga102_sor = अणु
	.route = अणु
		.get = gm200_sor_route_get,
		.set = gm200_sor_route_set,
	पूर्ण,
	.state = gv100_sor_state,
	.घातer = nv50_sor_घातer,
	.घड़ी = ga102_sor_घड़ी,
	.hdmi = अणु
		.ctrl = gv100_hdmi_ctrl,
		.scdc = gm200_hdmi_scdc,
	पूर्ण,
	.dp = अणु
		.lanes = अणु 0, 1, 2, 3 पूर्ण,
		.links = ga102_sor_dp_links,
		.घातer = g94_sor_dp_घातer,
		.pattern = gm107_sor_dp_pattern,
		.drive = gm200_sor_dp_drive,
		.vcpi = tu102_sor_dp_vcpi,
		.audio = gv100_sor_dp_audio,
		.audio_sym = gv100_sor_dp_audio_sym,
		.watermark = gv100_sor_dp_watermark,
	पूर्ण,
पूर्ण;

पूर्णांक
ga102_sor_new(काष्ठा nvkm_disp *disp, पूर्णांक id)
अणु
	काष्ठा nvkm_device *device = disp->engine.subdev.device;
	u32 hda = nvkm_rd32(device, 0x08a15c);
	अगर (hda & BIT(id))
		वापस nvkm_ior_new_(&ga102_sor_hda, disp, SOR, id);
	वापस nvkm_ior_new_(&ga102_sor, disp, SOR, id);
पूर्ण
