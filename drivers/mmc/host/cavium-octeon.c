<शैली गुरु>
/*
 * Driver क्रम MMC and SSD cards क्रम Cavium OCTEON SOCs.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2012-2017 Cavium Inc.
 */
#समावेश <linux/dma-mapping.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/mmc/slot-gpपन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <यंत्र/octeon/octeon.h>
#समावेश "cavium.h"

#घोषणा CVMX_MIO_BOOT_CTL CVMX_ADD_IO_SEG(0x00011800000000D0ull)

/*
 * The l2c* functions below are used क्रम the EMMC-17978 workaround.
 *
 * Due to a bug in the design of the MMC bus hardware, the 2nd to last
 * cache block of a DMA पढ़ो must be locked पूर्णांकo the L2 Cache.
 * Otherwise, data corruption may occur.
 */
अटल अंतरभूत व्योम *phys_to_ptr(u64 address)
अणु
	वापस (व्योम *)(address | (1ull << 63)); /* XKPHYS */
पूर्ण

/*
 * Lock a single line पूर्णांकo L2. The line is zeroed beक्रमe locking
 * to make sure no dram accesses are made.
 */
अटल व्योम l2c_lock_line(u64 addr)
अणु
	अक्षर *addr_ptr = phys_to_ptr(addr);

	यंत्र अस्थिर (
		"cache 31, %[line]"	/* Unlock the line */
		::[line] "m" (*addr_ptr));
पूर्ण

/* Unlock a single line in the L2 cache. */
अटल व्योम l2c_unlock_line(u64 addr)
अणु
	अक्षर *addr_ptr = phys_to_ptr(addr);

	यंत्र अस्थिर (
		"cache 23, %[line]"	/* Unlock the line */
		::[line] "m" (*addr_ptr));
पूर्ण

/* Locks a memory region in the L2 cache. */
अटल व्योम l2c_lock_mem_region(u64 start, u64 len)
अणु
	u64 end;

	/* Round start/end to cache line boundaries */
	end = ALIGN(start + len - 1, CVMX_CACHE_LINE_SIZE);
	start = ALIGN(start, CVMX_CACHE_LINE_SIZE);

	जबतक (start <= end) अणु
		l2c_lock_line(start);
		start += CVMX_CACHE_LINE_SIZE;
	पूर्ण
	यंत्र अस्थिर("sync");
पूर्ण

/* Unlock a memory region in the L2 cache. */
अटल व्योम l2c_unlock_mem_region(u64 start, u64 len)
अणु
	u64 end;

	/* Round start/end to cache line boundaries */
	end = ALIGN(start + len - 1, CVMX_CACHE_LINE_SIZE);
	start = ALIGN(start, CVMX_CACHE_LINE_SIZE);

	जबतक (start <= end) अणु
		l2c_unlock_line(start);
		start += CVMX_CACHE_LINE_SIZE;
	पूर्ण
पूर्ण

अटल व्योम octeon_mmc_acquire_bus(काष्ठा cvm_mmc_host *host)
अणु
	अगर (!host->has_ciu3) अणु
		करोwn(&octeon_bootbus_sem);
		/* For CN70XX, चयन the MMC controller onto the bus. */
		अगर (OCTEON_IS_MODEL(OCTEON_CN70XX))
			ग_लिखोq(0, (व्योम __iomem *)CVMX_MIO_BOOT_CTL);
	पूर्ण अन्यथा अणु
		करोwn(&host->mmc_serializer);
	पूर्ण
पूर्ण

अटल व्योम octeon_mmc_release_bus(काष्ठा cvm_mmc_host *host)
अणु
	अगर (!host->has_ciu3)
		up(&octeon_bootbus_sem);
	अन्यथा
		up(&host->mmc_serializer);
पूर्ण

अटल व्योम octeon_mmc_पूर्णांक_enable(काष्ठा cvm_mmc_host *host, u64 val)
अणु
	ग_लिखोq(val, host->base + MIO_EMM_INT(host));
	अगर (!host->has_ciu3)
		ग_लिखोq(val, host->base + MIO_EMM_INT_EN(host));
पूर्ण

अटल व्योम octeon_mmc_set_shared_घातer(काष्ठा cvm_mmc_host *host, पूर्णांक dir)
अणु
	अगर (dir == 0)
		अगर (!atomic_dec_वापस(&host->shared_घातer_users))
			gpiod_set_value_cansleep(host->global_pwr_gpiod, 0);
	अगर (dir == 1)
		अगर (atomic_inc_वापस(&host->shared_घातer_users) == 1)
			gpiod_set_value_cansleep(host->global_pwr_gpiod, 1);
पूर्ण

अटल व्योम octeon_mmc_dmar_fixup(काष्ठा cvm_mmc_host *host,
				  काष्ठा mmc_command *cmd,
				  काष्ठा mmc_data *data,
				  u64 addr)
अणु
	अगर (cmd->opcode != MMC_WRITE_MULTIPLE_BLOCK)
		वापस;
	अगर (data->blksz * data->blocks <= 1024)
		वापस;

	host->n_minus_one = addr + (data->blksz * data->blocks) - 1024;
	l2c_lock_mem_region(host->n_minus_one, 512);
पूर्ण

अटल व्योम octeon_mmc_dmar_fixup_करोne(काष्ठा cvm_mmc_host *host)
अणु
	अगर (!host->n_minus_one)
		वापस;
	l2c_unlock_mem_region(host->n_minus_one, 512);
	host->n_minus_one = 0;
पूर्ण

अटल पूर्णांक octeon_mmc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *cn, *node = pdev->dev.of_node;
	काष्ठा cvm_mmc_host *host;
	व्योम __iomem *base;
	पूर्णांक mmc_irq[9];
	पूर्णांक i, ret = 0;
	u64 val;

	host = devm_kzalloc(&pdev->dev, माप(*host), GFP_KERNEL);
	अगर (!host)
		वापस -ENOMEM;

	spin_lock_init(&host->irq_handler_lock);
	sema_init(&host->mmc_serializer, 1);

	host->dev = &pdev->dev;
	host->acquire_bus = octeon_mmc_acquire_bus;
	host->release_bus = octeon_mmc_release_bus;
	host->पूर्णांक_enable = octeon_mmc_पूर्णांक_enable;
	host->set_shared_घातer = octeon_mmc_set_shared_घातer;
	अगर (OCTEON_IS_MODEL(OCTEON_CN6XXX) ||
	    OCTEON_IS_MODEL(OCTEON_CNF7XXX)) अणु
		host->dmar_fixup = octeon_mmc_dmar_fixup;
		host->dmar_fixup_करोne = octeon_mmc_dmar_fixup_करोne;
	पूर्ण

	host->sys_freq = octeon_get_io_घड़ी_rate();

	अगर (of_device_is_compatible(node, "cavium,octeon-7890-mmc")) अणु
		host->big_dma_addr = true;
		host->need_irq_handler_lock = true;
		host->has_ciu3 = true;
		host->use_sg = true;
		/*
		 * First seven are the EMM_INT bits 0..6, then two क्रम
		 * the EMM_DMA_INT bits
		 */
		क्रम (i = 0; i < 9; i++) अणु
			mmc_irq[i] = platक्रमm_get_irq(pdev, i);
			अगर (mmc_irq[i] < 0)
				वापस mmc_irq[i];

			/* work around legacy u-boot device trees */
			irq_set_irq_type(mmc_irq[i], IRQ_TYPE_EDGE_RISING);
		पूर्ण
	पूर्ण अन्यथा अणु
		host->big_dma_addr = false;
		host->need_irq_handler_lock = false;
		host->has_ciu3 = false;
		/* First one is EMM second DMA */
		क्रम (i = 0; i < 2; i++) अणु
			mmc_irq[i] = platक्रमm_get_irq(pdev, i);
			अगर (mmc_irq[i] < 0)
				वापस mmc_irq[i];
		पूर्ण
	पूर्ण

	host->last_slot = -1;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);
	host->base = base;
	host->reg_off = 0;

	base = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);
	host->dma_base = base;
	/*
	 * To keep the रेजिस्टर addresses shared we पूर्णांकentionaly use
	 * a negative offset here, first रेजिस्टर used on Octeon thereक्रमe
	 * starts at 0x20 (MIO_EMM_DMA_CFG).
	 */
	host->reg_off_dma = -0x20;

	ret = dma_set_mask(&pdev->dev, DMA_BIT_MASK(64));
	अगर (ret)
		वापस ret;

	/*
	 * Clear out any pending पूर्णांकerrupts that may be left over from
	 * bootloader.
	 */
	val = पढ़ोq(host->base + MIO_EMM_INT(host));
	ग_लिखोq(val, host->base + MIO_EMM_INT(host));

	अगर (host->has_ciu3) अणु
		/* Only CMD_DONE, DMA_DONE, CMD_ERR, DMA_ERR */
		क्रम (i = 1; i <= 4; i++) अणु
			ret = devm_request_irq(&pdev->dev, mmc_irq[i],
					       cvm_mmc_पूर्णांकerrupt,
					       0, cvm_mmc_irq_names[i], host);
			अगर (ret < 0) अणु
				dev_err(&pdev->dev, "Error: devm_request_irq %d\n",
					mmc_irq[i]);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = devm_request_irq(&pdev->dev, mmc_irq[0],
				       cvm_mmc_पूर्णांकerrupt, 0, KBUILD_MODNAME,
				       host);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev, "Error: devm_request_irq %d\n",
				mmc_irq[0]);
			वापस ret;
		पूर्ण
	पूर्ण

	host->global_pwr_gpiod = devm_gpiod_get_optional(&pdev->dev,
							 "power",
							 GPIOD_OUT_HIGH);
	अगर (IS_ERR(host->global_pwr_gpiod)) अणु
		dev_err(&pdev->dev, "Invalid power GPIO\n");
		वापस PTR_ERR(host->global_pwr_gpiod);
	पूर्ण

	platक्रमm_set_drvdata(pdev, host);

	i = 0;
	क्रम_each_child_of_node(node, cn) अणु
		host->slot_pdev[i] =
			of_platक्रमm_device_create(cn, शून्य, &pdev->dev);
		अगर (!host->slot_pdev[i]) अणु
			i++;
			जारी;
		पूर्ण
		ret = cvm_mmc_of_slot_probe(&host->slot_pdev[i]->dev, host);
		अगर (ret) अणु
			dev_err(&pdev->dev, "Error populating slots\n");
			octeon_mmc_set_shared_घातer(host, 0);
			जाओ error;
		पूर्ण
		i++;
	पूर्ण
	वापस 0;

error:
	क्रम (i = 0; i < CAVIUM_MAX_MMC; i++) अणु
		अगर (host->slot[i])
			cvm_mmc_of_slot_हटाओ(host->slot[i]);
		अगर (host->slot_pdev[i])
			of_platक्रमm_device_destroy(&host->slot_pdev[i]->dev, शून्य);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक octeon_mmc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cvm_mmc_host *host = platक्रमm_get_drvdata(pdev);
	u64 dma_cfg;
	पूर्णांक i;

	क्रम (i = 0; i < CAVIUM_MAX_MMC; i++)
		अगर (host->slot[i])
			cvm_mmc_of_slot_हटाओ(host->slot[i]);

	dma_cfg = पढ़ोq(host->dma_base + MIO_EMM_DMA_CFG(host));
	dma_cfg &= ~MIO_EMM_DMA_CFG_EN;
	ग_लिखोq(dma_cfg, host->dma_base + MIO_EMM_DMA_CFG(host));

	octeon_mmc_set_shared_घातer(host, 0);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id octeon_mmc_match[] = अणु
	अणु
		.compatible = "cavium,octeon-6130-mmc",
	पूर्ण,
	अणु
		.compatible = "cavium,octeon-7890-mmc",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, octeon_mmc_match);

अटल काष्ठा platक्रमm_driver octeon_mmc_driver = अणु
	.probe		= octeon_mmc_probe,
	.हटाओ		= octeon_mmc_हटाओ,
	.driver		= अणु
		.name	= KBUILD_MODNAME,
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table = octeon_mmc_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(octeon_mmc_driver);

MODULE_AUTHOR("Cavium Inc. <support@cavium.com>");
MODULE_DESCRIPTION("Low-level driver for Cavium OCTEON MMC/SSD card");
MODULE_LICENSE("GPL");
