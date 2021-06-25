<शैली गुरु>
/*
 * Copyright 2019 Red Hat Inc.
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
#समावेश "priv.h"

अटल स्थिर काष्ठा nvkm_falcon_func
gv100_gsp_flcn = अणु
	.fbअगर = 0x600,
	.load_imem = nvkm_falcon_v1_load_imem,
	.load_dmem = nvkm_falcon_v1_load_dmem,
	.पढ़ो_dmem = nvkm_falcon_v1_पढ़ो_dmem,
	.bind_context = gp102_sec2_flcn_bind_context,
	.रुको_क्रम_halt = nvkm_falcon_v1_रुको_क्रम_halt,
	.clear_पूर्णांकerrupt = nvkm_falcon_v1_clear_पूर्णांकerrupt,
	.set_start_addr = nvkm_falcon_v1_set_start_addr,
	.start = nvkm_falcon_v1_start,
	.enable = gp102_sec2_flcn_enable,
	.disable = nvkm_falcon_v1_disable,
पूर्ण;

अटल पूर्णांक
gv100_gsp_nofw(काष्ठा nvkm_gsp *gsp, पूर्णांक ver, स्थिर काष्ठा nvkm_gsp_fwअगर *fwअगर)
अणु
	वापस 0;
पूर्ण

काष्ठा nvkm_gsp_fwअगर
gv100_gsp[] = अणु
	अणु -1, gv100_gsp_nofw, &gv100_gsp_flcn पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक
gv100_gsp_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_gsp **pgsp)
अणु
	वापस nvkm_gsp_new_(gv100_gsp, device, type, inst, pgsp);
पूर्ण
