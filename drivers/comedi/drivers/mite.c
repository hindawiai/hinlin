<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi/drivers/mite.c
 * Hardware driver क्रम NI Mite PCI पूर्णांकerface chip
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1997-2002 David A. Schleef <ds@schleef.org>
 */

/*
 * The PCI-MIO E series driver was originally written by
 * Tomasz Motylewski <...>, and ported to comedi by ds.
 *
 * References क्रम specअगरications:
 *
 *    321747b.pdf  Register Level Programmer Manual (obsolete)
 *    321747c.pdf  Register Level Programmer Manual (new)
 *    DAQ-STC reference manual
 *
 * Other possibly relevant info:
 *
 *    320517c.pdf  User manual (obsolete)
 *    320517f.pdf  User manual (new)
 *    320889a.pdf  delete
 *    320906c.pdf  maximum संकेत ratings
 *    321066a.pdf  about 16x
 *    321791a.pdf  discontinuation of at-mio-16e-10 rev. c
 *    321808a.pdf  about at-mio-16e-10 rev P
 *    321837a.pdf  discontinuation of at-mio-16de-10 rev d
 *    321838a.pdf  about at-mio-16de-10 rev N
 *
 * ISSUES:
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/log2.h>

#समावेश "../comedi_pci.h"

#समावेश "mite.h"

/*
 * Mite रेजिस्टरs
 */
#घोषणा MITE_UNKNOWN_DMA_BURST_REG	0x28
#घोषणा UNKNOWN_DMA_BURST_ENABLE_BITS	0x600

#घोषणा MITE_PCI_CONFIG_OFFSET	0x300
#घोषणा MITE_CSIGR		0x460			/* chip signature */
#घोषणा CSIGR_TO_IOWINS(x)	(((x) >> 29) & 0x7)
#घोषणा CSIGR_TO_WINS(x)	(((x) >> 24) & 0x1f)
#घोषणा CSIGR_TO_WPDEP(x)	(((x) >> 20) & 0x7)
#घोषणा CSIGR_TO_DMAC(x)	(((x) >> 16) & 0xf)
#घोषणा CSIGR_TO_IMODE(x)	(((x) >> 12) & 0x3)	/* pci=0x3 */
#घोषणा CSIGR_TO_MMODE(x)	(((x) >> 8) & 0x3)	/* minimite=1 */
#घोषणा CSIGR_TO_TYPE(x)	(((x) >> 4) & 0xf)	/* mite=0, minimite=1 */
#घोषणा CSIGR_TO_VER(x)		(((x) >> 0) & 0xf)

#घोषणा MITE_CHAN(x)		(0x500 + 0x100 * (x))
#घोषणा MITE_CHOR(x)		(0x00 + MITE_CHAN(x))	/* channel operation */
#घोषणा CHOR_DMARESET		BIT(31)
#घोषणा CHOR_SET_SEND_TC	BIT(11)
#घोषणा CHOR_CLR_SEND_TC	BIT(10)
#घोषणा CHOR_SET_LPAUSE		BIT(9)
#घोषणा CHOR_CLR_LPAUSE		BIT(8)
#घोषणा CHOR_CLRDONE		BIT(7)
#घोषणा CHOR_CLRRB		BIT(6)
#घोषणा CHOR_CLRLC		BIT(5)
#घोषणा CHOR_FRESET		BIT(4)
#घोषणा CHOR_ABORT		BIT(3)	/* stop without emptying fअगरo */
#घोषणा CHOR_STOP		BIT(2)	/* stop after emptying fअगरo */
#घोषणा CHOR_CONT		BIT(1)
#घोषणा CHOR_START		BIT(0)
#घोषणा MITE_CHCR(x)		(0x04 + MITE_CHAN(x))	/* channel control */
#घोषणा CHCR_SET_DMA_IE		BIT(31)
#घोषणा CHCR_CLR_DMA_IE		BIT(30)
#घोषणा CHCR_SET_LINKP_IE	BIT(29)
#घोषणा CHCR_CLR_LINKP_IE	BIT(28)
#घोषणा CHCR_SET_SAR_IE		BIT(27)
#घोषणा CHCR_CLR_SAR_IE		BIT(26)
#घोषणा CHCR_SET_DONE_IE	BIT(25)
#घोषणा CHCR_CLR_DONE_IE	BIT(24)
#घोषणा CHCR_SET_MRDY_IE	BIT(23)
#घोषणा CHCR_CLR_MRDY_IE	BIT(22)
#घोषणा CHCR_SET_DRDY_IE	BIT(21)
#घोषणा CHCR_CLR_DRDY_IE	BIT(20)
#घोषणा CHCR_SET_LC_IE		BIT(19)
#घोषणा CHCR_CLR_LC_IE		BIT(18)
#घोषणा CHCR_SET_CONT_RB_IE	BIT(17)
#घोषणा CHCR_CLR_CONT_RB_IE	BIT(16)
#घोषणा CHCR_FIFO(x)		(((x) & 0x1) << 15)
#घोषणा CHCR_FIFODIS		CHCR_FIFO(1)
#घोषणा CHCR_FIFO_ON		CHCR_FIFO(0)
#घोषणा CHCR_BURST(x)		(((x) & 0x1) << 14)
#घोषणा CHCR_BURSTEN		CHCR_BURST(1)
#घोषणा CHCR_NO_BURSTEN		CHCR_BURST(0)
#घोषणा CHCR_BYTE_SWAP_DEVICE	BIT(6)
#घोषणा CHCR_BYTE_SWAP_MEMORY	BIT(4)
#घोषणा CHCR_सूची(x)		(((x) & 0x1) << 3)
#घोषणा CHCR_DEV_TO_MEM		CHCR_सूची(1)
#घोषणा CHCR_MEM_TO_DEV		CHCR_सूची(0)
#घोषणा CHCR_MODE(x)		(((x) & 0x7) << 0)
#घोषणा CHCR_NORMAL		CHCR_MODE(0)
#घोषणा CHCR_CONTINUE		CHCR_MODE(1)
#घोषणा CHCR_RINGBUFF		CHCR_MODE(2)
#घोषणा CHCR_LINKSHORT		CHCR_MODE(4)
#घोषणा CHCR_LINKLONG		CHCR_MODE(5)
#घोषणा MITE_TCR(x)		(0x08 + MITE_CHAN(x))	/* transfer count */
#घोषणा MITE_MCR(x)		(0x0c + MITE_CHAN(x))	/* memory config */
#घोषणा MITE_MAR(x)		(0x10 + MITE_CHAN(x))	/* memory address */
#घोषणा MITE_DCR(x)		(0x14 + MITE_CHAN(x))	/* device config */
#घोषणा DCR_NORMAL		BIT(29)
#घोषणा MITE_DAR(x)		(0x18 + MITE_CHAN(x))	/* device address */
#घोषणा MITE_LKCR(x)		(0x1c + MITE_CHAN(x))	/* link config */
#घोषणा MITE_LKAR(x)		(0x20 + MITE_CHAN(x))	/* link address */
#घोषणा MITE_LLKAR(x)		(0x24 + MITE_CHAN(x))	/* see tnt5002 manual */
#घोषणा MITE_BAR(x)		(0x28 + MITE_CHAN(x))	/* base address */
#घोषणा MITE_BCR(x)		(0x2c + MITE_CHAN(x))	/* base count */
#घोषणा MITE_SAR(x)		(0x30 + MITE_CHAN(x))	/* ? address */
#घोषणा MITE_WSCR(x)		(0x34 + MITE_CHAN(x))	/* ? */
#घोषणा MITE_WSER(x)		(0x38 + MITE_CHAN(x))	/* ? */
#घोषणा MITE_CHSR(x)		(0x3c + MITE_CHAN(x))	/* channel status */
#घोषणा CHSR_INT		BIT(31)
#घोषणा CHSR_LPAUSES		BIT(29)
#घोषणा CHSR_SARS		BIT(27)
#घोषणा CHSR_DONE		BIT(25)
#घोषणा CHSR_MRDY		BIT(23)
#घोषणा CHSR_DRDY		BIT(21)
#घोषणा CHSR_LINKC		BIT(19)
#घोषणा CHSR_CONTS_RB		BIT(17)
#घोषणा CHSR_ERROR		BIT(15)
#घोषणा CHSR_SABORT		BIT(14)
#घोषणा CHSR_HABORT		BIT(13)
#घोषणा CHSR_STOPS		BIT(12)
#घोषणा CHSR_OPERR(x)		(((x) & 0x3) << 10)
#घोषणा CHSR_OPERR_MASK		CHSR_OPERR(3)
#घोषणा CHSR_OPERR_NOERROR	CHSR_OPERR(0)
#घोषणा CHSR_OPERR_FIFOERROR	CHSR_OPERR(1)
#घोषणा CHSR_OPERR_LINKERROR	CHSR_OPERR(1)	/* ??? */
#घोषणा CHSR_XFERR		BIT(9)
#घोषणा CHSR_END		BIT(8)
#घोषणा CHSR_DRQ1		BIT(7)
#घोषणा CHSR_DRQ0		BIT(6)
#घोषणा CHSR_LERR(x)		(((x) & 0x3) << 4)
#घोषणा CHSR_LERR_MASK		CHSR_LERR(3)
#घोषणा CHSR_LBERR		CHSR_LERR(1)
#घोषणा CHSR_LRERR		CHSR_LERR(2)
#घोषणा CHSR_LOERR		CHSR_LERR(3)
#घोषणा CHSR_MERR(x)		(((x) & 0x3) << 2)
#घोषणा CHSR_MERR_MASK		CHSR_MERR(3)
#घोषणा CHSR_MBERR		CHSR_MERR(1)
#घोषणा CHSR_MRERR		CHSR_MERR(2)
#घोषणा CHSR_MOERR		CHSR_MERR(3)
#घोषणा CHSR_DERR(x)		(((x) & 0x3) << 0)
#घोषणा CHSR_DERR_MASK		CHSR_DERR(3)
#घोषणा CHSR_DBERR		CHSR_DERR(1)
#घोषणा CHSR_DRERR		CHSR_DERR(2)
#घोषणा CHSR_DOERR		CHSR_DERR(3)
#घोषणा MITE_FCR(x)		(0x40 + MITE_CHAN(x))	/* fअगरo count */

/* common bits क्रम the memory/device/link config रेजिस्टरs */
#घोषणा CR_RL(x)		(((x) & 0x7) << 21)
#घोषणा CR_REQS(x)		(((x) & 0x7) << 16)
#घोषणा CR_REQS_MASK		CR_REQS(7)
#घोषणा CR_ASEQ(x)		(((x) & 0x3) << 10)
#घोषणा CR_ASEQDONT		CR_ASEQ(0)
#घोषणा CR_ASEQUP		CR_ASEQ(1)
#घोषणा CR_ASEQDOWN		CR_ASEQ(2)
#घोषणा CR_ASEQ_MASK		CR_ASEQ(3)
#घोषणा CR_PSIZE(x)		(((x) & 0x3) << 8)
#घोषणा CR_PSIZE8		CR_PSIZE(1)
#घोषणा CR_PSIZE16		CR_PSIZE(2)
#घोषणा CR_PSIZE32		CR_PSIZE(3)
#घोषणा CR_PORT(x)		(((x) & 0x3) << 6)
#घोषणा CR_PORTCPU		CR_PORT(0)
#घोषणा CR_PORTIO		CR_PORT(1)
#घोषणा CR_PORTVXI		CR_PORT(2)
#घोषणा CR_PORTMXI		CR_PORT(3)
#घोषणा CR_AMDEVICE		BIT(0)

अटल अचिन्हित पूर्णांक MITE_IODWBSR_1_WSIZE_bits(अचिन्हित पूर्णांक size)
अणु
	वापस (ilog2(size) - 1) & 0x1f;
पूर्ण

अटल अचिन्हित पूर्णांक mite_retry_limit(अचिन्हित पूर्णांक retry_limit)
अणु
	अचिन्हित पूर्णांक value = 0;

	अगर (retry_limit)
		value = 1 + ilog2(retry_limit);
	अगर (value > 0x7)
		value = 0x7;
	वापस CR_RL(value);
पूर्ण

अटल अचिन्हित पूर्णांक mite_drq_reqs(अचिन्हित पूर्णांक drq_line)
अणु
	/* This also works on m-series when using channels (drq_line) 4 or 5. */
	वापस CR_REQS((drq_line & 0x3) | 0x4);
पूर्ण

अटल अचिन्हित पूर्णांक mite_fअगरo_size(काष्ठा mite *mite, अचिन्हित पूर्णांक channel)
अणु
	अचिन्हित पूर्णांक fcr_bits = पढ़ोl(mite->mmio + MITE_FCR(channel));
	अचिन्हित पूर्णांक empty_count = (fcr_bits >> 16) & 0xff;
	अचिन्हित पूर्णांक full_count = fcr_bits & 0xff;

	वापस empty_count + full_count;
पूर्ण

अटल u32 mite_device_bytes_transferred(काष्ठा mite_channel *mite_chan)
अणु
	काष्ठा mite *mite = mite_chan->mite;

	वापस पढ़ोl(mite->mmio + MITE_DAR(mite_chan->channel));
पूर्ण

/**
 * mite_bytes_in_transit() - Returns the number of unपढ़ो bytes in the fअगरo.
 * @mite_chan: MITE dma channel.
 */
u32 mite_bytes_in_transit(काष्ठा mite_channel *mite_chan)
अणु
	काष्ठा mite *mite = mite_chan->mite;

	वापस पढ़ोl(mite->mmio + MITE_FCR(mite_chan->channel)) & 0xff;
पूर्ण
EXPORT_SYMBOL_GPL(mite_bytes_in_transit);

/* वापसs lower bound क्रम number of bytes transferred from device to memory */
अटल u32 mite_bytes_written_to_memory_lb(काष्ठा mite_channel *mite_chan)
अणु
	u32 device_byte_count;

	device_byte_count = mite_device_bytes_transferred(mite_chan);
	वापस device_byte_count - mite_bytes_in_transit(mite_chan);
पूर्ण

/* वापसs upper bound क्रम number of bytes transferred from device to memory */
अटल u32 mite_bytes_written_to_memory_ub(काष्ठा mite_channel *mite_chan)
अणु
	u32 in_transit_count;

	in_transit_count = mite_bytes_in_transit(mite_chan);
	वापस mite_device_bytes_transferred(mite_chan) - in_transit_count;
पूर्ण

/* वापसs lower bound क्रम number of bytes पढ़ो from memory to device */
अटल u32 mite_bytes_पढ़ो_from_memory_lb(काष्ठा mite_channel *mite_chan)
अणु
	u32 device_byte_count;

	device_byte_count = mite_device_bytes_transferred(mite_chan);
	वापस device_byte_count + mite_bytes_in_transit(mite_chan);
पूर्ण

/* वापसs upper bound क्रम number of bytes पढ़ो from memory to device */
अटल u32 mite_bytes_पढ़ो_from_memory_ub(काष्ठा mite_channel *mite_chan)
अणु
	u32 in_transit_count;

	in_transit_count = mite_bytes_in_transit(mite_chan);
	वापस mite_device_bytes_transferred(mite_chan) + in_transit_count;
पूर्ण

अटल व्योम mite_sync_input_dma(काष्ठा mite_channel *mite_chan,
				काष्ठा comedi_subdevice *s)
अणु
	काष्ठा comedi_async *async = s->async;
	पूर्णांक count;
	अचिन्हित पूर्णांक nbytes, old_alloc_count;

	old_alloc_count = async->buf_ग_लिखो_alloc_count;
	/* ग_लिखो alloc as much as we can */
	comedi_buf_ग_लिखो_alloc(s, async->pपुनः_स्मृति_bufsz);

	nbytes = mite_bytes_written_to_memory_lb(mite_chan);
	अगर ((पूर्णांक)(mite_bytes_written_to_memory_ub(mite_chan) -
		  old_alloc_count) > 0) अणु
		dev_warn(s->device->class_dev,
			 "mite: DMA overwrite of free area\n");
		async->events |= COMEDI_CB_OVERFLOW;
		वापस;
	पूर्ण

	count = nbytes - async->buf_ग_लिखो_count;
	/*
	 * it's possible count will be negative due to conservative value
	 * वापसed by mite_bytes_written_to_memory_lb
	 */
	अगर (count > 0) अणु
		comedi_buf_ग_लिखो_मुक्त(s, count);
		comedi_inc_scan_progress(s, count);
		async->events |= COMEDI_CB_BLOCK;
	पूर्ण
पूर्ण

अटल व्योम mite_sync_output_dma(काष्ठा mite_channel *mite_chan,
				 काष्ठा comedi_subdevice *s)
अणु
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	u32 stop_count = cmd->stop_arg * comedi_bytes_per_scan(s);
	अचिन्हित पूर्णांक old_alloc_count = async->buf_पढ़ो_alloc_count;
	u32 nbytes_ub, nbytes_lb;
	पूर्णांक count;
	bool finite_regen = (cmd->stop_src == TRIG_NONE && stop_count != 0);

	/* पढ़ो alloc as much as we can */
	comedi_buf_पढ़ो_alloc(s, async->pपुनः_स्मृति_bufsz);
	nbytes_lb = mite_bytes_पढ़ो_from_memory_lb(mite_chan);
	अगर (cmd->stop_src == TRIG_COUNT && (पूर्णांक)(nbytes_lb - stop_count) > 0)
		nbytes_lb = stop_count;
	nbytes_ub = mite_bytes_पढ़ो_from_memory_ub(mite_chan);
	अगर (cmd->stop_src == TRIG_COUNT && (पूर्णांक)(nbytes_ub - stop_count) > 0)
		nbytes_ub = stop_count;

	अगर ((!finite_regen || stop_count > old_alloc_count) &&
	    ((पूर्णांक)(nbytes_ub - old_alloc_count) > 0)) अणु
		dev_warn(s->device->class_dev, "mite: DMA underrun\n");
		async->events |= COMEDI_CB_OVERFLOW;
		वापस;
	पूर्ण

	अगर (finite_regen) अणु
		/*
		 * This is a special हाल where we continuously output a finite
		 * buffer.  In this हाल, we करो not मुक्त any of the memory,
		 * hence we expect that old_alloc_count will reach a maximum of
		 * stop_count bytes.
		 */
		वापस;
	पूर्ण

	count = nbytes_lb - async->buf_पढ़ो_count;
	अगर (count > 0) अणु
		comedi_buf_पढ़ो_मुक्त(s, count);
		async->events |= COMEDI_CB_BLOCK;
	पूर्ण
पूर्ण

/**
 * mite_sync_dma() - Sync the MITE dma with the COMEDI async buffer.
 * @mite_chan: MITE dma channel.
 * @s: COMEDI subdevice.
 */
व्योम mite_sync_dma(काष्ठा mite_channel *mite_chan, काष्ठा comedi_subdevice *s)
अणु
	अगर (mite_chan->dir == COMEDI_INPUT)
		mite_sync_input_dma(mite_chan, s);
	अन्यथा
		mite_sync_output_dma(mite_chan, s);
पूर्ण
EXPORT_SYMBOL_GPL(mite_sync_dma);

अटल अचिन्हित पूर्णांक mite_get_status(काष्ठा mite_channel *mite_chan)
अणु
	काष्ठा mite *mite = mite_chan->mite;
	अचिन्हित पूर्णांक status;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mite->lock, flags);
	status = पढ़ोl(mite->mmio + MITE_CHSR(mite_chan->channel));
	अगर (status & CHSR_DONE) अणु
		mite_chan->करोne = 1;
		ग_लिखोl(CHOR_CLRDONE,
		       mite->mmio + MITE_CHOR(mite_chan->channel));
	पूर्ण
	spin_unlock_irqrestore(&mite->lock, flags);
	वापस status;
पूर्ण

/**
 * mite_ack_linkc() - Check and ack the LINKC पूर्णांकerrupt,
 * @mite_chan: MITE dma channel.
 * @s: COMEDI subdevice.
 * @sync: flag to क्रमce a mite_sync_dma().
 *
 * This will also ack the DONE पूर्णांकerrupt अगर active.
 */
व्योम mite_ack_linkc(काष्ठा mite_channel *mite_chan,
		    काष्ठा comedi_subdevice *s,
		    bool sync)
अणु
	काष्ठा mite *mite = mite_chan->mite;
	अचिन्हित पूर्णांक status;

	status = mite_get_status(mite_chan);
	अगर (status & CHSR_LINKC) अणु
		ग_लिखोl(CHOR_CLRLC, mite->mmio + MITE_CHOR(mite_chan->channel));
		sync = true;
	पूर्ण
	अगर (sync)
		mite_sync_dma(mite_chan, s);

	अगर (status & CHSR_XFERR) अणु
		dev_err(s->device->class_dev,
			"mite: transfer error %08x\n", status);
		s->async->events |= COMEDI_CB_ERROR;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mite_ack_linkc);

/**
 * mite_करोne() - Check is a MITE dma transfer is complete.
 * @mite_chan: MITE dma channel.
 *
 * This will also ack the DONE पूर्णांकerrupt अगर active.
 */
पूर्णांक mite_करोne(काष्ठा mite_channel *mite_chan)
अणु
	काष्ठा mite *mite = mite_chan->mite;
	अचिन्हित दीर्घ flags;
	पूर्णांक करोne;

	mite_get_status(mite_chan);
	spin_lock_irqsave(&mite->lock, flags);
	करोne = mite_chan->करोne;
	spin_unlock_irqrestore(&mite->lock, flags);
	वापस करोne;
पूर्ण
EXPORT_SYMBOL_GPL(mite_करोne);

अटल व्योम mite_dma_reset(काष्ठा mite_channel *mite_chan)
अणु
	ग_लिखोl(CHOR_DMARESET | CHOR_FRESET,
	       mite_chan->mite->mmio + MITE_CHOR(mite_chan->channel));
पूर्ण

/**
 * mite_dma_arm() - Start a MITE dma transfer.
 * @mite_chan: MITE dma channel.
 */
व्योम mite_dma_arm(काष्ठा mite_channel *mite_chan)
अणु
	काष्ठा mite *mite = mite_chan->mite;
	अचिन्हित दीर्घ flags;

	/*
	 * memory barrier is पूर्णांकended to insure any twiddling with the buffer
	 * is करोne beक्रमe writing to the mite to arm dma transfer
	 */
	smp_mb();
	spin_lock_irqsave(&mite->lock, flags);
	mite_chan->करोne = 0;
	/* arm */
	ग_लिखोl(CHOR_START, mite->mmio + MITE_CHOR(mite_chan->channel));
	spin_unlock_irqrestore(&mite->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(mite_dma_arm);

/**
 * mite_dma_disarm() - Stop a MITE dma transfer.
 * @mite_chan: MITE dma channel.
 */
व्योम mite_dma_disarm(काष्ठा mite_channel *mite_chan)
अणु
	काष्ठा mite *mite = mite_chan->mite;

	/* disarm */
	ग_लिखोl(CHOR_ABORT, mite->mmio + MITE_CHOR(mite_chan->channel));
पूर्ण
EXPORT_SYMBOL_GPL(mite_dma_disarm);

/**
 * mite_prep_dma() - Prepare a MITE dma channel क्रम transfers.
 * @mite_chan: MITE dma channel.
 * @num_device_bits: device transfer size (8, 16, or 32-bits).
 * @num_memory_bits: memory transfer size (8, 16, or 32-bits).
 */
व्योम mite_prep_dma(काष्ठा mite_channel *mite_chan,
		   अचिन्हित पूर्णांक num_device_bits, अचिन्हित पूर्णांक num_memory_bits)
अणु
	काष्ठा mite *mite = mite_chan->mite;
	अचिन्हित पूर्णांक chcr, mcr, dcr, lkcr;

	mite_dma_reset(mite_chan);

	/* लघु link chaining mode */
	chcr = CHCR_SET_DMA_IE | CHCR_LINKSHORT | CHCR_SET_DONE_IE |
	    CHCR_BURSTEN;
	/*
	 * Link Complete Interrupt: पूर्णांकerrupt every समय a link
	 * in MITE_RING is completed. This can generate a lot of
	 * extra पूर्णांकerrupts, but right now we update the values
	 * of buf_पूर्णांक_ptr and buf_पूर्णांक_count at each पूर्णांकerrupt. A
	 * better method is to poll the MITE beक्रमe each user
	 * "read()" to calculate the number of bytes available.
	 */
	chcr |= CHCR_SET_LC_IE;
	अगर (num_memory_bits == 32 && num_device_bits == 16) अणु
		/*
		 * Doing a combined 32 and 16 bit byteswap माला_लो the 16 bit
		 * samples पूर्णांकo the fअगरo in the right order. Tested करोing 32 bit
		 * memory to 16 bit device transfers to the analog out of a
		 * pxi-6281, which has mite version = 1, type = 4. This also
		 * works क्रम dma पढ़ोs from the counters on e-series boards.
		 */
		chcr |= CHCR_BYTE_SWAP_DEVICE | CHCR_BYTE_SWAP_MEMORY;
	पूर्ण
	अगर (mite_chan->dir == COMEDI_INPUT)
		chcr |= CHCR_DEV_TO_MEM;

	ग_लिखोl(chcr, mite->mmio + MITE_CHCR(mite_chan->channel));

	/* to/from memory */
	mcr = mite_retry_limit(64) | CR_ASEQUP;
	चयन (num_memory_bits) अणु
	हाल 8:
		mcr |= CR_PSIZE8;
		अवरोध;
	हाल 16:
		mcr |= CR_PSIZE16;
		अवरोध;
	हाल 32:
		mcr |= CR_PSIZE32;
		अवरोध;
	शेष:
		pr_warn("bug! invalid mem bit width for dma transfer\n");
		अवरोध;
	पूर्ण
	ग_लिखोl(mcr, mite->mmio + MITE_MCR(mite_chan->channel));

	/* from/to device */
	dcr = mite_retry_limit(64) | CR_ASEQUP;
	dcr |= CR_PORTIO | CR_AMDEVICE | mite_drq_reqs(mite_chan->channel);
	चयन (num_device_bits) अणु
	हाल 8:
		dcr |= CR_PSIZE8;
		अवरोध;
	हाल 16:
		dcr |= CR_PSIZE16;
		अवरोध;
	हाल 32:
		dcr |= CR_PSIZE32;
		अवरोध;
	शेष:
		pr_warn("bug! invalid dev bit width for dma transfer\n");
		अवरोध;
	पूर्ण
	ग_लिखोl(dcr, mite->mmio + MITE_DCR(mite_chan->channel));

	/* reset the DAR */
	ग_लिखोl(0, mite->mmio + MITE_DAR(mite_chan->channel));

	/* the link is 32bits */
	lkcr = mite_retry_limit(64) | CR_ASEQUP | CR_PSIZE32;
	ग_लिखोl(lkcr, mite->mmio + MITE_LKCR(mite_chan->channel));

	/* starting address क्रम link chaining */
	ग_लिखोl(mite_chan->ring->dma_addr,
	       mite->mmio + MITE_LKAR(mite_chan->channel));
पूर्ण
EXPORT_SYMBOL_GPL(mite_prep_dma);

/**
 * mite_request_channel_in_range() - Request a MITE dma channel.
 * @mite: MITE device.
 * @ring: MITE dma ring.
 * @min_channel: minimum channel index to use.
 * @max_channel: maximum channel index to use.
 */
काष्ठा mite_channel *mite_request_channel_in_range(काष्ठा mite *mite,
						   काष्ठा mite_ring *ring,
						   अचिन्हित पूर्णांक min_channel,
						   अचिन्हित पूर्णांक max_channel)
अणु
	काष्ठा mite_channel *mite_chan = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	/*
	 * spin lock so mite_release_channel can be called safely
	 * from पूर्णांकerrupts
	 */
	spin_lock_irqsave(&mite->lock, flags);
	क्रम (i = min_channel; i <= max_channel; ++i) अणु
		mite_chan = &mite->channels[i];
		अगर (!mite_chan->ring) अणु
			mite_chan->ring = ring;
			अवरोध;
		पूर्ण
		mite_chan = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&mite->lock, flags);
	वापस mite_chan;
पूर्ण
EXPORT_SYMBOL_GPL(mite_request_channel_in_range);

/**
 * mite_request_channel() - Request a MITE dma channel.
 * @mite: MITE device.
 * @ring: MITE dma ring.
 */
काष्ठा mite_channel *mite_request_channel(काष्ठा mite *mite,
					  काष्ठा mite_ring *ring)
अणु
	वापस mite_request_channel_in_range(mite, ring, 0,
					     mite->num_channels - 1);
पूर्ण
EXPORT_SYMBOL_GPL(mite_request_channel);

/**
 * mite_release_channel() - Release a MITE dma channel.
 * @mite_chan: MITE dma channel.
 */
व्योम mite_release_channel(काष्ठा mite_channel *mite_chan)
अणु
	काष्ठा mite *mite = mite_chan->mite;
	अचिन्हित दीर्घ flags;

	/* spin lock to prevent races with mite_request_channel */
	spin_lock_irqsave(&mite->lock, flags);
	अगर (mite_chan->ring) अणु
		mite_dma_disarm(mite_chan);
		mite_dma_reset(mite_chan);
		/*
		 * disable all channel's पूर्णांकerrupts (करो it after disarm/reset so
		 * MITE_CHCR reg isn't changed जबतक dma is still active!)
		 */
		ग_लिखोl(CHCR_CLR_DMA_IE | CHCR_CLR_LINKP_IE |
		       CHCR_CLR_SAR_IE | CHCR_CLR_DONE_IE |
		       CHCR_CLR_MRDY_IE | CHCR_CLR_DRDY_IE |
		       CHCR_CLR_LC_IE | CHCR_CLR_CONT_RB_IE,
		       mite->mmio + MITE_CHCR(mite_chan->channel));
		mite_chan->ring = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&mite->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(mite_release_channel);

/**
 * mite_init_ring_descriptors() - Initialize a MITE dma ring descriptors.
 * @ring: MITE dma ring.
 * @s: COMEDI subdevice.
 * @nbytes: the size of the dma ring (in bytes).
 *
 * Initializes the ring buffer descriptors to provide correct DMA transfer
 * links to the exact amount of memory required. When the ring buffer is
 * allocated by mite_buf_change(), the शेष is to initialize the ring
 * to refer to the entire DMA data buffer. A command may call this function
 * later to re-initialize and लघुen the amount of memory that will be
 * transferred.
 */
पूर्णांक mite_init_ring_descriptors(काष्ठा mite_ring *ring,
			       काष्ठा comedi_subdevice *s,
			       अचिन्हित पूर्णांक nbytes)
अणु
	काष्ठा comedi_async *async = s->async;
	काष्ठा mite_dma_desc *desc = शून्य;
	अचिन्हित पूर्णांक n_full_links = nbytes >> PAGE_SHIFT;
	अचिन्हित पूर्णांक reमुख्यder = nbytes % PAGE_SIZE;
	पूर्णांक i;

	dev_dbg(s->device->class_dev,
		"mite: init ring buffer to %u bytes\n", nbytes);

	अगर ((n_full_links + (reमुख्यder > 0 ? 1 : 0)) > ring->n_links) अणु
		dev_err(s->device->class_dev,
			"mite: ring buffer too small for requested init\n");
		वापस -ENOMEM;
	पूर्ण

	/* We set the descriptors क्रम all full links. */
	क्रम (i = 0; i < n_full_links; ++i) अणु
		desc = &ring->descs[i];
		desc->count = cpu_to_le32(PAGE_SIZE);
		desc->addr = cpu_to_le32(async->buf_map->page_list[i].dma_addr);
		desc->next = cpu_to_le32(ring->dma_addr +
					 (i + 1) * माप(*desc));
	पूर्ण

	/* the last link is either a reमुख्यder or was a full link. */
	अगर (reमुख्यder > 0) अणु
		desc = &ring->descs[i];
		/* set the lesser count क्रम the reमुख्यder link */
		desc->count = cpu_to_le32(reमुख्यder);
		desc->addr = cpu_to_le32(async->buf_map->page_list[i].dma_addr);
	पूर्ण

	/* Assign the last link->next to poपूर्णांक back to the head of the list. */
	desc->next = cpu_to_le32(ring->dma_addr);

	/*
	 * barrier is meant to insure that all the ग_लिखोs to the dma descriptors
	 * have completed beक्रमe the dma controller is commanded to पढ़ो them
	 */
	smp_wmb();
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mite_init_ring_descriptors);

अटल व्योम mite_मुक्त_dma_descs(काष्ठा mite_ring *ring)
अणु
	काष्ठा mite_dma_desc *descs = ring->descs;

	अगर (descs) अणु
		dma_मुक्त_coherent(ring->hw_dev,
				  ring->n_links * माप(*descs),
				  descs, ring->dma_addr);
		ring->descs = शून्य;
		ring->dma_addr = 0;
		ring->n_links = 0;
	पूर्ण
पूर्ण

/**
 * mite_buf_change() - COMEDI subdevice (*buf_change) क्रम a MITE dma ring.
 * @ring: MITE dma ring.
 * @s: COMEDI subdevice.
 */
पूर्णांक mite_buf_change(काष्ठा mite_ring *ring, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा comedi_async *async = s->async;
	काष्ठा mite_dma_desc *descs;
	अचिन्हित पूर्णांक n_links;

	mite_मुक्त_dma_descs(ring);

	अगर (async->pपुनः_स्मृति_bufsz == 0)
		वापस 0;

	n_links = async->pपुनः_स्मृति_bufsz >> PAGE_SHIFT;

	descs = dma_alloc_coherent(ring->hw_dev,
				   n_links * माप(*descs),
				   &ring->dma_addr, GFP_KERNEL);
	अगर (!descs) अणु
		dev_err(s->device->class_dev,
			"mite: ring buffer allocation failed\n");
		वापस -ENOMEM;
	पूर्ण
	ring->descs = descs;
	ring->n_links = n_links;

	वापस mite_init_ring_descriptors(ring, s, n_links << PAGE_SHIFT);
पूर्ण
EXPORT_SYMBOL_GPL(mite_buf_change);

/**
 * mite_alloc_ring() - Allocate a MITE dma ring.
 * @mite: MITE device.
 */
काष्ठा mite_ring *mite_alloc_ring(काष्ठा mite *mite)
अणु
	काष्ठा mite_ring *ring;

	ring = kदो_स्मृति(माप(*ring), GFP_KERNEL);
	अगर (!ring)
		वापस शून्य;
	ring->hw_dev = get_device(&mite->pcidev->dev);
	अगर (!ring->hw_dev) अणु
		kमुक्त(ring);
		वापस शून्य;
	पूर्ण
	ring->n_links = 0;
	ring->descs = शून्य;
	ring->dma_addr = 0;
	वापस ring;
पूर्ण
EXPORT_SYMBOL_GPL(mite_alloc_ring);

/**
 * mite_मुक्त_ring() - Free a MITE dma ring and its descriptors.
 * @ring: MITE dma ring.
 */
व्योम mite_मुक्त_ring(काष्ठा mite_ring *ring)
अणु
	अगर (ring) अणु
		mite_मुक्त_dma_descs(ring);
		put_device(ring->hw_dev);
		kमुक्त(ring);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mite_मुक्त_ring);

अटल पूर्णांक mite_setup(काष्ठा comedi_device *dev, काष्ठा mite *mite,
		      bool use_win1)
अणु
	resource_माप_प्रकार daq_phys_addr;
	अचिन्हित दीर्घ length;
	पूर्णांक i;
	u32 csigr_bits;
	अचिन्हित पूर्णांक unknown_dma_burst_bits;
	अचिन्हित पूर्णांक wpdep;

	pci_set_master(mite->pcidev);

	mite->mmio = pci_ioremap_bar(mite->pcidev, 0);
	अगर (!mite->mmio)
		वापस -ENOMEM;

	dev->mmio = pci_ioremap_bar(mite->pcidev, 1);
	अगर (!dev->mmio)
		वापस -ENOMEM;
	daq_phys_addr = pci_resource_start(mite->pcidev, 1);
	length = pci_resource_len(mite->pcidev, 1);

	अगर (use_win1) अणु
		ग_लिखोl(0, mite->mmio + MITE_IODWBSR);
		dev_dbg(dev->class_dev,
			"mite: using I/O Window Base Size register 1\n");
		ग_लिखोl(daq_phys_addr | WENAB |
		       MITE_IODWBSR_1_WSIZE_bits(length),
		       mite->mmio + MITE_IODWBSR_1);
		ग_लिखोl(0, mite->mmio + MITE_IODWCR_1);
	पूर्ण अन्यथा अणु
		ग_लिखोl(daq_phys_addr | WENAB, mite->mmio + MITE_IODWBSR);
	पूर्ण
	/*
	 * Make sure dma bursts work. I got this from running a bus analyzer
	 * on a pxi-6281 and a pxi-6713. 6713 घातered up with रेजिस्टर value
	 * of 0x61f and bursts worked. 6281 घातered up with रेजिस्टर value of
	 * 0x1f and bursts didn't work. The NI winकरोws driver पढ़ोs the
	 * रेजिस्टर, then करोes a bitwise-or of 0x600 with it and ग_लिखोs it back.
	 *
	 * The bits 0x90180700 in MITE_UNKNOWN_DMA_BURST_REG can be
	 * written and पढ़ो back.  The bits 0x1f always पढ़ो as 1.
	 * The rest always पढ़ो as zero.
	 */
	unknown_dma_burst_bits = पढ़ोl(mite->mmio + MITE_UNKNOWN_DMA_BURST_REG);
	unknown_dma_burst_bits |= UNKNOWN_DMA_BURST_ENABLE_BITS;
	ग_लिखोl(unknown_dma_burst_bits, mite->mmio + MITE_UNKNOWN_DMA_BURST_REG);

	csigr_bits = पढ़ोl(mite->mmio + MITE_CSIGR);
	mite->num_channels = CSIGR_TO_DMAC(csigr_bits);
	अगर (mite->num_channels > MAX_MITE_DMA_CHANNELS) अणु
		dev_warn(dev->class_dev,
			 "mite: bug? chip claims to have %i dma channels. Setting to %i.\n",
			 mite->num_channels, MAX_MITE_DMA_CHANNELS);
		mite->num_channels = MAX_MITE_DMA_CHANNELS;
	पूर्ण

	/* get the wpdep bits and convert it to the ग_लिखो port fअगरo depth */
	wpdep = CSIGR_TO_WPDEP(csigr_bits);
	अगर (wpdep)
		wpdep = BIT(wpdep);

	dev_dbg(dev->class_dev,
		"mite: version = %i, type = %i, mite mode = %i, interface mode = %i\n",
		CSIGR_TO_VER(csigr_bits), CSIGR_TO_TYPE(csigr_bits),
		CSIGR_TO_MMODE(csigr_bits), CSIGR_TO_IMODE(csigr_bits));
	dev_dbg(dev->class_dev,
		"mite: num channels = %i, write post fifo depth = %i, wins = %i, iowins = %i\n",
		CSIGR_TO_DMAC(csigr_bits), wpdep,
		CSIGR_TO_WINS(csigr_bits), CSIGR_TO_IOWINS(csigr_bits));

	क्रम (i = 0; i < mite->num_channels; i++) अणु
		ग_लिखोl(CHOR_DMARESET, mite->mmio + MITE_CHOR(i));
		/* disable पूर्णांकerrupts */
		ग_लिखोl(CHCR_CLR_DMA_IE | CHCR_CLR_LINKP_IE | CHCR_CLR_SAR_IE |
		       CHCR_CLR_DONE_IE | CHCR_CLR_MRDY_IE | CHCR_CLR_DRDY_IE |
		       CHCR_CLR_LC_IE | CHCR_CLR_CONT_RB_IE,
		       mite->mmio + MITE_CHCR(i));
	पूर्ण
	mite->fअगरo_size = mite_fअगरo_size(mite, 0);
	dev_dbg(dev->class_dev, "mite: fifo size is %i.\n", mite->fअगरo_size);
	वापस 0;
पूर्ण

/**
 * mite_attach() - Allocate and initialize a MITE device क्रम a comedi driver.
 * @dev: COMEDI device.
 * @use_win1: flag to use I/O Winकरोw 1 instead of I/O Winकरोw 0.
 *
 * Called by a COMEDI drivers (*स्वतः_attach).
 *
 * Returns a poपूर्णांकer to the MITE device on success, or शून्य अगर the MITE cannot
 * be allocated or remapped.
 */
काष्ठा mite *mite_attach(काष्ठा comedi_device *dev, bool use_win1)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	काष्ठा mite *mite;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	mite = kzalloc(माप(*mite), GFP_KERNEL);
	अगर (!mite)
		वापस शून्य;

	spin_lock_init(&mite->lock);
	mite->pcidev = pcidev;
	क्रम (i = 0; i < MAX_MITE_DMA_CHANNELS; ++i) अणु
		mite->channels[i].mite = mite;
		mite->channels[i].channel = i;
		mite->channels[i].करोne = 1;
	पूर्ण

	ret = mite_setup(dev, mite, use_win1);
	अगर (ret) अणु
		अगर (mite->mmio)
			iounmap(mite->mmio);
		kमुक्त(mite);
		वापस शून्य;
	पूर्ण

	वापस mite;
पूर्ण
EXPORT_SYMBOL_GPL(mite_attach);

/**
 * mite_detach() - Unmap and मुक्त a MITE device क्रम a comedi driver.
 * @mite: MITE device.
 *
 * Called by a COMEDI drivers (*detach).
 */
व्योम mite_detach(काष्ठा mite *mite)
अणु
	अगर (!mite)
		वापस;

	अगर (mite->mmio)
		iounmap(mite->mmio);

	kमुक्त(mite);
पूर्ण
EXPORT_SYMBOL_GPL(mite_detach);

अटल पूर्णांक __init mite_module_init(व्योम)
अणु
	वापस 0;
पूर्ण
module_init(mite_module_init);

अटल व्योम __निकास mite_module_निकास(व्योम)
अणु
पूर्ण
module_निकास(mite_module_निकास);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi helper for NI Mite PCI interface chip");
MODULE_LICENSE("GPL");
