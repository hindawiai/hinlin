<शैली गुरु>
/*
 * Copyright (c) 2016, NVIDIA CORPORATION. All rights reserved.
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
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#समावेश "priv.h"
#समावेश "gk20a.h"

#समावेश <core/tegra.h>

अटल स्थिर काष्ठा cvb_coef gm20b_cvb_coef[] = अणु
	/* KHz,             c0,      c1,   c2 */
	/*  76800 */ अणु 1786666,  -85625, 1632 पूर्ण,
	/* 153600 */ अणु 1846729,  -87525, 1632 पूर्ण,
	/* 230400 */ अणु 1910480,  -89425, 1632 पूर्ण,
	/* 307200 */ अणु 1977920,  -91325, 1632 पूर्ण,
	/* 384000 */ अणु 2049049,  -93215, 1632 पूर्ण,
	/* 460800 */ अणु 2122872,  -95095, 1632 पूर्ण,
	/* 537600 */ अणु 2201331,  -96985, 1632 पूर्ण,
	/* 614400 */ अणु 2283479,  -98885, 1632 पूर्ण,
	/* 691200 */ अणु 2369315, -100785, 1632 पूर्ण,
	/* 768000 */ अणु 2458841, -102685, 1632 पूर्ण,
	/* 844800 */ अणु 2550821, -104555, 1632 पूर्ण,
	/* 921600 */ अणु 2647676, -106455, 1632 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cvb_coef gm20b_na_cvb_coef[] = अणु
	/* KHz,         c0,     c1,   c2,    c3,     c4,   c5 */
	/*  76800 */ अणु  814294, 8144, -940, 808, -21583, 226 पूर्ण,
	/* 153600 */ अणु  856185, 8144, -940, 808, -21583, 226 पूर्ण,
	/* 230400 */ अणु  898077, 8144, -940, 808, -21583, 226 पूर्ण,
	/* 307200 */ अणु  939968, 8144, -940, 808, -21583, 226 पूर्ण,
	/* 384000 */ अणु  981860, 8144, -940, 808, -21583, 226 पूर्ण,
	/* 460800 */ अणु 1023751, 8144, -940, 808, -21583, 226 पूर्ण,
	/* 537600 */ अणु 1065642, 8144, -940, 808, -21583, 226 पूर्ण,
	/* 614400 */ अणु 1107534, 8144, -940, 808, -21583, 226 पूर्ण,
	/* 691200 */ अणु 1149425, 8144, -940, 808, -21583, 226 पूर्ण,
	/* 768000 */ अणु 1191317, 8144, -940, 808, -21583, 226 पूर्ण,
	/* 844800 */ अणु 1233208, 8144, -940, 808, -21583, 226 पूर्ण,
	/* 921600 */ अणु 1275100, 8144, -940, 808, -21583, 226 पूर्ण,
	/* 998400 */ अणु 1316991, 8144, -940, 808, -21583, 226 पूर्ण,
पूर्ण;

अटल स्थिर u32 speeकरो_to_vmin[] = अणु
	/*   0,      1,      2,      3,      4, */
	950000, 840000, 818750, 840000, 810000,
पूर्ण;

पूर्णांक
gm20b_volt_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	       काष्ठा nvkm_volt **pvolt)
अणु
	काष्ठा nvkm_device_tegra *tdev = device->func->tegra(device);
	काष्ठा gk20a_volt *volt;
	u32 vmin;

	अगर (tdev->gpu_speeकरो_id >= ARRAY_SIZE(speeकरो_to_vmin)) अणु
		nvdev_error(device, "unsupported speedo %d\n",
			    tdev->gpu_speeकरो_id);
		वापस -EINVAL;
	पूर्ण

	volt = kzalloc(माप(*volt), GFP_KERNEL);
	अगर (!volt)
		वापस -ENOMEM;
	*pvolt = &volt->base;

	vmin = speeकरो_to_vmin[tdev->gpu_speeकरो_id];

	अगर (tdev->gpu_speeकरो_id >= 1)
		वापस gk20a_volt_ctor(device, type, inst, gm20b_na_cvb_coef,
				       ARRAY_SIZE(gm20b_na_cvb_coef), vmin, volt);
	अन्यथा
		वापस gk20a_volt_ctor(device, type, inst, gm20b_cvb_coef,
				       ARRAY_SIZE(gm20b_cvb_coef), vmin, volt);
पूर्ण
