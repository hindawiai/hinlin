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
#समावेश <subdev/acr.h>

अटल स्थिर काष्ठा nvkm_falcon_func
tu102_sec2_flcn = अणु
	.debug = 0x408,
	.fbअगर = 0x600,
	.load_imem = nvkm_falcon_v1_load_imem,
	.load_dmem = nvkm_falcon_v1_load_dmem,
	.पढ़ो_dmem = nvkm_falcon_v1_पढ़ो_dmem,
	.emem_addr = 0x01000000,
	.bind_context = gp102_sec2_flcn_bind_context,
	.रुको_क्रम_halt = nvkm_falcon_v1_रुको_क्रम_halt,
	.clear_पूर्णांकerrupt = nvkm_falcon_v1_clear_पूर्णांकerrupt,
	.set_start_addr = nvkm_falcon_v1_set_start_addr,
	.start = nvkm_falcon_v1_start,
	.enable = nvkm_falcon_v1_enable,
	.disable = nvkm_falcon_v1_disable,
	.cmdq = अणु 0xc00, 0xc04, 8 पूर्ण,
	.msgq = अणु 0xc80, 0xc84, 8 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_sec2_func
tu102_sec2 = अणु
	.flcn = &tu102_sec2_flcn,
	.unit_acr = 0x07,
	.पूर्णांकr = gp102_sec2_पूर्णांकr,
	.iniपंचांगsg = gp102_sec2_iniपंचांगsg,
पूर्ण;

MODULE_FIRMWARE("nvidia/tu102/sec2/desc.bin");
MODULE_FIRMWARE("nvidia/tu102/sec2/image.bin");
MODULE_FIRMWARE("nvidia/tu102/sec2/sig.bin");
MODULE_FIRMWARE("nvidia/tu104/sec2/desc.bin");
MODULE_FIRMWARE("nvidia/tu104/sec2/image.bin");
MODULE_FIRMWARE("nvidia/tu104/sec2/sig.bin");
MODULE_FIRMWARE("nvidia/tu106/sec2/desc.bin");
MODULE_FIRMWARE("nvidia/tu106/sec2/image.bin");
MODULE_FIRMWARE("nvidia/tu106/sec2/sig.bin");
MODULE_FIRMWARE("nvidia/tu116/sec2/desc.bin");
MODULE_FIRMWARE("nvidia/tu116/sec2/image.bin");
MODULE_FIRMWARE("nvidia/tu116/sec2/sig.bin");
MODULE_FIRMWARE("nvidia/tu117/sec2/desc.bin");
MODULE_FIRMWARE("nvidia/tu117/sec2/image.bin");
MODULE_FIRMWARE("nvidia/tu117/sec2/sig.bin");

अटल स्थिर काष्ठा nvkm_sec2_fwअगर
tu102_sec2_fwअगर[] = अणु
	अणु  0, gp102_sec2_load, &tu102_sec2, &gp102_sec2_acr_1 पूर्ण,
	अणु -1, gp102_sec2_nofw, &tu102_sec2 पूर्ण
पूर्ण;

पूर्णांक
tu102_sec2_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	       काष्ठा nvkm_sec2 **psec2)
अणु
	/* TOP info wasn't updated on Turing to reflect the PRI
	 * address change क्रम some reason.  We override it here.
	 */
	वापस nvkm_sec2_new_(tu102_sec2_fwअगर, device, type, inst, 0x840000, psec2);
पूर्ण
