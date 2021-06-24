<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * TI Palmas MFD Driver
 *
 * Copyright 2011-2012 Texas Instruments Inc.
 *
 * Author: Graeme Gregory <gg@slimlogic.co.uk>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/regmap.h>
#समावेश <linux/err.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/palmas.h>
#समावेश <linux/of_device.h>

अटल स्थिर काष्ठा regmap_config palmas_regmap_config[PALMAS_NUM_CLIENTS] = अणु
	अणु
		.reg_bits = 8,
		.val_bits = 8,
		.max_रेजिस्टर = PALMAS_BASE_TO_REG(PALMAS_PU_PD_OD_BASE,
					PALMAS_PRIMARY_SECONDARY_PAD3),
	पूर्ण,
	अणु
		.reg_bits = 8,
		.val_bits = 8,
		.max_रेजिस्टर = PALMAS_BASE_TO_REG(PALMAS_GPADC_BASE,
					PALMAS_GPADC_SMPS_VSEL_MONITORING),
	पूर्ण,
	अणु
		.reg_bits = 8,
		.val_bits = 8,
		.max_रेजिस्टर = PALMAS_BASE_TO_REG(PALMAS_TRIM_GPADC_BASE,
					PALMAS_GPADC_TRIM16),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq tps65917_irqs[] = अणु
	/* INT1 IRQs */
	[TPS65917_RESERVED1] = अणु
		.mask = TPS65917_RESERVED,
	पूर्ण,
	[TPS65917_PWRON_IRQ] = अणु
		.mask = TPS65917_INT1_STATUS_PWRON,
	पूर्ण,
	[TPS65917_LONG_PRESS_KEY_IRQ] = अणु
		.mask = TPS65917_INT1_STATUS_LONG_PRESS_KEY,
	पूर्ण,
	[TPS65917_RESERVED2] = अणु
		.mask = TPS65917_RESERVED,
	पूर्ण,
	[TPS65917_PWRDOWN_IRQ] = अणु
		.mask = TPS65917_INT1_STATUS_PWRDOWN,
	पूर्ण,
	[TPS65917_HOTDIE_IRQ] = अणु
		.mask = TPS65917_INT1_STATUS_HOTDIE,
	पूर्ण,
	[TPS65917_VSYS_MON_IRQ] = अणु
		.mask = TPS65917_INT1_STATUS_VSYS_MON,
	पूर्ण,
	[TPS65917_RESERVED3] = अणु
		.mask = TPS65917_RESERVED,
	पूर्ण,
	/* INT2 IRQs*/
	[TPS65917_RESERVED4] = अणु
		.mask = TPS65917_RESERVED,
		.reg_offset = 1,
	पूर्ण,
	[TPS65917_OTP_ERROR_IRQ] = अणु
		.mask = TPS65917_INT2_STATUS_OTP_ERROR,
		.reg_offset = 1,
	पूर्ण,
	[TPS65917_WDT_IRQ] = अणु
		.mask = TPS65917_INT2_STATUS_WDT,
		.reg_offset = 1,
	पूर्ण,
	[TPS65917_RESERVED5] = अणु
		.mask = TPS65917_RESERVED,
		.reg_offset = 1,
	पूर्ण,
	[TPS65917_RESET_IN_IRQ] = अणु
		.mask = TPS65917_INT2_STATUS_RESET_IN,
		.reg_offset = 1,
	पूर्ण,
	[TPS65917_FSD_IRQ] = अणु
		.mask = TPS65917_INT2_STATUS_FSD,
		.reg_offset = 1,
	पूर्ण,
	[TPS65917_SHORT_IRQ] = अणु
		.mask = TPS65917_INT2_STATUS_SHORT,
		.reg_offset = 1,
	पूर्ण,
	[TPS65917_RESERVED6] = अणु
		.mask = TPS65917_RESERVED,
		.reg_offset = 1,
	पूर्ण,
	/* INT3 IRQs */
	[TPS65917_GPADC_AUTO_0_IRQ] = अणु
		.mask = TPS65917_INT3_STATUS_GPADC_AUTO_0,
		.reg_offset = 2,
	पूर्ण,
	[TPS65917_GPADC_AUTO_1_IRQ] = अणु
		.mask = TPS65917_INT3_STATUS_GPADC_AUTO_1,
		.reg_offset = 2,
	पूर्ण,
	[TPS65917_GPADC_EOC_SW_IRQ] = अणु
		.mask = TPS65917_INT3_STATUS_GPADC_EOC_SW,
		.reg_offset = 2,
	पूर्ण,
	[TPS65917_RESREVED6] = अणु
		.mask = TPS65917_RESERVED6,
		.reg_offset = 2,
	पूर्ण,
	[TPS65917_RESERVED7] = अणु
		.mask = TPS65917_RESERVED,
		.reg_offset = 2,
	पूर्ण,
	[TPS65917_RESERVED8] = अणु
		.mask = TPS65917_RESERVED,
		.reg_offset = 2,
	पूर्ण,
	[TPS65917_RESERVED9] = अणु
		.mask = TPS65917_RESERVED,
		.reg_offset = 2,
	पूर्ण,
	[TPS65917_VBUS_IRQ] = अणु
		.mask = TPS65917_INT3_STATUS_VBUS,
		.reg_offset = 2,
	पूर्ण,
	/* INT4 IRQs */
	[TPS65917_GPIO_0_IRQ] = अणु
		.mask = TPS65917_INT4_STATUS_GPIO_0,
		.reg_offset = 3,
	पूर्ण,
	[TPS65917_GPIO_1_IRQ] = अणु
		.mask = TPS65917_INT4_STATUS_GPIO_1,
		.reg_offset = 3,
	पूर्ण,
	[TPS65917_GPIO_2_IRQ] = अणु
		.mask = TPS65917_INT4_STATUS_GPIO_2,
		.reg_offset = 3,
	पूर्ण,
	[TPS65917_GPIO_3_IRQ] = अणु
		.mask = TPS65917_INT4_STATUS_GPIO_3,
		.reg_offset = 3,
	पूर्ण,
	[TPS65917_GPIO_4_IRQ] = अणु
		.mask = TPS65917_INT4_STATUS_GPIO_4,
		.reg_offset = 3,
	पूर्ण,
	[TPS65917_GPIO_5_IRQ] = अणु
		.mask = TPS65917_INT4_STATUS_GPIO_5,
		.reg_offset = 3,
	पूर्ण,
	[TPS65917_GPIO_6_IRQ] = अणु
		.mask = TPS65917_INT4_STATUS_GPIO_6,
		.reg_offset = 3,
	पूर्ण,
	[TPS65917_RESERVED10] = अणु
		.mask = TPS65917_RESERVED10,
		.reg_offset = 3,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq palmas_irqs[] = अणु
	/* INT1 IRQs */
	[PALMAS_CHARG_DET_N_VBUS_OVV_IRQ] = अणु
		.mask = PALMAS_INT1_STATUS_CHARG_DET_N_VBUS_OVV,
	पूर्ण,
	[PALMAS_PWRON_IRQ] = अणु
		.mask = PALMAS_INT1_STATUS_PWRON,
	पूर्ण,
	[PALMAS_LONG_PRESS_KEY_IRQ] = अणु
		.mask = PALMAS_INT1_STATUS_LONG_PRESS_KEY,
	पूर्ण,
	[PALMAS_RPWRON_IRQ] = अणु
		.mask = PALMAS_INT1_STATUS_RPWRON,
	पूर्ण,
	[PALMAS_PWRDOWN_IRQ] = अणु
		.mask = PALMAS_INT1_STATUS_PWRDOWN,
	पूर्ण,
	[PALMAS_HOTDIE_IRQ] = अणु
		.mask = PALMAS_INT1_STATUS_HOTDIE,
	पूर्ण,
	[PALMAS_VSYS_MON_IRQ] = अणु
		.mask = PALMAS_INT1_STATUS_VSYS_MON,
	पूर्ण,
	[PALMAS_VBAT_MON_IRQ] = अणु
		.mask = PALMAS_INT1_STATUS_VBAT_MON,
	पूर्ण,
	/* INT2 IRQs*/
	[PALMAS_RTC_ALARM_IRQ] = अणु
		.mask = PALMAS_INT2_STATUS_RTC_ALARM,
		.reg_offset = 1,
	पूर्ण,
	[PALMAS_RTC_TIMER_IRQ] = अणु
		.mask = PALMAS_INT2_STATUS_RTC_TIMER,
		.reg_offset = 1,
	पूर्ण,
	[PALMAS_WDT_IRQ] = अणु
		.mask = PALMAS_INT2_STATUS_WDT,
		.reg_offset = 1,
	पूर्ण,
	[PALMAS_BATREMOVAL_IRQ] = अणु
		.mask = PALMAS_INT2_STATUS_BATREMOVAL,
		.reg_offset = 1,
	पूर्ण,
	[PALMAS_RESET_IN_IRQ] = अणु
		.mask = PALMAS_INT2_STATUS_RESET_IN,
		.reg_offset = 1,
	पूर्ण,
	[PALMAS_FBI_BB_IRQ] = अणु
		.mask = PALMAS_INT2_STATUS_FBI_BB,
		.reg_offset = 1,
	पूर्ण,
	[PALMAS_SHORT_IRQ] = अणु
		.mask = PALMAS_INT2_STATUS_SHORT,
		.reg_offset = 1,
	पूर्ण,
	[PALMAS_VAC_ACOK_IRQ] = अणु
		.mask = PALMAS_INT2_STATUS_VAC_ACOK,
		.reg_offset = 1,
	पूर्ण,
	/* INT3 IRQs */
	[PALMAS_GPADC_AUTO_0_IRQ] = अणु
		.mask = PALMAS_INT3_STATUS_GPADC_AUTO_0,
		.reg_offset = 2,
	पूर्ण,
	[PALMAS_GPADC_AUTO_1_IRQ] = अणु
		.mask = PALMAS_INT3_STATUS_GPADC_AUTO_1,
		.reg_offset = 2,
	पूर्ण,
	[PALMAS_GPADC_EOC_SW_IRQ] = अणु
		.mask = PALMAS_INT3_STATUS_GPADC_EOC_SW,
		.reg_offset = 2,
	पूर्ण,
	[PALMAS_GPADC_EOC_RT_IRQ] = अणु
		.mask = PALMAS_INT3_STATUS_GPADC_EOC_RT,
		.reg_offset = 2,
	पूर्ण,
	[PALMAS_ID_OTG_IRQ] = अणु
		.mask = PALMAS_INT3_STATUS_ID_OTG,
		.reg_offset = 2,
	पूर्ण,
	[PALMAS_ID_IRQ] = अणु
		.mask = PALMAS_INT3_STATUS_ID,
		.reg_offset = 2,
	पूर्ण,
	[PALMAS_VBUS_OTG_IRQ] = अणु
		.mask = PALMAS_INT3_STATUS_VBUS_OTG,
		.reg_offset = 2,
	पूर्ण,
	[PALMAS_VBUS_IRQ] = अणु
		.mask = PALMAS_INT3_STATUS_VBUS,
		.reg_offset = 2,
	पूर्ण,
	/* INT4 IRQs */
	[PALMAS_GPIO_0_IRQ] = अणु
		.mask = PALMAS_INT4_STATUS_GPIO_0,
		.reg_offset = 3,
	पूर्ण,
	[PALMAS_GPIO_1_IRQ] = अणु
		.mask = PALMAS_INT4_STATUS_GPIO_1,
		.reg_offset = 3,
	पूर्ण,
	[PALMAS_GPIO_2_IRQ] = अणु
		.mask = PALMAS_INT4_STATUS_GPIO_2,
		.reg_offset = 3,
	पूर्ण,
	[PALMAS_GPIO_3_IRQ] = अणु
		.mask = PALMAS_INT4_STATUS_GPIO_3,
		.reg_offset = 3,
	पूर्ण,
	[PALMAS_GPIO_4_IRQ] = अणु
		.mask = PALMAS_INT4_STATUS_GPIO_4,
		.reg_offset = 3,
	पूर्ण,
	[PALMAS_GPIO_5_IRQ] = अणु
		.mask = PALMAS_INT4_STATUS_GPIO_5,
		.reg_offset = 3,
	पूर्ण,
	[PALMAS_GPIO_6_IRQ] = अणु
		.mask = PALMAS_INT4_STATUS_GPIO_6,
		.reg_offset = 3,
	पूर्ण,
	[PALMAS_GPIO_7_IRQ] = अणु
		.mask = PALMAS_INT4_STATUS_GPIO_7,
		.reg_offset = 3,
	पूर्ण,
पूर्ण;

अटल काष्ठा regmap_irq_chip palmas_irq_chip = अणु
	.name = "palmas",
	.irqs = palmas_irqs,
	.num_irqs = ARRAY_SIZE(palmas_irqs),

	.num_regs = 4,
	.irq_reg_stride = 5,
	.status_base = PALMAS_BASE_TO_REG(PALMAS_INTERRUPT_BASE,
			PALMAS_INT1_STATUS),
	.mask_base = PALMAS_BASE_TO_REG(PALMAS_INTERRUPT_BASE,
			PALMAS_INT1_MASK),
पूर्ण;

अटल काष्ठा regmap_irq_chip tps65917_irq_chip = अणु
	.name = "tps65917",
	.irqs = tps65917_irqs,
	.num_irqs = ARRAY_SIZE(tps65917_irqs),

	.num_regs = 4,
	.irq_reg_stride = 5,
	.status_base = PALMAS_BASE_TO_REG(PALMAS_INTERRUPT_BASE,
			PALMAS_INT1_STATUS),
	.mask_base = PALMAS_BASE_TO_REG(PALMAS_INTERRUPT_BASE,
			PALMAS_INT1_MASK),
पूर्ण;

पूर्णांक palmas_ext_control_req_config(काष्ठा palmas *palmas,
	क्रमागत palmas_बाह्यal_requestor_id id,  पूर्णांक ext_ctrl, bool enable)
अणु
	काष्ठा palmas_pmic_driver_data *pmic_ddata = palmas->pmic_ddata;
	पूर्णांक preq_mask_bit = 0;
	पूर्णांक reg_add = 0;
	पूर्णांक bit_pos, ret;

	अगर (!(ext_ctrl & PALMAS_EXT_REQ))
		वापस 0;

	अगर (id >= PALMAS_EXTERNAL_REQSTR_ID_MAX)
		वापस 0;

	अगर (ext_ctrl & PALMAS_EXT_CONTROL_NSLEEP) अणु
		reg_add = PALMAS_NSLEEP_RES_ASSIGN;
		preq_mask_bit = 0;
	पूर्ण अन्यथा अगर (ext_ctrl & PALMAS_EXT_CONTROL_ENABLE1) अणु
		reg_add = PALMAS_ENABLE1_RES_ASSIGN;
		preq_mask_bit = 1;
	पूर्ण अन्यथा अगर (ext_ctrl & PALMAS_EXT_CONTROL_ENABLE2) अणु
		reg_add = PALMAS_ENABLE2_RES_ASSIGN;
		preq_mask_bit = 2;
	पूर्ण

	bit_pos = pmic_ddata->sleep_req_info[id].bit_pos;
	reg_add += pmic_ddata->sleep_req_info[id].reg_offset;
	अगर (enable)
		ret = palmas_update_bits(palmas, PALMAS_RESOURCE_BASE,
				reg_add, BIT(bit_pos), BIT(bit_pos));
	अन्यथा
		ret = palmas_update_bits(palmas, PALMAS_RESOURCE_BASE,
				reg_add, BIT(bit_pos), 0);
	अगर (ret < 0) अणु
		dev_err(palmas->dev, "Resource reg 0x%02x update failed %d\n",
			reg_add, ret);
		वापस ret;
	पूर्ण

	/* Unmask the PREQ */
	ret = palmas_update_bits(palmas, PALMAS_PMU_CONTROL_BASE,
			PALMAS_POWER_CTRL, BIT(preq_mask_bit), 0);
	अगर (ret < 0) अणु
		dev_err(palmas->dev, "POWER_CTRL register update failed %d\n",
			ret);
		वापस ret;
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(palmas_ext_control_req_config);

अटल पूर्णांक palmas_set_pdata_irq_flag(काष्ठा i2c_client *i2c,
		काष्ठा palmas_platक्रमm_data *pdata)
अणु
	काष्ठा irq_data *irq_data = irq_get_irq_data(i2c->irq);
	अगर (!irq_data) अणु
		dev_err(&i2c->dev, "Invalid IRQ: %d\n", i2c->irq);
		वापस -EINVAL;
	पूर्ण

	pdata->irq_flags = irqd_get_trigger_type(irq_data);
	dev_info(&i2c->dev, "Irq flag is 0x%08x\n", pdata->irq_flags);
	वापस 0;
पूर्ण

अटल व्योम palmas_dt_to_pdata(काष्ठा i2c_client *i2c,
		काष्ठा palmas_platक्रमm_data *pdata)
अणु
	काष्ठा device_node *node = i2c->dev.of_node;
	पूर्णांक ret;
	u32 prop;

	ret = of_property_पढ़ो_u32(node, "ti,mux-pad1", &prop);
	अगर (!ret) अणु
		pdata->mux_from_pdata = 1;
		pdata->pad1 = prop;
	पूर्ण

	ret = of_property_पढ़ो_u32(node, "ti,mux-pad2", &prop);
	अगर (!ret) अणु
		pdata->mux_from_pdata = 1;
		pdata->pad2 = prop;
	पूर्ण

	/* The शेष क्रम this रेजिस्टर is all masked */
	ret = of_property_पढ़ो_u32(node, "ti,power-ctrl", &prop);
	अगर (!ret)
		pdata->घातer_ctrl = prop;
	अन्यथा
		pdata->घातer_ctrl = PALMAS_POWER_CTRL_NSLEEP_MASK |
					PALMAS_POWER_CTRL_ENABLE1_MASK |
					PALMAS_POWER_CTRL_ENABLE2_MASK;
	अगर (i2c->irq)
		palmas_set_pdata_irq_flag(i2c, pdata);

	pdata->pm_off = of_property_पढ़ो_bool(node,
			"ti,system-power-controller");
पूर्ण

अटल काष्ठा palmas *palmas_dev;
अटल व्योम palmas_घातer_off(व्योम)
अणु
	अचिन्हित पूर्णांक addr;
	पूर्णांक ret, slave;
	u8 घातerhold_mask;
	काष्ठा device_node *np = palmas_dev->dev->of_node;

	अगर (of_property_पढ़ो_bool(np, "ti,palmas-override-powerhold")) अणु
		addr = PALMAS_BASE_TO_REG(PALMAS_PU_PD_OD_BASE,
					  PALMAS_PRIMARY_SECONDARY_PAD2);
		slave = PALMAS_BASE_TO_SLAVE(PALMAS_PU_PD_OD_BASE);

		अगर (of_device_is_compatible(np, "ti,tps65917"))
			घातerhold_mask =
				TPS65917_PRIMARY_SECONDARY_PAD2_GPIO_5_MASK;
		अन्यथा
			घातerhold_mask =
				PALMAS_PRIMARY_SECONDARY_PAD2_GPIO_7_MASK;

		ret = regmap_update_bits(palmas_dev->regmap[slave], addr,
					 घातerhold_mask, 0);
		अगर (ret)
			dev_err(palmas_dev->dev,
				"Unable to write PRIMARY_SECONDARY_PAD2 %d\n",
				ret);
	पूर्ण

	slave = PALMAS_BASE_TO_SLAVE(PALMAS_PMU_CONTROL_BASE);
	addr = PALMAS_BASE_TO_REG(PALMAS_PMU_CONTROL_BASE, PALMAS_DEV_CTRL);

	ret = regmap_update_bits(
			palmas_dev->regmap[slave],
			addr,
			PALMAS_DEV_CTRL_DEV_ON,
			0);

	अगर (ret)
		pr_err("%s: Unable to write to DEV_CTRL_DEV_ON: %d\n",
				__func__, ret);
पूर्ण

अटल अचिन्हित पूर्णांक palmas_features = PALMAS_PMIC_FEATURE_SMPS10_BOOST;
अटल अचिन्हित पूर्णांक tps659038_features;

काष्ठा palmas_driver_data अणु
	अचिन्हित पूर्णांक *features;
	काष्ठा regmap_irq_chip *irq_chip;
पूर्ण;

अटल काष्ठा palmas_driver_data palmas_data = अणु
	.features = &palmas_features,
	.irq_chip = &palmas_irq_chip,
पूर्ण;

अटल काष्ठा palmas_driver_data tps659038_data = अणु
	.features = &tps659038_features,
	.irq_chip = &palmas_irq_chip,
पूर्ण;

अटल काष्ठा palmas_driver_data tps65917_data = अणु
	.features = &tps659038_features,
	.irq_chip = &tps65917_irq_chip,
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_palmas_match_tbl[] = अणु
	अणु
		.compatible = "ti,palmas",
		.data = &palmas_data,
	पूर्ण,
	अणु
		.compatible = "ti,tps659038",
		.data = &tps659038_data,
	पूर्ण,
	अणु
		.compatible = "ti,tps65917",
		.data = &tps65917_data,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_palmas_match_tbl);

अटल पूर्णांक palmas_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा palmas *palmas;
	काष्ठा palmas_platक्रमm_data *pdata;
	काष्ठा palmas_driver_data *driver_data;
	काष्ठा device_node *node = i2c->dev.of_node;
	पूर्णांक ret = 0, i;
	अचिन्हित पूर्णांक reg, addr;
	पूर्णांक slave;
	स्थिर काष्ठा of_device_id *match;

	pdata = dev_get_platdata(&i2c->dev);

	अगर (node && !pdata) अणु
		pdata = devm_kzalloc(&i2c->dev, माप(*pdata), GFP_KERNEL);

		अगर (!pdata)
			वापस -ENOMEM;

		palmas_dt_to_pdata(i2c, pdata);
	पूर्ण

	अगर (!pdata)
		वापस -EINVAL;

	palmas = devm_kzalloc(&i2c->dev, माप(काष्ठा palmas), GFP_KERNEL);
	अगर (palmas == शून्य)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, palmas);
	palmas->dev = &i2c->dev;
	palmas->irq = i2c->irq;

	match = of_match_device(of_palmas_match_tbl, &i2c->dev);

	अगर (!match)
		वापस -ENODATA;

	driver_data = (काष्ठा palmas_driver_data *)match->data;
	palmas->features = *driver_data->features;

	क्रम (i = 0; i < PALMAS_NUM_CLIENTS; i++) अणु
		अगर (i == 0)
			palmas->i2c_clients[i] = i2c;
		अन्यथा अणु
			palmas->i2c_clients[i] =
					i2c_new_dummy_device(i2c->adapter,
							i2c->addr + i);
			अगर (IS_ERR(palmas->i2c_clients[i])) अणु
				dev_err(palmas->dev,
					"can't attach client %d\n", i);
				ret = PTR_ERR(palmas->i2c_clients[i]);
				जाओ err_i2c;
			पूर्ण
			palmas->i2c_clients[i]->dev.of_node = of_node_get(node);
		पूर्ण
		palmas->regmap[i] = devm_regmap_init_i2c(palmas->i2c_clients[i],
				&palmas_regmap_config[i]);
		अगर (IS_ERR(palmas->regmap[i])) अणु
			ret = PTR_ERR(palmas->regmap[i]);
			dev_err(palmas->dev,
				"Failed to allocate regmap %d, err: %d\n",
				i, ret);
			जाओ err_i2c;
		पूर्ण
	पूर्ण

	अगर (!palmas->irq) अणु
		dev_warn(palmas->dev, "IRQ missing: skipping irq request\n");
		जाओ no_irq;
	पूर्ण

	/* Change पूर्णांकerrupt line output polarity */
	अगर (pdata->irq_flags & IRQ_TYPE_LEVEL_HIGH)
		reg = PALMAS_POLARITY_CTRL_INT_POLARITY;
	अन्यथा
		reg = 0;
	ret = palmas_update_bits(palmas, PALMAS_PU_PD_OD_BASE,
			PALMAS_POLARITY_CTRL, PALMAS_POLARITY_CTRL_INT_POLARITY,
			reg);
	अगर (ret < 0) अणु
		dev_err(palmas->dev, "POLARITY_CTRL update failed: %d\n", ret);
		जाओ err_i2c;
	पूर्ण

	/* Change IRQ पूर्णांकo clear on पढ़ो mode क्रम efficiency */
	slave = PALMAS_BASE_TO_SLAVE(PALMAS_INTERRUPT_BASE);
	addr = PALMAS_BASE_TO_REG(PALMAS_INTERRUPT_BASE, PALMAS_INT_CTRL);
	reg = PALMAS_INT_CTRL_INT_CLEAR;

	regmap_ग_लिखो(palmas->regmap[slave], addr, reg);

	ret = regmap_add_irq_chip(palmas->regmap[slave], palmas->irq,
				  IRQF_ONESHOT | pdata->irq_flags, 0,
				  driver_data->irq_chip, &palmas->irq_data);
	अगर (ret < 0)
		जाओ err_i2c;

no_irq:
	slave = PALMAS_BASE_TO_SLAVE(PALMAS_PU_PD_OD_BASE);
	addr = PALMAS_BASE_TO_REG(PALMAS_PU_PD_OD_BASE,
			PALMAS_PRIMARY_SECONDARY_PAD1);

	अगर (pdata->mux_from_pdata) अणु
		reg = pdata->pad1;
		ret = regmap_ग_लिखो(palmas->regmap[slave], addr, reg);
		अगर (ret)
			जाओ err_irq;
	पूर्ण अन्यथा अणु
		ret = regmap_पढ़ो(palmas->regmap[slave], addr, &reg);
		अगर (ret)
			जाओ err_irq;
	पूर्ण

	अगर (!(reg & PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_0))
		palmas->gpio_muxed |= PALMAS_GPIO_0_MUXED;
	अगर (!(reg & PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_1_MASK))
		palmas->gpio_muxed |= PALMAS_GPIO_1_MUXED;
	अन्यथा अगर ((reg & PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_1_MASK) ==
			(2 << PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_1_SHIFT))
		palmas->led_muxed |= PALMAS_LED1_MUXED;
	अन्यथा अगर ((reg & PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_1_MASK) ==
			(3 << PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_1_SHIFT))
		palmas->pwm_muxed |= PALMAS_PWM1_MUXED;
	अगर (!(reg & PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_2_MASK))
		palmas->gpio_muxed |= PALMAS_GPIO_2_MUXED;
	अन्यथा अगर ((reg & PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_2_MASK) ==
			(2 << PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_2_SHIFT))
		palmas->led_muxed |= PALMAS_LED2_MUXED;
	अन्यथा अगर ((reg & PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_2_MASK) ==
			(3 << PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_2_SHIFT))
		palmas->pwm_muxed |= PALMAS_PWM2_MUXED;
	अगर (!(reg & PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_3))
		palmas->gpio_muxed |= PALMAS_GPIO_3_MUXED;

	addr = PALMAS_BASE_TO_REG(PALMAS_PU_PD_OD_BASE,
			PALMAS_PRIMARY_SECONDARY_PAD2);

	अगर (pdata->mux_from_pdata) अणु
		reg = pdata->pad2;
		ret = regmap_ग_लिखो(palmas->regmap[slave], addr, reg);
		अगर (ret)
			जाओ err_irq;
	पूर्ण अन्यथा अणु
		ret = regmap_पढ़ो(palmas->regmap[slave], addr, &reg);
		अगर (ret)
			जाओ err_irq;
	पूर्ण

	अगर (!(reg & PALMAS_PRIMARY_SECONDARY_PAD2_GPIO_4))
		palmas->gpio_muxed |= PALMAS_GPIO_4_MUXED;
	अगर (!(reg & PALMAS_PRIMARY_SECONDARY_PAD2_GPIO_5_MASK))
		palmas->gpio_muxed |= PALMAS_GPIO_5_MUXED;
	अगर (!(reg & PALMAS_PRIMARY_SECONDARY_PAD2_GPIO_6))
		palmas->gpio_muxed |= PALMAS_GPIO_6_MUXED;
	अगर (!(reg & PALMAS_PRIMARY_SECONDARY_PAD2_GPIO_7_MASK))
		palmas->gpio_muxed |= PALMAS_GPIO_7_MUXED;

	dev_info(palmas->dev, "Muxing GPIO %x, PWM %x, LED %x\n",
			palmas->gpio_muxed, palmas->pwm_muxed,
			palmas->led_muxed);

	reg = pdata->घातer_ctrl;

	slave = PALMAS_BASE_TO_SLAVE(PALMAS_PMU_CONTROL_BASE);
	addr = PALMAS_BASE_TO_REG(PALMAS_PMU_CONTROL_BASE, PALMAS_POWER_CTRL);

	ret = regmap_ग_लिखो(palmas->regmap[slave], addr, reg);
	अगर (ret)
		जाओ err_irq;

	/*
	 * If we are probing with DT करो this the DT way and वापस here
	 * otherwise जारी and add devices using mfd helpers.
	 */
	अगर (node) अणु
		ret = devm_of_platक्रमm_populate(&i2c->dev);
		अगर (ret < 0) अणु
			जाओ err_irq;
		पूर्ण अन्यथा अगर (pdata->pm_off && !pm_घातer_off) अणु
			palmas_dev = palmas;
			pm_घातer_off = palmas_घातer_off;
		पूर्ण
	पूर्ण

	वापस ret;

err_irq:
	regmap_del_irq_chip(palmas->irq, palmas->irq_data);
err_i2c:
	क्रम (i = 1; i < PALMAS_NUM_CLIENTS; i++) अणु
		अगर (palmas->i2c_clients[i])
			i2c_unरेजिस्टर_device(palmas->i2c_clients[i]);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक palmas_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	काष्ठा palmas *palmas = i2c_get_clientdata(i2c);
	पूर्णांक i;

	regmap_del_irq_chip(palmas->irq, palmas->irq_data);

	क्रम (i = 1; i < PALMAS_NUM_CLIENTS; i++) अणु
		अगर (palmas->i2c_clients[i])
			i2c_unरेजिस्टर_device(palmas->i2c_clients[i]);
	पूर्ण

	अगर (palmas == palmas_dev) अणु
		pm_घातer_off = शून्य;
		palmas_dev = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id palmas_i2c_id[] = अणु
	अणु "palmas", पूर्ण,
	अणु "twl6035", पूर्ण,
	अणु "twl6037", पूर्ण,
	अणु "tps65913", पूर्ण,
	अणु /* end */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, palmas_i2c_id);

अटल काष्ठा i2c_driver palmas_i2c_driver = अणु
	.driver = अणु
		   .name = "palmas",
		   .of_match_table = of_palmas_match_tbl,
	पूर्ण,
	.probe = palmas_i2c_probe,
	.हटाओ = palmas_i2c_हटाओ,
	.id_table = palmas_i2c_id,
पूर्ण;

अटल पूर्णांक __init palmas_i2c_init(व्योम)
अणु
	वापस i2c_add_driver(&palmas_i2c_driver);
पूर्ण
/* init early so consumer devices can complete प्रणाली boot */
subsys_initcall(palmas_i2c_init);

अटल व्योम __निकास palmas_i2c_निकास(व्योम)
अणु
	i2c_del_driver(&palmas_i2c_driver);
पूर्ण
module_निकास(palmas_i2c_निकास);

MODULE_AUTHOR("Graeme Gregory <gg@slimlogic.co.uk>");
MODULE_DESCRIPTION("Palmas chip family multi-function driver");
MODULE_LICENSE("GPL");
