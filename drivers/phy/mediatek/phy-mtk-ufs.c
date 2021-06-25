<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019 MediaTek Inc.
 * Author: Stanley Chu <stanley.chu@mediatek.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>

/* mphy रेजिस्टर and offsets */
#घोषणा MP_GLB_DIG_8C               0x008C
#घोषणा FRC_PLL_ISO_EN              BIT(8)
#घोषणा PLL_ISO_EN                  BIT(9)
#घोषणा FRC_FRC_PWR_ON              BIT(10)
#घोषणा PLL_PWR_ON                  BIT(11)

#घोषणा MP_LN_DIG_RX_9C             0xA09C
#घोषणा FSM_DIFZ_FRC                BIT(18)

#घोषणा MP_LN_DIG_RX_AC             0xA0AC
#घोषणा FRC_RX_SQ_EN                BIT(0)
#घोषणा RX_SQ_EN                    BIT(1)

#घोषणा MP_LN_RX_44                 0xB044
#घोषणा FRC_CDR_PWR_ON              BIT(17)
#घोषणा CDR_PWR_ON                  BIT(18)
#घोषणा FRC_CDR_ISO_EN              BIT(19)
#घोषणा CDR_ISO_EN                  BIT(20)

काष्ठा ufs_mtk_phy अणु
	काष्ठा device *dev;
	व्योम __iomem *mmio;
	काष्ठा clk *mp_clk;
	काष्ठा clk *unipro_clk;
पूर्ण;

अटल अंतरभूत u32 mphy_पढ़ोl(काष्ठा ufs_mtk_phy *phy, u32 reg)
अणु
	वापस पढ़ोl(phy->mmio + reg);
पूर्ण

अटल अंतरभूत व्योम mphy_ग_लिखोl(काष्ठा ufs_mtk_phy *phy, u32 val, u32 reg)
अणु
	ग_लिखोl(val, phy->mmio + reg);
पूर्ण

अटल व्योम mphy_set_bit(काष्ठा ufs_mtk_phy *phy, u32 reg, u32 bit)
अणु
	u32 val;

	val = mphy_पढ़ोl(phy, reg);
	val |= bit;
	mphy_ग_लिखोl(phy, val, reg);
पूर्ण

अटल व्योम mphy_clr_bit(काष्ठा ufs_mtk_phy *phy, u32 reg, u32 bit)
अणु
	u32 val;

	val = mphy_पढ़ोl(phy, reg);
	val &= ~bit;
	mphy_ग_लिखोl(phy, val, reg);
पूर्ण

अटल काष्ठा ufs_mtk_phy *get_ufs_mtk_phy(काष्ठा phy *generic_phy)
अणु
	वापस (काष्ठा ufs_mtk_phy *)phy_get_drvdata(generic_phy);
पूर्ण

अटल पूर्णांक ufs_mtk_phy_clk_init(काष्ठा ufs_mtk_phy *phy)
अणु
	काष्ठा device *dev = phy->dev;

	phy->unipro_clk = devm_clk_get(dev, "unipro");
	अगर (IS_ERR(phy->unipro_clk)) अणु
		dev_err(dev, "failed to get clock: unipro");
		वापस PTR_ERR(phy->unipro_clk);
	पूर्ण

	phy->mp_clk = devm_clk_get(dev, "mp");
	अगर (IS_ERR(phy->mp_clk)) अणु
		dev_err(dev, "failed to get clock: mp");
		वापस PTR_ERR(phy->mp_clk);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ufs_mtk_phy_set_active(काष्ठा ufs_mtk_phy *phy)
अणु
	/* release DA_MP_PLL_PWR_ON */
	mphy_set_bit(phy, MP_GLB_DIG_8C, PLL_PWR_ON);
	mphy_clr_bit(phy, MP_GLB_DIG_8C, FRC_FRC_PWR_ON);

	/* release DA_MP_PLL_ISO_EN */
	mphy_clr_bit(phy, MP_GLB_DIG_8C, PLL_ISO_EN);
	mphy_clr_bit(phy, MP_GLB_DIG_8C, FRC_PLL_ISO_EN);

	/* release DA_MP_CDR_PWR_ON */
	mphy_set_bit(phy, MP_LN_RX_44, CDR_PWR_ON);
	mphy_clr_bit(phy, MP_LN_RX_44, FRC_CDR_PWR_ON);

	/* release DA_MP_CDR_ISO_EN */
	mphy_clr_bit(phy, MP_LN_RX_44, CDR_ISO_EN);
	mphy_clr_bit(phy, MP_LN_RX_44, FRC_CDR_ISO_EN);

	/* release DA_MP_RX0_SQ_EN */
	mphy_set_bit(phy, MP_LN_DIG_RX_AC, RX_SQ_EN);
	mphy_clr_bit(phy, MP_LN_DIG_RX_AC, FRC_RX_SQ_EN);

	/* delay 1us to रुको DIFZ stable */
	udelay(1);

	/* release DIFZ */
	mphy_clr_bit(phy, MP_LN_DIG_RX_9C, FSM_DIFZ_FRC);
पूर्ण

अटल व्योम ufs_mtk_phy_set_deep_hibern(काष्ठा ufs_mtk_phy *phy)
अणु
	/* क्रमce DIFZ */
	mphy_set_bit(phy, MP_LN_DIG_RX_9C, FSM_DIFZ_FRC);

	/* क्रमce DA_MP_RX0_SQ_EN */
	mphy_set_bit(phy, MP_LN_DIG_RX_AC, FRC_RX_SQ_EN);
	mphy_clr_bit(phy, MP_LN_DIG_RX_AC, RX_SQ_EN);

	/* क्रमce DA_MP_CDR_ISO_EN */
	mphy_set_bit(phy, MP_LN_RX_44, FRC_CDR_ISO_EN);
	mphy_set_bit(phy, MP_LN_RX_44, CDR_ISO_EN);

	/* क्रमce DA_MP_CDR_PWR_ON */
	mphy_set_bit(phy, MP_LN_RX_44, FRC_CDR_PWR_ON);
	mphy_clr_bit(phy, MP_LN_RX_44, CDR_PWR_ON);

	/* क्रमce DA_MP_PLL_ISO_EN */
	mphy_set_bit(phy, MP_GLB_DIG_8C, FRC_PLL_ISO_EN);
	mphy_set_bit(phy, MP_GLB_DIG_8C, PLL_ISO_EN);

	/* क्रमce DA_MP_PLL_PWR_ON */
	mphy_set_bit(phy, MP_GLB_DIG_8C, FRC_FRC_PWR_ON);
	mphy_clr_bit(phy, MP_GLB_DIG_8C, PLL_PWR_ON);
पूर्ण

अटल पूर्णांक ufs_mtk_phy_घातer_on(काष्ठा phy *generic_phy)
अणु
	काष्ठा ufs_mtk_phy *phy = get_ufs_mtk_phy(generic_phy);
	पूर्णांक ret;

	ret = clk_prepare_enable(phy->unipro_clk);
	अगर (ret) अणु
		dev_err(phy->dev, "unipro_clk enable failed %d\n", ret);
		जाओ out;
	पूर्ण

	ret = clk_prepare_enable(phy->mp_clk);
	अगर (ret) अणु
		dev_err(phy->dev, "mp_clk enable failed %d\n", ret);
		जाओ out_unprepare_unipro_clk;
	पूर्ण

	ufs_mtk_phy_set_active(phy);

	वापस 0;

out_unprepare_unipro_clk:
	clk_disable_unprepare(phy->unipro_clk);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक ufs_mtk_phy_घातer_off(काष्ठा phy *generic_phy)
अणु
	काष्ठा ufs_mtk_phy *phy = get_ufs_mtk_phy(generic_phy);

	ufs_mtk_phy_set_deep_hibern(phy);

	clk_disable_unprepare(phy->unipro_clk);
	clk_disable_unprepare(phy->mp_clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops ufs_mtk_phy_ops = अणु
	.घातer_on       = ufs_mtk_phy_घातer_on,
	.घातer_off      = ufs_mtk_phy_घातer_off,
	.owner          = THIS_MODULE,
पूर्ण;

अटल पूर्णांक ufs_mtk_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा phy *generic_phy;
	काष्ठा phy_provider *phy_provider;
	काष्ठा ufs_mtk_phy *phy;
	पूर्णांक ret;

	phy = devm_kzalloc(dev, माप(*phy), GFP_KERNEL);
	अगर (!phy)
		वापस -ENOMEM;

	phy->mmio = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(phy->mmio))
		वापस PTR_ERR(phy->mmio);

	phy->dev = dev;

	ret = ufs_mtk_phy_clk_init(phy);
	अगर (ret)
		वापस ret;

	generic_phy = devm_phy_create(dev, शून्य, &ufs_mtk_phy_ops);
	अगर (IS_ERR(generic_phy))
		वापस PTR_ERR(generic_phy);

	phy_set_drvdata(generic_phy, phy);

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);

	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल स्थिर काष्ठा of_device_id ufs_mtk_phy_of_match[] = अणु
	अणु.compatible = "mediatek,mt8183-ufsphy"पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ufs_mtk_phy_of_match);

अटल काष्ठा platक्रमm_driver ufs_mtk_phy_driver = अणु
	.probe = ufs_mtk_phy_probe,
	.driver = अणु
		.of_match_table = ufs_mtk_phy_of_match,
		.name = "ufs_mtk_phy",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ufs_mtk_phy_driver);

MODULE_DESCRIPTION("Universal Flash Storage (UFS) MediaTek MPHY");
MODULE_AUTHOR("Stanley Chu <stanley.chu@mediatek.com>");
MODULE_LICENSE("GPL v2");
