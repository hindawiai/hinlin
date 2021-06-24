<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SH7760 DMABRG IRQ handling
 *
 * (c) 2007 MSC Vertriebsges.m.b.H, Manuel Lauss <mlau@msc-ge.com>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/dmabrg.h>
#समावेश <यंत्र/पन.स>

/*
 * The DMABRG is a special DMA unit within the SH7760. It करोes transfers
 * from USB-SRAM/Audio units to मुख्य memory (and also the LCDC; but that
 * part is sensibly placed  in the LCDC  रेजिस्टरs and requires no irqs)
 * It has 3 IRQ lines which trigger 10 events, and works independently
 * from the traditional SH DMAC (although it blocks usage of DMAC 0)
 *
 * BRGIRQID   | component | dir | meaning      | source
 * -----------------------------------------------------
 *     0      | USB-DMA   | ... | xfer करोne    | DMABRGI1
 *     1      | USB-UAE   | ... | USB addr err.| DMABRGI0
 *     2      | HAC0/SSI0 | play| all करोne     | DMABRGI1
 *     3      | HAC0/SSI0 | play| half करोne    | DMABRGI2
 *     4      | HAC0/SSI0 | rec | all करोne     | DMABRGI1
 *     5      | HAC0/SSI0 | rec | half करोne    | DMABRGI2
 *     6      | HAC1/SSI1 | play| all करोne     | DMABRGI1
 *     7      | HAC1/SSI1 | play| half करोne    | DMABRGI2
 *     8      | HAC1/SSI1 | rec | all करोne     | DMABRGI1
 *     9      | HAC1/SSI1 | rec | half करोne    | DMABRGI2
 *
 * all can be enabled/disabled in the DMABRGCR रेजिस्टर,
 * as well as checked अगर they occurred.
 *
 * DMABRGI0 services  USB  DMA  Address  errors,  but it still must be
 * enabled/acked in the DMABRGCR रेजिस्टर.  USB-DMA complete indicator
 * is grouped together with the audio buffer end indicators, too bad...
 *
 * DMABRGCR:	Bits 31-24: audio-dma ENABLE flags,
 *		Bits 23-16: audio-dma STATUS flags,
 *		Bits  9-8:  USB error/xfer ENABLE,
 *		Bits  1-0:  USB error/xfer STATUS.
 *	Ack an IRQ by writing 0 to the STATUS flag.
 *	Mask IRQ by writing 0 to ENABLE flag.
 *
 * Usage is almost like with any other IRQ:
 *  dmabrg_request_irq(BRGIRQID, handler, data)
 *  dmabrg_मुक्त_irq(BRGIRQID)
 *
 * handler prototype:  व्योम brgirqhandler(व्योम *data)
 */

#घोषणा DMARSRA		0xfe090000
#घोषणा DMAOR		0xffa00040
#घोषणा DMACHCR0	0xffa0000c
#घोषणा DMABRGCR	0xfe3c0000

#घोषणा DMAOR_BRG	0x0000c000
#घोषणा DMAOR_DMEN	0x00000001

#घोषणा DMABRGI0	68
#घोषणा DMABRGI1	69
#घोषणा DMABRGI2	70

काष्ठा dmabrg_handler अणु
	व्योम (*handler)(व्योम *);
	व्योम *data;
पूर्ण *dmabrg_handlers;

अटल अंतरभूत व्योम dmabrg_call_handler(पूर्णांक i)
अणु
	dmabrg_handlers[i].handler(dmabrg_handlers[i].data);
पूर्ण

/*
 * मुख्य DMABRG irq handler. It acks irqs and then
 * handles every set and unmasked bit sequentially.
 * No locking and no validity checks; it should be
 * as fast as possible (audio!)
 */
अटल irqवापस_t dmabrg_irq(पूर्णांक irq, व्योम *data)
अणु
	अचिन्हित दीर्घ dcr;
	अचिन्हित पूर्णांक i;

	dcr = __raw_पढ़ोl(DMABRGCR);
	__raw_ग_लिखोl(dcr & ~0x00ff0003, DMABRGCR);	/* ack all */
	dcr &= dcr >> 8;	/* ignore masked */

	/* USB stuff, get it out of the way first */
	अगर (dcr & 1)
		dmabrg_call_handler(DMABRGIRQ_USBDMA);
	अगर (dcr & 2)
		dmabrg_call_handler(DMABRGIRQ_USBDMAERR);

	/* Audio */
	dcr >>= 16;
	जबतक (dcr) अणु
		i = __ffs(dcr);
		dcr &= dcr - 1;
		dmabrg_call_handler(i + DMABRGIRQ_A0TXF);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम dmabrg_disable_irq(अचिन्हित पूर्णांक dmairq)
अणु
	अचिन्हित दीर्घ dcr;
	dcr = __raw_पढ़ोl(DMABRGCR);
	dcr &= ~(1 << ((dmairq > 1) ? dmairq + 22 : dmairq + 8));
	__raw_ग_लिखोl(dcr, DMABRGCR);
पूर्ण

अटल व्योम dmabrg_enable_irq(अचिन्हित पूर्णांक dmairq)
अणु
	अचिन्हित दीर्घ dcr;
	dcr = __raw_पढ़ोl(DMABRGCR);
	dcr |= (1 << ((dmairq > 1) ? dmairq + 22 : dmairq + 8));
	__raw_ग_लिखोl(dcr, DMABRGCR);
पूर्ण

पूर्णांक dmabrg_request_irq(अचिन्हित पूर्णांक dmairq, व्योम(*handler)(व्योम*),
		       व्योम *data)
अणु
	अगर ((dmairq > 9) || !handler)
		वापस -ENOENT;
	अगर (dmabrg_handlers[dmairq].handler)
		वापस -EBUSY;

	dmabrg_handlers[dmairq].handler = handler;
	dmabrg_handlers[dmairq].data = data;
	
	dmabrg_enable_irq(dmairq);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dmabrg_request_irq);

व्योम dmabrg_मुक्त_irq(अचिन्हित पूर्णांक dmairq)
अणु
	अगर (likely(dmairq < 10)) अणु
		dmabrg_disable_irq(dmairq);
		dmabrg_handlers[dmairq].handler = शून्य;
		dmabrg_handlers[dmairq].data = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(dmabrg_मुक्त_irq);

अटल पूर्णांक __init dmabrg_init(व्योम)
अणु
	अचिन्हित दीर्घ or;
	पूर्णांक ret;

	dmabrg_handlers = kसुस्मृति(10, माप(काष्ठा dmabrg_handler),
				  GFP_KERNEL);
	अगर (!dmabrg_handlers)
		वापस -ENOMEM;

#अगर_घोषित CONFIG_SH_DMA
	/* request DMAC channel 0 beक्रमe anyone अन्यथा can get it */
	ret = request_dma(0, "DMAC 0 (DMABRG)");
	अगर (ret < 0)
		prपूर्णांकk(KERN_INFO "DMABRG: DMAC ch0 not reserved!\n");
#पूर्ण_अगर

	__raw_ग_लिखोl(0, DMABRGCR);
	__raw_ग_लिखोl(0, DMACHCR0);
	__raw_ग_लिखोl(0x94000000, DMARSRA);	/* enable DMABRG in DMAC 0 */

	/* enable DMABRG mode, enable the DMAC */
	or = __raw_पढ़ोl(DMAOR);
	__raw_ग_लिखोl(or | DMAOR_BRG | DMAOR_DMEN, DMAOR);

	ret = request_irq(DMABRGI0, dmabrg_irq, 0,
			"DMABRG USB address error", शून्य);
	अगर (ret)
		जाओ out0;

	ret = request_irq(DMABRGI1, dmabrg_irq, 0,
			"DMABRG Transfer End", शून्य);
	अगर (ret)
		जाओ out1;

	ret = request_irq(DMABRGI2, dmabrg_irq, 0,
			"DMABRG Transfer Half", शून्य);
	अगर (ret == 0)
		वापस ret;

	मुक्त_irq(DMABRGI1, शून्य);
out1:	मुक्त_irq(DMABRGI0, शून्य);
out0:	kमुक्त(dmabrg_handlers);
	वापस ret;
पूर्ण
subsys_initcall(dmabrg_init);
