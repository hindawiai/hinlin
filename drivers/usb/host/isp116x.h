<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * ISP116x रेजिस्टर declarations and HCD data काष्ठाures
 *
 * Copyright (C) 2005 Olav Kongas <ok@artecdesign.ee>
 * Portions:
 * Copyright (C) 2004 Lothar Wassmann
 * Copyright (C) 2004 Psion Teklogix
 * Copyright (C) 2004 David Brownell
 */

/* us of 1ms frame */
#घोषणा  MAX_LOAD_LIMIT		850

/* Full speed: max # of bytes to transfer क्रम a single urb
   at a समय must be < 1024 && must be multiple of 64.
   832 allows transferring 4kiB within 5 frames. */
#घोषणा MAX_TRANSFER_SIZE_FULLSPEED	832

/* Low speed: there is no reason to schedule in very big
   chunks; often the requested दीर्घ transfers are क्रम
   string descriptors containing लघु strings. */
#घोषणा MAX_TRANSFER_SIZE_LOWSPEED	64

/* Byteसमय (us), a rough indication of how much समय it
   would take to transfer a byte of useful data over USB */
#घोषणा BYTE_TIME_FULLSPEED	1
#घोषणा BYTE_TIME_LOWSPEED	20

/* Buffer sizes */
#घोषणा ISP116x_BUF_SIZE	4096
#घोषणा ISP116x_ITL_बफ_मानE	0
#घोषणा ISP116x_ATL_बफ_मानE	((ISP116x_BUF_SIZE) - 2*(ISP116x_ITL_बफ_मानE))

#घोषणा ISP116x_WRITE_OFFSET	0x80

/*------------ ISP116x रेजिस्टरs/bits ------------*/
#घोषणा	HCREVISION	0x00
#घोषणा	HCCONTROL	0x01
#घोषणा		HCCONTROL_HCFS	(3 << 6)	/* host controller
						   functional state */
#घोषणा		HCCONTROL_USB_RESET	(0 << 6)
#घोषणा		HCCONTROL_USB_RESUME	(1 << 6)
#घोषणा		HCCONTROL_USB_OPER	(2 << 6)
#घोषणा		HCCONTROL_USB_SUSPEND	(3 << 6)
#घोषणा		HCCONTROL_RWC	(1 << 9)	/* remote wakeup connected */
#घोषणा		HCCONTROL_RWE	(1 << 10)	/* remote wakeup enable */
#घोषणा	HCCMDSTAT	0x02
#घोषणा		HCCMDSTAT_HCR	(1 << 0)	/* host controller reset */
#घोषणा		HCCMDSTAT_SOC	(3 << 16)	/* scheduling overrun count */
#घोषणा	HCINTSTAT	0x03
#घोषणा		HCINT_SO	(1 << 0)	/* scheduling overrun */
#घोषणा		HCINT_WDH	(1 << 1)	/* ग_लिखोback of करोne_head */
#घोषणा		HCINT_SF	(1 << 2)	/* start frame */
#घोषणा		HCINT_RD	(1 << 3)	/* resume detect */
#घोषणा		HCINT_UE	(1 << 4)	/* unrecoverable error */
#घोषणा		HCINT_FNO	(1 << 5)	/* frame number overflow */
#घोषणा		HCINT_RHSC	(1 << 6)	/* root hub status change */
#घोषणा		HCINT_OC	(1 << 30)	/* ownership change */
#घोषणा		HCINT_MIE	(1 << 31)	/* master पूर्णांकerrupt enable */
#घोषणा	HCINTENB	0x04
#घोषणा	HCINTDIS	0x05
#घोषणा	HCFMINTVL	0x0d
#घोषणा	HCFMREM		0x0e
#घोषणा	HCFMNUM		0x0f
#घोषणा	HCLSTHRESH	0x11
#घोषणा	HCRHDESCA	0x12
#घोषणा		RH_A_NDP	(0x3 << 0)	/* # करोwnstream ports */
#घोषणा		RH_A_PSM	(1 << 8)	/* घातer चयनing mode */
#घोषणा		RH_A_NPS	(1 << 9)	/* no घातer चयनing */
#घोषणा		RH_A_DT		(1 << 10)	/* device type (mbz) */
#घोषणा		RH_A_OCPM	(1 << 11)	/* overcurrent protection
						   mode */
#घोषणा		RH_A_NOCP	(1 << 12)	/* no overcurrent protection */
#घोषणा		RH_A_POTPGT	(0xff << 24)	/* घातer on -> घातer good
						   समय */
#घोषणा	HCRHDESCB	0x13
#घोषणा		RH_B_DR		(0xffff << 0)	/* device removable flags */
#घोषणा		RH_B_PPCM	(0xffff << 16)	/* port घातer control mask */
#घोषणा	HCRHSTATUS	0x14
#घोषणा		RH_HS_LPS	(1 << 0)	/* local घातer status */
#घोषणा		RH_HS_OCI	(1 << 1)	/* over current indicator */
#घोषणा		RH_HS_DRWE	(1 << 15)	/* device remote wakeup
						   enable */
#घोषणा		RH_HS_LPSC	(1 << 16)	/* local घातer status change */
#घोषणा		RH_HS_OCIC	(1 << 17)	/* over current indicator
						   change */
#घोषणा		RH_HS_CRWE	(1 << 31)	/* clear remote wakeup
						   enable */
#घोषणा	HCRHPORT1	0x15
#घोषणा		RH_PS_CCS	(1 << 0)	/* current connect status */
#घोषणा		RH_PS_PES	(1 << 1)	/* port enable status */
#घोषणा		RH_PS_PSS	(1 << 2)	/* port suspend status */
#घोषणा		RH_PS_POCI	(1 << 3)	/* port over current
						   indicator */
#घोषणा		RH_PS_PRS	(1 << 4)	/* port reset status */
#घोषणा		RH_PS_PPS	(1 << 8)	/* port घातer status */
#घोषणा		RH_PS_LSDA	(1 << 9)	/* low speed device attached */
#घोषणा		RH_PS_CSC	(1 << 16)	/* connect status change */
#घोषणा		RH_PS_PESC	(1 << 17)	/* port enable status change */
#घोषणा		RH_PS_PSSC	(1 << 18)	/* port suspend status
						   change */
#घोषणा		RH_PS_OCIC	(1 << 19)	/* over current indicator
						   change */
#घोषणा		RH_PS_PRSC	(1 << 20)	/* port reset status change */
#घोषणा		HCRHPORT_CLRMASK	(0x1f << 16)
#घोषणा	HCRHPORT2	0x16
#घोषणा	HCHWCFG		0x20
#घोषणा		HCHWCFG_15KRSEL		(1 << 12)
#घोषणा		HCHWCFG_CLKNOTSTOP	(1 << 11)
#घोषणा		HCHWCFG_ANALOG_OC	(1 << 10)
#घोषणा		HCHWCFG_DACK_MODE	(1 << 8)
#घोषणा		HCHWCFG_EOT_POL		(1 << 7)
#घोषणा		HCHWCFG_DACK_POL	(1 << 6)
#घोषणा		HCHWCFG_DREQ_POL	(1 << 5)
#घोषणा		HCHWCFG_DBWIDTH_MASK	(0x03 << 3)
#घोषणा		HCHWCFG_DBWIDTH(n)	(((n) << 3) & HCHWCFG_DBWIDTH_MASK)
#घोषणा		HCHWCFG_INT_POL		(1 << 2)
#घोषणा		HCHWCFG_INT_TRIGGER	(1 << 1)
#घोषणा		HCHWCFG_INT_ENABLE	(1 << 0)
#घोषणा	HCDMACFG	0x21
#घोषणा		HCDMACFG_BURST_LEN_MASK	(0x03 << 5)
#घोषणा		HCDMACFG_BURST_LEN(n)	(((n) << 5) & HCDMACFG_BURST_LEN_MASK)
#घोषणा		HCDMACFG_BURST_LEN_1	HCDMACFG_BURST_LEN(0)
#घोषणा		HCDMACFG_BURST_LEN_4	HCDMACFG_BURST_LEN(1)
#घोषणा		HCDMACFG_BURST_LEN_8	HCDMACFG_BURST_LEN(2)
#घोषणा		HCDMACFG_DMA_ENABLE	(1 << 4)
#घोषणा		HCDMACFG_BUF_TYPE_MASK	(0x07 << 1)
#घोषणा		HCDMACFG_CTR_SEL	(1 << 2)
#घोषणा		HCDMACFG_ITLATL_SEL	(1 << 1)
#घोषणा		HCDMACFG_DMA_RW_SELECT	(1 << 0)
#घोषणा	HCXFERCTR	0x22
#घोषणा	HCuPINT		0x24
#घोषणा		HCuPINT_SOF		(1 << 0)
#घोषणा		HCuPINT_ATL		(1 << 1)
#घोषणा		HCuPINT_AIIEOT		(1 << 2)
#घोषणा		HCuPINT_OPR		(1 << 4)
#घोषणा		HCuPINT_SUSP		(1 << 5)
#घोषणा		HCuPINT_CLKRDY		(1 << 6)
#घोषणा	HCuPINTENB	0x25
#घोषणा	HCCHIPID	0x27
#घोषणा		HCCHIPID_MASK		0xff00
#घोषणा		HCCHIPID_MAGIC		0x6100
#घोषणा	HCSCRATCH	0x28
#घोषणा	HCSWRES		0x29
#घोषणा		HCSWRES_MAGIC		0x00f6
#घोषणा	HCITLBUFLEN	0x2a
#घोषणा	HCATLBUFLEN	0x2b
#घोषणा	HCBUFSTAT	0x2c
#घोषणा		HCBUFSTAT_ITL0_FULL	(1 << 0)
#घोषणा		HCBUFSTAT_ITL1_FULL	(1 << 1)
#घोषणा		HCBUFSTAT_ATL_FULL	(1 << 2)
#घोषणा		HCBUFSTAT_ITL0_DONE	(1 << 3)
#घोषणा		HCBUFSTAT_ITL1_DONE	(1 << 4)
#घोषणा		HCBUFSTAT_ATL_DONE	(1 << 5)
#घोषणा	HCRDITL0LEN	0x2d
#घोषणा	HCRDITL1LEN	0x2e
#घोषणा	HCITLPORT	0x40
#घोषणा	HCATLPORT	0x41

/* Philips transfer descriptor */
काष्ठा ptd अणु
	u16 count;
#घोषणा	PTD_COUNT_MSK	(0x3ff << 0)
#घोषणा	PTD_TOGGLE_MSK	(1 << 10)
#घोषणा	PTD_ACTIVE_MSK	(1 << 11)
#घोषणा	PTD_CC_MSK	(0xf << 12)
	u16 mps;
#घोषणा	PTD_MPS_MSK	(0x3ff << 0)
#घोषणा	PTD_SPD_MSK	(1 << 10)
#घोषणा	PTD_LAST_MSK	(1 << 11)
#घोषणा	PTD_EP_MSK	(0xf << 12)
	u16 len;
#घोषणा	PTD_LEN_MSK	(0x3ff << 0)
#घोषणा	PTD_सूची_MSK	(3 << 10)
#घोषणा	PTD_सूची_SETUP	(0)
#घोषणा	PTD_सूची_OUT	(1)
#घोषणा	PTD_सूची_IN	(2)
#घोषणा	PTD_B5_5_MSK	(1 << 13)
	u16 faddr;
#घोषणा	PTD_FA_MSK	(0x7f << 0)
#घोषणा	PTD_FMT_MSK	(1 << 7)
पूर्ण __attribute__ ((packed, aligned(2)));

/* PTD accessor macros. */
#घोषणा PTD_GET_COUNT(p)	(((p)->count & PTD_COUNT_MSK) >> 0)
#घोषणा PTD_COUNT(v)		(((v) << 0) & PTD_COUNT_MSK)
#घोषणा PTD_GET_TOGGLE(p)	(((p)->count & PTD_TOGGLE_MSK) >> 10)
#घोषणा PTD_TOGGLE(v)		(((v) << 10) & PTD_TOGGLE_MSK)
#घोषणा PTD_GET_ACTIVE(p)	(((p)->count & PTD_ACTIVE_MSK) >> 11)
#घोषणा PTD_ACTIVE(v)		(((v) << 11) & PTD_ACTIVE_MSK)
#घोषणा PTD_GET_CC(p)		(((p)->count & PTD_CC_MSK) >> 12)
#घोषणा PTD_CC(v)		(((v) << 12) & PTD_CC_MSK)
#घोषणा PTD_GET_MPS(p)		(((p)->mps & PTD_MPS_MSK) >> 0)
#घोषणा PTD_MPS(v)		(((v) << 0) & PTD_MPS_MSK)
#घोषणा PTD_GET_SPD(p)		(((p)->mps & PTD_SPD_MSK) >> 10)
#घोषणा PTD_SPD(v)		(((v) << 10) & PTD_SPD_MSK)
#घोषणा PTD_GET_LAST(p)		(((p)->mps & PTD_LAST_MSK) >> 11)
#घोषणा PTD_LAST(v)		(((v) << 11) & PTD_LAST_MSK)
#घोषणा PTD_GET_EP(p)		(((p)->mps & PTD_EP_MSK) >> 12)
#घोषणा PTD_EP(v)		(((v) << 12) & PTD_EP_MSK)
#घोषणा PTD_GET_LEN(p)		(((p)->len & PTD_LEN_MSK) >> 0)
#घोषणा PTD_LEN(v)		(((v) << 0) & PTD_LEN_MSK)
#घोषणा PTD_GET_सूची(p)		(((p)->len & PTD_सूची_MSK) >> 10)
#घोषणा PTD_सूची(v)		(((v) << 10) & PTD_सूची_MSK)
#घोषणा PTD_GET_B5_5(p)		(((p)->len & PTD_B5_5_MSK) >> 13)
#घोषणा PTD_B5_5(v)		(((v) << 13) & PTD_B5_5_MSK)
#घोषणा PTD_GET_FA(p)		(((p)->faddr & PTD_FA_MSK) >> 0)
#घोषणा PTD_FA(v)		(((v) << 0) & PTD_FA_MSK)
#घोषणा PTD_GET_FMT(p)		(((p)->faddr & PTD_FMT_MSK) >> 7)
#घोषणा PTD_FMT(v)		(((v) << 7) & PTD_FMT_MSK)

/*  Hardware transfer status codes -- CC from ptd->count */
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

/* map PTD status codes (CC) to त्रुटि_सं values */
अटल स्थिर पूर्णांक cc_to_error[16] = अणु
	/* No  Error  */ 0,
	/* CRC Error  */ -EILSEQ,
	/* Bit Stuff  */ -EPROTO,
	/* Data Togg  */ -EILSEQ,
	/* Stall      */ -EPIPE,
	/* DevNotResp */ -ETIME,
	/* PIDCheck   */ -EPROTO,
	/* UnExpPID   */ -EPROTO,
	/* DataOver   */ -EOVERFLOW,
	/* DataUnder  */ -EREMOTEIO,
	/* (क्रम hw)   */ -EIO,
	/* (क्रम hw)   */ -EIO,
	/* BufferOver */ -ECOMM,
	/* BuffUnder  */ -ENOSR,
	/* (क्रम HCD)  */ -EALREADY,
	/* (क्रम HCD)  */ -EALREADY
पूर्ण;

/*--------------------------------------------------------------*/

#घोषणा	LOG2_PERIODIC_SIZE	5	/* arbitrary; this matches OHCI */
#घोषणा	PERIODIC_SIZE		(1 << LOG2_PERIODIC_SIZE)

काष्ठा isp116x अणु
	spinlock_t lock;

	व्योम __iomem *addr_reg;
	व्योम __iomem *data_reg;

	काष्ठा isp116x_platक्रमm_data *board;

	अचिन्हित दीर्घ stat1, stat2, stat4, stat8, stat16;

	/* HC रेजिस्टरs */
	u32 पूर्णांकenb;		/* "OHCI" पूर्णांकerrupts */
	u16 irqenb;		/* uP पूर्णांकerrupts */

	/* Root hub रेजिस्टरs */
	u32 rhdesca;
	u32 rhdescb;
	u32 rhstatus;

	/* async schedule: control, bulk */
	काष्ठा list_head async;

	/* periodic schedule: पूर्णांक */
	u16 load[PERIODIC_SIZE];
	काष्ठा isp116x_ep *periodic[PERIODIC_SIZE];
	अचिन्हित periodic_count;
	u16 fmindex;

	/* Schedule क्रम the current frame */
	काष्ठा isp116x_ep *atl_active;
	पूर्णांक atl_buflen;
	पूर्णांक atl_bufshrt;
	पूर्णांक atl_last_dir;
	atomic_t atl_finishing;
पूर्ण;

अटल अंतरभूत काष्ठा isp116x *hcd_to_isp116x(काष्ठा usb_hcd *hcd)
अणु
	वापस (काष्ठा isp116x *)(hcd->hcd_priv);
पूर्ण

अटल अंतरभूत काष्ठा usb_hcd *isp116x_to_hcd(काष्ठा isp116x *isp116x)
अणु
	वापस container_of((व्योम *)isp116x, काष्ठा usb_hcd, hcd_priv);
पूर्ण

काष्ठा isp116x_ep अणु
	काष्ठा usb_host_endpoपूर्णांक *hep;
	काष्ठा usb_device *udev;
	काष्ठा ptd ptd;

	u8 maxpacket;
	u8 epnum;
	u8 nextpid;
	u16 error_count;
	u16 length;		/* of current packet */
	अचिन्हित अक्षर *data;	/* to databuf */
	/* queue of active EP's (the ones scheduled क्रम the
	   current frame) */
	काष्ठा isp116x_ep *active;

	/* periodic schedule */
	u16 period;
	u16 branch;
	u16 load;
	काष्ठा isp116x_ep *next;

	/* async schedule */
	काष्ठा list_head schedule;
पूर्ण;

/*-------------------------------------------------------------------------*/

#घोषणा DBG(stuff...)		pr_debug("116x: " stuff)

#अगर_घोषित VERBOSE
#    define VDBG		DBG
#अन्यथा
#    define VDBG(stuff...)	करोअणुपूर्णजबतक(0)
#पूर्ण_अगर

#घोषणा ERR(stuff...)		prपूर्णांकk(KERN_ERR "116x: " stuff)
#घोषणा WARNING(stuff...)	prपूर्णांकk(KERN_WARNING "116x: " stuff)
#घोषणा INFO(stuff...)		prपूर्णांकk(KERN_INFO "116x: " stuff)

/* ------------------------------------------------- */

#अगर defined(USE_PLATFORM_DELAY)
#अगर defined(USE_NDELAY)
#त्रुटि USE_PLATFORM_DELAY and USE_NDELAY simultaneously defined.
#पूर्ण_अगर
#घोषणा	isp116x_delay(h,d)	(h)->board->delay(	\
				isp116x_to_hcd(h)->self.controller,d)
#घोषणा isp116x_check_platक्रमm_delay(h)	((h)->board->delay == शून्य)
#या_अगर defined(USE_NDELAY)
#घोषणा	isp116x_delay(h,d)	ndelay(d)
#घोषणा isp116x_check_platक्रमm_delay(h)	0
#अन्यथा
#घोषणा	isp116x_delay(h,d)	करोअणुपूर्णजबतक(0)
#घोषणा isp116x_check_platक्रमm_delay(h)	0
#पूर्ण_अगर

अटल अंतरभूत व्योम isp116x_ग_लिखो_addr(काष्ठा isp116x *isp116x, अचिन्हित reg)
अणु
	ग_लिखोw(reg & 0xff, isp116x->addr_reg);
	isp116x_delay(isp116x, 300);
पूर्ण

अटल अंतरभूत व्योम isp116x_ग_लिखो_data16(काष्ठा isp116x *isp116x, u16 val)
अणु
	ग_लिखोw(val, isp116x->data_reg);
	isp116x_delay(isp116x, 150);
पूर्ण

अटल अंतरभूत व्योम isp116x_raw_ग_लिखो_data16(काष्ठा isp116x *isp116x, u16 val)
अणु
	__raw_ग_लिखोw(val, isp116x->data_reg);
	isp116x_delay(isp116x, 150);
पूर्ण

अटल अंतरभूत u16 isp116x_पढ़ो_data16(काष्ठा isp116x *isp116x)
अणु
	u16 val;

	val = पढ़ोw(isp116x->data_reg);
	isp116x_delay(isp116x, 150);
	वापस val;
पूर्ण

अटल अंतरभूत u16 isp116x_raw_पढ़ो_data16(काष्ठा isp116x *isp116x)
अणु
	u16 val;

	val = __raw_पढ़ोw(isp116x->data_reg);
	isp116x_delay(isp116x, 150);
	वापस val;
पूर्ण

अटल अंतरभूत व्योम isp116x_ग_लिखो_data32(काष्ठा isp116x *isp116x, u32 val)
अणु
	ग_लिखोw(val & 0xffff, isp116x->data_reg);
	isp116x_delay(isp116x, 150);
	ग_लिखोw(val >> 16, isp116x->data_reg);
	isp116x_delay(isp116x, 150);
पूर्ण

अटल अंतरभूत u32 isp116x_पढ़ो_data32(काष्ठा isp116x *isp116x)
अणु
	u32 val;

	val = (u32) पढ़ोw(isp116x->data_reg);
	isp116x_delay(isp116x, 150);
	val |= ((u32) पढ़ोw(isp116x->data_reg)) << 16;
	isp116x_delay(isp116x, 150);
	वापस val;
पूर्ण

/* Let's keep रेजिस्टर access functions out of line. Hपूर्णांक:
   we रुको at least 150 ns at every access.
*/
अटल u16 isp116x_पढ़ो_reg16(काष्ठा isp116x *isp116x, अचिन्हित reg)
अणु
	isp116x_ग_लिखो_addr(isp116x, reg);
	वापस isp116x_पढ़ो_data16(isp116x);
पूर्ण

अटल u32 isp116x_पढ़ो_reg32(काष्ठा isp116x *isp116x, अचिन्हित reg)
अणु
	isp116x_ग_लिखो_addr(isp116x, reg);
	वापस isp116x_पढ़ो_data32(isp116x);
पूर्ण

अटल व्योम isp116x_ग_लिखो_reg16(काष्ठा isp116x *isp116x, अचिन्हित reg,
				अचिन्हित val)
अणु
	isp116x_ग_लिखो_addr(isp116x, reg | ISP116x_WRITE_OFFSET);
	isp116x_ग_लिखो_data16(isp116x, (u16) (val & 0xffff));
पूर्ण

अटल व्योम isp116x_ग_लिखो_reg32(काष्ठा isp116x *isp116x, अचिन्हित reg,
				अचिन्हित val)
अणु
	isp116x_ग_लिखो_addr(isp116x, reg | ISP116x_WRITE_OFFSET);
	isp116x_ग_लिखो_data32(isp116x, (u32) val);
पूर्ण

#घोषणा isp116x_show_reg_log(d,r,s) अणु				\
	अगर ((r) < 0x20) अणु			                \
		DBG("%-12s[%02x]: %08x\n", #r,			\
			r, isp116x_पढ़ो_reg32(d, r));		\
	पूर्ण अन्यथा अणु						\
		DBG("%-12s[%02x]:     %04x\n", #r,		\
			r, isp116x_पढ़ो_reg16(d, r));	    	\
	पूर्ण							\
पूर्ण
#घोषणा isp116x_show_reg_seq(d,r,s) अणु				\
	अगर ((r) < 0x20) अणु					\
		seq_म_लिखो(s, "%-12s[%02x]: %08x\n", #r,	\
			r, isp116x_पढ़ो_reg32(d, r));		\
	पूर्ण अन्यथा अणु						\
		seq_म_लिखो(s, "%-12s[%02x]:     %04x\n", #r,	\
			r, isp116x_पढ़ो_reg16(d, r));		\
	पूर्ण							\
पूर्ण

#घोषणा isp116x_show_regs(d,type,s) अणु			\
	isp116x_show_reg_##type(d, HCREVISION, s);	\
	isp116x_show_reg_##type(d, HCCONTROL, s);	\
	isp116x_show_reg_##type(d, HCCMDSTAT, s);	\
	isp116x_show_reg_##type(d, HCINTSTAT, s);	\
	isp116x_show_reg_##type(d, HCINTENB, s);	\
	isp116x_show_reg_##type(d, HCFMINTVL, s);	\
	isp116x_show_reg_##type(d, HCFMREM, s);		\
	isp116x_show_reg_##type(d, HCFMNUM, s);		\
	isp116x_show_reg_##type(d, HCLSTHRESH, s);	\
	isp116x_show_reg_##type(d, HCRHDESCA, s);	\
	isp116x_show_reg_##type(d, HCRHDESCB, s);	\
	isp116x_show_reg_##type(d, HCRHSTATUS, s);	\
	isp116x_show_reg_##type(d, HCRHPORT1, s);	\
	isp116x_show_reg_##type(d, HCRHPORT2, s);	\
	isp116x_show_reg_##type(d, HCHWCFG, s);		\
	isp116x_show_reg_##type(d, HCDMACFG, s);	\
	isp116x_show_reg_##type(d, HCXFERCTR, s);	\
	isp116x_show_reg_##type(d, HCuPINT, s);		\
	isp116x_show_reg_##type(d, HCuPINTENB, s);	\
	isp116x_show_reg_##type(d, HCCHIPID, s);	\
	isp116x_show_reg_##type(d, HCSCRATCH, s);	\
	isp116x_show_reg_##type(d, HCITLBUFLEN, s);	\
	isp116x_show_reg_##type(d, HCATLBUFLEN, s);	\
	isp116x_show_reg_##type(d, HCBUFSTAT, s);	\
	isp116x_show_reg_##type(d, HCRDITL0LEN, s);	\
	isp116x_show_reg_##type(d, HCRDITL1LEN, s);	\
पूर्ण

/*
   Dump रेजिस्टरs क्रम debugfs.
*/
अटल अंतरभूत व्योम isp116x_show_regs_seq(काष्ठा isp116x *isp116x,
					  काष्ठा seq_file *s)
अणु
	isp116x_show_regs(isp116x, seq, s);
पूर्ण

/*
   Dump रेजिस्टरs to syslog.
*/
अटल अंतरभूत व्योम isp116x_show_regs_log(काष्ठा isp116x *isp116x)
अणु
	isp116x_show_regs(isp116x, log, शून्य);
पूर्ण

#अगर defined(URB_TRACE)

#घोषणा PIPETYPE(pipe)  (अणु अक्षर *__s;			\
	अगर (usb_pipecontrol(pipe))	__s = "ctrl";	\
	अन्यथा अगर (usb_pipeपूर्णांक(pipe))	__s = "int";	\
	अन्यथा अगर (usb_pipebulk(pipe))	__s = "bulk";	\
	अन्यथा				__s = "iso";	\
	__s;पूर्ण)
#घोषणा PIPEसूची(pipe)   (अणु usb_pipein(pipe) ? "in" : "out"; पूर्ण)
#घोषणा URB_NOTSHORT(urb) (अणु (urb)->transfer_flags & URB_SHORT_NOT_OK ? \
	"short_not_ok" : ""; पूर्ण)

/* prपूर्णांक debug info about the URB */
अटल व्योम urb_dbg(काष्ठा urb *urb, अक्षर *msg)
अणु
	अचिन्हित पूर्णांक pipe;

	अगर (!urb) अणु
		DBG("%s: zero urb\n", msg);
		वापस;
	पूर्ण
	pipe = urb->pipe;
	DBG("%s: FA %d ep%d%s %s: len %d/%d %s\n", msg,
	    usb_pipedevice(pipe), usb_pipeendpoपूर्णांक(pipe),
	    PIPEसूची(pipe), PIPETYPE(pipe),
	    urb->transfer_buffer_length, urb->actual_length, URB_NOTSHORT(urb));
पूर्ण

#अन्यथा

#घोषणा  urb_dbg(urb,msg)   करोअणुपूर्णजबतक(0)

#पूर्ण_अगर				/* ! defined(URB_TRACE) */

#अगर defined(PTD_TRACE)

#घोषणा PTD_सूची_STR(ptd)  (अणुअक्षर __c;		\
	चयन(PTD_GET_सूची(ptd))अणु		\
	हाल 0:  __c = 's'; अवरोध;		\
	हाल 1:  __c = 'o'; अवरोध;		\
	शेष: __c = 'i'; अवरोध;		\
	पूर्ण; __c;पूर्ण)

/*
  Dump PTD info. The code करोcuments the क्रमmat
  perfectly, right :)
*/
अटल अंतरभूत व्योम dump_ptd(काष्ठा ptd *ptd)
अणु
	prपूर्णांकk(KERN_WARNING "td: %x %d%c%d %d,%d,%d  %x %x%x%x\n",
	       PTD_GET_CC(ptd), PTD_GET_FA(ptd),
	       PTD_सूची_STR(ptd), PTD_GET_EP(ptd),
	       PTD_GET_COUNT(ptd), PTD_GET_LEN(ptd), PTD_GET_MPS(ptd),
	       PTD_GET_TOGGLE(ptd), PTD_GET_ACTIVE(ptd),
	       PTD_GET_SPD(ptd), PTD_GET_LAST(ptd));
पूर्ण

अटल अंतरभूत व्योम dump_ptd_out_data(काष्ठा ptd *ptd, u8 * buf)
अणु
	पूर्णांक k;

	अगर (PTD_GET_सूची(ptd) != PTD_सूची_IN && PTD_GET_LEN(ptd)) अणु
		prपूर्णांकk(KERN_WARNING "-> ");
		क्रम (k = 0; k < PTD_GET_LEN(ptd); ++k)
			prपूर्णांकk("%02x ", ((u8 *) buf)[k]);
		prपूर्णांकk("\n");
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम dump_ptd_in_data(काष्ठा ptd *ptd, u8 * buf)
अणु
	पूर्णांक k;

	अगर (PTD_GET_सूची(ptd) == PTD_सूची_IN && PTD_GET_COUNT(ptd)) अणु
		prपूर्णांकk(KERN_WARNING "<- ");
		क्रम (k = 0; k < PTD_GET_COUNT(ptd); ++k)
			prपूर्णांकk("%02x ", ((u8 *) buf)[k]);
		prपूर्णांकk("\n");
	पूर्ण
	अगर (PTD_GET_LAST(ptd))
		prपूर्णांकk(KERN_WARNING "-\n");
पूर्ण

#अन्यथा

#घोषणा dump_ptd(ptd)               करोअणुपूर्णजबतक(0)
#घोषणा dump_ptd_in_data(ptd,buf)   करोअणुपूर्णजबतक(0)
#घोषणा dump_ptd_out_data(ptd,buf)  करोअणुपूर्णजबतक(0)

#पूर्ण_अगर				/* ! defined(PTD_TRACE) */
