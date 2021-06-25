<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-1.0+ */
/*
 * OHCI HCD (Host Controller Driver) क्रम USB.
 *
 * (C) Copyright 1999 Roman Weissgaerber <weissg@vienna.at>
 * (C) Copyright 2000-2002 David Brownell <dbrownell@users.sourceक्रमge.net>
 *
 * This file is licenced under the GPL.
 */

/*
 * __hc32 and __hc16 are "Host Controller" types, they may be equivalent to
 * __leXX (normally) or __beXX (given OHCI_BIG_ENDIAN), depending on the
 * host controller implementation.
 */
प्रकार __u32 __bitwise __hc32;
प्रकार __u16 __bitwise __hc16;

/*
 * OHCI Endpoपूर्णांक Descriptor (ED) ... holds TD queue
 * See OHCI spec, section 4.2
 *
 * This is a "Queue Head" क्रम those transfers, which is why
 * both EHCI and UHCI call similar काष्ठाures a "QH".
 */
काष्ठा ed अणु
	/* first fields are hardware-specअगरied */
	__hc32			hwINFO;      /* endpoपूर्णांक config biपंचांगap */
	/* info bits defined by hcd */
#घोषणा ED_DEQUEUE	(1 << 27)
	/* info bits defined by the hardware */
#घोषणा ED_ISO		(1 << 15)
#घोषणा ED_SKIP		(1 << 14)
#घोषणा ED_LOWSPEED	(1 << 13)
#घोषणा ED_OUT		(0x01 << 11)
#घोषणा ED_IN		(0x02 << 11)
	__hc32			hwTailP;	/* tail of TD list */
	__hc32			hwHeadP;	/* head of TD list (hc r/w) */
#घोषणा ED_C		(0x02)			/* toggle carry */
#घोषणा ED_H		(0x01)			/* halted */
	__hc32			hwNextED;	/* next ED in list */

	/* rest are purely क्रम the driver's use */
	dma_addr_t		dma;		/* addr of ED */
	काष्ठा td		*dummy;		/* next TD to activate */

	/* host's view of schedule */
	काष्ठा ed		*ed_next;	/* on schedule or rm_list */
	काष्ठा ed		*ed_prev;	/* क्रम non-पूर्णांकerrupt EDs */
	काष्ठा list_head	td_list;	/* "shadow list" of our TDs */
	काष्ठा list_head	in_use_list;

	/* create --> IDLE --> OPER --> ... --> IDLE --> destroy
	 * usually:  OPER --> UNLINK --> (IDLE | OPER) --> ...
	 */
	u8			state;		/* ED_अणुIDLE,UNLINK,OPERपूर्ण */
#घोषणा ED_IDLE		0x00		/* NOT linked to HC */
#घोषणा ED_UNLINK	0x01		/* being unlinked from hc */
#घोषणा ED_OPER		0x02		/* IS linked to hc */

	u8			type;		/* PIPE_अणुBULK,...पूर्ण */

	/* periodic scheduling params (क्रम पूर्णांकr and iso) */
	u8			branch;
	u16			पूर्णांकerval;
	u16			load;
	u16			last_iso;	/* iso only */

	/* HC may see EDs on rm_list until next frame (frame_no == tick) */
	u16			tick;

	/* Detect TDs not added to the करोne queue */
	अचिन्हित		takeback_wdh_cnt;
	काष्ठा td		*pending_td;
#घोषणा	OKAY_TO_TAKEBACK(ohci, ed)			\
		((पूर्णांक) (ohci->wdh_cnt - ed->takeback_wdh_cnt) >= 0)

पूर्ण __attribute__ ((aligned(16)));

#घोषणा ED_MASK	((u32)~0x0f)		/* strip hw status in low addr bits */


/*
 * OHCI Transfer Descriptor (TD) ... one per transfer segment
 * See OHCI spec, sections 4.3.1 (general = control/bulk/पूर्णांकerrupt)
 * and 4.3.2 (iso)
 */
काष्ठा td अणु
	/* first fields are hardware-specअगरied */
	__hc32		hwINFO;		/* transfer info biपंचांगask */

	/* hwINFO bits क्रम both general and iso tds: */
#घोषणा TD_CC       0xf0000000			/* condition code */
#घोषणा TD_CC_GET(td_p) ((td_p >>28) & 0x0f)
//#घोषणा TD_CC_SET(td_p, cc) (td_p) = ((td_p) & 0x0fffffff) | (((cc) & 0x0f) << 28)
#घोषणा TD_DI       0x00E00000			/* frames beक्रमe पूर्णांकerrupt */
#घोषणा TD_DI_SET(X) (((X) & 0x07)<< 21)
	/* these two bits are available क्रम definition/use by HCDs in both
	 * general and iso tds ... others are available क्रम only one type
	 */
#घोषणा TD_DONE     0x00020000			/* retired to करोnelist */
#घोषणा TD_ISO      0x00010000			/* copy of ED_ISO */

	/* hwINFO bits क्रम general tds: */
#घोषणा TD_EC       0x0C000000			/* error count */
#घोषणा TD_T        0x03000000			/* data toggle state */
#घोषणा TD_T_DATA0  0x02000000				/* DATA0 */
#घोषणा TD_T_DATA1  0x03000000				/* DATA1 */
#घोषणा TD_T_TOGGLE 0x00000000				/* uses ED_C */
#घोषणा TD_DP       0x00180000			/* direction/pid */
#घोषणा TD_DP_SETUP 0x00000000			/* SETUP pid */
#घोषणा TD_DP_IN    0x00100000				/* IN pid */
#घोषणा TD_DP_OUT   0x00080000				/* OUT pid */
							/* 0x00180000 rsvd */
#घोषणा TD_R        0x00040000			/* round: लघु packets OK? */

	/* (no hwINFO #घोषणाs yet क्रम iso tds) */

	__hc32		hwCBP;		/* Current Buffer Poपूर्णांकer (or 0) */
	__hc32		hwNextTD;	/* Next TD Poपूर्णांकer */
	__hc32		hwBE;		/* Memory Buffer End Poपूर्णांकer */

	/* PSW is only क्रम ISO.  Only 1 PSW entry is used, but on
	 * big-endian PPC hardware that's the second entry.
	 */
#घोषणा MAXPSW	2
	__hc16		hwPSW [MAXPSW];

	/* rest are purely क्रम the driver's use */
	__u8		index;
	काष्ठा ed	*ed;
	काष्ठा td	*td_hash;	/* dma-->td hashtable */
	काष्ठा td	*next_dl_td;
	काष्ठा urb	*urb;

	dma_addr_t	td_dma;		/* addr of this TD */
	dma_addr_t	data_dma;	/* addr of data it poपूर्णांकs to */

	काष्ठा list_head td_list;	/* "shadow list", TDs on same ED */
पूर्ण __attribute__ ((aligned(32)));	/* c/b/i need 16; only iso needs 32 */

#घोषणा TD_MASK	((u32)~0x1f)		/* strip hw status in low addr bits */

/*
 * Hardware transfer status codes -- CC from td->hwINFO or td->hwPSW
 */
#घोषणा TD_CC_NOERROR      0x00
#घोषणा TD_CC_CRC          0x01
#घोषणा TD_CC_BITSTUFFING  0x02
#घोषणा TD_CC_DATATOGGLEM  0x03
#घोषणा TD_CC_STALL        0x04
#घोषणा TD_DEVNOTRESP      0x05
#घोषणा TD_PIDCHECKFAIL    0x06
#घोषणा TD_UNEXPECTEDPID   0x07
#घोषणा TD_DATAOVERRUN     0x08
#घोषणा TD_DATAUNDERRUN    0x09
    /* 0x0A, 0x0B reserved क्रम hardware */
#घोषणा TD_BUFFEROVERRUN   0x0C
#घोषणा TD_BUFFERUNDERRUN  0x0D
    /* 0x0E, 0x0F reserved क्रम HCD */
#घोषणा TD_NOTACCESSED     0x0F


/* map OHCI TD status codes (CC) to त्रुटि_सं values */
अटल स्थिर पूर्णांक __maybe_unused cc_to_error [16] = अणु
	/* No  Error  */               0,
	/* CRC Error  */               -EILSEQ,
	/* Bit Stuff  */               -EPROTO,
	/* Data Togg  */               -EILSEQ,
	/* Stall      */               -EPIPE,
	/* DevNotResp */               -ETIME,
	/* PIDCheck   */               -EPROTO,
	/* UnExpPID   */               -EPROTO,
	/* DataOver   */               -EOVERFLOW,
	/* DataUnder  */               -EREMOTEIO,
	/* (क्रम hw)   */               -EIO,
	/* (क्रम hw)   */               -EIO,
	/* BufferOver */               -ECOMM,
	/* BuffUnder  */               -ENOSR,
	/* (क्रम HCD)  */               -EALREADY,
	/* (क्रम HCD)  */               -EALREADY
पूर्ण;


/*
 * The HCCA (Host Controller Communications Area) is a 256 byte
 * काष्ठाure defined section 4.4.1 of the OHCI spec. The HC is
 * told the base address of it.  It must be 256-byte aligned.
 */
काष्ठा ohci_hcca अणु
#घोषणा NUM_INTS 32
	__hc32	पूर्णांक_table [NUM_INTS];	/* periodic schedule */

	/*
	 * OHCI defines u16 frame_no, followed by u16 zero pad.
	 * Since some processors can't करो 16 bit bus accesses,
	 * portable access must be a 32 bits wide.
	 */
	__hc32	frame_no;		/* current frame number */
	__hc32	करोne_head;		/* info वापसed क्रम an पूर्णांकerrupt */
	u8	reserved_क्रम_hc [116];
	u8	what [4];		/* spec only identअगरies 252 bytes :) */
पूर्ण __attribute__ ((aligned(256)));

/*
 * This is the काष्ठाure of the OHCI controller's memory mapped I/O region.
 * You must use पढ़ोl() and ग_लिखोl() (in <यंत्र/पन.स>) to access these fields!!
 * Layout is in section 7 (and appendix B) of the spec.
 */
काष्ठा ohci_regs अणु
	/* control and status रेजिस्टरs (section 7.1) */
	__hc32	revision;
	__hc32	control;
	__hc32	cmdstatus;
	__hc32	पूर्णांकrstatus;
	__hc32	पूर्णांकrenable;
	__hc32	पूर्णांकrdisable;

	/* memory poपूर्णांकers (section 7.2) */
	__hc32	hcca;
	__hc32	ed_periodcurrent;
	__hc32	ed_controlhead;
	__hc32	ed_controlcurrent;
	__hc32	ed_bulkhead;
	__hc32	ed_bulkcurrent;
	__hc32	करोnehead;

	/* frame counters (section 7.3) */
	__hc32	fmपूर्णांकerval;
	__hc32	fmreमुख्यing;
	__hc32	fmnumber;
	__hc32	periodicstart;
	__hc32	lsthresh;

	/* Root hub ports (section 7.4) */
	काष्ठा	ohci_roothub_regs अणु
		__hc32	a;
		__hc32	b;
		__hc32	status;
#घोषणा MAX_ROOT_PORTS	15	/* maximum OHCI root hub ports (RH_A_NDP) */
		__hc32	portstatus [MAX_ROOT_PORTS];
	पूर्ण roothub;

	/* and optional "legacy support" रेजिस्टरs (appendix B) at 0x0100 */

पूर्ण __attribute__ ((aligned(32)));


/* OHCI CONTROL AND STATUS REGISTER MASKS */

/*
 * HcControl (control) रेजिस्टर masks
 */
#घोषणा OHCI_CTRL_CBSR	(3 << 0)	/* control/bulk service ratio */
#घोषणा OHCI_CTRL_PLE	(1 << 2)	/* periodic list enable */
#घोषणा OHCI_CTRL_IE	(1 << 3)	/* isochronous enable */
#घोषणा OHCI_CTRL_CLE	(1 << 4)	/* control list enable */
#घोषणा OHCI_CTRL_BLE	(1 << 5)	/* bulk list enable */
#घोषणा OHCI_CTRL_HCFS	(3 << 6)	/* host controller functional state */
#घोषणा OHCI_CTRL_IR	(1 << 8)	/* पूर्णांकerrupt routing */
#घोषणा OHCI_CTRL_RWC	(1 << 9)	/* remote wakeup connected */
#घोषणा OHCI_CTRL_RWE	(1 << 10)	/* remote wakeup enable */

/* pre-shअगरted values क्रम HCFS */
#	define OHCI_USB_RESET	(0 << 6)
#	define OHCI_USB_RESUME	(1 << 6)
#	define OHCI_USB_OPER	(2 << 6)
#	define OHCI_USB_SUSPEND	(3 << 6)

/*
 * HcCommandStatus (cmdstatus) रेजिस्टर masks
 */
#घोषणा OHCI_HCR	(1 << 0)	/* host controller reset */
#घोषणा OHCI_CLF	(1 << 1)	/* control list filled */
#घोषणा OHCI_BLF	(1 << 2)	/* bulk list filled */
#घोषणा OHCI_OCR	(1 << 3)	/* ownership change request */
#घोषणा OHCI_SOC	(3 << 16)	/* scheduling overrun count */

/*
 * masks used with पूर्णांकerrupt रेजिस्टरs:
 * HcInterruptStatus (पूर्णांकrstatus)
 * HcInterruptEnable (पूर्णांकrenable)
 * HcInterruptDisable (पूर्णांकrdisable)
 */
#घोषणा OHCI_INTR_SO	(1 << 0)	/* scheduling overrun */
#घोषणा OHCI_INTR_WDH	(1 << 1)	/* ग_लिखोback of करोne_head */
#घोषणा OHCI_INTR_SF	(1 << 2)	/* start frame */
#घोषणा OHCI_INTR_RD	(1 << 3)	/* resume detect */
#घोषणा OHCI_INTR_UE	(1 << 4)	/* unrecoverable error */
#घोषणा OHCI_INTR_FNO	(1 << 5)	/* frame number overflow */
#घोषणा OHCI_INTR_RHSC	(1 << 6)	/* root hub status change */
#घोषणा OHCI_INTR_OC	(1 << 30)	/* ownership change */
#घोषणा OHCI_INTR_MIE	(1 << 31)	/* master पूर्णांकerrupt enable */


/* OHCI ROOT HUB REGISTER MASKS */

/* roothub.portstatus [i] bits */
#घोषणा RH_PS_CCS            0x00000001		/* current connect status */
#घोषणा RH_PS_PES            0x00000002		/* port enable status*/
#घोषणा RH_PS_PSS            0x00000004		/* port suspend status */
#घोषणा RH_PS_POCI           0x00000008		/* port over current indicator */
#घोषणा RH_PS_PRS            0x00000010		/* port reset status */
#घोषणा RH_PS_PPS            0x00000100		/* port घातer status */
#घोषणा RH_PS_LSDA           0x00000200		/* low speed device attached */
#घोषणा RH_PS_CSC            0x00010000		/* connect status change */
#घोषणा RH_PS_PESC           0x00020000		/* port enable status change */
#घोषणा RH_PS_PSSC           0x00040000		/* port suspend status change */
#घोषणा RH_PS_OCIC           0x00080000		/* over current indicator change */
#घोषणा RH_PS_PRSC           0x00100000		/* port reset status change */

/* roothub.status bits */
#घोषणा RH_HS_LPS	     0x00000001		/* local घातer status */
#घोषणा RH_HS_OCI	     0x00000002		/* over current indicator */
#घोषणा RH_HS_DRWE	     0x00008000		/* device remote wakeup enable */
#घोषणा RH_HS_LPSC	     0x00010000		/* local घातer status change */
#घोषणा RH_HS_OCIC	     0x00020000		/* over current indicator change */
#घोषणा RH_HS_CRWE	     0x80000000		/* clear remote wakeup enable */

/* roothub.b masks */
#घोषणा RH_B_DR		0x0000ffff		/* device removable flags */
#घोषणा RH_B_PPCM	0xffff0000		/* port घातer control mask */

/* roothub.a masks */
#घोषणा	RH_A_NDP	(0xff << 0)		/* number of करोwnstream ports */
#घोषणा	RH_A_PSM	(1 << 8)		/* घातer चयनing mode */
#घोषणा	RH_A_NPS	(1 << 9)		/* no घातer चयनing */
#घोषणा	RH_A_DT		(1 << 10)		/* device type (mbz) */
#घोषणा	RH_A_OCPM	(1 << 11)		/* over current protection mode */
#घोषणा	RH_A_NOCP	(1 << 12)		/* no over current protection */
#घोषणा	RH_A_POTPGT	(0xff << 24)		/* घातer on to घातer good समय */


/* hcd-निजी per-urb state */
प्रकार काष्ठा urb_priv अणु
	काष्ठा ed		*ed;
	u16			length;		// # tds in this request
	u16			td_cnt;		// tds alपढ़ोy serviced
	काष्ठा list_head	pending;
	काष्ठा td		*td[];		// all TDs in this request

पूर्ण urb_priv_t;

#घोषणा TD_HASH_SIZE    64    /* घातer'o'two */
// माप (काष्ठा td) ~= 64 == 2^6 ...
#घोषणा TD_HASH_FUNC(td_dma) ((td_dma ^ (td_dma >> 6)) % TD_HASH_SIZE)


/*
 * This is the full ohci controller description
 *
 * Note how the "proper" USB inक्रमmation is just
 * a subset of what the full implementation needs. (Linus)
 */

क्रमागत ohci_rh_state अणु
	OHCI_RH_HALTED,
	OHCI_RH_SUSPENDED,
	OHCI_RH_RUNNING
पूर्ण;

काष्ठा ohci_hcd अणु
	spinlock_t		lock;

	/*
	 * I/O memory used to communicate with the HC (dma-consistent)
	 */
	काष्ठा ohci_regs __iomem *regs;

	/*
	 * मुख्य memory used to communicate with the HC (dma-consistent).
	 * hcd adds to schedule क्रम a live hc any समय, but removals finish
	 * only at the start of the next frame.
	 */
	काष्ठा ohci_hcca	*hcca;
	dma_addr_t		hcca_dma;

	काष्ठा ed		*ed_rm_list;		/* to be हटाओd */

	काष्ठा ed		*ed_bulktail;		/* last in bulk list */
	काष्ठा ed		*ed_controltail;	/* last in ctrl list */
	काष्ठा ed		*periodic [NUM_INTS];	/* shaकरोw पूर्णांक_table */

	व्योम (*start_hnp)(काष्ठा ohci_hcd *ohci);

	/*
	 * memory management क्रम queue data काष्ठाures
	 *
	 * @td_cache and @ed_cache are %शून्य अगर &usb_hcd.localmem_pool is used.
	 */
	काष्ठा dma_pool		*td_cache;
	काष्ठा dma_pool		*ed_cache;
	काष्ठा td		*td_hash [TD_HASH_SIZE];
	काष्ठा td		*dl_start, *dl_end;	/* the करोne list */
	काष्ठा list_head	pending;
	काष्ठा list_head	eds_in_use;	/* all EDs with at least 1 TD */

	/*
	 * driver state
	 */
	क्रमागत ohci_rh_state	rh_state;
	पूर्णांक			num_ports;
	पूर्णांक			load [NUM_INTS];
	u32			hc_control;	/* copy of hc control reg */
	अचिन्हित दीर्घ		next_statechange;	/* suspend/resume */
	u32			fmपूर्णांकerval;		/* saved रेजिस्टर */
	अचिन्हित		स्वतःstop:1;	/* rh स्वतः stopping/stopped */
	अचिन्हित		working:1;
	अचिन्हित		restart_work:1;

	अचिन्हित दीर्घ		flags;		/* क्रम HC bugs */
#घोषणा	OHCI_QUIRK_AMD756	0x01			/* erratum #4 */
#घोषणा	OHCI_QUIRK_SUPERIO	0x02			/* natsemi */
#घोषणा	OHCI_QUIRK_INITRESET	0x04			/* SiS, OPTi, ... */
#घोषणा	OHCI_QUIRK_BE_DESC	0x08			/* BE descriptors */
#घोषणा	OHCI_QUIRK_BE_MMIO	0x10			/* BE रेजिस्टरs */
#घोषणा	OHCI_QUIRK_ZFMICRO	0x20			/* Compaq ZFMicro chipset*/
#घोषणा	OHCI_QUIRK_NEC		0x40			/* lost पूर्णांकerrupts */
#घोषणा	OHCI_QUIRK_FRAME_NO	0x80			/* no big endian frame_no shअगरt */
#घोषणा	OHCI_QUIRK_HUB_POWER	0x100			/* distrust firmware घातer/oc setup */
#घोषणा	OHCI_QUIRK_AMD_PLL	0x200			/* AMD PLL quirk*/
#घोषणा	OHCI_QUIRK_AMD_PREFETCH	0x400			/* pre-fetch क्रम ISO transfer */
#घोषणा	OHCI_QUIRK_GLOBAL_SUSPEND	0x800		/* must suspend ports */
#घोषणा	OHCI_QUIRK_QEMU		0x1000			/* relax timing expectations */

	// there are also chip quirks/bugs in init logic

	अचिन्हित		prev_frame_no;
	अचिन्हित		wdh_cnt, prev_wdh_cnt;
	u32			prev_करोnehead;
	काष्ठा समयr_list	io_watchकरोg;

	काष्ठा work_काष्ठा	nec_work;	/* Worker क्रम NEC quirk */

	काष्ठा dentry		*debug_dir;

	/* platक्रमm-specअगरic data -- must come last */
	अचिन्हित दीर्घ           priv[] __aligned(माप(s64));

पूर्ण;

#अगर_घोषित CONFIG_USB_PCI
अटल अंतरभूत पूर्णांक quirk_nec(काष्ठा ohci_hcd *ohci)
अणु
	वापस ohci->flags & OHCI_QUIRK_NEC;
पूर्ण
अटल अंतरभूत पूर्णांक quirk_zfmicro(काष्ठा ohci_hcd *ohci)
अणु
	वापस ohci->flags & OHCI_QUIRK_ZFMICRO;
पूर्ण
अटल अंतरभूत पूर्णांक quirk_amdiso(काष्ठा ohci_hcd *ohci)
अणु
	वापस ohci->flags & OHCI_QUIRK_AMD_PLL;
पूर्ण
अटल अंतरभूत पूर्णांक quirk_amdprefetch(काष्ठा ohci_hcd *ohci)
अणु
	वापस ohci->flags & OHCI_QUIRK_AMD_PREFETCH;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक quirk_nec(काष्ठा ohci_hcd *ohci)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक quirk_zfmicro(काष्ठा ohci_hcd *ohci)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक quirk_amdiso(काष्ठा ohci_hcd *ohci)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक quirk_amdprefetch(काष्ठा ohci_hcd *ohci)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/* convert between an hcd poपूर्णांकer and the corresponding ohci_hcd */
अटल अंतरभूत काष्ठा ohci_hcd *hcd_to_ohci (काष्ठा usb_hcd *hcd)
अणु
	वापस (काष्ठा ohci_hcd *) (hcd->hcd_priv);
पूर्ण
अटल अंतरभूत काष्ठा usb_hcd *ohci_to_hcd (स्थिर काष्ठा ohci_hcd *ohci)
अणु
	वापस container_of ((व्योम *) ohci, काष्ठा usb_hcd, hcd_priv);
पूर्ण

/*-------------------------------------------------------------------------*/

#घोषणा ohci_dbg(ohci, fmt, args...) \
	dev_dbg (ohci_to_hcd(ohci)->self.controller , fmt , ## args )
#घोषणा ohci_err(ohci, fmt, args...) \
	dev_err (ohci_to_hcd(ohci)->self.controller , fmt , ## args )
#घोषणा ohci_info(ohci, fmt, args...) \
	dev_info (ohci_to_hcd(ohci)->self.controller , fmt , ## args )
#घोषणा ohci_warn(ohci, fmt, args...) \
	dev_warn (ohci_to_hcd(ohci)->self.controller , fmt , ## args )

/*-------------------------------------------------------------------------*/

/*
 * While most USB host controllers implement their रेजिस्टरs and
 * in-memory communication descriptors in little-endian क्रमmat,
 * a minority (notably the IBM STB04XXX and the Motorola MPC5200
 * processors) implement them in big endian क्रमmat.
 *
 * In addition some more exotic implementations like the Toshiba
 * Spider (aka SCC) cell southbridge are "mixed" endian, that is,
 * they have a dअगरferent endianness क्रम रेजिस्टरs vs. in-memory
 * descriptors.
 *
 * This attempts to support either क्रमmat at compile समय without a
 * runसमय penalty, or both क्रमmats with the additional overhead
 * of checking a flag bit.
 *
 * That leads to some tricky Kconfig rules howevber. There are
 * dअगरferent शेषs based on some arch/ppc platक्रमms, though
 * the basic rules are:
 *
 * Controller type              Kconfig options needed
 * ---------------              ----------------------
 * little endian                CONFIG_USB_OHCI_LITTLE_ENDIAN
 *
 * fully big endian             CONFIG_USB_OHCI_BIG_ENDIAN_DESC _and_
 *                              CONFIG_USB_OHCI_BIG_ENDIAN_MMIO
 *
 * mixed endian                 CONFIG_USB_OHCI_LITTLE_ENDIAN _and_
 *                              CONFIG_USB_OHCI_BIG_ENDIAN_अणुMMIO,DESCपूर्ण
 *
 * (If you have a mixed endian controller, you -must- also define
 * CONFIG_USB_OHCI_LITTLE_ENDIAN or things will not work when building
 * both your mixed endian and a fully big endian controller support in
 * the same kernel image).
 */

#अगर_घोषित CONFIG_USB_OHCI_BIG_ENDIAN_DESC
#अगर_घोषित CONFIG_USB_OHCI_LITTLE_ENDIAN
#घोषणा big_endian_desc(ohci)	(ohci->flags & OHCI_QUIRK_BE_DESC)
#अन्यथा
#घोषणा big_endian_desc(ohci)	1		/* only big endian */
#पूर्ण_अगर
#अन्यथा
#घोषणा big_endian_desc(ohci)	0		/* only little endian */
#पूर्ण_अगर

#अगर_घोषित CONFIG_USB_OHCI_BIG_ENDIAN_MMIO
#अगर_घोषित CONFIG_USB_OHCI_LITTLE_ENDIAN
#घोषणा big_endian_mmio(ohci)	(ohci->flags & OHCI_QUIRK_BE_MMIO)
#अन्यथा
#घोषणा big_endian_mmio(ohci)	1		/* only big endian */
#पूर्ण_अगर
#अन्यथा
#घोषणा big_endian_mmio(ohci)	0		/* only little endian */
#पूर्ण_अगर

/*
 * Big-endian पढ़ो/ग_लिखो functions are arch-specअगरic.
 * Other arches can be added अगर/when they're needed.
 *
 */
अटल अंतरभूत अचिन्हित पूर्णांक _ohci_पढ़ोl (स्थिर काष्ठा ohci_hcd *ohci,
					__hc32 __iomem * regs)
अणु
#अगर_घोषित CONFIG_USB_OHCI_BIG_ENDIAN_MMIO
	वापस big_endian_mmio(ohci) ?
		पढ़ोl_be (regs) :
		पढ़ोl (regs);
#अन्यथा
	वापस पढ़ोl (regs);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम _ohci_ग_लिखोl (स्थिर काष्ठा ohci_hcd *ohci,
				 स्थिर अचिन्हित पूर्णांक val, __hc32 __iomem *regs)
अणु
#अगर_घोषित CONFIG_USB_OHCI_BIG_ENDIAN_MMIO
	big_endian_mmio(ohci) ?
		ग_लिखोl_be (val, regs) :
		ग_लिखोl (val, regs);
#अन्यथा
		ग_लिखोl (val, regs);
#पूर्ण_अगर
पूर्ण

#घोषणा ohci_पढ़ोl(o,r)		_ohci_पढ़ोl(o,r)
#घोषणा ohci_ग_लिखोl(o,v,r)	_ohci_ग_लिखोl(o,v,r)


/*-------------------------------------------------------------------------*/

/* cpu to ohci */
अटल अंतरभूत __hc16 cpu_to_hc16 (स्थिर काष्ठा ohci_hcd *ohci, स्थिर u16 x)
अणु
	वापस big_endian_desc(ohci) ?
		(__क्रमce __hc16)cpu_to_be16(x) :
		(__क्रमce __hc16)cpu_to_le16(x);
पूर्ण

अटल अंतरभूत __hc16 cpu_to_hc16p (स्थिर काष्ठा ohci_hcd *ohci, स्थिर u16 *x)
अणु
	वापस big_endian_desc(ohci) ?
		cpu_to_be16p(x) :
		cpu_to_le16p(x);
पूर्ण

अटल अंतरभूत __hc32 cpu_to_hc32 (स्थिर काष्ठा ohci_hcd *ohci, स्थिर u32 x)
अणु
	वापस big_endian_desc(ohci) ?
		(__क्रमce __hc32)cpu_to_be32(x) :
		(__क्रमce __hc32)cpu_to_le32(x);
पूर्ण

अटल अंतरभूत __hc32 cpu_to_hc32p (स्थिर काष्ठा ohci_hcd *ohci, स्थिर u32 *x)
अणु
	वापस big_endian_desc(ohci) ?
		cpu_to_be32p(x) :
		cpu_to_le32p(x);
पूर्ण

/* ohci to cpu */
अटल अंतरभूत u16 hc16_to_cpu (स्थिर काष्ठा ohci_hcd *ohci, स्थिर __hc16 x)
अणु
	वापस big_endian_desc(ohci) ?
		be16_to_cpu((__क्रमce __be16)x) :
		le16_to_cpu((__क्रमce __le16)x);
पूर्ण

अटल अंतरभूत u16 hc16_to_cpup (स्थिर काष्ठा ohci_hcd *ohci, स्थिर __hc16 *x)
अणु
	वापस big_endian_desc(ohci) ?
		be16_to_cpup((__क्रमce __be16 *)x) :
		le16_to_cpup((__क्रमce __le16 *)x);
पूर्ण

अटल अंतरभूत u32 hc32_to_cpu (स्थिर काष्ठा ohci_hcd *ohci, स्थिर __hc32 x)
अणु
	वापस big_endian_desc(ohci) ?
		be32_to_cpu((__क्रमce __be32)x) :
		le32_to_cpu((__क्रमce __le32)x);
पूर्ण

अटल अंतरभूत u32 hc32_to_cpup (स्थिर काष्ठा ohci_hcd *ohci, स्थिर __hc32 *x)
अणु
	वापस big_endian_desc(ohci) ?
		be32_to_cpup((__क्रमce __be32 *)x) :
		le32_to_cpup((__क्रमce __le32 *)x);
पूर्ण

/*-------------------------------------------------------------------------*/

/*
 * The HCCA frame number is 16 bits, but is accessed as 32 bits since not all
 * hardware handles 16 bit पढ़ोs.  Depending on the SoC implementation, the
 * frame number can wind up in either bits [31:16] (शेष) or
 * [15:0] (OHCI_QUIRK_FRAME_NO) on big endian hosts.
 *
 * Somewhat similarly, the 16-bit PSW fields in a transfer descriptor are
 * reordered on BE.
 */

अटल अंतरभूत u16 ohci_frame_no(स्थिर काष्ठा ohci_hcd *ohci)
अणु
	u32 पंचांगp;
	अगर (big_endian_desc(ohci)) अणु
		पंचांगp = be32_to_cpup((__क्रमce __be32 *)&ohci->hcca->frame_no);
		अगर (!(ohci->flags & OHCI_QUIRK_FRAME_NO))
			पंचांगp >>= 16;
	पूर्ण अन्यथा
		पंचांगp = le32_to_cpup((__क्रमce __le32 *)&ohci->hcca->frame_no);

	वापस (u16)पंचांगp;
पूर्ण

अटल अंतरभूत __hc16 *ohci_hwPSWp(स्थिर काष्ठा ohci_hcd *ohci,
                                 स्थिर काष्ठा td *td, पूर्णांक index)
अणु
	वापस (__hc16 *)(big_endian_desc(ohci) ?
			&td->hwPSW[index ^ 1] : &td->hwPSW[index]);
पूर्ण

अटल अंतरभूत u16 ohci_hwPSW(स्थिर काष्ठा ohci_hcd *ohci,
                               स्थिर काष्ठा td *td, पूर्णांक index)
अणु
	वापस hc16_to_cpup(ohci, ohci_hwPSWp(ohci, td, index));
पूर्ण

/*-------------------------------------------------------------------------*/

#घोषणा	FI			0x2edf		/* 12000 bits per frame (-1) */
#घोषणा	FSMP(fi)		(0x7fff & ((6 * ((fi) - 210)) / 7))
#घोषणा	FIT			(1 << 31)
#घोषणा LSTHRESH		0x628		/* lowspeed bit threshold */

अटल अंतरभूत व्योम periodic_reinit (काष्ठा ohci_hcd *ohci)
अणु
	u32	fi = ohci->fmपूर्णांकerval & 0x03fff;
	u32	fit = ohci_पढ़ोl(ohci, &ohci->regs->fmपूर्णांकerval) & FIT;

	ohci_ग_लिखोl (ohci, (fit ^ FIT) | ohci->fmपूर्णांकerval,
						&ohci->regs->fmपूर्णांकerval);
	ohci_ग_लिखोl (ohci, ((9 * fi) / 10) & 0x3fff,
						&ohci->regs->periodicstart);
पूर्ण

/* AMD-756 (D2 rev) reports corrupt रेजिस्टर contents in some हालs.
 * The erratum (#4) description is incorrect.  AMD's workaround रुकोs
 * till some bits (mostly reserved) are clear; ok क्रम all revs.
 */
#घोषणा पढ़ो_roothub(hc, रेजिस्टर, mask) (अणु \
	u32 temp = ohci_पढ़ोl (hc, &hc->regs->roothub.रेजिस्टर); \
	अगर (temp == -1) \
		hc->rh_state = OHCI_RH_HALTED; \
	अन्यथा अगर (hc->flags & OHCI_QUIRK_AMD756) \
		जबतक (temp & mask) \
			temp = ohci_पढ़ोl (hc, &hc->regs->roothub.रेजिस्टर); \
	temp; पूर्ण)

अटल अंतरभूत u32 roothub_a (काष्ठा ohci_hcd *hc)
	अणु वापस पढ़ो_roothub (hc, a, 0xfc0fe000); पूर्ण
अटल अंतरभूत u32 roothub_b (काष्ठा ohci_hcd *hc)
	अणु वापस ohci_पढ़ोl (hc, &hc->regs->roothub.b); पूर्ण
अटल अंतरभूत u32 roothub_status (काष्ठा ohci_hcd *hc)
	अणु वापस ohci_पढ़ोl (hc, &hc->regs->roothub.status); पूर्ण
अटल अंतरभूत u32 roothub_portstatus (काष्ठा ohci_hcd *hc, पूर्णांक i)
	अणु वापस पढ़ो_roothub (hc, portstatus [i], 0xffe0fce0); पूर्ण

/* Declarations of things exported क्रम use by ohci platक्रमm drivers */

काष्ठा ohci_driver_overrides अणु
	स्थिर अक्षर	*product_desc;
	माप_प्रकार		extra_priv_size;
	पूर्णांक		(*reset)(काष्ठा usb_hcd *hcd);
पूर्ण;

बाह्य व्योम	ohci_init_driver(काष्ठा hc_driver *drv,
				स्थिर काष्ठा ohci_driver_overrides *over);
बाह्य पूर्णांक	ohci_restart(काष्ठा ohci_hcd *ohci);
बाह्य पूर्णांक	ohci_setup(काष्ठा usb_hcd *hcd);
बाह्य पूर्णांक	ohci_suspend(काष्ठा usb_hcd *hcd, bool करो_wakeup);
बाह्य पूर्णांक	ohci_resume(काष्ठा usb_hcd *hcd, bool hibernated);
बाह्य पूर्णांक	ohci_hub_control(काष्ठा usb_hcd	*hcd, u16 typeReq, u16 wValue,
				 u16 wIndex, अक्षर *buf, u16 wLength);
बाह्य पूर्णांक	ohci_hub_status_data(काष्ठा usb_hcd *hcd, अक्षर *buf);
