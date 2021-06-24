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
 */
#समावेश "channv50.h"

अटल स्थिर काष्ठा nv50_disp_mthd_list
gf119_disp_base_mthd_base = अणु
	.mthd = 0x0000,
	.addr = 0x000000,
	.data = अणु
		अणु 0x0080, 0x661080 पूर्ण,
		अणु 0x0084, 0x661084 पूर्ण,
		अणु 0x0088, 0x661088 पूर्ण,
		अणु 0x008c, 0x66108c पूर्ण,
		अणु 0x0090, 0x661090 पूर्ण,
		अणु 0x0094, 0x661094 पूर्ण,
		अणु 0x00a0, 0x6610a0 पूर्ण,
		अणु 0x00a4, 0x6610a4 पूर्ण,
		अणु 0x00c0, 0x6610c0 पूर्ण,
		अणु 0x00c4, 0x6610c4 पूर्ण,
		अणु 0x00c8, 0x6610c8 पूर्ण,
		अणु 0x00cc, 0x6610cc पूर्ण,
		अणु 0x00e0, 0x6610e0 पूर्ण,
		अणु 0x00e4, 0x6610e4 पूर्ण,
		अणु 0x00e8, 0x6610e8 पूर्ण,
		अणु 0x00ec, 0x6610ec पूर्ण,
		अणु 0x00fc, 0x6610fc पूर्ण,
		अणु 0x0100, 0x661100 पूर्ण,
		अणु 0x0104, 0x661104 पूर्ण,
		अणु 0x0108, 0x661108 पूर्ण,
		अणु 0x010c, 0x66110c पूर्ण,
		अणु 0x0110, 0x661110 पूर्ण,
		अणु 0x0114, 0x661114 पूर्ण,
		अणु 0x0118, 0x661118 पूर्ण,
		अणु 0x011c, 0x66111c पूर्ण,
		अणु 0x0130, 0x661130 पूर्ण,
		अणु 0x0134, 0x661134 पूर्ण,
		अणु 0x0138, 0x661138 पूर्ण,
		अणु 0x013c, 0x66113c पूर्ण,
		अणु 0x0140, 0x661140 पूर्ण,
		अणु 0x0144, 0x661144 पूर्ण,
		अणु 0x0148, 0x661148 पूर्ण,
		अणु 0x014c, 0x66114c पूर्ण,
		अणु 0x0150, 0x661150 पूर्ण,
		अणु 0x0154, 0x661154 पूर्ण,
		अणु 0x0158, 0x661158 पूर्ण,
		अणु 0x015c, 0x66115c पूर्ण,
		अणु 0x0160, 0x661160 पूर्ण,
		अणु 0x0164, 0x661164 पूर्ण,
		अणु 0x0168, 0x661168 पूर्ण,
		अणु 0x016c, 0x66116c पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा nv50_disp_mthd_list
gf119_disp_base_mthd_image = अणु
	.mthd = 0x0020,
	.addr = 0x000020,
	.data = अणु
		अणु 0x0400, 0x661400 पूर्ण,
		अणु 0x0404, 0x661404 पूर्ण,
		अणु 0x0408, 0x661408 पूर्ण,
		अणु 0x040c, 0x66140c पूर्ण,
		अणु 0x0410, 0x661410 पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

स्थिर काष्ठा nv50_disp_chan_mthd
gf119_disp_base_mthd = अणु
	.name = "Base",
	.addr = 0x001000,
	.prev = -0x020000,
	.data = अणु
		अणु "Global", 1, &gf119_disp_base_mthd_base पूर्ण,
		अणु  "Image", 2, &gf119_disp_base_mthd_image पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
gf119_disp_base_new(स्थिर काष्ठा nvkm_oclass *oclass, व्योम *argv, u32 argc,
		    काष्ठा nv50_disp *disp, काष्ठा nvkm_object **pobject)
अणु
	वापस nv50_disp_base_new_(&gf119_disp_dmac_func, &gf119_disp_base_mthd,
				   disp, 1, oclass, argv, argc, pobject);
पूर्ण
