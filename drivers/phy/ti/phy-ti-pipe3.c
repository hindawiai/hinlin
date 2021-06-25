<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * phy-ti-pipe3 - PIPE3 PHY driver.
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com
 * Author: Kishon Vijay Abraham I <kishon@ti.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/of.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/delay.h>
#समावेश <linux/phy/omap_control_phy.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>

#घोषणा	PLL_STATUS		0x00000004
#घोषणा	PLL_GO			0x00000008
#घोषणा	PLL_CONFIGURATION1	0x0000000C
#घोषणा	PLL_CONFIGURATION2	0x00000010
#घोषणा	PLL_CONFIGURATION3	0x00000014
#घोषणा	PLL_CONFIGURATION4	0x00000020

#घोषणा	PLL_REGM_MASK		0x001FFE00
#घोषणा	PLL_REGM_SHIFT		0x9
#घोषणा	PLL_REGM_F_MASK		0x0003FFFF
#घोषणा	PLL_REGM_F_SHIFT	0x0
#घोषणा	PLL_REGN_MASK		0x000001FE
#घोषणा	PLL_REGN_SHIFT		0x1
#घोषणा	PLL_SELFREQDCO_MASK	0x0000000E
#घोषणा	PLL_SELFREQDCO_SHIFT	0x1
#घोषणा	PLL_SD_MASK		0x0003FC00
#घोषणा	PLL_SD_SHIFT		10
#घोषणा	SET_PLL_GO		0x1
#घोषणा PLL_LDOPWDN		BIT(15)
#घोषणा PLL_TICOPWDN		BIT(16)
#घोषणा	PLL_LOCK		0x2
#घोषणा	PLL_IDLE		0x1

#घोषणा SATA_PLL_SOFT_RESET	BIT(18)

#घोषणा PIPE3_PHY_PWRCTL_CLK_CMD_MASK	GENMASK(21, 14)
#घोषणा PIPE3_PHY_PWRCTL_CLK_CMD_SHIFT	14

#घोषणा PIPE3_PHY_PWRCTL_CLK_FREQ_MASK	GENMASK(31, 22)
#घोषणा PIPE3_PHY_PWRCTL_CLK_FREQ_SHIFT	22

#घोषणा PIPE3_PHY_RX_POWERON       (0x1 << PIPE3_PHY_PWRCTL_CLK_CMD_SHIFT)
#घोषणा PIPE3_PHY_TX_POWERON       (0x2 << PIPE3_PHY_PWRCTL_CLK_CMD_SHIFT)

#घोषणा PCIE_PCS_MASK			0xFF0000
#घोषणा PCIE_PCS_DELAY_COUNT_SHIFT	0x10

#घोषणा PIPE3_PHY_RX_ANA_PROGRAMMABILITY	0x0000000C
#घोषणा INTERFACE_MASK			GENMASK(31, 27)
#घोषणा INTERFACE_SHIFT			27
#घोषणा INTERFACE_MODE_USBSS		BIT(4)
#घोषणा INTERFACE_MODE_SATA_1P5		BIT(3)
#घोषणा INTERFACE_MODE_SATA_3P0		BIT(2)
#घोषणा INTERFACE_MODE_PCIE		BIT(0)

#घोषणा LOSD_MASK			GENMASK(17, 14)
#घोषणा LOSD_SHIFT			14
#घोषणा MEM_PLLDIV			GENMASK(6, 5)

#घोषणा PIPE3_PHY_RX_TRIM		0x0000001C
#घोषणा MEM_DLL_TRIM_SEL_MASK		GENMASK(31, 30)
#घोषणा MEM_DLL_TRIM_SHIFT		30

#घोषणा PIPE3_PHY_RX_DLL		0x00000024
#घोषणा MEM_DLL_PHINT_RATE_MASK		GENMASK(31, 30)
#घोषणा MEM_DLL_PHINT_RATE_SHIFT	30

#घोषणा PIPE3_PHY_RX_DIGITAL_MODES		0x00000028
#घोषणा MEM_HS_RATE_MASK		GENMASK(28, 27)
#घोषणा MEM_HS_RATE_SHIFT		27
#घोषणा MEM_OVRD_HS_RATE		BIT(26)
#घोषणा MEM_OVRD_HS_RATE_SHIFT		26
#घोषणा MEM_CDR_FASTLOCK		BIT(23)
#घोषणा MEM_CDR_FASTLOCK_SHIFT		23
#घोषणा MEM_CDR_LBW_MASK		GENMASK(22, 21)
#घोषणा MEM_CDR_LBW_SHIFT		21
#घोषणा MEM_CDR_STEPCNT_MASK		GENMASK(20, 19)
#घोषणा MEM_CDR_STEPCNT_SHIFT		19
#घोषणा MEM_CDR_STL_MASK		GENMASK(18, 16)
#घोषणा MEM_CDR_STL_SHIFT		16
#घोषणा MEM_CDR_THR_MASK		GENMASK(15, 13)
#घोषणा MEM_CDR_THR_SHIFT		13
#घोषणा MEM_CDR_THR_MODE		BIT(12)
#घोषणा MEM_CDR_THR_MODE_SHIFT		12
#घोषणा MEM_CDR_2NDO_SDM_MODE		BIT(11)
#घोषणा MEM_CDR_2NDO_SDM_MODE_SHIFT	11

#घोषणा PIPE3_PHY_RX_EQUALIZER		0x00000038
#घोषणा MEM_EQLEV_MASK			GENMASK(31, 16)
#घोषणा MEM_EQLEV_SHIFT			16
#घोषणा MEM_EQFTC_MASK			GENMASK(15, 11)
#घोषणा MEM_EQFTC_SHIFT			11
#घोषणा MEM_EQCTL_MASK			GENMASK(10, 7)
#घोषणा MEM_EQCTL_SHIFT			7
#घोषणा MEM_OVRD_EQLEV			BIT(2)
#घोषणा MEM_OVRD_EQLEV_SHIFT		2
#घोषणा MEM_OVRD_EQFTC			BIT(1)
#घोषणा MEM_OVRD_EQFTC_SHIFT		1

#घोषणा SATA_PHY_RX_IO_AND_A2D_OVERRIDES	0x44
#घोषणा MEM_CDR_LOS_SOURCE_MASK		GENMASK(10, 9)
#घोषणा MEM_CDR_LOS_SOURCE_SHIFT	9

/*
 * This is an Empirical value that works, need to confirm the actual
 * value required क्रम the PIPE3PHY_PLL_CONFIGURATION2.PLL_IDLE status
 * to be correctly reflected in the PIPE3PHY_PLL_STATUS रेजिस्टर.
 */
#घोषणा PLL_IDLE_TIME	100	/* in milliseconds */
#घोषणा PLL_LOCK_TIME	100	/* in milliseconds */

क्रमागत pipe3_mode अणु PIPE3_MODE_PCIE = 1,
		  PIPE3_MODE_SATA,
		  PIPE3_MODE_USBSS पूर्ण;

काष्ठा pipe3_dpll_params अणु
	u16	m;
	u8	n;
	u8	freq:3;
	u8	sd;
	u32	mf;
पूर्ण;

काष्ठा pipe3_dpll_map अणु
	अचिन्हित दीर्घ rate;
	काष्ठा pipe3_dpll_params params;
पूर्ण;

काष्ठा pipe3_settings अणु
	u8 ana_पूर्णांकerface;
	u8 ana_losd;
	u8 dig_fastlock;
	u8 dig_lbw;
	u8 dig_stepcnt;
	u8 dig_stl;
	u8 dig_thr;
	u8 dig_thr_mode;
	u8 dig_2nकरो_sdm_mode;
	u8 dig_hs_rate;
	u8 dig_ovrd_hs_rate;
	u8 dll_trim_sel;
	u8 dll_phपूर्णांक_rate;
	u8 eq_lev;
	u8 eq_ftc;
	u8 eq_ctl;
	u8 eq_ovrd_lev;
	u8 eq_ovrd_ftc;
पूर्ण;

काष्ठा ti_pipe3 अणु
	व्योम __iomem		*pll_ctrl_base;
	व्योम __iomem		*phy_rx;
	व्योम __iomem		*phy_tx;
	काष्ठा device		*dev;
	काष्ठा device		*control_dev;
	काष्ठा clk		*wkupclk;
	काष्ठा clk		*sys_clk;
	काष्ठा clk		*refclk;
	काष्ठा clk		*भाग_clk;
	काष्ठा pipe3_dpll_map	*dpll_map;
	काष्ठा regmap		*phy_घातer_syscon; /* ctrl. reg. acces */
	काष्ठा regmap		*pcs_syscon; /* ctrl. reg. acces */
	काष्ठा regmap		*dpll_reset_syscon; /* ctrl. reg. acces */
	अचिन्हित पूर्णांक		dpll_reset_reg; /* reg. index within syscon */
	अचिन्हित पूर्णांक		घातer_reg; /* घातer reg. index within syscon */
	अचिन्हित पूर्णांक		pcie_pcs_reg; /* pcs reg. index in syscon */
	bool			sata_refclk_enabled;
	क्रमागत pipe3_mode		mode;
	काष्ठा pipe3_settings	settings;
पूर्ण;

अटल काष्ठा pipe3_dpll_map dpll_map_usb[] = अणु
	अणु12000000, अणु1250, 5, 4, 20, 0पूर्ण पूर्ण,	/* 12 MHz */
	अणु16800000, अणु3125, 20, 4, 20, 0पूर्ण पूर्ण,	/* 16.8 MHz */
	अणु19200000, अणु1172, 8, 4, 20, 65537पूर्ण पूर्ण,	/* 19.2 MHz */
	अणु20000000, अणु1000, 7, 4, 10, 0पूर्ण पूर्ण,	/* 20 MHz */
	अणु26000000, अणु1250, 12, 4, 20, 0पूर्ण पूर्ण,	/* 26 MHz */
	अणु38400000, अणु3125, 47, 4, 20, 92843पूर्ण पूर्ण,	/* 38.4 MHz */
	अणु पूर्ण,					/* Terminator */
पूर्ण;

अटल काष्ठा pipe3_dpll_map dpll_map_sata[] = अणु
	अणु12000000, अणु625, 4, 4, 6, 0पूर्ण पूर्ण,	/* 12 MHz */
	अणु16800000, अणु625, 6, 4, 7, 0पूर्ण पूर्ण,		/* 16.8 MHz */
	अणु19200000, अणु625, 7, 4, 6, 0पूर्ण पूर्ण,		/* 19.2 MHz */
	अणु20000000, अणु750, 9, 4, 6, 0पूर्ण पूर्ण,		/* 20 MHz */
	अणु26000000, अणु750, 12, 4, 6, 0पूर्ण पूर्ण,	/* 26 MHz */
	अणु38400000, अणु625, 15, 4, 6, 0पूर्ण पूर्ण,	/* 38.4 MHz */
	अणु पूर्ण,					/* Terminator */
पूर्ण;

काष्ठा pipe3_data अणु
	क्रमागत pipe3_mode mode;
	काष्ठा pipe3_dpll_map *dpll_map;
	काष्ठा pipe3_settings settings;
पूर्ण;

अटल काष्ठा pipe3_data data_usb = अणु
	.mode = PIPE3_MODE_USBSS,
	.dpll_map = dpll_map_usb,
	.settings = अणु
	/* DRA75x TRM Table 26-17 Preferred USB3_PHY_RX SCP Register Settings */
		.ana_पूर्णांकerface = INTERFACE_MODE_USBSS,
		.ana_losd = 0xa,
		.dig_fastlock = 1,
		.dig_lbw = 3,
		.dig_stepcnt = 0,
		.dig_stl = 0x3,
		.dig_thr = 1,
		.dig_thr_mode = 1,
		.dig_2nकरो_sdm_mode = 0,
		.dig_hs_rate = 0,
		.dig_ovrd_hs_rate = 1,
		.dll_trim_sel = 0x2,
		.dll_phपूर्णांक_rate = 0x3,
		.eq_lev = 0,
		.eq_ftc = 0,
		.eq_ctl = 0x9,
		.eq_ovrd_lev = 0,
		.eq_ovrd_ftc = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा pipe3_data data_sata = अणु
	.mode = PIPE3_MODE_SATA,
	.dpll_map = dpll_map_sata,
	.settings = अणु
	/* DRA75x TRM Table 26-9 Preferred SATA_PHY_RX SCP Register Settings */
		.ana_पूर्णांकerface = INTERFACE_MODE_SATA_3P0,
		.ana_losd = 0x5,
		.dig_fastlock = 1,
		.dig_lbw = 3,
		.dig_stepcnt = 0,
		.dig_stl = 0x3,
		.dig_thr = 1,
		.dig_thr_mode = 1,
		.dig_2nकरो_sdm_mode = 0,
		.dig_hs_rate = 0,	/* Not in TRM preferred settings */
		.dig_ovrd_hs_rate = 0,	/* Not in TRM preferred settings */
		.dll_trim_sel = 0x1,
		.dll_phपूर्णांक_rate = 0x2,	/* क्रम 1.5 GHz DPLL घड़ी */
		.eq_lev = 0,
		.eq_ftc = 0x1f,
		.eq_ctl = 0,
		.eq_ovrd_lev = 1,
		.eq_ovrd_ftc = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा pipe3_data data_pcie = अणु
	.mode = PIPE3_MODE_PCIE,
	.settings = अणु
	/* DRA75x TRM Table 26-62 Preferred PCIe_PHY_RX SCP Register Settings */
		.ana_पूर्णांकerface = INTERFACE_MODE_PCIE,
		.ana_losd = 0xa,
		.dig_fastlock = 1,
		.dig_lbw = 3,
		.dig_stepcnt = 0,
		.dig_stl = 0x3,
		.dig_thr = 1,
		.dig_thr_mode = 1,
		.dig_2nकरो_sdm_mode = 0,
		.dig_hs_rate = 0,
		.dig_ovrd_hs_rate = 0,
		.dll_trim_sel = 0x2,
		.dll_phपूर्णांक_rate = 0x3,
		.eq_lev = 0,
		.eq_ftc = 0x1f,
		.eq_ctl = 1,
		.eq_ovrd_lev = 0,
		.eq_ovrd_ftc = 0,
	पूर्ण,
पूर्ण;

अटल अंतरभूत u32 ti_pipe3_पढ़ोl(व्योम __iomem *addr, अचिन्हित offset)
अणु
	वापस __raw_पढ़ोl(addr + offset);
पूर्ण

अटल अंतरभूत व्योम ti_pipe3_ग_लिखोl(व्योम __iomem *addr, अचिन्हित offset,
	u32 data)
अणु
	__raw_ग_लिखोl(data, addr + offset);
पूर्ण

अटल काष्ठा pipe3_dpll_params *ti_pipe3_get_dpll_params(काष्ठा ti_pipe3 *phy)
अणु
	अचिन्हित दीर्घ rate;
	काष्ठा pipe3_dpll_map *dpll_map = phy->dpll_map;

	rate = clk_get_rate(phy->sys_clk);

	क्रम (; dpll_map->rate; dpll_map++) अणु
		अगर (rate == dpll_map->rate)
			वापस &dpll_map->params;
	पूर्ण

	dev_err(phy->dev, "No DPLL configuration for %lu Hz SYS CLK\n", rate);

	वापस शून्य;
पूर्ण

अटल पूर्णांक ti_pipe3_enable_घड़ीs(काष्ठा ti_pipe3 *phy);
अटल व्योम ti_pipe3_disable_घड़ीs(काष्ठा ti_pipe3 *phy);

अटल पूर्णांक ti_pipe3_घातer_off(काष्ठा phy *x)
अणु
	पूर्णांक ret;
	काष्ठा ti_pipe3 *phy = phy_get_drvdata(x);

	अगर (!phy->phy_घातer_syscon) अणु
		omap_control_phy_घातer(phy->control_dev, 0);
		वापस 0;
	पूर्ण

	ret = regmap_update_bits(phy->phy_घातer_syscon, phy->घातer_reg,
				 PIPE3_PHY_PWRCTL_CLK_CMD_MASK, 0);
	वापस ret;
पूर्ण

अटल व्योम ti_pipe3_calibrate(काष्ठा ti_pipe3 *phy);

अटल पूर्णांक ti_pipe3_घातer_on(काष्ठा phy *x)
अणु
	u32 val;
	u32 mask;
	अचिन्हित दीर्घ rate;
	काष्ठा ti_pipe3 *phy = phy_get_drvdata(x);
	bool rx_pending = false;

	अगर (!phy->phy_घातer_syscon) अणु
		omap_control_phy_घातer(phy->control_dev, 1);
		वापस 0;
	पूर्ण

	rate = clk_get_rate(phy->sys_clk);
	अगर (!rate) अणु
		dev_err(phy->dev, "Invalid clock rate\n");
		वापस -EINVAL;
	पूर्ण
	rate = rate / 1000000;
	mask = OMAP_CTRL_PIPE3_PHY_PWRCTL_CLK_FREQ_MASK;
	val = rate << OMAP_CTRL_PIPE3_PHY_PWRCTL_CLK_FREQ_SHIFT;
	regmap_update_bits(phy->phy_घातer_syscon, phy->घातer_reg,
			   mask, val);
	/*
	 * For PCIe, TX and RX must be घातered on simultaneously.
	 * For USB and SATA, TX must be घातered on beक्रमe RX
	 */
	mask = OMAP_CTRL_PIPE3_PHY_PWRCTL_CLK_CMD_MASK;
	अगर (phy->mode == PIPE3_MODE_SATA || phy->mode == PIPE3_MODE_USBSS) अणु
		val = PIPE3_PHY_TX_POWERON;
		rx_pending = true;
	पूर्ण अन्यथा अणु
		val = PIPE3_PHY_TX_POWERON | PIPE3_PHY_RX_POWERON;
	पूर्ण

	regmap_update_bits(phy->phy_घातer_syscon, phy->घातer_reg,
			   mask, val);

	अगर (rx_pending) अणु
		val = PIPE3_PHY_TX_POWERON | PIPE3_PHY_RX_POWERON;
		regmap_update_bits(phy->phy_घातer_syscon, phy->घातer_reg,
				   mask, val);
	पूर्ण

	अगर (phy->mode == PIPE3_MODE_PCIE)
		ti_pipe3_calibrate(phy);

	वापस 0;
पूर्ण

अटल पूर्णांक ti_pipe3_dpll_रुको_lock(काष्ठा ti_pipe3 *phy)
अणु
	u32		val;
	अचिन्हित दीर्घ	समयout;

	समयout = jअगरfies + msecs_to_jअगरfies(PLL_LOCK_TIME);
	करो अणु
		cpu_relax();
		val = ti_pipe3_पढ़ोl(phy->pll_ctrl_base, PLL_STATUS);
		अगर (val & PLL_LOCK)
			वापस 0;
	पूर्ण जबतक (!समय_after(jअगरfies, समयout));

	dev_err(phy->dev, "DPLL failed to lock\n");
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक ti_pipe3_dpll_program(काष्ठा ti_pipe3 *phy)
अणु
	u32			val;
	काष्ठा pipe3_dpll_params *dpll_params;

	dpll_params = ti_pipe3_get_dpll_params(phy);
	अगर (!dpll_params)
		वापस -EINVAL;

	val = ti_pipe3_पढ़ोl(phy->pll_ctrl_base, PLL_CONFIGURATION1);
	val &= ~PLL_REGN_MASK;
	val |= dpll_params->n << PLL_REGN_SHIFT;
	ti_pipe3_ग_लिखोl(phy->pll_ctrl_base, PLL_CONFIGURATION1, val);

	val = ti_pipe3_पढ़ोl(phy->pll_ctrl_base, PLL_CONFIGURATION2);
	val &= ~PLL_SELFREQDCO_MASK;
	val |= dpll_params->freq << PLL_SELFREQDCO_SHIFT;
	ti_pipe3_ग_लिखोl(phy->pll_ctrl_base, PLL_CONFIGURATION2, val);

	val = ti_pipe3_पढ़ोl(phy->pll_ctrl_base, PLL_CONFIGURATION1);
	val &= ~PLL_REGM_MASK;
	val |= dpll_params->m << PLL_REGM_SHIFT;
	ti_pipe3_ग_लिखोl(phy->pll_ctrl_base, PLL_CONFIGURATION1, val);

	val = ti_pipe3_पढ़ोl(phy->pll_ctrl_base, PLL_CONFIGURATION4);
	val &= ~PLL_REGM_F_MASK;
	val |= dpll_params->mf << PLL_REGM_F_SHIFT;
	ti_pipe3_ग_लिखोl(phy->pll_ctrl_base, PLL_CONFIGURATION4, val);

	val = ti_pipe3_पढ़ोl(phy->pll_ctrl_base, PLL_CONFIGURATION3);
	val &= ~PLL_SD_MASK;
	val |= dpll_params->sd << PLL_SD_SHIFT;
	ti_pipe3_ग_लिखोl(phy->pll_ctrl_base, PLL_CONFIGURATION3, val);

	ti_pipe3_ग_लिखोl(phy->pll_ctrl_base, PLL_GO, SET_PLL_GO);

	वापस ti_pipe3_dpll_रुको_lock(phy);
पूर्ण

अटल व्योम ti_pipe3_calibrate(काष्ठा ti_pipe3 *phy)
अणु
	u32 val;
	काष्ठा pipe3_settings *s = &phy->settings;

	val = ti_pipe3_पढ़ोl(phy->phy_rx, PIPE3_PHY_RX_ANA_PROGRAMMABILITY);
	val &= ~(INTERFACE_MASK | LOSD_MASK | MEM_PLLDIV);
	val |= (s->ana_पूर्णांकerface << INTERFACE_SHIFT | s->ana_losd << LOSD_SHIFT);
	ti_pipe3_ग_लिखोl(phy->phy_rx, PIPE3_PHY_RX_ANA_PROGRAMMABILITY, val);

	val = ti_pipe3_पढ़ोl(phy->phy_rx, PIPE3_PHY_RX_DIGITAL_MODES);
	val &= ~(MEM_HS_RATE_MASK | MEM_OVRD_HS_RATE | MEM_CDR_FASTLOCK |
		 MEM_CDR_LBW_MASK | MEM_CDR_STEPCNT_MASK | MEM_CDR_STL_MASK |
		 MEM_CDR_THR_MASK | MEM_CDR_THR_MODE | MEM_CDR_2NDO_SDM_MODE);
	val |= s->dig_hs_rate << MEM_HS_RATE_SHIFT |
		s->dig_ovrd_hs_rate << MEM_OVRD_HS_RATE_SHIFT |
		s->dig_fastlock << MEM_CDR_FASTLOCK_SHIFT |
		s->dig_lbw << MEM_CDR_LBW_SHIFT |
		s->dig_stepcnt << MEM_CDR_STEPCNT_SHIFT |
		s->dig_stl << MEM_CDR_STL_SHIFT |
		s->dig_thr << MEM_CDR_THR_SHIFT |
		s->dig_thr_mode << MEM_CDR_THR_MODE_SHIFT |
		s->dig_2nकरो_sdm_mode << MEM_CDR_2NDO_SDM_MODE_SHIFT;
	ti_pipe3_ग_लिखोl(phy->phy_rx, PIPE3_PHY_RX_DIGITAL_MODES, val);

	val = ti_pipe3_पढ़ोl(phy->phy_rx, PIPE3_PHY_RX_TRIM);
	val &= ~MEM_DLL_TRIM_SEL_MASK;
	val |= s->dll_trim_sel << MEM_DLL_TRIM_SHIFT;
	ti_pipe3_ग_लिखोl(phy->phy_rx, PIPE3_PHY_RX_TRIM, val);

	val = ti_pipe3_पढ़ोl(phy->phy_rx, PIPE3_PHY_RX_DLL);
	val &= ~MEM_DLL_PHINT_RATE_MASK;
	val |= s->dll_phपूर्णांक_rate << MEM_DLL_PHINT_RATE_SHIFT;
	ti_pipe3_ग_लिखोl(phy->phy_rx, PIPE3_PHY_RX_DLL, val);

	val = ti_pipe3_पढ़ोl(phy->phy_rx, PIPE3_PHY_RX_EQUALIZER);
	val &= ~(MEM_EQLEV_MASK | MEM_EQFTC_MASK | MEM_EQCTL_MASK |
		 MEM_OVRD_EQLEV | MEM_OVRD_EQFTC);
	val |= s->eq_lev << MEM_EQLEV_SHIFT |
		s->eq_ftc << MEM_EQFTC_SHIFT |
		s->eq_ctl << MEM_EQCTL_SHIFT |
		s->eq_ovrd_lev << MEM_OVRD_EQLEV_SHIFT |
		s->eq_ovrd_ftc << MEM_OVRD_EQFTC_SHIFT;
	ti_pipe3_ग_लिखोl(phy->phy_rx, PIPE3_PHY_RX_EQUALIZER, val);

	अगर (phy->mode == PIPE3_MODE_SATA) अणु
		val = ti_pipe3_पढ़ोl(phy->phy_rx,
				     SATA_PHY_RX_IO_AND_A2D_OVERRIDES);
		val &= ~MEM_CDR_LOS_SOURCE_MASK;
		ti_pipe3_ग_लिखोl(phy->phy_rx, SATA_PHY_RX_IO_AND_A2D_OVERRIDES,
				val);
	पूर्ण
पूर्ण

अटल पूर्णांक ti_pipe3_init(काष्ठा phy *x)
अणु
	काष्ठा ti_pipe3 *phy = phy_get_drvdata(x);
	u32 val;
	पूर्णांक ret = 0;

	ti_pipe3_enable_घड़ीs(phy);
	/*
	 * Set pcie_pcs रेजिस्टर to 0x96 क्रम proper functioning of phy
	 * as recommended in AM572x TRM SPRUHZ6, section 18.5.2.2, table
	 * 18-1804.
	 */
	अगर (phy->mode == PIPE3_MODE_PCIE) अणु
		अगर (!phy->pcs_syscon) अणु
			omap_control_pcie_pcs(phy->control_dev, 0x96);
			वापस 0;
		पूर्ण

		val = 0x96 << OMAP_CTRL_PCIE_PCS_DELAY_COUNT_SHIFT;
		ret = regmap_update_bits(phy->pcs_syscon, phy->pcie_pcs_reg,
					 PCIE_PCS_MASK, val);
		वापस ret;
	पूर्ण

	/* Bring it out of IDLE अगर it is IDLE */
	val = ti_pipe3_पढ़ोl(phy->pll_ctrl_base, PLL_CONFIGURATION2);
	अगर (val & PLL_IDLE) अणु
		val &= ~PLL_IDLE;
		ti_pipe3_ग_लिखोl(phy->pll_ctrl_base, PLL_CONFIGURATION2, val);
		ret = ti_pipe3_dpll_रुको_lock(phy);
	पूर्ण

	/* SATA has issues अगर re-programmed when locked */
	val = ti_pipe3_पढ़ोl(phy->pll_ctrl_base, PLL_STATUS);
	अगर ((val & PLL_LOCK) && phy->mode == PIPE3_MODE_SATA)
		वापस ret;

	/* Program the DPLL */
	ret = ti_pipe3_dpll_program(phy);
	अगर (ret) अणु
		ti_pipe3_disable_घड़ीs(phy);
		वापस -EINVAL;
	पूर्ण

	ti_pipe3_calibrate(phy);

	वापस ret;
पूर्ण

अटल पूर्णांक ti_pipe3_निकास(काष्ठा phy *x)
अणु
	काष्ठा ti_pipe3 *phy = phy_get_drvdata(x);
	u32 val;
	अचिन्हित दीर्घ समयout;

	/* If dpll_reset_syscon is not present we wont घातer करोwn SATA DPLL
	 * due to Errata i783
	 */
	अगर (phy->mode == PIPE3_MODE_SATA && !phy->dpll_reset_syscon)
		वापस 0;

	/* PCIe करोesn't have पूर्णांकernal DPLL */
	अगर (phy->mode != PIPE3_MODE_PCIE) अणु
		/* Put DPLL in IDLE mode */
		val = ti_pipe3_पढ़ोl(phy->pll_ctrl_base, PLL_CONFIGURATION2);
		val |= PLL_IDLE;
		ti_pipe3_ग_लिखोl(phy->pll_ctrl_base, PLL_CONFIGURATION2, val);

		/* रुको क्रम LDO and Oscillator to घातer करोwn */
		समयout = jअगरfies + msecs_to_jअगरfies(PLL_IDLE_TIME);
		करो अणु
			cpu_relax();
			val = ti_pipe3_पढ़ोl(phy->pll_ctrl_base, PLL_STATUS);
			अगर ((val & PLL_TICOPWDN) && (val & PLL_LDOPWDN))
				अवरोध;
		पूर्ण जबतक (!समय_after(jअगरfies, समयout));

		अगर (!(val & PLL_TICOPWDN) || !(val & PLL_LDOPWDN)) अणु
			dev_err(phy->dev, "Failed to power down: PLL_STATUS 0x%x\n",
				val);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	/* i783: SATA needs control bit toggle after PLL unlock */
	अगर (phy->mode == PIPE3_MODE_SATA) अणु
		regmap_update_bits(phy->dpll_reset_syscon, phy->dpll_reset_reg,
				   SATA_PLL_SOFT_RESET, SATA_PLL_SOFT_RESET);
		regmap_update_bits(phy->dpll_reset_syscon, phy->dpll_reset_reg,
				   SATA_PLL_SOFT_RESET, 0);
	पूर्ण

	ti_pipe3_disable_घड़ीs(phy);

	वापस 0;
पूर्ण
अटल स्थिर काष्ठा phy_ops ops = अणु
	.init		= ti_pipe3_init,
	.निकास		= ti_pipe3_निकास,
	.घातer_on	= ti_pipe3_घातer_on,
	.घातer_off	= ti_pipe3_घातer_off,
	.owner		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ti_pipe3_id_table[];

अटल पूर्णांक ti_pipe3_get_clk(काष्ठा ti_pipe3 *phy)
अणु
	काष्ठा clk *clk;
	काष्ठा device *dev = phy->dev;

	phy->refclk = devm_clk_get(dev, "refclk");
	अगर (IS_ERR(phy->refclk)) अणु
		dev_err(dev, "unable to get refclk\n");
		/* older DTBs have missing refclk in SATA PHY
		 * so करोn't bail out in हाल of SATA PHY.
		 */
		अगर (phy->mode != PIPE3_MODE_SATA)
			वापस PTR_ERR(phy->refclk);
	पूर्ण

	अगर (phy->mode != PIPE3_MODE_SATA) अणु
		phy->wkupclk = devm_clk_get(dev, "wkupclk");
		अगर (IS_ERR(phy->wkupclk)) अणु
			dev_err(dev, "unable to get wkupclk\n");
			वापस PTR_ERR(phy->wkupclk);
		पूर्ण
	पूर्ण अन्यथा अणु
		phy->wkupclk = ERR_PTR(-ENODEV);
	पूर्ण

	अगर (phy->mode != PIPE3_MODE_PCIE || phy->phy_घातer_syscon) अणु
		phy->sys_clk = devm_clk_get(dev, "sysclk");
		अगर (IS_ERR(phy->sys_clk)) अणु
			dev_err(dev, "unable to get sysclk\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (phy->mode == PIPE3_MODE_PCIE) अणु
		clk = devm_clk_get(dev, "dpll_ref");
		अगर (IS_ERR(clk)) अणु
			dev_err(dev, "unable to get dpll ref clk\n");
			वापस PTR_ERR(clk);
		पूर्ण
		clk_set_rate(clk, 1500000000);

		clk = devm_clk_get(dev, "dpll_ref_m2");
		अगर (IS_ERR(clk)) अणु
			dev_err(dev, "unable to get dpll ref m2 clk\n");
			वापस PTR_ERR(clk);
		पूर्ण
		clk_set_rate(clk, 100000000);

		clk = devm_clk_get(dev, "phy-div");
		अगर (IS_ERR(clk)) अणु
			dev_err(dev, "unable to get phy-div clk\n");
			वापस PTR_ERR(clk);
		पूर्ण
		clk_set_rate(clk, 100000000);

		phy->भाग_clk = devm_clk_get(dev, "div-clk");
		अगर (IS_ERR(phy->भाग_clk)) अणु
			dev_err(dev, "unable to get div-clk\n");
			वापस PTR_ERR(phy->भाग_clk);
		पूर्ण
	पूर्ण अन्यथा अणु
		phy->भाग_clk = ERR_PTR(-ENODEV);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ti_pipe3_get_sysctrl(काष्ठा ti_pipe3 *phy)
अणु
	काष्ठा device *dev = phy->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा device_node *control_node;
	काष्ठा platक्रमm_device *control_pdev;

	phy->phy_घातer_syscon = syscon_regmap_lookup_by_phandle(node,
							"syscon-phy-power");
	अगर (IS_ERR(phy->phy_घातer_syscon)) अणु
		dev_dbg(dev,
			"can't get syscon-phy-power, using control device\n");
		phy->phy_घातer_syscon = शून्य;
	पूर्ण अन्यथा अणु
		अगर (of_property_पढ़ो_u32_index(node,
					       "syscon-phy-power", 1,
					       &phy->घातer_reg)) अणु
			dev_err(dev, "couldn't get power reg. offset\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (!phy->phy_घातer_syscon) अणु
		control_node = of_parse_phandle(node, "ctrl-module", 0);
		अगर (!control_node) अणु
			dev_err(dev, "Failed to get control device phandle\n");
			वापस -EINVAL;
		पूर्ण

		control_pdev = of_find_device_by_node(control_node);
		अगर (!control_pdev) अणु
			dev_err(dev, "Failed to get control device\n");
			वापस -EINVAL;
		पूर्ण

		phy->control_dev = &control_pdev->dev;
	पूर्ण

	अगर (phy->mode == PIPE3_MODE_PCIE) अणु
		phy->pcs_syscon = syscon_regmap_lookup_by_phandle(node,
								  "syscon-pcs");
		अगर (IS_ERR(phy->pcs_syscon)) अणु
			dev_dbg(dev,
				"can't get syscon-pcs, using omap control\n");
			phy->pcs_syscon = शून्य;
		पूर्ण अन्यथा अणु
			अगर (of_property_पढ़ो_u32_index(node,
						       "syscon-pcs", 1,
						       &phy->pcie_pcs_reg)) अणु
				dev_err(dev,
					"couldn't get pcie pcs reg. offset\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (phy->mode == PIPE3_MODE_SATA) अणु
		phy->dpll_reset_syscon = syscon_regmap_lookup_by_phandle(node,
							"syscon-pllreset");
		अगर (IS_ERR(phy->dpll_reset_syscon)) अणु
			dev_info(dev,
				 "can't get syscon-pllreset, sata dpll won't idle\n");
			phy->dpll_reset_syscon = शून्य;
		पूर्ण अन्यथा अणु
			अगर (of_property_पढ़ो_u32_index(node,
						       "syscon-pllreset", 1,
						       &phy->dpll_reset_reg)) अणु
				dev_err(dev,
					"couldn't get pllreset reg. offset\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ti_pipe3_get_tx_rx_base(काष्ठा ti_pipe3 *phy)
अणु
	काष्ठा device *dev = phy->dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);

	phy->phy_rx = devm_platक्रमm_ioremap_resource_byname(pdev, "phy_rx");
	अगर (IS_ERR(phy->phy_rx))
		वापस PTR_ERR(phy->phy_rx);

	phy->phy_tx = devm_platक्रमm_ioremap_resource_byname(pdev, "phy_tx");

	वापस PTR_ERR_OR_ZERO(phy->phy_tx);
पूर्ण

अटल पूर्णांक ti_pipe3_get_pll_base(काष्ठा ti_pipe3 *phy)
अणु
	काष्ठा device *dev = phy->dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);

	अगर (phy->mode == PIPE3_MODE_PCIE)
		वापस 0;

	phy->pll_ctrl_base =
		devm_platक्रमm_ioremap_resource_byname(pdev, "pll_ctrl");
	वापस PTR_ERR_OR_ZERO(phy->pll_ctrl_base);
पूर्ण

अटल पूर्णांक ti_pipe3_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ti_pipe3 *phy;
	काष्ठा phy *generic_phy;
	काष्ठा phy_provider *phy_provider;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा pipe3_data *data;

	phy = devm_kzalloc(dev, माप(*phy), GFP_KERNEL);
	अगर (!phy)
		वापस -ENOMEM;

	match = of_match_device(ti_pipe3_id_table, dev);
	अगर (!match)
		वापस -EINVAL;

	data = (काष्ठा pipe3_data *)match->data;
	अगर (!data) अणु
		dev_err(dev, "no driver data\n");
		वापस -EINVAL;
	पूर्ण

	phy->dev = dev;
	phy->mode = data->mode;
	phy->dpll_map = data->dpll_map;
	phy->settings = data->settings;

	ret = ti_pipe3_get_pll_base(phy);
	अगर (ret)
		वापस ret;

	ret = ti_pipe3_get_tx_rx_base(phy);
	अगर (ret)
		वापस ret;

	ret = ti_pipe3_get_sysctrl(phy);
	अगर (ret)
		वापस ret;

	ret = ti_pipe3_get_clk(phy);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, phy);
	pm_runसमय_enable(dev);

	/*
	 * Prevent स्वतः-disable of refclk क्रम SATA PHY due to Errata i783
	 */
	अगर (phy->mode == PIPE3_MODE_SATA) अणु
		अगर (!IS_ERR(phy->refclk)) अणु
			clk_prepare_enable(phy->refclk);
			phy->sata_refclk_enabled = true;
		पूर्ण
	पूर्ण

	generic_phy = devm_phy_create(dev, शून्य, &ops);
	अगर (IS_ERR(generic_phy))
		वापस PTR_ERR(generic_phy);

	phy_set_drvdata(generic_phy, phy);

	ti_pipe3_घातer_off(generic_phy);

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);
	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल पूर्णांक ti_pipe3_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ti_pipe3 *phy = platक्रमm_get_drvdata(pdev);

	अगर (phy->mode == PIPE3_MODE_SATA) अणु
		clk_disable_unprepare(phy->refclk);
		phy->sata_refclk_enabled = false;
	पूर्ण
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक ti_pipe3_enable_घड़ीs(काष्ठा ti_pipe3 *phy)
अणु
	पूर्णांक ret = 0;

	अगर (!IS_ERR(phy->refclk)) अणु
		ret = clk_prepare_enable(phy->refclk);
		अगर (ret) अणु
			dev_err(phy->dev, "Failed to enable refclk %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (!IS_ERR(phy->wkupclk)) अणु
		ret = clk_prepare_enable(phy->wkupclk);
		अगर (ret) अणु
			dev_err(phy->dev, "Failed to enable wkupclk %d\n", ret);
			जाओ disable_refclk;
		पूर्ण
	पूर्ण

	अगर (!IS_ERR(phy->भाग_clk)) अणु
		ret = clk_prepare_enable(phy->भाग_clk);
		अगर (ret) अणु
			dev_err(phy->dev, "Failed to enable div_clk %d\n", ret);
			जाओ disable_wkupclk;
		पूर्ण
	पूर्ण

	वापस 0;

disable_wkupclk:
	अगर (!IS_ERR(phy->wkupclk))
		clk_disable_unprepare(phy->wkupclk);

disable_refclk:
	अगर (!IS_ERR(phy->refclk))
		clk_disable_unprepare(phy->refclk);

	वापस ret;
पूर्ण

अटल व्योम ti_pipe3_disable_घड़ीs(काष्ठा ti_pipe3 *phy)
अणु
	अगर (!IS_ERR(phy->wkupclk))
		clk_disable_unprepare(phy->wkupclk);
	अगर (!IS_ERR(phy->refclk))
		clk_disable_unprepare(phy->refclk);
	अगर (!IS_ERR(phy->भाग_clk))
		clk_disable_unprepare(phy->भाग_clk);
पूर्ण

अटल स्थिर काष्ठा of_device_id ti_pipe3_id_table[] = अणु
	अणु
		.compatible = "ti,phy-usb3",
		.data = &data_usb,
	पूर्ण,
	अणु
		.compatible = "ti,omap-usb3",
		.data = &data_usb,
	पूर्ण,
	अणु
		.compatible = "ti,phy-pipe3-sata",
		.data = &data_sata,
	पूर्ण,
	अणु
		.compatible = "ti,phy-pipe3-pcie",
		.data = &data_pcie,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ti_pipe3_id_table);

अटल काष्ठा platक्रमm_driver ti_pipe3_driver = अणु
	.probe		= ti_pipe3_probe,
	.हटाओ		= ti_pipe3_हटाओ,
	.driver		= अणु
		.name	= "ti-pipe3",
		.of_match_table = ti_pipe3_id_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ti_pipe3_driver);

MODULE_ALIAS("platform:ti_pipe3");
MODULE_AUTHOR("Texas Instruments Inc.");
MODULE_DESCRIPTION("TI PIPE3 phy driver");
MODULE_LICENSE("GPL v2");
