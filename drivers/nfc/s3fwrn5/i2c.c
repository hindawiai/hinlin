<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * I2C Link Layer क्रम Samsung S3FWRN5 NCI based Driver
 *
 * Copyright (C) 2015 Samsung Electrnoics
 * Robert Baldyga <r.baldyga@samsung.com>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/delay.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_irq.h>
#समावेश <linux/module.h>

#समावेश <net/nfc/nfc.h>

#समावेश "phy_common.h"

#घोषणा S3FWRN5_I2C_DRIVER_NAME "s3fwrn5_i2c"

काष्ठा s3fwrn5_i2c_phy अणु
	काष्ठा phy_common common;
	काष्ठा i2c_client *i2c_dev;

	अचिन्हित पूर्णांक irq_skip:1;
पूर्ण;

अटल व्योम s3fwrn5_i2c_set_mode(व्योम *phy_id, क्रमागत s3fwrn5_mode mode)
अणु
	काष्ठा s3fwrn5_i2c_phy *phy = phy_id;

	mutex_lock(&phy->common.mutex);

	अगर (s3fwrn5_phy_घातer_ctrl(&phy->common, mode) == false)
		जाओ out;

	phy->irq_skip = true;

out:
	mutex_unlock(&phy->common.mutex);
पूर्ण

अटल पूर्णांक s3fwrn5_i2c_ग_लिखो(व्योम *phy_id, काष्ठा sk_buff *skb)
अणु
	काष्ठा s3fwrn5_i2c_phy *phy = phy_id;
	पूर्णांक ret;

	mutex_lock(&phy->common.mutex);

	phy->irq_skip = false;

	ret = i2c_master_send(phy->i2c_dev, skb->data, skb->len);
	अगर (ret == -EREMOTEIO) अणु
		/* Retry, chip was in standby */
		usleep_range(110000, 120000);
		ret  = i2c_master_send(phy->i2c_dev, skb->data, skb->len);
	पूर्ण

	mutex_unlock(&phy->common.mutex);

	अगर (ret < 0)
		वापस ret;

	अगर (ret != skb->len)
		वापस -EREMOTEIO;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा s3fwrn5_phy_ops i2c_phy_ops = अणु
	.set_wake = s3fwrn5_phy_set_wake,
	.set_mode = s3fwrn5_i2c_set_mode,
	.get_mode = s3fwrn5_phy_get_mode,
	.ग_लिखो = s3fwrn5_i2c_ग_लिखो,
पूर्ण;

अटल पूर्णांक s3fwrn5_i2c_पढ़ो(काष्ठा s3fwrn5_i2c_phy *phy)
अणु
	काष्ठा sk_buff *skb;
	माप_प्रकार hdr_size;
	माप_प्रकार data_len;
	अक्षर hdr[4];
	पूर्णांक ret;

	hdr_size = (phy->common.mode == S3FWRN5_MODE_NCI) ?
		NCI_CTRL_HDR_SIZE : S3FWRN5_FW_HDR_SIZE;
	ret = i2c_master_recv(phy->i2c_dev, hdr, hdr_size);
	अगर (ret < 0)
		वापस ret;

	अगर (ret < hdr_size)
		वापस -EBADMSG;

	data_len = (phy->common.mode == S3FWRN5_MODE_NCI) ?
		((काष्ठा nci_ctrl_hdr *)hdr)->plen :
		((काष्ठा s3fwrn5_fw_header *)hdr)->len;

	skb = alloc_skb(hdr_size + data_len, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put_data(skb, hdr, hdr_size);

	अगर (data_len == 0)
		जाओ out;

	ret = i2c_master_recv(phy->i2c_dev, skb_put(skb, data_len), data_len);
	अगर (ret != data_len) अणु
		kमुक्त_skb(skb);
		वापस -EBADMSG;
	पूर्ण

out:
	वापस s3fwrn5_recv_frame(phy->common.ndev, skb, phy->common.mode);
पूर्ण

अटल irqवापस_t s3fwrn5_i2c_irq_thपढ़ो_fn(पूर्णांक irq, व्योम *phy_id)
अणु
	काष्ठा s3fwrn5_i2c_phy *phy = phy_id;

	अगर (!phy || !phy->common.ndev) अणु
		WARN_ON_ONCE(1);
		वापस IRQ_NONE;
	पूर्ण

	mutex_lock(&phy->common.mutex);

	अगर (phy->irq_skip)
		जाओ out;

	चयन (phy->common.mode) अणु
	हाल S3FWRN5_MODE_NCI:
	हाल S3FWRN5_MODE_FW:
		s3fwrn5_i2c_पढ़ो(phy);
		अवरोध;
	हाल S3FWRN5_MODE_COLD:
		अवरोध;
	पूर्ण

out:
	mutex_unlock(&phy->common.mutex);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक s3fwrn5_i2c_parse_dt(काष्ठा i2c_client *client)
अणु
	काष्ठा s3fwrn5_i2c_phy *phy = i2c_get_clientdata(client);
	काष्ठा device_node *np = client->dev.of_node;

	अगर (!np)
		वापस -ENODEV;

	phy->common.gpio_en = of_get_named_gpio(np, "en-gpios", 0);
	अगर (!gpio_is_valid(phy->common.gpio_en)) अणु
		/* Support also deprecated property */
		phy->common.gpio_en = of_get_named_gpio(np,
							"s3fwrn5,en-gpios",
							0);
		अगर (!gpio_is_valid(phy->common.gpio_en))
			वापस -ENODEV;
	पूर्ण

	phy->common.gpio_fw_wake = of_get_named_gpio(np, "wake-gpios", 0);
	अगर (!gpio_is_valid(phy->common.gpio_fw_wake)) अणु
		/* Support also deprecated property */
		phy->common.gpio_fw_wake = of_get_named_gpio(np,
							     "s3fwrn5,fw-gpios",
							     0);
		अगर (!gpio_is_valid(phy->common.gpio_fw_wake))
			वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s3fwrn5_i2c_probe(काष्ठा i2c_client *client,
				  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा s3fwrn5_i2c_phy *phy;
	पूर्णांक ret;

	phy = devm_kzalloc(&client->dev, माप(*phy), GFP_KERNEL);
	अगर (!phy)
		वापस -ENOMEM;

	mutex_init(&phy->common.mutex);
	phy->common.mode = S3FWRN5_MODE_COLD;
	phy->irq_skip = true;

	phy->i2c_dev = client;
	i2c_set_clientdata(client, phy);

	ret = s3fwrn5_i2c_parse_dt(client);
	अगर (ret < 0)
		वापस ret;

	ret = devm_gpio_request_one(&phy->i2c_dev->dev, phy->common.gpio_en,
				    GPIOF_OUT_INIT_HIGH, "s3fwrn5_en");
	अगर (ret < 0)
		वापस ret;

	ret = devm_gpio_request_one(&phy->i2c_dev->dev,
				    phy->common.gpio_fw_wake,
				    GPIOF_OUT_INIT_LOW, "s3fwrn5_fw_wake");
	अगर (ret < 0)
		वापस ret;

	ret = s3fwrn5_probe(&phy->common.ndev, phy, &phy->i2c_dev->dev,
			    &i2c_phy_ops);
	अगर (ret < 0)
		वापस ret;

	ret = devm_request_thपढ़ोed_irq(&client->dev, phy->i2c_dev->irq, शून्य,
		s3fwrn5_i2c_irq_thपढ़ो_fn, IRQF_ONESHOT,
		S3FWRN5_I2C_DRIVER_NAME, phy);
	अगर (ret)
		s3fwrn5_हटाओ(phy->common.ndev);

	वापस ret;
पूर्ण

अटल पूर्णांक s3fwrn5_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा s3fwrn5_i2c_phy *phy = i2c_get_clientdata(client);

	s3fwrn5_हटाओ(phy->common.ndev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id s3fwrn5_i2c_id_table[] = अणु
	अणुS3FWRN5_I2C_DRIVER_NAME, 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, s3fwrn5_i2c_id_table);

अटल स्थिर काष्ठा of_device_id of_s3fwrn5_i2c_match[] = अणु
	अणु .compatible = "samsung,s3fwrn5-i2c", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_s3fwrn5_i2c_match);

अटल काष्ठा i2c_driver s3fwrn5_i2c_driver = अणु
	.driver = अणु
		.name = S3FWRN5_I2C_DRIVER_NAME,
		.of_match_table = of_match_ptr(of_s3fwrn5_i2c_match),
	पूर्ण,
	.probe = s3fwrn5_i2c_probe,
	.हटाओ = s3fwrn5_i2c_हटाओ,
	.id_table = s3fwrn5_i2c_id_table,
पूर्ण;

module_i2c_driver(s3fwrn5_i2c_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("I2C driver for Samsung S3FWRN5");
MODULE_AUTHOR("Robert Baldyga <r.baldyga@samsung.com>");
