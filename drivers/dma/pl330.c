<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Copyright (C) 2010 Samsung Electronics Co. Ltd.
 *	Jaswinder Singh <jassi.brar@samsung.com>
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/amba/bus.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/of.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/err.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/bug.h>
#समावेश <linux/reset.h>

#समावेश "dmaengine.h"
#घोषणा PL330_MAX_CHAN		8
#घोषणा PL330_MAX_IRQS		32
#घोषणा PL330_MAX_PERI		32
#घोषणा PL330_MAX_BURST         16

#घोषणा PL330_QUIRK_BROKEN_NO_FLUSHP	BIT(0)
#घोषणा PL330_QUIRK_PERIPH_BURST	BIT(1)

क्रमागत pl330_cachectrl अणु
	CCTRL0,		/* Noncacheable and nonbufferable */
	CCTRL1,		/* Bufferable only */
	CCTRL2,		/* Cacheable, but करो not allocate */
	CCTRL3,		/* Cacheable and bufferable, but करो not allocate */
	INVALID1,	/* AWCACHE = 0x1000 */
	INVALID2,
	CCTRL6,		/* Cacheable ग_लिखो-through, allocate on ग_लिखोs only */
	CCTRL7,		/* Cacheable ग_लिखो-back, allocate on ग_लिखोs only */
पूर्ण;

क्रमागत pl330_byteswap अणु
	SWAP_NO,
	SWAP_2,
	SWAP_4,
	SWAP_8,
	SWAP_16,
पूर्ण;

/* Register and Bit field Definitions */
#घोषणा DS			0x0
#घोषणा DS_ST_STOP		0x0
#घोषणा DS_ST_EXEC		0x1
#घोषणा DS_ST_CMISS		0x2
#घोषणा DS_ST_UPDTPC		0x3
#घोषणा DS_ST_WFE		0x4
#घोषणा DS_ST_ATBRR		0x5
#घोषणा DS_ST_QBUSY		0x6
#घोषणा DS_ST_WFP		0x7
#घोषणा DS_ST_KILL		0x8
#घोषणा DS_ST_CMPLT		0x9
#घोषणा DS_ST_FLTCMP		0xe
#घोषणा DS_ST_FAULT		0xf

#घोषणा DPC			0x4
#घोषणा INTEN			0x20
#घोषणा ES			0x24
#घोषणा INTSTATUS		0x28
#घोषणा INTCLR			0x2c
#घोषणा FSM			0x30
#घोषणा FSC			0x34
#घोषणा FTM			0x38

#घोषणा _FTC			0x40
#घोषणा FTC(n)			(_FTC + (n)*0x4)

#घोषणा _CS			0x100
#घोषणा CS(n)			(_CS + (n)*0x8)
#घोषणा CS_CNS			(1 << 21)

#घोषणा _CPC			0x104
#घोषणा CPC(n)			(_CPC + (n)*0x8)

#घोषणा _SA			0x400
#घोषणा SA(n)			(_SA + (n)*0x20)

#घोषणा _DA			0x404
#घोषणा DA(n)			(_DA + (n)*0x20)

#घोषणा _CC			0x408
#घोषणा CC(n)			(_CC + (n)*0x20)

#घोषणा CC_SRCINC		(1 << 0)
#घोषणा CC_DSTINC		(1 << 14)
#घोषणा CC_SRCPRI		(1 << 8)
#घोषणा CC_DSTPRI		(1 << 22)
#घोषणा CC_SRCNS		(1 << 9)
#घोषणा CC_DSTNS		(1 << 23)
#घोषणा CC_SRCIA		(1 << 10)
#घोषणा CC_DSTIA		(1 << 24)
#घोषणा CC_SRCBRSTLEN_SHFT	4
#घोषणा CC_DSTBRSTLEN_SHFT	18
#घोषणा CC_SRCBRSTSIZE_SHFT	1
#घोषणा CC_DSTBRSTSIZE_SHFT	15
#घोषणा CC_SRCCCTRL_SHFT	11
#घोषणा CC_SRCCCTRL_MASK	0x7
#घोषणा CC_DSTCCTRL_SHFT	25
#घोषणा CC_DRCCCTRL_MASK	0x7
#घोषणा CC_SWAP_SHFT		28

#घोषणा _LC0			0x40c
#घोषणा LC0(n)			(_LC0 + (n)*0x20)

#घोषणा _LC1			0x410
#घोषणा LC1(n)			(_LC1 + (n)*0x20)

#घोषणा DBGSTATUS		0xd00
#घोषणा DBG_BUSY		(1 << 0)

#घोषणा DBGCMD			0xd04
#घोषणा DBGINST0		0xd08
#घोषणा DBGINST1		0xd0c

#घोषणा CR0			0xe00
#घोषणा CR1			0xe04
#घोषणा CR2			0xe08
#घोषणा CR3			0xe0c
#घोषणा CR4			0xe10
#घोषणा CRD			0xe14

#घोषणा PERIPH_ID		0xfe0
#घोषणा PERIPH_REV_SHIFT	20
#घोषणा PERIPH_REV_MASK		0xf
#घोषणा PERIPH_REV_R0P0		0
#घोषणा PERIPH_REV_R1P0		1
#घोषणा PERIPH_REV_R1P1		2

#घोषणा CR0_PERIPH_REQ_SET	(1 << 0)
#घोषणा CR0_BOOT_EN_SET		(1 << 1)
#घोषणा CR0_BOOT_MAN_NS		(1 << 2)
#घोषणा CR0_NUM_CHANS_SHIFT	4
#घोषणा CR0_NUM_CHANS_MASK	0x7
#घोषणा CR0_NUM_PERIPH_SHIFT	12
#घोषणा CR0_NUM_PERIPH_MASK	0x1f
#घोषणा CR0_NUM_EVENTS_SHIFT	17
#घोषणा CR0_NUM_EVENTS_MASK	0x1f

#घोषणा CR1_ICACHE_LEN_SHIFT	0
#घोषणा CR1_ICACHE_LEN_MASK	0x7
#घोषणा CR1_NUM_ICACHELINES_SHIFT	4
#घोषणा CR1_NUM_ICACHELINES_MASK	0xf

#घोषणा CRD_DATA_WIDTH_SHIFT	0
#घोषणा CRD_DATA_WIDTH_MASK	0x7
#घोषणा CRD_WR_CAP_SHIFT	4
#घोषणा CRD_WR_CAP_MASK		0x7
#घोषणा CRD_WR_Q_DEP_SHIFT	8
#घोषणा CRD_WR_Q_DEP_MASK	0xf
#घोषणा CRD_RD_CAP_SHIFT	12
#घोषणा CRD_RD_CAP_MASK		0x7
#घोषणा CRD_RD_Q_DEP_SHIFT	16
#घोषणा CRD_RD_Q_DEP_MASK	0xf
#घोषणा CRD_DATA_BUFF_SHIFT	20
#घोषणा CRD_DATA_BUFF_MASK	0x3ff

#घोषणा PART			0x330
#घोषणा DESIGNER		0x41
#घोषणा REVISION		0x0
#घोषणा INTEG_CFG		0x0
#घोषणा PERIPH_ID_VAL		((PART << 0) | (DESIGNER << 12))

#घोषणा PL330_STATE_STOPPED		(1 << 0)
#घोषणा PL330_STATE_EXECUTING		(1 << 1)
#घोषणा PL330_STATE_WFE			(1 << 2)
#घोषणा PL330_STATE_FAULTING		(1 << 3)
#घोषणा PL330_STATE_COMPLETING		(1 << 4)
#घोषणा PL330_STATE_WFP			(1 << 5)
#घोषणा PL330_STATE_KILLING		(1 << 6)
#घोषणा PL330_STATE_FAULT_COMPLETING	(1 << 7)
#घोषणा PL330_STATE_CACHEMISS		(1 << 8)
#घोषणा PL330_STATE_UPDTPC		(1 << 9)
#घोषणा PL330_STATE_ATBARRIER		(1 << 10)
#घोषणा PL330_STATE_QUEUEBUSY		(1 << 11)
#घोषणा PL330_STATE_INVALID		(1 << 15)

#घोषणा PL330_STABLE_STATES (PL330_STATE_STOPPED | PL330_STATE_EXECUTING \
				| PL330_STATE_WFE | PL330_STATE_FAULTING)

#घोषणा CMD_DMAADDH		0x54
#घोषणा CMD_DMAEND		0x00
#घोषणा CMD_DMAFLUSHP		0x35
#घोषणा CMD_DMAGO		0xa0
#घोषणा CMD_DMALD		0x04
#घोषणा CMD_DMALDP		0x25
#घोषणा CMD_DMALP		0x20
#घोषणा CMD_DMALPEND		0x28
#घोषणा CMD_DMAKILL		0x01
#घोषणा CMD_DMAMOV		0xbc
#घोषणा CMD_DMANOP		0x18
#घोषणा CMD_DMARMB		0x12
#घोषणा CMD_DMASEV		0x34
#घोषणा CMD_DMAST		0x08
#घोषणा CMD_DMASTP		0x29
#घोषणा CMD_DMASTZ		0x0c
#घोषणा CMD_DMAWFE		0x36
#घोषणा CMD_DMAWFP		0x30
#घोषणा CMD_DMAWMB		0x13

#घोषणा SZ_DMAADDH		3
#घोषणा SZ_DMAEND		1
#घोषणा SZ_DMAFLUSHP		2
#घोषणा SZ_DMALD		1
#घोषणा SZ_DMALDP		2
#घोषणा SZ_DMALP		2
#घोषणा SZ_DMALPEND		2
#घोषणा SZ_DMAKILL		1
#घोषणा SZ_DMAMOV		6
#घोषणा SZ_DMANOP		1
#घोषणा SZ_DMARMB		1
#घोषणा SZ_DMASEV		2
#घोषणा SZ_DMAST		1
#घोषणा SZ_DMASTP		2
#घोषणा SZ_DMASTZ		1
#घोषणा SZ_DMAWFE		2
#घोषणा SZ_DMAWFP		2
#घोषणा SZ_DMAWMB		1
#घोषणा SZ_DMAGO		6

#घोषणा BRST_LEN(ccr)		((((ccr) >> CC_SRCBRSTLEN_SHFT) & 0xf) + 1)
#घोषणा BRST_SIZE(ccr)		(1 << (((ccr) >> CC_SRCBRSTSIZE_SHFT) & 0x7))

#घोषणा BYTE_TO_BURST(b, ccr)	((b) / BRST_SIZE(ccr) / BRST_LEN(ccr))
#घोषणा BURST_TO_BYTE(c, ccr)	((c) * BRST_SIZE(ccr) * BRST_LEN(ccr))

/*
 * With 256 bytes, we can करो more than 2.5MB and 5MB xfers per req
 * at 1byte/burst क्रम P<->M and M<->M respectively.
 * For typical scenario, at 1word/burst, 10MB and 20MB xfers per req
 * should be enough क्रम P<->M and M<->M respectively.
 */
#घोषणा MCODE_BUFF_PER_REQ	256

/* Use this _only_ to रुको on transient states */
#घोषणा UNTIL(t, s)	जबतक (!(_state(t) & (s))) cpu_relax();

#अगर_घोषित PL330_DEBUG_MCGEN
अटल अचिन्हित cmd_line;
#घोषणा PL330_DBGCMD_DUMP(off, x...)	करो अणु \
						prपूर्णांकk("%x:", cmd_line); \
						prपूर्णांकk(KERN_CONT x); \
						cmd_line += off; \
					पूर्ण जबतक (0)
#घोषणा PL330_DBGMC_START(addr)		(cmd_line = addr)
#अन्यथा
#घोषणा PL330_DBGCMD_DUMP(off, x...)	करो अणुपूर्ण जबतक (0)
#घोषणा PL330_DBGMC_START(addr)		करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

/* The number of शेष descriptors */

#घोषणा NR_DEFAULT_DESC	16

/* Delay क्रम runसमय PM स्वतःsuspend, ms */
#घोषणा PL330_AUTOSUSPEND_DELAY 20

/* Populated by the PL330 core driver क्रम DMA API driver's info */
काष्ठा pl330_config अणु
	u32	periph_id;
#घोषणा DMAC_MODE_NS	(1 << 0)
	अचिन्हित पूर्णांक	mode;
	अचिन्हित पूर्णांक	data_bus_width:10; /* In number of bits */
	अचिन्हित पूर्णांक	data_buf_dep:11;
	अचिन्हित पूर्णांक	num_chan:4;
	अचिन्हित पूर्णांक	num_peri:6;
	u32		peri_ns;
	अचिन्हित पूर्णांक	num_events:6;
	u32		irq_ns;
पूर्ण;

/*
 * Request Configuration.
 * The PL330 core करोes not modअगरy this and uses the last
 * working configuration अगर the request करोesn't provide any.
 *
 * The Client may want to provide this info only क्रम the
 * first request and a request with new settings.
 */
काष्ठा pl330_reqcfg अणु
	/* Address Incrementing */
	अचिन्हित dst_inc:1;
	अचिन्हित src_inc:1;

	/*
	 * For now, the SRC & DST protection levels
	 * and burst size/length are assumed same.
	 */
	bool nonsecure;
	bool privileged;
	bool insnaccess;
	अचिन्हित brst_len:5;
	अचिन्हित brst_size:3; /* in घातer of 2 */

	क्रमागत pl330_cachectrl dcctl;
	क्रमागत pl330_cachectrl scctl;
	क्रमागत pl330_byteswap swap;
	काष्ठा pl330_config *pcfg;
पूर्ण;

/*
 * One cycle of DMAC operation.
 * There may be more than one xfer in a request.
 */
काष्ठा pl330_xfer अणु
	u32 src_addr;
	u32 dst_addr;
	/* Size to xfer */
	u32 bytes;
पूर्ण;

/* The xfer callbacks are made with one of these arguments. */
क्रमागत pl330_op_err अणु
	/* The all xfers in the request were success. */
	PL330_ERR_NONE,
	/* If req पातed due to global error. */
	PL330_ERR_ABORT,
	/* If req failed due to problem with Channel. */
	PL330_ERR_FAIL,
पूर्ण;

क्रमागत dmamov_dst अणु
	SAR = 0,
	CCR,
	DAR,
पूर्ण;

क्रमागत pl330_dst अणु
	SRC = 0,
	DST,
पूर्ण;

क्रमागत pl330_cond अणु
	SINGLE,
	BURST,
	ALWAYS,
पूर्ण;

काष्ठा dma_pl330_desc;

काष्ठा _pl330_req अणु
	u32 mc_bus;
	व्योम *mc_cpu;
	काष्ठा dma_pl330_desc *desc;
पूर्ण;

/* ToBeDone क्रम tasklet */
काष्ठा _pl330_tbd अणु
	bool reset_dmac;
	bool reset_mngr;
	u8 reset_chan;
पूर्ण;

/* A DMAC Thपढ़ो */
काष्ठा pl330_thपढ़ो अणु
	u8 id;
	पूर्णांक ev;
	/* If the channel is not yet acquired by any client */
	bool मुक्त;
	/* Parent DMAC */
	काष्ठा pl330_dmac *dmac;
	/* Only two at a समय */
	काष्ठा _pl330_req req[2];
	/* Index of the last enqueued request */
	अचिन्हित lstenq;
	/* Index of the last submitted request or -1 अगर the DMA is stopped */
	पूर्णांक req_running;
पूर्ण;

क्रमागत pl330_dmac_state अणु
	UNINIT,
	INIT,
	DYING,
पूर्ण;

क्रमागत desc_status अणु
	/* In the DMAC pool */
	FREE,
	/*
	 * Allocated to some channel during prep_xxx
	 * Also may be sitting on the work_list.
	 */
	PREP,
	/*
	 * Sitting on the work_list and alपढ़ोy submitted
	 * to the PL330 core. Not more than two descriptors
	 * of a channel can be BUSY at any समय.
	 */
	BUSY,
	/*
	 * Sitting on the channel work_list but xfer करोne
	 * by PL330 core
	 */
	DONE,
पूर्ण;

काष्ठा dma_pl330_chan अणु
	/* Schedule desc completion */
	काष्ठा tasklet_काष्ठा task;

	/* DMA-Engine Channel */
	काष्ठा dma_chan chan;

	/* List of submitted descriptors */
	काष्ठा list_head submitted_list;
	/* List of issued descriptors */
	काष्ठा list_head work_list;
	/* List of completed descriptors */
	काष्ठा list_head completed_list;

	/* Poपूर्णांकer to the DMAC that manages this channel,
	 * शून्य अगर the channel is available to be acquired.
	 * As the parent, this DMAC also provides descriptors
	 * to the channel.
	 */
	काष्ठा pl330_dmac *dmac;

	/* To protect channel manipulation */
	spinlock_t lock;

	/*
	 * Hardware channel thपढ़ो of PL330 DMAC. शून्य अगर the channel is
	 * available.
	 */
	काष्ठा pl330_thपढ़ो *thपढ़ो;

	/* For D-to-M and M-to-D channels */
	पूर्णांक burst_sz; /* the peripheral fअगरo width */
	पूर्णांक burst_len; /* the number of burst */
	phys_addr_t fअगरo_addr;
	/* DMA-mapped view of the FIFO; may dअगरfer अगर an IOMMU is present */
	dma_addr_t fअगरo_dma;
	क्रमागत dma_data_direction dir;
	काष्ठा dma_slave_config slave_config;

	/* क्रम cyclic capability */
	bool cyclic;

	/* क्रम runसमय pm tracking */
	bool active;
पूर्ण;

काष्ठा pl330_dmac अणु
	/* DMA-Engine Device */
	काष्ठा dma_device ddma;

	/* Pool of descriptors available क्रम the DMAC's channels */
	काष्ठा list_head desc_pool;
	/* To protect desc_pool manipulation */
	spinlock_t pool_lock;

	/* Size of MicroCode buffers क्रम each channel. */
	अचिन्हित mcbufsz;
	/* ioremap'ed address of PL330 रेजिस्टरs. */
	व्योम __iomem	*base;
	/* Populated by the PL330 core driver during pl330_add */
	काष्ठा pl330_config	pcfg;

	spinlock_t		lock;
	/* Maximum possible events/irqs */
	पूर्णांक			events[32];
	/* BUS address of MicroCode buffer */
	dma_addr_t		mcode_bus;
	/* CPU address of MicroCode buffer */
	व्योम			*mcode_cpu;
	/* List of all Channel thपढ़ोs */
	काष्ठा pl330_thपढ़ो	*channels;
	/* Poपूर्णांकer to the MANAGER thपढ़ो */
	काष्ठा pl330_thपढ़ो	*manager;
	/* To handle bad news in पूर्णांकerrupt */
	काष्ठा tasklet_काष्ठा	tasks;
	काष्ठा _pl330_tbd	dmac_tbd;
	/* State of DMAC operation */
	क्रमागत pl330_dmac_state	state;
	/* Holds list of reqs with due callbacks */
	काष्ठा list_head        req_करोne;

	/* Peripheral channels connected to this DMAC */
	अचिन्हित पूर्णांक num_peripherals;
	काष्ठा dma_pl330_chan *peripherals; /* keep at end */
	पूर्णांक quirks;

	काष्ठा reset_control	*rstc;
	काष्ठा reset_control	*rstc_ocp;
पूर्ण;

अटल काष्ठा pl330_of_quirks अणु
	अक्षर *quirk;
	पूर्णांक id;
पूर्ण of_quirks[] = अणु
	अणु
		.quirk = "arm,pl330-broken-no-flushp",
		.id = PL330_QUIRK_BROKEN_NO_FLUSHP,
	पूर्ण,
	अणु
		.quirk = "arm,pl330-periph-burst",
		.id = PL330_QUIRK_PERIPH_BURST,
	पूर्ण
पूर्ण;

काष्ठा dma_pl330_desc अणु
	/* To attach to a queue as child */
	काष्ठा list_head node;

	/* Descriptor क्रम the DMA Engine API */
	काष्ठा dma_async_tx_descriptor txd;

	/* Xfer क्रम PL330 core */
	काष्ठा pl330_xfer px;

	काष्ठा pl330_reqcfg rqcfg;

	क्रमागत desc_status status;

	पूर्णांक bytes_requested;
	bool last;

	/* The channel which currently holds this desc */
	काष्ठा dma_pl330_chan *pchan;

	क्रमागत dma_transfer_direction rqtype;
	/* Index of peripheral क्रम the xfer. */
	अचिन्हित peri:5;
	/* Hook to attach to DMAC's list of reqs with due callback */
	काष्ठा list_head rqd;
पूर्ण;

काष्ठा _xfer_spec अणु
	u32 ccr;
	काष्ठा dma_pl330_desc *desc;
पूर्ण;

अटल पूर्णांक pl330_config_ग_लिखो(काष्ठा dma_chan *chan,
			काष्ठा dma_slave_config *slave_config,
			क्रमागत dma_transfer_direction direction);

अटल अंतरभूत bool _queue_full(काष्ठा pl330_thपढ़ो *thrd)
अणु
	वापस thrd->req[0].desc != शून्य && thrd->req[1].desc != शून्य;
पूर्ण

अटल अंतरभूत bool is_manager(काष्ठा pl330_thपढ़ो *thrd)
अणु
	वापस thrd->dmac->manager == thrd;
पूर्ण

/* If manager of the thपढ़ो is in Non-Secure mode */
अटल अंतरभूत bool _manager_ns(काष्ठा pl330_thपढ़ो *thrd)
अणु
	वापस (thrd->dmac->pcfg.mode & DMAC_MODE_NS) ? true : false;
पूर्ण

अटल अंतरभूत u32 get_revision(u32 periph_id)
अणु
	वापस (periph_id >> PERIPH_REV_SHIFT) & PERIPH_REV_MASK;
पूर्ण

अटल अंतरभूत u32 _emit_END(अचिन्हित dry_run, u8 buf[])
अणु
	अगर (dry_run)
		वापस SZ_DMAEND;

	buf[0] = CMD_DMAEND;

	PL330_DBGCMD_DUMP(SZ_DMAEND, "\tDMAEND\n");

	वापस SZ_DMAEND;
पूर्ण

अटल अंतरभूत u32 _emit_FLUSHP(अचिन्हित dry_run, u8 buf[], u8 peri)
अणु
	अगर (dry_run)
		वापस SZ_DMAFLUSHP;

	buf[0] = CMD_DMAFLUSHP;

	peri &= 0x1f;
	peri <<= 3;
	buf[1] = peri;

	PL330_DBGCMD_DUMP(SZ_DMAFLUSHP, "\tDMAFLUSHP %u\n", peri >> 3);

	वापस SZ_DMAFLUSHP;
पूर्ण

अटल अंतरभूत u32 _emit_LD(अचिन्हित dry_run, u8 buf[],	क्रमागत pl330_cond cond)
अणु
	अगर (dry_run)
		वापस SZ_DMALD;

	buf[0] = CMD_DMALD;

	अगर (cond == SINGLE)
		buf[0] |= (0 << 1) | (1 << 0);
	अन्यथा अगर (cond == BURST)
		buf[0] |= (1 << 1) | (1 << 0);

	PL330_DBGCMD_DUMP(SZ_DMALD, "\tDMALD%c\n",
		cond == SINGLE ? 'S' : (cond == BURST ? 'B' : 'A'));

	वापस SZ_DMALD;
पूर्ण

अटल अंतरभूत u32 _emit_LDP(अचिन्हित dry_run, u8 buf[],
		क्रमागत pl330_cond cond, u8 peri)
अणु
	अगर (dry_run)
		वापस SZ_DMALDP;

	buf[0] = CMD_DMALDP;

	अगर (cond == BURST)
		buf[0] |= (1 << 1);

	peri &= 0x1f;
	peri <<= 3;
	buf[1] = peri;

	PL330_DBGCMD_DUMP(SZ_DMALDP, "\tDMALDP%c %u\n",
		cond == SINGLE ? 'S' : 'B', peri >> 3);

	वापस SZ_DMALDP;
पूर्ण

अटल अंतरभूत u32 _emit_LP(अचिन्हित dry_run, u8 buf[],
		अचिन्हित loop, u8 cnt)
अणु
	अगर (dry_run)
		वापस SZ_DMALP;

	buf[0] = CMD_DMALP;

	अगर (loop)
		buf[0] |= (1 << 1);

	cnt--; /* DMAC increments by 1 पूर्णांकernally */
	buf[1] = cnt;

	PL330_DBGCMD_DUMP(SZ_DMALP, "\tDMALP_%c %u\n", loop ? '1' : '0', cnt);

	वापस SZ_DMALP;
पूर्ण

काष्ठा _arg_LPEND अणु
	क्रमागत pl330_cond cond;
	bool क्रमever;
	अचिन्हित loop;
	u8 bjump;
पूर्ण;

अटल अंतरभूत u32 _emit_LPEND(अचिन्हित dry_run, u8 buf[],
		स्थिर काष्ठा _arg_LPEND *arg)
अणु
	क्रमागत pl330_cond cond = arg->cond;
	bool क्रमever = arg->क्रमever;
	अचिन्हित loop = arg->loop;
	u8 bjump = arg->bjump;

	अगर (dry_run)
		वापस SZ_DMALPEND;

	buf[0] = CMD_DMALPEND;

	अगर (loop)
		buf[0] |= (1 << 2);

	अगर (!क्रमever)
		buf[0] |= (1 << 4);

	अगर (cond == SINGLE)
		buf[0] |= (0 << 1) | (1 << 0);
	अन्यथा अगर (cond == BURST)
		buf[0] |= (1 << 1) | (1 << 0);

	buf[1] = bjump;

	PL330_DBGCMD_DUMP(SZ_DMALPEND, "\tDMALP%s%c_%c bjmpto_%x\n",
			क्रमever ? "FE" : "END",
			cond == SINGLE ? 'S' : (cond == BURST ? 'B' : 'A'),
			loop ? '1' : '0',
			bjump);

	वापस SZ_DMALPEND;
पूर्ण

अटल अंतरभूत u32 _emit_KILL(अचिन्हित dry_run, u8 buf[])
अणु
	अगर (dry_run)
		वापस SZ_DMAKILL;

	buf[0] = CMD_DMAKILL;

	वापस SZ_DMAKILL;
पूर्ण

अटल अंतरभूत u32 _emit_MOV(अचिन्हित dry_run, u8 buf[],
		क्रमागत dmamov_dst dst, u32 val)
अणु
	अगर (dry_run)
		वापस SZ_DMAMOV;

	buf[0] = CMD_DMAMOV;
	buf[1] = dst;
	buf[2] = val;
	buf[3] = val >> 8;
	buf[4] = val >> 16;
	buf[5] = val >> 24;

	PL330_DBGCMD_DUMP(SZ_DMAMOV, "\tDMAMOV %s 0x%x\n",
		dst == SAR ? "SAR" : (dst == DAR ? "DAR" : "CCR"), val);

	वापस SZ_DMAMOV;
पूर्ण

अटल अंतरभूत u32 _emit_RMB(अचिन्हित dry_run, u8 buf[])
अणु
	अगर (dry_run)
		वापस SZ_DMARMB;

	buf[0] = CMD_DMARMB;

	PL330_DBGCMD_DUMP(SZ_DMARMB, "\tDMARMB\n");

	वापस SZ_DMARMB;
पूर्ण

अटल अंतरभूत u32 _emit_SEV(अचिन्हित dry_run, u8 buf[], u8 ev)
अणु
	अगर (dry_run)
		वापस SZ_DMASEV;

	buf[0] = CMD_DMASEV;

	ev &= 0x1f;
	ev <<= 3;
	buf[1] = ev;

	PL330_DBGCMD_DUMP(SZ_DMASEV, "\tDMASEV %u\n", ev >> 3);

	वापस SZ_DMASEV;
पूर्ण

अटल अंतरभूत u32 _emit_ST(अचिन्हित dry_run, u8 buf[], क्रमागत pl330_cond cond)
अणु
	अगर (dry_run)
		वापस SZ_DMAST;

	buf[0] = CMD_DMAST;

	अगर (cond == SINGLE)
		buf[0] |= (0 << 1) | (1 << 0);
	अन्यथा अगर (cond == BURST)
		buf[0] |= (1 << 1) | (1 << 0);

	PL330_DBGCMD_DUMP(SZ_DMAST, "\tDMAST%c\n",
		cond == SINGLE ? 'S' : (cond == BURST ? 'B' : 'A'));

	वापस SZ_DMAST;
पूर्ण

अटल अंतरभूत u32 _emit_STP(अचिन्हित dry_run, u8 buf[],
		क्रमागत pl330_cond cond, u8 peri)
अणु
	अगर (dry_run)
		वापस SZ_DMASTP;

	buf[0] = CMD_DMASTP;

	अगर (cond == BURST)
		buf[0] |= (1 << 1);

	peri &= 0x1f;
	peri <<= 3;
	buf[1] = peri;

	PL330_DBGCMD_DUMP(SZ_DMASTP, "\tDMASTP%c %u\n",
		cond == SINGLE ? 'S' : 'B', peri >> 3);

	वापस SZ_DMASTP;
पूर्ण

अटल अंतरभूत u32 _emit_WFP(अचिन्हित dry_run, u8 buf[],
		क्रमागत pl330_cond cond, u8 peri)
अणु
	अगर (dry_run)
		वापस SZ_DMAWFP;

	buf[0] = CMD_DMAWFP;

	अगर (cond == SINGLE)
		buf[0] |= (0 << 1) | (0 << 0);
	अन्यथा अगर (cond == BURST)
		buf[0] |= (1 << 1) | (0 << 0);
	अन्यथा
		buf[0] |= (0 << 1) | (1 << 0);

	peri &= 0x1f;
	peri <<= 3;
	buf[1] = peri;

	PL330_DBGCMD_DUMP(SZ_DMAWFP, "\tDMAWFP%c %u\n",
		cond == SINGLE ? 'S' : (cond == BURST ? 'B' : 'P'), peri >> 3);

	वापस SZ_DMAWFP;
पूर्ण

अटल अंतरभूत u32 _emit_WMB(अचिन्हित dry_run, u8 buf[])
अणु
	अगर (dry_run)
		वापस SZ_DMAWMB;

	buf[0] = CMD_DMAWMB;

	PL330_DBGCMD_DUMP(SZ_DMAWMB, "\tDMAWMB\n");

	वापस SZ_DMAWMB;
पूर्ण

काष्ठा _arg_GO अणु
	u8 chan;
	u32 addr;
	अचिन्हित ns;
पूर्ण;

अटल अंतरभूत u32 _emit_GO(अचिन्हित dry_run, u8 buf[],
		स्थिर काष्ठा _arg_GO *arg)
अणु
	u8 chan = arg->chan;
	u32 addr = arg->addr;
	अचिन्हित ns = arg->ns;

	अगर (dry_run)
		वापस SZ_DMAGO;

	buf[0] = CMD_DMAGO;
	buf[0] |= (ns << 1);
	buf[1] = chan & 0x7;
	buf[2] = addr;
	buf[3] = addr >> 8;
	buf[4] = addr >> 16;
	buf[5] = addr >> 24;

	वापस SZ_DMAGO;
पूर्ण

#घोषणा msecs_to_loops(t) (loops_per_jअगरfy / 1000 * HZ * t)

/* Returns Time-Out */
अटल bool _until_dmac_idle(काष्ठा pl330_thपढ़ो *thrd)
अणु
	व्योम __iomem *regs = thrd->dmac->base;
	अचिन्हित दीर्घ loops = msecs_to_loops(5);

	करो अणु
		/* Until Manager is Idle */
		अगर (!(पढ़ोl(regs + DBGSTATUS) & DBG_BUSY))
			अवरोध;

		cpu_relax();
	पूर्ण जबतक (--loops);

	अगर (!loops)
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत व्योम _execute_DBGINSN(काष्ठा pl330_thपढ़ो *thrd,
		u8 insn[], bool as_manager)
अणु
	व्योम __iomem *regs = thrd->dmac->base;
	u32 val;

	/* If समयd out due to halted state-machine */
	अगर (_until_dmac_idle(thrd)) अणु
		dev_err(thrd->dmac->ddma.dev, "DMAC halted!\n");
		वापस;
	पूर्ण

	val = (insn[0] << 16) | (insn[1] << 24);
	अगर (!as_manager) अणु
		val |= (1 << 0);
		val |= (thrd->id << 8); /* Channel Number */
	पूर्ण
	ग_लिखोl(val, regs + DBGINST0);

	val = le32_to_cpu(*((__le32 *)&insn[2]));
	ग_लिखोl(val, regs + DBGINST1);

	/* Get going */
	ग_लिखोl(0, regs + DBGCMD);
पूर्ण

अटल अंतरभूत u32 _state(काष्ठा pl330_thपढ़ो *thrd)
अणु
	व्योम __iomem *regs = thrd->dmac->base;
	u32 val;

	अगर (is_manager(thrd))
		val = पढ़ोl(regs + DS) & 0xf;
	अन्यथा
		val = पढ़ोl(regs + CS(thrd->id)) & 0xf;

	चयन (val) अणु
	हाल DS_ST_STOP:
		वापस PL330_STATE_STOPPED;
	हाल DS_ST_EXEC:
		वापस PL330_STATE_EXECUTING;
	हाल DS_ST_CMISS:
		वापस PL330_STATE_CACHEMISS;
	हाल DS_ST_UPDTPC:
		वापस PL330_STATE_UPDTPC;
	हाल DS_ST_WFE:
		वापस PL330_STATE_WFE;
	हाल DS_ST_FAULT:
		वापस PL330_STATE_FAULTING;
	हाल DS_ST_ATBRR:
		अगर (is_manager(thrd))
			वापस PL330_STATE_INVALID;
		अन्यथा
			वापस PL330_STATE_ATBARRIER;
	हाल DS_ST_QBUSY:
		अगर (is_manager(thrd))
			वापस PL330_STATE_INVALID;
		अन्यथा
			वापस PL330_STATE_QUEUEBUSY;
	हाल DS_ST_WFP:
		अगर (is_manager(thrd))
			वापस PL330_STATE_INVALID;
		अन्यथा
			वापस PL330_STATE_WFP;
	हाल DS_ST_KILL:
		अगर (is_manager(thrd))
			वापस PL330_STATE_INVALID;
		अन्यथा
			वापस PL330_STATE_KILLING;
	हाल DS_ST_CMPLT:
		अगर (is_manager(thrd))
			वापस PL330_STATE_INVALID;
		अन्यथा
			वापस PL330_STATE_COMPLETING;
	हाल DS_ST_FLTCMP:
		अगर (is_manager(thrd))
			वापस PL330_STATE_INVALID;
		अन्यथा
			वापस PL330_STATE_FAULT_COMPLETING;
	शेष:
		वापस PL330_STATE_INVALID;
	पूर्ण
पूर्ण

अटल व्योम _stop(काष्ठा pl330_thपढ़ो *thrd)
अणु
	व्योम __iomem *regs = thrd->dmac->base;
	u8 insn[6] = अणु0, 0, 0, 0, 0, 0पूर्ण;
	u32 पूर्णांकen = पढ़ोl(regs + INTEN);

	अगर (_state(thrd) == PL330_STATE_FAULT_COMPLETING)
		UNTIL(thrd, PL330_STATE_FAULTING | PL330_STATE_KILLING);

	/* Return अगर nothing needs to be करोne */
	अगर (_state(thrd) == PL330_STATE_COMPLETING
		  || _state(thrd) == PL330_STATE_KILLING
		  || _state(thrd) == PL330_STATE_STOPPED)
		वापस;

	_emit_KILL(0, insn);

	_execute_DBGINSN(thrd, insn, is_manager(thrd));

	/* clear the event */
	अगर (पूर्णांकen & (1 << thrd->ev))
		ग_लिखोl(1 << thrd->ev, regs + INTCLR);
	/* Stop generating पूर्णांकerrupts क्रम SEV */
	ग_लिखोl(पूर्णांकen & ~(1 << thrd->ev), regs + INTEN);
पूर्ण

/* Start करोing req 'idx' of thread 'thrd' */
अटल bool _trigger(काष्ठा pl330_thपढ़ो *thrd)
अणु
	व्योम __iomem *regs = thrd->dmac->base;
	काष्ठा _pl330_req *req;
	काष्ठा dma_pl330_desc *desc;
	काष्ठा _arg_GO go;
	अचिन्हित ns;
	u8 insn[6] = अणु0, 0, 0, 0, 0, 0पूर्ण;
	पूर्णांक idx;

	/* Return अगर alपढ़ोy ACTIVE */
	अगर (_state(thrd) != PL330_STATE_STOPPED)
		वापस true;

	idx = 1 - thrd->lstenq;
	अगर (thrd->req[idx].desc != शून्य) अणु
		req = &thrd->req[idx];
	पूर्ण अन्यथा अणु
		idx = thrd->lstenq;
		अगर (thrd->req[idx].desc != शून्य)
			req = &thrd->req[idx];
		अन्यथा
			req = शून्य;
	पूर्ण

	/* Return अगर no request */
	अगर (!req)
		वापस true;

	/* Return अगर req is running */
	अगर (idx == thrd->req_running)
		वापस true;

	desc = req->desc;

	ns = desc->rqcfg.nonsecure ? 1 : 0;

	/* See 'Abort Sources' poपूर्णांक-4 at Page 2-25 */
	अगर (_manager_ns(thrd) && !ns)
		dev_info(thrd->dmac->ddma.dev, "%s:%d Recipe for ABORT!\n",
			__func__, __LINE__);

	go.chan = thrd->id;
	go.addr = req->mc_bus;
	go.ns = ns;
	_emit_GO(0, insn, &go);

	/* Set to generate पूर्णांकerrupts क्रम SEV */
	ग_लिखोl(पढ़ोl(regs + INTEN) | (1 << thrd->ev), regs + INTEN);

	/* Only manager can execute GO */
	_execute_DBGINSN(thrd, insn, true);

	thrd->req_running = idx;

	वापस true;
पूर्ण

अटल bool _start(काष्ठा pl330_thपढ़ो *thrd)
अणु
	चयन (_state(thrd)) अणु
	हाल PL330_STATE_FAULT_COMPLETING:
		UNTIL(thrd, PL330_STATE_FAULTING | PL330_STATE_KILLING);

		अगर (_state(thrd) == PL330_STATE_KILLING)
			UNTIL(thrd, PL330_STATE_STOPPED)
		fallthrough;

	हाल PL330_STATE_FAULTING:
		_stop(thrd);
		fallthrough;

	हाल PL330_STATE_KILLING:
	हाल PL330_STATE_COMPLETING:
		UNTIL(thrd, PL330_STATE_STOPPED)
		fallthrough;

	हाल PL330_STATE_STOPPED:
		वापस _trigger(thrd);

	हाल PL330_STATE_WFP:
	हाल PL330_STATE_QUEUEBUSY:
	हाल PL330_STATE_ATBARRIER:
	हाल PL330_STATE_UPDTPC:
	हाल PL330_STATE_CACHEMISS:
	हाल PL330_STATE_EXECUTING:
		वापस true;

	हाल PL330_STATE_WFE: /* For RESUME, nothing yet */
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक _ldst_memtomem(अचिन्हित dry_run, u8 buf[],
		स्थिर काष्ठा _xfer_spec *pxs, पूर्णांक cyc)
अणु
	पूर्णांक off = 0;
	काष्ठा pl330_config *pcfg = pxs->desc->rqcfg.pcfg;

	/* check lock-up मुक्त version */
	अगर (get_revision(pcfg->periph_id) >= PERIPH_REV_R1P0) अणु
		जबतक (cyc--) अणु
			off += _emit_LD(dry_run, &buf[off], ALWAYS);
			off += _emit_ST(dry_run, &buf[off], ALWAYS);
		पूर्ण
	पूर्ण अन्यथा अणु
		जबतक (cyc--) अणु
			off += _emit_LD(dry_run, &buf[off], ALWAYS);
			off += _emit_RMB(dry_run, &buf[off]);
			off += _emit_ST(dry_run, &buf[off], ALWAYS);
			off += _emit_WMB(dry_run, &buf[off]);
		पूर्ण
	पूर्ण

	वापस off;
पूर्ण

अटल u32 _emit_load(अचिन्हित पूर्णांक dry_run, u8 buf[],
	क्रमागत pl330_cond cond, क्रमागत dma_transfer_direction direction,
	u8 peri)
अणु
	पूर्णांक off = 0;

	चयन (direction) अणु
	हाल DMA_MEM_TO_MEM:
	हाल DMA_MEM_TO_DEV:
		off += _emit_LD(dry_run, &buf[off], cond);
		अवरोध;

	हाल DMA_DEV_TO_MEM:
		अगर (cond == ALWAYS) अणु
			off += _emit_LDP(dry_run, &buf[off], SINGLE,
				peri);
			off += _emit_LDP(dry_run, &buf[off], BURST,
				peri);
		पूर्ण अन्यथा अणु
			off += _emit_LDP(dry_run, &buf[off], cond,
				peri);
		पूर्ण
		अवरोध;

	शेष:
		/* this code should be unreachable */
		WARN_ON(1);
		अवरोध;
	पूर्ण

	वापस off;
पूर्ण

अटल अंतरभूत u32 _emit_store(अचिन्हित पूर्णांक dry_run, u8 buf[],
	क्रमागत pl330_cond cond, क्रमागत dma_transfer_direction direction,
	u8 peri)
अणु
	पूर्णांक off = 0;

	चयन (direction) अणु
	हाल DMA_MEM_TO_MEM:
	हाल DMA_DEV_TO_MEM:
		off += _emit_ST(dry_run, &buf[off], cond);
		अवरोध;

	हाल DMA_MEM_TO_DEV:
		अगर (cond == ALWAYS) अणु
			off += _emit_STP(dry_run, &buf[off], SINGLE,
				peri);
			off += _emit_STP(dry_run, &buf[off], BURST,
				peri);
		पूर्ण अन्यथा अणु
			off += _emit_STP(dry_run, &buf[off], cond,
				peri);
		पूर्ण
		अवरोध;

	शेष:
		/* this code should be unreachable */
		WARN_ON(1);
		अवरोध;
	पूर्ण

	वापस off;
पूर्ण

अटल अंतरभूत पूर्णांक _ldst_peripheral(काष्ठा pl330_dmac *pl330,
				 अचिन्हित dry_run, u8 buf[],
				 स्थिर काष्ठा _xfer_spec *pxs, पूर्णांक cyc,
				 क्रमागत pl330_cond cond)
अणु
	पूर्णांक off = 0;

	/*
	 * करो FLUSHP at beginning to clear any stale dma requests beक्रमe the
	 * first WFP.
	 */
	अगर (!(pl330->quirks & PL330_QUIRK_BROKEN_NO_FLUSHP))
		off += _emit_FLUSHP(dry_run, &buf[off], pxs->desc->peri);
	जबतक (cyc--) अणु
		off += _emit_WFP(dry_run, &buf[off], cond, pxs->desc->peri);
		off += _emit_load(dry_run, &buf[off], cond, pxs->desc->rqtype,
			pxs->desc->peri);
		off += _emit_store(dry_run, &buf[off], cond, pxs->desc->rqtype,
			pxs->desc->peri);
	पूर्ण

	वापस off;
पूर्ण

अटल पूर्णांक _bursts(काष्ठा pl330_dmac *pl330, अचिन्हित dry_run, u8 buf[],
		स्थिर काष्ठा _xfer_spec *pxs, पूर्णांक cyc)
अणु
	पूर्णांक off = 0;
	क्रमागत pl330_cond cond = BRST_LEN(pxs->ccr) > 1 ? BURST : SINGLE;

	अगर (pl330->quirks & PL330_QUIRK_PERIPH_BURST)
		cond = BURST;

	चयन (pxs->desc->rqtype) अणु
	हाल DMA_MEM_TO_DEV:
	हाल DMA_DEV_TO_MEM:
		off += _ldst_peripheral(pl330, dry_run, &buf[off], pxs, cyc,
			cond);
		अवरोध;

	हाल DMA_MEM_TO_MEM:
		off += _ldst_memtomem(dry_run, &buf[off], pxs, cyc);
		अवरोध;

	शेष:
		/* this code should be unreachable */
		WARN_ON(1);
		अवरोध;
	पूर्ण

	वापस off;
पूर्ण

/*
 * only the unaligned burst transfers have the dregs.
 * so, still transfer dregs with a reduced size burst
 * क्रम mem-to-mem, mem-to-dev or dev-to-mem.
 */
अटल पूर्णांक _dregs(काष्ठा pl330_dmac *pl330, अचिन्हित पूर्णांक dry_run, u8 buf[],
		स्थिर काष्ठा _xfer_spec *pxs, पूर्णांक transfer_length)
अणु
	पूर्णांक off = 0;
	पूर्णांक dregs_ccr;

	अगर (transfer_length == 0)
		वापस off;

	/*
	 * dregs_len = (total bytes - BURST_TO_BYTE(bursts, ccr)) /
	 *             BRST_SIZE(ccr)
	 * the dregs len must be smaller than burst len,
	 * so, क्रम higher efficiency, we can modअगरy CCR
	 * to use a reduced size burst len क्रम the dregs.
	 */
	dregs_ccr = pxs->ccr;
	dregs_ccr &= ~((0xf << CC_SRCBRSTLEN_SHFT) |
		(0xf << CC_DSTBRSTLEN_SHFT));
	dregs_ccr |= (((transfer_length - 1) & 0xf) <<
		CC_SRCBRSTLEN_SHFT);
	dregs_ccr |= (((transfer_length - 1) & 0xf) <<
		CC_DSTBRSTLEN_SHFT);

	चयन (pxs->desc->rqtype) अणु
	हाल DMA_MEM_TO_DEV:
	हाल DMA_DEV_TO_MEM:
		off += _emit_MOV(dry_run, &buf[off], CCR, dregs_ccr);
		off += _ldst_peripheral(pl330, dry_run, &buf[off], pxs, 1,
					BURST);
		अवरोध;

	हाल DMA_MEM_TO_MEM:
		off += _emit_MOV(dry_run, &buf[off], CCR, dregs_ccr);
		off += _ldst_memtomem(dry_run, &buf[off], pxs, 1);
		अवरोध;

	शेष:
		/* this code should be unreachable */
		WARN_ON(1);
		अवरोध;
	पूर्ण

	वापस off;
पूर्ण

/* Returns bytes consumed and updates bursts */
अटल अंतरभूत पूर्णांक _loop(काष्ठा pl330_dmac *pl330, अचिन्हित dry_run, u8 buf[],
		अचिन्हित दीर्घ *bursts, स्थिर काष्ठा _xfer_spec *pxs)
अणु
	पूर्णांक cyc, cycmax, szlp, szlpend, szbrst, off;
	अचिन्हित lcnt0, lcnt1, ljmp0, ljmp1;
	काष्ठा _arg_LPEND lpend;

	अगर (*bursts == 1)
		वापस _bursts(pl330, dry_run, buf, pxs, 1);

	/* Max iterations possible in DMALP is 256 */
	अगर (*bursts >= 256*256) अणु
		lcnt1 = 256;
		lcnt0 = 256;
		cyc = *bursts / lcnt1 / lcnt0;
	पूर्ण अन्यथा अगर (*bursts > 256) अणु
		lcnt1 = 256;
		lcnt0 = *bursts / lcnt1;
		cyc = 1;
	पूर्ण अन्यथा अणु
		lcnt1 = *bursts;
		lcnt0 = 0;
		cyc = 1;
	पूर्ण

	szlp = _emit_LP(1, buf, 0, 0);
	szbrst = _bursts(pl330, 1, buf, pxs, 1);

	lpend.cond = ALWAYS;
	lpend.क्रमever = false;
	lpend.loop = 0;
	lpend.bjump = 0;
	szlpend = _emit_LPEND(1, buf, &lpend);

	अगर (lcnt0) अणु
		szlp *= 2;
		szlpend *= 2;
	पूर्ण

	/*
	 * Max bursts that we can unroll due to limit on the
	 * size of backward jump that can be encoded in DMALPEND
	 * which is 8-bits and hence 255
	 */
	cycmax = (255 - (szlp + szlpend)) / szbrst;

	cyc = (cycmax < cyc) ? cycmax : cyc;

	off = 0;

	अगर (lcnt0) अणु
		off += _emit_LP(dry_run, &buf[off], 0, lcnt0);
		ljmp0 = off;
	पूर्ण

	off += _emit_LP(dry_run, &buf[off], 1, lcnt1);
	ljmp1 = off;

	off += _bursts(pl330, dry_run, &buf[off], pxs, cyc);

	lpend.cond = ALWAYS;
	lpend.क्रमever = false;
	lpend.loop = 1;
	lpend.bjump = off - ljmp1;
	off += _emit_LPEND(dry_run, &buf[off], &lpend);

	अगर (lcnt0) अणु
		lpend.cond = ALWAYS;
		lpend.क्रमever = false;
		lpend.loop = 0;
		lpend.bjump = off - ljmp0;
		off += _emit_LPEND(dry_run, &buf[off], &lpend);
	पूर्ण

	*bursts = lcnt1 * cyc;
	अगर (lcnt0)
		*bursts *= lcnt0;

	वापस off;
पूर्ण

अटल अंतरभूत पूर्णांक _setup_loops(काष्ठा pl330_dmac *pl330,
			       अचिन्हित dry_run, u8 buf[],
			       स्थिर काष्ठा _xfer_spec *pxs)
अणु
	काष्ठा pl330_xfer *x = &pxs->desc->px;
	u32 ccr = pxs->ccr;
	अचिन्हित दीर्घ c, bursts = BYTE_TO_BURST(x->bytes, ccr);
	पूर्णांक num_dregs = (x->bytes - BURST_TO_BYTE(bursts, ccr)) /
		BRST_SIZE(ccr);
	पूर्णांक off = 0;

	जबतक (bursts) अणु
		c = bursts;
		off += _loop(pl330, dry_run, &buf[off], &c, pxs);
		bursts -= c;
	पूर्ण
	off += _dregs(pl330, dry_run, &buf[off], pxs, num_dregs);

	वापस off;
पूर्ण

अटल अंतरभूत पूर्णांक _setup_xfer(काष्ठा pl330_dmac *pl330,
			      अचिन्हित dry_run, u8 buf[],
			      स्थिर काष्ठा _xfer_spec *pxs)
अणु
	काष्ठा pl330_xfer *x = &pxs->desc->px;
	पूर्णांक off = 0;

	/* DMAMOV SAR, x->src_addr */
	off += _emit_MOV(dry_run, &buf[off], SAR, x->src_addr);
	/* DMAMOV DAR, x->dst_addr */
	off += _emit_MOV(dry_run, &buf[off], DAR, x->dst_addr);

	/* Setup Loop(s) */
	off += _setup_loops(pl330, dry_run, &buf[off], pxs);

	वापस off;
पूर्ण

/*
 * A req is a sequence of one or more xfer units.
 * Returns the number of bytes taken to setup the MC क्रम the req.
 */
अटल पूर्णांक _setup_req(काष्ठा pl330_dmac *pl330, अचिन्हित dry_run,
		      काष्ठा pl330_thपढ़ो *thrd, अचिन्हित index,
		      काष्ठा _xfer_spec *pxs)
अणु
	काष्ठा _pl330_req *req = &thrd->req[index];
	u8 *buf = req->mc_cpu;
	पूर्णांक off = 0;

	PL330_DBGMC_START(req->mc_bus);

	/* DMAMOV CCR, ccr */
	off += _emit_MOV(dry_run, &buf[off], CCR, pxs->ccr);

	off += _setup_xfer(pl330, dry_run, &buf[off], pxs);

	/* DMASEV peripheral/event */
	off += _emit_SEV(dry_run, &buf[off], thrd->ev);
	/* DMAEND */
	off += _emit_END(dry_run, &buf[off]);

	वापस off;
पूर्ण

अटल अंतरभूत u32 _prepare_ccr(स्थिर काष्ठा pl330_reqcfg *rqc)
अणु
	u32 ccr = 0;

	अगर (rqc->src_inc)
		ccr |= CC_SRCINC;

	अगर (rqc->dst_inc)
		ccr |= CC_DSTINC;

	/* We set same protection levels क्रम Src and DST क्रम now */
	अगर (rqc->privileged)
		ccr |= CC_SRCPRI | CC_DSTPRI;
	अगर (rqc->nonsecure)
		ccr |= CC_SRCNS | CC_DSTNS;
	अगर (rqc->insnaccess)
		ccr |= CC_SRCIA | CC_DSTIA;

	ccr |= (((rqc->brst_len - 1) & 0xf) << CC_SRCBRSTLEN_SHFT);
	ccr |= (((rqc->brst_len - 1) & 0xf) << CC_DSTBRSTLEN_SHFT);

	ccr |= (rqc->brst_size << CC_SRCBRSTSIZE_SHFT);
	ccr |= (rqc->brst_size << CC_DSTBRSTSIZE_SHFT);

	ccr |= (rqc->scctl << CC_SRCCCTRL_SHFT);
	ccr |= (rqc->dcctl << CC_DSTCCTRL_SHFT);

	ccr |= (rqc->swap << CC_SWAP_SHFT);

	वापस ccr;
पूर्ण

/*
 * Submit a list of xfers after which the client wants notअगरication.
 * Client is not notअगरied after each xfer unit, just once after all
 * xfer units are करोne or some error occurs.
 */
अटल पूर्णांक pl330_submit_req(काष्ठा pl330_thपढ़ो *thrd,
	काष्ठा dma_pl330_desc *desc)
अणु
	काष्ठा pl330_dmac *pl330 = thrd->dmac;
	काष्ठा _xfer_spec xs;
	अचिन्हित दीर्घ flags;
	अचिन्हित idx;
	u32 ccr;
	पूर्णांक ret = 0;

	चयन (desc->rqtype) अणु
	हाल DMA_MEM_TO_DEV:
		अवरोध;

	हाल DMA_DEV_TO_MEM:
		अवरोध;

	हाल DMA_MEM_TO_MEM:
		अवरोध;

	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	अगर (pl330->state == DYING
		|| pl330->dmac_tbd.reset_chan & (1 << thrd->id)) अणु
		dev_info(thrd->dmac->ddma.dev, "%s:%d\n",
			__func__, __LINE__);
		वापस -EAGAIN;
	पूर्ण

	/* If request क्रम non-existing peripheral */
	अगर (desc->rqtype != DMA_MEM_TO_MEM &&
	    desc->peri >= pl330->pcfg.num_peri) अणु
		dev_info(thrd->dmac->ddma.dev,
				"%s:%d Invalid peripheral(%u)!\n",
				__func__, __LINE__, desc->peri);
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&pl330->lock, flags);

	अगर (_queue_full(thrd)) अणु
		ret = -EAGAIN;
		जाओ xfer_निकास;
	पूर्ण

	/* Prefer Secure Channel */
	अगर (!_manager_ns(thrd))
		desc->rqcfg.nonsecure = 0;
	अन्यथा
		desc->rqcfg.nonsecure = 1;

	ccr = _prepare_ccr(&desc->rqcfg);

	idx = thrd->req[0].desc == शून्य ? 0 : 1;

	xs.ccr = ccr;
	xs.desc = desc;

	/* First dry run to check अगर req is acceptable */
	ret = _setup_req(pl330, 1, thrd, idx, &xs);

	अगर (ret > pl330->mcbufsz / 2) अणु
		dev_info(pl330->ddma.dev, "%s:%d Try increasing mcbufsz (%i/%i)\n",
				__func__, __LINE__, ret, pl330->mcbufsz / 2);
		ret = -ENOMEM;
		जाओ xfer_निकास;
	पूर्ण

	/* Hook the request */
	thrd->lstenq = idx;
	thrd->req[idx].desc = desc;
	_setup_req(pl330, 0, thrd, idx, &xs);

	ret = 0;

xfer_निकास:
	spin_unlock_irqrestore(&pl330->lock, flags);

	वापस ret;
पूर्ण

अटल व्योम dma_pl330_rqcb(काष्ठा dma_pl330_desc *desc, क्रमागत pl330_op_err err)
अणु
	काष्ठा dma_pl330_chan *pch;
	अचिन्हित दीर्घ flags;

	अगर (!desc)
		वापस;

	pch = desc->pchan;

	/* If desc पातed */
	अगर (!pch)
		वापस;

	spin_lock_irqsave(&pch->lock, flags);

	desc->status = DONE;

	spin_unlock_irqrestore(&pch->lock, flags);

	tasklet_schedule(&pch->task);
पूर्ण

अटल व्योम pl330_करोtask(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा pl330_dmac *pl330 = from_tasklet(pl330, t, tasks);
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&pl330->lock, flags);

	/* The DMAC itself gone nuts */
	अगर (pl330->dmac_tbd.reset_dmac) अणु
		pl330->state = DYING;
		/* Reset the manager too */
		pl330->dmac_tbd.reset_mngr = true;
		/* Clear the reset flag */
		pl330->dmac_tbd.reset_dmac = false;
	पूर्ण

	अगर (pl330->dmac_tbd.reset_mngr) अणु
		_stop(pl330->manager);
		/* Reset all channels */
		pl330->dmac_tbd.reset_chan = (1 << pl330->pcfg.num_chan) - 1;
		/* Clear the reset flag */
		pl330->dmac_tbd.reset_mngr = false;
	पूर्ण

	क्रम (i = 0; i < pl330->pcfg.num_chan; i++) अणु

		अगर (pl330->dmac_tbd.reset_chan & (1 << i)) अणु
			काष्ठा pl330_thपढ़ो *thrd = &pl330->channels[i];
			व्योम __iomem *regs = pl330->base;
			क्रमागत pl330_op_err err;

			_stop(thrd);

			अगर (पढ़ोl(regs + FSC) & (1 << thrd->id))
				err = PL330_ERR_FAIL;
			अन्यथा
				err = PL330_ERR_ABORT;

			spin_unlock_irqrestore(&pl330->lock, flags);
			dma_pl330_rqcb(thrd->req[1 - thrd->lstenq].desc, err);
			dma_pl330_rqcb(thrd->req[thrd->lstenq].desc, err);
			spin_lock_irqsave(&pl330->lock, flags);

			thrd->req[0].desc = शून्य;
			thrd->req[1].desc = शून्य;
			thrd->req_running = -1;

			/* Clear the reset flag */
			pl330->dmac_tbd.reset_chan &= ~(1 << i);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&pl330->lock, flags);

	वापस;
पूर्ण

/* Returns 1 अगर state was updated, 0 otherwise */
अटल पूर्णांक pl330_update(काष्ठा pl330_dmac *pl330)
अणु
	काष्ठा dma_pl330_desc *descकरोne;
	अचिन्हित दीर्घ flags;
	व्योम __iomem *regs;
	u32 val;
	पूर्णांक id, ev, ret = 0;

	regs = pl330->base;

	spin_lock_irqsave(&pl330->lock, flags);

	val = पढ़ोl(regs + FSM) & 0x1;
	अगर (val)
		pl330->dmac_tbd.reset_mngr = true;
	अन्यथा
		pl330->dmac_tbd.reset_mngr = false;

	val = पढ़ोl(regs + FSC) & ((1 << pl330->pcfg.num_chan) - 1);
	pl330->dmac_tbd.reset_chan |= val;
	अगर (val) अणु
		पूर्णांक i = 0;
		जबतक (i < pl330->pcfg.num_chan) अणु
			अगर (val & (1 << i)) अणु
				dev_info(pl330->ddma.dev,
					"Reset Channel-%d\t CS-%x FTC-%x\n",
						i, पढ़ोl(regs + CS(i)),
						पढ़ोl(regs + FTC(i)));
				_stop(&pl330->channels[i]);
			पूर्ण
			i++;
		पूर्ण
	पूर्ण

	/* Check which event happened i.e, thपढ़ो notअगरied */
	val = पढ़ोl(regs + ES);
	अगर (pl330->pcfg.num_events < 32
			&& val & ~((1 << pl330->pcfg.num_events) - 1)) अणु
		pl330->dmac_tbd.reset_dmac = true;
		dev_err(pl330->ddma.dev, "%s:%d Unexpected!\n", __func__,
			__LINE__);
		ret = 1;
		जाओ updt_निकास;
	पूर्ण

	क्रम (ev = 0; ev < pl330->pcfg.num_events; ev++) अणु
		अगर (val & (1 << ev)) अणु /* Event occurred */
			काष्ठा pl330_thपढ़ो *thrd;
			u32 पूर्णांकen = पढ़ोl(regs + INTEN);
			पूर्णांक active;

			/* Clear the event */
			अगर (पूर्णांकen & (1 << ev))
				ग_लिखोl(1 << ev, regs + INTCLR);

			ret = 1;

			id = pl330->events[ev];

			thrd = &pl330->channels[id];

			active = thrd->req_running;
			अगर (active == -1) /* Aborted */
				जारी;

			/* Detach the req */
			descकरोne = thrd->req[active].desc;
			thrd->req[active].desc = शून्य;

			thrd->req_running = -1;

			/* Get going again ASAP */
			_start(thrd);

			/* For now, just make a list of callbacks to be करोne */
			list_add_tail(&descकरोne->rqd, &pl330->req_करोne);
		पूर्ण
	पूर्ण

	/* Now that we are in no hurry, करो the callbacks */
	जबतक (!list_empty(&pl330->req_करोne)) अणु
		descकरोne = list_first_entry(&pl330->req_करोne,
					    काष्ठा dma_pl330_desc, rqd);
		list_del(&descकरोne->rqd);
		spin_unlock_irqrestore(&pl330->lock, flags);
		dma_pl330_rqcb(descकरोne, PL330_ERR_NONE);
		spin_lock_irqsave(&pl330->lock, flags);
	पूर्ण

updt_निकास:
	spin_unlock_irqrestore(&pl330->lock, flags);

	अगर (pl330->dmac_tbd.reset_dmac
			|| pl330->dmac_tbd.reset_mngr
			|| pl330->dmac_tbd.reset_chan) अणु
		ret = 1;
		tasklet_schedule(&pl330->tasks);
	पूर्ण

	वापस ret;
पूर्ण

/* Reserve an event */
अटल अंतरभूत पूर्णांक _alloc_event(काष्ठा pl330_thपढ़ो *thrd)
अणु
	काष्ठा pl330_dmac *pl330 = thrd->dmac;
	पूर्णांक ev;

	क्रम (ev = 0; ev < pl330->pcfg.num_events; ev++)
		अगर (pl330->events[ev] == -1) अणु
			pl330->events[ev] = thrd->id;
			वापस ev;
		पूर्ण

	वापस -1;
पूर्ण

अटल bool _chan_ns(स्थिर काष्ठा pl330_dmac *pl330, पूर्णांक i)
अणु
	वापस pl330->pcfg.irq_ns & (1 << i);
पूर्ण

/* Upon success, वापसs IdentityToken क्रम the
 * allocated channel, शून्य otherwise.
 */
अटल काष्ठा pl330_thपढ़ो *pl330_request_channel(काष्ठा pl330_dmac *pl330)
अणु
	काष्ठा pl330_thपढ़ो *thrd = शून्य;
	पूर्णांक chans, i;

	अगर (pl330->state == DYING)
		वापस शून्य;

	chans = pl330->pcfg.num_chan;

	क्रम (i = 0; i < chans; i++) अणु
		thrd = &pl330->channels[i];
		अगर ((thrd->मुक्त) && (!_manager_ns(thrd) ||
					_chan_ns(pl330, i))) अणु
			thrd->ev = _alloc_event(thrd);
			अगर (thrd->ev >= 0) अणु
				thrd->मुक्त = false;
				thrd->lstenq = 1;
				thrd->req[0].desc = शून्य;
				thrd->req[1].desc = शून्य;
				thrd->req_running = -1;
				अवरोध;
			पूर्ण
		पूर्ण
		thrd = शून्य;
	पूर्ण

	वापस thrd;
पूर्ण

/* Release an event */
अटल अंतरभूत व्योम _मुक्त_event(काष्ठा pl330_thपढ़ो *thrd, पूर्णांक ev)
अणु
	काष्ठा pl330_dmac *pl330 = thrd->dmac;

	/* If the event is valid and was held by the thपढ़ो */
	अगर (ev >= 0 && ev < pl330->pcfg.num_events
			&& pl330->events[ev] == thrd->id)
		pl330->events[ev] = -1;
पूर्ण

अटल व्योम pl330_release_channel(काष्ठा pl330_thपढ़ो *thrd)
अणु
	अगर (!thrd || thrd->मुक्त)
		वापस;

	_stop(thrd);

	dma_pl330_rqcb(thrd->req[1 - thrd->lstenq].desc, PL330_ERR_ABORT);
	dma_pl330_rqcb(thrd->req[thrd->lstenq].desc, PL330_ERR_ABORT);

	_मुक्त_event(thrd, thrd->ev);
	thrd->मुक्त = true;
पूर्ण

/* Initialize the काष्ठाure क्रम PL330 configuration, that can be used
 * by the client driver the make best use of the DMAC
 */
अटल व्योम पढ़ो_dmac_config(काष्ठा pl330_dmac *pl330)
अणु
	व्योम __iomem *regs = pl330->base;
	u32 val;

	val = पढ़ोl(regs + CRD) >> CRD_DATA_WIDTH_SHIFT;
	val &= CRD_DATA_WIDTH_MASK;
	pl330->pcfg.data_bus_width = 8 * (1 << val);

	val = पढ़ोl(regs + CRD) >> CRD_DATA_BUFF_SHIFT;
	val &= CRD_DATA_BUFF_MASK;
	pl330->pcfg.data_buf_dep = val + 1;

	val = पढ़ोl(regs + CR0) >> CR0_NUM_CHANS_SHIFT;
	val &= CR0_NUM_CHANS_MASK;
	val += 1;
	pl330->pcfg.num_chan = val;

	val = पढ़ोl(regs + CR0);
	अगर (val & CR0_PERIPH_REQ_SET) अणु
		val = (val >> CR0_NUM_PERIPH_SHIFT) & CR0_NUM_PERIPH_MASK;
		val += 1;
		pl330->pcfg.num_peri = val;
		pl330->pcfg.peri_ns = पढ़ोl(regs + CR4);
	पूर्ण अन्यथा अणु
		pl330->pcfg.num_peri = 0;
	पूर्ण

	val = पढ़ोl(regs + CR0);
	अगर (val & CR0_BOOT_MAN_NS)
		pl330->pcfg.mode |= DMAC_MODE_NS;
	अन्यथा
		pl330->pcfg.mode &= ~DMAC_MODE_NS;

	val = पढ़ोl(regs + CR0) >> CR0_NUM_EVENTS_SHIFT;
	val &= CR0_NUM_EVENTS_MASK;
	val += 1;
	pl330->pcfg.num_events = val;

	pl330->pcfg.irq_ns = पढ़ोl(regs + CR3);
पूर्ण

अटल अंतरभूत व्योम _reset_thपढ़ो(काष्ठा pl330_thपढ़ो *thrd)
अणु
	काष्ठा pl330_dmac *pl330 = thrd->dmac;

	thrd->req[0].mc_cpu = pl330->mcode_cpu
				+ (thrd->id * pl330->mcbufsz);
	thrd->req[0].mc_bus = pl330->mcode_bus
				+ (thrd->id * pl330->mcbufsz);
	thrd->req[0].desc = शून्य;

	thrd->req[1].mc_cpu = thrd->req[0].mc_cpu
				+ pl330->mcbufsz / 2;
	thrd->req[1].mc_bus = thrd->req[0].mc_bus
				+ pl330->mcbufsz / 2;
	thrd->req[1].desc = शून्य;

	thrd->req_running = -1;
पूर्ण

अटल पूर्णांक dmac_alloc_thपढ़ोs(काष्ठा pl330_dmac *pl330)
अणु
	पूर्णांक chans = pl330->pcfg.num_chan;
	काष्ठा pl330_thपढ़ो *thrd;
	पूर्णांक i;

	/* Allocate 1 Manager and 'chans' Channel thपढ़ोs */
	pl330->channels = kसुस्मृति(1 + chans, माप(*thrd),
					GFP_KERNEL);
	अगर (!pl330->channels)
		वापस -ENOMEM;

	/* Init Channel thपढ़ोs */
	क्रम (i = 0; i < chans; i++) अणु
		thrd = &pl330->channels[i];
		thrd->id = i;
		thrd->dmac = pl330;
		_reset_thपढ़ो(thrd);
		thrd->मुक्त = true;
	पूर्ण

	/* MANAGER is indexed at the end */
	thrd = &pl330->channels[chans];
	thrd->id = chans;
	thrd->dmac = pl330;
	thrd->मुक्त = false;
	pl330->manager = thrd;

	वापस 0;
पूर्ण

अटल पूर्णांक dmac_alloc_resources(काष्ठा pl330_dmac *pl330)
अणु
	पूर्णांक chans = pl330->pcfg.num_chan;
	पूर्णांक ret;

	/*
	 * Alloc MicroCode buffer क्रम 'chans' Channel thपढ़ोs.
	 * A channel's buffer offset is (Channel_Id * MCODE_BUFF_PERCHAN)
	 */
	pl330->mcode_cpu = dma_alloc_attrs(pl330->ddma.dev,
				chans * pl330->mcbufsz,
				&pl330->mcode_bus, GFP_KERNEL,
				DMA_ATTR_PRIVILEGED);
	अगर (!pl330->mcode_cpu) अणु
		dev_err(pl330->ddma.dev, "%s:%d Can't allocate memory!\n",
			__func__, __LINE__);
		वापस -ENOMEM;
	पूर्ण

	ret = dmac_alloc_thपढ़ोs(pl330);
	अगर (ret) अणु
		dev_err(pl330->ddma.dev, "%s:%d Can't to create channels for DMAC!\n",
			__func__, __LINE__);
		dma_मुक्त_attrs(pl330->ddma.dev,
				chans * pl330->mcbufsz,
				pl330->mcode_cpu, pl330->mcode_bus,
				DMA_ATTR_PRIVILEGED);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pl330_add(काष्ठा pl330_dmac *pl330)
अणु
	पूर्णांक i, ret;

	/* Check अगर we can handle this DMAC */
	अगर ((pl330->pcfg.periph_id & 0xfffff) != PERIPH_ID_VAL) अणु
		dev_err(pl330->ddma.dev, "PERIPH_ID 0x%x !\n",
			pl330->pcfg.periph_id);
		वापस -EINVAL;
	पूर्ण

	/* Read the configuration of the DMAC */
	पढ़ो_dmac_config(pl330);

	अगर (pl330->pcfg.num_events == 0) अणु
		dev_err(pl330->ddma.dev, "%s:%d Can't work without events!\n",
			__func__, __LINE__);
		वापस -EINVAL;
	पूर्ण

	spin_lock_init(&pl330->lock);

	INIT_LIST_HEAD(&pl330->req_करोne);

	/* Use शेष MC buffer size अगर not provided */
	अगर (!pl330->mcbufsz)
		pl330->mcbufsz = MCODE_BUFF_PER_REQ * 2;

	/* Mark all events as मुक्त */
	क्रम (i = 0; i < pl330->pcfg.num_events; i++)
		pl330->events[i] = -1;

	/* Allocate resources needed by the DMAC */
	ret = dmac_alloc_resources(pl330);
	अगर (ret) अणु
		dev_err(pl330->ddma.dev, "Unable to create channels for DMAC\n");
		वापस ret;
	पूर्ण

	tasklet_setup(&pl330->tasks, pl330_करोtask);

	pl330->state = INIT;

	वापस 0;
पूर्ण

अटल पूर्णांक dmac_मुक्त_thपढ़ोs(काष्ठा pl330_dmac *pl330)
अणु
	काष्ठा pl330_thपढ़ो *thrd;
	पूर्णांक i;

	/* Release Channel thपढ़ोs */
	क्रम (i = 0; i < pl330->pcfg.num_chan; i++) अणु
		thrd = &pl330->channels[i];
		pl330_release_channel(thrd);
	पूर्ण

	/* Free memory */
	kमुक्त(pl330->channels);

	वापस 0;
पूर्ण

अटल व्योम pl330_del(काष्ठा pl330_dmac *pl330)
अणु
	pl330->state = UNINIT;

	tasklet_समाप्त(&pl330->tasks);

	/* Free DMAC resources */
	dmac_मुक्त_thपढ़ोs(pl330);

	dma_मुक्त_attrs(pl330->ddma.dev,
		pl330->pcfg.num_chan * pl330->mcbufsz, pl330->mcode_cpu,
		pl330->mcode_bus, DMA_ATTR_PRIVILEGED);
पूर्ण

/* क्रमward declaration */
अटल काष्ठा amba_driver pl330_driver;

अटल अंतरभूत काष्ठा dma_pl330_chan *
to_pchan(काष्ठा dma_chan *ch)
अणु
	अगर (!ch)
		वापस शून्य;

	वापस container_of(ch, काष्ठा dma_pl330_chan, chan);
पूर्ण

अटल अंतरभूत काष्ठा dma_pl330_desc *
to_desc(काष्ठा dma_async_tx_descriptor *tx)
अणु
	वापस container_of(tx, काष्ठा dma_pl330_desc, txd);
पूर्ण

अटल अंतरभूत व्योम fill_queue(काष्ठा dma_pl330_chan *pch)
अणु
	काष्ठा dma_pl330_desc *desc;
	पूर्णांक ret;

	list_क्रम_each_entry(desc, &pch->work_list, node) अणु

		/* If alपढ़ोy submitted */
		अगर (desc->status == BUSY)
			जारी;

		ret = pl330_submit_req(pch->thपढ़ो, desc);
		अगर (!ret) अणु
			desc->status = BUSY;
		पूर्ण अन्यथा अगर (ret == -EAGAIN) अणु
			/* QFull or DMAC Dying */
			अवरोध;
		पूर्ण अन्यथा अणु
			/* Unacceptable request */
			desc->status = DONE;
			dev_err(pch->dmac->ddma.dev, "%s:%d Bad Desc(%d)\n",
					__func__, __LINE__, desc->txd.cookie);
			tasklet_schedule(&pch->task);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम pl330_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा dma_pl330_chan *pch = from_tasklet(pch, t, task);
	काष्ठा dma_pl330_desc *desc, *_dt;
	अचिन्हित दीर्घ flags;
	bool घातer_करोwn = false;

	spin_lock_irqsave(&pch->lock, flags);

	/* Pick up ripe tomatoes */
	list_क्रम_each_entry_safe(desc, _dt, &pch->work_list, node)
		अगर (desc->status == DONE) अणु
			अगर (!pch->cyclic)
				dma_cookie_complete(&desc->txd);
			list_move_tail(&desc->node, &pch->completed_list);
		पूर्ण

	/* Try to submit a req imm. next to the last completed cookie */
	fill_queue(pch);

	अगर (list_empty(&pch->work_list)) अणु
		spin_lock(&pch->thपढ़ो->dmac->lock);
		_stop(pch->thपढ़ो);
		spin_unlock(&pch->thपढ़ो->dmac->lock);
		घातer_करोwn = true;
		pch->active = false;
	पूर्ण अन्यथा अणु
		/* Make sure the PL330 Channel thपढ़ो is active */
		spin_lock(&pch->thपढ़ो->dmac->lock);
		_start(pch->thपढ़ो);
		spin_unlock(&pch->thपढ़ो->dmac->lock);
	पूर्ण

	जबतक (!list_empty(&pch->completed_list)) अणु
		काष्ठा dmaengine_desc_callback cb;

		desc = list_first_entry(&pch->completed_list,
					काष्ठा dma_pl330_desc, node);

		dmaengine_desc_get_callback(&desc->txd, &cb);

		अगर (pch->cyclic) अणु
			desc->status = PREP;
			list_move_tail(&desc->node, &pch->work_list);
			अगर (घातer_करोwn) अणु
				pch->active = true;
				spin_lock(&pch->thपढ़ो->dmac->lock);
				_start(pch->thपढ़ो);
				spin_unlock(&pch->thपढ़ो->dmac->lock);
				घातer_करोwn = false;
			पूर्ण
		पूर्ण अन्यथा अणु
			desc->status = FREE;
			list_move_tail(&desc->node, &pch->dmac->desc_pool);
		पूर्ण

		dma_descriptor_unmap(&desc->txd);

		अगर (dmaengine_desc_callback_valid(&cb)) अणु
			spin_unlock_irqrestore(&pch->lock, flags);
			dmaengine_desc_callback_invoke(&cb, शून्य);
			spin_lock_irqsave(&pch->lock, flags);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&pch->lock, flags);

	/* If work list empty, घातer करोwn */
	अगर (घातer_करोwn) अणु
		pm_runसमय_mark_last_busy(pch->dmac->ddma.dev);
		pm_runसमय_put_स्वतःsuspend(pch->dmac->ddma.dev);
	पूर्ण
पूर्ण

अटल काष्ठा dma_chan *of_dma_pl330_xlate(काष्ठा of_phandle_args *dma_spec,
						काष्ठा of_dma *ofdma)
अणु
	पूर्णांक count = dma_spec->args_count;
	काष्ठा pl330_dmac *pl330 = ofdma->of_dma_data;
	अचिन्हित पूर्णांक chan_id;

	अगर (!pl330)
		वापस शून्य;

	अगर (count != 1)
		वापस शून्य;

	chan_id = dma_spec->args[0];
	अगर (chan_id >= pl330->num_peripherals)
		वापस शून्य;

	वापस dma_get_slave_channel(&pl330->peripherals[chan_id].chan);
पूर्ण

अटल पूर्णांक pl330_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा dma_pl330_chan *pch = to_pchan(chan);
	काष्ठा pl330_dmac *pl330 = pch->dmac;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pl330->lock, flags);

	dma_cookie_init(chan);
	pch->cyclic = false;

	pch->thपढ़ो = pl330_request_channel(pl330);
	अगर (!pch->thपढ़ो) अणु
		spin_unlock_irqrestore(&pl330->lock, flags);
		वापस -ENOMEM;
	पूर्ण

	tasklet_setup(&pch->task, pl330_tasklet);

	spin_unlock_irqrestore(&pl330->lock, flags);

	वापस 1;
पूर्ण

/*
 * We need the data direction between the DMAC (the dma-mapping "device") and
 * the FIFO (the dmaengine "dev"), from the FIFO's poपूर्णांक of view. Confusing!
 */
अटल क्रमागत dma_data_direction
pl330_dma_slave_map_dir(क्रमागत dma_transfer_direction dir)
अणु
	चयन (dir) अणु
	हाल DMA_MEM_TO_DEV:
		वापस DMA_FROM_DEVICE;
	हाल DMA_DEV_TO_MEM:
		वापस DMA_TO_DEVICE;
	हाल DMA_DEV_TO_DEV:
		वापस DMA_BIसूचीECTIONAL;
	शेष:
		वापस DMA_NONE;
	पूर्ण
पूर्ण

अटल व्योम pl330_unprep_slave_fअगरo(काष्ठा dma_pl330_chan *pch)
अणु
	अगर (pch->dir != DMA_NONE)
		dma_unmap_resource(pch->chan.device->dev, pch->fअगरo_dma,
				   1 << pch->burst_sz, pch->dir, 0);
	pch->dir = DMA_NONE;
पूर्ण


अटल bool pl330_prep_slave_fअगरo(काष्ठा dma_pl330_chan *pch,
				  क्रमागत dma_transfer_direction dir)
अणु
	काष्ठा device *dev = pch->chan.device->dev;
	क्रमागत dma_data_direction dma_dir = pl330_dma_slave_map_dir(dir);

	/* Alपढ़ोy mapped क्रम this config? */
	अगर (pch->dir == dma_dir)
		वापस true;

	pl330_unprep_slave_fअगरo(pch);
	pch->fअगरo_dma = dma_map_resource(dev, pch->fअगरo_addr,
					 1 << pch->burst_sz, dma_dir, 0);
	अगर (dma_mapping_error(dev, pch->fअगरo_dma))
		वापस false;

	pch->dir = dma_dir;
	वापस true;
पूर्ण

अटल पूर्णांक fixup_burst_len(पूर्णांक max_burst_len, पूर्णांक quirks)
अणु
	अगर (max_burst_len > PL330_MAX_BURST)
		वापस PL330_MAX_BURST;
	अन्यथा अगर (max_burst_len < 1)
		वापस 1;
	अन्यथा
		वापस max_burst_len;
पूर्ण

अटल पूर्णांक pl330_config_ग_लिखो(काष्ठा dma_chan *chan,
			काष्ठा dma_slave_config *slave_config,
			क्रमागत dma_transfer_direction direction)
अणु
	काष्ठा dma_pl330_chan *pch = to_pchan(chan);

	pl330_unprep_slave_fअगरo(pch);
	अगर (direction == DMA_MEM_TO_DEV) अणु
		अगर (slave_config->dst_addr)
			pch->fअगरo_addr = slave_config->dst_addr;
		अगर (slave_config->dst_addr_width)
			pch->burst_sz = __ffs(slave_config->dst_addr_width);
		pch->burst_len = fixup_burst_len(slave_config->dst_maxburst,
			pch->dmac->quirks);
	पूर्ण अन्यथा अगर (direction == DMA_DEV_TO_MEM) अणु
		अगर (slave_config->src_addr)
			pch->fअगरo_addr = slave_config->src_addr;
		अगर (slave_config->src_addr_width)
			pch->burst_sz = __ffs(slave_config->src_addr_width);
		pch->burst_len = fixup_burst_len(slave_config->src_maxburst,
			pch->dmac->quirks);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pl330_config(काष्ठा dma_chan *chan,
			काष्ठा dma_slave_config *slave_config)
अणु
	काष्ठा dma_pl330_chan *pch = to_pchan(chan);

	स_नकल(&pch->slave_config, slave_config, माप(*slave_config));

	वापस 0;
पूर्ण

अटल पूर्णांक pl330_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा dma_pl330_chan *pch = to_pchan(chan);
	काष्ठा dma_pl330_desc *desc;
	अचिन्हित दीर्घ flags;
	काष्ठा pl330_dmac *pl330 = pch->dmac;
	bool घातer_करोwn = false;

	pm_runसमय_get_sync(pl330->ddma.dev);
	spin_lock_irqsave(&pch->lock, flags);

	spin_lock(&pl330->lock);
	_stop(pch->thपढ़ो);
	pch->thपढ़ो->req[0].desc = शून्य;
	pch->thपढ़ो->req[1].desc = शून्य;
	pch->thपढ़ो->req_running = -1;
	spin_unlock(&pl330->lock);

	घातer_करोwn = pch->active;
	pch->active = false;

	/* Mark all desc करोne */
	list_क्रम_each_entry(desc, &pch->submitted_list, node) अणु
		desc->status = FREE;
		dma_cookie_complete(&desc->txd);
	पूर्ण

	list_क्रम_each_entry(desc, &pch->work_list , node) अणु
		desc->status = FREE;
		dma_cookie_complete(&desc->txd);
	पूर्ण

	list_splice_tail_init(&pch->submitted_list, &pl330->desc_pool);
	list_splice_tail_init(&pch->work_list, &pl330->desc_pool);
	list_splice_tail_init(&pch->completed_list, &pl330->desc_pool);
	spin_unlock_irqrestore(&pch->lock, flags);
	pm_runसमय_mark_last_busy(pl330->ddma.dev);
	अगर (घातer_करोwn)
		pm_runसमय_put_स्वतःsuspend(pl330->ddma.dev);
	pm_runसमय_put_स्वतःsuspend(pl330->ddma.dev);

	वापस 0;
पूर्ण

/*
 * We करोn't support DMA_RESUME command because of hardware
 * limitations, so after pausing the channel we cannot restore
 * it to active state. We have to terminate channel and setup
 * DMA transfer again. This छोड़ो feature was implemented to
 * allow safely पढ़ो residue beक्रमe channel termination.
 */
अटल पूर्णांक pl330_छोड़ो(काष्ठा dma_chan *chan)
अणु
	काष्ठा dma_pl330_chan *pch = to_pchan(chan);
	काष्ठा pl330_dmac *pl330 = pch->dmac;
	अचिन्हित दीर्घ flags;

	pm_runसमय_get_sync(pl330->ddma.dev);
	spin_lock_irqsave(&pch->lock, flags);

	spin_lock(&pl330->lock);
	_stop(pch->thपढ़ो);
	spin_unlock(&pl330->lock);

	spin_unlock_irqrestore(&pch->lock, flags);
	pm_runसमय_mark_last_busy(pl330->ddma.dev);
	pm_runसमय_put_स्वतःsuspend(pl330->ddma.dev);

	वापस 0;
पूर्ण

अटल व्योम pl330_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा dma_pl330_chan *pch = to_pchan(chan);
	काष्ठा pl330_dmac *pl330 = pch->dmac;
	अचिन्हित दीर्घ flags;

	tasklet_समाप्त(&pch->task);

	pm_runसमय_get_sync(pch->dmac->ddma.dev);
	spin_lock_irqsave(&pl330->lock, flags);

	pl330_release_channel(pch->thपढ़ो);
	pch->thपढ़ो = शून्य;

	अगर (pch->cyclic)
		list_splice_tail_init(&pch->work_list, &pch->dmac->desc_pool);

	spin_unlock_irqrestore(&pl330->lock, flags);
	pm_runसमय_mark_last_busy(pch->dmac->ddma.dev);
	pm_runसमय_put_स्वतःsuspend(pch->dmac->ddma.dev);
	pl330_unprep_slave_fअगरo(pch);
पूर्ण

अटल पूर्णांक pl330_get_current_xferred_count(काष्ठा dma_pl330_chan *pch,
					   काष्ठा dma_pl330_desc *desc)
अणु
	काष्ठा pl330_thपढ़ो *thrd = pch->thपढ़ो;
	काष्ठा pl330_dmac *pl330 = pch->dmac;
	व्योम __iomem *regs = thrd->dmac->base;
	u32 val, addr;

	pm_runसमय_get_sync(pl330->ddma.dev);
	val = addr = 0;
	अगर (desc->rqcfg.src_inc) अणु
		val = पढ़ोl(regs + SA(thrd->id));
		addr = desc->px.src_addr;
	पूर्ण अन्यथा अणु
		val = पढ़ोl(regs + DA(thrd->id));
		addr = desc->px.dst_addr;
	पूर्ण
	pm_runसमय_mark_last_busy(pch->dmac->ddma.dev);
	pm_runसमय_put_स्वतःsuspend(pl330->ddma.dev);

	/* If DMAMOV hasn't finished yet, SAR/DAR can be zero */
	अगर (!val)
		वापस 0;

	वापस val - addr;
पूर्ण

अटल क्रमागत dma_status
pl330_tx_status(काष्ठा dma_chan *chan, dma_cookie_t cookie,
		 काष्ठा dma_tx_state *txstate)
अणु
	क्रमागत dma_status ret;
	अचिन्हित दीर्घ flags;
	काष्ठा dma_pl330_desc *desc, *running = शून्य, *last_enq = शून्य;
	काष्ठा dma_pl330_chan *pch = to_pchan(chan);
	अचिन्हित पूर्णांक transferred, residual = 0;

	ret = dma_cookie_status(chan, cookie, txstate);

	अगर (!txstate)
		वापस ret;

	अगर (ret == DMA_COMPLETE)
		जाओ out;

	spin_lock_irqsave(&pch->lock, flags);
	spin_lock(&pch->thपढ़ो->dmac->lock);

	अगर (pch->thपढ़ो->req_running != -1)
		running = pch->thपढ़ो->req[pch->thपढ़ो->req_running].desc;

	last_enq = pch->thपढ़ो->req[pch->thपढ़ो->lstenq].desc;

	/* Check in pending list */
	list_क्रम_each_entry(desc, &pch->work_list, node) अणु
		अगर (desc->status == DONE)
			transferred = desc->bytes_requested;
		अन्यथा अगर (running && desc == running)
			transferred =
				pl330_get_current_xferred_count(pch, desc);
		अन्यथा अगर (desc->status == BUSY)
			/*
			 * Busy but not running means either just enqueued,
			 * or finished and not yet marked करोne
			 */
			अगर (desc == last_enq)
				transferred = 0;
			अन्यथा
				transferred = desc->bytes_requested;
		अन्यथा
			transferred = 0;
		residual += desc->bytes_requested - transferred;
		अगर (desc->txd.cookie == cookie) अणु
			चयन (desc->status) अणु
			हाल DONE:
				ret = DMA_COMPLETE;
				अवरोध;
			हाल PREP:
			हाल BUSY:
				ret = DMA_IN_PROGRESS;
				अवरोध;
			शेष:
				WARN_ON(1);
			पूर्ण
			अवरोध;
		पूर्ण
		अगर (desc->last)
			residual = 0;
	पूर्ण
	spin_unlock(&pch->thपढ़ो->dmac->lock);
	spin_unlock_irqrestore(&pch->lock, flags);

out:
	dma_set_residue(txstate, residual);

	वापस ret;
पूर्ण

अटल व्योम pl330_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा dma_pl330_chan *pch = to_pchan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pch->lock, flags);
	अगर (list_empty(&pch->work_list)) अणु
		/*
		 * Warn on nothing pending. Empty submitted_list may
		 * अवरोध our pm_runसमय usage counter as it is
		 * updated on work_list emptiness status.
		 */
		WARN_ON(list_empty(&pch->submitted_list));
		pch->active = true;
		pm_runसमय_get_sync(pch->dmac->ddma.dev);
	पूर्ण
	list_splice_tail_init(&pch->submitted_list, &pch->work_list);
	spin_unlock_irqrestore(&pch->lock, flags);

	pl330_tasklet(&pch->task);
पूर्ण

/*
 * We वापसed the last one of the circular list of descriptor(s)
 * from prep_xxx, so the argument to submit corresponds to the last
 * descriptor of the list.
 */
अटल dma_cookie_t pl330_tx_submit(काष्ठा dma_async_tx_descriptor *tx)
अणु
	काष्ठा dma_pl330_desc *desc, *last = to_desc(tx);
	काष्ठा dma_pl330_chan *pch = to_pchan(tx->chan);
	dma_cookie_t cookie;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pch->lock, flags);

	/* Assign cookies to all nodes */
	जबतक (!list_empty(&last->node)) अणु
		desc = list_entry(last->node.next, काष्ठा dma_pl330_desc, node);
		अगर (pch->cyclic) अणु
			desc->txd.callback = last->txd.callback;
			desc->txd.callback_param = last->txd.callback_param;
		पूर्ण
		desc->last = false;

		dma_cookie_assign(&desc->txd);

		list_move_tail(&desc->node, &pch->submitted_list);
	पूर्ण

	last->last = true;
	cookie = dma_cookie_assign(&last->txd);
	list_add_tail(&last->node, &pch->submitted_list);
	spin_unlock_irqrestore(&pch->lock, flags);

	वापस cookie;
पूर्ण

अटल अंतरभूत व्योम _init_desc(काष्ठा dma_pl330_desc *desc)
अणु
	desc->rqcfg.swap = SWAP_NO;
	desc->rqcfg.scctl = CCTRL0;
	desc->rqcfg.dcctl = CCTRL0;
	desc->txd.tx_submit = pl330_tx_submit;

	INIT_LIST_HEAD(&desc->node);
पूर्ण

/* Returns the number of descriptors added to the DMAC pool */
अटल पूर्णांक add_desc(काष्ठा list_head *pool, spinlock_t *lock,
		    gfp_t flg, पूर्णांक count)
अणु
	काष्ठा dma_pl330_desc *desc;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	desc = kसुस्मृति(count, माप(*desc), flg);
	अगर (!desc)
		वापस 0;

	spin_lock_irqsave(lock, flags);

	क्रम (i = 0; i < count; i++) अणु
		_init_desc(&desc[i]);
		list_add_tail(&desc[i].node, pool);
	पूर्ण

	spin_unlock_irqrestore(lock, flags);

	वापस count;
पूर्ण

अटल काष्ठा dma_pl330_desc *pluck_desc(काष्ठा list_head *pool,
					 spinlock_t *lock)
अणु
	काष्ठा dma_pl330_desc *desc = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(lock, flags);

	अगर (!list_empty(pool)) अणु
		desc = list_entry(pool->next,
				काष्ठा dma_pl330_desc, node);

		list_del_init(&desc->node);

		desc->status = PREP;
		desc->txd.callback = शून्य;
	पूर्ण

	spin_unlock_irqrestore(lock, flags);

	वापस desc;
पूर्ण

अटल काष्ठा dma_pl330_desc *pl330_get_desc(काष्ठा dma_pl330_chan *pch)
अणु
	काष्ठा pl330_dmac *pl330 = pch->dmac;
	u8 *peri_id = pch->chan.निजी;
	काष्ठा dma_pl330_desc *desc;

	/* Pluck one desc from the pool of DMAC */
	desc = pluck_desc(&pl330->desc_pool, &pl330->pool_lock);

	/* If the DMAC pool is empty, alloc new */
	अगर (!desc) अणु
		DEFINE_SPINLOCK(lock);
		LIST_HEAD(pool);

		अगर (!add_desc(&pool, &lock, GFP_ATOMIC, 1))
			वापस शून्य;

		desc = pluck_desc(&pool, &lock);
		WARN_ON(!desc || !list_empty(&pool));
	पूर्ण

	/* Initialize the descriptor */
	desc->pchan = pch;
	desc->txd.cookie = 0;
	async_tx_ack(&desc->txd);

	desc->peri = peri_id ? pch->chan.chan_id : 0;
	desc->rqcfg.pcfg = &pch->dmac->pcfg;

	dma_async_tx_descriptor_init(&desc->txd, &pch->chan);

	वापस desc;
पूर्ण

अटल अंतरभूत व्योम fill_px(काष्ठा pl330_xfer *px,
		dma_addr_t dst, dma_addr_t src, माप_प्रकार len)
अणु
	px->bytes = len;
	px->dst_addr = dst;
	px->src_addr = src;
पूर्ण

अटल काष्ठा dma_pl330_desc *
__pl330_prep_dma_स_नकल(काष्ठा dma_pl330_chan *pch, dma_addr_t dst,
		dma_addr_t src, माप_प्रकार len)
अणु
	काष्ठा dma_pl330_desc *desc = pl330_get_desc(pch);

	अगर (!desc) अणु
		dev_err(pch->dmac->ddma.dev, "%s:%d Unable to fetch desc\n",
			__func__, __LINE__);
		वापस शून्य;
	पूर्ण

	/*
	 * Ideally we should lookout क्रम reqs bigger than
	 * those that can be programmed with 256 bytes of
	 * MC buffer, but considering a req size is selकरोm
	 * going to be word-unaligned and more than 200MB,
	 * we take it easy.
	 * Also, should the limit is reached we'd rather
	 * have the platक्रमm increase MC buffer size than
	 * complicating this API driver.
	 */
	fill_px(&desc->px, dst, src, len);

	वापस desc;
पूर्ण

/* Call after fixing burst size */
अटल अंतरभूत पूर्णांक get_burst_len(काष्ठा dma_pl330_desc *desc, माप_प्रकार len)
अणु
	काष्ठा dma_pl330_chan *pch = desc->pchan;
	काष्ठा pl330_dmac *pl330 = pch->dmac;
	पूर्णांक burst_len;

	burst_len = pl330->pcfg.data_bus_width / 8;
	burst_len *= pl330->pcfg.data_buf_dep / pl330->pcfg.num_chan;
	burst_len >>= desc->rqcfg.brst_size;

	/* src/dst_burst_len can't be more than 16 */
	अगर (burst_len > PL330_MAX_BURST)
		burst_len = PL330_MAX_BURST;

	वापस burst_len;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *pl330_prep_dma_cyclic(
		काष्ठा dma_chan *chan, dma_addr_t dma_addr, माप_प्रकार len,
		माप_प्रकार period_len, क्रमागत dma_transfer_direction direction,
		अचिन्हित दीर्घ flags)
अणु
	काष्ठा dma_pl330_desc *desc = शून्य, *first = शून्य;
	काष्ठा dma_pl330_chan *pch = to_pchan(chan);
	काष्ठा pl330_dmac *pl330 = pch->dmac;
	अचिन्हित पूर्णांक i;
	dma_addr_t dst;
	dma_addr_t src;

	अगर (len % period_len != 0)
		वापस शून्य;

	अगर (!is_slave_direction(direction)) अणु
		dev_err(pch->dmac->ddma.dev, "%s:%d Invalid dma direction\n",
		__func__, __LINE__);
		वापस शून्य;
	पूर्ण

	pl330_config_ग_लिखो(chan, &pch->slave_config, direction);

	अगर (!pl330_prep_slave_fअगरo(pch, direction))
		वापस शून्य;

	क्रम (i = 0; i < len / period_len; i++) अणु
		desc = pl330_get_desc(pch);
		अगर (!desc) अणु
			अचिन्हित दीर्घ अगरlags;

			dev_err(pch->dmac->ddma.dev, "%s:%d Unable to fetch desc\n",
				__func__, __LINE__);

			अगर (!first)
				वापस शून्य;

			spin_lock_irqsave(&pl330->pool_lock, अगरlags);

			जबतक (!list_empty(&first->node)) अणु
				desc = list_entry(first->node.next,
						काष्ठा dma_pl330_desc, node);
				list_move_tail(&desc->node, &pl330->desc_pool);
			पूर्ण

			list_move_tail(&first->node, &pl330->desc_pool);

			spin_unlock_irqrestore(&pl330->pool_lock, अगरlags);

			वापस शून्य;
		पूर्ण

		चयन (direction) अणु
		हाल DMA_MEM_TO_DEV:
			desc->rqcfg.src_inc = 1;
			desc->rqcfg.dst_inc = 0;
			src = dma_addr;
			dst = pch->fअगरo_dma;
			अवरोध;
		हाल DMA_DEV_TO_MEM:
			desc->rqcfg.src_inc = 0;
			desc->rqcfg.dst_inc = 1;
			src = pch->fअगरo_dma;
			dst = dma_addr;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		desc->rqtype = direction;
		desc->rqcfg.brst_size = pch->burst_sz;
		desc->rqcfg.brst_len = pch->burst_len;
		desc->bytes_requested = period_len;
		fill_px(&desc->px, dst, src, period_len);

		अगर (!first)
			first = desc;
		अन्यथा
			list_add_tail(&desc->node, &first->node);

		dma_addr += period_len;
	पूर्ण

	अगर (!desc)
		वापस शून्य;

	pch->cyclic = true;
	desc->txd.flags = flags;

	वापस &desc->txd;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
pl330_prep_dma_स_नकल(काष्ठा dma_chan *chan, dma_addr_t dst,
		dma_addr_t src, माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा dma_pl330_desc *desc;
	काष्ठा dma_pl330_chan *pch = to_pchan(chan);
	काष्ठा pl330_dmac *pl330;
	पूर्णांक burst;

	अगर (unlikely(!pch || !len))
		वापस शून्य;

	pl330 = pch->dmac;

	desc = __pl330_prep_dma_स_नकल(pch, dst, src, len);
	अगर (!desc)
		वापस शून्य;

	desc->rqcfg.src_inc = 1;
	desc->rqcfg.dst_inc = 1;
	desc->rqtype = DMA_MEM_TO_MEM;

	/* Select max possible burst size */
	burst = pl330->pcfg.data_bus_width / 8;

	/*
	 * Make sure we use a burst size that aligns with all the स_नकल
	 * parameters because our DMA programming algorithm करोesn't cope with
	 * transfers which straddle an entry in the DMA device's MFIFO.
	 */
	जबतक ((src | dst | len) & (burst - 1))
		burst /= 2;

	desc->rqcfg.brst_size = 0;
	जबतक (burst != (1 << desc->rqcfg.brst_size))
		desc->rqcfg.brst_size++;

	desc->rqcfg.brst_len = get_burst_len(desc, len);
	/*
	 * If burst size is smaller than bus width then make sure we only
	 * transfer one at a समय to aव्योम a burst stradling an MFIFO entry.
	 */
	अगर (burst * 8 < pl330->pcfg.data_bus_width)
		desc->rqcfg.brst_len = 1;

	desc->bytes_requested = len;

	desc->txd.flags = flags;

	वापस &desc->txd;
पूर्ण

अटल व्योम __pl330_giveback_desc(काष्ठा pl330_dmac *pl330,
				  काष्ठा dma_pl330_desc *first)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा dma_pl330_desc *desc;

	अगर (!first)
		वापस;

	spin_lock_irqsave(&pl330->pool_lock, flags);

	जबतक (!list_empty(&first->node)) अणु
		desc = list_entry(first->node.next,
				काष्ठा dma_pl330_desc, node);
		list_move_tail(&desc->node, &pl330->desc_pool);
	पूर्ण

	list_move_tail(&first->node, &pl330->desc_pool);

	spin_unlock_irqrestore(&pl330->pool_lock, flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
pl330_prep_slave_sg(काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl,
		अचिन्हित पूर्णांक sg_len, क्रमागत dma_transfer_direction direction,
		अचिन्हित दीर्घ flg, व्योम *context)
अणु
	काष्ठा dma_pl330_desc *first, *desc = शून्य;
	काष्ठा dma_pl330_chan *pch = to_pchan(chan);
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	अगर (unlikely(!pch || !sgl || !sg_len))
		वापस शून्य;

	pl330_config_ग_लिखो(chan, &pch->slave_config, direction);

	अगर (!pl330_prep_slave_fअगरo(pch, direction))
		वापस शून्य;

	first = शून्य;

	क्रम_each_sg(sgl, sg, sg_len, i) अणु

		desc = pl330_get_desc(pch);
		अगर (!desc) अणु
			काष्ठा pl330_dmac *pl330 = pch->dmac;

			dev_err(pch->dmac->ddma.dev,
				"%s:%d Unable to fetch desc\n",
				__func__, __LINE__);
			__pl330_giveback_desc(pl330, first);

			वापस शून्य;
		पूर्ण

		अगर (!first)
			first = desc;
		अन्यथा
			list_add_tail(&desc->node, &first->node);

		अगर (direction == DMA_MEM_TO_DEV) अणु
			desc->rqcfg.src_inc = 1;
			desc->rqcfg.dst_inc = 0;
			fill_px(&desc->px, pch->fअगरo_dma, sg_dma_address(sg),
				sg_dma_len(sg));
		पूर्ण अन्यथा अणु
			desc->rqcfg.src_inc = 0;
			desc->rqcfg.dst_inc = 1;
			fill_px(&desc->px, sg_dma_address(sg), pch->fअगरo_dma,
				sg_dma_len(sg));
		पूर्ण

		desc->rqcfg.brst_size = pch->burst_sz;
		desc->rqcfg.brst_len = pch->burst_len;
		desc->rqtype = direction;
		desc->bytes_requested = sg_dma_len(sg);
	पूर्ण

	/* Return the last desc in the chain */
	desc->txd.flags = flg;
	वापस &desc->txd;
पूर्ण

अटल irqवापस_t pl330_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	अगर (pl330_update(data))
		वापस IRQ_HANDLED;
	अन्यथा
		वापस IRQ_NONE;
पूर्ण

#घोषणा PL330_DMA_BUSWIDTHS \
	BIT(DMA_SLAVE_BUSWIDTH_UNDEFINED) | \
	BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) | \
	BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) | \
	BIT(DMA_SLAVE_BUSWIDTH_4_BYTES) | \
	BIT(DMA_SLAVE_BUSWIDTH_8_BYTES)

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक pl330_debugfs_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा pl330_dmac *pl330 = s->निजी;
	पूर्णांक chans, pchs, ch, pr;

	chans = pl330->pcfg.num_chan;
	pchs = pl330->num_peripherals;

	seq_माला_दो(s, "PL330 physical channels:\n");
	seq_माला_दो(s, "THREAD:\t\tCHANNEL:\n");
	seq_माला_दो(s, "--------\t-----\n");
	क्रम (ch = 0; ch < chans; ch++) अणु
		काष्ठा pl330_thपढ़ो *thrd = &pl330->channels[ch];
		पूर्णांक found = -1;

		क्रम (pr = 0; pr < pchs; pr++) अणु
			काष्ठा dma_pl330_chan *pch = &pl330->peripherals[pr];

			अगर (!pch->thपढ़ो || thrd->id != pch->thपढ़ो->id)
				जारी;

			found = pr;
		पूर्ण

		seq_म_लिखो(s, "%d\t\t", thrd->id);
		अगर (found == -1)
			seq_माला_दो(s, "--\n");
		अन्यथा
			seq_म_लिखो(s, "%d\n", found);
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(pl330_debugfs);

अटल अंतरभूत व्योम init_pl330_debugfs(काष्ठा pl330_dmac *pl330)
अणु
	debugfs_create_file(dev_name(pl330->ddma.dev),
			    S_IFREG | 0444, शून्य, pl330,
			    &pl330_debugfs_fops);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम init_pl330_debugfs(काष्ठा pl330_dmac *pl330)
अणु
पूर्ण
#पूर्ण_अगर

/*
 * Runसमय PM callbacks are provided by amba/bus.c driver.
 *
 * It is assumed here that IRQ safe runसमय PM is chosen in probe and amba
 * bus driver will only disable/enable the घड़ी in runसमय PM callbacks.
 */
अटल पूर्णांक __maybe_unused pl330_suspend(काष्ठा device *dev)
अणु
	काष्ठा amba_device *pcdev = to_amba_device(dev);

	pm_runसमय_क्रमce_suspend(dev);
	amba_pclk_unprepare(pcdev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused pl330_resume(काष्ठा device *dev)
अणु
	काष्ठा amba_device *pcdev = to_amba_device(dev);
	पूर्णांक ret;

	ret = amba_pclk_prepare(pcdev);
	अगर (ret)
		वापस ret;

	pm_runसमय_क्रमce_resume(dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops pl330_pm = अणु
	SET_LATE_SYSTEM_SLEEP_PM_OPS(pl330_suspend, pl330_resume)
पूर्ण;

अटल पूर्णांक
pl330_probe(काष्ठा amba_device *adev, स्थिर काष्ठा amba_id *id)
अणु
	काष्ठा pl330_config *pcfg;
	काष्ठा pl330_dmac *pl330;
	काष्ठा dma_pl330_chan *pch, *_p;
	काष्ठा dma_device *pd;
	काष्ठा resource *res;
	पूर्णांक i, ret, irq;
	पूर्णांक num_chan;
	काष्ठा device_node *np = adev->dev.of_node;

	ret = dma_set_mask_and_coherent(&adev->dev, DMA_BIT_MASK(32));
	अगर (ret)
		वापस ret;

	/* Allocate a new DMAC and its Channels */
	pl330 = devm_kzalloc(&adev->dev, माप(*pl330), GFP_KERNEL);
	अगर (!pl330)
		वापस -ENOMEM;

	pd = &pl330->ddma;
	pd->dev = &adev->dev;

	pl330->mcbufsz = 0;

	/* get quirk */
	क्रम (i = 0; i < ARRAY_SIZE(of_quirks); i++)
		अगर (of_property_पढ़ो_bool(np, of_quirks[i].quirk))
			pl330->quirks |= of_quirks[i].id;

	res = &adev->res;
	pl330->base = devm_ioremap_resource(&adev->dev, res);
	अगर (IS_ERR(pl330->base))
		वापस PTR_ERR(pl330->base);

	amba_set_drvdata(adev, pl330);

	pl330->rstc = devm_reset_control_get_optional(&adev->dev, "dma");
	अगर (IS_ERR(pl330->rstc)) अणु
		वापस dev_err_probe(&adev->dev, PTR_ERR(pl330->rstc), "Failed to get reset!\n");
	पूर्ण अन्यथा अणु
		ret = reset_control_deनिश्चित(pl330->rstc);
		अगर (ret) अणु
			dev_err(&adev->dev, "Couldn't deassert the device from reset!\n");
			वापस ret;
		पूर्ण
	पूर्ण

	pl330->rstc_ocp = devm_reset_control_get_optional(&adev->dev, "dma-ocp");
	अगर (IS_ERR(pl330->rstc_ocp)) अणु
		वापस dev_err_probe(&adev->dev, PTR_ERR(pl330->rstc_ocp),
				     "Failed to get OCP reset!\n");
	पूर्ण अन्यथा अणु
		ret = reset_control_deनिश्चित(pl330->rstc_ocp);
		अगर (ret) अणु
			dev_err(&adev->dev, "Couldn't deassert the device from OCP reset!\n");
			वापस ret;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < AMBA_NR_IRQS; i++) अणु
		irq = adev->irq[i];
		अगर (irq) अणु
			ret = devm_request_irq(&adev->dev, irq,
					       pl330_irq_handler, 0,
					       dev_name(&adev->dev), pl330);
			अगर (ret)
				वापस ret;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण

	pcfg = &pl330->pcfg;

	pcfg->periph_id = adev->periphid;
	ret = pl330_add(pl330);
	अगर (ret)
		वापस ret;

	INIT_LIST_HEAD(&pl330->desc_pool);
	spin_lock_init(&pl330->pool_lock);

	/* Create a descriptor pool of शेष size */
	अगर (!add_desc(&pl330->desc_pool, &pl330->pool_lock,
		      GFP_KERNEL, NR_DEFAULT_DESC))
		dev_warn(&adev->dev, "unable to allocate desc\n");

	INIT_LIST_HEAD(&pd->channels);

	/* Initialize channel parameters */
	num_chan = max_t(पूर्णांक, pcfg->num_peri, pcfg->num_chan);

	pl330->num_peripherals = num_chan;

	pl330->peripherals = kसुस्मृति(num_chan, माप(*pch), GFP_KERNEL);
	अगर (!pl330->peripherals) अणु
		ret = -ENOMEM;
		जाओ probe_err2;
	पूर्ण

	क्रम (i = 0; i < num_chan; i++) अणु
		pch = &pl330->peripherals[i];

		pch->chan.निजी = adev->dev.of_node;
		INIT_LIST_HEAD(&pch->submitted_list);
		INIT_LIST_HEAD(&pch->work_list);
		INIT_LIST_HEAD(&pch->completed_list);
		spin_lock_init(&pch->lock);
		pch->thपढ़ो = शून्य;
		pch->chan.device = pd;
		pch->dmac = pl330;
		pch->dir = DMA_NONE;

		/* Add the channel to the DMAC list */
		list_add_tail(&pch->chan.device_node, &pd->channels);
	पूर्ण

	dma_cap_set(DMA_MEMCPY, pd->cap_mask);
	अगर (pcfg->num_peri) अणु
		dma_cap_set(DMA_SLAVE, pd->cap_mask);
		dma_cap_set(DMA_CYCLIC, pd->cap_mask);
		dma_cap_set(DMA_PRIVATE, pd->cap_mask);
	पूर्ण

	pd->device_alloc_chan_resources = pl330_alloc_chan_resources;
	pd->device_मुक्त_chan_resources = pl330_मुक्त_chan_resources;
	pd->device_prep_dma_स_नकल = pl330_prep_dma_स_नकल;
	pd->device_prep_dma_cyclic = pl330_prep_dma_cyclic;
	pd->device_tx_status = pl330_tx_status;
	pd->device_prep_slave_sg = pl330_prep_slave_sg;
	pd->device_config = pl330_config;
	pd->device_छोड़ो = pl330_छोड़ो;
	pd->device_terminate_all = pl330_terminate_all;
	pd->device_issue_pending = pl330_issue_pending;
	pd->src_addr_widths = PL330_DMA_BUSWIDTHS;
	pd->dst_addr_widths = PL330_DMA_BUSWIDTHS;
	pd->directions = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	pd->residue_granularity = DMA_RESIDUE_GRANULARITY_BURST;
	pd->max_burst = PL330_MAX_BURST;

	ret = dma_async_device_रेजिस्टर(pd);
	अगर (ret) अणु
		dev_err(&adev->dev, "unable to register DMAC\n");
		जाओ probe_err3;
	पूर्ण

	अगर (adev->dev.of_node) अणु
		ret = of_dma_controller_रेजिस्टर(adev->dev.of_node,
					 of_dma_pl330_xlate, pl330);
		अगर (ret) अणु
			dev_err(&adev->dev,
			"unable to register DMA to the generic DT DMA helpers\n");
		पूर्ण
	पूर्ण

	/*
	 * This is the limit क्रम transfers with a buswidth of 1, larger
	 * buswidths will have larger limits.
	 */
	ret = dma_set_max_seg_size(&adev->dev, 1900800);
	अगर (ret)
		dev_err(&adev->dev, "unable to set the seg size\n");


	init_pl330_debugfs(pl330);
	dev_info(&adev->dev,
		"Loaded driver for PL330 DMAC-%x\n", adev->periphid);
	dev_info(&adev->dev,
		"\tDBUFF-%ux%ubytes Num_Chans-%u Num_Peri-%u Num_Events-%u\n",
		pcfg->data_buf_dep, pcfg->data_bus_width / 8, pcfg->num_chan,
		pcfg->num_peri, pcfg->num_events);

	pm_runसमय_irq_safe(&adev->dev);
	pm_runसमय_use_स्वतःsuspend(&adev->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&adev->dev, PL330_AUTOSUSPEND_DELAY);
	pm_runसमय_mark_last_busy(&adev->dev);
	pm_runसमय_put_स्वतःsuspend(&adev->dev);

	वापस 0;
probe_err3:
	/* Idle the DMAC */
	list_क्रम_each_entry_safe(pch, _p, &pl330->ddma.channels,
			chan.device_node) अणु

		/* Remove the channel */
		list_del(&pch->chan.device_node);

		/* Flush the channel */
		अगर (pch->thपढ़ो) अणु
			pl330_terminate_all(&pch->chan);
			pl330_मुक्त_chan_resources(&pch->chan);
		पूर्ण
	पूर्ण
probe_err2:
	pl330_del(pl330);

	अगर (pl330->rstc_ocp)
		reset_control_निश्चित(pl330->rstc_ocp);

	अगर (pl330->rstc)
		reset_control_निश्चित(pl330->rstc);
	वापस ret;
पूर्ण

अटल व्योम pl330_हटाओ(काष्ठा amba_device *adev)
अणु
	काष्ठा pl330_dmac *pl330 = amba_get_drvdata(adev);
	काष्ठा dma_pl330_chan *pch, *_p;
	पूर्णांक i, irq;

	pm_runसमय_get_noresume(pl330->ddma.dev);

	अगर (adev->dev.of_node)
		of_dma_controller_मुक्त(adev->dev.of_node);

	क्रम (i = 0; i < AMBA_NR_IRQS; i++) अणु
		irq = adev->irq[i];
		अगर (irq)
			devm_मुक्त_irq(&adev->dev, irq, pl330);
	पूर्ण

	dma_async_device_unरेजिस्टर(&pl330->ddma);

	/* Idle the DMAC */
	list_क्रम_each_entry_safe(pch, _p, &pl330->ddma.channels,
			chan.device_node) अणु

		/* Remove the channel */
		list_del(&pch->chan.device_node);

		/* Flush the channel */
		अगर (pch->thपढ़ो) अणु
			pl330_terminate_all(&pch->chan);
			pl330_मुक्त_chan_resources(&pch->chan);
		पूर्ण
	पूर्ण

	pl330_del(pl330);

	अगर (pl330->rstc_ocp)
		reset_control_निश्चित(pl330->rstc_ocp);

	अगर (pl330->rstc)
		reset_control_निश्चित(pl330->rstc);
पूर्ण

अटल स्थिर काष्ठा amba_id pl330_ids[] = अणु
	अणु
		.id	= 0x00041330,
		.mask	= 0x000fffff,
	पूर्ण,
	अणु 0, 0 पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(amba, pl330_ids);

अटल काष्ठा amba_driver pl330_driver = अणु
	.drv = अणु
		.owner = THIS_MODULE,
		.name = "dma-pl330",
		.pm = &pl330_pm,
	पूर्ण,
	.id_table = pl330_ids,
	.probe = pl330_probe,
	.हटाओ = pl330_हटाओ,
पूर्ण;

module_amba_driver(pl330_driver);

MODULE_AUTHOR("Jaswinder Singh <jassisinghbrar@gmail.com>");
MODULE_DESCRIPTION("API Driver for PL330 DMAC");
MODULE_LICENSE("GPL");
