<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* sun3x_esp.c: ESP front-end क्रम Sun3x प्रणालीs.
 *
 * Copyright (C) 2007,2008 Thomas Bogenकरोerfer (tsbogend@alpha.franken.de)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/gfp.h>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/sun3x.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/dvma.h>

/* DMA controller reg offsets */
#घोषणा DMA_CSR		0x00UL	/* rw  DMA control/status रेजिस्टर    0x00   */
#घोषणा DMA_ADDR        0x04UL	/* rw  DMA transfer address रेजिस्टर  0x04   */
#घोषणा DMA_COUNT       0x08UL	/* rw  DMA transfer count रेजिस्टर    0x08   */
#घोषणा DMA_TEST        0x0cUL	/* rw  DMA test/debug रेजिस्टर        0x0c   */

#समावेश <scsi/scsi_host.h>

#समावेश "esp_scsi.h"

#घोषणा DRV_MODULE_NAME		"sun3x_esp"
#घोषणा PFX DRV_MODULE_NAME	": "
#घोषणा DRV_VERSION		"1.000"
#घोषणा DRV_MODULE_RELDATE	"Nov 1, 2007"

/*
 * m68k always assumes पढ़ोl/ग_लिखोl operate on little endian
 * mmio space; this is wrong at least क्रम Sun3x, so we
 * need to workaround this until a proper way is found
 */
#अगर 0
#घोषणा dma_पढ़ो32(REG) \
	पढ़ोl(esp->dma_regs + (REG))
#घोषणा dma_ग_लिखो32(VAL, REG) \
	ग_लिखोl((VAL), esp->dma_regs + (REG))
#अन्यथा
#घोषणा dma_पढ़ो32(REG) \
	*(अस्थिर u32 *)(esp->dma_regs + (REG))
#घोषणा dma_ग_लिखो32(VAL, REG) \
	करो अणु *(अस्थिर u32 *)(esp->dma_regs + (REG)) = (VAL); पूर्ण जबतक (0)
#पूर्ण_अगर

अटल व्योम sun3x_esp_ग_लिखो8(काष्ठा esp *esp, u8 val, अचिन्हित दीर्घ reg)
अणु
	ग_लिखोb(val, esp->regs + (reg * 4UL));
पूर्ण

अटल u8 sun3x_esp_पढ़ो8(काष्ठा esp *esp, अचिन्हित दीर्घ reg)
अणु
	वापस पढ़ोb(esp->regs + (reg * 4UL));
पूर्ण

अटल पूर्णांक sun3x_esp_irq_pending(काष्ठा esp *esp)
अणु
	अगर (dma_पढ़ो32(DMA_CSR) & (DMA_HNDL_INTR | DMA_HNDL_ERROR))
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम sun3x_esp_reset_dma(काष्ठा esp *esp)
अणु
	u32 val;

	val = dma_पढ़ो32(DMA_CSR);
	dma_ग_लिखो32(val | DMA_RST_SCSI, DMA_CSR);
	dma_ग_लिखो32(val & ~DMA_RST_SCSI, DMA_CSR);

	/* Enable पूर्णांकerrupts.  */
	val = dma_पढ़ो32(DMA_CSR);
	dma_ग_लिखो32(val | DMA_INT_ENAB, DMA_CSR);
पूर्ण

अटल व्योम sun3x_esp_dma_drain(काष्ठा esp *esp)
अणु
	u32 csr;
	पूर्णांक lim;

	csr = dma_पढ़ो32(DMA_CSR);
	अगर (!(csr & DMA_FIFO_ISDRAIN))
		वापस;

	dma_ग_लिखो32(csr | DMA_FIFO_STDRAIN, DMA_CSR);

	lim = 1000;
	जबतक (dma_पढ़ो32(DMA_CSR) & DMA_FIFO_ISDRAIN) अणु
		अगर (--lim == 0) अणु
			prपूर्णांकk(KERN_ALERT PFX "esp%d: DMA will not drain!\n",
			       esp->host->unique_id);
			अवरोध;
		पूर्ण
		udelay(1);
	पूर्ण
पूर्ण

अटल व्योम sun3x_esp_dma_invalidate(काष्ठा esp *esp)
अणु
	u32 val;
	पूर्णांक lim;

	lim = 1000;
	जबतक ((val = dma_पढ़ो32(DMA_CSR)) & DMA_PEND_READ) अणु
		अगर (--lim == 0) अणु
			prपूर्णांकk(KERN_ALERT PFX "esp%d: DMA will not "
			       "invalidate!\n", esp->host->unique_id);
			अवरोध;
		पूर्ण
		udelay(1);
	पूर्ण

	val &= ~(DMA_ENABLE | DMA_ST_WRITE | DMA_BCNT_ENAB);
	val |= DMA_FIFO_INV;
	dma_ग_लिखो32(val, DMA_CSR);
	val &= ~DMA_FIFO_INV;
	dma_ग_लिखो32(val, DMA_CSR);
पूर्ण

अटल व्योम sun3x_esp_send_dma_cmd(काष्ठा esp *esp, u32 addr, u32 esp_count,
				  u32 dma_count, पूर्णांक ग_लिखो, u8 cmd)
अणु
	u32 csr;

	BUG_ON(!(cmd & ESP_CMD_DMA));

	sun3x_esp_ग_लिखो8(esp, (esp_count >> 0) & 0xff, ESP_TCLOW);
	sun3x_esp_ग_लिखो8(esp, (esp_count >> 8) & 0xff, ESP_TCMED);
	csr = dma_पढ़ो32(DMA_CSR);
	csr |= DMA_ENABLE;
	अगर (ग_लिखो)
		csr |= DMA_ST_WRITE;
	अन्यथा
		csr &= ~DMA_ST_WRITE;
	dma_ग_लिखो32(csr, DMA_CSR);
	dma_ग_लिखो32(addr, DMA_ADDR);

	scsi_esp_cmd(esp, cmd);
पूर्ण

अटल पूर्णांक sun3x_esp_dma_error(काष्ठा esp *esp)
अणु
	u32 csr = dma_पढ़ो32(DMA_CSR);

	अगर (csr & DMA_HNDL_ERROR)
		वापस 1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा esp_driver_ops sun3x_esp_ops = अणु
	.esp_ग_लिखो8	=	sun3x_esp_ग_लिखो8,
	.esp_पढ़ो8	=	sun3x_esp_पढ़ो8,
	.irq_pending	=	sun3x_esp_irq_pending,
	.reset_dma	=	sun3x_esp_reset_dma,
	.dma_drain	=	sun3x_esp_dma_drain,
	.dma_invalidate	=	sun3x_esp_dma_invalidate,
	.send_dma_cmd	=	sun3x_esp_send_dma_cmd,
	.dma_error	=	sun3x_esp_dma_error,
पूर्ण;

अटल पूर्णांक esp_sun3x_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा scsi_host_ढाँचा *tpnt = &scsi_esp_ढाँचा;
	काष्ठा Scsi_Host *host;
	काष्ठा esp *esp;
	काष्ठा resource *res;
	पूर्णांक err = -ENOMEM;

	host = scsi_host_alloc(tpnt, माप(काष्ठा esp));
	अगर (!host)
		जाओ fail;

	host->max_id = 8;
	esp = shost_priv(host);

	esp->host = host;
	esp->dev = &dev->dev;
	esp->ops = &sun3x_esp_ops;

	res = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);
	अगर (!res || !res->start)
		जाओ fail_unlink;

	esp->regs = ioremap(res->start, 0x20);
	अगर (!esp->regs)
		जाओ fail_unmap_regs;

	res = platक्रमm_get_resource(dev, IORESOURCE_MEM, 1);
	अगर (!res || !res->start)
		जाओ fail_unmap_regs;

	esp->dma_regs = ioremap(res->start, 0x10);

	esp->command_block = dma_alloc_coherent(esp->dev, 16,
						&esp->command_block_dma,
						GFP_KERNEL);
	अगर (!esp->command_block)
		जाओ fail_unmap_regs_dma;

	host->irq = err = platक्रमm_get_irq(dev, 0);
	अगर (err < 0)
		जाओ fail_unmap_command_block;
	err = request_irq(host->irq, scsi_esp_पूर्णांकr, IRQF_SHARED,
			  "SUN3X ESP", esp);
	अगर (err < 0)
		जाओ fail_unmap_command_block;

	esp->scsi_id = 7;
	esp->host->this_id = esp->scsi_id;
	esp->scsi_id_mask = (1 << esp->scsi_id);
	esp->cfreq = 20000000;

	dev_set_drvdata(&dev->dev, esp);

	err = scsi_esp_रेजिस्टर(esp);
	अगर (err)
		जाओ fail_मुक्त_irq;

	वापस 0;

fail_मुक्त_irq:
	मुक्त_irq(host->irq, esp);
fail_unmap_command_block:
	dma_मुक्त_coherent(esp->dev, 16,
			  esp->command_block,
			  esp->command_block_dma);
fail_unmap_regs_dma:
	iounmap(esp->dma_regs);
fail_unmap_regs:
	iounmap(esp->regs);
fail_unlink:
	scsi_host_put(host);
fail:
	वापस err;
पूर्ण

अटल पूर्णांक esp_sun3x_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा esp *esp = dev_get_drvdata(&dev->dev);
	अचिन्हित पूर्णांक irq = esp->host->irq;
	u32 val;

	scsi_esp_unरेजिस्टर(esp);

	/* Disable पूर्णांकerrupts.  */
	val = dma_पढ़ो32(DMA_CSR);
	dma_ग_लिखो32(val & ~DMA_INT_ENAB, DMA_CSR);

	मुक्त_irq(irq, esp);
	dma_मुक्त_coherent(esp->dev, 16,
			  esp->command_block,
			  esp->command_block_dma);

	scsi_host_put(esp->host);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver esp_sun3x_driver = अणु
	.probe          = esp_sun3x_probe,
	.हटाओ         = esp_sun3x_हटाओ,
	.driver = अणु
		.name   = "sun3x_esp",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(esp_sun3x_driver);

MODULE_DESCRIPTION("Sun3x ESP SCSI driver");
MODULE_AUTHOR("Thomas Bogendoerfer (tsbogend@alpha.franken.de)");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);
MODULE_ALIAS("platform:sun3x_esp");
