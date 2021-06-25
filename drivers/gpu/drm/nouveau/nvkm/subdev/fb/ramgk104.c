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
#घोषणा gk104_ram(p) container_of((p), काष्ठा gk104_ram, base)
#समावेश "ram.h"
#समावेश "ramfuc.h"

#समावेश <core/option.h>
#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/init.h>
#समावेश <subdev/bios/M0205.h>
#समावेश <subdev/bios/M0209.h>
#समावेश <subdev/bios/pll.h>
#समावेश <subdev/bios/rammap.h>
#समावेश <subdev/bios/timing.h>
#समावेश <subdev/clk.h>
#समावेश <subdev/clk/pll.h>
#समावेश <subdev/gpपन.स>

काष्ठा gk104_ramfuc अणु
	काष्ठा ramfuc base;

	काष्ठा nvbios_pll refpll;
	काष्ठा nvbios_pll mempll;

	काष्ठा ramfuc_reg r_gpioMV;
	u32 r_funcMV[2];
	काष्ठा ramfuc_reg r_gpio2E;
	u32 r_func2E[2];
	काष्ठा ramfuc_reg r_gpiotrig;

	काष्ठा ramfuc_reg r_0x132020;
	काष्ठा ramfuc_reg r_0x132028;
	काष्ठा ramfuc_reg r_0x132024;
	काष्ठा ramfuc_reg r_0x132030;
	काष्ठा ramfuc_reg r_0x132034;
	काष्ठा ramfuc_reg r_0x132000;
	काष्ठा ramfuc_reg r_0x132004;
	काष्ठा ramfuc_reg r_0x132040;

	काष्ठा ramfuc_reg r_0x10f248;
	काष्ठा ramfuc_reg r_0x10f290;
	काष्ठा ramfuc_reg r_0x10f294;
	काष्ठा ramfuc_reg r_0x10f298;
	काष्ठा ramfuc_reg r_0x10f29c;
	काष्ठा ramfuc_reg r_0x10f2a0;
	काष्ठा ramfuc_reg r_0x10f2a4;
	काष्ठा ramfuc_reg r_0x10f2a8;
	काष्ठा ramfuc_reg r_0x10f2ac;
	काष्ठा ramfuc_reg r_0x10f2cc;
	काष्ठा ramfuc_reg r_0x10f2e8;
	काष्ठा ramfuc_reg r_0x10f250;
	काष्ठा ramfuc_reg r_0x10f24c;
	काष्ठा ramfuc_reg r_0x10fec4;
	काष्ठा ramfuc_reg r_0x10fec8;
	काष्ठा ramfuc_reg r_0x10f604;
	काष्ठा ramfuc_reg r_0x10f614;
	काष्ठा ramfuc_reg r_0x10f610;
	काष्ठा ramfuc_reg r_0x100770;
	काष्ठा ramfuc_reg r_0x100778;
	काष्ठा ramfuc_reg r_0x10f224;

	काष्ठा ramfuc_reg r_0x10f870;
	काष्ठा ramfuc_reg r_0x10f698;
	काष्ठा ramfuc_reg r_0x10f694;
	काष्ठा ramfuc_reg r_0x10f6b8;
	काष्ठा ramfuc_reg r_0x10f808;
	काष्ठा ramfuc_reg r_0x10f670;
	काष्ठा ramfuc_reg r_0x10f60c;
	काष्ठा ramfuc_reg r_0x10f830;
	काष्ठा ramfuc_reg r_0x1373ec;
	काष्ठा ramfuc_reg r_0x10f800;
	काष्ठा ramfuc_reg r_0x10f82c;

	काष्ठा ramfuc_reg r_0x10f978;
	काष्ठा ramfuc_reg r_0x10f910;
	काष्ठा ramfuc_reg r_0x10f914;

	काष्ठा ramfuc_reg r_mr[16]; /* MR0 - MR8, MR15 */

	काष्ठा ramfuc_reg r_0x62c000;

	काष्ठा ramfuc_reg r_0x10f200;

	काष्ठा ramfuc_reg r_0x10f210;
	काष्ठा ramfuc_reg r_0x10f310;
	काष्ठा ramfuc_reg r_0x10f314;
	काष्ठा ramfuc_reg r_0x10f318;
	काष्ठा ramfuc_reg r_0x10f090;
	काष्ठा ramfuc_reg r_0x10f69c;
	काष्ठा ramfuc_reg r_0x10f824;
	काष्ठा ramfuc_reg r_0x1373f0;
	काष्ठा ramfuc_reg r_0x1373f4;
	काष्ठा ramfuc_reg r_0x137320;
	काष्ठा ramfuc_reg r_0x10f65c;
	काष्ठा ramfuc_reg r_0x10f6bc;
	काष्ठा ramfuc_reg r_0x100710;
	काष्ठा ramfuc_reg r_0x100750;
पूर्ण;

काष्ठा gk104_ram अणु
	काष्ठा nvkm_ram base;
	काष्ठा gk104_ramfuc fuc;

	काष्ठा list_head cfg;
	u32 parts;
	u32 pmask;
	u32 pnuts;

	काष्ठा nvbios_ramcfg dअगरf;
	पूर्णांक from;
	पूर्णांक mode;
	पूर्णांक N1, fN1, M1, P1;
	पूर्णांक N2, M2, P2;
पूर्ण;

/*******************************************************************************
 * GDDR5
 ******************************************************************************/
अटल व्योम
gk104_ram_train(काष्ठा gk104_ramfuc *fuc, u32 mask, u32 data)
अणु
	काष्ठा gk104_ram *ram = container_of(fuc, typeof(*ram), fuc);
	u32 addr = 0x110974, i;

	ram_mask(fuc, 0x10f910, mask, data);
	ram_mask(fuc, 0x10f914, mask, data);

	क्रम (i = 0; (data & 0x80000000) && i < ram->parts; addr += 0x1000, i++) अणु
		अगर (ram->pmask & (1 << i))
			जारी;
		ram_रुको(fuc, addr, 0x0000000f, 0x00000000, 500000);
	पूर्ण
पूर्ण

अटल व्योम
r1373f4_init(काष्ठा gk104_ramfuc *fuc)
अणु
	काष्ठा gk104_ram *ram = container_of(fuc, typeof(*ram), fuc);
	स्थिर u32 mcoef = ((--ram->P2 << 28) | (ram->N2 << 8) | ram->M2);
	स्थिर u32 rcoef = ((  ram->P1 << 16) | (ram->N1 << 8) | ram->M1);
	स्थिर u32 runk0 = ram->fN1 << 16;
	स्थिर u32 runk1 = ram->fN1;

	अगर (ram->from == 2) अणु
		ram_mask(fuc, 0x1373f4, 0x00000000, 0x00001100);
		ram_mask(fuc, 0x1373f4, 0x00000000, 0x00000010);
	पूर्ण अन्यथा अणु
		ram_mask(fuc, 0x1373f4, 0x00000000, 0x00010010);
	पूर्ण

	ram_mask(fuc, 0x1373f4, 0x00000003, 0x00000000);
	ram_mask(fuc, 0x1373f4, 0x00000010, 0x00000000);

	/* (re)program refpll, अगर required */
	अगर ((ram_rd32(fuc, 0x132024) & 0xffffffff) != rcoef ||
	    (ram_rd32(fuc, 0x132034) & 0x0000ffff) != runk1) अणु
		ram_mask(fuc, 0x132000, 0x00000001, 0x00000000);
		ram_mask(fuc, 0x132020, 0x00000001, 0x00000000);
		ram_wr32(fuc, 0x137320, 0x00000000);
		ram_mask(fuc, 0x132030, 0xffff0000, runk0);
		ram_mask(fuc, 0x132034, 0x0000ffff, runk1);
		ram_wr32(fuc, 0x132024, rcoef);
		ram_mask(fuc, 0x132028, 0x00080000, 0x00080000);
		ram_mask(fuc, 0x132020, 0x00000001, 0x00000001);
		ram_रुको(fuc, 0x137390, 0x00020000, 0x00020000, 64000);
		ram_mask(fuc, 0x132028, 0x00080000, 0x00000000);
	पूर्ण

	/* (re)program mempll, अगर required */
	अगर (ram->mode == 2) अणु
		ram_mask(fuc, 0x1373f4, 0x00010000, 0x00000000);
		ram_mask(fuc, 0x132000, 0x80000000, 0x80000000);
		ram_mask(fuc, 0x132000, 0x00000001, 0x00000000);
		ram_mask(fuc, 0x132004, 0x103fffff, mcoef);
		ram_mask(fuc, 0x132000, 0x00000001, 0x00000001);
		ram_रुको(fuc, 0x137390, 0x00000002, 0x00000002, 64000);
		ram_mask(fuc, 0x1373f4, 0x00000000, 0x00001100);
	पूर्ण अन्यथा अणु
		ram_mask(fuc, 0x1373f4, 0x00000000, 0x00010100);
	पूर्ण

	ram_mask(fuc, 0x1373f4, 0x00000000, 0x00000010);
पूर्ण

अटल व्योम
r1373f4_fini(काष्ठा gk104_ramfuc *fuc)
अणु
	काष्ठा gk104_ram *ram = container_of(fuc, typeof(*ram), fuc);
	काष्ठा nvkm_ram_data *next = ram->base.next;
	u8 v0 = next->bios.ramcfg_11_03_c0;
	u8 v1 = next->bios.ramcfg_11_03_30;
	u32 पंचांगp;

	पंचांगp = ram_rd32(fuc, 0x1373ec) & ~0x00030000;
	ram_wr32(fuc, 0x1373ec, पंचांगp | (v1 << 16));
	ram_mask(fuc, 0x1373f0, (~ram->mode & 3), 0x00000000);
	अगर (ram->mode == 2) अणु
		ram_mask(fuc, 0x1373f4, 0x00000003, 0x00000002);
		ram_mask(fuc, 0x1373f4, 0x00001100, 0x00000000);
	पूर्ण अन्यथा अणु
		ram_mask(fuc, 0x1373f4, 0x00000003, 0x00000001);
		ram_mask(fuc, 0x1373f4, 0x00010000, 0x00000000);
	पूर्ण
	ram_mask(fuc, 0x10f800, 0x00000030, (v0 ^ v1) << 4);
पूर्ण

अटल व्योम
gk104_ram_nuts(काष्ठा gk104_ram *ram, काष्ठा ramfuc_reg *reg,
	       u32 _mask, u32 _data, u32 _copy)
अणु
	काष्ठा nvkm_fb *fb = ram->base.fb;
	काष्ठा ramfuc *fuc = &ram->fuc.base;
	काष्ठा nvkm_device *device = fb->subdev.device;
	u32 addr = 0x110000 + (reg->addr & 0xfff);
	u32 mask = _mask | _copy;
	u32 data = (_data & _mask) | (reg->data & _copy);
	u32 i;

	क्रम (i = 0; i < 16; i++, addr += 0x1000) अणु
		अगर (ram->pnuts & (1 << i)) अणु
			u32 prev = nvkm_rd32(device, addr);
			u32 next = (prev & ~mask) | data;
			nvkm_memx_wr32(fuc->memx, addr, next);
		पूर्ण
	पूर्ण
पूर्ण
#घोषणा ram_nuts(s,r,m,d,c)                                                    \
	gk104_ram_nuts((s), &(s)->fuc.r_##r, (m), (d), (c))

अटल पूर्णांक
gk104_ram_calc_gddr5(काष्ठा gk104_ram *ram, u32 freq)
अणु
	काष्ठा gk104_ramfuc *fuc = &ram->fuc;
	काष्ठा nvkm_ram_data *next = ram->base.next;
	पूर्णांक vc = !next->bios.ramcfg_11_02_08;
	पूर्णांक mv = !next->bios.ramcfg_11_02_04;
	u32 mask, data;

	ram_mask(fuc, 0x10f808, 0x40000000, 0x40000000);
	ram_block(fuc);

	अगर (ram->base.fb->subdev.device->disp)
		ram_wr32(fuc, 0x62c000, 0x0f0f0000);

	/* MR1: turn termination on early, क्रम some reason.. */
	अगर ((ram->base.mr[1] & 0x03c) != 0x030) अणु
		ram_mask(fuc, mr[1], 0x03c, ram->base.mr[1] & 0x03c);
		ram_nuts(ram, mr[1], 0x03c, ram->base.mr1_nuts & 0x03c, 0x000);
	पूर्ण

	अगर (vc == 1 && ram_have(fuc, gpio2E)) अणु
		u32 temp  = ram_mask(fuc, gpio2E, 0x3000, fuc->r_func2E[1]);
		अगर (temp != ram_rd32(fuc, gpio2E)) अणु
			ram_wr32(fuc, gpiotrig, 1);
			ram_nsec(fuc, 20000);
		पूर्ण
	पूर्ण

	ram_mask(fuc, 0x10f200, 0x00000800, 0x00000000);

	gk104_ram_train(fuc, 0x01020000, 0x000c0000);

	ram_wr32(fuc, 0x10f210, 0x00000000); /* REFRESH_AUTO = 0 */
	ram_nsec(fuc, 1000);
	ram_wr32(fuc, 0x10f310, 0x00000001); /* REFRESH */
	ram_nsec(fuc, 1000);

	ram_mask(fuc, 0x10f200, 0x80000000, 0x80000000);
	ram_wr32(fuc, 0x10f314, 0x00000001); /* PRECHARGE */
	ram_mask(fuc, 0x10f200, 0x80000000, 0x00000000);
	ram_wr32(fuc, 0x10f090, 0x00000061);
	ram_wr32(fuc, 0x10f090, 0xc000007f);
	ram_nsec(fuc, 1000);

	ram_wr32(fuc, 0x10f698, 0x00000000);
	ram_wr32(fuc, 0x10f69c, 0x00000000);

	/*XXX: there करोes appear to be some kind of condition here, simply
	 *     modअगरying these bits in the vbios from the शेष pl0
	 *     entries shows no change.  however, the data करोes appear to
	 *     be correct and may be required क्रम the transition back
	 */
	mask = 0x800f07e0;
	data = 0x00030000;
	अगर (ram_rd32(fuc, 0x10f978) & 0x00800000)
		data |= 0x00040000;

	अगर (1) अणु
		data |= 0x800807e0;
		चयन (next->bios.ramcfg_11_03_c0) अणु
		हाल 3: data &= ~0x00000040; अवरोध;
		हाल 2: data &= ~0x00000100; अवरोध;
		हाल 1: data &= ~0x80000000; अवरोध;
		हाल 0: data &= ~0x00000400; अवरोध;
		पूर्ण

		चयन (next->bios.ramcfg_11_03_30) अणु
		हाल 3: data &= ~0x00000020; अवरोध;
		हाल 2: data &= ~0x00000080; अवरोध;
		हाल 1: data &= ~0x00080000; अवरोध;
		हाल 0: data &= ~0x00000200; अवरोध;
		पूर्ण
	पूर्ण

	अगर (next->bios.ramcfg_11_02_80)
		mask |= 0x03000000;
	अगर (next->bios.ramcfg_11_02_40)
		mask |= 0x00002000;
	अगर (next->bios.ramcfg_11_07_10)
		mask |= 0x00004000;
	अगर (next->bios.ramcfg_11_07_08)
		mask |= 0x00000003;
	अन्यथा अणु
		mask |= 0x34000000;
		अगर (ram_rd32(fuc, 0x10f978) & 0x00800000)
			mask |= 0x40000000;
	पूर्ण
	ram_mask(fuc, 0x10f824, mask, data);

	ram_mask(fuc, 0x132040, 0x00010000, 0x00000000);

	अगर (ram->from == 2 && ram->mode != 2) अणु
		ram_mask(fuc, 0x10f808, 0x00080000, 0x00000000);
		ram_mask(fuc, 0x10f200, 0x18008000, 0x00008000);
		ram_mask(fuc, 0x10f800, 0x00000000, 0x00000004);
		ram_mask(fuc, 0x10f830, 0x00008000, 0x01040010);
		ram_mask(fuc, 0x10f830, 0x01000000, 0x00000000);
		r1373f4_init(fuc);
		ram_mask(fuc, 0x1373f0, 0x00000002, 0x00000001);
		r1373f4_fini(fuc);
		ram_mask(fuc, 0x10f830, 0x00c00000, 0x00240001);
	पूर्ण अन्यथा
	अगर (ram->from != 2 && ram->mode != 2) अणु
		r1373f4_init(fuc);
		r1373f4_fini(fuc);
	पूर्ण

	अगर (ram_have(fuc, gpioMV)) अणु
		u32 temp  = ram_mask(fuc, gpioMV, 0x3000, fuc->r_funcMV[mv]);
		अगर (temp != ram_rd32(fuc, gpioMV)) अणु
			ram_wr32(fuc, gpiotrig, 1);
			ram_nsec(fuc, 64000);
		पूर्ण
	पूर्ण

	अगर (next->bios.ramcfg_11_02_40 ||
	    next->bios.ramcfg_11_07_10) अणु
		ram_mask(fuc, 0x132040, 0x00010000, 0x00010000);
		ram_nsec(fuc, 20000);
	पूर्ण

	अगर (ram->from != 2 && ram->mode == 2) अणु
		अगर (0 /*XXX: Titan */)
			ram_mask(fuc, 0x10f200, 0x18000000, 0x18000000);
		ram_mask(fuc, 0x10f800, 0x00000004, 0x00000000);
		ram_mask(fuc, 0x1373f0, 0x00000000, 0x00000002);
		ram_mask(fuc, 0x10f830, 0x00800001, 0x00408010);
		r1373f4_init(fuc);
		r1373f4_fini(fuc);
		ram_mask(fuc, 0x10f808, 0x00000000, 0x00080000);
		ram_mask(fuc, 0x10f200, 0x00808000, 0x00800000);
	पूर्ण अन्यथा
	अगर (ram->from == 2 && ram->mode == 2) अणु
		ram_mask(fuc, 0x10f800, 0x00000004, 0x00000000);
		r1373f4_init(fuc);
		r1373f4_fini(fuc);
	पूर्ण

	अगर (ram->mode != 2) /*XXX*/ अणु
		अगर (next->bios.ramcfg_11_07_40)
			ram_mask(fuc, 0x10f670, 0x80000000, 0x80000000);
	पूर्ण

	ram_wr32(fuc, 0x10f65c, 0x00000011 * next->bios.rammap_11_11_0c);
	ram_wr32(fuc, 0x10f6b8, 0x01010101 * next->bios.ramcfg_11_09);
	ram_wr32(fuc, 0x10f6bc, 0x01010101 * next->bios.ramcfg_11_09);

	अगर (!next->bios.ramcfg_11_07_08 && !next->bios.ramcfg_11_07_04) अणु
		ram_wr32(fuc, 0x10f698, 0x01010101 * next->bios.ramcfg_11_04);
		ram_wr32(fuc, 0x10f69c, 0x01010101 * next->bios.ramcfg_11_04);
	पूर्ण अन्यथा
	अगर (!next->bios.ramcfg_11_07_08) अणु
		ram_wr32(fuc, 0x10f698, 0x00000000);
		ram_wr32(fuc, 0x10f69c, 0x00000000);
	पूर्ण

	अगर (ram->mode != 2) अणु
		u32 data = 0x01000100 * next->bios.ramcfg_11_04;
		ram_nuke(fuc, 0x10f694);
		ram_mask(fuc, 0x10f694, 0xff00ff00, data);
	पूर्ण

	अगर (ram->mode == 2 && next->bios.ramcfg_11_08_10)
		data = 0x00000080;
	अन्यथा
		data = 0x00000000;
	ram_mask(fuc, 0x10f60c, 0x00000080, data);

	mask = 0x00070000;
	data = 0x00000000;
	अगर (!next->bios.ramcfg_11_02_80)
		data |= 0x03000000;
	अगर (!next->bios.ramcfg_11_02_40)
		data |= 0x00002000;
	अगर (!next->bios.ramcfg_11_07_10)
		data |= 0x00004000;
	अगर (!next->bios.ramcfg_11_07_08)
		data |= 0x00000003;
	अन्यथा
		data |= 0x74000000;
	ram_mask(fuc, 0x10f824, mask, data);

	अगर (next->bios.ramcfg_11_01_08)
		data = 0x00000000;
	अन्यथा
		data = 0x00001000;
	ram_mask(fuc, 0x10f200, 0x00001000, data);

	अगर (ram_rd32(fuc, 0x10f670) & 0x80000000) अणु
		ram_nsec(fuc, 10000);
		ram_mask(fuc, 0x10f670, 0x80000000, 0x00000000);
	पूर्ण

	अगर (next->bios.ramcfg_11_08_01)
		data = 0x00100000;
	अन्यथा
		data = 0x00000000;
	ram_mask(fuc, 0x10f82c, 0x00100000, data);

	data = 0x00000000;
	अगर (next->bios.ramcfg_11_08_08)
		data |= 0x00002000;
	अगर (next->bios.ramcfg_11_08_04)
		data |= 0x00001000;
	अगर (next->bios.ramcfg_11_08_02)
		data |= 0x00004000;
	ram_mask(fuc, 0x10f830, 0x00007000, data);

	/* PFB timing */
	ram_mask(fuc, 0x10f248, 0xffffffff, next->bios.timing[10]);
	ram_mask(fuc, 0x10f290, 0xffffffff, next->bios.timing[0]);
	ram_mask(fuc, 0x10f294, 0xffffffff, next->bios.timing[1]);
	ram_mask(fuc, 0x10f298, 0xffffffff, next->bios.timing[2]);
	ram_mask(fuc, 0x10f29c, 0xffffffff, next->bios.timing[3]);
	ram_mask(fuc, 0x10f2a0, 0xffffffff, next->bios.timing[4]);
	ram_mask(fuc, 0x10f2a4, 0xffffffff, next->bios.timing[5]);
	ram_mask(fuc, 0x10f2a8, 0xffffffff, next->bios.timing[6]);
	ram_mask(fuc, 0x10f2ac, 0xffffffff, next->bios.timing[7]);
	ram_mask(fuc, 0x10f2cc, 0xffffffff, next->bios.timing[8]);
	ram_mask(fuc, 0x10f2e8, 0xffffffff, next->bios.timing[9]);

	data = mask = 0x00000000;
	अगर (ram->dअगरf.ramcfg_11_08_20) अणु
		अगर (next->bios.ramcfg_11_08_20)
			data |= 0x01000000;
		mask |= 0x01000000;
	पूर्ण
	ram_mask(fuc, 0x10f200, mask, data);

	data = mask = 0x00000000;
	अगर (ram->dअगरf.ramcfg_11_02_03) अणु
		data |= next->bios.ramcfg_11_02_03 << 8;
		mask |= 0x00000300;
	पूर्ण
	अगर (ram->dअगरf.ramcfg_11_01_10) अणु
		अगर (next->bios.ramcfg_11_01_10)
			data |= 0x70000000;
		mask |= 0x70000000;
	पूर्ण
	ram_mask(fuc, 0x10f604, mask, data);

	data = mask = 0x00000000;
	अगर (ram->dअगरf.timing_20_30_07) अणु
		data |= next->bios.timing_20_30_07 << 28;
		mask |= 0x70000000;
	पूर्ण
	अगर (ram->dअगरf.ramcfg_11_01_01) अणु
		अगर (next->bios.ramcfg_11_01_01)
			data |= 0x00000100;
		mask |= 0x00000100;
	पूर्ण
	ram_mask(fuc, 0x10f614, mask, data);

	data = mask = 0x00000000;
	अगर (ram->dअगरf.timing_20_30_07) अणु
		data |= next->bios.timing_20_30_07 << 28;
		mask |= 0x70000000;
	पूर्ण
	अगर (ram->dअगरf.ramcfg_11_01_02) अणु
		अगर (next->bios.ramcfg_11_01_02)
			data |= 0x00000100;
		mask |= 0x00000100;
	पूर्ण
	ram_mask(fuc, 0x10f610, mask, data);

	mask = 0x33f00000;
	data = 0x00000000;
	अगर (!next->bios.ramcfg_11_01_04)
		data |= 0x20200000;
	अगर (!next->bios.ramcfg_11_07_80)
		data |= 0x12800000;
	/*XXX: see note above about there probably being some condition
	 *     क्रम the 10f824 stuff that uses ramcfg 3...
	 */
	अगर (next->bios.ramcfg_11_03_f0) अणु
		अगर (next->bios.rammap_11_08_0c) अणु
			अगर (!next->bios.ramcfg_11_07_80)
				mask |= 0x00000020;
			अन्यथा
				data |= 0x00000020;
			mask |= 0x00000004;
		पूर्ण
	पूर्ण अन्यथा अणु
		mask |= 0x40000020;
		data |= 0x00000004;
	पूर्ण

	ram_mask(fuc, 0x10f808, mask, data);

	ram_wr32(fuc, 0x10f870, 0x11111111 * next->bios.ramcfg_11_03_0f);

	data = mask = 0x00000000;
	अगर (ram->dअगरf.ramcfg_11_02_03) अणु
		data |= next->bios.ramcfg_11_02_03;
		mask |= 0x00000003;
	पूर्ण
	अगर (ram->dअगरf.ramcfg_11_01_10) अणु
		अगर (next->bios.ramcfg_11_01_10)
			data |= 0x00000004;
		mask |= 0x00000004;
	पूर्ण

	अगर ((ram_mask(fuc, 0x100770, mask, data) & mask & 4) != (data & 4)) अणु
		ram_mask(fuc, 0x100750, 0x00000008, 0x00000008);
		ram_wr32(fuc, 0x100710, 0x00000000);
		ram_रुको(fuc, 0x100710, 0x80000000, 0x80000000, 200000);
	पूर्ण

	data = next->bios.timing_20_30_07 << 8;
	अगर (next->bios.ramcfg_11_01_01)
		data |= 0x80000000;
	ram_mask(fuc, 0x100778, 0x00000700, data);

	ram_mask(fuc, 0x10f250, 0x000003f0, next->bios.timing_20_2c_003f << 4);
	data = (next->bios.timing[10] & 0x7f000000) >> 24;
	अगर (data < next->bios.timing_20_2c_1fc0)
		data = next->bios.timing_20_2c_1fc0;
	ram_mask(fuc, 0x10f24c, 0x7f000000, data << 24);
	ram_mask(fuc, 0x10f224, 0x001f0000, next->bios.timing_20_30_f8 << 16);

	ram_mask(fuc, 0x10fec4, 0x041e0f07, next->bios.timing_20_31_0800 << 26 |
					    next->bios.timing_20_31_0780 << 17 |
					    next->bios.timing_20_31_0078 << 8 |
					    next->bios.timing_20_31_0007);
	ram_mask(fuc, 0x10fec8, 0x00000027, next->bios.timing_20_31_8000 << 5 |
					    next->bios.timing_20_31_7000);

	ram_wr32(fuc, 0x10f090, 0x4000007e);
	ram_nsec(fuc, 2000);
	ram_wr32(fuc, 0x10f314, 0x00000001); /* PRECHARGE */
	ram_wr32(fuc, 0x10f310, 0x00000001); /* REFRESH */
	ram_wr32(fuc, 0x10f210, 0x80000000); /* REFRESH_AUTO = 1 */

	अगर (next->bios.ramcfg_11_08_10 && (ram->mode == 2) /*XXX*/) अणु
		u32 temp = ram_mask(fuc, 0x10f294, 0xff000000, 0x24000000);
		gk104_ram_train(fuc, 0xbc0e0000, 0xa4010000); /*XXX*/
		ram_nsec(fuc, 1000);
		ram_wr32(fuc, 0x10f294, temp);
	पूर्ण

	ram_mask(fuc, mr[3], 0xfff, ram->base.mr[3]);
	ram_wr32(fuc, mr[0], ram->base.mr[0]);
	ram_mask(fuc, mr[8], 0xfff, ram->base.mr[8]);
	ram_nsec(fuc, 1000);
	ram_mask(fuc, mr[1], 0xfff, ram->base.mr[1]);
	ram_mask(fuc, mr[5], 0xfff, ram->base.mr[5] & ~0x004); /* LP3 later */
	ram_mask(fuc, mr[6], 0xfff, ram->base.mr[6]);
	ram_mask(fuc, mr[7], 0xfff, ram->base.mr[7]);

	अगर (vc == 0 && ram_have(fuc, gpio2E)) अणु
		u32 temp  = ram_mask(fuc, gpio2E, 0x3000, fuc->r_func2E[0]);
		अगर (temp != ram_rd32(fuc, gpio2E)) अणु
			ram_wr32(fuc, gpiotrig, 1);
			ram_nsec(fuc, 20000);
		पूर्ण
	पूर्ण

	ram_mask(fuc, 0x10f200, 0x80000000, 0x80000000);
	ram_wr32(fuc, 0x10f318, 0x00000001); /* NOP? */
	ram_mask(fuc, 0x10f200, 0x80000000, 0x00000000);
	ram_nsec(fuc, 1000);
	ram_nuts(ram, 0x10f200, 0x18808800, 0x00000000, 0x18808800);

	data  = ram_rd32(fuc, 0x10f978);
	data &= ~0x00046144;
	data |=  0x0000000b;
	अगर (!next->bios.ramcfg_11_07_08) अणु
		अगर (!next->bios.ramcfg_11_07_04)
			data |= 0x0000200c;
		अन्यथा
			data |= 0x00000000;
	पूर्ण अन्यथा अणु
		data |= 0x00040044;
	पूर्ण
	ram_wr32(fuc, 0x10f978, data);

	अगर (ram->mode == 1) अणु
		data = ram_rd32(fuc, 0x10f830) | 0x00000001;
		ram_wr32(fuc, 0x10f830, data);
	पूर्ण

	अगर (!next->bios.ramcfg_11_07_08) अणु
		data = 0x88020000;
		अगर ( next->bios.ramcfg_11_07_04)
			data |= 0x10000000;
		अगर (!next->bios.rammap_11_08_10)
			data |= 0x00080000;
	पूर्ण अन्यथा अणु
		data = 0xa40e0000;
	पूर्ण
	gk104_ram_train(fuc, 0xbc0f0000, data);
	अगर (1) /* XXX: not always? */
		ram_nsec(fuc, 1000);

	अगर (ram->mode == 2) अणु /*XXX*/
		ram_mask(fuc, 0x10f800, 0x00000004, 0x00000004);
	पूर्ण

	/* LP3 */
	अगर (ram_mask(fuc, mr[5], 0x004, ram->base.mr[5]) != ram->base.mr[5])
		ram_nsec(fuc, 1000);

	अगर (ram->mode != 2) अणु
		ram_mask(fuc, 0x10f830, 0x01000000, 0x01000000);
		ram_mask(fuc, 0x10f830, 0x01000000, 0x00000000);
	पूर्ण

	अगर (next->bios.ramcfg_11_07_02)
		gk104_ram_train(fuc, 0x80020000, 0x01000000);

	ram_unblock(fuc);

	अगर (ram->base.fb->subdev.device->disp)
		ram_wr32(fuc, 0x62c000, 0x0f0f0f00);

	अगर (next->bios.rammap_11_08_01)
		data = 0x00000800;
	अन्यथा
		data = 0x00000000;
	ram_mask(fuc, 0x10f200, 0x00000800, data);
	ram_nuts(ram, 0x10f200, 0x18808800, data, 0x18808800);
	वापस 0;
पूर्ण

/*******************************************************************************
 * DDR3
 ******************************************************************************/

अटल व्योम
nvkm_sddr3_dll_reset(काष्ठा gk104_ramfuc *fuc)
अणु
	ram_nuke(fuc, mr[0]);
	ram_mask(fuc, mr[0], 0x100, 0x100);
	ram_mask(fuc, mr[0], 0x100, 0x000);
पूर्ण

अटल व्योम
nvkm_sddr3_dll_disable(काष्ठा gk104_ramfuc *fuc)
अणु
	u32 mr1_old = ram_rd32(fuc, mr[1]);

	अगर (!(mr1_old & 0x1)) अणु
		ram_mask(fuc, mr[1], 0x1, 0x1);
		ram_nsec(fuc, 1000);
	पूर्ण
पूर्ण

अटल पूर्णांक
gk104_ram_calc_sddr3(काष्ठा gk104_ram *ram, u32 freq)
अणु
	काष्ठा gk104_ramfuc *fuc = &ram->fuc;
	स्थिर u32 rcoef = ((  ram->P1 << 16) | (ram->N1 << 8) | ram->M1);
	स्थिर u32 runk0 = ram->fN1 << 16;
	स्थिर u32 runk1 = ram->fN1;
	काष्ठा nvkm_ram_data *next = ram->base.next;
	पूर्णांक vc = !next->bios.ramcfg_11_02_08;
	पूर्णांक mv = !next->bios.ramcfg_11_02_04;
	u32 mask, data;

	ram_mask(fuc, 0x10f808, 0x40000000, 0x40000000);
	ram_block(fuc);

	अगर (ram->base.fb->subdev.device->disp)
		ram_wr32(fuc, 0x62c000, 0x0f0f0000);

	अगर (vc == 1 && ram_have(fuc, gpio2E)) अणु
		u32 temp  = ram_mask(fuc, gpio2E, 0x3000, fuc->r_func2E[1]);
		अगर (temp != ram_rd32(fuc, gpio2E)) अणु
			ram_wr32(fuc, gpiotrig, 1);
			ram_nsec(fuc, 20000);
		पूर्ण
	पूर्ण

	ram_mask(fuc, 0x10f200, 0x00000800, 0x00000000);
	अगर (next->bios.ramcfg_11_03_f0)
		ram_mask(fuc, 0x10f808, 0x04000000, 0x04000000);

	ram_wr32(fuc, 0x10f314, 0x00000001); /* PRECHARGE */

	अगर (next->bios.ramcfg_DLLoff)
		nvkm_sddr3_dll_disable(fuc);

	ram_wr32(fuc, 0x10f210, 0x00000000); /* REFRESH_AUTO = 0 */
	ram_wr32(fuc, 0x10f310, 0x00000001); /* REFRESH */
	ram_mask(fuc, 0x10f200, 0x80000000, 0x80000000);
	ram_wr32(fuc, 0x10f310, 0x00000001); /* REFRESH */
	ram_mask(fuc, 0x10f200, 0x80000000, 0x00000000);
	ram_nsec(fuc, 1000);

	ram_wr32(fuc, 0x10f090, 0x00000060);
	ram_wr32(fuc, 0x10f090, 0xc000007e);

	/*XXX: there करोes appear to be some kind of condition here, simply
	 *     modअगरying these bits in the vbios from the शेष pl0
	 *     entries shows no change.  however, the data करोes appear to
	 *     be correct and may be required क्रम the transition back
	 */
	mask = 0x00010000;
	data = 0x00010000;

	अगर (1) अणु
		mask |= 0x800807e0;
		data |= 0x800807e0;
		चयन (next->bios.ramcfg_11_03_c0) अणु
		हाल 3: data &= ~0x00000040; अवरोध;
		हाल 2: data &= ~0x00000100; अवरोध;
		हाल 1: data &= ~0x80000000; अवरोध;
		हाल 0: data &= ~0x00000400; अवरोध;
		पूर्ण

		चयन (next->bios.ramcfg_11_03_30) अणु
		हाल 3: data &= ~0x00000020; अवरोध;
		हाल 2: data &= ~0x00000080; अवरोध;
		हाल 1: data &= ~0x00080000; अवरोध;
		हाल 0: data &= ~0x00000200; अवरोध;
		पूर्ण
	पूर्ण

	अगर (next->bios.ramcfg_11_02_80)
		mask |= 0x03000000;
	अगर (next->bios.ramcfg_11_02_40)
		mask |= 0x00002000;
	अगर (next->bios.ramcfg_11_07_10)
		mask |= 0x00004000;
	अगर (next->bios.ramcfg_11_07_08)
		mask |= 0x00000003;
	अन्यथा
		mask |= 0x14000000;
	ram_mask(fuc, 0x10f824, mask, data);

	ram_mask(fuc, 0x132040, 0x00010000, 0x00000000);

	ram_mask(fuc, 0x1373f4, 0x00000000, 0x00010010);
	data  = ram_rd32(fuc, 0x1373ec) & ~0x00030000;
	data |= next->bios.ramcfg_11_03_30 << 16;
	ram_wr32(fuc, 0x1373ec, data);
	ram_mask(fuc, 0x1373f4, 0x00000003, 0x00000000);
	ram_mask(fuc, 0x1373f4, 0x00000010, 0x00000000);

	/* (re)program refpll, अगर required */
	अगर ((ram_rd32(fuc, 0x132024) & 0xffffffff) != rcoef ||
	    (ram_rd32(fuc, 0x132034) & 0x0000ffff) != runk1) अणु
		ram_mask(fuc, 0x132000, 0x00000001, 0x00000000);
		ram_mask(fuc, 0x132020, 0x00000001, 0x00000000);
		ram_wr32(fuc, 0x137320, 0x00000000);
		ram_mask(fuc, 0x132030, 0xffff0000, runk0);
		ram_mask(fuc, 0x132034, 0x0000ffff, runk1);
		ram_wr32(fuc, 0x132024, rcoef);
		ram_mask(fuc, 0x132028, 0x00080000, 0x00080000);
		ram_mask(fuc, 0x132020, 0x00000001, 0x00000001);
		ram_रुको(fuc, 0x137390, 0x00020000, 0x00020000, 64000);
		ram_mask(fuc, 0x132028, 0x00080000, 0x00000000);
	पूर्ण

	ram_mask(fuc, 0x1373f4, 0x00000010, 0x00000010);
	ram_mask(fuc, 0x1373f4, 0x00000003, 0x00000001);
	ram_mask(fuc, 0x1373f4, 0x00010000, 0x00000000);

	अगर (ram_have(fuc, gpioMV)) अणु
		u32 temp  = ram_mask(fuc, gpioMV, 0x3000, fuc->r_funcMV[mv]);
		अगर (temp != ram_rd32(fuc, gpioMV)) अणु
			ram_wr32(fuc, gpiotrig, 1);
			ram_nsec(fuc, 64000);
		पूर्ण
	पूर्ण

	अगर (next->bios.ramcfg_11_02_40 ||
	    next->bios.ramcfg_11_07_10) अणु
		ram_mask(fuc, 0x132040, 0x00010000, 0x00010000);
		ram_nsec(fuc, 20000);
	पूर्ण

	अगर (ram->mode != 2) /*XXX*/ अणु
		अगर (next->bios.ramcfg_11_07_40)
			ram_mask(fuc, 0x10f670, 0x80000000, 0x80000000);
	पूर्ण

	ram_wr32(fuc, 0x10f65c, 0x00000011 * next->bios.rammap_11_11_0c);
	ram_wr32(fuc, 0x10f6b8, 0x01010101 * next->bios.ramcfg_11_09);
	ram_wr32(fuc, 0x10f6bc, 0x01010101 * next->bios.ramcfg_11_09);

	mask = 0x00010000;
	data = 0x00000000;
	अगर (!next->bios.ramcfg_11_02_80)
		data |= 0x03000000;
	अगर (!next->bios.ramcfg_11_02_40)
		data |= 0x00002000;
	अगर (!next->bios.ramcfg_11_07_10)
		data |= 0x00004000;
	अगर (!next->bios.ramcfg_11_07_08)
		data |= 0x00000003;
	अन्यथा
		data |= 0x14000000;
	ram_mask(fuc, 0x10f824, mask, data);
	ram_nsec(fuc, 1000);

	अगर (next->bios.ramcfg_11_08_01)
		data = 0x00100000;
	अन्यथा
		data = 0x00000000;
	ram_mask(fuc, 0x10f82c, 0x00100000, data);

	/* PFB timing */
	ram_mask(fuc, 0x10f248, 0xffffffff, next->bios.timing[10]);
	ram_mask(fuc, 0x10f290, 0xffffffff, next->bios.timing[0]);
	ram_mask(fuc, 0x10f294, 0xffffffff, next->bios.timing[1]);
	ram_mask(fuc, 0x10f298, 0xffffffff, next->bios.timing[2]);
	ram_mask(fuc, 0x10f29c, 0xffffffff, next->bios.timing[3]);
	ram_mask(fuc, 0x10f2a0, 0xffffffff, next->bios.timing[4]);
	ram_mask(fuc, 0x10f2a4, 0xffffffff, next->bios.timing[5]);
	ram_mask(fuc, 0x10f2a8, 0xffffffff, next->bios.timing[6]);
	ram_mask(fuc, 0x10f2ac, 0xffffffff, next->bios.timing[7]);
	ram_mask(fuc, 0x10f2cc, 0xffffffff, next->bios.timing[8]);
	ram_mask(fuc, 0x10f2e8, 0xffffffff, next->bios.timing[9]);

	mask = 0x33f00000;
	data = 0x00000000;
	अगर (!next->bios.ramcfg_11_01_04)
		data |= 0x20200000;
	अगर (!next->bios.ramcfg_11_07_80)
		data |= 0x12800000;
	/*XXX: see note above about there probably being some condition
	 *     क्रम the 10f824 stuff that uses ramcfg 3...
	 */
	अगर (next->bios.ramcfg_11_03_f0) अणु
		अगर (next->bios.rammap_11_08_0c) अणु
			अगर (!next->bios.ramcfg_11_07_80)
				mask |= 0x00000020;
			अन्यथा
				data |= 0x00000020;
			mask |= 0x08000004;
		पूर्ण
		data |= 0x04000000;
	पूर्ण अन्यथा अणु
		mask |= 0x44000020;
		data |= 0x08000004;
	पूर्ण

	ram_mask(fuc, 0x10f808, mask, data);

	ram_wr32(fuc, 0x10f870, 0x11111111 * next->bios.ramcfg_11_03_0f);

	ram_mask(fuc, 0x10f250, 0x000003f0, next->bios.timing_20_2c_003f << 4);

	data = (next->bios.timing[10] & 0x7f000000) >> 24;
	अगर (data < next->bios.timing_20_2c_1fc0)
		data = next->bios.timing_20_2c_1fc0;
	ram_mask(fuc, 0x10f24c, 0x7f000000, data << 24);

	ram_mask(fuc, 0x10f224, 0x001f0000, next->bios.timing_20_30_f8 << 16);

	ram_wr32(fuc, 0x10f090, 0x4000007f);
	ram_nsec(fuc, 1000);

	ram_wr32(fuc, 0x10f314, 0x00000001); /* PRECHARGE */
	ram_wr32(fuc, 0x10f310, 0x00000001); /* REFRESH */
	ram_wr32(fuc, 0x10f210, 0x80000000); /* REFRESH_AUTO = 1 */
	ram_nsec(fuc, 1000);

	अगर (!next->bios.ramcfg_DLLoff) अणु
		ram_mask(fuc, mr[1], 0x1, 0x0);
		nvkm_sddr3_dll_reset(fuc);
	पूर्ण

	ram_mask(fuc, mr[2], 0x00000fff, ram->base.mr[2]);
	ram_mask(fuc, mr[1], 0xffffffff, ram->base.mr[1]);
	ram_wr32(fuc, mr[0], ram->base.mr[0]);
	ram_nsec(fuc, 1000);

	अगर (!next->bios.ramcfg_DLLoff) अणु
		nvkm_sddr3_dll_reset(fuc);
		ram_nsec(fuc, 1000);
	पूर्ण

	अगर (vc == 0 && ram_have(fuc, gpio2E)) अणु
		u32 temp  = ram_mask(fuc, gpio2E, 0x3000, fuc->r_func2E[0]);
		अगर (temp != ram_rd32(fuc, gpio2E)) अणु
			ram_wr32(fuc, gpiotrig, 1);
			ram_nsec(fuc, 20000);
		पूर्ण
	पूर्ण

	अगर (ram->mode != 2) अणु
		ram_mask(fuc, 0x10f830, 0x01000000, 0x01000000);
		ram_mask(fuc, 0x10f830, 0x01000000, 0x00000000);
	पूर्ण

	ram_mask(fuc, 0x10f200, 0x80000000, 0x80000000);
	ram_wr32(fuc, 0x10f318, 0x00000001); /* NOP? */
	ram_mask(fuc, 0x10f200, 0x80000000, 0x00000000);
	ram_nsec(fuc, 1000);

	ram_unblock(fuc);

	अगर (ram->base.fb->subdev.device->disp)
		ram_wr32(fuc, 0x62c000, 0x0f0f0f00);

	अगर (next->bios.rammap_11_08_01)
		data = 0x00000800;
	अन्यथा
		data = 0x00000000;
	ram_mask(fuc, 0x10f200, 0x00000800, data);
	वापस 0;
पूर्ण

/*******************************************************************************
 * मुख्य hooks
 ******************************************************************************/

अटल पूर्णांक
gk104_ram_calc_data(काष्ठा gk104_ram *ram, u32 khz, काष्ठा nvkm_ram_data *data)
अणु
	काष्ठा nvkm_subdev *subdev = &ram->base.fb->subdev;
	काष्ठा nvkm_ram_data *cfg;
	u32 mhz = khz / 1000;

	list_क्रम_each_entry(cfg, &ram->cfg, head) अणु
		अगर (mhz >= cfg->bios.rammap_min &&
		    mhz <= cfg->bios.rammap_max) अणु
			*data = *cfg;
			data->freq = khz;
			वापस 0;
		पूर्ण
	पूर्ण

	nvkm_error(subdev, "ramcfg data for %dMHz not found\n", mhz);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
gk104_calc_pll_output(पूर्णांक fN, पूर्णांक M, पूर्णांक N, पूर्णांक P, पूर्णांक clk)
अणु
	वापस ((clk * N) + (((u16)(fN + 4096) * clk) >> 13)) / (M * P);
पूर्ण

अटल पूर्णांक
gk104_pll_calc_hiclk(पूर्णांक target_khz, पूर्णांक crystal,
		पूर्णांक *N1, पूर्णांक *fN1, पूर्णांक *M1, पूर्णांक *P1,
		पूर्णांक *N2, पूर्णांक *M2, पूर्णांक *P2)
अणु
	पूर्णांक best_err = target_khz, p_ref, n_ref;
	bool upper = false;

	*M1 = 1;
	/* M has to be 1, otherwise it माला_लो unstable */
	*M2 = 1;
	/* can be 1 or 2, sticking with 1 क्रम simplicity */
	*P2 = 1;

	क्रम (p_ref = 0x7; p_ref >= 0x5; --p_ref) अणु
		क्रम (n_ref = 0x25; n_ref <= 0x2b; ++n_ref) अणु
			पूर्णांक cur_N, cur_clk, cur_err;

			cur_clk = gk104_calc_pll_output(0, 1, n_ref, p_ref, crystal);
			cur_N = target_khz / cur_clk;
			cur_err = target_khz
				- gk104_calc_pll_output(0xf000, 1, cur_N, 1, cur_clk);

			/* we found a better combination */
			अगर (cur_err < best_err) अणु
				best_err = cur_err;
				*N2 = cur_N;
				*N1 = n_ref;
				*P1 = p_ref;
				upper = false;
			पूर्ण

			cur_N += 1;
			cur_err = gk104_calc_pll_output(0xf000, 1, cur_N, 1, cur_clk)
				- target_khz;
			अगर (cur_err < best_err) अणु
				best_err = cur_err;
				*N2 = cur_N;
				*N1 = n_ref;
				*P1 = p_ref;
				upper = true;
			पूर्ण
		पूर्ण
	पूर्ण

	/* adjust fN to get बंदr to the target घड़ी */
	*fN1 = (u16)((((best_err / *N2 * *P2) * (*P1 * *M1)) << 13) / crystal);
	अगर (upper)
		*fN1 = (u16)(1 - *fN1);

	वापस gk104_calc_pll_output(*fN1, 1, *N1, *P1, crystal);
पूर्ण

अटल पूर्णांक
gk104_ram_calc_xits(काष्ठा gk104_ram *ram, काष्ठा nvkm_ram_data *next)
अणु
	काष्ठा gk104_ramfuc *fuc = &ram->fuc;
	काष्ठा nvkm_subdev *subdev = &ram->base.fb->subdev;
	पूर्णांक refclk, i;
	पूर्णांक ret;

	ret = ram_init(fuc, ram->base.fb);
	अगर (ret)
		वापस ret;

	ram->mode = (next->freq > fuc->refpll.vco1.max_freq) ? 2 : 1;
	ram->from = ram_rd32(fuc, 0x1373f4) & 0x0000000f;

	/* XXX: this is *not* what nvidia करो.  on fermi nvidia generally
	 * select, based on some unknown condition, one of the two possible
	 * reference frequencies listed in the vbios table क्रम mempll and
	 * program refpll to that frequency.
	 *
	 * so far, i've seen very weird values being chosen by nvidia on
	 * kepler boards, no idea how/why they're chosen.
	 */
	refclk = next->freq;
	अगर (ram->mode == 2) अणु
		ret = gk104_pll_calc_hiclk(next->freq, subdev->device->crystal,
				&ram->N1, &ram->fN1, &ram->M1, &ram->P1,
				&ram->N2, &ram->M2, &ram->P2);
		fuc->mempll.refclk = ret;
		अगर (ret <= 0) अणु
			nvkm_error(subdev, "unable to calc plls\n");
			वापस -EINVAL;
		पूर्ण
		nvkm_debug(subdev, "successfully calced PLLs for clock %i kHz"
				" (refclock: %i kHz)\n", next->freq, ret);
	पूर्ण अन्यथा अणु
		/* calculate refpll coefficients */
		ret = gt215_pll_calc(subdev, &fuc->refpll, refclk, &ram->N1,
				     &ram->fN1, &ram->M1, &ram->P1);
		fuc->mempll.refclk = ret;
		अगर (ret <= 0) अणु
			nvkm_error(subdev, "unable to calc refpll\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(fuc->r_mr); i++) अणु
		अगर (ram_have(fuc, mr[i]))
			ram->base.mr[i] = ram_rd32(fuc, mr[i]);
	पूर्ण
	ram->base.freq = next->freq;

	चयन (ram->base.type) अणु
	हाल NVKM_RAM_TYPE_DDR3:
		ret = nvkm_sddr3_calc(&ram->base);
		अगर (ret == 0)
			ret = gk104_ram_calc_sddr3(ram, next->freq);
		अवरोध;
	हाल NVKM_RAM_TYPE_GDDR5:
		ret = nvkm_gddr5_calc(&ram->base, ram->pnuts != 0);
		अगर (ret == 0)
			ret = gk104_ram_calc_gddr5(ram, next->freq);
		अवरोध;
	शेष:
		ret = -ENOSYS;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक
gk104_ram_calc(काष्ठा nvkm_ram *base, u32 freq)
अणु
	काष्ठा gk104_ram *ram = gk104_ram(base);
	काष्ठा nvkm_clk *clk = ram->base.fb->subdev.device->clk;
	काष्ठा nvkm_ram_data *xits = &ram->base.xition;
	काष्ठा nvkm_ram_data *copy;
	पूर्णांक ret;

	अगर (ram->base.next == शून्य) अणु
		ret = gk104_ram_calc_data(ram,
					  nvkm_clk_पढ़ो(clk, nv_clk_src_mem),
					  &ram->base.क्रमmer);
		अगर (ret)
			वापस ret;

		ret = gk104_ram_calc_data(ram, freq, &ram->base.target);
		अगर (ret)
			वापस ret;

		अगर (ram->base.target.freq < ram->base.क्रमmer.freq) अणु
			*xits = ram->base.target;
			copy = &ram->base.क्रमmer;
		पूर्ण अन्यथा अणु
			*xits = ram->base.क्रमmer;
			copy = &ram->base.target;
		पूर्ण

		xits->bios.ramcfg_11_02_04 = copy->bios.ramcfg_11_02_04;
		xits->bios.ramcfg_11_02_03 = copy->bios.ramcfg_11_02_03;
		xits->bios.timing_20_30_07 = copy->bios.timing_20_30_07;

		ram->base.next = &ram->base.target;
		अगर (स_भेद(xits, &ram->base.क्रमmer, माप(xits->bios)))
			ram->base.next = &ram->base.xition;
	पूर्ण अन्यथा अणु
		BUG_ON(ram->base.next != &ram->base.xition);
		ram->base.next = &ram->base.target;
	पूर्ण

	वापस gk104_ram_calc_xits(ram, ram->base.next);
पूर्ण

अटल व्योम
gk104_ram_prog_0(काष्ठा gk104_ram *ram, u32 freq)
अणु
	काष्ठा nvkm_device *device = ram->base.fb->subdev.device;
	काष्ठा nvkm_ram_data *cfg;
	u32 mhz = freq / 1000;
	u32 mask, data;

	list_क्रम_each_entry(cfg, &ram->cfg, head) अणु
		अगर (mhz >= cfg->bios.rammap_min &&
		    mhz <= cfg->bios.rammap_max)
			अवरोध;
	पूर्ण

	अगर (&cfg->head == &ram->cfg)
		वापस;

	अगर (mask = 0, data = 0, ram->dअगरf.rammap_11_0a_03fe) अणु
		data |= cfg->bios.rammap_11_0a_03fe << 12;
		mask |= 0x001ff000;
	पूर्ण
	अगर (ram->dअगरf.rammap_11_09_01ff) अणु
		data |= cfg->bios.rammap_11_09_01ff;
		mask |= 0x000001ff;
	पूर्ण
	nvkm_mask(device, 0x10f468, mask, data);

	अगर (mask = 0, data = 0, ram->dअगरf.rammap_11_0a_0400) अणु
		data |= cfg->bios.rammap_11_0a_0400;
		mask |= 0x00000001;
	पूर्ण
	nvkm_mask(device, 0x10f420, mask, data);

	अगर (mask = 0, data = 0, ram->dअगरf.rammap_11_0a_0800) अणु
		data |= cfg->bios.rammap_11_0a_0800;
		mask |= 0x00000001;
	पूर्ण
	nvkm_mask(device, 0x10f430, mask, data);

	अगर (mask = 0, data = 0, ram->dअगरf.rammap_11_0b_01f0) अणु
		data |= cfg->bios.rammap_11_0b_01f0;
		mask |= 0x0000001f;
	पूर्ण
	nvkm_mask(device, 0x10f400, mask, data);

	अगर (mask = 0, data = 0, ram->dअगरf.rammap_11_0b_0200) अणु
		data |= cfg->bios.rammap_11_0b_0200 << 9;
		mask |= 0x00000200;
	पूर्ण
	nvkm_mask(device, 0x10f410, mask, data);

	अगर (mask = 0, data = 0, ram->dअगरf.rammap_11_0d) अणु
		data |= cfg->bios.rammap_11_0d << 16;
		mask |= 0x00ff0000;
	पूर्ण
	अगर (ram->dअगरf.rammap_11_0f) अणु
		data |= cfg->bios.rammap_11_0f << 8;
		mask |= 0x0000ff00;
	पूर्ण
	nvkm_mask(device, 0x10f440, mask, data);

	अगर (mask = 0, data = 0, ram->dअगरf.rammap_11_0e) अणु
		data |= cfg->bios.rammap_11_0e << 8;
		mask |= 0x0000ff00;
	पूर्ण
	अगर (ram->dअगरf.rammap_11_0b_0800) अणु
		data |= cfg->bios.rammap_11_0b_0800 << 7;
		mask |= 0x00000080;
	पूर्ण
	अगर (ram->dअगरf.rammap_11_0b_0400) अणु
		data |= cfg->bios.rammap_11_0b_0400 << 5;
		mask |= 0x00000020;
	पूर्ण
	nvkm_mask(device, 0x10f444, mask, data);
पूर्ण

पूर्णांक
gk104_ram_prog(काष्ठा nvkm_ram *base)
अणु
	काष्ठा gk104_ram *ram = gk104_ram(base);
	काष्ठा gk104_ramfuc *fuc = &ram->fuc;
	काष्ठा nvkm_device *device = ram->base.fb->subdev.device;
	काष्ठा nvkm_ram_data *next = ram->base.next;

	अगर (!nvkm_boolopt(device->cfgopt, "NvMemExec", true)) अणु
		ram_exec(fuc, false);
		वापस (ram->base.next == &ram->base.xition);
	पूर्ण

	gk104_ram_prog_0(ram, 1000);
	ram_exec(fuc, true);
	gk104_ram_prog_0(ram, next->freq);

	वापस (ram->base.next == &ram->base.xition);
पूर्ण

व्योम
gk104_ram_tidy(काष्ठा nvkm_ram *base)
अणु
	काष्ठा gk104_ram *ram = gk104_ram(base);
	ram->base.next = शून्य;
	ram_exec(&ram->fuc, false);
पूर्ण

काष्ठा gk104_ram_train अणु
	u16 mask;
	काष्ठा nvbios_M0209S remap;
	काष्ठा nvbios_M0209S type00;
	काष्ठा nvbios_M0209S type01;
	काष्ठा nvbios_M0209S type04;
	काष्ठा nvbios_M0209S type06;
	काष्ठा nvbios_M0209S type07;
	काष्ठा nvbios_M0209S type08;
	काष्ठा nvbios_M0209S type09;
पूर्ण;

अटल पूर्णांक
gk104_ram_train_type(काष्ठा nvkm_ram *ram, पूर्णांक i, u8 ramcfg,
		     काष्ठा gk104_ram_train *train)
अणु
	काष्ठा nvkm_bios *bios = ram->fb->subdev.device->bios;
	काष्ठा nvbios_M0205E M0205E;
	काष्ठा nvbios_M0205S M0205S;
	काष्ठा nvbios_M0209E M0209E;
	काष्ठा nvbios_M0209S *remap = &train->remap;
	काष्ठा nvbios_M0209S *value;
	u8  ver, hdr, cnt, len;
	u32 data;

	/* determine type of data क्रम this index */
	अगर (!(data = nvbios_M0205Ep(bios, i, &ver, &hdr, &cnt, &len, &M0205E)))
		वापस -ENOENT;

	चयन (M0205E.type) अणु
	हाल 0x00: value = &train->type00; अवरोध;
	हाल 0x01: value = &train->type01; अवरोध;
	हाल 0x04: value = &train->type04; अवरोध;
	हाल 0x06: value = &train->type06; अवरोध;
	हाल 0x07: value = &train->type07; अवरोध;
	हाल 0x08: value = &train->type08; अवरोध;
	हाल 0x09: value = &train->type09; अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	/* training data index determined by ramcfg strap */
	अगर (!(data = nvbios_M0205Sp(bios, i, ramcfg, &ver, &hdr, &M0205S)))
		वापस -EINVAL;
	i = M0205S.data;

	/* training data क्रमmat inक्रमmation */
	अगर (!(data = nvbios_M0209Ep(bios, i, &ver, &hdr, &cnt, &len, &M0209E)))
		वापस -EINVAL;

	/* ... and the raw data */
	अगर (!(data = nvbios_M0209Sp(bios, i, 0, &ver, &hdr, value)))
		वापस -EINVAL;

	अगर (M0209E.v02_07 == 2) अणु
		/* of course! why wouldn't we have a poपूर्णांकer to another entry
		 * in the same table, and use the first one as an array of
		 * remap indices...
		 */
		अगर (!(data = nvbios_M0209Sp(bios, M0209E.v03, 0, &ver, &hdr,
					    remap)))
			वापस -EINVAL;

		क्रम (i = 0; i < ARRAY_SIZE(value->data); i++)
			value->data[i] = remap->data[value->data[i]];
	पूर्ण अन्यथा
	अगर (M0209E.v02_07 != 1)
		वापस -EINVAL;

	train->mask |= 1 << M0205E.type;
	वापस 0;
पूर्ण

अटल पूर्णांक
gk104_ram_train_init_0(काष्ठा nvkm_ram *ram, काष्ठा gk104_ram_train *train)
अणु
	काष्ठा nvkm_subdev *subdev = &ram->fb->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	पूर्णांक i, j;

	अगर ((train->mask & 0x03d3) != 0x03d3) अणु
		nvkm_warn(subdev, "missing link training data\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < 0x30; i++) अणु
		क्रम (j = 0; j < 8; j += 4) अणु
			nvkm_wr32(device, 0x10f968 + j, 0x00000000 | (i << 8));
			nvkm_wr32(device, 0x10f920 + j, 0x00000000 |
						   train->type08.data[i] << 4 |
						   train->type06.data[i]);
			nvkm_wr32(device, 0x10f918 + j, train->type00.data[i]);
			nvkm_wr32(device, 0x10f920 + j, 0x00000100 |
						   train->type09.data[i] << 4 |
						   train->type07.data[i]);
			nvkm_wr32(device, 0x10f918 + j, train->type01.data[i]);
		पूर्ण
	पूर्ण

	क्रम (j = 0; j < 8; j += 4) अणु
		क्रम (i = 0; i < 0x100; i++) अणु
			nvkm_wr32(device, 0x10f968 + j, i);
			nvkm_wr32(device, 0x10f900 + j, train->type04.data[i]);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
gk104_ram_train_init(काष्ठा nvkm_ram *ram)
अणु
	u8 ramcfg = nvbios_ramcfg_index(&ram->fb->subdev);
	काष्ठा gk104_ram_train *train;
	पूर्णांक ret, i;

	अगर (!(train = kzalloc(माप(*train), GFP_KERNEL)))
		वापस -ENOMEM;

	क्रम (i = 0; i < 0x100; i++) अणु
		ret = gk104_ram_train_type(ram, i, ramcfg, train);
		अगर (ret && ret != -ENOENT)
			अवरोध;
	पूर्ण

	चयन (ram->type) अणु
	हाल NVKM_RAM_TYPE_GDDR5:
		ret = gk104_ram_train_init_0(ram, train);
		अवरोध;
	शेष:
		ret = 0;
		अवरोध;
	पूर्ण

	kमुक्त(train);
	वापस ret;
पूर्ण

पूर्णांक
gk104_ram_init(काष्ठा nvkm_ram *ram)
अणु
	काष्ठा nvkm_subdev *subdev = &ram->fb->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_bios *bios = device->bios;
	u8  ver, hdr, cnt, len, snr, ssz;
	u32 data, save;
	पूर्णांक i;

	/* run a bunch of tables from rammap table.  there's actually
	 * inभागidual poपूर्णांकers क्रम each rammap entry too, but, nvidia
	 * seem to just run the last two entries' scripts early on in
	 * their init, and never again.. we'll just run 'em all once
	 * क्रम now.
	 *
	 * i strongly suspect that each script is क्रम a separate mode
	 * (likely selected by 0x10f65c's lower bits?), and the
	 * binary driver skips the one that's alपढ़ोy been setup by
	 * the init tables.
	 */
	data = nvbios_rammapTe(bios, &ver, &hdr, &cnt, &len, &snr, &ssz);
	अगर (!data || hdr < 0x15)
		वापस -EINVAL;

	cnt  = nvbios_rd08(bios, data + 0x14); /* guess at count */
	data = nvbios_rd32(bios, data + 0x10); /* guess u32... */
	save = nvkm_rd32(device, 0x10f65c) & 0x000000f0;
	क्रम (i = 0; i < cnt; i++, data += 4) अणु
		अगर (i != save >> 4) अणु
			nvkm_mask(device, 0x10f65c, 0x000000f0, i << 4);
			nvbios_init(subdev, nvbios_rd32(bios, data));
		पूर्ण
	पूर्ण
	nvkm_mask(device, 0x10f65c, 0x000000f0, save);
	nvkm_mask(device, 0x10f584, 0x11000000, 0x00000000);
	nvkm_wr32(device, 0x10ecc0, 0xffffffff);
	nvkm_mask(device, 0x10f160, 0x00000010, 0x00000010);

	वापस gk104_ram_train_init(ram);
पूर्ण

अटल पूर्णांक
gk104_ram_ctor_data(काष्ठा gk104_ram *ram, u8 ramcfg, पूर्णांक i)
अणु
	काष्ठा nvkm_bios *bios = ram->base.fb->subdev.device->bios;
	काष्ठा nvkm_ram_data *cfg;
	काष्ठा nvbios_ramcfg *d = &ram->dअगरf;
	काष्ठा nvbios_ramcfg *p, *n;
	u8  ver, hdr, cnt, len;
	u32 data;
	पूर्णांक ret;

	अगर (!(cfg = kदो_स्मृति(माप(*cfg), GFP_KERNEL)))
		वापस -ENOMEM;
	p = &list_last_entry(&ram->cfg, typeof(*cfg), head)->bios;
	n = &cfg->bios;

	/* memory config data क्रम a range of target frequencies */
	data = nvbios_rammapEp(bios, i, &ver, &hdr, &cnt, &len, &cfg->bios);
	अगर (ret = -ENOENT, !data)
		जाओ करोne;
	अगर (ret = -ENOSYS, ver != 0x11 || hdr < 0x12)
		जाओ करोne;

	/* ... and a portion specअगरic to the attached memory */
	data = nvbios_rammapSp(bios, data, ver, hdr, cnt, len, ramcfg,
			       &ver, &hdr, &cfg->bios);
	अगर (ret = -EINVAL, !data)
		जाओ करोne;
	अगर (ret = -ENOSYS, ver != 0x11 || hdr < 0x0a)
		जाओ करोne;

	/* lookup memory timings, अगर bios says they're present */
	अगर (cfg->bios.ramcfg_timing != 0xff) अणु
		data = nvbios_timingEp(bios, cfg->bios.ramcfg_timing,
				       &ver, &hdr, &cnt, &len,
				       &cfg->bios);
		अगर (ret = -EINVAL, !data)
			जाओ करोne;
		अगर (ret = -ENOSYS, ver != 0x20 || hdr < 0x33)
			जाओ करोne;
	पूर्ण

	list_add_tail(&cfg->head, &ram->cfg);
	अगर (ret = 0, i == 0)
		जाओ करोne;

	d->rammap_11_0a_03fe |= p->rammap_11_0a_03fe != n->rammap_11_0a_03fe;
	d->rammap_11_09_01ff |= p->rammap_11_09_01ff != n->rammap_11_09_01ff;
	d->rammap_11_0a_0400 |= p->rammap_11_0a_0400 != n->rammap_11_0a_0400;
	d->rammap_11_0a_0800 |= p->rammap_11_0a_0800 != n->rammap_11_0a_0800;
	d->rammap_11_0b_01f0 |= p->rammap_11_0b_01f0 != n->rammap_11_0b_01f0;
	d->rammap_11_0b_0200 |= p->rammap_11_0b_0200 != n->rammap_11_0b_0200;
	d->rammap_11_0d |= p->rammap_11_0d != n->rammap_11_0d;
	d->rammap_11_0f |= p->rammap_11_0f != n->rammap_11_0f;
	d->rammap_11_0e |= p->rammap_11_0e != n->rammap_11_0e;
	d->rammap_11_0b_0800 |= p->rammap_11_0b_0800 != n->rammap_11_0b_0800;
	d->rammap_11_0b_0400 |= p->rammap_11_0b_0400 != n->rammap_11_0b_0400;
	d->ramcfg_11_01_01 |= p->ramcfg_11_01_01 != n->ramcfg_11_01_01;
	d->ramcfg_11_01_02 |= p->ramcfg_11_01_02 != n->ramcfg_11_01_02;
	d->ramcfg_11_01_10 |= p->ramcfg_11_01_10 != n->ramcfg_11_01_10;
	d->ramcfg_11_02_03 |= p->ramcfg_11_02_03 != n->ramcfg_11_02_03;
	d->ramcfg_11_08_20 |= p->ramcfg_11_08_20 != n->ramcfg_11_08_20;
	d->timing_20_30_07 |= p->timing_20_30_07 != n->timing_20_30_07;
करोne:
	अगर (ret)
		kमुक्त(cfg);
	वापस ret;
पूर्ण

व्योम *
gk104_ram_dtor(काष्ठा nvkm_ram *base)
अणु
	काष्ठा gk104_ram *ram = gk104_ram(base);
	काष्ठा nvkm_ram_data *cfg, *पंचांगp;

	list_क्रम_each_entry_safe(cfg, पंचांगp, &ram->cfg, head) अणु
		kमुक्त(cfg);
	पूर्ण

	वापस ram;
पूर्ण

पूर्णांक
gk104_ram_new_(स्थिर काष्ठा nvkm_ram_func *func, काष्ठा nvkm_fb *fb,
	       काष्ठा nvkm_ram **pram)
अणु
	काष्ठा nvkm_subdev *subdev = &fb->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_bios *bios = device->bios;
	काष्ठा dcb_gpio_func gpio;
	काष्ठा gk104_ram *ram;
	पूर्णांक ret, i;
	u8  ramcfg = nvbios_ramcfg_index(subdev);
	u32 पंचांगp;

	अगर (!(ram = kzalloc(माप(*ram), GFP_KERNEL)))
		वापस -ENOMEM;
	*pram = &ram->base;

	ret = gf100_ram_ctor(func, fb, &ram->base);
	अगर (ret)
		वापस ret;

	INIT_LIST_HEAD(&ram->cfg);

	/* calculate a mask of dअगरferently configured memory partitions,
	 * because, of course reघड़ीing wasn't complicated enough
	 * alपढ़ोy without having to treat some of them dअगरferently to
	 * the others....
	 */
	ram->parts = nvkm_rd32(device, 0x022438);
	ram->pmask = nvkm_rd32(device, 0x022554);
	ram->pnuts = 0;
	क्रम (i = 0, पंचांगp = 0; i < ram->parts; i++) अणु
		अगर (!(ram->pmask & (1 << i))) अणु
			u32 cfg1 = nvkm_rd32(device, 0x110204 + (i * 0x1000));
			अगर (पंचांगp && पंचांगp != cfg1) अणु
				ram->pnuts |= (1 << i);
				जारी;
			पूर्ण
			पंचांगp = cfg1;
		पूर्ण
	पूर्ण

	/* parse bios data क्रम all rammap table entries up-front, and
	 * build inक्रमmation on whether certain fields dअगरfer between
	 * any of the entries.
	 *
	 * the binary driver appears to completely ignore some fields
	 * when all entries contain the same value.  at first, it was
	 * hoped that these were mere optimisations and the bios init
	 * tables had configured as per the values here, but there is
	 * evidence now to suggest that this isn't the हाल and we करो
	 * need to treat this condition as a "don't touch" indicator.
	 */
	क्रम (i = 0; !ret; i++) अणु
		ret = gk104_ram_ctor_data(ram, ramcfg, i);
		अगर (ret && ret != -ENOENT) अणु
			nvkm_error(subdev, "failed to parse ramcfg data\n");
			वापस ret;
		पूर्ण
	पूर्ण

	/* parse bios data क्रम both pll's */
	ret = nvbios_pll_parse(bios, 0x0c, &ram->fuc.refpll);
	अगर (ret) अणु
		nvkm_error(subdev, "mclk refpll data not found\n");
		वापस ret;
	पूर्ण

	ret = nvbios_pll_parse(bios, 0x04, &ram->fuc.mempll);
	अगर (ret) अणु
		nvkm_error(subdev, "mclk pll data not found\n");
		वापस ret;
	पूर्ण

	/* lookup memory voltage gpios */
	ret = nvkm_gpio_find(device->gpio, 0, 0x18, DCB_GPIO_UNUSED, &gpio);
	अगर (ret == 0) अणु
		ram->fuc.r_gpioMV = ramfuc_reg(0x00d610 + (gpio.line * 0x04));
		ram->fuc.r_funcMV[0] = (gpio.log[0] ^ 2) << 12;
		ram->fuc.r_funcMV[1] = (gpio.log[1] ^ 2) << 12;
	पूर्ण

	ret = nvkm_gpio_find(device->gpio, 0, 0x2e, DCB_GPIO_UNUSED, &gpio);
	अगर (ret == 0) अणु
		ram->fuc.r_gpio2E = ramfuc_reg(0x00d610 + (gpio.line * 0x04));
		ram->fuc.r_func2E[0] = (gpio.log[0] ^ 2) << 12;
		ram->fuc.r_func2E[1] = (gpio.log[1] ^ 2) << 12;
	पूर्ण

	ram->fuc.r_gpiotrig = ramfuc_reg(0x00d604);

	ram->fuc.r_0x132020 = ramfuc_reg(0x132020);
	ram->fuc.r_0x132028 = ramfuc_reg(0x132028);
	ram->fuc.r_0x132024 = ramfuc_reg(0x132024);
	ram->fuc.r_0x132030 = ramfuc_reg(0x132030);
	ram->fuc.r_0x132034 = ramfuc_reg(0x132034);
	ram->fuc.r_0x132000 = ramfuc_reg(0x132000);
	ram->fuc.r_0x132004 = ramfuc_reg(0x132004);
	ram->fuc.r_0x132040 = ramfuc_reg(0x132040);

	ram->fuc.r_0x10f248 = ramfuc_reg(0x10f248);
	ram->fuc.r_0x10f290 = ramfuc_reg(0x10f290);
	ram->fuc.r_0x10f294 = ramfuc_reg(0x10f294);
	ram->fuc.r_0x10f298 = ramfuc_reg(0x10f298);
	ram->fuc.r_0x10f29c = ramfuc_reg(0x10f29c);
	ram->fuc.r_0x10f2a0 = ramfuc_reg(0x10f2a0);
	ram->fuc.r_0x10f2a4 = ramfuc_reg(0x10f2a4);
	ram->fuc.r_0x10f2a8 = ramfuc_reg(0x10f2a8);
	ram->fuc.r_0x10f2ac = ramfuc_reg(0x10f2ac);
	ram->fuc.r_0x10f2cc = ramfuc_reg(0x10f2cc);
	ram->fuc.r_0x10f2e8 = ramfuc_reg(0x10f2e8);
	ram->fuc.r_0x10f250 = ramfuc_reg(0x10f250);
	ram->fuc.r_0x10f24c = ramfuc_reg(0x10f24c);
	ram->fuc.r_0x10fec4 = ramfuc_reg(0x10fec4);
	ram->fuc.r_0x10fec8 = ramfuc_reg(0x10fec8);
	ram->fuc.r_0x10f604 = ramfuc_reg(0x10f604);
	ram->fuc.r_0x10f614 = ramfuc_reg(0x10f614);
	ram->fuc.r_0x10f610 = ramfuc_reg(0x10f610);
	ram->fuc.r_0x100770 = ramfuc_reg(0x100770);
	ram->fuc.r_0x100778 = ramfuc_reg(0x100778);
	ram->fuc.r_0x10f224 = ramfuc_reg(0x10f224);

	ram->fuc.r_0x10f870 = ramfuc_reg(0x10f870);
	ram->fuc.r_0x10f698 = ramfuc_reg(0x10f698);
	ram->fuc.r_0x10f694 = ramfuc_reg(0x10f694);
	ram->fuc.r_0x10f6b8 = ramfuc_reg(0x10f6b8);
	ram->fuc.r_0x10f808 = ramfuc_reg(0x10f808);
	ram->fuc.r_0x10f670 = ramfuc_reg(0x10f670);
	ram->fuc.r_0x10f60c = ramfuc_reg(0x10f60c);
	ram->fuc.r_0x10f830 = ramfuc_reg(0x10f830);
	ram->fuc.r_0x1373ec = ramfuc_reg(0x1373ec);
	ram->fuc.r_0x10f800 = ramfuc_reg(0x10f800);
	ram->fuc.r_0x10f82c = ramfuc_reg(0x10f82c);

	ram->fuc.r_0x10f978 = ramfuc_reg(0x10f978);
	ram->fuc.r_0x10f910 = ramfuc_reg(0x10f910);
	ram->fuc.r_0x10f914 = ramfuc_reg(0x10f914);

	चयन (ram->base.type) अणु
	हाल NVKM_RAM_TYPE_GDDR5:
		ram->fuc.r_mr[0] = ramfuc_reg(0x10f300);
		ram->fuc.r_mr[1] = ramfuc_reg(0x10f330);
		ram->fuc.r_mr[2] = ramfuc_reg(0x10f334);
		ram->fuc.r_mr[3] = ramfuc_reg(0x10f338);
		ram->fuc.r_mr[4] = ramfuc_reg(0x10f33c);
		ram->fuc.r_mr[5] = ramfuc_reg(0x10f340);
		ram->fuc.r_mr[6] = ramfuc_reg(0x10f344);
		ram->fuc.r_mr[7] = ramfuc_reg(0x10f348);
		ram->fuc.r_mr[8] = ramfuc_reg(0x10f354);
		ram->fuc.r_mr[15] = ramfuc_reg(0x10f34c);
		अवरोध;
	हाल NVKM_RAM_TYPE_DDR3:
		ram->fuc.r_mr[0] = ramfuc_reg(0x10f300);
		ram->fuc.r_mr[1] = ramfuc_reg(0x10f304);
		ram->fuc.r_mr[2] = ramfuc_reg(0x10f320);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ram->fuc.r_0x62c000 = ramfuc_reg(0x62c000);
	ram->fuc.r_0x10f200 = ramfuc_reg(0x10f200);
	ram->fuc.r_0x10f210 = ramfuc_reg(0x10f210);
	ram->fuc.r_0x10f310 = ramfuc_reg(0x10f310);
	ram->fuc.r_0x10f314 = ramfuc_reg(0x10f314);
	ram->fuc.r_0x10f318 = ramfuc_reg(0x10f318);
	ram->fuc.r_0x10f090 = ramfuc_reg(0x10f090);
	ram->fuc.r_0x10f69c = ramfuc_reg(0x10f69c);
	ram->fuc.r_0x10f824 = ramfuc_reg(0x10f824);
	ram->fuc.r_0x1373f0 = ramfuc_reg(0x1373f0);
	ram->fuc.r_0x1373f4 = ramfuc_reg(0x1373f4);
	ram->fuc.r_0x137320 = ramfuc_reg(0x137320);
	ram->fuc.r_0x10f65c = ramfuc_reg(0x10f65c);
	ram->fuc.r_0x10f6bc = ramfuc_reg(0x10f6bc);
	ram->fuc.r_0x100710 = ramfuc_reg(0x100710);
	ram->fuc.r_0x100750 = ramfuc_reg(0x100750);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_ram_func
gk104_ram = अणु
	.upper = 0x0200000000ULL,
	.probe_fbp = gf100_ram_probe_fbp,
	.probe_fbp_amount = gf108_ram_probe_fbp_amount,
	.probe_fbpa_amount = gf100_ram_probe_fbpa_amount,
	.dtor = gk104_ram_dtor,
	.init = gk104_ram_init,
	.calc = gk104_ram_calc,
	.prog = gk104_ram_prog,
	.tidy = gk104_ram_tidy,
पूर्ण;

पूर्णांक
gk104_ram_new(काष्ठा nvkm_fb *fb, काष्ठा nvkm_ram **pram)
अणु
	वापस gk104_ram_new_(&gk104_ram, fb, pram);
पूर्ण
