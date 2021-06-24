<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* sun_esp.c: ESP front-end क्रम Sparc SBUS प्रणालीs.
 *
 * Copyright (C) 2007, 2008 David S. Miller (davem@davemloft.net)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/gfp.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dma.h>

#समावेश <scsi/scsi_host.h>

#समावेश "esp_scsi.h"

#घोषणा DRV_MODULE_NAME		"sun_esp"
#घोषणा PFX DRV_MODULE_NAME	": "
#घोषणा DRV_VERSION		"1.100"
#घोषणा DRV_MODULE_RELDATE	"August 27, 2008"

#घोषणा dma_पढ़ो32(REG) \
	sbus_पढ़ोl(esp->dma_regs + (REG))
#घोषणा dma_ग_लिखो32(VAL, REG) \
	sbus_ग_लिखोl((VAL), esp->dma_regs + (REG))

/* DVMA chip revisions */
क्रमागत dvma_rev अणु
	dvmarev0,
	dvmaesc1,
	dvmarev1,
	dvmarev2,
	dvmarev3,
	dvmarevplus,
	dvmahme
पूर्ण;

अटल पूर्णांक esp_sbus_setup_dma(काष्ठा esp *esp, काष्ठा platक्रमm_device *dma_of)
अणु
	esp->dma = dma_of;

	esp->dma_regs = of_ioremap(&dma_of->resource[0], 0,
				   resource_size(&dma_of->resource[0]),
				   "espdma");
	अगर (!esp->dma_regs)
		वापस -ENOMEM;

	चयन (dma_पढ़ो32(DMA_CSR) & DMA_DEVICE_ID) अणु
	हाल DMA_VERS0:
		esp->dmarev = dvmarev0;
		अवरोध;
	हाल DMA_ESCV1:
		esp->dmarev = dvmaesc1;
		अवरोध;
	हाल DMA_VERS1:
		esp->dmarev = dvmarev1;
		अवरोध;
	हाल DMA_VERS2:
		esp->dmarev = dvmarev2;
		अवरोध;
	हाल DMA_VERHME:
		esp->dmarev = dvmahme;
		अवरोध;
	हाल DMA_VERSPLUS:
		esp->dmarev = dvmarevplus;
		अवरोध;
	पूर्ण

	वापस 0;

पूर्ण

अटल पूर्णांक esp_sbus_map_regs(काष्ठा esp *esp, पूर्णांक hme)
अणु
	काष्ठा platक्रमm_device *op = to_platक्रमm_device(esp->dev);
	काष्ठा resource *res;

	/* On HME, two reg sets exist, first is DVMA,
	 * second is ESP रेजिस्टरs.
	 */
	अगर (hme)
		res = &op->resource[1];
	अन्यथा
		res = &op->resource[0];

	esp->regs = of_ioremap(res, 0, SBUS_ESP_REG_SIZE, "ESP");
	अगर (!esp->regs)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक esp_sbus_map_command_block(काष्ठा esp *esp)
अणु
	esp->command_block = dma_alloc_coherent(esp->dev, 16,
						&esp->command_block_dma,
						GFP_KERNEL);
	अगर (!esp->command_block)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल पूर्णांक esp_sbus_रेजिस्टर_irq(काष्ठा esp *esp)
अणु
	काष्ठा Scsi_Host *host = esp->host;
	काष्ठा platक्रमm_device *op = to_platक्रमm_device(esp->dev);

	host->irq = op->archdata.irqs[0];
	वापस request_irq(host->irq, scsi_esp_पूर्णांकr, IRQF_SHARED, "ESP", esp);
पूर्ण

अटल व्योम esp_get_scsi_id(काष्ठा esp *esp, काष्ठा platक्रमm_device *espdma)
अणु
	काष्ठा platक्रमm_device *op = to_platक्रमm_device(esp->dev);
	काष्ठा device_node *dp;

	dp = op->dev.of_node;
	esp->scsi_id = of_getपूर्णांकprop_शेष(dp, "initiator-id", 0xff);
	अगर (esp->scsi_id != 0xff)
		जाओ करोne;

	esp->scsi_id = of_getपूर्णांकprop_शेष(dp, "scsi-initiator-id", 0xff);
	अगर (esp->scsi_id != 0xff)
		जाओ करोne;

	esp->scsi_id = of_getपूर्णांकprop_शेष(espdma->dev.of_node,
					     "scsi-initiator-id", 7);

करोne:
	esp->host->this_id = esp->scsi_id;
	esp->scsi_id_mask = (1 << esp->scsi_id);
पूर्ण

अटल व्योम esp_get_dअगरferential(काष्ठा esp *esp)
अणु
	काष्ठा platक्रमm_device *op = to_platक्रमm_device(esp->dev);
	काष्ठा device_node *dp;

	dp = op->dev.of_node;
	अगर (of_find_property(dp, "differential", शून्य))
		esp->flags |= ESP_FLAG_DIFFERENTIAL;
	अन्यथा
		esp->flags &= ~ESP_FLAG_DIFFERENTIAL;
पूर्ण

अटल व्योम esp_get_घड़ी_params(काष्ठा esp *esp)
अणु
	काष्ठा platक्रमm_device *op = to_platक्रमm_device(esp->dev);
	काष्ठा device_node *bus_dp, *dp;
	पूर्णांक fmhz;

	dp = op->dev.of_node;
	bus_dp = dp->parent;

	fmhz = of_getपूर्णांकprop_शेष(dp, "clock-frequency", 0);
	अगर (fmhz == 0)
		fmhz = of_getपूर्णांकprop_शेष(bus_dp, "clock-frequency", 0);

	esp->cfreq = fmhz;
पूर्ण

अटल व्योम esp_get_bursts(काष्ठा esp *esp, काष्ठा platक्रमm_device *dma_of)
अणु
	काष्ठा device_node *dma_dp = dma_of->dev.of_node;
	काष्ठा platक्रमm_device *op = to_platक्रमm_device(esp->dev);
	काष्ठा device_node *dp;
	u8 bursts, val;

	dp = op->dev.of_node;
	bursts = of_getपूर्णांकprop_शेष(dp, "burst-sizes", 0xff);
	val = of_getपूर्णांकprop_शेष(dma_dp, "burst-sizes", 0xff);
	अगर (val != 0xff)
		bursts &= val;

	val = of_getपूर्णांकprop_शेष(dma_dp->parent, "burst-sizes", 0xff);
	अगर (val != 0xff)
		bursts &= val;

	अगर (bursts == 0xff ||
	    (bursts & DMA_BURST16) == 0 ||
	    (bursts & DMA_BURST32) == 0)
		bursts = (DMA_BURST32 - 1);

	esp->bursts = bursts;
पूर्ण

अटल व्योम esp_sbus_get_props(काष्ठा esp *esp, काष्ठा platक्रमm_device *espdma)
अणु
	esp_get_scsi_id(esp, espdma);
	esp_get_dअगरferential(esp);
	esp_get_घड़ी_params(esp);
	esp_get_bursts(esp, espdma);
पूर्ण

अटल व्योम sbus_esp_ग_लिखो8(काष्ठा esp *esp, u8 val, अचिन्हित दीर्घ reg)
अणु
	sbus_ग_लिखोb(val, esp->regs + (reg * 4UL));
पूर्ण

अटल u8 sbus_esp_पढ़ो8(काष्ठा esp *esp, अचिन्हित दीर्घ reg)
अणु
	वापस sbus_पढ़ोb(esp->regs + (reg * 4UL));
पूर्ण

अटल पूर्णांक sbus_esp_irq_pending(काष्ठा esp *esp)
अणु
	अगर (dma_पढ़ो32(DMA_CSR) & (DMA_HNDL_INTR | DMA_HNDL_ERROR))
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम sbus_esp_reset_dma(काष्ठा esp *esp)
अणु
	पूर्णांक can_करो_burst16, can_करो_burst32, can_करो_burst64;
	पूर्णांक can_करो_sbus64, lim;
	काष्ठा platक्रमm_device *op = to_platक्रमm_device(esp->dev);
	u32 val;

	can_करो_burst16 = (esp->bursts & DMA_BURST16) != 0;
	can_करो_burst32 = (esp->bursts & DMA_BURST32) != 0;
	can_करो_burst64 = 0;
	can_करो_sbus64 = 0;
	अगर (sbus_can_dma_64bit())
		can_करो_sbus64 = 1;
	अगर (sbus_can_burst64())
		can_करो_burst64 = (esp->bursts & DMA_BURST64) != 0;

	/* Put the DVMA पूर्णांकo a known state. */
	अगर (esp->dmarev != dvmahme) अणु
		val = dma_पढ़ो32(DMA_CSR);
		dma_ग_लिखो32(val | DMA_RST_SCSI, DMA_CSR);
		dma_ग_लिखो32(val & ~DMA_RST_SCSI, DMA_CSR);
	पूर्ण
	चयन (esp->dmarev) अणु
	हाल dvmahme:
		dma_ग_लिखो32(DMA_RESET_FAS366, DMA_CSR);
		dma_ग_लिखो32(DMA_RST_SCSI, DMA_CSR);

		esp->prev_hme_dmacsr = (DMA_PARITY_OFF | DMA_2CLKS |
					DMA_SCSI_DISAB | DMA_INT_ENAB);

		esp->prev_hme_dmacsr &= ~(DMA_ENABLE | DMA_ST_WRITE |
					  DMA_BRST_SZ);

		अगर (can_करो_burst64)
			esp->prev_hme_dmacsr |= DMA_BRST64;
		अन्यथा अगर (can_करो_burst32)
			esp->prev_hme_dmacsr |= DMA_BRST32;

		अगर (can_करो_sbus64) अणु
			esp->prev_hme_dmacsr |= DMA_SCSI_SBUS64;
			sbus_set_sbus64(&op->dev, esp->bursts);
		पूर्ण

		lim = 1000;
		जबतक (dma_पढ़ो32(DMA_CSR) & DMA_PEND_READ) अणु
			अगर (--lim == 0) अणु
				prपूर्णांकk(KERN_ALERT PFX "esp%d: DMA_PEND_READ "
				       "will not clear!\n",
				       esp->host->unique_id);
				अवरोध;
			पूर्ण
			udelay(1);
		पूर्ण

		dma_ग_लिखो32(0, DMA_CSR);
		dma_ग_लिखो32(esp->prev_hme_dmacsr, DMA_CSR);

		dma_ग_लिखो32(0, DMA_ADDR);
		अवरोध;

	हाल dvmarev2:
		अगर (esp->rev != ESP100) अणु
			val = dma_पढ़ो32(DMA_CSR);
			dma_ग_लिखो32(val | DMA_3CLKS, DMA_CSR);
		पूर्ण
		अवरोध;

	हाल dvmarev3:
		val = dma_पढ़ो32(DMA_CSR);
		val &= ~DMA_3CLKS;
		val |= DMA_2CLKS;
		अगर (can_करो_burst32) अणु
			val &= ~DMA_BRST_SZ;
			val |= DMA_BRST32;
		पूर्ण
		dma_ग_लिखो32(val, DMA_CSR);
		अवरोध;

	हाल dvmaesc1:
		val = dma_पढ़ो32(DMA_CSR);
		val |= DMA_ADD_ENABLE;
		val &= ~DMA_BCNT_ENAB;
		अगर (!can_करो_burst32 && can_करो_burst16) अणु
			val |= DMA_ESC_BURST;
		पूर्ण अन्यथा अणु
			val &= ~(DMA_ESC_BURST);
		पूर्ण
		dma_ग_लिखो32(val, DMA_CSR);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	/* Enable पूर्णांकerrupts.  */
	val = dma_पढ़ो32(DMA_CSR);
	dma_ग_लिखो32(val | DMA_INT_ENAB, DMA_CSR);
पूर्ण

अटल व्योम sbus_esp_dma_drain(काष्ठा esp *esp)
अणु
	u32 csr;
	पूर्णांक lim;

	अगर (esp->dmarev == dvmahme)
		वापस;

	csr = dma_पढ़ो32(DMA_CSR);
	अगर (!(csr & DMA_FIFO_ISDRAIN))
		वापस;

	अगर (esp->dmarev != dvmarev3 && esp->dmarev != dvmaesc1)
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

अटल व्योम sbus_esp_dma_invalidate(काष्ठा esp *esp)
अणु
	अगर (esp->dmarev == dvmahme) अणु
		dma_ग_लिखो32(DMA_RST_SCSI, DMA_CSR);

		esp->prev_hme_dmacsr = ((esp->prev_hme_dmacsr |
					 (DMA_PARITY_OFF | DMA_2CLKS |
					  DMA_SCSI_DISAB | DMA_INT_ENAB)) &
					~(DMA_ST_WRITE | DMA_ENABLE));

		dma_ग_लिखो32(0, DMA_CSR);
		dma_ग_लिखो32(esp->prev_hme_dmacsr, DMA_CSR);

		/* This is necessary to aव्योम having the SCSI channel
		 * engine lock up on us.
		 */
		dma_ग_लिखो32(0, DMA_ADDR);
	पूर्ण अन्यथा अणु
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
पूर्ण

अटल व्योम sbus_esp_send_dma_cmd(काष्ठा esp *esp, u32 addr, u32 esp_count,
				  u32 dma_count, पूर्णांक ग_लिखो, u8 cmd)
अणु
	u32 csr;

	BUG_ON(!(cmd & ESP_CMD_DMA));

	sbus_esp_ग_लिखो8(esp, (esp_count >> 0) & 0xff, ESP_TCLOW);
	sbus_esp_ग_लिखो8(esp, (esp_count >> 8) & 0xff, ESP_TCMED);
	अगर (esp->rev == FASHME) अणु
		sbus_esp_ग_लिखो8(esp, (esp_count >> 16) & 0xff, FAS_RLO);
		sbus_esp_ग_लिखो8(esp, 0, FAS_RHI);

		scsi_esp_cmd(esp, cmd);

		csr = esp->prev_hme_dmacsr;
		csr |= DMA_SCSI_DISAB | DMA_ENABLE;
		अगर (ग_लिखो)
			csr |= DMA_ST_WRITE;
		अन्यथा
			csr &= ~DMA_ST_WRITE;
		esp->prev_hme_dmacsr = csr;

		dma_ग_लिखो32(dma_count, DMA_COUNT);
		dma_ग_लिखो32(addr, DMA_ADDR);
		dma_ग_लिखो32(csr, DMA_CSR);
	पूर्ण अन्यथा अणु
		csr = dma_पढ़ो32(DMA_CSR);
		csr |= DMA_ENABLE;
		अगर (ग_लिखो)
			csr |= DMA_ST_WRITE;
		अन्यथा
			csr &= ~DMA_ST_WRITE;
		dma_ग_लिखो32(csr, DMA_CSR);
		अगर (esp->dmarev == dvmaesc1) अणु
			u32 end = PAGE_ALIGN(addr + dma_count + 16U);
			dma_ग_लिखो32(end - addr, DMA_COUNT);
		पूर्ण
		dma_ग_लिखो32(addr, DMA_ADDR);

		scsi_esp_cmd(esp, cmd);
	पूर्ण

पूर्ण

अटल पूर्णांक sbus_esp_dma_error(काष्ठा esp *esp)
अणु
	u32 csr = dma_पढ़ो32(DMA_CSR);

	अगर (csr & DMA_HNDL_ERROR)
		वापस 1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा esp_driver_ops sbus_esp_ops = अणु
	.esp_ग_लिखो8	=	sbus_esp_ग_लिखो8,
	.esp_पढ़ो8	=	sbus_esp_पढ़ो8,
	.irq_pending	=	sbus_esp_irq_pending,
	.reset_dma	=	sbus_esp_reset_dma,
	.dma_drain	=	sbus_esp_dma_drain,
	.dma_invalidate	=	sbus_esp_dma_invalidate,
	.send_dma_cmd	=	sbus_esp_send_dma_cmd,
	.dma_error	=	sbus_esp_dma_error,
पूर्ण;

अटल पूर्णांक esp_sbus_probe_one(काष्ठा platक्रमm_device *op,
			      काष्ठा platक्रमm_device *espdma, पूर्णांक hme)
अणु
	काष्ठा scsi_host_ढाँचा *tpnt = &scsi_esp_ढाँचा;
	काष्ठा Scsi_Host *host;
	काष्ठा esp *esp;
	पूर्णांक err;

	host = scsi_host_alloc(tpnt, माप(काष्ठा esp));

	err = -ENOMEM;
	अगर (!host)
		जाओ fail;

	host->max_id = (hme ? 16 : 8);
	esp = shost_priv(host);

	esp->host = host;
	esp->dev = &op->dev;
	esp->ops = &sbus_esp_ops;

	अगर (hme)
		esp->flags |= ESP_FLAG_WIDE_CAPABLE;

	err = esp_sbus_setup_dma(esp, espdma);
	अगर (err < 0)
		जाओ fail_unlink;

	err = esp_sbus_map_regs(esp, hme);
	अगर (err < 0)
		जाओ fail_unlink;

	err = esp_sbus_map_command_block(esp);
	अगर (err < 0)
		जाओ fail_unmap_regs;

	err = esp_sbus_रेजिस्टर_irq(esp);
	अगर (err < 0)
		जाओ fail_unmap_command_block;

	esp_sbus_get_props(esp, espdma);

	/* Beक्रमe we try to touch the ESP chip, ESC1 dma can
	 * come up with the reset bit set, so make sure that
	 * is clear first.
	 */
	अगर (esp->dmarev == dvmaesc1) अणु
		u32 val = dma_पढ़ो32(DMA_CSR);

		dma_ग_लिखो32(val & ~DMA_RST_SCSI, DMA_CSR);
	पूर्ण

	dev_set_drvdata(&op->dev, esp);

	err = scsi_esp_रेजिस्टर(esp);
	अगर (err)
		जाओ fail_मुक्त_irq;

	वापस 0;

fail_मुक्त_irq:
	मुक्त_irq(host->irq, esp);
fail_unmap_command_block:
	dma_मुक्त_coherent(&op->dev, 16,
			  esp->command_block,
			  esp->command_block_dma);
fail_unmap_regs:
	of_iounmap(&op->resource[(hme ? 1 : 0)], esp->regs, SBUS_ESP_REG_SIZE);
fail_unlink:
	scsi_host_put(host);
fail:
	वापस err;
पूर्ण

अटल पूर्णांक esp_sbus_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा device_node *dma_node = शून्य;
	काष्ठा device_node *dp = op->dev.of_node;
	काष्ठा platक्रमm_device *dma_of = शून्य;
	पूर्णांक hme = 0;
	पूर्णांक ret;

	अगर (of_node_name_eq(dp->parent, "espdma") ||
	    of_node_name_eq(dp->parent, "dma"))
		dma_node = dp->parent;
	अन्यथा अगर (of_node_name_eq(dp, "SUNW,fas")) अणु
		dma_node = op->dev.of_node;
		hme = 1;
	पूर्ण
	अगर (dma_node)
		dma_of = of_find_device_by_node(dma_node);
	अगर (!dma_of)
		वापस -ENODEV;

	ret = esp_sbus_probe_one(op, dma_of, hme);
	अगर (ret)
		put_device(&dma_of->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक esp_sbus_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा esp *esp = dev_get_drvdata(&op->dev);
	काष्ठा platक्रमm_device *dma_of = esp->dma;
	अचिन्हित पूर्णांक irq = esp->host->irq;
	bool is_hme;
	u32 val;

	scsi_esp_unरेजिस्टर(esp);

	/* Disable पूर्णांकerrupts.  */
	val = dma_पढ़ो32(DMA_CSR);
	dma_ग_लिखो32(val & ~DMA_INT_ENAB, DMA_CSR);

	मुक्त_irq(irq, esp);

	is_hme = (esp->dmarev == dvmahme);

	dma_मुक्त_coherent(&op->dev, 16,
			  esp->command_block,
			  esp->command_block_dma);
	of_iounmap(&op->resource[(is_hme ? 1 : 0)], esp->regs,
		   SBUS_ESP_REG_SIZE);
	of_iounmap(&dma_of->resource[0], esp->dma_regs,
		   resource_size(&dma_of->resource[0]));

	scsi_host_put(esp->host);

	dev_set_drvdata(&op->dev, शून्य);

	put_device(&dma_of->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id esp_match[] = अणु
	अणु
		.name = "SUNW,esp",
	पूर्ण,
	अणु
		.name = "SUNW,fas",
	पूर्ण,
	अणु
		.name = "esp",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, esp_match);

अटल काष्ठा platक्रमm_driver esp_sbus_driver = अणु
	.driver = अणु
		.name = "esp",
		.of_match_table = esp_match,
	पूर्ण,
	.probe		= esp_sbus_probe,
	.हटाओ		= esp_sbus_हटाओ,
पूर्ण;
module_platक्रमm_driver(esp_sbus_driver);

MODULE_DESCRIPTION("Sun ESP SCSI driver");
MODULE_AUTHOR("David S. Miller (davem@davemloft.net)");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);
