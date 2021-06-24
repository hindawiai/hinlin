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
 * 	    Roy Spliet <rspliet@eclipso.eu>
 */
#घोषणा gt215_ram(p) container_of((p), काष्ठा gt215_ram, base)
#समावेश "ram.h"
#समावेश "ramfuc.h"

#समावेश <core/memory.h>
#समावेश <core/option.h>
#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/M0205.h>
#समावेश <subdev/bios/rammap.h>
#समावेश <subdev/bios/timing.h>
#समावेश <subdev/clk/gt215.h>
#समावेश <subdev/gpपन.स>

काष्ठा gt215_ramfuc अणु
	काष्ठा ramfuc base;
	काष्ठा ramfuc_reg r_0x001610;
	काष्ठा ramfuc_reg r_0x001700;
	काष्ठा ramfuc_reg r_0x002504;
	काष्ठा ramfuc_reg r_0x004000;
	काष्ठा ramfuc_reg r_0x004004;
	काष्ठा ramfuc_reg r_0x004018;
	काष्ठा ramfuc_reg r_0x004128;
	काष्ठा ramfuc_reg r_0x004168;
	काष्ठा ramfuc_reg r_0x100080;
	काष्ठा ramfuc_reg r_0x100200;
	काष्ठा ramfuc_reg r_0x100210;
	काष्ठा ramfuc_reg r_0x100220[9];
	काष्ठा ramfuc_reg r_0x100264;
	काष्ठा ramfuc_reg r_0x1002d0;
	काष्ठा ramfuc_reg r_0x1002d4;
	काष्ठा ramfuc_reg r_0x1002dc;
	काष्ठा ramfuc_reg r_0x10053c;
	काष्ठा ramfuc_reg r_0x1005a0;
	काष्ठा ramfuc_reg r_0x1005a4;
	काष्ठा ramfuc_reg r_0x100700;
	काष्ठा ramfuc_reg r_0x100714;
	काष्ठा ramfuc_reg r_0x100718;
	काष्ठा ramfuc_reg r_0x10071c;
	काष्ठा ramfuc_reg r_0x100720;
	काष्ठा ramfuc_reg r_0x100760;
	काष्ठा ramfuc_reg r_0x1007a0;
	काष्ठा ramfuc_reg r_0x1007e0;
	काष्ठा ramfuc_reg r_0x100da0;
	काष्ठा ramfuc_reg r_0x10f804;
	काष्ठा ramfuc_reg r_0x1110e0;
	काष्ठा ramfuc_reg r_0x111100;
	काष्ठा ramfuc_reg r_0x111104;
	काष्ठा ramfuc_reg r_0x1111e0;
	काष्ठा ramfuc_reg r_0x111400;
	काष्ठा ramfuc_reg r_0x611200;
	काष्ठा ramfuc_reg r_mr[4];
	काष्ठा ramfuc_reg r_gpio[4];
पूर्ण;

काष्ठा gt215_ltrain अणु
	क्रमागत अणु
		NVA3_TRAIN_UNKNOWN,
		NVA3_TRAIN_UNSUPPORTED,
		NVA3_TRAIN_ONCE,
		NVA3_TRAIN_EXEC,
		NVA3_TRAIN_DONE
	पूर्ण state;
	u32 r_100720;
	u32 r_1111e0;
	u32 r_111400;
	काष्ठा nvkm_memory *memory;
पूर्ण;

काष्ठा gt215_ram अणु
	काष्ठा nvkm_ram base;
	काष्ठा gt215_ramfuc fuc;
	काष्ठा gt215_ltrain ltrain;
पूर्ण;

अटल व्योम
gt215_link_train_calc(u32 *vals, काष्ठा gt215_ltrain *train)
अणु
	पूर्णांक i, lo, hi;
	u8 median[8], bins[4] = अणु0, 0, 0, 0पूर्ण, bin = 0, qty = 0;

	क्रम (i = 0; i < 8; i++) अणु
		क्रम (lo = 0; lo < 0x40; lo++) अणु
			अगर (!(vals[lo] & 0x80000000))
				जारी;
			अगर (vals[lo] & (0x101 << i))
				अवरोध;
		पूर्ण

		अगर (lo == 0x40)
			वापस;

		क्रम (hi = lo + 1; hi < 0x40; hi++) अणु
			अगर (!(vals[lo] & 0x80000000))
				जारी;
			अगर (!(vals[hi] & (0x101 << i))) अणु
				hi--;
				अवरोध;
			पूर्ण
		पूर्ण

		median[i] = ((hi - lo) >> 1) + lo;
		bins[(median[i] & 0xf0) >> 4]++;
		median[i] += 0x30;
	पूर्ण

	/* Find the best value क्रम 0x1111e0 */
	क्रम (i = 0; i < 4; i++) अणु
		अगर (bins[i] > qty) अणु
			bin = i + 3;
			qty = bins[i];
		पूर्ण
	पूर्ण

	train->r_100720 = 0;
	क्रम (i = 0; i < 8; i++) अणु
		median[i] = max(median[i], (u8) (bin << 4));
		median[i] = min(median[i], (u8) ((bin << 4) | 0xf));

		train->r_100720 |= ((median[i] & 0x0f) << (i << 2));
	पूर्ण

	train->r_1111e0 = 0x02000000 | (bin * 0x101);
	train->r_111400 = 0x0;
पूर्ण

/*
 * Link training क्रम (at least) DDR3
 */
अटल पूर्णांक
gt215_link_train(काष्ठा gt215_ram *ram)
अणु
	काष्ठा gt215_ltrain *train = &ram->ltrain;
	काष्ठा gt215_ramfuc *fuc = &ram->fuc;
	काष्ठा nvkm_subdev *subdev = &ram->base.fb->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_bios *bios = device->bios;
	काष्ठा nvkm_clk *clk = device->clk;
	u32 *result, r1700;
	पूर्णांक ret, i;
	काष्ठा nvbios_M0205T M0205T = अणु 0 पूर्ण;
	u8 ver, hdr, cnt, len, snr, ssz;
	अचिन्हित पूर्णांक clk_current;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ *f = &flags;

	अगर (nvkm_boolopt(device->cfgopt, "NvMemExec", true) != true)
		वापस -ENOSYS;

	/* XXX: Multiple partitions? */
	result = kदो_स्मृति_array(64, माप(u32), GFP_KERNEL);
	अगर (!result)
		वापस -ENOMEM;

	train->state = NVA3_TRAIN_EXEC;

	/* Clock speeds क्रम training and back */
	nvbios_M0205Tp(bios, &ver, &hdr, &cnt, &len, &snr, &ssz, &M0205T);
	अगर (M0205T.freq == 0) अणु
		kमुक्त(result);
		वापस -ENOENT;
	पूर्ण

	clk_current = nvkm_clk_पढ़ो(clk, nv_clk_src_mem);

	ret = gt215_clk_pre(clk, f);
	अगर (ret)
		जाओ out;

	/* First: घड़ी up/करोwn */
	ret = ram->base.func->calc(&ram->base, (u32) M0205T.freq * 1000);
	अगर (ret)
		जाओ out;

	/* Do this *after* calc, eliminates ग_लिखो in script */
	nvkm_wr32(device, 0x111400, 0x00000000);
	/* XXX: Magic ग_लिखोs that improve train reliability? */
	nvkm_mask(device, 0x100674, 0x0000ffff, 0x00000000);
	nvkm_mask(device, 0x1005e4, 0x0000ffff, 0x00000000);
	nvkm_mask(device, 0x100b0c, 0x000000ff, 0x00000000);
	nvkm_wr32(device, 0x100c04, 0x00000400);

	/* Now the training script */
	r1700 = ram_rd32(fuc, 0x001700);

	ram_mask(fuc, 0x100200, 0x00000800, 0x00000000);
	ram_wr32(fuc, 0x611200, 0x3300);
	ram_रुको_vblank(fuc);
	ram_रुको(fuc, 0x611200, 0x00000003, 0x00000000, 500000);
	ram_mask(fuc, 0x001610, 0x00000083, 0x00000003);
	ram_mask(fuc, 0x100080, 0x00000020, 0x00000000);
	ram_mask(fuc, 0x10f804, 0x80000000, 0x00000000);
	ram_wr32(fuc, 0x001700, 0x00000000);

	ram_train(fuc);

	/* Reset */
	ram_mask(fuc, 0x10f804, 0x80000000, 0x80000000);
	ram_wr32(fuc, 0x10053c, 0x0);
	ram_wr32(fuc, 0x100720, train->r_100720);
	ram_wr32(fuc, 0x1111e0, train->r_1111e0);
	ram_wr32(fuc, 0x111400, train->r_111400);
	ram_nuke(fuc, 0x100080);
	ram_mask(fuc, 0x100080, 0x00000020, 0x00000020);
	ram_nsec(fuc, 1000);

	ram_wr32(fuc, 0x001700, r1700);
	ram_mask(fuc, 0x001610, 0x00000083, 0x00000080);
	ram_wr32(fuc, 0x611200, 0x3330);
	ram_mask(fuc, 0x100200, 0x00000800, 0x00000800);

	ram_exec(fuc, true);

	ram->base.func->calc(&ram->base, clk_current);
	ram_exec(fuc, true);

	/* Post-processing, aव्योमs flicker */
	nvkm_mask(device, 0x616308, 0x10, 0x10);
	nvkm_mask(device, 0x616b08, 0x10, 0x10);

	gt215_clk_post(clk, f);

	ram_train_result(ram->base.fb, result, 64);
	क्रम (i = 0; i < 64; i++)
		nvkm_debug(subdev, "Train: %08x", result[i]);
	gt215_link_train_calc(result, train);

	nvkm_debug(subdev, "Train: %08x %08x %08x", train->r_100720,
		   train->r_1111e0, train->r_111400);

	kमुक्त(result);

	train->state = NVA3_TRAIN_DONE;

	वापस ret;

out:
	अगर(ret == -EBUSY)
		f = शून्य;

	train->state = NVA3_TRAIN_UNSUPPORTED;

	gt215_clk_post(clk, f);
	kमुक्त(result);
	वापस ret;
पूर्ण

अटल पूर्णांक
gt215_link_train_init(काष्ठा gt215_ram *ram)
अणु
	अटल स्थिर u32 pattern[16] = अणु
		0xaaaaaaaa, 0xcccccccc, 0xdddddddd, 0xeeeeeeee,
		0x00000000, 0x11111111, 0x44444444, 0xdddddddd,
		0x33333333, 0x55555555, 0x77777777, 0x66666666,
		0x99999999, 0x88888888, 0xeeeeeeee, 0xbbbbbbbb,
	पूर्ण;
	काष्ठा gt215_ltrain *train = &ram->ltrain;
	काष्ठा nvkm_device *device = ram->base.fb->subdev.device;
	काष्ठा nvkm_bios *bios = device->bios;
	काष्ठा nvbios_M0205E M0205E;
	u8 ver, hdr, cnt, len;
	u32 r001700;
	u64 addr;
	पूर्णांक ret, i = 0;

	train->state = NVA3_TRAIN_UNSUPPORTED;

	/* We support type "5"
	 * XXX: training pattern table appears to be unused क्रम this routine */
	अगर (!nvbios_M0205Ep(bios, i, &ver, &hdr, &cnt, &len, &M0205E))
		वापस -ENOENT;

	अगर (M0205E.type != 5)
		वापस 0;

	train->state = NVA3_TRAIN_ONCE;

	ret = nvkm_ram_get(device, NVKM_RAM_MM_NORMAL, 0x01, 16, 0x8000,
			   true, true, &ram->ltrain.memory);
	अगर (ret)
		वापस ret;

	addr = nvkm_memory_addr(ram->ltrain.memory);

	nvkm_wr32(device, 0x100538, 0x10000000 | (addr >> 16));
	nvkm_wr32(device, 0x1005a8, 0x0000ffff);
	nvkm_mask(device, 0x10f800, 0x00000001, 0x00000001);

	क्रम (i = 0; i < 0x30; i++) अणु
		nvkm_wr32(device, 0x10f8c0, (i << 8) | i);
		nvkm_wr32(device, 0x10f900, pattern[i % 16]);
	पूर्ण

	क्रम (i = 0; i < 0x30; i++) अणु
		nvkm_wr32(device, 0x10f8e0, (i << 8) | i);
		nvkm_wr32(device, 0x10f920, pattern[i % 16]);
	पूर्ण

	/* And upload the pattern */
	r001700 = nvkm_rd32(device, 0x1700);
	nvkm_wr32(device, 0x1700, addr >> 16);
	क्रम (i = 0; i < 16; i++)
		nvkm_wr32(device, 0x700000 + (i << 2), pattern[i]);
	क्रम (i = 0; i < 16; i++)
		nvkm_wr32(device, 0x700100 + (i << 2), pattern[i]);
	nvkm_wr32(device, 0x1700, r001700);

	train->r_100720 = nvkm_rd32(device, 0x100720);
	train->r_1111e0 = nvkm_rd32(device, 0x1111e0);
	train->r_111400 = nvkm_rd32(device, 0x111400);
	वापस 0;
पूर्ण

अटल व्योम
gt215_link_train_fini(काष्ठा gt215_ram *ram)
अणु
	nvkm_memory_unref(&ram->ltrain.memory);
पूर्ण

/*
 * RAM reघड़ीing
 */
#घोषणा T(t) cfg->timing_10_##t
अटल पूर्णांक
gt215_ram_timing_calc(काष्ठा gt215_ram *ram, u32 *timing)
अणु
	काष्ठा nvbios_ramcfg *cfg = &ram->base.target.bios;
	काष्ठा nvkm_subdev *subdev = &ram->base.fb->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	पूर्णांक tUNK_base, tUNK_40_0, prevCL;
	u32 cur2, cur3, cur7, cur8;

	cur2 = nvkm_rd32(device, 0x100228);
	cur3 = nvkm_rd32(device, 0x10022c);
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

	prevCL = (cur3 & 0x000000ff) + 1;
	tUNK_base = ((cur7 & 0x00ff0000) >> 16) - prevCL;

	timing[0] = (T(RP) << 24 | T(RAS) << 16 | T(RFC) << 8 | T(RC));
	timing[1] = (T(WR) + 1 + T(CWL)) << 24 |
		    max_t(u8,T(18), 1) << 16 |
		    (T(WTR) + 1 + T(CWL)) << 8 |
		    (5 + T(CL) - T(CWL));
	timing[2] = (T(CWL) - 1) << 24 |
		    (T(RRD) << 16) |
		    (T(RCDWR) << 8) |
		    T(RCDRD);
	timing[3] = (cur3 & 0x00ff0000) |
		    (0x30 + T(CL)) << 24 |
		    (0xb + T(CL)) << 8 |
		    (T(CL) - 1);
	timing[4] = T(20) << 24 |
		    T(21) << 16 |
		    T(13) << 8 |
		    T(13);
	timing[5] = T(RFC) << 24 |
		    max_t(u8,T(RCDRD), T(RCDWR)) << 16 |
		    max_t(u8, (T(CWL) + 6), (T(CL) + 2)) << 8 |
		    T(RP);
	timing[6] = (0x5a + T(CL)) << 16 |
		    max_t(u8, 1, (6 - T(CL) + T(CWL))) << 8 |
		    (0x50 + T(CL) - T(CWL));
	timing[7] = (cur7 & 0xff000000) |
		    ((tUNK_base + T(CL)) << 16) |
		    0x202;
	timing[8] = cur8 & 0xffffff00;

	चयन (ram->base.type) अणु
	हाल NVKM_RAM_TYPE_DDR2:
	हाल NVKM_RAM_TYPE_GDDR3:
		tUNK_40_0 = prevCL - (cur8 & 0xff);
		अगर (tUNK_40_0 > 0)
			timing[8] |= T(CL);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	nvkm_debug(subdev, "Entry: 220: %08x %08x %08x %08x\n",
		   timing[0], timing[1], timing[2], timing[3]);
	nvkm_debug(subdev, "  230: %08x %08x %08x %08x\n",
		   timing[4], timing[5], timing[6], timing[7]);
	nvkm_debug(subdev, "  240: %08x\n", timing[8]);
	वापस 0;
पूर्ण
#अघोषित T

अटल व्योम
nvkm_sddr2_dll_reset(काष्ठा gt215_ramfuc *fuc)
अणु
	ram_mask(fuc, mr[0], 0x100, 0x100);
	ram_nsec(fuc, 1000);
	ram_mask(fuc, mr[0], 0x100, 0x000);
	ram_nsec(fuc, 1000);
पूर्ण

अटल व्योम
nvkm_sddr3_dll_disable(काष्ठा gt215_ramfuc *fuc, u32 *mr)
अणु
	u32 mr1_old = ram_rd32(fuc, mr[1]);

	अगर (!(mr1_old & 0x1)) अणु
		ram_wr32(fuc, 0x1002d4, 0x00000001);
		ram_wr32(fuc, mr[1], mr[1]);
		ram_nsec(fuc, 1000);
	पूर्ण
पूर्ण

अटल व्योम
nvkm_gddr3_dll_disable(काष्ठा gt215_ramfuc *fuc, u32 *mr)
अणु
	u32 mr1_old = ram_rd32(fuc, mr[1]);

	अगर (!(mr1_old & 0x40)) अणु
		ram_wr32(fuc, mr[1], mr[1]);
		ram_nsec(fuc, 1000);
	पूर्ण
पूर्ण

अटल व्योम
gt215_ram_lock_pll(काष्ठा gt215_ramfuc *fuc, काष्ठा gt215_clk_info *mclk)
अणु
	ram_wr32(fuc, 0x004004, mclk->pll);
	ram_mask(fuc, 0x004000, 0x00000001, 0x00000001);
	ram_mask(fuc, 0x004000, 0x00000010, 0x00000000);
	ram_रुको(fuc, 0x004000, 0x00020000, 0x00020000, 64000);
	ram_mask(fuc, 0x004000, 0x00000010, 0x00000010);
पूर्ण

अटल व्योम
gt215_ram_gpio(काष्ठा gt215_ramfuc *fuc, u8 tag, u32 val)
अणु
	काष्ठा nvkm_gpio *gpio = fuc->base.fb->subdev.device->gpio;
	काष्ठा dcb_gpio_func func;
	u32 reg, sh, gpio_val;
	पूर्णांक ret;

	अगर (nvkm_gpio_get(gpio, 0, tag, DCB_GPIO_UNUSED) != val) अणु
		ret = nvkm_gpio_find(gpio, 0, tag, DCB_GPIO_UNUSED, &func);
		अगर (ret)
			वापस;

		reg = func.line >> 3;
		sh = (func.line & 0x7) << 2;
		gpio_val = ram_rd32(fuc, gpio[reg]);
		अगर (gpio_val & (8 << sh))
			val = !val;
		अगर (!(func.log[1] & 1))
			val = !val;

		ram_mask(fuc, gpio[reg], (0x3 << sh), ((val | 0x2) << sh));
		ram_nsec(fuc, 20000);
	पूर्ण
पूर्ण

अटल पूर्णांक
gt215_ram_calc(काष्ठा nvkm_ram *base, u32 freq)
अणु
	काष्ठा gt215_ram *ram = gt215_ram(base);
	काष्ठा gt215_ramfuc *fuc = &ram->fuc;
	काष्ठा gt215_ltrain *train = &ram->ltrain;
	काष्ठा nvkm_subdev *subdev = &ram->base.fb->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_bios *bios = device->bios;
	काष्ठा gt215_clk_info mclk;
	काष्ठा nvkm_gpio *gpio = device->gpio;
	काष्ठा nvkm_ram_data *next;
	u8  ver, hdr, cnt, len, strap;
	u32 data;
	u32 r004018, r100760, r100da0, r111100, ctrl;
	u32 unk714, unk718, unk71c;
	पूर्णांक ret, i;
	u32 timing[9];
	bool pll2pll;

	next = &ram->base.target;
	next->freq = freq;
	ram->base.next = next;

	अगर (ram->ltrain.state == NVA3_TRAIN_ONCE)
		gt215_link_train(ram);

	/* lookup memory config data relevant to the target frequency */
	data = nvbios_rammapEm(bios, freq / 1000, &ver, &hdr, &cnt, &len,
			       &next->bios);
	अगर (!data || ver != 0x10 || hdr < 0x05) अणु
		nvkm_error(subdev, "invalid/missing rammap entry\n");
		वापस -EINVAL;
	पूर्ण

	/* locate specअगरic data set क्रम the attached memory */
	strap = nvbios_ramcfg_index(subdev);
	अगर (strap >= cnt) अणु
		nvkm_error(subdev, "invalid ramcfg strap\n");
		वापस -EINVAL;
	पूर्ण

	data = nvbios_rammapSp(bios, data, ver, hdr, cnt, len, strap,
			       &ver, &hdr, &next->bios);
	अगर (!data || ver != 0x10 || hdr < 0x09) अणु
		nvkm_error(subdev, "invalid/missing ramcfg entry\n");
		वापस -EINVAL;
	पूर्ण

	/* lookup memory timings, अगर bios says they're present */
	अगर (next->bios.ramcfg_timing != 0xff) अणु
		data = nvbios_timingEp(bios, next->bios.ramcfg_timing,
				       &ver, &hdr, &cnt, &len,
				       &next->bios);
		अगर (!data || ver != 0x10 || hdr < 0x17) अणु
			nvkm_error(subdev, "invalid/missing timing entry\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	ret = gt215_pll_info(device->clk, 0x12, 0x4000, freq, &mclk);
	अगर (ret < 0) अणु
		nvkm_error(subdev, "failed mclk calculation\n");
		वापस ret;
	पूर्ण

	gt215_ram_timing_calc(ram, timing);

	ret = ram_init(fuc, ram->base.fb);
	अगर (ret)
		वापस ret;

	/* Determine ram-specअगरic MR values */
	ram->base.mr[0] = ram_rd32(fuc, mr[0]);
	ram->base.mr[1] = ram_rd32(fuc, mr[1]);
	ram->base.mr[2] = ram_rd32(fuc, mr[2]);

	चयन (ram->base.type) अणु
	हाल NVKM_RAM_TYPE_DDR2:
		ret = nvkm_sddr2_calc(&ram->base);
		अवरोध;
	हाल NVKM_RAM_TYPE_DDR3:
		ret = nvkm_sddr3_calc(&ram->base);
		अवरोध;
	हाल NVKM_RAM_TYPE_GDDR3:
		ret = nvkm_gddr3_calc(&ram->base);
		अवरोध;
	शेष:
		ret = -ENOSYS;
		अवरोध;
	पूर्ण

	अगर (ret)
		वापस ret;

	/* XXX: 750MHz seems rather arbitrary */
	अगर (freq <= 750000) अणु
		r004018 = 0x10000000;
		r100760 = 0x22222222;
		r100da0 = 0x00000010;
	पूर्ण अन्यथा अणु
		r004018 = 0x00000000;
		r100760 = 0x00000000;
		r100da0 = 0x00000000;
	पूर्ण

	अगर (!next->bios.ramcfg_DLLoff)
		r004018 |= 0x00004000;

	/* pll2pll requires to चयन to a safe घड़ी first */
	ctrl = ram_rd32(fuc, 0x004000);
	pll2pll = (!(ctrl & 0x00000008)) && mclk.pll;

	/* Pre, NVIDIA करोes this outside the script */
	अगर (next->bios.ramcfg_10_02_10) अणु
		ram_mask(fuc, 0x111104, 0x00000600, 0x00000000);
	पूर्ण अन्यथा अणु
		ram_mask(fuc, 0x111100, 0x40000000, 0x40000000);
		ram_mask(fuc, 0x111104, 0x00000180, 0x00000000);
	पूर्ण
	/* Always disable this bit during reघड़ी */
	ram_mask(fuc, 0x100200, 0x00000800, 0x00000000);

	/* If चयनing from non-pll to pll, lock beक्रमe disabling FB */
	अगर (mclk.pll && !pll2pll) अणु
		ram_mask(fuc, 0x004128, 0x003f3141, mclk.clk | 0x00000101);
		gt215_ram_lock_pll(fuc, &mclk);
	पूर्ण

	/* Start with disabling some CRTCs and PFIFO? */
	ram_रुको_vblank(fuc);
	ram_wr32(fuc, 0x611200, 0x3300);
	ram_mask(fuc, 0x002504, 0x1, 0x1);
	ram_nsec(fuc, 10000);
	ram_रुको(fuc, 0x002504, 0x10, 0x10, 20000); /* XXX: or दीर्घer? */
	ram_block(fuc);
	ram_nsec(fuc, 2000);

	अगर (!next->bios.ramcfg_10_02_10) अणु
		अगर (ram->base.type == NVKM_RAM_TYPE_GDDR3)
			ram_mask(fuc, 0x111100, 0x04020000, 0x00020000);
		अन्यथा
			ram_mask(fuc, 0x111100, 0x04020000, 0x04020000);
	पूर्ण

	/* If we're disabling the DLL, करो it now */
	चयन (next->bios.ramcfg_DLLoff * ram->base.type) अणु
	हाल NVKM_RAM_TYPE_DDR3:
		nvkm_sddr3_dll_disable(fuc, ram->base.mr);
		अवरोध;
	हाल NVKM_RAM_TYPE_GDDR3:
		nvkm_gddr3_dll_disable(fuc, ram->base.mr);
		अवरोध;
	पूर्ण

	अगर (next->bios.timing_10_ODT)
		gt215_ram_gpio(fuc, 0x2e, 1);

	/* Brace RAM क्रम impact */
	ram_wr32(fuc, 0x1002d4, 0x00000001);
	ram_wr32(fuc, 0x1002d0, 0x00000001);
	ram_wr32(fuc, 0x1002d0, 0x00000001);
	ram_wr32(fuc, 0x100210, 0x00000000);
	ram_wr32(fuc, 0x1002dc, 0x00000001);
	ram_nsec(fuc, 2000);

	अगर (device->chipset == 0xa3 && freq <= 500000)
		ram_mask(fuc, 0x100700, 0x00000006, 0x00000006);

	/* Alter FBVDD/Q, apparently must be करोne with PLL disabled, thus
	 * set it to bypass */
	अगर (nvkm_gpio_get(gpio, 0, 0x18, DCB_GPIO_UNUSED) ==
			next->bios.ramcfg_FBVDDQ) अणु
		data = ram_rd32(fuc, 0x004000) & 0x9;

		अगर (data == 0x1)
			ram_mask(fuc, 0x004000, 0x8, 0x8);
		अगर (data & 0x1)
			ram_mask(fuc, 0x004000, 0x1, 0x0);

		gt215_ram_gpio(fuc, 0x18, !next->bios.ramcfg_FBVDDQ);

		अगर (data & 0x1)
			ram_mask(fuc, 0x004000, 0x1, 0x1);
	पूर्ण

	/* Fiddle with घड़ीs */
	/* There's 4 scenario's
	 * pll->pll: first चयन to a 324MHz घड़ी, set up new PLL, चयन
	 * clk->pll: Set up new PLL, चयन
	 * pll->clk: Set up घड़ी, चयन
	 * clk->clk: Overग_लिखो ctrl and other bits, चयन */

	/* Switch to regular घड़ी - 324MHz */
	अगर (pll2pll) अणु
		ram_mask(fuc, 0x004000, 0x00000004, 0x00000004);
		ram_mask(fuc, 0x004168, 0x003f3141, 0x00083101);
		ram_mask(fuc, 0x004000, 0x00000008, 0x00000008);
		ram_mask(fuc, 0x1110e0, 0x00088000, 0x00088000);
		ram_wr32(fuc, 0x004018, 0x00001000);
		gt215_ram_lock_pll(fuc, &mclk);
	पूर्ण

	अगर (mclk.pll) अणु
		ram_mask(fuc, 0x004000, 0x00000105, 0x00000105);
		ram_wr32(fuc, 0x004018, 0x00001000 | r004018);
		ram_wr32(fuc, 0x100da0, r100da0);
	पूर्ण अन्यथा अणु
		ram_mask(fuc, 0x004168, 0x003f3141, mclk.clk | 0x00000101);
		ram_mask(fuc, 0x004000, 0x00000108, 0x00000008);
		ram_mask(fuc, 0x1110e0, 0x00088000, 0x00088000);
		ram_wr32(fuc, 0x004018, 0x00009000 | r004018);
		ram_wr32(fuc, 0x100da0, r100da0);
	पूर्ण
	ram_nsec(fuc, 20000);

	अगर (next->bios.rammap_10_04_08) अणु
		ram_wr32(fuc, 0x1005a0, next->bios.ramcfg_10_06 << 16 |
					next->bios.ramcfg_10_05 << 8 |
					next->bios.ramcfg_10_05);
		ram_wr32(fuc, 0x1005a4, next->bios.ramcfg_10_08 << 8 |
					next->bios.ramcfg_10_07);
		ram_wr32(fuc, 0x10f804, next->bios.ramcfg_10_09_f0 << 20 |
					next->bios.ramcfg_10_03_0f << 16 |
					next->bios.ramcfg_10_09_0f |
					0x80000000);
		ram_mask(fuc, 0x10053c, 0x00001000, 0x00000000);
	पूर्ण अन्यथा अणु
		अगर (train->state == NVA3_TRAIN_DONE) अणु
			ram_wr32(fuc, 0x100080, 0x1020);
			ram_mask(fuc, 0x111400, 0xffffffff, train->r_111400);
			ram_mask(fuc, 0x1111e0, 0xffffffff, train->r_1111e0);
			ram_mask(fuc, 0x100720, 0xffffffff, train->r_100720);
		पूर्ण
		ram_mask(fuc, 0x10053c, 0x00001000, 0x00001000);
		ram_mask(fuc, 0x10f804, 0x80000000, 0x00000000);
		ram_mask(fuc, 0x100760, 0x22222222, r100760);
		ram_mask(fuc, 0x1007a0, 0x22222222, r100760);
		ram_mask(fuc, 0x1007e0, 0x22222222, r100760);
	पूर्ण

	अगर (device->chipset == 0xa3 && freq > 500000) अणु
		ram_mask(fuc, 0x100700, 0x00000006, 0x00000000);
	पूर्ण

	/* Final चयन */
	अगर (mclk.pll) अणु
		ram_mask(fuc, 0x1110e0, 0x00088000, 0x00011000);
		ram_mask(fuc, 0x004000, 0x00000008, 0x00000000);
	पूर्ण

	ram_wr32(fuc, 0x1002dc, 0x00000000);
	ram_wr32(fuc, 0x1002d4, 0x00000001);
	ram_wr32(fuc, 0x100210, 0x80000000);
	ram_nsec(fuc, 2000);

	/* Set RAM MR parameters and timings */
	क्रम (i = 2; i >= 0; i--) अणु
		अगर (ram_rd32(fuc, mr[i]) != ram->base.mr[i]) अणु
			ram_wr32(fuc, mr[i], ram->base.mr[i]);
			ram_nsec(fuc, 1000);
		पूर्ण
	पूर्ण

	ram_wr32(fuc, 0x100220[3], timing[3]);
	ram_wr32(fuc, 0x100220[1], timing[1]);
	ram_wr32(fuc, 0x100220[6], timing[6]);
	ram_wr32(fuc, 0x100220[7], timing[7]);
	ram_wr32(fuc, 0x100220[2], timing[2]);
	ram_wr32(fuc, 0x100220[4], timing[4]);
	ram_wr32(fuc, 0x100220[5], timing[5]);
	ram_wr32(fuc, 0x100220[0], timing[0]);
	ram_wr32(fuc, 0x100220[8], timing[8]);

	/* Misc */
	ram_mask(fuc, 0x100200, 0x00001000, !next->bios.ramcfg_10_02_08 << 12);

	/* XXX: A lot of "chipset"/"ram type" specअगरic stuff...? */
	unk714  = ram_rd32(fuc, 0x100714) & ~0xf0000130;
	unk718  = ram_rd32(fuc, 0x100718) & ~0x00000100;
	unk71c  = ram_rd32(fuc, 0x10071c) & ~0x00000100;
	r111100 = ram_rd32(fuc, 0x111100) & ~0x3a800000;

	/* NVA8 seems to skip various bits related to ramcfg_10_02_04 */
	अगर (device->chipset == 0xa8) अणु
		r111100 |= 0x08000000;
		अगर (!next->bios.ramcfg_10_02_04)
			unk714  |= 0x00000010;
	पूर्ण अन्यथा अणु
		अगर (next->bios.ramcfg_10_02_04) अणु
			चयन (ram->base.type) अणु
			हाल NVKM_RAM_TYPE_DDR2:
			हाल NVKM_RAM_TYPE_DDR3:
				r111100 &= ~0x00000020;
				अगर (next->bios.ramcfg_10_02_10)
					r111100 |= 0x08000004;
				अन्यथा
					r111100 |= 0x00000024;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (ram->base.type) अणु
			हाल NVKM_RAM_TYPE_DDR2:
			हाल NVKM_RAM_TYPE_DDR3:
				r111100 &= ~0x00000024;
				r111100 |=  0x12800000;

				अगर (next->bios.ramcfg_10_02_10)
					r111100 |= 0x08000000;
				unk714  |= 0x00000010;
				अवरोध;
			हाल NVKM_RAM_TYPE_GDDR3:
				r111100 |= 0x30000000;
				unk714  |= 0x00000020;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	unk714 |= (next->bios.ramcfg_10_04_01) << 8;

	अगर (next->bios.ramcfg_10_02_20)
		unk714 |= 0xf0000000;
	अगर (next->bios.ramcfg_10_02_02)
		unk718 |= 0x00000100;
	अगर (next->bios.ramcfg_10_02_01)
		unk71c |= 0x00000100;
	अगर (next->bios.timing_10_24 != 0xff) अणु
		unk718 &= ~0xf0000000;
		unk718 |= next->bios.timing_10_24 << 28;
	पूर्ण
	अगर (next->bios.ramcfg_10_02_10)
		r111100 &= ~0x04020000;

	ram_mask(fuc, 0x100714, 0xffffffff, unk714);
	ram_mask(fuc, 0x10071c, 0xffffffff, unk71c);
	ram_mask(fuc, 0x100718, 0xffffffff, unk718);
	ram_mask(fuc, 0x111100, 0xffffffff, r111100);

	अगर (!next->bios.timing_10_ODT)
		gt215_ram_gpio(fuc, 0x2e, 0);

	/* Reset DLL */
	अगर (!next->bios.ramcfg_DLLoff)
		nvkm_sddr2_dll_reset(fuc);

	अगर (ram->base.type == NVKM_RAM_TYPE_GDDR3) अणु
		ram_nsec(fuc, 31000);
	पूर्ण अन्यथा अणु
		ram_nsec(fuc, 14000);
	पूर्ण

	अगर (ram->base.type == NVKM_RAM_TYPE_DDR3) अणु
		ram_wr32(fuc, 0x100264, 0x1);
		ram_nsec(fuc, 2000);
	पूर्ण

	ram_nuke(fuc, 0x100700);
	ram_mask(fuc, 0x100700, 0x01000000, 0x01000000);
	ram_mask(fuc, 0x100700, 0x01000000, 0x00000000);

	/* Re-enable FB */
	ram_unblock(fuc);
	ram_wr32(fuc, 0x611200, 0x3330);

	/* Post fiddlings */
	अगर (next->bios.rammap_10_04_02)
		ram_mask(fuc, 0x100200, 0x00000800, 0x00000800);
	अगर (next->bios.ramcfg_10_02_10) अणु
		ram_mask(fuc, 0x111104, 0x00000180, 0x00000180);
		ram_mask(fuc, 0x111100, 0x40000000, 0x00000000);
	पूर्ण अन्यथा अणु
		ram_mask(fuc, 0x111104, 0x00000600, 0x00000600);
	पूर्ण

	अगर (mclk.pll) अणु
		ram_mask(fuc, 0x004168, 0x00000001, 0x00000000);
		ram_mask(fuc, 0x004168, 0x00000100, 0x00000000);
	पूर्ण अन्यथा अणु
		ram_mask(fuc, 0x004000, 0x00000001, 0x00000000);
		ram_mask(fuc, 0x004128, 0x00000001, 0x00000000);
		ram_mask(fuc, 0x004128, 0x00000100, 0x00000000);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
gt215_ram_prog(काष्ठा nvkm_ram *base)
अणु
	काष्ठा gt215_ram *ram = gt215_ram(base);
	काष्ठा gt215_ramfuc *fuc = &ram->fuc;
	काष्ठा nvkm_device *device = ram->base.fb->subdev.device;
	bool exec = nvkm_boolopt(device->cfgopt, "NvMemExec", true);

	अगर (exec) अणु
		nvkm_mask(device, 0x001534, 0x2, 0x2);

		ram_exec(fuc, true);

		/* Post-processing, aव्योमs flicker */
		nvkm_mask(device, 0x002504, 0x1, 0x0);
		nvkm_mask(device, 0x001534, 0x2, 0x0);

		nvkm_mask(device, 0x616308, 0x10, 0x10);
		nvkm_mask(device, 0x616b08, 0x10, 0x10);
	पूर्ण अन्यथा अणु
		ram_exec(fuc, false);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
gt215_ram_tidy(काष्ठा nvkm_ram *base)
अणु
	काष्ठा gt215_ram *ram = gt215_ram(base);
	ram_exec(&ram->fuc, false);
पूर्ण

अटल पूर्णांक
gt215_ram_init(काष्ठा nvkm_ram *base)
अणु
	काष्ठा gt215_ram *ram = gt215_ram(base);
	gt215_link_train_init(ram);
	वापस 0;
पूर्ण

अटल व्योम *
gt215_ram_dtor(काष्ठा nvkm_ram *base)
अणु
	काष्ठा gt215_ram *ram = gt215_ram(base);
	gt215_link_train_fini(ram);
	वापस ram;
पूर्ण

अटल स्थिर काष्ठा nvkm_ram_func
gt215_ram_func = अणु
	.dtor = gt215_ram_dtor,
	.init = gt215_ram_init,
	.calc = gt215_ram_calc,
	.prog = gt215_ram_prog,
	.tidy = gt215_ram_tidy,
पूर्ण;

पूर्णांक
gt215_ram_new(काष्ठा nvkm_fb *fb, काष्ठा nvkm_ram **pram)
अणु
	काष्ठा gt215_ram *ram;
	पूर्णांक ret, i;

	अगर (!(ram = kzalloc(माप(*ram), GFP_KERNEL)))
		वापस -ENOMEM;
	*pram = &ram->base;

	ret = nv50_ram_ctor(&gt215_ram_func, fb, &ram->base);
	अगर (ret)
		वापस ret;

	ram->fuc.r_0x001610 = ramfuc_reg(0x001610);
	ram->fuc.r_0x001700 = ramfuc_reg(0x001700);
	ram->fuc.r_0x002504 = ramfuc_reg(0x002504);
	ram->fuc.r_0x004000 = ramfuc_reg(0x004000);
	ram->fuc.r_0x004004 = ramfuc_reg(0x004004);
	ram->fuc.r_0x004018 = ramfuc_reg(0x004018);
	ram->fuc.r_0x004128 = ramfuc_reg(0x004128);
	ram->fuc.r_0x004168 = ramfuc_reg(0x004168);
	ram->fuc.r_0x100080 = ramfuc_reg(0x100080);
	ram->fuc.r_0x100200 = ramfuc_reg(0x100200);
	ram->fuc.r_0x100210 = ramfuc_reg(0x100210);
	क्रम (i = 0; i < 9; i++)
		ram->fuc.r_0x100220[i] = ramfuc_reg(0x100220 + (i * 4));
	ram->fuc.r_0x100264 = ramfuc_reg(0x100264);
	ram->fuc.r_0x1002d0 = ramfuc_reg(0x1002d0);
	ram->fuc.r_0x1002d4 = ramfuc_reg(0x1002d4);
	ram->fuc.r_0x1002dc = ramfuc_reg(0x1002dc);
	ram->fuc.r_0x10053c = ramfuc_reg(0x10053c);
	ram->fuc.r_0x1005a0 = ramfuc_reg(0x1005a0);
	ram->fuc.r_0x1005a4 = ramfuc_reg(0x1005a4);
	ram->fuc.r_0x100700 = ramfuc_reg(0x100700);
	ram->fuc.r_0x100714 = ramfuc_reg(0x100714);
	ram->fuc.r_0x100718 = ramfuc_reg(0x100718);
	ram->fuc.r_0x10071c = ramfuc_reg(0x10071c);
	ram->fuc.r_0x100720 = ramfuc_reg(0x100720);
	ram->fuc.r_0x100760 = ramfuc_stride(0x100760, 4, ram->base.part_mask);
	ram->fuc.r_0x1007a0 = ramfuc_stride(0x1007a0, 4, ram->base.part_mask);
	ram->fuc.r_0x1007e0 = ramfuc_stride(0x1007e0, 4, ram->base.part_mask);
	ram->fuc.r_0x100da0 = ramfuc_stride(0x100da0, 4, ram->base.part_mask);
	ram->fuc.r_0x10f804 = ramfuc_reg(0x10f804);
	ram->fuc.r_0x1110e0 = ramfuc_stride(0x1110e0, 4, ram->base.part_mask);
	ram->fuc.r_0x111100 = ramfuc_reg(0x111100);
	ram->fuc.r_0x111104 = ramfuc_reg(0x111104);
	ram->fuc.r_0x1111e0 = ramfuc_reg(0x1111e0);
	ram->fuc.r_0x111400 = ramfuc_reg(0x111400);
	ram->fuc.r_0x611200 = ramfuc_reg(0x611200);

	अगर (ram->base.ranks > 1) अणु
		ram->fuc.r_mr[0] = ramfuc_reg2(0x1002c0, 0x1002c8);
		ram->fuc.r_mr[1] = ramfuc_reg2(0x1002c4, 0x1002cc);
		ram->fuc.r_mr[2] = ramfuc_reg2(0x1002e0, 0x1002e8);
		ram->fuc.r_mr[3] = ramfuc_reg2(0x1002e4, 0x1002ec);
	पूर्ण अन्यथा अणु
		ram->fuc.r_mr[0] = ramfuc_reg(0x1002c0);
		ram->fuc.r_mr[1] = ramfuc_reg(0x1002c4);
		ram->fuc.r_mr[2] = ramfuc_reg(0x1002e0);
		ram->fuc.r_mr[3] = ramfuc_reg(0x1002e4);
	पूर्ण
	ram->fuc.r_gpio[0] = ramfuc_reg(0x00e104);
	ram->fuc.r_gpio[1] = ramfuc_reg(0x00e108);
	ram->fuc.r_gpio[2] = ramfuc_reg(0x00e120);
	ram->fuc.r_gpio[3] = ramfuc_reg(0x00e124);

	वापस 0;
पूर्ण
