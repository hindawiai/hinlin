<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* drivers/aपंचांग/zaपंचांग.c - ZeitNet ZN122x device driver */
 
/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */


#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/pci.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/aपंचांग.h>
#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/sonet.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/uपन.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/aपंचांग_zaपंचांग.h>
#समावेश <linux/capability.h>
#समावेश <linux/bitops.h>
#समावेश <linux/रुको.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/माला.स>
#समावेश <यंत्र/पन.स>
#समावेश <linux/atomic.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/nospec.h>

#समावेश "uPD98401.h"
#समावेश "uPD98402.h"
#समावेश "zeprom.h"
#समावेश "zatm.h"


/*
 * TODO:
 *
 * Minor features
 *  - support 64 kB SDUs (will have to use multibuffer batches then :-( )
 *  - proper use of CDV, credit = max(1,CDVT*PCR)
 *  - AAL0
 *  - better receive बारtamps
 *  - OAM
 */

#घोषणा ZATM_COPPER	1

#अगर 0
#घोषणा DPRINTK(क्रमmat,args...) prपूर्णांकk(KERN_DEBUG क्रमmat,##args)
#अन्यथा
#घोषणा DPRINTK(क्रमmat,args...)
#पूर्ण_अगर

#अगर_अघोषित CONFIG_ATM_ZATM_DEBUG


#घोषणा शून्यCHECK(x)

#घोषणा EVENT(s,a,b)


अटल व्योम event_dump(व्योम)
अणु
पूर्ण


#अन्यथा


/* 
 * शून्य poपूर्णांकer checking
 */

#घोषणा शून्यCHECK(x) \
  अगर ((अचिन्हित दीर्घ) (x) < 0x30) prपूर्णांकk(KERN_CRIT #x "==0x%x\n", (पूर्णांक) (x))

/*
 * Very extensive activity logging. Greatly improves bug detection speed but
 * costs a few Mbps अगर enabled.
 */

#घोषणा EV 64

अटल स्थिर अक्षर *ev[EV];
अटल अचिन्हित दीर्घ ev_a[EV],ev_b[EV];
अटल पूर्णांक ec = 0;


अटल व्योम EVENT(स्थिर अक्षर *s,अचिन्हित दीर्घ a,अचिन्हित दीर्घ b)
अणु
	ev[ec] = s; 
	ev_a[ec] = a;
	ev_b[ec] = b;
	ec = (ec+1) % EV;
पूर्ण


अटल व्योम event_dump(व्योम)
अणु
	पूर्णांक n,i;

	prपूर्णांकk(KERN_NOTICE "----- event dump follows -----\n");
	क्रम (n = 0; n < EV; n++) अणु
		i = (ec+n) % EV;
		prपूर्णांकk(KERN_NOTICE);
		prपूर्णांकk(ev[i] ? ev[i] : "(null)",ev_a[i],ev_b[i]);
	पूर्ण
	prपूर्णांकk(KERN_NOTICE "----- event dump ends here -----\n");
पूर्ण


#पूर्ण_अगर /* CONFIG_ATM_ZATM_DEBUG */


#घोषणा RING_BUSY	1	/* indication from करो_tx that PDU has to be
				   backlogged */

अटल काष्ठा aपंचांग_dev *zaपंचांग_boards = शून्य;
अटल अचिन्हित दीर्घ dummy[2] = अणु0,0पूर्ण;


#घोषणा zin_n(r) inl(zaपंचांग_dev->base+r*4)
#घोषणा zin(r) inl(zaपंचांग_dev->base+uPD98401_##r*4)
#घोषणा zout(v,r) outl(v,zaपंचांग_dev->base+uPD98401_##r*4)
#घोषणा zरुको() करो अणुपूर्ण जबतक (zin(CMR) & uPD98401_BUSY)

/* RX0, RX1, TX0, TX1 */
अटल स्थिर पूर्णांक mbx_entries[NR_MBX] = अणु 1024,1024,1024,1024 पूर्ण;
अटल स्थिर पूर्णांक mbx_esize[NR_MBX] = अणु 16,16,4,4 पूर्ण; /* entry size in bytes */

#घोषणा MBX_SIZE(i) (mbx_entries[i]*mbx_esize[i])


/*-------------------------------- utilities --------------------------------*/


अटल व्योम zpokel(काष्ठा zaपंचांग_dev *zaपंचांग_dev,u32 value,u32 addr)
अणु
	zरुको();
	zout(value,CER);
	zout(uPD98401_IND_ACC | uPD98401_IA_BALL |
	    (uPD98401_IA_TGT_CM << uPD98401_IA_TGT_SHIFT) | addr,CMR);
पूर्ण


अटल u32 zpeekl(काष्ठा zaपंचांग_dev *zaपंचांग_dev,u32 addr)
अणु
	zरुको();
	zout(uPD98401_IND_ACC | uPD98401_IA_BALL | uPD98401_IA_RW |
	  (uPD98401_IA_TGT_CM << uPD98401_IA_TGT_SHIFT) | addr,CMR);
	zरुको();
	वापस zin(CER);
पूर्ण


/*------------------------------- मुक्त lists --------------------------------*/


/*
 * Free buffer head काष्ठाure:
 *   [0] poपूर्णांकer to buffer (क्रम SAR)
 *   [1] buffer descr link poपूर्णांकer (क्रम SAR)
 *   [2] back poपूर्णांकer to skb (क्रम poll_rx)
 *   [3] data
 *   ...
 */

काष्ठा rx_buffer_head अणु
	u32		buffer;	/* poपूर्णांकer to buffer (क्रम SAR) */
	u32		link;	/* buffer descriptor link poपूर्णांकer (क्रम SAR) */
	काष्ठा sk_buff	*skb;	/* back poपूर्णांकer to skb (क्रम poll_rx) */
पूर्ण;


अटल व्योम refill_pool(काष्ठा aपंचांग_dev *dev,पूर्णांक pool)
अणु
	काष्ठा zaपंचांग_dev *zaपंचांग_dev;
	काष्ठा sk_buff *skb;
	काष्ठा rx_buffer_head *first;
	अचिन्हित दीर्घ flags;
	पूर्णांक align,offset,मुक्त,count,size;

	EVENT("refill_pool\n",0,0);
	zaपंचांग_dev = ZATM_DEV(dev);
	size = (64 << (pool <= ZATM_AAL5_POOL_BASE ? 0 :
	    pool-ZATM_AAL5_POOL_BASE))+माप(काष्ठा rx_buffer_head);
	अगर (size < PAGE_SIZE) अणु
		align = 32; /* क्रम 32 byte alignment */
		offset = माप(काष्ठा rx_buffer_head);
	पूर्ण
	अन्यथा अणु
		align = 4096;
		offset = zaपंचांग_dev->pool_info[pool].offset+
		    माप(काष्ठा rx_buffer_head);
	पूर्ण
	size += align;
	spin_lock_irqsave(&zaपंचांग_dev->lock, flags);
	मुक्त = zpeekl(zaपंचांग_dev,zaपंचांग_dev->pool_base+2*pool) &
	    uPD98401_RXFP_REMAIN;
	spin_unlock_irqrestore(&zaपंचांग_dev->lock, flags);
	अगर (मुक्त >= zaपंचांग_dev->pool_info[pool].low_water) वापस;
	EVENT("starting ... POOL: 0x%x, 0x%x\n",
	    zpeekl(zaपंचांग_dev,zaपंचांग_dev->pool_base+2*pool),
	    zpeekl(zaपंचांग_dev,zaपंचांग_dev->pool_base+2*pool+1));
	EVENT("dummy: 0x%08lx, 0x%08lx\n",dummy[0],dummy[1]);
	count = 0;
	first = शून्य;
	जबतक (मुक्त < zaपंचांग_dev->pool_info[pool].high_water) अणु
		काष्ठा rx_buffer_head *head;

		skb = alloc_skb(size,GFP_ATOMIC);
		अगर (!skb) अणु
			prपूर्णांकk(KERN_WARNING DEV_LABEL "(Itf %d): got no new "
			    "skb (%d) with %d free\n",dev->number,size,मुक्त);
			अवरोध;
		पूर्ण
		skb_reserve(skb,(अचिन्हित अक्षर *) ((((अचिन्हित दीर्घ) skb->data+
		    align+offset-1) & ~(अचिन्हित दीर्घ) (align-1))-offset)-
		    skb->data);
		head = (काष्ठा rx_buffer_head *) skb->data;
		skb_reserve(skb,माप(काष्ठा rx_buffer_head));
		अगर (!first) first = head;
		count++;
		head->buffer = virt_to_bus(skb->data);
		head->link = 0;
		head->skb = skb;
		EVENT("enq skb 0x%08lx/0x%08lx\n",(अचिन्हित दीर्घ) skb,
		    (अचिन्हित दीर्घ) head);
		spin_lock_irqsave(&zaपंचांग_dev->lock, flags);
		अगर (zaपंचांग_dev->last_मुक्त[pool])
			((काष्ठा rx_buffer_head *) (zaपंचांग_dev->last_मुक्त[pool]->
			    data))[-1].link = virt_to_bus(head);
		zaपंचांग_dev->last_मुक्त[pool] = skb;
		skb_queue_tail(&zaपंचांग_dev->pool[pool],skb);
		spin_unlock_irqrestore(&zaपंचांग_dev->lock, flags);
		मुक्त++;
	पूर्ण
	अगर (first) अणु
		spin_lock_irqsave(&zaपंचांग_dev->lock, flags);
		zरुको();
		zout(virt_to_bus(first),CER);
		zout(uPD98401_ADD_BAT | (pool << uPD98401_POOL_SHIFT) | count,
		    CMR);
		spin_unlock_irqrestore(&zaपंचांग_dev->lock, flags);
		EVENT ("POOL: 0x%x, 0x%x\n",
		    zpeekl(zaपंचांग_dev,zaपंचांग_dev->pool_base+2*pool),
		    zpeekl(zaपंचांग_dev,zaपंचांग_dev->pool_base+2*pool+1));
		EVENT("dummy: 0x%08lx, 0x%08lx\n",dummy[0],dummy[1]);
	पूर्ण
पूर्ण


अटल व्योम drain_मुक्त(काष्ठा aपंचांग_dev *dev,पूर्णांक pool)
अणु
	skb_queue_purge(&ZATM_DEV(dev)->pool[pool]);
पूर्ण


अटल पूर्णांक pool_index(पूर्णांक max_pdu)
अणु
	पूर्णांक i;

	अगर (max_pdu % ATM_CELL_PAYLOAD)
		prपूर्णांकk(KERN_ERR DEV_LABEL ": driver error in pool_index: "
		    "max_pdu is %d\n",max_pdu);
	अगर (max_pdu > 65536) वापस -1;
	क्रम (i = 0; (64 << i) < max_pdu; i++);
	वापस i+ZATM_AAL5_POOL_BASE;
पूर्ण


/* use_pool isn't reentrant */


अटल व्योम use_pool(काष्ठा aपंचांग_dev *dev,पूर्णांक pool)
अणु
	काष्ठा zaपंचांग_dev *zaपंचांग_dev;
	अचिन्हित दीर्घ flags;
	पूर्णांक size;

	zaपंचांग_dev = ZATM_DEV(dev);
	अगर (!(zaपंचांग_dev->pool_info[pool].ref_count++)) अणु
		skb_queue_head_init(&zaपंचांग_dev->pool[pool]);
		size = pool-ZATM_AAL5_POOL_BASE;
		अगर (size < 0) size = 0; /* 64B... */
		अन्यथा अगर (size > 10) size = 10; /* ... 64kB */
		spin_lock_irqsave(&zaपंचांग_dev->lock, flags);
		zpokel(zaपंचांग_dev,((zaपंचांग_dev->pool_info[pool].low_water/4) <<
		    uPD98401_RXFP_ALERT_SHIFT) |
		    (1 << uPD98401_RXFP_BTSZ_SHIFT) |
		    (size << uPD98401_RXFP_BFSZ_SHIFT),
		    zaपंचांग_dev->pool_base+pool*2);
		zpokel(zaपंचांग_dev,(अचिन्हित दीर्घ) dummy,zaपंचांग_dev->pool_base+
		    pool*2+1);
		spin_unlock_irqrestore(&zaपंचांग_dev->lock, flags);
		zaपंचांग_dev->last_मुक्त[pool] = शून्य;
		refill_pool(dev,pool);
	पूर्ण
	DPRINTK("pool %d: %d\n",pool,zaपंचांग_dev->pool_info[pool].ref_count);
पूर्ण


अटल व्योम unuse_pool(काष्ठा aपंचांग_dev *dev,पूर्णांक pool)
अणु
	अगर (!(--ZATM_DEV(dev)->pool_info[pool].ref_count))
		drain_मुक्त(dev,pool);
पूर्ण

/*----------------------------------- RX ------------------------------------*/


#अगर 0
अटल व्योम exception(काष्ठा aपंचांग_vcc *vcc)
अणु
   अटल पूर्णांक count = 0;
   काष्ठा zaपंचांग_dev *zaपंचांग_dev = ZATM_DEV(vcc->dev);
   काष्ठा zaपंचांग_vcc *zaपंचांग_vcc = ZATM_VCC(vcc);
   अचिन्हित दीर्घ *qrp;
   पूर्णांक i;

   अगर (count++ > 2) वापस;
   क्रम (i = 0; i < 8; i++)
	prपूर्णांकk("TX%d: 0x%08lx\n",i,
	  zpeekl(zaपंचांग_dev,zaपंचांग_vcc->tx_chan*VC_SIZE/4+i));
   क्रम (i = 0; i < 5; i++)
	prपूर्णांकk("SH%d: 0x%08lx\n",i,
	  zpeekl(zaपंचांग_dev,uPD98401_IM(zaपंचांग_vcc->shaper)+16*i));
   qrp = (अचिन्हित दीर्घ *) zpeekl(zaपंचांग_dev,zaपंचांग_vcc->tx_chan*VC_SIZE/4+
     uPD98401_TXVC_QRP);
   prपूर्णांकk("qrp=0x%08lx\n",(अचिन्हित दीर्घ) qrp);
   क्रम (i = 0; i < 4; i++) prपूर्णांकk("QRP[%d]: 0x%08lx",i,qrp[i]);
पूर्ण
#पूर्ण_अगर


अटल स्थिर अक्षर *err_txt[] = अणु
	"No error",
	"RX buf underflow",
	"RX FIFO overrun",
	"Maximum len violation",
	"CRC error",
	"User abort",
	"Length violation",
	"T1 error",
	"Deactivated",
	"???",
	"???",
	"???",
	"???",
	"???",
	"???",
	"???"
पूर्ण;


अटल व्योम poll_rx(काष्ठा aपंचांग_dev *dev,पूर्णांक mbx)
अणु
	काष्ठा zaपंचांग_dev *zaपंचांग_dev;
	अचिन्हित दीर्घ pos;
	u32 x;
	पूर्णांक error;

	EVENT("poll_rx\n",0,0);
	zaपंचांग_dev = ZATM_DEV(dev);
	pos = (zaपंचांग_dev->mbx_start[mbx] & ~0xffffUL) | zin(MTA(mbx));
	जबतक (x = zin(MWA(mbx)), (pos & 0xffff) != x) अणु
		u32 *here;
		काष्ठा sk_buff *skb;
		काष्ठा aपंचांग_vcc *vcc;
		पूर्णांक cells,size,chan;

		EVENT("MBX: host 0x%lx, nic 0x%x\n",pos,x);
		here = (u32 *) pos;
		अगर (((pos += 16) & 0xffff) == zaपंचांग_dev->mbx_end[mbx])
			pos = zaपंचांग_dev->mbx_start[mbx];
		cells = here[0] & uPD98401_AAL5_SIZE;
#अगर 0
prपूर्णांकk("RX IND: 0x%x, 0x%x, 0x%x, 0x%x\n",here[0],here[1],here[2],here[3]);
अणु
अचिन्हित दीर्घ *x;
		prपूर्णांकk("POOL: 0x%08x, 0x%08x\n",zpeekl(zaपंचांग_dev,
		      zaपंचांग_dev->pool_base),
		      zpeekl(zaपंचांग_dev,zaपंचांग_dev->pool_base+1));
		x = (अचिन्हित दीर्घ *) here[2];
		prपूर्णांकk("[0..3] = 0x%08lx, 0x%08lx, 0x%08lx, 0x%08lx\n",
		    x[0],x[1],x[2],x[3]);
पूर्ण
#पूर्ण_अगर
		error = 0;
		अगर (here[3] & uPD98401_AAL5_ERR) अणु
			error = (here[3] & uPD98401_AAL5_ES) >>
			    uPD98401_AAL5_ES_SHIFT;
			अगर (error == uPD98401_AAL5_ES_DEACT ||
			    error == uPD98401_AAL5_ES_FREE) जारी;
		पूर्ण
EVENT("error code 0x%x/0x%x\n",(here[3] & uPD98401_AAL5_ES) >>
  uPD98401_AAL5_ES_SHIFT,error);
		skb = ((काष्ठा rx_buffer_head *) bus_to_virt(here[2]))->skb;
		__net_बारtamp(skb);
#अगर 0
prपूर्णांकk("[-3..0] 0x%08lx 0x%08lx 0x%08lx 0x%08lx\n",((अचिन्हित *) skb->data)[-3],
  ((अचिन्हित *) skb->data)[-2],((अचिन्हित *) skb->data)[-1],
  ((अचिन्हित *) skb->data)[0]);
#पूर्ण_अगर
		EVENT("skb 0x%lx, here 0x%lx\n",(अचिन्हित दीर्घ) skb,
		    (अचिन्हित दीर्घ) here);
#अगर 0
prपूर्णांकk("dummy: 0x%08lx, 0x%08lx\n",dummy[0],dummy[1]);
#पूर्ण_अगर
		size = error ? 0 : ntohs(((__be16 *) skb->data)[cells*
		    ATM_CELL_PAYLOAD/माप(u16)-3]);
		EVENT("got skb 0x%lx, size %d\n",(अचिन्हित दीर्घ) skb,size);
		chan = (here[3] & uPD98401_AAL5_CHAN) >>
		    uPD98401_AAL5_CHAN_SHIFT;
		अगर (chan < zaपंचांग_dev->chans && zaपंचांग_dev->rx_map[chan]) अणु
			पूर्णांक pos;
			vcc = zaपंचांग_dev->rx_map[chan];
			pos = ZATM_VCC(vcc)->pool;
			अगर (skb == zaपंचांग_dev->last_मुक्त[pos])
				zaपंचांग_dev->last_मुक्त[pos] = शून्य;
			skb_unlink(skb, zaपंचांग_dev->pool + pos);
		पूर्ण
		अन्यथा अणु
			prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): RX indication "
			    "for non-existing channel\n",dev->number);
			size = 0;
			vcc = शून्य;
			event_dump();
		पूर्ण
		अगर (error) अणु
			अटल अचिन्हित दीर्घ silence = 0;
			अटल पूर्णांक last_error = 0;

			अगर (error != last_error ||
			    समय_after(jअगरfies, silence)  || silence == 0)अणु
				prपूर्णांकk(KERN_WARNING DEV_LABEL "(itf %d): "
				    "chan %d error %s\n",dev->number,chan,
				    err_txt[error]);
				last_error = error;
				silence = (jअगरfies+2*HZ)|1;
			पूर्ण
			size = 0;
		पूर्ण
		अगर (size && (size > cells*ATM_CELL_PAYLOAD-ATM_AAL5_TRAILER ||
		    size <= (cells-1)*ATM_CELL_PAYLOAD-ATM_AAL5_TRAILER)) अणु
			prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): size %d with %d "
			    "cells\n",dev->number,size,cells);
			size = 0;
			event_dump();
		पूर्ण
		अगर (size > ATM_MAX_AAL5_PDU) अणु
			prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): size too big "
			    "(%d)\n",dev->number,size);
			size = 0;
			event_dump();
		पूर्ण
		अगर (!size) अणु
			dev_kमुक्त_skb_irq(skb);
			अगर (vcc) atomic_inc(&vcc->stats->rx_err);
			जारी;
		पूर्ण
		अगर (!aपंचांग_अक्षरge(vcc,skb->truesize)) अणु
			dev_kमुक्त_skb_irq(skb);
			जारी;
		पूर्ण
		skb->len = size;
		ATM_SKB(skb)->vcc = vcc;
		vcc->push(vcc,skb);
		atomic_inc(&vcc->stats->rx);
	पूर्ण
	zout(pos & 0xffff,MTA(mbx));
#अगर 0 /* probably a stupid idea */
	refill_pool(dev,zaपंचांग_vcc->pool);
		/* maybe this saves us a few पूर्णांकerrupts */
#पूर्ण_अगर
पूर्ण


अटल पूर्णांक खोलो_rx_first(काष्ठा aपंचांग_vcc *vcc)
अणु
	काष्ठा zaपंचांग_dev *zaपंचांग_dev;
	काष्ठा zaपंचांग_vcc *zaपंचांग_vcc;
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु chan;
	पूर्णांक cells;

	DPRINTK("open_rx_first (0x%x)\n",inb_p(0xc053));
	zaपंचांग_dev = ZATM_DEV(vcc->dev);
	zaपंचांग_vcc = ZATM_VCC(vcc);
	zaपंचांग_vcc->rx_chan = 0;
	अगर (vcc->qos.rxtp.traffic_class == ATM_NONE) वापस 0;
	अगर (vcc->qos.aal == ATM_AAL5) अणु
		अगर (vcc->qos.rxtp.max_sdu > 65464)
			vcc->qos.rxtp.max_sdu = 65464;
			/* fix this - we may want to receive 64kB SDUs
			   later */
		cells = DIV_ROUND_UP(vcc->qos.rxtp.max_sdu + ATM_AAL5_TRAILER,
				ATM_CELL_PAYLOAD);
		zaपंचांग_vcc->pool = pool_index(cells*ATM_CELL_PAYLOAD);
	पूर्ण
	अन्यथा अणु
		cells = 1;
		zaपंचांग_vcc->pool = ZATM_AAL0_POOL;
	पूर्ण
	अगर (zaपंचांग_vcc->pool < 0) वापस -EMSGSIZE;
	spin_lock_irqsave(&zaपंचांग_dev->lock, flags);
	zरुको();
	zout(uPD98401_OPEN_CHAN,CMR);
	zरुको();
	DPRINTK("0x%x 0x%x\n",zin(CMR),zin(CER));
	chan = (zin(CMR) & uPD98401_CHAN_ADDR) >> uPD98401_CHAN_ADDR_SHIFT;
	spin_unlock_irqrestore(&zaपंचांग_dev->lock, flags);
	DPRINTK("chan is %d\n",chan);
	अगर (!chan) वापस -EAGAIN;
	use_pool(vcc->dev,zaपंचांग_vcc->pool);
	DPRINTK("pool %d\n",zaपंचांग_vcc->pool);
	/* set up VC descriptor */
	spin_lock_irqsave(&zaपंचांग_dev->lock, flags);
	zpokel(zaपंचांग_dev,zaपंचांग_vcc->pool << uPD98401_RXVC_POOL_SHIFT,
	    chan*VC_SIZE/4);
	zpokel(zaपंचांग_dev,uPD98401_RXVC_OD | (vcc->qos.aal == ATM_AAL5 ?
	    uPD98401_RXVC_AR : 0) | cells,chan*VC_SIZE/4+1);
	zpokel(zaपंचांग_dev,0,chan*VC_SIZE/4+2);
	zaपंचांग_vcc->rx_chan = chan;
	zaपंचांग_dev->rx_map[chan] = vcc;
	spin_unlock_irqrestore(&zaपंचांग_dev->lock, flags);
	वापस 0;
पूर्ण


अटल पूर्णांक खोलो_rx_second(काष्ठा aपंचांग_vcc *vcc)
अणु
	काष्ठा zaपंचांग_dev *zaपंचांग_dev;
	काष्ठा zaपंचांग_vcc *zaपंचांग_vcc;
	अचिन्हित दीर्घ flags;
	पूर्णांक pos,shअगरt;

	DPRINTK("open_rx_second (0x%x)\n",inb_p(0xc053));
	zaपंचांग_dev = ZATM_DEV(vcc->dev);
	zaपंचांग_vcc = ZATM_VCC(vcc);
	अगर (!zaपंचांग_vcc->rx_chan) वापस 0;
	spin_lock_irqsave(&zaपंचांग_dev->lock, flags);
	/* should also handle VPI @@@ */
	pos = vcc->vci >> 1;
	shअगरt = (1-(vcc->vci & 1)) << 4;
	zpokel(zaपंचांग_dev,(zpeekl(zaपंचांग_dev,pos) & ~(0xffff << shअगरt)) |
	    ((zaपंचांग_vcc->rx_chan | uPD98401_RXLT_ENBL) << shअगरt),pos);
	spin_unlock_irqrestore(&zaपंचांग_dev->lock, flags);
	वापस 0;
पूर्ण


अटल व्योम बंद_rx(काष्ठा aपंचांग_vcc *vcc)
अणु
	काष्ठा zaपंचांग_dev *zaपंचांग_dev;
	काष्ठा zaपंचांग_vcc *zaपंचांग_vcc;
	अचिन्हित दीर्घ flags;
	पूर्णांक pos,shअगरt;

	zaपंचांग_vcc = ZATM_VCC(vcc);
	zaपंचांग_dev = ZATM_DEV(vcc->dev);
	अगर (!zaपंचांग_vcc->rx_chan) वापस;
	DPRINTK("close_rx\n");
	/* disable receiver */
	अगर (vcc->vpi != ATM_VPI_UNSPEC && vcc->vci != ATM_VCI_UNSPEC) अणु
		spin_lock_irqsave(&zaपंचांग_dev->lock, flags);
		pos = vcc->vci >> 1;
		shअगरt = (1-(vcc->vci & 1)) << 4;
		zpokel(zaपंचांग_dev,zpeekl(zaपंचांग_dev,pos) & ~(0xffff << shअगरt),pos);
		zरुको();
		zout(uPD98401_NOP,CMR);
		zरुको();
		zout(uPD98401_NOP,CMR);
		spin_unlock_irqrestore(&zaपंचांग_dev->lock, flags);
	पूर्ण
	spin_lock_irqsave(&zaपंचांग_dev->lock, flags);
	zरुको();
	zout(uPD98401_DEACT_CHAN | uPD98401_CHAN_RT | (zaपंचांग_vcc->rx_chan <<
	    uPD98401_CHAN_ADDR_SHIFT),CMR);
	zरुको();
	udelay(10); /* why oh why ... ? */
	zout(uPD98401_CLOSE_CHAN | uPD98401_CHAN_RT | (zaपंचांग_vcc->rx_chan <<
	    uPD98401_CHAN_ADDR_SHIFT),CMR);
	zरुको();
	अगर (!(zin(CMR) & uPD98401_CHAN_ADDR))
		prपूर्णांकk(KERN_CRIT DEV_LABEL "(itf %d): can't close RX channel "
		    "%d\n",vcc->dev->number,zaपंचांग_vcc->rx_chan);
	spin_unlock_irqrestore(&zaपंचांग_dev->lock, flags);
	zaपंचांग_dev->rx_map[zaपंचांग_vcc->rx_chan] = शून्य;
	zaपंचांग_vcc->rx_chan = 0;
	unuse_pool(vcc->dev,zaपंचांग_vcc->pool);
पूर्ण


अटल पूर्णांक start_rx(काष्ठा aपंचांग_dev *dev)
अणु
	काष्ठा zaपंचांग_dev *zaपंचांग_dev;
	पूर्णांक i;

	DPRINTK("start_rx\n");
	zaपंचांग_dev = ZATM_DEV(dev);
	zaपंचांग_dev->rx_map = kसुस्मृति(zaपंचांग_dev->chans,
				   माप(*zaपंचांग_dev->rx_map),
				   GFP_KERNEL);
	अगर (!zaपंचांग_dev->rx_map) वापस -ENOMEM;
	/* set VPI/VCI split (use all VCIs and give what's left to VPIs) */
	zpokel(zaपंचांग_dev,(1 << dev->ci_range.vci_bits)-1,uPD98401_VRR);
	/* prepare मुक्त buffer pools */
	क्रम (i = 0; i <= ZATM_LAST_POOL; i++) अणु
		zaपंचांग_dev->pool_info[i].ref_count = 0;
		zaपंचांग_dev->pool_info[i].rqa_count = 0;
		zaपंचांग_dev->pool_info[i].rqu_count = 0;
		zaपंचांग_dev->pool_info[i].low_water = LOW_MARK;
		zaपंचांग_dev->pool_info[i].high_water = HIGH_MARK;
		zaपंचांग_dev->pool_info[i].offset = 0;
		zaपंचांग_dev->pool_info[i].next_off = 0;
		zaपंचांग_dev->pool_info[i].next_cnt = 0;
		zaपंचांग_dev->pool_info[i].next_thres = OFF_CNG_THRES;
	पूर्ण
	वापस 0;
पूर्ण


/*----------------------------------- TX ------------------------------------*/


अटल पूर्णांक करो_tx(काष्ठा sk_buff *skb)
अणु
	काष्ठा aपंचांग_vcc *vcc;
	काष्ठा zaपंचांग_dev *zaपंचांग_dev;
	काष्ठा zaपंचांग_vcc *zaपंचांग_vcc;
	u32 *dsc;
	अचिन्हित दीर्घ flags;

	EVENT("do_tx\n",0,0);
	DPRINTK("sending skb %p\n",skb);
	vcc = ATM_SKB(skb)->vcc;
	zaपंचांग_dev = ZATM_DEV(vcc->dev);
	zaपंचांग_vcc = ZATM_VCC(vcc);
	EVENT("iovcnt=%d\n",skb_shinfo(skb)->nr_frags,0);
	spin_lock_irqsave(&zaपंचांग_dev->lock, flags);
	अगर (!skb_shinfo(skb)->nr_frags) अणु
		अगर (zaपंचांग_vcc->txing == RING_ENTRIES-1) अणु
			spin_unlock_irqrestore(&zaपंचांग_dev->lock, flags);
			वापस RING_BUSY;
		पूर्ण
		zaपंचांग_vcc->txing++;
		dsc = zaपंचांग_vcc->ring+zaपंचांग_vcc->ring_curr;
		zaपंचांग_vcc->ring_curr = (zaपंचांग_vcc->ring_curr+RING_WORDS) &
		    (RING_ENTRIES*RING_WORDS-1);
		dsc[1] = 0;
		dsc[2] = skb->len;
		dsc[3] = virt_to_bus(skb->data);
		mb();
		dsc[0] = uPD98401_TXPD_V | uPD98401_TXPD_DP | uPD98401_TXPD_SM
		    | (vcc->qos.aal == ATM_AAL5 ? uPD98401_TXPD_AAL5 : 0 |
		    (ATM_SKB(skb)->aपंचांग_options & ATM_ATMOPT_CLP ?
		    uPD98401_CLPM_1 : uPD98401_CLPM_0));
		EVENT("dsc (0x%lx)\n",(अचिन्हित दीर्घ) dsc,0);
	पूर्ण
	अन्यथा अणु
prपूर्णांकk("NONONONOO!!!!\n");
		dsc = शून्य;
#अगर 0
		u32 *put;
		पूर्णांक i;

		dsc = kदो_स्मृति(uPD98401_TXPD_SIZE * 2 +
			uPD98401_TXBD_SIZE * ATM_SKB(skb)->iovcnt, GFP_ATOMIC);
		अगर (!dsc) अणु
			अगर (vcc->pop)
				vcc->pop(vcc, skb);
			अन्यथा
				dev_kमुक्त_skb_irq(skb);
			वापस -EAGAIN;
		पूर्ण
		/* @@@ should check alignment */
		put = dsc+8;
		dsc[0] = uPD98401_TXPD_V | uPD98401_TXPD_DP |
		    (vcc->aal == ATM_AAL5 ? uPD98401_TXPD_AAL5 : 0 |
		    (ATM_SKB(skb)->aपंचांग_options & ATM_ATMOPT_CLP ?
		    uPD98401_CLPM_1 : uPD98401_CLPM_0));
		dsc[1] = 0;
		dsc[2] = ATM_SKB(skb)->iovcnt * uPD98401_TXBD_SIZE;
		dsc[3] = virt_to_bus(put);
		क्रम (i = 0; i < ATM_SKB(skb)->iovcnt; i++) अणु
			*put++ = ((काष्ठा iovec *) skb->data)[i].iov_len;
			*put++ = virt_to_bus(((काष्ठा iovec *)
			    skb->data)[i].iov_base);
		पूर्ण
		put[-2] |= uPD98401_TXBD_LAST;
#पूर्ण_अगर
	पूर्ण
	ZATM_PRV_DSC(skb) = dsc;
	skb_queue_tail(&zaपंचांग_vcc->tx_queue,skb);
	DPRINTK("QRP=0x%08lx\n",zpeekl(zaपंचांग_dev,zaपंचांग_vcc->tx_chan*VC_SIZE/4+
	  uPD98401_TXVC_QRP));
	zरुको();
	zout(uPD98401_TX_READY | (zaपंचांग_vcc->tx_chan <<
	    uPD98401_CHAN_ADDR_SHIFT),CMR);
	spin_unlock_irqrestore(&zaपंचांग_dev->lock, flags);
	EVENT("done\n",0,0);
	वापस 0;
पूर्ण


अटल अंतरभूत व्योम dequeue_tx(काष्ठा aपंचांग_vcc *vcc)
अणु
	काष्ठा zaपंचांग_vcc *zaपंचांग_vcc;
	काष्ठा sk_buff *skb;

	EVENT("dequeue_tx\n",0,0);
	zaपंचांग_vcc = ZATM_VCC(vcc);
	skb = skb_dequeue(&zaपंचांग_vcc->tx_queue);
	अगर (!skb) अणु
		prपूर्णांकk(KERN_CRIT DEV_LABEL "(itf %d): dequeue_tx but not "
		    "txing\n",vcc->dev->number);
		वापस;
	पूर्ण
#अगर 0 /* @@@ would fail on CLP */
अगर (*ZATM_PRV_DSC(skb) != (uPD98401_TXPD_V | uPD98401_TXPD_DP |
  uPD98401_TXPD_SM | uPD98401_TXPD_AAL5)) prपूर्णांकk("@#*$!!!!  (%08x)\n",
  *ZATM_PRV_DSC(skb));
#पूर्ण_अगर
	*ZATM_PRV_DSC(skb) = 0; /* mark as invalid */
	zaपंचांग_vcc->txing--;
	अगर (vcc->pop) vcc->pop(vcc,skb);
	अन्यथा dev_kमुक्त_skb_irq(skb);
	जबतक ((skb = skb_dequeue(&zaपंचांग_vcc->backlog)))
		अगर (करो_tx(skb) == RING_BUSY) अणु
			skb_queue_head(&zaपंचांग_vcc->backlog,skb);
			अवरोध;
		पूर्ण
	atomic_inc(&vcc->stats->tx);
	wake_up(&zaपंचांग_vcc->tx_रुको);
पूर्ण


अटल व्योम poll_tx(काष्ठा aपंचांग_dev *dev,पूर्णांक mbx)
अणु
	काष्ठा zaपंचांग_dev *zaपंचांग_dev;
	अचिन्हित दीर्घ pos;
	u32 x;

	EVENT("poll_tx\n",0,0);
	zaपंचांग_dev = ZATM_DEV(dev);
	pos = (zaपंचांग_dev->mbx_start[mbx] & ~0xffffUL) | zin(MTA(mbx));
	जबतक (x = zin(MWA(mbx)), (pos & 0xffff) != x) अणु
		पूर्णांक chan;

#अगर 1
		u32 data,*addr;

		EVENT("MBX: host 0x%lx, nic 0x%x\n",pos,x);
		addr = (u32 *) pos;
		data = *addr;
		chan = (data & uPD98401_TXI_CONN) >> uPD98401_TXI_CONN_SHIFT;
		EVENT("addr = 0x%lx, data = 0x%08x,",(अचिन्हित दीर्घ) addr,
		    data);
		EVENT("chan = %d\n",chan,0);
#अन्यथा
NO !
		chan = (zaपंचांग_dev->mbx_start[mbx][pos >> 2] & uPD98401_TXI_CONN)
		>> uPD98401_TXI_CONN_SHIFT;
#पूर्ण_अगर
		अगर (chan < zaपंचांग_dev->chans && zaपंचांग_dev->tx_map[chan])
			dequeue_tx(zaपंचांग_dev->tx_map[chan]);
		अन्यथा अणु
			prपूर्णांकk(KERN_CRIT DEV_LABEL "(itf %d): TX indication "
			    "for non-existing channel %d\n",dev->number,chan);
			event_dump();
		पूर्ण
		अगर (((pos += 4) & 0xffff) == zaपंचांग_dev->mbx_end[mbx])
			pos = zaपंचांग_dev->mbx_start[mbx];
	पूर्ण
	zout(pos & 0xffff,MTA(mbx));
पूर्ण


/*
 * BUG BUG BUG: Doesn't handle "new-style" rate specअगरication yet.
 */

अटल पूर्णांक alloc_shaper(काष्ठा aपंचांग_dev *dev,पूर्णांक *pcr,पूर्णांक min,पूर्णांक max,पूर्णांक ubr)
अणु
	काष्ठा zaपंचांग_dev *zaपंचांग_dev;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ i,m,c;
	पूर्णांक shaper;

	DPRINTK("alloc_shaper (min = %d, max = %d)\n",min,max);
	zaपंचांग_dev = ZATM_DEV(dev);
	अगर (!zaपंचांग_dev->मुक्त_shapers) वापस -EAGAIN;
	क्रम (shaper = 0; !((zaपंचांग_dev->मुक्त_shapers >> shaper) & 1); shaper++);
	zaपंचांग_dev->मुक्त_shapers &= ~1 << shaper;
	अगर (ubr) अणु
		c = 5;
		i = m = 1;
		zaपंचांग_dev->ubr_ref_cnt++;
		zaपंचांग_dev->ubr = shaper;
		*pcr = 0;
	पूर्ण
	अन्यथा अणु
		अगर (min) अणु
			अगर (min <= 255) अणु
				i = min;
				m = ATM_OC3_PCR;
			पूर्ण
			अन्यथा अणु
				i = 255;
				m = ATM_OC3_PCR*255/min;
			पूर्ण
		पूर्ण
		अन्यथा अणु
			अगर (max > zaपंचांग_dev->tx_bw) max = zaपंचांग_dev->tx_bw;
			अगर (max <= 255) अणु
				i = max;
				m = ATM_OC3_PCR;
			पूर्ण
			अन्यथा अणु
				i = 255;
				m = DIV_ROUND_UP(ATM_OC3_PCR*255, max);
			पूर्ण
		पूर्ण
		अगर (i > m) अणु
			prपूर्णांकk(KERN_CRIT DEV_LABEL "shaper algorithm botched "
			    "[%d,%d] -> i=%ld,m=%ld\n",min,max,i,m);
			m = i;
		पूर्ण
		*pcr = i*ATM_OC3_PCR/m;
		c = 20; /* @@@ should use max_cdv ! */
		अगर ((min && *pcr < min) || (max && *pcr > max)) वापस -EINVAL;
		अगर (zaपंचांग_dev->tx_bw < *pcr) वापस -EAGAIN;
		zaपंचांग_dev->tx_bw -= *pcr;
	पूर्ण
	spin_lock_irqsave(&zaपंचांग_dev->lock, flags);
	DPRINTK("i = %d, m = %d, PCR = %d\n",i,m,*pcr);
	zpokel(zaपंचांग_dev,(i << uPD98401_IM_I_SHIFT) | m,uPD98401_IM(shaper));
	zpokel(zaपंचांग_dev,c << uPD98401_PC_C_SHIFT,uPD98401_PC(shaper));
	zpokel(zaपंचांग_dev,0,uPD98401_X(shaper));
	zpokel(zaपंचांग_dev,0,uPD98401_Y(shaper));
	zpokel(zaपंचांग_dev,uPD98401_PS_E,uPD98401_PS(shaper));
	spin_unlock_irqrestore(&zaपंचांग_dev->lock, flags);
	वापस shaper;
पूर्ण


अटल व्योम dealloc_shaper(काष्ठा aपंचांग_dev *dev,पूर्णांक shaper)
अणु
	काष्ठा zaपंचांग_dev *zaपंचांग_dev;
	अचिन्हित दीर्घ flags;

	zaपंचांग_dev = ZATM_DEV(dev);
	अगर (shaper == zaपंचांग_dev->ubr) अणु
		अगर (--zaपंचांग_dev->ubr_ref_cnt) वापस;
		zaपंचांग_dev->ubr = -1;
	पूर्ण
	spin_lock_irqsave(&zaपंचांग_dev->lock, flags);
	zpokel(zaपंचांग_dev,zpeekl(zaपंचांग_dev,uPD98401_PS(shaper)) & ~uPD98401_PS_E,
	    uPD98401_PS(shaper));
	spin_unlock_irqrestore(&zaपंचांग_dev->lock, flags);
	zaपंचांग_dev->मुक्त_shapers |= 1 << shaper;
पूर्ण


अटल व्योम बंद_tx(काष्ठा aपंचांग_vcc *vcc)
अणु
	काष्ठा zaपंचांग_dev *zaपंचांग_dev;
	काष्ठा zaपंचांग_vcc *zaपंचांग_vcc;
	अचिन्हित दीर्घ flags;
	पूर्णांक chan;

	zaपंचांग_vcc = ZATM_VCC(vcc);
	zaपंचांग_dev = ZATM_DEV(vcc->dev);
	chan = zaपंचांग_vcc->tx_chan;
	अगर (!chan) वापस;
	DPRINTK("close_tx\n");
	अगर (skb_peek(&zaपंचांग_vcc->backlog)) अणु
		prपूर्णांकk("waiting for backlog to drain ...\n");
		event_dump();
		रुको_event(zaपंचांग_vcc->tx_रुको, !skb_peek(&zaपंचांग_vcc->backlog));
	पूर्ण
	अगर (skb_peek(&zaपंचांग_vcc->tx_queue)) अणु
		prपूर्णांकk("waiting for TX queue to drain ...\n");
		event_dump();
		रुको_event(zaपंचांग_vcc->tx_रुको, !skb_peek(&zaपंचांग_vcc->tx_queue));
	पूर्ण
	spin_lock_irqsave(&zaपंचांग_dev->lock, flags);
#अगर 0
	zरुको();
	zout(uPD98401_DEACT_CHAN | (chan << uPD98401_CHAN_ADDR_SHIFT),CMR);
#पूर्ण_अगर
	zरुको();
	zout(uPD98401_CLOSE_CHAN | (chan << uPD98401_CHAN_ADDR_SHIFT),CMR);
	zरुको();
	अगर (!(zin(CMR) & uPD98401_CHAN_ADDR))
		prपूर्णांकk(KERN_CRIT DEV_LABEL "(itf %d): can't close TX channel "
		    "%d\n",vcc->dev->number,chan);
	spin_unlock_irqrestore(&zaपंचांग_dev->lock, flags);
	zaपंचांग_vcc->tx_chan = 0;
	zaपंचांग_dev->tx_map[chan] = शून्य;
	अगर (zaपंचांग_vcc->shaper != zaपंचांग_dev->ubr) अणु
		zaपंचांग_dev->tx_bw += vcc->qos.txtp.min_pcr;
		dealloc_shaper(vcc->dev,zaपंचांग_vcc->shaper);
	पूर्ण
	kमुक्त(zaपंचांग_vcc->ring);
पूर्ण


अटल पूर्णांक खोलो_tx_first(काष्ठा aपंचांग_vcc *vcc)
अणु
	काष्ठा zaपंचांग_dev *zaपंचांग_dev;
	काष्ठा zaपंचांग_vcc *zaपंचांग_vcc;
	अचिन्हित दीर्घ flags;
	u32 *loop;
	अचिन्हित लघु chan;
	पूर्णांक unlimited;

	DPRINTK("open_tx_first\n");
	zaपंचांग_dev = ZATM_DEV(vcc->dev);
	zaपंचांग_vcc = ZATM_VCC(vcc);
	zaपंचांग_vcc->tx_chan = 0;
	अगर (vcc->qos.txtp.traffic_class == ATM_NONE) वापस 0;
	spin_lock_irqsave(&zaपंचांग_dev->lock, flags);
	zरुको();
	zout(uPD98401_OPEN_CHAN,CMR);
	zरुको();
	DPRINTK("0x%x 0x%x\n",zin(CMR),zin(CER));
	chan = (zin(CMR) & uPD98401_CHAN_ADDR) >> uPD98401_CHAN_ADDR_SHIFT;
	spin_unlock_irqrestore(&zaपंचांग_dev->lock, flags);
	DPRINTK("chan is %d\n",chan);
	अगर (!chan) वापस -EAGAIN;
	unlimited = vcc->qos.txtp.traffic_class == ATM_UBR &&
	    (!vcc->qos.txtp.max_pcr || vcc->qos.txtp.max_pcr == ATM_MAX_PCR ||
	    vcc->qos.txtp.max_pcr >= ATM_OC3_PCR);
	अगर (unlimited && zaपंचांग_dev->ubr != -1) zaपंचांग_vcc->shaper = zaपंचांग_dev->ubr;
	अन्यथा अणु
		पूर्णांक pcr;

		अगर (unlimited) vcc->qos.txtp.max_sdu = ATM_MAX_AAL5_PDU;
		अगर ((zaपंचांग_vcc->shaper = alloc_shaper(vcc->dev,&pcr,
		    vcc->qos.txtp.min_pcr,vcc->qos.txtp.max_pcr,unlimited))
		    < 0) अणु
			बंद_tx(vcc);
			वापस zaपंचांग_vcc->shaper;
		पूर्ण
		अगर (pcr > ATM_OC3_PCR) pcr = ATM_OC3_PCR;
		vcc->qos.txtp.min_pcr = vcc->qos.txtp.max_pcr = pcr;
	पूर्ण
	zaपंचांग_vcc->tx_chan = chan;
	skb_queue_head_init(&zaपंचांग_vcc->tx_queue);
	init_रुकोqueue_head(&zaपंचांग_vcc->tx_रुको);
	/* initialize ring */
	zaपंचांग_vcc->ring = kzalloc(RING_SIZE,GFP_KERNEL);
	अगर (!zaपंचांग_vcc->ring) वापस -ENOMEM;
	loop = zaपंचांग_vcc->ring+RING_ENTRIES*RING_WORDS;
	loop[0] = uPD98401_TXPD_V;
	loop[1] = loop[2] = 0;
	loop[3] = virt_to_bus(zaपंचांग_vcc->ring);
	zaपंचांग_vcc->ring_curr = 0;
	zaपंचांग_vcc->txing = 0;
	skb_queue_head_init(&zaपंचांग_vcc->backlog);
	zpokel(zaपंचांग_dev,virt_to_bus(zaपंचांग_vcc->ring),
	    chan*VC_SIZE/4+uPD98401_TXVC_QRP);
	वापस 0;
पूर्ण


अटल पूर्णांक खोलो_tx_second(काष्ठा aपंचांग_vcc *vcc)
अणु
	काष्ठा zaपंचांग_dev *zaपंचांग_dev;
	काष्ठा zaपंचांग_vcc *zaपंचांग_vcc;
	अचिन्हित दीर्घ flags;

	DPRINTK("open_tx_second\n");
	zaपंचांग_dev = ZATM_DEV(vcc->dev);
	zaपंचांग_vcc = ZATM_VCC(vcc);
	अगर (!zaपंचांग_vcc->tx_chan) वापस 0;
	/* set up VC descriptor */
	spin_lock_irqsave(&zaपंचांग_dev->lock, flags);
	zpokel(zaपंचांग_dev,0,zaपंचांग_vcc->tx_chan*VC_SIZE/4);
	zpokel(zaपंचांग_dev,uPD98401_TXVC_L | (zaपंचांग_vcc->shaper <<
	    uPD98401_TXVC_SHP_SHIFT) | (vcc->vpi << uPD98401_TXVC_VPI_SHIFT) |
	    vcc->vci,zaपंचांग_vcc->tx_chan*VC_SIZE/4+1);
	zpokel(zaपंचांग_dev,0,zaपंचांग_vcc->tx_chan*VC_SIZE/4+2);
	spin_unlock_irqrestore(&zaपंचांग_dev->lock, flags);
	zaपंचांग_dev->tx_map[zaपंचांग_vcc->tx_chan] = vcc;
	वापस 0;
पूर्ण


अटल पूर्णांक start_tx(काष्ठा aपंचांग_dev *dev)
अणु
	काष्ठा zaपंचांग_dev *zaपंचांग_dev;
	पूर्णांक i;

	DPRINTK("start_tx\n");
	zaपंचांग_dev = ZATM_DEV(dev);
	zaपंचांग_dev->tx_map = kदो_स्मृति_array(zaपंचांग_dev->chans,
					 माप(*zaपंचांग_dev->tx_map),
					 GFP_KERNEL);
	अगर (!zaपंचांग_dev->tx_map) वापस -ENOMEM;
	zaपंचांग_dev->tx_bw = ATM_OC3_PCR;
	zaपंचांग_dev->मुक्त_shapers = (1 << NR_SHAPERS)-1;
	zaपंचांग_dev->ubr = -1;
	zaपंचांग_dev->ubr_ref_cnt = 0;
	/* initialize shapers */
	क्रम (i = 0; i < NR_SHAPERS; i++) zpokel(zaपंचांग_dev,0,uPD98401_PS(i));
	वापस 0;
पूर्ण


/*------------------------------- पूर्णांकerrupts --------------------------------*/


अटल irqवापस_t zaपंचांग_पूर्णांक(पूर्णांक irq,व्योम *dev_id)
अणु
	काष्ठा aपंचांग_dev *dev;
	काष्ठा zaपंचांग_dev *zaपंचांग_dev;
	u32 reason;
	पूर्णांक handled = 0;

	dev = dev_id;
	zaपंचांग_dev = ZATM_DEV(dev);
	जबतक ((reason = zin(GSR))) अणु
		handled = 1;
		EVENT("reason 0x%x\n",reason,0);
		अगर (reason & uPD98401_INT_PI) अणु
			EVENT("PHY int\n",0,0);
			dev->phy->पूर्णांकerrupt(dev);
		पूर्ण
		अगर (reason & uPD98401_INT_RQA) अणु
			अचिन्हित दीर्घ pools;
			पूर्णांक i;

			pools = zin(RQA);
			EVENT("RQA (0x%08x)\n",pools,0);
			क्रम (i = 0; pools; i++) अणु
				अगर (pools & 1) अणु
					refill_pool(dev,i);
					zaपंचांग_dev->pool_info[i].rqa_count++;
				पूर्ण
				pools >>= 1;
			पूर्ण
		पूर्ण
		अगर (reason & uPD98401_INT_RQU) अणु
			अचिन्हित दीर्घ pools;
			पूर्णांक i;
			pools = zin(RQU);
			prपूर्णांकk(KERN_WARNING DEV_LABEL "(itf %d): RQU 0x%08lx\n",
			    dev->number,pools);
			event_dump();
			क्रम (i = 0; pools; i++) अणु
				अगर (pools & 1) अणु
					refill_pool(dev,i);
					zaपंचांग_dev->pool_info[i].rqu_count++;
				पूर्ण
				pools >>= 1;
			पूर्ण
		पूर्ण
		/* करोn't handle RD */
		अगर (reason & uPD98401_INT_SPE)
			prपूर्णांकk(KERN_ALERT DEV_LABEL "(itf %d): system parity "
			    "error at 0x%08x\n",dev->number,zin(ADDR));
		अगर (reason & uPD98401_INT_CPE)
			prपूर्णांकk(KERN_ALERT DEV_LABEL "(itf %d): control memory "
			    "parity error at 0x%08x\n",dev->number,zin(ADDR));
		अगर (reason & uPD98401_INT_SBE) अणु
			prपूर्णांकk(KERN_ALERT DEV_LABEL "(itf %d): system bus "
			    "error at 0x%08x\n",dev->number,zin(ADDR));
			event_dump();
		पूर्ण
		/* करोn't handle IND */
		अगर (reason & uPD98401_INT_MF) अणु
			prपूर्णांकk(KERN_CRIT DEV_LABEL "(itf %d): mailbox full "
			    "(0x%x)\n",dev->number,(reason & uPD98401_INT_MF)
			    >> uPD98401_INT_MF_SHIFT);
			event_dump();
			    /* @@@ should try to recover */
		पूर्ण
		अगर (reason & uPD98401_INT_MM) अणु
			अगर (reason & 1) poll_rx(dev,0);
			अगर (reason & 2) poll_rx(dev,1);
			अगर (reason & 4) poll_tx(dev,2);
			अगर (reason & 8) poll_tx(dev,3);
		पूर्ण
		/* @@@ handle RCRn */
	पूर्ण
	वापस IRQ_RETVAL(handled);
पूर्ण


/*----------------------------- (E)EPROM access -----------------------------*/


अटल व्योम eprom_set(काष्ठा zaपंचांग_dev *zaपंचांग_dev, अचिन्हित दीर्घ value,
		      अचिन्हित लघु cmd)
अणु
	पूर्णांक error;

	अगर ((error = pci_ग_लिखो_config_dword(zaपंचांग_dev->pci_dev,cmd,value)))
		prपूर्णांकk(KERN_ERR DEV_LABEL ": PCI write failed (0x%02x)\n",
		    error);
पूर्ण


अटल अचिन्हित दीर्घ eprom_get(काष्ठा zaपंचांग_dev *zaपंचांग_dev, अचिन्हित लघु cmd)
अणु
	अचिन्हित पूर्णांक value;
	पूर्णांक error;

	अगर ((error = pci_पढ़ो_config_dword(zaपंचांग_dev->pci_dev,cmd,&value)))
		prपूर्णांकk(KERN_ERR DEV_LABEL ": PCI read failed (0x%02x)\n",
		    error);
	वापस value;
पूर्ण


अटल व्योम eprom_put_bits(काष्ठा zaपंचांग_dev *zaपंचांग_dev, अचिन्हित दीर्घ data,
			   पूर्णांक bits, अचिन्हित लघु cmd)
अणु
	अचिन्हित दीर्घ value;
	पूर्णांक i;

	क्रम (i = bits-1; i >= 0; i--) अणु
		value = ZEPROM_CS | (((data >> i) & 1) ? ZEPROM_DI : 0);
		eprom_set(zaपंचांग_dev,value,cmd);
		eprom_set(zaपंचांग_dev,value | ZEPROM_SK,cmd);
		eprom_set(zaपंचांग_dev,value,cmd);
	पूर्ण
पूर्ण


अटल व्योम eprom_get_byte(काष्ठा zaपंचांग_dev *zaपंचांग_dev, अचिन्हित अक्षर *byte,
			   अचिन्हित लघु cmd)
अणु
	पूर्णांक i;

	*byte = 0;
	क्रम (i = 8; i; i--) अणु
		eprom_set(zaपंचांग_dev,ZEPROM_CS,cmd);
		eprom_set(zaपंचांग_dev,ZEPROM_CS | ZEPROM_SK,cmd);
		*byte <<= 1;
		अगर (eprom_get(zaपंचांग_dev,cmd) & ZEPROM_DO) *byte |= 1;
		eprom_set(zaपंचांग_dev,ZEPROM_CS,cmd);
	पूर्ण
पूर्ण


अटल पूर्णांक eprom_try_esi(काष्ठा aपंचांग_dev *dev, अचिन्हित लघु cmd, पूर्णांक offset,
			 पूर्णांक swap)
अणु
	अचिन्हित अक्षर buf[ZEPROM_SIZE];
	काष्ठा zaपंचांग_dev *zaपंचांग_dev;
	पूर्णांक i;

	zaपंचांग_dev = ZATM_DEV(dev);
	क्रम (i = 0; i < ZEPROM_SIZE; i += 2) अणु
		eprom_set(zaपंचांग_dev,ZEPROM_CS,cmd); /* select EPROM */
		eprom_put_bits(zaपंचांग_dev,ZEPROM_CMD_READ,ZEPROM_CMD_LEN,cmd);
		eprom_put_bits(zaपंचांग_dev,i >> 1,ZEPROM_ADDR_LEN,cmd);
		eprom_get_byte(zaपंचांग_dev,buf+i+swap,cmd);
		eprom_get_byte(zaपंचांग_dev,buf+i+1-swap,cmd);
		eprom_set(zaपंचांग_dev,0,cmd); /* deselect EPROM */
	पूर्ण
	स_नकल(dev->esi,buf+offset,ESI_LEN);
	वापस स_भेद(dev->esi,"\0\0\0\0\0",ESI_LEN); /* assumes ESI_LEN == 6 */
पूर्ण


अटल व्योम eprom_get_esi(काष्ठा aपंचांग_dev *dev)
अणु
	अगर (eprom_try_esi(dev,ZEPROM_V1_REG,ZEPROM_V1_ESI_OFF,1)) वापस;
	(व्योम) eprom_try_esi(dev,ZEPROM_V2_REG,ZEPROM_V2_ESI_OFF,0);
पूर्ण


/*--------------------------------- entries ---------------------------------*/


अटल पूर्णांक zaपंचांग_init(काष्ठा aपंचांग_dev *dev)
अणु
	काष्ठा zaपंचांग_dev *zaपंचांग_dev;
	काष्ठा pci_dev *pci_dev;
	अचिन्हित लघु command;
	पूर्णांक error,i,last;
	अचिन्हित दीर्घ t0,t1,t2;

	DPRINTK(">zatm_init\n");
	zaपंचांग_dev = ZATM_DEV(dev);
	spin_lock_init(&zaपंचांग_dev->lock);
	pci_dev = zaपंचांग_dev->pci_dev;
	zaपंचांग_dev->base = pci_resource_start(pci_dev, 0);
	zaपंचांग_dev->irq = pci_dev->irq;
	अगर ((error = pci_पढ़ो_config_word(pci_dev,PCI_COMMAND,&command))) अणु
		prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): init error 0x%02x\n",
		    dev->number,error);
		वापस -EINVAL;
	पूर्ण
	अगर ((error = pci_ग_लिखो_config_word(pci_dev,PCI_COMMAND,
	    command | PCI_COMMAND_IO | PCI_COMMAND_MASTER))) अणु
		prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): can't enable IO (0x%02x)"
		    "\n",dev->number,error);
		वापस -EIO;
	पूर्ण
	eprom_get_esi(dev);
	prपूर्णांकk(KERN_NOTICE DEV_LABEL "(itf %d): rev.%d,base=0x%x,irq=%d,",
	    dev->number,pci_dev->revision,zaपंचांग_dev->base,zaपंचांग_dev->irq);
	/* reset uPD98401 */
	zout(0,SWR);
	जबतक (!(zin(GSR) & uPD98401_INT_IND));
	zout(uPD98401_GMR_ONE /*uPD98401_BURST4*/,GMR);
	last = MAX_CRAM_SIZE;
	क्रम (i = last-RAM_INCREMENT; i >= 0; i -= RAM_INCREMENT) अणु
		zpokel(zaपंचांग_dev,0x55555555,i);
		अगर (zpeekl(zaपंचांग_dev,i) != 0x55555555) last = i;
		अन्यथा अणु
			zpokel(zaपंचांग_dev,0xAAAAAAAA,i);
			अगर (zpeekl(zaपंचांग_dev,i) != 0xAAAAAAAA) last = i;
			अन्यथा zpokel(zaपंचांग_dev,i,i);
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < last; i += RAM_INCREMENT)
		अगर (zpeekl(zaपंचांग_dev,i) != i) अवरोध;
	zaपंचांग_dev->mem = i << 2;
	जबतक (i) zpokel(zaपंचांग_dev,0,--i);
	/* reset again to rebuild memory poपूर्णांकers */
	zout(0,SWR);
	जबतक (!(zin(GSR) & uPD98401_INT_IND));
	zout(uPD98401_GMR_ONE | uPD98401_BURST8 | uPD98401_BURST4 |
	    uPD98401_BURST2 | uPD98401_GMR_PM | uPD98401_GMR_DR,GMR);
	/* TODO: should shrink allocation now */
	prपूर्णांकk("mem=%dkB,%s (",zaपंचांग_dev->mem >> 10,zaपंचांग_dev->copper ? "UTP" :
	    "MMF");
	क्रम (i = 0; i < ESI_LEN; i++)
		prपूर्णांकk("%02X%s",dev->esi[i],i == ESI_LEN-1 ? ")\n" : "-");
	करो अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&zaपंचांग_dev->lock, flags);
		t0 = zpeekl(zaपंचांग_dev,uPD98401_TSR);
		udelay(10);
		t1 = zpeekl(zaपंचांग_dev,uPD98401_TSR);
		udelay(1010);
		t2 = zpeekl(zaपंचांग_dev,uPD98401_TSR);
		spin_unlock_irqrestore(&zaपंचांग_dev->lock, flags);
	पूर्ण
	जबतक (t0 > t1 || t1 > t2); /* loop अगर wrapping ... */
	zaपंचांग_dev->khz = t2-2*t1+t0;
	prपूर्णांकk(KERN_NOTICE DEV_LABEL "(itf %d): uPD98401 %d.%d at %d.%03d "
	    "MHz\n",dev->number,
	    (zin(VER) & uPD98401_MAJOR) >> uPD98401_MAJOR_SHIFT,
            zin(VER) & uPD98401_MINOR,zaपंचांग_dev->khz/1000,zaपंचांग_dev->khz % 1000);
	वापस uPD98402_init(dev);
पूर्ण


अटल पूर्णांक zaपंचांग_start(काष्ठा aपंचांग_dev *dev)
अणु
	काष्ठा zaपंचांग_dev *zaपंचांग_dev = ZATM_DEV(dev);
	काष्ठा pci_dev *pdev = zaपंचांग_dev->pci_dev;
	अचिन्हित दीर्घ curr;
	पूर्णांक pools,vccs,rx;
	पूर्णांक error, i, ld;

	DPRINTK("zatm_start\n");
	zaपंचांग_dev->rx_map = zaपंचांग_dev->tx_map = शून्य;
 	क्रम (i = 0; i < NR_MBX; i++)
 		zaपंचांग_dev->mbx_start[i] = 0;
 	error = request_irq(zaपंचांग_dev->irq, zaपंचांग_पूर्णांक, IRQF_SHARED, DEV_LABEL, dev);
	अगर (error < 0) अणु
 		prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): IRQ%d is already in use\n",
 		    dev->number,zaपंचांग_dev->irq);
		जाओ करोne;
	पूर्ण
	/* define memory regions */
	pools = NR_POOLS;
	अगर (NR_SHAPERS*SHAPER_SIZE > pools*POOL_SIZE)
		pools = NR_SHAPERS*SHAPER_SIZE/POOL_SIZE;
	vccs = (zaपंचांग_dev->mem-NR_SHAPERS*SHAPER_SIZE-pools*POOL_SIZE)/
	    (2*VC_SIZE+RX_SIZE);
	ld = -1;
	क्रम (rx = 1; rx < vccs; rx <<= 1) ld++;
	dev->ci_range.vpi_bits = 0; /* @@@ no VPI क्रम now */
	dev->ci_range.vci_bits = ld;
	dev->link_rate = ATM_OC3_PCR;
	zaपंचांग_dev->chans = vccs; /* ??? */
	curr = rx*RX_SIZE/4;
	DPRINTK("RX pool 0x%08lx\n",curr);
	zpokel(zaपंचांग_dev,curr,uPD98401_PMA); /* receive pool */
	zaपंचांग_dev->pool_base = curr;
	curr += pools*POOL_SIZE/4;
	DPRINTK("Shapers 0x%08lx\n",curr);
	zpokel(zaपंचांग_dev,curr,uPD98401_SMA); /* shapers */
	curr += NR_SHAPERS*SHAPER_SIZE/4;
	DPRINTK("Free    0x%08lx\n",curr);
	zpokel(zaपंचांग_dev,curr,uPD98401_TOS); /* मुक्त pool */
	prपूर्णांकk(KERN_INFO DEV_LABEL "(itf %d): %d shapers, %d pools, %d RX, "
	    "%ld VCs\n",dev->number,NR_SHAPERS,pools,rx,
	    (zaपंचांग_dev->mem-curr*4)/VC_SIZE);
	/* create mailboxes */
	क्रम (i = 0; i < NR_MBX; i++) अणु
		व्योम *mbx;
		dma_addr_t mbx_dma;

		अगर (!mbx_entries[i])
			जारी;
		mbx = dma_alloc_coherent(&pdev->dev,
					 2 * MBX_SIZE(i), &mbx_dma, GFP_KERNEL);
		अगर (!mbx) अणु
			error = -ENOMEM;
			जाओ out;
		पूर्ण
		/*
		 * Alignment provided by dma_alloc_coherent() isn't enough
		 * क्रम this device.
		 */
		अगर (((अचिन्हित दीर्घ)mbx ^ mbx_dma) & 0xffff) अणु
			prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): system "
			       "bus incompatible with driver\n", dev->number);
			dma_मुक्त_coherent(&pdev->dev, 2*MBX_SIZE(i), mbx, mbx_dma);
			error = -ENODEV;
			जाओ out;
		पूर्ण
		DPRINTK("mbx@0x%08lx-0x%08lx\n", mbx, mbx + MBX_SIZE(i));
		zaपंचांग_dev->mbx_start[i] = (अचिन्हित दीर्घ)mbx;
		zaपंचांग_dev->mbx_dma[i] = mbx_dma;
		zaपंचांग_dev->mbx_end[i] = (zaपंचांग_dev->mbx_start[i] + MBX_SIZE(i)) &
					0xffff;
		zout(mbx_dma >> 16, MSH(i));
		zout(mbx_dma, MSL(i));
		zout(zaपंचांग_dev->mbx_end[i], MBA(i));
		zout((अचिन्हित दीर्घ)mbx & 0xffff, MTA(i));
		zout((अचिन्हित दीर्घ)mbx & 0xffff, MWA(i));
	पूर्ण
	error = start_tx(dev);
	अगर (error)
		जाओ out;
	error = start_rx(dev);
	अगर (error)
		जाओ out_tx;
	error = dev->phy->start(dev);
	अगर (error)
		जाओ out_rx;
	zout(0xffffffff,IMR); /* enable पूर्णांकerrupts */
	/* enable TX & RX */
	zout(zin(GMR) | uPD98401_GMR_SE | uPD98401_GMR_RE,GMR);
करोne:
	वापस error;

out_rx:
	kमुक्त(zaपंचांग_dev->rx_map);
out_tx:
	kमुक्त(zaपंचांग_dev->tx_map);
out:
	जबतक (i-- > 0) अणु
		dma_मुक्त_coherent(&pdev->dev, 2 * MBX_SIZE(i),
				  (व्योम *)zaपंचांग_dev->mbx_start[i],
				  zaपंचांग_dev->mbx_dma[i]);
	पूर्ण
	मुक्त_irq(zaपंचांग_dev->irq, dev);
	जाओ करोne;
पूर्ण


अटल व्योम zaपंचांग_बंद(काष्ठा aपंचांग_vcc *vcc)
अणु
        DPRINTK(">zatm_close\n");
        अगर (!ZATM_VCC(vcc)) वापस;
	clear_bit(ATM_VF_READY,&vcc->flags);
        बंद_rx(vcc);
	EVENT("close_tx\n",0,0);
        बंद_tx(vcc);
        DPRINTK("zatm_close: done waiting\n");
        /* deallocate memory */
        kमुक्त(ZATM_VCC(vcc));
	vcc->dev_data = शून्य;
	clear_bit(ATM_VF_ADDR,&vcc->flags);
पूर्ण


अटल पूर्णांक zaपंचांग_खोलो(काष्ठा aपंचांग_vcc *vcc)
अणु
	काष्ठा zaपंचांग_vcc *zaपंचांग_vcc;
	लघु vpi = vcc->vpi;
	पूर्णांक vci = vcc->vci;
	पूर्णांक error;

	DPRINTK(">zatm_open\n");
	अगर (!test_bit(ATM_VF_PARTIAL,&vcc->flags))
		vcc->dev_data = शून्य;
	अगर (vci != ATM_VPI_UNSPEC && vpi != ATM_VCI_UNSPEC)
		set_bit(ATM_VF_ADDR,&vcc->flags);
	अगर (vcc->qos.aal != ATM_AAL5) वापस -EINVAL; /* @@@ AAL0 */
	DPRINTK(DEV_LABEL "(itf %d): open %d.%d\n",vcc->dev->number,vcc->vpi,
	    vcc->vci);
	अगर (!test_bit(ATM_VF_PARTIAL,&vcc->flags)) अणु
		zaपंचांग_vcc = kदो_स्मृति(माप(*zaपंचांग_vcc), GFP_KERNEL);
		अगर (!zaपंचांग_vcc) अणु
			clear_bit(ATM_VF_ADDR,&vcc->flags);
			वापस -ENOMEM;
		पूर्ण
		vcc->dev_data = zaपंचांग_vcc;
		ZATM_VCC(vcc)->tx_chan = 0; /* क्रम zaपंचांग_बंद after खोलो_rx */
		अगर ((error = खोलो_rx_first(vcc))) अणु
	                zaपंचांग_बंद(vcc);
	                वापस error;
	        पूर्ण
		अगर ((error = खोलो_tx_first(vcc))) अणु
			zaपंचांग_बंद(vcc);
			वापस error;
	        पूर्ण
	पूर्ण
	अगर (vci == ATM_VPI_UNSPEC || vpi == ATM_VCI_UNSPEC) वापस 0;
	अगर ((error = खोलो_rx_second(vcc))) अणु
		zaपंचांग_बंद(vcc);
		वापस error;
        पूर्ण
	अगर ((error = खोलो_tx_second(vcc))) अणु
		zaपंचांग_बंद(vcc);
		वापस error;
        पूर्ण
	set_bit(ATM_VF_READY,&vcc->flags);
        वापस 0;
पूर्ण


अटल पूर्णांक zaपंचांग_change_qos(काष्ठा aपंचांग_vcc *vcc,काष्ठा aपंचांग_qos *qos,पूर्णांक flags)
अणु
	prपूर्णांकk("Not yet implemented\n");
	वापस -ENOSYS;
	/* @@@ */
पूर्ण


अटल पूर्णांक zaपंचांग_ioctl(काष्ठा aपंचांग_dev *dev,अचिन्हित पूर्णांक cmd,व्योम __user *arg)
अणु
	काष्ठा zaपंचांग_dev *zaपंचांग_dev;
	अचिन्हित दीर्घ flags;

	zaपंचांग_dev = ZATM_DEV(dev);
	चयन (cmd) अणु
		हाल ZATM_GETPOOLZ:
			अगर (!capable(CAP_NET_ADMIN)) वापस -EPERM;
			fallthrough;
		हाल ZATM_GETPOOL:
			अणु
				काष्ठा zaपंचांग_pool_info info;
				पूर्णांक pool;

				अगर (get_user(pool,
				    &((काष्ठा zaपंचांग_pool_req __user *) arg)->pool_num))
					वापस -EFAULT;
				अगर (pool < 0 || pool > ZATM_LAST_POOL)
					वापस -EINVAL;
				pool = array_index_nospec(pool,
							  ZATM_LAST_POOL + 1);
				spin_lock_irqsave(&zaपंचांग_dev->lock, flags);
				info = zaपंचांग_dev->pool_info[pool];
				अगर (cmd == ZATM_GETPOOLZ) अणु
					zaपंचांग_dev->pool_info[pool].rqa_count = 0;
					zaपंचांग_dev->pool_info[pool].rqu_count = 0;
				पूर्ण
				spin_unlock_irqrestore(&zaपंचांग_dev->lock, flags);
				वापस copy_to_user(
				    &((काष्ठा zaपंचांग_pool_req __user *) arg)->info,
				    &info,माप(info)) ? -EFAULT : 0;
			पूर्ण
		हाल ZATM_SETPOOL:
			अणु
				काष्ठा zaपंचांग_pool_info info;
				पूर्णांक pool;

				अगर (!capable(CAP_NET_ADMIN)) वापस -EPERM;
				अगर (get_user(pool,
				    &((काष्ठा zaपंचांग_pool_req __user *) arg)->pool_num))
					वापस -EFAULT;
				अगर (pool < 0 || pool > ZATM_LAST_POOL)
					वापस -EINVAL;
				pool = array_index_nospec(pool,
							  ZATM_LAST_POOL + 1);
				अगर (copy_from_user(&info,
				    &((काष्ठा zaपंचांग_pool_req __user *) arg)->info,
				    माप(info))) वापस -EFAULT;
				अगर (!info.low_water)
					info.low_water = zaपंचांग_dev->
					    pool_info[pool].low_water;
				अगर (!info.high_water)
					info.high_water = zaपंचांग_dev->
					    pool_info[pool].high_water;
				अगर (!info.next_thres)
					info.next_thres = zaपंचांग_dev->
					    pool_info[pool].next_thres;
				अगर (info.low_water >= info.high_water ||
				    info.low_water < 0)
					वापस -EINVAL;
				spin_lock_irqsave(&zaपंचांग_dev->lock, flags);
				zaपंचांग_dev->pool_info[pool].low_water =
				    info.low_water;
				zaपंचांग_dev->pool_info[pool].high_water =
				    info.high_water;
				zaपंचांग_dev->pool_info[pool].next_thres =
				    info.next_thres;
				spin_unlock_irqrestore(&zaपंचांग_dev->lock, flags);
				वापस 0;
			पूर्ण
		शेष:
        		अगर (!dev->phy->ioctl) वापस -ENOIOCTLCMD;
		        वापस dev->phy->ioctl(dev,cmd,arg);
	पूर्ण
पूर्ण

अटल पूर्णांक zaपंचांग_send(काष्ठा aपंचांग_vcc *vcc,काष्ठा sk_buff *skb)
अणु
	पूर्णांक error;

	EVENT(">zatm_send 0x%lx\n",(अचिन्हित दीर्घ) skb,0);
	अगर (!ZATM_VCC(vcc)->tx_chan || !test_bit(ATM_VF_READY,&vcc->flags)) अणु
		अगर (vcc->pop) vcc->pop(vcc,skb);
		अन्यथा dev_kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण
	अगर (!skb) अणु
		prपूर्णांकk(KERN_CRIT "!skb in zatm_send ?\n");
		अगर (vcc->pop) vcc->pop(vcc,skb);
		वापस -EINVAL;
	पूर्ण
	ATM_SKB(skb)->vcc = vcc;
	error = करो_tx(skb);
	अगर (error != RING_BUSY) वापस error;
	skb_queue_tail(&ZATM_VCC(vcc)->backlog,skb);
	वापस 0;
पूर्ण


अटल व्योम zaपंचांग_phy_put(काष्ठा aपंचांग_dev *dev,अचिन्हित अक्षर value,
    अचिन्हित दीर्घ addr)
अणु
	काष्ठा zaपंचांग_dev *zaपंचांग_dev;

	zaपंचांग_dev = ZATM_DEV(dev);
	zरुको();
	zout(value,CER);
	zout(uPD98401_IND_ACC | uPD98401_IA_B0 |
	    (uPD98401_IA_TGT_PHY << uPD98401_IA_TGT_SHIFT) | addr,CMR);
पूर्ण


अटल अचिन्हित अक्षर zaपंचांग_phy_get(काष्ठा aपंचांग_dev *dev,अचिन्हित दीर्घ addr)
अणु
	काष्ठा zaपंचांग_dev *zaपंचांग_dev;

	zaपंचांग_dev = ZATM_DEV(dev);
	zरुको();
	zout(uPD98401_IND_ACC | uPD98401_IA_B0 | uPD98401_IA_RW |
	  (uPD98401_IA_TGT_PHY << uPD98401_IA_TGT_SHIFT) | addr,CMR);
	zरुको();
	वापस zin(CER) & 0xff;
पूर्ण


अटल स्थिर काष्ठा aपंचांगdev_ops ops = अणु
	.खोलो		= zaपंचांग_खोलो,
	.बंद		= zaपंचांग_बंद,
	.ioctl		= zaपंचांग_ioctl,
	.send		= zaपंचांग_send,
	.phy_put	= zaपंचांग_phy_put,
	.phy_get	= zaपंचांग_phy_get,
	.change_qos	= zaपंचांग_change_qos,
पूर्ण;

अटल पूर्णांक zaपंचांग_init_one(काष्ठा pci_dev *pci_dev,
			 स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा aपंचांग_dev *dev;
	काष्ठा zaपंचांग_dev *zaपंचांग_dev;
	पूर्णांक ret = -ENOMEM;

	zaपंचांग_dev = kदो_स्मृति(माप(*zaपंचांग_dev), GFP_KERNEL);
	अगर (!zaपंचांग_dev) अणु
		prपूर्णांकk(KERN_EMERG "%s: memory shortage\n", DEV_LABEL);
		जाओ out;
	पूर्ण

	dev = aपंचांग_dev_रेजिस्टर(DEV_LABEL, &pci_dev->dev, &ops, -1, शून्य);
	अगर (!dev)
		जाओ out_मुक्त;

	ret = pci_enable_device(pci_dev);
	अगर (ret < 0)
		जाओ out_deरेजिस्टर;

	ret = pci_request_regions(pci_dev, DEV_LABEL);
	अगर (ret < 0)
		जाओ out_disable;

	ret = dma_set_mask_and_coherent(&pci_dev->dev, DMA_BIT_MASK(32));
	अगर (ret < 0)
		जाओ out_release;

	zaपंचांग_dev->pci_dev = pci_dev;
	dev->dev_data = zaपंचांग_dev;
	zaपंचांग_dev->copper = (पूर्णांक)ent->driver_data;
	अगर ((ret = zaपंचांग_init(dev)) || (ret = zaपंचांग_start(dev)))
		जाओ out_release;

	pci_set_drvdata(pci_dev, dev);
	zaपंचांग_dev->more = zaपंचांग_boards;
	zaपंचांग_boards = dev;
	ret = 0;
out:
	वापस ret;

out_release:
	pci_release_regions(pci_dev);
out_disable:
	pci_disable_device(pci_dev);
out_deरेजिस्टर:
	aपंचांग_dev_deरेजिस्टर(dev);
out_मुक्त:
	kमुक्त(zaपंचांग_dev);
	जाओ out;
पूर्ण


MODULE_LICENSE("GPL");

अटल स्थिर काष्ठा pci_device_id zaपंचांग_pci_tbl[] = अणु
	अणु PCI_VDEVICE(ZEITNET, PCI_DEVICE_ID_ZEITNET_1221), ZATM_COPPER पूर्ण,
	अणु PCI_VDEVICE(ZEITNET, PCI_DEVICE_ID_ZEITNET_1225), 0 पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, zaपंचांग_pci_tbl);

अटल काष्ठा pci_driver zaपंचांग_driver = अणु
	.name =		DEV_LABEL,
	.id_table =	zaपंचांग_pci_tbl,
	.probe =	zaपंचांग_init_one,
पूर्ण;

अटल पूर्णांक __init zaपंचांग_init_module(व्योम)
अणु
	वापस pci_रेजिस्टर_driver(&zaपंचांग_driver);
पूर्ण

module_init(zaपंचांग_init_module);
/* module_निकास not defined so not unloadable */
