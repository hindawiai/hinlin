<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ispcsiphy.c
 *
 * TI OMAP3 ISP - CSI PHY module
 *
 * Copyright (C) 2010 Nokia Corporation
 * Copyright (C) 2009 Texas Instruments, Inc.
 *
 * Contacts: Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *	     Sakari Ailus <sakari.ailus@iki.fi>
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>

#समावेश "isp.h"
#समावेश "ispreg.h"
#समावेश "ispcsiphy.h"

अटल व्योम csiphy_routing_cfg_3630(काष्ठा isp_csiphy *phy,
				    क्रमागत isp_पूर्णांकerface_type अगरace,
				    bool ccp2_strobe)
अणु
	u32 reg;
	u32 shअगरt, mode;

	regmap_पढ़ो(phy->isp->syscon, phy->isp->syscon_offset, &reg);

	चयन (अगरace) अणु
	शेष:
	/* Should not happen in practice, but let's keep the compiler happy. */
	हाल ISP_INTERFACE_CCP2B_PHY1:
		reg &= ~OMAP3630_CONTROL_CAMERA_PHY_CTRL_CSI1_RX_SEL_PHY2;
		shअगरt = OMAP3630_CONTROL_CAMERA_PHY_CTRL_CAMMODE_PHY1_SHIFT;
		अवरोध;
	हाल ISP_INTERFACE_CSI2C_PHY1:
		shअगरt = OMAP3630_CONTROL_CAMERA_PHY_CTRL_CAMMODE_PHY1_SHIFT;
		mode = OMAP3630_CONTROL_CAMERA_PHY_CTRL_CAMMODE_DPHY;
		अवरोध;
	हाल ISP_INTERFACE_CCP2B_PHY2:
		reg |= OMAP3630_CONTROL_CAMERA_PHY_CTRL_CSI1_RX_SEL_PHY2;
		shअगरt = OMAP3630_CONTROL_CAMERA_PHY_CTRL_CAMMODE_PHY2_SHIFT;
		अवरोध;
	हाल ISP_INTERFACE_CSI2A_PHY2:
		shअगरt = OMAP3630_CONTROL_CAMERA_PHY_CTRL_CAMMODE_PHY2_SHIFT;
		mode = OMAP3630_CONTROL_CAMERA_PHY_CTRL_CAMMODE_DPHY;
		अवरोध;
	पूर्ण

	/* Select data/घड़ी or data/strobe mode क्रम CCP2 */
	अगर (अगरace == ISP_INTERFACE_CCP2B_PHY1 ||
	    अगरace == ISP_INTERFACE_CCP2B_PHY2) अणु
		अगर (ccp2_strobe)
			mode = OMAP3630_CONTROL_CAMERA_PHY_CTRL_CAMMODE_CCP2_DATA_STROBE;
		अन्यथा
			mode = OMAP3630_CONTROL_CAMERA_PHY_CTRL_CAMMODE_CCP2_DATA_CLOCK;
	पूर्ण

	reg &= ~(OMAP3630_CONTROL_CAMERA_PHY_CTRL_CAMMODE_MASK << shअगरt);
	reg |= mode << shअगरt;

	regmap_ग_लिखो(phy->isp->syscon, phy->isp->syscon_offset, reg);
पूर्ण

अटल व्योम csiphy_routing_cfg_3430(काष्ठा isp_csiphy *phy, u32 अगरace, bool on,
				    bool ccp2_strobe)
अणु
	u32 csirxfe = OMAP343X_CONTROL_CSIRXFE_PWRDNZ
		| OMAP343X_CONTROL_CSIRXFE_RESET;

	/* Only the CCP2B on PHY1 is configurable. */
	अगर (अगरace != ISP_INTERFACE_CCP2B_PHY1)
		वापस;

	अगर (!on) अणु
		regmap_ग_लिखो(phy->isp->syscon, phy->isp->syscon_offset, 0);
		वापस;
	पूर्ण

	अगर (ccp2_strobe)
		csirxfe |= OMAP343X_CONTROL_CSIRXFE_SELFORM;

	regmap_ग_लिखो(phy->isp->syscon, phy->isp->syscon_offset, csirxfe);
पूर्ण

/*
 * Configure OMAP 3 CSI PHY routing.
 * @phy: relevant phy device
 * @अगरace: ISP_INTERFACE_*
 * @on: घातer on or off
 * @ccp2_strobe: false: data/घड़ी, true: data/strobe
 *
 * Note that the underlying routing configuration रेजिस्टरs are part of the
 * control (SCM) रेजिस्टर space and part of the CORE घातer करोमुख्य on both 3430
 * and 3630, so they will not hold their contents in off-mode. This isn't an
 * issue since the MPU घातer करोमुख्य is क्रमced on whilst the ISP is in use.
 */
अटल व्योम csiphy_routing_cfg(काष्ठा isp_csiphy *phy,
			       क्रमागत isp_पूर्णांकerface_type अगरace, bool on,
			       bool ccp2_strobe)
अणु
	अगर (phy->isp->phy_type == ISP_PHY_TYPE_3630 && on)
		वापस csiphy_routing_cfg_3630(phy, अगरace, ccp2_strobe);
	अगर (phy->isp->phy_type == ISP_PHY_TYPE_3430)
		वापस csiphy_routing_cfg_3430(phy, अगरace, on, ccp2_strobe);
पूर्ण

/*
 * csiphy_घातer_स्वतःचयन_enable
 * @enable: Sets or clears the स्वतःचयन function enable flag.
 */
अटल व्योम csiphy_घातer_स्वतःचयन_enable(काष्ठा isp_csiphy *phy, bool enable)
अणु
	isp_reg_clr_set(phy->isp, phy->cfg_regs, ISPCSI2_PHY_CFG,
			ISPCSI2_PHY_CFG_PWR_AUTO,
			enable ? ISPCSI2_PHY_CFG_PWR_AUTO : 0);
पूर्ण

/*
 * csiphy_set_घातer
 * @घातer: Power state to be set.
 *
 * Returns 0 अगर successful, or -EBUSY अगर the retry count is exceeded.
 */
अटल पूर्णांक csiphy_set_घातer(काष्ठा isp_csiphy *phy, u32 घातer)
अणु
	u32 reg;
	u8 retry_count;

	isp_reg_clr_set(phy->isp, phy->cfg_regs, ISPCSI2_PHY_CFG,
			ISPCSI2_PHY_CFG_PWR_CMD_MASK, घातer);

	retry_count = 0;
	करो अणु
		udelay(50);
		reg = isp_reg_पढ़ोl(phy->isp, phy->cfg_regs, ISPCSI2_PHY_CFG) &
				    ISPCSI2_PHY_CFG_PWR_STATUS_MASK;

		अगर (reg != घातer >> 2)
			retry_count++;

	पूर्ण जबतक ((reg != घातer >> 2) && (retry_count < 100));

	अगर (retry_count == 100) अणु
		dev_err(phy->isp->dev, "CSI2 CIO set power failed!\n");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * TCLK values are OK at their reset values
 */
#घोषणा TCLK_TERM	0
#घोषणा TCLK_MISS	1
#घोषणा TCLK_SETTLE	14

अटल पूर्णांक omap3isp_csiphy_config(काष्ठा isp_csiphy *phy)
अणु
	काष्ठा isp_pipeline *pipe = to_isp_pipeline(phy->entity);
	काष्ठा isp_bus_cfg *buscfg = v4l2_subdev_to_bus_cfg(pipe->बाह्यal);
	काष्ठा isp_csiphy_lanes_cfg *lanes;
	पूर्णांक csi2_ddrclk_khz;
	अचिन्हित पूर्णांक num_data_lanes, used_lanes = 0;
	अचिन्हित पूर्णांक i;
	u32 reg;

	अगर (buscfg->पूर्णांकerface == ISP_INTERFACE_CCP2B_PHY1
	    || buscfg->पूर्णांकerface == ISP_INTERFACE_CCP2B_PHY2) अणु
		lanes = &buscfg->bus.ccp2.lanecfg;
		num_data_lanes = 1;
	पूर्ण अन्यथा अणु
		lanes = &buscfg->bus.csi2.lanecfg;
		num_data_lanes = buscfg->bus.csi2.num_data_lanes;
	पूर्ण

	अगर (num_data_lanes > phy->num_data_lanes)
		वापस -EINVAL;

	/* Clock and data lanes verअगरication */
	क्रम (i = 0; i < num_data_lanes; i++) अणु
		अगर (lanes->data[i].pol > 1 || lanes->data[i].pos > 3)
			वापस -EINVAL;

		अगर (used_lanes & (1 << lanes->data[i].pos))
			वापस -EINVAL;

		used_lanes |= 1 << lanes->data[i].pos;
	पूर्ण

	अगर (lanes->clk.pol > 1 || lanes->clk.pos > 3)
		वापस -EINVAL;

	अगर (lanes->clk.pos == 0 || used_lanes & (1 << lanes->clk.pos))
		वापस -EINVAL;

	/*
	 * The PHY configuration is lost in off mode, that's not an
	 * issue since the MPU घातer करोमुख्य is क्रमced on whilst the
	 * ISP is in use.
	 */
	csiphy_routing_cfg(phy, buscfg->पूर्णांकerface, true,
			   buscfg->bus.ccp2.phy_layer);

	/* DPHY timing configuration */
	/* CSI-2 is DDR and we only count used lanes. */
	csi2_ddrclk_khz = pipe->बाह्यal_rate / 1000
		/ (2 * hweight32(used_lanes)) * pipe->बाह्यal_width;

	reg = isp_reg_पढ़ोl(phy->isp, phy->phy_regs, ISPCSIPHY_REG0);

	reg &= ~(ISPCSIPHY_REG0_THS_TERM_MASK |
		 ISPCSIPHY_REG0_THS_SETTLE_MASK);
	/* THS_TERM: Programmed value = उच्चमान(12.5 ns/DDRClk period) - 1. */
	reg |= (DIV_ROUND_UP(25 * csi2_ddrclk_khz, 2000000) - 1)
		<< ISPCSIPHY_REG0_THS_TERM_SHIFT;
	/* THS_SETTLE: Programmed value = उच्चमान(90 ns/DDRClk period) + 3. */
	reg |= (DIV_ROUND_UP(90 * csi2_ddrclk_khz, 1000000) + 3)
		<< ISPCSIPHY_REG0_THS_SETTLE_SHIFT;

	isp_reg_ग_लिखोl(phy->isp, reg, phy->phy_regs, ISPCSIPHY_REG0);

	reg = isp_reg_पढ़ोl(phy->isp, phy->phy_regs, ISPCSIPHY_REG1);

	reg &= ~(ISPCSIPHY_REG1_TCLK_TERM_MASK |
		 ISPCSIPHY_REG1_TCLK_MISS_MASK |
		 ISPCSIPHY_REG1_TCLK_SETTLE_MASK);
	reg |= TCLK_TERM << ISPCSIPHY_REG1_TCLK_TERM_SHIFT;
	reg |= TCLK_MISS << ISPCSIPHY_REG1_TCLK_MISS_SHIFT;
	reg |= TCLK_SETTLE << ISPCSIPHY_REG1_TCLK_SETTLE_SHIFT;

	isp_reg_ग_लिखोl(phy->isp, reg, phy->phy_regs, ISPCSIPHY_REG1);

	/* DPHY lane configuration */
	reg = isp_reg_पढ़ोl(phy->isp, phy->cfg_regs, ISPCSI2_PHY_CFG);

	क्रम (i = 0; i < num_data_lanes; i++) अणु
		reg &= ~(ISPCSI2_PHY_CFG_DATA_POL_MASK(i + 1) |
			 ISPCSI2_PHY_CFG_DATA_POSITION_MASK(i + 1));
		reg |= (lanes->data[i].pol <<
			ISPCSI2_PHY_CFG_DATA_POL_SHIFT(i + 1));
		reg |= (lanes->data[i].pos <<
			ISPCSI2_PHY_CFG_DATA_POSITION_SHIFT(i + 1));
	पूर्ण

	reg &= ~(ISPCSI2_PHY_CFG_CLOCK_POL_MASK |
		 ISPCSI2_PHY_CFG_CLOCK_POSITION_MASK);
	reg |= lanes->clk.pol << ISPCSI2_PHY_CFG_CLOCK_POL_SHIFT;
	reg |= lanes->clk.pos << ISPCSI2_PHY_CFG_CLOCK_POSITION_SHIFT;

	isp_reg_ग_लिखोl(phy->isp, reg, phy->cfg_regs, ISPCSI2_PHY_CFG);

	वापस 0;
पूर्ण

पूर्णांक omap3isp_csiphy_acquire(काष्ठा isp_csiphy *phy, काष्ठा media_entity *entity)
अणु
	पूर्णांक rval;

	अगर (phy->vdd == शून्य) अणु
		dev_err(phy->isp->dev,
			"Power regulator for CSI PHY not available\n");
		वापस -ENODEV;
	पूर्ण

	mutex_lock(&phy->mutex);

	rval = regulator_enable(phy->vdd);
	अगर (rval < 0)
		जाओ करोne;

	rval = omap3isp_csi2_reset(phy->csi2);
	अगर (rval < 0)
		जाओ करोne;

	phy->entity = entity;

	rval = omap3isp_csiphy_config(phy);
	अगर (rval < 0)
		जाओ करोne;

	अगर (phy->isp->revision == ISP_REVISION_15_0) अणु
		rval = csiphy_set_घातer(phy, ISPCSI2_PHY_CFG_PWR_CMD_ON);
		अगर (rval) अणु
			regulator_disable(phy->vdd);
			जाओ करोne;
		पूर्ण

		csiphy_घातer_स्वतःचयन_enable(phy, true);
	पूर्ण
करोne:
	अगर (rval < 0)
		phy->entity = शून्य;

	mutex_unlock(&phy->mutex);
	वापस rval;
पूर्ण

व्योम omap3isp_csiphy_release(काष्ठा isp_csiphy *phy)
अणु
	mutex_lock(&phy->mutex);
	अगर (phy->entity) अणु
		काष्ठा isp_pipeline *pipe = to_isp_pipeline(phy->entity);
		काष्ठा isp_bus_cfg *buscfg =
			v4l2_subdev_to_bus_cfg(pipe->बाह्यal);

		csiphy_routing_cfg(phy, buscfg->पूर्णांकerface, false,
				   buscfg->bus.ccp2.phy_layer);
		अगर (phy->isp->revision == ISP_REVISION_15_0) अणु
			csiphy_घातer_स्वतःचयन_enable(phy, false);
			csiphy_set_घातer(phy, ISPCSI2_PHY_CFG_PWR_CMD_OFF);
		पूर्ण
		regulator_disable(phy->vdd);
		phy->entity = शून्य;
	पूर्ण
	mutex_unlock(&phy->mutex);
पूर्ण

/*
 * omap3isp_csiphy_init - Initialize the CSI PHY frontends
 */
पूर्णांक omap3isp_csiphy_init(काष्ठा isp_device *isp)
अणु
	काष्ठा isp_csiphy *phy1 = &isp->isp_csiphy1;
	काष्ठा isp_csiphy *phy2 = &isp->isp_csiphy2;

	phy2->isp = isp;
	phy2->csi2 = &isp->isp_csi2a;
	phy2->num_data_lanes = ISP_CSIPHY2_NUM_DATA_LANES;
	phy2->cfg_regs = OMAP3_ISP_IOMEM_CSI2A_REGS1;
	phy2->phy_regs = OMAP3_ISP_IOMEM_CSIPHY2;
	mutex_init(&phy2->mutex);

	phy1->isp = isp;
	mutex_init(&phy1->mutex);

	अगर (isp->revision == ISP_REVISION_15_0) अणु
		phy1->csi2 = &isp->isp_csi2c;
		phy1->num_data_lanes = ISP_CSIPHY1_NUM_DATA_LANES;
		phy1->cfg_regs = OMAP3_ISP_IOMEM_CSI2C_REGS1;
		phy1->phy_regs = OMAP3_ISP_IOMEM_CSIPHY1;
	पूर्ण

	वापस 0;
पूर्ण

व्योम omap3isp_csiphy_cleanup(काष्ठा isp_device *isp)
अणु
	mutex_destroy(&isp->isp_csiphy1.mutex);
	mutex_destroy(&isp->isp_csiphy2.mutex);
पूर्ण
