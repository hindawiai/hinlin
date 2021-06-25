<शैली गुरु>
#घोषणा RCS_ID "$Id: scc.c,v 1.75 1998/11/04 15:15:01 jreuter Exp jreuter $"

#घोषणा VERSION "3.0"

/*
 * Please use z8530drv-utils-3.0 with this version.
 *            ------------------
 *
 * You can find a subset of the करोcumentation in 
 * Documentation/networking/device_drivers/hamradio/z8530drv.rst.
 */

/*
   ********************************************************************
   *   SCC.C - Linux driver क्रम Z8530 based HDLC cards क्रम AX.25      *
   ********************************************************************


   ********************************************************************

	Copyright (c) 1993, 2000 Joerg Reuter DL1BKE

	portions (c) 1993 Guiकरो ten Dolle PE1NNZ

   ********************************************************************
   
   The driver and the programs in the archive are UNDER CONSTRUCTION.
   The code is likely to fail, and so your kernel could --- even 
   a whole network. 

   This driver is पूर्णांकended क्रम Amateur Radio use. If you are running it
   क्रम commercial purposes, please drop me a note. I am nosy...

   ...BUT:
 
   ! You  m u s t  recognize the appropriate legislations of your country !
   ! beक्रमe you connect a radio to the SCC board and start to transmit or !
   ! receive. The GPL allows you to use the  d r i v e r,  NOT the RADIO! !

   For non-Amateur-Radio use please note that you might need a special
   allowance/licence from the designer of the SCC Board and/or the
   MODEM. 

   This program is मुक्त software; you can redistribute it and/or modअगरy 
   it under the terms of the (modअगरied) GNU General Public License 
   delivered with the Linux kernel source.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License क्रम more details.

   You should find a copy of the GNU General Public License in 
   /usr/src/linux/COPYING; 
   
   ******************************************************************** 

		
   Incomplete history of z8530drv:
   -------------------------------

   1994-09-13	started to ग_लिखो the driver, rescued most of my own
		code (and Hans Alblas' memory buffer pool concept) from 
		an earlier project "sccdrv" which was initiated by 
		Guiकरो ten Dolle. Not much of the old driver survived, 
		though. The first version I put my hands on was sccdrv1.3
		from August 1993. The memory buffer pool concept
		appeared in an unauthorized sccdrv version (1.5) from
		August 1994.

   1995-01-31	changed copyright notice to GPL without limitations.
   
     .
     .	<SNIP>
     .
   		  
   1996-10-05	New semester, new driver... 

   		  * KISS TNC emulator हटाओd (TTY driver)
   		  * Source moved to drivers/net/
   		  * Includes Z8530 defines from drivers/net/z8530.h
   		  * Uses sk_buffer memory management
   		  * Reduced overhead of /proc/net/z8530drv output
   		  * Streamlined quite a lot things
   		  * Invents bअक्रम new bugs... ;-)

   		  The move to version number 3.0 reflects theses changes.
   		  You can use 'kissbridge' अगर you need a KISS TNC emulator.

   1996-12-13	Fixed क्रम Linux networking changes. (G4KLX)
   1997-01-08	Fixed the reमुख्यing problems.
   1997-04-02	Hopefully fixed the problems with the new *_समयr()
   		routines, added calibration code.
   1997-10-12	Made SCC_DELAY a CONFIG option, added CONFIG_SCC_TRXECHO
   1998-01-29	Small fix to aव्योम lock-up on initialization
   1998-09-29	Fixed the "grouping" bugs, tx_inhibit works again,
   		using dev->tx_queue_len now instead of MAXQUEUE now.
   1998-10-21	Postponed the spinlock changes, would need a lot of
   		testing I currently करोn't have the time to. Softdcd doesn't
   		work.
   1998-11-04	Softdcd करोes not work correctly in DPLL mode, in fact it 
   		never did. The DPLL locks on noise, the SYNC unit sees
   		flags that aren't... Restarting the DPLL करोes not help
   		either, it resynchronizes too slow and the first received
   		frame माला_लो lost.
   2000-02-13	Fixed क्रम new network driver पूर्णांकerface changes, still
   		करोes TX समयouts itself since it uses its own queue
   		scheme.

   Thanks to all who contributed to this driver with ideas and bug
   reports!
   
   NB -- अगर you find errors, change something, please let me know
      	 first beक्रमe you distribute it... And please करोn't touch
   	 the version number. Just replace my callsign in
   	 "v3.0.dl1bke" with your own. Just to aव्योम confusion...

   If you want to add your modअगरication to the linux distribution
   please (!) contact me first.
   
   New versions of the driver will be announced on the linux-hams
   mailing list on vger.kernel.org. To subscribe send an e-mail
   to majorकरोmo@vger.kernel.org with the following line in
   the body of the mail:
   
	   subscribe linux-hams
	   
   The content of the "Subject" field will be ignored.

   vy 73,
   Joerg Reuter	ampr-net: dl1bke@db0pra.ampr.org
		AX-25   : DL1BKE @ DB0ABH.#BAY.DEU.EU
		Internet: jreuter@yaina.de
		www     : http://yaina.de/jreuter
*/

/* ----------------------------------------------------------------------- */

#अघोषित  SCC_LDELAY		/* slow it even a bit more करोwn */
#अघोषित  SCC_DONT_CHECK		/* करोn't look अगर the SCCs you specअगरied are available */

#घोषणा SCC_MAXCHIPS	4       /* number of max. supported chips */
#घोषणा SCC_बफ_मानE	384     /* must not exceed 4096 */
#अघोषित	SCC_DEBUG

#घोषणा SCC_DEFAULT_CLOCK	4915200 
				/* शेष pघड़ी अगर nothing is specअगरied */

/* ----------------------------------------------------------------------- */

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/समयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/माला.स>
#समावेश <linux/in.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/delay.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/socket.h>
#समावेश <linux/init.h>
#समावेश <linux/scc.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/kernel.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/bitops.h>

#समावेश <net/net_namespace.h>
#समावेश <net/ax25.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>

#समावेश "z8530.h"

अटल स्थिर अक्षर banner[] __initस्थिर = KERN_INFO \
	"AX.25: Z8530 SCC driver version "VERSION".dl1bke\n";

अटल व्योम t_dरुको(काष्ठा समयr_list *t);
अटल व्योम t_txdelay(काष्ठा समयr_list *t);
अटल व्योम t_tail(काष्ठा समयr_list *t);
अटल व्योम t_busy(काष्ठा समयr_list *);
अटल व्योम t_maxkeyup(काष्ठा समयr_list *);
अटल व्योम t_idle(काष्ठा समयr_list *t);
अटल व्योम scc_tx_करोne(काष्ठा scc_channel *);
अटल व्योम scc_start_tx_समयr(काष्ठा scc_channel *,
			       व्योम (*)(काष्ठा समयr_list *), अचिन्हित दीर्घ);
अटल व्योम scc_start_maxkeyup(काष्ठा scc_channel *);
अटल व्योम scc_start_defer(काष्ठा scc_channel *);

अटल व्योम z8530_init(व्योम);

अटल व्योम init_channel(काष्ठा scc_channel *scc);
अटल व्योम scc_key_trx (काष्ठा scc_channel *scc, अक्षर tx);
अटल व्योम scc_init_समयr(काष्ठा scc_channel *scc);

अटल पूर्णांक scc_net_alloc(स्थिर अक्षर *name, काष्ठा scc_channel *scc);
अटल व्योम scc_net_setup(काष्ठा net_device *dev);
अटल पूर्णांक scc_net_खोलो(काष्ठा net_device *dev);
अटल पूर्णांक scc_net_बंद(काष्ठा net_device *dev);
अटल व्योम scc_net_rx(काष्ठा scc_channel *scc, काष्ठा sk_buff *skb);
अटल netdev_tx_t scc_net_tx(काष्ठा sk_buff *skb,
			      काष्ठा net_device *dev);
अटल पूर्णांक scc_net_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd);
अटल पूर्णांक scc_net_set_mac_address(काष्ठा net_device *dev, व्योम *addr);
अटल काष्ठा net_device_stats * scc_net_get_stats(काष्ठा net_device *dev);

अटल अचिन्हित अक्षर SCC_DriverName[] = "scc";

अटल काष्ठा irqflags अणु अचिन्हित अक्षर used : 1; पूर्ण Ivec[NR_IRQS];
	
अटल काष्ठा scc_channel SCC_Info[2 * SCC_MAXCHIPS];	/* inक्रमmation per channel */

अटल काष्ठा scc_ctrl अणु
	io_port chan_A;
	io_port chan_B;
	पूर्णांक irq;
पूर्ण SCC_ctrl[SCC_MAXCHIPS+1];

अटल अचिन्हित अक्षर Driver_Initialized;
अटल पूर्णांक Nchips;
अटल io_port Vector_Latch;


/* ******************************************************************** */
/* *			Port Access Functions			      * */
/* ******************************************************************** */

/* These provide पूर्णांकerrupt save 2-step access to the Z8530 रेजिस्टरs */

अटल DEFINE_SPINLOCK(iolock);	/* Guards paired accesses */

अटल अंतरभूत अचिन्हित अक्षर InReg(io_port port, अचिन्हित अक्षर reg)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर r;

	spin_lock_irqsave(&iolock, flags);	
#अगर_घोषित SCC_LDELAY
	Outb(port, reg);
	udelay(SCC_LDELAY);
	r=Inb(port);
	udelay(SCC_LDELAY);
#अन्यथा
	Outb(port, reg);
	r=Inb(port);
#पूर्ण_अगर
	spin_unlock_irqrestore(&iolock, flags);
	वापस r;
पूर्ण

अटल अंतरभूत व्योम OutReg(io_port port, अचिन्हित अक्षर reg, अचिन्हित अक्षर val)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&iolock, flags);
#अगर_घोषित SCC_LDELAY
	Outb(port, reg); udelay(SCC_LDELAY);
	Outb(port, val); udelay(SCC_LDELAY);
#अन्यथा
	Outb(port, reg);
	Outb(port, val);
#पूर्ण_अगर
	spin_unlock_irqrestore(&iolock, flags);
पूर्ण

अटल अंतरभूत व्योम wr(काष्ठा scc_channel *scc, अचिन्हित अक्षर reg,
	अचिन्हित अक्षर val)
अणु
	OutReg(scc->ctrl, reg, (scc->wreg[reg] = val));
पूर्ण

अटल अंतरभूत व्योम or(काष्ठा scc_channel *scc, अचिन्हित अक्षर reg, अचिन्हित अक्षर val)
अणु
	OutReg(scc->ctrl, reg, (scc->wreg[reg] |= val));
पूर्ण

अटल अंतरभूत व्योम cl(काष्ठा scc_channel *scc, अचिन्हित अक्षर reg, अचिन्हित अक्षर val)
अणु
	OutReg(scc->ctrl, reg, (scc->wreg[reg] &= ~val));
पूर्ण

/* ******************************************************************** */
/* *			Some useful macros			      * */
/* ******************************************************************** */

अटल अंतरभूत व्योम scc_discard_buffers(काष्ठा scc_channel *scc)
अणु
	अचिन्हित दीर्घ flags;
	
	spin_lock_irqsave(&scc->lock, flags);	
	अगर (scc->tx_buff != शून्य)
	अणु
		dev_kमुक्त_skb(scc->tx_buff);
		scc->tx_buff = शून्य;
	पूर्ण
	
	जबतक (!skb_queue_empty(&scc->tx_queue))
		dev_kमुक्त_skb(skb_dequeue(&scc->tx_queue));

	spin_unlock_irqrestore(&scc->lock, flags);
पूर्ण



/* ******************************************************************** */
/* *			Interrupt Service Routines		      * */
/* ******************************************************************** */


/* ----> subroutines क्रम the पूर्णांकerrupt handlers <---- */

अटल अंतरभूत व्योम scc_notअगरy(काष्ठा scc_channel *scc, पूर्णांक event)
अणु
	काष्ठा sk_buff *skb;
	अक्षर *bp;
	
        अगर (scc->kiss.fulldup != KISS_DUPLEX_OPTIMA)
		वापस;

	skb = dev_alloc_skb(2);
	अगर (skb != शून्य)
	अणु
		bp = skb_put(skb, 2);
		*bp++ = PARAM_HWEVENT;
		*bp++ = event;
		scc_net_rx(scc, skb);
	पूर्ण अन्यथा
		scc->stat.nospace++;
पूर्ण

अटल अंतरभूत व्योम flush_rx_FIFO(काष्ठा scc_channel *scc)
अणु
	पूर्णांक k;
	
	क्रम (k=0; k<3; k++)
		Inb(scc->data);
		
	अगर(scc->rx_buff != शून्य)		/* did we receive something? */
	अणु
		scc->stat.rxerrs++;  /* then count it as an error */
		dev_kमुक्त_skb_irq(scc->rx_buff);
		scc->rx_buff = शून्य;
	पूर्ण
पूर्ण

अटल व्योम start_hunt(काष्ठा scc_channel *scc)
अणु
	अगर ((scc->modem.घड़ीsrc != CLK_EXTERNAL))
		OutReg(scc->ctrl,R14,SEARCH|scc->wreg[R14]); /* DPLL: enter search mode */
	or(scc,R3,ENT_HM|RxENABLE);  /* enable the receiver, hunt mode */
पूर्ण

/* ----> four dअगरferent पूर्णांकerrupt handlers क्रम Tx, Rx, changing of	*/
/*       DCD/CTS and Rx/Tx errors					*/

/* Transmitter पूर्णांकerrupt handler */
अटल अंतरभूत व्योम scc_txपूर्णांक(काष्ठा scc_channel *scc)
अणु
	काष्ठा sk_buff *skb;

	scc->stat.txपूर्णांकs++;
	skb = scc->tx_buff;
	
	/* send first octet */
	
	अगर (skb == शून्य)
	अणु
		skb = skb_dequeue(&scc->tx_queue);
		scc->tx_buff = skb;
		netअगर_wake_queue(scc->dev);

		अगर (skb == शून्य)
		अणु
			scc_tx_करोne(scc);
			Outb(scc->ctrl, RES_Tx_P);
			वापस;
		पूर्ण
		
		अगर (skb->len == 0)		/* Paranoia... */
		अणु
			dev_kमुक्त_skb_irq(skb);
			scc->tx_buff = शून्य;
			scc_tx_करोne(scc);
			Outb(scc->ctrl, RES_Tx_P);
			वापस;
		पूर्ण

		scc->stat.tx_state = TXS_ACTIVE;

		OutReg(scc->ctrl, R0, RES_Tx_CRC);
						/* reset CRC generator */
		or(scc,R10,ABUNDER);		/* re-install underrun protection */
		Outb(scc->data,*skb->data);	/* send byte */
		skb_pull(skb, 1);

		अगर (!scc->enhanced)		/* reset EOM latch */
			Outb(scc->ctrl,RES_EOM_L);
		वापस;
	पूर्ण
	
	/* End Of Frame... */
	
	अगर (skb->len == 0)
	अणु
		Outb(scc->ctrl, RES_Tx_P);	/* reset pending पूर्णांक */
		cl(scc, R10, ABUNDER);		/* send CRC */
		dev_kमुक्त_skb_irq(skb);
		scc->tx_buff = शून्य;
		scc->stat.tx_state = TXS_NEWFRAME; /* next frame... */
		वापस;
	पूर्ण 
	
	/* send octet */
	
	Outb(scc->data,*skb->data);		
	skb_pull(skb, 1);
पूर्ण


/* External/Status पूर्णांकerrupt handler */
अटल अंतरभूत व्योम scc_exपूर्णांक(काष्ठा scc_channel *scc)
अणु
	अचिन्हित अक्षर status,changes,chg_and_stat;

	scc->stat.exपूर्णांकs++;

	status = InReg(scc->ctrl,R0);
	changes = status ^ scc->status;
	chg_and_stat = changes & status;
	
	/* ABORT: generated whenever DCD drops जबतक receiving */

	अगर (chg_and_stat & BRK_ABRT)		/* Received an ABORT */
		flush_rx_FIFO(scc);

	/* HUNT: software DCD; on = रुकोing क्रम SYNC, off = receiving frame */

	अगर ((changes & SYNC_HUNT) && scc->kiss.softdcd)
	अणु
		अगर (status & SYNC_HUNT)
		अणु
			scc->dcd = 0;
			flush_rx_FIFO(scc);
			अगर ((scc->modem.घड़ीsrc != CLK_EXTERNAL))
				OutReg(scc->ctrl,R14,SEARCH|scc->wreg[R14]); /* DPLL: enter search mode */
		पूर्ण अन्यथा अणु
			scc->dcd = 1;
		पूर्ण

		scc_notअगरy(scc, scc->dcd? HWEV_DCD_OFF:HWEV_DCD_ON);
	पूर्ण

	/* DCD: on = start to receive packet, off = ABORT condition */
	/* (a successfully received packet generates a special condition पूर्णांक) */
	
	अगर((changes & DCD) && !scc->kiss.softdcd) /* DCD input changed state */
	अणु
		अगर(status & DCD)                /* DCD is now ON */
		अणु
			start_hunt(scc);
			scc->dcd = 1;
		पूर्ण अन्यथा अणु                        /* DCD is now OFF */
			cl(scc,R3,ENT_HM|RxENABLE); /* disable the receiver */
			flush_rx_FIFO(scc);
			scc->dcd = 0;
		पूर्ण
		
		scc_notअगरy(scc, scc->dcd? HWEV_DCD_ON:HWEV_DCD_OFF);
	पूर्ण

#अगर_घोषित notdef
	/* CTS: use बाह्यal TxDelay (what's that good क्रम?!)
	 * Anyway: If we _could_ use it (BayCom USCC uses CTS क्रम
	 * own purposes) we _should_ use the "autoenable" feature
	 * of the Z8530 and not this पूर्णांकerrupt...
	 */
	 
	अगर (chg_and_stat & CTS)			/* CTS is now ON */
	अणु
		अगर (scc->kiss.txdelay == 0)	/* zero TXDELAY = रुको क्रम CTS */
			scc_start_tx_समयr(scc, t_txdelay, 0);
	पूर्ण
#पूर्ण_अगर
	
	अगर (scc->stat.tx_state == TXS_ACTIVE && (status & TxEOM))
	अणु
		scc->stat.tx_under++;	  /* oops, an underrun! count 'em */
		Outb(scc->ctrl, RES_EXT_INT);	/* reset ext/status पूर्णांकerrupts */

		अगर (scc->tx_buff != शून्य)
		अणु
			dev_kमुक्त_skb_irq(scc->tx_buff);
			scc->tx_buff = शून्य;
		पूर्ण
		
		or(scc,R10,ABUNDER);
		scc_start_tx_समयr(scc, t_txdelay, 0);	/* restart transmission */
	पूर्ण
		
	scc->status = status;
	Outb(scc->ctrl,RES_EXT_INT);
पूर्ण


/* Receiver पूर्णांकerrupt handler */
अटल अंतरभूत व्योम scc_rxपूर्णांक(काष्ठा scc_channel *scc)
अणु
	काष्ठा sk_buff *skb;

	scc->stat.rxपूर्णांकs++;

	अगर((scc->wreg[5] & RTS) && scc->kiss.fulldup == KISS_DUPLEX_HALF)
	अणु
		Inb(scc->data);		/* discard अक्षर */
		or(scc,R3,ENT_HM);	/* enter hunt mode क्रम next flag */
		वापस;
	पूर्ण

	skb = scc->rx_buff;
	
	अगर (skb == शून्य)
	अणु
		skb = dev_alloc_skb(scc->stat.bufsize);
		अगर (skb == शून्य)
		अणु
			scc->dev_stat.rx_dropped++;
			scc->stat.nospace++;
			Inb(scc->data);
			or(scc, R3, ENT_HM);
			वापस;
		पूर्ण
		
		scc->rx_buff = skb;
		skb_put_u8(skb, 0);	/* KISS data */
	पूर्ण
	
	अगर (skb->len >= scc->stat.bufsize)
	अणु
#अगर_घोषित notdef
		prपूर्णांकk(KERN_DEBUG "z8530drv: oops, scc_rxint() received huge frame...\n");
#पूर्ण_अगर
		dev_kमुक्त_skb_irq(skb);
		scc->rx_buff = शून्य;
		Inb(scc->data);
		or(scc, R3, ENT_HM);
		वापस;
	पूर्ण

	skb_put_u8(skb, Inb(scc->data));
पूर्ण


/* Receive Special Condition पूर्णांकerrupt handler */
अटल अंतरभूत व्योम scc_spपूर्णांक(काष्ठा scc_channel *scc)
अणु
	अचिन्हित अक्षर status;
	काष्ठा sk_buff *skb;

	scc->stat.spपूर्णांकs++;

	status = InReg(scc->ctrl,R1);		/* पढ़ो receiver status */
	
	Inb(scc->data);				/* throw away Rx byte */
	skb = scc->rx_buff;

	अगर(status & Rx_OVR)			/* receiver overrun */
	अणु
		scc->stat.rx_over++;             /* count them */
		or(scc,R3,ENT_HM);               /* enter hunt mode क्रम next flag */
		
		अगर (skb != शून्य) 
			dev_kमुक्त_skb_irq(skb);
		scc->rx_buff = skb = शून्य;
	पूर्ण

	अगर(status & END_FR && skb != शून्य)	/* end of frame */
	अणु
		/* CRC okay, frame ends on 8 bit boundary and received something ? */
		
		अगर (!(status & CRC_ERR) && (status & 0xe) == RES8 && skb->len > 0)
		अणु
			/* ignore last received byte (first of the CRC bytes) */
			skb_trim(skb, skb->len-1);
			scc_net_rx(scc, skb);
			scc->rx_buff = शून्य;
			scc->stat.rxframes++;
		पूर्ण अन्यथा अणु				/* a bad frame */
			dev_kमुक्त_skb_irq(skb);
			scc->rx_buff = शून्य;
			scc->stat.rxerrs++;
		पूर्ण
	पूर्ण 

	Outb(scc->ctrl,ERR_RES);
पूर्ण


/* ----> पूर्णांकerrupt service routine क्रम the Z8530 <---- */

अटल व्योम scc_isr_dispatch(काष्ठा scc_channel *scc, पूर्णांक vector)
अणु
	spin_lock(&scc->lock);
	चयन (vector & VECTOR_MASK)
	अणु
		हाल TXINT: scc_txपूर्णांक(scc); अवरोध;
		हाल EXINT: scc_exपूर्णांक(scc); अवरोध;
		हाल RXINT: scc_rxपूर्णांक(scc); अवरोध;
		हाल SPINT: scc_spपूर्णांक(scc); अवरोध;
	पूर्ण
	spin_unlock(&scc->lock);
पूर्ण

/* If the card has a latch क्रम the पूर्णांकerrupt vector (like the PA0HZP card)
   use it to get the number of the chip that generated the पूर्णांक.
   If not: poll all defined chips.
 */

#घोषणा SCC_IRQTIMEOUT 30000

अटल irqवापस_t scc_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	पूर्णांक chip_irq = (दीर्घ) dev_id;
	अचिन्हित अक्षर vector;	
	काष्ठा scc_channel *scc;
	काष्ठा scc_ctrl *ctrl;
	पूर्णांक k;
	
	अगर (Vector_Latch)
	अणु
	    	क्रम(k=0; k < SCC_IRQTIMEOUT; k++)
    		अणु
			Outb(Vector_Latch, 0);      /* Generate INTACK */
        
			/* Read the vector */
			अगर((vector=Inb(Vector_Latch)) >= 16 * Nchips) अवरोध; 
			अगर (vector & 0x01) अवरोध;
        	 
		        scc=&SCC_Info[vector >> 3 ^ 0x01];
			अगर (!scc->dev) अवरोध;

			scc_isr_dispatch(scc, vector);

			OutReg(scc->ctrl,R0,RES_H_IUS);              /* Reset Highest IUS */
		पूर्ण  

		अगर (k == SCC_IRQTIMEOUT)
			prपूर्णांकk(KERN_WARNING "z8530drv: endless loop in scc_isr()?\n");

		वापस IRQ_HANDLED;
	पूर्ण

	/* Find the SCC generating the पूर्णांकerrupt by polling all attached SCCs
	 * पढ़ोing RR3A (the पूर्णांकerrupt pending रेजिस्टर)
	 */

	ctrl = SCC_ctrl;
	जबतक (ctrl->chan_A)
	अणु
		अगर (ctrl->irq != chip_irq)
		अणु
			ctrl++;
			जारी;
		पूर्ण

		scc = शून्य;
		क्रम (k = 0; InReg(ctrl->chan_A,R3) && k < SCC_IRQTIMEOUT; k++)
		अणु
			vector=InReg(ctrl->chan_B,R2);	/* Read the vector */
			अगर (vector & 0x01) अवरोध; 

			scc = &SCC_Info[vector >> 3 ^ 0x01];
		        अगर (!scc->dev) अवरोध;

			scc_isr_dispatch(scc, vector);
		पूर्ण

		अगर (k == SCC_IRQTIMEOUT)
		अणु
			prपूर्णांकk(KERN_WARNING "z8530drv: endless loop in scc_isr()?!\n");
			अवरोध;
		पूर्ण

		/* This looks weird and it is. At least the BayCom USCC करोesn't
		 * use the Interrupt Daisy Chain, thus we'll have to start
		 * all over again to be sure not to miss an पूर्णांकerrupt from 
		 * (any of) the other chip(s)...
		 * Honestly, the situation *is* braindamaged...
		 */

		अगर (scc != शून्य)
		अणु
			OutReg(scc->ctrl,R0,RES_H_IUS);
			ctrl = SCC_ctrl; 
		पूर्ण अन्यथा
			ctrl++;
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण



/* ******************************************************************** */
/* *			Init Channel					*/
/* ******************************************************************** */


/* ----> set SCC channel speed <---- */

अटल अंतरभूत व्योम set_brg(काष्ठा scc_channel *scc, अचिन्हित पूर्णांक tc)
अणु
	cl(scc,R14,BRENABL);		/* disable baudrate generator */
	wr(scc,R12,tc & 255);		/* brg rate LOW */
	wr(scc,R13,tc >> 8);   		/* brg rate HIGH */
	or(scc,R14,BRENABL);		/* enable baudrate generator */
पूर्ण

अटल अंतरभूत व्योम set_speed(काष्ठा scc_channel *scc)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&scc->lock, flags);

	अगर (scc->modem.speed > 0)	/* paranoia... */
		set_brg(scc, (अचिन्हित) (scc->घड़ी / (scc->modem.speed * 64)) - 2);
		
	spin_unlock_irqrestore(&scc->lock, flags);
पूर्ण


/* ----> initialize a SCC channel <---- */

अटल अंतरभूत व्योम init_brg(काष्ठा scc_channel *scc)
अणु
	wr(scc, R14, BRSRC);				/* BRG source = PCLK */
	OutReg(scc->ctrl, R14, SSBR|scc->wreg[R14]);	/* DPLL source = BRG */
	OutReg(scc->ctrl, R14, SNRZI|scc->wreg[R14]);	/* DPLL NRZI mode */
पूर्ण

/*
 * Initialization according to the Z8530 manual (SGS-Thomson's version):
 *
 * 1. Modes and स्थिरants
 *
 * WR9	11000000	chip reset
 * WR4	XXXXXXXX	Tx/Rx control, async or sync mode
 * WR1	0XX00X00	select W/REQ (optional)
 * WR2	XXXXXXXX	program पूर्णांकerrupt vector
 * WR3	XXXXXXX0	select Rx control
 * WR5	XXXX0XXX	select Tx control
 * WR6	XXXXXXXX	sync अक्षरacter
 * WR7	XXXXXXXX	sync अक्षरacter
 * WR9	000X0XXX	select पूर्णांकerrupt control
 * WR10	XXXXXXXX	miscellaneous control (optional)
 * WR11	XXXXXXXX	घड़ी control
 * WR12	XXXXXXXX	समय स्थिरant lower byte (optional)
 * WR13	XXXXXXXX	समय स्थिरant upper byte (optional)
 * WR14	XXXXXXX0	miscellaneous control
 * WR14	XXXSSSSS	commands (optional)
 *
 * 2. Enables
 *
 * WR14	000SSSS1	baud rate enable
 * WR3	SSSSSSS1	Rx enable
 * WR5	SSSS1SSS	Tx enable
 * WR0	10000000	reset Tx CRG (optional)
 * WR1	XSS00S00	DMA enable (optional)
 *
 * 3. Interrupt status
 *
 * WR15	XXXXXXXX	enable बाह्यal/status
 * WR0	00010000	reset बाह्यal status
 * WR0	00010000	reset बाह्यal status twice
 * WR1	SSSXXSXX	enable Rx, Tx and Ext/status
 * WR9	000SXSSS	enable master पूर्णांकerrupt enable
 *
 * 1 = set to one, 0 = reset to zero
 * X = user defined, S = same as previous init
 *
 *
 * Note that the implementation dअगरfers in some poपूर्णांकs from above scheme.
 *
 */
 
अटल व्योम init_channel(काष्ठा scc_channel *scc)
अणु
	del_समयr(&scc->tx_t);
	del_समयr(&scc->tx_wकरोg);

	disable_irq(scc->irq);

	wr(scc,R4,X1CLK|SDLC);		/* *1 घड़ी, SDLC mode */
	wr(scc,R1,0);			/* no W/REQ operation */
	wr(scc,R3,Rx8|RxCRC_ENAB);	/* RX 8 bits/अक्षर, CRC, disabled */	
	wr(scc,R5,Tx8|DTR|TxCRC_ENAB);	/* TX 8 bits/अक्षर, disabled, DTR */
	wr(scc,R6,0);			/* SDLC address zero (not used) */
	wr(scc,R7,FLAG);		/* SDLC flag value */
	wr(scc,R9,VIS);			/* vector includes status */
	wr(scc,R10,(scc->modem.nrz? NRZ : NRZI)|CRCPS|ABUNDER); /* पात on underrun, preset CRC generator, NRZ(I) */
	wr(scc,R14, 0);


/* set घड़ी sources:

   CLK_DPLL: normal halfduplex operation
   
		RxClk: use DPLL
		TxClk: use DPLL
		TRxC mode DPLL output
		
   CLK_EXTERNAL: बाह्यal घड़ीing (G3RUH or DF9IC modem)
   
  	        BayCom: 		others:
  	        
  	        TxClk = pin RTxC	TxClk = pin TRxC
  	        RxClk = pin TRxC 	RxClk = pin RTxC
  	     

   CLK_DIVIDER:
   		RxClk = use DPLL
   		TxClk = pin RTxC
   		
   		BayCom:			others:
   		pin TRxC = DPLL		pin TRxC = BRG
   		(RxClk * 1)		(RxClk * 32)
*/  

   		
	चयन(scc->modem.घड़ीsrc)
	अणु
		हाल CLK_DPLL:
			wr(scc, R11, RCDPLL|TCDPLL|TRxCOI|TRxCDP);
			init_brg(scc);
			अवरोध;

		हाल CLK_DIVIDER:
			wr(scc, R11, ((scc->bअक्रम & BAYCOM)? TRxCDP : TRxCBR) | RCDPLL|TCRTxCP|TRxCOI);
			init_brg(scc);
			अवरोध;

		हाल CLK_EXTERNAL:
			wr(scc, R11, (scc->bअक्रम & BAYCOM)? RCTRxCP|TCRTxCP : RCRTxCP|TCTRxCP);
			OutReg(scc->ctrl, R14, DISDPLL);
			अवरोध;

	पूर्ण
	
	set_speed(scc);			/* set baudrate */
	
	अगर(scc->enhanced)
	अणु
		or(scc,R15,SHDLCE|FIFOE);	/* enable FIFO, SDLC/HDLC Enhancements (From now R7 is R7') */
		wr(scc,R7,AUTOEOM);
	पूर्ण

	अगर(scc->kiss.softdcd || (InReg(scc->ctrl,R0) & DCD))
						/* DCD is now ON */
	अणु
		start_hunt(scc);
	पूर्ण
	
	/* enable ABORT, DCD & SYNC/HUNT पूर्णांकerrupts */

	wr(scc,R15, BRKIE|TxUIE|(scc->kiss.softdcd? SYNCIE:DCDIE));

	Outb(scc->ctrl,RES_EXT_INT);	/* reset ext/status पूर्णांकerrupts */
	Outb(scc->ctrl,RES_EXT_INT);	/* must be करोne twice */

	or(scc,R1,INT_ALL_Rx|TxINT_ENAB|EXT_INT_ENAB); /* enable पूर्णांकerrupts */
	
	scc->status = InReg(scc->ctrl,R0);	/* पढ़ो initial status */
	
	or(scc,R9,MIE);			/* master पूर्णांकerrupt enable */
	
	scc_init_समयr(scc);
			
	enable_irq(scc->irq);
पूर्ण




/* ******************************************************************** */
/* *			SCC समयr functions			      * */
/* ******************************************************************** */


/* ----> scc_key_trx sets the समय स्थिरant क्रम the baudrate 
         generator and keys the transmitter		     <---- */

अटल व्योम scc_key_trx(काष्ठा scc_channel *scc, अक्षर tx)
अणु
	अचिन्हित पूर्णांक समय_स्थिर;
		
	अगर (scc->bअक्रम & PRIMUS)
		Outb(scc->ctrl + 4, scc->option | (tx? 0x80 : 0));

	अगर (scc->modem.speed < 300) 
		scc->modem.speed = 1200;

	समय_स्थिर = (अचिन्हित) (scc->घड़ी / (scc->modem.speed * (tx? 2:64))) - 2;

	disable_irq(scc->irq);

	अगर (tx)
	अणु
		or(scc, R1, TxINT_ENAB);	/* t_maxkeyup may have reset these */
		or(scc, R15, TxUIE);
	पूर्ण

	अगर (scc->modem.घड़ीsrc == CLK_DPLL)
	अणु				/* क्रमce simplex operation */
		अगर (tx)
		अणु
#अगर_घोषित CONFIG_SCC_TRXECHO
			cl(scc, R3, RxENABLE|ENT_HM);	/* चयन off receiver */
			cl(scc, R15, DCDIE|SYNCIE);	/* No DCD changes, please */
#पूर्ण_अगर
			set_brg(scc, समय_स्थिर);	/* reprogram baudrate generator */

			/* DPLL -> Rx clk, BRG -> Tx CLK, TRxC mode output, TRxC = BRG */
			wr(scc, R11, RCDPLL|TCBR|TRxCOI|TRxCBR);
			
			/* By popular demand: tx_inhibit */
			अगर (scc->kiss.tx_inhibit)
			अणु
				or(scc,R5, TxENAB);
				scc->wreg[R5] |= RTS;
			पूर्ण अन्यथा अणु
				or(scc,R5,RTS|TxENAB);	/* set the RTS line and enable TX */
			पूर्ण
		पूर्ण अन्यथा अणु
			cl(scc,R5,RTS|TxENAB);
			
			set_brg(scc, समय_स्थिर);	/* reprogram baudrate generator */
			
			/* DPLL -> Rx clk, DPLL -> Tx CLK, TRxC mode output, TRxC = DPLL */
			wr(scc, R11, RCDPLL|TCDPLL|TRxCOI|TRxCDP);

#अगर_अघोषित CONFIG_SCC_TRXECHO
			अगर (scc->kiss.softdcd)
#पूर्ण_अगर
			अणु
				or(scc,R15, scc->kiss.softdcd? SYNCIE:DCDIE);
				start_hunt(scc);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (tx)
		अणु
#अगर_घोषित CONFIG_SCC_TRXECHO
			अगर (scc->kiss.fulldup == KISS_DUPLEX_HALF)
			अणु
				cl(scc, R3, RxENABLE);
				cl(scc, R15, DCDIE|SYNCIE);
			पूर्ण
#पूर्ण_अगर
				
			अगर (scc->kiss.tx_inhibit)
			अणु
				or(scc,R5, TxENAB);
				scc->wreg[R5] |= RTS;
			पूर्ण अन्यथा अणु	
				or(scc,R5,RTS|TxENAB);	/* enable tx */
			पूर्ण
		पूर्ण अन्यथा अणु
			cl(scc,R5,RTS|TxENAB);		/* disable tx */

			अगर ((scc->kiss.fulldup == KISS_DUPLEX_HALF) &&
#अगर_अघोषित CONFIG_SCC_TRXECHO
			    scc->kiss.softdcd)
#अन्यथा
			    1)
#पूर्ण_अगर
			अणु
				or(scc, R15, scc->kiss.softdcd? SYNCIE:DCDIE);
				start_hunt(scc);
			पूर्ण
		पूर्ण
	पूर्ण

	enable_irq(scc->irq);
पूर्ण


/* ----> SCC समयr पूर्णांकerrupt handler and मित्रs. <---- */

अटल व्योम __scc_start_tx_समयr(काष्ठा scc_channel *scc,
				 व्योम (*handler)(काष्ठा समयr_list *t),
				 अचिन्हित दीर्घ when)
अणु
	del_समयr(&scc->tx_t);

	अगर (when == 0)
	अणु
		handler(&scc->tx_t);
	पूर्ण अन्यथा 
	अगर (when != TIMER_OFF)
	अणु
		scc->tx_t.function = handler;
		scc->tx_t.expires = jअगरfies + (when*HZ)/100;
		add_समयr(&scc->tx_t);
	पूर्ण
पूर्ण

अटल व्योम scc_start_tx_समयr(काष्ठा scc_channel *scc,
			       व्योम (*handler)(काष्ठा समयr_list *t),
			       अचिन्हित दीर्घ when)
अणु
	अचिन्हित दीर्घ flags;
	
	spin_lock_irqsave(&scc->lock, flags);
	__scc_start_tx_समयr(scc, handler, when);
	spin_unlock_irqrestore(&scc->lock, flags);
पूर्ण

अटल व्योम scc_start_defer(काष्ठा scc_channel *scc)
अणु
	अचिन्हित दीर्घ flags;
	
	spin_lock_irqsave(&scc->lock, flags);
	del_समयr(&scc->tx_wकरोg);
	
	अगर (scc->kiss.maxdefer != 0 && scc->kiss.maxdefer != TIMER_OFF)
	अणु
		scc->tx_wकरोg.function = t_busy;
		scc->tx_wकरोg.expires = jअगरfies + HZ*scc->kiss.maxdefer;
		add_समयr(&scc->tx_wकरोg);
	पूर्ण
	spin_unlock_irqrestore(&scc->lock, flags);
पूर्ण

अटल व्योम scc_start_maxkeyup(काष्ठा scc_channel *scc)
अणु
	अचिन्हित दीर्घ flags;
	
	spin_lock_irqsave(&scc->lock, flags);
	del_समयr(&scc->tx_wकरोg);
	
	अगर (scc->kiss.maxkeyup != 0 && scc->kiss.maxkeyup != TIMER_OFF)
	अणु
		scc->tx_wकरोg.function = t_maxkeyup;
		scc->tx_wकरोg.expires = jअगरfies + HZ*scc->kiss.maxkeyup;
		add_समयr(&scc->tx_wकरोg);
	पूर्ण
	spin_unlock_irqrestore(&scc->lock, flags);
पूर्ण

/* 
 * This is called from scc_txपूर्णांक() when there are no more frames to send.
 * Not exactly a समयr function, but it is a बंद मित्र of the family...
 */

अटल व्योम scc_tx_करोne(काष्ठा scc_channel *scc)
अणु
	/* 
	 * trx reमुख्यs keyed in fulldup mode 2 until t_idle expires.
	 */
				 
	चयन (scc->kiss.fulldup)
	अणु
		हाल KISS_DUPLEX_LINK:
			scc->stat.tx_state = TXS_IDLE2;
			अगर (scc->kiss.idleसमय != TIMER_OFF)
				scc_start_tx_समयr(scc, t_idle,
						   scc->kiss.idleसमय*100);
			अवरोध;
		हाल KISS_DUPLEX_OPTIMA:
			scc_notअगरy(scc, HWEV_ALL_SENT);
			अवरोध;
		शेष:
			scc->stat.tx_state = TXS_BUSY;
			scc_start_tx_समयr(scc, t_tail, scc->kiss.tailसमय);
	पूर्ण

	netअगर_wake_queue(scc->dev);
पूर्ण


अटल अचिन्हित अक्षर Rand = 17;

अटल अंतरभूत पूर्णांक is_grouped(काष्ठा scc_channel *scc)
अणु
	पूर्णांक k;
	काष्ठा scc_channel *scc2;
	अचिन्हित अक्षर grp1, grp2;

	grp1 = scc->kiss.group;
	
	क्रम (k = 0; k < (Nchips * 2); k++)
	अणु
		scc2 = &SCC_Info[k];
		grp2 = scc2->kiss.group;
		
		अगर (scc2 == scc || !(scc2->dev && grp2))
			जारी;
		
		अगर ((grp1 & 0x3f) == (grp2 & 0x3f))
		अणु
			अगर ( (grp1 & TXGROUP) && (scc2->wreg[R5] & RTS) )
				वापस 1;
			
			अगर ( (grp1 & RXGROUP) && scc2->dcd )
				वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* DWAIT and SLOTTIME expired
 *
 * fulldup == 0:  DCD is active or Rand > P-persistence: start t_busy समयr
 *                अन्यथा key trx and start txdelay
 * fulldup == 1:  key trx and start txdelay
 * fulldup == 2:  mपूर्णांकime expired, reset status or key trx and start txdelay
 */

अटल व्योम t_dरुको(काष्ठा समयr_list *t)
अणु
	काष्ठा scc_channel *scc = from_समयr(scc, t, tx_t);
	
	अगर (scc->stat.tx_state == TXS_WAIT)	/* maxkeyup or idle समयout */
	अणु
		अगर (skb_queue_empty(&scc->tx_queue)) अणु	/* nothing to send */
			scc->stat.tx_state = TXS_IDLE;
			netअगर_wake_queue(scc->dev);	/* t_maxkeyup locked it. */
			वापस;
		पूर्ण

		scc->stat.tx_state = TXS_BUSY;
	पूर्ण

	अगर (scc->kiss.fulldup == KISS_DUPLEX_HALF)
	अणु
		Rand = Rand * 17 + 31;
		
		अगर (scc->dcd || (scc->kiss.persist) < Rand || (scc->kiss.group && is_grouped(scc)) )
		अणु
			scc_start_defer(scc);
			scc_start_tx_समयr(scc, t_dरुको, scc->kiss.slotसमय);
			वापस ;
		पूर्ण
	पूर्ण

	अगर ( !(scc->wreg[R5] & RTS) )
	अणु
		scc_key_trx(scc, TX_ON);
		scc_start_tx_समयr(scc, t_txdelay, scc->kiss.txdelay);
	पूर्ण अन्यथा अणु
		scc_start_tx_समयr(scc, t_txdelay, 0);
	पूर्ण
पूर्ण


/* TXDELAY expired
 *
 * kick transmission by a fake scc_txपूर्णांक(scc), start 'maxkeyup' watchकरोg.
 */

अटल व्योम t_txdelay(काष्ठा समयr_list *t)
अणु
	काष्ठा scc_channel *scc = from_समयr(scc, t, tx_t);

	scc_start_maxkeyup(scc);

	अगर (scc->tx_buff == शून्य)
	अणु
		disable_irq(scc->irq);
		scc_txपूर्णांक(scc);	
		enable_irq(scc->irq);
	पूर्ण
पूर्ण
	

/* TAILTIME expired
 *
 * चयन off transmitter. If we were stopped by Maxkeyup restart
 * transmission after 'mintime' seconds
 */

अटल व्योम t_tail(काष्ठा समयr_list *t)
अणु
	काष्ठा scc_channel *scc = from_समयr(scc, t, tx_t);
	अचिन्हित दीर्घ flags;
	
	spin_lock_irqsave(&scc->lock, flags); 
 	del_समयr(&scc->tx_wकरोg);	
 	scc_key_trx(scc, TX_OFF);
	spin_unlock_irqrestore(&scc->lock, flags);

 	अगर (scc->stat.tx_state == TXS_TIMEOUT)		/* we had a समयout? */
 	अणु
 		scc->stat.tx_state = TXS_WAIT;
		scc_start_tx_समयr(scc, t_dरुको, scc->kiss.mपूर्णांकime*100);
 		वापस;
 	पूर्ण
 	
 	scc->stat.tx_state = TXS_IDLE;
	netअगर_wake_queue(scc->dev);
पूर्ण


/* BUSY समयout
 *
 * throw away send buffers अगर DCD reमुख्यs active too दीर्घ.
 */

अटल व्योम t_busy(काष्ठा समयr_list *t)
अणु
	काष्ठा scc_channel *scc = from_समयr(scc, t, tx_wकरोg);

	del_समयr(&scc->tx_t);
	netअगर_stop_queue(scc->dev);	/* करोn't pile on the wabbit! */

	scc_discard_buffers(scc);
	scc->stat.txerrs++;
	scc->stat.tx_state = TXS_IDLE;

	netअगर_wake_queue(scc->dev);	
पूर्ण

/* MAXKEYUP समयout
 *
 * this is our watchकरोg.
 */

अटल व्योम t_maxkeyup(काष्ठा समयr_list *t)
अणु
	काष्ठा scc_channel *scc = from_समयr(scc, t, tx_wकरोg);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&scc->lock, flags);
	/* 
	 * let things settle करोwn beक्रमe we start to
	 * accept new data.
	 */

	netअगर_stop_queue(scc->dev);
	scc_discard_buffers(scc);

	del_समयr(&scc->tx_t);

	cl(scc, R1, TxINT_ENAB);	/* क्रमce an ABORT, but करोn't */
	cl(scc, R15, TxUIE);		/* count it. */
	OutReg(scc->ctrl, R0, RES_Tx_P);

	spin_unlock_irqrestore(&scc->lock, flags);

	scc->stat.txerrs++;
	scc->stat.tx_state = TXS_TIMEOUT;
	scc_start_tx_समयr(scc, t_tail, scc->kiss.tailसमय);
पूर्ण

/* IDLE समयout
 *
 * in fulldup mode 2 it keys करोwn the transmitter after 'idle' seconds
 * of inactivity. We will not restart transmission beक्रमe 'mintime'
 * expires.
 */

अटल व्योम t_idle(काष्ठा समयr_list *t)
अणु
	काष्ठा scc_channel *scc = from_समयr(scc, t, tx_t);
	
	del_समयr(&scc->tx_wकरोg);

	scc_key_trx(scc, TX_OFF);
	अगर(scc->kiss.mपूर्णांकime)
		scc_start_tx_समयr(scc, t_dरुको, scc->kiss.mपूर्णांकime*100);
	scc->stat.tx_state = TXS_WAIT;
पूर्ण

अटल व्योम scc_init_समयr(काष्ठा scc_channel *scc)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&scc->lock, flags);	
	scc->stat.tx_state = TXS_IDLE;
	spin_unlock_irqrestore(&scc->lock, flags);
पूर्ण


/* ******************************************************************** */
/* *			Set/get L1 parameters			      * */
/* ******************************************************************** */


/*
 * this will set the "hardware" parameters through KISS commands or ioctl()
 */

#घोषणा CAST(x) (अचिन्हित दीर्घ)(x)

अटल अचिन्हित पूर्णांक scc_set_param(काष्ठा scc_channel *scc, अचिन्हित पूर्णांक cmd, अचिन्हित पूर्णांक arg)
अणु
	चयन (cmd)
	अणु
		हाल PARAM_TXDELAY:	scc->kiss.txdelay=arg;		अवरोध;
		हाल PARAM_PERSIST:	scc->kiss.persist=arg;		अवरोध;
		हाल PARAM_SLOTTIME:	scc->kiss.slotसमय=arg;		अवरोध;
		हाल PARAM_TXTAIL:	scc->kiss.tailसमय=arg;		अवरोध;
		हाल PARAM_FULLDUP:	scc->kiss.fulldup=arg;		अवरोध;
		हाल PARAM_DTR:		अवरोध; /* करोes someone need this? */
		हाल PARAM_GROUP:	scc->kiss.group=arg;		अवरोध;
		हाल PARAM_IDLE:	scc->kiss.idleसमय=arg;		अवरोध;
		हाल PARAM_MIN:		scc->kiss.mपूर्णांकime=arg;		अवरोध;
		हाल PARAM_MAXKEY:	scc->kiss.maxkeyup=arg;		अवरोध;
		हाल PARAM_WAIT:	scc->kiss.रुकोसमय=arg;		अवरोध;
		हाल PARAM_MAXDEFER:	scc->kiss.maxdefer=arg;		अवरोध;
		हाल PARAM_TX:		scc->kiss.tx_inhibit=arg;	अवरोध;

		हाल PARAM_SOFTDCD:	
			scc->kiss.softdcd=arg;
			अगर (arg)
			अणु
				or(scc, R15, SYNCIE);
				cl(scc, R15, DCDIE);
				start_hunt(scc);
			पूर्ण अन्यथा अणु
				or(scc, R15, DCDIE);
				cl(scc, R15, SYNCIE);
			पूर्ण
			अवरोध;
				
		हाल PARAM_SPEED:
			अगर (arg < 256)
				scc->modem.speed=arg*100;
			अन्यथा
				scc->modem.speed=arg;

			अगर (scc->stat.tx_state == 0)	/* only चयन baudrate on rx... ;-) */
				set_speed(scc);
			अवरोध;
			
		हाल PARAM_RTS:	
			अगर ( !(scc->wreg[R5] & RTS) )
			अणु
				अगर (arg != TX_OFF) अणु
					scc_key_trx(scc, TX_ON);
					scc_start_tx_समयr(scc, t_txdelay, scc->kiss.txdelay);
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (arg == TX_OFF)
				अणु
					scc->stat.tx_state = TXS_BUSY;
					scc_start_tx_समयr(scc, t_tail, scc->kiss.tailसमय);
				पूर्ण
			पूर्ण
			अवरोध;
			
		हाल PARAM_HWEVENT:
			scc_notअगरy(scc, scc->dcd? HWEV_DCD_ON:HWEV_DCD_OFF);
			अवरोध;

		शेष:		वापस -EINVAL;
	पूर्ण
	
	वापस 0;
पूर्ण


 
अटल अचिन्हित दीर्घ scc_get_param(काष्ठा scc_channel *scc, अचिन्हित पूर्णांक cmd)
अणु
	चयन (cmd)
	अणु
		हाल PARAM_TXDELAY:	वापस CAST(scc->kiss.txdelay);
		हाल PARAM_PERSIST:	वापस CAST(scc->kiss.persist);
		हाल PARAM_SLOTTIME:	वापस CAST(scc->kiss.slotसमय);
		हाल PARAM_TXTAIL:	वापस CAST(scc->kiss.tailसमय);
		हाल PARAM_FULLDUP:	वापस CAST(scc->kiss.fulldup);
		हाल PARAM_SOFTDCD:	वापस CAST(scc->kiss.softdcd);
		हाल PARAM_DTR:		वापस CAST((scc->wreg[R5] & DTR)? 1:0);
		हाल PARAM_RTS:		वापस CAST((scc->wreg[R5] & RTS)? 1:0);
		हाल PARAM_SPEED:	वापस CAST(scc->modem.speed);
		हाल PARAM_GROUP:	वापस CAST(scc->kiss.group);
		हाल PARAM_IDLE:	वापस CAST(scc->kiss.idleसमय);
		हाल PARAM_MIN:		वापस CAST(scc->kiss.mपूर्णांकime);
		हाल PARAM_MAXKEY:	वापस CAST(scc->kiss.maxkeyup);
		हाल PARAM_WAIT:	वापस CAST(scc->kiss.रुकोसमय);
		हाल PARAM_MAXDEFER:	वापस CAST(scc->kiss.maxdefer);
		हाल PARAM_TX:		वापस CAST(scc->kiss.tx_inhibit);
		शेष:		वापस NO_SUCH_PARAM;
	पूर्ण

पूर्ण

#अघोषित CAST

/* ******************************************************************* */
/* *			Send calibration pattern		     * */
/* ******************************************************************* */

अटल व्योम scc_stop_calibrate(काष्ठा समयr_list *t)
अणु
	काष्ठा scc_channel *scc = from_समयr(scc, t, tx_wकरोg);
	अचिन्हित दीर्घ flags;
	
	spin_lock_irqsave(&scc->lock, flags);
	del_समयr(&scc->tx_wकरोg);
	scc_key_trx(scc, TX_OFF);
	wr(scc, R6, 0);
	wr(scc, R7, FLAG);
	Outb(scc->ctrl,RES_EXT_INT);	/* reset ext/status पूर्णांकerrupts */
	Outb(scc->ctrl,RES_EXT_INT);

	netअगर_wake_queue(scc->dev);
	spin_unlock_irqrestore(&scc->lock, flags);
पूर्ण


अटल व्योम
scc_start_calibrate(काष्ठा scc_channel *scc, पूर्णांक duration, अचिन्हित अक्षर pattern)
अणु
	अचिन्हित दीर्घ flags;
	
	spin_lock_irqsave(&scc->lock, flags);
	netअगर_stop_queue(scc->dev);
	scc_discard_buffers(scc);

	del_समयr(&scc->tx_wकरोg);

	scc->tx_wकरोg.function = scc_stop_calibrate;
	scc->tx_wकरोg.expires = jअगरfies + HZ*duration;
	add_समयr(&scc->tx_wकरोg);

	/* This करोesn't seem to work. Why not? */	
	wr(scc, R6, 0);
	wr(scc, R7, pattern);

	/* 
	 * Don't know अगर this works. 
	 * Damn, where is my Z8530 programming manual...? 
	 */

	Outb(scc->ctrl,RES_EXT_INT);	/* reset ext/status पूर्णांकerrupts */
	Outb(scc->ctrl,RES_EXT_INT);

	scc_key_trx(scc, TX_ON);
	spin_unlock_irqrestore(&scc->lock, flags);
पूर्ण

/* ******************************************************************* */
/* *		Init channel काष्ठाures, special HW, etc...	     * */
/* ******************************************************************* */

/*
 * Reset the Z8530s and setup special hardware
 */

अटल व्योम z8530_init(व्योम)
अणु
	काष्ठा scc_channel *scc;
	पूर्णांक chip, k;
	अचिन्हित दीर्घ flags;
	अक्षर *flag;


	prपूर्णांकk(KERN_INFO "Init Z8530 driver: %u channels, IRQ", Nchips*2);
	
	flag=" ";
	क्रम (k = 0; k < nr_irqs; k++)
		अगर (Ivec[k].used) 
		अणु
			prपूर्णांकk("%s%d", flag, k);
			flag=",";
		पूर्ण
	prपूर्णांकk("\n");


	/* reset and pre-init all chips in the प्रणाली */
	क्रम (chip = 0; chip < Nchips; chip++)
	अणु
		scc=&SCC_Info[2*chip];
		अगर (!scc->ctrl) जारी;

		/* Special SCC cards */

		अगर(scc->bअक्रम & EAGLE)			/* this is an EAGLE card */
			Outb(scc->special,0x08);	/* enable पूर्णांकerrupt on the board */
			
		अगर(scc->bअक्रम & (PC100 | PRIMUS))	/* this is a PC100/PRIMUS card */
			Outb(scc->special,scc->option);	/* set the MODEM mode (0x22) */

			
		/* Reset and pre-init Z8530 */

		spin_lock_irqsave(&scc->lock, flags);
				
		Outb(scc->ctrl, 0);
		OutReg(scc->ctrl,R9,FHWRES);		/* क्रमce hardware reset */
		udelay(100);				/* give it 'a bit' more समय than required */
		wr(scc, R2, chip*16);			/* पूर्णांकerrupt vector */
		wr(scc, R9, VIS);			/* vector includes status */
		spin_unlock_irqrestore(&scc->lock, flags);		
        पूर्ण

 
	Driver_Initialized = 1;
पूर्ण

/*
 * Allocate device काष्ठाure, err, instance, and रेजिस्टर driver
 */

अटल पूर्णांक scc_net_alloc(स्थिर अक्षर *name, काष्ठा scc_channel *scc)
अणु
	पूर्णांक err;
	काष्ठा net_device *dev;

	dev = alloc_netdev(0, name, NET_NAME_UNKNOWN, scc_net_setup);
	अगर (!dev) 
		वापस -ENOMEM;

	dev->ml_priv = scc;
	scc->dev = dev;
	spin_lock_init(&scc->lock);
	समयr_setup(&scc->tx_t, शून्य, 0);
	समयr_setup(&scc->tx_wकरोg, शून्य, 0);

	err = रेजिस्टर_netdevice(dev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s: can't register network device (%d)\n", 
		       name, err);
		मुक्त_netdev(dev);
		scc->dev = शून्य;
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण



/* ******************************************************************** */
/* *			    Network driver methods		      * */
/* ******************************************************************** */

अटल स्थिर काष्ठा net_device_ops scc_netdev_ops = अणु
	.nकरो_खोलो            = scc_net_खोलो,
	.nकरो_stop	     = scc_net_बंद,
	.nकरो_start_xmit	     = scc_net_tx,
	.nकरो_set_mac_address = scc_net_set_mac_address,
	.nकरो_get_stats       = scc_net_get_stats,
	.nकरो_करो_ioctl        = scc_net_ioctl,
पूर्ण;

/* ----> Initialize device <----- */

अटल व्योम scc_net_setup(काष्ठा net_device *dev)
अणु
	dev->tx_queue_len    = 16;	/* should be enough... */

	dev->netdev_ops	     = &scc_netdev_ops;
	dev->header_ops      = &ax25_header_ops;

	स_नकल(dev->broadcast, &ax25_bcast,  AX25_ADDR_LEN);
	स_नकल(dev->dev_addr,  &ax25_defaddr, AX25_ADDR_LEN);
 
	dev->flags      = 0;

	dev->type = ARPHRD_AX25;
	dev->hard_header_len = AX25_MAX_HEADER_LEN + AX25_BPQ_HEADER_LEN;
	dev->mtu = AX25_DEF_PACLEN;
	dev->addr_len = AX25_ADDR_LEN;

पूर्ण

/* ----> खोलो network device <---- */

अटल पूर्णांक scc_net_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा scc_channel *scc = (काष्ठा scc_channel *) dev->ml_priv;

 	अगर (!scc->init)
		वापस -EINVAL;

	scc->tx_buff = शून्य;
	skb_queue_head_init(&scc->tx_queue);
 
	init_channel(scc);

	netअगर_start_queue(dev);
	वापस 0;
पूर्ण

/* ----> बंद network device <---- */

अटल पूर्णांक scc_net_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा scc_channel *scc = (काष्ठा scc_channel *) dev->ml_priv;
	अचिन्हित दीर्घ flags;

	netअगर_stop_queue(dev);

	spin_lock_irqsave(&scc->lock, flags);	
	Outb(scc->ctrl,0);		/* Make sure poपूर्णांकer is written */
	wr(scc,R1,0);			/* disable पूर्णांकerrupts */
	wr(scc,R3,0);
	spin_unlock_irqrestore(&scc->lock, flags);

	del_समयr_sync(&scc->tx_t);
	del_समयr_sync(&scc->tx_wकरोg);
	
	scc_discard_buffers(scc);

	वापस 0;
पूर्ण

/* ----> receive frame, called from scc_rxपूर्णांक() <---- */

अटल व्योम scc_net_rx(काष्ठा scc_channel *scc, काष्ठा sk_buff *skb)
अणु
	अगर (skb->len == 0) अणु
		dev_kमुक्त_skb_irq(skb);
		वापस;
	पूर्ण
		
	scc->dev_stat.rx_packets++;
	scc->dev_stat.rx_bytes += skb->len;

	skb->protocol = ax25_type_trans(skb, scc->dev);
	
	netअगर_rx(skb);
पूर्ण

/* ----> transmit frame <---- */

अटल netdev_tx_t scc_net_tx(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा scc_channel *scc = (काष्ठा scc_channel *) dev->ml_priv;
	अचिन्हित दीर्घ flags;
	अक्षर kisscmd;

	अगर (skb->protocol == htons(ETH_P_IP))
		वापस ax25_ip_xmit(skb);

	अगर (skb->len > scc->stat.bufsize || skb->len < 2) अणु
		scc->dev_stat.tx_dropped++;	/* bogus frame */
		dev_kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण
	
	scc->dev_stat.tx_packets++;
	scc->dev_stat.tx_bytes += skb->len;
	scc->stat.txframes++;
	
	kisscmd = *skb->data & 0x1f;
	skb_pull(skb, 1);

	अगर (kisscmd) अणु
		scc_set_param(scc, kisscmd, *skb->data);
		dev_kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	spin_lock_irqsave(&scc->lock, flags);
		
	अगर (skb_queue_len(&scc->tx_queue) > scc->dev->tx_queue_len) अणु
		काष्ठा sk_buff *skb_del;
		skb_del = skb_dequeue(&scc->tx_queue);
		dev_kमुक्त_skb(skb_del);
	पूर्ण
	skb_queue_tail(&scc->tx_queue, skb);
	netअगर_trans_update(dev);
	

	/*
	 * Start transmission अगर the trx state is idle or
	 * t_idle hasn't expired yet. Use dरुको/persistence/slotसमय
	 * algorithm क्रम normal halfduplex operation.
	 */

	अगर(scc->stat.tx_state == TXS_IDLE || scc->stat.tx_state == TXS_IDLE2) अणु
		scc->stat.tx_state = TXS_BUSY;
		अगर (scc->kiss.fulldup == KISS_DUPLEX_HALF)
			__scc_start_tx_समयr(scc, t_dरुको, scc->kiss.रुकोसमय);
		अन्यथा
			__scc_start_tx_समयr(scc, t_dरुको, 0);
	पूर्ण
	spin_unlock_irqrestore(&scc->lock, flags);
	वापस NETDEV_TX_OK;
पूर्ण

/* ----> ioctl functions <---- */

/*
 * SIOCSCCCFG		- configure driver	arg: (काष्ठा scc_hw_config *) arg
 * SIOCSCCINI		- initialize driver	arg: ---
 * SIOCSCCCHANINI	- initialize channel	arg: (काष्ठा scc_modem *) arg
 * SIOCSCCSMEM		- set memory		arg: (काष्ठा scc_mem_config *) arg
 * SIOCSCCGKISS		- get level 1 parameter	arg: (काष्ठा scc_kiss_cmd *) arg
 * SIOCSCCSKISS		- set level 1 parameter arg: (काष्ठा scc_kiss_cmd *) arg
 * SIOCSCCGSTAT		- get driver status	arg: (काष्ठा scc_stat *) arg
 * SIOCSCCCAL		- send calib. pattern	arg: (काष्ठा scc_calibrate *) arg
 */

अटल पूर्णांक scc_net_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा scc_kiss_cmd kiss_cmd;
	काष्ठा scc_mem_config memcfg;
	काष्ठा scc_hw_config hwcfg;
	काष्ठा scc_calibrate cal;
	काष्ठा scc_channel *scc = (काष्ठा scc_channel *) dev->ml_priv;
	पूर्णांक chan;
	अचिन्हित अक्षर device_name[IFNAMSIZ];
	व्योम __user *arg = अगरr->अगरr_data;
	
	
	अगर (!Driver_Initialized)
	अणु
		अगर (cmd == SIOCSCCCFG)
		अणु
			पूर्णांक found = 1;

			अगर (!capable(CAP_SYS_RAWIO)) वापस -EPERM;
			अगर (!arg) वापस -EFAULT;

			अगर (Nchips >= SCC_MAXCHIPS) 
				वापस -EINVAL;

			अगर (copy_from_user(&hwcfg, arg, माप(hwcfg)))
				वापस -EFAULT;

			अगर (hwcfg.irq == 2) hwcfg.irq = 9;

			अगर (hwcfg.irq < 0 || hwcfg.irq >= nr_irqs)
				वापस -EINVAL;
				
			अगर (!Ivec[hwcfg.irq].used && hwcfg.irq)
			अणु
				अगर (request_irq(hwcfg.irq, scc_isr,
						0, "AX.25 SCC",
						(व्योम *)(दीर्घ) hwcfg.irq))
					prपूर्णांकk(KERN_WARNING "z8530drv: warning, cannot get IRQ %d\n", hwcfg.irq);
				अन्यथा
					Ivec[hwcfg.irq].used = 1;
			पूर्ण

			अगर (hwcfg.vector_latch && !Vector_Latch) अणु
				अगर (!request_region(hwcfg.vector_latch, 1, "scc vector latch"))
					prपूर्णांकk(KERN_WARNING "z8530drv: warning, cannot reserve vector latch port 0x%lx\n, disabled.", hwcfg.vector_latch);
				अन्यथा
					Vector_Latch = hwcfg.vector_latch;
			पूर्ण

			अगर (hwcfg.घड़ी == 0)
				hwcfg.घड़ी = SCC_DEFAULT_CLOCK;

#अगर_अघोषित SCC_DONT_CHECK

			अगर(request_region(hwcfg.ctrl_a, 1, "scc-probe"))
			अणु
				disable_irq(hwcfg.irq);
				Outb(hwcfg.ctrl_a, 0);
				OutReg(hwcfg.ctrl_a, R9, FHWRES);
				udelay(100);
				OutReg(hwcfg.ctrl_a,R13,0x55);		/* is this chip really there? */
				udelay(5);

				अगर (InReg(hwcfg.ctrl_a,R13) != 0x55)
					found = 0;
				enable_irq(hwcfg.irq);
				release_region(hwcfg.ctrl_a, 1);
			पूर्ण
			अन्यथा
				found = 0;
#पूर्ण_अगर

			अगर (found)
			अणु
				SCC_Info[2*Nchips  ].ctrl = hwcfg.ctrl_a;
				SCC_Info[2*Nchips  ].data = hwcfg.data_a;
				SCC_Info[2*Nchips  ].irq  = hwcfg.irq;
				SCC_Info[2*Nchips+1].ctrl = hwcfg.ctrl_b;
				SCC_Info[2*Nchips+1].data = hwcfg.data_b;
				SCC_Info[2*Nchips+1].irq  = hwcfg.irq;
			
				SCC_ctrl[Nchips].chan_A = hwcfg.ctrl_a;
				SCC_ctrl[Nchips].chan_B = hwcfg.ctrl_b;
				SCC_ctrl[Nchips].irq    = hwcfg.irq;
			पूर्ण


			क्रम (chan = 0; chan < 2; chan++)
			अणु
				प्र_लिखो(device_name, "%s%i", SCC_DriverName, 2*Nchips+chan);

				SCC_Info[2*Nchips+chan].special = hwcfg.special;
				SCC_Info[2*Nchips+chan].घड़ी = hwcfg.घड़ी;
				SCC_Info[2*Nchips+chan].bअक्रम = hwcfg.bअक्रम;
				SCC_Info[2*Nchips+chan].option = hwcfg.option;
				SCC_Info[2*Nchips+chan].enhanced = hwcfg.escc;

#अगर_घोषित SCC_DONT_CHECK
				prपूर्णांकk(KERN_INFO "%s: data port = 0x%3.3x  control port = 0x%3.3x\n",
					device_name, 
					SCC_Info[2*Nchips+chan].data, 
					SCC_Info[2*Nchips+chan].ctrl);

#अन्यथा
				prपूर्णांकk(KERN_INFO "%s: data port = 0x%3.3lx  control port = 0x%3.3lx -- %s\n",
					device_name,
					chan? hwcfg.data_b : hwcfg.data_a, 
					chan? hwcfg.ctrl_b : hwcfg.ctrl_a,
					found? "found" : "missing");
#पूर्ण_अगर

				अगर (found)
				अणु
					request_region(SCC_Info[2*Nchips+chan].ctrl, 1, "scc ctrl");
					request_region(SCC_Info[2*Nchips+chan].data, 1, "scc data");
					अगर (Nchips+chan != 0 &&
					    scc_net_alloc(device_name, 
							  &SCC_Info[2*Nchips+chan]))
					    वापस -EINVAL;
				पूर्ण
			पूर्ण
			
			अगर (found) Nchips++;
			
			वापस 0;
		पूर्ण
		
		अगर (cmd == SIOCSCCINI)
		अणु
			अगर (!capable(CAP_SYS_RAWIO))
				वापस -EPERM;
				
			अगर (Nchips == 0)
				वापस -EINVAL;

			z8530_init();
			वापस 0;
		पूर्ण
		
		वापस -EINVAL;	/* confuse the user */
	पूर्ण
	
	अगर (!scc->init)
	अणु
		अगर (cmd == SIOCSCCCHANINI)
		अणु
			अगर (!capable(CAP_NET_ADMIN)) वापस -EPERM;
			अगर (!arg) वापस -EINVAL;
			
			scc->stat.bufsize   = SCC_बफ_मानE;

			अगर (copy_from_user(&scc->modem, arg, माप(काष्ठा scc_modem)))
				वापस -EINVAL;
			
			/* शेष KISS Params */
		
			अगर (scc->modem.speed < 4800)
			अणु
				scc->kiss.txdelay = 36;		/* 360 ms */
				scc->kiss.persist = 42;		/* 25% persistence */			/* was 25 */
				scc->kiss.slotसमय = 16;	/* 160 ms */
				scc->kiss.tailसमय = 4;		/* minimal reasonable value */
				scc->kiss.fulldup = 0;		/* CSMA */
				scc->kiss.रुकोसमय = 50;	/* 500 ms */
				scc->kiss.maxkeyup = 10;	/* 10 s */
				scc->kiss.mपूर्णांकime = 3;		/* 3 s */
				scc->kiss.idleसमय = 30;	/* 30 s */
				scc->kiss.maxdefer = 120;	/* 2 min */
				scc->kiss.softdcd = 0;		/* hardware dcd */
			पूर्ण अन्यथा अणु
				scc->kiss.txdelay = 10;		/* 100 ms */
				scc->kiss.persist = 64;		/* 25% persistence */			/* was 25 */
				scc->kiss.slotसमय = 8;		/* 160 ms */
				scc->kiss.tailसमय = 1;		/* minimal reasonable value */
				scc->kiss.fulldup = 0;		/* CSMA */
				scc->kiss.रुकोसमय = 50;	/* 500 ms */
				scc->kiss.maxkeyup = 7;		/* 7 s */
				scc->kiss.mपूर्णांकime = 3;		/* 3 s */
				scc->kiss.idleसमय = 30;	/* 30 s */
				scc->kiss.maxdefer = 120;	/* 2 min */
				scc->kiss.softdcd = 0;		/* hardware dcd */
			पूर्ण
			
			scc->tx_buff = शून्य;
			skb_queue_head_init(&scc->tx_queue);
			scc->init = 1;
			
			वापस 0;
		पूर्ण
		
		वापस -EINVAL;
	पूर्ण
	
	चयन(cmd)
	अणु
		हाल SIOCSCCRESERVED:
			वापस -ENOIOCTLCMD;

		हाल SIOCSCCSMEM:
			अगर (!capable(CAP_SYS_RAWIO)) वापस -EPERM;
			अगर (!arg || copy_from_user(&memcfg, arg, माप(memcfg)))
				वापस -EINVAL;
			scc->stat.bufsize   = memcfg.bufsize;
			वापस 0;
		
		हाल SIOCSCCGSTAT:
			अगर (!arg || copy_to_user(arg, &scc->stat, माप(scc->stat)))
				वापस -EINVAL;
			वापस 0;
		
		हाल SIOCSCCGKISS:
			अगर (!arg || copy_from_user(&kiss_cmd, arg, माप(kiss_cmd)))
				वापस -EINVAL;
			kiss_cmd.param = scc_get_param(scc, kiss_cmd.command);
			अगर (copy_to_user(arg, &kiss_cmd, माप(kiss_cmd)))
				वापस -EINVAL;
			वापस 0;
		
		हाल SIOCSCCSKISS:
			अगर (!capable(CAP_NET_ADMIN)) वापस -EPERM;
			अगर (!arg || copy_from_user(&kiss_cmd, arg, माप(kiss_cmd)))
				वापस -EINVAL;
			वापस scc_set_param(scc, kiss_cmd.command, kiss_cmd.param);
		
		हाल SIOCSCCCAL:
			अगर (!capable(CAP_SYS_RAWIO)) वापस -EPERM;
			अगर (!arg || copy_from_user(&cal, arg, माप(cal)) || cal.समय == 0)
				वापस -EINVAL;

			scc_start_calibrate(scc, cal.समय, cal.pattern);
			वापस 0;

		शेष:
			वापस -ENOIOCTLCMD;
		
	पूर्ण
	
	वापस -EINVAL;
पूर्ण

/* ----> set पूर्णांकerface callsign <---- */

अटल पूर्णांक scc_net_set_mac_address(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा sockaddr *sa = (काष्ठा sockaddr *) addr;
	स_नकल(dev->dev_addr, sa->sa_data, dev->addr_len);
	वापस 0;
पूर्ण

/* ----> get statistics <---- */

अटल काष्ठा net_device_stats *scc_net_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा scc_channel *scc = (काष्ठा scc_channel *) dev->ml_priv;
	
	scc->dev_stat.rx_errors = scc->stat.rxerrs + scc->stat.rx_over;
	scc->dev_stat.tx_errors = scc->stat.txerrs + scc->stat.tx_under;
	scc->dev_stat.rx_fअगरo_errors = scc->stat.rx_over;
	scc->dev_stat.tx_fअगरo_errors = scc->stat.tx_under;

	वापस &scc->dev_stat;
पूर्ण

/* ******************************************************************** */
/* *		dump statistics to /proc/net/z8530drv		      * */
/* ******************************************************************** */

#अगर_घोषित CONFIG_PROC_FS

अटल अंतरभूत काष्ठा scc_channel *scc_net_seq_idx(loff_t pos)
अणु
	पूर्णांक k;

	क्रम (k = 0; k < Nchips*2; ++k) अणु
		अगर (!SCC_Info[k].init) 
			जारी;
		अगर (pos-- == 0)
			वापस &SCC_Info[k];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम *scc_net_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	वापस *pos ? scc_net_seq_idx(*pos - 1) : SEQ_START_TOKEN;
	
पूर्ण

अटल व्योम *scc_net_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	अचिन्हित k;
	काष्ठा scc_channel *scc = v;
	++*pos;
	
	क्रम (k = (v == SEQ_START_TOKEN) ? 0 : (scc - SCC_Info)+1;
	     k < Nchips*2; ++k) अणु
		अगर (SCC_Info[k].init) 
			वापस &SCC_Info[k];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम scc_net_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
पूर्ण

अटल पूर्णांक scc_net_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(seq, "z8530drv-"VERSION"\n");
	पूर्ण अन्यथा अगर (!Driver_Initialized) अणु
		seq_माला_दो(seq, "not initialized\n");
	पूर्ण अन्यथा अगर (!Nchips) अणु
		seq_माला_दो(seq, "chips missing\n");
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा scc_channel *scc = v;
		स्थिर काष्ठा scc_stat *stat = &scc->stat;
		स्थिर काष्ठा scc_kiss *kiss = &scc->kiss;


		/* dev	data ctrl irq घड़ी bअक्रम enh vector special option 
		 *	baud nrz घड़ीsrc softdcd bufsize
		 *	rxपूर्णांकs txपूर्णांकs exपूर्णांकs spपूर्णांकs
		 *	rcvd rxerrs over / xmit txerrs under / nospace bufsize
		 *	txd pers slot tail ful रुको min maxk idl defr txof grp
		 *	W ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
		 *	R ## ## XX ## ## ## ## ## XX ## ## ## ## ## ## ##
		 */

		seq_म_लिखो(seq, "%s\t%3.3lx %3.3lx %d %lu %2.2x %d %3.3lx %3.3lx %d\n",
				scc->dev->name,
				scc->data, scc->ctrl, scc->irq, scc->घड़ी, scc->bअक्रम,
				scc->enhanced, Vector_Latch, scc->special,
				scc->option);
		seq_म_लिखो(seq, "\t%lu %d %d %d %d\n",
				scc->modem.speed, scc->modem.nrz,
				scc->modem.घड़ीsrc, kiss->softdcd,
				stat->bufsize);
		seq_म_लिखो(seq, "\t%lu %lu %lu %lu\n",
				stat->rxपूर्णांकs, stat->txपूर्णांकs, stat->exपूर्णांकs, stat->spपूर्णांकs);
		seq_म_लिखो(seq, "\t%lu %lu %d / %lu %lu %d / %d %d\n",
				stat->rxframes, stat->rxerrs, stat->rx_over,
				stat->txframes, stat->txerrs, stat->tx_under,
				stat->nospace,  stat->tx_state);

#घोषणा K(x) kiss->x
		seq_म_लिखो(seq, "\t%d %d %d %d %d %d %d %d %d %d %d %d\n",
				K(txdelay), K(persist), K(slotसमय), K(tailसमय),
				K(fulldup), K(रुकोसमय), K(mपूर्णांकime), K(maxkeyup),
				K(idleसमय), K(maxdefer), K(tx_inhibit), K(group));
#अघोषित K
#अगर_घोषित SCC_DEBUG
		अणु
			पूर्णांक reg;

		seq_म_लिखो(seq, "\tW ");
			क्रम (reg = 0; reg < 16; reg++)
				seq_म_लिखो(seq, "%2.2x ", scc->wreg[reg]);
			seq_म_लिखो(seq, "\n");
			
		seq_म_लिखो(seq, "\tR %2.2x %2.2x XX ", InReg(scc->ctrl,R0), InReg(scc->ctrl,R1));
			क्रम (reg = 3; reg < 8; reg++)
				seq_म_लिखो(seq, "%2.2x ", InReg(scc->ctrl, reg));
			seq_म_लिखो(seq, "XX ");
			क्रम (reg = 9; reg < 16; reg++)
				seq_म_लिखो(seq, "%2.2x ", InReg(scc->ctrl, reg));
			seq_म_लिखो(seq, "\n");
		पूर्ण
#पूर्ण_अगर
		seq_अ_दो(seq, '\n');
	पूर्ण

        वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations scc_net_seq_ops = अणु
	.start  = scc_net_seq_start,
	.next   = scc_net_seq_next,
	.stop   = scc_net_seq_stop,
	.show   = scc_net_seq_show,
पूर्ण;
#पूर्ण_अगर /* CONFIG_PROC_FS */

 
/* ******************************************************************** */
/* * 			Init SCC driver 			      * */
/* ******************************************************************** */

अटल पूर्णांक __init scc_init_driver (व्योम)
अणु
	अक्षर devname[IFNAMSIZ];
	
	prपूर्णांकk(banner);
	
	प्र_लिखो(devname,"%s0", SCC_DriverName);
	
	rtnl_lock();
	अगर (scc_net_alloc(devname, SCC_Info)) अणु
		rtnl_unlock();
		prपूर्णांकk(KERN_ERR "z8530drv: cannot initialize module\n");
		वापस -EIO;
	पूर्ण
	rtnl_unlock();

	proc_create_seq("z8530drv", 0, init_net.proc_net, &scc_net_seq_ops);

	वापस 0;
पूर्ण

अटल व्योम __निकास scc_cleanup_driver(व्योम)
अणु
	io_port ctrl;
	पूर्णांक k;
	काष्ठा scc_channel *scc;
	काष्ठा net_device *dev;
	
	अगर (Nchips == 0 && (dev = SCC_Info[0].dev)) 
	अणु
		unरेजिस्टर_netdev(dev);
		मुक्त_netdev(dev);
	पूर्ण

	/* Guard against chip prattle */
	local_irq_disable();
	
	क्रम (k = 0; k < Nchips; k++)
		अगर ( (ctrl = SCC_ctrl[k].chan_A) )
		अणु
			Outb(ctrl, 0);
			OutReg(ctrl,R9,FHWRES);	/* क्रमce hardware reset */
			udelay(50);
		पूर्ण
		
	/* To unload the port must be बंदd so no real IRQ pending */
	क्रम (k = 0; k < nr_irqs ; k++)
		अगर (Ivec[k].used) मुक्त_irq(k, शून्य);
		
	local_irq_enable();
		
	/* Now clean up */
	क्रम (k = 0; k < Nchips*2; k++)
	अणु
		scc = &SCC_Info[k];
		अगर (scc->ctrl)
		अणु
			release_region(scc->ctrl, 1);
			release_region(scc->data, 1);
		पूर्ण
		अगर (scc->dev)
		अणु
			unरेजिस्टर_netdev(scc->dev);
			मुक्त_netdev(scc->dev);
		पूर्ण
	पूर्ण
	
		
	अगर (Vector_Latch)
		release_region(Vector_Latch, 1);

	हटाओ_proc_entry("z8530drv", init_net.proc_net);
पूर्ण

MODULE_AUTHOR("Joerg Reuter <jreuter@yaina.de>");
MODULE_DESCRIPTION("AX.25 Device Driver for Z8530 based HDLC cards");
MODULE_LICENSE("GPL");
module_init(scc_init_driver);
module_निकास(scc_cleanup_driver);
