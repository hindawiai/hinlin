<शैली गुरु>
/*
 * Copyright 2016 Karol Herbst
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
 * Authors: Karol Herbst
 */
#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/bit.h>
#समावेश <subdev/bios/घातer_budget.h>

अटल u32
nvbios_घातer_budget_table(काष्ठा nvkm_bios *bios, u8 *ver, u8 *hdr, u8 *cnt,
			  u8 *len)
अणु
	काष्ठा bit_entry bit_P;
	u32 घातer_budget;

	अगर (bit_entry(bios, 'P', &bit_P) || bit_P.version != 2 ||
	    bit_P.length < 0x30)
		वापस 0;

	घातer_budget = nvbios_rd32(bios, bit_P.offset + 0x2c);
	अगर (!घातer_budget)
		वापस 0;

	*ver = nvbios_rd08(bios, घातer_budget);
	चयन (*ver) अणु
	हाल 0x20:
	हाल 0x30:
		*hdr = nvbios_rd08(bios, घातer_budget + 0x1);
		*len = nvbios_rd08(bios, घातer_budget + 0x2);
		*cnt = nvbios_rd08(bios, घातer_budget + 0x3);
		वापस घातer_budget;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
nvbios_घातer_budget_header(काष्ठा nvkm_bios *bios,
                           काष्ठा nvbios_घातer_budget *budget)
अणु
	काष्ठा nvkm_subdev *subdev = &bios->subdev;
	u8 ver, hdr, cnt, len, cap_entry;
	u32 header;

	अगर (!bios || !budget)
		वापस -EINVAL;

	header = nvbios_घातer_budget_table(bios, &ver, &hdr, &cnt, &len);
	अगर (!header || !cnt)
		वापस -ENODEV;

	चयन (ver) अणु
	हाल 0x20:
		cap_entry = nvbios_rd08(bios, header + 0x9);
		अवरोध;
	हाल 0x30:
		cap_entry = nvbios_rd08(bios, header + 0xa);
		अवरोध;
	शेष:
		cap_entry = 0xff;
	पूर्ण

	अगर (cap_entry >= cnt && cap_entry != 0xff) अणु
		nvkm_warn(subdev,
		          "invalid cap_entry in power budget table found\n");
		budget->cap_entry = 0xff;
		वापस -EINVAL;
	पूर्ण

	budget->offset = header;
	budget->ver = ver;
	budget->hlen = hdr;
	budget->elen = len;
	budget->ecount = cnt;

	budget->cap_entry = cap_entry;

	वापस 0;
पूर्ण

पूर्णांक
nvbios_घातer_budget_entry(काष्ठा nvkm_bios *bios,
                          काष्ठा nvbios_घातer_budget *budget,
                          u8 idx, काष्ठा nvbios_घातer_budget_entry *entry)
अणु
	u32 entry_offset;

	अगर (!bios || !budget || !budget->offset || idx >= budget->ecount
		|| !entry)
		वापस -EINVAL;

	entry_offset = budget->offset + budget->hlen + idx * budget->elen;

	अगर (budget->ver >= 0x20) अणु
		entry->min_w = nvbios_rd32(bios, entry_offset + 0x2);
		entry->avg_w = nvbios_rd32(bios, entry_offset + 0x6);
		entry->max_w = nvbios_rd32(bios, entry_offset + 0xa);
	पूर्ण अन्यथा अणु
		entry->min_w = 0;
		entry->max_w = nvbios_rd32(bios, entry_offset + 0x2);
		entry->avg_w = entry->max_w;
	पूर्ण

	वापस 0;
पूर्ण
