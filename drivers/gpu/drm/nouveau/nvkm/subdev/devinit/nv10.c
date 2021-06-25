<शैली गुरु>
/*
 * Copyright (C) 2010 Francisco Jerez.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining
 * a copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE COPYRIGHT OWNER(S) AND/OR ITS SUPPLIERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
#समावेश "nv04.h"
#समावेश "fbmem.h"

#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/init.h>

अटल व्योम
nv10_devinit_meminit(काष्ठा nvkm_devinit *init)
अणु
	काष्ठा nvkm_subdev *subdev = &init->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	अटल स्थिर पूर्णांक mem_width[] = अणु 0x10, 0x00, 0x20 पूर्ण;
	पूर्णांक mem_width_count;
	uपूर्णांक32_t patt = 0xdeadbeef;
	काष्ठा io_mapping *fb;
	पूर्णांक i, j, k;

	अगर (device->card_type >= NV_11 && device->chipset >= 0x17)
		mem_width_count = 3;
	अन्यथा
		mem_width_count = 2;

	/* Map the framebuffer aperture */
	fb = fbmem_init(device);
	अगर (!fb) अणु
		nvkm_error(subdev, "failed to map fb\n");
		वापस;
	पूर्ण

	nvkm_wr32(device, NV10_PFB_REFCTRL, NV10_PFB_REFCTRL_VALID_1);

	/* Probe memory bus width */
	क्रम (i = 0; i < mem_width_count; i++) अणु
		nvkm_mask(device, NV04_PFB_CFG0, 0x30, mem_width[i]);

		क्रम (j = 0; j < 4; j++) अणु
			क्रम (k = 0; k < 4; k++)
				fbmem_poke(fb, 0x1c, 0);

			fbmem_poke(fb, 0x1c, patt);
			fbmem_poke(fb, 0x3c, 0);

			अगर (fbmem_peek(fb, 0x1c) == patt)
				जाओ mem_width_found;
		पूर्ण
	पूर्ण

mem_width_found:
	patt <<= 1;

	/* Probe amount of installed memory */
	क्रम (i = 0; i < 4; i++) अणु
		पूर्णांक off = nvkm_rd32(device, 0x10020c) - 0x100000;

		fbmem_poke(fb, off, patt);
		fbmem_poke(fb, 0, 0);

		fbmem_peek(fb, 0);
		fbmem_peek(fb, 0);
		fbmem_peek(fb, 0);
		fbmem_peek(fb, 0);

		अगर (fbmem_peek(fb, off) == patt)
			जाओ amount_found;
	पूर्ण

	/* IC missing - disable the upper half memory space. */
	nvkm_mask(device, NV04_PFB_CFG0, 0x1000, 0);

amount_found:
	fbmem_fini(fb);
पूर्ण

अटल स्थिर काष्ठा nvkm_devinit_func
nv10_devinit = अणु
	.dtor = nv04_devinit_dtor,
	.preinit = nv04_devinit_preinit,
	.post = nv04_devinit_post,
	.meminit = nv10_devinit_meminit,
	.pll_set = nv04_devinit_pll_set,
पूर्ण;

पूर्णांक
nv10_devinit_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
		 काष्ठा nvkm_devinit **pinit)
अणु
	वापस nv04_devinit_new_(&nv10_devinit, device, type, inst, pinit);
पूर्ण
