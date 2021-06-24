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
#समावेश <subdev/bios/therm.h>

अटल u32
therm_table(काष्ठा nvkm_bios *bios, u8 *ver, u8 *hdr, u8 *len, u8 *cnt)
अणु
	काष्ठा bit_entry bit_P;
	u32 therm = 0;

	अगर (!bit_entry(bios, 'P', &bit_P)) अणु
		अगर (bit_P.version == 1)
			therm = nvbios_rd32(bios, bit_P.offset + 12);
		अन्यथा अगर (bit_P.version == 2)
			therm = nvbios_rd32(bios, bit_P.offset + 16);
		अन्यथा
			nvkm_error(&bios->subdev,
				   "unknown offset for thermal in BIT P %d\n",
				   bit_P.version);
	पूर्ण

	/* निकास now अगर we haven't found the thermal table */
	अगर (!therm)
		वापस 0;

	*ver = nvbios_rd08(bios, therm + 0);
	*hdr = nvbios_rd08(bios, therm + 1);
	*len = nvbios_rd08(bios, therm + 2);
	*cnt = nvbios_rd08(bios, therm + 3);
	वापस therm + nvbios_rd08(bios, therm + 1);
पूर्ण

अटल u32
nvbios_therm_entry(काष्ठा nvkm_bios *bios, पूर्णांक idx, u8 *ver, u8 *len)
अणु
	u8 hdr, cnt;
	u32 therm = therm_table(bios, ver, &hdr, len, &cnt);
	अगर (therm && idx < cnt)
		वापस therm + idx * *len;
	वापस 0;
पूर्ण

पूर्णांक
nvbios_therm_sensor_parse(काष्ठा nvkm_bios *bios,
			  क्रमागत nvbios_therm_करोमुख्य करोमुख्य,
			  काष्ठा nvbios_therm_sensor *sensor)
अणु
	s8 thrs_section, sensor_section, offset;
	u8 ver, len, i;
	u32 entry;

	/* we only support the core करोमुख्य क्रम now */
	अगर (करोमुख्य != NVBIOS_THERM_DOMAIN_CORE)
		वापस -EINVAL;

	/* Read the entries from the table */
	thrs_section = 0;
	sensor_section = -1;
	i = 0;
	जबतक ((entry = nvbios_therm_entry(bios, i++, &ver, &len))) अणु
		s16 value = nvbios_rd16(bios, entry + 1);

		चयन (nvbios_rd08(bios, entry + 0)) अणु
		हाल 0x0:
			thrs_section = value;
			अगर (value > 0)
				वापस 0; /* we करो not try to support ambient */
			अवरोध;
		हाल 0x01:
			sensor_section++;
			अगर (sensor_section == 0) अणु
				offset = ((s8) nvbios_rd08(bios, entry + 2)) / 2;
				sensor->offset_स्थिरant = offset;
			पूर्ण
			अवरोध;

		हाल 0x04:
			अगर (thrs_section == 0) अणु
				sensor->thrs_critical.temp = (value & 0xff0) >> 4;
				sensor->thrs_critical.hysteresis = value & 0xf;
			पूर्ण
			अवरोध;

		हाल 0x07:
			अगर (thrs_section == 0) अणु
				sensor->thrs_करोwn_घड़ी.temp = (value & 0xff0) >> 4;
				sensor->thrs_करोwn_घड़ी.hysteresis = value & 0xf;
			पूर्ण
			अवरोध;

		हाल 0x08:
			अगर (thrs_section == 0) अणु
				sensor->thrs_fan_boost.temp = (value & 0xff0) >> 4;
				sensor->thrs_fan_boost.hysteresis = value & 0xf;
			पूर्ण
			अवरोध;

		हाल 0x10:
			अगर (sensor_section == 0)
				sensor->offset_num = value;
			अवरोध;

		हाल 0x11:
			अगर (sensor_section == 0)
				sensor->offset_den = value;
			अवरोध;

		हाल 0x12:
			अगर (sensor_section == 0)
				sensor->slope_mult = value;
			अवरोध;

		हाल 0x13:
			अगर (sensor_section == 0)
				sensor->slope_भाग = value;
			अवरोध;
		हाल 0x32:
			अगर (thrs_section == 0) अणु
				sensor->thrs_shutकरोwn.temp = (value & 0xff0) >> 4;
				sensor->thrs_shutकरोwn.hysteresis = value & 0xf;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
nvbios_therm_fan_parse(काष्ठा nvkm_bios *bios, काष्ठा nvbios_therm_fan *fan)
अणु
	काष्ठा nvbios_therm_trip_poपूर्णांक *cur_trip = शून्य;
	u8 ver, len, i;
	u32 entry;

	uपूर्णांक8_t duty_lut[] = अणु 0, 0, 25, 0, 40, 0, 50, 0,
				75, 0, 85, 0, 100, 0, 100, 0 पूर्ण;

	i = 0;
	fan->nr_fan_trip = 0;
	fan->fan_mode = NVBIOS_THERM_FAN_OTHER;
	जबतक ((entry = nvbios_therm_entry(bios, i++, &ver, &len))) अणु
		s16 value = nvbios_rd16(bios, entry + 1);

		चयन (nvbios_rd08(bios, entry + 0)) अणु
		हाल 0x22:
			fan->min_duty = value & 0xff;
			fan->max_duty = (value & 0xff00) >> 8;
			अवरोध;
		हाल 0x24:
			fan->nr_fan_trip++;
			अगर (fan->fan_mode > NVBIOS_THERM_FAN_TRIP)
				fan->fan_mode = NVBIOS_THERM_FAN_TRIP;
			cur_trip = &fan->trip[fan->nr_fan_trip - 1];
			cur_trip->hysteresis = value & 0xf;
			cur_trip->temp = (value & 0xff0) >> 4;
			cur_trip->fan_duty = duty_lut[(value & 0xf000) >> 12];
			अवरोध;
		हाल 0x25:
			cur_trip = &fan->trip[fan->nr_fan_trip - 1];
			cur_trip->fan_duty = value;
			अवरोध;
		हाल 0x26:
			अगर (!fan->pwm_freq)
				fan->pwm_freq = value;
			अवरोध;
		हाल 0x3b:
			fan->bump_period = value;
			अवरोध;
		हाल 0x3c:
			fan->slow_करोwn_period = value;
			अवरोध;
		हाल 0x46:
			अगर (fan->fan_mode > NVBIOS_THERM_FAN_LINEAR)
				fan->fan_mode = NVBIOS_THERM_FAN_LINEAR;
			fan->linear_min_temp = nvbios_rd08(bios, entry + 1);
			fan->linear_max_temp = nvbios_rd08(bios, entry + 2);
			अवरोध;
		पूर्ण
	पूर्ण

	/* starting from fermi, fan management is always linear */
	अगर (bios->subdev.device->card_type >= NV_C0 &&
		fan->fan_mode == NVBIOS_THERM_FAN_OTHER) अणु
		fan->fan_mode = NVBIOS_THERM_FAN_LINEAR;
	पूर्ण

	वापस 0;
पूर्ण
