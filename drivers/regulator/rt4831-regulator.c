<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/bitops.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/regulator/driver.h>

क्रमागत अणु
	DSV_OUT_VLCM = 0,
	DSV_OUT_VPOS,
	DSV_OUT_VNEG,
	DSV_OUT_MAX
पूर्ण;

#घोषणा RT4831_REG_DSVEN	0x09
#घोषणा RT4831_REG_VLCM		0x0c
#घोषणा RT4831_REG_VPOS		0x0d
#घोषणा RT4831_REG_VNEG		0x0e
#घोषणा RT4831_REG_FLAGS	0x0f

#घोषणा RT4831_VOLT_MASK	GENMASK(5, 0)
#घोषणा RT4831_DSVMODE_SHIFT	5
#घोषणा RT4831_DSVMODE_MASK	GENMASK(7, 5)
#घोषणा RT4831_POSADEN_MASK	BIT(4)
#घोषणा RT4831_NEGADEN_MASK	BIT(3)
#घोषणा RT4831_POSEN_MASK	BIT(2)
#घोषणा RT4831_NEGEN_MASK	BIT(1)

#घोषणा RT4831_OTP_MASK		BIT(6)
#घोषणा RT4831_LCMOVP_MASK	BIT(5)
#घोषणा RT4831_VPOSSCP_MASK	BIT(3)
#घोषणा RT4831_VNEGSCP_MASK	BIT(2)

#घोषणा DSV_MODE_NORMAL		(0x4 << RT4831_DSVMODE_SHIFT)
#घोषणा DSV_MODE_BYPASS		(0x6 << RT4831_DSVMODE_SHIFT)
#घोषणा STEP_UV			50000
#घोषणा VLCM_MIN_UV		4000000
#घोषणा VLCM_MAX_UV		7150000
#घोषणा VLCM_N_VOLTAGES		((VLCM_MAX_UV - VLCM_MIN_UV) / STEP_UV + 1)
#घोषणा VPN_MIN_UV		4000000
#घोषणा VPN_MAX_UV		6500000
#घोषणा VPN_N_VOLTAGES		((VPN_MAX_UV - VPN_MIN_UV) / STEP_UV + 1)

अटल पूर्णांक rt4831_get_error_flags(काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक *flags)
अणु
	काष्ठा regmap *regmap = rdev_get_regmap(rdev);
	पूर्णांक rid = rdev_get_id(rdev);
	अचिन्हित पूर्णांक val, events = 0;
	पूर्णांक ret;

	ret = regmap_पढ़ो(regmap, RT4831_REG_FLAGS, &val);
	अगर (ret)
		वापस ret;

	अगर (val & RT4831_OTP_MASK)
		events |= REGULATOR_ERROR_OVER_TEMP;

	अगर (rid == DSV_OUT_VLCM && (val & RT4831_LCMOVP_MASK))
		events |= REGULATOR_ERROR_OVER_CURRENT;

	अगर (rid == DSV_OUT_VPOS && (val & RT4831_VPOSSCP_MASK))
		events |= REGULATOR_ERROR_OVER_CURRENT;

	अगर (rid == DSV_OUT_VNEG && (val & RT4831_VNEGSCP_MASK))
		events |= REGULATOR_ERROR_OVER_CURRENT;

	*flags = events;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regulator_ops rt4831_dsvlcm_ops = अणु
	.list_voltage = regulator_list_voltage_linear,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_bypass = regulator_set_bypass_regmap,
	.get_bypass = regulator_get_bypass_regmap,
	.get_error_flags = rt4831_get_error_flags,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops rt4831_dsvpn_ops = अणु
	.list_voltage = regulator_list_voltage_linear,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.set_active_disअक्षरge = regulator_set_active_disअक्षरge_regmap,
	.get_error_flags = rt4831_get_error_flags,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc rt4831_regulator_descs[] = अणु
	अणु
		.name = "DSVLCM",
		.ops = &rt4831_dsvlcm_ops,
		.of_match = of_match_ptr("DSVLCM"),
		.regulators_node = of_match_ptr("regulators"),
		.type = REGULATOR_VOLTAGE,
		.id = DSV_OUT_VLCM,
		.n_voltages = VLCM_N_VOLTAGES,
		.min_uV = VLCM_MIN_UV,
		.uV_step = STEP_UV,
		.vsel_reg = RT4831_REG_VLCM,
		.vsel_mask = RT4831_VOLT_MASK,
		.bypass_reg = RT4831_REG_DSVEN,
		.bypass_val_on = DSV_MODE_BYPASS,
		.bypass_val_off = DSV_MODE_NORMAL,
	पूर्ण,
	अणु
		.name = "DSVP",
		.ops = &rt4831_dsvpn_ops,
		.of_match = of_match_ptr("DSVP"),
		.regulators_node = of_match_ptr("regulators"),
		.type = REGULATOR_VOLTAGE,
		.id = DSV_OUT_VPOS,
		.n_voltages = VPN_N_VOLTAGES,
		.min_uV = VPN_MIN_UV,
		.uV_step = STEP_UV,
		.vsel_reg = RT4831_REG_VPOS,
		.vsel_mask = RT4831_VOLT_MASK,
		.enable_reg = RT4831_REG_DSVEN,
		.enable_mask = RT4831_POSEN_MASK,
		.active_disअक्षरge_reg = RT4831_REG_DSVEN,
		.active_disअक्षरge_mask = RT4831_POSADEN_MASK,
	पूर्ण,
	अणु
		.name = "DSVN",
		.ops = &rt4831_dsvpn_ops,
		.of_match = of_match_ptr("DSVN"),
		.regulators_node = of_match_ptr("regulators"),
		.type = REGULATOR_VOLTAGE,
		.id = DSV_OUT_VNEG,
		.n_voltages = VPN_N_VOLTAGES,
		.min_uV = VPN_MIN_UV,
		.uV_step = STEP_UV,
		.vsel_reg = RT4831_REG_VNEG,
		.vsel_mask = RT4831_VOLT_MASK,
		.enable_reg = RT4831_REG_DSVEN,
		.enable_mask = RT4831_NEGEN_MASK,
		.active_disअक्षरge_reg = RT4831_REG_DSVEN,
		.active_disअक्षरge_mask = RT4831_NEGADEN_MASK,
	पूर्ण
पूर्ण;

अटल पूर्णांक rt4831_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regmap *regmap;
	काष्ठा regulator_dev *rdev;
	काष्ठा regulator_config config = अणुपूर्ण;
	पूर्णांक i, ret;

	regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!regmap) अणु
		dev_err(&pdev->dev, "Failed to init regmap\n");
		वापस -ENODEV;
	पूर्ण

	/* Configure DSV mode to normal by शेष */
	ret = regmap_update_bits(regmap, RT4831_REG_DSVEN, RT4831_DSVMODE_MASK, DSV_MODE_NORMAL);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to configure dsv mode to normal\n");
		वापस ret;
	पूर्ण

	config.dev = pdev->dev.parent;
	config.regmap = regmap;

	क्रम (i = 0; i < DSV_OUT_MAX; i++) अणु
		rdev = devm_regulator_रेजिस्टर(&pdev->dev, rt4831_regulator_descs + i, &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(&pdev->dev, "Failed to register %d regulator\n", i);
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id rt4831_regulator_match[] = अणु
	अणु "rt4831-regulator", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, rt4831_regulator_match);

अटल काष्ठा platक्रमm_driver rt4831_regulator_driver = अणु
	.driver = अणु
		.name = "rt4831-regulator",
	पूर्ण,
	.id_table = rt4831_regulator_match,
	.probe = rt4831_regulator_probe,
पूर्ण;
module_platक्रमm_driver(rt4831_regulator_driver);

MODULE_AUTHOR("ChiYuan Huang <cy_huang@richtek.com>");
MODULE_LICENSE("GPL v2");
