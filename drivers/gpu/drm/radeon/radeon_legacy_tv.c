<शैली गुरु>
// SPDX-License-Identअगरier: MIT

#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_device.h>

#समावेश "radeon.h"

/*
 * Integrated TV out support based on the GATOS code by
 * Federico Ulivi <fulivi@lycos.com>
 */


/*
 * Limits of h/v positions (hPos & vPos)
 */
#घोषणा MAX_H_POSITION 5 /* Range: [-5..5], negative is on the left, 0 is शेष, positive is on the right */
#घोषणा MAX_V_POSITION 5 /* Range: [-5..5], negative is up, 0 is शेष, positive is करोwn */

/*
 * Unit क्रम hPos (in TV घड़ी periods)
 */
#घोषणा H_POS_UNIT 10

/*
 * Indexes in h. code timing table क्रम horizontal line position adjusपंचांगent
 */
#घोषणा H_TABLE_POS1 6
#घोषणा H_TABLE_POS2 8

/*
 * Limits of hor. size (hSize)
 */
#घोषणा MAX_H_SIZE 5 /* Range: [-5..5], negative is smaller, positive is larger */

/* tv standard स्थिरants */
#घोषणा NTSC_TV_CLOCK_T 233
#घोषणा NTSC_TV_VFTOTAL 1
#घोषणा NTSC_TV_LINES_PER_FRAME 525
#घोषणा NTSC_TV_ZERO_H_SIZE 479166
#घोषणा NTSC_TV_H_SIZE_UNIT 9478

#घोषणा PAL_TV_CLOCK_T 188
#घोषणा PAL_TV_VFTOTAL 3
#घोषणा PAL_TV_LINES_PER_FRAME 625
#घोषणा PAL_TV_ZERO_H_SIZE 473200
#घोषणा PAL_TV_H_SIZE_UNIT 9360

/* tv pll setting क्रम 27 mhz ref clk */
#घोषणा NTSC_TV_PLL_M_27 22
#घोषणा NTSC_TV_PLL_N_27 175
#घोषणा NTSC_TV_PLL_P_27 5

#घोषणा PAL_TV_PLL_M_27 113
#घोषणा PAL_TV_PLL_N_27 668
#घोषणा PAL_TV_PLL_P_27 3

/* tv pll setting क्रम 14 mhz ref clk */
#घोषणा NTSC_TV_PLL_M_14 33
#घोषणा NTSC_TV_PLL_N_14 693
#घोषणा NTSC_TV_PLL_P_14 7

#घोषणा PAL_TV_PLL_M_14 19
#घोषणा PAL_TV_PLL_N_14 353
#घोषणा PAL_TV_PLL_P_14 5

#घोषणा VERT_LEAD_IN_LINES 2
#घोषणा FRAC_BITS 0xe
#घोषणा FRAC_MASK 0x3fff

काष्ठा radeon_tv_mode_स्थिरants अणु
	uपूर्णांक16_t hor_resolution;
	uपूर्णांक16_t ver_resolution;
	क्रमागत radeon_tv_std standard;
	uपूर्णांक16_t hor_total;
	uपूर्णांक16_t ver_total;
	uपूर्णांक16_t hor_start;
	uपूर्णांक16_t hor_syncstart;
	uपूर्णांक16_t ver_syncstart;
	अचिन्हित def_restart;
	uपूर्णांक16_t crtcPLL_N;
	uपूर्णांक8_t  crtcPLL_M;
	uपूर्णांक8_t  crtcPLL_post_भाग;
	अचिन्हित pix_to_tv;
पूर्ण;

अटल स्थिर uपूर्णांक16_t hor_timing_NTSC[MAX_H_CODE_TIMING_LEN] = अणु
	0x0007,
	0x003f,
	0x0263,
	0x0a24,
	0x2a6b,
	0x0a36,
	0x126d, /* H_TABLE_POS1 */
	0x1bfe,
	0x1a8f, /* H_TABLE_POS2 */
	0x1ec7,
	0x3863,
	0x1bfe,
	0x1bfe,
	0x1a2a,
	0x1e95,
	0x0e31,
	0x201b,
	0
पूर्ण;

अटल स्थिर uपूर्णांक16_t vert_timing_NTSC[MAX_V_CODE_TIMING_LEN] = अणु
	0x2001,
	0x200d,
	0x1006,
	0x0c06,
	0x1006,
	0x1818,
	0x21e3,
	0x1006,
	0x0c06,
	0x1006,
	0x1817,
	0x21d4,
	0x0002,
	0
पूर्ण;

अटल स्थिर uपूर्णांक16_t hor_timing_PAL[MAX_H_CODE_TIMING_LEN] = अणु
	0x0007,
	0x0058,
	0x027c,
	0x0a31,
	0x2a77,
	0x0a95,
	0x124f, /* H_TABLE_POS1 */
	0x1bfe,
	0x1b22, /* H_TABLE_POS2 */
	0x1ef9,
	0x387c,
	0x1bfe,
	0x1bfe,
	0x1b31,
	0x1eb5,
	0x0e43,
	0x201b,
	0
पूर्ण;

अटल स्थिर uपूर्णांक16_t vert_timing_PAL[MAX_V_CODE_TIMING_LEN] = अणु
	0x2001,
	0x200c,
	0x1005,
	0x0c05,
	0x1005,
	0x1401,
	0x1821,
	0x2240,
	0x1005,
	0x0c05,
	0x1005,
	0x1401,
	0x1822,
	0x2230,
	0x0002,
	0
पूर्ण;

/**********************************************************************
 *
 * availableModes
 *
 * Table of all allowed modes क्रम tv output
 *
 **********************************************************************/
अटल स्थिर काष्ठा radeon_tv_mode_स्थिरants available_tv_modes[] = अणु
	अणु   /* NTSC timing क्रम 27 Mhz ref clk */
		800,                /* horResolution */
		600,                /* verResolution */
		TV_STD_NTSC,        /* standard */
		990,                /* horTotal */
		740,                /* verTotal */
		813,                /* horStart */
		824,                /* horSyncStart */
		632,                /* verSyncStart */
		625592,             /* defRestart */
		592,                /* crtcPLL_N */
		91,                 /* crtcPLL_M */
		4,                  /* crtcPLL_postDiv */
		1022,               /* pixToTV */
	पूर्ण,
	अणु   /* PAL timing क्रम 27 Mhz ref clk */
		800,               /* horResolution */
		600,               /* verResolution */
		TV_STD_PAL,        /* standard */
		1144,              /* horTotal */
		706,               /* verTotal */
		812,               /* horStart */
		824,               /* horSyncStart */
		669,               /* verSyncStart */
		696700,            /* defRestart */
		1382,              /* crtcPLL_N */
		231,               /* crtcPLL_M */
		4,                 /* crtcPLL_postDiv */
		759,               /* pixToTV */
	पूर्ण,
	अणु   /* NTSC timing क्रम 14 Mhz ref clk */
		800,                /* horResolution */
		600,                /* verResolution */
		TV_STD_NTSC,        /* standard */
		1018,               /* horTotal */
		727,                /* verTotal */
		813,                /* horStart */
		840,                /* horSyncStart */
		633,                /* verSyncStart */
		630627,             /* defRestart */
		347,                /* crtcPLL_N */
		14,                 /* crtcPLL_M */
		8,                  /* crtcPLL_postDiv */
		1022,               /* pixToTV */
	पूर्ण,
	अणु /* PAL timing क्रम 14 Mhz ref clk */
		800,                /* horResolution */
		600,                /* verResolution */
		TV_STD_PAL,         /* standard */
		1131,               /* horTotal */
		742,                /* verTotal */
		813,                /* horStart */
		840,                /* horSyncStart */
		633,                /* verSyncStart */
		708369,             /* defRestart */
		211,                /* crtcPLL_N */
		9,                  /* crtcPLL_M */
		8,                  /* crtcPLL_postDiv */
		759,                /* pixToTV */
	पूर्ण,
पूर्ण;

#घोषणा N_AVAILABLE_MODES ARRAY_SIZE(available_tv_modes)

अटल स्थिर काष्ठा radeon_tv_mode_स्थिरants *radeon_legacy_tv_get_std_mode(काष्ठा radeon_encoder *radeon_encoder,
									    uपूर्णांक16_t *pll_ref_freq)
अणु
	काष्ठा drm_device *dev = radeon_encoder->base.dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_crtc *radeon_crtc;
	काष्ठा radeon_encoder_tv_dac *tv_dac = radeon_encoder->enc_priv;
	स्थिर काष्ठा radeon_tv_mode_स्थिरants *स्थिर_ptr;
	काष्ठा radeon_pll *pll;

	radeon_crtc = to_radeon_crtc(radeon_encoder->base.crtc);
	अगर (radeon_crtc->crtc_id == 1)
		pll = &rdev->घड़ी.p2pll;
	अन्यथा
		pll = &rdev->घड़ी.p1pll;

	अगर (pll_ref_freq)
		*pll_ref_freq = pll->reference_freq;

	अगर (tv_dac->tv_std == TV_STD_NTSC ||
	    tv_dac->tv_std == TV_STD_NTSC_J ||
	    tv_dac->tv_std == TV_STD_PAL_M) अणु
		अगर (pll->reference_freq == 2700)
			स्थिर_ptr = &available_tv_modes[0];
		अन्यथा
			स्थिर_ptr = &available_tv_modes[2];
	पूर्ण अन्यथा अणु
		अगर (pll->reference_freq == 2700)
			स्थिर_ptr = &available_tv_modes[1];
		अन्यथा
			स्थिर_ptr = &available_tv_modes[3];
	पूर्ण
	वापस स्थिर_ptr;
पूर्ण

अटल दीर्घ YCOEF_value[5] = अणु 2, 2, 0, 4, 0 पूर्ण;
अटल दीर्घ YCOEF_EN_value[5] = अणु 1, 1, 0, 1, 0 पूर्ण;
अटल दीर्घ SLOPE_value[5] = अणु 1, 2, 2, 4, 8 पूर्ण;
अटल दीर्घ SLOPE_limit[5] = अणु 6, 5, 4, 3, 2 पूर्ण;

अटल व्योम radeon_रुको_pll_lock(काष्ठा drm_encoder *encoder, अचिन्हित n_tests,
				 अचिन्हित n_रुको_loops, अचिन्हित cnt_threshold)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	uपूर्णांक32_t save_pll_test;
	अचिन्हित पूर्णांक i, j;

	WREG32(RADEON_TEST_DEBUG_MUX, (RREG32(RADEON_TEST_DEBUG_MUX) & 0xffff60ff) | 0x100);
	save_pll_test = RREG32_PLL(RADEON_PLL_TEST_CNTL);
	WREG32_PLL(RADEON_PLL_TEST_CNTL, save_pll_test & ~RADEON_PLL_MASK_READ_B);

	WREG8(RADEON_CLOCK_CNTL_INDEX, RADEON_PLL_TEST_CNTL);
	क्रम (i = 0; i < n_tests; i++) अणु
		WREG8(RADEON_CLOCK_CNTL_DATA + 3, 0);
		क्रम (j = 0; j < n_रुको_loops; j++)
			अगर (RREG8(RADEON_CLOCK_CNTL_DATA + 3) >= cnt_threshold)
				अवरोध;
	पूर्ण
	WREG32_PLL(RADEON_PLL_TEST_CNTL, save_pll_test);
	WREG32(RADEON_TEST_DEBUG_MUX, RREG32(RADEON_TEST_DEBUG_MUX) & 0xffffe0ff);
पूर्ण


अटल व्योम radeon_legacy_tv_ग_लिखो_fअगरo(काष्ठा radeon_encoder *radeon_encoder,
					uपूर्णांक16_t addr, uपूर्णांक32_t value)
अणु
	काष्ठा drm_device *dev = radeon_encoder->base.dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	uपूर्णांक32_t पंचांगp;
	पूर्णांक i = 0;

	WREG32(RADEON_TV_HOST_WRITE_DATA, value);

	WREG32(RADEON_TV_HOST_RD_WT_CNTL, addr);
	WREG32(RADEON_TV_HOST_RD_WT_CNTL, addr | RADEON_HOST_FIFO_WT);

	करो अणु
		पंचांगp = RREG32(RADEON_TV_HOST_RD_WT_CNTL);
		अगर ((पंचांगp & RADEON_HOST_FIFO_WT_ACK) == 0)
			अवरोध;
		i++;
	पूर्ण जबतक (i < 10000);
	WREG32(RADEON_TV_HOST_RD_WT_CNTL, 0);
पूर्ण

#अगर 0 /* included क्रम completeness */
अटल uपूर्णांक32_t radeon_legacy_tv_पढ़ो_fअगरo(काष्ठा radeon_encoder *radeon_encoder, uपूर्णांक16_t addr)
अणु
	काष्ठा drm_device *dev = radeon_encoder->base.dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	uपूर्णांक32_t पंचांगp;
	पूर्णांक i = 0;

	WREG32(RADEON_TV_HOST_RD_WT_CNTL, addr);
	WREG32(RADEON_TV_HOST_RD_WT_CNTL, addr | RADEON_HOST_FIFO_RD);

	करो अणु
		पंचांगp = RREG32(RADEON_TV_HOST_RD_WT_CNTL);
		अगर ((पंचांगp & RADEON_HOST_FIFO_RD_ACK) == 0)
			अवरोध;
		i++;
	पूर्ण जबतक (i < 10000);
	WREG32(RADEON_TV_HOST_RD_WT_CNTL, 0);
	वापस RREG32(RADEON_TV_HOST_READ_DATA);
पूर्ण
#पूर्ण_अगर

अटल uपूर्णांक16_t radeon_get_htiming_tables_addr(uपूर्णांक32_t tv_uv_adr)
अणु
	uपूर्णांक16_t h_table;

	चयन ((tv_uv_adr & RADEON_HCODE_TABLE_SEL_MASK) >> RADEON_HCODE_TABLE_SEL_SHIFT) अणु
	हाल 0:
		h_table = RADEON_TV_MAX_FIFO_ADDR_INTERNAL;
		अवरोध;
	हाल 1:
		h_table = ((tv_uv_adr & RADEON_TABLE1_BOT_ADR_MASK) >> RADEON_TABLE1_BOT_ADR_SHIFT) * 2;
		अवरोध;
	हाल 2:
		h_table = ((tv_uv_adr & RADEON_TABLE3_TOP_ADR_MASK) >> RADEON_TABLE3_TOP_ADR_SHIFT) * 2;
		अवरोध;
	शेष:
		h_table = 0;
		अवरोध;
	पूर्ण
	वापस h_table;
पूर्ण

अटल uपूर्णांक16_t radeon_get_vtiming_tables_addr(uपूर्णांक32_t tv_uv_adr)
अणु
	uपूर्णांक16_t v_table;

	चयन ((tv_uv_adr & RADEON_VCODE_TABLE_SEL_MASK) >> RADEON_VCODE_TABLE_SEL_SHIFT) अणु
	हाल 0:
		v_table = ((tv_uv_adr & RADEON_MAX_UV_ADR_MASK) >> RADEON_MAX_UV_ADR_SHIFT) * 2 + 1;
		अवरोध;
	हाल 1:
		v_table = ((tv_uv_adr & RADEON_TABLE1_BOT_ADR_MASK) >> RADEON_TABLE1_BOT_ADR_SHIFT) * 2 + 1;
		अवरोध;
	हाल 2:
		v_table = ((tv_uv_adr & RADEON_TABLE3_TOP_ADR_MASK) >> RADEON_TABLE3_TOP_ADR_SHIFT) * 2 + 1;
		अवरोध;
	शेष:
		v_table = 0;
		अवरोध;
	पूर्ण
	वापस v_table;
पूर्ण

अटल व्योम radeon_restore_tv_timing_tables(काष्ठा radeon_encoder *radeon_encoder)
अणु
	काष्ठा drm_device *dev = radeon_encoder->base.dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder_tv_dac *tv_dac = radeon_encoder->enc_priv;
	uपूर्णांक16_t h_table, v_table;
	uपूर्णांक32_t पंचांगp;
	पूर्णांक i;

	WREG32(RADEON_TV_UV_ADR, tv_dac->tv.tv_uv_adr);
	h_table = radeon_get_htiming_tables_addr(tv_dac->tv.tv_uv_adr);
	v_table = radeon_get_vtiming_tables_addr(tv_dac->tv.tv_uv_adr);

	क्रम (i = 0; i < MAX_H_CODE_TIMING_LEN; i += 2, h_table--) अणु
		पंचांगp = ((uपूर्णांक32_t)tv_dac->tv.h_code_timing[i] << 14) | ((uपूर्णांक32_t)tv_dac->tv.h_code_timing[i+1]);
		radeon_legacy_tv_ग_लिखो_fअगरo(radeon_encoder, h_table, पंचांगp);
		अगर (tv_dac->tv.h_code_timing[i] == 0 || tv_dac->tv.h_code_timing[i + 1] == 0)
			अवरोध;
	पूर्ण
	क्रम (i = 0; i < MAX_V_CODE_TIMING_LEN; i += 2, v_table++) अणु
		पंचांगp = ((uपूर्णांक32_t)tv_dac->tv.v_code_timing[i+1] << 14) | ((uपूर्णांक32_t)tv_dac->tv.v_code_timing[i]);
		radeon_legacy_tv_ग_लिखो_fअगरo(radeon_encoder, v_table, पंचांगp);
		अगर (tv_dac->tv.v_code_timing[i] == 0 || tv_dac->tv.v_code_timing[i + 1] == 0)
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम radeon_legacy_ग_लिखो_tv_restarts(काष्ठा radeon_encoder *radeon_encoder)
अणु
	काष्ठा drm_device *dev = radeon_encoder->base.dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder_tv_dac *tv_dac = radeon_encoder->enc_priv;
	WREG32(RADEON_TV_FRESTART, tv_dac->tv.frestart);
	WREG32(RADEON_TV_HRESTART, tv_dac->tv.hrestart);
	WREG32(RADEON_TV_VRESTART, tv_dac->tv.vrestart);
पूर्ण

अटल bool radeon_legacy_tv_init_restarts(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_encoder_tv_dac *tv_dac = radeon_encoder->enc_priv;
	पूर्णांक restart;
	अचिन्हित पूर्णांक h_total, v_total, f_total;
	पूर्णांक v_offset, h_offset;
	u16 p1, p2, h_inc;
	bool h_changed;
	स्थिर काष्ठा radeon_tv_mode_स्थिरants *स्थिर_ptr;

	स्थिर_ptr = radeon_legacy_tv_get_std_mode(radeon_encoder, शून्य);
	अगर (!स्थिर_ptr)
		वापस false;

	h_total = स्थिर_ptr->hor_total;
	v_total = स्थिर_ptr->ver_total;

	अगर (tv_dac->tv_std == TV_STD_NTSC ||
	    tv_dac->tv_std == TV_STD_NTSC_J ||
	    tv_dac->tv_std == TV_STD_PAL_M ||
	    tv_dac->tv_std == TV_STD_PAL_60)
		f_total = NTSC_TV_VFTOTAL + 1;
	अन्यथा
		f_total = PAL_TV_VFTOTAL + 1;

	/* adjust positions 1&2 in hor. cod timing table */
	h_offset = tv_dac->h_pos * H_POS_UNIT;

	अगर (tv_dac->tv_std == TV_STD_NTSC ||
	    tv_dac->tv_std == TV_STD_NTSC_J ||
	    tv_dac->tv_std == TV_STD_PAL_M) अणु
		h_offset -= 50;
		p1 = hor_timing_NTSC[H_TABLE_POS1];
		p2 = hor_timing_NTSC[H_TABLE_POS2];
	पूर्ण अन्यथा अणु
		p1 = hor_timing_PAL[H_TABLE_POS1];
		p2 = hor_timing_PAL[H_TABLE_POS2];
	पूर्ण

	p1 = (u16)((पूर्णांक)p1 + h_offset);
	p2 = (u16)((पूर्णांक)p2 - h_offset);

	h_changed = (p1 != tv_dac->tv.h_code_timing[H_TABLE_POS1] ||
		     p2 != tv_dac->tv.h_code_timing[H_TABLE_POS2]);

	tv_dac->tv.h_code_timing[H_TABLE_POS1] = p1;
	tv_dac->tv.h_code_timing[H_TABLE_POS2] = p2;

	/* Convert hOffset from n. of TV घड़ी periods to n. of CRTC घड़ी periods (CRTC pixels) */
	h_offset = (h_offset * (पूर्णांक)(स्थिर_ptr->pix_to_tv)) / 1000;

	/* adjust restart */
	restart = स्थिर_ptr->def_restart;

	/*
	 * convert v_pos TV lines to n. of CRTC pixels
	 */
	अगर (tv_dac->tv_std == TV_STD_NTSC ||
	    tv_dac->tv_std == TV_STD_NTSC_J ||
	    tv_dac->tv_std == TV_STD_PAL_M ||
	    tv_dac->tv_std == TV_STD_PAL_60)
		v_offset = ((पूर्णांक)(v_total * h_total) * 2 * tv_dac->v_pos) / (पूर्णांक)(NTSC_TV_LINES_PER_FRAME);
	अन्यथा
		v_offset = ((पूर्णांक)(v_total * h_total) * 2 * tv_dac->v_pos) / (पूर्णांक)(PAL_TV_LINES_PER_FRAME);

	restart -= v_offset + h_offset;

	DRM_DEBUG_KMS("compute_restarts: def = %u h = %d v = %d, p1 = %04x, p2 = %04x, restart = %d\n",
		  स्थिर_ptr->def_restart, tv_dac->h_pos, tv_dac->v_pos, p1, p2, restart);

	tv_dac->tv.hrestart = restart % h_total;
	restart /= h_total;
	tv_dac->tv.vrestart = restart % v_total;
	restart /= v_total;
	tv_dac->tv.frestart = restart % f_total;

	DRM_DEBUG_KMS("compute_restart: F/H/V=%u,%u,%u\n",
		  (अचिन्हित)tv_dac->tv.frestart,
		  (अचिन्हित)tv_dac->tv.vrestart,
		  (अचिन्हित)tv_dac->tv.hrestart);

	/* compute h_inc from hsize */
	अगर (tv_dac->tv_std == TV_STD_NTSC ||
	    tv_dac->tv_std == TV_STD_NTSC_J ||
	    tv_dac->tv_std == TV_STD_PAL_M)
		h_inc = (u16)((पूर्णांक)(स्थिर_ptr->hor_resolution * 4096 * NTSC_TV_CLOCK_T) /
			      (tv_dac->h_size * (पूर्णांक)(NTSC_TV_H_SIZE_UNIT) + (पूर्णांक)(NTSC_TV_ZERO_H_SIZE)));
	अन्यथा
		h_inc = (u16)((पूर्णांक)(स्थिर_ptr->hor_resolution * 4096 * PAL_TV_CLOCK_T) /
			      (tv_dac->h_size * (पूर्णांक)(PAL_TV_H_SIZE_UNIT) + (पूर्णांक)(PAL_TV_ZERO_H_SIZE)));

	tv_dac->tv.timing_cntl = (tv_dac->tv.timing_cntl & ~RADEON_H_INC_MASK) |
		((u32)h_inc << RADEON_H_INC_SHIFT);

	DRM_DEBUG_KMS("compute_restart: h_size = %d h_inc = %d\n", tv_dac->h_size, h_inc);

	वापस h_changed;
पूर्ण

व्योम radeon_legacy_tv_mode_set(काष्ठा drm_encoder *encoder,
			       काष्ठा drm_display_mode *mode,
			       काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_encoder_tv_dac *tv_dac = radeon_encoder->enc_priv;
	स्थिर काष्ठा radeon_tv_mode_स्थिरants *स्थिर_ptr;
	काष्ठा radeon_crtc *radeon_crtc;
	पूर्णांक i;
	uपूर्णांक16_t pll_ref_freq;
	uपूर्णांक32_t vert_space, flicker_removal, पंचांगp;
	uपूर्णांक32_t tv_master_cntl, tv_rgb_cntl, tv_dac_cntl;
	uपूर्णांक32_t tv_modulator_cntl1, tv_modulator_cntl2;
	uपूर्णांक32_t tv_vscaler_cntl1, tv_vscaler_cntl2;
	uपूर्णांक32_t tv_pll_cntl, tv_ftotal;
	uपूर्णांक32_t tv_y_fall_cntl, tv_y_rise_cntl, tv_y_saw_tooth_cntl;
	uपूर्णांक32_t m, n, p;
	स्थिर uपूर्णांक16_t *hor_timing;
	स्थिर uपूर्णांक16_t *vert_timing;

	स्थिर_ptr = radeon_legacy_tv_get_std_mode(radeon_encoder, &pll_ref_freq);
	अगर (!स्थिर_ptr)
		वापस;

	radeon_crtc = to_radeon_crtc(encoder->crtc);

	tv_master_cntl = (RADEON_VIN_ASYNC_RST |
			  RADEON_CRT_FIFO_CE_EN |
			  RADEON_TV_FIFO_CE_EN |
			  RADEON_TV_ON);

	अगर (!ASIC_IS_R300(rdev))
		tv_master_cntl |= RADEON_TVCLK_ALWAYS_ONb;

	अगर (tv_dac->tv_std == TV_STD_NTSC ||
	    tv_dac->tv_std == TV_STD_NTSC_J)
		tv_master_cntl |= RADEON_RESTART_PHASE_FIX;

	tv_modulator_cntl1 = (RADEON_SLEW_RATE_LIMIT |
			      RADEON_SYNC_TIP_LEVEL |
			      RADEON_YFLT_EN |
			      RADEON_UVFLT_EN |
			      (6 << RADEON_CY_FILT_BLEND_SHIFT));

	अगर (tv_dac->tv_std == TV_STD_NTSC ||
	    tv_dac->tv_std == TV_STD_NTSC_J) अणु
		tv_modulator_cntl1 |= (0x46 << RADEON_SET_UP_LEVEL_SHIFT) |
			(0x3b << RADEON_BLANK_LEVEL_SHIFT);
		tv_modulator_cntl2 = (-111 & RADEON_TV_U_BURST_LEVEL_MASK) |
			((0 & RADEON_TV_V_BURST_LEVEL_MASK) << RADEON_TV_V_BURST_LEVEL_SHIFT);
	पूर्ण अन्यथा अगर (tv_dac->tv_std == TV_STD_SCART_PAL) अणु
		tv_modulator_cntl1 |= RADEON_ALT_PHASE_EN;
		tv_modulator_cntl2 = (0 & RADEON_TV_U_BURST_LEVEL_MASK) |
			((0 & RADEON_TV_V_BURST_LEVEL_MASK) << RADEON_TV_V_BURST_LEVEL_SHIFT);
	पूर्ण अन्यथा अणु
		tv_modulator_cntl1 |= RADEON_ALT_PHASE_EN |
			(0x3b << RADEON_SET_UP_LEVEL_SHIFT) |
			(0x3b << RADEON_BLANK_LEVEL_SHIFT);
		tv_modulator_cntl2 = (-78 & RADEON_TV_U_BURST_LEVEL_MASK) |
			((62 & RADEON_TV_V_BURST_LEVEL_MASK) << RADEON_TV_V_BURST_LEVEL_SHIFT);
	पूर्ण


	tv_rgb_cntl = (RADEON_RGB_DITHER_EN
		       | RADEON_TVOUT_SCALE_EN
		       | (0x0b << RADEON_UVRAM_READ_MARGIN_SHIFT)
		       | (0x07 << RADEON_FIFORAM_FFMACRO_READ_MARGIN_SHIFT)
		       | RADEON_RGB_ATTEN_SEL(0x3)
		       | RADEON_RGB_ATTEN_VAL(0xc));

	अगर (radeon_crtc->crtc_id == 1)
		tv_rgb_cntl |= RADEON_RGB_SRC_SEL_CRTC2;
	अन्यथा अणु
		अगर (radeon_crtc->rmx_type != RMX_OFF)
			tv_rgb_cntl |= RADEON_RGB_SRC_SEL_RMX;
		अन्यथा
			tv_rgb_cntl |= RADEON_RGB_SRC_SEL_CRTC1;
	पूर्ण

	अगर (tv_dac->tv_std == TV_STD_NTSC ||
	    tv_dac->tv_std == TV_STD_NTSC_J ||
	    tv_dac->tv_std == TV_STD_PAL_M ||
	    tv_dac->tv_std == TV_STD_PAL_60)
		vert_space = स्थिर_ptr->ver_total * 2 * 10000 / NTSC_TV_LINES_PER_FRAME;
	अन्यथा
		vert_space = स्थिर_ptr->ver_total * 2 * 10000 / PAL_TV_LINES_PER_FRAME;

	पंचांगp = RREG32(RADEON_TV_VSCALER_CNTL1);
	पंचांगp &= 0xe3ff0000;
	पंचांगp |= (vert_space * (1 << FRAC_BITS) / 10000);
	tv_vscaler_cntl1 = पंचांगp;

	अगर (pll_ref_freq == 2700)
		tv_vscaler_cntl1 |= RADEON_RESTART_FIELD;

	अगर (स्थिर_ptr->hor_resolution == 1024)
		tv_vscaler_cntl1 |= (4 << RADEON_Y_DEL_W_SIG_SHIFT);
	अन्यथा
		tv_vscaler_cntl1 |= (2 << RADEON_Y_DEL_W_SIG_SHIFT);

	/* scale up क्रम पूर्णांक भागide */
	पंचांगp = स्थिर_ptr->ver_total * 2 * 1000;
	अगर (tv_dac->tv_std == TV_STD_NTSC ||
	    tv_dac->tv_std == TV_STD_NTSC_J ||
	    tv_dac->tv_std == TV_STD_PAL_M ||
	    tv_dac->tv_std == TV_STD_PAL_60) अणु
		पंचांगp /= NTSC_TV_LINES_PER_FRAME;
	पूर्ण अन्यथा अणु
		पंचांगp /= PAL_TV_LINES_PER_FRAME;
	पूर्ण
	flicker_removal = (पंचांगp + 500) / 1000;

	अगर (flicker_removal < 3)
		flicker_removal = 3;
	क्रम (i = 0; i < ARRAY_SIZE(SLOPE_limit); ++i) अणु
		अगर (flicker_removal == SLOPE_limit[i])
			अवरोध;
	पूर्ण

	tv_y_saw_tooth_cntl = (vert_space * SLOPE_value[i] * (1 << (FRAC_BITS - 1)) +
				5001) / 10000 / 8 | ((SLOPE_value[i] *
				(1 << (FRAC_BITS - 1)) / 8) << 16);
	tv_y_fall_cntl =
		(YCOEF_EN_value[i] << 17) | ((YCOEF_value[i] * (1 << 8) / 8) << 24) |
		RADEON_Y_FALL_PING_PONG | (272 * SLOPE_value[i] / 8) * (1 << (FRAC_BITS - 1)) /
		1024;
	tv_y_rise_cntl = RADEON_Y_RISE_PING_PONG|
		(flicker_removal * 1024 - 272) * SLOPE_value[i] / 8 * (1 << (FRAC_BITS - 1)) / 1024;

	tv_vscaler_cntl2 = RREG32(RADEON_TV_VSCALER_CNTL2) & 0x00fffff0;
	tv_vscaler_cntl2 |= (0x10 << 24) |
		RADEON_DITHER_MODE |
		RADEON_Y_OUTPUT_DITHER_EN |
		RADEON_UV_OUTPUT_DITHER_EN |
		RADEON_UV_TO_BUF_DITHER_EN;

	पंचांगp = (tv_vscaler_cntl1 >> RADEON_UV_INC_SHIFT) & RADEON_UV_INC_MASK;
	पंचांगp = ((16384 * 256 * 10) / पंचांगp + 5) / 10;
	पंचांगp = (पंचांगp << RADEON_UV_OUTPUT_POST_SCALE_SHIFT) | 0x000b0000;
	tv_dac->tv.timing_cntl = पंचांगp;

	अगर (tv_dac->tv_std == TV_STD_NTSC ||
	    tv_dac->tv_std == TV_STD_NTSC_J ||
	    tv_dac->tv_std == TV_STD_PAL_M ||
	    tv_dac->tv_std == TV_STD_PAL_60)
		tv_dac_cntl = tv_dac->ntsc_tvdac_adj;
	अन्यथा
		tv_dac_cntl = tv_dac->pal_tvdac_adj;

	tv_dac_cntl |= RADEON_TV_DAC_NBLANK | RADEON_TV_DAC_NHOLD;

	अगर (tv_dac->tv_std == TV_STD_NTSC ||
	    tv_dac->tv_std == TV_STD_NTSC_J)
		tv_dac_cntl |= RADEON_TV_DAC_STD_NTSC;
	अन्यथा
		tv_dac_cntl |= RADEON_TV_DAC_STD_PAL;

	अगर (tv_dac->tv_std == TV_STD_NTSC ||
	    tv_dac->tv_std == TV_STD_NTSC_J) अणु
		अगर (pll_ref_freq == 2700) अणु
			m = NTSC_TV_PLL_M_27;
			n = NTSC_TV_PLL_N_27;
			p = NTSC_TV_PLL_P_27;
		पूर्ण अन्यथा अणु
			m = NTSC_TV_PLL_M_14;
			n = NTSC_TV_PLL_N_14;
			p = NTSC_TV_PLL_P_14;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (pll_ref_freq == 2700) अणु
			m = PAL_TV_PLL_M_27;
			n = PAL_TV_PLL_N_27;
			p = PAL_TV_PLL_P_27;
		पूर्ण अन्यथा अणु
			m = PAL_TV_PLL_M_14;
			n = PAL_TV_PLL_N_14;
			p = PAL_TV_PLL_P_14;
		पूर्ण
	पूर्ण

	tv_pll_cntl = (m & RADEON_TV_M0LO_MASK) |
		(((m >> 8) & RADEON_TV_M0HI_MASK) << RADEON_TV_M0HI_SHIFT) |
		((n & RADEON_TV_N0LO_MASK) << RADEON_TV_N0LO_SHIFT) |
		(((n >> 9) & RADEON_TV_N0HI_MASK) << RADEON_TV_N0HI_SHIFT) |
		((p & RADEON_TV_P_MASK) << RADEON_TV_P_SHIFT);

	tv_dac->tv.tv_uv_adr = 0xc8;

	अगर (tv_dac->tv_std == TV_STD_NTSC ||
	    tv_dac->tv_std == TV_STD_NTSC_J ||
	    tv_dac->tv_std == TV_STD_PAL_M ||
	    tv_dac->tv_std == TV_STD_PAL_60) अणु
		tv_ftotal = NTSC_TV_VFTOTAL;
		hor_timing = hor_timing_NTSC;
		vert_timing = vert_timing_NTSC;
	पूर्ण अन्यथा अणु
		hor_timing = hor_timing_PAL;
		vert_timing = vert_timing_PAL;
		tv_ftotal = PAL_TV_VFTOTAL;
	पूर्ण

	क्रम (i = 0; i < MAX_H_CODE_TIMING_LEN; i++) अणु
		अगर ((tv_dac->tv.h_code_timing[i] = hor_timing[i]) == 0)
			अवरोध;
	पूर्ण

	क्रम (i = 0; i < MAX_V_CODE_TIMING_LEN; i++) अणु
		अगर ((tv_dac->tv.v_code_timing[i] = vert_timing[i]) == 0)
			अवरोध;
	पूर्ण

	radeon_legacy_tv_init_restarts(encoder);

	/* play with DAC_CNTL */
	/* play with GPIOPAD_A */
	/* DISP_OUTPUT_CNTL */
	/* use reference freq */

	/* program the TV रेजिस्टरs */
	WREG32(RADEON_TV_MASTER_CNTL, (tv_master_cntl | RADEON_TV_ASYNC_RST |
				       RADEON_CRT_ASYNC_RST | RADEON_TV_FIFO_ASYNC_RST));

	पंचांगp = RREG32(RADEON_TV_DAC_CNTL);
	पंचांगp &= ~RADEON_TV_DAC_NBLANK;
	पंचांगp |= RADEON_TV_DAC_BGSLEEP |
		RADEON_TV_DAC_RDACPD |
		RADEON_TV_DAC_GDACPD |
		RADEON_TV_DAC_BDACPD;
	WREG32(RADEON_TV_DAC_CNTL, पंचांगp);

	/* TV PLL */
	WREG32_PLL_P(RADEON_TV_PLL_CNTL1, 0, ~RADEON_TVCLK_SRC_SEL_TVPLL);
	WREG32_PLL(RADEON_TV_PLL_CNTL, tv_pll_cntl);
	WREG32_PLL_P(RADEON_TV_PLL_CNTL1, RADEON_TVPLL_RESET, ~RADEON_TVPLL_RESET);

	radeon_रुको_pll_lock(encoder, 200, 800, 135);

	WREG32_PLL_P(RADEON_TV_PLL_CNTL1, 0, ~RADEON_TVPLL_RESET);

	radeon_रुको_pll_lock(encoder, 300, 160, 27);
	radeon_रुको_pll_lock(encoder, 200, 800, 135);

	WREG32_PLL_P(RADEON_TV_PLL_CNTL1, 0, ~0xf);
	WREG32_PLL_P(RADEON_TV_PLL_CNTL1, RADEON_TVCLK_SRC_SEL_TVPLL, ~RADEON_TVCLK_SRC_SEL_TVPLL);

	WREG32_PLL_P(RADEON_TV_PLL_CNTL1, (1 << RADEON_TVPDC_SHIFT), ~RADEON_TVPDC_MASK);
	WREG32_PLL_P(RADEON_TV_PLL_CNTL1, 0, ~RADEON_TVPLL_SLEEP);

	/* TV HV */
	WREG32(RADEON_TV_RGB_CNTL, tv_rgb_cntl);
	WREG32(RADEON_TV_HTOTAL, स्थिर_ptr->hor_total - 1);
	WREG32(RADEON_TV_HDISP, स्थिर_ptr->hor_resolution - 1);
	WREG32(RADEON_TV_HSTART, स्थिर_ptr->hor_start);

	WREG32(RADEON_TV_VTOTAL, स्थिर_ptr->ver_total - 1);
	WREG32(RADEON_TV_VDISP, स्थिर_ptr->ver_resolution - 1);
	WREG32(RADEON_TV_FTOTAL, tv_ftotal);
	WREG32(RADEON_TV_VSCALER_CNTL1, tv_vscaler_cntl1);
	WREG32(RADEON_TV_VSCALER_CNTL2, tv_vscaler_cntl2);

	WREG32(RADEON_TV_Y_FALL_CNTL, tv_y_fall_cntl);
	WREG32(RADEON_TV_Y_RISE_CNTL, tv_y_rise_cntl);
	WREG32(RADEON_TV_Y_SAW_TOOTH_CNTL, tv_y_saw_tooth_cntl);

	WREG32(RADEON_TV_MASTER_CNTL, (tv_master_cntl | RADEON_TV_ASYNC_RST |
				       RADEON_CRT_ASYNC_RST));

	/* TV restarts */
	radeon_legacy_ग_लिखो_tv_restarts(radeon_encoder);

	/* tv timings */
	radeon_restore_tv_timing_tables(radeon_encoder);

	WREG32(RADEON_TV_MASTER_CNTL, (tv_master_cntl | RADEON_TV_ASYNC_RST));

	/* tv std */
	WREG32(RADEON_TV_SYNC_CNTL, (RADEON_SYNC_PUB | RADEON_TV_SYNC_IO_DRIVE));
	WREG32(RADEON_TV_TIMING_CNTL, tv_dac->tv.timing_cntl);
	WREG32(RADEON_TV_MODULATOR_CNTL1, tv_modulator_cntl1);
	WREG32(RADEON_TV_MODULATOR_CNTL2, tv_modulator_cntl2);
	WREG32(RADEON_TV_PRE_DAC_MUX_CNTL, (RADEON_Y_RED_EN |
					    RADEON_C_GRN_EN |
					    RADEON_CMP_BLU_EN |
					    RADEON_DAC_DITHER_EN));

	WREG32(RADEON_TV_CRC_CNTL, 0);

	WREG32(RADEON_TV_MASTER_CNTL, tv_master_cntl);

	WREG32(RADEON_TV_GAIN_LIMIT_SETTINGS, ((0x17f << RADEON_UV_GAIN_LIMIT_SHIFT) |
					       (0x5ff << RADEON_Y_GAIN_LIMIT_SHIFT)));
	WREG32(RADEON_TV_LINEAR_GAIN_SETTINGS, ((0x100 << RADEON_UV_GAIN_SHIFT) |
						(0x100 << RADEON_Y_GAIN_SHIFT)));

	WREG32(RADEON_TV_DAC_CNTL, tv_dac_cntl);

पूर्ण

व्योम radeon_legacy_tv_adjust_crtc_reg(काष्ठा drm_encoder *encoder,
				      uपूर्णांक32_t *h_total_disp, uपूर्णांक32_t *h_sync_strt_wid,
				      uपूर्णांक32_t *v_total_disp, uपूर्णांक32_t *v_sync_strt_wid)
अणु
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	स्थिर काष्ठा radeon_tv_mode_स्थिरants *स्थिर_ptr;
	uपूर्णांक32_t पंचांगp;

	स्थिर_ptr = radeon_legacy_tv_get_std_mode(radeon_encoder, शून्य);
	अगर (!स्थिर_ptr)
		वापस;

	*h_total_disp = (((स्थिर_ptr->hor_resolution / 8) - 1) << RADEON_CRTC_H_DISP_SHIFT) |
		(((स्थिर_ptr->hor_total / 8) - 1) << RADEON_CRTC_H_TOTAL_SHIFT);

	पंचांगp = *h_sync_strt_wid;
	पंचांगp &= ~(RADEON_CRTC_H_SYNC_STRT_PIX | RADEON_CRTC_H_SYNC_STRT_CHAR);
	पंचांगp |= (((स्थिर_ptr->hor_syncstart / 8) - 1) << RADEON_CRTC_H_SYNC_STRT_CHAR_SHIFT) |
		(स्थिर_ptr->hor_syncstart & 7);
	*h_sync_strt_wid = पंचांगp;

	*v_total_disp = ((स्थिर_ptr->ver_resolution - 1) << RADEON_CRTC_V_DISP_SHIFT) |
		((स्थिर_ptr->ver_total - 1) << RADEON_CRTC_V_TOTAL_SHIFT);

	पंचांगp = *v_sync_strt_wid;
	पंचांगp &= ~RADEON_CRTC_V_SYNC_STRT;
	पंचांगp |= ((स्थिर_ptr->ver_syncstart - 1) << RADEON_CRTC_V_SYNC_STRT_SHIFT);
	*v_sync_strt_wid = पंचांगp;
पूर्ण

अटल पूर्णांक get_post_भाग(पूर्णांक value)
अणु
	पूर्णांक post_भाग;
	चयन (value) अणु
	हाल 1: post_भाग = 0; अवरोध;
	हाल 2: post_भाग = 1; अवरोध;
	हाल 3: post_भाग = 4; अवरोध;
	हाल 4: post_भाग = 2; अवरोध;
	हाल 6: post_भाग = 6; अवरोध;
	हाल 8: post_भाग = 3; अवरोध;
	हाल 12: post_भाग = 7; अवरोध;
	हाल 16:
	शेष: post_भाग = 5; अवरोध;
	पूर्ण
	वापस post_भाग;
पूर्ण

व्योम radeon_legacy_tv_adjust_pll1(काष्ठा drm_encoder *encoder,
				  uपूर्णांक32_t *htotal_cntl, uपूर्णांक32_t *ppll_ref_भाग,
				  uपूर्णांक32_t *ppll_भाग_3, uपूर्णांक32_t *pixclks_cntl)
अणु
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	स्थिर काष्ठा radeon_tv_mode_स्थिरants *स्थिर_ptr;

	स्थिर_ptr = radeon_legacy_tv_get_std_mode(radeon_encoder, शून्य);
	अगर (!स्थिर_ptr)
		वापस;

	*htotal_cntl = (स्थिर_ptr->hor_total & 0x7) | RADEON_HTOT_CNTL_VGA_EN;

	*ppll_ref_भाग = स्थिर_ptr->crtcPLL_M;

	*ppll_भाग_3 = (स्थिर_ptr->crtcPLL_N & 0x7ff) | (get_post_भाग(स्थिर_ptr->crtcPLL_post_भाग) << 16);
	*pixclks_cntl &= ~(RADEON_PIX2CLK_SRC_SEL_MASK | RADEON_PIXCLK_TV_SRC_SEL);
	*pixclks_cntl |= RADEON_PIX2CLK_SRC_SEL_P2PLLCLK;
पूर्ण

व्योम radeon_legacy_tv_adjust_pll2(काष्ठा drm_encoder *encoder,
				  uपूर्णांक32_t *htotal2_cntl, uपूर्णांक32_t *p2pll_ref_भाग,
				  uपूर्णांक32_t *p2pll_भाग_0, uपूर्णांक32_t *pixclks_cntl)
अणु
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	स्थिर काष्ठा radeon_tv_mode_स्थिरants *स्थिर_ptr;

	स्थिर_ptr = radeon_legacy_tv_get_std_mode(radeon_encoder, शून्य);
	अगर (!स्थिर_ptr)
		वापस;

	*htotal2_cntl = (स्थिर_ptr->hor_total & 0x7);

	*p2pll_ref_भाग = स्थिर_ptr->crtcPLL_M;

	*p2pll_भाग_0 = (स्थिर_ptr->crtcPLL_N & 0x7ff) | (get_post_भाग(स्थिर_ptr->crtcPLL_post_भाग) << 16);
	*pixclks_cntl &= ~RADEON_PIX2CLK_SRC_SEL_MASK;
	*pixclks_cntl |= RADEON_PIX2CLK_SRC_SEL_P2PLLCLK | RADEON_PIXCLK_TV_SRC_SEL;
पूर्ण

