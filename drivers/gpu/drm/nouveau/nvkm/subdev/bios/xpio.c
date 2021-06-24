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
#समावेश <subdev/bios/gpपन.स>
#समावेश <subdev/bios/xpपन.स>

अटल u16
dcb_xpiod_table(काष्ठा nvkm_bios *bios, u8 *ver, u8 *hdr, u8 *cnt, u8 *len)
अणु
	u16 data = dcb_gpio_table(bios, ver, hdr, cnt, len);
	अगर (data && *ver >= 0x40 && *hdr >= 0x06) अणु
		u16 xpio = nvbios_rd16(bios, data + 0x04);
		अगर (xpio) अणु
			*ver = nvbios_rd08(bios, data + 0x00);
			*hdr = nvbios_rd08(bios, data + 0x01);
			*cnt = nvbios_rd08(bios, data + 0x02);
			*len = nvbios_rd08(bios, data + 0x03);
			वापस xpio;
		पूर्ण
	पूर्ण
	वापस 0x0000;
पूर्ण

u16
dcb_xpio_table(काष्ठा nvkm_bios *bios, u8 idx,
	       u8 *ver, u8 *hdr, u8 *cnt, u8 *len)
अणु
	u16 data = dcb_xpiod_table(bios, ver, hdr, cnt, len);
	अगर (data && idx < *cnt) अणु
		u16 xpio = nvbios_rd16(bios, data + *hdr + (idx * *len));
		अगर (xpio) अणु
			*ver = nvbios_rd08(bios, data + 0x00);
			*hdr = nvbios_rd08(bios, data + 0x01);
			*cnt = nvbios_rd08(bios, data + 0x02);
			*len = nvbios_rd08(bios, data + 0x03);
			वापस xpio;
		पूर्ण
	पूर्ण
	वापस 0x0000;
पूर्ण

u16
dcb_xpio_parse(काष्ठा nvkm_bios *bios, u8 idx,
	       u8 *ver, u8 *hdr, u8 *cnt, u8 *len, काष्ठा nvbios_xpio *info)
अणु
	u16 data = dcb_xpio_table(bios, idx, ver, hdr, cnt, len);
	अगर (data && *len >= 6) अणु
		info->type = nvbios_rd08(bios, data + 0x04);
		info->addr = nvbios_rd08(bios, data + 0x05);
		info->flags = nvbios_rd08(bios, data + 0x06);
	पूर्ण
	वापस 0x0000;
पूर्ण
