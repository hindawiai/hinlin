<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* jazz_esp.c: ESP front-end क्रम MIPS JAZZ प्रणालीs.
 *
 * Copyright (C) 2007 Thomas Bogendथघrfer (tsbogend@alpha.frankende)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/gfp.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dma.h>

#समावेश <यंत्र/jazz.h>
#समावेश <यंत्र/jazzdma.h>

#समावेश <scsi/scsi_host.h>

#समावेश "esp_scsi.h"

#घोषणा DRV_MODULE_NAME		"jazz_esp"
#घोषणा PFX DRV_MODULE_NAME	": "
#घोषणा DRV_VERSION		"1.000"
#घोषणा DRV_MODULE_RELDATE	"May 19, 2007"

अटल व्योम jazz_esp_ग_लिखो8(काष्ठा esp *esp, u8 val, अचिन्हित दीर्घ reg)
अणु
	*(अस्थिर u8 *)(esp->regs + reg) = val;
पूर्ण

अटल u8 jazz_esp_पढ़ो8(काष्ठा esp *esp, अचिन्हित दीर्घ reg)
अणु
	वापस *(अस्थिर u8 *)(esp->regs + reg);
पूर्ण

अटल पूर्णांक jazz_esp_irq_pending(काष्ठा esp *esp)
अणु
	अगर (jazz_esp_पढ़ो8(esp, ESP_STATUS) & ESP_STAT_INTR)
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम jazz_esp_reset_dma(काष्ठा esp *esp)
अणु
	vdma_disable ((पूर्णांक)esp->dma_regs);
पूर्ण

अटल व्योम jazz_esp_dma_drain(काष्ठा esp *esp)
अणु
	/* nothing to करो */
पूर्ण

अटल व्योम jazz_esp_dma_invalidate(काष्ठा esp *esp)
अणु
	vdma_disable ((पूर्णांक)esp->dma_regs);
पूर्ण

अटल व्योम jazz_esp_send_dma_cmd(काष्ठा esp *esp, u32 addr, u32 esp_count,
				  u32 dma_count, पूर्णांक ग_लिखो, u8 cmd)
अणु
	BUG_ON(!(cmd & ESP_CMD_DMA));

	jazz_esp_ग_लिखो8(esp, (esp_count >> 0) & 0xff, ESP_TCLOW);
	jazz_esp_ग_लिखो8(esp, (esp_count >> 8) & 0xff, ESP_TCMED);
	vdma_disable ((पूर्णांक)esp->dma_regs);
	अगर (ग_लिखो)
		vdma_set_mode ((पूर्णांक)esp->dma_regs, DMA_MODE_READ);
	अन्यथा
		vdma_set_mode ((पूर्णांक)esp->dma_regs, DMA_MODE_WRITE);

	vdma_set_addr ((पूर्णांक)esp->dma_regs, addr);
	vdma_set_count ((पूर्णांक)esp->dma_regs, dma_count);
	vdma_enable ((पूर्णांक)esp->dma_regs);

	scsi_esp_cmd(esp, cmd);
पूर्ण

अटल पूर्णांक jazz_esp_dma_error(काष्ठा esp *esp)
अणु
	u32 enable = vdma_get_enable((पूर्णांक)esp->dma_regs);

	अगर (enable & (R4030_MEM_INTR|R4030_ADDR_INTR))
		वापस 1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा esp_driver_ops jazz_esp_ops = अणु
	.esp_ग_लिखो8	=	jazz_esp_ग_लिखो8,
	.esp_पढ़ो8	=	jazz_esp_पढ़ो8,
	.irq_pending	=	jazz_esp_irq_pending,
	.reset_dma	=	jazz_esp_reset_dma,
	.dma_drain	=	jazz_esp_dma_drain,
	.dma_invalidate	=	jazz_esp_dma_invalidate,
	.send_dma_cmd	=	jazz_esp_send_dma_cmd,
	.dma_error	=	jazz_esp_dma_error,
पूर्ण;

अटल पूर्णांक esp_jazz_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा scsi_host_ढाँचा *tpnt = &scsi_esp_ढाँचा;
	काष्ठा Scsi_Host *host;
	काष्ठा esp *esp;
	काष्ठा resource *res;
	पूर्णांक err;

	host = scsi_host_alloc(tpnt, माप(काष्ठा esp));

	err = -ENOMEM;
	अगर (!host)
		जाओ fail;

	host->max_id = 8;
	esp = shost_priv(host);

	esp->host = host;
	esp->dev = &dev->dev;
	esp->ops = &jazz_esp_ops;

	res = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);
	अगर (!res)
		जाओ fail_unlink;

	esp->regs = (व्योम __iomem *)res->start;
	अगर (!esp->regs)
		जाओ fail_unlink;

	res = platक्रमm_get_resource(dev, IORESOURCE_MEM, 1);
	अगर (!res)
		जाओ fail_unlink;

	esp->dma_regs = (व्योम __iomem *)res->start;

	esp->command_block = dma_alloc_coherent(esp->dev, 16,
						&esp->command_block_dma,
						GFP_KERNEL);
	अगर (!esp->command_block)
		जाओ fail_unmap_regs;

	host->irq = err = platक्रमm_get_irq(dev, 0);
	अगर (err < 0)
		जाओ fail_unmap_command_block;
	err = request_irq(host->irq, scsi_esp_पूर्णांकr, IRQF_SHARED, "ESP", esp);
	अगर (err < 0)
		जाओ fail_unmap_command_block;

	esp->scsi_id = 7;
	esp->host->this_id = esp->scsi_id;
	esp->scsi_id_mask = (1 << esp->scsi_id);
	esp->cfreq = 40000000;

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
fail_unmap_regs:
fail_unlink:
	scsi_host_put(host);
fail:
	वापस err;
पूर्ण

अटल पूर्णांक esp_jazz_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा esp *esp = dev_get_drvdata(&dev->dev);
	अचिन्हित पूर्णांक irq = esp->host->irq;

	scsi_esp_unरेजिस्टर(esp);

	मुक्त_irq(irq, esp);
	dma_मुक्त_coherent(esp->dev, 16,
			  esp->command_block,
			  esp->command_block_dma);

	scsi_host_put(esp->host);

	वापस 0;
पूर्ण

/* work with hotplug and coldplug */
MODULE_ALIAS("platform:jazz_esp");

अटल काष्ठा platक्रमm_driver esp_jazz_driver = अणु
	.probe		= esp_jazz_probe,
	.हटाओ		= esp_jazz_हटाओ,
	.driver	= अणु
		.name	= "jazz_esp",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(esp_jazz_driver);

MODULE_DESCRIPTION("JAZZ ESP SCSI driver");
MODULE_AUTHOR("Thomas Bogendoerfer (tsbogend@alpha.franken.de)");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);
