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
#समावेश <subdev/bios/cstep.h>

u32
nvbios_cstepTe(काष्ठा nvkm_bios *bios,
	       u8 *ver, u8 *hdr, u8 *cnt, u8 *len, u8 *xnr, u8 *xsz)
अणु
	काष्ठा bit_entry bit_P;
	u32 cstep = 0;

	अगर (!bit_entry(bios, 'P', &bit_P)) अणु
		अगर (bit_P.version == 2 && bit_P.length >= 0x38)
			cstep = nvbios_rd32(bios, bit_P.offset + 0x34);

		अगर (cstep) अणु
			*ver = nvbios_rd08(bios, cstep + 0);
			चयन (*ver) अणु
			हाल 0x10:
				*hdr = nvbios_rd08(bios, cstep + 1);
				*cnt = nvbios_rd08(bios, cstep + 3);
				*len = nvbios_rd08(bios, cstep + 2);
				*xnr = nvbios_rd08(bios, cstep + 5);
				*xsz = nvbios_rd08(bios, cstep + 4);
				वापस cstep;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

u32
nvbios_cstepEe(काष्ठा nvkm_bios *bios, पूर्णांक idx, u8 *ver, u8 *hdr)
अणु
	u8  cnt, len, xnr, xsz;
	u32 data = nvbios_cstepTe(bios, ver, hdr, &cnt, &len, &xnr, &xsz);
	अगर (data && idx < cnt) अणु
		data = data + *hdr + (idx * len);
		*hdr = len;
		वापस data;
	पूर्ण
	वापस 0;
पूर्ण

u32
nvbios_cstepEp(काष्ठा nvkm_bios *bios, पूर्णांक idx, u8 *ver, u8 *hdr,
	       काष्ठा nvbios_cstepE *info)
अणु
	u32 data = nvbios_cstepEe(bios, idx, ver, hdr);
	स_रखो(info, 0x00, माप(*info));
	अगर (data) अणु
		info->pstate = (nvbios_rd16(bios, data + 0x00) & 0x01e0) >> 5;
		info->index   = nvbios_rd08(bios, data + 0x03);
	पूर्ण
	वापस data;
पूर्ण

u32
nvbios_cstepEm(काष्ठा nvkm_bios *bios, u8 pstate, u8 *ver, u8 *hdr,
	       काष्ठा nvbios_cstepE *info)
अणु
	u32 data, idx = 0;
	जबतक ((data = nvbios_cstepEp(bios, idx++, ver, hdr, info))) अणु
		अगर (info->pstate == pstate)
			अवरोध;
	पूर्ण
	वापस data;
पूर्ण

u32
nvbios_cstepXe(काष्ठा nvkm_bios *bios, पूर्णांक idx, u8 *ver, u8 *hdr)
अणु
	u8  cnt, len, xnr, xsz;
	u32 data = nvbios_cstepTe(bios, ver, hdr, &cnt, &len, &xnr, &xsz);
	अगर (data && idx < xnr) अणु
		data = data + *hdr + (cnt * len) + (idx * xsz);
		*hdr = xsz;
		वापस data;
	पूर्ण
	वापस 0;
पूर्ण

u32
nvbios_cstepXp(काष्ठा nvkm_bios *bios, पूर्णांक idx, u8 *ver, u8 *hdr,
	       काष्ठा nvbios_cstepX *info)
अणु
	u32 data = nvbios_cstepXe(bios, idx, ver, hdr);
	स_रखो(info, 0x00, माप(*info));
	अगर (data) अणु
		info->freq    = nvbios_rd16(bios, data + 0x00) * 1000;
		info->unkn[0] = nvbios_rd08(bios, data + 0x02);
		info->unkn[1] = nvbios_rd08(bios, data + 0x03);
		info->voltage = nvbios_rd08(bios, data + 0x04);
	पूर्ण
	वापस data;
पूर्ण
