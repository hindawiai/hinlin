<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * linux/drivers/video/mmp/hw/mmp_spi.c
 * using the spi in LCD controler क्रम commands send
 *
 * Copyright (C) 2012 Marvell Technology Group Ltd.
 * Authors:  Guoqing Li <ligq@marvell.com>
 *          Lisa Du <cldu@marvell.com>
 *          Zhou Zhu <zzhu3@marvell.com>
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/spi/spi.h>
#समावेश "mmp_ctrl.h"

/**
 * spi_ग_लिखो - ग_लिखो command to the SPI port
 * @spi:  the SPI device.
 * @data: can be 8/16/32-bit, MSB justअगरied data to ग_लिखो.
 *
 * Wait bus transfer complete IRQ.
 * The caller is expected to perक्रमm the necessary locking.
 *
 * Returns:
 *   %-ETIMEDOUT	समयout occurred
 *   0			success
 */
अटल अंतरभूत पूर्णांक lcd_spi_ग_लिखो(काष्ठा spi_device *spi, u32 data)
अणु
	पूर्णांक समयout = 100000, isr, ret = 0;
	u32 पंचांगp;
	व्योम __iomem *reg_base = (व्योम __iomem *)
		*(व्योम **)spi_master_get_devdata(spi->master);

	/* clear ISR */
	ग_लिखोl_relaxed(~SPI_IRQ_MASK, reg_base + SPU_IRQ_ISR);

	चयन (spi->bits_per_word) अणु
	हाल 8:
		ग_लिखोl_relaxed((u8)data, reg_base + LCD_SPU_SPI_TXDATA);
		अवरोध;
	हाल 16:
		ग_लिखोl_relaxed((u16)data, reg_base + LCD_SPU_SPI_TXDATA);
		अवरोध;
	हाल 32:
		ग_लिखोl_relaxed((u32)data, reg_base + LCD_SPU_SPI_TXDATA);
		अवरोध;
	शेष:
		dev_err(&spi->dev, "Wrong spi bit length\n");
	पूर्ण

	/* SPI start to send command */
	पंचांगp = पढ़ोl_relaxed(reg_base + LCD_SPU_SPI_CTRL);
	पंचांगp &= ~CFG_SPI_START_MASK;
	पंचांगp |= CFG_SPI_START(1);
	ग_लिखोl(पंचांगp, reg_base + LCD_SPU_SPI_CTRL);

	isr = पढ़ोl_relaxed(reg_base + SPU_IRQ_ISR);
	जबतक (!(isr & SPI_IRQ_ENA_MASK)) अणु
		udelay(100);
		isr = पढ़ोl_relaxed(reg_base + SPU_IRQ_ISR);
		अगर (!--समयout) अणु
			ret = -ETIMEDOUT;
			dev_err(&spi->dev, "spi cmd send time out\n");
			अवरोध;
		पूर्ण
	पूर्ण

	पंचांगp = पढ़ोl_relaxed(reg_base + LCD_SPU_SPI_CTRL);
	पंचांगp &= ~CFG_SPI_START_MASK;
	पंचांगp |= CFG_SPI_START(0);
	ग_लिखोl_relaxed(पंचांगp, reg_base + LCD_SPU_SPI_CTRL);

	ग_लिखोl_relaxed(~SPI_IRQ_MASK, reg_base + SPU_IRQ_ISR);

	वापस ret;
पूर्ण

अटल पूर्णांक lcd_spi_setup(काष्ठा spi_device *spi)
अणु
	व्योम __iomem *reg_base = (व्योम __iomem *)
		*(व्योम **)spi_master_get_devdata(spi->master);
	u32 पंचांगp;

	पंचांगp = CFG_SCLKCNT(16) |
		CFG_TXBITS(spi->bits_per_word) |
		CFG_SPI_SEL(1) | CFG_SPI_ENA(1) |
		CFG_SPI_3W4WB(1);
	ग_लिखोl(पंचांगp, reg_base + LCD_SPU_SPI_CTRL);

	/*
	 * After set mode it need a समय to pull up the spi singals,
	 * or it would cause the wrong waveक्रमm when send spi command,
	 * especially on pxa910h
	 */
	पंचांगp = पढ़ोl_relaxed(reg_base + SPU_IOPAD_CONTROL);
	अगर ((पंचांगp & CFG_IOPADMODE_MASK) != IOPAD_DUMB18SPI)
		ग_लिखोl_relaxed(IOPAD_DUMB18SPI |
			(पंचांगp & ~CFG_IOPADMODE_MASK),
			reg_base + SPU_IOPAD_CONTROL);
	udelay(20);
	वापस 0;
पूर्ण

अटल पूर्णांक lcd_spi_one_transfer(काष्ठा spi_device *spi, काष्ठा spi_message *m)
अणु
	काष्ठा spi_transfer *t;
	पूर्णांक i;

	list_क्रम_each_entry(t, &m->transfers, transfer_list) अणु
		चयन (spi->bits_per_word) अणु
		हाल 8:
			क्रम (i = 0; i < t->len; i++)
				lcd_spi_ग_लिखो(spi, ((u8 *)t->tx_buf)[i]);
			अवरोध;
		हाल 16:
			क्रम (i = 0; i < t->len/2; i++)
				lcd_spi_ग_लिखो(spi, ((u16 *)t->tx_buf)[i]);
			अवरोध;
		हाल 32:
			क्रम (i = 0; i < t->len/4; i++)
				lcd_spi_ग_लिखो(spi, ((u32 *)t->tx_buf)[i]);
			अवरोध;
		शेष:
			dev_err(&spi->dev, "Wrong spi bit length\n");
		पूर्ण
	पूर्ण

	m->status = 0;
	अगर (m->complete)
		m->complete(m->context);
	वापस 0;
पूर्ण

पूर्णांक lcd_spi_रेजिस्टर(काष्ठा mmphw_ctrl *ctrl)
अणु
	काष्ठा spi_master *master;
	व्योम **p_regbase;
	पूर्णांक err;

	master = spi_alloc_master(ctrl->dev, माप(व्योम *));
	अगर (!master) अणु
		dev_err(ctrl->dev, "unable to allocate SPI master\n");
		वापस -ENOMEM;
	पूर्ण
	p_regbase = spi_master_get_devdata(master);
	*p_regbase = (व्योम __क्रमce *)ctrl->reg_base;

	/* set bus num to 5 to aव्योम conflict with other spi hosts */
	master->bus_num = 5;
	master->num_chipselect = 1;
	master->setup = lcd_spi_setup;
	master->transfer = lcd_spi_one_transfer;

	err = spi_रेजिस्टर_master(master);
	अगर (err < 0) अणु
		dev_err(ctrl->dev, "unable to register SPI master\n");
		spi_master_put(master);
		वापस err;
	पूर्ण

	dev_info(&master->dev, "registered\n");

	वापस 0;
पूर्ण
