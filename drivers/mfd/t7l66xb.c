<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Toshiba T7L66XB core mfd support
 *
 * Copyright (c) 2005, 2007, 2008 Ian Molton
 * Copyright (c) 2008 Dmitry Baryshkov
 *
 * T7L66 features:
 *
 * Supported in this driver:
 * SD/MMC
 * SM/न_अंकD flash controller
 *
 * As yet not supported
 * GPIO पूर्णांकerface (on न_अंकD pins)
 * Serial पूर्णांकerface
 * TFT 'interface converter'
 * PCMCIA पूर्णांकerface logic
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/irq.h>
#समावेश <linux/clk.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/पंचांगपन.स>
#समावेश <linux/mfd/t7l66xb.h>

क्रमागत अणु
	T7L66XB_CELL_न_अंकD,
	T7L66XB_CELL_MMC,
पूर्ण;

अटल स्थिर काष्ठा resource t7l66xb_mmc_resources[] = अणु
	अणु
		.start = 0x800,
		.end	= 0x9ff,
		.flags = IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start = IRQ_T7L66XB_MMC,
		.end	= IRQ_T7L66XB_MMC,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

#घोषणा SCR_REVID	0x08		/* b Revision ID	*/
#घोषणा SCR_IMR		0x42		/* b Interrupt Mask	*/
#घोषणा SCR_DEV_CTL	0xe0		/* b Device control	*/
#घोषणा SCR_ISR		0xe1		/* b Interrupt Status	*/
#घोषणा SCR_GPO_OC	0xf0		/* b GPO output control	*/
#घोषणा SCR_GPO_OS	0xf1		/* b GPO output enable	*/
#घोषणा SCR_GPI_S	0xf2		/* w GPI status		*/
#घोषणा SCR_APDC	0xf8		/* b Active pullup करोwn ctrl */

#घोषणा SCR_DEV_CTL_USB		BIT(0)	/* USB enable		*/
#घोषणा SCR_DEV_CTL_MMC		BIT(1)	/* MMC enable		*/

/*--------------------------------------------------------------------------*/

काष्ठा t7l66xb अणु
	व्योम __iomem		*scr;
	/* Lock to protect रेजिस्टरs requiring पढ़ो/modअगरy/ग_लिखो ops. */
	raw_spinlock_t		lock;

	काष्ठा resource		rscr;
	काष्ठा clk		*clk48m;
	काष्ठा clk		*clk32k;
	पूर्णांक			irq;
	पूर्णांक			irq_base;
पूर्ण;

/*--------------------------------------------------------------------------*/

अटल पूर्णांक t7l66xb_mmc_enable(काष्ठा platक्रमm_device *mmc)
अणु
	काष्ठा t7l66xb *t7l66xb = dev_get_drvdata(mmc->dev.parent);
	अचिन्हित दीर्घ flags;
	u8 dev_ctl;
	पूर्णांक ret;

	ret = clk_prepare_enable(t7l66xb->clk32k);
	अगर (ret)
		वापस ret;

	raw_spin_lock_irqsave(&t7l66xb->lock, flags);

	dev_ctl = पंचांगio_ioपढ़ो8(t7l66xb->scr + SCR_DEV_CTL);
	dev_ctl |= SCR_DEV_CTL_MMC;
	पंचांगio_ioग_लिखो8(dev_ctl, t7l66xb->scr + SCR_DEV_CTL);

	raw_spin_unlock_irqrestore(&t7l66xb->lock, flags);

	पंचांगio_core_mmc_enable(t7l66xb->scr + 0x200, 0,
		t7l66xb_mmc_resources[0].start & 0xfffe);

	वापस 0;
पूर्ण

अटल पूर्णांक t7l66xb_mmc_disable(काष्ठा platक्रमm_device *mmc)
अणु
	काष्ठा t7l66xb *t7l66xb = dev_get_drvdata(mmc->dev.parent);
	अचिन्हित दीर्घ flags;
	u8 dev_ctl;

	raw_spin_lock_irqsave(&t7l66xb->lock, flags);

	dev_ctl = पंचांगio_ioपढ़ो8(t7l66xb->scr + SCR_DEV_CTL);
	dev_ctl &= ~SCR_DEV_CTL_MMC;
	पंचांगio_ioग_लिखो8(dev_ctl, t7l66xb->scr + SCR_DEV_CTL);

	raw_spin_unlock_irqrestore(&t7l66xb->lock, flags);

	clk_disable_unprepare(t7l66xb->clk32k);

	वापस 0;
पूर्ण

अटल व्योम t7l66xb_mmc_pwr(काष्ठा platक्रमm_device *mmc, पूर्णांक state)
अणु
	काष्ठा t7l66xb *t7l66xb = dev_get_drvdata(mmc->dev.parent);

	पंचांगio_core_mmc_pwr(t7l66xb->scr + 0x200, 0, state);
पूर्ण

अटल व्योम t7l66xb_mmc_clk_भाग(काष्ठा platक्रमm_device *mmc, पूर्णांक state)
अणु
	काष्ठा t7l66xb *t7l66xb = dev_get_drvdata(mmc->dev.parent);

	पंचांगio_core_mmc_clk_भाग(t7l66xb->scr + 0x200, 0, state);
पूर्ण

/*--------------------------------------------------------------------------*/

अटल काष्ठा पंचांगio_mmc_data t7166xb_mmc_data = अणु
	.hclk = 24000000,
	.set_pwr = t7l66xb_mmc_pwr,
	.set_clk_भाग = t7l66xb_mmc_clk_भाग,
पूर्ण;

अटल स्थिर काष्ठा resource t7l66xb_nand_resources[] = अणु
	अणु
		.start	= 0xc00,
		.end	= 0xc07,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= 0x0100,
		.end	= 0x01ff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= IRQ_T7L66XB_न_अंकD,
		.end	= IRQ_T7L66XB_न_अंकD,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा mfd_cell t7l66xb_cells[] = अणु
	[T7L66XB_CELL_MMC] = अणु
		.name = "tmio-mmc",
		.enable = t7l66xb_mmc_enable,
		.disable = t7l66xb_mmc_disable,
		.platक्रमm_data = &t7166xb_mmc_data,
		.pdata_size    = माप(t7166xb_mmc_data),
		.num_resources = ARRAY_SIZE(t7l66xb_mmc_resources),
		.resources = t7l66xb_mmc_resources,
	पूर्ण,
	[T7L66XB_CELL_न_अंकD] = अणु
		.name = "tmio-nand",
		.num_resources = ARRAY_SIZE(t7l66xb_nand_resources),
		.resources = t7l66xb_nand_resources,
	पूर्ण,
पूर्ण;

/*--------------------------------------------------------------------------*/

/* Handle the T7L66XB पूर्णांकerrupt mux */
अटल व्योम t7l66xb_irq(काष्ठा irq_desc *desc)
अणु
	काष्ठा t7l66xb *t7l66xb = irq_desc_get_handler_data(desc);
	अचिन्हित पूर्णांक isr;
	अचिन्हित पूर्णांक i, irq_base;

	irq_base = t7l66xb->irq_base;

	जबतक ((isr = पंचांगio_ioपढ़ो8(t7l66xb->scr + SCR_ISR) &
				~पंचांगio_ioपढ़ो8(t7l66xb->scr + SCR_IMR)))
		क्रम (i = 0; i < T7L66XB_NR_IRQS; i++)
			अगर (isr & (1 << i))
				generic_handle_irq(irq_base + i);
पूर्ण

अटल व्योम t7l66xb_irq_mask(काष्ठा irq_data *data)
अणु
	काष्ठा t7l66xb *t7l66xb = irq_data_get_irq_chip_data(data);
	अचिन्हित दीर्घ			flags;
	u8 imr;

	raw_spin_lock_irqsave(&t7l66xb->lock, flags);
	imr = पंचांगio_ioपढ़ो8(t7l66xb->scr + SCR_IMR);
	imr |= 1 << (data->irq - t7l66xb->irq_base);
	पंचांगio_ioग_लिखो8(imr, t7l66xb->scr + SCR_IMR);
	raw_spin_unlock_irqrestore(&t7l66xb->lock, flags);
पूर्ण

अटल व्योम t7l66xb_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा t7l66xb *t7l66xb = irq_data_get_irq_chip_data(data);
	अचिन्हित दीर्घ flags;
	u8 imr;

	raw_spin_lock_irqsave(&t7l66xb->lock, flags);
	imr = पंचांगio_ioपढ़ो8(t7l66xb->scr + SCR_IMR);
	imr &= ~(1 << (data->irq - t7l66xb->irq_base));
	पंचांगio_ioग_लिखो8(imr, t7l66xb->scr + SCR_IMR);
	raw_spin_unlock_irqrestore(&t7l66xb->lock, flags);
पूर्ण

अटल काष्ठा irq_chip t7l66xb_chip = अणु
	.name		= "t7l66xb",
	.irq_ack	= t7l66xb_irq_mask,
	.irq_mask	= t7l66xb_irq_mask,
	.irq_unmask	= t7l66xb_irq_unmask,
पूर्ण;

/*--------------------------------------------------------------------------*/

/* Install the IRQ handler */
अटल व्योम t7l66xb_attach_irq(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा t7l66xb *t7l66xb = platक्रमm_get_drvdata(dev);
	अचिन्हित पूर्णांक irq, irq_base;

	irq_base = t7l66xb->irq_base;

	क्रम (irq = irq_base; irq < irq_base + T7L66XB_NR_IRQS; irq++) अणु
		irq_set_chip_and_handler(irq, &t7l66xb_chip, handle_level_irq);
		irq_set_chip_data(irq, t7l66xb);
	पूर्ण

	irq_set_irq_type(t7l66xb->irq, IRQ_TYPE_EDGE_FALLING);
	irq_set_chained_handler_and_data(t7l66xb->irq, t7l66xb_irq, t7l66xb);
पूर्ण

अटल व्योम t7l66xb_detach_irq(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा t7l66xb *t7l66xb = platक्रमm_get_drvdata(dev);
	अचिन्हित पूर्णांक irq, irq_base;

	irq_base = t7l66xb->irq_base;

	irq_set_chained_handler_and_data(t7l66xb->irq, शून्य, शून्य);

	क्रम (irq = irq_base; irq < irq_base + T7L66XB_NR_IRQS; irq++) अणु
		irq_set_chip(irq, शून्य);
		irq_set_chip_data(irq, शून्य);
	पूर्ण
पूर्ण

/*--------------------------------------------------------------------------*/

#अगर_घोषित CONFIG_PM
अटल पूर्णांक t7l66xb_suspend(काष्ठा platक्रमm_device *dev, pm_message_t state)
अणु
	काष्ठा t7l66xb *t7l66xb = platक्रमm_get_drvdata(dev);
	काष्ठा t7l66xb_platक्रमm_data *pdata = dev_get_platdata(&dev->dev);

	अगर (pdata && pdata->suspend)
		pdata->suspend(dev);
	clk_disable_unprepare(t7l66xb->clk48m);

	वापस 0;
पूर्ण

अटल पूर्णांक t7l66xb_resume(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा t7l66xb *t7l66xb = platक्रमm_get_drvdata(dev);
	काष्ठा t7l66xb_platक्रमm_data *pdata = dev_get_platdata(&dev->dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(t7l66xb->clk48m);
	अगर (ret)
		वापस ret;

	अगर (pdata && pdata->resume)
		pdata->resume(dev);

	पंचांगio_core_mmc_enable(t7l66xb->scr + 0x200, 0,
		t7l66xb_mmc_resources[0].start & 0xfffe);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा t7l66xb_suspend शून्य
#घोषणा t7l66xb_resume	शून्य
#पूर्ण_अगर

/*--------------------------------------------------------------------------*/

अटल पूर्णांक t7l66xb_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा t7l66xb_platक्रमm_data *pdata = dev_get_platdata(&dev->dev);
	काष्ठा t7l66xb *t7l66xb;
	काष्ठा resource *iomem, *rscr;
	पूर्णांक ret;

	अगर (!pdata)
		वापस -EINVAL;

	iomem = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);
	अगर (!iomem)
		वापस -EINVAL;

	t7l66xb = kzalloc(माप *t7l66xb, GFP_KERNEL);
	अगर (!t7l66xb)
		वापस -ENOMEM;

	raw_spin_lock_init(&t7l66xb->lock);

	platक्रमm_set_drvdata(dev, t7l66xb);

	ret = platक्रमm_get_irq(dev, 0);
	अगर (ret >= 0)
		t7l66xb->irq = ret;
	अन्यथा
		जाओ err_noirq;

	t7l66xb->irq_base = pdata->irq_base;

	t7l66xb->clk32k = clk_get(&dev->dev, "CLK_CK32K");
	अगर (IS_ERR(t7l66xb->clk32k)) अणु
		ret = PTR_ERR(t7l66xb->clk32k);
		जाओ err_clk32k_get;
	पूर्ण

	t7l66xb->clk48m = clk_get(&dev->dev, "CLK_CK48M");
	अगर (IS_ERR(t7l66xb->clk48m)) अणु
		ret = PTR_ERR(t7l66xb->clk48m);
		जाओ err_clk48m_get;
	पूर्ण

	rscr = &t7l66xb->rscr;
	rscr->name = "t7l66xb-core";
	rscr->start = iomem->start;
	rscr->end = iomem->start + 0xff;
	rscr->flags = IORESOURCE_MEM;

	ret = request_resource(iomem, rscr);
	अगर (ret)
		जाओ err_request_scr;

	t7l66xb->scr = ioremap(rscr->start, resource_size(rscr));
	अगर (!t7l66xb->scr) अणु
		ret = -ENOMEM;
		जाओ err_ioremap;
	पूर्ण

	ret = clk_prepare_enable(t7l66xb->clk48m);
	अगर (ret)
		जाओ err_clk_enable;

	अगर (pdata->enable)
		pdata->enable(dev);

	/* Mask all पूर्णांकerrupts */
	पंचांगio_ioग_लिखो8(0xbf, t7l66xb->scr + SCR_IMR);

	prपूर्णांकk(KERN_INFO "%s rev %d @ 0x%08lx, irq %d\n",
		dev->name, पंचांगio_ioपढ़ो8(t7l66xb->scr + SCR_REVID),
		(अचिन्हित दीर्घ)iomem->start, t7l66xb->irq);

	t7l66xb_attach_irq(dev);

	t7l66xb_cells[T7L66XB_CELL_न_अंकD].platक्रमm_data = pdata->nand_data;
	t7l66xb_cells[T7L66XB_CELL_न_अंकD].pdata_size = माप(*pdata->nand_data);

	ret = mfd_add_devices(&dev->dev, dev->id,
			      t7l66xb_cells, ARRAY_SIZE(t7l66xb_cells),
			      iomem, t7l66xb->irq_base, शून्य);

	अगर (!ret)
		वापस 0;

	t7l66xb_detach_irq(dev);
	clk_disable_unprepare(t7l66xb->clk48m);
err_clk_enable:
	iounmap(t7l66xb->scr);
err_ioremap:
	release_resource(&t7l66xb->rscr);
err_request_scr:
	clk_put(t7l66xb->clk48m);
err_clk48m_get:
	clk_put(t7l66xb->clk32k);
err_clk32k_get:
err_noirq:
	kमुक्त(t7l66xb);
	वापस ret;
पूर्ण

अटल पूर्णांक t7l66xb_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा t7l66xb_platक्रमm_data *pdata = dev_get_platdata(&dev->dev);
	काष्ठा t7l66xb *t7l66xb = platक्रमm_get_drvdata(dev);
	पूर्णांक ret;

	ret = pdata->disable(dev);
	clk_disable_unprepare(t7l66xb->clk48m);
	clk_put(t7l66xb->clk48m);
	clk_disable_unprepare(t7l66xb->clk32k);
	clk_put(t7l66xb->clk32k);
	t7l66xb_detach_irq(dev);
	iounmap(t7l66xb->scr);
	release_resource(&t7l66xb->rscr);
	mfd_हटाओ_devices(&dev->dev);
	kमुक्त(t7l66xb);

	वापस ret;

पूर्ण

अटल काष्ठा platक्रमm_driver t7l66xb_platक्रमm_driver = अणु
	.driver = अणु
		.name	= "t7l66xb",
	पूर्ण,
	.suspend	= t7l66xb_suspend,
	.resume		= t7l66xb_resume,
	.probe		= t7l66xb_probe,
	.हटाओ		= t7l66xb_हटाओ,
पूर्ण;

/*--------------------------------------------------------------------------*/

module_platक्रमm_driver(t7l66xb_platक्रमm_driver);

MODULE_DESCRIPTION("Toshiba T7L66XB core driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Ian Molton");
MODULE_ALIAS("platform:t7l66xb");
