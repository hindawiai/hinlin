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
#समावेश <subdev/bios/vpstate.h>

अटल u32
nvbios_vpstate_offset(काष्ठा nvkm_bios *b)
अणु
	काष्ठा bit_entry bit_P;

	अगर (!bit_entry(b, 'P', &bit_P)) अणु
		अगर (bit_P.version == 2 && bit_P.length >= 0x3c)
			वापस nvbios_rd32(b, bit_P.offset + 0x38);
	पूर्ण

	वापस 0x0000;
पूर्ण

पूर्णांक
nvbios_vpstate_parse(काष्ठा nvkm_bios *b, काष्ठा nvbios_vpstate_header *h)
अणु
	अगर (!h)
		वापस -EINVAL;

	h->offset = nvbios_vpstate_offset(b);
	अगर (!h->offset)
		वापस -ENODEV;

	h->version = nvbios_rd08(b, h->offset);
	चयन (h->version) अणु
	हाल 0x10:
		h->hlen     = nvbios_rd08(b, h->offset + 0x1);
		h->elen     = nvbios_rd08(b, h->offset + 0x2);
		h->slen     = nvbios_rd08(b, h->offset + 0x3);
		h->scount   = nvbios_rd08(b, h->offset + 0x4);
		h->ecount   = nvbios_rd08(b, h->offset + 0x5);

		h->base_id  = nvbios_rd08(b, h->offset + 0x0f);
		अगर (h->hlen > 0x10)
			h->boost_id = nvbios_rd08(b, h->offset + 0x10);
		अन्यथा
			h->boost_id = 0xff;
		अगर (h->hlen > 0x11)
			h->tdp_id = nvbios_rd08(b, h->offset + 0x11);
		अन्यथा
			h->tdp_id = 0xff;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक
nvbios_vpstate_entry(काष्ठा nvkm_bios *b, काष्ठा nvbios_vpstate_header *h,
		     u8 idx, काष्ठा nvbios_vpstate_entry *e)
अणु
	u32 offset;

	अगर (!e || !h || idx > h->ecount)
		वापस -EINVAL;

	offset = h->offset + h->hlen + idx * (h->elen + (h->slen * h->scount));
	e->pstate    = nvbios_rd08(b, offset);
	e->घड़ी_mhz = nvbios_rd16(b, offset + 0x5);
	वापस 0;
पूर्ण
