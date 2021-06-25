<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * camss-csiphy-3ph-1-0.c
 *
 * Qualcomm MSM Camera Subप्रणाली - CSIPHY Module 3phase v1.0
 *
 * Copyright (c) 2011-2015, The Linux Foundation. All rights reserved.
 * Copyright (C) 2016-2018 Linaro Ltd.
 */

#समावेश "camss.h"
#समावेश "camss-csiphy.h"

#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>

#घोषणा CSIPHY_3PH_LNn_CFG1(n)			(0x000 + 0x100 * (n))
#घोषणा CSIPHY_3PH_LNn_CFG1_SWI_REC_DLY_PRG	(BIT(7) | BIT(6))
#घोषणा CSIPHY_3PH_LNn_CFG2(n)			(0x004 + 0x100 * (n))
#घोषणा CSIPHY_3PH_LNn_CFG2_LP_REC_EN_INT	BIT(3)
#घोषणा CSIPHY_3PH_LNn_CFG3(n)			(0x008 + 0x100 * (n))
#घोषणा CSIPHY_3PH_LNn_CFG4(n)			(0x00c + 0x100 * (n))
#घोषणा CSIPHY_3PH_LNn_CFG4_T_HS_CLK_MISS	0xa4
#घोषणा CSIPHY_3PH_LNn_CFG4_T_HS_CLK_MISS_660	0xa5
#घोषणा CSIPHY_3PH_LNn_CFG5(n)			(0x010 + 0x100 * (n))
#घोषणा CSIPHY_3PH_LNn_CFG5_T_HS_DTERM		0x02
#घोषणा CSIPHY_3PH_LNn_CFG5_HS_REC_EQ_FQ_INT	0x50
#घोषणा CSIPHY_3PH_LNn_TEST_IMP(n)		(0x01c + 0x100 * (n))
#घोषणा CSIPHY_3PH_LNn_TEST_IMP_HS_TERM_IMP	0xa
#घोषणा CSIPHY_3PH_LNn_MISC1(n)			(0x028 + 0x100 * (n))
#घोषणा CSIPHY_3PH_LNn_MISC1_IS_CLKLANE		BIT(2)
#घोषणा CSIPHY_3PH_LNn_CFG6(n)			(0x02c + 0x100 * (n))
#घोषणा CSIPHY_3PH_LNn_CFG6_SWI_FORCE_INIT_EXIT	BIT(0)
#घोषणा CSIPHY_3PH_LNn_CFG7(n)			(0x030 + 0x100 * (n))
#घोषणा CSIPHY_3PH_LNn_CFG7_SWI_T_INIT		0x2
#घोषणा CSIPHY_3PH_LNn_CFG8(n)			(0x034 + 0x100 * (n))
#घोषणा CSIPHY_3PH_LNn_CFG8_SWI_SKIP_WAKEUP	BIT(0)
#घोषणा CSIPHY_3PH_LNn_CFG8_SKEW_FILTER_ENABLE	BIT(1)
#घोषणा CSIPHY_3PH_LNn_CFG9(n)			(0x038 + 0x100 * (n))
#घोषणा CSIPHY_3PH_LNn_CFG9_SWI_T_WAKEUP	0x1
#घोषणा CSIPHY_3PH_LNn_CSI_LANE_CTRL15(n)	(0x03c + 0x100 * (n))
#घोषणा CSIPHY_3PH_LNn_CSI_LANE_CTRL15_SWI_SOT_SYMBOL	0xb8

#घोषणा CSIPHY_3PH_CMN_CSI_COMMON_CTRLn(n)	(0x800 + 0x4 * (n))
#घोषणा CSIPHY_3PH_CMN_CSI_COMMON_CTRL6_COMMON_PWRDN_B	BIT(0)
#घोषणा CSIPHY_3PH_CMN_CSI_COMMON_CTRL6_SHOW_REV_ID	BIT(1)
#घोषणा CSIPHY_3PH_CMN_CSI_COMMON_STATUSn(n)	(0x8b0 + 0x4 * (n))

#घोषणा CSIPHY_DEFAULT_PARAMS            0
#घोषणा CSIPHY_LANE_ENABLE               1
#घोषणा CSIPHY_SETTLE_CNT_LOWER_BYTE     2
#घोषणा CSIPHY_SETTLE_CNT_HIGHER_BYTE    3
#घोषणा CSIPHY_DNP_PARAMS                4
#घोषणा CSIPHY_2PH_REGS                  5
#घोषणा CSIPHY_3PH_REGS                  6

काष्ठा csiphy_reg_t अणु
	s32 reg_addr;
	s32 reg_data;
	s32 delay;
	u32 csiphy_param_type;
पूर्ण;

अटल स्थिर काष्ठा
csiphy_reg_t lane_regs_sdm845[5][14] = अणु
	अणु
		अणु0x0004, 0x0C, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x002C, 0x01, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0034, 0x0F, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x001C, 0x0A, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0014, 0x60, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0028, 0x00, 0x00, CSIPHY_DNP_PARAMSपूर्ण,
		अणु0x003C, 0xB8, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0000, 0x91, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0008, 0x00, 0x00, CSIPHY_SETTLE_CNT_LOWER_BYTEपूर्ण,
		अणु0x000c, 0x00, 0x00, CSIPHY_DNP_PARAMSपूर्ण,
		अणु0x0010, 0x52, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0038, 0xFE, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0060, 0x00, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0064, 0x7F, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
	पूर्ण,
	अणु
		अणु0x0704, 0x0C, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x072C, 0x01, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0734, 0x0F, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x071C, 0x0A, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0714, 0x60, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0728, 0x04, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x073C, 0xB8, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0700, 0x80, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0708, 0x14, 0x00, CSIPHY_SETTLE_CNT_LOWER_BYTEपूर्ण,
		अणु0x070C, 0xA5, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0710, 0x52, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0738, 0x1F, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0760, 0x00, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0764, 0x7F, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
	पूर्ण,
	अणु
		अणु0x0204, 0x0C, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x022C, 0x01, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0234, 0x0F, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x021C, 0x0A, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0214, 0x60, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0228, 0x00, 0x00, CSIPHY_DNP_PARAMSपूर्ण,
		अणु0x023C, 0xB8, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0200, 0x91, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0208, 0x00, 0x00, CSIPHY_SETTLE_CNT_LOWER_BYTEपूर्ण,
		अणु0x020C, 0x00, 0x00, CSIPHY_DNP_PARAMSपूर्ण,
		अणु0x0210, 0x52, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0238, 0xFE, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0260, 0x00, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0264, 0x7F, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
	पूर्ण,
	अणु
		अणु0x0404, 0x0C, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x042C, 0x01, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0434, 0x0F, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x041C, 0x0A, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0414, 0x60, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0428, 0x00, 0x00, CSIPHY_DNP_PARAMSपूर्ण,
		अणु0x043C, 0xB8, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0400, 0x91, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0408, 0x00, 0x00, CSIPHY_SETTLE_CNT_LOWER_BYTEपूर्ण,
		अणु0x040C, 0x00, 0x00, CSIPHY_DNP_PARAMSपूर्ण,
		अणु0x0410, 0x52, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0438, 0xFE, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0460, 0x00, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0464, 0x7F, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
	पूर्ण,
	अणु
		अणु0x0604, 0x0C, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x062C, 0x01, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0634, 0x0F, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x061C, 0x0A, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0614, 0x60, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0628, 0x00, 0x00, CSIPHY_DNP_PARAMSपूर्ण,
		अणु0x063C, 0xB8, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0600, 0x91, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0608, 0x00, 0x00, CSIPHY_SETTLE_CNT_LOWER_BYTEपूर्ण,
		अणु0x060C, 0x00, 0x00, CSIPHY_DNP_PARAMSपूर्ण,
		अणु0x0610, 0x52, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0638, 0xFE, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0660, 0x00, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
		अणु0x0664, 0x7F, 0x00, CSIPHY_DEFAULT_PARAMSपूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम csiphy_hw_version_पढ़ो(काष्ठा csiphy_device *csiphy,
				   काष्ठा device *dev)
अणु
	u32 hw_version;

	ग_लिखोl(CSIPHY_3PH_CMN_CSI_COMMON_CTRL6_SHOW_REV_ID,
	       csiphy->base + CSIPHY_3PH_CMN_CSI_COMMON_CTRLn(6));

	hw_version = पढ़ोl_relaxed(csiphy->base +
				   CSIPHY_3PH_CMN_CSI_COMMON_STATUSn(12));
	hw_version |= पढ़ोl_relaxed(csiphy->base +
				   CSIPHY_3PH_CMN_CSI_COMMON_STATUSn(13)) << 8;
	hw_version |= पढ़ोl_relaxed(csiphy->base +
				   CSIPHY_3PH_CMN_CSI_COMMON_STATUSn(14)) << 16;
	hw_version |= पढ़ोl_relaxed(csiphy->base +
				   CSIPHY_3PH_CMN_CSI_COMMON_STATUSn(15)) << 24;

	dev_err(dev, "CSIPHY 3PH HW Version = 0x%08x\n", hw_version);
पूर्ण

/*
 * csiphy_reset - Perक्रमm software reset on CSIPHY module
 * @csiphy: CSIPHY device
 */
अटल व्योम csiphy_reset(काष्ठा csiphy_device *csiphy)
अणु
	ग_लिखोl_relaxed(0x1, csiphy->base + CSIPHY_3PH_CMN_CSI_COMMON_CTRLn(0));
	usleep_range(5000, 8000);
	ग_लिखोl_relaxed(0x0, csiphy->base + CSIPHY_3PH_CMN_CSI_COMMON_CTRLn(0));
पूर्ण

अटल irqवापस_t csiphy_isr(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा csiphy_device *csiphy = dev;
	पूर्णांक i;

	क्रम (i = 0; i < 11; i++) अणु
		पूर्णांक c = i + 22;
		u8 val = पढ़ोl_relaxed(csiphy->base +
				       CSIPHY_3PH_CMN_CSI_COMMON_STATUSn(i));

		ग_लिखोl_relaxed(val, csiphy->base +
				    CSIPHY_3PH_CMN_CSI_COMMON_CTRLn(c));
	पूर्ण

	ग_लिखोl_relaxed(0x1, csiphy->base + CSIPHY_3PH_CMN_CSI_COMMON_CTRLn(10));
	ग_लिखोl_relaxed(0x0, csiphy->base + CSIPHY_3PH_CMN_CSI_COMMON_CTRLn(10));

	क्रम (i = 22; i < 33; i++)
		ग_लिखोl_relaxed(0x0, csiphy->base +
				    CSIPHY_3PH_CMN_CSI_COMMON_CTRLn(i));

	वापस IRQ_HANDLED;
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
	u32 t_hs_settle; /* ps */
	u8 settle_cnt;

	अगर (link_freq <= 0)
		वापस 0;

	ui = भाग_u64(1000000000000LL, link_freq);
	ui /= 2;
	t_hs_prepare_max = 85000 + 6 * ui;
	t_hs_settle = t_hs_prepare_max;

	समयr_period = भाग_u64(1000000000000LL, समयr_clk_rate);
	settle_cnt = t_hs_settle / समयr_period - 6;

	वापस settle_cnt;
पूर्ण

अटल व्योम csiphy_gen1_config_lanes(काष्ठा csiphy_device *csiphy,
				     काष्ठा csiphy_config *cfg,
				     u8 settle_cnt)
अणु
	काष्ठा csiphy_lanes_cfg *c = &cfg->csi2->lane_cfg;
	पूर्णांक i, l = 0;
	u8 val;

	क्रम (i = 0; i <= c->num_data; i++) अणु
		अगर (i == c->num_data)
			l = 7;
		अन्यथा
			l = c->data[i].pos * 2;

		val = CSIPHY_3PH_LNn_CFG1_SWI_REC_DLY_PRG;
		val |= 0x17;
		ग_लिखोl_relaxed(val, csiphy->base + CSIPHY_3PH_LNn_CFG1(l));

		val = CSIPHY_3PH_LNn_CFG2_LP_REC_EN_INT;
		ग_लिखोl_relaxed(val, csiphy->base + CSIPHY_3PH_LNn_CFG2(l));

		val = settle_cnt;
		ग_लिखोl_relaxed(val, csiphy->base + CSIPHY_3PH_LNn_CFG3(l));

		val = CSIPHY_3PH_LNn_CFG5_T_HS_DTERM |
			CSIPHY_3PH_LNn_CFG5_HS_REC_EQ_FQ_INT;
		ग_लिखोl_relaxed(val, csiphy->base + CSIPHY_3PH_LNn_CFG5(l));

		val = CSIPHY_3PH_LNn_CFG6_SWI_FORCE_INIT_EXIT;
		ग_लिखोl_relaxed(val, csiphy->base + CSIPHY_3PH_LNn_CFG6(l));

		val = CSIPHY_3PH_LNn_CFG7_SWI_T_INIT;
		ग_लिखोl_relaxed(val, csiphy->base + CSIPHY_3PH_LNn_CFG7(l));

		val = CSIPHY_3PH_LNn_CFG8_SWI_SKIP_WAKEUP |
			CSIPHY_3PH_LNn_CFG8_SKEW_FILTER_ENABLE;
		ग_लिखोl_relaxed(val, csiphy->base + CSIPHY_3PH_LNn_CFG8(l));

		val = CSIPHY_3PH_LNn_CFG9_SWI_T_WAKEUP;
		ग_लिखोl_relaxed(val, csiphy->base + CSIPHY_3PH_LNn_CFG9(l));

		val = CSIPHY_3PH_LNn_TEST_IMP_HS_TERM_IMP;
		ग_लिखोl_relaxed(val, csiphy->base + CSIPHY_3PH_LNn_TEST_IMP(l));

		val = CSIPHY_3PH_LNn_CSI_LANE_CTRL15_SWI_SOT_SYMBOL;
		ग_लिखोl_relaxed(val, csiphy->base +
				    CSIPHY_3PH_LNn_CSI_LANE_CTRL15(l));
	पूर्ण

	val = CSIPHY_3PH_LNn_CFG1_SWI_REC_DLY_PRG;
	ग_लिखोl_relaxed(val, csiphy->base + CSIPHY_3PH_LNn_CFG1(l));

	अगर (csiphy->camss->version == CAMSS_660)
		val = CSIPHY_3PH_LNn_CFG4_T_HS_CLK_MISS_660;
	अन्यथा
		val = CSIPHY_3PH_LNn_CFG4_T_HS_CLK_MISS;
	ग_लिखोl_relaxed(val, csiphy->base + CSIPHY_3PH_LNn_CFG4(l));

	val = CSIPHY_3PH_LNn_MISC1_IS_CLKLANE;
	ग_लिखोl_relaxed(val, csiphy->base + CSIPHY_3PH_LNn_MISC1(l));
पूर्ण

अटल व्योम csiphy_gen2_config_lanes(काष्ठा csiphy_device *csiphy,
				     u8 settle_cnt)
अणु
	पूर्णांक i, l;
	u32 val;

	क्रम (l = 0; l < 5; l++) अणु
		क्रम (i = 0; i < 14; i++) अणु
			स्थिर काष्ठा csiphy_reg_t *r = &lane_regs_sdm845[l][i];

			चयन (r->csiphy_param_type) अणु
			हाल CSIPHY_SETTLE_CNT_LOWER_BYTE:
				val = settle_cnt & 0xff;
				अवरोध;
			हाल CSIPHY_DNP_PARAMS:
				जारी;
			शेष:
				val = r->reg_data;
				अवरोध;
			पूर्ण
			ग_लिखोl_relaxed(val, csiphy->base + r->reg_addr);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम csiphy_lanes_enable(काष्ठा csiphy_device *csiphy,
				काष्ठा csiphy_config *cfg,
				s64 link_freq, u8 lane_mask)
अणु
	काष्ठा csiphy_lanes_cfg *c = &cfg->csi2->lane_cfg;
	u8 settle_cnt;
	u8 val;
	पूर्णांक i;

	settle_cnt = csiphy_settle_cnt_calc(link_freq, csiphy->समयr_clk_rate);

	val = BIT(c->clk.pos);
	क्रम (i = 0; i < c->num_data; i++)
		val |= BIT(c->data[i].pos * 2);

	ग_लिखोl_relaxed(val, csiphy->base + CSIPHY_3PH_CMN_CSI_COMMON_CTRLn(5));

	val = CSIPHY_3PH_CMN_CSI_COMMON_CTRL6_COMMON_PWRDN_B;
	ग_लिखोl_relaxed(val, csiphy->base + CSIPHY_3PH_CMN_CSI_COMMON_CTRLn(6));

	val = 0x02;
	ग_लिखोl_relaxed(val, csiphy->base + CSIPHY_3PH_CMN_CSI_COMMON_CTRLn(7));

	val = 0x00;
	ग_लिखोl_relaxed(val, csiphy->base + CSIPHY_3PH_CMN_CSI_COMMON_CTRLn(0));

	अगर (csiphy->camss->version == CAMSS_8x16 ||
	    csiphy->camss->version == CAMSS_8x96)
		csiphy_gen1_config_lanes(csiphy, cfg, settle_cnt);
	अन्यथा अगर (csiphy->camss->version == CAMSS_845)
		csiphy_gen2_config_lanes(csiphy, settle_cnt);

	val = 0xff;
	ग_लिखोl_relaxed(val, csiphy->base + CSIPHY_3PH_CMN_CSI_COMMON_CTRLn(11));

	val = 0xff;
	ग_लिखोl_relaxed(val, csiphy->base + CSIPHY_3PH_CMN_CSI_COMMON_CTRLn(12));

	val = 0xfb;
	ग_लिखोl_relaxed(val, csiphy->base + CSIPHY_3PH_CMN_CSI_COMMON_CTRLn(13));

	val = 0xff;
	ग_लिखोl_relaxed(val, csiphy->base + CSIPHY_3PH_CMN_CSI_COMMON_CTRLn(14));

	val = 0x7f;
	ग_लिखोl_relaxed(val, csiphy->base + CSIPHY_3PH_CMN_CSI_COMMON_CTRLn(15));

	val = 0xff;
	ग_लिखोl_relaxed(val, csiphy->base + CSIPHY_3PH_CMN_CSI_COMMON_CTRLn(16));

	val = 0xff;
	ग_लिखोl_relaxed(val, csiphy->base + CSIPHY_3PH_CMN_CSI_COMMON_CTRLn(17));

	val = 0xef;
	ग_लिखोl_relaxed(val, csiphy->base + CSIPHY_3PH_CMN_CSI_COMMON_CTRLn(18));

	val = 0xff;
	ग_लिखोl_relaxed(val, csiphy->base + CSIPHY_3PH_CMN_CSI_COMMON_CTRLn(19));

	val = 0xff;
	ग_लिखोl_relaxed(val, csiphy->base + CSIPHY_3PH_CMN_CSI_COMMON_CTRLn(20));

	val = 0xff;
	ग_लिखोl_relaxed(val, csiphy->base + CSIPHY_3PH_CMN_CSI_COMMON_CTRLn(21));
पूर्ण

अटल व्योम csiphy_lanes_disable(काष्ठा csiphy_device *csiphy,
				 काष्ठा csiphy_config *cfg)
अणु
	ग_लिखोl_relaxed(0, csiphy->base +
			  CSIPHY_3PH_CMN_CSI_COMMON_CTRLn(5));

	ग_लिखोl_relaxed(0, csiphy->base +
			  CSIPHY_3PH_CMN_CSI_COMMON_CTRLn(6));
पूर्ण

स्थिर काष्ठा csiphy_hw_ops csiphy_ops_3ph_1_0 = अणु
	.hw_version_पढ़ो = csiphy_hw_version_पढ़ो,
	.reset = csiphy_reset,
	.lanes_enable = csiphy_lanes_enable,
	.lanes_disable = csiphy_lanes_disable,
	.isr = csiphy_isr,
पूर्ण;
