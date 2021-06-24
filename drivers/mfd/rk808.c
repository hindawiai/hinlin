<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MFD core driver क्रम Rockchip RK808/RK818
 *
 * Copyright (c) 2014, Fuzhou Rockchip Electronics Co., Ltd
 *
 * Author: Chris Zhong <zyw@rock-chips.com>
 * Author: Zhang Qing <zhangqing@rock-chips.com>
 *
 * Copyright (C) 2016 PHYTEC Messtechnik GmbH
 *
 * Author: Wadim Egorov <w.egorov@phytec.de>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/rk808.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>

काष्ठा rk808_reg_data अणु
	पूर्णांक addr;
	पूर्णांक mask;
	पूर्णांक value;
पूर्ण;

अटल bool rk808_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	/*
	 * Notes:
	 * - Technically the ROUND_30s bit makes RTC_CTRL_REG अस्थिर, but
	 *   we करोn't use that feature.  It's better to cache.
	 * - It's unlikely we care that RK808_DEVCTRL_REG is अस्थिर since
	 *   bits are cleared in हाल when we shutoff anyway, but better safe.
	 */

	चयन (reg) अणु
	हाल RK808_SECONDS_REG ... RK808_WEEKS_REG:
	हाल RK808_RTC_STATUS_REG:
	हाल RK808_VB_MON_REG:
	हाल RK808_THERMAL_REG:
	हाल RK808_DCDC_UV_STS_REG:
	हाल RK808_LDO_UV_STS_REG:
	हाल RK808_DCDC_PG_REG:
	हाल RK808_LDO_PG_REG:
	हाल RK808_DEVCTRL_REG:
	हाल RK808_INT_STS_REG1:
	हाल RK808_INT_STS_REG2:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool rk817_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	/*
	 * Notes:
	 * - Technically the ROUND_30s bit makes RTC_CTRL_REG अस्थिर, but
	 *   we करोn't use that feature.  It's better to cache.
	 */

	चयन (reg) अणु
	हाल RK817_SECONDS_REG ... RK817_WEEKS_REG:
	हाल RK817_RTC_STATUS_REG:
	हाल RK817_INT_STS_REG0:
	हाल RK817_INT_STS_REG1:
	हाल RK817_INT_STS_REG2:
	हाल RK817_SYS_STS:
		वापस true;
	पूर्ण

	वापस true;
पूर्ण

अटल स्थिर काष्ठा regmap_config rk818_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = RK818_USB_CTRL_REG,
	.cache_type = REGCACHE_RBTREE,
	.अस्थिर_reg = rk808_is_अस्थिर_reg,
पूर्ण;

अटल स्थिर काष्ठा regmap_config rk805_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = RK805_OFF_SOURCE_REG,
	.cache_type = REGCACHE_RBTREE,
	.अस्थिर_reg = rk808_is_अस्थिर_reg,
पूर्ण;

अटल स्थिर काष्ठा regmap_config rk808_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = RK808_IO_POL_REG,
	.cache_type = REGCACHE_RBTREE,
	.अस्थिर_reg = rk808_is_अस्थिर_reg,
पूर्ण;

अटल स्थिर काष्ठा regmap_config rk817_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = RK817_GPIO_INT_CFG,
	.cache_type = REGCACHE_NONE,
	.अस्थिर_reg = rk817_is_अस्थिर_reg,
पूर्ण;

अटल स्थिर काष्ठा resource rtc_resources[] = अणु
	DEFINE_RES_IRQ(RK808_IRQ_RTC_ALARM),
पूर्ण;

अटल स्थिर काष्ठा resource rk817_rtc_resources[] = अणु
	DEFINE_RES_IRQ(RK817_IRQ_RTC_ALARM),
पूर्ण;

अटल स्थिर काष्ठा resource rk805_key_resources[] = अणु
	DEFINE_RES_IRQ(RK805_IRQ_PWRON_RISE),
	DEFINE_RES_IRQ(RK805_IRQ_PWRON_FALL),
पूर्ण;

अटल स्थिर काष्ठा resource rk817_pwrkey_resources[] = अणु
	DEFINE_RES_IRQ(RK817_IRQ_PWRON_RISE),
	DEFINE_RES_IRQ(RK817_IRQ_PWRON_FALL),
पूर्ण;

अटल स्थिर काष्ठा mfd_cell rk805s[] = अणु
	अणु .name = "rk808-clkout", पूर्ण,
	अणु .name = "rk808-regulator", पूर्ण,
	अणु .name = "rk805-pinctrl", पूर्ण,
	अणु
		.name = "rk808-rtc",
		.num_resources = ARRAY_SIZE(rtc_resources),
		.resources = &rtc_resources[0],
	पूर्ण,
	अणु	.name = "rk805-pwrkey",
		.num_resources = ARRAY_SIZE(rk805_key_resources),
		.resources = &rk805_key_resources[0],
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell rk808s[] = अणु
	अणु .name = "rk808-clkout", पूर्ण,
	अणु .name = "rk808-regulator", पूर्ण,
	अणु
		.name = "rk808-rtc",
		.num_resources = ARRAY_SIZE(rtc_resources),
		.resources = rtc_resources,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell rk817s[] = अणु
	अणु .name = "rk808-clkout",पूर्ण,
	अणु .name = "rk808-regulator",पूर्ण,
	अणु
		.name = "rk805-pwrkey",
		.num_resources = ARRAY_SIZE(rk817_pwrkey_resources),
		.resources = &rk817_pwrkey_resources[0],
	पूर्ण,
	अणु
		.name = "rk808-rtc",
		.num_resources = ARRAY_SIZE(rk817_rtc_resources),
		.resources = &rk817_rtc_resources[0],
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell rk818s[] = अणु
	अणु .name = "rk808-clkout", पूर्ण,
	अणु .name = "rk808-regulator", पूर्ण,
	अणु
		.name = "rk808-rtc",
		.num_resources = ARRAY_SIZE(rtc_resources),
		.resources = rtc_resources,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rk808_reg_data rk805_pre_init_reg[] = अणु
	अणुRK805_BUCK1_CONFIG_REG, RK805_BUCK1_2_ILMAX_MASK,
				 RK805_BUCK1_2_ILMAX_4000MAपूर्ण,
	अणुRK805_BUCK2_CONFIG_REG, RK805_BUCK1_2_ILMAX_MASK,
				 RK805_BUCK1_2_ILMAX_4000MAपूर्ण,
	अणुRK805_BUCK3_CONFIG_REG, RK805_BUCK3_4_ILMAX_MASK,
				 RK805_BUCK3_ILMAX_3000MAपूर्ण,
	अणुRK805_BUCK4_CONFIG_REG, RK805_BUCK3_4_ILMAX_MASK,
				 RK805_BUCK4_ILMAX_3500MAपूर्ण,
	अणुRK805_BUCK4_CONFIG_REG, BUCK_ILMIN_MASK, BUCK_ILMIN_400MAपूर्ण,
	अणुRK805_THERMAL_REG, TEMP_HOTDIE_MSK, TEMP115Cपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rk808_reg_data rk808_pre_init_reg[] = अणु
	अणु RK808_BUCK3_CONFIG_REG, BUCK_ILMIN_MASK,  BUCK_ILMIN_150MA पूर्ण,
	अणु RK808_BUCK4_CONFIG_REG, BUCK_ILMIN_MASK,  BUCK_ILMIN_200MA पूर्ण,
	अणु RK808_BOOST_CONFIG_REG, BOOST_ILMIN_MASK, BOOST_ILMIN_100MA पूर्ण,
	अणु RK808_BUCK1_CONFIG_REG, BUCK1_RATE_MASK,  BUCK_ILMIN_200MA पूर्ण,
	अणु RK808_BUCK2_CONFIG_REG, BUCK2_RATE_MASK,  BUCK_ILMIN_200MA पूर्ण,
	अणु RK808_DCDC_UV_ACT_REG,  BUCK_UV_ACT_MASK, BUCK_UV_ACT_DISABLEपूर्ण,
	अणु RK808_VB_MON_REG,       MASK_ALL,         VB_LO_ACT |
						    VB_LO_SEL_3500MV पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rk808_reg_data rk817_pre_init_reg[] = अणु
	अणुRK817_RTC_CTRL_REG, RTC_STOP, RTC_STOPपूर्ण,
	अणुRK817_GPIO_INT_CFG, RK817_INT_POL_MSK, RK817_INT_POL_Lपूर्ण,
	अणुRK817_SYS_CFG(1), RK817_HOTDIE_TEMP_MSK | RK817_TSD_TEMP_MSK,
					   RK817_HOTDIE_105 | RK817_TSD_140पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rk808_reg_data rk818_pre_init_reg[] = अणु
	/* improve efficiency */
	अणु RK818_BUCK2_CONFIG_REG, BUCK2_RATE_MASK,  BUCK_ILMIN_250MA पूर्ण,
	अणु RK818_BUCK4_CONFIG_REG, BUCK_ILMIN_MASK,  BUCK_ILMIN_250MA पूर्ण,
	अणु RK818_BOOST_CONFIG_REG, BOOST_ILMIN_MASK, BOOST_ILMIN_100MA पूर्ण,
	अणु RK818_USB_CTRL_REG,	  RK818_USB_ILIM_SEL_MASK,
						    RK818_USB_ILMIN_2000MA पूर्ण,
	/* बंद अक्षरger when usb lower then 3.4V */
	अणु RK818_USB_CTRL_REG,	  RK818_USB_CHG_SD_VSEL_MASK,
						    (0x7 << 4) पूर्ण,
	/* no action when vref */
	अणु RK818_H5V_EN_REG,	  BIT(1),	    RK818_REF_RDY_CTRL पूर्ण,
	/* enable HDMI 5V */
	अणु RK818_H5V_EN_REG,	  BIT(0),	    RK818_H5V_EN पूर्ण,
	अणु RK808_VB_MON_REG,	  MASK_ALL,	    VB_LO_ACT |
						    VB_LO_SEL_3500MV पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq rk805_irqs[] = अणु
	[RK805_IRQ_PWRON_RISE] = अणु
		.mask = RK805_IRQ_PWRON_RISE_MSK,
		.reg_offset = 0,
	पूर्ण,
	[RK805_IRQ_VB_LOW] = अणु
		.mask = RK805_IRQ_VB_LOW_MSK,
		.reg_offset = 0,
	पूर्ण,
	[RK805_IRQ_PWRON] = अणु
		.mask = RK805_IRQ_PWRON_MSK,
		.reg_offset = 0,
	पूर्ण,
	[RK805_IRQ_PWRON_LP] = अणु
		.mask = RK805_IRQ_PWRON_LP_MSK,
		.reg_offset = 0,
	पूर्ण,
	[RK805_IRQ_HOTDIE] = अणु
		.mask = RK805_IRQ_HOTDIE_MSK,
		.reg_offset = 0,
	पूर्ण,
	[RK805_IRQ_RTC_ALARM] = अणु
		.mask = RK805_IRQ_RTC_ALARM_MSK,
		.reg_offset = 0,
	पूर्ण,
	[RK805_IRQ_RTC_PERIOD] = अणु
		.mask = RK805_IRQ_RTC_PERIOD_MSK,
		.reg_offset = 0,
	पूर्ण,
	[RK805_IRQ_PWRON_FALL] = अणु
		.mask = RK805_IRQ_PWRON_FALL_MSK,
		.reg_offset = 0,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq rk808_irqs[] = अणु
	/* INT_STS */
	[RK808_IRQ_VOUT_LO] = अणु
		.mask = RK808_IRQ_VOUT_LO_MSK,
		.reg_offset = 0,
	पूर्ण,
	[RK808_IRQ_VB_LO] = अणु
		.mask = RK808_IRQ_VB_LO_MSK,
		.reg_offset = 0,
	पूर्ण,
	[RK808_IRQ_PWRON] = अणु
		.mask = RK808_IRQ_PWRON_MSK,
		.reg_offset = 0,
	पूर्ण,
	[RK808_IRQ_PWRON_LP] = अणु
		.mask = RK808_IRQ_PWRON_LP_MSK,
		.reg_offset = 0,
	पूर्ण,
	[RK808_IRQ_HOTDIE] = अणु
		.mask = RK808_IRQ_HOTDIE_MSK,
		.reg_offset = 0,
	पूर्ण,
	[RK808_IRQ_RTC_ALARM] = अणु
		.mask = RK808_IRQ_RTC_ALARM_MSK,
		.reg_offset = 0,
	पूर्ण,
	[RK808_IRQ_RTC_PERIOD] = अणु
		.mask = RK808_IRQ_RTC_PERIOD_MSK,
		.reg_offset = 0,
	पूर्ण,

	/* INT_STS2 */
	[RK808_IRQ_PLUG_IN_INT] = अणु
		.mask = RK808_IRQ_PLUG_IN_INT_MSK,
		.reg_offset = 1,
	पूर्ण,
	[RK808_IRQ_PLUG_OUT_INT] = अणु
		.mask = RK808_IRQ_PLUG_OUT_INT_MSK,
		.reg_offset = 1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq rk818_irqs[] = अणु
	/* INT_STS */
	[RK818_IRQ_VOUT_LO] = अणु
		.mask = RK818_IRQ_VOUT_LO_MSK,
		.reg_offset = 0,
	पूर्ण,
	[RK818_IRQ_VB_LO] = अणु
		.mask = RK818_IRQ_VB_LO_MSK,
		.reg_offset = 0,
	पूर्ण,
	[RK818_IRQ_PWRON] = अणु
		.mask = RK818_IRQ_PWRON_MSK,
		.reg_offset = 0,
	पूर्ण,
	[RK818_IRQ_PWRON_LP] = अणु
		.mask = RK818_IRQ_PWRON_LP_MSK,
		.reg_offset = 0,
	पूर्ण,
	[RK818_IRQ_HOTDIE] = अणु
		.mask = RK818_IRQ_HOTDIE_MSK,
		.reg_offset = 0,
	पूर्ण,
	[RK818_IRQ_RTC_ALARM] = अणु
		.mask = RK818_IRQ_RTC_ALARM_MSK,
		.reg_offset = 0,
	पूर्ण,
	[RK818_IRQ_RTC_PERIOD] = अणु
		.mask = RK818_IRQ_RTC_PERIOD_MSK,
		.reg_offset = 0,
	पूर्ण,
	[RK818_IRQ_USB_OV] = अणु
		.mask = RK818_IRQ_USB_OV_MSK,
		.reg_offset = 0,
	पूर्ण,

	/* INT_STS2 */
	[RK818_IRQ_PLUG_IN] = अणु
		.mask = RK818_IRQ_PLUG_IN_MSK,
		.reg_offset = 1,
	पूर्ण,
	[RK818_IRQ_PLUG_OUT] = अणु
		.mask = RK818_IRQ_PLUG_OUT_MSK,
		.reg_offset = 1,
	पूर्ण,
	[RK818_IRQ_CHG_OK] = अणु
		.mask = RK818_IRQ_CHG_OK_MSK,
		.reg_offset = 1,
	पूर्ण,
	[RK818_IRQ_CHG_TE] = अणु
		.mask = RK818_IRQ_CHG_TE_MSK,
		.reg_offset = 1,
	पूर्ण,
	[RK818_IRQ_CHG_TS1] = अणु
		.mask = RK818_IRQ_CHG_TS1_MSK,
		.reg_offset = 1,
	पूर्ण,
	[RK818_IRQ_TS2] = अणु
		.mask = RK818_IRQ_TS2_MSK,
		.reg_offset = 1,
	पूर्ण,
	[RK818_IRQ_CHG_CVTLIM] = अणु
		.mask = RK818_IRQ_CHG_CVTLIM_MSK,
		.reg_offset = 1,
	पूर्ण,
	[RK818_IRQ_DISCHG_ILIM] = अणु
		.mask = RK818_IRQ_DISCHG_ILIM_MSK,
		.reg_offset = 1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq rk817_irqs[RK817_IRQ_END] = अणु
	REGMAP_IRQ_REG_LINE(0, 8),
	REGMAP_IRQ_REG_LINE(1, 8),
	REGMAP_IRQ_REG_LINE(2, 8),
	REGMAP_IRQ_REG_LINE(3, 8),
	REGMAP_IRQ_REG_LINE(4, 8),
	REGMAP_IRQ_REG_LINE(5, 8),
	REGMAP_IRQ_REG_LINE(6, 8),
	REGMAP_IRQ_REG_LINE(7, 8),
	REGMAP_IRQ_REG_LINE(8, 8),
	REGMAP_IRQ_REG_LINE(9, 8),
	REGMAP_IRQ_REG_LINE(10, 8),
	REGMAP_IRQ_REG_LINE(11, 8),
	REGMAP_IRQ_REG_LINE(12, 8),
	REGMAP_IRQ_REG_LINE(13, 8),
	REGMAP_IRQ_REG_LINE(14, 8),
	REGMAP_IRQ_REG_LINE(15, 8),
	REGMAP_IRQ_REG_LINE(16, 8),
	REGMAP_IRQ_REG_LINE(17, 8),
	REGMAP_IRQ_REG_LINE(18, 8),
	REGMAP_IRQ_REG_LINE(19, 8),
	REGMAP_IRQ_REG_LINE(20, 8),
	REGMAP_IRQ_REG_LINE(21, 8),
	REGMAP_IRQ_REG_LINE(22, 8),
	REGMAP_IRQ_REG_LINE(23, 8)
पूर्ण;

अटल काष्ठा regmap_irq_chip rk805_irq_chip = अणु
	.name = "rk805",
	.irqs = rk805_irqs,
	.num_irqs = ARRAY_SIZE(rk805_irqs),
	.num_regs = 1,
	.status_base = RK805_INT_STS_REG,
	.mask_base = RK805_INT_STS_MSK_REG,
	.ack_base = RK805_INT_STS_REG,
	.init_ack_masked = true,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip rk808_irq_chip = अणु
	.name = "rk808",
	.irqs = rk808_irqs,
	.num_irqs = ARRAY_SIZE(rk808_irqs),
	.num_regs = 2,
	.irq_reg_stride = 2,
	.status_base = RK808_INT_STS_REG1,
	.mask_base = RK808_INT_STS_MSK_REG1,
	.ack_base = RK808_INT_STS_REG1,
	.init_ack_masked = true,
पूर्ण;

अटल काष्ठा regmap_irq_chip rk817_irq_chip = अणु
	.name = "rk817",
	.irqs = rk817_irqs,
	.num_irqs = ARRAY_SIZE(rk817_irqs),
	.num_regs = 3,
	.irq_reg_stride = 2,
	.status_base = RK817_INT_STS_REG0,
	.mask_base = RK817_INT_STS_MSK_REG0,
	.ack_base = RK817_INT_STS_REG0,
	.init_ack_masked = true,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip rk818_irq_chip = अणु
	.name = "rk818",
	.irqs = rk818_irqs,
	.num_irqs = ARRAY_SIZE(rk818_irqs),
	.num_regs = 2,
	.irq_reg_stride = 2,
	.status_base = RK818_INT_STS_REG1,
	.mask_base = RK818_INT_STS_MSK_REG1,
	.ack_base = RK818_INT_STS_REG1,
	.init_ack_masked = true,
पूर्ण;

अटल काष्ठा i2c_client *rk808_i2c_client;

अटल व्योम rk808_pm_घातer_off(व्योम)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक reg, bit;
	काष्ठा rk808 *rk808 = i2c_get_clientdata(rk808_i2c_client);

	चयन (rk808->variant) अणु
	हाल RK805_ID:
		reg = RK805_DEV_CTRL_REG;
		bit = DEV_OFF;
		अवरोध;
	हाल RK808_ID:
		reg = RK808_DEVCTRL_REG,
		bit = DEV_OFF_RST;
		अवरोध;
	हाल RK818_ID:
		reg = RK818_DEVCTRL_REG;
		bit = DEV_OFF;
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	ret = regmap_update_bits(rk808->regmap, reg, bit, bit);
	अगर (ret)
		dev_err(&rk808_i2c_client->dev, "Failed to shutdown device!\n");
पूर्ण

अटल व्योम rk8xx_shutकरोwn(काष्ठा i2c_client *client)
अणु
	काष्ठा rk808 *rk808 = i2c_get_clientdata(client);
	पूर्णांक ret;

	चयन (rk808->variant) अणु
	हाल RK805_ID:
		ret = regmap_update_bits(rk808->regmap,
					 RK805_GPIO_IO_POL_REG,
					 SLP_SD_MSK,
					 SHUTDOWN_FUN);
		अवरोध;
	हाल RK809_ID:
	हाल RK817_ID:
		ret = regmap_update_bits(rk808->regmap,
					 RK817_SYS_CFG(3),
					 RK817_SLPPIN_FUNC_MSK,
					 SLPPIN_DN_FUN);
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	अगर (ret)
		dev_warn(&client->dev,
			 "Cannot switch to power down function\n");
पूर्ण

अटल स्थिर काष्ठा of_device_id rk808_of_match[] = अणु
	अणु .compatible = "rockchip,rk805" पूर्ण,
	अणु .compatible = "rockchip,rk808" पूर्ण,
	अणु .compatible = "rockchip,rk809" पूर्ण,
	अणु .compatible = "rockchip,rk817" पूर्ण,
	अणु .compatible = "rockchip,rk818" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rk808_of_match);

अटल पूर्णांक rk808_probe(काष्ठा i2c_client *client,
		       स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device_node *np = client->dev.of_node;
	काष्ठा rk808 *rk808;
	स्थिर काष्ठा rk808_reg_data *pre_init_reg;
	स्थिर काष्ठा mfd_cell *cells;
	पूर्णांक nr_pre_init_regs;
	पूर्णांक nr_cells;
	पूर्णांक msb, lsb;
	अचिन्हित अक्षर pmic_id_msb, pmic_id_lsb;
	पूर्णांक ret;
	पूर्णांक i;

	rk808 = devm_kzalloc(&client->dev, माप(*rk808), GFP_KERNEL);
	अगर (!rk808)
		वापस -ENOMEM;

	अगर (of_device_is_compatible(np, "rockchip,rk817") ||
	    of_device_is_compatible(np, "rockchip,rk809")) अणु
		pmic_id_msb = RK817_ID_MSB;
		pmic_id_lsb = RK817_ID_LSB;
	पूर्ण अन्यथा अणु
		pmic_id_msb = RK808_ID_MSB;
		pmic_id_lsb = RK808_ID_LSB;
	पूर्ण

	/* Read chip variant */
	msb = i2c_smbus_पढ़ो_byte_data(client, pmic_id_msb);
	अगर (msb < 0) अणु
		dev_err(&client->dev, "failed to read the chip id at 0x%x\n",
			RK808_ID_MSB);
		वापस msb;
	पूर्ण

	lsb = i2c_smbus_पढ़ो_byte_data(client, pmic_id_lsb);
	अगर (lsb < 0) अणु
		dev_err(&client->dev, "failed to read the chip id at 0x%x\n",
			RK808_ID_LSB);
		वापस lsb;
	पूर्ण

	rk808->variant = ((msb << 8) | lsb) & RK8XX_ID_MSK;
	dev_info(&client->dev, "chip id: 0x%x\n", (अचिन्हित पूर्णांक)rk808->variant);

	चयन (rk808->variant) अणु
	हाल RK805_ID:
		rk808->regmap_cfg = &rk805_regmap_config;
		rk808->regmap_irq_chip = &rk805_irq_chip;
		pre_init_reg = rk805_pre_init_reg;
		nr_pre_init_regs = ARRAY_SIZE(rk805_pre_init_reg);
		cells = rk805s;
		nr_cells = ARRAY_SIZE(rk805s);
		अवरोध;
	हाल RK808_ID:
		rk808->regmap_cfg = &rk808_regmap_config;
		rk808->regmap_irq_chip = &rk808_irq_chip;
		pre_init_reg = rk808_pre_init_reg;
		nr_pre_init_regs = ARRAY_SIZE(rk808_pre_init_reg);
		cells = rk808s;
		nr_cells = ARRAY_SIZE(rk808s);
		अवरोध;
	हाल RK818_ID:
		rk808->regmap_cfg = &rk818_regmap_config;
		rk808->regmap_irq_chip = &rk818_irq_chip;
		pre_init_reg = rk818_pre_init_reg;
		nr_pre_init_regs = ARRAY_SIZE(rk818_pre_init_reg);
		cells = rk818s;
		nr_cells = ARRAY_SIZE(rk818s);
		अवरोध;
	हाल RK809_ID:
	हाल RK817_ID:
		rk808->regmap_cfg = &rk817_regmap_config;
		rk808->regmap_irq_chip = &rk817_irq_chip;
		pre_init_reg = rk817_pre_init_reg;
		nr_pre_init_regs = ARRAY_SIZE(rk817_pre_init_reg);
		cells = rk817s;
		nr_cells = ARRAY_SIZE(rk817s);
		अवरोध;
	शेष:
		dev_err(&client->dev, "Unsupported RK8XX ID %lu\n",
			rk808->variant);
		वापस -EINVAL;
	पूर्ण

	rk808->i2c = client;
	i2c_set_clientdata(client, rk808);

	rk808->regmap = devm_regmap_init_i2c(client, rk808->regmap_cfg);
	अगर (IS_ERR(rk808->regmap)) अणु
		dev_err(&client->dev, "regmap initialization failed\n");
		वापस PTR_ERR(rk808->regmap);
	पूर्ण

	अगर (!client->irq) अणु
		dev_err(&client->dev, "No interrupt support, no core IRQ\n");
		वापस -EINVAL;
	पूर्ण

	ret = regmap_add_irq_chip(rk808->regmap, client->irq,
				  IRQF_ONESHOT, -1,
				  rk808->regmap_irq_chip, &rk808->irq_data);
	अगर (ret) अणु
		dev_err(&client->dev, "Failed to add irq_chip %d\n", ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < nr_pre_init_regs; i++) अणु
		ret = regmap_update_bits(rk808->regmap,
					pre_init_reg[i].addr,
					pre_init_reg[i].mask,
					pre_init_reg[i].value);
		अगर (ret) अणु
			dev_err(&client->dev,
				"0x%x write err\n",
				pre_init_reg[i].addr);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = devm_mfd_add_devices(&client->dev, PLATFORM_DEVID_NONE,
			      cells, nr_cells, शून्य, 0,
			      regmap_irq_get_करोमुख्य(rk808->irq_data));
	अगर (ret) अणु
		dev_err(&client->dev, "failed to add MFD devices %d\n", ret);
		जाओ err_irq;
	पूर्ण

	अगर (of_property_पढ़ो_bool(np, "rockchip,system-power-controller")) अणु
		rk808_i2c_client = client;
		pm_घातer_off = rk808_pm_घातer_off;
	पूर्ण

	वापस 0;

err_irq:
	regmap_del_irq_chip(client->irq, rk808->irq_data);
	वापस ret;
पूर्ण

अटल पूर्णांक rk808_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा rk808 *rk808 = i2c_get_clientdata(client);

	regmap_del_irq_chip(client->irq, rk808->irq_data);

	/**
	 * pm_घातer_off may poपूर्णांकs to a function from another module.
	 * Check अगर the poपूर्णांकer is set by us and only then overग_लिखो it.
	 */
	अगर (pm_घातer_off == rk808_pm_घातer_off)
		pm_घातer_off = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused rk8xx_suspend(काष्ठा device *dev)
अणु
	काष्ठा rk808 *rk808 = i2c_get_clientdata(to_i2c_client(dev));
	पूर्णांक ret = 0;

	चयन (rk808->variant) अणु
	हाल RK805_ID:
		ret = regmap_update_bits(rk808->regmap,
					 RK805_GPIO_IO_POL_REG,
					 SLP_SD_MSK,
					 SLEEP_FUN);
		अवरोध;
	हाल RK809_ID:
	हाल RK817_ID:
		ret = regmap_update_bits(rk808->regmap,
					 RK817_SYS_CFG(3),
					 RK817_SLPPIN_FUNC_MSK,
					 SLPPIN_SLP_FUN);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused rk8xx_resume(काष्ठा device *dev)
अणु
	काष्ठा rk808 *rk808 = i2c_get_clientdata(to_i2c_client(dev));
	पूर्णांक ret = 0;

	चयन (rk808->variant) अणु
	हाल RK809_ID:
	हाल RK817_ID:
		ret = regmap_update_bits(rk808->regmap,
					 RK817_SYS_CFG(3),
					 RK817_SLPPIN_FUNC_MSK,
					 SLPPIN_शून्य_FUN);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
अटल SIMPLE_DEV_PM_OPS(rk8xx_pm_ops, rk8xx_suspend, rk8xx_resume);

अटल काष्ठा i2c_driver rk808_i2c_driver = अणु
	.driver = अणु
		.name = "rk808",
		.of_match_table = rk808_of_match,
		.pm = &rk8xx_pm_ops,
	पूर्ण,
	.probe    = rk808_probe,
	.हटाओ   = rk808_हटाओ,
	.shutकरोwn = rk8xx_shutकरोwn,
पूर्ण;

module_i2c_driver(rk808_i2c_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chris Zhong <zyw@rock-chips.com>");
MODULE_AUTHOR("Zhang Qing <zhangqing@rock-chips.com>");
MODULE_AUTHOR("Wadim Egorov <w.egorov@phytec.de>");
MODULE_DESCRIPTION("RK808/RK818 PMIC driver");
