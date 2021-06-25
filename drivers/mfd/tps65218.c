<शैली गुरु>
/*
 * Driver क्रम TPS65218 Integrated घातer management chipsets
 *
 * Copyright (C) 2014 Texas Instruments Incorporated - https://www.ti.com/
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether expressed or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/regmap.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mutex.h>

#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/tps65218.h>

#घोषणा TPS65218_PASSWORD_REGS_UNLOCK   0x7D

अटल स्थिर काष्ठा mfd_cell tps65218_cells[] = अणु
	अणु
		.name = "tps65218-pwrbutton",
		.of_compatible = "ti,tps65218-pwrbutton",
	पूर्ण,
	अणु
		.name = "tps65218-gpio",
		.of_compatible = "ti,tps65218-gpio",
	पूर्ण,
	अणु .name = "tps65218-regulator", पूर्ण,
पूर्ण;

/**
 * tps65218_reg_ग_लिखो: Write a single tps65218 रेजिस्टर.
 *
 * @tps: Device to ग_लिखो to.
 * @reg: Register to ग_लिखो to.
 * @val: Value to ग_लिखो.
 * @level: Password रक्षित level
 */
पूर्णांक tps65218_reg_ग_लिखो(काष्ठा tps65218 *tps, अचिन्हित पूर्णांक reg,
			अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक level)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक xor_reg_val;

	चयन (level) अणु
	हाल TPS65218_PROTECT_NONE:
		वापस regmap_ग_लिखो(tps->regmap, reg, val);
	हाल TPS65218_PROTECT_L1:
		xor_reg_val = reg ^ TPS65218_PASSWORD_REGS_UNLOCK;
		ret = regmap_ग_लिखो(tps->regmap, TPS65218_REG_PASSWORD,
							xor_reg_val);
		अगर (ret < 0)
			वापस ret;

		वापस regmap_ग_लिखो(tps->regmap, reg, val);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(tps65218_reg_ग_लिखो);

/**
 * tps65218_update_bits: Modअगरy bits w.r.t mask, val and level.
 *
 * @tps: Device to ग_लिखो to.
 * @reg: Register to पढ़ो-ग_लिखो to.
 * @mask: Mask.
 * @val: Value to ग_लिखो.
 * @level: Password रक्षित level
 */
अटल पूर्णांक tps65218_update_bits(काष्ठा tps65218 *tps, अचिन्हित पूर्णांक reg,
		अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक level)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक data;

	ret = regmap_पढ़ो(tps->regmap, reg, &data);
	अगर (ret) अणु
		dev_err(tps->dev, "Read from reg 0x%x failed\n", reg);
		वापस ret;
	पूर्ण

	data &= ~mask;
	data |= val & mask;

	mutex_lock(&tps->tps_lock);
	ret = tps65218_reg_ग_लिखो(tps, reg, data, level);
	अगर (ret)
		dev_err(tps->dev, "Write for reg 0x%x failed\n", reg);
	mutex_unlock(&tps->tps_lock);

	वापस ret;
पूर्ण

पूर्णांक tps65218_set_bits(काष्ठा tps65218 *tps, अचिन्हित पूर्णांक reg,
		अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक level)
अणु
	वापस tps65218_update_bits(tps, reg, mask, val, level);
पूर्ण
EXPORT_SYMBOL_GPL(tps65218_set_bits);

पूर्णांक tps65218_clear_bits(काष्ठा tps65218 *tps, अचिन्हित पूर्णांक reg,
		अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक level)
अणु
	वापस tps65218_update_bits(tps, reg, mask, 0, level);
पूर्ण
EXPORT_SYMBOL_GPL(tps65218_clear_bits);

अटल स्थिर काष्ठा regmap_range tps65218_yes_ranges[] = अणु
	regmap_reg_range(TPS65218_REG_INT1, TPS65218_REG_INT2),
	regmap_reg_range(TPS65218_REG_STATUS, TPS65218_REG_STATUS),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table tps65218_अस्थिर_table = अणु
	.yes_ranges = tps65218_yes_ranges,
	.n_yes_ranges = ARRAY_SIZE(tps65218_yes_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config tps65218_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.cache_type = REGCACHE_RBTREE,
	.अस्थिर_table = &tps65218_अस्थिर_table,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq tps65218_irqs[] = अणु
	/* INT1 IRQs */
	[TPS65218_PRGC_IRQ] = अणु
		.mask = TPS65218_INT1_PRGC,
	पूर्ण,
	[TPS65218_CC_AQC_IRQ] = अणु
		.mask = TPS65218_INT1_CC_AQC,
	पूर्ण,
	[TPS65218_HOT_IRQ] = अणु
		.mask = TPS65218_INT1_HOT,
	पूर्ण,
	[TPS65218_PB_IRQ] = अणु
		.mask = TPS65218_INT1_PB,
	पूर्ण,
	[TPS65218_AC_IRQ] = अणु
		.mask = TPS65218_INT1_AC,
	पूर्ण,
	[TPS65218_VPRG_IRQ] = अणु
		.mask = TPS65218_INT1_VPRG,
	पूर्ण,
	[TPS65218_INVALID1_IRQ] = अणु
	पूर्ण,
	[TPS65218_INVALID2_IRQ] = अणु
	पूर्ण,
	/* INT2 IRQs*/
	[TPS65218_LS1_I_IRQ] = अणु
		.mask = TPS65218_INT2_LS1_I,
		.reg_offset = 1,
	पूर्ण,
	[TPS65218_LS2_I_IRQ] = अणु
		.mask = TPS65218_INT2_LS2_I,
		.reg_offset = 1,
	पूर्ण,
	[TPS65218_LS3_I_IRQ] = अणु
		.mask = TPS65218_INT2_LS3_I,
		.reg_offset = 1,
	पूर्ण,
	[TPS65218_LS1_F_IRQ] = अणु
		.mask = TPS65218_INT2_LS1_F,
		.reg_offset = 1,
	पूर्ण,
	[TPS65218_LS2_F_IRQ] = अणु
		.mask = TPS65218_INT2_LS2_F,
		.reg_offset = 1,
	पूर्ण,
	[TPS65218_LS3_F_IRQ] = अणु
		.mask = TPS65218_INT2_LS3_F,
		.reg_offset = 1,
	पूर्ण,
	[TPS65218_INVALID3_IRQ] = अणु
	पूर्ण,
	[TPS65218_INVALID4_IRQ] = अणु
	पूर्ण,
पूर्ण;

अटल काष्ठा regmap_irq_chip tps65218_irq_chip = अणु
	.name = "tps65218",
	.irqs = tps65218_irqs,
	.num_irqs = ARRAY_SIZE(tps65218_irqs),

	.num_regs = 2,
	.mask_base = TPS65218_REG_INT_MASK1,
	.status_base = TPS65218_REG_INT1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_tps65218_match_table[] = अणु
	अणु .compatible = "ti,tps65218", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_tps65218_match_table);

अटल पूर्णांक tps65218_voltage_set_strict(काष्ठा tps65218 *tps)
अणु
	u32 strict;

	अगर (of_property_पढ़ो_u32(tps->dev->of_node,
				 "ti,strict-supply-voltage-supervision",
				 &strict))
		वापस 0;

	अगर (strict != 0 && strict != 1) अणु
		dev_err(tps->dev,
			"Invalid ti,strict-supply-voltage-supervision value\n");
		वापस -EINVAL;
	पूर्ण

	tps65218_update_bits(tps, TPS65218_REG_CONFIG1,
			     TPS65218_CONFIG1_STRICT,
			     strict ? TPS65218_CONFIG1_STRICT : 0,
			     TPS65218_PROTECT_L1);
	वापस 0;
पूर्ण

अटल पूर्णांक tps65218_voltage_set_uv_hyst(काष्ठा tps65218 *tps)
अणु
	u32 hyst;

	अगर (of_property_पढ़ो_u32(tps->dev->of_node,
				 "ti,under-voltage-hyst-microvolt", &hyst))
		वापस 0;

	अगर (hyst != 400000 && hyst != 200000) अणु
		dev_err(tps->dev,
			"Invalid ti,under-voltage-hyst-microvolt value\n");
		वापस -EINVAL;
	पूर्ण

	tps65218_update_bits(tps, TPS65218_REG_CONFIG2,
			     TPS65218_CONFIG2_UVLOHYS,
			     hyst == 400000 ? TPS65218_CONFIG2_UVLOHYS : 0,
			     TPS65218_PROTECT_L1);
	वापस 0;
पूर्ण

अटल पूर्णांक tps65218_voltage_set_uvlo(काष्ठा tps65218 *tps)
अणु
	u32 uvlo;
	पूर्णांक uvloval;

	अगर (of_property_पढ़ो_u32(tps->dev->of_node,
				 "ti,under-voltage-limit-microvolt", &uvlo))
		वापस 0;

	चयन (uvlo) अणु
	हाल 2750000:
		uvloval = TPS65218_CONFIG1_UVLO_2750000;
		अवरोध;
	हाल 2950000:
		uvloval = TPS65218_CONFIG1_UVLO_2950000;
		अवरोध;
	हाल 3250000:
		uvloval = TPS65218_CONFIG1_UVLO_3250000;
		अवरोध;
	हाल 3350000:
		uvloval = TPS65218_CONFIG1_UVLO_3350000;
		अवरोध;
	शेष:
		dev_err(tps->dev,
			"Invalid ti,under-voltage-limit-microvolt value\n");
		वापस -EINVAL;
	पूर्ण

	tps65218_update_bits(tps, TPS65218_REG_CONFIG1,
			     TPS65218_CONFIG1_UVLO_MASK, uvloval,
			     TPS65218_PROTECT_L1);
	वापस 0;
पूर्ण

अटल पूर्णांक tps65218_probe(काष्ठा i2c_client *client,
				स्थिर काष्ठा i2c_device_id *ids)
अणु
	काष्ठा tps65218 *tps;
	पूर्णांक ret;
	अचिन्हित पूर्णांक chipid;

	tps = devm_kzalloc(&client->dev, माप(*tps), GFP_KERNEL);
	अगर (!tps)
		वापस -ENOMEM;

	i2c_set_clientdata(client, tps);
	tps->dev = &client->dev;
	tps->irq = client->irq;
	tps->regmap = devm_regmap_init_i2c(client, &tps65218_regmap_config);
	अगर (IS_ERR(tps->regmap)) अणु
		ret = PTR_ERR(tps->regmap);
		dev_err(tps->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	mutex_init(&tps->tps_lock);

	ret = devm_regmap_add_irq_chip(&client->dev, tps->regmap, tps->irq,
				       IRQF_ONESHOT, 0, &tps65218_irq_chip,
				       &tps->irq_data);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_पढ़ो(tps->regmap, TPS65218_REG_CHIPID, &chipid);
	अगर (ret) अणु
		dev_err(tps->dev, "Failed to read chipid: %d\n", ret);
		वापस ret;
	पूर्ण

	tps->rev = chipid & TPS65218_CHIPID_REV_MASK;

	ret = tps65218_voltage_set_strict(tps);
	अगर (ret)
		वापस ret;

	ret = tps65218_voltage_set_uvlo(tps);
	अगर (ret)
		वापस ret;

	ret = tps65218_voltage_set_uv_hyst(tps);
	अगर (ret)
		वापस ret;

	ret = mfd_add_devices(tps->dev, PLATFORM_DEVID_AUTO, tps65218_cells,
			      ARRAY_SIZE(tps65218_cells), शून्य, 0,
			      regmap_irq_get_करोमुख्य(tps->irq_data));

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tps65218_id_table[] = अणु
	अणु "tps65218", TPS65218 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tps65218_id_table);

अटल काष्ठा i2c_driver tps65218_driver = अणु
	.driver		= अणु
		.name	= "tps65218",
		.of_match_table = of_tps65218_match_table,
	पूर्ण,
	.probe		= tps65218_probe,
	.id_table       = tps65218_id_table,
पूर्ण;

module_i2c_driver(tps65218_driver);

MODULE_AUTHOR("J Keerthy <j-keerthy@ti.com>");
MODULE_DESCRIPTION("TPS65218 chip family multi-function driver");
MODULE_LICENSE("GPL v2");
