<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 *	(c) Copyright 1998 Alan Cox <alan@lxorguk.ukuu.org.uk>
 *	(c) Copyright 2000, 2001 Red Hat Inc
 *
 *	Development of this driver was funded by Equiinet Ltd
 *			http://www.equiinet.com
 *
 *	ChangeLog:
 *
 *	Asynchronous mode dropped क्रम 2.2. For 2.5 we will attempt the
 *	unअगरication of all the Z85x30 asynchronous drivers क्रम real.
 *
 *	DMA now uses get_मुक्त_page as kदो_स्मृति buffers may span a 64K 
 *	boundary.
 *
 *	Modअगरied क्रम SMP safety and SMP locking by Alan Cox
 *					<alan@lxorguk.ukuu.org.uk>
 *
 *	Perक्रमmance
 *
 *	Z85230:
 *	Non DMA you want a 486DX50 or better to करो 64Kbits. 9600 baud
 *	X.25 is not unrealistic on all machines. DMA mode can in theory
 *	handle T1/E1 quite nicely. In practice the limit seems to be about
 *	512Kbit->1Mbit depending on motherboard.
 *
 *	Z85C30:
 *	64K will take DMA, 9600 baud X.25 should be ok.
 *
 *	Z8530:
 *	Synchronous mode without DMA is unlikely to pass about 2400 baud.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/net.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/delay.h>
#समावेश <linux/hdlc.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/gfp.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/पन.स>
#घोषणा RT_LOCK
#घोषणा RT_UNLOCK
#समावेश <linux/spinlock.h>

#समावेश "z85230.h"


/**
 *	z8530_पढ़ो_port - Architecture specअगरic पूर्णांकerface function
 *	@p: port to पढ़ो
 *
 *	Provided port access methods. The Comtrol SV11 requires no delays
 *	between accesses and uses PC I/O. Some drivers may need a 5uS delay
 *	
 *	In the दीर्घer term this should become an architecture specअगरic
 *	section so that this can become a generic driver पूर्णांकerface क्रम all
 *	platक्रमms. For now we only handle PC I/O ports with or without the
 *	dपढ़ो 5uS sanity delay.
 *
 *	The caller must hold sufficient locks to aव्योम violating the horrible
 *	5uS delay rule.
 */

अटल अंतरभूत पूर्णांक z8530_पढ़ो_port(अचिन्हित दीर्घ p)
अणु
	u8 r=inb(Z8530_PORT_OF(p));
	अगर(p&Z8530_PORT_SLEEP)	/* gcc should figure this out efficiently ! */
		udelay(5);
	वापस r;
पूर्ण

/**
 *	z8530_ग_लिखो_port - Architecture specअगरic पूर्णांकerface function
 *	@p: port to ग_लिखो
 *	@d: value to ग_लिखो
 *
 *	Write a value to a port with delays अगर need be. Note that the
 *	caller must hold locks to aव्योम पढ़ो/ग_लिखोs from other contexts
 *	violating the 5uS rule
 *
 *	In the दीर्घer term this should become an architecture specअगरic
 *	section so that this can become a generic driver पूर्णांकerface क्रम all
 *	platक्रमms. For now we only handle PC I/O ports with or without the
 *	dपढ़ो 5uS sanity delay.
 */


अटल अंतरभूत व्योम z8530_ग_लिखो_port(अचिन्हित दीर्घ p, u8 d)
अणु
	outb(d,Z8530_PORT_OF(p));
	अगर(p&Z8530_PORT_SLEEP)
		udelay(5);
पूर्ण



अटल व्योम z8530_rx_करोne(काष्ठा z8530_channel *c);
अटल व्योम z8530_tx_करोne(काष्ठा z8530_channel *c);


/**
 *	पढ़ो_zsreg - Read a रेजिस्टर from a Z85230 
 *	@c: Z8530 channel to पढ़ो from (2 per chip)
 *	@reg: Register to पढ़ो
 *	FIXME: Use a spinlock.
 *	
 *	Most of the Z8530 रेजिस्टरs are indexed off the control रेजिस्टरs.
 *	A पढ़ो is करोne by writing to the control रेजिस्टर and पढ़ोing the
 *	रेजिस्टर back.  The caller must hold the lock
 */
 
अटल अंतरभूत u8 पढ़ो_zsreg(काष्ठा z8530_channel *c, u8 reg)
अणु
	अगर(reg)
		z8530_ग_लिखो_port(c->ctrlio, reg);
	वापस z8530_पढ़ो_port(c->ctrlio);
पूर्ण

/**
 *	पढ़ो_zsdata - Read the data port of a Z8530 channel
 *	@c: The Z8530 channel to पढ़ो the data port from
 *
 *	The data port provides fast access to some things. We still
 *	have all the 5uS delays to worry about.
 */

अटल अंतरभूत u8 पढ़ो_zsdata(काष्ठा z8530_channel *c)
अणु
	u8 r;
	r=z8530_पढ़ो_port(c->dataio);
	वापस r;
पूर्ण

/**
 *	ग_लिखो_zsreg - Write to a Z8530 channel रेजिस्टर
 *	@c: The Z8530 channel
 *	@reg: Register number
 *	@val: Value to ग_लिखो
 *
 *	Write a value to an indexed रेजिस्टर. The caller must hold the lock
 *	to honour the irritating delay rules. We know about रेजिस्टर 0
 *	being fast to access.
 *
 *      Assumes c->lock is held.
 */
अटल अंतरभूत व्योम ग_लिखो_zsreg(काष्ठा z8530_channel *c, u8 reg, u8 val)
अणु
	अगर(reg)
		z8530_ग_लिखो_port(c->ctrlio, reg);
	z8530_ग_लिखो_port(c->ctrlio, val);

पूर्ण

/**
 *	ग_लिखो_zsctrl - Write to a Z8530 control रेजिस्टर
 *	@c: The Z8530 channel
 *	@val: Value to ग_लिखो
 *
 *	Write directly to the control रेजिस्टर on the Z8530
 */

अटल अंतरभूत व्योम ग_लिखो_zsctrl(काष्ठा z8530_channel *c, u8 val)
अणु
	z8530_ग_लिखो_port(c->ctrlio, val);
पूर्ण

/**
 *	ग_लिखो_zsdata - Write to a Z8530 control रेजिस्टर
 *	@c: The Z8530 channel
 *	@val: Value to ग_लिखो
 *
 *	Write directly to the data रेजिस्टर on the Z8530
 */


अटल अंतरभूत व्योम ग_लिखो_zsdata(काष्ठा z8530_channel *c, u8 val)
अणु
	z8530_ग_लिखो_port(c->dataio, val);
पूर्ण

/*
 *	Register loading parameters क्रम a dead port
 */
 
u8 z8530_dead_port[]=
अणु
	255
पूर्ण;

EXPORT_SYMBOL(z8530_dead_port);

/*
 *	Register loading parameters क्रम currently supported circuit types
 */


/*
 *	Data घड़ीed by telco end. This is the correct data क्रम the UK
 *	"kilostream" service, and most other similar services.
 */
 
u8 z8530_hdlc_kilostream[]=
अणु
	4,	SYNC_ENAB|SDLC|X1CLK,
	2,	0,	/* No vector */
	1,	0,
	3,	ENT_HM|RxCRC_ENAB|Rx8,
	5,	TxCRC_ENAB|RTS|TxENAB|Tx8|DTR,
	9,	0,		/* Disable पूर्णांकerrupts */
	6,	0xFF,
	7,	FLAG,
	10,	ABUNDER|NRZ|CRCPS,/*MARKIDLE ??*/
	11,	TCTRxCP,
	14,	DISDPLL,
	15,	DCDIE|SYNCIE|CTSIE|TxUIE|BRKIE,
	1,	EXT_INT_ENAB|TxINT_ENAB|INT_ALL_Rx,
	9,	NV|MIE|NORESET,
	255
पूर्ण;

EXPORT_SYMBOL(z8530_hdlc_kilostream);

/*
 *	As above but क्रम enhanced chips.
 */
 
u8 z8530_hdlc_kilostream_85230[]=
अणु
	4,	SYNC_ENAB|SDLC|X1CLK,
	2,	0,	/* No vector */
	1,	0,
	3,	ENT_HM|RxCRC_ENAB|Rx8,
	5,	TxCRC_ENAB|RTS|TxENAB|Tx8|DTR,
	9,	0,		/* Disable पूर्णांकerrupts */
	6,	0xFF,
	7,	FLAG,
	10,	ABUNDER|NRZ|CRCPS,	/* MARKIDLE?? */
	11,	TCTRxCP,
	14,	DISDPLL,
	15,	DCDIE|SYNCIE|CTSIE|TxUIE|BRKIE,
	1,	EXT_INT_ENAB|TxINT_ENAB|INT_ALL_Rx,
	9,	NV|MIE|NORESET,
	23,	3,		/* Extended mode AUTO TX and EOM*/
	
	255
पूर्ण;

EXPORT_SYMBOL(z8530_hdlc_kilostream_85230);

/**
 *	z8530_flush_fअगरo - Flush on chip RX FIFO
 *	@c: Channel to flush
 *
 *	Flush the receive FIFO. There is no specअगरic option क्रम this, we 
 *	blindly पढ़ो bytes and discard them. Reading when there is no data
 *	is harmless. The 8530 has a 4 byte FIFO, the 85230 has 8 bytes.
 *	
 *	All locking is handled क्रम the caller. On वापस data may still be
 *	present अगर it arrived during the flush.
 */
 
अटल व्योम z8530_flush_fअगरo(काष्ठा z8530_channel *c)
अणु
	पढ़ो_zsreg(c, R1);
	पढ़ो_zsreg(c, R1);
	पढ़ो_zsreg(c, R1);
	पढ़ो_zsreg(c, R1);
	अगर(c->dev->type==Z85230)
	अणु
		पढ़ो_zsreg(c, R1);
		पढ़ो_zsreg(c, R1);
		पढ़ो_zsreg(c, R1);
		पढ़ो_zsreg(c, R1);
	पूर्ण
पूर्ण	

/**
 *	z8530_rtsdtr - Control the outgoing DTS/RTS line
 *	@c: The Z8530 channel to control;
 *	@set: 1 to set, 0 to clear
 *
 *	Sets or clears DTR/RTS on the requested line. All locking is handled
 *	by the caller. For now we assume all boards use the actual RTS/DTR
 *	on the chip. Apparently one or two करोn't. We'll scream about them
 *	later.
 */

अटल व्योम z8530_rtsdtr(काष्ठा z8530_channel *c, पूर्णांक set)
अणु
	अगर (set)
		c->regs[5] |= (RTS | DTR);
	अन्यथा
		c->regs[5] &= ~(RTS | DTR);
	ग_लिखो_zsreg(c, R5, c->regs[5]);
पूर्ण

/**
 *	z8530_rx - Handle a PIO receive event
 *	@c: Z8530 channel to process
 *
 *	Receive handler क्रम receiving in PIO mode. This is much like the 
 *	async one but not quite the same or as complex
 *
 *	Note: Its पूर्णांकended that this handler can easily be separated from
 *	the मुख्य code to run realसमय. That'll be needed क्रम some machines
 *	(eg to ever घड़ी 64kbits on a sparc ;)).
 *
 *	The RT_LOCK macros करोn't करो anything now. Keep the code covered
 *	by them as लघु as possible in all circumstances - घड़ीs cost
 *	baud. The पूर्णांकerrupt handler is assumed to be atomic w.r.t. to
 *	other code - this is true in the RT हाल too.
 *
 *	We only cover the sync हालs क्रम this. If you want 2Mbit async
 *	करो it yourself but consider medical assistance first. This non DMA 
 *	synchronous mode is portable code. The DMA mode assumes PCI like 
 *	ISA DMA
 *
 *	Called with the device lock held
 */
 
अटल व्योम z8530_rx(काष्ठा z8530_channel *c)
अणु
	u8 ch,stat;

	जबतक(1)
	अणु
		/* FIFO empty ? */
		अगर(!(पढ़ो_zsreg(c, R0)&1))
			अवरोध;
		ch=पढ़ो_zsdata(c);
		stat=पढ़ो_zsreg(c, R1);
	
		/*
		 *	Overrun ?
		 */
		अगर(c->count < c->max)
		अणु
			*c->dptr++=ch;
			c->count++;
		पूर्ण

		अगर(stat&END_FR)
		अणु
		
			/*
			 *	Error ?
			 */
			अगर(stat&(Rx_OVR|CRC_ERR))
			अणु
				/* Rewind the buffer and वापस */
				अगर(c->skb)
					c->dptr=c->skb->data;
				c->count=0;
				अगर(stat&Rx_OVR)
				अणु
					pr_warn("%s: overrun\n", c->dev->name);
					c->rx_overrun++;
				पूर्ण
				अगर(stat&CRC_ERR)
				अणु
					c->rx_crc_err++;
					/* prपूर्णांकk("crc error\n"); */
				पूर्ण
				/* Shove the frame upstream */
			पूर्ण
			अन्यथा
			अणु
				/*
				 *	Drop the lock क्रम RX processing, or
		 		 *	there are deadlocks
		 		 */
				z8530_rx_करोne(c);
				ग_लिखो_zsctrl(c, RES_Rx_CRC);
			पूर्ण
		पूर्ण
	पूर्ण
	/*
	 *	Clear irq
	 */
	ग_लिखो_zsctrl(c, ERR_RES);
	ग_लिखो_zsctrl(c, RES_H_IUS);
पूर्ण


/**
 *	z8530_tx - Handle a PIO transmit event
 *	@c: Z8530 channel to process
 *
 *	Z8530 transmit पूर्णांकerrupt handler क्रम the PIO mode. The basic
 *	idea is to attempt to keep the FIFO fed. We fill as many bytes
 *	in as possible, its quite possible that we won't keep up with the
 *	data rate otherwise.
 */
 
अटल व्योम z8530_tx(काष्ठा z8530_channel *c)
अणु
	जबतक(c->txcount) अणु
		/* FIFO full ? */
		अगर(!(पढ़ो_zsreg(c, R0)&4))
			वापस;
		c->txcount--;
		/*
		 *	Shovel out the byte
		 */
		ग_लिखो_zsreg(c, R8, *c->tx_ptr++);
		ग_लिखो_zsctrl(c, RES_H_IUS);
		/* We are about to underflow */
		अगर(c->txcount==0)
		अणु
			ग_लिखो_zsctrl(c, RES_EOM_L);
			ग_लिखो_zsreg(c, R10, c->regs[10]&~ABUNDER);
		पूर्ण
	पूर्ण

	
	/*
	 *	End of frame TX - fire another one
	 */
	 
	ग_लिखो_zsctrl(c, RES_Tx_P);

	z8530_tx_करोne(c);	 
	ग_लिखो_zsctrl(c, RES_H_IUS);
पूर्ण

/**
 *	z8530_status - Handle a PIO status exception
 *	@chan: Z8530 channel to process
 *
 *	A status event occurred in PIO synchronous mode. There are several
 *	reasons the chip will bother us here. A transmit underrun means we
 *	failed to feed the chip fast enough and just broke a packet. A DCD
 *	change is a line up or करोwn.
 */

अटल व्योम z8530_status(काष्ठा z8530_channel *chan)
अणु
	u8 status, altered;

	status = पढ़ो_zsreg(chan, R0);
	altered = chan->status ^ status;

	chan->status = status;

	अगर (status & TxEOM) अणु
/*		prपूर्णांकk("%s: Tx underrun.\n", chan->dev->name); */
		chan->netdevice->stats.tx_fअगरo_errors++;
		ग_लिखो_zsctrl(chan, ERR_RES);
		z8530_tx_करोne(chan);
	पूर्ण

	अगर (altered & chan->dcdcheck)
	अणु
		अगर (status & chan->dcdcheck) अणु
			pr_info("%s: DCD raised\n", chan->dev->name);
			ग_लिखो_zsreg(chan, R3, chan->regs[3] | RxENABLE);
			अगर (chan->netdevice)
				netअगर_carrier_on(chan->netdevice);
		पूर्ण अन्यथा अणु
			pr_info("%s: DCD lost\n", chan->dev->name);
			ग_लिखो_zsreg(chan, R3, chan->regs[3] & ~RxENABLE);
			z8530_flush_fअगरo(chan);
			अगर (chan->netdevice)
				netअगर_carrier_off(chan->netdevice);
		पूर्ण

	पूर्ण
	ग_लिखो_zsctrl(chan, RES_EXT_INT);
	ग_लिखो_zsctrl(chan, RES_H_IUS);
पूर्ण

काष्ठा z8530_irqhandler z8530_sync = अणु
	.rx = z8530_rx,
	.tx = z8530_tx,
	.status = z8530_status,
पूर्ण;

EXPORT_SYMBOL(z8530_sync);

/**
 *	z8530_dma_rx - Handle a DMA RX event
 *	@chan: Channel to handle
 *
 *	Non bus mastering DMA पूर्णांकerfaces क्रम the Z8x30 devices. This
 *	is really pretty PC specअगरic. The DMA mode means that most receive
 *	events are handled by the DMA hardware. We get a kick here only अगर
 *	a frame ended.
 */
 
अटल व्योम z8530_dma_rx(काष्ठा z8530_channel *chan)
अणु
	अगर(chan->rxdma_on)
	अणु
		/* Special condition check only */
		u8 status;
	
		पढ़ो_zsreg(chan, R7);
		पढ़ो_zsreg(chan, R6);
		
		status=पढ़ो_zsreg(chan, R1);
	
		अगर(status&END_FR)
		अणु
			z8530_rx_करोne(chan);	/* Fire up the next one */
		पूर्ण		
		ग_लिखो_zsctrl(chan, ERR_RES);
		ग_लिखो_zsctrl(chan, RES_H_IUS);
	पूर्ण
	अन्यथा
	अणु
		/* DMA is off right now, drain the slow way */
		z8530_rx(chan);
	पूर्ण	
पूर्ण

/**
 *	z8530_dma_tx - Handle a DMA TX event
 *	@chan:	The Z8530 channel to handle
 *
 *	We have received an पूर्णांकerrupt जबतक करोing DMA transmissions. It
 *	shouldn't happen. Scream loudly अगर it करोes.
 */
 
अटल व्योम z8530_dma_tx(काष्ठा z8530_channel *chan)
अणु
	अगर(!chan->dma_tx)
	अणु
		pr_warn("Hey who turned the DMA off?\n");
		z8530_tx(chan);
		वापस;
	पूर्ण
	/* This shouldn't occur in DMA mode */
	pr_err("DMA tx - bogus event!\n");
	z8530_tx(chan);
पूर्ण

/**
 *	z8530_dma_status - Handle a DMA status exception
 *	@chan: Z8530 channel to process
 *	
 *	A status event occurred on the Z8530. We receive these क्रम two reasons
 *	when in DMA mode. Firstly अगर we finished a packet transfer we get one
 *	and kick the next packet out. Secondly we may see a DCD change.
 *
 */
 
अटल व्योम z8530_dma_status(काष्ठा z8530_channel *chan)
अणु
	u8 status, altered;

	status=पढ़ो_zsreg(chan, R0);
	altered=chan->status^status;
	
	chan->status=status;


	अगर(chan->dma_tx)
	अणु
		अगर(status&TxEOM)
		अणु
			अचिन्हित दीर्घ flags;
	
			flags=claim_dma_lock();
			disable_dma(chan->txdma);
			clear_dma_ff(chan->txdma);	
			chan->txdma_on=0;
			release_dma_lock(flags);
			z8530_tx_करोne(chan);
		पूर्ण
	पूर्ण

	अगर (altered & chan->dcdcheck)
	अणु
		अगर (status & chan->dcdcheck) अणु
			pr_info("%s: DCD raised\n", chan->dev->name);
			ग_लिखो_zsreg(chan, R3, chan->regs[3] | RxENABLE);
			अगर (chan->netdevice)
				netअगर_carrier_on(chan->netdevice);
		पूर्ण अन्यथा अणु
			pr_info("%s: DCD lost\n", chan->dev->name);
			ग_लिखो_zsreg(chan, R3, chan->regs[3] & ~RxENABLE);
			z8530_flush_fअगरo(chan);
			अगर (chan->netdevice)
				netअगर_carrier_off(chan->netdevice);
		पूर्ण
	पूर्ण

	ग_लिखो_zsctrl(chan, RES_EXT_INT);
	ग_लिखो_zsctrl(chan, RES_H_IUS);
पूर्ण

अटल काष्ठा z8530_irqhandler z8530_dma_sync = अणु
	.rx = z8530_dma_rx,
	.tx = z8530_dma_tx,
	.status = z8530_dma_status,
पूर्ण;

अटल काष्ठा z8530_irqhandler z8530_txdma_sync = अणु
	.rx = z8530_rx,
	.tx = z8530_dma_tx,
	.status = z8530_dma_status,
पूर्ण;

/**
 *	z8530_rx_clear - Handle RX events from a stopped chip
 *	@c: Z8530 channel to shut up
 *
 *	Receive पूर्णांकerrupt vectors क्रम a Z8530 that is in 'parked' mode.
 *	For machines with PCI Z85x30 cards, or level triggered पूर्णांकerrupts
 *	(eg the MacII) we must clear the पूर्णांकerrupt cause or die.
 */


अटल व्योम z8530_rx_clear(काष्ठा z8530_channel *c)
अणु
	/*
	 *	Data and status bytes
	 */
	u8 stat;

	पढ़ो_zsdata(c);
	stat=पढ़ो_zsreg(c, R1);
	
	अगर(stat&END_FR)
		ग_लिखो_zsctrl(c, RES_Rx_CRC);
	/*
	 *	Clear irq
	 */
	ग_लिखो_zsctrl(c, ERR_RES);
	ग_लिखो_zsctrl(c, RES_H_IUS);
पूर्ण

/**
 *	z8530_tx_clear - Handle TX events from a stopped chip
 *	@c: Z8530 channel to shut up
 *
 *	Transmit पूर्णांकerrupt vectors क्रम a Z8530 that is in 'parked' mode.
 *	For machines with PCI Z85x30 cards, or level triggered पूर्णांकerrupts
 *	(eg the MacII) we must clear the पूर्णांकerrupt cause or die.
 */

अटल व्योम z8530_tx_clear(काष्ठा z8530_channel *c)
अणु
	ग_लिखो_zsctrl(c, RES_Tx_P);
	ग_लिखो_zsctrl(c, RES_H_IUS);
पूर्ण

/**
 *	z8530_status_clear - Handle status events from a stopped chip
 *	@chan: Z8530 channel to shut up
 *
 *	Status पूर्णांकerrupt vectors क्रम a Z8530 that is in 'parked' mode.
 *	For machines with PCI Z85x30 cards, or level triggered पूर्णांकerrupts
 *	(eg the MacII) we must clear the पूर्णांकerrupt cause or die.
 */

अटल व्योम z8530_status_clear(काष्ठा z8530_channel *chan)
अणु
	u8 status=पढ़ो_zsreg(chan, R0);
	अगर(status&TxEOM)
		ग_लिखो_zsctrl(chan, ERR_RES);
	ग_लिखो_zsctrl(chan, RES_EXT_INT);
	ग_लिखो_zsctrl(chan, RES_H_IUS);
पूर्ण

काष्ठा z8530_irqhandler z8530_nop = अणु
	.rx = z8530_rx_clear,
	.tx = z8530_tx_clear,
	.status = z8530_status_clear,
पूर्ण;


EXPORT_SYMBOL(z8530_nop);

/**
 *	z8530_पूर्णांकerrupt - Handle an पूर्णांकerrupt from a Z8530
 *	@irq: 	Interrupt number
 *	@dev_id: The Z8530 device that is पूर्णांकerrupting.
 *
 *	A Z85[2]30 device has stuck its hand in the air क्रम attention.
 *	We scan both the channels on the chip क्रम events and then call
 *	the channel specअगरic call backs क्रम each channel that has events.
 *	We have to use callback functions because the two channels can be
 *	in dअगरferent modes.
 *
 *	Locking is करोne क्रम the handlers. Note that locking is करोne
 *	at the chip level (the 5uS delay issue is per chip not per
 *	channel). c->lock क्रम both channels poपूर्णांकs to dev->lock
 */

irqवापस_t z8530_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा z8530_dev *dev=dev_id;
	u8 पूर्णांकr;
	अटल अस्थिर पूर्णांक locker=0;
	पूर्णांक work=0;
	काष्ठा z8530_irqhandler *irqs;
	
	अगर(locker)
	अणु
		pr_err("IRQ re-enter\n");
		वापस IRQ_NONE;
	पूर्ण
	locker=1;

	spin_lock(&dev->lock);

	जबतक(++work<5000)
	अणु

		पूर्णांकr = पढ़ो_zsreg(&dev->chanA, R3);
		अगर(!(पूर्णांकr & (CHARxIP|CHATxIP|CHAEXT|CHBRxIP|CHBTxIP|CHBEXT)))
			अवरोध;
	
		/* This holds the IRQ status. On the 8530 you must पढ़ो it from chan 
		   A even though it applies to the whole chip */
		
		/* Now walk the chip and see what it is wanting - it may be
		   an IRQ क्रम someone अन्यथा remember */
		   
		irqs=dev->chanA.irqs;

		अगर(पूर्णांकr & (CHARxIP|CHATxIP|CHAEXT))
		अणु
			अगर(पूर्णांकr&CHARxIP)
				irqs->rx(&dev->chanA);
			अगर(पूर्णांकr&CHATxIP)
				irqs->tx(&dev->chanA);
			अगर(पूर्णांकr&CHAEXT)
				irqs->status(&dev->chanA);
		पूर्ण

		irqs=dev->chanB.irqs;

		अगर(पूर्णांकr & (CHBRxIP|CHBTxIP|CHBEXT))
		अणु
			अगर(पूर्णांकr&CHBRxIP)
				irqs->rx(&dev->chanB);
			अगर(पूर्णांकr&CHBTxIP)
				irqs->tx(&dev->chanB);
			अगर(पूर्णांकr&CHBEXT)
				irqs->status(&dev->chanB);
		पूर्ण
	पूर्ण
	spin_unlock(&dev->lock);
	अगर(work==5000)
		pr_err("%s: interrupt jammed - abort(0x%X)!\n",
		       dev->name, पूर्णांकr);
	/* Ok all करोne */
	locker=0;
	वापस IRQ_HANDLED;
पूर्ण

EXPORT_SYMBOL(z8530_पूर्णांकerrupt);

अटल स्थिर u8 reg_init[16]=
अणु
	0,0,0,0,
	0,0,0,0,
	0,0,0,0,
	0x55,0,0,0
पूर्ण;


/**
 *	z8530_sync_खोलो - Open a Z8530 channel क्रम PIO
 *	@dev:	The network पूर्णांकerface we are using
 *	@c:	The Z8530 channel to खोलो in synchronous PIO mode
 *
 *	Switch a Z8530 पूर्णांकo synchronous mode without DMA assist. We
 *	उठाओ the RTS/DTR and commence network operation.
 */
 
पूर्णांक z8530_sync_खोलो(काष्ठा net_device *dev, काष्ठा z8530_channel *c)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(c->lock, flags);

	c->sync = 1;
	c->mtu = dev->mtu+64;
	c->count = 0;
	c->skb = शून्य;
	c->skb2 = शून्य;
	c->irqs = &z8530_sync;

	/* This loads the द्विगुन buffer up */
	z8530_rx_करोne(c);	/* Load the frame ring */
	z8530_rx_करोne(c);	/* Load the backup frame */
	z8530_rtsdtr(c,1);
	c->dma_tx = 0;
	c->regs[R1]|=TxINT_ENAB;
	ग_लिखो_zsreg(c, R1, c->regs[R1]);
	ग_लिखो_zsreg(c, R3, c->regs[R3]|RxENABLE);

	spin_unlock_irqrestore(c->lock, flags);
	वापस 0;
पूर्ण


EXPORT_SYMBOL(z8530_sync_खोलो);

/**
 *	z8530_sync_बंद - Close a PIO Z8530 channel
 *	@dev: Network device to बंद
 *	@c: Z8530 channel to disassociate and move to idle
 *
 *	Close करोwn a Z8530 पूर्णांकerface and चयन its पूर्णांकerrupt handlers
 *	to discard future events.
 */
 
पूर्णांक z8530_sync_बंद(काष्ठा net_device *dev, काष्ठा z8530_channel *c)
अणु
	u8 chk;
	अचिन्हित दीर्घ flags;
	
	spin_lock_irqsave(c->lock, flags);
	c->irqs = &z8530_nop;
	c->max = 0;
	c->sync = 0;
	
	chk=पढ़ो_zsreg(c,R0);
	ग_लिखो_zsreg(c, R3, c->regs[R3]);
	z8530_rtsdtr(c,0);

	spin_unlock_irqrestore(c->lock, flags);
	वापस 0;
पूर्ण

EXPORT_SYMBOL(z8530_sync_बंद);

/**
 *	z8530_sync_dma_खोलो - Open a Z8530 क्रम DMA I/O
 *	@dev: The network device to attach
 *	@c: The Z8530 channel to configure in sync DMA mode.
 *
 *	Set up a Z85x30 device क्रम synchronous DMA in both directions. Two
 *	ISA DMA channels must be available क्रम this to work. We assume ISA
 *	DMA driven I/O and PC limits on access.
 */
 
पूर्णांक z8530_sync_dma_खोलो(काष्ठा net_device *dev, काष्ठा z8530_channel *c)
अणु
	अचिन्हित दीर्घ cflags, dflags;
	
	c->sync = 1;
	c->mtu = dev->mtu+64;
	c->count = 0;
	c->skb = शून्य;
	c->skb2 = शून्य;
	/*
	 *	Load the DMA पूर्णांकerfaces up
	 */
	c->rxdma_on = 0;
	c->txdma_on = 0;
	
	/*
	 *	Allocate the DMA flip buffers. Limit by page size.
	 *	Everyone runs 1500 mtu or less on wan links so this
	 *	should be fine.
	 */
	 
	अगर(c->mtu  > PAGE_SIZE/2)
		वापस -EMSGSIZE;
	 
	c->rx_buf[0]=(व्योम *)get_zeroed_page(GFP_KERNEL|GFP_DMA);
	अगर(c->rx_buf[0]==शून्य)
		वापस -ENOBUFS;
	c->rx_buf[1]=c->rx_buf[0]+PAGE_SIZE/2;
	
	c->tx_dma_buf[0]=(व्योम *)get_zeroed_page(GFP_KERNEL|GFP_DMA);
	अगर(c->tx_dma_buf[0]==शून्य)
	अणु
		मुक्त_page((अचिन्हित दीर्घ)c->rx_buf[0]);
		c->rx_buf[0]=शून्य;
		वापस -ENOBUFS;
	पूर्ण
	c->tx_dma_buf[1]=c->tx_dma_buf[0]+PAGE_SIZE/2;

	c->tx_dma_used=0;
	c->dma_tx = 1;
	c->dma_num=0;
	c->dma_पढ़ोy=1;
	
	/*
	 *	Enable DMA control mode
	 */

	spin_lock_irqsave(c->lock, cflags);
	 
	/*
	 *	TX DMA via सूची/REQ
	 */
	 
	c->regs[R14]|= DTRREQ;
	ग_लिखो_zsreg(c, R14, c->regs[R14]);     

	c->regs[R1]&= ~TxINT_ENAB;
	ग_लिखो_zsreg(c, R1, c->regs[R1]);
	
	/*
	 *	RX DMA via W/Req
	 */	 

	c->regs[R1]|= WT_FN_RDYFN;
	c->regs[R1]|= WT_RDY_RT;
	c->regs[R1]|= INT_ERR_Rx;
	c->regs[R1]&= ~TxINT_ENAB;
	ग_लिखो_zsreg(c, R1, c->regs[R1]);
	c->regs[R1]|= WT_RDY_ENAB;
	ग_लिखो_zsreg(c, R1, c->regs[R1]);            
	
	/*
	 *	DMA पूर्णांकerrupts
	 */
	 
	/*
	 *	Set up the DMA configuration
	 */	
	 
	dflags=claim_dma_lock();
	 
	disable_dma(c->rxdma);
	clear_dma_ff(c->rxdma);
	set_dma_mode(c->rxdma, DMA_MODE_READ|0x10);
	set_dma_addr(c->rxdma, virt_to_bus(c->rx_buf[0]));
	set_dma_count(c->rxdma, c->mtu);
	enable_dma(c->rxdma);

	disable_dma(c->txdma);
	clear_dma_ff(c->txdma);
	set_dma_mode(c->txdma, DMA_MODE_WRITE);
	disable_dma(c->txdma);
	
	release_dma_lock(dflags);
	
	/*
	 *	Select the DMA पूर्णांकerrupt handlers
	 */

	c->rxdma_on = 1;
	c->txdma_on = 1;
	c->tx_dma_used = 1;
	 
	c->irqs = &z8530_dma_sync;
	z8530_rtsdtr(c,1);
	ग_लिखो_zsreg(c, R3, c->regs[R3]|RxENABLE);

	spin_unlock_irqrestore(c->lock, cflags);
	
	वापस 0;
पूर्ण

EXPORT_SYMBOL(z8530_sync_dma_खोलो);

/**
 *	z8530_sync_dma_बंद - Close करोwn DMA I/O
 *	@dev: Network device to detach
 *	@c: Z8530 channel to move पूर्णांकo discard mode
 *
 *	Shut करोwn a DMA mode synchronous पूर्णांकerface. Halt the DMA, and
 *	मुक्त the buffers.
 */
 
पूर्णांक z8530_sync_dma_बंद(काष्ठा net_device *dev, काष्ठा z8530_channel *c)
अणु
	u8 chk;
	अचिन्हित दीर्घ flags;
	
	c->irqs = &z8530_nop;
	c->max = 0;
	c->sync = 0;
	
	/*
	 *	Disable the PC DMA channels
	 */
	
	flags=claim_dma_lock(); 
	disable_dma(c->rxdma);
	clear_dma_ff(c->rxdma);
	
	c->rxdma_on = 0;
	
	disable_dma(c->txdma);
	clear_dma_ff(c->txdma);
	release_dma_lock(flags);
	
	c->txdma_on = 0;
	c->tx_dma_used = 0;

	spin_lock_irqsave(c->lock, flags);

	/*
	 *	Disable DMA control mode
	 */
	 
	c->regs[R1]&= ~WT_RDY_ENAB;
	ग_लिखो_zsreg(c, R1, c->regs[R1]);            
	c->regs[R1]&= ~(WT_RDY_RT|WT_FN_RDYFN|INT_ERR_Rx);
	c->regs[R1]|= INT_ALL_Rx;
	ग_लिखो_zsreg(c, R1, c->regs[R1]);
	c->regs[R14]&= ~DTRREQ;
	ग_लिखो_zsreg(c, R14, c->regs[R14]);   
	
	अगर(c->rx_buf[0])
	अणु
		मुक्त_page((अचिन्हित दीर्घ)c->rx_buf[0]);
		c->rx_buf[0]=शून्य;
	पूर्ण
	अगर(c->tx_dma_buf[0])
	अणु
		मुक्त_page((अचिन्हित  दीर्घ)c->tx_dma_buf[0]);
		c->tx_dma_buf[0]=शून्य;
	पूर्ण
	chk=पढ़ो_zsreg(c,R0);
	ग_लिखो_zsreg(c, R3, c->regs[R3]);
	z8530_rtsdtr(c,0);

	spin_unlock_irqrestore(c->lock, flags);

	वापस 0;
पूर्ण

EXPORT_SYMBOL(z8530_sync_dma_बंद);

/**
 *	z8530_sync_txdma_खोलो - Open a Z8530 क्रम TX driven DMA
 *	@dev: The network device to attach
 *	@c: The Z8530 channel to configure in sync DMA mode.
 *
 *	Set up a Z85x30 device क्रम synchronous DMA transmission. One
 *	ISA DMA channel must be available क्रम this to work. The receive
 *	side is run in PIO mode, but then it has the bigger FIFO.
 */

पूर्णांक z8530_sync_txdma_खोलो(काष्ठा net_device *dev, काष्ठा z8530_channel *c)
अणु
	अचिन्हित दीर्घ cflags, dflags;

	prपूर्णांकk("Opening sync interface for TX-DMA\n");
	c->sync = 1;
	c->mtu = dev->mtu+64;
	c->count = 0;
	c->skb = शून्य;
	c->skb2 = शून्य;
	
	/*
	 *	Allocate the DMA flip buffers. Limit by page size.
	 *	Everyone runs 1500 mtu or less on wan links so this
	 *	should be fine.
	 */
	 
	अगर(c->mtu  > PAGE_SIZE/2)
		वापस -EMSGSIZE;
	 
	c->tx_dma_buf[0]=(व्योम *)get_zeroed_page(GFP_KERNEL|GFP_DMA);
	अगर(c->tx_dma_buf[0]==शून्य)
		वापस -ENOBUFS;

	c->tx_dma_buf[1] = c->tx_dma_buf[0] + PAGE_SIZE/2;


	spin_lock_irqsave(c->lock, cflags);

	/*
	 *	Load the PIO receive ring
	 */

	z8530_rx_करोne(c);
	z8530_rx_करोne(c);

 	/*
	 *	Load the DMA पूर्णांकerfaces up
	 */

	c->rxdma_on = 0;
	c->txdma_on = 0;
	
	c->tx_dma_used=0;
	c->dma_num=0;
	c->dma_पढ़ोy=1;
	c->dma_tx = 1;

 	/*
	 *	Enable DMA control mode
	 */

 	/*
	 *	TX DMA via सूची/REQ
 	 */
	c->regs[R14]|= DTRREQ;
	ग_लिखो_zsreg(c, R14, c->regs[R14]);     
	
	c->regs[R1]&= ~TxINT_ENAB;
	ग_लिखो_zsreg(c, R1, c->regs[R1]);
	
	/*
	 *	Set up the DMA configuration
	 */	
	 
	dflags = claim_dma_lock();

	disable_dma(c->txdma);
	clear_dma_ff(c->txdma);
	set_dma_mode(c->txdma, DMA_MODE_WRITE);
	disable_dma(c->txdma);

	release_dma_lock(dflags);
	
	/*
	 *	Select the DMA पूर्णांकerrupt handlers
	 */

	c->rxdma_on = 0;
	c->txdma_on = 1;
	c->tx_dma_used = 1;
	 
	c->irqs = &z8530_txdma_sync;
	z8530_rtsdtr(c,1);
	ग_लिखो_zsreg(c, R3, c->regs[R3]|RxENABLE);
	spin_unlock_irqrestore(c->lock, cflags);
	
	वापस 0;
पूर्ण

EXPORT_SYMBOL(z8530_sync_txdma_खोलो);

/**
 *	z8530_sync_txdma_बंद - Close करोwn a TX driven DMA channel
 *	@dev: Network device to detach
 *	@c: Z8530 channel to move पूर्णांकo discard mode
 *
 *	Shut करोwn a DMA/PIO split mode synchronous पूर्णांकerface. Halt the DMA, 
 *	and  मुक्त the buffers.
 */

पूर्णांक z8530_sync_txdma_बंद(काष्ठा net_device *dev, काष्ठा z8530_channel *c)
अणु
	अचिन्हित दीर्घ dflags, cflags;
	u8 chk;

	
	spin_lock_irqsave(c->lock, cflags);
	
	c->irqs = &z8530_nop;
	c->max = 0;
	c->sync = 0;
	
	/*
	 *	Disable the PC DMA channels
	 */
	 
	dflags = claim_dma_lock();

	disable_dma(c->txdma);
	clear_dma_ff(c->txdma);
	c->txdma_on = 0;
	c->tx_dma_used = 0;

	release_dma_lock(dflags);

	/*
	 *	Disable DMA control mode
	 */
	 
	c->regs[R1]&= ~WT_RDY_ENAB;
	ग_लिखो_zsreg(c, R1, c->regs[R1]);            
	c->regs[R1]&= ~(WT_RDY_RT|WT_FN_RDYFN|INT_ERR_Rx);
	c->regs[R1]|= INT_ALL_Rx;
	ग_लिखो_zsreg(c, R1, c->regs[R1]);
	c->regs[R14]&= ~DTRREQ;
	ग_लिखो_zsreg(c, R14, c->regs[R14]);   
	
	अगर(c->tx_dma_buf[0])
	अणु
		मुक्त_page((अचिन्हित दीर्घ)c->tx_dma_buf[0]);
		c->tx_dma_buf[0]=शून्य;
	पूर्ण
	chk=पढ़ो_zsreg(c,R0);
	ग_लिखो_zsreg(c, R3, c->regs[R3]);
	z8530_rtsdtr(c,0);

	spin_unlock_irqrestore(c->lock, cflags);
	वापस 0;
पूर्ण


EXPORT_SYMBOL(z8530_sync_txdma_बंद);


/*
 *	Name strings क्रम Z8530 chips. SGI claim to have a 130, Zilog deny
 *	it exists...
 */
 
अटल स्थिर अक्षर *z8530_type_name[]=अणु
	"Z8530",
	"Z85C30",
	"Z85230"
पूर्ण;

/**
 *	z8530_describe - Unअगरormly describe a Z8530 port
 *	@dev: Z8530 device to describe
 *	@mapping: string holding mapping type (eg "I/O" or "Mem")
 *	@io: the port value in question
 *
 *	Describe a Z8530 in a standard क्रमmat. We must pass the I/O as
 *	the port offset isn't predictable. The मुख्य reason क्रम this function
 *	is to try and get a common क्रमmat of report.
 */

व्योम z8530_describe(काष्ठा z8530_dev *dev, अक्षर *mapping, अचिन्हित दीर्घ io)
अणु
	pr_info("%s: %s found at %s 0x%lX, IRQ %d\n",
		dev->name, 
		z8530_type_name[dev->type],
		mapping,
		Z8530_PORT_OF(io),
		dev->irq);
पूर्ण

EXPORT_SYMBOL(z8530_describe);

/*
 *	Locked operation part of the z8530 init code
 */
 
अटल अंतरभूत पूर्णांक करो_z8530_init(काष्ठा z8530_dev *dev)
अणु
	/* NOP the पूर्णांकerrupt handlers first - we might get a
	   भग्नing IRQ transition when we reset the chip */
	dev->chanA.irqs=&z8530_nop;
	dev->chanB.irqs=&z8530_nop;
	dev->chanA.dcdcheck=DCD;
	dev->chanB.dcdcheck=DCD;

	/* Reset the chip */
	ग_लिखो_zsreg(&dev->chanA, R9, 0xC0);
	udelay(200);
	/* Now check its valid */
	ग_लिखो_zsreg(&dev->chanA, R12, 0xAA);
	अगर(पढ़ो_zsreg(&dev->chanA, R12)!=0xAA)
		वापस -ENODEV;
	ग_लिखो_zsreg(&dev->chanA, R12, 0x55);
	अगर(पढ़ो_zsreg(&dev->chanA, R12)!=0x55)
		वापस -ENODEV;
		
	dev->type=Z8530;
	
	/*
	 *	See the application note.
	 */
	 
	ग_लिखो_zsreg(&dev->chanA, R15, 0x01);
	
	/*
	 *	If we can set the low bit of R15 then
	 *	the chip is enhanced.
	 */
	 
	अगर(पढ़ो_zsreg(&dev->chanA, R15)==0x01)
	अणु
		/* This C30 versus 230 detect is from Klaus Kudielka's dmascc */
		/* Put a अक्षर in the fअगरo */
		ग_लिखो_zsreg(&dev->chanA, R8, 0);
		अगर(पढ़ो_zsreg(&dev->chanA, R0)&Tx_BUF_EMP)
			dev->type = Z85230;	/* Has a FIFO */
		अन्यथा
			dev->type = Z85C30;	/* Z85C30, 1 byte FIFO */
	पूर्ण
		
	/*
	 *	The code assumes R7' and मित्रs are
	 *	off. Use ग_लिखो_zsext() क्रम these and keep
	 *	this bit clear.
	 */
	 
	ग_लिखो_zsreg(&dev->chanA, R15, 0);
		
	/*
	 *	At this poपूर्णांक it looks like the chip is behaving
	 */
	 
	स_नकल(dev->chanA.regs, reg_init, 16);
	स_नकल(dev->chanB.regs, reg_init ,16);
	
	वापस 0;
पूर्ण

/**
 *	z8530_init - Initialise a Z8530 device
 *	@dev: Z8530 device to initialise.
 *
 *	Configure up a Z8530/Z85C30 or Z85230 chip. We check the device
 *	is present, identअगरy the type and then program it to hopefully
 *	keep quite and behave. This matters a lot, a Z8530 in the wrong
 *	state will someबार get पूर्णांकo stupid modes generating 10Khz
 *	पूर्णांकerrupt streams and the like.
 *
 *	We set the पूर्णांकerrupt handler up to discard any events, in हाल
 *	we get them during reset or setp.
 *
 *	Return 0 क्रम success, or a negative value indicating the problem
 *	in त्रुटि_सं क्रमm.
 */

पूर्णांक z8530_init(काष्ठा z8530_dev *dev)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/* Set up the chip level lock */
	spin_lock_init(&dev->lock);
	dev->chanA.lock = &dev->lock;
	dev->chanB.lock = &dev->lock;

	spin_lock_irqsave(&dev->lock, flags);
	ret = करो_z8530_init(dev);
	spin_unlock_irqrestore(&dev->lock, flags);

	वापस ret;
पूर्ण


EXPORT_SYMBOL(z8530_init);

/**
 *	z8530_shutकरोwn - Shutकरोwn a Z8530 device
 *	@dev: The Z8530 chip to shutकरोwn
 *
 *	We set the पूर्णांकerrupt handlers to silence any पूर्णांकerrupts. We then 
 *	reset the chip and रुको 100uS to be sure the reset completed. Just
 *	in हाल the caller then tries to करो stuff.
 *
 *	This is called without the lock held
 */
 
पूर्णांक z8530_shutकरोwn(काष्ठा z8530_dev *dev)
अणु
	अचिन्हित दीर्घ flags;
	/* Reset the chip */

	spin_lock_irqsave(&dev->lock, flags);
	dev->chanA.irqs=&z8530_nop;
	dev->chanB.irqs=&z8530_nop;
	ग_लिखो_zsreg(&dev->chanA, R9, 0xC0);
	/* We must lock the udelay, the chip is offlimits here */
	udelay(100);
	spin_unlock_irqrestore(&dev->lock, flags);
	वापस 0;
पूर्ण

EXPORT_SYMBOL(z8530_shutकरोwn);

/**
 *	z8530_channel_load - Load channel data
 *	@c: Z8530 channel to configure
 *	@rtable: table of रेजिस्टर, value pairs
 *	FIXME: ioctl to allow user uploaded tables
 *
 *	Load a Z8530 channel up from the प्रणाली data. We use +16 to 
 *	indicate the "prime" रेजिस्टरs. The value 255 terminates the
 *	table.
 */

पूर्णांक z8530_channel_load(काष्ठा z8530_channel *c, u8 *rtable)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(c->lock, flags);

	जबतक(*rtable!=255)
	अणु
		पूर्णांक reg=*rtable++;
		अगर(reg>0x0F)
			ग_लिखो_zsreg(c, R15, c->regs[15]|1);
		ग_लिखो_zsreg(c, reg&0x0F, *rtable);
		अगर(reg>0x0F)
			ग_लिखो_zsreg(c, R15, c->regs[15]&~1);
		c->regs[reg]=*rtable++;
	पूर्ण
	c->rx_function=z8530_null_rx;
	c->skb=शून्य;
	c->tx_skb=शून्य;
	c->tx_next_skb=शून्य;
	c->mtu=1500;
	c->max=0;
	c->count=0;
	c->status=पढ़ो_zsreg(c, R0);
	c->sync=1;
	ग_लिखो_zsreg(c, R3, c->regs[R3]|RxENABLE);

	spin_unlock_irqrestore(c->lock, flags);
	वापस 0;
पूर्ण

EXPORT_SYMBOL(z8530_channel_load);


/**
 *	z8530_tx_begin - Begin packet transmission
 *	@c: The Z8530 channel to kick
 *
 *	This is the speed sensitive side of transmission. If we are called
 *	and no buffer is being transmitted we commence the next buffer. If
 *	nothing is queued we idle the sync. 
 *
 *	Note: We are handling this code path in the पूर्णांकerrupt path, keep it
 *	fast or bad things will happen.
 *
 *	Called with the lock held.
 */

अटल व्योम z8530_tx_begin(काष्ठा z8530_channel *c)
अणु
	अचिन्हित दीर्घ flags;
	अगर(c->tx_skb)
		वापस;
		
	c->tx_skb=c->tx_next_skb;
	c->tx_next_skb=शून्य;
	c->tx_ptr=c->tx_next_ptr;
	
	अगर(c->tx_skb==शून्य)
	अणु
		/* Idle on */
		अगर(c->dma_tx)
		अणु
			flags=claim_dma_lock();
			disable_dma(c->txdma);
			/*
			 *	Check अगर we crapped out.
			 */
			अगर (get_dma_residue(c->txdma))
			अणु
				c->netdevice->stats.tx_dropped++;
				c->netdevice->stats.tx_fअगरo_errors++;
			पूर्ण
			release_dma_lock(flags);
		पूर्ण
		c->txcount=0;
	पूर्ण
	अन्यथा
	अणु
		c->txcount=c->tx_skb->len;
		
		
		अगर(c->dma_tx)
		अणु
			/*
			 *	FIXME. DMA is broken क्रम the original 8530,
			 *	on the older parts we need to set a flag and
			 *	रुको क्रम a further TX पूर्णांकerrupt to fire this
			 *	stage off	
			 */
			 
			flags=claim_dma_lock();
			disable_dma(c->txdma);

			/*
			 *	These two are needed by the 8530/85C30
			 *	and must be issued when idling.
			 */
			 
			अगर(c->dev->type!=Z85230)
			अणु
				ग_लिखो_zsctrl(c, RES_Tx_CRC);
				ग_लिखो_zsctrl(c, RES_EOM_L);
			पूर्ण	
			ग_लिखो_zsreg(c, R10, c->regs[10]&~ABUNDER);
			clear_dma_ff(c->txdma);
			set_dma_addr(c->txdma, virt_to_bus(c->tx_ptr));
			set_dma_count(c->txdma, c->txcount);
			enable_dma(c->txdma);
			release_dma_lock(flags);
			ग_लिखो_zsctrl(c, RES_EOM_L);
			ग_लिखो_zsreg(c, R5, c->regs[R5]|TxENAB);
		पूर्ण
		अन्यथा
		अणु

			/* ABUNDER off */
			ग_लिखो_zsreg(c, R10, c->regs[10]);
			ग_लिखो_zsctrl(c, RES_Tx_CRC);
	
			जबतक(c->txcount && (पढ़ो_zsreg(c,R0)&Tx_BUF_EMP))
			अणु		
				ग_लिखो_zsreg(c, R8, *c->tx_ptr++);
				c->txcount--;
			पूर्ण

		पूर्ण
	पूर्ण
	/*
	 *	Since we emptied tx_skb we can ask क्रम more
	 */
	netअगर_wake_queue(c->netdevice);
पूर्ण

/**
 *	z8530_tx_करोne - TX complete callback
 *	@c: The channel that completed a transmit.
 *
 *	This is called when we complete a packet send. We wake the queue,
 *	start the next packet going and then मुक्त the buffer of the existing
 *	packet. This code is fairly timing sensitive.
 *
 *	Called with the रेजिस्टर lock held.
 */

अटल व्योम z8530_tx_करोne(काष्ठा z8530_channel *c)
अणु
	काष्ठा sk_buff *skb;

	/* Actually this can happen.*/
	अगर (c->tx_skb == शून्य)
		वापस;

	skb = c->tx_skb;
	c->tx_skb = शून्य;
	z8530_tx_begin(c);
	c->netdevice->stats.tx_packets++;
	c->netdevice->stats.tx_bytes += skb->len;
	dev_consume_skb_irq(skb);
पूर्ण

/**
 *	z8530_null_rx - Discard a packet
 *	@c: The channel the packet arrived on
 *	@skb: The buffer
 *
 *	We poपूर्णांक the receive handler at this function when idle. Instead
 *	of processing the frames we get to throw them away.
 */
 
व्योम z8530_null_rx(काष्ठा z8530_channel *c, काष्ठा sk_buff *skb)
अणु
	dev_kमुक्त_skb_any(skb);
पूर्ण

EXPORT_SYMBOL(z8530_null_rx);

/**
 *	z8530_rx_करोne - Receive completion callback
 *	@c: The channel that completed a receive
 *
 *	A new packet is complete. Our goal here is to get back पूर्णांकo receive
 *	mode as fast as possible. On the Z85230 we could change to using
 *	ESCC mode, but on the older chips we have no choice. We flip to the
 *	new buffer immediately in DMA mode so that the DMA of the next
 *	frame can occur जबतक we are copying the previous buffer to an sk_buff
 *
 *	Called with the lock held
 */
 
अटल व्योम z8530_rx_करोne(काष्ठा z8530_channel *c)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक ct;
	
	/*
	 *	Is our receive engine in DMA mode
	 */
	 
	अगर(c->rxdma_on)
	अणु
		/*
		 *	Save the पढ़ोy state and the buffer currently
		 *	being used as the DMA target
		 */
		 
		पूर्णांक पढ़ोy=c->dma_पढ़ोy;
		अचिन्हित अक्षर *rxb=c->rx_buf[c->dma_num];
		अचिन्हित दीर्घ flags;
		
		/*
		 *	Complete this DMA. Necessary to find the length
		 */		
		 
		flags=claim_dma_lock();
		
		disable_dma(c->rxdma);
		clear_dma_ff(c->rxdma);
		c->rxdma_on=0;
		ct=c->mtu-get_dma_residue(c->rxdma);
		अगर(ct<0)
			ct=2;	/* Shit happens.. */
		c->dma_पढ़ोy=0;
		
		/*
		 *	Normal हाल: the other slot is मुक्त, start the next DMA
		 *	पूर्णांकo it immediately.
		 */
		 
		अगर(पढ़ोy)
		अणु
			c->dma_num^=1;
			set_dma_mode(c->rxdma, DMA_MODE_READ|0x10);
			set_dma_addr(c->rxdma, virt_to_bus(c->rx_buf[c->dma_num]));
			set_dma_count(c->rxdma, c->mtu);
			c->rxdma_on = 1;
			enable_dma(c->rxdma);
			/* Stop any frames that we missed the head of 
			   from passing */
			ग_लिखो_zsreg(c, R0, RES_Rx_CRC);
		पूर्ण
		अन्यथा
			/* Can't occur as we करोnt reenable the DMA irq until
			   after the flip is करोne */
			netdev_warn(c->netdevice, "DMA flip overrun!\n");

		release_dma_lock(flags);

		/*
		 *	Shove the old buffer पूर्णांकo an sk_buff. We can't DMA
		 *	directly पूर्णांकo one on a PC - it might be above the 16Mb
		 *	boundary. Optimisation - we could check to see अगर we
		 *	can aव्योम the copy. Optimisation 2 - make the स_नकल
		 *	a copychecksum.
		 */

		skb = dev_alloc_skb(ct);
		अगर (skb == शून्य) अणु
			c->netdevice->stats.rx_dropped++;
			netdev_warn(c->netdevice, "Memory squeeze\n");
		पूर्ण अन्यथा अणु
			skb_put(skb, ct);
			skb_copy_to_linear_data(skb, rxb, ct);
			c->netdevice->stats.rx_packets++;
			c->netdevice->stats.rx_bytes += ct;
		पूर्ण
		c->dma_पढ़ोy = 1;
	पूर्ण अन्यथा अणु
		RT_LOCK;
		skb = c->skb;

		/*
		 *	The game we play क्रम non DMA is similar. We want to
		 *	get the controller set up क्रम the next packet as fast
		 *	as possible. We potentially only have one byte + the
		 *	fअगरo length क्रम this. Thus we want to flip to the new
		 *	buffer and then mess around copying and allocating
		 *	things. For the current हाल it करोesn't matter but
		 *	अगर you build a प्रणाली where the sync irq isn't blocked
		 *	by the kernel IRQ disable then you need only block the
		 *	sync IRQ क्रम the RT_LOCK area.
		 *
		 */
		ct=c->count;

		c->skb = c->skb2;
		c->count = 0;
		c->max = c->mtu;
		अगर (c->skb) अणु
			c->dptr = c->skb->data;
			c->max = c->mtu;
		पूर्ण अन्यथा अणु
			c->count = 0;
			c->max = 0;
		पूर्ण
		RT_UNLOCK;

		c->skb2 = dev_alloc_skb(c->mtu);
		अगर (c->skb2 == शून्य)
			netdev_warn(c->netdevice, "memory squeeze\n");
		अन्यथा
			skb_put(c->skb2, c->mtu);
		c->netdevice->stats.rx_packets++;
		c->netdevice->stats.rx_bytes += ct;
	पूर्ण
	/*
	 *	If we received a frame we must now process it.
	 */
	अगर (skb) अणु
		skb_trim(skb, ct);
		c->rx_function(c, skb);
	पूर्ण अन्यथा अणु
		c->netdevice->stats.rx_dropped++;
		netdev_err(c->netdevice, "Lost a frame\n");
	पूर्ण
पूर्ण

/**
 *	spans_boundary - Check a packet can be ISA DMA'd
 *	@skb: The buffer to check
 *
 *	Returns true अगर the buffer cross a DMA boundary on a PC. The poor
 *	thing can only DMA within a 64K block not across the edges of it.
 */

अटल अंतरभूत पूर्णांक spans_boundary(काष्ठा sk_buff *skb)
अणु
	अचिन्हित दीर्घ a=(अचिन्हित दीर्घ)skb->data;
	a^=(a+skb->len);
	अगर(a&0x00010000)	/* If the 64K bit is dअगरferent.. */
		वापस 1;
	वापस 0;
पूर्ण

/**
 *	z8530_queue_xmit - Queue a packet
 *	@c: The channel to use
 *	@skb: The packet to kick करोwn the channel
 *
 *	Queue a packet क्रम transmission. Because we have rather
 *	hard to hit पूर्णांकerrupt latencies क्रम the Z85230 per packet 
 *	even in DMA mode we करो the flip to DMA buffer अगर needed here
 *	not in the IRQ.
 *
 *	Called from the network code. The lock is not held at this 
 *	poपूर्णांक.
 */

netdev_tx_t z8530_queue_xmit(काष्ठा z8530_channel *c, काष्ठा sk_buff *skb)
अणु
	अचिन्हित दीर्घ flags;
	
	netअगर_stop_queue(c->netdevice);
	अगर(c->tx_next_skb)
		वापस NETDEV_TX_BUSY;

	
	/* PC SPECIFIC - DMA limits */
	
	/*
	 *	If we will DMA the transmit and its gone over the ISA bus
	 *	limit, then copy to the flip buffer
	 */
	 
	अगर(c->dma_tx && ((अचिन्हित दीर्घ)(virt_to_bus(skb->data+skb->len))>=16*1024*1024 || spans_boundary(skb)))
	अणु
		/* 
		 *	Send the flip buffer, and flip the flippy bit.
		 *	We करोn't care which is used when just so दीर्घ as
		 *	we never use the same buffer twice in a row. Since
		 *	only one buffer can be going out at a समय the other
		 *	has to be safe.
		 */
		c->tx_next_ptr=c->tx_dma_buf[c->tx_dma_used];
		c->tx_dma_used^=1;	/* Flip temp buffer */
		skb_copy_from_linear_data(skb, c->tx_next_ptr, skb->len);
	पूर्ण
	अन्यथा
		c->tx_next_ptr=skb->data;	
	RT_LOCK;
	c->tx_next_skb=skb;
	RT_UNLOCK;
	
	spin_lock_irqsave(c->lock, flags);
	z8530_tx_begin(c);
	spin_unlock_irqrestore(c->lock, flags);
	
	वापस NETDEV_TX_OK;
पूर्ण

EXPORT_SYMBOL(z8530_queue_xmit);

/*
 *	Module support
 */
अटल स्थिर अक्षर banner[] __initस्थिर =
	KERN_INFO "Generic Z85C30/Z85230 interface driver v0.02\n";

अटल पूर्णांक __init z85230_init_driver(व्योम)
अणु
	prपूर्णांकk(banner);
	वापस 0;
पूर्ण
module_init(z85230_init_driver);

अटल व्योम __निकास z85230_cleanup_driver(व्योम)
अणु
पूर्ण
module_निकास(z85230_cleanup_driver);

MODULE_AUTHOR("Red Hat Inc.");
MODULE_DESCRIPTION("Z85x30 synchronous driver core");
MODULE_LICENSE("GPL");
