<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Broadcom BCM2835 SPI Controllers
 *
 * Copyright (C) 2012 Chris Boot
 * Copyright (C) 2013 Stephen Warren
 * Copyright (C) 2015 Martin Sperl
 *
 * This driver is inspired by:
 * spi-ath79.c, Copyright (C) 2009-2011 Gabor Juhos <juhosg@खोलोwrt.org>
 * spi-aपंचांगel.c, Copyright (C) 2006 Aपंचांगel Corporation
 */

#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/gpio/machine.h> /* FIXME: using chip पूर्णांकernals */
#समावेश <linux/gpio/driver.h> /* FIXME: using chip पूर्णांकernals */
#समावेश <linux/of_irq.h>
#समावेश <linux/spi/spi.h>

/* SPI रेजिस्टर offsets */
#घोषणा BCM2835_SPI_CS			0x00
#घोषणा BCM2835_SPI_FIFO		0x04
#घोषणा BCM2835_SPI_CLK			0x08
#घोषणा BCM2835_SPI_DLEN		0x0c
#घोषणा BCM2835_SPI_LTOH		0x10
#घोषणा BCM2835_SPI_DC			0x14

/* Bitfields in CS */
#घोषणा BCM2835_SPI_CS_LEN_LONG		0x02000000
#घोषणा BCM2835_SPI_CS_DMA_LEN		0x01000000
#घोषणा BCM2835_SPI_CS_CSPOL2		0x00800000
#घोषणा BCM2835_SPI_CS_CSPOL1		0x00400000
#घोषणा BCM2835_SPI_CS_CSPOL0		0x00200000
#घोषणा BCM2835_SPI_CS_RXF		0x00100000
#घोषणा BCM2835_SPI_CS_RXR		0x00080000
#घोषणा BCM2835_SPI_CS_TXD		0x00040000
#घोषणा BCM2835_SPI_CS_RXD		0x00020000
#घोषणा BCM2835_SPI_CS_DONE		0x00010000
#घोषणा BCM2835_SPI_CS_LEN		0x00002000
#घोषणा BCM2835_SPI_CS_REN		0x00001000
#घोषणा BCM2835_SPI_CS_ADCS		0x00000800
#घोषणा BCM2835_SPI_CS_INTR		0x00000400
#घोषणा BCM2835_SPI_CS_INTD		0x00000200
#घोषणा BCM2835_SPI_CS_DMAEN		0x00000100
#घोषणा BCM2835_SPI_CS_TA		0x00000080
#घोषणा BCM2835_SPI_CS_CSPOL		0x00000040
#घोषणा BCM2835_SPI_CS_CLEAR_RX		0x00000020
#घोषणा BCM2835_SPI_CS_CLEAR_TX		0x00000010
#घोषणा BCM2835_SPI_CS_CPOL		0x00000008
#घोषणा BCM2835_SPI_CS_CPHA		0x00000004
#घोषणा BCM2835_SPI_CS_CS_10		0x00000002
#घोषणा BCM2835_SPI_CS_CS_01		0x00000001

#घोषणा BCM2835_SPI_FIFO_SIZE		64
#घोषणा BCM2835_SPI_FIFO_SIZE_3_4	48
#घोषणा BCM2835_SPI_DMA_MIN_LENGTH	96
#घोषणा BCM2835_SPI_NUM_CS		24  /* उठाओ as necessary */
#घोषणा BCM2835_SPI_MODE_BITS	(SPI_CPOL | SPI_CPHA | SPI_CS_HIGH \
				| SPI_NO_CS | SPI_3WIRE)

#घोषणा DRV_NAME	"spi-bcm2835"

/* define polling limits */
अटल अचिन्हित पूर्णांक polling_limit_us = 30;
module_param(polling_limit_us, uपूर्णांक, 0664);
MODULE_PARM_DESC(polling_limit_us,
		 "time in us to run a transfer in polling mode\n");

/**
 * काष्ठा bcm2835_spi - BCM2835 SPI controller
 * @regs: base address of रेजिस्टर map
 * @clk: core घड़ी, भागided to calculate serial घड़ी
 * @irq: पूर्णांकerrupt, संकेतs TX FIFO empty or RX FIFO तठ full
 * @tfr: SPI transfer currently processed
 * @ctlr: SPI controller reverse lookup
 * @tx_buf: poपूर्णांकer whence next transmitted byte is पढ़ो
 * @rx_buf: poपूर्णांकer where next received byte is written
 * @tx_len: reमुख्यing bytes to transmit
 * @rx_len: reमुख्यing bytes to receive
 * @tx_prologue: bytes transmitted without DMA अगर first TX sglist entry's
 *	length is not a multiple of 4 (to overcome hardware limitation)
 * @rx_prologue: bytes received without DMA अगर first RX sglist entry's
 *	length is not a multiple of 4 (to overcome hardware limitation)
 * @tx_spillover: whether @tx_prologue spills over to second TX sglist entry
 * @prepare_cs: precalculated CS रेजिस्टर value क्रम ->prepare_message()
 *	(uses slave-specअगरic घड़ी polarity and phase settings)
 * @debugfs_dir: the debugfs directory - neede to हटाओ debugfs when
 *      unloading the module
 * @count_transfer_polling: count of how often polling mode is used
 * @count_transfer_irq: count of how often पूर्णांकerrupt mode is used
 * @count_transfer_irq_after_polling: count of how often we fall back to
 *      पूर्णांकerrupt mode after starting in polling mode.
 *      These are counted as well in @count_transfer_polling and
 *      @count_transfer_irq
 * @count_transfer_dma: count how often dma mode is used
 * @chip_select: SPI slave currently selected
 *	(used by bcm2835_spi_dma_tx_करोne() to ग_लिखो @clear_rx_cs)
 * @tx_dma_active: whether a TX DMA descriptor is in progress
 * @rx_dma_active: whether a RX DMA descriptor is in progress
 *	(used by bcm2835_spi_dma_tx_करोne() to handle a race)
 * @fill_tx_desc: pपुनः_स्मृतिated TX DMA descriptor used क्रम RX-only transfers
 *	(cyclically copies from zero page to TX FIFO)
 * @fill_tx_addr: bus address of zero page
 * @clear_rx_desc: pपुनः_स्मृतिated RX DMA descriptor used क्रम TX-only transfers
 *	(cyclically clears RX FIFO by writing @clear_rx_cs to CS रेजिस्टर)
 * @clear_rx_addr: bus address of @clear_rx_cs
 * @clear_rx_cs: precalculated CS रेजिस्टर value to clear RX FIFO
 *	(uses slave-specअगरic घड़ी polarity and phase settings)
 */
काष्ठा bcm2835_spi अणु
	व्योम __iomem *regs;
	काष्ठा clk *clk;
	पूर्णांक irq;
	काष्ठा spi_transfer *tfr;
	काष्ठा spi_controller *ctlr;
	स्थिर u8 *tx_buf;
	u8 *rx_buf;
	पूर्णांक tx_len;
	पूर्णांक rx_len;
	पूर्णांक tx_prologue;
	पूर्णांक rx_prologue;
	अचिन्हित पूर्णांक tx_spillover;
	u32 prepare_cs[BCM2835_SPI_NUM_CS];

	काष्ठा dentry *debugfs_dir;
	u64 count_transfer_polling;
	u64 count_transfer_irq;
	u64 count_transfer_irq_after_polling;
	u64 count_transfer_dma;

	u8 chip_select;
	अचिन्हित पूर्णांक tx_dma_active;
	अचिन्हित पूर्णांक rx_dma_active;
	काष्ठा dma_async_tx_descriptor *fill_tx_desc;
	dma_addr_t fill_tx_addr;
	काष्ठा dma_async_tx_descriptor *clear_rx_desc[BCM2835_SPI_NUM_CS];
	dma_addr_t clear_rx_addr;
	u32 clear_rx_cs[BCM2835_SPI_NUM_CS] ____cacheline_aligned;
पूर्ण;

#अगर defined(CONFIG_DEBUG_FS)
अटल व्योम bcm2835_debugfs_create(काष्ठा bcm2835_spi *bs,
				   स्थिर अक्षर *dname)
अणु
	अक्षर name[64];
	काष्ठा dentry *dir;

	/* get full name */
	snम_लिखो(name, माप(name), "spi-bcm2835-%s", dname);

	/* the base directory */
	dir = debugfs_create_dir(name, शून्य);
	bs->debugfs_dir = dir;

	/* the counters */
	debugfs_create_u64("count_transfer_polling", 0444, dir,
			   &bs->count_transfer_polling);
	debugfs_create_u64("count_transfer_irq", 0444, dir,
			   &bs->count_transfer_irq);
	debugfs_create_u64("count_transfer_irq_after_polling", 0444, dir,
			   &bs->count_transfer_irq_after_polling);
	debugfs_create_u64("count_transfer_dma", 0444, dir,
			   &bs->count_transfer_dma);
पूर्ण

अटल व्योम bcm2835_debugfs_हटाओ(काष्ठा bcm2835_spi *bs)
अणु
	debugfs_हटाओ_recursive(bs->debugfs_dir);
	bs->debugfs_dir = शून्य;
पूर्ण
#अन्यथा
अटल व्योम bcm2835_debugfs_create(काष्ठा bcm2835_spi *bs,
				   स्थिर अक्षर *dname)
अणु
पूर्ण

अटल व्योम bcm2835_debugfs_हटाओ(काष्ठा bcm2835_spi *bs)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

अटल अंतरभूत u32 bcm2835_rd(काष्ठा bcm2835_spi *bs, अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोl(bs->regs + reg);
पूर्ण

अटल अंतरभूत व्योम bcm2835_wr(काष्ठा bcm2835_spi *bs, अचिन्हित पूर्णांक reg, u32 val)
अणु
	ग_लिखोl(val, bs->regs + reg);
पूर्ण

अटल अंतरभूत व्योम bcm2835_rd_fअगरo(काष्ठा bcm2835_spi *bs)
अणु
	u8 byte;

	जबतक ((bs->rx_len) &&
	       (bcm2835_rd(bs, BCM2835_SPI_CS) & BCM2835_SPI_CS_RXD)) अणु
		byte = bcm2835_rd(bs, BCM2835_SPI_FIFO);
		अगर (bs->rx_buf)
			*bs->rx_buf++ = byte;
		bs->rx_len--;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम bcm2835_wr_fअगरo(काष्ठा bcm2835_spi *bs)
अणु
	u8 byte;

	जबतक ((bs->tx_len) &&
	       (bcm2835_rd(bs, BCM2835_SPI_CS) & BCM2835_SPI_CS_TXD)) अणु
		byte = bs->tx_buf ? *bs->tx_buf++ : 0;
		bcm2835_wr(bs, BCM2835_SPI_FIFO, byte);
		bs->tx_len--;
	पूर्ण
पूर्ण

/**
 * bcm2835_rd_fअगरo_count() - blindly पढ़ो exactly @count bytes from RX FIFO
 * @bs: BCM2835 SPI controller
 * @count: bytes to पढ़ो from RX FIFO
 *
 * The caller must ensure that @bs->rx_len is greater than or equal to @count,
 * that the RX FIFO contains at least @count bytes and that the DMA Enable flag
 * in the CS रेजिस्टर is set (such that a पढ़ो from the FIFO रेजिस्टर receives
 * 32-bit instead of just 8-bit).  Moreover @bs->rx_buf must not be %शून्य.
 */
अटल अंतरभूत व्योम bcm2835_rd_fअगरo_count(काष्ठा bcm2835_spi *bs, पूर्णांक count)
अणु
	u32 val;
	पूर्णांक len;

	bs->rx_len -= count;

	करो अणु
		val = bcm2835_rd(bs, BCM2835_SPI_FIFO);
		len = min(count, 4);
		स_नकल(bs->rx_buf, &val, len);
		bs->rx_buf += len;
		count -= 4;
	पूर्ण जबतक (count > 0);
पूर्ण

/**
 * bcm2835_wr_fअगरo_count() - blindly ग_लिखो exactly @count bytes to TX FIFO
 * @bs: BCM2835 SPI controller
 * @count: bytes to ग_लिखो to TX FIFO
 *
 * The caller must ensure that @bs->tx_len is greater than or equal to @count,
 * that the TX FIFO can accommodate @count bytes and that the DMA Enable flag
 * in the CS रेजिस्टर is set (such that a ग_लिखो to the FIFO रेजिस्टर transmits
 * 32-bit instead of just 8-bit).
 */
अटल अंतरभूत व्योम bcm2835_wr_fअगरo_count(काष्ठा bcm2835_spi *bs, पूर्णांक count)
अणु
	u32 val;
	पूर्णांक len;

	bs->tx_len -= count;

	करो अणु
		अगर (bs->tx_buf) अणु
			len = min(count, 4);
			स_नकल(&val, bs->tx_buf, len);
			bs->tx_buf += len;
		पूर्ण अन्यथा अणु
			val = 0;
		पूर्ण
		bcm2835_wr(bs, BCM2835_SPI_FIFO, val);
		count -= 4;
	पूर्ण जबतक (count > 0);
पूर्ण

/**
 * bcm2835_रुको_tx_fअगरo_empty() - busy-रुको क्रम TX FIFO to empty
 * @bs: BCM2835 SPI controller
 *
 * The caller must ensure that the RX FIFO can accommodate as many bytes
 * as have been written to the TX FIFO:  Transmission is halted once the
 * RX FIFO is full, causing this function to spin क्रमever.
 */
अटल अंतरभूत व्योम bcm2835_रुको_tx_fअगरo_empty(काष्ठा bcm2835_spi *bs)
अणु
	जबतक (!(bcm2835_rd(bs, BCM2835_SPI_CS) & BCM2835_SPI_CS_DONE))
		cpu_relax();
पूर्ण

/**
 * bcm2835_rd_fअगरo_blind() - blindly पढ़ो up to @count bytes from RX FIFO
 * @bs: BCM2835 SPI controller
 * @count: bytes available क्रम पढ़ोing in RX FIFO
 */
अटल अंतरभूत व्योम bcm2835_rd_fअगरo_blind(काष्ठा bcm2835_spi *bs, पूर्णांक count)
अणु
	u8 val;

	count = min(count, bs->rx_len);
	bs->rx_len -= count;

	करो अणु
		val = bcm2835_rd(bs, BCM2835_SPI_FIFO);
		अगर (bs->rx_buf)
			*bs->rx_buf++ = val;
	पूर्ण जबतक (--count);
पूर्ण

/**
 * bcm2835_wr_fअगरo_blind() - blindly ग_लिखो up to @count bytes to TX FIFO
 * @bs: BCM2835 SPI controller
 * @count: bytes available क्रम writing in TX FIFO
 */
अटल अंतरभूत व्योम bcm2835_wr_fअगरo_blind(काष्ठा bcm2835_spi *bs, पूर्णांक count)
अणु
	u8 val;

	count = min(count, bs->tx_len);
	bs->tx_len -= count;

	करो अणु
		val = bs->tx_buf ? *bs->tx_buf++ : 0;
		bcm2835_wr(bs, BCM2835_SPI_FIFO, val);
	पूर्ण जबतक (--count);
पूर्ण

अटल व्योम bcm2835_spi_reset_hw(काष्ठा bcm2835_spi *bs)
अणु
	u32 cs = bcm2835_rd(bs, BCM2835_SPI_CS);

	/* Disable SPI पूर्णांकerrupts and transfer */
	cs &= ~(BCM2835_SPI_CS_INTR |
		BCM2835_SPI_CS_INTD |
		BCM2835_SPI_CS_DMAEN |
		BCM2835_SPI_CS_TA);
	/*
	 * Transmission someबार अवरोधs unless the DONE bit is written at the
	 * end of every transfer.  The spec says it's a RO bit.  Either the
	 * spec is wrong and the bit is actually of type RW1C, or it's a
	 * hardware erratum.
	 */
	cs |= BCM2835_SPI_CS_DONE;
	/* and reset RX/TX FIFOS */
	cs |= BCM2835_SPI_CS_CLEAR_RX | BCM2835_SPI_CS_CLEAR_TX;

	/* and reset the SPI_HW */
	bcm2835_wr(bs, BCM2835_SPI_CS, cs);
	/* as well as DLEN */
	bcm2835_wr(bs, BCM2835_SPI_DLEN, 0);
पूर्ण

अटल irqवापस_t bcm2835_spi_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा bcm2835_spi *bs = dev_id;
	u32 cs = bcm2835_rd(bs, BCM2835_SPI_CS);

	/*
	 * An पूर्णांकerrupt is संकेतed either अगर DONE is set (TX FIFO empty)
	 * or अगर RXR is set (RX FIFO >= तठ full).
	 */
	अगर (cs & BCM2835_SPI_CS_RXF)
		bcm2835_rd_fअगरo_blind(bs, BCM2835_SPI_FIFO_SIZE);
	अन्यथा अगर (cs & BCM2835_SPI_CS_RXR)
		bcm2835_rd_fअगरo_blind(bs, BCM2835_SPI_FIFO_SIZE_3_4);

	अगर (bs->tx_len && cs & BCM2835_SPI_CS_DONE)
		bcm2835_wr_fअगरo_blind(bs, BCM2835_SPI_FIFO_SIZE);

	/* Read as many bytes as possible from FIFO */
	bcm2835_rd_fअगरo(bs);
	/* Write as many bytes as possible to FIFO */
	bcm2835_wr_fअगरo(bs);

	अगर (!bs->rx_len) अणु
		/* Transfer complete - reset SPI HW */
		bcm2835_spi_reset_hw(bs);
		/* wake up the framework */
		spi_finalize_current_transfer(bs->ctlr);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक bcm2835_spi_transfer_one_irq(काष्ठा spi_controller *ctlr,
					काष्ठा spi_device *spi,
					काष्ठा spi_transfer *tfr,
					u32 cs, bool fअगरo_empty)
अणु
	काष्ठा bcm2835_spi *bs = spi_controller_get_devdata(ctlr);

	/* update usage statistics */
	bs->count_transfer_irq++;

	/*
	 * Enable HW block, but with पूर्णांकerrupts still disabled.
	 * Otherwise the empty TX FIFO would immediately trigger an पूर्णांकerrupt.
	 */
	bcm2835_wr(bs, BCM2835_SPI_CS, cs | BCM2835_SPI_CS_TA);

	/* fill TX FIFO as much as possible */
	अगर (fअगरo_empty)
		bcm2835_wr_fअगरo_blind(bs, BCM2835_SPI_FIFO_SIZE);
	bcm2835_wr_fअगरo(bs);

	/* enable पूर्णांकerrupts */
	cs |= BCM2835_SPI_CS_INTR | BCM2835_SPI_CS_INTD | BCM2835_SPI_CS_TA;
	bcm2835_wr(bs, BCM2835_SPI_CS, cs);

	/* संकेत that we need to रुको क्रम completion */
	वापस 1;
पूर्ण

/**
 * bcm2835_spi_transfer_prologue() - transfer first few bytes without DMA
 * @ctlr: SPI master controller
 * @tfr: SPI transfer
 * @bs: BCM2835 SPI controller
 * @cs: CS रेजिस्टर
 *
 * A limitation in DMA mode is that the FIFO must be accessed in 4 byte chunks.
 * Only the final ग_लिखो access is permitted to transmit less than 4 bytes, the
 * SPI controller deduces its पूर्णांकended size from the DLEN रेजिस्टर.
 *
 * If a TX or RX sglist contains multiple entries, one per page, and the first
 * entry starts in the middle of a page, that first entry's length may not be
 * a multiple of 4.  Subsequent entries are fine because they span an entire
 * page, hence करो have a length that's a multiple of 4.
 *
 * This cannot happen with kदो_स्मृति'ed buffers (which is what most clients use)
 * because they are contiguous in physical memory and thereक्रमe not split on
 * page boundaries by spi_map_buf().  But it *can* happen with vदो_स्मृति'ed
 * buffers.
 *
 * The DMA engine is incapable of combining sglist entries पूर्णांकo a continuous
 * stream of 4 byte chunks, it treats every entry separately:  A TX entry is
 * rounded up a to a multiple of 4 bytes by transmitting surplus bytes, an RX
 * entry is rounded up by throwing away received bytes.
 *
 * Overcome this limitation by transferring the first few bytes without DMA:
 * E.g. अगर the first TX sglist entry's length is 23 and the first RX's is 42,
 * ग_लिखो 3 bytes to the TX FIFO but पढ़ो only 2 bytes from the RX FIFO.
 * The residue of 1 byte in the RX FIFO is picked up by DMA.  Together with
 * the rest of the first RX sglist entry it makes up a multiple of 4 bytes.
 *
 * Should the RX prologue be larger, say, 3 vis-थ -vis a TX prologue of 1,
 * ग_लिखो 1 + 4 = 5 bytes to the TX FIFO and पढ़ो 3 bytes from the RX FIFO.
 * Caution, the additional 4 bytes spill over to the second TX sglist entry
 * अगर the length of the first is *exactly* 1.
 *
 * At most 6 bytes are written and at most 3 bytes पढ़ो.  Do we know the
 * transfer has this many bytes?  Yes, see BCM2835_SPI_DMA_MIN_LENGTH.
 *
 * The FIFO is normally accessed with 8-bit width by the CPU and 32-bit width
 * by the DMA engine.  Toggling the DMA Enable flag in the CS रेजिस्टर चयनes
 * the width but also garbles the FIFO's contents.  The prologue must thereक्रमe
 * be transmitted in 32-bit width to ensure that the following DMA transfer can
 * pick up the residue in the RX FIFO in ungarbled क्रमm.
 */
अटल व्योम bcm2835_spi_transfer_prologue(काष्ठा spi_controller *ctlr,
					  काष्ठा spi_transfer *tfr,
					  काष्ठा bcm2835_spi *bs,
					  u32 cs)
अणु
	पूर्णांक tx_reमुख्यing;

	bs->tfr		 = tfr;
	bs->tx_prologue  = 0;
	bs->rx_prologue  = 0;
	bs->tx_spillover = false;

	अगर (bs->tx_buf && !sg_is_last(&tfr->tx_sg.sgl[0]))
		bs->tx_prologue = sg_dma_len(&tfr->tx_sg.sgl[0]) & 3;

	अगर (bs->rx_buf && !sg_is_last(&tfr->rx_sg.sgl[0])) अणु
		bs->rx_prologue = sg_dma_len(&tfr->rx_sg.sgl[0]) & 3;

		अगर (bs->rx_prologue > bs->tx_prologue) अणु
			अगर (!bs->tx_buf || sg_is_last(&tfr->tx_sg.sgl[0])) अणु
				bs->tx_prologue  = bs->rx_prologue;
			पूर्ण अन्यथा अणु
				bs->tx_prologue += 4;
				bs->tx_spillover =
					!(sg_dma_len(&tfr->tx_sg.sgl[0]) & ~3);
			पूर्ण
		पूर्ण
	पूर्ण

	/* rx_prologue > 0 implies tx_prologue > 0, so check only the latter */
	अगर (!bs->tx_prologue)
		वापस;

	/* Write and पढ़ो RX prologue.  Adjust first entry in RX sglist. */
	अगर (bs->rx_prologue) अणु
		bcm2835_wr(bs, BCM2835_SPI_DLEN, bs->rx_prologue);
		bcm2835_wr(bs, BCM2835_SPI_CS, cs | BCM2835_SPI_CS_TA
						  | BCM2835_SPI_CS_DMAEN);
		bcm2835_wr_fअगरo_count(bs, bs->rx_prologue);
		bcm2835_रुको_tx_fअगरo_empty(bs);
		bcm2835_rd_fअगरo_count(bs, bs->rx_prologue);
		bcm2835_wr(bs, BCM2835_SPI_CS, cs | BCM2835_SPI_CS_CLEAR_RX
						  | BCM2835_SPI_CS_CLEAR_TX
						  | BCM2835_SPI_CS_DONE);

		dma_sync_single_क्रम_device(ctlr->dma_rx->device->dev,
					   sg_dma_address(&tfr->rx_sg.sgl[0]),
					   bs->rx_prologue, DMA_FROM_DEVICE);

		sg_dma_address(&tfr->rx_sg.sgl[0]) += bs->rx_prologue;
		sg_dma_len(&tfr->rx_sg.sgl[0])     -= bs->rx_prologue;
	पूर्ण

	अगर (!bs->tx_buf)
		वापस;

	/*
	 * Write reमुख्यing TX prologue.  Adjust first entry in TX sglist.
	 * Also adjust second entry अगर prologue spills over to it.
	 */
	tx_reमुख्यing = bs->tx_prologue - bs->rx_prologue;
	अगर (tx_reमुख्यing) अणु
		bcm2835_wr(bs, BCM2835_SPI_DLEN, tx_reमुख्यing);
		bcm2835_wr(bs, BCM2835_SPI_CS, cs | BCM2835_SPI_CS_TA
						  | BCM2835_SPI_CS_DMAEN);
		bcm2835_wr_fअगरo_count(bs, tx_reमुख्यing);
		bcm2835_रुको_tx_fअगरo_empty(bs);
		bcm2835_wr(bs, BCM2835_SPI_CS, cs | BCM2835_SPI_CS_CLEAR_TX
						  | BCM2835_SPI_CS_DONE);
	पूर्ण

	अगर (likely(!bs->tx_spillover)) अणु
		sg_dma_address(&tfr->tx_sg.sgl[0]) += bs->tx_prologue;
		sg_dma_len(&tfr->tx_sg.sgl[0])     -= bs->tx_prologue;
	पूर्ण अन्यथा अणु
		sg_dma_len(&tfr->tx_sg.sgl[0])      = 0;
		sg_dma_address(&tfr->tx_sg.sgl[1]) += 4;
		sg_dma_len(&tfr->tx_sg.sgl[1])     -= 4;
	पूर्ण
पूर्ण

/**
 * bcm2835_spi_unकरो_prologue() - reस्थिरruct original sglist state
 * @bs: BCM2835 SPI controller
 *
 * Unकरो changes which were made to an SPI transfer's sglist when transmitting
 * the prologue.  This is necessary to ensure the same memory ranges are
 * unmapped that were originally mapped.
 */
अटल व्योम bcm2835_spi_unकरो_prologue(काष्ठा bcm2835_spi *bs)
अणु
	काष्ठा spi_transfer *tfr = bs->tfr;

	अगर (!bs->tx_prologue)
		वापस;

	अगर (bs->rx_prologue) अणु
		sg_dma_address(&tfr->rx_sg.sgl[0]) -= bs->rx_prologue;
		sg_dma_len(&tfr->rx_sg.sgl[0])     += bs->rx_prologue;
	पूर्ण

	अगर (!bs->tx_buf)
		जाओ out;

	अगर (likely(!bs->tx_spillover)) अणु
		sg_dma_address(&tfr->tx_sg.sgl[0]) -= bs->tx_prologue;
		sg_dma_len(&tfr->tx_sg.sgl[0])     += bs->tx_prologue;
	पूर्ण अन्यथा अणु
		sg_dma_len(&tfr->tx_sg.sgl[0])      = bs->tx_prologue - 4;
		sg_dma_address(&tfr->tx_sg.sgl[1]) -= 4;
		sg_dma_len(&tfr->tx_sg.sgl[1])     += 4;
	पूर्ण
out:
	bs->tx_prologue = 0;
पूर्ण

/**
 * bcm2835_spi_dma_rx_करोne() - callback क्रम DMA RX channel
 * @data: SPI master controller
 *
 * Used क्रम bidirectional and RX-only transfers.
 */
अटल व्योम bcm2835_spi_dma_rx_करोne(व्योम *data)
अणु
	काष्ठा spi_controller *ctlr = data;
	काष्ठा bcm2835_spi *bs = spi_controller_get_devdata(ctlr);

	/* terminate tx-dma as we करो not have an irq क्रम it
	 * because when the rx dma will terminate and this callback
	 * is called the tx-dma must have finished - can't get to this
	 * situation otherwise...
	 */
	dmaengine_terminate_async(ctlr->dma_tx);
	bs->tx_dma_active = false;
	bs->rx_dma_active = false;
	bcm2835_spi_unकरो_prologue(bs);

	/* reset fअगरo and HW */
	bcm2835_spi_reset_hw(bs);

	/* and mark as completed */;
	spi_finalize_current_transfer(ctlr);
पूर्ण

/**
 * bcm2835_spi_dma_tx_करोne() - callback क्रम DMA TX channel
 * @data: SPI master controller
 *
 * Used क्रम TX-only transfers.
 */
अटल व्योम bcm2835_spi_dma_tx_करोne(व्योम *data)
अणु
	काष्ठा spi_controller *ctlr = data;
	काष्ठा bcm2835_spi *bs = spi_controller_get_devdata(ctlr);

	/* busy-रुको क्रम TX FIFO to empty */
	जबतक (!(bcm2835_rd(bs, BCM2835_SPI_CS) & BCM2835_SPI_CS_DONE))
		bcm2835_wr(bs, BCM2835_SPI_CS,
			   bs->clear_rx_cs[bs->chip_select]);

	bs->tx_dma_active = false;
	smp_wmb();

	/*
	 * In हाल of a very लघु transfer, RX DMA may not have been
	 * issued yet.  The onus is then on bcm2835_spi_transfer_one_dma()
	 * to terminate it immediately after issuing.
	 */
	अगर (cmpxchg(&bs->rx_dma_active, true, false))
		dmaengine_terminate_async(ctlr->dma_rx);

	bcm2835_spi_unकरो_prologue(bs);
	bcm2835_spi_reset_hw(bs);
	spi_finalize_current_transfer(ctlr);
पूर्ण

/**
 * bcm2835_spi_prepare_sg() - prepare and submit DMA descriptor क्रम sglist
 * @ctlr: SPI master controller
 * @spi: SPI slave
 * @tfr: SPI transfer
 * @bs: BCM2835 SPI controller
 * @is_tx: whether to submit DMA descriptor क्रम TX or RX sglist
 *
 * Prepare and submit a DMA descriptor क्रम the TX or RX sglist of @tfr.
 * Return 0 on success or a negative error number.
 */
अटल पूर्णांक bcm2835_spi_prepare_sg(काष्ठा spi_controller *ctlr,
				  काष्ठा spi_device *spi,
				  काष्ठा spi_transfer *tfr,
				  काष्ठा bcm2835_spi *bs,
				  bool is_tx)
अणु
	काष्ठा dma_chan *chan;
	काष्ठा scatterlist *sgl;
	अचिन्हित पूर्णांक nents;
	क्रमागत dma_transfer_direction dir;
	अचिन्हित दीर्घ flags;

	काष्ठा dma_async_tx_descriptor *desc;
	dma_cookie_t cookie;

	अगर (is_tx) अणु
		dir   = DMA_MEM_TO_DEV;
		chan  = ctlr->dma_tx;
		nents = tfr->tx_sg.nents;
		sgl   = tfr->tx_sg.sgl;
		flags = tfr->rx_buf ? 0 : DMA_PREP_INTERRUPT;
	पूर्ण अन्यथा अणु
		dir   = DMA_DEV_TO_MEM;
		chan  = ctlr->dma_rx;
		nents = tfr->rx_sg.nents;
		sgl   = tfr->rx_sg.sgl;
		flags = DMA_PREP_INTERRUPT;
	पूर्ण
	/* prepare the channel */
	desc = dmaengine_prep_slave_sg(chan, sgl, nents, dir, flags);
	अगर (!desc)
		वापस -EINVAL;

	/*
	 * Completion is संकेतed by the RX channel क्रम bidirectional and
	 * RX-only transfers; अन्यथा by the TX channel क्रम TX-only transfers.
	 */
	अगर (!is_tx) अणु
		desc->callback = bcm2835_spi_dma_rx_करोne;
		desc->callback_param = ctlr;
	पूर्ण अन्यथा अगर (!tfr->rx_buf) अणु
		desc->callback = bcm2835_spi_dma_tx_करोne;
		desc->callback_param = ctlr;
		bs->chip_select = spi->chip_select;
	पूर्ण

	/* submit it to DMA-engine */
	cookie = dmaengine_submit(desc);

	वापस dma_submit_error(cookie);
पूर्ण

/**
 * bcm2835_spi_transfer_one_dma() - perक्रमm SPI transfer using DMA engine
 * @ctlr: SPI master controller
 * @spi: SPI slave
 * @tfr: SPI transfer
 * @cs: CS रेजिस्टर
 *
 * For *bidirectional* transfers (both tx_buf and rx_buf are non-%शून्य), set up
 * the TX and RX DMA channel to copy between memory and FIFO रेजिस्टर.
 *
 * For *TX-only* transfers (rx_buf is %शून्य), copying the RX FIFO's contents to
 * memory is poपूर्णांकless.  However not पढ़ोing the RX FIFO isn't an option either
 * because transmission is halted once it's full.  As a workaround, cyclically
 * clear the RX FIFO by setting the CLEAR_RX bit in the CS रेजिस्टर.
 *
 * The CS रेजिस्टर value is precalculated in bcm2835_spi_setup().  Normally
 * this is called only once, on slave registration.  A DMA descriptor to ग_लिखो
 * this value is pपुनः_स्मृतिated in bcm2835_dma_init().  All that's left to करो
 * when perक्रमming a TX-only transfer is to submit this descriptor to the RX
 * DMA channel.  Latency is thereby minimized.  The descriptor करोes not
 * generate any पूर्णांकerrupts जबतक running.  It must be terminated once the
 * TX DMA channel is करोne.
 *
 * Clearing the RX FIFO is paced by the DREQ संकेत.  The संकेत is निश्चितed
 * when the RX FIFO becomes half full, i.e. 32 bytes.  (Tuneable with the DC
 * रेजिस्टर.)  Reading 32 bytes from the RX FIFO would normally require 8 bus
 * accesses, whereas clearing it requires only 1 bus access.  So an 8-fold
 * reduction in bus traffic and thus energy consumption is achieved.
 *
 * For *RX-only* transfers (tx_buf is %शून्य), fill the TX FIFO by cyclically
 * copying from the zero page.  The DMA descriptor to करो this is pपुनः_स्मृतिated
 * in bcm2835_dma_init().  It must be terminated once the RX DMA channel is
 * करोne and can then be reused.
 *
 * The BCM2835 DMA driver स्वतःdetects when a transaction copies from the zero
 * page and utilizes the DMA controller's ability to synthesize zeroes instead
 * of copying them from memory.  This reduces traffic on the memory bus.  The
 * feature is not available on so-called "lite" channels, but normally TX DMA
 * is backed by a full-featured channel.
 *
 * Zero-filling the TX FIFO is paced by the DREQ संकेत.  Unक्रमtunately the
 * BCM2835 SPI controller जारीs to निश्चित DREQ even after the DLEN रेजिस्टर
 * has been counted करोwn to zero (hardware erratum).  Thus, when the transfer
 * has finished, the DMA engine zero-fills the TX FIFO until it is half full.
 * (Tuneable with the DC रेजिस्टर.)  So up to 9 gratuitous bus accesses are
 * perक्रमmed at the end of an RX-only transfer.
 */
अटल पूर्णांक bcm2835_spi_transfer_one_dma(काष्ठा spi_controller *ctlr,
					काष्ठा spi_device *spi,
					काष्ठा spi_transfer *tfr,
					u32 cs)
अणु
	काष्ठा bcm2835_spi *bs = spi_controller_get_devdata(ctlr);
	dma_cookie_t cookie;
	पूर्णांक ret;

	/* update usage statistics */
	bs->count_transfer_dma++;

	/*
	 * Transfer first few bytes without DMA अगर length of first TX or RX
	 * sglist entry is not a multiple of 4 bytes (hardware limitation).
	 */
	bcm2835_spi_transfer_prologue(ctlr, tfr, bs, cs);

	/* setup tx-DMA */
	अगर (bs->tx_buf) अणु
		ret = bcm2835_spi_prepare_sg(ctlr, spi, tfr, bs, true);
	पूर्ण अन्यथा अणु
		cookie = dmaengine_submit(bs->fill_tx_desc);
		ret = dma_submit_error(cookie);
	पूर्ण
	अगर (ret)
		जाओ err_reset_hw;

	/* set the DMA length */
	bcm2835_wr(bs, BCM2835_SPI_DLEN, bs->tx_len);

	/* start the HW */
	bcm2835_wr(bs, BCM2835_SPI_CS,
		   cs | BCM2835_SPI_CS_TA | BCM2835_SPI_CS_DMAEN);

	bs->tx_dma_active = true;
	smp_wmb();

	/* start TX early */
	dma_async_issue_pending(ctlr->dma_tx);

	/* setup rx-DMA late - to run transfers जबतक
	 * mapping of the rx buffers still takes place
	 * this saves 10us or more.
	 */
	अगर (bs->rx_buf) अणु
		ret = bcm2835_spi_prepare_sg(ctlr, spi, tfr, bs, false);
	पूर्ण अन्यथा अणु
		cookie = dmaengine_submit(bs->clear_rx_desc[spi->chip_select]);
		ret = dma_submit_error(cookie);
	पूर्ण
	अगर (ret) अणु
		/* need to reset on errors */
		dmaengine_terminate_sync(ctlr->dma_tx);
		bs->tx_dma_active = false;
		जाओ err_reset_hw;
	पूर्ण

	/* start rx dma late */
	dma_async_issue_pending(ctlr->dma_rx);
	bs->rx_dma_active = true;
	smp_mb();

	/*
	 * In हाल of a very लघु TX-only transfer, bcm2835_spi_dma_tx_करोne()
	 * may run beक्रमe RX DMA is issued.  Terminate RX DMA अगर so.
	 */
	अगर (!bs->rx_buf && !bs->tx_dma_active &&
	    cmpxchg(&bs->rx_dma_active, true, false)) अणु
		dmaengine_terminate_async(ctlr->dma_rx);
		bcm2835_spi_reset_hw(bs);
	पूर्ण

	/* रुको क्रम wakeup in framework */
	वापस 1;

err_reset_hw:
	bcm2835_spi_reset_hw(bs);
	bcm2835_spi_unकरो_prologue(bs);
	वापस ret;
पूर्ण

अटल bool bcm2835_spi_can_dma(काष्ठा spi_controller *ctlr,
				काष्ठा spi_device *spi,
				काष्ठा spi_transfer *tfr)
अणु
	/* we start DMA efक्रमts only on bigger transfers */
	अगर (tfr->len < BCM2835_SPI_DMA_MIN_LENGTH)
		वापस false;

	/* वापस OK */
	वापस true;
पूर्ण

अटल व्योम bcm2835_dma_release(काष्ठा spi_controller *ctlr,
				काष्ठा bcm2835_spi *bs)
अणु
	पूर्णांक i;

	अगर (ctlr->dma_tx) अणु
		dmaengine_terminate_sync(ctlr->dma_tx);

		अगर (bs->fill_tx_desc)
			dmaengine_desc_मुक्त(bs->fill_tx_desc);

		अगर (bs->fill_tx_addr)
			dma_unmap_page_attrs(ctlr->dma_tx->device->dev,
					     bs->fill_tx_addr, माप(u32),
					     DMA_TO_DEVICE,
					     DMA_ATTR_SKIP_CPU_SYNC);

		dma_release_channel(ctlr->dma_tx);
		ctlr->dma_tx = शून्य;
	पूर्ण

	अगर (ctlr->dma_rx) अणु
		dmaengine_terminate_sync(ctlr->dma_rx);

		क्रम (i = 0; i < BCM2835_SPI_NUM_CS; i++)
			अगर (bs->clear_rx_desc[i])
				dmaengine_desc_मुक्त(bs->clear_rx_desc[i]);

		अगर (bs->clear_rx_addr)
			dma_unmap_single(ctlr->dma_rx->device->dev,
					 bs->clear_rx_addr,
					 माप(bs->clear_rx_cs),
					 DMA_TO_DEVICE);

		dma_release_channel(ctlr->dma_rx);
		ctlr->dma_rx = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक bcm2835_dma_init(काष्ठा spi_controller *ctlr, काष्ठा device *dev,
			    काष्ठा bcm2835_spi *bs)
अणु
	काष्ठा dma_slave_config slave_config;
	स्थिर __be32 *addr;
	dma_addr_t dma_reg_base;
	पूर्णांक ret, i;

	/* base address in dma-space */
	addr = of_get_address(ctlr->dev.of_node, 0, शून्य, शून्य);
	अगर (!addr) अणु
		dev_err(dev, "could not get DMA-register address - not using dma mode\n");
		/* Fall back to पूर्णांकerrupt mode */
		वापस 0;
	पूर्ण
	dma_reg_base = be32_to_cpup(addr);

	/* get tx/rx dma */
	ctlr->dma_tx = dma_request_chan(dev, "tx");
	अगर (IS_ERR(ctlr->dma_tx)) अणु
		dev_err(dev, "no tx-dma configuration found - not using dma mode\n");
		ret = PTR_ERR(ctlr->dma_tx);
		ctlr->dma_tx = शून्य;
		जाओ err;
	पूर्ण
	ctlr->dma_rx = dma_request_chan(dev, "rx");
	अगर (IS_ERR(ctlr->dma_rx)) अणु
		dev_err(dev, "no rx-dma configuration found - not using dma mode\n");
		ret = PTR_ERR(ctlr->dma_rx);
		ctlr->dma_rx = शून्य;
		जाओ err_release;
	पूर्ण

	/*
	 * The TX DMA channel either copies a transfer's TX buffer to the FIFO
	 * or, in हाल of an RX-only transfer, cyclically copies from the zero
	 * page to the FIFO using a pपुनः_स्मृतिated, reusable descriptor.
	 */
	slave_config.dst_addr = (u32)(dma_reg_base + BCM2835_SPI_FIFO);
	slave_config.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;

	ret = dmaengine_slave_config(ctlr->dma_tx, &slave_config);
	अगर (ret)
		जाओ err_config;

	bs->fill_tx_addr = dma_map_page_attrs(ctlr->dma_tx->device->dev,
					      ZERO_PAGE(0), 0, माप(u32),
					      DMA_TO_DEVICE,
					      DMA_ATTR_SKIP_CPU_SYNC);
	अगर (dma_mapping_error(ctlr->dma_tx->device->dev, bs->fill_tx_addr)) अणु
		dev_err(dev, "cannot map zero page - not using DMA mode\n");
		bs->fill_tx_addr = 0;
		ret = -ENOMEM;
		जाओ err_release;
	पूर्ण

	bs->fill_tx_desc = dmaengine_prep_dma_cyclic(ctlr->dma_tx,
						     bs->fill_tx_addr,
						     माप(u32), 0,
						     DMA_MEM_TO_DEV, 0);
	अगर (!bs->fill_tx_desc) अणु
		dev_err(dev, "cannot prepare fill_tx_desc - not using DMA mode\n");
		ret = -ENOMEM;
		जाओ err_release;
	पूर्ण

	ret = dmaengine_desc_set_reuse(bs->fill_tx_desc);
	अगर (ret) अणु
		dev_err(dev, "cannot reuse fill_tx_desc - not using DMA mode\n");
		जाओ err_release;
	पूर्ण

	/*
	 * The RX DMA channel is used bidirectionally:  It either पढ़ोs the
	 * RX FIFO or, in हाल of a TX-only transfer, cyclically ग_लिखोs a
	 * precalculated value to the CS रेजिस्टर to clear the RX FIFO.
	 */
	slave_config.src_addr = (u32)(dma_reg_base + BCM2835_SPI_FIFO);
	slave_config.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	slave_config.dst_addr = (u32)(dma_reg_base + BCM2835_SPI_CS);
	slave_config.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;

	ret = dmaengine_slave_config(ctlr->dma_rx, &slave_config);
	अगर (ret)
		जाओ err_config;

	bs->clear_rx_addr = dma_map_single(ctlr->dma_rx->device->dev,
					   bs->clear_rx_cs,
					   माप(bs->clear_rx_cs),
					   DMA_TO_DEVICE);
	अगर (dma_mapping_error(ctlr->dma_rx->device->dev, bs->clear_rx_addr)) अणु
		dev_err(dev, "cannot map clear_rx_cs - not using DMA mode\n");
		bs->clear_rx_addr = 0;
		ret = -ENOMEM;
		जाओ err_release;
	पूर्ण

	क्रम (i = 0; i < BCM2835_SPI_NUM_CS; i++) अणु
		bs->clear_rx_desc[i] = dmaengine_prep_dma_cyclic(ctlr->dma_rx,
					   bs->clear_rx_addr + i * माप(u32),
					   माप(u32), 0,
					   DMA_MEM_TO_DEV, 0);
		अगर (!bs->clear_rx_desc[i]) अणु
			dev_err(dev, "cannot prepare clear_rx_desc - not using DMA mode\n");
			ret = -ENOMEM;
			जाओ err_release;
		पूर्ण

		ret = dmaengine_desc_set_reuse(bs->clear_rx_desc[i]);
		अगर (ret) अणु
			dev_err(dev, "cannot reuse clear_rx_desc - not using DMA mode\n");
			जाओ err_release;
		पूर्ण
	पूर्ण

	/* all went well, so set can_dma */
	ctlr->can_dma = bcm2835_spi_can_dma;

	वापस 0;

err_config:
	dev_err(dev, "issue configuring dma: %d - not using DMA mode\n",
		ret);
err_release:
	bcm2835_dma_release(ctlr, bs);
err:
	/*
	 * Only report error क्रम deferred probing, otherwise fall back to
	 * पूर्णांकerrupt mode
	 */
	अगर (ret != -EPROBE_DEFER)
		ret = 0;

	वापस ret;
पूर्ण

अटल पूर्णांक bcm2835_spi_transfer_one_poll(काष्ठा spi_controller *ctlr,
					 काष्ठा spi_device *spi,
					 काष्ठा spi_transfer *tfr,
					 u32 cs)
अणु
	काष्ठा bcm2835_spi *bs = spi_controller_get_devdata(ctlr);
	अचिन्हित दीर्घ समयout;

	/* update usage statistics */
	bs->count_transfer_polling++;

	/* enable HW block without पूर्णांकerrupts */
	bcm2835_wr(bs, BCM2835_SPI_CS, cs | BCM2835_SPI_CS_TA);

	/* fill in the fअगरo beक्रमe समयout calculations
	 * अगर we are पूर्णांकerrupted here, then the data is
	 * getting transferred by the HW जबतक we are पूर्णांकerrupted
	 */
	bcm2835_wr_fअगरo_blind(bs, BCM2835_SPI_FIFO_SIZE);

	/* set the समयout to at least 2 jअगरfies */
	समयout = jअगरfies + 2 + HZ * polling_limit_us / 1000000;

	/* loop until finished the transfer */
	जबतक (bs->rx_len) अणु
		/* fill in tx fअगरo with reमुख्यing data */
		bcm2835_wr_fअगरo(bs);

		/* पढ़ो from fअगरo as much as possible */
		bcm2835_rd_fअगरo(bs);

		/* अगर there is still data pending to पढ़ो
		 * then check the समयout
		 */
		अगर (bs->rx_len && समय_after(jअगरfies, समयout)) अणु
			dev_dbg_ratelimited(&spi->dev,
					    "timeout period reached: jiffies: %lu remaining tx/rx: %d/%d - falling back to interrupt mode\n",
					    jअगरfies - समयout,
					    bs->tx_len, bs->rx_len);
			/* fall back to पूर्णांकerrupt mode */

			/* update usage statistics */
			bs->count_transfer_irq_after_polling++;

			वापस bcm2835_spi_transfer_one_irq(ctlr, spi,
							    tfr, cs, false);
		पूर्ण
	पूर्ण

	/* Transfer complete - reset SPI HW */
	bcm2835_spi_reset_hw(bs);
	/* and वापस without रुकोing क्रम completion */
	वापस 0;
पूर्ण

अटल पूर्णांक bcm2835_spi_transfer_one(काष्ठा spi_controller *ctlr,
				    काष्ठा spi_device *spi,
				    काष्ठा spi_transfer *tfr)
अणु
	काष्ठा bcm2835_spi *bs = spi_controller_get_devdata(ctlr);
	अचिन्हित दीर्घ spi_hz, clk_hz, cभाग;
	अचिन्हित दीर्घ hz_per_byte, byte_limit;
	u32 cs = bs->prepare_cs[spi->chip_select];

	/* set घड़ी */
	spi_hz = tfr->speed_hz;
	clk_hz = clk_get_rate(bs->clk);

	अगर (spi_hz >= clk_hz / 2) अणु
		cभाग = 2; /* clk_hz/2 is the fastest we can go */
	पूर्ण अन्यथा अगर (spi_hz) अणु
		/* CDIV must be a multiple of two */
		cभाग = DIV_ROUND_UP(clk_hz, spi_hz);
		cभाग += (cभाग % 2);

		अगर (cभाग >= 65536)
			cभाग = 0; /* 0 is the slowest we can go */
	पूर्ण अन्यथा अणु
		cभाग = 0; /* 0 is the slowest we can go */
	पूर्ण
	tfr->effective_speed_hz = cभाग ? (clk_hz / cभाग) : (clk_hz / 65536);
	bcm2835_wr(bs, BCM2835_SPI_CLK, cभाग);

	/* handle all the 3-wire mode */
	अगर (spi->mode & SPI_3WIRE && tfr->rx_buf)
		cs |= BCM2835_SPI_CS_REN;

	/* set transmit buffers and length */
	bs->tx_buf = tfr->tx_buf;
	bs->rx_buf = tfr->rx_buf;
	bs->tx_len = tfr->len;
	bs->rx_len = tfr->len;

	/* Calculate the estimated समय in us the transfer runs.  Note that
	 * there is 1 idle घड़ीs cycles after each byte getting transferred
	 * so we have 9 cycles/byte.  This is used to find the number of Hz
	 * per byte per polling limit.  E.g., we can transfer 1 byte in 30 us
	 * per 300,000 Hz of bus घड़ी.
	 */
	hz_per_byte = polling_limit_us ? (9 * 1000000) / polling_limit_us : 0;
	byte_limit = hz_per_byte ? tfr->effective_speed_hz / hz_per_byte : 1;

	/* run in polling mode क्रम लघु transfers */
	अगर (tfr->len < byte_limit)
		वापस bcm2835_spi_transfer_one_poll(ctlr, spi, tfr, cs);

	/* run in dma mode अगर conditions are right
	 * Note that unlike poll or पूर्णांकerrupt mode DMA mode करोes not have
	 * this 1 idle घड़ी cycle pattern but runs the spi घड़ी without gaps
	 */
	अगर (ctlr->can_dma && bcm2835_spi_can_dma(ctlr, spi, tfr))
		वापस bcm2835_spi_transfer_one_dma(ctlr, spi, tfr, cs);

	/* run in पूर्णांकerrupt-mode */
	वापस bcm2835_spi_transfer_one_irq(ctlr, spi, tfr, cs, true);
पूर्ण

अटल पूर्णांक bcm2835_spi_prepare_message(काष्ठा spi_controller *ctlr,
				       काष्ठा spi_message *msg)
अणु
	काष्ठा spi_device *spi = msg->spi;
	काष्ठा bcm2835_spi *bs = spi_controller_get_devdata(ctlr);
	पूर्णांक ret;

	अगर (ctlr->can_dma) अणु
		/*
		 * DMA transfers are limited to 16 bit (0 to 65535 bytes) by
		 * the SPI HW due to DLEN. Split up transfers (32-bit FIFO
		 * aligned) अगर the limit is exceeded.
		 */
		ret = spi_split_transfers_maxsize(ctlr, msg, 65532,
						  GFP_KERNEL | GFP_DMA);
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * Set up घड़ी polarity beक्रमe spi_transfer_one_message() निश्चितs
	 * chip select to aव्योम a gratuitous घड़ी संकेत edge.
	 */
	bcm2835_wr(bs, BCM2835_SPI_CS, bs->prepare_cs[spi->chip_select]);

	वापस 0;
पूर्ण

अटल व्योम bcm2835_spi_handle_err(काष्ठा spi_controller *ctlr,
				   काष्ठा spi_message *msg)
अणु
	काष्ठा bcm2835_spi *bs = spi_controller_get_devdata(ctlr);

	/* अगर an error occurred and we have an active dma, then terminate */
	dmaengine_terminate_sync(ctlr->dma_tx);
	bs->tx_dma_active = false;
	dmaengine_terminate_sync(ctlr->dma_rx);
	bs->rx_dma_active = false;
	bcm2835_spi_unकरो_prologue(bs);

	/* and reset */
	bcm2835_spi_reset_hw(bs);
पूर्ण

अटल पूर्णांक chip_match_name(काष्ठा gpio_chip *chip, व्योम *data)
अणु
	वापस !म_भेद(chip->label, data);
पूर्ण

अटल पूर्णांक bcm2835_spi_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा spi_controller *ctlr = spi->controller;
	काष्ठा bcm2835_spi *bs = spi_controller_get_devdata(ctlr);
	काष्ठा gpio_chip *chip;
	u32 cs;

	अगर (spi->chip_select >= BCM2835_SPI_NUM_CS) अणु
		dev_err(&spi->dev, "only %d chip-selects supported\n",
			BCM2835_SPI_NUM_CS - 1);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Precalculate SPI slave's CS रेजिस्टर value क्रम ->prepare_message():
	 * The driver always uses software-controlled GPIO chip select, hence
	 * set the hardware-controlled native chip select to an invalid value
	 * to prevent it from पूर्णांकerfering.
	 */
	cs = BCM2835_SPI_CS_CS_10 | BCM2835_SPI_CS_CS_01;
	अगर (spi->mode & SPI_CPOL)
		cs |= BCM2835_SPI_CS_CPOL;
	अगर (spi->mode & SPI_CPHA)
		cs |= BCM2835_SPI_CS_CPHA;
	bs->prepare_cs[spi->chip_select] = cs;

	/*
	 * Precalculate SPI slave's CS रेजिस्टर value to clear RX FIFO
	 * in हाल of a TX-only DMA transfer.
	 */
	अगर (ctlr->dma_rx) अणु
		bs->clear_rx_cs[spi->chip_select] = cs |
						    BCM2835_SPI_CS_TA |
						    BCM2835_SPI_CS_DMAEN |
						    BCM2835_SPI_CS_CLEAR_RX;
		dma_sync_single_क्रम_device(ctlr->dma_rx->device->dev,
					   bs->clear_rx_addr,
					   माप(bs->clear_rx_cs),
					   DMA_TO_DEVICE);
	पूर्ण

	/*
	 * sanity checking the native-chipselects
	 */
	अगर (spi->mode & SPI_NO_CS)
		वापस 0;
	/*
	 * The SPI core has successfully requested the CS GPIO line from the
	 * device tree, so we are करोne.
	 */
	अगर (spi->cs_gpiod)
		वापस 0;
	अगर (spi->chip_select > 1) अणु
		/* error in the हाल of native CS requested with CS > 1
		 * officially there is a CS2, but it is not करोcumented
		 * which GPIO is connected with that...
		 */
		dev_err(&spi->dev,
			"setup: only two native chip-selects are supported\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Translate native CS to GPIO
	 *
	 * FIXME: poking around in the gpiolib पूर्णांकernals like this is
	 * not very good practice. Find a way to locate the real problem
	 * and fix it. Why is the GPIO descriptor in spi->cs_gpiod
	 * someबार not asचिन्हित correctly? Erroneous device trees?
	 */

	/* get the gpio chip क्रम the base */
	chip = gpiochip_find("pinctrl-bcm2835", chip_match_name);
	अगर (!chip)
		वापस 0;

	spi->cs_gpiod = gpiochip_request_own_desc(chip, 8 - spi->chip_select,
						  DRV_NAME,
						  GPIO_LOOKUP_FLAGS_DEFAULT,
						  GPIOD_OUT_LOW);
	अगर (IS_ERR(spi->cs_gpiod))
		वापस PTR_ERR(spi->cs_gpiod);

	/* and set up the "mode" and level */
	dev_info(&spi->dev, "setting up native-CS%i to use GPIO\n",
		 spi->chip_select);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm2835_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_controller *ctlr;
	काष्ठा bcm2835_spi *bs;
	पूर्णांक err;

	ctlr = devm_spi_alloc_master(&pdev->dev, ALIGN(माप(*bs),
						  dma_get_cache_alignment()));
	अगर (!ctlr)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, ctlr);

	ctlr->use_gpio_descriptors = true;
	ctlr->mode_bits = BCM2835_SPI_MODE_BITS;
	ctlr->bits_per_word_mask = SPI_BPW_MASK(8);
	ctlr->num_chipselect = 3;
	ctlr->setup = bcm2835_spi_setup;
	ctlr->transfer_one = bcm2835_spi_transfer_one;
	ctlr->handle_err = bcm2835_spi_handle_err;
	ctlr->prepare_message = bcm2835_spi_prepare_message;
	ctlr->dev.of_node = pdev->dev.of_node;

	bs = spi_controller_get_devdata(ctlr);
	bs->ctlr = ctlr;

	bs->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(bs->regs))
		वापस PTR_ERR(bs->regs);

	bs->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(bs->clk))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(bs->clk),
				     "could not get clk\n");

	ctlr->max_speed_hz = clk_get_rate(bs->clk) / 2;

	bs->irq = platक्रमm_get_irq(pdev, 0);
	अगर (bs->irq <= 0)
		वापस bs->irq ? bs->irq : -ENODEV;

	clk_prepare_enable(bs->clk);

	err = bcm2835_dma_init(ctlr, &pdev->dev, bs);
	अगर (err)
		जाओ out_clk_disable;

	/* initialise the hardware with the शेष polarities */
	bcm2835_wr(bs, BCM2835_SPI_CS,
		   BCM2835_SPI_CS_CLEAR_RX | BCM2835_SPI_CS_CLEAR_TX);

	err = devm_request_irq(&pdev->dev, bs->irq, bcm2835_spi_पूर्णांकerrupt, 0,
			       dev_name(&pdev->dev), bs);
	अगर (err) अणु
		dev_err(&pdev->dev, "could not request IRQ: %d\n", err);
		जाओ out_dma_release;
	पूर्ण

	err = spi_रेजिस्टर_controller(ctlr);
	अगर (err) अणु
		dev_err(&pdev->dev, "could not register SPI controller: %d\n",
			err);
		जाओ out_dma_release;
	पूर्ण

	bcm2835_debugfs_create(bs, dev_name(&pdev->dev));

	वापस 0;

out_dma_release:
	bcm2835_dma_release(ctlr, bs);
out_clk_disable:
	clk_disable_unprepare(bs->clk);
	वापस err;
पूर्ण

अटल पूर्णांक bcm2835_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_controller *ctlr = platक्रमm_get_drvdata(pdev);
	काष्ठा bcm2835_spi *bs = spi_controller_get_devdata(ctlr);

	bcm2835_debugfs_हटाओ(bs);

	spi_unरेजिस्टर_controller(ctlr);

	bcm2835_dma_release(ctlr, bs);

	/* Clear FIFOs, and disable the HW block */
	bcm2835_wr(bs, BCM2835_SPI_CS,
		   BCM2835_SPI_CS_CLEAR_RX | BCM2835_SPI_CS_CLEAR_TX);

	clk_disable_unprepare(bs->clk);

	वापस 0;
पूर्ण

अटल व्योम bcm2835_spi_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	ret = bcm2835_spi_हटाओ(pdev);
	अगर (ret)
		dev_err(&pdev->dev, "failed to shutdown\n");
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm2835_spi_match[] = अणु
	अणु .compatible = "brcm,bcm2835-spi", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm2835_spi_match);

अटल काष्ठा platक्रमm_driver bcm2835_spi_driver = अणु
	.driver		= अणु
		.name		= DRV_NAME,
		.of_match_table	= bcm2835_spi_match,
	पूर्ण,
	.probe		= bcm2835_spi_probe,
	.हटाओ		= bcm2835_spi_हटाओ,
	.shutकरोwn	= bcm2835_spi_shutकरोwn,
पूर्ण;
module_platक्रमm_driver(bcm2835_spi_driver);

MODULE_DESCRIPTION("SPI controller driver for Broadcom BCM2835");
MODULE_AUTHOR("Chris Boot <bootc@bootc.net>");
MODULE_LICENSE("GPL");
