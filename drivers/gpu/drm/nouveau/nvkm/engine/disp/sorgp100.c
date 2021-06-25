<शैली गुरु>
/*
 * Copyright 2020 Red Hat Inc.
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

अटल स्थिर काष्ठा nvkm_ior_func
gp100_sor_hda = अणु
	.route = अणु
		.get = gm200_sor_route_get,
		.set = gm200_sor_route_set,
	पूर्ण,
	.state = gf119_sor_state,
	.घातer = nv50_sor_घातer,
	.घड़ी = gf119_sor_घड़ी,
	.hdmi = अणु
		.ctrl = gk104_hdmi_ctrl,
		.scdc = gm200_hdmi_scdc,
	पूर्ण,
	.dp = अणु
		.lanes = अणु 0, 1, 2, 3 पूर्ण,
		.links = gf119_sor_dp_links,
		.घातer = g94_sor_dp_घातer,
		.pattern = gm107_sor_dp_pattern,
		.drive = gm200_sor_dp_drive,
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

अटल स्थिर काष्ठा nvkm_ior_func
gp100_sor = अणु
	.route = अणु
		.get = gm200_sor_route_get,
		.set = gm200_sor_route_set,
	पूर्ण,
	.state = gf119_sor_state,
	.घातer = nv50_sor_घातer,
	.घड़ी = gf119_sor_घड़ी,
	.hdmi = अणु
		.ctrl = gk104_hdmi_ctrl,
		.scdc = gm200_hdmi_scdc,
	पूर्ण,
	.dp = अणु
		.lanes = अणु 0, 1, 2, 3 पूर्ण,
		.links = gf119_sor_dp_links,
		.घातer = g94_sor_dp_घातer,
		.pattern = gm107_sor_dp_pattern,
		.drive = gm200_sor_dp_drive,
		.vcpi = gf119_sor_dp_vcpi,
		.audio = gf119_sor_dp_audio,
		.audio_sym = gf119_sor_dp_audio_sym,
		.watermark = gf119_sor_dp_watermark,
	पूर्ण,
पूर्ण;

पूर्णांक
gp100_sor_new(काष्ठा nvkm_disp *disp, पूर्णांक id)
अणु
	काष्ठा nvkm_device *device = disp->engine.subdev.device;
	u32 hda;

	अगर (!((hda = nvkm_rd32(device, 0x08a15c)) & 0x40000000))
		hda = nvkm_rd32(device, 0x10ebb0) >> 8;

	अगर (hda & BIT(id))
		वापस nvkm_ior_new_(&gp100_sor_hda, disp, SOR, id);
	वापस nvkm_ior_new_(&gp100_sor, disp, SOR, id);
पूर्ण
