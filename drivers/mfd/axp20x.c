<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MFD core driver क्रम the X-Powers' Power Management ICs
 *
 * AXP20x typically comprises an adaptive USB-Compatible PWM अक्षरger, BUCK DC-DC
 * converters, LDOs, multiple 12-bit ADCs of voltage, current and temperature
 * as well as configurable GPIOs.
 *
 * This file contains the पूर्णांकerface independent core functions.
 *
 * Copyright (C) 2014 Carlo Caione
 *
 * Author: Carlo Caione <carlo@caione.org>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/axp20x.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>

#घोषणा AXP20X_OFF	BIT(7)

#घोषणा AXP806_REG_ADDR_EXT_ADDR_MASTER_MODE	0
#घोषणा AXP806_REG_ADDR_EXT_ADDR_SLAVE_MODE	BIT(4)

अटल स्थिर अक्षर * स्थिर axp20x_model_names[] = अणु
	"AXP152",
	"AXP202",
	"AXP209",
	"AXP221",
	"AXP223",
	"AXP288",
	"AXP803",
	"AXP806",
	"AXP809",
	"AXP813",
पूर्ण;

अटल स्थिर काष्ठा regmap_range axp152_ग_लिखोable_ranges[] = अणु
	regmap_reg_range(AXP152_LDO3456_DC1234_CTRL, AXP152_IRQ3_STATE),
	regmap_reg_range(AXP152_DCDC_MODE, AXP152_PWM1_DUTY_CYCLE),
पूर्ण;

अटल स्थिर काष्ठा regmap_range axp152_अस्थिर_ranges[] = अणु
	regmap_reg_range(AXP152_PWR_OP_MODE, AXP152_PWR_OP_MODE),
	regmap_reg_range(AXP152_IRQ1_EN, AXP152_IRQ3_STATE),
	regmap_reg_range(AXP152_GPIO_INPUT, AXP152_GPIO_INPUT),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table axp152_ग_लिखोable_table = अणु
	.yes_ranges	= axp152_ग_लिखोable_ranges,
	.n_yes_ranges	= ARRAY_SIZE(axp152_ग_लिखोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table axp152_अस्थिर_table = अणु
	.yes_ranges	= axp152_अस्थिर_ranges,
	.n_yes_ranges	= ARRAY_SIZE(axp152_अस्थिर_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range axp20x_ग_लिखोable_ranges[] = अणु
	regmap_reg_range(AXP20X_DATACACHE(0), AXP20X_IRQ5_STATE),
	regmap_reg_range(AXP20X_CHRG_CTRL1, AXP20X_CHRG_CTRL2),
	regmap_reg_range(AXP20X_DCDC_MODE, AXP20X_FG_RES),
	regmap_reg_range(AXP20X_RDC_H, AXP20X_OCV(AXP20X_OCV_MAX)),
पूर्ण;

अटल स्थिर काष्ठा regmap_range axp20x_अस्थिर_ranges[] = अणु
	regmap_reg_range(AXP20X_PWR_INPUT_STATUS, AXP20X_USB_OTG_STATUS),
	regmap_reg_range(AXP20X_CHRG_CTRL1, AXP20X_CHRG_CTRL2),
	regmap_reg_range(AXP20X_IRQ1_EN, AXP20X_IRQ5_STATE),
	regmap_reg_range(AXP20X_ACIN_V_ADC_H, AXP20X_IPSOUT_V_HIGH_L),
	regmap_reg_range(AXP20X_GPIO20_SS, AXP20X_GPIO3_CTRL),
	regmap_reg_range(AXP20X_FG_RES, AXP20X_RDC_L),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table axp20x_ग_लिखोable_table = अणु
	.yes_ranges	= axp20x_ग_लिखोable_ranges,
	.n_yes_ranges	= ARRAY_SIZE(axp20x_ग_लिखोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table axp20x_अस्थिर_table = अणु
	.yes_ranges	= axp20x_अस्थिर_ranges,
	.n_yes_ranges	= ARRAY_SIZE(axp20x_अस्थिर_ranges),
पूर्ण;

/* AXP22x ranges are shared with the AXP809, as they cover the same range */
अटल स्थिर काष्ठा regmap_range axp22x_ग_लिखोable_ranges[] = अणु
	regmap_reg_range(AXP20X_DATACACHE(0), AXP20X_IRQ5_STATE),
	regmap_reg_range(AXP20X_CHRG_CTRL1, AXP22X_CHRG_CTRL3),
	regmap_reg_range(AXP20X_DCDC_MODE, AXP22X_BATLOW_THRES1),
पूर्ण;

अटल स्थिर काष्ठा regmap_range axp22x_अस्थिर_ranges[] = अणु
	regmap_reg_range(AXP20X_PWR_INPUT_STATUS, AXP20X_PWR_OP_MODE),
	regmap_reg_range(AXP20X_IRQ1_EN, AXP20X_IRQ5_STATE),
	regmap_reg_range(AXP22X_GPIO_STATE, AXP22X_GPIO_STATE),
	regmap_reg_range(AXP22X_PMIC_TEMP_H, AXP20X_IPSOUT_V_HIGH_L),
	regmap_reg_range(AXP20X_FG_RES, AXP20X_FG_RES),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table axp22x_ग_लिखोable_table = अणु
	.yes_ranges	= axp22x_ग_लिखोable_ranges,
	.n_yes_ranges	= ARRAY_SIZE(axp22x_ग_लिखोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table axp22x_अस्थिर_table = अणु
	.yes_ranges	= axp22x_अस्थिर_ranges,
	.n_yes_ranges	= ARRAY_SIZE(axp22x_अस्थिर_ranges),
पूर्ण;

/* AXP288 ranges are shared with the AXP803, as they cover the same range */
अटल स्थिर काष्ठा regmap_range axp288_ग_लिखोable_ranges[] = अणु
	regmap_reg_range(AXP20X_DATACACHE(0), AXP20X_IRQ6_STATE),
	regmap_reg_range(AXP20X_DCDC_MODE, AXP288_FG_TUNE5),
पूर्ण;

अटल स्थिर काष्ठा regmap_range axp288_अस्थिर_ranges[] = अणु
	regmap_reg_range(AXP20X_PWR_INPUT_STATUS, AXP288_POWER_REASON),
	regmap_reg_range(AXP288_BC_GLOBAL, AXP288_BC_GLOBAL),
	regmap_reg_range(AXP288_BC_DET_STAT, AXP20X_VBUS_IPSOUT_MGMT),
	regmap_reg_range(AXP20X_CHRG_BAK_CTRL, AXP20X_CHRG_BAK_CTRL),
	regmap_reg_range(AXP20X_IRQ1_EN, AXP20X_IPSOUT_V_HIGH_L),
	regmap_reg_range(AXP20X_TIMER_CTRL, AXP20X_TIMER_CTRL),
	regmap_reg_range(AXP22X_GPIO_STATE, AXP22X_GPIO_STATE),
	regmap_reg_range(AXP288_RT_BATT_V_H, AXP288_RT_BATT_V_L),
	regmap_reg_range(AXP20X_FG_RES, AXP288_FG_CC_CAP_REG),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table axp288_ग_लिखोable_table = अणु
	.yes_ranges	= axp288_ग_लिखोable_ranges,
	.n_yes_ranges	= ARRAY_SIZE(axp288_ग_लिखोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table axp288_अस्थिर_table = अणु
	.yes_ranges	= axp288_अस्थिर_ranges,
	.n_yes_ranges	= ARRAY_SIZE(axp288_अस्थिर_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range axp806_ग_लिखोable_ranges[] = अणु
	regmap_reg_range(AXP20X_DATACACHE(0), AXP20X_DATACACHE(3)),
	regmap_reg_range(AXP806_PWR_OUT_CTRL1, AXP806_CLDO3_V_CTRL),
	regmap_reg_range(AXP20X_IRQ1_EN, AXP20X_IRQ2_EN),
	regmap_reg_range(AXP20X_IRQ1_STATE, AXP20X_IRQ2_STATE),
	regmap_reg_range(AXP806_REG_ADDR_EXT, AXP806_REG_ADDR_EXT),
पूर्ण;

अटल स्थिर काष्ठा regmap_range axp806_अस्थिर_ranges[] = अणु
	regmap_reg_range(AXP20X_IRQ1_STATE, AXP20X_IRQ2_STATE),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table axp806_ग_लिखोable_table = अणु
	.yes_ranges	= axp806_ग_लिखोable_ranges,
	.n_yes_ranges	= ARRAY_SIZE(axp806_ग_लिखोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table axp806_अस्थिर_table = अणु
	.yes_ranges	= axp806_अस्थिर_ranges,
	.n_yes_ranges	= ARRAY_SIZE(axp806_अस्थिर_ranges),
पूर्ण;

अटल स्थिर काष्ठा resource axp152_pek_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(AXP152_IRQ_PEK_RIS_EDGE, "PEK_DBR"),
	DEFINE_RES_IRQ_NAMED(AXP152_IRQ_PEK_FAL_EDGE, "PEK_DBF"),
पूर्ण;

अटल स्थिर काष्ठा resource axp20x_ac_घातer_supply_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(AXP20X_IRQ_ACIN_PLUGIN, "ACIN_PLUGIN"),
	DEFINE_RES_IRQ_NAMED(AXP20X_IRQ_ACIN_REMOVAL, "ACIN_REMOVAL"),
	DEFINE_RES_IRQ_NAMED(AXP20X_IRQ_ACIN_OVER_V, "ACIN_OVER_V"),
पूर्ण;

अटल स्थिर काष्ठा resource axp20x_pek_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(AXP20X_IRQ_PEK_RIS_EDGE, "PEK_DBR"),
	DEFINE_RES_IRQ_NAMED(AXP20X_IRQ_PEK_FAL_EDGE, "PEK_DBF"),
पूर्ण;

अटल स्थिर काष्ठा resource axp20x_usb_घातer_supply_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(AXP20X_IRQ_VBUS_PLUGIN, "VBUS_PLUGIN"),
	DEFINE_RES_IRQ_NAMED(AXP20X_IRQ_VBUS_REMOVAL, "VBUS_REMOVAL"),
	DEFINE_RES_IRQ_NAMED(AXP20X_IRQ_VBUS_VALID, "VBUS_VALID"),
	DEFINE_RES_IRQ_NAMED(AXP20X_IRQ_VBUS_NOT_VALID, "VBUS_NOT_VALID"),
पूर्ण;

अटल स्थिर काष्ठा resource axp22x_usb_घातer_supply_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(AXP22X_IRQ_VBUS_PLUGIN, "VBUS_PLUGIN"),
	DEFINE_RES_IRQ_NAMED(AXP22X_IRQ_VBUS_REMOVAL, "VBUS_REMOVAL"),
पूर्ण;

/* AXP803 and AXP813/AXP818 share the same पूर्णांकerrupts */
अटल स्थिर काष्ठा resource axp803_usb_घातer_supply_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(AXP803_IRQ_VBUS_PLUGIN, "VBUS_PLUGIN"),
	DEFINE_RES_IRQ_NAMED(AXP803_IRQ_VBUS_REMOVAL, "VBUS_REMOVAL"),
पूर्ण;

अटल स्थिर काष्ठा resource axp22x_pek_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(AXP22X_IRQ_PEK_RIS_EDGE, "PEK_DBR"),
	DEFINE_RES_IRQ_NAMED(AXP22X_IRQ_PEK_FAL_EDGE, "PEK_DBF"),
पूर्ण;

अटल स्थिर काष्ठा resource axp288_घातer_button_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(AXP288_IRQ_POKP, "PEK_DBR"),
	DEFINE_RES_IRQ_NAMED(AXP288_IRQ_POKN, "PEK_DBF"),
पूर्ण;

अटल स्थिर काष्ठा resource axp288_fuel_gauge_resources[] = अणु
	DEFINE_RES_IRQ(AXP288_IRQ_QWBTU),
	DEFINE_RES_IRQ(AXP288_IRQ_WBTU),
	DEFINE_RES_IRQ(AXP288_IRQ_QWBTO),
	DEFINE_RES_IRQ(AXP288_IRQ_WBTO),
	DEFINE_RES_IRQ(AXP288_IRQ_WL2),
	DEFINE_RES_IRQ(AXP288_IRQ_WL1),
पूर्ण;

अटल स्थिर काष्ठा resource axp803_pek_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(AXP803_IRQ_PEK_RIS_EDGE, "PEK_DBR"),
	DEFINE_RES_IRQ_NAMED(AXP803_IRQ_PEK_FAL_EDGE, "PEK_DBF"),
पूर्ण;

अटल स्थिर काष्ठा resource axp806_pek_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(AXP806_IRQ_POK_RISE, "PEK_DBR"),
	DEFINE_RES_IRQ_NAMED(AXP806_IRQ_POK_FALL, "PEK_DBF"),
पूर्ण;

अटल स्थिर काष्ठा resource axp809_pek_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(AXP809_IRQ_PEK_RIS_EDGE, "PEK_DBR"),
	DEFINE_RES_IRQ_NAMED(AXP809_IRQ_PEK_FAL_EDGE, "PEK_DBF"),
पूर्ण;

अटल स्थिर काष्ठा regmap_config axp152_regmap_config = अणु
	.reg_bits	= 8,
	.val_bits	= 8,
	.wr_table	= &axp152_ग_लिखोable_table,
	.अस्थिर_table	= &axp152_अस्थिर_table,
	.max_रेजिस्टर	= AXP152_PWM1_DUTY_CYCLE,
	.cache_type	= REGCACHE_RBTREE,
पूर्ण;

अटल स्थिर काष्ठा regmap_config axp20x_regmap_config = अणु
	.reg_bits	= 8,
	.val_bits	= 8,
	.wr_table	= &axp20x_ग_लिखोable_table,
	.अस्थिर_table	= &axp20x_अस्थिर_table,
	.max_रेजिस्टर	= AXP20X_OCV(AXP20X_OCV_MAX),
	.cache_type	= REGCACHE_RBTREE,
पूर्ण;

अटल स्थिर काष्ठा regmap_config axp22x_regmap_config = अणु
	.reg_bits	= 8,
	.val_bits	= 8,
	.wr_table	= &axp22x_ग_लिखोable_table,
	.अस्थिर_table	= &axp22x_अस्थिर_table,
	.max_रेजिस्टर	= AXP22X_BATLOW_THRES1,
	.cache_type	= REGCACHE_RBTREE,
पूर्ण;

अटल स्थिर काष्ठा regmap_config axp288_regmap_config = अणु
	.reg_bits	= 8,
	.val_bits	= 8,
	.wr_table	= &axp288_ग_लिखोable_table,
	.अस्थिर_table	= &axp288_अस्थिर_table,
	.max_रेजिस्टर	= AXP288_FG_TUNE5,
	.cache_type	= REGCACHE_RBTREE,
पूर्ण;

अटल स्थिर काष्ठा regmap_config axp806_regmap_config = अणु
	.reg_bits	= 8,
	.val_bits	= 8,
	.wr_table	= &axp806_ग_लिखोable_table,
	.अस्थिर_table	= &axp806_अस्थिर_table,
	.max_रेजिस्टर	= AXP806_REG_ADDR_EXT,
	.cache_type	= REGCACHE_RBTREE,
पूर्ण;

#घोषणा INIT_REGMAP_IRQ(_variant, _irq, _off, _mask)			\
	[_variant##_IRQ_##_irq] = अणु .reg_offset = (_off), .mask = BIT(_mask) पूर्ण

अटल स्थिर काष्ठा regmap_irq axp152_regmap_irqs[] = अणु
	INIT_REGMAP_IRQ(AXP152, LDO0IN_CONNECT,		0, 6),
	INIT_REGMAP_IRQ(AXP152, LDO0IN_REMOVAL,		0, 5),
	INIT_REGMAP_IRQ(AXP152, ALDO0IN_CONNECT,	0, 3),
	INIT_REGMAP_IRQ(AXP152, ALDO0IN_REMOVAL,	0, 2),
	INIT_REGMAP_IRQ(AXP152, DCDC1_V_LOW,		1, 5),
	INIT_REGMAP_IRQ(AXP152, DCDC2_V_LOW,		1, 4),
	INIT_REGMAP_IRQ(AXP152, DCDC3_V_LOW,		1, 3),
	INIT_REGMAP_IRQ(AXP152, DCDC4_V_LOW,		1, 2),
	INIT_REGMAP_IRQ(AXP152, PEK_SHORT,		1, 1),
	INIT_REGMAP_IRQ(AXP152, PEK_LONG,		1, 0),
	INIT_REGMAP_IRQ(AXP152, TIMER,			2, 7),
	INIT_REGMAP_IRQ(AXP152, PEK_RIS_EDGE,		2, 6),
	INIT_REGMAP_IRQ(AXP152, PEK_FAL_EDGE,		2, 5),
	INIT_REGMAP_IRQ(AXP152, GPIO3_INPUT,		2, 3),
	INIT_REGMAP_IRQ(AXP152, GPIO2_INPUT,		2, 2),
	INIT_REGMAP_IRQ(AXP152, GPIO1_INPUT,		2, 1),
	INIT_REGMAP_IRQ(AXP152, GPIO0_INPUT,		2, 0),
पूर्ण;

अटल स्थिर काष्ठा regmap_irq axp20x_regmap_irqs[] = अणु
	INIT_REGMAP_IRQ(AXP20X, ACIN_OVER_V,		0, 7),
	INIT_REGMAP_IRQ(AXP20X, ACIN_PLUGIN,		0, 6),
	INIT_REGMAP_IRQ(AXP20X, ACIN_REMOVAL,	        0, 5),
	INIT_REGMAP_IRQ(AXP20X, VBUS_OVER_V,		0, 4),
	INIT_REGMAP_IRQ(AXP20X, VBUS_PLUGIN,		0, 3),
	INIT_REGMAP_IRQ(AXP20X, VBUS_REMOVAL,	        0, 2),
	INIT_REGMAP_IRQ(AXP20X, VBUS_V_LOW,		0, 1),
	INIT_REGMAP_IRQ(AXP20X, BATT_PLUGIN,		1, 7),
	INIT_REGMAP_IRQ(AXP20X, BATT_REMOVAL,	        1, 6),
	INIT_REGMAP_IRQ(AXP20X, BATT_ENT_ACT_MODE,	1, 5),
	INIT_REGMAP_IRQ(AXP20X, BATT_EXIT_ACT_MODE,	1, 4),
	INIT_REGMAP_IRQ(AXP20X, CHARG,		        1, 3),
	INIT_REGMAP_IRQ(AXP20X, CHARG_DONE,		1, 2),
	INIT_REGMAP_IRQ(AXP20X, BATT_TEMP_HIGH,	        1, 1),
	INIT_REGMAP_IRQ(AXP20X, BATT_TEMP_LOW,	        1, 0),
	INIT_REGMAP_IRQ(AXP20X, DIE_TEMP_HIGH,	        2, 7),
	INIT_REGMAP_IRQ(AXP20X, CHARG_I_LOW,		2, 6),
	INIT_REGMAP_IRQ(AXP20X, DCDC1_V_LONG,	        2, 5),
	INIT_REGMAP_IRQ(AXP20X, DCDC2_V_LONG,	        2, 4),
	INIT_REGMAP_IRQ(AXP20X, DCDC3_V_LONG,	        2, 3),
	INIT_REGMAP_IRQ(AXP20X, PEK_SHORT,		2, 1),
	INIT_REGMAP_IRQ(AXP20X, PEK_LONG,		2, 0),
	INIT_REGMAP_IRQ(AXP20X, N_OE_PWR_ON,		3, 7),
	INIT_REGMAP_IRQ(AXP20X, N_OE_PWR_OFF,	        3, 6),
	INIT_REGMAP_IRQ(AXP20X, VBUS_VALID,		3, 5),
	INIT_REGMAP_IRQ(AXP20X, VBUS_NOT_VALID,	        3, 4),
	INIT_REGMAP_IRQ(AXP20X, VBUS_SESS_VALID,	3, 3),
	INIT_REGMAP_IRQ(AXP20X, VBUS_SESS_END,	        3, 2),
	INIT_REGMAP_IRQ(AXP20X, LOW_PWR_LVL1,	        3, 1),
	INIT_REGMAP_IRQ(AXP20X, LOW_PWR_LVL2,	        3, 0),
	INIT_REGMAP_IRQ(AXP20X, TIMER,		        4, 7),
	INIT_REGMAP_IRQ(AXP20X, PEK_RIS_EDGE,	        4, 6),
	INIT_REGMAP_IRQ(AXP20X, PEK_FAL_EDGE,	        4, 5),
	INIT_REGMAP_IRQ(AXP20X, GPIO3_INPUT,		4, 3),
	INIT_REGMAP_IRQ(AXP20X, GPIO2_INPUT,		4, 2),
	INIT_REGMAP_IRQ(AXP20X, GPIO1_INPUT,		4, 1),
	INIT_REGMAP_IRQ(AXP20X, GPIO0_INPUT,		4, 0),
पूर्ण;

अटल स्थिर काष्ठा regmap_irq axp22x_regmap_irqs[] = अणु
	INIT_REGMAP_IRQ(AXP22X, ACIN_OVER_V,		0, 7),
	INIT_REGMAP_IRQ(AXP22X, ACIN_PLUGIN,		0, 6),
	INIT_REGMAP_IRQ(AXP22X, ACIN_REMOVAL,	        0, 5),
	INIT_REGMAP_IRQ(AXP22X, VBUS_OVER_V,		0, 4),
	INIT_REGMAP_IRQ(AXP22X, VBUS_PLUGIN,		0, 3),
	INIT_REGMAP_IRQ(AXP22X, VBUS_REMOVAL,	        0, 2),
	INIT_REGMAP_IRQ(AXP22X, VBUS_V_LOW,		0, 1),
	INIT_REGMAP_IRQ(AXP22X, BATT_PLUGIN,		1, 7),
	INIT_REGMAP_IRQ(AXP22X, BATT_REMOVAL,	        1, 6),
	INIT_REGMAP_IRQ(AXP22X, BATT_ENT_ACT_MODE,	1, 5),
	INIT_REGMAP_IRQ(AXP22X, BATT_EXIT_ACT_MODE,	1, 4),
	INIT_REGMAP_IRQ(AXP22X, CHARG,		        1, 3),
	INIT_REGMAP_IRQ(AXP22X, CHARG_DONE,		1, 2),
	INIT_REGMAP_IRQ(AXP22X, BATT_TEMP_HIGH,	        1, 1),
	INIT_REGMAP_IRQ(AXP22X, BATT_TEMP_LOW,	        1, 0),
	INIT_REGMAP_IRQ(AXP22X, DIE_TEMP_HIGH,	        2, 7),
	INIT_REGMAP_IRQ(AXP22X, PEK_SHORT,		2, 1),
	INIT_REGMAP_IRQ(AXP22X, PEK_LONG,		2, 0),
	INIT_REGMAP_IRQ(AXP22X, LOW_PWR_LVL1,	        3, 1),
	INIT_REGMAP_IRQ(AXP22X, LOW_PWR_LVL2,	        3, 0),
	INIT_REGMAP_IRQ(AXP22X, TIMER,		        4, 7),
	INIT_REGMAP_IRQ(AXP22X, PEK_RIS_EDGE,	        4, 6),
	INIT_REGMAP_IRQ(AXP22X, PEK_FAL_EDGE,	        4, 5),
	INIT_REGMAP_IRQ(AXP22X, GPIO1_INPUT,		4, 1),
	INIT_REGMAP_IRQ(AXP22X, GPIO0_INPUT,		4, 0),
पूर्ण;

/* some IRQs are compatible with axp20x models */
अटल स्थिर काष्ठा regmap_irq axp288_regmap_irqs[] = अणु
	INIT_REGMAP_IRQ(AXP288, VBUS_FALL,              0, 2),
	INIT_REGMAP_IRQ(AXP288, VBUS_RISE,              0, 3),
	INIT_REGMAP_IRQ(AXP288, OV,                     0, 4),
	INIT_REGMAP_IRQ(AXP288, FALLING_ALT,            0, 5),
	INIT_REGMAP_IRQ(AXP288, RISING_ALT,             0, 6),
	INIT_REGMAP_IRQ(AXP288, OV_ALT,                 0, 7),

	INIT_REGMAP_IRQ(AXP288, DONE,                   1, 2),
	INIT_REGMAP_IRQ(AXP288, CHARGING,               1, 3),
	INIT_REGMAP_IRQ(AXP288, SAFE_QUIT,              1, 4),
	INIT_REGMAP_IRQ(AXP288, SAFE_ENTER,             1, 5),
	INIT_REGMAP_IRQ(AXP288, ABSENT,                 1, 6),
	INIT_REGMAP_IRQ(AXP288, APPEND,                 1, 7),

	INIT_REGMAP_IRQ(AXP288, QWBTU,                  2, 0),
	INIT_REGMAP_IRQ(AXP288, WBTU,                   2, 1),
	INIT_REGMAP_IRQ(AXP288, QWBTO,                  2, 2),
	INIT_REGMAP_IRQ(AXP288, WBTO,                   2, 3),
	INIT_REGMAP_IRQ(AXP288, QCBTU,                  2, 4),
	INIT_REGMAP_IRQ(AXP288, CBTU,                   2, 5),
	INIT_REGMAP_IRQ(AXP288, QCBTO,                  2, 6),
	INIT_REGMAP_IRQ(AXP288, CBTO,                   2, 7),

	INIT_REGMAP_IRQ(AXP288, WL2,                    3, 0),
	INIT_REGMAP_IRQ(AXP288, WL1,                    3, 1),
	INIT_REGMAP_IRQ(AXP288, GPADC,                  3, 2),
	INIT_REGMAP_IRQ(AXP288, OT,                     3, 7),

	INIT_REGMAP_IRQ(AXP288, GPIO0,                  4, 0),
	INIT_REGMAP_IRQ(AXP288, GPIO1,                  4, 1),
	INIT_REGMAP_IRQ(AXP288, POKO,                   4, 2),
	INIT_REGMAP_IRQ(AXP288, POKL,                   4, 3),
	INIT_REGMAP_IRQ(AXP288, POKS,                   4, 4),
	INIT_REGMAP_IRQ(AXP288, POKN,                   4, 5),
	INIT_REGMAP_IRQ(AXP288, POKP,                   4, 6),
	INIT_REGMAP_IRQ(AXP288, TIMER,                  4, 7),

	INIT_REGMAP_IRQ(AXP288, MV_CHNG,                5, 0),
	INIT_REGMAP_IRQ(AXP288, BC_USB_CHNG,            5, 1),
पूर्ण;

अटल स्थिर काष्ठा regmap_irq axp803_regmap_irqs[] = अणु
	INIT_REGMAP_IRQ(AXP803, ACIN_OVER_V,		0, 7),
	INIT_REGMAP_IRQ(AXP803, ACIN_PLUGIN,		0, 6),
	INIT_REGMAP_IRQ(AXP803, ACIN_REMOVAL,	        0, 5),
	INIT_REGMAP_IRQ(AXP803, VBUS_OVER_V,		0, 4),
	INIT_REGMAP_IRQ(AXP803, VBUS_PLUGIN,		0, 3),
	INIT_REGMAP_IRQ(AXP803, VBUS_REMOVAL,	        0, 2),
	INIT_REGMAP_IRQ(AXP803, BATT_PLUGIN,		1, 7),
	INIT_REGMAP_IRQ(AXP803, BATT_REMOVAL,	        1, 6),
	INIT_REGMAP_IRQ(AXP803, BATT_ENT_ACT_MODE,	1, 5),
	INIT_REGMAP_IRQ(AXP803, BATT_EXIT_ACT_MODE,	1, 4),
	INIT_REGMAP_IRQ(AXP803, CHARG,		        1, 3),
	INIT_REGMAP_IRQ(AXP803, CHARG_DONE,		1, 2),
	INIT_REGMAP_IRQ(AXP803, BATT_CHG_TEMP_HIGH,	2, 7),
	INIT_REGMAP_IRQ(AXP803, BATT_CHG_TEMP_HIGH_END,	2, 6),
	INIT_REGMAP_IRQ(AXP803, BATT_CHG_TEMP_LOW,	2, 5),
	INIT_REGMAP_IRQ(AXP803, BATT_CHG_TEMP_LOW_END,	2, 4),
	INIT_REGMAP_IRQ(AXP803, BATT_ACT_TEMP_HIGH,	2, 3),
	INIT_REGMAP_IRQ(AXP803, BATT_ACT_TEMP_HIGH_END,	2, 2),
	INIT_REGMAP_IRQ(AXP803, BATT_ACT_TEMP_LOW,	2, 1),
	INIT_REGMAP_IRQ(AXP803, BATT_ACT_TEMP_LOW_END,	2, 0),
	INIT_REGMAP_IRQ(AXP803, DIE_TEMP_HIGH,	        3, 7),
	INIT_REGMAP_IRQ(AXP803, GPADC,		        3, 2),
	INIT_REGMAP_IRQ(AXP803, LOW_PWR_LVL1,	        3, 1),
	INIT_REGMAP_IRQ(AXP803, LOW_PWR_LVL2,	        3, 0),
	INIT_REGMAP_IRQ(AXP803, TIMER,		        4, 7),
	INIT_REGMAP_IRQ(AXP803, PEK_RIS_EDGE,	        4, 6),
	INIT_REGMAP_IRQ(AXP803, PEK_FAL_EDGE,	        4, 5),
	INIT_REGMAP_IRQ(AXP803, PEK_SHORT,		4, 4),
	INIT_REGMAP_IRQ(AXP803, PEK_LONG,		4, 3),
	INIT_REGMAP_IRQ(AXP803, PEK_OVER_OFF,		4, 2),
	INIT_REGMAP_IRQ(AXP803, GPIO1_INPUT,		4, 1),
	INIT_REGMAP_IRQ(AXP803, GPIO0_INPUT,		4, 0),
	INIT_REGMAP_IRQ(AXP803, BC_USB_CHNG,            5, 1),
	INIT_REGMAP_IRQ(AXP803, MV_CHNG,                5, 0),
पूर्ण;

अटल स्थिर काष्ठा regmap_irq axp806_regmap_irqs[] = अणु
	INIT_REGMAP_IRQ(AXP806, DIE_TEMP_HIGH_LV1,	0, 0),
	INIT_REGMAP_IRQ(AXP806, DIE_TEMP_HIGH_LV2,	0, 1),
	INIT_REGMAP_IRQ(AXP806, DCDCA_V_LOW,		0, 3),
	INIT_REGMAP_IRQ(AXP806, DCDCB_V_LOW,		0, 4),
	INIT_REGMAP_IRQ(AXP806, DCDCC_V_LOW,		0, 5),
	INIT_REGMAP_IRQ(AXP806, DCDCD_V_LOW,		0, 6),
	INIT_REGMAP_IRQ(AXP806, DCDCE_V_LOW,		0, 7),
	INIT_REGMAP_IRQ(AXP806, POK_LONG,		1, 0),
	INIT_REGMAP_IRQ(AXP806, POK_SHORT,		1, 1),
	INIT_REGMAP_IRQ(AXP806, WAKEUP,			1, 4),
	INIT_REGMAP_IRQ(AXP806, POK_FALL,		1, 5),
	INIT_REGMAP_IRQ(AXP806, POK_RISE,		1, 6),
पूर्ण;

अटल स्थिर काष्ठा regmap_irq axp809_regmap_irqs[] = अणु
	INIT_REGMAP_IRQ(AXP809, ACIN_OVER_V,		0, 7),
	INIT_REGMAP_IRQ(AXP809, ACIN_PLUGIN,		0, 6),
	INIT_REGMAP_IRQ(AXP809, ACIN_REMOVAL,	        0, 5),
	INIT_REGMAP_IRQ(AXP809, VBUS_OVER_V,		0, 4),
	INIT_REGMAP_IRQ(AXP809, VBUS_PLUGIN,		0, 3),
	INIT_REGMAP_IRQ(AXP809, VBUS_REMOVAL,	        0, 2),
	INIT_REGMAP_IRQ(AXP809, VBUS_V_LOW,		0, 1),
	INIT_REGMAP_IRQ(AXP809, BATT_PLUGIN,		1, 7),
	INIT_REGMAP_IRQ(AXP809, BATT_REMOVAL,	        1, 6),
	INIT_REGMAP_IRQ(AXP809, BATT_ENT_ACT_MODE,	1, 5),
	INIT_REGMAP_IRQ(AXP809, BATT_EXIT_ACT_MODE,	1, 4),
	INIT_REGMAP_IRQ(AXP809, CHARG,		        1, 3),
	INIT_REGMAP_IRQ(AXP809, CHARG_DONE,		1, 2),
	INIT_REGMAP_IRQ(AXP809, BATT_CHG_TEMP_HIGH,	2, 7),
	INIT_REGMAP_IRQ(AXP809, BATT_CHG_TEMP_HIGH_END,	2, 6),
	INIT_REGMAP_IRQ(AXP809, BATT_CHG_TEMP_LOW,	2, 5),
	INIT_REGMAP_IRQ(AXP809, BATT_CHG_TEMP_LOW_END,	2, 4),
	INIT_REGMAP_IRQ(AXP809, BATT_ACT_TEMP_HIGH,	2, 3),
	INIT_REGMAP_IRQ(AXP809, BATT_ACT_TEMP_HIGH_END,	2, 2),
	INIT_REGMAP_IRQ(AXP809, BATT_ACT_TEMP_LOW,	2, 1),
	INIT_REGMAP_IRQ(AXP809, BATT_ACT_TEMP_LOW_END,	2, 0),
	INIT_REGMAP_IRQ(AXP809, DIE_TEMP_HIGH,	        3, 7),
	INIT_REGMAP_IRQ(AXP809, LOW_PWR_LVL1,	        3, 1),
	INIT_REGMAP_IRQ(AXP809, LOW_PWR_LVL2,	        3, 0),
	INIT_REGMAP_IRQ(AXP809, TIMER,		        4, 7),
	INIT_REGMAP_IRQ(AXP809, PEK_RIS_EDGE,	        4, 6),
	INIT_REGMAP_IRQ(AXP809, PEK_FAL_EDGE,	        4, 5),
	INIT_REGMAP_IRQ(AXP809, PEK_SHORT,		4, 4),
	INIT_REGMAP_IRQ(AXP809, PEK_LONG,		4, 3),
	INIT_REGMAP_IRQ(AXP809, PEK_OVER_OFF,		4, 2),
	INIT_REGMAP_IRQ(AXP809, GPIO1_INPUT,		4, 1),
	INIT_REGMAP_IRQ(AXP809, GPIO0_INPUT,		4, 0),
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip axp152_regmap_irq_chip = अणु
	.name			= "axp152_irq_chip",
	.status_base		= AXP152_IRQ1_STATE,
	.ack_base		= AXP152_IRQ1_STATE,
	.mask_base		= AXP152_IRQ1_EN,
	.mask_invert		= true,
	.init_ack_masked	= true,
	.irqs			= axp152_regmap_irqs,
	.num_irqs		= ARRAY_SIZE(axp152_regmap_irqs),
	.num_regs		= 3,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip axp20x_regmap_irq_chip = अणु
	.name			= "axp20x_irq_chip",
	.status_base		= AXP20X_IRQ1_STATE,
	.ack_base		= AXP20X_IRQ1_STATE,
	.mask_base		= AXP20X_IRQ1_EN,
	.mask_invert		= true,
	.init_ack_masked	= true,
	.irqs			= axp20x_regmap_irqs,
	.num_irqs		= ARRAY_SIZE(axp20x_regmap_irqs),
	.num_regs		= 5,

पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip axp22x_regmap_irq_chip = अणु
	.name			= "axp22x_irq_chip",
	.status_base		= AXP20X_IRQ1_STATE,
	.ack_base		= AXP20X_IRQ1_STATE,
	.mask_base		= AXP20X_IRQ1_EN,
	.mask_invert		= true,
	.init_ack_masked	= true,
	.irqs			= axp22x_regmap_irqs,
	.num_irqs		= ARRAY_SIZE(axp22x_regmap_irqs),
	.num_regs		= 5,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip axp288_regmap_irq_chip = अणु
	.name			= "axp288_irq_chip",
	.status_base		= AXP20X_IRQ1_STATE,
	.ack_base		= AXP20X_IRQ1_STATE,
	.mask_base		= AXP20X_IRQ1_EN,
	.mask_invert		= true,
	.init_ack_masked	= true,
	.irqs			= axp288_regmap_irqs,
	.num_irqs		= ARRAY_SIZE(axp288_regmap_irqs),
	.num_regs		= 6,

पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip axp803_regmap_irq_chip = अणु
	.name			= "axp803",
	.status_base		= AXP20X_IRQ1_STATE,
	.ack_base		= AXP20X_IRQ1_STATE,
	.mask_base		= AXP20X_IRQ1_EN,
	.mask_invert		= true,
	.init_ack_masked	= true,
	.irqs			= axp803_regmap_irqs,
	.num_irqs		= ARRAY_SIZE(axp803_regmap_irqs),
	.num_regs		= 6,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip axp806_regmap_irq_chip = अणु
	.name			= "axp806",
	.status_base		= AXP20X_IRQ1_STATE,
	.ack_base		= AXP20X_IRQ1_STATE,
	.mask_base		= AXP20X_IRQ1_EN,
	.mask_invert		= true,
	.init_ack_masked	= true,
	.irqs			= axp806_regmap_irqs,
	.num_irqs		= ARRAY_SIZE(axp806_regmap_irqs),
	.num_regs		= 2,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip axp809_regmap_irq_chip = अणु
	.name			= "axp809",
	.status_base		= AXP20X_IRQ1_STATE,
	.ack_base		= AXP20X_IRQ1_STATE,
	.mask_base		= AXP20X_IRQ1_EN,
	.mask_invert		= true,
	.init_ack_masked	= true,
	.irqs			= axp809_regmap_irqs,
	.num_irqs		= ARRAY_SIZE(axp809_regmap_irqs),
	.num_regs		= 5,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell axp20x_cells[] = अणु
	अणु
		.name		= "axp20x-gpio",
		.of_compatible	= "x-powers,axp209-gpio",
	पूर्ण, अणु
		.name		= "axp20x-pek",
		.num_resources	= ARRAY_SIZE(axp20x_pek_resources),
		.resources	= axp20x_pek_resources,
	पूर्ण, अणु
		.name		= "axp20x-regulator",
	पूर्ण, अणु
		.name		= "axp20x-adc",
		.of_compatible	= "x-powers,axp209-adc",
	पूर्ण, अणु
		.name		= "axp20x-battery-power-supply",
		.of_compatible	= "x-powers,axp209-battery-power-supply",
	पूर्ण, अणु
		.name		= "axp20x-ac-power-supply",
		.of_compatible	= "x-powers,axp202-ac-power-supply",
		.num_resources	= ARRAY_SIZE(axp20x_ac_घातer_supply_resources),
		.resources	= axp20x_ac_घातer_supply_resources,
	पूर्ण, अणु
		.name		= "axp20x-usb-power-supply",
		.of_compatible	= "x-powers,axp202-usb-power-supply",
		.num_resources	= ARRAY_SIZE(axp20x_usb_घातer_supply_resources),
		.resources	= axp20x_usb_घातer_supply_resources,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell axp221_cells[] = अणु
	अणु
		.name		= "axp221-pek",
		.num_resources	= ARRAY_SIZE(axp22x_pek_resources),
		.resources	= axp22x_pek_resources,
	पूर्ण, अणु
		.name		= "axp20x-regulator",
	पूर्ण, अणु
		.name		= "axp22x-adc",
		.of_compatible	= "x-powers,axp221-adc",
	पूर्ण, अणु
		.name		= "axp20x-ac-power-supply",
		.of_compatible	= "x-powers,axp221-ac-power-supply",
		.num_resources	= ARRAY_SIZE(axp20x_ac_घातer_supply_resources),
		.resources	= axp20x_ac_घातer_supply_resources,
	पूर्ण, अणु
		.name		= "axp20x-battery-power-supply",
		.of_compatible	= "x-powers,axp221-battery-power-supply",
	पूर्ण, अणु
		.name		= "axp20x-usb-power-supply",
		.of_compatible	= "x-powers,axp221-usb-power-supply",
		.num_resources	= ARRAY_SIZE(axp22x_usb_घातer_supply_resources),
		.resources	= axp22x_usb_घातer_supply_resources,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell axp223_cells[] = अणु
	अणु
		.name		= "axp221-pek",
		.num_resources	= ARRAY_SIZE(axp22x_pek_resources),
		.resources	= axp22x_pek_resources,
	पूर्ण, अणु
		.name		= "axp22x-adc",
		.of_compatible	= "x-powers,axp221-adc",
	पूर्ण, अणु
		.name		= "axp20x-battery-power-supply",
		.of_compatible	= "x-powers,axp221-battery-power-supply",
	पूर्ण, अणु
		.name		= "axp20x-regulator",
	पूर्ण, अणु
		.name		= "axp20x-ac-power-supply",
		.of_compatible	= "x-powers,axp221-ac-power-supply",
		.num_resources	= ARRAY_SIZE(axp20x_ac_घातer_supply_resources),
		.resources	= axp20x_ac_घातer_supply_resources,
	पूर्ण, अणु
		.name		= "axp20x-usb-power-supply",
		.of_compatible	= "x-powers,axp223-usb-power-supply",
		.num_resources	= ARRAY_SIZE(axp22x_usb_घातer_supply_resources),
		.resources	= axp22x_usb_घातer_supply_resources,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell axp152_cells[] = अणु
	अणु
		.name		= "axp20x-pek",
		.num_resources	= ARRAY_SIZE(axp152_pek_resources),
		.resources	= axp152_pek_resources,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource axp288_adc_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(AXP288_IRQ_GPADC, "GPADC"),
पूर्ण;

अटल स्थिर काष्ठा resource axp288_extcon_resources[] = अणु
	DEFINE_RES_IRQ(AXP288_IRQ_VBUS_FALL),
	DEFINE_RES_IRQ(AXP288_IRQ_VBUS_RISE),
	DEFINE_RES_IRQ(AXP288_IRQ_MV_CHNG),
	DEFINE_RES_IRQ(AXP288_IRQ_BC_USB_CHNG),
पूर्ण;

अटल स्थिर काष्ठा resource axp288_अक्षरger_resources[] = अणु
	DEFINE_RES_IRQ(AXP288_IRQ_OV),
	DEFINE_RES_IRQ(AXP288_IRQ_DONE),
	DEFINE_RES_IRQ(AXP288_IRQ_CHARGING),
	DEFINE_RES_IRQ(AXP288_IRQ_SAFE_QUIT),
	DEFINE_RES_IRQ(AXP288_IRQ_SAFE_ENTER),
	DEFINE_RES_IRQ(AXP288_IRQ_QCBTU),
	DEFINE_RES_IRQ(AXP288_IRQ_CBTU),
	DEFINE_RES_IRQ(AXP288_IRQ_QCBTO),
	DEFINE_RES_IRQ(AXP288_IRQ_CBTO),
पूर्ण;

अटल स्थिर काष्ठा mfd_cell axp288_cells[] = अणु
	अणु
		.name		= "axp288_adc",
		.num_resources	= ARRAY_SIZE(axp288_adc_resources),
		.resources	= axp288_adc_resources,
	पूर्ण, अणु
		.name		= "axp288_extcon",
		.num_resources	= ARRAY_SIZE(axp288_extcon_resources),
		.resources	= axp288_extcon_resources,
	पूर्ण, अणु
		.name		= "axp288_charger",
		.num_resources	= ARRAY_SIZE(axp288_अक्षरger_resources),
		.resources	= axp288_अक्षरger_resources,
	पूर्ण, अणु
		.name		= "axp288_fuel_gauge",
		.num_resources	= ARRAY_SIZE(axp288_fuel_gauge_resources),
		.resources	= axp288_fuel_gauge_resources,
	पूर्ण, अणु
		.name		= "axp221-pek",
		.num_resources	= ARRAY_SIZE(axp288_घातer_button_resources),
		.resources	= axp288_घातer_button_resources,
	पूर्ण, अणु
		.name		= "axp288_pmic_acpi",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell axp803_cells[] = अणु
	अणु
		.name		= "axp221-pek",
		.num_resources	= ARRAY_SIZE(axp803_pek_resources),
		.resources	= axp803_pek_resources,
	पूर्ण, अणु
		.name		= "axp20x-gpio",
		.of_compatible	= "x-powers,axp813-gpio",
	पूर्ण, अणु
		.name		= "axp813-adc",
		.of_compatible	= "x-powers,axp813-adc",
	पूर्ण, अणु
		.name		= "axp20x-battery-power-supply",
		.of_compatible	= "x-powers,axp813-battery-power-supply",
	पूर्ण, अणु
		.name		= "axp20x-ac-power-supply",
		.of_compatible	= "x-powers,axp813-ac-power-supply",
		.num_resources	= ARRAY_SIZE(axp20x_ac_घातer_supply_resources),
		.resources	= axp20x_ac_घातer_supply_resources,
	पूर्ण, अणु
		.name		= "axp20x-usb-power-supply",
		.num_resources	= ARRAY_SIZE(axp803_usb_घातer_supply_resources),
		.resources	= axp803_usb_घातer_supply_resources,
		.of_compatible	= "x-powers,axp813-usb-power-supply",
	पूर्ण,
	अणु	.name		= "axp20x-regulator" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell axp806_self_working_cells[] = अणु
	अणु
		.name		= "axp221-pek",
		.num_resources	= ARRAY_SIZE(axp806_pek_resources),
		.resources	= axp806_pek_resources,
	पूर्ण,
	अणु	.name		= "axp20x-regulator" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell axp806_cells[] = अणु
	अणु
		.id		= 2,
		.name		= "axp20x-regulator",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell axp809_cells[] = अणु
	अणु
		.name		= "axp221-pek",
		.num_resources	= ARRAY_SIZE(axp809_pek_resources),
		.resources	= axp809_pek_resources,
	पूर्ण, अणु
		.id		= 1,
		.name		= "axp20x-regulator",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell axp813_cells[] = अणु
	अणु
		.name		= "axp221-pek",
		.num_resources	= ARRAY_SIZE(axp803_pek_resources),
		.resources	= axp803_pek_resources,
	पूर्ण, अणु
		.name		= "axp20x-regulator",
	पूर्ण, अणु
		.name		= "axp20x-gpio",
		.of_compatible	= "x-powers,axp813-gpio",
	पूर्ण, अणु
		.name		= "axp813-adc",
		.of_compatible	= "x-powers,axp813-adc",
	पूर्ण, अणु
		.name		= "axp20x-battery-power-supply",
		.of_compatible	= "x-powers,axp813-battery-power-supply",
	पूर्ण, अणु
		.name		= "axp20x-ac-power-supply",
		.of_compatible	= "x-powers,axp813-ac-power-supply",
		.num_resources	= ARRAY_SIZE(axp20x_ac_घातer_supply_resources),
		.resources	= axp20x_ac_घातer_supply_resources,
	पूर्ण, अणु
		.name		= "axp20x-usb-power-supply",
		.num_resources	= ARRAY_SIZE(axp803_usb_घातer_supply_resources),
		.resources	= axp803_usb_घातer_supply_resources,
		.of_compatible	= "x-powers,axp813-usb-power-supply",
	पूर्ण,
पूर्ण;

अटल काष्ठा axp20x_dev *axp20x_pm_घातer_off;
अटल व्योम axp20x_घातer_off(व्योम)
अणु
	अगर (axp20x_pm_घातer_off->variant == AXP288_ID)
		वापस;

	regmap_ग_लिखो(axp20x_pm_घातer_off->regmap, AXP20X_OFF_CTRL,
		     AXP20X_OFF);

	/* Give capacitors etc. समय to drain to aव्योम kernel panic msg. */
	msleep(500);
पूर्ण

पूर्णांक axp20x_match_device(काष्ठा axp20x_dev *axp20x)
अणु
	काष्ठा device *dev = axp20x->dev;
	स्थिर काष्ठा acpi_device_id *acpi_id;
	स्थिर काष्ठा of_device_id *of_id;

	अगर (dev->of_node) अणु
		of_id = of_match_device(dev->driver->of_match_table, dev);
		अगर (!of_id) अणु
			dev_err(dev, "Unable to match OF ID\n");
			वापस -ENODEV;
		पूर्ण
		axp20x->variant = (दीर्घ)of_id->data;
	पूर्ण अन्यथा अणु
		acpi_id = acpi_match_device(dev->driver->acpi_match_table, dev);
		अगर (!acpi_id || !acpi_id->driver_data) अणु
			dev_err(dev, "Unable to match ACPI ID and data\n");
			वापस -ENODEV;
		पूर्ण
		axp20x->variant = (दीर्घ)acpi_id->driver_data;
	पूर्ण

	चयन (axp20x->variant) अणु
	हाल AXP152_ID:
		axp20x->nr_cells = ARRAY_SIZE(axp152_cells);
		axp20x->cells = axp152_cells;
		axp20x->regmap_cfg = &axp152_regmap_config;
		axp20x->regmap_irq_chip = &axp152_regmap_irq_chip;
		अवरोध;
	हाल AXP202_ID:
	हाल AXP209_ID:
		axp20x->nr_cells = ARRAY_SIZE(axp20x_cells);
		axp20x->cells = axp20x_cells;
		axp20x->regmap_cfg = &axp20x_regmap_config;
		axp20x->regmap_irq_chip = &axp20x_regmap_irq_chip;
		अवरोध;
	हाल AXP221_ID:
		axp20x->nr_cells = ARRAY_SIZE(axp221_cells);
		axp20x->cells = axp221_cells;
		axp20x->regmap_cfg = &axp22x_regmap_config;
		axp20x->regmap_irq_chip = &axp22x_regmap_irq_chip;
		अवरोध;
	हाल AXP223_ID:
		axp20x->nr_cells = ARRAY_SIZE(axp223_cells);
		axp20x->cells = axp223_cells;
		axp20x->regmap_cfg = &axp22x_regmap_config;
		axp20x->regmap_irq_chip = &axp22x_regmap_irq_chip;
		अवरोध;
	हाल AXP288_ID:
		axp20x->cells = axp288_cells;
		axp20x->nr_cells = ARRAY_SIZE(axp288_cells);
		axp20x->regmap_cfg = &axp288_regmap_config;
		axp20x->regmap_irq_chip = &axp288_regmap_irq_chip;
		axp20x->irq_flags = IRQF_TRIGGER_LOW;
		अवरोध;
	हाल AXP803_ID:
		axp20x->nr_cells = ARRAY_SIZE(axp803_cells);
		axp20x->cells = axp803_cells;
		axp20x->regmap_cfg = &axp288_regmap_config;
		axp20x->regmap_irq_chip = &axp803_regmap_irq_chip;
		अवरोध;
	हाल AXP806_ID:
		अगर (of_property_पढ़ो_bool(axp20x->dev->of_node,
					  "x-powers,self-working-mode")) अणु
			axp20x->nr_cells = ARRAY_SIZE(axp806_self_working_cells);
			axp20x->cells = axp806_self_working_cells;
		पूर्ण अन्यथा अणु
			axp20x->nr_cells = ARRAY_SIZE(axp806_cells);
			axp20x->cells = axp806_cells;
		पूर्ण
		axp20x->regmap_cfg = &axp806_regmap_config;
		axp20x->regmap_irq_chip = &axp806_regmap_irq_chip;
		अवरोध;
	हाल AXP809_ID:
		axp20x->nr_cells = ARRAY_SIZE(axp809_cells);
		axp20x->cells = axp809_cells;
		axp20x->regmap_cfg = &axp22x_regmap_config;
		axp20x->regmap_irq_chip = &axp809_regmap_irq_chip;
		अवरोध;
	हाल AXP813_ID:
		axp20x->nr_cells = ARRAY_SIZE(axp813_cells);
		axp20x->cells = axp813_cells;
		axp20x->regmap_cfg = &axp288_regmap_config;
		/*
		 * The IRQ table given in the datasheet is incorrect.
		 * In IRQ enable/status रेजिस्टरs 1, there are separate
		 * IRQs क्रम ACIN and VBUS, instead of bits [7:5] being
		 * the same as bits [4:2]. So it shares the same IRQs
		 * as the AXP803, rather than the AXP288.
		 */
		axp20x->regmap_irq_chip = &axp803_regmap_irq_chip;
		अवरोध;
	शेष:
		dev_err(dev, "unsupported AXP20X ID %lu\n", axp20x->variant);
		वापस -EINVAL;
	पूर्ण
	dev_info(dev, "AXP20x variant %s found\n",
		 axp20x_model_names[axp20x->variant]);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(axp20x_match_device);

पूर्णांक axp20x_device_probe(काष्ठा axp20x_dev *axp20x)
अणु
	पूर्णांक ret;

	/*
	 * The AXP806 supports either master/standalone or slave mode.
	 * Slave mode allows sharing the serial bus, even with multiple
	 * AXP806 which all have the same hardware address.
	 *
	 * This is करोne with extra "serial interface address extension",
	 * or AXP806_BUS_ADDR_EXT, and "register address extension", or
	 * AXP806_REG_ADDR_EXT, रेजिस्टरs. The क्रमmer is पढ़ो-only, with
	 * 1 bit customizable at the factory, and 1 bit depending on the
	 * state of an बाह्यal pin. The latter is writable. The device
	 * will only respond to operations to its other रेजिस्टरs when
	 * the these device addressing bits (in the upper 4 bits of the
	 * रेजिस्टरs) match.
	 *
	 * By शेष we support an AXP806 chained to an AXP809 in slave
	 * mode. Boards which use an AXP806 in master mode can set the
	 * property "x-powers,master-mode" to override the शेष.
	 */
	अगर (axp20x->variant == AXP806_ID) अणु
		अगर (of_property_पढ़ो_bool(axp20x->dev->of_node,
					  "x-powers,master-mode") ||
		    of_property_पढ़ो_bool(axp20x->dev->of_node,
					  "x-powers,self-working-mode"))
			regmap_ग_लिखो(axp20x->regmap, AXP806_REG_ADDR_EXT,
				     AXP806_REG_ADDR_EXT_ADDR_MASTER_MODE);
		अन्यथा
			regmap_ग_लिखो(axp20x->regmap, AXP806_REG_ADDR_EXT,
				     AXP806_REG_ADDR_EXT_ADDR_SLAVE_MODE);
	पूर्ण

	ret = regmap_add_irq_chip(axp20x->regmap, axp20x->irq,
			  IRQF_ONESHOT | IRQF_SHARED | axp20x->irq_flags,
			   -1, axp20x->regmap_irq_chip, &axp20x->regmap_irqc);
	अगर (ret) अणु
		dev_err(axp20x->dev, "failed to add irq chip: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = mfd_add_devices(axp20x->dev, -1, axp20x->cells,
			      axp20x->nr_cells, शून्य, 0, शून्य);

	अगर (ret) अणु
		dev_err(axp20x->dev, "failed to add MFD devices: %d\n", ret);
		regmap_del_irq_chip(axp20x->irq, axp20x->regmap_irqc);
		वापस ret;
	पूर्ण

	अगर (!pm_घातer_off) अणु
		axp20x_pm_घातer_off = axp20x;
		pm_घातer_off = axp20x_घातer_off;
	पूर्ण

	dev_info(axp20x->dev, "AXP20X driver loaded\n");

	वापस 0;
पूर्ण
EXPORT_SYMBOL(axp20x_device_probe);

व्योम axp20x_device_हटाओ(काष्ठा axp20x_dev *axp20x)
अणु
	अगर (axp20x == axp20x_pm_घातer_off) अणु
		axp20x_pm_घातer_off = शून्य;
		pm_घातer_off = शून्य;
	पूर्ण

	mfd_हटाओ_devices(axp20x->dev);
	regmap_del_irq_chip(axp20x->irq, axp20x->regmap_irqc);
पूर्ण
EXPORT_SYMBOL(axp20x_device_हटाओ);

MODULE_DESCRIPTION("PMIC MFD core driver for AXP20X");
MODULE_AUTHOR("Carlo Caione <carlo@caione.org>");
MODULE_LICENSE("GPL");
