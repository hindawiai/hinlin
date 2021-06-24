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
#समावेश "nv50.h"
#समावेश "head.h"
#समावेश "ior.h"
#समावेश "rootnv50.h"

अटल स्थिर काष्ठा nv50_disp_func
gt215_disp = अणु
	.init = nv50_disp_init,
	.fini = nv50_disp_fini,
	.पूर्णांकr = nv50_disp_पूर्णांकr,
	.uevent = &nv50_disp_chan_uevent,
	.super = nv50_disp_super,
	.root = &gt215_disp_root_oclass,
	.head = अणु .cnt = nv50_head_cnt, .new = nv50_head_new पूर्ण,
	.dac = अणु .cnt = nv50_dac_cnt, .new = nv50_dac_new पूर्ण,
	.sor = अणु .cnt = g94_sor_cnt, .new = gt215_sor_new पूर्ण,
	.pior = अणु .cnt = nv50_pior_cnt, .new = nv50_pior_new पूर्ण,
पूर्ण;

पूर्णांक
gt215_disp_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	       काष्ठा nvkm_disp **pdisp)
अणु
	वापस nv50_disp_new_(&gt215_disp, device, type, inst, pdisp);
पूर्ण
