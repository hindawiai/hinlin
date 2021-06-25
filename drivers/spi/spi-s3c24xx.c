<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2006 Ben Dooks
 * Copyright 2006-2009 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
*/

#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>

#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi_bitbang.h>
#समावेश <linux/spi/s3c24xx.h>
#समावेश <linux/spi/s3c24xx-fiq.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/fiq.h>

#समावेश "spi-s3c24xx-regs.h"

/**
 * काष्ठा s3c24xx_spi_devstate - per device data
 * @hz: Last frequency calculated क्रम @sppre field.
 * @mode: Last mode setting क्रम the @spcon field.
 * @spcon: Value to ग_लिखो to the SPCON रेजिस्टर.
 * @sppre: Value to ग_लिखो to the SPPRE रेजिस्टर.
 */
काष्ठा s3c24xx_spi_devstate अणु
	अचिन्हित पूर्णांक	hz;
	अचिन्हित पूर्णांक	mode;
	u8		spcon;
	u8		sppre;
पूर्ण;

क्रमागत spi_fiq_mode अणु
	FIQ_MODE_NONE	= 0,
	FIQ_MODE_TX	= 1,
	FIQ_MODE_RX	= 2,
	FIQ_MODE_TXRX	= 3,
पूर्ण;

काष्ठा s3c24xx_spi अणु
	/* bitbang has to be first */
	काष्ठा spi_bitbang	 bitbang;
	काष्ठा completion	 करोne;

	व्योम __iomem		*regs;
	पूर्णांक			 irq;
	पूर्णांक			 len;
	पूर्णांक			 count;

	काष्ठा fiq_handler	 fiq_handler;
	क्रमागत spi_fiq_mode	 fiq_mode;
	अचिन्हित अक्षर		 fiq_inuse;
	अचिन्हित अक्षर		 fiq_claimed;

	व्योम			(*set_cs)(काष्ठा s3c2410_spi_info *spi,
					  पूर्णांक cs, पूर्णांक pol);

	/* data buffers */
	स्थिर अचिन्हित अक्षर	*tx;
	अचिन्हित अक्षर		*rx;

	काष्ठा clk		*clk;
	काष्ठा spi_master	*master;
	काष्ठा spi_device	*curdev;
	काष्ठा device		*dev;
	काष्ठा s3c2410_spi_info *pdata;
पूर्ण;

#घोषणा SPCON_DEFAULT (S3C2410_SPCON_MSTR | S3C2410_SPCON_SMOD_INT)
#घोषणा SPPIN_DEFAULT (S3C2410_SPPIN_KEEP)

अटल अंतरभूत काष्ठा s3c24xx_spi *to_hw(काष्ठा spi_device *sdev)
अणु
	वापस spi_master_get_devdata(sdev->master);
पूर्ण

अटल व्योम s3c24xx_spi_gpiocs(काष्ठा s3c2410_spi_info *spi, पूर्णांक cs, पूर्णांक pol)
अणु
	gpio_set_value(spi->pin_cs, pol);
पूर्ण

अटल व्योम s3c24xx_spi_chipsel(काष्ठा spi_device *spi, पूर्णांक value)
अणु
	काष्ठा s3c24xx_spi_devstate *cs = spi->controller_state;
	काष्ठा s3c24xx_spi *hw = to_hw(spi);
	अचिन्हित पूर्णांक cspol = spi->mode & SPI_CS_HIGH ? 1 : 0;

	/* change the chipselect state and the state of the spi engine घड़ी */

	चयन (value) अणु
	हाल BITBANG_CS_INACTIVE:
		hw->set_cs(hw->pdata, spi->chip_select, cspol^1);
		ग_लिखोb(cs->spcon, hw->regs + S3C2410_SPCON);
		अवरोध;

	हाल BITBANG_CS_ACTIVE:
		ग_लिखोb(cs->spcon | S3C2410_SPCON_ENSCK,
		       hw->regs + S3C2410_SPCON);
		hw->set_cs(hw->pdata, spi->chip_select, cspol);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक s3c24xx_spi_update_state(काष्ठा spi_device *spi,
				    काष्ठा spi_transfer *t)
अणु
	काष्ठा s3c24xx_spi *hw = to_hw(spi);
	काष्ठा s3c24xx_spi_devstate *cs = spi->controller_state;
	अचिन्हित पूर्णांक hz;
	अचिन्हित पूर्णांक भाग;
	अचिन्हित दीर्घ clk;

	hz  = t ? t->speed_hz : spi->max_speed_hz;

	अगर (!hz)
		hz = spi->max_speed_hz;

	अगर (spi->mode != cs->mode) अणु
		u8 spcon = SPCON_DEFAULT | S3C2410_SPCON_ENSCK;

		अगर (spi->mode & SPI_CPHA)
			spcon |= S3C2410_SPCON_CPHA_FMTB;

		अगर (spi->mode & SPI_CPOL)
			spcon |= S3C2410_SPCON_CPOL_HIGH;

		cs->mode = spi->mode;
		cs->spcon = spcon;
	पूर्ण

	अगर (cs->hz != hz) अणु
		clk = clk_get_rate(hw->clk);
		भाग = DIV_ROUND_UP(clk, hz * 2) - 1;

		अगर (भाग > 255)
			भाग = 255;

		dev_dbg(&spi->dev, "pre-scaler=%d (wanted %d, got %ld)\n",
			भाग, hz, clk / (2 * (भाग + 1)));

		cs->hz = hz;
		cs->sppre = भाग;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s3c24xx_spi_setupxfer(काष्ठा spi_device *spi,
				 काष्ठा spi_transfer *t)
अणु
	काष्ठा s3c24xx_spi_devstate *cs = spi->controller_state;
	काष्ठा s3c24xx_spi *hw = to_hw(spi);
	पूर्णांक ret;

	ret = s3c24xx_spi_update_state(spi, t);
	अगर (!ret)
		ग_लिखोb(cs->sppre, hw->regs + S3C2410_SPPRE);

	वापस ret;
पूर्ण

अटल पूर्णांक s3c24xx_spi_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा s3c24xx_spi_devstate *cs = spi->controller_state;
	काष्ठा s3c24xx_spi *hw = to_hw(spi);
	पूर्णांक ret;

	/* allocate settings on the first call */
	अगर (!cs) अणु
		cs = devm_kzalloc(&spi->dev,
				  माप(काष्ठा s3c24xx_spi_devstate),
				  GFP_KERNEL);
		अगर (!cs)
			वापस -ENOMEM;

		cs->spcon = SPCON_DEFAULT;
		cs->hz = -1;
		spi->controller_state = cs;
	पूर्ण

	/* initialise the state from the device */
	ret = s3c24xx_spi_update_state(spi, शून्य);
	अगर (ret)
		वापस ret;

	mutex_lock(&hw->bitbang.lock);
	अगर (!hw->bitbang.busy) अणु
		hw->bitbang.chipselect(spi, BITBANG_CS_INACTIVE);
		/* need to ndelay क्रम 0.5 घड़ीtick ? */
	पूर्ण
	mutex_unlock(&hw->bitbang.lock);

	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक hw_txbyte(काष्ठा s3c24xx_spi *hw, पूर्णांक count)
अणु
	वापस hw->tx ? hw->tx[count] : 0;
पूर्ण

#अगर_घोषित CONFIG_SPI_S3C24XX_FIQ
/* Support क्रम FIQ based pseuकरो-DMA to improve the transfer speed.
 *
 * This code uses the assembly helper in spi_s3c24xx_spi.S which is
 * used by the FIQ core to move data between मुख्य memory and the peripheral
 * block. Since this is code running on the processor, there is no problem
 * with cache coherency of the buffers, so we can use any buffer we like.
 */

/**
 * काष्ठा spi_fiq_code - FIQ code and header
 * @length: The length of the code fragment, excluding this header.
 * @ack_offset: The offset from @data to the word to place the IRQ ACK bit at.
 * @data: The code itself to install as a FIQ handler.
 */
काष्ठा spi_fiq_code अणु
	u32	length;
	u32	ack_offset;
	u8	data[];
पूर्ण;

/**
 * s3c24xx_spi_tryfiq - attempt to claim and setup FIQ क्रम transfer
 * @hw: The hardware state.
 *
 * Claim the FIQ handler (only one can be active at any one समय) and
 * then setup the correct transfer code क्रम this transfer.
 *
 * This call updates all the necessary state inक्रमmation अगर successful,
 * so the caller करोes not need to करो anything more than start the transfer
 * as normal, since the IRQ will have been re-routed to the FIQ handler.
*/
अटल व्योम s3c24xx_spi_tryfiq(काष्ठा s3c24xx_spi *hw)
अणु
	काष्ठा pt_regs regs;
	क्रमागत spi_fiq_mode mode;
	काष्ठा spi_fiq_code *code;
	u32 *ack_ptr = शून्य;
	पूर्णांक ret;

	अगर (!hw->fiq_claimed) अणु
		/* try and claim fiq अगर we haven't got it, and अगर not
		 * then वापस and simply use another transfer method */

		ret = claim_fiq(&hw->fiq_handler);
		अगर (ret)
			वापस;
	पूर्ण

	अगर (hw->tx && !hw->rx)
		mode = FIQ_MODE_TX;
	अन्यथा अगर (hw->rx && !hw->tx)
		mode = FIQ_MODE_RX;
	अन्यथा
		mode = FIQ_MODE_TXRX;

	regs.uregs[fiq_rspi] = (दीर्घ)hw->regs;
	regs.uregs[fiq_rrx]  = (दीर्घ)hw->rx;
	regs.uregs[fiq_rtx]  = (दीर्घ)hw->tx + 1;
	regs.uregs[fiq_rcount] = hw->len - 1;

	set_fiq_regs(&regs);

	अगर (hw->fiq_mode != mode) अणु
		hw->fiq_mode = mode;

		चयन (mode) अणु
		हाल FIQ_MODE_TX:
			code = &s3c24xx_spi_fiq_tx;
			अवरोध;
		हाल FIQ_MODE_RX:
			code = &s3c24xx_spi_fiq_rx;
			अवरोध;
		हाल FIQ_MODE_TXRX:
			code = &s3c24xx_spi_fiq_txrx;
			अवरोध;
		शेष:
			code = शून्य;
		पूर्ण

		BUG_ON(!code);

		ack_ptr = (u32 *)&code->data[code->ack_offset];
		set_fiq_handler(&code->data, code->length);
	पूर्ण

	s3c24xx_set_fiq(hw->irq, ack_ptr, true);

	hw->fiq_mode = mode;
	hw->fiq_inuse = 1;
पूर्ण

/**
 * s3c24xx_spi_fiqop - FIQ core code callback
 * @pw: Data रेजिस्टरed with the handler
 * @release: Whether this is a release or a वापस.
 *
 * Called by the FIQ code when another module wants to use the FIQ, so
 * वापस whether we are currently using this or not and then update our
 * पूर्णांकernal state.
 */
अटल पूर्णांक s3c24xx_spi_fiqop(व्योम *pw, पूर्णांक release)
अणु
	काष्ठा s3c24xx_spi *hw = pw;
	पूर्णांक ret = 0;

	अगर (release) अणु
		अगर (hw->fiq_inuse)
			ret = -EBUSY;

		/* note, we करो not need to unroute the FIQ, as the FIQ
		 * vector code de-routes it to संकेत the end of transfer */

		hw->fiq_mode = FIQ_MODE_NONE;
		hw->fiq_claimed = 0;
	पूर्ण अन्यथा अणु
		hw->fiq_claimed = 1;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * s3c24xx_spi_initfiq - setup the inक्रमmation क्रम the FIQ core
 * @hw: The hardware state.
 *
 * Setup the fiq_handler block to pass to the FIQ core.
 */
अटल अंतरभूत व्योम s3c24xx_spi_initfiq(काष्ठा s3c24xx_spi *hw)
अणु
	hw->fiq_handler.dev_id = hw;
	hw->fiq_handler.name = dev_name(hw->dev);
	hw->fiq_handler.fiq_op = s3c24xx_spi_fiqop;
पूर्ण

/**
 * s3c24xx_spi_usefiq - वापस अगर we should be using FIQ.
 * @hw: The hardware state.
 *
 * Return true अगर the platक्रमm data specअगरies whether this channel is
 * allowed to use the FIQ.
 */
अटल अंतरभूत bool s3c24xx_spi_usefiq(काष्ठा s3c24xx_spi *hw)
अणु
	वापस hw->pdata->use_fiq;
पूर्ण

/**
 * s3c24xx_spi_usingfiq - वापस अगर channel is using FIQ
 * @spi: The hardware state.
 *
 * Return whether the channel is currently using the FIQ (separate from
 * whether the FIQ is claimed).
 */
अटल अंतरभूत bool s3c24xx_spi_usingfiq(काष्ठा s3c24xx_spi *spi)
अणु
	वापस spi->fiq_inuse;
पूर्ण
#अन्यथा

अटल अंतरभूत व्योम s3c24xx_spi_initfiq(काष्ठा s3c24xx_spi *s) अणु पूर्ण
अटल अंतरभूत व्योम s3c24xx_spi_tryfiq(काष्ठा s3c24xx_spi *s) अणु पूर्ण
अटल अंतरभूत bool s3c24xx_spi_usefiq(काष्ठा s3c24xx_spi *s) अणु वापस false; पूर्ण
अटल अंतरभूत bool s3c24xx_spi_usingfiq(काष्ठा s3c24xx_spi *s) अणु वापस false; पूर्ण

#पूर्ण_अगर /* CONFIG_SPI_S3C24XX_FIQ */

अटल पूर्णांक s3c24xx_spi_txrx(काष्ठा spi_device *spi, काष्ठा spi_transfer *t)
अणु
	काष्ठा s3c24xx_spi *hw = to_hw(spi);

	hw->tx = t->tx_buf;
	hw->rx = t->rx_buf;
	hw->len = t->len;
	hw->count = 0;

	init_completion(&hw->करोne);

	hw->fiq_inuse = 0;
	अगर (s3c24xx_spi_usefiq(hw) && t->len >= 3)
		s3c24xx_spi_tryfiq(hw);

	/* send the first byte */
	ग_लिखोb(hw_txbyte(hw, 0), hw->regs + S3C2410_SPTDAT);

	रुको_क्रम_completion(&hw->करोne);
	वापस hw->count;
पूर्ण

अटल irqवापस_t s3c24xx_spi_irq(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा s3c24xx_spi *hw = dev;
	अचिन्हित पूर्णांक spsta = पढ़ोb(hw->regs + S3C2410_SPSTA);
	अचिन्हित पूर्णांक count = hw->count;

	अगर (spsta & S3C2410_SPSTA_DCOL) अणु
		dev_dbg(hw->dev, "data-collision\n");
		complete(&hw->करोne);
		जाओ irq_करोne;
	पूर्ण

	अगर (!(spsta & S3C2410_SPSTA_READY)) अणु
		dev_dbg(hw->dev, "spi not ready for tx?\n");
		complete(&hw->करोne);
		जाओ irq_करोne;
	पूर्ण

	अगर (!s3c24xx_spi_usingfiq(hw)) अणु
		hw->count++;

		अगर (hw->rx)
			hw->rx[count] = पढ़ोb(hw->regs + S3C2410_SPRDAT);

		count++;

		अगर (count < hw->len)
			ग_लिखोb(hw_txbyte(hw, count), hw->regs + S3C2410_SPTDAT);
		अन्यथा
			complete(&hw->करोne);
	पूर्ण अन्यथा अणु
		hw->count = hw->len;
		hw->fiq_inuse = 0;

		अगर (hw->rx)
			hw->rx[hw->len-1] = पढ़ोb(hw->regs + S3C2410_SPRDAT);

		complete(&hw->करोne);
	पूर्ण

 irq_करोne:
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम s3c24xx_spi_initialsetup(काष्ठा s3c24xx_spi *hw)
अणु
	/* क्रम the moment, permanently enable the घड़ी */

	clk_enable(hw->clk);

	/* program शेषs पूर्णांकo the रेजिस्टरs */

	ग_लिखोb(0xff, hw->regs + S3C2410_SPPRE);
	ग_लिखोb(SPPIN_DEFAULT, hw->regs + S3C2410_SPPIN);
	ग_लिखोb(SPCON_DEFAULT, hw->regs + S3C2410_SPCON);

	अगर (hw->pdata) अणु
		अगर (hw->set_cs == s3c24xx_spi_gpiocs)
			gpio_direction_output(hw->pdata->pin_cs, 1);

		अगर (hw->pdata->gpio_setup)
			hw->pdata->gpio_setup(hw->pdata, 1);
	पूर्ण
पूर्ण

अटल पूर्णांक s3c24xx_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा s3c2410_spi_info *pdata;
	काष्ठा s3c24xx_spi *hw;
	काष्ठा spi_master *master;
	पूर्णांक err = 0;

	master = spi_alloc_master(&pdev->dev, माप(काष्ठा s3c24xx_spi));
	अगर (master == शून्य) अणु
		dev_err(&pdev->dev, "No memory for spi_master\n");
		वापस -ENOMEM;
	पूर्ण

	hw = spi_master_get_devdata(master);

	hw->master = master;
	hw->pdata = pdata = dev_get_platdata(&pdev->dev);
	hw->dev = &pdev->dev;

	अगर (pdata == शून्य) अणु
		dev_err(&pdev->dev, "No platform data supplied\n");
		err = -ENOENT;
		जाओ err_no_pdata;
	पूर्ण

	platक्रमm_set_drvdata(pdev, hw);
	init_completion(&hw->करोne);

	/* initialise fiq handler */

	s3c24xx_spi_initfiq(hw);

	/* setup the master state. */

	/* the spi->mode bits understood by this driver: */
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH;

	master->num_chipselect = hw->pdata->num_cs;
	master->bus_num = pdata->bus_num;
	master->bits_per_word_mask = SPI_BPW_MASK(8);

	/* setup the state क्रम the bitbang driver */

	hw->bitbang.master         = hw->master;
	hw->bitbang.setup_transfer = s3c24xx_spi_setupxfer;
	hw->bitbang.chipselect     = s3c24xx_spi_chipsel;
	hw->bitbang.txrx_bufs      = s3c24xx_spi_txrx;

	hw->master->setup  = s3c24xx_spi_setup;

	dev_dbg(hw->dev, "bitbang at %p\n", &hw->bitbang);

	/* find and map our resources */
	hw->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(hw->regs)) अणु
		err = PTR_ERR(hw->regs);
		जाओ err_no_pdata;
	पूर्ण

	hw->irq = platक्रमm_get_irq(pdev, 0);
	अगर (hw->irq < 0) अणु
		err = -ENOENT;
		जाओ err_no_pdata;
	पूर्ण

	err = devm_request_irq(&pdev->dev, hw->irq, s3c24xx_spi_irq, 0,
				pdev->name, hw);
	अगर (err) अणु
		dev_err(&pdev->dev, "Cannot claim IRQ\n");
		जाओ err_no_pdata;
	पूर्ण

	hw->clk = devm_clk_get(&pdev->dev, "spi");
	अगर (IS_ERR(hw->clk)) अणु
		dev_err(&pdev->dev, "No clock for device\n");
		err = PTR_ERR(hw->clk);
		जाओ err_no_pdata;
	पूर्ण

	/* setup any gpio we can */

	अगर (!pdata->set_cs) अणु
		अगर (pdata->pin_cs < 0) अणु
			dev_err(&pdev->dev, "No chipselect pin\n");
			err = -EINVAL;
			जाओ err_रेजिस्टर;
		पूर्ण

		err = devm_gpio_request(&pdev->dev, pdata->pin_cs,
					dev_name(&pdev->dev));
		अगर (err) अणु
			dev_err(&pdev->dev, "Failed to get gpio for cs\n");
			जाओ err_रेजिस्टर;
		पूर्ण

		hw->set_cs = s3c24xx_spi_gpiocs;
		gpio_direction_output(pdata->pin_cs, 1);
	पूर्ण अन्यथा
		hw->set_cs = pdata->set_cs;

	s3c24xx_spi_initialsetup(hw);

	/* रेजिस्टर our spi controller */

	err = spi_bitbang_start(&hw->bitbang);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to register SPI master\n");
		जाओ err_रेजिस्टर;
	पूर्ण

	वापस 0;

 err_रेजिस्टर:
	clk_disable(hw->clk);

 err_no_pdata:
	spi_master_put(hw->master);
	वापस err;
पूर्ण

अटल पूर्णांक s3c24xx_spi_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा s3c24xx_spi *hw = platक्रमm_get_drvdata(dev);

	spi_bitbang_stop(&hw->bitbang);
	clk_disable(hw->clk);
	spi_master_put(hw->master);
	वापस 0;
पूर्ण


#अगर_घोषित CONFIG_PM

अटल पूर्णांक s3c24xx_spi_suspend(काष्ठा device *dev)
अणु
	काष्ठा s3c24xx_spi *hw = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = spi_master_suspend(hw->master);
	अगर (ret)
		वापस ret;

	अगर (hw->pdata && hw->pdata->gpio_setup)
		hw->pdata->gpio_setup(hw->pdata, 0);

	clk_disable(hw->clk);
	वापस 0;
पूर्ण

अटल पूर्णांक s3c24xx_spi_resume(काष्ठा device *dev)
अणु
	काष्ठा s3c24xx_spi *hw = dev_get_drvdata(dev);

	s3c24xx_spi_initialsetup(hw);
	वापस spi_master_resume(hw->master);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops s3c24xx_spi_pmops = अणु
	.suspend	= s3c24xx_spi_suspend,
	.resume		= s3c24xx_spi_resume,
पूर्ण;

#घोषणा S3C24XX_SPI_PMOPS &s3c24xx_spi_pmops
#अन्यथा
#घोषणा S3C24XX_SPI_PMOPS शून्य
#पूर्ण_अगर /* CONFIG_PM */

MODULE_ALIAS("platform:s3c2410-spi");
अटल काष्ठा platक्रमm_driver s3c24xx_spi_driver = अणु
	.probe		= s3c24xx_spi_probe,
	.हटाओ		= s3c24xx_spi_हटाओ,
	.driver		= अणु
		.name	= "s3c2410-spi",
		.pm	= S3C24XX_SPI_PMOPS,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(s3c24xx_spi_driver);

MODULE_DESCRIPTION("S3C24XX SPI Driver");
MODULE_AUTHOR("Ben Dooks, <ben@simtec.co.uk>");
MODULE_LICENSE("GPL");
