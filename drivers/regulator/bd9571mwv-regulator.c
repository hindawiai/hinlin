<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ROHM BD9571MWV-M and BD9574MWF-M regulator driver
 *
 * Copyright (C) 2017 Marek Vasut <marek.vasut+renesas@gmail.com>
 *
 * Based on the TPS65086 driver
 *
 * NOTE: VD09 is missing
 */

#समावेश <linux/mfd/rohm-generic.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>

#समावेश <linux/mfd/bd9571mwv.h>

काष्ठा bd9571mwv_reg अणु
	काष्ठा regmap *regmap;

	/* DDR Backup Power */
	u8 bkup_mode_cnt_keepon;	/* from "rohm,ddr-backup-power" */
	u8 bkup_mode_cnt_saved;
	bool bkup_mode_enabled;

	/* Power चयन type */
	bool rstbmode_level;
	bool rstbmode_pulse;
पूर्ण;

क्रमागत bd9571mwv_regulators अणु VD09, VD18, VD25, VD33, DVFS पूर्ण;

#घोषणा BD9571MWV_REG(_name, _of, _id, _ops, _vr, _vm, _nv, _min, _step, _lmin)\
	अणु							\
		.name			= _name,		\
		.of_match		= of_match_ptr(_of),	\
		.regulators_node	= "regulators",		\
		.id			= _id,			\
		.ops			= &_ops,		\
		.n_voltages		= _nv,			\
		.type			= REGULATOR_VOLTAGE,	\
		.owner			= THIS_MODULE,		\
		.vsel_reg		= _vr,			\
		.vsel_mask		= _vm,			\
		.min_uV			= _min,			\
		.uV_step		= _step,		\
		.linear_min_sel		= _lmin,		\
	पूर्ण

अटल पूर्णांक bd9571mwv_avs_get_moni_state(काष्ठा regulator_dev *rdev)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(rdev->regmap, BD9571MWV_AVS_SET_MONI, &val);
	अगर (ret != 0)
		वापस ret;

	वापस val & BD9571MWV_AVS_SET_MONI_MASK;
पूर्ण

अटल पूर्णांक bd9571mwv_avs_set_voltage_sel_regmap(काष्ठा regulator_dev *rdev,
						अचिन्हित पूर्णांक sel)
अणु
	पूर्णांक ret;

	ret = bd9571mwv_avs_get_moni_state(rdev);
	अगर (ret < 0)
		वापस ret;

	वापस regmap_ग_लिखो_bits(rdev->regmap, BD9571MWV_AVS_VD09_VID(ret),
				 rdev->desc->vsel_mask, sel);
पूर्ण

अटल पूर्णांक bd9571mwv_avs_get_voltage_sel_regmap(काष्ठा regulator_dev *rdev)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = bd9571mwv_avs_get_moni_state(rdev);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_पढ़ो(rdev->regmap, BD9571MWV_AVS_VD09_VID(ret), &val);
	अगर (ret != 0)
		वापस ret;

	val &= rdev->desc->vsel_mask;
	val >>= ffs(rdev->desc->vsel_mask) - 1;

	वापस val;
पूर्ण

अटल पूर्णांक bd9571mwv_reg_set_voltage_sel_regmap(काष्ठा regulator_dev *rdev,
						अचिन्हित पूर्णांक sel)
अणु
	वापस regmap_ग_लिखो_bits(rdev->regmap, BD9571MWV_DVFS_SETVID,
				 rdev->desc->vsel_mask, sel);
पूर्ण

/* Operations permitted on AVS voltage regulator */
अटल स्थिर काष्ठा regulator_ops avs_ops = अणु
	.set_voltage_sel	= bd9571mwv_avs_set_voltage_sel_regmap,
	.map_voltage		= regulator_map_voltage_linear,
	.get_voltage_sel	= bd9571mwv_avs_get_voltage_sel_regmap,
	.list_voltage		= regulator_list_voltage_linear,
पूर्ण;

/* Operations permitted on voltage regulators */
अटल स्थिर काष्ठा regulator_ops reg_ops = अणु
	.set_voltage_sel	= bd9571mwv_reg_set_voltage_sel_regmap,
	.map_voltage		= regulator_map_voltage_linear,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.list_voltage		= regulator_list_voltage_linear,
पूर्ण;

/* Operations permitted on voltage monitors */
अटल स्थिर काष्ठा regulator_ops vid_ops = अणु
	.map_voltage		= regulator_map_voltage_linear,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.list_voltage		= regulator_list_voltage_linear,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc regulators[] = अणु
	BD9571MWV_REG("VD09", "vd09", VD09, avs_ops, 0, 0x7f,
		      0x6f, 600000, 10000, 0x3c),
	BD9571MWV_REG("VD18", "vd18", VD18, vid_ops, BD9571MWV_VD18_VID, 0xf,
		      16, 1625000, 25000, 0),
	BD9571MWV_REG("VD25", "vd25", VD25, vid_ops, BD9571MWV_VD25_VID, 0xf,
		      16, 2150000, 50000, 0),
	BD9571MWV_REG("VD33", "vd33", VD33, vid_ops, BD9571MWV_VD33_VID, 0xf,
		      11, 2800000, 100000, 0),
	BD9571MWV_REG("DVFS", "dvfs", DVFS, reg_ops,
		      BD9571MWV_DVFS_MONIVDAC, 0x7f,
		      0x6f, 600000, 10000, 0x3c),
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक bd9571mwv_bkup_mode_पढ़ो(काष्ठा bd9571mwv_reg *bdreg,
				    अचिन्हित पूर्णांक *mode)
अणु
	पूर्णांक ret;

	ret = regmap_पढ़ो(bdreg->regmap, BD9571MWV_BKUP_MODE_CNT, mode);
	अगर (ret) अणु
		dev_err(regmap_get_device(bdreg->regmap),
			"failed to read backup mode (%d)\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bd9571mwv_bkup_mode_ग_लिखो(काष्ठा bd9571mwv_reg *bdreg,
				     अचिन्हित पूर्णांक mode)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(bdreg->regmap, BD9571MWV_BKUP_MODE_CNT, mode);
	अगर (ret) अणु
		dev_err(regmap_get_device(bdreg->regmap),
			"failed to configure backup mode 0x%x (%d)\n",
			mode, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार backup_mode_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा bd9571mwv_reg *bdreg = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%s\n", bdreg->bkup_mode_enabled ? "on" : "off");
पूर्ण

अटल sमाप_प्रकार backup_mode_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा bd9571mwv_reg *bdreg = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक mode;
	पूर्णांक ret;

	अगर (!count)
		वापस 0;

	ret = kstrtobool(buf, &bdreg->bkup_mode_enabled);
	अगर (ret)
		वापस ret;

	अगर (!bdreg->rstbmode_level)
		वापस count;

	/*
	 * Configure DDR Backup Mode, to change the role of the accessory घातer
	 * चयन from a घातer चयन to a wake-up चयन, or vice versa
	 */
	ret = bd9571mwv_bkup_mode_पढ़ो(bdreg, &mode);
	अगर (ret)
		वापस ret;

	mode &= ~BD9571MWV_BKUP_MODE_CNT_KEEPON_MASK;
	अगर (bdreg->bkup_mode_enabled)
		mode |= bdreg->bkup_mode_cnt_keepon;

	ret = bd9571mwv_bkup_mode_ग_लिखो(bdreg, mode);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(backup_mode);

अटल पूर्णांक bd9571mwv_suspend(काष्ठा device *dev)
अणु
	काष्ठा bd9571mwv_reg *bdreg = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक mode;
	पूर्णांक ret;

	अगर (!bdreg->bkup_mode_enabled)
		वापस 0;

	/* Save DDR Backup Mode */
	ret = bd9571mwv_bkup_mode_पढ़ो(bdreg, &mode);
	अगर (ret)
		वापस ret;

	bdreg->bkup_mode_cnt_saved = mode;

	अगर (!bdreg->rstbmode_pulse)
		वापस 0;

	/* Enable DDR Backup Mode */
	mode &= ~BD9571MWV_BKUP_MODE_CNT_KEEPON_MASK;
	mode |= bdreg->bkup_mode_cnt_keepon;

	अगर (mode != bdreg->bkup_mode_cnt_saved)
		वापस bd9571mwv_bkup_mode_ग_लिखो(bdreg, mode);

	वापस 0;
पूर्ण

अटल पूर्णांक bd9571mwv_resume(काष्ठा device *dev)
अणु
	काष्ठा bd9571mwv_reg *bdreg = dev_get_drvdata(dev);

	अगर (!bdreg->bkup_mode_enabled)
		वापस 0;

	/* Restore DDR Backup Mode */
	वापस bd9571mwv_bkup_mode_ग_लिखो(bdreg, bdreg->bkup_mode_cnt_saved);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops bd9571mwv_pm  = अणु
	SET_SYSTEM_SLEEP_PM_OPS(bd9571mwv_suspend, bd9571mwv_resume)
पूर्ण;

अटल पूर्णांक bd9571mwv_regulator_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	device_हटाओ_file(&pdev->dev, &dev_attr_backup_mode);
	वापस 0;
पूर्ण
#घोषणा DEV_PM_OPS	&bd9571mwv_pm
#अन्यथा
#घोषणा DEV_PM_OPS	शून्य
#घोषणा bd9571mwv_regulator_हटाओ	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल पूर्णांक bd9571mwv_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा bd9571mwv_reg *bdreg;
	काष्ठा regulator_dev *rdev;
	अचिन्हित पूर्णांक val;
	पूर्णांक i;
	क्रमागत rohm_chip_type chip = platक्रमm_get_device_id(pdev)->driver_data;

	bdreg = devm_kzalloc(&pdev->dev, माप(*bdreg), GFP_KERNEL);
	अगर (!bdreg)
		वापस -ENOMEM;

	bdreg->regmap = dev_get_regmap(pdev->dev.parent, शून्य);

	platक्रमm_set_drvdata(pdev, bdreg);

	config.dev = &pdev->dev;
	config.dev->of_node = pdev->dev.parent->of_node;
	config.driver_data = bdreg;
	config.regmap = bdreg->regmap;

	क्रम (i = 0; i < ARRAY_SIZE(regulators); i++) अणु
		/* BD9574MWF supports DVFS only */
		अगर (chip == ROHM_CHIP_TYPE_BD9574 && regulators[i].id != DVFS)
			जारी;
		rdev = devm_regulator_रेजिस्टर(&pdev->dev, &regulators[i],
					       &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(&pdev->dev, "failed to register %s regulator\n",
				regulators[i].name);
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण

	val = 0;
	of_property_पढ़ो_u32(config.dev->of_node, "rohm,ddr-backup-power", &val);
	अगर (val & ~BD9571MWV_BKUP_MODE_CNT_KEEPON_MASK) अणु
		dev_err(&pdev->dev, "invalid %s mode %u\n",
			"rohm,ddr-backup-power", val);
		वापस -EINVAL;
	पूर्ण
	bdreg->bkup_mode_cnt_keepon = val;

	bdreg->rstbmode_level = of_property_पढ़ो_bool(config.dev->of_node,
						      "rohm,rstbmode-level");
	bdreg->rstbmode_pulse = of_property_पढ़ो_bool(config.dev->of_node,
						      "rohm,rstbmode-pulse");
	अगर (bdreg->rstbmode_level && bdreg->rstbmode_pulse) अणु
		dev_err(&pdev->dev, "only one rohm,rstbmode-* may be specified");
		वापस -EINVAL;
	पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
	अगर (bdreg->bkup_mode_cnt_keepon) अणु
		पूर्णांक ret;

		/*
		 * Backup mode is enabled by शेष in pulse mode, but needs
		 * explicit user setup in level mode.
		 */
		bdreg->bkup_mode_enabled = bdreg->rstbmode_pulse;

		ret = device_create_file(&pdev->dev, &dev_attr_backup_mode);
		अगर (ret)
			वापस ret;
	पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id bd9571mwv_regulator_id_table[] = अणु
	अणु "bd9571mwv-regulator", ROHM_CHIP_TYPE_BD9571 पूर्ण,
	अणु "bd9574mwf-regulator", ROHM_CHIP_TYPE_BD9574 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, bd9571mwv_regulator_id_table);

अटल काष्ठा platक्रमm_driver bd9571mwv_regulator_driver = अणु
	.driver = अणु
		.name = "bd9571mwv-regulator",
		.pm = DEV_PM_OPS,
	पूर्ण,
	.probe = bd9571mwv_regulator_probe,
	.हटाओ = bd9571mwv_regulator_हटाओ,
	.id_table = bd9571mwv_regulator_id_table,
पूर्ण;
module_platक्रमm_driver(bd9571mwv_regulator_driver);

MODULE_AUTHOR("Marek Vasut <marek.vasut+renesas@gmail.com>");
MODULE_DESCRIPTION("BD9571MWV Regulator driver");
MODULE_LICENSE("GPL v2");
