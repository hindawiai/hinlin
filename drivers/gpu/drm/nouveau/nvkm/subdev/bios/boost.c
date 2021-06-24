<शैली गुरु>
/*
 * Copyright 2013 Red Hat Inc.
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
#समावेश <subdev/bios/boost.h>

u32
nvbios_boostTe(काष्ठा nvkm_bios *bios,
	       u8 *ver, u8 *hdr, u8 *cnt, u8 *len, u8 *snr, u8 *ssz)
अणु
	काष्ठा bit_entry bit_P;
	u32 boost = 0;

	अगर (!bit_entry(bios, 'P', &bit_P)) अणु
		अगर (bit_P.version == 2 && bit_P.length >= 0x34)
			boost = nvbios_rd32(bios, bit_P.offset + 0x30);

		अगर (boost) अणु
			*ver = nvbios_rd08(bios, boost + 0);
			चयन (*ver) अणु
			हाल 0x11:
				*hdr = nvbios_rd08(bios, boost + 1);
				*cnt = nvbios_rd08(bios, boost + 5);
				*len = nvbios_rd08(bios, boost + 2);
				*snr = nvbios_rd08(bios, boost + 4);
				*ssz = nvbios_rd08(bios, boost + 3);
				वापस boost;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

u32
nvbios_boostEe(काष्ठा nvkm_bios *bios, पूर्णांक idx,
	       u8 *ver, u8 *hdr, u8 *cnt, u8 *len)
अणु
	u8  snr, ssz;
	u32 data = nvbios_boostTe(bios, ver, hdr, cnt, len, &snr, &ssz);
	अगर (data && idx < *cnt) अणु
		data = data + *hdr + (idx * (*len + (snr * ssz)));
		*hdr = *len;
		*cnt = snr;
		*len = ssz;
		वापस data;
	पूर्ण
	वापस 0;
पूर्ण

u32
nvbios_boostEp(काष्ठा nvkm_bios *bios, पूर्णांक idx,
	       u8 *ver, u8 *hdr, u8 *cnt, u8 *len, काष्ठा nvbios_boostE *info)
अणु
	u32 data = nvbios_boostEe(bios, idx, ver, hdr, cnt, len);
	स_रखो(info, 0x00, माप(*info));
	अगर (data) अणु
		info->pstate = (nvbios_rd16(bios, data + 0x00) & 0x01e0) >> 5;
		info->min    =  nvbios_rd16(bios, data + 0x02) * 1000;
		info->max    =  nvbios_rd16(bios, data + 0x04) * 1000;
	पूर्ण
	वापस data;
पूर्ण

u32
nvbios_boostEm(काष्ठा nvkm_bios *bios, u8 pstate,
	       u8 *ver, u8 *hdr, u8 *cnt, u8 *len, काष्ठा nvbios_boostE *info)
अणु
	u32 data, idx = 0;
	जबतक ((data = nvbios_boostEp(bios, idx++, ver, hdr, cnt, len, info))) अणु
		अगर (info->pstate == pstate)
			अवरोध;
	पूर्ण
	वापस data;
पूर्ण

u32
nvbios_boostSe(काष्ठा nvkm_bios *bios, पूर्णांक idx,
	       u32 data, u8 *ver, u8 *hdr, u8 cnt, u8 len)
अणु
	अगर (data && idx < cnt) अणु
		data = data + *hdr + (idx * len);
		*hdr = len;
		वापस data;
	पूर्ण
	वापस 0;
पूर्ण

u32
nvbios_boostSp(काष्ठा nvkm_bios *bios, पूर्णांक idx,
	       u32 data, u8 *ver, u8 *hdr, u8 cnt, u8 len,
	       काष्ठा nvbios_boostS *info)
अणु
	data = nvbios_boostSe(bios, idx, data, ver, hdr, cnt, len);
	स_रखो(info, 0x00, माप(*info));
	अगर (data) अणु
		info->करोमुख्य  = nvbios_rd08(bios, data + 0x00);
		info->percent = nvbios_rd08(bios, data + 0x01);
		info->min     = nvbios_rd16(bios, data + 0x02) * 1000;
		info->max     = nvbios_rd16(bios, data + 0x04) * 1000;
	पूर्ण
	वापस data;
पूर्ण
