<शैली गुरु>
/*
 * Copyright (c) 2014-2016, NVIDIA CORPORATION. All rights reserved.
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
#घोषणा gk20a_volt(p) container_of((p), काष्ठा gk20a_volt, base)
#समावेश "priv.h"

#समावेश <core/tegra.h>

#समावेश "gk20a.h"

अटल स्थिर काष्ठा cvb_coef gk20a_cvb_coef[] = अणु
	/* MHz,        c0,     c1,   c2,    c3,     c4,   c5 */
	/*  72 */ अणु 1209886, -36468,  515,   417, -13123,  203पूर्ण,
	/* 108 */ अणु 1130804, -27659,  296,   298, -10834,  221पूर्ण,
	/* 180 */ अणु 1162871, -27110,  247,   238, -10681,  268पूर्ण,
	/* 252 */ अणु 1220458, -28654,  247,   179, -10376,  298पूर्ण,
	/* 324 */ अणु 1280953, -30204,  247,   119,  -9766,  304पूर्ण,
	/* 396 */ अणु 1344547, -31777,  247,   119,  -8545,  292पूर्ण,
	/* 468 */ अणु 1420168, -34227,  269,    60,  -7172,  256पूर्ण,
	/* 540 */ अणु 1490757, -35955,  274,    60,  -5188,  197पूर्ण,
	/* 612 */ अणु 1599112, -42583,  398,     0,  -1831,  119पूर्ण,
	/* 648 */ अणु 1366986, -16459, -274,     0,  -3204,   72पूर्ण,
	/* 684 */ अणु 1391884, -17078, -274,   -60,  -1526,   30पूर्ण,
	/* 708 */ अणु 1415522, -17497, -274,   -60,   -458,    0पूर्ण,
	/* 756 */ अणु 1464061, -18331, -274,  -119,   1831,  -72पूर्ण,
	/* 804 */ अणु 1524225, -20064, -254,  -119,   4272, -155पूर्ण,
	/* 852 */ अणु 1608418, -21643, -269,     0,    763,  -48पूर्ण,
पूर्ण;

/**
 * cvb_mv = ((c2 * speeकरो / s_scale + c1) * speeकरो / s_scale + c0)
 */
अटल अंतरभूत पूर्णांक
gk20a_volt_get_cvb_voltage(पूर्णांक speeकरो, पूर्णांक s_scale, स्थिर काष्ठा cvb_coef *coef)
अणु
	पूर्णांक mv;

	mv = DIV_ROUND_CLOSEST(coef->c2 * speeकरो, s_scale);
	mv = DIV_ROUND_CLOSEST((mv + coef->c1) * speeकरो, s_scale) + coef->c0;
	वापस mv;
पूर्ण

/**
 * cvb_t_mv =
 * ((c2 * speeकरो / s_scale + c1) * speeकरो / s_scale + c0) +
 * ((c3 * speeकरो / s_scale + c4 + c5 * T / t_scale) * T / t_scale)
 */
अटल अंतरभूत पूर्णांक
gk20a_volt_get_cvb_t_voltage(पूर्णांक speeकरो, पूर्णांक temp, पूर्णांक s_scale, पूर्णांक t_scale,
			     स्थिर काष्ठा cvb_coef *coef)
अणु
	पूर्णांक cvb_mv, mv;

	cvb_mv = gk20a_volt_get_cvb_voltage(speeकरो, s_scale, coef);

	mv = DIV_ROUND_CLOSEST(coef->c3 * speeकरो, s_scale) + coef->c4 +
		DIV_ROUND_CLOSEST(coef->c5 * temp, t_scale);
	mv = DIV_ROUND_CLOSEST(mv * temp, t_scale) + cvb_mv;
	वापस mv;
पूर्ण

अटल पूर्णांक
gk20a_volt_calc_voltage(स्थिर काष्ठा cvb_coef *coef, पूर्णांक speeकरो)
अणु
	अटल स्थिर पूर्णांक v_scale = 1000;
	पूर्णांक mv;

	mv = gk20a_volt_get_cvb_t_voltage(speeकरो, -10, 100, 10, coef);
	mv = DIV_ROUND_UP(mv, v_scale);

	वापस mv * 1000;
पूर्ण

अटल पूर्णांक
gk20a_volt_vid_get(काष्ठा nvkm_volt *base)
अणु
	काष्ठा gk20a_volt *volt = gk20a_volt(base);
	पूर्णांक i, uv;

	uv = regulator_get_voltage(volt->vdd);

	क्रम (i = 0; i < volt->base.vid_nr; i++)
		अगर (volt->base.vid[i].uv >= uv)
			वापस i;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
gk20a_volt_vid_set(काष्ठा nvkm_volt *base, u8 vid)
अणु
	काष्ठा gk20a_volt *volt = gk20a_volt(base);
	काष्ठा nvkm_subdev *subdev = &volt->base.subdev;

	nvkm_debug(subdev, "set voltage as %duv\n", volt->base.vid[vid].uv);
	वापस regulator_set_voltage(volt->vdd, volt->base.vid[vid].uv, 1200000);
पूर्ण

अटल पूर्णांक
gk20a_volt_set_id(काष्ठा nvkm_volt *base, u8 id, पूर्णांक condition)
अणु
	काष्ठा gk20a_volt *volt = gk20a_volt(base);
	काष्ठा nvkm_subdev *subdev = &volt->base.subdev;
	पूर्णांक prev_uv = regulator_get_voltage(volt->vdd);
	पूर्णांक target_uv = volt->base.vid[id].uv;
	पूर्णांक ret;

	nvkm_debug(subdev, "prev=%d, target=%d, condition=%d\n",
		   prev_uv, target_uv, condition);
	अगर (!condition ||
		(condition < 0 && target_uv < prev_uv) ||
		(condition > 0 && target_uv > prev_uv)) अणु
		ret = gk20a_volt_vid_set(&volt->base, volt->base.vid[id].vid);
	पूर्ण अन्यथा अणु
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nvkm_volt_func
gk20a_volt = अणु
	.vid_get = gk20a_volt_vid_get,
	.vid_set = gk20a_volt_vid_set,
	.set_id = gk20a_volt_set_id,
पूर्ण;

पूर्णांक
gk20a_volt_ctor(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
		स्थिर काष्ठा cvb_coef *coefs, पूर्णांक nb_coefs,
		पूर्णांक vmin, काष्ठा gk20a_volt *volt)
अणु
	काष्ठा nvkm_device_tegra *tdev = device->func->tegra(device);
	पूर्णांक i, uv;

	nvkm_volt_ctor(&gk20a_volt, device, type, inst, &volt->base);

	uv = regulator_get_voltage(tdev->vdd);
	nvkm_debug(&volt->base.subdev, "the default voltage is %duV\n", uv);

	volt->vdd = tdev->vdd;

	volt->base.vid_nr = nb_coefs;
	क्रम (i = 0; i < volt->base.vid_nr; i++) अणु
		volt->base.vid[i].vid = i;
		volt->base.vid[i].uv = max(
			gk20a_volt_calc_voltage(&coefs[i], tdev->gpu_speeकरो),
			vmin);
		nvkm_debug(&volt->base.subdev, "%2d: vid=%d, uv=%d\n", i,
			   volt->base.vid[i].vid, volt->base.vid[i].uv);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
gk20a_volt_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_volt **pvolt)
अणु
	काष्ठा gk20a_volt *volt;

	volt = kzalloc(माप(*volt), GFP_KERNEL);
	अगर (!volt)
		वापस -ENOMEM;
	*pvolt = &volt->base;

	वापस gk20a_volt_ctor(device, type, inst, gk20a_cvb_coef,
			       ARRAY_SIZE(gk20a_cvb_coef), 0, volt);
पूर्ण
