<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Broadcom BCM2835 auxiliary SPI Controllers
 *
 * the driver करोes not rely on the native chipselects at all
 * but only uses the gpio type chipselects
 *
 * Based on: spi-bcm2835.c
 *
 * Copyright (C) 2015 Martin Sperl
 */

#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_irq.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spinlock.h>

/* define polling limits */
अटल अचिन्हित पूर्णांक polling_limit_us = 30;
module_param(polling_limit_us, uपूर्णांक, 0664);
MODULE_PARM_DESC(polling_limit_us,
		 "time in us to run a transfer in polling mode - if zero no polling is used\n");

/*
 * spi रेजिस्टर defines
 *
 * note there is garbage in the "official" करोcumentation,
 * so some data is taken from the file:
 *   brcm_usrlib/dag/vmcsx/vcinclude/bcm2708_chip/aux_पन.स
 * inside of:
 *   http://www.broadcom.com/करोcs/support/videocore/Brcm_Android_ICS_Graphics_Stack.tar.gz
 */

/* SPI रेजिस्टर offsets */
#घोषणा BCM2835_AUX_SPI_CNTL0	0x00
#घोषणा BCM2835_AUX_SPI_CNTL1	0x04
#घोषणा BCM2835_AUX_SPI_STAT	0x08
#घोषणा BCM2835_AUX_SPI_PEEK	0x0C
#घोषणा BCM2835_AUX_SPI_IO	0x20
#घोषणा BCM2835_AUX_SPI_TXHOLD	0x30

/* Bitfields in CNTL0 */
#घोषणा BCM2835_AUX_SPI_CNTL0_SPEED	0xFFF00000
#घोषणा BCM2835_AUX_SPI_CNTL0_SPEED_MAX	0xFFF
#घोषणा BCM2835_AUX_SPI_CNTL0_SPEED_SHIFT	20
#घोषणा BCM2835_AUX_SPI_CNTL0_CS	0x000E0000
#घोषणा BCM2835_AUX_SPI_CNTL0_POSTINPUT	0x00010000
#घोषणा BCM2835_AUX_SPI_CNTL0_VAR_CS	0x00008000
#घोषणा BCM2835_AUX_SPI_CNTL0_VAR_WIDTH	0x00004000
#घोषणा BCM2835_AUX_SPI_CNTL0_DOUTHOLD	0x00003000
#घोषणा BCM2835_AUX_SPI_CNTL0_ENABLE	0x00000800
#घोषणा BCM2835_AUX_SPI_CNTL0_IN_RISING	0x00000400
#घोषणा BCM2835_AUX_SPI_CNTL0_CLEARFIFO	0x00000200
#घोषणा BCM2835_AUX_SPI_CNTL0_OUT_RISING	0x00000100
#घोषणा BCM2835_AUX_SPI_CNTL0_CPOL	0x00000080
#घोषणा BCM2835_AUX_SPI_CNTL0_MSBF_OUT	0x00000040
#घोषणा BCM2835_AUX_SPI_CNTL0_SHIFTLEN	0x0000003F

/* Bitfields in CNTL1 */
#घोषणा BCM2835_AUX_SPI_CNTL1_CSHIGH	0x00000700
#घोषणा BCM2835_AUX_SPI_CNTL1_TXEMPTY	0x00000080
#घोषणा BCM2835_AUX_SPI_CNTL1_IDLE	0x00000040
#घोषणा BCM2835_AUX_SPI_CNTL1_MSBF_IN	0x00000002
#घोषणा BCM2835_AUX_SPI_CNTL1_KEEP_IN	0x00000001

/* Bitfields in STAT */
#घोषणा BCM2835_AUX_SPI_STAT_TX_LVL	0xFF000000
#घोषणा BCM2835_AUX_SPI_STAT_RX_LVL	0x00FF0000
#घोषणा BCM2835_AUX_SPI_STAT_TX_FULL	0x00000400
#घोषणा BCM2835_AUX_SPI_STAT_TX_EMPTY	0x00000200
#घोषणा BCM2835_AUX_SPI_STAT_RX_FULL	0x00000100
#घोषणा BCM2835_AUX_SPI_STAT_RX_EMPTY	0x00000080
#घोषणा BCM2835_AUX_SPI_STAT_BUSY	0x00000040
#घोषणा BCM2835_AUX_SPI_STAT_BITCOUNT	0x0000003F

काष्ठा bcm2835aux_spi अणु
	व्योम __iomem *regs;
	काष्ठा clk *clk;
	पूर्णांक irq;
	u32 cntl[2];
	स्थिर u8 *tx_buf;
	u8 *rx_buf;
	पूर्णांक tx_len;
	पूर्णांक rx_len;
	पूर्णांक pending;

	u64 count_transfer_polling;
	u64 count_transfer_irq;
	u64 count_transfer_irq_after_poll;

	काष्ठा dentry *debugfs_dir;
पूर्ण;

#अगर defined(CONFIG_DEBUG_FS)
अटल व्योम bcm2835aux_debugfs_create(काष्ठा bcm2835aux_spi *bs,
				      स्थिर अक्षर *dname)
अणु
	अक्षर name[64];
	काष्ठा dentry *dir;

	/* get full name */
	snम_लिखो(name, माप(name), "spi-bcm2835aux-%s", dname);

	/* the base directory */
	dir = debugfs_create_dir(name, शून्य);
	bs->debugfs_dir = dir;

	/* the counters */
	debugfs_create_u64("count_transfer_polling", 0444, dir,
			   &bs->count_transfer_polling);
	debugfs_create_u64("count_transfer_irq", 0444, dir,
			   &bs->count_transfer_irq);
	debugfs_create_u64("count_transfer_irq_after_poll", 0444, dir,
			   &bs->count_transfer_irq_after_poll);
पूर्ण

अटल व्योम bcm2835aux_debugfs_हटाओ(काष्ठा bcm2835aux_spi *bs)
अणु
	debugfs_हटाओ_recursive(bs->debugfs_dir);
	bs->debugfs_dir = शून्य;
पूर्ण
#अन्यथा
अटल व्योम bcm2835aux_debugfs_create(काष्ठा bcm2835aux_spi *bs,
				      स्थिर अक्षर *dname)
अणु
पूर्ण

अटल व्योम bcm2835aux_debugfs_हटाओ(काष्ठा bcm2835aux_spi *bs)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

अटल अंतरभूत u32 bcm2835aux_rd(काष्ठा bcm2835aux_spi *bs, अचिन्हित reg)
अणु
	वापस पढ़ोl(bs->regs + reg);
पूर्ण

अटल अंतरभूत व्योम bcm2835aux_wr(काष्ठा bcm2835aux_spi *bs, अचिन्हित reg,
				 u32 val)
अणु
	ग_लिखोl(val, bs->regs + reg);
पूर्ण

अटल अंतरभूत व्योम bcm2835aux_rd_fअगरo(काष्ठा bcm2835aux_spi *bs)
अणु
	u32 data;
	पूर्णांक count = min(bs->rx_len, 3);

	data = bcm2835aux_rd(bs, BCM2835_AUX_SPI_IO);
	अगर (bs->rx_buf) अणु
		चयन (count) अणु
		हाल 3:
			*bs->rx_buf++ = (data >> 16) & 0xff;
			fallthrough;
		हाल 2:
			*bs->rx_buf++ = (data >> 8) & 0xff;
			fallthrough;
		हाल 1:
			*bs->rx_buf++ = (data >> 0) & 0xff;
			/* fallthrough - no शेष */
		पूर्ण
	पूर्ण
	bs->rx_len -= count;
	bs->pending -= count;
पूर्ण

अटल अंतरभूत व्योम bcm2835aux_wr_fअगरo(काष्ठा bcm2835aux_spi *bs)
अणु
	u32 data;
	u8 byte;
	पूर्णांक count;
	पूर्णांक i;

	/* gather up to 3 bytes to ग_लिखो to the FIFO */
	count = min(bs->tx_len, 3);
	data = 0;
	क्रम (i = 0; i < count; i++) अणु
		byte = bs->tx_buf ? *bs->tx_buf++ : 0;
		data |= byte << (8 * (2 - i));
	पूर्ण

	/* and set the variable bit-length */
	data |= (count * 8) << 24;

	/* and decrement length */
	bs->tx_len -= count;
	bs->pending += count;

	/* ग_लिखो to the correct TX-रेजिस्टर */
	अगर (bs->tx_len)
		bcm2835aux_wr(bs, BCM2835_AUX_SPI_TXHOLD, data);
	अन्यथा
		bcm2835aux_wr(bs, BCM2835_AUX_SPI_IO, data);
पूर्ण

अटल व्योम bcm2835aux_spi_reset_hw(काष्ठा bcm2835aux_spi *bs)
अणु
	/* disable spi clearing fअगरo and पूर्णांकerrupts */
	bcm2835aux_wr(bs, BCM2835_AUX_SPI_CNTL1, 0);
	bcm2835aux_wr(bs, BCM2835_AUX_SPI_CNTL0,
		      BCM2835_AUX_SPI_CNTL0_CLEARFIFO);
पूर्ण

अटल व्योम bcm2835aux_spi_transfer_helper(काष्ठा bcm2835aux_spi *bs)
अणु
	u32 stat = bcm2835aux_rd(bs, BCM2835_AUX_SPI_STAT);

	/* check अगर we have data to पढ़ो */
	क्रम (; bs->rx_len && (stat & BCM2835_AUX_SPI_STAT_RX_LVL);
	     stat = bcm2835aux_rd(bs, BCM2835_AUX_SPI_STAT))
		bcm2835aux_rd_fअगरo(bs);

	/* check अगर we have data to ग_लिखो */
	जबतक (bs->tx_len &&
	       (bs->pending < 12) &&
	       (!(bcm2835aux_rd(bs, BCM2835_AUX_SPI_STAT) &
		  BCM2835_AUX_SPI_STAT_TX_FULL))) अणु
		bcm2835aux_wr_fअगरo(bs);
	पूर्ण
पूर्ण

अटल irqवापस_t bcm2835aux_spi_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा spi_master *master = dev_id;
	काष्ठा bcm2835aux_spi *bs = spi_master_get_devdata(master);

	/* IRQ may be shared, so वापस अगर our पूर्णांकerrupts are disabled */
	अगर (!(bcm2835aux_rd(bs, BCM2835_AUX_SPI_CNTL1) &
	      (BCM2835_AUX_SPI_CNTL1_TXEMPTY | BCM2835_AUX_SPI_CNTL1_IDLE)))
		वापस IRQ_NONE;

	/* करो common fअगरo handling */
	bcm2835aux_spi_transfer_helper(bs);

	अगर (!bs->tx_len) अणु
		/* disable tx fअगरo empty पूर्णांकerrupt */
		bcm2835aux_wr(bs, BCM2835_AUX_SPI_CNTL1, bs->cntl[1] |
			BCM2835_AUX_SPI_CNTL1_IDLE);
	पूर्ण

	/* and अगर rx_len is 0 then disable पूर्णांकerrupts and wake up completion */
	अगर (!bs->rx_len) अणु
		bcm2835aux_wr(bs, BCM2835_AUX_SPI_CNTL1, bs->cntl[1]);
		spi_finalize_current_transfer(master);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __bcm2835aux_spi_transfer_one_irq(काष्ठा spi_master *master,
					     काष्ठा spi_device *spi,
					     काष्ठा spi_transfer *tfr)
अणु
	काष्ठा bcm2835aux_spi *bs = spi_master_get_devdata(master);

	/* enable पूर्णांकerrupts */
	bcm2835aux_wr(bs, BCM2835_AUX_SPI_CNTL1, bs->cntl[1] |
		BCM2835_AUX_SPI_CNTL1_TXEMPTY |
		BCM2835_AUX_SPI_CNTL1_IDLE);

	/* and रुको क्रम finish... */
	वापस 1;
पूर्ण

अटल पूर्णांक bcm2835aux_spi_transfer_one_irq(काष्ठा spi_master *master,
					   काष्ठा spi_device *spi,
					   काष्ठा spi_transfer *tfr)
अणु
	काष्ठा bcm2835aux_spi *bs = spi_master_get_devdata(master);

	/* update statistics */
	bs->count_transfer_irq++;

	/* fill in रेजिस्टरs and fअगरos beक्रमe enabling पूर्णांकerrupts */
	bcm2835aux_wr(bs, BCM2835_AUX_SPI_CNTL1, bs->cntl[1]);
	bcm2835aux_wr(bs, BCM2835_AUX_SPI_CNTL0, bs->cntl[0]);

	/* fill in tx fअगरo with data beक्रमe enabling पूर्णांकerrupts */
	जबतक ((bs->tx_len) &&
	       (bs->pending < 12) &&
	       (!(bcm2835aux_rd(bs, BCM2835_AUX_SPI_STAT) &
		  BCM2835_AUX_SPI_STAT_TX_FULL))) अणु
		bcm2835aux_wr_fअगरo(bs);
	पूर्ण

	/* now run the पूर्णांकerrupt mode */
	वापस __bcm2835aux_spi_transfer_one_irq(master, spi, tfr);
पूर्ण

अटल पूर्णांक bcm2835aux_spi_transfer_one_poll(काष्ठा spi_master *master,
					    काष्ठा spi_device *spi,
					काष्ठा spi_transfer *tfr)
अणु
	काष्ठा bcm2835aux_spi *bs = spi_master_get_devdata(master);
	अचिन्हित दीर्घ समयout;

	/* update statistics */
	bs->count_transfer_polling++;

	/* configure spi */
	bcm2835aux_wr(bs, BCM2835_AUX_SPI_CNTL1, bs->cntl[1]);
	bcm2835aux_wr(bs, BCM2835_AUX_SPI_CNTL0, bs->cntl[0]);

	/* set the समयout to at least 2 jअगरfies */
	समयout = jअगरfies + 2 + HZ * polling_limit_us / 1000000;

	/* loop until finished the transfer */
	जबतक (bs->rx_len) अणु

		/* करो common fअगरo handling */
		bcm2835aux_spi_transfer_helper(bs);

		/* there is still data pending to पढ़ो check the समयout */
		अगर (bs->rx_len && समय_after(jअगरfies, समयout)) अणु
			dev_dbg_ratelimited(&spi->dev,
					    "timeout period reached: jiffies: %lu remaining tx/rx: %d/%d - falling back to interrupt mode\n",
					    jअगरfies - समयout,
					    bs->tx_len, bs->rx_len);
			/* क्रमward to पूर्णांकerrupt handler */
			bs->count_transfer_irq_after_poll++;
			वापस __bcm2835aux_spi_transfer_one_irq(master,
							       spi, tfr);
		पूर्ण
	पूर्ण

	/* and वापस without रुकोing क्रम completion */
	वापस 0;
पूर्ण

अटल पूर्णांक bcm2835aux_spi_transfer_one(काष्ठा spi_master *master,
				       काष्ठा spi_device *spi,
				       काष्ठा spi_transfer *tfr)
अणु
	काष्ठा bcm2835aux_spi *bs = spi_master_get_devdata(master);
	अचिन्हित दीर्घ spi_hz, clk_hz, speed;
	अचिन्हित दीर्घ hz_per_byte, byte_limit;

	/* calculate the रेजिस्टरs to handle
	 *
	 * note that we use the variable data mode, which
	 * is not optimal क्रम दीर्घer transfers as we waste रेजिस्टरs
	 * resulting (potentially) in more पूर्णांकerrupts when transferring
	 * more than 12 bytes
	 */

	/* set घड़ी */
	spi_hz = tfr->speed_hz;
	clk_hz = clk_get_rate(bs->clk);

	अगर (spi_hz >= clk_hz / 2) अणु
		speed = 0;
	पूर्ण अन्यथा अगर (spi_hz) अणु
		speed = DIV_ROUND_UP(clk_hz, 2 * spi_hz) - 1;
		अगर (speed >  BCM2835_AUX_SPI_CNTL0_SPEED_MAX)
			speed = BCM2835_AUX_SPI_CNTL0_SPEED_MAX;
	पूर्ण अन्यथा अणु /* the slowest we can go */
		speed = BCM2835_AUX_SPI_CNTL0_SPEED_MAX;
	पूर्ण
	/* mask out old speed from previous spi_transfer */
	bs->cntl[0] &= ~(BCM2835_AUX_SPI_CNTL0_SPEED);
	/* set the new speed */
	bs->cntl[0] |= speed << BCM2835_AUX_SPI_CNTL0_SPEED_SHIFT;

	tfr->effective_speed_hz = clk_hz / (2 * (speed + 1));

	/* set transmit buffers and length */
	bs->tx_buf = tfr->tx_buf;
	bs->rx_buf = tfr->rx_buf;
	bs->tx_len = tfr->len;
	bs->rx_len = tfr->len;
	bs->pending = 0;

	/* Calculate the estimated समय in us the transfer runs.  Note that
	 * there are are 2 idle घड़ीs cycles after each chunk getting
	 * transferred - in our हाल the chunk size is 3 bytes, so we
	 * approximate this by 9 cycles/byte.  This is used to find the number
	 * of Hz per byte per polling limit.  E.g., we can transfer 1 byte in
	 * 30 तगs per 300,000 Hz of bus घड़ी.
	 */
	hz_per_byte = polling_limit_us ? (9 * 1000000) / polling_limit_us : 0;
	byte_limit = hz_per_byte ? tfr->effective_speed_hz / hz_per_byte : 1;

	/* run in polling mode क्रम लघु transfers */
	अगर (tfr->len < byte_limit)
		वापस bcm2835aux_spi_transfer_one_poll(master, spi, tfr);

	/* run in पूर्णांकerrupt mode क्रम all others */
	वापस bcm2835aux_spi_transfer_one_irq(master, spi, tfr);
पूर्ण

अटल पूर्णांक bcm2835aux_spi_prepare_message(काष्ठा spi_master *master,
					  काष्ठा spi_message *msg)
अणु
	काष्ठा spi_device *spi = msg->spi;
	काष्ठा bcm2835aux_spi *bs = spi_master_get_devdata(master);

	bs->cntl[0] = BCM2835_AUX_SPI_CNTL0_ENABLE |
		      BCM2835_AUX_SPI_CNTL0_VAR_WIDTH |
		      BCM2835_AUX_SPI_CNTL0_MSBF_OUT;
	bs->cntl[1] = BCM2835_AUX_SPI_CNTL1_MSBF_IN;

	/* handle all the modes */
	अगर (spi->mode & SPI_CPOL) अणु
		bs->cntl[0] |= BCM2835_AUX_SPI_CNTL0_CPOL;
		bs->cntl[0] |= BCM2835_AUX_SPI_CNTL0_OUT_RISING;
	पूर्ण अन्यथा अणु
		bs->cntl[0] |= BCM2835_AUX_SPI_CNTL0_IN_RISING;
	पूर्ण
	bcm2835aux_wr(bs, BCM2835_AUX_SPI_CNTL1, bs->cntl[1]);
	bcm2835aux_wr(bs, BCM2835_AUX_SPI_CNTL0, bs->cntl[0]);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm2835aux_spi_unprepare_message(काष्ठा spi_master *master,
					    काष्ठा spi_message *msg)
अणु
	काष्ठा bcm2835aux_spi *bs = spi_master_get_devdata(master);

	bcm2835aux_spi_reset_hw(bs);

	वापस 0;
पूर्ण

अटल व्योम bcm2835aux_spi_handle_err(काष्ठा spi_master *master,
				      काष्ठा spi_message *msg)
अणु
	काष्ठा bcm2835aux_spi *bs = spi_master_get_devdata(master);

	bcm2835aux_spi_reset_hw(bs);
पूर्ण

अटल पूर्णांक bcm2835aux_spi_setup(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret;

	/* sanity check क्रम native cs */
	अगर (spi->mode & SPI_NO_CS)
		वापस 0;
	अगर (gpio_is_valid(spi->cs_gpio)) अणु
		/* with gpio-cs set the GPIO to the correct level
		 * and as output (in हाल the dt has the gpio not configured
		 * as output but native cs)
		 */
		ret = gpio_direction_output(spi->cs_gpio,
					    (spi->mode & SPI_CS_HIGH) ? 0 : 1);
		अगर (ret)
			dev_err(&spi->dev,
				"could not set gpio %i as output: %i\n",
				spi->cs_gpio, ret);

		वापस ret;
	पूर्ण

	/* क्रम dt-backwards compatibility: only support native on CS0
	 * known things not supported with broken native CS:
	 * * multiple chip-selects: cs0-cs2 are all
	 *     simultaniously निश्चितed whenever there is a transfer
	 *     this even includes SPI_NO_CS
	 * * SPI_CS_HIGH: cs are always निश्चितed low
	 * * cs_change: cs is deनिश्चितed after each spi_transfer
	 * * cs_delay_usec: cs is always deनिश्चितed one SCK cycle
	 *     after the last transfer
	 * probably more...
	 */
	dev_warn(&spi->dev,
		 "Native CS is not supported - please configure cs-gpio in device-tree\n");

	अगर (spi->chip_select == 0)
		वापस 0;

	dev_warn(&spi->dev, "Native CS is not working for cs > 0\n");

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक bcm2835aux_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master;
	काष्ठा bcm2835aux_spi *bs;
	अचिन्हित दीर्घ clk_hz;
	पूर्णांक err;

	master = devm_spi_alloc_master(&pdev->dev, माप(*bs));
	अगर (!master)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, master);
	master->mode_bits = (SPI_CPOL | SPI_CS_HIGH | SPI_NO_CS);
	master->bits_per_word_mask = SPI_BPW_MASK(8);
	/* even though the driver never officially supported native CS
	 * allow a single native CS क्रम legacy DT support purposes when
	 * no cs-gpio is configured.
	 * Known limitations क्रम native cs are:
	 * * multiple chip-selects: cs0-cs2 are all simultaniously निश्चितed
	 *     whenever there is a transfer -  this even includes SPI_NO_CS
	 * * SPI_CS_HIGH: is ignores - cs are always निश्चितed low
	 * * cs_change: cs is deनिश्चितed after each spi_transfer
	 * * cs_delay_usec: cs is always deनिश्चितed one SCK cycle after
	 *     a spi_transfer
	 */
	master->num_chipselect = 1;
	master->setup = bcm2835aux_spi_setup;
	master->transfer_one = bcm2835aux_spi_transfer_one;
	master->handle_err = bcm2835aux_spi_handle_err;
	master->prepare_message = bcm2835aux_spi_prepare_message;
	master->unprepare_message = bcm2835aux_spi_unprepare_message;
	master->dev.of_node = pdev->dev.of_node;

	bs = spi_master_get_devdata(master);

	/* the मुख्य area */
	bs->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(bs->regs))
		वापस PTR_ERR(bs->regs);

	bs->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(bs->clk)) अणु
		err = PTR_ERR(bs->clk);
		dev_err(&pdev->dev, "could not get clk: %d\n", err);
		वापस err;
	पूर्ण

	bs->irq = platक्रमm_get_irq(pdev, 0);
	अगर (bs->irq <= 0)
		वापस bs->irq ? bs->irq : -ENODEV;

	/* this also enables the HW block */
	err = clk_prepare_enable(bs->clk);
	अगर (err) अणु
		dev_err(&pdev->dev, "could not prepare clock: %d\n", err);
		वापस err;
	पूर्ण

	/* just checking अगर the घड़ी वापसs a sane value */
	clk_hz = clk_get_rate(bs->clk);
	अगर (!clk_hz) अणु
		dev_err(&pdev->dev, "clock returns 0 Hz\n");
		err = -ENODEV;
		जाओ out_clk_disable;
	पूर्ण

	/* reset SPI-HW block */
	bcm2835aux_spi_reset_hw(bs);

	err = devm_request_irq(&pdev->dev, bs->irq,
			       bcm2835aux_spi_पूर्णांकerrupt,
			       IRQF_SHARED,
			       dev_name(&pdev->dev), master);
	अगर (err) अणु
		dev_err(&pdev->dev, "could not request IRQ: %d\n", err);
		जाओ out_clk_disable;
	पूर्ण

	err = spi_रेजिस्टर_master(master);
	अगर (err) अणु
		dev_err(&pdev->dev, "could not register SPI master: %d\n", err);
		जाओ out_clk_disable;
	पूर्ण

	bcm2835aux_debugfs_create(bs, dev_name(&pdev->dev));

	वापस 0;

out_clk_disable:
	clk_disable_unprepare(bs->clk);
	वापस err;
पूर्ण

अटल पूर्णांक bcm2835aux_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master = platक्रमm_get_drvdata(pdev);
	काष्ठा bcm2835aux_spi *bs = spi_master_get_devdata(master);

	bcm2835aux_debugfs_हटाओ(bs);

	spi_unरेजिस्टर_master(master);

	bcm2835aux_spi_reset_hw(bs);

	/* disable the HW block by releasing the घड़ी */
	clk_disable_unprepare(bs->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm2835aux_spi_match[] = अणु
	अणु .compatible = "brcm,bcm2835-aux-spi", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm2835aux_spi_match);

अटल काष्ठा platक्रमm_driver bcm2835aux_spi_driver = अणु
	.driver		= अणु
		.name		= "spi-bcm2835aux",
		.of_match_table	= bcm2835aux_spi_match,
	पूर्ण,
	.probe		= bcm2835aux_spi_probe,
	.हटाओ		= bcm2835aux_spi_हटाओ,
पूर्ण;
module_platक्रमm_driver(bcm2835aux_spi_driver);

MODULE_DESCRIPTION("SPI controller driver for Broadcom BCM2835 aux");
MODULE_AUTHOR("Martin Sperl <kernel@martin.sperl.org>");
MODULE_LICENSE("GPL");
