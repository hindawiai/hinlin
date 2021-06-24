<शैली गुरु>
/*
 * Marvell NFC driver: major functions
 *
 * Copyright (C) 2014-2015 Marvell International Ltd.
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
 */

#समावेश <linux/module.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/delay.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/nfc.h>
#समावेश <net/nfc/nci.h>
#समावेश <net/nfc/nci_core.h>
#समावेश "nfcmrvl.h"

अटल पूर्णांक nfcmrvl_nci_खोलो(काष्ठा nci_dev *ndev)
अणु
	काष्ठा nfcmrvl_निजी *priv = nci_get_drvdata(ndev);
	पूर्णांक err;

	अगर (test_and_set_bit(NFCMRVL_NCI_RUNNING, &priv->flags))
		वापस 0;

	/* Reset possible fault of previous session */
	clear_bit(NFCMRVL_PHY_ERROR, &priv->flags);

	err = priv->अगर_ops->nci_खोलो(priv);

	अगर (err)
		clear_bit(NFCMRVL_NCI_RUNNING, &priv->flags);

	वापस err;
पूर्ण

अटल पूर्णांक nfcmrvl_nci_बंद(काष्ठा nci_dev *ndev)
अणु
	काष्ठा nfcmrvl_निजी *priv = nci_get_drvdata(ndev);

	अगर (!test_and_clear_bit(NFCMRVL_NCI_RUNNING, &priv->flags))
		वापस 0;

	priv->अगर_ops->nci_बंद(priv);

	वापस 0;
पूर्ण

अटल पूर्णांक nfcmrvl_nci_send(काष्ठा nci_dev *ndev, काष्ठा sk_buff *skb)
अणु
	काष्ठा nfcmrvl_निजी *priv = nci_get_drvdata(ndev);

	nfc_info(priv->dev, "send entry, len %d\n", skb->len);

	skb->dev = (व्योम *)ndev;

	अगर (priv->config.hci_muxed) अणु
		अचिन्हित अक्षर *hdr;
		अचिन्हित अक्षर len = skb->len;

		hdr = skb_push(skb, NFCMRVL_HCI_EVENT_HEADER_SIZE);
		hdr[0] = NFCMRVL_HCI_COMMAND_CODE;
		hdr[1] = NFCMRVL_HCI_OGF;
		hdr[2] = NFCMRVL_HCI_OCF;
		hdr[3] = len;
	पूर्ण

	वापस priv->अगर_ops->nci_send(priv, skb);
पूर्ण

अटल पूर्णांक nfcmrvl_nci_setup(काष्ठा nci_dev *ndev)
अणु
	__u8 val = 1;

	nci_set_config(ndev, NFCMRVL_PB_BAIL_OUT, 1, &val);
	वापस 0;
पूर्ण

अटल पूर्णांक nfcmrvl_nci_fw_करोwnload(काष्ठा nci_dev *ndev,
				   स्थिर अक्षर *firmware_name)
अणु
	वापस nfcmrvl_fw_dnld_start(ndev, firmware_name);
पूर्ण

अटल काष्ठा nci_ops nfcmrvl_nci_ops = अणु
	.खोलो = nfcmrvl_nci_खोलो,
	.बंद = nfcmrvl_nci_बंद,
	.send = nfcmrvl_nci_send,
	.setup = nfcmrvl_nci_setup,
	.fw_करोwnload = nfcmrvl_nci_fw_करोwnload,
पूर्ण;

काष्ठा nfcmrvl_निजी *nfcmrvl_nci_रेजिस्टर_dev(क्रमागत nfcmrvl_phy phy,
				व्योम *drv_data,
				काष्ठा nfcmrvl_अगर_ops *ops,
				काष्ठा device *dev,
				काष्ठा nfcmrvl_platक्रमm_data *pdata)
अणु
	काष्ठा nfcmrvl_निजी *priv;
	पूर्णांक rc;
	पूर्णांक headroom;
	पूर्णांक tailroom;
	u32 protocols;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस ERR_PTR(-ENOMEM);

	priv->drv_data = drv_data;
	priv->अगर_ops = ops;
	priv->dev = dev;
	priv->phy = phy;

	स_नकल(&priv->config, pdata, माप(*pdata));

	अगर (gpio_is_valid(priv->config.reset_n_io)) अणु
		rc = gpio_request_one(priv->config.reset_n_io,
				      GPIOF_OUT_INIT_LOW,
				      "nfcmrvl_reset_n");
		अगर (rc < 0) अणु
			priv->config.reset_n_io = -EINVAL;
			nfc_err(dev, "failed to request reset_n io\n");
		पूर्ण
	पूर्ण

	अगर (phy == NFCMRVL_PHY_SPI) अणु
		headroom = NCI_SPI_HDR_LEN;
		tailroom = 1;
	पूर्ण अन्यथा
		headroom = tailroom = 0;

	अगर (priv->config.hci_muxed)
		headroom += NFCMRVL_HCI_EVENT_HEADER_SIZE;

	protocols = NFC_PROTO_JEWEL_MASK
		| NFC_PROTO_MIFARE_MASK
		| NFC_PROTO_FELICA_MASK
		| NFC_PROTO_ISO14443_MASK
		| NFC_PROTO_ISO14443_B_MASK
		| NFC_PROTO_ISO15693_MASK
		| NFC_PROTO_NFC_DEP_MASK;

	priv->ndev = nci_allocate_device(&nfcmrvl_nci_ops, protocols,
					 headroom, tailroom);
	अगर (!priv->ndev) अणु
		nfc_err(dev, "nci_allocate_device failed\n");
		rc = -ENOMEM;
		जाओ error_मुक्त_gpio;
	पूर्ण

	rc = nfcmrvl_fw_dnld_init(priv);
	अगर (rc) अणु
		nfc_err(dev, "failed to initialize FW download %d\n", rc);
		जाओ error_मुक्त_dev;
	पूर्ण

	nci_set_drvdata(priv->ndev, priv);

	rc = nci_रेजिस्टर_device(priv->ndev);
	अगर (rc) अणु
		nfc_err(dev, "nci_register_device failed %d\n", rc);
		जाओ error_fw_dnld_deinit;
	पूर्ण

	/* Ensure that controller is घातered off */
	nfcmrvl_chip_halt(priv);

	nfc_info(dev, "registered with nci successfully\n");
	वापस priv;

error_fw_dnld_deinit:
	nfcmrvl_fw_dnld_deinit(priv);
error_मुक्त_dev:
	nci_मुक्त_device(priv->ndev);
error_मुक्त_gpio:
	अगर (gpio_is_valid(priv->config.reset_n_io))
		gpio_मुक्त(priv->config.reset_n_io);
	kमुक्त(priv);
	वापस ERR_PTR(rc);
पूर्ण
EXPORT_SYMBOL_GPL(nfcmrvl_nci_रेजिस्टर_dev);

व्योम nfcmrvl_nci_unरेजिस्टर_dev(काष्ठा nfcmrvl_निजी *priv)
अणु
	काष्ठा nci_dev *ndev = priv->ndev;

	अगर (priv->ndev->nfc_dev->fw_करोwnload_in_progress)
		nfcmrvl_fw_dnld_पात(priv);

	nfcmrvl_fw_dnld_deinit(priv);

	अगर (gpio_is_valid(priv->config.reset_n_io))
		gpio_मुक्त(priv->config.reset_n_io);

	nci_unरेजिस्टर_device(ndev);
	nci_मुक्त_device(ndev);
	kमुक्त(priv);
पूर्ण
EXPORT_SYMBOL_GPL(nfcmrvl_nci_unरेजिस्टर_dev);

पूर्णांक nfcmrvl_nci_recv_frame(काष्ठा nfcmrvl_निजी *priv, काष्ठा sk_buff *skb)
अणु
	अगर (priv->config.hci_muxed) अणु
		अगर (skb->data[0] == NFCMRVL_HCI_EVENT_CODE &&
		    skb->data[1] == NFCMRVL_HCI_NFC_EVENT_CODE) अणु
			/* Data packet, let's extract NCI payload */
			skb_pull(skb, NFCMRVL_HCI_EVENT_HEADER_SIZE);
		पूर्ण अन्यथा अणु
			/* Skip this packet */
			kमुक्त_skb(skb);
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (priv->ndev->nfc_dev->fw_करोwnload_in_progress) अणु
		nfcmrvl_fw_dnld_recv_frame(priv, skb);
		वापस 0;
	पूर्ण

	अगर (test_bit(NFCMRVL_NCI_RUNNING, &priv->flags))
		nci_recv_frame(priv->ndev, skb);
	अन्यथा अणु
		/* Drop this packet since nobody wants it */
		kमुक्त_skb(skb);
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nfcmrvl_nci_recv_frame);

व्योम nfcmrvl_chip_reset(काष्ठा nfcmrvl_निजी *priv)
अणु
	/* Reset possible fault of previous session */
	clear_bit(NFCMRVL_PHY_ERROR, &priv->flags);

	अगर (gpio_is_valid(priv->config.reset_n_io)) अणु
		nfc_info(priv->dev, "reset the chip\n");
		gpio_set_value(priv->config.reset_n_io, 0);
		usleep_range(5000, 10000);
		gpio_set_value(priv->config.reset_n_io, 1);
	पूर्ण अन्यथा
		nfc_info(priv->dev, "no reset available on this interface\n");
पूर्ण

व्योम nfcmrvl_chip_halt(काष्ठा nfcmrvl_निजी *priv)
अणु
	अगर (gpio_is_valid(priv->config.reset_n_io))
		gpio_set_value(priv->config.reset_n_io, 0);
पूर्ण

पूर्णांक nfcmrvl_parse_dt(काष्ठा device_node *node,
		     काष्ठा nfcmrvl_platक्रमm_data *pdata)
अणु
	पूर्णांक reset_n_io;

	reset_n_io = of_get_named_gpio(node, "reset-n-io", 0);
	अगर (reset_n_io < 0) अणु
		pr_info("no reset-n-io config\n");
	पूर्ण अन्यथा अगर (!gpio_is_valid(reset_n_io)) अणु
		pr_err("invalid reset-n-io GPIO\n");
		वापस reset_n_io;
	पूर्ण
	pdata->reset_n_io = reset_n_io;

	अगर (of_find_property(node, "hci-muxed", शून्य))
		pdata->hci_muxed = 1;
	अन्यथा
		pdata->hci_muxed = 0;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nfcmrvl_parse_dt);

MODULE_AUTHOR("Marvell International Ltd.");
MODULE_DESCRIPTION("Marvell NFC driver");
MODULE_LICENSE("GPL v2");
