<शैली गुरु>
/*
 * Copyright 2012 Maarten Lankhorst
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
 * Authors: Maarten Lankhorst
 */
#समावेश "priv.h"

#समावेश <nvअगर/class.h>

व्योम
gf100_msvld_init(काष्ठा nvkm_falcon *msvld)
अणु
	काष्ठा nvkm_device *device = msvld->engine.subdev.device;
	nvkm_wr32(device, 0x084010, 0x0000fff2);
	nvkm_wr32(device, 0x08401c, 0x0000fff2);
पूर्ण

अटल स्थिर काष्ठा nvkm_falcon_func
gf100_msvld = अणु
	.init = gf100_msvld_init,
	.sclass = अणु
		अणु -1, -1, GF100_MSVLD पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
gf100_msvld_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
		काष्ठा nvkm_engine **pengine)
अणु
	वापस nvkm_msvld_new_(&gf100_msvld, device, type, inst, pengine);
पूर्ण
