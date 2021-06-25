<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 1999, 2000 Ralf Baechle
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 */
#अगर_अघोषित MIPS_SN_IOC3_H
#घोषणा MIPS_SN_IOC3_H

#समावेश <linux/types.h>

/* serial port रेजिस्टर map */
काष्ठा ioc3_serialregs अणु
	u32	sscr;
	u32	stpir;
	u32	stcir;
	u32	srpir;
	u32	srcir;
	u32	srtr;
	u32	shaकरोw;
पूर्ण;

/* SUPERIO uart रेजिस्टर map */
काष्ठा ioc3_uartregs अणु
	u8	iu_lcr;
	जोड़ अणु
		u8	iu_iir;	/* पढ़ो only */
		u8	iu_fcr;	/* ग_लिखो only */
	पूर्ण;
	जोड़ अणु
		u8	iu_ier;	/* DLAB == 0 */
		u8	iu_dlm;	/* DLAB == 1 */
	पूर्ण;
	जोड़ अणु
		u8	iu_rbr;	/* पढ़ो only, DLAB == 0 */
		u8	iu_thr;	/* ग_लिखो only, DLAB == 0 */
		u8	iu_dll;	/* DLAB == 1 */
	पूर्ण;
	u8	iu_scr;
	u8	iu_msr;
	u8	iu_lsr;
	u8	iu_mcr;
पूर्ण;

काष्ठा ioc3_sioregs अणु
	u8	fill[0x141];	/* starts at 0x141 */

	u8	kbdcg;
	u8	uartc;

	u8	fill0[0x151 - 0x142 - 1];

	u8	pp_dcr;
	u8	pp_dsr;
	u8	pp_data;

	u8	fill1[0x159 - 0x153 - 1];

	u8	pp_ecr;
	u8	pp_cfgb;
	u8	pp_fअगरa;

	u8	fill2[0x16a - 0x15b - 1];

	u8	rtcdat;
	u8	rtcad;

	u8	fill3[0x170 - 0x16b - 1];

	काष्ठा ioc3_uartregs	uartb;	/* 0x20170  */
	काष्ठा ioc3_uartregs	uarta;	/* 0x20178  */
पूर्ण;

काष्ठा ioc3_ethregs अणु
	u32	emcr;		/* 0x000f0  */
	u32	eisr;		/* 0x000f4  */
	u32	eier;		/* 0x000f8  */
	u32	ercsr;		/* 0x000fc  */
	u32	erbr_h;		/* 0x00100  */
	u32	erbr_l;		/* 0x00104  */
	u32	erbar;		/* 0x00108  */
	u32	ercir;		/* 0x0010c  */
	u32	erpir;		/* 0x00110  */
	u32	ertr;		/* 0x00114  */
	u32	etcsr;		/* 0x00118  */
	u32	ersr;		/* 0x0011c  */
	u32	etcdc;		/* 0x00120  */
	u32	ebir;		/* 0x00124  */
	u32	etbr_h;		/* 0x00128  */
	u32	etbr_l;		/* 0x0012c  */
	u32	etcir;		/* 0x00130  */
	u32	etpir;		/* 0x00134  */
	u32	emar_h;		/* 0x00138  */
	u32	emar_l;		/* 0x0013c  */
	u32	ehar_h;		/* 0x00140  */
	u32	ehar_l;		/* 0x00144  */
	u32	micr;		/* 0x00148  */
	u32	midr_r;		/* 0x0014c  */
	u32	midr_w;		/* 0x00150  */
पूर्ण;

काष्ठा ioc3_serioregs अणु
	u32	km_csr;		/* 0x0009c  */
	u32	k_rd;		/* 0x000a0  */
	u32	m_rd;		/* 0x000a4  */
	u32	k_wd;		/* 0x000a8  */
	u32	m_wd;		/* 0x000ac  */
पूर्ण;

/* Register layout of IOC3 in configuration space.  */
काष्ठा ioc3 अणु
	/* PCI Config Space रेजिस्टरs  */
	u32	pci_id;		/* 0x00000  */
	u32	pci_scr;	/* 0x00004  */
	u32	pci_rev;	/* 0x00008  */
	u32	pci_lat;	/* 0x0000c  */
	u32	pci_addr;	/* 0x00010  */
	u32	pci_err_addr_l;	/* 0x00014  */
	u32	pci_err_addr_h;	/* 0x00018  */

	u32	sio_ir;		/* 0x0001c  */
	u32	sio_ies;	/* 0x00020  */
	u32	sio_iec;	/* 0x00024  */
	u32	sio_cr;		/* 0x00028  */
	u32	पूर्णांक_out;	/* 0x0002c  */
	u32	mcr;		/* 0x00030  */

	/* General Purpose I/O रेजिस्टरs  */
	u32	gpcr_s;		/* 0x00034  */
	u32	gpcr_c;		/* 0x00038  */
	u32	gpdr;		/* 0x0003c  */
	u32	gppr[16];	/* 0x00040  */

	/* Parallel Port Registers  */
	u32	ppbr_h_a;	/* 0x00080  */
	u32	ppbr_l_a;	/* 0x00084  */
	u32	ppcr_a;		/* 0x00088  */
	u32	ppcr;		/* 0x0008c  */
	u32	ppbr_h_b;	/* 0x00090  */
	u32	ppbr_l_b;	/* 0x00094  */
	u32	ppcr_b;		/* 0x00098  */

	/* Keyboard and Mouse Registers	 */
	काष्ठा ioc3_serioregs	serio;

	/* Serial Port Registers  */
	u32	sbbr_h;		/* 0x000b0  */
	u32	sbbr_l;		/* 0x000b4  */
	काष्ठा ioc3_serialregs	port_a;
	काष्ठा ioc3_serialregs	port_b;

	/* Ethernet Registers */
	काष्ठा ioc3_ethregs	eth;
	u32	pad1[(0x20000 - 0x00154) / 4];

	/* SuperIO Registers  XXX */
	काष्ठा ioc3_sioregs	sregs;	/* 0x20000 */
	u32	pad2[(0x40000 - 0x20180) / 4];

	/* SSRAM Diagnostic Access */
	u32	ssram[(0x80000 - 0x40000) / 4];

	/* Bytebus device offsets
	   0x80000 -   Access to the generic devices selected with   DEV0
	   0x9FFFF     bytebus DEV_SEL_0
	   0xA0000 -   Access to the generic devices selected with   DEV1
	   0xBFFFF     bytebus DEV_SEL_1
	   0xC0000 -   Access to the generic devices selected with   DEV2
	   0xDFFFF     bytebus DEV_SEL_2
	   0xE0000 -   Access to the generic devices selected with   DEV3
	   0xFFFFF     bytebus DEV_SEL_3  */
पूर्ण;


#घोषणा PCI_LAT			0xc		/* Latency Timer */
#घोषणा PCI_SCR_DROP_MODE_EN	0x00008000	/* drop pios on parity err */
#घोषणा UARTA_BASE		0x178
#घोषणा UARTB_BASE		0x170

/*
 * Bytebus device space
 */
#घोषणा IOC3_BYTEBUS_DEV0	0x80000L
#घोषणा IOC3_BYTEBUS_DEV1	0xa0000L
#घोषणा IOC3_BYTEBUS_DEV2	0xc0000L
#घोषणा IOC3_BYTEBUS_DEV3	0xe0000L

/*
 * Ethernet RX Buffer
 */
काष्ठा ioc3_erxbuf अणु
	u32	w0;			/* first word (valid,bcnt,cksum) */
	u32	err;			/* second word various errors */
	/* next comes n bytes of padding */
	/* then the received ethernet frame itself */
पूर्ण;

#घोषणा ERXBUF_IPCKSUM_MASK	0x0000ffff
#घोषणा ERXBUF_BYTECNT_MASK	0x07ff0000
#घोषणा ERXBUF_BYTECNT_SHIFT	16
#घोषणा ERXBUF_V		0x80000000

#घोषणा ERXBUF_CRCERR		0x00000001	/* aka RSV15 */
#घोषणा ERXBUF_FRAMERR		0x00000002	/* aka RSV14 */
#घोषणा ERXBUF_CODERR		0x00000004	/* aka RSV13 */
#घोषणा ERXBUF_INVPREAMB	0x00000008	/* aka RSV18 */
#घोषणा ERXBUF_LOLEN		0x00007000	/* aka RSV2_0 */
#घोषणा ERXBUF_HILEN		0x03ff0000	/* aka RSV12_3 */
#घोषणा ERXBUF_MULTICAST	0x04000000	/* aka RSV16 */
#घोषणा ERXBUF_BROADCAST	0x08000000	/* aka RSV17 */
#घोषणा ERXBUF_LONGEVENT	0x10000000	/* aka RSV19 */
#घोषणा ERXBUF_BADPKT		0x20000000	/* aka RSV20 */
#घोषणा ERXBUF_GOODPKT		0x40000000	/* aka RSV21 */
#घोषणा ERXBUF_CARRIER		0x80000000	/* aka RSV22 */

/*
 * Ethernet TX Descriptor
 */
#घोषणा ETXD_DATALEN	104
काष्ठा ioc3_etxd अणु
	u32	cmd;				/* command field */
	u32	bufcnt;				/* buffer counts field */
	u64	p1;				/* buffer poपूर्णांकer 1 */
	u64	p2;				/* buffer poपूर्णांकer 2 */
	u8	data[ETXD_DATALEN];		/* opt. tx data */
पूर्ण;

#घोषणा ETXD_BYTECNT_MASK	0x000007ff	/* total byte count */
#घोषणा ETXD_INTWHENDONE	0x00001000	/* पूर्णांकr when करोne */
#घोषणा ETXD_D0V		0x00010000	/* data 0 valid */
#घोषणा ETXD_B1V		0x00020000	/* buf 1 valid */
#घोषणा ETXD_B2V		0x00040000	/* buf 2 valid */
#घोषणा ETXD_DOCHECKSUM		0x00080000	/* insert ip cksum */
#घोषणा ETXD_CHKOFF_MASK	0x07f00000	/* cksum byte offset */
#घोषणा ETXD_CHKOFF_SHIFT	20

#घोषणा ETXD_D0CNT_MASK		0x0000007f
#घोषणा ETXD_B1CNT_MASK		0x0007ff00
#घोषणा ETXD_B1CNT_SHIFT	8
#घोषणा ETXD_B2CNT_MASK		0x7ff00000
#घोषणा ETXD_B2CNT_SHIFT	20

/* ------------------------------------------------------------------------- */

/* Superio Registers (PIO Access) */
#घोषणा IOC3_SIO_BASE		0x20000
#घोषणा IOC3_SIO_UARTC		(IOC3_SIO_BASE+0x141)	/* UART Config */
#घोषणा IOC3_SIO_KBDCG		(IOC3_SIO_BASE+0x142)	/* KBD Config */
#घोषणा IOC3_SIO_PP_BASE	(IOC3_SIO_BASE+PP_BASE)	/* Parallel Port */
#घोषणा IOC3_SIO_RTC_BASE	(IOC3_SIO_BASE+0x168)	/* Real Time Clock */
#घोषणा IOC3_SIO_UB_BASE	(IOC3_SIO_BASE+UARTB_BASE)	/* UART B */
#घोषणा IOC3_SIO_UA_BASE	(IOC3_SIO_BASE+UARTA_BASE)	/* UART A */

/* SSRAM Diagnostic Access */
#घोषणा IOC3_SSRAM	IOC3_RAM_OFF	/* base of SSRAM diagnostic access */
#घोषणा IOC3_SSRAM_LEN	0x40000	/* 256kb (addrspc sz, may not be populated) */
#घोषणा IOC3_SSRAM_DM	0x0000ffff	/* data mask */
#घोषणा IOC3_SSRAM_PM	0x00010000	/* parity mask */

/* biपंचांगasks क्रम PCI_SCR */
#घोषणा PCI_SCR_PAR_RESP_EN	0x00000040	/* enb PCI parity checking */
#घोषणा PCI_SCR_SERR_EN		0x00000100	/* enable the SERR# driver */
#घोषणा PCI_SCR_DROP_MODE_EN	0x00008000	/* drop pios on parity err */
#घोषणा PCI_SCR_RX_SERR		(0x1 << 16)
#घोषणा PCI_SCR_DROP_MODE	(0x1 << 17)
#घोषणा PCI_SCR_SIG_PAR_ERR	(0x1 << 24)
#घोषणा PCI_SCR_SIG_TAR_ABRT	(0x1 << 27)
#घोषणा PCI_SCR_RX_TAR_ABRT	(0x1 << 28)
#घोषणा PCI_SCR_SIG_MST_ABRT	(0x1 << 29)
#घोषणा PCI_SCR_SIG_SERR	(0x1 << 30)
#घोषणा PCI_SCR_PAR_ERR		(0x1 << 31)

/* biपंचांगasks क्रम IOC3_KM_CSR */
#घोषणा KM_CSR_K_WRT_PEND 0x00000001	/* kbd port xmitting or resetting */
#घोषणा KM_CSR_M_WRT_PEND 0x00000002	/* mouse port xmitting or resetting */
#घोषणा KM_CSR_K_LCB	  0x00000004	/* Line Cntrl Bit क्रम last KBD ग_लिखो */
#घोषणा KM_CSR_M_LCB	  0x00000008	/* same क्रम mouse */
#घोषणा KM_CSR_K_DATA	  0x00000010	/* state of kbd data line */
#घोषणा KM_CSR_K_CLK	  0x00000020	/* state of kbd घड़ी line */
#घोषणा KM_CSR_K_PULL_DATA 0x00000040	/* pull kbd data line low */
#घोषणा KM_CSR_K_PULL_CLK 0x00000080	/* pull kbd घड़ी line low */
#घोषणा KM_CSR_M_DATA	  0x00000100	/* state of ms data line */
#घोषणा KM_CSR_M_CLK	  0x00000200	/* state of ms घड़ी line */
#घोषणा KM_CSR_M_PULL_DATA 0x00000400	/* pull ms data line low */
#घोषणा KM_CSR_M_PULL_CLK 0x00000800	/* pull ms घड़ी line low */
#घोषणा KM_CSR_EMM_MODE	  0x00001000	/* emulation mode */
#घोषणा KM_CSR_SIM_MODE	  0x00002000	/* घड़ी X8 */
#घोषणा KM_CSR_K_SM_IDLE  0x00004000	/* Keyboard is idle */
#घोषणा KM_CSR_M_SM_IDLE  0x00008000	/* Mouse is idle */
#घोषणा KM_CSR_K_TO	  0x00010000	/* Keyboard trying to send/receive */
#घोषणा KM_CSR_M_TO	  0x00020000	/* Mouse trying to send/receive */
#घोषणा KM_CSR_K_TO_EN	  0x00040000	/* KM_CSR_K_TO + KM_CSR_K_TO_EN = cause
					   SIO_IR to निश्चित */
#घोषणा KM_CSR_M_TO_EN	  0x00080000	/* KM_CSR_M_TO + KM_CSR_M_TO_EN = cause
					   SIO_IR to निश्चित */
#घोषणा KM_CSR_K_CLAMP_1  0x00100000	/* Pull K_CLK low aft recv 1 अक्षर */
#घोषणा KM_CSR_M_CLAMP_1  0x00200000	/* Pull M_CLK low aft recv 1 अक्षर */
#घोषणा KM_CSR_K_CLAMP_3  0x00400000	/* Pull K_CLK low aft recv 3 अक्षरs */
#घोषणा KM_CSR_M_CLAMP_3  0x00800000	/* Pull M_CLK low aft recv 3 अक्षरs */

/* biपंचांगasks क्रम IOC3_K_RD and IOC3_M_RD */
#घोषणा KM_RD_DATA_2	0x000000ff	/* 3rd अक्षर recvd since last पढ़ो */
#घोषणा KM_RD_DATA_2_SHIFT 0
#घोषणा KM_RD_DATA_1	0x0000ff00	/* 2nd अक्षर recvd since last पढ़ो */
#घोषणा KM_RD_DATA_1_SHIFT 8
#घोषणा KM_RD_DATA_0	0x00ff0000	/* 1st अक्षर recvd since last पढ़ो */
#घोषणा KM_RD_DATA_0_SHIFT 16
#घोषणा KM_RD_FRAME_ERR_2 0x01000000	/*  framing or parity error in byte 2 */
#घोषणा KM_RD_FRAME_ERR_1 0x02000000	/* same क्रम byte 1 */
#घोषणा KM_RD_FRAME_ERR_0 0x04000000	/* same क्रम byte 0 */

#घोषणा KM_RD_KBD_MSE	0x08000000	/* 0 अगर from kbd, 1 अगर from mouse */
#घोषणा KM_RD_OFLO	0x10000000	/* 4th अक्षर recvd beक्रमe this पढ़ो */
#घोषणा KM_RD_VALID_2	0x20000000	/* DATA_2 valid */
#घोषणा KM_RD_VALID_1	0x40000000	/* DATA_1 valid */
#घोषणा KM_RD_VALID_0	0x80000000	/* DATA_0 valid */
#घोषणा KM_RD_VALID_ALL (KM_RD_VALID_0|KM_RD_VALID_1|KM_RD_VALID_2)

/* biपंचांगasks क्रम IOC3_K_WD & IOC3_M_WD */
#घोषणा KM_WD_WRT_DATA	0x000000ff	/* ग_लिखो to keyboard/mouse port */
#घोषणा KM_WD_WRT_DATA_SHIFT 0

/* biपंचांगasks क्रम serial RX status byte */
#घोषणा RXSB_OVERRUN	0x01	/* अक्षर(s) lost */
#घोषणा RXSB_PAR_ERR	0x02	/* parity error */
#घोषणा RXSB_FRAME_ERR	0x04	/* framing error */
#घोषणा RXSB_BREAK	0x08	/* अवरोध अक्षरacter */
#घोषणा RXSB_CTS	0x10	/* state of CTS */
#घोषणा RXSB_DCD	0x20	/* state of DCD */
#घोषणा RXSB_MODEM_VALID 0x40	/* DCD, CTS and OVERRUN are valid */
#घोषणा RXSB_DATA_VALID 0x80	/* data byte, FRAME_ERR PAR_ERR & BREAK valid */

/* biपंचांगasks क्रम serial TX control byte */
#घोषणा TXCB_INT_WHEN_DONE 0x20 /* पूर्णांकerrupt after this byte is sent */
#घोषणा TXCB_INVALID	0x00	/* byte is invalid */
#घोषणा TXCB_VALID	0x40	/* byte is valid */
#घोषणा TXCB_MCR	0x80	/* data<7:0> to modem control रेजिस्टर */
#घोषणा TXCB_DELAY	0xc0	/* delay data<7:0> mSec */

/* biपंचांगasks क्रम IOC3_SBBR_L */
#घोषणा SBBR_L_SIZE	0x00000001	/* 0 == 1KB rings, 1 == 4KB rings */
#घोषणा SBBR_L_BASE	0xfffff000	/* lower serial ring base addr */

/* biपंचांगasks क्रम IOC3_SSCR_<A:B> */
#घोषणा SSCR_RX_THRESHOLD 0x000001ff	/* hiwater mark */
#घोषणा SSCR_TX_TIMER_BUSY 0x00010000	/* TX समयr in progress */
#घोषणा SSCR_HFC_EN	0x00020000	/* hardware flow control enabled */
#घोषणा SSCR_RX_RING_DCD 0x00040000	/* post RX record on delta-DCD */
#घोषणा SSCR_RX_RING_CTS 0x00080000	/* post RX record on delta-CTS */
#घोषणा SSCR_HIGH_SPD	0x00100000	/* 4X speed */
#घोषणा SSCR_DIAG	0x00200000	/* bypass घड़ी भागider क्रम sim */
#घोषणा SSCR_RX_DRAIN	0x08000000	/* drain RX buffer to memory */
#घोषणा SSCR_DMA_EN	0x10000000	/* enable ring buffer DMA */
#घोषणा SSCR_DMA_PAUSE	0x20000000	/* छोड़ो DMA */
#घोषणा SSCR_PAUSE_STATE 0x40000000	/* sets when PAUSE takes effect */
#घोषणा SSCR_RESET	0x80000000	/* reset DMA channels */

/* all producer/consumer poपूर्णांकers are the same bitfield */
#घोषणा PROD_CONS_PTR_4K 0x00000ff8	/* क्रम 4K buffers */
#घोषणा PROD_CONS_PTR_1K 0x000003f8	/* क्रम 1K buffers */
#घोषणा PROD_CONS_PTR_OFF 3

/* biपंचांगasks क्रम IOC3_SRCIR_<A:B> */
#घोषणा SRCIR_ARM	0x80000000	/* arm RX समयr */

/* biपंचांगasks क्रम IOC3_SRPIR_<A:B> */
#घोषणा SRPIR_BYTE_CNT	0x07000000	/* bytes in packer */
#घोषणा SRPIR_BYTE_CNT_SHIFT 24

/* biपंचांगasks क्रम IOC3_STCIR_<A:B> */
#घोषणा STCIR_BYTE_CNT	0x0f000000	/* bytes in unpacker */
#घोषणा STCIR_BYTE_CNT_SHIFT 24

/* biपंचांगasks क्रम IOC3_SHADOW_<A:B> */
#घोषणा SHADOW_DR	0x00000001	/* data पढ़ोy */
#घोषणा SHADOW_OE	0x00000002	/* overrun error */
#घोषणा SHADOW_PE	0x00000004	/* parity error */
#घोषणा SHADOW_FE	0x00000008	/* framing error */
#घोषणा SHADOW_BI	0x00000010	/* अवरोध पूर्णांकerrupt */
#घोषणा SHADOW_THRE	0x00000020	/* transmit holding रेजिस्टर empty */
#घोषणा SHADOW_TEMT	0x00000040	/* transmit shअगरt रेजिस्टर empty */
#घोषणा SHADOW_RFCE	0x00000080	/* अक्षर in RX fअगरo has an error */
#घोषणा SHADOW_DCTS	0x00010000	/* delta clear to send */
#घोषणा SHADOW_DDCD	0x00080000	/* delta data carrier detect */
#घोषणा SHADOW_CTS	0x00100000	/* clear to send */
#घोषणा SHADOW_DCD	0x00800000	/* data carrier detect */
#घोषणा SHADOW_DTR	0x01000000	/* data terminal पढ़ोy */
#घोषणा SHADOW_RTS	0x02000000	/* request to send */
#घोषणा SHADOW_OUT1	0x04000000	/* 16550 OUT1 bit */
#घोषणा SHADOW_OUT2	0x08000000	/* 16550 OUT2 bit */
#घोषणा SHADOW_LOOP	0x10000000	/* loopback enabled */

/* biपंचांगasks क्रम IOC3_SRTR_<A:B> */
#घोषणा SRTR_CNT	0x00000fff	/* reload value क्रम RX समयr */
#घोषणा SRTR_CNT_VAL	0x0fff0000	/* current value of RX समयr */
#घोषणा SRTR_CNT_VAL_SHIFT 16
#घोषणा SRTR_HZ		16000	/* SRTR घड़ी frequency */

/* biपंचांगasks क्रम IOC3_SIO_IR, IOC3_SIO_IEC and IOC3_SIO_IES  */
#घोषणा SIO_IR_SA_TX_MT		0x00000001	/* Serial port A TX empty */
#घोषणा SIO_IR_SA_RX_FULL	0x00000002	/* port A RX buf full */
#घोषणा SIO_IR_SA_RX_HIGH	0x00000004	/* port A RX hiwat */
#घोषणा SIO_IR_SA_RX_TIMER	0x00000008	/* port A RX समयout */
#घोषणा SIO_IR_SA_DELTA_DCD	0x00000010	/* port A delta DCD */
#घोषणा SIO_IR_SA_DELTA_CTS	0x00000020	/* port A delta CTS */
#घोषणा SIO_IR_SA_INT		0x00000040	/* port A pass-thru पूर्णांकr */
#घोषणा SIO_IR_SA_TX_EXPLICIT	0x00000080	/* port A explicit TX thru */
#घोषणा SIO_IR_SA_MEMERR	0x00000100	/* port A PCI error */
#घोषणा SIO_IR_SB_TX_MT		0x00000200	/* */
#घोषणा SIO_IR_SB_RX_FULL	0x00000400	/* */
#घोषणा SIO_IR_SB_RX_HIGH	0x00000800	/* */
#घोषणा SIO_IR_SB_RX_TIMER	0x00001000	/* */
#घोषणा SIO_IR_SB_DELTA_DCD	0x00002000	/* */
#घोषणा SIO_IR_SB_DELTA_CTS	0x00004000	/* */
#घोषणा SIO_IR_SB_INT		0x00008000	/* */
#घोषणा SIO_IR_SB_TX_EXPLICIT	0x00010000	/* */
#घोषणा SIO_IR_SB_MEMERR	0x00020000	/* */
#घोषणा SIO_IR_PP_INT		0x00040000	/* P port pass-thru पूर्णांकr */
#घोषणा SIO_IR_PP_INTA		0x00080000	/* PP context A thru */
#घोषणा SIO_IR_PP_INTB		0x00100000	/* PP context B thru */
#घोषणा SIO_IR_PP_MEMERR	0x00200000	/* PP PCI error */
#घोषणा SIO_IR_KBD_INT		0x00400000	/* kbd/mouse पूर्णांकr */
#घोषणा SIO_IR_RT_INT		0x08000000	/* RT output pulse */
#घोषणा SIO_IR_GEN_INT1		0x10000000	/* RT input pulse */
#घोषणा SIO_IR_GEN_INT_SHIFT	28

/* per device पूर्णांकerrupt masks */
#घोषणा SIO_IR_SA		(SIO_IR_SA_TX_MT | SIO_IR_SA_RX_FULL | \
				 SIO_IR_SA_RX_HIGH | SIO_IR_SA_RX_TIMER | \
				 SIO_IR_SA_DELTA_DCD | SIO_IR_SA_DELTA_CTS | \
				 SIO_IR_SA_INT | SIO_IR_SA_TX_EXPLICIT | \
				 SIO_IR_SA_MEMERR)
#घोषणा SIO_IR_SB		(SIO_IR_SB_TX_MT | SIO_IR_SB_RX_FULL | \
				 SIO_IR_SB_RX_HIGH | SIO_IR_SB_RX_TIMER | \
				 SIO_IR_SB_DELTA_DCD | SIO_IR_SB_DELTA_CTS | \
				 SIO_IR_SB_INT | SIO_IR_SB_TX_EXPLICIT | \
				 SIO_IR_SB_MEMERR)
#घोषणा SIO_IR_PP		(SIO_IR_PP_INT | SIO_IR_PP_INTA | \
				 SIO_IR_PP_INTB | SIO_IR_PP_MEMERR)
#घोषणा SIO_IR_RT		(SIO_IR_RT_INT | SIO_IR_GEN_INT1)

/* biपंचांगasks क्रम SIO_CR */
#घोषणा SIO_CR_SIO_RESET	0x00000001	/* reset the SIO */
#घोषणा SIO_CR_SER_A_BASE	0x000000fe	/* DMA poll addr port A */
#घोषणा SIO_CR_SER_A_BASE_SHIFT 1
#घोषणा SIO_CR_SER_B_BASE	0x00007f00	/* DMA poll addr port B */
#घोषणा SIO_CR_SER_B_BASE_SHIFT 8
#घोषणा SIO_SR_CMD_PULSE	0x00078000	/* byte bus strobe length */
#घोषणा SIO_CR_CMD_PULSE_SHIFT	15
#घोषणा SIO_CR_ARB_DIAG		0x00380000	/* cur !enet PCI requet (ro) */
#घोषणा SIO_CR_ARB_DIAG_TXA	0x00000000
#घोषणा SIO_CR_ARB_DIAG_RXA	0x00080000
#घोषणा SIO_CR_ARB_DIAG_TXB	0x00100000
#घोषणा SIO_CR_ARB_DIAG_RXB	0x00180000
#घोषणा SIO_CR_ARB_DIAG_PP	0x00200000
#घोषणा SIO_CR_ARB_DIAG_IDLE	0x00400000	/* 0 -> active request (ro) */

/* biपंचांगasks क्रम INT_OUT */
#घोषणा INT_OUT_COUNT	0x0000ffff	/* pulse पूर्णांकerval समयr */
#घोषणा INT_OUT_MODE	0x00070000	/* mode mask */
#घोषणा INT_OUT_MODE_0	0x00000000	/* set output to 0 */
#घोषणा INT_OUT_MODE_1	0x00040000	/* set output to 1 */
#घोषणा INT_OUT_MODE_1PULSE 0x00050000	/* send 1 pulse */
#घोषणा INT_OUT_MODE_PULSES 0x00060000	/* send 1 pulse every पूर्णांकerval */
#घोषणा INT_OUT_MODE_SQW 0x00070000	/* toggle output every पूर्णांकerval */
#घोषणा INT_OUT_DIAG	0x40000000	/* diag mode */
#घोषणा INT_OUT_INT_OUT 0x80000000	/* current state of INT_OUT */

/* समय स्थिरants क्रम INT_OUT */
#घोषणा INT_OUT_NS_PER_TICK (30 * 260)	/* 30 ns PCI घड़ी, भागisor=260 */
#घोषणा INT_OUT_TICKS_PER_PULSE 3	/* outgoing pulse lasts 3 ticks */
#घोषणा INT_OUT_US_TO_COUNT(x)		/* convert uS to a count value */ \
	(((x) * 10 + INT_OUT_NS_PER_TICK / 200) *	\
	 100 / INT_OUT_NS_PER_TICK - 1)
#घोषणा INT_OUT_COUNT_TO_US(x)		/* convert count value to uS */ \
	(((x) + 1) * INT_OUT_NS_PER_TICK / 1000)
#घोषणा INT_OUT_MIN_TICKS 3	/* min period is width of pulse in "ticks" */
#घोषणा INT_OUT_MAX_TICKS INT_OUT_COUNT		/* largest possible count */

/* biपंचांगasks क्रम GPCR */
#घोषणा GPCR_सूची	0x000000ff	/* tristate pin input or output */
#घोषणा GPCR_सूची_PIN(x) (1<<(x))	/* access one of the सूची bits */
#घोषणा GPCR_EDGE	0x000f0000	/* extपूर्णांक edge or level sensitive */
#घोषणा GPCR_EDGE_PIN(x) (1<<((x)+15))	/* access one of the EDGE bits */

/* values क्रम GPCR */
#घोषणा GPCR_INT_OUT_EN 0x00100000	/* enable INT_OUT to pin 0 */
#घोषणा GPCR_MLAN_EN	0x00200000	/* enable MCR to pin 8 */
#घोषणा GPCR_सूची_SERA_XCVR 0x00000080	/* Port A Transceiver select enable */
#घोषणा GPCR_सूची_SERB_XCVR 0x00000040	/* Port B Transceiver select enable */
#घोषणा GPCR_सूची_PHY_RST   0x00000020	/* ethernet PHY reset enable */

/* defs क्रम some of the generic I/O pins */
#घोषणा GPCR_PHY_RESET		0x20	/* pin is output to PHY reset */
#घोषणा GPCR_UARTB_MODESEL	0x40	/* pin is output to port B mode sel */
#घोषणा GPCR_UARTA_MODESEL	0x80	/* pin is output to port A mode sel */

#घोषणा GPPR_PHY_RESET_PIN	5	/* GIO pin cntrlling phy reset */
#घोषणा GPPR_UARTB_MODESEL_PIN	6	/* GIO pin cntrlling uart b mode sel */
#घोषणा GPPR_UARTA_MODESEL_PIN	7	/* GIO pin cntrlling uart a mode sel */

/* ethernet */
#घोषणा EMCR_DUPLEX		0x00000001
#घोषणा EMCR_PROMISC		0x00000002
#घोषणा EMCR_PADEN		0x00000004
#घोषणा EMCR_RXOFF_MASK		0x000001f8
#घोषणा EMCR_RXOFF_SHIFT	3
#घोषणा EMCR_RAMPAR		0x00000200
#घोषणा EMCR_BADPAR		0x00000800
#घोषणा EMCR_बफ_मान		0x00001000
#घोषणा EMCR_TXDMAEN		0x00002000
#घोषणा EMCR_TXEN		0x00004000
#घोषणा EMCR_RXDMAEN		0x00008000
#घोषणा EMCR_RXEN		0x00010000
#घोषणा EMCR_LOOPBACK		0x00020000
#घोषणा EMCR_ARB_DIAG		0x001c0000
#घोषणा EMCR_ARB_DIAG_IDLE	0x00200000
#घोषणा EMCR_RST		0x80000000

#घोषणा EISR_RXTIMERINT		0x00000001
#घोषणा EISR_RXTHRESHINT	0x00000002
#घोषणा EISR_RXOFLO		0x00000004
#घोषणा EISR_RXBUFOFLO		0x00000008
#घोषणा EISR_RXMEMERR		0x00000010
#घोषणा EISR_RXPARERR		0x00000020
#घोषणा EISR_TXEMPTY		0x00010000
#घोषणा EISR_TXRTRY		0x00020000
#घोषणा EISR_TXEXDEF		0x00040000
#घोषणा EISR_TXLCOL		0x00080000
#घोषणा EISR_TXGIANT		0x00100000
#घोषणा EISR_TXBUFUFLO		0x00200000
#घोषणा EISR_TXEXPLICIT		0x00400000
#घोषणा EISR_TXCOLLWRAP		0x00800000
#घोषणा EISR_TXDEFERWRAP	0x01000000
#घोषणा EISR_TXMEMERR		0x02000000
#घोषणा EISR_TXPARERR		0x04000000

#घोषणा ERCSR_THRESH_MASK	0x000001ff	/* enet RX threshold */
#घोषणा ERCSR_RX_TMR		0x40000000	/* simulation only */
#घोषणा ERCSR_DIAG_OFLO		0x80000000	/* simulation only */

#घोषणा ERBR_ALIGNMENT		4096
#घोषणा ERBR_L_RXRINGBASE_MASK	0xfffff000

#घोषणा ERBAR_BARRIER_BIT	0x0100
#घोषणा ERBAR_RXBARR_MASK	0xffff0000
#घोषणा ERBAR_RXBARR_SHIFT	16

#घोषणा ERCIR_RXCONSUME_MASK	0x00000fff

#घोषणा ERPIR_RXPRODUCE_MASK	0x00000fff
#घोषणा ERPIR_ARM		0x80000000

#घोषणा ERTR_CNT_MASK		0x000007ff

#घोषणा ETCSR_IPGT_MASK		0x0000007f
#घोषणा ETCSR_IPGR1_MASK	0x00007f00
#घोषणा ETCSR_IPGR1_SHIFT	8
#घोषणा ETCSR_IPGR2_MASK	0x007f0000
#घोषणा ETCSR_IPGR2_SHIFT	16
#घोषणा ETCSR_NOTXCLK		0x80000000

#घोषणा ETCDC_COLLCNT_MASK	0x0000ffff
#घोषणा ETCDC_DEFERCNT_MASK	0xffff0000
#घोषणा ETCDC_DEFERCNT_SHIFT	16

#घोषणा ETBR_ALIGNMENT		(64*1024)
#घोषणा ETBR_L_RINGSZ_MASK	0x00000001
#घोषणा ETBR_L_RINGSZ128	0
#घोषणा ETBR_L_RINGSZ512	1
#घोषणा ETBR_L_TXRINGBASE_MASK	0xffffc000

#घोषणा ETCIR_TXCONSUME_MASK	0x0000ffff
#घोषणा ETCIR_IDLE		0x80000000

#घोषणा ETPIR_TXPRODUCE_MASK	0x0000ffff

#घोषणा EBIR_TXBUFPROD_MASK	0x0000001f
#घोषणा EBIR_TXBUFCONS_MASK	0x00001f00
#घोषणा EBIR_TXBUFCONS_SHIFT	8
#घोषणा EBIR_RXBUFPROD_MASK	0x007fc000
#घोषणा EBIR_RXBUFPROD_SHIFT	14
#घोषणा EBIR_RXBUFCONS_MASK	0xff800000
#घोषणा EBIR_RXBUFCONS_SHIFT	23

#घोषणा MICR_REGADDR_MASK	0x0000001f
#घोषणा MICR_PHYADDR_MASK	0x000003e0
#घोषणा MICR_PHYADDR_SHIFT	5
#घोषणा MICR_READTRIG		0x00000400
#घोषणा MICR_BUSY		0x00000800

#घोषणा MIDR_DATA_MASK		0x0000ffff

/* subप्रणाली IDs supplied by card detection in pci-xtalk-bridge */
#घोषणा	IOC3_SUBSYS_IP27_BASEIO6G	0xc300
#घोषणा	IOC3_SUBSYS_IP27_MIO		0xc301
#घोषणा	IOC3_SUBSYS_IP27_BASEIO		0xc302
#घोषणा	IOC3_SUBSYS_IP29_SYSBOARD	0xc303
#घोषणा	IOC3_SUBSYS_IP30_SYSBOARD	0xc304
#घोषणा	IOC3_SUBSYS_MENET		0xc305
#घोषणा	IOC3_SUBSYS_MENET4		0xc306
#घोषणा	IOC3_SUBSYS_IO7			0xc307
#घोषणा	IOC3_SUBSYS_IO8			0xc308
#घोषणा	IOC3_SUBSYS_IO9			0xc309
#घोषणा	IOC3_SUBSYS_IP34_SYSBOARD	0xc30A

#पूर्ण_अगर /* MIPS_SN_IOC3_H */
