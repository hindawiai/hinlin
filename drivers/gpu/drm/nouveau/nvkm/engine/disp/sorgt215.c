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

#समावेश <subdev/समयr.h>

व्योम
gt215_sor_dp_audio(काष्ठा nvkm_ior *sor, पूर्णांक head, bool enable)
अणु
	काष्ठा nvkm_device *device = sor->disp->engine.subdev.device;
	स्थिर u32 soff = nv50_ior_base(sor);
	स्थिर u32 data = 0x80000000 | (0x00000001 * enable);
	स्थिर u32 mask = 0x8000000d;
	nvkm_mask(device, 0x61c1e0 + soff, mask, data);
	nvkm_msec(device, 2000,
		अगर (!(nvkm_rd32(device, 0x61c1e0 + soff) & 0x80000000))
			अवरोध;
	);
पूर्ण

अटल स्थिर काष्ठा nvkm_ior_func
gt215_sor = अणु
	.state = g94_sor_state,
	.घातer = nv50_sor_घातer,
	.घड़ी = nv50_sor_घड़ी,
	.hdmi = अणु
		.ctrl = gt215_hdmi_ctrl,
	पूर्ण,
	.dp = अणु
		.lanes = अणु 2, 1, 0, 3 पूर्ण,
		.links = g94_sor_dp_links,
		.घातer = g94_sor_dp_घातer,
		.pattern = g94_sor_dp_pattern,
		.drive = g94_sor_dp_drive,
		.audio = gt215_sor_dp_audio,
		.audio_sym = g94_sor_dp_audio_sym,
		.activesym = g94_sor_dp_activesym,
		.watermark = g94_sor_dp_watermark,
	पूर्ण,
	.hda = अणु
		.hpd = gt215_hda_hpd,
		.eld = gt215_hda_eld,
	पूर्ण,
पूर्ण;

पूर्णांक
gt215_sor_new(काष्ठा nvkm_disp *disp, पूर्णांक id)
अणु
	वापस nvkm_ior_new_(&gt215_sor, disp, SOR, id);
पूर्ण
