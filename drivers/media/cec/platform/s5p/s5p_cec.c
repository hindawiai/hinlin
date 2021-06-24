<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* drivers/media/platक्रमm/s5p-cec/s5p_cec.c
 *
 * Samsung S5P CEC driver
 *
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 *
 * This driver is based on the "cec interface driver for exynos soc" by
 * SangPil Moon.
 */

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/समयr.h>
#समावेश <linux/workqueue.h>
#समावेश <media/cec.h>
#समावेश <media/cec-notअगरier.h>

#समावेश "exynos_hdmi_cec.h"
#समावेश "regs-cec.h"
#समावेश "s5p_cec.h"

#घोषणा CEC_NAME	"s5p-cec"

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "debug level (0-2)");

अटल पूर्णांक s5p_cec_adap_enable(काष्ठा cec_adapter *adap, bool enable)
अणु
	काष्ठा s5p_cec_dev *cec = cec_get_drvdata(adap);

	अगर (enable) अणु
		pm_runसमय_get_sync(cec->dev);

		s5p_cec_reset(cec);

		s5p_cec_set_भागider(cec);
		s5p_cec_threshold(cec);

		s5p_cec_unmask_tx_पूर्णांकerrupts(cec);
		s5p_cec_unmask_rx_पूर्णांकerrupts(cec);
		s5p_cec_enable_rx(cec);
	पूर्ण अन्यथा अणु
		s5p_cec_mask_tx_पूर्णांकerrupts(cec);
		s5p_cec_mask_rx_पूर्णांकerrupts(cec);
		pm_runसमय_disable(cec->dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s5p_cec_adap_log_addr(काष्ठा cec_adapter *adap, u8 addr)
अणु
	काष्ठा s5p_cec_dev *cec = cec_get_drvdata(adap);

	s5p_cec_set_addr(cec, addr);
	वापस 0;
पूर्ण

अटल पूर्णांक s5p_cec_adap_transmit(काष्ठा cec_adapter *adap, u8 attempts,
				 u32 संकेत_मुक्त_समय, काष्ठा cec_msg *msg)
अणु
	काष्ठा s5p_cec_dev *cec = cec_get_drvdata(adap);

	/*
	 * Unclear अगर 0 retries are allowed by the hardware, so have 1 as
	 * the minimum.
	 */
	s5p_cec_copy_packet(cec, msg->msg, msg->len, max(1, attempts - 1));
	वापस 0;
पूर्ण

अटल irqवापस_t s5p_cec_irq_handler(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा s5p_cec_dev *cec = priv;
	u32 status = 0;

	status = s5p_cec_get_status(cec);

	dev_dbg(cec->dev, "irq received\n");

	अगर (status & CEC_STATUS_TX_DONE) अणु
		अगर (status & CEC_STATUS_TX_NACK) अणु
			dev_dbg(cec->dev, "CEC_STATUS_TX_NACK set\n");
			cec->tx = STATE_NACK;
		पूर्ण अन्यथा अगर (status & CEC_STATUS_TX_ERROR) अणु
			dev_dbg(cec->dev, "CEC_STATUS_TX_ERROR set\n");
			cec->tx = STATE_ERROR;
		पूर्ण अन्यथा अणु
			dev_dbg(cec->dev, "CEC_STATUS_TX_DONE\n");
			cec->tx = STATE_DONE;
		पूर्ण
		s5p_clr_pending_tx(cec);
	पूर्ण

	अगर (status & CEC_STATUS_RX_DONE) अणु
		अगर (status & CEC_STATUS_RX_ERROR) अणु
			dev_dbg(cec->dev, "CEC_STATUS_RX_ERROR set\n");
			s5p_cec_rx_reset(cec);
			s5p_cec_enable_rx(cec);
		पूर्ण अन्यथा अणु
			dev_dbg(cec->dev, "CEC_STATUS_RX_DONE set\n");
			अगर (cec->rx != STATE_IDLE)
				dev_dbg(cec->dev, "Buffer overrun (worker did not process previous message)\n");
			cec->rx = STATE_BUSY;
			cec->msg.len = status >> 24;
			cec->msg.rx_status = CEC_RX_STATUS_OK;
			s5p_cec_get_rx_buf(cec, cec->msg.len,
					cec->msg.msg);
			cec->rx = STATE_DONE;
			s5p_cec_enable_rx(cec);
		पूर्ण
		/* Clear पूर्णांकerrupt pending bit */
		s5p_clr_pending_rx(cec);
	पूर्ण
	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t s5p_cec_irq_handler_thपढ़ो(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा s5p_cec_dev *cec = priv;

	dev_dbg(cec->dev, "irq processing thread\n");
	चयन (cec->tx) अणु
	हाल STATE_DONE:
		cec_transmit_करोne(cec->adap, CEC_TX_STATUS_OK, 0, 0, 0, 0);
		cec->tx = STATE_IDLE;
		अवरोध;
	हाल STATE_NACK:
		cec_transmit_करोne(cec->adap,
			CEC_TX_STATUS_MAX_RETRIES | CEC_TX_STATUS_NACK,
			0, 1, 0, 0);
		cec->tx = STATE_IDLE;
		अवरोध;
	हाल STATE_ERROR:
		cec_transmit_करोne(cec->adap,
			CEC_TX_STATUS_MAX_RETRIES | CEC_TX_STATUS_ERROR,
			0, 0, 0, 1);
		cec->tx = STATE_IDLE;
		अवरोध;
	हाल STATE_BUSY:
		dev_err(cec->dev, "state set to busy, this should not occur here\n");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (cec->rx) अणु
	हाल STATE_DONE:
		cec_received_msg(cec->adap, &cec->msg);
		cec->rx = STATE_IDLE;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा cec_adap_ops s5p_cec_adap_ops = अणु
	.adap_enable = s5p_cec_adap_enable,
	.adap_log_addr = s5p_cec_adap_log_addr,
	.adap_transmit = s5p_cec_adap_transmit,
पूर्ण;

अटल पूर्णांक s5p_cec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device *hdmi_dev;
	काष्ठा resource *res;
	काष्ठा s5p_cec_dev *cec;
	bool needs_hpd = of_property_पढ़ो_bool(pdev->dev.of_node, "needs-hpd");
	पूर्णांक ret;

	hdmi_dev = cec_notअगरier_parse_hdmi_phandle(dev);

	अगर (IS_ERR(hdmi_dev))
		वापस PTR_ERR(hdmi_dev);

	cec = devm_kzalloc(&pdev->dev, माप(*cec), GFP_KERNEL);
	अगर (!cec)
		वापस -ENOMEM;

	cec->dev = dev;

	cec->irq = platक्रमm_get_irq(pdev, 0);
	अगर (cec->irq < 0)
		वापस cec->irq;

	ret = devm_request_thपढ़ोed_irq(dev, cec->irq, s5p_cec_irq_handler,
		s5p_cec_irq_handler_thपढ़ो, 0, pdev->name, cec);
	अगर (ret)
		वापस ret;

	cec->clk = devm_clk_get(dev, "hdmicec");
	अगर (IS_ERR(cec->clk))
		वापस PTR_ERR(cec->clk);

	cec->pmu = syscon_regmap_lookup_by_phandle(dev->of_node,
						 "samsung,syscon-phandle");
	अगर (IS_ERR(cec->pmu))
		वापस -EPROBE_DEFER;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	cec->reg = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(cec->reg))
		वापस PTR_ERR(cec->reg);

	cec->adap = cec_allocate_adapter(&s5p_cec_adap_ops, cec, CEC_NAME,
		CEC_CAP_DEFAULTS | (needs_hpd ? CEC_CAP_NEEDS_HPD : 0) |
		CEC_CAP_CONNECTOR_INFO, 1);
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
	pm_runसमय_enable(dev);

	dev_dbg(dev, "successfully probed\n");
	वापस 0;

err_notअगरier:
	cec_notअगरier_cec_adap_unरेजिस्टर(cec->notअगरier, cec->adap);

err_delete_adapter:
	cec_delete_adapter(cec->adap);
	वापस ret;
पूर्ण

अटल पूर्णांक s5p_cec_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा s5p_cec_dev *cec = platक्रमm_get_drvdata(pdev);

	cec_notअगरier_cec_adap_unरेजिस्टर(cec->notअगरier, cec->adap);
	cec_unरेजिस्टर_adapter(cec->adap);
	pm_runसमय_disable(&pdev->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused s5p_cec_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा s5p_cec_dev *cec = dev_get_drvdata(dev);

	clk_disable_unprepare(cec->clk);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused s5p_cec_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा s5p_cec_dev *cec = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(cec->clk);
	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops s5p_cec_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(s5p_cec_runसमय_suspend, s5p_cec_runसमय_resume,
			   शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id s5p_cec_match[] = अणु
	अणु
		.compatible	= "samsung,s5p-cec",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, s5p_cec_match);

अटल काष्ठा platक्रमm_driver s5p_cec_pdrv = अणु
	.probe	= s5p_cec_probe,
	.हटाओ	= s5p_cec_हटाओ,
	.driver	= अणु
		.name		= CEC_NAME,
		.of_match_table	= s5p_cec_match,
		.pm		= &s5p_cec_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(s5p_cec_pdrv);

MODULE_AUTHOR("Kamil Debski <kamil@wypas.org>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Samsung S5P CEC driver");
