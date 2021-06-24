<शैली गुरु>
/*
 * Programmable Real-Time Unit Sub System (PRUSS) UIO driver (uio_pruss)
 *
 * This driver exports PRUSS host event out पूर्णांकerrupts and PRUSS, L3 RAM,
 * and DDR RAM to user space क्रम applications पूर्णांकeracting with PRUSS firmware
 *
 * Copyright (C) 2010-11 Texas Instruments Incorporated - http://www.ti.com/
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/uio_driver.h>
#समावेश <linux/platक्रमm_data/uio_pruss.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>
#समावेश <linux/genभाग.स>

#घोषणा DRV_NAME "pruss_uio"
#घोषणा DRV_VERSION "1.0"

अटल पूर्णांक sram_pool_sz = SZ_16K;
module_param(sram_pool_sz, पूर्णांक, 0);
MODULE_PARM_DESC(sram_pool_sz, "sram pool size to allocate ");

अटल पूर्णांक extram_pool_sz = SZ_256K;
module_param(extram_pool_sz, पूर्णांक, 0);
MODULE_PARM_DESC(extram_pool_sz, "external ram pool size to allocate");

/*
 * Host event IRQ numbers from PRUSS - PRUSS can generate up to 8 पूर्णांकerrupt
 * events to AINTC of ARM host processor - which can be used क्रम IPC b/w PRUSS
 * firmware and user space application, async notअगरication from PRU firmware
 * to user space application
 * 3	PRU_EVTOUT0
 * 4	PRU_EVTOUT1
 * 5	PRU_EVTOUT2
 * 6	PRU_EVTOUT3
 * 7	PRU_EVTOUT4
 * 8	PRU_EVTOUT5
 * 9	PRU_EVTOUT6
 * 10	PRU_EVTOUT7
*/
#घोषणा MAX_PRUSS_EVT	8

#घोषणा PINTC_HIDISR	0x0038
#घोषणा PINTC_HIPIR	0x0900
#घोषणा HIPIR_NOPEND	0x80000000
#घोषणा PINTC_HIER	0x1500

काष्ठा uio_pruss_dev अणु
	काष्ठा uio_info *info;
	काष्ठा clk *pruss_clk;
	dma_addr_t sram_paddr;
	dma_addr_t ddr_paddr;
	व्योम __iomem *prussio_vaddr;
	अचिन्हित दीर्घ sram_vaddr;
	व्योम *ddr_vaddr;
	अचिन्हित पूर्णांक hostirq_start;
	अचिन्हित पूर्णांक pपूर्णांकc_base;
	काष्ठा gen_pool *sram_pool;
पूर्ण;

अटल irqवापस_t pruss_handler(पूर्णांक irq, काष्ठा uio_info *info)
अणु
	काष्ठा uio_pruss_dev *gdev = info->priv;
	पूर्णांक पूर्णांकr_bit = (irq - gdev->hostirq_start + 2);
	पूर्णांक val, पूर्णांकr_mask = (1 << पूर्णांकr_bit);
	व्योम __iomem *base = gdev->prussio_vaddr + gdev->pपूर्णांकc_base;
	व्योम __iomem *पूर्णांकren_reg = base + PINTC_HIER;
	व्योम __iomem *पूर्णांकrdis_reg = base + PINTC_HIDISR;
	व्योम __iomem *पूर्णांकrstat_reg = base + PINTC_HIPIR + (पूर्णांकr_bit << 2);

	val = ioपढ़ो32(पूर्णांकren_reg);
	/* Is पूर्णांकerrupt enabled and active ? */
	अगर (!(val & पूर्णांकr_mask) && (ioपढ़ो32(पूर्णांकrstat_reg) & HIPIR_NOPEND))
		वापस IRQ_NONE;
	/* Disable पूर्णांकerrupt */
	ioग_लिखो32(पूर्णांकr_bit, पूर्णांकrdis_reg);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम pruss_cleanup(काष्ठा device *dev, काष्ठा uio_pruss_dev *gdev)
अणु
	पूर्णांक cnt;
	काष्ठा uio_info *p = gdev->info;

	क्रम (cnt = 0; cnt < MAX_PRUSS_EVT; cnt++, p++) अणु
		uio_unरेजिस्टर_device(p);
	पूर्ण
	iounmap(gdev->prussio_vaddr);
	अगर (gdev->ddr_vaddr) अणु
		dma_मुक्त_coherent(dev, extram_pool_sz, gdev->ddr_vaddr,
			gdev->ddr_paddr);
	पूर्ण
	अगर (gdev->sram_vaddr)
		gen_pool_मुक्त(gdev->sram_pool,
			      gdev->sram_vaddr,
			      sram_pool_sz);
	clk_disable(gdev->pruss_clk);
पूर्ण

अटल पूर्णांक pruss_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uio_info *p;
	काष्ठा uio_pruss_dev *gdev;
	काष्ठा resource *regs_prussio;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret, cnt, i, len;
	काष्ठा uio_pruss_pdata *pdata = dev_get_platdata(dev);

	gdev = devm_kzalloc(dev, माप(काष्ठा uio_pruss_dev), GFP_KERNEL);
	अगर (!gdev)
		वापस -ENOMEM;

	gdev->info = devm_kसुस्मृति(dev, MAX_PRUSS_EVT, माप(*p), GFP_KERNEL);
	अगर (!gdev->info)
		वापस -ENOMEM;

	/* Power on PRU in हाल its not करोne as part of boot-loader */
	gdev->pruss_clk = devm_clk_get(dev, "pruss");
	अगर (IS_ERR(gdev->pruss_clk)) अणु
		dev_err(dev, "Failed to get clock\n");
		वापस PTR_ERR(gdev->pruss_clk);
	पूर्ण

	ret = clk_enable(gdev->pruss_clk);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable clock\n");
		वापस ret;
	पूर्ण

	regs_prussio = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!regs_prussio) अणु
		dev_err(dev, "No PRUSS I/O resource specified\n");
		ret = -EIO;
		जाओ err_clk_disable;
	पूर्ण

	अगर (!regs_prussio->start) अणु
		dev_err(dev, "Invalid memory resource\n");
		ret = -EIO;
		जाओ err_clk_disable;
	पूर्ण

	अगर (pdata->sram_pool) अणु
		gdev->sram_pool = pdata->sram_pool;
		gdev->sram_vaddr =
			(अचिन्हित दीर्घ)gen_pool_dma_alloc(gdev->sram_pool,
					sram_pool_sz, &gdev->sram_paddr);
		अगर (!gdev->sram_vaddr) अणु
			dev_err(dev, "Could not allocate SRAM pool\n");
			ret = -ENOMEM;
			जाओ err_clk_disable;
		पूर्ण
	पूर्ण

	gdev->ddr_vaddr = dma_alloc_coherent(dev, extram_pool_sz,
				&(gdev->ddr_paddr), GFP_KERNEL | GFP_DMA);
	अगर (!gdev->ddr_vaddr) अणु
		dev_err(dev, "Could not allocate external memory\n");
		ret = -ENOMEM;
		जाओ err_मुक्त_sram;
	पूर्ण

	len = resource_size(regs_prussio);
	gdev->prussio_vaddr = ioremap(regs_prussio->start, len);
	अगर (!gdev->prussio_vaddr) अणु
		dev_err(dev, "Can't remap PRUSS I/O  address range\n");
		ret = -ENOMEM;
		जाओ err_मुक्त_ddr_vaddr;
	पूर्ण

	gdev->pपूर्णांकc_base = pdata->pपूर्णांकc_base;
	gdev->hostirq_start = platक्रमm_get_irq(pdev, 0);

	क्रम (cnt = 0, p = gdev->info; cnt < MAX_PRUSS_EVT; cnt++, p++) अणु
		p->mem[0].addr = regs_prussio->start;
		p->mem[0].size = resource_size(regs_prussio);
		p->mem[0].memtype = UIO_MEM_PHYS;

		p->mem[1].addr = gdev->sram_paddr;
		p->mem[1].size = sram_pool_sz;
		p->mem[1].memtype = UIO_MEM_PHYS;

		p->mem[2].addr = gdev->ddr_paddr;
		p->mem[2].size = extram_pool_sz;
		p->mem[2].memtype = UIO_MEM_PHYS;

		p->name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "pruss_evt%d", cnt);
		p->version = DRV_VERSION;

		/* Register PRUSS IRQ lines */
		p->irq = gdev->hostirq_start + cnt;
		p->handler = pruss_handler;
		p->priv = gdev;

		ret = uio_रेजिस्टर_device(dev, p);
		अगर (ret < 0)
			जाओ err_unloop;
	पूर्ण

	platक्रमm_set_drvdata(pdev, gdev);
	वापस 0;

err_unloop:
	क्रम (i = 0, p = gdev->info; i < cnt; i++, p++) अणु
		uio_unरेजिस्टर_device(p);
	पूर्ण
	iounmap(gdev->prussio_vaddr);
err_मुक्त_ddr_vaddr:
	dma_मुक्त_coherent(dev, extram_pool_sz, gdev->ddr_vaddr,
			  gdev->ddr_paddr);
err_मुक्त_sram:
	अगर (pdata->sram_pool)
		gen_pool_मुक्त(gdev->sram_pool, gdev->sram_vaddr, sram_pool_sz);
err_clk_disable:
	clk_disable(gdev->pruss_clk);

	वापस ret;
पूर्ण

अटल पूर्णांक pruss_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा uio_pruss_dev *gdev = platक्रमm_get_drvdata(dev);

	pruss_cleanup(&dev->dev, gdev);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pruss_driver = अणु
	.probe = pruss_probe,
	.हटाओ = pruss_हटाओ,
	.driver = अणु
		   .name = DRV_NAME,
		   पूर्ण,
पूर्ण;

module_platक्रमm_driver(pruss_driver);

MODULE_LICENSE("GPL v2");
MODULE_VERSION(DRV_VERSION);
MODULE_AUTHOR("Amit Chatterjee <amit.chatterjee@ti.com>");
MODULE_AUTHOR("Pratheesh Gangadhar <pratheesh@ti.com>");
