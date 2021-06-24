<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PCAP2 Regulator Driver
 *
 * Copyright (c) 2009 Daniel Ribeiro <drwyrm@gmail.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/mfd/ezx-pcap.h>

अटल स्थिर अचिन्हित पूर्णांक V1_table[] = अणु
	2775000, 1275000, 1600000, 1725000, 1825000, 1925000, 2075000, 2275000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक V2_table[] = अणु
	2500000, 2775000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक V3_table[] = अणु
	1075000, 1275000, 1550000, 1725000, 1876000, 1950000, 2075000, 2275000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक V4_table[] = अणु
	1275000, 1550000, 1725000, 1875000, 1950000, 2075000, 2275000, 2775000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक V5_table[] = अणु
	1875000, 2275000, 2475000, 2775000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक V6_table[] = अणु
	2475000, 2775000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक V7_table[] = अणु
	1875000, 2775000,
पूर्ण;

#घोषणा V8_table V4_table

अटल स्थिर अचिन्हित पूर्णांक V9_table[] = अणु
	1575000, 1875000, 2475000, 2775000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक V10_table[] = अणु
	5000000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक VAUX1_table[] = अणु
	1875000, 2475000, 2775000, 3000000,
पूर्ण;

#घोषणा VAUX2_table VAUX1_table

अटल स्थिर अचिन्हित पूर्णांक VAUX3_table[] = अणु
	1200000, 1200000, 1200000, 1200000, 1400000, 1600000, 1800000, 2000000,
	2200000, 2400000, 2600000, 2800000, 3000000, 3200000, 3400000, 3600000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक VAUX4_table[] = अणु
	1800000, 1800000, 3000000, 5000000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक VSIM_table[] = अणु
	1875000, 3000000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक VSIM2_table[] = अणु
	1875000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक VVIB_table[] = अणु
	1300000, 1800000, 2000000, 3000000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक SW1_table[] = अणु
	 900000,  950000, 1000000, 1050000, 1100000, 1150000, 1200000, 1250000,
	1300000, 1350000, 1400000, 1450000, 1500000, 1600000, 1875000, 2250000,
पूर्ण;

#घोषणा SW2_table SW1_table

काष्ठा pcap_regulator अणु
	स्थिर u8 reg;
	स्थिर u8 en;
	स्थिर u8 index;
	स्थिर u8 stby;
	स्थिर u8 lowpwr;
पूर्ण;

#घोषणा NA 0xff

#घोषणा VREG_INFO(_vreg, _reg, _en, _index, _stby, _lowpwr)		\
	[_vreg]	= अणु							\
		.reg		= _reg,					\
		.en		= _en,					\
		.index		= _index,				\
		.stby		= _stby,				\
		.lowpwr		= _lowpwr,				\
	पूर्ण

अटल काष्ठा pcap_regulator vreg_table[] = अणु
	VREG_INFO(V1,    PCAP_REG_VREG1,   1,  2,  18, 0),
	VREG_INFO(V2,    PCAP_REG_VREG1,   5,  6,  19, 22),
	VREG_INFO(V3,    PCAP_REG_VREG1,   7,  8,  20, 23),
	VREG_INFO(V4,    PCAP_REG_VREG1,   11, 12, 21, 24),
	/* V5 STBY and LOWPWR are on PCAP_REG_VREG2 */
	VREG_INFO(V5,    PCAP_REG_VREG1,   15, 16, 12, 19),

	VREG_INFO(V6,    PCAP_REG_VREG2,   1,  2,  14, 20),
	VREG_INFO(V7,    PCAP_REG_VREG2,   3,  4,  15, 21),
	VREG_INFO(V8,    PCAP_REG_VREG2,   5,  6,  16, 22),
	VREG_INFO(V9,    PCAP_REG_VREG2,   9,  10, 17, 23),
	VREG_INFO(V10,   PCAP_REG_VREG2,   10, NA, 18, 24),

	VREG_INFO(VAUX1, PCAP_REG_AUXVREG, 1,  2,  22, 23),
	/* VAUX2 ... VSIM2 STBY and LOWPWR are on PCAP_REG_LOWPWR */
	VREG_INFO(VAUX2, PCAP_REG_AUXVREG, 4,  5,  0,  1),
	VREG_INFO(VAUX3, PCAP_REG_AUXVREG, 7,  8,  2,  3),
	VREG_INFO(VAUX4, PCAP_REG_AUXVREG, 12, 13, 4,  5),
	VREG_INFO(VSIM,  PCAP_REG_AUXVREG, 17, 18, NA, 6),
	VREG_INFO(VSIM2, PCAP_REG_AUXVREG, 16, NA, NA, 7),
	VREG_INFO(VVIB,  PCAP_REG_AUXVREG, 19, 20, NA, NA),

	VREG_INFO(SW1,   PCAP_REG_SWCTRL,  1,  2,  NA, NA),
	VREG_INFO(SW2,   PCAP_REG_SWCTRL,  6,  7,  NA, NA),
	/* SW3 STBY is on PCAP_REG_AUXVREG */
	VREG_INFO(SW3,   PCAP_REG_SWCTRL,  11, 12, 24, NA),

	/* SWxS used to control SWx voltage on standby */
/*	VREG_INFO(SW1S,  PCAP_REG_LOWPWR,  NA, 12, NA, NA),
	VREG_INFO(SW2S,  PCAP_REG_LOWPWR,  NA, 20, NA, NA), */
पूर्ण;

अटल पूर्णांक pcap_regulator_set_voltage_sel(काष्ठा regulator_dev *rdev,
					  अचिन्हित selector)
अणु
	काष्ठा pcap_regulator *vreg = &vreg_table[rdev_get_id(rdev)];
	व्योम *pcap = rdev_get_drvdata(rdev);

	/* the regulator करोesn't support voltage चयनing */
	अगर (rdev->desc->n_voltages == 1)
		वापस -EINVAL;

	वापस ezx_pcap_set_bits(pcap, vreg->reg,
				 (rdev->desc->n_voltages - 1) << vreg->index,
				 selector << vreg->index);
पूर्ण

अटल पूर्णांक pcap_regulator_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा pcap_regulator *vreg = &vreg_table[rdev_get_id(rdev)];
	व्योम *pcap = rdev_get_drvdata(rdev);
	u32 पंचांगp;

	अगर (rdev->desc->n_voltages == 1)
		वापस 0;

	ezx_pcap_पढ़ो(pcap, vreg->reg, &पंचांगp);
	पंचांगp = ((पंचांगp >> vreg->index) & (rdev->desc->n_voltages - 1));
	वापस पंचांगp;
पूर्ण

अटल पूर्णांक pcap_regulator_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा pcap_regulator *vreg = &vreg_table[rdev_get_id(rdev)];
	व्योम *pcap = rdev_get_drvdata(rdev);

	अगर (vreg->en == NA)
		वापस -EINVAL;

	वापस ezx_pcap_set_bits(pcap, vreg->reg, 1 << vreg->en, 1 << vreg->en);
पूर्ण

अटल पूर्णांक pcap_regulator_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा pcap_regulator *vreg = &vreg_table[rdev_get_id(rdev)];
	व्योम *pcap = rdev_get_drvdata(rdev);

	अगर (vreg->en == NA)
		वापस -EINVAL;

	वापस ezx_pcap_set_bits(pcap, vreg->reg, 1 << vreg->en, 0);
पूर्ण

अटल पूर्णांक pcap_regulator_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा pcap_regulator *vreg = &vreg_table[rdev_get_id(rdev)];
	व्योम *pcap = rdev_get_drvdata(rdev);
	u32 पंचांगp;

	अगर (vreg->en == NA)
		वापस -EINVAL;

	ezx_pcap_पढ़ो(pcap, vreg->reg, &पंचांगp);
	वापस (पंचांगp >> vreg->en) & 1;
पूर्ण

अटल स्थिर काष्ठा regulator_ops pcap_regulator_ops = अणु
	.list_voltage	= regulator_list_voltage_table,
	.set_voltage_sel = pcap_regulator_set_voltage_sel,
	.get_voltage_sel = pcap_regulator_get_voltage_sel,
	.enable		= pcap_regulator_enable,
	.disable	= pcap_regulator_disable,
	.is_enabled	= pcap_regulator_is_enabled,
पूर्ण;

#घोषणा VREG(_vreg)						\
	[_vreg]	= अणु						\
		.name		= #_vreg,			\
		.id		= _vreg,			\
		.n_voltages	= ARRAY_SIZE(_vreg##_table),	\
		.volt_table	= _vreg##_table,		\
		.ops		= &pcap_regulator_ops,		\
		.type		= REGULATOR_VOLTAGE,		\
		.owner		= THIS_MODULE,			\
	पूर्ण

अटल स्थिर काष्ठा regulator_desc pcap_regulators[] = अणु
	VREG(V1), VREG(V2), VREG(V3), VREG(V4), VREG(V5), VREG(V6), VREG(V7),
	VREG(V8), VREG(V9), VREG(V10), VREG(VAUX1), VREG(VAUX2), VREG(VAUX3),
	VREG(VAUX4), VREG(VSIM), VREG(VSIM2), VREG(VVIB), VREG(SW1), VREG(SW2),
पूर्ण;

अटल पूर्णांक pcap_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regulator_dev *rdev;
	व्योम *pcap = dev_get_drvdata(pdev->dev.parent);
	काष्ठा regulator_config config = अणु पूर्ण;

	config.dev = &pdev->dev;
	config.init_data = dev_get_platdata(&pdev->dev);
	config.driver_data = pcap;

	rdev = devm_regulator_रेजिस्टर(&pdev->dev, &pcap_regulators[pdev->id],
				       &config);
	अगर (IS_ERR(rdev))
		वापस PTR_ERR(rdev);

	platक्रमm_set_drvdata(pdev, rdev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pcap_regulator_driver = अणु
	.driver = अणु
		.name	= "pcap-regulator",
	पूर्ण,
	.probe	= pcap_regulator_probe,
पूर्ण;

अटल पूर्णांक __init pcap_regulator_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&pcap_regulator_driver);
पूर्ण

अटल व्योम __निकास pcap_regulator_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&pcap_regulator_driver);
पूर्ण

subsys_initcall(pcap_regulator_init);
module_निकास(pcap_regulator_निकास);

MODULE_AUTHOR("Daniel Ribeiro <drwyrm@gmail.com>");
MODULE_DESCRIPTION("PCAP2 Regulator Driver");
MODULE_LICENSE("GPL");
