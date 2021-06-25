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
#समावेश <subdev/bios/perf.h>
#समावेश <subdev/pci.h>

u32
nvbios_perf_table(काष्ठा nvkm_bios *bios, u8 *ver, u8 *hdr,
		  u8 *cnt, u8 *len, u8 *snr, u8 *ssz)
अणु
	काष्ठा bit_entry bit_P;
	u32 perf = 0;

	अगर (!bit_entry(bios, 'P', &bit_P)) अणु
		अगर (bit_P.version <= 2) अणु
			perf = nvbios_rd32(bios, bit_P.offset + 0);
			अगर (perf) अणु
				*ver = nvbios_rd08(bios, perf + 0);
				*hdr = nvbios_rd08(bios, perf + 1);
				अगर (*ver >= 0x40 && *ver < 0x41) अणु
					*cnt = nvbios_rd08(bios, perf + 5);
					*len = nvbios_rd08(bios, perf + 2);
					*snr = nvbios_rd08(bios, perf + 4);
					*ssz = nvbios_rd08(bios, perf + 3);
					वापस perf;
				पूर्ण अन्यथा
				अगर (*ver >= 0x20 && *ver < 0x40) अणु
					*cnt = nvbios_rd08(bios, perf + 2);
					*len = nvbios_rd08(bios, perf + 3);
					*snr = nvbios_rd08(bios, perf + 4);
					*ssz = nvbios_rd08(bios, perf + 5);
					वापस perf;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (bios->bmp_offset) अणु
		अगर (nvbios_rd08(bios, bios->bmp_offset + 6) >= 0x25) अणु
			perf = nvbios_rd16(bios, bios->bmp_offset + 0x94);
			अगर (perf) अणु
				*hdr = nvbios_rd08(bios, perf + 0);
				*ver = nvbios_rd08(bios, perf + 1);
				*cnt = nvbios_rd08(bios, perf + 2);
				*len = nvbios_rd08(bios, perf + 3);
				*snr = 0;
				*ssz = 0;
				वापस perf;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

u32
nvbios_perf_entry(काष्ठा nvkm_bios *bios, पूर्णांक idx,
		  u8 *ver, u8 *hdr, u8 *cnt, u8 *len)
अणु
	u8  snr, ssz;
	u32 perf = nvbios_perf_table(bios, ver, hdr, cnt, len, &snr, &ssz);
	अगर (perf && idx < *cnt) अणु
		perf = perf + *hdr + (idx * (*len + (snr * ssz)));
		*hdr = *len;
		*cnt = snr;
		*len = ssz;
		वापस perf;
	पूर्ण
	वापस 0;
पूर्ण

u32
nvbios_perfEp(काष्ठा nvkm_bios *bios, पूर्णांक idx,
	      u8 *ver, u8 *hdr, u8 *cnt, u8 *len, काष्ठा nvbios_perfE *info)
अणु
	u32 perf = nvbios_perf_entry(bios, idx, ver, hdr, cnt, len);
	स_रखो(info, 0x00, माप(*info));
	info->pstate = nvbios_rd08(bios, perf + 0x00);
	चयन (!!perf * *ver) अणु
	हाल 0x12:
	हाल 0x13:
	हाल 0x14:
		info->core     = nvbios_rd32(bios, perf + 0x01) * 10;
		info->memory   = nvbios_rd32(bios, perf + 0x05) * 20;
		info->fanspeed = nvbios_rd08(bios, perf + 0x37);
		अगर (*hdr > 0x38)
			info->voltage = nvbios_rd08(bios, perf + 0x38);
		अवरोध;
	हाल 0x21:
	हाल 0x23:
	हाल 0x24:
		info->fanspeed = nvbios_rd08(bios, perf + 0x04);
		info->voltage  = nvbios_rd08(bios, perf + 0x05);
		info->shader   = nvbios_rd16(bios, perf + 0x06) * 1000;
		info->core     = info->shader + (चिन्हित अक्षर)
				 nvbios_rd08(bios, perf + 0x08) * 1000;
		चयन (bios->subdev.device->chipset) अणु
		हाल 0x49:
		हाल 0x4b:
			info->memory = nvbios_rd16(bios, perf + 0x0b) * 1000;
			अवरोध;
		शेष:
			info->memory = nvbios_rd16(bios, perf + 0x0b) * 2000;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 0x25:
		info->fanspeed = nvbios_rd08(bios, perf + 0x04);
		info->voltage  = nvbios_rd08(bios, perf + 0x05);
		info->core     = nvbios_rd16(bios, perf + 0x06) * 1000;
		info->shader   = nvbios_rd16(bios, perf + 0x0a) * 1000;
		info->memory   = nvbios_rd16(bios, perf + 0x0c) * 1000;
		अवरोध;
	हाल 0x30:
		info->script   = nvbios_rd16(bios, perf + 0x02);
		fallthrough;
	हाल 0x35:
		info->fanspeed = nvbios_rd08(bios, perf + 0x06);
		info->voltage  = nvbios_rd08(bios, perf + 0x07);
		info->core     = nvbios_rd16(bios, perf + 0x08) * 1000;
		info->shader   = nvbios_rd16(bios, perf + 0x0a) * 1000;
		info->memory   = nvbios_rd16(bios, perf + 0x0c) * 1000;
		info->vdec     = nvbios_rd16(bios, perf + 0x10) * 1000;
		info->disp     = nvbios_rd16(bios, perf + 0x14) * 1000;
		अवरोध;
	हाल 0x40:
		info->voltage  = nvbios_rd08(bios, perf + 0x02);
		चयन (nvbios_rd08(bios, perf + 0xb) & 0x3) अणु
		हाल 0:
			info->pcie_speed = NVKM_PCIE_SPEED_5_0;
			अवरोध;
		हाल 3:
		हाल 1:
			info->pcie_speed = NVKM_PCIE_SPEED_2_5;
			अवरोध;
		हाल 2:
			info->pcie_speed = NVKM_PCIE_SPEED_8_0;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		info->pcie_width = 0xff;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण
	वापस perf;
पूर्ण

u32
nvbios_perfSe(काष्ठा nvkm_bios *bios, u32 perfE, पूर्णांक idx,
	      u8 *ver, u8 *hdr, u8 cnt, u8 len)
अणु
	u32 data = 0x00000000;
	अगर (idx < cnt) अणु
		data = perfE + *hdr + (idx * len);
		*hdr = len;
	पूर्ण
	वापस data;
पूर्ण

u32
nvbios_perfSp(काष्ठा nvkm_bios *bios, u32 perfE, पूर्णांक idx,
	      u8 *ver, u8 *hdr, u8 cnt, u8 len,
	      काष्ठा nvbios_perfS *info)
अणु
	u32 data = nvbios_perfSe(bios, perfE, idx, ver, hdr, cnt, len);
	स_रखो(info, 0x00, माप(*info));
	चयन (!!data * *ver) अणु
	हाल 0x40:
		info->v40.freq = (nvbios_rd16(bios, data + 0x00) & 0x3fff) * 1000;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस data;
पूर्ण

पूर्णांक
nvbios_perf_fan_parse(काष्ठा nvkm_bios *bios,
		      काष्ठा nvbios_perf_fan *fan)
अणु
	u8  ver, hdr, cnt, len, snr, ssz;
	u32 perf = nvbios_perf_table(bios, &ver, &hdr, &cnt, &len, &snr, &ssz);
	अगर (!perf)
		वापस -ENODEV;

	अगर (ver >= 0x20 && ver < 0x40 && hdr > 6)
		fan->pwm_भागisor = nvbios_rd16(bios, perf + 6);
	अन्यथा
		fan->pwm_भागisor = 0;

	वापस 0;
पूर्ण
