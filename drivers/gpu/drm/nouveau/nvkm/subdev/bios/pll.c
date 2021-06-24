<शैली गुरु>
/*
 * Copyright 2005-2006 Erik Waling
 * Copyright 2006 Stephane Marchesin
 * Copyright 2007-2009 Stuart Bennett
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
 * THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/bit.h>
#समावेश <subdev/bios/bmp.h>
#समावेश <subdev/bios/pll.h>
#समावेश <subdev/vga.h>


काष्ठा pll_mapping अणु
	u8  type;
	u32 reg;
पूर्ण;

अटल काष्ठा pll_mapping
nv04_pll_mapping[] = अणु
	अणु PLL_CORE  , 0x680500 पूर्ण,
	अणु PLL_MEMORY, 0x680504 पूर्ण,
	अणु PLL_VPLL0 , 0x680508 पूर्ण,
	अणु PLL_VPLL1 , 0x680520 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा pll_mapping
nv40_pll_mapping[] = अणु
	अणु PLL_CORE  , 0x004000 पूर्ण,
	अणु PLL_MEMORY, 0x004020 पूर्ण,
	अणु PLL_VPLL0 , 0x680508 पूर्ण,
	अणु PLL_VPLL1 , 0x680520 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा pll_mapping
nv50_pll_mapping[] = अणु
	अणु PLL_CORE  , 0x004028 पूर्ण,
	अणु PLL_SHADER, 0x004020 पूर्ण,
	अणु PLL_UNK03 , 0x004000 पूर्ण,
	अणु PLL_MEMORY, 0x004008 पूर्ण,
	अणु PLL_UNK40 , 0x00e810 पूर्ण,
	अणु PLL_UNK41 , 0x00e818 पूर्ण,
	अणु PLL_UNK42 , 0x00e824 पूर्ण,
	अणु PLL_VPLL0 , 0x614100 पूर्ण,
	अणु PLL_VPLL1 , 0x614900 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा pll_mapping
g84_pll_mapping[] = अणु
	अणु PLL_CORE  , 0x004028 पूर्ण,
	अणु PLL_SHADER, 0x004020 पूर्ण,
	अणु PLL_MEMORY, 0x004008 पूर्ण,
	अणु PLL_VDEC  , 0x004030 पूर्ण,
	अणु PLL_UNK41 , 0x00e818 पूर्ण,
	अणु PLL_VPLL0 , 0x614100 पूर्ण,
	अणु PLL_VPLL1 , 0x614900 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल u32
pll_limits_table(काष्ठा nvkm_bios *bios, u8 *ver, u8 *hdr, u8 *cnt, u8 *len)
अणु
	काष्ठा bit_entry bit_C;
	u32 data = 0x0000;

	अगर (!bit_entry(bios, 'C', &bit_C)) अणु
		अगर (bit_C.version == 1 && bit_C.length >= 10)
			data = nvbios_rd16(bios, bit_C.offset + 8);
		अगर (bit_C.version == 2 && bit_C.length >= 4)
			data = nvbios_rd32(bios, bit_C.offset + 0);
		अगर (data) अणु
			*ver = nvbios_rd08(bios, data + 0);
			*hdr = nvbios_rd08(bios, data + 1);
			*len = nvbios_rd08(bios, data + 2);
			*cnt = nvbios_rd08(bios, data + 3);
			वापस data;
		पूर्ण
	पूर्ण

	अगर (bmp_version(bios) >= 0x0524) अणु
		data = nvbios_rd16(bios, bios->bmp_offset + 142);
		अगर (data) अणु
			*ver = nvbios_rd08(bios, data + 0);
			*hdr = 1;
			*cnt = 1;
			*len = 0x18;
			वापस data;
		पूर्ण
	पूर्ण

	*ver = 0x00;
	वापस data;
पूर्ण

अटल काष्ठा pll_mapping *
pll_map(काष्ठा nvkm_bios *bios)
अणु
	काष्ठा nvkm_device *device = bios->subdev.device;
	चयन (device->card_type) अणु
	हाल NV_04:
	हाल NV_10:
	हाल NV_11:
	हाल NV_20:
	हाल NV_30:
		वापस nv04_pll_mapping;
	हाल NV_40:
		वापस nv40_pll_mapping;
	हाल NV_50:
		अगर (device->chipset == 0x50)
			वापस nv50_pll_mapping;
		अन्यथा
		अगर (device->chipset <  0xa3 ||
		    device->chipset == 0xaa ||
		    device->chipset == 0xac)
			वापस g84_pll_mapping;
		fallthrough;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल u32
pll_map_reg(काष्ठा nvkm_bios *bios, u32 reg, u32 *type, u8 *ver, u8 *len)
अणु
	काष्ठा pll_mapping *map;
	u8  hdr, cnt;
	u32 data;

	data = pll_limits_table(bios, ver, &hdr, &cnt, len);
	अगर (data && *ver >= 0x30) अणु
		data += hdr;
		जबतक (cnt--) अणु
			अगर (nvbios_rd32(bios, data + 3) == reg) अणु
				*type = nvbios_rd08(bios, data + 0);
				वापस data;
			पूर्ण
			data += *len;
		पूर्ण
		वापस 0x0000;
	पूर्ण

	map = pll_map(bios);
	जबतक (map && map->reg) अणु
		अगर (map->reg == reg && *ver >= 0x20) अणु
			u32 addr = (data += hdr);
			*type = map->type;
			जबतक (cnt--) अणु
				अगर (nvbios_rd32(bios, data) == map->reg)
					वापस data;
				data += *len;
			पूर्ण
			वापस addr;
		पूर्ण अन्यथा
		अगर (map->reg == reg) अणु
			*type = map->type;
			वापस data + 1;
		पूर्ण
		map++;
	पूर्ण

	वापस 0x0000;
पूर्ण

अटल u32
pll_map_type(काष्ठा nvkm_bios *bios, u8 type, u32 *reg, u8 *ver, u8 *len)
अणु
	काष्ठा pll_mapping *map;
	u8  hdr, cnt;
	u32 data;

	data = pll_limits_table(bios, ver, &hdr, &cnt, len);
	अगर (data && *ver >= 0x30) अणु
		data += hdr;
		जबतक (cnt--) अणु
			अगर (nvbios_rd08(bios, data + 0) == type) अणु
				अगर (*ver < 0x50)
					*reg = nvbios_rd32(bios, data + 3);
				अन्यथा
					*reg = 0;
				वापस data;
			पूर्ण
			data += *len;
		पूर्ण
		वापस 0x0000;
	पूर्ण

	map = pll_map(bios);
	जबतक (map && map->reg) अणु
		अगर (map->type == type && *ver >= 0x20) अणु
			u32 addr = (data += hdr);
			*reg = map->reg;
			जबतक (cnt--) अणु
				अगर (nvbios_rd32(bios, data) == map->reg)
					वापस data;
				data += *len;
			पूर्ण
			वापस addr;
		पूर्ण अन्यथा
		अगर (map->type == type) अणु
			*reg = map->reg;
			वापस data + 1;
		पूर्ण
		map++;
	पूर्ण

	वापस 0x0000;
पूर्ण

पूर्णांक
nvbios_pll_parse(काष्ठा nvkm_bios *bios, u32 type, काष्ठा nvbios_pll *info)
अणु
	काष्ठा nvkm_subdev *subdev = &bios->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u8  ver, len;
	u32 reg = type;
	u32 data;

	अगर (type > PLL_MAX) अणु
		reg  = type;
		data = pll_map_reg(bios, reg, &type, &ver, &len);
	पूर्ण अन्यथा अणु
		data = pll_map_type(bios, type, &reg, &ver, &len);
	पूर्ण

	अगर (ver && !data)
		वापस -ENOENT;

	स_रखो(info, 0, माप(*info));
	info->type = type;
	info->reg = reg;

	चयन (ver) अणु
	हाल 0x00:
		अवरोध;
	हाल 0x10:
	हाल 0x11:
		info->vco1.min_freq = nvbios_rd32(bios, data + 0);
		info->vco1.max_freq = nvbios_rd32(bios, data + 4);
		info->vco2.min_freq = nvbios_rd32(bios, data + 8);
		info->vco2.max_freq = nvbios_rd32(bios, data + 12);
		info->vco1.min_inputfreq = nvbios_rd32(bios, data + 16);
		info->vco2.min_inputfreq = nvbios_rd32(bios, data + 20);
		info->vco1.max_inputfreq = पूर्णांक_उच्च;
		info->vco2.max_inputfreq = पूर्णांक_उच्च;

		info->max_p = 0x7;
		info->max_p_usable = 0x6;

		/* these values taken from nv30/31/36 */
		चयन (bios->version.chip) अणु
		हाल 0x36:
			info->vco1.min_n = 0x5;
			अवरोध;
		शेष:
			info->vco1.min_n = 0x1;
			अवरोध;
		पूर्ण
		info->vco1.max_n = 0xff;
		info->vco1.min_m = 0x1;
		info->vco1.max_m = 0xd;

		/*
		 * On nv30, 31, 36 (i.e. all cards with two stage PLLs with this
		 * table version (apart from nv35)), N2 is compared to
		 * maxN2 (0x46) and 10 * maxM2 (0x4), so set maxN2 to 0x28 and
		 * save a comparison
		 */
		info->vco2.min_n = 0x4;
		चयन (bios->version.chip) अणु
		हाल 0x30:
		हाल 0x35:
			info->vco2.max_n = 0x1f;
			अवरोध;
		शेष:
			info->vco2.max_n = 0x28;
			अवरोध;
		पूर्ण
		info->vco2.min_m = 0x1;
		info->vco2.max_m = 0x4;
		अवरोध;
	हाल 0x20:
	हाल 0x21:
		info->vco1.min_freq = nvbios_rd16(bios, data + 4) * 1000;
		info->vco1.max_freq = nvbios_rd16(bios, data + 6) * 1000;
		info->vco2.min_freq = nvbios_rd16(bios, data + 8) * 1000;
		info->vco2.max_freq = nvbios_rd16(bios, data + 10) * 1000;
		info->vco1.min_inputfreq = nvbios_rd16(bios, data + 12) * 1000;
		info->vco2.min_inputfreq = nvbios_rd16(bios, data + 14) * 1000;
		info->vco1.max_inputfreq = nvbios_rd16(bios, data + 16) * 1000;
		info->vco2.max_inputfreq = nvbios_rd16(bios, data + 18) * 1000;
		info->vco1.min_n = nvbios_rd08(bios, data + 20);
		info->vco1.max_n = nvbios_rd08(bios, data + 21);
		info->vco1.min_m = nvbios_rd08(bios, data + 22);
		info->vco1.max_m = nvbios_rd08(bios, data + 23);
		info->vco2.min_n = nvbios_rd08(bios, data + 24);
		info->vco2.max_n = nvbios_rd08(bios, data + 25);
		info->vco2.min_m = nvbios_rd08(bios, data + 26);
		info->vco2.max_m = nvbios_rd08(bios, data + 27);

		info->max_p = nvbios_rd08(bios, data + 29);
		info->max_p_usable = info->max_p;
		अगर (bios->version.chip < 0x60)
			info->max_p_usable = 0x6;
		info->bias_p = nvbios_rd08(bios, data + 30);

		अगर (len > 0x22)
			info->refclk = nvbios_rd32(bios, data + 31);
		अवरोध;
	हाल 0x30:
		data = nvbios_rd16(bios, data + 1);

		info->vco1.min_freq = nvbios_rd16(bios, data + 0) * 1000;
		info->vco1.max_freq = nvbios_rd16(bios, data + 2) * 1000;
		info->vco2.min_freq = nvbios_rd16(bios, data + 4) * 1000;
		info->vco2.max_freq = nvbios_rd16(bios, data + 6) * 1000;
		info->vco1.min_inputfreq = nvbios_rd16(bios, data + 8) * 1000;
		info->vco2.min_inputfreq = nvbios_rd16(bios, data + 10) * 1000;
		info->vco1.max_inputfreq = nvbios_rd16(bios, data + 12) * 1000;
		info->vco2.max_inputfreq = nvbios_rd16(bios, data + 14) * 1000;
		info->vco1.min_n = nvbios_rd08(bios, data + 16);
		info->vco1.max_n = nvbios_rd08(bios, data + 17);
		info->vco1.min_m = nvbios_rd08(bios, data + 18);
		info->vco1.max_m = nvbios_rd08(bios, data + 19);
		info->vco2.min_n = nvbios_rd08(bios, data + 20);
		info->vco2.max_n = nvbios_rd08(bios, data + 21);
		info->vco2.min_m = nvbios_rd08(bios, data + 22);
		info->vco2.max_m = nvbios_rd08(bios, data + 23);
		info->max_p_usable = info->max_p = nvbios_rd08(bios, data + 25);
		info->bias_p = nvbios_rd08(bios, data + 27);
		info->refclk = nvbios_rd32(bios, data + 28);
		अवरोध;
	हाल 0x40:
		info->refclk = nvbios_rd16(bios, data + 9) * 1000;
		data = nvbios_rd16(bios, data + 1);

		info->vco1.min_freq = nvbios_rd16(bios, data + 0) * 1000;
		info->vco1.max_freq = nvbios_rd16(bios, data + 2) * 1000;
		info->vco1.min_inputfreq = nvbios_rd16(bios, data + 4) * 1000;
		info->vco1.max_inputfreq = nvbios_rd16(bios, data + 6) * 1000;
		info->vco1.min_m = nvbios_rd08(bios, data + 8);
		info->vco1.max_m = nvbios_rd08(bios, data + 9);
		info->vco1.min_n = nvbios_rd08(bios, data + 10);
		info->vco1.max_n = nvbios_rd08(bios, data + 11);
		info->min_p = nvbios_rd08(bios, data + 12);
		info->max_p = nvbios_rd08(bios, data + 13);
		अवरोध;
	हाल 0x50:
		info->refclk = nvbios_rd16(bios, data + 1) * 1000;
		/* info->refclk_alt = nvbios_rd16(bios, data + 3) * 1000; */
		info->vco1.min_freq = nvbios_rd16(bios, data + 5) * 1000;
		info->vco1.max_freq = nvbios_rd16(bios, data + 7) * 1000;
		info->vco1.min_inputfreq = nvbios_rd16(bios, data + 9) * 1000;
		info->vco1.max_inputfreq = nvbios_rd16(bios, data + 11) * 1000;
		info->vco1.min_m = nvbios_rd08(bios, data + 13);
		info->vco1.max_m = nvbios_rd08(bios, data + 14);
		info->vco1.min_n = nvbios_rd08(bios, data + 15);
		info->vco1.max_n = nvbios_rd08(bios, data + 16);
		info->min_p = nvbios_rd08(bios, data + 17);
		info->max_p = nvbios_rd08(bios, data + 18);
		अवरोध;
	शेष:
		nvkm_error(subdev, "unknown pll limits version 0x%02x\n", ver);
		वापस -EINVAL;
	पूर्ण

	अगर (!info->refclk) अणु
		info->refclk = device->crystal;
		अगर (bios->version.chip == 0x51) अणु
			u32 sel_clk = nvkm_rd32(device, 0x680524);
			अगर ((info->reg == 0x680508 && sel_clk & 0x20) ||
			    (info->reg == 0x680520 && sel_clk & 0x80)) अणु
				अगर (nvkm_rdvgac(device, 0, 0x27) < 0xa3)
					info->refclk = 200000;
				अन्यथा
					info->refclk = 25000;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * By now any valid limit table ought to have set a max frequency क्रम
	 * vco1, so अगर it's zero it's either a pre limit table bios, or one
	 * with an empty limit table (seen on nv18)
	 */
	अगर (!info->vco1.max_freq) अणु
		info->vco1.max_freq = nvbios_rd32(bios, bios->bmp_offset + 67);
		info->vco1.min_freq = nvbios_rd32(bios, bios->bmp_offset + 71);
		अगर (bmp_version(bios) < 0x0506) अणु
			info->vco1.max_freq = 256000;
			info->vco1.min_freq = 128000;
		पूर्ण

		info->vco1.min_inputfreq = 0;
		info->vco1.max_inputfreq = पूर्णांक_उच्च;
		info->vco1.min_n = 0x1;
		info->vco1.max_n = 0xff;
		info->vco1.min_m = 0x1;

		अगर (device->crystal == 13500) अणु
			/* nv05 करोes this, nv11 करोesn't, nv10 unknown */
			अगर (bios->version.chip < 0x11)
				info->vco1.min_m = 0x7;
			info->vco1.max_m = 0xd;
		पूर्ण अन्यथा अणु
			अगर (bios->version.chip < 0x11)
				info->vco1.min_m = 0x8;
			info->vco1.max_m = 0xe;
		पूर्ण

		अगर (bios->version.chip <  0x17 ||
		    bios->version.chip == 0x1a ||
		    bios->version.chip == 0x20)
			info->max_p = 4;
		अन्यथा
			info->max_p = 5;
		info->max_p_usable = info->max_p;
	पूर्ण

	वापस 0;
पूर्ण
