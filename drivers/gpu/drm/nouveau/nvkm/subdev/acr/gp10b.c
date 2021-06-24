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

#अगर IS_ENABLED(CONFIG_ARCH_TEGRA_186_SOC)
MODULE_FIRMWARE("nvidia/gp10b/acr/bl.bin");
MODULE_FIRMWARE("nvidia/gp10b/acr/ucode_load.bin");
#पूर्ण_अगर

अटल स्थिर काष्ठा nvkm_acr_hsf_fwअगर
gp10b_acr_load_fwअगर[] = अणु
	अणु 0, nvkm_acr_hsfw_load, &gm20b_acr_load_0 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_acr_func
gp10b_acr = अणु
	.load = gp10b_acr_load_fwअगर,
	.wpr_parse = gm200_acr_wpr_parse,
	.wpr_layout = gm200_acr_wpr_layout,
	.wpr_alloc = gm20b_acr_wpr_alloc,
	.wpr_build = gm200_acr_wpr_build,
	.wpr_patch = gm200_acr_wpr_patch,
	.wpr_check = gm200_acr_wpr_check,
	.init = gm200_acr_init,
पूर्ण;

अटल स्थिर काष्ठा nvkm_acr_fwअगर
gp10b_acr_fwअगर[] = अणु
	अणु  0, gm20b_acr_load, &gp10b_acr पूर्ण,
	अणु -1, gm200_acr_nofw, &gm200_acr पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक
gp10b_acr_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_acr **pacr)
अणु
	वापस nvkm_acr_new_(gp10b_acr_fwअगर, device, type, inst, pacr);
पूर्ण
