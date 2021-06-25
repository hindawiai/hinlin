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
#समावेश "priv.h"
#समावेश "fuc/gf100.fuc3.h"

#समावेश <nvअगर/class.h>

अटल व्योम
gf100_ce_init(काष्ठा nvkm_falcon *ce)
अणु
	nvkm_wr32(ce->engine.subdev.device, ce->addr + 0x084, ce->engine.subdev.inst);
पूर्ण

अटल स्थिर काष्ठा nvkm_falcon_func
gf100_ce0 = अणु
	.code.data = gf100_ce_code,
	.code.size = माप(gf100_ce_code),
	.data.data = gf100_ce_data,
	.data.size = माप(gf100_ce_data),
	.init = gf100_ce_init,
	.पूर्णांकr = gt215_ce_पूर्णांकr,
	.sclass = अणु
		अणु -1, -1, FERMI_DMA पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_falcon_func
gf100_ce1 = अणु
	.code.data = gf100_ce_code,
	.code.size = माप(gf100_ce_code),
	.data.data = gf100_ce_data,
	.data.size = माप(gf100_ce_data),
	.init = gf100_ce_init,
	.पूर्णांकr = gt215_ce_पूर्णांकr,
	.sclass = अणु
		अणु -1, -1, FERMI_DECOMPRESS पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
gf100_ce_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	     काष्ठा nvkm_engine **pengine)
अणु
	वापस nvkm_falcon_new_(inst ? &gf100_ce1 : &gf100_ce0, device, type, inst, true,
				0x104000 + (inst * 0x1000), pengine);
पूर्ण
