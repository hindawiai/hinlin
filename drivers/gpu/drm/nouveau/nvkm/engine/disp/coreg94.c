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
g94_disp_core_mthd_sor = अणु
	.mthd = 0x0040,
	.addr = 0x000008,
	.data = अणु
		अणु 0x0600, 0x610794 पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

स्थिर काष्ठा nv50_disp_chan_mthd
g94_disp_core_mthd = अणु
	.name = "Core",
	.addr = 0x000000,
	.prev = 0x000004,
	.data = अणु
		अणु "Global", 1, &nv50_disp_core_mthd_base पूर्ण,
		अणु    "DAC", 3, &g84_disp_core_mthd_dac पूर्ण,
		अणु    "SOR", 4, &g94_disp_core_mthd_sor पूर्ण,
		अणु   "PIOR", 3, &nv50_disp_core_mthd_pior पूर्ण,
		अणु   "HEAD", 2, &g84_disp_core_mthd_head पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
g94_disp_core_new(स्थिर काष्ठा nvkm_oclass *oclass, व्योम *argv, u32 argc,
		  काष्ठा nv50_disp *disp, काष्ठा nvkm_object **pobject)
अणु
	वापस nv50_disp_core_new_(&nv50_disp_core_func, &g94_disp_core_mthd,
				   disp, 0, oclass, argv, argc, pobject);
पूर्ण
