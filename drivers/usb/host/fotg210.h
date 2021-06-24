<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_FOTG210_H
#घोषणा __LINUX_FOTG210_H

#समावेश <linux/usb/ehci-dbgp.h>

/* definitions used क्रम the EHCI driver */

/*
 * __hc32 and __hc16 are "Host Controller" types, they may be equivalent to
 * __leXX (normally) or __beXX (given FOTG210_BIG_ENDIAN_DESC), depending on
 * the host controller implementation.
 *
 * To facilitate the strongest possible byte-order checking from "sparse"
 * and so on, we use __leXX unless that's not practical.
 */
#घोषणा __hc32	__le32
#घोषणा __hc16	__le16

/* statistics can be kept क्रम tuning/monitoring */
काष्ठा fotg210_stats अणु
	/* irq usage */
	अचिन्हित दीर्घ		normal;
	अचिन्हित दीर्घ		error;
	अचिन्हित दीर्घ		iaa;
	अचिन्हित दीर्घ		lost_iaa;

	/* termination of urbs from core */
	अचिन्हित दीर्घ		complete;
	अचिन्हित दीर्घ		unlink;
पूर्ण;

/* fotg210_hcd->lock guards shared data against other CPUs:
 *   fotg210_hcd:	async, unlink, periodic (and shaकरोw), ...
 *   usb_host_endpoपूर्णांक: hcpriv
 *   fotg210_qh:	qh_next, qtd_list
 *   fotg210_qtd:	qtd_list
 *
 * Also, hold this lock when talking to HC रेजिस्टरs or
 * when updating hw_* fields in shared qh/qtd/... काष्ठाures.
 */

#घोषणा	FOTG210_MAX_ROOT_PORTS	1		/* see HCS_N_PORTS */

/*
 * fotg210_rh_state values of FOTG210_RH_RUNNING or above mean that the
 * controller may be करोing DMA.  Lower values mean there's no DMA.
 */
क्रमागत fotg210_rh_state अणु
	FOTG210_RH_HALTED,
	FOTG210_RH_SUSPENDED,
	FOTG210_RH_RUNNING,
	FOTG210_RH_STOPPING
पूर्ण;

/*
 * Timer events, ordered by increasing delay length.
 * Always update event_delays_ns[] and event_handlers[] (defined in
 * ehci-समयr.c) in parallel with this list.
 */
क्रमागत fotg210_hrसमयr_event अणु
	FOTG210_HRTIMER_POLL_ASS,	/* Poll क्रम async schedule off */
	FOTG210_HRTIMER_POLL_PSS,	/* Poll क्रम periodic schedule off */
	FOTG210_HRTIMER_POLL_DEAD,	/* Wait क्रम dead controller to stop */
	FOTG210_HRTIMER_UNLINK_INTR,	/* Wait क्रम पूर्णांकerrupt QH unlink */
	FOTG210_HRTIMER_FREE_ITDS,	/* Wait क्रम unused iTDs and siTDs */
	FOTG210_HRTIMER_ASYNC_UNLINKS,	/* Unlink empty async QHs */
	FOTG210_HRTIMER_IAA_WATCHDOG,	/* Handle lost IAA पूर्णांकerrupts */
	FOTG210_HRTIMER_DISABLE_PERIODIC, /* Wait to disable periodic sched */
	FOTG210_HRTIMER_DISABLE_ASYNC,	/* Wait to disable async sched */
	FOTG210_HRTIMER_IO_WATCHDOG,	/* Check क्रम missing IRQs */
	FOTG210_HRTIMER_NUM_EVENTS	/* Must come last */
पूर्ण;
#घोषणा FOTG210_HRTIMER_NO_EVENT	99

काष्ठा fotg210_hcd अणु			/* one per controller */
	/* timing support */
	क्रमागत fotg210_hrसमयr_event	next_hrसमयr_event;
	अचिन्हित		enabled_hrसमयr_events;
	kसमय_प्रकार			hr_समयouts[FOTG210_HRTIMER_NUM_EVENTS];
	काष्ठा hrसमयr		hrसमयr;

	पूर्णांक			PSS_poll_count;
	पूर्णांक			ASS_poll_count;
	पूर्णांक			died_poll_count;

	/* glue to PCI and HCD framework */
	काष्ठा fotg210_caps __iomem *caps;
	काष्ठा fotg210_regs __iomem *regs;
	काष्ठा ehci_dbg_port __iomem *debug;

	__u32			hcs_params;	/* cached रेजिस्टर copy */
	spinlock_t		lock;
	क्रमागत fotg210_rh_state	rh_state;

	/* general schedule support */
	bool			scanning:1;
	bool			need_rescan:1;
	bool			पूर्णांकr_unlinking:1;
	bool			async_unlinking:1;
	bool			shutकरोwn:1;
	काष्ठा fotg210_qh		*qh_scan_next;

	/* async schedule support */
	काष्ठा fotg210_qh		*async;
	काष्ठा fotg210_qh		*dummy;		/* For AMD quirk use */
	काष्ठा fotg210_qh		*async_unlink;
	काष्ठा fotg210_qh		*async_unlink_last;
	काष्ठा fotg210_qh		*async_iaa;
	अचिन्हित		async_unlink_cycle;
	अचिन्हित		async_count;	/* async activity count */

	/* periodic schedule support */
#घोषणा	DEFAULT_I_TDPS		1024		/* some HCs can करो less */
	अचिन्हित		periodic_size;
	__hc32			*periodic;	/* hw periodic table */
	dma_addr_t		periodic_dma;
	काष्ठा list_head	पूर्णांकr_qh_list;
	अचिन्हित		i_thresh;	/* uframes HC might cache */

	जोड़ fotg210_shaकरोw	*pshaकरोw;	/* mirror hw periodic table */
	काष्ठा fotg210_qh		*पूर्णांकr_unlink;
	काष्ठा fotg210_qh		*पूर्णांकr_unlink_last;
	अचिन्हित		पूर्णांकr_unlink_cycle;
	अचिन्हित		now_frame;	/* frame from HC hardware */
	अचिन्हित		next_frame;	/* scan periodic, start here */
	अचिन्हित		पूर्णांकr_count;	/* पूर्णांकr activity count */
	अचिन्हित		isoc_count;	/* isoc activity count */
	अचिन्हित		periodic_count;	/* periodic activity count */
	/* max periodic समय per uframe */
	अचिन्हित		uframe_periodic_max;


	/* list of itds completed जबतक now_frame was still active */
	काष्ठा list_head	cached_itd_list;
	काष्ठा fotg210_itd	*last_itd_to_मुक्त;

	/* per root hub port */
	अचिन्हित दीर्घ		reset_करोne[FOTG210_MAX_ROOT_PORTS];

	/* bit vectors (one bit per port)
	 * which ports were alपढ़ोy suspended at the start of a bus suspend
	 */
	अचिन्हित दीर्घ		bus_suspended;

	/* which ports are edicated to the companion controller */
	अचिन्हित दीर्घ		companion_ports;

	/* which ports are owned by the companion during a bus suspend */
	अचिन्हित दीर्घ		owned_ports;

	/* which ports have the change-suspend feature turned on */
	अचिन्हित दीर्घ		port_c_suspend;

	/* which ports are suspended */
	अचिन्हित दीर्घ		suspended_ports;

	/* which ports have started to resume */
	अचिन्हित दीर्घ		resuming_ports;

	/* per-HC memory pools (could be per-bus, but ...) */
	काष्ठा dma_pool		*qh_pool;	/* qh per active urb */
	काष्ठा dma_pool		*qtd_pool;	/* one or more per qh */
	काष्ठा dma_pool		*itd_pool;	/* itd per iso urb */

	अचिन्हित		अक्रमom_frame;
	अचिन्हित दीर्घ		next_statechange;
	kसमय_प्रकार			last_periodic_enable;
	u32			command;

	/* SILICON QUIRKS */
	अचिन्हित		need_io_watchकरोg:1;
	अचिन्हित		fs_i_thresh:1;	/* Intel iso scheduling */

	u8			sbrn;		/* packed release number */

	/* irq statistics */
#अगर_घोषित FOTG210_STATS
	काष्ठा fotg210_stats	stats;
#	define INCR(x) ((x)++)
#अन्यथा
#	define INCR(x) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

	/* silicon घड़ी */
	काष्ठा clk		*pclk;

	/* debug files */
	काष्ठा dentry		*debug_dir;
पूर्ण;

/* convert between an HCD poपूर्णांकer and the corresponding FOTG210_HCD */
अटल अंतरभूत काष्ठा fotg210_hcd *hcd_to_fotg210(काष्ठा usb_hcd *hcd)
अणु
	वापस (काष्ठा fotg210_hcd *)(hcd->hcd_priv);
पूर्ण
अटल अंतरभूत काष्ठा usb_hcd *fotg210_to_hcd(काष्ठा fotg210_hcd *fotg210)
अणु
	वापस container_of((व्योम *) fotg210, काष्ठा usb_hcd, hcd_priv);
पूर्ण

/*-------------------------------------------------------------------------*/

/* EHCI रेजिस्टर पूर्णांकerface, corresponds to EHCI Revision 0.95 specअगरication */

/* Section 2.2 Host Controller Capability Registers */
काष्ठा fotg210_caps अणु
	/* these fields are specअगरied as 8 and 16 bit रेजिस्टरs,
	 * but some hosts can't perक्रमm 8 or 16 bit PCI accesses.
	 * some hosts treat caplength and hciversion as parts of a 32-bit
	 * रेजिस्टर, others treat them as two separate रेजिस्टरs, this
	 * affects the memory map क्रम big endian controllers.
	 */
	u32		hc_capbase;
#घोषणा HC_LENGTH(fotg210, p)	(0x00ff&((p) >> /* bits 7:0 / offset 00h */ \
				(fotg210_big_endian_capbase(fotg210) ? 24 : 0)))
#घोषणा HC_VERSION(fotg210, p)	(0xffff&((p) >> /* bits 31:16 / offset 02h */ \
				(fotg210_big_endian_capbase(fotg210) ? 0 : 16)))
	u32		hcs_params;     /* HCSPARAMS - offset 0x4 */
#घोषणा HCS_N_PORTS(p)		(((p)>>0)&0xf)	/* bits 3:0, ports on HC */

	u32		hcc_params;	/* HCCPARAMS - offset 0x8 */
#घोषणा HCC_CANPARK(p)		((p)&(1 << 2))  /* true: can park on async qh */
#घोषणा HCC_PGM_FRAMELISTLEN(p) ((p)&(1 << 1))  /* true: periodic_size changes*/
	u8		portroute[8];	 /* nibbles क्रम routing - offset 0xC */
पूर्ण;


/* Section 2.3 Host Controller Operational Registers */
काष्ठा fotg210_regs अणु

	/* USBCMD: offset 0x00 */
	u32		command;

/* EHCI 1.1 addendum */
/* 23:16 is r/w पूर्णांकr rate, in microframes; शेष "8" == 1/msec */
#घोषणा CMD_PARK	(1<<11)		/* enable "park" on async qh */
#घोषणा CMD_PARK_CNT(c)	(((c)>>8)&3)	/* how many transfers to park क्रम */
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

	u32	reserved1;
	/* PORTSC: offset 0x20 */
	u32	port_status;
/* 31:23 reserved */
#घोषणा PORT_USB11(x) (((x)&(3<<10)) == (1<<10))	/* USB 1.1 device */
#घोषणा PORT_RESET	(1<<8)		/* reset port */
#घोषणा PORT_SUSPEND	(1<<7)		/* suspend port */
#घोषणा PORT_RESUME	(1<<6)		/* resume it */
#घोषणा PORT_PEC	(1<<3)		/* port enable change */
#घोषणा PORT_PE		(1<<2)		/* port enable */
#घोषणा PORT_CSC	(1<<1)		/* connect status change */
#घोषणा PORT_CONNECT	(1<<0)		/* device connected */
#घोषणा PORT_RWC_BITS   (PORT_CSC | PORT_PEC)
	u32     reserved2[19];

	/* OTGCSR: offet 0x70 */
	u32     otgcsr;
#घोषणा OTGCSR_HOST_SPD_TYP     (3 << 22)
#घोषणा OTGCSR_A_BUS_DROP	(1 << 5)
#घोषणा OTGCSR_A_BUS_REQ	(1 << 4)

	/* OTGISR: offset 0x74 */
	u32     otgisr;
#घोषणा OTGISR_OVC	(1 << 10)

	u32     reserved3[15];

	/* GMIR: offset 0xB4 */
	u32     gmir;
#घोषणा GMIR_INT_POLARITY	(1 << 3) /*Active High*/
#घोषणा GMIR_MHC_INT		(1 << 2)
#घोषणा GMIR_MOTG_INT		(1 << 1)
#घोषणा GMIR_MDEV_INT	(1 << 0)
पूर्ण;

/*-------------------------------------------------------------------------*/

#घोषणा	QTD_NEXT(fotg210, dma)	cpu_to_hc32(fotg210, (u32)dma)

/*
 * EHCI Specअगरication 0.95 Section 3.5
 * QTD: describe data transfer components (buffer, direction, ...)
 * See Fig 3-6 "Queue Element Transfer Descriptor Block Diagram".
 *
 * These are associated only with "QH" (Queue Head) काष्ठाures,
 * used with control, bulk, and पूर्णांकerrupt transfers.
 */
काष्ठा fotg210_qtd अणु
	/* first part defined by EHCI spec */
	__hc32			hw_next;	/* see EHCI 3.5.1 */
	__hc32			hw_alt_next;    /* see EHCI 3.5.2 */
	__hc32			hw_token;	/* see EHCI 3.5.3 */
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

#घोषणा ACTIVE_BIT(fotg210)	cpu_to_hc32(fotg210, QTD_STS_ACTIVE)
#घोषणा HALT_BIT(fotg210)		cpu_to_hc32(fotg210, QTD_STS_HALT)
#घोषणा STATUS_BIT(fotg210)	cpu_to_hc32(fotg210, QTD_STS_STS)

	__hc32			hw_buf[5];	/* see EHCI 3.5.4 */
	__hc32			hw_buf_hi[5];	/* Appendix B */

	/* the rest is HCD-निजी */
	dma_addr_t		qtd_dma;		/* qtd address */
	काष्ठा list_head	qtd_list;		/* sw qtd list */
	काष्ठा urb		*urb;			/* qtd's urb */
	माप_प्रकार			length;			/* length of buffer */
पूर्ण __aligned(32);

/* mask NakCnt+T in qh->hw_alt_next */
#घोषणा QTD_MASK(fotg210)	cpu_to_hc32(fotg210, ~0x1f)

#घोषणा IS_SHORT_READ(token) (QTD_LENGTH(token) != 0 && QTD_PID(token) == 1)

/*-------------------------------------------------------------------------*/

/* type tag from अणुqh,itd,fstnपूर्ण->hw_next */
#घोषणा Q_NEXT_TYPE(fotg210, dma)	((dma) & cpu_to_hc32(fotg210, 3 << 1))

/*
 * Now the following defines are not converted using the
 * cpu_to_le32() macro anymore, since we have to support
 * "dynamic" चयनing between be and le support, so that the driver
 * can be used on one प्रणाली with SoC EHCI controller using big-endian
 * descriptors as well as a normal little-endian PCI EHCI controller.
 */
/* values क्रम that type tag */
#घोषणा Q_TYPE_ITD	(0 << 1)
#घोषणा Q_TYPE_QH	(1 << 1)
#घोषणा Q_TYPE_SITD	(2 << 1)
#घोषणा Q_TYPE_FSTN	(3 << 1)

/* next async queue entry, or poपूर्णांकer to पूर्णांकerrupt/periodic QH */
#घोषणा QH_NEXT(fotg210, dma) \
	(cpu_to_hc32(fotg210, (((u32)dma)&~0x01f)|Q_TYPE_QH))

/* क्रम periodic/async schedules and qtd lists, mark end of list */
#घोषणा FOTG210_LIST_END(fotg210) \
	cpu_to_hc32(fotg210, 1) /* "null pointer" to hw */

/*
 * Entries in periodic shaकरोw table are poपूर्णांकers to one of four kinds
 * of data काष्ठाure.  That's dictated by the hardware; a type tag is
 * encoded in the low bits of the hardware's periodic schedule.  Use
 * Q_NEXT_TYPE to get the tag.
 *
 * For entries in the async schedule, the type tag always says "qh".
 */
जोड़ fotg210_shaकरोw अणु
	काष्ठा fotg210_qh	*qh;		/* Q_TYPE_QH */
	काष्ठा fotg210_itd	*itd;		/* Q_TYPE_ITD */
	काष्ठा fotg210_fstn	*fstn;		/* Q_TYPE_FSTN */
	__hc32			*hw_next;	/* (all types) */
	व्योम			*ptr;
पूर्ण;

/*-------------------------------------------------------------------------*/

/*
 * EHCI Specअगरication 0.95 Section 3.6
 * QH: describes control/bulk/पूर्णांकerrupt endpoपूर्णांकs
 * See Fig 3-7 "Queue Head Structure Layout".
 *
 * These appear in both the async and (क्रम पूर्णांकerrupt) periodic schedules.
 */

/* first part defined by EHCI spec */
काष्ठा fotg210_qh_hw अणु
	__hc32			hw_next;	/* see EHCI 3.6.1 */
	__hc32			hw_info1;	/* see EHCI 3.6.2 */
#घोषणा	QH_CONTROL_EP	(1 << 27)	/* FS/LS control endpoपूर्णांक */
#घोषणा	QH_HEAD		(1 << 15)	/* Head of async reclamation list */
#घोषणा	QH_TOGGLE_CTL	(1 << 14)	/* Data toggle control */
#घोषणा	QH_HIGH_SPEED	(2 << 12)	/* Endpoपूर्णांक speed */
#घोषणा	QH_LOW_SPEED	(1 << 12)
#घोषणा	QH_FULL_SPEED	(0 << 12)
#घोषणा	QH_INACTIVATE	(1 << 7)	/* Inactivate on next transaction */
	__hc32			hw_info2;	/* see EHCI 3.6.2 */
#घोषणा	QH_SMASK	0x000000ff
#घोषणा	QH_CMASK	0x0000ff00
#घोषणा	QH_HUBADDR	0x007f0000
#घोषणा	QH_HUBPORT	0x3f800000
#घोषणा	QH_MULT		0xc0000000
	__hc32			hw_current;	/* qtd list - see EHCI 3.6.4 */

	/* qtd overlay (hardware parts of a काष्ठा fotg210_qtd) */
	__hc32			hw_qtd_next;
	__hc32			hw_alt_next;
	__hc32			hw_token;
	__hc32			hw_buf[5];
	__hc32			hw_buf_hi[5];
पूर्ण __aligned(32);

काष्ठा fotg210_qh अणु
	काष्ठा fotg210_qh_hw	*hw;		/* Must come first */
	/* the rest is HCD-निजी */
	dma_addr_t		qh_dma;		/* address of qh */
	जोड़ fotg210_shaकरोw	qh_next;	/* ptr to qh; or periodic */
	काष्ठा list_head	qtd_list;	/* sw qtd list */
	काष्ठा list_head	पूर्णांकr_node;	/* list of पूर्णांकr QHs */
	काष्ठा fotg210_qtd	*dummy;
	काष्ठा fotg210_qh	*unlink_next;	/* next on unlink list */

	अचिन्हित		unlink_cycle;

	u8			needs_rescan;	/* Dequeue during giveback */
	u8			qh_state;
#घोषणा	QH_STATE_LINKED		1		/* HC sees this */
#घोषणा	QH_STATE_UNLINK		2		/* HC may still see this */
#घोषणा	QH_STATE_IDLE		3		/* HC करोesn't see this */
#घोषणा	QH_STATE_UNLINK_WAIT	4		/* LINKED and on unlink q */
#घोषणा	QH_STATE_COMPLETING	5		/* करोn't touch token.HALT */

	u8			xacterrs;	/* XactErr retry counter */
#घोषणा	QH_XACTERR_MAX		32		/* XactErr retry limit */

	/* periodic schedule info */
	u8			usecs;		/* पूर्णांकr bandwidth */
	u8			gap_uf;		/* uframes split/csplit gap */
	u8			c_usecs;	/* ... split completion bw */
	u16			tt_usecs;	/* tt करोwnstream bandwidth */
	अचिन्हित लघु		period;		/* polling पूर्णांकerval */
	अचिन्हित लघु		start;		/* where polling starts */
#घोषणा NO_FRAME ((अचिन्हित लघु)~0)			/* pick new start */

	काष्ठा usb_device	*dev;		/* access to TT */
	अचिन्हित		is_out:1;	/* bulk or पूर्णांकr OUT */
	अचिन्हित		clearing_tt:1;	/* Clear-TT-Buf in progress */
पूर्ण;

/*-------------------------------------------------------------------------*/

/* description of one iso transaction (up to 3 KB data अगर highspeed) */
काष्ठा fotg210_iso_packet अणु
	/* These will be copied to iTD when scheduling */
	u64			bufp;		/* itd->hw_bufpअणु,_hiपूर्ण[pg] |= */
	__hc32			transaction;	/* itd->hw_transaction[i] |= */
	u8			cross;		/* buf crosses pages */
	/* क्रम full speed OUT splits */
	u32			buf1;
पूर्ण;

/* temporary schedule data क्रम packets from iso urbs (both speeds)
 * each packet is one logical usb transaction to the device (not TT),
 * beginning at stream->next_uframe
 */
काष्ठा fotg210_iso_sched अणु
	काष्ठा list_head	td_list;
	अचिन्हित		span;
	काष्ठा fotg210_iso_packet	packet[];
पूर्ण;

/*
 * fotg210_iso_stream - groups all (s)itds क्रम this endpoपूर्णांक.
 * acts like a qh would, अगर EHCI had them क्रम ISO.
 */
काष्ठा fotg210_iso_stream अणु
	/* first field matches fotg210_hq, but is शून्य */
	काष्ठा fotg210_qh_hw	*hw;

	u8			bEndpoपूर्णांकAddress;
	u8			highspeed;
	काष्ठा list_head	td_list;	/* queued itds */
	काष्ठा list_head	मुक्त_list;	/* list of unused itds */
	काष्ठा usb_device	*udev;
	काष्ठा usb_host_endpoपूर्णांक *ep;

	/* output of (re)scheduling */
	पूर्णांक			next_uframe;
	__hc32			splits;

	/* the rest is derived from the endpoपूर्णांक descriptor,
	 * trusting urb->पूर्णांकerval == f(epdesc->bInterval) and
	 * including the extra info क्रम hw_bufp[0..2]
	 */
	u8			usecs, c_usecs;
	u16			पूर्णांकerval;
	u16			tt_usecs;
	u16			maxp;
	u16			raw_mask;
	अचिन्हित		bandwidth;

	/* This is used to initialize iTD's hw_bufp fields */
	__hc32			buf0;
	__hc32			buf1;
	__hc32			buf2;

	/* this is used to initialize sITD's tt info */
	__hc32			address;
पूर्ण;

/*-------------------------------------------------------------------------*/

/*
 * EHCI Specअगरication 0.95 Section 3.3
 * Fig 3-4 "Isochronous Transaction Descriptor (iTD)"
 *
 * Schedule records क्रम high speed iso xfers
 */
काष्ठा fotg210_itd अणु
	/* first part defined by EHCI spec */
	__hc32			hw_next;	/* see EHCI 3.3.1 */
	__hc32			hw_transaction[8]; /* see EHCI 3.3.2 */
#घोषणा FOTG210_ISOC_ACTIVE	(1<<31)	/* activate transfer this slot */
#घोषणा FOTG210_ISOC_BUF_ERR	(1<<30)	/* Data buffer error */
#घोषणा FOTG210_ISOC_BABBLE	(1<<29)	/* babble detected */
#घोषणा FOTG210_ISOC_XACTERR	(1<<28)	/* XactErr - transaction error */
#घोषणा	FOTG210_ITD_LENGTH(tok)	(((tok)>>16) & 0x0fff)
#घोषणा	FOTG210_ITD_IOC		(1 << 15)	/* पूर्णांकerrupt on complete */

#घोषणा ITD_ACTIVE(fotg210)	cpu_to_hc32(fotg210, FOTG210_ISOC_ACTIVE)

	__hc32			hw_bufp[7];	/* see EHCI 3.3.3 */
	__hc32			hw_bufp_hi[7];	/* Appendix B */

	/* the rest is HCD-निजी */
	dma_addr_t		itd_dma;	/* क्रम this itd */
	जोड़ fotg210_shaकरोw	itd_next;	/* ptr to periodic q entry */

	काष्ठा urb		*urb;
	काष्ठा fotg210_iso_stream	*stream;	/* endpoपूर्णांक's queue */
	काष्ठा list_head	itd_list;	/* list of stream's itds */

	/* any/all hw_transactions here may be used by that urb */
	अचिन्हित		frame;		/* where scheduled */
	अचिन्हित		pg;
	अचिन्हित		index[8];	/* in urb->iso_frame_desc */
पूर्ण __aligned(32);

/*-------------------------------------------------------------------------*/

/*
 * EHCI Specअगरication 0.96 Section 3.7
 * Periodic Frame Span Traversal Node (FSTN)
 *
 * Manages split पूर्णांकerrupt transactions (using TT) that span frame boundaries
 * पूर्णांकo uframes 0/1; see 4.12.2.2.  In those uframes, a "save place" FSTN
 * makes the HC jump (back) to a QH to scan क्रम fs/ls QH completions until
 * it hits a "restore" FSTN; then it वापसs to finish other uframe 0/1 work.
 */
काष्ठा fotg210_fstn अणु
	__hc32			hw_next;	/* any periodic q entry */
	__hc32			hw_prev;	/* qh or FOTG210_LIST_END */

	/* the rest is HCD-निजी */
	dma_addr_t		fstn_dma;
	जोड़ fotg210_shaकरोw	fstn_next;	/* ptr to periodic q entry */
पूर्ण __aligned(32);

/*-------------------------------------------------------------------------*/

/* Prepare the PORTSC wakeup flags during controller suspend/resume */

#घोषणा fotg210_prepare_ports_क्रम_controller_suspend(fotg210, करो_wakeup) \
		fotg210_adjust_port_wakeup_flags(fotg210, true, करो_wakeup)

#घोषणा fotg210_prepare_ports_क्रम_controller_resume(fotg210)		\
		fotg210_adjust_port_wakeup_flags(fotg210, false, false)

/*-------------------------------------------------------------------------*/

/*
 * Some EHCI controllers have a Transaction Translator built पूर्णांकo the
 * root hub. This is a non-standard feature.  Each controller will need
 * to add code to the following अंतरभूत functions, and call them as
 * needed (mostly in root hub code).
 */

अटल अंतरभूत अचिन्हित पूर्णांक
fotg210_get_speed(काष्ठा fotg210_hcd *fotg210, अचिन्हित पूर्णांक portsc)
अणु
	वापस (पढ़ोl(&fotg210->regs->otgcsr)
		& OTGCSR_HOST_SPD_TYP) >> 22;
पूर्ण

/* Returns the speed of a device attached to a port on the root hub. */
अटल अंतरभूत अचिन्हित पूर्णांक
fotg210_port_speed(काष्ठा fotg210_hcd *fotg210, अचिन्हित पूर्णांक portsc)
अणु
	चयन (fotg210_get_speed(fotg210, portsc)) अणु
	हाल 0:
		वापस 0;
	हाल 1:
		वापस USB_PORT_STAT_LOW_SPEED;
	हाल 2:
	शेष:
		वापस USB_PORT_STAT_HIGH_SPEED;
	पूर्ण
पूर्ण

/*-------------------------------------------------------------------------*/

#घोषणा	fotg210_has_fsl_portno_bug(e)		(0)

/*
 * While most USB host controllers implement their रेजिस्टरs in
 * little-endian क्रमmat, a minority (celleb companion chip) implement
 * them in big endian क्रमmat.
 *
 * This attempts to support either क्रमmat at compile समय without a
 * runसमय penalty, or both क्रमmats with the additional overhead
 * of checking a flag bit.
 *
 */

#घोषणा fotg210_big_endian_mmio(e)	0
#घोषणा fotg210_big_endian_capbase(e)	0

अटल अंतरभूत अचिन्हित पूर्णांक fotg210_पढ़ोl(स्थिर काष्ठा fotg210_hcd *fotg210,
		__u32 __iomem *regs)
अणु
	वापस पढ़ोl(regs);
पूर्ण

अटल अंतरभूत व्योम fotg210_ग_लिखोl(स्थिर काष्ठा fotg210_hcd *fotg210,
		स्थिर अचिन्हित पूर्णांक val, __u32 __iomem *regs)
अणु
	ग_लिखोl(val, regs);
पूर्ण

/* cpu to fotg210 */
अटल अंतरभूत __hc32 cpu_to_hc32(स्थिर काष्ठा fotg210_hcd *fotg210, स्थिर u32 x)
अणु
	वापस cpu_to_le32(x);
पूर्ण

/* fotg210 to cpu */
अटल अंतरभूत u32 hc32_to_cpu(स्थिर काष्ठा fotg210_hcd *fotg210, स्थिर __hc32 x)
अणु
	वापस le32_to_cpu(x);
पूर्ण

अटल अंतरभूत u32 hc32_to_cpup(स्थिर काष्ठा fotg210_hcd *fotg210,
			       स्थिर __hc32 *x)
अणु
	वापस le32_to_cpup(x);
पूर्ण

/*-------------------------------------------------------------------------*/

अटल अंतरभूत अचिन्हित fotg210_पढ़ो_frame_index(काष्ठा fotg210_hcd *fotg210)
अणु
	वापस fotg210_पढ़ोl(fotg210, &fotg210->regs->frame_index);
पूर्ण

#घोषणा fotg210_itdlen(urb, desc, t) (अणु			\
	usb_pipein((urb)->pipe) ?				\
	(desc)->length - FOTG210_ITD_LENGTH(t) :			\
	FOTG210_ITD_LENGTH(t);					\
पूर्ण)
/*-------------------------------------------------------------------------*/

#पूर्ण_अगर /* __LINUX_FOTG210_H */
