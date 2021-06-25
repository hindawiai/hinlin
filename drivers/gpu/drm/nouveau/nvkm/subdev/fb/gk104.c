<शैली गुरु>
/*
 * Copyright 2012 Red Hat Inc.
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
 *          Lyude Paul
 */
#समावेश "gk104.h"
#समावेश "gf100.h"
#समावेश "ram.h"

/*
 *******************************************************************************
 * PGRAPH रेजिस्टरs क्रम घड़ीgating
 *******************************************************************************
 */
स्थिर काष्ठा nvkm_therm_clkgate_init
gk104_fb_clkgate_blcg_init_unk_0[] = अणु
	अणु 0x100d10, 1, 0x0000c244 पूर्ण,
	अणु 0x100d30, 1, 0x0000c242 पूर्ण,
	अणु 0x100d3c, 1, 0x00000242 पूर्ण,
	अणु 0x100d48, 1, 0x00000242 पूर्ण,
	अणु 0x100d1c, 1, 0x00000042 पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा nvkm_therm_clkgate_init
gk104_fb_clkgate_blcg_init_vm_0[] = अणु
	अणु 0x100c98, 1, 0x00000242 पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा nvkm_therm_clkgate_init
gk104_fb_clkgate_blcg_init_मुख्य_0[] = अणु
	अणु 0x10f000, 1, 0x00000042 पूर्ण,
	अणु 0x17e030, 1, 0x00000044 पूर्ण,
	अणु 0x17e040, 1, 0x00000044 पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा nvkm_therm_clkgate_init
gk104_fb_clkgate_blcg_init_bcast_0[] = अणु
	अणु 0x17ea60, 4, 0x00000044 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_therm_clkgate_pack
gk104_fb_clkgate_pack[] = अणु
	अणु gk104_fb_clkgate_blcg_init_unk_0 पूर्ण,
	अणु gk104_fb_clkgate_blcg_init_vm_0 पूर्ण,
	अणु gk104_fb_clkgate_blcg_init_मुख्य_0 पूर्ण,
	अणु gk104_fb_clkgate_blcg_init_bcast_0 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_fb_func
gk104_fb = अणु
	.dtor = gf100_fb_dtor,
	.oneinit = gf100_fb_oneinit,
	.init = gf100_fb_init,
	.init_page = gf100_fb_init_page,
	.पूर्णांकr = gf100_fb_पूर्णांकr,
	.ram_new = gk104_ram_new,
	.शेष_bigpage = 17,
	.clkgate_pack = gk104_fb_clkgate_pack,
पूर्ण;

पूर्णांक
gk104_fb_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_fb **pfb)
अणु
	वापस gf100_fb_new_(&gk104_fb, device, type, inst, pfb);
पूर्ण
