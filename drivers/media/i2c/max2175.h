<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Maxim Integrated MAX2175 RF to Bits tuner driver
 *
 * This driver & most of the hard coded values are based on the reference
 * application delivered by Maxim क्रम this device.
 *
 * Copyright (C) 2016 Maxim Integrated Products
 * Copyright (C) 2017 Renesas Electronics Corporation
 */

#अगर_अघोषित __MAX2175_H__
#घोषणा __MAX2175_H__

#घोषणा MAX2175_EU_XTAL_FREQ	36864000	/* In Hz */
#घोषणा MAX2175_NA_XTAL_FREQ	40186125	/* In Hz */

क्रमागत max2175_region अणु
	MAX2175_REGION_EU = 0,	/* Europe */
	MAX2175_REGION_NA,	/* North America */
पूर्ण;

क्रमागत max2175_band अणु
	MAX2175_BAND_AM = 0,
	MAX2175_BAND_FM,
	MAX2175_BAND_VHF,
	MAX2175_BAND_L,
पूर्ण;

क्रमागत max2175_eu_mode अणु
	/* EU modes */
	MAX2175_EU_FM_1_2 = 0,
	MAX2175_DAB_1_2,

	/*
	 * Other possible modes to add in future
	 * MAX2175_DAB_1_0,
	 * MAX2175_DAB_1_3,
	 * MAX2175_EU_FM_2_2,
	 * MAX2175_EU_FMHD_4_0,
	 * MAX2175_EU_AM_1_0,
	 * MAX2175_EU_AM_2_2,
	 */
पूर्ण;

क्रमागत max2175_na_mode अणु
	/* NA modes */
	MAX2175_NA_FM_1_0 = 0,
	MAX2175_NA_FM_2_0,

	/*
	 * Other possible modes to add in future
	 * MAX2175_NA_FMHD_1_0,
	 * MAX2175_NA_FMHD_1_2,
	 * MAX2175_NA_AM_1_0,
	 * MAX2175_NA_AM_1_2,
	 */
पूर्ण;

/* Supported I2S modes */
क्रमागत अणु
	MAX2175_I2S_MODE0 = 0,
	MAX2175_I2S_MODE1,
	MAX2175_I2S_MODE2,
	MAX2175_I2S_MODE3,
	MAX2175_I2S_MODE4,
पूर्ण;

/* Coefficient table groups */
क्रमागत अणु
	MAX2175_CH_MSEL = 0,
	MAX2175_EQ_MSEL,
	MAX2175_AA_MSEL,
पूर्ण;

/* HSLS LO injection polarity */
क्रमागत अणु
	MAX2175_LO_BELOW_DESIRED = 0,
	MAX2175_LO_ABOVE_DESIRED,
पूर्ण;

/* Channel FSM modes */
क्रमागत max2175_csm_mode अणु
	MAX2175_LOAD_TO_BUFFER = 0,
	MAX2175_PRESET_TUNE,
	MAX2175_SEARCH,
	MAX2175_AF_UPDATE,
	MAX2175_JUMP_FAST_TUNE,
	MAX2175_CHECK,
	MAX2175_LOAD_AND_SWAP,
	MAX2175_END,
	MAX2175_BUFFER_PLUS_PRESET_TUNE,
	MAX2175_BUFFER_PLUS_SEARCH,
	MAX2175_BUFFER_PLUS_AF_UPDATE,
	MAX2175_BUFFER_PLUS_JUMP_FAST_TUNE,
	MAX2175_BUFFER_PLUS_CHECK,
	MAX2175_BUFFER_PLUS_LOAD_AND_SWAP,
	MAX2175_NO_ACTION
पूर्ण;

#पूर्ण_अगर /* __MAX2175_H__ */
