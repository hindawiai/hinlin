<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#अगर_अघोषित __PIXELGEN_GLOBAL_H_INCLUDED__
#घोषणा __PIXELGEN_GLOBAL_H_INCLUDED__

#समावेश <type_support.h>

/**
 * Pixel-generator. ("pixelgen_global.h")
 */
/*
 * Duplicates "sync_generator_cfg_t" in "input_system_global.h".
 */
प्रकार काष्ठा isp2401_sync_generator_cfg_s isp2401_sync_generator_cfg_t;
काष्ठा isp2401_sync_generator_cfg_s अणु
	u32	hblank_cycles;
	u32	vblank_cycles;
	u32	pixels_per_घड़ी;
	u32	nr_of_frames;
	u32	pixels_per_line;
	u32	lines_per_frame;
पूर्ण;

प्रकार क्रमागत अणु
	PIXELGEN_TPG_MODE_RAMP = 0,
	PIXELGEN_TPG_MODE_CHBO,
	PIXELGEN_TPG_MODE_MONO,
	N_PIXELGEN_TPG_MODE
पूर्ण pixelgen_tpg_mode_t;

/*
 * "pixelgen_tpg_cfg_t" duplicates parts of
 * "tpg_cfg_t" in "input_system_global.h".
 */
प्रकार काष्ठा pixelgen_tpg_cfg_s pixelgen_tpg_cfg_t;
काष्ठा pixelgen_tpg_cfg_s अणु
	pixelgen_tpg_mode_t	mode;	/* CHBO, MONO */

	काष्ठा अणु
		/* be used by CHBO and MON */
		u32 R1;
		u32 G1;
		u32 B1;

		/* be used by CHBO only */
		u32 R2;
		u32 G2;
		u32 B2;
	पूर्ण color_cfg;

	काष्ठा अणु
		u32	h_mask;		/* horizontal mask */
		u32	v_mask;		/* vertical mask */
		u32	hv_mask;	/* horizontal+vertical mask? */
	पूर्ण mask_cfg;

	काष्ठा अणु
		s32	h_delta;	/* horizontal delta? */
		s32	v_delta;	/* vertical delta? */
	पूर्ण delta_cfg;

	isp2401_sync_generator_cfg_t	 sync_gen_cfg;
पूर्ण;

/*
 * "pixelgen_prbs_cfg_t" duplicates parts of
 * prbs_cfg_t" in "input_प्रणाली_global.h".
 */
प्रकार काष्ठा pixelgen_prbs_cfg_s pixelgen_prbs_cfg_t;
काष्ठा pixelgen_prbs_cfg_s अणु
	s32	seed0;
	s32	seed1;

	isp2401_sync_generator_cfg_t	sync_gen_cfg;
पूर्ण;

/* end of Pixel-generator: TPG. ("pixelgen_global.h") */
#पूर्ण_अगर /* __PIXELGEN_GLOBAL_H_INCLUDED__ */
