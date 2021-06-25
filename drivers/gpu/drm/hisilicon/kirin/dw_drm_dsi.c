<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * DesignWare MIPI DSI Host Controller v1.02 driver
 *
 * Copyright (c) 2016 Linaro Limited.
 * Copyright (c) 2014-2016 Hisilicon Limited.
 *
 * Author:
 *	Xinliang Liu <z.liuxinliang@hisilicon.com>
 *	Xinliang Liu <xinliang.liu@linaro.org>
 *	Xinwei Kong <kong.kongxinwei@hisilicon.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "dw_dsi_reg.h"

#घोषणा MAX_TX_ESC_CLK		10
#घोषणा ROUND(x, y)		((x) / (y) + \
				((x) % (y) * 10 / (y) >= 5 ? 1 : 0))
#घोषणा PHY_REF_CLK_RATE	19200000
#घोषणा PHY_REF_CLK_PERIOD_PS	(1000000000 / (PHY_REF_CLK_RATE / 1000))

#घोषणा encoder_to_dsi(encoder) \
	container_of(encoder, काष्ठा dw_dsi, encoder)
#घोषणा host_to_dsi(host) \
	container_of(host, काष्ठा dw_dsi, host)

काष्ठा mipi_phy_params अणु
	u32 clk_t_lpx;
	u32 clk_t_hs_prepare;
	u32 clk_t_hs_zero;
	u32 clk_t_hs_trial;
	u32 clk_t_wakeup;
	u32 data_t_lpx;
	u32 data_t_hs_prepare;
	u32 data_t_hs_zero;
	u32 data_t_hs_trial;
	u32 data_t_ta_go;
	u32 data_t_ta_get;
	u32 data_t_wakeup;
	u32 hstx_ckg_sel;
	u32 pll_fbd_भाग5f;
	u32 pll_fbd_भाग1f;
	u32 pll_fbd_2p;
	u32 pll_enbwt;
	u32 pll_fbd_p;
	u32 pll_fbd_s;
	u32 pll_pre_भाग1p;
	u32 pll_pre_p;
	u32 pll_vco_750M;
	u32 pll_lpf_rs;
	u32 pll_lpf_cs;
	u32 clklp2hs_समय;
	u32 clkhs2lp_समय;
	u32 lp2hs_समय;
	u32 hs2lp_समय;
	u32 clk_to_data_delay;
	u32 data_to_clk_delay;
	u32 lane_byte_clk_kHz;
	u32 clk_भागision;
पूर्ण;

काष्ठा dsi_hw_ctx अणु
	व्योम __iomem *base;
	काष्ठा clk *pclk;
पूर्ण;

काष्ठा dw_dsi अणु
	काष्ठा drm_encoder encoder;
	काष्ठा drm_bridge *bridge;
	काष्ठा mipi_dsi_host host;
	काष्ठा drm_display_mode cur_mode;
	काष्ठा dsi_hw_ctx *ctx;
	काष्ठा mipi_phy_params phy;

	u32 lanes;
	क्रमागत mipi_dsi_pixel_क्रमmat क्रमmat;
	अचिन्हित दीर्घ mode_flags;
	bool enable;
पूर्ण;

काष्ठा dsi_data अणु
	काष्ठा dw_dsi dsi;
	काष्ठा dsi_hw_ctx ctx;
पूर्ण;

काष्ठा dsi_phy_range अणु
	u32 min_range_kHz;
	u32 max_range_kHz;
	u32 pll_vco_750M;
	u32 hstx_ckg_sel;
पूर्ण;

अटल स्थिर काष्ठा dsi_phy_range dphy_range_info[] = अणु
	अणु   46875,    62500,   1,    7 पूर्ण,
	अणु   62500,    93750,   0,    7 पूर्ण,
	अणु   93750,   125000,   1,    6 पूर्ण,
	अणु  125000,   187500,   0,    6 पूर्ण,
	अणु  187500,   250000,   1,    5 पूर्ण,
	अणु  250000,   375000,   0,    5 पूर्ण,
	अणु  375000,   500000,   1,    4 पूर्ण,
	अणु  500000,   750000,   0,    4 पूर्ण,
	अणु  750000,  1000000,   1,    0 पूर्ण,
	अणु 1000000,  1500000,   0,    0 पूर्ण
पूर्ण;

अटल u32 dsi_calc_phy_rate(u32 req_kHz, काष्ठा mipi_phy_params *phy)
अणु
	u32 ref_clk_ps = PHY_REF_CLK_PERIOD_PS;
	u32 पंचांगp_kHz = req_kHz;
	u32 i = 0;
	u32 q_pll = 1;
	u32 m_pll = 0;
	u32 n_pll = 0;
	u32 r_pll = 1;
	u32 m_n = 0;
	u32 m_n_पूर्णांक = 0;
	u32 f_kHz = 0;
	u64 temp;

	/*
	 * Find a rate >= req_kHz.
	 */
	करो अणु
		f_kHz = पंचांगp_kHz;

		क्रम (i = 0; i < ARRAY_SIZE(dphy_range_info); i++)
			अगर (f_kHz >= dphy_range_info[i].min_range_kHz &&
			    f_kHz <= dphy_range_info[i].max_range_kHz)
				अवरोध;

		अगर (i == ARRAY_SIZE(dphy_range_info)) अणु
			DRM_ERROR("%dkHz out of range\n", f_kHz);
			वापस 0;
		पूर्ण

		phy->pll_vco_750M = dphy_range_info[i].pll_vco_750M;
		phy->hstx_ckg_sel = dphy_range_info[i].hstx_ckg_sel;

		अगर (phy->hstx_ckg_sel <= 7 &&
		    phy->hstx_ckg_sel >= 4)
			q_pll = 0x10 >> (7 - phy->hstx_ckg_sel);

		temp = f_kHz * (u64)q_pll * (u64)ref_clk_ps;
		m_n_पूर्णांक = temp / (u64)1000000000;
		m_n = (temp % (u64)1000000000) / (u64)100000000;

		अगर (m_n_पूर्णांक % 2 == 0) अणु
			अगर (m_n * 6 >= 50) अणु
				n_pll = 2;
				m_pll = (m_n_पूर्णांक + 1) * n_pll;
			पूर्ण अन्यथा अगर (m_n * 6 >= 30) अणु
				n_pll = 3;
				m_pll = m_n_पूर्णांक * n_pll + 2;
			पूर्ण अन्यथा अणु
				n_pll = 1;
				m_pll = m_n_पूर्णांक * n_pll;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (m_n * 6 >= 50) अणु
				n_pll = 1;
				m_pll = (m_n_पूर्णांक + 1) * n_pll;
			पूर्ण अन्यथा अगर (m_n * 6 >= 30) अणु
				n_pll = 1;
				m_pll = (m_n_पूर्णांक + 1) * n_pll;
			पूर्ण अन्यथा अगर (m_n * 6 >= 10) अणु
				n_pll = 3;
				m_pll = m_n_पूर्णांक * n_pll + 1;
			पूर्ण अन्यथा अणु
				n_pll = 2;
				m_pll = m_n_पूर्णांक * n_pll;
			पूर्ण
		पूर्ण

		अगर (n_pll == 1) अणु
			phy->pll_fbd_p = 0;
			phy->pll_pre_भाग1p = 1;
		पूर्ण अन्यथा अणु
			phy->pll_fbd_p = n_pll;
			phy->pll_pre_भाग1p = 0;
		पूर्ण

		अगर (phy->pll_fbd_2p <= 7 && phy->pll_fbd_2p >= 4)
			r_pll = 0x10 >> (7 - phy->pll_fbd_2p);

		अगर (m_pll == 2) अणु
			phy->pll_pre_p = 0;
			phy->pll_fbd_s = 0;
			phy->pll_fbd_भाग1f = 0;
			phy->pll_fbd_भाग5f = 1;
		पूर्ण अन्यथा अगर (m_pll >= 2 * 2 * r_pll && m_pll <= 2 * 4 * r_pll) अणु
			phy->pll_pre_p = m_pll / (2 * r_pll);
			phy->pll_fbd_s = 0;
			phy->pll_fbd_भाग1f = 1;
			phy->pll_fbd_भाग5f = 0;
		पूर्ण अन्यथा अगर (m_pll >= 2 * 5 * r_pll && m_pll <= 2 * 150 * r_pll) अणु
			अगर (((m_pll / (2 * r_pll)) % 2) == 0) अणु
				phy->pll_pre_p =
					(m_pll / (2 * r_pll)) / 2 - 1;
				phy->pll_fbd_s =
					(m_pll / (2 * r_pll)) % 2 + 2;
			पूर्ण अन्यथा अणु
				phy->pll_pre_p =
					(m_pll / (2 * r_pll)) / 2;
				phy->pll_fbd_s =
					(m_pll / (2 * r_pll)) % 2;
			पूर्ण
			phy->pll_fbd_भाग1f = 0;
			phy->pll_fbd_भाग5f = 0;
		पूर्ण अन्यथा अणु
			phy->pll_pre_p = 0;
			phy->pll_fbd_s = 0;
			phy->pll_fbd_भाग1f = 0;
			phy->pll_fbd_भाग5f = 1;
		पूर्ण

		f_kHz = (u64)1000000000 * (u64)m_pll /
			((u64)ref_clk_ps * (u64)n_pll * (u64)q_pll);

		अगर (f_kHz >= req_kHz)
			अवरोध;

		पंचांगp_kHz += 10;

	पूर्ण जबतक (true);

	वापस f_kHz;
पूर्ण

अटल व्योम dsi_get_phy_params(u32 phy_req_kHz,
			       काष्ठा mipi_phy_params *phy)
अणु
	u32 ref_clk_ps = PHY_REF_CLK_PERIOD_PS;
	u32 phy_rate_kHz;
	u32 ui;

	स_रखो(phy, 0, माप(*phy));

	phy_rate_kHz = dsi_calc_phy_rate(phy_req_kHz, phy);
	अगर (!phy_rate_kHz)
		वापस;

	ui = 1000000 / phy_rate_kHz;

	phy->clk_t_lpx = ROUND(50, 8 * ui);
	phy->clk_t_hs_prepare = ROUND(133, 16 * ui) - 1;

	phy->clk_t_hs_zero = ROUND(262, 8 * ui);
	phy->clk_t_hs_trial = 2 * (ROUND(60, 8 * ui) - 1);
	phy->clk_t_wakeup = ROUND(1000000, (ref_clk_ps / 1000) - 1);
	अगर (phy->clk_t_wakeup > 0xff)
		phy->clk_t_wakeup = 0xff;
	phy->data_t_wakeup = phy->clk_t_wakeup;
	phy->data_t_lpx = phy->clk_t_lpx;
	phy->data_t_hs_prepare = ROUND(125 + 10 * ui, 16 * ui) - 1;
	phy->data_t_hs_zero = ROUND(105 + 6 * ui, 8 * ui);
	phy->data_t_hs_trial = 2 * (ROUND(60 + 4 * ui, 8 * ui) - 1);
	phy->data_t_ta_go = 3;
	phy->data_t_ta_get = 4;

	phy->pll_enbwt = 1;
	phy->clklp2hs_समय = ROUND(407, 8 * ui) + 12;
	phy->clkhs2lp_समय = ROUND(105 + 12 * ui, 8 * ui);
	phy->lp2hs_समय = ROUND(240 + 12 * ui, 8 * ui) + 1;
	phy->hs2lp_समय = phy->clkhs2lp_समय;
	phy->clk_to_data_delay = 1 + phy->clklp2hs_समय;
	phy->data_to_clk_delay = ROUND(60 + 52 * ui, 8 * ui) +
				phy->clkhs2lp_समय;

	phy->lane_byte_clk_kHz = phy_rate_kHz / 8;
	phy->clk_भागision =
		DIV_ROUND_UP(phy->lane_byte_clk_kHz, MAX_TX_ESC_CLK);
पूर्ण

अटल u32 dsi_get_dpi_color_coding(क्रमागत mipi_dsi_pixel_क्रमmat क्रमmat)
अणु
	u32 val;

	/*
	 * TODO: only support RGB888 now, to support more
	 */
	चयन (क्रमmat) अणु
	हाल MIPI_DSI_FMT_RGB888:
		val = DSI_24BITS_1;
		अवरोध;
	शेष:
		val = DSI_24BITS_1;
		अवरोध;
	पूर्ण

	वापस val;
पूर्ण

/*
 * dsi phy reg ग_लिखो function
 */
अटल व्योम dsi_phy_tst_set(व्योम __iomem *base, u32 reg, u32 val)
अणु
	u32 reg_ग_लिखो = 0x10000 + reg;

	/*
	 * latch reg first
	 */
	ग_लिखोl(reg_ग_लिखो, base + PHY_TST_CTRL1);
	ग_लिखोl(0x02, base + PHY_TST_CTRL0);
	ग_लिखोl(0x00, base + PHY_TST_CTRL0);

	/*
	 * then latch value
	 */
	ग_लिखोl(val, base + PHY_TST_CTRL1);
	ग_लिखोl(0x02, base + PHY_TST_CTRL0);
	ग_लिखोl(0x00, base + PHY_TST_CTRL0);
पूर्ण

अटल व्योम dsi_set_phy_समयr(व्योम __iomem *base,
			      काष्ठा mipi_phy_params *phy,
			      u32 lanes)
अणु
	u32 val;

	/*
	 * Set lane value and phy stop रुको समय.
	 */
	val = (lanes - 1) | (PHY_STOP_WAIT_TIME << 8);
	ग_लिखोl(val, base + PHY_IF_CFG);

	/*
	 * Set phy clk भागision.
	 */
	val = पढ़ोl(base + CLKMGR_CFG) | phy->clk_भागision;
	ग_लिखोl(val, base + CLKMGR_CFG);

	/*
	 * Set lp and hs चयनing params.
	 */
	dw_update_bits(base + PHY_TMR_CFG, 24, MASK(8), phy->hs2lp_समय);
	dw_update_bits(base + PHY_TMR_CFG, 16, MASK(8), phy->lp2hs_समय);
	dw_update_bits(base + PHY_TMR_LPCLK_CFG, 16, MASK(10),
		       phy->clkhs2lp_समय);
	dw_update_bits(base + PHY_TMR_LPCLK_CFG, 0, MASK(10),
		       phy->clklp2hs_समय);
	dw_update_bits(base + CLK_DATA_TMR_CFG, 8, MASK(8),
		       phy->data_to_clk_delay);
	dw_update_bits(base + CLK_DATA_TMR_CFG, 0, MASK(8),
		       phy->clk_to_data_delay);
पूर्ण

अटल व्योम dsi_set_mipi_phy(व्योम __iomem *base,
			     काष्ठा mipi_phy_params *phy,
			     u32 lanes)
अणु
	u32 delay_count;
	u32 val;
	u32 i;

	/* phy समयr setting */
	dsi_set_phy_समयr(base, phy, lanes);

	/*
	 * Reset to clean up phy tst params.
	 */
	ग_लिखोl(0, base + PHY_RSTZ);
	ग_लिखोl(0, base + PHY_TST_CTRL0);
	ग_लिखोl(1, base + PHY_TST_CTRL0);
	ग_लिखोl(0, base + PHY_TST_CTRL0);

	/*
	 * Clock lane timing control setting: TLPX, THS-PREPARE,
	 * THS-ZERO, THS-TRAIL, TWAKEUP.
	 */
	dsi_phy_tst_set(base, CLK_TLPX, phy->clk_t_lpx);
	dsi_phy_tst_set(base, CLK_THS_PREPARE, phy->clk_t_hs_prepare);
	dsi_phy_tst_set(base, CLK_THS_ZERO, phy->clk_t_hs_zero);
	dsi_phy_tst_set(base, CLK_THS_TRAIL, phy->clk_t_hs_trial);
	dsi_phy_tst_set(base, CLK_TWAKEUP, phy->clk_t_wakeup);

	/*
	 * Data lane timing control setting: TLPX, THS-PREPARE,
	 * THS-ZERO, THS-TRAIL, TTA-GO, TTA-GET, TWAKEUP.
	 */
	क्रम (i = 0; i < lanes; i++) अणु
		dsi_phy_tst_set(base, DATA_TLPX(i), phy->data_t_lpx);
		dsi_phy_tst_set(base, DATA_THS_PREPARE(i),
				phy->data_t_hs_prepare);
		dsi_phy_tst_set(base, DATA_THS_ZERO(i), phy->data_t_hs_zero);
		dsi_phy_tst_set(base, DATA_THS_TRAIL(i), phy->data_t_hs_trial);
		dsi_phy_tst_set(base, DATA_TTA_GO(i), phy->data_t_ta_go);
		dsi_phy_tst_set(base, DATA_TTA_GET(i), phy->data_t_ta_get);
		dsi_phy_tst_set(base, DATA_TWAKEUP(i), phy->data_t_wakeup);
	पूर्ण

	/*
	 * physical configuration: I, pll I, pll II, pll III,
	 * pll IV, pll V.
	 */
	dsi_phy_tst_set(base, PHY_CFG_I, phy->hstx_ckg_sel);
	val = (phy->pll_fbd_भाग5f << 5) + (phy->pll_fbd_भाग1f << 4) +
				(phy->pll_fbd_2p << 1) + phy->pll_enbwt;
	dsi_phy_tst_set(base, PHY_CFG_PLL_I, val);
	dsi_phy_tst_set(base, PHY_CFG_PLL_II, phy->pll_fbd_p);
	dsi_phy_tst_set(base, PHY_CFG_PLL_III, phy->pll_fbd_s);
	val = (phy->pll_pre_भाग1p << 7) + phy->pll_pre_p;
	dsi_phy_tst_set(base, PHY_CFG_PLL_IV, val);
	val = (5 << 5) + (phy->pll_vco_750M << 4) + (phy->pll_lpf_rs << 2) +
		phy->pll_lpf_cs;
	dsi_phy_tst_set(base, PHY_CFG_PLL_V, val);

	ग_लिखोl(PHY_ENABLECLK, base + PHY_RSTZ);
	udelay(1);
	ग_लिखोl(PHY_ENABLECLK | PHY_UNSHUTDOWNZ, base + PHY_RSTZ);
	udelay(1);
	ग_लिखोl(PHY_ENABLECLK | PHY_UNRSTZ | PHY_UNSHUTDOWNZ, base + PHY_RSTZ);
	usleep_range(1000, 1500);

	/*
	 * रुको क्रम phy's घड़ी पढ़ोy
	 */
	delay_count = 100;
	जबतक (delay_count) अणु
		val = पढ़ोl(base +  PHY_STATUS);
		अगर ((BIT(0) | BIT(2)) & val)
			अवरोध;

		udelay(1);
		delay_count--;
	पूर्ण

	अगर (!delay_count)
		DRM_INFO("phylock and phystopstateclklane is not ready.\n");
पूर्ण

अटल व्योम dsi_set_mode_timing(व्योम __iomem *base,
				u32 lane_byte_clk_kHz,
				काष्ठा drm_display_mode *mode,
				क्रमागत mipi_dsi_pixel_क्रमmat क्रमmat)
अणु
	u32 hfp, hbp, hsw, vfp, vbp, vsw;
	u32 hline_समय;
	u32 hsa_समय;
	u32 hbp_समय;
	u32 pixel_clk_kHz;
	पूर्णांक htot, vtot;
	u32 val;
	u64 पंचांगp;

	val = dsi_get_dpi_color_coding(क्रमmat);
	ग_लिखोl(val, base + DPI_COLOR_CODING);

	val = (mode->flags & DRM_MODE_FLAG_NHSYNC ? 1 : 0) << 2;
	val |= (mode->flags & DRM_MODE_FLAG_NVSYNC ? 1 : 0) << 1;
	ग_लिखोl(val, base +  DPI_CFG_POL);

	/*
	 * The DSI IP accepts vertical timing using lines as normal,
	 * but horizontal timing is a mixture of pixel-घड़ीs क्रम the
	 * active region and byte-lane घड़ीs क्रम the blanking-related
	 * timings.  hfp is specअगरied as the total hline_समय in byte-
	 * lane घड़ीs minus hsa, hbp and active.
	 */
	pixel_clk_kHz = mode->घड़ी;
	htot = mode->htotal;
	vtot = mode->vtotal;
	hfp = mode->hsync_start - mode->hdisplay;
	hbp = mode->htotal - mode->hsync_end;
	hsw = mode->hsync_end - mode->hsync_start;
	vfp = mode->vsync_start - mode->vdisplay;
	vbp = mode->vtotal - mode->vsync_end;
	vsw = mode->vsync_end - mode->vsync_start;
	अगर (vsw > 15) अणु
		DRM_DEBUG_DRIVER("vsw exceeded 15\n");
		vsw = 15;
	पूर्ण

	hsa_समय = (hsw * lane_byte_clk_kHz) / pixel_clk_kHz;
	hbp_समय = (hbp * lane_byte_clk_kHz) / pixel_clk_kHz;
	पंचांगp = (u64)htot * (u64)lane_byte_clk_kHz;
	hline_समय = DIV_ROUND_UP(पंचांगp, pixel_clk_kHz);

	/* all specअगरied in byte-lane घड़ीs */
	ग_लिखोl(hsa_समय, base + VID_HSA_TIME);
	ग_लिखोl(hbp_समय, base + VID_HBP_TIME);
	ग_लिखोl(hline_समय, base + VID_HLINE_TIME);

	ग_लिखोl(vsw, base + VID_VSA_LINES);
	ग_लिखोl(vbp, base + VID_VBP_LINES);
	ग_लिखोl(vfp, base + VID_VFP_LINES);
	ग_लिखोl(mode->vdisplay, base + VID_VACTIVE_LINES);
	ग_लिखोl(mode->hdisplay, base + VID_PKT_SIZE);

	DRM_DEBUG_DRIVER("htot=%d, hfp=%d, hbp=%d, hsw=%d\n",
			 htot, hfp, hbp, hsw);
	DRM_DEBUG_DRIVER("vtol=%d, vfp=%d, vbp=%d, vsw=%d\n",
			 vtot, vfp, vbp, vsw);
	DRM_DEBUG_DRIVER("hsa_time=%d, hbp_time=%d, hline_time=%d\n",
			 hsa_समय, hbp_समय, hline_समय);
पूर्ण

अटल व्योम dsi_set_video_mode(व्योम __iomem *base, अचिन्हित दीर्घ flags)
अणु
	u32 val;
	u32 mode_mask = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
		MIPI_DSI_MODE_VIDEO_SYNC_PULSE;
	u32 non_burst_sync_pulse = MIPI_DSI_MODE_VIDEO |
		MIPI_DSI_MODE_VIDEO_SYNC_PULSE;
	u32 non_burst_sync_event = MIPI_DSI_MODE_VIDEO;

	/*
	 * choose video mode type
	 */
	अगर ((flags & mode_mask) == non_burst_sync_pulse)
		val = DSI_NON_BURST_SYNC_PULSES;
	अन्यथा अगर ((flags & mode_mask) == non_burst_sync_event)
		val = DSI_NON_BURST_SYNC_EVENTS;
	अन्यथा
		val = DSI_BURST_SYNC_PULSES_1;
	ग_लिखोl(val, base + VID_MODE_CFG);

	ग_लिखोl(PHY_TXREQUESTCLKHS, base + LPCLK_CTRL);
	ग_लिखोl(DSI_VIDEO_MODE, base + MODE_CFG);
पूर्ण

अटल व्योम dsi_mipi_init(काष्ठा dw_dsi *dsi)
अणु
	काष्ठा dsi_hw_ctx *ctx = dsi->ctx;
	काष्ठा mipi_phy_params *phy = &dsi->phy;
	काष्ठा drm_display_mode *mode = &dsi->cur_mode;
	u32 bpp = mipi_dsi_pixel_क्रमmat_to_bpp(dsi->क्रमmat);
	व्योम __iomem *base = ctx->base;
	u32 dphy_req_kHz;

	/*
	 * count phy params
	 */
	dphy_req_kHz = mode->घड़ी * bpp / dsi->lanes;
	dsi_get_phy_params(dphy_req_kHz, phy);

	/* reset Core */
	ग_लिखोl(RESET, base + PWR_UP);

	/* set dsi phy params */
	dsi_set_mipi_phy(base, phy, dsi->lanes);

	/* set dsi mode timing */
	dsi_set_mode_timing(base, phy->lane_byte_clk_kHz, mode, dsi->क्रमmat);

	/* set dsi video mode */
	dsi_set_video_mode(base, dsi->mode_flags);

	/* dsi wake up */
	ग_लिखोl(POWERUP, base + PWR_UP);

	DRM_DEBUG_DRIVER("lanes=%d, pixel_clk=%d kHz, bytes_freq=%d kHz\n",
			 dsi->lanes, mode->घड़ी, phy->lane_byte_clk_kHz);
पूर्ण

अटल व्योम dsi_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा dw_dsi *dsi = encoder_to_dsi(encoder);
	काष्ठा dsi_hw_ctx *ctx = dsi->ctx;
	व्योम __iomem *base = ctx->base;

	अगर (!dsi->enable)
		वापस;

	ग_लिखोl(0, base + PWR_UP);
	ग_लिखोl(0, base + LPCLK_CTRL);
	ग_लिखोl(0, base + PHY_RSTZ);
	clk_disable_unprepare(ctx->pclk);

	dsi->enable = false;
पूर्ण

अटल व्योम dsi_encoder_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा dw_dsi *dsi = encoder_to_dsi(encoder);
	काष्ठा dsi_hw_ctx *ctx = dsi->ctx;
	पूर्णांक ret;

	अगर (dsi->enable)
		वापस;

	ret = clk_prepare_enable(ctx->pclk);
	अगर (ret) अणु
		DRM_ERROR("fail to enable pclk: %d\n", ret);
		वापस;
	पूर्ण

	dsi_mipi_init(dsi);

	dsi->enable = true;
पूर्ण

अटल क्रमागत drm_mode_status dsi_encoder_phy_mode_valid(
					काष्ठा drm_encoder *encoder,
					स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा dw_dsi *dsi = encoder_to_dsi(encoder);
	काष्ठा mipi_phy_params phy;
	u32 bpp = mipi_dsi_pixel_क्रमmat_to_bpp(dsi->क्रमmat);
	u32 req_kHz, act_kHz, lane_byte_clk_kHz;

	/* Calculate the lane byte clk using the adjusted mode clk */
	स_रखो(&phy, 0, माप(phy));
	req_kHz = mode->घड़ी * bpp / dsi->lanes;
	act_kHz = dsi_calc_phy_rate(req_kHz, &phy);
	lane_byte_clk_kHz = act_kHz / 8;

	DRM_DEBUG_DRIVER("Checking mode %ix%i-%i@%i clock: %i...",
			mode->hdisplay, mode->vdisplay, bpp,
			drm_mode_vrefresh(mode), mode->घड़ी);

	/*
	 * Make sure the adjusted mode घड़ी and the lane byte clk
	 * have a common denominator base frequency
	 */
	अगर (mode->घड़ी/dsi->lanes == lane_byte_clk_kHz/3) अणु
		DRM_DEBUG_DRIVER("OK!\n");
		वापस MODE_OK;
	पूर्ण

	DRM_DEBUG_DRIVER("BAD!\n");
	वापस MODE_BAD;
पूर्ण

अटल क्रमागत drm_mode_status dsi_encoder_mode_valid(काष्ठा drm_encoder *encoder,
					स्थिर काष्ठा drm_display_mode *mode)

अणु
	स्थिर काष्ठा drm_crtc_helper_funcs *crtc_funcs = शून्य;
	काष्ठा drm_crtc *crtc = शून्य;
	काष्ठा drm_display_mode adj_mode;
	क्रमागत drm_mode_status ret;

	/*
	 * The crtc might adjust the mode, so go through the
	 * possible crtcs (technically just one) and call
	 * mode_fixup to figure out the adjusted mode beक्रमe we
	 * validate it.
	 */
	drm_क्रम_each_crtc(crtc, encoder->dev) अणु
		/*
		 * reset adj_mode to the mode value each समय,
		 * so we करोn't adjust the mode twice
		 */
		drm_mode_copy(&adj_mode, mode);

		crtc_funcs = crtc->helper_निजी;
		अगर (crtc_funcs && crtc_funcs->mode_fixup)
			अगर (!crtc_funcs->mode_fixup(crtc, mode, &adj_mode))
				वापस MODE_BAD;

		ret = dsi_encoder_phy_mode_valid(encoder, &adj_mode);
		अगर (ret != MODE_OK)
			वापस ret;
	पूर्ण
	वापस MODE_OK;
पूर्ण

अटल व्योम dsi_encoder_mode_set(काष्ठा drm_encoder *encoder,
				 काष्ठा drm_display_mode *mode,
				 काष्ठा drm_display_mode *adj_mode)
अणु
	काष्ठा dw_dsi *dsi = encoder_to_dsi(encoder);

	drm_mode_copy(&dsi->cur_mode, adj_mode);
पूर्ण

अटल पूर्णांक dsi_encoder_atomic_check(काष्ठा drm_encoder *encoder,
				    काष्ठा drm_crtc_state *crtc_state,
				    काष्ठा drm_connector_state *conn_state)
अणु
	/* करो nothing */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs dw_encoder_helper_funcs = अणु
	.atomic_check	= dsi_encoder_atomic_check,
	.mode_valid	= dsi_encoder_mode_valid,
	.mode_set	= dsi_encoder_mode_set,
	.enable		= dsi_encoder_enable,
	.disable	= dsi_encoder_disable
पूर्ण;

अटल पूर्णांक dw_drm_encoder_init(काष्ठा device *dev,
			       काष्ठा drm_device *drm_dev,
			       काष्ठा drm_encoder *encoder)
अणु
	पूर्णांक ret;
	u32 crtc_mask = drm_of_find_possible_crtcs(drm_dev, dev->of_node);

	अगर (!crtc_mask) अणु
		DRM_ERROR("failed to find crtc mask\n");
		वापस -EINVAL;
	पूर्ण

	encoder->possible_crtcs = crtc_mask;
	ret = drm_simple_encoder_init(drm_dev, encoder, DRM_MODE_ENCODER_DSI);
	अगर (ret) अणु
		DRM_ERROR("failed to init dsi encoder\n");
		वापस ret;
	पूर्ण

	drm_encoder_helper_add(encoder, &dw_encoder_helper_funcs);

	वापस 0;
पूर्ण

अटल पूर्णांक dsi_host_attach(काष्ठा mipi_dsi_host *host,
			   काष्ठा mipi_dsi_device *mdsi)
अणु
	काष्ठा dw_dsi *dsi = host_to_dsi(host);

	अगर (mdsi->lanes < 1 || mdsi->lanes > 4) अणु
		DRM_ERROR("dsi device params invalid\n");
		वापस -EINVAL;
	पूर्ण

	dsi->lanes = mdsi->lanes;
	dsi->क्रमmat = mdsi->क्रमmat;
	dsi->mode_flags = mdsi->mode_flags;

	वापस 0;
पूर्ण

अटल पूर्णांक dsi_host_detach(काष्ठा mipi_dsi_host *host,
			   काष्ठा mipi_dsi_device *mdsi)
अणु
	/* करो nothing */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mipi_dsi_host_ops dsi_host_ops = अणु
	.attach = dsi_host_attach,
	.detach = dsi_host_detach,
पूर्ण;

अटल पूर्णांक dsi_host_init(काष्ठा device *dev, काष्ठा dw_dsi *dsi)
अणु
	काष्ठा mipi_dsi_host *host = &dsi->host;
	पूर्णांक ret;

	host->dev = dev;
	host->ops = &dsi_host_ops;
	ret = mipi_dsi_host_रेजिस्टर(host);
	अगर (ret) अणु
		DRM_ERROR("failed to register dsi host\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dsi_bridge_init(काष्ठा drm_device *dev, काष्ठा dw_dsi *dsi)
अणु
	काष्ठा drm_encoder *encoder = &dsi->encoder;
	काष्ठा drm_bridge *bridge = dsi->bridge;
	पूर्णांक ret;

	/* associate the bridge to dsi encoder */
	ret = drm_bridge_attach(encoder, bridge, शून्य, 0);
	अगर (ret) अणु
		DRM_ERROR("failed to attach external bridge\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dsi_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा dsi_data *ddata = dev_get_drvdata(dev);
	काष्ठा dw_dsi *dsi = &ddata->dsi;
	काष्ठा drm_device *drm_dev = data;
	पूर्णांक ret;

	ret = dw_drm_encoder_init(dev, drm_dev, &dsi->encoder);
	अगर (ret)
		वापस ret;

	ret = dsi_host_init(dev, dsi);
	अगर (ret)
		वापस ret;

	ret = dsi_bridge_init(drm_dev, dsi);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम dsi_unbind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	/* करो nothing */
पूर्ण

अटल स्थिर काष्ठा component_ops dsi_ops = अणु
	.bind	= dsi_bind,
	.unbind	= dsi_unbind,
पूर्ण;

अटल पूर्णांक dsi_parse_dt(काष्ठा platक्रमm_device *pdev, काष्ठा dw_dsi *dsi)
अणु
	काष्ठा dsi_hw_ctx *ctx = dsi->ctx;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा resource *res;
	पूर्णांक ret;

	/*
	 * Get the endpoपूर्णांक node. In our हाल, dsi has one output port1
	 * to which the बाह्यal HDMI bridge is connected.
	 */
	ret = drm_of_find_panel_or_bridge(np, 1, 0, शून्य, &dsi->bridge);
	अगर (ret)
		वापस ret;

	ctx->pclk = devm_clk_get(&pdev->dev, "pclk");
	अगर (IS_ERR(ctx->pclk)) अणु
		DRM_ERROR("failed to get pclk clock\n");
		वापस PTR_ERR(ctx->pclk);
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ctx->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(ctx->base)) अणु
		DRM_ERROR("failed to remap dsi io region\n");
		वापस PTR_ERR(ctx->base);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dsi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dsi_data *data;
	काष्ठा dw_dsi *dsi;
	काष्ठा dsi_hw_ctx *ctx;
	पूर्णांक ret;

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data) अणु
		DRM_ERROR("failed to allocate dsi data.\n");
		वापस -ENOMEM;
	पूर्ण
	dsi = &data->dsi;
	ctx = &data->ctx;
	dsi->ctx = ctx;

	ret = dsi_parse_dt(pdev, dsi);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, data);

	वापस component_add(&pdev->dev, &dsi_ops);
पूर्ण

अटल पूर्णांक dsi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &dsi_ops);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id dsi_of_match[] = अणु
	अणु.compatible = "hisilicon,hi6220-dsi"पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, dsi_of_match);

अटल काष्ठा platक्रमm_driver dsi_driver = अणु
	.probe = dsi_probe,
	.हटाओ = dsi_हटाओ,
	.driver = अणु
		.name = "dw-dsi",
		.of_match_table = dsi_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(dsi_driver);

MODULE_AUTHOR("Xinliang Liu <xinliang.liu@linaro.org>");
MODULE_AUTHOR("Xinliang Liu <z.liuxinliang@hisilicon.com>");
MODULE_AUTHOR("Xinwei Kong <kong.kongxinwei@hisilicon.com>");
MODULE_DESCRIPTION("DesignWare MIPI DSI Host Controller v1.02 driver");
MODULE_LICENSE("GPL v2");
