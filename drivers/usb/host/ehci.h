<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (c) 2001-2002 by David Brownell
 */

#अगर_अघोषित __LINUX_EHCI_HCD_H
#घोषणा __LINUX_EHCI_HCD_H

/* definitions used क्रम the EHCI driver */

/*
 * __hc32 and __hc16 are "Host Controller" types, they may be equivalent to
 * __leXX (normally) or __beXX (given EHCI_BIG_ENDIAN_DESC), depending on
 * the host controller implementation.
 *
 * To facilitate the strongest possible byte-order checking from "sparse"
 * and so on, we use __leXX unless that's not practical.
 */
#अगर_घोषित CONFIG_USB_EHCI_BIG_ENDIAN_DESC
प्रकार __u32 __bitwise __hc32;
प्रकार __u16 __bitwise __hc16;
#अन्यथा
#घोषणा __hc32	__le32
#घोषणा __hc16	__le16
#पूर्ण_अगर

/* statistics can be kept क्रम tuning/monitoring */
#अगर_घोषित CONFIG_DYNAMIC_DEBUG
#घोषणा EHCI_STATS
#पूर्ण_अगर

काष्ठा ehci_stats अणु
	/* irq usage */
	अचिन्हित दीर्घ		normal;
	अचिन्हित दीर्घ		error;
	अचिन्हित दीर्घ		iaa;
	अचिन्हित दीर्घ		lost_iaa;

	/* termination of urbs from core */
	अचिन्हित दीर्घ		complete;
	अचिन्हित दीर्घ		unlink;
पूर्ण;

/*
 * Scheduling and budgeting inक्रमmation क्रम periodic transfers, क्रम both
 * high-speed devices and full/low-speed devices lying behind a TT.
 */
काष्ठा ehci_per_sched अणु
	काष्ठा usb_device	*udev;		/* access to the TT */
	काष्ठा usb_host_endpoपूर्णांक *ep;
	काष्ठा list_head	ps_list;	/* node on ehci_tt's ps_list */
	u16			tt_usecs;	/* समय on the FS/LS bus */
	u16			cs_mask;	/* C-mask and S-mask bytes */
	u16			period;		/* actual period in frames */
	u16			phase;		/* actual phase, frame part */
	u8			bw_phase;	/* same, क्रम bandwidth
						   reservation */
	u8			phase_uf;	/* uframe part of the phase */
	u8			usecs, c_usecs;	/* बार on the HS bus */
	u8			bw_uperiod;	/* period in microframes, क्रम
						   bandwidth reservation */
	u8			bw_period;	/* same, in frames */
पूर्ण;
#घोषणा NO_FRAME	29999			/* frame not asचिन्हित yet */

/* ehci_hcd->lock guards shared data against other CPUs:
 *   ehci_hcd:	async, unlink, periodic (and shaकरोw), ...
 *   usb_host_endpoपूर्णांक: hcpriv
 *   ehci_qh:	qh_next, qtd_list
 *   ehci_qtd:	qtd_list
 *
 * Also, hold this lock when talking to HC रेजिस्टरs or
 * when updating hw_* fields in shared qh/qtd/... काष्ठाures.
 */

#घोषणा	EHCI_MAX_ROOT_PORTS	15		/* see HCS_N_PORTS */

/*
 * ehci_rh_state values of EHCI_RH_RUNNING or above mean that the
 * controller may be करोing DMA.  Lower values mean there's no DMA.
 */
क्रमागत ehci_rh_state अणु
	EHCI_RH_HALTED,
	EHCI_RH_SUSPENDED,
	EHCI_RH_RUNNING,
	EHCI_RH_STOPPING
पूर्ण;

/*
 * Timer events, ordered by increasing delay length.
 * Always update event_delays_ns[] and event_handlers[] (defined in
 * ehci-समयr.c) in parallel with this list.
 */
क्रमागत ehci_hrसमयr_event अणु
	EHCI_HRTIMER_POLL_ASS,		/* Poll क्रम async schedule off */
	EHCI_HRTIMER_POLL_PSS,		/* Poll क्रम periodic schedule off */
	EHCI_HRTIMER_POLL_DEAD,		/* Wait क्रम dead controller to stop */
	EHCI_HRTIMER_UNLINK_INTR,	/* Wait क्रम पूर्णांकerrupt QH unlink */
	EHCI_HRTIMER_FREE_ITDS,		/* Wait क्रम unused iTDs and siTDs */
	EHCI_HRTIMER_ACTIVE_UNLINK,	/* Wait जबतक unlinking an active QH */
	EHCI_HRTIMER_START_UNLINK_INTR, /* Unlink empty पूर्णांकerrupt QHs */
	EHCI_HRTIMER_ASYNC_UNLINKS,	/* Unlink empty async QHs */
	EHCI_HRTIMER_IAA_WATCHDOG,	/* Handle lost IAA पूर्णांकerrupts */
	EHCI_HRTIMER_DISABLE_PERIODIC,	/* Wait to disable periodic sched */
	EHCI_HRTIMER_DISABLE_ASYNC,	/* Wait to disable async sched */
	EHCI_HRTIMER_IO_WATCHDOG,	/* Check क्रम missing IRQs */
	EHCI_HRTIMER_NUM_EVENTS		/* Must come last */
पूर्ण;
#घोषणा EHCI_HRTIMER_NO_EVENT	99

काष्ठा ehci_hcd अणु			/* one per controller */
	/* timing support */
	क्रमागत ehci_hrसमयr_event	next_hrसमयr_event;
	अचिन्हित		enabled_hrसमयr_events;
	kसमय_प्रकार			hr_समयouts[EHCI_HRTIMER_NUM_EVENTS];
	काष्ठा hrसमयr		hrसमयr;

	पूर्णांक			PSS_poll_count;
	पूर्णांक			ASS_poll_count;
	पूर्णांक			died_poll_count;

	/* glue to PCI and HCD framework */
	काष्ठा ehci_caps __iomem *caps;
	काष्ठा ehci_regs __iomem *regs;
	काष्ठा ehci_dbg_port __iomem *debug;

	__u32			hcs_params;	/* cached रेजिस्टर copy */
	spinlock_t		lock;
	क्रमागत ehci_rh_state	rh_state;

	/* general schedule support */
	bool			scanning:1;
	bool			need_rescan:1;
	bool			पूर्णांकr_unlinking:1;
	bool			iaa_in_progress:1;
	bool			async_unlinking:1;
	bool			shutकरोwn:1;
	काष्ठा ehci_qh		*qh_scan_next;

	/* async schedule support */
	काष्ठा ehci_qh		*async;
	काष्ठा ehci_qh		*dummy;		/* For AMD quirk use */
	काष्ठा list_head	async_unlink;
	काष्ठा list_head	async_idle;
	अचिन्हित		async_unlink_cycle;
	अचिन्हित		async_count;	/* async activity count */
	__hc32			old_current;	/* Test क्रम QH becoming */
	__hc32			old_token;	/*  inactive during unlink */

	/* periodic schedule support */
#घोषणा	DEFAULT_I_TDPS		1024		/* some HCs can करो less */
	अचिन्हित		periodic_size;
	__hc32			*periodic;	/* hw periodic table */
	dma_addr_t		periodic_dma;
	काष्ठा list_head	पूर्णांकr_qh_list;
	अचिन्हित		i_thresh;	/* uframes HC might cache */

	जोड़ ehci_shaकरोw	*pshaकरोw;	/* mirror hw periodic table */
	काष्ठा list_head	पूर्णांकr_unlink_रुको;
	काष्ठा list_head	पूर्णांकr_unlink;
	अचिन्हित		पूर्णांकr_unlink_रुको_cycle;
	अचिन्हित		पूर्णांकr_unlink_cycle;
	अचिन्हित		now_frame;	/* frame from HC hardware */
	अचिन्हित		last_iso_frame;	/* last frame scanned क्रम iso */
	अचिन्हित		पूर्णांकr_count;	/* पूर्णांकr activity count */
	अचिन्हित		isoc_count;	/* isoc activity count */
	अचिन्हित		periodic_count;	/* periodic activity count */
	अचिन्हित		uframe_periodic_max; /* max periodic समय per uframe */


	/* list of itds & sitds completed जबतक now_frame was still active */
	काष्ठा list_head	cached_itd_list;
	काष्ठा ehci_itd		*last_itd_to_मुक्त;
	काष्ठा list_head	cached_sitd_list;
	काष्ठा ehci_sitd	*last_sitd_to_मुक्त;

	/* per root hub port */
	अचिन्हित दीर्घ		reset_करोne[EHCI_MAX_ROOT_PORTS];

	/* bit vectors (one bit per port) */
	अचिन्हित दीर्घ		bus_suspended;		/* which ports were
			alपढ़ोy suspended at the start of a bus suspend */
	अचिन्हित दीर्घ		companion_ports;	/* which ports are
			dedicated to the companion controller */
	अचिन्हित दीर्घ		owned_ports;		/* which ports are
			owned by the companion during a bus suspend */
	अचिन्हित दीर्घ		port_c_suspend;		/* which ports have
			the change-suspend feature turned on */
	अचिन्हित दीर्घ		suspended_ports;	/* which ports are
			suspended */
	अचिन्हित दीर्घ		resuming_ports;		/* which ports have
			started to resume */

	/* per-HC memory pools (could be per-bus, but ...) */
	काष्ठा dma_pool		*qh_pool;	/* qh per active urb */
	काष्ठा dma_pool		*qtd_pool;	/* one or more per qh */
	काष्ठा dma_pool		*itd_pool;	/* itd per iso urb */
	काष्ठा dma_pool		*sitd_pool;	/* sitd per split iso urb */

	अचिन्हित		अक्रमom_frame;
	अचिन्हित दीर्घ		next_statechange;
	kसमय_प्रकार			last_periodic_enable;
	u32			command;

	/* SILICON QUIRKS */
	अचिन्हित		no_selective_suspend:1;
	अचिन्हित		has_fsl_port_bug:1; /* FreeScale */
	अचिन्हित		has_fsl_hs_errata:1;	/* Freescale HS quirk */
	अचिन्हित		has_fsl_susp_errata:1;	/* NXP SUSP quirk */
	अचिन्हित		big_endian_mmio:1;
	अचिन्हित		big_endian_desc:1;
	अचिन्हित		big_endian_capbase:1;
	अचिन्हित		has_amcc_usb23:1;
	अचिन्हित		need_io_watchकरोg:1;
	अचिन्हित		amd_pll_fix:1;
	अचिन्हित		use_dummy_qh:1;	/* AMD Frame List table quirk*/
	अचिन्हित		has_synopsys_hc_bug:1; /* Synopsys HC */
	अचिन्हित		frame_index_bug:1; /* MosChip (AKA NetMos) */
	अचिन्हित		need_oc_pp_cycle:1; /* MPC834X port घातer */
	अचिन्हित		imx28_ग_लिखो_fix:1; /* For Freescale i.MX28 */
	अचिन्हित		spurious_oc:1;

	/* required क्रम usb32 quirk */
	#घोषणा OHCI_CTRL_HCFS          (3 << 6)
	#घोषणा OHCI_USB_OPER           (2 << 6)
	#घोषणा OHCI_USB_SUSPEND        (3 << 6)

	#घोषणा OHCI_HCCTRL_OFFSET      0x4
	#घोषणा OHCI_HCCTRL_LEN         0x4
	__hc32			*ohci_hcctrl_reg;
	अचिन्हित		has_hostpc:1;
	अचिन्हित		has_tdi_phy_lpm:1;
	अचिन्हित		has_ppcd:1; /* support per-port change bits */
	u8			sbrn;		/* packed release number */

	/* irq statistics */
#अगर_घोषित EHCI_STATS
	काष्ठा ehci_stats	stats;
#	define INCR(x) ((x)++)
#अन्यथा
#	define INCR(x) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

	/* debug files */
#अगर_घोषित CONFIG_DYNAMIC_DEBUG
	काष्ठा dentry		*debug_dir;
#पूर्ण_अगर

	/* bandwidth usage */
#घोषणा EHCI_BANDWIDTH_SIZE	64
#घोषणा EHCI_BANDWIDTH_FRAMES	(EHCI_BANDWIDTH_SIZE >> 3)
	u8			bandwidth[EHCI_BANDWIDTH_SIZE];
						/* us allocated per uframe */
	u8			tt_budget[EHCI_BANDWIDTH_SIZE];
						/* us budgeted per uframe */
	काष्ठा list_head	tt_list;

	/* platक्रमm-specअगरic data -- must come last */
	अचिन्हित दीर्घ		priv[] __aligned(माप(s64));
पूर्ण;

/* convert between an HCD poपूर्णांकer and the corresponding EHCI_HCD */
अटल अंतरभूत काष्ठा ehci_hcd *hcd_to_ehci(काष्ठा usb_hcd *hcd)
अणु
	वापस (काष्ठा ehci_hcd *) (hcd->hcd_priv);
पूर्ण
अटल अंतरभूत काष्ठा usb_hcd *ehci_to_hcd(काष्ठा ehci_hcd *ehci)
अणु
	वापस container_of((व्योम *) ehci, काष्ठा usb_hcd, hcd_priv);
पूर्ण

/*-------------------------------------------------------------------------*/

#समावेश <linux/usb/ehci_def.h>

/*-------------------------------------------------------------------------*/

#घोषणा	QTD_NEXT(ehci, dma)	cpu_to_hc32(ehci, (u32)dma)

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
	__hc32			hw_next;	/* see EHCI 3.5.1 */
	__hc32			hw_alt_next;    /* see EHCI 3.5.2 */
	__hc32			hw_token;       /* see EHCI 3.5.3 */
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

#घोषणा ACTIVE_BIT(ehci)	cpu_to_hc32(ehci, QTD_STS_ACTIVE)
#घोषणा HALT_BIT(ehci)		cpu_to_hc32(ehci, QTD_STS_HALT)
#घोषणा STATUS_BIT(ehci)	cpu_to_hc32(ehci, QTD_STS_STS)

	__hc32			hw_buf[5];        /* see EHCI 3.5.4 */
	__hc32			hw_buf_hi[5];        /* Appendix B */

	/* the rest is HCD-निजी */
	dma_addr_t		qtd_dma;		/* qtd address */
	काष्ठा list_head	qtd_list;		/* sw qtd list */
	काष्ठा urb		*urb;			/* qtd's urb */
	माप_प्रकार			length;			/* length of buffer */
पूर्ण __aligned(32);

/* mask NakCnt+T in qh->hw_alt_next */
#घोषणा QTD_MASK(ehci)	cpu_to_hc32(ehci, ~0x1f)

#घोषणा IS_SHORT_READ(token) (QTD_LENGTH(token) != 0 && QTD_PID(token) == 1)

/*-------------------------------------------------------------------------*/

/* type tag from अणुqh,itd,sitd,fstnपूर्ण->hw_next */
#घोषणा Q_NEXT_TYPE(ehci, dma)	((dma) & cpu_to_hc32(ehci, 3 << 1))

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
#घोषणा QH_NEXT(ehci, dma) \
		(cpu_to_hc32(ehci, (((u32) dma) & ~0x01f) | Q_TYPE_QH))

/* क्रम periodic/async schedules and qtd lists, mark end of list */
#घोषणा EHCI_LIST_END(ehci)	cpu_to_hc32(ehci, 1) /* "null pointer" to hw */

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
	काष्ठा ehci_itd		*itd;		/* Q_TYPE_ITD */
	काष्ठा ehci_sitd	*sitd;		/* Q_TYPE_SITD */
	काष्ठा ehci_fstn	*fstn;		/* Q_TYPE_FSTN */
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
काष्ठा ehci_qh_hw अणु
	__hc32			hw_next;	/* see EHCI 3.6.1 */
	__hc32			hw_info1;       /* see EHCI 3.6.2 */
#घोषणा	QH_CONTROL_EP	(1 << 27)	/* FS/LS control endpoपूर्णांक */
#घोषणा	QH_HEAD		(1 << 15)	/* Head of async reclamation list */
#घोषणा	QH_TOGGLE_CTL	(1 << 14)	/* Data toggle control */
#घोषणा	QH_HIGH_SPEED	(2 << 12)	/* Endpoपूर्णांक speed */
#घोषणा	QH_LOW_SPEED	(1 << 12)
#घोषणा	QH_FULL_SPEED	(0 << 12)
#घोषणा	QH_INACTIVATE	(1 << 7)	/* Inactivate on next transaction */
	__hc32			hw_info2;        /* see EHCI 3.6.2 */
#घोषणा	QH_SMASK	0x000000ff
#घोषणा	QH_CMASK	0x0000ff00
#घोषणा	QH_HUBADDR	0x007f0000
#घोषणा	QH_HUBPORT	0x3f800000
#घोषणा	QH_MULT		0xc0000000
	__hc32			hw_current;	/* qtd list - see EHCI 3.6.4 */

	/* qtd overlay (hardware parts of a काष्ठा ehci_qtd) */
	__hc32			hw_qtd_next;
	__hc32			hw_alt_next;
	__hc32			hw_token;
	__hc32			hw_buf[5];
	__hc32			hw_buf_hi[5];
पूर्ण __aligned(32);

काष्ठा ehci_qh अणु
	काष्ठा ehci_qh_hw	*hw;		/* Must come first */
	/* the rest is HCD-निजी */
	dma_addr_t		qh_dma;		/* address of qh */
	जोड़ ehci_shaकरोw	qh_next;	/* ptr to qh; or periodic */
	काष्ठा list_head	qtd_list;	/* sw qtd list */
	काष्ठा list_head	पूर्णांकr_node;	/* list of पूर्णांकr QHs */
	काष्ठा ehci_qtd		*dummy;
	काष्ठा list_head	unlink_node;
	काष्ठा ehci_per_sched	ps;		/* scheduling info */

	अचिन्हित		unlink_cycle;

	u8			qh_state;
#घोषणा	QH_STATE_LINKED		1		/* HC sees this */
#घोषणा	QH_STATE_UNLINK		2		/* HC may still see this */
#घोषणा	QH_STATE_IDLE		3		/* HC करोesn't see this */
#घोषणा	QH_STATE_UNLINK_WAIT	4		/* LINKED and on unlink q */
#घोषणा	QH_STATE_COMPLETING	5		/* करोn't touch token.HALT */

	u8			xacterrs;	/* XactErr retry counter */
#घोषणा	QH_XACTERR_MAX		32		/* XactErr retry limit */

	u8			unlink_reason;
#घोषणा QH_UNLINK_HALTED	0x01		/* Halt flag is set */
#घोषणा QH_UNLINK_SHORT_READ	0x02		/* Recover from a लघु पढ़ो */
#घोषणा QH_UNLINK_DUMMY_OVERLAY	0x04		/* QH overlayed the dummy TD */
#घोषणा QH_UNLINK_SHUTDOWN	0x08		/* The HC isn't running */
#घोषणा QH_UNLINK_QUEUE_EMPTY	0x10		/* Reached end of the queue */
#घोषणा QH_UNLINK_REQUESTED	0x20		/* Disable, reset, or dequeue */

	u8			gap_uf;		/* uframes split/csplit gap */

	अचिन्हित		is_out:1;	/* bulk or पूर्णांकr OUT */
	अचिन्हित		clearing_tt:1;	/* Clear-TT-Buf in progress */
	अचिन्हित		dequeue_during_giveback:1;
	अचिन्हित		should_be_inactive:1;
पूर्ण;

/*-------------------------------------------------------------------------*/

/* description of one iso transaction (up to 3 KB data अगर highspeed) */
काष्ठा ehci_iso_packet अणु
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
काष्ठा ehci_iso_sched अणु
	काष्ठा list_head	td_list;
	अचिन्हित		span;
	अचिन्हित		first_packet;
	काष्ठा ehci_iso_packet	packet[];
पूर्ण;

/*
 * ehci_iso_stream - groups all (s)itds क्रम this endpoपूर्णांक.
 * acts like a qh would, अगर EHCI had them क्रम ISO.
 */
काष्ठा ehci_iso_stream अणु
	/* first field matches ehci_hq, but is शून्य */
	काष्ठा ehci_qh_hw	*hw;

	u8			bEndpoपूर्णांकAddress;
	u8			highspeed;
	काष्ठा list_head	td_list;	/* queued itds/sitds */
	काष्ठा list_head	मुक्त_list;	/* list of unused itds/sitds */

	/* output of (re)scheduling */
	काष्ठा ehci_per_sched	ps;		/* scheduling info */
	अचिन्हित		next_uframe;
	__hc32			splits;

	/* the rest is derived from the endpoपूर्णांक descriptor,
	 * including the extra info क्रम hw_bufp[0..2]
	 */
	u16			uperiod;	/* period in uframes */
	u16			maxp;
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
काष्ठा ehci_itd अणु
	/* first part defined by EHCI spec */
	__hc32			hw_next;           /* see EHCI 3.3.1 */
	__hc32			hw_transaction[8]; /* see EHCI 3.3.2 */
#घोषणा EHCI_ISOC_ACTIVE        (1<<31)        /* activate transfer this slot */
#घोषणा EHCI_ISOC_BUF_ERR       (1<<30)        /* Data buffer error */
#घोषणा EHCI_ISOC_BABBLE        (1<<29)        /* babble detected */
#घोषणा EHCI_ISOC_XACTERR       (1<<28)        /* XactErr - transaction error */
#घोषणा	EHCI_ITD_LENGTH(tok)	(((tok)>>16) & 0x0fff)
#घोषणा	EHCI_ITD_IOC		(1 << 15)	/* पूर्णांकerrupt on complete */

#घोषणा ITD_ACTIVE(ehci)	cpu_to_hc32(ehci, EHCI_ISOC_ACTIVE)

	__hc32			hw_bufp[7];	/* see EHCI 3.3.3 */
	__hc32			hw_bufp_hi[7];	/* Appendix B */

	/* the rest is HCD-निजी */
	dma_addr_t		itd_dma;	/* क्रम this itd */
	जोड़ ehci_shaकरोw	itd_next;	/* ptr to periodic q entry */

	काष्ठा urb		*urb;
	काष्ठा ehci_iso_stream	*stream;	/* endpoपूर्णांक's queue */
	काष्ठा list_head	itd_list;	/* list of stream's itds */

	/* any/all hw_transactions here may be used by that urb */
	अचिन्हित		frame;		/* where scheduled */
	अचिन्हित		pg;
	अचिन्हित		index[8];	/* in urb->iso_frame_desc */
पूर्ण __aligned(32);

/*-------------------------------------------------------------------------*/

/*
 * EHCI Specअगरication 0.95 Section 3.4
 * siTD, aka split-transaction isochronous Transfer Descriptor
 *       ... describe full speed iso xfers through TT in hubs
 * see Figure 3-5 "Split-transaction Isochronous Transaction Descriptor (siTD)
 */
काष्ठा ehci_sitd अणु
	/* first part defined by EHCI spec */
	__hc32			hw_next;
/* uses bit field macros above - see EHCI 0.95 Table 3-8 */
	__hc32			hw_fullspeed_ep;	/* EHCI table 3-9 */
	__hc32			hw_uframe;		/* EHCI table 3-10 */
	__hc32			hw_results;		/* EHCI table 3-11 */
#घोषणा	SITD_IOC	(1 << 31)	/* पूर्णांकerrupt on completion */
#घोषणा	SITD_PAGE	(1 << 30)	/* buffer 0/1 */
#घोषणा	SITD_LENGTH(x)	(((x) >> 16) & 0x3ff)
#घोषणा	SITD_STS_ACTIVE	(1 << 7)	/* HC may execute this */
#घोषणा	SITD_STS_ERR	(1 << 6)	/* error from TT */
#घोषणा	SITD_STS_DBE	(1 << 5)	/* data buffer error (in HC) */
#घोषणा	SITD_STS_BABBLE	(1 << 4)	/* device was babbling */
#घोषणा	SITD_STS_XACT	(1 << 3)	/* illegal IN response */
#घोषणा	SITD_STS_MMF	(1 << 2)	/* incomplete split transaction */
#घोषणा	SITD_STS_STS	(1 << 1)	/* split transaction state */

#घोषणा SITD_ACTIVE(ehci)	cpu_to_hc32(ehci, SITD_STS_ACTIVE)

	__hc32			hw_buf[2];		/* EHCI table 3-12 */
	__hc32			hw_backpoपूर्णांकer;		/* EHCI table 3-13 */
	__hc32			hw_buf_hi[2];		/* Appendix B */

	/* the rest is HCD-निजी */
	dma_addr_t		sitd_dma;
	जोड़ ehci_shaकरोw	sitd_next;	/* ptr to periodic q entry */

	काष्ठा urb		*urb;
	काष्ठा ehci_iso_stream	*stream;	/* endpoपूर्णांक's queue */
	काष्ठा list_head	sitd_list;	/* list of stream's sitds */
	अचिन्हित		frame;
	अचिन्हित		index;
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
काष्ठा ehci_fstn अणु
	__hc32			hw_next;	/* any periodic q entry */
	__hc32			hw_prev;	/* qh or EHCI_LIST_END */

	/* the rest is HCD-निजी */
	dma_addr_t		fstn_dma;
	जोड़ ehci_shaकरोw	fstn_next;	/* ptr to periodic q entry */
पूर्ण __aligned(32);

/*-------------------------------------------------------------------------*/

/*
 * USB-2.0 Specअगरication Sections 11.14 and 11.18
 * Scheduling and budgeting split transactions using TTs
 *
 * A hub can have a single TT क्रम all its ports, or multiple TTs (one क्रम each
 * port).  The bandwidth and budgeting inक्रमmation क्रम the full/low-speed bus
 * below each TT is self-contained and independent of the other TTs or the
 * high-speed bus.
 *
 * "Bandwidth" refers to the number of microseconds on the FS/LS bus allocated
 * to an पूर्णांकerrupt or isochronous endpoपूर्णांक क्रम each frame.  "Budget" refers to
 * the best-हाल estimate of the number of full-speed bytes allocated to an
 * endpoपूर्णांक क्रम each microframe within an allocated frame.
 *
 * Removal of an endpoपूर्णांक invalidates a TT's budget.  Instead of trying to
 * keep an up-to-date record, we recompute the budget when it is needed.
 */

काष्ठा ehci_tt अणु
	u16			bandwidth[EHCI_BANDWIDTH_FRAMES];

	काष्ठा list_head	tt_list;	/* List of all ehci_tt's */
	काष्ठा list_head	ps_list;	/* Items using this TT */
	काष्ठा usb_tt		*usb_tt;
	पूर्णांक			tt_port;	/* TT port number */
पूर्ण;

/*-------------------------------------------------------------------------*/

/* Prepare the PORTSC wakeup flags during controller suspend/resume */

#घोषणा ehci_prepare_ports_क्रम_controller_suspend(ehci, करो_wakeup)	\
		ehci_adjust_port_wakeup_flags(ehci, true, करो_wakeup)

#घोषणा ehci_prepare_ports_क्रम_controller_resume(ehci)			\
		ehci_adjust_port_wakeup_flags(ehci, false, false)

/*-------------------------------------------------------------------------*/

#अगर_घोषित CONFIG_USB_EHCI_ROOT_HUB_TT

/*
 * Some EHCI controllers have a Transaction Translator built पूर्णांकo the
 * root hub. This is a non-standard feature.  Each controller will need
 * to add code to the following अंतरभूत functions, and call them as
 * needed (mostly in root hub code).
 */

#घोषणा	ehci_is_TDI(e)			(ehci_to_hcd(e)->has_tt)

/* Returns the speed of a device attached to a port on the root hub. */
अटल अंतरभूत अचिन्हित पूर्णांक
ehci_port_speed(काष्ठा ehci_hcd *ehci, अचिन्हित पूर्णांक portsc)
अणु
	अगर (ehci_is_TDI(ehci)) अणु
		चयन ((portsc >> (ehci->has_hostpc ? 25 : 26)) & 3) अणु
		हाल 0:
			वापस 0;
		हाल 1:
			वापस USB_PORT_STAT_LOW_SPEED;
		हाल 2:
		शेष:
			वापस USB_PORT_STAT_HIGH_SPEED;
		पूर्ण
	पूर्ण
	वापस USB_PORT_STAT_HIGH_SPEED;
पूर्ण

#अन्यथा

#घोषणा	ehci_is_TDI(e)			(0)

#घोषणा	ehci_port_speed(ehci, portsc)	USB_PORT_STAT_HIGH_SPEED
#पूर्ण_अगर

/*-------------------------------------------------------------------------*/

#अगर_घोषित CONFIG_PPC_83xx
/* Some Freescale processors have an erratum in which the TT
 * port number in the queue head was 0..N-1 instead of 1..N.
 */
#घोषणा	ehci_has_fsl_portno_bug(e)		((e)->has_fsl_port_bug)
#अन्यथा
#घोषणा	ehci_has_fsl_portno_bug(e)		(0)
#पूर्ण_अगर

#घोषणा PORTSC_FSL_PFSC	24	/* Port Force Full-Speed Connect */

#अगर defined(CONFIG_PPC_85xx)
/* Some Freescale processors have an erratum (USB A-005275) in which
 * incoming packets get corrupted in HS mode
 */
#घोषणा ehci_has_fsl_hs_errata(e)	((e)->has_fsl_hs_errata)
#अन्यथा
#घोषणा ehci_has_fsl_hs_errata(e)	(0)
#पूर्ण_अगर

/*
 * Some Freescale/NXP processors have an erratum (USB A-005697)
 * in which we need to रुको क्रम 10ms क्रम bus to enter suspend mode
 * after setting SUSP bit.
 */
#घोषणा ehci_has_fsl_susp_errata(e)	((e)->has_fsl_susp_errata)

/*
 * While most USB host controllers implement their रेजिस्टरs in
 * little-endian क्रमmat, a minority (celleb companion chip) implement
 * them in big endian क्रमmat.
 *
 * This attempts to support either क्रमmat at compile समय without a
 * runसमय penalty, or both क्रमmats with the additional overhead
 * of checking a flag bit.
 *
 * ehci_big_endian_capbase is a special quirk क्रम controllers that
 * implement the HC capability रेजिस्टरs as separate रेजिस्टरs and not
 * as fields of a 32-bit रेजिस्टर.
 */

#अगर_घोषित CONFIG_USB_EHCI_BIG_ENDIAN_MMIO
#घोषणा ehci_big_endian_mmio(e)		((e)->big_endian_mmio)
#घोषणा ehci_big_endian_capbase(e)	((e)->big_endian_capbase)
#अन्यथा
#घोषणा ehci_big_endian_mmio(e)		0
#घोषणा ehci_big_endian_capbase(e)	0
#पूर्ण_अगर

/*
 * Big-endian पढ़ो/ग_लिखो functions are arch-specअगरic.
 * Other arches can be added अगर/when they're needed.
 */
#अगर defined(CONFIG_ARM) && defined(CONFIG_ARCH_IXP4XX)
#घोषणा पढ़ोl_be(addr)		__raw_पढ़ोl((__क्रमce अचिन्हित *)addr)
#घोषणा ग_लिखोl_be(val, addr)	__raw_ग_लिखोl(val, (__क्रमce अचिन्हित *)addr)
#पूर्ण_अगर

अटल अंतरभूत अचिन्हित पूर्णांक ehci_पढ़ोl(स्थिर काष्ठा ehci_hcd *ehci,
		__u32 __iomem *regs)
अणु
#अगर_घोषित CONFIG_USB_EHCI_BIG_ENDIAN_MMIO
	वापस ehci_big_endian_mmio(ehci) ?
		पढ़ोl_be(regs) :
		पढ़ोl(regs);
#अन्यथा
	वापस पढ़ोl(regs);
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_SOC_IMX28
अटल अंतरभूत व्योम imx28_ehci_ग_लिखोl(स्थिर अचिन्हित पूर्णांक val,
		अस्थिर __u32 __iomem *addr)
अणु
	__यंत्र__ ("swp %0, %0, [%1]" : : "r"(val), "r"(addr));
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम imx28_ehci_ग_लिखोl(स्थिर अचिन्हित पूर्णांक val,
		अस्थिर __u32 __iomem *addr)
अणु
पूर्ण
#पूर्ण_अगर
अटल अंतरभूत व्योम ehci_ग_लिखोl(स्थिर काष्ठा ehci_hcd *ehci,
		स्थिर अचिन्हित पूर्णांक val, __u32 __iomem *regs)
अणु
#अगर_घोषित CONFIG_USB_EHCI_BIG_ENDIAN_MMIO
	ehci_big_endian_mmio(ehci) ?
		ग_लिखोl_be(val, regs) :
		ग_लिखोl(val, regs);
#अन्यथा
	अगर (ehci->imx28_ग_लिखो_fix)
		imx28_ehci_ग_लिखोl(val, regs);
	अन्यथा
		ग_लिखोl(val, regs);
#पूर्ण_अगर
पूर्ण

/*
 * On certain ppc-44x SoC there is a HW issue, that could only worked around with
 * explicit suspend/operate of OHCI. This function hereby makes sense only on that arch.
 * Other common bits are dependent on has_amcc_usb23 quirk flag.
 */
#अगर_घोषित CONFIG_44x
अटल अंतरभूत व्योम set_ohci_hcfs(काष्ठा ehci_hcd *ehci, पूर्णांक operational)
अणु
	u32 hc_control;

	hc_control = (पढ़ोl_be(ehci->ohci_hcctrl_reg) & ~OHCI_CTRL_HCFS);
	अगर (operational)
		hc_control |= OHCI_USB_OPER;
	अन्यथा
		hc_control |= OHCI_USB_SUSPEND;

	ग_लिखोl_be(hc_control, ehci->ohci_hcctrl_reg);
	(व्योम) पढ़ोl_be(ehci->ohci_hcctrl_reg);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम set_ohci_hcfs(काष्ठा ehci_hcd *ehci, पूर्णांक operational)
अणु पूर्ण
#पूर्ण_अगर

/*-------------------------------------------------------------------------*/

/*
 * The AMCC 440EPx not only implements its EHCI रेजिस्टरs in big-endian
 * क्रमmat, but also its DMA data काष्ठाures (descriptors).
 *
 * EHCI controllers accessed through PCI work normally (little-endian
 * everywhere), so we won't bother supporting a BE-only mode क्रम now.
 */
#अगर_घोषित CONFIG_USB_EHCI_BIG_ENDIAN_DESC
#घोषणा ehci_big_endian_desc(e)		((e)->big_endian_desc)

/* cpu to ehci */
अटल अंतरभूत __hc32 cpu_to_hc32(स्थिर काष्ठा ehci_hcd *ehci, स्थिर u32 x)
अणु
	वापस ehci_big_endian_desc(ehci)
		? (__क्रमce __hc32)cpu_to_be32(x)
		: (__क्रमce __hc32)cpu_to_le32(x);
पूर्ण

/* ehci to cpu */
अटल अंतरभूत u32 hc32_to_cpu(स्थिर काष्ठा ehci_hcd *ehci, स्थिर __hc32 x)
अणु
	वापस ehci_big_endian_desc(ehci)
		? be32_to_cpu((__क्रमce __be32)x)
		: le32_to_cpu((__क्रमce __le32)x);
पूर्ण

अटल अंतरभूत u32 hc32_to_cpup(स्थिर काष्ठा ehci_hcd *ehci, स्थिर __hc32 *x)
अणु
	वापस ehci_big_endian_desc(ehci)
		? be32_to_cpup((__क्रमce __be32 *)x)
		: le32_to_cpup((__क्रमce __le32 *)x);
पूर्ण

#अन्यथा

/* cpu to ehci */
अटल अंतरभूत __hc32 cpu_to_hc32(स्थिर काष्ठा ehci_hcd *ehci, स्थिर u32 x)
अणु
	वापस cpu_to_le32(x);
पूर्ण

/* ehci to cpu */
अटल अंतरभूत u32 hc32_to_cpu(स्थिर काष्ठा ehci_hcd *ehci, स्थिर __hc32 x)
अणु
	वापस le32_to_cpu(x);
पूर्ण

अटल अंतरभूत u32 hc32_to_cpup(स्थिर काष्ठा ehci_hcd *ehci, स्थिर __hc32 *x)
अणु
	वापस le32_to_cpup(x);
पूर्ण

#पूर्ण_अगर

/*-------------------------------------------------------------------------*/

#घोषणा ehci_dbg(ehci, fmt, args...) \
	dev_dbg(ehci_to_hcd(ehci)->self.controller, fmt, ## args)
#घोषणा ehci_err(ehci, fmt, args...) \
	dev_err(ehci_to_hcd(ehci)->self.controller, fmt, ## args)
#घोषणा ehci_info(ehci, fmt, args...) \
	dev_info(ehci_to_hcd(ehci)->self.controller, fmt, ## args)
#घोषणा ehci_warn(ehci, fmt, args...) \
	dev_warn(ehci_to_hcd(ehci)->self.controller, fmt, ## args)

/*-------------------------------------------------------------------------*/

/* Declarations of things exported क्रम use by ehci platक्रमm drivers */

काष्ठा ehci_driver_overrides अणु
	माप_प्रकार		extra_priv_size;
	पूर्णांक		(*reset)(काष्ठा usb_hcd *hcd);
	पूर्णांक		(*port_घातer)(काष्ठा usb_hcd *hcd,
				पूर्णांक portnum, bool enable);
पूर्ण;

बाह्य व्योम	ehci_init_driver(काष्ठा hc_driver *drv,
				स्थिर काष्ठा ehci_driver_overrides *over);
बाह्य पूर्णांक	ehci_setup(काष्ठा usb_hcd *hcd);
बाह्य पूर्णांक	ehci_handshake(काष्ठा ehci_hcd *ehci, व्योम __iomem *ptr,
				u32 mask, u32 करोne, पूर्णांक usec);
बाह्य पूर्णांक	ehci_reset(काष्ठा ehci_hcd *ehci);

बाह्य पूर्णांक	ehci_suspend(काष्ठा usb_hcd *hcd, bool करो_wakeup);
बाह्य पूर्णांक	ehci_resume(काष्ठा usb_hcd *hcd, bool क्रमce_reset);
बाह्य व्योम	ehci_adjust_port_wakeup_flags(काष्ठा ehci_hcd *ehci,
			bool suspending, bool करो_wakeup);

बाह्य पूर्णांक	ehci_hub_control(काष्ठा usb_hcd	*hcd, u16 typeReq, u16 wValue,
				 u16 wIndex, अक्षर *buf, u16 wLength);

#पूर्ण_अगर /* __LINUX_EHCI_HCD_H */
