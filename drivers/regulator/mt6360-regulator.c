<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// Copyright (C) 2020 MediaTek Inc.
//
// Author: Gene Chen <gene_chen@richtek.com>

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>

#समावेश <dt-bindings/regulator/mediatek,mt6360-regulator.h>

क्रमागत अणु
	MT6360_REGULATOR_BUCK1 = 0,
	MT6360_REGULATOR_BUCK2,
	MT6360_REGULATOR_LDO6,
	MT6360_REGULATOR_LDO7,
	MT6360_REGULATOR_LDO1,
	MT6360_REGULATOR_LDO2,
	MT6360_REGULATOR_LDO3,
	MT6360_REGULATOR_LDO5,
	MT6360_REGULATOR_MAX,
पूर्ण;

काष्ठा mt6360_irq_mapping अणु
	स्थिर अक्षर *name;
	irq_handler_t handler;
पूर्ण;

काष्ठा mt6360_regulator_desc अणु
	स्थिर काष्ठा regulator_desc desc;
	अचिन्हित पूर्णांक mode_reg;
	अचिन्हित पूर्णांक mode_mask;
	अचिन्हित पूर्णांक state_reg;
	अचिन्हित पूर्णांक state_mask;
	स्थिर काष्ठा mt6360_irq_mapping *irq_tables;
	पूर्णांक irq_table_size;
पूर्ण;

काष्ठा mt6360_regulator_data अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
पूर्ण;

अटल irqवापस_t mt6360_pgb_event_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा regulator_dev *rdev = data;

	regulator_notअगरier_call_chain(rdev, REGULATOR_EVENT_FAIL, शून्य);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t mt6360_oc_event_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा regulator_dev *rdev = data;

	regulator_notअगरier_call_chain(rdev, REGULATOR_EVENT_OVER_CURRENT, शून्य);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t mt6360_ov_event_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा regulator_dev *rdev = data;

	regulator_notअगरier_call_chain(rdev, REGULATOR_EVENT_REGULATION_OUT, शून्य);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t mt6360_uv_event_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा regulator_dev *rdev = data;

	regulator_notअगरier_call_chain(rdev, REGULATOR_EVENT_UNDER_VOLTAGE, शून्य);
	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा mt6360_irq_mapping buck1_irq_tbls[] = अणु
	अणु "buck1_pgb_evt", mt6360_pgb_event_handler पूर्ण,
	अणु "buck1_oc_evt", mt6360_oc_event_handler पूर्ण,
	अणु "buck1_ov_evt", mt6360_ov_event_handler पूर्ण,
	अणु "buck1_uv_evt", mt6360_uv_event_handler पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mt6360_irq_mapping buck2_irq_tbls[] = अणु
	अणु "buck2_pgb_evt", mt6360_pgb_event_handler पूर्ण,
	अणु "buck2_oc_evt", mt6360_oc_event_handler पूर्ण,
	अणु "buck2_ov_evt", mt6360_ov_event_handler पूर्ण,
	अणु "buck2_uv_evt", mt6360_uv_event_handler पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mt6360_irq_mapping lकरो6_irq_tbls[] = अणु
	अणु "ldo6_pgb_evt", mt6360_pgb_event_handler पूर्ण,
	अणु "ldo6_oc_evt", mt6360_oc_event_handler पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mt6360_irq_mapping lकरो7_irq_tbls[] = अणु
	अणु "ldo7_pgb_evt", mt6360_pgb_event_handler पूर्ण,
	अणु "ldo7_oc_evt", mt6360_oc_event_handler पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mt6360_irq_mapping lकरो1_irq_tbls[] = अणु
	अणु "ldo1_pgb_evt", mt6360_pgb_event_handler पूर्ण,
	अणु "ldo1_oc_evt", mt6360_oc_event_handler पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mt6360_irq_mapping lकरो2_irq_tbls[] = अणु
	अणु "ldo2_pgb_evt", mt6360_pgb_event_handler पूर्ण,
	अणु "ldo2_oc_evt", mt6360_oc_event_handler पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mt6360_irq_mapping lकरो3_irq_tbls[] = अणु
	अणु "ldo3_pgb_evt", mt6360_pgb_event_handler पूर्ण,
	अणु "ldo3_oc_evt", mt6360_oc_event_handler पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mt6360_irq_mapping lकरो5_irq_tbls[] = अणु
	अणु "ldo5_pgb_evt", mt6360_pgb_event_handler पूर्ण,
	अणु "ldo5_oc_evt", mt6360_oc_event_handler पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा linear_range buck_vout_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(300000, 0x00, 0xc7, 5000),
	REGULATOR_LINEAR_RANGE(1300000, 0xc8, 0xff, 0),
पूर्ण;

अटल स्थिर काष्ठा linear_range lकरो_vout_ranges1[] = अणु
	REGULATOR_LINEAR_RANGE(500000, 0x00, 0x09, 10000),
	REGULATOR_LINEAR_RANGE(600000, 0x0a, 0x10, 0),
	REGULATOR_LINEAR_RANGE(610000, 0x11, 0x19, 10000),
	REGULATOR_LINEAR_RANGE(700000, 0x1a, 0x20, 0),
	REGULATOR_LINEAR_RANGE(710000, 0x21, 0x29, 10000),
	REGULATOR_LINEAR_RANGE(800000, 0x2a, 0x30, 0),
	REGULATOR_LINEAR_RANGE(810000, 0x31, 0x39, 10000),
	REGULATOR_LINEAR_RANGE(900000, 0x3a, 0x40, 0),
	REGULATOR_LINEAR_RANGE(910000, 0x41, 0x49, 10000),
	REGULATOR_LINEAR_RANGE(1000000, 0x4a, 0x50, 0),
	REGULATOR_LINEAR_RANGE(1010000, 0x51, 0x59, 10000),
	REGULATOR_LINEAR_RANGE(1100000, 0x5a, 0x60, 0),
	REGULATOR_LINEAR_RANGE(1110000, 0x61, 0x69, 10000),
	REGULATOR_LINEAR_RANGE(1200000, 0x6a, 0x70, 0),
	REGULATOR_LINEAR_RANGE(1210000, 0x71, 0x79, 10000),
	REGULATOR_LINEAR_RANGE(1300000, 0x7a, 0x80, 0),
	REGULATOR_LINEAR_RANGE(1310000, 0x81, 0x89, 10000),
	REGULATOR_LINEAR_RANGE(1400000, 0x8a, 0x90, 0),
	REGULATOR_LINEAR_RANGE(1410000, 0x91, 0x99, 10000),
	REGULATOR_LINEAR_RANGE(1500000, 0x9a, 0xa0, 0),
	REGULATOR_LINEAR_RANGE(1510000, 0xa1, 0xa9, 10000),
	REGULATOR_LINEAR_RANGE(1600000, 0xaa, 0xb0, 0),
	REGULATOR_LINEAR_RANGE(1610000, 0xb1, 0xb9, 10000),
	REGULATOR_LINEAR_RANGE(1700000, 0xba, 0xc0, 0),
	REGULATOR_LINEAR_RANGE(1710000, 0xc1, 0xc9, 10000),
	REGULATOR_LINEAR_RANGE(1800000, 0xca, 0xd0, 0),
	REGULATOR_LINEAR_RANGE(1810000, 0xd1, 0xd9, 10000),
	REGULATOR_LINEAR_RANGE(1900000, 0xda, 0xe0, 0),
	REGULATOR_LINEAR_RANGE(1910000, 0xe1, 0xe9, 10000),
	REGULATOR_LINEAR_RANGE(2000000, 0xea, 0xf0, 0),
	REGULATOR_LINEAR_RANGE(2010000, 0xf1, 0xf9, 10000),
	REGULATOR_LINEAR_RANGE(2100000, 0xfa, 0xff, 0),
पूर्ण;

अटल स्थिर काष्ठा linear_range lकरो_vout_ranges2[] = अणु
	REGULATOR_LINEAR_RANGE(1200000, 0x00, 0x09, 10000),
	REGULATOR_LINEAR_RANGE(1300000, 0x0a, 0x10, 0),
	REGULATOR_LINEAR_RANGE(1310000, 0x11, 0x19, 10000),
	REGULATOR_LINEAR_RANGE(1400000, 0x1a, 0x1f, 0),
	REGULATOR_LINEAR_RANGE(1500000, 0x20, 0x29, 10000),
	REGULATOR_LINEAR_RANGE(1600000, 0x2a, 0x2f, 0),
	REGULATOR_LINEAR_RANGE(1700000, 0x30, 0x39, 10000),
	REGULATOR_LINEAR_RANGE(1800000, 0x3a, 0x40, 0),
	REGULATOR_LINEAR_RANGE(1810000, 0x41, 0x49, 10000),
	REGULATOR_LINEAR_RANGE(1900000, 0x4a, 0x4f, 0),
	REGULATOR_LINEAR_RANGE(2000000, 0x50, 0x59, 10000),
	REGULATOR_LINEAR_RANGE(2100000, 0x5a, 0x60, 0),
	REGULATOR_LINEAR_RANGE(2110000, 0x61, 0x69, 10000),
	REGULATOR_LINEAR_RANGE(2200000, 0x6a, 0x6f, 0),
	REGULATOR_LINEAR_RANGE(2500000, 0x70, 0x79, 10000),
	REGULATOR_LINEAR_RANGE(2600000, 0x7a, 0x7f, 0),
	REGULATOR_LINEAR_RANGE(2700000, 0x80, 0x89, 10000),
	REGULATOR_LINEAR_RANGE(2800000, 0x8a, 0x90, 0),
	REGULATOR_LINEAR_RANGE(2810000, 0x91, 0x99, 10000),
	REGULATOR_LINEAR_RANGE(2900000, 0x9a, 0xa0, 0),
	REGULATOR_LINEAR_RANGE(2910000, 0xa1, 0xa9, 10000),
	REGULATOR_LINEAR_RANGE(3000000, 0xaa, 0xb0, 0),
	REGULATOR_LINEAR_RANGE(3010000, 0xb1, 0xb9, 10000),
	REGULATOR_LINEAR_RANGE(3100000, 0xba, 0xc0, 0),
	REGULATOR_LINEAR_RANGE(3110000, 0xc1, 0xc9, 10000),
	REGULATOR_LINEAR_RANGE(3200000, 0xca, 0xcf, 0),
	REGULATOR_LINEAR_RANGE(3300000, 0xd0, 0xd9, 10000),
	REGULATOR_LINEAR_RANGE(3400000, 0xda, 0xe0, 0),
	REGULATOR_LINEAR_RANGE(3410000, 0xe1, 0xe9, 10000),
	REGULATOR_LINEAR_RANGE(3500000, 0xea, 0xf0, 0),
	REGULATOR_LINEAR_RANGE(3510000, 0xf1, 0xf9, 10000),
	REGULATOR_LINEAR_RANGE(3600000, 0xfa, 0xff, 0),
पूर्ण;

अटल स्थिर काष्ठा linear_range lकरो_vout_ranges3[] = अणु
	REGULATOR_LINEAR_RANGE(2700000, 0x00, 0x09, 10000),
	REGULATOR_LINEAR_RANGE(2800000, 0x0a, 0x10, 0),
	REGULATOR_LINEAR_RANGE(2810000, 0x11, 0x19, 10000),
	REGULATOR_LINEAR_RANGE(2900000, 0x1a, 0x20, 0),
	REGULATOR_LINEAR_RANGE(2910000, 0x21, 0x29, 10000),
	REGULATOR_LINEAR_RANGE(3000000, 0x2a, 0x30, 0),
	REGULATOR_LINEAR_RANGE(3010000, 0x31, 0x39, 10000),
	REGULATOR_LINEAR_RANGE(3100000, 0x3a, 0x40, 0),
	REGULATOR_LINEAR_RANGE(3110000, 0x41, 0x49, 10000),
	REGULATOR_LINEAR_RANGE(3200000, 0x4a, 0x4f, 0),
	REGULATOR_LINEAR_RANGE(3300000, 0x50, 0x59, 10000),
	REGULATOR_LINEAR_RANGE(3400000, 0x5a, 0x60, 0),
	REGULATOR_LINEAR_RANGE(3410000, 0x61, 0x69, 10000),
	REGULATOR_LINEAR_RANGE(3500000, 0x6a, 0x70, 0),
	REGULATOR_LINEAR_RANGE(3510000, 0x71, 0x79, 10000),
	REGULATOR_LINEAR_RANGE(3600000, 0x7a, 0x7f, 0),
पूर्ण;

अटल पूर्णांक mt6360_regulator_set_mode(काष्ठा regulator_dev *rdev,
				     अचिन्हित पूर्णांक mode)
अणु
	स्थिर काष्ठा mt6360_regulator_desc *rdesc = (काष्ठा mt6360_regulator_desc *)rdev->desc;
	काष्ठा regmap *regmap = rdev_get_regmap(rdev);
	पूर्णांक shअगरt = ffs(rdesc->mode_mask) - 1;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	चयन (mode) अणु
	हाल REGULATOR_MODE_NORMAL:
		val = MT6360_OPMODE_NORMAL;
		अवरोध;
	हाल REGULATOR_MODE_STANDBY:
		val = MT6360_OPMODE_ULP;
		अवरोध;
	हाल REGULATOR_MODE_IDLE:
		val = MT6360_OPMODE_LP;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = regmap_update_bits(regmap, rdesc->mode_reg, rdesc->mode_mask, val << shअगरt);
	अगर (ret) अणु
		dev_err(&rdev->dev, "%s: fail (%d)\n", __func__, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक mt6360_regulator_get_mode(काष्ठा regulator_dev *rdev)
अणु
	स्थिर काष्ठा mt6360_regulator_desc *rdesc = (काष्ठा mt6360_regulator_desc *)rdev->desc;
	काष्ठा regmap *regmap = rdev_get_regmap(rdev);
	पूर्णांक shअगरt = ffs(rdesc->mode_mask) - 1;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(regmap, rdesc->mode_reg, &val);
	अगर (ret)
		वापस ret;

	val &= rdesc->mode_mask;
	val >>= shअगरt;

	चयन (val) अणु
	हाल MT6360_OPMODE_LP:
		वापस REGULATOR_MODE_IDLE;
	हाल MT6360_OPMODE_ULP:
		वापस REGULATOR_MODE_STANDBY;
	हाल MT6360_OPMODE_NORMAL:
		वापस REGULATOR_MODE_NORMAL;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mt6360_regulator_get_status(काष्ठा regulator_dev *rdev)
अणु
	स्थिर काष्ठा mt6360_regulator_desc *rdesc = (काष्ठा mt6360_regulator_desc *)rdev->desc;
	काष्ठा regmap *regmap = rdev_get_regmap(rdev);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(regmap, rdesc->state_reg, &val);
	अगर (ret)
		वापस ret;

	अगर (val & rdesc->state_mask)
		वापस REGULATOR_STATUS_ON;

	वापस REGULATOR_STATUS_OFF;
पूर्ण

अटल स्थिर काष्ठा regulator_ops mt6360_regulator_ops = अणु
	.list_voltage = regulator_list_voltage_linear_range,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_mode = mt6360_regulator_set_mode,
	.get_mode = mt6360_regulator_get_mode,
	.get_status = mt6360_regulator_get_status,
पूर्ण;

अटल अचिन्हित पूर्णांक mt6360_regulator_of_map_mode(अचिन्हित पूर्णांक hw_mode)
अणु
	चयन (hw_mode) अणु
	हाल MT6360_OPMODE_NORMAL:
		वापस REGULATOR_MODE_NORMAL;
	हाल MT6360_OPMODE_LP:
		वापस REGULATOR_MODE_IDLE;
	हाल MT6360_OPMODE_ULP:
		वापस REGULATOR_MODE_STANDBY;
	शेष:
		वापस REGULATOR_MODE_INVALID;
	पूर्ण
पूर्ण

#घोषणा MT6360_REGULATOR_DESC(_name, _sname, ereg, emask, vreg,	vmask,	\
			      mreg, mmask, streg, sपंचांगask, vranges,	\
			      vcnts, offon_delay, irq_tbls)		\
अणु									\
	.desc = अणु							\
		.name = #_name,						\
		.supply_name = #_sname,					\
		.id =  MT6360_REGULATOR_##_name,			\
		.of_match = of_match_ptr(#_name),			\
		.regulators_node = of_match_ptr("regulator"),		\
		.of_map_mode = mt6360_regulator_of_map_mode,		\
		.owner = THIS_MODULE,					\
		.ops = &mt6360_regulator_ops,				\
		.type = REGULATOR_VOLTAGE,				\
		.vsel_reg = vreg,					\
		.vsel_mask = vmask,					\
		.enable_reg = ereg,					\
		.enable_mask = emask,					\
		.linear_ranges = vranges,				\
		.n_linear_ranges = ARRAY_SIZE(vranges),			\
		.n_voltages = vcnts,					\
		.off_on_delay = offon_delay,				\
	पूर्ण,								\
	.mode_reg = mreg,						\
	.mode_mask = mmask,						\
	.state_reg = streg,						\
	.state_mask = sपंचांगask,						\
	.irq_tables = irq_tbls,						\
	.irq_table_size = ARRAY_SIZE(irq_tbls),				\
पूर्ण

अटल स्थिर काष्ठा mt6360_regulator_desc mt6360_regulator_descs[] =  अणु
	MT6360_REGULATOR_DESC(BUCK1, BUCK1_VIN, 0x117, 0x40, 0x110, 0xff, 0x117, 0x30, 0x117, 0x04,
			      buck_vout_ranges, 256, 0, buck1_irq_tbls),
	MT6360_REGULATOR_DESC(BUCK2, BUCK2_VIN, 0x127, 0x40, 0x120, 0xff, 0x127, 0x30, 0x127, 0x04,
			      buck_vout_ranges, 256, 0, buck2_irq_tbls),
	MT6360_REGULATOR_DESC(LDO6, LDO_VIN3, 0x137, 0x40, 0x13B, 0xff, 0x137, 0x30, 0x137, 0x04,
			      lकरो_vout_ranges1, 256, 0, lकरो6_irq_tbls),
	MT6360_REGULATOR_DESC(LDO7, LDO_VIN3, 0x131, 0x40, 0x135, 0xff, 0x131, 0x30, 0x131, 0x04,
			      lकरो_vout_ranges1, 256, 0, lकरो7_irq_tbls),
	MT6360_REGULATOR_DESC(LDO1, LDO_VIN1, 0x217, 0x40, 0x21B, 0xff, 0x217, 0x30, 0x217, 0x04,
			      lकरो_vout_ranges2, 256, 0, lकरो1_irq_tbls),
	MT6360_REGULATOR_DESC(LDO2, LDO_VIN1, 0x211, 0x40, 0x215, 0xff, 0x211, 0x30, 0x211, 0x04,
			      lकरो_vout_ranges2, 256, 0, lकरो2_irq_tbls),
	MT6360_REGULATOR_DESC(LDO3, LDO_VIN1, 0x205, 0x40, 0x209, 0xff, 0x205, 0x30, 0x205, 0x04,
			      lकरो_vout_ranges2, 256, 100, lकरो3_irq_tbls),
	MT6360_REGULATOR_DESC(LDO5, LDO_VIN2, 0x20B, 0x40, 0x20F, 0x7f, 0x20B, 0x30, 0x20B, 0x04,
			      lकरो_vout_ranges3, 128, 100, lकरो5_irq_tbls),
पूर्ण;

अटल पूर्णांक mt6360_regulator_irq_रेजिस्टर(काष्ठा platक्रमm_device *pdev,
					 काष्ठा regulator_dev *rdev,
					 स्थिर काष्ठा mt6360_irq_mapping *tbls,
					 पूर्णांक tbl_size)
अणु
	पूर्णांक i, irq, ret;

	क्रम (i = 0; i < tbl_size; i++) अणु
		स्थिर काष्ठा mt6360_irq_mapping *irq_desc = tbls + i;

		irq = platक्रमm_get_irq_byname(pdev, irq_desc->name);
		अगर (irq < 0)
			वापस irq;

		ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य, irq_desc->handler, 0,
						irq_desc->name, rdev);
		अगर (ret) अणु
			dev_err(&pdev->dev, "Fail to request %s irq\n", irq_desc->name);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt6360_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mt6360_regulator_data *mrd;
	काष्ठा regulator_config config = अणुपूर्ण;
	पूर्णांक i, ret;

	mrd = devm_kzalloc(&pdev->dev, माप(*mrd), GFP_KERNEL);
	अगर (!mrd)
		वापस -ENOMEM;

	mrd->dev = &pdev->dev;

	mrd->regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!mrd->regmap) अणु
		dev_err(&pdev->dev, "Failed to get parent regmap\n");
		वापस -ENODEV;
	पूर्ण

	config.dev = pdev->dev.parent;
	config.driver_data = mrd;
	config.regmap = mrd->regmap;

	क्रम (i = 0; i < ARRAY_SIZE(mt6360_regulator_descs); i++) अणु
		स्थिर काष्ठा mt6360_regulator_desc *rdesc = mt6360_regulator_descs + i;
		काष्ठा regulator_dev *rdev;

		rdev = devm_regulator_रेजिस्टर(&pdev->dev, &rdesc->desc, &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(&pdev->dev, "Failed to register  %d regulator\n", i);
			वापस PTR_ERR(rdev);
		पूर्ण

		ret = mt6360_regulator_irq_रेजिस्टर(pdev, rdev, rdesc->irq_tables,
						    rdesc->irq_table_size);
		अगर (ret) अणु
			dev_err(&pdev->dev, "Failed to register  %d regulator irqs\n", i);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id mt6360_regulator_id_table[] = अणु
	अणु "mt6360-regulator", 0 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, mt6360_regulator_id_table);

अटल काष्ठा platक्रमm_driver mt6360_regulator_driver = अणु
	.driver = अणु
		.name = "mt6360-regulator",
	पूर्ण,
	.probe = mt6360_regulator_probe,
	.id_table = mt6360_regulator_id_table,
पूर्ण;
module_platक्रमm_driver(mt6360_regulator_driver);

MODULE_AUTHOR("Gene Chen <gene_chen@richtek.com>");
MODULE_DESCRIPTION("MT6360 Regulator Driver");
MODULE_LICENSE("GPL v2");
