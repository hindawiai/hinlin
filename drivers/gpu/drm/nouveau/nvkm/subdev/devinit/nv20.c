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
nv20_devinit_meminit(काष्ठा nvkm_devinit *init)
अणु
	काष्ठा nvkm_subdev *subdev = &init->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	uपूर्णांक32_t mask = (device->chipset >= 0x25 ? 0x300 : 0x900);
	uपूर्णांक32_t amount, off;
	काष्ठा io_mapping *fb;

	/* Map the framebuffer aperture */
	fb = fbmem_init(device);
	अगर (!fb) अणु
		nvkm_error(subdev, "failed to map fb\n");
		वापस;
	पूर्ण

	nvkm_wr32(device, NV10_PFB_REFCTRL, NV10_PFB_REFCTRL_VALID_1);

	/* Allow full addressing */
	nvkm_mask(device, NV04_PFB_CFG0, 0, mask);

	amount = nvkm_rd32(device, 0x10020c);
	क्रम (off = amount; off > 0x2000000; off -= 0x2000000)
		fbmem_poke(fb, off - 4, off);

	amount = nvkm_rd32(device, 0x10020c);
	अगर (amount != fbmem_peek(fb, amount - 4))
		/* IC missing - disable the upper half memory space. */
		nvkm_mask(device, NV04_PFB_CFG0, mask, 0);

	fbmem_fini(fb);
पूर्ण

अटल स्थिर काष्ठा nvkm_devinit_func
nv20_devinit = अणु
	.dtor = nv04_devinit_dtor,
	.preinit = nv04_devinit_preinit,
	.post = nv04_devinit_post,
	.meminit = nv20_devinit_meminit,
	.pll_set = nv04_devinit_pll_set,
पूर्ण;

पूर्णांक
nv20_devinit_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
		 काष्ठा nvkm_devinit **pinit)
अणु
	वापस nv04_devinit_new_(&nv20_devinit, device, type, inst, pinit);
पूर्ण
