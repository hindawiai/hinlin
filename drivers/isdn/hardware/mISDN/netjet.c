<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * NETJet mISDN driver
 *
 * Author       Karsten Keil <keil@isdn4linux.de>
 *
 * Copyright 2009  by Karsten Keil <keil@isdn4linux.de>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/mISDNhw.h>
#समावेश <linux/slab.h>
#समावेश "ipac.h"
#समावेश "iohelper.h"
#समावेश "netjet.h"
#समावेश "isdnhdlc.h"

#घोषणा NETJET_REV	"2.0"

क्रमागत nj_types अणु
	NETJET_S_TJ300,
	NETJET_S_TJ320,
	ENTERNOW__TJ320,
पूर्ण;

काष्ठा tiger_dma अणु
	माप_प्रकार		size;
	u32		*start;
	पूर्णांक		idx;
	u32		dmastart;
	u32		dmairq;
	u32		dmaend;
	u32		dmacur;
पूर्ण;

काष्ठा tiger_hw;

काष्ठा tiger_ch अणु
	काष्ठा bchannel		bch;
	काष्ठा tiger_hw		*nj;
	पूर्णांक			idx;
	पूर्णांक			मुक्त;
	पूर्णांक			lastrx;
	u16			rxstate;
	u16			txstate;
	काष्ठा isdnhdlc_vars	hsend;
	काष्ठा isdnhdlc_vars	hrecv;
	u8			*hsbuf;
	u8			*hrbuf;
पूर्ण;

#घोषणा TX_INIT		0x0001
#घोषणा TX_IDLE		0x0002
#घोषणा TX_RUN		0x0004
#घोषणा TX_UNDERRUN	0x0100
#घोषणा RX_OVERRUN	0x0100

#घोषणा LOG_SIZE	64

काष्ठा tiger_hw अणु
	काष्ठा list_head	list;
	काष्ठा pci_dev		*pdev;
	अक्षर			name[MISDN_MAX_IDLEN];
	क्रमागत nj_types		typ;
	पूर्णांक			irq;
	u32			irqcnt;
	u32			base;
	माप_प्रकार			base_s;
	dma_addr_t		dma;
	व्योम			*dma_p;
	spinlock_t		lock;	/* lock HW */
	काष्ठा isac_hw		isac;
	काष्ठा tiger_dma	send;
	काष्ठा tiger_dma	recv;
	काष्ठा tiger_ch		bc[2];
	u8			ctrlreg;
	u8			dmactrl;
	u8			auxd;
	u8			last_is0;
	u8			irqmask0;
	अक्षर			log[LOG_SIZE];
पूर्ण;

अटल LIST_HEAD(Cards);
अटल DEFINE_RWLOCK(card_lock); /* protect Cards */
अटल u32 debug;
अटल पूर्णांक nj_cnt;

अटल व्योम
_set_debug(काष्ठा tiger_hw *card)
अणु
	card->isac.dch.debug = debug;
	card->bc[0].bch.debug = debug;
	card->bc[1].bch.debug = debug;
पूर्ण

अटल पूर्णांक
set_debug(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक ret;
	काष्ठा tiger_hw *card;

	ret = param_set_uपूर्णांक(val, kp);
	अगर (!ret) अणु
		पढ़ो_lock(&card_lock);
		list_क्रम_each_entry(card, &Cards, list)
			_set_debug(card);
		पढ़ो_unlock(&card_lock);
	पूर्ण
	वापस ret;
पूर्ण

MODULE_AUTHOR("Karsten Keil");
MODULE_LICENSE("GPL v2");
MODULE_VERSION(NETJET_REV);
module_param_call(debug, set_debug, param_get_uपूर्णांक, &debug, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(debug, "Netjet debug mask");

अटल व्योम
nj_disable_hwirq(काष्ठा tiger_hw *card)
अणु
	outb(0, card->base + NJ_IRQMASK0);
	outb(0, card->base + NJ_IRQMASK1);
पूर्ण


अटल u8
ReadISAC_nj(व्योम *p, u8 offset)
अणु
	काष्ठा tiger_hw *card = p;
	u8 ret;

	card->auxd &= 0xfc;
	card->auxd |= (offset >> 4) & 3;
	outb(card->auxd, card->base + NJ_AUXDATA);
	ret = inb(card->base + NJ_ISAC_OFF + ((offset & 0x0f) << 2));
	वापस ret;
पूर्ण

अटल व्योम
WriteISAC_nj(व्योम *p, u8 offset, u8 value)
अणु
	काष्ठा tiger_hw *card = p;

	card->auxd &= 0xfc;
	card->auxd |= (offset >> 4) & 3;
	outb(card->auxd, card->base + NJ_AUXDATA);
	outb(value, card->base + NJ_ISAC_OFF + ((offset & 0x0f) << 2));
पूर्ण

अटल व्योम
ReadFiFoISAC_nj(व्योम *p, u8 offset, u8 *data, पूर्णांक size)
अणु
	काष्ठा tiger_hw *card = p;

	card->auxd &= 0xfc;
	outb(card->auxd, card->base + NJ_AUXDATA);
	insb(card->base + NJ_ISAC_OFF, data, size);
पूर्ण

अटल व्योम
WriteFiFoISAC_nj(व्योम *p, u8 offset, u8 *data, पूर्णांक size)
अणु
	काष्ठा tiger_hw *card = p;

	card->auxd &= 0xfc;
	outb(card->auxd, card->base + NJ_AUXDATA);
	outsb(card->base + NJ_ISAC_OFF, data, size);
पूर्ण

अटल व्योम
fill_mem(काष्ठा tiger_ch *bc, u32 idx, u32 cnt, u32 fill)
अणु
	काष्ठा tiger_hw *card = bc->bch.hw;
	u32 mask = 0xff, val;

	pr_debug("%s: B%1d fill %02x len %d idx %d/%d\n", card->name,
		 bc->bch.nr, fill, cnt, idx, card->send.idx);
	अगर (bc->bch.nr & 2) अणु
		fill  <<= 8;
		mask <<= 8;
	पूर्ण
	mask ^= 0xffffffff;
	जबतक (cnt--) अणु
		val = card->send.start[idx];
		val &= mask;
		val |= fill;
		card->send.start[idx++] = val;
		अगर (idx >= card->send.size)
			idx = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक
mode_tiger(काष्ठा tiger_ch *bc, u32 protocol)
अणु
	काष्ठा tiger_hw *card = bc->bch.hw;

	pr_debug("%s: B%1d protocol %x-->%x\n", card->name,
		 bc->bch.nr, bc->bch.state, protocol);
	चयन (protocol) अणु
	हाल ISDN_P_NONE:
		अगर (bc->bch.state == ISDN_P_NONE)
			अवरोध;
		fill_mem(bc, 0, card->send.size, 0xff);
		bc->bch.state = protocol;
		/* only stop dma and पूर्णांकerrupts अगर both channels शून्य */
		अगर ((card->bc[0].bch.state == ISDN_P_NONE) &&
		    (card->bc[1].bch.state == ISDN_P_NONE)) अणु
			card->dmactrl = 0;
			outb(card->dmactrl, card->base + NJ_DMACTRL);
			outb(0, card->base + NJ_IRQMASK0);
		पूर्ण
		test_and_clear_bit(FLG_HDLC, &bc->bch.Flags);
		test_and_clear_bit(FLG_TRANSPARENT, &bc->bch.Flags);
		bc->txstate = 0;
		bc->rxstate = 0;
		bc->lastrx = -1;
		अवरोध;
	हाल ISDN_P_B_RAW:
		test_and_set_bit(FLG_TRANSPARENT, &bc->bch.Flags);
		bc->bch.state = protocol;
		bc->idx = 0;
		bc->मुक्त = card->send.size / 2;
		bc->rxstate = 0;
		bc->txstate = TX_INIT | TX_IDLE;
		bc->lastrx = -1;
		अगर (!card->dmactrl) अणु
			card->dmactrl = 1;
			outb(card->dmactrl, card->base + NJ_DMACTRL);
			outb(0x0f, card->base + NJ_IRQMASK0);
		पूर्ण
		अवरोध;
	हाल ISDN_P_B_HDLC:
		test_and_set_bit(FLG_HDLC, &bc->bch.Flags);
		bc->bch.state = protocol;
		bc->idx = 0;
		bc->मुक्त = card->send.size / 2;
		bc->rxstate = 0;
		bc->txstate = TX_INIT | TX_IDLE;
		isdnhdlc_rcv_init(&bc->hrecv, 0);
		isdnhdlc_out_init(&bc->hsend, 0);
		bc->lastrx = -1;
		अगर (!card->dmactrl) अणु
			card->dmactrl = 1;
			outb(card->dmactrl, card->base + NJ_DMACTRL);
			outb(0x0f, card->base + NJ_IRQMASK0);
		पूर्ण
		अवरोध;
	शेष:
		pr_info("%s: %s protocol %x not handled\n", card->name,
			__func__, protocol);
		वापस -ENOPROTOOPT;
	पूर्ण
	card->send.dmacur = inl(card->base + NJ_DMA_READ_ADR);
	card->recv.dmacur = inl(card->base + NJ_DMA_WRITE_ADR);
	card->send.idx = (card->send.dmacur - card->send.dmastart) >> 2;
	card->recv.idx = (card->recv.dmacur - card->recv.dmastart) >> 2;
	pr_debug("%s: %s ctrl %x irq  %02x/%02x idx %d/%d\n",
		 card->name, __func__,
		 inb(card->base + NJ_DMACTRL),
		 inb(card->base + NJ_IRQMASK0),
		 inb(card->base + NJ_IRQSTAT0),
		 card->send.idx,
		 card->recv.idx);
	वापस 0;
पूर्ण

अटल व्योम
nj_reset(काष्ठा tiger_hw *card)
अणु
	outb(0xff, card->base + NJ_CTRL); /* Reset On */
	mdelay(1);

	/* now edge triggered क्रम TJ320 GE 13/07/00 */
	/* see comment in IRQ function */
	अगर (card->typ == NETJET_S_TJ320) /* TJ320 */
		card->ctrlreg = 0x40;  /* Reset Off and status पढ़ो clear */
	अन्यथा
		card->ctrlreg = 0x00;  /* Reset Off and status पढ़ो clear */
	outb(card->ctrlreg, card->base + NJ_CTRL);
	mdelay(10);

	/* configure AUX pins (all output except ISAC IRQ pin) */
	card->auxd = 0;
	card->dmactrl = 0;
	outb(~NJ_ISACIRQ, card->base + NJ_AUXCTRL);
	outb(NJ_ISACIRQ,  card->base + NJ_IRQMASK1);
	outb(card->auxd, card->base + NJ_AUXDATA);
पूर्ण

अटल पूर्णांक
inittiger(काष्ठा tiger_hw *card)
अणु
	पूर्णांक i;

	card->dma_p = dma_alloc_coherent(&card->pdev->dev, NJ_DMA_SIZE,
					 &card->dma, GFP_ATOMIC);
	अगर (!card->dma_p) अणु
		pr_info("%s: No DMA memory\n", card->name);
		वापस -ENOMEM;
	पूर्ण
	अगर ((u64)card->dma > 0xffffffff) अणु
		pr_info("%s: DMA outside 32 bit\n", card->name);
		वापस -ENOMEM;
	पूर्ण
	क्रम (i = 0; i < 2; i++) अणु
		card->bc[i].hsbuf = kदो_स्मृति(NJ_DMA_TXSIZE, GFP_ATOMIC);
		अगर (!card->bc[i].hsbuf) अणु
			pr_info("%s: no B%d send buffer\n", card->name, i + 1);
			वापस -ENOMEM;
		पूर्ण
		card->bc[i].hrbuf = kदो_स्मृति(NJ_DMA_RXSIZE, GFP_ATOMIC);
		अगर (!card->bc[i].hrbuf) अणु
			pr_info("%s: no B%d recv buffer\n", card->name, i + 1);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	स_रखो(card->dma_p, 0xff, NJ_DMA_SIZE);

	card->send.start = card->dma_p;
	card->send.dmastart = (u32)card->dma;
	card->send.dmaend = card->send.dmastart +
		(4 * (NJ_DMA_TXSIZE - 1));
	card->send.dmairq = card->send.dmastart +
		(4 * ((NJ_DMA_TXSIZE / 2) - 1));
	card->send.size = NJ_DMA_TXSIZE;

	अगर (debug & DEBUG_HW)
		pr_notice("%s: send buffer phy %#x - %#x - %#x  virt %p"
			  " size %zu u32\n", card->name,
			  card->send.dmastart, card->send.dmairq,
			  card->send.dmaend, card->send.start, card->send.size);

	outl(card->send.dmastart, card->base + NJ_DMA_READ_START);
	outl(card->send.dmairq, card->base + NJ_DMA_READ_IRQ);
	outl(card->send.dmaend, card->base + NJ_DMA_READ_END);

	card->recv.start = card->dma_p + (NJ_DMA_SIZE / 2);
	card->recv.dmastart = (u32)card->dma  + (NJ_DMA_SIZE / 2);
	card->recv.dmaend = card->recv.dmastart +
		(4 * (NJ_DMA_RXSIZE - 1));
	card->recv.dmairq = card->recv.dmastart +
		(4 * ((NJ_DMA_RXSIZE / 2) - 1));
	card->recv.size = NJ_DMA_RXSIZE;

	अगर (debug & DEBUG_HW)
		pr_notice("%s: recv buffer phy %#x - %#x - %#x  virt %p"
			  " size %zu u32\n", card->name,
			  card->recv.dmastart, card->recv.dmairq,
			  card->recv.dmaend, card->recv.start, card->recv.size);

	outl(card->recv.dmastart, card->base + NJ_DMA_WRITE_START);
	outl(card->recv.dmairq, card->base + NJ_DMA_WRITE_IRQ);
	outl(card->recv.dmaend, card->base + NJ_DMA_WRITE_END);
	वापस 0;
पूर्ण

अटल व्योम
पढ़ो_dma(काष्ठा tiger_ch *bc, u32 idx, पूर्णांक cnt)
अणु
	काष्ठा tiger_hw *card = bc->bch.hw;
	पूर्णांक i, stat;
	u32 val;
	u8 *p, *pn;

	अगर (bc->lastrx == idx) अणु
		bc->rxstate |= RX_OVERRUN;
		pr_info("%s: B%1d overrun at idx %d\n", card->name,
			bc->bch.nr, idx);
	पूर्ण
	bc->lastrx = idx;
	अगर (test_bit(FLG_RX_OFF, &bc->bch.Flags)) अणु
		bc->bch.dropcnt += cnt;
		वापस;
	पूर्ण
	stat = bchannel_get_rxbuf(&bc->bch, cnt);
	/* only transparent use the count here, HDLC overun is detected later */
	अगर (stat == -ENOMEM) अणु
		pr_warn("%s.B%d: No memory for %d bytes\n",
			card->name, bc->bch.nr, cnt);
		वापस;
	पूर्ण
	अगर (test_bit(FLG_TRANSPARENT, &bc->bch.Flags))
		p = skb_put(bc->bch.rx_skb, cnt);
	अन्यथा
		p = bc->hrbuf;

	क्रम (i = 0; i < cnt; i++) अणु
		val = card->recv.start[idx++];
		अगर (bc->bch.nr & 2)
			val >>= 8;
		अगर (idx >= card->recv.size)
			idx = 0;
		p[i] = val & 0xff;
	पूर्ण

	अगर (test_bit(FLG_TRANSPARENT, &bc->bch.Flags)) अणु
		recv_Bchannel(&bc->bch, 0, false);
		वापस;
	पूर्ण

	pn = bc->hrbuf;
	जबतक (cnt > 0) अणु
		stat = isdnhdlc_decode(&bc->hrecv, pn, cnt, &i,
				       bc->bch.rx_skb->data, bc->bch.maxlen);
		अगर (stat > 0) अणु /* valid frame received */
			p = skb_put(bc->bch.rx_skb, stat);
			अगर (debug & DEBUG_HW_BFIFO) अणु
				snम_लिखो(card->log, LOG_SIZE,
					 "B%1d-recv %s %d ", bc->bch.nr,
					 card->name, stat);
				prपूर्णांक_hex_dump_bytes(card->log,
						     DUMP_PREFIX_OFFSET, p,
						     stat);
			पूर्ण
			recv_Bchannel(&bc->bch, 0, false);
			stat = bchannel_get_rxbuf(&bc->bch, bc->bch.maxlen);
			अगर (stat < 0) अणु
				pr_warn("%s.B%d: No memory for %d bytes\n",
					card->name, bc->bch.nr, cnt);
				वापस;
			पूर्ण
		पूर्ण अन्यथा अगर (stat == -HDLC_CRC_ERROR) अणु
			pr_info("%s: B%1d receive frame CRC error\n",
				card->name, bc->bch.nr);
		पूर्ण अन्यथा अगर (stat == -HDLC_FRAMING_ERROR) अणु
			pr_info("%s: B%1d receive framing error\n",
				card->name, bc->bch.nr);
		पूर्ण अन्यथा अगर (stat == -HDLC_LENGTH_ERROR) अणु
			pr_info("%s: B%1d receive frame too long (> %d)\n",
				card->name, bc->bch.nr, bc->bch.maxlen);
		पूर्ण
		pn += i;
		cnt -= i;
	पूर्ण
पूर्ण

अटल व्योम
recv_tiger(काष्ठा tiger_hw *card, u8 irq_stat)
अणु
	u32 idx;
	पूर्णांक cnt = card->recv.size / 2;

	/* Note receive is via the WRITE DMA channel */
	card->last_is0 &= ~NJ_IRQM0_WR_MASK;
	card->last_is0 |= (irq_stat & NJ_IRQM0_WR_MASK);

	अगर (irq_stat & NJ_IRQM0_WR_END)
		idx = cnt - 1;
	अन्यथा
		idx = card->recv.size - 1;

	अगर (test_bit(FLG_ACTIVE, &card->bc[0].bch.Flags))
		पढ़ो_dma(&card->bc[0], idx, cnt);
	अगर (test_bit(FLG_ACTIVE, &card->bc[1].bch.Flags))
		पढ़ो_dma(&card->bc[1], idx, cnt);
पूर्ण

/* sync with current DMA address at start or after exception */
अटल व्योम
resync(काष्ठा tiger_ch *bc, काष्ठा tiger_hw *card)
अणु
	card->send.dmacur = inl(card->base | NJ_DMA_READ_ADR);
	card->send.idx = (card->send.dmacur - card->send.dmastart) >> 2;
	अगर (bc->मुक्त > card->send.size / 2)
		bc->मुक्त = card->send.size / 2;
	/* currently we simple sync to the next complete मुक्त area
	 * this hast the advantage that we have always maximum समय to
	 * handle TX irq
	 */
	अगर (card->send.idx < ((card->send.size / 2) - 1))
		bc->idx = (card->recv.size / 2) - 1;
	अन्यथा
		bc->idx = card->recv.size - 1;
	bc->txstate = TX_RUN;
	pr_debug("%s: %s B%1d free %d idx %d/%d\n", card->name,
		 __func__, bc->bch.nr, bc->मुक्त, bc->idx, card->send.idx);
पूर्ण

अटल पूर्णांक bc_next_frame(काष्ठा tiger_ch *);

अटल व्योम
fill_hdlc_flag(काष्ठा tiger_ch *bc)
अणु
	काष्ठा tiger_hw *card = bc->bch.hw;
	पूर्णांक count, i;
	u32 m, v;
	u8  *p;

	अगर (bc->मुक्त == 0)
		वापस;
	pr_debug("%s: %s B%1d %d state %x idx %d/%d\n", card->name,
		 __func__, bc->bch.nr, bc->मुक्त, bc->txstate,
		 bc->idx, card->send.idx);
	अगर (bc->txstate & (TX_IDLE | TX_INIT | TX_UNDERRUN))
		resync(bc, card);
	count = isdnhdlc_encode(&bc->hsend, शून्य, 0, &i,
				bc->hsbuf, bc->मुक्त);
	pr_debug("%s: B%1d hdlc encoded %d flags\n", card->name,
		 bc->bch.nr, count);
	bc->मुक्त -= count;
	p = bc->hsbuf;
	m = (bc->bch.nr & 1) ? 0xffffff00 : 0xffff00ff;
	क्रम (i = 0; i < count; i++) अणु
		अगर (bc->idx >= card->send.size)
			bc->idx = 0;
		v = card->send.start[bc->idx];
		v &= m;
		v |= (bc->bch.nr & 1) ? (u32)(p[i]) : ((u32)(p[i])) << 8;
		card->send.start[bc->idx++] = v;
	पूर्ण
	अगर (debug & DEBUG_HW_BFIFO) अणु
		snम_लिखो(card->log, LOG_SIZE, "B%1d-send %s %d ",
			 bc->bch.nr, card->name, count);
		prपूर्णांक_hex_dump_bytes(card->log, DUMP_PREFIX_OFFSET, p, count);
	पूर्ण
पूर्ण

अटल व्योम
fill_dma(काष्ठा tiger_ch *bc)
अणु
	काष्ठा tiger_hw *card = bc->bch.hw;
	पूर्णांक count, i, fillempty = 0;
	u32 m, v, n = 0;
	u8  *p;

	अगर (bc->मुक्त == 0)
		वापस;
	अगर (!bc->bch.tx_skb) अणु
		अगर (!test_bit(FLG_TX_EMPTY, &bc->bch.Flags))
			वापस;
		fillempty = 1;
		count = card->send.size >> 1;
		p = bc->bch.fill;
	पूर्ण अन्यथा अणु
		count = bc->bch.tx_skb->len - bc->bch.tx_idx;
		अगर (count <= 0)
			वापस;
		pr_debug("%s: %s B%1d %d/%d/%d/%d state %x idx %d/%d\n",
			 card->name, __func__, bc->bch.nr, count, bc->मुक्त,
			 bc->bch.tx_idx, bc->bch.tx_skb->len, bc->txstate,
			 bc->idx, card->send.idx);
		p = bc->bch.tx_skb->data + bc->bch.tx_idx;
	पूर्ण
	अगर (bc->txstate & (TX_IDLE | TX_INIT | TX_UNDERRUN))
		resync(bc, card);
	अगर (test_bit(FLG_HDLC, &bc->bch.Flags) && !fillempty) अणु
		count = isdnhdlc_encode(&bc->hsend, p, count, &i,
					bc->hsbuf, bc->मुक्त);
		pr_debug("%s: B%1d hdlc encoded %d in %d\n", card->name,
			 bc->bch.nr, i, count);
		bc->bch.tx_idx += i;
		bc->मुक्त -= count;
		p = bc->hsbuf;
	पूर्ण अन्यथा अणु
		अगर (count > bc->मुक्त)
			count = bc->मुक्त;
		अगर (!fillempty)
			bc->bch.tx_idx += count;
		bc->मुक्त -= count;
	पूर्ण
	m = (bc->bch.nr & 1) ? 0xffffff00 : 0xffff00ff;
	अगर (fillempty) अणु
		n = p[0];
		अगर (!(bc->bch.nr & 1))
			n <<= 8;
		क्रम (i = 0; i < count; i++) अणु
			अगर (bc->idx >= card->send.size)
				bc->idx = 0;
			v = card->send.start[bc->idx];
			v &= m;
			v |= n;
			card->send.start[bc->idx++] = v;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < count; i++) अणु
			अगर (bc->idx >= card->send.size)
				bc->idx = 0;
			v = card->send.start[bc->idx];
			v &= m;
			n = p[i];
			v |= (bc->bch.nr & 1) ? n : n << 8;
			card->send.start[bc->idx++] = v;
		पूर्ण
	पूर्ण
	अगर (debug & DEBUG_HW_BFIFO) अणु
		snम_लिखो(card->log, LOG_SIZE, "B%1d-send %s %d ",
			 bc->bch.nr, card->name, count);
		prपूर्णांक_hex_dump_bytes(card->log, DUMP_PREFIX_OFFSET, p, count);
	पूर्ण
	अगर (bc->मुक्त)
		bc_next_frame(bc);
पूर्ण


अटल पूर्णांक
bc_next_frame(काष्ठा tiger_ch *bc)
अणु
	पूर्णांक ret = 1;

	अगर (bc->bch.tx_skb && bc->bch.tx_idx < bc->bch.tx_skb->len) अणु
		fill_dma(bc);
	पूर्ण अन्यथा अणु
		dev_kमुक्त_skb(bc->bch.tx_skb);
		अगर (get_next_bframe(&bc->bch)) अणु
			fill_dma(bc);
			test_and_clear_bit(FLG_TX_EMPTY, &bc->bch.Flags);
		पूर्ण अन्यथा अगर (test_bit(FLG_TX_EMPTY, &bc->bch.Flags)) अणु
			fill_dma(bc);
		पूर्ण अन्यथा अगर (test_bit(FLG_FILLEMPTY, &bc->bch.Flags)) अणु
			test_and_set_bit(FLG_TX_EMPTY, &bc->bch.Flags);
			ret = 0;
		पूर्ण अन्यथा अणु
			ret = 0;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम
send_tiger_bc(काष्ठा tiger_hw *card, काष्ठा tiger_ch *bc)
अणु
	पूर्णांक ret;

	bc->मुक्त += card->send.size / 2;
	अगर (bc->मुक्त >= card->send.size) अणु
		अगर (!(bc->txstate & (TX_UNDERRUN | TX_INIT))) अणु
			pr_info("%s: B%1d TX underrun state %x\n", card->name,
				bc->bch.nr, bc->txstate);
			bc->txstate |= TX_UNDERRUN;
		पूर्ण
		bc->मुक्त = card->send.size;
	पूर्ण
	ret = bc_next_frame(bc);
	अगर (!ret) अणु
		अगर (test_bit(FLG_HDLC, &bc->bch.Flags)) अणु
			fill_hdlc_flag(bc);
			वापस;
		पूर्ण
		pr_debug("%s: B%1d TX no data free %d idx %d/%d\n", card->name,
			 bc->bch.nr, bc->मुक्त, bc->idx, card->send.idx);
		अगर (!(bc->txstate & (TX_IDLE | TX_INIT))) अणु
			fill_mem(bc, bc->idx, bc->मुक्त, 0xff);
			अगर (bc->मुक्त == card->send.size)
				bc->txstate |= TX_IDLE;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
send_tiger(काष्ठा tiger_hw *card, u8 irq_stat)
अणु
	पूर्णांक i;

	/* Note send is via the READ DMA channel */
	अगर ((irq_stat & card->last_is0) & NJ_IRQM0_RD_MASK) अणु
		pr_info("%s: tiger warn write double dma %x/%x\n",
			card->name, irq_stat, card->last_is0);
		वापस;
	पूर्ण अन्यथा अणु
		card->last_is0 &= ~NJ_IRQM0_RD_MASK;
		card->last_is0 |= (irq_stat & NJ_IRQM0_RD_MASK);
	पूर्ण
	क्रम (i = 0; i < 2; i++) अणु
		अगर (test_bit(FLG_ACTIVE, &card->bc[i].bch.Flags))
			send_tiger_bc(card, &card->bc[i]);
	पूर्ण
पूर्ण

अटल irqवापस_t
nj_irq(पूर्णांक पूर्णांकno, व्योम *dev_id)
अणु
	काष्ठा tiger_hw *card = dev_id;
	u8 val, s1val, s0val;

	spin_lock(&card->lock);
	s0val = inb(card->base | NJ_IRQSTAT0);
	s1val = inb(card->base | NJ_IRQSTAT1);
	अगर ((s1val & NJ_ISACIRQ) && (s0val == 0)) अणु
		/* shared IRQ */
		spin_unlock(&card->lock);
		वापस IRQ_NONE;
	पूर्ण
	pr_debug("%s: IRQSTAT0 %02x IRQSTAT1 %02x\n", card->name, s0val, s1val);
	card->irqcnt++;
	अगर (!(s1val & NJ_ISACIRQ)) अणु
		val = ReadISAC_nj(card, ISAC_ISTA);
		अगर (val)
			mISDNisac_irq(&card->isac, val);
	पूर्ण

	अगर (s0val)
		/* ग_लिखो to clear */
		outb(s0val, card->base | NJ_IRQSTAT0);
	अन्यथा
		जाओ end;
	s1val = s0val;
	/* set bits in sval to indicate which page is मुक्त */
	card->recv.dmacur = inl(card->base | NJ_DMA_WRITE_ADR);
	card->recv.idx = (card->recv.dmacur - card->recv.dmastart) >> 2;
	अगर (card->recv.dmacur < card->recv.dmairq)
		s0val = 0x08;	/* the 2nd ग_लिखो area is मुक्त */
	अन्यथा
		s0val = 0x04;	/* the 1st ग_लिखो area is मुक्त */

	card->send.dmacur = inl(card->base | NJ_DMA_READ_ADR);
	card->send.idx = (card->send.dmacur - card->send.dmastart) >> 2;
	अगर (card->send.dmacur < card->send.dmairq)
		s0val |= 0x02;	/* the 2nd पढ़ो area is मुक्त */
	अन्यथा
		s0val |= 0x01;	/* the 1st पढ़ो area is मुक्त */

	pr_debug("%s: DMA Status %02x/%02x/%02x %d/%d\n", card->name,
		 s1val, s0val, card->last_is0,
		 card->recv.idx, card->send.idx);
	/* test अगर we have a DMA पूर्णांकerrupt */
	अगर (s0val != card->last_is0) अणु
		अगर ((s0val & NJ_IRQM0_RD_MASK) !=
		    (card->last_is0 & NJ_IRQM0_RD_MASK))
			/* got a ग_लिखो dma पूर्णांक */
			send_tiger(card, s0val);
		अगर ((s0val & NJ_IRQM0_WR_MASK) !=
		    (card->last_is0 & NJ_IRQM0_WR_MASK))
			/* got a पढ़ो dma पूर्णांक */
			recv_tiger(card, s0val);
	पूर्ण
end:
	spin_unlock(&card->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक
nj_l2l1B(काष्ठा mISDNchannel *ch, काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret = -EINVAL;
	काष्ठा bchannel *bch = container_of(ch, काष्ठा bchannel, ch);
	काष्ठा tiger_ch *bc = container_of(bch, काष्ठा tiger_ch, bch);
	काष्ठा tiger_hw *card = bch->hw;
	काष्ठा mISDNhead *hh = mISDN_HEAD_P(skb);
	अचिन्हित दीर्घ flags;

	चयन (hh->prim) अणु
	हाल PH_DATA_REQ:
		spin_lock_irqsave(&card->lock, flags);
		ret = bchannel_senddata(bch, skb);
		अगर (ret > 0) अणु /* direct TX */
			fill_dma(bc);
			ret = 0;
		पूर्ण
		spin_unlock_irqrestore(&card->lock, flags);
		वापस ret;
	हाल PH_ACTIVATE_REQ:
		spin_lock_irqsave(&card->lock, flags);
		अगर (!test_and_set_bit(FLG_ACTIVE, &bch->Flags))
			ret = mode_tiger(bc, ch->protocol);
		अन्यथा
			ret = 0;
		spin_unlock_irqrestore(&card->lock, flags);
		अगर (!ret)
			_queue_data(ch, PH_ACTIVATE_IND, MISDN_ID_ANY, 0,
				    शून्य, GFP_KERNEL);
		अवरोध;
	हाल PH_DEACTIVATE_REQ:
		spin_lock_irqsave(&card->lock, flags);
		mISDN_clear_bchannel(bch);
		mode_tiger(bc, ISDN_P_NONE);
		spin_unlock_irqrestore(&card->lock, flags);
		_queue_data(ch, PH_DEACTIVATE_IND, MISDN_ID_ANY, 0,
			    शून्य, GFP_KERNEL);
		ret = 0;
		अवरोध;
	पूर्ण
	अगर (!ret)
		dev_kमुक्त_skb(skb);
	वापस ret;
पूर्ण

अटल पूर्णांक
channel_bctrl(काष्ठा tiger_ch *bc, काष्ठा mISDN_ctrl_req *cq)
अणु
	वापस mISDN_ctrl_bchannel(&bc->bch, cq);
पूर्ण

अटल पूर्णांक
nj_bctrl(काष्ठा mISDNchannel *ch, u32 cmd, व्योम *arg)
अणु
	काष्ठा bchannel *bch = container_of(ch, काष्ठा bchannel, ch);
	काष्ठा tiger_ch *bc = container_of(bch, काष्ठा tiger_ch, bch);
	काष्ठा tiger_hw *card  = bch->hw;
	पूर्णांक ret = -EINVAL;
	u_दीर्घ flags;

	pr_debug("%s: %s cmd:%x %p\n", card->name, __func__, cmd, arg);
	चयन (cmd) अणु
	हाल CLOSE_CHANNEL:
		test_and_clear_bit(FLG_OPEN, &bch->Flags);
		cancel_work_sync(&bch->workq);
		spin_lock_irqsave(&card->lock, flags);
		mISDN_clear_bchannel(bch);
		mode_tiger(bc, ISDN_P_NONE);
		spin_unlock_irqrestore(&card->lock, flags);
		ch->protocol = ISDN_P_NONE;
		ch->peer = शून्य;
		module_put(THIS_MODULE);
		ret = 0;
		अवरोध;
	हाल CONTROL_CHANNEL:
		ret = channel_bctrl(bc, arg);
		अवरोध;
	शेष:
		pr_info("%s: %s unknown prim(%x)\n", card->name, __func__, cmd);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
channel_ctrl(काष्ठा tiger_hw *card, काष्ठा mISDN_ctrl_req *cq)
अणु
	पूर्णांक	ret = 0;

	चयन (cq->op) अणु
	हाल MISDN_CTRL_GETOP:
		cq->op = MISDN_CTRL_LOOP | MISDN_CTRL_L1_TIMER3;
		अवरोध;
	हाल MISDN_CTRL_LOOP:
		/* cq->channel: 0 disable, 1 B1 loop 2 B2 loop, 3 both */
		अगर (cq->channel < 0 || cq->channel > 3) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		ret = card->isac.ctrl(&card->isac, HW_TESTLOOP, cq->channel);
		अवरोध;
	हाल MISDN_CTRL_L1_TIMER3:
		ret = card->isac.ctrl(&card->isac, HW_TIMER3_VALUE, cq->p1);
		अवरोध;
	शेष:
		pr_info("%s: %s unknown Op %x\n", card->name, __func__, cq->op);
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
खोलो_bchannel(काष्ठा tiger_hw *card, काष्ठा channel_req *rq)
अणु
	काष्ठा bchannel *bch;

	अगर (rq->adr.channel == 0 || rq->adr.channel > 2)
		वापस -EINVAL;
	अगर (rq->protocol == ISDN_P_NONE)
		वापस -EINVAL;
	bch = &card->bc[rq->adr.channel - 1].bch;
	अगर (test_and_set_bit(FLG_OPEN, &bch->Flags))
		वापस -EBUSY; /* b-channel can be only खोलो once */
	test_and_clear_bit(FLG_FILLEMPTY, &bch->Flags);
	bch->ch.protocol = rq->protocol;
	rq->ch = &bch->ch;
	वापस 0;
पूर्ण

/*
 * device control function
 */
अटल पूर्णांक
nj_dctrl(काष्ठा mISDNchannel *ch, u32 cmd, व्योम *arg)
अणु
	काष्ठा mISDNdevice	*dev = container_of(ch, काष्ठा mISDNdevice, D);
	काष्ठा dchannel		*dch = container_of(dev, काष्ठा dchannel, dev);
	काष्ठा tiger_hw	*card = dch->hw;
	काष्ठा channel_req	*rq;
	पूर्णांक			err = 0;

	pr_debug("%s: %s cmd:%x %p\n", card->name, __func__, cmd, arg);
	चयन (cmd) अणु
	हाल OPEN_CHANNEL:
		rq = arg;
		अगर (rq->protocol == ISDN_P_TE_S0)
			err = card->isac.खोलो(&card->isac, rq);
		अन्यथा
			err = खोलो_bchannel(card, rq);
		अगर (err)
			अवरोध;
		अगर (!try_module_get(THIS_MODULE))
			pr_info("%s: cannot get module\n", card->name);
		अवरोध;
	हाल CLOSE_CHANNEL:
		pr_debug("%s: dev(%d) close from %p\n", card->name, dch->dev.id,
			 __builtin_वापस_address(0));
		module_put(THIS_MODULE);
		अवरोध;
	हाल CONTROL_CHANNEL:
		err = channel_ctrl(card, arg);
		अवरोध;
	शेष:
		pr_debug("%s: %s unknown command %x\n",
			 card->name, __func__, cmd);
		वापस -EINVAL;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक
nj_init_card(काष्ठा tiger_hw *card)
अणु
	u_दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&card->lock, flags);
	nj_disable_hwirq(card);
	spin_unlock_irqrestore(&card->lock, flags);

	card->irq = card->pdev->irq;
	अगर (request_irq(card->irq, nj_irq, IRQF_SHARED, card->name, card)) अणु
		pr_info("%s: couldn't get interrupt %d\n",
			card->name, card->irq);
		card->irq = -1;
		वापस -EIO;
	पूर्ण

	spin_lock_irqsave(&card->lock, flags);
	nj_reset(card);
	ret = card->isac.init(&card->isac);
	अगर (ret)
		जाओ error;
	ret = inittiger(card);
	अगर (ret)
		जाओ error;
	mode_tiger(&card->bc[0], ISDN_P_NONE);
	mode_tiger(&card->bc[1], ISDN_P_NONE);
error:
	spin_unlock_irqrestore(&card->lock, flags);
	वापस ret;
पूर्ण


अटल व्योम
nj_release(काष्ठा tiger_hw *card)
अणु
	u_दीर्घ flags;
	पूर्णांक i;

	अगर (card->base_s) अणु
		spin_lock_irqsave(&card->lock, flags);
		nj_disable_hwirq(card);
		mode_tiger(&card->bc[0], ISDN_P_NONE);
		mode_tiger(&card->bc[1], ISDN_P_NONE);
		card->isac.release(&card->isac);
		spin_unlock_irqrestore(&card->lock, flags);
		release_region(card->base, card->base_s);
		card->base_s = 0;
	पूर्ण
	अगर (card->irq > 0)
		मुक्त_irq(card->irq, card);
	अगर (card->isac.dch.dev.dev.class)
		mISDN_unरेजिस्टर_device(&card->isac.dch.dev);

	क्रम (i = 0; i < 2; i++) अणु
		mISDN_मुक्तbchannel(&card->bc[i].bch);
		kमुक्त(card->bc[i].hsbuf);
		kमुक्त(card->bc[i].hrbuf);
	पूर्ण
	अगर (card->dma_p)
		dma_मुक्त_coherent(&card->pdev->dev, NJ_DMA_SIZE, card->dma_p,
				  card->dma);
	ग_लिखो_lock_irqsave(&card_lock, flags);
	list_del(&card->list);
	ग_लिखो_unlock_irqrestore(&card_lock, flags);
	pci_clear_master(card->pdev);
	pci_disable_device(card->pdev);
	pci_set_drvdata(card->pdev, शून्य);
	kमुक्त(card);
पूर्ण


अटल पूर्णांक
nj_setup(काष्ठा tiger_hw *card)
अणु
	card->base = pci_resource_start(card->pdev, 0);
	card->base_s = pci_resource_len(card->pdev, 0);
	अगर (!request_region(card->base, card->base_s, card->name)) अणु
		pr_info("%s: NETjet config port %#x-%#x already in use\n",
			card->name, card->base,
			(u32)(card->base + card->base_s - 1));
		card->base_s = 0;
		वापस -EIO;
	पूर्ण
	ASSIGN_FUNC(nj, ISAC, card->isac);
	वापस 0;
पूर्ण


अटल पूर्णांक
setup_instance(काष्ठा tiger_hw *card)
अणु
	पूर्णांक i, err;
	u_दीर्घ flags;

	snम_लिखो(card->name, MISDN_MAX_IDLEN - 1, "netjet.%d", nj_cnt + 1);
	ग_लिखो_lock_irqsave(&card_lock, flags);
	list_add_tail(&card->list, &Cards);
	ग_लिखो_unlock_irqrestore(&card_lock, flags);

	_set_debug(card);
	card->isac.name = card->name;
	spin_lock_init(&card->lock);
	card->isac.hwlock = &card->lock;
	mISDNisac_init(&card->isac, card);

	card->isac.dch.dev.Bprotocols = (1 << (ISDN_P_B_RAW & ISDN_P_B_MASK)) |
		(1 << (ISDN_P_B_HDLC & ISDN_P_B_MASK));
	card->isac.dch.dev.D.ctrl = nj_dctrl;
	क्रम (i = 0; i < 2; i++) अणु
		card->bc[i].bch.nr = i + 1;
		set_channelmap(i + 1, card->isac.dch.dev.channelmap);
		mISDN_initbchannel(&card->bc[i].bch, MAX_DATA_MEM,
				   NJ_DMA_RXSIZE >> 1);
		card->bc[i].bch.hw = card;
		card->bc[i].bch.ch.send = nj_l2l1B;
		card->bc[i].bch.ch.ctrl = nj_bctrl;
		card->bc[i].bch.ch.nr = i + 1;
		list_add(&card->bc[i].bch.ch.list,
			 &card->isac.dch.dev.bchannels);
		card->bc[i].bch.hw = card;
	पूर्ण
	err = nj_setup(card);
	अगर (err)
		जाओ error;
	err = mISDN_रेजिस्टर_device(&card->isac.dch.dev, &card->pdev->dev,
				    card->name);
	अगर (err)
		जाओ error;
	err = nj_init_card(card);
	अगर (!err)  अणु
		nj_cnt++;
		pr_notice("Netjet %d cards installed\n", nj_cnt);
		वापस 0;
	पूर्ण
error:
	nj_release(card);
	वापस err;
पूर्ण

अटल पूर्णांक
nj_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक err = -ENOMEM;
	पूर्णांक cfg;
	काष्ठा tiger_hw *card;

	अगर (pdev->subप्रणाली_venकरोr == 0x8086 &&
	    pdev->subप्रणाली_device == 0x0003) अणु
		pr_notice("Netjet: Digium X100P/X101P not handled\n");
		वापस -ENODEV;
	पूर्ण

	अगर (pdev->subप्रणाली_venकरोr == 0x55 &&
	    pdev->subप्रणाली_device == 0x02) अणु
		pr_notice("Netjet: Enter!Now not handled yet\n");
		वापस -ENODEV;
	पूर्ण

	अगर (pdev->subप्रणाली_venकरोr == 0xb100 &&
	    pdev->subप्रणाली_device == 0x0003) अणु
		pr_notice("Netjet: Digium TDM400P not handled yet\n");
		वापस -ENODEV;
	पूर्ण

	card = kzalloc(माप(काष्ठा tiger_hw), GFP_KERNEL);
	अगर (!card) अणु
		pr_info("No kmem for Netjet\n");
		वापस err;
	पूर्ण

	card->pdev = pdev;

	err = pci_enable_device(pdev);
	अगर (err) अणु
		kमुक्त(card);
		वापस err;
	पूर्ण

	prपूर्णांकk(KERN_INFO "nj_probe(mISDN): found adapter at %s\n",
	       pci_name(pdev));

	pci_set_master(pdev);

	/* the TJ300 and TJ320 must be detected, the IRQ handling is dअगरferent
	 * unक्रमtunately the chips use the same device ID, but the TJ320 has
	 * the bit20 in status PCI cfg रेजिस्टर set
	 */
	pci_पढ़ो_config_dword(pdev, 0x04, &cfg);
	अगर (cfg & 0x00100000)
		card->typ = NETJET_S_TJ320;
	अन्यथा
		card->typ = NETJET_S_TJ300;

	card->base = pci_resource_start(pdev, 0);
	pci_set_drvdata(pdev, card);
	err = setup_instance(card);
	अगर (err)
		pci_set_drvdata(pdev, शून्य);

	वापस err;
पूर्ण


अटल व्योम nj_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा tiger_hw *card = pci_get_drvdata(pdev);

	अगर (card)
		nj_release(card);
	अन्यथा
		pr_info("%s drvdata already removed\n", __func__);
पूर्ण

/* We cannot select cards with PCI_SUB... IDs, since here are cards with
 * SUB IDs set to PCI_ANY_ID, so we need to match all and reject
 * known other cards which not work with this driver - see probe function */
अटल स्थिर काष्ठा pci_device_id nj_pci_ids[] = अणु
	अणु PCI_VENDOR_ID_TIGERJET, PCI_DEVICE_ID_TIGERJET_300,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, nj_pci_ids);

अटल काष्ठा pci_driver nj_driver = अणु
	.name = "netjet",
	.probe = nj_probe,
	.हटाओ = nj_हटाओ,
	.id_table = nj_pci_ids,
पूर्ण;

अटल पूर्णांक __init nj_init(व्योम)
अणु
	पूर्णांक err;

	pr_notice("Netjet PCI driver Rev. %s\n", NETJET_REV);
	err = pci_रेजिस्टर_driver(&nj_driver);
	वापस err;
पूर्ण

अटल व्योम __निकास nj_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&nj_driver);
पूर्ण

module_init(nj_init);
module_निकास(nj_cleanup);
