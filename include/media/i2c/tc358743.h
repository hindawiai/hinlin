<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * tc358743 - Toshiba HDMI to CSI-2 bridge
 *
 * Copyright 2015 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

/*
 * References (c = chapter, p = page):
 * REF_01 - Toshiba, TC358743XBG (H2C), Functional Specअगरication, Rev 0.60
 * REF_02 - Toshiba, TC358743XBG_HDMI-CSI_Tv11p_nm.xls
 */

#अगर_अघोषित _TC358743_
#घोषणा _TC358743_

क्रमागत tc358743_ddc5v_delays अणु
	DDC5V_DELAY_0_MS,
	DDC5V_DELAY_50_MS,
	DDC5V_DELAY_100_MS,
	DDC5V_DELAY_200_MS,
पूर्ण;

क्रमागत tc358743_hdmi_detection_delay अणु
	HDMI_MODE_DELAY_0_MS,
	HDMI_MODE_DELAY_25_MS,
	HDMI_MODE_DELAY_50_MS,
	HDMI_MODE_DELAY_100_MS,
पूर्ण;

काष्ठा tc358743_platक्रमm_data अणु
	/* System घड़ी connected to REFCLK (pin H5) */
	u32 refclk_hz; /* 26 MHz, 27 MHz or 42 MHz */

	/* DDC +5V debounce delay to aव्योम spurious पूर्णांकerrupts when the cable
	 * is connected.
	 * Sets DDC5V_MODE in रेजिस्टर DDC_CTL.
	 * Default: DDC5V_DELAY_0_MS
	 */
	क्रमागत tc358743_ddc5v_delays ddc5v_delay;

	bool enable_hdcp;

	/*
	 * The FIFO size is 512x32, so Toshiba recommend to set the शेष FIFO
	 * level to somewhere in the middle (e.g. 300), so it can cover speed
	 * mismatches in input and output ports.
	 */
	u16 fअगरo_level;

	/* Bps pr lane is (refclk_hz / pll_prd) * pll_fbd */
	u16 pll_prd;
	u16 pll_fbd;

	/* CSI
	 * Calculate CSI parameters with REF_02 क्रम the highest resolution your
	 * CSI पूर्णांकerface can handle. The driver will adjust the number of CSI
	 * lanes in use according to the pixel घड़ी.
	 *
	 * The values in brackets are calculated with REF_02 when the number of
	 * bps pr lane is 823.5 MHz, and can serve as a starting poपूर्णांक.
	 */
	u32 lineinitcnt;	/* (0x00001770) */
	u32 lptxसमयcnt;	/* (0x00000005) */
	u32 tclk_headercnt;	/* (0x00001d04) */
	u32 tclk_trailcnt;	/* (0x00000000) */
	u32 ths_headercnt;	/* (0x00000505) */
	u32 twakeup;		/* (0x00004650) */
	u32 tclk_postcnt;	/* (0x00000000) */
	u32 ths_trailcnt;	/* (0x00000004) */
	u32 hstxvregcnt;	/* (0x00000005) */

	/* DVI->HDMI detection delay to aव्योम unnecessary चयनing between DVI
	 * and HDMI mode.
	 * Sets HDMI_DET_V in रेजिस्टर HDMI_DET.
	 * Default: HDMI_MODE_DELAY_0_MS
	 */
	क्रमागत tc358743_hdmi_detection_delay hdmi_detection_delay;

	/* Reset PHY स्वतःmatically when TMDS घड़ी goes from DC to AC.
	 * Sets PHY_AUTO_RST2 in रेजिस्टर PHY_CTL2.
	 * Default: false
	 */
	bool hdmi_phy_स्वतः_reset_पंचांगds_detected;

	/* Reset PHY स्वतःmatically when TMDS घड़ी passes 21 MHz.
	 * Sets PHY_AUTO_RST3 in रेजिस्टर PHY_CTL2.
	 * Default: false
	 */
	bool hdmi_phy_स्वतः_reset_पंचांगds_in_range;

	/* Reset PHY स्वतःmatically when TMDS घड़ी is detected.
	 * Sets PHY_AUTO_RST4 in रेजिस्टर PHY_CTL2.
	 * Default: false
	 */
	bool hdmi_phy_स्वतः_reset_पंचांगds_valid;

	/* Reset HDMI PHY स्वतःmatically when hsync period is out of range.
	 * Sets H_PI_RST in रेजिस्टर HV_RST.
	 * Default: false
	 */
	bool hdmi_phy_स्वतः_reset_hsync_out_of_range;

	/* Reset HDMI PHY स्वतःmatically when vsync period is out of range.
	 * Sets V_PI_RST in रेजिस्टर HV_RST.
	 * Default: false
	 */
	bool hdmi_phy_स्वतः_reset_vsync_out_of_range;
पूर्ण;

/* custom controls */
/* Audio sample rate in Hz */
#घोषणा TC358743_CID_AUDIO_SAMPLING_RATE (V4L2_CID_USER_TC358743_BASE + 0)
/* Audio present status */
#घोषणा TC358743_CID_AUDIO_PRESENT       (V4L2_CID_USER_TC358743_BASE + 1)

#पूर्ण_अगर
