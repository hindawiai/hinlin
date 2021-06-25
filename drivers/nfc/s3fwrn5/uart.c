<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * UART Link Layer क्रम S3FWRN82 NCI based Driver
 *
 * Copyright (C) 2015 Samsung Electronics
 * Robert Baldyga <r.baldyga@samsung.com>
 * Copyright (C) 2020 Samsung Electronics
 * Bongsu Jeon <bongsu.jeon@samsung.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/nfc.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/of.h>
#समावेश <linux/serdev.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/of_gpपन.स>

#समावेश "phy_common.h"

#घोषणा S3FWRN82_NCI_HEADER 3
#घोषणा S3FWRN82_NCI_IDX 2
#घोषणा NCI_SKB_BUFF_LEN 258

काष्ठा s3fwrn82_uart_phy अणु
	काष्ठा phy_common common;
	काष्ठा serdev_device *ser_dev;
	काष्ठा sk_buff *recv_skb;
पूर्ण;

अटल पूर्णांक s3fwrn82_uart_ग_लिखो(व्योम *phy_id, काष्ठा sk_buff *out)
अणु
	काष्ठा s3fwrn82_uart_phy *phy = phy_id;
	पूर्णांक err;

	err = serdev_device_ग_लिखो(phy->ser_dev,
				  out->data, out->len,
				  MAX_SCHEDULE_TIMEOUT);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा s3fwrn5_phy_ops uart_phy_ops = अणु
	.set_wake = s3fwrn5_phy_set_wake,
	.set_mode = s3fwrn5_phy_set_mode,
	.get_mode = s3fwrn5_phy_get_mode,
	.ग_लिखो = s3fwrn82_uart_ग_लिखो,
पूर्ण;

अटल पूर्णांक s3fwrn82_uart_पढ़ो(काष्ठा serdev_device *serdev,
			      स्थिर अचिन्हित अक्षर *data,
			      माप_प्रकार count)
अणु
	काष्ठा s3fwrn82_uart_phy *phy = serdev_device_get_drvdata(serdev);
	माप_प्रकार i;

	क्रम (i = 0; i < count; i++) अणु
		skb_put_u8(phy->recv_skb, *data++);

		अगर (phy->recv_skb->len < S3FWRN82_NCI_HEADER)
			जारी;

		अगर ((phy->recv_skb->len - S3FWRN82_NCI_HEADER)
				< phy->recv_skb->data[S3FWRN82_NCI_IDX])
			जारी;

		s3fwrn5_recv_frame(phy->common.ndev, phy->recv_skb,
				   phy->common.mode);
		phy->recv_skb = alloc_skb(NCI_SKB_BUFF_LEN, GFP_KERNEL);
		अगर (!phy->recv_skb)
			वापस 0;
	पूर्ण

	वापस i;
पूर्ण

अटल स्थिर काष्ठा serdev_device_ops s3fwrn82_serdev_ops = अणु
	.receive_buf = s3fwrn82_uart_पढ़ो,
	.ग_लिखो_wakeup = serdev_device_ग_लिखो_wakeup,
पूर्ण;

अटल स्थिर काष्ठा of_device_id s3fwrn82_uart_of_match[] = अणु
	अणु .compatible = "samsung,s3fwrn82", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, s3fwrn82_uart_of_match);

अटल पूर्णांक s3fwrn82_uart_parse_dt(काष्ठा serdev_device *serdev)
अणु
	काष्ठा s3fwrn82_uart_phy *phy = serdev_device_get_drvdata(serdev);
	काष्ठा device_node *np = serdev->dev.of_node;

	अगर (!np)
		वापस -ENODEV;

	phy->common.gpio_en = of_get_named_gpio(np, "en-gpios", 0);
	अगर (!gpio_is_valid(phy->common.gpio_en))
		वापस -ENODEV;

	phy->common.gpio_fw_wake = of_get_named_gpio(np, "wake-gpios", 0);
	अगर (!gpio_is_valid(phy->common.gpio_fw_wake))
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक s3fwrn82_uart_probe(काष्ठा serdev_device *serdev)
अणु
	काष्ठा s3fwrn82_uart_phy *phy;
	पूर्णांक ret = -ENOMEM;

	phy = devm_kzalloc(&serdev->dev, माप(*phy), GFP_KERNEL);
	अगर (!phy)
		जाओ err_निकास;

	phy->recv_skb = alloc_skb(NCI_SKB_BUFF_LEN, GFP_KERNEL);
	अगर (!phy->recv_skb)
		जाओ err_निकास;

	mutex_init(&phy->common.mutex);
	phy->common.mode = S3FWRN5_MODE_COLD;

	phy->ser_dev = serdev;
	serdev_device_set_drvdata(serdev, phy);
	serdev_device_set_client_ops(serdev, &s3fwrn82_serdev_ops);
	ret = serdev_device_खोलो(serdev);
	अगर (ret) अणु
		dev_err(&serdev->dev, "Unable to open device\n");
		जाओ err_skb;
	पूर्ण

	ret = serdev_device_set_baudrate(serdev, 115200);
	अगर (ret != 115200) अणु
		ret = -EINVAL;
		जाओ err_serdev;
	पूर्ण

	serdev_device_set_flow_control(serdev, false);

	ret = s3fwrn82_uart_parse_dt(serdev);
	अगर (ret < 0)
		जाओ err_serdev;

	ret = devm_gpio_request_one(&phy->ser_dev->dev, phy->common.gpio_en,
				    GPIOF_OUT_INIT_HIGH, "s3fwrn82_en");
	अगर (ret < 0)
		जाओ err_serdev;

	ret = devm_gpio_request_one(&phy->ser_dev->dev,
				    phy->common.gpio_fw_wake,
				    GPIOF_OUT_INIT_LOW, "s3fwrn82_fw_wake");
	अगर (ret < 0)
		जाओ err_serdev;

	ret = s3fwrn5_probe(&phy->common.ndev, phy, &phy->ser_dev->dev,
			    &uart_phy_ops);
	अगर (ret < 0)
		जाओ err_serdev;

	वापस ret;

err_serdev:
	serdev_device_बंद(serdev);
err_skb:
	kमुक्त_skb(phy->recv_skb);
err_निकास:
	वापस ret;
पूर्ण

अटल व्योम s3fwrn82_uart_हटाओ(काष्ठा serdev_device *serdev)
अणु
	काष्ठा s3fwrn82_uart_phy *phy = serdev_device_get_drvdata(serdev);

	s3fwrn5_हटाओ(phy->common.ndev);
	serdev_device_बंद(serdev);
	kमुक्त_skb(phy->recv_skb);
पूर्ण

अटल काष्ठा serdev_device_driver s3fwrn82_uart_driver = अणु
	.probe = s3fwrn82_uart_probe,
	.हटाओ = s3fwrn82_uart_हटाओ,
	.driver = अणु
		.name = "s3fwrn82_uart",
		.of_match_table = s3fwrn82_uart_of_match,
	पूर्ण,
पूर्ण;

module_serdev_device_driver(s3fwrn82_uart_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("UART driver for Samsung NFC");
MODULE_AUTHOR("Bongsu Jeon <bongsu.jeon@samsung.com>");
