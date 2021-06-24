<शैली गुरु>
/*
 * Copyright 2014 Martin Peres
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
#समावेश <subdev/bios/fan.h>

अटल u32
nvbios_fan_table(काष्ठा nvkm_bios *bios, u8 *ver, u8 *hdr, u8 *cnt, u8 *len)
अणु
	काष्ठा bit_entry bit_P;
	u32 fan = 0;

	अगर (!bit_entry(bios, 'P', &bit_P)) अणु
		अगर (bit_P.version == 2 && bit_P.length >= 0x5c)
			fan = nvbios_rd32(bios, bit_P.offset + 0x58);

		अगर (fan) अणु
			*ver = nvbios_rd08(bios, fan + 0);
			चयन (*ver) अणु
			हाल 0x10:
				*hdr = nvbios_rd08(bios, fan + 1);
				*len = nvbios_rd08(bios, fan + 2);
				*cnt = nvbios_rd08(bios, fan + 3);
				वापस fan;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल u32
nvbios_fan_entry(काष्ठा nvkm_bios *bios, पूर्णांक idx, u8 *ver, u8 *hdr,
		 u8 *cnt, u8 *len)
अणु
	u32 data = nvbios_fan_table(bios, ver, hdr, cnt, len);
	अगर (data && idx < *cnt)
		वापस data + *hdr + (idx * (*len));
	वापस 0;
पूर्ण

u32
nvbios_fan_parse(काष्ठा nvkm_bios *bios, काष्ठा nvbios_therm_fan *fan)
अणु
	u8 ver, hdr, cnt, len;

	u32 data = nvbios_fan_entry(bios, 0, &ver, &hdr, &cnt, &len);
	अगर (data) अणु
		u8 type = nvbios_rd08(bios, data + 0x00);
		चयन (type) अणु
		हाल 0:
			fan->type = NVBIOS_THERM_FAN_TOGGLE;
			अवरोध;
		हाल 1:
		हाल 2:
			/* TODO: Understand the dअगरference between the two! */
			fan->type = NVBIOS_THERM_FAN_PWM;
			अवरोध;
		शेष:
			fan->type = NVBIOS_THERM_FAN_UNK;
		पूर्ण

		fan->fan_mode = NVBIOS_THERM_FAN_LINEAR;
		fan->min_duty = nvbios_rd08(bios, data + 0x02);
		fan->max_duty = nvbios_rd08(bios, data + 0x03);

		fan->pwm_freq = nvbios_rd32(bios, data + 0x0b) & 0xffffff;
	पूर्ण

	वापस data;
पूर्ण
