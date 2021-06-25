<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Synopsys DesignWare Mulसमयdia Card Interface driver
 *  (Based on NXP driver क्रम lpc 31xx)
 *
 * Copyright (C) 2009 NXP Semiconductors
 * Copyright (C) 2009, 2010 Imagination Technologies Ltd.
 */

#अगर_अघोषित _DW_MMC_H_
#घोषणा _DW_MMC_H_

#समावेश <linux/scatterlist.h>
#समावेश <linux/mmc/core.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/reset.h>
#समावेश <linux/पूर्णांकerrupt.h>

क्रमागत dw_mci_state अणु
	STATE_IDLE = 0,
	STATE_SENDING_CMD,
	STATE_SENDING_DATA,
	STATE_DATA_BUSY,
	STATE_SENDING_STOP,
	STATE_DATA_ERROR,
	STATE_SENDING_CMD11,
	STATE_WAITING_CMD11_DONE,
पूर्ण;

क्रमागत अणु
	EVENT_CMD_COMPLETE = 0,
	EVENT_XFER_COMPLETE,
	EVENT_DATA_COMPLETE,
	EVENT_DATA_ERROR,
पूर्ण;

क्रमागत dw_mci_cookie अणु
	COOKIE_UNMAPPED,
	COOKIE_PRE_MAPPED,	/* mapped by pre_req() of dwmmc */
	COOKIE_MAPPED,		/* mapped by prepare_data() of dwmmc */
पूर्ण;

काष्ठा mmc_data;

क्रमागत अणु
	TRANS_MODE_PIO = 0,
	TRANS_MODE_IDMAC,
	TRANS_MODE_EDMAC
पूर्ण;

काष्ठा dw_mci_dma_slave अणु
	काष्ठा dma_chan *ch;
	क्रमागत dma_transfer_direction direction;
पूर्ण;

/**
 * काष्ठा dw_mci - MMC controller state shared between all slots
 * @lock: Spinlock protecting the queue and associated data.
 * @irq_lock: Spinlock protecting the INTMASK setting.
 * @regs: Poपूर्णांकer to MMIO रेजिस्टरs.
 * @fअगरo_reg: Poपूर्णांकer to MMIO रेजिस्टरs क्रम data FIFO
 * @sg: Scatterlist entry currently being processed by PIO code, अगर any.
 * @sg_miter: PIO mapping scatterlist iterator.
 * @mrq: The request currently being processed on @slot,
 *	or शून्य अगर the controller is idle.
 * @cmd: The command currently being sent to the card, or शून्य.
 * @data: The data currently being transferred, or शून्य अगर no data
 *	transfer is in progress.
 * @stop_पात: The command currently prepared क्रम stoping transfer.
 * @prev_blksz: The क्रमmer transfer blksz record.
 * @timing: Record of current ios timing.
 * @use_dma: Which DMA channel is in use क्रम the current transfer, zero
 *	denotes PIO mode.
 * @using_dma: Whether DMA is in use क्रम the current transfer.
 * @dma_64bit_address: Whether DMA supports 64-bit address mode or not.
 * @sg_dma: Bus address of DMA buffer.
 * @sg_cpu: Virtual address of DMA buffer.
 * @dma_ops: Poपूर्णांकer to platक्रमm-specअगरic DMA callbacks.
 * @cmd_status: Snapshot of SR taken upon completion of the current
 * @ring_size: Buffer size क्रम idma descriptors.
 *	command. Only valid when EVENT_CMD_COMPLETE is pending.
 * @dms: काष्ठाure of slave-dma निजी data.
 * @phy_regs: physical address of controller's रेजिस्टर map
 * @data_status: Snapshot of SR taken upon completion of the current
 *	data transfer. Only valid when EVENT_DATA_COMPLETE or
 *	EVENT_DATA_ERROR is pending.
 * @stop_cmdr: Value to be loaded पूर्णांकo CMDR when the stop command is
 *	to be sent.
 * @dir_status: Direction of current transfer.
 * @tasklet: Tasklet running the request state machine.
 * @pending_events: Biपंचांगask of events flagged by the पूर्णांकerrupt handler
 *	to be processed by the tasklet.
 * @completed_events: Biपंचांगask of events which the state machine has
 *	processed.
 * @state: Tasklet state.
 * @queue: List of slots रुकोing क्रम access to the controller.
 * @bus_hz: The rate of @mck in Hz. This क्रमms the basis क्रम MMC bus
 *	rate and समयout calculations.
 * @current_speed: Configured rate of the controller.
 * @fअगरoth_val: The value of FIFOTH रेजिस्टर.
 * @verid: Denote Version ID.
 * @dev: Device associated with the MMC controller.
 * @pdata: Platक्रमm data associated with the MMC controller.
 * @drv_data: Driver specअगरic data क्रम identअगरied variant of the controller
 * @priv: Implementation defined निजी data.
 * @biu_clk: Poपूर्णांकer to bus पूर्णांकerface unit घड़ी instance.
 * @ciu_clk: Poपूर्णांकer to card पूर्णांकerface unit घड़ी instance.
 * @slot: Slots sharing this MMC controller.
 * @fअगरo_depth: depth of FIFO.
 * @data_addr_override: override fअगरo reg offset with this value.
 * @wm_aligned: क्रमce fअगरo watermark equal with data length in PIO mode.
 *	Set as true अगर alignment is needed.
 * @data_shअगरt: log2 of FIFO item size.
 * @part_buf_start: Start index in part_buf.
 * @part_buf_count: Bytes of partial data in part_buf.
 * @part_buf: Simple buffer क्रम partial fअगरo पढ़ोs/ग_लिखोs.
 * @push_data: Poपूर्णांकer to FIFO push function.
 * @pull_data: Poपूर्णांकer to FIFO pull function.
 * @vqmmc_enabled: Status of vqmmc, should be true or false.
 * @irq_flags: The flags to be passed to request_irq.
 * @irq: The irq value to be passed to request_irq.
 * @sdio_id0: Number of slot0 in the SDIO पूर्णांकerrupt रेजिस्टरs.
 * @cmd11_समयr: Timer क्रम SD3.0 voltage चयन over scheme.
 * @cto_समयr: Timer क्रम broken command transfer over scheme.
 * @dto_समयr: Timer क्रम broken data transfer over scheme.
 *
 * Locking
 * =======
 *
 * @lock is a softirq-safe spinlock protecting @queue as well as
 * @slot, @mrq and @state. These must always be updated
 * at the same समय जबतक holding @lock.
 * The @mrq field of काष्ठा dw_mci_slot is also रक्षित by @lock,
 * and must always be written at the same समय as the slot is added to
 * @queue.
 *
 * @irq_lock is an irq-safe spinlock protecting the INTMASK रेजिस्टर
 * to allow the पूर्णांकerrupt handler to modअगरy it directly.  Held क्रम only दीर्घ
 * enough to पढ़ो-modअगरy-ग_लिखो INTMASK and no other locks are grabbed when
 * holding this one.
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
काष्ठा dw_mci अणु
	spinlock_t		lock;
	spinlock_t		irq_lock;
	व्योम __iomem		*regs;
	व्योम __iomem		*fअगरo_reg;
	u32			data_addr_override;
	bool			wm_aligned;

	काष्ठा scatterlist	*sg;
	काष्ठा sg_mapping_iter	sg_miter;

	काष्ठा mmc_request	*mrq;
	काष्ठा mmc_command	*cmd;
	काष्ठा mmc_data		*data;
	काष्ठा mmc_command	stop_पात;
	अचिन्हित पूर्णांक		prev_blksz;
	अचिन्हित अक्षर		timing;

	/* DMA पूर्णांकerface members*/
	पूर्णांक			use_dma;
	पूर्णांक			using_dma;
	पूर्णांक			dma_64bit_address;

	dma_addr_t		sg_dma;
	व्योम			*sg_cpu;
	स्थिर काष्ठा dw_mci_dma_ops	*dma_ops;
	/* For idmac */
	अचिन्हित पूर्णांक		ring_size;

	/* For edmac */
	काष्ठा dw_mci_dma_slave *dms;
	/* Registers's physical base address */
	resource_माप_प्रकार		phy_regs;

	u32			cmd_status;
	u32			data_status;
	u32			stop_cmdr;
	u32			dir_status;
	काष्ठा tasklet_काष्ठा	tasklet;
	अचिन्हित दीर्घ		pending_events;
	अचिन्हित दीर्घ		completed_events;
	क्रमागत dw_mci_state	state;
	काष्ठा list_head	queue;

	u32			bus_hz;
	u32			current_speed;
	u32			fअगरoth_val;
	u16			verid;
	काष्ठा device		*dev;
	काष्ठा dw_mci_board	*pdata;
	स्थिर काष्ठा dw_mci_drv_data	*drv_data;
	व्योम			*priv;
	काष्ठा clk		*biu_clk;
	काष्ठा clk		*ciu_clk;
	काष्ठा dw_mci_slot	*slot;

	/* FIFO push and pull */
	पूर्णांक			fअगरo_depth;
	पूर्णांक			data_shअगरt;
	u8			part_buf_start;
	u8			part_buf_count;
	जोड़ अणु
		u16		part_buf16;
		u32		part_buf32;
		u64		part_buf;
	पूर्ण;
	व्योम (*push_data)(काष्ठा dw_mci *host, व्योम *buf, पूर्णांक cnt);
	व्योम (*pull_data)(काष्ठा dw_mci *host, व्योम *buf, पूर्णांक cnt);

	bool			vqmmc_enabled;
	अचिन्हित दीर्घ		irq_flags; /* IRQ flags */
	पूर्णांक			irq;

	पूर्णांक			sdio_id0;

	काष्ठा समयr_list       cmd11_समयr;
	काष्ठा समयr_list       cto_समयr;
	काष्ठा समयr_list       dto_समयr;
पूर्ण;

/* DMA ops क्रम Internal/External DMAC पूर्णांकerface */
काष्ठा dw_mci_dma_ops अणु
	/* DMA Ops */
	पूर्णांक (*init)(काष्ठा dw_mci *host);
	पूर्णांक (*start)(काष्ठा dw_mci *host, अचिन्हित पूर्णांक sg_len);
	व्योम (*complete)(व्योम *host);
	व्योम (*stop)(काष्ठा dw_mci *host);
	व्योम (*cleanup)(काष्ठा dw_mci *host);
	व्योम (*निकास)(काष्ठा dw_mci *host);
पूर्ण;

काष्ठा dma_pdata;

/* Board platक्रमm data */
काष्ठा dw_mci_board अणु
	अचिन्हित पूर्णांक bus_hz; /* Clock speed at the cclk_in pad */

	u32 caps;	/* Capabilities */
	u32 caps2;	/* More capabilities */
	u32 pm_caps;	/* PM capabilities */
	/*
	 * Override fअगरo depth. If 0, स्वतःdetect it from the FIFOTH रेजिस्टर,
	 * but note that this may not be reliable after a bootloader has used
	 * it.
	 */
	अचिन्हित पूर्णांक fअगरo_depth;

	/* delay in mS beक्रमe detecting cards after पूर्णांकerrupt */
	u32 detect_delay_ms;

	काष्ठा reset_control *rstc;
	काष्ठा dw_mci_dma_ops *dma_ops;
	काष्ठा dma_pdata *data;
पूर्ण;

#घोषणा DW_MMC_240A		0x240a
#घोषणा DW_MMC_280A		0x280a

#घोषणा SDMMC_CTRL		0x000
#घोषणा SDMMC_PWREN		0x004
#घोषणा SDMMC_CLKDIV		0x008
#घोषणा SDMMC_CLKSRC		0x00c
#घोषणा SDMMC_CLKENA		0x010
#घोषणा SDMMC_TMOUT		0x014
#घोषणा SDMMC_CTYPE		0x018
#घोषणा SDMMC_BLKSIZ		0x01c
#घोषणा SDMMC_BYTCNT		0x020
#घोषणा SDMMC_INTMASK		0x024
#घोषणा SDMMC_CMDARG		0x028
#घोषणा SDMMC_CMD		0x02c
#घोषणा SDMMC_RESP0		0x030
#घोषणा SDMMC_RESP1		0x034
#घोषणा SDMMC_RESP2		0x038
#घोषणा SDMMC_RESP3		0x03c
#घोषणा SDMMC_MINTSTS		0x040
#घोषणा SDMMC_RINTSTS		0x044
#घोषणा SDMMC_STATUS		0x048
#घोषणा SDMMC_FIFOTH		0x04c
#घोषणा SDMMC_CDETECT		0x050
#घोषणा SDMMC_WRTPRT		0x054
#घोषणा SDMMC_GPIO		0x058
#घोषणा SDMMC_TCBCNT		0x05c
#घोषणा SDMMC_TBBCNT		0x060
#घोषणा SDMMC_DEBNCE		0x064
#घोषणा SDMMC_USRID		0x068
#घोषणा SDMMC_VERID		0x06c
#घोषणा SDMMC_HCON		0x070
#घोषणा SDMMC_UHS_REG		0x074
#घोषणा SDMMC_RST_N		0x078
#घोषणा SDMMC_BMOD		0x080
#घोषणा SDMMC_PLDMND		0x084
#घोषणा SDMMC_DBADDR		0x088
#घोषणा SDMMC_IDSTS		0x08c
#घोषणा SDMMC_IDINTEN		0x090
#घोषणा SDMMC_DSCADDR		0x094
#घोषणा SDMMC_BUFADDR		0x098
#घोषणा SDMMC_CDTHRCTL		0x100
#घोषणा SDMMC_UHS_REG_EXT	0x108
#घोषणा SDMMC_DDR_REG		0x10c
#घोषणा SDMMC_ENABLE_SHIFT	0x110
#घोषणा SDMMC_DATA(x)		(x)
/*
 * Registers to support idmac 64-bit address mode
 */
#घोषणा SDMMC_DBADDRL		0x088
#घोषणा SDMMC_DBADDRU		0x08c
#घोषणा SDMMC_IDSTS64		0x090
#घोषणा SDMMC_IDINTEN64		0x094
#घोषणा SDMMC_DSCADDRL		0x098
#घोषणा SDMMC_DSCADDRU		0x09c
#घोषणा SDMMC_BUFADDRL		0x0A0
#घोषणा SDMMC_BUFADDRU		0x0A4

/*
 * Data offset is dअगरference according to Version
 * Lower than 2.40a : data रेजिस्टर offest is 0x100
 */
#घोषणा DATA_OFFSET		0x100
#घोषणा DATA_240A_OFFSET	0x200

/* shअगरt bit field */
#घोषणा _SBF(f, v)		((v) << (f))

/* Control रेजिस्टर defines */
#घोषणा SDMMC_CTRL_USE_IDMAC		BIT(25)
#घोषणा SDMMC_CTRL_CEATA_INT_EN		BIT(11)
#घोषणा SDMMC_CTRL_SEND_AS_CCSD		BIT(10)
#घोषणा SDMMC_CTRL_SEND_CCSD		BIT(9)
#घोषणा SDMMC_CTRL_ABRT_READ_DATA	BIT(8)
#घोषणा SDMMC_CTRL_SEND_IRQ_RESP	BIT(7)
#घोषणा SDMMC_CTRL_READ_WAIT		BIT(6)
#घोषणा SDMMC_CTRL_DMA_ENABLE		BIT(5)
#घोषणा SDMMC_CTRL_INT_ENABLE		BIT(4)
#घोषणा SDMMC_CTRL_DMA_RESET		BIT(2)
#घोषणा SDMMC_CTRL_FIFO_RESET		BIT(1)
#घोषणा SDMMC_CTRL_RESET		BIT(0)
/* Clock Enable रेजिस्टर defines */
#घोषणा SDMMC_CLKEN_LOW_PWR		BIT(16)
#घोषणा SDMMC_CLKEN_ENABLE		BIT(0)
/* समय-out रेजिस्टर defines */
#घोषणा SDMMC_TMOUT_DATA(n)		_SBF(8, (n))
#घोषणा SDMMC_TMOUT_DATA_MSK		0xFFFFFF00
#घोषणा SDMMC_TMOUT_RESP(n)		((n) & 0xFF)
#घोषणा SDMMC_TMOUT_RESP_MSK		0xFF
/* card-type रेजिस्टर defines */
#घोषणा SDMMC_CTYPE_8BIT		BIT(16)
#घोषणा SDMMC_CTYPE_4BIT		BIT(0)
#घोषणा SDMMC_CTYPE_1BIT		0
/* Interrupt status & mask रेजिस्टर defines */
#घोषणा SDMMC_INT_SDIO(n)		BIT(16 + (n))
#घोषणा SDMMC_INT_EBE			BIT(15)
#घोषणा SDMMC_INT_ACD			BIT(14)
#घोषणा SDMMC_INT_SBE			BIT(13)
#घोषणा SDMMC_INT_HLE			BIT(12)
#घोषणा SDMMC_INT_FRUN			BIT(11)
#घोषणा SDMMC_INT_HTO			BIT(10)
#घोषणा SDMMC_INT_VOLT_SWITCH		BIT(10) /* overloads bit 10! */
#घोषणा SDMMC_INT_DRTO			BIT(9)
#घोषणा SDMMC_INT_RTO			BIT(8)
#घोषणा SDMMC_INT_DCRC			BIT(7)
#घोषणा SDMMC_INT_RCRC			BIT(6)
#घोषणा SDMMC_INT_RXDR			BIT(5)
#घोषणा SDMMC_INT_TXDR			BIT(4)
#घोषणा SDMMC_INT_DATA_OVER		BIT(3)
#घोषणा SDMMC_INT_CMD_DONE		BIT(2)
#घोषणा SDMMC_INT_RESP_ERR		BIT(1)
#घोषणा SDMMC_INT_CD			BIT(0)
#घोषणा SDMMC_INT_ERROR			0xbfc2
/* Command रेजिस्टर defines */
#घोषणा SDMMC_CMD_START			BIT(31)
#घोषणा SDMMC_CMD_USE_HOLD_REG	BIT(29)
#घोषणा SDMMC_CMD_VOLT_SWITCH		BIT(28)
#घोषणा SDMMC_CMD_CCS_EXP		BIT(23)
#घोषणा SDMMC_CMD_CEATA_RD		BIT(22)
#घोषणा SDMMC_CMD_UPD_CLK		BIT(21)
#घोषणा SDMMC_CMD_INIT			BIT(15)
#घोषणा SDMMC_CMD_STOP			BIT(14)
#घोषणा SDMMC_CMD_PRV_DAT_WAIT		BIT(13)
#घोषणा SDMMC_CMD_SEND_STOP		BIT(12)
#घोषणा SDMMC_CMD_STRM_MODE		BIT(11)
#घोषणा SDMMC_CMD_DAT_WR		BIT(10)
#घोषणा SDMMC_CMD_DAT_EXP		BIT(9)
#घोषणा SDMMC_CMD_RESP_CRC		BIT(8)
#घोषणा SDMMC_CMD_RESP_LONG		BIT(7)
#घोषणा SDMMC_CMD_RESP_EXP		BIT(6)
#घोषणा SDMMC_CMD_INDX(n)		((n) & 0x1F)
/* Status रेजिस्टर defines */
#घोषणा SDMMC_GET_FCNT(x)		(((x)>>17) & 0x1FFF)
#घोषणा SDMMC_STATUS_DMA_REQ		BIT(31)
#घोषणा SDMMC_STATUS_BUSY		BIT(9)
/* FIFOTH रेजिस्टर defines */
#घोषणा SDMMC_SET_FIFOTH(m, r, t)	(((m) & 0x7) << 28 | \
					 ((r) & 0xFFF) << 16 | \
					 ((t) & 0xFFF))
/* HCON रेजिस्टर defines */
#घोषणा DMA_INTERFACE_IDMA		(0x0)
#घोषणा DMA_INTERFACE_DWDMA		(0x1)
#घोषणा DMA_INTERFACE_GDMA		(0x2)
#घोषणा DMA_INTERFACE_NODMA		(0x3)
#घोषणा SDMMC_GET_TRANS_MODE(x)		(((x)>>16) & 0x3)
#घोषणा SDMMC_GET_SLOT_NUM(x)		((((x)>>1) & 0x1F) + 1)
#घोषणा SDMMC_GET_HDATA_WIDTH(x)	(((x)>>7) & 0x7)
#घोषणा SDMMC_GET_ADDR_CONFIG(x)	(((x)>>27) & 0x1)
/* Internal DMAC पूर्णांकerrupt defines */
#घोषणा SDMMC_IDMAC_INT_AI		BIT(9)
#घोषणा SDMMC_IDMAC_INT_NI		BIT(8)
#घोषणा SDMMC_IDMAC_INT_CES		BIT(5)
#घोषणा SDMMC_IDMAC_INT_DU		BIT(4)
#घोषणा SDMMC_IDMAC_INT_FBE		BIT(2)
#घोषणा SDMMC_IDMAC_INT_RI		BIT(1)
#घोषणा SDMMC_IDMAC_INT_TI		BIT(0)
/* Internal DMAC bus mode bits */
#घोषणा SDMMC_IDMAC_ENABLE		BIT(7)
#घोषणा SDMMC_IDMAC_FB			BIT(1)
#घोषणा SDMMC_IDMAC_SWRESET		BIT(0)
/* H/W reset */
#घोषणा SDMMC_RST_HWACTIVE		0x1
/* Version ID रेजिस्टर define */
#घोषणा SDMMC_GET_VERID(x)		((x) & 0xFFFF)
/* Card पढ़ो threshold */
#घोषणा SDMMC_SET_THLD(v, x)		(((v) & 0xFFF) << 16 | (x))
#घोषणा SDMMC_CARD_WR_THR_EN		BIT(2)
#घोषणा SDMMC_CARD_RD_THR_EN		BIT(0)
/* UHS-1 रेजिस्टर defines */
#घोषणा SDMMC_UHS_DDR			BIT(16)
#घोषणा SDMMC_UHS_18V			BIT(0)
/* DDR रेजिस्टर defines */
#घोषणा SDMMC_DDR_HS400			BIT(31)
/* Enable shअगरt रेजिस्टर defines */
#घोषणा SDMMC_ENABLE_PHASE		BIT(0)
/* All ctrl reset bits */
#घोषणा SDMMC_CTRL_ALL_RESET_FLAGS \
	(SDMMC_CTRL_RESET | SDMMC_CTRL_FIFO_RESET | SDMMC_CTRL_DMA_RESET)

/* FIFO रेजिस्टर access macros. These should not change the data endian-ness
 * as they are written to memory to be dealt with by the upper layers
 */
#घोषणा mci_fअगरo_पढ़ोw(__reg)	__raw_पढ़ोw(__reg)
#घोषणा mci_fअगरo_पढ़ोl(__reg)	__raw_पढ़ोl(__reg)
#घोषणा mci_fअगरo_पढ़ोq(__reg)	__raw_पढ़ोq(__reg)

#घोषणा mci_fअगरo_ग_लिखोw(__value, __reg)	__raw_ग_लिखोw(__reg, __value)
#घोषणा mci_fअगरo_ग_लिखोl(__value, __reg)	__raw_ग_लिखोl(__reg, __value)
#घोषणा mci_fअगरo_ग_लिखोq(__value, __reg)	__raw_ग_लिखोq(__reg, __value)

/* Register access macros */
#घोषणा mci_पढ़ोl(dev, reg)			\
	पढ़ोl_relaxed((dev)->regs + SDMMC_##reg)
#घोषणा mci_ग_लिखोl(dev, reg, value)			\
	ग_लिखोl_relaxed((value), (dev)->regs + SDMMC_##reg)

/* 16-bit FIFO access macros */
#घोषणा mci_पढ़ोw(dev, reg)			\
	पढ़ोw_relaxed((dev)->regs + SDMMC_##reg)
#घोषणा mci_ग_लिखोw(dev, reg, value)			\
	ग_लिखोw_relaxed((value), (dev)->regs + SDMMC_##reg)

/* 64-bit FIFO access macros */
#अगर_घोषित पढ़ोq
#घोषणा mci_पढ़ोq(dev, reg)			\
	पढ़ोq_relaxed((dev)->regs + SDMMC_##reg)
#घोषणा mci_ग_लिखोq(dev, reg, value)			\
	ग_लिखोq_relaxed((value), (dev)->regs + SDMMC_##reg)
#अन्यथा
/*
 * Dummy पढ़ोq implementation क्रम architectures that करोn't define it.
 *
 * We would assume that none of these architectures would configure
 * the IP block with a 64bit FIFO width, so this code will never be
 * executed on those machines. Defining these macros here keeps the
 * rest of the code मुक्त from अगरdefs.
 */
#घोषणा mci_पढ़ोq(dev, reg)			\
	(*(अस्थिर u64 __क्रमce *)((dev)->regs + SDMMC_##reg))
#घोषणा mci_ग_लिखोq(dev, reg, value)			\
	(*(अस्थिर u64 __क्रमce *)((dev)->regs + SDMMC_##reg) = (value))

#घोषणा __raw_ग_लिखोq(__value, __reg) \
	(*(अस्थिर u64 __क्रमce *)(__reg) = (__value))
#घोषणा __raw_पढ़ोq(__reg) (*(अस्थिर u64 __क्रमce *)(__reg))
#पूर्ण_अगर

बाह्य पूर्णांक dw_mci_probe(काष्ठा dw_mci *host);
बाह्य व्योम dw_mci_हटाओ(काष्ठा dw_mci *host);
#अगर_घोषित CONFIG_PM
बाह्य पूर्णांक dw_mci_runसमय_suspend(काष्ठा device *device);
बाह्य पूर्णांक dw_mci_runसमय_resume(काष्ठा device *device);
#पूर्ण_अगर

/**
 * काष्ठा dw_mci_slot - MMC slot state
 * @mmc: The mmc_host representing this slot.
 * @host: The MMC controller this slot is using.
 * @ctype: Card type क्रम this slot.
 * @mrq: mmc_request currently being processed or रुकोing to be
 *	processed, or शून्य when the slot is idle.
 * @queue_node: List node क्रम placing this node in the @queue list of
 *	&काष्ठा dw_mci.
 * @घड़ी: Clock rate configured by set_ios(). Protected by host->lock.
 * @__clk_old: The last घड़ी value that was requested from core.
 *	Keeping track of this helps us to aव्योम spamming the console.
 * @flags: Ranकरोm state bits associated with the slot.
 * @id: Number of this slot.
 * @sdio_id: Number of this slot in the SDIO पूर्णांकerrupt रेजिस्टरs.
 */
काष्ठा dw_mci_slot अणु
	काष्ठा mmc_host		*mmc;
	काष्ठा dw_mci		*host;

	u32			ctype;

	काष्ठा mmc_request	*mrq;
	काष्ठा list_head	queue_node;

	अचिन्हित पूर्णांक		घड़ी;
	अचिन्हित पूर्णांक		__clk_old;

	अचिन्हित दीर्घ		flags;
#घोषणा DW_MMC_CARD_PRESENT	0
#घोषणा DW_MMC_CARD_NEED_INIT	1
#घोषणा DW_MMC_CARD_NO_LOW_PWR	2
#घोषणा DW_MMC_CARD_NO_USE_HOLD 3
#घोषणा DW_MMC_CARD_NEEDS_POLL	4
	पूर्णांक			id;
	पूर्णांक			sdio_id;
पूर्ण;

/**
 * dw_mci driver data - dw-mshc implementation specअगरic driver data.
 * @caps: mmc subप्रणाली specअगरied capabilities of the controller(s).
 * @num_caps: number of capabilities specअगरied by @caps.
 * @init: early implementation specअगरic initialization.
 * @set_ios: handle bus specअगरic extensions.
 * @parse_dt: parse implementation specअगरic device tree properties.
 * @execute_tuning: implementation specअगरic tuning procedure.
 *
 * Provide controller implementation specअगरic extensions. The usage of this
 * data काष्ठाure is fully optional and usage of each member in this काष्ठाure
 * is optional as well.
 */
काष्ठा dw_mci_drv_data अणु
	अचिन्हित दीर्घ	*caps;
	u32		num_caps;
	पूर्णांक		(*init)(काष्ठा dw_mci *host);
	व्योम		(*set_ios)(काष्ठा dw_mci *host, काष्ठा mmc_ios *ios);
	पूर्णांक		(*parse_dt)(काष्ठा dw_mci *host);
	पूर्णांक		(*execute_tuning)(काष्ठा dw_mci_slot *slot, u32 opcode);
	पूर्णांक		(*prepare_hs400_tuning)(काष्ठा dw_mci *host,
						काष्ठा mmc_ios *ios);
	पूर्णांक		(*चयन_voltage)(काष्ठा mmc_host *mmc,
					  काष्ठा mmc_ios *ios);
पूर्ण;
#पूर्ण_अगर /* _DW_MMC_H_ */
