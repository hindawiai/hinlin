<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 2008 Roकरोlfo Giometti <giometti@linux.it>
 * Copyright (c) 2008 Eurotech S.p.A. <info@eurtech.it>
 *
 * This code is *strongly* based on EHCI-HCD code by David Brownell since
 * the chip is a quasi-EHCI compatible.
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/समयr.h>
#समावेश <linux/list.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <linux/irq.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा DRIVER_VERSION "0.0.50"

#घोषणा OXU_DEVICEID			0x00
	#घोषणा OXU_REV_MASK		0xffff0000
	#घोषणा OXU_REV_SHIFT		16
	#घोषणा OXU_REV_2100		0x2100
	#घोषणा OXU_BO_SHIFT		8
	#घोषणा OXU_BO_MASK		(0x3 << OXU_BO_SHIFT)
	#घोषणा OXU_MAJ_REV_SHIFT	4
	#घोषणा OXU_MAJ_REV_MASK	(0xf << OXU_MAJ_REV_SHIFT)
	#घोषणा OXU_MIN_REV_SHIFT	0
	#घोषणा OXU_MIN_REV_MASK	(0xf << OXU_MIN_REV_SHIFT)
#घोषणा OXU_HOSTIFCONFIG		0x04
#घोषणा OXU_SOFTRESET			0x08
	#घोषणा OXU_SRESET		(1 << 0)

#घोषणा OXU_PIOBURSTREADCTRL		0x0C

#घोषणा OXU_CHIPIRQSTATUS		0x10
#घोषणा OXU_CHIPIRQEN_SET		0x14
#घोषणा OXU_CHIPIRQEN_CLR		0x18
	#घोषणा OXU_USBSPHLPWUI		0x00000080
	#घोषणा OXU_USBOTGLPWUI		0x00000040
	#घोषणा OXU_USBSPHI		0x00000002
	#घोषणा OXU_USBOTGI		0x00000001

#घोषणा OXU_CLKCTRL_SET			0x1C
	#घोषणा OXU_SYSCLKEN		0x00000008
	#घोषणा OXU_USBSPHCLKEN		0x00000002
	#घोषणा OXU_USBOTGCLKEN		0x00000001

#घोषणा OXU_ASO				0x68
	#घोषणा OXU_SPHPOEN		0x00000100
	#घोषणा OXU_OVRCCURPUPDEN	0x00000800
	#घोषणा OXU_ASO_OP		(1 << 10)
	#घोषणा OXU_COMPARATOR		0x000004000

#घोषणा OXU_USBMODE			0x1A8
	#घोषणा OXU_VBPS		0x00000020
	#घोषणा OXU_ES_LITTLE		0x00000000
	#घोषणा OXU_CM_HOST_ONLY	0x00000003

/*
 * Proper EHCI काष्ठाs & defines
 */

/* Magic numbers that can affect प्रणाली perक्रमmance */
#घोषणा EHCI_TUNE_CERR		3	/* 0-3 qtd retries; 0 == करोn't stop */
#घोषणा EHCI_TUNE_RL_HS		4	/* nak throttle; see 4.9 */
#घोषणा EHCI_TUNE_RL_TT		0
#घोषणा EHCI_TUNE_MULT_HS	1	/* 1-3 transactions/uframe; 4.10.3 */
#घोषणा EHCI_TUNE_MULT_TT	1
#घोषणा EHCI_TUNE_FLS		2	/* (small) 256 frame schedule */

काष्ठा oxu_hcd;

/* EHCI रेजिस्टर पूर्णांकerface, corresponds to EHCI Revision 0.95 specअगरication */

/* Section 2.2 Host Controller Capability Registers */
काष्ठा ehci_caps अणु
	/* these fields are specअगरied as 8 and 16 bit रेजिस्टरs,
	 * but some hosts can't perक्रमm 8 or 16 bit PCI accesses.
	 */
	u32		hc_capbase;
#घोषणा HC_LENGTH(p)		(((p)>>00)&0x00ff)	/* bits 7:0 */
#घोषणा HC_VERSION(p)		(((p)>>16)&0xffff)	/* bits 31:16 */
	u32		hcs_params;     /* HCSPARAMS - offset 0x4 */
#घोषणा HCS_DEBUG_PORT(p)	(((p)>>20)&0xf)	/* bits 23:20, debug port? */
#घोषणा HCS_INDICATOR(p)	((p)&(1 << 16))	/* true: has port indicators */
#घोषणा HCS_N_CC(p)		(((p)>>12)&0xf)	/* bits 15:12, #companion HCs */
#घोषणा HCS_N_PCC(p)		(((p)>>8)&0xf)	/* bits 11:8, ports per CC */
#घोषणा HCS_PORTROUTED(p)	((p)&(1 << 7))	/* true: port routing */
#घोषणा HCS_PPC(p)		((p)&(1 << 4))	/* true: port घातer control */
#घोषणा HCS_N_PORTS(p)		(((p)>>0)&0xf)	/* bits 3:0, ports on HC */

	u32		hcc_params;      /* HCCPARAMS - offset 0x8 */
#घोषणा HCC_EXT_CAPS(p)		(((p)>>8)&0xff)	/* क्रम pci extended caps */
#घोषणा HCC_ISOC_CACHE(p)       ((p)&(1 << 7))  /* true: can cache isoc frame */
#घोषणा HCC_ISOC_THRES(p)       (((p)>>4)&0x7)  /* bits 6:4, uframes cached */
#घोषणा HCC_CANPARK(p)		((p)&(1 << 2))  /* true: can park on async qh */
#घोषणा HCC_PGM_FRAMELISTLEN(p) ((p)&(1 << 1))  /* true: periodic_size changes*/
#घोषणा HCC_64BIT_ADDR(p)       ((p)&(1))       /* true: can use 64-bit addr */
	u8		portroute[8];	 /* nibbles क्रम routing - offset 0xC */
पूर्ण __packed;


/* Section 2.3 Host Controller Operational Registers */
काष्ठा ehci_regs अणु
	/* USBCMD: offset 0x00 */
	u32		command;
/* 23:16 is r/w पूर्णांकr rate, in microframes; शेष "8" == 1/msec */
#घोषणा CMD_PARK	(1<<11)		/* enable "park" on async qh */
#घोषणा CMD_PARK_CNT(c)	(((c)>>8)&3)	/* how many transfers to park क्रम */
#घोषणा CMD_LRESET	(1<<7)		/* partial reset (no ports, etc) */
#घोषणा CMD_IAAD	(1<<6)		/* "doorbell" पूर्णांकerrupt async advance */
#घोषणा CMD_ASE		(1<<5)		/* async schedule enable */
#घोषणा CMD_PSE		(1<<4)		/* periodic schedule enable */
/* 3:2 is periodic frame list size */
#घोषणा CMD_RESET	(1<<1)		/* reset HC not bus */
#घोषणा CMD_RUN		(1<<0)		/* start/stop HC */

	/* USBSTS: offset 0x04 */
	u32		status;
#घोषणा STS_ASS		(1<<15)		/* Async Schedule Status */
#घोषणा STS_PSS		(1<<14)		/* Periodic Schedule Status */
#घोषणा STS_RECL	(1<<13)		/* Reclamation */
#घोषणा STS_HALT	(1<<12)		/* Not running (any reason) */
/* some bits reserved */
	/* these STS_* flags are also पूर्णांकr_enable bits (USBINTR) */
#घोषणा STS_IAA		(1<<5)		/* Interrupted on async advance */
#घोषणा STS_FATAL	(1<<4)		/* such as some PCI access errors */
#घोषणा STS_FLR		(1<<3)		/* frame list rolled over */
#घोषणा STS_PCD		(1<<2)		/* port change detect */
#घोषणा STS_ERR		(1<<1)		/* "error" completion (overflow, ...) */
#घोषणा STS_INT		(1<<0)		/* "normal" completion (लघु, ...) */

#घोषणा INTR_MASK (STS_IAA | STS_FATAL | STS_PCD | STS_ERR | STS_INT)

	/* USBINTR: offset 0x08 */
	u32		पूर्णांकr_enable;

	/* FRINDEX: offset 0x0C */
	u32		frame_index;	/* current microframe number */
	/* CTRLDSSEGMENT: offset 0x10 */
	u32		segment;	/* address bits 63:32 अगर needed */
	/* PERIODICLISTBASE: offset 0x14 */
	u32		frame_list;	/* poपूर्णांकs to periodic list */
	/* ASYNCLISTADDR: offset 0x18 */
	u32		async_next;	/* address of next async queue head */

	u32		reserved[9];

	/* CONFIGFLAG: offset 0x40 */
	u32		configured_flag;
#घोषणा FLAG_CF		(1<<0)		/* true: we'll support "high speed" */

	/* PORTSC: offset 0x44 */
	u32		port_status[0];	/* up to N_PORTS */
/* 31:23 reserved */
#घोषणा PORT_WKOC_E	(1<<22)		/* wake on overcurrent (enable) */
#घोषणा PORT_WKDISC_E	(1<<21)		/* wake on disconnect (enable) */
#घोषणा PORT_WKCONN_E	(1<<20)		/* wake on connect (enable) */
/* 19:16 क्रम port testing */
#घोषणा PORT_LED_OFF	(0<<14)
#घोषणा PORT_LED_AMBER	(1<<14)
#घोषणा PORT_LED_GREEN	(2<<14)
#घोषणा PORT_LED_MASK	(3<<14)
#घोषणा PORT_OWNER	(1<<13)		/* true: companion hc owns this port */
#घोषणा PORT_POWER	(1<<12)		/* true: has घातer (see PPC) */
#घोषणा PORT_USB11(x) (((x)&(3<<10)) == (1<<10))	/* USB 1.1 device */
/* 11:10 क्रम detecting lowspeed devices (reset vs release ownership) */
/* 9 reserved */
#घोषणा PORT_RESET	(1<<8)		/* reset port */
#घोषणा PORT_SUSPEND	(1<<7)		/* suspend port */
#घोषणा PORT_RESUME	(1<<6)		/* resume it */
#घोषणा PORT_OCC	(1<<5)		/* over current change */
#घोषणा PORT_OC		(1<<4)		/* over current active */
#घोषणा PORT_PEC	(1<<3)		/* port enable change */
#घोषणा PORT_PE		(1<<2)		/* port enable */
#घोषणा PORT_CSC	(1<<1)		/* connect status change */
#घोषणा PORT_CONNECT	(1<<0)		/* device connected */
#घोषणा PORT_RWC_BITS   (PORT_CSC | PORT_PEC | PORT_OCC)
पूर्ण __packed;

/* Appendix C, Debug port ... पूर्णांकended क्रम use with special "debug devices"
 * that can help अगर there's no serial console.  (nonstandard क्रमागतeration.)
 */
काष्ठा ehci_dbg_port अणु
	u32	control;
#घोषणा DBGP_OWNER	(1<<30)
#घोषणा DBGP_ENABLED	(1<<28)
#घोषणा DBGP_DONE	(1<<16)
#घोषणा DBGP_INUSE	(1<<10)
#घोषणा DBGP_ERRCODE(x)	(((x)>>7)&0x07)
#	define DBGP_ERR_BAD	1
#	define DBGP_ERR_SIGNAL	2
#घोषणा DBGP_ERROR	(1<<6)
#घोषणा DBGP_GO		(1<<5)
#घोषणा DBGP_OUT	(1<<4)
#घोषणा DBGP_LEN(x)	(((x)>>0)&0x0f)
	u32	pids;
#घोषणा DBGP_PID_GET(x)		(((x)>>16)&0xff)
#घोषणा DBGP_PID_SET(data, tok)	(((data)<<8)|(tok))
	u32	data03;
	u32	data47;
	u32	address;
#घोषणा DBGP_EPADDR(dev, ep)	(((dev)<<8)|(ep))
पूर्ण __packed;

#घोषणा	QTD_NEXT(dma)	cpu_to_le32((u32)dma)

/*
 * EHCI Specअगरication 0.95 Section 3.5
 * QTD: describe data transfer components (buffer, direction, ...)
 * See Fig 3-6 "Queue Element Transfer Descriptor Block Diagram".
 *
 * These are associated only with "QH" (Queue Head) काष्ठाures,
 * used with control, bulk, and पूर्णांकerrupt transfers.
 */
काष्ठा ehci_qtd अणु
	/* first part defined by EHCI spec */
	__le32			hw_next;		/* see EHCI 3.5.1 */
	__le32			hw_alt_next;		/* see EHCI 3.5.2 */
	__le32			hw_token;		/* see EHCI 3.5.3 */
#घोषणा	QTD_TOGGLE	(1 << 31)	/* data toggle */
#घोषणा	QTD_LENGTH(tok)	(((tok)>>16) & 0x7fff)
#घोषणा	QTD_IOC		(1 << 15)	/* पूर्णांकerrupt on complete */
#घोषणा	QTD_CERR(tok)	(((tok)>>10) & 0x3)
#घोषणा	QTD_PID(tok)	(((tok)>>8) & 0x3)
#घोषणा	QTD_STS_ACTIVE	(1 << 7)	/* HC may execute this */
#घोषणा	QTD_STS_HALT	(1 << 6)	/* halted on error */
#घोषणा	QTD_STS_DBE	(1 << 5)	/* data buffer error (in HC) */
#घोषणा	QTD_STS_BABBLE	(1 << 4)	/* device was babbling (qtd halted) */
#घोषणा	QTD_STS_XACT	(1 << 3)	/* device gave illegal response */
#घोषणा	QTD_STS_MMF	(1 << 2)	/* incomplete split transaction */
#घोषणा	QTD_STS_STS	(1 << 1)	/* split transaction state */
#घोषणा	QTD_STS_PING	(1 << 0)	/* issue PING? */
	__le32			hw_buf[5];		/* see EHCI 3.5.4 */
	__le32			hw_buf_hi[5];		/* Appendix B */

	/* the rest is HCD-निजी */
	dma_addr_t		qtd_dma;		/* qtd address */
	काष्ठा list_head	qtd_list;		/* sw qtd list */
	काष्ठा urb		*urb;			/* qtd's urb */
	माप_प्रकार			length;			/* length of buffer */

	u32			qtd_buffer_len;
	व्योम			*buffer;
	dma_addr_t		buffer_dma;
	व्योम			*transfer_buffer;
	व्योम			*transfer_dma;
पूर्ण __aligned(32);

/* mask NakCnt+T in qh->hw_alt_next */
#घोषणा QTD_MASK cpu_to_le32 (~0x1f)

#घोषणा IS_SHORT_READ(token) (QTD_LENGTH(token) != 0 && QTD_PID(token) == 1)

/* Type tag from अणुqh, itd, sitd, fstnपूर्ण->hw_next */
#घोषणा Q_NEXT_TYPE(dma) ((dma) & cpu_to_le32 (3 << 1))

/* values क्रम that type tag */
#घोषणा Q_TYPE_QH	cpu_to_le32 (1 << 1)

/* next async queue entry, or poपूर्णांकer to पूर्णांकerrupt/periodic QH */
#घोषणा	QH_NEXT(dma)	(cpu_to_le32(((u32)dma)&~0x01f)|Q_TYPE_QH)

/* क्रम periodic/async schedules and qtd lists, mark end of list */
#घोषणा	EHCI_LIST_END	cpu_to_le32(1) /* "null pointer" to hw */

/*
 * Entries in periodic shaकरोw table are poपूर्णांकers to one of four kinds
 * of data काष्ठाure.  That's dictated by the hardware; a type tag is
 * encoded in the low bits of the hardware's periodic schedule.  Use
 * Q_NEXT_TYPE to get the tag.
 *
 * For entries in the async schedule, the type tag always says "qh".
 */
जोड़ ehci_shaकरोw अणु
	काष्ठा ehci_qh		*qh;		/* Q_TYPE_QH */
	__le32			*hw_next;	/* (all types) */
	व्योम			*ptr;
पूर्ण;

/*
 * EHCI Specअगरication 0.95 Section 3.6
 * QH: describes control/bulk/पूर्णांकerrupt endpoपूर्णांकs
 * See Fig 3-7 "Queue Head Structure Layout".
 *
 * These appear in both the async and (क्रम पूर्णांकerrupt) periodic schedules.
 */

काष्ठा ehci_qh अणु
	/* first part defined by EHCI spec */
	__le32			hw_next;	 /* see EHCI 3.6.1 */
	__le32			hw_info1;	/* see EHCI 3.6.2 */
#घोषणा	QH_HEAD		0x00008000
	__le32			hw_info2;	/* see EHCI 3.6.2 */
#घोषणा	QH_SMASK	0x000000ff
#घोषणा	QH_CMASK	0x0000ff00
#घोषणा	QH_HUBADDR	0x007f0000
#घोषणा	QH_HUBPORT	0x3f800000
#घोषणा	QH_MULT		0xc0000000
	__le32			hw_current;	 /* qtd list - see EHCI 3.6.4 */

	/* qtd overlay (hardware parts of a काष्ठा ehci_qtd) */
	__le32			hw_qtd_next;
	__le32			hw_alt_next;
	__le32			hw_token;
	__le32			hw_buf[5];
	__le32			hw_buf_hi[5];

	/* the rest is HCD-निजी */
	dma_addr_t		qh_dma;		/* address of qh */
	जोड़ ehci_shaकरोw	qh_next;	/* ptr to qh; or periodic */
	काष्ठा list_head	qtd_list;	/* sw qtd list */
	काष्ठा ehci_qtd		*dummy;
	काष्ठा ehci_qh		*reclaim;	/* next to reclaim */

	काष्ठा oxu_hcd		*oxu;
	काष्ठा kref		kref;
	अचिन्हित पूर्णांक		stamp;

	u8			qh_state;
#घोषणा	QH_STATE_LINKED		1		/* HC sees this */
#घोषणा	QH_STATE_UNLINK		2		/* HC may still see this */
#घोषणा	QH_STATE_IDLE		3		/* HC करोesn't see this */
#घोषणा	QH_STATE_UNLINK_WAIT	4		/* LINKED and on reclaim q */
#घोषणा	QH_STATE_COMPLETING	5		/* करोn't touch token.HALT */

	/* periodic schedule info */
	u8			usecs;		/* पूर्णांकr bandwidth */
	u8			gap_uf;		/* uframes split/csplit gap */
	u8			c_usecs;	/* ... split completion bw */
	u16			tt_usecs;	/* tt करोwnstream bandwidth */
	अचिन्हित लघु		period;		/* polling पूर्णांकerval */
	अचिन्हित लघु		start;		/* where polling starts */
#घोषणा NO_FRAME ((अचिन्हित लघु)~0)			/* pick new start */
	काष्ठा usb_device	*dev;		/* access to TT */
पूर्ण __aligned(32);

/*
 * Proper OXU210HP काष्ठाs
 */

#घोषणा OXU_OTG_CORE_OFFSET	0x00400
#घोषणा OXU_OTG_CAP_OFFSET	(OXU_OTG_CORE_OFFSET + 0x100)
#घोषणा OXU_SPH_CORE_OFFSET	0x00800
#घोषणा OXU_SPH_CAP_OFFSET	(OXU_SPH_CORE_OFFSET + 0x100)

#घोषणा OXU_OTG_MEM		0xE000
#घोषणा OXU_SPH_MEM		0x16000

/* Only how many elements & element काष्ठाure are specअगरies here. */
/* 2 host controllers are enabled - total size <= 28 kbytes */
#घोषणा	DEFAULT_I_TDPS		1024
#घोषणा QHEAD_NUM		16
#घोषणा QTD_NUM			32
#घोषणा SITD_NUM		8
#घोषणा MURB_NUM		8

#घोषणा BUFFER_NUM		8
#घोषणा BUFFER_SIZE		512

काष्ठा oxu_info अणु
	काष्ठा usb_hcd *hcd[2];
पूर्ण;

काष्ठा oxu_buf अणु
	u8			buffer[BUFFER_SIZE];
पूर्ण __aligned(BUFFER_SIZE);

काष्ठा oxu_onchip_mem अणु
	काष्ठा oxu_buf		db_pool[BUFFER_NUM];

	u32			frame_list[DEFAULT_I_TDPS];
	काष्ठा ehci_qh		qh_pool[QHEAD_NUM];
	काष्ठा ehci_qtd		qtd_pool[QTD_NUM];
पूर्ण __aligned(4 << 10);

#घोषणा	EHCI_MAX_ROOT_PORTS	15		/* see HCS_N_PORTS */

काष्ठा oxu_murb अणु
	काष्ठा urb		urb;
	काष्ठा urb		*मुख्य;
	u8			last;
पूर्ण;

काष्ठा oxu_hcd अणु				/* one per controller */
	अचिन्हित पूर्णांक		is_otg:1;

	u8			qh_used[QHEAD_NUM];
	u8			qtd_used[QTD_NUM];
	u8			db_used[BUFFER_NUM];
	u8			murb_used[MURB_NUM];

	काष्ठा oxu_onchip_mem	__iomem *mem;
	spinlock_t		mem_lock;

	काष्ठा समयr_list	urb_समयr;

	काष्ठा ehci_caps __iomem *caps;
	काष्ठा ehci_regs __iomem *regs;

	u32			hcs_params;	/* cached रेजिस्टर copy */
	spinlock_t		lock;

	/* async schedule support */
	काष्ठा ehci_qh		*async;
	काष्ठा ehci_qh		*reclaim;
	अचिन्हित पूर्णांक		reclaim_पढ़ोy:1;
	अचिन्हित पूर्णांक		scanning:1;

	/* periodic schedule support */
	अचिन्हित पूर्णांक		periodic_size;
	__le32			*periodic;	/* hw periodic table */
	dma_addr_t		periodic_dma;
	अचिन्हित पूर्णांक		i_thresh;	/* uframes HC might cache */

	जोड़ ehci_shaकरोw	*pshaकरोw;	/* mirror hw periodic table */
	पूर्णांक			next_uframe;	/* scan periodic, start here */
	अचिन्हित पूर्णांक		periodic_sched;	/* periodic activity count */

	/* per root hub port */
	अचिन्हित दीर्घ		reset_करोne[EHCI_MAX_ROOT_PORTS];
	/* bit vectors (one bit per port) */
	अचिन्हित दीर्घ		bus_suspended;	/* which ports were
						 * alपढ़ोy suspended at the
						 * start of a bus suspend
						 */
	अचिन्हित दीर्घ		companion_ports;/* which ports are dedicated
						 * to the companion controller
						 */

	काष्ठा समयr_list	watchकरोg;
	अचिन्हित दीर्घ		actions;
	अचिन्हित पूर्णांक		stamp;
	अचिन्हित दीर्घ		next_statechange;
	u32			command;

	/* SILICON QUIRKS */
	काष्ठा list_head	urb_list;	/* this is the head to urb
						 * queue that didn't get enough
						 * resources
						 */
	काष्ठा oxu_murb		*murb_pool;	/* murb per split big urb */
	अचिन्हित पूर्णांक		urb_len;

	u8			sbrn;		/* packed release number */
पूर्ण;

#घोषणा EHCI_IAA_JIFFIES	(HZ/100)	/* arbitrary; ~10 msec */
#घोषणा EHCI_IO_JIFFIES		(HZ/10)		/* io watchकरोg > irq_thresh */
#घोषणा EHCI_ASYNC_JIFFIES      (HZ/20)		/* async idle समयout */
#घोषणा EHCI_SHRINK_JIFFIES     (HZ/200)	/* async qh unlink delay */

क्रमागत ehci_समयr_action अणु
	TIMER_IO_WATCHDOG,
	TIMER_IAA_WATCHDOG,
	TIMER_ASYNC_SHRINK,
	TIMER_ASYNC_OFF,
पूर्ण;

/*
 * Main defines
 */

#घोषणा oxu_dbg(oxu, fmt, args...) \
		dev_dbg(oxu_to_hcd(oxu)->self.controller , fmt , ## args)
#घोषणा oxu_err(oxu, fmt, args...) \
		dev_err(oxu_to_hcd(oxu)->self.controller , fmt , ## args)
#घोषणा oxu_info(oxu, fmt, args...) \
		dev_info(oxu_to_hcd(oxu)->self.controller , fmt , ## args)

#अगर_घोषित CONFIG_DYNAMIC_DEBUG
#घोषणा DEBUG
#पूर्ण_अगर

अटल अंतरभूत काष्ठा usb_hcd *oxu_to_hcd(काष्ठा oxu_hcd *oxu)
अणु
	वापस container_of((व्योम *) oxu, काष्ठा usb_hcd, hcd_priv);
पूर्ण

अटल अंतरभूत काष्ठा oxu_hcd *hcd_to_oxu(काष्ठा usb_hcd *hcd)
अणु
	वापस (काष्ठा oxu_hcd *) (hcd->hcd_priv);
पूर्ण

/*
 * Debug stuff
 */

#अघोषित OXU_URB_TRACE
#अघोषित OXU_VERBOSE_DEBUG

#अगर_घोषित OXU_VERBOSE_DEBUG
#घोषणा oxu_vdbg			oxu_dbg
#अन्यथा
#घोषणा oxu_vdbg(oxu, fmt, args...)	/* Nop */
#पूर्ण_अगर

#अगर_घोषित DEBUG

अटल पूर्णांक __attribute__((__unused__))
dbg_status_buf(अक्षर *buf, अचिन्हित len, स्थिर अक्षर *label, u32 status)
अणु
	वापस scnम_लिखो(buf, len, "%s%sstatus %04x%s%s%s%s%s%s%s%s%s%s",
		label, label[0] ? " " : "", status,
		(status & STS_ASS) ? " Async" : "",
		(status & STS_PSS) ? " Periodic" : "",
		(status & STS_RECL) ? " Recl" : "",
		(status & STS_HALT) ? " Halt" : "",
		(status & STS_IAA) ? " IAA" : "",
		(status & STS_FATAL) ? " FATAL" : "",
		(status & STS_FLR) ? " FLR" : "",
		(status & STS_PCD) ? " PCD" : "",
		(status & STS_ERR) ? " ERR" : "",
		(status & STS_INT) ? " INT" : ""
		);
पूर्ण

अटल पूर्णांक __attribute__((__unused__))
dbg_पूर्णांकr_buf(अक्षर *buf, अचिन्हित len, स्थिर अक्षर *label, u32 enable)
अणु
	वापस scnम_लिखो(buf, len, "%s%sintrenable %02x%s%s%s%s%s%s",
		label, label[0] ? " " : "", enable,
		(enable & STS_IAA) ? " IAA" : "",
		(enable & STS_FATAL) ? " FATAL" : "",
		(enable & STS_FLR) ? " FLR" : "",
		(enable & STS_PCD) ? " PCD" : "",
		(enable & STS_ERR) ? " ERR" : "",
		(enable & STS_INT) ? " INT" : ""
		);
पूर्ण

अटल स्थिर अक्षर *स्थिर fls_strings[] =
    अणु "1024", "512", "256", "??" पूर्ण;

अटल पूर्णांक dbg_command_buf(अक्षर *buf, अचिन्हित len,
				स्थिर अक्षर *label, u32 command)
अणु
	वापस scnम_लिखो(buf, len,
		"%s%scommand %06x %s=%d ithresh=%d%s%s%s%s period=%s%s %s",
		label, label[0] ? " " : "", command,
		(command & CMD_PARK) ? "park" : "(park)",
		CMD_PARK_CNT(command),
		(command >> 16) & 0x3f,
		(command & CMD_LRESET) ? " LReset" : "",
		(command & CMD_IAAD) ? " IAAD" : "",
		(command & CMD_ASE) ? " Async" : "",
		(command & CMD_PSE) ? " Periodic" : "",
		fls_strings[(command >> 2) & 0x3],
		(command & CMD_RESET) ? " Reset" : "",
		(command & CMD_RUN) ? "RUN" : "HALT"
		);
पूर्ण

अटल पूर्णांक dbg_port_buf(अक्षर *buf, अचिन्हित len, स्थिर अक्षर *label,
				पूर्णांक port, u32 status)
अणु
	अक्षर	*sig;

	/* संकेतing state */
	चयन (status & (3 << 10)) अणु
	हाल 0 << 10:
		sig = "se0";
		अवरोध;
	हाल 1 << 10:
		sig = "k";	/* low speed */
		अवरोध;
	हाल 2 << 10:
		sig = "j";
		अवरोध;
	शेष:
		sig = "?";
		अवरोध;
	पूर्ण

	वापस scnम_लिखो(buf, len,
		"%s%sport %d status %06x%s%s sig=%s%s%s%s%s%s%s%s%s%s",
		label, label[0] ? " " : "", port, status,
		(status & PORT_POWER) ? " POWER" : "",
		(status & PORT_OWNER) ? " OWNER" : "",
		sig,
		(status & PORT_RESET) ? " RESET" : "",
		(status & PORT_SUSPEND) ? " SUSPEND" : "",
		(status & PORT_RESUME) ? " RESUME" : "",
		(status & PORT_OCC) ? " OCC" : "",
		(status & PORT_OC) ? " OC" : "",
		(status & PORT_PEC) ? " PEC" : "",
		(status & PORT_PE) ? " PE" : "",
		(status & PORT_CSC) ? " CSC" : "",
		(status & PORT_CONNECT) ? " CONNECT" : ""
	    );
पूर्ण

#अन्यथा

अटल अंतरभूत पूर्णांक __attribute__((__unused__))
dbg_status_buf(अक्षर *buf, अचिन्हित len, स्थिर अक्षर *label, u32 status)
अणु वापस 0; पूर्ण

अटल अंतरभूत पूर्णांक __attribute__((__unused__))
dbg_command_buf(अक्षर *buf, अचिन्हित len, स्थिर अक्षर *label, u32 command)
अणु वापस 0; पूर्ण

अटल अंतरभूत पूर्णांक __attribute__((__unused__))
dbg_पूर्णांकr_buf(अक्षर *buf, अचिन्हित len, स्थिर अक्षर *label, u32 enable)
अणु वापस 0; पूर्ण

अटल अंतरभूत पूर्णांक __attribute__((__unused__))
dbg_port_buf(अक्षर *buf, अचिन्हित len, स्थिर अक्षर *label, पूर्णांक port, u32 status)
अणु वापस 0; पूर्ण

#पूर्ण_अगर /* DEBUG */

/* functions have the "wrong" filename when they're output... */
#घोषणा dbg_status(oxu, label, status) अणु \
	अक्षर _buf[80]; \
	dbg_status_buf(_buf, माप _buf, label, status); \
	oxu_dbg(oxu, "%s\n", _buf); \
पूर्ण

#घोषणा dbg_cmd(oxu, label, command) अणु \
	अक्षर _buf[80]; \
	dbg_command_buf(_buf, माप _buf, label, command); \
	oxu_dbg(oxu, "%s\n", _buf); \
पूर्ण

#घोषणा dbg_port(oxu, label, port, status) अणु \
	अक्षर _buf[80]; \
	dbg_port_buf(_buf, माप _buf, label, port, status); \
	oxu_dbg(oxu, "%s\n", _buf); \
पूर्ण

/*
 * Module parameters
 */

/* Initial IRQ latency: faster than hw शेष */
अटल पूर्णांक log2_irq_thresh;			/* 0 to 6 */
module_param(log2_irq_thresh, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(log2_irq_thresh, "log2 IRQ latency, 1-64 microframes");

/* Initial park setting: slower than hw शेष */
अटल अचिन्हित park;
module_param(park, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(park, "park setting; 1-3 back-to-back async packets");

/* For flakey hardware, ignore overcurrent indicators */
अटल bool ignore_oc;
module_param(ignore_oc, bool, S_IRUGO);
MODULE_PARM_DESC(ignore_oc, "ignore bogus hardware overcurrent indications");


अटल व्योम ehci_work(काष्ठा oxu_hcd *oxu);
अटल पूर्णांक oxu_hub_control(काष्ठा usb_hcd *hcd,
				u16 typeReq, u16 wValue, u16 wIndex,
				अक्षर *buf, u16 wLength);

/*
 * Local functions
 */

/* Low level पढ़ो/ग_लिखो रेजिस्टरs functions */
अटल अंतरभूत u32 oxu_पढ़ोl(व्योम __iomem *base, u32 reg)
अणु
	वापस पढ़ोl(base + reg);
पूर्ण

अटल अंतरभूत व्योम oxu_ग_लिखोl(व्योम __iomem *base, u32 reg, u32 val)
अणु
	ग_लिखोl(val, base + reg);
पूर्ण

अटल अंतरभूत व्योम समयr_action_करोne(काष्ठा oxu_hcd *oxu,
					क्रमागत ehci_समयr_action action)
अणु
	clear_bit(action, &oxu->actions);
पूर्ण

अटल अंतरभूत व्योम समयr_action(काष्ठा oxu_hcd *oxu,
					क्रमागत ehci_समयr_action action)
अणु
	अगर (!test_and_set_bit(action, &oxu->actions)) अणु
		अचिन्हित दीर्घ t;

		चयन (action) अणु
		हाल TIMER_IAA_WATCHDOG:
			t = EHCI_IAA_JIFFIES;
			अवरोध;
		हाल TIMER_IO_WATCHDOG:
			t = EHCI_IO_JIFFIES;
			अवरोध;
		हाल TIMER_ASYNC_OFF:
			t = EHCI_ASYNC_JIFFIES;
			अवरोध;
		हाल TIMER_ASYNC_SHRINK:
		शेष:
			t = EHCI_SHRINK_JIFFIES;
			अवरोध;
		पूर्ण
		t += jअगरfies;
		/* all timings except IAA watchकरोg can be overridden.
		 * async queue SHRINK often precedes IAA.  जबतक it's पढ़ोy
		 * to go OFF neither can matter, and afterwards the IO
		 * watchकरोg stops unless there's still periodic traffic.
		 */
		अगर (action != TIMER_IAA_WATCHDOG
				&& t > oxu->watchकरोg.expires
				&& समयr_pending(&oxu->watchकरोg))
			वापस;
		mod_समयr(&oxu->watchकरोg, t);
	पूर्ण
पूर्ण

/*
 * handshake - spin पढ़ोing hc until handshake completes or fails
 * @ptr: address of hc रेजिस्टर to be पढ़ो
 * @mask: bits to look at in result of पढ़ो
 * @करोne: value of those bits when handshake succeeds
 * @usec: समयout in microseconds
 *
 * Returns negative त्रुटि_सं, or zero on success
 *
 * Success happens when the "mask" bits have the specअगरied value (hardware
 * handshake करोne).  There are two failure modes:  "usec" have passed (major
 * hardware flakeout), or the रेजिस्टर पढ़ोs as all-ones (hardware हटाओd).
 *
 * That last failure should_only happen in हालs like physical cardbus eject
 * beक्रमe driver shutकरोwn. But it also seems to be caused by bugs in cardbus
 * bridge shutकरोwn:  shutting करोwn the bridge beक्रमe the devices using it.
 */
अटल पूर्णांक handshake(काष्ठा oxu_hcd *oxu, व्योम __iomem *ptr,
					u32 mask, u32 करोne, पूर्णांक usec)
अणु
	u32 result;
	पूर्णांक ret;

	ret = पढ़ोl_poll_समयout_atomic(ptr, result,
					((result & mask) == करोne ||
					 result == U32_MAX),
					1, usec);
	अगर (result == U32_MAX)		/* card हटाओd */
		वापस -ENODEV;

	वापस ret;
पूर्ण

/* Force HC to halt state from unknown (EHCI spec section 2.3) */
अटल पूर्णांक ehci_halt(काष्ठा oxu_hcd *oxu)
अणु
	u32	temp = पढ़ोl(&oxu->regs->status);

	/* disable any irqs left enabled by previous code */
	ग_लिखोl(0, &oxu->regs->पूर्णांकr_enable);

	अगर ((temp & STS_HALT) != 0)
		वापस 0;

	temp = पढ़ोl(&oxu->regs->command);
	temp &= ~CMD_RUN;
	ग_लिखोl(temp, &oxu->regs->command);
	वापस handshake(oxu, &oxu->regs->status,
			  STS_HALT, STS_HALT, 16 * 125);
पूर्ण

/* Put TDI/ARC silicon पूर्णांकo EHCI mode */
अटल व्योम tdi_reset(काष्ठा oxu_hcd *oxu)
अणु
	u32 __iomem *reg_ptr;
	u32 पंचांगp;

	reg_ptr = (u32 __iomem *)(((u8 __iomem *)oxu->regs) + 0x68);
	पंचांगp = पढ़ोl(reg_ptr);
	पंचांगp |= 0x3;
	ग_लिखोl(पंचांगp, reg_ptr);
पूर्ण

/* Reset a non-running (STS_HALT == 1) controller */
अटल पूर्णांक ehci_reset(काष्ठा oxu_hcd *oxu)
अणु
	पूर्णांक	retval;
	u32	command = पढ़ोl(&oxu->regs->command);

	command |= CMD_RESET;
	dbg_cmd(oxu, "reset", command);
	ग_लिखोl(command, &oxu->regs->command);
	oxu_to_hcd(oxu)->state = HC_STATE_HALT;
	oxu->next_statechange = jअगरfies;
	retval = handshake(oxu, &oxu->regs->command,
			    CMD_RESET, 0, 250 * 1000);

	अगर (retval)
		वापस retval;

	tdi_reset(oxu);

	वापस retval;
पूर्ण

/* Idle the controller (from running) */
अटल व्योम ehci_quiesce(काष्ठा oxu_hcd *oxu)
अणु
	u32	temp;

#अगर_घोषित DEBUG
	BUG_ON(!HC_IS_RUNNING(oxu_to_hcd(oxu)->state));
#पूर्ण_अगर

	/* रुको क्रम any schedule enables/disables to take effect */
	temp = पढ़ोl(&oxu->regs->command) << 10;
	temp &= STS_ASS | STS_PSS;
	अगर (handshake(oxu, &oxu->regs->status, STS_ASS | STS_PSS,
				temp, 16 * 125) != 0) अणु
		oxu_to_hcd(oxu)->state = HC_STATE_HALT;
		वापस;
	पूर्ण

	/* then disable anything that's still active */
	temp = पढ़ोl(&oxu->regs->command);
	temp &= ~(CMD_ASE | CMD_IAAD | CMD_PSE);
	ग_लिखोl(temp, &oxu->regs->command);

	/* hardware can take 16 microframes to turn off ... */
	अगर (handshake(oxu, &oxu->regs->status, STS_ASS | STS_PSS,
				0, 16 * 125) != 0) अणु
		oxu_to_hcd(oxu)->state = HC_STATE_HALT;
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक check_reset_complete(काष्ठा oxu_hcd *oxu, पूर्णांक index,
				u32 __iomem *status_reg, पूर्णांक port_status)
अणु
	अगर (!(port_status & PORT_CONNECT)) अणु
		oxu->reset_करोne[index] = 0;
		वापस port_status;
	पूर्ण

	/* अगर reset finished and it's still not enabled -- hanकरोff */
	अगर (!(port_status & PORT_PE)) अणु
		oxu_dbg(oxu, "Failed to enable port %d on root hub TT\n",
				index+1);
		वापस port_status;
	पूर्ण अन्यथा
		oxu_dbg(oxu, "port %d high speed\n", index + 1);

	वापस port_status;
पूर्ण

अटल व्योम ehci_hub_descriptor(काष्ठा oxu_hcd *oxu,
				काष्ठा usb_hub_descriptor *desc)
अणु
	पूर्णांक ports = HCS_N_PORTS(oxu->hcs_params);
	u16 temp;

	desc->bDescriptorType = USB_DT_HUB;
	desc->bPwrOn2PwrGood = 10;	/* oxu 1.0, 2.3.9 says 20ms max */
	desc->bHubContrCurrent = 0;

	desc->bNbrPorts = ports;
	temp = 1 + (ports / 8);
	desc->bDescLength = 7 + 2 * temp;

	/* ports removable, and usb 1.0 legacy PortPwrCtrlMask */
	स_रखो(&desc->u.hs.DeviceRemovable[0], 0, temp);
	स_रखो(&desc->u.hs.DeviceRemovable[temp], 0xff, temp);

	temp = HUB_CHAR_INDV_PORT_OCPM;	/* per-port overcurrent reporting */
	अगर (HCS_PPC(oxu->hcs_params))
		temp |= HUB_CHAR_INDV_PORT_LPSM; /* per-port घातer control */
	अन्यथा
		temp |= HUB_CHAR_NO_LPSM; /* no घातer चयनing */
	desc->wHubCharacteristics = (__क्रमce __u16)cpu_to_le16(temp);
पूर्ण


/* Allocate an OXU210HP on-chip memory data buffer
 *
 * An on-chip memory data buffer is required क्रम each OXU210HP USB transfer.
 * Each transfer descriptor has one or more on-chip memory data buffers.
 *
 * Data buffers are allocated from a fix sized pool of data blocks.
 * To minimise fragmentation and give reasonable memory utlisation,
 * data buffers are allocated with sizes the घातer of 2 multiples of
 * the block size, starting on an address a multiple of the allocated size.
 *
 * FIXME: callers of this function require a buffer to be allocated क्रम
 * len=0. This is a waste of on-chip memory and should be fix. Then this
 * function should be changed to not allocate a buffer क्रम len=0.
 */
अटल पूर्णांक oxu_buf_alloc(काष्ठा oxu_hcd *oxu, काष्ठा ehci_qtd *qtd, पूर्णांक len)
अणु
	पूर्णांक n_blocks;	/* minium blocks needed to hold len */
	पूर्णांक a_blocks;	/* blocks allocated */
	पूर्णांक i, j;

	/* Don't allocte bigger than supported */
	अगर (len > BUFFER_SIZE * BUFFER_NUM) अणु
		oxu_err(oxu, "buffer too big (%d)\n", len);
		वापस -ENOMEM;
	पूर्ण

	spin_lock(&oxu->mem_lock);

	/* Number of blocks needed to hold len */
	n_blocks = (len + BUFFER_SIZE - 1) / BUFFER_SIZE;

	/* Round the number of blocks up to the घातer of 2 */
	क्रम (a_blocks = 1; a_blocks < n_blocks; a_blocks <<= 1)
		;

	/* Find a suitable available data buffer */
	क्रम (i = 0; i < BUFFER_NUM;
			i += max(a_blocks, (पूर्णांक)oxu->db_used[i])) अणु

		/* Check all the required blocks are available */
		क्रम (j = 0; j < a_blocks; j++)
			अगर (oxu->db_used[i + j])
				अवरोध;

		अगर (j != a_blocks)
			जारी;

		/* Allocate blocks found! */
		qtd->buffer = (व्योम *) &oxu->mem->db_pool[i];
		qtd->buffer_dma = virt_to_phys(qtd->buffer);

		qtd->qtd_buffer_len = BUFFER_SIZE * a_blocks;
		oxu->db_used[i] = a_blocks;

		spin_unlock(&oxu->mem_lock);

		वापस 0;
	पूर्ण

	/* Failed */

	spin_unlock(&oxu->mem_lock);

	वापस -ENOMEM;
पूर्ण

अटल व्योम oxu_buf_मुक्त(काष्ठा oxu_hcd *oxu, काष्ठा ehci_qtd *qtd)
अणु
	पूर्णांक index;

	spin_lock(&oxu->mem_lock);

	index = (qtd->buffer - (व्योम *) &oxu->mem->db_pool[0])
							 / BUFFER_SIZE;
	oxu->db_used[index] = 0;
	qtd->qtd_buffer_len = 0;
	qtd->buffer_dma = 0;
	qtd->buffer = शून्य;

	spin_unlock(&oxu->mem_lock);
पूर्ण

अटल अंतरभूत व्योम ehci_qtd_init(काष्ठा ehci_qtd *qtd, dma_addr_t dma)
अणु
	स_रखो(qtd, 0, माप *qtd);
	qtd->qtd_dma = dma;
	qtd->hw_token = cpu_to_le32(QTD_STS_HALT);
	qtd->hw_next = EHCI_LIST_END;
	qtd->hw_alt_next = EHCI_LIST_END;
	INIT_LIST_HEAD(&qtd->qtd_list);
पूर्ण

अटल अंतरभूत व्योम oxu_qtd_मुक्त(काष्ठा oxu_hcd *oxu, काष्ठा ehci_qtd *qtd)
अणु
	पूर्णांक index;

	अगर (qtd->buffer)
		oxu_buf_मुक्त(oxu, qtd);

	spin_lock(&oxu->mem_lock);

	index = qtd - &oxu->mem->qtd_pool[0];
	oxu->qtd_used[index] = 0;

	spin_unlock(&oxu->mem_lock);
पूर्ण

अटल काष्ठा ehci_qtd *ehci_qtd_alloc(काष्ठा oxu_hcd *oxu)
अणु
	पूर्णांक i;
	काष्ठा ehci_qtd *qtd = शून्य;

	spin_lock(&oxu->mem_lock);

	क्रम (i = 0; i < QTD_NUM; i++)
		अगर (!oxu->qtd_used[i])
			अवरोध;

	अगर (i < QTD_NUM) अणु
		qtd = (काष्ठा ehci_qtd *) &oxu->mem->qtd_pool[i];
		स_रखो(qtd, 0, माप *qtd);

		qtd->hw_token = cpu_to_le32(QTD_STS_HALT);
		qtd->hw_next = EHCI_LIST_END;
		qtd->hw_alt_next = EHCI_LIST_END;
		INIT_LIST_HEAD(&qtd->qtd_list);

		qtd->qtd_dma = virt_to_phys(qtd);

		oxu->qtd_used[i] = 1;
	पूर्ण

	spin_unlock(&oxu->mem_lock);

	वापस qtd;
पूर्ण

अटल व्योम oxu_qh_मुक्त(काष्ठा oxu_hcd *oxu, काष्ठा ehci_qh *qh)
अणु
	पूर्णांक index;

	spin_lock(&oxu->mem_lock);

	index = qh - &oxu->mem->qh_pool[0];
	oxu->qh_used[index] = 0;

	spin_unlock(&oxu->mem_lock);
पूर्ण

अटल व्योम qh_destroy(काष्ठा kref *kref)
अणु
	काष्ठा ehci_qh *qh = container_of(kref, काष्ठा ehci_qh, kref);
	काष्ठा oxu_hcd *oxu = qh->oxu;

	/* clean qtds first, and know this is not linked */
	अगर (!list_empty(&qh->qtd_list) || qh->qh_next.ptr) अणु
		oxu_dbg(oxu, "unused qh not empty!\n");
		BUG();
	पूर्ण
	अगर (qh->dummy)
		oxu_qtd_मुक्त(oxu, qh->dummy);
	oxu_qh_मुक्त(oxu, qh);
पूर्ण

अटल काष्ठा ehci_qh *oxu_qh_alloc(काष्ठा oxu_hcd *oxu)
अणु
	पूर्णांक i;
	काष्ठा ehci_qh *qh = शून्य;

	spin_lock(&oxu->mem_lock);

	क्रम (i = 0; i < QHEAD_NUM; i++)
		अगर (!oxu->qh_used[i])
			अवरोध;

	अगर (i < QHEAD_NUM) अणु
		qh = (काष्ठा ehci_qh *) &oxu->mem->qh_pool[i];
		स_रखो(qh, 0, माप *qh);

		kref_init(&qh->kref);
		qh->oxu = oxu;
		qh->qh_dma = virt_to_phys(qh);
		INIT_LIST_HEAD(&qh->qtd_list);

		/* dummy td enables safe urb queuing */
		qh->dummy = ehci_qtd_alloc(oxu);
		अगर (qh->dummy == शून्य) अणु
			oxu_dbg(oxu, "no dummy td\n");
			oxu->qh_used[i] = 0;
			qh = शून्य;
			जाओ unlock;
		पूर्ण

		oxu->qh_used[i] = 1;
	पूर्ण
unlock:
	spin_unlock(&oxu->mem_lock);

	वापस qh;
पूर्ण

/* to share a qh (cpu thपढ़ोs, or hc) */
अटल अंतरभूत काष्ठा ehci_qh *qh_get(काष्ठा ehci_qh *qh)
अणु
	kref_get(&qh->kref);
	वापस qh;
पूर्ण

अटल अंतरभूत व्योम qh_put(काष्ठा ehci_qh *qh)
अणु
	kref_put(&qh->kref, qh_destroy);
पूर्ण

अटल व्योम oxu_murb_मुक्त(काष्ठा oxu_hcd *oxu, काष्ठा oxu_murb *murb)
अणु
	पूर्णांक index;

	spin_lock(&oxu->mem_lock);

	index = murb - &oxu->murb_pool[0];
	oxu->murb_used[index] = 0;

	spin_unlock(&oxu->mem_lock);
पूर्ण

अटल काष्ठा oxu_murb *oxu_murb_alloc(काष्ठा oxu_hcd *oxu)

अणु
	पूर्णांक i;
	काष्ठा oxu_murb *murb = शून्य;

	spin_lock(&oxu->mem_lock);

	क्रम (i = 0; i < MURB_NUM; i++)
		अगर (!oxu->murb_used[i])
			अवरोध;

	अगर (i < MURB_NUM) अणु
		murb = &(oxu->murb_pool)[i];

		oxu->murb_used[i] = 1;
	पूर्ण

	spin_unlock(&oxu->mem_lock);

	वापस murb;
पूर्ण

/* The queue heads and transfer descriptors are managed from pools tied
 * to each of the "per device" काष्ठाures.
 * This is the initialisation and cleanup code.
 */
अटल व्योम ehci_mem_cleanup(काष्ठा oxu_hcd *oxu)
अणु
	kमुक्त(oxu->murb_pool);
	oxu->murb_pool = शून्य;

	अगर (oxu->async)
		qh_put(oxu->async);
	oxu->async = शून्य;

	del_समयr(&oxu->urb_समयr);

	oxu->periodic = शून्य;

	/* shaकरोw periodic table */
	kमुक्त(oxu->pshaकरोw);
	oxu->pshaकरोw = शून्य;
पूर्ण

/* Remember to add cleanup code (above) अगर you add anything here.
 */
अटल पूर्णांक ehci_mem_init(काष्ठा oxu_hcd *oxu, gfp_t flags)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < oxu->periodic_size; i++)
		oxu->mem->frame_list[i] = EHCI_LIST_END;
	क्रम (i = 0; i < QHEAD_NUM; i++)
		oxu->qh_used[i] = 0;
	क्रम (i = 0; i < QTD_NUM; i++)
		oxu->qtd_used[i] = 0;

	oxu->murb_pool = kसुस्मृति(MURB_NUM, माप(काष्ठा oxu_murb), flags);
	अगर (!oxu->murb_pool)
		जाओ fail;

	क्रम (i = 0; i < MURB_NUM; i++)
		oxu->murb_used[i] = 0;

	oxu->async = oxu_qh_alloc(oxu);
	अगर (!oxu->async)
		जाओ fail;

	oxu->periodic = (__le32 *) &oxu->mem->frame_list;
	oxu->periodic_dma = virt_to_phys(oxu->periodic);

	क्रम (i = 0; i < oxu->periodic_size; i++)
		oxu->periodic[i] = EHCI_LIST_END;

	/* software shaकरोw of hardware table */
	oxu->pshaकरोw = kसुस्मृति(oxu->periodic_size, माप(व्योम *), flags);
	अगर (oxu->pshaकरोw != शून्य)
		वापस 0;

fail:
	oxu_dbg(oxu, "couldn't init memory\n");
	ehci_mem_cleanup(oxu);
	वापस -ENOMEM;
पूर्ण

/* Fill a qtd, वापसing how much of the buffer we were able to queue up.
 */
अटल पूर्णांक qtd_fill(काष्ठा ehci_qtd *qtd, dma_addr_t buf, माप_प्रकार len,
				पूर्णांक token, पूर्णांक maxpacket)
अणु
	पूर्णांक i, count;
	u64 addr = buf;

	/* one buffer entry per 4K ... first might be लघु or unaligned */
	qtd->hw_buf[0] = cpu_to_le32((u32)addr);
	qtd->hw_buf_hi[0] = cpu_to_le32((u32)(addr >> 32));
	count = 0x1000 - (buf & 0x0fff);	/* rest of that page */
	अगर (likely(len < count))		/* ... अगरf needed */
		count = len;
	अन्यथा अणु
		buf +=  0x1000;
		buf &= ~0x0fff;

		/* per-qtd limit: from 16K to 20K (best alignment) */
		क्रम (i = 1; count < len && i < 5; i++) अणु
			addr = buf;
			qtd->hw_buf[i] = cpu_to_le32((u32)addr);
			qtd->hw_buf_hi[i] = cpu_to_le32((u32)(addr >> 32));
			buf += 0x1000;
			अगर ((count + 0x1000) < len)
				count += 0x1000;
			अन्यथा
				count = len;
		पूर्ण

		/* लघु packets may only terminate transfers */
		अगर (count != len)
			count -= (count % maxpacket);
	पूर्ण
	qtd->hw_token = cpu_to_le32((count << 16) | token);
	qtd->length = count;

	वापस count;
पूर्ण

अटल अंतरभूत व्योम qh_update(काष्ठा oxu_hcd *oxu,
				काष्ठा ehci_qh *qh, काष्ठा ehci_qtd *qtd)
अणु
	/* ग_लिखोs to an active overlay are unsafe */
	BUG_ON(qh->qh_state != QH_STATE_IDLE);

	qh->hw_qtd_next = QTD_NEXT(qtd->qtd_dma);
	qh->hw_alt_next = EHCI_LIST_END;

	/* Except क्रम control endpoपूर्णांकs, we make hardware मुख्यtain data
	 * toggle (like OHCI) ... here (re)initialize the toggle in the QH,
	 * and set the pseuकरो-toggle in udev. Only usb_clear_halt() will
	 * ever clear it.
	 */
	अगर (!(qh->hw_info1 & cpu_to_le32(1 << 14))) अणु
		अचिन्हित	is_out, epnum;

		is_out = !(qtd->hw_token & cpu_to_le32(1 << 8));
		epnum = (le32_to_cpup(&qh->hw_info1) >> 8) & 0x0f;
		अगर (unlikely(!usb_gettoggle(qh->dev, epnum, is_out))) अणु
			qh->hw_token &= ~cpu_to_le32(QTD_TOGGLE);
			usb_settoggle(qh->dev, epnum, is_out, 1);
		पूर्ण
	पूर्ण

	/* HC must see latest qtd and qh data beक्रमe we clear ACTIVE+HALT */
	wmb();
	qh->hw_token &= cpu_to_le32(QTD_TOGGLE | QTD_STS_PING);
पूर्ण

/* If it weren't क्रम a common silicon quirk (writing the dummy पूर्णांकo the qh
 * overlay, so qh->hw_token wrongly becomes inactive/halted), only fault
 * recovery (including urb dequeue) would need software changes to a QH...
 */
अटल व्योम qh_refresh(काष्ठा oxu_hcd *oxu, काष्ठा ehci_qh *qh)
अणु
	काष्ठा ehci_qtd *qtd;

	अगर (list_empty(&qh->qtd_list))
		qtd = qh->dummy;
	अन्यथा अणु
		qtd = list_entry(qh->qtd_list.next,
				काष्ठा ehci_qtd, qtd_list);
		/* first qtd may alपढ़ोy be partially processed */
		अगर (cpu_to_le32(qtd->qtd_dma) == qh->hw_current)
			qtd = शून्य;
	पूर्ण

	अगर (qtd)
		qh_update(oxu, qh, qtd);
पूर्ण

अटल व्योम qtd_copy_status(काष्ठा oxu_hcd *oxu, काष्ठा urb *urb,
				माप_प्रकार length, u32 token)
अणु
	/* count IN/OUT bytes, not SETUP (even लघु packets) */
	अगर (likely(QTD_PID(token) != 2))
		urb->actual_length += length - QTD_LENGTH(token);

	/* करोn't modअगरy error codes */
	अगर (unlikely(urb->status != -EINPROGRESS))
		वापस;

	/* क्रमce cleanup after लघु पढ़ो; not always an error */
	अगर (unlikely(IS_SHORT_READ(token)))
		urb->status = -EREMOTEIO;

	/* serious "can't proceed" faults reported by the hardware */
	अगर (token & QTD_STS_HALT) अणु
		अगर (token & QTD_STS_BABBLE) अणु
			/* FIXME "must" disable babbling device's port too */
			urb->status = -EOVERFLOW;
		पूर्ण अन्यथा अगर (token & QTD_STS_MMF) अणु
			/* fs/ls पूर्णांकerrupt xfer missed the complete-split */
			urb->status = -EPROTO;
		पूर्ण अन्यथा अगर (token & QTD_STS_DBE) अणु
			urb->status = (QTD_PID(token) == 1) /* IN ? */
				? -ENOSR  /* hc couldn't पढ़ो data */
				: -ECOMM; /* hc couldn't ग_लिखो data */
		पूर्ण अन्यथा अगर (token & QTD_STS_XACT) अणु
			/* समयout, bad crc, wrong PID, etc; retried */
			अगर (QTD_CERR(token))
				urb->status = -EPIPE;
			अन्यथा अणु
				oxu_dbg(oxu, "devpath %s ep%d%s 3strikes\n",
					urb->dev->devpath,
					usb_pipeendpoपूर्णांक(urb->pipe),
					usb_pipein(urb->pipe) ? "in" : "out");
				urb->status = -EPROTO;
			पूर्ण
		/* CERR nonzero + no errors + halt --> stall */
		पूर्ण अन्यथा अगर (QTD_CERR(token))
			urb->status = -EPIPE;
		अन्यथा	/* unknown */
			urb->status = -EPROTO;

		oxu_vdbg(oxu, "dev%d ep%d%s qtd token %08x --> status %d\n",
			usb_pipedevice(urb->pipe),
			usb_pipeendpoपूर्णांक(urb->pipe),
			usb_pipein(urb->pipe) ? "in" : "out",
			token, urb->status);
	पूर्ण
पूर्ण

अटल व्योम ehci_urb_करोne(काष्ठा oxu_hcd *oxu, काष्ठा urb *urb)
__releases(oxu->lock)
__acquires(oxu->lock)
अणु
	अगर (likely(urb->hcpriv != शून्य)) अणु
		काष्ठा ehci_qh	*qh = (काष्ठा ehci_qh *) urb->hcpriv;

		/* S-mask in a QH means it's an पूर्णांकerrupt urb */
		अगर ((qh->hw_info2 & cpu_to_le32(QH_SMASK)) != 0) अणु

			/* ... update hc-wide periodic stats (क्रम usbfs) */
			oxu_to_hcd(oxu)->self.bandwidth_पूर्णांक_reqs--;
		पूर्ण
		qh_put(qh);
	पूर्ण

	urb->hcpriv = शून्य;
	चयन (urb->status) अणु
	हाल -EINPROGRESS:		/* success */
		urb->status = 0;
		अवरोध;
	शेष:			/* fault */
		अवरोध;
	हाल -EREMOTEIO:		/* fault or normal */
		अगर (!(urb->transfer_flags & URB_SHORT_NOT_OK))
			urb->status = 0;
		अवरोध;
	हाल -ECONNRESET:		/* canceled */
	हाल -ENOENT:
		अवरोध;
	पूर्ण

#अगर_घोषित OXU_URB_TRACE
	oxu_dbg(oxu, "%s %s urb %p ep%d%s status %d len %d/%d\n",
		__func__, urb->dev->devpath, urb,
		usb_pipeendpoपूर्णांक(urb->pipe),
		usb_pipein(urb->pipe) ? "in" : "out",
		urb->status,
		urb->actual_length, urb->transfer_buffer_length);
#पूर्ण_अगर

	/* complete() can reenter this HCD */
	spin_unlock(&oxu->lock);
	usb_hcd_giveback_urb(oxu_to_hcd(oxu), urb, urb->status);
	spin_lock(&oxu->lock);
पूर्ण

अटल व्योम start_unlink_async(काष्ठा oxu_hcd *oxu, काष्ठा ehci_qh *qh);
अटल व्योम unlink_async(काष्ठा oxu_hcd *oxu, काष्ठा ehci_qh *qh);

अटल व्योम पूर्णांकr_deschedule(काष्ठा oxu_hcd *oxu, काष्ठा ehci_qh *qh);
अटल पूर्णांक qh_schedule(काष्ठा oxu_hcd *oxu, काष्ठा ehci_qh *qh);

#घोषणा HALT_BIT cpu_to_le32(QTD_STS_HALT)

/* Process and मुक्त completed qtds क्रम a qh, वापसing URBs to drivers.
 * Chases up to qh->hw_current.  Returns number of completions called,
 * indicating how much "real" work we did.
 */
अटल अचिन्हित qh_completions(काष्ठा oxu_hcd *oxu, काष्ठा ehci_qh *qh)
अणु
	काष्ठा ehci_qtd *last = शून्य, *end = qh->dummy;
	काष्ठा ehci_qtd	*qtd, *पंचांगp;
	पूर्णांक stopped;
	अचिन्हित count = 0;
	पूर्णांक करो_status = 0;
	u8 state;
	काष्ठा oxu_murb *murb = शून्य;

	अगर (unlikely(list_empty(&qh->qtd_list)))
		वापस count;

	/* completions (or tasks on other cpus) must never clobber HALT
	 * till we've gone through and cleaned everything up, even when
	 * they add urbs to this qh's queue or mark them क्रम unlinking.
	 *
	 * NOTE:  unlinking expects to be करोne in queue order.
	 */
	state = qh->qh_state;
	qh->qh_state = QH_STATE_COMPLETING;
	stopped = (state == QH_STATE_IDLE);

	/* हटाओ de-activated QTDs from front of queue.
	 * after faults (including लघु पढ़ोs), cleanup this urb
	 * then let the queue advance.
	 * अगर queue is stopped, handles unlinks.
	 */
	list_क्रम_each_entry_safe(qtd, पंचांगp, &qh->qtd_list, qtd_list) अणु
		काष्ठा urb *urb;
		u32 token = 0;

		urb = qtd->urb;

		/* Clean up any state from previous QTD ...*/
		अगर (last) अणु
			अगर (likely(last->urb != urb)) अणु
				अगर (last->urb->complete == शून्य) अणु
					murb = (काष्ठा oxu_murb *) last->urb;
					last->urb = murb->मुख्य;
					अगर (murb->last) अणु
						ehci_urb_करोne(oxu, last->urb);
						count++;
					पूर्ण
					oxu_murb_मुक्त(oxu, murb);
				पूर्ण अन्यथा अणु
					ehci_urb_करोne(oxu, last->urb);
					count++;
				पूर्ण
			पूर्ण
			oxu_qtd_मुक्त(oxu, last);
			last = शून्य;
		पूर्ण

		/* ignore urbs submitted during completions we reported */
		अगर (qtd == end)
			अवरोध;

		/* hardware copies qtd out of qh overlay */
		rmb();
		token = le32_to_cpu(qtd->hw_token);

		/* always clean up qtds the hc de-activated */
		अगर ((token & QTD_STS_ACTIVE) == 0) अणु

			अगर ((token & QTD_STS_HALT) != 0) अणु
				stopped = 1;

			/* magic dummy क्रम some लघु पढ़ोs; qh won't advance.
			 * that silicon quirk can kick in with this dummy too.
			 */
			पूर्ण अन्यथा अगर (IS_SHORT_READ(token) &&
					!(qtd->hw_alt_next & EHCI_LIST_END)) अणु
				stopped = 1;
				जाओ halt;
			पूर्ण

		/* stop scanning when we reach qtds the hc is using */
		पूर्ण अन्यथा अगर (likely(!stopped &&
				HC_IS_RUNNING(oxu_to_hcd(oxu)->state))) अणु
			अवरोध;

		पूर्ण अन्यथा अणु
			stopped = 1;

			अगर (unlikely(!HC_IS_RUNNING(oxu_to_hcd(oxu)->state)))
				urb->status = -ESHUTDOWN;

			/* ignore active urbs unless some previous qtd
			 * क्रम the urb faulted (including लघु पढ़ो) or
			 * its urb was canceled.  we may patch qh or qtds.
			 */
			अगर (likely(urb->status == -EINPROGRESS))
				जारी;

			/* issue status after लघु control पढ़ोs */
			अगर (unlikely(करो_status != 0)
					&& QTD_PID(token) == 0 /* OUT */) अणु
				करो_status = 0;
				जारी;
			पूर्ण

			/* token in overlay may be most current */
			अगर (state == QH_STATE_IDLE
					&& cpu_to_le32(qtd->qtd_dma)
						== qh->hw_current)
				token = le32_to_cpu(qh->hw_token);

			/* क्रमce halt क्रम unlinked or blocked qh, so we'll
			 * patch the qh later and so that completions can't
			 * activate it जबतक we "know" it's stopped.
			 */
			अगर ((HALT_BIT & qh->hw_token) == 0) अणु
halt:
				qh->hw_token |= HALT_BIT;
				wmb();
			पूर्ण
		पूर्ण

		/* Remove it from the queue */
		qtd_copy_status(oxu, urb->complete ?
					urb : ((काष्ठा oxu_murb *) urb)->मुख्य,
				qtd->length, token);
		अगर ((usb_pipein(qtd->urb->pipe)) &&
				(शून्य != qtd->transfer_buffer))
			स_नकल(qtd->transfer_buffer, qtd->buffer, qtd->length);
		करो_status = (urb->status == -EREMOTEIO)
				&& usb_pipecontrol(urb->pipe);

		अगर (stopped && qtd->qtd_list.prev != &qh->qtd_list) अणु
			last = list_entry(qtd->qtd_list.prev,
					काष्ठा ehci_qtd, qtd_list);
			last->hw_next = qtd->hw_next;
		पूर्ण
		list_del(&qtd->qtd_list);
		last = qtd;
	पूर्ण

	/* last urb's completion might still need calling */
	अगर (likely(last != शून्य)) अणु
		अगर (last->urb->complete == शून्य) अणु
			murb = (काष्ठा oxu_murb *) last->urb;
			last->urb = murb->मुख्य;
			अगर (murb->last) अणु
				ehci_urb_करोne(oxu, last->urb);
				count++;
			पूर्ण
			oxu_murb_मुक्त(oxu, murb);
		पूर्ण अन्यथा अणु
			ehci_urb_करोne(oxu, last->urb);
			count++;
		पूर्ण
		oxu_qtd_मुक्त(oxu, last);
	पूर्ण

	/* restore original state; caller must unlink or relink */
	qh->qh_state = state;

	/* be sure the hardware's करोne with the qh beक्रमe refreshing
	 * it after fault cleanup, or recovering from silicon wrongly
	 * overlaying the dummy qtd (which reduces DMA chatter).
	 */
	अगर (stopped != 0 || qh->hw_qtd_next == EHCI_LIST_END) अणु
		चयन (state) अणु
		हाल QH_STATE_IDLE:
			qh_refresh(oxu, qh);
			अवरोध;
		हाल QH_STATE_LINKED:
			/* should be rare क्रम periodic transfers,
			 * except maybe high bandwidth ...
			 */
			अगर ((cpu_to_le32(QH_SMASK)
					& qh->hw_info2) != 0) अणु
				पूर्णांकr_deschedule(oxu, qh);
				(व्योम) qh_schedule(oxu, qh);
			पूर्ण अन्यथा
				unlink_async(oxu, qh);
			अवरोध;
		/* otherwise, unlink alपढ़ोy started */
		पूर्ण
	पूर्ण

	वापस count;
पूर्ण

/* High bandwidth multiplier, as encoded in highspeed endpoपूर्णांक descriptors */
#घोषणा hb_mult(wMaxPacketSize)		(1 + (((wMaxPacketSize) >> 11) & 0x03))
/* ... and packet size, क्रम any kind of endpoपूर्णांक descriptor */
#घोषणा max_packet(wMaxPacketSize)	((wMaxPacketSize) & 0x07ff)

/* Reverse of qh_urb_transaction: मुक्त a list of TDs.
 * used क्रम cleanup after errors, beक्रमe HC sees an URB's TDs.
 */
अटल व्योम qtd_list_मुक्त(काष्ठा oxu_hcd *oxu,
				काष्ठा urb *urb, काष्ठा list_head *head)
अणु
	काष्ठा ehci_qtd	*qtd, *temp;

	list_क्रम_each_entry_safe(qtd, temp, head, qtd_list) अणु
		list_del(&qtd->qtd_list);
		oxu_qtd_मुक्त(oxu, qtd);
	पूर्ण
पूर्ण

/* Create a list of filled qtds क्रम this URB; won't link पूर्णांकo qh.
 */
अटल काष्ठा list_head *qh_urb_transaction(काष्ठा oxu_hcd *oxu,
						काष्ठा urb *urb,
						काष्ठा list_head *head,
						gfp_t flags)
अणु
	काष्ठा ehci_qtd	*qtd, *qtd_prev;
	dma_addr_t buf;
	पूर्णांक len, maxpacket;
	पूर्णांक is_input;
	u32 token;
	व्योम *transfer_buf = शून्य;
	पूर्णांक ret;

	/*
	 * URBs map to sequences of QTDs: one logical transaction
	 */
	qtd = ehci_qtd_alloc(oxu);
	अगर (unlikely(!qtd))
		वापस शून्य;
	list_add_tail(&qtd->qtd_list, head);
	qtd->urb = urb;

	token = QTD_STS_ACTIVE;
	token |= (EHCI_TUNE_CERR << 10);
	/* क्रम split transactions, SplitXState initialized to zero */

	len = urb->transfer_buffer_length;
	is_input = usb_pipein(urb->pipe);
	अगर (!urb->transfer_buffer && urb->transfer_buffer_length && is_input)
		urb->transfer_buffer = phys_to_virt(urb->transfer_dma);

	अगर (usb_pipecontrol(urb->pipe)) अणु
		/* SETUP pid */
		ret = oxu_buf_alloc(oxu, qtd, माप(काष्ठा usb_ctrlrequest));
		अगर (ret)
			जाओ cleanup;

		qtd_fill(qtd, qtd->buffer_dma, माप(काष्ठा usb_ctrlrequest),
				token | (2 /* "setup" */ << 8), 8);
		स_नकल(qtd->buffer, qtd->urb->setup_packet,
				माप(काष्ठा usb_ctrlrequest));

		/* ... and always at least one more pid */
		token ^= QTD_TOGGLE;
		qtd_prev = qtd;
		qtd = ehci_qtd_alloc(oxu);
		अगर (unlikely(!qtd))
			जाओ cleanup;
		qtd->urb = urb;
		qtd_prev->hw_next = QTD_NEXT(qtd->qtd_dma);
		list_add_tail(&qtd->qtd_list, head);

		/* क्रम zero length DATA stages, STATUS is always IN */
		अगर (len == 0)
			token |= (1 /* "in" */ << 8);
	पूर्ण

	/*
	 * Data transfer stage: buffer setup
	 */

	ret = oxu_buf_alloc(oxu, qtd, len);
	अगर (ret)
		जाओ cleanup;

	buf = qtd->buffer_dma;
	transfer_buf = urb->transfer_buffer;

	अगर (!is_input)
		स_नकल(qtd->buffer, qtd->urb->transfer_buffer, len);

	अगर (is_input)
		token |= (1 /* "in" */ << 8);
	/* अन्यथा it's alपढ़ोy initted to "out" pid (0 << 8) */

	maxpacket = max_packet(usb_maxpacket(urb->dev, urb->pipe, !is_input));

	/*
	 * buffer माला_लो wrapped in one or more qtds;
	 * last one may be "short" (including zero len)
	 * and may serve as a control status ack
	 */
	क्रम (;;) अणु
		पूर्णांक this_qtd_len;

		this_qtd_len = qtd_fill(qtd, buf, len, token, maxpacket);
		qtd->transfer_buffer = transfer_buf;
		len -= this_qtd_len;
		buf += this_qtd_len;
		transfer_buf += this_qtd_len;
		अगर (is_input)
			qtd->hw_alt_next = oxu->async->hw_alt_next;

		/* qh makes control packets use qtd toggle; maybe चयन it */
		अगर ((maxpacket & (this_qtd_len + (maxpacket - 1))) == 0)
			token ^= QTD_TOGGLE;

		अगर (likely(len <= 0))
			अवरोध;

		qtd_prev = qtd;
		qtd = ehci_qtd_alloc(oxu);
		अगर (unlikely(!qtd))
			जाओ cleanup;
		अगर (likely(len > 0)) अणु
			ret = oxu_buf_alloc(oxu, qtd, len);
			अगर (ret)
				जाओ cleanup;
		पूर्ण
		qtd->urb = urb;
		qtd_prev->hw_next = QTD_NEXT(qtd->qtd_dma);
		list_add_tail(&qtd->qtd_list, head);
	पूर्ण

	/* unless the bulk/पूर्णांकerrupt caller wants a chance to clean
	 * up after लघु पढ़ोs, hc should advance qh past this urb
	 */
	अगर (likely((urb->transfer_flags & URB_SHORT_NOT_OK) == 0
				|| usb_pipecontrol(urb->pipe)))
		qtd->hw_alt_next = EHCI_LIST_END;

	/*
	 * control requests may need a terminating data "status" ack;
	 * bulk ones may need a terminating लघु packet (zero length).
	 */
	अगर (likely(urb->transfer_buffer_length != 0)) अणु
		पूर्णांक	one_more = 0;

		अगर (usb_pipecontrol(urb->pipe)) अणु
			one_more = 1;
			token ^= 0x0100;	/* "in" <--> "out"  */
			token |= QTD_TOGGLE;	/* क्रमce DATA1 */
		पूर्ण अन्यथा अगर (usb_pipebulk(urb->pipe)
				&& (urb->transfer_flags & URB_ZERO_PACKET)
				&& !(urb->transfer_buffer_length % maxpacket)) अणु
			one_more = 1;
		पूर्ण
		अगर (one_more) अणु
			qtd_prev = qtd;
			qtd = ehci_qtd_alloc(oxu);
			अगर (unlikely(!qtd))
				जाओ cleanup;
			qtd->urb = urb;
			qtd_prev->hw_next = QTD_NEXT(qtd->qtd_dma);
			list_add_tail(&qtd->qtd_list, head);

			/* never any data in such packets */
			qtd_fill(qtd, 0, 0, token, 0);
		पूर्ण
	पूर्ण

	/* by शेष, enable पूर्णांकerrupt on urb completion */
	qtd->hw_token |= cpu_to_le32(QTD_IOC);
	वापस head;

cleanup:
	qtd_list_मुक्त(oxu, urb, head);
	वापस शून्य;
पूर्ण

/* Each QH holds a qtd list; a QH is used क्रम everything except iso.
 *
 * For पूर्णांकerrupt urbs, the scheduler must set the microframe scheduling
 * mask(s) each समय the QH माला_लो scheduled.  For highspeed, that's
 * just one microframe in the s-mask.  For split पूर्णांकerrupt transactions
 * there are additional complications: c-mask, maybe FSTNs.
 */
अटल काष्ठा ehci_qh *qh_make(काष्ठा oxu_hcd *oxu,
				काष्ठा urb *urb, gfp_t flags)
अणु
	काष्ठा ehci_qh *qh = oxu_qh_alloc(oxu);
	u32 info1 = 0, info2 = 0;
	पूर्णांक is_input, type;
	पूर्णांक maxp = 0;

	अगर (!qh)
		वापस qh;

	/*
	 * init endpoपूर्णांक/device data क्रम this QH
	 */
	info1 |= usb_pipeendpoपूर्णांक(urb->pipe) << 8;
	info1 |= usb_pipedevice(urb->pipe) << 0;

	is_input = usb_pipein(urb->pipe);
	type = usb_pipetype(urb->pipe);
	maxp = usb_maxpacket(urb->dev, urb->pipe, !is_input);

	/* Compute पूर्णांकerrupt scheduling parameters just once, and save.
	 * - allowing क्रम high bandwidth, how many nsec/uframe are used?
	 * - split transactions need a second CSPLIT uframe; same question
	 * - splits also need a schedule gap (क्रम full/low speed I/O)
	 * - qh has a polling पूर्णांकerval
	 *
	 * For control/bulk requests, the HC or TT handles these.
	 */
	अगर (type == PIPE_INTERRUPT) अणु
		qh->usecs = NS_TO_US(usb_calc_bus_समय(USB_SPEED_HIGH,
								is_input, 0,
				hb_mult(maxp) * max_packet(maxp)));
		qh->start = NO_FRAME;

		अगर (urb->dev->speed == USB_SPEED_HIGH) अणु
			qh->c_usecs = 0;
			qh->gap_uf = 0;

			qh->period = urb->पूर्णांकerval >> 3;
			अगर (qh->period == 0 && urb->पूर्णांकerval != 1) अणु
				/* NOTE पूर्णांकerval 2 or 4 uframes could work.
				 * But पूर्णांकerval 1 scheduling is simpler, and
				 * includes high bandwidth.
				 */
				oxu_dbg(oxu, "intr period %d uframes, NYET!\n",
					urb->पूर्णांकerval);
				जाओ करोne;
			पूर्ण
		पूर्ण अन्यथा अणु
			काष्ठा usb_tt	*tt = urb->dev->tt;
			पूर्णांक		think_समय;

			/* gap is f(FS/LS transfer बार) */
			qh->gap_uf = 1 + usb_calc_bus_समय(urb->dev->speed,
					is_input, 0, maxp) / (125 * 1000);

			/* FIXME this just approximates SPLIT/CSPLIT बार */
			अगर (is_input) अणु		/* SPLIT, gap, CSPLIT+DATA */
				qh->c_usecs = qh->usecs + HS_USECS(0);
				qh->usecs = HS_USECS(1);
			पूर्ण अन्यथा अणु		/* SPLIT+DATA, gap, CSPLIT */
				qh->usecs += HS_USECS(1);
				qh->c_usecs = HS_USECS(0);
			पूर्ण

			think_समय = tt ? tt->think_समय : 0;
			qh->tt_usecs = NS_TO_US(think_समय +
					usb_calc_bus_समय(urb->dev->speed,
					is_input, 0, max_packet(maxp)));
			qh->period = urb->पूर्णांकerval;
		पूर्ण
	पूर्ण

	/* support क्रम tt scheduling, and access to toggles */
	qh->dev = urb->dev;

	/* using TT? */
	चयन (urb->dev->speed) अणु
	हाल USB_SPEED_LOW:
		info1 |= (1 << 12);	/* EPS "low" */
		fallthrough;

	हाल USB_SPEED_FULL:
		/* EPS 0 means "full" */
		अगर (type != PIPE_INTERRUPT)
			info1 |= (EHCI_TUNE_RL_TT << 28);
		अगर (type == PIPE_CONTROL) अणु
			info1 |= (1 << 27);	/* क्रम TT */
			info1 |= 1 << 14;	/* toggle from qtd */
		पूर्ण
		info1 |= maxp << 16;

		info2 |= (EHCI_TUNE_MULT_TT << 30);
		info2 |= urb->dev->ttport << 23;

		/* NOTE:  अगर (PIPE_INTERRUPT) अणु scheduler sets c-mask पूर्ण */

		अवरोध;

	हाल USB_SPEED_HIGH:		/* no TT involved */
		info1 |= (2 << 12);	/* EPS "high" */
		अगर (type == PIPE_CONTROL) अणु
			info1 |= (EHCI_TUNE_RL_HS << 28);
			info1 |= 64 << 16;	/* usb2 fixed maxpacket */
			info1 |= 1 << 14;	/* toggle from qtd */
			info2 |= (EHCI_TUNE_MULT_HS << 30);
		पूर्ण अन्यथा अगर (type == PIPE_BULK) अणु
			info1 |= (EHCI_TUNE_RL_HS << 28);
			info1 |= 512 << 16;	/* usb2 fixed maxpacket */
			info2 |= (EHCI_TUNE_MULT_HS << 30);
		पूर्ण अन्यथा अणु		/* PIPE_INTERRUPT */
			info1 |= max_packet(maxp) << 16;
			info2 |= hb_mult(maxp) << 30;
		पूर्ण
		अवरोध;
	शेष:
		oxu_dbg(oxu, "bogus dev %p speed %d\n", urb->dev, urb->dev->speed);
करोne:
		qh_put(qh);
		वापस शून्य;
	पूर्ण

	/* NOTE:  अगर (PIPE_INTERRUPT) अणु scheduler sets s-mask पूर्ण */

	/* init as live, toggle clear, advance to dummy */
	qh->qh_state = QH_STATE_IDLE;
	qh->hw_info1 = cpu_to_le32(info1);
	qh->hw_info2 = cpu_to_le32(info2);
	usb_settoggle(urb->dev, usb_pipeendpoपूर्णांक(urb->pipe), !is_input, 1);
	qh_refresh(oxu, qh);
	वापस qh;
पूर्ण

/* Move qh (and its qtds) onto async queue; maybe enable queue.
 */
अटल व्योम qh_link_async(काष्ठा oxu_hcd *oxu, काष्ठा ehci_qh *qh)
अणु
	__le32 dma = QH_NEXT(qh->qh_dma);
	काष्ठा ehci_qh *head;

	/* (re)start the async schedule? */
	head = oxu->async;
	समयr_action_करोne(oxu, TIMER_ASYNC_OFF);
	अगर (!head->qh_next.qh) अणु
		u32	cmd = पढ़ोl(&oxu->regs->command);

		अगर (!(cmd & CMD_ASE)) अणु
			/* in हाल a clear of CMD_ASE didn't take yet */
			(व्योम)handshake(oxu, &oxu->regs->status,
					STS_ASS, 0, 150);
			cmd |= CMD_ASE | CMD_RUN;
			ग_लिखोl(cmd, &oxu->regs->command);
			oxu_to_hcd(oxu)->state = HC_STATE_RUNNING;
			/* posted ग_लिखो need not be known to HC yet ... */
		पूर्ण
	पूर्ण

	/* clear halt and/or toggle; and maybe recover from silicon quirk */
	अगर (qh->qh_state == QH_STATE_IDLE)
		qh_refresh(oxu, qh);

	/* splice right after start */
	qh->qh_next = head->qh_next;
	qh->hw_next = head->hw_next;
	wmb();

	head->qh_next.qh = qh;
	head->hw_next = dma;

	qh->qh_state = QH_STATE_LINKED;
	/* qtd completions reported later by पूर्णांकerrupt */
पूर्ण

#घोषणा	QH_ADDR_MASK	cpu_to_le32(0x7f)

/*
 * For control/bulk/पूर्णांकerrupt, वापस QH with these TDs appended.
 * Allocates and initializes the QH अगर necessary.
 * Returns null अगर it can't allocate a QH it needs to.
 * If the QH has TDs (urbs) alपढ़ोy, that's great.
 */
अटल काष्ठा ehci_qh *qh_append_tds(काष्ठा oxu_hcd *oxu,
				काष्ठा urb *urb, काष्ठा list_head *qtd_list,
				पूर्णांक epnum, व्योम	**ptr)
अणु
	काष्ठा ehci_qh *qh = शून्य;

	qh = (काष्ठा ehci_qh *) *ptr;
	अगर (unlikely(qh == शून्य)) अणु
		/* can't sleep here, we have oxu->lock... */
		qh = qh_make(oxu, urb, GFP_ATOMIC);
		*ptr = qh;
	पूर्ण
	अगर (likely(qh != शून्य)) अणु
		काष्ठा ehci_qtd	*qtd;

		अगर (unlikely(list_empty(qtd_list)))
			qtd = शून्य;
		अन्यथा
			qtd = list_entry(qtd_list->next, काष्ठा ehci_qtd,
					qtd_list);

		/* control qh may need patching ... */
		अगर (unlikely(epnum == 0)) अणु

			/* usb_reset_device() briefly reverts to address 0 */
			अगर (usb_pipedevice(urb->pipe) == 0)
				qh->hw_info1 &= ~QH_ADDR_MASK;
		पूर्ण

		/* just one way to queue requests: swap with the dummy qtd.
		 * only hc or qh_refresh() ever modअगरy the overlay.
		 */
		अगर (likely(qtd != शून्य)) अणु
			काष्ठा ehci_qtd	*dummy;
			dma_addr_t dma;
			__le32 token;

			/* to aव्योम racing the HC, use the dummy td instead of
			 * the first td of our list (becomes new dummy).  both
			 * tds stay deactivated until we're करोne, when the
			 * HC is allowed to fetch the old dummy (4.10.2).
			 */
			token = qtd->hw_token;
			qtd->hw_token = HALT_BIT;
			wmb();
			dummy = qh->dummy;

			dma = dummy->qtd_dma;
			*dummy = *qtd;
			dummy->qtd_dma = dma;

			list_del(&qtd->qtd_list);
			list_add(&dummy->qtd_list, qtd_list);
			list_splice(qtd_list, qh->qtd_list.prev);

			ehci_qtd_init(qtd, qtd->qtd_dma);
			qh->dummy = qtd;

			/* hc must see the new dummy at list end */
			dma = qtd->qtd_dma;
			qtd = list_entry(qh->qtd_list.prev,
					काष्ठा ehci_qtd, qtd_list);
			qtd->hw_next = QTD_NEXT(dma);

			/* let the hc process these next qtds */
			dummy->hw_token = (token & ~(0x80));
			wmb();
			dummy->hw_token = token;

			urb->hcpriv = qh_get(qh);
		पूर्ण
	पूर्ण
	वापस qh;
पूर्ण

अटल पूर्णांक submit_async(काष्ठा oxu_hcd	*oxu, काष्ठा urb *urb,
			काष्ठा list_head *qtd_list, gfp_t mem_flags)
अणु
	पूर्णांक epnum = urb->ep->desc.bEndpoपूर्णांकAddress;
	अचिन्हित दीर्घ flags;
	काष्ठा ehci_qh *qh = शून्य;
	पूर्णांक rc = 0;
#अगर_घोषित OXU_URB_TRACE
	काष्ठा ehci_qtd	*qtd;

	qtd = list_entry(qtd_list->next, काष्ठा ehci_qtd, qtd_list);

	oxu_dbg(oxu, "%s %s urb %p ep%d%s len %d, qtd %p [qh %p]\n",
		__func__, urb->dev->devpath, urb,
		epnum & 0x0f, (epnum & USB_सूची_IN) ? "in" : "out",
		urb->transfer_buffer_length,
		qtd, urb->ep->hcpriv);
#पूर्ण_अगर

	spin_lock_irqsave(&oxu->lock, flags);
	अगर (unlikely(!HCD_HW_ACCESSIBLE(oxu_to_hcd(oxu)))) अणु
		rc = -ESHUTDOWN;
		जाओ करोne;
	पूर्ण

	qh = qh_append_tds(oxu, urb, qtd_list, epnum, &urb->ep->hcpriv);
	अगर (unlikely(qh == शून्य)) अणु
		rc = -ENOMEM;
		जाओ करोne;
	पूर्ण

	/* Control/bulk operations through TTs करोn't need scheduling,
	 * the HC and TT handle it when the TT has a buffer पढ़ोy.
	 */
	अगर (likely(qh->qh_state == QH_STATE_IDLE))
		qh_link_async(oxu, qh_get(qh));
करोne:
	spin_unlock_irqrestore(&oxu->lock, flags);
	अगर (unlikely(qh == शून्य))
		qtd_list_मुक्त(oxu, urb, qtd_list);
	वापस rc;
पूर्ण

/* The async qh क्रम the qtds being reclaimed are now unlinked from the HC */

अटल व्योम end_unlink_async(काष्ठा oxu_hcd *oxu)
अणु
	काष्ठा ehci_qh *qh = oxu->reclaim;
	काष्ठा ehci_qh *next;

	समयr_action_करोne(oxu, TIMER_IAA_WATCHDOG);

	qh->qh_state = QH_STATE_IDLE;
	qh->qh_next.qh = शून्य;
	qh_put(qh);			/* refcount from reclaim */

	/* other unlink(s) may be pending (in QH_STATE_UNLINK_WAIT) */
	next = qh->reclaim;
	oxu->reclaim = next;
	oxu->reclaim_पढ़ोy = 0;
	qh->reclaim = शून्य;

	qh_completions(oxu, qh);

	अगर (!list_empty(&qh->qtd_list)
			&& HC_IS_RUNNING(oxu_to_hcd(oxu)->state))
		qh_link_async(oxu, qh);
	अन्यथा अणु
		qh_put(qh);		/* refcount from async list */

		/* it's not मुक्त to turn the async schedule on/off; leave it
		 * active but idle क्रम a जबतक once it empties.
		 */
		अगर (HC_IS_RUNNING(oxu_to_hcd(oxu)->state)
				&& oxu->async->qh_next.qh == शून्य)
			समयr_action(oxu, TIMER_ASYNC_OFF);
	पूर्ण

	अगर (next) अणु
		oxu->reclaim = शून्य;
		start_unlink_async(oxu, next);
	पूर्ण
पूर्ण

/* makes sure the async qh will become idle */
/* caller must own oxu->lock */

अटल व्योम start_unlink_async(काष्ठा oxu_hcd *oxu, काष्ठा ehci_qh *qh)
अणु
	पूर्णांक cmd = पढ़ोl(&oxu->regs->command);
	काष्ठा ehci_qh *prev;

#अगर_घोषित DEBUG
	निश्चित_spin_locked(&oxu->lock);
	BUG_ON(oxu->reclaim || (qh->qh_state != QH_STATE_LINKED
				&& qh->qh_state != QH_STATE_UNLINK_WAIT));
#पूर्ण_अगर

	/* stop async schedule right now? */
	अगर (unlikely(qh == oxu->async)) अणु
		/* can't get here without STS_ASS set */
		अगर (oxu_to_hcd(oxu)->state != HC_STATE_HALT
				&& !oxu->reclaim) अणु
			/* ... and CMD_IAAD clear */
			ग_लिखोl(cmd & ~CMD_ASE, &oxu->regs->command);
			wmb();
			/* handshake later, अगर we need to */
			समयr_action_करोne(oxu, TIMER_ASYNC_OFF);
		पूर्ण
		वापस;
	पूर्ण

	qh->qh_state = QH_STATE_UNLINK;
	oxu->reclaim = qh = qh_get(qh);

	prev = oxu->async;
	जबतक (prev->qh_next.qh != qh)
		prev = prev->qh_next.qh;

	prev->hw_next = qh->hw_next;
	prev->qh_next = qh->qh_next;
	wmb();

	अगर (unlikely(oxu_to_hcd(oxu)->state == HC_STATE_HALT)) अणु
		/* अगर (unlikely(qh->reclaim != 0))
		 *	this will recurse, probably not much
		 */
		end_unlink_async(oxu);
		वापस;
	पूर्ण

	oxu->reclaim_पढ़ोy = 0;
	cmd |= CMD_IAAD;
	ग_लिखोl(cmd, &oxu->regs->command);
	(व्योम) पढ़ोl(&oxu->regs->command);
	समयr_action(oxu, TIMER_IAA_WATCHDOG);
पूर्ण

अटल व्योम scan_async(काष्ठा oxu_hcd *oxu)
अणु
	काष्ठा ehci_qh *qh;
	क्रमागत ehci_समयr_action action = TIMER_IO_WATCHDOG;

	अगर (!++(oxu->stamp))
		oxu->stamp++;
	समयr_action_करोne(oxu, TIMER_ASYNC_SHRINK);
rescan:
	qh = oxu->async->qh_next.qh;
	अगर (likely(qh != शून्य)) अणु
		करो अणु
			/* clean any finished work क्रम this qh */
			अगर (!list_empty(&qh->qtd_list)
					&& qh->stamp != oxu->stamp) अणु
				पूर्णांक temp;

				/* unlinks could happen here; completion
				 * reporting drops the lock.  rescan using
				 * the latest schedule, but करोn't rescan
				 * qhs we alपढ़ोy finished (no looping).
				 */
				qh = qh_get(qh);
				qh->stamp = oxu->stamp;
				temp = qh_completions(oxu, qh);
				qh_put(qh);
				अगर (temp != 0)
					जाओ rescan;
			पूर्ण

			/* unlink idle entries, reducing HC PCI usage as well
			 * as HCD schedule-scanning costs.  delay क्रम any qh
			 * we just scanned, there's a not-unusual हाल that it
			 * करोesn't stay idle क्रम दीर्घ.
			 * (plus, aव्योमs some kind of re-activation race.)
			 */
			अगर (list_empty(&qh->qtd_list)) अणु
				अगर (qh->stamp == oxu->stamp)
					action = TIMER_ASYNC_SHRINK;
				अन्यथा अगर (!oxu->reclaim
					    && qh->qh_state == QH_STATE_LINKED)
					start_unlink_async(oxu, qh);
			पूर्ण

			qh = qh->qh_next.qh;
		पूर्ण जबतक (qh);
	पूर्ण
	अगर (action == TIMER_ASYNC_SHRINK)
		समयr_action(oxu, TIMER_ASYNC_SHRINK);
पूर्ण

/*
 * periodic_next_shaकरोw - वापस "next" poपूर्णांकer on shaकरोw list
 * @periodic: host poपूर्णांकer to qh/itd/sitd
 * @tag: hardware tag क्रम type of this record
 */
अटल जोड़ ehci_shaकरोw *periodic_next_shaकरोw(जोड़ ehci_shaकरोw *periodic,
						__le32 tag)
अणु
	चयन (tag) अणु
	शेष:
	हाल Q_TYPE_QH:
		वापस &periodic->qh->qh_next;
	पूर्ण
पूर्ण

/* caller must hold oxu->lock */
अटल व्योम periodic_unlink(काष्ठा oxu_hcd *oxu, अचिन्हित frame, व्योम *ptr)
अणु
	जोड़ ehci_shaकरोw *prev_p = &oxu->pshaकरोw[frame];
	__le32 *hw_p = &oxu->periodic[frame];
	जोड़ ehci_shaकरोw here = *prev_p;

	/* find predecessor of "ptr"; hw and shaकरोw lists are in sync */
	जबतक (here.ptr && here.ptr != ptr) अणु
		prev_p = periodic_next_shaकरोw(prev_p, Q_NEXT_TYPE(*hw_p));
		hw_p = here.hw_next;
		here = *prev_p;
	पूर्ण
	/* an पूर्णांकerrupt entry (at list end) could have been shared */
	अगर (!here.ptr)
		वापस;

	/* update shaकरोw and hardware lists ... the old "next" poपूर्णांकers
	 * from ptr may still be in use, the caller updates them.
	 */
	*prev_p = *periodic_next_shaकरोw(&here, Q_NEXT_TYPE(*hw_p));
	*hw_p = *here.hw_next;
पूर्ण

/* how many of the uframe's 125 usecs are allocated? */
अटल अचिन्हित लघु periodic_usecs(काष्ठा oxu_hcd *oxu,
					अचिन्हित frame, अचिन्हित uframe)
अणु
	__le32 *hw_p = &oxu->periodic[frame];
	जोड़ ehci_shaकरोw *q = &oxu->pshaकरोw[frame];
	अचिन्हित usecs = 0;

	जबतक (q->ptr) अणु
		चयन (Q_NEXT_TYPE(*hw_p)) अणु
		हाल Q_TYPE_QH:
		शेष:
			/* is it in the S-mask? */
			अगर (q->qh->hw_info2 & cpu_to_le32(1 << uframe))
				usecs += q->qh->usecs;
			/* ... or C-mask? */
			अगर (q->qh->hw_info2 & cpu_to_le32(1 << (8 + uframe)))
				usecs += q->qh->c_usecs;
			hw_p = &q->qh->hw_next;
			q = &q->qh->qh_next;
			अवरोध;
		पूर्ण
	पूर्ण
#अगर_घोषित DEBUG
	अगर (usecs > 100)
		oxu_err(oxu, "uframe %d sched overrun: %d usecs\n",
						frame * 8 + uframe, usecs);
#पूर्ण_अगर
	वापस usecs;
पूर्ण

अटल पूर्णांक enable_periodic(काष्ठा oxu_hcd *oxu)
अणु
	u32 cmd;
	पूर्णांक status;

	/* did clearing PSE did take effect yet?
	 * takes effect only at frame boundaries...
	 */
	status = handshake(oxu, &oxu->regs->status, STS_PSS, 0, 9 * 125);
	अगर (status != 0) अणु
		oxu_to_hcd(oxu)->state = HC_STATE_HALT;
		usb_hc_died(oxu_to_hcd(oxu));
		वापस status;
	पूर्ण

	cmd = पढ़ोl(&oxu->regs->command) | CMD_PSE;
	ग_लिखोl(cmd, &oxu->regs->command);
	/* posted ग_लिखो ... PSS happens later */
	oxu_to_hcd(oxu)->state = HC_STATE_RUNNING;

	/* make sure ehci_work scans these */
	oxu->next_uframe = पढ़ोl(&oxu->regs->frame_index)
		% (oxu->periodic_size << 3);
	वापस 0;
पूर्ण

अटल पूर्णांक disable_periodic(काष्ठा oxu_hcd *oxu)
अणु
	u32 cmd;
	पूर्णांक status;

	/* did setting PSE not take effect yet?
	 * takes effect only at frame boundaries...
	 */
	status = handshake(oxu, &oxu->regs->status, STS_PSS, STS_PSS, 9 * 125);
	अगर (status != 0) अणु
		oxu_to_hcd(oxu)->state = HC_STATE_HALT;
		usb_hc_died(oxu_to_hcd(oxu));
		वापस status;
	पूर्ण

	cmd = पढ़ोl(&oxu->regs->command) & ~CMD_PSE;
	ग_लिखोl(cmd, &oxu->regs->command);
	/* posted ग_लिखो ... */

	oxu->next_uframe = -1;
	वापस 0;
पूर्ण

/* periodic schedule slots have iso tds (normal or split) first, then a
 * sparse tree क्रम active पूर्णांकerrupt transfers.
 *
 * this just links in a qh; caller guarantees uframe masks are set right.
 * no FSTN support (yet; oxu 0.96+)
 */
अटल पूर्णांक qh_link_periodic(काष्ठा oxu_hcd *oxu, काष्ठा ehci_qh *qh)
अणु
	अचिन्हित i;
	अचिन्हित period = qh->period;

	dev_dbg(&qh->dev->dev,
		"link qh%d-%04x/%p start %d [%d/%d us]\n",
		period, le32_to_cpup(&qh->hw_info2) & (QH_CMASK | QH_SMASK),
		qh, qh->start, qh->usecs, qh->c_usecs);

	/* high bandwidth, or otherwise every microframe */
	अगर (period == 0)
		period = 1;

	क्रम (i = qh->start; i < oxu->periodic_size; i += period) अणु
		जोड़ ehci_shaकरोw	*prev = &oxu->pshaकरोw[i];
		__le32			*hw_p = &oxu->periodic[i];
		जोड़ ehci_shaकरोw	here = *prev;
		__le32			type = 0;

		/* skip the iso nodes at list head */
		जबतक (here.ptr) अणु
			type = Q_NEXT_TYPE(*hw_p);
			अगर (type == Q_TYPE_QH)
				अवरोध;
			prev = periodic_next_shaकरोw(prev, type);
			hw_p = &here.qh->hw_next;
			here = *prev;
		पूर्ण

		/* sorting each branch by period (slow-->fast)
		 * enables sharing पूर्णांकerior tree nodes
		 */
		जबतक (here.ptr && qh != here.qh) अणु
			अगर (qh->period > here.qh->period)
				अवरोध;
			prev = &here.qh->qh_next;
			hw_p = &here.qh->hw_next;
			here = *prev;
		पूर्ण
		/* link in this qh, unless some earlier pass did that */
		अगर (qh != here.qh) अणु
			qh->qh_next = here;
			अगर (here.qh)
				qh->hw_next = *hw_p;
			wmb();
			prev->qh = qh;
			*hw_p = QH_NEXT(qh->qh_dma);
		पूर्ण
	पूर्ण
	qh->qh_state = QH_STATE_LINKED;
	qh_get(qh);

	/* update per-qh bandwidth क्रम usbfs */
	oxu_to_hcd(oxu)->self.bandwidth_allocated += qh->period
		? ((qh->usecs + qh->c_usecs) / qh->period)
		: (qh->usecs * 8);

	/* maybe enable periodic schedule processing */
	अगर (!oxu->periodic_sched++)
		वापस enable_periodic(oxu);

	वापस 0;
पूर्ण

अटल व्योम qh_unlink_periodic(काष्ठा oxu_hcd *oxu, काष्ठा ehci_qh *qh)
अणु
	अचिन्हित i;
	अचिन्हित period;

	/* FIXME:
	 *   IF this isn't high speed
	 *   and this qh is active in the current uframe
	 *   (and overlay token SplitXstate is false?)
	 * THEN
	 *   qh->hw_info1 |= cpu_to_le32(1 << 7 "ignore");
	 */

	/* high bandwidth, or otherwise part of every microframe */
	period = qh->period;
	अगर (period == 0)
		period = 1;

	क्रम (i = qh->start; i < oxu->periodic_size; i += period)
		periodic_unlink(oxu, i, qh);

	/* update per-qh bandwidth क्रम usbfs */
	oxu_to_hcd(oxu)->self.bandwidth_allocated -= qh->period
		? ((qh->usecs + qh->c_usecs) / qh->period)
		: (qh->usecs * 8);

	dev_dbg(&qh->dev->dev,
		"unlink qh%d-%04x/%p start %d [%d/%d us]\n",
		qh->period,
		le32_to_cpup(&qh->hw_info2) & (QH_CMASK | QH_SMASK),
		qh, qh->start, qh->usecs, qh->c_usecs);

	/* qh->qh_next still "live" to HC */
	qh->qh_state = QH_STATE_UNLINK;
	qh->qh_next.ptr = शून्य;
	qh_put(qh);

	/* maybe turn off periodic schedule */
	oxu->periodic_sched--;
	अगर (!oxu->periodic_sched)
		(व्योम) disable_periodic(oxu);
पूर्ण

अटल व्योम पूर्णांकr_deschedule(काष्ठा oxu_hcd *oxu, काष्ठा ehci_qh *qh)
अणु
	अचिन्हित रुको;

	qh_unlink_periodic(oxu, qh);

	/* simple/paranoid:  always delay, expecting the HC needs to पढ़ो
	 * qh->hw_next or finish a ग_लिखोback after SPLIT/CSPLIT ... and
	 * expect hub_wq to clean up after any CSPLITs we won't issue.
	 * active high speed queues may need bigger delays...
	 */
	अगर (list_empty(&qh->qtd_list)
		|| (cpu_to_le32(QH_CMASK) & qh->hw_info2) != 0)
		रुको = 2;
	अन्यथा
		रुको = 55;	/* worst हाल: 3 * 1024 */

	udelay(रुको);
	qh->qh_state = QH_STATE_IDLE;
	qh->hw_next = EHCI_LIST_END;
	wmb();
पूर्ण

अटल पूर्णांक check_period(काष्ठा oxu_hcd *oxu,
			अचिन्हित frame, अचिन्हित uframe,
			अचिन्हित period, अचिन्हित usecs)
अणु
	पूर्णांक claimed;

	/* complete split running पूर्णांकo next frame?
	 * given FSTN support, we could someबार check...
	 */
	अगर (uframe >= 8)
		वापस 0;

	/*
	 * 80% periodic == 100 usec/uframe available
	 * convert "usecs we need" to "max already claimed"
	 */
	usecs = 100 - usecs;

	/* we "know" 2 and 4 uframe पूर्णांकervals were rejected; so
	 * क्रम period 0, check _every_ microframe in the schedule.
	 */
	अगर (unlikely(period == 0)) अणु
		करो अणु
			क्रम (uframe = 0; uframe < 7; uframe++) अणु
				claimed = periodic_usecs(oxu, frame, uframe);
				अगर (claimed > usecs)
					वापस 0;
			पूर्ण
		पूर्ण जबतक ((frame += 1) < oxu->periodic_size);

	/* just check the specअगरied uframe, at that period */
	पूर्ण अन्यथा अणु
		करो अणु
			claimed = periodic_usecs(oxu, frame, uframe);
			अगर (claimed > usecs)
				वापस 0;
		पूर्ण जबतक ((frame += period) < oxu->periodic_size);
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक check_पूर्णांकr_schedule(काष्ठा oxu_hcd	*oxu,
				अचिन्हित frame, अचिन्हित uframe,
				स्थिर काष्ठा ehci_qh *qh, __le32 *c_maskp)
अणु
	पूर्णांक retval = -ENOSPC;

	अगर (qh->c_usecs && uframe >= 6)		/* FSTN territory? */
		जाओ करोne;

	अगर (!check_period(oxu, frame, uframe, qh->period, qh->usecs))
		जाओ करोne;
	अगर (!qh->c_usecs) अणु
		retval = 0;
		*c_maskp = 0;
		जाओ करोne;
	पूर्ण

करोne:
	वापस retval;
पूर्ण

/* "first fit" scheduling policy used the first समय through,
 * or when the previous schedule slot can't be re-used.
 */
अटल पूर्णांक qh_schedule(काष्ठा oxu_hcd *oxu, काष्ठा ehci_qh *qh)
अणु
	पूर्णांक		status;
	अचिन्हित	uframe;
	__le32		c_mask;
	अचिन्हित	frame;		/* 0..(qh->period - 1), or NO_FRAME */

	qh_refresh(oxu, qh);
	qh->hw_next = EHCI_LIST_END;
	frame = qh->start;

	/* reuse the previous schedule slots, अगर we can */
	अगर (frame < qh->period) अणु
		uframe = ffs(le32_to_cpup(&qh->hw_info2) & QH_SMASK);
		status = check_पूर्णांकr_schedule(oxu, frame, --uframe,
				qh, &c_mask);
	पूर्ण अन्यथा अणु
		uframe = 0;
		c_mask = 0;
		status = -ENOSPC;
	पूर्ण

	/* अन्यथा scan the schedule to find a group of slots such that all
	 * uframes have enough periodic bandwidth available.
	 */
	अगर (status) अणु
		/* "normal" हाल, uframing flexible except with splits */
		अगर (qh->period) अणु
			frame = qh->period - 1;
			करो अणु
				क्रम (uframe = 0; uframe < 8; uframe++) अणु
					status = check_पूर्णांकr_schedule(oxu,
							frame, uframe, qh,
							&c_mask);
					अगर (status == 0)
						अवरोध;
				पूर्ण
			पूर्ण जबतक (status && frame--);

		/* qh->period == 0 means every uframe */
		पूर्ण अन्यथा अणु
			frame = 0;
			status = check_पूर्णांकr_schedule(oxu, 0, 0, qh, &c_mask);
		पूर्ण
		अगर (status)
			जाओ करोne;
		qh->start = frame;

		/* reset S-frame and (maybe) C-frame masks */
		qh->hw_info2 &= cpu_to_le32(~(QH_CMASK | QH_SMASK));
		qh->hw_info2 |= qh->period
			? cpu_to_le32(1 << uframe)
			: cpu_to_le32(QH_SMASK);
		qh->hw_info2 |= c_mask;
	पूर्ण अन्यथा
		oxu_dbg(oxu, "reused qh %p schedule\n", qh);

	/* stuff पूर्णांकo the periodic schedule */
	status = qh_link_periodic(oxu, qh);
करोne:
	वापस status;
पूर्ण

अटल पूर्णांक पूर्णांकr_submit(काष्ठा oxu_hcd *oxu, काष्ठा urb *urb,
			काष्ठा list_head *qtd_list, gfp_t mem_flags)
अणु
	अचिन्हित epnum;
	अचिन्हित दीर्घ flags;
	काष्ठा ehci_qh *qh;
	पूर्णांक status = 0;
	काष्ठा list_head	empty;

	/* get endpoपूर्णांक and transfer/schedule data */
	epnum = urb->ep->desc.bEndpoपूर्णांकAddress;

	spin_lock_irqsave(&oxu->lock, flags);

	अगर (unlikely(!HCD_HW_ACCESSIBLE(oxu_to_hcd(oxu)))) अणु
		status = -ESHUTDOWN;
		जाओ करोne;
	पूर्ण

	/* get qh and क्रमce any scheduling errors */
	INIT_LIST_HEAD(&empty);
	qh = qh_append_tds(oxu, urb, &empty, epnum, &urb->ep->hcpriv);
	अगर (qh == शून्य) अणु
		status = -ENOMEM;
		जाओ करोne;
	पूर्ण
	अगर (qh->qh_state == QH_STATE_IDLE) अणु
		status = qh_schedule(oxu, qh);
		अगर (status != 0)
			जाओ करोne;
	पूर्ण

	/* then queue the urb's tds to the qh */
	qh = qh_append_tds(oxu, urb, qtd_list, epnum, &urb->ep->hcpriv);
	BUG_ON(qh == शून्य);

	/* ... update usbfs periodic stats */
	oxu_to_hcd(oxu)->self.bandwidth_पूर्णांक_reqs++;

करोne:
	spin_unlock_irqrestore(&oxu->lock, flags);
	अगर (status)
		qtd_list_मुक्त(oxu, urb, qtd_list);

	वापस status;
पूर्ण

अटल अंतरभूत पूर्णांक itd_submit(काष्ठा oxu_hcd *oxu, काष्ठा urb *urb,
						gfp_t mem_flags)
अणु
	oxu_dbg(oxu, "iso support is missing!\n");
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक sitd_submit(काष्ठा oxu_hcd *oxu, काष्ठा urb *urb,
						gfp_t mem_flags)
अणु
	oxu_dbg(oxu, "split iso support is missing!\n");
	वापस -ENOSYS;
पूर्ण

अटल व्योम scan_periodic(काष्ठा oxu_hcd *oxu)
अणु
	अचिन्हित frame, घड़ी, now_uframe, mod;
	अचिन्हित modअगरied;

	mod = oxu->periodic_size << 3;

	/*
	 * When running, scan from last scan poपूर्णांक up to "now"
	 * अन्यथा clean up by scanning everything that's left.
	 * Touches as few pages as possible:  cache-मित्रly.
	 */
	now_uframe = oxu->next_uframe;
	अगर (HC_IS_RUNNING(oxu_to_hcd(oxu)->state))
		घड़ी = पढ़ोl(&oxu->regs->frame_index);
	अन्यथा
		घड़ी = now_uframe + mod - 1;
	घड़ी %= mod;

	क्रम (;;) अणु
		जोड़ ehci_shaकरोw	q, *q_p;
		__le32			type, *hw_p;

		/* करोn't scan past the live uframe */
		frame = now_uframe >> 3;
		अगर (frame != (घड़ी >> 3)) अणु
			/* safe to scan the whole frame at once */
			now_uframe |= 0x07;
		पूर्ण

restart:
		/* scan each element in frame's queue क्रम completions */
		q_p = &oxu->pshaकरोw[frame];
		hw_p = &oxu->periodic[frame];
		q.ptr = q_p->ptr;
		type = Q_NEXT_TYPE(*hw_p);
		modअगरied = 0;

		जबतक (q.ptr != शून्य) अणु
			जोड़ ehci_shaकरोw temp;

			चयन (type) अणु
			हाल Q_TYPE_QH:
				/* handle any completions */
				temp.qh = qh_get(q.qh);
				type = Q_NEXT_TYPE(q.qh->hw_next);
				q = q.qh->qh_next;
				modअगरied = qh_completions(oxu, temp.qh);
				अगर (unlikely(list_empty(&temp.qh->qtd_list)))
					पूर्णांकr_deschedule(oxu, temp.qh);
				qh_put(temp.qh);
				अवरोध;
			शेष:
				oxu_dbg(oxu, "corrupt type %d frame %d shadow %p\n",
					type, frame, q.ptr);
				q.ptr = शून्य;
			पूर्ण

			/* assume completion callbacks modअगरy the queue */
			अगर (unlikely(modअगरied))
				जाओ restart;
		पूर्ण

		/* Stop when we catch up to the HC */

		/* FIXME:  this assumes we won't get lapped when
		 * latencies climb; that should be rare, but...
		 * detect it, and just go all the way around.
		 * FLR might help detect this हाल, so दीर्घ as latencies
		 * करोn't exceed periodic_size msec (शेष 1.024 sec).
		 */

		/* FIXME: likewise assumes HC करोesn't halt mid-scan */

		अगर (now_uframe == घड़ी) अणु
			अचिन्हित	now;

			अगर (!HC_IS_RUNNING(oxu_to_hcd(oxu)->state))
				अवरोध;
			oxu->next_uframe = now_uframe;
			now = पढ़ोl(&oxu->regs->frame_index) % mod;
			अगर (now_uframe == now)
				अवरोध;

			/* rescan the rest of this frame, then ... */
			घड़ी = now;
		पूर्ण अन्यथा अणु
			now_uframe++;
			now_uframe %= mod;
		पूर्ण
	पूर्ण
पूर्ण

/* On some प्रणालीs, leaving remote wakeup enabled prevents प्रणाली shutकरोwn.
 * The firmware seems to think that घातering off is a wakeup event!
 * This routine turns off remote wakeup and everything अन्यथा, on all ports.
 */
अटल व्योम ehci_turn_off_all_ports(काष्ठा oxu_hcd *oxu)
अणु
	पूर्णांक port = HCS_N_PORTS(oxu->hcs_params);

	जबतक (port--)
		ग_लिखोl(PORT_RWC_BITS, &oxu->regs->port_status[port]);
पूर्ण

अटल व्योम ehci_port_घातer(काष्ठा oxu_hcd *oxu, पूर्णांक is_on)
अणु
	अचिन्हित port;

	अगर (!HCS_PPC(oxu->hcs_params))
		वापस;

	oxu_dbg(oxu, "...power%s ports...\n", is_on ? "up" : "down");
	क्रम (port = HCS_N_PORTS(oxu->hcs_params); port > 0; ) अणु
		अगर (is_on)
			oxu_hub_control(oxu_to_hcd(oxu), SetPortFeature,
				USB_PORT_FEAT_POWER, port--, शून्य, 0);
		अन्यथा
			oxu_hub_control(oxu_to_hcd(oxu), ClearPortFeature,
				USB_PORT_FEAT_POWER, port--, शून्य, 0);
	पूर्ण

	msleep(20);
पूर्ण

/* Called from some पूर्णांकerrupts, समयrs, and so on.
 * It calls driver completion functions, after dropping oxu->lock.
 */
अटल व्योम ehci_work(काष्ठा oxu_hcd *oxu)
अणु
	समयr_action_करोne(oxu, TIMER_IO_WATCHDOG);
	अगर (oxu->reclaim_पढ़ोy)
		end_unlink_async(oxu);

	/* another CPU may drop oxu->lock during a schedule scan जबतक
	 * it reports urb completions.  this flag guards against bogus
	 * attempts at re-entrant schedule scanning.
	 */
	अगर (oxu->scanning)
		वापस;
	oxu->scanning = 1;
	scan_async(oxu);
	अगर (oxu->next_uframe != -1)
		scan_periodic(oxu);
	oxu->scanning = 0;

	/* the IO watchकरोg guards against hardware or driver bugs that
	 * misplace IRQs, and should let us run completely without IRQs.
	 * such lossage has been observed on both VT6202 and VT8235.
	 */
	अगर (HC_IS_RUNNING(oxu_to_hcd(oxu)->state) &&
			(oxu->async->qh_next.ptr != शून्य ||
			 oxu->periodic_sched != 0))
		समयr_action(oxu, TIMER_IO_WATCHDOG);
पूर्ण

अटल व्योम unlink_async(काष्ठा oxu_hcd *oxu, काष्ठा ehci_qh *qh)
अणु
	/* अगर we need to use IAA and it's busy, defer */
	अगर (qh->qh_state == QH_STATE_LINKED
			&& oxu->reclaim
			&& HC_IS_RUNNING(oxu_to_hcd(oxu)->state)) अणु
		काष्ठा ehci_qh		*last;

		क्रम (last = oxu->reclaim;
				last->reclaim;
				last = last->reclaim)
			जारी;
		qh->qh_state = QH_STATE_UNLINK_WAIT;
		last->reclaim = qh;

	/* bypass IAA अगर the hc can't care */
	पूर्ण अन्यथा अगर (!HC_IS_RUNNING(oxu_to_hcd(oxu)->state) && oxu->reclaim)
		end_unlink_async(oxu);

	/* something अन्यथा might have unlinked the qh by now */
	अगर (qh->qh_state == QH_STATE_LINKED)
		start_unlink_async(oxu, qh);
पूर्ण

/*
 * USB host controller methods
 */

अटल irqवापस_t oxu210_hcd_irq(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा oxu_hcd *oxu = hcd_to_oxu(hcd);
	u32 status, pcd_status = 0;
	पूर्णांक bh;

	spin_lock(&oxu->lock);

	status = पढ़ोl(&oxu->regs->status);

	/* e.g. cardbus physical eject */
	अगर (status == ~(u32) 0) अणु
		oxu_dbg(oxu, "device removed\n");
		जाओ dead;
	पूर्ण

	/* Shared IRQ? */
	status &= INTR_MASK;
	अगर (!status || unlikely(hcd->state == HC_STATE_HALT)) अणु
		spin_unlock(&oxu->lock);
		वापस IRQ_NONE;
	पूर्ण

	/* clear (just) पूर्णांकerrupts */
	ग_लिखोl(status, &oxu->regs->status);
	पढ़ोl(&oxu->regs->command);	/* unblock posted ग_लिखो */
	bh = 0;

#अगर_घोषित OXU_VERBOSE_DEBUG
	/* unrequested/ignored: Frame List Rollover */
	dbg_status(oxu, "irq", status);
#पूर्ण_अगर

	/* INT, ERR, and IAA पूर्णांकerrupt rates can be throttled */

	/* normal [4.15.1.2] or error [4.15.1.1] completion */
	अगर (likely((status & (STS_INT|STS_ERR)) != 0))
		bh = 1;

	/* complete the unlinking of some qh [4.15.2.3] */
	अगर (status & STS_IAA) अणु
		oxu->reclaim_पढ़ोy = 1;
		bh = 1;
	पूर्ण

	/* remote wakeup [4.3.1] */
	अगर (status & STS_PCD) अणु
		अचिन्हित i = HCS_N_PORTS(oxu->hcs_params);
		pcd_status = status;

		/* resume root hub? */
		अगर (!(पढ़ोl(&oxu->regs->command) & CMD_RUN))
			usb_hcd_resume_root_hub(hcd);

		जबतक (i--) अणु
			पूर्णांक pstatus = पढ़ोl(&oxu->regs->port_status[i]);

			अगर (pstatus & PORT_OWNER)
				जारी;
			अगर (!(pstatus & PORT_RESUME)
					|| oxu->reset_करोne[i] != 0)
				जारी;

			/* start USB_RESUME_TIMEOUT resume संकेतing from this
			 * port, and make hub_wq collect PORT_STAT_C_SUSPEND to
			 * stop that संकेतing.
			 */
			oxu->reset_करोne[i] = jअगरfies +
				msecs_to_jअगरfies(USB_RESUME_TIMEOUT);
			oxu_dbg(oxu, "port %d remote wakeup\n", i + 1);
			mod_समयr(&hcd->rh_समयr, oxu->reset_करोne[i]);
		पूर्ण
	पूर्ण

	/* PCI errors [4.15.2.4] */
	अगर (unlikely((status & STS_FATAL) != 0)) अणु
		/* bogus "fatal" IRQs appear on some chips... why?  */
		status = पढ़ोl(&oxu->regs->status);
		dbg_cmd(oxu, "fatal", पढ़ोl(&oxu->regs->command));
		dbg_status(oxu, "fatal", status);
		अगर (status & STS_HALT) अणु
			oxu_err(oxu, "fatal error\n");
dead:
			ehci_reset(oxu);
			ग_लिखोl(0, &oxu->regs->configured_flag);
			usb_hc_died(hcd);
			/* generic layer समाप्तs/unlinks all urbs, then
			 * uses oxu_stop to clean up the rest
			 */
			bh = 1;
		पूर्ण
	पूर्ण

	अगर (bh)
		ehci_work(oxu);
	spin_unlock(&oxu->lock);
	अगर (pcd_status & STS_PCD)
		usb_hcd_poll_rh_status(hcd);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t oxu_irq(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा oxu_hcd *oxu = hcd_to_oxu(hcd);
	पूर्णांक ret = IRQ_HANDLED;

	u32 status = oxu_पढ़ोl(hcd->regs, OXU_CHIPIRQSTATUS);
	u32 enable = oxu_पढ़ोl(hcd->regs, OXU_CHIPIRQEN_SET);

	/* Disable all पूर्णांकerrupt */
	oxu_ग_लिखोl(hcd->regs, OXU_CHIPIRQEN_CLR, enable);

	अगर ((oxu->is_otg && (status & OXU_USBOTGI)) ||
		(!oxu->is_otg && (status & OXU_USBSPHI)))
		oxu210_hcd_irq(hcd);
	अन्यथा
		ret = IRQ_NONE;

	/* Enable all पूर्णांकerrupt back */
	oxu_ग_लिखोl(hcd->regs, OXU_CHIPIRQEN_SET, enable);

	वापस ret;
पूर्ण

अटल व्योम oxu_watchकरोg(काष्ठा समयr_list *t)
अणु
	काष्ठा oxu_hcd	*oxu = from_समयr(oxu, t, watchकरोg);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&oxu->lock, flags);

	/* lost IAA irqs wedge things badly; seen with a vt8235 */
	अगर (oxu->reclaim) अणु
		u32 status = पढ़ोl(&oxu->regs->status);
		अगर (status & STS_IAA) अणु
			oxu_vdbg(oxu, "lost IAA\n");
			ग_लिखोl(STS_IAA, &oxu->regs->status);
			oxu->reclaim_पढ़ोy = 1;
		पूर्ण
	पूर्ण

	/* stop async processing after it's idled a bit */
	अगर (test_bit(TIMER_ASYNC_OFF, &oxu->actions))
		start_unlink_async(oxu, oxu->async);

	/* oxu could run by समयr, without IRQs ... */
	ehci_work(oxu);

	spin_unlock_irqrestore(&oxu->lock, flags);
पूर्ण

/* One-समय init, only क्रम memory state.
 */
अटल पूर्णांक oxu_hcd_init(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा oxu_hcd *oxu = hcd_to_oxu(hcd);
	u32 temp;
	पूर्णांक retval;
	u32 hcc_params;

	spin_lock_init(&oxu->lock);

	समयr_setup(&oxu->watchकरोg, oxu_watchकरोg, 0);

	/*
	 * hw शेष: 1K periodic list heads, one per frame.
	 * periodic_size can shrink by USBCMD update अगर hcc_params allows.
	 */
	oxu->periodic_size = DEFAULT_I_TDPS;
	retval = ehci_mem_init(oxu, GFP_KERNEL);
	अगर (retval < 0)
		वापस retval;

	/* controllers may cache some of the periodic schedule ... */
	hcc_params = पढ़ोl(&oxu->caps->hcc_params);
	अगर (HCC_ISOC_CACHE(hcc_params))		/* full frame cache */
		oxu->i_thresh = 8;
	अन्यथा					/* N microframes cached */
		oxu->i_thresh = 2 + HCC_ISOC_THRES(hcc_params);

	oxu->reclaim = शून्य;
	oxu->reclaim_पढ़ोy = 0;
	oxu->next_uframe = -1;

	/*
	 * dedicate a qh क्रम the async ring head, since we couldn't unlink
	 * a 'real' qh without stopping the async schedule [4.8].  use it
	 * as the 'reclamation list head' too.
	 * its dummy is used in hw_alt_next of many tds, to prevent the qh
	 * from स्वतःmatically advancing to the next td after लघु पढ़ोs.
	 */
	oxu->async->qh_next.qh = शून्य;
	oxu->async->hw_next = QH_NEXT(oxu->async->qh_dma);
	oxu->async->hw_info1 = cpu_to_le32(QH_HEAD);
	oxu->async->hw_token = cpu_to_le32(QTD_STS_HALT);
	oxu->async->hw_qtd_next = EHCI_LIST_END;
	oxu->async->qh_state = QH_STATE_LINKED;
	oxu->async->hw_alt_next = QTD_NEXT(oxu->async->dummy->qtd_dma);

	/* clear पूर्णांकerrupt enables, set irq latency */
	अगर (log2_irq_thresh < 0 || log2_irq_thresh > 6)
		log2_irq_thresh = 0;
	temp = 1 << (16 + log2_irq_thresh);
	अगर (HCC_CANPARK(hcc_params)) अणु
		/* HW शेष park == 3, on hardware that supports it (like
		 * NVidia and ALI silicon), maximizes throughput on the async
		 * schedule by aव्योमing QH fetches between transfers.
		 *
		 * With fast usb storage devices and NForce2, "park" seems to
		 * make problems:  throughput reduction (!), data errors...
		 */
		अगर (park) अणु
			park = min(park, (अचिन्हित) 3);
			temp |= CMD_PARK;
			temp |= park << 8;
		पूर्ण
		oxu_dbg(oxu, "park %d\n", park);
	पूर्ण
	अगर (HCC_PGM_FRAMELISTLEN(hcc_params)) अणु
		/* periodic schedule size can be smaller than शेष */
		temp &= ~(3 << 2);
		temp |= (EHCI_TUNE_FLS << 2);
	पूर्ण
	oxu->command = temp;

	वापस 0;
पूर्ण

/* Called during probe() after chip reset completes.
 */
अटल पूर्णांक oxu_reset(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा oxu_hcd *oxu = hcd_to_oxu(hcd);

	spin_lock_init(&oxu->mem_lock);
	INIT_LIST_HEAD(&oxu->urb_list);
	oxu->urb_len = 0;

	अगर (oxu->is_otg) अणु
		oxu->caps = hcd->regs + OXU_OTG_CAP_OFFSET;
		oxu->regs = hcd->regs + OXU_OTG_CAP_OFFSET + \
			HC_LENGTH(पढ़ोl(&oxu->caps->hc_capbase));

		oxu->mem = hcd->regs + OXU_SPH_MEM;
	पूर्ण अन्यथा अणु
		oxu->caps = hcd->regs + OXU_SPH_CAP_OFFSET;
		oxu->regs = hcd->regs + OXU_SPH_CAP_OFFSET + \
			HC_LENGTH(पढ़ोl(&oxu->caps->hc_capbase));

		oxu->mem = hcd->regs + OXU_OTG_MEM;
	पूर्ण

	oxu->hcs_params = पढ़ोl(&oxu->caps->hcs_params);
	oxu->sbrn = 0x20;

	वापस oxu_hcd_init(hcd);
पूर्ण

अटल पूर्णांक oxu_run(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा oxu_hcd *oxu = hcd_to_oxu(hcd);
	पूर्णांक retval;
	u32 temp, hcc_params;

	hcd->uses_new_polling = 1;

	/* EHCI spec section 4.1 */
	retval = ehci_reset(oxu);
	अगर (retval != 0) अणु
		ehci_mem_cleanup(oxu);
		वापस retval;
	पूर्ण
	ग_लिखोl(oxu->periodic_dma, &oxu->regs->frame_list);
	ग_लिखोl((u32) oxu->async->qh_dma, &oxu->regs->async_next);

	/* hcc_params controls whether oxu->regs->segment must (!!!)
	 * be used; it स्थिरrains QH/ITD/SITD and QTD locations.
	 * dma_pool consistent memory always uses segment zero.
	 * streaming mappings क्रम I/O buffers, like pci_map_single(),
	 * can वापस segments above 4GB, अगर the device allows.
	 *
	 * NOTE:  the dma mask is visible through dev->dma_mask, so
	 * drivers can pass this info aदीर्घ ... like NETIF_F_HIGHDMA,
	 * Scsi_Host.highmem_io, and so क्रमth.  It's पढ़ोonly to all
	 * host side drivers though.
	 */
	hcc_params = पढ़ोl(&oxu->caps->hcc_params);
	अगर (HCC_64BIT_ADDR(hcc_params))
		ग_लिखोl(0, &oxu->regs->segment);

	oxu->command &= ~(CMD_LRESET | CMD_IAAD | CMD_PSE |
				CMD_ASE | CMD_RESET);
	oxu->command |= CMD_RUN;
	ग_लिखोl(oxu->command, &oxu->regs->command);
	dbg_cmd(oxu, "init", oxu->command);

	/*
	 * Start, enabling full USB 2.0 functionality ... usb 1.1 devices
	 * are explicitly handed to companion controller(s), so no TT is
	 * involved with the root hub.  (Except where one is पूर्णांकegrated,
	 * and there's no companion controller unless maybe क्रम USB OTG.)
	 */
	hcd->state = HC_STATE_RUNNING;
	ग_लिखोl(FLAG_CF, &oxu->regs->configured_flag);
	पढ़ोl(&oxu->regs->command);	/* unblock posted ग_लिखोs */

	temp = HC_VERSION(पढ़ोl(&oxu->caps->hc_capbase));
	oxu_info(oxu, "USB %x.%x started, quasi-EHCI %x.%02x, driver %s%s\n",
		((oxu->sbrn & 0xf0)>>4), (oxu->sbrn & 0x0f),
		temp >> 8, temp & 0xff, DRIVER_VERSION,
		ignore_oc ? ", overcurrent ignored" : "");

	ग_लिखोl(INTR_MASK, &oxu->regs->पूर्णांकr_enable); /* Turn On Interrupts */

	वापस 0;
पूर्ण

अटल व्योम oxu_stop(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा oxu_hcd *oxu = hcd_to_oxu(hcd);

	/* Turn off port घातer on all root hub ports. */
	ehci_port_घातer(oxu, 0);

	/* no more पूर्णांकerrupts ... */
	del_समयr_sync(&oxu->watchकरोg);

	spin_lock_irq(&oxu->lock);
	अगर (HC_IS_RUNNING(hcd->state))
		ehci_quiesce(oxu);

	ehci_reset(oxu);
	ग_लिखोl(0, &oxu->regs->पूर्णांकr_enable);
	spin_unlock_irq(&oxu->lock);

	/* let companion controllers work when we aren't */
	ग_लिखोl(0, &oxu->regs->configured_flag);

	/* root hub is shut करोwn separately (first, when possible) */
	spin_lock_irq(&oxu->lock);
	अगर (oxu->async)
		ehci_work(oxu);
	spin_unlock_irq(&oxu->lock);
	ehci_mem_cleanup(oxu);

	dbg_status(oxu, "oxu_stop completed", पढ़ोl(&oxu->regs->status));
पूर्ण

/* Kick in क्रम silicon on any bus (not just pci, etc).
 * This क्रमcibly disables dma and IRQs, helping kexec and other हालs
 * where the next प्रणाली software may expect clean state.
 */
अटल व्योम oxu_shutकरोwn(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा oxu_hcd *oxu = hcd_to_oxu(hcd);

	(व्योम) ehci_halt(oxu);
	ehci_turn_off_all_ports(oxu);

	/* make BIOS/etc use companion controller during reboot */
	ग_लिखोl(0, &oxu->regs->configured_flag);

	/* unblock posted ग_लिखोs */
	पढ़ोl(&oxu->regs->configured_flag);
पूर्ण

/* Non-error वापसs are a promise to giveback() the urb later
 * we drop ownership so next owner (or urb unlink) can get it
 *
 * urb + dev is in hcd.self.controller.urb_list
 * we're queueing TDs onto software and hardware lists
 *
 * hcd-specअगरic init क्रम hcpriv hasn't been करोne yet
 *
 * NOTE:  control, bulk, and पूर्णांकerrupt share the same code to append TDs
 * to a (possibly active) QH, and the same QH scanning code.
 */
अटल पूर्णांक __oxu_urb_enqueue(काष्ठा usb_hcd *hcd, काष्ठा urb *urb,
				gfp_t mem_flags)
अणु
	काष्ठा oxu_hcd *oxu = hcd_to_oxu(hcd);
	काष्ठा list_head qtd_list;

	INIT_LIST_HEAD(&qtd_list);

	चयन (usb_pipetype(urb->pipe)) अणु
	हाल PIPE_CONTROL:
	हाल PIPE_BULK:
	शेष:
		अगर (!qh_urb_transaction(oxu, urb, &qtd_list, mem_flags))
			वापस -ENOMEM;
		वापस submit_async(oxu, urb, &qtd_list, mem_flags);

	हाल PIPE_INTERRUPT:
		अगर (!qh_urb_transaction(oxu, urb, &qtd_list, mem_flags))
			वापस -ENOMEM;
		वापस पूर्णांकr_submit(oxu, urb, &qtd_list, mem_flags);

	हाल PIPE_ISOCHRONOUS:
		अगर (urb->dev->speed == USB_SPEED_HIGH)
			वापस itd_submit(oxu, urb, mem_flags);
		अन्यथा
			वापस sitd_submit(oxu, urb, mem_flags);
	पूर्ण
पूर्ण

/* This function is responsible क्रम अवरोधing URBs with big data size
 * पूर्णांकo smaller size and processing small urbs in sequence.
 */
अटल पूर्णांक oxu_urb_enqueue(काष्ठा usb_hcd *hcd, काष्ठा urb *urb,
				gfp_t mem_flags)
अणु
	काष्ठा oxu_hcd *oxu = hcd_to_oxu(hcd);
	पूर्णांक num, rem;
	व्योम *transfer_buffer;
	काष्ठा urb *murb;
	पूर्णांक i, ret;

	/* If not bulk pipe just enqueue the URB */
	अगर (!usb_pipebulk(urb->pipe))
		वापस __oxu_urb_enqueue(hcd, urb, mem_flags);

	/* Otherwise we should verअगरy the USB transfer buffer size! */
	transfer_buffer = urb->transfer_buffer;

	num = urb->transfer_buffer_length / 4096;
	rem = urb->transfer_buffer_length % 4096;
	अगर (rem != 0)
		num++;

	/* If URB is smaller than 4096 bytes just enqueue it! */
	अगर (num == 1)
		वापस __oxu_urb_enqueue(hcd, urb, mem_flags);

	/* Ok, we have more job to करो! :) */

	क्रम (i = 0; i < num - 1; i++) अणु
		/* Get मुक्त micro URB poll till a मुक्त urb is received */

		करो अणु
			murb = (काष्ठा urb *) oxu_murb_alloc(oxu);
			अगर (!murb)
				schedule();
		पूर्ण जबतक (!murb);

		/* Coping the urb */
		स_नकल(murb, urb, माप(काष्ठा urb));

		murb->transfer_buffer_length = 4096;
		murb->transfer_buffer = transfer_buffer + i * 4096;

		/* Null poपूर्णांकer क्रम the encodes that this is a micro urb */
		murb->complete = शून्य;

		((काष्ठा oxu_murb *) murb)->मुख्य = urb;
		((काष्ठा oxu_murb *) murb)->last = 0;

		/* This loop is to guarantee urb to be processed when there's
		 * not enough resources at a particular समय by retrying.
		 */
		करो अणु
			ret  = __oxu_urb_enqueue(hcd, murb, mem_flags);
			अगर (ret)
				schedule();
		पूर्ण जबतक (ret);
	पूर्ण

	/* Last urb requires special handling  */

	/* Get मुक्त micro URB poll till a मुक्त urb is received */
	करो अणु
		murb = (काष्ठा urb *) oxu_murb_alloc(oxu);
		अगर (!murb)
			schedule();
	पूर्ण जबतक (!murb);

	/* Coping the urb */
	स_नकल(murb, urb, माप(काष्ठा urb));

	murb->transfer_buffer_length = rem > 0 ? rem : 4096;
	murb->transfer_buffer = transfer_buffer + (num - 1) * 4096;

	/* Null poपूर्णांकer क्रम the encodes that this is a micro urb */
	murb->complete = शून्य;

	((काष्ठा oxu_murb *) murb)->मुख्य = urb;
	((काष्ठा oxu_murb *) murb)->last = 1;

	करो अणु
		ret = __oxu_urb_enqueue(hcd, murb, mem_flags);
		अगर (ret)
			schedule();
	पूर्ण जबतक (ret);

	वापस ret;
पूर्ण

/* Remove from hardware lists.
 * Completions normally happen asynchronously
 */
अटल पूर्णांक oxu_urb_dequeue(काष्ठा usb_hcd *hcd, काष्ठा urb *urb, पूर्णांक status)
अणु
	काष्ठा oxu_hcd *oxu = hcd_to_oxu(hcd);
	काष्ठा ehci_qh *qh;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&oxu->lock, flags);
	चयन (usb_pipetype(urb->pipe)) अणु
	हाल PIPE_CONTROL:
	हाल PIPE_BULK:
	शेष:
		qh = (काष्ठा ehci_qh *) urb->hcpriv;
		अगर (!qh)
			अवरोध;
		unlink_async(oxu, qh);
		अवरोध;

	हाल PIPE_INTERRUPT:
		qh = (काष्ठा ehci_qh *) urb->hcpriv;
		अगर (!qh)
			अवरोध;
		चयन (qh->qh_state) अणु
		हाल QH_STATE_LINKED:
			पूर्णांकr_deschedule(oxu, qh);
			fallthrough;
		हाल QH_STATE_IDLE:
			qh_completions(oxu, qh);
			अवरोध;
		शेष:
			oxu_dbg(oxu, "bogus qh %p state %d\n",
					qh, qh->qh_state);
			जाओ करोne;
		पूर्ण

		/* reschedule QH अगरf another request is queued */
		अगर (!list_empty(&qh->qtd_list)
				&& HC_IS_RUNNING(hcd->state)) अणु
			पूर्णांक status;

			status = qh_schedule(oxu, qh);
			spin_unlock_irqrestore(&oxu->lock, flags);

			अगर (status != 0) अणु
				/* shouldn't happen often, but ...
				 * FIXME समाप्त those tds' urbs
				 */
				dev_err(hcd->self.controller,
					"can't reschedule qh %p, err %d\n", qh,
					status);
			पूर्ण
			वापस status;
		पूर्ण
		अवरोध;
	पूर्ण
करोne:
	spin_unlock_irqrestore(&oxu->lock, flags);
	वापस 0;
पूर्ण

/* Bulk qh holds the data toggle */
अटल व्योम oxu_endpoपूर्णांक_disable(काष्ठा usb_hcd *hcd,
					काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	काष्ठा oxu_hcd *oxu = hcd_to_oxu(hcd);
	अचिन्हित दीर्घ		flags;
	काष्ठा ehci_qh		*qh, *पंचांगp;

	/* ASSERT:  any requests/urbs are being unlinked */
	/* ASSERT:  nobody can be submitting urbs क्रम this any more */

rescan:
	spin_lock_irqsave(&oxu->lock, flags);
	qh = ep->hcpriv;
	अगर (!qh)
		जाओ करोne;

	/* endpoपूर्णांकs can be iso streams.  क्रम now, we करोn't
	 * accelerate iso completions ... so spin a जबतक.
	 */
	अगर (qh->hw_info1 == 0) अणु
		oxu_vdbg(oxu, "iso delay\n");
		जाओ idle_समयout;
	पूर्ण

	अगर (!HC_IS_RUNNING(hcd->state))
		qh->qh_state = QH_STATE_IDLE;
	चयन (qh->qh_state) अणु
	हाल QH_STATE_LINKED:
		क्रम (पंचांगp = oxu->async->qh_next.qh;
				पंचांगp && पंचांगp != qh;
				पंचांगp = पंचांगp->qh_next.qh)
			जारी;
		/* periodic qh self-unlinks on empty */
		अगर (!पंचांगp)
			जाओ nogood;
		unlink_async(oxu, qh);
		fallthrough;
	हाल QH_STATE_UNLINK:		/* रुको क्रम hw to finish? */
idle_समयout:
		spin_unlock_irqrestore(&oxu->lock, flags);
		schedule_समयout_unपूर्णांकerruptible(1);
		जाओ rescan;
	हाल QH_STATE_IDLE:		/* fully unlinked */
		अगर (list_empty(&qh->qtd_list)) अणु
			qh_put(qh);
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
nogood:
		/* caller was supposed to have unlinked any requests;
		 * that's not our job.  just leak this memory.
		 */
		oxu_err(oxu, "qh %p (#%02x) state %d%s\n",
			qh, ep->desc.bEndpoपूर्णांकAddress, qh->qh_state,
			list_empty(&qh->qtd_list) ? "" : "(has tds)");
		अवरोध;
	पूर्ण
	ep->hcpriv = शून्य;
करोne:
	spin_unlock_irqrestore(&oxu->lock, flags);
पूर्ण

अटल पूर्णांक oxu_get_frame(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा oxu_hcd *oxu = hcd_to_oxu(hcd);

	वापस (पढ़ोl(&oxu->regs->frame_index) >> 3) %
		oxu->periodic_size;
पूर्ण

/* Build "status change" packet (one or two bytes) from HC रेजिस्टरs */
अटल पूर्णांक oxu_hub_status_data(काष्ठा usb_hcd *hcd, अक्षर *buf)
अणु
	काष्ठा oxu_hcd *oxu = hcd_to_oxu(hcd);
	u32 temp, mask, status = 0;
	पूर्णांक ports, i, retval = 1;
	अचिन्हित दीर्घ flags;

	/* अगर !PM, root hub समयrs won't get shut करोwn ... */
	अगर (!HC_IS_RUNNING(hcd->state))
		वापस 0;

	/* init status to no-changes */
	buf[0] = 0;
	ports = HCS_N_PORTS(oxu->hcs_params);
	अगर (ports > 7) अणु
		buf[1] = 0;
		retval++;
	पूर्ण

	/* Some boards (mostly VIA?) report bogus overcurrent indications,
	 * causing massive log spam unless we completely ignore them.  It
	 * may be relevant that VIA VT8235 controllers, where PORT_POWER is
	 * always set, seem to clear PORT_OCC and PORT_CSC when writing to
	 * PORT_POWER; that's surprising, but maybe within-spec.
	 */
	अगर (!ignore_oc)
		mask = PORT_CSC | PORT_PEC | PORT_OCC;
	अन्यथा
		mask = PORT_CSC | PORT_PEC;

	/* no hub change reports (bit 0) क्रम now (घातer, ...) */

	/* port N changes (bit N)? */
	spin_lock_irqsave(&oxu->lock, flags);
	क्रम (i = 0; i < ports; i++) अणु
		temp = पढ़ोl(&oxu->regs->port_status[i]);

		/*
		 * Return status inक्रमmation even क्रम ports with OWNER set.
		 * Otherwise hub_wq wouldn't see the disconnect event when a
		 * high-speed device is चयनed over to the companion
		 * controller by the user.
		 */

		अगर (!(temp & PORT_CONNECT))
			oxu->reset_करोne[i] = 0;
		अगर ((temp & mask) != 0 || ((temp & PORT_RESUME) != 0 &&
				समय_after_eq(jअगरfies, oxu->reset_करोne[i]))) अणु
			अगर (i < 7)
				buf[0] |= 1 << (i + 1);
			अन्यथा
				buf[1] |= 1 << (i - 7);
			status = STS_PCD;
		पूर्ण
	पूर्ण
	/* FIXME स्वतःsuspend idle root hubs */
	spin_unlock_irqrestore(&oxu->lock, flags);
	वापस status ? retval : 0;
पूर्ण

/* Returns the speed of a device attached to a port on the root hub. */
अटल अंतरभूत अचिन्हित पूर्णांक oxu_port_speed(काष्ठा oxu_hcd *oxu,
						अचिन्हित पूर्णांक portsc)
अणु
	चयन ((portsc >> 26) & 3) अणु
	हाल 0:
		वापस 0;
	हाल 1:
		वापस USB_PORT_STAT_LOW_SPEED;
	हाल 2:
	शेष:
		वापस USB_PORT_STAT_HIGH_SPEED;
	पूर्ण
पूर्ण

#घोषणा	PORT_WAKE_BITS	(PORT_WKOC_E|PORT_WKDISC_E|PORT_WKCONN_E)
अटल पूर्णांक oxu_hub_control(काष्ठा usb_hcd *hcd, u16 typeReq,
				u16 wValue, u16 wIndex, अक्षर *buf, u16 wLength)
अणु
	काष्ठा oxu_hcd *oxu = hcd_to_oxu(hcd);
	पूर्णांक ports = HCS_N_PORTS(oxu->hcs_params);
	u32 __iomem *status_reg = &oxu->regs->port_status[wIndex - 1];
	u32 temp, status;
	अचिन्हित दीर्घ	flags;
	पूर्णांक retval = 0;
	अचिन्हित selector;

	/*
	 * FIXME:  support SetPortFeatures USB_PORT_FEAT_INDICATOR.
	 * HCS_INDICATOR may say we can change LEDs to off/amber/green.
	 * (track current state ourselves) ... blink क्रम diagnostics,
	 * घातer, "this is the one", etc.  EHCI spec supports this.
	 */

	spin_lock_irqsave(&oxu->lock, flags);
	चयन (typeReq) अणु
	हाल ClearHubFeature:
		चयन (wValue) अणु
		हाल C_HUB_LOCAL_POWER:
		हाल C_HUB_OVER_CURRENT:
			/* no hub-wide feature/status flags */
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		अवरोध;
	हाल ClearPortFeature:
		अगर (!wIndex || wIndex > ports)
			जाओ error;
		wIndex--;
		temp = पढ़ोl(status_reg);

		/*
		 * Even अगर OWNER is set, so the port is owned by the
		 * companion controller, hub_wq needs to be able to clear
		 * the port-change status bits (especially
		 * USB_PORT_STAT_C_CONNECTION).
		 */

		चयन (wValue) अणु
		हाल USB_PORT_FEAT_ENABLE:
			ग_लिखोl(temp & ~PORT_PE, status_reg);
			अवरोध;
		हाल USB_PORT_FEAT_C_ENABLE:
			ग_लिखोl((temp & ~PORT_RWC_BITS) | PORT_PEC, status_reg);
			अवरोध;
		हाल USB_PORT_FEAT_SUSPEND:
			अगर (temp & PORT_RESET)
				जाओ error;
			अगर (temp & PORT_SUSPEND) अणु
				अगर ((temp & PORT_PE) == 0)
					जाओ error;
				/* resume संकेतing क्रम 20 msec */
				temp &= ~(PORT_RWC_BITS | PORT_WAKE_BITS);
				ग_लिखोl(temp | PORT_RESUME, status_reg);
				oxu->reset_करोne[wIndex] = jअगरfies
						+ msecs_to_jअगरfies(20);
			पूर्ण
			अवरोध;
		हाल USB_PORT_FEAT_C_SUSPEND:
			/* we स्वतः-clear this feature */
			अवरोध;
		हाल USB_PORT_FEAT_POWER:
			अगर (HCS_PPC(oxu->hcs_params))
				ग_लिखोl(temp & ~(PORT_RWC_BITS | PORT_POWER),
					  status_reg);
			अवरोध;
		हाल USB_PORT_FEAT_C_CONNECTION:
			ग_लिखोl((temp & ~PORT_RWC_BITS) | PORT_CSC, status_reg);
			अवरोध;
		हाल USB_PORT_FEAT_C_OVER_CURRENT:
			ग_लिखोl((temp & ~PORT_RWC_BITS) | PORT_OCC, status_reg);
			अवरोध;
		हाल USB_PORT_FEAT_C_RESET:
			/* GetPortStatus clears reset */
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		पढ़ोl(&oxu->regs->command);	/* unblock posted ग_लिखो */
		अवरोध;
	हाल GetHubDescriptor:
		ehci_hub_descriptor(oxu, (काष्ठा usb_hub_descriptor *)
			buf);
		अवरोध;
	हाल GetHubStatus:
		/* no hub-wide feature/status flags */
		स_रखो(buf, 0, 4);
		अवरोध;
	हाल GetPortStatus:
		अगर (!wIndex || wIndex > ports)
			जाओ error;
		wIndex--;
		status = 0;
		temp = पढ़ोl(status_reg);

		/* wPortChange bits */
		अगर (temp & PORT_CSC)
			status |= USB_PORT_STAT_C_CONNECTION << 16;
		अगर (temp & PORT_PEC)
			status |= USB_PORT_STAT_C_ENABLE << 16;
		अगर ((temp & PORT_OCC) && !ignore_oc)
			status |= USB_PORT_STAT_C_OVERCURRENT << 16;

		/* whoever resumes must GetPortStatus to complete it!! */
		अगर (temp & PORT_RESUME) अणु

			/* Remote Wakeup received? */
			अगर (!oxu->reset_करोne[wIndex]) अणु
				/* resume संकेतing क्रम 20 msec */
				oxu->reset_करोne[wIndex] = jअगरfies
						+ msecs_to_jअगरfies(20);
				/* check the port again */
				mod_समयr(&oxu_to_hcd(oxu)->rh_समयr,
						oxu->reset_करोne[wIndex]);
			पूर्ण

			/* resume completed? */
			अन्यथा अगर (समय_after_eq(jअगरfies,
					oxu->reset_करोne[wIndex])) अणु
				status |= USB_PORT_STAT_C_SUSPEND << 16;
				oxu->reset_करोne[wIndex] = 0;

				/* stop resume संकेतing */
				temp = पढ़ोl(status_reg);
				ग_लिखोl(temp & ~(PORT_RWC_BITS | PORT_RESUME),
					status_reg);
				retval = handshake(oxu, status_reg,
					   PORT_RESUME, 0, 2000 /* 2msec */);
				अगर (retval != 0) अणु
					oxu_err(oxu,
						"port %d resume error %d\n",
						wIndex + 1, retval);
					जाओ error;
				पूर्ण
				temp &= ~(PORT_SUSPEND|PORT_RESUME|(3<<10));
			पूर्ण
		पूर्ण

		/* whoever resets must GetPortStatus to complete it!! */
		अगर ((temp & PORT_RESET)
				&& समय_after_eq(jअगरfies,
					oxu->reset_करोne[wIndex])) अणु
			status |= USB_PORT_STAT_C_RESET << 16;
			oxu->reset_करोne[wIndex] = 0;

			/* क्रमce reset to complete */
			ग_लिखोl(temp & ~(PORT_RWC_BITS | PORT_RESET),
					status_reg);
			/* REVISIT:  some hardware needs 550+ usec to clear
			 * this bit; seems too दीर्घ to spin routinely...
			 */
			retval = handshake(oxu, status_reg,
					PORT_RESET, 0, 750);
			अगर (retval != 0) अणु
				oxu_err(oxu, "port %d reset error %d\n",
					wIndex + 1, retval);
				जाओ error;
			पूर्ण

			/* see what we found out */
			temp = check_reset_complete(oxu, wIndex, status_reg,
					पढ़ोl(status_reg));
		पूर्ण

		/* transfer dedicated ports to the companion hc */
		अगर ((temp & PORT_CONNECT) &&
				test_bit(wIndex, &oxu->companion_ports)) अणु
			temp &= ~PORT_RWC_BITS;
			temp |= PORT_OWNER;
			ग_लिखोl(temp, status_reg);
			oxu_dbg(oxu, "port %d --> companion\n", wIndex + 1);
			temp = पढ़ोl(status_reg);
		पूर्ण

		/*
		 * Even अगर OWNER is set, there's no harm letting hub_wq
		 * see the wPortStatus values (they should all be 0 except
		 * क्रम PORT_POWER anyway).
		 */

		अगर (temp & PORT_CONNECT) अणु
			status |= USB_PORT_STAT_CONNECTION;
			/* status may be from पूर्णांकegrated TT */
			status |= oxu_port_speed(oxu, temp);
		पूर्ण
		अगर (temp & PORT_PE)
			status |= USB_PORT_STAT_ENABLE;
		अगर (temp & (PORT_SUSPEND|PORT_RESUME))
			status |= USB_PORT_STAT_SUSPEND;
		अगर (temp & PORT_OC)
			status |= USB_PORT_STAT_OVERCURRENT;
		अगर (temp & PORT_RESET)
			status |= USB_PORT_STAT_RESET;
		अगर (temp & PORT_POWER)
			status |= USB_PORT_STAT_POWER;

#अगर_अघोषित	OXU_VERBOSE_DEBUG
	अगर (status & ~0xffff)	/* only अगर wPortChange is पूर्णांकeresting */
#पूर्ण_अगर
		dbg_port(oxu, "GetStatus", wIndex + 1, temp);
		put_unaligned(cpu_to_le32(status), (__le32 *) buf);
		अवरोध;
	हाल SetHubFeature:
		चयन (wValue) अणु
		हाल C_HUB_LOCAL_POWER:
		हाल C_HUB_OVER_CURRENT:
			/* no hub-wide feature/status flags */
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		अवरोध;
	हाल SetPortFeature:
		selector = wIndex >> 8;
		wIndex &= 0xff;
		अगर (!wIndex || wIndex > ports)
			जाओ error;
		wIndex--;
		temp = पढ़ोl(status_reg);
		अगर (temp & PORT_OWNER)
			अवरोध;

		temp &= ~PORT_RWC_BITS;
		चयन (wValue) अणु
		हाल USB_PORT_FEAT_SUSPEND:
			अगर ((temp & PORT_PE) == 0
					|| (temp & PORT_RESET) != 0)
				जाओ error;
			अगर (device_may_wakeup(&hcd->self.root_hub->dev))
				temp |= PORT_WAKE_BITS;
			ग_लिखोl(temp | PORT_SUSPEND, status_reg);
			अवरोध;
		हाल USB_PORT_FEAT_POWER:
			अगर (HCS_PPC(oxu->hcs_params))
				ग_लिखोl(temp | PORT_POWER, status_reg);
			अवरोध;
		हाल USB_PORT_FEAT_RESET:
			अगर (temp & PORT_RESUME)
				जाओ error;
			/* line status bits may report this as low speed,
			 * which can be fine अगर this root hub has a
			 * transaction translator built in.
			 */
			oxu_vdbg(oxu, "port %d reset\n", wIndex + 1);
			temp |= PORT_RESET;
			temp &= ~PORT_PE;

			/*
			 * caller must रुको, then call GetPortStatus
			 * usb 2.0 spec says 50 ms resets on root
			 */
			oxu->reset_करोne[wIndex] = jअगरfies
					+ msecs_to_jअगरfies(50);
			ग_लिखोl(temp, status_reg);
			अवरोध;

		/* For करोwnstream facing ports (these):  one hub port is put
		 * पूर्णांकo test mode according to USB2 11.24.2.13, then the hub
		 * must be reset (which क्रम root hub now means rmmod+modprobe,
		 * or अन्यथा प्रणाली reboot).  See EHCI 2.3.9 and 4.14 क्रम info
		 * about the EHCI-specअगरic stuff.
		 */
		हाल USB_PORT_FEAT_TEST:
			अगर (!selector || selector > 5)
				जाओ error;
			ehci_quiesce(oxu);
			ehci_halt(oxu);
			temp |= selector << 16;
			ग_लिखोl(temp, status_reg);
			अवरोध;

		शेष:
			जाओ error;
		पूर्ण
		पढ़ोl(&oxu->regs->command);	/* unblock posted ग_लिखोs */
		अवरोध;

	शेष:
error:
		/* "stall" on error */
		retval = -EPIPE;
	पूर्ण
	spin_unlock_irqrestore(&oxu->lock, flags);
	वापस retval;
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक oxu_bus_suspend(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा oxu_hcd *oxu = hcd_to_oxu(hcd);
	पूर्णांक port;
	पूर्णांक mask;

	oxu_dbg(oxu, "suspend root hub\n");

	अगर (समय_beक्रमe(jअगरfies, oxu->next_statechange))
		msleep(5);

	port = HCS_N_PORTS(oxu->hcs_params);
	spin_lock_irq(&oxu->lock);

	/* stop schedules, clean any completed work */
	अगर (HC_IS_RUNNING(hcd->state)) अणु
		ehci_quiesce(oxu);
		hcd->state = HC_STATE_QUIESCING;
	पूर्ण
	oxu->command = पढ़ोl(&oxu->regs->command);
	अगर (oxu->reclaim)
		oxu->reclaim_पढ़ोy = 1;
	ehci_work(oxu);

	/* Unlike other USB host controller types, EHCI करोesn't have
	 * any notion of "global" or bus-wide suspend.  The driver has
	 * to manually suspend all the active unsuspended ports, and
	 * then manually resume them in the bus_resume() routine.
	 */
	oxu->bus_suspended = 0;
	जबतक (port--) अणु
		u32 __iomem *reg = &oxu->regs->port_status[port];
		u32 t1 = पढ़ोl(reg) & ~PORT_RWC_BITS;
		u32 t2 = t1;

		/* keep track of which ports we suspend */
		अगर ((t1 & PORT_PE) && !(t1 & PORT_OWNER) &&
				!(t1 & PORT_SUSPEND)) अणु
			t2 |= PORT_SUSPEND;
			set_bit(port, &oxu->bus_suspended);
		पूर्ण

		/* enable remote wakeup on all ports */
		अगर (device_may_wakeup(&hcd->self.root_hub->dev))
			t2 |= PORT_WKOC_E|PORT_WKDISC_E|PORT_WKCONN_E;
		अन्यथा
			t2 &= ~(PORT_WKOC_E|PORT_WKDISC_E|PORT_WKCONN_E);

		अगर (t1 != t2) अणु
			oxu_vdbg(oxu, "port %d, %08x -> %08x\n",
				port + 1, t1, t2);
			ग_लिखोl(t2, reg);
		पूर्ण
	पूर्ण

	/* turn off now-idle HC */
	del_समयr_sync(&oxu->watchकरोg);
	ehci_halt(oxu);
	hcd->state = HC_STATE_SUSPENDED;

	/* allow remote wakeup */
	mask = INTR_MASK;
	अगर (!device_may_wakeup(&hcd->self.root_hub->dev))
		mask &= ~STS_PCD;
	ग_लिखोl(mask, &oxu->regs->पूर्णांकr_enable);
	पढ़ोl(&oxu->regs->पूर्णांकr_enable);

	oxu->next_statechange = jअगरfies + msecs_to_jअगरfies(10);
	spin_unlock_irq(&oxu->lock);
	वापस 0;
पूर्ण

/* Caller has locked the root hub, and should reset/reinit on error */
अटल पूर्णांक oxu_bus_resume(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा oxu_hcd *oxu = hcd_to_oxu(hcd);
	u32 temp;
	पूर्णांक i;

	अगर (समय_beक्रमe(jअगरfies, oxu->next_statechange))
		msleep(5);
	spin_lock_irq(&oxu->lock);

	/* Ideally and we've got a real resume here, and no port's घातer
	 * was lost.  (For PCI, that means Vaux was मुख्यtained.)  But we
	 * could instead be restoring a swsusp snapshot -- so that BIOS was
	 * the last user of the controller, not reset/pm hardware keeping
	 * state we gave to it.
	 */
	temp = पढ़ोl(&oxu->regs->पूर्णांकr_enable);
	oxu_dbg(oxu, "resume root hub%s\n", temp ? "" : " after power loss");

	/* at least some APM implementations will try to deliver
	 * IRQs right away, so delay them until we're पढ़ोy.
	 */
	ग_लिखोl(0, &oxu->regs->पूर्णांकr_enable);

	/* re-init operational रेजिस्टरs */
	ग_लिखोl(0, &oxu->regs->segment);
	ग_लिखोl(oxu->periodic_dma, &oxu->regs->frame_list);
	ग_लिखोl((u32) oxu->async->qh_dma, &oxu->regs->async_next);

	/* restore CMD_RUN, framelist size, and irq threshold */
	ग_लिखोl(oxu->command, &oxu->regs->command);

	/* Some controller/firmware combinations need a delay during which
	 * they set up the port statuses.  See Bugzilla #8190. */
	mdelay(8);

	/* manually resume the ports we suspended during bus_suspend() */
	i = HCS_N_PORTS(oxu->hcs_params);
	जबतक (i--) अणु
		temp = पढ़ोl(&oxu->regs->port_status[i]);
		temp &= ~(PORT_RWC_BITS
			| PORT_WKOC_E | PORT_WKDISC_E | PORT_WKCONN_E);
		अगर (test_bit(i, &oxu->bus_suspended) && (temp & PORT_SUSPEND)) अणु
			oxu->reset_करोne[i] = jअगरfies + msecs_to_jअगरfies(20);
			temp |= PORT_RESUME;
		पूर्ण
		ग_लिखोl(temp, &oxu->regs->port_status[i]);
	पूर्ण
	i = HCS_N_PORTS(oxu->hcs_params);
	mdelay(20);
	जबतक (i--) अणु
		temp = पढ़ोl(&oxu->regs->port_status[i]);
		अगर (test_bit(i, &oxu->bus_suspended) && (temp & PORT_SUSPEND)) अणु
			temp &= ~(PORT_RWC_BITS | PORT_RESUME);
			ग_लिखोl(temp, &oxu->regs->port_status[i]);
			oxu_vdbg(oxu, "resumed port %d\n", i + 1);
		पूर्ण
	पूर्ण
	(व्योम) पढ़ोl(&oxu->regs->command);

	/* maybe re-activate the schedule(s) */
	temp = 0;
	अगर (oxu->async->qh_next.qh)
		temp |= CMD_ASE;
	अगर (oxu->periodic_sched)
		temp |= CMD_PSE;
	अगर (temp) अणु
		oxu->command |= temp;
		ग_लिखोl(oxu->command, &oxu->regs->command);
	पूर्ण

	oxu->next_statechange = jअगरfies + msecs_to_jअगरfies(5);
	hcd->state = HC_STATE_RUNNING;

	/* Now we can safely re-enable irqs */
	ग_लिखोl(INTR_MASK, &oxu->regs->पूर्णांकr_enable);

	spin_unlock_irq(&oxu->lock);
	वापस 0;
पूर्ण

#अन्यथा

अटल पूर्णांक oxu_bus_suspend(काष्ठा usb_hcd *hcd)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक oxu_bus_resume(काष्ठा usb_hcd *hcd)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर	/* CONFIG_PM */

अटल स्थिर काष्ठा hc_driver oxu_hc_driver = अणु
	.description =		"oxu210hp_hcd",
	.product_desc =		"oxu210hp HCD",
	.hcd_priv_size =	माप(काष्ठा oxu_hcd),

	/*
	 * Generic hardware linkage
	 */
	.irq =			oxu_irq,
	.flags =		HCD_MEMORY | HCD_USB2,

	/*
	 * Basic lअगरecycle operations
	 */
	.reset =		oxu_reset,
	.start =		oxu_run,
	.stop =			oxu_stop,
	.shutकरोwn =		oxu_shutकरोwn,

	/*
	 * Managing i/o requests and associated device resources
	 */
	.urb_enqueue =		oxu_urb_enqueue,
	.urb_dequeue =		oxu_urb_dequeue,
	.endpoपूर्णांक_disable =	oxu_endpoपूर्णांक_disable,

	/*
	 * Scheduling support
	 */
	.get_frame_number =	oxu_get_frame,

	/*
	 * Root hub support
	 */
	.hub_status_data =	oxu_hub_status_data,
	.hub_control =		oxu_hub_control,
	.bus_suspend =		oxu_bus_suspend,
	.bus_resume =		oxu_bus_resume,
पूर्ण;

/*
 * Module stuff
 */

अटल व्योम oxu_configuration(काष्ठा platक्रमm_device *pdev, व्योम __iomem *base)
अणु
	u32 पंचांगp;

	/* Initialize top level रेजिस्टरs.
	 * First ग_लिखो ever
	 */
	oxu_ग_लिखोl(base, OXU_HOSTIFCONFIG, 0x0000037D);
	oxu_ग_लिखोl(base, OXU_SOFTRESET, OXU_SRESET);
	oxu_ग_लिखोl(base, OXU_HOSTIFCONFIG, 0x0000037D);

	पंचांगp = oxu_पढ़ोl(base, OXU_PIOBURSTREADCTRL);
	oxu_ग_लिखोl(base, OXU_PIOBURSTREADCTRL, पंचांगp | 0x0040);

	oxu_ग_लिखोl(base, OXU_ASO, OXU_SPHPOEN | OXU_OVRCCURPUPDEN |
					OXU_COMPARATOR | OXU_ASO_OP);

	पंचांगp = oxu_पढ़ोl(base, OXU_CLKCTRL_SET);
	oxu_ग_लिखोl(base, OXU_CLKCTRL_SET, पंचांगp | OXU_SYSCLKEN | OXU_USBOTGCLKEN);

	/* Clear all top पूर्णांकerrupt enable */
	oxu_ग_लिखोl(base, OXU_CHIPIRQEN_CLR, 0xff);

	/* Clear all top पूर्णांकerrupt status */
	oxu_ग_लिखोl(base, OXU_CHIPIRQSTATUS, 0xff);

	/* Enable all needed top पूर्णांकerrupt except OTG SPH core */
	oxu_ग_लिखोl(base, OXU_CHIPIRQEN_SET, OXU_USBSPHLPWUI | OXU_USBOTGLPWUI);
पूर्ण

अटल पूर्णांक oxu_verअगरy_id(काष्ठा platक्रमm_device *pdev, व्योम __iomem *base)
अणु
	u32 id;
	अटल स्थिर अक्षर * स्थिर bo[] = अणु
		"reserved",
		"128-pin LQFP",
		"84-pin TFBGA",
		"reserved",
	पूर्ण;

	/* Read controller signature रेजिस्टर to find a match */
	id = oxu_पढ़ोl(base, OXU_DEVICEID);
	dev_info(&pdev->dev, "device ID %x\n", id);
	अगर ((id & OXU_REV_MASK) != (OXU_REV_2100 << OXU_REV_SHIFT))
		वापस -1;

	dev_info(&pdev->dev, "found device %x %s (%04x:%04x)\n",
		id >> OXU_REV_SHIFT,
		bo[(id & OXU_BO_MASK) >> OXU_BO_SHIFT],
		(id & OXU_MAJ_REV_MASK) >> OXU_MAJ_REV_SHIFT,
		(id & OXU_MIN_REV_MASK) >> OXU_MIN_REV_SHIFT);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hc_driver oxu_hc_driver;
अटल काष्ठा usb_hcd *oxu_create(काष्ठा platक्रमm_device *pdev,
				अचिन्हित दीर्घ memstart, अचिन्हित दीर्घ memlen,
				व्योम __iomem *base, पूर्णांक irq, पूर्णांक otg)
अणु
	काष्ठा device *dev = &pdev->dev;

	काष्ठा usb_hcd *hcd;
	काष्ठा oxu_hcd *oxu;
	पूर्णांक ret;

	/* Set endian mode and host mode */
	oxu_ग_लिखोl(base + (otg ? OXU_OTG_CORE_OFFSET : OXU_SPH_CORE_OFFSET),
				OXU_USBMODE,
				OXU_CM_HOST_ONLY | OXU_ES_LITTLE | OXU_VBPS);

	hcd = usb_create_hcd(&oxu_hc_driver, dev,
				otg ? "oxu210hp_otg" : "oxu210hp_sph");
	अगर (!hcd)
		वापस ERR_PTR(-ENOMEM);

	hcd->rsrc_start = memstart;
	hcd->rsrc_len = memlen;
	hcd->regs = base;
	hcd->irq = irq;
	hcd->state = HC_STATE_HALT;

	oxu = hcd_to_oxu(hcd);
	oxu->is_otg = otg;

	ret = usb_add_hcd(hcd, irq, IRQF_SHARED);
	अगर (ret < 0) अणु
		usb_put_hcd(hcd);
		वापस ERR_PTR(ret);
	पूर्ण

	device_wakeup_enable(hcd->self.controller);
	वापस hcd;
पूर्ण

अटल पूर्णांक oxu_init(काष्ठा platक्रमm_device *pdev,
				अचिन्हित दीर्घ memstart, अचिन्हित दीर्घ memlen,
				व्योम __iomem *base, पूर्णांक irq)
अणु
	काष्ठा oxu_info *info = platक्रमm_get_drvdata(pdev);
	काष्ठा usb_hcd *hcd;
	पूर्णांक ret;

	/* First समय configuration at start up */
	oxu_configuration(pdev, base);

	ret = oxu_verअगरy_id(pdev, base);
	अगर (ret) अणु
		dev_err(&pdev->dev, "no devices found!\n");
		वापस -ENODEV;
	पूर्ण

	/* Create the OTG controller */
	hcd = oxu_create(pdev, memstart, memlen, base, irq, 1);
	अगर (IS_ERR(hcd)) अणु
		dev_err(&pdev->dev, "cannot create OTG controller!\n");
		ret = PTR_ERR(hcd);
		जाओ error_create_otg;
	पूर्ण
	info->hcd[0] = hcd;

	/* Create the SPH host controller */
	hcd = oxu_create(pdev, memstart, memlen, base, irq, 0);
	अगर (IS_ERR(hcd)) अणु
		dev_err(&pdev->dev, "cannot create SPH controller!\n");
		ret = PTR_ERR(hcd);
		जाओ error_create_sph;
	पूर्ण
	info->hcd[1] = hcd;

	oxu_ग_लिखोl(base, OXU_CHIPIRQEN_SET,
		oxu_पढ़ोl(base, OXU_CHIPIRQEN_SET) | 3);

	वापस 0;

error_create_sph:
	usb_हटाओ_hcd(info->hcd[0]);
	usb_put_hcd(info->hcd[0]);

error_create_otg:
	वापस ret;
पूर्ण

अटल पूर्णांक oxu_drv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	व्योम __iomem *base;
	अचिन्हित दीर्घ memstart, memlen;
	पूर्णांक irq, ret;
	काष्ठा oxu_info *info;

	अगर (usb_disabled())
		वापस -ENODEV;

	/*
	 * Get the platक्रमm resources
	 */
	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev,
			"no IRQ! Check %s setup!\n", dev_name(&pdev->dev));
		वापस -ENODEV;
	पूर्ण
	irq = res->start;
	dev_dbg(&pdev->dev, "IRQ resource %d\n", irq);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base)) अणु
		ret = PTR_ERR(base);
		जाओ error;
	पूर्ण
	memstart = res->start;
	memlen = resource_size(res);

	ret = irq_set_irq_type(irq, IRQF_TRIGGER_FALLING);
	अगर (ret) अणु
		dev_err(&pdev->dev, "error setting irq type\n");
		ret = -EFAULT;
		जाओ error;
	पूर्ण

	/* Allocate a driver data काष्ठा to hold useful info क्रम both
	 * SPH & OTG devices
	 */
	info = devm_kzalloc(&pdev->dev, माप(काष्ठा oxu_info), GFP_KERNEL);
	अगर (!info) अणु
		ret = -EFAULT;
		जाओ error;
	पूर्ण
	platक्रमm_set_drvdata(pdev, info);

	ret = oxu_init(pdev, memstart, memlen, base, irq);
	अगर (ret < 0) अणु
		dev_dbg(&pdev->dev, "cannot init USB devices\n");
		जाओ error;
	पूर्ण

	dev_info(&pdev->dev, "devices enabled and running\n");
	platक्रमm_set_drvdata(pdev, info);

	वापस 0;

error:
	dev_err(&pdev->dev, "init %s fail, %d\n", dev_name(&pdev->dev), ret);
	वापस ret;
पूर्ण

अटल व्योम oxu_हटाओ(काष्ठा platक्रमm_device *pdev, काष्ठा usb_hcd *hcd)
अणु
	usb_हटाओ_hcd(hcd);
	usb_put_hcd(hcd);
पूर्ण

अटल पूर्णांक oxu_drv_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा oxu_info *info = platक्रमm_get_drvdata(pdev);

	oxu_हटाओ(pdev, info->hcd[0]);
	oxu_हटाओ(pdev, info->hcd[1]);

	वापस 0;
पूर्ण

अटल व्योम oxu_drv_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	oxu_drv_हटाओ(pdev);
पूर्ण

#अगर 0
/* FIXME: TODO */
अटल पूर्णांक oxu_drv_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा usb_hcd *hcd = dev_get_drvdata(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक oxu_drv_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा usb_hcd *hcd = dev_get_drvdata(dev);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा oxu_drv_suspend	शून्य
#घोषणा oxu_drv_resume	शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver oxu_driver = अणु
	.probe		= oxu_drv_probe,
	.हटाओ		= oxu_drv_हटाओ,
	.shutकरोwn	= oxu_drv_shutकरोwn,
	.suspend	= oxu_drv_suspend,
	.resume		= oxu_drv_resume,
	.driver = अणु
		.name = "oxu210hp-hcd",
		.bus = &platक्रमm_bus_type
	पूर्ण
पूर्ण;

module_platक्रमm_driver(oxu_driver);

MODULE_DESCRIPTION("Oxford OXU210HP HCD driver - ver. " DRIVER_VERSION);
MODULE_AUTHOR("Rodolfo Giometti <giometti@linux.it>");
MODULE_LICENSE("GPL");
