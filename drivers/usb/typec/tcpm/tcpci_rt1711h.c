<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2018, Richtek Technology Corporation
 *
 * Richtek RT1711H Type-C Chip Driver
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/usb/tcpm.h>
#समावेश <linux/regmap.h>
#समावेश "tcpci.h"

#घोषणा RT1711H_VID		0x29CF
#घोषणा RT1711H_PID		0x1711

#घोषणा RT1711H_RTCTRL8		0x9B

/* Autoidle समयout = (tout * 2 + 1) * 6.4ms */
#घोषणा RT1711H_RTCTRL8_SET(ck300, ship_off, स्वतः_idle, tout) \
			    (((ck300) << 7) | ((ship_off) << 5) | \
			    ((स्वतः_idle) << 3) | ((tout) & 0x07))

#घोषणा RT1711H_RTCTRL11	0x9E

/* I2C समयout = (tout + 1) * 12.5ms */
#घोषणा RT1711H_RTCTRL11_SET(en, tout) \
			     (((en) << 7) | ((tout) & 0x0F))

#घोषणा RT1711H_RTCTRL13	0xA0
#घोषणा RT1711H_RTCTRL14	0xA1
#घोषणा RT1711H_RTCTRL15	0xA2
#घोषणा RT1711H_RTCTRL16	0xA3

काष्ठा rt1711h_chip अणु
	काष्ठा tcpci_data data;
	काष्ठा tcpci *tcpci;
	काष्ठा device *dev;
पूर्ण;

अटल पूर्णांक rt1711h_पढ़ो16(काष्ठा rt1711h_chip *chip, अचिन्हित पूर्णांक reg, u16 *val)
अणु
	वापस regmap_raw_पढ़ो(chip->data.regmap, reg, val, माप(u16));
पूर्ण

अटल पूर्णांक rt1711h_ग_लिखो16(काष्ठा rt1711h_chip *chip, अचिन्हित पूर्णांक reg, u16 val)
अणु
	वापस regmap_raw_ग_लिखो(chip->data.regmap, reg, &val, माप(u16));
पूर्ण

अटल पूर्णांक rt1711h_पढ़ो8(काष्ठा rt1711h_chip *chip, अचिन्हित पूर्णांक reg, u8 *val)
अणु
	वापस regmap_raw_पढ़ो(chip->data.regmap, reg, val, माप(u8));
पूर्ण

अटल पूर्णांक rt1711h_ग_लिखो8(काष्ठा rt1711h_chip *chip, अचिन्हित पूर्णांक reg, u8 val)
अणु
	वापस regmap_raw_ग_लिखो(chip->data.regmap, reg, &val, माप(u8));
पूर्ण

अटल स्थिर काष्ठा regmap_config rt1711h_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = 0xFF, /* 0x80 .. 0xFF are venकरोr defined */
पूर्ण;

अटल काष्ठा rt1711h_chip *tdata_to_rt1711h(काष्ठा tcpci_data *tdata)
अणु
	वापस container_of(tdata, काष्ठा rt1711h_chip, data);
पूर्ण

अटल पूर्णांक rt1711h_init(काष्ठा tcpci *tcpci, काष्ठा tcpci_data *tdata)
अणु
	पूर्णांक ret;
	काष्ठा rt1711h_chip *chip = tdata_to_rt1711h(tdata);

	/* CK 300K from 320K, shipping off, स्वतः_idle enable, tout = 32ms */
	ret = rt1711h_ग_लिखो8(chip, RT1711H_RTCTRL8,
			     RT1711H_RTCTRL8_SET(0, 1, 1, 2));
	अगर (ret < 0)
		वापस ret;

	/* I2C reset : (val + 1) * 12.5ms */
	ret = rt1711h_ग_लिखो8(chip, RT1711H_RTCTRL11,
			     RT1711H_RTCTRL11_SET(1, 0x0F));
	अगर (ret < 0)
		वापस ret;

	/* tTCPCfilter : (26.7 * val) us */
	ret = rt1711h_ग_लिखो8(chip, RT1711H_RTCTRL14, 0x0F);
	अगर (ret < 0)
		वापस ret;

	/*  tDRP : (51.2 + 6.4 * val) ms */
	ret = rt1711h_ग_लिखो8(chip, RT1711H_RTCTRL15, 0x04);
	अगर (ret < 0)
		वापस ret;

	/* dcSRC.DRP : 33% */
	वापस rt1711h_ग_लिखो16(chip, RT1711H_RTCTRL16, 330);
पूर्ण

अटल पूर्णांक rt1711h_set_vconn(काष्ठा tcpci *tcpci, काष्ठा tcpci_data *tdata,
			     bool enable)
अणु
	काष्ठा rt1711h_chip *chip = tdata_to_rt1711h(tdata);

	वापस rt1711h_ग_लिखो8(chip, RT1711H_RTCTRL8,
			      RT1711H_RTCTRL8_SET(0, 1, !enable, 2));
पूर्ण

अटल पूर्णांक rt1711h_start_drp_toggling(काष्ठा tcpci *tcpci,
				      काष्ठा tcpci_data *tdata,
				      क्रमागत typec_cc_status cc)
अणु
	काष्ठा rt1711h_chip *chip = tdata_to_rt1711h(tdata);
	पूर्णांक ret;
	अचिन्हित पूर्णांक reg = 0;

	चयन (cc) अणु
	शेष:
	हाल TYPEC_CC_RP_DEF:
		reg |= (TCPC_ROLE_CTRL_RP_VAL_DEF <<
			TCPC_ROLE_CTRL_RP_VAL_SHIFT);
		अवरोध;
	हाल TYPEC_CC_RP_1_5:
		reg |= (TCPC_ROLE_CTRL_RP_VAL_1_5 <<
			TCPC_ROLE_CTRL_RP_VAL_SHIFT);
		अवरोध;
	हाल TYPEC_CC_RP_3_0:
		reg |= (TCPC_ROLE_CTRL_RP_VAL_3_0 <<
			TCPC_ROLE_CTRL_RP_VAL_SHIFT);
		अवरोध;
	पूर्ण

	अगर (cc == TYPEC_CC_RD)
		reg |= (TCPC_ROLE_CTRL_CC_RD << TCPC_ROLE_CTRL_CC1_SHIFT) |
			   (TCPC_ROLE_CTRL_CC_RD << TCPC_ROLE_CTRL_CC2_SHIFT);
	अन्यथा
		reg |= (TCPC_ROLE_CTRL_CC_RP << TCPC_ROLE_CTRL_CC1_SHIFT) |
			   (TCPC_ROLE_CTRL_CC_RP << TCPC_ROLE_CTRL_CC2_SHIFT);

	ret = rt1711h_ग_लिखो8(chip, TCPC_ROLE_CTRL, reg);
	अगर (ret < 0)
		वापस ret;
	usleep_range(500, 1000);

	वापस 0;
पूर्ण

अटल irqवापस_t rt1711h_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	पूर्णांक ret;
	u16 alert;
	u8 status;
	काष्ठा rt1711h_chip *chip = dev_id;

	अगर (!chip->tcpci)
		वापस IRQ_HANDLED;

	ret = rt1711h_पढ़ो16(chip, TCPC_ALERT, &alert);
	अगर (ret < 0)
		जाओ out;

	अगर (alert & TCPC_ALERT_CC_STATUS) अणु
		ret = rt1711h_पढ़ो8(chip, TCPC_CC_STATUS, &status);
		अगर (ret < 0)
			जाओ out;
		/* Clear cc change event triggered by starting toggling */
		अगर (status & TCPC_CC_STATUS_TOGGLING)
			rt1711h_ग_लिखो8(chip, TCPC_ALERT, TCPC_ALERT_CC_STATUS);
	पूर्ण

out:
	वापस tcpci_irq(chip->tcpci);
पूर्ण

अटल पूर्णांक rt1711h_sw_reset(काष्ठा rt1711h_chip *chip)
अणु
	पूर्णांक ret;

	ret = rt1711h_ग_लिखो8(chip, RT1711H_RTCTRL13, 0x01);
	अगर (ret < 0)
		वापस ret;

	usleep_range(1000, 2000);
	वापस 0;
पूर्ण

अटल पूर्णांक rt1711h_check_revision(काष्ठा i2c_client *i2c)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_word_data(i2c, TCPC_VENDOR_ID);
	अगर (ret < 0)
		वापस ret;
	अगर (ret != RT1711H_VID) अणु
		dev_err(&i2c->dev, "vid is not correct, 0x%04x\n", ret);
		वापस -ENODEV;
	पूर्ण
	ret = i2c_smbus_पढ़ो_word_data(i2c, TCPC_PRODUCT_ID);
	अगर (ret < 0)
		वापस ret;
	अगर (ret != RT1711H_PID) अणु
		dev_err(&i2c->dev, "pid is not correct, 0x%04x\n", ret);
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rt1711h_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *i2c_id)
अणु
	पूर्णांक ret;
	काष्ठा rt1711h_chip *chip;

	ret = rt1711h_check_revision(client);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "check vid/pid fail\n");
		वापस ret;
	पूर्ण

	chip = devm_kzalloc(&client->dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	chip->data.regmap = devm_regmap_init_i2c(client,
						 &rt1711h_regmap_config);
	अगर (IS_ERR(chip->data.regmap))
		वापस PTR_ERR(chip->data.regmap);

	chip->dev = &client->dev;
	i2c_set_clientdata(client, chip);

	ret = rt1711h_sw_reset(chip);
	अगर (ret < 0)
		वापस ret;

	/* Disable chip पूर्णांकerrupts beक्रमe requesting irq */
	ret = rt1711h_ग_लिखो16(chip, TCPC_ALERT_MASK, 0);
	अगर (ret < 0)
		वापस ret;

	chip->data.init = rt1711h_init;
	chip->data.set_vconn = rt1711h_set_vconn;
	chip->data.start_drp_toggling = rt1711h_start_drp_toggling;
	chip->tcpci = tcpci_रेजिस्टर_port(chip->dev, &chip->data);
	अगर (IS_ERR_OR_शून्य(chip->tcpci))
		वापस PTR_ERR(chip->tcpci);

	ret = devm_request_thपढ़ोed_irq(chip->dev, client->irq, शून्य,
					rt1711h_irq,
					IRQF_ONESHOT | IRQF_TRIGGER_LOW,
					dev_name(chip->dev), chip);
	अगर (ret < 0)
		वापस ret;
	enable_irq_wake(client->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक rt1711h_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा rt1711h_chip *chip = i2c_get_clientdata(client);

	tcpci_unरेजिस्टर_port(chip->tcpci);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id rt1711h_id[] = अणु
	अणु "rt1711h", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rt1711h_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id rt1711h_of_match[] = अणु
	अणु .compatible = "richtek,rt1711h", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rt1711h_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver rt1711h_i2c_driver = अणु
	.driver = अणु
		.name = "rt1711h",
		.of_match_table = of_match_ptr(rt1711h_of_match),
	पूर्ण,
	.probe = rt1711h_probe,
	.हटाओ = rt1711h_हटाओ,
	.id_table = rt1711h_id,
पूर्ण;
module_i2c_driver(rt1711h_i2c_driver);

MODULE_AUTHOR("ShuFan Lee <shufan_lee@richtek.com>");
MODULE_DESCRIPTION("RT1711H USB Type-C Port Controller Interface Driver");
MODULE_LICENSE("GPL");
