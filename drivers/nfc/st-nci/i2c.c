<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * I2C Link Layer क्रम ST NCI NFC controller familly based Driver
 * Copyright (C) 2014-2015 STMicroelectronics SAS. All rights reserved.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/acpi.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/nfc.h>
#समावेश <linux/of.h>

#समावेश "st-nci.h"

#घोषणा DRIVER_DESC "NCI NFC driver for ST_NCI"

/* ndlc header */
#घोषणा ST_NCI_FRAME_HEADROOM 1
#घोषणा ST_NCI_FRAME_TAILROOM 0

#घोषणा ST_NCI_I2C_MIN_SIZE 4   /* PCB(1) + NCI Packet header(3) */
#घोषणा ST_NCI_I2C_MAX_SIZE 250 /* req 4.2.1 */

#घोषणा ST_NCI_DRIVER_NAME "st_nci"
#घोषणा ST_NCI_I2C_DRIVER_NAME "st_nci_i2c"

काष्ठा st_nci_i2c_phy अणु
	काष्ठा i2c_client *i2c_dev;
	काष्ठा llt_ndlc *ndlc;

	bool irq_active;

	काष्ठा gpio_desc *gpiod_reset;

	काष्ठा st_nci_se_status se_status;
पूर्ण;

अटल पूर्णांक st_nci_i2c_enable(व्योम *phy_id)
अणु
	काष्ठा st_nci_i2c_phy *phy = phy_id;

	gpiod_set_value(phy->gpiod_reset, 0);
	usleep_range(10000, 15000);
	gpiod_set_value(phy->gpiod_reset, 1);
	usleep_range(80000, 85000);

	अगर (phy->ndlc->घातered == 0 && phy->irq_active == 0) अणु
		enable_irq(phy->i2c_dev->irq);
		phy->irq_active = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम st_nci_i2c_disable(व्योम *phy_id)
अणु
	काष्ठा st_nci_i2c_phy *phy = phy_id;

	disable_irq_nosync(phy->i2c_dev->irq);
	phy->irq_active = false;
पूर्ण

/*
 * Writing a frame must not वापस the number of written bytes.
 * It must वापस either zero क्रम success, or <0 क्रम error.
 * In addition, it must not alter the skb
 */
अटल पूर्णांक st_nci_i2c_ग_लिखो(व्योम *phy_id, काष्ठा sk_buff *skb)
अणु
	पूर्णांक r;
	काष्ठा st_nci_i2c_phy *phy = phy_id;
	काष्ठा i2c_client *client = phy->i2c_dev;

	अगर (phy->ndlc->hard_fault != 0)
		वापस phy->ndlc->hard_fault;

	r = i2c_master_send(client, skb->data, skb->len);
	अगर (r < 0) अणु  /* Retry, chip was in standby */
		usleep_range(1000, 4000);
		r = i2c_master_send(client, skb->data, skb->len);
	पूर्ण

	अगर (r >= 0) अणु
		अगर (r != skb->len)
			r = -EREMOTEIO;
		अन्यथा
			r = 0;
	पूर्ण

	वापस r;
पूर्ण

/*
 * Reads an ndlc frame and वापसs it in a newly allocated sk_buff.
 * वापसs:
 * 0 : अगर received frame is complete
 * -EREMOTEIO : i2c पढ़ो error (fatal)
 * -EBADMSG : frame was incorrect and discarded
 * -ENOMEM : cannot allocate skb, frame dropped
 */
अटल पूर्णांक st_nci_i2c_पढ़ो(काष्ठा st_nci_i2c_phy *phy,
				 काष्ठा sk_buff **skb)
अणु
	पूर्णांक r;
	u8 len;
	u8 buf[ST_NCI_I2C_MAX_SIZE];
	काष्ठा i2c_client *client = phy->i2c_dev;

	r = i2c_master_recv(client, buf, ST_NCI_I2C_MIN_SIZE);
	अगर (r < 0) अणु  /* Retry, chip was in standby */
		usleep_range(1000, 4000);
		r = i2c_master_recv(client, buf, ST_NCI_I2C_MIN_SIZE);
	पूर्ण

	अगर (r != ST_NCI_I2C_MIN_SIZE)
		वापस -EREMOTEIO;

	len = be16_to_cpu(*(__be16 *) (buf + 2));
	अगर (len > ST_NCI_I2C_MAX_SIZE) अणु
		nfc_err(&client->dev, "invalid frame len\n");
		वापस -EBADMSG;
	पूर्ण

	*skb = alloc_skb(ST_NCI_I2C_MIN_SIZE + len, GFP_KERNEL);
	अगर (*skb == शून्य)
		वापस -ENOMEM;

	skb_reserve(*skb, ST_NCI_I2C_MIN_SIZE);
	skb_put(*skb, ST_NCI_I2C_MIN_SIZE);
	स_नकल((*skb)->data, buf, ST_NCI_I2C_MIN_SIZE);

	अगर (!len)
		वापस 0;

	r = i2c_master_recv(client, buf, len);
	अगर (r != len) अणु
		kमुक्त_skb(*skb);
		वापस -EREMOTEIO;
	पूर्ण

	skb_put(*skb, len);
	स_नकल((*skb)->data + ST_NCI_I2C_MIN_SIZE, buf, len);

	वापस 0;
पूर्ण

/*
 * Reads an ndlc frame from the chip.
 *
 * On ST_NCI, IRQ goes in idle state when पढ़ो starts.
 */
अटल irqवापस_t st_nci_irq_thपढ़ो_fn(पूर्णांक irq, व्योम *phy_id)
अणु
	काष्ठा st_nci_i2c_phy *phy = phy_id;
	काष्ठा i2c_client *client;
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक r;

	अगर (!phy || !phy->ndlc || irq != phy->i2c_dev->irq) अणु
		WARN_ON_ONCE(1);
		वापस IRQ_NONE;
	पूर्ण

	client = phy->i2c_dev;
	dev_dbg(&client->dev, "IRQ\n");

	अगर (phy->ndlc->hard_fault)
		वापस IRQ_HANDLED;

	अगर (!phy->ndlc->घातered) अणु
		st_nci_i2c_disable(phy);
		वापस IRQ_HANDLED;
	पूर्ण

	r = st_nci_i2c_पढ़ो(phy, &skb);
	अगर (r == -EREMOTEIO || r == -ENOMEM || r == -EBADMSG)
		वापस IRQ_HANDLED;

	ndlc_recv(phy->ndlc, skb);

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा nfc_phy_ops i2c_phy_ops = अणु
	.ग_लिखो = st_nci_i2c_ग_लिखो,
	.enable = st_nci_i2c_enable,
	.disable = st_nci_i2c_disable,
पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_params reset_gpios = अणु 1, 0, false पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_mapping acpi_st_nci_gpios[] = अणु
	अणु "reset-gpios", &reset_gpios, 1 पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक st_nci_i2c_probe(काष्ठा i2c_client *client,
				  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा st_nci_i2c_phy *phy;
	पूर्णांक r;

	dev_dbg(&client->dev, "%s\n", __func__);
	dev_dbg(&client->dev, "IRQ: %d\n", client->irq);

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		nfc_err(&client->dev, "Need I2C_FUNC_I2C\n");
		वापस -ENODEV;
	पूर्ण

	phy = devm_kzalloc(dev, माप(काष्ठा st_nci_i2c_phy), GFP_KERNEL);
	अगर (!phy)
		वापस -ENOMEM;

	phy->i2c_dev = client;

	i2c_set_clientdata(client, phy);

	r = devm_acpi_dev_add_driver_gpios(dev, acpi_st_nci_gpios);
	अगर (r)
		dev_dbg(dev, "Unable to add GPIO mapping table\n");

	/* Get RESET GPIO */
	phy->gpiod_reset = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(phy->gpiod_reset)) अणु
		nfc_err(dev, "Unable to get RESET GPIO\n");
		वापस -ENODEV;
	पूर्ण

	phy->se_status.is_ese_present =
				device_property_पढ़ो_bool(dev, "ese-present");
	phy->se_status.is_uicc_present =
				device_property_पढ़ो_bool(dev, "uicc-present");

	r = ndlc_probe(phy, &i2c_phy_ops, &client->dev,
			ST_NCI_FRAME_HEADROOM, ST_NCI_FRAME_TAILROOM,
			&phy->ndlc, &phy->se_status);
	अगर (r < 0) अणु
		nfc_err(&client->dev, "Unable to register ndlc layer\n");
		वापस r;
	पूर्ण

	phy->irq_active = true;
	r = devm_request_thपढ़ोed_irq(&client->dev, client->irq, शून्य,
				st_nci_irq_thपढ़ो_fn,
				IRQF_ONESHOT,
				ST_NCI_DRIVER_NAME, phy);
	अगर (r < 0)
		nfc_err(&client->dev, "Unable to register IRQ handler\n");

	वापस r;
पूर्ण

अटल पूर्णांक st_nci_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा st_nci_i2c_phy *phy = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "%s\n", __func__);

	ndlc_हटाओ(phy->ndlc);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id st_nci_i2c_id_table[] = अणु
	अणुST_NCI_DRIVER_NAME, 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, st_nci_i2c_id_table);

अटल स्थिर काष्ठा acpi_device_id st_nci_i2c_acpi_match[] = अणु
	अणु"SMO2101"पूर्ण,
	अणु"SMO2102"पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, st_nci_i2c_acpi_match);

अटल स्थिर काष्ठा of_device_id of_st_nci_i2c_match[] = अणु
	अणु .compatible = "st,st21nfcb-i2c", पूर्ण,
	अणु .compatible = "st,st21nfcb_i2c", पूर्ण,
	अणु .compatible = "st,st21nfcc-i2c", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_st_nci_i2c_match);

अटल काष्ठा i2c_driver st_nci_i2c_driver = अणु
	.driver = अणु
		.name = ST_NCI_I2C_DRIVER_NAME,
		.of_match_table = of_match_ptr(of_st_nci_i2c_match),
		.acpi_match_table = ACPI_PTR(st_nci_i2c_acpi_match),
	पूर्ण,
	.probe = st_nci_i2c_probe,
	.id_table = st_nci_i2c_id_table,
	.हटाओ = st_nci_i2c_हटाओ,
पूर्ण;
module_i2c_driver(st_nci_i2c_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION(DRIVER_DESC);
