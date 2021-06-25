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
#घोषणा gf100_ram(p) container_of((p), काष्ठा gf100_ram, base)
#समावेश "ram.h"
#समावेश "ramfuc.h"

#समावेश <core/option.h>
#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/pll.h>
#समावेश <subdev/bios/rammap.h>
#समावेश <subdev/bios/timing.h>
#समावेश <subdev/clk.h>
#समावेश <subdev/clk/pll.h>

काष्ठा gf100_ramfuc अणु
	काष्ठा ramfuc base;

	काष्ठा ramfuc_reg r_0x10fe20;
	काष्ठा ramfuc_reg r_0x10fe24;
	काष्ठा ramfuc_reg r_0x137320;
	काष्ठा ramfuc_reg r_0x137330;

	काष्ठा ramfuc_reg r_0x132000;
	काष्ठा ramfuc_reg r_0x132004;
	काष्ठा ramfuc_reg r_0x132100;

	काष्ठा ramfuc_reg r_0x137390;

	काष्ठा ramfuc_reg r_0x10f290;
	काष्ठा ramfuc_reg r_0x10f294;
	काष्ठा ramfuc_reg r_0x10f298;
	काष्ठा ramfuc_reg r_0x10f29c;
	काष्ठा ramfuc_reg r_0x10f2a0;

	काष्ठा ramfuc_reg r_0x10f300;
	काष्ठा ramfuc_reg r_0x10f338;
	काष्ठा ramfuc_reg r_0x10f340;
	काष्ठा ramfuc_reg r_0x10f344;
	काष्ठा ramfuc_reg r_0x10f348;

	काष्ठा ramfuc_reg r_0x10f910;
	काष्ठा ramfuc_reg r_0x10f914;

	काष्ठा ramfuc_reg r_0x100b0c;
	काष्ठा ramfuc_reg r_0x10f050;
	काष्ठा ramfuc_reg r_0x10f090;
	काष्ठा ramfuc_reg r_0x10f200;
	काष्ठा ramfuc_reg r_0x10f210;
	काष्ठा ramfuc_reg r_0x10f310;
	काष्ठा ramfuc_reg r_0x10f314;
	काष्ठा ramfuc_reg r_0x10f610;
	काष्ठा ramfuc_reg r_0x10f614;
	काष्ठा ramfuc_reg r_0x10f800;
	काष्ठा ramfuc_reg r_0x10f808;
	काष्ठा ramfuc_reg r_0x10f824;
	काष्ठा ramfuc_reg r_0x10f830;
	काष्ठा ramfuc_reg r_0x10f988;
	काष्ठा ramfuc_reg r_0x10f98c;
	काष्ठा ramfuc_reg r_0x10f990;
	काष्ठा ramfuc_reg r_0x10f998;
	काष्ठा ramfuc_reg r_0x10f9b0;
	काष्ठा ramfuc_reg r_0x10f9b4;
	काष्ठा ramfuc_reg r_0x10fb04;
	काष्ठा ramfuc_reg r_0x10fb08;
	काष्ठा ramfuc_reg r_0x137300;
	काष्ठा ramfuc_reg r_0x137310;
	काष्ठा ramfuc_reg r_0x137360;
	काष्ठा ramfuc_reg r_0x1373ec;
	काष्ठा ramfuc_reg r_0x1373f0;
	काष्ठा ramfuc_reg r_0x1373f8;

	काष्ठा ramfuc_reg r_0x61c140;
	काष्ठा ramfuc_reg r_0x611200;

	काष्ठा ramfuc_reg r_0x13d8f4;
पूर्ण;

काष्ठा gf100_ram अणु
	काष्ठा nvkm_ram base;
	काष्ठा gf100_ramfuc fuc;
	काष्ठा nvbios_pll refpll;
	काष्ठा nvbios_pll mempll;
पूर्ण;

अटल व्योम
gf100_ram_train(काष्ठा gf100_ramfuc *fuc, u32 magic)
अणु
	काष्ठा gf100_ram *ram = container_of(fuc, typeof(*ram), fuc);
	काष्ठा nvkm_fb *fb = ram->base.fb;
	काष्ठा nvkm_device *device = fb->subdev.device;
	u32 part = nvkm_rd32(device, 0x022438), i;
	u32 mask = nvkm_rd32(device, 0x022554);
	u32 addr = 0x110974;

	ram_wr32(fuc, 0x10f910, magic);
	ram_wr32(fuc, 0x10f914, magic);

	क्रम (i = 0; (magic & 0x80000000) && i < part; addr += 0x1000, i++) अणु
		अगर (mask & (1 << i))
			जारी;
		ram_रुको(fuc, addr, 0x0000000f, 0x00000000, 500000);
	पूर्ण
पूर्ण

पूर्णांक
gf100_ram_calc(काष्ठा nvkm_ram *base, u32 freq)
अणु
	काष्ठा gf100_ram *ram = gf100_ram(base);
	काष्ठा gf100_ramfuc *fuc = &ram->fuc;
	काष्ठा nvkm_subdev *subdev = &ram->base.fb->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_clk *clk = device->clk;
	काष्ठा nvkm_bios *bios = device->bios;
	काष्ठा nvbios_ramcfg cfg;
	u8  ver, cnt, len, strap;
	काष्ठा अणु
		u32 data;
		u8  size;
	पूर्ण rammap, ramcfg, timing;
	पूर्णांक ref, भाग, out;
	पूर्णांक from, mode;
	पूर्णांक N1, M1, P;
	पूर्णांक ret;

	/* lookup memory config data relevant to the target frequency */
	rammap.data = nvbios_rammapEm(bios, freq / 1000, &ver, &rammap.size,
				      &cnt, &ramcfg.size, &cfg);
	अगर (!rammap.data || ver != 0x10 || rammap.size < 0x0e) अणु
		nvkm_error(subdev, "invalid/missing rammap entry\n");
		वापस -EINVAL;
	पूर्ण

	/* locate specअगरic data set क्रम the attached memory */
	strap = nvbios_ramcfg_index(subdev);
	अगर (strap >= cnt) अणु
		nvkm_error(subdev, "invalid ramcfg strap\n");
		वापस -EINVAL;
	पूर्ण

	ramcfg.data = rammap.data + rammap.size + (strap * ramcfg.size);
	अगर (!ramcfg.data || ver != 0x10 || ramcfg.size < 0x0e) अणु
		nvkm_error(subdev, "invalid/missing ramcfg entry\n");
		वापस -EINVAL;
	पूर्ण

	/* lookup memory timings, अगर bios says they're present */
	strap = nvbios_rd08(bios, ramcfg.data + 0x01);
	अगर (strap != 0xff) अणु
		timing.data = nvbios_timingEe(bios, strap, &ver, &timing.size,
					      &cnt, &len);
		अगर (!timing.data || ver != 0x10 || timing.size < 0x19) अणु
			nvkm_error(subdev, "invalid/missing timing entry\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		timing.data = 0;
	पूर्ण

	ret = ram_init(fuc, ram->base.fb);
	अगर (ret)
		वापस ret;

	/* determine current mclk configuration */
	from = !!(ram_rd32(fuc, 0x1373f0) & 0x00000002); /*XXX: ok? */

	/* determine target mclk configuration */
	अगर (!(ram_rd32(fuc, 0x137300) & 0x00000100))
		ref = nvkm_clk_पढ़ो(clk, nv_clk_src_sppll0);
	अन्यथा
		ref = nvkm_clk_पढ़ो(clk, nv_clk_src_sppll1);
	भाग = max(min((ref * 2) / freq, (u32)65), (u32)2) - 2;
	out = (ref * 2) / (भाग + 2);
	mode = freq != out;

	ram_mask(fuc, 0x137360, 0x00000002, 0x00000000);

	अगर ((ram_rd32(fuc, 0x132000) & 0x00000002) || 0 /*XXX*/) अणु
		ram_nuke(fuc, 0x132000);
		ram_mask(fuc, 0x132000, 0x00000002, 0x00000002);
		ram_mask(fuc, 0x132000, 0x00000002, 0x00000000);
	पूर्ण

	अगर (mode == 1) अणु
		ram_nuke(fuc, 0x10fe20);
		ram_mask(fuc, 0x10fe20, 0x00000002, 0x00000002);
		ram_mask(fuc, 0x10fe20, 0x00000002, 0x00000000);
	पूर्ण

// 0x00020034 // 0x0000000a
	ram_wr32(fuc, 0x132100, 0x00000001);

	अगर (mode == 1 && from == 0) अणु
		/* calculate refpll */
		ret = gt215_pll_calc(subdev, &ram->refpll, ram->mempll.refclk,
				     &N1, शून्य, &M1, &P);
		अगर (ret <= 0) अणु
			nvkm_error(subdev, "unable to calc refpll\n");
			वापस ret ? ret : -दुस्फल;
		पूर्ण

		ram_wr32(fuc, 0x10fe20, 0x20010000);
		ram_wr32(fuc, 0x137320, 0x00000003);
		ram_wr32(fuc, 0x137330, 0x81200006);
		ram_wr32(fuc, 0x10fe24, (P << 16) | (N1 << 8) | M1);
		ram_wr32(fuc, 0x10fe20, 0x20010001);
		ram_रुको(fuc, 0x137390, 0x00020000, 0x00020000, 64000);

		/* calculate mempll */
		ret = gt215_pll_calc(subdev, &ram->mempll, freq,
				     &N1, शून्य, &M1, &P);
		अगर (ret <= 0) अणु
			nvkm_error(subdev, "unable to calc refpll\n");
			वापस ret ? ret : -दुस्फल;
		पूर्ण

		ram_wr32(fuc, 0x10fe20, 0x20010005);
		ram_wr32(fuc, 0x132004, (P << 16) | (N1 << 8) | M1);
		ram_wr32(fuc, 0x132000, 0x18010101);
		ram_रुको(fuc, 0x137390, 0x00000002, 0x00000002, 64000);
	पूर्ण अन्यथा
	अगर (mode == 0) अणु
		ram_wr32(fuc, 0x137300, 0x00000003);
	पूर्ण

	अगर (from == 0) अणु
		ram_nuke(fuc, 0x10fb04);
		ram_mask(fuc, 0x10fb04, 0x0000ffff, 0x00000000);
		ram_nuke(fuc, 0x10fb08);
		ram_mask(fuc, 0x10fb08, 0x0000ffff, 0x00000000);
		ram_wr32(fuc, 0x10f988, 0x2004ff00);
		ram_wr32(fuc, 0x10f98c, 0x003fc040);
		ram_wr32(fuc, 0x10f990, 0x20012001);
		ram_wr32(fuc, 0x10f998, 0x00011a00);
		ram_wr32(fuc, 0x13d8f4, 0x00000000);
	पूर्ण अन्यथा अणु
		ram_wr32(fuc, 0x10f988, 0x20010000);
		ram_wr32(fuc, 0x10f98c, 0x00000000);
		ram_wr32(fuc, 0x10f990, 0x20012001);
		ram_wr32(fuc, 0x10f998, 0x00010a00);
	पूर्ण

	अगर (from == 0) अणु
// 0x00020039 // 0x000000ba
	पूर्ण

// 0x0002003a // 0x00000002
	ram_wr32(fuc, 0x100b0c, 0x00080012);
// 0x00030014 // 0x00000000 // 0x02b5f070
// 0x00030014 // 0x00010000 // 0x02b5f070
	ram_wr32(fuc, 0x611200, 0x00003300);
// 0x00020034 // 0x0000000a
// 0x00030020 // 0x00000001 // 0x00000000

	ram_mask(fuc, 0x10f200, 0x00000800, 0x00000000);
	ram_wr32(fuc, 0x10f210, 0x00000000);
	ram_nsec(fuc, 1000);
	अगर (mode == 0)
		gf100_ram_train(fuc, 0x000c1001);
	ram_wr32(fuc, 0x10f310, 0x00000001);
	ram_nsec(fuc, 1000);
	ram_wr32(fuc, 0x10f090, 0x00000061);
	ram_wr32(fuc, 0x10f090, 0xc000007f);
	ram_nsec(fuc, 1000);

	अगर (from == 0) अणु
		ram_wr32(fuc, 0x10f824, 0x00007fd4);
	पूर्ण अन्यथा अणु
		ram_wr32(fuc, 0x1373ec, 0x00020404);
	पूर्ण

	अगर (mode == 0) अणु
		ram_mask(fuc, 0x10f808, 0x00080000, 0x00000000);
		ram_mask(fuc, 0x10f200, 0x00008000, 0x00008000);
		ram_wr32(fuc, 0x10f830, 0x41500010);
		ram_mask(fuc, 0x10f830, 0x01000000, 0x00000000);
		ram_mask(fuc, 0x132100, 0x00000100, 0x00000100);
		ram_wr32(fuc, 0x10f050, 0xff000090);
		ram_wr32(fuc, 0x1373ec, 0x00020f0f);
		ram_wr32(fuc, 0x1373f0, 0x00000003);
		ram_wr32(fuc, 0x137310, 0x81201616);
		ram_wr32(fuc, 0x132100, 0x00000001);
// 0x00020039 // 0x000000ba
		ram_wr32(fuc, 0x10f830, 0x00300017);
		ram_wr32(fuc, 0x1373f0, 0x00000001);
		ram_wr32(fuc, 0x10f824, 0x00007e77);
		ram_wr32(fuc, 0x132000, 0x18030001);
		ram_wr32(fuc, 0x10f090, 0x4000007e);
		ram_nsec(fuc, 2000);
		ram_wr32(fuc, 0x10f314, 0x00000001);
		ram_wr32(fuc, 0x10f210, 0x80000000);
		ram_wr32(fuc, 0x10f338, 0x00300220);
		ram_wr32(fuc, 0x10f300, 0x0000011d);
		ram_nsec(fuc, 1000);
		ram_wr32(fuc, 0x10f290, 0x02060505);
		ram_wr32(fuc, 0x10f294, 0x34208288);
		ram_wr32(fuc, 0x10f298, 0x44050411);
		ram_wr32(fuc, 0x10f29c, 0x0000114c);
		ram_wr32(fuc, 0x10f2a0, 0x42e10069);
		ram_wr32(fuc, 0x10f614, 0x40044f77);
		ram_wr32(fuc, 0x10f610, 0x40044f77);
		ram_wr32(fuc, 0x10f344, 0x00600009);
		ram_nsec(fuc, 1000);
		ram_wr32(fuc, 0x10f348, 0x00700008);
		ram_wr32(fuc, 0x61c140, 0x19240000);
		ram_wr32(fuc, 0x10f830, 0x00300017);
		gf100_ram_train(fuc, 0x80021001);
		gf100_ram_train(fuc, 0x80081001);
		ram_wr32(fuc, 0x10f340, 0x00500004);
		ram_nsec(fuc, 1000);
		ram_wr32(fuc, 0x10f830, 0x01300017);
		ram_wr32(fuc, 0x10f830, 0x00300017);
// 0x00030020 // 0x00000000 // 0x00000000
// 0x00020034 // 0x0000000b
		ram_wr32(fuc, 0x100b0c, 0x00080028);
		ram_wr32(fuc, 0x611200, 0x00003330);
	पूर्ण अन्यथा अणु
		ram_wr32(fuc, 0x10f800, 0x00001800);
		ram_wr32(fuc, 0x13d8f4, 0x00000000);
		ram_wr32(fuc, 0x1373ec, 0x00020404);
		ram_wr32(fuc, 0x1373f0, 0x00000003);
		ram_wr32(fuc, 0x10f830, 0x40700010);
		ram_wr32(fuc, 0x10f830, 0x40500010);
		ram_wr32(fuc, 0x13d8f4, 0x00000000);
		ram_wr32(fuc, 0x1373f8, 0x00000000);
		ram_wr32(fuc, 0x132100, 0x00000101);
		ram_wr32(fuc, 0x137310, 0x89201616);
		ram_wr32(fuc, 0x10f050, 0xff000090);
		ram_wr32(fuc, 0x1373ec, 0x00030404);
		ram_wr32(fuc, 0x1373f0, 0x00000002);
	// 0x00020039 // 0x00000011
		ram_wr32(fuc, 0x132100, 0x00000001);
		ram_wr32(fuc, 0x1373f8, 0x00002000);
		ram_nsec(fuc, 2000);
		ram_wr32(fuc, 0x10f808, 0x7aaa0050);
		ram_wr32(fuc, 0x10f830, 0x00500010);
		ram_wr32(fuc, 0x10f200, 0x00ce1000);
		ram_wr32(fuc, 0x10f090, 0x4000007e);
		ram_nsec(fuc, 2000);
		ram_wr32(fuc, 0x10f314, 0x00000001);
		ram_wr32(fuc, 0x10f210, 0x80000000);
		ram_wr32(fuc, 0x10f338, 0x00300200);
		ram_wr32(fuc, 0x10f300, 0x0000084d);
		ram_nsec(fuc, 1000);
		ram_wr32(fuc, 0x10f290, 0x0b343825);
		ram_wr32(fuc, 0x10f294, 0x3483028e);
		ram_wr32(fuc, 0x10f298, 0x440c0600);
		ram_wr32(fuc, 0x10f29c, 0x0000214c);
		ram_wr32(fuc, 0x10f2a0, 0x42e20069);
		ram_wr32(fuc, 0x10f200, 0x00ce0000);
		ram_wr32(fuc, 0x10f614, 0x60044e77);
		ram_wr32(fuc, 0x10f610, 0x60044e77);
		ram_wr32(fuc, 0x10f340, 0x00500000);
		ram_nsec(fuc, 1000);
		ram_wr32(fuc, 0x10f344, 0x00600228);
		ram_nsec(fuc, 1000);
		ram_wr32(fuc, 0x10f348, 0x00700000);
		ram_wr32(fuc, 0x13d8f4, 0x00000000);
		ram_wr32(fuc, 0x61c140, 0x09a40000);

		gf100_ram_train(fuc, 0x800e1008);

		ram_nsec(fuc, 1000);
		ram_wr32(fuc, 0x10f800, 0x00001804);
	// 0x00030020 // 0x00000000 // 0x00000000
	// 0x00020034 // 0x0000000b
		ram_wr32(fuc, 0x13d8f4, 0x00000000);
		ram_wr32(fuc, 0x100b0c, 0x00080028);
		ram_wr32(fuc, 0x611200, 0x00003330);
		ram_nsec(fuc, 100000);
		ram_wr32(fuc, 0x10f9b0, 0x05313f41);
		ram_wr32(fuc, 0x10f9b4, 0x00002f50);

		gf100_ram_train(fuc, 0x010c1001);
	पूर्ण

	ram_mask(fuc, 0x10f200, 0x00000800, 0x00000800);
// 0x00020016 // 0x00000000

	अगर (mode == 0)
		ram_mask(fuc, 0x132000, 0x00000001, 0x00000000);

	वापस 0;
पूर्ण

पूर्णांक
gf100_ram_prog(काष्ठा nvkm_ram *base)
अणु
	काष्ठा gf100_ram *ram = gf100_ram(base);
	काष्ठा nvkm_device *device = ram->base.fb->subdev.device;
	ram_exec(&ram->fuc, nvkm_boolopt(device->cfgopt, "NvMemExec", true));
	वापस 0;
पूर्ण

व्योम
gf100_ram_tidy(काष्ठा nvkm_ram *base)
अणु
	काष्ठा gf100_ram *ram = gf100_ram(base);
	ram_exec(&ram->fuc, false);
पूर्ण

पूर्णांक
gf100_ram_init(काष्ठा nvkm_ram *base)
अणु
	अटल स्थिर u8  train0[] = अणु
		0x00, 0xff, 0x55, 0xaa, 0x33, 0xcc,
		0x00, 0xff, 0xff, 0x00, 0xff, 0x00,
	पूर्ण;
	अटल स्थिर u32 train1[] = अणु
		0x00000000, 0xffffffff,
		0x55555555, 0xaaaaaaaa,
		0x33333333, 0xcccccccc,
		0xf0f0f0f0, 0x0f0f0f0f,
		0x00ff00ff, 0xff00ff00,
		0x0000ffff, 0xffff0000,
	पूर्ण;
	काष्ठा gf100_ram *ram = gf100_ram(base);
	काष्ठा nvkm_device *device = ram->base.fb->subdev.device;
	पूर्णांक i;

	चयन (ram->base.type) अणु
	हाल NVKM_RAM_TYPE_GDDR5:
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	/* prepare क्रम ddr link training, and load training patterns */
	क्रम (i = 0; i < 0x30; i++) अणु
		nvkm_wr32(device, 0x10f968, 0x00000000 | (i << 8));
		nvkm_wr32(device, 0x10f96c, 0x00000000 | (i << 8));
		nvkm_wr32(device, 0x10f920, 0x00000100 | train0[i % 12]);
		nvkm_wr32(device, 0x10f924, 0x00000100 | train0[i % 12]);
		nvkm_wr32(device, 0x10f918,              train1[i % 12]);
		nvkm_wr32(device, 0x10f91c,              train1[i % 12]);
		nvkm_wr32(device, 0x10f920, 0x00000000 | train0[i % 12]);
		nvkm_wr32(device, 0x10f924, 0x00000000 | train0[i % 12]);
		nvkm_wr32(device, 0x10f918,              train1[i % 12]);
		nvkm_wr32(device, 0x10f91c,              train1[i % 12]);
	पूर्ण

	वापस 0;
पूर्ण

u32
gf100_ram_probe_fbpa_amount(काष्ठा nvkm_device *device, पूर्णांक fbpa)
अणु
	वापस nvkm_rd32(device, 0x11020c + (fbpa * 0x1000));
पूर्ण

u32
gf100_ram_probe_fbp_amount(स्थिर काष्ठा nvkm_ram_func *func, u32 fbpao,
			   काष्ठा nvkm_device *device, पूर्णांक fbp, पूर्णांक *pltcs)
अणु
	अगर (!(fbpao & BIT(fbp))) अणु
		*pltcs = 1;
		वापस func->probe_fbpa_amount(device, fbp);
	पूर्ण
	वापस 0;
पूर्ण

u32
gf100_ram_probe_fbp(स्थिर काष्ठा nvkm_ram_func *func,
		    काष्ठा nvkm_device *device, पूर्णांक fbp, पूर्णांक *pltcs)
अणु
	u32 fbpao = nvkm_rd32(device, 0x022554);
	वापस func->probe_fbp_amount(func, fbpao, device, fbp, pltcs);
पूर्ण

पूर्णांक
gf100_ram_ctor(स्थिर काष्ठा nvkm_ram_func *func, काष्ठा nvkm_fb *fb,
	       काष्ठा nvkm_ram *ram)
अणु
	काष्ठा nvkm_subdev *subdev = &fb->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_bios *bios = device->bios;
	स्थिर u32 rsvd_head = ( 256 * 1024); /* vga memory */
	स्थिर u32 rsvd_tail = (1024 * 1024); /* vbios etc */
	क्रमागत nvkm_ram_type type = nvkm_fb_bios_memtype(bios);
	u32 fbps = nvkm_rd32(device, 0x022438);
	u64 total = 0, lcomm = ~0, lower, ubase, usize;
	पूर्णांक ret, fbp, ltcs, ltcn = 0;

	nvkm_debug(subdev, "%d FBP(s)\n", fbps);
	क्रम (fbp = 0; fbp < fbps; fbp++) अणु
		u32 size = func->probe_fbp(func, device, fbp, &ltcs);
		अगर (size) अणु
			nvkm_debug(subdev, "FBP %d: %4d MiB, %d LTC(s)\n",
				   fbp, size, ltcs);
			lcomm  = min(lcomm, (u64)(size / ltcs) << 20);
			total += (u64) size << 20;
			ltcn  += ltcs;
		पूर्ण अन्यथा अणु
			nvkm_debug(subdev, "FBP %d: disabled\n", fbp);
		पूर्ण
	पूर्ण

	lower = lcomm * ltcn;
	ubase = lcomm + func->upper;
	usize = total - lower;

	nvkm_debug(subdev, "Lower: %4lld MiB @ %010llx\n", lower >> 20, 0ULL);
	nvkm_debug(subdev, "Upper: %4lld MiB @ %010llx\n", usize >> 20, ubase);
	nvkm_debug(subdev, "Total: %4lld MiB\n", total >> 20);

	ret = nvkm_ram_ctor(func, fb, type, total, ram);
	अगर (ret)
		वापस ret;

	nvkm_mm_fini(&ram->vram);

	/* Some GPUs are in what's known as a "mixed memory" configuration.
	 *
	 * This is either where some FBPs have more memory than the others,
	 * or where LTCs have been disabled on a FBP.
	 */
	अगर (lower != total) अणु
		/* The common memory amount is addressed normally. */
		ret = nvkm_mm_init(&ram->vram, NVKM_RAM_MM_NORMAL,
				   rsvd_head >> NVKM_RAM_MM_SHIFT,
				   (lower - rsvd_head) >> NVKM_RAM_MM_SHIFT, 1);
		अगर (ret)
			वापस ret;

		/* And the rest is much higher in the physical address
		 * space, and may not be usable क्रम certain operations.
		 */
		ret = nvkm_mm_init(&ram->vram, NVKM_RAM_MM_MIXED,
				   ubase >> NVKM_RAM_MM_SHIFT,
				   (usize - rsvd_tail) >> NVKM_RAM_MM_SHIFT, 1);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		/* GPUs without mixed-memory are a lot nicer... */
		ret = nvkm_mm_init(&ram->vram, NVKM_RAM_MM_NORMAL,
				   rsvd_head >> NVKM_RAM_MM_SHIFT,
				   (total - rsvd_head - rsvd_tail) >>
				   NVKM_RAM_MM_SHIFT, 1);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
gf100_ram_new_(स्थिर काष्ठा nvkm_ram_func *func,
	       काष्ठा nvkm_fb *fb, काष्ठा nvkm_ram **pram)
अणु
	काष्ठा nvkm_subdev *subdev = &fb->subdev;
	काष्ठा nvkm_bios *bios = subdev->device->bios;
	काष्ठा gf100_ram *ram;
	पूर्णांक ret;

	अगर (!(ram = kzalloc(माप(*ram), GFP_KERNEL)))
		वापस -ENOMEM;
	*pram = &ram->base;

	ret = gf100_ram_ctor(func, fb, &ram->base);
	अगर (ret)
		वापस ret;

	ret = nvbios_pll_parse(bios, 0x0c, &ram->refpll);
	अगर (ret) अणु
		nvkm_error(subdev, "mclk refpll data not found\n");
		वापस ret;
	पूर्ण

	ret = nvbios_pll_parse(bios, 0x04, &ram->mempll);
	अगर (ret) अणु
		nvkm_error(subdev, "mclk pll data not found\n");
		वापस ret;
	पूर्ण

	ram->fuc.r_0x10fe20 = ramfuc_reg(0x10fe20);
	ram->fuc.r_0x10fe24 = ramfuc_reg(0x10fe24);
	ram->fuc.r_0x137320 = ramfuc_reg(0x137320);
	ram->fuc.r_0x137330 = ramfuc_reg(0x137330);

	ram->fuc.r_0x132000 = ramfuc_reg(0x132000);
	ram->fuc.r_0x132004 = ramfuc_reg(0x132004);
	ram->fuc.r_0x132100 = ramfuc_reg(0x132100);

	ram->fuc.r_0x137390 = ramfuc_reg(0x137390);

	ram->fuc.r_0x10f290 = ramfuc_reg(0x10f290);
	ram->fuc.r_0x10f294 = ramfuc_reg(0x10f294);
	ram->fuc.r_0x10f298 = ramfuc_reg(0x10f298);
	ram->fuc.r_0x10f29c = ramfuc_reg(0x10f29c);
	ram->fuc.r_0x10f2a0 = ramfuc_reg(0x10f2a0);

	ram->fuc.r_0x10f300 = ramfuc_reg(0x10f300);
	ram->fuc.r_0x10f338 = ramfuc_reg(0x10f338);
	ram->fuc.r_0x10f340 = ramfuc_reg(0x10f340);
	ram->fuc.r_0x10f344 = ramfuc_reg(0x10f344);
	ram->fuc.r_0x10f348 = ramfuc_reg(0x10f348);

	ram->fuc.r_0x10f910 = ramfuc_reg(0x10f910);
	ram->fuc.r_0x10f914 = ramfuc_reg(0x10f914);

	ram->fuc.r_0x100b0c = ramfuc_reg(0x100b0c);
	ram->fuc.r_0x10f050 = ramfuc_reg(0x10f050);
	ram->fuc.r_0x10f090 = ramfuc_reg(0x10f090);
	ram->fuc.r_0x10f200 = ramfuc_reg(0x10f200);
	ram->fuc.r_0x10f210 = ramfuc_reg(0x10f210);
	ram->fuc.r_0x10f310 = ramfuc_reg(0x10f310);
	ram->fuc.r_0x10f314 = ramfuc_reg(0x10f314);
	ram->fuc.r_0x10f610 = ramfuc_reg(0x10f610);
	ram->fuc.r_0x10f614 = ramfuc_reg(0x10f614);
	ram->fuc.r_0x10f800 = ramfuc_reg(0x10f800);
	ram->fuc.r_0x10f808 = ramfuc_reg(0x10f808);
	ram->fuc.r_0x10f824 = ramfuc_reg(0x10f824);
	ram->fuc.r_0x10f830 = ramfuc_reg(0x10f830);
	ram->fuc.r_0x10f988 = ramfuc_reg(0x10f988);
	ram->fuc.r_0x10f98c = ramfuc_reg(0x10f98c);
	ram->fuc.r_0x10f990 = ramfuc_reg(0x10f990);
	ram->fuc.r_0x10f998 = ramfuc_reg(0x10f998);
	ram->fuc.r_0x10f9b0 = ramfuc_reg(0x10f9b0);
	ram->fuc.r_0x10f9b4 = ramfuc_reg(0x10f9b4);
	ram->fuc.r_0x10fb04 = ramfuc_reg(0x10fb04);
	ram->fuc.r_0x10fb08 = ramfuc_reg(0x10fb08);
	ram->fuc.r_0x137310 = ramfuc_reg(0x137300);
	ram->fuc.r_0x137310 = ramfuc_reg(0x137310);
	ram->fuc.r_0x137360 = ramfuc_reg(0x137360);
	ram->fuc.r_0x1373ec = ramfuc_reg(0x1373ec);
	ram->fuc.r_0x1373f0 = ramfuc_reg(0x1373f0);
	ram->fuc.r_0x1373f8 = ramfuc_reg(0x1373f8);

	ram->fuc.r_0x61c140 = ramfuc_reg(0x61c140);
	ram->fuc.r_0x611200 = ramfuc_reg(0x611200);

	ram->fuc.r_0x13d8f4 = ramfuc_reg(0x13d8f4);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_ram_func
gf100_ram = अणु
	.upper = 0x0200000000ULL,
	.probe_fbp = gf100_ram_probe_fbp,
	.probe_fbp_amount = gf100_ram_probe_fbp_amount,
	.probe_fbpa_amount = gf100_ram_probe_fbpa_amount,
	.init = gf100_ram_init,
	.calc = gf100_ram_calc,
	.prog = gf100_ram_prog,
	.tidy = gf100_ram_tidy,
पूर्ण;

पूर्णांक
gf100_ram_new(काष्ठा nvkm_fb *fb, काष्ठा nvkm_ram **pram)
अणु
	वापस gf100_ram_new_(&gf100_ram, fb, pram);
पूर्ण
