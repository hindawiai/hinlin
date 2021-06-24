<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* $Id: sunlance.c,v 1.112 2002/01/15 06:48:55 davem Exp $
 * lance.c: Linux/Sparc/Lance driver
 *
 *	Written 1995, 1996 by Miguel de Icaza
 * Sources:
 *	The Linux  depca driver
 *	The Linux  lance driver.
 *	The Linux  skeleton driver.
 *	The NetBSD Sparc/Lance driver.
 *	Theo de Raadt (deraadt@खोलोbsd.org)
 *	NCR92C990 Lan Controller manual
 *
 * 1.4:
 *	Added support to run with a ledma on the Sun4m
 *
 * 1.5:
 *	Added multiple card detection.
 *
 *	 4/17/96: Burst sizes and tpe selection on sun4m by Eddie C. Dost
 *		  (ecd@skynet.be)
 *
 *	 5/15/96: स्वतः carrier detection on sun4m by Eddie C. Dost
 *		  (ecd@skynet.be)
 *
 *	 5/17/96: lebuffer on scsi/ether cards now work David S. Miller
 *		  (davem@caip.rutgers.edu)
 *
 *	 5/29/96: override option 'tpe-link-test?', if it is 'false', as
 *		  this disables स्वतः carrier detection on sun4m. Eddie C. Dost
 *		  (ecd@skynet.be)
 *
 * 1.7:
 *	 6/26/96: Bug fix क्रम multiple ledmas, miguel.
 *
 * 1.8:
 *		  Stole multicast code from depca.c, fixed lance_tx.
 *
 * 1.9:
 *	 8/21/96: Fixed the multicast code (Pedro Roque)
 *
 *	 8/28/96: Send fake packet in lance_खोलो() अगर स्वतः_select is true,
 *		  so we can detect the carrier loss condition in समय.
 *		  Eddie C. Dost (ecd@skynet.be)
 *
 *	 9/15/96: Align rx_buf so that eth_copy_and_sum() won't cause an
 *		  MNA trap during chksum_partial_copy(). (ecd@skynet.be)
 *
 *	11/17/96: Handle LE_C0_MERR in lance_पूर्णांकerrupt(). (ecd@skynet.be)
 *
 *	12/22/96: Don't loop क्रमever in lance_rx() on incomplete packets.
 *		  This was the sun4c समाप्तer. Shit, stupid bug.
 *		  (ecd@skynet.be)
 *
 * 1.10:
 *	 1/26/97: Modularize driver. (ecd@skynet.be)
 *
 * 1.11:
 *	12/27/97: Added sun4d support. (jj@sunsite.mff.cuni.cz)
 *
 * 1.12:
 * 	 11/3/99: Fixed SMP race in lance_start_xmit found by davem.
 * 	          Anton Blanअक्षरd (anton@progsoc.uts.edu.au)
 * 2.00: 11/9/99: Massive overhaul and port to new SBUS driver पूर्णांकerfaces.
 *		  David S. Miller (davem@redhat.com)
 * 2.01:
 *      11/08/01: Use library crc32 functions (Matt_Domsch@dell.com)
 *
 */

#अघोषित DEBUG_DRIVER

अटल अक्षर lancestr[] = "LANCE";

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/in.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/crc32.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/socket.h> /* Used क्रम the temporal inet entries and routing */
#समावेश <linux/route.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/bitops.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/gfp.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/byteorder.h>	/* Used by the checksum routines */
#समावेश <यंत्र/idprom.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/auxपन.स>		/* For tpe-link-test? setting */
#समावेश <यंत्र/irq.h>

#घोषणा DRV_NAME	"sunlance"
#घोषणा DRV_RELDATE	"8/24/03"
#घोषणा DRV_AUTHOR	"Miguel de Icaza (miguel@nuclecu.unam.mx)"

MODULE_AUTHOR(DRV_AUTHOR);
MODULE_DESCRIPTION("Sun Lance ethernet driver");
MODULE_LICENSE("GPL");

/* Define: 2^4 Tx buffers and 2^4 Rx buffers */
#अगर_अघोषित LANCE_LOG_TX_BUFFERS
#घोषणा LANCE_LOG_TX_BUFFERS 4
#घोषणा LANCE_LOG_RX_BUFFERS 4
#पूर्ण_अगर

#घोषणा LE_CSR0 0
#घोषणा LE_CSR1 1
#घोषणा LE_CSR2 2
#घोषणा LE_CSR3 3

#घोषणा LE_MO_PROM      0x8000  /* Enable promiscuous mode */

#घोषणा	LE_C0_ERR	0x8000	/* Error: set अगर BAB, SQE, MISS or ME is set */
#घोषणा	LE_C0_BABL	0x4000	/* BAB:  Babble: tx समयout. */
#घोषणा	LE_C0_CERR	0x2000	/* SQE:  Signal quality error */
#घोषणा	LE_C0_MISS	0x1000	/* MISS: Missed a packet */
#घोषणा	LE_C0_MERR	0x0800	/* ME:   Memory error */
#घोषणा	LE_C0_RINT	0x0400	/* Received पूर्णांकerrupt */
#घोषणा	LE_C0_TINT	0x0200	/* Transmitter Interrupt */
#घोषणा	LE_C0_IDON	0x0100	/* IFIN: Init finished. */
#घोषणा	LE_C0_INTR	0x0080	/* Interrupt or error */
#घोषणा	LE_C0_INEA	0x0040	/* Interrupt enable */
#घोषणा	LE_C0_RXON	0x0020	/* Receiver on */
#घोषणा	LE_C0_TXON	0x0010	/* Transmitter on */
#घोषणा	LE_C0_TDMD	0x0008	/* Transmitter demand */
#घोषणा	LE_C0_STOP	0x0004	/* Stop the card */
#घोषणा	LE_C0_STRT	0x0002	/* Start the card */
#घोषणा	LE_C0_INIT	0x0001	/* Init the card */

#घोषणा	LE_C3_BSWP	0x4     /* SWAP */
#घोषणा	LE_C3_ACON	0x2	/* ALE Control */
#घोषणा	LE_C3_BCON	0x1	/* Byte control */

/* Receive message descriptor 1 */
#घोषणा LE_R1_OWN       0x80    /* Who owns the entry */
#घोषणा LE_R1_ERR       0x40    /* Error: अगर FRA, OFL, CRC or BUF is set */
#घोषणा LE_R1_FRA       0x20    /* FRA: Frame error */
#घोषणा LE_R1_OFL       0x10    /* OFL: Frame overflow */
#घोषणा LE_R1_CRC       0x08    /* CRC error */
#घोषणा LE_R1_BUF       0x04    /* BUF: Buffer error */
#घोषणा LE_R1_SOP       0x02    /* Start of packet */
#घोषणा LE_R1_EOP       0x01    /* End of packet */
#घोषणा LE_R1_POK       0x03    /* Packet is complete: SOP + EOP */

#घोषणा LE_T1_OWN       0x80    /* Lance owns the packet */
#घोषणा LE_T1_ERR       0x40    /* Error summary */
#घोषणा LE_T1_EMORE     0x10    /* Error: more than one retry needed */
#घोषणा LE_T1_EONE      0x08    /* Error: one retry needed */
#घोषणा LE_T1_EDEF      0x04    /* Error: deferred */
#घोषणा LE_T1_SOP       0x02    /* Start of packet */
#घोषणा LE_T1_EOP       0x01    /* End of packet */
#घोषणा LE_T1_POK	0x03	/* Packet is complete: SOP + EOP */

#घोषणा LE_T3_BUF       0x8000  /* Buffer error */
#घोषणा LE_T3_UFL       0x4000  /* Error underflow */
#घोषणा LE_T3_LCOL      0x1000  /* Error late collision */
#घोषणा LE_T3_CLOS      0x0800  /* Error carrier loss */
#घोषणा LE_T3_RTY       0x0400  /* Error retry */
#घोषणा LE_T3_TDR       0x03ff  /* Time Doमुख्य Reflectometry counter */

#घोषणा TX_RING_SIZE			(1 << (LANCE_LOG_TX_BUFFERS))
#घोषणा TX_RING_MOD_MASK		(TX_RING_SIZE - 1)
#घोषणा TX_RING_LEN_BITS		((LANCE_LOG_TX_BUFFERS) << 29)
#घोषणा TX_NEXT(__x)			(((__x)+1) & TX_RING_MOD_MASK)

#घोषणा RX_RING_SIZE			(1 << (LANCE_LOG_RX_BUFFERS))
#घोषणा RX_RING_MOD_MASK		(RX_RING_SIZE - 1)
#घोषणा RX_RING_LEN_BITS		((LANCE_LOG_RX_BUFFERS) << 29)
#घोषणा RX_NEXT(__x)			(((__x)+1) & RX_RING_MOD_MASK)

#घोषणा PKT_BUF_SZ		1544
#घोषणा RX_BUFF_SIZE            PKT_BUF_SZ
#घोषणा TX_BUFF_SIZE            PKT_BUF_SZ

काष्ठा lance_rx_desc अणु
	u16	rmd0;		/* low address of packet */
	u8	rmd1_bits;	/* descriptor bits */
	u8	rmd1_hadr;	/* high address of packet */
	s16	length;		/* This length is 2s complement (negative)!
				 * Buffer length
				 */
	u16	mblength;	/* This is the actual number of bytes received */
पूर्ण;

काष्ठा lance_tx_desc अणु
	u16	पंचांगd0;		/* low address of packet */
	u8 	पंचांगd1_bits;	/* descriptor bits */
	u8 	पंचांगd1_hadr;	/* high address of packet */
	s16 	length;		/* Length is 2s complement (negative)! */
	u16 	misc;
पूर्ण;

/* The LANCE initialization block, described in databook. */
/* On the Sparc, this block should be on a DMA region     */
काष्ठा lance_init_block अणु
	u16	mode;		/* Pre-set mode (reg. 15) */
	u8	phys_addr[6];	/* Physical ethernet address */
	u32	filter[2];	/* Multicast filter. */

	/* Receive and transmit ring base, aदीर्घ with extra bits. */
	u16	rx_ptr;		/* receive descriptor addr */
	u16	rx_len;		/* receive len and high addr */
	u16	tx_ptr;		/* transmit descriptor addr */
	u16	tx_len;		/* transmit len and high addr */

	/* The Tx and Rx ring entries must aligned on 8-byte boundaries. */
	काष्ठा lance_rx_desc brx_ring[RX_RING_SIZE];
	काष्ठा lance_tx_desc btx_ring[TX_RING_SIZE];

	u8	tx_buf [TX_RING_SIZE][TX_BUFF_SIZE];
	u8	pad[2];		/* align rx_buf क्रम copy_and_sum(). */
	u8	rx_buf [RX_RING_SIZE][RX_BUFF_SIZE];
पूर्ण;

#घोषणा libdesc_offset(rt, elem) \
((__u32)(((अचिन्हित दीर्घ)(&(((काष्ठा lance_init_block *)0)->rt[elem])))))

#घोषणा libbuff_offset(rt, elem) \
((__u32)(((अचिन्हित दीर्घ)(&(((काष्ठा lance_init_block *)0)->rt[elem][0])))))

काष्ठा lance_निजी अणु
	व्योम __iomem	*lregs;		/* Lance RAP/RDP regs.		*/
	व्योम __iomem	*dregs;		/* DMA controller regs.		*/
	काष्ठा lance_init_block __iomem *init_block_iomem;
	काष्ठा lance_init_block *init_block_mem;

	spinlock_t	lock;

	पूर्णांक		rx_new, tx_new;
	पूर्णांक		rx_old, tx_old;

	काष्ठा platक्रमm_device *ledma;	/* If set this poपूर्णांकs to ledma	*/
	अक्षर		tpe;		/* cable-selection is TPE	*/
	अक्षर		स्वतः_select;	/* cable-selection by carrier	*/
	अक्षर		burst_sizes;	/* ledma SBus burst sizes	*/
	अक्षर		pio_buffer;	/* init block in PIO space?	*/

	अचिन्हित लघु	busmaster_regval;

	व्योम (*init_ring)(काष्ठा net_device *);
	व्योम (*rx)(काष्ठा net_device *);
	व्योम (*tx)(काष्ठा net_device *);

	अक्षर	       	       *name;
	dma_addr_t		init_block_dvma;
	काष्ठा net_device      *dev;		  /* Backpoपूर्णांकer	*/
	काष्ठा platक्रमm_device       *op;
	काष्ठा platक्रमm_device       *lebuffer;
	काष्ठा समयr_list       multicast_समयr;
पूर्ण;

#घोषणा TX_BUFFS_AVAIL ((lp->tx_old<=lp->tx_new)?\
			lp->tx_old+TX_RING_MOD_MASK-lp->tx_new:\
			lp->tx_old - lp->tx_new-1)

/* Lance रेजिस्टरs. */
#घोषणा RDP		0x00UL		/* रेजिस्टर data port		*/
#घोषणा RAP		0x02UL		/* रेजिस्टर address port	*/
#घोषणा LANCE_REG_SIZE	0x04UL

#घोषणा STOP_LANCE(__lp) \
करो अणु	व्योम __iomem *__base = (__lp)->lregs; \
	sbus_ग_लिखोw(LE_CSR0,	__base + RAP); \
	sbus_ग_लिखोw(LE_C0_STOP,	__base + RDP); \
पूर्ण जबतक (0)

पूर्णांक sparc_lance_debug = 2;

/* The Lance uses 24 bit addresses */
/* On the Sun4c the DVMA will provide the reमुख्यing bytes क्रम us */
/* On the Sun4m we have to inकाष्ठा the ledma to provide them    */
/* Even worse, on scsi/ether SBUS cards, the init block and the
 * transmit/receive buffers are addresses as offsets from असलolute
 * zero on the lebuffer PIO area. -DaveM
 */

#घोषणा LANCE_ADDR(x) ((दीर्घ)(x) & ~0xff000000)

/* Load the CSR रेजिस्टरs */
अटल व्योम load_csrs(काष्ठा lance_निजी *lp)
अणु
	u32 leptr;

	अगर (lp->pio_buffer)
		leptr = 0;
	अन्यथा
		leptr = LANCE_ADDR(lp->init_block_dvma);

	sbus_ग_लिखोw(LE_CSR1,		  lp->lregs + RAP);
	sbus_ग_लिखोw(leptr & 0xffff,	  lp->lregs + RDP);
	sbus_ग_लिखोw(LE_CSR2,		  lp->lregs + RAP);
	sbus_ग_लिखोw(leptr >> 16,	  lp->lregs + RDP);
	sbus_ग_लिखोw(LE_CSR3,		  lp->lregs + RAP);
	sbus_ग_लिखोw(lp->busmaster_regval, lp->lregs + RDP);

	/* Poपूर्णांक back to csr0 */
	sbus_ग_लिखोw(LE_CSR0, lp->lregs + RAP);
पूर्ण

/* Setup the Lance Rx and Tx rings */
अटल व्योम lance_init_ring_dvma(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	काष्ठा lance_init_block *ib = lp->init_block_mem;
	dma_addr_t aib = lp->init_block_dvma;
	__u32 leptr;
	पूर्णांक i;

	/* Lock out other processes जबतक setting up hardware */
	netअगर_stop_queue(dev);
	lp->rx_new = lp->tx_new = 0;
	lp->rx_old = lp->tx_old = 0;

	/* Copy the ethernet address to the lance init block
	 * Note that on the sparc you need to swap the ethernet address.
	 */
	ib->phys_addr [0] = dev->dev_addr [1];
	ib->phys_addr [1] = dev->dev_addr [0];
	ib->phys_addr [2] = dev->dev_addr [3];
	ib->phys_addr [3] = dev->dev_addr [2];
	ib->phys_addr [4] = dev->dev_addr [5];
	ib->phys_addr [5] = dev->dev_addr [4];

	/* Setup the Tx ring entries */
	क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
		leptr = LANCE_ADDR(aib + libbuff_offset(tx_buf, i));
		ib->btx_ring [i].पंचांगd0      = leptr;
		ib->btx_ring [i].पंचांगd1_hadr = leptr >> 16;
		ib->btx_ring [i].पंचांगd1_bits = 0;
		ib->btx_ring [i].length    = 0xf000; /* The ones required by पंचांगd2 */
		ib->btx_ring [i].misc      = 0;
	पूर्ण

	/* Setup the Rx ring entries */
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		leptr = LANCE_ADDR(aib + libbuff_offset(rx_buf, i));

		ib->brx_ring [i].rmd0      = leptr;
		ib->brx_ring [i].rmd1_hadr = leptr >> 16;
		ib->brx_ring [i].rmd1_bits = LE_R1_OWN;
		ib->brx_ring [i].length    = -RX_BUFF_SIZE | 0xf000;
		ib->brx_ring [i].mblength  = 0;
	पूर्ण

	/* Setup the initialization block */

	/* Setup rx descriptor poपूर्णांकer */
	leptr = LANCE_ADDR(aib + libdesc_offset(brx_ring, 0));
	ib->rx_len = (LANCE_LOG_RX_BUFFERS << 13) | (leptr >> 16);
	ib->rx_ptr = leptr;

	/* Setup tx descriptor poपूर्णांकer */
	leptr = LANCE_ADDR(aib + libdesc_offset(btx_ring, 0));
	ib->tx_len = (LANCE_LOG_TX_BUFFERS << 13) | (leptr >> 16);
	ib->tx_ptr = leptr;
पूर्ण

अटल व्योम lance_init_ring_pio(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	काष्ठा lance_init_block __iomem *ib = lp->init_block_iomem;
	u32 leptr;
	पूर्णांक i;

	/* Lock out other processes जबतक setting up hardware */
	netअगर_stop_queue(dev);
	lp->rx_new = lp->tx_new = 0;
	lp->rx_old = lp->tx_old = 0;

	/* Copy the ethernet address to the lance init block
	 * Note that on the sparc you need to swap the ethernet address.
	 */
	sbus_ग_लिखोb(dev->dev_addr[1], &ib->phys_addr[0]);
	sbus_ग_लिखोb(dev->dev_addr[0], &ib->phys_addr[1]);
	sbus_ग_लिखोb(dev->dev_addr[3], &ib->phys_addr[2]);
	sbus_ग_लिखोb(dev->dev_addr[2], &ib->phys_addr[3]);
	sbus_ग_लिखोb(dev->dev_addr[5], &ib->phys_addr[4]);
	sbus_ग_लिखोb(dev->dev_addr[4], &ib->phys_addr[5]);

	/* Setup the Tx ring entries */
	क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
		leptr = libbuff_offset(tx_buf, i);
		sbus_ग_लिखोw(leptr,	&ib->btx_ring [i].पंचांगd0);
		sbus_ग_लिखोb(leptr >> 16,&ib->btx_ring [i].पंचांगd1_hadr);
		sbus_ग_लिखोb(0,		&ib->btx_ring [i].पंचांगd1_bits);

		/* The ones required by पंचांगd2 */
		sbus_ग_लिखोw(0xf000,	&ib->btx_ring [i].length);
		sbus_ग_लिखोw(0,		&ib->btx_ring [i].misc);
	पूर्ण

	/* Setup the Rx ring entries */
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		leptr = libbuff_offset(rx_buf, i);

		sbus_ग_लिखोw(leptr,	&ib->brx_ring [i].rmd0);
		sbus_ग_लिखोb(leptr >> 16,&ib->brx_ring [i].rmd1_hadr);
		sbus_ग_लिखोb(LE_R1_OWN,	&ib->brx_ring [i].rmd1_bits);
		sbus_ग_लिखोw(-RX_BUFF_SIZE|0xf000,
			    &ib->brx_ring [i].length);
		sbus_ग_लिखोw(0,		&ib->brx_ring [i].mblength);
	पूर्ण

	/* Setup the initialization block */

	/* Setup rx descriptor poपूर्णांकer */
	leptr = libdesc_offset(brx_ring, 0);
	sbus_ग_लिखोw((LANCE_LOG_RX_BUFFERS << 13) | (leptr >> 16),
		    &ib->rx_len);
	sbus_ग_लिखोw(leptr, &ib->rx_ptr);

	/* Setup tx descriptor poपूर्णांकer */
	leptr = libdesc_offset(btx_ring, 0);
	sbus_ग_लिखोw((LANCE_LOG_TX_BUFFERS << 13) | (leptr >> 16),
		    &ib->tx_len);
	sbus_ग_लिखोw(leptr, &ib->tx_ptr);
पूर्ण

अटल व्योम init_restart_ledma(काष्ठा lance_निजी *lp)
अणु
	u32 csr = sbus_पढ़ोl(lp->dregs + DMA_CSR);

	अगर (!(csr & DMA_HNDL_ERROR)) अणु
		/* E-Cache draining */
		जबतक (sbus_पढ़ोl(lp->dregs + DMA_CSR) & DMA_FIFO_ISDRAIN)
			barrier();
	पूर्ण

	csr = sbus_पढ़ोl(lp->dregs + DMA_CSR);
	csr &= ~DMA_E_BURSTS;
	अगर (lp->burst_sizes & DMA_BURST32)
		csr |= DMA_E_BURST32;
	अन्यथा
		csr |= DMA_E_BURST16;

	csr |= (DMA_DSBL_RD_DRN | DMA_DSBL_WR_INV | DMA_FIFO_INV);

	अगर (lp->tpe)
		csr |= DMA_EN_ENETAUI;
	अन्यथा
		csr &= ~DMA_EN_ENETAUI;
	udelay(20);
	sbus_ग_लिखोl(csr, lp->dregs + DMA_CSR);
	udelay(200);
पूर्ण

अटल पूर्णांक init_restart_lance(काष्ठा lance_निजी *lp)
अणु
	u16 regval = 0;
	पूर्णांक i;

	अगर (lp->dregs)
		init_restart_ledma(lp);

	sbus_ग_लिखोw(LE_CSR0,	lp->lregs + RAP);
	sbus_ग_लिखोw(LE_C0_INIT,	lp->lregs + RDP);

	/* Wait क्रम the lance to complete initialization */
	क्रम (i = 0; i < 100; i++) अणु
		regval = sbus_पढ़ोw(lp->lregs + RDP);

		अगर (regval & (LE_C0_ERR | LE_C0_IDON))
			अवरोध;
		barrier();
	पूर्ण
	अगर (i == 100 || (regval & LE_C0_ERR)) अणु
		prपूर्णांकk(KERN_ERR "LANCE unopened after %d ticks, csr0=%4.4x.\n",
		       i, regval);
		अगर (lp->dregs)
			prपूर्णांकk("dcsr=%8.8x\n", sbus_पढ़ोl(lp->dregs + DMA_CSR));
		वापस -1;
	पूर्ण

	/* Clear IDON by writing a "1", enable पूर्णांकerrupts and start lance */
	sbus_ग_लिखोw(LE_C0_IDON,			lp->lregs + RDP);
	sbus_ग_लिखोw(LE_C0_INEA | LE_C0_STRT,	lp->lregs + RDP);

	अगर (lp->dregs) अणु
		u32 csr = sbus_पढ़ोl(lp->dregs + DMA_CSR);

		csr |= DMA_INT_ENAB;
		sbus_ग_लिखोl(csr, lp->dregs + DMA_CSR);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम lance_rx_dvma(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	काष्ठा lance_init_block *ib = lp->init_block_mem;
	काष्ठा lance_rx_desc *rd;
	u8 bits;
	पूर्णांक len, entry = lp->rx_new;
	काष्ठा sk_buff *skb;

	क्रम (rd = &ib->brx_ring [entry];
	     !((bits = rd->rmd1_bits) & LE_R1_OWN);
	     rd = &ib->brx_ring [entry]) अणु

		/* We got an incomplete frame? */
		अगर ((bits & LE_R1_POK) != LE_R1_POK) अणु
			dev->stats.rx_over_errors++;
			dev->stats.rx_errors++;
		पूर्ण अन्यथा अगर (bits & LE_R1_ERR) अणु
			/* Count only the end frame as a rx error,
			 * not the beginning
			 */
			अगर (bits & LE_R1_BUF) dev->stats.rx_fअगरo_errors++;
			अगर (bits & LE_R1_CRC) dev->stats.rx_crc_errors++;
			अगर (bits & LE_R1_OFL) dev->stats.rx_over_errors++;
			अगर (bits & LE_R1_FRA) dev->stats.rx_frame_errors++;
			अगर (bits & LE_R1_EOP) dev->stats.rx_errors++;
		पूर्ण अन्यथा अणु
			len = (rd->mblength & 0xfff) - 4;
			skb = netdev_alloc_skb(dev, len + 2);

			अगर (skb == शून्य) अणु
				dev->stats.rx_dropped++;
				rd->mblength = 0;
				rd->rmd1_bits = LE_R1_OWN;
				lp->rx_new = RX_NEXT(entry);
				वापस;
			पूर्ण

			dev->stats.rx_bytes += len;

			skb_reserve(skb, 2);		/* 16 byte align */
			skb_put(skb, len);		/* make room */
			skb_copy_to_linear_data(skb,
					 (अचिन्हित अक्षर *)&(ib->rx_buf [entry][0]),
					 len);
			skb->protocol = eth_type_trans(skb, dev);
			netअगर_rx(skb);
			dev->stats.rx_packets++;
		पूर्ण

		/* Return the packet to the pool */
		rd->mblength = 0;
		rd->rmd1_bits = LE_R1_OWN;
		entry = RX_NEXT(entry);
	पूर्ण

	lp->rx_new = entry;
पूर्ण

अटल व्योम lance_tx_dvma(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	काष्ठा lance_init_block *ib = lp->init_block_mem;
	पूर्णांक i, j;

	spin_lock(&lp->lock);

	j = lp->tx_old;
	क्रम (i = j; i != lp->tx_new; i = j) अणु
		काष्ठा lance_tx_desc *td = &ib->btx_ring [i];
		u8 bits = td->पंचांगd1_bits;

		/* If we hit a packet not owned by us, stop */
		अगर (bits & LE_T1_OWN)
			अवरोध;

		अगर (bits & LE_T1_ERR) अणु
			u16 status = td->misc;

			dev->stats.tx_errors++;
			अगर (status & LE_T3_RTY)  dev->stats.tx_पातed_errors++;
			अगर (status & LE_T3_LCOL) dev->stats.tx_winकरोw_errors++;

			अगर (status & LE_T3_CLOS) अणु
				dev->stats.tx_carrier_errors++;
				अगर (lp->स्वतः_select) अणु
					lp->tpe = 1 - lp->tpe;
					prपूर्णांकk(KERN_NOTICE "%s: Carrier Lost, trying %s\n",
					       dev->name, lp->tpe?"TPE":"AUI");
					STOP_LANCE(lp);
					lp->init_ring(dev);
					load_csrs(lp);
					init_restart_lance(lp);
					जाओ out;
				पूर्ण
			पूर्ण

			/* Buffer errors and underflows turn off the
			 * transmitter, restart the adapter.
			 */
			अगर (status & (LE_T3_BUF|LE_T3_UFL)) अणु
				dev->stats.tx_fअगरo_errors++;

				prपूर्णांकk(KERN_ERR "%s: Tx: ERR_BUF|ERR_UFL, restarting\n",
				       dev->name);
				STOP_LANCE(lp);
				lp->init_ring(dev);
				load_csrs(lp);
				init_restart_lance(lp);
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अगर ((bits & LE_T1_POK) == LE_T1_POK) अणु
			/*
			 * So we करोn't count the packet more than once.
			 */
			td->पंचांगd1_bits = bits & ~(LE_T1_POK);

			/* One collision beक्रमe packet was sent. */
			अगर (bits & LE_T1_EONE)
				dev->stats.collisions++;

			/* More than one collision, be optimistic. */
			अगर (bits & LE_T1_EMORE)
				dev->stats.collisions += 2;

			dev->stats.tx_packets++;
		पूर्ण

		j = TX_NEXT(j);
	पूर्ण
	lp->tx_old = j;
out:
	अगर (netअगर_queue_stopped(dev) &&
	    TX_BUFFS_AVAIL > 0)
		netअगर_wake_queue(dev);

	spin_unlock(&lp->lock);
पूर्ण

अटल व्योम lance_piocopy_to_skb(काष्ठा sk_buff *skb, व्योम __iomem *piobuf, पूर्णांक len)
अणु
	u16 *p16 = (u16 *) skb->data;
	u32 *p32;
	u8 *p8;
	व्योम __iomem *pbuf = piobuf;

	/* We know here that both src and dest are on a 16bit boundary. */
	*p16++ = sbus_पढ़ोw(pbuf);
	p32 = (u32 *) p16;
	pbuf += 2;
	len -= 2;

	जबतक (len >= 4) अणु
		*p32++ = sbus_पढ़ोl(pbuf);
		pbuf += 4;
		len -= 4;
	पूर्ण
	p8 = (u8 *) p32;
	अगर (len >= 2) अणु
		p16 = (u16 *) p32;
		*p16++ = sbus_पढ़ोw(pbuf);
		pbuf += 2;
		len -= 2;
		p8 = (u8 *) p16;
	पूर्ण
	अगर (len >= 1)
		*p8 = sbus_पढ़ोb(pbuf);
पूर्ण

अटल व्योम lance_rx_pio(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	काष्ठा lance_init_block __iomem *ib = lp->init_block_iomem;
	काष्ठा lance_rx_desc __iomem *rd;
	अचिन्हित अक्षर bits;
	पूर्णांक len, entry;
	काष्ठा sk_buff *skb;

	entry = lp->rx_new;
	क्रम (rd = &ib->brx_ring [entry];
	     !((bits = sbus_पढ़ोb(&rd->rmd1_bits)) & LE_R1_OWN);
	     rd = &ib->brx_ring [entry]) अणु

		/* We got an incomplete frame? */
		अगर ((bits & LE_R1_POK) != LE_R1_POK) अणु
			dev->stats.rx_over_errors++;
			dev->stats.rx_errors++;
		पूर्ण अन्यथा अगर (bits & LE_R1_ERR) अणु
			/* Count only the end frame as a rx error,
			 * not the beginning
			 */
			अगर (bits & LE_R1_BUF) dev->stats.rx_fअगरo_errors++;
			अगर (bits & LE_R1_CRC) dev->stats.rx_crc_errors++;
			अगर (bits & LE_R1_OFL) dev->stats.rx_over_errors++;
			अगर (bits & LE_R1_FRA) dev->stats.rx_frame_errors++;
			अगर (bits & LE_R1_EOP) dev->stats.rx_errors++;
		पूर्ण अन्यथा अणु
			len = (sbus_पढ़ोw(&rd->mblength) & 0xfff) - 4;
			skb = netdev_alloc_skb(dev, len + 2);

			अगर (skb == शून्य) अणु
				dev->stats.rx_dropped++;
				sbus_ग_लिखोw(0, &rd->mblength);
				sbus_ग_लिखोb(LE_R1_OWN, &rd->rmd1_bits);
				lp->rx_new = RX_NEXT(entry);
				वापस;
			पूर्ण

			dev->stats.rx_bytes += len;

			skb_reserve (skb, 2);		/* 16 byte align */
			skb_put(skb, len);		/* make room */
			lance_piocopy_to_skb(skb, &(ib->rx_buf[entry][0]), len);
			skb->protocol = eth_type_trans(skb, dev);
			netअगर_rx(skb);
			dev->stats.rx_packets++;
		पूर्ण

		/* Return the packet to the pool */
		sbus_ग_लिखोw(0, &rd->mblength);
		sbus_ग_लिखोb(LE_R1_OWN, &rd->rmd1_bits);
		entry = RX_NEXT(entry);
	पूर्ण

	lp->rx_new = entry;
पूर्ण

अटल व्योम lance_tx_pio(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	काष्ठा lance_init_block __iomem *ib = lp->init_block_iomem;
	पूर्णांक i, j;

	spin_lock(&lp->lock);

	j = lp->tx_old;
	क्रम (i = j; i != lp->tx_new; i = j) अणु
		काष्ठा lance_tx_desc __iomem *td = &ib->btx_ring [i];
		u8 bits = sbus_पढ़ोb(&td->पंचांगd1_bits);

		/* If we hit a packet not owned by us, stop */
		अगर (bits & LE_T1_OWN)
			अवरोध;

		अगर (bits & LE_T1_ERR) अणु
			u16 status = sbus_पढ़ोw(&td->misc);

			dev->stats.tx_errors++;
			अगर (status & LE_T3_RTY)  dev->stats.tx_पातed_errors++;
			अगर (status & LE_T3_LCOL) dev->stats.tx_winकरोw_errors++;

			अगर (status & LE_T3_CLOS) अणु
				dev->stats.tx_carrier_errors++;
				अगर (lp->स्वतः_select) अणु
					lp->tpe = 1 - lp->tpe;
					prपूर्णांकk(KERN_NOTICE "%s: Carrier Lost, trying %s\n",
					       dev->name, lp->tpe?"TPE":"AUI");
					STOP_LANCE(lp);
					lp->init_ring(dev);
					load_csrs(lp);
					init_restart_lance(lp);
					जाओ out;
				पूर्ण
			पूर्ण

			/* Buffer errors and underflows turn off the
			 * transmitter, restart the adapter.
			 */
			अगर (status & (LE_T3_BUF|LE_T3_UFL)) अणु
				dev->stats.tx_fअगरo_errors++;

				prपूर्णांकk(KERN_ERR "%s: Tx: ERR_BUF|ERR_UFL, restarting\n",
				       dev->name);
				STOP_LANCE(lp);
				lp->init_ring(dev);
				load_csrs(lp);
				init_restart_lance(lp);
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अगर ((bits & LE_T1_POK) == LE_T1_POK) अणु
			/*
			 * So we करोn't count the packet more than once.
			 */
			sbus_ग_लिखोb(bits & ~(LE_T1_POK), &td->पंचांगd1_bits);

			/* One collision beक्रमe packet was sent. */
			अगर (bits & LE_T1_EONE)
				dev->stats.collisions++;

			/* More than one collision, be optimistic. */
			अगर (bits & LE_T1_EMORE)
				dev->stats.collisions += 2;

			dev->stats.tx_packets++;
		पूर्ण

		j = TX_NEXT(j);
	पूर्ण
	lp->tx_old = j;

	अगर (netअगर_queue_stopped(dev) &&
	    TX_BUFFS_AVAIL > 0)
		netअगर_wake_queue(dev);
out:
	spin_unlock(&lp->lock);
पूर्ण

अटल irqवापस_t lance_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	पूर्णांक csr0;

	sbus_ग_लिखोw(LE_CSR0, lp->lregs + RAP);
	csr0 = sbus_पढ़ोw(lp->lregs + RDP);

	/* Acknowledge all the पूर्णांकerrupt sources ASAP */
	sbus_ग_लिखोw(csr0 & (LE_C0_INTR | LE_C0_TINT | LE_C0_RINT),
		    lp->lregs + RDP);

	अगर ((csr0 & LE_C0_ERR) != 0) अणु
		/* Clear the error condition */
		sbus_ग_लिखोw((LE_C0_BABL | LE_C0_ERR | LE_C0_MISS |
			     LE_C0_CERR | LE_C0_MERR),
			    lp->lregs + RDP);
	पूर्ण

	अगर (csr0 & LE_C0_RINT)
		lp->rx(dev);

	अगर (csr0 & LE_C0_TINT)
		lp->tx(dev);

	अगर (csr0 & LE_C0_BABL)
		dev->stats.tx_errors++;

	अगर (csr0 & LE_C0_MISS)
		dev->stats.rx_errors++;

	अगर (csr0 & LE_C0_MERR) अणु
		अगर (lp->dregs) अणु
			u32 addr = sbus_पढ़ोl(lp->dregs + DMA_ADDR);

			prपूर्णांकk(KERN_ERR "%s: Memory error, status %04x, addr %06x\n",
			       dev->name, csr0, addr & 0xffffff);
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_ERR "%s: Memory error, status %04x\n",
			       dev->name, csr0);
		पूर्ण

		sbus_ग_लिखोw(LE_C0_STOP, lp->lregs + RDP);

		अगर (lp->dregs) अणु
			u32 dma_csr = sbus_पढ़ोl(lp->dregs + DMA_CSR);

			dma_csr |= DMA_FIFO_INV;
			sbus_ग_लिखोl(dma_csr, lp->dregs + DMA_CSR);
		पूर्ण

		lp->init_ring(dev);
		load_csrs(lp);
		init_restart_lance(lp);
		netअगर_wake_queue(dev);
	पूर्ण

	sbus_ग_लिखोw(LE_C0_INEA, lp->lregs + RDP);

	वापस IRQ_HANDLED;
पूर्ण

/* Build a fake network packet and send it to ourselves. */
अटल व्योम build_fake_packet(काष्ठा lance_निजी *lp)
अणु
	काष्ठा net_device *dev = lp->dev;
	पूर्णांक i, entry;

	entry = lp->tx_new & TX_RING_MOD_MASK;
	अगर (lp->pio_buffer) अणु
		काष्ठा lance_init_block __iomem *ib = lp->init_block_iomem;
		u16 __iomem *packet = (u16 __iomem *) &(ib->tx_buf[entry][0]);
		काष्ठा ethhdr __iomem *eth = (काष्ठा ethhdr __iomem *) packet;
		क्रम (i = 0; i < (ETH_ZLEN / माप(u16)); i++)
			sbus_ग_लिखोw(0, &packet[i]);
		क्रम (i = 0; i < 6; i++) अणु
			sbus_ग_लिखोb(dev->dev_addr[i], &eth->h_dest[i]);
			sbus_ग_लिखोb(dev->dev_addr[i], &eth->h_source[i]);
		पूर्ण
		sbus_ग_लिखोw((-ETH_ZLEN) | 0xf000, &ib->btx_ring[entry].length);
		sbus_ग_लिखोw(0, &ib->btx_ring[entry].misc);
		sbus_ग_लिखोb(LE_T1_POK|LE_T1_OWN, &ib->btx_ring[entry].पंचांगd1_bits);
	पूर्ण अन्यथा अणु
		काष्ठा lance_init_block *ib = lp->init_block_mem;
		u16 *packet = (u16 *) &(ib->tx_buf[entry][0]);
		काष्ठा ethhdr *eth = (काष्ठा ethhdr *) packet;
		स_रखो(packet, 0, ETH_ZLEN);
		क्रम (i = 0; i < 6; i++) अणु
			eth->h_dest[i] = dev->dev_addr[i];
			eth->h_source[i] = dev->dev_addr[i];
		पूर्ण
		ib->btx_ring[entry].length = (-ETH_ZLEN) | 0xf000;
		ib->btx_ring[entry].misc = 0;
		ib->btx_ring[entry].पंचांगd1_bits = (LE_T1_POK|LE_T1_OWN);
	पूर्ण
	lp->tx_new = TX_NEXT(entry);
पूर्ण

अटल पूर्णांक lance_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	पूर्णांक status = 0;

	STOP_LANCE(lp);

	अगर (request_irq(dev->irq, lance_पूर्णांकerrupt, IRQF_SHARED,
			lancestr, (व्योम *) dev)) अणु
		prपूर्णांकk(KERN_ERR "Lance: Can't get irq %d\n", dev->irq);
		वापस -EAGAIN;
	पूर्ण

	/* On the 4m, setup the ledma to provide the upper bits क्रम buffers */
	अगर (lp->dregs) अणु
		u32 regval = lp->init_block_dvma & 0xff000000;

		sbus_ग_लिखोl(regval, lp->dregs + DMA_TEST);
	पूर्ण

	/* Set mode and clear multicast filter only at device खोलो,
	 * so that lance_init_ring() called at any error will not
	 * क्रमget multicast filters.
	 *
	 * BTW it is common bug in all lance drivers! --ANK
	 */
	अगर (lp->pio_buffer) अणु
		काष्ठा lance_init_block __iomem *ib = lp->init_block_iomem;
		sbus_ग_लिखोw(0, &ib->mode);
		sbus_ग_लिखोl(0, &ib->filter[0]);
		sbus_ग_लिखोl(0, &ib->filter[1]);
	पूर्ण अन्यथा अणु
		काष्ठा lance_init_block *ib = lp->init_block_mem;
		ib->mode = 0;
		ib->filter [0] = 0;
		ib->filter [1] = 0;
	पूर्ण

	lp->init_ring(dev);
	load_csrs(lp);

	netअगर_start_queue(dev);

	status = init_restart_lance(lp);
	अगर (!status && lp->स्वतः_select) अणु
		build_fake_packet(lp);
		sbus_ग_लिखोw(LE_C0_INEA | LE_C0_TDMD, lp->lregs + RDP);
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक lance_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);

	netअगर_stop_queue(dev);
	del_समयr_sync(&lp->multicast_समयr);

	STOP_LANCE(lp);

	मुक्त_irq(dev->irq, (व्योम *) dev);
	वापस 0;
पूर्ण

अटल पूर्णांक lance_reset(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	पूर्णांक status;

	STOP_LANCE(lp);

	/* On the 4m, reset the dma too */
	अगर (lp->dregs) अणु
		u32 csr, addr;

		prपूर्णांकk(KERN_ERR "resetting ledma\n");
		csr = sbus_पढ़ोl(lp->dregs + DMA_CSR);
		sbus_ग_लिखोl(csr | DMA_RST_ENET, lp->dregs + DMA_CSR);
		udelay(200);
		sbus_ग_लिखोl(csr & ~DMA_RST_ENET, lp->dregs + DMA_CSR);

		addr = lp->init_block_dvma & 0xff000000;
		sbus_ग_लिखोl(addr, lp->dregs + DMA_TEST);
	पूर्ण
	lp->init_ring(dev);
	load_csrs(lp);
	netअगर_trans_update(dev); /* prevent tx समयout */
	status = init_restart_lance(lp);
	वापस status;
पूर्ण

अटल व्योम lance_piocopy_from_skb(व्योम __iomem *dest, अचिन्हित अक्षर *src, पूर्णांक len)
अणु
	व्योम __iomem *piobuf = dest;
	u32 *p32;
	u16 *p16;
	u8 *p8;

	चयन ((अचिन्हित दीर्घ)src & 0x3) अणु
	हाल 0:
		p32 = (u32 *) src;
		जबतक (len >= 4) अणु
			sbus_ग_लिखोl(*p32, piobuf);
			p32++;
			piobuf += 4;
			len -= 4;
		पूर्ण
		src = (अक्षर *) p32;
		अवरोध;
	हाल 1:
	हाल 3:
		p8 = (u8 *) src;
		जबतक (len >= 4) अणु
			u32 val;

			val  = p8[0] << 24;
			val |= p8[1] << 16;
			val |= p8[2] << 8;
			val |= p8[3];
			sbus_ग_लिखोl(val, piobuf);
			p8 += 4;
			piobuf += 4;
			len -= 4;
		पूर्ण
		src = (अक्षर *) p8;
		अवरोध;
	हाल 2:
		p16 = (u16 *) src;
		जबतक (len >= 4) अणु
			u32 val = p16[0]<<16 | p16[1];
			sbus_ग_लिखोl(val, piobuf);
			p16 += 2;
			piobuf += 4;
			len -= 4;
		पूर्ण
		src = (अक्षर *) p16;
		अवरोध;
	पूर्ण
	अगर (len >= 2) अणु
		u16 val = src[0] << 8 | src[1];
		sbus_ग_लिखोw(val, piobuf);
		src += 2;
		piobuf += 2;
		len -= 2;
	पूर्ण
	अगर (len >= 1)
		sbus_ग_लिखोb(src[0], piobuf);
पूर्ण

अटल व्योम lance_piozero(व्योम __iomem *dest, पूर्णांक len)
अणु
	व्योम __iomem *piobuf = dest;

	अगर ((अचिन्हित दीर्घ)piobuf & 1) अणु
		sbus_ग_लिखोb(0, piobuf);
		piobuf += 1;
		len -= 1;
		अगर (len == 0)
			वापस;
	पूर्ण
	अगर (len == 1) अणु
		sbus_ग_लिखोb(0, piobuf);
		वापस;
	पूर्ण
	अगर ((अचिन्हित दीर्घ)piobuf & 2) अणु
		sbus_ग_लिखोw(0, piobuf);
		piobuf += 2;
		len -= 2;
		अगर (len == 0)
			वापस;
	पूर्ण
	जबतक (len >= 4) अणु
		sbus_ग_लिखोl(0, piobuf);
		piobuf += 4;
		len -= 4;
	पूर्ण
	अगर (len >= 2) अणु
		sbus_ग_लिखोw(0, piobuf);
		piobuf += 2;
		len -= 2;
	पूर्ण
	अगर (len >= 1)
		sbus_ग_लिखोb(0, piobuf);
पूर्ण

अटल व्योम lance_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);

	prपूर्णांकk(KERN_ERR "%s: transmit timed out, status %04x, reset\n",
	       dev->name, sbus_पढ़ोw(lp->lregs + RDP));
	lance_reset(dev);
	netअगर_wake_queue(dev);
पूर्ण

अटल netdev_tx_t lance_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	पूर्णांक entry, skblen, len;

	skblen = skb->len;

	len = (skblen <= ETH_ZLEN) ? ETH_ZLEN : skblen;

	spin_lock_irq(&lp->lock);

	dev->stats.tx_bytes += len;

	entry = lp->tx_new & TX_RING_MOD_MASK;
	अगर (lp->pio_buffer) अणु
		काष्ठा lance_init_block __iomem *ib = lp->init_block_iomem;
		sbus_ग_लिखोw((-len) | 0xf000, &ib->btx_ring[entry].length);
		sbus_ग_लिखोw(0, &ib->btx_ring[entry].misc);
		lance_piocopy_from_skb(&ib->tx_buf[entry][0], skb->data, skblen);
		अगर (len != skblen)
			lance_piozero(&ib->tx_buf[entry][skblen], len - skblen);
		sbus_ग_लिखोb(LE_T1_POK | LE_T1_OWN, &ib->btx_ring[entry].पंचांगd1_bits);
	पूर्ण अन्यथा अणु
		काष्ठा lance_init_block *ib = lp->init_block_mem;
		ib->btx_ring [entry].length = (-len) | 0xf000;
		ib->btx_ring [entry].misc = 0;
		skb_copy_from_linear_data(skb, &ib->tx_buf [entry][0], skblen);
		अगर (len != skblen)
			स_रखो((अक्षर *) &ib->tx_buf [entry][skblen], 0, len - skblen);
		ib->btx_ring [entry].पंचांगd1_bits = (LE_T1_POK | LE_T1_OWN);
	पूर्ण

	lp->tx_new = TX_NEXT(entry);

	अगर (TX_BUFFS_AVAIL <= 0)
		netअगर_stop_queue(dev);

	/* Kick the lance: transmit now */
	sbus_ग_लिखोw(LE_C0_INEA | LE_C0_TDMD, lp->lregs + RDP);

	/* Read back CSR to invalidate the E-Cache.
	 * This is needed, because DMA_DSBL_WR_INV is set.
	 */
	अगर (lp->dregs)
		sbus_पढ़ोw(lp->lregs + RDP);

	spin_unlock_irq(&lp->lock);

	dev_kमुक्त_skb(skb);

	वापस NETDEV_TX_OK;
पूर्ण

/* taken from the depca driver */
अटल व्योम lance_load_multicast(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	काष्ठा netdev_hw_addr *ha;
	u32 crc;
	u32 val;

	/* set all multicast bits */
	अगर (dev->flags & IFF_ALLMULTI)
		val = ~0;
	अन्यथा
		val = 0;

	अगर (lp->pio_buffer) अणु
		काष्ठा lance_init_block __iomem *ib = lp->init_block_iomem;
		sbus_ग_लिखोl(val, &ib->filter[0]);
		sbus_ग_लिखोl(val, &ib->filter[1]);
	पूर्ण अन्यथा अणु
		काष्ठा lance_init_block *ib = lp->init_block_mem;
		ib->filter [0] = val;
		ib->filter [1] = val;
	पूर्ण

	अगर (dev->flags & IFF_ALLMULTI)
		वापस;

	/* Add addresses */
	netdev_क्रम_each_mc_addr(ha, dev) अणु
		crc = ether_crc_le(6, ha->addr);
		crc = crc >> 26;
		अगर (lp->pio_buffer) अणु
			काष्ठा lance_init_block __iomem *ib = lp->init_block_iomem;
			u16 __iomem *mcast_table = (u16 __iomem *) &ib->filter;
			u16 पंचांगp = sbus_पढ़ोw(&mcast_table[crc>>4]);
			पंचांगp |= 1 << (crc & 0xf);
			sbus_ग_लिखोw(पंचांगp, &mcast_table[crc>>4]);
		पूर्ण अन्यथा अणु
			काष्ठा lance_init_block *ib = lp->init_block_mem;
			u16 *mcast_table = (u16 *) &ib->filter;
			mcast_table [crc >> 4] |= 1 << (crc & 0xf);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम lance_set_multicast(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	काष्ठा lance_init_block *ib_mem = lp->init_block_mem;
	काष्ठा lance_init_block __iomem *ib_iomem = lp->init_block_iomem;
	u16 mode;

	अगर (!netअगर_running(dev))
		वापस;

	अगर (lp->tx_old != lp->tx_new) अणु
		mod_समयr(&lp->multicast_समयr, jअगरfies + 4);
		netअगर_wake_queue(dev);
		वापस;
	पूर्ण

	netअगर_stop_queue(dev);

	STOP_LANCE(lp);
	lp->init_ring(dev);

	अगर (lp->pio_buffer)
		mode = sbus_पढ़ोw(&ib_iomem->mode);
	अन्यथा
		mode = ib_mem->mode;
	अगर (dev->flags & IFF_PROMISC) अणु
		mode |= LE_MO_PROM;
		अगर (lp->pio_buffer)
			sbus_ग_लिखोw(mode, &ib_iomem->mode);
		अन्यथा
			ib_mem->mode = mode;
	पूर्ण अन्यथा अणु
		mode &= ~LE_MO_PROM;
		अगर (lp->pio_buffer)
			sbus_ग_लिखोw(mode, &ib_iomem->mode);
		अन्यथा
			ib_mem->mode = mode;
		lance_load_multicast(dev);
	पूर्ण
	load_csrs(lp);
	init_restart_lance(lp);
	netअगर_wake_queue(dev);
पूर्ण

अटल व्योम lance_set_multicast_retry(काष्ठा समयr_list *t)
अणु
	काष्ठा lance_निजी *lp = from_समयr(lp, t, multicast_समयr);
	काष्ठा net_device *dev = lp->dev;

	lance_set_multicast(dev);
पूर्ण

अटल व्योम lance_मुक्त_hwresources(काष्ठा lance_निजी *lp)
अणु
	अगर (lp->lregs)
		of_iounmap(&lp->op->resource[0], lp->lregs, LANCE_REG_SIZE);
	अगर (lp->dregs) अणु
		काष्ठा platक्रमm_device *ledma = lp->ledma;

		of_iounmap(&ledma->resource[0], lp->dregs,
			   resource_size(&ledma->resource[0]));
	पूर्ण
	अगर (lp->init_block_iomem) अणु
		of_iounmap(&lp->lebuffer->resource[0], lp->init_block_iomem,
			   माप(काष्ठा lance_init_block));
	पूर्ण अन्यथा अगर (lp->init_block_mem) अणु
		dma_मुक्त_coherent(&lp->op->dev,
				  माप(काष्ठा lance_init_block),
				  lp->init_block_mem,
				  lp->init_block_dvma);
	पूर्ण
पूर्ण

/* Ethtool support... */
अटल व्योम sparc_lance_get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, "sunlance", माप(info->driver));
पूर्ण

अटल स्थिर काष्ठा ethtool_ops sparc_lance_ethtool_ops = अणु
	.get_drvinfo		= sparc_lance_get_drvinfo,
	.get_link		= ethtool_op_get_link,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops sparc_lance_ops = अणु
	.nकरो_खोलो		= lance_खोलो,
	.nकरो_stop		= lance_बंद,
	.nकरो_start_xmit		= lance_start_xmit,
	.nकरो_set_rx_mode	= lance_set_multicast,
	.nकरो_tx_समयout		= lance_tx_समयout,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक sparc_lance_probe_one(काष्ठा platक्रमm_device *op,
				 काष्ठा platक्रमm_device *ledma,
				 काष्ठा platक्रमm_device *lebuffer)
अणु
	काष्ठा device_node *dp = op->dev.of_node;
	काष्ठा lance_निजी *lp;
	काष्ठा net_device *dev;
	पूर्णांक    i;

	dev = alloc_etherdev(माप(काष्ठा lance_निजी) + 8);
	अगर (!dev)
		वापस -ENOMEM;

	lp = netdev_priv(dev);

	spin_lock_init(&lp->lock);

	/* Copy the IDPROM ethernet address to the device काष्ठाure, later we
	 * will copy the address in the device काष्ठाure to the lance
	 * initialization block.
	 */
	क्रम (i = 0; i < 6; i++)
		dev->dev_addr[i] = idprom->id_ethaddr[i];

	/* Get the IO region */
	lp->lregs = of_ioremap(&op->resource[0], 0,
			       LANCE_REG_SIZE, lancestr);
	अगर (!lp->lregs) अणु
		prपूर्णांकk(KERN_ERR "SunLance: Cannot map registers.\n");
		जाओ fail;
	पूर्ण

	lp->ledma = ledma;
	अगर (lp->ledma) अणु
		lp->dregs = of_ioremap(&ledma->resource[0], 0,
				       resource_size(&ledma->resource[0]),
				       "ledma");
		अगर (!lp->dregs) अणु
			prपूर्णांकk(KERN_ERR "SunLance: Cannot map "
			       "ledma registers.\n");
			जाओ fail;
		पूर्ण
	पूर्ण

	lp->op = op;
	lp->lebuffer = lebuffer;
	अगर (lebuffer) अणु
		/* sanity check */
		अगर (lebuffer->resource[0].start & 7) अणु
			prपूर्णांकk(KERN_ERR "SunLance: ERROR: Rx and Tx rings not on even boundary.\n");
			जाओ fail;
		पूर्ण
		lp->init_block_iomem =
			of_ioremap(&lebuffer->resource[0], 0,
				   माप(काष्ठा lance_init_block), "lebuffer");
		अगर (!lp->init_block_iomem) अणु
			prपूर्णांकk(KERN_ERR "SunLance: Cannot map PIO buffer.\n");
			जाओ fail;
		पूर्ण
		lp->init_block_dvma = 0;
		lp->pio_buffer = 1;
		lp->init_ring = lance_init_ring_pio;
		lp->rx = lance_rx_pio;
		lp->tx = lance_tx_pio;
	पूर्ण अन्यथा अणु
		lp->init_block_mem =
			dma_alloc_coherent(&op->dev,
					   माप(काष्ठा lance_init_block),
					   &lp->init_block_dvma, GFP_ATOMIC);
		अगर (!lp->init_block_mem)
			जाओ fail;

		lp->pio_buffer = 0;
		lp->init_ring = lance_init_ring_dvma;
		lp->rx = lance_rx_dvma;
		lp->tx = lance_tx_dvma;
	पूर्ण
	lp->busmaster_regval = of_getपूर्णांकprop_शेष(dp,  "busmaster-regval",
						     (LE_C3_BSWP |
						      LE_C3_ACON |
						      LE_C3_BCON));

	lp->name = lancestr;

	lp->burst_sizes = 0;
	अगर (lp->ledma) अणु
		काष्ठा device_node *ledma_dp = ledma->dev.of_node;
		काष्ठा device_node *sbus_dp;
		अचिन्हित पूर्णांक sbmask;
		स्थिर अक्षर *prop;
		u32 csr;

		/* Find burst-size property क्रम ledma */
		lp->burst_sizes = of_getपूर्णांकprop_शेष(ledma_dp,
							"burst-sizes", 0);

		/* ledma may be capable of fast bursts, but sbus may not. */
		sbus_dp = ledma_dp->parent;
		sbmask = of_getपूर्णांकprop_शेष(sbus_dp, "burst-sizes",
					       DMA_BURSTBITS);
		lp->burst_sizes &= sbmask;

		/* Get the cable-selection property */
		prop = of_get_property(ledma_dp, "cable-selection", शून्य);
		अगर (!prop || prop[0] == '\0') अणु
			काष्ठा device_node *nd;

			prपूर्णांकk(KERN_INFO "SunLance: using "
			       "auto-carrier-detection.\n");

			nd = of_find_node_by_path("/options");
			अगर (!nd)
				जाओ no_link_test;

			prop = of_get_property(nd, "tpe-link-test?", शून्य);
			अगर (!prop)
				जाओ node_put;

			अगर (म_भेद(prop, "true")) अणु
				prपूर्णांकk(KERN_NOTICE "SunLance: warning: overriding option "
				       "'tpe-link-test?'\n");
				prपूर्णांकk(KERN_NOTICE "SunLance: warning: mail any problems "
				       "to ecd@skynet.be\n");
				auxio_set_lte(AUXIO_LTE_ON);
			पूर्ण
node_put:
			of_node_put(nd);
no_link_test:
			lp->स्वतः_select = 1;
			lp->tpe = 0;
		पूर्ण अन्यथा अगर (!म_भेद(prop, "aui")) अणु
			lp->स्वतः_select = 0;
			lp->tpe = 0;
		पूर्ण अन्यथा अणु
			lp->स्वतः_select = 0;
			lp->tpe = 1;
		पूर्ण

		/* Reset ledma */
		csr = sbus_पढ़ोl(lp->dregs + DMA_CSR);
		sbus_ग_लिखोl(csr | DMA_RST_ENET, lp->dregs + DMA_CSR);
		udelay(200);
		sbus_ग_लिखोl(csr & ~DMA_RST_ENET, lp->dregs + DMA_CSR);
	पूर्ण अन्यथा
		lp->dregs = शून्य;

	lp->dev = dev;
	SET_NETDEV_DEV(dev, &op->dev);
	dev->watchकरोg_समयo = 5*HZ;
	dev->ethtool_ops = &sparc_lance_ethtool_ops;
	dev->netdev_ops = &sparc_lance_ops;

	dev->irq = op->archdata.irqs[0];

	/* We cannot sleep अगर the chip is busy during a
	 * multicast list update event, because such events
	 * can occur from पूर्णांकerrupts (ex. IPv6).  So we
	 * use a समयr to try again later when necessary. -DaveM
	 */
	समयr_setup(&lp->multicast_समयr, lance_set_multicast_retry, 0);

	अगर (रेजिस्टर_netdev(dev)) अणु
		prपूर्णांकk(KERN_ERR "SunLance: Cannot register device.\n");
		जाओ fail;
	पूर्ण

	platक्रमm_set_drvdata(op, lp);

	prपूर्णांकk(KERN_INFO "%s: LANCE %pM\n",
	       dev->name, dev->dev_addr);

	वापस 0;

fail:
	lance_मुक्त_hwresources(lp);
	मुक्त_netdev(dev);
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक sunlance_sbus_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा platक्रमm_device *parent = to_platक्रमm_device(op->dev.parent);
	काष्ठा device_node *parent_dp = parent->dev.of_node;
	पूर्णांक err;

	अगर (of_node_name_eq(parent_dp, "ledma")) अणु
		err = sparc_lance_probe_one(op, parent, शून्य);
	पूर्ण अन्यथा अगर (of_node_name_eq(parent_dp, "lebuffer")) अणु
		err = sparc_lance_probe_one(op, शून्य, parent);
	पूर्ण अन्यथा
		err = sparc_lance_probe_one(op, शून्य, शून्य);

	वापस err;
पूर्ण

अटल पूर्णांक sunlance_sbus_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा lance_निजी *lp = platक्रमm_get_drvdata(op);
	काष्ठा net_device *net_dev = lp->dev;

	unरेजिस्टर_netdev(net_dev);

	lance_मुक्त_hwresources(lp);

	मुक्त_netdev(net_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sunlance_sbus_match[] = अणु
	अणु
		.name = "le",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, sunlance_sbus_match);

अटल काष्ठा platक्रमm_driver sunlance_sbus_driver = अणु
	.driver = अणु
		.name = "sunlance",
		.of_match_table = sunlance_sbus_match,
	पूर्ण,
	.probe		= sunlance_sbus_probe,
	.हटाओ		= sunlance_sbus_हटाओ,
पूर्ण;

module_platक्रमm_driver(sunlance_sbus_driver);
