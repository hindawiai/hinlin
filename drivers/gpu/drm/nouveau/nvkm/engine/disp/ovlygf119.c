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
gf119_disp_ovly_mthd_base = अणु
	.mthd = 0x0000,
	.data = अणु
		अणु 0x0080, 0x665080 पूर्ण,
		अणु 0x0084, 0x665084 पूर्ण,
		अणु 0x0088, 0x665088 पूर्ण,
		अणु 0x008c, 0x66508c पूर्ण,
		अणु 0x0090, 0x665090 पूर्ण,
		अणु 0x0094, 0x665094 पूर्ण,
		अणु 0x00a0, 0x6650a0 पूर्ण,
		अणु 0x00a4, 0x6650a4 पूर्ण,
		अणु 0x00b0, 0x6650b0 पूर्ण,
		अणु 0x00b4, 0x6650b4 पूर्ण,
		अणु 0x00b8, 0x6650b8 पूर्ण,
		अणु 0x00c0, 0x6650c0 पूर्ण,
		अणु 0x00e0, 0x6650e0 पूर्ण,
		अणु 0x00e4, 0x6650e4 पूर्ण,
		अणु 0x00e8, 0x6650e8 पूर्ण,
		अणु 0x0100, 0x665100 पूर्ण,
		अणु 0x0104, 0x665104 पूर्ण,
		अणु 0x0108, 0x665108 पूर्ण,
		अणु 0x010c, 0x66510c पूर्ण,
		अणु 0x0110, 0x665110 पूर्ण,
		अणु 0x0118, 0x665118 पूर्ण,
		अणु 0x011c, 0x66511c पूर्ण,
		अणु 0x0120, 0x665120 पूर्ण,
		अणु 0x0124, 0x665124 पूर्ण,
		अणु 0x0130, 0x665130 पूर्ण,
		अणु 0x0134, 0x665134 पूर्ण,
		अणु 0x0138, 0x665138 पूर्ण,
		अणु 0x013c, 0x66513c पूर्ण,
		अणु 0x0140, 0x665140 पूर्ण,
		अणु 0x0144, 0x665144 पूर्ण,
		अणु 0x0148, 0x665148 पूर्ण,
		अणु 0x014c, 0x66514c पूर्ण,
		अणु 0x0150, 0x665150 पूर्ण,
		अणु 0x0154, 0x665154 पूर्ण,
		अणु 0x0158, 0x665158 पूर्ण,
		अणु 0x015c, 0x66515c पूर्ण,
		अणु 0x0160, 0x665160 पूर्ण,
		अणु 0x0164, 0x665164 पूर्ण,
		अणु 0x0168, 0x665168 पूर्ण,
		अणु 0x016c, 0x66516c पूर्ण,
		अणु 0x0400, 0x665400 पूर्ण,
		अणु 0x0408, 0x665408 पूर्ण,
		अणु 0x040c, 0x66540c पूर्ण,
		अणु 0x0410, 0x665410 पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा nv50_disp_chan_mthd
gf119_disp_ovly_mthd = अणु
	.name = "Overlay",
	.addr = 0x001000,
	.prev = -0x020000,
	.data = अणु
		अणु "Global", 1, &gf119_disp_ovly_mthd_base पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
gf119_disp_ovly_new(स्थिर काष्ठा nvkm_oclass *oclass, व्योम *argv, u32 argc,
		    काष्ठा nv50_disp *disp, काष्ठा nvkm_object **pobject)
अणु
	वापस nv50_disp_ovly_new_(&gf119_disp_dmac_func, &gf119_disp_ovly_mthd,
				   disp, 5, oclass, argv, argc, pobject);
पूर्ण
