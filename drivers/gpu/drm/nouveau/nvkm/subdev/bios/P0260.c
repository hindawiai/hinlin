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
#समावेश <subdev/bios/P0260.h>

u32
nvbios_P0260Te(काष्ठा nvkm_bios *bios,
	       u8 *ver, u8 *hdr, u8 *cnt, u8 *len, u8 *xnr, u8 *xsz)
अणु
	काष्ठा bit_entry bit_P;
	u32 data = 0x00000000;

	अगर (!bit_entry(bios, 'P', &bit_P)) अणु
		अगर (bit_P.version == 2 && bit_P.length > 0x63)
			data = nvbios_rd32(bios, bit_P.offset + 0x60);
		अगर (data) अणु
			*ver = nvbios_rd08(bios, data + 0);
			चयन (*ver) अणु
			हाल 0x10:
				*hdr = nvbios_rd08(bios, data + 1);
				*cnt = nvbios_rd08(bios, data + 2);
				*len = 4;
				*xnr = nvbios_rd08(bios, data + 3);
				*xsz = 4;
				वापस data;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0x00000000;
पूर्ण

u32
nvbios_P0260Ee(काष्ठा nvkm_bios *bios, पूर्णांक idx, u8 *ver, u8 *len)
अणु
	u8  hdr, cnt, xnr, xsz;
	u32 data = nvbios_P0260Te(bios, ver, &hdr, &cnt, len, &xnr, &xsz);
	अगर (data && idx < cnt)
		वापस data + hdr + (idx * *len);
	वापस 0x00000000;
पूर्ण

u32
nvbios_P0260Ep(काष्ठा nvkm_bios *bios, पूर्णांक idx, u8 *ver, u8 *len,
	       काष्ठा nvbios_P0260E *info)
अणु
	u32 data = nvbios_P0260Ee(bios, idx, ver, len);
	स_रखो(info, 0x00, माप(*info));
	चयन (!!data * *ver) अणु
	हाल 0x10:
		info->data = nvbios_rd32(bios, data);
		वापस data;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0x00000000;
पूर्ण

u32
nvbios_P0260Xe(काष्ठा nvkm_bios *bios, पूर्णांक idx, u8 *ver, u8 *xsz)
अणु
	u8  hdr, cnt, len, xnr;
	u32 data = nvbios_P0260Te(bios, ver, &hdr, &cnt, &len, &xnr, xsz);
	अगर (data && idx < xnr)
		वापस data + hdr + (cnt * len) + (idx * *xsz);
	वापस 0x00000000;
पूर्ण

u32
nvbios_P0260Xp(काष्ठा nvkm_bios *bios, पूर्णांक idx, u8 *ver, u8 *hdr,
	       काष्ठा nvbios_P0260X *info)
अणु
	u32 data = nvbios_P0260Xe(bios, idx, ver, hdr);
	स_रखो(info, 0x00, माप(*info));
	चयन (!!data * *ver) अणु
	हाल 0x10:
		info->data = nvbios_rd32(bios, data);
		वापस data;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0x00000000;
पूर्ण
