<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_UHCI_HCD_H
#घोषणा __LINUX_UHCI_HCD_H

#समावेश <linux/list.h>
#समावेश <linux/usb.h>
#समावेश <linux/clk.h>

#घोषणा usb_packetid(pipe)	(usb_pipein(pipe) ? USB_PID_IN : USB_PID_OUT)
#घोषणा PIPE_DEVEP_MASK		0x0007ff00


/*
 * Universal Host Controller Interface data काष्ठाures and defines
 */

/* Command रेजिस्टर */
#घोषणा USBCMD		0
#घोषणा   USBCMD_RS		0x0001	/* Run/Stop */
#घोषणा   USBCMD_HCRESET	0x0002	/* Host reset */
#घोषणा   USBCMD_GRESET		0x0004	/* Global reset */
#घोषणा   USBCMD_EGSM		0x0008	/* Global Suspend Mode */
#घोषणा   USBCMD_FGR		0x0010	/* Force Global Resume */
#घोषणा   USBCMD_SWDBG		0x0020	/* SW Debug mode */
#घोषणा   USBCMD_CF		0x0040	/* Config Flag (sw only) */
#घोषणा   USBCMD_MAXP		0x0080	/* Max Packet (0 = 32, 1 = 64) */

/* Status रेजिस्टर */
#घोषणा USBSTS		2
#घोषणा   USBSTS_USBINT		0x0001	/* Interrupt due to IOC */
#घोषणा   USBSTS_ERROR		0x0002	/* Interrupt due to error */
#घोषणा   USBSTS_RD		0x0004	/* Resume Detect */
#घोषणा   USBSTS_HSE		0x0008	/* Host System Error: PCI problems */
#घोषणा   USBSTS_HCPE		0x0010	/* Host Controller Process Error:
					 * the schedule is buggy */
#घोषणा   USBSTS_HCH		0x0020	/* HC Halted */

/* Interrupt enable रेजिस्टर */
#घोषणा USBINTR		4
#घोषणा   USBINTR_TIMEOUT	0x0001	/* Timeout/CRC error enable */
#घोषणा   USBINTR_RESUME	0x0002	/* Resume पूर्णांकerrupt enable */
#घोषणा   USBINTR_IOC		0x0004	/* Interrupt On Complete enable */
#घोषणा   USBINTR_SP		0x0008	/* Short packet पूर्णांकerrupt enable */

#घोषणा USBFRNUM	6
#घोषणा USBFLBASEADD	8
#घोषणा USBSOF		12
#घोषणा   USBSOF_DEFAULT	64	/* Frame length is exactly 1 ms */

/* USB port status and control रेजिस्टरs */
#घोषणा USBPORTSC1	16
#घोषणा USBPORTSC2	18
#घोषणा USBPORTSC3	20
#घोषणा USBPORTSC4	22
#घोषणा   USBPORTSC_CCS		0x0001	/* Current Connect Status
					 * ("device present") */
#घोषणा   USBPORTSC_CSC		0x0002	/* Connect Status Change */
#घोषणा   USBPORTSC_PE		0x0004	/* Port Enable */
#घोषणा   USBPORTSC_PEC		0x0008	/* Port Enable Change */
#घोषणा   USBPORTSC_DPLUS	0x0010	/* D+ high (line status) */
#घोषणा   USBPORTSC_DMINUS	0x0020	/* D- high (line status) */
#घोषणा   USBPORTSC_RD		0x0040	/* Resume Detect */
#घोषणा   USBPORTSC_RES1	0x0080	/* reserved, always 1 */
#घोषणा   USBPORTSC_LSDA	0x0100	/* Low Speed Device Attached */
#घोषणा   USBPORTSC_PR		0x0200	/* Port Reset */
/* OC and OCC from Intel 430TX and later (not UHCI 1.1d spec) */
#घोषणा   USBPORTSC_OC		0x0400	/* Over Current condition */
#घोषणा   USBPORTSC_OCC		0x0800	/* Over Current Change R/WC */
#घोषणा   USBPORTSC_SUSP	0x1000	/* Suspend */
#घोषणा   USBPORTSC_RES2	0x2000	/* reserved, ग_लिखो zeroes */
#घोषणा   USBPORTSC_RES3	0x4000	/* reserved, ग_लिखो zeroes */
#घोषणा   USBPORTSC_RES4	0x8000	/* reserved, ग_लिखो zeroes */

/* PCI legacy support रेजिस्टर */
#घोषणा USBLEGSUP		0xc0
#घोषणा   USBLEGSUP_DEFAULT	0x2000	/* only PIRQ enable set */
#घोषणा   USBLEGSUP_RWC		0x8f00	/* the R/WC bits */
#घोषणा   USBLEGSUP_RO		0x5040	/* R/O and reserved bits */

/* PCI Intel-specअगरic resume-enable रेजिस्टर */
#घोषणा USBRES_INTEL		0xc4
#घोषणा   USBPORT1EN		0x01
#घोषणा   USBPORT2EN		0x02

#घोषणा UHCI_PTR_BITS(uhci)	cpu_to_hc32((uhci), 0x000F)
#घोषणा UHCI_PTR_TERM(uhci)	cpu_to_hc32((uhci), 0x0001)
#घोषणा UHCI_PTR_QH(uhci)	cpu_to_hc32((uhci), 0x0002)
#घोषणा UHCI_PTR_DEPTH(uhci)	cpu_to_hc32((uhci), 0x0004)
#घोषणा UHCI_PTR_BREADTH(uhci)	cpu_to_hc32((uhci), 0x0000)

#घोषणा UHCI_NUMFRAMES		1024	/* in the frame list [array] */
#घोषणा UHCI_MAX_SOF_NUMBER	2047	/* in an SOF packet */
#घोषणा CAN_SCHEDULE_FRAMES	1000	/* how far in the future frames
					 * can be scheduled */
#घोषणा MAX_PHASE		32	/* Periodic scheduling length */

/* When no queues need Full-Speed Bandwidth Reclamation,
 * delay this दीर्घ beक्रमe turning FSBR off */
#घोषणा FSBR_OFF_DELAY		msecs_to_jअगरfies(10)

/* If a queue hasn't advanced after this much समय, assume it is stuck */
#घोषणा QH_WAIT_TIMEOUT		msecs_to_jअगरfies(200)


/*
 * __hc32 and __hc16 are "Host Controller" types, they may be equivalent to
 * __leXX (normally) or __beXX (given UHCI_BIG_ENDIAN_DESC), depending on
 * the host controller implementation.
 *
 * To facilitate the strongest possible byte-order checking from "sparse"
 * and so on, we use __leXX unless that's not practical.
 */
#अगर_घोषित CONFIG_USB_UHCI_BIG_ENDIAN_DESC
प्रकार __u32 __bitwise __hc32;
प्रकार __u16 __bitwise __hc16;
#अन्यथा
#घोषणा __hc32	__le32
#घोषणा __hc16	__le16
#पूर्ण_अगर

/*
 *	Queue Headers
 */

/*
 * One role of a QH is to hold a queue of TDs क्रम some endpoपूर्णांक.  One QH goes
 * with each endpoपूर्णांक, and qh->element (updated by the HC) is either:
 *   - the next unprocessed TD in the endpoपूर्णांक's queue, or
 *   - UHCI_PTR_TERM (when there's no more traffic क्रम this endpoपूर्णांक).
 *
 * The other role of a QH is to serve as a "skeleton" framelist entry, so we
 * can easily splice a QH क्रम some endpoपूर्णांक पूर्णांकo the schedule at the right
 * place.  Then qh->element is UHCI_PTR_TERM.
 *
 * In the schedule, qh->link मुख्यtains a list of QHs seen by the HC:
 *     skel1 --> ep1-qh --> ep2-qh --> ... --> skel2 --> ...
 *
 * qh->node is the software equivalent of qh->link.  The dअगरferences
 * are that the software list is करोubly-linked and QHs in the UNLINKING
 * state are on the software list but not the hardware schedule.
 *
 * For bookkeeping purposes we मुख्यtain QHs even क्रम Isochronous endpoपूर्णांकs,
 * but they never get added to the hardware schedule.
 */
#घोषणा QH_STATE_IDLE		1	/* QH is not being used */
#घोषणा QH_STATE_UNLINKING	2	/* QH has been हटाओd from the
					 * schedule but the hardware may
					 * still be using it */
#घोषणा QH_STATE_ACTIVE		3	/* QH is on the schedule */

काष्ठा uhci_qh अणु
	/* Hardware fields */
	__hc32 link;			/* Next QH in the schedule */
	__hc32 element;			/* Queue element (TD) poपूर्णांकer */

	/* Software fields */
	dma_addr_t dma_handle;

	काष्ठा list_head node;		/* Node in the list of QHs */
	काष्ठा usb_host_endpoपूर्णांक *hep;	/* Endpoपूर्णांक inक्रमmation */
	काष्ठा usb_device *udev;
	काष्ठा list_head queue;		/* Queue of urbps क्रम this QH */
	काष्ठा uhci_td *dummy_td;	/* Dummy TD to end the queue */
	काष्ठा uhci_td *post_td;	/* Last TD completed */

	काष्ठा usb_iso_packet_descriptor *iso_packet_desc;
					/* Next urb->iso_frame_desc entry */
	अचिन्हित दीर्घ advance_jअगरfies;	/* Time of last queue advance */
	अचिन्हित पूर्णांक unlink_frame;	/* When the QH was unlinked */
	अचिन्हित पूर्णांक period;		/* For Interrupt and Isochronous QHs */
	लघु phase;			/* Between 0 and period-1 */
	लघु load;			/* Periodic समय requirement, in us */
	अचिन्हित पूर्णांक iso_frame;		/* Frame # क्रम iso_packet_desc */

	पूर्णांक state;			/* QH_STATE_xxx; see above */
	पूर्णांक type;			/* Queue type (control, bulk, etc) */
	पूर्णांक skel;			/* Skeleton queue number */

	अचिन्हित पूर्णांक initial_toggle:1;	/* Endpoपूर्णांक's current toggle value */
	अचिन्हित पूर्णांक needs_fixup:1;	/* Must fix the TD toggle values */
	अचिन्हित पूर्णांक is_stopped:1;	/* Queue was stopped by error/unlink */
	अचिन्हित पूर्णांक रुको_expired:1;	/* QH_WAIT_TIMEOUT has expired */
	अचिन्हित पूर्णांक bandwidth_reserved:1;	/* Periodic bandwidth has
						 * been allocated */
पूर्ण __attribute__((aligned(16)));

/*
 * We need a special accessor क्रम the element poपूर्णांकer because it is
 * subject to asynchronous updates by the controller.
 */
#घोषणा qh_element(qh)		READ_ONCE((qh)->element)

#घोषणा LINK_TO_QH(uhci, qh)	(UHCI_PTR_QH((uhci)) | \
				cpu_to_hc32((uhci), (qh)->dma_handle))


/*
 *	Transfer Descriptors
 */

/*
 * क्रम TD <status>:
 */
#घोषणा TD_CTRL_SPD		(1 << 29)	/* Short Packet Detect */
#घोषणा TD_CTRL_C_ERR_MASK	(3 << 27)	/* Error Counter bits */
#घोषणा TD_CTRL_C_ERR_SHIFT	27
#घोषणा TD_CTRL_LS		(1 << 26)	/* Low Speed Device */
#घोषणा TD_CTRL_IOS		(1 << 25)	/* Isochronous Select */
#घोषणा TD_CTRL_IOC		(1 << 24)	/* Interrupt on Complete */
#घोषणा TD_CTRL_ACTIVE		(1 << 23)	/* TD Active */
#घोषणा TD_CTRL_STALLED		(1 << 22)	/* TD Stalled */
#घोषणा TD_CTRL_DBUFERR		(1 << 21)	/* Data Buffer Error */
#घोषणा TD_CTRL_BABBLE		(1 << 20)	/* Babble Detected */
#घोषणा TD_CTRL_NAK		(1 << 19)	/* NAK Received */
#घोषणा TD_CTRL_CRCTIMEO	(1 << 18)	/* CRC/Time Out Error */
#घोषणा TD_CTRL_BITSTUFF	(1 << 17)	/* Bit Stuff Error */
#घोषणा TD_CTRL_ACTLEN_MASK	0x7FF	/* actual length, encoded as n - 1 */

#घोषणा uhci_maxerr(err)		((err) << TD_CTRL_C_ERR_SHIFT)
#घोषणा uhci_status_bits(ctrl_sts)	((ctrl_sts) & 0xF60000)
#घोषणा uhci_actual_length(ctrl_sts)	(((ctrl_sts) + 1) & \
			TD_CTRL_ACTLEN_MASK)	/* 1-based */

/*
 * क्रम TD <info>: (a.k.a. Token)
 */
#घोषणा td_token(uhci, td)	hc32_to_cpu((uhci), (td)->token)
#घोषणा TD_TOKEN_DEVADDR_SHIFT	8
#घोषणा TD_TOKEN_TOGGLE_SHIFT	19
#घोषणा TD_TOKEN_TOGGLE		(1 << 19)
#घोषणा TD_TOKEN_EXPLEN_SHIFT	21
#घोषणा TD_TOKEN_EXPLEN_MASK	0x7FF	/* expected length, encoded as n-1 */
#घोषणा TD_TOKEN_PID_MASK	0xFF

#घोषणा uhci_explen(len)	((((len) - 1) & TD_TOKEN_EXPLEN_MASK) << \
					TD_TOKEN_EXPLEN_SHIFT)

#घोषणा uhci_expected_length(token) ((((token) >> TD_TOKEN_EXPLEN_SHIFT) + \
					1) & TD_TOKEN_EXPLEN_MASK)
#घोषणा uhci_toggle(token)	(((token) >> TD_TOKEN_TOGGLE_SHIFT) & 1)
#घोषणा uhci_endpoपूर्णांक(token)	(((token) >> 15) & 0xf)
#घोषणा uhci_devaddr(token)	(((token) >> TD_TOKEN_DEVADDR_SHIFT) & 0x7f)
#घोषणा uhci_devep(token)	(((token) >> TD_TOKEN_DEVADDR_SHIFT) & 0x7ff)
#घोषणा uhci_packetid(token)	((token) & TD_TOKEN_PID_MASK)
#घोषणा uhci_packetout(token)	(uhci_packetid(token) != USB_PID_IN)
#घोषणा uhci_packetin(token)	(uhci_packetid(token) == USB_PID_IN)

/*
 * The करोcumentation says "4 words for hardware, 4 words for software".
 *
 * That's silly, the hardware doesn't care. The hardware only cares that
 * the hardware words are 16-byte aligned, and we can have any amount of
 * sw space after the TD entry.
 *
 * td->link poपूर्णांकs to either another TD (not necessarily क्रम the same urb or
 * even the same endpoपूर्णांक), or nothing (PTR_TERM), or a QH.
 */
काष्ठा uhci_td अणु
	/* Hardware fields */
	__hc32 link;
	__hc32 status;
	__hc32 token;
	__hc32 buffer;

	/* Software fields */
	dma_addr_t dma_handle;

	काष्ठा list_head list;

	पूर्णांक frame;			/* क्रम iso: what frame? */
	काष्ठा list_head fl_list;
पूर्ण __attribute__((aligned(16)));

/*
 * We need a special accessor क्रम the control/status word because it is
 * subject to asynchronous updates by the controller.
 */
#घोषणा td_status(uhci, td)		hc32_to_cpu((uhci), \
						READ_ONCE((td)->status))

#घोषणा LINK_TO_TD(uhci, td)		(cpu_to_hc32((uhci), (td)->dma_handle))


/*
 *	Skeleton Queue Headers
 */

/*
 * The UHCI driver uses QHs with Interrupt, Control and Bulk URBs क्रम
 * स्वतःmatic queuing. To make it easy to insert entries पूर्णांकo the schedule,
 * we have a skeleton of QHs क्रम each predefined Interrupt latency.
 * Asynchronous QHs (low-speed control, full-speed control, and bulk)
 * go onto the period-1 पूर्णांकerrupt list, since they all get accessed on
 * every frame.
 *
 * When we want to add a new QH, we add it to the list starting from the
 * appropriate skeleton QH.  For instance, the schedule can look like this:
 *
 * skel पूर्णांक128 QH
 * dev 1 पूर्णांकerrupt QH
 * dev 5 पूर्णांकerrupt QH
 * skel पूर्णांक64 QH
 * skel पूर्णांक32 QH
 * ...
 * skel पूर्णांक1 + async QH
 * dev 5 low-speed control QH
 * dev 1 bulk QH
 * dev 2 bulk QH
 *
 * There is a special terminating QH used to keep full-speed bandwidth
 * reclamation active when no full-speed control or bulk QHs are linked
 * पूर्णांकo the schedule.  It has an inactive TD (to work around a PIIX bug,
 * see the Intel errata) and it poपूर्णांकs back to itself.
 *
 * There's a special skeleton QH क्रम Isochronous QHs which never appears
 * on the schedule.  Isochronous TDs go on the schedule beक्रमe the
 * the skeleton QHs.  The hardware accesses them directly rather than
 * through their QH, which is used only क्रम bookkeeping purposes.
 * While the UHCI spec करोesn't क्रमbid the use of QHs क्रम Isochronous,
 * it करोesn't use them either.  And the spec says that queues never
 * advance on an error completion status, which makes them totally
 * unsuitable क्रम Isochronous transfers.
 *
 * There's also a special skeleton QH used क्रम QHs which are in the process
 * of unlinking and so may still be in use by the hardware.  It too never
 * appears on the schedule.
 */

#घोषणा UHCI_NUM_SKELQH		11
#घोषणा SKEL_UNLINK		0
#घोषणा skel_unlink_qh		skelqh[SKEL_UNLINK]
#घोषणा SKEL_ISO		1
#घोषणा skel_iso_qh		skelqh[SKEL_ISO]
	/* पूर्णांक128, पूर्णांक64, ..., पूर्णांक1 = 2, 3, ..., 9 */
#घोषणा SKEL_INDEX(exponent)	(9 - exponent)
#घोषणा SKEL_ASYNC		9
#घोषणा skel_async_qh		skelqh[SKEL_ASYNC]
#घोषणा SKEL_TERM		10
#घोषणा skel_term_qh		skelqh[SKEL_TERM]

/* The following entries refer to sublists of skel_async_qh */
#घोषणा SKEL_LS_CONTROL		20
#घोषणा SKEL_FS_CONTROL		21
#घोषणा SKEL_FSBR		SKEL_FS_CONTROL
#घोषणा SKEL_BULK		22

/*
 *	The UHCI controller and root hub
 */

/*
 * States क्रम the root hub:
 *
 * To prevent "bouncing" in the presence of electrical noise,
 * when there are no devices attached we delay क्रम 1 second in the
 * RUNNING_NODEVS state beक्रमe चयनing to the AUTO_STOPPED state.
 * 
 * (Note that the AUTO_STOPPED state won't be necessary once the hub
 * driver learns to स्वतःsuspend.)
 */
क्रमागत uhci_rh_state अणु
	/* In the following states the HC must be halted.
	 * These two must come first. */
	UHCI_RH_RESET,
	UHCI_RH_SUSPENDED,

	UHCI_RH_AUTO_STOPPED,
	UHCI_RH_RESUMING,

	/* In this state the HC changes from running to halted,
	 * so it can legally appear either way. */
	UHCI_RH_SUSPENDING,

	/* In the following states it's an error अगर the HC is halted.
	 * These two must come last. */
	UHCI_RH_RUNNING,		/* The normal state */
	UHCI_RH_RUNNING_NODEVS,		/* Running with no devices attached */
पूर्ण;

/*
 * The full UHCI controller inक्रमmation:
 */
काष्ठा uhci_hcd अणु
	/* Grabbed from PCI */
	अचिन्हित दीर्घ io_addr;

	/* Used when रेजिस्टरs are memory mapped */
	व्योम __iomem *regs;

	काष्ठा dma_pool *qh_pool;
	काष्ठा dma_pool *td_pool;

	काष्ठा uhci_td *term_td;	/* Terminating TD, see UHCI bug */
	काष्ठा uhci_qh *skelqh[UHCI_NUM_SKELQH];	/* Skeleton QHs */
	काष्ठा uhci_qh *next_qh;	/* Next QH to scan */

	spinlock_t lock;

	dma_addr_t frame_dma_handle;	/* Hardware frame list */
	__hc32 *frame;
	व्योम **frame_cpu;		/* CPU's frame list */

	क्रमागत uhci_rh_state rh_state;
	अचिन्हित दीर्घ स्वतः_stop_समय;		/* When to AUTO_STOP */

	अचिन्हित पूर्णांक frame_number;		/* As of last check */
	अचिन्हित पूर्णांक is_stopped;
#घोषणा UHCI_IS_STOPPED		9999		/* Larger than a frame # */
	अचिन्हित पूर्णांक last_iso_frame;		/* Frame of last scan */
	अचिन्हित पूर्णांक cur_iso_frame;		/* Frame क्रम current scan */

	अचिन्हित पूर्णांक scan_in_progress:1;	/* Schedule scan is running */
	अचिन्हित पूर्णांक need_rescan:1;		/* Reकरो the schedule scan */
	अचिन्हित पूर्णांक dead:1;			/* Controller has died */
	अचिन्हित पूर्णांक RD_enable:1;		/* Suspended root hub with
						   Resume-Detect पूर्णांकerrupts
						   enabled */
	अचिन्हित पूर्णांक is_initialized:1;		/* Data काष्ठाure is usable */
	अचिन्हित पूर्णांक fsbr_is_on:1;		/* FSBR is turned on */
	अचिन्हित पूर्णांक fsbr_is_wanted:1;		/* Does any URB want FSBR? */
	अचिन्हित पूर्णांक fsbr_expiring:1;		/* FSBR is timing out */

	काष्ठा समयr_list fsbr_समयr;		/* For turning off FBSR */

	/* Silicon quirks */
	अचिन्हित पूर्णांक oc_low:1;			/* OverCurrent bit active low */
	अचिन्हित पूर्णांक रुको_क्रम_hp:1;		/* Wait क्रम HP port reset */
	अचिन्हित पूर्णांक big_endian_mmio:1;		/* Big endian रेजिस्टरs */
	अचिन्हित पूर्णांक big_endian_desc:1;		/* Big endian descriptors */
	अचिन्हित पूर्णांक is_aspeed:1;		/* Aspeed impl. workarounds */

	/* Support क्रम port suspend/resume/reset */
	अचिन्हित दीर्घ port_c_suspend;		/* Bit-arrays of ports */
	अचिन्हित दीर्घ resuming_ports;
	अचिन्हित दीर्घ ports_समयout;		/* Time to stop संकेतling */

	काष्ठा list_head idle_qh_list;		/* Where the idle QHs live */

	पूर्णांक rh_numports;			/* Number of root-hub ports */

	रुको_queue_head_t रुकोqh;		/* endpoपूर्णांक_disable रुकोers */
	पूर्णांक num_रुकोing;			/* Number of रुकोers */

	पूर्णांक total_load;				/* Sum of array values */
	लघु load[MAX_PHASE];			/* Periodic allocations */

	काष्ठा clk *clk;			/* (optional) घड़ी source */

	/* Reset host controller */
	व्योम	(*reset_hc) (काष्ठा uhci_hcd *uhci);
	पूर्णांक	(*check_and_reset_hc) (काष्ठा uhci_hcd *uhci);
	/* configure_hc should perक्रमm arch specअगरic settings, अगर needed */
	व्योम	(*configure_hc) (काष्ठा uhci_hcd *uhci);
	/* Check क्रम broken resume detect पूर्णांकerrupts */
	पूर्णांक	(*resume_detect_पूर्णांकerrupts_are_broken) (काष्ठा uhci_hcd *uhci);
	/* Check क्रम broken global suspend */
	पूर्णांक	(*global_suspend_mode_is_broken) (काष्ठा uhci_hcd *uhci);
पूर्ण;

/* Convert between a usb_hcd poपूर्णांकer and the corresponding uhci_hcd */
अटल अंतरभूत काष्ठा uhci_hcd *hcd_to_uhci(काष्ठा usb_hcd *hcd)
अणु
	वापस (काष्ठा uhci_hcd *) (hcd->hcd_priv);
पूर्ण
अटल अंतरभूत काष्ठा usb_hcd *uhci_to_hcd(काष्ठा uhci_hcd *uhci)
अणु
	वापस container_of((व्योम *) uhci, काष्ठा usb_hcd, hcd_priv);
पूर्ण

#घोषणा uhci_dev(u)	(uhci_to_hcd(u)->self.controller)

/* Utility macro क्रम comparing frame numbers */
#घोषणा uhci_frame_beक्रमe_eq(f1, f2)	(0 <= (पूर्णांक) ((f2) - (f1)))


/*
 *	Private per-URB data
 */
काष्ठा urb_priv अणु
	काष्ठा list_head node;		/* Node in the QH's urbp list */

	काष्ठा urb *urb;

	काष्ठा uhci_qh *qh;		/* QH क्रम this URB */
	काष्ठा list_head td_list;

	अचिन्हित fsbr:1;		/* URB wants FSBR */
पूर्ण;


/* Some special IDs */

#घोषणा PCI_VENDOR_ID_GENESYS		0x17a0
#घोषणा PCI_DEVICE_ID_GL880S_UHCI	0x8083

/* Aspeed SoC needs some quirks */
अटल अंतरभूत bool uhci_is_aspeed(स्थिर काष्ठा uhci_hcd *uhci)
अणु
	वापस IS_ENABLED(CONFIG_USB_UHCI_ASPEED) && uhci->is_aspeed;
पूर्ण

/*
 * Functions used to access controller रेजिस्टरs. The UCHI spec says that host
 * controller I/O रेजिस्टरs are mapped पूर्णांकo PCI I/O space. For non-PCI hosts
 * we use memory mapped रेजिस्टरs.
 */

#अगर_अघोषित CONFIG_USB_UHCI_SUPPORT_NON_PCI_HC
/* Support PCI only */
अटल अंतरभूत u32 uhci_पढ़ोl(स्थिर काष्ठा uhci_hcd *uhci, पूर्णांक reg)
अणु
	वापस inl(uhci->io_addr + reg);
पूर्ण

अटल अंतरभूत व्योम uhci_ग_लिखोl(स्थिर काष्ठा uhci_hcd *uhci, u32 val, पूर्णांक reg)
अणु
	outl(val, uhci->io_addr + reg);
पूर्ण

अटल अंतरभूत u16 uhci_पढ़ोw(स्थिर काष्ठा uhci_hcd *uhci, पूर्णांक reg)
अणु
	वापस inw(uhci->io_addr + reg);
पूर्ण

अटल अंतरभूत व्योम uhci_ग_लिखोw(स्थिर काष्ठा uhci_hcd *uhci, u16 val, पूर्णांक reg)
अणु
	outw(val, uhci->io_addr + reg);
पूर्ण

अटल अंतरभूत u8 uhci_पढ़ोb(स्थिर काष्ठा uhci_hcd *uhci, पूर्णांक reg)
अणु
	वापस inb(uhci->io_addr + reg);
पूर्ण

अटल अंतरभूत व्योम uhci_ग_लिखोb(स्थिर काष्ठा uhci_hcd *uhci, u8 val, पूर्णांक reg)
अणु
	outb(val, uhci->io_addr + reg);
पूर्ण

#अन्यथा
/* Support non-PCI host controllers */
#अगर_घोषित CONFIG_USB_PCI
/* Support PCI and non-PCI host controllers */
#घोषणा uhci_has_pci_रेजिस्टरs(u)	((u)->io_addr != 0)
#अन्यथा
/* Support non-PCI host controllers only */
#घोषणा uhci_has_pci_रेजिस्टरs(u)	0
#पूर्ण_अगर

#अगर_घोषित CONFIG_USB_UHCI_BIG_ENDIAN_MMIO
/* Support (non-PCI) big endian host controllers */
#घोषणा uhci_big_endian_mmio(u)		((u)->big_endian_mmio)
#अन्यथा
#घोषणा uhci_big_endian_mmio(u)		0
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक uhci_aspeed_reg(अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल USBCMD:
		वापस 00;
	हाल USBSTS:
		वापस 0x04;
	हाल USBINTR:
		वापस 0x08;
	हाल USBFRNUM:
		वापस 0x80;
	हाल USBFLBASEADD:
		वापस 0x0c;
	हाल USBSOF:
		वापस 0x84;
	हाल USBPORTSC1:
		वापस 0x88;
	हाल USBPORTSC2:
		वापस 0x8c;
	हाल USBPORTSC3:
		वापस 0x90;
	हाल USBPORTSC4:
		वापस 0x94;
	शेष:
		pr_warn("UHCI: Unsupported register 0x%02x on Aspeed\n", reg);
		/* Return an unimplemented रेजिस्टर */
		वापस 0x10;
	पूर्ण
पूर्ण

अटल अंतरभूत u32 uhci_पढ़ोl(स्थिर काष्ठा uhci_hcd *uhci, पूर्णांक reg)
अणु
	अगर (uhci_has_pci_रेजिस्टरs(uhci))
		वापस inl(uhci->io_addr + reg);
	अन्यथा अगर (uhci_is_aspeed(uhci))
		वापस पढ़ोl(uhci->regs + uhci_aspeed_reg(reg));
#अगर_घोषित CONFIG_USB_UHCI_BIG_ENDIAN_MMIO
	अन्यथा अगर (uhci_big_endian_mmio(uhci))
		वापस पढ़ोl_be(uhci->regs + reg);
#पूर्ण_अगर
	अन्यथा
		वापस पढ़ोl(uhci->regs + reg);
पूर्ण

अटल अंतरभूत व्योम uhci_ग_लिखोl(स्थिर काष्ठा uhci_hcd *uhci, u32 val, पूर्णांक reg)
अणु
	अगर (uhci_has_pci_रेजिस्टरs(uhci))
		outl(val, uhci->io_addr + reg);
	अन्यथा अगर (uhci_is_aspeed(uhci))
		ग_लिखोl(val, uhci->regs + uhci_aspeed_reg(reg));
#अगर_घोषित CONFIG_USB_UHCI_BIG_ENDIAN_MMIO
	अन्यथा अगर (uhci_big_endian_mmio(uhci))
		ग_लिखोl_be(val, uhci->regs + reg);
#पूर्ण_अगर
	अन्यथा
		ग_लिखोl(val, uhci->regs + reg);
पूर्ण

अटल अंतरभूत u16 uhci_पढ़ोw(स्थिर काष्ठा uhci_hcd *uhci, पूर्णांक reg)
अणु
	अगर (uhci_has_pci_रेजिस्टरs(uhci))
		वापस inw(uhci->io_addr + reg);
	अन्यथा अगर (uhci_is_aspeed(uhci))
		वापस पढ़ोl(uhci->regs + uhci_aspeed_reg(reg));
#अगर_घोषित CONFIG_USB_UHCI_BIG_ENDIAN_MMIO
	अन्यथा अगर (uhci_big_endian_mmio(uhci))
		वापस पढ़ोw_be(uhci->regs + reg);
#पूर्ण_अगर
	अन्यथा
		वापस पढ़ोw(uhci->regs + reg);
पूर्ण

अटल अंतरभूत व्योम uhci_ग_लिखोw(स्थिर काष्ठा uhci_hcd *uhci, u16 val, पूर्णांक reg)
अणु
	अगर (uhci_has_pci_रेजिस्टरs(uhci))
		outw(val, uhci->io_addr + reg);
	अन्यथा अगर (uhci_is_aspeed(uhci))
		ग_लिखोl(val, uhci->regs + uhci_aspeed_reg(reg));
#अगर_घोषित CONFIG_USB_UHCI_BIG_ENDIAN_MMIO
	अन्यथा अगर (uhci_big_endian_mmio(uhci))
		ग_लिखोw_be(val, uhci->regs + reg);
#पूर्ण_अगर
	अन्यथा
		ग_लिखोw(val, uhci->regs + reg);
पूर्ण

अटल अंतरभूत u8 uhci_पढ़ोb(स्थिर काष्ठा uhci_hcd *uhci, पूर्णांक reg)
अणु
	अगर (uhci_has_pci_रेजिस्टरs(uhci))
		वापस inb(uhci->io_addr + reg);
	अन्यथा अगर (uhci_is_aspeed(uhci))
		वापस पढ़ोl(uhci->regs + uhci_aspeed_reg(reg));
#अगर_घोषित CONFIG_USB_UHCI_BIG_ENDIAN_MMIO
	अन्यथा अगर (uhci_big_endian_mmio(uhci))
		वापस पढ़ोb_be(uhci->regs + reg);
#पूर्ण_अगर
	अन्यथा
		वापस पढ़ोb(uhci->regs + reg);
पूर्ण

अटल अंतरभूत व्योम uhci_ग_लिखोb(स्थिर काष्ठा uhci_hcd *uhci, u8 val, पूर्णांक reg)
अणु
	अगर (uhci_has_pci_रेजिस्टरs(uhci))
		outb(val, uhci->io_addr + reg);
	अन्यथा अगर (uhci_is_aspeed(uhci))
		ग_लिखोl(val, uhci->regs + uhci_aspeed_reg(reg));
#अगर_घोषित CONFIG_USB_UHCI_BIG_ENDIAN_MMIO
	अन्यथा अगर (uhci_big_endian_mmio(uhci))
		ग_लिखोb_be(val, uhci->regs + reg);
#पूर्ण_अगर
	अन्यथा
		ग_लिखोb(val, uhci->regs + reg);
पूर्ण
#पूर्ण_अगर /* CONFIG_USB_UHCI_SUPPORT_NON_PCI_HC */

/*
 * The GRLIB GRUSBHC controller can use big endian क्रमmat क्रम its descriptors.
 *
 * UHCI controllers accessed through PCI work normally (little-endian
 * everywhere), so we करोn't bother supporting a BE-only mode.
 */
#अगर_घोषित CONFIG_USB_UHCI_BIG_ENDIAN_DESC
#घोषणा uhci_big_endian_desc(u)		((u)->big_endian_desc)

/* cpu to uhci */
अटल अंतरभूत __hc32 cpu_to_hc32(स्थिर काष्ठा uhci_hcd *uhci, स्थिर u32 x)
अणु
	वापस uhci_big_endian_desc(uhci)
		? (__क्रमce __hc32)cpu_to_be32(x)
		: (__क्रमce __hc32)cpu_to_le32(x);
पूर्ण

/* uhci to cpu */
अटल अंतरभूत u32 hc32_to_cpu(स्थिर काष्ठा uhci_hcd *uhci, स्थिर __hc32 x)
अणु
	वापस uhci_big_endian_desc(uhci)
		? be32_to_cpu((__क्रमce __be32)x)
		: le32_to_cpu((__क्रमce __le32)x);
पूर्ण

#अन्यथा
/* cpu to uhci */
अटल अंतरभूत __hc32 cpu_to_hc32(स्थिर काष्ठा uhci_hcd *uhci, स्थिर u32 x)
अणु
	वापस cpu_to_le32(x);
पूर्ण

/* uhci to cpu */
अटल अंतरभूत u32 hc32_to_cpu(स्थिर काष्ठा uhci_hcd *uhci, स्थिर __hc32 x)
अणु
	वापस le32_to_cpu(x);
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
