<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * I2C link layer क्रम the NXP NCI driver
 *
 * Copyright (C) 2014  NXP Semiconductors  All rights reserved.
 * Copyright (C) 2012-2015  Intel Corporation. All rights reserved.
 *
 * Authors: Clथऊment Perrochaud <clement.perrochaud@nxp.com>
 * Authors: Oleg Zhurakivskyy <oleg.zhurakivskyy@पूर्णांकel.com>
 *
 * Derived from PN544 device driver:
 * Copyright (C) 2012  Intel Corporation. All rights reserved.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/nfc.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <net/nfc/nfc.h>

#समावेश "nxp-nci.h"

#घोषणा NXP_NCI_I2C_DRIVER_NAME	"nxp-nci_i2c"

#घोषणा NXP_NCI_I2C_MAX_PAYLOAD	32

काष्ठा nxp_nci_i2c_phy अणु
	काष्ठा i2c_client *i2c_dev;
	काष्ठा nci_dev *ndev;

	काष्ठा gpio_desc *gpiod_en;
	काष्ठा gpio_desc *gpiod_fw;

	पूर्णांक hard_fault; /*
			 * < 0 अगर hardware error occurred (e.g. i2c err)
			 * and prevents normal operation.
			 */
पूर्ण;

अटल पूर्णांक nxp_nci_i2c_set_mode(व्योम *phy_id,
				    क्रमागत nxp_nci_mode mode)
अणु
	काष्ठा nxp_nci_i2c_phy *phy = (काष्ठा nxp_nci_i2c_phy *) phy_id;

	gpiod_set_value(phy->gpiod_fw, (mode == NXP_NCI_MODE_FW) ? 1 : 0);
	gpiod_set_value(phy->gpiod_en, (mode != NXP_NCI_MODE_COLD) ? 1 : 0);
	usleep_range(10000, 15000);

	अगर (mode == NXP_NCI_MODE_COLD)
		phy->hard_fault = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक nxp_nci_i2c_ग_लिखो(व्योम *phy_id, काष्ठा sk_buff *skb)
अणु
	पूर्णांक r;
	काष्ठा nxp_nci_i2c_phy *phy = phy_id;
	काष्ठा i2c_client *client = phy->i2c_dev;

	अगर (phy->hard_fault != 0)
		वापस phy->hard_fault;

	r = i2c_master_send(client, skb->data, skb->len);
	अगर (r < 0) अणु
		/* Retry, chip was in standby */
		msleep(110);
		r = i2c_master_send(client, skb->data, skb->len);
	पूर्ण

	अगर (r < 0) अणु
		nfc_err(&client->dev, "Error %d on I2C send\n", r);
	पूर्ण अन्यथा अगर (r != skb->len) अणु
		nfc_err(&client->dev,
			"Invalid length sent: %u (expected %u)\n",
			r, skb->len);
		r = -EREMOTEIO;
	पूर्ण अन्यथा अणु
		/* Success but वापस 0 and not number of bytes */
		r = 0;
	पूर्ण

	वापस r;
पूर्ण

अटल स्थिर काष्ठा nxp_nci_phy_ops i2c_phy_ops = अणु
	.set_mode = nxp_nci_i2c_set_mode,
	.ग_लिखो = nxp_nci_i2c_ग_लिखो,
पूर्ण;

अटल पूर्णांक nxp_nci_i2c_fw_पढ़ो(काष्ठा nxp_nci_i2c_phy *phy,
			       काष्ठा sk_buff **skb)
अणु
	काष्ठा i2c_client *client = phy->i2c_dev;
	u16 header;
	माप_प्रकार frame_len;
	पूर्णांक r;

	r = i2c_master_recv(client, (u8 *) &header, NXP_NCI_FW_HDR_LEN);
	अगर (r < 0) अणु
		जाओ fw_पढ़ो_निकास;
	पूर्ण अन्यथा अगर (r != NXP_NCI_FW_HDR_LEN) अणु
		nfc_err(&client->dev, "Incorrect header length: %u\n", r);
		r = -EBADMSG;
		जाओ fw_पढ़ो_निकास;
	पूर्ण

	frame_len = (be16_to_cpu(header) & NXP_NCI_FW_FRAME_LEN_MASK) +
		    NXP_NCI_FW_CRC_LEN;

	*skb = alloc_skb(NXP_NCI_FW_HDR_LEN + frame_len, GFP_KERNEL);
	अगर (*skb == शून्य) अणु
		r = -ENOMEM;
		जाओ fw_पढ़ो_निकास;
	पूर्ण

	skb_put_data(*skb, &header, NXP_NCI_FW_HDR_LEN);

	r = i2c_master_recv(client, skb_put(*skb, frame_len), frame_len);
	अगर (r != frame_len) अणु
		nfc_err(&client->dev,
			"Invalid frame length: %u (expected %zu)\n",
			r, frame_len);
		r = -EBADMSG;
		जाओ fw_पढ़ो_निकास_मुक्त_skb;
	पूर्ण

	वापस 0;

fw_पढ़ो_निकास_मुक्त_skb:
	kमुक्त_skb(*skb);
fw_पढ़ो_निकास:
	वापस r;
पूर्ण

अटल पूर्णांक nxp_nci_i2c_nci_पढ़ो(काष्ठा nxp_nci_i2c_phy *phy,
				काष्ठा sk_buff **skb)
अणु
	काष्ठा nci_ctrl_hdr header; /* May actually be a data header */
	काष्ठा i2c_client *client = phy->i2c_dev;
	पूर्णांक r;

	r = i2c_master_recv(client, (u8 *) &header, NCI_CTRL_HDR_SIZE);
	अगर (r < 0) अणु
		जाओ nci_पढ़ो_निकास;
	पूर्ण अन्यथा अगर (r != NCI_CTRL_HDR_SIZE) अणु
		nfc_err(&client->dev, "Incorrect header length: %u\n", r);
		r = -EBADMSG;
		जाओ nci_पढ़ो_निकास;
	पूर्ण

	*skb = alloc_skb(NCI_CTRL_HDR_SIZE + header.plen, GFP_KERNEL);
	अगर (*skb == शून्य) अणु
		r = -ENOMEM;
		जाओ nci_पढ़ो_निकास;
	पूर्ण

	skb_put_data(*skb, (व्योम *)&header, NCI_CTRL_HDR_SIZE);

	r = i2c_master_recv(client, skb_put(*skb, header.plen), header.plen);
	अगर (r != header.plen) अणु
		nfc_err(&client->dev,
			"Invalid frame payload length: %u (expected %u)\n",
			r, header.plen);
		r = -EBADMSG;
		जाओ nci_पढ़ो_निकास_मुक्त_skb;
	पूर्ण

	वापस 0;

nci_पढ़ो_निकास_मुक्त_skb:
	kमुक्त_skb(*skb);
nci_पढ़ो_निकास:
	वापस r;
पूर्ण

अटल irqवापस_t nxp_nci_i2c_irq_thपढ़ो_fn(पूर्णांक irq, व्योम *phy_id)
अणु
	काष्ठा nxp_nci_i2c_phy *phy = phy_id;
	काष्ठा i2c_client *client;
	काष्ठा nxp_nci_info *info;

	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक r = 0;

	अगर (!phy || !phy->ndev)
		जाओ निकास_irq_none;

	client = phy->i2c_dev;

	अगर (!client || irq != client->irq)
		जाओ निकास_irq_none;

	info = nci_get_drvdata(phy->ndev);

	अगर (!info)
		जाओ निकास_irq_none;

	mutex_lock(&info->info_lock);

	अगर (phy->hard_fault != 0)
		जाओ निकास_irq_handled;

	चयन (info->mode) अणु
	हाल NXP_NCI_MODE_NCI:
		r = nxp_nci_i2c_nci_पढ़ो(phy, &skb);
		अवरोध;
	हाल NXP_NCI_MODE_FW:
		r = nxp_nci_i2c_fw_पढ़ो(phy, &skb);
		अवरोध;
	हाल NXP_NCI_MODE_COLD:
		r = -EREMOTEIO;
		अवरोध;
	पूर्ण

	अगर (r == -EREMOTEIO) अणु
		phy->hard_fault = r;
		अगर (info->mode == NXP_NCI_MODE_FW)
			nxp_nci_fw_recv_frame(phy->ndev, शून्य);
	पूर्ण
	अगर (r < 0) अणु
		nfc_err(&client->dev, "Read failed with error %d\n", r);
		जाओ निकास_irq_handled;
	पूर्ण

	चयन (info->mode) अणु
	हाल NXP_NCI_MODE_NCI:
		nci_recv_frame(phy->ndev, skb);
		अवरोध;
	हाल NXP_NCI_MODE_FW:
		nxp_nci_fw_recv_frame(phy->ndev, skb);
		अवरोध;
	हाल NXP_NCI_MODE_COLD:
		अवरोध;
	पूर्ण

निकास_irq_handled:
	mutex_unlock(&info->info_lock);
	वापस IRQ_HANDLED;
निकास_irq_none:
	WARN_ON_ONCE(1);
	वापस IRQ_NONE;
पूर्ण

अटल स्थिर काष्ठा acpi_gpio_params firmware_gpios = अणु 1, 0, false पूर्ण;
अटल स्थिर काष्ठा acpi_gpio_params enable_gpios = अणु 2, 0, false पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_mapping acpi_nxp_nci_gpios[] = अणु
	अणु "enable-gpios", &enable_gpios, 1 पूर्ण,
	अणु "firmware-gpios", &firmware_gpios, 1 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक nxp_nci_i2c_probe(काष्ठा i2c_client *client,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा nxp_nci_i2c_phy *phy;
	पूर्णांक r;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		nfc_err(&client->dev, "Need I2C_FUNC_I2C\n");
		वापस -ENODEV;
	पूर्ण

	phy = devm_kzalloc(&client->dev, माप(काष्ठा nxp_nci_i2c_phy),
			   GFP_KERNEL);
	अगर (!phy)
		वापस -ENOMEM;

	phy->i2c_dev = client;
	i2c_set_clientdata(client, phy);

	r = devm_acpi_dev_add_driver_gpios(dev, acpi_nxp_nci_gpios);
	अगर (r)
		dev_dbg(dev, "Unable to add GPIO mapping table\n");

	phy->gpiod_en = devm_gpiod_get(dev, "enable", GPIOD_OUT_LOW);
	अगर (IS_ERR(phy->gpiod_en)) अणु
		nfc_err(dev, "Failed to get EN gpio\n");
		वापस PTR_ERR(phy->gpiod_en);
	पूर्ण

	phy->gpiod_fw = devm_gpiod_get_optional(dev, "firmware", GPIOD_OUT_LOW);
	अगर (IS_ERR(phy->gpiod_fw)) अणु
		nfc_err(dev, "Failed to get FW gpio\n");
		वापस PTR_ERR(phy->gpiod_fw);
	पूर्ण

	r = nxp_nci_probe(phy, &client->dev, &i2c_phy_ops,
			  NXP_NCI_I2C_MAX_PAYLOAD, &phy->ndev);
	अगर (r < 0)
		वापस r;

	r = request_thपढ़ोed_irq(client->irq, शून्य,
				 nxp_nci_i2c_irq_thपढ़ो_fn,
				 IRQF_TRIGGER_RISING | IRQF_ONESHOT,
				 NXP_NCI_I2C_DRIVER_NAME, phy);
	अगर (r < 0)
		nfc_err(&client->dev, "Unable to register IRQ handler\n");

	वापस r;
पूर्ण

अटल पूर्णांक nxp_nci_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा nxp_nci_i2c_phy *phy = i2c_get_clientdata(client);

	nxp_nci_हटाओ(phy->ndev);
	मुक्त_irq(client->irq, phy);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id nxp_nci_i2c_id_table[] = अणु
	अणु"nxp-nci_i2c", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, nxp_nci_i2c_id_table);

अटल स्थिर काष्ठा of_device_id of_nxp_nci_i2c_match[] = अणु
	अणु .compatible = "nxp,nxp-nci-i2c", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_nxp_nci_i2c_match);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id acpi_id[] = अणु
	अणु "NXP1001" पूर्ण,
	अणु "NXP7471" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, acpi_id);
#पूर्ण_अगर

अटल काष्ठा i2c_driver nxp_nci_i2c_driver = अणु
	.driver = अणु
		   .name = NXP_NCI_I2C_DRIVER_NAME,
		   .acpi_match_table = ACPI_PTR(acpi_id),
		   .of_match_table = of_nxp_nci_i2c_match,
		  पूर्ण,
	.probe = nxp_nci_i2c_probe,
	.id_table = nxp_nci_i2c_id_table,
	.हटाओ = nxp_nci_i2c_हटाओ,
पूर्ण;

module_i2c_driver(nxp_nci_i2c_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("I2C driver for NXP NCI NFC controllers");
MODULE_AUTHOR("Clथऊment Perrochaud <clement.perrochaud@nxp.com>");
MODULE_AUTHOR("Oleg Zhurakivskyy <oleg.zhurakivskyy@intel.com>");
