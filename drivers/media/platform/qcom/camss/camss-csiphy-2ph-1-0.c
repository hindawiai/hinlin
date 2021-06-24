<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * camss-csiphy-2ph-1-0.c
 *
 * Qualcomm MSM Camera Subप्रणाली - CSIPHY Module 2phase v1.0
 *
 * Copyright (c) 2011-2015, The Linux Foundation. All rights reserved.
 * Copyright (C) 2016-2018 Linaro Ltd.
 */

#समावेश "camss-csiphy.h"

#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>

#घोषणा CAMSS_CSI_PHY_LNn_CFG2(n)		(0x004 + 0x40 * (n))
#घोषणा CAMSS_CSI_PHY_LNn_CFG3(n)		(0x008 + 0x40 * (n))
#घोषणा CAMSS_CSI_PHY_GLBL_RESET		0x140
#घोषणा CAMSS_CSI_PHY_GLBL_PWR_CFG		0x144
#घोषणा CAMSS_CSI_PHY_GLBL_IRQ_CMD		0x164
#घोषणा CAMSS_CSI_PHY_HW_VERSION		0x188
#घोषणा CAMSS_CSI_PHY_INTERRUPT_STATUSn(n)	(0x18c + 0x4 * (n))
#घोषणा CAMSS_CSI_PHY_INTERRUPT_MASKn(n)	(0x1ac + 0x4 * (n))
#घोषणा CAMSS_CSI_PHY_INTERRUPT_CLEARn(n)	(0x1cc + 0x4 * (n))
#घोषणा CAMSS_CSI_PHY_GLBL_T_INIT_CFG0		0x1ec
#घोषणा CAMSS_CSI_PHY_T_WAKEUP_CFG0		0x1f4

अटल व्योम csiphy_hw_version_पढ़ो(काष्ठा csiphy_device *csiphy,
				   काष्ठा device *dev)
अणु
	u8 hw_version = पढ़ोl_relaxed(csiphy->base +
				      CAMSS_CSI_PHY_HW_VERSION);

	dev_dbg(dev, "CSIPHY HW Version = 0x%02x\n", hw_version);
पूर्ण

/*
 * csiphy_reset - Perक्रमm software reset on CSIPHY module
 * @csiphy: CSIPHY device
 */
अटल व्योम csiphy_reset(काष्ठा csiphy_device *csiphy)
अणु
	ग_लिखोl_relaxed(0x1, csiphy->base + CAMSS_CSI_PHY_GLBL_RESET);
	usleep_range(5000, 8000);
	ग_लिखोl_relaxed(0x0, csiphy->base + CAMSS_CSI_PHY_GLBL_RESET);
पूर्ण

/*
 * csiphy_settle_cnt_calc - Calculate settle count value
 *
 * Helper function to calculate settle count value. This is
 * based on the CSI2 T_hs_settle parameter which in turn
 * is calculated based on the CSI2 transmitter link frequency.
 *
 * Return settle count value or 0 अगर the CSI2 link frequency
 * is not available
 */
अटल u8 csiphy_settle_cnt_calc(s64 link_freq, u32 समयr_clk_rate)
अणु
	u32 ui; /* ps */
	u32 समयr_period; /* ps */
	u32 t_hs_prepare_max; /* ps */
	u32 t_hs_prepare_zero_min; /* ps */
	u32 t_hs_settle; /* ps */
	u8 settle_cnt;

	अगर (link_freq <= 0)
		वापस 0;

	ui = भाग_u64(1000000000000LL, link_freq);
	ui /= 2;
	t_hs_prepare_max = 85000 + 6 * ui;
	t_hs_prepare_zero_min = 145000 + 10 * ui;
	t_hs_settle = (t_hs_prepare_max + t_hs_prepare_zero_min) / 2;

	समयr_period = भाग_u64(1000000000000LL, समयr_clk_rate);
	settle_cnt = t_hs_settle / समयr_period - 1;

	वापस settle_cnt;
पूर्ण

अटल व्योम csiphy_lanes_enable(काष्ठा csiphy_device *csiphy,
				काष्ठा csiphy_config *cfg,
				s64 link_freq, u8 lane_mask)
अणु
	काष्ठा csiphy_lanes_cfg *c = &cfg->csi2->lane_cfg;
	u8 settle_cnt;
	u8 val, l = 0;
	पूर्णांक i = 0;

	settle_cnt = csiphy_settle_cnt_calc(link_freq, csiphy->समयr_clk_rate);

	ग_लिखोl_relaxed(0x1, csiphy->base +
		       CAMSS_CSI_PHY_GLBL_T_INIT_CFG0);
	ग_लिखोl_relaxed(0x1, csiphy->base +
		       CAMSS_CSI_PHY_T_WAKEUP_CFG0);

	val = 0x1;
	val |= lane_mask << 1;
	ग_लिखोl_relaxed(val, csiphy->base + CAMSS_CSI_PHY_GLBL_PWR_CFG);

	val = cfg->combo_mode << 4;
	ग_लिखोl_relaxed(val, csiphy->base + CAMSS_CSI_PHY_GLBL_RESET);

	क्रम (i = 0; i <= c->num_data; i++) अणु
		अगर (i == c->num_data)
			l = c->clk.pos;
		अन्यथा
			l = c->data[i].pos;

		ग_लिखोl_relaxed(0x10, csiphy->base +
			       CAMSS_CSI_PHY_LNn_CFG2(l));
		ग_लिखोl_relaxed(settle_cnt, csiphy->base +
			       CAMSS_CSI_PHY_LNn_CFG3(l));
		ग_लिखोl_relaxed(0x3f, csiphy->base +
			       CAMSS_CSI_PHY_INTERRUPT_MASKn(l));
		ग_लिखोl_relaxed(0x3f, csiphy->base +
			       CAMSS_CSI_PHY_INTERRUPT_CLEARn(l));
	पूर्ण
पूर्ण

अटल व्योम csiphy_lanes_disable(काष्ठा csiphy_device *csiphy,
				 काष्ठा csiphy_config *cfg)
अणु
	काष्ठा csiphy_lanes_cfg *c = &cfg->csi2->lane_cfg;
	u8 l = 0;
	पूर्णांक i = 0;

	क्रम (i = 0; i <= c->num_data; i++) अणु
		अगर (i == c->num_data)
			l = c->clk.pos;
		अन्यथा
			l = c->data[i].pos;

		ग_लिखोl_relaxed(0x0, csiphy->base +
			       CAMSS_CSI_PHY_LNn_CFG2(l));
	पूर्ण

	ग_लिखोl_relaxed(0x0, csiphy->base + CAMSS_CSI_PHY_GLBL_PWR_CFG);
पूर्ण

/*
 * csiphy_isr - CSIPHY module पूर्णांकerrupt handler
 * @irq: Interrupt line
 * @dev: CSIPHY device
 *
 * Return IRQ_HANDLED on success
 */
अटल irqवापस_t csiphy_isr(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा csiphy_device *csiphy = dev;
	u8 i;

	क्रम (i = 0; i < 8; i++) अणु
		u8 val = पढ़ोl_relaxed(csiphy->base +
				       CAMSS_CSI_PHY_INTERRUPT_STATUSn(i));
		ग_लिखोl_relaxed(val, csiphy->base +
			       CAMSS_CSI_PHY_INTERRUPT_CLEARn(i));
		ग_लिखोl_relaxed(0x1, csiphy->base + CAMSS_CSI_PHY_GLBL_IRQ_CMD);
		ग_लिखोl_relaxed(0x0, csiphy->base + CAMSS_CSI_PHY_GLBL_IRQ_CMD);
		ग_लिखोl_relaxed(0x0, csiphy->base +
			       CAMSS_CSI_PHY_INTERRUPT_CLEARn(i));
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

स्थिर काष्ठा csiphy_hw_ops csiphy_ops_2ph_1_0 = अणु
	.hw_version_पढ़ो = csiphy_hw_version_पढ़ो,
	.reset = csiphy_reset,
	.lanes_enable = csiphy_lanes_enable,
	.lanes_disable = csiphy_lanes_disable,
	.isr = csiphy_isr,
पूर्ण;
