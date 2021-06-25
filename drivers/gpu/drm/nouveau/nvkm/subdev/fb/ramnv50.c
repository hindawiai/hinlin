<शैली गुरु>
/*
 * Copyright 2013 Red Hat Inc.
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
#घोषणा nv50_ram(p) container_of((p), काष्ठा nv50_ram, base)
#समावेश "ram.h"
#समावेश "ramseq.h"
#समावेश "nv50.h"

#समावेश <core/option.h>
#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/perf.h>
#समावेश <subdev/bios/pll.h>
#समावेश <subdev/bios/rammap.h>
#समावेश <subdev/bios/timing.h>
#समावेश <subdev/clk/pll.h>
#समावेश <subdev/gpपन.स>

काष्ठा nv50_ramseq अणु
	काष्ठा hwsq base;
	काष्ठा hwsq_reg r_0x002504;
	काष्ठा hwsq_reg r_0x004008;
	काष्ठा hwsq_reg r_0x00400c;
	काष्ठा hwsq_reg r_0x00c040;
	काष्ठा hwsq_reg r_0x100200;
	काष्ठा hwsq_reg r_0x100210;
	काष्ठा hwsq_reg r_0x10021c;
	काष्ठा hwsq_reg r_0x1002d0;
	काष्ठा hwsq_reg r_0x1002d4;
	काष्ठा hwsq_reg r_0x1002dc;
	काष्ठा hwsq_reg r_0x10053c;
	काष्ठा hwsq_reg r_0x1005a0;
	काष्ठा hwsq_reg r_0x1005a4;
	काष्ठा hwsq_reg r_0x100710;
	काष्ठा hwsq_reg r_0x100714;
	काष्ठा hwsq_reg r_0x100718;
	काष्ठा hwsq_reg r_0x10071c;
	काष्ठा hwsq_reg r_0x100da0;
	काष्ठा hwsq_reg r_0x100e20;
	काष्ठा hwsq_reg r_0x100e24;
	काष्ठा hwsq_reg r_0x611200;
	काष्ठा hwsq_reg r_timing[9];
	काष्ठा hwsq_reg r_mr[4];
	काष्ठा hwsq_reg r_gpio[4];
पूर्ण;

काष्ठा nv50_ram अणु
	काष्ठा nvkm_ram base;
	काष्ठा nv50_ramseq hwsq;
पूर्ण;

#घोषणा T(t) cfg->timing_10_##t
अटल पूर्णांक
nv50_ram_timing_calc(काष्ठा nv50_ram *ram, u32 *timing)
अणु
	काष्ठा nvbios_ramcfg *cfg = &ram->base.target.bios;
	काष्ठा nvkm_subdev *subdev = &ram->base.fb->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 cur2, cur4, cur7, cur8;
	u8 unkt3b;

	cur2 = nvkm_rd32(device, 0x100228);
	cur4 = nvkm_rd32(device, 0x100230);
	cur7 = nvkm_rd32(device, 0x10023c);
	cur8 = nvkm_rd32(device, 0x100240);

	चयन ((!T(CWL)) * ram->base.type) अणु
	हाल NVKM_RAM_TYPE_DDR2:
		T(CWL) = T(CL) - 1;
		अवरोध;
	हाल NVKM_RAM_TYPE_GDDR3:
		T(CWL) = ((cur2 & 0xff000000) >> 24) + 1;
		अवरोध;
	पूर्ण

	/* XXX: N=1 is not proper statistics */
	अगर (device->chipset == 0xa0) अणु
		unkt3b = 0x19 + ram->base.next->bios.rammap_00_16_40;
		timing[6] = (0x2d + T(CL) - T(CWL) +
				ram->base.next->bios.rammap_00_16_40) << 16 |
			    T(CWL) << 8 |
			    (0x2f + T(CL) - T(CWL));
	पूर्ण अन्यथा अणु
		unkt3b = 0x16;
		timing[6] = (0x2b + T(CL) - T(CWL)) << 16 |
			    max_t(s8, T(CWL) - 2, 1) << 8 |
			    (0x2e + T(CL) - T(CWL));
	पूर्ण

	timing[0] = (T(RP) << 24 | T(RAS) << 16 | T(RFC) << 8 | T(RC));
	timing[1] = (T(WR) + 1 + T(CWL)) << 24 |
		    max_t(u8, T(18), 1) << 16 |
		    (T(WTR) + 1 + T(CWL)) << 8 |
		    (3 + T(CL) - T(CWL));
	timing[2] = (T(CWL) - 1) << 24 |
		    (T(RRD) << 16) |
		    (T(RCDWR) << 8) |
		    T(RCDRD);
	timing[3] = (unkt3b - 2 + T(CL)) << 24 |
		    unkt3b << 16 |
		    (T(CL) - 1) << 8 |
		    (T(CL) - 1);
	timing[4] = (cur4 & 0xffff0000) |
		    T(13) << 8 |
		    T(13);
	timing[5] = T(RFC) << 24 |
		    max_t(u8, T(RCDRD), T(RCDWR)) << 16 |
		    T(RP);
	/* Timing 6 is alपढ़ोy करोne above */
	timing[7] = (cur7 & 0xff00ffff) | (T(CL) - 1) << 16;
	timing[8] = (cur8 & 0xffffff00);

	/* XXX: P.version == 1 only has DDR2 and GDDR3? */
	अगर (ram->base.type == NVKM_RAM_TYPE_DDR2) अणु
		timing[5] |= (T(CL) + 3) << 8;
		timing[8] |= (T(CL) - 4);
	पूर्ण अन्यथा
	अगर (ram->base.type == NVKM_RAM_TYPE_GDDR3) अणु
		timing[5] |= (T(CL) + 2) << 8;
		timing[8] |= (T(CL) - 2);
	पूर्ण

	nvkm_debug(subdev, " 220: %08x %08x %08x %08x\n",
		   timing[0], timing[1], timing[2], timing[3]);
	nvkm_debug(subdev, " 230: %08x %08x %08x %08x\n",
		   timing[4], timing[5], timing[6], timing[7]);
	nvkm_debug(subdev, " 240: %08x\n", timing[8]);
	वापस 0;
पूर्ण

अटल पूर्णांक
nv50_ram_timing_पढ़ो(काष्ठा nv50_ram *ram, u32 *timing)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा nvbios_ramcfg *cfg = &ram->base.target.bios;
	काष्ठा nvkm_subdev *subdev = &ram->base.fb->subdev;
	काष्ठा nvkm_device *device = subdev->device;

	क्रम (i = 0; i <= 8; i++)
		timing[i] = nvkm_rd32(device, 0x100220 + (i * 4));

	/* Derive the bare minimum क्रम the MR calculation to succeed */
	cfg->timing_ver = 0x10;
	T(CL) = (timing[3] & 0xff) + 1;

	चयन (ram->base.type) अणु
	हाल NVKM_RAM_TYPE_DDR2:
		T(CWL) = T(CL) - 1;
		अवरोध;
	हाल NVKM_RAM_TYPE_GDDR3:
		T(CWL) = ((timing[2] & 0xff000000) >> 24) + 1;
		अवरोध;
	शेष:
		वापस -ENOSYS;
	पूर्ण

	T(WR) = ((timing[1] >> 24) & 0xff) - 1 - T(CWL);

	वापस 0;
पूर्ण
#अघोषित T

अटल व्योम
nvkm_sddr2_dll_reset(काष्ठा nv50_ramseq *hwsq)
अणु
	ram_mask(hwsq, mr[0], 0x100, 0x100);
	ram_mask(hwsq, mr[0], 0x100, 0x000);
	ram_nsec(hwsq, 24000);
पूर्ण

अटल व्योम
nv50_ram_gpio(काष्ठा nv50_ramseq *hwsq, u8 tag, u32 val)
अणु
	काष्ठा nvkm_gpio *gpio = hwsq->base.subdev->device->gpio;
	काष्ठा dcb_gpio_func func;
	u32 reg, sh, gpio_val;
	पूर्णांक ret;

	अगर (nvkm_gpio_get(gpio, 0, tag, DCB_GPIO_UNUSED) != val) अणु
		ret = nvkm_gpio_find(gpio, 0, tag, DCB_GPIO_UNUSED, &func);
		अगर (ret)
			वापस;

		reg = func.line >> 3;
		sh = (func.line & 0x7) << 2;
		gpio_val = ram_rd32(hwsq, gpio[reg]);

		अगर (gpio_val & (8 << sh))
			val = !val;
		अगर (!(func.log[1] & 1))
			val = !val;

		ram_mask(hwsq, gpio[reg], (0x3 << sh), ((val | 0x2) << sh));
		ram_nsec(hwsq, 20000);
	पूर्ण
पूर्ण

अटल पूर्णांक
nv50_ram_calc(काष्ठा nvkm_ram *base, u32 freq)
अणु
	काष्ठा nv50_ram *ram = nv50_ram(base);
	काष्ठा nv50_ramseq *hwsq = &ram->hwsq;
	काष्ठा nvkm_subdev *subdev = &ram->base.fb->subdev;
	काष्ठा nvkm_bios *bios = subdev->device->bios;
	काष्ठा nvbios_perfE perfE;
	काष्ठा nvbios_pll mpll;
	काष्ठा nvkm_ram_data *next;
	u8  ver, hdr, cnt, len, strap, size;
	u32 data;
	u32 r100da0, r004008, unk710, unk714, unk718, unk71c;
	पूर्णांक N1, M1, N2, M2, P;
	पूर्णांक ret, i;
	u32 timing[9];

	next = &ram->base.target;
	next->freq = freq;
	ram->base.next = next;

	/* lookup बंदst matching perक्रमmance table entry क्रम frequency */
	i = 0;
	करो अणु
		data = nvbios_perfEp(bios, i++, &ver, &hdr, &cnt,
				     &size, &perfE);
		अगर (!data || (ver < 0x25 || ver >= 0x40) ||
		    (size < 2)) अणु
			nvkm_error(subdev, "invalid/missing perftab entry\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण जबतक (perfE.memory < freq);

	nvbios_rammapEp_from_perf(bios, data, hdr, &next->bios);

	/* locate specअगरic data set क्रम the attached memory */
	strap = nvbios_ramcfg_index(subdev);
	अगर (strap >= cnt) अणु
		nvkm_error(subdev, "invalid ramcfg strap\n");
		वापस -EINVAL;
	पूर्ण

	data = nvbios_rammapSp_from_perf(bios, data + hdr, size, strap,
			&next->bios);
	अगर (!data) अणु
		nvkm_error(subdev, "invalid/missing rammap entry ");
		वापस -EINVAL;
	पूर्ण

	/* lookup memory timings, अगर bios says they're present */
	अगर (next->bios.ramcfg_timing != 0xff) अणु
		data = nvbios_timingEp(bios, next->bios.ramcfg_timing,
					&ver, &hdr, &cnt, &len, &next->bios);
		अगर (!data || ver != 0x10 || hdr < 0x12) अणु
			nvkm_error(subdev, "invalid/missing timing entry "
				 "%02x %04x %02x %02x\n",
				 strap, data, ver, hdr);
			वापस -EINVAL;
		पूर्ण
		nv50_ram_timing_calc(ram, timing);
	पूर्ण अन्यथा अणु
		nv50_ram_timing_पढ़ो(ram, timing);
	पूर्ण

	ret = ram_init(hwsq, subdev);
	अगर (ret)
		वापस ret;

	/* Determine ram-specअगरic MR values */
	ram->base.mr[0] = ram_rd32(hwsq, mr[0]);
	ram->base.mr[1] = ram_rd32(hwsq, mr[1]);
	ram->base.mr[2] = ram_rd32(hwsq, mr[2]);

	चयन (ram->base.type) अणु
	हाल NVKM_RAM_TYPE_GDDR3:
		ret = nvkm_gddr3_calc(&ram->base);
		अवरोध;
	शेष:
		ret = -ENOSYS;
		अवरोध;
	पूर्ण

	अगर (ret) अणु
		nvkm_error(subdev, "Could not calculate MR\n");
		वापस ret;
	पूर्ण

	अगर (subdev->device->chipset <= 0x96 && !next->bios.ramcfg_00_03_02)
		ram_mask(hwsq, 0x100710, 0x00000200, 0x00000000);

	/* Always disable this bit during reघड़ी */
	ram_mask(hwsq, 0x100200, 0x00000800, 0x00000000);

	ram_रुको_vblank(hwsq);
	ram_wr32(hwsq, 0x611200, 0x00003300);
	ram_wr32(hwsq, 0x002504, 0x00000001); /* block fअगरo */
	ram_nsec(hwsq, 8000);
	ram_setf(hwsq, 0x10, 0x00); /* disable fb */
	ram_रुको(hwsq, 0x00, 0x01); /* रुको क्रम fb disabled */
	ram_nsec(hwsq, 2000);

	अगर (next->bios.timing_10_ODT)
		nv50_ram_gpio(hwsq, 0x2e, 1);

	ram_wr32(hwsq, 0x1002d4, 0x00000001); /* preअक्षरge */
	ram_wr32(hwsq, 0x1002d0, 0x00000001); /* refresh */
	ram_wr32(hwsq, 0x1002d0, 0x00000001); /* refresh */
	ram_wr32(hwsq, 0x100210, 0x00000000); /* disable स्वतः-refresh */
	ram_wr32(hwsq, 0x1002dc, 0x00000001); /* enable self-refresh */

	ret = nvbios_pll_parse(bios, 0x004008, &mpll);
	mpll.vco2.max_freq = 0;
	अगर (ret >= 0) अणु
		ret = nv04_pll_calc(subdev, &mpll, freq,
				    &N1, &M1, &N2, &M2, &P);
		अगर (ret <= 0)
			ret = -EINVAL;
	पूर्ण

	अगर (ret < 0)
		वापस ret;

	/* XXX: 750MHz seems rather arbitrary */
	अगर (freq <= 750000) अणु
		r100da0 = 0x00000010;
		r004008 = 0x90000000;
	पूर्ण अन्यथा अणु
		r100da0 = 0x00000000;
		r004008 = 0x80000000;
	पूर्ण

	r004008 |= (mpll.bias_p << 19) | (P << 22) | (P << 16);

	ram_mask(hwsq, 0x00c040, 0xc000c000, 0x0000c000);
	/* XXX: Is rammap_00_16_40 the DLL bit we've seen in GT215? Why करोes
	 * it have a dअगरferent rammap bit from DLLoff? */
	ram_mask(hwsq, 0x004008, 0x00004200, 0x00000200 |
			next->bios.rammap_00_16_40 << 14);
	ram_mask(hwsq, 0x00400c, 0x0000ffff, (N1 << 8) | M1);
	ram_mask(hwsq, 0x004008, 0x91ff0000, r004008);

	/* XXX: GDDR3 only? */
	अगर (subdev->device->chipset >= 0x92)
		ram_wr32(hwsq, 0x100da0, r100da0);

	nv50_ram_gpio(hwsq, 0x18, !next->bios.ramcfg_FBVDDQ);
	ram_nsec(hwsq, 64000); /*XXX*/
	ram_nsec(hwsq, 32000); /*XXX*/

	ram_mask(hwsq, 0x004008, 0x00002200, 0x00002000);

	ram_wr32(hwsq, 0x1002dc, 0x00000000); /* disable self-refresh */
	ram_wr32(hwsq, 0x1002d4, 0x00000001); /* disable self-refresh */
	ram_wr32(hwsq, 0x100210, 0x80000000); /* enable स्वतः-refresh */

	ram_nsec(hwsq, 12000);

	चयन (ram->base.type) अणु
	हाल NVKM_RAM_TYPE_DDR2:
		ram_nuke(hwsq, mr[0]); /* क्रमce update */
		ram_mask(hwsq, mr[0], 0x000, 0x000);
		अवरोध;
	हाल NVKM_RAM_TYPE_GDDR3:
		ram_nuke(hwsq, mr[1]); /* क्रमce update */
		ram_wr32(hwsq, mr[1], ram->base.mr[1]);
		ram_nuke(hwsq, mr[0]); /* क्रमce update */
		ram_wr32(hwsq, mr[0], ram->base.mr[0]);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ram_mask(hwsq, timing[3], 0xffffffff, timing[3]);
	ram_mask(hwsq, timing[1], 0xffffffff, timing[1]);
	ram_mask(hwsq, timing[6], 0xffffffff, timing[6]);
	ram_mask(hwsq, timing[7], 0xffffffff, timing[7]);
	ram_mask(hwsq, timing[8], 0xffffffff, timing[8]);
	ram_mask(hwsq, timing[0], 0xffffffff, timing[0]);
	ram_mask(hwsq, timing[2], 0xffffffff, timing[2]);
	ram_mask(hwsq, timing[4], 0xffffffff, timing[4]);
	ram_mask(hwsq, timing[5], 0xffffffff, timing[5]);

	अगर (!next->bios.ramcfg_00_03_02)
		ram_mask(hwsq, 0x10021c, 0x00010000, 0x00000000);
	ram_mask(hwsq, 0x100200, 0x00001000, !next->bios.ramcfg_00_04_02 << 12);

	/* XXX: A lot of this could be "chipset"/"ram type" specअगरic stuff */
	unk710  = ram_rd32(hwsq, 0x100710) & ~0x00000100;
	unk714  = ram_rd32(hwsq, 0x100714) & ~0xf0000020;
	unk718  = ram_rd32(hwsq, 0x100718) & ~0x00000100;
	unk71c  = ram_rd32(hwsq, 0x10071c) & ~0x00000100;
	अगर (subdev->device->chipset <= 0x96) अणु
		unk710 &= ~0x0000006e;
		unk714 &= ~0x00000100;

		अगर (!next->bios.ramcfg_00_03_08)
			unk710 |= 0x00000060;
		अगर (!next->bios.ramcfg_FBVDDQ)
			unk714 |= 0x00000100;
		अगर ( next->bios.ramcfg_00_04_04)
			unk710 |= 0x0000000e;
	पूर्ण अन्यथा अणु
		unk710 &= ~0x00000001;

		अगर (!next->bios.ramcfg_00_03_08)
			unk710 |= 0x00000001;
	पूर्ण

	अगर ( next->bios.ramcfg_00_03_01)
		unk71c |= 0x00000100;
	अगर ( next->bios.ramcfg_00_03_02)
		unk710 |= 0x00000100;
	अगर (!next->bios.ramcfg_00_03_08)
		unk714 |= 0x00000020;
	अगर ( next->bios.ramcfg_00_04_04)
		unk714 |= 0x70000000;
	अगर ( next->bios.ramcfg_00_04_20)
		unk718 |= 0x00000100;

	ram_mask(hwsq, 0x100714, 0xffffffff, unk714);
	ram_mask(hwsq, 0x10071c, 0xffffffff, unk71c);
	ram_mask(hwsq, 0x100718, 0xffffffff, unk718);
	ram_mask(hwsq, 0x100710, 0xffffffff, unk710);

	/* XXX: G94 करोes not even test these regs in trace. Harmless we करो it,
	 * but why is it omitted? */
	अगर (next->bios.rammap_00_16_20) अणु
		ram_wr32(hwsq, 0x1005a0, next->bios.ramcfg_00_07 << 16 |
					 next->bios.ramcfg_00_06 << 8 |
					 next->bios.ramcfg_00_05);
		ram_wr32(hwsq, 0x1005a4, next->bios.ramcfg_00_09 << 8 |
					 next->bios.ramcfg_00_08);
		ram_mask(hwsq, 0x10053c, 0x00001000, 0x00000000);
	पूर्ण अन्यथा अणु
		ram_mask(hwsq, 0x10053c, 0x00001000, 0x00001000);
	पूर्ण
	ram_mask(hwsq, mr[1], 0xffffffff, ram->base.mr[1]);

	अगर (!next->bios.timing_10_ODT)
		nv50_ram_gpio(hwsq, 0x2e, 0);

	/* Reset DLL */
	अगर (!next->bios.ramcfg_DLLoff)
		nvkm_sddr2_dll_reset(hwsq);

	ram_setf(hwsq, 0x10, 0x01); /* enable fb */
	ram_रुको(hwsq, 0x00, 0x00); /* रुको क्रम fb enabled */
	ram_wr32(hwsq, 0x611200, 0x00003330);
	ram_wr32(hwsq, 0x002504, 0x00000000); /* un-block fअगरo */

	अगर (next->bios.rammap_00_17_02)
		ram_mask(hwsq, 0x100200, 0x00000800, 0x00000800);
	अगर (!next->bios.rammap_00_16_40)
		ram_mask(hwsq, 0x004008, 0x00004000, 0x00000000);
	अगर (next->bios.ramcfg_00_03_02)
		ram_mask(hwsq, 0x10021c, 0x00010000, 0x00010000);
	अगर (subdev->device->chipset <= 0x96 && next->bios.ramcfg_00_03_02)
		ram_mask(hwsq, 0x100710, 0x00000200, 0x00000200);

	वापस 0;
पूर्ण

अटल पूर्णांक
nv50_ram_prog(काष्ठा nvkm_ram *base)
अणु
	काष्ठा nv50_ram *ram = nv50_ram(base);
	काष्ठा nvkm_device *device = ram->base.fb->subdev.device;
	ram_exec(&ram->hwsq, nvkm_boolopt(device->cfgopt, "NvMemExec", true));
	वापस 0;
पूर्ण

अटल व्योम
nv50_ram_tidy(काष्ठा nvkm_ram *base)
अणु
	काष्ठा nv50_ram *ram = nv50_ram(base);
	ram_exec(&ram->hwsq, false);
पूर्ण

अटल स्थिर काष्ठा nvkm_ram_func
nv50_ram_func = अणु
	.calc = nv50_ram_calc,
	.prog = nv50_ram_prog,
	.tidy = nv50_ram_tidy,
पूर्ण;

अटल u32
nv50_fb_vram_rblock(काष्ठा nvkm_ram *ram)
अणु
	काष्ठा nvkm_subdev *subdev = &ram->fb->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	पूर्णांक colbits, rowbitsa, rowbitsb, banks;
	u64 rowsize, predicted;
	u32 r0, r4, rt, rblock_size;

	r0 = nvkm_rd32(device, 0x100200);
	r4 = nvkm_rd32(device, 0x100204);
	rt = nvkm_rd32(device, 0x100250);
	nvkm_debug(subdev, "memcfg %08x %08x %08x %08x\n",
		   r0, r4, rt, nvkm_rd32(device, 0x001540));

	colbits  =  (r4 & 0x0000f000) >> 12;
	rowbitsa = ((r4 & 0x000f0000) >> 16) + 8;
	rowbitsb = ((r4 & 0x00f00000) >> 20) + 8;
	banks    = 1 << (((r4 & 0x03000000) >> 24) + 2);

	rowsize = ram->parts * banks * (1 << colbits) * 8;
	predicted = rowsize << rowbitsa;
	अगर (r0 & 0x00000004)
		predicted += rowsize << rowbitsb;

	अगर (predicted != ram->size) अणु
		nvkm_warn(subdev, "memory controller reports %d MiB VRAM\n",
			  (u32)(ram->size >> 20));
	पूर्ण

	rblock_size = rowsize;
	अगर (rt & 1)
		rblock_size *= 3;

	nvkm_debug(subdev, "rblock %d bytes\n", rblock_size);
	वापस rblock_size;
पूर्ण

पूर्णांक
nv50_ram_ctor(स्थिर काष्ठा nvkm_ram_func *func,
	      काष्ठा nvkm_fb *fb, काष्ठा nvkm_ram *ram)
अणु
	काष्ठा nvkm_device *device = fb->subdev.device;
	काष्ठा nvkm_bios *bios = device->bios;
	स्थिर u32 rsvd_head = ( 256 * 1024); /* vga memory */
	स्थिर u32 rsvd_tail = (1024 * 1024); /* vbios etc */
	u64 size = nvkm_rd32(device, 0x10020c);
	क्रमागत nvkm_ram_type type = NVKM_RAM_TYPE_UNKNOWN;
	पूर्णांक ret;

	चयन (nvkm_rd32(device, 0x100714) & 0x00000007) अणु
	हाल 0: type = NVKM_RAM_TYPE_DDR1; अवरोध;
	हाल 1:
		अगर (nvkm_fb_bios_memtype(bios) == NVKM_RAM_TYPE_DDR3)
			type = NVKM_RAM_TYPE_DDR3;
		अन्यथा
			type = NVKM_RAM_TYPE_DDR2;
		अवरोध;
	हाल 2: type = NVKM_RAM_TYPE_GDDR3; अवरोध;
	हाल 3: type = NVKM_RAM_TYPE_GDDR4; अवरोध;
	हाल 4: type = NVKM_RAM_TYPE_GDDR5; अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	size = (size & 0x000000ff) << 32 | (size & 0xffffff00);

	ret = nvkm_ram_ctor(func, fb, type, size, ram);
	अगर (ret)
		वापस ret;

	ram->part_mask = (nvkm_rd32(device, 0x001540) & 0x00ff0000) >> 16;
	ram->parts = hweight8(ram->part_mask);
	ram->ranks = (nvkm_rd32(device, 0x100200) & 0x4) ? 2 : 1;
	nvkm_mm_fini(&ram->vram);

	वापस nvkm_mm_init(&ram->vram, NVKM_RAM_MM_NORMAL,
			    rsvd_head >> NVKM_RAM_MM_SHIFT,
			    (size - rsvd_head - rsvd_tail) >> NVKM_RAM_MM_SHIFT,
			    nv50_fb_vram_rblock(ram) >> NVKM_RAM_MM_SHIFT);
पूर्ण

पूर्णांक
nv50_ram_new(काष्ठा nvkm_fb *fb, काष्ठा nvkm_ram **pram)
अणु
	काष्ठा nv50_ram *ram;
	पूर्णांक ret, i;

	अगर (!(ram = kzalloc(माप(*ram), GFP_KERNEL)))
		वापस -ENOMEM;
	*pram = &ram->base;

	ret = nv50_ram_ctor(&nv50_ram_func, fb, &ram->base);
	अगर (ret)
		वापस ret;

	ram->hwsq.r_0x002504 = hwsq_reg(0x002504);
	ram->hwsq.r_0x00c040 = hwsq_reg(0x00c040);
	ram->hwsq.r_0x004008 = hwsq_reg(0x004008);
	ram->hwsq.r_0x00400c = hwsq_reg(0x00400c);
	ram->hwsq.r_0x100200 = hwsq_reg(0x100200);
	ram->hwsq.r_0x100210 = hwsq_reg(0x100210);
	ram->hwsq.r_0x10021c = hwsq_reg(0x10021c);
	ram->hwsq.r_0x1002d0 = hwsq_reg(0x1002d0);
	ram->hwsq.r_0x1002d4 = hwsq_reg(0x1002d4);
	ram->hwsq.r_0x1002dc = hwsq_reg(0x1002dc);
	ram->hwsq.r_0x10053c = hwsq_reg(0x10053c);
	ram->hwsq.r_0x1005a0 = hwsq_reg(0x1005a0);
	ram->hwsq.r_0x1005a4 = hwsq_reg(0x1005a4);
	ram->hwsq.r_0x100710 = hwsq_reg(0x100710);
	ram->hwsq.r_0x100714 = hwsq_reg(0x100714);
	ram->hwsq.r_0x100718 = hwsq_reg(0x100718);
	ram->hwsq.r_0x10071c = hwsq_reg(0x10071c);
	ram->hwsq.r_0x100da0 = hwsq_stride(0x100da0, 4, ram->base.part_mask);
	ram->hwsq.r_0x100e20 = hwsq_reg(0x100e20);
	ram->hwsq.r_0x100e24 = hwsq_reg(0x100e24);
	ram->hwsq.r_0x611200 = hwsq_reg(0x611200);

	क्रम (i = 0; i < 9; i++)
		ram->hwsq.r_timing[i] = hwsq_reg(0x100220 + (i * 0x04));

	अगर (ram->base.ranks > 1) अणु
		ram->hwsq.r_mr[0] = hwsq_reg2(0x1002c0, 0x1002c8);
		ram->hwsq.r_mr[1] = hwsq_reg2(0x1002c4, 0x1002cc);
		ram->hwsq.r_mr[2] = hwsq_reg2(0x1002e0, 0x1002e8);
		ram->hwsq.r_mr[3] = hwsq_reg2(0x1002e4, 0x1002ec);
	पूर्ण अन्यथा अणु
		ram->hwsq.r_mr[0] = hwsq_reg(0x1002c0);
		ram->hwsq.r_mr[1] = hwsq_reg(0x1002c4);
		ram->hwsq.r_mr[2] = hwsq_reg(0x1002e0);
		ram->hwsq.r_mr[3] = hwsq_reg(0x1002e4);
	पूर्ण

	ram->hwsq.r_gpio[0] = hwsq_reg(0x00e104);
	ram->hwsq.r_gpio[1] = hwsq_reg(0x00e108);
	ram->hwsq.r_gpio[2] = hwsq_reg(0x00e120);
	ram->hwsq.r_gpio[3] = hwsq_reg(0x00e124);

	वापस 0;
पूर्ण
