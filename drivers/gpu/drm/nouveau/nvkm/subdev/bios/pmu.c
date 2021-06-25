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
#समावेश <subdev/bios/bit.h>
#समावेश <subdev/bios/image.h>
#समावेश <subdev/bios/pmu.h>

u32
nvbios_pmuTe(काष्ठा nvkm_bios *bios, u8 *ver, u8 *hdr, u8 *cnt, u8 *len)
अणु
	काष्ठा bit_entry bit_p;
	u32 data = 0;

	अगर (!bit_entry(bios, 'p', &bit_p)) अणु
		अगर (bit_p.version == 2 && bit_p.length >= 4)
			data = nvbios_rd32(bios, bit_p.offset + 0x00);
		अगर (data) अणु
			*ver = nvbios_rd08(bios, data + 0x00); /* maybe? */
			*hdr = nvbios_rd08(bios, data + 0x01);
			*len = nvbios_rd08(bios, data + 0x02);
			*cnt = nvbios_rd08(bios, data + 0x03);
		पूर्ण
	पूर्ण

	वापस data;
पूर्ण

u32
nvbios_pmuEe(काष्ठा nvkm_bios *bios, पूर्णांक idx, u8 *ver, u8 *hdr)
अणु
	u8  cnt, len;
	u32 data = nvbios_pmuTe(bios, ver, hdr, &cnt, &len);
	अगर (data && idx < cnt) अणु
		data = data + *hdr + (idx * len);
		*hdr = len;
		वापस data;
	पूर्ण
	वापस 0;
पूर्ण

u32
nvbios_pmuEp(काष्ठा nvkm_bios *bios, पूर्णांक idx, u8 *ver, u8 *hdr,
	     काष्ठा nvbios_pmuE *info)
अणु
	u32 data = nvbios_pmuEe(bios, idx, ver, hdr);
	स_रखो(info, 0x00, माप(*info));
	चयन (!!data * *ver) अणु
	शेष:
		info->type = nvbios_rd08(bios, data + 0x00);
		info->data = nvbios_rd32(bios, data + 0x02);
		अवरोध;
	पूर्ण
	वापस data;
पूर्ण

bool
nvbios_pmuRm(काष्ठा nvkm_bios *bios, u8 type, काष्ठा nvbios_pmuR *info)
अणु
	काष्ठा nvbios_pmuE pmuE;
	u8  ver, hdr, idx = 0;
	u32 data;
	स_रखो(info, 0x00, माप(*info));
	जबतक ((data = nvbios_pmuEp(bios, idx++, &ver, &hdr, &pmuE))) अणु
		अगर (pmuE.type == type && (data = pmuE.data)) अणु
			info->init_addr_pmu = nvbios_rd32(bios, data + 0x08);
			info->args_addr_pmu = nvbios_rd32(bios, data + 0x0c);
			info->boot_addr     = data + 0x30;
			info->boot_addr_pmu = nvbios_rd32(bios, data + 0x10) +
					      nvbios_rd32(bios, data + 0x18);
			info->boot_size     = nvbios_rd32(bios, data + 0x1c) -
					      nvbios_rd32(bios, data + 0x18);
			info->code_addr     = info->boot_addr + info->boot_size;
			info->code_addr_pmu = info->boot_addr_pmu +
					      info->boot_size;
			info->code_size     = nvbios_rd32(bios, data + 0x20);
			info->data_addr     = data + 0x30 +
					      nvbios_rd32(bios, data + 0x24);
			info->data_addr_pmu = nvbios_rd32(bios, data + 0x28);
			info->data_size     = nvbios_rd32(bios, data + 0x2c);
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण
