<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * SL811HS रेजिस्टर declarations and HCD data काष्ठाures
 *
 * Copyright (C) 2004 Psion Teklogix
 * Copyright (C) 2004 David Brownell
 * Copyright (C) 2001 Cypress Semiconductor Inc. 
 */

/*
 * SL811HS has transfer रेजिस्टरs, and control रेजिस्टरs.  In host/master
 * mode one set of रेजिस्टरs is used; in peripheral/slave mode, another.
 *  - SL11H only has some "A" transfer रेजिस्टरs from 0x00-0x04
 *  - SL811HS also has "B" रेजिस्टरs from 0x08-0x0c
 *  - SL811S (or HS in slave mode) has four A+B sets, at 00, 10, 20, 30
 */

#घोषणा SL811_EP_A(base)	((base) + 0)
#घोषणा SL811_EP_B(base)	((base) + 8)

#घोषणा SL811_HOST_BUF		0x00
#घोषणा SL811_PERIPH_EP0	0x00
#घोषणा SL811_PERIPH_EP1	0x10
#घोषणा SL811_PERIPH_EP2	0x20
#घोषणा SL811_PERIPH_EP3	0x30


/* TRANSFER REGISTERS:  host and peripheral sides are similar
 * except क्रम the control models (master vs slave).
 */
#घोषणा SL11H_HOSTCTLREG	0
#	define SL11H_HCTLMASK_ARM	0x01
#	define SL11H_HCTLMASK_ENABLE	0x02
#	define SL11H_HCTLMASK_IN	0x00
#	define SL11H_HCTLMASK_OUT	0x04
#	define SL11H_HCTLMASK_ISOCH	0x10
#	define SL11H_HCTLMASK_AFTERSOF	0x20
#	define SL11H_HCTLMASK_TOGGLE	0x40
#	define SL11H_HCTLMASK_PREAMBLE	0x80
#घोषणा SL11H_BUFADDRREG	1
#घोषणा SL11H_BUFLNTHREG	2
#घोषणा SL11H_PKTSTATREG	3	/* पढ़ो */
#	define SL11H_STATMASK_ACK	0x01
#	define SL11H_STATMASK_ERROR	0x02
#	define SL11H_STATMASK_TMOUT	0x04
#	define SL11H_STATMASK_SEQ	0x08
#	define SL11H_STATMASK_SETUP	0x10
#	define SL11H_STATMASK_OVF	0x20
#	define SL11H_STATMASK_NAK	0x40
#	define SL11H_STATMASK_STALL	0x80
#घोषणा SL11H_PIDEPREG		3	/* ग_लिखो */
#	define	SL_SETUP	0xd0
#	define	SL_IN		0x90
#	define	SL_OUT		0x10
#	define	SL_SOF		0x50
#	define	SL_PREAMBLE	0xc0
#	define	SL_NAK		0xa0
#	define	SL_STALL	0xe0
#	define	SL_DATA0	0x30
#	define	SL_DATA1	0xb0
#घोषणा SL11H_XFERCNTREG	4	/* पढ़ो */
#घोषणा SL11H_DEVADDRREG	4	/* ग_लिखो */


/* CONTROL REGISTERS:  host and peripheral are very dअगरferent.
 */
#घोषणा SL11H_CTLREG1		5
#	define SL11H_CTL1MASK_SOF_ENA	0x01
#	define SL11H_CTL1MASK_FORCE	0x18
#		define SL11H_CTL1MASK_NORMAL	0x00
#		define SL11H_CTL1MASK_SE0	0x08	/* reset */
#		define SL11H_CTL1MASK_J		0x10
#		define SL11H_CTL1MASK_K		0x18	/* resume */
#	define SL11H_CTL1MASK_LSPD	0x20
#	define SL11H_CTL1MASK_SUSPEND	0x40
#घोषणा SL11H_IRQ_ENABLE	6
#	define SL11H_INTMASK_DONE_A	0x01
#	define SL11H_INTMASK_DONE_B	0x02
#	define SL11H_INTMASK_SOFINTR	0x10
#	define SL11H_INTMASK_INSRMV	0x20	/* to/from SE0 */
#	define SL11H_INTMASK_RD		0x40
#	define SL11H_INTMASK_DP		0x80	/* only in INTSTATREG */
#घोषणा SL11S_ADDRESS		7

/* 0x08-0x0c are क्रम the B buffer (not in SL11) */

#घोषणा SL11H_IRQ_STATUS	0x0D	/* ग_लिखो to ack */
#घोषणा SL11H_HWREVREG		0x0E	/* पढ़ो */
#	define SL11H_HWRMASK_HWREV	0xF0
#घोषणा SL11H_SOFLOWREG		0x0E	/* ग_लिखो */
#घोषणा SL11H_SOFTMRREG		0x0F	/* पढ़ो */

/* a ग_लिखो to this रेजिस्टर enables SL811HS features.
 * HOST flag presumably overrides the chip input संकेत?
 */
#घोषणा SL811HS_CTLREG2		0x0F
#	define SL811HS_CTL2MASK_SOF_MASK	0x3F
#	define SL811HS_CTL2MASK_DSWAP		0x40
#	define SL811HS_CTL2MASK_HOST		0x80

#घोषणा SL811HS_CTL2_INIT	(SL811HS_CTL2MASK_HOST | 0x2e)


/* DATA BUFFERS: रेजिस्टरs from 0x10..0xff are क्रम data buffers;
 * that's 240 bytes, which we'll split evenly between A and B sides.
 * Only ISO can use more than 64 bytes per packet.
 * (The SL11S has 0x40..0xff क्रम buffers.)
 */
#घोषणा H_MAXPACKET	120		/* bytes in A or B fअगरos */

#घोषणा SL11H_DATA_START	0x10
#घोषणा	SL811HS_PACKET_BUF(is_a)	((is_a) \
		? SL11H_DATA_START \
		: (SL11H_DATA_START + H_MAXPACKET))

/*-------------------------------------------------------------------------*/

#घोषणा	LOG2_PERIODIC_SIZE	5	/* arbitrary; this matches OHCI */
#घोषणा	PERIODIC_SIZE		(1 << LOG2_PERIODIC_SIZE)

काष्ठा sl811 अणु
	spinlock_t		lock;
	व्योम __iomem		*addr_reg;
	व्योम __iomem		*data_reg;
	काष्ठा sl811_platक्रमm_data	*board;

	अचिन्हित दीर्घ		stat_insrmv;
	अचिन्हित दीर्घ		stat_wake;
	अचिन्हित दीर्घ		stat_sof;
	अचिन्हित दीर्घ		stat_a;
	अचिन्हित दीर्घ		stat_b;
	अचिन्हित दीर्घ		stat_lost;
	अचिन्हित दीर्घ		stat_overrun;

	/* sw model */
	काष्ठा समयr_list	समयr;
	काष्ठा sl811h_ep	*next_periodic;
	काष्ठा sl811h_ep	*next_async;

	काष्ठा sl811h_ep	*active_a;
	अचिन्हित दीर्घ		jअगरfies_a;
	काष्ठा sl811h_ep	*active_b;
	अचिन्हित दीर्घ		jअगरfies_b;

	u32			port1;
	u8			ctrl1, ctrl2, irq_enable;
	u16			frame;

	/* async schedule: control, bulk */
	काष्ठा list_head	async;

	/* periodic schedule: पूर्णांकerrupt, iso */
	u16			load[PERIODIC_SIZE];
	काष्ठा sl811h_ep	*periodic[PERIODIC_SIZE];
	अचिन्हित		periodic_count;
पूर्ण;

अटल अंतरभूत काष्ठा sl811 *hcd_to_sl811(काष्ठा usb_hcd *hcd)
अणु
	वापस (काष्ठा sl811 *) (hcd->hcd_priv);
पूर्ण

अटल अंतरभूत काष्ठा usb_hcd *sl811_to_hcd(काष्ठा sl811 *sl811)
अणु
	वापस container_of((व्योम *) sl811, काष्ठा usb_hcd, hcd_priv);
पूर्ण

काष्ठा sl811h_ep अणु
	काष्ठा usb_host_endpoपूर्णांक *hep;
	काष्ठा usb_device	*udev;

	u8			defctrl;
	u8			maxpacket;
	u8			epnum;
	u8			nextpid;

	u16			error_count;
	u16			nak_count;
	u16			length;		/* of current packet */

	/* periodic schedule */
	u16			period;
	u16			branch;
	u16			load;
	काष्ठा sl811h_ep	*next;

	/* async schedule */
	काष्ठा list_head	schedule;
पूर्ण;

/*-------------------------------------------------------------------------*/

/* These रेजिस्टर utilities should work क्रम the SL811S रेजिस्टर API too
 * NOTE:  caller must hold sl811->lock.
 */

अटल अंतरभूत u8 sl811_पढ़ो(काष्ठा sl811 *sl811, पूर्णांक reg)
अणु
	ग_लिखोb(reg, sl811->addr_reg);
	वापस पढ़ोb(sl811->data_reg);
पूर्ण

अटल अंतरभूत व्योम sl811_ग_लिखो(काष्ठा sl811 *sl811, पूर्णांक reg, u8 val)
अणु
	ग_लिखोb(reg, sl811->addr_reg);
	ग_लिखोb(val, sl811->data_reg);
पूर्ण

अटल अंतरभूत व्योम
sl811_ग_लिखो_buf(काष्ठा sl811 *sl811, पूर्णांक addr, स्थिर व्योम *buf, माप_प्रकार count)
अणु
	स्थिर u8	*data;
	व्योम __iomem	*data_reg;

	अगर (!count)
		वापस;
	ग_लिखोb(addr, sl811->addr_reg);

	data = buf;
	data_reg = sl811->data_reg;
	करो अणु
		ग_लिखोb(*data++, data_reg);
	पूर्ण जबतक (--count);
पूर्ण

अटल अंतरभूत व्योम
sl811_पढ़ो_buf(काष्ठा sl811 *sl811, पूर्णांक addr, व्योम *buf, माप_प्रकार count)
अणु
	u8 		*data;
	व्योम __iomem	*data_reg;

	अगर (!count)
		वापस;
	ग_लिखोb(addr, sl811->addr_reg);

	data = buf;
	data_reg = sl811->data_reg;
	करो अणु
		*data++ = पढ़ोb(data_reg);
	पूर्ण जबतक (--count);
पूर्ण

/*-------------------------------------------------------------------------*/

#अगर_घोषित PACKET_TRACE
#    define PACKET		pr_debug("sl811: "stuff)
#अन्यथा
#    define PACKET(stuff...)	करोअणुपूर्णजबतक(0)
#पूर्ण_अगर
