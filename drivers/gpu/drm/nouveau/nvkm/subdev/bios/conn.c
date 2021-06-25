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
#समावेश <subdev/bios/dcb.h>
#समावेश <subdev/bios/conn.h>

u32
nvbios_connTe(काष्ठा nvkm_bios *bios, u8 *ver, u8 *hdr, u8 *cnt, u8 *len)
अणु
	u32 dcb = dcb_table(bios, ver, hdr, cnt, len);
	अगर (dcb && *ver >= 0x30 && *hdr >= 0x16) अणु
		u32 data = nvbios_rd16(bios, dcb + 0x14);
		अगर (data) अणु
			*ver = nvbios_rd08(bios, data + 0);
			*hdr = nvbios_rd08(bios, data + 1);
			*cnt = nvbios_rd08(bios, data + 2);
			*len = nvbios_rd08(bios, data + 3);
			वापस data;
		पूर्ण
	पूर्ण
	वापस 0x00000000;
पूर्ण

u32
nvbios_connTp(काष्ठा nvkm_bios *bios, u8 *ver, u8 *hdr, u8 *cnt, u8 *len,
	      काष्ठा nvbios_connT *info)
अणु
	u32 data = nvbios_connTe(bios, ver, hdr, cnt, len);
	स_रखो(info, 0x00, माप(*info));
	चयन (!!data * *ver) अणु
	हाल 0x30:
	हाल 0x40:
		वापस data;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0x00000000;
पूर्ण

u32
nvbios_connEe(काष्ठा nvkm_bios *bios, u8 idx, u8 *ver, u8 *len)
अणु
	u8  hdr, cnt;
	u32 data = nvbios_connTe(bios, ver, &hdr, &cnt, len);
	अगर (data && idx < cnt)
		वापस data + hdr + (idx * *len);
	वापस 0x00000000;
पूर्ण

u32
nvbios_connEp(काष्ठा nvkm_bios *bios, u8 idx, u8 *ver, u8 *len,
	      काष्ठा nvbios_connE *info)
अणु
	u32 data = nvbios_connEe(bios, idx, ver, len);
	स_रखो(info, 0x00, माप(*info));
	चयन (!!data * *ver) अणु
	हाल 0x30:
	हाल 0x40:
		info->type     =  nvbios_rd08(bios, data + 0x00);
		info->location =  nvbios_rd08(bios, data + 0x01) & 0x0f;
		info->hpd      = (nvbios_rd08(bios, data + 0x01) & 0x30) >> 4;
		info->dp       = (nvbios_rd08(bios, data + 0x01) & 0xc0) >> 6;
		अगर (*len < 4)
			वापस data;
		info->hpd     |= (nvbios_rd08(bios, data + 0x02) & 0x03) << 2;
		info->dp      |=  nvbios_rd08(bios, data + 0x02) & 0x0c;
		info->di       = (nvbios_rd08(bios, data + 0x02) & 0xf0) >> 4;
		info->hpd     |= (nvbios_rd08(bios, data + 0x03) & 0x07) << 4;
		info->sr       = (nvbios_rd08(bios, data + 0x03) & 0x08) >> 3;
		info->lcdid    = (nvbios_rd08(bios, data + 0x03) & 0x70) >> 4;
		वापस data;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0x00000000;
पूर्ण
