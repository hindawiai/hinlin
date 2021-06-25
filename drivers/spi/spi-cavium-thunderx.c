<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Cavium ThunderX SPI driver.
 *
 * Copyright (C) 2016 Cavium Inc.
 * Authors: Jan Glauber <jglauber@cavium.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/spi/spi.h>

#समावेश "spi-cavium.h"

#घोषणा DRV_NAME "spi-thunderx"

#घोषणा SYS_FREQ_DEFAULT 700000000 /* 700 Mhz */

अटल पूर्णांक thunderx_spi_probe(काष्ठा pci_dev *pdev,
			      स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा spi_master *master;
	काष्ठा octeon_spi *p;
	पूर्णांक ret;

	master = spi_alloc_master(dev, माप(काष्ठा octeon_spi));
	अगर (!master)
		वापस -ENOMEM;

	p = spi_master_get_devdata(master);

	ret = pcim_enable_device(pdev);
	अगर (ret)
		जाओ error;

	ret = pci_request_regions(pdev, DRV_NAME);
	अगर (ret)
		जाओ error;

	p->रेजिस्टर_base = pcim_iomap(pdev, 0, pci_resource_len(pdev, 0));
	अगर (!p->रेजिस्टर_base) अणु
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	p->regs.config = 0x1000;
	p->regs.status = 0x1008;
	p->regs.tx = 0x1010;
	p->regs.data = 0x1080;

	p->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(p->clk)) अणु
		ret = PTR_ERR(p->clk);
		जाओ error;
	पूर्ण

	ret = clk_prepare_enable(p->clk);
	अगर (ret)
		जाओ error;

	p->sys_freq = clk_get_rate(p->clk);
	अगर (!p->sys_freq)
		p->sys_freq = SYS_FREQ_DEFAULT;
	dev_info(dev, "Set system clock to %u\n", p->sys_freq);

	master->flags = SPI_MASTER_HALF_DUPLEX;
	master->num_chipselect = 4;
	master->mode_bits = SPI_CPHA | SPI_CPOL | SPI_CS_HIGH |
			    SPI_LSB_FIRST | SPI_3WIRE;
	master->transfer_one_message = octeon_spi_transfer_one_message;
	master->bits_per_word_mask = SPI_BPW_MASK(8);
	master->max_speed_hz = OCTEON_SPI_MAX_CLOCK_HZ;
	master->dev.of_node = pdev->dev.of_node;

	pci_set_drvdata(pdev, master);

	ret = devm_spi_रेजिस्टर_master(dev, master);
	अगर (ret)
		जाओ error;

	वापस 0;

error:
	clk_disable_unprepare(p->clk);
	pci_release_regions(pdev);
	spi_master_put(master);
	वापस ret;
पूर्ण

अटल व्योम thunderx_spi_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा spi_master *master = pci_get_drvdata(pdev);
	काष्ठा octeon_spi *p;

	p = spi_master_get_devdata(master);
	अगर (!p)
		वापस;

	clk_disable_unprepare(p->clk);
	pci_release_regions(pdev);
	/* Put everything in a known state. */
	ग_लिखोq(0, p->रेजिस्टर_base + OCTEON_SPI_CFG(p));
पूर्ण

अटल स्थिर काष्ठा pci_device_id thunderx_spi_pci_id_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_CAVIUM, 0xa00b) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, thunderx_spi_pci_id_table);

अटल काष्ठा pci_driver thunderx_spi_driver = अणु
	.name		= DRV_NAME,
	.id_table	= thunderx_spi_pci_id_table,
	.probe		= thunderx_spi_probe,
	.हटाओ		= thunderx_spi_हटाओ,
पूर्ण;

module_pci_driver(thunderx_spi_driver);

MODULE_DESCRIPTION("Cavium, Inc. ThunderX SPI bus driver");
MODULE_AUTHOR("Jan Glauber");
MODULE_LICENSE("GPL");
