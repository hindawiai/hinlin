<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Core driver access RC5T583 घातer management chip.
 *
 * Copyright (c) 2011-2012, NVIDIA CORPORATION.  All rights reserved.
 * Author: Laxman dewangan <ldewangan@nvidia.com>
 *
 * Based on code
 *	Copyright (C) 2011 RICOH COMPANY,LTD
 */
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/rc5t583.h>
#समावेश <linux/regmap.h>

#घोषणा RICOH_ONOFFSEL_REG	0x10
#घोषणा RICOH_SWCTL_REG		0x5E

काष्ठा deepsleep_control_data अणु
	u8 reg_add;
	u8 ds_pos_bit;
पूर्ण;

#घोषणा DEEPSLEEP_INIT(_id, _reg, _pos)		\
	अणु					\
		.reg_add = RC5T583_##_reg,	\
		.ds_pos_bit = _pos,		\
	पूर्ण

अटल काष्ठा deepsleep_control_data deepsleep_data[] = अणु
	DEEPSLEEP_INIT(DC0, SLPSEQ1, 0),
	DEEPSLEEP_INIT(DC1, SLPSEQ1, 4),
	DEEPSLEEP_INIT(DC2, SLPSEQ2, 0),
	DEEPSLEEP_INIT(DC3, SLPSEQ2, 4),
	DEEPSLEEP_INIT(LDO0, SLPSEQ3, 0),
	DEEPSLEEP_INIT(LDO1, SLPSEQ3, 4),
	DEEPSLEEP_INIT(LDO2, SLPSEQ4, 0),
	DEEPSLEEP_INIT(LDO3, SLPSEQ4, 4),
	DEEPSLEEP_INIT(LDO4, SLPSEQ5, 0),
	DEEPSLEEP_INIT(LDO5, SLPSEQ5, 4),
	DEEPSLEEP_INIT(LDO6, SLPSEQ6, 0),
	DEEPSLEEP_INIT(LDO7, SLPSEQ6, 4),
	DEEPSLEEP_INIT(LDO8, SLPSEQ7, 0),
	DEEPSLEEP_INIT(LDO9, SLPSEQ7, 4),
	DEEPSLEEP_INIT(PSO0, SLPSEQ8, 0),
	DEEPSLEEP_INIT(PSO1, SLPSEQ8, 4),
	DEEPSLEEP_INIT(PSO2, SLPSEQ9, 0),
	DEEPSLEEP_INIT(PSO3, SLPSEQ9, 4),
	DEEPSLEEP_INIT(PSO4, SLPSEQ10, 0),
	DEEPSLEEP_INIT(PSO5, SLPSEQ10, 4),
	DEEPSLEEP_INIT(PSO6, SLPSEQ11, 0),
	DEEPSLEEP_INIT(PSO7, SLPSEQ11, 4),
पूर्ण;

#घोषणा EXT_PWR_REQ		\
	(RC5T583_EXT_PWRREQ1_CONTROL | RC5T583_EXT_PWRREQ2_CONTROL)

अटल स्थिर काष्ठा mfd_cell rc5t583_subdevs[] = अणु
	अणु.name = "rc5t583-gpio",पूर्ण,
	अणु.name = "rc5t583-regulator",पूर्ण,
	अणु.name = "rc5t583-rtc",      पूर्ण,
	अणु.name = "rc5t583-key",      पूर्ण
पूर्ण;

अटल पूर्णांक __rc5t583_set_ext_pwrreq1_control(काष्ठा device *dev,
	पूर्णांक id, पूर्णांक ext_pwr, पूर्णांक slots)
अणु
	पूर्णांक ret;
	uपूर्णांक8_t sleepseq_val = 0;
	अचिन्हित पूर्णांक en_bit;
	अचिन्हित पूर्णांक slot_bit;

	अगर (id == RC5T583_DS_DC0) अणु
		dev_err(dev, "PWRREQ1 is invalid control for rail %d\n", id);
		वापस -EINVAL;
	पूर्ण

	en_bit = deepsleep_data[id].ds_pos_bit;
	slot_bit = en_bit + 1;
	ret = rc5t583_पढ़ो(dev, deepsleep_data[id].reg_add, &sleepseq_val);
	अगर (ret < 0) अणु
		dev_err(dev, "Error in reading reg 0x%x\n",
				deepsleep_data[id].reg_add);
		वापस ret;
	पूर्ण

	sleepseq_val &= ~(0xF << en_bit);
	sleepseq_val |= BIT(en_bit);
	sleepseq_val |= ((slots & 0x7) << slot_bit);
	ret = rc5t583_set_bits(dev, RICOH_ONOFFSEL_REG, BIT(1));
	अगर (ret < 0) अणु
		dev_err(dev, "Error in updating the 0x%02x register\n",
				RICOH_ONOFFSEL_REG);
		वापस ret;
	पूर्ण

	ret = rc5t583_ग_लिखो(dev, deepsleep_data[id].reg_add, sleepseq_val);
	अगर (ret < 0) अणु
		dev_err(dev, "Error in writing reg 0x%x\n",
				deepsleep_data[id].reg_add);
		वापस ret;
	पूर्ण

	अगर (id == RC5T583_DS_LDO4) अणु
		ret = rc5t583_ग_लिखो(dev, RICOH_SWCTL_REG, 0x1);
		अगर (ret < 0)
			dev_err(dev, "Error in writing reg 0x%x\n",
				RICOH_SWCTL_REG);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक __rc5t583_set_ext_pwrreq2_control(काष्ठा device *dev,
	पूर्णांक id, पूर्णांक ext_pwr)
अणु
	पूर्णांक ret;

	अगर (id != RC5T583_DS_DC0) अणु
		dev_err(dev, "PWRREQ2 is invalid control for rail %d\n", id);
		वापस -EINVAL;
	पूर्ण

	ret = rc5t583_set_bits(dev, RICOH_ONOFFSEL_REG, BIT(2));
	अगर (ret < 0)
		dev_err(dev, "Error in updating the ONOFFSEL 0x10 register\n");
	वापस ret;
पूर्ण

पूर्णांक rc5t583_ext_घातer_req_config(काष्ठा device *dev, पूर्णांक ds_id,
	पूर्णांक ext_pwr_req, पूर्णांक deepsleep_slot_nr)
अणु
	अगर ((ext_pwr_req & EXT_PWR_REQ) == EXT_PWR_REQ)
		वापस -EINVAL;

	अगर (ext_pwr_req & RC5T583_EXT_PWRREQ1_CONTROL)
		वापस __rc5t583_set_ext_pwrreq1_control(dev, ds_id,
				ext_pwr_req, deepsleep_slot_nr);

	अगर (ext_pwr_req & RC5T583_EXT_PWRREQ2_CONTROL)
		वापस __rc5t583_set_ext_pwrreq2_control(dev,
			ds_id, ext_pwr_req);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(rc5t583_ext_घातer_req_config);

अटल पूर्णांक rc5t583_clear_ext_घातer_req(काष्ठा rc5t583 *rc5t583,
	काष्ठा rc5t583_platक्रमm_data *pdata)
अणु
	पूर्णांक ret;
	पूर्णांक i;
	uपूर्णांक8_t on_off_val = 0;

	/*  Clear ONOFFSEL रेजिस्टर */
	अगर (pdata->enable_shutकरोwn)
		on_off_val = 0x1;

	ret = rc5t583_ग_लिखो(rc5t583->dev, RICOH_ONOFFSEL_REG, on_off_val);
	अगर (ret < 0)
		dev_warn(rc5t583->dev, "Error in writing reg %d error: %d\n",
					RICOH_ONOFFSEL_REG, ret);

	ret = rc5t583_ग_लिखो(rc5t583->dev, RICOH_SWCTL_REG, 0x0);
	अगर (ret < 0)
		dev_warn(rc5t583->dev, "Error in writing reg %d error: %d\n",
					RICOH_SWCTL_REG, ret);

	/* Clear sleep sequence रेजिस्टर */
	क्रम (i = RC5T583_SLPSEQ1; i <= RC5T583_SLPSEQ11; ++i) अणु
		ret = rc5t583_ग_लिखो(rc5t583->dev, i, 0x0);
		अगर (ret < 0)
			dev_warn(rc5t583->dev,
				"Error in writing reg 0x%02x error: %d\n",
				i, ret);
	पूर्ण
	वापस 0;
पूर्ण

अटल bool अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	/* Enable caching in पूर्णांकerrupt रेजिस्टरs */
	चयन (reg) अणु
	हाल RC5T583_INT_EN_SYS1:
	हाल RC5T583_INT_EN_SYS2:
	हाल RC5T583_INT_EN_DCDC:
	हाल RC5T583_INT_EN_RTC:
	हाल RC5T583_INT_EN_ADC1:
	हाल RC5T583_INT_EN_ADC2:
	हाल RC5T583_INT_EN_ADC3:
	हाल RC5T583_GPIO_GPEDGE1:
	हाल RC5T583_GPIO_GPEDGE2:
	हाल RC5T583_GPIO_EN_INT:
		वापस false;

	हाल RC5T583_GPIO_MON_IOIN:
		/* This is gpio input रेजिस्टर */
		वापस true;

	शेष:
		/* Enable caching in gpio रेजिस्टरs */
		अगर ((reg >= RC5T583_GPIO_IOSEL) &&
				(reg <= RC5T583_GPIO_GPOFUNC))
			वापस false;

		/* Enable caching in sleep seq रेजिस्टरs */
		अगर ((reg >= RC5T583_SLPSEQ1) && (reg <= RC5T583_SLPSEQ11))
			वापस false;

		/* Enable caching of regulator रेजिस्टरs */
		अगर ((reg >= RC5T583_REG_DC0CTL) && (reg <= RC5T583_REG_SR3CTL))
			वापस false;
		अगर ((reg >= RC5T583_REG_LDOEN1) &&
					(reg <= RC5T583_REG_LDO9DAC_DS))
			वापस false;

		अवरोध;
	पूर्ण

	वापस true;
पूर्ण

अटल स्थिर काष्ठा regmap_config rc5t583_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.अस्थिर_reg = अस्थिर_reg,
	.max_रेजिस्टर = RC5T583_MAX_REG,
	.num_reg_शेषs_raw = RC5T583_NUM_REGS,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक rc5t583_i2c_probe(काष्ठा i2c_client *i2c,
			      स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा rc5t583 *rc5t583;
	काष्ठा rc5t583_platक्रमm_data *pdata = dev_get_platdata(&i2c->dev);
	पूर्णांक ret;

	अगर (!pdata) अणु
		dev_err(&i2c->dev, "Err: Platform data not found\n");
		वापस -EINVAL;
	पूर्ण

	rc5t583 = devm_kzalloc(&i2c->dev, माप(*rc5t583), GFP_KERNEL);
	अगर (!rc5t583)
		वापस -ENOMEM;

	rc5t583->dev = &i2c->dev;
	i2c_set_clientdata(i2c, rc5t583);

	rc5t583->regmap = devm_regmap_init_i2c(i2c, &rc5t583_regmap_config);
	अगर (IS_ERR(rc5t583->regmap)) अणु
		ret = PTR_ERR(rc5t583->regmap);
		dev_err(&i2c->dev, "regmap initialization failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = rc5t583_clear_ext_घातer_req(rc5t583, pdata);
	अगर (ret < 0)
		वापस ret;

	अगर (i2c->irq) अणु
		ret = rc5t583_irq_init(rc5t583, i2c->irq, pdata->irq_base);
		/* Still जारी with warning, अगर irq init fails */
		अगर (ret)
			dev_warn(&i2c->dev, "IRQ init failed: %d\n", ret);
	पूर्ण

	ret = devm_mfd_add_devices(rc5t583->dev, -1, rc5t583_subdevs,
				   ARRAY_SIZE(rc5t583_subdevs), शून्य, 0, शून्य);
	अगर (ret) अणु
		dev_err(&i2c->dev, "add mfd devices failed: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id rc5t583_i2c_id[] = अणु
	अणु.name = "rc5t583", .driver_data = 0पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा i2c_driver rc5t583_i2c_driver = अणु
	.driver = अणु
		   .name = "rc5t583",
		   पूर्ण,
	.probe = rc5t583_i2c_probe,
	.id_table = rc5t583_i2c_id,
पूर्ण;

अटल पूर्णांक __init rc5t583_i2c_init(व्योम)
अणु
	वापस i2c_add_driver(&rc5t583_i2c_driver);
पूर्ण
subsys_initcall(rc5t583_i2c_init);
