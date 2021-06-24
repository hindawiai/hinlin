<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// Copyright (C) 2019 ROHM Semiconductors
//
// ROHM BD71828/BD71815 PMIC driver

#समावेश <linux/gpio_keys.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/irq.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/rohm-bd71815.h>
#समावेश <linux/mfd/rohm-bd71828.h>
#समावेश <linux/mfd/rohm-generic.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/types.h>

अटल काष्ठा gpio_keys_button button = अणु
	.code = KEY_POWER,
	.gpio = -1,
	.type = EV_KEY,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data bd71828_घातerkey_data = अणु
	.buttons = &button,
	.nbuttons = 1,
	.name = "bd71828-pwrkey",
पूर्ण;

अटल स्थिर काष्ठा resource bd71815_rtc_irqs[] = अणु
	DEFINE_RES_IRQ_NAMED(BD71815_INT_RTC0, "bd71815-rtc-alm-0"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_RTC1, "bd71815-rtc-alm-1"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_RTC2, "bd71815-rtc-alm-2"),
पूर्ण;

अटल स्थिर काष्ठा resource bd71828_rtc_irqs[] = अणु
	DEFINE_RES_IRQ_NAMED(BD71828_INT_RTC0, "bd71828-rtc-alm-0"),
	DEFINE_RES_IRQ_NAMED(BD71828_INT_RTC1, "bd71828-rtc-alm-1"),
	DEFINE_RES_IRQ_NAMED(BD71828_INT_RTC2, "bd71828-rtc-alm-2"),
पूर्ण;

अटल काष्ठा resource bd71815_घातer_irqs[] = अणु
	DEFINE_RES_IRQ_NAMED(BD71815_INT_DCIN_RMV, "bd71815-dcin-rmv"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_CLPS_OUT, "bd71815-clps-out"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_CLPS_IN, "bd71815-clps-in"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_DCIN_OVP_RES, "bd71815-dcin-ovp-res"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_DCIN_OVP_DET, "bd71815-dcin-ovp-det"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_DCIN_MON_RES, "bd71815-dcin-mon-res"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_DCIN_MON_DET, "bd71815-dcin-mon-det"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_VSYS_UV_RES, "bd71815-vsys-uv-res"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_VSYS_UV_DET, "bd71815-vsys-uv-det"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_VSYS_LOW_RES, "bd71815-vsys-low-res"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_VSYS_LOW_DET, "bd71815-vsys-low-det"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_VSYS_MON_RES, "bd71815-vsys-mon-res"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_VSYS_MON_RES, "bd71815-vsys-mon-det"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_CHG_WDG_TEMP, "bd71815-chg-wdg-temp"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_CHG_WDG_TIME, "bd71815-chg-wdg"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_CHG_RECHARGE_RES, "bd71815-rechg-res"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_CHG_RECHARGE_DET, "bd71815-rechg-det"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_CHG_RANGED_TEMP_TRANSITION, "bd71815-ranged-temp-transit"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_CHG_STATE_TRANSITION, "bd71815-chg-state-change"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_BAT_TEMP_NORMAL, "bd71815-bat-temp-normal"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_BAT_TEMP_दुस्फल, "bd71815-bat-temp-erange"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_BAT_REMOVED, "bd71815-bat-rmv"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_BAT_DETECTED, "bd71815-bat-det"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_THERM_REMOVED, "bd71815-therm-rmv"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_THERM_DETECTED, "bd71815-therm-det"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_BAT_DEAD, "bd71815-bat-dead"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_BAT_SHORTC_RES, "bd71815-bat-short-res"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_BAT_SHORTC_DET, "bd71815-bat-short-det"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_BAT_LOW_VOLT_RES, "bd71815-bat-low-res"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_BAT_LOW_VOLT_DET, "bd71815-bat-low-det"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_BAT_OVER_VOLT_RES, "bd71815-bat-over-res"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_BAT_OVER_VOLT_DET, "bd71815-bat-over-det"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_BAT_MON_RES, "bd71815-bat-mon-res"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_BAT_MON_DET, "bd71815-bat-mon-det"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_BAT_CC_MON1, "bd71815-bat-cc-mon1"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_BAT_CC_MON2, "bd71815-bat-cc-mon2"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_BAT_CC_MON3, "bd71815-bat-cc-mon3"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_BAT_OVER_CURR_1_RES, "bd71815-bat-oc1-res"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_BAT_OVER_CURR_1_DET, "bd71815-bat-oc1-det"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_BAT_OVER_CURR_2_RES, "bd71815-bat-oc2-res"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_BAT_OVER_CURR_2_DET, "bd71815-bat-oc2-det"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_BAT_OVER_CURR_3_RES, "bd71815-bat-oc3-res"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_BAT_OVER_CURR_3_DET, "bd71815-bat-oc3-det"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_TEMP_BAT_LOW_RES, "bd71815-bat-low-res"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_TEMP_BAT_LOW_DET, "bd71815-bat-low-det"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_TEMP_BAT_HI_RES, "bd71815-bat-hi-res"),
	DEFINE_RES_IRQ_NAMED(BD71815_INT_TEMP_BAT_HI_DET, "bd71815-bat-hi-det"),
पूर्ण;

अटल काष्ठा mfd_cell bd71815_mfd_cells[] = अणु
	अणु .name = "bd71815-pmic", पूर्ण,
	अणु .name = "bd71815-clk", पूर्ण,
	अणु .name = "bd71815-gpo", पूर्ण,
	अणु
		.name = "bd71815-power",
		.num_resources = ARRAY_SIZE(bd71815_घातer_irqs),
		.resources = &bd71815_घातer_irqs[0],
	पूर्ण,
	अणु
		.name = "bd71815-rtc",
		.num_resources = ARRAY_SIZE(bd71815_rtc_irqs),
		.resources = &bd71815_rtc_irqs[0],
	पूर्ण,
पूर्ण;

अटल काष्ठा mfd_cell bd71828_mfd_cells[] = अणु
	अणु .name = "bd71828-pmic", पूर्ण,
	अणु .name = "bd71828-gpio", पूर्ण,
	अणु .name = "bd71828-led", .of_compatible = "rohm,bd71828-leds" पूर्ण,
	/*
	 * We use BD71837 driver to drive the घड़ी block. Only dअगरferences to
	 * BD70528 घड़ी gate are the रेजिस्टर address and mask.
	 */
	अणु .name = "bd71828-clk", पूर्ण,
	अणु .name = "bd71827-power", पूर्ण,
	अणु
		.name = "bd71828-rtc",
		.resources = bd71828_rtc_irqs,
		.num_resources = ARRAY_SIZE(bd71828_rtc_irqs),
	पूर्ण, अणु
		.name = "gpio-keys",
		.platक्रमm_data = &bd71828_घातerkey_data,
		.pdata_size = माप(bd71828_घातerkey_data),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_range bd71815_अस्थिर_ranges[] = अणु
	अणु
		.range_min = BD71815_REG_SEC,
		.range_max = BD71815_REG_YEAR,
	पूर्ण, अणु
		.range_min = BD71815_REG_CONF,
		.range_max = BD71815_REG_BAT_TEMP,
	पूर्ण, अणु
		.range_min = BD71815_REG_VM_IBAT_U,
		.range_max = BD71815_REG_CC_CTRL,
	पूर्ण, अणु
		.range_min = BD71815_REG_CC_STAT,
		.range_max = BD71815_REG_CC_CURCD_L,
	पूर्ण, अणु
		.range_min = BD71815_REG_VM_BTMP_MON,
		.range_max = BD71815_REG_VM_BTMP_MON,
	पूर्ण, अणु
		.range_min = BD71815_REG_INT_STAT,
		.range_max = BD71815_REG_INT_UPDATE,
	पूर्ण, अणु
		.range_min = BD71815_REG_VM_VSYS_U,
		.range_max = BD71815_REG_REX_CTRL_1,
	पूर्ण, अणु
		.range_min = BD71815_REG_FULL_CCNTD_3,
		.range_max = BD71815_REG_CCNTD_CHG_2,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_range bd71828_अस्थिर_ranges[] = अणु
	अणु
		.range_min = BD71828_REG_PS_CTRL_1,
		.range_max = BD71828_REG_PS_CTRL_1,
	पूर्ण, अणु
		.range_min = BD71828_REG_PS_CTRL_3,
		.range_max = BD71828_REG_PS_CTRL_3,
	पूर्ण, अणु
		.range_min = BD71828_REG_RTC_SEC,
		.range_max = BD71828_REG_RTC_YEAR,
	पूर्ण, अणु
		/*
		 * For now make all अक्षरger रेजिस्टरs अस्थिर because many
		 * needs to be and because the अक्षरger block is not that
		 * perक्रमmance critical.
		 */
		.range_min = BD71828_REG_CHG_STATE,
		.range_max = BD71828_REG_CHG_FULL,
	पूर्ण, अणु
		.range_min = BD71828_REG_INT_MAIN,
		.range_max = BD71828_REG_IO_STAT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table bd71815_अस्थिर_regs = अणु
	.yes_ranges = &bd71815_अस्थिर_ranges[0],
	.n_yes_ranges = ARRAY_SIZE(bd71815_अस्थिर_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table bd71828_अस्थिर_regs = अणु
	.yes_ranges = &bd71828_अस्थिर_ranges[0],
	.n_yes_ranges = ARRAY_SIZE(bd71828_अस्थिर_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config bd71815_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.अस्थिर_table = &bd71815_अस्थिर_regs,
	.max_रेजिस्टर = BD71815_MAX_REGISTER - 1,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल स्थिर काष्ठा regmap_config bd71828_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.अस्थिर_table = &bd71828_अस्थिर_regs,
	.max_रेजिस्टर = BD71828_MAX_REGISTER,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

/*
 * Mapping of मुख्य IRQ रेजिस्टर bits to sub-IRQ रेजिस्टर offsets so that we can
 * access corect sub-IRQ रेजिस्टरs based on bits that are set in मुख्य IRQ
 * रेजिस्टर. BD71815 and BD71828 have same sub-रेजिस्टर-block offests.
 */

अटल अचिन्हित पूर्णांक bit0_offsets[] = अणु11पूर्ण;		/* RTC IRQ */
अटल अचिन्हित पूर्णांक bit1_offsets[] = अणु10पूर्ण;		/* TEMP IRQ */
अटल अचिन्हित पूर्णांक bit2_offsets[] = अणु6, 7, 8, 9पूर्ण;	/* BAT MON IRQ */
अटल अचिन्हित पूर्णांक bit3_offsets[] = अणु5पूर्ण;		/* BAT IRQ */
अटल अचिन्हित पूर्णांक bit4_offsets[] = अणु4पूर्ण;		/* CHG IRQ */
अटल अचिन्हित पूर्णांक bit5_offsets[] = अणु3पूर्ण;		/* VSYS IRQ */
अटल अचिन्हित पूर्णांक bit6_offsets[] = अणु1, 2पूर्ण;		/* DCIN IRQ */
अटल अचिन्हित पूर्णांक bit7_offsets[] = अणु0पूर्ण;		/* BUCK IRQ */

अटल काष्ठा regmap_irq_sub_irq_map bd718xx_sub_irq_offsets[] = अणु
	REGMAP_IRQ_MAIN_REG_OFFSET(bit0_offsets),
	REGMAP_IRQ_MAIN_REG_OFFSET(bit1_offsets),
	REGMAP_IRQ_MAIN_REG_OFFSET(bit2_offsets),
	REGMAP_IRQ_MAIN_REG_OFFSET(bit3_offsets),
	REGMAP_IRQ_MAIN_REG_OFFSET(bit4_offsets),
	REGMAP_IRQ_MAIN_REG_OFFSET(bit5_offsets),
	REGMAP_IRQ_MAIN_REG_OFFSET(bit6_offsets),
	REGMAP_IRQ_MAIN_REG_OFFSET(bit7_offsets),
पूर्ण;

अटल स्थिर काष्ठा regmap_irq bd71815_irqs[] = अणु
	REGMAP_IRQ_REG(BD71815_INT_BUCK1_OCP, 0, BD71815_INT_BUCK1_OCP_MASK),
	REGMAP_IRQ_REG(BD71815_INT_BUCK2_OCP, 0, BD71815_INT_BUCK2_OCP_MASK),
	REGMAP_IRQ_REG(BD71815_INT_BUCK3_OCP, 0, BD71815_INT_BUCK3_OCP_MASK),
	REGMAP_IRQ_REG(BD71815_INT_BUCK4_OCP, 0, BD71815_INT_BUCK4_OCP_MASK),
	REGMAP_IRQ_REG(BD71815_INT_BUCK5_OCP, 0, BD71815_INT_BUCK5_OCP_MASK),
	REGMAP_IRQ_REG(BD71815_INT_LED_OVP, 0, BD71815_INT_LED_OVP_MASK),
	REGMAP_IRQ_REG(BD71815_INT_LED_OCP, 0, BD71815_INT_LED_OCP_MASK),
	REGMAP_IRQ_REG(BD71815_INT_LED_SCP, 0, BD71815_INT_LED_SCP_MASK),
	/* DCIN1 पूर्णांकerrupts */
	REGMAP_IRQ_REG(BD71815_INT_DCIN_RMV, 1, BD71815_INT_DCIN_RMV_MASK),
	REGMAP_IRQ_REG(BD71815_INT_CLPS_OUT, 1, BD71815_INT_CLPS_OUT_MASK),
	REGMAP_IRQ_REG(BD71815_INT_CLPS_IN, 1, BD71815_INT_CLPS_IN_MASK),
	REGMAP_IRQ_REG(BD71815_INT_DCIN_OVP_RES, 1, BD71815_INT_DCIN_OVP_RES_MASK),
	REGMAP_IRQ_REG(BD71815_INT_DCIN_OVP_DET, 1, BD71815_INT_DCIN_OVP_DET_MASK),
	/* DCIN2 पूर्णांकerrupts */
	REGMAP_IRQ_REG(BD71815_INT_DCIN_MON_RES, 2, BD71815_INT_DCIN_MON_RES_MASK),
	REGMAP_IRQ_REG(BD71815_INT_DCIN_MON_DET, 2, BD71815_INT_DCIN_MON_DET_MASK),
	REGMAP_IRQ_REG(BD71815_INT_WDOG, 2, BD71815_INT_WDOG_MASK),
	/* Vsys */
	REGMAP_IRQ_REG(BD71815_INT_VSYS_UV_RES, 3, BD71815_INT_VSYS_UV_RES_MASK),
	REGMAP_IRQ_REG(BD71815_INT_VSYS_UV_DET, 3, BD71815_INT_VSYS_UV_DET_MASK),
	REGMAP_IRQ_REG(BD71815_INT_VSYS_LOW_RES, 3, BD71815_INT_VSYS_LOW_RES_MASK),
	REGMAP_IRQ_REG(BD71815_INT_VSYS_LOW_DET, 3, BD71815_INT_VSYS_LOW_DET_MASK),
	REGMAP_IRQ_REG(BD71815_INT_VSYS_MON_RES, 3, BD71815_INT_VSYS_MON_RES_MASK),
	REGMAP_IRQ_REG(BD71815_INT_VSYS_MON_DET, 3, BD71815_INT_VSYS_MON_DET_MASK),
	/* Charger */
	REGMAP_IRQ_REG(BD71815_INT_CHG_WDG_TEMP, 4, BD71815_INT_CHG_WDG_TEMP_MASK),
	REGMAP_IRQ_REG(BD71815_INT_CHG_WDG_TIME, 4, BD71815_INT_CHG_WDG_TIME_MASK),
	REGMAP_IRQ_REG(BD71815_INT_CHG_RECHARGE_RES, 4, BD71815_INT_CHG_RECHARGE_RES_MASK),
	REGMAP_IRQ_REG(BD71815_INT_CHG_RECHARGE_DET, 4, BD71815_INT_CHG_RECHARGE_DET_MASK),
	REGMAP_IRQ_REG(BD71815_INT_CHG_RANGED_TEMP_TRANSITION, 4,
		       BD71815_INT_CHG_RANGED_TEMP_TRANSITION_MASK),
	REGMAP_IRQ_REG(BD71815_INT_CHG_STATE_TRANSITION, 4, BD71815_INT_CHG_STATE_TRANSITION_MASK),
	/* Battery */
	REGMAP_IRQ_REG(BD71815_INT_BAT_TEMP_NORMAL, 5, BD71815_INT_BAT_TEMP_NORMAL_MASK),
	REGMAP_IRQ_REG(BD71815_INT_BAT_TEMP_दुस्फल, 5, BD71815_INT_BAT_TEMP_दुस्फल_MASK),
	REGMAP_IRQ_REG(BD71815_INT_BAT_REMOVED, 5, BD71815_INT_BAT_REMOVED_MASK),
	REGMAP_IRQ_REG(BD71815_INT_BAT_DETECTED, 5, BD71815_INT_BAT_DETECTED_MASK),
	REGMAP_IRQ_REG(BD71815_INT_THERM_REMOVED, 5, BD71815_INT_THERM_REMOVED_MASK),
	REGMAP_IRQ_REG(BD71815_INT_THERM_DETECTED, 5, BD71815_INT_THERM_DETECTED_MASK),
	/* Battery Mon 1 */
	REGMAP_IRQ_REG(BD71815_INT_BAT_DEAD, 6, BD71815_INT_BAT_DEAD_MASK),
	REGMAP_IRQ_REG(BD71815_INT_BAT_SHORTC_RES, 6, BD71815_INT_BAT_SHORTC_RES_MASK),
	REGMAP_IRQ_REG(BD71815_INT_BAT_SHORTC_DET, 6, BD71815_INT_BAT_SHORTC_DET_MASK),
	REGMAP_IRQ_REG(BD71815_INT_BAT_LOW_VOLT_RES, 6, BD71815_INT_BAT_LOW_VOLT_RES_MASK),
	REGMAP_IRQ_REG(BD71815_INT_BAT_LOW_VOLT_DET, 6, BD71815_INT_BAT_LOW_VOLT_DET_MASK),
	REGMAP_IRQ_REG(BD71815_INT_BAT_OVER_VOLT_RES, 6, BD71815_INT_BAT_OVER_VOLT_RES_MASK),
	REGMAP_IRQ_REG(BD71815_INT_BAT_OVER_VOLT_DET, 6, BD71815_INT_BAT_OVER_VOLT_DET_MASK),
	/* Battery Mon 2 */
	REGMAP_IRQ_REG(BD71815_INT_BAT_MON_RES, 7, BD71815_INT_BAT_MON_RES_MASK),
	REGMAP_IRQ_REG(BD71815_INT_BAT_MON_DET, 7, BD71815_INT_BAT_MON_DET_MASK),
	/* Battery Mon 3 (Coulomb counter) */
	REGMAP_IRQ_REG(BD71815_INT_BAT_CC_MON1, 8, BD71815_INT_BAT_CC_MON1_MASK),
	REGMAP_IRQ_REG(BD71815_INT_BAT_CC_MON2, 8, BD71815_INT_BAT_CC_MON2_MASK),
	REGMAP_IRQ_REG(BD71815_INT_BAT_CC_MON3, 8, BD71815_INT_BAT_CC_MON3_MASK),
	/* Battery Mon 4 */
	REGMAP_IRQ_REG(BD71815_INT_BAT_OVER_CURR_1_RES, 9, BD71815_INT_BAT_OVER_CURR_1_RES_MASK),
	REGMAP_IRQ_REG(BD71815_INT_BAT_OVER_CURR_1_DET, 9, BD71815_INT_BAT_OVER_CURR_1_DET_MASK),
	REGMAP_IRQ_REG(BD71815_INT_BAT_OVER_CURR_2_RES, 9, BD71815_INT_BAT_OVER_CURR_2_RES_MASK),
	REGMAP_IRQ_REG(BD71815_INT_BAT_OVER_CURR_2_DET, 9, BD71815_INT_BAT_OVER_CURR_2_DET_MASK),
	REGMAP_IRQ_REG(BD71815_INT_BAT_OVER_CURR_3_RES, 9, BD71815_INT_BAT_OVER_CURR_3_RES_MASK),
	REGMAP_IRQ_REG(BD71815_INT_BAT_OVER_CURR_3_DET, 9, BD71815_INT_BAT_OVER_CURR_3_DET_MASK),
	/* Temperature */
	REGMAP_IRQ_REG(BD71815_INT_TEMP_BAT_LOW_RES, 10, BD71815_INT_TEMP_BAT_LOW_RES_MASK),
	REGMAP_IRQ_REG(BD71815_INT_TEMP_BAT_LOW_DET, 10, BD71815_INT_TEMP_BAT_LOW_DET_MASK),
	REGMAP_IRQ_REG(BD71815_INT_TEMP_BAT_HI_RES, 10, BD71815_INT_TEMP_BAT_HI_RES_MASK),
	REGMAP_IRQ_REG(BD71815_INT_TEMP_BAT_HI_DET, 10, BD71815_INT_TEMP_BAT_HI_DET_MASK),
	REGMAP_IRQ_REG(BD71815_INT_TEMP_CHIP_OVER_125_RES, 10,
		       BD71815_INT_TEMP_CHIP_OVER_125_RES_MASK),
	REGMAP_IRQ_REG(BD71815_INT_TEMP_CHIP_OVER_125_DET, 10,
		       BD71815_INT_TEMP_CHIP_OVER_125_DET_MASK),
	REGMAP_IRQ_REG(BD71815_INT_TEMP_CHIP_OVER_VF_RES, 10,
		       BD71815_INT_TEMP_CHIP_OVER_VF_RES_MASK),
	REGMAP_IRQ_REG(BD71815_INT_TEMP_CHIP_OVER_VF_DET, 10,
		       BD71815_INT_TEMP_CHIP_OVER_VF_DET_MASK),
	/* RTC Alarm */
	REGMAP_IRQ_REG(BD71815_INT_RTC0, 11, BD71815_INT_RTC0_MASK),
	REGMAP_IRQ_REG(BD71815_INT_RTC1, 11, BD71815_INT_RTC1_MASK),
	REGMAP_IRQ_REG(BD71815_INT_RTC2, 11, BD71815_INT_RTC2_MASK),
पूर्ण;

अटल काष्ठा regmap_irq bd71828_irqs[] = अणु
	REGMAP_IRQ_REG(BD71828_INT_BUCK1_OCP, 0, BD71828_INT_BUCK1_OCP_MASK),
	REGMAP_IRQ_REG(BD71828_INT_BUCK2_OCP, 0, BD71828_INT_BUCK2_OCP_MASK),
	REGMAP_IRQ_REG(BD71828_INT_BUCK3_OCP, 0, BD71828_INT_BUCK3_OCP_MASK),
	REGMAP_IRQ_REG(BD71828_INT_BUCK4_OCP, 0, BD71828_INT_BUCK4_OCP_MASK),
	REGMAP_IRQ_REG(BD71828_INT_BUCK5_OCP, 0, BD71828_INT_BUCK5_OCP_MASK),
	REGMAP_IRQ_REG(BD71828_INT_BUCK6_OCP, 0, BD71828_INT_BUCK6_OCP_MASK),
	REGMAP_IRQ_REG(BD71828_INT_BUCK7_OCP, 0, BD71828_INT_BUCK7_OCP_MASK),
	REGMAP_IRQ_REG(BD71828_INT_PGFAULT, 0, BD71828_INT_PGFAULT_MASK),
	/* DCIN1 पूर्णांकerrupts */
	REGMAP_IRQ_REG(BD71828_INT_DCIN_DET, 1, BD71828_INT_DCIN_DET_MASK),
	REGMAP_IRQ_REG(BD71828_INT_DCIN_RMV, 1, BD71828_INT_DCIN_RMV_MASK),
	REGMAP_IRQ_REG(BD71828_INT_CLPS_OUT, 1, BD71828_INT_CLPS_OUT_MASK),
	REGMAP_IRQ_REG(BD71828_INT_CLPS_IN, 1, BD71828_INT_CLPS_IN_MASK),
	/* DCIN2 पूर्णांकerrupts */
	REGMAP_IRQ_REG(BD71828_INT_DCIN_MON_RES, 2, BD71828_INT_DCIN_MON_RES_MASK),
	REGMAP_IRQ_REG(BD71828_INT_DCIN_MON_DET, 2, BD71828_INT_DCIN_MON_DET_MASK),
	REGMAP_IRQ_REG(BD71828_INT_LONGPUSH, 2, BD71828_INT_LONGPUSH_MASK),
	REGMAP_IRQ_REG(BD71828_INT_MIDPUSH, 2, BD71828_INT_MIDPUSH_MASK),
	REGMAP_IRQ_REG(BD71828_INT_SHORTPUSH, 2, BD71828_INT_SHORTPUSH_MASK),
	REGMAP_IRQ_REG(BD71828_INT_PUSH, 2, BD71828_INT_PUSH_MASK),
	REGMAP_IRQ_REG(BD71828_INT_WDOG, 2, BD71828_INT_WDOG_MASK),
	REGMAP_IRQ_REG(BD71828_INT_SWRESET, 2, BD71828_INT_SWRESET_MASK),
	/* Vsys */
	REGMAP_IRQ_REG(BD71828_INT_VSYS_UV_RES, 3, BD71828_INT_VSYS_UV_RES_MASK),
	REGMAP_IRQ_REG(BD71828_INT_VSYS_UV_DET, 3, BD71828_INT_VSYS_UV_DET_MASK),
	REGMAP_IRQ_REG(BD71828_INT_VSYS_LOW_RES, 3, BD71828_INT_VSYS_LOW_RES_MASK),
	REGMAP_IRQ_REG(BD71828_INT_VSYS_LOW_DET, 3, BD71828_INT_VSYS_LOW_DET_MASK),
	REGMAP_IRQ_REG(BD71828_INT_VSYS_HALL_IN, 3, BD71828_INT_VSYS_HALL_IN_MASK),
	REGMAP_IRQ_REG(BD71828_INT_VSYS_HALL_TOGGLE, 3, BD71828_INT_VSYS_HALL_TOGGLE_MASK),
	REGMAP_IRQ_REG(BD71828_INT_VSYS_MON_RES, 3, BD71828_INT_VSYS_MON_RES_MASK),
	REGMAP_IRQ_REG(BD71828_INT_VSYS_MON_DET, 3, BD71828_INT_VSYS_MON_DET_MASK),
	/* Charger */
	REGMAP_IRQ_REG(BD71828_INT_CHG_DCIN_ILIM, 4, BD71828_INT_CHG_DCIN_ILIM_MASK),
	REGMAP_IRQ_REG(BD71828_INT_CHG_TOPOFF_TO_DONE, 4, BD71828_INT_CHG_TOPOFF_TO_DONE_MASK),
	REGMAP_IRQ_REG(BD71828_INT_CHG_WDG_TEMP, 4, BD71828_INT_CHG_WDG_TEMP_MASK),
	REGMAP_IRQ_REG(BD71828_INT_CHG_WDG_TIME, 4, BD71828_INT_CHG_WDG_TIME_MASK),
	REGMAP_IRQ_REG(BD71828_INT_CHG_RECHARGE_RES, 4, BD71828_INT_CHG_RECHARGE_RES_MASK),
	REGMAP_IRQ_REG(BD71828_INT_CHG_RECHARGE_DET, 4, BD71828_INT_CHG_RECHARGE_DET_MASK),
	REGMAP_IRQ_REG(BD71828_INT_CHG_RANGED_TEMP_TRANSITION, 4,
		       BD71828_INT_CHG_RANGED_TEMP_TRANSITION_MASK),
	REGMAP_IRQ_REG(BD71828_INT_CHG_STATE_TRANSITION, 4, BD71828_INT_CHG_STATE_TRANSITION_MASK),
	/* Battery */
	REGMAP_IRQ_REG(BD71828_INT_BAT_TEMP_NORMAL, 5, BD71828_INT_BAT_TEMP_NORMAL_MASK),
	REGMAP_IRQ_REG(BD71828_INT_BAT_TEMP_दुस्फल, 5, BD71828_INT_BAT_TEMP_दुस्फल_MASK),
	REGMAP_IRQ_REG(BD71828_INT_BAT_TEMP_WARN, 5, BD71828_INT_BAT_TEMP_WARN_MASK),
	REGMAP_IRQ_REG(BD71828_INT_BAT_REMOVED, 5, BD71828_INT_BAT_REMOVED_MASK),
	REGMAP_IRQ_REG(BD71828_INT_BAT_DETECTED, 5, BD71828_INT_BAT_DETECTED_MASK),
	REGMAP_IRQ_REG(BD71828_INT_THERM_REMOVED, 5, BD71828_INT_THERM_REMOVED_MASK),
	REGMAP_IRQ_REG(BD71828_INT_THERM_DETECTED, 5, BD71828_INT_THERM_DETECTED_MASK),
	/* Battery Mon 1 */
	REGMAP_IRQ_REG(BD71828_INT_BAT_DEAD, 6, BD71828_INT_BAT_DEAD_MASK),
	REGMAP_IRQ_REG(BD71828_INT_BAT_SHORTC_RES, 6, BD71828_INT_BAT_SHORTC_RES_MASK),
	REGMAP_IRQ_REG(BD71828_INT_BAT_SHORTC_DET, 6, BD71828_INT_BAT_SHORTC_DET_MASK),
	REGMAP_IRQ_REG(BD71828_INT_BAT_LOW_VOLT_RES, 6, BD71828_INT_BAT_LOW_VOLT_RES_MASK),
	REGMAP_IRQ_REG(BD71828_INT_BAT_LOW_VOLT_DET, 6, BD71828_INT_BAT_LOW_VOLT_DET_MASK),
	REGMAP_IRQ_REG(BD71828_INT_BAT_OVER_VOLT_RES, 6, BD71828_INT_BAT_OVER_VOLT_RES_MASK),
	REGMAP_IRQ_REG(BD71828_INT_BAT_OVER_VOLT_DET, 6, BD71828_INT_BAT_OVER_VOLT_DET_MASK),
	/* Battery Mon 2 */
	REGMAP_IRQ_REG(BD71828_INT_BAT_MON_RES, 7, BD71828_INT_BAT_MON_RES_MASK),
	REGMAP_IRQ_REG(BD71828_INT_BAT_MON_DET, 7, BD71828_INT_BAT_MON_DET_MASK),
	/* Battery Mon 3 (Coulomb counter) */
	REGMAP_IRQ_REG(BD71828_INT_BAT_CC_MON1, 8, BD71828_INT_BAT_CC_MON1_MASK),
	REGMAP_IRQ_REG(BD71828_INT_BAT_CC_MON2, 8, BD71828_INT_BAT_CC_MON2_MASK),
	REGMAP_IRQ_REG(BD71828_INT_BAT_CC_MON3, 8, BD71828_INT_BAT_CC_MON3_MASK),
	/* Battery Mon 4 */
	REGMAP_IRQ_REG(BD71828_INT_BAT_OVER_CURR_1_RES, 9, BD71828_INT_BAT_OVER_CURR_1_RES_MASK),
	REGMAP_IRQ_REG(BD71828_INT_BAT_OVER_CURR_1_DET, 9, BD71828_INT_BAT_OVER_CURR_1_DET_MASK),
	REGMAP_IRQ_REG(BD71828_INT_BAT_OVER_CURR_2_RES, 9, BD71828_INT_BAT_OVER_CURR_2_RES_MASK),
	REGMAP_IRQ_REG(BD71828_INT_BAT_OVER_CURR_2_DET, 9, BD71828_INT_BAT_OVER_CURR_2_DET_MASK),
	REGMAP_IRQ_REG(BD71828_INT_BAT_OVER_CURR_3_RES, 9, BD71828_INT_BAT_OVER_CURR_3_RES_MASK),
	REGMAP_IRQ_REG(BD71828_INT_BAT_OVER_CURR_3_DET, 9, BD71828_INT_BAT_OVER_CURR_3_DET_MASK),
	/* Temperature */
	REGMAP_IRQ_REG(BD71828_INT_TEMP_BAT_LOW_RES, 10, BD71828_INT_TEMP_BAT_LOW_RES_MASK),
	REGMAP_IRQ_REG(BD71828_INT_TEMP_BAT_LOW_DET, 10, BD71828_INT_TEMP_BAT_LOW_DET_MASK),
	REGMAP_IRQ_REG(BD71828_INT_TEMP_BAT_HI_RES, 10, BD71828_INT_TEMP_BAT_HI_RES_MASK),
	REGMAP_IRQ_REG(BD71828_INT_TEMP_BAT_HI_DET, 10, BD71828_INT_TEMP_BAT_HI_DET_MASK),
	REGMAP_IRQ_REG(BD71828_INT_TEMP_CHIP_OVER_125_RES, 10,
		       BD71828_INT_TEMP_CHIP_OVER_125_RES_MASK),
	REGMAP_IRQ_REG(BD71828_INT_TEMP_CHIP_OVER_125_DET, 10,
		       BD71828_INT_TEMP_CHIP_OVER_125_DET_MASK),
	REGMAP_IRQ_REG(BD71828_INT_TEMP_CHIP_OVER_VF_DET, 10,
		       BD71828_INT_TEMP_CHIP_OVER_VF_DET_MASK),
	REGMAP_IRQ_REG(BD71828_INT_TEMP_CHIP_OVER_VF_RES, 10,
		       BD71828_INT_TEMP_CHIP_OVER_VF_RES_MASK),
	/* RTC Alarm */
	REGMAP_IRQ_REG(BD71828_INT_RTC0, 11, BD71828_INT_RTC0_MASK),
	REGMAP_IRQ_REG(BD71828_INT_RTC1, 11, BD71828_INT_RTC1_MASK),
	REGMAP_IRQ_REG(BD71828_INT_RTC2, 11, BD71828_INT_RTC2_MASK),
पूर्ण;

अटल काष्ठा regmap_irq_chip bd71828_irq_chip = अणु
	.name = "bd71828_irq",
	.मुख्य_status = BD71828_REG_INT_MAIN,
	.irqs = &bd71828_irqs[0],
	.num_irqs = ARRAY_SIZE(bd71828_irqs),
	.status_base = BD71828_REG_INT_BUCK,
	.mask_base = BD71828_REG_INT_MASK_BUCK,
	.ack_base = BD71828_REG_INT_BUCK,
	.mask_invert = true,
	.init_ack_masked = true,
	.num_regs = 12,
	.num_मुख्य_regs = 1,
	.sub_reg_offsets = &bd718xx_sub_irq_offsets[0],
	.num_मुख्य_status_bits = 8,
	.irq_reg_stride = 1,
पूर्ण;

अटल काष्ठा regmap_irq_chip bd71815_irq_chip = अणु
	.name = "bd71815_irq",
	.मुख्य_status = BD71815_REG_INT_STAT,
	.irqs = &bd71815_irqs[0],
	.num_irqs = ARRAY_SIZE(bd71815_irqs),
	.status_base = BD71815_REG_INT_STAT_01,
	.mask_base = BD71815_REG_INT_EN_01,
	.ack_base = BD71815_REG_INT_STAT_01,
	.mask_invert = true,
	.init_ack_masked = true,
	.num_regs = 12,
	.num_मुख्य_regs = 1,
	.sub_reg_offsets = &bd718xx_sub_irq_offsets[0],
	.num_मुख्य_status_bits = 8,
	.irq_reg_stride = 1,
पूर्ण;

अटल पूर्णांक set_clk_mode(काष्ठा device *dev, काष्ठा regmap *regmap,
			पूर्णांक clkmode_reg)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक खोलो_drain;

	ret = of_property_पढ़ो_u32(dev->of_node, "rohm,clkout-open-drain", &खोलो_drain);
	अगर (ret) अणु
		अगर (ret == -EINVAL)
			वापस 0;
		वापस ret;
	पूर्ण
	अगर (खोलो_drain > 1) अणु
		dev_err(dev, "bad clk32kout mode configuration");
		वापस -EINVAL;
	पूर्ण

	अगर (खोलो_drain)
		वापस regmap_update_bits(regmap, clkmode_reg, OUT32K_MODE,
					  OUT32K_MODE_OPEN_DRAIN);

	वापस regmap_update_bits(regmap, clkmode_reg, OUT32K_MODE,
				  OUT32K_MODE_CMOS);
पूर्ण

अटल पूर्णांक bd71828_i2c_probe(काष्ठा i2c_client *i2c)
अणु
	काष्ठा regmap_irq_chip_data *irq_data;
	पूर्णांक ret;
	काष्ठा regmap *regmap;
	स्थिर काष्ठा regmap_config *regmap_config;
	काष्ठा regmap_irq_chip *irqchip;
	अचिन्हित पूर्णांक chip_type;
	काष्ठा mfd_cell *mfd;
	पूर्णांक cells;
	पूर्णांक button_irq;
	पूर्णांक clkmode_reg;

	अगर (!i2c->irq) अणु
		dev_err(&i2c->dev, "No IRQ configured\n");
		वापस -EINVAL;
	पूर्ण

	chip_type = (अचिन्हित पूर्णांक)(uपूर्णांकptr_t)
		    of_device_get_match_data(&i2c->dev);
	चयन (chip_type) अणु
	हाल ROHM_CHIP_TYPE_BD71828:
		mfd = bd71828_mfd_cells;
		cells = ARRAY_SIZE(bd71828_mfd_cells);
		regmap_config = &bd71828_regmap;
		irqchip = &bd71828_irq_chip;
		clkmode_reg = BD71828_REG_OUT32K;
		button_irq = BD71828_INT_SHORTPUSH;
		अवरोध;
	हाल ROHM_CHIP_TYPE_BD71815:
		mfd = bd71815_mfd_cells;
		cells = ARRAY_SIZE(bd71815_mfd_cells);
		regmap_config = &bd71815_regmap;
		irqchip = &bd71815_irq_chip;
		clkmode_reg = BD71815_REG_OUT32K;
		/*
		 * If BD71817 support is needed we should be able to handle it
		 * with proper DT configs + BD71815 drivers + घातer-button.
		 * BD71815 data-sheet करोes not list the घातer-button IRQ so we
		 * करोn't use it.
		 */
		button_irq = 0;
		अवरोध;
	शेष:
		dev_err(&i2c->dev, "Unknown device type");
		वापस -EINVAL;
	पूर्ण

	regmap = devm_regmap_init_i2c(i2c, regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&i2c->dev, "Failed to initialize Regmap\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	ret = devm_regmap_add_irq_chip(&i2c->dev, regmap, i2c->irq,
				       IRQF_ONESHOT, 0, irqchip, &irq_data);
	अगर (ret) अणु
		dev_err(&i2c->dev, "Failed to add IRQ chip\n");
		वापस ret;
	पूर्ण

	dev_dbg(&i2c->dev, "Registered %d IRQs for chip\n",
		irqchip->num_irqs);

	अगर (button_irq) अणु
		ret = regmap_irq_get_virq(irq_data, button_irq);
		अगर (ret < 0) अणु
			dev_err(&i2c->dev, "Failed to get the power-key IRQ\n");
			वापस ret;
		पूर्ण

		button.irq = ret;
	पूर्ण

	ret = set_clk_mode(&i2c->dev, regmap, clkmode_reg);
	अगर (ret)
		वापस ret;

	ret = devm_mfd_add_devices(&i2c->dev, PLATFORM_DEVID_AUTO, mfd, cells,
				   शून्य, 0, regmap_irq_get_करोमुख्य(irq_data));
	अगर (ret)
		dev_err(&i2c->dev, "Failed to create subdevices\n");

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id bd71828_of_match[] = अणु
	अणु
		.compatible = "rohm,bd71828",
		.data = (व्योम *)ROHM_CHIP_TYPE_BD71828,
	पूर्ण, अणु
		.compatible = "rohm,bd71815",
		.data = (व्योम *)ROHM_CHIP_TYPE_BD71815,
	 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bd71828_of_match);

अटल काष्ठा i2c_driver bd71828_drv = अणु
	.driver = अणु
		.name = "rohm-bd71828",
		.of_match_table = bd71828_of_match,
	पूर्ण,
	.probe_new = &bd71828_i2c_probe,
पूर्ण;
module_i2c_driver(bd71828_drv);

MODULE_AUTHOR("Matti Vaittinen <matti.vaittinen@fi.rohmeurope.com>");
MODULE_DESCRIPTION("ROHM BD71828 Power Management IC driver");
MODULE_LICENSE("GPL");
