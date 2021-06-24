<शैली गुरु>
/*
 * Copyright 2016 Red Hat Inc.
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
#समावेश "rootnv50.h"
#समावेश "channv50.h"

#समावेश <nvअगर/class.h>

अटल स्थिर काष्ठा nv50_disp_root_func
gp102_disp_root = अणु
	.user = अणु
		अणुअणु0,0,GK104_DISP_CURSOR             पूर्ण, gp102_disp_curs_new पूर्ण,
		अणुअणु0,0,GK104_DISP_OVERLAY            पूर्ण, gp102_disp_oimm_new पूर्ण,
		अणुअणु0,0,GK110_DISP_BASE_CHANNEL_DMA   पूर्ण, gp102_disp_base_new पूर्ण,
		अणुअणु0,0,GP102_DISP_CORE_CHANNEL_DMA   पूर्ण, gp102_disp_core_new पूर्ण,
		अणुअणु0,0,GK104_DISP_OVERLAY_CONTROL_DMAपूर्ण, gp102_disp_ovly_new पूर्ण,
		अणुपूर्ण
	पूर्ण,
पूर्ण;

अटल पूर्णांक
gp102_disp_root_new(काष्ठा nvkm_disp *disp, स्थिर काष्ठा nvkm_oclass *oclass,
		    व्योम *data, u32 size, काष्ठा nvkm_object **pobject)
अणु
	वापस nv50_disp_root_new_(&gp102_disp_root, disp, oclass,
				   data, size, pobject);
पूर्ण

स्थिर काष्ठा nvkm_disp_oclass
gp102_disp_root_oclass = अणु
	.base.oclass = GP102_DISP,
	.base.minver = -1,
	.base.maxver = -1,
	.ctor = gp102_disp_root_new,
पूर्ण;
