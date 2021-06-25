<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2015, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित __DSI_PHY_H__
#घोषणा __DSI_PHY_H__

#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/regulator/consumer.h>

#समावेश "dsi.h"

#घोषणा dsi_phy_पढ़ो(offset) msm_पढ़ोl((offset))
#घोषणा dsi_phy_ग_लिखो(offset, data) msm_ग_लिखोl((data), (offset))
#घोषणा dsi_phy_ग_लिखो_udelay(offset, data, delay_us) अणु msm_ग_लिखोl((data), (offset)); udelay(delay_us); पूर्ण
#घोषणा dsi_phy_ग_लिखो_ndelay(offset, data, delay_ns) अणु msm_ग_लिखोl((data), (offset)); ndelay(delay_ns); पूर्ण

काष्ठा msm_dsi_phy_ops अणु
	पूर्णांक (*pll_init)(काष्ठा msm_dsi_phy *phy);
	पूर्णांक (*enable)(काष्ठा msm_dsi_phy *phy,
			काष्ठा msm_dsi_phy_clk_request *clk_req);
	व्योम (*disable)(काष्ठा msm_dsi_phy *phy);
	व्योम (*save_pll_state)(काष्ठा msm_dsi_phy *phy);
	पूर्णांक (*restore_pll_state)(काष्ठा msm_dsi_phy *phy);
पूर्ण;

काष्ठा msm_dsi_phy_cfg अणु
	काष्ठा dsi_reg_config reg_cfg;
	काष्ठा msm_dsi_phy_ops ops;

	अचिन्हित दीर्घ	min_pll_rate;
	अचिन्हित दीर्घ	max_pll_rate;

	स्थिर resource_माप_प्रकार io_start[DSI_MAX];
	स्थिर पूर्णांक num_dsi_phy;
	स्थिर पूर्णांक quirks;
	bool has_phy_regulator;
	bool has_phy_lane;
पूर्ण;

बाह्य स्थिर काष्ठा msm_dsi_phy_cfg dsi_phy_28nm_hpm_cfgs;
बाह्य स्थिर काष्ठा msm_dsi_phy_cfg dsi_phy_28nm_hpm_famb_cfgs;
बाह्य स्थिर काष्ठा msm_dsi_phy_cfg dsi_phy_28nm_lp_cfgs;
बाह्य स्थिर काष्ठा msm_dsi_phy_cfg dsi_phy_20nm_cfgs;
बाह्य स्थिर काष्ठा msm_dsi_phy_cfg dsi_phy_28nm_8960_cfgs;
बाह्य स्थिर काष्ठा msm_dsi_phy_cfg dsi_phy_14nm_cfgs;
बाह्य स्थिर काष्ठा msm_dsi_phy_cfg dsi_phy_14nm_660_cfgs;
बाह्य स्थिर काष्ठा msm_dsi_phy_cfg dsi_phy_10nm_cfgs;
बाह्य स्थिर काष्ठा msm_dsi_phy_cfg dsi_phy_10nm_8998_cfgs;
बाह्य स्थिर काष्ठा msm_dsi_phy_cfg dsi_phy_7nm_cfgs;
बाह्य स्थिर काष्ठा msm_dsi_phy_cfg dsi_phy_7nm_8150_cfgs;

काष्ठा msm_dsi_dphy_timing अणु
	u32 clk_zero;
	u32 clk_trail;
	u32 clk_prepare;
	u32 hs_निकास;
	u32 hs_zero;
	u32 hs_prepare;
	u32 hs_trail;
	u32 hs_rqst;
	u32 ta_go;
	u32 ta_sure;
	u32 ta_get;

	काष्ठा msm_dsi_phy_shared_timings shared_timings;

	/* For PHY v2 only */
	u32 hs_rqst_ckln;
	u32 hs_prep_dly;
	u32 hs_prep_dly_ckln;
	u8 hs_halfbyte_en;
	u8 hs_halfbyte_en_ckln;
पूर्ण;

#घोषणा DSI_BYTE_PLL_CLK		0
#घोषणा DSI_PIXEL_PLL_CLK		1
#घोषणा NUM_PROVIDED_CLKS		2

काष्ठा msm_dsi_phy अणु
	काष्ठा platक्रमm_device *pdev;
	व्योम __iomem *base;
	व्योम __iomem *pll_base;
	व्योम __iomem *reg_base;
	व्योम __iomem *lane_base;
	पूर्णांक id;

	काष्ठा clk *ahb_clk;
	काष्ठा regulator_bulk_data supplies[DSI_DEV_REGULATOR_MAX];

	काष्ठा msm_dsi_dphy_timing timing;
	स्थिर काष्ठा msm_dsi_phy_cfg *cfg;

	क्रमागत msm_dsi_phy_useहाल useहाल;
	bool regulator_lकरो_mode;

	काष्ठा clk_hw *vco_hw;
	bool pll_on;

	काष्ठा clk_hw_onecell_data *provided_घड़ीs;

	bool state_saved;
पूर्ण;

/*
 * PHY पूर्णांकernal functions
 */
पूर्णांक msm_dsi_dphy_timing_calc(काष्ठा msm_dsi_dphy_timing *timing,
			     काष्ठा msm_dsi_phy_clk_request *clk_req);
पूर्णांक msm_dsi_dphy_timing_calc_v2(काष्ठा msm_dsi_dphy_timing *timing,
				काष्ठा msm_dsi_phy_clk_request *clk_req);
पूर्णांक msm_dsi_dphy_timing_calc_v3(काष्ठा msm_dsi_dphy_timing *timing,
				काष्ठा msm_dsi_phy_clk_request *clk_req);
पूर्णांक msm_dsi_dphy_timing_calc_v4(काष्ठा msm_dsi_dphy_timing *timing,
				काष्ठा msm_dsi_phy_clk_request *clk_req);

#पूर्ण_अगर /* __DSI_PHY_H__ */
