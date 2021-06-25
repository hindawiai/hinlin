<शैली गुरु>
/*
 * Copyright 2018 Red Hat Inc.
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
 */
#समावेश "rootnv50.h"
#समावेश "channv50.h"

#समावेश <nvअगर/class.h>

अटल स्थिर काष्ठा nv50_disp_root_func
tu102_disp_root = अणु
	.user = अणु
		अणुअणु-1,-1,GV100_DISP_CAPS                पूर्ण, gv100_disp_caps_new पूर्ण,
		अणुअणु0,0,TU102_DISP_CURSOR                पूर्ण, gv100_disp_curs_new पूर्ण,
		अणुअणु0,0,TU102_DISP_WINDOW_IMM_CHANNEL_DMAपूर्ण, gv100_disp_wimm_new पूर्ण,
		अणुअणु0,0,TU102_DISP_CORE_CHANNEL_DMA      पूर्ण, gv100_disp_core_new पूर्ण,
		अणुअणु0,0,TU102_DISP_WINDOW_CHANNEL_DMA    पूर्ण, gv100_disp_wndw_new पूर्ण,
		अणुपूर्ण
	पूर्ण,
पूर्ण;

अटल पूर्णांक
tu102_disp_root_new(काष्ठा nvkm_disp *disp, स्थिर काष्ठा nvkm_oclass *oclass,
		    व्योम *data, u32 size, काष्ठा nvkm_object **pobject)
अणु
	वापस nv50_disp_root_new_(&tu102_disp_root, disp, oclass,
				   data, size, pobject);
पूर्ण

स्थिर काष्ठा nvkm_disp_oclass
tu102_disp_root_oclass = अणु
	.base.oclass = TU102_DISP,
	.base.minver = -1,
	.base.maxver = -1,
	.ctor = tu102_disp_root_new,
पूर्ण;
