<शैली गुरु>
/*
 * Marvell NFC-over-I2C driver: I2C पूर्णांकerface related functions
 *
 * Copyright (C) 2015, Marvell International Ltd.
 *
 * This software file (the "File") is distributed by Marvell International
 * Ltd. under the terms of the GNU General Public License Version 2, June 1991
 * (the "License").  You may use, redistribute and/or modअगरy this File in
 * accordance with the terms and conditions of the License, a copy of which
 * is available on the worldwide web at
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 * THE खाता IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE
 * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about
 * this warranty disclaimer.
 **/

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/i2c.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/nfc.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/delay.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_gpपन.स>
#समावेश <net/nfc/nci.h>
#समावेश <net/nfc/nci_core.h>
#समावेश "nfcmrvl.h"

काष्ठा nfcmrvl_i2c_drv_data अणु
	अचिन्हित दीर्घ flags;
	काष्ठा device *dev;
	काष्ठा i2c_client *i2c;
	काष्ठा nfcmrvl_निजी *priv;
पूर्ण;

अटल पूर्णांक nfcmrvl_i2c_पढ़ो(काष्ठा nfcmrvl_i2c_drv_data *drv_data,
			    काष्ठा sk_buff **skb)
अणु
	पूर्णांक ret;
	काष्ठा nci_ctrl_hdr nci_hdr;

	/* Read NCI header to know the payload size */
	ret = i2c_master_recv(drv_data->i2c, (u8 *)&nci_hdr, NCI_CTRL_HDR_SIZE);
	अगर (ret != NCI_CTRL_HDR_SIZE) अणु
		nfc_err(&drv_data->i2c->dev, "cannot read NCI header\n");
		वापस -EBADMSG;
	पूर्ण

	अगर (nci_hdr.plen > NCI_MAX_PAYLOAD_SIZE) अणु
		nfc_err(&drv_data->i2c->dev, "invalid packet payload size\n");
		वापस -EBADMSG;
	पूर्ण

	*skb = nci_skb_alloc(drv_data->priv->ndev,
			     nci_hdr.plen + NCI_CTRL_HDR_SIZE, GFP_KERNEL);
	अगर (!*skb)
		वापस -ENOMEM;

	/* Copy NCI header पूर्णांकo the SKB */
	skb_put_data(*skb, &nci_hdr, NCI_CTRL_HDR_SIZE);

	अगर (nci_hdr.plen) अणु
		/* Read the NCI payload */
		ret = i2c_master_recv(drv_data->i2c,
				      skb_put(*skb, nci_hdr.plen),
				      nci_hdr.plen);

		अगर (ret != nci_hdr.plen) अणु
			nfc_err(&drv_data->i2c->dev,
				"Invalid frame payload length: %u (expected %u)\n",
				ret, nci_hdr.plen);
			kमुक्त_skb(*skb);
			वापस -EBADMSG;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t nfcmrvl_i2c_पूर्णांक_irq_thपढ़ो_fn(पूर्णांक irq, व्योम *drv_data_ptr)
अणु
	काष्ठा nfcmrvl_i2c_drv_data *drv_data = drv_data_ptr;
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक ret;

	अगर (!drv_data->priv)
		वापस IRQ_HANDLED;

	अगर (test_bit(NFCMRVL_PHY_ERROR, &drv_data->priv->flags))
		वापस IRQ_HANDLED;

	ret = nfcmrvl_i2c_पढ़ो(drv_data, &skb);

	चयन (ret) अणु
	हाल -EREMOTEIO:
		set_bit(NFCMRVL_PHY_ERROR, &drv_data->priv->flags);
		अवरोध;
	हाल -ENOMEM:
	हाल -EBADMSG:
		nfc_err(&drv_data->i2c->dev, "read failed %d\n", ret);
		अवरोध;
	शेष:
		अगर (nfcmrvl_nci_recv_frame(drv_data->priv, skb) < 0)
			nfc_err(&drv_data->i2c->dev, "corrupted RX packet\n");
		अवरोध;
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक nfcmrvl_i2c_nci_खोलो(काष्ठा nfcmrvl_निजी *priv)
अणु
	काष्ठा nfcmrvl_i2c_drv_data *drv_data = priv->drv_data;

	अगर (!drv_data)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक nfcmrvl_i2c_nci_बंद(काष्ठा nfcmrvl_निजी *priv)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक nfcmrvl_i2c_nci_send(काष्ठा nfcmrvl_निजी *priv,
				काष्ठा sk_buff *skb)
अणु
	काष्ठा nfcmrvl_i2c_drv_data *drv_data = priv->drv_data;
	पूर्णांक ret;

	अगर (test_bit(NFCMRVL_PHY_ERROR, &priv->flags))
		वापस -EREMOTEIO;

	ret = i2c_master_send(drv_data->i2c, skb->data, skb->len);

	/* Retry अगर chip was in standby */
	अगर (ret == -EREMOTEIO) अणु
		nfc_info(drv_data->dev, "chip may sleep, retry\n");
		usleep_range(6000, 10000);
		ret = i2c_master_send(drv_data->i2c, skb->data, skb->len);
	पूर्ण

	अगर (ret >= 0) अणु
		अगर (ret != skb->len) अणु
			nfc_err(drv_data->dev,
				"Invalid length sent: %u (expected %u)\n",
				ret, skb->len);
			ret = -EREMOTEIO;
		पूर्ण अन्यथा
			ret = 0;
		kमुक्त_skb(skb);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम nfcmrvl_i2c_nci_update_config(काष्ठा nfcmrvl_निजी *priv,
					  स्थिर व्योम *param)
अणु
पूर्ण

अटल काष्ठा nfcmrvl_अगर_ops i2c_ops = अणु
	.nci_खोलो = nfcmrvl_i2c_nci_खोलो,
	.nci_बंद = nfcmrvl_i2c_nci_बंद,
	.nci_send = nfcmrvl_i2c_nci_send,
	.nci_update_config = nfcmrvl_i2c_nci_update_config,
पूर्ण;

अटल पूर्णांक nfcmrvl_i2c_parse_dt(काष्ठा device_node *node,
				काष्ठा nfcmrvl_platक्रमm_data *pdata)
अणु
	पूर्णांक ret;

	ret = nfcmrvl_parse_dt(node, pdata);
	अगर (ret < 0) अणु
		pr_err("Failed to get generic entries\n");
		वापस ret;
	पूर्ण

	अगर (of_find_property(node, "i2c-int-falling", शून्य))
		pdata->irq_polarity = IRQF_TRIGGER_FALLING;
	अन्यथा
		pdata->irq_polarity = IRQF_TRIGGER_RISING;

	ret = irq_of_parse_and_map(node, 0);
	अगर (ret < 0) अणु
		pr_err("Unable to get irq, error: %d\n", ret);
		वापस ret;
	पूर्ण
	pdata->irq = ret;

	वापस 0;
पूर्ण

अटल पूर्णांक nfcmrvl_i2c_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा nfcmrvl_i2c_drv_data *drv_data;
	काष्ठा nfcmrvl_platक्रमm_data *pdata;
	काष्ठा nfcmrvl_platक्रमm_data config;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		nfc_err(&client->dev, "Need I2C_FUNC_I2C\n");
		वापस -ENODEV;
	पूर्ण

	drv_data = devm_kzalloc(&client->dev, माप(*drv_data), GFP_KERNEL);
	अगर (!drv_data)
		वापस -ENOMEM;

	drv_data->i2c = client;
	drv_data->dev = &client->dev;
	drv_data->priv = शून्य;

	i2c_set_clientdata(client, drv_data);

	pdata = client->dev.platक्रमm_data;

	अगर (!pdata && client->dev.of_node)
		अगर (nfcmrvl_i2c_parse_dt(client->dev.of_node, &config) == 0)
			pdata = &config;

	अगर (!pdata)
		वापस -EINVAL;

	/* Request the पढ़ो IRQ */
	ret = devm_request_thपढ़ोed_irq(&drv_data->i2c->dev, pdata->irq,
					शून्य, nfcmrvl_i2c_पूर्णांक_irq_thपढ़ो_fn,
					pdata->irq_polarity | IRQF_ONESHOT,
					"nfcmrvl_i2c_int", drv_data);
	अगर (ret < 0) अणु
		nfc_err(&drv_data->i2c->dev,
			"Unable to register IRQ handler\n");
		वापस ret;
	पूर्ण

	drv_data->priv = nfcmrvl_nci_रेजिस्टर_dev(NFCMRVL_PHY_I2C,
						  drv_data, &i2c_ops,
						  &drv_data->i2c->dev, pdata);

	अगर (IS_ERR(drv_data->priv))
		वापस PTR_ERR(drv_data->priv);

	drv_data->priv->support_fw_dnld = true;

	वापस 0;
पूर्ण

अटल पूर्णांक nfcmrvl_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा nfcmrvl_i2c_drv_data *drv_data = i2c_get_clientdata(client);

	nfcmrvl_nci_unरेजिस्टर_dev(drv_data->priv);

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा of_device_id of_nfcmrvl_i2c_match[] = अणु
	अणु .compatible = "marvell,nfc-i2c", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_nfcmrvl_i2c_match);

अटल स्थिर काष्ठा i2c_device_id nfcmrvl_i2c_id_table[] = अणु
	अणु "nfcmrvl_i2c", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, nfcmrvl_i2c_id_table);

अटल काष्ठा i2c_driver nfcmrvl_i2c_driver = अणु
	.probe = nfcmrvl_i2c_probe,
	.id_table = nfcmrvl_i2c_id_table,
	.हटाओ = nfcmrvl_i2c_हटाओ,
	.driver = अणु
		.name		= "nfcmrvl_i2c",
		.of_match_table	= of_match_ptr(of_nfcmrvl_i2c_match),
	पूर्ण,
पूर्ण;

module_i2c_driver(nfcmrvl_i2c_driver);

MODULE_AUTHOR("Marvell International Ltd.");
MODULE_DESCRIPTION("Marvell NFC-over-I2C driver");
MODULE_LICENSE("GPL v2");
