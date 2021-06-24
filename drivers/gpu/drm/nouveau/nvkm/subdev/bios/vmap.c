<शैली गुरु>
/*
 * Copyright 2012 Nouveau Community
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
 * Authors: Martin Peres
 */
#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/bit.h>
#समावेश <subdev/bios/vmap.h>

u32
nvbios_vmap_table(काष्ठा nvkm_bios *bios, u8 *ver, u8 *hdr, u8 *cnt, u8 *len)
अणु
	काष्ठा bit_entry bit_P;
	u32 vmap = 0;

	अगर (!bit_entry(bios, 'P', &bit_P)) अणु
		अगर (bit_P.version == 2) अणु
			vmap = nvbios_rd32(bios, bit_P.offset + 0x20);
			अगर (vmap) अणु
				*ver = nvbios_rd08(bios, vmap + 0);
				चयन (*ver) अणु
				हाल 0x10:
				हाल 0x20:
					*hdr = nvbios_rd08(bios, vmap + 1);
					*cnt = nvbios_rd08(bios, vmap + 3);
					*len = nvbios_rd08(bios, vmap + 2);
					वापस vmap;
				शेष:
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

u32
nvbios_vmap_parse(काष्ठा nvkm_bios *bios, u8 *ver, u8 *hdr, u8 *cnt, u8 *len,
		  काष्ठा nvbios_vmap *info)
अणु
	u32 vmap = nvbios_vmap_table(bios, ver, hdr, cnt, len);
	स_रखो(info, 0x00, माप(*info));
	चयन (!!vmap * *ver) अणु
	हाल 0x10:
		info->max0 = 0xff;
		info->max1 = 0xff;
		info->max2 = 0xff;
		अवरोध;
	हाल 0x20:
		info->max0 = nvbios_rd08(bios, vmap + 0x7);
		info->max1 = nvbios_rd08(bios, vmap + 0x8);
		अगर (*len >= 0xc)
			info->max2 = nvbios_rd08(bios, vmap + 0xc);
		अन्यथा
			info->max2 = 0xff;
		अवरोध;
	पूर्ण
	वापस vmap;
पूर्ण

u32
nvbios_vmap_entry(काष्ठा nvkm_bios *bios, पूर्णांक idx, u8 *ver, u8 *len)
अणु
	u8  hdr, cnt;
	u32 vmap = nvbios_vmap_table(bios, ver, &hdr, &cnt, len);
	अगर (vmap && idx < cnt) अणु
		vmap = vmap + hdr + (idx * *len);
		वापस vmap;
	पूर्ण
	वापस 0;
पूर्ण

u32
nvbios_vmap_entry_parse(काष्ठा nvkm_bios *bios, पूर्णांक idx, u8 *ver, u8 *len,
			काष्ठा nvbios_vmap_entry *info)
अणु
	u32 vmap = nvbios_vmap_entry(bios, idx, ver, len);
	स_रखो(info, 0x00, माप(*info));
	चयन (!!vmap * *ver) अणु
	हाल 0x10:
		info->link   = 0xff;
		info->min    = nvbios_rd32(bios, vmap + 0x00);
		info->max    = nvbios_rd32(bios, vmap + 0x04);
		info->arg[0] = nvbios_rd32(bios, vmap + 0x08);
		info->arg[1] = nvbios_rd32(bios, vmap + 0x0c);
		info->arg[2] = nvbios_rd32(bios, vmap + 0x10);
		अवरोध;
	हाल 0x20:
		info->mode   = nvbios_rd08(bios, vmap + 0x00);
		info->link   = nvbios_rd08(bios, vmap + 0x01);
		info->min    = nvbios_rd32(bios, vmap + 0x02);
		info->max    = nvbios_rd32(bios, vmap + 0x06);
		info->arg[0] = nvbios_rd32(bios, vmap + 0x0a);
		info->arg[1] = nvbios_rd32(bios, vmap + 0x0e);
		info->arg[2] = nvbios_rd32(bios, vmap + 0x12);
		info->arg[3] = nvbios_rd32(bios, vmap + 0x16);
		info->arg[4] = nvbios_rd32(bios, vmap + 0x1a);
		info->arg[5] = nvbios_rd32(bios, vmap + 0x1e);
		अवरोध;
	पूर्ण
	वापस vmap;
पूर्ण
