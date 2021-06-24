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
#समावेश <subdev/bios/gpपन.स>
#समावेश <subdev/bios/xpपन.स>

u16
dcb_gpio_table(काष्ठा nvkm_bios *bios, u8 *ver, u8 *hdr, u8 *cnt, u8 *len)
अणु
	u16 data = 0x0000;
	u16 dcb = dcb_table(bios, ver, hdr, cnt, len);
	अगर (dcb) अणु
		अगर (*ver >= 0x30 && *hdr >= 0x0c)
			data = nvbios_rd16(bios, dcb + 0x0a);
		अन्यथा
		अगर (*ver >= 0x22 && nvbios_rd08(bios, dcb - 1) >= 0x13)
			data = nvbios_rd16(bios, dcb - 0x0f);

		अगर (data) अणु
			*ver = nvbios_rd08(bios, data + 0x00);
			अगर (*ver < 0x30) अणु
				*hdr = 3;
				*cnt = nvbios_rd08(bios, data + 0x02);
				*len = nvbios_rd08(bios, data + 0x01);
			पूर्ण अन्यथा
			अगर (*ver <= 0x41) अणु
				*hdr = nvbios_rd08(bios, data + 0x01);
				*cnt = nvbios_rd08(bios, data + 0x02);
				*len = nvbios_rd08(bios, data + 0x03);
			पूर्ण अन्यथा अणु
				data = 0x0000;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस data;
पूर्ण

u16
dcb_gpio_entry(काष्ठा nvkm_bios *bios, पूर्णांक idx, पूर्णांक ent, u8 *ver, u8 *len)
अणु
	u8  hdr, cnt, xver; /* use gpio version क्रम xpio entry parsing */
	u16 gpio;

	अगर (!idx--)
		gpio = dcb_gpio_table(bios, ver, &hdr, &cnt, len);
	अन्यथा
		gpio = dcb_xpio_table(bios, idx, &xver, &hdr, &cnt, len);

	अगर (gpio && ent < cnt)
		वापस gpio + hdr + (ent * *len);

	वापस 0x0000;
पूर्ण

u16
dcb_gpio_parse(काष्ठा nvkm_bios *bios, पूर्णांक idx, पूर्णांक ent, u8 *ver, u8 *len,
	       काष्ठा dcb_gpio_func *gpio)
अणु
	u16 data = dcb_gpio_entry(bios, idx, ent, ver, len);
	अगर (data) अणु
		अगर (*ver < 0x40) अणु
			u16 info = nvbios_rd16(bios, data);
			*gpio = (काष्ठा dcb_gpio_func) अणु
				.line = (info & 0x001f) >> 0,
				.func = (info & 0x07e0) >> 5,
				.log[0] = (info & 0x1800) >> 11,
				.log[1] = (info & 0x6000) >> 13,
				.param = !!(info & 0x8000),
			पूर्ण;
		पूर्ण अन्यथा
		अगर (*ver < 0x41) अणु
			u32 info = nvbios_rd32(bios, data);
			*gpio = (काष्ठा dcb_gpio_func) अणु
				.line = (info & 0x0000001f) >> 0,
				.func = (info & 0x0000ff00) >> 8,
				.log[0] = (info & 0x18000000) >> 27,
				.log[1] = (info & 0x60000000) >> 29,
				.param = !!(info & 0x80000000),
			पूर्ण;
		पूर्ण अन्यथा अणु
			u32 info = nvbios_rd32(bios, data + 0);
			u8 info1 = nvbios_rd32(bios, data + 4);
			*gpio = (काष्ठा dcb_gpio_func) अणु
				.line = (info & 0x0000003f) >> 0,
				.func = (info & 0x0000ff00) >> 8,
				.log[0] = (info1 & 0x30) >> 4,
				.log[1] = (info1 & 0xc0) >> 6,
				.param = !!(info & 0x80000000),
			पूर्ण;
		पूर्ण
	पूर्ण

	वापस data;
पूर्ण

u16
dcb_gpio_match(काष्ठा nvkm_bios *bios, पूर्णांक idx, u8 func, u8 line,
	       u8 *ver, u8 *len, काष्ठा dcb_gpio_func *gpio)
अणु
	u8  hdr, cnt, i = 0;
	u16 data;

	जबतक ((data = dcb_gpio_parse(bios, idx, i++, ver, len, gpio))) अणु
		अगर ((line == 0xff || line == gpio->line) &&
		    (func == 0xff || func == gpio->func))
			वापस data;
	पूर्ण

	/* DCB 2.2, fixed TVDAC GPIO data */
	अगर ((data = dcb_table(bios, ver, &hdr, &cnt, len))) अणु
		अगर (*ver >= 0x22 && *ver < 0x30 && func == DCB_GPIO_TVDAC0) अणु
			u8 conf = nvbios_rd08(bios, data - 5);
			u8 addr = nvbios_rd08(bios, data - 4);
			अगर (conf & 0x01) अणु
				*gpio = (काष्ठा dcb_gpio_func) अणु
					.func = DCB_GPIO_TVDAC0,
					.line = addr >> 4,
					.log[0] = !!(conf & 0x02),
					.log[1] =  !(conf & 0x02),
				पूर्ण;
				*ver = 0x00;
				वापस data;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0x0000;
पूर्ण
