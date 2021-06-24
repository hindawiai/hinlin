<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * UFS PHY driver क्रम Samsung EXYNOS SoC
 *
 * Copyright (C) 2020 Samsung Electronics Co., Ltd.
 * Author: Seungwon Jeon <essuuj@gmail.com>
 * Author: Alim Akhtar <alim.akhtar@samsung.com>
 *
 */
#अगर_अघोषित _PHY_SAMSUNG_UFS_
#घोषणा _PHY_SAMSUNG_UFS_

#घोषणा PHY_COMN_BLK	1
#घोषणा PHY_TRSV_BLK	2
#घोषणा END_UFS_PHY_CFG अणु 0 पूर्ण
#घोषणा PHY_TRSV_CH_OFFSET	0x30
#घोषणा PHY_APB_ADDR(off)	((off) << 2)

#घोषणा PHY_COMN_REG_CFG(o, v, d) अणु	\
	.off_0 = PHY_APB_ADDR((o)),	\
	.off_1 = 0,		\
	.val = (v),		\
	.desc = (d),		\
	.id = PHY_COMN_BLK,	\
पूर्ण

#घोषणा PHY_TRSV_REG_CFG(o, v, d) अणु	\
	.off_0 = PHY_APB_ADDR((o)),	\
	.off_1 = PHY_APB_ADDR((o) + PHY_TRSV_CH_OFFSET),	\
	.val = (v),		\
	.desc = (d),		\
	.id = PHY_TRSV_BLK,	\
पूर्ण

/* UFS PHY रेजिस्टरs */
#घोषणा PHY_PLL_LOCK_STATUS	0x1e
#घोषणा PHY_CDR_LOCK_STATUS	0x5e

#घोषणा PHY_PLL_LOCK_BIT	BIT(5)
#घोषणा PHY_CDR_LOCK_BIT	BIT(4)

/* description क्रम PHY calibration */
क्रमागत अणु
	/* applicable to any */
	PWR_DESC_ANY	= 0,
	/* mode */
	PWR_DESC_PWM	= 1,
	PWR_DESC_HS	= 2,
	/* series */
	PWR_DESC_SER_A	= 1,
	PWR_DESC_SER_B	= 2,
	/* gear */
	PWR_DESC_G1	= 1,
	PWR_DESC_G2	= 2,
	PWR_DESC_G3	= 3,
	/* field mask */
	MD_MASK		= 0x3,
	SR_MASK		= 0x3,
	GR_MASK		= 0x7,
पूर्ण;

#घोषणा PWR_MODE_HS_G1_ANY	PWR_MODE_HS(PWR_DESC_G1, PWR_DESC_ANY)
#घोषणा PWR_MODE_HS_G1_SER_A	PWR_MODE_HS(PWR_DESC_G1, PWR_DESC_SER_A)
#घोषणा PWR_MODE_HS_G1_SER_B	PWR_MODE_HS(PWR_DESC_G1, PWR_DESC_SER_B)
#घोषणा PWR_MODE_HS_G2_ANY	PWR_MODE_HS(PWR_DESC_G2, PWR_DESC_ANY)
#घोषणा PWR_MODE_HS_G2_SER_A	PWR_MODE_HS(PWR_DESC_G2, PWR_DESC_SER_A)
#घोषणा PWR_MODE_HS_G2_SER_B	PWR_MODE_HS(PWR_DESC_G2, PWR_DESC_SER_B)
#घोषणा PWR_MODE_HS_G3_ANY	PWR_MODE_HS(PWR_DESC_G3, PWR_DESC_ANY)
#घोषणा PWR_MODE_HS_G3_SER_A	PWR_MODE_HS(PWR_DESC_G3, PWR_DESC_SER_A)
#घोषणा PWR_MODE_HS_G3_SER_B	PWR_MODE_HS(PWR_DESC_G3, PWR_DESC_SER_B)
#घोषणा PWR_MODE(g, s, m)	((((g) & GR_MASK) << 4) |\
				 (((s) & SR_MASK) << 2) | ((m) & MD_MASK))
#घोषणा PWR_MODE_PWM_ANY	PWR_MODE(PWR_DESC_ANY,\
					 PWR_DESC_ANY, PWR_DESC_PWM)
#घोषणा PWR_MODE_HS(g, s)	((((g) & GR_MASK) << 4) |\
				 (((s) & SR_MASK) << 2) | PWR_DESC_HS)
#घोषणा PWR_MODE_HS_ANY		PWR_MODE(PWR_DESC_ANY,\
					 PWR_DESC_ANY, PWR_DESC_HS)
#घोषणा PWR_MODE_ANY		PWR_MODE(PWR_DESC_ANY,\
					 PWR_DESC_ANY, PWR_DESC_ANY)
/* PHY calibration poपूर्णांक/state */
क्रमागत अणु
	CFG_PRE_INIT,
	CFG_POST_INIT,
	CFG_PRE_PWR_HS,
	CFG_POST_PWR_HS,
	CFG_TAG_MAX,
पूर्ण;

काष्ठा samsung_ufs_phy_cfg अणु
	u32 off_0;
	u32 off_1;
	u32 val;
	u8 desc;
	u8 id;
पूर्ण;

काष्ठा samsung_ufs_phy_drvdata अणु
	स्थिर काष्ठा samsung_ufs_phy_cfg **cfg;
	काष्ठा pmu_isol अणु
		u32 offset;
		u32 mask;
		u32 en;
	पूर्ण isol;
	bool has_symbol_clk;
पूर्ण;

काष्ठा samsung_ufs_phy अणु
	काष्ठा device *dev;
	व्योम __iomem *reg_pma;
	काष्ठा regmap *reg_pmu;
	काष्ठा clk *ref_clk;
	काष्ठा clk *ref_clk_parent;
	काष्ठा clk *tx0_symbol_clk;
	काष्ठा clk *rx0_symbol_clk;
	काष्ठा clk *rx1_symbol_clk;
	स्थिर काष्ठा samsung_ufs_phy_drvdata *drvdata;
	काष्ठा samsung_ufs_phy_cfg **cfg;
	स्थिर काष्ठा pmu_isol *isol;
	u8 lane_cnt;
	पूर्णांक ufs_phy_state;
	क्रमागत phy_mode mode;
पूर्ण;

अटल अंतरभूत काष्ठा samsung_ufs_phy *get_samsung_ufs_phy(काष्ठा phy *phy)
अणु
	वापस (काष्ठा samsung_ufs_phy *)phy_get_drvdata(phy);
पूर्ण

अटल अंतरभूत व्योम samsung_ufs_phy_ctrl_isol(
		काष्ठा samsung_ufs_phy *phy, u32 isol)
अणु
	regmap_update_bits(phy->reg_pmu, phy->isol->offset,
			   phy->isol->mask, isol ? 0 : phy->isol->en);
पूर्ण

#समावेश "phy-exynos7-ufs.h"

#पूर्ण_अगर /* _PHY_SAMSUNG_UFS_ */
