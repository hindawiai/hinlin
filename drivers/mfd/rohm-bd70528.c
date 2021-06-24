<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
//
// Copyright (C) 2019 ROHM Semiconductors
//
// ROHM BD70528 PMIC driver

#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/irq.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/rohm-bd70528.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/types.h>

#घोषणा BD70528_NUM_OF_GPIOS 4

अटल स्थिर काष्ठा resource rtc_irqs[] = अणु
	DEFINE_RES_IRQ_NAMED(BD70528_INT_RTC_ALARM, "bd70528-rtc-alm"),
	DEFINE_RES_IRQ_NAMED(BD70528_INT_ELPS_TIM, "bd70528-elapsed-timer"),
पूर्ण;

अटल स्थिर काष्ठा resource अक्षरger_irqs[] = अणु
	DEFINE_RES_IRQ_NAMED(BD70528_INT_BAT_OV_RES, "bd70528-bat-ov-res"),
	DEFINE_RES_IRQ_NAMED(BD70528_INT_BAT_OV_DET, "bd70528-bat-ov-det"),
	DEFINE_RES_IRQ_NAMED(BD70528_INT_DBAT_DET, "bd70528-bat-dead"),
	DEFINE_RES_IRQ_NAMED(BD70528_INT_BATTSD_COLD_RES, "bd70528-bat-warmed"),
	DEFINE_RES_IRQ_NAMED(BD70528_INT_BATTSD_COLD_DET, "bd70528-bat-cold"),
	DEFINE_RES_IRQ_NAMED(BD70528_INT_BATTSD_HOT_RES, "bd70528-bat-cooled"),
	DEFINE_RES_IRQ_NAMED(BD70528_INT_BATTSD_HOT_DET, "bd70528-bat-hot"),
	DEFINE_RES_IRQ_NAMED(BD70528_INT_CHG_TSD, "bd70528-chg-tshd"),
	DEFINE_RES_IRQ_NAMED(BD70528_INT_BAT_RMV, "bd70528-bat-removed"),
	DEFINE_RES_IRQ_NAMED(BD70528_INT_BAT_DET, "bd70528-bat-detected"),
	DEFINE_RES_IRQ_NAMED(BD70528_INT_DCIN2_OV_RES, "bd70528-dcin2-ov-res"),
	DEFINE_RES_IRQ_NAMED(BD70528_INT_DCIN2_OV_DET, "bd70528-dcin2-ov-det"),
	DEFINE_RES_IRQ_NAMED(BD70528_INT_DCIN2_RMV, "bd70528-dcin2-removed"),
	DEFINE_RES_IRQ_NAMED(BD70528_INT_DCIN2_DET, "bd70528-dcin2-detected"),
	DEFINE_RES_IRQ_NAMED(BD70528_INT_DCIN1_RMV, "bd70528-dcin1-removed"),
	DEFINE_RES_IRQ_NAMED(BD70528_INT_DCIN1_DET, "bd70528-dcin1-detected"),
पूर्ण;

अटल काष्ठा mfd_cell bd70528_mfd_cells[] = अणु
	अणु .name = "bd70528-pmic", पूर्ण,
	अणु .name = "bd70528-gpio", पूर्ण,
	/*
	 * We use BD71837 driver to drive the घड़ी block. Only dअगरferences to
	 * BD70528 घड़ी gate are the रेजिस्टर address and mask.
	 */
	अणु .name = "bd70528-clk", पूर्ण,
	अणु .name = "bd70528-wdt", पूर्ण,
	अणु
		.name = "bd70528-power",
		.resources = अक्षरger_irqs,
		.num_resources = ARRAY_SIZE(अक्षरger_irqs),
	पूर्ण, अणु
		.name = "bd70528-rtc",
		.resources = rtc_irqs,
		.num_resources = ARRAY_SIZE(rtc_irqs),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_range अस्थिर_ranges[] = अणु
	अणु
		.range_min = BD70528_REG_INT_MAIN,
		.range_max = BD70528_REG_INT_OP_FAIL,
	पूर्ण, अणु
		.range_min = BD70528_REG_RTC_COUNT_H,
		.range_max = BD70528_REG_RTC_ALM_REPEAT,
	पूर्ण, अणु
		/*
		 * WDT control reg is special. Magic values must be written to
		 * it in order to change the control. Should not be cached.
		 */
		.range_min = BD70528_REG_WDT_CTRL,
		.range_max = BD70528_REG_WDT_CTRL,
	पूर्ण, अणु
		/*
		 * BD70528 also contains a few other रेजिस्टरs which require
		 * magic sequences to be written in order to update the value.
		 * At least SHIPMODE, HWRESET, WARMRESET,and STANDBY
		 */
		.range_min = BD70528_REG_SHIPMODE,
		.range_max = BD70528_REG_STANDBY,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table अस्थिर_regs = अणु
	.yes_ranges = &अस्थिर_ranges[0],
	.n_yes_ranges = ARRAY_SIZE(अस्थिर_ranges),
पूर्ण;

अटल काष्ठा regmap_config bd70528_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.अस्थिर_table = &अस्थिर_regs,
	.max_रेजिस्टर = BD70528_MAX_REGISTER,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

/*
 * Mapping of मुख्य IRQ रेजिस्टर bits to sub-IRQ रेजिस्टर offsets so that we can
 * access corect sub-IRQ रेजिस्टरs based on bits that are set in मुख्य IRQ
 * रेजिस्टर.
 */

अटल अचिन्हित पूर्णांक bit0_offsets[] = अणु0पूर्ण;	/* Shutकरोwn */
अटल अचिन्हित पूर्णांक bit1_offsets[] = अणु1पूर्ण;	/* Power failure */
अटल अचिन्हित पूर्णांक bit2_offsets[] = अणु2पूर्ण;	/* VR FAULT */
अटल अचिन्हित पूर्णांक bit3_offsets[] = अणु3पूर्ण;	/* PMU पूर्णांकerrupts */
अटल अचिन्हित पूर्णांक bit4_offsets[] = अणु4, 5पूर्ण;	/* Charger 1 and Charger 2 */
अटल अचिन्हित पूर्णांक bit5_offsets[] = अणु6पूर्ण;	/* RTC */
अटल अचिन्हित पूर्णांक bit6_offsets[] = अणु7पूर्ण;	/* GPIO */
अटल अचिन्हित पूर्णांक bit7_offsets[] = अणु8पूर्ण;	/* Invalid operation */

अटल काष्ठा regmap_irq_sub_irq_map bd70528_sub_irq_offsets[] = अणु
	REGMAP_IRQ_MAIN_REG_OFFSET(bit0_offsets),
	REGMAP_IRQ_MAIN_REG_OFFSET(bit1_offsets),
	REGMAP_IRQ_MAIN_REG_OFFSET(bit2_offsets),
	REGMAP_IRQ_MAIN_REG_OFFSET(bit3_offsets),
	REGMAP_IRQ_MAIN_REG_OFFSET(bit4_offsets),
	REGMAP_IRQ_MAIN_REG_OFFSET(bit5_offsets),
	REGMAP_IRQ_MAIN_REG_OFFSET(bit6_offsets),
	REGMAP_IRQ_MAIN_REG_OFFSET(bit7_offsets),
पूर्ण;

अटल काष्ठा regmap_irq bd70528_irqs[] = अणु
	REGMAP_IRQ_REG(BD70528_INT_LONGPUSH, 0, BD70528_INT_LONGPUSH_MASK),
	REGMAP_IRQ_REG(BD70528_INT_WDT, 0, BD70528_INT_WDT_MASK),
	REGMAP_IRQ_REG(BD70528_INT_HWRESET, 0, BD70528_INT_HWRESET_MASK),
	REGMAP_IRQ_REG(BD70528_INT_RSTB_FAULT, 0, BD70528_INT_RSTB_FAULT_MASK),
	REGMAP_IRQ_REG(BD70528_INT_VBAT_UVLO, 0, BD70528_INT_VBAT_UVLO_MASK),
	REGMAP_IRQ_REG(BD70528_INT_TSD, 0, BD70528_INT_TSD_MASK),
	REGMAP_IRQ_REG(BD70528_INT_RSTIN, 0, BD70528_INT_RSTIN_MASK),
	REGMAP_IRQ_REG(BD70528_INT_BUCK1_FAULT, 1,
		       BD70528_INT_BUCK1_FAULT_MASK),
	REGMAP_IRQ_REG(BD70528_INT_BUCK2_FAULT, 1,
		       BD70528_INT_BUCK2_FAULT_MASK),
	REGMAP_IRQ_REG(BD70528_INT_BUCK3_FAULT, 1,
		       BD70528_INT_BUCK3_FAULT_MASK),
	REGMAP_IRQ_REG(BD70528_INT_LDO1_FAULT, 1, BD70528_INT_LDO1_FAULT_MASK),
	REGMAP_IRQ_REG(BD70528_INT_LDO2_FAULT, 1, BD70528_INT_LDO2_FAULT_MASK),
	REGMAP_IRQ_REG(BD70528_INT_LDO3_FAULT, 1, BD70528_INT_LDO3_FAULT_MASK),
	REGMAP_IRQ_REG(BD70528_INT_LED1_FAULT, 1, BD70528_INT_LED1_FAULT_MASK),
	REGMAP_IRQ_REG(BD70528_INT_LED2_FAULT, 1, BD70528_INT_LED2_FAULT_MASK),
	REGMAP_IRQ_REG(BD70528_INT_BUCK1_OCP, 2, BD70528_INT_BUCK1_OCP_MASK),
	REGMAP_IRQ_REG(BD70528_INT_BUCK2_OCP, 2, BD70528_INT_BUCK2_OCP_MASK),
	REGMAP_IRQ_REG(BD70528_INT_BUCK3_OCP, 2, BD70528_INT_BUCK3_OCP_MASK),
	REGMAP_IRQ_REG(BD70528_INT_LED1_OCP, 2, BD70528_INT_LED1_OCP_MASK),
	REGMAP_IRQ_REG(BD70528_INT_LED2_OCP, 2, BD70528_INT_LED2_OCP_MASK),
	REGMAP_IRQ_REG(BD70528_INT_BUCK1_FULLON, 2,
		       BD70528_INT_BUCK1_FULLON_MASK),
	REGMAP_IRQ_REG(BD70528_INT_BUCK2_FULLON, 2,
		       BD70528_INT_BUCK2_FULLON_MASK),
	REGMAP_IRQ_REG(BD70528_INT_SHORTPUSH, 3, BD70528_INT_SHORTPUSH_MASK),
	REGMAP_IRQ_REG(BD70528_INT_AUTO_WAKEUP, 3,
		       BD70528_INT_AUTO_WAKEUP_MASK),
	REGMAP_IRQ_REG(BD70528_INT_STATE_CHANGE, 3,
		       BD70528_INT_STATE_CHANGE_MASK),
	REGMAP_IRQ_REG(BD70528_INT_BAT_OV_RES, 4, BD70528_INT_BAT_OV_RES_MASK),
	REGMAP_IRQ_REG(BD70528_INT_BAT_OV_DET, 4, BD70528_INT_BAT_OV_DET_MASK),
	REGMAP_IRQ_REG(BD70528_INT_DBAT_DET, 4, BD70528_INT_DBAT_DET_MASK),
	REGMAP_IRQ_REG(BD70528_INT_BATTSD_COLD_RES, 4,
		       BD70528_INT_BATTSD_COLD_RES_MASK),
	REGMAP_IRQ_REG(BD70528_INT_BATTSD_COLD_DET, 4,
		       BD70528_INT_BATTSD_COLD_DET_MASK),
	REGMAP_IRQ_REG(BD70528_INT_BATTSD_HOT_RES, 4,
		       BD70528_INT_BATTSD_HOT_RES_MASK),
	REGMAP_IRQ_REG(BD70528_INT_BATTSD_HOT_DET, 4,
		       BD70528_INT_BATTSD_HOT_DET_MASK),
	REGMAP_IRQ_REG(BD70528_INT_CHG_TSD, 4, BD70528_INT_CHG_TSD_MASK),
	REGMAP_IRQ_REG(BD70528_INT_BAT_RMV, 5, BD70528_INT_BAT_RMV_MASK),
	REGMAP_IRQ_REG(BD70528_INT_BAT_DET, 5, BD70528_INT_BAT_DET_MASK),
	REGMAP_IRQ_REG(BD70528_INT_DCIN2_OV_RES, 5,
		       BD70528_INT_DCIN2_OV_RES_MASK),
	REGMAP_IRQ_REG(BD70528_INT_DCIN2_OV_DET, 5,
		       BD70528_INT_DCIN2_OV_DET_MASK),
	REGMAP_IRQ_REG(BD70528_INT_DCIN2_RMV, 5, BD70528_INT_DCIN2_RMV_MASK),
	REGMAP_IRQ_REG(BD70528_INT_DCIN2_DET, 5, BD70528_INT_DCIN2_DET_MASK),
	REGMAP_IRQ_REG(BD70528_INT_DCIN1_RMV, 5, BD70528_INT_DCIN1_RMV_MASK),
	REGMAP_IRQ_REG(BD70528_INT_DCIN1_DET, 5, BD70528_INT_DCIN1_DET_MASK),
	REGMAP_IRQ_REG(BD70528_INT_RTC_ALARM, 6, BD70528_INT_RTC_ALARM_MASK),
	REGMAP_IRQ_REG(BD70528_INT_ELPS_TIM, 6, BD70528_INT_ELPS_TIM_MASK),
	REGMAP_IRQ_REG(BD70528_INT_GPIO0, 7, BD70528_INT_GPIO0_MASK),
	REGMAP_IRQ_REG(BD70528_INT_GPIO1, 7, BD70528_INT_GPIO1_MASK),
	REGMAP_IRQ_REG(BD70528_INT_GPIO2, 7, BD70528_INT_GPIO2_MASK),
	REGMAP_IRQ_REG(BD70528_INT_GPIO3, 7, BD70528_INT_GPIO3_MASK),
	REGMAP_IRQ_REG(BD70528_INT_BUCK1_DVS_OPFAIL, 8,
		       BD70528_INT_BUCK1_DVS_OPFAIL_MASK),
	REGMAP_IRQ_REG(BD70528_INT_BUCK2_DVS_OPFAIL, 8,
		       BD70528_INT_BUCK2_DVS_OPFAIL_MASK),
	REGMAP_IRQ_REG(BD70528_INT_BUCK3_DVS_OPFAIL, 8,
		       BD70528_INT_BUCK3_DVS_OPFAIL_MASK),
	REGMAP_IRQ_REG(BD70528_INT_LED1_VOLT_OPFAIL, 8,
		       BD70528_INT_LED1_VOLT_OPFAIL_MASK),
	REGMAP_IRQ_REG(BD70528_INT_LED2_VOLT_OPFAIL, 8,
		       BD70528_INT_LED2_VOLT_OPFAIL_MASK),
पूर्ण;

अटल काष्ठा regmap_irq_chip bd70528_irq_chip = अणु
	.name = "bd70528_irq",
	.मुख्य_status = BD70528_REG_INT_MAIN,
	.irqs = &bd70528_irqs[0],
	.num_irqs = ARRAY_SIZE(bd70528_irqs),
	.status_base = BD70528_REG_INT_SHDN,
	.mask_base = BD70528_REG_INT_SHDN_MASK,
	.ack_base = BD70528_REG_INT_SHDN,
	.type_base = BD70528_REG_GPIO1_IN,
	.init_ack_masked = true,
	.num_regs = 9,
	.num_मुख्य_regs = 1,
	.num_type_reg = 4,
	.sub_reg_offsets = &bd70528_sub_irq_offsets[0],
	.num_मुख्य_status_bits = 8,
	.irq_reg_stride = 1,
पूर्ण;

अटल पूर्णांक bd70528_i2c_probe(काष्ठा i2c_client *i2c,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा bd70528_data *bd70528;
	काष्ठा regmap_irq_chip_data *irq_data;
	पूर्णांक ret, i;

	अगर (!i2c->irq) अणु
		dev_err(&i2c->dev, "No IRQ configured\n");
		वापस -EINVAL;
	पूर्ण

	bd70528 = devm_kzalloc(&i2c->dev, माप(*bd70528), GFP_KERNEL);
	अगर (!bd70528)
		वापस -ENOMEM;

	mutex_init(&bd70528->rtc_समयr_lock);

	dev_set_drvdata(&i2c->dev, &bd70528->chip);

	bd70528->chip.regmap = devm_regmap_init_i2c(i2c, &bd70528_regmap);
	अगर (IS_ERR(bd70528->chip.regmap)) अणु
		dev_err(&i2c->dev, "Failed to initialize Regmap\n");
		वापस PTR_ERR(bd70528->chip.regmap);
	पूर्ण

	/*
	 * Disallow type setting क्रम all IRQs by शेष as most of them करो not
	 * support setting type.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(bd70528_irqs); i++)
		bd70528_irqs[i].type.types_supported = 0;

	/* Set IRQ typesetting inक्रमmation क्रम GPIO pins 0 - 3 */
	क्रम (i = 0; i < BD70528_NUM_OF_GPIOS; i++) अणु
		काष्ठा regmap_irq_type *type;

		type = &bd70528_irqs[BD70528_INT_GPIO0 + i].type;
		type->type_reg_offset = 2 * i;
		type->type_rising_val = 0x20;
		type->type_falling_val = 0x10;
		type->type_level_high_val = 0x40;
		type->type_level_low_val = 0x50;
		type->types_supported = (IRQ_TYPE_EDGE_BOTH |
				IRQ_TYPE_LEVEL_HIGH | IRQ_TYPE_LEVEL_LOW);
	पूर्ण

	ret = devm_regmap_add_irq_chip(&i2c->dev, bd70528->chip.regmap,
				       i2c->irq, IRQF_ONESHOT, 0,
				       &bd70528_irq_chip, &irq_data);
	अगर (ret) अणु
		dev_err(&i2c->dev, "Failed to add IRQ chip\n");
		वापस ret;
	पूर्ण
	dev_dbg(&i2c->dev, "Registered %d IRQs for chip\n",
		bd70528_irq_chip.num_irqs);

	/*
	 * BD70528 IRQ controller is not touching the मुख्य mask रेजिस्टर.
	 * So enable the GPIO block पूर्णांकerrupts at मुख्य level. We can just leave
	 * them enabled as the IRQ controller should disable IRQs from
	 * sub-रेजिस्टरs when IRQ is disabled or मुक्तd.
	 */
	ret = regmap_update_bits(bd70528->chip.regmap,
				 BD70528_REG_INT_MAIN_MASK,
				 BD70528_INT_GPIO_MASK, 0);

	ret = devm_mfd_add_devices(&i2c->dev, PLATFORM_DEVID_AUTO,
				   bd70528_mfd_cells,
				   ARRAY_SIZE(bd70528_mfd_cells), शून्य, 0,
				   regmap_irq_get_करोमुख्य(irq_data));
	अगर (ret)
		dev_err(&i2c->dev, "Failed to create subdevices\n");

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id bd70528_of_match[] = अणु
	अणु .compatible = "rohm,bd70528", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bd70528_of_match);

अटल काष्ठा i2c_driver bd70528_drv = अणु
	.driver = अणु
		.name = "rohm-bd70528",
		.of_match_table = bd70528_of_match,
	पूर्ण,
	.probe = &bd70528_i2c_probe,
पूर्ण;

module_i2c_driver(bd70528_drv);

MODULE_AUTHOR("Matti Vaittinen <matti.vaittinen@fi.rohmeurope.com>");
MODULE_DESCRIPTION("ROHM BD70528 Power Management IC driver");
MODULE_LICENSE("GPL");
