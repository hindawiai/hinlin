<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics SA 2017
 *
 * Authors: Philippe Cornu <philippe.cornu@st.com>
 *          Yannick Fertre <yannick.fertre@st.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <video/mipi_display.h>

#समावेश <drm/bridge/dw_mipi_dsi.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_prपूर्णांक.h>

#घोषणा HWVER_130			0x31333000	/* IP version 1.30 */
#घोषणा HWVER_131			0x31333100	/* IP version 1.31 */

/* DSI digital रेजिस्टरs & bit definitions */
#घोषणा DSI_VERSION			0x00
#घोषणा VERSION				GENMASK(31, 8)

/* DSI wrapper रेजिस्टरs & bit definitions */
/* Note: रेजिस्टरs are named as in the Reference Manual */
#घोषणा DSI_WCFGR	0x0400		/* Wrapper ConFiGuration Reg */
#घोषणा WCFGR_DSIM	BIT(0)		/* DSI Mode */
#घोषणा WCFGR_COLMUX	GENMASK(3, 1)	/* COLor MUltipleXing */

#घोषणा DSI_WCR		0x0404		/* Wrapper Control Reg */
#घोषणा WCR_DSIEN	BIT(3)		/* DSI ENable */

#घोषणा DSI_WISR	0x040C		/* Wrapper Interrupt and Status Reg */
#घोषणा WISR_PLLLS	BIT(8)		/* PLL Lock Status */
#घोषणा WISR_RRS	BIT(12)		/* Regulator Ready Status */

#घोषणा DSI_WPCR0	0x0418		/* Wrapper Phy Conf Reg 0 */
#घोषणा WPCR0_UIX4	GENMASK(5, 0)	/* Unit Interval X 4 */
#घोषणा WPCR0_TDDL	BIT(16)		/* Turn Disable Data Lanes */

#घोषणा DSI_WRPCR	0x0430		/* Wrapper Regulator & Pll Ctrl Reg */
#घोषणा WRPCR_PLLEN	BIT(0)		/* PLL ENable */
#घोषणा WRPCR_NDIV	GENMASK(8, 2)	/* pll loop DIVision Factor */
#घोषणा WRPCR_IDF	GENMASK(14, 11)	/* pll Input Division Factor */
#घोषणा WRPCR_ODF	GENMASK(17, 16)	/* pll Output Division Factor */
#घोषणा WRPCR_REGEN	BIT(24)		/* REGulator ENable */
#घोषणा WRPCR_BGREN	BIT(28)		/* BandGap Reference ENable */
#घोषणा IDF_MIN		1
#घोषणा IDF_MAX		7
#घोषणा NDIV_MIN	10
#घोषणा NDIV_MAX	125
#घोषणा ODF_MIN		1
#घोषणा ODF_MAX		8

/* dsi color क्रमmat coding according to the datasheet */
क्रमागत dsi_color अणु
	DSI_RGB565_CONF1,
	DSI_RGB565_CONF2,
	DSI_RGB565_CONF3,
	DSI_RGB666_CONF1,
	DSI_RGB666_CONF2,
	DSI_RGB888,
पूर्ण;

#घोषणा LANE_MIN_KBPS	31250
#घोषणा LANE_MAX_KBPS	500000

/* Sleep & समयout क्रम regulator on/off, pll lock/unlock & fअगरo empty */
#घोषणा SLEEP_US	1000
#घोषणा TIMEOUT_US	200000

काष्ठा dw_mipi_dsi_sपंचांग अणु
	व्योम __iomem *base;
	काष्ठा clk *pllref_clk;
	काष्ठा dw_mipi_dsi *dsi;
	u32 hw_version;
	पूर्णांक lane_min_kbps;
	पूर्णांक lane_max_kbps;
	काष्ठा regulator *vdd_supply;
पूर्ण;

अटल अंतरभूत व्योम dsi_ग_लिखो(काष्ठा dw_mipi_dsi_sपंचांग *dsi, u32 reg, u32 val)
अणु
	ग_लिखोl(val, dsi->base + reg);
पूर्ण

अटल अंतरभूत u32 dsi_पढ़ो(काष्ठा dw_mipi_dsi_sपंचांग *dsi, u32 reg)
अणु
	वापस पढ़ोl(dsi->base + reg);
पूर्ण

अटल अंतरभूत व्योम dsi_set(काष्ठा dw_mipi_dsi_sपंचांग *dsi, u32 reg, u32 mask)
अणु
	dsi_ग_लिखो(dsi, reg, dsi_पढ़ो(dsi, reg) | mask);
पूर्ण

अटल अंतरभूत व्योम dsi_clear(काष्ठा dw_mipi_dsi_sपंचांग *dsi, u32 reg, u32 mask)
अणु
	dsi_ग_लिखो(dsi, reg, dsi_पढ़ो(dsi, reg) & ~mask);
पूर्ण

अटल अंतरभूत व्योम dsi_update_bits(काष्ठा dw_mipi_dsi_sपंचांग *dsi, u32 reg,
				   u32 mask, u32 val)
अणु
	dsi_ग_लिखो(dsi, reg, (dsi_पढ़ो(dsi, reg) & ~mask) | val);
पूर्ण

अटल क्रमागत dsi_color dsi_color_from_mipi(क्रमागत mipi_dsi_pixel_क्रमmat fmt)
अणु
	चयन (fmt) अणु
	हाल MIPI_DSI_FMT_RGB888:
		वापस DSI_RGB888;
	हाल MIPI_DSI_FMT_RGB666:
		वापस DSI_RGB666_CONF2;
	हाल MIPI_DSI_FMT_RGB666_PACKED:
		वापस DSI_RGB666_CONF1;
	हाल MIPI_DSI_FMT_RGB565:
		वापस DSI_RGB565_CONF1;
	शेष:
		DRM_DEBUG_DRIVER("MIPI color invalid, so we use rgb888\n");
	पूर्ण
	वापस DSI_RGB888;
पूर्ण

अटल पूर्णांक dsi_pll_get_clkout_khz(पूर्णांक clkin_khz, पूर्णांक idf, पूर्णांक nभाग, पूर्णांक odf)
अणु
	पूर्णांक भागisor = idf * odf;

	/* prevent from भागision by 0 */
	अगर (!भागisor)
		वापस 0;

	वापस DIV_ROUND_CLOSEST(clkin_khz * nभाग, भागisor);
पूर्ण

अटल पूर्णांक dsi_pll_get_params(काष्ठा dw_mipi_dsi_sपंचांग *dsi,
			      पूर्णांक clkin_khz, पूर्णांक clkout_khz,
			      पूर्णांक *idf, पूर्णांक *nभाग, पूर्णांक *odf)
अणु
	पूर्णांक i, o, n, n_min, n_max;
	पूर्णांक fvco_min, fvco_max, delta, best_delta; /* all in khz */

	/* Early checks preventing भागision by 0 & odd results */
	अगर (clkin_khz <= 0 || clkout_khz <= 0)
		वापस -EINVAL;

	fvco_min = dsi->lane_min_kbps * 2 * ODF_MAX;
	fvco_max = dsi->lane_max_kbps * 2 * ODF_MIN;

	best_delta = 1000000; /* big started value (1000000khz) */

	क्रम (i = IDF_MIN; i <= IDF_MAX; i++) अणु
		/* Compute nभाग range according to Fvco */
		n_min = ((fvco_min * i) / (2 * clkin_khz)) + 1;
		n_max = (fvco_max * i) / (2 * clkin_khz);

		/* No need to जारी idf loop अगर we reach nभाग max */
		अगर (n_min >= NDIV_MAX)
			अवरोध;

		/* Clamp nभाग to valid values */
		अगर (n_min < NDIV_MIN)
			n_min = NDIV_MIN;
		अगर (n_max > NDIV_MAX)
			n_max = NDIV_MAX;

		क्रम (o = ODF_MIN; o <= ODF_MAX; o *= 2) अणु
			n = DIV_ROUND_CLOSEST(i * o * clkout_khz, clkin_khz);
			/* Check nभाग according to vco range */
			अगर (n < n_min || n > n_max)
				जारी;
			/* Check अगर new delta is better & saves parameters */
			delta = dsi_pll_get_clkout_khz(clkin_khz, i, n, o) -
				clkout_khz;
			अगर (delta < 0)
				delta = -delta;
			अगर (delta < best_delta) अणु
				*idf = i;
				*nभाग = n;
				*odf = o;
				best_delta = delta;
			पूर्ण
			/* fast वापस in हाल of "perfect result" */
			अगर (!delta)
				वापस 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dw_mipi_dsi_phy_init(व्योम *priv_data)
अणु
	काष्ठा dw_mipi_dsi_sपंचांग *dsi = priv_data;
	u32 val;
	पूर्णांक ret;

	/* Enable the regulator */
	dsi_set(dsi, DSI_WRPCR, WRPCR_REGEN | WRPCR_BGREN);
	ret = पढ़ोl_poll_समयout(dsi->base + DSI_WISR, val, val & WISR_RRS,
				 SLEEP_US, TIMEOUT_US);
	अगर (ret)
		DRM_DEBUG_DRIVER("!TIMEOUT! waiting REGU, let's continue\n");

	/* Enable the DSI PLL & रुको क्रम its lock */
	dsi_set(dsi, DSI_WRPCR, WRPCR_PLLEN);
	ret = पढ़ोl_poll_समयout(dsi->base + DSI_WISR, val, val & WISR_PLLLS,
				 SLEEP_US, TIMEOUT_US);
	अगर (ret)
		DRM_DEBUG_DRIVER("!TIMEOUT! waiting PLL, let's continue\n");

	वापस 0;
पूर्ण

अटल व्योम dw_mipi_dsi_phy_घातer_on(व्योम *priv_data)
अणु
	काष्ठा dw_mipi_dsi_sपंचांग *dsi = priv_data;

	DRM_DEBUG_DRIVER("\n");

	/* Enable the DSI wrapper */
	dsi_set(dsi, DSI_WCR, WCR_DSIEN);
पूर्ण

अटल व्योम dw_mipi_dsi_phy_घातer_off(व्योम *priv_data)
अणु
	काष्ठा dw_mipi_dsi_sपंचांग *dsi = priv_data;

	DRM_DEBUG_DRIVER("\n");

	/* Disable the DSI wrapper */
	dsi_clear(dsi, DSI_WCR, WCR_DSIEN);
पूर्ण

अटल पूर्णांक
dw_mipi_dsi_get_lane_mbps(व्योम *priv_data, स्थिर काष्ठा drm_display_mode *mode,
			  अचिन्हित दीर्घ mode_flags, u32 lanes, u32 क्रमmat,
			  अचिन्हित पूर्णांक *lane_mbps)
अणु
	काष्ठा dw_mipi_dsi_sपंचांग *dsi = priv_data;
	अचिन्हित पूर्णांक idf, nभाग, odf, pll_in_khz, pll_out_khz;
	पूर्णांक ret, bpp;
	u32 val;

	/* Update lane capabilities according to hw version */
	dsi->lane_min_kbps = LANE_MIN_KBPS;
	dsi->lane_max_kbps = LANE_MAX_KBPS;
	अगर (dsi->hw_version == HWVER_131) अणु
		dsi->lane_min_kbps *= 2;
		dsi->lane_max_kbps *= 2;
	पूर्ण

	pll_in_khz = (अचिन्हित पूर्णांक)(clk_get_rate(dsi->pllref_clk) / 1000);

	/* Compute requested pll out */
	bpp = mipi_dsi_pixel_क्रमmat_to_bpp(क्रमmat);
	pll_out_khz = mode->घड़ी * bpp / lanes;

	/* Add 20% to pll out to be higher than pixel bw (burst mode only) */
	अगर (mode_flags & MIPI_DSI_MODE_VIDEO_BURST)
		pll_out_khz = (pll_out_khz * 12) / 10;

	अगर (pll_out_khz > dsi->lane_max_kbps) अणु
		pll_out_khz = dsi->lane_max_kbps;
		DRM_WARN("Warning max phy mbps is used\n");
	पूर्ण
	अगर (pll_out_khz < dsi->lane_min_kbps) अणु
		pll_out_khz = dsi->lane_min_kbps;
		DRM_WARN("Warning min phy mbps is used\n");
	पूर्ण

	/* Compute best pll parameters */
	idf = 0;
	nभाग = 0;
	odf = 0;
	ret = dsi_pll_get_params(dsi, pll_in_khz, pll_out_khz,
				 &idf, &nभाग, &odf);
	अगर (ret)
		DRM_WARN("Warning dsi_pll_get_params(): bad params\n");

	/* Get the adjusted pll out value */
	pll_out_khz = dsi_pll_get_clkout_khz(pll_in_khz, idf, nभाग, odf);

	/* Set the PLL भागision factors */
	dsi_update_bits(dsi, DSI_WRPCR,	WRPCR_NDIV | WRPCR_IDF | WRPCR_ODF,
			(nभाग << 2) | (idf << 11) | ((ffs(odf) - 1) << 16));

	/* Compute uix4 & set the bit period in high-speed mode */
	val = 4000000 / pll_out_khz;
	dsi_update_bits(dsi, DSI_WPCR0, WPCR0_UIX4, val);

	/* Select video mode by resetting DSIM bit */
	dsi_clear(dsi, DSI_WCFGR, WCFGR_DSIM);

	/* Select the color coding */
	dsi_update_bits(dsi, DSI_WCFGR, WCFGR_COLMUX,
			dsi_color_from_mipi(क्रमmat) << 1);

	*lane_mbps = pll_out_khz / 1000;

	DRM_DEBUG_DRIVER("pll_in %ukHz pll_out %ukHz lane_mbps %uMHz\n",
			 pll_in_khz, pll_out_khz, *lane_mbps);

	वापस 0;
पूर्ण

अटल पूर्णांक
dw_mipi_dsi_phy_get_timing(व्योम *priv_data, अचिन्हित पूर्णांक lane_mbps,
			   काष्ठा dw_mipi_dsi_dphy_timing *timing)
अणु
	timing->clk_hs2lp = 0x40;
	timing->clk_lp2hs = 0x40;
	timing->data_hs2lp = 0x40;
	timing->data_lp2hs = 0x40;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dw_mipi_dsi_phy_ops dw_mipi_dsi_sपंचांग_phy_ops = अणु
	.init = dw_mipi_dsi_phy_init,
	.घातer_on = dw_mipi_dsi_phy_घातer_on,
	.घातer_off = dw_mipi_dsi_phy_घातer_off,
	.get_lane_mbps = dw_mipi_dsi_get_lane_mbps,
	.get_timing = dw_mipi_dsi_phy_get_timing,
पूर्ण;

अटल काष्ठा dw_mipi_dsi_plat_data dw_mipi_dsi_sपंचांग_plat_data = अणु
	.max_data_lanes = 2,
	.phy_ops = &dw_mipi_dsi_sपंचांग_phy_ops,
पूर्ण;

अटल स्थिर काष्ठा of_device_id dw_mipi_dsi_sपंचांग_dt_ids[] = अणु
	अणु .compatible = "st,stm32-dsi", .data = &dw_mipi_dsi_sपंचांग_plat_data, पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, dw_mipi_dsi_sपंचांग_dt_ids);

अटल पूर्णांक dw_mipi_dsi_sपंचांग_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा dw_mipi_dsi_sपंचांग *dsi;
	काष्ठा clk *pclk;
	काष्ठा resource *res;
	पूर्णांक ret;

	dsi = devm_kzalloc(dev, माप(*dsi), GFP_KERNEL);
	अगर (!dsi)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	dsi->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(dsi->base)) अणु
		ret = PTR_ERR(dsi->base);
		DRM_ERROR("Unable to get dsi registers %d\n", ret);
		वापस ret;
	पूर्ण

	dsi->vdd_supply = devm_regulator_get(dev, "phy-dsi");
	अगर (IS_ERR(dsi->vdd_supply)) अणु
		ret = PTR_ERR(dsi->vdd_supply);
		dev_err_probe(dev, ret, "Failed to request regulator\n");
		वापस ret;
	पूर्ण

	ret = regulator_enable(dsi->vdd_supply);
	अगर (ret) अणु
		DRM_ERROR("Failed to enable regulator: %d\n", ret);
		वापस ret;
	पूर्ण

	dsi->pllref_clk = devm_clk_get(dev, "ref");
	अगर (IS_ERR(dsi->pllref_clk)) अणु
		ret = PTR_ERR(dsi->pllref_clk);
		dev_err_probe(dev, ret, "Unable to get pll reference clock\n");
		जाओ err_clk_get;
	पूर्ण

	ret = clk_prepare_enable(dsi->pllref_clk);
	अगर (ret) अणु
		DRM_ERROR("Failed to enable pllref_clk: %d\n", ret);
		जाओ err_clk_get;
	पूर्ण

	pclk = devm_clk_get(dev, "pclk");
	अगर (IS_ERR(pclk)) अणु
		ret = PTR_ERR(pclk);
		DRM_ERROR("Unable to get peripheral clock: %d\n", ret);
		जाओ err_dsi_probe;
	पूर्ण

	ret = clk_prepare_enable(pclk);
	अगर (ret) अणु
		DRM_ERROR("%s: Failed to enable peripheral clk\n", __func__);
		जाओ err_dsi_probe;
	पूर्ण

	dsi->hw_version = dsi_पढ़ो(dsi, DSI_VERSION) & VERSION;
	clk_disable_unprepare(pclk);

	अगर (dsi->hw_version != HWVER_130 && dsi->hw_version != HWVER_131) अणु
		ret = -ENODEV;
		DRM_ERROR("bad dsi hardware version\n");
		जाओ err_dsi_probe;
	पूर्ण

	dw_mipi_dsi_sपंचांग_plat_data.base = dsi->base;
	dw_mipi_dsi_sपंचांग_plat_data.priv_data = dsi;

	platक्रमm_set_drvdata(pdev, dsi);

	dsi->dsi = dw_mipi_dsi_probe(pdev, &dw_mipi_dsi_sपंचांग_plat_data);
	अगर (IS_ERR(dsi->dsi)) अणु
		ret = PTR_ERR(dsi->dsi);
		dev_err_probe(dev, ret, "Failed to initialize mipi dsi host\n");
		जाओ err_dsi_probe;
	पूर्ण

	वापस 0;

err_dsi_probe:
	clk_disable_unprepare(dsi->pllref_clk);
err_clk_get:
	regulator_disable(dsi->vdd_supply);

	वापस ret;
पूर्ण

अटल पूर्णांक dw_mipi_dsi_sपंचांग_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dw_mipi_dsi_sपंचांग *dsi = platक्रमm_get_drvdata(pdev);

	dw_mipi_dsi_हटाओ(dsi->dsi);
	clk_disable_unprepare(dsi->pllref_clk);
	regulator_disable(dsi->vdd_supply);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused dw_mipi_dsi_sपंचांग_suspend(काष्ठा device *dev)
अणु
	काष्ठा dw_mipi_dsi_sपंचांग *dsi = dw_mipi_dsi_sपंचांग_plat_data.priv_data;

	DRM_DEBUG_DRIVER("\n");

	clk_disable_unprepare(dsi->pllref_clk);
	regulator_disable(dsi->vdd_supply);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused dw_mipi_dsi_sपंचांग_resume(काष्ठा device *dev)
अणु
	काष्ठा dw_mipi_dsi_sपंचांग *dsi = dw_mipi_dsi_sपंचांग_plat_data.priv_data;
	पूर्णांक ret;

	DRM_DEBUG_DRIVER("\n");

	ret = regulator_enable(dsi->vdd_supply);
	अगर (ret) अणु
		DRM_ERROR("Failed to enable regulator: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(dsi->pllref_clk);
	अगर (ret) अणु
		regulator_disable(dsi->vdd_supply);
		DRM_ERROR("Failed to enable pllref_clk: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops dw_mipi_dsi_sपंचांग_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(dw_mipi_dsi_sपंचांग_suspend,
				dw_mipi_dsi_sपंचांग_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver dw_mipi_dsi_sपंचांग_driver = अणु
	.probe		= dw_mipi_dsi_sपंचांग_probe,
	.हटाओ		= dw_mipi_dsi_sपंचांग_हटाओ,
	.driver		= अणु
		.of_match_table = dw_mipi_dsi_sपंचांग_dt_ids,
		.name	= "stm32-display-dsi",
		.pm = &dw_mipi_dsi_sपंचांग_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(dw_mipi_dsi_sपंचांग_driver);

MODULE_AUTHOR("Philippe Cornu <philippe.cornu@st.com>");
MODULE_AUTHOR("Yannick Fertre <yannick.fertre@st.com>");
MODULE_DESCRIPTION("STMicroelectronics DW MIPI DSI host controller driver");
MODULE_LICENSE("GPL v2");
