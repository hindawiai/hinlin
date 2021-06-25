<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DA9150 Core MFD Driver
 *
 * Copyright (c) 2014 Dialog Semiconductor
 *
 * Author: Adam Thomson <Adam.Thomson.Opensource@diasemi.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/da9150/core.h>
#समावेश <linux/mfd/da9150/रेजिस्टरs.h>

/* Raw device access, used क्रम QIF */
अटल पूर्णांक da9150_i2c_पढ़ो_device(काष्ठा i2c_client *client, u8 addr, पूर्णांक count,
				  u8 *buf)
अणु
	काष्ठा i2c_msg xfer;
	पूर्णांक ret;

	/*
	 * Read is split पूर्णांकo two transfers as device expects STOP/START rather
	 * than repeated start to carry out this kind of access.
	 */

	/* Write address */
	xfer.addr = client->addr;
	xfer.flags = 0;
	xfer.len = 1;
	xfer.buf = &addr;

	ret = i2c_transfer(client->adapter, &xfer, 1);
	अगर (ret != 1) अणु
		अगर (ret < 0)
			वापस ret;
		अन्यथा
			वापस -EIO;
	पूर्ण

	/* Read data */
	xfer.addr = client->addr;
	xfer.flags = I2C_M_RD;
	xfer.len = count;
	xfer.buf = buf;

	ret = i2c_transfer(client->adapter, &xfer, 1);
	अगर (ret == 1)
		वापस 0;
	अन्यथा अगर (ret < 0)
		वापस ret;
	अन्यथा
		वापस -EIO;
पूर्ण

अटल पूर्णांक da9150_i2c_ग_लिखो_device(काष्ठा i2c_client *client, u8 addr,
				   पूर्णांक count, स्थिर u8 *buf)
अणु
	काष्ठा i2c_msg xfer;
	u8 *reg_data;
	पूर्णांक ret;

	reg_data = kzalloc(1 + count, GFP_KERNEL);
	अगर (!reg_data)
		वापस -ENOMEM;

	reg_data[0] = addr;
	स_नकल(&reg_data[1], buf, count);

	/* Write address & data */
	xfer.addr = client->addr;
	xfer.flags = 0;
	xfer.len = 1 + count;
	xfer.buf = reg_data;

	ret = i2c_transfer(client->adapter, &xfer, 1);
	kमुक्त(reg_data);
	अगर (ret == 1)
		वापस 0;
	अन्यथा अगर (ret < 0)
		वापस ret;
	अन्यथा
		वापस -EIO;
पूर्ण

अटल bool da9150_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल DA9150_PAGE_CON:
	हाल DA9150_STATUS_A:
	हाल DA9150_STATUS_B:
	हाल DA9150_STATUS_C:
	हाल DA9150_STATUS_D:
	हाल DA9150_STATUS_E:
	हाल DA9150_STATUS_F:
	हाल DA9150_STATUS_G:
	हाल DA9150_STATUS_H:
	हाल DA9150_STATUS_I:
	हाल DA9150_STATUS_J:
	हाल DA9150_STATUS_K:
	हाल DA9150_STATUS_L:
	हाल DA9150_STATUS_N:
	हाल DA9150_FAULT_LOG_A:
	हाल DA9150_FAULT_LOG_B:
	हाल DA9150_EVENT_E:
	हाल DA9150_EVENT_F:
	हाल DA9150_EVENT_G:
	हाल DA9150_EVENT_H:
	हाल DA9150_CONTROL_B:
	हाल DA9150_CONTROL_C:
	हाल DA9150_GPADC_MAN:
	हाल DA9150_GPADC_RES_A:
	हाल DA9150_GPADC_RES_B:
	हाल DA9150_ADETVB_CFG_C:
	हाल DA9150_ADETD_STAT:
	हाल DA9150_ADET_CMPSTAT:
	हाल DA9150_ADET_CTRL_A:
	हाल DA9150_PPR_TCTR_B:
	हाल DA9150_COREBTLD_STAT_A:
	हाल DA9150_CORE_DATA_A:
	हाल DA9150_CORE_DATA_B:
	हाल DA9150_CORE_DATA_C:
	हाल DA9150_CORE_DATA_D:
	हाल DA9150_CORE2WIRE_STAT_A:
	हाल DA9150_FW_CTRL_C:
	हाल DA9150_FG_CTRL_B:
	हाल DA9150_FW_CTRL_B:
	हाल DA9150_GPADC_CMAN:
	हाल DA9150_GPADC_CRES_A:
	हाल DA9150_GPADC_CRES_B:
	हाल DA9150_CC_ICHG_RES_A:
	हाल DA9150_CC_ICHG_RES_B:
	हाल DA9150_CC_IAVG_RES_A:
	हाल DA9150_CC_IAVG_RES_B:
	हाल DA9150_TAUX_CTRL_A:
	हाल DA9150_TAUX_VALUE_H:
	हाल DA9150_TAUX_VALUE_L:
	हाल DA9150_TBAT_RES_A:
	हाल DA9150_TBAT_RES_B:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_range_cfg da9150_range_cfg[] = अणु
	अणु
		.range_min = DA9150_PAGE_CON,
		.range_max = DA9150_TBAT_RES_B,
		.selector_reg = DA9150_PAGE_CON,
		.selector_mask = DA9150_I2C_PAGE_MASK,
		.selector_shअगरt = DA9150_I2C_PAGE_SHIFT,
		.winकरोw_start = 0,
		.winकरोw_len = 256,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config da9150_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.ranges = da9150_range_cfg,
	.num_ranges = ARRAY_SIZE(da9150_range_cfg),
	.max_रेजिस्टर = DA9150_TBAT_RES_B,

	.cache_type = REGCACHE_RBTREE,

	.अस्थिर_reg = da9150_अस्थिर_reg,
पूर्ण;

व्योम da9150_पढ़ो_qअगर(काष्ठा da9150 *da9150, u8 addr, पूर्णांक count, u8 *buf)
अणु
	पूर्णांक ret;

	ret = da9150_i2c_पढ़ो_device(da9150->core_qअगर, addr, count, buf);
	अगर (ret < 0)
		dev_err(da9150->dev, "Failed to read from QIF 0x%x: %d\n",
			addr, ret);
पूर्ण
EXPORT_SYMBOL_GPL(da9150_पढ़ो_qअगर);

व्योम da9150_ग_लिखो_qअगर(काष्ठा da9150 *da9150, u8 addr, पूर्णांक count, स्थिर u8 *buf)
अणु
	पूर्णांक ret;

	ret = da9150_i2c_ग_लिखो_device(da9150->core_qअगर, addr, count, buf);
	अगर (ret < 0)
		dev_err(da9150->dev, "Failed to write to QIF 0x%x: %d\n",
			addr, ret);
पूर्ण
EXPORT_SYMBOL_GPL(da9150_ग_लिखो_qअगर);

u8 da9150_reg_पढ़ो(काष्ठा da9150 *da9150, u16 reg)
अणु
	पूर्णांक val, ret;

	ret = regmap_पढ़ो(da9150->regmap, reg, &val);
	अगर (ret)
		dev_err(da9150->dev, "Failed to read from reg 0x%x: %d\n",
			reg, ret);

	वापस (u8) val;
पूर्ण
EXPORT_SYMBOL_GPL(da9150_reg_पढ़ो);

व्योम da9150_reg_ग_लिखो(काष्ठा da9150 *da9150, u16 reg, u8 val)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(da9150->regmap, reg, val);
	अगर (ret)
		dev_err(da9150->dev, "Failed to write to reg 0x%x: %d\n",
			reg, ret);
पूर्ण
EXPORT_SYMBOL_GPL(da9150_reg_ग_लिखो);

व्योम da9150_set_bits(काष्ठा da9150 *da9150, u16 reg, u8 mask, u8 val)
अणु
	पूर्णांक ret;

	ret = regmap_update_bits(da9150->regmap, reg, mask, val);
	अगर (ret)
		dev_err(da9150->dev, "Failed to set bits in reg 0x%x: %d\n",
			reg, ret);
पूर्ण
EXPORT_SYMBOL_GPL(da9150_set_bits);

व्योम da9150_bulk_पढ़ो(काष्ठा da9150 *da9150, u16 reg, पूर्णांक count, u8 *buf)
अणु
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(da9150->regmap, reg, buf, count);
	अगर (ret)
		dev_err(da9150->dev, "Failed to bulk read from reg 0x%x: %d\n",
			reg, ret);
पूर्ण
EXPORT_SYMBOL_GPL(da9150_bulk_पढ़ो);

व्योम da9150_bulk_ग_लिखो(काष्ठा da9150 *da9150, u16 reg, पूर्णांक count, स्थिर u8 *buf)
अणु
	पूर्णांक ret;

	ret = regmap_raw_ग_लिखो(da9150->regmap, reg, buf, count);
	अगर (ret)
		dev_err(da9150->dev, "Failed to bulk write to reg 0x%x %d\n",
			reg, ret);
पूर्ण
EXPORT_SYMBOL_GPL(da9150_bulk_ग_लिखो);

अटल स्थिर काष्ठा regmap_irq da9150_irqs[] = अणु
	[DA9150_IRQ_VBUS] = अणु
		.reg_offset = 0,
		.mask = DA9150_E_VBUS_MASK,
	पूर्ण,
	[DA9150_IRQ_CHG] = अणु
		.reg_offset = 0,
		.mask = DA9150_E_CHG_MASK,
	पूर्ण,
	[DA9150_IRQ_TCLASS] = अणु
		.reg_offset = 0,
		.mask = DA9150_E_TCLASS_MASK,
	पूर्ण,
	[DA9150_IRQ_TJUNC] = अणु
		.reg_offset = 0,
		.mask = DA9150_E_TJUNC_MASK,
	पूर्ण,
	[DA9150_IRQ_VFAULT] = अणु
		.reg_offset = 0,
		.mask = DA9150_E_VFAULT_MASK,
	पूर्ण,
	[DA9150_IRQ_CONF] = अणु
		.reg_offset = 1,
		.mask = DA9150_E_CONF_MASK,
	पूर्ण,
	[DA9150_IRQ_DAT] = अणु
		.reg_offset = 1,
		.mask = DA9150_E_DAT_MASK,
	पूर्ण,
	[DA9150_IRQ_DTYPE] = अणु
		.reg_offset = 1,
		.mask = DA9150_E_DTYPE_MASK,
	पूर्ण,
	[DA9150_IRQ_ID] = अणु
		.reg_offset = 1,
		.mask = DA9150_E_ID_MASK,
	पूर्ण,
	[DA9150_IRQ_ADP] = अणु
		.reg_offset = 1,
		.mask = DA9150_E_ADP_MASK,
	पूर्ण,
	[DA9150_IRQ_SESS_END] = अणु
		.reg_offset = 1,
		.mask = DA9150_E_SESS_END_MASK,
	पूर्ण,
	[DA9150_IRQ_SESS_VLD] = अणु
		.reg_offset = 1,
		.mask = DA9150_E_SESS_VLD_MASK,
	पूर्ण,
	[DA9150_IRQ_FG] = अणु
		.reg_offset = 2,
		.mask = DA9150_E_FG_MASK,
	पूर्ण,
	[DA9150_IRQ_GP] = अणु
		.reg_offset = 2,
		.mask = DA9150_E_GP_MASK,
	पूर्ण,
	[DA9150_IRQ_TBAT] = अणु
		.reg_offset = 2,
		.mask = DA9150_E_TBAT_MASK,
	पूर्ण,
	[DA9150_IRQ_GPIOA] = अणु
		.reg_offset = 2,
		.mask = DA9150_E_GPIOA_MASK,
	पूर्ण,
	[DA9150_IRQ_GPIOB] = अणु
		.reg_offset = 2,
		.mask = DA9150_E_GPIOB_MASK,
	पूर्ण,
	[DA9150_IRQ_GPIOC] = अणु
		.reg_offset = 2,
		.mask = DA9150_E_GPIOC_MASK,
	पूर्ण,
	[DA9150_IRQ_GPIOD] = अणु
		.reg_offset = 2,
		.mask = DA9150_E_GPIOD_MASK,
	पूर्ण,
	[DA9150_IRQ_GPADC] = अणु
		.reg_offset = 2,
		.mask = DA9150_E_GPADC_MASK,
	पूर्ण,
	[DA9150_IRQ_WKUP] = अणु
		.reg_offset = 3,
		.mask = DA9150_E_WKUP_MASK,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip da9150_regmap_irq_chip = अणु
	.name = "da9150_irq",
	.status_base = DA9150_EVENT_E,
	.mask_base = DA9150_IRQ_MASK_E,
	.ack_base = DA9150_EVENT_E,
	.num_regs = DA9150_NUM_IRQ_REGS,
	.irqs = da9150_irqs,
	.num_irqs = ARRAY_SIZE(da9150_irqs),
पूर्ण;

अटल स्थिर काष्ठा resource da9150_gpadc_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(DA9150_IRQ_GPADC, "GPADC"),
पूर्ण;

अटल स्थिर काष्ठा resource da9150_अक्षरger_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(DA9150_IRQ_CHG, "CHG_STATUS"),
	DEFINE_RES_IRQ_NAMED(DA9150_IRQ_TJUNC, "CHG_TJUNC"),
	DEFINE_RES_IRQ_NAMED(DA9150_IRQ_VFAULT, "CHG_VFAULT"),
	DEFINE_RES_IRQ_NAMED(DA9150_IRQ_VBUS, "CHG_VBUS"),
पूर्ण;

अटल स्थिर काष्ठा resource da9150_fg_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(DA9150_IRQ_FG, "FG"),
पूर्ण;

क्रमागत da9150_dev_idx अणु
	DA9150_GPADC_IDX = 0,
	DA9150_CHARGER_IDX,
	DA9150_FG_IDX,
पूर्ण;

अटल काष्ठा mfd_cell da9150_devs[] = अणु
	[DA9150_GPADC_IDX] = अणु
		.name = "da9150-gpadc",
		.of_compatible = "dlg,da9150-gpadc",
		.resources = da9150_gpadc_resources,
		.num_resources = ARRAY_SIZE(da9150_gpadc_resources),
	पूर्ण,
	[DA9150_CHARGER_IDX] = अणु
		.name = "da9150-charger",
		.of_compatible = "dlg,da9150-charger",
		.resources = da9150_अक्षरger_resources,
		.num_resources = ARRAY_SIZE(da9150_अक्षरger_resources),
	पूर्ण,
	[DA9150_FG_IDX] = अणु
		.name = "da9150-fuel-gauge",
		.of_compatible = "dlg,da9150-fuel-gauge",
		.resources = da9150_fg_resources,
		.num_resources = ARRAY_SIZE(da9150_fg_resources),
	पूर्ण,
पूर्ण;

अटल पूर्णांक da9150_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा da9150 *da9150;
	काष्ठा da9150_pdata *pdata = dev_get_platdata(&client->dev);
	पूर्णांक qअगर_addr;
	पूर्णांक ret;

	da9150 = devm_kzalloc(&client->dev, माप(*da9150), GFP_KERNEL);
	अगर (!da9150)
		वापस -ENOMEM;

	da9150->dev = &client->dev;
	da9150->irq = client->irq;
	i2c_set_clientdata(client, da9150);

	da9150->regmap = devm_regmap_init_i2c(client, &da9150_regmap_config);
	अगर (IS_ERR(da9150->regmap)) अणु
		ret = PTR_ERR(da9150->regmap);
		dev_err(da9150->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	/* Setup secondary I2C पूर्णांकerface क्रम QIF access */
	qअगर_addr = da9150_reg_पढ़ो(da9150, DA9150_CORE2WIRE_CTRL_A);
	qअगर_addr = (qअगर_addr & DA9150_CORE_BASE_ADDR_MASK) >> 1;
	qअगर_addr |= DA9150_QIF_I2C_ADDR_LSB;
	da9150->core_qअगर = i2c_new_dummy_device(client->adapter, qअगर_addr);
	अगर (IS_ERR(da9150->core_qअगर)) अणु
		dev_err(da9150->dev, "Failed to attach QIF client\n");
		वापस PTR_ERR(da9150->core_qअगर);
	पूर्ण

	i2c_set_clientdata(da9150->core_qअगर, da9150);

	अगर (pdata) अणु
		da9150->irq_base = pdata->irq_base;

		da9150_devs[DA9150_FG_IDX].platक्रमm_data = pdata->fg_pdata;
		da9150_devs[DA9150_FG_IDX].pdata_size =
			माप(काष्ठा da9150_fg_pdata);
	पूर्ण अन्यथा अणु
		da9150->irq_base = -1;
	पूर्ण

	ret = regmap_add_irq_chip(da9150->regmap, da9150->irq,
				  IRQF_TRIGGER_LOW | IRQF_ONESHOT,
				  da9150->irq_base, &da9150_regmap_irq_chip,
				  &da9150->regmap_irq_data);
	अगर (ret) अणु
		dev_err(da9150->dev, "Failed to add regmap irq chip: %d\n",
			ret);
		जाओ regmap_irq_fail;
	पूर्ण


	da9150->irq_base = regmap_irq_chip_get_base(da9150->regmap_irq_data);

	enable_irq_wake(da9150->irq);

	ret = mfd_add_devices(da9150->dev, -1, da9150_devs,
			      ARRAY_SIZE(da9150_devs), शून्य,
			      da9150->irq_base, शून्य);
	अगर (ret) अणु
		dev_err(da9150->dev, "Failed to add child devices: %d\n", ret);
		जाओ mfd_fail;
	पूर्ण

	वापस 0;

mfd_fail:
	regmap_del_irq_chip(da9150->irq, da9150->regmap_irq_data);
regmap_irq_fail:
	i2c_unरेजिस्टर_device(da9150->core_qअगर);

	वापस ret;
पूर्ण

अटल पूर्णांक da9150_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा da9150 *da9150 = i2c_get_clientdata(client);

	regmap_del_irq_chip(da9150->irq, da9150->regmap_irq_data);
	mfd_हटाओ_devices(da9150->dev);
	i2c_unरेजिस्टर_device(da9150->core_qअगर);

	वापस 0;
पूर्ण

अटल व्योम da9150_shutकरोwn(काष्ठा i2c_client *client)
अणु
	काष्ठा da9150 *da9150 = i2c_get_clientdata(client);

	/* Make sure we have a wakup source क्रम the device */
	da9150_set_bits(da9150, DA9150_CONFIG_D,
			DA9150_WKUP_PM_EN_MASK,
			DA9150_WKUP_PM_EN_MASK);

	/* Set device to DISABLED mode */
	da9150_set_bits(da9150, DA9150_CONTROL_C,
			DA9150_DISABLE_MASK, DA9150_DISABLE_MASK);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id da9150_i2c_id[] = अणु
	अणु "da9150", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, da9150_i2c_id);

अटल स्थिर काष्ठा of_device_id da9150_of_match[] = अणु
	अणु .compatible = "dlg,da9150", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, da9150_of_match);

अटल काष्ठा i2c_driver da9150_driver = अणु
	.driver	= अणु
		.name	= "da9150",
		.of_match_table = da9150_of_match,
	पूर्ण,
	.probe		= da9150_probe,
	.हटाओ		= da9150_हटाओ,
	.shutकरोwn	= da9150_shutकरोwn,
	.id_table	= da9150_i2c_id,
पूर्ण;

module_i2c_driver(da9150_driver);

MODULE_DESCRIPTION("MFD Core Driver for DA9150");
MODULE_AUTHOR("Adam Thomson <Adam.Thomson.Opensource@diasemi.com>");
MODULE_LICENSE("GPL");
