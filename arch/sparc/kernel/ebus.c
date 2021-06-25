<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* ebus.c: EBUS DMA library code.
 *
 * Copyright (C) 1997  Eddie C. Dost  (ecd@skynet.be)
 * Copyright (C) 1999  David S. Miller (davem@redhat.com)
 */

#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>

#समावेश <यंत्र/ebus_dma.h>
#समावेश <यंत्र/पन.स>

#घोषणा EBDMA_CSR	0x00UL	/* Control/Status */
#घोषणा EBDMA_ADDR	0x04UL	/* DMA Address */
#घोषणा EBDMA_COUNT	0x08UL	/* DMA Count */

#घोषणा EBDMA_CSR_INT_PEND	0x00000001
#घोषणा EBDMA_CSR_ERR_PEND	0x00000002
#घोषणा EBDMA_CSR_DRAIN		0x00000004
#घोषणा EBDMA_CSR_INT_EN	0x00000010
#घोषणा EBDMA_CSR_RESET		0x00000080
#घोषणा EBDMA_CSR_WRITE		0x00000100
#घोषणा EBDMA_CSR_EN_DMA	0x00000200
#घोषणा EBDMA_CSR_CYC_PEND	0x00000400
#घोषणा EBDMA_CSR_DIAG_RD_DONE	0x00000800
#घोषणा EBDMA_CSR_DIAG_WR_DONE	0x00001000
#घोषणा EBDMA_CSR_EN_CNT	0x00002000
#घोषणा EBDMA_CSR_TC		0x00004000
#घोषणा EBDMA_CSR_DIS_CSR_DRN	0x00010000
#घोषणा EBDMA_CSR_BURST_SZ_MASK	0x000c0000
#घोषणा EBDMA_CSR_BURST_SZ_1	0x00080000
#घोषणा EBDMA_CSR_BURST_SZ_4	0x00000000
#घोषणा EBDMA_CSR_BURST_SZ_8	0x00040000
#घोषणा EBDMA_CSR_BURST_SZ_16	0x000c0000
#घोषणा EBDMA_CSR_DIAG_EN	0x00100000
#घोषणा EBDMA_CSR_DIS_ERR_PEND	0x00400000
#घोषणा EBDMA_CSR_TCI_DIS	0x00800000
#घोषणा EBDMA_CSR_EN_NEXT	0x01000000
#घोषणा EBDMA_CSR_DMA_ON	0x02000000
#घोषणा EBDMA_CSR_A_LOADED	0x04000000
#घोषणा EBDMA_CSR_NA_LOADED	0x08000000
#घोषणा EBDMA_CSR_DEV_ID_MASK	0xf0000000

#घोषणा EBUS_DMA_RESET_TIMEOUT	10000

अटल व्योम __ebus_dma_reset(काष्ठा ebus_dma_info *p, पूर्णांक no_drain)
अणु
	पूर्णांक i;
	u32 val = 0;

	ग_लिखोl(EBDMA_CSR_RESET, p->regs + EBDMA_CSR);
	udelay(1);

	अगर (no_drain)
		वापस;

	क्रम (i = EBUS_DMA_RESET_TIMEOUT; i > 0; i--) अणु
		val = पढ़ोl(p->regs + EBDMA_CSR);

		अगर (!(val & (EBDMA_CSR_DRAIN | EBDMA_CSR_CYC_PEND)))
			अवरोध;
		udelay(10);
	पूर्ण
पूर्ण

अटल irqवापस_t ebus_dma_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ebus_dma_info *p = dev_id;
	अचिन्हित दीर्घ flags;
	u32 csr = 0;

	spin_lock_irqsave(&p->lock, flags);
	csr = पढ़ोl(p->regs + EBDMA_CSR);
	ग_लिखोl(csr, p->regs + EBDMA_CSR);
	spin_unlock_irqrestore(&p->lock, flags);

	अगर (csr & EBDMA_CSR_ERR_PEND) अणु
		prपूर्णांकk(KERN_CRIT "ebus_dma(%s): DMA error!\n", p->name);
		p->callback(p, EBUS_DMA_EVENT_ERROR, p->client_cookie);
		वापस IRQ_HANDLED;
	पूर्ण अन्यथा अगर (csr & EBDMA_CSR_INT_PEND) अणु
		p->callback(p,
			    (csr & EBDMA_CSR_TC) ?
			    EBUS_DMA_EVENT_DMA : EBUS_DMA_EVENT_DEVICE,
			    p->client_cookie);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;

पूर्ण

पूर्णांक ebus_dma_रेजिस्टर(काष्ठा ebus_dma_info *p)
अणु
	u32 csr;

	अगर (!p->regs)
		वापस -EINVAL;
	अगर (p->flags & ~(EBUS_DMA_FLAG_USE_EBDMA_HANDLER |
			 EBUS_DMA_FLAG_TCI_DISABLE))
		वापस -EINVAL;
	अगर ((p->flags & EBUS_DMA_FLAG_USE_EBDMA_HANDLER) && !p->callback)
		वापस -EINVAL;
	अगर (!म_माप(p->name))
		वापस -EINVAL;

	__ebus_dma_reset(p, 1);

	csr = EBDMA_CSR_BURST_SZ_16 | EBDMA_CSR_EN_CNT;

	अगर (p->flags & EBUS_DMA_FLAG_TCI_DISABLE)
		csr |= EBDMA_CSR_TCI_DIS;

	ग_लिखोl(csr, p->regs + EBDMA_CSR);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ebus_dma_रेजिस्टर);

पूर्णांक ebus_dma_irq_enable(काष्ठा ebus_dma_info *p, पूर्णांक on)
अणु
	अचिन्हित दीर्घ flags;
	u32 csr;

	अगर (on) अणु
		अगर (p->flags & EBUS_DMA_FLAG_USE_EBDMA_HANDLER) अणु
			अगर (request_irq(p->irq, ebus_dma_irq, IRQF_SHARED, p->name, p))
				वापस -EBUSY;
		पूर्ण

		spin_lock_irqsave(&p->lock, flags);
		csr = पढ़ोl(p->regs + EBDMA_CSR);
		csr |= EBDMA_CSR_INT_EN;
		ग_लिखोl(csr, p->regs + EBDMA_CSR);
		spin_unlock_irqrestore(&p->lock, flags);
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&p->lock, flags);
		csr = पढ़ोl(p->regs + EBDMA_CSR);
		csr &= ~EBDMA_CSR_INT_EN;
		ग_लिखोl(csr, p->regs + EBDMA_CSR);
		spin_unlock_irqrestore(&p->lock, flags);

		अगर (p->flags & EBUS_DMA_FLAG_USE_EBDMA_HANDLER) अणु
			मुक्त_irq(p->irq, p);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ebus_dma_irq_enable);

व्योम ebus_dma_unरेजिस्टर(काष्ठा ebus_dma_info *p)
अणु
	अचिन्हित दीर्घ flags;
	u32 csr;
	पूर्णांक irq_on = 0;

	spin_lock_irqsave(&p->lock, flags);
	csr = पढ़ोl(p->regs + EBDMA_CSR);
	अगर (csr & EBDMA_CSR_INT_EN) अणु
		csr &= ~EBDMA_CSR_INT_EN;
		ग_लिखोl(csr, p->regs + EBDMA_CSR);
		irq_on = 1;
	पूर्ण
	spin_unlock_irqrestore(&p->lock, flags);

	अगर (irq_on)
		मुक्त_irq(p->irq, p);
पूर्ण
EXPORT_SYMBOL(ebus_dma_unरेजिस्टर);

पूर्णांक ebus_dma_request(काष्ठा ebus_dma_info *p, dma_addr_t bus_addr, माप_प्रकार len)
अणु
	अचिन्हित दीर्घ flags;
	u32 csr;
	पूर्णांक err;

	अगर (len >= (1 << 24))
		वापस -EINVAL;

	spin_lock_irqsave(&p->lock, flags);
	csr = पढ़ोl(p->regs + EBDMA_CSR);
	err = -EINVAL;
	अगर (!(csr & EBDMA_CSR_EN_DMA))
		जाओ out;
	err = -EBUSY;
	अगर (csr & EBDMA_CSR_NA_LOADED)
		जाओ out;

	ग_लिखोl(len,      p->regs + EBDMA_COUNT);
	ग_लिखोl(bus_addr, p->regs + EBDMA_ADDR);
	err = 0;

out:
	spin_unlock_irqrestore(&p->lock, flags);

	वापस err;
पूर्ण
EXPORT_SYMBOL(ebus_dma_request);

व्योम ebus_dma_prepare(काष्ठा ebus_dma_info *p, पूर्णांक ग_लिखो)
अणु
	अचिन्हित दीर्घ flags;
	u32 csr;

	spin_lock_irqsave(&p->lock, flags);
	__ebus_dma_reset(p, 0);

	csr = (EBDMA_CSR_INT_EN |
	       EBDMA_CSR_EN_CNT |
	       EBDMA_CSR_BURST_SZ_16 |
	       EBDMA_CSR_EN_NEXT);

	अगर (ग_लिखो)
		csr |= EBDMA_CSR_WRITE;
	अगर (p->flags & EBUS_DMA_FLAG_TCI_DISABLE)
		csr |= EBDMA_CSR_TCI_DIS;

	ग_लिखोl(csr, p->regs + EBDMA_CSR);

	spin_unlock_irqrestore(&p->lock, flags);
पूर्ण
EXPORT_SYMBOL(ebus_dma_prepare);

अचिन्हित पूर्णांक ebus_dma_residue(काष्ठा ebus_dma_info *p)
अणु
	वापस पढ़ोl(p->regs + EBDMA_COUNT);
पूर्ण
EXPORT_SYMBOL(ebus_dma_residue);

अचिन्हित पूर्णांक ebus_dma_addr(काष्ठा ebus_dma_info *p)
अणु
	वापस पढ़ोl(p->regs + EBDMA_ADDR);
पूर्ण
EXPORT_SYMBOL(ebus_dma_addr);

व्योम ebus_dma_enable(काष्ठा ebus_dma_info *p, पूर्णांक on)
अणु
	अचिन्हित दीर्घ flags;
	u32 orig_csr, csr;

	spin_lock_irqsave(&p->lock, flags);
	orig_csr = csr = पढ़ोl(p->regs + EBDMA_CSR);
	अगर (on)
		csr |= EBDMA_CSR_EN_DMA;
	अन्यथा
		csr &= ~EBDMA_CSR_EN_DMA;
	अगर ((orig_csr & EBDMA_CSR_EN_DMA) !=
	    (csr & EBDMA_CSR_EN_DMA))
		ग_लिखोl(csr, p->regs + EBDMA_CSR);
	spin_unlock_irqrestore(&p->lock, flags);
पूर्ण
EXPORT_SYMBOL(ebus_dma_enable);
