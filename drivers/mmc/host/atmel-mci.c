<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Aपंचांगel MultiMedia Card Interface driver
 *
 * Copyright (C) 2004-2008 Aपंचांगel Corporation
 */
#समावेश <linux/blkdev.h>
#समावेश <linux/clk.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/device.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/types.h>

#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/sdपन.स>

#समावेश <linux/aपंचांगel-mci.h>
#समावेश <linux/aपंचांगel_pdc.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pinctrl/consumer.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/unaligned.h>

/*
 * Superset of MCI IP रेजिस्टरs पूर्णांकegrated in Aपंचांगel AT91 Processor
 * Registers and bitfields marked with [2] are only available in MCI2
 */

/* MCI Register Definitions */
#घोषणा	ATMCI_CR			0x0000	/* Control */
#घोषणा		ATMCI_CR_MCIEN			BIT(0)		/* MCI Enable */
#घोषणा		ATMCI_CR_MCIDIS			BIT(1)		/* MCI Disable */
#घोषणा		ATMCI_CR_PWSEN			BIT(2)		/* Power Save Enable */
#घोषणा		ATMCI_CR_PWSDIS			BIT(3)		/* Power Save Disable */
#घोषणा		ATMCI_CR_SWRST			BIT(7)		/* Software Reset */
#घोषणा	ATMCI_MR			0x0004	/* Mode */
#घोषणा		ATMCI_MR_CLKDIV(x)		((x) <<  0)	/* Clock Divider */
#घोषणा		ATMCI_MR_PWSDIV(x)		((x) <<  8)	/* Power Saving Divider */
#घोषणा		ATMCI_MR_RDPROOF		BIT(11)		/* Read Proof */
#घोषणा		ATMCI_MR_WRPROOF		BIT(12)		/* Write Proof */
#घोषणा		ATMCI_MR_PDCFBYTE		BIT(13)		/* Force Byte Transfer */
#घोषणा		ATMCI_MR_PDCPADV		BIT(14)		/* Padding Value */
#घोषणा		ATMCI_MR_PDCMODE		BIT(15)		/* PDC-oriented Mode */
#घोषणा		ATMCI_MR_CLKODD(x)		((x) << 16)	/* LSB of Clock Divider */
#घोषणा	ATMCI_DTOR			0x0008	/* Data Timeout */
#घोषणा		ATMCI_DTOCYC(x)			((x) <<  0)	/* Data Timeout Cycles */
#घोषणा		ATMCI_DTOMUL(x)			((x) <<  4)	/* Data Timeout Multiplier */
#घोषणा	ATMCI_SDCR			0x000c	/* SD Card / SDIO */
#घोषणा		ATMCI_SDCSEL_SLOT_A		(0 <<  0)	/* Select SD slot A */
#घोषणा		ATMCI_SDCSEL_SLOT_B		(1 <<  0)	/* Select SD slot A */
#घोषणा		ATMCI_SDCSEL_MASK		(3 <<  0)
#घोषणा		ATMCI_SDCBUS_1BIT		(0 <<  6)	/* 1-bit data bus */
#घोषणा		ATMCI_SDCBUS_4BIT		(2 <<  6)	/* 4-bit data bus */
#घोषणा		ATMCI_SDCBUS_8BIT		(3 <<  6)	/* 8-bit data bus[2] */
#घोषणा		ATMCI_SDCBUS_MASK		(3 <<  6)
#घोषणा	ATMCI_ARGR			0x0010	/* Command Argument */
#घोषणा	ATMCI_CMDR			0x0014	/* Command */
#घोषणा		ATMCI_CMDR_CMDNB(x)		((x) <<  0)	/* Command Opcode */
#घोषणा		ATMCI_CMDR_RSPTYP_NONE		(0 <<  6)	/* No response */
#घोषणा		ATMCI_CMDR_RSPTYP_48BIT		(1 <<  6)	/* 48-bit response */
#घोषणा		ATMCI_CMDR_RSPTYP_136BIT	(2 <<  6)	/* 136-bit response */
#घोषणा		ATMCI_CMDR_SPCMD_INIT		(1 <<  8)	/* Initialization command */
#घोषणा		ATMCI_CMDR_SPCMD_SYNC		(2 <<  8)	/* Synchronized command */
#घोषणा		ATMCI_CMDR_SPCMD_INT		(4 <<  8)	/* Interrupt command */
#घोषणा		ATMCI_CMDR_SPCMD_INTRESP	(5 <<  8)	/* Interrupt response */
#घोषणा		ATMCI_CMDR_OPDCMD		(1 << 11)	/* Open Drain */
#घोषणा		ATMCI_CMDR_MAXLAT_5CYC		(0 << 12)	/* Max latency 5 cycles */
#घोषणा		ATMCI_CMDR_MAXLAT_64CYC		(1 << 12)	/* Max latency 64 cycles */
#घोषणा		ATMCI_CMDR_START_XFER		(1 << 16)	/* Start data transfer */
#घोषणा		ATMCI_CMDR_STOP_XFER		(2 << 16)	/* Stop data transfer */
#घोषणा		ATMCI_CMDR_TRसूची_WRITE		(0 << 18)	/* Write data */
#घोषणा		ATMCI_CMDR_TRसूची_READ		(1 << 18)	/* Read data */
#घोषणा		ATMCI_CMDR_BLOCK		(0 << 19)	/* Single-block transfer */
#घोषणा		ATMCI_CMDR_MULTI_BLOCK		(1 << 19)	/* Multi-block transfer */
#घोषणा		ATMCI_CMDR_STREAM		(2 << 19)	/* MMC Stream transfer */
#घोषणा		ATMCI_CMDR_SDIO_BYTE		(4 << 19)	/* SDIO Byte transfer */
#घोषणा		ATMCI_CMDR_SDIO_BLOCK		(5 << 19)	/* SDIO Block transfer */
#घोषणा		ATMCI_CMDR_SDIO_SUSPEND		(1 << 24)	/* SDIO Suspend Command */
#घोषणा		ATMCI_CMDR_SDIO_RESUME		(2 << 24)	/* SDIO Resume Command */
#घोषणा	ATMCI_BLKR			0x0018	/* Block */
#घोषणा		ATMCI_BCNT(x)			((x) <<  0)	/* Data Block Count */
#घोषणा		ATMCI_BLKLEN(x)			((x) << 16)	/* Data Block Length */
#घोषणा	ATMCI_CSTOR			0x001c	/* Completion Signal Timeout[2] */
#घोषणा		ATMCI_CSTOCYC(x)		((x) <<  0)	/* CST cycles */
#घोषणा		ATMCI_CSTOMUL(x)		((x) <<  4)	/* CST multiplier */
#घोषणा	ATMCI_RSPR			0x0020	/* Response 0 */
#घोषणा	ATMCI_RSPR1			0x0024	/* Response 1 */
#घोषणा	ATMCI_RSPR2			0x0028	/* Response 2 */
#घोषणा	ATMCI_RSPR3			0x002c	/* Response 3 */
#घोषणा	ATMCI_RDR			0x0030	/* Receive Data */
#घोषणा	ATMCI_TDR			0x0034	/* Transmit Data */
#घोषणा	ATMCI_SR			0x0040	/* Status */
#घोषणा	ATMCI_IER			0x0044	/* Interrupt Enable */
#घोषणा	ATMCI_IDR			0x0048	/* Interrupt Disable */
#घोषणा	ATMCI_IMR			0x004c	/* Interrupt Mask */
#घोषणा		ATMCI_CMDRDY			BIT(0)		/* Command Ready */
#घोषणा		ATMCI_RXRDY			BIT(1)		/* Receiver Ready */
#घोषणा		ATMCI_TXRDY			BIT(2)		/* Transmitter Ready */
#घोषणा		ATMCI_BLKE			BIT(3)		/* Data Block Ended */
#घोषणा		ATMCI_DTIP			BIT(4)		/* Data Transfer In Progress */
#घोषणा		ATMCI_NOTBUSY			BIT(5)		/* Data Not Busy */
#घोषणा		ATMCI_ENDRX			BIT(6)		/* End of RX Buffer */
#घोषणा		ATMCI_ENDTX			BIT(7)		/* End of TX Buffer */
#घोषणा		ATMCI_SDIOIRQA			BIT(8)		/* SDIO IRQ in slot A */
#घोषणा		ATMCI_SDIOIRQB			BIT(9)		/* SDIO IRQ in slot B */
#घोषणा		ATMCI_SDIOWAIT			BIT(12)		/* SDIO Read Wait Operation Status */
#घोषणा		ATMCI_CSRCV			BIT(13)		/* CE-ATA Completion Signal Received */
#घोषणा		ATMCI_RXBUFF			BIT(14)		/* RX Buffer Full */
#घोषणा		ATMCI_TXBUFE			BIT(15)		/* TX Buffer Empty */
#घोषणा		ATMCI_RINDE			BIT(16)		/* Response Index Error */
#घोषणा		ATMCI_RसूचीE			BIT(17)		/* Response Direction Error */
#घोषणा		ATMCI_RCRCE			BIT(18)		/* Response CRC Error */
#घोषणा		ATMCI_RENDE			BIT(19)		/* Response End Bit Error */
#घोषणा		ATMCI_RTOE			BIT(20)		/* Response Time-Out Error */
#घोषणा		ATMCI_DCRCE			BIT(21)		/* Data CRC Error */
#घोषणा		ATMCI_DTOE			BIT(22)		/* Data Time-Out Error */
#घोषणा		ATMCI_CSTOE			BIT(23)		/* Completion Signal Time-out Error */
#घोषणा		ATMCI_BLKOVRE			BIT(24)		/* DMA Block Overrun Error */
#घोषणा		ATMCI_DMADONE			BIT(25)		/* DMA Transfer Done */
#घोषणा		ATMCI_FIFOEMPTY			BIT(26)		/* FIFO Empty Flag */
#घोषणा		ATMCI_XFRDONE			BIT(27)		/* Transfer Done Flag */
#घोषणा		ATMCI_ACKRCV			BIT(28)		/* Boot Operation Acknowledge Received */
#घोषणा		ATMCI_ACKRCVE			BIT(29)		/* Boot Operation Acknowledge Error */
#घोषणा		ATMCI_OVRE			BIT(30)		/* RX Overrun Error */
#घोषणा		ATMCI_UNRE			BIT(31)		/* TX Underrun Error */
#घोषणा	ATMCI_DMA			0x0050	/* DMA Configuration[2] */
#घोषणा		ATMCI_DMA_OFFSET(x)		((x) <<  0)	/* DMA Write Buffer Offset */
#घोषणा		ATMCI_DMA_CHKSIZE(x)		((x) <<  4)	/* DMA Channel Read and Write Chunk Size */
#घोषणा		ATMCI_DMAEN			BIT(8)	/* DMA Hardware Handshaking Enable */
#घोषणा	ATMCI_CFG			0x0054	/* Configuration[2] */
#घोषणा		ATMCI_CFG_FIFOMODE_1DATA	BIT(0)		/* MCI Internal FIFO control mode */
#घोषणा		ATMCI_CFG_FERRCTRL_COR		BIT(4)		/* Flow Error flag reset control mode */
#घोषणा		ATMCI_CFG_HSMODE		BIT(8)		/* High Speed Mode */
#घोषणा		ATMCI_CFG_LSYNC			BIT(12)		/* Synchronize on the last block */
#घोषणा	ATMCI_WPMR			0x00e4	/* Write Protection Mode[2] */
#घोषणा		ATMCI_WP_EN			BIT(0)		/* WP Enable */
#घोषणा		ATMCI_WP_KEY			(0x4d4349 << 8)	/* WP Key */
#घोषणा	ATMCI_WPSR			0x00e8	/* Write Protection Status[2] */
#घोषणा		ATMCI_GET_WP_VS(x)		((x) & 0x0f)
#घोषणा		ATMCI_GET_WP_VSRC(x)		(((x) >> 8) & 0xffff)
#घोषणा	ATMCI_VERSION			0x00FC  /* Version */
#घोषणा	ATMCI_FIFO_APERTURE		0x0200	/* FIFO Aperture[2] */

/* This is not including the FIFO Aperture on MCI2 */
#घोषणा	ATMCI_REGS_SIZE		0x100

/* Register access macros */
#घोषणा	aपंचांगci_पढ़ोl(port, reg)				\
	__raw_पढ़ोl((port)->regs + reg)
#घोषणा	aपंचांगci_ग_लिखोl(port, reg, value)			\
	__raw_ग_लिखोl((value), (port)->regs + reg)

#घोषणा ATMCI_CMD_TIMEOUT_MS	2000
#घोषणा AUTOSUSPEND_DELAY	50

#घोषणा ATMCI_DATA_ERROR_FLAGS	(ATMCI_DCRCE | ATMCI_DTOE | ATMCI_OVRE | ATMCI_UNRE)
#घोषणा ATMCI_DMA_THRESHOLD	16

क्रमागत अणु
	EVENT_CMD_RDY = 0,
	EVENT_XFER_COMPLETE,
	EVENT_NOTBUSY,
	EVENT_DATA_ERROR,
पूर्ण;

क्रमागत aपंचांगel_mci_state अणु
	STATE_IDLE = 0,
	STATE_SENDING_CMD,
	STATE_DATA_XFER,
	STATE_WAITING_NOTBUSY,
	STATE_SENDING_STOP,
	STATE_END_REQUEST,
पूर्ण;

क्रमागत aपंचांगci_xfer_dir अणु
	XFER_RECEIVE = 0,
	XFER_TRANSMIT,
पूर्ण;

क्रमागत aपंचांगci_pdc_buf अणु
	PDC_FIRST_BUF = 0,
	PDC_SECOND_BUF,
पूर्ण;

काष्ठा aपंचांगel_mci_caps अणु
	bool    has_dma_conf_reg;
	bool    has_pdc;
	bool    has_cfg_reg;
	bool    has_cstor_reg;
	bool    has_highspeed;
	bool    has_rwproof;
	bool	has_odd_clk_भाग;
	bool	has_bad_data_ordering;
	bool	need_reset_after_xfer;
	bool	need_blksz_mul_4;
	bool	need_notbusy_क्रम_पढ़ो_ops;
पूर्ण;

काष्ठा aपंचांगel_mci_dma अणु
	काष्ठा dma_chan			*chan;
	काष्ठा dma_async_tx_descriptor	*data_desc;
पूर्ण;

/**
 * काष्ठा aपंचांगel_mci - MMC controller state shared between all slots
 * @lock: Spinlock protecting the queue and associated data.
 * @regs: Poपूर्णांकer to MMIO रेजिस्टरs.
 * @sg: Scatterlist entry currently being processed by PIO or PDC code.
 * @sg_len: Size of the scatterlist
 * @pio_offset: Offset पूर्णांकo the current scatterlist entry.
 * @buffer: Buffer used अगर we करोn't have the r/w proof capability. We
 *      करोn't have the समय to चयन pdc buffers so we have to use only
 *      one buffer क्रम the full transaction.
 * @buf_size: size of the buffer.
 * @buf_phys_addr: buffer address needed क्रम pdc.
 * @cur_slot: The slot which is currently using the controller.
 * @mrq: The request currently being processed on @cur_slot,
 *	or शून्य अगर the controller is idle.
 * @cmd: The command currently being sent to the card, or शून्य.
 * @data: The data currently being transferred, or शून्य अगर no data
 *	transfer is in progress.
 * @data_size: just data->blocks * data->blksz.
 * @dma: DMA client state.
 * @data_chan: DMA channel being used क्रम the current data transfer.
 * @dma_conf: Configuration क्रम the DMA slave
 * @cmd_status: Snapshot of SR taken upon completion of the current
 *	command. Only valid when EVENT_CMD_COMPLETE is pending.
 * @data_status: Snapshot of SR taken upon completion of the current
 *	data transfer. Only valid when EVENT_DATA_COMPLETE or
 *	EVENT_DATA_ERROR is pending.
 * @stop_cmdr: Value to be loaded पूर्णांकo CMDR when the stop command is
 *	to be sent.
 * @tasklet: Tasklet running the request state machine.
 * @pending_events: Biपंचांगask of events flagged by the पूर्णांकerrupt handler
 *	to be processed by the tasklet.
 * @completed_events: Biपंचांगask of events which the state machine has
 *	processed.
 * @state: Tasklet state.
 * @queue: List of slots रुकोing क्रम access to the controller.
 * @need_घड़ी_update: Update the घड़ी rate beक्रमe the next request.
 * @need_reset: Reset controller beक्रमe next request.
 * @समयr: Timer to balance the data समयout error flag which cannot rise.
 * @mode_reg: Value of the MR रेजिस्टर.
 * @cfg_reg: Value of the CFG रेजिस्टर.
 * @bus_hz: The rate of @mck in Hz. This क्रमms the basis क्रम MMC bus
 *	rate and समयout calculations.
 * @mapbase: Physical address of the MMIO रेजिस्टरs.
 * @mck: The peripheral bus घड़ी hooked up to the MMC controller.
 * @pdev: Platक्रमm device associated with the MMC controller.
 * @slot: Slots sharing this MMC controller.
 * @caps: MCI capabilities depending on MCI version.
 * @prepare_data: function to setup MCI beक्रमe data transfer which
 * depends on MCI capabilities.
 * @submit_data: function to start data transfer which depends on MCI
 * capabilities.
 * @stop_transfer: function to stop data transfer which depends on MCI
 * capabilities.
 *
 * Locking
 * =======
 *
 * @lock is a softirq-safe spinlock protecting @queue as well as
 * @cur_slot, @mrq and @state. These must always be updated
 * at the same समय जबतक holding @lock.
 *
 * @lock also protects mode_reg and need_घड़ी_update since these are
 * used to synchronize mode रेजिस्टर updates with the queue
 * processing.
 *
 * The @mrq field of काष्ठा aपंचांगel_mci_slot is also रक्षित by @lock,
 * and must always be written at the same समय as the slot is added to
 * @queue.
 *
 * @pending_events and @completed_events are accessed using atomic bit
 * operations, so they करोn't need any locking.
 *
 * None of the fields touched by the पूर्णांकerrupt handler need any
 * locking. However, ordering is important: Beक्रमe EVENT_DATA_ERROR or
 * EVENT_DATA_COMPLETE is set in @pending_events, all data-related
 * पूर्णांकerrupts must be disabled and @data_status updated with a
 * snapshot of SR. Similarly, beक्रमe EVENT_CMD_COMPLETE is set, the
 * CMDRDY पूर्णांकerrupt must be disabled and @cmd_status updated with a
 * snapshot of SR, and beक्रमe EVENT_XFER_COMPLETE can be set, the
 * bytes_xfered field of @data must be written. This is ensured by
 * using barriers.
 */
काष्ठा aपंचांगel_mci अणु
	spinlock_t		lock;
	व्योम __iomem		*regs;

	काष्ठा scatterlist	*sg;
	अचिन्हित पूर्णांक		sg_len;
	अचिन्हित पूर्णांक		pio_offset;
	अचिन्हित पूर्णांक		*buffer;
	अचिन्हित पूर्णांक		buf_size;
	dma_addr_t		buf_phys_addr;

	काष्ठा aपंचांगel_mci_slot	*cur_slot;
	काष्ठा mmc_request	*mrq;
	काष्ठा mmc_command	*cmd;
	काष्ठा mmc_data		*data;
	अचिन्हित पूर्णांक		data_size;

	काष्ठा aपंचांगel_mci_dma	dma;
	काष्ठा dma_chan		*data_chan;
	काष्ठा dma_slave_config	dma_conf;

	u32			cmd_status;
	u32			data_status;
	u32			stop_cmdr;

	काष्ठा tasklet_काष्ठा	tasklet;
	अचिन्हित दीर्घ		pending_events;
	अचिन्हित दीर्घ		completed_events;
	क्रमागत aपंचांगel_mci_state	state;
	काष्ठा list_head	queue;

	bool			need_घड़ी_update;
	bool			need_reset;
	काष्ठा समयr_list	समयr;
	u32			mode_reg;
	u32			cfg_reg;
	अचिन्हित दीर्घ		bus_hz;
	अचिन्हित दीर्घ		mapbase;
	काष्ठा clk		*mck;
	काष्ठा platक्रमm_device	*pdev;

	काष्ठा aपंचांगel_mci_slot	*slot[ATMCI_MAX_NR_SLOTS];

	काष्ठा aपंचांगel_mci_caps   caps;

	u32 (*prepare_data)(काष्ठा aपंचांगel_mci *host, काष्ठा mmc_data *data);
	व्योम (*submit_data)(काष्ठा aपंचांगel_mci *host, काष्ठा mmc_data *data);
	व्योम (*stop_transfer)(काष्ठा aपंचांगel_mci *host);
पूर्ण;

/**
 * काष्ठा aपंचांगel_mci_slot - MMC slot state
 * @mmc: The mmc_host representing this slot.
 * @host: The MMC controller this slot is using.
 * @sdc_reg: Value of SDCR to be written beक्रमe using this slot.
 * @sdio_irq: SDIO irq mask क्रम this slot.
 * @mrq: mmc_request currently being processed or रुकोing to be
 *	processed, or शून्य when the slot is idle.
 * @queue_node: List node क्रम placing this node in the @queue list of
 *	&काष्ठा aपंचांगel_mci.
 * @घड़ी: Clock rate configured by set_ios(). Protected by host->lock.
 * @flags: Ranकरोm state bits associated with the slot.
 * @detect_pin: GPIO pin used क्रम card detection, or negative अगर not
 *	available.
 * @wp_pin: GPIO pin used क्रम card ग_लिखो protect sending, or negative
 *	अगर not available.
 * @detect_is_active_high: The state of the detect pin when it is active.
 * @detect_समयr: Timer used क्रम debouncing @detect_pin पूर्णांकerrupts.
 */
काष्ठा aपंचांगel_mci_slot अणु
	काष्ठा mmc_host		*mmc;
	काष्ठा aपंचांगel_mci	*host;

	u32			sdc_reg;
	u32			sdio_irq;

	काष्ठा mmc_request	*mrq;
	काष्ठा list_head	queue_node;

	अचिन्हित पूर्णांक		घड़ी;
	अचिन्हित दीर्घ		flags;
#घोषणा ATMCI_CARD_PRESENT	0
#घोषणा ATMCI_CARD_NEED_INIT	1
#घोषणा ATMCI_SHUTDOWN		2

	पूर्णांक			detect_pin;
	पूर्णांक			wp_pin;
	bool			detect_is_active_high;

	काष्ठा समयr_list	detect_समयr;
पूर्ण;

#घोषणा aपंचांगci_test_and_clear_pending(host, event)		\
	test_and_clear_bit(event, &host->pending_events)
#घोषणा aपंचांगci_set_completed(host, event)			\
	set_bit(event, &host->completed_events)
#घोषणा aपंचांगci_set_pending(host, event)				\
	set_bit(event, &host->pending_events)

/*
 * The debugfs stuff below is mostly optimized away when
 * CONFIG_DEBUG_FS is not set.
 */
अटल पूर्णांक aपंचांगci_req_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा aपंचांगel_mci_slot	*slot = s->निजी;
	काष्ठा mmc_request	*mrq;
	काष्ठा mmc_command	*cmd;
	काष्ठा mmc_command	*stop;
	काष्ठा mmc_data		*data;

	/* Make sure we get a consistent snapshot */
	spin_lock_bh(&slot->host->lock);
	mrq = slot->mrq;

	अगर (mrq) अणु
		cmd = mrq->cmd;
		data = mrq->data;
		stop = mrq->stop;

		अगर (cmd)
			seq_म_लिखो(s,
				"CMD%u(0x%x) flg %x rsp %x %x %x %x err %d\n",
				cmd->opcode, cmd->arg, cmd->flags,
				cmd->resp[0], cmd->resp[1], cmd->resp[2],
				cmd->resp[3], cmd->error);
		अगर (data)
			seq_म_लिखो(s, "DATA %u / %u * %u flg %x err %d\n",
				data->bytes_xfered, data->blocks,
				data->blksz, data->flags, data->error);
		अगर (stop)
			seq_म_लिखो(s,
				"CMD%u(0x%x) flg %x rsp %x %x %x %x err %d\n",
				stop->opcode, stop->arg, stop->flags,
				stop->resp[0], stop->resp[1], stop->resp[2],
				stop->resp[3], stop->error);
	पूर्ण

	spin_unlock_bh(&slot->host->lock);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(aपंचांगci_req);

अटल व्योम aपंचांगci_show_status_reg(काष्ठा seq_file *s,
		स्थिर अक्षर *regname, u32 value)
अणु
	अटल स्थिर अक्षर	*sr_bit[] = अणु
		[0]	= "CMDRDY",
		[1]	= "RXRDY",
		[2]	= "TXRDY",
		[3]	= "BLKE",
		[4]	= "DTIP",
		[5]	= "NOTBUSY",
		[6]	= "ENDRX",
		[7]	= "ENDTX",
		[8]	= "SDIOIRQA",
		[9]	= "SDIOIRQB",
		[12]	= "SDIOWAIT",
		[14]	= "RXBUFF",
		[15]	= "TXBUFE",
		[16]	= "RINDE",
		[17]	= "RDIRE",
		[18]	= "RCRCE",
		[19]	= "RENDE",
		[20]	= "RTOE",
		[21]	= "DCRCE",
		[22]	= "DTOE",
		[23]	= "CSTOE",
		[24]	= "BLKOVRE",
		[25]	= "DMADONE",
		[26]	= "FIFOEMPTY",
		[27]	= "XFRDONE",
		[30]	= "OVRE",
		[31]	= "UNRE",
	पूर्ण;
	अचिन्हित पूर्णांक		i;

	seq_म_लिखो(s, "%s:\t0x%08x", regname, value);
	क्रम (i = 0; i < ARRAY_SIZE(sr_bit); i++) अणु
		अगर (value & (1 << i)) अणु
			अगर (sr_bit[i])
				seq_म_लिखो(s, " %s", sr_bit[i]);
			अन्यथा
				seq_माला_दो(s, " UNKNOWN");
		पूर्ण
	पूर्ण
	seq_अ_दो(s, '\n');
पूर्ण

अटल पूर्णांक aपंचांगci_regs_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा aपंचांगel_mci	*host = s->निजी;
	u32			*buf;
	पूर्णांक			ret = 0;


	buf = kदो_स्मृति(ATMCI_REGS_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	pm_runसमय_get_sync(&host->pdev->dev);

	/*
	 * Grab a more or less consistent snapshot. Note that we're
	 * not disabling पूर्णांकerrupts, so IMR and SR may not be
	 * consistent.
	 */
	spin_lock_bh(&host->lock);
	स_नकल_fromio(buf, host->regs, ATMCI_REGS_SIZE);
	spin_unlock_bh(&host->lock);

	pm_runसमय_mark_last_busy(&host->pdev->dev);
	pm_runसमय_put_स्वतःsuspend(&host->pdev->dev);

	seq_म_लिखो(s, "MR:\t0x%08x%s%s ",
			buf[ATMCI_MR / 4],
			buf[ATMCI_MR / 4] & ATMCI_MR_RDPROOF ? " RDPROOF" : "",
			buf[ATMCI_MR / 4] & ATMCI_MR_WRPROOF ? " WRPROOF" : "");
	अगर (host->caps.has_odd_clk_भाग)
		seq_म_लिखो(s, "{CLKDIV,CLKODD}=%u\n",
				((buf[ATMCI_MR / 4] & 0xff) << 1)
				| ((buf[ATMCI_MR / 4] >> 16) & 1));
	अन्यथा
		seq_म_लिखो(s, "CLKDIV=%u\n",
				(buf[ATMCI_MR / 4] & 0xff));
	seq_म_लिखो(s, "DTOR:\t0x%08x\n", buf[ATMCI_DTOR / 4]);
	seq_म_लिखो(s, "SDCR:\t0x%08x\n", buf[ATMCI_SDCR / 4]);
	seq_म_लिखो(s, "ARGR:\t0x%08x\n", buf[ATMCI_ARGR / 4]);
	seq_म_लिखो(s, "BLKR:\t0x%08x BCNT=%u BLKLEN=%u\n",
			buf[ATMCI_BLKR / 4],
			buf[ATMCI_BLKR / 4] & 0xffff,
			(buf[ATMCI_BLKR / 4] >> 16) & 0xffff);
	अगर (host->caps.has_cstor_reg)
		seq_म_लिखो(s, "CSTOR:\t0x%08x\n", buf[ATMCI_CSTOR / 4]);

	/* Don't पढ़ो RSPR and RDR; it will consume the data there */

	aपंचांगci_show_status_reg(s, "SR", buf[ATMCI_SR / 4]);
	aपंचांगci_show_status_reg(s, "IMR", buf[ATMCI_IMR / 4]);

	अगर (host->caps.has_dma_conf_reg) अणु
		u32 val;

		val = buf[ATMCI_DMA / 4];
		seq_म_लिखो(s, "DMA:\t0x%08x OFFSET=%u CHKSIZE=%u%s\n",
				val, val & 3,
				((val >> 4) & 3) ?
					1 << (((val >> 4) & 3) + 1) : 1,
				val & ATMCI_DMAEN ? " DMAEN" : "");
	पूर्ण
	अगर (host->caps.has_cfg_reg) अणु
		u32 val;

		val = buf[ATMCI_CFG / 4];
		seq_म_लिखो(s, "CFG:\t0x%08x%s%s%s%s\n",
				val,
				val & ATMCI_CFG_FIFOMODE_1DATA ? " FIFOMODE_ONE_DATA" : "",
				val & ATMCI_CFG_FERRCTRL_COR ? " FERRCTRL_CLEAR_ON_READ" : "",
				val & ATMCI_CFG_HSMODE ? " HSMODE" : "",
				val & ATMCI_CFG_LSYNC ? " LSYNC" : "");
	पूर्ण

	kमुक्त(buf);

	वापस ret;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(aपंचांगci_regs);

अटल व्योम aपंचांगci_init_debugfs(काष्ठा aपंचांगel_mci_slot *slot)
अणु
	काष्ठा mmc_host		*mmc = slot->mmc;
	काष्ठा aपंचांगel_mci	*host = slot->host;
	काष्ठा dentry		*root;

	root = mmc->debugfs_root;
	अगर (!root)
		वापस;

	debugfs_create_file("regs", S_IRUSR, root, host, &aपंचांगci_regs_fops);
	debugfs_create_file("req", S_IRUSR, root, slot, &aपंचांगci_req_fops);
	debugfs_create_u32("state", S_IRUSR, root, &host->state);
	debugfs_create_xul("pending_events", S_IRUSR, root,
			   &host->pending_events);
	debugfs_create_xul("completed_events", S_IRUSR, root,
			   &host->completed_events);
पूर्ण

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id aपंचांगci_dt_ids[] = अणु
	अणु .compatible = "atmel,hsmci" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, aपंचांगci_dt_ids);

अटल काष्ठा mci_platक्रमm_data*
aपंचांगci_of_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *cnp;
	काष्ठा mci_platक्रमm_data *pdata;
	u32 slot_id;

	अगर (!np) अणु
		dev_err(&pdev->dev, "device node not found\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस ERR_PTR(-ENOMEM);

	क्रम_each_child_of_node(np, cnp) अणु
		अगर (of_property_पढ़ो_u32(cnp, "reg", &slot_id)) अणु
			dev_warn(&pdev->dev, "reg property is missing for %pOF\n",
				 cnp);
			जारी;
		पूर्ण

		अगर (slot_id >= ATMCI_MAX_NR_SLOTS) अणु
			dev_warn(&pdev->dev, "can't have more than %d slots\n",
			         ATMCI_MAX_NR_SLOTS);
			of_node_put(cnp);
			अवरोध;
		पूर्ण

		अगर (of_property_पढ़ो_u32(cnp, "bus-width",
		                         &pdata->slot[slot_id].bus_width))
			pdata->slot[slot_id].bus_width = 1;

		pdata->slot[slot_id].detect_pin =
			of_get_named_gpio(cnp, "cd-gpios", 0);

		pdata->slot[slot_id].detect_is_active_high =
			of_property_पढ़ो_bool(cnp, "cd-inverted");

		pdata->slot[slot_id].non_removable =
			of_property_पढ़ो_bool(cnp, "non-removable");

		pdata->slot[slot_id].wp_pin =
			of_get_named_gpio(cnp, "wp-gpios", 0);
	पूर्ण

	वापस pdata;
पूर्ण
#अन्यथा /* CONFIG_OF */
अटल अंतरभूत काष्ठा mci_platक्रमm_data*
aपंचांगci_of_init(काष्ठा platक्रमm_device *dev)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत अचिन्हित पूर्णांक aपंचांगci_get_version(काष्ठा aपंचांगel_mci *host)
अणु
	वापस aपंचांगci_पढ़ोl(host, ATMCI_VERSION) & 0x00000fff;
पूर्ण

/*
 * Fix sconfig's burst size according to aपंचांगel MCI. We need to convert them as:
 * 1 -> 0, 4 -> 1, 8 -> 2, 16 -> 3.
 * With version 0x600, we need to convert them as: 1 -> 0, 2 -> 1, 4 -> 2,
 * 8 -> 3, 16 -> 4.
 *
 * This can be करोne by finding most signअगरicant bit set.
 */
अटल अंतरभूत अचिन्हित पूर्णांक aपंचांगci_convert_chksize(काष्ठा aपंचांगel_mci *host,
						 अचिन्हित पूर्णांक maxburst)
अणु
	अचिन्हित पूर्णांक version = aपंचांगci_get_version(host);
	अचिन्हित पूर्णांक offset = 2;

	अगर (version >= 0x600)
		offset = 1;

	अगर (maxburst > 1)
		वापस fls(maxburst) - offset;
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम aपंचांगci_समयout_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा aपंचांगel_mci *host;

	host = from_समयr(host, t, समयr);

	dev_dbg(&host->pdev->dev, "software timeout\n");

	अगर (host->mrq->cmd->data) अणु
		host->mrq->cmd->data->error = -ETIMEDOUT;
		host->data = शून्य;
		/*
		 * With some SDIO modules, someबार DMA transfer hangs. If
		 * stop_transfer() is not called then the DMA request is not
		 * हटाओd, following ones are queued and never computed.
		 */
		अगर (host->state == STATE_DATA_XFER)
			host->stop_transfer(host);
	पूर्ण अन्यथा अणु
		host->mrq->cmd->error = -ETIMEDOUT;
		host->cmd = शून्य;
	पूर्ण
	host->need_reset = 1;
	host->state = STATE_END_REQUEST;
	smp_wmb();
	tasklet_schedule(&host->tasklet);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक aपंचांगci_ns_to_घड़ीs(काष्ठा aपंचांगel_mci *host,
					अचिन्हित पूर्णांक ns)
अणु
	/*
	 * It is easier here to use us instead of ns क्रम the समयout,
	 * it prevents from overflows during calculation.
	 */
	अचिन्हित पूर्णांक us = DIV_ROUND_UP(ns, 1000);

	/* Maximum घड़ी frequency is host->bus_hz/2 */
	वापस us * (DIV_ROUND_UP(host->bus_hz, 2000000));
पूर्ण

अटल व्योम aपंचांगci_set_समयout(काष्ठा aपंचांगel_mci *host,
		काष्ठा aपंचांगel_mci_slot *slot, काष्ठा mmc_data *data)
अणु
	अटल अचिन्हित	dtomul_to_shअगरt[] = अणु
		0, 4, 7, 8, 10, 12, 16, 20
	पूर्ण;
	अचिन्हित	समयout;
	अचिन्हित	dtocyc;
	अचिन्हित	dtomul;

	समयout = aपंचांगci_ns_to_घड़ीs(host, data->समयout_ns)
		+ data->समयout_clks;

	क्रम (dtomul = 0; dtomul < 8; dtomul++) अणु
		अचिन्हित shअगरt = dtomul_to_shअगरt[dtomul];
		dtocyc = (समयout + (1 << shअगरt) - 1) >> shअगरt;
		अगर (dtocyc < 15)
			अवरोध;
	पूर्ण

	अगर (dtomul >= 8) अणु
		dtomul = 7;
		dtocyc = 15;
	पूर्ण

	dev_vdbg(&slot->mmc->class_dev, "setting timeout to %u cycles\n",
			dtocyc << dtomul_to_shअगरt[dtomul]);
	aपंचांगci_ग_लिखोl(host, ATMCI_DTOR, (ATMCI_DTOMUL(dtomul) | ATMCI_DTOCYC(dtocyc)));
पूर्ण

/*
 * Return mask with command flags to be enabled क्रम this command.
 */
अटल u32 aपंचांगci_prepare_command(काष्ठा mmc_host *mmc,
				 काष्ठा mmc_command *cmd)
अणु
	काष्ठा mmc_data	*data;
	u32		cmdr;

	cmd->error = -EINPROGRESS;

	cmdr = ATMCI_CMDR_CMDNB(cmd->opcode);

	अगर (cmd->flags & MMC_RSP_PRESENT) अणु
		अगर (cmd->flags & MMC_RSP_136)
			cmdr |= ATMCI_CMDR_RSPTYP_136BIT;
		अन्यथा
			cmdr |= ATMCI_CMDR_RSPTYP_48BIT;
	पूर्ण

	/*
	 * This should really be MAXLAT_5 क्रम CMD2 and ACMD41, but
	 * it's too dअगरficult to determine whether this is an ACMD or
	 * not. Better make it 64.
	 */
	cmdr |= ATMCI_CMDR_MAXLAT_64CYC;

	अगर (mmc->ios.bus_mode == MMC_BUSMODE_OPENDRAIN)
		cmdr |= ATMCI_CMDR_OPDCMD;

	data = cmd->data;
	अगर (data) अणु
		cmdr |= ATMCI_CMDR_START_XFER;

		अगर (cmd->opcode == SD_IO_RW_EXTENDED) अणु
			cmdr |= ATMCI_CMDR_SDIO_BLOCK;
		पूर्ण अन्यथा अणु
			अगर (data->blocks > 1)
				cmdr |= ATMCI_CMDR_MULTI_BLOCK;
			अन्यथा
				cmdr |= ATMCI_CMDR_BLOCK;
		पूर्ण

		अगर (data->flags & MMC_DATA_READ)
			cmdr |= ATMCI_CMDR_TRसूची_READ;
	पूर्ण

	वापस cmdr;
पूर्ण

अटल व्योम aपंचांगci_send_command(काष्ठा aपंचांगel_mci *host,
		काष्ठा mmc_command *cmd, u32 cmd_flags)
अणु
	अचिन्हित पूर्णांक समयout_ms = cmd->busy_समयout ? cmd->busy_समयout :
		ATMCI_CMD_TIMEOUT_MS;

	WARN_ON(host->cmd);
	host->cmd = cmd;

	dev_vdbg(&host->pdev->dev,
			"start command: ARGR=0x%08x CMDR=0x%08x\n",
			cmd->arg, cmd_flags);

	aपंचांगci_ग_लिखोl(host, ATMCI_ARGR, cmd->arg);
	aपंचांगci_ग_लिखोl(host, ATMCI_CMDR, cmd_flags);

	mod_समयr(&host->समयr, jअगरfies + msecs_to_jअगरfies(समयout_ms));
पूर्ण

अटल व्योम aपंचांगci_send_stop_cmd(काष्ठा aपंचांगel_mci *host, काष्ठा mmc_data *data)
अणु
	dev_dbg(&host->pdev->dev, "send stop command\n");
	aपंचांगci_send_command(host, data->stop, host->stop_cmdr);
	aपंचांगci_ग_लिखोl(host, ATMCI_IER, ATMCI_CMDRDY);
पूर्ण

/*
 * Configure given PDC buffer taking care of alignement issues.
 * Update host->data_size and host->sg.
 */
अटल व्योम aपंचांगci_pdc_set_single_buf(काष्ठा aपंचांगel_mci *host,
	क्रमागत aपंचांगci_xfer_dir dir, क्रमागत aपंचांगci_pdc_buf buf_nb)
अणु
	u32 poपूर्णांकer_reg, counter_reg;
	अचिन्हित पूर्णांक buf_size;

	अगर (dir == XFER_RECEIVE) अणु
		poपूर्णांकer_reg = ATMEL_PDC_RPR;
		counter_reg = ATMEL_PDC_RCR;
	पूर्ण अन्यथा अणु
		poपूर्णांकer_reg = ATMEL_PDC_TPR;
		counter_reg = ATMEL_PDC_TCR;
	पूर्ण

	अगर (buf_nb == PDC_SECOND_BUF) अणु
		poपूर्णांकer_reg += ATMEL_PDC_SCND_BUF_OFF;
		counter_reg += ATMEL_PDC_SCND_BUF_OFF;
	पूर्ण

	अगर (!host->caps.has_rwproof) अणु
		buf_size = host->buf_size;
		aपंचांगci_ग_लिखोl(host, poपूर्णांकer_reg, host->buf_phys_addr);
	पूर्ण अन्यथा अणु
		buf_size = sg_dma_len(host->sg);
		aपंचांगci_ग_लिखोl(host, poपूर्णांकer_reg, sg_dma_address(host->sg));
	पूर्ण

	अगर (host->data_size <= buf_size) अणु
		अगर (host->data_size & 0x3) अणु
			/* If size is dअगरferent from modulo 4, transfer bytes */
			aपंचांगci_ग_लिखोl(host, counter_reg, host->data_size);
			aपंचांगci_ग_लिखोl(host, ATMCI_MR, host->mode_reg | ATMCI_MR_PDCFBYTE);
		पूर्ण अन्यथा अणु
			/* Else transfer 32-bits words */
			aपंचांगci_ग_लिखोl(host, counter_reg, host->data_size / 4);
		पूर्ण
		host->data_size = 0;
	पूर्ण अन्यथा अणु
		/* We assume the size of a page is 32-bits aligned */
		aपंचांगci_ग_लिखोl(host, counter_reg, sg_dma_len(host->sg) / 4);
		host->data_size -= sg_dma_len(host->sg);
		अगर (host->data_size)
			host->sg = sg_next(host->sg);
	पूर्ण
पूर्ण

/*
 * Configure PDC buffer according to the data size ie configuring one or two
 * buffers. Don't use this function अगर you want to configure only the second
 * buffer. In this हाल, use aपंचांगci_pdc_set_single_buf.
 */
अटल व्योम aपंचांगci_pdc_set_both_buf(काष्ठा aपंचांगel_mci *host, पूर्णांक dir)
अणु
	aपंचांगci_pdc_set_single_buf(host, dir, PDC_FIRST_BUF);
	अगर (host->data_size)
		aपंचांगci_pdc_set_single_buf(host, dir, PDC_SECOND_BUF);
पूर्ण

/*
 * Unmap sg lists, called when transfer is finished.
 */
अटल व्योम aपंचांगci_pdc_cleanup(काष्ठा aपंचांगel_mci *host)
अणु
	काष्ठा mmc_data         *data = host->data;

	अगर (data)
		dma_unmap_sg(&host->pdev->dev,
				data->sg, data->sg_len,
				mmc_get_dma_dir(data));
पूर्ण

/*
 * Disable PDC transfers. Update pending flags to EVENT_XFER_COMPLETE after
 * having received ATMCI_TXBUFE or ATMCI_RXBUFF पूर्णांकerrupt. Enable ATMCI_NOTBUSY
 * पूर्णांकerrupt needed क्रम both transfer directions.
 */
अटल व्योम aपंचांगci_pdc_complete(काष्ठा aपंचांगel_mci *host)
अणु
	पूर्णांक transfer_size = host->data->blocks * host->data->blksz;
	पूर्णांक i;

	aपंचांगci_ग_लिखोl(host, ATMEL_PDC_PTCR, ATMEL_PDC_RXTDIS | ATMEL_PDC_TXTDIS);

	अगर ((!host->caps.has_rwproof)
	    && (host->data->flags & MMC_DATA_READ)) अणु
		अगर (host->caps.has_bad_data_ordering)
			क्रम (i = 0; i < transfer_size; i++)
				host->buffer[i] = swab32(host->buffer[i]);
		sg_copy_from_buffer(host->data->sg, host->data->sg_len,
		                    host->buffer, transfer_size);
	पूर्ण

	aपंचांगci_pdc_cleanup(host);

	dev_dbg(&host->pdev->dev, "(%s) set pending xfer complete\n", __func__);
	aपंचांगci_set_pending(host, EVENT_XFER_COMPLETE);
	tasklet_schedule(&host->tasklet);
पूर्ण

अटल व्योम aपंचांगci_dma_cleanup(काष्ठा aपंचांगel_mci *host)
अणु
	काष्ठा mmc_data                 *data = host->data;

	अगर (data)
		dma_unmap_sg(host->dma.chan->device->dev,
				data->sg, data->sg_len,
				mmc_get_dma_dir(data));
पूर्ण

/*
 * This function is called by the DMA driver from tasklet context.
 */
अटल व्योम aपंचांगci_dma_complete(व्योम *arg)
अणु
	काष्ठा aपंचांगel_mci	*host = arg;
	काष्ठा mmc_data		*data = host->data;

	dev_vdbg(&host->pdev->dev, "DMA complete\n");

	अगर (host->caps.has_dma_conf_reg)
		/* Disable DMA hardware handshaking on MCI */
		aपंचांगci_ग_लिखोl(host, ATMCI_DMA, aपंचांगci_पढ़ोl(host, ATMCI_DMA) & ~ATMCI_DMAEN);

	aपंचांगci_dma_cleanup(host);

	/*
	 * If the card was हटाओd, data will be शून्य. No poपूर्णांक trying
	 * to send the stop command or रुकोing क्रम NBUSY in this हाल.
	 */
	अगर (data) अणु
		dev_dbg(&host->pdev->dev,
		        "(%s) set pending xfer complete\n", __func__);
		aपंचांगci_set_pending(host, EVENT_XFER_COMPLETE);
		tasklet_schedule(&host->tasklet);

		/*
		 * Regardless of what the करोcumentation says, we have
		 * to रुको क्रम NOTBUSY even after block पढ़ो
		 * operations.
		 *
		 * When the DMA transfer is complete, the controller
		 * may still be पढ़ोing the CRC from the card, i.e.
		 * the data transfer is still in progress and we
		 * haven't seen all the potential error bits yet.
		 *
		 * The पूर्णांकerrupt handler will schedule a dअगरferent
		 * tasklet to finish things up when the data transfer
		 * is completely करोne.
		 *
		 * We may not complete the mmc request here anyway
		 * because the mmc layer may call back and cause us to
		 * violate the "करोn't submit new operations from the
		 * completion callback" rule of the dma engine
		 * framework.
		 */
		aपंचांगci_ग_लिखोl(host, ATMCI_IER, ATMCI_NOTBUSY);
	पूर्ण
पूर्ण

/*
 * Returns a mask of पूर्णांकerrupt flags to be enabled after the whole
 * request has been prepared.
 */
अटल u32 aपंचांगci_prepare_data(काष्ठा aपंचांगel_mci *host, काष्ठा mmc_data *data)
अणु
	u32 अगरlags;

	data->error = -EINPROGRESS;

	host->sg = data->sg;
	host->sg_len = data->sg_len;
	host->data = data;
	host->data_chan = शून्य;

	अगरlags = ATMCI_DATA_ERROR_FLAGS;

	/*
	 * Errata: MMC data ग_लिखो operation with less than 12
	 * bytes is impossible.
	 *
	 * Errata: MCI Transmit Data Register (TDR) FIFO
	 * corruption when length is not multiple of 4.
	 */
	अगर (data->blocks * data->blksz < 12
			|| (data->blocks * data->blksz) & 3)
		host->need_reset = true;

	host->pio_offset = 0;
	अगर (data->flags & MMC_DATA_READ)
		अगरlags |= ATMCI_RXRDY;
	अन्यथा
		अगरlags |= ATMCI_TXRDY;

	वापस अगरlags;
पूर्ण

/*
 * Set पूर्णांकerrupt flags and set block length पूर्णांकo the MCI mode रेजिस्टर even
 * अगर this value is also accessible in the MCI block रेजिस्टर. It seems to be
 * necessary beक्रमe the High Speed MCI version. It also map sg and configure
 * PDC रेजिस्टरs.
 */
अटल u32
aपंचांगci_prepare_data_pdc(काष्ठा aपंचांगel_mci *host, काष्ठा mmc_data *data)
अणु
	u32 अगरlags, पंचांगp;
	पूर्णांक i;

	data->error = -EINPROGRESS;

	host->data = data;
	host->sg = data->sg;
	अगरlags = ATMCI_DATA_ERROR_FLAGS;

	/* Enable pdc mode */
	aपंचांगci_ग_लिखोl(host, ATMCI_MR, host->mode_reg | ATMCI_MR_PDCMODE);

	अगर (data->flags & MMC_DATA_READ)
		अगरlags |= ATMCI_ENDRX | ATMCI_RXBUFF;
	अन्यथा
		अगरlags |= ATMCI_ENDTX | ATMCI_TXBUFE | ATMCI_BLKE;

	/* Set BLKLEN */
	पंचांगp = aपंचांगci_पढ़ोl(host, ATMCI_MR);
	पंचांगp &= 0x0000ffff;
	पंचांगp |= ATMCI_BLKLEN(data->blksz);
	aपंचांगci_ग_लिखोl(host, ATMCI_MR, पंचांगp);

	/* Configure PDC */
	host->data_size = data->blocks * data->blksz;
	dma_map_sg(&host->pdev->dev, data->sg, data->sg_len,
		   mmc_get_dma_dir(data));

	अगर ((!host->caps.has_rwproof)
	    && (host->data->flags & MMC_DATA_WRITE)) अणु
		sg_copy_to_buffer(host->data->sg, host->data->sg_len,
		                  host->buffer, host->data_size);
		अगर (host->caps.has_bad_data_ordering)
			क्रम (i = 0; i < host->data_size; i++)
				host->buffer[i] = swab32(host->buffer[i]);
	पूर्ण

	अगर (host->data_size)
		aपंचांगci_pdc_set_both_buf(host, data->flags & MMC_DATA_READ ?
				       XFER_RECEIVE : XFER_TRANSMIT);
	वापस अगरlags;
पूर्ण

अटल u32
aपंचांगci_prepare_data_dma(काष्ठा aपंचांगel_mci *host, काष्ठा mmc_data *data)
अणु
	काष्ठा dma_chan			*chan;
	काष्ठा dma_async_tx_descriptor	*desc;
	काष्ठा scatterlist		*sg;
	अचिन्हित पूर्णांक			i;
	क्रमागत dma_transfer_direction	slave_dirn;
	अचिन्हित पूर्णांक			sglen;
	u32				maxburst;
	u32 अगरlags;

	data->error = -EINPROGRESS;

	WARN_ON(host->data);
	host->sg = शून्य;
	host->data = data;

	अगरlags = ATMCI_DATA_ERROR_FLAGS;

	/*
	 * We करोn't करो DMA on "complex" transfers, i.e. with
	 * non-word-aligned buffers or lengths. Also, we करोn't bother
	 * with all the DMA setup overhead क्रम लघु transfers.
	 */
	अगर (data->blocks * data->blksz < ATMCI_DMA_THRESHOLD)
		वापस aपंचांगci_prepare_data(host, data);
	अगर (data->blksz & 3)
		वापस aपंचांगci_prepare_data(host, data);

	क्रम_each_sg(data->sg, sg, data->sg_len, i) अणु
		अगर (sg->offset & 3 || sg->length & 3)
			वापस aपंचांगci_prepare_data(host, data);
	पूर्ण

	/* If we करोn't have a channel, we can't करो DMA */
	chan = host->dma.chan;
	अगर (chan)
		host->data_chan = chan;

	अगर (!chan)
		वापस -ENODEV;

	अगर (data->flags & MMC_DATA_READ) अणु
		host->dma_conf.direction = slave_dirn = DMA_DEV_TO_MEM;
		maxburst = aपंचांगci_convert_chksize(host,
						 host->dma_conf.src_maxburst);
	पूर्ण अन्यथा अणु
		host->dma_conf.direction = slave_dirn = DMA_MEM_TO_DEV;
		maxburst = aपंचांगci_convert_chksize(host,
						 host->dma_conf.dst_maxburst);
	पूर्ण

	अगर (host->caps.has_dma_conf_reg)
		aपंचांगci_ग_लिखोl(host, ATMCI_DMA, ATMCI_DMA_CHKSIZE(maxburst) |
			ATMCI_DMAEN);

	sglen = dma_map_sg(chan->device->dev, data->sg,
			data->sg_len, mmc_get_dma_dir(data));

	dmaengine_slave_config(chan, &host->dma_conf);
	desc = dmaengine_prep_slave_sg(chan,
			data->sg, sglen, slave_dirn,
			DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!desc)
		जाओ unmap_निकास;

	host->dma.data_desc = desc;
	desc->callback = aपंचांगci_dma_complete;
	desc->callback_param = host;

	वापस अगरlags;
unmap_निकास:
	dma_unmap_sg(chan->device->dev, data->sg, data->sg_len,
		     mmc_get_dma_dir(data));
	वापस -ENOMEM;
पूर्ण

अटल व्योम
aपंचांगci_submit_data(काष्ठा aपंचांगel_mci *host, काष्ठा mmc_data *data)
अणु
	वापस;
पूर्ण

/*
 * Start PDC according to transfer direction.
 */
अटल व्योम
aपंचांगci_submit_data_pdc(काष्ठा aपंचांगel_mci *host, काष्ठा mmc_data *data)
अणु
	अगर (data->flags & MMC_DATA_READ)
		aपंचांगci_ग_लिखोl(host, ATMEL_PDC_PTCR, ATMEL_PDC_RXTEN);
	अन्यथा
		aपंचांगci_ग_लिखोl(host, ATMEL_PDC_PTCR, ATMEL_PDC_TXTEN);
पूर्ण

अटल व्योम
aपंचांगci_submit_data_dma(काष्ठा aपंचांगel_mci *host, काष्ठा mmc_data *data)
अणु
	काष्ठा dma_chan			*chan = host->data_chan;
	काष्ठा dma_async_tx_descriptor	*desc = host->dma.data_desc;

	अगर (chan) अणु
		dmaengine_submit(desc);
		dma_async_issue_pending(chan);
	पूर्ण
पूर्ण

अटल व्योम aपंचांगci_stop_transfer(काष्ठा aपंचांगel_mci *host)
अणु
	dev_dbg(&host->pdev->dev,
	        "(%s) set pending xfer complete\n", __func__);
	aपंचांगci_set_pending(host, EVENT_XFER_COMPLETE);
	aपंचांगci_ग_लिखोl(host, ATMCI_IER, ATMCI_NOTBUSY);
पूर्ण

/*
 * Stop data transfer because error(s) occurred.
 */
अटल व्योम aपंचांगci_stop_transfer_pdc(काष्ठा aपंचांगel_mci *host)
अणु
	aपंचांगci_ग_लिखोl(host, ATMEL_PDC_PTCR, ATMEL_PDC_RXTDIS | ATMEL_PDC_TXTDIS);
पूर्ण

अटल व्योम aपंचांगci_stop_transfer_dma(काष्ठा aपंचांगel_mci *host)
अणु
	काष्ठा dma_chan *chan = host->data_chan;

	अगर (chan) अणु
		dmaengine_terminate_all(chan);
		aपंचांगci_dma_cleanup(host);
	पूर्ण अन्यथा अणु
		/* Data transfer was stopped by the पूर्णांकerrupt handler */
		dev_dbg(&host->pdev->dev,
		        "(%s) set pending xfer complete\n", __func__);
		aपंचांगci_set_pending(host, EVENT_XFER_COMPLETE);
		aपंचांगci_ग_लिखोl(host, ATMCI_IER, ATMCI_NOTBUSY);
	पूर्ण
पूर्ण

/*
 * Start a request: prepare data अगर needed, prepare the command and activate
 * पूर्णांकerrupts.
 */
अटल व्योम aपंचांगci_start_request(काष्ठा aपंचांगel_mci *host,
		काष्ठा aपंचांगel_mci_slot *slot)
अणु
	काष्ठा mmc_request	*mrq;
	काष्ठा mmc_command	*cmd;
	काष्ठा mmc_data		*data;
	u32			अगरlags;
	u32			cmdflags;

	mrq = slot->mrq;
	host->cur_slot = slot;
	host->mrq = mrq;

	host->pending_events = 0;
	host->completed_events = 0;
	host->cmd_status = 0;
	host->data_status = 0;

	dev_dbg(&host->pdev->dev, "start request: cmd %u\n", mrq->cmd->opcode);

	अगर (host->need_reset || host->caps.need_reset_after_xfer) अणु
		अगरlags = aपंचांगci_पढ़ोl(host, ATMCI_IMR);
		अगरlags &= (ATMCI_SDIOIRQA | ATMCI_SDIOIRQB);
		aपंचांगci_ग_लिखोl(host, ATMCI_CR, ATMCI_CR_SWRST);
		aपंचांगci_ग_लिखोl(host, ATMCI_CR, ATMCI_CR_MCIEN);
		aपंचांगci_ग_लिखोl(host, ATMCI_MR, host->mode_reg);
		अगर (host->caps.has_cfg_reg)
			aपंचांगci_ग_लिखोl(host, ATMCI_CFG, host->cfg_reg);
		aपंचांगci_ग_लिखोl(host, ATMCI_IER, अगरlags);
		host->need_reset = false;
	पूर्ण
	aपंचांगci_ग_लिखोl(host, ATMCI_SDCR, slot->sdc_reg);

	अगरlags = aपंचांगci_पढ़ोl(host, ATMCI_IMR);
	अगर (अगरlags & ~(ATMCI_SDIOIRQA | ATMCI_SDIOIRQB))
		dev_dbg(&slot->mmc->class_dev, "WARNING: IMR=0x%08x\n",
				अगरlags);

	अगर (unlikely(test_and_clear_bit(ATMCI_CARD_NEED_INIT, &slot->flags))) अणु
		/* Send init sequence (74 घड़ी cycles) */
		aपंचांगci_ग_लिखोl(host, ATMCI_CMDR, ATMCI_CMDR_SPCMD_INIT);
		जबतक (!(aपंचांगci_पढ़ोl(host, ATMCI_SR) & ATMCI_CMDRDY))
			cpu_relax();
	पूर्ण
	अगरlags = 0;
	data = mrq->data;
	अगर (data) अणु
		aपंचांगci_set_समयout(host, slot, data);

		/* Must set block count/size beक्रमe sending command */
		aपंचांगci_ग_लिखोl(host, ATMCI_BLKR, ATMCI_BCNT(data->blocks)
				| ATMCI_BLKLEN(data->blksz));
		dev_vdbg(&slot->mmc->class_dev, "BLKR=0x%08x\n",
			ATMCI_BCNT(data->blocks) | ATMCI_BLKLEN(data->blksz));

		अगरlags |= host->prepare_data(host, data);
	पूर्ण

	अगरlags |= ATMCI_CMDRDY;
	cmd = mrq->cmd;
	cmdflags = aपंचांगci_prepare_command(slot->mmc, cmd);

	/*
	 * DMA transfer should be started beक्रमe sending the command to aव्योम
	 * unexpected errors especially क्रम पढ़ो operations in SDIO mode.
	 * Unक्रमtunately, in PDC mode, command has to be sent beक्रमe starting
	 * the transfer.
	 */
	अगर (host->submit_data != &aपंचांगci_submit_data_dma)
		aपंचांगci_send_command(host, cmd, cmdflags);

	अगर (data)
		host->submit_data(host, data);

	अगर (host->submit_data == &aपंचांगci_submit_data_dma)
		aपंचांगci_send_command(host, cmd, cmdflags);

	अगर (mrq->stop) अणु
		host->stop_cmdr = aपंचांगci_prepare_command(slot->mmc, mrq->stop);
		host->stop_cmdr |= ATMCI_CMDR_STOP_XFER;
		अगर (!(data->flags & MMC_DATA_WRITE))
			host->stop_cmdr |= ATMCI_CMDR_TRसूची_READ;
		host->stop_cmdr |= ATMCI_CMDR_MULTI_BLOCK;
	पूर्ण

	/*
	 * We could have enabled पूर्णांकerrupts earlier, but I suspect
	 * that would खोलो up a nice can of पूर्णांकeresting race
	 * conditions (e.g. command and data complete, but stop not
	 * prepared yet.)
	 */
	aपंचांगci_ग_लिखोl(host, ATMCI_IER, अगरlags);
पूर्ण

अटल व्योम aपंचांगci_queue_request(काष्ठा aपंचांगel_mci *host,
		काष्ठा aपंचांगel_mci_slot *slot, काष्ठा mmc_request *mrq)
अणु
	dev_vdbg(&slot->mmc->class_dev, "queue request: state=%d\n",
			host->state);

	spin_lock_bh(&host->lock);
	slot->mrq = mrq;
	अगर (host->state == STATE_IDLE) अणु
		host->state = STATE_SENDING_CMD;
		aपंचांगci_start_request(host, slot);
	पूर्ण अन्यथा अणु
		dev_dbg(&host->pdev->dev, "queue request\n");
		list_add_tail(&slot->queue_node, &host->queue);
	पूर्ण
	spin_unlock_bh(&host->lock);
पूर्ण

अटल व्योम aपंचांगci_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा aपंचांगel_mci_slot	*slot = mmc_priv(mmc);
	काष्ठा aपंचांगel_mci	*host = slot->host;
	काष्ठा mmc_data		*data;

	WARN_ON(slot->mrq);
	dev_dbg(&host->pdev->dev, "MRQ: cmd %u\n", mrq->cmd->opcode);

	/*
	 * We may "know" the card is gone even though there's still an
	 * electrical connection. If so, we really need to communicate
	 * this to the MMC core since there won't be any more
	 * पूर्णांकerrupts as the card is completely हटाओd. Otherwise,
	 * the MMC core might believe the card is still there even
	 * though the card was just हटाओd very slowly.
	 */
	अगर (!test_bit(ATMCI_CARD_PRESENT, &slot->flags)) अणु
		mrq->cmd->error = -ENOMEDIUM;
		mmc_request_करोne(mmc, mrq);
		वापस;
	पूर्ण

	/* We करोn't support multiple blocks of weird lengths. */
	data = mrq->data;
	अगर (data && data->blocks > 1 && data->blksz & 3) अणु
		mrq->cmd->error = -EINVAL;
		mmc_request_करोne(mmc, mrq);
	पूर्ण

	aपंचांगci_queue_request(host, slot, mrq);
पूर्ण

अटल व्योम aपंचांगci_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा aपंचांगel_mci_slot	*slot = mmc_priv(mmc);
	काष्ठा aपंचांगel_mci	*host = slot->host;
	अचिन्हित पूर्णांक		i;

	slot->sdc_reg &= ~ATMCI_SDCBUS_MASK;
	चयन (ios->bus_width) अणु
	हाल MMC_BUS_WIDTH_1:
		slot->sdc_reg |= ATMCI_SDCBUS_1BIT;
		अवरोध;
	हाल MMC_BUS_WIDTH_4:
		slot->sdc_reg |= ATMCI_SDCBUS_4BIT;
		अवरोध;
	हाल MMC_BUS_WIDTH_8:
		slot->sdc_reg |= ATMCI_SDCBUS_8BIT;
		अवरोध;
	पूर्ण

	अगर (ios->घड़ी) अणु
		अचिन्हित पूर्णांक घड़ी_min = ~0U;
		पूर्णांक clkभाग;

		spin_lock_bh(&host->lock);
		अगर (!host->mode_reg) अणु
			aपंचांगci_ग_लिखोl(host, ATMCI_CR, ATMCI_CR_SWRST);
			aपंचांगci_ग_लिखोl(host, ATMCI_CR, ATMCI_CR_MCIEN);
			अगर (host->caps.has_cfg_reg)
				aपंचांगci_ग_लिखोl(host, ATMCI_CFG, host->cfg_reg);
		पूर्ण

		/*
		 * Use mirror of ios->घड़ी to prevent race with mmc
		 * core ios update when finding the minimum.
		 */
		slot->घड़ी = ios->घड़ी;
		क्रम (i = 0; i < ATMCI_MAX_NR_SLOTS; i++) अणु
			अगर (host->slot[i] && host->slot[i]->घड़ी
					&& host->slot[i]->घड़ी < घड़ी_min)
				घड़ी_min = host->slot[i]->घड़ी;
		पूर्ण

		/* Calculate घड़ी भागider */
		अगर (host->caps.has_odd_clk_भाग) अणु
			clkभाग = DIV_ROUND_UP(host->bus_hz, घड़ी_min) - 2;
			अगर (clkभाग < 0) अणु
				dev_warn(&mmc->class_dev,
					 "clock %u too fast; using %lu\n",
					 घड़ी_min, host->bus_hz / 2);
				clkभाग = 0;
			पूर्ण अन्यथा अगर (clkभाग > 511) अणु
				dev_warn(&mmc->class_dev,
				         "clock %u too slow; using %lu\n",
				         घड़ी_min, host->bus_hz / (511 + 2));
				clkभाग = 511;
			पूर्ण
			host->mode_reg = ATMCI_MR_CLKDIV(clkभाग >> 1)
			                 | ATMCI_MR_CLKODD(clkभाग & 1);
		पूर्ण अन्यथा अणु
			clkभाग = DIV_ROUND_UP(host->bus_hz, 2 * घड़ी_min) - 1;
			अगर (clkभाग > 255) अणु
				dev_warn(&mmc->class_dev,
				         "clock %u too slow; using %lu\n",
				         घड़ी_min, host->bus_hz / (2 * 256));
				clkभाग = 255;
			पूर्ण
			host->mode_reg = ATMCI_MR_CLKDIV(clkभाग);
		पूर्ण

		/*
		 * WRPROOF and RDPROOF prevent overruns/underruns by
		 * stopping the घड़ी when the FIFO is full/empty.
		 * This state is not expected to last क्रम दीर्घ.
		 */
		अगर (host->caps.has_rwproof)
			host->mode_reg |= (ATMCI_MR_WRPROOF | ATMCI_MR_RDPROOF);

		अगर (host->caps.has_cfg_reg) अणु
			/* setup High Speed mode in relation with card capacity */
			अगर (ios->timing == MMC_TIMING_SD_HS)
				host->cfg_reg |= ATMCI_CFG_HSMODE;
			अन्यथा
				host->cfg_reg &= ~ATMCI_CFG_HSMODE;
		पूर्ण

		अगर (list_empty(&host->queue)) अणु
			aपंचांगci_ग_लिखोl(host, ATMCI_MR, host->mode_reg);
			अगर (host->caps.has_cfg_reg)
				aपंचांगci_ग_लिखोl(host, ATMCI_CFG, host->cfg_reg);
		पूर्ण अन्यथा अणु
			host->need_घड़ी_update = true;
		पूर्ण

		spin_unlock_bh(&host->lock);
	पूर्ण अन्यथा अणु
		bool any_slot_active = false;

		spin_lock_bh(&host->lock);
		slot->घड़ी = 0;
		क्रम (i = 0; i < ATMCI_MAX_NR_SLOTS; i++) अणु
			अगर (host->slot[i] && host->slot[i]->घड़ी) अणु
				any_slot_active = true;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!any_slot_active) अणु
			aपंचांगci_ग_लिखोl(host, ATMCI_CR, ATMCI_CR_MCIDIS);
			अगर (host->mode_reg) अणु
				aपंचांगci_पढ़ोl(host, ATMCI_MR);
			पूर्ण
			host->mode_reg = 0;
		पूर्ण
		spin_unlock_bh(&host->lock);
	पूर्ण

	चयन (ios->घातer_mode) अणु
	हाल MMC_POWER_OFF:
		अगर (!IS_ERR(mmc->supply.vmmc))
			mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, 0);
		अवरोध;
	हाल MMC_POWER_UP:
		set_bit(ATMCI_CARD_NEED_INIT, &slot->flags);
		अगर (!IS_ERR(mmc->supply.vmmc))
			mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, ios->vdd);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक aपंचांगci_get_ro(काष्ठा mmc_host *mmc)
अणु
	पूर्णांक			पढ़ो_only = -ENOSYS;
	काष्ठा aपंचांगel_mci_slot	*slot = mmc_priv(mmc);

	अगर (gpio_is_valid(slot->wp_pin)) अणु
		पढ़ो_only = gpio_get_value(slot->wp_pin);
		dev_dbg(&mmc->class_dev, "card is %s\n",
				पढ़ो_only ? "read-only" : "read-write");
	पूर्ण

	वापस पढ़ो_only;
पूर्ण

अटल पूर्णांक aपंचांगci_get_cd(काष्ठा mmc_host *mmc)
अणु
	पूर्णांक			present = -ENOSYS;
	काष्ठा aपंचांगel_mci_slot	*slot = mmc_priv(mmc);

	अगर (gpio_is_valid(slot->detect_pin)) अणु
		present = !(gpio_get_value(slot->detect_pin) ^
			    slot->detect_is_active_high);
		dev_dbg(&mmc->class_dev, "card is %spresent\n",
				present ? "" : "not ");
	पूर्ण

	वापस present;
पूर्ण

अटल व्योम aपंचांगci_enable_sdio_irq(काष्ठा mmc_host *mmc, पूर्णांक enable)
अणु
	काष्ठा aपंचांगel_mci_slot	*slot = mmc_priv(mmc);
	काष्ठा aपंचांगel_mci	*host = slot->host;

	अगर (enable)
		aपंचांगci_ग_लिखोl(host, ATMCI_IER, slot->sdio_irq);
	अन्यथा
		aपंचांगci_ग_लिखोl(host, ATMCI_IDR, slot->sdio_irq);
पूर्ण

अटल स्थिर काष्ठा mmc_host_ops aपंचांगci_ops = अणु
	.request	= aपंचांगci_request,
	.set_ios	= aपंचांगci_set_ios,
	.get_ro		= aपंचांगci_get_ro,
	.get_cd		= aपंचांगci_get_cd,
	.enable_sdio_irq = aपंचांगci_enable_sdio_irq,
पूर्ण;

/* Called with host->lock held */
अटल व्योम aपंचांगci_request_end(काष्ठा aपंचांगel_mci *host, काष्ठा mmc_request *mrq)
	__releases(&host->lock)
	__acquires(&host->lock)
अणु
	काष्ठा aपंचांगel_mci_slot	*slot = शून्य;
	काष्ठा mmc_host		*prev_mmc = host->cur_slot->mmc;

	WARN_ON(host->cmd || host->data);

	del_समयr(&host->समयr);

	/*
	 * Update the MMC घड़ी rate अगर necessary. This may be
	 * necessary अगर set_ios() is called when a dअगरferent slot is
	 * busy transferring data.
	 */
	अगर (host->need_घड़ी_update) अणु
		aपंचांगci_ग_लिखोl(host, ATMCI_MR, host->mode_reg);
		अगर (host->caps.has_cfg_reg)
			aपंचांगci_ग_लिखोl(host, ATMCI_CFG, host->cfg_reg);
	पूर्ण

	host->cur_slot->mrq = शून्य;
	host->mrq = शून्य;
	अगर (!list_empty(&host->queue)) अणु
		slot = list_entry(host->queue.next,
				काष्ठा aपंचांगel_mci_slot, queue_node);
		list_del(&slot->queue_node);
		dev_vdbg(&host->pdev->dev, "list not empty: %s is next\n",
				mmc_hostname(slot->mmc));
		host->state = STATE_SENDING_CMD;
		aपंचांगci_start_request(host, slot);
	पूर्ण अन्यथा अणु
		dev_vdbg(&host->pdev->dev, "list empty\n");
		host->state = STATE_IDLE;
	पूर्ण

	spin_unlock(&host->lock);
	mmc_request_करोne(prev_mmc, mrq);
	spin_lock(&host->lock);
पूर्ण

अटल व्योम aपंचांगci_command_complete(काष्ठा aपंचांगel_mci *host,
			काष्ठा mmc_command *cmd)
अणु
	u32		status = host->cmd_status;

	/* Read the response from the card (up to 16 bytes) */
	cmd->resp[0] = aपंचांगci_पढ़ोl(host, ATMCI_RSPR);
	cmd->resp[1] = aपंचांगci_पढ़ोl(host, ATMCI_RSPR);
	cmd->resp[2] = aपंचांगci_पढ़ोl(host, ATMCI_RSPR);
	cmd->resp[3] = aपंचांगci_पढ़ोl(host, ATMCI_RSPR);

	अगर (status & ATMCI_RTOE)
		cmd->error = -ETIMEDOUT;
	अन्यथा अगर ((cmd->flags & MMC_RSP_CRC) && (status & ATMCI_RCRCE))
		cmd->error = -EILSEQ;
	अन्यथा अगर (status & (ATMCI_RINDE | ATMCI_RसूचीE | ATMCI_RENDE))
		cmd->error = -EIO;
	अन्यथा अगर (host->mrq->data && (host->mrq->data->blksz & 3)) अणु
		अगर (host->caps.need_blksz_mul_4) अणु
			cmd->error = -EINVAL;
			host->need_reset = 1;
		पूर्ण
	पूर्ण अन्यथा
		cmd->error = 0;
पूर्ण

अटल व्योम aपंचांगci_detect_change(काष्ठा समयr_list *t)
अणु
	काष्ठा aपंचांगel_mci_slot	*slot = from_समयr(slot, t, detect_समयr);
	bool			present;
	bool			present_old;

	/*
	 * aपंचांगci_cleanup_slot() sets the ATMCI_SHUTDOWN flag beक्रमe
	 * मुक्तing the पूर्णांकerrupt. We must not re-enable the पूर्णांकerrupt
	 * अगर it has been मुक्तd, and अगर we're shutting करोwn, it
	 * करोesn't really matter whether the card is present or not.
	 */
	smp_rmb();
	अगर (test_bit(ATMCI_SHUTDOWN, &slot->flags))
		वापस;

	enable_irq(gpio_to_irq(slot->detect_pin));
	present = !(gpio_get_value(slot->detect_pin) ^
		    slot->detect_is_active_high);
	present_old = test_bit(ATMCI_CARD_PRESENT, &slot->flags);

	dev_vdbg(&slot->mmc->class_dev, "detect change: %d (was %d)\n",
			present, present_old);

	अगर (present != present_old) अणु
		काष्ठा aपंचांगel_mci	*host = slot->host;
		काष्ठा mmc_request	*mrq;

		dev_dbg(&slot->mmc->class_dev, "card %s\n",
			present ? "inserted" : "removed");

		spin_lock(&host->lock);

		अगर (!present)
			clear_bit(ATMCI_CARD_PRESENT, &slot->flags);
		अन्यथा
			set_bit(ATMCI_CARD_PRESENT, &slot->flags);

		/* Clean up queue अगर present */
		mrq = slot->mrq;
		अगर (mrq) अणु
			अगर (mrq == host->mrq) अणु
				/*
				 * Reset controller to terminate any ongoing
				 * commands or data transfers.
				 */
				aपंचांगci_ग_लिखोl(host, ATMCI_CR, ATMCI_CR_SWRST);
				aपंचांगci_ग_लिखोl(host, ATMCI_CR, ATMCI_CR_MCIEN);
				aपंचांगci_ग_लिखोl(host, ATMCI_MR, host->mode_reg);
				अगर (host->caps.has_cfg_reg)
					aपंचांगci_ग_लिखोl(host, ATMCI_CFG, host->cfg_reg);

				host->data = शून्य;
				host->cmd = शून्य;

				चयन (host->state) अणु
				हाल STATE_IDLE:
					अवरोध;
				हाल STATE_SENDING_CMD:
					mrq->cmd->error = -ENOMEDIUM;
					अगर (mrq->data)
						host->stop_transfer(host);
					अवरोध;
				हाल STATE_DATA_XFER:
					mrq->data->error = -ENOMEDIUM;
					host->stop_transfer(host);
					अवरोध;
				हाल STATE_WAITING_NOTBUSY:
					mrq->data->error = -ENOMEDIUM;
					अवरोध;
				हाल STATE_SENDING_STOP:
					mrq->stop->error = -ENOMEDIUM;
					अवरोध;
				हाल STATE_END_REQUEST:
					अवरोध;
				पूर्ण

				aपंचांगci_request_end(host, mrq);
			पूर्ण अन्यथा अणु
				list_del(&slot->queue_node);
				mrq->cmd->error = -ENOMEDIUM;
				अगर (mrq->data)
					mrq->data->error = -ENOMEDIUM;
				अगर (mrq->stop)
					mrq->stop->error = -ENOMEDIUM;

				spin_unlock(&host->lock);
				mmc_request_करोne(slot->mmc, mrq);
				spin_lock(&host->lock);
			पूर्ण
		पूर्ण
		spin_unlock(&host->lock);

		mmc_detect_change(slot->mmc, 0);
	पूर्ण
पूर्ण

अटल व्योम aपंचांगci_tasklet_func(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा aपंचांगel_mci        *host = from_tasklet(host, t, tasklet);
	काष्ठा mmc_request	*mrq = host->mrq;
	काष्ठा mmc_data		*data = host->data;
	क्रमागत aपंचांगel_mci_state	state = host->state;
	क्रमागत aपंचांगel_mci_state	prev_state;
	u32			status;

	spin_lock(&host->lock);

	state = host->state;

	dev_vdbg(&host->pdev->dev,
		"tasklet: state %u pending/completed/mask %lx/%lx/%x\n",
		state, host->pending_events, host->completed_events,
		aपंचांगci_पढ़ोl(host, ATMCI_IMR));

	करो अणु
		prev_state = state;
		dev_dbg(&host->pdev->dev, "FSM: state=%d\n", state);

		चयन (state) अणु
		हाल STATE_IDLE:
			अवरोध;

		हाल STATE_SENDING_CMD:
			/*
			 * Command has been sent, we are रुकोing क्रम command
			 * पढ़ोy. Then we have three next states possible:
			 * END_REQUEST by शेष, WAITING_NOTBUSY अगर it's a
			 * command needing it or DATA_XFER अगर there is data.
			 */
			dev_dbg(&host->pdev->dev, "FSM: cmd ready?\n");
			अगर (!aपंचांगci_test_and_clear_pending(host,
						EVENT_CMD_RDY))
				अवरोध;

			dev_dbg(&host->pdev->dev, "set completed cmd ready\n");
			host->cmd = शून्य;
			aपंचांगci_set_completed(host, EVENT_CMD_RDY);
			aपंचांगci_command_complete(host, mrq->cmd);
			अगर (mrq->data) अणु
				dev_dbg(&host->pdev->dev,
				        "command with data transfer");
				/*
				 * If there is a command error करोn't start
				 * data transfer.
				 */
				अगर (mrq->cmd->error) अणु
					host->stop_transfer(host);
					host->data = शून्य;
					aपंचांगci_ग_लिखोl(host, ATMCI_IDR,
					             ATMCI_TXRDY | ATMCI_RXRDY
					             | ATMCI_DATA_ERROR_FLAGS);
					state = STATE_END_REQUEST;
				पूर्ण अन्यथा
					state = STATE_DATA_XFER;
			पूर्ण अन्यथा अगर ((!mrq->data) && (mrq->cmd->flags & MMC_RSP_BUSY)) अणु
				dev_dbg(&host->pdev->dev,
				        "command response need waiting notbusy");
				aपंचांगci_ग_लिखोl(host, ATMCI_IER, ATMCI_NOTBUSY);
				state = STATE_WAITING_NOTBUSY;
			पूर्ण अन्यथा
				state = STATE_END_REQUEST;

			अवरोध;

		हाल STATE_DATA_XFER:
			अगर (aपंचांगci_test_and_clear_pending(host,
						EVENT_DATA_ERROR)) अणु
				dev_dbg(&host->pdev->dev, "set completed data error\n");
				aपंचांगci_set_completed(host, EVENT_DATA_ERROR);
				state = STATE_END_REQUEST;
				अवरोध;
			पूर्ण

			/*
			 * A data transfer is in progress. The event expected
			 * to move to the next state depends of data transfer
			 * type (PDC or DMA). Once transfer करोne we can move
			 * to the next step which is WAITING_NOTBUSY in ग_लिखो
			 * हाल and directly SENDING_STOP in पढ़ो हाल.
			 */
			dev_dbg(&host->pdev->dev, "FSM: xfer complete?\n");
			अगर (!aपंचांगci_test_and_clear_pending(host,
						EVENT_XFER_COMPLETE))
				अवरोध;

			dev_dbg(&host->pdev->dev,
			        "(%s) set completed xfer complete\n",
				__func__);
			aपंचांगci_set_completed(host, EVENT_XFER_COMPLETE);

			अगर (host->caps.need_notbusy_क्रम_पढ़ो_ops ||
			   (host->data->flags & MMC_DATA_WRITE)) अणु
				aपंचांगci_ग_लिखोl(host, ATMCI_IER, ATMCI_NOTBUSY);
				state = STATE_WAITING_NOTBUSY;
			पूर्ण अन्यथा अगर (host->mrq->stop) अणु
				aपंचांगci_ग_लिखोl(host, ATMCI_IER, ATMCI_CMDRDY);
				aपंचांगci_send_stop_cmd(host, data);
				state = STATE_SENDING_STOP;
			पूर्ण अन्यथा अणु
				host->data = शून्य;
				data->bytes_xfered = data->blocks * data->blksz;
				data->error = 0;
				state = STATE_END_REQUEST;
			पूर्ण
			अवरोध;

		हाल STATE_WAITING_NOTBUSY:
			/*
			 * We can be in the state क्रम two reasons: a command
			 * requiring रुकोing not busy संकेत (stop command
			 * included) or a ग_लिखो operation. In the latest हाल,
			 * we need to send a stop command.
			 */
			dev_dbg(&host->pdev->dev, "FSM: not busy?\n");
			अगर (!aपंचांगci_test_and_clear_pending(host,
						EVENT_NOTBUSY))
				अवरोध;

			dev_dbg(&host->pdev->dev, "set completed not busy\n");
			aपंचांगci_set_completed(host, EVENT_NOTBUSY);

			अगर (host->data) अणु
				/*
				 * For some commands such as CMD53, even अगर
				 * there is data transfer, there is no stop
				 * command to send.
				 */
				अगर (host->mrq->stop) अणु
					aपंचांगci_ग_लिखोl(host, ATMCI_IER,
					             ATMCI_CMDRDY);
					aपंचांगci_send_stop_cmd(host, data);
					state = STATE_SENDING_STOP;
				पूर्ण अन्यथा अणु
					host->data = शून्य;
					data->bytes_xfered = data->blocks
					                     * data->blksz;
					data->error = 0;
					state = STATE_END_REQUEST;
				पूर्ण
			पूर्ण अन्यथा
				state = STATE_END_REQUEST;
			अवरोध;

		हाल STATE_SENDING_STOP:
			/*
			 * In this state, it is important to set host->data to
			 * शून्य (which is tested in the रुकोing notbusy state)
			 * in order to go to the end request state instead of
			 * sending stop again.
			 */
			dev_dbg(&host->pdev->dev, "FSM: cmd ready?\n");
			अगर (!aपंचांगci_test_and_clear_pending(host,
						EVENT_CMD_RDY))
				अवरोध;

			dev_dbg(&host->pdev->dev, "FSM: cmd ready\n");
			host->cmd = शून्य;
			data->bytes_xfered = data->blocks * data->blksz;
			data->error = 0;
			aपंचांगci_command_complete(host, mrq->stop);
			अगर (mrq->stop->error) अणु
				host->stop_transfer(host);
				aपंचांगci_ग_लिखोl(host, ATMCI_IDR,
				             ATMCI_TXRDY | ATMCI_RXRDY
				             | ATMCI_DATA_ERROR_FLAGS);
				state = STATE_END_REQUEST;
			पूर्ण अन्यथा अणु
				aपंचांगci_ग_लिखोl(host, ATMCI_IER, ATMCI_NOTBUSY);
				state = STATE_WAITING_NOTBUSY;
			पूर्ण
			host->data = शून्य;
			अवरोध;

		हाल STATE_END_REQUEST:
			aपंचांगci_ग_लिखोl(host, ATMCI_IDR, ATMCI_TXRDY | ATMCI_RXRDY
			                   | ATMCI_DATA_ERROR_FLAGS);
			status = host->data_status;
			अगर (unlikely(status)) अणु
				host->stop_transfer(host);
				host->data = शून्य;
				अगर (data) अणु
					अगर (status & ATMCI_DTOE) अणु
						data->error = -ETIMEDOUT;
					पूर्ण अन्यथा अगर (status & ATMCI_DCRCE) अणु
						data->error = -EILSEQ;
					पूर्ण अन्यथा अणु
						data->error = -EIO;
					पूर्ण
				पूर्ण
			पूर्ण

			aपंचांगci_request_end(host, host->mrq);
			जाओ unlock; /* aपंचांगci_request_end() sets host->state */
			अवरोध;
		पूर्ण
	पूर्ण जबतक (state != prev_state);

	host->state = state;

unlock:
	spin_unlock(&host->lock);
पूर्ण

अटल व्योम aपंचांगci_पढ़ो_data_pio(काष्ठा aपंचांगel_mci *host)
अणु
	काष्ठा scatterlist	*sg = host->sg;
	अचिन्हित पूर्णांक		offset = host->pio_offset;
	काष्ठा mmc_data		*data = host->data;
	u32			value;
	u32			status;
	अचिन्हित पूर्णांक		nbytes = 0;

	करो अणु
		value = aपंचांगci_पढ़ोl(host, ATMCI_RDR);
		अगर (likely(offset + 4 <= sg->length)) अणु
			sg_pcopy_from_buffer(sg, 1, &value, माप(u32), offset);

			offset += 4;
			nbytes += 4;

			अगर (offset == sg->length) अणु
				flush_dcache_page(sg_page(sg));
				host->sg = sg = sg_next(sg);
				host->sg_len--;
				अगर (!sg || !host->sg_len)
					जाओ करोne;

				offset = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			अचिन्हित पूर्णांक reमुख्यing = sg->length - offset;

			sg_pcopy_from_buffer(sg, 1, &value, reमुख्यing, offset);
			nbytes += reमुख्यing;

			flush_dcache_page(sg_page(sg));
			host->sg = sg = sg_next(sg);
			host->sg_len--;
			अगर (!sg || !host->sg_len)
				जाओ करोne;

			offset = 4 - reमुख्यing;
			sg_pcopy_from_buffer(sg, 1, (u8 *)&value + reमुख्यing,
					offset, 0);
			nbytes += offset;
		पूर्ण

		status = aपंचांगci_पढ़ोl(host, ATMCI_SR);
		अगर (status & ATMCI_DATA_ERROR_FLAGS) अणु
			aपंचांगci_ग_लिखोl(host, ATMCI_IDR, (ATMCI_NOTBUSY | ATMCI_RXRDY
						| ATMCI_DATA_ERROR_FLAGS));
			host->data_status = status;
			data->bytes_xfered += nbytes;
			वापस;
		पूर्ण
	पूर्ण जबतक (status & ATMCI_RXRDY);

	host->pio_offset = offset;
	data->bytes_xfered += nbytes;

	वापस;

करोne:
	aपंचांगci_ग_लिखोl(host, ATMCI_IDR, ATMCI_RXRDY);
	aपंचांगci_ग_लिखोl(host, ATMCI_IER, ATMCI_NOTBUSY);
	data->bytes_xfered += nbytes;
	smp_wmb();
	aपंचांगci_set_pending(host, EVENT_XFER_COMPLETE);
पूर्ण

अटल व्योम aपंचांगci_ग_लिखो_data_pio(काष्ठा aपंचांगel_mci *host)
अणु
	काष्ठा scatterlist	*sg = host->sg;
	अचिन्हित पूर्णांक		offset = host->pio_offset;
	काष्ठा mmc_data		*data = host->data;
	u32			value;
	u32			status;
	अचिन्हित पूर्णांक		nbytes = 0;

	करो अणु
		अगर (likely(offset + 4 <= sg->length)) अणु
			sg_pcopy_to_buffer(sg, 1, &value, माप(u32), offset);
			aपंचांगci_ग_लिखोl(host, ATMCI_TDR, value);

			offset += 4;
			nbytes += 4;
			अगर (offset == sg->length) अणु
				host->sg = sg = sg_next(sg);
				host->sg_len--;
				अगर (!sg || !host->sg_len)
					जाओ करोne;

				offset = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			अचिन्हित पूर्णांक reमुख्यing = sg->length - offset;

			value = 0;
			sg_pcopy_to_buffer(sg, 1, &value, reमुख्यing, offset);
			nbytes += reमुख्यing;

			host->sg = sg = sg_next(sg);
			host->sg_len--;
			अगर (!sg || !host->sg_len) अणु
				aपंचांगci_ग_लिखोl(host, ATMCI_TDR, value);
				जाओ करोne;
			पूर्ण

			offset = 4 - reमुख्यing;
			sg_pcopy_to_buffer(sg, 1, (u8 *)&value + reमुख्यing,
					offset, 0);
			aपंचांगci_ग_लिखोl(host, ATMCI_TDR, value);
			nbytes += offset;
		पूर्ण

		status = aपंचांगci_पढ़ोl(host, ATMCI_SR);
		अगर (status & ATMCI_DATA_ERROR_FLAGS) अणु
			aपंचांगci_ग_लिखोl(host, ATMCI_IDR, (ATMCI_NOTBUSY | ATMCI_TXRDY
						| ATMCI_DATA_ERROR_FLAGS));
			host->data_status = status;
			data->bytes_xfered += nbytes;
			वापस;
		पूर्ण
	पूर्ण जबतक (status & ATMCI_TXRDY);

	host->pio_offset = offset;
	data->bytes_xfered += nbytes;

	वापस;

करोne:
	aपंचांगci_ग_लिखोl(host, ATMCI_IDR, ATMCI_TXRDY);
	aपंचांगci_ग_लिखोl(host, ATMCI_IER, ATMCI_NOTBUSY);
	data->bytes_xfered += nbytes;
	smp_wmb();
	aपंचांगci_set_pending(host, EVENT_XFER_COMPLETE);
पूर्ण

अटल व्योम aपंचांगci_sdio_पूर्णांकerrupt(काष्ठा aपंचांगel_mci *host, u32 status)
अणु
	पूर्णांक	i;

	क्रम (i = 0; i < ATMCI_MAX_NR_SLOTS; i++) अणु
		काष्ठा aपंचांगel_mci_slot *slot = host->slot[i];
		अगर (slot && (status & slot->sdio_irq)) अणु
			mmc_संकेत_sdio_irq(slot->mmc);
		पूर्ण
	पूर्ण
पूर्ण


अटल irqवापस_t aपंचांगci_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा aपंचांगel_mci	*host = dev_id;
	u32			status, mask, pending;
	अचिन्हित पूर्णांक		pass_count = 0;

	करो अणु
		status = aपंचांगci_पढ़ोl(host, ATMCI_SR);
		mask = aपंचांगci_पढ़ोl(host, ATMCI_IMR);
		pending = status & mask;
		अगर (!pending)
			अवरोध;

		अगर (pending & ATMCI_DATA_ERROR_FLAGS) अणु
			dev_dbg(&host->pdev->dev, "IRQ: data error\n");
			aपंचांगci_ग_लिखोl(host, ATMCI_IDR, ATMCI_DATA_ERROR_FLAGS
					| ATMCI_RXRDY | ATMCI_TXRDY
					| ATMCI_ENDRX | ATMCI_ENDTX
					| ATMCI_RXBUFF | ATMCI_TXBUFE);

			host->data_status = status;
			dev_dbg(&host->pdev->dev, "set pending data error\n");
			smp_wmb();
			aपंचांगci_set_pending(host, EVENT_DATA_ERROR);
			tasklet_schedule(&host->tasklet);
		पूर्ण

		अगर (pending & ATMCI_TXBUFE) अणु
			dev_dbg(&host->pdev->dev, "IRQ: tx buffer empty\n");
			aपंचांगci_ग_लिखोl(host, ATMCI_IDR, ATMCI_TXBUFE);
			aपंचांगci_ग_लिखोl(host, ATMCI_IDR, ATMCI_ENDTX);
			/*
			 * We can receive this पूर्णांकerruption beक्रमe having configured
			 * the second pdc buffer, so we need to reconfigure first and
			 * second buffers again
			 */
			अगर (host->data_size) अणु
				aपंचांगci_pdc_set_both_buf(host, XFER_TRANSMIT);
				aपंचांगci_ग_लिखोl(host, ATMCI_IER, ATMCI_ENDTX);
				aपंचांगci_ग_लिखोl(host, ATMCI_IER, ATMCI_TXBUFE);
			पूर्ण अन्यथा अणु
				aपंचांगci_pdc_complete(host);
			पूर्ण
		पूर्ण अन्यथा अगर (pending & ATMCI_ENDTX) अणु
			dev_dbg(&host->pdev->dev, "IRQ: end of tx buffer\n");
			aपंचांगci_ग_लिखोl(host, ATMCI_IDR, ATMCI_ENDTX);

			अगर (host->data_size) अणु
				aपंचांगci_pdc_set_single_buf(host,
						XFER_TRANSMIT, PDC_SECOND_BUF);
				aपंचांगci_ग_लिखोl(host, ATMCI_IER, ATMCI_ENDTX);
			पूर्ण
		पूर्ण

		अगर (pending & ATMCI_RXBUFF) अणु
			dev_dbg(&host->pdev->dev, "IRQ: rx buffer full\n");
			aपंचांगci_ग_लिखोl(host, ATMCI_IDR, ATMCI_RXBUFF);
			aपंचांगci_ग_लिखोl(host, ATMCI_IDR, ATMCI_ENDRX);
			/*
			 * We can receive this पूर्णांकerruption beक्रमe having configured
			 * the second pdc buffer, so we need to reconfigure first and
			 * second buffers again
			 */
			अगर (host->data_size) अणु
				aपंचांगci_pdc_set_both_buf(host, XFER_RECEIVE);
				aपंचांगci_ग_लिखोl(host, ATMCI_IER, ATMCI_ENDRX);
				aपंचांगci_ग_लिखोl(host, ATMCI_IER, ATMCI_RXBUFF);
			पूर्ण अन्यथा अणु
				aपंचांगci_pdc_complete(host);
			पूर्ण
		पूर्ण अन्यथा अगर (pending & ATMCI_ENDRX) अणु
			dev_dbg(&host->pdev->dev, "IRQ: end of rx buffer\n");
			aपंचांगci_ग_लिखोl(host, ATMCI_IDR, ATMCI_ENDRX);

			अगर (host->data_size) अणु
				aपंचांगci_pdc_set_single_buf(host,
						XFER_RECEIVE, PDC_SECOND_BUF);
				aपंचांगci_ग_लिखोl(host, ATMCI_IER, ATMCI_ENDRX);
			पूर्ण
		पूर्ण

		/*
		 * First mci IPs, so मुख्यly the ones having pdc, have some
		 * issues with the notbusy संकेत. You can't get it after
		 * data transmission अगर you have not sent a stop command.
		 * The appropriate workaround is to use the BLKE संकेत.
		 */
		अगर (pending & ATMCI_BLKE) अणु
			dev_dbg(&host->pdev->dev, "IRQ: blke\n");
			aपंचांगci_ग_लिखोl(host, ATMCI_IDR, ATMCI_BLKE);
			smp_wmb();
			dev_dbg(&host->pdev->dev, "set pending notbusy\n");
			aपंचांगci_set_pending(host, EVENT_NOTBUSY);
			tasklet_schedule(&host->tasklet);
		पूर्ण

		अगर (pending & ATMCI_NOTBUSY) अणु
			dev_dbg(&host->pdev->dev, "IRQ: not_busy\n");
			aपंचांगci_ग_लिखोl(host, ATMCI_IDR, ATMCI_NOTBUSY);
			smp_wmb();
			dev_dbg(&host->pdev->dev, "set pending notbusy\n");
			aपंचांगci_set_pending(host, EVENT_NOTBUSY);
			tasklet_schedule(&host->tasklet);
		पूर्ण

		अगर (pending & ATMCI_RXRDY)
			aपंचांगci_पढ़ो_data_pio(host);
		अगर (pending & ATMCI_TXRDY)
			aपंचांगci_ग_लिखो_data_pio(host);

		अगर (pending & ATMCI_CMDRDY) अणु
			dev_dbg(&host->pdev->dev, "IRQ: cmd ready\n");
			aपंचांगci_ग_लिखोl(host, ATMCI_IDR, ATMCI_CMDRDY);
			host->cmd_status = status;
			smp_wmb();
			dev_dbg(&host->pdev->dev, "set pending cmd rdy\n");
			aपंचांगci_set_pending(host, EVENT_CMD_RDY);
			tasklet_schedule(&host->tasklet);
		पूर्ण

		अगर (pending & (ATMCI_SDIOIRQA | ATMCI_SDIOIRQB))
			aपंचांगci_sdio_पूर्णांकerrupt(host, status);

	पूर्ण जबतक (pass_count++ < 5);

	वापस pass_count ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल irqवापस_t aपंचांगci_detect_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा aपंचांगel_mci_slot	*slot = dev_id;

	/*
	 * Disable पूर्णांकerrupts until the pin has stabilized and check
	 * the state then. Use mod_समयr() since we may be in the
	 * middle of the समयr routine when this पूर्णांकerrupt triggers.
	 */
	disable_irq_nosync(irq);
	mod_समयr(&slot->detect_समयr, jअगरfies + msecs_to_jअगरfies(20));

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक aपंचांगci_init_slot(काष्ठा aपंचांगel_mci *host,
		काष्ठा mci_slot_pdata *slot_data, अचिन्हित पूर्णांक id,
		u32 sdc_reg, u32 sdio_irq)
अणु
	काष्ठा mmc_host			*mmc;
	काष्ठा aपंचांगel_mci_slot		*slot;

	mmc = mmc_alloc_host(माप(काष्ठा aपंचांगel_mci_slot), &host->pdev->dev);
	अगर (!mmc)
		वापस -ENOMEM;

	slot = mmc_priv(mmc);
	slot->mmc = mmc;
	slot->host = host;
	slot->detect_pin = slot_data->detect_pin;
	slot->wp_pin = slot_data->wp_pin;
	slot->detect_is_active_high = slot_data->detect_is_active_high;
	slot->sdc_reg = sdc_reg;
	slot->sdio_irq = sdio_irq;

	dev_dbg(&mmc->class_dev,
	        "slot[%u]: bus_width=%u, detect_pin=%d, "
		"detect_is_active_high=%s, wp_pin=%d\n",
		id, slot_data->bus_width, slot_data->detect_pin,
		slot_data->detect_is_active_high ? "true" : "false",
		slot_data->wp_pin);

	mmc->ops = &aपंचांगci_ops;
	mmc->f_min = DIV_ROUND_UP(host->bus_hz, 512);
	mmc->f_max = host->bus_hz / 2;
	mmc->ocr_avail	= MMC_VDD_32_33 | MMC_VDD_33_34;
	अगर (sdio_irq)
		mmc->caps |= MMC_CAP_SDIO_IRQ;
	अगर (host->caps.has_highspeed)
		mmc->caps |= MMC_CAP_SD_HIGHSPEED;
	/*
	 * Without the पढ़ो/ग_लिखो proof capability, it is strongly suggested to
	 * use only one bit क्रम data to prevent fअगरo underruns and overruns
	 * which will corrupt data.
	 */
	अगर ((slot_data->bus_width >= 4) && host->caps.has_rwproof) अणु
		mmc->caps |= MMC_CAP_4_BIT_DATA;
		अगर (slot_data->bus_width >= 8)
			mmc->caps |= MMC_CAP_8_BIT_DATA;
	पूर्ण

	अगर (aपंचांगci_get_version(host) < 0x200) अणु
		mmc->max_segs = 256;
		mmc->max_blk_size = 4095;
		mmc->max_blk_count = 256;
		mmc->max_req_size = mmc->max_blk_size * mmc->max_blk_count;
		mmc->max_seg_size = mmc->max_blk_size * mmc->max_segs;
	पूर्ण अन्यथा अणु
		mmc->max_segs = 64;
		mmc->max_req_size = 32768 * 512;
		mmc->max_blk_size = 32768;
		mmc->max_blk_count = 512;
	पूर्ण

	/* Assume card is present initially */
	set_bit(ATMCI_CARD_PRESENT, &slot->flags);
	अगर (gpio_is_valid(slot->detect_pin)) अणु
		अगर (devm_gpio_request(&host->pdev->dev, slot->detect_pin,
				      "mmc_detect")) अणु
			dev_dbg(&mmc->class_dev, "no detect pin available\n");
			slot->detect_pin = -EBUSY;
		पूर्ण अन्यथा अगर (gpio_get_value(slot->detect_pin) ^
				slot->detect_is_active_high) अणु
			clear_bit(ATMCI_CARD_PRESENT, &slot->flags);
		पूर्ण
	पूर्ण

	अगर (!gpio_is_valid(slot->detect_pin)) अणु
		अगर (slot_data->non_removable)
			mmc->caps |= MMC_CAP_NONREMOVABLE;
		अन्यथा
			mmc->caps |= MMC_CAP_NEEDS_POLL;
	पूर्ण

	अगर (gpio_is_valid(slot->wp_pin)) अणु
		अगर (devm_gpio_request(&host->pdev->dev, slot->wp_pin,
				      "mmc_wp")) अणु
			dev_dbg(&mmc->class_dev, "no WP pin available\n");
			slot->wp_pin = -EBUSY;
		पूर्ण
	पूर्ण

	host->slot[id] = slot;
	mmc_regulator_get_supply(mmc);
	mmc_add_host(mmc);

	अगर (gpio_is_valid(slot->detect_pin)) अणु
		पूर्णांक ret;

		समयr_setup(&slot->detect_समयr, aपंचांगci_detect_change, 0);

		ret = request_irq(gpio_to_irq(slot->detect_pin),
				aपंचांगci_detect_पूर्णांकerrupt,
				IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING,
				"mmc-detect", slot);
		अगर (ret) अणु
			dev_dbg(&mmc->class_dev,
				"could not request IRQ %d for detect pin\n",
				gpio_to_irq(slot->detect_pin));
			slot->detect_pin = -EBUSY;
		पूर्ण
	पूर्ण

	aपंचांगci_init_debugfs(slot);

	वापस 0;
पूर्ण

अटल व्योम aपंचांगci_cleanup_slot(काष्ठा aपंचांगel_mci_slot *slot,
		अचिन्हित पूर्णांक id)
अणु
	/* Debugfs stuff is cleaned up by mmc core */

	set_bit(ATMCI_SHUTDOWN, &slot->flags);
	smp_wmb();

	mmc_हटाओ_host(slot->mmc);

	अगर (gpio_is_valid(slot->detect_pin)) अणु
		पूर्णांक pin = slot->detect_pin;

		मुक्त_irq(gpio_to_irq(pin), slot);
		del_समयr_sync(&slot->detect_समयr);
	पूर्ण

	slot->host->slot[id] = शून्य;
	mmc_मुक्त_host(slot->mmc);
पूर्ण

अटल पूर्णांक aपंचांगci_configure_dma(काष्ठा aपंचांगel_mci *host)
अणु
	host->dma.chan = dma_request_chan(&host->pdev->dev, "rxtx");

	अगर (PTR_ERR(host->dma.chan) == -ENODEV) अणु
		काष्ठा mci_platक्रमm_data *pdata = host->pdev->dev.platक्रमm_data;
		dma_cap_mask_t mask;

		अगर (!pdata || !pdata->dma_filter)
			वापस -ENODEV;

		dma_cap_zero(mask);
		dma_cap_set(DMA_SLAVE, mask);

		host->dma.chan = dma_request_channel(mask, pdata->dma_filter,
						     pdata->dma_slave);
		अगर (!host->dma.chan)
			host->dma.chan = ERR_PTR(-ENODEV);
	पूर्ण

	अगर (IS_ERR(host->dma.chan))
		वापस PTR_ERR(host->dma.chan);

	dev_info(&host->pdev->dev, "using %s for DMA transfers\n",
		 dma_chan_name(host->dma.chan));

	host->dma_conf.src_addr = host->mapbase + ATMCI_RDR;
	host->dma_conf.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	host->dma_conf.src_maxburst = 1;
	host->dma_conf.dst_addr = host->mapbase + ATMCI_TDR;
	host->dma_conf.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	host->dma_conf.dst_maxburst = 1;
	host->dma_conf.device_fc = false;

	वापस 0;
पूर्ण

/*
 * HSMCI (High Speed MCI) module is not fully compatible with MCI module.
 * HSMCI provides DMA support and a new config रेजिस्टर but no more supports
 * PDC.
 */
अटल व्योम aपंचांगci_get_cap(काष्ठा aपंचांगel_mci *host)
अणु
	अचिन्हित पूर्णांक version;

	version = aपंचांगci_get_version(host);
	dev_info(&host->pdev->dev,
			"version: 0x%x\n", version);

	host->caps.has_dma_conf_reg = false;
	host->caps.has_pdc = true;
	host->caps.has_cfg_reg = false;
	host->caps.has_cstor_reg = false;
	host->caps.has_highspeed = false;
	host->caps.has_rwproof = false;
	host->caps.has_odd_clk_भाग = false;
	host->caps.has_bad_data_ordering = true;
	host->caps.need_reset_after_xfer = true;
	host->caps.need_blksz_mul_4 = true;
	host->caps.need_notbusy_क्रम_पढ़ो_ops = false;

	/* keep only major version number */
	चयन (version & 0xf00) अणु
	हाल 0x600:
	हाल 0x500:
		host->caps.has_odd_clk_भाग = true;
		fallthrough;
	हाल 0x400:
	हाल 0x300:
		host->caps.has_dma_conf_reg = true;
		host->caps.has_pdc = false;
		host->caps.has_cfg_reg = true;
		host->caps.has_cstor_reg = true;
		host->caps.has_highspeed = true;
		fallthrough;
	हाल 0x200:
		host->caps.has_rwproof = true;
		host->caps.need_blksz_mul_4 = false;
		host->caps.need_notbusy_क्रम_पढ़ो_ops = true;
		fallthrough;
	हाल 0x100:
		host->caps.has_bad_data_ordering = false;
		host->caps.need_reset_after_xfer = false;
		fallthrough;
	हाल 0x0:
		अवरोध;
	शेष:
		host->caps.has_pdc = false;
		dev_warn(&host->pdev->dev,
				"Unmanaged mci version, set minimum capabilities\n");
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक aपंचांगci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mci_platक्रमm_data	*pdata;
	काष्ठा aपंचांगel_mci		*host;
	काष्ठा resource			*regs;
	अचिन्हित पूर्णांक			nr_slots;
	पूर्णांक				irq;
	पूर्णांक				ret, i;

	regs = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!regs)
		वापस -ENXIO;
	pdata = pdev->dev.platक्रमm_data;
	अगर (!pdata) अणु
		pdata = aपंचांगci_of_init(pdev);
		अगर (IS_ERR(pdata)) अणु
			dev_err(&pdev->dev, "platform data not available\n");
			वापस PTR_ERR(pdata);
		पूर्ण
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	host = devm_kzalloc(&pdev->dev, माप(*host), GFP_KERNEL);
	अगर (!host)
		वापस -ENOMEM;

	host->pdev = pdev;
	spin_lock_init(&host->lock);
	INIT_LIST_HEAD(&host->queue);

	host->mck = devm_clk_get(&pdev->dev, "mci_clk");
	अगर (IS_ERR(host->mck))
		वापस PTR_ERR(host->mck);

	host->regs = devm_ioremap(&pdev->dev, regs->start, resource_size(regs));
	अगर (!host->regs)
		वापस -ENOMEM;

	ret = clk_prepare_enable(host->mck);
	अगर (ret)
		वापस ret;

	aपंचांगci_ग_लिखोl(host, ATMCI_CR, ATMCI_CR_SWRST);
	host->bus_hz = clk_get_rate(host->mck);

	host->mapbase = regs->start;

	tasklet_setup(&host->tasklet, aपंचांगci_tasklet_func);

	ret = request_irq(irq, aपंचांगci_पूर्णांकerrupt, 0, dev_name(&pdev->dev), host);
	अगर (ret) अणु
		clk_disable_unprepare(host->mck);
		वापस ret;
	पूर्ण

	/* Get MCI capabilities and set operations according to it */
	aपंचांगci_get_cap(host);
	ret = aपंचांगci_configure_dma(host);
	अगर (ret == -EPROBE_DEFER)
		जाओ err_dma_probe_defer;
	अगर (ret == 0) अणु
		host->prepare_data = &aपंचांगci_prepare_data_dma;
		host->submit_data = &aपंचांगci_submit_data_dma;
		host->stop_transfer = &aपंचांगci_stop_transfer_dma;
	पूर्ण अन्यथा अगर (host->caps.has_pdc) अणु
		dev_info(&pdev->dev, "using PDC\n");
		host->prepare_data = &aपंचांगci_prepare_data_pdc;
		host->submit_data = &aपंचांगci_submit_data_pdc;
		host->stop_transfer = &aपंचांगci_stop_transfer_pdc;
	पूर्ण अन्यथा अणु
		dev_info(&pdev->dev, "using PIO\n");
		host->prepare_data = &aपंचांगci_prepare_data;
		host->submit_data = &aपंचांगci_submit_data;
		host->stop_transfer = &aपंचांगci_stop_transfer;
	पूर्ण

	platक्रमm_set_drvdata(pdev, host);

	समयr_setup(&host->समयr, aपंचांगci_समयout_समयr, 0);

	pm_runसमय_get_noresume(&pdev->dev);
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, AUTOSUSPEND_DELAY);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	/* We need at least one slot to succeed */
	nr_slots = 0;
	ret = -ENODEV;
	अगर (pdata->slot[0].bus_width) अणु
		ret = aपंचांगci_init_slot(host, &pdata->slot[0],
				0, ATMCI_SDCSEL_SLOT_A, ATMCI_SDIOIRQA);
		अगर (!ret) अणु
			nr_slots++;
			host->buf_size = host->slot[0]->mmc->max_req_size;
		पूर्ण
	पूर्ण
	अगर (pdata->slot[1].bus_width) अणु
		ret = aपंचांगci_init_slot(host, &pdata->slot[1],
				1, ATMCI_SDCSEL_SLOT_B, ATMCI_SDIOIRQB);
		अगर (!ret) अणु
			nr_slots++;
			अगर (host->slot[1]->mmc->max_req_size > host->buf_size)
				host->buf_size =
					host->slot[1]->mmc->max_req_size;
		पूर्ण
	पूर्ण

	अगर (!nr_slots) अणु
		dev_err(&pdev->dev, "init failed: no slot defined\n");
		जाओ err_init_slot;
	पूर्ण

	अगर (!host->caps.has_rwproof) अणु
		host->buffer = dma_alloc_coherent(&pdev->dev, host->buf_size,
		                                  &host->buf_phys_addr,
						  GFP_KERNEL);
		अगर (!host->buffer) अणु
			ret = -ENOMEM;
			dev_err(&pdev->dev, "buffer allocation failed\n");
			जाओ err_dma_alloc;
		पूर्ण
	पूर्ण

	dev_info(&pdev->dev,
			"Atmel MCI controller at 0x%08lx irq %d, %u slots\n",
			host->mapbase, irq, nr_slots);

	pm_runसमय_mark_last_busy(&host->pdev->dev);
	pm_runसमय_put_स्वतःsuspend(&pdev->dev);

	वापस 0;

err_dma_alloc:
	क्रम (i = 0; i < ATMCI_MAX_NR_SLOTS; i++) अणु
		अगर (host->slot[i])
			aपंचांगci_cleanup_slot(host->slot[i], i);
	पूर्ण
err_init_slot:
	clk_disable_unprepare(host->mck);

	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_put_noidle(&pdev->dev);

	del_समयr_sync(&host->समयr);
	अगर (!IS_ERR(host->dma.chan))
		dma_release_channel(host->dma.chan);
err_dma_probe_defer:
	मुक्त_irq(irq, host);
	वापस ret;
पूर्ण

अटल पूर्णांक aपंचांगci_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aपंचांगel_mci	*host = platक्रमm_get_drvdata(pdev);
	अचिन्हित पूर्णांक		i;

	pm_runसमय_get_sync(&pdev->dev);

	अगर (host->buffer)
		dma_मुक्त_coherent(&pdev->dev, host->buf_size,
		                  host->buffer, host->buf_phys_addr);

	क्रम (i = 0; i < ATMCI_MAX_NR_SLOTS; i++) अणु
		अगर (host->slot[i])
			aपंचांगci_cleanup_slot(host->slot[i], i);
	पूर्ण

	aपंचांगci_ग_लिखोl(host, ATMCI_IDR, ~0UL);
	aपंचांगci_ग_लिखोl(host, ATMCI_CR, ATMCI_CR_MCIDIS);
	aपंचांगci_पढ़ोl(host, ATMCI_SR);

	del_समयr_sync(&host->समयr);
	अगर (!IS_ERR(host->dma.chan))
		dma_release_channel(host->dma.chan);

	मुक्त_irq(platक्रमm_get_irq(pdev, 0), host);

	clk_disable_unprepare(host->mck);

	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_put_noidle(&pdev->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक aपंचांगci_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा aपंचांगel_mci *host = dev_get_drvdata(dev);

	clk_disable_unprepare(host->mck);

	pinctrl_pm_select_sleep_state(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगci_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा aपंचांगel_mci *host = dev_get_drvdata(dev);

	pinctrl_select_शेष_state(dev);

	वापस clk_prepare_enable(host->mck);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops aपंचांगci_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(aपंचांगci_runसमय_suspend, aपंचांगci_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver aपंचांगci_driver = अणु
	.probe		= aपंचांगci_probe,
	.हटाओ		= aपंचांगci_हटाओ,
	.driver		= अणु
		.name		= "atmel_mci",
		.probe_type	= PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table	= of_match_ptr(aपंचांगci_dt_ids),
		.pm		= &aपंचांगci_dev_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(aपंचांगci_driver);

MODULE_DESCRIPTION("Atmel Multimedia Card Interface driver");
MODULE_AUTHOR("Haavard Skinnemoen (Atmel)");
MODULE_LICENSE("GPL v2");
