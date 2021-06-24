<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2018-2020, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/mailbox_controller.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <dt-bindings/mailbox/qcom-ipcc.h>

#घोषणा IPCC_MBOX_MAX_CHAN		48

/* IPCC Register offsets */
#घोषणा IPCC_REG_SEND_ID		0x0c
#घोषणा IPCC_REG_RECV_ID		0x10
#घोषणा IPCC_REG_RECV_SIGNAL_ENABLE	0x14
#घोषणा IPCC_REG_RECV_SIGNAL_DISABLE	0x18
#घोषणा IPCC_REG_RECV_SIGNAL_CLEAR	0x1c
#घोषणा IPCC_REG_CLIENT_CLEAR		0x38

#घोषणा IPCC_SIGNAL_ID_MASK		GENMASK(15, 0)
#घोषणा IPCC_CLIENT_ID_MASK		GENMASK(31, 16)

#घोषणा IPCC_NO_PENDING_IRQ		GENMASK(31, 0)

/**
 * काष्ठा qcom_ipcc_chan_info - Per-mailbox-channel info
 * @client_id:	The client-id to which the पूर्णांकerrupt has to be triggered
 * @संकेत_id:	The संकेत-id to which the पूर्णांकerrupt has to be triggered
 */
काष्ठा qcom_ipcc_chan_info अणु
	u16 client_id;
	u16 संकेत_id;
पूर्ण;

/**
 * काष्ठा qcom_ipcc - Holder क्रम the mailbox driver
 * @dev:		Device associated with this instance
 * @base:		Base address of the IPCC frame associated to APSS
 * @irq_करोमुख्य:		The irq_करोमुख्य associated with this instance
 * @chan:		The mailbox channels array
 * @mchan:		The per-mailbox channel info array
 * @mbox:		The mailbox controller
 * @irq:		Summary irq
 */
काष्ठा qcom_ipcc अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	काष्ठा irq_करोमुख्य *irq_करोमुख्य;
	काष्ठा mbox_chan chan[IPCC_MBOX_MAX_CHAN];
	काष्ठा qcom_ipcc_chan_info mchan[IPCC_MBOX_MAX_CHAN];
	काष्ठा mbox_controller mbox;
	पूर्णांक irq;
पूर्ण;

अटल अंतरभूत काष्ठा qcom_ipcc *to_qcom_ipcc(काष्ठा mbox_controller *mbox)
अणु
	वापस container_of(mbox, काष्ठा qcom_ipcc, mbox);
पूर्ण

अटल अंतरभूत u32 qcom_ipcc_get_hwirq(u16 client_id, u16 संकेत_id)
अणु
	वापस FIELD_PREP(IPCC_CLIENT_ID_MASK, client_id) |
	       FIELD_PREP(IPCC_SIGNAL_ID_MASK, संकेत_id);
पूर्ण

अटल irqवापस_t qcom_ipcc_irq_fn(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा qcom_ipcc *ipcc = data;
	u32 hwirq;
	पूर्णांक virq;

	क्रम (;;) अणु
		hwirq = पढ़ोl(ipcc->base + IPCC_REG_RECV_ID);
		अगर (hwirq == IPCC_NO_PENDING_IRQ)
			अवरोध;

		virq = irq_find_mapping(ipcc->irq_करोमुख्य, hwirq);
		ग_लिखोl(hwirq, ipcc->base + IPCC_REG_RECV_SIGNAL_CLEAR);
		generic_handle_irq(virq);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम qcom_ipcc_mask_irq(काष्ठा irq_data *irqd)
अणु
	काष्ठा qcom_ipcc *ipcc = irq_data_get_irq_chip_data(irqd);
	irq_hw_number_t hwirq = irqd_to_hwirq(irqd);

	ग_लिखोl(hwirq, ipcc->base + IPCC_REG_RECV_SIGNAL_DISABLE);
पूर्ण

अटल व्योम qcom_ipcc_unmask_irq(काष्ठा irq_data *irqd)
अणु
	काष्ठा qcom_ipcc *ipcc = irq_data_get_irq_chip_data(irqd);
	irq_hw_number_t hwirq = irqd_to_hwirq(irqd);

	ग_लिखोl(hwirq, ipcc->base + IPCC_REG_RECV_SIGNAL_ENABLE);
पूर्ण

अटल काष्ठा irq_chip qcom_ipcc_irq_chip = अणु
	.name = "ipcc",
	.irq_mask = qcom_ipcc_mask_irq,
	.irq_unmask = qcom_ipcc_unmask_irq,
	.flags = IRQCHIP_SKIP_SET_WAKE,
पूर्ण;

अटल पूर्णांक qcom_ipcc_करोमुख्य_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
				irq_hw_number_t hw)
अणु
	काष्ठा qcom_ipcc *ipcc = d->host_data;

	irq_set_chip_and_handler(irq, &qcom_ipcc_irq_chip, handle_level_irq);
	irq_set_chip_data(irq, ipcc);
	irq_set_noprobe(irq);

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_ipcc_करोमुख्य_xlate(काष्ठा irq_करोमुख्य *d,
				  काष्ठा device_node *node, स्थिर u32 *पूर्णांकspec,
				  अचिन्हित पूर्णांक पूर्णांकsize,
				  अचिन्हित दीर्घ *out_hwirq,
				  अचिन्हित पूर्णांक *out_type)
अणु
	अगर (पूर्णांकsize != 3)
		वापस -EINVAL;

	*out_hwirq = qcom_ipcc_get_hwirq(पूर्णांकspec[0], पूर्णांकspec[1]);
	*out_type = पूर्णांकspec[2] & IRQ_TYPE_SENSE_MASK;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops qcom_ipcc_irq_ops = अणु
	.map = qcom_ipcc_करोमुख्य_map,
	.xlate = qcom_ipcc_करोमुख्य_xlate,
पूर्ण;

अटल पूर्णांक qcom_ipcc_mbox_send_data(काष्ठा mbox_chan *chan, व्योम *data)
अणु
	काष्ठा qcom_ipcc *ipcc = to_qcom_ipcc(chan->mbox);
	काष्ठा qcom_ipcc_chan_info *mchan = chan->con_priv;
	u32 hwirq;

	hwirq = qcom_ipcc_get_hwirq(mchan->client_id, mchan->संकेत_id);
	ग_लिखोl(hwirq, ipcc->base + IPCC_REG_SEND_ID);

	वापस 0;
पूर्ण

अटल काष्ठा mbox_chan *qcom_ipcc_mbox_xlate(काष्ठा mbox_controller *mbox,
					स्थिर काष्ठा of_phandle_args *ph)
अणु
	काष्ठा qcom_ipcc *ipcc = to_qcom_ipcc(mbox);
	काष्ठा qcom_ipcc_chan_info *mchan;
	काष्ठा mbox_chan *chan;
	अचिन्हित पूर्णांक i;

	अगर (ph->args_count != 2)
		वापस ERR_PTR(-EINVAL);

	क्रम (i = 0; i < IPCC_MBOX_MAX_CHAN; i++) अणु
		chan = &ipcc->chan[i];
		अगर (!chan->con_priv) अणु
			mchan = &ipcc->mchan[i];
			mchan->client_id = ph->args[0];
			mchan->संकेत_id = ph->args[1];
			chan->con_priv = mchan;
			अवरोध;
		पूर्ण

		chan = शून्य;
	पूर्ण

	वापस chan ?: ERR_PTR(-EBUSY);
पूर्ण

अटल स्थिर काष्ठा mbox_chan_ops ipcc_mbox_chan_ops = अणु
	.send_data = qcom_ipcc_mbox_send_data,
पूर्ण;

अटल पूर्णांक qcom_ipcc_setup_mbox(काष्ठा qcom_ipcc *ipcc)
अणु
	काष्ठा mbox_controller *mbox;
	काष्ठा device *dev = ipcc->dev;

	mbox = &ipcc->mbox;
	mbox->dev = dev;
	mbox->num_chans = IPCC_MBOX_MAX_CHAN;
	mbox->chans = ipcc->chan;
	mbox->ops = &ipcc_mbox_chan_ops;
	mbox->of_xlate = qcom_ipcc_mbox_xlate;
	mbox->txकरोne_irq = false;
	mbox->txकरोne_poll = false;

	वापस devm_mbox_controller_रेजिस्टर(dev, mbox);
पूर्ण

अटल पूर्णांक qcom_ipcc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_ipcc *ipcc;
	पूर्णांक ret;

	ipcc = devm_kzalloc(&pdev->dev, माप(*ipcc), GFP_KERNEL);
	अगर (!ipcc)
		वापस -ENOMEM;

	ipcc->dev = &pdev->dev;

	ipcc->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ipcc->base))
		वापस PTR_ERR(ipcc->base);

	ipcc->irq = platक्रमm_get_irq(pdev, 0);
	अगर (ipcc->irq < 0)
		वापस ipcc->irq;

	ipcc->irq_करोमुख्य = irq_करोमुख्य_add_tree(pdev->dev.of_node,
					       &qcom_ipcc_irq_ops, ipcc);
	अगर (!ipcc->irq_करोमुख्य)
		वापस -ENOMEM;

	ret = qcom_ipcc_setup_mbox(ipcc);
	अगर (ret)
		जाओ err_mbox;

	ret = devm_request_irq(&pdev->dev, ipcc->irq, qcom_ipcc_irq_fn,
			       IRQF_TRIGGER_HIGH, "ipcc", ipcc);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to register the irq: %d\n", ret);
		जाओ err_mbox;
	पूर्ण

	enable_irq_wake(ipcc->irq);
	platक्रमm_set_drvdata(pdev, ipcc);

	वापस 0;

err_mbox:
	irq_करोमुख्य_हटाओ(ipcc->irq_करोमुख्य);

	वापस ret;
पूर्ण

अटल पूर्णांक qcom_ipcc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_ipcc *ipcc = platक्रमm_get_drvdata(pdev);

	disable_irq_wake(ipcc->irq);
	irq_करोमुख्य_हटाओ(ipcc->irq_करोमुख्य);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id qcom_ipcc_of_match[] = अणु
	अणु .compatible = "qcom,ipcc"पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_ipcc_of_match);

अटल काष्ठा platक्रमm_driver qcom_ipcc_driver = अणु
	.probe = qcom_ipcc_probe,
	.हटाओ = qcom_ipcc_हटाओ,
	.driver = अणु
		.name = "qcom-ipcc",
		.of_match_table = qcom_ipcc_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init qcom_ipcc_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&qcom_ipcc_driver);
पूर्ण
arch_initcall(qcom_ipcc_init);

MODULE_AUTHOR("Venkata Narendra Kumar Gutta <vnkgutta@codeaurora.org>");
MODULE_AUTHOR("Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>");
MODULE_DESCRIPTION("Qualcomm Technologies, Inc. IPCC driver");
MODULE_LICENSE("GPL v2");
