<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम NXP PN533 NFC Chip - I2C transport layer
 *
 * Copyright (C) 2011 Instituto Nokia de Tecnologia
 * Copyright (C) 2012-2013 Tieto Poland
 * Copyright (C) 2016 HALE electronic
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/nfc.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <net/nfc/nfc.h>
#समावेश "pn533.h"

#घोषणा VERSION "0.1"

#घोषणा PN533_I2C_DRIVER_NAME "pn533_i2c"

काष्ठा pn533_i2c_phy अणु
	काष्ठा i2c_client *i2c_dev;
	काष्ठा pn533 *priv;

	bool पातed;

	पूर्णांक hard_fault;		/*
				 * < 0 अगर hardware error occurred (e.g. i2c err)
				 * and prevents normal operation.
				 */
पूर्ण;

अटल पूर्णांक pn533_i2c_send_ack(काष्ठा pn533 *dev, gfp_t flags)
अणु
	काष्ठा pn533_i2c_phy *phy = dev->phy;
	काष्ठा i2c_client *client = phy->i2c_dev;
	अटल स्थिर u8 ack[6] = अणु0x00, 0x00, 0xff, 0x00, 0xff, 0x00पूर्ण;
	/* spec 6.2.1.3:  Preamble, SoPC (2), ACK Code (2), Postamble */

	वापस i2c_master_send(client, ack, 6);
पूर्ण

अटल पूर्णांक pn533_i2c_send_frame(काष्ठा pn533 *dev,
				काष्ठा sk_buff *out)
अणु
	काष्ठा pn533_i2c_phy *phy = dev->phy;
	काष्ठा i2c_client *client = phy->i2c_dev;
	पूर्णांक rc;

	अगर (phy->hard_fault != 0)
		वापस phy->hard_fault;

	अगर (phy->priv == शून्य)
		phy->priv = dev;

	phy->पातed = false;

	prपूर्णांक_hex_dump_debug("PN533_i2c TX: ", DUMP_PREFIX_NONE, 16, 1,
			     out->data, out->len, false);

	rc = i2c_master_send(client, out->data, out->len);

	अगर (rc == -EREMOTEIO) अणु /* Retry, chip was in घातer करोwn */
		usleep_range(6000, 10000);
		rc = i2c_master_send(client, out->data, out->len);
	पूर्ण

	अगर (rc >= 0) अणु
		अगर (rc != out->len)
			rc = -EREMOTEIO;
		अन्यथा
			rc = 0;
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम pn533_i2c_पात_cmd(काष्ठा pn533 *dev, gfp_t flags)
अणु
	काष्ठा pn533_i2c_phy *phy = dev->phy;

	phy->पातed = true;

	/* An ack will cancel the last issued command */
	pn533_i2c_send_ack(dev, flags);

	/* schedule cmd_complete_work to finish current command execution */
	pn533_recv_frame(phy->priv, शून्य, -ENOENT);
पूर्ण

अटल पूर्णांक pn533_i2c_पढ़ो(काष्ठा pn533_i2c_phy *phy, काष्ठा sk_buff **skb)
अणु
	काष्ठा i2c_client *client = phy->i2c_dev;
	पूर्णांक len = PN533_EXT_FRAME_HEADER_LEN +
		  PN533_STD_FRAME_MAX_PAYLOAD_LEN +
		  PN533_STD_FRAME_TAIL_LEN + 1;
	पूर्णांक r;

	*skb = alloc_skb(len, GFP_KERNEL);
	अगर (*skb == शून्य)
		वापस -ENOMEM;

	r = i2c_master_recv(client, skb_put(*skb, len), len);
	अगर (r != len) अणु
		nfc_err(&client->dev, "cannot read. r=%d len=%d\n", r, len);
		kमुक्त_skb(*skb);
		वापस -EREMOTEIO;
	पूर्ण

	अगर (!((*skb)->data[0] & 0x01)) अणु
		nfc_err(&client->dev, "READY flag not set");
		kमुक्त_skb(*skb);
		वापस -EBUSY;
	पूर्ण

	/* हटाओ READY byte */
	skb_pull(*skb, 1);
	/* trim to frame size */
	skb_trim(*skb, phy->priv->ops->rx_frame_size((*skb)->data));

	वापस 0;
पूर्ण

अटल irqवापस_t pn533_i2c_irq_thपढ़ो_fn(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा pn533_i2c_phy *phy = data;
	काष्ठा i2c_client *client;
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक r;

	अगर (!phy || irq != phy->i2c_dev->irq) अणु
		WARN_ON_ONCE(1);
		वापस IRQ_NONE;
	पूर्ण

	client = phy->i2c_dev;
	dev_dbg(&client->dev, "IRQ\n");

	अगर (phy->hard_fault != 0)
		वापस IRQ_HANDLED;

	r = pn533_i2c_पढ़ो(phy, &skb);
	अगर (r == -EREMOTEIO) अणु
		phy->hard_fault = r;

		pn533_recv_frame(phy->priv, शून्य, -EREMOTEIO);

		वापस IRQ_HANDLED;
	पूर्ण अन्यथा अगर ((r == -ENOMEM) || (r == -EBADMSG) || (r == -EBUSY)) अणु
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (!phy->पातed)
		pn533_recv_frame(phy->priv, skb, 0);

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा pn533_phy_ops i2c_phy_ops = अणु
	.send_frame = pn533_i2c_send_frame,
	.send_ack = pn533_i2c_send_ack,
	.पात_cmd = pn533_i2c_पात_cmd,
पूर्ण;


अटल पूर्णांक pn533_i2c_probe(काष्ठा i2c_client *client,
			       स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा pn533_i2c_phy *phy;
	काष्ठा pn533 *priv;
	पूर्णांक r = 0;

	dev_dbg(&client->dev, "%s\n", __func__);
	dev_dbg(&client->dev, "IRQ: %d\n", client->irq);

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		nfc_err(&client->dev, "Need I2C_FUNC_I2C\n");
		वापस -ENODEV;
	पूर्ण

	phy = devm_kzalloc(&client->dev, माप(काष्ठा pn533_i2c_phy),
			   GFP_KERNEL);
	अगर (!phy)
		वापस -ENOMEM;

	phy->i2c_dev = client;
	i2c_set_clientdata(client, phy);

	priv = pn53x_common_init(PN533_DEVICE_PN532,
				PN533_PROTO_REQ_ACK_RESP,
				phy, &i2c_phy_ops, शून्य,
				&phy->i2c_dev->dev);

	अगर (IS_ERR(priv)) अणु
		वापस PTR_ERR(priv);
	पूर्ण

	phy->priv = priv;
	r = pn532_i2c_nfc_alloc(priv, PN533_NO_TYPE_B_PROTOCOLS, &client->dev);
	अगर (r)
		जाओ nfc_alloc_err;

	r = request_thपढ़ोed_irq(client->irq, शून्य, pn533_i2c_irq_thपढ़ो_fn,
				IRQF_TRIGGER_FALLING |
				IRQF_SHARED | IRQF_ONESHOT,
				PN533_I2C_DRIVER_NAME, phy);
	अगर (r < 0) अणु
		nfc_err(&client->dev, "Unable to register IRQ handler\n");
		जाओ irq_rqst_err;
	पूर्ण

	r = pn533_finalize_setup(priv);
	अगर (r)
		जाओ fn_setup_err;

	r = nfc_रेजिस्टर_device(priv->nfc_dev);
	अगर (r)
		जाओ fn_setup_err;

	वापस r;

fn_setup_err:
	मुक्त_irq(client->irq, phy);

irq_rqst_err:
	nfc_मुक्त_device(priv->nfc_dev);

nfc_alloc_err:
	pn53x_common_clean(phy->priv);

	वापस r;
पूर्ण

अटल पूर्णांक pn533_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा pn533_i2c_phy *phy = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "%s\n", __func__);

	मुक्त_irq(client->irq, phy);

	pn53x_unरेजिस्टर_nfc(phy->priv);
	pn53x_common_clean(phy->priv);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_pn533_i2c_match[] = अणु
	अणु .compatible = "nxp,pn532", पूर्ण,
	/*
	 * NOTE: The use of the compatibles with the trailing "...-i2c" is
	 * deprecated and will be हटाओd.
	 */
	अणु .compatible = "nxp,pn533-i2c", पूर्ण,
	अणु .compatible = "nxp,pn532-i2c", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_pn533_i2c_match);

अटल स्थिर काष्ठा i2c_device_id pn533_i2c_id_table[] = अणु
	अणु PN533_I2C_DRIVER_NAME, 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, pn533_i2c_id_table);

अटल काष्ठा i2c_driver pn533_i2c_driver = अणु
	.driver = अणु
		   .name = PN533_I2C_DRIVER_NAME,
		   .of_match_table = of_match_ptr(of_pn533_i2c_match),
		  पूर्ण,
	.probe = pn533_i2c_probe,
	.id_table = pn533_i2c_id_table,
	.हटाओ = pn533_i2c_हटाओ,
पूर्ण;

module_i2c_driver(pn533_i2c_driver);

MODULE_AUTHOR("Michael Thalmeier <michael.thalmeier@hale.at>");
MODULE_DESCRIPTION("PN533 I2C driver ver " VERSION);
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL");
