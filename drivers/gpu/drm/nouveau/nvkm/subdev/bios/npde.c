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
 * Authors: Ben Skeggs <bskeggs@redhat.com>
 */
#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/npde.h>
#समावेश <subdev/bios/pcir.h>

u32
nvbios_npdeTe(काष्ठा nvkm_bios *bios, u32 base)
अणु
	काष्ठा nvbios_pcirT pcir;
	u8  ver; u16 hdr;
	u32 data = nvbios_pcirTp(bios, base, &ver, &hdr, &pcir);
	अगर (data = (data + hdr + 0x0f) & ~0x0f, data) अणु
		चयन (nvbios_rd32(bios, data + 0x00)) अणु
		हाल 0x4544504e: /* NPDE */
			अवरोध;
		शेष:
			nvkm_debug(&bios->subdev,
				   "%08x: NPDE signature (%08x) unknown\n",
				   data, nvbios_rd32(bios, data + 0x00));
			data = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस data;
पूर्ण

u32
nvbios_npdeTp(काष्ठा nvkm_bios *bios, u32 base, काष्ठा nvbios_npdeT *info)
अणु
	u32 data = nvbios_npdeTe(bios, base);
	स_रखो(info, 0x00, माप(*info));
	अगर (data) अणु
		info->image_size = nvbios_rd16(bios, data + 0x08) * 512;
		info->last = nvbios_rd08(bios, data + 0x0a) & 0x80;
	पूर्ण
	वापस data;
पूर्ण
