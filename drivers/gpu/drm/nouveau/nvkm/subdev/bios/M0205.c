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
#समावेश <subdev/bios/M0205.h>

u32
nvbios_M0205Te(काष्ठा nvkm_bios *bios,
	       u8 *ver, u8 *hdr, u8 *cnt, u8 *len, u8 *snr, u8 *ssz)
अणु
	काष्ठा bit_entry bit_M;
	u32 data = 0x00000000;

	अगर (!bit_entry(bios, 'M', &bit_M)) अणु
		अगर (bit_M.version == 2 && bit_M.length > 0x08)
			data = nvbios_rd32(bios, bit_M.offset + 0x05);
		अगर (data) अणु
			*ver = nvbios_rd08(bios, data + 0x00);
			चयन (*ver) अणु
			हाल 0x10:
				*hdr = nvbios_rd08(bios, data + 0x01);
				*len = nvbios_rd08(bios, data + 0x02);
				*ssz = nvbios_rd08(bios, data + 0x03);
				*snr = nvbios_rd08(bios, data + 0x04);
				*cnt = nvbios_rd08(bios, data + 0x05);
				वापस data;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0x00000000;
पूर्ण

u32
nvbios_M0205Tp(काष्ठा nvkm_bios *bios,
	       u8 *ver, u8 *hdr, u8 *cnt, u8 *len, u8 *snr, u8 *ssz,
	       काष्ठा nvbios_M0205T *info)
अणु
	u32 data = nvbios_M0205Te(bios, ver, hdr, cnt, len, snr, ssz);
	स_रखो(info, 0x00, माप(*info));
	चयन (!!data * *ver) अणु
	हाल 0x10:
		info->freq = nvbios_rd16(bios, data + 0x06);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस data;
पूर्ण

u32
nvbios_M0205Ee(काष्ठा nvkm_bios *bios, पूर्णांक idx,
	       u8 *ver, u8 *hdr, u8 *cnt, u8 *len)
अणु
	u8  snr, ssz;
	u32 data = nvbios_M0205Te(bios, ver, hdr, cnt, len, &snr, &ssz);
	अगर (data && idx < *cnt) अणु
		data = data + *hdr + idx * (*len + (snr * ssz));
		*hdr = *len;
		*cnt = snr;
		*len = ssz;
		वापस data;
	पूर्ण
	वापस 0x00000000;
पूर्ण

u32
nvbios_M0205Ep(काष्ठा nvkm_bios *bios, पूर्णांक idx,
	       u8 *ver, u8 *hdr, u8 *cnt, u8 *len,
	       काष्ठा nvbios_M0205E *info)
अणु
	u32 data = nvbios_M0205Ee(bios, idx, ver, hdr, cnt, len);
	स_रखो(info, 0x00, माप(*info));
	चयन (!!data * *ver) अणु
	हाल 0x10:
		info->type = nvbios_rd08(bios, data + 0x00) & 0x0f;
		वापस data;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0x00000000;
पूर्ण

u32
nvbios_M0205Se(काष्ठा nvkm_bios *bios, पूर्णांक ent, पूर्णांक idx, u8 *ver, u8 *hdr)
अणु

	u8  cnt, len;
	u32 data = nvbios_M0205Ee(bios, ent, ver, hdr, &cnt, &len);
	अगर (data && idx < cnt) अणु
		data = data + *hdr + idx * len;
		*hdr = len;
		वापस data;
	पूर्ण
	वापस 0x00000000;
पूर्ण

u32
nvbios_M0205Sp(काष्ठा nvkm_bios *bios, पूर्णांक ent, पूर्णांक idx, u8 *ver, u8 *hdr,
	       काष्ठा nvbios_M0205S *info)
अणु
	u32 data = nvbios_M0205Se(bios, ent, idx, ver, hdr);
	स_रखो(info, 0x00, माप(*info));
	चयन (!!data * *ver) अणु
	हाल 0x10:
		info->data = nvbios_rd08(bios, data + 0x00);
		वापस data;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0x00000000;
पूर्ण
