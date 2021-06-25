<शैली गुरु>
/*------------------------------------------------------------------------
 . smc9194.c
 . This is a driver क्रम SMC's 9000 series of Ethernet cards.
 .
 . Copyright (C) 1996 by Erik Stahlman
 . This software may be used and distributed according to the terms
 . of the GNU General Public License, incorporated herein by reference.
 .
 . "Features" of the SMC chip:
 .   4608 byte packet memory. ( क्रम the 91C92.  Others have more )
 .   EEPROM क्रम configuration
 .   AUI/TP selection  ( mine has 10Base2/10BaseT select )
 .
 . Arguments:
 . 	io		 = क्रम the base address
 .	irq	 = क्रम the IRQ
 .	अगरport = 0 क्रम स्वतःdetect, 1 क्रम TP, 2 क्रम AUI ( or 10base2 )
 .
 . author:
 . 	Erik Stahlman				( erik@vt.edu )
 . contributors:
 .      Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 .
 . Hardware multicast code from Peter Cammaert ( pc@denkart.be )
 .
 . Sources:
 .    o   SMC databook
 .    o   skeleton.c by Donald Becker ( becker@scyld.com )
 .    o   ( a LOT of advice from Becker as well )
 .
 . History:
 .	12/07/95  Erik Stahlman  written, got receive/xmit handled
 . 	01/03/96  Erik Stahlman  worked out some bugs, actually usable!!! :-)
 .	01/06/96  Erik Stahlman	 cleaned up some, better testing, etc
 .	01/29/96  Erik Stahlman	 fixed स्वतःirq, added multicast
 . 	02/01/96  Erik Stahlman	 1. disabled all पूर्णांकerrupts in smc_reset
 .		   		 2. got rid of post-decrementing bug -- UGH.
 .	02/13/96  Erik Stahlman  Tried to fix स्वतःirq failure.  Added more
 .				 descriptive error messages.
 .	02/15/96  Erik Stahlman  Fixed typo that caused detection failure
 . 	02/23/96  Erik Stahlman	 Modअगरied it to fit पूर्णांकo kernel tree
 .				 Added support to change hardware address
 .				 Cleared stats on खोलोs
 .	02/26/96  Erik Stahlman	 Trial support क्रम Kernel 1.2.13
 .				 Kludge क्रम स्वतःmatic IRQ detection
 .	03/04/96  Erik Stahlman	 Fixed kernel 1.3.70 +
 .				 Fixed bug reported by Gardner Buchanan in
 .				   smc_enable, with outw instead of outb
 .	03/06/96  Erik Stahlman  Added hardware multicast from Peter Cammaert
 .	04/14/00  Heiko Pruessing (SMA Regelप्रणालीe)  Fixed bug in chip memory
 .				 allocation
 .      08/20/00  Arnalकरो Melo   fix kमुक्त(skb) in smc_hardware_send_packet
 .      12/15/00  Christian Jullien fix "Warning: kfree_skb on hard IRQ"
 .      11/08/01 Matt Domsch     Use common crc32 function
 ----------------------------------------------------------------------------*/

अटल स्थिर अक्षर version[] =
	"smc9194.c:v0.14 12/15/00 by Erik Stahlman (erik@vt.edu)";

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/in.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/crc32.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/पन.स>

#समावेश "smc9194.h"

#घोषणा DRV_NAME "smc9194"

/*------------------------------------------------------------------------
 .
 . Configuration options, क्रम the experienced user to change.
 .
 -------------------------------------------------------------------------*/

/*
 . Do you want to use 32 bit xfers?  This should work on all chips, as
 . the chipset is deचिन्हित to accommodate them.
*/
#अगर_घोषित __sh__
#अघोषित USE_32_BIT
#अन्यथा
#घोषणा USE_32_BIT 1
#पूर्ण_अगर

/*
 .the SMC9194 can be at any of the following port addresses.  To change,
 .क्रम a slightly dअगरferent card, you can add it to the array.  Keep in
 .mind that the array must end in zero.
*/

काष्ठा devlist अणु
	अचिन्हित पूर्णांक port;
	अचिन्हित पूर्णांक irq;
पूर्ण;

अटल काष्ठा devlist smc_devlist[] __initdata = अणु
	अणु.port = 0x200, .irq = 0पूर्ण,
	अणु.port = 0x220, .irq = 0पूर्ण,
	अणु.port = 0x240, .irq = 0पूर्ण,
	अणु.port = 0x260, .irq = 0पूर्ण,
	अणु.port = 0x280, .irq = 0पूर्ण,
	अणु.port = 0x2A0, .irq = 0पूर्ण,
	अणु.port = 0x2C0, .irq = 0पूर्ण,
	अणु.port = 0x2E0, .irq = 0पूर्ण,
	अणु.port = 0x300, .irq = 0पूर्ण,
	अणु.port = 0x320, .irq = 0पूर्ण,
	अणु.port = 0x340, .irq = 0पूर्ण,
	अणु.port = 0x360, .irq = 0पूर्ण,
	अणु.port = 0x380, .irq = 0पूर्ण,
	अणु.port = 0x3A0, .irq = 0पूर्ण,
	अणु.port = 0x3C0, .irq = 0पूर्ण,
	अणु.port = 0x3E0, .irq = 0पूर्ण,
	अणु.port = 0,     .irq = 0पूर्ण,
पूर्ण;
/*
 . Wait समय क्रम memory to be मुक्त.  This probably shouldn't be
 . tuned that much, as रुकोing क्रम this means nothing अन्यथा happens
 . in the प्रणाली
*/
#घोषणा MEMORY_WAIT_TIME 16

/*
 . DEBUGGING LEVELS
 .
 . 0 क्रम normal operation
 . 1 क्रम slightly more details
 . >2 क्रम various levels of increasingly useless inक्रमmation
 .    2 क्रम पूर्णांकerrupt tracking, status flags
 .    3 क्रम packet dumps, etc.
*/
#घोषणा SMC_DEBUG 0

#अगर (SMC_DEBUG > 2 )
#घोषणा PRINTK3(x) prपूर्णांकk x
#अन्यथा
#घोषणा PRINTK3(x)
#पूर्ण_अगर

#अगर SMC_DEBUG > 1
#घोषणा PRINTK2(x) prपूर्णांकk x
#अन्यथा
#घोषणा PRINTK2(x)
#पूर्ण_अगर

#अगर_घोषित SMC_DEBUG
#घोषणा PRINTK(x) prपूर्णांकk x
#अन्यथा
#घोषणा PRINTK(x)
#पूर्ण_अगर


/*------------------------------------------------------------------------
 .
 . The पूर्णांकernal workings of the driver.  If you are changing anything
 . here with the SMC stuff, you should have the datasheet and known
 . what you are करोing.
 .
 -------------------------------------------------------------------------*/
#घोषणा CARDNAME "SMC9194"


/* store this inक्रमmation क्रम the driver.. */
काष्ठा smc_local अणु
	/*
	   If I have to रुको until memory is available to send
	   a packet, I will store the skbuff here, until I get the
	   desired memory.  Then, I'll send it out and मुक्त it.
	*/
	काष्ठा sk_buff * saved_skb;

	/*
 	 . This keeps track of how many packets that I have
 	 . sent out.  When an TX_EMPTY पूर्णांकerrupt comes, I know
	 . that all of these have been sent.
	*/
	पूर्णांक	packets_रुकोing;
पूर्ण;


/*-----------------------------------------------------------------
 .
 .  The driver can be entered at any of the following entry poपूर्णांकs.
 .
 .------------------------------------------------------------------  */

/*
 . This is called by  रेजिस्टर_netdev().  It is responsible क्रम
 . checking the portlist क्रम the SMC9000 series chipset.  If it finds
 . one, then it will initialize the device, find the hardware inक्रमmation,
 . and sets up the appropriate device parameters.
 . NOTE: Interrupts are *OFF* when this procedure is called.
 .
 . NB:This shouldn't be अटल since it is referred to बाह्यally.
*/
काष्ठा net_device *smc_init(पूर्णांक unit);

/*
 . The kernel calls this function when someone wants to use the device,
 . typically 'ifconfig ethX up'.
*/
अटल पूर्णांक smc_खोलो(काष्ठा net_device *dev);

/*
 . Our watchकरोg समयd out. Called by the networking layer
*/
अटल व्योम smc_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);

/*
 . This is called by the kernel in response to 'ifconfig ethX down'.  It
 . is responsible क्रम cleaning up everything that the खोलो routine
 . करोes, and maybe putting the card पूर्णांकo a घातerकरोwn state.
*/
अटल पूर्णांक smc_बंद(काष्ठा net_device *dev);

/*
 . Finally, a call to set promiscuous mode ( क्रम TCPDUMP and related
 . programs ) and multicast modes.
*/
अटल व्योम smc_set_multicast_list(काष्ठा net_device *dev);


/*---------------------------------------------------------------
 .
 . Interrupt level calls..
 .
 ----------------------------------------------------------------*/

/*
 . Handles the actual पूर्णांकerrupt
*/
अटल irqवापस_t smc_पूर्णांकerrupt(पूर्णांक irq, व्योम *);
/*
 . This is a separate procedure to handle the receipt of a packet, to
 . leave the पूर्णांकerrupt code looking slightly cleaner
*/
अटल अंतरभूत व्योम smc_rcv( काष्ठा net_device *dev );
/*
 . This handles a TX पूर्णांकerrupt, which is only called when an error
 . relating to a packet is sent.
*/
अटल अंतरभूत व्योम smc_tx( काष्ठा net_device * dev );

/*
 ------------------------------------------------------------
 .
 . Internal routines
 .
 ------------------------------------------------------------
*/

/*
 . Test अगर a given location contains a chip, trying to cause as
 . little damage as possible अगर it's not a SMC chip.
*/
अटल पूर्णांक smc_probe(काष्ठा net_device *dev, पूर्णांक ioaddr);

/*
 . A rather simple routine to prपूर्णांक out a packet क्रम debugging purposes.
*/
#अगर SMC_DEBUG > 2
अटल व्योम prपूर्णांक_packet( byte *, पूर्णांक );
#पूर्ण_अगर

#घोषणा tx_करोne(dev) 1

/* this is called to actually send the packet to the chip */
अटल व्योम smc_hardware_send_packet( काष्ठा net_device * dev );

/* Since I am not sure अगर I will have enough room in the chip's ram
 . to store the packet, I call this routine, which either sends it
 . now, or generates an पूर्णांकerrupt when the card is पढ़ोy क्रम the
 . packet */
अटल netdev_tx_t  smc_रुको_to_send_packet( काष्ठा sk_buff * skb,
					     काष्ठा net_device *dev );

/* this करोes a soft reset on the device */
अटल व्योम smc_reset( पूर्णांक ioaddr );

/* Enable Interrupts, Receive, and Transmit */
अटल व्योम smc_enable( पूर्णांक ioaddr );

/* this माला_दो the device in an inactive state */
अटल व्योम smc_shutकरोwn( पूर्णांक ioaddr );

/* This routine will find the IRQ of the driver अगर one is not
 . specअगरied in the input to the device.  */
अटल पूर्णांक smc_findirq( पूर्णांक ioaddr );

/*
 . Function: smc_reset( पूर्णांक ioaddr )
 . Purpose:
 .  	This sets the SMC91xx chip to its normal state, hopefully from whatever
 . 	mess that any other DOS driver has put it in.
 .
 . Maybe I should reset more रेजिस्टरs to शेषs in here?  SOFTRESET  should
 . करो that क्रम me.
 .
 . Method:
 .	1.  send a SOFT RESET
 .	2.  रुको क्रम it to finish
 .	3.  enable स्वतःrelease mode
 .	4.  reset the memory management unit
 .	5.  clear all पूर्णांकerrupts
 .
*/
अटल व्योम smc_reset( पूर्णांक ioaddr )
अणु
	/* This resets the रेजिस्टरs mostly to शेषs, but करोesn't
	   affect EEPROM.  That seems unnecessary */
	SMC_SELECT_BANK( 0 );
	outw( RCR_SOFTRESET, ioaddr + RCR );

	/* this should छोड़ो enough क्रम the chip to be happy */
	SMC_DELAY( );

	/* Set the transmit and receive configuration रेजिस्टरs to
	   शेष values */
	outw( RCR_CLEAR, ioaddr + RCR );
	outw( TCR_CLEAR, ioaddr + TCR );

	/* set the control रेजिस्टर to स्वतःmatically
	   release successfully transmitted packets, to make the best
	   use out of our limited memory */
	SMC_SELECT_BANK( 1 );
	outw( inw( ioaddr + CONTROL ) | CTL_AUTO_RELEASE , ioaddr + CONTROL );

	/* Reset the MMU */
	SMC_SELECT_BANK( 2 );
	outw( MC_RESET, ioaddr + MMU_CMD );

	/* Note:  It करोesn't seem that रुकोing क्रम the MMU busy is needed here,
	   but this is a place where future chipsets _COULD_ अवरोध.  Be wary
 	   of issuing another MMU command right after this */

	outb( 0, ioaddr + INT_MASK );
पूर्ण

/*
 . Function: smc_enable
 . Purpose: let the chip talk to the outside work
 . Method:
 .	1.  Enable the transmitter
 .	2.  Enable the receiver
 .	3.  Enable पूर्णांकerrupts
*/
अटल व्योम smc_enable( पूर्णांक ioaddr )
अणु
	SMC_SELECT_BANK( 0 );
	/* see the header file क्रम options in TCR/RCR NORMAL*/
	outw( TCR_NORMAL, ioaddr + TCR );
	outw( RCR_NORMAL, ioaddr + RCR );

	/* now, enable पूर्णांकerrupts */
	SMC_SELECT_BANK( 2 );
	outb( SMC_INTERRUPT_MASK, ioaddr + INT_MASK );
पूर्ण

/*
 . Function: smc_shutकरोwn
 . Purpose:  बंदs करोwn the SMC91xxx chip.
 . Method:
 .	1. zero the पूर्णांकerrupt mask
 .	2. clear the enable receive flag
 .	3. clear the enable xmit flags
 .
 . TODO:
 .   (1) maybe utilize घातer करोwn mode.
 .	Why not yet?  Because जबतक the chip will go पूर्णांकo घातer करोwn mode,
 .	the manual says that it will wake up in response to any I/O requests
 .	in the रेजिस्टर space.   Empirical results करो not show this working.
*/
अटल व्योम smc_shutकरोwn( पूर्णांक ioaddr )
अणु
	/* no more पूर्णांकerrupts क्रम me */
	SMC_SELECT_BANK( 2 );
	outb( 0, ioaddr + INT_MASK );

	/* and tell the card to stay away from that nasty outside world */
	SMC_SELECT_BANK( 0 );
	outb( RCR_CLEAR, ioaddr + RCR );
	outb( TCR_CLEAR, ioaddr + TCR );
#अगर 0
	/* finally, shut the chip करोwn */
	SMC_SELECT_BANK( 1 );
	outw( inw( ioaddr + CONTROL ), CTL_POWERDOWN, ioaddr + CONTROL  );
#पूर्ण_अगर
पूर्ण


/*
 . Function: smc_seपंचांगulticast( पूर्णांक ioaddr, काष्ठा net_device *dev )
 . Purpose:
 .    This sets the पूर्णांकernal hardware table to filter out unwanted multicast
 .    packets beक्रमe they take up memory.
 .
 .    The SMC chip uses a hash table where the high 6 bits of the CRC of
 .    address are the offset पूर्णांकo the table.  If that bit is 1, then the
 .    multicast packet is accepted.  Otherwise, it's dropped silently.
 .
 .    To use the 6 bits as an offset पूर्णांकo the table, the high 3 bits are the
 .    number of the 8 bit रेजिस्टर, जबतक the low 3 bits are the bit within
 .    that रेजिस्टर.
 .
 . This routine is based very heavily on the one provided by Peter Cammaert.
*/


अटल व्योम smc_seपंचांगulticast(पूर्णांक ioaddr, काष्ठा net_device *dev)
अणु
	पूर्णांक			i;
	अचिन्हित अक्षर		multicast_table[ 8 ];
	काष्ठा netdev_hw_addr *ha;
	/* table क्रम flipping the order of 3 bits */
	अचिन्हित अक्षर invert3[] = अणु 0, 4, 2, 6, 1, 5, 3, 7 पूर्ण;

	/* start with a table of all zeros: reject all */
	स_रखो( multicast_table, 0, माप( multicast_table ) );

	netdev_क्रम_each_mc_addr(ha, dev) अणु
		पूर्णांक position;

		/* only use the low order bits */
		position = ether_crc_le(6, ha->addr) & 0x3f;

		/* करो some messy swapping to put the bit in the right spot */
		multicast_table[invert3[position&7]] |=
					(1<<invert3[(position>>3)&7]);

	पूर्ण
	/* now, the table can be loaded पूर्णांकo the chipset */
	SMC_SELECT_BANK( 3 );

	क्रम ( i = 0; i < 8 ; i++ ) अणु
		outb( multicast_table[i], ioaddr + MULTICAST1 + i );
	पूर्ण
पूर्ण

/*
 . Function: smc_रुको_to_send_packet( काष्ठा sk_buff * skb, काष्ठा net_device * )
 . Purpose:
 .    Attempt to allocate memory क्रम a packet, अगर chip-memory is not
 .    available, then tell the card to generate an पूर्णांकerrupt when it
 .    is available.
 .
 . Algorithm:
 .
 . o	अगर the saved_skb is not currently null, then drop this packet
 .	on the न्यूनमान.  This should never happen, because of TBUSY.
 . o	अगर the saved_skb is null, then replace it with the current packet,
 . o	See अगर I can sending it now.
 . o 	(NO): Enable पूर्णांकerrupts and let the पूर्णांकerrupt handler deal with it.
 . o	(YES):Send it now.
*/
अटल netdev_tx_t smc_रुको_to_send_packet(काष्ठा sk_buff *skb,
					   काष्ठा net_device *dev)
अणु
	काष्ठा smc_local *lp = netdev_priv(dev);
	अचिन्हित पूर्णांक ioaddr 	= dev->base_addr;
	word 			length;
	अचिन्हित लघु 		numPages;
	word			समय_out;

	netअगर_stop_queue(dev);
	/* Well, I want to send the packet.. but I करोn't know
	   अगर I can send it right now...  */

	अगर ( lp->saved_skb) अणु
		/* THIS SHOULD NEVER HAPPEN. */
		dev->stats.tx_पातed_errors++;
		prपूर्णांकk(CARDNAME": Bad Craziness - sent packet while busy.\n" );
		वापस NETDEV_TX_BUSY;
	पूर्ण
	lp->saved_skb = skb;

	length = skb->len;

	अगर (length < ETH_ZLEN) अणु
		अगर (skb_padto(skb, ETH_ZLEN)) अणु
			netअगर_wake_queue(dev);
			वापस NETDEV_TX_OK;
		पूर्ण
		length = ETH_ZLEN;
	पूर्ण

	/*
	** The MMU wants the number of pages to be the number of 256 bytes
	** 'pages', minus 1 ( since a packet can't ever have 0 pages :) )
	**
	** Pkt size क्रम allocating is data length +6 (क्रम additional status words,
	** length and ctl!) If odd size last byte is included in this header.
	*/
	numPages =  ((length & 0xfffe) + 6) / 256;

	अगर (numPages > 7 ) अणु
		prपूर्णांकk(CARDNAME": Far too big packet error.\n");
		/* मुक्तing the packet is a good thing here... but should
		 . any packets of this size get करोwn here?   */
		dev_kमुक्त_skb (skb);
		lp->saved_skb = शून्य;
		/* this IS an error, but, i करोn't want the skb saved */
		netअगर_wake_queue(dev);
		वापस NETDEV_TX_OK;
	पूर्ण
	/* either way, a packet is रुकोing now */
	lp->packets_रुकोing++;

	/* now, try to allocate the memory */
	SMC_SELECT_BANK( 2 );
	outw( MC_ALLOC | numPages, ioaddr + MMU_CMD );
	/*
 	. Perक्रमmance Hack
	.
 	. रुको a लघु amount of समय.. अगर I can send a packet now, I send
	. it now.  Otherwise, I enable an पूर्णांकerrupt and रुको क्रम one to be
	. available.
	.
	. I could have handled this a slightly dअगरferent way, by checking to
	. see अगर any memory was available in the FREE MEMORY रेजिस्टर.  However,
	. either way, I need to generate an allocation, and the allocation works
	. no matter what, so I saw no poपूर्णांक in checking मुक्त memory.
	*/
	समय_out = MEMORY_WAIT_TIME;
	करो अणु
		word	status;

		status = inb( ioaddr + INTERRUPT );
		अगर ( status & IM_ALLOC_INT ) अणु
			/* acknowledge the पूर्णांकerrupt */
			outb( IM_ALLOC_INT, ioaddr + INTERRUPT );
  			अवरोध;
		पूर्ण
   	पूर्ण जबतक ( -- समय_out );

   	अगर ( !समय_out ) अणु
		/* oh well, रुको until the chip finds memory later */
		SMC_ENABLE_INT( IM_ALLOC_INT );
		PRINTK2((CARDNAME": memory allocation deferred.\n"));
		/* it's deferred, but I'll handle it later */
		वापस NETDEV_TX_OK;
   	पूर्ण
	/* or YES! I can send the packet now.. */
	smc_hardware_send_packet(dev);
	netअगर_wake_queue(dev);
	वापस NETDEV_TX_OK;
पूर्ण

/*
 . Function:  smc_hardware_send_packet(काष्ठा net_device * )
 . Purpose:
 .	This sends the actual packet to the SMC9xxx chip.
 .
 . Algorithm:
 . 	First, see अगर a saved_skb is available.
 .		( this should NOT be called अगर there is no 'saved_skb'
 .	Now, find the packet number that the chip allocated
 .	Poपूर्णांक the data poपूर्णांकers at it in memory
 .	Set the length word in the chip's memory
 .	Dump the packet to chip memory
 .	Check अगर a last byte is needed ( odd length packet )
 .		अगर so, set the control flag right
 . 	Tell the card to send it
 .	Enable the transmit पूर्णांकerrupt, so I know अगर it failed
 . 	Free the kernel data अगर I actually sent it.
*/
अटल व्योम smc_hardware_send_packet( काष्ठा net_device * dev )
अणु
	काष्ठा smc_local *lp = netdev_priv(dev);
	byte	 		packet_no;
	काष्ठा sk_buff * 	skb = lp->saved_skb;
	word			length;
	अचिन्हित पूर्णांक		ioaddr;
	byte			* buf;

	ioaddr = dev->base_addr;

	अगर ( !skb ) अणु
		PRINTK((CARDNAME": In XMIT with no packet to send\n"));
		वापस;
	पूर्ण
	length = ETH_ZLEN < skb->len ? skb->len : ETH_ZLEN;
	buf = skb->data;

	/* If I get here, I _know_ there is a packet slot रुकोing क्रम me */
	packet_no = inb( ioaddr + PNR_ARR + 1 );
	अगर ( packet_no & 0x80 ) अणु
		/* or isn't there?  BAD CHIP! */
		netdev_dbg(dev, CARDNAME": Memory allocation failed.\n");
		dev_kमुक्त_skb_any(skb);
		lp->saved_skb = शून्य;
		netअगर_wake_queue(dev);
		वापस;
	पूर्ण

	/* we have a packet address, so tell the card to use it */
	outb( packet_no, ioaddr + PNR_ARR );

	/* poपूर्णांक to the beginning of the packet */
	outw( PTR_AUTOINC , ioaddr + POINTER );

	PRINTK3((CARDNAME": Trying to xmit packet of length %x\n", length));
#अगर SMC_DEBUG > 2
	prपूर्णांक_packet( buf, length );
#पूर्ण_अगर

	/* send the packet length ( +6 क्रम status, length and ctl byte )
 	   and the status word ( set to zeros ) */
#अगर_घोषित USE_32_BIT
	outl(  (length +6 ) << 16 , ioaddr + DATA_1 );
#अन्यथा
	outw( 0, ioaddr + DATA_1 );
	/* send the packet length ( +6 क्रम status words, length, and ctl*/
	outb( (length+6) & 0xFF,ioaddr + DATA_1 );
	outb( (length+6) >> 8 , ioaddr + DATA_1 );
#पूर्ण_अगर

	/* send the actual data
	 . I _think_ it's faster to send the दीर्घs first, and then
	 . mop up by sending the last word.  It depends heavily
 	 . on alignment, at least on the 486.  Maybe it would be
 	 . a good idea to check which is optimal?  But that could take
	 . almost as much समय as is saved?
	*/
#अगर_घोषित USE_32_BIT
	अगर ( length & 0x2  ) अणु
		outsl(ioaddr + DATA_1, buf,  length >> 2 );
		outw( *((word *)(buf + (length & 0xFFFFFFFC))),ioaddr +DATA_1);
	पूर्ण
	अन्यथा
		outsl(ioaddr + DATA_1, buf,  length >> 2 );
#अन्यथा
	outsw(ioaddr + DATA_1 , buf, (length ) >> 1);
#पूर्ण_अगर
	/* Send the last byte, अगर there is one.   */

	अगर ( (length & 1) == 0 ) अणु
		outw( 0, ioaddr + DATA_1 );
	पूर्ण अन्यथा अणु
		outb( buf[length -1 ], ioaddr + DATA_1 );
		outb( 0x20, ioaddr + DATA_1);
	पूर्ण

	/* enable the पूर्णांकerrupts */
	SMC_ENABLE_INT( (IM_TX_INT | IM_TX_EMPTY_INT) );

	/* and let the chipset deal with it */
	outw( MC_ENQUEUE , ioaddr + MMU_CMD );

	PRINTK2((CARDNAME": Sent packet of length %d\n", length));

	lp->saved_skb = शून्य;
	dev_kमुक्त_skb_any (skb);

	netअगर_trans_update(dev);

	/* we can send another packet */
	netअगर_wake_queue(dev);
पूर्ण

/*-------------------------------------------------------------------------
 |
 | smc_init(पूर्णांक unit)
 |   Input parameters:
 |	dev->base_addr == 0, try to find all possible locations
 |	dev->base_addr == 1, वापस failure code
 |	dev->base_addr == 2, always allocate space,  and वापस success
 |	dev->base_addr == <anything अन्यथा>   this is the address to check
 |
 |   Output:
 |	poपूर्णांकer to net_device or ERR_PTR(error)
 |
 ---------------------------------------------------------------------------
*/
अटल पूर्णांक io;
अटल पूर्णांक irq;
अटल पूर्णांक अगरport;

काष्ठा net_device * __init smc_init(पूर्णांक unit)
अणु
	काष्ठा net_device *dev = alloc_etherdev(माप(काष्ठा smc_local));
	काष्ठा devlist *smcdev = smc_devlist;
	पूर्णांक err = 0;

	अगर (!dev)
		वापस ERR_PTR(-ENODEV);

	अगर (unit >= 0) अणु
		प्र_लिखो(dev->name, "eth%d", unit);
		netdev_boot_setup_check(dev);
		io = dev->base_addr;
		irq = dev->irq;
	पूर्ण

	अगर (io > 0x1ff) अणु	/* Check a single specअगरied location. */
		err = smc_probe(dev, io);
	पूर्ण अन्यथा अगर (io != 0) अणु	/* Don't probe at all. */
		err = -ENXIO;
	पूर्ण अन्यथा अणु
		क्रम (;smcdev->port; smcdev++) अणु
			अगर (smc_probe(dev, smcdev->port) == 0)
				अवरोध;
		पूर्ण
		अगर (!smcdev->port)
			err = -ENODEV;
	पूर्ण
	अगर (err)
		जाओ out;
	err = रेजिस्टर_netdev(dev);
	अगर (err)
		जाओ out1;
	वापस dev;
out1:
	मुक्त_irq(dev->irq, dev);
	release_region(dev->base_addr, SMC_IO_EXTENT);
out:
	मुक्त_netdev(dev);
	वापस ERR_PTR(err);
पूर्ण

/*----------------------------------------------------------------------
 . smc_findirq
 .
 . This routine has a simple purpose -- make the SMC chip generate an
 . पूर्णांकerrupt, so an स्वतः-detect routine can detect it, and find the IRQ,
 ------------------------------------------------------------------------
*/
अटल पूर्णांक __init smc_findirq(पूर्णांक ioaddr)
अणु
#अगर_अघोषित NO_AUTOPROBE
	पूर्णांक	समयout = 20;
	अचिन्हित दीर्घ cookie;


	cookie = probe_irq_on();

	/*
	 * What I try to करो here is trigger an ALLOC_INT. This is करोne
	 * by allocating a small chunk of memory, which will give an पूर्णांकerrupt
	 * when करोne.
	 */


	SMC_SELECT_BANK(2);
	/* enable ALLOCation पूर्णांकerrupts ONLY */
	outb( IM_ALLOC_INT, ioaddr + INT_MASK );

	/*
 	 . Allocate 512 bytes of memory.  Note that the chip was just
	 . reset so all the memory is available
	*/
	outw( MC_ALLOC | 1, ioaddr + MMU_CMD );

	/*
	 . Wait until positive that the पूर्णांकerrupt has been generated
	*/
	जबतक ( समयout ) अणु
		byte	पूर्णांक_status;

		पूर्णांक_status = inb( ioaddr + INTERRUPT );

		अगर ( पूर्णांक_status & IM_ALLOC_INT )
			अवरोध;		/* got the पूर्णांकerrupt */
		समयout--;
	पूर्ण
	/* there is really nothing that I can करो here अगर समयout fails,
	   as probe_irq_off will वापस a 0 anyway, which is what I
	   want in this हाल.   Plus, the clean up is needed in both
	   हालs.  */

	/* DELAY HERE!
	   On a fast machine, the status might change beक्रमe the पूर्णांकerrupt
	   is given to the processor.  This means that the पूर्णांकerrupt was
	   never detected, and probe_irq_off fails to report anything.
	   This should fix probe_irq_* problems.
	*/
	SMC_DELAY();
	SMC_DELAY();

	/* and disable all पूर्णांकerrupts again */
	outb( 0, ioaddr + INT_MASK );

	/* and वापस what I found */
	वापस probe_irq_off(cookie);
#अन्यथा /* NO_AUTOPROBE */
	काष्ठा devlist *smcdev;
	क्रम (smcdev = smc_devlist; smcdev->port; smcdev++) अणु
		अगर (smcdev->port == ioaddr)
			वापस smcdev->irq;
	पूर्ण
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल स्थिर काष्ठा net_device_ops smc_netdev_ops = अणु
	.nकरो_खोलो		 = smc_खोलो,
	.nकरो_stop		= smc_बंद,
	.nकरो_start_xmit    	= smc_रुको_to_send_packet,
	.nकरो_tx_समयout	    	= smc_समयout,
	.nकरो_set_rx_mode	= smc_set_multicast_list,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

/*----------------------------------------------------------------------
 . Function: smc_probe( पूर्णांक ioaddr )
 .
 . Purpose:
 .	Tests to see अगर a given ioaddr poपूर्णांकs to an SMC9xxx chip.
 .	Returns a 0 on success
 .
 . Algorithm:
 .	(1) see अगर the high byte of BANK_SELECT is 0x33
 . 	(2) compare the ioaddr with the base रेजिस्टर's address
 .	(3) see अगर I recognize the chip ID in the appropriate रेजिस्टर
 .
 .---------------------------------------------------------------------
 */

/*---------------------------------------------------------------
 . Here I करो typical initialization tasks.
 .
 . o  Initialize the काष्ठाure अगर needed
 . o  prपूर्णांक out my vanity message अगर not करोne so alपढ़ोy
 . o  prपूर्णांक out what type of hardware is detected
 . o  prपूर्णांक out the ethernet address
 . o  find the IRQ
 . o  set up my निजी data
 . o  configure the dev काष्ठाure with my subroutines
 . o  actually GRAB the irq.
 . o  GRAB the region
 .-----------------------------------------------------------------
*/
अटल पूर्णांक __init smc_probe(काष्ठा net_device *dev, पूर्णांक ioaddr)
अणु
	पूर्णांक i, memory, retval;
	अचिन्हित पूर्णांक bank;

	स्थिर अक्षर *version_string;
	स्थिर अक्षर *अगर_string;

	/* रेजिस्टरs */
	word revision_रेजिस्टर;
	word base_address_रेजिस्टर;
	word configuration_रेजिस्टर;
	word memory_info_रेजिस्टर;
	word memory_cfg_रेजिस्टर;

	/* Grab the region so that no one अन्यथा tries to probe our ioports. */
	अगर (!request_region(ioaddr, SMC_IO_EXTENT, DRV_NAME))
		वापस -EBUSY;

	dev->irq = irq;
	dev->अगर_port = अगरport;

	/* First, see अगर the high byte is 0x33 */
	bank = inw( ioaddr + BANK_SELECT );
	अगर ( (bank & 0xFF00) != 0x3300 ) अणु
		retval = -ENODEV;
		जाओ err_out;
	पूर्ण
	/* The above MIGHT indicate a device, but I need to ग_लिखो to further
 	 	test this.  */
	outw( 0x0, ioaddr + BANK_SELECT );
	bank = inw( ioaddr + BANK_SELECT );
	अगर ( (bank & 0xFF00 ) != 0x3300 ) अणु
		retval = -ENODEV;
		जाओ err_out;
	पूर्ण
	/* well, we've already written once, so hopefully another time won't
 	   hurt.  This समय, I need to चयन the bank रेजिस्टर to bank 1,
	   so I can access the base address रेजिस्टर */
	SMC_SELECT_BANK(1);
	base_address_रेजिस्टर = inw( ioaddr + BASE );
	अगर ( ioaddr != ( base_address_रेजिस्टर >> 3 & 0x3E0 ) )  अणु
		prपूर्णांकk(CARDNAME ": IOADDR %x doesn't match configuration (%x). "
			"Probably not a SMC chip\n",
			ioaddr, base_address_रेजिस्टर >> 3 & 0x3E0 );
		/* well, the base address रेजिस्टर didn't match.  Must not have
		   been a SMC chip after all. */
		retval = -ENODEV;
		जाओ err_out;
	पूर्ण

	/*  check अगर the revision रेजिस्टर is something that I recognize.
	    These might need to be added to later, as future revisions
	    could be added.  */
	SMC_SELECT_BANK(3);
	revision_रेजिस्टर  = inw( ioaddr + REVISION );
	अगर ( !chip_ids[ ( revision_रेजिस्टर  >> 4 ) & 0xF  ] ) अणु
		/* I करोn't recognize this chip, so... */
		prपूर्णांकk(CARDNAME ": IO %x: Unrecognized revision register:"
			" %x, Contact author.\n", ioaddr, revision_रेजिस्टर);

		retval = -ENODEV;
		जाओ err_out;
	पूर्ण

	/* at this poपूर्णांक I'll assume that the chip is an SMC9xxx.
	   It might be prudent to check a listing of MAC addresses
	   against the hardware address, or करो some other tests. */

	pr_info_once("%s\n", version);

	/* fill in some of the fields */
	dev->base_addr = ioaddr;

	/*
 	 . Get the MAC address ( bank 1, regs 4 - 9 )
	*/
	SMC_SELECT_BANK( 1 );
	क्रम ( i = 0; i < 6; i += 2 ) अणु
		word	address;

		address = inw( ioaddr + ADDR0 + i  );
		dev->dev_addr[ i + 1] = address >> 8;
		dev->dev_addr[ i ] = address & 0xFF;
	पूर्ण

	/* get the memory inक्रमmation */

	SMC_SELECT_BANK( 0 );
	memory_info_रेजिस्टर = inw( ioaddr + MIR );
	memory_cfg_रेजिस्टर  = inw( ioaddr + MCR );
	memory = ( memory_cfg_रेजिस्टर >> 9 )  & 0x7;  /* multiplier */
	memory *= 256 * ( memory_info_रेजिस्टर & 0xFF );

	/*
	 Now, I want to find out more about the chip.  This is sort of
 	 redundant, but it's cleaner to have it in both, rather than having
 	 one VERY दीर्घ probe procedure.
	*/
	SMC_SELECT_BANK(3);
	revision_रेजिस्टर  = inw( ioaddr + REVISION );
	version_string = chip_ids[ ( revision_रेजिस्टर  >> 4 ) & 0xF  ];
	अगर ( !version_string ) अणु
		/* I shouldn't get here because this call was करोne beक्रमe.... */
		retval = -ENODEV;
		जाओ err_out;
	पूर्ण

	/* is it using AUI or 10BaseT ? */
	अगर ( dev->अगर_port == 0 ) अणु
		SMC_SELECT_BANK(1);
		configuration_रेजिस्टर = inw( ioaddr + CONFIG );
		अगर ( configuration_रेजिस्टर & CFG_AUI_SELECT )
			dev->अगर_port = 2;
		अन्यथा
			dev->अगर_port = 1;
	पूर्ण
	अगर_string = पूर्णांकerfaces[ dev->अगर_port - 1 ];

	/* now, reset the chip, and put it पूर्णांकo a known state */
	smc_reset( ioaddr );

	/*
	 . If dev->irq is 0, then the device has to be banged on to see
	 . what the IRQ is.
 	 .
	 . This banging करोesn't always detect the IRQ, क्रम unknown reasons.
	 . a workaround is to reset the chip and try again.
	 .
	 . Interestingly, the DOS packet driver *SETS* the IRQ on the card to
	 . be what is requested on the command line.   I करोn't करो that, mostly
	 . because the card that I have uses a non-standard method of accessing
	 . the IRQs, and because this _should_ work in most configurations.
	 .
	 . Specअगरying an IRQ is करोne with the assumption that the user knows
	 . what (s)he is करोing.  No checking is करोne!!!!
 	 .
	*/
	अगर ( dev->irq < 2 ) अणु
		पूर्णांक	trials;

		trials = 3;
		जबतक ( trials-- ) अणु
			dev->irq = smc_findirq( ioaddr );
			अगर ( dev->irq )
				अवरोध;
			/* kick the card and try again */
			smc_reset( ioaddr );
		पूर्ण
	पूर्ण
	अगर (dev->irq == 0 ) अणु
		prपूर्णांकk(CARDNAME": Couldn't autodetect your IRQ. Use irq=xx.\n");
		retval = -ENODEV;
		जाओ err_out;
	पूर्ण

	/* now, prपूर्णांक out the card info, in a लघु क्रमmat.. */

	netdev_info(dev, "%s(r:%d) at %#3x IRQ:%d INTF:%s MEM:%db ",
		    version_string, revision_रेजिस्टर & 0xF, ioaddr, dev->irq,
		    अगर_string, memory);
	/*
	 . Prपूर्णांक the Ethernet address
	*/
	netdev_info(dev, "ADDR: %pM\n", dev->dev_addr);

	/* Grab the IRQ */
	retval = request_irq(dev->irq, smc_पूर्णांकerrupt, 0, DRV_NAME, dev);
	अगर (retval) अणु
		netdev_warn(dev, "%s: unable to get IRQ %d (irqval=%d).\n",
			    DRV_NAME, dev->irq, retval);
		जाओ err_out;
	पूर्ण

	dev->netdev_ops			= &smc_netdev_ops;
	dev->watchकरोg_समयo		= HZ/20;

	वापस 0;

err_out:
	release_region(ioaddr, SMC_IO_EXTENT);
	वापस retval;
पूर्ण

#अगर SMC_DEBUG > 2
अटल व्योम prपूर्णांक_packet( byte * buf, पूर्णांक length )
अणु
#अगर 0
	prपूर्णांक_hex_dump_debug(DRV_NAME, DUMP_PREFIX_OFFSET, 16, 1,
			     buf, length, true);
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर


/*
 * Open and Initialize the board
 *
 * Set up everything, reset the card, etc ..
 *
 */
अटल पूर्णांक smc_खोलो(काष्ठा net_device *dev)
अणु
	पूर्णांक	ioaddr = dev->base_addr;

	पूर्णांक	i;	/* used to set hw ethernet address */

	/* clear out all the junk that was put here beक्रमe... */
	स_रखो(netdev_priv(dev), 0, माप(काष्ठा smc_local));

	/* reset the hardware */

	smc_reset( ioaddr );
	smc_enable( ioaddr );

	/* Select which पूर्णांकerface to use */

	SMC_SELECT_BANK( 1 );
	अगर ( dev->अगर_port == 1 ) अणु
		outw( inw( ioaddr + CONFIG ) & ~CFG_AUI_SELECT,
			ioaddr + CONFIG );
	पूर्ण
	अन्यथा अगर ( dev->अगर_port == 2 ) अणु
		outw( inw( ioaddr + CONFIG ) | CFG_AUI_SELECT,
			ioaddr + CONFIG );
	पूर्ण

	/*
  		According to Becker, I have to set the hardware address
		at this poपूर्णांक, because the (l)user can set it with an
		ioctl.  Easily करोne...
	*/
	SMC_SELECT_BANK( 1 );
	क्रम ( i = 0; i < 6; i += 2 ) अणु
		word	address;

		address = dev->dev_addr[ i + 1 ] << 8 ;
		address  |= dev->dev_addr[ i ];
		outw( address, ioaddr + ADDR0 + i );
	पूर्ण

	netअगर_start_queue(dev);
	वापस 0;
पूर्ण

/*--------------------------------------------------------
 . Called by the kernel to send a packet out पूर्णांकo the व्योम
 . of the net.  This routine is largely based on
 . skeleton.c, from Becker.
 .--------------------------------------------------------
*/

अटल व्योम smc_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	/* If we get here, some higher level has decided we are broken.
	   There should really be a "kick me" function call instead. */
	netdev_warn(dev, CARDNAME": transmit timed out, %s?\n",
		    tx_करोne(dev) ? "IRQ conflict" : "network cable problem");
	/* "kick" the adaptor */
	smc_reset( dev->base_addr );
	smc_enable( dev->base_addr );
	netअगर_trans_update(dev); /* prevent tx समयout */
	/* clear anything saved */
	((काष्ठा smc_local *)netdev_priv(dev))->saved_skb = शून्य;
	netअगर_wake_queue(dev);
पूर्ण

/*-------------------------------------------------------------
 .
 . smc_rcv -  receive a packet from the card
 .
 . There is ( at least ) a packet रुकोing to be पढ़ो from
 . chip-memory.
 .
 . o Read the status
 . o If an error, record it
 . o otherwise, पढ़ो in the packet
 --------------------------------------------------------------
*/
अटल व्योम smc_rcv(काष्ठा net_device *dev)
अणु
	पूर्णांक 	ioaddr = dev->base_addr;
	पूर्णांक 	packet_number;
	word	status;
	word	packet_length;

	/* assume bank 2 */

	packet_number = inw( ioaddr + FIFO_PORTS );

	अगर ( packet_number & FP_RXEMPTY ) अणु
		/* we got called , but nothing was on the FIFO */
		PRINTK((CARDNAME ": WARNING: smc_rcv with nothing on FIFO.\n"));
		/* करोn't need to restore anything */
		वापस;
	पूर्ण

	/*  start पढ़ोing from the start of the packet */
	outw( PTR_READ | PTR_RCV | PTR_AUTOINC, ioaddr + POINTER );

	/* First two words are status and packet_length */
	status 		= inw( ioaddr + DATA_1 );
	packet_length 	= inw( ioaddr + DATA_1 );

	packet_length &= 0x07ff;  /* mask off top bits */

	PRINTK2(("RCV: STATUS %4x LENGTH %4x\n", status, packet_length ));
	/*
	 . the packet length contains 3 extra words :
	 . status, length, and an extra word with an odd byte .
	*/
	packet_length -= 6;

	अगर ( !(status & RS_ERRORS ) )अणु
		/* करो stuff to make a new packet */
		काष्ठा sk_buff  * skb;
		byte		* data;

		/* पढ़ो one extra byte */
		अगर ( status & RS_ODDFRAME )
			packet_length++;

		/* set multicast stats */
		अगर ( status & RS_MULTICAST )
			dev->stats.multicast++;

		skb = netdev_alloc_skb(dev, packet_length + 5);
		अगर ( skb == शून्य ) अणु
			dev->stats.rx_dropped++;
			जाओ करोne;
		पूर्ण

		/*
		 ! This should work without alignment, but it could be
		 ! in the worse हाल
		*/

		skb_reserve( skb, 2 );   /* 16 bit alignment */

		data = skb_put( skb, packet_length);

#अगर_घोषित USE_32_BIT
		/* QUESTION:  Like in the TX routine, करो I want
		   to send the DWORDs or the bytes first, or some
		   mixture.  A mixture might improve alपढ़ोy slow PIO
		   perक्रमmance  */
		PRINTK3((" Reading %d dwords (and %d bytes)\n",
			packet_length >> 2, packet_length & 3 ));
		insl(ioaddr + DATA_1 , data, packet_length >> 2 );
		/* पढ़ो the left over bytes */
		insb( ioaddr + DATA_1, data + (packet_length & 0xFFFFFC),
			packet_length & 0x3  );
#अन्यथा
		PRINTK3((" Reading %d words and %d byte(s)\n",
			(packet_length >> 1 ), packet_length & 1 ));
		insw(ioaddr + DATA_1 , data, packet_length >> 1);
		अगर ( packet_length & 1 ) अणु
			data += packet_length & ~1;
			*(data++) = inb( ioaddr + DATA_1 );
		पूर्ण
#पूर्ण_अगर
#अगर	SMC_DEBUG > 2
			prपूर्णांक_packet( data, packet_length );
#पूर्ण_अगर

		skb->protocol = eth_type_trans(skb, dev );
		netअगर_rx(skb);
		dev->stats.rx_packets++;
		dev->stats.rx_bytes += packet_length;
	पूर्ण अन्यथा अणु
		/* error ... */
		dev->stats.rx_errors++;

		अगर ( status & RS_ALGNERR )  dev->stats.rx_frame_errors++;
		अगर ( status & (RS_TOOSHORT | RS_TOOLONG ) )
			dev->stats.rx_length_errors++;
		अगर ( status & RS_BADCRC)	dev->stats.rx_crc_errors++;
	पूर्ण

करोne:
	/*  error or good, tell the card to get rid of this packet */
	outw( MC_RELEASE, ioaddr + MMU_CMD );
पूर्ण


/*************************************************************************
 . smc_tx
 .
 . Purpose:  Handle a transmit error message.   This will only be called
 .   when an error, because of the AUTO_RELEASE mode.
 .
 . Algorithm:
 .	Save poपूर्णांकer and packet no
 .	Get the packet no from the top of the queue
 .	check अगर it's valid ( अगर not, is this an error??? )
 .	पढ़ो the status word
 .	record the error
 .	( resend?  Not really, since we करोn't want old packets around )
 .	Restore saved values
 ************************************************************************/
अटल व्योम smc_tx( काष्ठा net_device * dev )
अणु
	पूर्णांक	ioaddr = dev->base_addr;
	काष्ठा smc_local *lp = netdev_priv(dev);
	byte saved_packet;
	byte packet_no;
	word tx_status;


	/* assume bank 2  */

	saved_packet = inb( ioaddr + PNR_ARR );
	packet_no = inw( ioaddr + FIFO_PORTS );
	packet_no &= 0x7F;

	/* select this as the packet to पढ़ो from */
	outb( packet_no, ioaddr + PNR_ARR );

	/* पढ़ो the first word from this packet */
	outw( PTR_AUTOINC | PTR_READ, ioaddr + POINTER );

	tx_status = inw( ioaddr + DATA_1 );
	PRINTK3((CARDNAME": TX DONE STATUS: %4x\n", tx_status));

	dev->stats.tx_errors++;
	अगर ( tx_status & TS_LOSTCAR ) dev->stats.tx_carrier_errors++;
	अगर ( tx_status & TS_LATCOL  ) अणु
		netdev_dbg(dev, CARDNAME": Late collision occurred on last xmit.\n");
		dev->stats.tx_winकरोw_errors++;
	पूर्ण
#अगर 0
		अगर ( tx_status & TS_16COL ) अणु ... पूर्ण
#पूर्ण_अगर

	अगर ( tx_status & TS_SUCCESS ) अणु
		netdev_info(dev, CARDNAME": Successful packet caused interrupt\n");
	पूर्ण
	/* re-enable transmit */
	SMC_SELECT_BANK( 0 );
	outw( inw( ioaddr + TCR ) | TCR_ENABLE, ioaddr + TCR );

	/* समाप्त the packet */
	SMC_SELECT_BANK( 2 );
	outw( MC_FREEPKT, ioaddr + MMU_CMD );

	/* one less packet रुकोing क्रम me */
	lp->packets_रुकोing--;

	outb( saved_packet, ioaddr + PNR_ARR );
पूर्ण

/*--------------------------------------------------------------------
 .
 . This is the मुख्य routine of the driver, to handle the device when
 . it needs some attention.
 .
 . So:
 .   first, save state of the chipset
 .   branch off पूर्णांकo routines to handle each हाल, and acknowledge
 .	    each to the पूर्णांकerrupt रेजिस्टर
 .   and finally restore state.
 .
 ---------------------------------------------------------------------*/

अटल irqवापस_t smc_पूर्णांकerrupt(पूर्णांक irq, व्योम * dev_id)
अणु
	काष्ठा net_device *dev 	= dev_id;
	पूर्णांक ioaddr 		= dev->base_addr;
	काष्ठा smc_local *lp = netdev_priv(dev);

	byte	status;
	word	card_stats;
	byte	mask;
	पूर्णांक	समयout;
	/* state रेजिस्टरs */
	word	saved_bank;
	word	saved_poपूर्णांकer;
	पूर्णांक handled = 0;


	PRINTK3((CARDNAME": SMC interrupt started\n"));

	saved_bank = inw( ioaddr + BANK_SELECT );

	SMC_SELECT_BANK(2);
	saved_poपूर्णांकer = inw( ioaddr + POINTER );

	mask = inb( ioaddr + INT_MASK );
	/* clear all पूर्णांकerrupts */
	outb( 0, ioaddr + INT_MASK );


	/* set a समयout value, so I करोn't stay here क्रमever */
	समयout = 4;

	PRINTK2((KERN_WARNING CARDNAME ": MASK IS %x\n", mask));
	करो अणु
		/* पढ़ो the status flag, and mask it */
		status = inb( ioaddr + INTERRUPT ) & mask;
		अगर (!status )
			अवरोध;

		handled = 1;

		PRINTK3((KERN_WARNING CARDNAME
			": Handling interrupt status %x\n", status));

		अगर (status & IM_RCV_INT) अणु
			/* Got a packet(s). */
			PRINTK2((KERN_WARNING CARDNAME
				": Receive Interrupt\n"));
			smc_rcv(dev);
		पूर्ण अन्यथा अगर (status & IM_TX_INT ) अणु
			PRINTK2((KERN_WARNING CARDNAME
				": TX ERROR handled\n"));
			smc_tx(dev);
			outb(IM_TX_INT, ioaddr + INTERRUPT );
		पूर्ण अन्यथा अगर (status & IM_TX_EMPTY_INT ) अणु
			/* update stats */
			SMC_SELECT_BANK( 0 );
			card_stats = inw( ioaddr + COUNTER );
			/* single collisions */
			dev->stats.collisions += card_stats & 0xF;
			card_stats >>= 4;
			/* multiple collisions */
			dev->stats.collisions += card_stats & 0xF;

			/* these are क्रम when linux supports these statistics */

			SMC_SELECT_BANK( 2 );
			PRINTK2((KERN_WARNING CARDNAME
				": TX_BUFFER_EMPTY handled\n"));
			outb( IM_TX_EMPTY_INT, ioaddr + INTERRUPT );
			mask &= ~IM_TX_EMPTY_INT;
			dev->stats.tx_packets += lp->packets_रुकोing;
			lp->packets_रुकोing = 0;

		पूर्ण अन्यथा अगर (status & IM_ALLOC_INT ) अणु
			PRINTK2((KERN_DEBUG CARDNAME
				": Allocation interrupt\n"));
			/* clear this पूर्णांकerrupt so it करोesn't happen again */
			mask &= ~IM_ALLOC_INT;

			smc_hardware_send_packet( dev );

			/* enable xmit पूर्णांकerrupts based on this */
			mask |= ( IM_TX_EMPTY_INT | IM_TX_INT );

			/* and let the card send more packets to me */
			netअगर_wake_queue(dev);

			PRINTK2((CARDNAME": Handoff done successfully.\n"));
		पूर्ण अन्यथा अगर (status & IM_RX_OVRN_INT ) अणु
			dev->stats.rx_errors++;
			dev->stats.rx_fअगरo_errors++;
			outb( IM_RX_OVRN_INT, ioaddr + INTERRUPT );
		पूर्ण अन्यथा अगर (status & IM_EPH_INT ) अणु
			PRINTK((CARDNAME ": UNSUPPORTED: EPH INTERRUPT\n"));
		पूर्ण अन्यथा अगर (status & IM_ERCV_INT ) अणु
			PRINTK((CARDNAME ": UNSUPPORTED: ERCV INTERRUPT\n"));
			outb( IM_ERCV_INT, ioaddr + INTERRUPT );
		पूर्ण
	पूर्ण जबतक ( समयout -- );


	/* restore state रेजिस्टर */
	SMC_SELECT_BANK( 2 );
	outb( mask, ioaddr + INT_MASK );

	PRINTK3((KERN_WARNING CARDNAME ": MASK is now %x\n", mask));
	outw( saved_poपूर्णांकer, ioaddr + POINTER );

	SMC_SELECT_BANK( saved_bank );

	PRINTK3((CARDNAME ": Interrupt done\n"));
	वापस IRQ_RETVAL(handled);
पूर्ण


/*----------------------------------------------------
 . smc_बंद
 .
 . this makes the board clean up everything that it can
 . and not talk to the outside world.   Caused by
 . an 'ifconfig ethX down'
 .
 -----------------------------------------------------*/
अटल पूर्णांक smc_बंद(काष्ठा net_device *dev)
अणु
	netअगर_stop_queue(dev);
	/* clear everything */
	smc_shutकरोwn( dev->base_addr );

	/* Update the statistics here. */
	वापस 0;
पूर्ण

/*-----------------------------------------------------------
 . smc_set_multicast_list
 .
 . This routine will, depending on the values passed to it,
 . either make it accept multicast packets, go पूर्णांकo
 . promiscuous mode ( क्रम TCPDUMP and cousins ) or accept
 . a select set of multicast packets
*/
अटल व्योम smc_set_multicast_list(काष्ठा net_device *dev)
अणु
	लघु ioaddr = dev->base_addr;

	SMC_SELECT_BANK(0);
	अगर ( dev->flags & IFF_PROMISC )
		outw( inw(ioaddr + RCR ) | RCR_PROMISC, ioaddr + RCR );

/* BUG?  I never disable promiscuous mode अगर multicasting was turned on.
   Now, I turn off promiscuous mode, but I करोn't करो anything to multicasting
   when promiscuous mode is turned on.
*/

	/* Here, I am setting this to accept all multicast packets.
	   I करोn't need to zero the multicast table, because the flag is
	   checked beक्रमe the table is
	*/
	अन्यथा अगर (dev->flags & IFF_ALLMULTI)
		outw( inw(ioaddr + RCR ) | RCR_ALMUL, ioaddr + RCR );

	/* We just get all multicast packets even अगर we only want them
	 . from one source.  This will be changed at some future
	 . poपूर्णांक. */
	अन्यथा अगर (!netdev_mc_empty(dev)) अणु
		/* support hardware multicasting */

		/* be sure I get rid of flags I might have set */
		outw( inw( ioaddr + RCR ) & ~(RCR_PROMISC | RCR_ALMUL),
			ioaddr + RCR );
		/* NOTE: this has to set the bank, so make sure it is the
		   last thing called.  The bank is set to zero at the top */
		smc_seपंचांगulticast(ioaddr, dev);
	पूर्ण
	अन्यथा  अणु
		outw( inw( ioaddr + RCR ) & ~(RCR_PROMISC | RCR_ALMUL),
			ioaddr + RCR );

		/*
		  since I'm disabling all multicast entirely, I need to
		  clear the multicast list
		*/
		SMC_SELECT_BANK( 3 );
		outw( 0, ioaddr + MULTICAST1 );
		outw( 0, ioaddr + MULTICAST2 );
		outw( 0, ioaddr + MULTICAST3 );
		outw( 0, ioaddr + MULTICAST4 );
	पूर्ण
पूर्ण

#अगर_घोषित MODULE

अटल काष्ठा net_device *devSMC9194;
MODULE_LICENSE("GPL");

module_param_hw(io, पूर्णांक, ioport, 0);
module_param_hw(irq, पूर्णांक, irq, 0);
module_param(अगरport, पूर्णांक, 0);
MODULE_PARM_DESC(io, "SMC 99194 I/O base address");
MODULE_PARM_DESC(irq, "SMC 99194 IRQ number");
MODULE_PARM_DESC(अगरport, "SMC 99194 interface port (0-default, 1-TP, 2-AUI)");

पूर्णांक __init init_module(व्योम)
अणु
	अगर (io == 0)
		prपूर्णांकk(KERN_WARNING
		CARDNAME": You shouldn't use auto-probing with insmod!\n" );

	/* copy the parameters from insmod पूर्णांकo the device काष्ठाure */
	devSMC9194 = smc_init(-1);
	वापस PTR_ERR_OR_ZERO(devSMC9194);
पूर्ण

व्योम __निकास cleanup_module(व्योम)
अणु
	unरेजिस्टर_netdev(devSMC9194);
	मुक्त_irq(devSMC9194->irq, devSMC9194);
	release_region(devSMC9194->base_addr, SMC_IO_EXTENT);
	मुक्त_netdev(devSMC9194);
पूर्ण

#पूर्ण_अगर /* MODULE */
