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
#समावेश <subdev/bios/dcb.h>
#समावेश <subdev/bios/extdev.h>

अटल u16
extdev_table(काष्ठा nvkm_bios *bios, u8 *ver, u8 *hdr, u8 *len, u8 *cnt)
अणु
	u8  dcb_ver, dcb_hdr, dcb_cnt, dcb_len;
	u16 dcb, extdev = 0;

	dcb = dcb_table(bios, &dcb_ver, &dcb_hdr, &dcb_cnt, &dcb_len);
	अगर (!dcb || (dcb_ver != 0x30 && dcb_ver != 0x40 && dcb_ver != 0x41))
		वापस 0x0000;

	extdev = nvbios_rd16(bios, dcb + 18);
	अगर (!extdev)
		वापस 0x0000;

	*ver = nvbios_rd08(bios, extdev + 0);
	*hdr = nvbios_rd08(bios, extdev + 1);
	*cnt = nvbios_rd08(bios, extdev + 2);
	*len = nvbios_rd08(bios, extdev + 3);
	वापस extdev + *hdr;
पूर्ण

bool
nvbios_extdev_skip_probe(काष्ठा nvkm_bios *bios)
अणु
	u8  ver, hdr, len, cnt;
	u16 data = extdev_table(bios, &ver, &hdr, &len, &cnt);
	अगर (data && ver == 0x40 && hdr >= 5) अणु
		u8 flags = nvbios_rd08(bios, data - hdr + 4);
		अगर (flags & 1)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल u16
nvbios_extdev_entry(काष्ठा nvkm_bios *bios, पूर्णांक idx, u8 *ver, u8 *len)
अणु
	u8 hdr, cnt;
	u16 extdev = extdev_table(bios, ver, &hdr, len, &cnt);
	अगर (extdev && idx < cnt)
		वापस extdev + idx * *len;
	वापस 0x0000;
पूर्ण

अटल व्योम
extdev_parse_entry(काष्ठा nvkm_bios *bios, u16 offset,
		   काष्ठा nvbios_extdev_func *entry)
अणु
	entry->type = nvbios_rd08(bios, offset + 0);
	entry->addr = nvbios_rd08(bios, offset + 1);
	entry->bus = (nvbios_rd08(bios, offset + 2) >> 4) & 1;
पूर्ण

पूर्णांक
nvbios_extdev_parse(काष्ठा nvkm_bios *bios, पूर्णांक idx,
		    काष्ठा nvbios_extdev_func *func)
अणु
	u8 ver, len;
	u16 entry;

	अगर (!(entry = nvbios_extdev_entry(bios, idx, &ver, &len)))
		वापस -EINVAL;

	extdev_parse_entry(bios, entry, func);
	वापस 0;
पूर्ण

पूर्णांक
nvbios_extdev_find(काष्ठा nvkm_bios *bios, क्रमागत nvbios_extdev_type type,
		   काष्ठा nvbios_extdev_func *func)
अणु
	u8 ver, len, i;
	u16 entry;

	i = 0;
	जबतक ((entry = nvbios_extdev_entry(bios, i++, &ver, &len))) अणु
		extdev_parse_entry(bios, entry, func);
		अगर (func->type == type)
			वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण
