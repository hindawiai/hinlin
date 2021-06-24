<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2011 Marvell International Ltd. All rights reserved.
 * Copyright (C) 2018,2019 Lubomir Rपूर्णांकel <lkundrak@v3.sk>
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/soc/mmp/cputype.h>

#घोषणा USB2_PLL_REG0		0x4
#घोषणा USB2_PLL_REG1		0x8
#घोषणा USB2_TX_REG0		0x10
#घोषणा USB2_TX_REG1		0x14
#घोषणा USB2_TX_REG2		0x18
#घोषणा USB2_RX_REG0		0x20
#घोषणा USB2_RX_REG1		0x24
#घोषणा USB2_RX_REG2		0x28
#घोषणा USB2_ANA_REG0		0x30
#घोषणा USB2_ANA_REG1		0x34
#घोषणा USB2_ANA_REG2		0x38
#घोषणा USB2_DIG_REG0		0x3C
#घोषणा USB2_DIG_REG1		0x40
#घोषणा USB2_DIG_REG2		0x44
#घोषणा USB2_DIG_REG3		0x48
#घोषणा USB2_TEST_REG0		0x4C
#घोषणा USB2_TEST_REG1		0x50
#घोषणा USB2_TEST_REG2		0x54
#घोषणा USB2_CHARGER_REG0	0x58
#घोषणा USB2_OTG_REG0		0x5C
#घोषणा USB2_PHY_MON0		0x60
#घोषणा USB2_RESETVE_REG0	0x64
#घोषणा USB2_ICID_REG0		0x78
#घोषणा USB2_ICID_REG1		0x7C

/* USB2_PLL_REG0 */

/* This is क्रम Ax stepping */
#घोषणा USB2_PLL_FBDIV_SHIFT_MMP3		0
#घोषणा USB2_PLL_FBDIV_MASK_MMP3		(0xFF << 0)

#घोषणा USB2_PLL_REFDIV_SHIFT_MMP3		8
#घोषणा USB2_PLL_REFDIV_MASK_MMP3		(0xF << 8)

#घोषणा USB2_PLL_VDD12_SHIFT_MMP3		12
#घोषणा USB2_PLL_VDD18_SHIFT_MMP3		14

/* This is क्रम B0 stepping */
#घोषणा USB2_PLL_FBDIV_SHIFT_MMP3_B0		0
#घोषणा USB2_PLL_REFDIV_SHIFT_MMP3_B0		9
#घोषणा USB2_PLL_VDD18_SHIFT_MMP3_B0		14
#घोषणा USB2_PLL_FBDIV_MASK_MMP3_B0		0x01FF
#घोषणा USB2_PLL_REFDIV_MASK_MMP3_B0		0x3E00

#घोषणा USB2_PLL_CAL12_SHIFT_MMP3		0
#घोषणा USB2_PLL_CALI12_MASK_MMP3		(0x3 << 0)

#घोषणा USB2_PLL_VCOCAL_START_SHIFT_MMP3	2

#घोषणा USB2_PLL_KVCO_SHIFT_MMP3		4
#घोषणा USB2_PLL_KVCO_MASK_MMP3			(0x7<<4)

#घोषणा USB2_PLL_ICP_SHIFT_MMP3			8
#घोषणा USB2_PLL_ICP_MASK_MMP3			(0x7<<8)

#घोषणा USB2_PLL_LOCK_BYPASS_SHIFT_MMP3		12

#घोषणा USB2_PLL_PU_PLL_SHIFT_MMP3		13
#घोषणा USB2_PLL_PU_PLL_MASK			(0x1 << 13)

#घोषणा USB2_PLL_READY_MASK_MMP3		(0x1 << 15)

/* USB2_TX_REG0 */
#घोषणा USB2_TX_IMPCAL_VTH_SHIFT_MMP3		8
#घोषणा USB2_TX_IMPCAL_VTH_MASK_MMP3		(0x7 << 8)

#घोषणा USB2_TX_RCAL_START_SHIFT_MMP3		13

/* USB2_TX_REG1 */
#घोषणा USB2_TX_CK60_PHSEL_SHIFT_MMP3		0
#घोषणा USB2_TX_CK60_PHSEL_MASK_MMP3		(0xf << 0)

#घोषणा USB2_TX_AMP_SHIFT_MMP3			4
#घोषणा USB2_TX_AMP_MASK_MMP3			(0x7 << 4)

#घोषणा USB2_TX_VDD12_SHIFT_MMP3		8
#घोषणा USB2_TX_VDD12_MASK_MMP3			(0x3 << 8)

/* USB2_TX_REG2 */
#घोषणा USB2_TX_DRV_SLEWRATE_SHIFT		10

/* USB2_RX_REG0 */
#घोषणा USB2_RX_SQ_THRESH_SHIFT_MMP3		4
#घोषणा USB2_RX_SQ_THRESH_MASK_MMP3		(0xf << 4)

#घोषणा USB2_RX_SQ_LENGTH_SHIFT_MMP3		10
#घोषणा USB2_RX_SQ_LENGTH_MASK_MMP3		(0x3 << 10)

/* USB2_ANA_REG1*/
#घोषणा USB2_ANA_PU_ANA_SHIFT_MMP3		14

/* USB2_OTG_REG0 */
#घोषणा USB2_OTG_PU_OTG_SHIFT_MMP3		3

काष्ठा mmp3_usb_phy अणु
	काष्ठा phy *phy;
	व्योम __iomem *base;
पूर्ण;

अटल अचिन्हित पूर्णांक u2o_get(व्योम __iomem *base, अचिन्हित पूर्णांक offset)
अणु
	वापस पढ़ोl_relaxed(base + offset);
पूर्ण

अटल व्योम u2o_set(व्योम __iomem *base, अचिन्हित पूर्णांक offset,
		अचिन्हित पूर्णांक value)
अणु
	u32 reg;

	reg = पढ़ोl_relaxed(base + offset);
	reg |= value;
	ग_लिखोl_relaxed(reg, base + offset);
	पढ़ोl_relaxed(base + offset);
पूर्ण

अटल व्योम u2o_clear(व्योम __iomem *base, अचिन्हित पूर्णांक offset,
		अचिन्हित पूर्णांक value)
अणु
	u32 reg;

	reg = पढ़ोl_relaxed(base + offset);
	reg &= ~value;
	ग_लिखोl_relaxed(reg, base + offset);
	पढ़ोl_relaxed(base + offset);
पूर्ण

अटल पूर्णांक mmp3_usb_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा mmp3_usb_phy *mmp3_usb_phy = phy_get_drvdata(phy);
	व्योम __iomem *base = mmp3_usb_phy->base;

	अगर (cpu_is_mmp3_a0()) अणु
		u2o_clear(base, USB2_PLL_REG0, (USB2_PLL_FBDIV_MASK_MMP3
			| USB2_PLL_REFDIV_MASK_MMP3));
		u2o_set(base, USB2_PLL_REG0,
			0xd << USB2_PLL_REFDIV_SHIFT_MMP3
			| 0xf0 << USB2_PLL_FBDIV_SHIFT_MMP3);
	पूर्ण अन्यथा अगर (cpu_is_mmp3_b0()) अणु
		u2o_clear(base, USB2_PLL_REG0, USB2_PLL_REFDIV_MASK_MMP3_B0
			| USB2_PLL_FBDIV_MASK_MMP3_B0);
		u2o_set(base, USB2_PLL_REG0,
			0xd << USB2_PLL_REFDIV_SHIFT_MMP3_B0
			| 0xf0 << USB2_PLL_FBDIV_SHIFT_MMP3_B0);
	पूर्ण अन्यथा अणु
		dev_err(&phy->dev, "unsupported silicon revision\n");
		वापस -ENODEV;
	पूर्ण

	u2o_clear(base, USB2_PLL_REG1, USB2_PLL_PU_PLL_MASK
		| USB2_PLL_ICP_MASK_MMP3
		| USB2_PLL_KVCO_MASK_MMP3
		| USB2_PLL_CALI12_MASK_MMP3);
	u2o_set(base, USB2_PLL_REG1, 1 << USB2_PLL_PU_PLL_SHIFT_MMP3
		| 1 << USB2_PLL_LOCK_BYPASS_SHIFT_MMP3
		| 3 << USB2_PLL_ICP_SHIFT_MMP3
		| 3 << USB2_PLL_KVCO_SHIFT_MMP3
		| 3 << USB2_PLL_CAL12_SHIFT_MMP3);

	u2o_clear(base, USB2_TX_REG0, USB2_TX_IMPCAL_VTH_MASK_MMP3);
	u2o_set(base, USB2_TX_REG0, 2 << USB2_TX_IMPCAL_VTH_SHIFT_MMP3);

	u2o_clear(base, USB2_TX_REG1, USB2_TX_VDD12_MASK_MMP3
		| USB2_TX_AMP_MASK_MMP3
		| USB2_TX_CK60_PHSEL_MASK_MMP3);
	u2o_set(base, USB2_TX_REG1, 3 << USB2_TX_VDD12_SHIFT_MMP3
		| 4 << USB2_TX_AMP_SHIFT_MMP3
		| 4 << USB2_TX_CK60_PHSEL_SHIFT_MMP3);

	u2o_clear(base, USB2_TX_REG2, 3 << USB2_TX_DRV_SLEWRATE_SHIFT);
	u2o_set(base, USB2_TX_REG2, 2 << USB2_TX_DRV_SLEWRATE_SHIFT);

	u2o_clear(base, USB2_RX_REG0, USB2_RX_SQ_THRESH_MASK_MMP3);
	u2o_set(base, USB2_RX_REG0, 0xa << USB2_RX_SQ_THRESH_SHIFT_MMP3);

	u2o_set(base, USB2_ANA_REG1, 0x1 << USB2_ANA_PU_ANA_SHIFT_MMP3);

	u2o_set(base, USB2_OTG_REG0, 0x1 << USB2_OTG_PU_OTG_SHIFT_MMP3);

	वापस 0;
पूर्ण

अटल पूर्णांक mmp3_usb_phy_calibrate(काष्ठा phy *phy)
अणु
	काष्ठा mmp3_usb_phy *mmp3_usb_phy = phy_get_drvdata(phy);
	व्योम __iomem *base = mmp3_usb_phy->base;
	पूर्णांक loops;

	/*
	 * PLL VCO and TX Impedance Calibration Timing:
	 *
	 *                _____________________________________
	 * PU  __________|
	 *                        _____________________________
	 * VCOCAL START _________|
	 *                                 ___
	 * REG_RCAL_START ________________|   |________|_______
	 *               | 200us | 400us  | 40| 400us  | USB PHY READY
	 */

	udelay(200);
	u2o_set(base, USB2_PLL_REG1, 1 << USB2_PLL_VCOCAL_START_SHIFT_MMP3);
	udelay(400);
	u2o_set(base, USB2_TX_REG0, 1 << USB2_TX_RCAL_START_SHIFT_MMP3);
	udelay(40);
	u2o_clear(base, USB2_TX_REG0, 1 << USB2_TX_RCAL_START_SHIFT_MMP3);
	udelay(400);

	loops = 0;
	जबतक ((u2o_get(base, USB2_PLL_REG1) & USB2_PLL_READY_MASK_MMP3) == 0) अणु
		mdelay(1);
		loops++;
		अगर (loops > 100) अणु
			dev_err(&phy->dev, "PLL_READY not set after 100mS.\n");
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops mmp3_usb_phy_ops = अणु
	.init		= mmp3_usb_phy_init,
	.calibrate	= mmp3_usb_phy_calibrate,
	.owner		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mmp3_usb_phy_of_match[] = अणु
	अणु .compatible = "marvell,mmp3-usb-phy", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mmp3_usb_phy_of_match);

अटल पूर्णांक mmp3_usb_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mmp3_usb_phy *mmp3_usb_phy;
	काष्ठा phy_provider *provider;

	mmp3_usb_phy = devm_kzalloc(dev, माप(*mmp3_usb_phy), GFP_KERNEL);
	अगर (!mmp3_usb_phy)
		वापस -ENOMEM;

	mmp3_usb_phy->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(mmp3_usb_phy->base)) अणु
		dev_err(dev, "failed to remap PHY regs\n");
		वापस PTR_ERR(mmp3_usb_phy->base);
	पूर्ण

	mmp3_usb_phy->phy = devm_phy_create(dev, शून्य, &mmp3_usb_phy_ops);
	अगर (IS_ERR(mmp3_usb_phy->phy)) अणु
		dev_err(dev, "failed to create PHY\n");
		वापस PTR_ERR(mmp3_usb_phy->phy);
	पूर्ण

	phy_set_drvdata(mmp3_usb_phy->phy, mmp3_usb_phy);
	provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);
	अगर (IS_ERR(provider)) अणु
		dev_err(dev, "failed to register PHY provider\n");
		वापस PTR_ERR(provider);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mmp3_usb_phy_driver = अणु
	.probe		= mmp3_usb_phy_probe,
	.driver		= अणु
		.name	= "mmp3-usb-phy",
		.of_match_table = mmp3_usb_phy_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(mmp3_usb_phy_driver);

MODULE_AUTHOR("Lubomir Rintel <lkundrak@v3.sk>");
MODULE_DESCRIPTION("Marvell MMP3 USB PHY Driver");
MODULE_LICENSE("GPL v2");
