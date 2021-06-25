<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *    Lance ethernet driver क्रम the MIPS processor based
 *      DECstation family
 *
 *
 *      aकरोpted from sunlance.c by Riअक्षरd van den Berg
 *
 *      Copyright (C) 2002, 2003, 2005, 2006  Maciej W. Rozycki
 *
 *      additional sources:
 *      - PMAD-AA TURBOchannel Ethernet Module Functional Specअगरication,
 *        Revision 1.2
 *
 *      History:
 *
 *      v0.001: The kernel accepts the code and it shows the hardware address.
 *
 *      v0.002: Removed most sparc stuff, left only some module and dma stuff.
 *
 *      v0.003: Enhanced base address calculation from proposals by
 *              Harald Koerfgen and Thomas Riemer.
 *
 *      v0.004: lance-regs is poपूर्णांकing at the right addresses, added prom
 *              check. First start of address mapping and DMA.
 *
 *      v0.005: started to play around with LANCE-DMA. This driver will not
 *              work क्रम non IOASIC lances. HK
 *
 *      v0.006: added poपूर्णांकer arrays to lance_निजी and setup routine क्रम
 *              them in dec_lance_init. HK
 *
 *      v0.007: Big shit. The LANCE seems to use a dअगरferent DMA mechanism to
 *              access the init block. This looks like one (लघु) word at a
 *              समय, but the smallest amount the IOASIC can transfer is a
 *              (दीर्घ) word. So we have a 2-2 padding here. Changed
 *              lance_init_block accordingly. The 16-16 padding क्रम the buffers
 *              seems to be correct. HK
 *
 *      v0.008: mods to make PMAX_LANCE work. 01/09/1999 triemer
 *
 *      v0.009: Module support fixes, multiple पूर्णांकerfaces support, various
 *              bits. macro
 *
 *      v0.010: Fixes क्रम the PMAD mapping of the LANCE buffer and क्रम the
 *              PMAX requirement to only use halfword accesses to the
 *              buffer. macro
 *
 *      v0.011: Converted the PMAD to the driver model. macro
 */

#समावेश <linux/crc32.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/माला.स>
#समावेश <linux/tc.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/addrspace.h>

#समावेश <यंत्र/dec/पूर्णांकerrupts.h>
#समावेश <यंत्र/dec/ioasic.h>
#समावेश <यंत्र/dec/ioasic_addrs.h>
#समावेश <यंत्र/dec/kn01.h>
#समावेश <यंत्र/dec/machtype.h>
#समावेश <यंत्र/dec/प्रणाली.h>

अटल स्थिर अक्षर version[] =
"declance.c: v0.011 by Linux MIPS DECstation task force\n";

MODULE_AUTHOR("Linux MIPS DECstation task force");
MODULE_DESCRIPTION("DEC LANCE (DECstation onboard, PMAD-xx) driver");
MODULE_LICENSE("GPL");

#घोषणा __unused __attribute__ ((unused))

/*
 * card types
 */
#घोषणा ASIC_LANCE 1
#घोषणा PMAD_LANCE 2
#घोषणा PMAX_LANCE 3


#घोषणा LE_CSR0 0
#घोषणा LE_CSR1 1
#घोषणा LE_CSR2 2
#घोषणा LE_CSR3 3

#घोषणा LE_MO_PROM      0x8000	/* Enable promiscuous mode */

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

#घोषणा	LE_C3_BSWP	0x4	/* SWAP */
#घोषणा	LE_C3_ACON	0x2	/* ALE Control */
#घोषणा	LE_C3_BCON	0x1	/* Byte control */

/* Receive message descriptor 1 */
#घोषणा LE_R1_OWN	0x8000	/* Who owns the entry */
#घोषणा LE_R1_ERR	0x4000	/* Error: अगर FRA, OFL, CRC or BUF is set */
#घोषणा LE_R1_FRA	0x2000	/* FRA: Frame error */
#घोषणा LE_R1_OFL	0x1000	/* OFL: Frame overflow */
#घोषणा LE_R1_CRC	0x0800	/* CRC error */
#घोषणा LE_R1_BUF	0x0400	/* BUF: Buffer error */
#घोषणा LE_R1_SOP	0x0200	/* Start of packet */
#घोषणा LE_R1_EOP	0x0100	/* End of packet */
#घोषणा LE_R1_POK	0x0300	/* Packet is complete: SOP + EOP */

/* Transmit message descriptor 1 */
#घोषणा LE_T1_OWN	0x8000	/* Lance owns the packet */
#घोषणा LE_T1_ERR	0x4000	/* Error summary */
#घोषणा LE_T1_EMORE	0x1000	/* Error: more than one retry needed */
#घोषणा LE_T1_EONE	0x0800	/* Error: one retry needed */
#घोषणा LE_T1_EDEF	0x0400	/* Error: deferred */
#घोषणा LE_T1_SOP	0x0200	/* Start of packet */
#घोषणा LE_T1_EOP	0x0100	/* End of packet */
#घोषणा LE_T1_POK	0x0300	/* Packet is complete: SOP + EOP */

#घोषणा LE_T3_BUF       0x8000	/* Buffer error */
#घोषणा LE_T3_UFL       0x4000	/* Error underflow */
#घोषणा LE_T3_LCOL      0x1000	/* Error late collision */
#घोषणा LE_T3_CLOS      0x0800	/* Error carrier loss */
#घोषणा LE_T3_RTY       0x0400	/* Error retry */
#घोषणा LE_T3_TDR       0x03ff	/* Time Doमुख्य Reflectometry counter */

/* Define: 2^4 Tx buffers and 2^4 Rx buffers */

#अगर_अघोषित LANCE_LOG_TX_BUFFERS
#घोषणा LANCE_LOG_TX_BUFFERS 4
#घोषणा LANCE_LOG_RX_BUFFERS 4
#पूर्ण_अगर

#घोषणा TX_RING_SIZE			(1 << (LANCE_LOG_TX_BUFFERS))
#घोषणा TX_RING_MOD_MASK		(TX_RING_SIZE - 1)

#घोषणा RX_RING_SIZE			(1 << (LANCE_LOG_RX_BUFFERS))
#घोषणा RX_RING_MOD_MASK		(RX_RING_SIZE - 1)

#घोषणा PKT_BUF_SZ		1536
#घोषणा RX_BUFF_SIZE            PKT_BUF_SZ
#घोषणा TX_BUFF_SIZE            PKT_BUF_SZ

#अघोषित TEST_HITS
#घोषणा ZERO 0

/*
 * The DS2100/3100 have a linear 64 kB buffer which supports halfword
 * accesses only.  Each halfword of the buffer is word-aligned in the
 * CPU address space.
 *
 * The PMAD-AA has a 128 kB buffer on-board.
 *
 * The IOASIC LANCE devices use a shared memory region.  This region
 * as seen from the CPU is (max) 128 kB दीर्घ and has to be on an 128 kB
 * boundary.  The LANCE sees this as a 64 kB दीर्घ continuous memory
 * region.
 *
 * The LANCE's DMA address is used as an index in this buffer and DMA
 * takes place in bursts of eight 16-bit words which are packed पूर्णांकo
 * four 32-bit words by the IOASIC.  This leads to a strange padding:
 * 16 bytes of valid data followed by a 16 byte gap :-(.
 */

काष्ठा lance_rx_desc अणु
	अचिन्हित लघु rmd0;		/* low address of packet */
	अचिन्हित लघु rmd1;		/* high address of packet
					   and descriptor bits */
	लघु length;			/* 2s complement (negative!)
					   of buffer length */
	अचिन्हित लघु mblength;	/* actual number of bytes received */
पूर्ण;

काष्ठा lance_tx_desc अणु
	अचिन्हित लघु पंचांगd0;		/* low address of packet */
	अचिन्हित लघु पंचांगd1;		/* high address of packet
					   and descriptor bits */
	लघु length;			/* 2s complement (negative!)
					   of buffer length */
	अचिन्हित लघु misc;
पूर्ण;


/* First part of the LANCE initialization block, described in databook. */
काष्ठा lance_init_block अणु
	अचिन्हित लघु mode;		/* pre-set mode (reg. 15) */

	अचिन्हित लघु phys_addr[3];	/* physical ethernet address */
	अचिन्हित लघु filter[4];	/* multicast filter */

	/* Receive and transmit ring base, aदीर्घ with extra bits. */
	अचिन्हित लघु rx_ptr;		/* receive descriptor addr */
	अचिन्हित लघु rx_len;		/* receive len and high addr */
	अचिन्हित लघु tx_ptr;		/* transmit descriptor addr */
	अचिन्हित लघु tx_len;		/* transmit len and high addr */

	लघु gap[4];

	/* The buffer descriptors */
	काष्ठा lance_rx_desc brx_ring[RX_RING_SIZE];
	काष्ठा lance_tx_desc btx_ring[TX_RING_SIZE];
पूर्ण;

#घोषणा BUF_OFFSET_CPU माप(काष्ठा lance_init_block)
#घोषणा BUF_OFFSET_LNC माप(काष्ठा lance_init_block)

#घोषणा shअगरt_off(off, type)						\
	(type == ASIC_LANCE || type == PMAX_LANCE ? off << 1 : off)

#घोषणा lib_off(rt, type)						\
	shअगरt_off(दुरत्व(काष्ठा lance_init_block, rt), type)

#घोषणा lib_ptr(ib, rt, type) 						\
	((अस्थिर u16 *)((u8 *)(ib) + lib_off(rt, type)))

#घोषणा rds_off(rt, type)						\
	shअगरt_off(दुरत्व(काष्ठा lance_rx_desc, rt), type)

#घोषणा rds_ptr(rd, rt, type) 						\
	((अस्थिर u16 *)((u8 *)(rd) + rds_off(rt, type)))

#घोषणा tds_off(rt, type)						\
	shअगरt_off(दुरत्व(काष्ठा lance_tx_desc, rt), type)

#घोषणा tds_ptr(td, rt, type) 						\
	((अस्थिर u16 *)((u8 *)(td) + tds_off(rt, type)))

काष्ठा lance_निजी अणु
	काष्ठा net_device *next;
	पूर्णांक type;
	पूर्णांक dma_irq;
	अस्थिर काष्ठा lance_regs *ll;

	spinlock_t	lock;

	पूर्णांक rx_new, tx_new;
	पूर्णांक rx_old, tx_old;

	अचिन्हित लघु busmaster_regval;

	काष्ठा समयr_list       multicast_समयr;
	काष्ठा net_device	*dev;

	/* Poपूर्णांकers to the ring buffers as seen from the CPU */
	अक्षर *rx_buf_ptr_cpu[RX_RING_SIZE];
	अक्षर *tx_buf_ptr_cpu[TX_RING_SIZE];

	/* Poपूर्णांकers to the ring buffers as seen from the LANCE */
	uपूर्णांक rx_buf_ptr_lnc[RX_RING_SIZE];
	uपूर्णांक tx_buf_ptr_lnc[TX_RING_SIZE];
पूर्ण;

#घोषणा TX_BUFFS_AVAIL ((lp->tx_old<=lp->tx_new)?\
			lp->tx_old+TX_RING_MOD_MASK-lp->tx_new:\
			lp->tx_old - lp->tx_new-1)

/* The lance control ports are at an असलolute address, machine and tc-slot
 * dependent.
 * DECstations करो only 32-bit access and the LANCE uses 16 bit addresses,
 * so we have to give the काष्ठाure an extra member making rap poपूर्णांकing
 * at the right address
 */
काष्ठा lance_regs अणु
	अस्थिर अचिन्हित लघु rdp;	/* रेजिस्टर data port */
	अचिन्हित लघु pad;
	अस्थिर अचिन्हित लघु rap;	/* रेजिस्टर address port */
पूर्ण;

पूर्णांक dec_lance_debug = 2;

अटल काष्ठा tc_driver dec_lance_tc_driver;
अटल काष्ठा net_device *root_lance_dev;

अटल अंतरभूत व्योम ग_लिखोreg(अस्थिर अचिन्हित लघु *regptr, लघु value)
अणु
	*regptr = value;
	iob();
पूर्ण

/* Load the CSR रेजिस्टरs */
अटल व्योम load_csrs(काष्ठा lance_निजी *lp)
अणु
	अस्थिर काष्ठा lance_regs *ll = lp->ll;
	uपूर्णांक leptr;

	/* The address space as seen from the LANCE
	 * begins at address 0. HK
	 */
	leptr = 0;

	ग_लिखोreg(&ll->rap, LE_CSR1);
	ग_लिखोreg(&ll->rdp, (leptr & 0xFFFF));
	ग_लिखोreg(&ll->rap, LE_CSR2);
	ग_लिखोreg(&ll->rdp, leptr >> 16);
	ग_लिखोreg(&ll->rap, LE_CSR3);
	ग_लिखोreg(&ll->rdp, lp->busmaster_regval);

	/* Poपूर्णांक back to csr0 */
	ग_लिखोreg(&ll->rap, LE_CSR0);
पूर्ण

/*
 * Our specialized copy routines
 *
 */
अटल व्योम cp_to_buf(स्थिर पूर्णांक type, व्योम *to, स्थिर व्योम *from, पूर्णांक len)
अणु
	अचिन्हित लघु *tp;
	स्थिर अचिन्हित लघु *fp;
	अचिन्हित लघु clen;
	अचिन्हित अक्षर *rtp;
	स्थिर अचिन्हित अक्षर *rfp;

	अगर (type == PMAD_LANCE) अणु
		स_नकल(to, from, len);
	पूर्ण अन्यथा अगर (type == PMAX_LANCE) अणु
		clen = len >> 1;
		tp = to;
		fp = from;

		जबतक (clen--) अणु
			*tp++ = *fp++;
			tp++;
		पूर्ण

		clen = len & 1;
		rtp = (अचिन्हित अक्षर *)tp;
		rfp = (स्थिर अचिन्हित अक्षर *)fp;
		जबतक (clen--) अणु
			*rtp++ = *rfp++;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * copy 16 Byte chunks
		 */
		clen = len >> 4;
		tp = to;
		fp = from;
		जबतक (clen--) अणु
			*tp++ = *fp++;
			*tp++ = *fp++;
			*tp++ = *fp++;
			*tp++ = *fp++;
			*tp++ = *fp++;
			*tp++ = *fp++;
			*tp++ = *fp++;
			*tp++ = *fp++;
			tp += 8;
		पूर्ण

		/*
		 * करो the rest, अगर any.
		 */
		clen = len & 15;
		rtp = (अचिन्हित अक्षर *)tp;
		rfp = (स्थिर अचिन्हित अक्षर *)fp;
		जबतक (clen--) अणु
			*rtp++ = *rfp++;
		पूर्ण
	पूर्ण

	iob();
पूर्ण

अटल व्योम cp_from_buf(स्थिर पूर्णांक type, व्योम *to, स्थिर व्योम *from, पूर्णांक len)
अणु
	अचिन्हित लघु *tp;
	स्थिर अचिन्हित लघु *fp;
	अचिन्हित लघु clen;
	अचिन्हित अक्षर *rtp;
	स्थिर अचिन्हित अक्षर *rfp;

	अगर (type == PMAD_LANCE) अणु
		स_नकल(to, from, len);
	पूर्ण अन्यथा अगर (type == PMAX_LANCE) अणु
		clen = len >> 1;
		tp = to;
		fp = from;
		जबतक (clen--) अणु
			*tp++ = *fp++;
			fp++;
		पूर्ण

		clen = len & 1;

		rtp = (अचिन्हित अक्षर *)tp;
		rfp = (स्थिर अचिन्हित अक्षर *)fp;

		जबतक (clen--) अणु
			*rtp++ = *rfp++;
		पूर्ण
	पूर्ण अन्यथा अणु

		/*
		 * copy 16 Byte chunks
		 */
		clen = len >> 4;
		tp = to;
		fp = from;
		जबतक (clen--) अणु
			*tp++ = *fp++;
			*tp++ = *fp++;
			*tp++ = *fp++;
			*tp++ = *fp++;
			*tp++ = *fp++;
			*tp++ = *fp++;
			*tp++ = *fp++;
			*tp++ = *fp++;
			fp += 8;
		पूर्ण

		/*
		 * करो the rest, अगर any.
		 */
		clen = len & 15;
		rtp = (अचिन्हित अक्षर *)tp;
		rfp = (स्थिर अचिन्हित अक्षर *)fp;
		जबतक (clen--) अणु
			*rtp++ = *rfp++;
		पूर्ण


	पूर्ण

पूर्ण

/* Setup the Lance Rx and Tx rings */
अटल व्योम lance_init_ring(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	अस्थिर u16 *ib = (अस्थिर u16 *)dev->mem_start;
	uपूर्णांक leptr;
	पूर्णांक i;

	/* Lock out other processes जबतक setting up hardware */
	netअगर_stop_queue(dev);
	lp->rx_new = lp->tx_new = 0;
	lp->rx_old = lp->tx_old = 0;

	/* Copy the ethernet address to the lance init block.
	 * XXX bit 0 of the physical address रेजिस्टरs has to be zero
	 */
	*lib_ptr(ib, phys_addr[0], lp->type) = (dev->dev_addr[1] << 8) |
				     dev->dev_addr[0];
	*lib_ptr(ib, phys_addr[1], lp->type) = (dev->dev_addr[3] << 8) |
				     dev->dev_addr[2];
	*lib_ptr(ib, phys_addr[2], lp->type) = (dev->dev_addr[5] << 8) |
				     dev->dev_addr[4];
	/* Setup the initialization block */

	/* Setup rx descriptor poपूर्णांकer */
	leptr = दुरत्व(काष्ठा lance_init_block, brx_ring);
	*lib_ptr(ib, rx_len, lp->type) = (LANCE_LOG_RX_BUFFERS << 13) |
					 (leptr >> 16);
	*lib_ptr(ib, rx_ptr, lp->type) = leptr;
	अगर (ZERO)
		prपूर्णांकk("RX ptr: %8.8x(%8.8x)\n",
		       leptr, (uपूर्णांक)lib_off(brx_ring, lp->type));

	/* Setup tx descriptor poपूर्णांकer */
	leptr = दुरत्व(काष्ठा lance_init_block, btx_ring);
	*lib_ptr(ib, tx_len, lp->type) = (LANCE_LOG_TX_BUFFERS << 13) |
					 (leptr >> 16);
	*lib_ptr(ib, tx_ptr, lp->type) = leptr;
	अगर (ZERO)
		prपूर्णांकk("TX ptr: %8.8x(%8.8x)\n",
		       leptr, (uपूर्णांक)lib_off(btx_ring, lp->type));

	अगर (ZERO)
		prपूर्णांकk("TX rings:\n");

	/* Setup the Tx ring entries */
	क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
		leptr = lp->tx_buf_ptr_lnc[i];
		*lib_ptr(ib, btx_ring[i].पंचांगd0, lp->type) = leptr;
		*lib_ptr(ib, btx_ring[i].पंचांगd1, lp->type) = (leptr >> 16) &
							   0xff;
		*lib_ptr(ib, btx_ring[i].length, lp->type) = 0xf000;
						/* The ones required by पंचांगd2 */
		*lib_ptr(ib, btx_ring[i].misc, lp->type) = 0;
		अगर (i < 3 && ZERO)
			prपूर्णांकk("%d: %8.8x(%p)\n",
			       i, leptr, lp->tx_buf_ptr_cpu[i]);
	पूर्ण

	/* Setup the Rx ring entries */
	अगर (ZERO)
		prपूर्णांकk("RX rings:\n");
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		leptr = lp->rx_buf_ptr_lnc[i];
		*lib_ptr(ib, brx_ring[i].rmd0, lp->type) = leptr;
		*lib_ptr(ib, brx_ring[i].rmd1, lp->type) = ((leptr >> 16) &
							    0xff) |
							   LE_R1_OWN;
		*lib_ptr(ib, brx_ring[i].length, lp->type) = -RX_BUFF_SIZE |
							     0xf000;
		*lib_ptr(ib, brx_ring[i].mblength, lp->type) = 0;
		अगर (i < 3 && ZERO)
			prपूर्णांकk("%d: %8.8x(%p)\n",
			       i, leptr, lp->rx_buf_ptr_cpu[i]);
	पूर्ण
	iob();
पूर्ण

अटल पूर्णांक init_restart_lance(काष्ठा lance_निजी *lp)
अणु
	अस्थिर काष्ठा lance_regs *ll = lp->ll;
	पूर्णांक i;

	ग_लिखोreg(&ll->rap, LE_CSR0);
	ग_लिखोreg(&ll->rdp, LE_C0_INIT);

	/* Wait क्रम the lance to complete initialization */
	क्रम (i = 0; (i < 100) && !(ll->rdp & LE_C0_IDON); i++) अणु
		udelay(10);
	पूर्ण
	अगर ((i == 100) || (ll->rdp & LE_C0_ERR)) अणु
		prपूर्णांकk("LANCE unopened after %d ticks, csr0=%4.4x.\n",
		       i, ll->rdp);
		वापस -1;
	पूर्ण
	अगर ((ll->rdp & LE_C0_ERR)) अणु
		prपूर्णांकk("LANCE unopened after %d ticks, csr0=%4.4x.\n",
		       i, ll->rdp);
		वापस -1;
	पूर्ण
	ग_लिखोreg(&ll->rdp, LE_C0_IDON);
	ग_लिखोreg(&ll->rdp, LE_C0_STRT);
	ग_लिखोreg(&ll->rdp, LE_C0_INEA);

	वापस 0;
पूर्ण

अटल पूर्णांक lance_rx(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	अस्थिर u16 *ib = (अस्थिर u16 *)dev->mem_start;
	अस्थिर u16 *rd;
	अचिन्हित लघु bits;
	पूर्णांक entry, len;
	काष्ठा sk_buff *skb;

#अगर_घोषित TEST_HITS
	अणु
		पूर्णांक i;

		prपूर्णांकk("[");
		क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
			अगर (i == lp->rx_new)
				prपूर्णांकk("%s", *lib_ptr(ib, brx_ring[i].rmd1,
						      lp->type) &
					     LE_R1_OWN ? "_" : "X");
			अन्यथा
				prपूर्णांकk("%s", *lib_ptr(ib, brx_ring[i].rmd1,
						      lp->type) &
					     LE_R1_OWN ? "." : "1");
		पूर्ण
		prपूर्णांकk("]");
	पूर्ण
#पूर्ण_अगर

	क्रम (rd = lib_ptr(ib, brx_ring[lp->rx_new], lp->type);
	     !((bits = *rds_ptr(rd, rmd1, lp->type)) & LE_R1_OWN);
	     rd = lib_ptr(ib, brx_ring[lp->rx_new], lp->type)) अणु
		entry = lp->rx_new;

		/* We got an incomplete frame? */
		अगर ((bits & LE_R1_POK) != LE_R1_POK) अणु
			dev->stats.rx_over_errors++;
			dev->stats.rx_errors++;
		पूर्ण अन्यथा अगर (bits & LE_R1_ERR) अणु
			/* Count only the end frame as a rx error,
			 * not the beginning
			 */
			अगर (bits & LE_R1_BUF)
				dev->stats.rx_fअगरo_errors++;
			अगर (bits & LE_R1_CRC)
				dev->stats.rx_crc_errors++;
			अगर (bits & LE_R1_OFL)
				dev->stats.rx_over_errors++;
			अगर (bits & LE_R1_FRA)
				dev->stats.rx_frame_errors++;
			अगर (bits & LE_R1_EOP)
				dev->stats.rx_errors++;
		पूर्ण अन्यथा अणु
			len = (*rds_ptr(rd, mblength, lp->type) & 0xfff) - 4;
			skb = netdev_alloc_skb(dev, len + 2);

			अगर (!skb) अणु
				dev->stats.rx_dropped++;
				*rds_ptr(rd, mblength, lp->type) = 0;
				*rds_ptr(rd, rmd1, lp->type) =
					((lp->rx_buf_ptr_lnc[entry] >> 16) &
					 0xff) | LE_R1_OWN;
				lp->rx_new = (entry + 1) & RX_RING_MOD_MASK;
				वापस 0;
			पूर्ण
			dev->stats.rx_bytes += len;

			skb_reserve(skb, 2);	/* 16 byte align */
			skb_put(skb, len);	/* make room */

			cp_from_buf(lp->type, skb->data,
				    lp->rx_buf_ptr_cpu[entry], len);

			skb->protocol = eth_type_trans(skb, dev);
			netअगर_rx(skb);
			dev->stats.rx_packets++;
		पूर्ण

		/* Return the packet to the pool */
		*rds_ptr(rd, mblength, lp->type) = 0;
		*rds_ptr(rd, length, lp->type) = -RX_BUFF_SIZE | 0xf000;
		*rds_ptr(rd, rmd1, lp->type) =
			((lp->rx_buf_ptr_lnc[entry] >> 16) & 0xff) | LE_R1_OWN;
		lp->rx_new = (entry + 1) & RX_RING_MOD_MASK;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम lance_tx(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	अस्थिर u16 *ib = (अस्थिर u16 *)dev->mem_start;
	अस्थिर काष्ठा lance_regs *ll = lp->ll;
	अस्थिर u16 *td;
	पूर्णांक i, j;
	पूर्णांक status;

	j = lp->tx_old;

	spin_lock(&lp->lock);

	क्रम (i = j; i != lp->tx_new; i = j) अणु
		td = lib_ptr(ib, btx_ring[i], lp->type);
		/* If we hit a packet not owned by us, stop */
		अगर (*tds_ptr(td, पंचांगd1, lp->type) & LE_T1_OWN)
			अवरोध;

		अगर (*tds_ptr(td, पंचांगd1, lp->type) & LE_T1_ERR) अणु
			status = *tds_ptr(td, misc, lp->type);

			dev->stats.tx_errors++;
			अगर (status & LE_T3_RTY)
				dev->stats.tx_पातed_errors++;
			अगर (status & LE_T3_LCOL)
				dev->stats.tx_winकरोw_errors++;

			अगर (status & LE_T3_CLOS) अणु
				dev->stats.tx_carrier_errors++;
				prपूर्णांकk("%s: Carrier Lost\n", dev->name);
				/* Stop the lance */
				ग_लिखोreg(&ll->rap, LE_CSR0);
				ग_लिखोreg(&ll->rdp, LE_C0_STOP);
				lance_init_ring(dev);
				load_csrs(lp);
				init_restart_lance(lp);
				जाओ out;
			पूर्ण
			/* Buffer errors and underflows turn off the
			 * transmitter, restart the adapter.
			 */
			अगर (status & (LE_T3_BUF | LE_T3_UFL)) अणु
				dev->stats.tx_fअगरo_errors++;

				prपूर्णांकk("%s: Tx: ERR_BUF|ERR_UFL, restarting\n",
				       dev->name);
				/* Stop the lance */
				ग_लिखोreg(&ll->rap, LE_CSR0);
				ग_लिखोreg(&ll->rdp, LE_C0_STOP);
				lance_init_ring(dev);
				load_csrs(lp);
				init_restart_lance(lp);
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अगर ((*tds_ptr(td, पंचांगd1, lp->type) & LE_T1_POK) ==
			   LE_T1_POK) अणु
			/*
			 * So we करोn't count the packet more than once.
			 */
			*tds_ptr(td, पंचांगd1, lp->type) &= ~(LE_T1_POK);

			/* One collision beक्रमe packet was sent. */
			अगर (*tds_ptr(td, पंचांगd1, lp->type) & LE_T1_EONE)
				dev->stats.collisions++;

			/* More than one collision, be optimistic. */
			अगर (*tds_ptr(td, पंचांगd1, lp->type) & LE_T1_EMORE)
				dev->stats.collisions += 2;

			dev->stats.tx_packets++;
		पूर्ण
		j = (j + 1) & TX_RING_MOD_MASK;
	पूर्ण
	lp->tx_old = j;
out:
	अगर (netअगर_queue_stopped(dev) &&
	    TX_BUFFS_AVAIL > 0)
		netअगर_wake_queue(dev);

	spin_unlock(&lp->lock);
पूर्ण

अटल irqवापस_t lance_dma_merr_पूर्णांक(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;

	prपूर्णांकk(KERN_ERR "%s: DMA error\n", dev->name);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t lance_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	अस्थिर काष्ठा lance_regs *ll = lp->ll;
	पूर्णांक csr0;

	ग_लिखोreg(&ll->rap, LE_CSR0);
	csr0 = ll->rdp;

	/* Acknowledge all the पूर्णांकerrupt sources ASAP */
	ग_लिखोreg(&ll->rdp, csr0 & (LE_C0_INTR | LE_C0_TINT | LE_C0_RINT));

	अगर ((csr0 & LE_C0_ERR)) अणु
		/* Clear the error condition */
		ग_लिखोreg(&ll->rdp, LE_C0_BABL | LE_C0_ERR | LE_C0_MISS |
			 LE_C0_CERR | LE_C0_MERR);
	पूर्ण
	अगर (csr0 & LE_C0_RINT)
		lance_rx(dev);

	अगर (csr0 & LE_C0_TINT)
		lance_tx(dev);

	अगर (csr0 & LE_C0_BABL)
		dev->stats.tx_errors++;

	अगर (csr0 & LE_C0_MISS)
		dev->stats.rx_errors++;

	अगर (csr0 & LE_C0_MERR) अणु
		prपूर्णांकk("%s: Memory error, status %04x\n", dev->name, csr0);

		ग_लिखोreg(&ll->rdp, LE_C0_STOP);

		lance_init_ring(dev);
		load_csrs(lp);
		init_restart_lance(lp);
		netअगर_wake_queue(dev);
	पूर्ण

	ग_लिखोreg(&ll->rdp, LE_C0_INEA);
	ग_लिखोreg(&ll->rdp, LE_C0_INEA);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक lance_खोलो(काष्ठा net_device *dev)
अणु
	अस्थिर u16 *ib = (अस्थिर u16 *)dev->mem_start;
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	अस्थिर काष्ठा lance_regs *ll = lp->ll;
	पूर्णांक status = 0;

	/* Stop the Lance */
	ग_लिखोreg(&ll->rap, LE_CSR0);
	ग_लिखोreg(&ll->rdp, LE_C0_STOP);

	/* Set mode and clear multicast filter only at device खोलो,
	 * so that lance_init_ring() called at any error will not
	 * क्रमget multicast filters.
	 *
	 * BTW it is common bug in all lance drivers! --ANK
	 */
	*lib_ptr(ib, mode, lp->type) = 0;
	*lib_ptr(ib, filter[0], lp->type) = 0;
	*lib_ptr(ib, filter[1], lp->type) = 0;
	*lib_ptr(ib, filter[2], lp->type) = 0;
	*lib_ptr(ib, filter[3], lp->type) = 0;

	lance_init_ring(dev);
	load_csrs(lp);

	netअगर_start_queue(dev);

	/* Associate IRQ with lance_पूर्णांकerrupt */
	अगर (request_irq(dev->irq, lance_पूर्णांकerrupt, 0, "lance", dev)) अणु
		prपूर्णांकk("%s: Can't get IRQ %d\n", dev->name, dev->irq);
		वापस -EAGAIN;
	पूर्ण
	अगर (lp->dma_irq >= 0) अणु
		अचिन्हित दीर्घ flags;

		अगर (request_irq(lp->dma_irq, lance_dma_merr_पूर्णांक, IRQF_ONESHOT,
				"lance error", dev)) अणु
			मुक्त_irq(dev->irq, dev);
			prपूर्णांकk("%s: Can't get DMA IRQ %d\n", dev->name,
				lp->dma_irq);
			वापस -EAGAIN;
		पूर्ण

		spin_lock_irqsave(&ioasic_ssr_lock, flags);

		fast_mb();
		/* Enable I/O ASIC LANCE DMA.  */
		ioasic_ग_लिखो(IO_REG_SSR,
			     ioasic_पढ़ो(IO_REG_SSR) | IO_SSR_LANCE_DMA_EN);

		fast_mb();
		spin_unlock_irqrestore(&ioasic_ssr_lock, flags);
	पूर्ण

	status = init_restart_lance(lp);
	वापस status;
पूर्ण

अटल पूर्णांक lance_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	अस्थिर काष्ठा lance_regs *ll = lp->ll;

	netअगर_stop_queue(dev);
	del_समयr_sync(&lp->multicast_समयr);

	/* Stop the card */
	ग_लिखोreg(&ll->rap, LE_CSR0);
	ग_लिखोreg(&ll->rdp, LE_C0_STOP);

	अगर (lp->dma_irq >= 0) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&ioasic_ssr_lock, flags);

		fast_mb();
		/* Disable I/O ASIC LANCE DMA.  */
		ioasic_ग_लिखो(IO_REG_SSR,
			     ioasic_पढ़ो(IO_REG_SSR) & ~IO_SSR_LANCE_DMA_EN);

		fast_iob();
		spin_unlock_irqrestore(&ioasic_ssr_lock, flags);

		मुक्त_irq(lp->dma_irq, dev);
	पूर्ण
	मुक्त_irq(dev->irq, dev);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक lance_reset(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	अस्थिर काष्ठा lance_regs *ll = lp->ll;
	पूर्णांक status;

	/* Stop the lance */
	ग_लिखोreg(&ll->rap, LE_CSR0);
	ग_लिखोreg(&ll->rdp, LE_C0_STOP);

	lance_init_ring(dev);
	load_csrs(lp);
	netअगर_trans_update(dev); /* prevent tx समयout */
	status = init_restart_lance(lp);
	वापस status;
पूर्ण

अटल व्योम lance_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	अस्थिर काष्ठा lance_regs *ll = lp->ll;

	prपूर्णांकk(KERN_ERR "%s: transmit timed out, status %04x, reset\n",
		dev->name, ll->rdp);
	lance_reset(dev);
	netअगर_wake_queue(dev);
पूर्ण

अटल netdev_tx_t lance_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	अस्थिर काष्ठा lance_regs *ll = lp->ll;
	अस्थिर u16 *ib = (अस्थिर u16 *)dev->mem_start;
	अचिन्हित दीर्घ flags;
	पूर्णांक entry, len;

	len = skb->len;

	अगर (len < ETH_ZLEN) अणु
		अगर (skb_padto(skb, ETH_ZLEN))
			वापस NETDEV_TX_OK;
		len = ETH_ZLEN;
	पूर्ण

	dev->stats.tx_bytes += len;

	spin_lock_irqsave(&lp->lock, flags);

	entry = lp->tx_new;
	*lib_ptr(ib, btx_ring[entry].length, lp->type) = (-len);
	*lib_ptr(ib, btx_ring[entry].misc, lp->type) = 0;

	cp_to_buf(lp->type, lp->tx_buf_ptr_cpu[entry], skb->data, len);

	/* Now, give the packet to the lance */
	*lib_ptr(ib, btx_ring[entry].पंचांगd1, lp->type) =
		((lp->tx_buf_ptr_lnc[entry] >> 16) & 0xff) |
		(LE_T1_POK | LE_T1_OWN);
	lp->tx_new = (entry + 1) & TX_RING_MOD_MASK;

	अगर (TX_BUFFS_AVAIL <= 0)
		netअगर_stop_queue(dev);

	/* Kick the lance: transmit now */
	ग_लिखोreg(&ll->rdp, LE_C0_INEA | LE_C0_TDMD);

	spin_unlock_irqrestore(&lp->lock, flags);

	dev_kमुक्त_skb(skb);

 	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम lance_load_multicast(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	अस्थिर u16 *ib = (अस्थिर u16 *)dev->mem_start;
	काष्ठा netdev_hw_addr *ha;
	u32 crc;

	/* set all multicast bits */
	अगर (dev->flags & IFF_ALLMULTI) अणु
		*lib_ptr(ib, filter[0], lp->type) = 0xffff;
		*lib_ptr(ib, filter[1], lp->type) = 0xffff;
		*lib_ptr(ib, filter[2], lp->type) = 0xffff;
		*lib_ptr(ib, filter[3], lp->type) = 0xffff;
		वापस;
	पूर्ण
	/* clear the multicast filter */
	*lib_ptr(ib, filter[0], lp->type) = 0;
	*lib_ptr(ib, filter[1], lp->type) = 0;
	*lib_ptr(ib, filter[2], lp->type) = 0;
	*lib_ptr(ib, filter[3], lp->type) = 0;

	/* Add addresses */
	netdev_क्रम_each_mc_addr(ha, dev) अणु
		crc = ether_crc_le(ETH_ALEN, ha->addr);
		crc = crc >> 26;
		*lib_ptr(ib, filter[crc >> 4], lp->type) |= 1 << (crc & 0xf);
	पूर्ण
पूर्ण

अटल व्योम lance_set_multicast(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	अस्थिर u16 *ib = (अस्थिर u16 *)dev->mem_start;
	अस्थिर काष्ठा lance_regs *ll = lp->ll;

	अगर (!netअगर_running(dev))
		वापस;

	अगर (lp->tx_old != lp->tx_new) अणु
		mod_समयr(&lp->multicast_समयr, jअगरfies + 4 * HZ/100);
		netअगर_wake_queue(dev);
		वापस;
	पूर्ण

	netअगर_stop_queue(dev);

	ग_लिखोreg(&ll->rap, LE_CSR0);
	ग_लिखोreg(&ll->rdp, LE_C0_STOP);

	lance_init_ring(dev);

	अगर (dev->flags & IFF_PROMISC) अणु
		*lib_ptr(ib, mode, lp->type) |= LE_MO_PROM;
	पूर्ण अन्यथा अणु
		*lib_ptr(ib, mode, lp->type) &= ~LE_MO_PROM;
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

अटल स्थिर काष्ठा net_device_ops lance_netdev_ops = अणु
	.nकरो_खोलो		= lance_खोलो,
	.nकरो_stop		= lance_बंद,
	.nकरो_start_xmit		= lance_start_xmit,
	.nकरो_tx_समयout		= lance_tx_समयout,
	.nकरो_set_rx_mode	= lance_set_multicast,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= eth_mac_addr,
पूर्ण;

अटल पूर्णांक dec_lance_probe(काष्ठा device *bdev, स्थिर पूर्णांक type)
अणु
	अटल अचिन्हित version_prपूर्णांकed;
	अटल स्थिर अक्षर fmt[] = "declance%d";
	अक्षर name[10];
	काष्ठा net_device *dev;
	काष्ठा lance_निजी *lp;
	अस्थिर काष्ठा lance_regs *ll;
	resource_माप_प्रकार start = 0, len = 0;
	पूर्णांक i, ret;
	अचिन्हित दीर्घ esar_base;
	अचिन्हित अक्षर *esar;
	स्थिर अक्षर *desc;

	अगर (dec_lance_debug && version_prपूर्णांकed++ == 0)
		prपूर्णांकk(version);

	अगर (bdev)
		snम_लिखो(name, माप(name), "%s", dev_name(bdev));
	अन्यथा अणु
		i = 0;
		dev = root_lance_dev;
		जबतक (dev) अणु
			i++;
			lp = netdev_priv(dev);
			dev = lp->next;
		पूर्ण
		snम_लिखो(name, माप(name), fmt, i);
	पूर्ण

	dev = alloc_etherdev(माप(काष्ठा lance_निजी));
	अगर (!dev) अणु
		ret = -ENOMEM;
		जाओ err_out;
	पूर्ण

	/*
	 * alloc_etherdev ensures the data काष्ठाures used by the LANCE
	 * are aligned.
	 */
	lp = netdev_priv(dev);
	spin_lock_init(&lp->lock);

	lp->type = type;
	चयन (type) अणु
	हाल ASIC_LANCE:
		dev->base_addr = CKSEG1ADDR(dec_kn_slot_base + IOASIC_LANCE);

		/* buffer space क्रम the on-board LANCE shared memory */
		/*
		 * FIXME: ugly hack!
		 */
		dev->mem_start = CKSEG1ADDR(0x00020000);
		dev->mem_end = dev->mem_start + 0x00020000;
		dev->irq = dec_पूर्णांकerrupt[DEC_IRQ_LANCE];
		esar_base = CKSEG1ADDR(dec_kn_slot_base + IOASIC_ESAR);

		/* Workaround crash with booting KN04 2.1k from Disk */
		स_रखो((व्योम *)dev->mem_start, 0,
		       dev->mem_end - dev->mem_start);

		/*
		 * setup the poपूर्णांकer arrays, this sucks [पंचांग] :-(
		 */
		क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
			lp->rx_buf_ptr_cpu[i] =
				(अक्षर *)(dev->mem_start + 2 * BUF_OFFSET_CPU +
					 2 * i * RX_BUFF_SIZE);
			lp->rx_buf_ptr_lnc[i] =
				(BUF_OFFSET_LNC + i * RX_BUFF_SIZE);
		पूर्ण
		क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
			lp->tx_buf_ptr_cpu[i] =
				(अक्षर *)(dev->mem_start + 2 * BUF_OFFSET_CPU +
					 2 * RX_RING_SIZE * RX_BUFF_SIZE +
					 2 * i * TX_BUFF_SIZE);
			lp->tx_buf_ptr_lnc[i] =
				(BUF_OFFSET_LNC +
				 RX_RING_SIZE * RX_BUFF_SIZE +
				 i * TX_BUFF_SIZE);
		पूर्ण

		/* Setup I/O ASIC LANCE DMA.  */
		lp->dma_irq = dec_पूर्णांकerrupt[DEC_IRQ_LANCE_MERR];
		ioasic_ग_लिखो(IO_REG_LANCE_DMA_P,
			     CPHYSADDR(dev->mem_start) << 3);

		अवरोध;
#अगर_घोषित CONFIG_TC
	हाल PMAD_LANCE:
		dev_set_drvdata(bdev, dev);

		start = to_tc_dev(bdev)->resource.start;
		len = to_tc_dev(bdev)->resource.end - start + 1;
		अगर (!request_mem_region(start, len, dev_name(bdev))) अणु
			prपूर्णांकk(KERN_ERR
			       "%s: Unable to reserve MMIO resource\n",
			       dev_name(bdev));
			ret = -EBUSY;
			जाओ err_out_dev;
		पूर्ण

		dev->mem_start = CKSEG1ADDR(start);
		dev->mem_end = dev->mem_start + 0x100000;
		dev->base_addr = dev->mem_start + 0x100000;
		dev->irq = to_tc_dev(bdev)->पूर्णांकerrupt;
		esar_base = dev->mem_start + 0x1c0002;
		lp->dma_irq = -1;

		क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
			lp->rx_buf_ptr_cpu[i] =
				(अक्षर *)(dev->mem_start + BUF_OFFSET_CPU +
					 i * RX_BUFF_SIZE);
			lp->rx_buf_ptr_lnc[i] =
				(BUF_OFFSET_LNC + i * RX_BUFF_SIZE);
		पूर्ण
		क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
			lp->tx_buf_ptr_cpu[i] =
				(अक्षर *)(dev->mem_start + BUF_OFFSET_CPU +
					 RX_RING_SIZE * RX_BUFF_SIZE +
					 i * TX_BUFF_SIZE);
			lp->tx_buf_ptr_lnc[i] =
				(BUF_OFFSET_LNC +
				 RX_RING_SIZE * RX_BUFF_SIZE +
				 i * TX_BUFF_SIZE);
		पूर्ण

		अवरोध;
#पूर्ण_अगर
	हाल PMAX_LANCE:
		dev->irq = dec_पूर्णांकerrupt[DEC_IRQ_LANCE];
		dev->base_addr = CKSEG1ADDR(KN01_SLOT_BASE + KN01_LANCE);
		dev->mem_start = CKSEG1ADDR(KN01_SLOT_BASE + KN01_LANCE_MEM);
		dev->mem_end = dev->mem_start + KN01_SLOT_SIZE;
		esar_base = CKSEG1ADDR(KN01_SLOT_BASE + KN01_ESAR + 1);
		lp->dma_irq = -1;

		/*
		 * setup the poपूर्णांकer arrays, this sucks [पंचांग] :-(
		 */
		क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
			lp->rx_buf_ptr_cpu[i] =
				(अक्षर *)(dev->mem_start + 2 * BUF_OFFSET_CPU +
					 2 * i * RX_BUFF_SIZE);
			lp->rx_buf_ptr_lnc[i] =
				(BUF_OFFSET_LNC + i * RX_BUFF_SIZE);
		पूर्ण
		क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
			lp->tx_buf_ptr_cpu[i] =
				(अक्षर *)(dev->mem_start + 2 * BUF_OFFSET_CPU +
					 2 * RX_RING_SIZE * RX_BUFF_SIZE +
					 2 * i * TX_BUFF_SIZE);
			lp->tx_buf_ptr_lnc[i] =
				(BUF_OFFSET_LNC +
				 RX_RING_SIZE * RX_BUFF_SIZE +
				 i * TX_BUFF_SIZE);
		पूर्ण

		अवरोध;

	शेष:
		prपूर्णांकk(KERN_ERR "%s: declance_init called with unknown type\n",
			name);
		ret = -ENODEV;
		जाओ err_out_dev;
	पूर्ण

	ll = (काष्ठा lance_regs *) dev->base_addr;
	esar = (अचिन्हित अक्षर *) esar_base;

	/* prom checks */
	/* First, check क्रम test pattern */
	अगर (esar[0x60] != 0xff && esar[0x64] != 0x00 &&
	    esar[0x68] != 0x55 && esar[0x6c] != 0xaa) अणु
		prपूर्णांकk(KERN_ERR
			"%s: Ethernet station address prom not found!\n",
			name);
		ret = -ENODEV;
		जाओ err_out_resource;
	पूर्ण
	/* Check the prom contents */
	क्रम (i = 0; i < 8; i++) अणु
		अगर (esar[i * 4] != esar[0x3c - i * 4] &&
		    esar[i * 4] != esar[0x40 + i * 4] &&
		    esar[0x3c - i * 4] != esar[0x40 + i * 4]) अणु
			prपूर्णांकk(KERN_ERR "%s: Something is wrong with the "
				"ethernet station address prom!\n", name);
			ret = -ENODEV;
			जाओ err_out_resource;
		पूर्ण
	पूर्ण

	/* Copy the ethernet address to the device काष्ठाure, later to the
	 * lance initialization block so the lance माला_लो it every समय it's
	 * (re)initialized.
	 */
	चयन (type) अणु
	हाल ASIC_LANCE:
		desc = "IOASIC onboard LANCE";
		अवरोध;
	हाल PMAD_LANCE:
		desc = "PMAD-AA";
		अवरोध;
	हाल PMAX_LANCE:
		desc = "PMAX onboard LANCE";
		अवरोध;
	पूर्ण
	क्रम (i = 0; i < 6; i++)
		dev->dev_addr[i] = esar[i * 4];

	prपूर्णांकk("%s: %s, addr = %pM, irq = %d\n",
	       name, desc, dev->dev_addr, dev->irq);

	dev->netdev_ops = &lance_netdev_ops;
	dev->watchकरोg_समयo = 5*HZ;

	/* lp->ll is the location of the रेजिस्टरs क्रम lance card */
	lp->ll = ll;

	/* busmaster_regval (CSR3) should be zero according to the PMAD-AA
	 * specअगरication.
	 */
	lp->busmaster_regval = 0;

	dev->dma = 0;

	/* We cannot sleep अगर the chip is busy during a
	 * multicast list update event, because such events
	 * can occur from पूर्णांकerrupts (ex. IPv6).  So we
	 * use a समयr to try again later when necessary. -DaveM
	 */
	lp->dev = dev;
	समयr_setup(&lp->multicast_समयr, lance_set_multicast_retry, 0);


	ret = रेजिस्टर_netdev(dev);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR
			"%s: Unable to register netdev, aborting.\n", name);
		जाओ err_out_resource;
	पूर्ण

	अगर (!bdev) अणु
		lp->next = root_lance_dev;
		root_lance_dev = dev;
	पूर्ण

	prपूर्णांकk("%s: registered as %s.\n", name, dev->name);
	वापस 0;

err_out_resource:
	अगर (bdev)
		release_mem_region(start, len);

err_out_dev:
	मुक्त_netdev(dev);

err_out:
	वापस ret;
पूर्ण

/* Find all the lance cards on the प्रणाली and initialize them */
अटल पूर्णांक __init dec_lance_platक्रमm_probe(व्योम)
अणु
	पूर्णांक count = 0;

	अगर (dec_पूर्णांकerrupt[DEC_IRQ_LANCE] >= 0) अणु
		अगर (dec_पूर्णांकerrupt[DEC_IRQ_LANCE_MERR] >= 0) अणु
			अगर (dec_lance_probe(शून्य, ASIC_LANCE) >= 0)
				count++;
		पूर्ण अन्यथा अगर (!TURBOCHANNEL) अणु
			अगर (dec_lance_probe(शून्य, PMAX_LANCE) >= 0)
				count++;
		पूर्ण
	पूर्ण

	वापस (count > 0) ? 0 : -ENODEV;
पूर्ण

अटल व्योम __निकास dec_lance_platक्रमm_हटाओ(व्योम)
अणु
	जबतक (root_lance_dev) अणु
		काष्ठा net_device *dev = root_lance_dev;
		काष्ठा lance_निजी *lp = netdev_priv(dev);

		unरेजिस्टर_netdev(dev);
		root_lance_dev = lp->next;
		मुक्त_netdev(dev);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_TC
अटल पूर्णांक dec_lance_tc_probe(काष्ठा device *dev);
अटल पूर्णांक dec_lance_tc_हटाओ(काष्ठा device *dev);

अटल स्थिर काष्ठा tc_device_id dec_lance_tc_table[] = अणु
	अणु "DEC     ", "PMAD-AA " पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(tc, dec_lance_tc_table);

अटल काष्ठा tc_driver dec_lance_tc_driver = अणु
	.id_table	= dec_lance_tc_table,
	.driver		= अणु
		.name	= "declance",
		.bus	= &tc_bus_type,
		.probe	= dec_lance_tc_probe,
		.हटाओ	= dec_lance_tc_हटाओ,
	पूर्ण,
पूर्ण;

अटल पूर्णांक dec_lance_tc_probe(काष्ठा device *dev)
अणु
        पूर्णांक status = dec_lance_probe(dev, PMAD_LANCE);
        अगर (!status)
                get_device(dev);
        वापस status;
पूर्ण

अटल व्योम dec_lance_हटाओ(काष्ठा device *bdev)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(bdev);
	resource_माप_प्रकार start, len;

	unरेजिस्टर_netdev(dev);
	start = to_tc_dev(bdev)->resource.start;
	len = to_tc_dev(bdev)->resource.end - start + 1;
	release_mem_region(start, len);
	मुक्त_netdev(dev);
पूर्ण

अटल पूर्णांक dec_lance_tc_हटाओ(काष्ठा device *dev)
अणु
        put_device(dev);
        dec_lance_हटाओ(dev);
        वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init dec_lance_init(व्योम)
अणु
	पूर्णांक status;

	status = tc_रेजिस्टर_driver(&dec_lance_tc_driver);
	अगर (!status)
		dec_lance_platक्रमm_probe();
	वापस status;
पूर्ण

अटल व्योम __निकास dec_lance_निकास(व्योम)
अणु
	dec_lance_platक्रमm_हटाओ();
	tc_unरेजिस्टर_driver(&dec_lance_tc_driver);
पूर्ण


module_init(dec_lance_init);
module_निकास(dec_lance_निकास);
