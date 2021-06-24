<शैली गुरु>
/*
 * Driver क्रम MMC and SSD cards क्रम Cavium ThunderX SOCs.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2016 Cavium Inc.
 */
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pci.h>
#समावेश "cavium.h"

अटल व्योम thunder_mmc_acquire_bus(काष्ठा cvm_mmc_host *host)
अणु
	करोwn(&host->mmc_serializer);
पूर्ण

अटल व्योम thunder_mmc_release_bus(काष्ठा cvm_mmc_host *host)
अणु
	up(&host->mmc_serializer);
पूर्ण

अटल व्योम thunder_mmc_पूर्णांक_enable(काष्ठा cvm_mmc_host *host, u64 val)
अणु
	ग_लिखोq(val, host->base + MIO_EMM_INT(host));
	ग_लिखोq(val, host->base + MIO_EMM_INT_EN_SET(host));
पूर्ण

अटल पूर्णांक thunder_mmc_रेजिस्टर_पूर्णांकerrupts(काष्ठा cvm_mmc_host *host,
					   काष्ठा pci_dev *pdev)
अणु
	पूर्णांक nvec, ret, i;

	nvec = pci_alloc_irq_vectors(pdev, 1, 9, PCI_IRQ_MSIX);
	अगर (nvec < 0)
		वापस nvec;

	/* रेजिस्टर पूर्णांकerrupts */
	क्रम (i = 0; i < nvec; i++) अणु
		ret = devm_request_irq(&pdev->dev, pci_irq_vector(pdev, i),
				       cvm_mmc_पूर्णांकerrupt,
				       0, cvm_mmc_irq_names[i], host);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक thunder_mmc_probe(काष्ठा pci_dev *pdev,
			     स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *child_node;
	काष्ठा cvm_mmc_host *host;
	पूर्णांक ret, i = 0;

	host = devm_kzalloc(dev, माप(*host), GFP_KERNEL);
	अगर (!host)
		वापस -ENOMEM;

	pci_set_drvdata(pdev, host);
	ret = pcim_enable_device(pdev);
	अगर (ret)
		वापस ret;

	ret = pci_request_regions(pdev, KBUILD_MODNAME);
	अगर (ret)
		वापस ret;

	host->base = pcim_iomap(pdev, 0, pci_resource_len(pdev, 0));
	अगर (!host->base) अणु
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	/* On ThunderX these are identical */
	host->dma_base = host->base;

	host->reg_off = 0x2000;
	host->reg_off_dma = 0x160;

	host->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(host->clk)) अणु
		ret = PTR_ERR(host->clk);
		जाओ error;
	पूर्ण

	ret = clk_prepare_enable(host->clk);
	अगर (ret)
		जाओ error;
	host->sys_freq = clk_get_rate(host->clk);

	spin_lock_init(&host->irq_handler_lock);
	sema_init(&host->mmc_serializer, 1);

	host->dev = dev;
	host->acquire_bus = thunder_mmc_acquire_bus;
	host->release_bus = thunder_mmc_release_bus;
	host->पूर्णांक_enable = thunder_mmc_पूर्णांक_enable;

	host->use_sg = true;
	host->big_dma_addr = true;
	host->need_irq_handler_lock = true;
	host->last_slot = -1;

	ret = dma_set_mask(dev, DMA_BIT_MASK(48));
	अगर (ret)
		जाओ error;

	/*
	 * Clear out any pending पूर्णांकerrupts that may be left over from
	 * bootloader. Writing 1 to the bits clears them.
	 */
	ग_लिखोq(127, host->base + MIO_EMM_INT_EN(host));
	ग_लिखोq(3, host->base + MIO_EMM_DMA_INT_ENA_W1C(host));
	/* Clear DMA FIFO */
	ग_लिखोq(BIT_ULL(16), host->base + MIO_EMM_DMA_FIFO_CFG(host));

	ret = thunder_mmc_रेजिस्टर_पूर्णांकerrupts(host, pdev);
	अगर (ret)
		जाओ error;

	क्रम_each_child_of_node(node, child_node) अणु
		/*
		 * mmc_of_parse and devm* require one device per slot.
		 * Create a dummy device per slot and set the node poपूर्णांकer to
		 * the slot. The easiest way to get this is using
		 * of_platक्रमm_device_create.
		 */
		अगर (of_device_is_compatible(child_node, "mmc-slot")) अणु
			host->slot_pdev[i] = of_platक्रमm_device_create(child_node, शून्य,
								       &pdev->dev);
			अगर (!host->slot_pdev[i])
				जारी;

			ret = cvm_mmc_of_slot_probe(&host->slot_pdev[i]->dev, host);
			अगर (ret)
				जाओ error;
		पूर्ण
		i++;
	पूर्ण
	dev_info(dev, "probed\n");
	वापस 0;

error:
	क्रम (i = 0; i < CAVIUM_MAX_MMC; i++) अणु
		अगर (host->slot[i])
			cvm_mmc_of_slot_हटाओ(host->slot[i]);
		अगर (host->slot_pdev[i]) अणु
			get_device(&host->slot_pdev[i]->dev);
			of_platक्रमm_device_destroy(&host->slot_pdev[i]->dev, शून्य);
			put_device(&host->slot_pdev[i]->dev);
		पूर्ण
	पूर्ण
	clk_disable_unprepare(host->clk);
	pci_release_regions(pdev);
	वापस ret;
पूर्ण

अटल व्योम thunder_mmc_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा cvm_mmc_host *host = pci_get_drvdata(pdev);
	u64 dma_cfg;
	पूर्णांक i;

	क्रम (i = 0; i < CAVIUM_MAX_MMC; i++)
		अगर (host->slot[i])
			cvm_mmc_of_slot_हटाओ(host->slot[i]);

	dma_cfg = पढ़ोq(host->dma_base + MIO_EMM_DMA_CFG(host));
	dma_cfg &= ~MIO_EMM_DMA_CFG_EN;
	ग_लिखोq(dma_cfg, host->dma_base + MIO_EMM_DMA_CFG(host));

	clk_disable_unprepare(host->clk);
	pci_release_regions(pdev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id thunder_mmc_id_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_CAVIUM, 0xa010) पूर्ण,
	अणु 0, पूर्ण  /* end of table */
पूर्ण;

अटल काष्ठा pci_driver thunder_mmc_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = thunder_mmc_id_table,
	.probe = thunder_mmc_probe,
	.हटाओ = thunder_mmc_हटाओ,
पूर्ण;

module_pci_driver(thunder_mmc_driver);

MODULE_AUTHOR("Cavium Inc.");
MODULE_DESCRIPTION("Cavium ThunderX eMMC Driver");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, thunder_mmc_id_table);
