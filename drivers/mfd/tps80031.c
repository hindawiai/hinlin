<शैली गुरु>
/*
 * tps80031.c -- TI TPS80031/TPS80032 mfd core driver.
 *
 * MFD core driver क्रम TI TPS80031/TPS80032 Fully Integrated
 * Power Management with Power Path and Battery Charger
 *
 * Copyright (c) 2012, NVIDIA Corporation.
 *
 * Author: Laxman Dewangan <ldewangan@nvidia.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any kind,
 * whether express or implied; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307, USA
 */

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/tps80031.h>
#समावेश <linux/pm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

अटल स्थिर काष्ठा resource tps80031_rtc_resources[] = अणु
	अणु
		.start = TPS80031_INT_RTC_ALARM,
		.end = TPS80031_INT_RTC_ALARM,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

/* TPS80031 sub mfd devices */
अटल स्थिर काष्ठा mfd_cell tps80031_cell[] = अणु
	अणु
		.name = "tps80031-pmic",
	पूर्ण,
	अणु
		.name = "tps80031-clock",
	पूर्ण,
	अणु
		.name = "tps80031-rtc",
		.num_resources = ARRAY_SIZE(tps80031_rtc_resources),
		.resources = tps80031_rtc_resources,
	पूर्ण,
	अणु
		.name = "tps80031-gpadc",
	पूर्ण,
	अणु
		.name = "tps80031-fuel-gauge",
	पूर्ण,
	अणु
		.name = "tps80031-charger",
	पूर्ण,
पूर्ण;

अटल पूर्णांक tps80031_slave_address[TPS80031_NUM_SLAVES] = अणु
	TPS80031_I2C_ID0_ADDR,
	TPS80031_I2C_ID1_ADDR,
	TPS80031_I2C_ID2_ADDR,
	TPS80031_I2C_ID3_ADDR,
पूर्ण;

काष्ठा tps80031_pupd_data अणु
	u8	reg;
	u8	pullup_bit;
	u8	pullकरोwn_bit;
पूर्ण;

#घोषणा TPS80031_IRQ(_reg, _mask)			\
	अणु							\
		.reg_offset = (TPS80031_INT_MSK_LINE_##_reg) -	\
				TPS80031_INT_MSK_LINE_A,	\
		.mask = BIT(_mask),				\
	पूर्ण

अटल स्थिर काष्ठा regmap_irq tps80031_मुख्य_irqs[] = अणु
	[TPS80031_INT_PWRON]		= TPS80031_IRQ(A, 0),
	[TPS80031_INT_RPWRON]		= TPS80031_IRQ(A, 1),
	[TPS80031_INT_SYS_VLOW]		= TPS80031_IRQ(A, 2),
	[TPS80031_INT_RTC_ALARM]	= TPS80031_IRQ(A, 3),
	[TPS80031_INT_RTC_PERIOD]	= TPS80031_IRQ(A, 4),
	[TPS80031_INT_HOT_DIE]		= TPS80031_IRQ(A, 5),
	[TPS80031_INT_VXX_SHORT]	= TPS80031_IRQ(A, 6),
	[TPS80031_INT_SPDURATION]	= TPS80031_IRQ(A, 7),
	[TPS80031_INT_WATCHDOG]		= TPS80031_IRQ(B, 0),
	[TPS80031_INT_BAT]		= TPS80031_IRQ(B, 1),
	[TPS80031_INT_SIM]		= TPS80031_IRQ(B, 2),
	[TPS80031_INT_MMC]		= TPS80031_IRQ(B, 3),
	[TPS80031_INT_RES]		= TPS80031_IRQ(B, 4),
	[TPS80031_INT_GPADC_RT]		= TPS80031_IRQ(B, 5),
	[TPS80031_INT_GPADC_SW2_EOC]	= TPS80031_IRQ(B, 6),
	[TPS80031_INT_CC_AUTOCAL]	= TPS80031_IRQ(B, 7),
	[TPS80031_INT_ID_WKUP]		= TPS80031_IRQ(C, 0),
	[TPS80031_INT_VBUSS_WKUP]	= TPS80031_IRQ(C, 1),
	[TPS80031_INT_ID]		= TPS80031_IRQ(C, 2),
	[TPS80031_INT_VBUS]		= TPS80031_IRQ(C, 3),
	[TPS80031_INT_CHRG_CTRL]	= TPS80031_IRQ(C, 4),
	[TPS80031_INT_EXT_CHRG]		= TPS80031_IRQ(C, 5),
	[TPS80031_INT_INT_CHRG]		= TPS80031_IRQ(C, 6),
	[TPS80031_INT_RES2]		= TPS80031_IRQ(C, 7),
पूर्ण;

अटल काष्ठा regmap_irq_chip tps80031_irq_chip = अणु
	.name = "tps80031",
	.irqs = tps80031_मुख्य_irqs,
	.num_irqs = ARRAY_SIZE(tps80031_मुख्य_irqs),
	.num_regs = 3,
	.status_base = TPS80031_INT_STS_A,
	.mask_base = TPS80031_INT_MSK_LINE_A,
पूर्ण;

#घोषणा PUPD_DATA(_reg, _pullकरोwn_bit, _pullup_bit)	\
	अणु						\
		.reg = TPS80031_CFG_INPUT_PUPD##_reg,	\
		.pullकरोwn_bit = _pullकरोwn_bit,		\
		.pullup_bit = _pullup_bit,		\
	पूर्ण

अटल स्थिर काष्ठा tps80031_pupd_data tps80031_pupds[] = अणु
	[TPS80031_PREQ1]		= PUPD_DATA(1, BIT(0),	BIT(1)),
	[TPS80031_PREQ2A]		= PUPD_DATA(1, BIT(2),	BIT(3)),
	[TPS80031_PREQ2B]		= PUPD_DATA(1, BIT(4),	BIT(5)),
	[TPS80031_PREQ2C]		= PUPD_DATA(1, BIT(6),	BIT(7)),
	[TPS80031_PREQ3]		= PUPD_DATA(2, BIT(0),	BIT(1)),
	[TPS80031_NRES_WARM]		= PUPD_DATA(2, 0,	BIT(2)),
	[TPS80031_PWM_FORCE]		= PUPD_DATA(2, BIT(5),	0),
	[TPS80031_CHRG_EXT_CHRG_STATZ]	= PUPD_DATA(2, 0,	BIT(6)),
	[TPS80031_SIM]			= PUPD_DATA(3, BIT(0),	BIT(1)),
	[TPS80031_MMC]			= PUPD_DATA(3, BIT(2),	BIT(3)),
	[TPS80031_GPADC_START]		= PUPD_DATA(3, BIT(4),	0),
	[TPS80031_DVSI2C_SCL]		= PUPD_DATA(4, 0,	BIT(0)),
	[TPS80031_DVSI2C_SDA]		= PUPD_DATA(4, 0,	BIT(1)),
	[TPS80031_CTLI2C_SCL]		= PUPD_DATA(4, 0,	BIT(2)),
	[TPS80031_CTLI2C_SDA]		= PUPD_DATA(4, 0,	BIT(3)),
पूर्ण;
अटल काष्ठा tps80031 *tps80031_घातer_off_dev;

पूर्णांक tps80031_ext_घातer_req_config(काष्ठा device *dev,
		अचिन्हित दीर्घ ext_ctrl_flag, पूर्णांक preq_bit,
		पूर्णांक state_reg_add, पूर्णांक trans_reg_add)
अणु
	u8 res_ass_reg = 0;
	पूर्णांक preq_mask_bit = 0;
	पूर्णांक ret;

	अगर (!(ext_ctrl_flag & TPS80031_EXT_PWR_REQ))
		वापस 0;

	अगर (ext_ctrl_flag & TPS80031_PWR_REQ_INPUT_PREQ1) अणु
		res_ass_reg = TPS80031_PREQ1_RES_ASS_A + (preq_bit >> 3);
		preq_mask_bit = 5;
	पूर्ण अन्यथा अगर (ext_ctrl_flag & TPS80031_PWR_REQ_INPUT_PREQ2) अणु
		res_ass_reg = TPS80031_PREQ2_RES_ASS_A + (preq_bit >> 3);
		preq_mask_bit = 6;
	पूर्ण अन्यथा अगर (ext_ctrl_flag & TPS80031_PWR_REQ_INPUT_PREQ3) अणु
		res_ass_reg = TPS80031_PREQ3_RES_ASS_A + (preq_bit >> 3);
		preq_mask_bit = 7;
	पूर्ण

	/* Configure REQ_ASS रेजिस्टरs */
	ret = tps80031_set_bits(dev, TPS80031_SLAVE_ID1, res_ass_reg,
					BIT(preq_bit & 0x7));
	अगर (ret < 0) अणु
		dev_err(dev, "reg 0x%02x setbit failed, err = %d\n",
				res_ass_reg, ret);
		वापस ret;
	पूर्ण

	/* Unmask the PREQ */
	ret = tps80031_clr_bits(dev, TPS80031_SLAVE_ID1,
			TPS80031_PHOENIX_MSK_TRANSITION, BIT(preq_mask_bit));
	अगर (ret < 0) अणु
		dev_err(dev, "reg 0x%02x clrbit failed, err = %d\n",
			TPS80031_PHOENIX_MSK_TRANSITION, ret);
		वापस ret;
	पूर्ण

	/* Switch regulator control to resource now */
	अगर (ext_ctrl_flag & (TPS80031_PWR_REQ_INPUT_PREQ2 |
					TPS80031_PWR_REQ_INPUT_PREQ3)) अणु
		ret = tps80031_update(dev, TPS80031_SLAVE_ID1, state_reg_add,
						0x0, TPS80031_STATE_MASK);
		अगर (ret < 0)
			dev_err(dev, "reg 0x%02x update failed, err = %d\n",
				state_reg_add, ret);
	पूर्ण अन्यथा अणु
		ret = tps80031_update(dev, TPS80031_SLAVE_ID1, trans_reg_add,
				TPS80031_TRANS_SLEEP_OFF,
				TPS80031_TRANS_SLEEP_MASK);
		अगर (ret < 0)
			dev_err(dev, "reg 0x%02x update failed, err = %d\n",
				trans_reg_add, ret);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(tps80031_ext_घातer_req_config);

अटल व्योम tps80031_घातer_off(व्योम)
अणु
	dev_info(tps80031_घातer_off_dev->dev, "switching off PMU\n");
	tps80031_ग_लिखो(tps80031_घातer_off_dev->dev, TPS80031_SLAVE_ID1,
				TPS80031_PHOENIX_DEV_ON, TPS80031_DEVOFF);
पूर्ण

अटल व्योम tps80031_pupd_init(काष्ठा tps80031 *tps80031,
			       काष्ठा tps80031_platक्रमm_data *pdata)
अणु
	काष्ठा tps80031_pupd_init_data *pupd_init_data = pdata->pupd_init_data;
	पूर्णांक data_size = pdata->pupd_init_data_size;
	पूर्णांक i;

	क्रम (i = 0; i < data_size; ++i) अणु
		काष्ठा tps80031_pupd_init_data *pupd_init = &pupd_init_data[i];
		स्थिर काष्ठा tps80031_pupd_data *pupd =
			&tps80031_pupds[pupd_init->input_pin];
		u8 update_value = 0;
		u8 update_mask = pupd->pullकरोwn_bit | pupd->pullup_bit;

		अगर (pupd_init->setting == TPS80031_PUPD_PULLDOWN)
			update_value = pupd->pullकरोwn_bit;
		अन्यथा अगर (pupd_init->setting == TPS80031_PUPD_PULLUP)
			update_value = pupd->pullup_bit;

		tps80031_update(tps80031->dev, TPS80031_SLAVE_ID1, pupd->reg,
				update_value, update_mask);
	पूर्ण
पूर्ण

अटल पूर्णांक tps80031_init_ext_control(काष्ठा tps80031 *tps80031,
			काष्ठा tps80031_platक्रमm_data *pdata)
अणु
	काष्ठा device *dev = tps80031->dev;
	पूर्णांक ret;
	पूर्णांक i;

	/* Clear all बाह्यal control क्रम this rail */
	क्रम (i = 0; i < 9; ++i) अणु
		ret = tps80031_ग_लिखो(dev, TPS80031_SLAVE_ID1,
				TPS80031_PREQ1_RES_ASS_A + i, 0);
		अगर (ret < 0) अणु
			dev_err(dev, "reg 0x%02x write failed, err = %d\n",
				TPS80031_PREQ1_RES_ASS_A + i, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Mask the PREQ */
	ret = tps80031_set_bits(dev, TPS80031_SLAVE_ID1,
			TPS80031_PHOENIX_MSK_TRANSITION, 0x7 << 5);
	अगर (ret < 0) अणु
		dev_err(dev, "reg 0x%02x set_bits failed, err = %d\n",
			TPS80031_PHOENIX_MSK_TRANSITION, ret);
		वापस ret;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक tps80031_irq_init(काष्ठा tps80031 *tps80031, पूर्णांक irq, पूर्णांक irq_base)
अणु
	काष्ठा device *dev = tps80031->dev;
	पूर्णांक i, ret;

	/*
	 * The MASK रेजिस्टर used क्रम updating status रेजिस्टर when
	 * पूर्णांकerrupt occurs and LINE रेजिस्टर used to pass the status
	 * to actual पूर्णांकerrupt line.  As per datasheet:
	 * When INT_MSK_LINE [i] is set to 1, the associated पूर्णांकerrupt
	 * number i is INT line masked, which means that no पूर्णांकerrupt is
	 * generated on the INT line.
	 * When INT_MSK_LINE [i] is set to 0, the associated पूर्णांकerrupt
	 * number i is  line enabled: An पूर्णांकerrupt is generated on the
	 * INT line.
	 * In any हाल, the INT_STS [i] status bit may or may not be updated,
	 * only linked to the INT_MSK_STS [i] configuration रेजिस्टर bit.
	 *
	 * When INT_MSK_STS [i] is set to 1, the associated पूर्णांकerrupt number
	 * i is status masked, which means that no पूर्णांकerrupt is stored in
	 * the INT_STS[i] status bit. Note that no पूर्णांकerrupt number i is
	 * generated on the INT line, even अगर the INT_MSK_LINE [i] रेजिस्टर
	 * bit is set to 0.
	 * When INT_MSK_STS [i] is set to 0, the associated पूर्णांकerrupt number i
	 * is status enabled: An पूर्णांकerrupt status is updated in the INT_STS [i]
	 * रेजिस्टर. The पूर्णांकerrupt may or may not be generated on the INT line,
	 * depending on the INT_MSK_LINE [i] configuration रेजिस्टर bit.
	 */
	क्रम (i = 0; i < 3; i++)
		tps80031_ग_लिखो(dev, TPS80031_SLAVE_ID2,
				TPS80031_INT_MSK_STS_A + i, 0x00);

	ret = regmap_add_irq_chip(tps80031->regmap[TPS80031_SLAVE_ID2], irq,
			IRQF_ONESHOT, irq_base,
			&tps80031_irq_chip, &tps80031->irq_data);
	अगर (ret < 0) अणु
		dev_err(dev, "add irq failed, err = %d\n", ret);
		वापस ret;
	पूर्ण
	वापस ret;
पूर्ण

अटल bool rd_wr_reg_id0(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TPS80031_SMPS1_CFG_FORCE ... TPS80031_SMPS2_CFG_VOLTAGE:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rd_wr_reg_id1(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TPS80031_SECONDS_REG ... TPS80031_RTC_RESET_STATUS_REG:
	हाल TPS80031_VALIDITY0 ... TPS80031_VALIDITY7:
	हाल TPS80031_PHOENIX_START_CONDITION ... TPS80031_KEY_PRESS_DUR_CFG:
	हाल TPS80031_SMPS4_CFG_TRANS ... TPS80031_SMPS3_CFG_VOLTAGE:
	हाल TPS80031_BROADCAST_ADDR_ALL ... TPS80031_BROADCAST_ADDR_CLK_RST:
	हाल TPS80031_VANA_CFG_TRANS ... TPS80031_LDO7_CFG_VOLTAGE:
	हाल TPS80031_REGEN1_CFG_TRANS ... TPS80031_TMP_CFG_STATE:
	हाल TPS80031_PREQ1_RES_ASS_A ... TPS80031_PREQ3_RES_ASS_C:
	हाल TPS80031_SMPS_OFFSET ... TPS80031_BATDEBOUNCING:
	हाल TPS80031_CFG_INPUT_PUPD1 ... TPS80031_CFG_SMPS_PD:
	हाल TPS80031_BACKUP_REG:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool is_अस्थिर_reg_id1(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TPS80031_SMPS4_CFG_TRANS ... TPS80031_SMPS3_CFG_VOLTAGE:
	हाल TPS80031_VANA_CFG_TRANS ... TPS80031_LDO7_CFG_VOLTAGE:
	हाल TPS80031_REGEN1_CFG_TRANS ... TPS80031_TMP_CFG_STATE:
	हाल TPS80031_PREQ1_RES_ASS_A ... TPS80031_PREQ3_RES_ASS_C:
	हाल TPS80031_SMPS_OFFSET ... TPS80031_BATDEBOUNCING:
	हाल TPS80031_CFG_INPUT_PUPD1 ... TPS80031_CFG_SMPS_PD:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rd_wr_reg_id2(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TPS80031_USB_VENDOR_ID_LSB ... TPS80031_USB_OTG_REVISION:
	हाल TPS80031_GPADC_CTRL ... TPS80031_CTRL_P1:
	हाल TPS80031_RTCH0_LSB ... TPS80031_GPCH0_MSB:
	हाल TPS80031_TOGGLE1 ... TPS80031_VIBMODE:
	हाल TPS80031_PWM1ON ... TPS80031_PWM2OFF:
	हाल TPS80031_FG_REG_00 ... TPS80031_FG_REG_11:
	हाल TPS80031_INT_STS_A ... TPS80031_INT_MSK_STS_C:
	हाल TPS80031_CONTROLLER_CTRL2 ... TPS80031_LED_PWM_CTRL2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rd_wr_reg_id3(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TPS80031_GPADC_TRIM0 ... TPS80031_GPADC_TRIM18:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config tps80031_regmap_configs[] = अणु
	अणु
		.reg_bits = 8,
		.val_bits = 8,
		.ग_लिखोable_reg = rd_wr_reg_id0,
		.पढ़ोable_reg = rd_wr_reg_id0,
		.max_रेजिस्टर = TPS80031_MAX_REGISTER,
	पूर्ण,
	अणु
		.reg_bits = 8,
		.val_bits = 8,
		.ग_लिखोable_reg = rd_wr_reg_id1,
		.पढ़ोable_reg = rd_wr_reg_id1,
		.अस्थिर_reg = is_अस्थिर_reg_id1,
		.max_रेजिस्टर = TPS80031_MAX_REGISTER,
	पूर्ण,
	अणु
		.reg_bits = 8,
		.val_bits = 8,
		.ग_लिखोable_reg = rd_wr_reg_id2,
		.पढ़ोable_reg = rd_wr_reg_id2,
		.max_रेजिस्टर = TPS80031_MAX_REGISTER,
	पूर्ण,
	अणु
		.reg_bits = 8,
		.val_bits = 8,
		.ग_लिखोable_reg = rd_wr_reg_id3,
		.पढ़ोable_reg = rd_wr_reg_id3,
		.max_रेजिस्टर = TPS80031_MAX_REGISTER,
	पूर्ण,
पूर्ण;

अटल पूर्णांक tps80031_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tps80031_platक्रमm_data *pdata = dev_get_platdata(&client->dev);
	काष्ठा tps80031 *tps80031;
	पूर्णांक ret;
	uपूर्णांक8_t es_version;
	uपूर्णांक8_t ep_ver;
	पूर्णांक i;

	अगर (!pdata) अणु
		dev_err(&client->dev, "tps80031 requires platform data\n");
		वापस -EINVAL;
	पूर्ण

	tps80031 = devm_kzalloc(&client->dev, माप(*tps80031), GFP_KERNEL);
	अगर (!tps80031)
		वापस -ENOMEM;

	क्रम (i = 0; i < TPS80031_NUM_SLAVES; i++) अणु
		अगर (tps80031_slave_address[i] == client->addr)
			tps80031->clients[i] = client;
		अन्यथा
			tps80031->clients[i] = devm_i2c_new_dummy_device(&client->dev,
						client->adapter, tps80031_slave_address[i]);
		अगर (IS_ERR(tps80031->clients[i])) अणु
			dev_err(&client->dev, "can't attach client %d\n", i);
			वापस PTR_ERR(tps80031->clients[i]);
		पूर्ण

		i2c_set_clientdata(tps80031->clients[i], tps80031);
		tps80031->regmap[i] = devm_regmap_init_i2c(tps80031->clients[i],
					&tps80031_regmap_configs[i]);
		अगर (IS_ERR(tps80031->regmap[i])) अणु
			ret = PTR_ERR(tps80031->regmap[i]);
			dev_err(&client->dev,
				"regmap %d init failed, err %d\n", i, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = tps80031_पढ़ो(&client->dev, TPS80031_SLAVE_ID3,
			TPS80031_JTAGVERNUM, &es_version);
	अगर (ret < 0) अणु
		dev_err(&client->dev,
			"Silicon version number read failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = tps80031_पढ़ो(&client->dev, TPS80031_SLAVE_ID3,
			TPS80031_EPROM_REV, &ep_ver);
	अगर (ret < 0) अणु
		dev_err(&client->dev,
			"Silicon eeprom version read failed: %d\n", ret);
		वापस ret;
	पूर्ण

	dev_info(&client->dev, "ES version 0x%02x and EPROM version 0x%02x\n",
					es_version, ep_ver);
	tps80031->es_version = es_version;
	tps80031->dev = &client->dev;
	i2c_set_clientdata(client, tps80031);
	tps80031->chip_info = id->driver_data;

	ret = tps80031_irq_init(tps80031, client->irq, pdata->irq_base);
	अगर (ret) अणु
		dev_err(&client->dev, "IRQ init failed: %d\n", ret);
		वापस ret;
	पूर्ण

	tps80031_pupd_init(tps80031, pdata);

	tps80031_init_ext_control(tps80031, pdata);

	ret = mfd_add_devices(tps80031->dev, -1,
			tps80031_cell, ARRAY_SIZE(tps80031_cell),
			शून्य, 0,
			regmap_irq_get_करोमुख्य(tps80031->irq_data));
	अगर (ret < 0) अणु
		dev_err(&client->dev, "mfd_add_devices failed: %d\n", ret);
		जाओ fail_mfd_add;
	पूर्ण

	अगर (pdata->use_घातer_off && !pm_घातer_off) अणु
		tps80031_घातer_off_dev = tps80031;
		pm_घातer_off = tps80031_घातer_off;
	पूर्ण
	वापस 0;

fail_mfd_add:
	regmap_del_irq_chip(client->irq, tps80031->irq_data);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tps80031_id_table[] = अणु
	अणु "tps80031", TPS80031 पूर्ण,
	अणु "tps80032", TPS80032 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा i2c_driver tps80031_driver = अणु
	.driver	= अणु
		.name			= "tps80031",
		.suppress_bind_attrs	= true,
	पूर्ण,
	.probe		= tps80031_probe,
	.id_table	= tps80031_id_table,
पूर्ण;

अटल पूर्णांक __init tps80031_init(व्योम)
अणु
	वापस i2c_add_driver(&tps80031_driver);
पूर्ण
subsys_initcall(tps80031_init);
