<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel IXP4xx Queue Manager driver क्रम Linux
 *
 * Copyright (C) 2007 Krzysztof Halasa <khc@pm.waw.pl>
 */

#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/soc/ixp4xx/qmgr.h>

अटल काष्ठा qmgr_regs __iomem *qmgr_regs;
अटल पूर्णांक qmgr_irq_1;
अटल पूर्णांक qmgr_irq_2;
अटल spinlock_t qmgr_lock;
अटल u32 used_sram_biपंचांगap[4]; /* 128 16-dword pages */
अटल व्योम (*irq_handlers[QUEUES])(व्योम *pdev);
अटल व्योम *irq_pdevs[QUEUES];

#अगर DEBUG_QMGR
अक्षर qmgr_queue_descs[QUEUES][32];
#पूर्ण_अगर

व्योम qmgr_put_entry(अचिन्हित पूर्णांक queue, u32 val)
अणु
#अगर DEBUG_QMGR
	BUG_ON(!qmgr_queue_descs[queue]); /* not yet requested */

	prपूर्णांकk(KERN_DEBUG "Queue %s(%i) put %X\n",
	       qmgr_queue_descs[queue], queue, val);
#पूर्ण_अगर
	__raw_ग_लिखोl(val, &qmgr_regs->acc[queue][0]);
पूर्ण

u32 qmgr_get_entry(अचिन्हित पूर्णांक queue)
अणु
	u32 val;
	val = __raw_पढ़ोl(&qmgr_regs->acc[queue][0]);
#अगर DEBUG_QMGR
	BUG_ON(!qmgr_queue_descs[queue]); /* not yet requested */

	prपूर्णांकk(KERN_DEBUG "Queue %s(%i) get %X\n",
	       qmgr_queue_descs[queue], queue, val);
#पूर्ण_अगर
	वापस val;
पूर्ण

अटल पूर्णांक __qmgr_get_stat1(अचिन्हित पूर्णांक queue)
अणु
	वापस (__raw_पढ़ोl(&qmgr_regs->stat1[queue >> 3])
		>> ((queue & 7) << 2)) & 0xF;
पूर्ण

अटल पूर्णांक __qmgr_get_stat2(अचिन्हित पूर्णांक queue)
अणु
	BUG_ON(queue >= HALF_QUEUES);
	वापस (__raw_पढ़ोl(&qmgr_regs->stat2[queue >> 4])
		>> ((queue & 0xF) << 1)) & 0x3;
पूर्ण

/**
 * qmgr_stat_empty() - checks अगर a hardware queue is empty
 * @queue:	queue number
 *
 * Returns non-zero value अगर the queue is empty.
 */
पूर्णांक qmgr_stat_empty(अचिन्हित पूर्णांक queue)
अणु
	BUG_ON(queue >= HALF_QUEUES);
	वापस __qmgr_get_stat1(queue) & QUEUE_STAT1_EMPTY;
पूर्ण

/**
 * qmgr_stat_below_low_watermark() - checks अगर a queue is below low watermark
 * @queue:	queue number
 *
 * Returns non-zero value अगर the queue is below low watermark.
 */
पूर्णांक qmgr_stat_below_low_watermark(अचिन्हित पूर्णांक queue)
अणु
	अगर (queue >= HALF_QUEUES)
		वापस (__raw_पढ़ोl(&qmgr_regs->statne_h) >>
			(queue - HALF_QUEUES)) & 0x01;
	वापस __qmgr_get_stat1(queue) & QUEUE_STAT1_NEARLY_EMPTY;
पूर्ण

/**
 * qmgr_stat_full() - checks अगर a hardware queue is full
 * @queue:	queue number
 *
 * Returns non-zero value अगर the queue is full.
 */
पूर्णांक qmgr_stat_full(अचिन्हित पूर्णांक queue)
अणु
	अगर (queue >= HALF_QUEUES)
		वापस (__raw_पढ़ोl(&qmgr_regs->statf_h) >>
			(queue - HALF_QUEUES)) & 0x01;
	वापस __qmgr_get_stat1(queue) & QUEUE_STAT1_FULL;
पूर्ण

/**
 * qmgr_stat_overflow() - checks अगर a hardware queue experienced overflow
 * @queue:	queue number
 *
 * Returns non-zero value अगर the queue experienced overflow.
 */
पूर्णांक qmgr_stat_overflow(अचिन्हित पूर्णांक queue)
अणु
	वापस __qmgr_get_stat2(queue) & QUEUE_STAT2_OVERFLOW;
पूर्ण

व्योम qmgr_set_irq(अचिन्हित पूर्णांक queue, पूर्णांक src,
		  व्योम (*handler)(व्योम *pdev), व्योम *pdev)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&qmgr_lock, flags);
	अगर (queue < HALF_QUEUES) अणु
		u32 __iomem *reg;
		पूर्णांक bit;
		BUG_ON(src > QUEUE_IRQ_SRC_NOT_FULL);
		reg = &qmgr_regs->irqsrc[queue >> 3]; /* 8 queues per u32 */
		bit = (queue % 8) * 4; /* 3 bits + 1 reserved bit per queue */
		__raw_ग_लिखोl((__raw_पढ़ोl(reg) & ~(7 << bit)) | (src << bit),
			     reg);
	पूर्ण अन्यथा
		/* IRQ source क्रम queues 32-63 is fixed */
		BUG_ON(src != QUEUE_IRQ_SRC_NOT_NEARLY_EMPTY);

	irq_handlers[queue] = handler;
	irq_pdevs[queue] = pdev;
	spin_unlock_irqrestore(&qmgr_lock, flags);
पूर्ण


अटल irqवापस_t qmgr_irq1_a0(पूर्णांक irq, व्योम *pdev)
अणु
	पूर्णांक i, ret = 0;
	u32 en_biपंचांगap, src, stat;

	/* ACK - it may clear any bits so करोn't rely on it */
	__raw_ग_लिखोl(0xFFFFFFFF, &qmgr_regs->irqstat[0]);

	en_biपंचांगap = qmgr_regs->irqen[0];
	जबतक (en_biपंचांगap) अणु
		i = __fls(en_biपंचांगap); /* number of the last "low" queue */
		en_biपंचांगap &= ~BIT(i);
		src = qmgr_regs->irqsrc[i >> 3];
		stat = qmgr_regs->stat1[i >> 3];
		अगर (src & 4) /* the IRQ condition is inverted */
			stat = ~stat;
		अगर (stat & BIT(src & 3)) अणु
			irq_handlers[i](irq_pdevs[i]);
			ret = IRQ_HANDLED;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण


अटल irqवापस_t qmgr_irq2_a0(पूर्णांक irq, व्योम *pdev)
अणु
	पूर्णांक i, ret = 0;
	u32 req_biपंचांगap;

	/* ACK - it may clear any bits so करोn't rely on it */
	__raw_ग_लिखोl(0xFFFFFFFF, &qmgr_regs->irqstat[1]);

	req_biपंचांगap = qmgr_regs->irqen[1] & qmgr_regs->statne_h;
	जबतक (req_biपंचांगap) अणु
		i = __fls(req_biपंचांगap); /* number of the last "high" queue */
		req_biपंचांगap &= ~BIT(i);
		irq_handlers[HALF_QUEUES + i](irq_pdevs[HALF_QUEUES + i]);
		ret = IRQ_HANDLED;
	पूर्ण
	वापस ret;
पूर्ण


अटल irqवापस_t qmgr_irq(पूर्णांक irq, व्योम *pdev)
अणु
	पूर्णांक i, half = (irq == qmgr_irq_1 ? 0 : 1);
	u32 req_biपंचांगap = __raw_पढ़ोl(&qmgr_regs->irqstat[half]);

	अगर (!req_biपंचांगap)
		वापस 0;
	__raw_ग_लिखोl(req_biपंचांगap, &qmgr_regs->irqstat[half]); /* ACK */

	जबतक (req_biपंचांगap) अणु
		i = __fls(req_biपंचांगap); /* number of the last queue */
		req_biपंचांगap &= ~BIT(i);
		i += half * HALF_QUEUES;
		irq_handlers[i](irq_pdevs[i]);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण


व्योम qmgr_enable_irq(अचिन्हित पूर्णांक queue)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक half = queue / 32;
	u32 mask = 1 << (queue & (HALF_QUEUES - 1));

	spin_lock_irqsave(&qmgr_lock, flags);
	__raw_ग_लिखोl(__raw_पढ़ोl(&qmgr_regs->irqen[half]) | mask,
		     &qmgr_regs->irqen[half]);
	spin_unlock_irqrestore(&qmgr_lock, flags);
पूर्ण

व्योम qmgr_disable_irq(अचिन्हित पूर्णांक queue)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक half = queue / 32;
	u32 mask = 1 << (queue & (HALF_QUEUES - 1));

	spin_lock_irqsave(&qmgr_lock, flags);
	__raw_ग_लिखोl(__raw_पढ़ोl(&qmgr_regs->irqen[half]) & ~mask,
		     &qmgr_regs->irqen[half]);
	__raw_ग_लिखोl(mask, &qmgr_regs->irqstat[half]); /* clear */
	spin_unlock_irqrestore(&qmgr_lock, flags);
पूर्ण

अटल अंतरभूत व्योम shअगरt_mask(u32 *mask)
अणु
	mask[3] = mask[3] << 1 | mask[2] >> 31;
	mask[2] = mask[2] << 1 | mask[1] >> 31;
	mask[1] = mask[1] << 1 | mask[0] >> 31;
	mask[0] <<= 1;
पूर्ण

#अगर DEBUG_QMGR
पूर्णांक qmgr_request_queue(अचिन्हित पूर्णांक queue, अचिन्हित पूर्णांक len /* dwords */,
		       अचिन्हित पूर्णांक nearly_empty_watermark,
		       अचिन्हित पूर्णांक nearly_full_watermark,
		       स्थिर अक्षर *desc_क्रमmat, स्थिर अक्षर* name)
#अन्यथा
पूर्णांक __qmgr_request_queue(अचिन्हित पूर्णांक queue, अचिन्हित पूर्णांक len /* dwords */,
			 अचिन्हित पूर्णांक nearly_empty_watermark,
			 अचिन्हित पूर्णांक nearly_full_watermark)
#पूर्ण_अगर
अणु
	u32 cfg, addr = 0, mask[4]; /* in 16-dwords */
	पूर्णांक err;

	BUG_ON(queue >= QUEUES);

	अगर ((nearly_empty_watermark | nearly_full_watermark) & ~7)
		वापस -EINVAL;

	चयन (len) अणु
	हाल  16:
		cfg = 0 << 24;
		mask[0] = 0x1;
		अवरोध;
	हाल  32:
		cfg = 1 << 24;
		mask[0] = 0x3;
		अवरोध;
	हाल  64:
		cfg = 2 << 24;
		mask[0] = 0xF;
		अवरोध;
	हाल 128:
		cfg = 3 << 24;
		mask[0] = 0xFF;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	cfg |= nearly_empty_watermark << 26;
	cfg |= nearly_full_watermark << 29;
	len /= 16;		/* in 16-dwords: 1, 2, 4 or 8 */
	mask[1] = mask[2] = mask[3] = 0;

	अगर (!try_module_get(THIS_MODULE))
		वापस -ENODEV;

	spin_lock_irq(&qmgr_lock);
	अगर (__raw_पढ़ोl(&qmgr_regs->sram[queue])) अणु
		err = -EBUSY;
		जाओ err;
	पूर्ण

	जबतक (1) अणु
		अगर (!(used_sram_biपंचांगap[0] & mask[0]) &&
		    !(used_sram_biपंचांगap[1] & mask[1]) &&
		    !(used_sram_biपंचांगap[2] & mask[2]) &&
		    !(used_sram_biपंचांगap[3] & mask[3]))
			अवरोध; /* found मुक्त space */

		addr++;
		shअगरt_mask(mask);
		अगर (addr + len > ARRAY_SIZE(qmgr_regs->sram)) अणु
			prपूर्णांकk(KERN_ERR "qmgr: no free SRAM space for"
			       " queue %i\n", queue);
			err = -ENOMEM;
			जाओ err;
		पूर्ण
	पूर्ण

	used_sram_biपंचांगap[0] |= mask[0];
	used_sram_biपंचांगap[1] |= mask[1];
	used_sram_biपंचांगap[2] |= mask[2];
	used_sram_biपंचांगap[3] |= mask[3];
	__raw_ग_लिखोl(cfg | (addr << 14), &qmgr_regs->sram[queue]);
#अगर DEBUG_QMGR
	snम_लिखो(qmgr_queue_descs[queue], माप(qmgr_queue_descs[0]),
		 desc_क्रमmat, name);
	prपूर्णांकk(KERN_DEBUG "qmgr: requested queue %s(%i) addr = 0x%02X\n",
	       qmgr_queue_descs[queue], queue, addr);
#पूर्ण_अगर
	spin_unlock_irq(&qmgr_lock);
	वापस 0;

err:
	spin_unlock_irq(&qmgr_lock);
	module_put(THIS_MODULE);
	वापस err;
पूर्ण

व्योम qmgr_release_queue(अचिन्हित पूर्णांक queue)
अणु
	u32 cfg, addr, mask[4];

	BUG_ON(queue >= QUEUES); /* not in valid range */

	spin_lock_irq(&qmgr_lock);
	cfg = __raw_पढ़ोl(&qmgr_regs->sram[queue]);
	addr = (cfg >> 14) & 0xFF;

	BUG_ON(!addr);		/* not requested */

	चयन ((cfg >> 24) & 3) अणु
	हाल 0: mask[0] = 0x1; अवरोध;
	हाल 1: mask[0] = 0x3; अवरोध;
	हाल 2: mask[0] = 0xF; अवरोध;
	हाल 3: mask[0] = 0xFF; अवरोध;
	पूर्ण

	mask[1] = mask[2] = mask[3] = 0;

	जबतक (addr--)
		shअगरt_mask(mask);

#अगर DEBUG_QMGR
	prपूर्णांकk(KERN_DEBUG "qmgr: releasing queue %s(%i)\n",
	       qmgr_queue_descs[queue], queue);
	qmgr_queue_descs[queue][0] = '\x0';
#पूर्ण_अगर

	जबतक ((addr = qmgr_get_entry(queue)))
		prपूर्णांकk(KERN_ERR "qmgr: released queue %i not empty: 0x%08X\n",
		       queue, addr);

	__raw_ग_लिखोl(0, &qmgr_regs->sram[queue]);

	used_sram_biपंचांगap[0] &= ~mask[0];
	used_sram_biपंचांगap[1] &= ~mask[1];
	used_sram_biपंचांगap[2] &= ~mask[2];
	used_sram_biपंचांगap[3] &= ~mask[3];
	irq_handlers[queue] = शून्य; /* catch IRQ bugs */
	spin_unlock_irq(&qmgr_lock);

	module_put(THIS_MODULE);
पूर्ण

अटल पूर्णांक ixp4xx_qmgr_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i, err;
	irq_handler_t handler1, handler2;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	पूर्णांक irq1, irq2;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;
	qmgr_regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(qmgr_regs))
		वापस PTR_ERR(qmgr_regs);

	irq1 = platक्रमm_get_irq(pdev, 0);
	अगर (irq1 <= 0)
		वापस irq1 ? irq1 : -EINVAL;
	qmgr_irq_1 = irq1;
	irq2 = platक्रमm_get_irq(pdev, 1);
	अगर (irq2 <= 0)
		वापस irq2 ? irq2 : -EINVAL;
	qmgr_irq_2 = irq2;

	/* reset qmgr रेजिस्टरs */
	क्रम (i = 0; i < 4; i++) अणु
		__raw_ग_लिखोl(0x33333333, &qmgr_regs->stat1[i]);
		__raw_ग_लिखोl(0, &qmgr_regs->irqsrc[i]);
	पूर्ण
	क्रम (i = 0; i < 2; i++) अणु
		__raw_ग_लिखोl(0, &qmgr_regs->stat2[i]);
		__raw_ग_लिखोl(0xFFFFFFFF, &qmgr_regs->irqstat[i]); /* clear */
		__raw_ग_लिखोl(0, &qmgr_regs->irqen[i]);
	पूर्ण

	__raw_ग_लिखोl(0xFFFFFFFF, &qmgr_regs->statne_h);
	__raw_ग_लिखोl(0, &qmgr_regs->statf_h);

	क्रम (i = 0; i < QUEUES; i++)
		__raw_ग_लिखोl(0, &qmgr_regs->sram[i]);

	अगर (cpu_is_ixp42x_rev_a0()) अणु
		handler1 = qmgr_irq1_a0;
		handler2 = qmgr_irq2_a0;
	पूर्ण अन्यथा
		handler1 = handler2 = qmgr_irq;

	err = devm_request_irq(dev, irq1, handler1, 0, "IXP4xx Queue Manager",
			       शून्य);
	अगर (err) अणु
		dev_err(dev, "failed to request IRQ%i (%i)\n",
			irq1, err);
		वापस err;
	पूर्ण

	err = devm_request_irq(dev, irq2, handler2, 0, "IXP4xx Queue Manager",
			       शून्य);
	अगर (err) अणु
		dev_err(dev, "failed to request IRQ%i (%i)\n",
			irq2, err);
		वापस err;
	पूर्ण

	used_sram_biपंचांगap[0] = 0xF; /* 4 first pages reserved क्रम config */
	spin_lock_init(&qmgr_lock);

	dev_info(dev, "IXP4xx Queue Manager initialized.\n");
	वापस 0;
पूर्ण

अटल पूर्णांक ixp4xx_qmgr_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	synchronize_irq(qmgr_irq_1);
	synchronize_irq(qmgr_irq_2);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ixp4xx_qmgr_of_match[] = अणु
	अणु
		.compatible = "intel,ixp4xx-ahb-queue-manager",
        पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver ixp4xx_qmgr_driver = अणु
	.driver = अणु
		.name           = "ixp4xx-qmgr",
		.of_match_table = of_match_ptr(ixp4xx_qmgr_of_match),
	पूर्ण,
	.probe = ixp4xx_qmgr_probe,
	.हटाओ = ixp4xx_qmgr_हटाओ,
पूर्ण;
module_platक्रमm_driver(ixp4xx_qmgr_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Krzysztof Halasa");

EXPORT_SYMBOL(qmgr_put_entry);
EXPORT_SYMBOL(qmgr_get_entry);
EXPORT_SYMBOL(qmgr_stat_empty);
EXPORT_SYMBOL(qmgr_stat_below_low_watermark);
EXPORT_SYMBOL(qmgr_stat_full);
EXPORT_SYMBOL(qmgr_stat_overflow);
EXPORT_SYMBOL(qmgr_set_irq);
EXPORT_SYMBOL(qmgr_enable_irq);
EXPORT_SYMBOL(qmgr_disable_irq);
#अगर DEBUG_QMGR
EXPORT_SYMBOL(qmgr_queue_descs);
EXPORT_SYMBOL(qmgr_request_queue);
#अन्यथा
EXPORT_SYMBOL(__qmgr_request_queue);
#पूर्ण_अगर
EXPORT_SYMBOL(qmgr_release_queue);
