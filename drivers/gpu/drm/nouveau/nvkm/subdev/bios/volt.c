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
#समावेश <subdev/bios/bit.h>
#समावेश <subdev/bios/volt.h>

u32
nvbios_volt_table(काष्ठा nvkm_bios *bios, u8 *ver, u8 *hdr, u8 *cnt, u8 *len)
अणु
	काष्ठा bit_entry bit_P;
	u32 volt = 0;

	अगर (!bit_entry(bios, 'P', &bit_P)) अणु
		अगर (bit_P.version == 2)
			volt = nvbios_rd32(bios, bit_P.offset + 0x0c);
		अन्यथा
		अगर (bit_P.version == 1)
			volt = nvbios_rd32(bios, bit_P.offset + 0x10);

		अगर (volt) अणु
			*ver = nvbios_rd08(bios, volt + 0);
			चयन (*ver) अणु
			हाल 0x12:
				*hdr = 5;
				*cnt = nvbios_rd08(bios, volt + 2);
				*len = nvbios_rd08(bios, volt + 1);
				वापस volt;
			हाल 0x20:
				*hdr = nvbios_rd08(bios, volt + 1);
				*cnt = nvbios_rd08(bios, volt + 2);
				*len = nvbios_rd08(bios, volt + 3);
				वापस volt;
			हाल 0x30:
			हाल 0x40:
			हाल 0x50:
				*hdr = nvbios_rd08(bios, volt + 1);
				*cnt = nvbios_rd08(bios, volt + 3);
				*len = nvbios_rd08(bios, volt + 2);
				वापस volt;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

u32
nvbios_volt_parse(काष्ठा nvkm_bios *bios, u8 *ver, u8 *hdr, u8 *cnt, u8 *len,
		  काष्ठा nvbios_volt *info)
अणु
	u32 volt = nvbios_volt_table(bios, ver, hdr, cnt, len);
	स_रखो(info, 0x00, माप(*info));
	चयन (!!volt * *ver) अणु
	हाल 0x12:
		info->type    = NVBIOS_VOLT_GPIO;
		info->vidmask = nvbios_rd08(bios, volt + 0x04);
		info->ranged  = false;
		अवरोध;
	हाल 0x20:
		info->type    = NVBIOS_VOLT_GPIO;
		info->vidmask = nvbios_rd08(bios, volt + 0x05);
		info->ranged  = false;
		अवरोध;
	हाल 0x30:
		info->type    = NVBIOS_VOLT_GPIO;
		info->vidmask = nvbios_rd08(bios, volt + 0x04);
		info->ranged  = false;
		अवरोध;
	हाल 0x40:
		info->type    = NVBIOS_VOLT_GPIO;
		info->base    = nvbios_rd32(bios, volt + 0x04);
		info->step    = nvbios_rd16(bios, volt + 0x08);
		info->vidmask = nvbios_rd08(bios, volt + 0x0b);
		info->ranged  = true; /* XXX: find the flag byte */
		info->min     = min(info->base,
				    info->base + info->step * info->vidmask);
		info->max     = nvbios_rd32(bios, volt + 0x0e);
		अगर (!info->max)
			info->max = max(info->base, info->base + info->step * info->vidmask);
		अवरोध;
	हाल 0x50:
		info->min     = nvbios_rd32(bios, volt + 0x0a);
		info->max     = nvbios_rd32(bios, volt + 0x0e);
		info->base    = nvbios_rd32(bios, volt + 0x12) & 0x00ffffff;

		/* offset 4 seems to be a flag byte */
		अगर (nvbios_rd32(bios, volt + 0x4) & 1) अणु
			info->type      = NVBIOS_VOLT_PWM;
			info->pwm_freq  = nvbios_rd32(bios, volt + 0x5) / 1000;
			info->pwm_range = nvbios_rd32(bios, volt + 0x16);
		पूर्ण अन्यथा अणु
			info->type    = NVBIOS_VOLT_GPIO;
			info->vidmask = nvbios_rd08(bios, volt + 0x06);
			info->step    = nvbios_rd16(bios, volt + 0x16);
			info->ranged  =
				!!(nvbios_rd08(bios, volt + 0x4) & 0x2);
		पूर्ण
		अवरोध;
	पूर्ण
	वापस volt;
पूर्ण

u32
nvbios_volt_entry(काष्ठा nvkm_bios *bios, पूर्णांक idx, u8 *ver, u8 *len)
अणु
	u8  hdr, cnt;
	u32 volt = nvbios_volt_table(bios, ver, &hdr, &cnt, len);
	अगर (volt && idx < cnt) अणु
		volt = volt + hdr + (idx * *len);
		वापस volt;
	पूर्ण
	वापस 0;
पूर्ण

u32
nvbios_volt_entry_parse(काष्ठा nvkm_bios *bios, पूर्णांक idx, u8 *ver, u8 *len,
			काष्ठा nvbios_volt_entry *info)
अणु
	u32 volt = nvbios_volt_entry(bios, idx, ver, len);
	स_रखो(info, 0x00, माप(*info));
	चयन (!!volt * *ver) अणु
	हाल 0x12:
	हाल 0x20:
		info->voltage = nvbios_rd08(bios, volt + 0x00) * 10000;
		info->vid     = nvbios_rd08(bios, volt + 0x01);
		अवरोध;
	हाल 0x30:
		info->voltage = nvbios_rd08(bios, volt + 0x00) * 10000;
		info->vid     = nvbios_rd08(bios, volt + 0x01) >> 2;
		अवरोध;
	हाल 0x40:
		अवरोध;
	हाल 0x50:
		info->voltage = nvbios_rd32(bios, volt) & 0x001fffff;
		info->vid     = (nvbios_rd32(bios, volt) >> 23) & 0xff;
		अवरोध;
	पूर्ण
	वापस volt;
पूर्ण
