<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम the Chrontel CH7322 CEC Controller
 *
 * Copyright 2020 Google LLC.
 */

/*
 * Notes
 *
 * - This device घातers on in Auto Mode which has limited functionality. This
 *   driver disables Auto Mode when it attaches.
 *
 */

#समावेश <linux/cec.h>
#समावेश <linux/dmi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>
#समावेश <linux/regmap.h>
#समावेश <media/cec.h>
#समावेश <media/cec-notअगरier.h>

#घोषणा CH7322_WRITE		0x00
#घोषणा CH7322_WRITE_MSENT		0x80
#घोषणा CH7322_WRITE_BOK		0x40
#घोषणा CH7322_WRITE_NMASK		0x0f

/* Write buffer is 0x01-0x10 */
#घोषणा CH7322_WRBUF		0x01
#घोषणा CH7322_WRBUF_LEN	0x10

#घोषणा CH7322_READ		0x40
#घोषणा CH7322_READ_NRDT		0x80
#घोषणा CH7322_READ_MSENT		0x20
#घोषणा CH7322_READ_NMASK		0x0f

/* Read buffer is 0x41-0x50 */
#घोषणा CH7322_RDBUF		0x41
#घोषणा CH7322_RDBUF_LEN	0x10

#घोषणा CH7322_MODE		0x11
#घोषणा CH7322_MODE_AUTO		0x78
#घोषणा CH7322_MODE_SW			0xb5

#घोषणा CH7322_RESET		0x12
#घोषणा CH7322_RESET_RST		0x00

#घोषणा CH7322_POWER		0x13
#घोषणा CH7322_POWER_FPD		0x04

#घोषणा CH7322_CFG0		0x17
#घोषणा CH7322_CFG0_EOBEN		0x40
#घोषणा CH7322_CFG0_PEOB		0x20
#घोषणा CH7322_CFG0_CLRSPP		0x10
#घोषणा CH7322_CFG0_FLOW		0x08

#घोषणा CH7322_CFG1		0x1a
#घोषणा CH7322_CFG1_STDBYO		0x04
#घोषणा CH7322_CFG1_HPBP		0x02
#घोषणा CH7322_CFG1_PIO			0x01

#घोषणा CH7322_INTCTL		0x1b
#घोषणा CH7322_INTCTL_INTPB		0x80
#घोषणा CH7322_INTCTL_STDBY		0x40
#घोषणा CH7322_INTCTL_HPDFALL		0x20
#घोषणा CH7322_INTCTL_HPDRISE		0x10
#घोषणा CH7322_INTCTL_RXMSG		0x08
#घोषणा CH7322_INTCTL_TXMSG		0x04
#घोषणा CH7322_INTCTL_NEWPHA		0x02
#घोषणा CH7322_INTCTL_ERROR		0x01

#घोषणा CH7322_DVCLKFNH	0x1d
#घोषणा CH7322_DVCLKFNL	0x1e

#घोषणा CH7322_CTL		0x31
#घोषणा CH7322_CTL_FSTDBY		0x80
#घोषणा CH7322_CTL_PLSEN		0x40
#घोषणा CH7322_CTL_PLSPB		0x20
#घोषणा CH7322_CTL_SPADL		0x10
#घोषणा CH7322_CTL_HINIT		0x08
#घोषणा CH7322_CTL_WPHYA		0x04
#घोषणा CH7322_CTL_H1T			0x02
#घोषणा CH7322_CTL_S1T			0x01

#घोषणा CH7322_PAWH		0x32
#घोषणा CH7322_PAWL		0x33

#घोषणा CH7322_ADDLW		0x34
#घोषणा CH7322_ADDLW_MASK	0xf0

#घोषणा CH7322_ADDLR		0x3d
#घोषणा CH7322_ADDLR_HPD		0x80
#घोषणा CH7322_ADDLR_MASK		0x0f

#घोषणा CH7322_INTDATA		0x3e
#घोषणा CH7322_INTDATA_MODE		0x80
#घोषणा CH7322_INTDATA_STDBY		0x40
#घोषणा CH7322_INTDATA_HPDFALL		0x20
#घोषणा CH7322_INTDATA_HPDRISE		0x10
#घोषणा CH7322_INTDATA_RXMSG		0x08
#घोषणा CH7322_INTDATA_TXMSG		0x04
#घोषणा CH7322_INTDATA_NEWPHA		0x02
#घोषणा CH7322_INTDATA_ERROR		0x01

#घोषणा CH7322_EVENT		0x3f
#घोषणा CH7322_EVENT_TXERR		0x80
#घोषणा CH7322_EVENT_HRST		0x40
#घोषणा CH7322_EVENT_HFST		0x20
#घोषणा CH7322_EVENT_PHACHG		0x10
#घोषणा CH7322_EVENT_ACTST		0x08
#घोषणा CH7322_EVENT_PHARDY		0x04
#घोषणा CH7322_EVENT_BSOK		0x02
#घोषणा CH7322_EVENT_ERRADCF		0x01

#घोषणा CH7322_DID		0x51
#घोषणा CH7322_DID_CH7322		0x5b
#घोषणा CH7322_DID_CH7323		0x5f

#घोषणा CH7322_REVISIONID	0x52

#घोषणा CH7322_PARH		0x53
#घोषणा CH7322_PARL		0x54

#घोषणा CH7322_IOCFG2		0x75
#घोषणा CH7322_IOCFG_CIO		0x80
#घोषणा CH7322_IOCFG_IOCFGMASK		0x78
#घोषणा CH7322_IOCFG_AUDIO		0x04
#घोषणा CH7322_IOCFG_SPAMST		0x02
#घोषणा CH7322_IOCFG_SPAMSP		0x01

#घोषणा CH7322_CTL3		0x7b
#घोषणा CH7322_CTL3_SWENA		0x80
#घोषणा CH7322_CTL3_FC_INIT		0x40
#घोषणा CH7322_CTL3_SML_FL		0x20
#घोषणा CH7322_CTL3_SM_RDST		0x10
#घोषणा CH7322_CTL3_SPP_CIAH		0x08
#घोषणा CH7322_CTL3_SPP_CIAL		0x04
#घोषणा CH7322_CTL3_SPP_ACTH		0x02
#घोषणा CH7322_CTL3_SPP_ACTL		0x01

/* BOK status means NACK */
#घोषणा CH7322_TX_FLAG_NACK	BIT(0)
/* Device will retry स्वतःmatically */
#घोषणा CH7322_TX_FLAG_RETRY	BIT(1)

काष्ठा ch7322 अणु
	काष्ठा i2c_client *i2c;
	काष्ठा regmap *regmap;
	काष्ठा cec_adapter *cec;
	काष्ठा mutex mutex;	/* device access mutex */
	u8 tx_flags;
पूर्ण;

अटल स्थिर काष्ठा regmap_config ch7322_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 0x7f,
	.disable_locking = true,
पूर्ण;

अटल पूर्णांक ch7322_send_message(काष्ठा ch7322 *ch7322, स्थिर काष्ठा cec_msg *msg)
अणु
	अचिन्हित पूर्णांक val;
	अचिन्हित पूर्णांक len = msg->len;
	पूर्णांक ret;
	पूर्णांक i;

	WARN_ON(!mutex_is_locked(&ch7322->mutex));

	अगर (len > CH7322_WRBUF_LEN || len < 1)
		वापस -EINVAL;

	ret = regmap_पढ़ो(ch7322->regmap, CH7322_WRITE, &val);
	अगर (ret)
		वापस ret;

	/* Buffer not पढ़ोy */
	अगर (!(val & CH7322_WRITE_MSENT))
		वापस -EBUSY;

	अगर (cec_msg_opcode(msg) == -1 &&
	    cec_msg_initiator(msg) == cec_msg_destination(msg)) अणु
		ch7322->tx_flags = CH7322_TX_FLAG_NACK | CH7322_TX_FLAG_RETRY;
	पूर्ण अन्यथा अगर (cec_msg_is_broadcast(msg)) अणु
		ch7322->tx_flags = CH7322_TX_FLAG_NACK;
	पूर्ण अन्यथा अणु
		ch7322->tx_flags = CH7322_TX_FLAG_RETRY;
	पूर्ण

	ret = regmap_ग_लिखो(ch7322->regmap, CH7322_WRITE, len - 1);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < len; i++) अणु
		ret = regmap_ग_लिखो(ch7322->regmap,
				   CH7322_WRBUF + i, msg->msg[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ch7322_receive_message(काष्ठा ch7322 *ch7322, काष्ठा cec_msg *msg)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret = 0;
	पूर्णांक i;

	WARN_ON(!mutex_is_locked(&ch7322->mutex));

	ret = regmap_पढ़ो(ch7322->regmap, CH7322_READ, &val);
	अगर (ret)
		वापस ret;

	/* Message not पढ़ोy */
	अगर (!(val & CH7322_READ_NRDT))
		वापस -EIO;

	msg->len = (val & CH7322_READ_NMASK) + 1;

	/* Read entire RDBUF to clear state */
	क्रम (i = 0; i < CH7322_RDBUF_LEN; i++) अणु
		ret = regmap_पढ़ो(ch7322->regmap, CH7322_RDBUF + i, &val);
		अगर (ret)
			वापस ret;
		msg->msg[i] = (u8)val;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ch7322_tx_करोne(काष्ठा ch7322 *ch7322)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;
	u8 status, flags;

	mutex_lock(&ch7322->mutex);
	ret = regmap_पढ़ो(ch7322->regmap, CH7322_WRITE, &val);
	flags = ch7322->tx_flags;
	mutex_unlock(&ch7322->mutex);

	/*
	 * The device वापसs a one-bit OK status which usually means ACK but
	 * actually means NACK when sending a logical address query or a
	 * broadcast.
	 */
	अगर (ret)
		status = CEC_TX_STATUS_ERROR;
	अन्यथा अगर ((val & CH7322_WRITE_BOK) && (flags & CH7322_TX_FLAG_NACK))
		status = CEC_TX_STATUS_NACK;
	अन्यथा अगर (val & CH7322_WRITE_BOK)
		status = CEC_TX_STATUS_OK;
	अन्यथा अगर (flags & CH7322_TX_FLAG_NACK)
		status = CEC_TX_STATUS_OK;
	अन्यथा
		status = CEC_TX_STATUS_NACK;

	अगर (status == CEC_TX_STATUS_NACK && (flags & CH7322_TX_FLAG_RETRY))
		status |= CEC_TX_STATUS_MAX_RETRIES;

	cec_transmit_attempt_करोne(ch7322->cec, status);
पूर्ण

अटल व्योम ch7322_rx_करोne(काष्ठा ch7322 *ch7322)
अणु
	काष्ठा cec_msg msg;
	पूर्णांक ret;

	mutex_lock(&ch7322->mutex);
	ret = ch7322_receive_message(ch7322, &msg);
	mutex_unlock(&ch7322->mutex);

	अगर (ret)
		dev_err(&ch7322->i2c->dev, "cec receive error: %d\n", ret);
	अन्यथा
		cec_received_msg(ch7322->cec, &msg);
पूर्ण

/*
 * This device can either monitor the DDC lines to obtain the physical address
 * or it can allow the host to program it. This driver lets the device obtain
 * it.
 */
अटल व्योम ch7322_phys_addr(काष्ठा ch7322 *ch7322)
अणु
	अचिन्हित पूर्णांक pah, pal;
	पूर्णांक ret = 0;

	mutex_lock(&ch7322->mutex);
	ret |= regmap_पढ़ो(ch7322->regmap, CH7322_PARH, &pah);
	ret |= regmap_पढ़ो(ch7322->regmap, CH7322_PARL, &pal);
	mutex_unlock(&ch7322->mutex);

	अगर (ret)
		dev_err(&ch7322->i2c->dev, "phys addr error\n");
	अन्यथा
		cec_s_phys_addr(ch7322->cec, pal | (pah << 8), false);
पूर्ण

अटल irqवापस_t ch7322_irq(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा ch7322 *ch7322 = dev;
	अचिन्हित पूर्णांक data = 0;

	mutex_lock(&ch7322->mutex);
	regmap_पढ़ो(ch7322->regmap, CH7322_INTDATA, &data);
	regmap_ग_लिखो(ch7322->regmap, CH7322_INTDATA, data);
	mutex_unlock(&ch7322->mutex);

	अगर (data & CH7322_INTDATA_HPDFALL)
		cec_phys_addr_invalidate(ch7322->cec);

	अगर (data & CH7322_INTDATA_TXMSG)
		ch7322_tx_करोne(ch7322);

	अगर (data & CH7322_INTDATA_RXMSG)
		ch7322_rx_करोne(ch7322);

	अगर (data & CH7322_INTDATA_NEWPHA)
		ch7322_phys_addr(ch7322);

	अगर (data & CH7322_INTDATA_ERROR)
		dev_dbg(&ch7322->i2c->dev, "unknown error\n");

	वापस IRQ_HANDLED;
पूर्ण

/* This device is always enabled */
अटल पूर्णांक ch7322_cec_adap_enable(काष्ठा cec_adapter *adap, bool enable)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक ch7322_cec_adap_log_addr(काष्ठा cec_adapter *adap, u8 log_addr)
अणु
	काष्ठा ch7322 *ch7322 = cec_get_drvdata(adap);
	पूर्णांक ret;

	mutex_lock(&ch7322->mutex);
	ret = regmap_update_bits(ch7322->regmap, CH7322_ADDLW,
				 CH7322_ADDLW_MASK, log_addr << 4);
	mutex_unlock(&ch7322->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक ch7322_cec_adap_transmit(काष्ठा cec_adapter *adap, u8 attempts,
				    u32 संकेत_मुक्त_समय, काष्ठा cec_msg *msg)
अणु
	काष्ठा ch7322 *ch7322 = cec_get_drvdata(adap);
	पूर्णांक ret;

	mutex_lock(&ch7322->mutex);
	ret = ch7322_send_message(ch7322, msg);
	mutex_unlock(&ch7322->mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा cec_adap_ops ch7322_cec_adap_ops = अणु
	.adap_enable = ch7322_cec_adap_enable,
	.adap_log_addr = ch7322_cec_adap_log_addr,
	.adap_transmit = ch7322_cec_adap_transmit,
पूर्ण;

#अगर IS_ENABLED(CONFIG_PCI) && IS_ENABLED(CONFIG_DMI)

काष्ठा ch7322_conn_match अणु
	स्थिर अक्षर *dev_name;
	स्थिर अक्षर *pci_name;
	स्थिर अक्षर *port_name;
पूर्ण;

अटल काष्ठा ch7322_conn_match google_endeavour[] = अणु
	अणु "i2c-PRP0001:00", "0000:00:02.0", "Port B" पूर्ण,
	अणु "i2c-PRP0001:01", "0000:00:02.0", "Port C" पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dmi_प्रणाली_id ch7322_dmi_table[] = अणु
	अणु
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Google"),
			DMI_MATCH(DMI_BOARD_NAME, "Endeavour"),
		पूर्ण,
		.driver_data = google_endeavour,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

/* Make a best-efक्रमt attempt to locate a matching HDMI port */
अटल पूर्णांक ch7322_get_port(काष्ठा i2c_client *client,
			   काष्ठा device **dev,
			   स्थिर अक्षर **port)
अणु
	स्थिर काष्ठा dmi_प्रणाली_id *प्रणाली;
	स्थिर काष्ठा ch7322_conn_match *conn;

	*dev = शून्य;
	*port = शून्य;

	प्रणाली = dmi_first_match(ch7322_dmi_table);
	अगर (!प्रणाली)
		वापस 0;

	क्रम (conn = प्रणाली->driver_data; conn->dev_name; conn++) अणु
		अगर (!म_भेद(dev_name(&client->dev), conn->dev_name)) अणु
			काष्ठा device *d;

			d = bus_find_device_by_name(&pci_bus_type, शून्य,
						    conn->pci_name);
			अगर (!d)
				वापस -EPROBE_DEFER;

			put_device(d);

			*dev = d;
			*port = conn->port_name;

			वापस 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#अन्यथा

अटल पूर्णांक ch7322_get_port(काष्ठा i2c_client *client,
			   काष्ठा device **dev,
			   स्थिर अक्षर **port)
अणु
	*dev = शून्य;
	*port = शून्य;

	वापस 0;
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक ch7322_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *hdmi_dev;
	स्थिर अक्षर *port_name;
	काष्ठा ch7322 *ch7322;
	काष्ठा cec_notअगरier *notअगरier = शून्य;
	u32 caps = CEC_CAP_DEFAULTS;
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	ret = ch7322_get_port(client, &hdmi_dev, &port_name);
	अगर (ret)
		वापस ret;

	अगर (hdmi_dev)
		caps |= CEC_CAP_CONNECTOR_INFO;

	ch7322 = devm_kzalloc(&client->dev, माप(*ch7322), GFP_KERNEL);
	अगर (!ch7322)
		वापस -ENOMEM;

	ch7322->regmap = devm_regmap_init_i2c(client, &ch7322_regmap);
	अगर (IS_ERR(ch7322->regmap))
		वापस PTR_ERR(ch7322->regmap);

	ret = regmap_पढ़ो(ch7322->regmap, CH7322_DID, &val);
	अगर (ret)
		वापस ret;

	अगर (val != CH7322_DID_CH7322)
		वापस -EOPNOTSUPP;

	mutex_init(&ch7322->mutex);
	ch7322->i2c = client;
	ch7322->tx_flags = 0;

	i2c_set_clientdata(client, ch7322);

	/* Disable स्वतः mode */
	ret = regmap_ग_लिखो(ch7322->regmap, CH7322_MODE, CH7322_MODE_SW);
	अगर (ret)
		जाओ err_mutex;

	/* Enable logical address रेजिस्टर */
	ret = regmap_update_bits(ch7322->regmap, CH7322_CTL,
				 CH7322_CTL_SPADL, CH7322_CTL_SPADL);
	अगर (ret)
		जाओ err_mutex;

	ch7322->cec = cec_allocate_adapter(&ch7322_cec_adap_ops, ch7322,
					   dev_name(&client->dev),
					   caps, 1);

	अगर (IS_ERR(ch7322->cec)) अणु
		ret = PTR_ERR(ch7322->cec);
		जाओ err_mutex;
	पूर्ण

	ch7322->cec->adap_controls_phys_addr = true;

	अगर (hdmi_dev) अणु
		notअगरier = cec_notअगरier_cec_adap_रेजिस्टर(hdmi_dev,
							  port_name,
							  ch7322->cec);
		अगर (!notअगरier) अणु
			ret = -ENOMEM;
			जाओ err_cec;
		पूर्ण
	पूर्ण

	/* Configure, mask, and clear पूर्णांकerrupt */
	ret = regmap_ग_लिखो(ch7322->regmap, CH7322_CFG1, 0);
	अगर (ret)
		जाओ err_notअगरier;
	ret = regmap_ग_लिखो(ch7322->regmap, CH7322_INTCTL, CH7322_INTCTL_INTPB);
	अगर (ret)
		जाओ err_notअगरier;
	ret = regmap_ग_लिखो(ch7322->regmap, CH7322_INTDATA, 0xff);
	अगर (ret)
		जाओ err_notअगरier;

	/* If HPD is up पढ़ो physical address */
	ret = regmap_पढ़ो(ch7322->regmap, CH7322_ADDLR, &val);
	अगर (ret)
		जाओ err_notअगरier;
	अगर (val & CH7322_ADDLR_HPD)
		ch7322_phys_addr(ch7322);

	ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq, शून्य,
					ch7322_irq,
					IRQF_ONESHOT | IRQF_TRIGGER_RISING,
					client->name, ch7322);
	अगर (ret)
		जाओ err_notअगरier;

	/* Unmask पूर्णांकerrupt */
	mutex_lock(&ch7322->mutex);
	ret = regmap_ग_लिखो(ch7322->regmap, CH7322_INTCTL, 0xff);
	mutex_unlock(&ch7322->mutex);

	अगर (ret)
		जाओ err_notअगरier;

	ret = cec_रेजिस्टर_adapter(ch7322->cec, &client->dev);
	अगर (ret)
		जाओ err_notअगरier;

	dev_info(&client->dev, "device registered\n");

	वापस 0;

err_notअगरier:
	अगर (notअगरier)
		cec_notअगरier_cec_adap_unरेजिस्टर(notअगरier, ch7322->cec);
err_cec:
	cec_delete_adapter(ch7322->cec);
err_mutex:
	mutex_destroy(&ch7322->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक ch7322_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा ch7322 *ch7322 = i2c_get_clientdata(client);

	/* Mask पूर्णांकerrupt */
	mutex_lock(&ch7322->mutex);
	regmap_ग_लिखो(ch7322->regmap, CH7322_INTCTL, CH7322_INTCTL_INTPB);
	mutex_unlock(&ch7322->mutex);

	cec_unरेजिस्टर_adapter(ch7322->cec);
	mutex_destroy(&ch7322->mutex);

	dev_info(&client->dev, "device unregistered\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ch7322_of_match[] = अणु
	अणु .compatible = "chrontel,ch7322", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ch7322_of_match);

अटल काष्ठा i2c_driver ch7322_i2c_driver = अणु
	.driver = अणु
		.name = "ch7322",
		.of_match_table = of_match_ptr(ch7322_of_match),
	पूर्ण,
	.probe_new	= ch7322_probe,
	.हटाओ		= ch7322_हटाओ,
पूर्ण;

module_i2c_driver(ch7322_i2c_driver);

MODULE_DESCRIPTION("Chrontel CH7322 CEC Controller Driver");
MODULE_AUTHOR("Jeff Chase <jnchase@google.com>");
MODULE_LICENSE("GPL");
