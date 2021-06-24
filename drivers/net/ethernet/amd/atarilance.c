<शैली गुरु>
/* atarilance.c: Ethernet driver क्रम VME Lance cards on the Atari */
/*
	Written 1995/96 by Roman Hodek (Roman.Hodek@inक्रमmatik.uni-erlangen.de)

	This software may be used and distributed according to the terms
	of the GNU General Public License, incorporated herein by reference.

	This drivers was written with the following sources of reference:
	 - The driver क्रम the Riebl Lance card by the TU Vienna.
	 - The modअगरied TUW driver क्रम PAM's VME cards
	 - The PC-Linux driver क्रम Lance cards (but this is क्रम bus master
       cards, not the shared memory ones)
	 - The Amiga Ariadne driver

	v1.0: (in 1.2.13pl4/0.9.13)
	      Initial version
	v1.1: (in 1.2.13pl5)
	      more comments
		  deleted some debugging stuff
		  optimized रेजिस्टर access (keep AREG poपूर्णांकing to CSR0)
		  following AMD, CSR0_STRT should be set only after IDON is detected
		  use स_नकल() क्रम data transfers, that also employs दीर्घ word moves
		  better probe procedure क्रम 24-bit प्रणालीs
          non-VME-RieblCards need extra delays in स_नकल
		  must also करो ग_लिखो test, since 0xfxe00000 may hit ROM
		  use 8/32 tx/rx buffers, which should give better NFS perक्रमmance;
		    this is made possible by shअगरting the last packet buffer after the
		    RieblCard reserved area
    v1.2: (in 1.2.13pl8)
	      again fixed probing क्रम the Falcon; 0xfe01000 hits phys. 0x00010000
		  and thus RAM, in हाल of no Lance found all memory contents have to
		  be restored!
		  Now possible to compile as module.
	v1.3: 03/30/96 Jes Sorensen, Roman (in 1.3)
	      Several little 1.3 adaptions
		  When the lance is stopped it jumps back पूर्णांकo little-endian
		  mode. It is thereक्रमe necessary to put it back where it
		  beदीर्घs, in big endian mode, in order to make things work.
		  This might be the reason why multicast-mode didn't work
		  beक्रमe, but I'm not able to test it as I only got an Amiga
		  (we had similar problems with the A2065 driver).

*/

अटल स्थिर अक्षर version[] = "atarilance.c: v1.3 04/04/96 "
			      "Roman.Hodek@informatik.uni-erlangen.de\n";

#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/atarihw.h>
#समावेश <यंत्र/atariपूर्णांकs.h>
#समावेश <यंत्र/पन.स>

/* Debug level:
 *  0 = silent, prपूर्णांक only serious errors
 *  1 = normal, prपूर्णांक error messages
 *  2 = debug, prपूर्णांक debug infos
 *  3 = debug, prपूर्णांक even more debug infos (packet data)
 */

#घोषणा	LANCE_DEBUG	1

#अगर_घोषित LANCE_DEBUG
अटल पूर्णांक lance_debug = LANCE_DEBUG;
#अन्यथा
अटल पूर्णांक lance_debug = 1;
#पूर्ण_अगर
module_param(lance_debug, पूर्णांक, 0);
MODULE_PARM_DESC(lance_debug, "atarilance debug level (0-3)");
MODULE_LICENSE("GPL");

/* Prपूर्णांक debug messages on probing? */
#अघोषित LANCE_DEBUG_PROBE

#घोषणा	DPRINTK(n,a)							\
	करो अणु										\
		अगर (lance_debug >= n)					\
			prपूर्णांकk a;							\
	पूर्ण जबतक( 0 )

#अगर_घोषित LANCE_DEBUG_PROBE
# define PROBE_PRINT(a)	prपूर्णांकk a
#अन्यथा
# define PROBE_PRINT(a)
#पूर्ण_अगर

/* These define the number of Rx and Tx buffers as log2. (Only घातers
 * of two are valid)
 * Much more rx buffers (32) are reserved than tx buffers (8), since receiving
 * is more समय critical then sending and packets may have to reमुख्य in the
 * board's memory when मुख्य memory is low.
 */

#घोषणा TX_LOG_RING_SIZE			3
#घोषणा RX_LOG_RING_SIZE			5

/* These are the derived values */

#घोषणा TX_RING_SIZE			(1 << TX_LOG_RING_SIZE)
#घोषणा TX_RING_LEN_BITS		(TX_LOG_RING_SIZE << 5)
#घोषणा	TX_RING_MOD_MASK		(TX_RING_SIZE - 1)

#घोषणा RX_RING_SIZE			(1 << RX_LOG_RING_SIZE)
#घोषणा RX_RING_LEN_BITS		(RX_LOG_RING_SIZE << 5)
#घोषणा	RX_RING_MOD_MASK		(RX_RING_SIZE - 1)

#घोषणा TX_TIMEOUT	(HZ/5)

/* The LANCE Rx and Tx ring descriptors. */
काष्ठा lance_rx_head अणु
	अचिन्हित लघु			base;		/* Low word of base addr */
	अस्थिर अचिन्हित अक्षर	flag;
	अचिन्हित अक्षर			base_hi;	/* High word of base addr (unused) */
	लघु					buf_length;	/* This length is 2s complement! */
	अस्थिर लघु			msg_length;	/* This length is "normal". */
पूर्ण;

काष्ठा lance_tx_head अणु
	अचिन्हित लघु			base;		/* Low word of base addr */
	अस्थिर अचिन्हित अक्षर	flag;
	अचिन्हित अक्षर			base_hi;	/* High word of base addr (unused) */
	लघु					length;		/* Length is 2s complement! */
	अस्थिर लघु			misc;
पूर्ण;

काष्ठा ringdesc अणु
	अचिन्हित लघु	adr_lo;		/* Low 16 bits of address */
	अचिन्हित अक्षर	len;		/* Length bits */
	अचिन्हित अक्षर	adr_hi;		/* High 8 bits of address (unused) */
पूर्ण;

/* The LANCE initialization block, described in databook. */
काष्ठा lance_init_block अणु
	अचिन्हित लघु	mode;		/* Pre-set mode */
	अचिन्हित अक्षर	hwaddr[6];	/* Physical ethernet address */
	अचिन्हित		filter[2];	/* Multicast filter (unused). */
	/* Receive and transmit ring base, aदीर्घ with length bits. */
	काष्ठा ringdesc	rx_ring;
	काष्ठा ringdesc	tx_ring;
पूर्ण;

/* The whole layout of the Lance shared memory */
काष्ठा lance_memory अणु
	काष्ठा lance_init_block	init;
	काष्ठा lance_tx_head	tx_head[TX_RING_SIZE];
	काष्ठा lance_rx_head	rx_head[RX_RING_SIZE];
	अक्षर					packet_area[];	/* packet data follow after the
											 * init block and the ring
											 * descriptors and are located
											 * at runसमय */
पूर्ण;

/* RieblCard specअगरics:
 * The original TOS driver क्रम these cards reserves the area from offset
 * 0xee70 to 0xeebb क्रम storing configuration data. Of पूर्णांकerest to us is the
 * Ethernet address there, and the magic क्रम verअगरying the data's validity.
 * The reserved area isn't touch by packet buffers. Furthermore, offset 0xfffe
 * is reserved क्रम the पूर्णांकerrupt vector number.
 */
#घोषणा	RIEBL_RSVD_START	0xee70
#घोषणा	RIEBL_RSVD_END		0xeec0
#घोषणा RIEBL_MAGIC			0x09051990
#घोषणा RIEBL_MAGIC_ADDR	((अचिन्हित दीर्घ *)(((अक्षर *)MEM) + 0xee8a))
#घोषणा RIEBL_HWADDR_ADDR	((अचिन्हित अक्षर *)(((अक्षर *)MEM) + 0xee8e))
#घोषणा RIEBL_IVEC_ADDR		((अचिन्हित लघु *)(((अक्षर *)MEM) + 0xfffe))

/* This is a शेष address क्रम the old RieblCards without a battery
 * that have no ethernet address at boot समय. 00:00:36:04 is the
 * prefix क्रम Riebl cards, the 00:00 at the end is arbitrary.
 */

अटल अचिन्हित अक्षर OldRieblDefHwaddr[6] = अणु
	0x00, 0x00, 0x36, 0x04, 0x00, 0x00
पूर्ण;


/* I/O रेजिस्टरs of the Lance chip */

काष्ठा lance_ioreg अणु
/* base+0x0 */	अस्थिर अचिन्हित लघु	data;
/* base+0x2 */	अस्थिर अचिन्हित लघु	addr;
				अचिन्हित अक्षर			_dummy1[3];
/* base+0x7 */	अस्थिर अचिन्हित अक्षर	ivec;
				अचिन्हित अक्षर			_dummy2[5];
/* base+0xd */	अस्थिर अचिन्हित अक्षर	eeprom;
				अचिन्हित अक्षर			_dummy3;
/* base+0xf */	अस्थिर अचिन्हित अक्षर	mem;
पूर्ण;

/* Types of boards this driver supports */

क्रमागत lance_type अणु
	OLD_RIEBL,		/* old Riebl card without battery */
	NEW_RIEBL,		/* new Riebl card with battery */
	PAM_CARD		/* PAM card with EEPROM */
पूर्ण;

अटल अक्षर *lance_names[] = अणु
	"Riebl-Card (without battery)",
	"Riebl-Card (with battery)",
	"PAM intern card"
पूर्ण;

/* The driver's निजी device काष्ठाure */

काष्ठा lance_निजी अणु
	क्रमागत lance_type		cardtype;
	काष्ठा lance_ioreg	*iobase;
	काष्ठा lance_memory	*mem;
	पूर्णांक		 	cur_rx, cur_tx;	/* The next मुक्त ring entry */
	पूर्णांक			dirty_tx;		/* Ring entries to be मुक्तd. */
				/* copy function */
	व्योम			*(*स_नकल_f)( व्योम *, स्थिर व्योम *, माप_प्रकार );
/* This must be दीर्घ क्रम set_bit() */
	दीर्घ			tx_full;
	spinlock_t		devlock;
पूर्ण;

/* I/O रेजिस्टर access macros */

#घोषणा	MEM		lp->mem
#घोषणा	DREG	IO->data
#घोषणा	AREG	IO->addr
#घोषणा	REGA(a)	(*( AREG = (a), &DREG ))

/* Definitions क्रम packet buffer access: */
#घोषणा PKT_BUF_SZ		1544
/* Get the address of a packet buffer corresponding to a given buffer head */
#घोषणा	PKTBUF_ADDR(head)	(((अचिन्हित अक्षर *)(MEM)) + (head)->base)

/* Possible memory/IO addresses क्रम probing */

अटल काष्ठा lance_addr अणु
	अचिन्हित दीर्घ	memaddr;
	अचिन्हित दीर्घ	ioaddr;
	पूर्णांक				slow_flag;
पूर्ण lance_addr_list[] = अणु
	अणु 0xfe010000, 0xfe00fff0, 0 पूर्ण,	/* RieblCard VME in TT */
	अणु 0xffc10000, 0xffc0fff0, 0 पूर्ण,	/* RieblCard VME in MegaSTE
									   (highest byte stripped) */
	अणु 0xffe00000, 0xffff7000, 1 पूर्ण,	/* RieblCard in ST
									   (highest byte stripped) */
	अणु 0xffd00000, 0xffff7000, 1 पूर्ण,	/* RieblCard in ST with hw modअगर. to
									   aव्योम conflict with ROM
									   (highest byte stripped) */
	अणु 0xffcf0000, 0xffcffff0, 0 पूर्ण,	/* PAMCard VME in TT and MSTE
									   (highest byte stripped) */
	अणु 0xfecf0000, 0xfecffff0, 0 पूर्ण,	/* Rhotron's PAMCard VME in TT and MSTE
									   (highest byte stripped) */
पूर्ण;

#घोषणा	N_LANCE_ADDR	ARRAY_SIZE(lance_addr_list)


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

अटल अचिन्हित दीर्घ lance_probe1( काष्ठा net_device *dev, काष्ठा lance_addr
                                   *init_rec );
अटल पूर्णांक lance_खोलो( काष्ठा net_device *dev );
अटल व्योम lance_init_ring( काष्ठा net_device *dev );
अटल netdev_tx_t lance_start_xmit(काष्ठा sk_buff *skb,
				    काष्ठा net_device *dev);
अटल irqवापस_t lance_पूर्णांकerrupt( पूर्णांक irq, व्योम *dev_id );
अटल पूर्णांक lance_rx( काष्ठा net_device *dev );
अटल पूर्णांक lance_बंद( काष्ठा net_device *dev );
अटल व्योम set_multicast_list( काष्ठा net_device *dev );
अटल पूर्णांक lance_set_mac_address( काष्ठा net_device *dev, व्योम *addr );
अटल व्योम lance_tx_समयout (काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);

/************************* End of Prototypes **************************/





अटल व्योम *slow_स_नकल( व्योम *dst, स्थिर व्योम *src, माप_प्रकार len )

अणु	अक्षर *cto = dst;
	स्थिर अक्षर *cfrom = src;

	जबतक( len-- ) अणु
		*cto++ = *cfrom++;
		MFPDELAY();
	पूर्ण
	वापस dst;
पूर्ण


काष्ठा net_device * __init atarilance_probe(पूर्णांक unit)
अणु
	पूर्णांक i;
	अटल पूर्णांक found;
	काष्ठा net_device *dev;
	पूर्णांक err = -ENODEV;

	अगर (!MACH_IS_ATARI || found)
		/* Assume there's only one board possible... That seems true, since
		 * the Riebl/PAM board's address cannot be changed. */
		वापस ERR_PTR(-ENODEV);

	dev = alloc_etherdev(माप(काष्ठा lance_निजी));
	अगर (!dev)
		वापस ERR_PTR(-ENOMEM);
	अगर (unit >= 0) अणु
		प्र_लिखो(dev->name, "eth%d", unit);
		netdev_boot_setup_check(dev);
	पूर्ण

	क्रम( i = 0; i < N_LANCE_ADDR; ++i ) अणु
		अगर (lance_probe1( dev, &lance_addr_list[i] )) अणु
			found = 1;
			err = रेजिस्टर_netdev(dev);
			अगर (!err)
				वापस dev;
			मुक्त_irq(dev->irq, dev);
			अवरोध;
		पूर्ण
	पूर्ण
	मुक्त_netdev(dev);
	वापस ERR_PTR(err);
पूर्ण


/* Derived from hwreg_present() in atari/config.c: */

अटल noअंतरभूत पूर्णांक __init addr_accessible(अस्थिर व्योम *regp, पूर्णांक wordflag,
					   पूर्णांक ग_लिखोflag)
अणु
	पूर्णांक		ret;
	अचिन्हित दीर्घ	flags;
	दीर्घ	*vbr, save_berr;

	local_irq_save(flags);

	__यंत्र__ __अस्थिर__ ( "movec	%/vbr,%0" : "=r" (vbr) : );
	save_berr = vbr[2];

	__यंत्र__ __अस्थिर__
	(	"movel	%/sp,%/d1\n\t"
		"movel	#Lberr,%2@\n\t"
		"moveq	#0,%0\n\t"
		"tstl   %3\n\t"
		"bne	1f\n\t"
		"moveb	%1@,%/d0\n\t"
		"nop	\n\t"
		"bra	2f\n"
"1:		 movew	%1@,%/d0\n\t"
		"nop	\n"
"2:		 tstl   %4\n\t"
		"beq	2f\n\t"
		"tstl	%3\n\t"
		"bne	1f\n\t"
		"clrb	%1@\n\t"
		"nop	\n\t"
		"moveb	%/d0,%1@\n\t"
		"nop	\n\t"
		"bra	2f\n"
"1:		 clrw	%1@\n\t"
		"nop	\n\t"
		"movew	%/d0,%1@\n\t"
		"nop	\n"
"2:		 moveq	#1,%0\n"
"Lberr:	 movel	%/d1,%/sp"
		: "=&d" (ret)
		: "a" (regp), "a" (&vbr[2]), "rm" (wordflag), "rm" (ग_लिखोflag)
		: "d0", "d1", "memory"
	);

	vbr[2] = save_berr;
	local_irq_restore(flags);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा net_device_ops lance_netdev_ops = अणु
	.nकरो_खोलो		= lance_खोलो,
	.nकरो_stop		= lance_बंद,
	.nकरो_start_xmit		= lance_start_xmit,
	.nकरो_set_rx_mode	= set_multicast_list,
	.nकरो_set_mac_address	= lance_set_mac_address,
	.nकरो_tx_समयout		= lance_tx_समयout,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल अचिन्हित दीर्घ __init lance_probe1( काष्ठा net_device *dev,
					   काष्ठा lance_addr *init_rec )
अणु
	अस्थिर अचिन्हित लघु *memaddr =
		(अस्थिर अचिन्हित लघु *)init_rec->memaddr;
	अस्थिर अचिन्हित लघु *ioaddr =
		(अस्थिर अचिन्हित लघु *)init_rec->ioaddr;
	काष्ठा lance_निजी	*lp;
	काष्ठा lance_ioreg		*IO;
	पूर्णांक 					i;
	अटल पूर्णांक 				did_version;
	अचिन्हित लघु			save1, save2;

	PROBE_PRINT(( "Probing for Lance card at mem %#lx io %#lx\n",
				  (दीर्घ)memaddr, (दीर्घ)ioaddr ));

	/* Test whether memory पढ़ोable and writable */
	PROBE_PRINT(( "lance_probe1: testing memory to be accessible\n" ));
	अगर (!addr_accessible( memaddr, 1, 1 )) जाओ probe_fail;

	/* Written values should come back... */
	PROBE_PRINT(( "lance_probe1: testing memory to be writable (1)\n" ));
	save1 = *memaddr;
	*memaddr = 0x0001;
	अगर (*memaddr != 0x0001) जाओ probe_fail;
	PROBE_PRINT(( "lance_probe1: testing memory to be writable (2)\n" ));
	*memaddr = 0x0000;
	अगर (*memaddr != 0x0000) जाओ probe_fail;
	*memaddr = save1;

	/* First port should be पढ़ोable and writable */
	PROBE_PRINT(( "lance_probe1: testing ioport to be accessible\n" ));
	अगर (!addr_accessible( ioaddr, 1, 1 )) जाओ probe_fail;

	/* and written values should be पढ़ोable */
	PROBE_PRINT(( "lance_probe1: testing ioport to be writeable\n" ));
	save2 = ioaddr[1];
	ioaddr[1] = 0x0001;
	अगर (ioaddr[1] != 0x0001) जाओ probe_fail;

	/* The CSR0_INIT bit should not be पढ़ोable */
	PROBE_PRINT(( "lance_probe1: testing CSR0 register function (1)\n" ));
	save1 = ioaddr[0];
	ioaddr[1] = CSR0;
	ioaddr[0] = CSR0_INIT | CSR0_STOP;
	अगर (ioaddr[0] != CSR0_STOP) अणु
		ioaddr[0] = save1;
		ioaddr[1] = save2;
		जाओ probe_fail;
	पूर्ण
	PROBE_PRINT(( "lance_probe1: testing CSR0 register function (2)\n" ));
	ioaddr[0] = CSR0_STOP;
	अगर (ioaddr[0] != CSR0_STOP) अणु
		ioaddr[0] = save1;
		ioaddr[1] = save2;
		जाओ probe_fail;
	पूर्ण

	/* Now ok... */
	PROBE_PRINT(( "lance_probe1: Lance card detected\n" ));
	जाओ probe_ok;

  probe_fail:
	वापस 0;

  probe_ok:
	lp = netdev_priv(dev);
	MEM = (काष्ठा lance_memory *)memaddr;
	IO = lp->iobase = (काष्ठा lance_ioreg *)ioaddr;
	dev->base_addr = (अचिन्हित दीर्घ)ioaddr; /* inक्रमmational only */
	lp->स_नकल_f = init_rec->slow_flag ? slow_स_नकल : स_नकल;

	REGA( CSR0 ) = CSR0_STOP;

	/* Now test क्रम type: If the eeprom I/O port is पढ़ोable, it is a
	 * PAM card */
	अगर (addr_accessible( &(IO->eeprom), 0, 0 )) अणु
		/* Switch back to Ram */
		i = IO->mem;
		lp->cardtype = PAM_CARD;
	पूर्ण
	अन्यथा अगर (*RIEBL_MAGIC_ADDR == RIEBL_MAGIC) अणु
		lp->cardtype = NEW_RIEBL;
	पूर्ण
	अन्यथा
		lp->cardtype = OLD_RIEBL;

	अगर (lp->cardtype == PAM_CARD ||
		memaddr == (अचिन्हित लघु *)0xffe00000) अणु
		/* PAMs card and Riebl on ST use level 5 स्वतःvector */
		अगर (request_irq(IRQ_AUTO_5, lance_पूर्णांकerrupt, 0,
				"PAM,Riebl-ST Ethernet", dev)) अणु
			prपूर्णांकk( "Lance: request for irq %d failed\n", IRQ_AUTO_5 );
			वापस 0;
		पूर्ण
		dev->irq = IRQ_AUTO_5;
	पूर्ण
	अन्यथा अणु
		/* For VME-RieblCards, request a मुक्त VME पूर्णांक */
		अचिन्हित पूर्णांक irq = atari_रेजिस्टर_vme_पूर्णांक();
		अगर (!irq) अणु
			prपूर्णांकk( "Lance: request for VME interrupt failed\n" );
			वापस 0;
		पूर्ण
		अगर (request_irq(irq, lance_पूर्णांकerrupt, 0, "Riebl-VME Ethernet",
				dev)) अणु
			prपूर्णांकk( "Lance: request for irq %u failed\n", irq );
			वापस 0;
		पूर्ण
		dev->irq = irq;
	पूर्ण

	prपूर्णांकk("%s: %s at io %#lx, mem %#lx, irq %d%s, hwaddr ",
		   dev->name, lance_names[lp->cardtype],
		   (अचिन्हित दीर्घ)ioaddr,
		   (अचिन्हित दीर्घ)memaddr,
		   dev->irq,
		   init_rec->slow_flag ? " (slow memcpy)" : "" );

	/* Get the ethernet address */
	चयन( lp->cardtype ) अणु
	  हाल OLD_RIEBL:
		/* No ethernet address! (Set some शेष address) */
		स_नकल(dev->dev_addr, OldRieblDefHwaddr, ETH_ALEN);
		अवरोध;
	  हाल NEW_RIEBL:
		lp->स_नकल_f(dev->dev_addr, RIEBL_HWADDR_ADDR, ETH_ALEN);
		अवरोध;
	  हाल PAM_CARD:
		i = IO->eeprom;
		क्रम( i = 0; i < 6; ++i )
			dev->dev_addr[i] =
				((((अचिन्हित लघु *)MEM)[i*2] & 0x0f) << 4) |
				((((अचिन्हित लघु *)MEM)[i*2+1] & 0x0f));
		i = IO->mem;
		अवरोध;
	पूर्ण
	prपूर्णांकk("%pM\n", dev->dev_addr);
	अगर (lp->cardtype == OLD_RIEBL) अणु
		prपूर्णांकk( "%s: Warning: This is a default ethernet address!\n",
				dev->name );
		prपूर्णांकk( "      Use \"ifconfig hw ether ...\" to set the address.\n" );
	पूर्ण

	spin_lock_init(&lp->devlock);

	MEM->init.mode = 0x0000;		/* Disable Rx and Tx. */
	क्रम( i = 0; i < 6; i++ )
		MEM->init.hwaddr[i] = dev->dev_addr[i^1]; /* <- 16 bit swap! */
	MEM->init.filter[0] = 0x00000000;
	MEM->init.filter[1] = 0x00000000;
	MEM->init.rx_ring.adr_lo = दुरत्व( काष्ठा lance_memory, rx_head );
	MEM->init.rx_ring.adr_hi = 0;
	MEM->init.rx_ring.len    = RX_RING_LEN_BITS;
	MEM->init.tx_ring.adr_lo = दुरत्व( काष्ठा lance_memory, tx_head );
	MEM->init.tx_ring.adr_hi = 0;
	MEM->init.tx_ring.len    = TX_RING_LEN_BITS;

	अगर (lp->cardtype == PAM_CARD)
		IO->ivec = IRQ_SOURCE_TO_VECTOR(dev->irq);
	अन्यथा
		*RIEBL_IVEC_ADDR = IRQ_SOURCE_TO_VECTOR(dev->irq);

	अगर (did_version++ == 0)
		DPRINTK( 1, ( version ));

	dev->netdev_ops = &lance_netdev_ops;

	/* XXX MSch */
	dev->watchकरोg_समयo = TX_TIMEOUT;

	वापस 1;
पूर्ण


अटल पूर्णांक lance_खोलो( काष्ठा net_device *dev )
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	काष्ठा lance_ioreg	 *IO = lp->iobase;
	पूर्णांक i;

	DPRINTK( 2, ( "%s: lance_open()\n", dev->name ));

	lance_init_ring(dev);
	/* Re-initialize the LANCE, and start it when करोne. */

	REGA( CSR3 ) = CSR3_BSWP | (lp->cardtype == PAM_CARD ? CSR3_ACON : 0);
	REGA( CSR2 ) = 0;
	REGA( CSR1 ) = 0;
	REGA( CSR0 ) = CSR0_INIT;
	/* From now on, AREG is kept to poपूर्णांक to CSR0 */

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
	DREG = CSR0_IDON;
	DREG = CSR0_STRT;
	DREG = CSR0_INEA;

	netअगर_start_queue (dev);

	DPRINTK( 2, ( "%s: LANCE is open, csr0 %04x\n", dev->name, DREG ));

	वापस 0;
पूर्ण


/* Initialize the LANCE Rx and Tx rings. */

अटल व्योम lance_init_ring( काष्ठा net_device *dev )
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	पूर्णांक i;
	अचिन्हित offset;

	lp->tx_full = 0;
	lp->cur_rx = lp->cur_tx = 0;
	lp->dirty_tx = 0;

	offset = दुरत्व( काष्ठा lance_memory, packet_area );

/* If the packet buffer at offset 'o' would conflict with the reserved area
 * of RieblCards, advance it */
#घोषणा	CHECK_OFFSET(o)														 \
	करो अणु																	 \
		अगर (lp->cardtype == OLD_RIEBL || lp->cardtype == NEW_RIEBL) अणु		 \
			अगर (((o) < RIEBL_RSVD_START) ? (o)+PKT_BUF_SZ > RIEBL_RSVD_START \
										 : (o) < RIEBL_RSVD_END)			 \
				(o) = RIEBL_RSVD_END;										 \
		पूर्ण																	 \
	पूर्ण जबतक(0)

	क्रम( i = 0; i < TX_RING_SIZE; i++ ) अणु
		CHECK_OFFSET(offset);
		MEM->tx_head[i].base = offset;
		MEM->tx_head[i].flag = TMD1_OWN_HOST;
 		MEM->tx_head[i].base_hi = 0;
		MEM->tx_head[i].length = 0;
		MEM->tx_head[i].misc = 0;
		offset += PKT_BUF_SZ;
	पूर्ण

	क्रम( i = 0; i < RX_RING_SIZE; i++ ) अणु
		CHECK_OFFSET(offset);
		MEM->rx_head[i].base = offset;
		MEM->rx_head[i].flag = TMD1_OWN_CHIP;
		MEM->rx_head[i].base_hi = 0;
		MEM->rx_head[i].buf_length = -PKT_BUF_SZ;
		MEM->rx_head[i].msg_length = 0;
		offset += PKT_BUF_SZ;
	पूर्ण
पूर्ण


/* XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX */


अटल व्योम lance_tx_समयout (काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	काष्ठा lance_ioreg	 *IO = lp->iobase;

	AREG = CSR0;
	DPRINTK( 1, ( "%s: transmit timed out, status %04x, resetting.\n",
			  dev->name, DREG ));
	DREG = CSR0_STOP;
	/*
	 * Always set BSWP after a STOP as STOP माला_दो it back पूर्णांकo
	 * little endian mode.
	 */
	REGA( CSR3 ) = CSR3_BSWP | (lp->cardtype == PAM_CARD ? CSR3_ACON : 0);
	dev->stats.tx_errors++;
#अगर_अघोषित final_version
		अणु	पूर्णांक i;
			DPRINTK( 2, ( "Ring data: dirty_tx %d cur_tx %d%s cur_rx %d\n",
						  lp->dirty_tx, lp->cur_tx,
						  lp->tx_full ? " (full)" : "",
						  lp->cur_rx ));
			क्रम( i = 0 ; i < RX_RING_SIZE; i++ )
				DPRINTK( 2, ( "rx #%d: base=%04x blen=%04x mlen=%04x\n",
							  i, MEM->rx_head[i].base,
							  -MEM->rx_head[i].buf_length,
							  MEM->rx_head[i].msg_length ));
			क्रम( i = 0 ; i < TX_RING_SIZE; i++ )
				DPRINTK( 2, ( "tx #%d: base=%04x len=%04x misc=%04x\n",
							  i, MEM->tx_head[i].base,
							  -MEM->tx_head[i].length,
							  MEM->tx_head[i].misc ));
		पूर्ण
#पूर्ण_अगर
	/* XXX MSch: maybe purge/reinit ring here */
	/* lance_restart, essentially */
	lance_init_ring(dev);
	REGA( CSR0 ) = CSR0_INEA | CSR0_INIT | CSR0_STRT;
	netअगर_trans_update(dev); /* prevent tx समयout */
	netअगर_wake_queue(dev);
पूर्ण

/* XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX */

अटल netdev_tx_t
lance_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	काष्ठा lance_ioreg	 *IO = lp->iobase;
	पूर्णांक entry, len;
	काष्ठा lance_tx_head *head;
	अचिन्हित दीर्घ flags;

	DPRINTK( 2, ( "%s: lance_start_xmit() called, csr0 %4.4x.\n",
				  dev->name, DREG ));


	/* The old LANCE chips करोesn't स्वतःmatically pad buffers to min. size. */
	len = skb->len;
	अगर (len < ETH_ZLEN)
		len = ETH_ZLEN;
	/* PAM-Card has a bug: Can only send packets with even number of bytes! */
	अन्यथा अगर (lp->cardtype == PAM_CARD && (len & 1))
		++len;

	अगर (len > skb->len) अणु
		अगर (skb_padto(skb, len))
			वापस NETDEV_TX_OK;
	पूर्ण

	netअगर_stop_queue (dev);

	/* Fill in a Tx ring entry */
	अगर (lance_debug >= 3) अणु
		prपूर्णांकk( "%s: TX pkt type 0x%04x from %pM to %pM"
				" data at 0x%08x len %d\n",
				dev->name, ((u_लघु *)skb->data)[6],
				&skb->data[6], skb->data,
				(पूर्णांक)skb->data, (पूर्णांक)skb->len );
	पूर्ण

	/* We're not prepared क्रम the पूर्णांक until the last flags are set/reset. And
	 * the पूर्णांक may happen alपढ़ोy after setting the OWN_CHIP... */
	spin_lock_irqsave (&lp->devlock, flags);

	/* Mask to ring buffer boundary. */
	entry = lp->cur_tx & TX_RING_MOD_MASK;
	head  = &(MEM->tx_head[entry]);

	/* Caution: the ग_लिखो order is important here, set the "ownership" bits
	 * last.
	 */


	head->length = -len;
	head->misc = 0;
	lp->स_नकल_f( PKTBUF_ADDR(head), (व्योम *)skb->data, skb->len );
	head->flag = TMD1_OWN_CHIP | TMD1_ENP | TMD1_STP;
	dev->stats.tx_bytes += skb->len;
	dev_kमुक्त_skb( skb );
	lp->cur_tx++;
	जबतक( lp->cur_tx >= TX_RING_SIZE && lp->dirty_tx >= TX_RING_SIZE ) अणु
		lp->cur_tx -= TX_RING_SIZE;
		lp->dirty_tx -= TX_RING_SIZE;
	पूर्ण

	/* Trigger an immediate send poll. */
	DREG = CSR0_INEA | CSR0_TDMD;

	अगर ((MEM->tx_head[(entry+1) & TX_RING_MOD_MASK].flag & TMD1_OWN) ==
		TMD1_OWN_HOST)
		netअगर_start_queue (dev);
	अन्यथा
		lp->tx_full = 1;
	spin_unlock_irqrestore (&lp->devlock, flags);

	वापस NETDEV_TX_OK;
पूर्ण

/* The LANCE पूर्णांकerrupt handler. */

अटल irqवापस_t lance_पूर्णांकerrupt( पूर्णांक irq, व्योम *dev_id )
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा lance_निजी *lp;
	काष्ठा lance_ioreg	 *IO;
	पूर्णांक csr0, boguscnt = 10;
	पूर्णांक handled = 0;

	अगर (dev == शून्य) अणु
		DPRINTK( 1, ( "lance_interrupt(): interrupt for unknown device.\n" ));
		वापस IRQ_NONE;
	पूर्ण

	lp = netdev_priv(dev);
	IO = lp->iobase;
	spin_lock (&lp->devlock);

	AREG = CSR0;

	जबतक( ((csr0 = DREG) & (CSR0_ERR | CSR0_TINT | CSR0_RINT)) &&
		   --boguscnt >= 0) अणु
		handled = 1;
		/* Acknowledge all of the current पूर्णांकerrupt sources ASAP. */
		DREG = csr0 & ~(CSR0_INIT | CSR0_STRT | CSR0_STOP |
									CSR0_TDMD | CSR0_INEA);

		DPRINTK( 2, ( "%s: interrupt  csr0=%04x new csr=%04x.\n",
					  dev->name, csr0, DREG ));

		अगर (csr0 & CSR0_RINT)			/* Rx पूर्णांकerrupt */
			lance_rx( dev );

		अगर (csr0 & CSR0_TINT) अणु			/* Tx-करोne पूर्णांकerrupt */
			पूर्णांक dirty_tx = lp->dirty_tx;

			जबतक( dirty_tx < lp->cur_tx) अणु
				पूर्णांक entry = dirty_tx & TX_RING_MOD_MASK;
				पूर्णांक status = MEM->tx_head[entry].flag;

				अगर (status & TMD1_OWN_CHIP)
					अवरोध;			/* It still hasn't been Txed */

				MEM->tx_head[entry].flag = 0;

				अगर (status & TMD1_ERR) अणु
					/* There was an major error, log it. */
					पूर्णांक err_status = MEM->tx_head[entry].misc;
					dev->stats.tx_errors++;
					अगर (err_status & TMD3_RTRY) dev->stats.tx_पातed_errors++;
					अगर (err_status & TMD3_LCAR) dev->stats.tx_carrier_errors++;
					अगर (err_status & TMD3_LCOL) dev->stats.tx_winकरोw_errors++;
					अगर (err_status & TMD3_UFLO) अणु
						/* Ackk!  On FIFO errors the Tx unit is turned off! */
						dev->stats.tx_fअगरo_errors++;
						/* Remove this verbosity later! */
						DPRINTK( 1, ( "%s: Tx FIFO error! Status %04x\n",
									  dev->name, csr0 ));
						/* Restart the chip. */
						DREG = CSR0_STRT;
					पूर्ण
				पूर्ण अन्यथा अणु
					अगर (status & (TMD1_MORE | TMD1_ONE | TMD1_DEF))
						dev->stats.collisions++;
					dev->stats.tx_packets++;
				पूर्ण

				/* XXX MSch: मुक्त skb?? */
				dirty_tx++;
			पूर्ण

#अगर_अघोषित final_version
			अगर (lp->cur_tx - dirty_tx >= TX_RING_SIZE) अणु
				DPRINTK( 0, ( "out-of-sync dirty pointer,"
							  " %d vs. %d, full=%ld.\n",
							  dirty_tx, lp->cur_tx, lp->tx_full ));
				dirty_tx += TX_RING_SIZE;
			पूर्ण
#पूर्ण_अगर

			अगर (lp->tx_full && (netअगर_queue_stopped(dev)) &&
				dirty_tx > lp->cur_tx - TX_RING_SIZE + 2) अणु
				/* The ring is no दीर्घer full, clear tbusy. */
				lp->tx_full = 0;
				netअगर_wake_queue (dev);
			पूर्ण

			lp->dirty_tx = dirty_tx;
		पूर्ण

		/* Log misc errors. */
		अगर (csr0 & CSR0_BABL) dev->stats.tx_errors++; /* Tx babble. */
		अगर (csr0 & CSR0_MISS) dev->stats.rx_errors++; /* Missed a Rx frame. */
		अगर (csr0 & CSR0_MERR) अणु
			DPRINTK( 1, ( "%s: Bus master arbitration failure (?!?), "
						  "status %04x.\n", dev->name, csr0 ));
			/* Restart the chip. */
			DREG = CSR0_STRT;
		पूर्ण
	पूर्ण

    /* Clear any other पूर्णांकerrupt, and set पूर्णांकerrupt enable. */
	DREG = CSR0_BABL | CSR0_CERR | CSR0_MISS | CSR0_MERR |
		   CSR0_IDON | CSR0_INEA;

	DPRINTK( 2, ( "%s: exiting interrupt, csr0=%#04x.\n",
				  dev->name, DREG ));

	spin_unlock (&lp->devlock);
	वापस IRQ_RETVAL(handled);
पूर्ण


अटल पूर्णांक lance_rx( काष्ठा net_device *dev )
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	पूर्णांक entry = lp->cur_rx & RX_RING_MOD_MASK;
	पूर्णांक i;

	DPRINTK( 2, ( "%s: rx int, flag=%04x\n", dev->name,
				  MEM->rx_head[entry].flag ));

	/* If we own the next entry, it's a new packet. Send it up. */
	जबतक( (MEM->rx_head[entry].flag & RMD1_OWN) == RMD1_OWN_HOST ) अणु
		काष्ठा lance_rx_head *head = &(MEM->rx_head[entry]);
		पूर्णांक status = head->flag;

		अगर (status != (RMD1_ENP|RMD1_STP)) अणु		/* There was an error. */
			/* There is a tricky error noted by John Murphy,
			   <murf@perftech.com> to Russ Nelson: Even with full-sized
			   buffers it's possible क्रम a jabber packet to use two
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
			लघु pkt_len = head->msg_length & 0xfff;
			काष्ठा sk_buff *skb;

			अगर (pkt_len < 60) अणु
				prपूर्णांकk( "%s: Runt packet!\n", dev->name );
				dev->stats.rx_errors++;
			पूर्ण
			अन्यथा अणु
				skb = netdev_alloc_skb(dev, pkt_len + 2);
				अगर (skb == शून्य) अणु
					क्रम( i = 0; i < RX_RING_SIZE; i++ )
						अगर (MEM->rx_head[(entry+i) & RX_RING_MOD_MASK].flag &
							RMD1_OWN_CHIP)
							अवरोध;

					अगर (i > RX_RING_SIZE - 2) अणु
						dev->stats.rx_dropped++;
						head->flag |= RMD1_OWN_CHIP;
						lp->cur_rx++;
					पूर्ण
					अवरोध;
				पूर्ण

				अगर (lance_debug >= 3) अणु
					u_अक्षर *data = PKTBUF_ADDR(head);

					prपूर्णांकk(KERN_DEBUG "%s: RX pkt type 0x%04x from %pM to %pM "
						   "data %8ph len %d\n",
						   dev->name, ((u_लघु *)data)[6],
						   &data[6], data, &data[15], pkt_len);
				पूर्ण

				skb_reserve( skb, 2 );	/* 16 byte align */
				skb_put( skb, pkt_len );	/* Make room */
				lp->स_नकल_f( skb->data, PKTBUF_ADDR(head), pkt_len );
				skb->protocol = eth_type_trans( skb, dev );
				netअगर_rx( skb );
				dev->stats.rx_packets++;
				dev->stats.rx_bytes += pkt_len;
			पूर्ण
		पूर्ण

		head->flag |= RMD1_OWN_CHIP;
		entry = (++lp->cur_rx) & RX_RING_MOD_MASK;
	पूर्ण
	lp->cur_rx &= RX_RING_MOD_MASK;

	/* From lance.c (Donald Becker): */
	/* We should check that at least two ring entries are मुक्त.	 If not,
	   we should मुक्त one and mark stats->rx_dropped++. */

	वापस 0;
पूर्ण


अटल पूर्णांक lance_बंद( काष्ठा net_device *dev )
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	काष्ठा lance_ioreg	 *IO = lp->iobase;

	netअगर_stop_queue (dev);

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

अटल व्योम set_multicast_list( काष्ठा net_device *dev )
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	काष्ठा lance_ioreg	 *IO = lp->iobase;

	अगर (netअगर_running(dev))
		/* Only possible अगर board is alपढ़ोy started */
		वापस;

	/* We take the simple way out and always enable promiscuous mode. */
	DREG = CSR0_STOP; /* Temporarily stop the lance. */

	अगर (dev->flags & IFF_PROMISC) अणु
		/* Log any net taps. */
		DPRINTK( 2, ( "%s: Promiscuous mode enabled.\n", dev->name ));
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
	REGA( CSR3 ) = CSR3_BSWP | (lp->cardtype == PAM_CARD ? CSR3_ACON : 0);

	/* Resume normal operation and reset AREG to CSR0 */
	REGA( CSR0 ) = CSR0_IDON | CSR0_INEA | CSR0_STRT;
पूर्ण


/* This is needed क्रम old RieblCards and possible क्रम new RieblCards */

अटल पूर्णांक lance_set_mac_address( काष्ठा net_device *dev, व्योम *addr )
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	काष्ठा sockaddr *saddr = addr;
	पूर्णांक i;

	अगर (lp->cardtype != OLD_RIEBL && lp->cardtype != NEW_RIEBL)
		वापस -EOPNOTSUPP;

	अगर (netअगर_running(dev)) अणु
		/* Only possible जबतक card isn't started */
		DPRINTK( 1, ( "%s: hwaddr can be set only while card isn't open.\n",
					  dev->name ));
		वापस -EIO;
	पूर्ण

	स_नकल( dev->dev_addr, saddr->sa_data, dev->addr_len );
	क्रम( i = 0; i < 6; i++ )
		MEM->init.hwaddr[i] = dev->dev_addr[i^1]; /* <- 16 bit swap! */
	lp->स_नकल_f( RIEBL_HWADDR_ADDR, dev->dev_addr, 6 );
	/* set also the magic क्रम future sessions */
	*RIEBL_MAGIC_ADDR = RIEBL_MAGIC;

	वापस 0;
पूर्ण


#अगर_घोषित MODULE
अटल काष्ठा net_device *atarilance_dev;

अटल पूर्णांक __init atarilance_module_init(व्योम)
अणु
	atarilance_dev = atarilance_probe(-1);
	वापस PTR_ERR_OR_ZERO(atarilance_dev);
पूर्ण

अटल व्योम __निकास atarilance_module_निकास(व्योम)
अणु
	unरेजिस्टर_netdev(atarilance_dev);
	मुक्त_irq(atarilance_dev->irq, atarilance_dev);
	मुक्त_netdev(atarilance_dev);
पूर्ण
module_init(atarilance_module_init);
module_निकास(atarilance_module_निकास);
#पूर्ण_अगर /* MODULE */
