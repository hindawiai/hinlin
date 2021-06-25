<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2011, 2012 Cavium, Inc.
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>

#समावेश <यंत्र/octeon/octeon.h>

#समावेश "spi-cavium.h"

अटल पूर्णांक octeon_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	व्योम __iomem *reg_base;
	काष्ठा spi_master *master;
	काष्ठा octeon_spi *p;
	पूर्णांक err = -ENOENT;

	master = spi_alloc_master(&pdev->dev, माप(काष्ठा octeon_spi));
	अगर (!master)
		वापस -ENOMEM;
	p = spi_master_get_devdata(master);
	platक्रमm_set_drvdata(pdev, master);

	reg_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(reg_base)) अणु
		err = PTR_ERR(reg_base);
		जाओ fail;
	पूर्ण

	p->रेजिस्टर_base = reg_base;
	p->sys_freq = octeon_get_io_घड़ी_rate();

	p->regs.config = 0;
	p->regs.status = 0x08;
	p->regs.tx = 0x10;
	p->regs.data = 0x80;

	master->num_chipselect = 4;
	master->mode_bits = SPI_CPHA |
			    SPI_CPOL |
			    SPI_CS_HIGH |
			    SPI_LSB_FIRST |
			    SPI_3WIRE;

	master->transfer_one_message = octeon_spi_transfer_one_message;
	master->bits_per_word_mask = SPI_BPW_MASK(8);
	master->max_speed_hz = OCTEON_SPI_MAX_CLOCK_HZ;

	master->dev.of_node = pdev->dev.of_node;
	err = devm_spi_रेजिस्टर_master(&pdev->dev, master);
	अगर (err) अणु
		dev_err(&pdev->dev, "register master failed: %d\n", err);
		जाओ fail;
	पूर्ण

	dev_info(&pdev->dev, "OCTEON SPI bus driver\n");

	वापस 0;
fail:
	spi_master_put(master);
	वापस err;
पूर्ण

अटल पूर्णांक octeon_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master = platक्रमm_get_drvdata(pdev);
	काष्ठा octeon_spi *p = spi_master_get_devdata(master);

	/* Clear the CSENA* and put everything in a known state. */
	ग_लिखोq(0, p->रेजिस्टर_base + OCTEON_SPI_CFG(p));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id octeon_spi_match[] = अणु
	अणु .compatible = "cavium,octeon-3010-spi", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, octeon_spi_match);

अटल काष्ठा platक्रमm_driver octeon_spi_driver = अणु
	.driver = अणु
		.name		= "spi-octeon",
		.of_match_table = octeon_spi_match,
	पूर्ण,
	.probe		= octeon_spi_probe,
	.हटाओ		= octeon_spi_हटाओ,
पूर्ण;

module_platक्रमm_driver(octeon_spi_driver);

MODULE_DESCRIPTION("Cavium, Inc. OCTEON SPI bus driver");
MODULE_AUTHOR("David Daney");
MODULE_LICENSE("GPL");
