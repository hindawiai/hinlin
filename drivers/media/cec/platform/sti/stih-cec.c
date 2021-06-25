<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * STIH4xx CEC driver
 * Copyright (C) STMicroelectronics SA 2016
 *
 */
#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <media/cec.h>
#समावेश <media/cec-notअगरier.h>

#घोषणा CEC_NAME	"stih-cec"

/* CEC रेजिस्टरs  */
#घोषणा CEC_CLK_DIV           0x0
#घोषणा CEC_CTRL              0x4
#घोषणा CEC_IRQ_CTRL          0x8
#घोषणा CEC_STATUS            0xC
#घोषणा CEC_EXT_STATUS        0x10
#घोषणा CEC_TX_CTRL           0x14
#घोषणा CEC_FREE_TIME_THRESH  0x18
#घोषणा CEC_BIT_TOUT_THRESH   0x1C
#घोषणा CEC_BIT_PULSE_THRESH  0x20
#घोषणा CEC_DATA              0x24
#घोषणा CEC_TX_ARRAY_CTRL     0x28
#घोषणा CEC_CTRL2             0x2C
#घोषणा CEC_TX_ERROR_STS      0x30
#घोषणा CEC_ADDR_TABLE        0x34
#घोषणा CEC_DATA_ARRAY_CTRL   0x38
#घोषणा CEC_DATA_ARRAY_STATUS 0x3C
#घोषणा CEC_TX_DATA_BASE      0x40
#घोषणा CEC_TX_DATA_TOP       0x50
#घोषणा CEC_TX_DATA_SIZE      0x1
#घोषणा CEC_RX_DATA_BASE      0x54
#घोषणा CEC_RX_DATA_TOP       0x64
#घोषणा CEC_RX_DATA_SIZE      0x1

/* CEC_CTRL2 */
#घोषणा CEC_LINE_INACTIVE_EN   BIT(0)
#घोषणा CEC_AUTO_BUS_ERR_EN    BIT(1)
#घोषणा CEC_STOP_ON_ARB_ERR_EN BIT(2)
#घोषणा CEC_TX_REQ_WAIT_EN     BIT(3)

/* CEC_DATA_ARRAY_CTRL */
#घोषणा CEC_TX_ARRAY_EN          BIT(0)
#घोषणा CEC_RX_ARRAY_EN          BIT(1)
#घोषणा CEC_TX_ARRAY_RESET       BIT(2)
#घोषणा CEC_RX_ARRAY_RESET       BIT(3)
#घोषणा CEC_TX_N_OF_BYTES_IRQ_EN BIT(4)
#घोषणा CEC_TX_STOP_ON_NACK      BIT(7)

/* CEC_TX_ARRAY_CTRL */
#घोषणा CEC_TX_N_OF_BYTES  0x1F
#घोषणा CEC_TX_START       BIT(5)
#घोषणा CEC_TX_AUTO_SOM_EN BIT(6)
#घोषणा CEC_TX_AUTO_EOM_EN BIT(7)

/* CEC_IRQ_CTRL */
#घोषणा CEC_TX_DONE_IRQ_EN   BIT(0)
#घोषणा CEC_ERROR_IRQ_EN     BIT(2)
#घोषणा CEC_RX_DONE_IRQ_EN   BIT(3)
#घोषणा CEC_RX_SOM_IRQ_EN    BIT(4)
#घोषणा CEC_RX_EOM_IRQ_EN    BIT(5)
#घोषणा CEC_FREE_TIME_IRQ_EN BIT(6)
#घोषणा CEC_PIN_STS_IRQ_EN   BIT(7)

/* CEC_CTRL */
#घोषणा CEC_IN_FILTER_EN    BIT(0)
#घोषणा CEC_PWR_SAVE_EN     BIT(1)
#घोषणा CEC_EN              BIT(4)
#घोषणा CEC_ACK_CTRL        BIT(5)
#घोषणा CEC_RX_RESET_EN     BIT(6)
#घोषणा CEC_IGNORE_RX_ERROR BIT(7)

/* CEC_STATUS */
#घोषणा CEC_TX_DONE_STS       BIT(0)
#घोषणा CEC_TX_ACK_GET_STS    BIT(1)
#घोषणा CEC_ERROR_STS         BIT(2)
#घोषणा CEC_RX_DONE_STS       BIT(3)
#घोषणा CEC_RX_SOM_STS        BIT(4)
#घोषणा CEC_RX_EOM_STS        BIT(5)
#घोषणा CEC_FREE_TIME_IRQ_STS BIT(6)
#घोषणा CEC_PIN_STS           BIT(7)
#घोषणा CEC_SBIT_TOUT_STS     BIT(8)
#घोषणा CEC_DBIT_TOUT_STS     BIT(9)
#घोषणा CEC_LPULSE_ERROR_STS  BIT(10)
#घोषणा CEC_HPULSE_ERROR_STS  BIT(11)
#घोषणा CEC_TX_ERROR          BIT(12)
#घोषणा CEC_TX_ARB_ERROR      BIT(13)
#घोषणा CEC_RX_ERROR_MIN      BIT(14)
#घोषणा CEC_RX_ERROR_MAX      BIT(15)

/* Signal मुक्त समय in bit periods (2.4ms) */
#घोषणा CEC_PRESENT_INIT_SFT 7
#घोषणा CEC_NEW_INIT_SFT     5
#घोषणा CEC_RETRANSMIT_SFT   3

/* Constants क्रम CEC_BIT_TOUT_THRESH रेजिस्टर */
#घोषणा CEC_SBIT_TOUT_47MS BIT(1)
#घोषणा CEC_SBIT_TOUT_48MS (BIT(0) | BIT(1))
#घोषणा CEC_SBIT_TOUT_50MS BIT(2)
#घोषणा CEC_DBIT_TOUT_27MS BIT(0)
#घोषणा CEC_DBIT_TOUT_28MS BIT(1)
#घोषणा CEC_DBIT_TOUT_29MS (BIT(0) | BIT(1))

/* Constants क्रम CEC_BIT_PULSE_THRESH रेजिस्टर */
#घोषणा CEC_BIT_LPULSE_03MS BIT(1)
#घोषणा CEC_BIT_HPULSE_03MS BIT(3)

/* Constants क्रम CEC_DATA_ARRAY_STATUS रेजिस्टर */
#घोषणा CEC_RX_N_OF_BYTES                     0x1F
#घोषणा CEC_TX_N_OF_BYTES_SENT                BIT(5)
#घोषणा CEC_RX_OVERRUN                        BIT(6)

काष्ठा stih_cec अणु
	काष्ठा cec_adapter	*adap;
	काष्ठा device		*dev;
	काष्ठा clk		*clk;
	व्योम __iomem		*regs;
	पूर्णांक			irq;
	u32			irq_status;
	काष्ठा cec_notअगरier	*notअगरier;
पूर्ण;

अटल पूर्णांक stih_cec_adap_enable(काष्ठा cec_adapter *adap, bool enable)
अणु
	काष्ठा stih_cec *cec = cec_get_drvdata(adap);

	अगर (enable) अणु
		/* The करोc says (input TCLK_PERIOD * CEC_CLK_DIV) = 0.1ms */
		अचिन्हित दीर्घ clk_freq = clk_get_rate(cec->clk);
		u32 cec_clk_भाग = clk_freq / 10000;

		ग_लिखोl(cec_clk_भाग, cec->regs + CEC_CLK_DIV);

		/* Configuration of the durations activating a समयout */
		ग_लिखोl(CEC_SBIT_TOUT_47MS | (CEC_DBIT_TOUT_28MS << 4),
		       cec->regs + CEC_BIT_TOUT_THRESH);

		/* Configuration of the smallest allowed duration क्रम pulses */
		ग_लिखोl(CEC_BIT_LPULSE_03MS | CEC_BIT_HPULSE_03MS,
		       cec->regs + CEC_BIT_PULSE_THRESH);

		/* Minimum received bit period threshold */
		ग_लिखोl(BIT(5) | BIT(7), cec->regs + CEC_TX_CTRL);

		/* Configuration of transceiver data arrays */
		ग_लिखोl(CEC_TX_ARRAY_EN | CEC_RX_ARRAY_EN | CEC_TX_STOP_ON_NACK,
		       cec->regs + CEC_DATA_ARRAY_CTRL);

		/* Configuration of the control bits क्रम CEC Transceiver */
		ग_लिखोl(CEC_IN_FILTER_EN | CEC_EN | CEC_RX_RESET_EN,
		       cec->regs + CEC_CTRL);

		/* Clear logical addresses */
		ग_लिखोl(0, cec->regs + CEC_ADDR_TABLE);

		/* Clear the status रेजिस्टर */
		ग_लिखोl(0x0, cec->regs + CEC_STATUS);

		/* Enable the पूर्णांकerrupts */
		ग_लिखोl(CEC_TX_DONE_IRQ_EN | CEC_RX_DONE_IRQ_EN |
		       CEC_RX_SOM_IRQ_EN | CEC_RX_EOM_IRQ_EN |
		       CEC_ERROR_IRQ_EN,
		       cec->regs + CEC_IRQ_CTRL);

	पूर्ण अन्यथा अणु
		/* Clear logical addresses */
		ग_लिखोl(0, cec->regs + CEC_ADDR_TABLE);

		/* Clear the status रेजिस्टर */
		ग_लिखोl(0x0, cec->regs + CEC_STATUS);

		/* Disable the पूर्णांकerrupts */
		ग_लिखोl(0, cec->regs + CEC_IRQ_CTRL);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stih_cec_adap_log_addr(काष्ठा cec_adapter *adap, u8 logical_addr)
अणु
	काष्ठा stih_cec *cec = cec_get_drvdata(adap);
	u32 reg = पढ़ोl(cec->regs + CEC_ADDR_TABLE);

	reg |= 1 << logical_addr;

	अगर (logical_addr == CEC_LOG_ADDR_INVALID)
		reg = 0;

	ग_लिखोl(reg, cec->regs + CEC_ADDR_TABLE);

	वापस 0;
पूर्ण

अटल पूर्णांक stih_cec_adap_transmit(काष्ठा cec_adapter *adap, u8 attempts,
				  u32 संकेत_मुक्त_समय, काष्ठा cec_msg *msg)
अणु
	काष्ठा stih_cec *cec = cec_get_drvdata(adap);
	पूर्णांक i;

	/* Copy message पूर्णांकo रेजिस्टरs */
	क्रम (i = 0; i < msg->len; i++)
		ग_लिखोb(msg->msg[i], cec->regs + CEC_TX_DATA_BASE + i);

	/*
	 * Start transmission, configure hardware to add start and stop bits
	 * Signal मुक्त समय is handled by the hardware
	 */
	ग_लिखोl(CEC_TX_AUTO_SOM_EN | CEC_TX_AUTO_EOM_EN | CEC_TX_START |
	       msg->len, cec->regs + CEC_TX_ARRAY_CTRL);

	वापस 0;
पूर्ण

अटल व्योम stih_tx_करोne(काष्ठा stih_cec *cec, u32 status)
अणु
	अगर (status & CEC_TX_ERROR) अणु
		cec_transmit_attempt_करोne(cec->adap, CEC_TX_STATUS_ERROR);
		वापस;
	पूर्ण

	अगर (status & CEC_TX_ARB_ERROR) अणु
		cec_transmit_attempt_करोne(cec->adap, CEC_TX_STATUS_ARB_LOST);
		वापस;
	पूर्ण

	अगर (!(status & CEC_TX_ACK_GET_STS)) अणु
		cec_transmit_attempt_करोne(cec->adap, CEC_TX_STATUS_NACK);
		वापस;
	पूर्ण

	cec_transmit_attempt_करोne(cec->adap, CEC_TX_STATUS_OK);
पूर्ण

अटल व्योम stih_rx_करोne(काष्ठा stih_cec *cec, u32 status)
अणु
	काष्ठा cec_msg msg = अणुपूर्ण;
	u8 i;

	अगर (status & CEC_RX_ERROR_MIN)
		वापस;

	अगर (status & CEC_RX_ERROR_MAX)
		वापस;

	msg.len = पढ़ोl(cec->regs + CEC_DATA_ARRAY_STATUS) & 0x1f;

	अगर (!msg.len)
		वापस;

	अगर (msg.len > 16)
		msg.len = 16;

	क्रम (i = 0; i < msg.len; i++)
		msg.msg[i] = पढ़ोl(cec->regs + CEC_RX_DATA_BASE + i);

	cec_received_msg(cec->adap, &msg);
पूर्ण

अटल irqवापस_t stih_cec_irq_handler_thपढ़ो(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा stih_cec *cec = priv;

	अगर (cec->irq_status & CEC_TX_DONE_STS)
		stih_tx_करोne(cec, cec->irq_status);

	अगर (cec->irq_status & CEC_RX_DONE_STS)
		stih_rx_करोne(cec, cec->irq_status);

	cec->irq_status = 0;

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t stih_cec_irq_handler(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा stih_cec *cec = priv;

	cec->irq_status = पढ़ोl(cec->regs + CEC_STATUS);
	ग_लिखोl(cec->irq_status, cec->regs + CEC_STATUS);

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल स्थिर काष्ठा cec_adap_ops sti_cec_adap_ops = अणु
	.adap_enable = stih_cec_adap_enable,
	.adap_log_addr = stih_cec_adap_log_addr,
	.adap_transmit = stih_cec_adap_transmit,
पूर्ण;

अटल पूर्णांक stih_cec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	काष्ठा stih_cec *cec;
	काष्ठा device *hdmi_dev;
	पूर्णांक ret;

	hdmi_dev = cec_notअगरier_parse_hdmi_phandle(dev);

	अगर (IS_ERR(hdmi_dev))
		वापस PTR_ERR(hdmi_dev);

	cec = devm_kzalloc(dev, माप(*cec), GFP_KERNEL);
	अगर (!cec)
		वापस -ENOMEM;

	cec->dev = dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	cec->regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(cec->regs))
		वापस PTR_ERR(cec->regs);

	cec->irq = platक्रमm_get_irq(pdev, 0);
	अगर (cec->irq < 0)
		वापस cec->irq;

	ret = devm_request_thपढ़ोed_irq(dev, cec->irq, stih_cec_irq_handler,
					stih_cec_irq_handler_thपढ़ो, 0,
					pdev->name, cec);
	अगर (ret)
		वापस ret;

	cec->clk = devm_clk_get(dev, "cec-clk");
	अगर (IS_ERR(cec->clk)) अणु
		dev_err(dev, "Cannot get cec clock\n");
		वापस PTR_ERR(cec->clk);
	पूर्ण

	cec->adap = cec_allocate_adapter(&sti_cec_adap_ops, cec, CEC_NAME,
					 CEC_CAP_DEFAULTS |
					 CEC_CAP_CONNECTOR_INFO,
					 CEC_MAX_LOG_ADDRS);
	ret = PTR_ERR_OR_ZERO(cec->adap);
	अगर (ret)
		वापस ret;

	cec->notअगरier = cec_notअगरier_cec_adap_रेजिस्टर(hdmi_dev, शून्य,
						       cec->adap);
	अगर (!cec->notअगरier) अणु
		ret = -ENOMEM;
		जाओ err_delete_adapter;
	पूर्ण

	ret = cec_रेजिस्टर_adapter(cec->adap, &pdev->dev);
	अगर (ret)
		जाओ err_notअगरier;

	platक्रमm_set_drvdata(pdev, cec);
	वापस 0;

err_notअगरier:
	cec_notअगरier_cec_adap_unरेजिस्टर(cec->notअगरier, cec->adap);

err_delete_adapter:
	cec_delete_adapter(cec->adap);
	वापस ret;
पूर्ण

अटल पूर्णांक stih_cec_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा stih_cec *cec = platक्रमm_get_drvdata(pdev);

	cec_notअगरier_cec_adap_unरेजिस्टर(cec->notअगरier, cec->adap);
	cec_unरेजिस्टर_adapter(cec->adap);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id stih_cec_match[] = अणु
	अणु
		.compatible	= "st,stih-cec",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, stih_cec_match);

अटल काष्ठा platक्रमm_driver stih_cec_pdrv = अणु
	.probe	= stih_cec_probe,
	.हटाओ = stih_cec_हटाओ,
	.driver = अणु
		.name		= CEC_NAME,
		.of_match_table	= stih_cec_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(stih_cec_pdrv);

MODULE_AUTHOR("Benjamin Gaignard <benjamin.gaignard@linaro.org>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("STIH4xx CEC driver");
