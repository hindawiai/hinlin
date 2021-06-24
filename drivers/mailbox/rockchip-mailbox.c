<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015, Fuzhou Rockchip Electronics Co., Ltd
 */

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mailbox_controller.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा MAILBOX_A2B_INTEN		0x00
#घोषणा MAILBOX_A2B_STATUS		0x04
#घोषणा MAILBOX_A2B_CMD(x)		(0x08 + (x) * 8)
#घोषणा MAILBOX_A2B_DAT(x)		(0x0c + (x) * 8)

#घोषणा MAILBOX_B2A_INTEN		0x28
#घोषणा MAILBOX_B2A_STATUS		0x2C
#घोषणा MAILBOX_B2A_CMD(x)		(0x30 + (x) * 8)
#घोषणा MAILBOX_B2A_DAT(x)		(0x34 + (x) * 8)

काष्ठा rockchip_mbox_msg अणु
	u32 cmd;
	पूर्णांक rx_size;
पूर्ण;

काष्ठा rockchip_mbox_data अणु
	पूर्णांक num_chans;
पूर्ण;

काष्ठा rockchip_mbox_chan अणु
	पूर्णांक idx;
	पूर्णांक irq;
	काष्ठा rockchip_mbox_msg *msg;
	काष्ठा rockchip_mbox *mb;
पूर्ण;

काष्ठा rockchip_mbox अणु
	काष्ठा mbox_controller mbox;
	काष्ठा clk *pclk;
	व्योम __iomem *mbox_base;

	/* The maximum size of buf क्रम each channel */
	u32 buf_size;

	काष्ठा rockchip_mbox_chan *chans;
पूर्ण;

अटल पूर्णांक rockchip_mbox_send_data(काष्ठा mbox_chan *chan, व्योम *data)
अणु
	काष्ठा rockchip_mbox *mb = dev_get_drvdata(chan->mbox->dev);
	काष्ठा rockchip_mbox_msg *msg = data;
	काष्ठा rockchip_mbox_chan *chans = mb->chans;

	अगर (!msg)
		वापस -EINVAL;

	अगर (msg->rx_size > mb->buf_size) अणु
		dev_err(mb->mbox.dev, "Transmit size over buf size(%d)\n",
			mb->buf_size);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(mb->mbox.dev, "Chan[%d]: A2B message, cmd 0x%08x\n",
		chans->idx, msg->cmd);

	mb->chans[chans->idx].msg = msg;

	ग_लिखोl_relaxed(msg->cmd, mb->mbox_base + MAILBOX_A2B_CMD(chans->idx));
	ग_लिखोl_relaxed(msg->rx_size, mb->mbox_base +
		       MAILBOX_A2B_DAT(chans->idx));

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_mbox_startup(काष्ठा mbox_chan *chan)
अणु
	काष्ठा rockchip_mbox *mb = dev_get_drvdata(chan->mbox->dev);

	/* Enable all B2A पूर्णांकerrupts */
	ग_लिखोl_relaxed((1 << mb->mbox.num_chans) - 1,
		       mb->mbox_base + MAILBOX_B2A_INTEN);

	वापस 0;
पूर्ण

अटल व्योम rockchip_mbox_shutकरोwn(काष्ठा mbox_chan *chan)
अणु
	काष्ठा rockchip_mbox *mb = dev_get_drvdata(chan->mbox->dev);
	काष्ठा rockchip_mbox_chan *chans = mb->chans;

	/* Disable all B2A पूर्णांकerrupts */
	ग_लिखोl_relaxed(0, mb->mbox_base + MAILBOX_B2A_INTEN);

	mb->chans[chans->idx].msg = शून्य;
पूर्ण

अटल स्थिर काष्ठा mbox_chan_ops rockchip_mbox_chan_ops = अणु
	.send_data	= rockchip_mbox_send_data,
	.startup	= rockchip_mbox_startup,
	.shutकरोwn	= rockchip_mbox_shutकरोwn,
पूर्ण;

अटल irqवापस_t rockchip_mbox_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	पूर्णांक idx;
	काष्ठा rockchip_mbox *mb = (काष्ठा rockchip_mbox *)dev_id;
	u32 status = पढ़ोl_relaxed(mb->mbox_base + MAILBOX_B2A_STATUS);

	क्रम (idx = 0; idx < mb->mbox.num_chans; idx++) अणु
		अगर ((status & (1 << idx)) && (irq == mb->chans[idx].irq)) अणु
			/* Clear mbox पूर्णांकerrupt */
			ग_लिखोl_relaxed(1 << idx,
				       mb->mbox_base + MAILBOX_B2A_STATUS);
			वापस IRQ_WAKE_THREAD;
		पूर्ण
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल irqवापस_t rockchip_mbox_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	पूर्णांक idx;
	काष्ठा rockchip_mbox_msg *msg = शून्य;
	काष्ठा rockchip_mbox *mb = (काष्ठा rockchip_mbox *)dev_id;

	क्रम (idx = 0; idx < mb->mbox.num_chans; idx++) अणु
		अगर (irq != mb->chans[idx].irq)
			जारी;

		msg = mb->chans[idx].msg;
		अगर (!msg) अणु
			dev_err(mb->mbox.dev,
				"Chan[%d]: B2A message is NULL\n", idx);
			अवरोध; /* spurious */
		पूर्ण

		mbox_chan_received_data(&mb->mbox.chans[idx], msg);
		mb->chans[idx].msg = शून्य;

		dev_dbg(mb->mbox.dev, "Chan[%d]: B2A message, cmd 0x%08x\n",
			idx, msg->cmd);

		अवरोध;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा rockchip_mbox_data rk3368_drv_data = अणु
	.num_chans = 4,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rockchip_mbox_of_match[] = अणु
	अणु .compatible = "rockchip,rk3368-mailbox", .data = &rk3368_drv_dataपूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rockchp_mbox_of_match);

अटल पूर्णांक rockchip_mbox_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rockchip_mbox *mb;
	स्थिर काष्ठा of_device_id *match;
	स्थिर काष्ठा rockchip_mbox_data *drv_data;
	काष्ठा resource *res;
	पूर्णांक ret, irq, i;

	अगर (!pdev->dev.of_node)
		वापस -ENODEV;

	match = of_match_node(rockchip_mbox_of_match, pdev->dev.of_node);
	drv_data = (स्थिर काष्ठा rockchip_mbox_data *)match->data;

	mb = devm_kzalloc(&pdev->dev, माप(*mb), GFP_KERNEL);
	अगर (!mb)
		वापस -ENOMEM;

	mb->chans = devm_kसुस्मृति(&pdev->dev, drv_data->num_chans,
				 माप(*mb->chans), GFP_KERNEL);
	अगर (!mb->chans)
		वापस -ENOMEM;

	mb->mbox.chans = devm_kसुस्मृति(&pdev->dev, drv_data->num_chans,
				      माप(*mb->mbox.chans), GFP_KERNEL);
	अगर (!mb->mbox.chans)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, mb);

	mb->mbox.dev = &pdev->dev;
	mb->mbox.num_chans = drv_data->num_chans;
	mb->mbox.ops = &rockchip_mbox_chan_ops;
	mb->mbox.txकरोne_irq = true;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;

	mb->mbox_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(mb->mbox_base))
		वापस PTR_ERR(mb->mbox_base);

	/* Each channel has two buffers क्रम A2B and B2A */
	mb->buf_size = (माप_प्रकार)resource_size(res) / (drv_data->num_chans * 2);

	mb->pclk = devm_clk_get(&pdev->dev, "pclk_mailbox");
	अगर (IS_ERR(mb->pclk)) अणु
		ret = PTR_ERR(mb->pclk);
		dev_err(&pdev->dev, "failed to get pclk_mailbox clock: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(mb->pclk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to enable pclk: %d\n", ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < mb->mbox.num_chans; i++) अणु
		irq = platक्रमm_get_irq(pdev, i);
		अगर (irq < 0)
			वापस irq;

		ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq,
						rockchip_mbox_irq,
						rockchip_mbox_isr, IRQF_ONESHOT,
						dev_name(&pdev->dev), mb);
		अगर (ret < 0)
			वापस ret;

		mb->chans[i].idx = i;
		mb->chans[i].irq = irq;
		mb->chans[i].mb = mb;
		mb->chans[i].msg = शून्य;
	पूर्ण

	ret = devm_mbox_controller_रेजिस्टर(&pdev->dev, &mb->mbox);
	अगर (ret < 0)
		dev_err(&pdev->dev, "Failed to register mailbox: %d\n", ret);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver rockchip_mbox_driver = अणु
	.probe	= rockchip_mbox_probe,
	.driver = अणु
		.name = "rockchip-mailbox",
		.of_match_table = of_match_ptr(rockchip_mbox_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rockchip_mbox_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Rockchip mailbox: communicate between CPU cores and MCU");
MODULE_AUTHOR("Addy Ke <addy.ke@rock-chips.com>");
MODULE_AUTHOR("Caesar Wang <wxt@rock-chips.com>");
