<शैली गुरु>
/*
 * MicroWire पूर्णांकerface driver क्रम OMAP
 *
 * Copyright 2003 MontaVista Software Inc. <source@mvista.com>
 *
 * Ported to 2.6 OMAP uwire पूर्णांकerface.
 * Copyright (C) 2004 Texas Instruments.
 *
 * Generalization patches by Juha Yrjola <juha.yrjola@nokia.com>
 *
 * Copyright (C) 2005 David Brownell (ported to 2.6 SPI पूर्णांकerface)
 * Copyright (C) 2006 Nokia
 *
 * Many updates by Imre Deak <imre.deak@nokia.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY सूचीECT, INसूचीECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>

#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi_bitbang.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>

#समावेश <mach/hardware.h>
#समावेश <यंत्र/mach-types.h>

#समावेश <mach/mux.h>

#समावेश <mach/omap7xx.h>	/* OMAP7XX_IO_CONF रेजिस्टरs */


/* FIXME address is now a platक्रमm device resource,
 * and irqs should show there too...
 */
#घोषणा UWIRE_BASE_PHYS		0xFFFB3000

/* uWire Registers: */
#घोषणा UWIRE_IO_SIZE 0x20
#घोषणा UWIRE_TDR     0x00
#घोषणा UWIRE_RDR     0x00
#घोषणा UWIRE_CSR     0x01
#घोषणा UWIRE_SR1     0x02
#घोषणा UWIRE_SR2     0x03
#घोषणा UWIRE_SR3     0x04
#घोषणा UWIRE_SR4     0x05
#घोषणा UWIRE_SR5     0x06

/* CSR bits */
#घोषणा	RDRB	(1 << 15)
#घोषणा	CSRB	(1 << 14)
#घोषणा	START	(1 << 13)
#घोषणा	CS_CMD	(1 << 12)

/* SR1 or SR2 bits */
#घोषणा UWIRE_READ_FALLING_EDGE		0x0001
#घोषणा UWIRE_READ_RISING_EDGE		0x0000
#घोषणा UWIRE_WRITE_FALLING_EDGE	0x0000
#घोषणा UWIRE_WRITE_RISING_EDGE		0x0002
#घोषणा UWIRE_CS_ACTIVE_LOW		0x0000
#घोषणा UWIRE_CS_ACTIVE_HIGH		0x0004
#घोषणा UWIRE_FREQ_DIV_2		0x0000
#घोषणा UWIRE_FREQ_DIV_4		0x0008
#घोषणा UWIRE_FREQ_DIV_8		0x0010
#घोषणा UWIRE_CHK_READY			0x0020
#घोषणा UWIRE_CLK_INVERTED		0x0040


काष्ठा uwire_spi अणु
	काष्ठा spi_bitbang	bitbang;
	काष्ठा clk		*ck;
पूर्ण;

काष्ठा uwire_state अणु
	अचिन्हित	भाग1_idx;
पूर्ण;

/* REVISIT compile समय स्थिरant क्रम idx_shअगरt? */
/*
 * Or, put it in a काष्ठाure which is used throughout the driver;
 * that aव्योमs having to issue two loads क्रम each bit of अटल data.
 */
अटल अचिन्हित पूर्णांक uwire_idx_shअगरt;
अटल व्योम __iomem *uwire_base;

अटल अंतरभूत व्योम uwire_ग_लिखो_reg(पूर्णांक idx, u16 val)
अणु
	__raw_ग_लिखोw(val, uwire_base + (idx << uwire_idx_shअगरt));
पूर्ण

अटल अंतरभूत u16 uwire_पढ़ो_reg(पूर्णांक idx)
अणु
	वापस __raw_पढ़ोw(uwire_base + (idx << uwire_idx_shअगरt));
पूर्ण

अटल अंतरभूत व्योम omap_uwire_configure_mode(u8 cs, अचिन्हित दीर्घ flags)
अणु
	u16	w, val = 0;
	पूर्णांक	shअगरt, reg;

	अगर (flags & UWIRE_CLK_INVERTED)
		val ^= 0x03;
	val = flags & 0x3f;
	अगर (cs & 1)
		shअगरt = 6;
	अन्यथा
		shअगरt = 0;
	अगर (cs <= 1)
		reg = UWIRE_SR1;
	अन्यथा
		reg = UWIRE_SR2;

	w = uwire_पढ़ो_reg(reg);
	w &= ~(0x3f << shअगरt);
	w |= val << shअगरt;
	uwire_ग_लिखो_reg(reg, w);
पूर्ण

अटल पूर्णांक रुको_uwire_csr_flag(u16 mask, u16 val, पूर्णांक might_not_catch)
अणु
	u16 w;
	पूर्णांक c = 0;
	अचिन्हित दीर्घ max_jअगरfies = jअगरfies + HZ;

	क्रम (;;) अणु
		w = uwire_पढ़ो_reg(UWIRE_CSR);
		अगर ((w & mask) == val)
			अवरोध;
		अगर (समय_after(jअगरfies, max_jअगरfies)) अणु
			prपूर्णांकk(KERN_ERR "%s: timeout. reg=%#06x "
					"mask=%#06x val=%#06x\n",
			       __func__, w, mask, val);
			वापस -1;
		पूर्ण
		c++;
		अगर (might_not_catch && c > 64)
			अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम uwire_set_clk1_भाग(पूर्णांक भाग1_idx)
अणु
	u16 w;

	w = uwire_पढ़ो_reg(UWIRE_SR3);
	w &= ~(0x03 << 1);
	w |= भाग1_idx << 1;
	uwire_ग_लिखो_reg(UWIRE_SR3, w);
पूर्ण

अटल व्योम uwire_chipselect(काष्ठा spi_device *spi, पूर्णांक value)
अणु
	काष्ठा	uwire_state *ust = spi->controller_state;
	u16	w;
	पूर्णांक	old_cs;


	BUG_ON(रुको_uwire_csr_flag(CSRB, 0, 0));

	w = uwire_पढ़ो_reg(UWIRE_CSR);
	old_cs = (w >> 10) & 0x03;
	अगर (value == BITBANG_CS_INACTIVE || old_cs != spi->chip_select) अणु
		/* Deselect this CS, or the previous CS */
		w &= ~CS_CMD;
		uwire_ग_लिखो_reg(UWIRE_CSR, w);
	पूर्ण
	/* activate specfied chipselect */
	अगर (value == BITBANG_CS_ACTIVE) अणु
		uwire_set_clk1_भाग(ust->भाग1_idx);
		/* invert घड़ी? */
		अगर (spi->mode & SPI_CPOL)
			uwire_ग_लिखो_reg(UWIRE_SR4, 1);
		अन्यथा
			uwire_ग_लिखो_reg(UWIRE_SR4, 0);

		w = spi->chip_select << 10;
		w |= CS_CMD;
		uwire_ग_लिखो_reg(UWIRE_CSR, w);
	पूर्ण
पूर्ण

अटल पूर्णांक uwire_txrx(काष्ठा spi_device *spi, काष्ठा spi_transfer *t)
अणु
	अचिन्हित	len = t->len;
	अचिन्हित	bits = t->bits_per_word;
	अचिन्हित	bytes;
	u16		val, w;
	पूर्णांक		status = 0;

	अगर (!t->tx_buf && !t->rx_buf)
		वापस 0;

	w = spi->chip_select << 10;
	w |= CS_CMD;

	अगर (t->tx_buf) अणु
		स्थिर u8	*buf = t->tx_buf;

		/* NOTE:  DMA could be used क्रम TX transfers */

		/* ग_लिखो one or two bytes at a समय */
		जबतक (len >= 1) अणु
			/* tx bit 15 is first sent; we byteswap multibyte words
			 * (msb-first) on the way out from memory.
			 */
			val = *buf++;
			अगर (bits > 8) अणु
				bytes = 2;
				val |= *buf++ << 8;
			पूर्ण अन्यथा
				bytes = 1;
			val <<= 16 - bits;

#अगर_घोषित	VERBOSE
			pr_debug("%s: write-%d =%04x\n",
					dev_name(&spi->dev), bits, val);
#पूर्ण_अगर
			अगर (रुको_uwire_csr_flag(CSRB, 0, 0))
				जाओ eio;

			uwire_ग_लिखो_reg(UWIRE_TDR, val);

			/* start ग_लिखो */
			val = START | w | (bits << 5);

			uwire_ग_लिखो_reg(UWIRE_CSR, val);
			len -= bytes;

			/* Wait till ग_लिखो actually starts.
			 * This is needed with MPU घड़ी 60+ MHz.
			 * REVISIT: we may not have समय to catch it...
			 */
			अगर (रुको_uwire_csr_flag(CSRB, CSRB, 1))
				जाओ eio;

			status += bytes;
		पूर्ण

		/* REVISIT:  save this क्रम later to get more i/o overlap */
		अगर (रुको_uwire_csr_flag(CSRB, 0, 0))
			जाओ eio;

	पूर्ण अन्यथा अगर (t->rx_buf) अणु
		u8		*buf = t->rx_buf;

		/* पढ़ो one or two bytes at a समय */
		जबतक (len) अणु
			अगर (bits > 8) अणु
				bytes = 2;
			पूर्ण अन्यथा
				bytes = 1;

			/* start पढ़ो */
			val = START | w | (bits << 0);
			uwire_ग_लिखो_reg(UWIRE_CSR, val);
			len -= bytes;

			/* Wait till पढ़ो actually starts */
			(व्योम) रुको_uwire_csr_flag(CSRB, CSRB, 1);

			अगर (रुको_uwire_csr_flag(RDRB | CSRB,
						RDRB, 0))
				जाओ eio;

			/* rx bit 0 is last received; multibyte words will
			 * be properly byteswapped on the way to memory.
			 */
			val = uwire_पढ़ो_reg(UWIRE_RDR);
			val &= (1 << bits) - 1;
			*buf++ = (u8) val;
			अगर (bytes == 2)
				*buf++ = val >> 8;
			status += bytes;
#अगर_घोषित	VERBOSE
			pr_debug("%s: read-%d =%04x\n",
					dev_name(&spi->dev), bits, val);
#पूर्ण_अगर

		पूर्ण
	पूर्ण
	वापस status;
eio:
	वापस -EIO;
पूर्ण

अटल पूर्णांक uwire_setup_transfer(काष्ठा spi_device *spi, काष्ठा spi_transfer *t)
अणु
	काष्ठा uwire_state	*ust = spi->controller_state;
	काष्ठा uwire_spi	*uwire;
	अचिन्हित		flags = 0;
	अचिन्हित		hz;
	अचिन्हित दीर्घ		rate;
	पूर्णांक			भाग1_idx;
	पूर्णांक			भाग1;
	पूर्णांक			भाग2;
	पूर्णांक			status;

	uwire = spi_master_get_devdata(spi->master);

	/* mode 0..3, घड़ी inverted separately;
	 * standard nCS संकेतing;
	 * करोn't treat DI=high as "not ready"
	 */
	अगर (spi->mode & SPI_CS_HIGH)
		flags |= UWIRE_CS_ACTIVE_HIGH;

	अगर (spi->mode & SPI_CPOL)
		flags |= UWIRE_CLK_INVERTED;

	चयन (spi->mode & (SPI_CPOL | SPI_CPHA)) अणु
	हाल SPI_MODE_0:
	हाल SPI_MODE_3:
		flags |= UWIRE_WRITE_FALLING_EDGE | UWIRE_READ_RISING_EDGE;
		अवरोध;
	हाल SPI_MODE_1:
	हाल SPI_MODE_2:
		flags |= UWIRE_WRITE_RISING_EDGE | UWIRE_READ_FALLING_EDGE;
		अवरोध;
	पूर्ण

	/* assume it's alपढ़ोy enabled */
	rate = clk_get_rate(uwire->ck);

	अगर (t != शून्य)
		hz = t->speed_hz;
	अन्यथा
		hz = spi->max_speed_hz;

	अगर (!hz) अणु
		pr_debug("%s: zero speed?\n", dev_name(&spi->dev));
		status = -EINVAL;
		जाओ करोne;
	पूर्ण

	/* F_INT = mpu_xor_clk / DIV1 */
	क्रम (भाग1_idx = 0; भाग1_idx < 4; भाग1_idx++) अणु
		चयन (भाग1_idx) अणु
		हाल 0:
			भाग1 = 2;
			अवरोध;
		हाल 1:
			भाग1 = 4;
			अवरोध;
		हाल 2:
			भाग1 = 7;
			अवरोध;
		शेष:
		हाल 3:
			भाग1 = 10;
			अवरोध;
		पूर्ण
		भाग2 = (rate / भाग1 + hz - 1) / hz;
		अगर (भाग2 <= 8)
			अवरोध;
	पूर्ण
	अगर (भाग1_idx == 4) अणु
		pr_debug("%s: lowest clock %ld, need %d\n",
			dev_name(&spi->dev), rate / 10 / 8, hz);
		status = -गलत_तर्क;
		जाओ करोne;
	पूर्ण

	/* we have to cache this and reset in uwire_chipselect as this is a
	 * global parameter and another uwire device can change it under
	 * us */
	ust->भाग1_idx = भाग1_idx;
	uwire_set_clk1_भाग(भाग1_idx);

	rate /= भाग1;

	चयन (भाग2) अणु
	हाल 0:
	हाल 1:
	हाल 2:
		flags |= UWIRE_FREQ_DIV_2;
		rate /= 2;
		अवरोध;
	हाल 3:
	हाल 4:
		flags |= UWIRE_FREQ_DIV_4;
		rate /= 4;
		अवरोध;
	हाल 5:
	हाल 6:
	हाल 7:
	हाल 8:
		flags |= UWIRE_FREQ_DIV_8;
		rate /= 8;
		अवरोध;
	पूर्ण
	omap_uwire_configure_mode(spi->chip_select, flags);
	pr_debug("%s: uwire flags %02x, armxor %lu KHz, SCK %lu KHz\n",
			__func__, flags,
			clk_get_rate(uwire->ck) / 1000,
			rate / 1000);
	status = 0;
करोne:
	वापस status;
पूर्ण

अटल पूर्णांक uwire_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा uwire_state *ust = spi->controller_state;
	bool initial_setup = false;
	पूर्णांक status;

	अगर (ust == शून्य) अणु
		ust = kzalloc(माप(*ust), GFP_KERNEL);
		अगर (ust == शून्य)
			वापस -ENOMEM;
		spi->controller_state = ust;
		initial_setup = true;
	पूर्ण

	status = uwire_setup_transfer(spi, शून्य);
	अगर (status && initial_setup)
		kमुक्त(ust);

	वापस status;
पूर्ण

अटल व्योम uwire_cleanup(काष्ठा spi_device *spi)
अणु
	kमुक्त(spi->controller_state);
पूर्ण

अटल व्योम uwire_off(काष्ठा uwire_spi *uwire)
अणु
	uwire_ग_लिखो_reg(UWIRE_SR3, 0);
	clk_disable_unprepare(uwire->ck);
	spi_master_put(uwire->bitbang.master);
पूर्ण

अटल पूर्णांक uwire_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master	*master;
	काष्ठा uwire_spi	*uwire;
	पूर्णांक			status;

	master = spi_alloc_master(&pdev->dev, माप *uwire);
	अगर (!master)
		वापस -ENODEV;

	uwire = spi_master_get_devdata(master);

	uwire_base = devm_ioremap(&pdev->dev, UWIRE_BASE_PHYS, UWIRE_IO_SIZE);
	अगर (!uwire_base) अणु
		dev_dbg(&pdev->dev, "can't ioremap UWIRE\n");
		spi_master_put(master);
		वापस -ENOMEM;
	पूर्ण

	platक्रमm_set_drvdata(pdev, uwire);

	uwire->ck = devm_clk_get(&pdev->dev, "fck");
	अगर (IS_ERR(uwire->ck)) अणु
		status = PTR_ERR(uwire->ck);
		dev_dbg(&pdev->dev, "no functional clock?\n");
		spi_master_put(master);
		वापस status;
	पूर्ण
	clk_prepare_enable(uwire->ck);

	अगर (cpu_is_omap7xx())
		uwire_idx_shअगरt = 1;
	अन्यथा
		uwire_idx_shअगरt = 2;

	uwire_ग_लिखो_reg(UWIRE_SR3, 1);

	/* the spi->mode bits understood by this driver: */
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH;
	master->bits_per_word_mask = SPI_BPW_RANGE_MASK(1, 16);
	master->flags = SPI_MASTER_HALF_DUPLEX;

	master->bus_num = 2;	/* "official" */
	master->num_chipselect = 4;
	master->setup = uwire_setup;
	master->cleanup = uwire_cleanup;

	uwire->bitbang.master = master;
	uwire->bitbang.chipselect = uwire_chipselect;
	uwire->bitbang.setup_transfer = uwire_setup_transfer;
	uwire->bitbang.txrx_bufs = uwire_txrx;

	status = spi_bitbang_start(&uwire->bitbang);
	अगर (status < 0) अणु
		uwire_off(uwire);
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक uwire_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uwire_spi	*uwire = platक्रमm_get_drvdata(pdev);

	// FIXME हटाओ all child devices, somewhere ...

	spi_bitbang_stop(&uwire->bitbang);
	uwire_off(uwire);
	वापस 0;
पूर्ण

/* work with hotplug and coldplug */
MODULE_ALIAS("platform:omap_uwire");

अटल काष्ठा platक्रमm_driver uwire_driver = अणु
	.driver = अणु
		.name		= "omap_uwire",
	पूर्ण,
	.probe = uwire_probe,
	.हटाओ = uwire_हटाओ,
	// suspend ... unuse ck
	// resume ... use ck
पूर्ण;

अटल पूर्णांक __init omap_uwire_init(व्योम)
अणु
	/* FIXME move these पूर्णांकo the relevant board init code. also, include
	 * H3 support; it uses tsc2101 like H2 (on a dअगरferent chipselect).
	 */

	अगर (machine_is_omap_h2()) अणु
		/* शेषs: W21 SDO, U18 SDI, V19 SCL */
		omap_cfg_reg(N14_1610_UWIRE_CS0);
		omap_cfg_reg(N15_1610_UWIRE_CS1);
	पूर्ण
	अगर (machine_is_omap_perseus2()) अणु
		/* configure pins: MPU_UW_nSCS1, MPU_UW_SDO, MPU_UW_SCLK */
		पूर्णांक val = omap_पढ़ोl(OMAP7XX_IO_CONF_9) & ~0x00EEE000;
		omap_ग_लिखोl(val | 0x00AAA000, OMAP7XX_IO_CONF_9);
	पूर्ण

	वापस platक्रमm_driver_रेजिस्टर(&uwire_driver);
पूर्ण

अटल व्योम __निकास omap_uwire_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&uwire_driver);
पूर्ण

subsys_initcall(omap_uwire_init);
module_निकास(omap_uwire_निकास);

MODULE_LICENSE("GPL");

