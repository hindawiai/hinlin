<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *   Copyright (C) 2011 John Crispin <john@phrozen.org>
 */

#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/export.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>

#समावेश <lantiq_soc.h>
#समावेश <xway_dma.h>

#घोषणा LTQ_DMA_ID		0x08
#घोषणा LTQ_DMA_CTRL		0x10
#घोषणा LTQ_DMA_CPOLL		0x14
#घोषणा LTQ_DMA_CS		0x18
#घोषणा LTQ_DMA_CCTRL		0x1C
#घोषणा LTQ_DMA_CDBA		0x20
#घोषणा LTQ_DMA_CDLEN		0x24
#घोषणा LTQ_DMA_CIS		0x28
#घोषणा LTQ_DMA_CIE		0x2C
#घोषणा LTQ_DMA_PS		0x40
#घोषणा LTQ_DMA_PCTRL		0x44
#घोषणा LTQ_DMA_IRNEN		0xf4

#घोषणा DMA_DESCPT		BIT(3)		/* descriptor complete irq */
#घोषणा DMA_TX			BIT(8)		/* TX channel direction */
#घोषणा DMA_CHAN_ON		BIT(0)		/* channel on / off bit */
#घोषणा DMA_PDEN		BIT(6)		/* enable packet drop */
#घोषणा DMA_CHAN_RST		BIT(1)		/* channel on / off bit */
#घोषणा DMA_RESET		BIT(0)		/* channel on / off bit */
#घोषणा DMA_IRQ_ACK		0x7e		/* IRQ status रेजिस्टर */
#घोषणा DMA_POLL		BIT(31)		/* turn on channel polling */
#घोषणा DMA_CLK_DIV4		BIT(6)		/* polling घड़ी भागider */
#घोषणा DMA_2W_BURST		BIT(1)		/* 2 word burst length */
#घोषणा DMA_MAX_CHANNEL		20		/* the soc has 20 channels */
#घोषणा DMA_ETOP_ENDIANNESS	(0xf << 8) /* endianness swap etop channels */
#घोषणा DMA_WEIGHT	(BIT(17) | BIT(16))	/* शेष channel wheight */

#घोषणा ltq_dma_r32(x)			ltq_r32(ltq_dma_membase + (x))
#घोषणा ltq_dma_w32(x, y)		ltq_w32(x, ltq_dma_membase + (y))
#घोषणा ltq_dma_w32_mask(x, y, z)	ltq_w32_mask(x, y, \
						ltq_dma_membase + (z))

अटल व्योम __iomem *ltq_dma_membase;
अटल DEFINE_SPINLOCK(ltq_dma_lock);

व्योम
ltq_dma_enable_irq(काष्ठा ltq_dma_channel *ch)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ltq_dma_lock, flags);
	ltq_dma_w32(ch->nr, LTQ_DMA_CS);
	ltq_dma_w32_mask(0, 1 << ch->nr, LTQ_DMA_IRNEN);
	spin_unlock_irqrestore(&ltq_dma_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(ltq_dma_enable_irq);

व्योम
ltq_dma_disable_irq(काष्ठा ltq_dma_channel *ch)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ltq_dma_lock, flags);
	ltq_dma_w32(ch->nr, LTQ_DMA_CS);
	ltq_dma_w32_mask(1 << ch->nr, 0, LTQ_DMA_IRNEN);
	spin_unlock_irqrestore(&ltq_dma_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(ltq_dma_disable_irq);

व्योम
ltq_dma_ack_irq(काष्ठा ltq_dma_channel *ch)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ltq_dma_lock, flags);
	ltq_dma_w32(ch->nr, LTQ_DMA_CS);
	ltq_dma_w32(DMA_IRQ_ACK, LTQ_DMA_CIS);
	spin_unlock_irqrestore(&ltq_dma_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(ltq_dma_ack_irq);

व्योम
ltq_dma_खोलो(काष्ठा ltq_dma_channel *ch)
अणु
	अचिन्हित दीर्घ flag;

	spin_lock_irqsave(&ltq_dma_lock, flag);
	ltq_dma_w32(ch->nr, LTQ_DMA_CS);
	ltq_dma_w32_mask(0, DMA_CHAN_ON, LTQ_DMA_CCTRL);
	spin_unlock_irqrestore(&ltq_dma_lock, flag);
पूर्ण
EXPORT_SYMBOL_GPL(ltq_dma_खोलो);

व्योम
ltq_dma_बंद(काष्ठा ltq_dma_channel *ch)
अणु
	अचिन्हित दीर्घ flag;

	spin_lock_irqsave(&ltq_dma_lock, flag);
	ltq_dma_w32(ch->nr, LTQ_DMA_CS);
	ltq_dma_w32_mask(DMA_CHAN_ON, 0, LTQ_DMA_CCTRL);
	ltq_dma_w32_mask(1 << ch->nr, 0, LTQ_DMA_IRNEN);
	spin_unlock_irqrestore(&ltq_dma_lock, flag);
पूर्ण
EXPORT_SYMBOL_GPL(ltq_dma_बंद);

अटल व्योम
ltq_dma_alloc(काष्ठा ltq_dma_channel *ch)
अणु
	अचिन्हित दीर्घ flags;

	ch->desc = 0;
	ch->desc_base = dma_alloc_coherent(ch->dev,
					   LTQ_DESC_NUM * LTQ_DESC_SIZE,
					   &ch->phys, GFP_ATOMIC);

	spin_lock_irqsave(&ltq_dma_lock, flags);
	ltq_dma_w32(ch->nr, LTQ_DMA_CS);
	ltq_dma_w32(ch->phys, LTQ_DMA_CDBA);
	ltq_dma_w32(LTQ_DESC_NUM, LTQ_DMA_CDLEN);
	ltq_dma_w32_mask(DMA_CHAN_ON, 0, LTQ_DMA_CCTRL);
	wmb();
	ltq_dma_w32_mask(0, DMA_CHAN_RST, LTQ_DMA_CCTRL);
	जबतक (ltq_dma_r32(LTQ_DMA_CCTRL) & DMA_CHAN_RST)
		;
	spin_unlock_irqrestore(&ltq_dma_lock, flags);
पूर्ण

व्योम
ltq_dma_alloc_tx(काष्ठा ltq_dma_channel *ch)
अणु
	अचिन्हित दीर्घ flags;

	ltq_dma_alloc(ch);

	spin_lock_irqsave(&ltq_dma_lock, flags);
	ltq_dma_w32(DMA_DESCPT, LTQ_DMA_CIE);
	ltq_dma_w32_mask(0, 1 << ch->nr, LTQ_DMA_IRNEN);
	ltq_dma_w32(DMA_WEIGHT | DMA_TX, LTQ_DMA_CCTRL);
	spin_unlock_irqrestore(&ltq_dma_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(ltq_dma_alloc_tx);

व्योम
ltq_dma_alloc_rx(काष्ठा ltq_dma_channel *ch)
अणु
	अचिन्हित दीर्घ flags;

	ltq_dma_alloc(ch);

	spin_lock_irqsave(&ltq_dma_lock, flags);
	ltq_dma_w32(DMA_DESCPT, LTQ_DMA_CIE);
	ltq_dma_w32_mask(0, 1 << ch->nr, LTQ_DMA_IRNEN);
	ltq_dma_w32(DMA_WEIGHT, LTQ_DMA_CCTRL);
	spin_unlock_irqrestore(&ltq_dma_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(ltq_dma_alloc_rx);

व्योम
ltq_dma_मुक्त(काष्ठा ltq_dma_channel *ch)
अणु
	अगर (!ch->desc_base)
		वापस;
	ltq_dma_बंद(ch);
	dma_मुक्त_coherent(ch->dev, LTQ_DESC_NUM * LTQ_DESC_SIZE,
		ch->desc_base, ch->phys);
पूर्ण
EXPORT_SYMBOL_GPL(ltq_dma_मुक्त);

व्योम
ltq_dma_init_port(पूर्णांक p)
अणु
	ltq_dma_w32(p, LTQ_DMA_PS);
	चयन (p) अणु
	हाल DMA_PORT_ETOP:
		/*
		 * Tell the DMA engine to swap the endianness of data frames and
		 * drop packets अगर the channel arbitration fails.
		 */
		ltq_dma_w32_mask(0, DMA_ETOP_ENDIANNESS | DMA_PDEN,
			LTQ_DMA_PCTRL);
		अवरोध;

	हाल DMA_PORT_DEU:
		ltq_dma_w32((DMA_2W_BURST << 4) | (DMA_2W_BURST << 2),
			LTQ_DMA_PCTRL);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ltq_dma_init_port);

अटल पूर्णांक
ltq_dma_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk *clk;
	काष्ठा resource *res;
	अचिन्हित id;
	पूर्णांक i;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ltq_dma_membase = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(ltq_dma_membase))
		panic("Failed to remap dma resource");

	/* घातer up and reset the dma engine */
	clk = clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(clk))
		panic("Failed to get dma clock");

	clk_enable(clk);
	ltq_dma_w32_mask(0, DMA_RESET, LTQ_DMA_CTRL);

	/* disable all पूर्णांकerrupts */
	ltq_dma_w32(0, LTQ_DMA_IRNEN);

	/* reset/configure each channel */
	क्रम (i = 0; i < DMA_MAX_CHANNEL; i++) अणु
		ltq_dma_w32(i, LTQ_DMA_CS);
		ltq_dma_w32(DMA_CHAN_RST, LTQ_DMA_CCTRL);
		ltq_dma_w32(DMA_POLL | DMA_CLK_DIV4, LTQ_DMA_CPOLL);
		ltq_dma_w32_mask(DMA_CHAN_ON, 0, LTQ_DMA_CCTRL);
	पूर्ण

	id = ltq_dma_r32(LTQ_DMA_ID);
	dev_info(&pdev->dev,
		"Init done - hw rev: %X, ports: %d, channels: %d\n",
		id & 0x1f, (id >> 16) & 0xf, id >> 20);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id dma_match[] = अणु
	अणु .compatible = "lantiq,dma-xway" पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver dma_driver = अणु
	.probe = ltq_dma_init,
	.driver = अणु
		.name = "dma-xway",
		.of_match_table = dma_match,
	पूर्ण,
पूर्ण;

पूर्णांक __init
dma_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&dma_driver);
पूर्ण

postcore_initcall(dma_init);
