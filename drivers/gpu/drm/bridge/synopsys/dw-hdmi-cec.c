<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Designware HDMI CEC driver
 *
 * Copyright (C) 2015-2017 Russell King.
 */
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>

#समावेश <drm/drm_edid.h>

#समावेश <media/cec.h>
#समावेश <media/cec-notअगरier.h>

#समावेश "dw-hdmi-cec.h"

क्रमागत अणु
	HDMI_IH_CEC_STAT0	= 0x0106,
	HDMI_IH_MUTE_CEC_STAT0	= 0x0186,

	HDMI_CEC_CTRL		= 0x7d00,
	CEC_CTRL_START		= BIT(0),
	CEC_CTRL_FRAME_TYP	= 3 << 1,
	CEC_CTRL_RETRY		= 0 << 1,
	CEC_CTRL_NORMAL		= 1 << 1,
	CEC_CTRL_IMMED		= 2 << 1,

	HDMI_CEC_STAT		= 0x7d01,
	CEC_STAT_DONE		= BIT(0),
	CEC_STAT_EOM		= BIT(1),
	CEC_STAT_NACK		= BIT(2),
	CEC_STAT_ARBLOST	= BIT(3),
	CEC_STAT_ERROR_INIT	= BIT(4),
	CEC_STAT_ERROR_FOLL	= BIT(5),
	CEC_STAT_WAKEUP		= BIT(6),

	HDMI_CEC_MASK		= 0x7d02,
	HDMI_CEC_POLARITY	= 0x7d03,
	HDMI_CEC_INT		= 0x7d04,
	HDMI_CEC_ADDR_L		= 0x7d05,
	HDMI_CEC_ADDR_H		= 0x7d06,
	HDMI_CEC_TX_CNT		= 0x7d07,
	HDMI_CEC_RX_CNT		= 0x7d08,
	HDMI_CEC_TX_DATA0	= 0x7d10,
	HDMI_CEC_RX_DATA0	= 0x7d20,
	HDMI_CEC_LOCK		= 0x7d30,
	HDMI_CEC_WKUPCTRL	= 0x7d31,
पूर्ण;

काष्ठा dw_hdmi_cec अणु
	काष्ठा dw_hdmi *hdmi;
	स्थिर काष्ठा dw_hdmi_cec_ops *ops;
	u32 addresses;
	काष्ठा cec_adapter *adap;
	काष्ठा cec_msg rx_msg;
	अचिन्हित पूर्णांक tx_status;
	bool tx_करोne;
	bool rx_करोne;
	काष्ठा cec_notअगरier *notअगरy;
	पूर्णांक irq;
पूर्ण;

अटल व्योम dw_hdmi_ग_लिखो(काष्ठा dw_hdmi_cec *cec, u8 val, पूर्णांक offset)
अणु
	cec->ops->ग_लिखो(cec->hdmi, val, offset);
पूर्ण

अटल u8 dw_hdmi_पढ़ो(काष्ठा dw_hdmi_cec *cec, पूर्णांक offset)
अणु
	वापस cec->ops->पढ़ो(cec->hdmi, offset);
पूर्ण

अटल पूर्णांक dw_hdmi_cec_log_addr(काष्ठा cec_adapter *adap, u8 logical_addr)
अणु
	काष्ठा dw_hdmi_cec *cec = cec_get_drvdata(adap);

	अगर (logical_addr == CEC_LOG_ADDR_INVALID)
		cec->addresses = 0;
	अन्यथा
		cec->addresses |= BIT(logical_addr) | BIT(15);

	dw_hdmi_ग_लिखो(cec, cec->addresses & 255, HDMI_CEC_ADDR_L);
	dw_hdmi_ग_लिखो(cec, cec->addresses >> 8, HDMI_CEC_ADDR_H);

	वापस 0;
पूर्ण

अटल पूर्णांक dw_hdmi_cec_transmit(काष्ठा cec_adapter *adap, u8 attempts,
				u32 संकेत_मुक्त_समय, काष्ठा cec_msg *msg)
अणु
	काष्ठा dw_hdmi_cec *cec = cec_get_drvdata(adap);
	अचिन्हित पूर्णांक i, ctrl;

	चयन (संकेत_मुक्त_समय) अणु
	हाल CEC_SIGNAL_FREE_TIME_RETRY:
		ctrl = CEC_CTRL_RETRY;
		अवरोध;
	हाल CEC_SIGNAL_FREE_TIME_NEW_INITIATOR:
	शेष:
		ctrl = CEC_CTRL_NORMAL;
		अवरोध;
	हाल CEC_SIGNAL_FREE_TIME_NEXT_XFER:
		ctrl = CEC_CTRL_IMMED;
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < msg->len; i++)
		dw_hdmi_ग_लिखो(cec, msg->msg[i], HDMI_CEC_TX_DATA0 + i);

	dw_hdmi_ग_लिखो(cec, msg->len, HDMI_CEC_TX_CNT);
	dw_hdmi_ग_लिखो(cec, ctrl | CEC_CTRL_START, HDMI_CEC_CTRL);

	वापस 0;
पूर्ण

अटल irqवापस_t dw_hdmi_cec_hardirq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cec_adapter *adap = data;
	काष्ठा dw_hdmi_cec *cec = cec_get_drvdata(adap);
	अचिन्हित पूर्णांक stat = dw_hdmi_पढ़ो(cec, HDMI_IH_CEC_STAT0);
	irqवापस_t ret = IRQ_HANDLED;

	अगर (stat == 0)
		वापस IRQ_NONE;

	dw_hdmi_ग_लिखो(cec, stat, HDMI_IH_CEC_STAT0);

	अगर (stat & CEC_STAT_ERROR_INIT) अणु
		cec->tx_status = CEC_TX_STATUS_ERROR;
		cec->tx_करोne = true;
		ret = IRQ_WAKE_THREAD;
	पूर्ण अन्यथा अगर (stat & CEC_STAT_DONE) अणु
		cec->tx_status = CEC_TX_STATUS_OK;
		cec->tx_करोne = true;
		ret = IRQ_WAKE_THREAD;
	पूर्ण अन्यथा अगर (stat & CEC_STAT_NACK) अणु
		cec->tx_status = CEC_TX_STATUS_NACK;
		cec->tx_करोne = true;
		ret = IRQ_WAKE_THREAD;
	पूर्ण

	अगर (stat & CEC_STAT_EOM) अणु
		अचिन्हित पूर्णांक len, i;

		len = dw_hdmi_पढ़ो(cec, HDMI_CEC_RX_CNT);
		अगर (len > माप(cec->rx_msg.msg))
			len = माप(cec->rx_msg.msg);

		क्रम (i = 0; i < len; i++)
			cec->rx_msg.msg[i] =
				dw_hdmi_पढ़ो(cec, HDMI_CEC_RX_DATA0 + i);

		dw_hdmi_ग_लिखो(cec, 0, HDMI_CEC_LOCK);

		cec->rx_msg.len = len;
		smp_wmb();
		cec->rx_करोne = true;

		ret = IRQ_WAKE_THREAD;
	पूर्ण

	वापस ret;
पूर्ण

अटल irqवापस_t dw_hdmi_cec_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cec_adapter *adap = data;
	काष्ठा dw_hdmi_cec *cec = cec_get_drvdata(adap);

	अगर (cec->tx_करोne) अणु
		cec->tx_करोne = false;
		cec_transmit_attempt_करोne(adap, cec->tx_status);
	पूर्ण
	अगर (cec->rx_करोne) अणु
		cec->rx_करोne = false;
		smp_rmb();
		cec_received_msg(adap, &cec->rx_msg);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक dw_hdmi_cec_enable(काष्ठा cec_adapter *adap, bool enable)
अणु
	काष्ठा dw_hdmi_cec *cec = cec_get_drvdata(adap);

	अगर (!enable) अणु
		dw_hdmi_ग_लिखो(cec, ~0, HDMI_CEC_MASK);
		dw_hdmi_ग_लिखो(cec, ~0, HDMI_IH_MUTE_CEC_STAT0);
		dw_hdmi_ग_लिखो(cec, 0, HDMI_CEC_POLARITY);

		cec->ops->disable(cec->hdmi);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक irqs;

		dw_hdmi_ग_लिखो(cec, 0, HDMI_CEC_CTRL);
		dw_hdmi_ग_लिखो(cec, ~0, HDMI_IH_CEC_STAT0);
		dw_hdmi_ग_लिखो(cec, 0, HDMI_CEC_LOCK);

		dw_hdmi_cec_log_addr(cec->adap, CEC_LOG_ADDR_INVALID);

		cec->ops->enable(cec->hdmi);

		irqs = CEC_STAT_ERROR_INIT | CEC_STAT_NACK | CEC_STAT_EOM |
		       CEC_STAT_DONE;
		dw_hdmi_ग_लिखो(cec, irqs, HDMI_CEC_POLARITY);
		dw_hdmi_ग_लिखो(cec, ~irqs, HDMI_CEC_MASK);
		dw_hdmi_ग_लिखो(cec, ~irqs, HDMI_IH_MUTE_CEC_STAT0);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cec_adap_ops dw_hdmi_cec_ops = अणु
	.adap_enable = dw_hdmi_cec_enable,
	.adap_log_addr = dw_hdmi_cec_log_addr,
	.adap_transmit = dw_hdmi_cec_transmit,
पूर्ण;

अटल व्योम dw_hdmi_cec_del(व्योम *data)
अणु
	काष्ठा dw_hdmi_cec *cec = data;

	cec_delete_adapter(cec->adap);
पूर्ण

अटल पूर्णांक dw_hdmi_cec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dw_hdmi_cec_data *data = dev_get_platdata(&pdev->dev);
	काष्ठा dw_hdmi_cec *cec;
	पूर्णांक ret;

	अगर (!data)
		वापस -ENXIO;

	/*
	 * Our device is just a convenience - we want to link to the real
	 * hardware device here, so that userspace can see the association
	 * between the HDMI hardware and its associated CEC अक्षरdev.
	 */
	cec = devm_kzalloc(&pdev->dev, माप(*cec), GFP_KERNEL);
	अगर (!cec)
		वापस -ENOMEM;

	cec->irq = data->irq;
	cec->ops = data->ops;
	cec->hdmi = data->hdmi;

	platक्रमm_set_drvdata(pdev, cec);

	dw_hdmi_ग_लिखो(cec, 0, HDMI_CEC_TX_CNT);
	dw_hdmi_ग_लिखो(cec, ~0, HDMI_CEC_MASK);
	dw_hdmi_ग_लिखो(cec, ~0, HDMI_IH_MUTE_CEC_STAT0);
	dw_hdmi_ग_लिखो(cec, 0, HDMI_CEC_POLARITY);

	cec->adap = cec_allocate_adapter(&dw_hdmi_cec_ops, cec, "dw_hdmi",
					 CEC_CAP_DEFAULTS |
					 CEC_CAP_CONNECTOR_INFO,
					 CEC_MAX_LOG_ADDRS);
	अगर (IS_ERR(cec->adap))
		वापस PTR_ERR(cec->adap);

	/* override the module poपूर्णांकer */
	cec->adap->owner = THIS_MODULE;

	ret = devm_add_action(&pdev->dev, dw_hdmi_cec_del, cec);
	अगर (ret) अणु
		cec_delete_adapter(cec->adap);
		वापस ret;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, cec->irq,
					dw_hdmi_cec_hardirq,
					dw_hdmi_cec_thपढ़ो, IRQF_SHARED,
					"dw-hdmi-cec", cec->adap);
	अगर (ret < 0)
		वापस ret;

	cec->notअगरy = cec_notअगरier_cec_adap_रेजिस्टर(pdev->dev.parent,
						     शून्य, cec->adap);
	अगर (!cec->notअगरy)
		वापस -ENOMEM;

	ret = cec_रेजिस्टर_adapter(cec->adap, pdev->dev.parent);
	अगर (ret < 0) अणु
		cec_notअगरier_cec_adap_unरेजिस्टर(cec->notअगरy, cec->adap);
		वापस ret;
	पूर्ण

	/*
	 * CEC करोcumentation says we must not call cec_delete_adapter
	 * after a successful call to cec_रेजिस्टर_adapter().
	 */
	devm_हटाओ_action(&pdev->dev, dw_hdmi_cec_del, cec);

	वापस 0;
पूर्ण

अटल पूर्णांक dw_hdmi_cec_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dw_hdmi_cec *cec = platक्रमm_get_drvdata(pdev);

	cec_notअगरier_cec_adap_unरेजिस्टर(cec->notअगरy, cec->adap);
	cec_unरेजिस्टर_adapter(cec->adap);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver dw_hdmi_cec_driver = अणु
	.probe	= dw_hdmi_cec_probe,
	.हटाओ	= dw_hdmi_cec_हटाओ,
	.driver = अणु
		.name = "dw-hdmi-cec",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(dw_hdmi_cec_driver);

MODULE_AUTHOR("Russell King <rmk+kernel@armlinux.org.uk>");
MODULE_DESCRIPTION("Synopsys Designware HDMI CEC driver for i.MX");
MODULE_LICENSE("GPL");
MODULE_ALIAS(PLATFORM_MODULE_PREFIX "dw-hdmi-cec");
