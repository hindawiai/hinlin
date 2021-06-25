<शैली गुरु>
/* Generic NS8390 रेजिस्टर definitions. */

/* This file is part of Donald Becker's 8390 drivers, and is distributed
 * under the same license. Auto-loading of 8390.o only in v2.2 - Paul G.
 * Some of these names and comments originated from the Crynwr
 * packet drivers, which are distributed under the GPL.
 */

#अगर_अघोषित _8390_h
#घोषणा _8390_h

#समावेश <linux/अगर_ether.h>
#समावेश <linux/ioport.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/skbuff.h>

#घोषणा TX_PAGES 12	/* Two Tx slots */

/* The 8390 specअगरic per-packet-header क्रमmat. */
काष्ठा e8390_pkt_hdr अणु
	अचिन्हित अक्षर status; /* status */
	अचिन्हित अक्षर next;   /* poपूर्णांकer to next packet. */
	अचिन्हित लघु count; /* header + packet length in bytes */
पूर्ण;

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
व्योम ei_poll(काष्ठा net_device *dev);
व्योम eip_poll(काष्ठा net_device *dev);
#पूर्ण_अगर


/* Without I/O delay - non ISA or later chips */
व्योम NS8390_init(काष्ठा net_device *dev, पूर्णांक startp);
पूर्णांक ei_खोलो(काष्ठा net_device *dev);
पूर्णांक ei_बंद(काष्ठा net_device *dev);
irqवापस_t ei_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
व्योम ei_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
netdev_tx_t ei_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
व्योम ei_set_multicast_list(काष्ठा net_device *dev);
काष्ठा net_device_stats *ei_get_stats(काष्ठा net_device *dev);

बाह्य स्थिर काष्ठा net_device_ops ei_netdev_ops;

काष्ठा net_device *__alloc_ei_netdev(पूर्णांक size);
अटल अंतरभूत काष्ठा net_device *alloc_ei_netdev(व्योम)
अणु
	वापस __alloc_ei_netdev(0);
पूर्ण

/* With I/O delay क्रमm */
व्योम NS8390p_init(काष्ठा net_device *dev, पूर्णांक startp);
पूर्णांक eip_खोलो(काष्ठा net_device *dev);
पूर्णांक eip_बंद(काष्ठा net_device *dev);
irqवापस_t eip_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
व्योम eip_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
netdev_tx_t eip_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
व्योम eip_set_multicast_list(काष्ठा net_device *dev);
काष्ठा net_device_stats *eip_get_stats(काष्ठा net_device *dev);

बाह्य स्थिर काष्ठा net_device_ops eip_netdev_ops;

काष्ठा net_device *__alloc_eip_netdev(पूर्णांक size);
अटल अंतरभूत काष्ठा net_device *alloc_eip_netdev(व्योम)
अणु
	वापस __alloc_eip_netdev(0);
पूर्ण

/* You have one of these per-board */
काष्ठा ei_device अणु
	स्थिर अक्षर *name;
	व्योम (*reset_8390)(काष्ठा net_device *dev);
	व्योम (*get_8390_hdr)(काष्ठा net_device *dev,
			     काष्ठा e8390_pkt_hdr *hdr, पूर्णांक ring_page);
	व्योम (*block_output)(काष्ठा net_device *dev, पूर्णांक count,
			     स्थिर अचिन्हित अक्षर *buf, पूर्णांक start_page);
	व्योम (*block_input)(काष्ठा net_device *dev, पूर्णांक count,
			    काष्ठा sk_buff *skb, पूर्णांक ring_offset);
	अचिन्हित दीर्घ rmem_start;
	अचिन्हित दीर्घ rmem_end;
	व्योम __iomem *mem;
	अचिन्हित अक्षर mcfilter[8];
	अचिन्हित खोलो:1;
	अचिन्हित word16:1;		/* We have the 16-bit (vs 8-bit)
					 * version of the card.
					 */
	अचिन्हित bigendian:1;		/* 16-bit big endian mode. Do NOT
					 * set this on अक्रमom 8390 clones!
					 */
	अचिन्हित txing:1;		/* Transmit Active */
	अचिन्हित irqlock:1;		/* 8390's intrs disabled when '1'. */
	अचिन्हित dमुख्यg:1;		/* Remote DMA Active */
	अचिन्हित अक्षर tx_start_page, rx_start_page, stop_page;
	अचिन्हित अक्षर current_page;	/* Read poपूर्णांकer in buffer  */
	अचिन्हित अक्षर पूर्णांकerface_num;	/* Net port (AUI, 10bT.) to use. */
	अचिन्हित अक्षर txqueue;		/* Tx Packet buffer queue length. */
	लघु tx1, tx2;			/* Packet lengths क्रम ping-pong tx. */
	लघु lasttx;			/* Alpha version consistency check. */
	अचिन्हित अक्षर reg0;		/* Register '0' in a WD8013 */
	अचिन्हित अक्षर reg5;		/* Register '5' in a WD8013 */
	अचिन्हित अक्षर saved_irq;	/* Original dev->irq value. */
	u32 *reg_offset;		/* Register mapping table */
	spinlock_t page_lock;		/* Page रेजिस्टर locks */
	अचिन्हित दीर्घ priv;		/* Private field to store bus IDs etc. */
	u32 msg_enable;			/* debug message level */
#अगर_घोषित AX88796_PLATFORM
	अचिन्हित अक्षर rxcr_base;	/* शेष value क्रम RXCR */
#पूर्ण_अगर
पूर्ण;

/* The maximum number of 8390 पूर्णांकerrupt service routines called per IRQ. */
#घोषणा MAX_SERVICE 12

/* The maximum समय रुकोed (in jअगरfies) beक्रमe assuming a Tx failed. (20ms) */
#घोषणा TX_TIMEOUT (20*HZ/100)

#घोषणा ei_status (*(काष्ठा ei_device *)netdev_priv(dev))

/* Some generic ethernet रेजिस्टर configurations. */
#घोषणा E8390_TX_IRQ_MASK	0xa	/* For रेजिस्टर EN0_ISR */
#घोषणा E8390_RX_IRQ_MASK	0x5

#अगर_घोषित AX88796_PLATFORM
#घोषणा E8390_RXCONFIG		(ei_status.rxcr_base | 0x04)
#घोषणा E8390_RXOFF		(ei_status.rxcr_base | 0x20)
#अन्यथा
/* EN0_RXCR: broadcasts, no multicast,errors */
#घोषणा E8390_RXCONFIG		0x4
/* EN0_RXCR: Accept no packets */
#घोषणा E8390_RXOFF		0x20
#पूर्ण_अगर

/* EN0_TXCR: Normal transmit mode */
#घोषणा E8390_TXCONFIG		0x00
/* EN0_TXCR: Transmitter off */
#घोषणा E8390_TXOFF		0x02


/*  Register accessed at EN_CMD, the 8390 base addr.  */
#घोषणा E8390_STOP	0x01	/* Stop and reset the chip */
#घोषणा E8390_START	0x02	/* Start the chip, clear reset */
#घोषणा E8390_TRANS	0x04	/* Transmit a frame */
#घोषणा E8390_RREAD	0x08	/* Remote पढ़ो */
#घोषणा E8390_RWRITE	0x10	/* Remote ग_लिखो  */
#घोषणा E8390_NODMA	0x20	/* Remote DMA */
#घोषणा E8390_PAGE0	0x00	/* Select page chip रेजिस्टरs */
#घोषणा E8390_PAGE1	0x40	/* using the two high-order bits */
#घोषणा E8390_PAGE2	0x80	/* Page 3 is invalid. */

/* Only generate indirect loads given a machine that needs them.
 * - हटाओd AMIGA_PCMCIA from this list, handled as ISA io now
 * - the _p क्रम generates no delay by शेष 8390p.c overrides this.
 */

#अगर_अघोषित ei_inb
#घोषणा ei_inb(_p)	inb(_p)
#घोषणा ei_outb(_v, _p)	outb(_v, _p)
#घोषणा ei_inb_p(_p)	inb(_p)
#घोषणा ei_outb_p(_v, _p) outb(_v, _p)
#पूर्ण_अगर

#अगर_अघोषित EI_SHIFT
#घोषणा EI_SHIFT(x)	(x)
#पूर्ण_अगर

#घोषणा E8390_CMD	EI_SHIFT(0x00)  /* The command रेजिस्टर (क्रम all pages) */
/* Page 0 रेजिस्टर offsets. */
#घोषणा EN0_CLDALO	EI_SHIFT(0x01)	/* Low byte of current local dma addr RD */
#घोषणा EN0_STARTPG	EI_SHIFT(0x01)	/* Starting page of ring bfr WR */
#घोषणा EN0_CLDAHI	EI_SHIFT(0x02)	/* High byte of current local dma addr RD */
#घोषणा EN0_STOPPG	EI_SHIFT(0x02)	/* Ending page +1 of ring bfr WR */
#घोषणा EN0_BOUNDARY	EI_SHIFT(0x03)	/* Boundary page of ring bfr RD WR */
#घोषणा EN0_TSR		EI_SHIFT(0x04)	/* Transmit status reg RD */
#घोषणा EN0_TPSR	EI_SHIFT(0x04)	/* Transmit starting page WR */
#घोषणा EN0_NCR		EI_SHIFT(0x05)	/* Number of collision reg RD */
#घोषणा EN0_TCNTLO	EI_SHIFT(0x05)	/* Low  byte of tx byte count WR */
#घोषणा EN0_FIFO	EI_SHIFT(0x06)	/* FIFO RD */
#घोषणा EN0_TCNTHI	EI_SHIFT(0x06)	/* High byte of tx byte count WR */
#घोषणा EN0_ISR		EI_SHIFT(0x07)	/* Interrupt status reg RD WR */
#घोषणा EN0_CRDALO	EI_SHIFT(0x08)	/* low byte of current remote dma address RD */
#घोषणा EN0_RSARLO	EI_SHIFT(0x08)	/* Remote start address reg 0 */
#घोषणा EN0_CRDAHI	EI_SHIFT(0x09)	/* high byte, current remote dma address RD */
#घोषणा EN0_RSARHI	EI_SHIFT(0x09)	/* Remote start address reg 1 */
#घोषणा EN0_RCNTLO	EI_SHIFT(0x0a)	/* Remote byte count reg WR */
#घोषणा EN0_RCNTHI	EI_SHIFT(0x0b)	/* Remote byte count reg WR */
#घोषणा EN0_RSR		EI_SHIFT(0x0c)	/* rx status reg RD */
#घोषणा EN0_RXCR	EI_SHIFT(0x0c)	/* RX configuration reg WR */
#घोषणा EN0_TXCR	EI_SHIFT(0x0d)	/* TX configuration reg WR */
#घोषणा EN0_COUNTER0	EI_SHIFT(0x0d)	/* Rcv alignment error counter RD */
#घोषणा EN0_DCFG	EI_SHIFT(0x0e)	/* Data configuration reg WR */
#घोषणा EN0_COUNTER1	EI_SHIFT(0x0e)	/* Rcv CRC error counter RD */
#घोषणा EN0_IMR		EI_SHIFT(0x0f)	/* Interrupt mask reg WR */
#घोषणा EN0_COUNTER2	EI_SHIFT(0x0f)	/* Rcv missed frame error counter RD */

/* Bits in EN0_ISR - Interrupt status रेजिस्टर */
#घोषणा ENISR_RX	0x01	/* Receiver, no error */
#घोषणा ENISR_TX	0x02	/* Transmitter, no error */
#घोषणा ENISR_RX_ERR	0x04	/* Receiver, with error */
#घोषणा ENISR_TX_ERR	0x08	/* Transmitter, with error */
#घोषणा ENISR_OVER	0x10	/* Receiver overwrote the ring */
#घोषणा ENISR_COUNTERS	0x20	/* Counters need emptying */
#घोषणा ENISR_RDC	0x40	/* remote dma complete */
#घोषणा ENISR_RESET	0x80	/* Reset completed */
#घोषणा ENISR_ALL	0x3f	/* Interrupts we will enable */

/* Bits in EN0_DCFG - Data config रेजिस्टर */
#घोषणा ENDCFG_WTS	0x01	/* word transfer mode selection */
#घोषणा ENDCFG_BOS	0x02	/* byte order selection */

/* Page 1 रेजिस्टर offsets. */
#घोषणा EN1_PHYS   EI_SHIFT(0x01)	/* This board's physical enet addr RD WR */
#घोषणा EN1_PHYS_SHIFT(i)  EI_SHIFT(i+1) /* Get and set mac address */
#घोषणा EN1_CURPAG EI_SHIFT(0x07)	/* Current memory page RD WR */
#घोषणा EN1_MULT   EI_SHIFT(0x08)	/* Multicast filter mask array (8 bytes) RD WR */
#घोषणा EN1_MULT_SHIFT(i)  EI_SHIFT(8+i) /* Get and set multicast filter */

/* Bits in received packet status byte and EN0_RSR*/
#घोषणा ENRSR_RXOK	0x01	/* Received a good packet */
#घोषणा ENRSR_CRC	0x02	/* CRC error */
#घोषणा ENRSR_FAE	0x04	/* frame alignment error */
#घोषणा ENRSR_FO	0x08	/* FIFO overrun */
#घोषणा ENRSR_MPA	0x10	/* missed pkt */
#घोषणा ENRSR_PHY	0x20	/* physical/multicast address */
#घोषणा ENRSR_DIS	0x40	/* receiver disable. set in monitor mode */
#घोषणा ENRSR_DEF	0x80	/* deferring */

/* Transmitted packet status, EN0_TSR. */
#घोषणा ENTSR_PTX 0x01	/* Packet transmitted without error */
#घोषणा ENTSR_ND  0x02	/* The transmit wasn't deferred. */
#घोषणा ENTSR_COL 0x04	/* The transmit collided at least once. */
#घोषणा ENTSR_ABT 0x08  /* The transmit collided 16 बार, and was deferred. */
#घोषणा ENTSR_CRS 0x10	/* The carrier sense was lost. */
#घोषणा ENTSR_FU  0x20  /* A "FIFO underrun" occurred during transmit. */
#घोषणा ENTSR_CDH 0x40	/* The collision detect "heartbeat" संकेत was lost. */
#घोषणा ENTSR_OWC 0x80  /* There was an out-of-winकरोw collision. */

#पूर्ण_अगर /* _8390_h */
