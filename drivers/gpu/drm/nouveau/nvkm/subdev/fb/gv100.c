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
#समावेश "gf100.h"
#समावेश "ram.h"

पूर्णांक
gv100_fb_init_page(काष्ठा nvkm_fb *fb)
अणु
	वापस (fb->page == 16) ? 0 : -EINVAL;
पूर्ण

अटल स्थिर काष्ठा nvkm_fb_func
gv100_fb = अणु
	.dtor = gf100_fb_dtor,
	.oneinit = gf100_fb_oneinit,
	.init = gp100_fb_init,
	.init_page = gv100_fb_init_page,
	.init_unkn = gp100_fb_init_unkn,
	.vpr.scrub_required = gp102_fb_vpr_scrub_required,
	.vpr.scrub = gp102_fb_vpr_scrub,
	.ram_new = gp100_ram_new,
	.शेष_bigpage = 16,
पूर्ण;

पूर्णांक
gv100_fb_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_fb **pfb)
अणु
	वापस gp102_fb_new_(&gv100_fb, device, type, inst, pfb);
पूर्ण

MODULE_FIRMWARE("nvidia/gv100/nvdec/scrubber.bin");
MODULE_FIRMWARE("nvidia/tu102/nvdec/scrubber.bin");
MODULE_FIRMWARE("nvidia/tu104/nvdec/scrubber.bin");
MODULE_FIRMWARE("nvidia/tu106/nvdec/scrubber.bin");
MODULE_FIRMWARE("nvidia/tu116/nvdec/scrubber.bin");
MODULE_FIRMWARE("nvidia/tu117/nvdec/scrubber.bin");
