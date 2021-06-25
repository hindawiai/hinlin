<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018, NVIDIA CORPORATION.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <soc/tegra/bpmp.h>

#समावेश "bpmp-private.h"

#घोषणा TRIGGER_OFFSET		0x000
#घोषणा RESULT_OFFSET(id)	(0xc00 + id * 4)
#घोषणा TRIGGER_ID_SHIFT	16
#घोषणा TRIGGER_CMD_GET		4

#घोषणा STA_OFFSET		0
#घोषणा SET_OFFSET		4
#घोषणा CLR_OFFSET		8

#घोषणा CH_MASK(ch)	(0x3 << ((ch) * 2))
#घोषणा SL_SIGL(ch)	(0x0 << ((ch) * 2))
#घोषणा SL_QUED(ch)	(0x1 << ((ch) * 2))
#घोषणा MA_FREE(ch)	(0x2 << ((ch) * 2))
#घोषणा MA_ACKD(ch)	(0x3 << ((ch) * 2))

काष्ठा tegra210_bpmp अणु
	व्योम __iomem *atomics;
	व्योम __iomem *arb_sema;
	काष्ठा irq_data *tx_irq_data;
पूर्ण;

अटल u32 bpmp_channel_status(काष्ठा tegra_bpmp *bpmp, अचिन्हित पूर्णांक index)
अणु
	काष्ठा tegra210_bpmp *priv = bpmp->priv;

	वापस __raw_पढ़ोl(priv->arb_sema + STA_OFFSET) & CH_MASK(index);
पूर्ण

अटल bool tegra210_bpmp_is_response_पढ़ोy(काष्ठा tegra_bpmp_channel *channel)
अणु
	अचिन्हित पूर्णांक index = channel->index;

	वापस bpmp_channel_status(channel->bpmp, index) == MA_ACKD(index);
पूर्ण

अटल bool tegra210_bpmp_is_request_पढ़ोy(काष्ठा tegra_bpmp_channel *channel)
अणु
	अचिन्हित पूर्णांक index = channel->index;

	वापस bpmp_channel_status(channel->bpmp, index) == SL_SIGL(index);
पूर्ण

अटल bool
tegra210_bpmp_is_request_channel_मुक्त(काष्ठा tegra_bpmp_channel *channel)
अणु
	अचिन्हित पूर्णांक index = channel->index;

	वापस bpmp_channel_status(channel->bpmp, index) == MA_FREE(index);
पूर्ण

अटल bool
tegra210_bpmp_is_response_channel_मुक्त(काष्ठा tegra_bpmp_channel *channel)
अणु
	अचिन्हित पूर्णांक index = channel->index;

	वापस bpmp_channel_status(channel->bpmp, index) == SL_QUED(index);
पूर्ण

अटल पूर्णांक tegra210_bpmp_post_request(काष्ठा tegra_bpmp_channel *channel)
अणु
	काष्ठा tegra210_bpmp *priv = channel->bpmp->priv;

	__raw_ग_लिखोl(CH_MASK(channel->index), priv->arb_sema + CLR_OFFSET);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra210_bpmp_post_response(काष्ठा tegra_bpmp_channel *channel)
अणु
	काष्ठा tegra210_bpmp *priv = channel->bpmp->priv;

	__raw_ग_लिखोl(MA_ACKD(channel->index), priv->arb_sema + SET_OFFSET);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra210_bpmp_ack_response(काष्ठा tegra_bpmp_channel *channel)
अणु
	काष्ठा tegra210_bpmp *priv = channel->bpmp->priv;

	__raw_ग_लिखोl(MA_ACKD(channel->index) ^ MA_FREE(channel->index),
		     priv->arb_sema + CLR_OFFSET);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra210_bpmp_ack_request(काष्ठा tegra_bpmp_channel *channel)
अणु
	काष्ठा tegra210_bpmp *priv = channel->bpmp->priv;

	__raw_ग_लिखोl(SL_QUED(channel->index), priv->arb_sema + SET_OFFSET);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra210_bpmp_ring_करोorbell(काष्ठा tegra_bpmp *bpmp)
अणु
	काष्ठा tegra210_bpmp *priv = bpmp->priv;
	काष्ठा irq_data *irq_data = priv->tx_irq_data;

	/*
	 * Tegra Legacy Interrupt Controller (LIC) is used to notअगरy BPMP of
	 * available messages
	 */
	अगर (irq_data->chip->irq_retrigger)
		वापस irq_data->chip->irq_retrigger(irq_data);

	वापस -EINVAL;
पूर्ण

अटल irqवापस_t rx_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा tegra_bpmp *bpmp = data;

	tegra_bpmp_handle_rx(bpmp);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक tegra210_bpmp_channel_init(काष्ठा tegra_bpmp_channel *channel,
				      काष्ठा tegra_bpmp *bpmp,
				      अचिन्हित पूर्णांक index)
अणु
	काष्ठा tegra210_bpmp *priv = bpmp->priv;
	u32 address;
	व्योम *p;

	/* Retrieve channel base address from BPMP */
	ग_लिखोl(index << TRIGGER_ID_SHIFT | TRIGGER_CMD_GET,
	       priv->atomics + TRIGGER_OFFSET);
	address = पढ़ोl(priv->atomics + RESULT_OFFSET(index));

	p = devm_ioremap(bpmp->dev, address, 0x80);
	अगर (!p)
		वापस -ENOMEM;

	channel->ib = p;
	channel->ob = p;
	channel->index = index;
	init_completion(&channel->completion);
	channel->bpmp = bpmp;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra210_bpmp_init(काष्ठा tegra_bpmp *bpmp)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(bpmp->dev);
	काष्ठा tegra210_bpmp *priv;
	काष्ठा resource *res;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	bpmp->priv = priv;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->atomics = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(priv->atomics))
		वापस PTR_ERR(priv->atomics);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	priv->arb_sema = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(priv->arb_sema))
		वापस PTR_ERR(priv->arb_sema);

	err = tegra210_bpmp_channel_init(bpmp->tx_channel, bpmp,
					 bpmp->soc->channels.cpu_tx.offset);
	अगर (err < 0)
		वापस err;

	err = tegra210_bpmp_channel_init(bpmp->rx_channel, bpmp,
					 bpmp->soc->channels.cpu_rx.offset);
	अगर (err < 0)
		वापस err;

	क्रम (i = 0; i < bpmp->thपढ़ोed.count; i++) अणु
		अचिन्हित पूर्णांक index = bpmp->soc->channels.thपढ़ो.offset + i;

		err = tegra210_bpmp_channel_init(&bpmp->thपढ़ोed_channels[i],
						 bpmp, index);
		अगर (err < 0)
			वापस err;
	पूर्ण

	err = platक्रमm_get_irq_byname(pdev, "tx");
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to get TX IRQ: %d\n", err);
		वापस err;
	पूर्ण

	priv->tx_irq_data = irq_get_irq_data(err);
	अगर (!priv->tx_irq_data) अणु
		dev_err(&pdev->dev, "failed to get IRQ data for TX IRQ\n");
		वापस err;
	पूर्ण

	err = platक्रमm_get_irq_byname(pdev, "rx");
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to get rx IRQ: %d\n", err);
		वापस err;
	पूर्ण

	err = devm_request_irq(&pdev->dev, err, rx_irq,
			       IRQF_NO_SUSPEND, dev_name(&pdev->dev), bpmp);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to request IRQ: %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

स्थिर काष्ठा tegra_bpmp_ops tegra210_bpmp_ops = अणु
	.init = tegra210_bpmp_init,
	.is_response_पढ़ोy = tegra210_bpmp_is_response_पढ़ोy,
	.is_request_पढ़ोy = tegra210_bpmp_is_request_पढ़ोy,
	.ack_response = tegra210_bpmp_ack_response,
	.ack_request = tegra210_bpmp_ack_request,
	.is_response_channel_मुक्त = tegra210_bpmp_is_response_channel_मुक्त,
	.is_request_channel_मुक्त = tegra210_bpmp_is_request_channel_मुक्त,
	.post_response = tegra210_bpmp_post_response,
	.post_request = tegra210_bpmp_post_request,
	.ring_करोorbell = tegra210_bpmp_ring_करोorbell,
पूर्ण;
