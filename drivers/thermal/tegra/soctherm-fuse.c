<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014-2016, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <soc/tegra/fuse.h>

#समावेश "soctherm.h"

#घोषणा NOMINAL_CALIB_FT			105
#घोषणा NOMINAL_CALIB_CP			25

#घोषणा FUSE_TSENSOR_CALIB_CP_TS_BASE_MASK	0x1fff
#घोषणा FUSE_TSENSOR_CALIB_FT_TS_BASE_MASK	(0x1fff << 13)
#घोषणा FUSE_TSENSOR_CALIB_FT_TS_BASE_SHIFT	13

#घोषणा FUSE_TSENSOR_COMMON			0x180

/*
 * Tegra210: Layout of bits in FUSE_TSENSOR_COMMON:
 *    3                   2                   1                   0
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |       BASE_FT       |      BASE_CP      | SHFT_FT | SHIFT_CP  |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * Tegra12x, etc:
 * In chips prior to Tegra210, this fuse was incorrectly sized as 26 bits,
 * and didn't hold SHIFT_CP in [31:26]. Thereक्रमe these missing six bits
 * were obtained via the FUSE_SPARE_REALIGNMENT_REG रेजिस्टर [5:0].
 *
 * FUSE_TSENSOR_COMMON:
 *    3                   2                   1                   0
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |-----------| SHFT_FT |       BASE_FT       |      BASE_CP      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * FUSE_SPARE_REALIGNMENT_REG:
 *    3                   2                   1                   0
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |---------------------------------------------------| SHIFT_CP  |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#घोषणा CALIB_COEFFICIENT 1000000LL

/**
 * भाग64_s64_precise() - wrapper क्रम भाग64_s64()
 * @a:  the भागidend
 * @b:  the भागisor
 *
 * Implements भागision with fairly accurate rounding instead of truncation by
 * shअगरting the भागidend to the left by 16 so that the quotient has a
 * much higher precision.
 *
 * Return: the quotient of a / b.
 */
अटल s64 भाग64_s64_precise(s64 a, s32 b)
अणु
	s64 r, al;

	/* Scale up क्रम increased precision भागision */
	al = a << 16;

	r = भाग64_s64(al * 2 + 1, 2 * b);
	वापस r >> 16;
पूर्ण

पूर्णांक tegra_calc_shared_calib(स्थिर काष्ठा tegra_soctherm_fuse *tfuse,
			    काष्ठा tsensor_shared_calib *shared)
अणु
	u32 val;
	s32 shअगरted_cp, shअगरted_ft;
	पूर्णांक err;

	err = tegra_fuse_पढ़ोl(FUSE_TSENSOR_COMMON, &val);
	अगर (err)
		वापस err;

	shared->base_cp = (val & tfuse->fuse_base_cp_mask) >>
			  tfuse->fuse_base_cp_shअगरt;
	shared->base_ft = (val & tfuse->fuse_base_ft_mask) >>
			  tfuse->fuse_base_ft_shअगरt;

	shअगरted_ft = (val & tfuse->fuse_shअगरt_ft_mask) >>
		     tfuse->fuse_shअगरt_ft_shअगरt;
	shअगरted_ft = sign_extend32(shअगरted_ft, 4);

	अगर (tfuse->fuse_spare_realignment) अणु
		err = tegra_fuse_पढ़ोl(tfuse->fuse_spare_realignment, &val);
		अगर (err)
			वापस err;
	पूर्ण

	shअगरted_cp = sign_extend32(val, 5);

	shared->actual_temp_cp = 2 * NOMINAL_CALIB_CP + shअगरted_cp;
	shared->actual_temp_ft = 2 * NOMINAL_CALIB_FT + shअगरted_ft;

	वापस 0;
पूर्ण

पूर्णांक tegra_calc_tsensor_calib(स्थिर काष्ठा tegra_tsensor *sensor,
			     स्थिर काष्ठा tsensor_shared_calib *shared,
			     u32 *calibration)
अणु
	स्थिर काष्ठा tegra_tsensor_group *sensor_group;
	u32 val, calib;
	s32 actual_tsensor_ft, actual_tsensor_cp;
	s32 delta_sens, delta_temp;
	s32 mult, भाग;
	s16 therma, thermb;
	s64 temp;
	पूर्णांक err;

	sensor_group = sensor->group;

	err = tegra_fuse_पढ़ोl(sensor->calib_fuse_offset, &val);
	अगर (err)
		वापस err;

	actual_tsensor_cp = (shared->base_cp * 64) + sign_extend32(val, 12);
	val = (val & FUSE_TSENSOR_CALIB_FT_TS_BASE_MASK) >>
	      FUSE_TSENSOR_CALIB_FT_TS_BASE_SHIFT;
	actual_tsensor_ft = (shared->base_ft * 32) + sign_extend32(val, 12);

	delta_sens = actual_tsensor_ft - actual_tsensor_cp;
	delta_temp = shared->actual_temp_ft - shared->actual_temp_cp;

	mult = sensor_group->pभाग * sensor->config->tsample_ate;
	भाग = sensor->config->tsample * sensor_group->pभाग_ate;

	temp = (s64)delta_temp * (1LL << 13) * mult;
	therma = भाग64_s64_precise(temp, (s64)delta_sens * भाग);

	temp = ((s64)actual_tsensor_ft * shared->actual_temp_cp) -
		((s64)actual_tsensor_cp * shared->actual_temp_ft);
	thermb = भाग64_s64_precise(temp, delta_sens);

	temp = (s64)therma * sensor->fuse_corr_alpha;
	therma = भाग64_s64_precise(temp, CALIB_COEFFICIENT);

	temp = (s64)thermb * sensor->fuse_corr_alpha + sensor->fuse_corr_beta;
	thermb = भाग64_s64_precise(temp, CALIB_COEFFICIENT);

	calib = ((u16)therma << SENSOR_CONFIG2_THERMA_SHIFT) |
		((u16)thermb << SENSOR_CONFIG2_THERMB_SHIFT);

	*calibration = calib;

	वापस 0;
पूर्ण

MODULE_AUTHOR("Wei Ni <wni@nvidia.com>");
MODULE_DESCRIPTION("Tegra SOCTHERM fuse management");
MODULE_LICENSE("GPL v2");
