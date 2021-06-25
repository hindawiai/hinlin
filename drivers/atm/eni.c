<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* drivers/aपंचांग/eni.c - Efficient Networks ENI155P device driver */
 
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
#समावेश <linux/समय.स>
#समावेश <linux/delay.h>
#समावेश <linux/uपन.स>
#समावेश <linux/init.h>
#समावेश <linux/aपंचांग_eni.h>
#समावेश <linux/bitops.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/atomic.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/माला.स>
#समावेश <यंत्र/byteorder.h>

#समावेश "tonga.h"
#समावेश "midway.h"
#समावेश "suni.h"
#समावेश "eni.h"

/*
 * TODO:
 *
 * Show stoppers
 *  none
 *
 * Minor
 *  - OAM support
 *  - fix bugs listed below
 */

/*
 * KNOWN BUGS:
 *
 * - may run पूर्णांकo JK-JK bug and deadlock
 * - should allocate UBR channel first
 * - buffer space allocation algorithm is stupid
 *   (RX: should be maxSDU+maxdelay*rate
 *    TX: should be maxSDU+min(maxSDU,maxdelay*rate) )
 * - करोesn't support OAM cells
 * - eni_put_मुक्त may hang अगर not putting memory fragments that _complete_
 *   2^n block (never happens in real lअगरe, though)
 */


#अगर 0
#घोषणा DPRINTK(क्रमmat,args...) prपूर्णांकk(KERN_DEBUG क्रमmat,##args)
#अन्यथा
#घोषणा DPRINTK(क्रमmat,args...)
#पूर्ण_अगर


#अगर_अघोषित CONFIG_ATM_ENI_TUNE_BURST
#घोषणा CONFIG_ATM_ENI_BURST_TX_8W
#घोषणा CONFIG_ATM_ENI_BURST_RX_4W
#पूर्ण_अगर


#अगर_अघोषित CONFIG_ATM_ENI_DEBUG


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
	अगर ((अचिन्हित दीर्घ) (x) < 0x30) \
		prपूर्णांकk(KERN_CRIT #x "==0x%lx\n",(अचिन्हित दीर्घ) (x))

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

	क्रम (n = 0; n < EV; n++) अणु
		i = (ec+n) % EV;
		prपूर्णांकk(KERN_NOTICE);
		prपूर्णांकk(ev[i] ? ev[i] : "(null)",ev_a[i],ev_b[i]);
	पूर्ण
पूर्ण


#पूर्ण_अगर /* CONFIG_ATM_ENI_DEBUG */


/*
 * NExx   must not be equal at end
 * EExx   may be equal at end
 * xxPJOK verअगरy validity of poपूर्णांकer jumps
 * xxPMOK operating on a circular buffer of "c" words
 */

#घोषणा NEPJOK(a0,a1,b) \
    ((a0) < (a1) ? (b) <= (a0) || (b) > (a1) : (b) <= (a0) && (b) > (a1))
#घोषणा EEPJOK(a0,a1,b) \
    ((a0) < (a1) ? (b) < (a0) || (b) >= (a1) : (b) < (a0) && (b) >= (a1))
#घोषणा NEPMOK(a0,d,b,c) NEPJOK(a0,(a0+d) & (c-1),b)
#घोषणा EEPMOK(a0,d,b,c) EEPJOK(a0,(a0+d) & (c-1),b)


अटल पूर्णांक tx_complete = 0,dma_complete = 0,queued = 0,requeued = 0,
  backlogged = 0,rx_enqueued = 0,rx_dequeued = 0,pushed = 0,submitted = 0,
  putting = 0;

अटल काष्ठा aपंचांग_dev *eni_boards = शून्य;

/* Read/ग_लिखो रेजिस्टरs on card */
#घोषणा eni_in(r)	पढ़ोl(eni_dev->reg+(r)*4)
#घोषणा eni_out(v,r)	ग_लिखोl((v),eni_dev->reg+(r)*4)


/*-------------------------------- utilities --------------------------------*/


अटल व्योम dump_mem(काष्ठा eni_dev *eni_dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < eni_dev->मुक्त_len; i++)
		prपूर्णांकk(KERN_DEBUG "  %d: %p %d\n",i,
		    eni_dev->मुक्त_list[i].start,
		    1 << eni_dev->मुक्त_list[i].order);
पूर्ण


अटल व्योम dump(काष्ठा aपंचांग_dev *dev)
अणु
	काष्ठा eni_dev *eni_dev;

	पूर्णांक i;

	eni_dev = ENI_DEV(dev);
	prपूर्णांकk(KERN_NOTICE "Free memory\n");
	dump_mem(eni_dev);
	prपूर्णांकk(KERN_NOTICE "TX buffers\n");
	क्रम (i = 0; i < NR_CHAN; i++)
		अगर (eni_dev->tx[i].send)
			prपूर्णांकk(KERN_NOTICE "  TX %d @ %p: %ld\n",i,
			    eni_dev->tx[i].send,eni_dev->tx[i].words*4);
	prपूर्णांकk(KERN_NOTICE "RX buffers\n");
	क्रम (i = 0; i < 1024; i++)
		अगर (eni_dev->rx_map[i] && ENI_VCC(eni_dev->rx_map[i])->rx)
			prपूर्णांकk(KERN_NOTICE "  RX %d @ %p: %ld\n",i,
			    ENI_VCC(eni_dev->rx_map[i])->recv,
			    ENI_VCC(eni_dev->rx_map[i])->words*4);
	prपूर्णांकk(KERN_NOTICE "----\n");
पूर्ण


अटल व्योम eni_put_मुक्त(काष्ठा eni_dev *eni_dev, व्योम __iomem *start,
    अचिन्हित दीर्घ size)
अणु
	काष्ठा eni_मुक्त *list;
	पूर्णांक len,order;

	DPRINTK("init 0x%lx+%ld(0x%lx)\n",start,size,size);
	start += eni_dev->base_dअगरf;
	list = eni_dev->मुक्त_list;
	len = eni_dev->मुक्त_len;
	जबतक (size) अणु
		अगर (len >= eni_dev->मुक्त_list_size) अणु
			prपूर्णांकk(KERN_CRIT "eni_put_free overflow (%p,%ld)\n",
			    start,size);
			अवरोध;
		पूर्ण
		क्रम (order = 0; !(((अचिन्हित दीर्घ)start | size) & (1 << order)); order++);
		अगर (MID_MIN_BUF_SIZE > (1 << order)) अणु
			prपूर्णांकk(KERN_CRIT "eni_put_free: order %d too small\n",
			    order);
			अवरोध;
		पूर्ण
		list[len].start = (व्योम __iomem *) start;
		list[len].order = order;
		len++;
		start += 1 << order;
		size -= 1 << order;
	पूर्ण
	eni_dev->मुक्त_len = len;
	/*dump_mem(eni_dev);*/
पूर्ण


अटल व्योम __iomem *eni_alloc_mem(काष्ठा eni_dev *eni_dev, अचिन्हित दीर्घ *size)
अणु
	काष्ठा eni_मुक्त *list;
	व्योम __iomem *start;
	पूर्णांक len,i,order,best_order,index;

	list = eni_dev->मुक्त_list;
	len = eni_dev->मुक्त_len;
	अगर (*size < MID_MIN_BUF_SIZE) *size = MID_MIN_BUF_SIZE;
	अगर (*size > MID_MAX_BUF_SIZE) वापस शून्य;
	क्रम (order = 0; (1 << order) < *size; order++)
		;
	DPRINTK("trying: %ld->%d\n",*size,order);
	best_order = 65; /* we करोn't have more than 2^64 of anything ... */
	index = 0; /* silence GCC */
	क्रम (i = 0; i < len; i++)
		अगर (list[i].order == order) अणु
			best_order = order;
			index = i;
			अवरोध;
		पूर्ण
		अन्यथा अगर (best_order > list[i].order && list[i].order > order) अणु
				best_order = list[i].order;
				index = i;
			पूर्ण
	अगर (best_order == 65) वापस शून्य;
	start = list[index].start-eni_dev->base_dअगरf;
	list[index] = list[--len];
	eni_dev->मुक्त_len = len;
	*size = 1 << order;
	eni_put_मुक्त(eni_dev,start+*size,(1 << best_order)-*size);
	DPRINTK("%ld bytes (order %d) at 0x%lx\n",*size,order,start);
	स_रखो_io(start,0,*size);       /* never leak data */
	/*dump_mem(eni_dev);*/
	वापस start;
पूर्ण


अटल व्योम eni_मुक्त_mem(काष्ठा eni_dev *eni_dev, व्योम __iomem *start,
    अचिन्हित दीर्घ size)
अणु
	काष्ठा eni_मुक्त *list;
	पूर्णांक len,i,order;

	start += eni_dev->base_dअगरf;
	list = eni_dev->मुक्त_list;
	len = eni_dev->मुक्त_len;
	क्रम (order = -1; size; order++) size >>= 1;
	DPRINTK("eni_free_mem: %p+0x%lx (order %d)\n",start,size,order);
	क्रम (i = 0; i < len; i++)
		अगर (((अचिन्हित दीर्घ) list[i].start) == ((अचिन्हित दीर्घ)start^(1 << order)) &&
		    list[i].order == order) अणु
			DPRINTK("match[%d]: 0x%lx/0x%lx(0x%x), %d/%d\n",i,
			    list[i].start,start,1 << order,list[i].order,order);
			list[i] = list[--len];
			start = (व्योम __iomem *) ((अचिन्हित दीर्घ) start & ~(अचिन्हित दीर्घ) (1 << order));
			order++;
			i = -1;
			जारी;
		पूर्ण
	अगर (len >= eni_dev->मुक्त_list_size) अणु
		prपूर्णांकk(KERN_ALERT "eni_free_mem overflow (%p,%d)\n",start,
		    order);
		वापस;
	पूर्ण
	list[len].start = start;
	list[len].order = order;
	eni_dev->मुक्त_len = len+1;
	/*dump_mem(eni_dev);*/
पूर्ण


/*----------------------------------- RX ------------------------------------*/


#घोषणा ENI_VCC_NOS ((काष्ठा aपंचांग_vcc *) 1)


अटल व्योम rx_ident_err(काष्ठा aपंचांग_vcc *vcc)
अणु
	काष्ठा aपंचांग_dev *dev;
	काष्ठा eni_dev *eni_dev;
	काष्ठा eni_vcc *eni_vcc;

	dev = vcc->dev;
	eni_dev = ENI_DEV(dev);
	/* immediately halt adapter */
	eni_out(eni_in(MID_MC_S) &
	    ~(MID_DMA_ENABLE | MID_TX_ENABLE | MID_RX_ENABLE),MID_MC_S);
	/* dump useful inक्रमmation */
	eni_vcc = ENI_VCC(vcc);
	prपूर्णांकk(KERN_ALERT DEV_LABEL "(itf %d): driver error - RX ident "
	    "mismatch\n",dev->number);
	prपूर्णांकk(KERN_ALERT "  VCI %d, rxing %d, words %ld\n",vcc->vci,
	    eni_vcc->rxing,eni_vcc->words);
	prपूर्णांकk(KERN_ALERT "  host descr 0x%lx, rx pos 0x%lx, descr value "
	    "0x%x\n",eni_vcc->descr,eni_vcc->rx_pos,
	    (अचिन्हित) पढ़ोl(eni_vcc->recv+eni_vcc->descr*4));
	prपूर्णांकk(KERN_ALERT "  last %p, servicing %d\n",eni_vcc->last,
	    eni_vcc->servicing);
	EVENT("---dump ends here---\n",0,0);
	prपूर्णांकk(KERN_NOTICE "---recent events---\n");
	event_dump();
	ENI_DEV(dev)->fast = शून्य; /* really stop it */
	ENI_DEV(dev)->slow = शून्य;
	skb_queue_head_init(&ENI_DEV(dev)->rx_queue);
पूर्ण


अटल पूर्णांक करो_rx_dma(काष्ठा aपंचांग_vcc *vcc,काष्ठा sk_buff *skb,
    अचिन्हित दीर्घ skip,अचिन्हित दीर्घ size,अचिन्हित दीर्घ eff)
अणु
	काष्ठा eni_dev *eni_dev;
	काष्ठा eni_vcc *eni_vcc;
	u32 dma_rd,dma_wr;
	u32 dma[RX_DMA_BUF*2];
	dma_addr_t paddr;
	अचिन्हित दीर्घ here;
	पूर्णांक i,j;

	eni_dev = ENI_DEV(vcc->dev);
	eni_vcc = ENI_VCC(vcc);
	paddr = 0; /* GCC, shut up */
	अगर (skb) अणु
		paddr = dma_map_single(&eni_dev->pci_dev->dev,skb->data,skb->len,
				       DMA_FROM_DEVICE);
		अगर (dma_mapping_error(&eni_dev->pci_dev->dev, paddr))
			जाओ dma_map_error;
		ENI_PRV_PADDR(skb) = paddr;
		अगर (paddr & 3)
			prपूर्णांकk(KERN_CRIT DEV_LABEL "(itf %d): VCI %d has "
			    "mis-aligned RX data (0x%lx)\n",vcc->dev->number,
			    vcc->vci,(अचिन्हित दीर्घ) paddr);
		ENI_PRV_SIZE(skb) = size+skip;
		    /* PDU plus descriptor */
		ATM_SKB(skb)->vcc = vcc;
	पूर्ण
	j = 0;
	अगर ((eff && skip) || 1) अणु /* @@@ actually, skip is always == 1 ... */
		here = (eni_vcc->descr+skip) & (eni_vcc->words-1);
		dma[j++] = (here << MID_DMA_COUNT_SHIFT) | (vcc->vci
		    << MID_DMA_VCI_SHIFT) | MID_DT_JK;
		dma[j++] = 0;
	पूर्ण
	here = (eni_vcc->descr+size+skip) & (eni_vcc->words-1);
	अगर (!eff) size += skip;
	अन्यथा अणु
		अचिन्हित दीर्घ words;

		अगर (!size) अणु
			DPRINTK("strange things happen ...\n");
			EVENT("strange things happen ... (skip=%ld,eff=%ld)\n",
			    size,eff);
		पूर्ण
		words = eff;
		अगर (paddr & 15) अणु
			अचिन्हित दीर्घ init;

			init = 4-((paddr & 15) >> 2);
			अगर (init > words) init = words;
			dma[j++] = MID_DT_WORD | (init << MID_DMA_COUNT_SHIFT) |
			    (vcc->vci << MID_DMA_VCI_SHIFT);
			dma[j++] = paddr;
			paddr += init << 2;
			words -= init;
		पूर्ण
#अगर_घोषित CONFIG_ATM_ENI_BURST_RX_16W /* may work with some PCI chipsets ... */
		अगर (words & ~15) अणु
			dma[j++] = MID_DT_16W | ((words >> 4) <<
			    MID_DMA_COUNT_SHIFT) | (vcc->vci <<
			    MID_DMA_VCI_SHIFT);
			dma[j++] = paddr;
			paddr += (words & ~15) << 2;
			words &= 15;
		पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_ATM_ENI_BURST_RX_8W  /* works only with *some* PCI chipsets ... */
		अगर (words & ~7) अणु
			dma[j++] = MID_DT_8W | ((words >> 3) <<
			    MID_DMA_COUNT_SHIFT) | (vcc->vci <<
			    MID_DMA_VCI_SHIFT);
			dma[j++] = paddr;
			paddr += (words & ~7) << 2;
			words &= 7;
		पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_ATM_ENI_BURST_RX_4W /* recommended */
		अगर (words & ~3) अणु
			dma[j++] = MID_DT_4W | ((words >> 2) <<
			    MID_DMA_COUNT_SHIFT) | (vcc->vci <<
			    MID_DMA_VCI_SHIFT);
			dma[j++] = paddr;
			paddr += (words & ~3) << 2;
			words &= 3;
		पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_ATM_ENI_BURST_RX_2W /* probably useless अगर RX_4W, RX_8W, ... */
		अगर (words & ~1) अणु
			dma[j++] = MID_DT_2W | ((words >> 1) <<
			    MID_DMA_COUNT_SHIFT) | (vcc->vci <<
			    MID_DMA_VCI_SHIFT);
			dma[j++] = paddr;
			paddr += (words & ~1) << 2;
			words &= 1;
		पूर्ण
#पूर्ण_अगर
		अगर (words) अणु
			dma[j++] = MID_DT_WORD | (words << MID_DMA_COUNT_SHIFT)
			    | (vcc->vci << MID_DMA_VCI_SHIFT);
			dma[j++] = paddr;
		पूर्ण
	पूर्ण
	अगर (size != eff) अणु
		dma[j++] = (here << MID_DMA_COUNT_SHIFT) |
		    (vcc->vci << MID_DMA_VCI_SHIFT) | MID_DT_JK;
		dma[j++] = 0;
	पूर्ण
	अगर (!j || j > 2*RX_DMA_BUF) अणु
		prपूर्णांकk(KERN_CRIT DEV_LABEL "!j or j too big!!!\n");
		जाओ trouble;
	पूर्ण
	dma[j-2] |= MID_DMA_END;
	j = j >> 1;
	dma_wr = eni_in(MID_DMA_WR_RX);
	dma_rd = eni_in(MID_DMA_RD_RX);
	/*
	 * Can I move the dma_wr poपूर्णांकer by 2j+1 positions without overwriting
	 * data that hasn't been पढ़ो (position of dma_rd) yet ?
	 */
	अगर (!NEPMOK(dma_wr,j+j+1,dma_rd,NR_DMA_RX)) अणु /* @@@ +1 is ugly */
		prपूर्णांकk(KERN_WARNING DEV_LABEL "(itf %d): RX DMA full\n",
		    vcc->dev->number);
		जाओ trouble;
	पूर्ण
        क्रम (i = 0; i < j; i++) अणु
		ग_लिखोl(dma[i*2],eni_dev->rx_dma+dma_wr*8);
		ग_लिखोl(dma[i*2+1],eni_dev->rx_dma+dma_wr*8+4);
		dma_wr = (dma_wr+1) & (NR_DMA_RX-1);
        पूर्ण
	अगर (skb) अणु
		ENI_PRV_POS(skb) = eni_vcc->descr+size+1;
		skb_queue_tail(&eni_dev->rx_queue,skb);
		eni_vcc->last = skb;
		rx_enqueued++;
	पूर्ण
	eni_vcc->descr = here;
	eni_out(dma_wr,MID_DMA_WR_RX);
	वापस 0;

trouble:
	अगर (paddr)
		dma_unmap_single(&eni_dev->pci_dev->dev,paddr,skb->len,
				 DMA_FROM_DEVICE);
dma_map_error:
	अगर (skb) dev_kमुक्त_skb_irq(skb);
	वापस -1;
पूर्ण


अटल व्योम discard(काष्ठा aपंचांग_vcc *vcc,अचिन्हित दीर्घ size)
अणु
	काष्ठा eni_vcc *eni_vcc;

	eni_vcc = ENI_VCC(vcc);
	EVENT("discard (size=%ld)\n",size,0);
	जबतक (करो_rx_dma(vcc,शून्य,1,size,0)) EVENT("BUSY LOOP",0,0);
	    /* could करो a full fallback, but that might be more expensive */
	अगर (eni_vcc->rxing) ENI_PRV_POS(eni_vcc->last) += size+1;
	अन्यथा eni_vcc->rx_pos = (eni_vcc->rx_pos+size+1) & (eni_vcc->words-1);
पूर्ण


/*
 * TODO: should check whether direct copies (without DMA setup, dequeuing on
 * पूर्णांकerrupt, etc.) aren't much faster क्रम AAL0
 */

अटल पूर्णांक rx_aal0(काष्ठा aपंचांग_vcc *vcc)
अणु
	काष्ठा eni_vcc *eni_vcc;
	अचिन्हित दीर्घ descr;
	अचिन्हित दीर्घ length;
	काष्ठा sk_buff *skb;

	DPRINTK(">rx_aal0\n");
	eni_vcc = ENI_VCC(vcc);
	descr = पढ़ोl(eni_vcc->recv+eni_vcc->descr*4);
	अगर ((descr & MID_RED_IDEN) != (MID_RED_RX_ID << MID_RED_SHIFT)) अणु
		rx_ident_err(vcc);
		वापस 1;
	पूर्ण
	अगर (descr & MID_RED_T) अणु
		DPRINTK(DEV_LABEL "(itf %d): trashing empty cell\n",
		    vcc->dev->number);
		length = 0;
		atomic_inc(&vcc->stats->rx_err);
	पूर्ण
	अन्यथा अणु
		length = ATM_CELL_SIZE-1; /* no HEC */
	पूर्ण
	skb = length ? aपंचांग_alloc_अक्षरge(vcc,length,GFP_ATOMIC) : शून्य;
	अगर (!skb) अणु
		discard(vcc,length >> 2);
		वापस 0;
	पूर्ण
	skb_put(skb,length);
	skb->tstamp = eni_vcc->बारtamp;
	DPRINTK("got len %ld\n",length);
	अगर (करो_rx_dma(vcc,skb,1,length >> 2,length >> 2)) वापस 1;
	eni_vcc->rxing++;
	वापस 0;
पूर्ण


अटल पूर्णांक rx_aal5(काष्ठा aपंचांग_vcc *vcc)
अणु
	काष्ठा eni_vcc *eni_vcc;
	अचिन्हित दीर्घ descr;
	अचिन्हित दीर्घ size,eff,length;
	काष्ठा sk_buff *skb;

	EVENT("rx_aal5\n",0,0);
	DPRINTK(">rx_aal5\n");
	eni_vcc = ENI_VCC(vcc);
	descr = पढ़ोl(eni_vcc->recv+eni_vcc->descr*4);
	अगर ((descr & MID_RED_IDEN) != (MID_RED_RX_ID << MID_RED_SHIFT)) अणु
		rx_ident_err(vcc);
		वापस 1;
	पूर्ण
	अगर (descr & (MID_RED_T | MID_RED_CRC_ERR)) अणु
		अगर (descr & MID_RED_T) अणु
			EVENT("empty cell (descr=0x%lx)\n",descr,0);
			DPRINTK(DEV_LABEL "(itf %d): trashing empty cell\n",
			    vcc->dev->number);
			size = 0;
		पूर्ण
		अन्यथा अणु
			अटल अचिन्हित दीर्घ silence = 0;

			अगर (समय_after(jअगरfies, silence) || silence == 0) अणु
				prपूर्णांकk(KERN_WARNING DEV_LABEL "(itf %d): "
				    "discarding PDU(s) with CRC error\n",
				    vcc->dev->number);
				silence = (jअगरfies+2*HZ)|1;
			पूर्ण
			size = (descr & MID_RED_COUNT)*(ATM_CELL_PAYLOAD >> 2);
			EVENT("CRC error (descr=0x%lx,size=%ld)\n",descr,
			    size);
		पूर्ण
		eff = length = 0;
		atomic_inc(&vcc->stats->rx_err);
	पूर्ण
	अन्यथा अणु
		size = (descr & MID_RED_COUNT)*(ATM_CELL_PAYLOAD >> 2);
		DPRINTK("size=%ld\n",size);
		length = पढ़ोl(eni_vcc->recv+(((eni_vcc->descr+size-1) &
		    (eni_vcc->words-1)))*4) & 0xffff;
				/* -trailer(2)+header(1) */
		अगर (length && length <= (size << 2)-8 && length <=
		  ATM_MAX_AAL5_PDU) eff = (length+3) >> 2;
		अन्यथा अणु				 /* ^ trailer length (8) */
			EVENT("bad PDU (descr=0x08%lx,length=%ld)\n",descr,
			    length);
			prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): bad AAL5 PDU "
			    "(VCI=%d,length=%ld,size=%ld (descr 0x%lx))\n",
			    vcc->dev->number,vcc->vci,length,size << 2,descr);
			length = eff = 0;
			atomic_inc(&vcc->stats->rx_err);
		पूर्ण
	पूर्ण
	skb = eff ? aपंचांग_alloc_अक्षरge(vcc,eff << 2,GFP_ATOMIC) : शून्य;
	अगर (!skb) अणु
		discard(vcc,size);
		वापस 0;
	पूर्ण
	skb_put(skb,length);
	DPRINTK("got len %ld\n",length);
	अगर (करो_rx_dma(vcc,skb,1,size,eff)) वापस 1;
	eni_vcc->rxing++;
	वापस 0;
पूर्ण


अटल अंतरभूत पूर्णांक rx_vcc(काष्ठा aपंचांग_vcc *vcc)
अणु
	व्योम __iomem *vci_dsc;
	अचिन्हित दीर्घ पंचांगp;
	काष्ठा eni_vcc *eni_vcc;

	eni_vcc = ENI_VCC(vcc);
	vci_dsc = ENI_DEV(vcc->dev)->vci+vcc->vci*16;
	EVENT("rx_vcc(1)\n",0,0);
	जबतक (eni_vcc->descr != (पंचांगp = (पढ़ोl(vci_dsc+4) & MID_VCI_DESCR) >>
	    MID_VCI_DESCR_SHIFT)) अणु
		EVENT("rx_vcc(2: host dsc=0x%lx, nic dsc=0x%lx)\n",
		    eni_vcc->descr,पंचांगp);
		DPRINTK("CB_DESCR %ld REG_DESCR %d\n",ENI_VCC(vcc)->descr,
		    (((अचिन्हित) पढ़ोl(vci_dsc+4) & MID_VCI_DESCR) >>
		    MID_VCI_DESCR_SHIFT));
		अगर (ENI_VCC(vcc)->rx(vcc)) वापस 1;
	पूर्ण
	/* clear IN_SERVICE flag */
	ग_लिखोl(पढ़ोl(vci_dsc) & ~MID_VCI_IN_SERVICE,vci_dsc);
	/*
	 * If new data has arrived between evaluating the जबतक condition and
	 * clearing IN_SERVICE, we wouldn't be notअगरied until additional data
	 * follows. So we have to loop again to be sure.
	 */
	EVENT("rx_vcc(3)\n",0,0);
	जबतक (ENI_VCC(vcc)->descr != (पंचांगp = (पढ़ोl(vci_dsc+4) & MID_VCI_DESCR)
	    >> MID_VCI_DESCR_SHIFT)) अणु
		EVENT("rx_vcc(4: host dsc=0x%lx, nic dsc=0x%lx)\n",
		    eni_vcc->descr,पंचांगp);
		DPRINTK("CB_DESCR %ld REG_DESCR %d\n",ENI_VCC(vcc)->descr,
		    (((अचिन्हित) पढ़ोl(vci_dsc+4) & MID_VCI_DESCR) >>
		    MID_VCI_DESCR_SHIFT));
		अगर (ENI_VCC(vcc)->rx(vcc)) वापस 1;
	पूर्ण
	वापस 0;
पूर्ण


अटल व्योम poll_rx(काष्ठा aपंचांग_dev *dev)
अणु
	काष्ठा eni_dev *eni_dev;
	काष्ठा aपंचांग_vcc *curr;

	eni_dev = ENI_DEV(dev);
	जबतक ((curr = eni_dev->fast)) अणु
		EVENT("poll_rx.fast\n",0,0);
		अगर (rx_vcc(curr)) वापस;
		eni_dev->fast = ENI_VCC(curr)->next;
		ENI_VCC(curr)->next = ENI_VCC_NOS;
		barrier();
		ENI_VCC(curr)->servicing--;
	पूर्ण
	जबतक ((curr = eni_dev->slow)) अणु
		EVENT("poll_rx.slow\n",0,0);
		अगर (rx_vcc(curr)) वापस;
		eni_dev->slow = ENI_VCC(curr)->next;
		ENI_VCC(curr)->next = ENI_VCC_NOS;
		barrier();
		ENI_VCC(curr)->servicing--;
	पूर्ण
पूर्ण


अटल व्योम get_service(काष्ठा aपंचांग_dev *dev)
अणु
	काष्ठा eni_dev *eni_dev;
	काष्ठा aपंचांग_vcc *vcc;
	अचिन्हित दीर्घ vci;

	DPRINTK(">get_service\n");
	eni_dev = ENI_DEV(dev);
	जबतक (eni_in(MID_SERV_WRITE) != eni_dev->serv_पढ़ो) अणु
		vci = पढ़ोl(eni_dev->service+eni_dev->serv_पढ़ो*4);
		eni_dev->serv_पढ़ो = (eni_dev->serv_पढ़ो+1) & (NR_SERVICE-1);
		vcc = eni_dev->rx_map[vci & 1023];
		अगर (!vcc) अणु
			prपूर्णांकk(KERN_CRIT DEV_LABEL "(itf %d): VCI %ld not "
			    "found\n",dev->number,vci);
			जारी; /* nasty but we try to go on anyway */
			/* @@@ nope, करोesn't work */
		पूर्ण
		EVENT("getting from service\n",0,0);
		अगर (ENI_VCC(vcc)->next != ENI_VCC_NOS) अणु
			EVENT("double service\n",0,0);
			DPRINTK("Grr, servicing VCC %ld twice\n",vci);
			जारी;
		पूर्ण
		ENI_VCC(vcc)->बारtamp = kसमय_get_real();
		ENI_VCC(vcc)->next = शून्य;
		अगर (vcc->qos.rxtp.traffic_class == ATM_CBR) अणु
			अगर (eni_dev->fast)
				ENI_VCC(eni_dev->last_fast)->next = vcc;
			अन्यथा eni_dev->fast = vcc;
			eni_dev->last_fast = vcc;
		पूर्ण
		अन्यथा अणु
			अगर (eni_dev->slow)
				ENI_VCC(eni_dev->last_slow)->next = vcc;
			अन्यथा eni_dev->slow = vcc;
			eni_dev->last_slow = vcc;
		पूर्ण
		putting++;
		ENI_VCC(vcc)->servicing++;
	पूर्ण
पूर्ण


अटल व्योम dequeue_rx(काष्ठा aपंचांग_dev *dev)
अणु
	काष्ठा eni_dev *eni_dev;
	काष्ठा eni_vcc *eni_vcc;
	काष्ठा aपंचांग_vcc *vcc;
	काष्ठा sk_buff *skb;
	व्योम __iomem *vci_dsc;
	पूर्णांक first;

	eni_dev = ENI_DEV(dev);
	first = 1;
	जबतक (1) अणु
		skb = skb_dequeue(&eni_dev->rx_queue);
		अगर (!skb) अणु
			अगर (first) अणु
				DPRINTK(DEV_LABEL "(itf %d): RX but not "
				    "rxing\n",dev->number);
				EVENT("nothing to dequeue\n",0,0);
			पूर्ण
			अवरोध;
		पूर्ण
		EVENT("dequeued (size=%ld,pos=0x%lx)\n",ENI_PRV_SIZE(skb),
		    ENI_PRV_POS(skb));
		rx_dequeued++;
		vcc = ATM_SKB(skb)->vcc;
		eni_vcc = ENI_VCC(vcc);
		first = 0;
		vci_dsc = eni_dev->vci+vcc->vci*16;
		अगर (!EEPMOK(eni_vcc->rx_pos,ENI_PRV_SIZE(skb),
		    (पढ़ोl(vci_dsc+4) & MID_VCI_READ) >> MID_VCI_READ_SHIFT,
		    eni_vcc->words)) अणु
			EVENT("requeuing\n",0,0);
			skb_queue_head(&eni_dev->rx_queue,skb);
			अवरोध;
		पूर्ण
		eni_vcc->rxing--;
		eni_vcc->rx_pos = ENI_PRV_POS(skb) & (eni_vcc->words-1);
		dma_unmap_single(&eni_dev->pci_dev->dev,ENI_PRV_PADDR(skb),skb->len,
			         DMA_TO_DEVICE);
		अगर (!skb->len) dev_kमुक्त_skb_irq(skb);
		अन्यथा अणु
			EVENT("pushing (len=%ld)\n",skb->len,0);
			अगर (vcc->qos.aal == ATM_AAL0)
				*(अचिन्हित दीर्घ *) skb->data =
				    ntohl(*(अचिन्हित दीर्घ *) skb->data);
			स_रखो(skb->cb,0,माप(काष्ठा eni_skb_prv));
			vcc->push(vcc,skb);
			pushed++;
		पूर्ण
		atomic_inc(&vcc->stats->rx);
	पूर्ण
	wake_up(&eni_dev->rx_रुको);
पूर्ण


अटल पूर्णांक खोलो_rx_first(काष्ठा aपंचांग_vcc *vcc)
अणु
	काष्ठा eni_dev *eni_dev;
	काष्ठा eni_vcc *eni_vcc;
	अचिन्हित दीर्घ size;

	DPRINTK("open_rx_first\n");
	eni_dev = ENI_DEV(vcc->dev);
	eni_vcc = ENI_VCC(vcc);
	eni_vcc->rx = शून्य;
	अगर (vcc->qos.rxtp.traffic_class == ATM_NONE) वापस 0;
	size = vcc->qos.rxtp.max_sdu*eni_dev->rx_mult/100;
	अगर (size > MID_MAX_BUF_SIZE && vcc->qos.rxtp.max_sdu <=
	    MID_MAX_BUF_SIZE)
		size = MID_MAX_BUF_SIZE;
	eni_vcc->recv = eni_alloc_mem(eni_dev,&size);
	DPRINTK("rx at 0x%lx\n",eni_vcc->recv);
	eni_vcc->words = size >> 2;
	अगर (!eni_vcc->recv) वापस -ENOBUFS;
	eni_vcc->rx = vcc->qos.aal == ATM_AAL5 ? rx_aal5 : rx_aal0;
	eni_vcc->descr = 0;
	eni_vcc->rx_pos = 0;
	eni_vcc->rxing = 0;
	eni_vcc->servicing = 0;
	eni_vcc->next = ENI_VCC_NOS;
	वापस 0;
पूर्ण


अटल पूर्णांक खोलो_rx_second(काष्ठा aपंचांग_vcc *vcc)
अणु
	व्योम __iomem *here;
	काष्ठा eni_dev *eni_dev;
	काष्ठा eni_vcc *eni_vcc;
	अचिन्हित दीर्घ size;
	पूर्णांक order;

	DPRINTK("open_rx_second\n");
	eni_dev = ENI_DEV(vcc->dev);
	eni_vcc = ENI_VCC(vcc);
	अगर (!eni_vcc->rx) वापस 0;
	/* set up VCI descriptor */
	here = eni_dev->vci+vcc->vci*16;
	DPRINTK("loc 0x%x\n",(अचिन्हित) (eni_vcc->recv-eni_dev->ram)/4);
	size = eni_vcc->words >> 8;
	क्रम (order = -1; size; order++) size >>= 1;
	ग_लिखोl(0,here+4); /* descr, पढ़ो = 0 */
	ग_लिखोl(0,here+8); /* ग_लिखो, state, count = 0 */
	अगर (eni_dev->rx_map[vcc->vci])
		prपूर्णांकk(KERN_CRIT DEV_LABEL "(itf %d): BUG - VCI %d already "
		    "in use\n",vcc->dev->number,vcc->vci);
	eni_dev->rx_map[vcc->vci] = vcc; /* now it counts */
	ग_लिखोl(((vcc->qos.aal != ATM_AAL5 ? MID_MODE_RAW : MID_MODE_AAL5) <<
	    MID_VCI_MODE_SHIFT) | MID_VCI_PTI_MODE |
	    (((eni_vcc->recv-eni_dev->ram) >> (MID_LOC_SKIP+2)) <<
	    MID_VCI_LOCATION_SHIFT) | (order << MID_VCI_SIZE_SHIFT),here);
	वापस 0;
पूर्ण


अटल व्योम बंद_rx(काष्ठा aपंचांग_vcc *vcc)
अणु
	DECLARE_WAITQUEUE(रुको,current);
	व्योम __iomem *here;
	काष्ठा eni_dev *eni_dev;
	काष्ठा eni_vcc *eni_vcc;

	eni_vcc = ENI_VCC(vcc);
	अगर (!eni_vcc->rx) वापस;
	eni_dev = ENI_DEV(vcc->dev);
	अगर (vcc->vpi != ATM_VPI_UNSPEC && vcc->vci != ATM_VCI_UNSPEC) अणु
		here = eni_dev->vci+vcc->vci*16;
		/* block receiver */
		ग_लिखोl((पढ़ोl(here) & ~MID_VCI_MODE) | (MID_MODE_TRASH <<
		    MID_VCI_MODE_SHIFT),here);
		/* रुको क्रम receiver to become idle */
		udelay(27);
		/* discard pending cell */
		ग_लिखोl(पढ़ोl(here) & ~MID_VCI_IN_SERVICE,here);
		/* करोn't accept any new ones */
		eni_dev->rx_map[vcc->vci] = शून्य;
		/* रुको क्रम RX queue to drain */
		DPRINTK("eni_close: waiting for RX ...\n");
		EVENT("RX closing\n",0,0);
		add_रुको_queue(&eni_dev->rx_रुको,&रुको);
		set_current_state(TASK_UNINTERRUPTIBLE);
		barrier();
		क्रम (;;) अणु
			/* transition service->rx: rxing++, servicing-- */
			अगर (!eni_vcc->servicing) अणु
				barrier();
				अगर (!eni_vcc->rxing) अवरोध;
			पूर्ण
			EVENT("drain PDUs (rx %ld, serv %ld)\n",eni_vcc->rxing,
			    eni_vcc->servicing);
			prपूर्णांकk(KERN_INFO "%d+%d RX left\n",eni_vcc->servicing,
			    eni_vcc->rxing);
			schedule();
			set_current_state(TASK_UNINTERRUPTIBLE);
		पूर्ण
		क्रम (;;) अणु
			पूर्णांक at_end;
			u32 पंचांगp;

			tasklet_disable(&eni_dev->task);
			पंचांगp = पढ़ोl(eni_dev->vci+vcc->vci*16+4) & MID_VCI_READ;
			at_end = eni_vcc->rx_pos == पंचांगp >> MID_VCI_READ_SHIFT;
			tasklet_enable(&eni_dev->task);
			अगर (at_end) अवरोध;
			EVENT("drain discard (host 0x%lx, nic 0x%lx)\n",
			    eni_vcc->rx_pos,पंचांगp);
			prपूर्णांकk(KERN_INFO "draining RX: host 0x%lx, nic 0x%x\n",
			    eni_vcc->rx_pos,पंचांगp);
			schedule();
			set_current_state(TASK_UNINTERRUPTIBLE);
		पूर्ण
		set_current_state(TASK_RUNNING);
		हटाओ_रुको_queue(&eni_dev->rx_रुको,&रुको);
	पूर्ण
	eni_मुक्त_mem(eni_dev,eni_vcc->recv,eni_vcc->words << 2);
	eni_vcc->rx = शून्य;
पूर्ण


अटल पूर्णांक start_rx(काष्ठा aपंचांग_dev *dev)
अणु
	काष्ठा eni_dev *eni_dev;

	eni_dev = ENI_DEV(dev);
	eni_dev->rx_map = (काष्ठा aपंचांग_vcc **) get_zeroed_page(GFP_KERNEL);
	अगर (!eni_dev->rx_map) अणु
		prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): couldn't get free page\n",
		    dev->number);
		मुक्त_page((अचिन्हित दीर्घ) eni_dev->मुक्त_list);
		वापस -ENOMEM;
	पूर्ण
	eni_dev->rx_mult = DEFAULT_RX_MULT;
	eni_dev->fast = eni_dev->last_fast = शून्य;
	eni_dev->slow = eni_dev->last_slow = शून्य;
	init_रुकोqueue_head(&eni_dev->rx_रुको);
	skb_queue_head_init(&eni_dev->rx_queue);
	eni_dev->serv_पढ़ो = eni_in(MID_SERV_WRITE);
	eni_out(0,MID_DMA_WR_RX);
	वापस 0;
पूर्ण


/*----------------------------------- TX ------------------------------------*/


क्रमागत enq_res अणु enq_ok,enq_next,enq_jam पूर्ण;


अटल अंतरभूत व्योम put_dma(पूर्णांक chan,u32 *dma,पूर्णांक *j,dma_addr_t paddr,
    u32 size)
अणु
	u32 init,words;

	DPRINTK("put_dma: 0x%lx+0x%x\n",(अचिन्हित दीर्घ) paddr,size);
	EVENT("put_dma: 0x%lx+0x%lx\n",(अचिन्हित दीर्घ) paddr,size);
#अगर 0 /* करोn't complain anymore */
	अगर (paddr & 3)
		prपूर्णांकk(KERN_ERR "put_dma: unaligned addr (0x%lx)\n",paddr);
	अगर (size & 3)
		prपूर्णांकk(KERN_ERR "put_dma: unaligned size (0x%lx)\n",size);
#पूर्ण_अगर
	अगर (paddr & 3) अणु
		init = 4-(paddr & 3);
		अगर (init > size || size < 7) init = size;
		DPRINTK("put_dma: %lx DMA: %d/%d bytes\n",
		    (अचिन्हित दीर्घ) paddr,init,size);
		dma[(*j)++] = MID_DT_BYTE | (init << MID_DMA_COUNT_SHIFT) |
		    (chan << MID_DMA_CHAN_SHIFT);
		dma[(*j)++] = paddr;
		paddr += init;
		size -= init;
	पूर्ण
	words = size >> 2;
	size &= 3;
	अगर (words && (paddr & 31)) अणु
		init = 8-((paddr & 31) >> 2);
		अगर (init > words) init = words;
		DPRINTK("put_dma: %lx DMA: %d/%d words\n",
		    (अचिन्हित दीर्घ) paddr,init,words);
		dma[(*j)++] = MID_DT_WORD | (init << MID_DMA_COUNT_SHIFT) |
		    (chan << MID_DMA_CHAN_SHIFT);
		dma[(*j)++] = paddr;
		paddr += init << 2;
		words -= init;
	पूर्ण
#अगर_घोषित CONFIG_ATM_ENI_BURST_TX_16W /* may work with some PCI chipsets ... */
	अगर (words & ~15) अणु
		DPRINTK("put_dma: %lx DMA: %d*16/%d words\n",
		    (अचिन्हित दीर्घ) paddr,words >> 4,words);
		dma[(*j)++] = MID_DT_16W | ((words >> 4) << MID_DMA_COUNT_SHIFT)
		    | (chan << MID_DMA_CHAN_SHIFT);
		dma[(*j)++] = paddr;
		paddr += (words & ~15) << 2;
		words &= 15;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_ATM_ENI_BURST_TX_8W /* recommended */
	अगर (words & ~7) अणु
		DPRINTK("put_dma: %lx DMA: %d*8/%d words\n",
		    (अचिन्हित दीर्घ) paddr,words >> 3,words);
		dma[(*j)++] = MID_DT_8W | ((words >> 3) << MID_DMA_COUNT_SHIFT)
		    | (chan << MID_DMA_CHAN_SHIFT);
		dma[(*j)++] = paddr;
		paddr += (words & ~7) << 2;
		words &= 7;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_ATM_ENI_BURST_TX_4W /* probably useless अगर TX_8W or TX_16W */
	अगर (words & ~3) अणु
		DPRINTK("put_dma: %lx DMA: %d*4/%d words\n",
		    (अचिन्हित दीर्घ) paddr,words >> 2,words);
		dma[(*j)++] = MID_DT_4W | ((words >> 2) << MID_DMA_COUNT_SHIFT)
		    | (chan << MID_DMA_CHAN_SHIFT);
		dma[(*j)++] = paddr;
		paddr += (words & ~3) << 2;
		words &= 3;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_ATM_ENI_BURST_TX_2W /* probably useless अगर TX_4W, TX_8W, ... */
	अगर (words & ~1) अणु
		DPRINTK("put_dma: %lx DMA: %d*2/%d words\n",
		    (अचिन्हित दीर्घ) paddr,words >> 1,words);
		dma[(*j)++] = MID_DT_2W | ((words >> 1) << MID_DMA_COUNT_SHIFT)
		    | (chan << MID_DMA_CHAN_SHIFT);
		dma[(*j)++] = paddr;
		paddr += (words & ~1) << 2;
		words &= 1;
	पूर्ण
#पूर्ण_अगर
	अगर (words) अणु
		DPRINTK("put_dma: %lx DMA: %d words\n",(अचिन्हित दीर्घ) paddr,
		    words);
		dma[(*j)++] = MID_DT_WORD | (words << MID_DMA_COUNT_SHIFT) |
		    (chan << MID_DMA_CHAN_SHIFT);
		dma[(*j)++] = paddr;
		paddr += words << 2;
	पूर्ण
	अगर (size) अणु
		DPRINTK("put_dma: %lx DMA: %d bytes\n",(अचिन्हित दीर्घ) paddr,
		    size);
		dma[(*j)++] = MID_DT_BYTE | (size << MID_DMA_COUNT_SHIFT) |
		    (chan << MID_DMA_CHAN_SHIFT);
		dma[(*j)++] = paddr;
	पूर्ण
पूर्ण


अटल क्रमागत enq_res करो_tx(काष्ठा sk_buff *skb)
अणु
	काष्ठा aपंचांग_vcc *vcc;
	काष्ठा eni_dev *eni_dev;
	काष्ठा eni_vcc *eni_vcc;
	काष्ठा eni_tx *tx;
	dma_addr_t paddr;
	u32 dma_rd,dma_wr;
	u32 size; /* in words */
	पूर्णांक aal5,dma_size,i,j;
	अचिन्हित अक्षर skb_data3;

	DPRINTK(">do_tx\n");
	शून्यCHECK(skb);
	EVENT("do_tx: skb=0x%lx, %ld bytes\n",(अचिन्हित दीर्घ) skb,skb->len);
	vcc = ATM_SKB(skb)->vcc;
	शून्यCHECK(vcc);
	eni_dev = ENI_DEV(vcc->dev);
	शून्यCHECK(eni_dev);
	eni_vcc = ENI_VCC(vcc);
	tx = eni_vcc->tx;
	शून्यCHECK(tx);
#अगर 0 /* Enable this क्रम testing with the "align" program */
	अणु
		अचिन्हित पूर्णांक hack = *((अक्षर *) skb->data)-'0';

		अगर (hack < 8) अणु
			skb->data += hack;
			skb->len -= hack;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
#अगर 0 /* should work now */
	अगर ((अचिन्हित दीर्घ) skb->data & 3)
		prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): VCI %d has mis-aligned "
		    "TX data\n",vcc->dev->number,vcc->vci);
#पूर्ण_अगर
	/*
	 * Potential future IP speedup: make hard_header big enough to put
	 * segmentation descriptor directly पूर्णांकo PDU. Saves: 4 slave ग_लिखोs,
	 * 1 DMA xfer & 2 DMA'ed bytes (protocol layering is क्रम wimps :-)
	 */

	aal5 = vcc->qos.aal == ATM_AAL5;
	/* check space in buffer */
	अगर (!aal5)
		size = (ATM_CELL_PAYLOAD >> 2)+TX_DESCR_SIZE;
			/* cell without HEC plus segmentation header (includes
			   four-byte cell header) */
	अन्यथा अणु
		size = skb->len+4*AAL5_TRAILER+ATM_CELL_PAYLOAD-1;
			/* add AAL5 trailer */
		size = ((size-(size % ATM_CELL_PAYLOAD)) >> 2)+TX_DESCR_SIZE;
						/* add segmentation header */
	पूर्ण
	/*
	 * Can I move tx_pos by size bytes without getting बंदr than TX_GAP
	 * to the पढ़ो poपूर्णांकer ? TX_GAP means to leave some space क्रम what
	 * the manual calls "too close".
	 */
	अगर (!NEPMOK(tx->tx_pos,size+TX_GAP,
	    eni_in(MID_TX_RDPTR(tx->index)),tx->words)) अणु
		DPRINTK(DEV_LABEL "(itf %d): TX full (size %d)\n",
		    vcc->dev->number,size);
		वापस enq_next;
	पूर्ण
	/* check DMA */
	dma_wr = eni_in(MID_DMA_WR_TX);
	dma_rd = eni_in(MID_DMA_RD_TX);
	dma_size = 3; /* JK क्रम descriptor and final fill, plus final size
			 mis-alignment fix */
DPRINTK("iovcnt = %d\n",skb_shinfo(skb)->nr_frags);
	अगर (!skb_shinfo(skb)->nr_frags) dma_size += 5;
	अन्यथा dma_size += 5*(skb_shinfo(skb)->nr_frags+1);
	अगर (dma_size > TX_DMA_BUF) अणु
		prपूर्णांकk(KERN_CRIT DEV_LABEL "(itf %d): needs %d DMA entries "
		    "(got only %d)\n",vcc->dev->number,dma_size,TX_DMA_BUF);
	पूर्ण
	DPRINTK("dma_wr is %d, tx_pos is %ld\n",dma_wr,tx->tx_pos);
	अगर (dma_wr != dma_rd && ((dma_rd+NR_DMA_TX-dma_wr) & (NR_DMA_TX-1)) <
	     dma_size) अणु
		prपूर्णांकk(KERN_WARNING DEV_LABEL "(itf %d): TX DMA full\n",
		    vcc->dev->number);
		वापस enq_jam;
	पूर्ण
	skb_data3 = skb->data[3];
	paddr = dma_map_single(&eni_dev->pci_dev->dev,skb->data,skb->len,
			       DMA_TO_DEVICE);
	ENI_PRV_PADDR(skb) = paddr;
	/* prepare DMA queue entries */
	j = 0;
	eni_dev->dma[j++] = (((tx->tx_pos+TX_DESCR_SIZE) & (tx->words-1)) <<
	     MID_DMA_COUNT_SHIFT) | (tx->index << MID_DMA_CHAN_SHIFT) |
	     MID_DT_JK;
	j++;
	अगर (!skb_shinfo(skb)->nr_frags)
		अगर (aal5) put_dma(tx->index,eni_dev->dma,&j,paddr,skb->len);
		अन्यथा put_dma(tx->index,eni_dev->dma,&j,paddr+4,skb->len-4);
	अन्यथा अणु
DPRINTK("doing direct send\n"); /* @@@ well, this करोesn't work anyway */
		क्रम (i = -1; i < skb_shinfo(skb)->nr_frags; i++)
			अगर (i == -1)
				put_dma(tx->index,eni_dev->dma,&j,(अचिन्हित दीर्घ)
				    skb->data,
				    skb_headlen(skb));
			अन्यथा
				put_dma(tx->index,eni_dev->dma,&j,(अचिन्हित दीर्घ)
				    skb_frag_page(&skb_shinfo(skb)->frags[i]) +
					skb_frag_off(&skb_shinfo(skb)->frags[i]),
				    skb_frag_size(&skb_shinfo(skb)->frags[i]));
	पूर्ण
	अगर (skb->len & 3) अणु
		put_dma(tx->index, eni_dev->dma, &j, eni_dev->zero.dma,
			4 - (skb->len & 3));
	पूर्ण
	/* JK क्रम AAL5 trailer - AAL0 करोesn't need it, but who cares ... */
	eni_dev->dma[j++] = (((tx->tx_pos+size) & (tx->words-1)) <<
	     MID_DMA_COUNT_SHIFT) | (tx->index << MID_DMA_CHAN_SHIFT) |
	     MID_DMA_END | MID_DT_JK;
	j++;
	DPRINTK("DMA at end: %d\n",j);
	/* store frame */
	ग_लिखोl((MID_SEG_TX_ID << MID_SEG_ID_SHIFT) |
	    (aal5 ? MID_SEG_AAL5 : 0) | (tx->prescaler << MID_SEG_PR_SHIFT) |
	    (tx->resolution << MID_SEG_RATE_SHIFT) |
	    (size/(ATM_CELL_PAYLOAD/4)),tx->send+tx->tx_pos*4);
/*prपूर्णांकk("dsc = 0x%08lx\n",(अचिन्हित दीर्घ) पढ़ोl(tx->send+tx->tx_pos*4));*/
	ग_लिखोl((vcc->vci << MID_SEG_VCI_SHIFT) |
            (aal5 ? 0 : (skb_data3 & 0xf)) |
	    (ATM_SKB(skb)->aपंचांग_options & ATM_ATMOPT_CLP ? MID_SEG_CLP : 0),
	    tx->send+((tx->tx_pos+1) & (tx->words-1))*4);
	DPRINTK("size: %d, len:%d\n",size,skb->len);
	अगर (aal5)
		ग_लिखोl(skb->len,tx->send+
                    ((tx->tx_pos+size-AAL5_TRAILER) & (tx->words-1))*4);
	j = j >> 1;
	क्रम (i = 0; i < j; i++) अणु
		ग_लिखोl(eni_dev->dma[i*2],eni_dev->tx_dma+dma_wr*8);
		ग_लिखोl(eni_dev->dma[i*2+1],eni_dev->tx_dma+dma_wr*8+4);
		dma_wr = (dma_wr+1) & (NR_DMA_TX-1);
	पूर्ण
	ENI_PRV_POS(skb) = tx->tx_pos;
	ENI_PRV_SIZE(skb) = size;
	ENI_VCC(vcc)->txing += size;
	tx->tx_pos = (tx->tx_pos+size) & (tx->words-1);
	DPRINTK("dma_wr set to %d, tx_pos is now %ld\n",dma_wr,tx->tx_pos);
	eni_out(dma_wr,MID_DMA_WR_TX);
	skb_queue_tail(&eni_dev->tx_queue,skb);
	queued++;
	वापस enq_ok;
पूर्ण


अटल व्योम poll_tx(काष्ठा aपंचांग_dev *dev)
अणु
	काष्ठा eni_tx *tx;
	काष्ठा sk_buff *skb;
	क्रमागत enq_res res;
	पूर्णांक i;

	DPRINTK(">poll_tx\n");
	क्रम (i = NR_CHAN-1; i >= 0; i--) अणु
		tx = &ENI_DEV(dev)->tx[i];
		अगर (tx->send)
			जबतक ((skb = skb_dequeue(&tx->backlog))) अणु
				res = करो_tx(skb);
				अगर (res == enq_ok) जारी;
				DPRINTK("re-queuing TX PDU\n");
				skb_queue_head(&tx->backlog,skb);
				requeued++;
				अगर (res == enq_jam) वापस;
				अवरोध;
			पूर्ण
	पूर्ण
पूर्ण


अटल व्योम dequeue_tx(काष्ठा aपंचांग_dev *dev)
अणु
	काष्ठा eni_dev *eni_dev;
	काष्ठा aपंचांग_vcc *vcc;
	काष्ठा sk_buff *skb;
	काष्ठा eni_tx *tx;

	शून्यCHECK(dev);
	eni_dev = ENI_DEV(dev);
	शून्यCHECK(eni_dev);
	जबतक ((skb = skb_dequeue(&eni_dev->tx_queue))) अणु
		vcc = ATM_SKB(skb)->vcc;
		शून्यCHECK(vcc);
		tx = ENI_VCC(vcc)->tx;
		शून्यCHECK(ENI_VCC(vcc)->tx);
		DPRINTK("dequeue_tx: next 0x%lx curr 0x%x\n",ENI_PRV_POS(skb),
		    (अचिन्हित) eni_in(MID_TX_DESCRSTART(tx->index)));
		अगर (ENI_VCC(vcc)->txing < tx->words && ENI_PRV_POS(skb) ==
		    eni_in(MID_TX_DESCRSTART(tx->index))) अणु
			skb_queue_head(&eni_dev->tx_queue,skb);
			अवरोध;
		पूर्ण
		ENI_VCC(vcc)->txing -= ENI_PRV_SIZE(skb);
		dma_unmap_single(&eni_dev->pci_dev->dev,ENI_PRV_PADDR(skb),skb->len,
				 DMA_TO_DEVICE);
		अगर (vcc->pop) vcc->pop(vcc,skb);
		अन्यथा dev_kमुक्त_skb_irq(skb);
		atomic_inc(&vcc->stats->tx);
		wake_up(&eni_dev->tx_रुको);
		dma_complete++;
	पूर्ण
पूर्ण


अटल काष्ठा eni_tx *alloc_tx(काष्ठा eni_dev *eni_dev,पूर्णांक ubr)
अणु
	पूर्णांक i;

	क्रम (i = !ubr; i < NR_CHAN; i++)
		अगर (!eni_dev->tx[i].send) वापस eni_dev->tx+i;
	वापस शून्य;
पूर्ण


अटल पूर्णांक comp_tx(काष्ठा eni_dev *eni_dev,पूर्णांक *pcr,पूर्णांक reserved,पूर्णांक *pre,
    पूर्णांक *res,पूर्णांक unlimited)
अणु
	अटल स्थिर पूर्णांक pre_भाग[] = अणु 4,16,128,2048 पूर्ण;
	    /* 2^(((x+2)^2-(x+2))/2+1) */

	अगर (unlimited) *pre = *res = 0;
	अन्यथा अणु
		अगर (*pcr > 0) अणु
			पूर्णांक भाग;

			क्रम (*pre = 0; *pre < 3; (*pre)++)
				अगर (TS_CLOCK/pre_भाग[*pre]/64 <= *pcr) अवरोध;
			भाग = pre_भाग[*pre]**pcr;
			DPRINTK("min div %d\n",भाग);
			*res = TS_CLOCK/भाग-1;
		पूर्ण
		अन्यथा अणु
			पूर्णांक भाग;

			अगर (!*pcr) *pcr = eni_dev->tx_bw+reserved;
			क्रम (*pre = 3; *pre >= 0; (*pre)--)
				अगर (TS_CLOCK/pre_भाग[*pre]/64 > -*pcr) अवरोध;
			अगर (*pre < 3) (*pre)++; /* अन्यथा fail later */
			भाग = pre_भाग[*pre]*-*pcr;
			DPRINTK("max div %d\n",भाग);
			*res = DIV_ROUND_UP(TS_CLOCK, भाग)-1;
		पूर्ण
		अगर (*res < 0) *res = 0;
		अगर (*res > MID_SEG_MAX_RATE) *res = MID_SEG_MAX_RATE;
	पूर्ण
	*pcr = TS_CLOCK/pre_भाग[*pre]/(*res+1);
	DPRINTK("out pcr: %d (%d:%d)\n",*pcr,*pre,*res);
	वापस 0;
पूर्ण


अटल पूर्णांक reserve_or_set_tx(काष्ठा aपंचांग_vcc *vcc,काष्ठा aपंचांग_trafprm *txtp,
    पूर्णांक set_rsv,पूर्णांक set_shp)
अणु
	काष्ठा eni_dev *eni_dev = ENI_DEV(vcc->dev);
	काष्ठा eni_vcc *eni_vcc = ENI_VCC(vcc);
	काष्ठा eni_tx *tx;
	अचिन्हित दीर्घ size;
	व्योम __iomem *mem;
	पूर्णांक rate,ubr,unlimited,new_tx;
	पूर्णांक pre,res,order;
	पूर्णांक error;

	rate = aपंचांग_pcr_goal(txtp);
	ubr = txtp->traffic_class == ATM_UBR;
	unlimited = ubr && (!rate || rate <= -ATM_OC3_PCR ||
	    rate >= ATM_OC3_PCR);
	अगर (!unlimited) अणु
		size = txtp->max_sdu*eni_dev->tx_mult/100;
		अगर (size > MID_MAX_BUF_SIZE && txtp->max_sdu <=
		    MID_MAX_BUF_SIZE)
			size = MID_MAX_BUF_SIZE;
	पूर्ण
	अन्यथा अणु
		अगर (eni_dev->ubr) अणु
			eni_vcc->tx = eni_dev->ubr;
			txtp->pcr = ATM_OC3_PCR;
			वापस 0;
		पूर्ण
		size = UBR_BUFFER;
	पूर्ण
	new_tx = !eni_vcc->tx;
	mem = शून्य; /* क्रम gcc */
	अगर (!new_tx) tx = eni_vcc->tx;
	अन्यथा अणु
		mem = eni_alloc_mem(eni_dev,&size);
		अगर (!mem) वापस -ENOBUFS;
		tx = alloc_tx(eni_dev,unlimited);
		अगर (!tx) अणु
			eni_मुक्त_mem(eni_dev,mem,size);
			वापस -EBUSY;
		पूर्ण
		DPRINTK("got chan %d\n",tx->index);
		tx->reserved = tx->shaping = 0;
		tx->send = mem;
		tx->words = size >> 2;
		skb_queue_head_init(&tx->backlog);
		क्रम (order = 0; size > (1 << (order+10)); order++);
		eni_out((order << MID_SIZE_SHIFT) |
		    ((tx->send-eni_dev->ram) >> (MID_LOC_SKIP+2)),
		    MID_TX_PLACE(tx->index));
		tx->tx_pos = eni_in(MID_TX_DESCRSTART(tx->index)) &
		    MID_DESCR_START;
	पूर्ण
	error = comp_tx(eni_dev,&rate,tx->reserved,&pre,&res,unlimited);
	अगर (!error  && txtp->min_pcr > rate) error = -EINVAL;
	अगर (!error && txtp->max_pcr && txtp->max_pcr != ATM_MAX_PCR &&
	    txtp->max_pcr < rate) error = -EINVAL;
	अगर (!error && !ubr && rate > eni_dev->tx_bw+tx->reserved)
		error = -EINVAL;
	अगर (!error && set_rsv && !set_shp && rate < tx->shaping)
		error = -EINVAL;
	अगर (!error && !set_rsv && rate > tx->reserved && !ubr)
		error = -EINVAL;
	अगर (error) अणु
		अगर (new_tx) अणु
			tx->send = शून्य;
			eni_मुक्त_mem(eni_dev,mem,size);
		पूर्ण
		वापस error;
	पूर्ण
	txtp->pcr = rate;
	अगर (set_rsv && !ubr) अणु
		eni_dev->tx_bw += tx->reserved;
		tx->reserved = rate;
		eni_dev->tx_bw -= rate;
	पूर्ण
	अगर (set_shp || (unlimited && new_tx)) अणु
		अगर (unlimited && new_tx) eni_dev->ubr = tx;
		tx->prescaler = pre;
		tx->resolution = res;
		tx->shaping = rate;
	पूर्ण
	अगर (set_shp) eni_vcc->tx = tx;
	DPRINTK("rsv %d shp %d\n",tx->reserved,tx->shaping);
	वापस 0;
पूर्ण


अटल पूर्णांक खोलो_tx_first(काष्ठा aपंचांग_vcc *vcc)
अणु
	ENI_VCC(vcc)->tx = शून्य;
	अगर (vcc->qos.txtp.traffic_class == ATM_NONE) वापस 0;
	ENI_VCC(vcc)->txing = 0;
	वापस reserve_or_set_tx(vcc,&vcc->qos.txtp,1,1);
पूर्ण


अटल पूर्णांक खोलो_tx_second(काष्ठा aपंचांग_vcc *vcc)
अणु
	वापस 0; /* nothing to करो */
पूर्ण


अटल व्योम बंद_tx(काष्ठा aपंचांग_vcc *vcc)
अणु
	DECLARE_WAITQUEUE(रुको,current);
	काष्ठा eni_dev *eni_dev;
	काष्ठा eni_vcc *eni_vcc;

	eni_vcc = ENI_VCC(vcc);
	अगर (!eni_vcc->tx) वापस;
	eni_dev = ENI_DEV(vcc->dev);
	/* रुको क्रम TX queue to drain */
	DPRINTK("eni_close: waiting for TX ...\n");
	add_रुको_queue(&eni_dev->tx_रुको,&रुको);
	set_current_state(TASK_UNINTERRUPTIBLE);
	क्रम (;;) अणु
		पूर्णांक txing;

		tasklet_disable(&eni_dev->task);
		txing = skb_peek(&eni_vcc->tx->backlog) || eni_vcc->txing;
		tasklet_enable(&eni_dev->task);
		अगर (!txing) अवरोध;
		DPRINTK("%d TX left\n",eni_vcc->txing);
		schedule();
		set_current_state(TASK_UNINTERRUPTIBLE);
	पूर्ण
	set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(&eni_dev->tx_रुको,&रुको);
	अगर (eni_vcc->tx != eni_dev->ubr) अणु
		/*
		 * Looping a few बार in here is probably far cheaper than
		 * keeping track of TX completions all the समय, so let's poll
		 * a bit ...
		 */
		जबतक (eni_in(MID_TX_RDPTR(eni_vcc->tx->index)) !=
		    eni_in(MID_TX_DESCRSTART(eni_vcc->tx->index)))
			schedule();
		eni_मुक्त_mem(eni_dev,eni_vcc->tx->send,eni_vcc->tx->words << 2);
		eni_vcc->tx->send = शून्य;
		eni_dev->tx_bw += eni_vcc->tx->reserved;
	पूर्ण
	eni_vcc->tx = शून्य;
पूर्ण


अटल पूर्णांक start_tx(काष्ठा aपंचांग_dev *dev)
अणु
	काष्ठा eni_dev *eni_dev;
	पूर्णांक i;

	eni_dev = ENI_DEV(dev);
	eni_dev->lost = 0;
	eni_dev->tx_bw = ATM_OC3_PCR;
	eni_dev->tx_mult = DEFAULT_TX_MULT;
	init_रुकोqueue_head(&eni_dev->tx_रुको);
	eni_dev->ubr = शून्य;
	skb_queue_head_init(&eni_dev->tx_queue);
	eni_out(0,MID_DMA_WR_TX);
	क्रम (i = 0; i < NR_CHAN; i++) अणु
		eni_dev->tx[i].send = शून्य;
		eni_dev->tx[i].index = i;
	पूर्ण
	वापस 0;
पूर्ण


/*--------------------------------- common ----------------------------------*/


#अगर 0 /* may become useful again when tuning things */

अटल व्योम foo(व्योम)
अणु
prपूर्णांकk(KERN_INFO
  "tx_complete=%d,dma_complete=%d,queued=%d,requeued=%d,sub=%d,\n"
  "backlogged=%d,rx_enqueued=%d,rx_dequeued=%d,putting=%d,pushed=%d\n",
  tx_complete,dma_complete,queued,requeued,submitted,backlogged,
  rx_enqueued,rx_dequeued,putting,pushed);
अगर (eni_boards) prपूर्णांकk(KERN_INFO "loss: %ld\n",ENI_DEV(eni_boards)->lost);
पूर्ण

#पूर्ण_अगर


अटल व्योम bug_पूर्णांक(काष्ठा aपंचांग_dev *dev,अचिन्हित दीर्घ reason)
अणु
	DPRINTK(">bug_int\n");
	अगर (reason & MID_DMA_ERR_ACK)
		prपूर्णांकk(KERN_CRIT DEV_LABEL "(itf %d): driver error - DMA "
		    "error\n",dev->number);
	अगर (reason & MID_TX_IDENT_MISM)
		prपूर्णांकk(KERN_CRIT DEV_LABEL "(itf %d): driver error - ident "
		    "mismatch\n",dev->number);
	अगर (reason & MID_TX_DMA_OVFL)
		prपूर्णांकk(KERN_CRIT DEV_LABEL "(itf %d): driver error - DMA "
		    "overflow\n",dev->number);
	EVENT("---dump ends here---\n",0,0);
	prपूर्णांकk(KERN_NOTICE "---recent events---\n");
	event_dump();
पूर्ण


अटल irqवापस_t eni_पूर्णांक(पूर्णांक irq,व्योम *dev_id)
अणु
	काष्ठा aपंचांग_dev *dev;
	काष्ठा eni_dev *eni_dev;
	u32 reason;

	DPRINTK(">eni_int\n");
	dev = dev_id;
	eni_dev = ENI_DEV(dev);
	reason = eni_in(MID_ISA);
	DPRINTK(DEV_LABEL ": int 0x%lx\n",(अचिन्हित दीर्घ) reason);
	/*
	 * Must handle these two right now, because पढ़ोing ISA करोesn't clear
	 * them, so they re-occur and we never make it to the tasklet. Since
	 * they're rare, we don't mind the occasional invocation of eni_tasklet
	 * with eni_dev->events == 0.
	 */
	अगर (reason & MID_STAT_OVFL) अणु
		EVENT("stat overflow\n",0,0);
		eni_dev->lost += eni_in(MID_STAT) & MID_OVFL_TRASH;
	पूर्ण
	अगर (reason & MID_SUNI_INT) अणु
		EVENT("SUNI int\n",0,0);
		dev->phy->पूर्णांकerrupt(dev);
#अगर 0
		foo();
#पूर्ण_अगर
	पूर्ण
	spin_lock(&eni_dev->lock);
	eni_dev->events |= reason;
	spin_unlock(&eni_dev->lock);
	tasklet_schedule(&eni_dev->task);
	वापस IRQ_HANDLED;
पूर्ण


अटल व्योम eni_tasklet(अचिन्हित दीर्घ data)
अणु
	काष्ठा aपंचांग_dev *dev = (काष्ठा aपंचांग_dev *) data;
	काष्ठा eni_dev *eni_dev = ENI_DEV(dev);
	अचिन्हित दीर्घ flags;
	u32 events;

	DPRINTK("eni_tasklet (dev %p)\n",dev);
	spin_lock_irqsave(&eni_dev->lock,flags);
	events = xchg(&eni_dev->events,0);
	spin_unlock_irqrestore(&eni_dev->lock,flags);
	अगर (events & MID_RX_DMA_COMPLETE) अणु
		EVENT("INT: RX DMA complete, starting dequeue_rx\n",0,0);
		dequeue_rx(dev);
		EVENT("dequeue_rx done, starting poll_rx\n",0,0);
		poll_rx(dev);
		EVENT("poll_rx done\n",0,0);
		/* poll_tx ? */
	पूर्ण
	अगर (events & MID_SERVICE) अणु
		EVENT("INT: service, starting get_service\n",0,0);
		get_service(dev);
		EVENT("get_service done, starting poll_rx\n",0,0);
		poll_rx(dev);
		EVENT("poll_rx done\n",0,0);
	पूर्ण
 	अगर (events & MID_TX_DMA_COMPLETE) अणु
		EVENT("INT: TX DMA COMPLETE\n",0,0);
		dequeue_tx(dev);
	पूर्ण
	अगर (events & MID_TX_COMPLETE) अणु
		EVENT("INT: TX COMPLETE\n",0,0);
		tx_complete++;
		wake_up(&eni_dev->tx_रुको);
		/* poll_rx ? */
	पूर्ण
	अगर (events & (MID_DMA_ERR_ACK | MID_TX_IDENT_MISM | MID_TX_DMA_OVFL)) अणु
		EVENT("bug interrupt\n",0,0);
		bug_पूर्णांक(dev,events);
	पूर्ण
	poll_tx(dev);
पूर्ण


/*--------------------------------- entries ---------------------------------*/


अटल अक्षर * स्थिर media_name[] = अणु
    "MMF", "SMF", "MMF", "03?", /*  0- 3 */
    "UTP", "05?", "06?", "07?", /*  4- 7 */
    "TAXI","09?", "10?", "11?", /*  8-11 */
    "12?", "13?", "14?", "15?", /* 12-15 */
    "MMF", "SMF", "18?", "19?", /* 16-19 */
    "UTP", "21?", "22?", "23?", /* 20-23 */
    "24?", "25?", "26?", "27?", /* 24-27 */
    "28?", "29?", "30?", "31?"  /* 28-31 */
पूर्ण;


#घोषणा SET_SEPROM \
  (अणु अगर (!error && !pci_error) अणु \
    pci_error = pci_ग_लिखो_config_byte(eni_dev->pci_dev,PCI_TONGA_CTRL,tonga); \
    udelay(10); /* 10 usecs */ \
  पूर्ण पूर्ण)
#घोषणा GET_SEPROM \
  (अणु अगर (!error && !pci_error) अणु \
    pci_error = pci_पढ़ो_config_byte(eni_dev->pci_dev,PCI_TONGA_CTRL,&tonga); \
    udelay(10); /* 10 usecs */ \
  पूर्ण पूर्ण)


अटल पूर्णांक get_esi_asic(काष्ठा aपंचांग_dev *dev)
अणु
	काष्ठा eni_dev *eni_dev;
	अचिन्हित अक्षर tonga;
	पूर्णांक error,failed,pci_error;
	पूर्णांक address,i,j;

	eni_dev = ENI_DEV(dev);
	error = pci_error = 0;
	tonga = SEPROM_MAGIC | SEPROM_DATA | SEPROM_CLK;
	SET_SEPROM;
	क्रम (i = 0; i < ESI_LEN && !error && !pci_error; i++) अणु
		/* start operation */
		tonga |= SEPROM_DATA;
		SET_SEPROM;
		tonga |= SEPROM_CLK;
		SET_SEPROM;
		tonga &= ~SEPROM_DATA;
		SET_SEPROM;
		tonga &= ~SEPROM_CLK;
		SET_SEPROM;
		/* send address */
		address = ((i+SEPROM_ESI_BASE) << 1)+1;
		क्रम (j = 7; j >= 0; j--) अणु
			tonga = (address >> j) & 1 ? tonga | SEPROM_DATA :
			    tonga & ~SEPROM_DATA;
			SET_SEPROM;
			tonga |= SEPROM_CLK;
			SET_SEPROM;
			tonga &= ~SEPROM_CLK;
			SET_SEPROM;
		पूर्ण
		/* get ack */
		tonga |= SEPROM_DATA;
		SET_SEPROM;
		tonga |= SEPROM_CLK;
		SET_SEPROM;
		GET_SEPROM;
		failed = tonga & SEPROM_DATA;
		tonga &= ~SEPROM_CLK;
		SET_SEPROM;
		tonga |= SEPROM_DATA;
		SET_SEPROM;
		अगर (failed) error = -EIO;
		अन्यथा अणु
			dev->esi[i] = 0;
			क्रम (j = 7; j >= 0; j--) अणु
				dev->esi[i] <<= 1;
				tonga |= SEPROM_DATA;
				SET_SEPROM;
				tonga |= SEPROM_CLK;
				SET_SEPROM;
				GET_SEPROM;
				अगर (tonga & SEPROM_DATA) dev->esi[i] |= 1;
				tonga &= ~SEPROM_CLK;
				SET_SEPROM;
				tonga |= SEPROM_DATA;
				SET_SEPROM;
			पूर्ण
			/* get ack */
			tonga |= SEPROM_DATA;
			SET_SEPROM;
			tonga |= SEPROM_CLK;
			SET_SEPROM;
			GET_SEPROM;
			अगर (!(tonga & SEPROM_DATA)) error = -EIO;
			tonga &= ~SEPROM_CLK;
			SET_SEPROM;
			tonga |= SEPROM_DATA;
			SET_SEPROM;
		पूर्ण
		/* stop operation */
		tonga &= ~SEPROM_DATA;
		SET_SEPROM;
		tonga |= SEPROM_CLK;
		SET_SEPROM;
		tonga |= SEPROM_DATA;
		SET_SEPROM;
	पूर्ण
	अगर (pci_error) अणु
		prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): error reading ESI "
		    "(0x%02x)\n",dev->number,pci_error);
		error = -EIO;
	पूर्ण
	वापस error;
पूर्ण


#अघोषित SET_SEPROM
#अघोषित GET_SEPROM


अटल पूर्णांक get_esi_fpga(काष्ठा aपंचांग_dev *dev, व्योम __iomem *base)
अणु
	व्योम __iomem *mac_base;
	पूर्णांक i;

	mac_base = base+EPROM_SIZE-माप(काष्ठा midway_eprom);
	क्रम (i = 0; i < ESI_LEN; i++) dev->esi[i] = पढ़ोb(mac_base+(i^3));
	वापस 0;
पूर्ण


अटल पूर्णांक eni_करो_init(काष्ठा aपंचांग_dev *dev)
अणु
	काष्ठा midway_eprom __iomem *eprom;
	काष्ठा eni_dev *eni_dev;
	काष्ठा pci_dev *pci_dev;
	अचिन्हित दीर्घ real_base;
	व्योम __iomem *base;
	पूर्णांक error,i,last;

	DPRINTK(">eni_init\n");
	dev->ci_range.vpi_bits = 0;
	dev->ci_range.vci_bits = NR_VCI_LD;
	dev->link_rate = ATM_OC3_PCR;
	eni_dev = ENI_DEV(dev);
	pci_dev = eni_dev->pci_dev;
	real_base = pci_resource_start(pci_dev, 0);
	eni_dev->irq = pci_dev->irq;
	अगर ((error = pci_ग_लिखो_config_word(pci_dev,PCI_COMMAND,
	    PCI_COMMAND_MEMORY |
	    (eni_dev->asic ? PCI_COMMAND_PARITY | PCI_COMMAND_SERR : 0)))) अणु
		prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): can't enable memory "
		    "(0x%02x)\n",dev->number,error);
		वापस -EIO;
	पूर्ण
	prपूर्णांकk(KERN_NOTICE DEV_LABEL "(itf %d): rev.%d,base=0x%lx,irq=%d,",
	    dev->number,pci_dev->revision,real_base,eni_dev->irq);
	अगर (!(base = ioremap(real_base,MAP_MAX_SIZE))) अणु
		prपूर्णांकk("\n");
		prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): can't set up page "
		    "mapping\n",dev->number);
		वापस -ENOMEM;
	पूर्ण
	eni_dev->ioaddr = base;
	eni_dev->base_dअगरf = real_base - (अचिन्हित दीर्घ) base;
	/* id may not be present in ASIC Tonga boards - check this @@@ */
	अगर (!eni_dev->asic) अणु
		eprom = (base+EPROM_SIZE-माप(काष्ठा midway_eprom));
		अगर (पढ़ोl(&eprom->magic) != ENI155_MAGIC) अणु
			prपूर्णांकk("\n");
			prपूर्णांकk(KERN_ERR DEV_LABEL
			       "(itf %d): bad magic - expected 0x%x, got 0x%x\n",
			       dev->number, ENI155_MAGIC,
			       (अचिन्हित)पढ़ोl(&eprom->magic));
			error = -EINVAL;
			जाओ unmap;
		पूर्ण
	पूर्ण
	eni_dev->phy = base+PHY_BASE;
	eni_dev->reg = base+REG_BASE;
	eni_dev->ram = base+RAM_BASE;
	last = MAP_MAX_SIZE-RAM_BASE;
	क्रम (i = last-RAM_INCREMENT; i >= 0; i -= RAM_INCREMENT) अणु
		ग_लिखोl(0x55555555,eni_dev->ram+i);
		अगर (पढ़ोl(eni_dev->ram+i) != 0x55555555) last = i;
		अन्यथा अणु
			ग_लिखोl(0xAAAAAAAA,eni_dev->ram+i);
			अगर (पढ़ोl(eni_dev->ram+i) != 0xAAAAAAAA) last = i;
			अन्यथा ग_लिखोl(i,eni_dev->ram+i);
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < last; i += RAM_INCREMENT)
		अगर (पढ़ोl(eni_dev->ram+i) != i) अवरोध;
	eni_dev->mem = i;
	स_रखो_io(eni_dev->ram,0,eni_dev->mem);
	/* TODO: should shrink allocation now */
	prपूर्णांकk("mem=%dkB (",eni_dev->mem >> 10);
	/* TODO: check क्रम non-SUNI, check क्रम TAXI ? */
	अगर (!(eni_in(MID_RES_ID_MCON) & 0x200) != !eni_dev->asic) अणु
		prपूर्णांकk(")\n");
		prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): ERROR - wrong id 0x%x\n",
		    dev->number,(अचिन्हित) eni_in(MID_RES_ID_MCON));
		error = -EINVAL;
		जाओ unmap;
	पूर्ण
	error = eni_dev->asic ? get_esi_asic(dev) : get_esi_fpga(dev,base);
	अगर (error)
		जाओ unmap;
	क्रम (i = 0; i < ESI_LEN; i++)
		prपूर्णांकk("%s%02X",i ? "-" : "",dev->esi[i]);
	prपूर्णांकk(")\n");
	prपूर्णांकk(KERN_NOTICE DEV_LABEL "(itf %d): %s,%s\n",dev->number,
	    eni_in(MID_RES_ID_MCON) & 0x200 ? "ASIC" : "FPGA",
	    media_name[eni_in(MID_RES_ID_MCON) & DAUGHTER_ID]);

	error = suni_init(dev);
	अगर (error)
		जाओ unmap;
out:
	वापस error;
unmap:
	iounmap(base);
	जाओ out;
पूर्ण

अटल व्योम eni_करो_release(काष्ठा aपंचांग_dev *dev)
अणु
	काष्ठा eni_dev *ed = ENI_DEV(dev);

	dev->phy->stop(dev);
	dev->phy = शून्य;
	iounmap(ed->ioaddr);
पूर्ण

अटल पूर्णांक eni_start(काष्ठा aपंचांग_dev *dev)
अणु
	काष्ठा eni_dev *eni_dev;
	
	व्योम __iomem *buf;
	अचिन्हित दीर्घ buffer_mem;
	पूर्णांक error;

	DPRINTK(">eni_start\n");
	eni_dev = ENI_DEV(dev);
	अगर (request_irq(eni_dev->irq,&eni_पूर्णांक,IRQF_SHARED,DEV_LABEL,dev)) अणु
		prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): IRQ%d is already in use\n",
		    dev->number,eni_dev->irq);
		error = -EAGAIN;
		जाओ out;
	पूर्ण
	pci_set_master(eni_dev->pci_dev);
	अगर ((error = pci_ग_लिखो_config_word(eni_dev->pci_dev,PCI_COMMAND,
	    PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER |
	    (eni_dev->asic ? PCI_COMMAND_PARITY | PCI_COMMAND_SERR : 0)))) अणु
		prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): can't enable memory+"
		    "master (0x%02x)\n",dev->number,error);
		जाओ मुक्त_irq;
	पूर्ण
	अगर ((error = pci_ग_लिखो_config_byte(eni_dev->pci_dev,PCI_TONGA_CTRL,
	    END_SWAP_DMA))) अणु
		prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): can't set endian swap "
		    "(0x%02x)\n",dev->number,error);
		जाओ मुक्त_irq;
	पूर्ण
	/* determine addresses of पूर्णांकernal tables */
	eni_dev->vci = eni_dev->ram;
	eni_dev->rx_dma = eni_dev->ram+NR_VCI*16;
	eni_dev->tx_dma = eni_dev->rx_dma+NR_DMA_RX*8;
	eni_dev->service = eni_dev->tx_dma+NR_DMA_TX*8;
	buf = eni_dev->service+NR_SERVICE*4;
	DPRINTK("vci 0x%lx,rx 0x%lx, tx 0x%lx,srv 0x%lx,buf 0x%lx\n",
	     eni_dev->vci,eni_dev->rx_dma,eni_dev->tx_dma,
	     eni_dev->service,buf);
	spin_lock_init(&eni_dev->lock);
	tasklet_init(&eni_dev->task,eni_tasklet,(अचिन्हित दीर्घ) dev);
	eni_dev->events = 0;
	/* initialize memory management */
	buffer_mem = eni_dev->mem - (buf - eni_dev->ram);
	eni_dev->मुक्त_list_size = buffer_mem/MID_MIN_BUF_SIZE/2;
	eni_dev->मुक्त_list = kदो_स्मृति_array(eni_dev->मुक्त_list_size + 1,
					   माप(*eni_dev->मुक्त_list),
					   GFP_KERNEL);
	अगर (!eni_dev->मुक्त_list) अणु
		prपूर्णांकk(KERN_ERR DEV_LABEL "(itf %d): couldn't get free page\n",
		    dev->number);
		error = -ENOMEM;
		जाओ मुक्त_irq;
	पूर्ण
	eni_dev->मुक्त_len = 0;
	eni_put_मुक्त(eni_dev,buf,buffer_mem);
	स_रखो_io(eni_dev->vci,0,16*NR_VCI); /* clear VCI table */
	/*
	 * byte_addr  मुक्त (k)
	 * 0x00000000     512  VCI table
	 * 0x00004000	  496  RX DMA
	 * 0x00005000	  492  TX DMA
	 * 0x00006000	  488  service list
	 * 0x00007000	  484  buffers
	 * 0x00080000	    0  end (512kB)
	 */
	eni_out(0xffffffff,MID_IE);
	error = start_tx(dev);
	अगर (error) जाओ मुक्त_list;
	error = start_rx(dev);
	अगर (error) जाओ मुक्त_list;
	error = dev->phy->start(dev);
	अगर (error) जाओ मुक्त_list;
	eni_out(eni_in(MID_MC_S) | (1 << MID_INT_SEL_SHIFT) |
	    MID_TX_LOCK_MODE | MID_DMA_ENABLE | MID_TX_ENABLE | MID_RX_ENABLE,
	    MID_MC_S);
	    /* Tonga uses SBus INTReq1 */
	(व्योम) eni_in(MID_ISA); /* clear Midway पूर्णांकerrupts */
	वापस 0;

मुक्त_list:
	kमुक्त(eni_dev->मुक्त_list);

मुक्त_irq:
	मुक्त_irq(eni_dev->irq, dev);

out:
	वापस error;
पूर्ण


अटल व्योम eni_बंद(काष्ठा aपंचांग_vcc *vcc)
अणु
	DPRINTK(">eni_close\n");
	अगर (!ENI_VCC(vcc)) वापस;
	clear_bit(ATM_VF_READY,&vcc->flags);
	बंद_rx(vcc);
	बंद_tx(vcc);
	DPRINTK("eni_close: done waiting\n");
	/* deallocate memory */
	kमुक्त(ENI_VCC(vcc));
	vcc->dev_data = शून्य;
	clear_bit(ATM_VF_ADDR,&vcc->flags);
	/*foo();*/
पूर्ण


अटल पूर्णांक eni_खोलो(काष्ठा aपंचांग_vcc *vcc)
अणु
	काष्ठा eni_vcc *eni_vcc;
	पूर्णांक error;
	लघु vpi = vcc->vpi;
	पूर्णांक vci = vcc->vci;

	DPRINTK(">eni_open\n");
	EVENT("eni_open\n",0,0);
	अगर (!test_bit(ATM_VF_PARTIAL,&vcc->flags))
		vcc->dev_data = शून्य;
	अगर (vci != ATM_VPI_UNSPEC && vpi != ATM_VCI_UNSPEC)
		set_bit(ATM_VF_ADDR,&vcc->flags);
	अगर (vcc->qos.aal != ATM_AAL0 && vcc->qos.aal != ATM_AAL5)
		वापस -EINVAL;
	DPRINTK(DEV_LABEL "(itf %d): open %d.%d\n",vcc->dev->number,vcc->vpi,
	    vcc->vci);
	अगर (!test_bit(ATM_VF_PARTIAL,&vcc->flags)) अणु
		eni_vcc = kदो_स्मृति(माप(काष्ठा eni_vcc),GFP_KERNEL);
		अगर (!eni_vcc) वापस -ENOMEM;
		vcc->dev_data = eni_vcc;
		eni_vcc->tx = शून्य; /* क्रम eni_बंद after खोलो_rx */
		अगर ((error = खोलो_rx_first(vcc))) अणु
			eni_बंद(vcc);
			वापस error;
		पूर्ण
		अगर ((error = खोलो_tx_first(vcc))) अणु
			eni_बंद(vcc);
			वापस error;
		पूर्ण
	पूर्ण
	अगर (vci == ATM_VPI_UNSPEC || vpi == ATM_VCI_UNSPEC) वापस 0;
	अगर ((error = खोलो_rx_second(vcc))) अणु
		eni_बंद(vcc);
		वापस error;
	पूर्ण
	अगर ((error = खोलो_tx_second(vcc))) अणु
		eni_बंद(vcc);
		वापस error;
	पूर्ण
	set_bit(ATM_VF_READY,&vcc->flags);
	/* should घातer करोwn SUNI जबतक !ref_count @@@ */
	वापस 0;
पूर्ण


अटल पूर्णांक eni_change_qos(काष्ठा aपंचांग_vcc *vcc,काष्ठा aपंचांग_qos *qos,पूर्णांक flgs)
अणु
	काष्ठा eni_dev *eni_dev = ENI_DEV(vcc->dev);
	काष्ठा eni_tx *tx = ENI_VCC(vcc)->tx;
	काष्ठा sk_buff *skb;
	पूर्णांक error,rate,rsv,shp;

	अगर (qos->txtp.traffic_class == ATM_NONE) वापस 0;
	अगर (tx == eni_dev->ubr) वापस -EBADFD;
	rate = aपंचांग_pcr_goal(&qos->txtp);
	अगर (rate < 0) rate = -rate;
	rsv = shp = 0;
	अगर ((flgs & ATM_MF_DEC_RSV) && rate && rate < tx->reserved) rsv = 1;
	अगर ((flgs & ATM_MF_INC_RSV) && (!rate || rate > tx->reserved)) rsv = 1;
	अगर ((flgs & ATM_MF_DEC_SHP) && rate && rate < tx->shaping) shp = 1;
	अगर ((flgs & ATM_MF_INC_SHP) && (!rate || rate > tx->shaping)) shp = 1;
	अगर (!rsv && !shp) वापस 0;
	error = reserve_or_set_tx(vcc,&qos->txtp,rsv,shp);
	अगर (error) वापस error;
	अगर (shp && !(flgs & ATM_MF_IMMED)) वापस 0;
	/*
	 * Walk through the send buffer and patch the rate inक्रमmation in all
	 * segmentation buffer descriptors of this VCC.
	 */
	tasklet_disable(&eni_dev->task);
	skb_queue_walk(&eni_dev->tx_queue, skb) अणु
		व्योम __iomem *dsc;

		अगर (ATM_SKB(skb)->vcc != vcc) जारी;
		dsc = tx->send+ENI_PRV_POS(skb)*4;
		ग_लिखोl((पढ़ोl(dsc) & ~(MID_SEG_RATE | MID_SEG_PR)) |
		    (tx->prescaler << MID_SEG_PR_SHIFT) |
		    (tx->resolution << MID_SEG_RATE_SHIFT), dsc);
	पूर्ण
	tasklet_enable(&eni_dev->task);
	वापस 0;
पूर्ण


अटल पूर्णांक eni_ioctl(काष्ठा aपंचांग_dev *dev,अचिन्हित पूर्णांक cmd,व्योम __user *arg)
अणु
	काष्ठा eni_dev *eni_dev = ENI_DEV(dev);

	अगर (cmd == ENI_MEMDUMP) अणु
		अगर (!capable(CAP_NET_ADMIN)) वापस -EPERM;
		prपूर्णांकk(KERN_WARNING "Please use /proc/atm/" DEV_LABEL ":%d "
		    "instead of obsolete ioctl ENI_MEMDUMP\n",dev->number);
		dump(dev);
		वापस 0;
	पूर्ण
	अगर (cmd == ENI_SETMULT) अणु
		काष्ठा eni_multipliers mult;

		अगर (!capable(CAP_NET_ADMIN)) वापस -EPERM;
		अगर (copy_from_user(&mult, arg,
		    माप(काष्ठा eni_multipliers)))
			वापस -EFAULT;
		अगर ((mult.tx && mult.tx <= 100) || (mult.rx &&mult.rx <= 100) ||
		    mult.tx > 65536 || mult.rx > 65536)
			वापस -EINVAL;
		अगर (mult.tx) eni_dev->tx_mult = mult.tx;
		अगर (mult.rx) eni_dev->rx_mult = mult.rx;
		वापस 0;
	पूर्ण
	अगर (cmd == ATM_SETCIRANGE) अणु
		काष्ठा aपंचांग_cirange ci;

		अगर (copy_from_user(&ci, arg,माप(काष्ठा aपंचांग_cirange)))
			वापस -EFAULT;
		अगर ((ci.vpi_bits == 0 || ci.vpi_bits == ATM_CI_MAX) &&
		    (ci.vci_bits == NR_VCI_LD || ci.vpi_bits == ATM_CI_MAX))
		    वापस 0;
		वापस -EINVAL;
	पूर्ण
	अगर (!dev->phy->ioctl) वापस -ENOIOCTLCMD;
	वापस dev->phy->ioctl(dev,cmd,arg);
पूर्ण

अटल पूर्णांक eni_send(काष्ठा aपंचांग_vcc *vcc,काष्ठा sk_buff *skb)
अणु
	क्रमागत enq_res res;

	DPRINTK(">eni_send\n");
	अगर (!ENI_VCC(vcc)->tx) अणु
		अगर (vcc->pop) vcc->pop(vcc,skb);
		अन्यथा dev_kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण
	अगर (!skb) अणु
		prपूर्णांकk(KERN_CRIT "!skb in eni_send ?\n");
		अगर (vcc->pop) vcc->pop(vcc,skb);
		वापस -EINVAL;
	पूर्ण
	अगर (vcc->qos.aal == ATM_AAL0) अणु
		अगर (skb->len != ATM_CELL_SIZE-1) अणु
			अगर (vcc->pop) vcc->pop(vcc,skb);
			अन्यथा dev_kमुक्त_skb(skb);
			वापस -EINVAL;
		पूर्ण
		*(u32 *) skb->data = htonl(*(u32 *) skb->data);
	पूर्ण
	submitted++;
	ATM_SKB(skb)->vcc = vcc;
	tasklet_disable_in_atomic(&ENI_DEV(vcc->dev)->task);
	res = करो_tx(skb);
	tasklet_enable(&ENI_DEV(vcc->dev)->task);
	अगर (res == enq_ok) वापस 0;
	skb_queue_tail(&ENI_VCC(vcc)->tx->backlog,skb);
	backlogged++;
	tasklet_schedule(&ENI_DEV(vcc->dev)->task);
	वापस 0;
पूर्ण

अटल व्योम eni_phy_put(काष्ठा aपंचांग_dev *dev,अचिन्हित अक्षर value,
    अचिन्हित दीर्घ addr)
अणु
	ग_लिखोl(value,ENI_DEV(dev)->phy+addr*4);
पूर्ण



अटल अचिन्हित अक्षर eni_phy_get(काष्ठा aपंचांग_dev *dev,अचिन्हित दीर्घ addr)
अणु
	वापस पढ़ोl(ENI_DEV(dev)->phy+addr*4);
पूर्ण


अटल पूर्णांक eni_proc_पढ़ो(काष्ठा aपंचांग_dev *dev,loff_t *pos,अक्षर *page)
अणु
	काष्ठा sock *s;
	अटल स्थिर अक्षर *संकेत[] = अणु "LOST","unknown","okay" पूर्ण;
	काष्ठा eni_dev *eni_dev = ENI_DEV(dev);
	काष्ठा aपंचांग_vcc *vcc;
	पूर्णांक left,i;

	left = *pos;
	अगर (!left)
		वापस प्र_लिखो(page,DEV_LABEL "(itf %d) signal %s, %dkB, "
		    "%d cps remaining\n",dev->number,संकेत[(पूर्णांक) dev->संकेत],
		    eni_dev->mem >> 10,eni_dev->tx_bw);
	अगर (!--left)
		वापस प्र_लिखो(page,"%4sBursts: TX"
#अगर !defined(CONFIG_ATM_ENI_BURST_TX_16W) && \
    !defined(CONFIG_ATM_ENI_BURST_TX_8W) && \
    !defined(CONFIG_ATM_ENI_BURST_TX_4W) && \
    !defined(CONFIG_ATM_ENI_BURST_TX_2W)
		    " none"
#पूर्ण_अगर
#अगर_घोषित CONFIG_ATM_ENI_BURST_TX_16W
		    " 16W"
#पूर्ण_अगर
#अगर_घोषित CONFIG_ATM_ENI_BURST_TX_8W
		    " 8W"
#पूर्ण_अगर
#अगर_घोषित CONFIG_ATM_ENI_BURST_TX_4W
		    " 4W"
#पूर्ण_अगर
#अगर_घोषित CONFIG_ATM_ENI_BURST_TX_2W
		    " 2W"
#पूर्ण_अगर
		    ", RX"
#अगर !defined(CONFIG_ATM_ENI_BURST_RX_16W) && \
    !defined(CONFIG_ATM_ENI_BURST_RX_8W) && \
    !defined(CONFIG_ATM_ENI_BURST_RX_4W) && \
    !defined(CONFIG_ATM_ENI_BURST_RX_2W)
		    " none"
#पूर्ण_अगर
#अगर_घोषित CONFIG_ATM_ENI_BURST_RX_16W
		    " 16W"
#पूर्ण_अगर
#अगर_घोषित CONFIG_ATM_ENI_BURST_RX_8W
		    " 8W"
#पूर्ण_अगर
#अगर_घोषित CONFIG_ATM_ENI_BURST_RX_4W
		    " 4W"
#पूर्ण_अगर
#अगर_घोषित CONFIG_ATM_ENI_BURST_RX_2W
		    " 2W"
#पूर्ण_अगर
#अगर_अघोषित CONFIG_ATM_ENI_TUNE_BURST
		    " (default)"
#पूर्ण_अगर
		    "\n","");
	अगर (!--left) 
		वापस प्र_लिखो(page,"%4sBuffer multipliers: tx %d%%, rx %d%%\n",
		    "",eni_dev->tx_mult,eni_dev->rx_mult);
	क्रम (i = 0; i < NR_CHAN; i++) अणु
		काष्ठा eni_tx *tx = eni_dev->tx+i;

		अगर (!tx->send) जारी;
		अगर (!--left) अणु
			वापस प्र_लिखो(page, "tx[%d]:    0x%lx-0x%lx "
			    "(%6ld bytes), rsv %d cps, shp %d cps%s\n",i,
			    (अचिन्हित दीर्घ) (tx->send - eni_dev->ram),
			    tx->send-eni_dev->ram+tx->words*4-1,tx->words*4,
			    tx->reserved,tx->shaping,
			    tx == eni_dev->ubr ? " (UBR)" : "");
		पूर्ण
		अगर (--left) जारी;
		वापस प्र_लिखो(page,"%10sbacklog %u packets\n","",
		    skb_queue_len(&tx->backlog));
	पूर्ण
	पढ़ो_lock(&vcc_sklist_lock);
	क्रम(i = 0; i < VCC_HTABLE_SIZE; ++i) अणु
		काष्ठा hlist_head *head = &vcc_hash[i];

		sk_क्रम_each(s, head) अणु
			काष्ठा eni_vcc *eni_vcc;
			पूर्णांक length;

			vcc = aपंचांग_sk(s);
			अगर (vcc->dev != dev)
				जारी;
			eni_vcc = ENI_VCC(vcc);
			अगर (--left) जारी;
			length = प्र_लिखो(page,"vcc %4d: ",vcc->vci);
			अगर (eni_vcc->rx) अणु
				length += प्र_लिखो(page+length, "0x%lx-0x%lx "
				    "(%6ld bytes)",
				    (अचिन्हित दीर्घ) (eni_vcc->recv - eni_dev->ram),
				    eni_vcc->recv-eni_dev->ram+eni_vcc->words*4-1,
				    eni_vcc->words*4);
				अगर (eni_vcc->tx) length += प्र_लिखो(page+length,", ");
			पूर्ण
			अगर (eni_vcc->tx)
				length += प्र_लिखो(page+length,"tx[%d], txing %d bytes",
				    eni_vcc->tx->index,eni_vcc->txing);
			page[length] = '\n';
			पढ़ो_unlock(&vcc_sklist_lock);
			वापस length+1;
		पूर्ण
	पूर्ण
	पढ़ो_unlock(&vcc_sklist_lock);
	क्रम (i = 0; i < eni_dev->मुक्त_len; i++) अणु
		काष्ठा eni_मुक्त *fe = eni_dev->मुक्त_list+i;
		अचिन्हित दीर्घ offset;

		अगर (--left) जारी;
		offset = (अचिन्हित दीर्घ) eni_dev->ram+eni_dev->base_dअगरf;
		वापस प्र_लिखो(page,"free      %p-%p (%6d bytes)\n",
		    fe->start-offset,fe->start-offset+(1 << fe->order)-1,
		    1 << fe->order);
	पूर्ण
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा aपंचांगdev_ops ops = अणु
	.खोलो		= eni_खोलो,
	.बंद		= eni_बंद,
	.ioctl		= eni_ioctl,
	.send		= eni_send,
	.phy_put	= eni_phy_put,
	.phy_get	= eni_phy_get,
	.change_qos	= eni_change_qos,
	.proc_पढ़ो	= eni_proc_पढ़ो
पूर्ण;


अटल पूर्णांक eni_init_one(काष्ठा pci_dev *pci_dev,
			स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा aपंचांग_dev *dev;
	काष्ठा eni_dev *eni_dev;
	काष्ठा eni_zero *zero;
	पूर्णांक rc;

	rc = pci_enable_device(pci_dev);
	अगर (rc < 0)
		जाओ out;

	rc = dma_set_mask_and_coherent(&pci_dev->dev, DMA_BIT_MASK(32));
	अगर (rc < 0)
		जाओ err_disable;

	rc = -ENOMEM;
	eni_dev = kदो_स्मृति(माप(काष्ठा eni_dev), GFP_KERNEL);
	अगर (!eni_dev)
		जाओ err_disable;

	zero = &eni_dev->zero;
	zero->addr = dma_alloc_coherent(&pci_dev->dev,
					ENI_ZEROES_SIZE, &zero->dma, GFP_KERNEL);
	अगर (!zero->addr)
		जाओ err_kमुक्त;

	dev = aपंचांग_dev_रेजिस्टर(DEV_LABEL, &pci_dev->dev, &ops, -1, शून्य);
	अगर (!dev)
		जाओ err_मुक्त_consistent;

	dev->dev_data = eni_dev;
	pci_set_drvdata(pci_dev, dev);
	eni_dev->pci_dev = pci_dev;
	eni_dev->asic = ent->driver_data;

	rc = eni_करो_init(dev);
	अगर (rc < 0)
		जाओ err_unरेजिस्टर;

	rc = eni_start(dev);
	अगर (rc < 0)
		जाओ err_eni_release;

	eni_dev->more = eni_boards;
	eni_boards = dev;
out:
	वापस rc;

err_eni_release:
	dev->phy = शून्य;
	iounmap(ENI_DEV(dev)->ioaddr);
err_unरेजिस्टर:
	aपंचांग_dev_deरेजिस्टर(dev);
err_मुक्त_consistent:
	dma_मुक्त_coherent(&pci_dev->dev, ENI_ZEROES_SIZE, zero->addr, zero->dma);
err_kमुक्त:
	kमुक्त(eni_dev);
err_disable:
	pci_disable_device(pci_dev);
	जाओ out;
पूर्ण


अटल स्थिर काष्ठा pci_device_id eni_pci_tbl[] = अणु
	अणु PCI_VDEVICE(EF, PCI_DEVICE_ID_EF_ATM_FPGA), 0 /* FPGA */ पूर्ण,
	अणु PCI_VDEVICE(EF, PCI_DEVICE_ID_EF_ATM_ASIC), 1 /* ASIC */ पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci,eni_pci_tbl);


अटल व्योम eni_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा aपंचांग_dev *dev = pci_get_drvdata(pdev);
	काष्ठा eni_dev *ed = ENI_DEV(dev);
	काष्ठा eni_zero *zero = &ed->zero;

	eni_करो_release(dev);
	aपंचांग_dev_deरेजिस्टर(dev);
	dma_मुक्त_coherent(&pdev->dev, ENI_ZEROES_SIZE, zero->addr, zero->dma);
	kमुक्त(ed);
	pci_disable_device(pdev);
पूर्ण


अटल काष्ठा pci_driver eni_driver = अणु
	.name		= DEV_LABEL,
	.id_table	= eni_pci_tbl,
	.probe		= eni_init_one,
	.हटाओ		= eni_हटाओ_one,
पूर्ण;


अटल पूर्णांक __init eni_init(व्योम)
अणु
	काष्ठा sk_buff *skb; /* dummy क्रम माप */

	BUILD_BUG_ON(माप(skb->cb) < माप(काष्ठा eni_skb_prv));
	वापस pci_रेजिस्टर_driver(&eni_driver);
पूर्ण


module_init(eni_init);
/* @@@ since निकास routine not defined, this module can not be unloaded */

MODULE_LICENSE("GPL");
