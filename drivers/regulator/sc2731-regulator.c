<शैली गुरु>
 //SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2017 Spपढ़ोtrum Communications Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/of_regulator.h>

/*
 * SC2731 regulator lock रेजिस्टर
 */
#घोषणा SC2731_PWR_WR_PROT		0xf0c
#घोषणा SC2731_WR_UNLOCK_VALUE		0x6e7f

/*
 * SC2731 enable रेजिस्टर
 */
#घोषणा SC2731_POWER_PD_SW		0xc28
#घोषणा SC2731_LDO_CAMA0_PD		0xcfc
#घोषणा SC2731_LDO_CAMA1_PD		0xd04
#घोषणा SC2731_LDO_CAMMOT_PD		0xd0c
#घोषणा SC2731_LDO_VLDO_PD		0xd6c
#घोषणा SC2731_LDO_EMMCCORE_PD		0xd2c
#घोषणा SC2731_LDO_SDCORE_PD		0xd74
#घोषणा SC2731_LDO_SDIO_PD		0xd70
#घोषणा SC2731_LDO_WIFIPA_PD		0xd4c
#घोषणा SC2731_LDO_USB33_PD		0xd5c
#घोषणा SC2731_LDO_CAMD0_PD		0xd7c
#घोषणा SC2731_LDO_CAMD1_PD		0xd84
#घोषणा SC2731_LDO_CON_PD		0xd8c
#घोषणा SC2731_LDO_CAMIO_PD		0xd94
#घोषणा SC2731_LDO_SRAM_PD		0xd78

/*
 * SC2731 enable mask
 */
#घोषणा SC2731_DCDC_CPU0_PD_MASK	BIT(4)
#घोषणा SC2731_DCDC_CPU1_PD_MASK	BIT(3)
#घोषणा SC2731_DCDC_RF_PD_MASK		BIT(11)
#घोषणा SC2731_LDO_CAMA0_PD_MASK	BIT(0)
#घोषणा SC2731_LDO_CAMA1_PD_MASK	BIT(0)
#घोषणा SC2731_LDO_CAMMOT_PD_MASK	BIT(0)
#घोषणा SC2731_LDO_VLDO_PD_MASK		BIT(0)
#घोषणा SC2731_LDO_EMMCCORE_PD_MASK	BIT(0)
#घोषणा SC2731_LDO_SDCORE_PD_MASK	BIT(0)
#घोषणा SC2731_LDO_SDIO_PD_MASK		BIT(0)
#घोषणा SC2731_LDO_WIFIPA_PD_MASK	BIT(0)
#घोषणा SC2731_LDO_USB33_PD_MASK	BIT(0)
#घोषणा SC2731_LDO_CAMD0_PD_MASK	BIT(0)
#घोषणा SC2731_LDO_CAMD1_PD_MASK	BIT(0)
#घोषणा SC2731_LDO_CON_PD_MASK		BIT(0)
#घोषणा SC2731_LDO_CAMIO_PD_MASK	BIT(0)
#घोषणा SC2731_LDO_SRAM_PD_MASK		BIT(0)

/*
 * SC2731 vsel रेजिस्टर
 */
#घोषणा SC2731_DCDC_CPU0_VOL		0xc54
#घोषणा SC2731_DCDC_CPU1_VOL		0xc64
#घोषणा SC2731_DCDC_RF_VOL		0xcb8
#घोषणा SC2731_LDO_CAMA0_VOL		0xd00
#घोषणा SC2731_LDO_CAMA1_VOL		0xd08
#घोषणा SC2731_LDO_CAMMOT_VOL		0xd10
#घोषणा SC2731_LDO_VLDO_VOL		0xd28
#घोषणा SC2731_LDO_EMMCCORE_VOL		0xd30
#घोषणा SC2731_LDO_SDCORE_VOL		0xd38
#घोषणा SC2731_LDO_SDIO_VOL		0xd40
#घोषणा SC2731_LDO_WIFIPA_VOL		0xd50
#घोषणा SC2731_LDO_USB33_VOL		0xd60
#घोषणा SC2731_LDO_CAMD0_VOL		0xd80
#घोषणा SC2731_LDO_CAMD1_VOL		0xd88
#घोषणा SC2731_LDO_CON_VOL		0xd90
#घोषणा SC2731_LDO_CAMIO_VOL		0xd98
#घोषणा SC2731_LDO_SRAM_VOL		0xdB0

/*
 * SC2731 vsel रेजिस्टर mask
 */
#घोषणा SC2731_DCDC_CPU0_VOL_MASK	GENMASK(8, 0)
#घोषणा SC2731_DCDC_CPU1_VOL_MASK	GENMASK(8, 0)
#घोषणा SC2731_DCDC_RF_VOL_MASK		GENMASK(8, 0)
#घोषणा SC2731_LDO_CAMA0_VOL_MASK	GENMASK(7, 0)
#घोषणा SC2731_LDO_CAMA1_VOL_MASK	GENMASK(7, 0)
#घोषणा SC2731_LDO_CAMMOT_VOL_MASK	GENMASK(7, 0)
#घोषणा SC2731_LDO_VLDO_VOL_MASK	GENMASK(7, 0)
#घोषणा SC2731_LDO_EMMCCORE_VOL_MASK	GENMASK(7, 0)
#घोषणा SC2731_LDO_SDCORE_VOL_MASK	GENMASK(7, 0)
#घोषणा SC2731_LDO_SDIO_VOL_MASK	GENMASK(7, 0)
#घोषणा SC2731_LDO_WIFIPA_VOL_MASK	GENMASK(7, 0)
#घोषणा SC2731_LDO_USB33_VOL_MASK	GENMASK(7, 0)
#घोषणा SC2731_LDO_CAMD0_VOL_MASK	GENMASK(6, 0)
#घोषणा SC2731_LDO_CAMD1_VOL_MASK	GENMASK(6, 0)
#घोषणा SC2731_LDO_CON_VOL_MASK		GENMASK(6, 0)
#घोषणा SC2731_LDO_CAMIO_VOL_MASK	GENMASK(6, 0)
#घोषणा SC2731_LDO_SRAM_VOL_MASK	GENMASK(6, 0)

क्रमागत sc2731_regulator_id अणु
	SC2731_BUCK_CPU0,
	SC2731_BUCK_CPU1,
	SC2731_BUCK_RF,
	SC2731_LDO_CAMA0,
	SC2731_LDO_CAMA1,
	SC2731_LDO_CAMMOT,
	SC2731_LDO_VLDO,
	SC2731_LDO_EMMCCORE,
	SC2731_LDO_SDCORE,
	SC2731_LDO_SDIO,
	SC2731_LDO_WIFIPA,
	SC2731_LDO_USB33,
	SC2731_LDO_CAMD0,
	SC2731_LDO_CAMD1,
	SC2731_LDO_CON,
	SC2731_LDO_CAMIO,
	SC2731_LDO_SRAM,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops sc2731_regu_linear_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.list_voltage = regulator_list_voltage_linear,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
पूर्ण;

#घोषणा SC2731_REGU_LINEAR(_id, en_reg, en_mask, vreg, vmask,	\
			  vstep, vmin, vmax) अणु			\
	.name			= #_id,				\
	.of_match		= of_match_ptr(#_id),		\
	.ops			= &sc2731_regu_linear_ops,	\
	.type			= REGULATOR_VOLTAGE,		\
	.id			= SC2731_##_id,			\
	.owner			= THIS_MODULE,			\
	.min_uV			= vmin,				\
	.n_voltages		= ((vmax) - (vmin)) / (vstep) + 1,	\
	.uV_step		= vstep,			\
	.enable_is_inverted	= true,				\
	.enable_val		= 0,				\
	.enable_reg		= en_reg,			\
	.enable_mask		= en_mask,			\
	.vsel_reg		= vreg,				\
	.vsel_mask		= vmask,			\
पूर्ण

अटल स्थिर काष्ठा regulator_desc regulators[] = अणु
	SC2731_REGU_LINEAR(BUCK_CPU0, SC2731_POWER_PD_SW,
			   SC2731_DCDC_CPU0_PD_MASK, SC2731_DCDC_CPU0_VOL,
			   SC2731_DCDC_CPU0_VOL_MASK, 3125, 400000, 1996875),
	SC2731_REGU_LINEAR(BUCK_CPU1, SC2731_POWER_PD_SW,
			   SC2731_DCDC_CPU1_PD_MASK, SC2731_DCDC_CPU1_VOL,
			   SC2731_DCDC_CPU1_VOL_MASK, 3125, 400000, 1996875),
	SC2731_REGU_LINEAR(BUCK_RF, SC2731_POWER_PD_SW, SC2731_DCDC_RF_PD_MASK,
			   SC2731_DCDC_RF_VOL, SC2731_DCDC_RF_VOL_MASK,
			   3125, 600000, 2196875),
	SC2731_REGU_LINEAR(LDO_CAMA0, SC2731_LDO_CAMA0_PD,
			   SC2731_LDO_CAMA0_PD_MASK, SC2731_LDO_CAMA0_VOL,
			   SC2731_LDO_CAMA0_VOL_MASK, 10000, 1200000, 3750000),
	SC2731_REGU_LINEAR(LDO_CAMA1, SC2731_LDO_CAMA1_PD,
			   SC2731_LDO_CAMA1_PD_MASK, SC2731_LDO_CAMA1_VOL,
			   SC2731_LDO_CAMA1_VOL_MASK, 10000, 1200000, 3750000),
	SC2731_REGU_LINEAR(LDO_CAMMOT, SC2731_LDO_CAMMOT_PD,
			   SC2731_LDO_CAMMOT_PD_MASK, SC2731_LDO_CAMMOT_VOL,
			   SC2731_LDO_CAMMOT_VOL_MASK, 10000, 1200000, 3750000),
	SC2731_REGU_LINEAR(LDO_VLDO, SC2731_LDO_VLDO_PD,
			   SC2731_LDO_VLDO_PD_MASK, SC2731_LDO_VLDO_VOL,
			   SC2731_LDO_VLDO_VOL_MASK, 10000, 1200000, 3750000),
	SC2731_REGU_LINEAR(LDO_EMMCCORE, SC2731_LDO_EMMCCORE_PD,
			   SC2731_LDO_EMMCCORE_PD_MASK, SC2731_LDO_EMMCCORE_VOL,
			   SC2731_LDO_EMMCCORE_VOL_MASK, 10000, 1200000,
			   3750000),
	SC2731_REGU_LINEAR(LDO_SDCORE, SC2731_LDO_SDCORE_PD,
			   SC2731_LDO_SDCORE_PD_MASK, SC2731_LDO_SDCORE_VOL,
			   SC2731_LDO_SDCORE_VOL_MASK, 10000, 1200000, 3750000),
	SC2731_REGU_LINEAR(LDO_SDIO, SC2731_LDO_SDIO_PD,
			   SC2731_LDO_SDIO_PD_MASK, SC2731_LDO_SDIO_VOL,
			   SC2731_LDO_SDIO_VOL_MASK, 10000, 1200000, 3750000),
	SC2731_REGU_LINEAR(LDO_WIFIPA, SC2731_LDO_WIFIPA_PD,
			   SC2731_LDO_WIFIPA_PD_MASK, SC2731_LDO_WIFIPA_VOL,
			   SC2731_LDO_WIFIPA_VOL_MASK, 10000, 1200000, 3750000),
	SC2731_REGU_LINEAR(LDO_USB33, SC2731_LDO_USB33_PD,
			   SC2731_LDO_USB33_PD_MASK, SC2731_LDO_USB33_VOL,
			   SC2731_LDO_USB33_VOL_MASK, 10000, 1200000, 3750000),
	SC2731_REGU_LINEAR(LDO_CAMD0, SC2731_LDO_CAMD0_PD,
			   SC2731_LDO_CAMD0_PD_MASK, SC2731_LDO_CAMD0_VOL,
			   SC2731_LDO_CAMD0_VOL_MASK, 6250, 1000000, 1793750),
	SC2731_REGU_LINEAR(LDO_CAMD1, SC2731_LDO_CAMD1_PD,
			   SC2731_LDO_CAMD1_PD_MASK, SC2731_LDO_CAMD1_VOL,
			   SC2731_LDO_CAMD1_VOL_MASK, 6250, 1000000, 1793750),
	SC2731_REGU_LINEAR(LDO_CON, SC2731_LDO_CON_PD,
			   SC2731_LDO_CON_PD_MASK, SC2731_LDO_CON_VOL,
			   SC2731_LDO_CON_VOL_MASK, 6250, 1000000, 1793750),
	SC2731_REGU_LINEAR(LDO_CAMIO, SC2731_LDO_CAMIO_PD,
			   SC2731_LDO_CAMIO_PD_MASK, SC2731_LDO_CAMIO_VOL,
			   SC2731_LDO_CAMIO_VOL_MASK, 6250, 1000000, 1793750),
	SC2731_REGU_LINEAR(LDO_SRAM, SC2731_LDO_SRAM_PD,
			   SC2731_LDO_SRAM_PD_MASK, SC2731_LDO_SRAM_VOL,
			   SC2731_LDO_SRAM_VOL_MASK, 6250, 1000000, 1793750),
पूर्ण;

अटल पूर्णांक sc2731_regulator_unlock(काष्ठा regmap *regmap)
अणु
	वापस regmap_ग_लिखो(regmap, SC2731_PWR_WR_PROT,
			    SC2731_WR_UNLOCK_VALUE);
पूर्ण

अटल पूर्णांक sc2731_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i, ret;
	काष्ठा regmap *regmap;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_dev *rdev;

	regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!regmap) अणु
		dev_err(&pdev->dev, "failed to get regmap.\n");
		वापस -ENODEV;
	पूर्ण

	ret = sc2731_regulator_unlock(regmap);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to release regulator lock\n");
		वापस ret;
	पूर्ण

	config.dev = &pdev->dev;
	config.regmap = regmap;

	क्रम (i = 0; i < ARRAY_SIZE(regulators); i++) अणु
		rdev = devm_regulator_रेजिस्टर(&pdev->dev, &regulators[i],
					       &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(&pdev->dev, "failed to register regulator %s\n",
				regulators[i].name);
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sc2731_regulator_driver = अणु
	.driver = अणु
		.name = "sc27xx-regulator",
	पूर्ण,
	.probe = sc2731_regulator_probe,
पूर्ण;

module_platक्रमm_driver(sc2731_regulator_driver);

MODULE_AUTHOR("Chen Junhui <erick.chen@spreadtrum.com>");
MODULE_DESCRIPTION("Spreadtrum SC2731 regulator driver");
MODULE_LICENSE("GPL v2");
