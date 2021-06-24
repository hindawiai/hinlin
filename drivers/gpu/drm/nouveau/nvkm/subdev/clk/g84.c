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
 * Authors: Ben Skeggs <bskeggs@redhat.com>
 */
#समावेश "nv50.h"

अटल स्थिर काष्ठा nvkm_clk_func
g84_clk = अणु
	.पढ़ो = nv50_clk_पढ़ो,
	.calc = nv50_clk_calc,
	.prog = nv50_clk_prog,
	.tidy = nv50_clk_tidy,
	.करोमुख्यs = अणु
		अणु nv_clk_src_crystal, 0xff पूर्ण,
		अणु nv_clk_src_href   , 0xff पूर्ण,
		अणु nv_clk_src_core   , 0xff, 0, "core", 1000 पूर्ण,
		अणु nv_clk_src_shader , 0xff, 0, "shader", 1000 पूर्ण,
		अणु nv_clk_src_mem    , 0xff, 0, "memory", 1000 पूर्ण,
		अणु nv_clk_src_vdec   , 0xff पूर्ण,
		अणु nv_clk_src_max पूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
g84_clk_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	    काष्ठा nvkm_clk **pclk)
अणु
	वापस nv50_clk_new_(&g84_clk, device, type, inst, (device->chipset >= 0x94), pclk);
पूर्ण
