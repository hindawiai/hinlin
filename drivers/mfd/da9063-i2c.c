<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* I2C support क्रम Dialog DA9063
 *
 * Copyright 2012 Dialog Semiconductor Ltd.
 * Copyright 2013 Philipp Zabel, Pengutronix
 *
 * Author: Krystian Garbaciak, Dialog Semiconductor
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>

#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/da9063/core.h>
#समावेश <linux/mfd/da9063/रेजिस्टरs.h>

#समावेश <linux/of.h>
#समावेश <linux/regulator/of_regulator.h>

/*
 * Raw I2C access required क्रम just accessing chip and variant info beक्रमe we
 * know which device is present. The info पढ़ो from the device using this
 * approach is then used to select the correct regmap tables.
 */

#घोषणा DA9063_REG_PAGE_SIZE		0x100
#घोषणा DA9063_REG_PAGED_ADDR_MASK	0xFF

क्रमागत da9063_page_sel_buf_fmt अणु
	DA9063_PAGE_SEL_BUF_PAGE_REG = 0,
	DA9063_PAGE_SEL_BUF_PAGE_VAL,
	DA9063_PAGE_SEL_BUF_SIZE,
पूर्ण;

क्रमागत da9063_paged_पढ़ो_msgs अणु
	DA9063_PAGED_READ_MSG_PAGE_SEL = 0,
	DA9063_PAGED_READ_MSG_REG_SEL,
	DA9063_PAGED_READ_MSG_DATA,
	DA9063_PAGED_READ_MSG_CNT,
पूर्ण;

अटल पूर्णांक da9063_i2c_blockreg_पढ़ो(काष्ठा i2c_client *client, u16 addr,
				    u8 *buf, पूर्णांक count)
अणु
	काष्ठा i2c_msg xfer[DA9063_PAGED_READ_MSG_CNT];
	u8 page_sel_buf[DA9063_PAGE_SEL_BUF_SIZE];
	u8 page_num, paged_addr;
	पूर्णांक ret;

	/* Determine page info based on रेजिस्टर address */
	page_num = (addr / DA9063_REG_PAGE_SIZE);
	अगर (page_num > 1) अणु
		dev_err(&client->dev, "Invalid register address provided\n");
		वापस -EINVAL;
	पूर्ण

	paged_addr = (addr % DA9063_REG_PAGE_SIZE) & DA9063_REG_PAGED_ADDR_MASK;
	page_sel_buf[DA9063_PAGE_SEL_BUF_PAGE_REG] = DA9063_REG_PAGE_CON;
	page_sel_buf[DA9063_PAGE_SEL_BUF_PAGE_VAL] =
		(page_num << DA9063_I2C_PAGE_SEL_SHIFT) & DA9063_REG_PAGE_MASK;

	/* Write reg address, page selection */
	xfer[DA9063_PAGED_READ_MSG_PAGE_SEL].addr = client->addr;
	xfer[DA9063_PAGED_READ_MSG_PAGE_SEL].flags = 0;
	xfer[DA9063_PAGED_READ_MSG_PAGE_SEL].len = DA9063_PAGE_SEL_BUF_SIZE;
	xfer[DA9063_PAGED_READ_MSG_PAGE_SEL].buf = page_sel_buf;

	/* Select रेजिस्टर address */
	xfer[DA9063_PAGED_READ_MSG_REG_SEL].addr = client->addr;
	xfer[DA9063_PAGED_READ_MSG_REG_SEL].flags = 0;
	xfer[DA9063_PAGED_READ_MSG_REG_SEL].len = माप(paged_addr);
	xfer[DA9063_PAGED_READ_MSG_REG_SEL].buf = &paged_addr;

	/* Read data */
	xfer[DA9063_PAGED_READ_MSG_DATA].addr = client->addr;
	xfer[DA9063_PAGED_READ_MSG_DATA].flags = I2C_M_RD;
	xfer[DA9063_PAGED_READ_MSG_DATA].len = count;
	xfer[DA9063_PAGED_READ_MSG_DATA].buf = buf;

	ret = i2c_transfer(client->adapter, xfer, DA9063_PAGED_READ_MSG_CNT);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Paged block read failed: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (ret != DA9063_PAGED_READ_MSG_CNT) अणु
		dev_err(&client->dev, "Paged block read failed to complete\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

क्रमागत अणु
	DA9063_DEV_ID_REG = 0,
	DA9063_VAR_ID_REG,
	DA9063_CHIP_ID_REGS,
पूर्ण;

अटल पूर्णांक da9063_get_device_type(काष्ठा i2c_client *i2c, काष्ठा da9063 *da9063)
अणु
	u8 buf[DA9063_CHIP_ID_REGS];
	पूर्णांक ret;

	ret = da9063_i2c_blockreg_पढ़ो(i2c, DA9063_REG_DEVICE_ID, buf,
				       DA9063_CHIP_ID_REGS);
	अगर (ret)
		वापस ret;

	अगर (buf[DA9063_DEV_ID_REG] != PMIC_CHIP_ID_DA9063) अणु
		dev_err(da9063->dev,
			"Invalid chip device ID: 0x%02x\n",
			buf[DA9063_DEV_ID_REG]);
		वापस -ENODEV;
	पूर्ण

	dev_info(da9063->dev,
		 "Device detected (chip-ID: 0x%02X, var-ID: 0x%02X)\n",
		 buf[DA9063_DEV_ID_REG], buf[DA9063_VAR_ID_REG]);

	da9063->variant_code =
		(buf[DA9063_VAR_ID_REG] & DA9063_VARIANT_ID_MRC_MASK)
		>> DA9063_VARIANT_ID_MRC_SHIFT;

	वापस 0;
पूर्ण

/*
 * Variant specअगरic regmap configs
 */

अटल स्थिर काष्ठा regmap_range da9063_ad_पढ़ोable_ranges[] = अणु
	regmap_reg_range(DA9063_REG_PAGE_CON, DA9063_AD_REG_SECOND_D),
	regmap_reg_range(DA9063_REG_SEQ, DA9063_REG_ID_32_31),
	regmap_reg_range(DA9063_REG_SEQ_A, DA9063_REG_AUTO3_LOW),
	regmap_reg_range(DA9063_REG_T_OFFSET, DA9063_AD_REG_GP_ID_19),
	regmap_reg_range(DA9063_REG_DEVICE_ID, DA9063_REG_VARIANT_ID),
पूर्ण;

अटल स्थिर काष्ठा regmap_range da9063_ad_ग_लिखोable_ranges[] = अणु
	regmap_reg_range(DA9063_REG_PAGE_CON, DA9063_REG_PAGE_CON),
	regmap_reg_range(DA9063_REG_FAULT_LOG, DA9063_REG_VSYS_MON),
	regmap_reg_range(DA9063_REG_COUNT_S, DA9063_AD_REG_ALARM_Y),
	regmap_reg_range(DA9063_REG_SEQ, DA9063_REG_ID_32_31),
	regmap_reg_range(DA9063_REG_SEQ_A, DA9063_REG_AUTO3_LOW),
	regmap_reg_range(DA9063_REG_CONFIG_I, DA9063_AD_REG_MON_REG_4),
	regmap_reg_range(DA9063_AD_REG_GP_ID_0, DA9063_AD_REG_GP_ID_19),
पूर्ण;

अटल स्थिर काष्ठा regmap_range da9063_ad_अस्थिर_ranges[] = अणु
	regmap_reg_range(DA9063_REG_PAGE_CON, DA9063_REG_EVENT_D),
	regmap_reg_range(DA9063_REG_CONTROL_A, DA9063_REG_CONTROL_B),
	regmap_reg_range(DA9063_REG_CONTROL_E, DA9063_REG_CONTROL_F),
	regmap_reg_range(DA9063_REG_BCORE2_CONT, DA9063_REG_LDO11_CONT),
	regmap_reg_range(DA9063_REG_DVC_1, DA9063_REG_ADC_MAN),
	regmap_reg_range(DA9063_REG_ADC_RES_L, DA9063_AD_REG_SECOND_D),
	regmap_reg_range(DA9063_REG_SEQ, DA9063_REG_SEQ),
	regmap_reg_range(DA9063_REG_EN_32K, DA9063_REG_EN_32K),
	regmap_reg_range(DA9063_AD_REG_MON_REG_5, DA9063_AD_REG_MON_REG_6),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table da9063_ad_पढ़ोable_table = अणु
	.yes_ranges = da9063_ad_पढ़ोable_ranges,
	.n_yes_ranges = ARRAY_SIZE(da9063_ad_पढ़ोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table da9063_ad_ग_लिखोable_table = अणु
	.yes_ranges = da9063_ad_ग_लिखोable_ranges,
	.n_yes_ranges = ARRAY_SIZE(da9063_ad_ग_लिखोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table da9063_ad_अस्थिर_table = अणु
	.yes_ranges = da9063_ad_अस्थिर_ranges,
	.n_yes_ranges = ARRAY_SIZE(da9063_ad_अस्थिर_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range da9063_bb_पढ़ोable_ranges[] = अणु
	regmap_reg_range(DA9063_REG_PAGE_CON, DA9063_BB_REG_SECOND_D),
	regmap_reg_range(DA9063_REG_SEQ, DA9063_REG_ID_32_31),
	regmap_reg_range(DA9063_REG_SEQ_A, DA9063_REG_AUTO3_LOW),
	regmap_reg_range(DA9063_REG_T_OFFSET, DA9063_BB_REG_GP_ID_19),
	regmap_reg_range(DA9063_REG_DEVICE_ID, DA9063_REG_VARIANT_ID),
पूर्ण;

अटल स्थिर काष्ठा regmap_range da9063_bb_ग_लिखोable_ranges[] = अणु
	regmap_reg_range(DA9063_REG_PAGE_CON, DA9063_REG_PAGE_CON),
	regmap_reg_range(DA9063_REG_FAULT_LOG, DA9063_REG_VSYS_MON),
	regmap_reg_range(DA9063_REG_COUNT_S, DA9063_BB_REG_ALARM_Y),
	regmap_reg_range(DA9063_REG_SEQ, DA9063_REG_ID_32_31),
	regmap_reg_range(DA9063_REG_SEQ_A, DA9063_REG_AUTO3_LOW),
	regmap_reg_range(DA9063_REG_CONFIG_I, DA9063_BB_REG_MON_REG_4),
	regmap_reg_range(DA9063_BB_REG_GP_ID_0, DA9063_BB_REG_GP_ID_19),
पूर्ण;

अटल स्थिर काष्ठा regmap_range da9063_bb_da_अस्थिर_ranges[] = अणु
	regmap_reg_range(DA9063_REG_PAGE_CON, DA9063_REG_EVENT_D),
	regmap_reg_range(DA9063_REG_CONTROL_A, DA9063_REG_CONTROL_B),
	regmap_reg_range(DA9063_REG_CONTROL_E, DA9063_REG_CONTROL_F),
	regmap_reg_range(DA9063_REG_BCORE2_CONT, DA9063_REG_LDO11_CONT),
	regmap_reg_range(DA9063_REG_DVC_1, DA9063_REG_ADC_MAN),
	regmap_reg_range(DA9063_REG_ADC_RES_L, DA9063_BB_REG_SECOND_D),
	regmap_reg_range(DA9063_REG_SEQ, DA9063_REG_SEQ),
	regmap_reg_range(DA9063_REG_EN_32K, DA9063_REG_EN_32K),
	regmap_reg_range(DA9063_BB_REG_MON_REG_5, DA9063_BB_REG_MON_REG_6),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table da9063_bb_पढ़ोable_table = अणु
	.yes_ranges = da9063_bb_पढ़ोable_ranges,
	.n_yes_ranges = ARRAY_SIZE(da9063_bb_पढ़ोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table da9063_bb_ग_लिखोable_table = अणु
	.yes_ranges = da9063_bb_ग_लिखोable_ranges,
	.n_yes_ranges = ARRAY_SIZE(da9063_bb_ग_लिखोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table da9063_bb_da_अस्थिर_table = अणु
	.yes_ranges = da9063_bb_da_अस्थिर_ranges,
	.n_yes_ranges = ARRAY_SIZE(da9063_bb_da_अस्थिर_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range da9063l_bb_पढ़ोable_ranges[] = अणु
	regmap_reg_range(DA9063_REG_PAGE_CON, DA9063_REG_MON_A10_RES),
	regmap_reg_range(DA9063_REG_SEQ, DA9063_REG_ID_32_31),
	regmap_reg_range(DA9063_REG_SEQ_A, DA9063_REG_AUTO3_LOW),
	regmap_reg_range(DA9063_REG_T_OFFSET, DA9063_BB_REG_GP_ID_19),
	regmap_reg_range(DA9063_REG_DEVICE_ID, DA9063_REG_VARIANT_ID),
पूर्ण;

अटल स्थिर काष्ठा regmap_range da9063l_bb_ग_लिखोable_ranges[] = अणु
	regmap_reg_range(DA9063_REG_PAGE_CON, DA9063_REG_PAGE_CON),
	regmap_reg_range(DA9063_REG_FAULT_LOG, DA9063_REG_VSYS_MON),
	regmap_reg_range(DA9063_REG_SEQ, DA9063_REG_ID_32_31),
	regmap_reg_range(DA9063_REG_SEQ_A, DA9063_REG_AUTO3_LOW),
	regmap_reg_range(DA9063_REG_CONFIG_I, DA9063_BB_REG_MON_REG_4),
	regmap_reg_range(DA9063_BB_REG_GP_ID_0, DA9063_BB_REG_GP_ID_19),
पूर्ण;

अटल स्थिर काष्ठा regmap_range da9063l_bb_da_अस्थिर_ranges[] = अणु
	regmap_reg_range(DA9063_REG_PAGE_CON, DA9063_REG_EVENT_D),
	regmap_reg_range(DA9063_REG_CONTROL_A, DA9063_REG_CONTROL_B),
	regmap_reg_range(DA9063_REG_CONTROL_E, DA9063_REG_CONTROL_F),
	regmap_reg_range(DA9063_REG_BCORE2_CONT, DA9063_REG_LDO11_CONT),
	regmap_reg_range(DA9063_REG_DVC_1, DA9063_REG_ADC_MAN),
	regmap_reg_range(DA9063_REG_ADC_RES_L, DA9063_REG_MON_A10_RES),
	regmap_reg_range(DA9063_REG_SEQ, DA9063_REG_SEQ),
	regmap_reg_range(DA9063_REG_EN_32K, DA9063_REG_EN_32K),
	regmap_reg_range(DA9063_BB_REG_MON_REG_5, DA9063_BB_REG_MON_REG_6),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table da9063l_bb_पढ़ोable_table = अणु
	.yes_ranges = da9063l_bb_पढ़ोable_ranges,
	.n_yes_ranges = ARRAY_SIZE(da9063l_bb_पढ़ोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table da9063l_bb_ग_लिखोable_table = अणु
	.yes_ranges = da9063l_bb_ग_लिखोable_ranges,
	.n_yes_ranges = ARRAY_SIZE(da9063l_bb_ग_लिखोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table da9063l_bb_da_अस्थिर_table = अणु
	.yes_ranges = da9063l_bb_da_अस्थिर_ranges,
	.n_yes_ranges = ARRAY_SIZE(da9063l_bb_da_अस्थिर_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range da9063_da_पढ़ोable_ranges[] = अणु
	regmap_reg_range(DA9063_REG_PAGE_CON, DA9063_BB_REG_SECOND_D),
	regmap_reg_range(DA9063_REG_SEQ, DA9063_REG_ID_32_31),
	regmap_reg_range(DA9063_REG_SEQ_A, DA9063_REG_AUTO3_LOW),
	regmap_reg_range(DA9063_REG_T_OFFSET, DA9063_BB_REG_GP_ID_11),
	regmap_reg_range(DA9063_REG_DEVICE_ID, DA9063_REG_VARIANT_ID),
पूर्ण;

अटल स्थिर काष्ठा regmap_range da9063_da_ग_लिखोable_ranges[] = अणु
	regmap_reg_range(DA9063_REG_PAGE_CON, DA9063_REG_PAGE_CON),
	regmap_reg_range(DA9063_REG_FAULT_LOG, DA9063_REG_VSYS_MON),
	regmap_reg_range(DA9063_REG_COUNT_S, DA9063_BB_REG_ALARM_Y),
	regmap_reg_range(DA9063_REG_SEQ, DA9063_REG_ID_32_31),
	regmap_reg_range(DA9063_REG_SEQ_A, DA9063_REG_AUTO3_LOW),
	regmap_reg_range(DA9063_REG_CONFIG_I, DA9063_BB_REG_MON_REG_4),
	regmap_reg_range(DA9063_BB_REG_GP_ID_0, DA9063_BB_REG_GP_ID_11),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table da9063_da_पढ़ोable_table = अणु
	.yes_ranges = da9063_da_पढ़ोable_ranges,
	.n_yes_ranges = ARRAY_SIZE(da9063_da_पढ़ोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table da9063_da_ग_लिखोable_table = अणु
	.yes_ranges = da9063_da_ग_लिखोable_ranges,
	.n_yes_ranges = ARRAY_SIZE(da9063_da_ग_लिखोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range da9063l_da_पढ़ोable_ranges[] = अणु
	regmap_reg_range(DA9063_REG_PAGE_CON, DA9063_REG_MON_A10_RES),
	regmap_reg_range(DA9063_REG_SEQ, DA9063_REG_ID_32_31),
	regmap_reg_range(DA9063_REG_SEQ_A, DA9063_REG_AUTO3_LOW),
	regmap_reg_range(DA9063_REG_T_OFFSET, DA9063_BB_REG_GP_ID_11),
	regmap_reg_range(DA9063_REG_DEVICE_ID, DA9063_REG_VARIANT_ID),
पूर्ण;

अटल स्थिर काष्ठा regmap_range da9063l_da_ग_लिखोable_ranges[] = अणु
	regmap_reg_range(DA9063_REG_PAGE_CON, DA9063_REG_PAGE_CON),
	regmap_reg_range(DA9063_REG_FAULT_LOG, DA9063_REG_VSYS_MON),
	regmap_reg_range(DA9063_REG_SEQ, DA9063_REG_ID_32_31),
	regmap_reg_range(DA9063_REG_SEQ_A, DA9063_REG_AUTO3_LOW),
	regmap_reg_range(DA9063_REG_CONFIG_I, DA9063_BB_REG_MON_REG_4),
	regmap_reg_range(DA9063_BB_REG_GP_ID_0, DA9063_BB_REG_GP_ID_11),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table da9063l_da_पढ़ोable_table = अणु
	.yes_ranges = da9063l_da_पढ़ोable_ranges,
	.n_yes_ranges = ARRAY_SIZE(da9063l_da_पढ़ोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table da9063l_da_ग_लिखोable_table = अणु
	.yes_ranges = da9063l_da_ग_लिखोable_ranges,
	.n_yes_ranges = ARRAY_SIZE(da9063l_da_ग_लिखोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range_cfg da9063_range_cfg[] = अणु
	अणु
		.range_min = DA9063_REG_PAGE_CON,
		.range_max = DA9063_REG_CONFIG_ID,
		.selector_reg = DA9063_REG_PAGE_CON,
		.selector_mask = 1 << DA9063_I2C_PAGE_SEL_SHIFT,
		.selector_shअगरt = DA9063_I2C_PAGE_SEL_SHIFT,
		.winकरोw_start = 0,
		.winकरोw_len = 256,
	पूर्ण
पूर्ण;

अटल काष्ठा regmap_config da9063_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.ranges = da9063_range_cfg,
	.num_ranges = ARRAY_SIZE(da9063_range_cfg),
	.max_रेजिस्टर = DA9063_REG_CONFIG_ID,

	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id da9063_dt_ids[] = अणु
	अणु .compatible = "dlg,da9063", पूर्ण,
	अणु .compatible = "dlg,da9063l", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, da9063_dt_ids);
अटल पूर्णांक da9063_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा da9063 *da9063;
	पूर्णांक ret;

	da9063 = devm_kzalloc(&i2c->dev, माप(काष्ठा da9063), GFP_KERNEL);
	अगर (da9063 == शून्य)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, da9063);
	da9063->dev = &i2c->dev;
	da9063->chip_irq = i2c->irq;
	da9063->type = id->driver_data;

	ret = da9063_get_device_type(i2c, da9063);
	अगर (ret)
		वापस ret;

	चयन (da9063->type) अणु
	हाल PMIC_TYPE_DA9063:
		चयन (da9063->variant_code) अणु
		हाल PMIC_DA9063_AD:
			da9063_regmap_config.rd_table =
				&da9063_ad_पढ़ोable_table;
			da9063_regmap_config.wr_table =
				&da9063_ad_ग_लिखोable_table;
			da9063_regmap_config.अस्थिर_table =
				&da9063_ad_अस्थिर_table;
			अवरोध;
		हाल PMIC_DA9063_BB:
		हाल PMIC_DA9063_CA:
			da9063_regmap_config.rd_table =
				&da9063_bb_पढ़ोable_table;
			da9063_regmap_config.wr_table =
				&da9063_bb_ग_लिखोable_table;
			da9063_regmap_config.अस्थिर_table =
				&da9063_bb_da_अस्थिर_table;
			अवरोध;
		हाल PMIC_DA9063_DA:
			da9063_regmap_config.rd_table =
				&da9063_da_पढ़ोable_table;
			da9063_regmap_config.wr_table =
				&da9063_da_ग_लिखोable_table;
			da9063_regmap_config.अस्थिर_table =
				&da9063_bb_da_अस्थिर_table;
			अवरोध;
		शेष:
			dev_err(da9063->dev,
				"Chip variant not supported for DA9063\n");
			वापस -ENODEV;
		पूर्ण
		अवरोध;
	हाल PMIC_TYPE_DA9063L:
		चयन (da9063->variant_code) अणु
		हाल PMIC_DA9063_BB:
		हाल PMIC_DA9063_CA:
			da9063_regmap_config.rd_table =
				&da9063l_bb_पढ़ोable_table;
			da9063_regmap_config.wr_table =
				&da9063l_bb_ग_लिखोable_table;
			da9063_regmap_config.अस्थिर_table =
				&da9063l_bb_da_अस्थिर_table;
			अवरोध;
		हाल PMIC_DA9063_DA:
			da9063_regmap_config.rd_table =
				&da9063l_da_पढ़ोable_table;
			da9063_regmap_config.wr_table =
				&da9063l_da_ग_लिखोable_table;
			da9063_regmap_config.अस्थिर_table =
				&da9063l_bb_da_अस्थिर_table;
			अवरोध;
		शेष:
			dev_err(da9063->dev,
				"Chip variant not supported for DA9063L\n");
			वापस -ENODEV;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(da9063->dev, "Chip type not supported\n");
		वापस -ENODEV;
	पूर्ण

	da9063->regmap = devm_regmap_init_i2c(i2c, &da9063_regmap_config);
	अगर (IS_ERR(da9063->regmap)) अणु
		ret = PTR_ERR(da9063->regmap);
		dev_err(da9063->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	/* If SMBus is not available and only I2C is possible, enter I2C mode */
	अगर (i2c_check_functionality(i2c->adapter, I2C_FUNC_I2C)) अणु
		ret = regmap_clear_bits(da9063->regmap, DA9063_REG_CONFIG_J,
					DA9063_TWOWIRE_TO);
		अगर (ret < 0) अणु
			dev_err(da9063->dev, "Failed to set Two-Wire Bus Mode.\n");
			वापस -EIO;
		पूर्ण
	पूर्ण

	वापस da9063_device_init(da9063, i2c->irq);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id da9063_i2c_id[] = अणु
	अणु "da9063", PMIC_TYPE_DA9063 पूर्ण,
	अणु "da9063l", PMIC_TYPE_DA9063L पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, da9063_i2c_id);

अटल काष्ठा i2c_driver da9063_i2c_driver = अणु
	.driver = अणु
		.name = "da9063",
		.of_match_table = da9063_dt_ids,
	पूर्ण,
	.probe    = da9063_i2c_probe,
	.id_table = da9063_i2c_id,
पूर्ण;

module_i2c_driver(da9063_i2c_driver);
