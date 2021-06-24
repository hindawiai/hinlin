<शैली गुरु>
/*
 * Copyright 2014 Red Hat Inc.
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
#समावेश "hdmi.h"

व्योम
gk104_hdmi_ctrl(काष्ठा nvkm_ior *ior, पूर्णांक head, bool enable, u8 max_ac_packet,
		u8 rekey, u8 *avi, u8 avi_size, u8 *venकरोr, u8 venकरोr_size)
अणु
	काष्ठा nvkm_device *device = ior->disp->engine.subdev.device;
	स्थिर u32 ctrl = 0x40000000 * enable |
			 max_ac_packet << 16 |
			 rekey;
	स्थिर u32 hoff = head * 0x800;
	स्थिर u32 hdmi = head * 0x400;
	काष्ठा packed_hdmi_infoframe avi_infoframe;
	काष्ठा packed_hdmi_infoframe venकरोr_infoframe;

	pack_hdmi_infoframe(&avi_infoframe, avi, avi_size);
	pack_hdmi_infoframe(&venकरोr_infoframe, venकरोr, venकरोr_size);

	अगर (!(ctrl & 0x40000000)) अणु
		nvkm_mask(device, 0x616798 + hoff, 0x40000000, 0x00000000);
		nvkm_mask(device, 0x690100 + hdmi, 0x00000001, 0x00000000);
		nvkm_mask(device, 0x6900c0 + hdmi, 0x00000001, 0x00000000);
		nvkm_mask(device, 0x690000 + hdmi, 0x00000001, 0x00000000);
		वापस;
	पूर्ण

	/* AVI InfoFrame */
	nvkm_mask(device, 0x690000 + hdmi, 0x00000001, 0x00000000);
	अगर (avi_size) अणु
		nvkm_wr32(device, 0x690008 + hdmi, avi_infoframe.header);
		nvkm_wr32(device, 0x69000c + hdmi, avi_infoframe.subpack0_low);
		nvkm_wr32(device, 0x690010 + hdmi, avi_infoframe.subpack0_high);
		nvkm_wr32(device, 0x690014 + hdmi, avi_infoframe.subpack1_low);
		nvkm_wr32(device, 0x690018 + hdmi, avi_infoframe.subpack1_high);
		nvkm_mask(device, 0x690000 + hdmi, 0x00000001, 0x00000001);
	पूर्ण

	/* GENERIC(?) / Venकरोr InfoFrame? */
	nvkm_mask(device, 0x690100 + hdmi, 0x00010001, 0x00000000);
	अगर (venकरोr_size) अणु
		nvkm_wr32(device, 0x690108 + hdmi, venकरोr_infoframe.header);
		nvkm_wr32(device, 0x69010c + hdmi, venकरोr_infoframe.subpack0_low);
		nvkm_wr32(device, 0x690110 + hdmi, venकरोr_infoframe.subpack0_high);
		/* Is there a second (or further?) set of subpack रेजिस्टरs here? */
		nvkm_mask(device, 0x690100 + hdmi, 0x00000001, 0x00000001);
	पूर्ण


	/* ??? InfoFrame? */
	nvkm_mask(device, 0x6900c0 + hdmi, 0x00000001, 0x00000000);
	nvkm_wr32(device, 0x6900cc + hdmi, 0x00000010);
	nvkm_mask(device, 0x6900c0 + hdmi, 0x00000001, 0x00000001);

	/* ??? */
	nvkm_wr32(device, 0x690080 + hdmi, 0x82000000);

	/* HDMI_CTRL */
	nvkm_mask(device, 0x616798 + hoff, 0x401f007f, ctrl);
पूर्ण
