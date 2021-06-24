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

व्योम
gm200_sor_dp_drive(काष्ठा nvkm_ior *sor, पूर्णांक ln, पूर्णांक pc, पूर्णांक dc, पूर्णांक pe, पूर्णांक pu)
अणु
	काष्ठा nvkm_device *device = sor->disp->engine.subdev.device;
	स्थिर u32  loff = nv50_sor_link(sor);
	स्थिर u32 shअगरt = sor->func->dp.lanes[ln] * 8;
	u32 data[4];

	pu &= 0x0f;

	data[0] = nvkm_rd32(device, 0x61c118 + loff) & ~(0x000000ff << shअगरt);
	data[1] = nvkm_rd32(device, 0x61c120 + loff) & ~(0x000000ff << shअगरt);
	data[2] = nvkm_rd32(device, 0x61c130 + loff);
	अगर ((data[2] & 0x00000f00) < (pu << 8) || ln == 0)
		data[2] = (data[2] & ~0x00000f00) | (pu << 8);
	nvkm_wr32(device, 0x61c118 + loff, data[0] | (dc << shअगरt));
	nvkm_wr32(device, 0x61c120 + loff, data[1] | (pe << shअगरt));
	nvkm_wr32(device, 0x61c130 + loff, data[2]);
	data[3] = nvkm_rd32(device, 0x61c13c + loff) & ~(0x000000ff << shअगरt);
	nvkm_wr32(device, 0x61c13c + loff, data[3] | (pc << shअगरt));
पूर्ण

व्योम
gm200_sor_route_set(काष्ठा nvkm_outp *outp, काष्ठा nvkm_ior *ior)
अणु
	काष्ठा nvkm_device *device = outp->disp->engine.subdev.device;
	स्थिर u32 moff = __ffs(outp->info.or) * 0x100;
	स्थिर u32  sor = ior ? ior->id + 1 : 0;
	u32 link = ior ? (ior->asy.link == 2) : 0;

	अगर (outp->info.sorconf.link & 1) अणु
		nvkm_mask(device, 0x612308 + moff, 0x0000001f, link << 4 | sor);
		link++;
	पूर्ण

	अगर (outp->info.sorconf.link & 2)
		nvkm_mask(device, 0x612388 + moff, 0x0000001f, link << 4 | sor);
पूर्ण

पूर्णांक
gm200_sor_route_get(काष्ठा nvkm_outp *outp, पूर्णांक *link)
अणु
	काष्ठा nvkm_device *device = outp->disp->engine.subdev.device;
	स्थिर पूर्णांक sublinks = outp->info.sorconf.link;
	पूर्णांक lnk[2], sor[2], m, s;

	क्रम (*link = 0, m = __ffs(outp->info.or) * 2, s = 0; s < 2; m++, s++) अणु
		अगर (sublinks & BIT(s)) अणु
			u32 data = nvkm_rd32(device, 0x612308 + (m * 0x80));
			lnk[s] = (data & 0x00000010) >> 4;
			sor[s] = (data & 0x0000000f);
			अगर (!sor[s])
				वापस -1;
			*link |= lnk[s];
		पूर्ण
	पूर्ण

	अगर (sublinks == 3) अणु
		अगर (sor[0] != sor[1] || WARN_ON(lnk[0] || !lnk[1]))
			वापस -1;
	पूर्ण

	वापस ((sublinks & 1) ? sor[0] : sor[1]) - 1;
पूर्ण

अटल स्थिर काष्ठा nvkm_ior_func
gm200_sor_hda = अणु
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
gm200_sor = अणु
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
gm200_sor_new(काष्ठा nvkm_disp *disp, पूर्णांक id)
अणु
	काष्ठा nvkm_device *device = disp->engine.subdev.device;
	u32 hda;

	अगर (!((hda = nvkm_rd32(device, 0x08a15c)) & 0x40000000))
		hda = nvkm_rd32(device, 0x101034);

	अगर (hda & BIT(id))
		वापस nvkm_ior_new_(&gm200_sor_hda, disp, SOR, id);
	वापस nvkm_ior_new_(&gm200_sor, disp, SOR, id);
पूर्ण
