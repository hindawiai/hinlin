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
#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/bit.h>
#समावेश <subdev/bios/disp.h>

u16
nvbios_disp_table(काष्ठा nvkm_bios *bios,
		  u8 *ver, u8 *hdr, u8 *cnt, u8 *len, u8 *sub)
अणु
	काष्ठा bit_entry U;

	अगर (!bit_entry(bios, 'U', &U)) अणु
		अगर (U.version == 1) अणु
			u16 data = nvbios_rd16(bios, U.offset);
			अगर (data) अणु
				*ver = nvbios_rd08(bios, data + 0x00);
				चयन (*ver) अणु
				हाल 0x20:
				हाल 0x21:
				हाल 0x22:
					*hdr = nvbios_rd08(bios, data + 0x01);
					*len = nvbios_rd08(bios, data + 0x02);
					*cnt = nvbios_rd08(bios, data + 0x03);
					*sub = nvbios_rd08(bios, data + 0x04);
					वापस data;
				शेष:
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0x0000;
पूर्ण

u16
nvbios_disp_entry(काष्ठा nvkm_bios *bios, u8 idx, u8 *ver, u8 *len, u8 *sub)
अणु
	u8  hdr, cnt;
	u16 data = nvbios_disp_table(bios, ver, &hdr, &cnt, len, sub);
	अगर (data && idx < cnt)
		वापस data + hdr + (idx * *len);
	*ver = 0x00;
	वापस 0x0000;
पूर्ण

u16
nvbios_disp_parse(काष्ठा nvkm_bios *bios, u8 idx, u8 *ver, u8 *len, u8 *sub,
		  काष्ठा nvbios_disp *info)
अणु
	u16 data = nvbios_disp_entry(bios, idx, ver, len, sub);
	अगर (data && *len >= 2) अणु
		info->data = nvbios_rd16(bios, data + 0);
		वापस data;
	पूर्ण
	वापस 0x0000;
पूर्ण

u16
nvbios_outp_entry(काष्ठा nvkm_bios *bios, u8 idx,
		  u8 *ver, u8 *hdr, u8 *cnt, u8 *len)
अणु
	काष्ठा nvbios_disp info;
	u16 data = nvbios_disp_parse(bios, idx, ver, len, hdr, &info);
	अगर (data) अणु
		*cnt = nvbios_rd08(bios, info.data + 0x05);
		*len = 0x06;
		data = info.data;
	पूर्ण
	वापस data;
पूर्ण

u16
nvbios_outp_parse(काष्ठा nvkm_bios *bios, u8 idx,
		  u8 *ver, u8 *hdr, u8 *cnt, u8 *len, काष्ठा nvbios_outp *info)
अणु
	u16 data = nvbios_outp_entry(bios, idx, ver, hdr, cnt, len);
	अगर (data && *hdr >= 0x0a) अणु
		info->type      = nvbios_rd16(bios, data + 0x00);
		info->mask      = nvbios_rd32(bios, data + 0x02);
		अगर (*ver <= 0x20) /* match any link */
			info->mask |= 0x00c0;
		info->script[0] = nvbios_rd16(bios, data + 0x06);
		info->script[1] = nvbios_rd16(bios, data + 0x08);
		info->script[2] = 0x0000;
		अगर (*hdr >= 0x0c)
			info->script[2] = nvbios_rd16(bios, data + 0x0a);
		वापस data;
	पूर्ण
	वापस 0x0000;
पूर्ण

u16
nvbios_outp_match(काष्ठा nvkm_bios *bios, u16 type, u16 mask,
		  u8 *ver, u8 *hdr, u8 *cnt, u8 *len, काष्ठा nvbios_outp *info)
अणु
	u16 data, idx = 0;
	जबतक ((data = nvbios_outp_parse(bios, idx++, ver, hdr, cnt, len, info)) || *ver) अणु
		अगर (data && info->type == type) अणु
			अगर ((info->mask & mask) == mask)
				अवरोध;
		पूर्ण
	पूर्ण
	वापस data;
पूर्ण

u16
nvbios_ocfg_entry(काष्ठा nvkm_bios *bios, u16 outp, u8 idx,
		  u8 *ver, u8 *hdr, u8 *cnt, u8 *len)
अणु
	अगर (idx < *cnt)
		वापस outp + *hdr + (idx * *len);
	वापस 0x0000;
पूर्ण

u16
nvbios_ocfg_parse(काष्ठा nvkm_bios *bios, u16 outp, u8 idx,
		  u8 *ver, u8 *hdr, u8 *cnt, u8 *len, काष्ठा nvbios_ocfg *info)
अणु
	u16 data = nvbios_ocfg_entry(bios, outp, idx, ver, hdr, cnt, len);
	अगर (data) अणु
		info->proto     = nvbios_rd08(bios, data + 0x00);
		info->flags     = nvbios_rd16(bios, data + 0x01);
		info->clkcmp[0] = nvbios_rd16(bios, data + 0x02);
		info->clkcmp[1] = nvbios_rd16(bios, data + 0x04);
	पूर्ण
	वापस data;
पूर्ण

u16
nvbios_ocfg_match(काष्ठा nvkm_bios *bios, u16 outp, u8 proto, u8 flags,
		  u8 *ver, u8 *hdr, u8 *cnt, u8 *len, काष्ठा nvbios_ocfg *info)
अणु
	u16 data, idx = 0;
	जबतक ((data = nvbios_ocfg_parse(bios, outp, idx++, ver, hdr, cnt, len, info))) अणु
		अगर ((info->proto == proto || info->proto == 0xff) &&
		    (info->flags == flags))
			अवरोध;
	पूर्ण
	वापस data;
पूर्ण

u16
nvbios_oclk_match(काष्ठा nvkm_bios *bios, u16 cmp, u32 khz)
अणु
	जबतक (cmp) अणु
		अगर (khz / 10 >= nvbios_rd16(bios, cmp + 0x00))
			वापस  nvbios_rd16(bios, cmp + 0x02);
		cmp += 0x04;
	पूर्ण
	वापस 0x0000;
पूर्ण
