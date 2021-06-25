<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * ISP1362 HCD (Host Controller Driver) क्रम USB.
 *
 * COPYRIGHT (C) by L. Wassmann <LW@KARO-electronics.de>
 */

/* ------------------------------------------------------------------------- */

#घोषणा MAX_ROOT_PORTS		2

#घोषणा USE_32BIT		0

/* These options are mutually exclusive */
#घोषणा USE_PLATFORM_DELAY	0
#घोषणा USE_NDELAY		0

#घोषणा DUMMY_DELAY_ACCESS करो अणुपूर्ण जबतक (0)

/* ------------------------------------------------------------------------- */

#घोषणा USB_RESET_WIDTH			50
#घोषणा MAX_XFER_SIZE			1023

/* Buffer sizes */
#घोषणा ISP1362_BUF_SIZE		4096
#घोषणा ISP1362_ISTL_बफ_मानE		512
#घोषणा ISP1362_INTL_BLKSIZE		64
#घोषणा ISP1362_INTL_BUFFERS		16
#घोषणा ISP1362_ATL_BLKSIZE		64

#घोषणा ISP1362_REG_WRITE_OFFSET	0x80

#घोषणा REG_WIDTH_16			0x000
#घोषणा REG_WIDTH_32			0x100
#घोषणा REG_WIDTH_MASK			0x100
#घोषणा REG_NO_MASK			0x0ff

#अगर_घोषित ISP1362_DEBUG
प्रकार स्थिर अचिन्हित पूर्णांक isp1362_reg_t;

#घोषणा REG_ACCESS_R			0x200
#घोषणा REG_ACCESS_W			0x400
#घोषणा REG_ACCESS_RW			0x600
#घोषणा REG_ACCESS_MASK			0x600

#घोषणा ISP1362_REG_NO(r)		((r) & REG_NO_MASK)

#घोषणा ISP1362_REG(name, addr, width, rw) \
अटल isp1362_reg_t ISP1362_REG_##name = ((addr) | (width) | (rw))

#घोषणा REG_ACCESS_TEST(r)   BUG_ON(((r) & ISP1362_REG_WRITE_OFFSET) && !((r) & REG_ACCESS_W))
#घोषणा REG_WIDTH_TEST(r, w) BUG_ON(((r) & REG_WIDTH_MASK) != (w))
#अन्यथा
प्रकार स्थिर अचिन्हित अक्षर isp1362_reg_t;
#घोषणा ISP1362_REG_NO(r)		(r)

#घोषणा ISP1362_REG(name, addr, width, rw) \
अटल isp1362_reg_t __maybe_unused ISP1362_REG_##name = addr

#घोषणा REG_ACCESS_TEST(r)		करो अणुपूर्ण जबतक (0)
#घोषणा REG_WIDTH_TEST(r, w)		करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

/* OHCI compatible रेजिस्टरs */
/*
 * Note: Some of the ISP1362 'OHCI' रेजिस्टरs implement only
 * a subset of the bits defined in the OHCI spec.
 *
 * Biपंचांगasks क्रम the inभागidual bits of these रेजिस्टरs are defined in "ohci.h"
 */
ISP1362_REG(HCREVISION,	0x00,	REG_WIDTH_32,	REG_ACCESS_R);
ISP1362_REG(HCCONTROL,	0x01,	REG_WIDTH_32,	REG_ACCESS_RW);
ISP1362_REG(HCCMDSTAT,	0x02,	REG_WIDTH_32,	REG_ACCESS_RW);
ISP1362_REG(HCINTSTAT,	0x03,	REG_WIDTH_32,	REG_ACCESS_RW);
ISP1362_REG(HCINTENB,	0x04,	REG_WIDTH_32,	REG_ACCESS_RW);
ISP1362_REG(HCINTDIS,	0x05,	REG_WIDTH_32,	REG_ACCESS_RW);
ISP1362_REG(HCFMINTVL,	0x0d,	REG_WIDTH_32,	REG_ACCESS_RW);
ISP1362_REG(HCFMREM,	0x0e,	REG_WIDTH_32,	REG_ACCESS_RW);
ISP1362_REG(HCFMNUM,	0x0f,	REG_WIDTH_32,	REG_ACCESS_RW);
ISP1362_REG(HCLSTHRESH,	0x11,	REG_WIDTH_32,	REG_ACCESS_RW);
ISP1362_REG(HCRHDESCA,	0x12,	REG_WIDTH_32,	REG_ACCESS_RW);
ISP1362_REG(HCRHDESCB,	0x13,	REG_WIDTH_32,	REG_ACCESS_RW);
ISP1362_REG(HCRHSTATUS,	0x14,	REG_WIDTH_32,	REG_ACCESS_RW);
ISP1362_REG(HCRHPORT1,	0x15,	REG_WIDTH_32,	REG_ACCESS_RW);
ISP1362_REG(HCRHPORT2,	0x16,	REG_WIDTH_32,	REG_ACCESS_RW);

/* Philips ISP1362 specअगरic रेजिस्टरs */
ISP1362_REG(HCHWCFG,	0x20,	REG_WIDTH_16,	REG_ACCESS_RW);
#घोषणा HCHWCFG_DISABLE_SUSPEND	(1 << 15)
#घोषणा HCHWCFG_GLOBAL_PWRDOWN	(1 << 14)
#घोषणा HCHWCFG_PULLDOWN_DS2	(1 << 13)
#घोषणा HCHWCFG_PULLDOWN_DS1	(1 << 12)
#घोषणा HCHWCFG_CLKNOTSTOP	(1 << 11)
#घोषणा HCHWCFG_ANALOG_OC	(1 << 10)
#घोषणा HCHWCFG_ONEINT		(1 << 9)
#घोषणा HCHWCFG_DACK_MODE	(1 << 8)
#घोषणा HCHWCFG_ONEDMA		(1 << 7)
#घोषणा HCHWCFG_DACK_POL	(1 << 6)
#घोषणा HCHWCFG_DREQ_POL	(1 << 5)
#घोषणा HCHWCFG_DBWIDTH_MASK	(0x03 << 3)
#घोषणा HCHWCFG_DBWIDTH(n)	(((n) << 3) & HCHWCFG_DBWIDTH_MASK)
#घोषणा HCHWCFG_INT_POL		(1 << 2)
#घोषणा HCHWCFG_INT_TRIGGER	(1 << 1)
#घोषणा HCHWCFG_INT_ENABLE	(1 << 0)

ISP1362_REG(HCDMACFG,	0x21,	REG_WIDTH_16,	REG_ACCESS_RW);
#घोषणा HCDMACFG_CTR_ENABLE	(1 << 7)
#घोषणा HCDMACFG_BURST_LEN_MASK	(0x03 << 5)
#घोषणा HCDMACFG_BURST_LEN(n)	(((n) << 5) & HCDMACFG_BURST_LEN_MASK)
#घोषणा HCDMACFG_BURST_LEN_1	HCDMACFG_BURST_LEN(0)
#घोषणा HCDMACFG_BURST_LEN_4	HCDMACFG_BURST_LEN(1)
#घोषणा HCDMACFG_BURST_LEN_8	HCDMACFG_BURST_LEN(2)
#घोषणा HCDMACFG_DMA_ENABLE	(1 << 4)
#घोषणा HCDMACFG_BUF_TYPE_MASK	(0x07 << 1)
#घोषणा HCDMACFG_BUF_TYPE(n)	(((n) << 1) & HCDMACFG_BUF_TYPE_MASK)
#घोषणा HCDMACFG_BUF_ISTL0	HCDMACFG_BUF_TYPE(0)
#घोषणा HCDMACFG_BUF_ISTL1	HCDMACFG_BUF_TYPE(1)
#घोषणा HCDMACFG_BUF_INTL	HCDMACFG_BUF_TYPE(2)
#घोषणा HCDMACFG_BUF_ATL	HCDMACFG_BUF_TYPE(3)
#घोषणा HCDMACFG_BUF_सूचीECT	HCDMACFG_BUF_TYPE(4)
#घोषणा HCDMACFG_DMA_RW_SELECT	(1 << 0)

ISP1362_REG(HCXFERCTR,	0x22,	REG_WIDTH_16,	REG_ACCESS_RW);

ISP1362_REG(HCuPINT,	0x24,	REG_WIDTH_16,	REG_ACCESS_RW);
#घोषणा HCuPINT_SOF		(1 << 0)
#घोषणा HCuPINT_ISTL0		(1 << 1)
#घोषणा HCuPINT_ISTL1		(1 << 2)
#घोषणा HCuPINT_EOT		(1 << 3)
#घोषणा HCuPINT_OPR		(1 << 4)
#घोषणा HCuPINT_SUSP		(1 << 5)
#घोषणा HCuPINT_CLKRDY		(1 << 6)
#घोषणा HCuPINT_INTL		(1 << 7)
#घोषणा HCuPINT_ATL		(1 << 8)
#घोषणा HCuPINT_OTG		(1 << 9)

ISP1362_REG(HCuPINTENB,	0x25,	REG_WIDTH_16,	REG_ACCESS_RW);
/* same bit definitions apply as क्रम HCuPINT */

ISP1362_REG(HCCHIPID,	0x27,	REG_WIDTH_16,	REG_ACCESS_R);
#घोषणा HCCHIPID_MASK		0xff00
#घोषणा HCCHIPID_MAGIC		0x3600

ISP1362_REG(HCSCRATCH,	0x28,	REG_WIDTH_16,	REG_ACCESS_RW);

ISP1362_REG(HCSWRES,	0x29,	REG_WIDTH_16,	REG_ACCESS_W);
#घोषणा HCSWRES_MAGIC		0x00f6

ISP1362_REG(HCBUFSTAT,	0x2c,	REG_WIDTH_16,	REG_ACCESS_RW);
#घोषणा HCBUFSTAT_ISTL0_FULL	(1 << 0)
#घोषणा HCBUFSTAT_ISTL1_FULL	(1 << 1)
#घोषणा HCBUFSTAT_INTL_ACTIVE	(1 << 2)
#घोषणा HCBUFSTAT_ATL_ACTIVE	(1 << 3)
#घोषणा HCBUFSTAT_RESET_HWPP	(1 << 4)
#घोषणा HCBUFSTAT_ISTL0_ACTIVE	(1 << 5)
#घोषणा HCBUFSTAT_ISTL1_ACTIVE	(1 << 6)
#घोषणा HCBUFSTAT_ISTL0_DONE	(1 << 8)
#घोषणा HCBUFSTAT_ISTL1_DONE	(1 << 9)
#घोषणा HCBUFSTAT_PAIRED_PTDPP	(1 << 10)

ISP1362_REG(HCसूचीADDR,	0x32,	REG_WIDTH_32,	REG_ACCESS_RW);
#घोषणा HCसूचीADDR_ADDR_MASK	0x0000ffff
#घोषणा HCसूचीADDR_ADDR(n)	(((n) << 0) & HCसूचीADDR_ADDR_MASK)
#घोषणा HCसूचीADDR_COUNT_MASK	0xffff0000
#घोषणा HCसूचीADDR_COUNT(n)	(((n) << 16) & HCसूचीADDR_COUNT_MASK)
ISP1362_REG(HCसूचीDATA,	0x45,	REG_WIDTH_16,	REG_ACCESS_RW);

ISP1362_REG(HCISTLBUFSZ, 0x30,	REG_WIDTH_16,	REG_ACCESS_RW);
ISP1362_REG(HCISTL0PORT, 0x40,	REG_WIDTH_16,	REG_ACCESS_RW);
ISP1362_REG(HCISTL1PORT, 0x42,	REG_WIDTH_16,	REG_ACCESS_RW);
ISP1362_REG(HCISTLRATE,	0x47,	REG_WIDTH_16,	REG_ACCESS_RW);

ISP1362_REG(HCINTLBUFSZ, 0x33,	REG_WIDTH_16,	REG_ACCESS_RW);
ISP1362_REG(HCINTLPORT,	0x43,	REG_WIDTH_16,	REG_ACCESS_RW);
ISP1362_REG(HCINTLBLKSZ, 0x53,	REG_WIDTH_16,	REG_ACCESS_RW);
ISP1362_REG(HCINTLDONE,	0x17,	REG_WIDTH_32,	REG_ACCESS_R);
ISP1362_REG(HCINTLSKIP,	0x18,	REG_WIDTH_32,	REG_ACCESS_RW);
ISP1362_REG(HCINTLLAST,	0x19,	REG_WIDTH_32,	REG_ACCESS_RW);
ISP1362_REG(HCINTLCURR,	0x1a,	REG_WIDTH_16,	REG_ACCESS_R);

ISP1362_REG(HCATLBUFSZ, 0x34,	REG_WIDTH_16,	REG_ACCESS_RW);
ISP1362_REG(HCATLPORT,	0x44,	REG_WIDTH_16,	REG_ACCESS_RW);
ISP1362_REG(HCATLBLKSZ, 0x54,	REG_WIDTH_16,	REG_ACCESS_RW);
ISP1362_REG(HCATLDONE,	0x1b,	REG_WIDTH_32,	REG_ACCESS_R);
ISP1362_REG(HCATLSKIP,	0x1c,	REG_WIDTH_32,	REG_ACCESS_RW);
ISP1362_REG(HCATLLAST,	0x1d,	REG_WIDTH_32,	REG_ACCESS_RW);
ISP1362_REG(HCATLCURR,	0x1e,	REG_WIDTH_16,	REG_ACCESS_R);

ISP1362_REG(HCATLDTC,	0x51,	REG_WIDTH_16,	REG_ACCESS_RW);
ISP1362_REG(HCATLDTCTO,	0x52,	REG_WIDTH_16,	REG_ACCESS_RW);


ISP1362_REG(OTGCONTROL,	0x62,	REG_WIDTH_16,	REG_ACCESS_RW);
ISP1362_REG(OTGSTATUS,	0x67,	REG_WIDTH_16,	REG_ACCESS_R);
ISP1362_REG(OTGINT,	0x68,	REG_WIDTH_16,	REG_ACCESS_RW);
ISP1362_REG(OTGINTENB,	0x69,	REG_WIDTH_16,	REG_ACCESS_RW);
ISP1362_REG(OTGTIMER,	0x6A,	REG_WIDTH_16,	REG_ACCESS_RW);
ISP1362_REG(OTGALTTMR,	0x6C,	REG_WIDTH_16,	REG_ACCESS_RW);

/* Philips transfer descriptor, cpu-endian */
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
	u16 faddr;
#घोषणा	PTD_FA_MSK	(0x7f << 0)
/* PTD Byte 7: [StartingFrame (अगर ISO PTD) | StartingFrame[0..4], PollingRate[0..2] (अगर INT PTD)] */
#घोषणा PTD_SF_ISO_MSK	(0xff << 8)
#घोषणा PTD_SF_INT_MSK	(0x1f << 8)
#घोषणा PTD_PR_MSK	(0x07 << 13)
पूर्ण __attribute__ ((packed, aligned(2)));
#घोषणा PTD_HEADER_SIZE माप(काष्ठा ptd)

/* ------------------------------------------------------------------------- */
/* Copied from ohci.h: */
/*
 * Hardware transfer status codes -- CC from PTD
 */
#घोषणा PTD_CC_NOERROR      0x00
#घोषणा PTD_CC_CRC          0x01
#घोषणा PTD_CC_BITSTUFFING  0x02
#घोषणा PTD_CC_DATATOGGLEM  0x03
#घोषणा PTD_CC_STALL        0x04
#घोषणा PTD_DEVNOTRESP      0x05
#घोषणा PTD_PIDCHECKFAIL    0x06
#घोषणा PTD_UNEXPECTEDPID   0x07
#घोषणा PTD_DATAOVERRUN     0x08
#घोषणा PTD_DATAUNDERRUN    0x09
    /* 0x0A, 0x0B reserved क्रम hardware */
#घोषणा PTD_BUFFEROVERRUN   0x0C
#घोषणा PTD_BUFFERUNDERRUN  0x0D
    /* 0x0E, 0x0F reserved क्रम HCD */
#घोषणा PTD_NOTACCESSED     0x0F


/* map OHCI TD status codes (CC) to त्रुटि_सं values */
अटल स्थिर पूर्णांक cc_to_error[16] = अणु
	/* No  Error  */               0,
	/* CRC Error  */               -EILSEQ,
	/* Bit Stuff  */               -EPROTO,
	/* Data Togg  */               -EILSEQ,
	/* Stall      */               -EPIPE,
	/* DevNotResp */               -ETIMEDOUT,
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
 * HcControl (control) रेजिस्टर masks
 */
#घोषणा OHCI_CTRL_HCFS	(3 << 6)	/* host controller functional state */
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
#घोषणा OHCI_SOC  	(3 << 16)	/* scheduling overrun count */

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

/* roothub.portstatus [i] bits */
#घोषणा RH_PS_CCS            0x00000001   	/* current connect status */
#घोषणा RH_PS_PES            0x00000002   	/* port enable status*/
#घोषणा RH_PS_PSS            0x00000004   	/* port suspend status */
#घोषणा RH_PS_POCI           0x00000008   	/* port over current indicator */
#घोषणा RH_PS_PRS            0x00000010  	/* port reset status */
#घोषणा RH_PS_PPS            0x00000100   	/* port घातer status */
#घोषणा RH_PS_LSDA           0x00000200    	/* low speed device attached */
#घोषणा RH_PS_CSC            0x00010000 	/* connect status change */
#घोषणा RH_PS_PESC           0x00020000   	/* port enable status change */
#घोषणा RH_PS_PSSC           0x00040000    	/* port suspend status change */
#घोषणा RH_PS_OCIC           0x00080000    	/* over current indicator change */
#घोषणा RH_PS_PRSC           0x00100000   	/* port reset status change */

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

#घोषणा	FI			0x2edf		/* 12000 bits per frame (-1) */
#घोषणा	FSMP(fi) 		(0x7fff & ((6 * ((fi) - 210)) / 7))
#घोषणा LSTHRESH		0x628		/* lowspeed bit threshold */

/* ------------------------------------------------------------------------- */

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
#घोषणा PTD_GET_FA(p)		(((p)->faddr & PTD_FA_MSK) >> 0)
#घोषणा PTD_FA(v)		(((v) << 0) & PTD_FA_MSK)
#घोषणा PTD_GET_SF_INT(p)	(((p)->faddr & PTD_SF_INT_MSK) >> 8)
#घोषणा PTD_SF_INT(v)		(((v) << 8) & PTD_SF_INT_MSK)
#घोषणा PTD_GET_SF_ISO(p)	(((p)->faddr & PTD_SF_ISO_MSK) >> 8)
#घोषणा PTD_SF_ISO(v)		(((v) << 8) & PTD_SF_ISO_MSK)
#घोषणा PTD_GET_PR(p)		(((p)->faddr & PTD_PR_MSK) >> 13)
#घोषणा PTD_PR(v)		(((v) << 13) & PTD_PR_MSK)

#घोषणा	LOG2_PERIODIC_SIZE	5	/* arbitrary; this matches OHCI */
#घोषणा	PERIODIC_SIZE		(1 << LOG2_PERIODIC_SIZE)

काष्ठा isp1362_ep अणु
	काष्ठा usb_host_endpoपूर्णांक *hep;
	काष्ठा usb_device	*udev;

	/* philips transfer descriptor */
	काष्ठा ptd		ptd;

	u8			maxpacket;
	u8			epnum;
	u8			nextpid;
	u16			error_count;
	u16			length;		/* of current packet */
	s16			ptd_offset;	/* buffer offset in ISP1362 where
						   PTD has been stored
						   (क्रम access thru HCसूचीDATA) */
	पूर्णांक			ptd_index;
	पूर्णांक num_ptds;
	व्योम 			*data;		/* to databuf */
	/* queue of active EPs (the ones transmitted to the chip) */
	काष्ठा list_head	active;

	/* periodic schedule */
	u8			branch;
	u16			पूर्णांकerval;
	u16			load;
	u16			last_iso;

	/* async schedule */
	काष्ठा list_head	schedule;	/* list of all EPs that need processing */
	काष्ठा list_head	हटाओ_list;
	पूर्णांक			num_req;
पूर्ण;

काष्ठा isp1362_ep_queue अणु
	काष्ठा list_head	active;		/* list of PTDs currently processed by HC */
	atomic_t		finishing;
	अचिन्हित दीर्घ		buf_map;
	अचिन्हित दीर्घ		skip_map;
	पूर्णांक			मुक्त_ptd;
	u16			buf_start;
	u16			buf_size;
	u16			blk_size;	/* PTD buffer block size क्रम ATL and INTL */
	u8			buf_count;
	u8			buf_avail;
	अक्षर			name[16];

	/* क्रम statistical tracking */
	u8			stat_maxptds;	/* Max # of ptds seen simultaneously in fअगरo */
	u8			ptd_count;	/* number of ptds submitted to this queue */
पूर्ण;

काष्ठा isp1362_hcd अणु
	spinlock_t		lock;
	व्योम __iomem		*addr_reg;
	व्योम __iomem		*data_reg;

	काष्ठा isp1362_platक्रमm_data *board;

	अचिन्हित दीर्घ		stat1, stat2, stat4, stat8, stat16;

	/* HC रेजिस्टरs */
	u32			पूर्णांकenb;		/* "OHCI" पूर्णांकerrupts */
	u16			irqenb;		/* uP पूर्णांकerrupts */

	/* Root hub रेजिस्टरs */
	u32			rhdesca;
	u32			rhdescb;
	u32			rhstatus;
	u32			rhport[MAX_ROOT_PORTS];
	अचिन्हित दीर्घ		next_statechange;

	/* HC control reg shaकरोw copy */
	u32			hc_control;

	/* async schedule: control, bulk */
	काष्ठा list_head	async;

	/* periodic schedule: पूर्णांक */
	u16			load[PERIODIC_SIZE];
	काष्ठा list_head	periodic;
	u16			fmindex;

	/* periodic schedule: isochronous */
	काष्ठा list_head	isoc;
	अचिन्हित पूर्णांक		istl_flip:1;
	अचिन्हित पूर्णांक		irq_active:1;

	/* Schedules क्रम the current frame */
	काष्ठा isp1362_ep_queue atl_queue;
	काष्ठा isp1362_ep_queue पूर्णांकl_queue;
	काष्ठा isp1362_ep_queue istl_queue[2];

	/* list of PTDs retrieved from HC */
	काष्ठा list_head	हटाओ_list;
	क्रमागत अणु
		ISP1362_INT_SOF,
		ISP1362_INT_ISTL0,
		ISP1362_INT_ISTL1,
		ISP1362_INT_EOT,
		ISP1362_INT_OPR,
		ISP1362_INT_SUSP,
		ISP1362_INT_CLKRDY,
		ISP1362_INT_INTL,
		ISP1362_INT_ATL,
		ISP1362_INT_OTG,
		NUM_ISP1362_IRQS
	पूर्ण IRQ_NAMES;
	अचिन्हित पूर्णांक		irq_stat[NUM_ISP1362_IRQS];
	पूर्णांक			req_serial;
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *ISP1362_INT_NAME(पूर्णांक n)
अणु
	चयन (n) अणु
	हाल ISP1362_INT_SOF:    वापस "SOF";
	हाल ISP1362_INT_ISTL0:  वापस "ISTL0";
	हाल ISP1362_INT_ISTL1:  वापस "ISTL1";
	हाल ISP1362_INT_EOT:    वापस "EOT";
	हाल ISP1362_INT_OPR:    वापस "OPR";
	हाल ISP1362_INT_SUSP:   वापस "SUSP";
	हाल ISP1362_INT_CLKRDY: वापस "CLKRDY";
	हाल ISP1362_INT_INTL:   वापस "INTL";
	हाल ISP1362_INT_ATL:    वापस "ATL";
	हाल ISP1362_INT_OTG:    वापस "OTG";
	शेष:                 वापस "unknown";
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम ALIGNSTAT(काष्ठा isp1362_hcd *isp1362_hcd, व्योम *ptr)
अणु
	अचिन्हित दीर्घ p = (अचिन्हित दीर्घ)ptr;
	अगर (!(p & 0xf))
		isp1362_hcd->stat16++;
	अन्यथा अगर (!(p & 0x7))
		isp1362_hcd->stat8++;
	अन्यथा अगर (!(p & 0x3))
		isp1362_hcd->stat4++;
	अन्यथा अगर (!(p & 0x1))
		isp1362_hcd->stat2++;
	अन्यथा
		isp1362_hcd->stat1++;
पूर्ण

अटल अंतरभूत काष्ठा isp1362_hcd *hcd_to_isp1362_hcd(काष्ठा usb_hcd *hcd)
अणु
	वापस (काष्ठा isp1362_hcd *) (hcd->hcd_priv);
पूर्ण

अटल अंतरभूत काष्ठा usb_hcd *isp1362_hcd_to_hcd(काष्ठा isp1362_hcd *isp1362_hcd)
अणु
	वापस container_of((व्योम *)isp1362_hcd, काष्ठा usb_hcd, hcd_priv);
पूर्ण

#घोषणा frame_beक्रमe(f1, f2)	((s16)((u16)f1 - (u16)f2) < 0)

/*
 * ISP1362 HW Interface
 */

#घोषणा DBG(level, fmt...) \
	करो अणु \
		अगर (dbg_level > level) \
			pr_debug(fmt); \
	पूर्ण जबतक (0)

#अगर_घोषित VERBOSE
#    define VDBG(fmt...)	DBG(3, fmt)
#अन्यथा
#    define VDBG(fmt...)	करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_घोषित REGISTERS
#    define RDBG(fmt...)	DBG(1, fmt)
#अन्यथा
#    define RDBG(fmt...)	करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_घोषित URB_TRACE
#घोषणा URB_DBG(fmt...)		DBG(0, fmt)
#अन्यथा
#घोषणा URB_DBG(fmt...)		करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर


#अगर USE_PLATFORM_DELAY
#अगर USE_NDELAY
#त्रुटि USE_PLATFORM_DELAY and USE_NDELAY defined simultaneously.
#पूर्ण_अगर
#घोषणा	isp1362_delay(h, d)	(h)->board->delay(isp1362_hcd_to_hcd(h)->self.controller, d)
#या_अगर USE_NDELAY
#घोषणा	isp1362_delay(h, d)	ndelay(d)
#अन्यथा
#घोषणा	isp1362_delay(h, d)	करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा get_urb(ep) (अणु							\
	BUG_ON(list_empty(&ep->hep->urb_list));				\
	container_of(ep->hep->urb_list.next, काष्ठा urb, urb_list);	\
पूर्ण)

/* basic access functions क्रम ISP1362 chip रेजिस्टरs */
/* NOTE: The contents of the address poपूर्णांकer रेजिस्टर cannot be पढ़ो back! The driver must ensure,
 * that all रेजिस्टर accesses are perक्रमmed with पूर्णांकerrupts disabled, since the पूर्णांकerrupt
 * handler has no way of restoring the previous state.
 */
अटल व्योम isp1362_ग_लिखो_addr(काष्ठा isp1362_hcd *isp1362_hcd, isp1362_reg_t reg)
अणु
	REG_ACCESS_TEST(reg);
	DUMMY_DELAY_ACCESS;
	ग_लिखोw(ISP1362_REG_NO(reg), isp1362_hcd->addr_reg);
	DUMMY_DELAY_ACCESS;
	isp1362_delay(isp1362_hcd, 1);
पूर्ण

अटल व्योम isp1362_ग_लिखो_data16(काष्ठा isp1362_hcd *isp1362_hcd, u16 val)
अणु
	DUMMY_DELAY_ACCESS;
	ग_लिखोw(val, isp1362_hcd->data_reg);
पूर्ण

अटल u16 isp1362_पढ़ो_data16(काष्ठा isp1362_hcd *isp1362_hcd)
अणु
	u16 val;

	DUMMY_DELAY_ACCESS;
	val = पढ़ोw(isp1362_hcd->data_reg);

	वापस val;
पूर्ण

अटल व्योम isp1362_ग_लिखो_data32(काष्ठा isp1362_hcd *isp1362_hcd, u32 val)
अणु
#अगर USE_32BIT
	DUMMY_DELAY_ACCESS;
	ग_लिखोl(val, isp1362_hcd->data_reg);
#अन्यथा
	DUMMY_DELAY_ACCESS;
	ग_लिखोw((u16)val, isp1362_hcd->data_reg);
	DUMMY_DELAY_ACCESS;
	ग_लिखोw(val >> 16, isp1362_hcd->data_reg);
#पूर्ण_अगर
पूर्ण

अटल u32 isp1362_पढ़ो_data32(काष्ठा isp1362_hcd *isp1362_hcd)
अणु
	u32 val;

#अगर USE_32BIT
	DUMMY_DELAY_ACCESS;
	val = पढ़ोl(isp1362_hcd->data_reg);
#अन्यथा
	DUMMY_DELAY_ACCESS;
	val = (u32)पढ़ोw(isp1362_hcd->data_reg);
	DUMMY_DELAY_ACCESS;
	val |= (u32)पढ़ोw(isp1362_hcd->data_reg) << 16;
#पूर्ण_अगर
	वापस val;
पूर्ण

/* use पढ़ोsw/ग_लिखोsw to access the fअगरo whenever possible */
/* assume HCसूचीDATA or XFERCTR & addr_reg have been set up */
अटल व्योम isp1362_पढ़ो_fअगरo(काष्ठा isp1362_hcd *isp1362_hcd, व्योम *buf, u16 len)
अणु
	u8 *dp = buf;
	u16 data;

	अगर (!len)
		वापस;

	RDBG("%s: Reading %d byte from fifo to mem @ %p\n", __func__, len, buf);
#अगर USE_32BIT
	अगर (len >= 4) अणु
		RDBG("%s: Using readsl for %d dwords\n", __func__, len >> 2);
		पढ़ोsl(isp1362_hcd->data_reg, dp, len >> 2);
		dp += len & ~3;
		len &= 3;
	पूर्ण
#पूर्ण_अगर
	अगर (len >= 2) अणु
		RDBG("%s: Using readsw for %d words\n", __func__, len >> 1);
		insw((अचिन्हित दीर्घ)isp1362_hcd->data_reg, dp, len >> 1);
		dp += len & ~1;
		len &= 1;
	पूर्ण

	BUG_ON(len & ~1);
	अगर (len > 0) अणु
		data = isp1362_पढ़ो_data16(isp1362_hcd);
		RDBG("%s: Reading trailing byte %02x to mem @ %08x\n", __func__,
		     (u8)data, (u32)dp);
		*dp = (u8)data;
	पूर्ण
पूर्ण

अटल व्योम isp1362_ग_लिखो_fअगरo(काष्ठा isp1362_hcd *isp1362_hcd, व्योम *buf, u16 len)
अणु
	u8 *dp = buf;
	u16 data;

	अगर (!len)
		वापस;

	अगर ((अचिन्हित दीर्घ)dp & 0x1) अणु
		/* not aligned */
		क्रम (; len > 1; len -= 2) अणु
			data = *dp++;
			data |= *dp++ << 8;
			isp1362_ग_लिखो_data16(isp1362_hcd, data);
		पूर्ण
		अगर (len)
			isp1362_ग_लिखो_data16(isp1362_hcd, *dp);
		वापस;
	पूर्ण

	RDBG("%s: Writing %d byte to fifo from memory @%p\n", __func__, len, buf);
#अगर USE_32BIT
	अगर (len >= 4) अणु
		RDBG("%s: Using writesl for %d dwords\n", __func__, len >> 2);
		ग_लिखोsl(isp1362_hcd->data_reg, dp, len >> 2);
		dp += len & ~3;
		len &= 3;
	पूर्ण
#पूर्ण_अगर
	अगर (len >= 2) अणु
		RDBG("%s: Using writesw for %d words\n", __func__, len >> 1);
		outsw((अचिन्हित दीर्घ)isp1362_hcd->data_reg, dp, len >> 1);
		dp += len & ~1;
		len &= 1;
	पूर्ण

	BUG_ON(len & ~1);
	अगर (len > 0) अणु
		/* finally ग_लिखो any trailing byte; we करोn't need to care
		 * about the high byte of the last word written
		 */
		data = (u16)*dp;
		RDBG("%s: Sending trailing byte %02x from mem @ %08x\n", __func__,
			data, (u32)dp);
		isp1362_ग_लिखो_data16(isp1362_hcd, data);
	पूर्ण
पूर्ण

#घोषणा isp1362_पढ़ो_reg16(d, r)		(अणु			\
	u16 __v;							\
	REG_WIDTH_TEST(ISP1362_REG_##r, REG_WIDTH_16);			\
	isp1362_ग_लिखो_addr(d, ISP1362_REG_##r);				\
	__v = isp1362_पढ़ो_data16(d);					\
	RDBG("%s: Read %04x from %s[%02x]\n", __func__, __v, #r,	\
	     ISP1362_REG_NO(ISP1362_REG_##r));				\
	__v;								\
पूर्ण)

#घोषणा isp1362_पढ़ो_reg32(d, r)		(अणु			\
	u32 __v;							\
	REG_WIDTH_TEST(ISP1362_REG_##r, REG_WIDTH_32);			\
	isp1362_ग_लिखो_addr(d, ISP1362_REG_##r);				\
	__v = isp1362_पढ़ो_data32(d);					\
	RDBG("%s: Read %08x from %s[%02x]\n", __func__, __v, #r,	\
	     ISP1362_REG_NO(ISP1362_REG_##r));				\
	__v;								\
पूर्ण)

#घोषणा isp1362_ग_लिखो_reg16(d, r, v)	अणु					\
	REG_WIDTH_TEST(ISP1362_REG_##r, REG_WIDTH_16);				\
	isp1362_ग_लिखो_addr(d, (ISP1362_REG_##r) | ISP1362_REG_WRITE_OFFSET);	\
	isp1362_ग_लिखो_data16(d, (u16)(v));					\
	RDBG("%s: Wrote %04x to %s[%02x]\n", __func__, (u16)(v), #r,	\
	     ISP1362_REG_NO(ISP1362_REG_##r));					\
पूर्ण

#घोषणा isp1362_ग_लिखो_reg32(d, r, v)	अणु					\
	REG_WIDTH_TEST(ISP1362_REG_##r, REG_WIDTH_32);				\
	isp1362_ग_लिखो_addr(d, (ISP1362_REG_##r) | ISP1362_REG_WRITE_OFFSET);	\
	isp1362_ग_लिखो_data32(d, (u32)(v));					\
	RDBG("%s: Wrote %08x to %s[%02x]\n", __func__, (u32)(v), #r,	\
	     ISP1362_REG_NO(ISP1362_REG_##r));					\
पूर्ण

#घोषणा isp1362_set_mask16(d, r, m) अणु			\
	u16 __v;					\
	__v = isp1362_पढ़ो_reg16(d, r);			\
	अगर ((__v | m) != __v)				\
		isp1362_ग_लिखो_reg16(d, r, __v | m);	\
पूर्ण

#घोषणा isp1362_clr_mask16(d, r, m) अणु			\
	u16 __v;					\
	__v = isp1362_पढ़ो_reg16(d, r);			\
	अगर ((__v & ~m) != __v)			\
		isp1362_ग_लिखो_reg16(d, r, __v & ~m);	\
पूर्ण

#घोषणा isp1362_set_mask32(d, r, m) अणु			\
	u32 __v;					\
	__v = isp1362_पढ़ो_reg32(d, r);			\
	अगर ((__v | m) != __v)				\
		isp1362_ग_लिखो_reg32(d, r, __v | m);	\
पूर्ण

#घोषणा isp1362_clr_mask32(d, r, m) अणु			\
	u32 __v;					\
	__v = isp1362_पढ़ो_reg32(d, r);			\
	अगर ((__v & ~m) != __v)			\
		isp1362_ग_लिखो_reg32(d, r, __v & ~m);	\
पूर्ण

#घोषणा isp1362_show_reg(d, r) अणु								\
	अगर ((ISP1362_REG_##r & REG_WIDTH_MASK) == REG_WIDTH_32)			\
		DBG(0, "%-12s[%02x]: %08x\n", #r,					\
			ISP1362_REG_NO(ISP1362_REG_##r), isp1362_पढ़ो_reg32(d, r));	\
	अन्यथा									\
		DBG(0, "%-12s[%02x]:     %04x\n", #r,					\
			ISP1362_REG_NO(ISP1362_REG_##r), isp1362_पढ़ो_reg16(d, r));	\
पूर्ण

अटल व्योम isp1362_ग_लिखो_diraddr(काष्ठा isp1362_hcd *isp1362_hcd, u16 offset, u16 len)
अणु
	len = (len + 1) & ~1;

	isp1362_clr_mask16(isp1362_hcd, HCDMACFG, HCDMACFG_CTR_ENABLE);
	isp1362_ग_लिखो_reg32(isp1362_hcd, HCसूचीADDR,
			    HCसूचीADDR_ADDR(offset) | HCसूचीADDR_COUNT(len));
पूर्ण

अटल व्योम isp1362_पढ़ो_buffer(काष्ठा isp1362_hcd *isp1362_hcd, व्योम *buf, u16 offset, पूर्णांक len)
अणु
	isp1362_ग_लिखो_diraddr(isp1362_hcd, offset, len);

	DBG(3, "%s: Reading %d byte from buffer @%04x to memory @ %p\n",
	    __func__, len, offset, buf);

	isp1362_ग_लिखो_reg16(isp1362_hcd, HCuPINT, HCuPINT_EOT);

	isp1362_ग_लिखो_addr(isp1362_hcd, ISP1362_REG_HCसूचीDATA);

	isp1362_पढ़ो_fअगरo(isp1362_hcd, buf, len);
	isp1362_ग_लिखो_reg16(isp1362_hcd, HCuPINT, HCuPINT_EOT);
पूर्ण

अटल व्योम isp1362_ग_लिखो_buffer(काष्ठा isp1362_hcd *isp1362_hcd, व्योम *buf, u16 offset, पूर्णांक len)
अणु
	isp1362_ग_लिखो_diraddr(isp1362_hcd, offset, len);

	DBG(3, "%s: Writing %d byte to buffer @%04x from memory @ %p\n",
	    __func__, len, offset, buf);

	isp1362_ग_लिखो_reg16(isp1362_hcd, HCuPINT, HCuPINT_EOT);

	isp1362_ग_लिखो_addr(isp1362_hcd, ISP1362_REG_HCसूचीDATA | ISP1362_REG_WRITE_OFFSET);
	isp1362_ग_लिखो_fअगरo(isp1362_hcd, buf, len);

	isp1362_ग_लिखो_reg16(isp1362_hcd, HCuPINT, HCuPINT_EOT);
पूर्ण

अटल व्योम __attribute__((unused)) dump_data(अक्षर *buf, पूर्णांक len)
अणु
	अगर (dbg_level > 0) अणु
		पूर्णांक k;
		पूर्णांक lf = 0;

		क्रम (k = 0; k < len; ++k) अणु
			अगर (!lf)
				DBG(0, "%04x:", k);
			prपूर्णांकk(" %02x", ((u8 *) buf)[k]);
			lf = 1;
			अगर (!k)
				जारी;
			अगर (k % 16 == 15) अणु
				prपूर्णांकk("\n");
				lf = 0;
				जारी;
			पूर्ण
			अगर (k % 8 == 7)
				prपूर्णांकk(" ");
			अगर (k % 4 == 3)
				prपूर्णांकk(" ");
		पूर्ण
		अगर (lf)
			prपूर्णांकk("\n");
	पूर्ण
पूर्ण

#अगर defined(PTD_TRACE)

अटल व्योम dump_ptd(काष्ठा ptd *ptd)
अणु
	DBG(0, "EP %p: CC=%x EP=%d DIR=%x CNT=%d LEN=%d MPS=%d TGL=%x ACT=%x FA=%d SPD=%x SF=%x PR=%x LST=%x\n",
	    container_of(ptd, काष्ठा isp1362_ep, ptd),
	    PTD_GET_CC(ptd), PTD_GET_EP(ptd), PTD_GET_सूची(ptd),
	    PTD_GET_COUNT(ptd), PTD_GET_LEN(ptd), PTD_GET_MPS(ptd),
	    PTD_GET_TOGGLE(ptd), PTD_GET_ACTIVE(ptd), PTD_GET_FA(ptd),
	    PTD_GET_SPD(ptd), PTD_GET_SF_INT(ptd), PTD_GET_PR(ptd), PTD_GET_LAST(ptd));
	DBG(0, "  %04x %04x %04x %04x\n", ptd->count, ptd->mps, ptd->len, ptd->faddr);
पूर्ण

अटल व्योम dump_ptd_out_data(काष्ठा ptd *ptd, u8 *buf)
अणु
	अगर (dbg_level > 0) अणु
		अगर (PTD_GET_सूची(ptd) != PTD_सूची_IN && PTD_GET_LEN(ptd)) अणु
			DBG(0, "--out->\n");
			dump_data(buf, PTD_GET_LEN(ptd));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dump_ptd_in_data(काष्ठा ptd *ptd, u8 *buf)
अणु
	अगर (dbg_level > 0) अणु
		अगर (PTD_GET_सूची(ptd) == PTD_सूची_IN && PTD_GET_COUNT(ptd)) अणु
			DBG(0, "<--in--\n");
			dump_data(buf, PTD_GET_COUNT(ptd));
		पूर्ण
		DBG(0, "-----\n");
	पूर्ण
पूर्ण

अटल व्योम dump_ptd_queue(काष्ठा isp1362_ep_queue *epq)
अणु
	काष्ठा isp1362_ep *ep;
	पूर्णांक dbg = dbg_level;

	dbg_level = 1;
	list_क्रम_each_entry(ep, &epq->active, active) अणु
		dump_ptd(&ep->ptd);
		dump_data(ep->data, ep->length);
	पूर्ण
	dbg_level = dbg;
पूर्ण
#अन्यथा
#घोषणा dump_ptd(ptd)			करो अणुपूर्ण जबतक (0)
#घोषणा dump_ptd_in_data(ptd, buf)	करो अणुपूर्ण जबतक (0)
#घोषणा dump_ptd_out_data(ptd, buf)	करो अणुपूर्ण जबतक (0)
#घोषणा dump_ptd_data(ptd, buf)		करो अणुपूर्ण जबतक (0)
#घोषणा dump_ptd_queue(epq)		करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर
