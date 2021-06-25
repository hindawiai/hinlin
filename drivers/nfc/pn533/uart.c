<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम NXP PN532 NFC Chip - UART transport layer
 *
 * Copyright (C) 2018 Lemonage Software GmbH
 * Author: Lars Pथघschel <poeschel@lemonage.de>
 * All rights reserved.
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/nfc.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/of.h>
#समावेश <linux/serdev.h>
#समावेश "pn533.h"

#घोषणा PN532_UART_SKB_BUFF_LEN	(PN533_CMD_DATAEXCH_DATA_MAXLEN * 2)

क्रमागत send_wakeup अणु
	PN532_SEND_NO_WAKEUP = 0,
	PN532_SEND_WAKEUP,
	PN532_SEND_LAST_WAKEUP,
पूर्ण;


काष्ठा pn532_uart_phy अणु
	काष्ठा serdev_device *serdev;
	काष्ठा sk_buff *recv_skb;
	काष्ठा pn533 *priv;
	/*
	 * send_wakeup variable is used to control अगर we need to send a wakeup
	 * request to the pn532 chip prior to our actual command. There is a
	 * little propability of a race condition. We decided to not mutex the
	 * variable as the worst that could happen is, that we send a wakeup
	 * to the chip that is alपढ़ोy awake. This करोes not hurt. It is a
	 * no-op to the chip.
	 */
	क्रमागत send_wakeup send_wakeup;
	काष्ठा समयr_list cmd_समयout;
	काष्ठा sk_buff *cur_out_buf;
पूर्ण;

अटल पूर्णांक pn532_uart_send_frame(काष्ठा pn533 *dev,
				काष्ठा sk_buff *out)
अणु
	/* wakeup sequence and dummy bytes क्रम रुकोing समय */
	अटल स्थिर u8 wakeup[] = अणु
		0x55, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00पूर्ण;
	काष्ठा pn532_uart_phy *pn532 = dev->phy;
	पूर्णांक err;

	prपूर्णांक_hex_dump_debug("PN532_uart TX: ", DUMP_PREFIX_NONE, 16, 1,
			     out->data, out->len, false);

	pn532->cur_out_buf = out;
	अगर (pn532->send_wakeup) अणु
		err = serdev_device_ग_लिखो(pn532->serdev,
				wakeup, माप(wakeup),
				MAX_SCHEDULE_TIMEOUT);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (pn532->send_wakeup == PN532_SEND_LAST_WAKEUP)
		pn532->send_wakeup = PN532_SEND_NO_WAKEUP;

	err = serdev_device_ग_लिखो(pn532->serdev, out->data, out->len,
			MAX_SCHEDULE_TIMEOUT);
	अगर (err < 0)
		वापस err;

	mod_समयr(&pn532->cmd_समयout, HZ / 40 + jअगरfies);
	वापस 0;
पूर्ण

अटल पूर्णांक pn532_uart_send_ack(काष्ठा pn533 *dev, gfp_t flags)
अणु
	/* spec 7.1.1.3:  Preamble, SoPC (2), ACK Code (2), Postamble */
	अटल स्थिर u8 ack[PN533_STD_FRAME_ACK_SIZE] = अणु
			0x00, 0x00, 0xff, 0x00, 0xff, 0x00पूर्ण;
	काष्ठा pn532_uart_phy *pn532 = dev->phy;
	पूर्णांक err;

	err = serdev_device_ग_लिखो(pn532->serdev, ack, माप(ack),
			MAX_SCHEDULE_TIMEOUT);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल व्योम pn532_uart_पात_cmd(काष्ठा pn533 *dev, gfp_t flags)
अणु
	/* An ack will cancel the last issued command */
	pn532_uart_send_ack(dev, flags);
	/* schedule cmd_complete_work to finish current command execution */
	pn533_recv_frame(dev, शून्य, -ENOENT);
पूर्ण

अटल पूर्णांक pn532_dev_up(काष्ठा pn533 *dev)
अणु
	काष्ठा pn532_uart_phy *pn532 = dev->phy;
	पूर्णांक ret = 0;

	ret = serdev_device_खोलो(pn532->serdev);
	अगर (ret)
		वापस ret;

	pn532->send_wakeup = PN532_SEND_LAST_WAKEUP;
	वापस ret;
पूर्ण

अटल पूर्णांक pn532_dev_करोwn(काष्ठा pn533 *dev)
अणु
	काष्ठा pn532_uart_phy *pn532 = dev->phy;

	serdev_device_बंद(pn532->serdev);
	pn532->send_wakeup = PN532_SEND_WAKEUP;

	वापस 0;
पूर्ण

अटल काष्ठा pn533_phy_ops uart_phy_ops = अणु
	.send_frame = pn532_uart_send_frame,
	.send_ack = pn532_uart_send_ack,
	.पात_cmd = pn532_uart_पात_cmd,
	.dev_up = pn532_dev_up,
	.dev_करोwn = pn532_dev_करोwn,
पूर्ण;

अटल व्योम pn532_cmd_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा pn532_uart_phy *dev = from_समयr(dev, t, cmd_समयout);

	pn532_uart_send_frame(dev->priv, dev->cur_out_buf);
पूर्ण

/*
 * scans the buffer अगर it contains a pn532 frame. It is not checked अगर the
 * frame is really valid. This is later करोne with pn533_rx_frame_is_valid.
 * This is useful क्रम malक्रमmed or errornous transmitted frames. Adjusts the
 * bufferposition where the frame starts, since pn533_recv_frame expects a
 * well क्रमmed frame.
 */
अटल पूर्णांक pn532_uart_rx_is_frame(काष्ठा sk_buff *skb)
अणु
	काष्ठा pn533_std_frame *std;
	काष्ठा pn533_ext_frame *ext;
	u16 frame_len;
	पूर्णांक i;

	क्रम (i = 0; i + PN533_STD_FRAME_ACK_SIZE <= skb->len; i++) अणु
		std = (काष्ठा pn533_std_frame *)&skb->data[i];
		/* search start code */
		अगर (std->start_frame != cpu_to_be16(PN533_STD_FRAME_SOF))
			जारी;

		/* frame type */
		चयन (std->datalen) अणु
		हाल PN533_FRAME_DATALEN_ACK:
			अगर (std->datalen_checksum == 0xff) अणु
				skb_pull(skb, i);
				वापस 1;
			पूर्ण

			अवरोध;
		हाल PN533_FRAME_DATALEN_ERROR:
			अगर ((std->datalen_checksum == 0xff) &&
					(skb->len >=
					 PN533_STD_ERROR_FRAME_SIZE)) अणु
				skb_pull(skb, i);
				वापस 1;
			पूर्ण

			अवरोध;
		हाल PN533_FRAME_DATALEN_EXTENDED:
			ext = (काष्ठा pn533_ext_frame *)&skb->data[i];
			frame_len = be16_to_cpu(ext->datalen);
			अगर (skb->len >= frame_len +
					माप(काष्ठा pn533_ext_frame) +
					2 /* CKS + Postamble */) अणु
				skb_pull(skb, i);
				वापस 1;
			पूर्ण

			अवरोध;
		शेष: /* normal inक्रमmation frame */
			frame_len = std->datalen;
			अगर (skb->len >= frame_len +
					माप(काष्ठा pn533_std_frame) +
					2 /* CKS + Postamble */) अणु
				skb_pull(skb, i);
				वापस 1;
			पूर्ण

			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pn532_receive_buf(काष्ठा serdev_device *serdev,
		स्थिर अचिन्हित अक्षर *data, माप_प्रकार count)
अणु
	काष्ठा pn532_uart_phy *dev = serdev_device_get_drvdata(serdev);
	माप_प्रकार i;

	del_समयr(&dev->cmd_समयout);
	क्रम (i = 0; i < count; i++) अणु
		skb_put_u8(dev->recv_skb, *data++);
		अगर (!pn532_uart_rx_is_frame(dev->recv_skb))
			जारी;

		pn533_recv_frame(dev->priv, dev->recv_skb, 0);
		dev->recv_skb = alloc_skb(PN532_UART_SKB_BUFF_LEN, GFP_KERNEL);
		अगर (!dev->recv_skb)
			वापस 0;
	पूर्ण

	वापस i;
पूर्ण

अटल काष्ठा serdev_device_ops pn532_serdev_ops = अणु
	.receive_buf = pn532_receive_buf,
	.ग_लिखो_wakeup = serdev_device_ग_लिखो_wakeup,
पूर्ण;

अटल स्थिर काष्ठा of_device_id pn532_uart_of_match[] = अणु
	अणु .compatible = "nxp,pn532", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, pn532_uart_of_match);

अटल पूर्णांक pn532_uart_probe(काष्ठा serdev_device *serdev)
अणु
	काष्ठा pn532_uart_phy *pn532;
	काष्ठा pn533 *priv;
	पूर्णांक err;

	err = -ENOMEM;
	pn532 = kzalloc(माप(*pn532), GFP_KERNEL);
	अगर (!pn532)
		जाओ err_निकास;

	pn532->recv_skb = alloc_skb(PN532_UART_SKB_BUFF_LEN, GFP_KERNEL);
	अगर (!pn532->recv_skb)
		जाओ err_मुक्त;

	pn532->serdev = serdev;
	serdev_device_set_drvdata(serdev, pn532);
	serdev_device_set_client_ops(serdev, &pn532_serdev_ops);
	err = serdev_device_खोलो(serdev);
	अगर (err) अणु
		dev_err(&serdev->dev, "Unable to open device\n");
		जाओ err_skb;
	पूर्ण

	err = serdev_device_set_baudrate(serdev, 115200);
	अगर (err != 115200) अणु
		err = -EINVAL;
		जाओ err_serdev;
	पूर्ण

	serdev_device_set_flow_control(serdev, false);
	pn532->send_wakeup = PN532_SEND_WAKEUP;
	समयr_setup(&pn532->cmd_समयout, pn532_cmd_समयout, 0);
	priv = pn53x_common_init(PN533_DEVICE_PN532_AUTOPOLL,
				     PN533_PROTO_REQ_ACK_RESP,
				     pn532, &uart_phy_ops, शून्य,
				     &pn532->serdev->dev);
	अगर (IS_ERR(priv)) अणु
		err = PTR_ERR(priv);
		जाओ err_serdev;
	पूर्ण

	pn532->priv = priv;
	err = pn533_finalize_setup(pn532->priv);
	अगर (err)
		जाओ err_clean;

	serdev_device_बंद(serdev);
	err = pn53x_रेजिस्टर_nfc(priv, PN533_NO_TYPE_B_PROTOCOLS, &serdev->dev);
	अगर (err) अणु
		pn53x_common_clean(pn532->priv);
		जाओ err_skb;
	पूर्ण

	वापस err;

err_clean:
	pn53x_common_clean(pn532->priv);
err_serdev:
	serdev_device_बंद(serdev);
err_skb:
	kमुक्त_skb(pn532->recv_skb);
err_मुक्त:
	kमुक्त(pn532);
err_निकास:
	वापस err;
पूर्ण

अटल व्योम pn532_uart_हटाओ(काष्ठा serdev_device *serdev)
अणु
	काष्ठा pn532_uart_phy *pn532 = serdev_device_get_drvdata(serdev);

	pn53x_unरेजिस्टर_nfc(pn532->priv);
	serdev_device_बंद(serdev);
	pn53x_common_clean(pn532->priv);
	kमुक्त_skb(pn532->recv_skb);
	kमुक्त(pn532);
पूर्ण

अटल काष्ठा serdev_device_driver pn532_uart_driver = अणु
	.probe = pn532_uart_probe,
	.हटाओ = pn532_uart_हटाओ,
	.driver = अणु
		.name = "pn532_uart",
		.of_match_table = of_match_ptr(pn532_uart_of_match),
	पूर्ण,
पूर्ण;

module_serdev_device_driver(pn532_uart_driver);

MODULE_AUTHOR("Lars Pथघschel <poeschel@lemonage.de>");
MODULE_DESCRIPTION("PN532 UART driver");
MODULE_LICENSE("GPL");
