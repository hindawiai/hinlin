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
g84_disp_ovly_mthd_base = अणु
	.mthd = 0x0000,
	.addr = 0x000000,
	.data = अणु
		अणु 0x0080, 0x000000 पूर्ण,
		अणु 0x0084, 0x6109a0 पूर्ण,
		अणु 0x0088, 0x6109c0 पूर्ण,
		अणु 0x008c, 0x6109c8 पूर्ण,
		अणु 0x0090, 0x6109b4 पूर्ण,
		अणु 0x0094, 0x610970 पूर्ण,
		अणु 0x00a0, 0x610998 पूर्ण,
		अणु 0x00a4, 0x610964 पूर्ण,
		अणु 0x00c0, 0x610958 पूर्ण,
		अणु 0x00e0, 0x6109a8 पूर्ण,
		अणु 0x00e4, 0x6109d0 पूर्ण,
		अणु 0x00e8, 0x6109d8 पूर्ण,
		अणु 0x0100, 0x61094c पूर्ण,
		अणु 0x0104, 0x610984 पूर्ण,
		अणु 0x0108, 0x61098c पूर्ण,
		अणु 0x0800, 0x6109f8 पूर्ण,
		अणु 0x0808, 0x610a08 पूर्ण,
		अणु 0x080c, 0x610a10 पूर्ण,
		अणु 0x0810, 0x610a00 पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा nv50_disp_chan_mthd
g84_disp_ovly_mthd = अणु
	.name = "Overlay",
	.addr = 0x000540,
	.prev = 0x000004,
	.data = अणु
		अणु "Global", 1, &g84_disp_ovly_mthd_base पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
g84_disp_ovly_new(स्थिर काष्ठा nvkm_oclass *oclass, व्योम *argv, u32 argc,
		  काष्ठा nv50_disp *disp, काष्ठा nvkm_object **pobject)
अणु
	वापस nv50_disp_ovly_new_(&nv50_disp_dmac_func, &g84_disp_ovly_mthd,
				   disp, 3, oclass, argv, argc, pobject);
पूर्ण
