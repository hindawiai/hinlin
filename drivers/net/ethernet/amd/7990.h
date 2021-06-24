<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * 7990.h -- LANCE ethernet IC generic routines.
 * This is an attempt to separate out the bits of various ethernet
 * drivers that are common because they all use the AMD 7990 LANCE
 * (Local Area Network Controller क्रम Ethernet) chip.
 *
 * Copyright (C) 05/1998 Peter Maydell <pmaydell@chiark.greenend.org.uk>
 *
 * Most of this stuff was obtained by looking at other LANCE drivers,
 * in particular a2065.[ch]. The AMD C-LANCE datasheet was also helpful.
 */

#अगर_अघोषित _7990_H
#घोषणा _7990_H

/* The lance only has two रेजिस्टर locations. We communicate mostly via memory. */
#घोषणा LANCE_RDP	0	/* Register Data Port */
#घोषणा LANCE_RAP	2	/* Register Address Port */

/* Transmit/receive ring definitions.
 * We allow the specअगरic drivers to override these शेषs अगर they want to.
 * NB: according to lance.c, increasing the number of buffers is a waste
 * of space and reduces the chance that an upper layer will be able to
 * reorder queued Tx packets based on priority. [Clearly there is a minimum
 * limit too: too small and we drop rx packets and can't tx at full speed.]
 * 4+4 seems to be the usual setting; the atarilance driver uses 3 and 5.
 */

/* Blast! This won't work. The problem is that we can't specअगरy a शेष
 * setting because that would cause the lance_init_block काष्ठा to be
 * too दीर्घ (and overflow the RAM on shared-memory cards like the HP LANCE.
 */
#अगर_अघोषित LANCE_LOG_TX_BUFFERS
#घोषणा LANCE_LOG_TX_BUFFERS 1
#घोषणा LANCE_LOG_RX_BUFFERS 3
#पूर्ण_अगर

#घोषणा TX_RING_SIZE		(1 << LANCE_LOG_TX_BUFFERS)
#घोषणा RX_RING_SIZE		(1 << LANCE_LOG_RX_BUFFERS)
#घोषणा TX_RING_MOD_MASK	(TX_RING_SIZE - 1)
#घोषणा RX_RING_MOD_MASK	(RX_RING_SIZE - 1)
#घोषणा TX_RING_LEN_BITS	((LANCE_LOG_TX_BUFFERS) << 29)
#घोषणा RX_RING_LEN_BITS	((LANCE_LOG_RX_BUFFERS) << 29)
#घोषणा PKT_BUFF_SIZE		(1544)
#घोषणा RX_BUFF_SIZE		PKT_BUFF_SIZE
#घोषणा TX_BUFF_SIZE		PKT_BUFF_SIZE

/* Each receive buffer is described by a receive message descriptor (RMD) */
काष्ठा lance_rx_desc अणु
	अस्थिर अचिन्हित लघु rmd0;	    /* low address of packet */
	अस्थिर अचिन्हित अक्षर  rmd1_bits;  /* descriptor bits */
	अस्थिर अचिन्हित अक्षर  rmd1_hadr;  /* high address of packet */
	अस्थिर लघु    length;	    /* This length is 2s complement (negative)!
					     * Buffer length */
	अस्थिर अचिन्हित लघु mblength;   /* Actual number of bytes received */
पूर्ण;

/* Ditto क्रम TMD: */
काष्ठा lance_tx_desc अणु
	अस्थिर अचिन्हित लघु पंचांगd0;	    /* low address of packet */
	अस्थिर अचिन्हित अक्षर  पंचांगd1_bits;  /* descriptor bits */
	अस्थिर अचिन्हित अक्षर  पंचांगd1_hadr;  /* high address of packet */
	अस्थिर लघु    length;	    /* Length is 2s complement (negative)! */
	अस्थिर अचिन्हित लघु misc;
पूर्ण;

/* There are three memory काष्ठाures accessed by the LANCE:
 * the initialization block, the receive and transmit descriptor rings,
 * and the data buffers themselves. In fact we might as well put the
 * init block,the Tx and Rx rings and the buffers together in memory:
 */
काष्ठा lance_init_block अणु
	अस्थिर अचिन्हित लघु mode;		/* Pre-set mode (reg. 15) */
	अस्थिर अचिन्हित अक्षर phys_addr[6];	/* Physical ethernet address */
	अस्थिर अचिन्हित filter[2];		/* Multicast filter (64 bits) */

	/* Receive and transmit ring base, aदीर्घ with extra bits. */
	अस्थिर अचिन्हित लघु rx_ptr;		/* receive descriptor addr */
	अस्थिर अचिन्हित लघु rx_len;		/* receive len and high addr */
	अस्थिर अचिन्हित लघु tx_ptr;		/* transmit descriptor addr */
	अस्थिर अचिन्हित लघु tx_len;		/* transmit len and high addr */

	/* The Tx and Rx ring entries must be aligned on 8-byte boundaries.
	 * This will be true अगर this whole काष्ठा is 8-byte aligned.
	 */
	अस्थिर काष्ठा lance_tx_desc btx_ring[TX_RING_SIZE];
	अस्थिर काष्ठा lance_rx_desc brx_ring[RX_RING_SIZE];

	अस्थिर अक्षर tx_buf[TX_RING_SIZE][TX_BUFF_SIZE];
	अस्थिर अक्षर rx_buf[RX_RING_SIZE][RX_BUFF_SIZE];
	/* we use this just to make the काष्ठा big enough that we can move its startaddr
	 * in order to क्रमce alignment to an eight byte boundary.
	 */
पूर्ण;

/* This is where we keep all the stuff the driver needs to know about.
 * I'm definitely unhappy about the mechanism क्रम allowing specअगरic
 * drivers to add things...
 */
काष्ठा lance_निजी अणु
	स्थिर अक्षर *name;
	अचिन्हित दीर्घ base;
	अस्थिर काष्ठा lance_init_block *init_block; /* CPU address of RAM */
	अस्थिर काष्ठा lance_init_block *lance_init_block; /* LANCE address of RAM */

	पूर्णांक rx_new, tx_new;
	पूर्णांक rx_old, tx_old;

	पूर्णांक lance_log_rx_bufs, lance_log_tx_bufs;
	पूर्णांक rx_ring_mod_mask, tx_ring_mod_mask;

	पूर्णांक tpe;			/* TPE is selected */
	पूर्णांक स्वतः_select;		/* cable-selection is by carrier */
	अचिन्हित लघु busmaster_regval;

	अचिन्हित पूर्णांक irq;		/* IRQ to रेजिस्टर */

	/* This is because the HP LANCE is disgusting and you have to check
	 * a DIO-specअगरic रेजिस्टर every समय you पढ़ो/ग_लिखो the LANCE regs :-<
	 * [could we get away with making these some sort of macro?]
	 */
	व्योम (*ग_लिखोrap)(व्योम *, अचिन्हित लघु);
	व्योम (*ग_लिखोrdp)(व्योम *, अचिन्हित लघु);
	अचिन्हित लघु (*पढ़ोrdp)(व्योम *);
	spinlock_t devlock;
	अक्षर tx_full;
पूर्ण;

/*
 *		Am7990 Control and Status Registers
 */
#घोषणा LE_CSR0		0x0000	/* LANCE Controller Status */
#घोषणा LE_CSR1		0x0001	/* IADR[15:0] (bit0==0 ie word aligned) */
#घोषणा LE_CSR2		0x0002	/* IADR[23:16] (high bits reserved) */
#घोषणा LE_CSR3		0x0003	/* Misc */

/*
 *		Bit definitions क्रम CSR0 (LANCE Controller Status)
 */
#घोषणा LE_C0_ERR	0x8000	/* Error = BABL | CERR | MISS | MERR */
#घोषणा LE_C0_BABL	0x4000	/* Babble: Transmitted too many bits */
#घोषणा LE_C0_CERR	0x2000	/* No Heartbeat (10BASE-T) */
#घोषणा LE_C0_MISS	0x1000	/* Missed Frame (no rx buffer to put it in) */
#घोषणा LE_C0_MERR	0x0800	/* Memory Error */
#घोषणा LE_C0_RINT	0x0400	/* Receive Interrupt */
#घोषणा LE_C0_TINT	0x0200	/* Transmit Interrupt */
#घोषणा LE_C0_IDON	0x0100	/* Initialization Done */
#घोषणा LE_C0_INTR	0x0080	/* Interrupt Flag
				   = BABL | MISS | MERR | RINT | TINT | IDON */
#घोषणा LE_C0_INEA	0x0040	/* Interrupt Enable */
#घोषणा LE_C0_RXON	0x0020	/* Receive On */
#घोषणा LE_C0_TXON	0x0010	/* Transmit On */
#घोषणा LE_C0_TDMD	0x0008	/* Transmit Demand */
#घोषणा LE_C0_STOP	0x0004	/* Stop */
#घोषणा LE_C0_STRT	0x0002	/* Start */
#घोषणा LE_C0_INIT	0x0001	/* Initialize */


/*
 *		Bit definitions क्रम CSR3
 */
#घोषणा LE_C3_BSWP	0x0004	/* Byte Swap (on क्रम big endian byte order) */
#घोषणा LE_C3_ACON	0x0002	/* ALE Control (on क्रम active low ALE) */
#घोषणा LE_C3_BCON	0x0001	/* Byte Control */


/*
 *		Mode Flags
 */
#घोषणा LE_MO_PROM	0x8000	/* Promiscuous Mode */
/* these next ones 0x4000 -- 0x0080 are not available on the LANCE 7990,
 * but they are in NetBSD's am7990.h, presumably क्रम backwards-compatible chips
 */
#घोषणा LE_MO_DRCVBC	0x4000	/* disable receive broadcast */
#घोषणा LE_MO_DRCVPA	0x2000	/* disable physical address detection */
#घोषणा LE_MO_DLNKTST	0x1000	/* disable link status */
#घोषणा LE_MO_DAPC	0x0800	/* disable स्वतःmatic polarity correction */
#घोषणा LE_MO_MENDECL	0x0400	/* MENDEC loopback mode */
#घोषणा LE_MO_LRTTSEL	0x0200	/* lower RX threshold / TX mode selection */
#घोषणा LE_MO_PSEL1	0x0100	/* port selection bit1 */
#घोषणा LE_MO_PSEL0	0x0080	/* port selection bit0 */
/* and this one is from the C-LANCE data sheet... */
#घोषणा LE_MO_EMBA	0x0080	/* Enable Modअगरied Backoff Algorithm
				   (C-LANCE, not original LANCE) */
#घोषणा LE_MO_INTL	0x0040	/* Internal Loopback */
#घोषणा LE_MO_DRTY	0x0020	/* Disable Retry */
#घोषणा LE_MO_FCOLL	0x0010	/* Force Collision */
#घोषणा LE_MO_DXMTFCS	0x0008	/* Disable Transmit CRC */
#घोषणा LE_MO_LOOP	0x0004	/* Loopback Enable */
#घोषणा LE_MO_DTX	0x0002	/* Disable Transmitter */
#घोषणा LE_MO_DRX	0x0001	/* Disable Receiver */


/*
 *		Receive Flags
 */
#घोषणा LE_R1_OWN	0x80	/* LANCE owns the descriptor */
#घोषणा LE_R1_ERR	0x40	/* Error */
#घोषणा LE_R1_FRA	0x20	/* Framing Error */
#घोषणा LE_R1_OFL	0x10	/* Overflow Error */
#घोषणा LE_R1_CRC	0x08	/* CRC Error */
#घोषणा LE_R1_BUF	0x04	/* Buffer Error */
#घोषणा LE_R1_SOP	0x02	/* Start of Packet */
#घोषणा LE_R1_EOP	0x01	/* End of Packet */
#घोषणा LE_R1_POK	0x03	/* Packet is complete: SOP + EOP */


/*
 *		Transmit Flags
 */
#घोषणा LE_T1_OWN	0x80	/* LANCE owns the descriptor */
#घोषणा LE_T1_ERR	0x40	/* Error */
#घोषणा LE_T1_RES	0x20	/* Reserved, LANCE ग_लिखोs this with a zero */
#घोषणा LE_T1_EMORE	0x10	/* More than one retry needed */
#घोषणा LE_T1_EONE	0x08	/* One retry needed */
#घोषणा LE_T1_EDEF	0x04	/* Deferred */
#घोषणा LE_T1_SOP	0x02	/* Start of Packet */
#घोषणा LE_T1_EOP	0x01	/* End of Packet */
#घोषणा LE_T1_POK	0x03	/* Packet is complete: SOP + EOP */

/*
 *		Error Flags
 */
#घोषणा LE_T3_BUF	0x8000	/* Buffer Error */
#घोषणा LE_T3_UFL	0x4000	/* Underflow Error */
#घोषणा LE_T3_LCOL	0x1000	/* Late Collision */
#घोषणा LE_T3_CLOS	0x0800	/* Loss of Carrier */
#घोषणा LE_T3_RTY	0x0400	/* Retry Error */
#घोषणा LE_T3_TDR	0x03ff	/* Time Doमुख्य Reflectometry */

/* Miscellaneous useful macros */

#घोषणा TX_BUFFS_AVAIL ((lp->tx_old <= lp->tx_new) ? \
			lp->tx_old + lp->tx_ring_mod_mask - lp->tx_new : \
			lp->tx_old - lp->tx_new - 1)

/* The LANCE only uses 24 bit addresses. This करोes the obvious thing. */
#घोषणा LANCE_ADDR(x) ((पूर्णांक)(x) & ~0xff000000)

/* Now the prototypes we export */
पूर्णांक lance_खोलो(काष्ठा net_device *dev);
पूर्णांक lance_बंद(काष्ठा net_device *dev);
netdev_tx_t lance_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
व्योम lance_set_multicast(काष्ठा net_device *dev);
व्योम lance_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
व्योम lance_poll(काष्ठा net_device *dev);
#पूर्ण_अगर

#पूर्ण_अगर /* ndef _7990_H */
