<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2013 NVIDIA Corporation
 * Copyright (C) 2018 Cadence Design Systems Inc.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समय64.h>

#समावेश <linux/phy/phy.h>
#समावेश <linux/phy/phy-mipi-dphy.h>

/*
 * Minimum D-PHY timings based on MIPI D-PHY specअगरication. Derived
 * from the valid ranges specअगरied in Section 6.9, Table 14, Page 41
 * of the D-PHY specअगरication (v2.1).
 */
पूर्णांक phy_mipi_dphy_get_शेष_config(अचिन्हित दीर्घ pixel_घड़ी,
				     अचिन्हित पूर्णांक bpp,
				     अचिन्हित पूर्णांक lanes,
				     काष्ठा phy_configure_opts_mipi_dphy *cfg)
अणु
	अचिन्हित दीर्घ दीर्घ hs_clk_rate;
	अचिन्हित दीर्घ दीर्घ ui;

	अगर (!cfg)
		वापस -EINVAL;

	hs_clk_rate = pixel_घड़ी * bpp;
	करो_भाग(hs_clk_rate, lanes);

	ui = ALIGN(PSEC_PER_SEC, hs_clk_rate);
	करो_भाग(ui, hs_clk_rate);

	cfg->clk_miss = 0;
	cfg->clk_post = 60000 + 52 * ui;
	cfg->clk_pre = 8000;
	cfg->clk_prepare = 38000;
	cfg->clk_settle = 95000;
	cfg->clk_term_en = 0;
	cfg->clk_trail = 60000;
	cfg->clk_zero = 262000;
	cfg->d_term_en = 0;
	cfg->eot = 0;
	cfg->hs_निकास = 100000;
	cfg->hs_prepare = 40000 + 4 * ui;
	cfg->hs_zero = 105000 + 6 * ui;
	cfg->hs_settle = 85000 + 6 * ui;
	cfg->hs_skip = 40000;

	/*
	 * The MIPI D-PHY specअगरication (Section 6.9, v1.2, Table 14, Page 40)
	 * contains this क्रमmula as:
	 *
	 *     T_HS-TRAIL = max(n * 8 * ui, 60 + n * 4 * ui)
	 *
	 * where n = 1 क्रम क्रमward-direction HS mode and n = 4 क्रम reverse-
	 * direction HS mode. There's only one setting and this function करोes
	 * not parameterize on anything other that ui, so this code will
	 * assumes that reverse-direction HS mode is supported and uses n = 4.
	 */
	cfg->hs_trail = max(4 * 8 * ui, 60000 + 4 * 4 * ui);

	cfg->init = 100;
	cfg->lpx = 60000;
	cfg->ta_get = 5 * cfg->lpx;
	cfg->ta_go = 4 * cfg->lpx;
	cfg->ta_sure = 2 * cfg->lpx;
	cfg->wakeup = 1000;

	cfg->hs_clk_rate = hs_clk_rate;
	cfg->lanes = lanes;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(phy_mipi_dphy_get_शेष_config);

/*
 * Validate D-PHY configuration according to MIPI D-PHY specअगरication
 * (v1.2, Section Section 6.9 "Global Operation Timing Parameters").
 */
पूर्णांक phy_mipi_dphy_config_validate(काष्ठा phy_configure_opts_mipi_dphy *cfg)
अणु
	अचिन्हित दीर्घ दीर्घ ui;

	अगर (!cfg)
		वापस -EINVAL;

	ui = ALIGN(PSEC_PER_SEC, cfg->hs_clk_rate);
	करो_भाग(ui, cfg->hs_clk_rate);

	अगर (cfg->clk_miss > 60000)
		वापस -EINVAL;

	अगर (cfg->clk_post < (60000 + 52 * ui))
		वापस -EINVAL;

	अगर (cfg->clk_pre < 8000)
		वापस -EINVAL;

	अगर (cfg->clk_prepare < 38000 || cfg->clk_prepare > 95000)
		वापस -EINVAL;

	अगर (cfg->clk_settle < 95000 || cfg->clk_settle > 300000)
		वापस -EINVAL;

	अगर (cfg->clk_term_en > 38000)
		वापस -EINVAL;

	अगर (cfg->clk_trail < 60000)
		वापस -EINVAL;

	अगर ((cfg->clk_prepare + cfg->clk_zero) < 300000)
		वापस -EINVAL;

	अगर (cfg->d_term_en > (35000 + 4 * ui))
		वापस -EINVAL;

	अगर (cfg->eot > (105000 + 12 * ui))
		वापस -EINVAL;

	अगर (cfg->hs_निकास < 100000)
		वापस -EINVAL;

	अगर (cfg->hs_prepare < (40000 + 4 * ui) ||
	    cfg->hs_prepare > (85000 + 6 * ui))
		वापस -EINVAL;

	अगर ((cfg->hs_prepare + cfg->hs_zero) < (145000 + 10 * ui))
		वापस -EINVAL;

	अगर ((cfg->hs_settle < (85000 + 6 * ui)) ||
	    (cfg->hs_settle > (145000 + 10 * ui)))
		वापस -EINVAL;

	अगर (cfg->hs_skip < 40000 || cfg->hs_skip > (55000 + 4 * ui))
		वापस -EINVAL;

	अगर (cfg->hs_trail < max(8 * ui, 60000 + 4 * ui))
		वापस -EINVAL;

	अगर (cfg->init < 100)
		वापस -EINVAL;

	अगर (cfg->lpx < 50000)
		वापस -EINVAL;

	अगर (cfg->ta_get != (5 * cfg->lpx))
		वापस -EINVAL;

	अगर (cfg->ta_go != (4 * cfg->lpx))
		वापस -EINVAL;

	अगर (cfg->ta_sure < cfg->lpx || cfg->ta_sure > (2 * cfg->lpx))
		वापस -EINVAL;

	अगर (cfg->wakeup < 1000)
		वापस -EINVAL;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(phy_mipi_dphy_config_validate);
