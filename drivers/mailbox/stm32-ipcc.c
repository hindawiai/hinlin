<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics 2018 - All Rights Reserved
 * Authors: Luकरोvic Barre <luकरोvic.barre@st.com> क्रम STMicroelectronics.
 *          Fabien Dessenne <fabien.dessenne@st.com> क्रम STMicroelectronics.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/mailbox_controller.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_wakeirq.h>

#घोषणा IPCC_XCR		0x000
#घोषणा XCR_RXOIE		BIT(0)
#घोषणा XCR_TXOIE		BIT(16)

#घोषणा IPCC_XMR		0x004
#घोषणा IPCC_XSCR		0x008
#घोषणा IPCC_XTOYSR		0x00c

#घोषणा IPCC_PROC_OFFST		0x010

#घोषणा IPCC_HWCFGR		0x3f0
#घोषणा IPCFGR_CHAN_MASK	GENMASK(7, 0)

#घोषणा IPCC_VER		0x3f4
#घोषणा VER_MINREV_MASK		GENMASK(3, 0)
#घोषणा VER_MAJREV_MASK		GENMASK(7, 4)

#घोषणा RX_BIT_MASK		GENMASK(15, 0)
#घोषणा RX_BIT_CHAN(chan)	BIT(chan)
#घोषणा TX_BIT_SHIFT		16
#घोषणा TX_BIT_MASK		GENMASK(31, 16)
#घोषणा TX_BIT_CHAN(chan)	BIT(TX_BIT_SHIFT + (chan))

#घोषणा STM32_MAX_PROCS		2

क्रमागत अणु
	IPCC_IRQ_RX,
	IPCC_IRQ_TX,
	IPCC_IRQ_NUM,
पूर्ण;

काष्ठा sपंचांग32_ipcc अणु
	काष्ठा mbox_controller controller;
	व्योम __iomem *reg_base;
	व्योम __iomem *reg_proc;
	काष्ठा clk *clk;
	spinlock_t lock; /* protect access to IPCC रेजिस्टरs */
	पूर्णांक irqs[IPCC_IRQ_NUM];
	u32 proc_id;
	u32 n_chans;
	u32 xcr;
	u32 xmr;
पूर्ण;

अटल अंतरभूत व्योम sपंचांग32_ipcc_set_bits(spinlock_t *lock, व्योम __iomem *reg,
				       u32 mask)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(lock, flags);
	ग_लिखोl_relaxed(पढ़ोl_relaxed(reg) | mask, reg);
	spin_unlock_irqrestore(lock, flags);
पूर्ण

अटल अंतरभूत व्योम sपंचांग32_ipcc_clr_bits(spinlock_t *lock, व्योम __iomem *reg,
				       u32 mask)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(lock, flags);
	ग_लिखोl_relaxed(पढ़ोl_relaxed(reg) & ~mask, reg);
	spin_unlock_irqrestore(lock, flags);
पूर्ण

अटल irqवापस_t sपंचांग32_ipcc_rx_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा sपंचांग32_ipcc *ipcc = data;
	काष्ठा device *dev = ipcc->controller.dev;
	u32 status, mr, tosr, chan;
	irqवापस_t ret = IRQ_NONE;
	पूर्णांक proc_offset;

	/* पढ़ो 'channel occupied' status from other proc */
	proc_offset = ipcc->proc_id ? -IPCC_PROC_OFFST : IPCC_PROC_OFFST;
	tosr = पढ़ोl_relaxed(ipcc->reg_proc + proc_offset + IPCC_XTOYSR);
	mr = पढ़ोl_relaxed(ipcc->reg_proc + IPCC_XMR);

	/* search क्रम unmasked 'channel occupied' */
	status = tosr & FIELD_GET(RX_BIT_MASK, ~mr);

	क्रम (chan = 0; chan < ipcc->n_chans; chan++) अणु
		अगर (!(status & (1 << chan)))
			जारी;

		dev_dbg(dev, "%s: chan:%d rx\n", __func__, chan);

		mbox_chan_received_data(&ipcc->controller.chans[chan], शून्य);

		sपंचांग32_ipcc_set_bits(&ipcc->lock, ipcc->reg_proc + IPCC_XSCR,
				    RX_BIT_CHAN(chan));

		ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;
पूर्ण

अटल irqवापस_t sपंचांग32_ipcc_tx_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा sपंचांग32_ipcc *ipcc = data;
	काष्ठा device *dev = ipcc->controller.dev;
	u32 status, mr, tosr, chan;
	irqवापस_t ret = IRQ_NONE;

	tosr = पढ़ोl_relaxed(ipcc->reg_proc + IPCC_XTOYSR);
	mr = पढ़ोl_relaxed(ipcc->reg_proc + IPCC_XMR);

	/* search क्रम unmasked 'channel free' */
	status = ~tosr & FIELD_GET(TX_BIT_MASK, ~mr);

	क्रम (chan = 0; chan < ipcc->n_chans ; chan++) अणु
		अगर (!(status & (1 << chan)))
			जारी;

		dev_dbg(dev, "%s: chan:%d tx\n", __func__, chan);

		/* mask 'tx channel free' पूर्णांकerrupt */
		sपंचांग32_ipcc_set_bits(&ipcc->lock, ipcc->reg_proc + IPCC_XMR,
				    TX_BIT_CHAN(chan));

		mbox_chan_txकरोne(&ipcc->controller.chans[chan], 0);

		ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_ipcc_send_data(काष्ठा mbox_chan *link, व्योम *data)
अणु
	अचिन्हित दीर्घ chan = (अचिन्हित दीर्घ)link->con_priv;
	काष्ठा sपंचांग32_ipcc *ipcc = container_of(link->mbox, काष्ठा sपंचांग32_ipcc,
					       controller);

	dev_dbg(ipcc->controller.dev, "%s: chan:%lu\n", __func__, chan);

	/* set channel n occupied */
	sपंचांग32_ipcc_set_bits(&ipcc->lock, ipcc->reg_proc + IPCC_XSCR,
			    TX_BIT_CHAN(chan));

	/* unmask 'tx channel free' पूर्णांकerrupt */
	sपंचांग32_ipcc_clr_bits(&ipcc->lock, ipcc->reg_proc + IPCC_XMR,
			    TX_BIT_CHAN(chan));

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_ipcc_startup(काष्ठा mbox_chan *link)
अणु
	अचिन्हित दीर्घ chan = (अचिन्हित दीर्घ)link->con_priv;
	काष्ठा sपंचांग32_ipcc *ipcc = container_of(link->mbox, काष्ठा sपंचांग32_ipcc,
					       controller);
	पूर्णांक ret;

	ret = clk_prepare_enable(ipcc->clk);
	अगर (ret) अणु
		dev_err(ipcc->controller.dev, "can not enable the clock\n");
		वापस ret;
	पूर्ण

	/* unmask 'rx channel occupied' पूर्णांकerrupt */
	sपंचांग32_ipcc_clr_bits(&ipcc->lock, ipcc->reg_proc + IPCC_XMR,
			    RX_BIT_CHAN(chan));

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32_ipcc_shutकरोwn(काष्ठा mbox_chan *link)
अणु
	अचिन्हित दीर्घ chan = (अचिन्हित दीर्घ)link->con_priv;
	काष्ठा sपंचांग32_ipcc *ipcc = container_of(link->mbox, काष्ठा sपंचांग32_ipcc,
					       controller);

	/* mask rx/tx पूर्णांकerrupt */
	sपंचांग32_ipcc_set_bits(&ipcc->lock, ipcc->reg_proc + IPCC_XMR,
			    RX_BIT_CHAN(chan) | TX_BIT_CHAN(chan));

	clk_disable_unprepare(ipcc->clk);
पूर्ण

अटल स्थिर काष्ठा mbox_chan_ops sपंचांग32_ipcc_ops = अणु
	.send_data	= sपंचांग32_ipcc_send_data,
	.startup	= sपंचांग32_ipcc_startup,
	.shutकरोwn	= sपंचांग32_ipcc_shutकरोwn,
पूर्ण;

अटल पूर्णांक sपंचांग32_ipcc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा sपंचांग32_ipcc *ipcc;
	काष्ठा resource *res;
	अचिन्हित दीर्घ i;
	पूर्णांक ret;
	u32 ip_ver;
	अटल स्थिर अक्षर * स्थिर irq_name[] = अणु"rx", "tx"पूर्ण;
	irq_handler_t irq_thपढ़ो[] = अणुsपंचांग32_ipcc_rx_irq, sपंचांग32_ipcc_tx_irqपूर्ण;

	अगर (!np) अणु
		dev_err(dev, "No DT found\n");
		वापस -ENODEV;
	पूर्ण

	ipcc = devm_kzalloc(dev, माप(*ipcc), GFP_KERNEL);
	अगर (!ipcc)
		वापस -ENOMEM;

	spin_lock_init(&ipcc->lock);

	/* proc_id */
	अगर (of_property_पढ़ो_u32(np, "st,proc-id", &ipcc->proc_id)) अणु
		dev_err(dev, "Missing st,proc-id\n");
		वापस -ENODEV;
	पूर्ण

	अगर (ipcc->proc_id >= STM32_MAX_PROCS) अणु
		dev_err(dev, "Invalid proc_id (%d)\n", ipcc->proc_id);
		वापस -EINVAL;
	पूर्ण

	/* regs */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ipcc->reg_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(ipcc->reg_base))
		वापस PTR_ERR(ipcc->reg_base);

	ipcc->reg_proc = ipcc->reg_base + ipcc->proc_id * IPCC_PROC_OFFST;

	/* घड़ी */
	ipcc->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(ipcc->clk))
		वापस PTR_ERR(ipcc->clk);

	ret = clk_prepare_enable(ipcc->clk);
	अगर (ret) अणु
		dev_err(dev, "can not enable the clock\n");
		वापस ret;
	पूर्ण

	/* irq */
	क्रम (i = 0; i < IPCC_IRQ_NUM; i++) अणु
		ipcc->irqs[i] = platक्रमm_get_irq_byname(pdev, irq_name[i]);
		अगर (ipcc->irqs[i] < 0) अणु
			ret = ipcc->irqs[i];
			जाओ err_clk;
		पूर्ण

		ret = devm_request_thपढ़ोed_irq(dev, ipcc->irqs[i], शून्य,
						irq_thपढ़ो[i], IRQF_ONESHOT,
						dev_name(dev), ipcc);
		अगर (ret) अणु
			dev_err(dev, "failed to request irq %lu (%d)\n", i, ret);
			जाओ err_clk;
		पूर्ण
	पूर्ण

	/* mask and enable rx/tx irq */
	sपंचांग32_ipcc_set_bits(&ipcc->lock, ipcc->reg_proc + IPCC_XMR,
			    RX_BIT_MASK | TX_BIT_MASK);
	sपंचांग32_ipcc_set_bits(&ipcc->lock, ipcc->reg_proc + IPCC_XCR,
			    XCR_RXOIE | XCR_TXOIE);

	/* wakeup */
	अगर (of_property_पढ़ो_bool(np, "wakeup-source")) अणु
		device_set_wakeup_capable(dev, true);

		ret = dev_pm_set_wake_irq(dev, ipcc->irqs[IPCC_IRQ_RX]);
		अगर (ret) अणु
			dev_err(dev, "Failed to set wake up irq\n");
			जाओ err_init_wkp;
		पूर्ण
	पूर्ण

	/* mailbox controller */
	ipcc->n_chans = पढ़ोl_relaxed(ipcc->reg_base + IPCC_HWCFGR);
	ipcc->n_chans &= IPCFGR_CHAN_MASK;

	ipcc->controller.dev = dev;
	ipcc->controller.txकरोne_irq = true;
	ipcc->controller.ops = &sपंचांग32_ipcc_ops;
	ipcc->controller.num_chans = ipcc->n_chans;
	ipcc->controller.chans = devm_kसुस्मृति(dev, ipcc->controller.num_chans,
					      माप(*ipcc->controller.chans),
					      GFP_KERNEL);
	अगर (!ipcc->controller.chans) अणु
		ret = -ENOMEM;
		जाओ err_irq_wkp;
	पूर्ण

	क्रम (i = 0; i < ipcc->controller.num_chans; i++)
		ipcc->controller.chans[i].con_priv = (व्योम *)i;

	ret = devm_mbox_controller_रेजिस्टर(dev, &ipcc->controller);
	अगर (ret)
		जाओ err_irq_wkp;

	platक्रमm_set_drvdata(pdev, ipcc);

	ip_ver = पढ़ोl_relaxed(ipcc->reg_base + IPCC_VER);

	dev_info(dev, "ipcc rev:%ld.%ld enabled, %d chans, proc %d\n",
		 FIELD_GET(VER_MAJREV_MASK, ip_ver),
		 FIELD_GET(VER_MINREV_MASK, ip_ver),
		 ipcc->controller.num_chans, ipcc->proc_id);

	clk_disable_unprepare(ipcc->clk);
	वापस 0;

err_irq_wkp:
	अगर (of_property_पढ़ो_bool(np, "wakeup-source"))
		dev_pm_clear_wake_irq(dev);
err_init_wkp:
	device_set_wakeup_capable(dev, false);
err_clk:
	clk_disable_unprepare(ipcc->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_ipcc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;

	अगर (of_property_पढ़ो_bool(dev->of_node, "wakeup-source"))
		dev_pm_clear_wake_irq(&pdev->dev);

	device_set_wakeup_capable(dev, false);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sपंचांग32_ipcc_suspend(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_ipcc *ipcc = dev_get_drvdata(dev);

	ipcc->xmr = पढ़ोl_relaxed(ipcc->reg_proc + IPCC_XMR);
	ipcc->xcr = पढ़ोl_relaxed(ipcc->reg_proc + IPCC_XCR);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_ipcc_resume(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_ipcc *ipcc = dev_get_drvdata(dev);

	ग_लिखोl_relaxed(ipcc->xmr, ipcc->reg_proc + IPCC_XMR);
	ग_लिखोl_relaxed(ipcc->xcr, ipcc->reg_proc + IPCC_XCR);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(sपंचांग32_ipcc_pm_ops,
			 sपंचांग32_ipcc_suspend, sपंचांग32_ipcc_resume);

अटल स्थिर काष्ठा of_device_id sपंचांग32_ipcc_of_match[] = अणु
	अणु .compatible = "st,stm32mp1-ipcc" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_ipcc_of_match);

अटल काष्ठा platक्रमm_driver sपंचांग32_ipcc_driver = अणु
	.driver = अणु
		.name = "stm32-ipcc",
		.pm = &sपंचांग32_ipcc_pm_ops,
		.of_match_table = sपंचांग32_ipcc_of_match,
	पूर्ण,
	.probe		= sपंचांग32_ipcc_probe,
	.हटाओ		= sपंचांग32_ipcc_हटाओ,
पूर्ण;

module_platक्रमm_driver(sपंचांग32_ipcc_driver);

MODULE_AUTHOR("Ludovic Barre <ludovic.barre@st.com>");
MODULE_AUTHOR("Fabien Dessenne <fabien.dessenne@st.com>");
MODULE_DESCRIPTION("STM32 IPCC driver");
MODULE_LICENSE("GPL v2");
