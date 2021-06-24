<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Tegra CEC implementation
 *
 * The original 3.10 CEC driver using a custom API:
 *
 * Copyright (c) 2012-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * Conversion to the CEC framework and to the मुख्यline kernel:
 *
 * Copyright 2016-2017 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk/tegra.h>

#समावेश <media/cec-notअगरier.h>

#समावेश "tegra_cec.h"

#घोषणा TEGRA_CEC_NAME "tegra-cec"

काष्ठा tegra_cec अणु
	काष्ठा cec_adapter	*adap;
	काष्ठा device		*dev;
	काष्ठा clk		*clk;
	व्योम __iomem		*cec_base;
	काष्ठा cec_notअगरier	*notअगरier;
	पूर्णांक			tegra_cec_irq;
	bool			rx_करोne;
	bool			tx_करोne;
	पूर्णांक			tx_status;
	u8			rx_buf[CEC_MAX_MSG_SIZE];
	u8			rx_buf_cnt;
	u32			tx_buf[CEC_MAX_MSG_SIZE];
	u8			tx_buf_cur;
	u8			tx_buf_cnt;
पूर्ण;

अटल अंतरभूत u32 cec_पढ़ो(काष्ठा tegra_cec *cec, u32 reg)
अणु
	वापस पढ़ोl(cec->cec_base + reg);
पूर्ण

अटल अंतरभूत व्योम cec_ग_लिखो(काष्ठा tegra_cec *cec, u32 reg, u32 val)
अणु
	ग_लिखोl(val, cec->cec_base + reg);
पूर्ण

अटल व्योम tegra_cec_error_recovery(काष्ठा tegra_cec *cec)
अणु
	u32 hw_ctrl;

	hw_ctrl = cec_पढ़ो(cec, TEGRA_CEC_HW_CONTROL);
	cec_ग_लिखो(cec, TEGRA_CEC_HW_CONTROL, 0);
	cec_ग_लिखो(cec, TEGRA_CEC_INT_STAT, 0xffffffff);
	cec_ग_लिखो(cec, TEGRA_CEC_HW_CONTROL, hw_ctrl);
पूर्ण

अटल irqवापस_t tegra_cec_irq_thपढ़ो_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा device *dev = data;
	काष्ठा tegra_cec *cec = dev_get_drvdata(dev);

	अगर (cec->tx_करोne) अणु
		cec_transmit_attempt_करोne(cec->adap, cec->tx_status);
		cec->tx_करोne = false;
	पूर्ण
	अगर (cec->rx_करोne) अणु
		काष्ठा cec_msg msg = अणुपूर्ण;

		msg.len = cec->rx_buf_cnt;
		स_नकल(msg.msg, cec->rx_buf, msg.len);
		cec_received_msg(cec->adap, &msg);
		cec->rx_करोne = false;
		cec->rx_buf_cnt = 0;
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t tegra_cec_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा device *dev = data;
	काष्ठा tegra_cec *cec = dev_get_drvdata(dev);
	u32 status, mask;

	status = cec_पढ़ो(cec, TEGRA_CEC_INT_STAT);
	mask = cec_पढ़ो(cec, TEGRA_CEC_INT_MASK);

	status &= mask;

	अगर (!status)
		वापस IRQ_HANDLED;

	अगर (status & TEGRA_CEC_INT_STAT_TX_REGISTER_UNDERRUN) अणु
		dev_err(dev, "TX underrun, interrupt timing issue!\n");

		tegra_cec_error_recovery(cec);
		cec_ग_लिखो(cec, TEGRA_CEC_INT_MASK,
			  mask & ~TEGRA_CEC_INT_MASK_TX_REGISTER_EMPTY);

		cec->tx_करोne = true;
		cec->tx_status = CEC_TX_STATUS_ERROR;
		वापस IRQ_WAKE_THREAD;
	पूर्ण

	अगर ((status & TEGRA_CEC_INT_STAT_TX_ARBITRATION_FAILED) ||
		   (status & TEGRA_CEC_INT_STAT_TX_BUS_ANOMALY_DETECTED)) अणु
		tegra_cec_error_recovery(cec);
		cec_ग_लिखो(cec, TEGRA_CEC_INT_MASK,
			  mask & ~TEGRA_CEC_INT_MASK_TX_REGISTER_EMPTY);

		cec->tx_करोne = true;
		अगर (status & TEGRA_CEC_INT_STAT_TX_BUS_ANOMALY_DETECTED)
			cec->tx_status = CEC_TX_STATUS_LOW_DRIVE;
		अन्यथा
			cec->tx_status = CEC_TX_STATUS_ARB_LOST;
		वापस IRQ_WAKE_THREAD;
	पूर्ण

	अगर (status & TEGRA_CEC_INT_STAT_TX_FRAME_TRANSMITTED) अणु
		cec_ग_लिखो(cec, TEGRA_CEC_INT_STAT,
			  TEGRA_CEC_INT_STAT_TX_FRAME_TRANSMITTED);

		अगर (status & TEGRA_CEC_INT_STAT_TX_FRAME_OR_BLOCK_NAKD) अणु
			tegra_cec_error_recovery(cec);

			cec->tx_करोne = true;
			cec->tx_status = CEC_TX_STATUS_NACK;
		पूर्ण अन्यथा अणु
			cec->tx_करोne = true;
			cec->tx_status = CEC_TX_STATUS_OK;
		पूर्ण
		वापस IRQ_WAKE_THREAD;
	पूर्ण

	अगर (status & TEGRA_CEC_INT_STAT_TX_FRAME_OR_BLOCK_NAKD)
		dev_warn(dev, "TX NAKed on the fly!\n");

	अगर (status & TEGRA_CEC_INT_STAT_TX_REGISTER_EMPTY) अणु
		अगर (cec->tx_buf_cur == cec->tx_buf_cnt) अणु
			cec_ग_लिखो(cec, TEGRA_CEC_INT_MASK,
				  mask & ~TEGRA_CEC_INT_MASK_TX_REGISTER_EMPTY);
		पूर्ण अन्यथा अणु
			cec_ग_लिखो(cec, TEGRA_CEC_TX_REGISTER,
				  cec->tx_buf[cec->tx_buf_cur++]);
			cec_ग_लिखो(cec, TEGRA_CEC_INT_STAT,
				  TEGRA_CEC_INT_STAT_TX_REGISTER_EMPTY);
		पूर्ण
	पूर्ण

	अगर (status & TEGRA_CEC_INT_STAT_RX_START_BIT_DETECTED) अणु
		cec_ग_लिखो(cec, TEGRA_CEC_INT_STAT,
			  TEGRA_CEC_INT_STAT_RX_START_BIT_DETECTED);
		cec->rx_करोne = false;
		cec->rx_buf_cnt = 0;
	पूर्ण
	अगर (status & TEGRA_CEC_INT_STAT_RX_REGISTER_FULL) अणु
		u32 v;

		cec_ग_लिखो(cec, TEGRA_CEC_INT_STAT,
			  TEGRA_CEC_INT_STAT_RX_REGISTER_FULL);
		v = cec_पढ़ो(cec, TEGRA_CEC_RX_REGISTER);
		अगर (cec->rx_buf_cnt < CEC_MAX_MSG_SIZE)
			cec->rx_buf[cec->rx_buf_cnt++] = v & 0xff;
		अगर (v & TEGRA_CEC_RX_REGISTER_EOM) अणु
			cec->rx_करोne = true;
			वापस IRQ_WAKE_THREAD;
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक tegra_cec_adap_enable(काष्ठा cec_adapter *adap, bool enable)
अणु
	काष्ठा tegra_cec *cec = adap->priv;

	cec->rx_buf_cnt = 0;
	cec->tx_buf_cnt = 0;
	cec->tx_buf_cur = 0;

	cec_ग_लिखो(cec, TEGRA_CEC_HW_CONTROL, 0);
	cec_ग_लिखो(cec, TEGRA_CEC_INT_MASK, 0);
	cec_ग_लिखो(cec, TEGRA_CEC_INT_STAT, 0xffffffff);
	cec_ग_लिखो(cec, TEGRA_CEC_SW_CONTROL, 0);

	अगर (!enable)
		वापस 0;

	cec_ग_लिखो(cec, TEGRA_CEC_INPUT_FILTER, (1U << 31) | 0x20);

	cec_ग_लिखो(cec, TEGRA_CEC_RX_TIMING_0,
		  (0x7a << TEGRA_CEC_RX_TIM0_START_BIT_MAX_LO_TIME_SHIFT) |
		  (0x6d << TEGRA_CEC_RX_TIM0_START_BIT_MIN_LO_TIME_SHIFT) |
		  (0x93 << TEGRA_CEC_RX_TIM0_START_BIT_MAX_DURATION_SHIFT) |
		  (0x86 << TEGRA_CEC_RX_TIM0_START_BIT_MIN_DURATION_SHIFT));

	cec_ग_लिखो(cec, TEGRA_CEC_RX_TIMING_1,
		  (0x35 << TEGRA_CEC_RX_TIM1_DATA_BIT_MAX_LO_TIME_SHIFT) |
		  (0x21 << TEGRA_CEC_RX_TIM1_DATA_BIT_SAMPLE_TIME_SHIFT) |
		  (0x56 << TEGRA_CEC_RX_TIM1_DATA_BIT_MAX_DURATION_SHIFT) |
		  (0x40 << TEGRA_CEC_RX_TIM1_DATA_BIT_MIN_DURATION_SHIFT));

	cec_ग_लिखो(cec, TEGRA_CEC_RX_TIMING_2,
		  (0x50 << TEGRA_CEC_RX_TIM2_END_OF_BLOCK_TIME_SHIFT));

	cec_ग_लिखो(cec, TEGRA_CEC_TX_TIMING_0,
		  (0x74 << TEGRA_CEC_TX_TIM0_START_BIT_LO_TIME_SHIFT) |
		  (0x8d << TEGRA_CEC_TX_TIM0_START_BIT_DURATION_SHIFT) |
		  (0x08 << TEGRA_CEC_TX_TIM0_BUS_XITION_TIME_SHIFT) |
		  (0x71 << TEGRA_CEC_TX_TIM0_BUS_ERROR_LO_TIME_SHIFT));

	cec_ग_लिखो(cec, TEGRA_CEC_TX_TIMING_1,
		  (0x2f << TEGRA_CEC_TX_TIM1_LO_DATA_BIT_LO_TIME_SHIFT) |
		  (0x13 << TEGRA_CEC_TX_TIM1_HI_DATA_BIT_LO_TIME_SHIFT) |
		  (0x4b << TEGRA_CEC_TX_TIM1_DATA_BIT_DURATION_SHIFT) |
		  (0x21 << TEGRA_CEC_TX_TIM1_ACK_NAK_BIT_SAMPLE_TIME_SHIFT));

	cec_ग_लिखो(cec, TEGRA_CEC_TX_TIMING_2,
		  (0x07 << TEGRA_CEC_TX_TIM2_BUS_IDLE_TIME_ADDITIONAL_FRAME_SHIFT) |
		  (0x05 << TEGRA_CEC_TX_TIM2_BUS_IDLE_TIME_NEW_FRAME_SHIFT) |
		  (0x03 << TEGRA_CEC_TX_TIM2_BUS_IDLE_TIME_RETRY_FRAME_SHIFT));

	cec_ग_लिखो(cec, TEGRA_CEC_INT_MASK,
		  TEGRA_CEC_INT_MASK_TX_REGISTER_UNDERRUN |
		  TEGRA_CEC_INT_MASK_TX_FRAME_OR_BLOCK_NAKD |
		  TEGRA_CEC_INT_MASK_TX_ARBITRATION_FAILED |
		  TEGRA_CEC_INT_MASK_TX_BUS_ANOMALY_DETECTED |
		  TEGRA_CEC_INT_MASK_TX_FRAME_TRANSMITTED |
		  TEGRA_CEC_INT_MASK_RX_REGISTER_FULL |
		  TEGRA_CEC_INT_MASK_RX_START_BIT_DETECTED);

	cec_ग_लिखो(cec, TEGRA_CEC_HW_CONTROL, TEGRA_CEC_HWCTRL_TX_RX_MODE);
	वापस 0;
पूर्ण

अटल पूर्णांक tegra_cec_adap_log_addr(काष्ठा cec_adapter *adap, u8 logical_addr)
अणु
	काष्ठा tegra_cec *cec = adap->priv;
	u32 state = cec_पढ़ो(cec, TEGRA_CEC_HW_CONTROL);

	अगर (logical_addr == CEC_LOG_ADDR_INVALID)
		state &= ~TEGRA_CEC_HWCTRL_RX_LADDR_MASK;
	अन्यथा
		state |= TEGRA_CEC_HWCTRL_RX_LADDR((1 << logical_addr));

	cec_ग_लिखो(cec, TEGRA_CEC_HW_CONTROL, state);
	वापस 0;
पूर्ण

अटल पूर्णांक tegra_cec_adap_monitor_all_enable(काष्ठा cec_adapter *adap,
					     bool enable)
अणु
	काष्ठा tegra_cec *cec = adap->priv;
	u32 reg = cec_पढ़ो(cec, TEGRA_CEC_HW_CONTROL);

	अगर (enable)
		reg |= TEGRA_CEC_HWCTRL_RX_SNOOP;
	अन्यथा
		reg &= ~TEGRA_CEC_HWCTRL_RX_SNOOP;
	cec_ग_लिखो(cec, TEGRA_CEC_HW_CONTROL, reg);
	वापस 0;
पूर्ण

अटल पूर्णांक tegra_cec_adap_transmit(काष्ठा cec_adapter *adap, u8 attempts,
				   u32 संकेत_मुक्त_समय_ms, काष्ठा cec_msg *msg)
अणु
	bool retry_xfer = संकेत_मुक्त_समय_ms == CEC_SIGNAL_FREE_TIME_RETRY;
	काष्ठा tegra_cec *cec = adap->priv;
	अचिन्हित पूर्णांक i;
	u32 mode = 0;
	u32 mask;

	अगर (cec_msg_is_broadcast(msg))
		mode = TEGRA_CEC_TX_REG_BCAST;

	cec->tx_buf_cur = 0;
	cec->tx_buf_cnt = msg->len;

	क्रम (i = 0; i < msg->len; i++) अणु
		cec->tx_buf[i] = mode | msg->msg[i];
		अगर (i == 0)
			cec->tx_buf[i] |= TEGRA_CEC_TX_REG_START_BIT;
		अगर (i == msg->len - 1)
			cec->tx_buf[i] |= TEGRA_CEC_TX_REG_EOM;
		अगर (i == 0 && retry_xfer)
			cec->tx_buf[i] |= TEGRA_CEC_TX_REG_RETRY;
	पूर्ण

	mask = cec_पढ़ो(cec, TEGRA_CEC_INT_MASK);
	cec_ग_लिखो(cec, TEGRA_CEC_INT_MASK,
		  mask | TEGRA_CEC_INT_MASK_TX_REGISTER_EMPTY);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cec_adap_ops tegra_cec_ops = अणु
	.adap_enable = tegra_cec_adap_enable,
	.adap_log_addr = tegra_cec_adap_log_addr,
	.adap_transmit = tegra_cec_adap_transmit,
	.adap_monitor_all_enable = tegra_cec_adap_monitor_all_enable,
पूर्ण;

अटल पूर्णांक tegra_cec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *hdmi_dev;
	काष्ठा tegra_cec *cec;
	काष्ठा resource *res;
	पूर्णांक ret = 0;

	hdmi_dev = cec_notअगरier_parse_hdmi_phandle(&pdev->dev);

	अगर (IS_ERR(hdmi_dev))
		वापस PTR_ERR(hdmi_dev);

	cec = devm_kzalloc(&pdev->dev, माप(काष्ठा tegra_cec), GFP_KERNEL);

	अगर (!cec)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	अगर (!res) अणु
		dev_err(&pdev->dev,
			"Unable to allocate resources for device\n");
		वापस -EBUSY;
	पूर्ण

	अगर (!devm_request_mem_region(&pdev->dev, res->start, resource_size(res),
		pdev->name)) अणु
		dev_err(&pdev->dev,
			"Unable to request mem region for device\n");
		वापस -EBUSY;
	पूर्ण

	cec->tegra_cec_irq = platक्रमm_get_irq(pdev, 0);

	अगर (cec->tegra_cec_irq <= 0)
		वापस -EBUSY;

	cec->cec_base = devm_ioremap(&pdev->dev, res->start,
					     resource_size(res));

	अगर (!cec->cec_base) अणु
		dev_err(&pdev->dev, "Unable to grab IOs for device\n");
		वापस -EBUSY;
	पूर्ण

	cec->clk = devm_clk_get(&pdev->dev, "cec");

	अगर (IS_ERR_OR_शून्य(cec->clk)) अणु
		dev_err(&pdev->dev, "Can't get clock for CEC\n");
		वापस -ENOENT;
	पूर्ण

	clk_prepare_enable(cec->clk);

	/* set context info. */
	cec->dev = &pdev->dev;

	platक्रमm_set_drvdata(pdev, cec);

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, cec->tegra_cec_irq,
		tegra_cec_irq_handler, tegra_cec_irq_thपढ़ो_handler,
		0, "cec_irq", &pdev->dev);

	अगर (ret) अणु
		dev_err(&pdev->dev,
			"Unable to request interrupt for device\n");
		जाओ err_clk;
	पूर्ण

	cec->adap = cec_allocate_adapter(&tegra_cec_ops, cec, TEGRA_CEC_NAME,
			CEC_CAP_DEFAULTS | CEC_CAP_MONITOR_ALL |
			CEC_CAP_CONNECTOR_INFO,
			CEC_MAX_LOG_ADDRS);
	अगर (IS_ERR(cec->adap)) अणु
		ret = -ENOMEM;
		dev_err(&pdev->dev, "Couldn't create cec adapter\n");
		जाओ err_clk;
	पूर्ण

	cec->notअगरier = cec_notअगरier_cec_adap_रेजिस्टर(hdmi_dev, शून्य,
						       cec->adap);
	अगर (!cec->notअगरier) अणु
		ret = -ENOMEM;
		जाओ err_adapter;
	पूर्ण

	ret = cec_रेजिस्टर_adapter(cec->adap, &pdev->dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Couldn't register device\n");
		जाओ err_notअगरier;
	पूर्ण

	वापस 0;

err_notअगरier:
	cec_notअगरier_cec_adap_unरेजिस्टर(cec->notअगरier, cec->adap);
err_adapter:
	cec_delete_adapter(cec->adap);
err_clk:
	clk_disable_unprepare(cec->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक tegra_cec_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_cec *cec = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(cec->clk);

	cec_notअगरier_cec_adap_unरेजिस्टर(cec->notअगरier, cec->adap);
	cec_unरेजिस्टर_adapter(cec->adap);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक tegra_cec_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state)
अणु
	काष्ठा tegra_cec *cec = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(cec->clk);

	dev_notice(&pdev->dev, "suspended\n");
	वापस 0;
पूर्ण

अटल पूर्णांक tegra_cec_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_cec *cec = platक्रमm_get_drvdata(pdev);

	dev_notice(&pdev->dev, "Resuming\n");

	clk_prepare_enable(cec->clk);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id tegra_cec_of_match[] = अणु
	अणु .compatible = "nvidia,tegra114-cec", पूर्ण,
	अणु .compatible = "nvidia,tegra124-cec", पूर्ण,
	अणु .compatible = "nvidia,tegra210-cec", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra_cec_driver = अणु
	.driver = अणु
		.name = TEGRA_CEC_NAME,
		.of_match_table = of_match_ptr(tegra_cec_of_match),
	पूर्ण,
	.probe = tegra_cec_probe,
	.हटाओ = tegra_cec_हटाओ,

#अगर_घोषित CONFIG_PM
	.suspend = tegra_cec_suspend,
	.resume = tegra_cec_resume,
#पूर्ण_अगर
पूर्ण;

module_platक्रमm_driver(tegra_cec_driver);

MODULE_DESCRIPTION("Tegra HDMI CEC driver");
MODULE_AUTHOR("NVIDIA CORPORATION");
MODULE_AUTHOR("Cisco Systems, Inc. and/or its affiliates");
MODULE_LICENSE("GPL v2");
