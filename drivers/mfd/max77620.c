<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Maxim MAX77620 MFD Driver
 *
 * Copyright (C) 2016 NVIDIA CORPORATION. All rights reserved.
 *
 * Author:
 *	Laxman Dewangan <ldewangan@nvidia.com>
 *	Chaitanya Bandi <bandik@nvidia.com>
 *	Mallikarjun Kasoju <mkasoju@nvidia.com>
 */

/****************** Teminology used in driver ********************
 * Here are some terminology used from datasheet क्रम quick reference:
 * Flexible Power Sequence (FPS):
 * The Flexible Power Sequencer (FPS) allows each regulator to घातer up under
 * hardware or software control. Additionally, each regulator can घातer on
 * independently or among a group of other regulators with an adjustable
 * घातer-up and घातer-करोwn delays (sequencing). GPIO1, GPIO2, and GPIO3 can
 * be programmed to be part of a sequence allowing बाह्यal regulators to be
 * sequenced aदीर्घ with पूर्णांकernal regulators. 32KHz घड़ी can be programmed to
 * be part of a sequence.
 * There is 3 FPS confguration रेजिस्टरs and all resources are configured to
 * any of these FPS or no FPS.
 */

#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/max77620.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

अटल काष्ठा max77620_chip *max77620_scratch;

अटल स्थिर काष्ठा resource gpio_resources[] = अणु
	DEFINE_RES_IRQ(MAX77620_IRQ_TOP_GPIO),
पूर्ण;

अटल स्थिर काष्ठा resource घातer_resources[] = अणु
	DEFINE_RES_IRQ(MAX77620_IRQ_LBT_MBATLOW),
पूर्ण;

अटल स्थिर काष्ठा resource rtc_resources[] = अणु
	DEFINE_RES_IRQ(MAX77620_IRQ_TOP_RTC),
पूर्ण;

अटल स्थिर काष्ठा resource thermal_resources[] = अणु
	DEFINE_RES_IRQ(MAX77620_IRQ_LBT_TJALRM1),
	DEFINE_RES_IRQ(MAX77620_IRQ_LBT_TJALRM2),
पूर्ण;

अटल स्थिर काष्ठा regmap_irq max77620_top_irqs[] = अणु
	REGMAP_IRQ_REG(MAX77620_IRQ_TOP_GLBL, 0, MAX77620_IRQ_TOP_GLBL_MASK),
	REGMAP_IRQ_REG(MAX77620_IRQ_TOP_SD, 0, MAX77620_IRQ_TOP_SD_MASK),
	REGMAP_IRQ_REG(MAX77620_IRQ_TOP_LDO, 0, MAX77620_IRQ_TOP_LDO_MASK),
	REGMAP_IRQ_REG(MAX77620_IRQ_TOP_GPIO, 0, MAX77620_IRQ_TOP_GPIO_MASK),
	REGMAP_IRQ_REG(MAX77620_IRQ_TOP_RTC, 0, MAX77620_IRQ_TOP_RTC_MASK),
	REGMAP_IRQ_REG(MAX77620_IRQ_TOP_32K, 0, MAX77620_IRQ_TOP_32K_MASK),
	REGMAP_IRQ_REG(MAX77620_IRQ_TOP_ONOFF, 0, MAX77620_IRQ_TOP_ONOFF_MASK),
	REGMAP_IRQ_REG(MAX77620_IRQ_LBT_MBATLOW, 1, MAX77620_IRQ_LBM_MASK),
	REGMAP_IRQ_REG(MAX77620_IRQ_LBT_TJALRM1, 1, MAX77620_IRQ_TJALRM1_MASK),
	REGMAP_IRQ_REG(MAX77620_IRQ_LBT_TJALRM2, 1, MAX77620_IRQ_TJALRM2_MASK),
पूर्ण;

अटल स्थिर काष्ठा mfd_cell max77620_children[] = अणु
	अणु .name = "max77620-pinctrl", पूर्ण,
	अणु .name = "max77620-clock", पूर्ण,
	अणु .name = "max77620-pmic", पूर्ण,
	अणु .name = "max77620-watchdog", पूर्ण,
	अणु
		.name = "max77620-gpio",
		.resources = gpio_resources,
		.num_resources = ARRAY_SIZE(gpio_resources),
	पूर्ण, अणु
		.name = "max77620-rtc",
		.resources = rtc_resources,
		.num_resources = ARRAY_SIZE(rtc_resources),
	पूर्ण, अणु
		.name = "max77620-power",
		.resources = घातer_resources,
		.num_resources = ARRAY_SIZE(घातer_resources),
	पूर्ण, अणु
		.name = "max77620-thermal",
		.resources = thermal_resources,
		.num_resources = ARRAY_SIZE(thermal_resources),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell max20024_children[] = अणु
	अणु .name = "max20024-pinctrl", पूर्ण,
	अणु .name = "max77620-clock", पूर्ण,
	अणु .name = "max20024-pmic", पूर्ण,
	अणु .name = "max77620-watchdog", पूर्ण,
	अणु
		.name = "max77620-gpio",
		.resources = gpio_resources,
		.num_resources = ARRAY_SIZE(gpio_resources),
	पूर्ण, अणु
		.name = "max77620-rtc",
		.resources = rtc_resources,
		.num_resources = ARRAY_SIZE(rtc_resources),
	पूर्ण, अणु
		.name = "max20024-power",
		.resources = घातer_resources,
		.num_resources = ARRAY_SIZE(घातer_resources),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell max77663_children[] = अणु
	अणु .name = "max77620-pinctrl", पूर्ण,
	अणु .name = "max77620-clock", पूर्ण,
	अणु .name = "max77663-pmic", पूर्ण,
	अणु .name = "max77620-watchdog", पूर्ण,
	अणु
		.name = "max77620-gpio",
		.resources = gpio_resources,
		.num_resources = ARRAY_SIZE(gpio_resources),
	पूर्ण, अणु
		.name = "max77620-rtc",
		.resources = rtc_resources,
		.num_resources = ARRAY_SIZE(rtc_resources),
	पूर्ण, अणु
		.name = "max77663-power",
		.resources = घातer_resources,
		.num_resources = ARRAY_SIZE(घातer_resources),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_range max77620_पढ़ोable_ranges[] = अणु
	regmap_reg_range(MAX77620_REG_CNFGGLBL1, MAX77620_REG_DVSSD4),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table max77620_पढ़ोable_table = अणु
	.yes_ranges = max77620_पढ़ोable_ranges,
	.n_yes_ranges = ARRAY_SIZE(max77620_पढ़ोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range max20024_पढ़ोable_ranges[] = अणु
	regmap_reg_range(MAX77620_REG_CNFGGLBL1, MAX77620_REG_DVSSD4),
	regmap_reg_range(MAX20024_REG_MAX_ADD, MAX20024_REG_MAX_ADD),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table max20024_पढ़ोable_table = अणु
	.yes_ranges = max20024_पढ़ोable_ranges,
	.n_yes_ranges = ARRAY_SIZE(max20024_पढ़ोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range max77620_writable_ranges[] = अणु
	regmap_reg_range(MAX77620_REG_CNFGGLBL1, MAX77620_REG_DVSSD4),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table max77620_writable_table = अणु
	.yes_ranges = max77620_writable_ranges,
	.n_yes_ranges = ARRAY_SIZE(max77620_writable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range max77620_cacheable_ranges[] = अणु
	regmap_reg_range(MAX77620_REG_SD0_CFG, MAX77620_REG_LDO_CFG3),
	regmap_reg_range(MAX77620_REG_FPS_CFG0, MAX77620_REG_FPS_SD3),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table max77620_अस्थिर_table = अणु
	.no_ranges = max77620_cacheable_ranges,
	.n_no_ranges = ARRAY_SIZE(max77620_cacheable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config max77620_regmap_config = अणु
	.name = "power-slave",
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = MAX77620_REG_DVSSD4 + 1,
	.cache_type = REGCACHE_RBTREE,
	.rd_table = &max77620_पढ़ोable_table,
	.wr_table = &max77620_writable_table,
	.अस्थिर_table = &max77620_अस्थिर_table,
	.use_single_ग_लिखो = true,
पूर्ण;

अटल स्थिर काष्ठा regmap_config max20024_regmap_config = अणु
	.name = "power-slave",
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = MAX20024_REG_MAX_ADD + 1,
	.cache_type = REGCACHE_RBTREE,
	.rd_table = &max20024_पढ़ोable_table,
	.wr_table = &max77620_writable_table,
	.अस्थिर_table = &max77620_अस्थिर_table,
पूर्ण;

अटल स्थिर काष्ठा regmap_range max77663_पढ़ोable_ranges[] = अणु
	regmap_reg_range(MAX77620_REG_CNFGGLBL1, MAX77620_REG_CID5),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table max77663_पढ़ोable_table = अणु
	.yes_ranges = max77663_पढ़ोable_ranges,
	.n_yes_ranges = ARRAY_SIZE(max77663_पढ़ोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range max77663_writable_ranges[] = अणु
	regmap_reg_range(MAX77620_REG_CNFGGLBL1, MAX77620_REG_CID5),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table max77663_writable_table = अणु
	.yes_ranges = max77663_writable_ranges,
	.n_yes_ranges = ARRAY_SIZE(max77663_writable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config max77663_regmap_config = अणु
	.name = "power-slave",
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = MAX77620_REG_CID5 + 1,
	.cache_type = REGCACHE_RBTREE,
	.rd_table = &max77663_पढ़ोable_table,
	.wr_table = &max77663_writable_table,
	.अस्थिर_table = &max77620_अस्थिर_table,
पूर्ण;

/*
 * MAX77620 and MAX20024 has the following steps of the पूर्णांकerrupt handling
 * क्रम TOP पूर्णांकerrupts:
 * 1. When पूर्णांकerrupt occurs from PMIC, mask the PMIC पूर्णांकerrupt by setting GLBLM.
 * 2. Read IRQTOP and service the पूर्णांकerrupt.
 * 3. Once all पूर्णांकerrupts has been checked and serviced, the पूर्णांकerrupt service
 *    routine un-masks the hardware पूर्णांकerrupt line by clearing GLBLM.
 */
अटल पूर्णांक max77620_irq_global_mask(व्योम *irq_drv_data)
अणु
	काष्ठा max77620_chip *chip = irq_drv_data;
	पूर्णांक ret;

	ret = regmap_update_bits(chip->rmap, MAX77620_REG_INTENLBT,
				 MAX77620_GLBLM_MASK, MAX77620_GLBLM_MASK);
	अगर (ret < 0)
		dev_err(chip->dev, "Failed to set GLBLM: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक max77620_irq_global_unmask(व्योम *irq_drv_data)
अणु
	काष्ठा max77620_chip *chip = irq_drv_data;
	पूर्णांक ret;

	ret = regmap_update_bits(chip->rmap, MAX77620_REG_INTENLBT,
				 MAX77620_GLBLM_MASK, 0);
	अगर (ret < 0)
		dev_err(chip->dev, "Failed to reset GLBLM: %d\n", ret);

	वापस ret;
पूर्ण

अटल काष्ठा regmap_irq_chip max77620_top_irq_chip = अणु
	.name = "max77620-top",
	.irqs = max77620_top_irqs,
	.num_irqs = ARRAY_SIZE(max77620_top_irqs),
	.num_regs = 2,
	.status_base = MAX77620_REG_IRQTOP,
	.mask_base = MAX77620_REG_IRQTOPM,
	.handle_pre_irq = max77620_irq_global_mask,
	.handle_post_irq = max77620_irq_global_unmask,
पूर्ण;

/* max77620_get_fps_period_reg_value:  Get FPS bit field value from
 *				       requested periods.
 * MAX77620 supports the FPS period of 40, 80, 160, 320, 540, 1280, 2560
 * and 5120 microseconds. MAX20024 supports the FPS period of 20, 40, 80,
 * 160, 320, 540, 1280 and 2560 microseconds.
 * The FPS रेजिस्टर has 3 bits field to set the FPS period as
 * bits		max77620		max20024
 * 000		40			20
 * 001		80			40
 * :::
*/
अटल पूर्णांक max77620_get_fps_period_reg_value(काष्ठा max77620_chip *chip,
					     पूर्णांक tperiod)
अणु
	पूर्णांक fps_min_period;
	पूर्णांक i;

	चयन (chip->chip_id) अणु
	हाल MAX20024:
		fps_min_period = MAX20024_FPS_PERIOD_MIN_US;
		अवरोध;
	हाल MAX77620:
		fps_min_period = MAX77620_FPS_PERIOD_MIN_US;
		अवरोध;
	हाल MAX77663:
		fps_min_period = MAX20024_FPS_PERIOD_MIN_US;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < 7; i++) अणु
		अगर (fps_min_period >= tperiod)
			वापस i;
		fps_min_period *= 2;
	पूर्ण

	वापस i;
पूर्ण

/* max77620_config_fps: Configure FPS configuration रेजिस्टरs
 *			based on platक्रमm specअगरic inक्रमmation.
 */
अटल पूर्णांक max77620_config_fps(काष्ठा max77620_chip *chip,
			       काष्ठा device_node *fps_np)
अणु
	काष्ठा device *dev = chip->dev;
	अचिन्हित पूर्णांक mask = 0, config = 0;
	u32 fps_max_period;
	u32 param_val;
	पूर्णांक tperiod, fps_id;
	पूर्णांक ret;
	अक्षर fps_name[10];

	चयन (chip->chip_id) अणु
	हाल MAX20024:
		fps_max_period = MAX20024_FPS_PERIOD_MAX_US;
		अवरोध;
	हाल MAX77620:
		fps_max_period = MAX77620_FPS_PERIOD_MAX_US;
		अवरोध;
	हाल MAX77663:
		fps_max_period = MAX20024_FPS_PERIOD_MAX_US;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	क्रम (fps_id = 0; fps_id < MAX77620_FPS_COUNT; fps_id++) अणु
		प्र_लिखो(fps_name, "fps%d", fps_id);
		अगर (of_node_name_eq(fps_np, fps_name))
			अवरोध;
	पूर्ण

	अगर (fps_id == MAX77620_FPS_COUNT) अणु
		dev_err(dev, "FPS node name %pOFn is not valid\n", fps_np);
		वापस -EINVAL;
	पूर्ण

	ret = of_property_पढ़ो_u32(fps_np, "maxim,shutdown-fps-time-period-us",
				   &param_val);
	अगर (!ret) अणु
		mask |= MAX77620_FPS_TIME_PERIOD_MASK;
		chip->shutकरोwn_fps_period[fps_id] = min(param_val,
							fps_max_period);
		tperiod = max77620_get_fps_period_reg_value(chip,
				chip->shutकरोwn_fps_period[fps_id]);
		config |= tperiod << MAX77620_FPS_TIME_PERIOD_SHIFT;
	पूर्ण

	ret = of_property_पढ़ो_u32(fps_np, "maxim,suspend-fps-time-period-us",
				   &param_val);
	अगर (!ret)
		chip->suspend_fps_period[fps_id] = min(param_val,
						       fps_max_period);

	ret = of_property_पढ़ो_u32(fps_np, "maxim,fps-event-source",
				   &param_val);
	अगर (!ret) अणु
		अगर (param_val > 2) अणु
			dev_err(dev, "FPS%d event-source invalid\n", fps_id);
			वापस -EINVAL;
		पूर्ण
		mask |= MAX77620_FPS_EN_SRC_MASK;
		config |= param_val << MAX77620_FPS_EN_SRC_SHIFT;
		अगर (param_val == 2) अणु
			mask |= MAX77620_FPS_ENFPS_SW_MASK;
			config |= MAX77620_FPS_ENFPS_SW;
		पूर्ण
	पूर्ण

	अगर (!chip->sleep_enable && !chip->enable_global_lpm) अणु
		ret = of_property_पढ़ो_u32(fps_np,
				"maxim,device-state-on-disabled-event",
				&param_val);
		अगर (!ret) अणु
			अगर (param_val == 0)
				chip->sleep_enable = true;
			अन्यथा अगर (param_val == 1)
				chip->enable_global_lpm = true;
		पूर्ण
	पूर्ण

	ret = regmap_update_bits(chip->rmap, MAX77620_REG_FPS_CFG0 + fps_id,
				 mask, config);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to update FPS CFG: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max77620_initialise_fps(काष्ठा max77620_chip *chip)
अणु
	काष्ठा device *dev = chip->dev;
	काष्ठा device_node *fps_np, *fps_child;
	u8 config;
	पूर्णांक fps_id;
	पूर्णांक ret;

	क्रम (fps_id = 0; fps_id < MAX77620_FPS_COUNT; fps_id++) अणु
		chip->shutकरोwn_fps_period[fps_id] = -1;
		chip->suspend_fps_period[fps_id] = -1;
	पूर्ण

	fps_np = of_get_child_by_name(dev->of_node, "fps");
	अगर (!fps_np)
		जाओ skip_fps;

	क्रम_each_child_of_node(fps_np, fps_child) अणु
		ret = max77620_config_fps(chip, fps_child);
		अगर (ret < 0) अणु
			of_node_put(fps_child);
			वापस ret;
		पूर्ण
	पूर्ण

	config = chip->enable_global_lpm ? MAX77620_ONOFFCNFG2_SLP_LPM_MSK : 0;
	ret = regmap_update_bits(chip->rmap, MAX77620_REG_ONOFFCNFG2,
				 MAX77620_ONOFFCNFG2_SLP_LPM_MSK, config);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to update SLP_LPM: %d\n", ret);
		वापस ret;
	पूर्ण

skip_fps:
	अगर (chip->chip_id == MAX77663)
		वापस 0;

	/* Enable wake on EN0 pin */
	ret = regmap_update_bits(chip->rmap, MAX77620_REG_ONOFFCNFG2,
				 MAX77620_ONOFFCNFG2_WK_EN0,
				 MAX77620_ONOFFCNFG2_WK_EN0);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to update WK_EN0: %d\n", ret);
		वापस ret;
	पूर्ण

	/* For MAX20024, SLPEN will be POR reset अगर CLRSE is b11 */
	अगर ((chip->chip_id == MAX20024) && chip->sleep_enable) अणु
		config = MAX77620_ONOFFCNFG1_SLPEN | MAX20024_ONOFFCNFG1_CLRSE;
		ret = regmap_update_bits(chip->rmap, MAX77620_REG_ONOFFCNFG1,
					 config, config);
		अगर (ret < 0) अणु
			dev_err(dev, "Failed to update SLPEN: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max77620_पढ़ो_es_version(काष्ठा max77620_chip *chip)
अणु
	अचिन्हित पूर्णांक val;
	u8 cid_val[6];
	पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = MAX77620_REG_CID0; i <= MAX77620_REG_CID5; i++) अणु
		ret = regmap_पढ़ो(chip->rmap, i, &val);
		अगर (ret < 0) अणु
			dev_err(chip->dev, "Failed to read CID: %d\n", ret);
			वापस ret;
		पूर्ण
		dev_dbg(chip->dev, "CID%d: 0x%02x\n",
			i - MAX77620_REG_CID0, val);
		cid_val[i - MAX77620_REG_CID0] = val;
	पूर्ण

	/* CID4 is OTP Version  and CID5 is ES version */
	dev_info(chip->dev, "PMIC Version OTP:0x%02X and ES:0x%X\n",
		 cid_val[4], MAX77620_CID5_DIDM(cid_val[5]));

	वापस ret;
पूर्ण

अटल व्योम max77620_pm_घातer_off(व्योम)
अणु
	काष्ठा max77620_chip *chip = max77620_scratch;

	regmap_update_bits(chip->rmap, MAX77620_REG_ONOFFCNFG1,
			   MAX77620_ONOFFCNFG1_SFT_RST,
			   MAX77620_ONOFFCNFG1_SFT_RST);
पूर्ण

अटल पूर्णांक max77620_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	स्थिर काष्ठा regmap_config *rmap_config;
	काष्ठा max77620_chip *chip;
	स्थिर काष्ठा mfd_cell *mfd_cells;
	पूर्णांक n_mfd_cells;
	bool pm_off;
	पूर्णांक ret;

	chip = devm_kzalloc(&client->dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	i2c_set_clientdata(client, chip);
	chip->dev = &client->dev;
	chip->chip_irq = client->irq;
	chip->chip_id = (क्रमागत max77620_chip_id)id->driver_data;

	चयन (chip->chip_id) अणु
	हाल MAX77620:
		mfd_cells = max77620_children;
		n_mfd_cells = ARRAY_SIZE(max77620_children);
		rmap_config = &max77620_regmap_config;
		अवरोध;
	हाल MAX20024:
		mfd_cells = max20024_children;
		n_mfd_cells = ARRAY_SIZE(max20024_children);
		rmap_config = &max20024_regmap_config;
		अवरोध;
	हाल MAX77663:
		mfd_cells = max77663_children;
		n_mfd_cells = ARRAY_SIZE(max77663_children);
		rmap_config = &max77663_regmap_config;
		अवरोध;
	शेष:
		dev_err(chip->dev, "ChipID is invalid %d\n", chip->chip_id);
		वापस -EINVAL;
	पूर्ण

	chip->rmap = devm_regmap_init_i2c(client, rmap_config);
	अगर (IS_ERR(chip->rmap)) अणु
		ret = PTR_ERR(chip->rmap);
		dev_err(chip->dev, "Failed to initialise regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = max77620_पढ़ो_es_version(chip);
	अगर (ret < 0)
		वापस ret;

	max77620_top_irq_chip.irq_drv_data = chip;
	ret = devm_regmap_add_irq_chip(chip->dev, chip->rmap, client->irq,
				       IRQF_ONESHOT | IRQF_SHARED, 0,
				       &max77620_top_irq_chip,
				       &chip->top_irq_data);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Failed to add regmap irq: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = max77620_initialise_fps(chip);
	अगर (ret < 0)
		वापस ret;

	ret =  devm_mfd_add_devices(chip->dev, PLATFORM_DEVID_NONE,
				    mfd_cells, n_mfd_cells, शून्य, 0,
				    regmap_irq_get_करोमुख्य(chip->top_irq_data));
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Failed to add MFD children: %d\n", ret);
		वापस ret;
	पूर्ण

	pm_off = of_device_is_प्रणाली_घातer_controller(client->dev.of_node);
	अगर (pm_off && !pm_घातer_off) अणु
		max77620_scratch = chip;
		pm_घातer_off = max77620_pm_घातer_off;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक max77620_set_fps_period(काष्ठा max77620_chip *chip,
				   पूर्णांक fps_id, पूर्णांक समय_period)
अणु
	पूर्णांक period = max77620_get_fps_period_reg_value(chip, समय_period);
	पूर्णांक ret;

	ret = regmap_update_bits(chip->rmap, MAX77620_REG_FPS_CFG0 + fps_id,
				 MAX77620_FPS_TIME_PERIOD_MASK,
				 period << MAX77620_FPS_TIME_PERIOD_SHIFT);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Failed to update FPS period: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max77620_i2c_suspend(काष्ठा device *dev)
अणु
	काष्ठा max77620_chip *chip = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = to_i2c_client(dev);
	अचिन्हित पूर्णांक config;
	पूर्णांक fps;
	पूर्णांक ret;

	क्रम (fps = 0; fps < MAX77620_FPS_COUNT; fps++) अणु
		अगर (chip->suspend_fps_period[fps] < 0)
			जारी;

		ret = max77620_set_fps_period(chip, fps,
					      chip->suspend_fps_period[fps]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/*
	 * For MAX20024: No need to configure SLPEN on suspend as
	 * it will be configured on Init.
	 */
	अगर (chip->chip_id == MAX20024)
		जाओ out;

	config = (chip->sleep_enable) ? MAX77620_ONOFFCNFG1_SLPEN : 0;
	ret = regmap_update_bits(chip->rmap, MAX77620_REG_ONOFFCNFG1,
				 MAX77620_ONOFFCNFG1_SLPEN,
				 config);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to configure sleep in suspend: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (chip->chip_id == MAX77663)
		जाओ out;

	/* Disable WK_EN0 */
	ret = regmap_update_bits(chip->rmap, MAX77620_REG_ONOFFCNFG2,
				 MAX77620_ONOFFCNFG2_WK_EN0, 0);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to configure WK_EN in suspend: %d\n", ret);
		वापस ret;
	पूर्ण

out:
	disable_irq(client->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक max77620_i2c_resume(काष्ठा device *dev)
अणु
	काष्ठा max77620_chip *chip = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = to_i2c_client(dev);
	पूर्णांक ret;
	पूर्णांक fps;

	क्रम (fps = 0; fps < MAX77620_FPS_COUNT; fps++) अणु
		अगर (chip->shutकरोwn_fps_period[fps] < 0)
			जारी;

		ret = max77620_set_fps_period(chip, fps,
					      chip->shutकरोwn_fps_period[fps]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/*
	 * For MAX20024: No need to configure WKEN0 on resume as
	 * it is configured on Init.
	 */
	अगर (chip->chip_id == MAX20024 || chip->chip_id == MAX77663)
		जाओ out;

	/* Enable WK_EN0 */
	ret = regmap_update_bits(chip->rmap, MAX77620_REG_ONOFFCNFG2,
				 MAX77620_ONOFFCNFG2_WK_EN0,
				 MAX77620_ONOFFCNFG2_WK_EN0);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to configure WK_EN0 n resume: %d\n", ret);
		वापस ret;
	पूर्ण

out:
	enable_irq(client->irq);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id max77620_id[] = अणु
	अणु"max77620", MAX77620पूर्ण,
	अणु"max20024", MAX20024पूर्ण,
	अणु"max77663", MAX77663पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dev_pm_ops max77620_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(max77620_i2c_suspend, max77620_i2c_resume)
पूर्ण;

अटल काष्ठा i2c_driver max77620_driver = अणु
	.driver = अणु
		.name = "max77620",
		.pm = &max77620_pm_ops,
	पूर्ण,
	.probe = max77620_probe,
	.id_table = max77620_id,
पूर्ण;
builtin_i2c_driver(max77620_driver);
