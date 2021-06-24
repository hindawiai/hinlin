<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * TI OMAP4 ISS V4L2 Driver - CSI PHY module
 *
 * Copyright (C) 2012 Texas Instruments, Inc.
 *
 * Author: Sergio Aguirre <sergio.a.aguirre@gmail.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/regmap.h>

#समावेश "../../../../arch/arm/mach-omap2/control.h"

#समावेश "iss.h"
#समावेश "iss_regs.h"
#समावेश "iss_csiphy.h"

/*
 * csiphy_lanes_config - Configuration of CSIPHY lanes.
 *
 * Updates HW configuration.
 * Called with phy->mutex taken.
 */
अटल व्योम csiphy_lanes_config(काष्ठा iss_csiphy *phy)
अणु
	अचिन्हित पूर्णांक i;
	u32 reg;

	reg = iss_reg_पढ़ो(phy->iss, phy->cfg_regs, CSI2_COMPLEXIO_CFG);

	क्रम (i = 0; i < phy->max_data_lanes; i++) अणु
		reg &= ~(CSI2_COMPLEXIO_CFG_DATA_POL(i + 1) |
			 CSI2_COMPLEXIO_CFG_DATA_POSITION_MASK(i + 1));
		reg |= (phy->lanes.data[i].pol ?
			CSI2_COMPLEXIO_CFG_DATA_POL(i + 1) : 0);
		reg |= (phy->lanes.data[i].pos <<
			CSI2_COMPLEXIO_CFG_DATA_POSITION_SHIFT(i + 1));
	पूर्ण

	reg &= ~(CSI2_COMPLEXIO_CFG_CLOCK_POL |
		 CSI2_COMPLEXIO_CFG_CLOCK_POSITION_MASK);
	reg |= phy->lanes.clk.pol ? CSI2_COMPLEXIO_CFG_CLOCK_POL : 0;
	reg |= phy->lanes.clk.pos << CSI2_COMPLEXIO_CFG_CLOCK_POSITION_SHIFT;

	iss_reg_ग_लिखो(phy->iss, phy->cfg_regs, CSI2_COMPLEXIO_CFG, reg);
पूर्ण

/*
 * csiphy_set_घातer
 * @घातer: Power state to be set.
 *
 * Returns 0 अगर successful, or -EBUSY अगर the retry count is exceeded.
 */
अटल पूर्णांक csiphy_set_घातer(काष्ठा iss_csiphy *phy, u32 घातer)
अणु
	u32 reg;
	u8 retry_count;

	iss_reg_update(phy->iss, phy->cfg_regs, CSI2_COMPLEXIO_CFG,
		       CSI2_COMPLEXIO_CFG_PWD_CMD_MASK,
		       घातer | CSI2_COMPLEXIO_CFG_PWR_AUTO);

	retry_count = 0;
	करो अणु
		udelay(1);
		reg = iss_reg_पढ़ो(phy->iss, phy->cfg_regs, CSI2_COMPLEXIO_CFG)
		    & CSI2_COMPLEXIO_CFG_PWD_STATUS_MASK;

		अगर (reg != घातer >> 2)
			retry_count++;

	पूर्ण जबतक ((reg != घातer >> 2) && (retry_count < 250));

	अगर (retry_count == 250) अणु
		dev_err(phy->iss->dev, "CSI2 CIO set power failed!\n");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * csiphy_dphy_config - Configure CSI2 D-PHY parameters.
 *
 * Called with phy->mutex taken.
 */
अटल व्योम csiphy_dphy_config(काष्ठा iss_csiphy *phy)
अणु
	u32 reg;

	/* Set up REGISTER0 */
	reg = phy->dphy.ths_term << REGISTER0_THS_TERM_SHIFT;
	reg |= phy->dphy.ths_settle << REGISTER0_THS_SETTLE_SHIFT;

	iss_reg_ग_लिखो(phy->iss, phy->phy_regs, REGISTER0, reg);

	/* Set up REGISTER1 */
	reg = phy->dphy.tclk_term << REGISTER1_TCLK_TERM_SHIFT;
	reg |= phy->dphy.tclk_miss << REGISTER1_CTRLCLK_DIV_FACTOR_SHIFT;
	reg |= phy->dphy.tclk_settle << REGISTER1_TCLK_SETTLE_SHIFT;
	reg |= 0xb8 << REGISTER1_DPHY_HS_SYNC_PATTERN_SHIFT;

	iss_reg_ग_लिखो(phy->iss, phy->phy_regs, REGISTER1, reg);
पूर्ण

/*
 * TCLK values are OK at their reset values
 */
#घोषणा TCLK_TERM	0
#घोषणा TCLK_MISS	1
#घोषणा TCLK_SETTLE	14

पूर्णांक omap4iss_csiphy_config(काष्ठा iss_device *iss,
			   काष्ठा v4l2_subdev *csi2_subdev)
अणु
	काष्ठा iss_csi2_device *csi2 = v4l2_get_subdevdata(csi2_subdev);
	काष्ठा iss_pipeline *pipe = to_iss_pipeline(&csi2_subdev->entity);
	काष्ठा iss_v4l2_subdevs_group *subdevs = pipe->बाह्यal->host_priv;
	काष्ठा iss_csiphy_dphy_cfg csi2phy;
	पूर्णांक csi2_ddrclk_khz;
	काष्ठा iss_csiphy_lanes_cfg *lanes;
	अचिन्हित पूर्णांक used_lanes = 0;
	u32 cam_rx_ctrl;
	अचिन्हित पूर्णांक i;

	lanes = &subdevs->bus.csi2.lanecfg;

	/*
	 * SCM.CONTROL_CAMERA_RX
	 * - bit [31] : CSIPHY2 lane 2 enable (4460+ only)
	 * - bit [30:29] : CSIPHY2 per-lane enable (1 to 0)
	 * - bit [28:24] : CSIPHY1 per-lane enable (4 to 0)
	 * - bit [21] : CSIPHY2 CTRLCLK enable
	 * - bit [20:19] : CSIPHY2 config: 00 d-phy, 01/10 ccp2
	 * - bit [18] : CSIPHY1 CTRLCLK enable
	 * - bit [17:16] : CSIPHY1 config: 00 d-phy, 01/10 ccp2
	 */
	/*
	 * TODO: When implementing DT support specअगरy the CONTROL_CAMERA_RX
	 * रेजिस्टर offset in the syscon property instead of hardcoding it.
	 */
	regmap_पढ़ो(iss->syscon, 0x68, &cam_rx_ctrl);

	अगर (subdevs->पूर्णांकerface == ISS_INTERFACE_CSI2A_PHY1) अणु
		cam_rx_ctrl &= ~(OMAP4_CAMERARX_CSI21_LANEENABLE_MASK |
				OMAP4_CAMERARX_CSI21_CAMMODE_MASK);
		/* NOTE: Leave CSIPHY1 config to 0x0: D-PHY mode */
		/* Enable all lanes क्रम now */
		cam_rx_ctrl |=
			0x1f << OMAP4_CAMERARX_CSI21_LANEENABLE_SHIFT;
		/* Enable CTRLCLK */
		cam_rx_ctrl |= OMAP4_CAMERARX_CSI21_CTRLCLKEN_MASK;
	पूर्ण

	अगर (subdevs->पूर्णांकerface == ISS_INTERFACE_CSI2B_PHY2) अणु
		cam_rx_ctrl &= ~(OMAP4_CAMERARX_CSI22_LANEENABLE_MASK |
				OMAP4_CAMERARX_CSI22_CAMMODE_MASK);
		/* NOTE: Leave CSIPHY2 config to 0x0: D-PHY mode */
		/* Enable all lanes क्रम now */
		cam_rx_ctrl |=
			0x3 << OMAP4_CAMERARX_CSI22_LANEENABLE_SHIFT;
		/* Enable CTRLCLK */
		cam_rx_ctrl |= OMAP4_CAMERARX_CSI22_CTRLCLKEN_MASK;
	पूर्ण

	regmap_ग_लिखो(iss->syscon, 0x68, cam_rx_ctrl);

	/* Reset used lane count */
	csi2->phy->used_data_lanes = 0;

	/* Clock and data lanes verअगरication */
	क्रम (i = 0; i < csi2->phy->max_data_lanes; i++) अणु
		अगर (lanes->data[i].pos == 0)
			जारी;

		अगर (lanes->data[i].pol > 1 ||
		    lanes->data[i].pos > (csi2->phy->max_data_lanes + 1))
			वापस -EINVAL;

		अगर (used_lanes & (1 << lanes->data[i].pos))
			वापस -EINVAL;

		used_lanes |= 1 << lanes->data[i].pos;
		csi2->phy->used_data_lanes++;
	पूर्ण

	अगर (lanes->clk.pol > 1 ||
	    lanes->clk.pos > (csi2->phy->max_data_lanes + 1))
		वापस -EINVAL;

	अगर (lanes->clk.pos == 0 || used_lanes & (1 << lanes->clk.pos))
		वापस -EINVAL;

	csi2_ddrclk_khz = pipe->बाह्यal_rate / 1000
		/ (2 * csi2->phy->used_data_lanes)
		* pipe->बाह्यal_bpp;

	/*
	 * THS_TERM: Programmed value = उच्चमान(12.5 ns/DDRClk period) - 1.
	 * THS_SETTLE: Programmed value = उच्चमान(90 ns/DDRClk period) + 3.
	 */
	csi2phy.ths_term = DIV_ROUND_UP(25 * csi2_ddrclk_khz, 2000000) - 1;
	csi2phy.ths_settle = DIV_ROUND_UP(90 * csi2_ddrclk_khz, 1000000) + 3;
	csi2phy.tclk_term = TCLK_TERM;
	csi2phy.tclk_miss = TCLK_MISS;
	csi2phy.tclk_settle = TCLK_SETTLE;

	mutex_lock(&csi2->phy->mutex);
	csi2->phy->dphy = csi2phy;
	csi2->phy->lanes = *lanes;
	mutex_unlock(&csi2->phy->mutex);

	वापस 0;
पूर्ण

पूर्णांक omap4iss_csiphy_acquire(काष्ठा iss_csiphy *phy)
अणु
	पूर्णांक rval;

	mutex_lock(&phy->mutex);

	rval = omap4iss_csi2_reset(phy->csi2);
	अगर (rval)
		जाओ करोne;

	csiphy_dphy_config(phy);
	csiphy_lanes_config(phy);

	rval = csiphy_set_घातer(phy, CSI2_COMPLEXIO_CFG_PWD_CMD_ON);
	अगर (rval)
		जाओ करोne;

	phy->phy_in_use = 1;

करोne:
	mutex_unlock(&phy->mutex);
	वापस rval;
पूर्ण

व्योम omap4iss_csiphy_release(काष्ठा iss_csiphy *phy)
अणु
	mutex_lock(&phy->mutex);
	अगर (phy->phy_in_use) अणु
		csiphy_set_घातer(phy, CSI2_COMPLEXIO_CFG_PWD_CMD_OFF);
		phy->phy_in_use = 0;
	पूर्ण
	mutex_unlock(&phy->mutex);
पूर्ण

/*
 * omap4iss_csiphy_init - Initialize the CSI PHY frontends
 */
पूर्णांक omap4iss_csiphy_init(काष्ठा iss_device *iss)
अणु
	काष्ठा iss_csiphy *phy1 = &iss->csiphy1;
	काष्ठा iss_csiphy *phy2 = &iss->csiphy2;

	phy1->iss = iss;
	phy1->csi2 = &iss->csi2a;
	phy1->max_data_lanes = ISS_CSIPHY1_NUM_DATA_LANES;
	phy1->used_data_lanes = 0;
	phy1->cfg_regs = OMAP4_ISS_MEM_CSI2_A_REGS1;
	phy1->phy_regs = OMAP4_ISS_MEM_CAMERARX_CORE1;
	mutex_init(&phy1->mutex);

	phy2->iss = iss;
	phy2->csi2 = &iss->csi2b;
	phy2->max_data_lanes = ISS_CSIPHY2_NUM_DATA_LANES;
	phy2->used_data_lanes = 0;
	phy2->cfg_regs = OMAP4_ISS_MEM_CSI2_B_REGS1;
	phy2->phy_regs = OMAP4_ISS_MEM_CAMERARX_CORE2;
	mutex_init(&phy2->mutex);

	वापस 0;
पूर्ण
