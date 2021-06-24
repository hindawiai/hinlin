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
#समावेश <subdev/bios/dp.h>

u16
nvbios_dp_table(काष्ठा nvkm_bios *bios, u8 *ver, u8 *hdr, u8 *cnt, u8 *len)
अणु
	काष्ठा bit_entry d;

	अगर (!bit_entry(bios, 'd', &d)) अणु
		अगर (d.version == 1 && d.length >= 2) अणु
			u16 data = nvbios_rd16(bios, d.offset);
			अगर (data) अणु
				*ver = nvbios_rd08(bios, data + 0x00);
				चयन (*ver) अणु
				हाल 0x20:
				हाल 0x21:
				हाल 0x30:
				हाल 0x40:
				हाल 0x41:
				हाल 0x42:
					*hdr = nvbios_rd08(bios, data + 0x01);
					*len = nvbios_rd08(bios, data + 0x02);
					*cnt = nvbios_rd08(bios, data + 0x03);
					वापस data;
				शेष:
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0x0000;
पूर्ण

अटल u16
nvbios_dpout_entry(काष्ठा nvkm_bios *bios, u8 idx,
		   u8 *ver, u8 *hdr, u8 *cnt, u8 *len)
अणु
	u16 data = nvbios_dp_table(bios, ver, hdr, cnt, len);
	अगर (data && idx < *cnt) अणु
		u16 outp = nvbios_rd16(bios, data + *hdr + idx * *len);
		चयन (*ver * !!outp) अणु
		हाल 0x20:
		हाल 0x21:
		हाल 0x30:
			*hdr = nvbios_rd08(bios, data + 0x04);
			*len = nvbios_rd08(bios, data + 0x05);
			*cnt = nvbios_rd08(bios, outp + 0x04);
			अवरोध;
		हाल 0x40:
		हाल 0x41:
		हाल 0x42:
			*hdr = nvbios_rd08(bios, data + 0x04);
			*cnt = 0;
			*len = 0;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		वापस outp;
	पूर्ण
	*ver = 0x00;
	वापस 0x0000;
पूर्ण

u16
nvbios_dpout_parse(काष्ठा nvkm_bios *bios, u8 idx,
		   u8 *ver, u8 *hdr, u8 *cnt, u8 *len,
		   काष्ठा nvbios_dpout *info)
अणु
	u16 data = nvbios_dpout_entry(bios, idx, ver, hdr, cnt, len);
	स_रखो(info, 0x00, माप(*info));
	अगर (data && *ver) अणु
		info->type = nvbios_rd16(bios, data + 0x00);
		info->mask = nvbios_rd16(bios, data + 0x02);
		चयन (*ver) अणु
		हाल 0x20:
			info->mask |= 0x00c0; /* match any link */
			fallthrough;
		हाल 0x21:
		हाल 0x30:
			info->flags     = nvbios_rd08(bios, data + 0x05);
			info->script[0] = nvbios_rd16(bios, data + 0x06);
			info->script[1] = nvbios_rd16(bios, data + 0x08);
			अगर (*len >= 0x0c)
				info->lnkcmp    = nvbios_rd16(bios, data + 0x0a);
			अगर (*len >= 0x0f) अणु
				info->script[2] = nvbios_rd16(bios, data + 0x0c);
				info->script[3] = nvbios_rd16(bios, data + 0x0e);
			पूर्ण
			अगर (*len >= 0x11)
				info->script[4] = nvbios_rd16(bios, data + 0x10);
			अवरोध;
		हाल 0x40:
		हाल 0x41:
		हाल 0x42:
			info->flags     = nvbios_rd08(bios, data + 0x04);
			info->script[0] = nvbios_rd16(bios, data + 0x05);
			info->script[1] = nvbios_rd16(bios, data + 0x07);
			info->lnkcmp    = nvbios_rd16(bios, data + 0x09);
			info->script[2] = nvbios_rd16(bios, data + 0x0b);
			info->script[3] = nvbios_rd16(bios, data + 0x0d);
			info->script[4] = nvbios_rd16(bios, data + 0x0f);
			अवरोध;
		शेष:
			data = 0x0000;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस data;
पूर्ण

u16
nvbios_dpout_match(काष्ठा nvkm_bios *bios, u16 type, u16 mask,
		   u8 *ver, u8 *hdr, u8 *cnt, u8 *len,
		   काष्ठा nvbios_dpout *info)
अणु
	u16 data, idx = 0;
	जबतक ((data = nvbios_dpout_parse(bios, idx++, ver, hdr, cnt, len, info)) || *ver) अणु
		अगर (data && info->type == type) अणु
			अगर ((info->mask & mask) == mask)
				अवरोध;
		पूर्ण
	पूर्ण
	वापस data;
पूर्ण

अटल u16
nvbios_dpcfg_entry(काष्ठा nvkm_bios *bios, u16 outp, u8 idx,
		   u8 *ver, u8 *hdr, u8 *cnt, u8 *len)
अणु
	अगर (*ver >= 0x40) अणु
		outp = nvbios_dp_table(bios, ver, hdr, cnt, len);
		*hdr = *hdr + (*len * * cnt);
		*len = nvbios_rd08(bios, outp + 0x06);
		*cnt = nvbios_rd08(bios, outp + 0x07) *
		       nvbios_rd08(bios, outp + 0x05);
	पूर्ण

	अगर (idx < *cnt)
		वापस outp + *hdr + (idx * *len);

	वापस 0x0000;
पूर्ण

u16
nvbios_dpcfg_parse(काष्ठा nvkm_bios *bios, u16 outp, u8 idx,
		   u8 *ver, u8 *hdr, u8 *cnt, u8 *len,
		   काष्ठा nvbios_dpcfg *info)
अणु
	u16 data = nvbios_dpcfg_entry(bios, outp, idx, ver, hdr, cnt, len);
	स_रखो(info, 0x00, माप(*info));
	अगर (data) अणु
		चयन (*ver) अणु
		हाल 0x20:
		हाल 0x21:
			info->dc    = nvbios_rd08(bios, data + 0x02);
			info->pe    = nvbios_rd08(bios, data + 0x03);
			info->tx_pu = nvbios_rd08(bios, data + 0x04);
			अवरोध;
		हाल 0x30:
		हाल 0x40:
		हाल 0x41:
			info->pc    = nvbios_rd08(bios, data + 0x00);
			info->dc    = nvbios_rd08(bios, data + 0x01);
			info->pe    = nvbios_rd08(bios, data + 0x02);
			info->tx_pu = nvbios_rd08(bios, data + 0x03);
			अवरोध;
		हाल 0x42:
			info->dc    = nvbios_rd08(bios, data + 0x00);
			info->pe    = nvbios_rd08(bios, data + 0x01);
			info->tx_pu = nvbios_rd08(bios, data + 0x02);
			अवरोध;
		शेष:
			data = 0x0000;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस data;
पूर्ण

u16
nvbios_dpcfg_match(काष्ठा nvkm_bios *bios, u16 outp, u8 pc, u8 vs, u8 pe,
		   u8 *ver, u8 *hdr, u8 *cnt, u8 *len,
		   काष्ठा nvbios_dpcfg *info)
अणु
	u8 idx = 0xff;
	u16 data;

	अगर (*ver >= 0x30) अणु
		अटल स्थिर u8 vsoff[] = अणु 0, 4, 7, 9 पूर्ण;
		idx = (pc * 10) + vsoff[vs] + pe;
		अगर (*ver >= 0x40 && *ver <= 0x41 && *hdr >= 0x12)
			idx += nvbios_rd08(bios, outp + 0x11) * 40;
		अन्यथा
		अगर (*ver >= 0x42)
			idx += nvbios_rd08(bios, outp + 0x11) * 10;
	पूर्ण अन्यथा अणु
		जबतक ((data = nvbios_dpcfg_entry(bios, outp, ++idx,
						  ver, hdr, cnt, len))) अणु
			अगर (nvbios_rd08(bios, data + 0x00) == vs &&
			    nvbios_rd08(bios, data + 0x01) == pe)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस nvbios_dpcfg_parse(bios, outp, idx, ver, hdr, cnt, len, info);
पूर्ण
