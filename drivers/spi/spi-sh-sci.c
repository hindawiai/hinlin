<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SH SCI SPI पूर्णांकerface
 *
 * Copyright (c) 2008 Magnus Damm
 *
 * Based on S3C24XX GPIO based SPI driver, which is:
 *   Copyright (c) 2006 Ben Dooks
 *   Copyright (c) 2006 Simtec Electronics
 */

#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi_bitbang.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/spi.h>
#समावेश <यंत्र/पन.स>

काष्ठा sh_sci_spi अणु
	काष्ठा spi_bitbang bitbang;

	व्योम __iomem *membase;
	अचिन्हित अक्षर val;
	काष्ठा sh_spi_info *info;
	काष्ठा platक्रमm_device *dev;
पूर्ण;

#घोषणा SCSPTR(sp)	(sp->membase + 0x1c)
#घोषणा PIN_SCK		(1 << 2)
#घोषणा PIN_TXD		(1 << 0)
#घोषणा PIN_RXD		PIN_TXD
#घोषणा PIN_INIT	((1 << 1) | (1 << 3) | PIN_SCK | PIN_TXD)

अटल अंतरभूत व्योम setbits(काष्ठा sh_sci_spi *sp, पूर्णांक bits, पूर्णांक on)
अणु
	/*
	 * We are the only user of SCSPTR so no locking is required.
	 * Reading bit 2 and 0 in SCSPTR gives pin state as input.
	 * Writing the same bits sets the output value.
	 * This makes regular पढ़ो-modअगरy-ग_लिखो dअगरficult so we
	 * use sp->val to keep track of the latest रेजिस्टर value.
	 */

	अगर (on)
		sp->val |= bits;
	अन्यथा
		sp->val &= ~bits;

	ioग_लिखो8(sp->val, SCSPTR(sp));
पूर्ण

अटल अंतरभूत व्योम setsck(काष्ठा spi_device *dev, पूर्णांक on)
अणु
	setbits(spi_master_get_devdata(dev->master), PIN_SCK, on);
पूर्ण

अटल अंतरभूत व्योम seपंचांगosi(काष्ठा spi_device *dev, पूर्णांक on)
अणु
	setbits(spi_master_get_devdata(dev->master), PIN_TXD, on);
पूर्ण

अटल अंतरभूत u32 geपंचांगiso(काष्ठा spi_device *dev)
अणु
	काष्ठा sh_sci_spi *sp = spi_master_get_devdata(dev->master);

	वापस (ioपढ़ो8(SCSPTR(sp)) & PIN_RXD) ? 1 : 0;
पूर्ण

#घोषणा spidelay(x) ndelay(x)

#समावेश "spi-bitbang-txrx.h"

अटल u32 sh_sci_spi_txrx_mode0(काष्ठा spi_device *spi,
				 अचिन्हित nsecs, u32 word, u8 bits,
				 अचिन्हित flags)
अणु
	वापस bitbang_txrx_be_cpha0(spi, nsecs, 0, flags, word, bits);
पूर्ण

अटल u32 sh_sci_spi_txrx_mode1(काष्ठा spi_device *spi,
				 अचिन्हित nsecs, u32 word, u8 bits,
				 अचिन्हित flags)
अणु
	वापस bitbang_txrx_be_cpha1(spi, nsecs, 0, flags, word, bits);
पूर्ण

अटल u32 sh_sci_spi_txrx_mode2(काष्ठा spi_device *spi,
				 अचिन्हित nsecs, u32 word, u8 bits,
				 अचिन्हित flags)
अणु
	वापस bitbang_txrx_be_cpha0(spi, nsecs, 1, flags, word, bits);
पूर्ण

अटल u32 sh_sci_spi_txrx_mode3(काष्ठा spi_device *spi,
				 अचिन्हित nsecs, u32 word, u8 bits,
				 अचिन्हित flags)
अणु
	वापस bitbang_txrx_be_cpha1(spi, nsecs, 1, flags, word, bits);
पूर्ण

अटल व्योम sh_sci_spi_chipselect(काष्ठा spi_device *dev, पूर्णांक value)
अणु
	काष्ठा sh_sci_spi *sp = spi_master_get_devdata(dev->master);

	अगर (sp->info->chip_select)
		(sp->info->chip_select)(sp->info, dev->chip_select, value);
पूर्ण

अटल पूर्णांक sh_sci_spi_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा resource	*r;
	काष्ठा spi_master *master;
	काष्ठा sh_sci_spi *sp;
	पूर्णांक ret;

	master = spi_alloc_master(&dev->dev, माप(काष्ठा sh_sci_spi));
	अगर (master == शून्य) अणु
		dev_err(&dev->dev, "failed to allocate spi master\n");
		ret = -ENOMEM;
		जाओ err0;
	पूर्ण

	sp = spi_master_get_devdata(master);

	platक्रमm_set_drvdata(dev, sp);
	sp->info = dev_get_platdata(&dev->dev);
	अगर (!sp->info) अणु
		dev_err(&dev->dev, "platform data is missing\n");
		ret = -ENOENT;
		जाओ err1;
	पूर्ण

	/* setup spi bitbang adaptor */
	sp->bitbang.master = master;
	sp->bitbang.master->bus_num = sp->info->bus_num;
	sp->bitbang.master->num_chipselect = sp->info->num_chipselect;
	sp->bitbang.chipselect = sh_sci_spi_chipselect;

	sp->bitbang.txrx_word[SPI_MODE_0] = sh_sci_spi_txrx_mode0;
	sp->bitbang.txrx_word[SPI_MODE_1] = sh_sci_spi_txrx_mode1;
	sp->bitbang.txrx_word[SPI_MODE_2] = sh_sci_spi_txrx_mode2;
	sp->bitbang.txrx_word[SPI_MODE_3] = sh_sci_spi_txrx_mode3;

	r = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);
	अगर (r == शून्य) अणु
		ret = -ENOENT;
		जाओ err1;
	पूर्ण
	sp->membase = ioremap(r->start, resource_size(r));
	अगर (!sp->membase) अणु
		ret = -ENXIO;
		जाओ err1;
	पूर्ण
	sp->val = ioपढ़ो8(SCSPTR(sp));
	setbits(sp, PIN_INIT, 1);

	ret = spi_bitbang_start(&sp->bitbang);
	अगर (!ret)
		वापस 0;

	setbits(sp, PIN_INIT, 0);
	iounmap(sp->membase);
 err1:
	spi_master_put(sp->bitbang.master);
 err0:
	वापस ret;
पूर्ण

अटल पूर्णांक sh_sci_spi_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा sh_sci_spi *sp = platक्रमm_get_drvdata(dev);

	spi_bitbang_stop(&sp->bitbang);
	setbits(sp, PIN_INIT, 0);
	iounmap(sp->membase);
	spi_master_put(sp->bitbang.master);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sh_sci_spi_drv = अणु
	.probe		= sh_sci_spi_probe,
	.हटाओ		= sh_sci_spi_हटाओ,
	.driver		= अणु
		.name	= "spi_sh_sci",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sh_sci_spi_drv);

MODULE_DESCRIPTION("SH SCI SPI Driver");
MODULE_AUTHOR("Magnus Damm <damm@opensource.se>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:spi_sh_sci");
