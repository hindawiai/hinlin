<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * STM32 CEC driver
 * Copyright (C) STMicroelectronics SA 2017
 *
 */

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश <media/cec.h>

#घोषणा CEC_NAME	"stm32-cec"

/* CEC रेजिस्टरs  */
#घोषणा CEC_CR		0x0000 /* Control Register */
#घोषणा CEC_CFGR	0x0004 /* ConFiGuration Register */
#घोषणा CEC_TXDR	0x0008 /* Rx data Register */
#घोषणा CEC_RXDR	0x000C /* Rx data Register */
#घोषणा CEC_ISR		0x0010 /* Interrupt and status Register */
#घोषणा CEC_IER		0x0014 /* Interrupt enable Register */

#घोषणा TXEOM		BIT(2)
#घोषणा TXSOM		BIT(1)
#घोषणा CECEN		BIT(0)

#घोषणा LSTN		BIT(31)
#घोषणा OAR		GENMASK(30, 16)
#घोषणा SFTOP		BIT(8)
#घोषणा BRDNOGEN	BIT(7)
#घोषणा LBPEGEN		BIT(6)
#घोषणा BREGEN		BIT(5)
#घोषणा BRESTP		BIT(4)
#घोषणा RXTOL		BIT(3)
#घोषणा SFT		GENMASK(2, 0)
#घोषणा FULL_CFG	(LSTN | SFTOP | BRDNOGEN | LBPEGEN | BREGEN | BRESTP \
			 | RXTOL)

#घोषणा TXACKE		BIT(12)
#घोषणा TXERR		BIT(11)
#घोषणा TXUDR		BIT(10)
#घोषणा TXEND		BIT(9)
#घोषणा TXBR		BIT(8)
#घोषणा ARBLST		BIT(7)
#घोषणा RXACKE		BIT(6)
#घोषणा RXOVR		BIT(2)
#घोषणा RXEND		BIT(1)
#घोषणा RXBR		BIT(0)

#घोषणा ALL_TX_IT	(TXEND | TXBR | TXACKE | TXERR | TXUDR | ARBLST)
#घोषणा ALL_RX_IT	(RXEND | RXBR | RXACKE | RXOVR)

/*
 * 400 ms is the समय it takes क्रम one 16 byte message to be
 * transferred and 5 is the maximum number of retries. Add
 * another 100 ms as a margin.
 */
#घोषणा CEC_XFER_TIMEOUT_MS (5 * 400 + 100)

काष्ठा sपंचांग32_cec अणु
	काष्ठा cec_adapter	*adap;
	काष्ठा device		*dev;
	काष्ठा clk		*clk_cec;
	काष्ठा clk		*clk_hdmi_cec;
	काष्ठा reset_control	*rstc;
	काष्ठा regmap		*regmap;
	पूर्णांक			irq;
	u32			irq_status;
	काष्ठा cec_msg		rx_msg;
	काष्ठा cec_msg		tx_msg;
	पूर्णांक			tx_cnt;
पूर्ण;

अटल व्योम cec_hw_init(काष्ठा sपंचांग32_cec *cec)
अणु
	regmap_update_bits(cec->regmap, CEC_CR, TXEOM | TXSOM | CECEN, 0);

	regmap_update_bits(cec->regmap, CEC_IER, ALL_TX_IT | ALL_RX_IT,
			   ALL_TX_IT | ALL_RX_IT);

	regmap_update_bits(cec->regmap, CEC_CFGR, FULL_CFG, FULL_CFG);
पूर्ण

अटल व्योम sपंचांग32_tx_करोne(काष्ठा sपंचांग32_cec *cec, u32 status)
अणु
	अगर (status & (TXERR | TXUDR)) अणु
		cec_transmit_करोne(cec->adap, CEC_TX_STATUS_ERROR,
				  0, 0, 0, 1);
		वापस;
	पूर्ण

	अगर (status & ARBLST) अणु
		cec_transmit_करोne(cec->adap, CEC_TX_STATUS_ARB_LOST,
				  1, 0, 0, 0);
		वापस;
	पूर्ण

	अगर (status & TXACKE) अणु
		cec_transmit_करोne(cec->adap, CEC_TX_STATUS_NACK,
				  0, 1, 0, 0);
		वापस;
	पूर्ण

	अगर (cec->irq_status & TXBR) अणु
		/* send next byte */
		अगर (cec->tx_cnt < cec->tx_msg.len)
			regmap_ग_लिखो(cec->regmap, CEC_TXDR,
				     cec->tx_msg.msg[cec->tx_cnt++]);

		/* TXEOM is set to command transmission of the last byte */
		अगर (cec->tx_cnt == cec->tx_msg.len)
			regmap_update_bits(cec->regmap, CEC_CR, TXEOM, TXEOM);
	पूर्ण

	अगर (cec->irq_status & TXEND)
		cec_transmit_करोne(cec->adap, CEC_TX_STATUS_OK, 0, 0, 0, 0);
पूर्ण

अटल व्योम sपंचांग32_rx_करोne(काष्ठा sपंचांग32_cec *cec, u32 status)
अणु
	अगर (cec->irq_status & (RXACKE | RXOVR)) अणु
		cec->rx_msg.len = 0;
		वापस;
	पूर्ण

	अगर (cec->irq_status & RXBR) अणु
		u32 val;

		regmap_पढ़ो(cec->regmap, CEC_RXDR, &val);
		cec->rx_msg.msg[cec->rx_msg.len++] = val & 0xFF;
	पूर्ण

	अगर (cec->irq_status & RXEND) अणु
		cec_received_msg(cec->adap, &cec->rx_msg);
		cec->rx_msg.len = 0;
	पूर्ण
पूर्ण

अटल irqवापस_t sपंचांग32_cec_irq_thपढ़ो(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा sपंचांग32_cec *cec = arg;

	अगर (cec->irq_status & ALL_TX_IT)
		sपंचांग32_tx_करोne(cec, cec->irq_status);

	अगर (cec->irq_status & ALL_RX_IT)
		sपंचांग32_rx_करोne(cec, cec->irq_status);

	cec->irq_status = 0;

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t sपंचांग32_cec_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा sपंचांग32_cec *cec = arg;

	regmap_पढ़ो(cec->regmap, CEC_ISR, &cec->irq_status);

	regmap_update_bits(cec->regmap, CEC_ISR,
			   ALL_TX_IT | ALL_RX_IT,
			   ALL_TX_IT | ALL_RX_IT);

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल पूर्णांक sपंचांग32_cec_adap_enable(काष्ठा cec_adapter *adap, bool enable)
अणु
	काष्ठा sपंचांग32_cec *cec = adap->priv;
	पूर्णांक ret = 0;

	अगर (enable) अणु
		ret = clk_enable(cec->clk_cec);
		अगर (ret)
			dev_err(cec->dev, "fail to enable cec clock\n");

		clk_enable(cec->clk_hdmi_cec);
		regmap_update_bits(cec->regmap, CEC_CR, CECEN, CECEN);
	पूर्ण अन्यथा अणु
		clk_disable(cec->clk_cec);
		clk_disable(cec->clk_hdmi_cec);
		regmap_update_bits(cec->regmap, CEC_CR, CECEN, 0);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_cec_adap_log_addr(काष्ठा cec_adapter *adap, u8 logical_addr)
अणु
	काष्ठा sपंचांग32_cec *cec = adap->priv;
	u32 oar = (1 << logical_addr) << 16;
	u32 val;

	/* Poll every 100तगs the रेजिस्टर CEC_CR to रुको end of transmission */
	regmap_पढ़ो_poll_समयout(cec->regmap, CEC_CR, val, !(val & TXSOM),
				 100, CEC_XFER_TIMEOUT_MS * 1000);
	regmap_update_bits(cec->regmap, CEC_CR, CECEN, 0);

	अगर (logical_addr == CEC_LOG_ADDR_INVALID)
		regmap_update_bits(cec->regmap, CEC_CFGR, OAR, 0);
	अन्यथा
		regmap_update_bits(cec->regmap, CEC_CFGR, oar, oar);

	regmap_update_bits(cec->regmap, CEC_CR, CECEN, CECEN);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_cec_adap_transmit(काष्ठा cec_adapter *adap, u8 attempts,
				   u32 संकेत_मुक्त_समय, काष्ठा cec_msg *msg)
अणु
	काष्ठा sपंचांग32_cec *cec = adap->priv;

	/* Copy message */
	cec->tx_msg = *msg;
	cec->tx_cnt = 0;

	/*
	 * If the CEC message consists of only one byte,
	 * TXEOM must be set beक्रमe of TXSOM.
	 */
	अगर (cec->tx_msg.len == 1)
		regmap_update_bits(cec->regmap, CEC_CR, TXEOM, TXEOM);

	/* TXSOM is set to command transmission of the first byte */
	regmap_update_bits(cec->regmap, CEC_CR, TXSOM, TXSOM);

	/* Write the header (first byte of message) */
	regmap_ग_लिखो(cec->regmap, CEC_TXDR, cec->tx_msg.msg[0]);
	cec->tx_cnt++;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cec_adap_ops sपंचांग32_cec_adap_ops = अणु
	.adap_enable = sपंचांग32_cec_adap_enable,
	.adap_log_addr = sपंचांग32_cec_adap_log_addr,
	.adap_transmit = sपंचांग32_cec_adap_transmit,
पूर्ण;

अटल स्थिर काष्ठा regmap_config sपंचांग32_cec_regmap_cfg = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = माप(u32),
	.max_रेजिस्टर = 0x14,
	.fast_io = true,
पूर्ण;

अटल पूर्णांक sपंचांग32_cec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	u32 caps = CEC_CAP_DEFAULTS | CEC_CAP_PHYS_ADDR | CEC_MODE_MONITOR_ALL;
	काष्ठा resource *res;
	काष्ठा sपंचांग32_cec *cec;
	व्योम __iomem *mmio;
	पूर्णांक ret;

	cec = devm_kzalloc(&pdev->dev, माप(*cec), GFP_KERNEL);
	अगर (!cec)
		वापस -ENOMEM;

	cec->dev = &pdev->dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	mmio = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(mmio))
		वापस PTR_ERR(mmio);

	cec->regmap = devm_regmap_init_mmio_clk(&pdev->dev, "cec", mmio,
						&sपंचांग32_cec_regmap_cfg);

	अगर (IS_ERR(cec->regmap))
		वापस PTR_ERR(cec->regmap);

	cec->irq = platक्रमm_get_irq(pdev, 0);
	अगर (cec->irq < 0)
		वापस cec->irq;

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, cec->irq,
					sपंचांग32_cec_irq_handler,
					sपंचांग32_cec_irq_thपढ़ो,
					0,
					pdev->name, cec);
	अगर (ret)
		वापस ret;

	cec->clk_cec = devm_clk_get(&pdev->dev, "cec");
	अगर (IS_ERR(cec->clk_cec)) अणु
		अगर (PTR_ERR(cec->clk_cec) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Cannot get cec clock\n");

		वापस PTR_ERR(cec->clk_cec);
	पूर्ण

	ret = clk_prepare(cec->clk_cec);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Unable to prepare cec clock\n");
		वापस ret;
	पूर्ण

	cec->clk_hdmi_cec = devm_clk_get(&pdev->dev, "hdmi-cec");
	अगर (IS_ERR(cec->clk_hdmi_cec) &&
	    PTR_ERR(cec->clk_hdmi_cec) == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;

	अगर (!IS_ERR(cec->clk_hdmi_cec)) अणु
		ret = clk_prepare(cec->clk_hdmi_cec);
		अगर (ret) अणु
			dev_err(&pdev->dev, "Can't prepare hdmi-cec clock\n");
			वापस ret;
		पूर्ण
	पूर्ण

	/*
	 * CEC_CAP_PHYS_ADDR caps should be हटाओd when a cec notअगरier is
	 * available क्रम example when a drm driver can provide edid
	 */
	cec->adap = cec_allocate_adapter(&sपंचांग32_cec_adap_ops, cec,
			CEC_NAME, caps,	CEC_MAX_LOG_ADDRS);
	ret = PTR_ERR_OR_ZERO(cec->adap);
	अगर (ret)
		वापस ret;

	ret = cec_रेजिस्टर_adapter(cec->adap, &pdev->dev);
	अगर (ret) अणु
		cec_delete_adapter(cec->adap);
		वापस ret;
	पूर्ण

	cec_hw_init(cec);

	platक्रमm_set_drvdata(pdev, cec);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_cec_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_cec *cec = platक्रमm_get_drvdata(pdev);

	clk_unprepare(cec->clk_cec);
	clk_unprepare(cec->clk_hdmi_cec);

	cec_unरेजिस्टर_adapter(cec->adap);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sपंचांग32_cec_of_match[] = अणु
	अणु .compatible = "st,stm32-cec" पूर्ण,
	अणु /* end node */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_cec_of_match);

अटल काष्ठा platक्रमm_driver sपंचांग32_cec_driver = अणु
	.probe  = sपंचांग32_cec_probe,
	.हटाओ = sपंचांग32_cec_हटाओ,
	.driver = अणु
		.name		= CEC_NAME,
		.of_match_table = sपंचांग32_cec_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sपंचांग32_cec_driver);

MODULE_AUTHOR("Benjamin Gaignard <benjamin.gaignard@st.com>");
MODULE_AUTHOR("Yannick Fertre <yannick.fertre@st.com>");
MODULE_DESCRIPTION("STMicroelectronics STM32 Consumer Electronics Control");
MODULE_LICENSE("GPL v2");
