<शैली गुरु>
/*
 * Copyright 2015 Martin Peres
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
#समावेश <subdev/bios/extdev.h>
#समावेश <subdev/bios/iccsense.h>

अटल u32
nvbios_iccsense_table(काष्ठा nvkm_bios *bios, u8 *ver, u8 *hdr, u8 *cnt,
		      u8 *len)
अणु
	काष्ठा bit_entry bit_P;
	u32 iccsense;

	अगर (bit_entry(bios, 'P', &bit_P) || bit_P.version != 2 ||
	    bit_P.length < 0x2c)
		वापस 0;

	iccsense = nvbios_rd32(bios, bit_P.offset + 0x28);
	अगर (!iccsense)
		वापस 0;

	*ver = nvbios_rd08(bios, iccsense + 0);
	चयन (*ver) अणु
	हाल 0x10:
	हाल 0x20:
		*hdr = nvbios_rd08(bios, iccsense + 1);
		*len = nvbios_rd08(bios, iccsense + 2);
		*cnt = nvbios_rd08(bios, iccsense + 3);
		वापस iccsense;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
nvbios_iccsense_parse(काष्ठा nvkm_bios *bios, काष्ठा nvbios_iccsense *iccsense)
अणु
	काष्ठा nvkm_subdev *subdev = &bios->subdev;
	u8 ver, hdr, cnt, len, i;
	u32 table, entry;

	table = nvbios_iccsense_table(bios, &ver, &hdr, &cnt, &len);
	अगर (!table || !cnt)
		वापस -EINVAL;

	अगर (ver != 0x10 && ver != 0x20) अणु
		nvkm_error(subdev, "ICCSENSE version 0x%02x unknown\n", ver);
		वापस -EINVAL;
	पूर्ण

	iccsense->nr_entry = cnt;
	iccsense->rail = kदो_स्मृति_array(cnt, माप(काष्ठा pwr_rail_t),
				       GFP_KERNEL);
	अगर (!iccsense->rail)
		वापस -ENOMEM;

	क्रम (i = 0; i < cnt; ++i) अणु
		काष्ठा nvbios_extdev_func extdev;
		काष्ठा pwr_rail_t *rail = &iccsense->rail[i];
		u8 res_start = 0;
		पूर्णांक r;

		entry = table + hdr + i * len;

		चयन(ver) अणु
		हाल 0x10:
			अगर ((nvbios_rd08(bios, entry + 0x1) & 0xf8) == 0xf8)
				rail->mode = 1;
			अन्यथा
				rail->mode = 0;
			rail->extdev_id = nvbios_rd08(bios, entry + 0x2);
			res_start = 0x3;
			अवरोध;
		हाल 0x20:
			rail->mode = nvbios_rd08(bios, entry);
			rail->extdev_id = nvbios_rd08(bios, entry + 0x1);
			res_start = 0x5;
			अवरोध;
		पूर्ण

		अगर (nvbios_extdev_parse(bios, rail->extdev_id, &extdev))
			जारी;

		चयन (extdev.type) अणु
		हाल NVBIOS_EXTDEV_INA209:
		हाल NVBIOS_EXTDEV_INA219:
			rail->resistor_count = 1;
			अवरोध;
		हाल NVBIOS_EXTDEV_INA3221:
			rail->resistor_count = 3;
			अवरोध;
		शेष:
			rail->resistor_count = 0;
			अवरोध;
		पूर्ण

		क्रम (r = 0; r < rail->resistor_count; ++r) अणु
			rail->resistors[r].mohm = nvbios_rd08(bios, entry + res_start + r * 2);
			rail->resistors[r].enabled = !(nvbios_rd08(bios, entry + res_start + r * 2 + 1) & 0x40);
		पूर्ण
		rail->config = nvbios_rd16(bios, entry + res_start + rail->resistor_count * 2);
	पूर्ण

	वापस 0;
पूर्ण
