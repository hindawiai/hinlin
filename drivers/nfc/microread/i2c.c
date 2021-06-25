<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HCI based Driver क्रम Inside Secure microपढ़ो NFC Chip - i2c layer
 *
 * Copyright (C) 2013 Intel Corporation. All rights reserved.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/gpपन.स>

#समावेश <linux/nfc.h>
#समावेश <net/nfc/hci.h>
#समावेश <net/nfc/llc.h>

#समावेश "microread.h"

#घोषणा MICROREAD_I2C_DRIVER_NAME "microread"

#घोषणा MICROREAD_I2C_FRAME_HEADROOM 1
#घोषणा MICROREAD_I2C_FRAME_TAILROOM 1

/* framing in HCI mode */
#घोषणा MICROREAD_I2C_LLC_LEN		1
#घोषणा MICROREAD_I2C_LLC_CRC		1
#घोषणा MICROREAD_I2C_LLC_LEN_CRC	(MICROREAD_I2C_LLC_LEN + \
					MICROREAD_I2C_LLC_CRC)
#घोषणा MICROREAD_I2C_LLC_MIN_SIZE	(1 + MICROREAD_I2C_LLC_LEN_CRC)
#घोषणा MICROREAD_I2C_LLC_MAX_PAYLOAD	29
#घोषणा MICROREAD_I2C_LLC_MAX_SIZE	(MICROREAD_I2C_LLC_LEN_CRC + 1 + \
					MICROREAD_I2C_LLC_MAX_PAYLOAD)

काष्ठा microपढ़ो_i2c_phy अणु
	काष्ठा i2c_client *i2c_dev;
	काष्ठा nfc_hci_dev *hdev;

	पूर्णांक hard_fault;		/*
				 * < 0 अगर hardware error occured (e.g. i2c err)
				 * and prevents normal operation.
				 */
पूर्ण;

#घोषणा I2C_DUMP_SKB(info, skb)					\
करो अणु								\
	pr_debug("%s:\n", info);				\
	prपूर्णांक_hex_dump(KERN_DEBUG, "i2c: ", DUMP_PREFIX_OFFSET,	\
		       16, 1, (skb)->data, (skb)->len, 0);	\
पूर्ण जबतक (0)

अटल व्योम microपढ़ो_i2c_add_len_crc(काष्ठा sk_buff *skb)
अणु
	पूर्णांक i;
	u8 crc = 0;
	पूर्णांक len;

	len = skb->len;
	*(u8 *)skb_push(skb, 1) = len;

	क्रम (i = 0; i < skb->len; i++)
		crc = crc ^ skb->data[i];

	skb_put_u8(skb, crc);
पूर्ण

अटल व्योम microपढ़ो_i2c_हटाओ_len_crc(काष्ठा sk_buff *skb)
अणु
	skb_pull(skb, MICROREAD_I2C_FRAME_HEADROOM);
	skb_trim(skb, MICROREAD_I2C_FRAME_TAILROOM);
पूर्ण

अटल पूर्णांक check_crc(काष्ठा sk_buff *skb)
अणु
	पूर्णांक i;
	u8 crc = 0;

	क्रम (i = 0; i < skb->len - 1; i++)
		crc = crc ^ skb->data[i];

	अगर (crc != skb->data[skb->len-1]) अणु
		pr_err("CRC error 0x%x != 0x%x\n", crc, skb->data[skb->len-1]);
		pr_info("%s: BAD CRC\n", __func__);
		वापस -EPERM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक microपढ़ो_i2c_enable(व्योम *phy_id)
अणु
	वापस 0;
पूर्ण

अटल व्योम microपढ़ो_i2c_disable(व्योम *phy_id)
अणु
	वापस;
पूर्ण

अटल पूर्णांक microपढ़ो_i2c_ग_लिखो(व्योम *phy_id, काष्ठा sk_buff *skb)
अणु
	पूर्णांक r;
	काष्ठा microपढ़ो_i2c_phy *phy = phy_id;
	काष्ठा i2c_client *client = phy->i2c_dev;

	अगर (phy->hard_fault != 0)
		वापस phy->hard_fault;

	usleep_range(3000, 6000);

	microपढ़ो_i2c_add_len_crc(skb);

	I2C_DUMP_SKB("i2c frame written", skb);

	r = i2c_master_send(client, skb->data, skb->len);

	अगर (r == -EREMOTEIO) अणु	/* Retry, chip was in standby */
		usleep_range(6000, 10000);
		r = i2c_master_send(client, skb->data, skb->len);
	पूर्ण

	अगर (r >= 0) अणु
		अगर (r != skb->len)
			r = -EREMOTEIO;
		अन्यथा
			r = 0;
	पूर्ण

	microपढ़ो_i2c_हटाओ_len_crc(skb);

	वापस r;
पूर्ण


अटल पूर्णांक microपढ़ो_i2c_पढ़ो(काष्ठा microपढ़ो_i2c_phy *phy,
			      काष्ठा sk_buff **skb)
अणु
	पूर्णांक r;
	u8 len;
	u8 पंचांगp[MICROREAD_I2C_LLC_MAX_SIZE - 1];
	काष्ठा i2c_client *client = phy->i2c_dev;

	r = i2c_master_recv(client, &len, 1);
	अगर (r != 1) अणु
		nfc_err(&client->dev, "cannot read len byte\n");
		वापस -EREMOTEIO;
	पूर्ण

	अगर ((len < MICROREAD_I2C_LLC_MIN_SIZE) ||
	    (len > MICROREAD_I2C_LLC_MAX_SIZE)) अणु
		nfc_err(&client->dev, "invalid len byte\n");
		r = -EBADMSG;
		जाओ flush;
	पूर्ण

	*skb = alloc_skb(1 + len, GFP_KERNEL);
	अगर (*skb == शून्य) अणु
		r = -ENOMEM;
		जाओ flush;
	पूर्ण

	skb_put_u8(*skb, len);

	r = i2c_master_recv(client, skb_put(*skb, len), len);
	अगर (r != len) अणु
		kमुक्त_skb(*skb);
		वापस -EREMOTEIO;
	पूर्ण

	I2C_DUMP_SKB("cc frame read", *skb);

	r = check_crc(*skb);
	अगर (r != 0) अणु
		kमुक्त_skb(*skb);
		r = -EBADMSG;
		जाओ flush;
	पूर्ण

	skb_pull(*skb, 1);
	skb_trim(*skb, (*skb)->len - MICROREAD_I2C_FRAME_TAILROOM);

	usleep_range(3000, 6000);

	वापस 0;

flush:
	अगर (i2c_master_recv(client, पंचांगp, माप(पंचांगp)) < 0)
		r = -EREMOTEIO;

	usleep_range(3000, 6000);

	वापस r;
पूर्ण

अटल irqवापस_t microपढ़ो_i2c_irq_thपढ़ो_fn(पूर्णांक irq, व्योम *phy_id)
अणु
	काष्ठा microपढ़ो_i2c_phy *phy = phy_id;
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक r;

	अगर (!phy || irq != phy->i2c_dev->irq) अणु
		WARN_ON_ONCE(1);
		वापस IRQ_NONE;
	पूर्ण

	अगर (phy->hard_fault != 0)
		वापस IRQ_HANDLED;

	r = microपढ़ो_i2c_पढ़ो(phy, &skb);
	अगर (r == -EREMOTEIO) अणु
		phy->hard_fault = r;

		nfc_hci_recv_frame(phy->hdev, शून्य);

		वापस IRQ_HANDLED;
	पूर्ण अन्यथा अगर ((r == -ENOMEM) || (r == -EBADMSG)) अणु
		वापस IRQ_HANDLED;
	पूर्ण

	nfc_hci_recv_frame(phy->hdev, skb);

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा nfc_phy_ops i2c_phy_ops = अणु
	.ग_लिखो = microपढ़ो_i2c_ग_लिखो,
	.enable = microपढ़ो_i2c_enable,
	.disable = microपढ़ो_i2c_disable,
पूर्ण;

अटल पूर्णांक microपढ़ो_i2c_probe(काष्ठा i2c_client *client,
			       स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा microपढ़ो_i2c_phy *phy;
	पूर्णांक r;

	dev_dbg(&client->dev, "client %p\n", client);

	phy = devm_kzalloc(&client->dev, माप(काष्ठा microपढ़ो_i2c_phy),
			   GFP_KERNEL);
	अगर (!phy)
		वापस -ENOMEM;

	i2c_set_clientdata(client, phy);
	phy->i2c_dev = client;

	r = request_thपढ़ोed_irq(client->irq, शून्य, microपढ़ो_i2c_irq_thपढ़ो_fn,
				 IRQF_TRIGGER_RISING | IRQF_ONESHOT,
				 MICROREAD_I2C_DRIVER_NAME, phy);
	अगर (r) अणु
		nfc_err(&client->dev, "Unable to register IRQ handler\n");
		वापस r;
	पूर्ण

	r = microपढ़ो_probe(phy, &i2c_phy_ops, LLC_SHDLC_NAME,
			    MICROREAD_I2C_FRAME_HEADROOM,
			    MICROREAD_I2C_FRAME_TAILROOM,
			    MICROREAD_I2C_LLC_MAX_PAYLOAD, &phy->hdev);
	अगर (r < 0)
		जाओ err_irq;

	nfc_info(&client->dev, "Probed\n");

	वापस 0;

err_irq:
	मुक्त_irq(client->irq, phy);

	वापस r;
पूर्ण

अटल पूर्णांक microपढ़ो_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा microपढ़ो_i2c_phy *phy = i2c_get_clientdata(client);

	microपढ़ो_हटाओ(phy->hdev);

	मुक्त_irq(client->irq, phy);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id microपढ़ो_i2c_id[] = अणु
	अणु MICROREAD_I2C_DRIVER_NAME, 0पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, microपढ़ो_i2c_id);

अटल काष्ठा i2c_driver microपढ़ो_i2c_driver = अणु
	.driver = अणु
		.name = MICROREAD_I2C_DRIVER_NAME,
	पूर्ण,
	.probe		= microपढ़ो_i2c_probe,
	.हटाओ		= microपढ़ो_i2c_हटाओ,
	.id_table	= microपढ़ो_i2c_id,
पूर्ण;

module_i2c_driver(microपढ़ो_i2c_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION(DRIVER_DESC);
