<शैली गुरु>
/* sun3lance.c: Ethernet driver क्रम SUN3 Lance chip */
/*

  Sun3 Lance ethernet driver, by Sam Creasey (sammy@users.qual.net).
  This driver is a part of the linux kernel, and is thus distributed
  under the GNU General Public License.

  The values used in LANCE_OBIO and LANCE_IRQ seem to be empirically
  true क्रम the correct IRQ and address of the lance रेजिस्टरs.  They
  have not been widely tested, however.  What we probably need is a
  "proper" way to search क्रम a device in the sun3's prom, but, alas,
  linux has no such thing.

  This driver is largely based on atarilance.c, by Roman Hodek.  Other
  sources of inspiration were the NetBSD sun3 am7990 driver, and the
  linux sparc lance driver (sunlance.c).

  There are more assumptions made throughout this driver, it almost
  certainly still needs work, but it करोes work at least क्रम RARP/BOOTP and
  mounting the root NFS fileप्रणाली.

*/

अटल स्थिर अक्षर version[] =
"sun3lance.c: v1.2 1/12/2001  Sam Creasey (sammy@sammy.net)\n";

#समावेश <linux/module.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/bitops.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dvma.h>
#समावेश <यंत्र/idprom.h>
#समावेश <यंत्र/machines.h>

#अगर_घोषित CONFIG_SUN3
#समावेश <यंत्र/sun3mmu.h>
#अन्यथा
#समावेश <यंत्र/sun3xprom.h>
#पूर्ण_अगर

/* sun3/60 addr/irq क्रम the lance chip.  If your sun is dअगरferent,
   change this. */
#घोषणा LANCE_OBIO 0x120000
#घोषणा LANCE_IRQ IRQ_AUTO_3

/* Debug level:
 *  0 = silent, prपूर्णांक only serious errors
 *  1 = normal, prपूर्णांक error messages
 *  2 = debug, prपूर्णांक debug infos
 *  3 = debug, prपूर्णांक even more debug infos (packet data)
 */

#घोषणा	LANCE_DEBUG	0

#अगर_घोषित LANCE_DEBUG
अटल पूर्णांक lance_debug = LANCE_DEBUG;
#अन्यथा
अटल पूर्णांक lance_debug = 1;
#पूर्ण_अगर
module_param(lance_debug, पूर्णांक, 0);
MODULE_PARM_DESC(lance_debug, "SUN3 Lance debug level (0-3)");
MODULE_LICENSE("GPL");

#घोषणा	DPRINTK(n,a) \
	करो अणु  \
		अगर (lance_debug >= n)  \
			prपूर्णांकk a; \
	पूर्ण जबतक( 0 )


/* we're only using 32k of memory, so we use 4 TX
   buffers and 16 RX buffers.  These values are expressed as log2. */

#घोषणा TX_LOG_RING_SIZE			3
#घोषणा RX_LOG_RING_SIZE			5

/* These are the derived values */

#घोषणा TX_RING_SIZE			(1 << TX_LOG_RING_SIZE)
#घोषणा TX_RING_LEN_BITS		(TX_LOG_RING_SIZE << 5)
#घोषणा	TX_RING_MOD_MASK		(TX_RING_SIZE - 1)

#घोषणा RX_RING_SIZE			(1 << RX_LOG_RING_SIZE)
#घोषणा RX_RING_LEN_BITS		(RX_LOG_RING_SIZE << 5)
#घोषणा	RX_RING_MOD_MASK		(RX_RING_SIZE - 1)

/* Definitions क्रम packet buffer access: */
#घोषणा PKT_BUF_SZ		1544

/* Get the address of a packet buffer corresponding to a given buffer head */
#घोषणा	PKTBUF_ADDR(head)	(व्योम *)((अचिन्हित दीर्घ)(MEM) | (head)->base)


/* The LANCE Rx and Tx ring descriptors. */
काष्ठा lance_rx_head अणु
	अचिन्हित लघु	base;		/* Low word of base addr */
	अस्थिर अचिन्हित अक्षर	flag;
	अचिन्हित अक्षर  base_hi;	/* High word of base addr (unused) */
	लघु buf_length;	/* This length is 2s complement! */
	अस्थिर लघु msg_length;	/* This length is "normal". */
पूर्ण;

काष्ठा lance_tx_head अणु
	अचिन्हित लघु base;		/* Low word of base addr */
	अस्थिर अचिन्हित अक्षर	flag;
	अचिन्हित अक्षर base_hi;	/* High word of base addr (unused) */
	लघु length;		/* Length is 2s complement! */
	अस्थिर लघु misc;
पूर्ण;

/* The LANCE initialization block, described in databook. */
काष्ठा lance_init_block अणु
	अचिन्हित लघु	mode;		/* Pre-set mode */
	अचिन्हित अक्षर	hwaddr[6];	/* Physical ethernet address */
	अचिन्हित पूर्णांक    filter[2];	/* Multicast filter (unused). */
	/* Receive and transmit ring base, aदीर्घ with length bits. */
	अचिन्हित लघु rdra;
	अचिन्हित लघु rlen;
	अचिन्हित लघु tdra;
	अचिन्हित लघु tlen;
	अचिन्हित लघु pad[4]; /* is thie needed? */
पूर्ण;

/* The whole layout of the Lance shared memory */
काष्ठा lance_memory अणु
	काष्ठा lance_init_block	init;
	काष्ठा lance_tx_head	tx_head[TX_RING_SIZE];
	काष्ठा lance_rx_head	rx_head[RX_RING_SIZE];
	अक्षर   rx_data[RX_RING_SIZE][PKT_BUF_SZ];
	अक्षर   tx_data[TX_RING_SIZE][PKT_BUF_SZ];
पूर्ण;

/* The driver's निजी device काष्ठाure */

काष्ठा lance_निजी अणु
	अस्थिर अचिन्हित लघु	*iobase;
	काष्ठा lance_memory	*mem;
     	पूर्णांक new_rx, new_tx;	/* The next मुक्त ring entry */
	पूर्णांक old_tx, old_rx;     /* ring entry to be processed */
/* These two must be दीर्घs क्रम set_bit() */
	दीर्घ	    tx_full;
	दीर्घ	    lock;
पूर्ण;

/* I/O रेजिस्टर access macros */

#घोषणा	MEM	lp->mem
#घोषणा	DREG	lp->iobase[0]
#घोषणा	AREG	lp->iobase[1]
#घोषणा	REGA(a)	(*( AREG = (a), &DREG ))

/* Definitions क्रम the Lance */

/* tx_head flags */
#घोषणा TMD1_ENP		0x01	/* end of packet */
#घोषणा TMD1_STP		0x02	/* start of packet */
#घोषणा TMD1_DEF		0x04	/* deferred */
#घोषणा TMD1_ONE		0x08	/* one retry needed */
#घोषणा TMD1_MORE		0x10	/* more than one retry needed */
#घोषणा TMD1_ERR		0x40	/* error summary */
#घोषणा TMD1_OWN 		0x80	/* ownership (set: chip owns) */

#घोषणा TMD1_OWN_CHIP	TMD1_OWN
#घोषणा TMD1_OWN_HOST	0

/* tx_head misc field */
#घोषणा TMD3_TDR		0x03FF	/* Time Doमुख्य Reflectometry counter */
#घोषणा TMD3_RTRY		0x0400	/* failed after 16 retries */
#घोषणा TMD3_LCAR		0x0800	/* carrier lost */
#घोषणा TMD3_LCOL		0x1000	/* late collision */
#घोषणा TMD3_UFLO		0x4000	/* underflow (late memory) */
#घोषणा TMD3_BUFF		0x8000	/* buffering error (no ENP) */

/* rx_head flags */
#घोषणा RMD1_ENP		0x01	/* end of packet */
#घोषणा RMD1_STP		0x02	/* start of packet */
#घोषणा RMD1_BUFF		0x04	/* buffer error */
#घोषणा RMD1_CRC		0x08	/* CRC error */
#घोषणा RMD1_OFLO		0x10	/* overflow */
#घोषणा RMD1_FRAM		0x20	/* framing error */
#घोषणा RMD1_ERR		0x40	/* error summary */
#घोषणा RMD1_OWN 		0x80	/* ownership (set: ship owns) */

#घोषणा RMD1_OWN_CHIP	RMD1_OWN
#घोषणा RMD1_OWN_HOST	0

/* रेजिस्टर names */
#घोषणा CSR0	0		/* mode/status */
#घोषणा CSR1	1		/* init block addr (low) */
#घोषणा CSR2	2		/* init block addr (high) */
#घोषणा CSR3	3		/* misc */
#घोषणा CSR8	8	  	/* address filter */
#घोषणा CSR15	15		/* promiscuous mode */

/* CSR0 */
/* (R=पढ़ोable, W=ग_लिखोable, S=set on ग_लिखो, C=clear on ग_लिखो) */
#घोषणा CSR0_INIT	0x0001		/* initialize (RS) */
#घोषणा CSR0_STRT	0x0002		/* start (RS) */
#घोषणा CSR0_STOP	0x0004		/* stop (RS) */
#घोषणा CSR0_TDMD	0x0008		/* transmit demand (RS) */
#घोषणा CSR0_TXON	0x0010		/* transmitter on (R) */
#घोषणा CSR0_RXON	0x0020		/* receiver on (R) */
#घोषणा CSR0_INEA	0x0040		/* पूर्णांकerrupt enable (RW) */
#घोषणा CSR0_INTR	0x0080		/* पूर्णांकerrupt active (R) */
#घोषणा CSR0_IDON	0x0100		/* initialization करोne (RC) */
#घोषणा CSR0_TINT	0x0200		/* transmitter पूर्णांकerrupt (RC) */
#घोषणा CSR0_RINT	0x0400		/* receiver पूर्णांकerrupt (RC) */
#घोषणा CSR0_MERR	0x0800		/* memory error (RC) */
#घोषणा CSR0_MISS	0x1000		/* missed frame (RC) */
#घोषणा CSR0_CERR	0x2000		/* carrier error (no heartbeat :-) (RC) */
#घोषणा CSR0_BABL	0x4000		/* babble: tx-ed too many bits (RC) */
#घोषणा CSR0_ERR	0x8000		/* error (RC) */

/* CSR3 */
#घोषणा CSR3_BCON	0x0001		/* byte control */
#घोषणा CSR3_ACON	0x0002		/* ALE control */
#घोषणा CSR3_BSWP	0x0004		/* byte swap (1=big endian) */

/***************************** Prototypes *****************************/

अटल पूर्णांक lance_probe( काष्ठा net_device *dev);
अटल पूर्णांक lance_खोलो( काष्ठा net_device *dev );
अटल व्योम lance_init_ring( काष्ठा net_device *dev );
अटल netdev_tx_t lance_start_xmit(काष्ठा sk_buff *skb,
				    काष्ठा net_device *dev);
अटल irqवापस_t lance_पूर्णांकerrupt( पूर्णांक irq, व्योम *dev_id);
अटल पूर्णांक lance_rx( काष्ठा net_device *dev );
अटल पूर्णांक lance_बंद( काष्ठा net_device *dev );
अटल व्योम set_multicast_list( काष्ठा net_device *dev );

/************************* End of Prototypes **************************/

काष्ठा net_device * __init sun3lance_probe(पूर्णांक unit)
अणु
	काष्ठा net_device *dev;
	अटल पूर्णांक found;
	पूर्णांक err = -ENODEV;

	अगर (!MACH_IS_SUN3 && !MACH_IS_SUN3X)
		वापस ERR_PTR(-ENODEV);

	/* check that this machine has an onboard lance */
	चयन(idprom->id_machtype) अणु
	हाल SM_SUN3|SM_3_50:
	हाल SM_SUN3|SM_3_60:
	हाल SM_SUN3X|SM_3_80:
		/* these machines have lance */
		अवरोध;

	शेष:
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	अगर (found)
		वापस ERR_PTR(-ENODEV);

	dev = alloc_etherdev(माप(काष्ठा lance_निजी));
	अगर (!dev)
		वापस ERR_PTR(-ENOMEM);
	अगर (unit >= 0) अणु
		प्र_लिखो(dev->name, "eth%d", unit);
		netdev_boot_setup_check(dev);
	पूर्ण

	अगर (!lance_probe(dev))
		जाओ out;

	err = रेजिस्टर_netdev(dev);
	अगर (err)
		जाओ out1;
	found = 1;
	वापस dev;

out1:
#अगर_घोषित CONFIG_SUN3
	iounmap((व्योम __iomem *)dev->base_addr);
#पूर्ण_अगर
out:
	मुक्त_netdev(dev);
	वापस ERR_PTR(err);
पूर्ण

अटल स्थिर काष्ठा net_device_ops lance_netdev_ops = अणु
	.nकरो_खोलो		= lance_खोलो,
	.nकरो_stop		= lance_बंद,
	.nकरो_start_xmit		= lance_start_xmit,
	.nकरो_set_rx_mode	= set_multicast_list,
	.nकरो_set_mac_address	= शून्य,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक __init lance_probe( काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ ioaddr;

	काष्ठा lance_निजी	*lp;
	पूर्णांक 			i;
	अटल पूर्णांक 		did_version;
	अस्थिर अचिन्हित लघु *ioaddr_probe;
	अचिन्हित लघु पंचांगp1, पंचांगp2;

#अगर_घोषित CONFIG_SUN3
	ioaddr = (अचिन्हित दीर्घ)ioremap(LANCE_OBIO, PAGE_SIZE);
	अगर (!ioaddr)
		वापस 0;
#अन्यथा
	ioaddr = SUN3X_LANCE;
#पूर्ण_अगर

	/* test to see अगर there's really a lance here */
	/* (CSRO_INIT shouldn't be पढ़ोable) */

	ioaddr_probe = (अस्थिर अचिन्हित लघु *)ioaddr;
	पंचांगp1 = ioaddr_probe[0];
	पंचांगp2 = ioaddr_probe[1];

	ioaddr_probe[1] = CSR0;
	ioaddr_probe[0] = CSR0_INIT | CSR0_STOP;

	अगर(ioaddr_probe[0] != CSR0_STOP) अणु
		ioaddr_probe[0] = पंचांगp1;
		ioaddr_probe[1] = पंचांगp2;

#अगर_घोषित CONFIG_SUN3
		iounmap((व्योम __iomem *)ioaddr);
#पूर्ण_अगर
		वापस 0;
	पूर्ण

	lp = netdev_priv(dev);

	/* XXX - leak? */
	MEM = dvma_दो_स्मृति_align(माप(काष्ठा lance_memory), 0x10000);
	अगर (MEM == शून्य) अणु
#अगर_घोषित CONFIG_SUN3
		iounmap((व्योम __iomem *)ioaddr);
#पूर्ण_अगर
		prपूर्णांकk(KERN_WARNING "SUN3 Lance couldn't allocate DVMA memory\n");
		वापस 0;
	पूर्ण

	lp->iobase = (अस्थिर अचिन्हित लघु *)ioaddr;
	dev->base_addr = (अचिन्हित दीर्घ)ioaddr; /* inक्रमmational only */

	REGA(CSR0) = CSR0_STOP;

	अगर (request_irq(LANCE_IRQ, lance_पूर्णांकerrupt, 0, "SUN3 Lance", dev) < 0) अणु
#अगर_घोषित CONFIG_SUN3
		iounmap((व्योम __iomem *)ioaddr);
#पूर्ण_अगर
		dvma_मुक्त((व्योम *)MEM);
		prपूर्णांकk(KERN_WARNING "SUN3 Lance unable to allocate IRQ\n");
		वापस 0;
	पूर्ण
	dev->irq = (अचिन्हित लघु)LANCE_IRQ;


	prपूर्णांकk("%s: SUN3 Lance at io %#lx, mem %#lx, irq %d, hwaddr ",
		   dev->name,
		   (अचिन्हित दीर्घ)ioaddr,
		   (अचिन्हित दीर्घ)MEM,
		   dev->irq);

	/* copy in the ethernet address from the prom */
	क्रम(i = 0; i < 6 ; i++)
	     dev->dev_addr[i] = idprom->id_ethaddr[i];

	/* tell the card it's ether address, bytes swapped */
	MEM->init.hwaddr[0] = dev->dev_addr[1];
	MEM->init.hwaddr[1] = dev->dev_addr[0];
	MEM->init.hwaddr[2] = dev->dev_addr[3];
	MEM->init.hwaddr[3] = dev->dev_addr[2];
	MEM->init.hwaddr[4] = dev->dev_addr[5];
	MEM->init.hwaddr[5] = dev->dev_addr[4];

	prपूर्णांकk("%pM\n", dev->dev_addr);

	MEM->init.mode = 0x0000;
	MEM->init.filter[0] = 0x00000000;
	MEM->init.filter[1] = 0x00000000;
	MEM->init.rdra = dvma_vtob(MEM->rx_head);
	MEM->init.rlen    = (RX_LOG_RING_SIZE << 13) |
		(dvma_vtob(MEM->rx_head) >> 16);
	MEM->init.tdra = dvma_vtob(MEM->tx_head);
	MEM->init.tlen    = (TX_LOG_RING_SIZE << 13) |
		(dvma_vtob(MEM->tx_head) >> 16);

	DPRINTK(2, ("initaddr: %08lx rx_ring: %08lx tx_ring: %08lx\n",
	       dvma_vtob(&(MEM->init)), dvma_vtob(MEM->rx_head),
	       (dvma_vtob(MEM->tx_head))));

	अगर (did_version++ == 0)
		prपूर्णांकk( version );

	dev->netdev_ops = &lance_netdev_ops;
//	KLUDGE -- REMOVE ME
	set_bit(__LINK_STATE_PRESENT, &dev->state);


	वापस 1;
पूर्ण

अटल पूर्णांक lance_खोलो( काष्ठा net_device *dev )
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	पूर्णांक i;

	DPRINTK( 2, ( "%s: lance_open()\n", dev->name ));

	REGA(CSR0) = CSR0_STOP;

	lance_init_ring(dev);

	/* From now on, AREG is kept to poपूर्णांक to CSR0 */
	REGA(CSR0) = CSR0_INIT;

	i = 1000000;
	जबतक (--i > 0)
		अगर (DREG & CSR0_IDON)
			अवरोध;
	अगर (i <= 0 || (DREG & CSR0_ERR)) अणु
		DPRINTK( 2, ( "lance_open(): opening %s failed, i=%d, csr0=%04x\n",
					  dev->name, i, DREG ));
		DREG = CSR0_STOP;
		वापस -EIO;
	पूर्ण

	DREG = CSR0_IDON | CSR0_STRT | CSR0_INEA;

	netअगर_start_queue(dev);

	DPRINTK( 2, ( "%s: LANCE is open, csr0 %04x\n", dev->name, DREG ));

	वापस 0;
पूर्ण


/* Initialize the LANCE Rx and Tx rings. */

अटल व्योम lance_init_ring( काष्ठा net_device *dev )
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	पूर्णांक i;

	lp->lock = 0;
	lp->tx_full = 0;
	lp->new_rx = lp->new_tx = 0;
	lp->old_rx = lp->old_tx = 0;

	क्रम( i = 0; i < TX_RING_SIZE; i++ ) अणु
		MEM->tx_head[i].base = dvma_vtob(MEM->tx_data[i]);
		MEM->tx_head[i].flag = 0;
 		MEM->tx_head[i].base_hi =
			(dvma_vtob(MEM->tx_data[i])) >>16;
		MEM->tx_head[i].length = 0;
		MEM->tx_head[i].misc = 0;
	पूर्ण

	क्रम( i = 0; i < RX_RING_SIZE; i++ ) अणु
		MEM->rx_head[i].base = dvma_vtob(MEM->rx_data[i]);
		MEM->rx_head[i].flag = RMD1_OWN_CHIP;
		MEM->rx_head[i].base_hi =
			(dvma_vtob(MEM->rx_data[i])) >> 16;
		MEM->rx_head[i].buf_length = -PKT_BUF_SZ | 0xf000;
		MEM->rx_head[i].msg_length = 0;
	पूर्ण

	/* tell the card it's ether address, bytes swapped */
	MEM->init.hwaddr[0] = dev->dev_addr[1];
	MEM->init.hwaddr[1] = dev->dev_addr[0];
	MEM->init.hwaddr[2] = dev->dev_addr[3];
	MEM->init.hwaddr[3] = dev->dev_addr[2];
	MEM->init.hwaddr[4] = dev->dev_addr[5];
	MEM->init.hwaddr[5] = dev->dev_addr[4];

	MEM->init.mode = 0x0000;
	MEM->init.filter[0] = 0x00000000;
	MEM->init.filter[1] = 0x00000000;
	MEM->init.rdra = dvma_vtob(MEM->rx_head);
	MEM->init.rlen    = (RX_LOG_RING_SIZE << 13) |
		(dvma_vtob(MEM->rx_head) >> 16);
	MEM->init.tdra = dvma_vtob(MEM->tx_head);
	MEM->init.tlen    = (TX_LOG_RING_SIZE << 13) |
		(dvma_vtob(MEM->tx_head) >> 16);


	/* tell the lance the address of its init block */
	REGA(CSR1) = dvma_vtob(&(MEM->init));
	REGA(CSR2) = dvma_vtob(&(MEM->init)) >> 16;

#अगर_घोषित CONFIG_SUN3X
	REGA(CSR3) = CSR3_BSWP | CSR3_ACON | CSR3_BCON;
#अन्यथा
	REGA(CSR3) = CSR3_BSWP;
#पूर्ण_अगर

पूर्ण


अटल netdev_tx_t
lance_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	पूर्णांक entry, len;
	काष्ठा lance_tx_head *head;
	अचिन्हित दीर्घ flags;

	DPRINTK( 1, ( "%s: transmit start.\n",
		      dev->name));

	/* Transmitter समयout, serious problems. */
	अगर (netअगर_queue_stopped(dev)) अणु
		पूर्णांक tickssofar = jअगरfies - dev_trans_start(dev);
		अगर (tickssofar < HZ/5)
			वापस NETDEV_TX_BUSY;

		DPRINTK( 1, ( "%s: transmit timed out, status %04x, resetting.\n",
					  dev->name, DREG ));
		DREG = CSR0_STOP;
		/*
		 * Always set BSWP after a STOP as STOP माला_दो it back पूर्णांकo
		 * little endian mode.
		 */
		REGA(CSR3) = CSR3_BSWP;
		dev->stats.tx_errors++;

		अगर(lance_debug >= 2) अणु
			पूर्णांक i;
			prपूर्णांकk("Ring data: old_tx %d new_tx %d%s new_rx %d\n",
			       lp->old_tx, lp->new_tx,
			       lp->tx_full ? " (full)" : "",
			       lp->new_rx );
			क्रम( i = 0 ; i < RX_RING_SIZE; i++ )
				prपूर्णांकk( "rx #%d: base=%04x blen=%04x mlen=%04x\n",
					i, MEM->rx_head[i].base,
					-MEM->rx_head[i].buf_length,
					MEM->rx_head[i].msg_length);
			क्रम( i = 0 ; i < TX_RING_SIZE; i++ )
				prपूर्णांकk("tx #%d: base=%04x len=%04x misc=%04x\n",
				       i, MEM->tx_head[i].base,
				       -MEM->tx_head[i].length,
				       MEM->tx_head[i].misc );
		पूर्ण

		lance_init_ring(dev);
		REGA( CSR0 ) = CSR0_INEA | CSR0_INIT | CSR0_STRT;

		netअगर_start_queue(dev);

		वापस NETDEV_TX_OK;
	पूर्ण


	/* Block a समयr-based transmit from overlapping.  This could better be
	   करोne with atomic_swap(1, dev->tbusy), but set_bit() works as well. */

	/* Block a समयr-based transmit from overlapping with us by
	   stopping the queue क्रम a bit... */

	netअगर_stop_queue(dev);

	अगर (test_and_set_bit( 0, (व्योम*)&lp->lock ) != 0) अणु
		prपूर्णांकk( "%s: tx queue lock!.\n", dev->name);
		/* करोn't clear dev->tbusy flag. */
		वापस NETDEV_TX_BUSY;
	पूर्ण

	AREG = CSR0;
  	DPRINTK( 2, ( "%s: lance_start_xmit() called, csr0 %4.4x.\n",
  				  dev->name, DREG ));

#अगर_घोषित CONFIG_SUN3X
	/* this weirdness करोesn't appear on sun3... */
	अगर(!(DREG & CSR0_INIT)) अणु
		DPRINTK( 1, ("INIT not set, reinitializing...\n"));
		REGA( CSR0 ) = CSR0_STOP;
		lance_init_ring(dev);
		REGA( CSR0 ) = CSR0_INIT | CSR0_STRT;
	पूर्ण
#पूर्ण_अगर

	/* Fill in a Tx ring entry */
#अगर 0
	अगर (lance_debug >= 2) अणु
		prपूर्णांकk( "%s: TX pkt %d type 0x%04x"
			" from %s to %s"
			" data at 0x%08x len %d\n",
			dev->name, lp->new_tx, ((u_लघु *)skb->data)[6],
			DEV_ADDR(&skb->data[6]), DEV_ADDR(skb->data),
			(पूर्णांक)skb->data, (पूर्णांक)skb->len );
	पूर्ण
#पूर्ण_अगर
	/* We're not prepared क्रम the पूर्णांक until the last flags are set/reset.
	 * And the पूर्णांक may happen alपढ़ोy after setting the OWN_CHIP... */
	local_irq_save(flags);

	/* Mask to ring buffer boundary. */
	entry = lp->new_tx;
	head  = &(MEM->tx_head[entry]);

	/* Caution: the ग_लिखो order is important here, set the "ownership" bits
	 * last.
	 */

	/* the sun3's lance needs it's buffer padded to the minimum
	   size */
	len = (ETH_ZLEN < skb->len) ? skb->len : ETH_ZLEN;

//	head->length = -len;
	head->length = (-len) | 0xf000;
	head->misc = 0;

	skb_copy_from_linear_data(skb, PKTBUF_ADDR(head), skb->len);
	अगर (len != skb->len)
		स_रखो(PKTBUF_ADDR(head) + skb->len, 0, len-skb->len);

	head->flag = TMD1_OWN_CHIP | TMD1_ENP | TMD1_STP;
	lp->new_tx = (lp->new_tx + 1) & TX_RING_MOD_MASK;
	dev->stats.tx_bytes += skb->len;

	/* Trigger an immediate send poll. */
	REGA(CSR0) = CSR0_INEA | CSR0_TDMD | CSR0_STRT;
	AREG = CSR0;
  	DPRINTK( 2, ( "%s: lance_start_xmit() exiting, csr0 %4.4x.\n",
  				  dev->name, DREG ));
	dev_kमुक्त_skb(skb);

	lp->lock = 0;
	अगर ((MEM->tx_head[(entry+1) & TX_RING_MOD_MASK].flag & TMD1_OWN) ==
	    TMD1_OWN_HOST)
		netअगर_start_queue(dev);

	local_irq_restore(flags);

	वापस NETDEV_TX_OK;
पूर्ण

/* The LANCE पूर्णांकerrupt handler. */

अटल irqवापस_t lance_पूर्णांकerrupt( पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	पूर्णांक csr0;

 still_more:
	flush_cache_all();

	AREG = CSR0;
	csr0 = DREG;

	/* ack पूर्णांकerrupts */
	DREG = csr0 & (CSR0_TINT | CSR0_RINT | CSR0_IDON);

	/* clear errors */
	अगर(csr0 & CSR0_ERR)
		DREG = CSR0_BABL | CSR0_MERR | CSR0_CERR | CSR0_MISS;


	DPRINTK( 2, ( "%s: interrupt  csr0=%04x new csr=%04x.\n",
		      dev->name, csr0, DREG ));

	अगर (csr0 & CSR0_TINT) अणु			/* Tx-करोne पूर्णांकerrupt */
		पूर्णांक old_tx = lp->old_tx;

//		अगर(lance_debug >= 3) अणु
//			पूर्णांक i;
//
//			prपूर्णांकk("%s: tx int\n", dev->name);
//
//			क्रम(i = 0; i < TX_RING_SIZE; i++)
//				prपूर्णांकk("ring %d flag=%04x\n", i,
//				       MEM->tx_head[i].flag);
//		पूर्ण

		जबतक( old_tx != lp->new_tx) अणु
			काष्ठा lance_tx_head *head = &(MEM->tx_head[old_tx]);

			DPRINTK(3, ("on tx_ring %d\n", old_tx));

			अगर (head->flag & TMD1_OWN_CHIP)
				अवरोध; /* It still hasn't been Txed */

			अगर (head->flag & TMD1_ERR) अणु
				पूर्णांक status = head->misc;
				dev->stats.tx_errors++;
				अगर (status & TMD3_RTRY) dev->stats.tx_पातed_errors++;
				अगर (status & TMD3_LCAR) dev->stats.tx_carrier_errors++;
				अगर (status & TMD3_LCOL) dev->stats.tx_winकरोw_errors++;
				अगर (status & (TMD3_UFLO | TMD3_BUFF)) अणु
					dev->stats.tx_fअगरo_errors++;
					prपूर्णांकk("%s: Tx FIFO error\n",
					       dev->name);
					REGA(CSR0) = CSR0_STOP;
					REGA(CSR3) = CSR3_BSWP;
					lance_init_ring(dev);
					REGA(CSR0) = CSR0_STRT | CSR0_INEA;
					वापस IRQ_HANDLED;
				पूर्ण
			पूर्ण अन्यथा अगर(head->flag & (TMD1_ENP | TMD1_STP)) अणु

				head->flag &= ~(TMD1_ENP | TMD1_STP);
				अगर(head->flag & (TMD1_ONE | TMD1_MORE))
					dev->stats.collisions++;

				dev->stats.tx_packets++;
				DPRINTK(3, ("cleared tx ring %d\n", old_tx));
			पूर्ण
			old_tx = (old_tx +1) & TX_RING_MOD_MASK;
		पूर्ण

		lp->old_tx = old_tx;
	पूर्ण


	अगर (netअगर_queue_stopped(dev)) अणु
		/* The ring is no दीर्घer full, clear tbusy. */
		netअगर_start_queue(dev);
		netअगर_wake_queue(dev);
	पूर्ण

	अगर (csr0 & CSR0_RINT)			/* Rx पूर्णांकerrupt */
		lance_rx( dev );

	/* Log misc errors. */
	अगर (csr0 & CSR0_BABL) dev->stats.tx_errors++; /* Tx babble. */
	अगर (csr0 & CSR0_MISS) dev->stats.rx_errors++; /* Missed a Rx frame. */
	अगर (csr0 & CSR0_MERR) अणु
		DPRINTK( 1, ( "%s: Bus master arbitration failure (?!?), "
			      "status %04x.\n", dev->name, csr0 ));
		/* Restart the chip. */
		REGA(CSR0) = CSR0_STOP;
		REGA(CSR3) = CSR3_BSWP;
		lance_init_ring(dev);
		REGA(CSR0) = CSR0_STRT | CSR0_INEA;
	पूर्ण


    /* Clear any other पूर्णांकerrupt, and set पूर्णांकerrupt enable. */
//	DREG = CSR0_BABL | CSR0_CERR | CSR0_MISS | CSR0_MERR |
//		   CSR0_IDON | CSR0_INEA;

	REGA(CSR0) = CSR0_INEA;

	अगर(DREG & (CSR0_RINT | CSR0_TINT)) अणु
	     DPRINTK(2, ("restarting interrupt, csr0=%#04x\n", DREG));
	     जाओ still_more;
	पूर्ण

	DPRINTK( 2, ( "%s: exiting interrupt, csr0=%#04x.\n",
				  dev->name, DREG ));
	वापस IRQ_HANDLED;
पूर्ण

/* get packet, toss पूर्णांकo skbuff */
अटल पूर्णांक lance_rx( काष्ठा net_device *dev )
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	पूर्णांक entry = lp->new_rx;

	/* If we own the next entry, it's a new packet. Send it up. */
	जबतक( (MEM->rx_head[entry].flag & RMD1_OWN) == RMD1_OWN_HOST ) अणु
		काष्ठा lance_rx_head *head = &(MEM->rx_head[entry]);
		पूर्णांक status = head->flag;

		अगर (status != (RMD1_ENP|RMD1_STP)) अणु  /* There was an error. */
			/* There is a tricky error noted by John Murphy,
			   <murf@perftech.com> to Russ Nelson: Even with
			   full-sized buffers it's possible क्रम a jabber packet to use two
			   buffers, with only the last correctly noting the error. */
			अगर (status & RMD1_ENP)	/* Only count a general error at the */
				dev->stats.rx_errors++; /* end of a packet.*/
			अगर (status & RMD1_FRAM) dev->stats.rx_frame_errors++;
			अगर (status & RMD1_OFLO) dev->stats.rx_over_errors++;
			अगर (status & RMD1_CRC) dev->stats.rx_crc_errors++;
			अगर (status & RMD1_BUFF) dev->stats.rx_fअगरo_errors++;
			head->flag &= (RMD1_ENP|RMD1_STP);
		पूर्ण अन्यथा अणु
			/* Malloc up new buffer, compatible with net-3. */
//			लघु pkt_len = head->msg_length;// & 0xfff;
			लघु pkt_len = (head->msg_length & 0xfff) - 4;
			काष्ठा sk_buff *skb;

			अगर (pkt_len < 60) अणु
				prपूर्णांकk( "%s: Runt packet!\n", dev->name );
				dev->stats.rx_errors++;
			पूर्ण
			अन्यथा अणु
				skb = netdev_alloc_skb(dev, pkt_len + 2);
				अगर (skb == शून्य) अणु
					dev->stats.rx_dropped++;
					head->msg_length = 0;
					head->flag |= RMD1_OWN_CHIP;
					lp->new_rx = (lp->new_rx+1) &
					     RX_RING_MOD_MASK;
				पूर्ण

#अगर 0
				अगर (lance_debug >= 3) अणु
					u_अक्षर *data = PKTBUF_ADDR(head);
					prपूर्णांकk("%s: RX pkt %d type 0x%04x"
					       " from %pM to %pM",
					       dev->name, lp->new_tx, ((u_लघु *)data)[6],
					       &data[6], data);

					prपूर्णांकk(" data %02x %02x %02x %02x %02x %02x %02x %02x "
					       "len %d at %08x\n",
					       data[15], data[16], data[17], data[18],
					       data[19], data[20], data[21], data[22],
					       pkt_len, data);
				पूर्ण
#पूर्ण_अगर
				अगर (lance_debug >= 3) अणु
					u_अक्षर *data = PKTBUF_ADDR(head);
					prपूर्णांकk( "%s: RX pkt %d type 0x%04x len %d\n ", dev->name, entry, ((u_लघु *)data)[6], pkt_len);
				पूर्ण


				skb_reserve( skb, 2 );	/* 16 byte align */
				skb_put( skb, pkt_len );	/* Make room */
				skb_copy_to_linear_data(skb,
						 PKTBUF_ADDR(head),
						 pkt_len);

				skb->protocol = eth_type_trans( skb, dev );
				netअगर_rx( skb );
				dev->stats.rx_packets++;
				dev->stats.rx_bytes += pkt_len;
			पूर्ण
		पूर्ण

//		head->buf_length = -PKT_BUF_SZ | 0xf000;
		head->msg_length = 0;
		head->flag = RMD1_OWN_CHIP;

		entry = lp->new_rx = (lp->new_rx +1) & RX_RING_MOD_MASK;
	पूर्ण

	/* From lance.c (Donald Becker): */
	/* We should check that at least two ring entries are मुक्त.
	   If not, we should मुक्त one and mark stats->rx_dropped++. */

	वापस 0;
पूर्ण


अटल पूर्णांक lance_बंद( काष्ठा net_device *dev )
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);

	netअगर_stop_queue(dev);

	AREG = CSR0;

	DPRINTK( 2, ( "%s: Shutting down ethercard, status was %2.2x.\n",
				  dev->name, DREG ));

	/* We stop the LANCE here -- it occasionally polls
	   memory अगर we करोn't. */
	DREG = CSR0_STOP;
	वापस 0;
पूर्ण


/* Set or clear the multicast filter क्रम this adaptor.
   num_addrs == -1		Promiscuous mode, receive all packets
   num_addrs == 0		Normal mode, clear multicast list
   num_addrs > 0		Multicast mode, receive normal and MC packets, and करो
						best-efक्रमt filtering.
 */

/* completely untested on a sun3 */
अटल व्योम set_multicast_list( काष्ठा net_device *dev )
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);

	अगर(netअगर_queue_stopped(dev))
		/* Only possible अगर board is alपढ़ोy started */
		वापस;

	/* We take the simple way out and always enable promiscuous mode. */
	DREG = CSR0_STOP; /* Temporarily stop the lance. */

	अगर (dev->flags & IFF_PROMISC) अणु
		/* Log any net taps. */
		DPRINTK( 3, ( "%s: Promiscuous mode enabled.\n", dev->name ));
		REGA( CSR15 ) = 0x8000; /* Set promiscuous mode */
	पूर्ण अन्यथा अणु
		लघु multicast_table[4];
		पूर्णांक num_addrs = netdev_mc_count(dev);
		पूर्णांक i;
		/* We करोn't use the multicast table, but rely on upper-layer
		 * filtering. */
		स_रखो( multicast_table, (num_addrs == 0) ? 0 : -1,
				माप(multicast_table) );
		क्रम( i = 0; i < 4; i++ )
			REGA( CSR8+i ) = multicast_table[i];
		REGA( CSR15 ) = 0; /* Unset promiscuous mode */
	पूर्ण

	/*
	 * Always set BSWP after a STOP as STOP माला_दो it back पूर्णांकo
	 * little endian mode.
	 */
	REGA( CSR3 ) = CSR3_BSWP;

	/* Resume normal operation and reset AREG to CSR0 */
	REGA( CSR0 ) = CSR0_IDON | CSR0_INEA | CSR0_STRT;
पूर्ण


#अगर_घोषित MODULE

अटल काष्ठा net_device *sun3lance_dev;

पूर्णांक __init init_module(व्योम)
अणु
	sun3lance_dev = sun3lance_probe(-1);
	वापस PTR_ERR_OR_ZERO(sun3lance_dev);
पूर्ण

व्योम __निकास cleanup_module(व्योम)
अणु
	unरेजिस्टर_netdev(sun3lance_dev);
#अगर_घोषित CONFIG_SUN3
	iounmap((व्योम __iomem *)sun3lance_dev->base_addr);
#पूर्ण_अगर
	मुक्त_netdev(sun3lance_dev);
पूर्ण

#पूर्ण_अगर /* MODULE */

