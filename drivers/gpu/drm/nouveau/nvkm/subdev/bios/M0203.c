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
 * Authors: Ben Skeggs
 */
#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/bit.h>
#समावेश <subdev/bios/M0203.h>

u32
nvbios_M0203Te(काष्ठा nvkm_bios *bios, u8 *ver, u8 *hdr, u8 *cnt, u8 *len)
अणु
	काष्ठा bit_entry bit_M;
	u32 data = 0x00000000;

	अगर (!bit_entry(bios, 'M', &bit_M)) अणु
		अगर (bit_M.version == 2 && bit_M.length > 0x04)
			data = nvbios_rd16(bios, bit_M.offset + 0x03);
		अगर (data) अणु
			*ver = nvbios_rd08(bios, data + 0x00);
			चयन (*ver) अणु
			हाल 0x10:
				*hdr = nvbios_rd08(bios, data + 0x01);
				*len = nvbios_rd08(bios, data + 0x02);
				*cnt = nvbios_rd08(bios, data + 0x03);
				वापस data;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0x00000000;
पूर्ण

u32
nvbios_M0203Tp(काष्ठा nvkm_bios *bios, u8 *ver, u8 *hdr, u8 *cnt, u8 *len,
	       काष्ठा nvbios_M0203T *info)
अणु
	u32 data = nvbios_M0203Te(bios, ver, hdr, cnt, len);
	स_रखो(info, 0x00, माप(*info));
	चयन (!!data * *ver) अणु
	हाल 0x10:
		info->type    = nvbios_rd08(bios, data + 0x04);
		info->poपूर्णांकer = nvbios_rd16(bios, data + 0x05);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस data;
पूर्ण

u32
nvbios_M0203Ee(काष्ठा nvkm_bios *bios, पूर्णांक idx, u8 *ver, u8 *hdr)
अणु
	u8  cnt, len;
	u32 data = nvbios_M0203Te(bios, ver, hdr, &cnt, &len);
	अगर (data && idx < cnt) अणु
		data = data + *hdr + idx * len;
		*hdr = len;
		वापस data;
	पूर्ण
	वापस 0x00000000;
पूर्ण

u32
nvbios_M0203Ep(काष्ठा nvkm_bios *bios, पूर्णांक idx, u8 *ver, u8 *hdr,
	       काष्ठा nvbios_M0203E *info)
अणु
	u32 data = nvbios_M0203Ee(bios, idx, ver, hdr);
	स_रखो(info, 0x00, माप(*info));
	चयन (!!data * *ver) अणु
	हाल 0x10:
		info->type  = (nvbios_rd08(bios, data + 0x00) & 0x0f) >> 0;
		info->strap = (nvbios_rd08(bios, data + 0x00) & 0xf0) >> 4;
		info->group = (nvbios_rd08(bios, data + 0x01) & 0x0f) >> 0;
		वापस data;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0x00000000;
पूर्ण

u32
nvbios_M0203Em(काष्ठा nvkm_bios *bios, u8 ramcfg, u8 *ver, u8 *hdr,
	       काष्ठा nvbios_M0203E *info)
अणु
	काष्ठा nvkm_subdev *subdev = &bios->subdev;
	काष्ठा nvbios_M0203T M0203T;
	u8  cnt, len, idx = 0xff;
	u32 data;

	अगर (!nvbios_M0203Tp(bios, ver, hdr, &cnt, &len, &M0203T)) अणु
		nvkm_warn(subdev, "M0203T not found\n");
		वापस 0x00000000;
	पूर्ण

	जबतक ((data = nvbios_M0203Ep(bios, ++idx, ver, hdr, info))) अणु
		चयन (M0203T.type) अणु
		हाल M0203T_TYPE_RAMCFG:
			अगर (info->strap != ramcfg)
				जारी;
			वापस data;
		शेष:
			nvkm_warn(subdev, "M0203T type %02x\n", M0203T.type);
			वापस 0x00000000;
		पूर्ण
	पूर्ण

	वापस data;
पूर्ण
