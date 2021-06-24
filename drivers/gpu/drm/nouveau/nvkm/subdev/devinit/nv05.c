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
#समावेश <subdev/bios/bmp.h>
#समावेश <subdev/bios/init.h>
#समावेश <subdev/vga.h>

अटल व्योम
nv05_devinit_meminit(काष्ठा nvkm_devinit *init)
अणु
	अटल स्थिर u8 शेष_config_tab[][2] = अणु
		अणु 0x24, 0x00 पूर्ण,
		अणु 0x28, 0x00 पूर्ण,
		अणु 0x24, 0x01 पूर्ण,
		अणु 0x1f, 0x00 पूर्ण,
		अणु 0x0f, 0x00 पूर्ण,
		अणु 0x17, 0x00 पूर्ण,
		अणु 0x06, 0x00 पूर्ण,
		अणु 0x00, 0x00 पूर्ण
	पूर्ण;
	काष्ठा nvkm_subdev *subdev = &init->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_bios *bios = device->bios;
	काष्ठा io_mapping *fb;
	u32 patt = 0xdeadbeef;
	u16 data;
	u8 strap, ramcfg[2];
	पूर्णांक i, v;

	/* Map the framebuffer aperture */
	fb = fbmem_init(device);
	अगर (!fb) अणु
		nvkm_error(subdev, "failed to map fb\n");
		वापस;
	पूर्ण

	strap = (nvkm_rd32(device, 0x101000) & 0x0000003c) >> 2;
	अगर ((data = bmp_mem_init_table(bios))) अणु
		ramcfg[0] = nvbios_rd08(bios, data + 2 * strap + 0);
		ramcfg[1] = nvbios_rd08(bios, data + 2 * strap + 1);
	पूर्ण अन्यथा अणु
		ramcfg[0] = शेष_config_tab[strap][0];
		ramcfg[1] = शेष_config_tab[strap][1];
	पूर्ण

	/* Sequencer off */
	nvkm_wrvgas(device, 0, 1, nvkm_rdvgas(device, 0, 1) | 0x20);

	अगर (nvkm_rd32(device, NV04_PFB_BOOT_0) & NV04_PFB_BOOT_0_UMA_ENABLE)
		जाओ out;

	nvkm_mask(device, NV04_PFB_DEBUG_0, NV04_PFB_DEBUG_0_REFRESH_OFF, 0);

	/* If present load the hardcoded scrambling table */
	अगर (data) अणु
		क्रम (i = 0, data += 0x10; i < 8; i++, data += 4) अणु
			u32 scramble = nvbios_rd32(bios, data);
			nvkm_wr32(device, NV04_PFB_SCRAMBLE(i), scramble);
		पूर्ण
	पूर्ण

	/* Set memory type/width/length शेषs depending on the straps */
	nvkm_mask(device, NV04_PFB_BOOT_0, 0x3f, ramcfg[0]);

	अगर (ramcfg[1] & 0x80)
		nvkm_mask(device, NV04_PFB_CFG0, 0, NV04_PFB_CFG0_SCRAMBLE);

	nvkm_mask(device, NV04_PFB_CFG1, 0x700001, (ramcfg[1] & 1) << 20);
	nvkm_mask(device, NV04_PFB_CFG1, 0, 1);

	/* Probe memory bus width */
	क्रम (i = 0; i < 4; i++)
		fbmem_poke(fb, 4 * i, patt);

	अगर (fbmem_peek(fb, 0xc) != patt)
		nvkm_mask(device, NV04_PFB_BOOT_0,
			  NV04_PFB_BOOT_0_RAM_WIDTH_128, 0);

	/* Probe memory length */
	v = nvkm_rd32(device, NV04_PFB_BOOT_0) & NV04_PFB_BOOT_0_RAM_AMOUNT;

	अगर (v == NV04_PFB_BOOT_0_RAM_AMOUNT_32MB &&
	    (!fbmem_पढ़ोback(fb, 0x1000000, ++patt) ||
	     !fbmem_पढ़ोback(fb, 0, ++patt)))
		nvkm_mask(device, NV04_PFB_BOOT_0, NV04_PFB_BOOT_0_RAM_AMOUNT,
			  NV04_PFB_BOOT_0_RAM_AMOUNT_16MB);

	अगर (v == NV04_PFB_BOOT_0_RAM_AMOUNT_16MB &&
	    !fbmem_पढ़ोback(fb, 0x800000, ++patt))
		nvkm_mask(device, NV04_PFB_BOOT_0, NV04_PFB_BOOT_0_RAM_AMOUNT,
			  NV04_PFB_BOOT_0_RAM_AMOUNT_8MB);

	अगर (!fbmem_पढ़ोback(fb, 0x400000, ++patt))
		nvkm_mask(device, NV04_PFB_BOOT_0, NV04_PFB_BOOT_0_RAM_AMOUNT,
			  NV04_PFB_BOOT_0_RAM_AMOUNT_4MB);

out:
	/* Sequencer on */
	nvkm_wrvgas(device, 0, 1, nvkm_rdvgas(device, 0, 1) & ~0x20);
	fbmem_fini(fb);
पूर्ण

अटल स्थिर काष्ठा nvkm_devinit_func
nv05_devinit = अणु
	.dtor = nv04_devinit_dtor,
	.preinit = nv04_devinit_preinit,
	.post = nv04_devinit_post,
	.meminit = nv05_devinit_meminit,
	.pll_set = nv04_devinit_pll_set,
पूर्ण;

पूर्णांक
nv05_devinit_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
		 काष्ठा nvkm_devinit **pinit)
अणु
	वापस nv04_devinit_new_(&nv05_devinit, device, type, inst, pinit);
पूर्ण
