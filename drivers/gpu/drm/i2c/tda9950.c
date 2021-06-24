<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  TDA9950 Consumer Electronics Control driver
 *
 * The NXP TDA9950 implements the HDMI Consumer Electronics Control
 * पूर्णांकerface.  The host पूर्णांकerface is similar to a mailbox: the data
 * रेजिस्टरs starting at REG_CDR0 are written to send a command to the
 * पूर्णांकernal CPU, and replies are पढ़ो from these रेजिस्टरs.
 *
 * As the data रेजिस्टरs represent a mailbox, they must be accessed
 * as a single I2C transaction.  See the TDA9950 data sheet क्रम details.
 */
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/tda9950.h>
#समावेश <linux/slab.h>
#समावेश <drm/drm_edid.h>
#समावेश <media/cec.h>
#समावेश <media/cec-notअगरier.h>

क्रमागत अणु
	REG_CSR = 0x00,
	CSR_BUSY = BIT(7),
	CSR_INT  = BIT(6),
	CSR_ERR  = BIT(5),

	REG_CER = 0x01,

	REG_CVR = 0x02,

	REG_CCR = 0x03,
	CCR_RESET = BIT(7),
	CCR_ON    = BIT(6),

	REG_ACKH = 0x04,
	REG_ACKL = 0x05,

	REG_CCONR = 0x06,
	CCONR_ENABLE_ERROR = BIT(4),
	CCONR_RETRY_MASK = 7,

	REG_CDR0 = 0x07,

	CDR1_REQ = 0x00,
	CDR1_CNF = 0x01,
	CDR1_IND = 0x81,
	CDR1_ERR = 0x82,
	CDR1_IER = 0x83,

	CDR2_CNF_SUCCESS    = 0x00,
	CDR2_CNF_OFF_STATE  = 0x80,
	CDR2_CNF_BAD_REQ    = 0x81,
	CDR2_CNF_CEC_ACCESS = 0x82,
	CDR2_CNF_ARB_ERROR  = 0x83,
	CDR2_CNF_BAD_TIMING = 0x84,
	CDR2_CNF_NACK_ADDR  = 0x85,
	CDR2_CNF_NACK_DATA  = 0x86,
पूर्ण;

काष्ठा tda9950_priv अणु
	काष्ठा i2c_client *client;
	काष्ठा device *hdmi;
	काष्ठा cec_adapter *adap;
	काष्ठा tda9950_glue *glue;
	u16 addresses;
	काष्ठा cec_msg rx_msg;
	काष्ठा cec_notअगरier *notअगरy;
	bool खोलो;
पूर्ण;

अटल पूर्णांक tda9950_ग_लिखो_range(काष्ठा i2c_client *client, u8 addr, u8 *p, पूर्णांक cnt)
अणु
	काष्ठा i2c_msg msg;
	u8 buf[CEC_MAX_MSG_SIZE + 3];
	पूर्णांक ret;

	अगर (WARN_ON(cnt > माप(buf) - 1))
		वापस -EINVAL;

	buf[0] = addr;
	स_नकल(buf + 1, p, cnt);

	msg.addr = client->addr;
	msg.flags = 0;
	msg.len = cnt + 1;
	msg.buf = buf;

	dev_dbg(&client->dev, "wr 0x%02x: %*ph\n", addr, cnt, p);

	ret = i2c_transfer(client->adapter, &msg, 1);
	अगर (ret < 0)
		dev_err(&client->dev, "Error %d writing to cec:0x%x\n", ret, addr);
	वापस ret < 0 ? ret : 0;
पूर्ण

अटल व्योम tda9950_ग_लिखो(काष्ठा i2c_client *client, u8 addr, u8 val)
अणु
	tda9950_ग_लिखो_range(client, addr, &val, 1);
पूर्ण

अटल पूर्णांक tda9950_पढ़ो_range(काष्ठा i2c_client *client, u8 addr, u8 *p, पूर्णांक cnt)
अणु
	काष्ठा i2c_msg msg[2];
	पूर्णांक ret;

	msg[0].addr = client->addr;
	msg[0].flags = 0;
	msg[0].len = 1;
	msg[0].buf = &addr;
	msg[1].addr = client->addr;
	msg[1].flags = I2C_M_RD;
	msg[1].len = cnt;
	msg[1].buf = p;

	ret = i2c_transfer(client->adapter, msg, 2);
	अगर (ret < 0)
		dev_err(&client->dev, "Error %d reading from cec:0x%x\n", ret, addr);

	dev_dbg(&client->dev, "rd 0x%02x: %*ph\n", addr, cnt, p);

	वापस ret;
पूर्ण

अटल u8 tda9950_पढ़ो(काष्ठा i2c_client *client, u8 addr)
अणु
	पूर्णांक ret;
	u8 val;

	ret = tda9950_पढ़ो_range(client, addr, &val, 1);
	अगर (ret < 0)
		val = 0;

	वापस val;
पूर्ण

अटल irqवापस_t tda9950_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा tda9950_priv *priv = data;
	अचिन्हित पूर्णांक tx_status;
	u8 csr, cconr, buf[19];
	u8 arb_lost_cnt, nack_cnt, err_cnt;

	अगर (!priv->खोलो)
		वापस IRQ_NONE;

	csr = tda9950_पढ़ो(priv->client, REG_CSR);
	अगर (!(csr & CSR_INT))
		वापस IRQ_NONE;

	cconr = tda9950_पढ़ो(priv->client, REG_CCONR) & CCONR_RETRY_MASK;

	tda9950_पढ़ो_range(priv->client, REG_CDR0, buf, माप(buf));

	/*
	 * This should never happen: the data sheet says that there will
	 * always be a valid message अगर the पूर्णांकerrupt line is निश्चितed.
	 */
	अगर (buf[0] == 0) अणु
		dev_warn(&priv->client->dev, "interrupt pending, but no message?\n");
		वापस IRQ_NONE;
	पूर्ण

	चयन (buf[1]) अणु
	हाल CDR1_CNF: /* transmit result */
		arb_lost_cnt = nack_cnt = err_cnt = 0;
		चयन (buf[2]) अणु
		हाल CDR2_CNF_SUCCESS:
			tx_status = CEC_TX_STATUS_OK;
			अवरोध;

		हाल CDR2_CNF_ARB_ERROR:
			tx_status = CEC_TX_STATUS_ARB_LOST;
			arb_lost_cnt = cconr;
			अवरोध;

		हाल CDR2_CNF_NACK_ADDR:
			tx_status = CEC_TX_STATUS_NACK;
			nack_cnt = cconr;
			अवरोध;

		शेष: /* some other error, refer to TDA9950 करोcs */
			dev_err(&priv->client->dev, "CNF reply error 0x%02x\n",
				buf[2]);
			tx_status = CEC_TX_STATUS_ERROR;
			err_cnt = cconr;
			अवरोध;
		पूर्ण
		/* TDA9950 executes all retries क्रम us */
		अगर (tx_status != CEC_TX_STATUS_OK)
			tx_status |= CEC_TX_STATUS_MAX_RETRIES;
		cec_transmit_करोne(priv->adap, tx_status, arb_lost_cnt,
				  nack_cnt, 0, err_cnt);
		अवरोध;

	हाल CDR1_IND:
		priv->rx_msg.len = buf[0] - 2;
		अगर (priv->rx_msg.len > CEC_MAX_MSG_SIZE)
			priv->rx_msg.len = CEC_MAX_MSG_SIZE;

		स_नकल(priv->rx_msg.msg, buf + 2, priv->rx_msg.len);
		cec_received_msg(priv->adap, &priv->rx_msg);
		अवरोध;

	शेष: /* unknown */
		dev_err(&priv->client->dev, "unknown service id 0x%02x\n",
			buf[1]);
		अवरोध;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक tda9950_cec_transmit(काष्ठा cec_adapter *adap, u8 attempts,
				u32 संकेत_मुक्त_समय, काष्ठा cec_msg *msg)
अणु
	काष्ठा tda9950_priv *priv = adap->priv;
	u8 buf[CEC_MAX_MSG_SIZE + 2];

	buf[0] = 2 + msg->len;
	buf[1] = CDR1_REQ;
	स_नकल(buf + 2, msg->msg, msg->len);

	अगर (attempts > 5)
		attempts = 5;

	tda9950_ग_लिखो(priv->client, REG_CCONR, attempts);

	वापस tda9950_ग_लिखो_range(priv->client, REG_CDR0, buf, 2 + msg->len);
पूर्ण

अटल पूर्णांक tda9950_cec_adap_log_addr(काष्ठा cec_adapter *adap, u8 addr)
अणु
	काष्ठा tda9950_priv *priv = adap->priv;
	u16 addresses;
	u8 buf[2];

	अगर (addr == CEC_LOG_ADDR_INVALID)
		addresses = priv->addresses = 0;
	अन्यथा
		addresses = priv->addresses |= BIT(addr);

	/* TDA9950 करोesn't want address 15 set */
	addresses &= 0x7fff;
	buf[0] = addresses >> 8;
	buf[1] = addresses;

	वापस tda9950_ग_लिखो_range(priv->client, REG_ACKH, buf, 2);
पूर्ण

/*
 * When operating as part of the TDA998x, we need additional handling
 * to initialise and shut करोwn the TDA9950 part of the device.  These
 * two hooks are provided to allow the TDA998x code to perक्रमm those
 * activities.
 */
अटल पूर्णांक tda9950_glue_खोलो(काष्ठा tda9950_priv *priv)
अणु
	पूर्णांक ret = 0;

	अगर (priv->glue && priv->glue->खोलो)
		ret = priv->glue->खोलो(priv->glue->data);

	priv->खोलो = true;

	वापस ret;
पूर्ण

अटल व्योम tda9950_glue_release(काष्ठा tda9950_priv *priv)
अणु
	priv->खोलो = false;

	अगर (priv->glue && priv->glue->release)
		priv->glue->release(priv->glue->data);
पूर्ण

अटल पूर्णांक tda9950_खोलो(काष्ठा tda9950_priv *priv)
अणु
	काष्ठा i2c_client *client = priv->client;
	पूर्णांक ret;

	ret = tda9950_glue_खोलो(priv);
	अगर (ret)
		वापस ret;

	/* Reset the TDA9950, and रुको 250ms क्रम it to recover */
	tda9950_ग_लिखो(client, REG_CCR, CCR_RESET);
	msleep(250);

	tda9950_cec_adap_log_addr(priv->adap, CEC_LOG_ADDR_INVALID);

	/* Start the command processor */
	tda9950_ग_लिखो(client, REG_CCR, CCR_ON);

	वापस 0;
पूर्ण

अटल व्योम tda9950_release(काष्ठा tda9950_priv *priv)
अणु
	काष्ठा i2c_client *client = priv->client;
	पूर्णांक समयout = 50;
	u8 csr;

	/* Stop the command processor */
	tda9950_ग_लिखो(client, REG_CCR, 0);

	/* Wait up to .5s क्रम it to संकेत non-busy */
	करो अणु
		csr = tda9950_पढ़ो(client, REG_CSR);
		अगर (!(csr & CSR_BUSY) || !--समयout)
			अवरोध;
		msleep(10);
	पूर्ण जबतक (1);

	/* Warn the user that their IRQ may die अगर it's shared. */
	अगर (csr & CSR_BUSY)
		dev_warn(&client->dev, "command processor failed to stop, irq%d may die (csr=0x%02x)\n",
			 client->irq, csr);

	tda9950_glue_release(priv);
पूर्ण

अटल पूर्णांक tda9950_cec_adap_enable(काष्ठा cec_adapter *adap, bool enable)
अणु
	काष्ठा tda9950_priv *priv = adap->priv;

	अगर (!enable) अणु
		tda9950_release(priv);
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस tda9950_खोलो(priv);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा cec_adap_ops tda9950_cec_ops = अणु
	.adap_enable = tda9950_cec_adap_enable,
	.adap_log_addr = tda9950_cec_adap_log_addr,
	.adap_transmit = tda9950_cec_transmit,
पूर्ण;

/*
 * When operating as part of the TDA998x, we need to claim additional
 * resources.  These two hooks permit the management of those resources.
 */
अटल व्योम tda9950_devm_glue_निकास(व्योम *data)
अणु
	काष्ठा tda9950_glue *glue = data;

	अगर (glue && glue->निकास)
		glue->निकास(glue->data);
पूर्ण

अटल पूर्णांक tda9950_devm_glue_init(काष्ठा device *dev, काष्ठा tda9950_glue *glue)
अणु
	पूर्णांक ret;

	अगर (glue && glue->init) अणु
		ret = glue->init(glue->data);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = devm_add_action(dev, tda9950_devm_glue_निकास, glue);
	अगर (ret)
		tda9950_devm_glue_निकास(glue);

	वापस ret;
पूर्ण

अटल व्योम tda9950_cec_del(व्योम *data)
अणु
	काष्ठा tda9950_priv *priv = data;

	cec_delete_adapter(priv->adap);
पूर्ण

अटल पूर्णांक tda9950_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tda9950_glue *glue = client->dev.platक्रमm_data;
	काष्ठा device *dev = &client->dev;
	काष्ठा tda9950_priv *priv;
	अचिन्हित दीर्घ irqflags;
	पूर्णांक ret;
	u8 cvr;

	/*
	 * We must have I2C functionality: our multi-byte accesses
	 * must be perक्रमmed as a single contiguous transaction.
	 */
	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		dev_err(&client->dev,
			"adapter does not support I2C functionality\n");
		वापस -ENXIO;
	पूर्ण

	/* We must have an पूर्णांकerrupt to be functional. */
	अगर (client->irq <= 0) अणु
		dev_err(&client->dev, "driver requires an interrupt\n");
		वापस -ENXIO;
	पूर्ण

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->client = client;
	priv->glue = glue;

	i2c_set_clientdata(client, priv);

	/*
	 * If we're part of a TDA998x, we want the class devices to be
	 * associated with the HDMI Tx so we have a tight relationship
	 * between the HDMI पूर्णांकerface and the CEC पूर्णांकerface.
	 */
	priv->hdmi = dev;
	अगर (glue && glue->parent)
		priv->hdmi = glue->parent;

	priv->adap = cec_allocate_adapter(&tda9950_cec_ops, priv, "tda9950",
					  CEC_CAP_DEFAULTS |
					  CEC_CAP_CONNECTOR_INFO,
					  CEC_MAX_LOG_ADDRS);
	अगर (IS_ERR(priv->adap))
		वापस PTR_ERR(priv->adap);

	ret = devm_add_action(dev, tda9950_cec_del, priv);
	अगर (ret) अणु
		cec_delete_adapter(priv->adap);
		वापस ret;
	पूर्ण

	ret = tda9950_devm_glue_init(dev, glue);
	अगर (ret)
		वापस ret;

	ret = tda9950_glue_खोलो(priv);
	अगर (ret)
		वापस ret;

	cvr = tda9950_पढ़ो(client, REG_CVR);

	dev_info(&client->dev,
		 "TDA9950 CEC interface, hardware version %u.%u\n",
		 cvr >> 4, cvr & 15);

	tda9950_glue_release(priv);

	irqflags = IRQF_TRIGGER_FALLING;
	अगर (glue)
		irqflags = glue->irq_flags;

	ret = devm_request_thपढ़ोed_irq(dev, client->irq, शून्य, tda9950_irq,
					irqflags | IRQF_SHARED | IRQF_ONESHOT,
					dev_name(&client->dev), priv);
	अगर (ret < 0)
		वापस ret;

	priv->notअगरy = cec_notअगरier_cec_adap_रेजिस्टर(priv->hdmi, शून्य,
						      priv->adap);
	अगर (!priv->notअगरy)
		वापस -ENOMEM;

	ret = cec_रेजिस्टर_adapter(priv->adap, priv->hdmi);
	अगर (ret < 0) अणु
		cec_notअगरier_cec_adap_unरेजिस्टर(priv->notअगरy, priv->adap);
		वापस ret;
	पूर्ण

	/*
	 * CEC करोcumentation says we must not call cec_delete_adapter
	 * after a successful call to cec_रेजिस्टर_adapter().
	 */
	devm_हटाओ_action(dev, tda9950_cec_del, priv);

	वापस 0;
पूर्ण

अटल पूर्णांक tda9950_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा tda9950_priv *priv = i2c_get_clientdata(client);

	cec_notअगरier_cec_adap_unरेजिस्टर(priv->notअगरy, priv->adap);
	cec_unरेजिस्टर_adapter(priv->adap);

	वापस 0;
पूर्ण

अटल काष्ठा i2c_device_id tda9950_ids[] = अणु
	अणु "tda9950", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tda9950_ids);

अटल काष्ठा i2c_driver tda9950_driver = अणु
	.probe = tda9950_probe,
	.हटाओ = tda9950_हटाओ,
	.driver = अणु
		.name = "tda9950",
	पूर्ण,
	.id_table = tda9950_ids,
पूर्ण;

module_i2c_driver(tda9950_driver);

MODULE_AUTHOR("Russell King <rmk+kernel@armlinux.org.uk>");
MODULE_DESCRIPTION("TDA9950/TDA998x Consumer Electronics Control Driver");
MODULE_LICENSE("GPL v2");
