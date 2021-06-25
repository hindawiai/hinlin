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

स्थिर काष्ठा nv50_disp_mthd_list
g84_disp_core_mthd_dac = अणु
	.mthd = 0x0080,
	.addr = 0x000008,
	.data = अणु
		अणु 0x0400, 0x610b58 पूर्ण,
		अणु 0x0404, 0x610bdc पूर्ण,
		अणु 0x0420, 0x610bc4 पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

स्थिर काष्ठा nv50_disp_mthd_list
g84_disp_core_mthd_head = अणु
	.mthd = 0x0400,
	.addr = 0x000540,
	.data = अणु
		अणु 0x0800, 0x610ad8 पूर्ण,
		अणु 0x0804, 0x610ad0 पूर्ण,
		अणु 0x0808, 0x610a48 पूर्ण,
		अणु 0x080c, 0x610a78 पूर्ण,
		अणु 0x0810, 0x610ac0 पूर्ण,
		अणु 0x0814, 0x610af8 पूर्ण,
		अणु 0x0818, 0x610b00 पूर्ण,
		अणु 0x081c, 0x610ae8 पूर्ण,
		अणु 0x0820, 0x610af0 पूर्ण,
		अणु 0x0824, 0x610b08 पूर्ण,
		अणु 0x0828, 0x610b10 पूर्ण,
		अणु 0x082c, 0x610a68 पूर्ण,
		अणु 0x0830, 0x610a60 पूर्ण,
		अणु 0x0834, 0x000000 पूर्ण,
		अणु 0x0838, 0x610a40 पूर्ण,
		अणु 0x0840, 0x610a24 पूर्ण,
		अणु 0x0844, 0x610a2c पूर्ण,
		अणु 0x0848, 0x610aa8 पूर्ण,
		अणु 0x084c, 0x610ab0 पूर्ण,
		अणु 0x085c, 0x610c5c पूर्ण,
		अणु 0x0860, 0x610a84 पूर्ण,
		अणु 0x0864, 0x610a90 पूर्ण,
		अणु 0x0868, 0x610b18 पूर्ण,
		अणु 0x086c, 0x610b20 पूर्ण,
		अणु 0x0870, 0x610ac8 पूर्ण,
		अणु 0x0874, 0x610a38 पूर्ण,
		अणु 0x0878, 0x610c50 पूर्ण,
		अणु 0x0880, 0x610a58 पूर्ण,
		अणु 0x0884, 0x610a9c पूर्ण,
		अणु 0x089c, 0x610c68 पूर्ण,
		अणु 0x08a0, 0x610a70 पूर्ण,
		अणु 0x08a4, 0x610a50 पूर्ण,
		अणु 0x08a8, 0x610ae0 पूर्ण,
		अणु 0x08c0, 0x610b28 पूर्ण,
		अणु 0x08c4, 0x610b30 पूर्ण,
		अणु 0x08c8, 0x610b40 पूर्ण,
		अणु 0x08d4, 0x610b38 पूर्ण,
		अणु 0x08d8, 0x610b48 पूर्ण,
		अणु 0x08dc, 0x610b50 पूर्ण,
		अणु 0x0900, 0x610a18 पूर्ण,
		अणु 0x0904, 0x610ab8 पूर्ण,
		अणु 0x0910, 0x610c70 पूर्ण,
		अणु 0x0914, 0x610c78 पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

स्थिर काष्ठा nv50_disp_chan_mthd
g84_disp_core_mthd = अणु
	.name = "Core",
	.addr = 0x000000,
	.prev = 0x000004,
	.data = अणु
		अणु "Global", 1, &nv50_disp_core_mthd_base पूर्ण,
		अणु    "DAC", 3, &g84_disp_core_mthd_dac  पूर्ण,
		अणु    "SOR", 2, &nv50_disp_core_mthd_sor  पूर्ण,
		अणु   "PIOR", 3, &nv50_disp_core_mthd_pior पूर्ण,
		अणु   "HEAD", 2, &g84_disp_core_mthd_head पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
g84_disp_core_new(स्थिर काष्ठा nvkm_oclass *oclass, व्योम *argv, u32 argc,
		  काष्ठा nv50_disp *disp, काष्ठा nvkm_object **pobject)
अणु
	वापस nv50_disp_core_new_(&nv50_disp_core_func, &g84_disp_core_mthd,
				   disp, 0, oclass, argv, argc, pobject);
पूर्ण
