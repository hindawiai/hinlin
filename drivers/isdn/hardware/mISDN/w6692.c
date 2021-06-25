<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * w6692.c     mISDN driver क्रम Winbond w6692 based cards
 *
 * Author      Karsten Keil <kkeil@suse.de>
 *             based on the w6692 I4L driver from Petr Novak <petr.novak@i.cz>
 *
 * Copyright 2009  by Karsten Keil <keil@isdn4linux.de>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/mISDNhw.h>
#समावेश <linux/slab.h>
#समावेश "w6692.h"

#घोषणा W6692_REV	"2.0"

#घोषणा DBUSY_TIMER_VALUE	80

क्रमागत अणु
	W6692_ASUS,
	W6692_WINBOND,
	W6692_USR
पूर्ण;

/* निजी data in the PCI devices list */
काष्ठा w6692map अणु
	u_पूर्णांक	subtype;
	अक्षर	*name;
पूर्ण;

अटल स्थिर काष्ठा w6692map  w6692_map[] =
अणु
	अणुW6692_ASUS, "Dynalink/AsusCom IS64PH"पूर्ण,
	अणुW6692_WINBOND, "Winbond W6692"पूर्ण,
	अणुW6692_USR, "USR W6692"पूर्ण
पूर्ण;

#घोषणा PCI_DEVICE_ID_USR_6692	0x3409

काष्ठा w6692_ch अणु
	काष्ठा bchannel		bch;
	u32			addr;
	काष्ठा समयr_list	समयr;
	u8			b_mode;
पूर्ण;

काष्ठा w6692_hw अणु
	काष्ठा list_head	list;
	काष्ठा pci_dev		*pdev;
	अक्षर			name[MISDN_MAX_IDLEN];
	u32			irq;
	u32			irqcnt;
	u32			addr;
	u32			fmask;	/* feature mask - bit set per card nr */
	पूर्णांक			subtype;
	spinlock_t		lock;	/* hw lock */
	u8			imask;
	u8			pctl;
	u8			xaddr;
	u8			xdata;
	u8			state;
	काष्ठा w6692_ch		bc[2];
	काष्ठा dchannel		dch;
	अक्षर			log[64];
पूर्ण;

अटल LIST_HEAD(Cards);
अटल DEFINE_RWLOCK(card_lock); /* protect Cards */

अटल पूर्णांक w6692_cnt;
अटल पूर्णांक debug;
अटल u32 led;
अटल u32 pots;

अटल व्योम
_set_debug(काष्ठा w6692_hw *card)
अणु
	card->dch.debug = debug;
	card->bc[0].bch.debug = debug;
	card->bc[1].bch.debug = debug;
पूर्ण

अटल पूर्णांक
set_debug(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक ret;
	काष्ठा w6692_hw *card;

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
MODULE_VERSION(W6692_REV);
module_param_call(debug, set_debug, param_get_uपूर्णांक, &debug, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(debug, "W6692 debug mask");
module_param(led, uपूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(led, "W6692 LED support bitmask (one bit per card)");
module_param(pots, uपूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(pots, "W6692 POTS support bitmask (one bit per card)");

अटल अंतरभूत u8
ReadW6692(काष्ठा w6692_hw *card, u8 offset)
अणु
	वापस inb(card->addr + offset);
पूर्ण

अटल अंतरभूत व्योम
WriteW6692(काष्ठा w6692_hw *card, u8 offset, u8 value)
अणु
	outb(value, card->addr + offset);
पूर्ण

अटल अंतरभूत u8
ReadW6692B(काष्ठा w6692_ch *bc, u8 offset)
अणु
	वापस inb(bc->addr + offset);
पूर्ण

अटल अंतरभूत व्योम
WriteW6692B(काष्ठा w6692_ch *bc, u8 offset, u8 value)
अणु
	outb(value, bc->addr + offset);
पूर्ण

अटल व्योम
enable_hwirq(काष्ठा w6692_hw *card)
अणु
	WriteW6692(card, W_IMASK, card->imask);
पूर्ण

अटल व्योम
disable_hwirq(काष्ठा w6692_hw *card)
अणु
	WriteW6692(card, W_IMASK, 0xff);
पूर्ण

अटल स्थिर अक्षर *W6692Ver[] = अणु"V00", "V01", "V10", "V11"पूर्ण;

अटल व्योम
W6692Version(काष्ठा w6692_hw *card)
अणु
	पूर्णांक val;

	val = ReadW6692(card, W_D_RBCH);
	pr_notice("%s: Winbond W6692 version: %s\n", card->name,
		  W6692Ver[(val >> 6) & 3]);
पूर्ण

अटल व्योम
w6692_led_handler(काष्ठा w6692_hw *card, पूर्णांक on)
अणु
	अगर ((!(card->fmask & led)) || card->subtype == W6692_USR)
		वापस;
	अगर (on) अणु
		card->xdata &= 0xfb;	/*  LED ON */
		WriteW6692(card, W_XDATA, card->xdata);
	पूर्ण अन्यथा अणु
		card->xdata |= 0x04;	/*  LED OFF */
		WriteW6692(card, W_XDATA, card->xdata);
	पूर्ण
पूर्ण

अटल व्योम
ph_command(काष्ठा w6692_hw *card, u8 cmd)
अणु
	pr_debug("%s: ph_command %x\n", card->name, cmd);
	WriteW6692(card, W_CIX, cmd);
पूर्ण

अटल व्योम
W6692_new_ph(काष्ठा w6692_hw *card)
अणु
	अगर (card->state == W_L1CMD_RST)
		ph_command(card, W_L1CMD_DRC);
	schedule_event(&card->dch, FLG_PHCHANGE);
पूर्ण

अटल व्योम
W6692_ph_bh(काष्ठा dchannel *dch)
अणु
	काष्ठा w6692_hw *card = dch->hw;

	चयन (card->state) अणु
	हाल W_L1CMD_RST:
		dch->state = 0;
		l1_event(dch->l1, HW_RESET_IND);
		अवरोध;
	हाल W_L1IND_CD:
		dch->state = 3;
		l1_event(dch->l1, HW_DEACT_CNF);
		अवरोध;
	हाल W_L1IND_DRD:
		dch->state = 3;
		l1_event(dch->l1, HW_DEACT_IND);
		अवरोध;
	हाल W_L1IND_CE:
		dch->state = 4;
		l1_event(dch->l1, HW_POWERUP_IND);
		अवरोध;
	हाल W_L1IND_LD:
		अगर (dch->state <= 5) अणु
			dch->state = 5;
			l1_event(dch->l1, ANYSIGNAL);
		पूर्ण अन्यथा अणु
			dch->state = 8;
			l1_event(dch->l1, LOSTFRAMING);
		पूर्ण
		अवरोध;
	हाल W_L1IND_ARD:
		dch->state = 6;
		l1_event(dch->l1, INFO2);
		अवरोध;
	हाल W_L1IND_AI8:
		dch->state = 7;
		l1_event(dch->l1, INFO4_P8);
		अवरोध;
	हाल W_L1IND_AI10:
		dch->state = 7;
		l1_event(dch->l1, INFO4_P10);
		अवरोध;
	शेष:
		pr_debug("%s: TE unknown state %02x dch state %02x\n",
			 card->name, card->state, dch->state);
		अवरोध;
	पूर्ण
	pr_debug("%s: TE newstate %02x\n", card->name, dch->state);
पूर्ण

अटल व्योम
W6692_empty_Dfअगरo(काष्ठा w6692_hw *card, पूर्णांक count)
अणु
	काष्ठा dchannel *dch = &card->dch;
	u8 *ptr;

	pr_debug("%s: empty_Dfifo %d\n", card->name, count);
	अगर (!dch->rx_skb) अणु
		dch->rx_skb = mI_alloc_skb(card->dch.maxlen, GFP_ATOMIC);
		अगर (!dch->rx_skb) अणु
			pr_info("%s: D receive out of memory\n", card->name);
			WriteW6692(card, W_D_CMDR, W_D_CMDR_RACK);
			वापस;
		पूर्ण
	पूर्ण
	अगर ((dch->rx_skb->len + count) >= dch->maxlen) अणु
		pr_debug("%s: empty_Dfifo overrun %d\n", card->name,
			 dch->rx_skb->len + count);
		WriteW6692(card, W_D_CMDR, W_D_CMDR_RACK);
		वापस;
	पूर्ण
	ptr = skb_put(dch->rx_skb, count);
	insb(card->addr + W_D_RFIFO, ptr, count);
	WriteW6692(card, W_D_CMDR, W_D_CMDR_RACK);
	अगर (debug & DEBUG_HW_DFIFO) अणु
		snम_लिखो(card->log, 63, "D-recv %s %d ",
			 card->name, count);
		prपूर्णांक_hex_dump_bytes(card->log, DUMP_PREFIX_OFFSET, ptr, count);
	पूर्ण
पूर्ण

अटल व्योम
W6692_fill_Dfअगरo(काष्ठा w6692_hw *card)
अणु
	काष्ठा dchannel *dch = &card->dch;
	पूर्णांक count;
	u8 *ptr;
	u8 cmd = W_D_CMDR_XMS;

	pr_debug("%s: fill_Dfifo\n", card->name);
	अगर (!dch->tx_skb)
		वापस;
	count = dch->tx_skb->len - dch->tx_idx;
	अगर (count <= 0)
		वापस;
	अगर (count > W_D_FIFO_THRESH)
		count = W_D_FIFO_THRESH;
	अन्यथा
		cmd |= W_D_CMDR_XME;
	ptr = dch->tx_skb->data + dch->tx_idx;
	dch->tx_idx += count;
	outsb(card->addr + W_D_XFIFO, ptr, count);
	WriteW6692(card, W_D_CMDR, cmd);
	अगर (test_and_set_bit(FLG_BUSY_TIMER, &dch->Flags)) अणु
		pr_debug("%s: fill_Dfifo dbusytimer running\n", card->name);
		del_समयr(&dch->समयr);
	पूर्ण
	dch->समयr.expires = jअगरfies + ((DBUSY_TIMER_VALUE * HZ) / 1000);
	add_समयr(&dch->समयr);
	अगर (debug & DEBUG_HW_DFIFO) अणु
		snम_लिखो(card->log, 63, "D-send %s %d ",
			 card->name, count);
		prपूर्णांक_hex_dump_bytes(card->log, DUMP_PREFIX_OFFSET, ptr, count);
	पूर्ण
पूर्ण

अटल व्योम
d_retransmit(काष्ठा w6692_hw *card)
अणु
	काष्ठा dchannel *dch = &card->dch;

	अगर (test_and_clear_bit(FLG_BUSY_TIMER, &dch->Flags))
		del_समयr(&dch->समयr);
#अगर_घोषित FIXME
	अगर (test_and_clear_bit(FLG_L1_BUSY, &dch->Flags))
		dchannel_sched_event(dch, D_CLEARBUSY);
#पूर्ण_अगर
	अगर (test_bit(FLG_TX_BUSY, &dch->Flags)) अणु
		/* Restart frame */
		dch->tx_idx = 0;
		W6692_fill_Dfअगरo(card);
	पूर्ण अन्यथा अगर (dch->tx_skb) अणु /* should not happen */
		pr_info("%s: %s without TX_BUSY\n", card->name, __func__);
		test_and_set_bit(FLG_TX_BUSY, &dch->Flags);
		dch->tx_idx = 0;
		W6692_fill_Dfअगरo(card);
	पूर्ण अन्यथा अणु
		pr_info("%s: XDU no TX_BUSY\n", card->name);
		अगर (get_next_dframe(dch))
			W6692_fill_Dfअगरo(card);
	पूर्ण
पूर्ण

अटल व्योम
handle_rxD(काष्ठा w6692_hw *card) अणु
	u8	stat;
	पूर्णांक	count;

	stat = ReadW6692(card, W_D_RSTA);
	अगर (stat & (W_D_RSTA_RDOV | W_D_RSTA_CRCE | W_D_RSTA_RMB)) अणु
		अगर (stat & W_D_RSTA_RDOV) अणु
			pr_debug("%s: D-channel RDOV\n", card->name);
#अगर_घोषित ERROR_STATISTIC
			card->dch.err_rx++;
#पूर्ण_अगर
		पूर्ण
		अगर (stat & W_D_RSTA_CRCE) अणु
			pr_debug("%s: D-channel CRC error\n", card->name);
#अगर_घोषित ERROR_STATISTIC
			card->dch.err_crc++;
#पूर्ण_अगर
		पूर्ण
		अगर (stat & W_D_RSTA_RMB) अणु
			pr_debug("%s: D-channel ABORT\n", card->name);
#अगर_घोषित ERROR_STATISTIC
			card->dch.err_rx++;
#पूर्ण_अगर
		पूर्ण
		dev_kमुक्त_skb(card->dch.rx_skb);
		card->dch.rx_skb = शून्य;
		WriteW6692(card, W_D_CMDR, W_D_CMDR_RACK | W_D_CMDR_RRST);
	पूर्ण अन्यथा अणु
		count = ReadW6692(card, W_D_RBCL) & (W_D_FIFO_THRESH - 1);
		अगर (count == 0)
			count = W_D_FIFO_THRESH;
		W6692_empty_Dfअगरo(card, count);
		recv_Dchannel(&card->dch);
	पूर्ण
पूर्ण

अटल व्योम
handle_txD(काष्ठा w6692_hw *card) अणु
	अगर (test_and_clear_bit(FLG_BUSY_TIMER, &card->dch.Flags))
		del_समयr(&card->dch.समयr);
	अगर (card->dch.tx_skb && card->dch.tx_idx < card->dch.tx_skb->len) अणु
		W6692_fill_Dfअगरo(card);
	पूर्ण अन्यथा अणु
		dev_kमुक्त_skb(card->dch.tx_skb);
		अगर (get_next_dframe(&card->dch))
			W6692_fill_Dfअगरo(card);
	पूर्ण
पूर्ण

अटल व्योम
handle_statusD(काष्ठा w6692_hw *card)
अणु
	काष्ठा dchannel *dch = &card->dch;
	u8 exval, v1, cir;

	exval = ReadW6692(card, W_D_EXIR);

	pr_debug("%s: D_EXIR %02x\n", card->name, exval);
	अगर (exval & (W_D_EXI_XDUN | W_D_EXI_XCOL)) अणु
		/* Transmit underrun/collision */
		pr_debug("%s: D-channel underrun/collision\n", card->name);
#अगर_घोषित ERROR_STATISTIC
		dch->err_tx++;
#पूर्ण_अगर
		d_retransmit(card);
	पूर्ण
	अगर (exval & W_D_EXI_RDOV) अणु	/* RDOV */
		pr_debug("%s: D-channel RDOV\n", card->name);
		WriteW6692(card, W_D_CMDR, W_D_CMDR_RRST);
	पूर्ण
	अगर (exval & W_D_EXI_TIN2)	/* TIN2 - never */
		pr_debug("%s: spurious TIN2 interrupt\n", card->name);
	अगर (exval & W_D_EXI_MOC) अणु	/* MOC - not supported */
		v1 = ReadW6692(card, W_MOSR);
		pr_debug("%s: spurious MOC interrupt MOSR %02x\n",
			 card->name, v1);
	पूर्ण
	अगर (exval & W_D_EXI_ISC) अणु	/* ISC - Level1 change */
		cir = ReadW6692(card, W_CIR);
		pr_debug("%s: ISC CIR %02X\n", card->name, cir);
		अगर (cir & W_CIR_ICC) अणु
			v1 = cir & W_CIR_COD_MASK;
			pr_debug("%s: ph_state_change %x -> %x\n", card->name,
				 dch->state, v1);
			card->state = v1;
			अगर (card->fmask & led) अणु
				चयन (v1) अणु
				हाल W_L1IND_AI8:
				हाल W_L1IND_AI10:
					w6692_led_handler(card, 1);
					अवरोध;
				शेष:
					w6692_led_handler(card, 0);
					अवरोध;
				पूर्ण
			पूर्ण
			W6692_new_ph(card);
		पूर्ण
		अगर (cir & W_CIR_SCC) अणु
			v1 = ReadW6692(card, W_SQR);
			pr_debug("%s: SCC SQR %02X\n", card->name, v1);
		पूर्ण
	पूर्ण
	अगर (exval & W_D_EXI_WEXP)
		pr_debug("%s: spurious WEXP interrupt!\n", card->name);
	अगर (exval & W_D_EXI_TEXP)
		pr_debug("%s: spurious TEXP interrupt!\n", card->name);
पूर्ण

अटल व्योम
W6692_empty_Bfअगरo(काष्ठा w6692_ch *wch, पूर्णांक count)
अणु
	काष्ठा w6692_hw *card = wch->bch.hw;
	u8 *ptr;
	पूर्णांक maxlen;

	pr_debug("%s: empty_Bfifo %d\n", card->name, count);
	अगर (unlikely(wch->bch.state == ISDN_P_NONE)) अणु
		pr_debug("%s: empty_Bfifo ISDN_P_NONE\n", card->name);
		WriteW6692B(wch, W_B_CMDR, W_B_CMDR_RACK | W_B_CMDR_RACT);
		अगर (wch->bch.rx_skb)
			skb_trim(wch->bch.rx_skb, 0);
		वापस;
	पूर्ण
	अगर (test_bit(FLG_RX_OFF, &wch->bch.Flags)) अणु
		wch->bch.dropcnt += count;
		WriteW6692B(wch, W_B_CMDR, W_B_CMDR_RACK | W_B_CMDR_RACT);
		वापस;
	पूर्ण
	maxlen = bchannel_get_rxbuf(&wch->bch, count);
	अगर (maxlen < 0) अणु
		WriteW6692B(wch, W_B_CMDR, W_B_CMDR_RACK | W_B_CMDR_RACT);
		अगर (wch->bch.rx_skb)
			skb_trim(wch->bch.rx_skb, 0);
		pr_warn("%s.B%d: No bufferspace for %d bytes\n",
			card->name, wch->bch.nr, count);
		वापस;
	पूर्ण
	ptr = skb_put(wch->bch.rx_skb, count);
	insb(wch->addr + W_B_RFIFO, ptr, count);
	WriteW6692B(wch, W_B_CMDR, W_B_CMDR_RACK | W_B_CMDR_RACT);
	अगर (debug & DEBUG_HW_DFIFO) अणु
		snम_लिखो(card->log, 63, "B%1d-recv %s %d ",
			 wch->bch.nr, card->name, count);
		prपूर्णांक_hex_dump_bytes(card->log, DUMP_PREFIX_OFFSET, ptr, count);
	पूर्ण
पूर्ण

अटल व्योम
W6692_fill_Bfअगरo(काष्ठा w6692_ch *wch)
अणु
	काष्ठा w6692_hw *card = wch->bch.hw;
	पूर्णांक count, fillempty = 0;
	u8 *ptr, cmd = W_B_CMDR_RACT | W_B_CMDR_XMS;

	pr_debug("%s: fill Bfifo\n", card->name);
	अगर (!wch->bch.tx_skb) अणु
		अगर (!test_bit(FLG_TX_EMPTY, &wch->bch.Flags))
			वापस;
		ptr = wch->bch.fill;
		count = W_B_FIFO_THRESH;
		fillempty = 1;
	पूर्ण अन्यथा अणु
		count = wch->bch.tx_skb->len - wch->bch.tx_idx;
		अगर (count <= 0)
			वापस;
		ptr = wch->bch.tx_skb->data + wch->bch.tx_idx;
	पूर्ण
	अगर (count > W_B_FIFO_THRESH)
		count = W_B_FIFO_THRESH;
	अन्यथा अगर (test_bit(FLG_HDLC, &wch->bch.Flags))
		cmd |= W_B_CMDR_XME;

	pr_debug("%s: fill Bfifo%d/%d\n", card->name,
		 count, wch->bch.tx_idx);
	wch->bch.tx_idx += count;
	अगर (fillempty) अणु
		जबतक (count > 0) अणु
			outsb(wch->addr + W_B_XFIFO, ptr, MISDN_BCH_FILL_SIZE);
			count -= MISDN_BCH_FILL_SIZE;
		पूर्ण
	पूर्ण अन्यथा अणु
		outsb(wch->addr + W_B_XFIFO, ptr, count);
	पूर्ण
	WriteW6692B(wch, W_B_CMDR, cmd);
	अगर ((debug & DEBUG_HW_BFIFO) && !fillempty) अणु
		snम_लिखो(card->log, 63, "B%1d-send %s %d ",
			 wch->bch.nr, card->name, count);
		prपूर्णांक_hex_dump_bytes(card->log, DUMP_PREFIX_OFFSET, ptr, count);
	पूर्ण
पूर्ण

#अगर 0
अटल पूर्णांक
setvolume(काष्ठा w6692_ch *wch, पूर्णांक mic, काष्ठा sk_buff *skb)
अणु
	काष्ठा w6692_hw *card = wch->bch.hw;
	u16 *vol = (u16 *)skb->data;
	u8 val;

	अगर ((!(card->fmask & pots)) ||
	    !test_bit(FLG_TRANSPARENT, &wch->bch.Flags))
		वापस -ENODEV;
	अगर (skb->len < 2)
		वापस -EINVAL;
	अगर (*vol > 7)
		वापस -EINVAL;
	val = *vol & 7;
	val = 7 - val;
	अगर (mic) अणु
		val <<= 3;
		card->xaddr &= 0xc7;
	पूर्ण अन्यथा अणु
		card->xaddr &= 0xf8;
	पूर्ण
	card->xaddr |= val;
	WriteW6692(card, W_XADDR, card->xaddr);
	वापस 0;
पूर्ण

अटल पूर्णांक
enable_pots(काष्ठा w6692_ch *wch)
अणु
	काष्ठा w6692_hw *card = wch->bch.hw;

	अगर ((!(card->fmask & pots)) ||
	    !test_bit(FLG_TRANSPARENT, &wch->bch.Flags))
		वापस -ENODEV;
	wch->b_mode |= W_B_MODE_EPCM | W_B_MODE_BSW0;
	WriteW6692B(wch, W_B_MODE, wch->b_mode);
	WriteW6692B(wch, W_B_CMDR, W_B_CMDR_RRST | W_B_CMDR_XRST);
	card->pctl |= ((wch->bch.nr & 2) ? W_PCTL_PCX : 0);
	WriteW6692(card, W_PCTL, card->pctl);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक
disable_pots(काष्ठा w6692_ch *wch)
अणु
	काष्ठा w6692_hw *card = wch->bch.hw;

	अगर (!(card->fmask & pots))
		वापस -ENODEV;
	wch->b_mode &= ~(W_B_MODE_EPCM | W_B_MODE_BSW0);
	WriteW6692B(wch, W_B_MODE, wch->b_mode);
	WriteW6692B(wch, W_B_CMDR, W_B_CMDR_RRST | W_B_CMDR_RACT |
		    W_B_CMDR_XRST);
	वापस 0;
पूर्ण

अटल पूर्णांक
w6692_mode(काष्ठा w6692_ch *wch, u32 pr)
अणु
	काष्ठा w6692_hw	*card;

	card = wch->bch.hw;
	pr_debug("%s: B%d protocol %x-->%x\n", card->name,
		 wch->bch.nr, wch->bch.state, pr);
	चयन (pr) अणु
	हाल ISDN_P_NONE:
		अगर ((card->fmask & pots) && (wch->b_mode & W_B_MODE_EPCM))
			disable_pots(wch);
		wch->b_mode = 0;
		mISDN_clear_bchannel(&wch->bch);
		WriteW6692B(wch, W_B_MODE, wch->b_mode);
		WriteW6692B(wch, W_B_CMDR, W_B_CMDR_RRST | W_B_CMDR_XRST);
		test_and_clear_bit(FLG_HDLC, &wch->bch.Flags);
		test_and_clear_bit(FLG_TRANSPARENT, &wch->bch.Flags);
		अवरोध;
	हाल ISDN_P_B_RAW:
		wch->b_mode = W_B_MODE_MMS;
		WriteW6692B(wch, W_B_MODE, wch->b_mode);
		WriteW6692B(wch, W_B_EXIM, 0);
		WriteW6692B(wch, W_B_CMDR, W_B_CMDR_RRST | W_B_CMDR_RACT |
			    W_B_CMDR_XRST);
		test_and_set_bit(FLG_TRANSPARENT, &wch->bch.Flags);
		अवरोध;
	हाल ISDN_P_B_HDLC:
		wch->b_mode = W_B_MODE_ITF;
		WriteW6692B(wch, W_B_MODE, wch->b_mode);
		WriteW6692B(wch, W_B_ADM1, 0xff);
		WriteW6692B(wch, W_B_ADM2, 0xff);
		WriteW6692B(wch, W_B_EXIM, 0);
		WriteW6692B(wch, W_B_CMDR, W_B_CMDR_RRST | W_B_CMDR_RACT |
			    W_B_CMDR_XRST);
		test_and_set_bit(FLG_HDLC, &wch->bch.Flags);
		अवरोध;
	शेष:
		pr_info("%s: protocol %x not known\n", card->name, pr);
		वापस -ENOPROTOOPT;
	पूर्ण
	wch->bch.state = pr;
	वापस 0;
पूर्ण

अटल व्योम
send_next(काष्ठा w6692_ch *wch)
अणु
	अगर (wch->bch.tx_skb && wch->bch.tx_idx < wch->bch.tx_skb->len) अणु
		W6692_fill_Bfअगरo(wch);
	पूर्ण अन्यथा अणु
		dev_kमुक्त_skb(wch->bch.tx_skb);
		अगर (get_next_bframe(&wch->bch)) अणु
			W6692_fill_Bfअगरo(wch);
			test_and_clear_bit(FLG_TX_EMPTY, &wch->bch.Flags);
		पूर्ण अन्यथा अगर (test_bit(FLG_TX_EMPTY, &wch->bch.Flags)) अणु
			W6692_fill_Bfअगरo(wch);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
W6692B_पूर्णांकerrupt(काष्ठा w6692_hw *card, पूर्णांक ch)
अणु
	काष्ठा w6692_ch	*wch = &card->bc[ch];
	पूर्णांक		count;
	u8		stat, star = 0;

	stat = ReadW6692B(wch, W_B_EXIR);
	pr_debug("%s: B%d EXIR %02x\n", card->name, wch->bch.nr, stat);
	अगर (stat & W_B_EXI_RME) अणु
		star = ReadW6692B(wch, W_B_STAR);
		अगर (star & (W_B_STAR_RDOV | W_B_STAR_CRCE | W_B_STAR_RMB)) अणु
			अगर ((star & W_B_STAR_RDOV) &&
			    test_bit(FLG_ACTIVE, &wch->bch.Flags)) अणु
				pr_debug("%s: B%d RDOV proto=%x\n", card->name,
					 wch->bch.nr, wch->bch.state);
#अगर_घोषित ERROR_STATISTIC
				wch->bch.err_rकरो++;
#पूर्ण_अगर
			पूर्ण
			अगर (test_bit(FLG_HDLC, &wch->bch.Flags)) अणु
				अगर (star & W_B_STAR_CRCE) अणु
					pr_debug("%s: B%d CRC error\n",
						 card->name, wch->bch.nr);
#अगर_घोषित ERROR_STATISTIC
					wch->bch.err_crc++;
#पूर्ण_अगर
				पूर्ण
				अगर (star & W_B_STAR_RMB) अणु
					pr_debug("%s: B%d message abort\n",
						 card->name, wch->bch.nr);
#अगर_घोषित ERROR_STATISTIC
					wch->bch.err_inv++;
#पूर्ण_अगर
				पूर्ण
			पूर्ण
			WriteW6692B(wch, W_B_CMDR, W_B_CMDR_RACK |
				    W_B_CMDR_RRST | W_B_CMDR_RACT);
			अगर (wch->bch.rx_skb)
				skb_trim(wch->bch.rx_skb, 0);
		पूर्ण अन्यथा अणु
			count = ReadW6692B(wch, W_B_RBCL) &
				(W_B_FIFO_THRESH - 1);
			अगर (count == 0)
				count = W_B_FIFO_THRESH;
			W6692_empty_Bfअगरo(wch, count);
			recv_Bchannel(&wch->bch, 0, false);
		पूर्ण
	पूर्ण
	अगर (stat & W_B_EXI_RMR) अणु
		अगर (!(stat & W_B_EXI_RME))
			star = ReadW6692B(wch, W_B_STAR);
		अगर (star & W_B_STAR_RDOV) अणु
			pr_debug("%s: B%d RDOV proto=%x\n", card->name,
				 wch->bch.nr, wch->bch.state);
#अगर_घोषित ERROR_STATISTIC
			wch->bch.err_rकरो++;
#पूर्ण_अगर
			WriteW6692B(wch, W_B_CMDR, W_B_CMDR_RACK |
				    W_B_CMDR_RRST | W_B_CMDR_RACT);
		पूर्ण अन्यथा अणु
			W6692_empty_Bfअगरo(wch, W_B_FIFO_THRESH);
			अगर (test_bit(FLG_TRANSPARENT, &wch->bch.Flags))
				recv_Bchannel(&wch->bch, 0, false);
		पूर्ण
	पूर्ण
	अगर (stat & W_B_EXI_RDOV) अणु
		/* only अगर it is not handled yet */
		अगर (!(star & W_B_STAR_RDOV)) अणु
			pr_debug("%s: B%d RDOV IRQ proto=%x\n", card->name,
				 wch->bch.nr, wch->bch.state);
#अगर_घोषित ERROR_STATISTIC
			wch->bch.err_rकरो++;
#पूर्ण_अगर
			WriteW6692B(wch, W_B_CMDR, W_B_CMDR_RACK |
				    W_B_CMDR_RRST | W_B_CMDR_RACT);
		पूर्ण
	पूर्ण
	अगर (stat & W_B_EXI_XFR) अणु
		अगर (!(stat & (W_B_EXI_RME | W_B_EXI_RMR))) अणु
			star = ReadW6692B(wch, W_B_STAR);
			pr_debug("%s: B%d star %02x\n", card->name,
				 wch->bch.nr, star);
		पूर्ण
		अगर (star & W_B_STAR_XDOW) अणु
			pr_warn("%s: B%d XDOW proto=%x\n", card->name,
				wch->bch.nr, wch->bch.state);
#अगर_घोषित ERROR_STATISTIC
			wch->bch.err_xdu++;
#पूर्ण_अगर
			WriteW6692B(wch, W_B_CMDR, W_B_CMDR_XRST |
				    W_B_CMDR_RACT);
			/* resend */
			अगर (wch->bch.tx_skb) अणु
				अगर (!test_bit(FLG_TRANSPARENT, &wch->bch.Flags))
					wch->bch.tx_idx = 0;
			पूर्ण
		पूर्ण
		send_next(wch);
		अगर (star & W_B_STAR_XDOW)
			वापस; /* handle XDOW only once */
	पूर्ण
	अगर (stat & W_B_EXI_XDUN) अणु
		pr_warn("%s: B%d XDUN proto=%x\n", card->name,
			wch->bch.nr, wch->bch.state);
#अगर_घोषित ERROR_STATISTIC
		wch->bch.err_xdu++;
#पूर्ण_अगर
		/* resend - no XRST needed */
		अगर (wch->bch.tx_skb) अणु
			अगर (!test_bit(FLG_TRANSPARENT, &wch->bch.Flags))
				wch->bch.tx_idx = 0;
		पूर्ण अन्यथा अगर (test_bit(FLG_FILLEMPTY, &wch->bch.Flags)) अणु
			test_and_set_bit(FLG_TX_EMPTY, &wch->bch.Flags);
		पूर्ण
		send_next(wch);
	पूर्ण
पूर्ण

अटल irqवापस_t
w6692_irq(पूर्णांक पूर्णांकno, व्योम *dev_id)
अणु
	काष्ठा w6692_hw	*card = dev_id;
	u8		ista;

	spin_lock(&card->lock);
	ista = ReadW6692(card, W_ISTA);
	अगर ((ista | card->imask) == card->imask) अणु
		/* possible a shared  IRQ reqest */
		spin_unlock(&card->lock);
		वापस IRQ_NONE;
	पूर्ण
	card->irqcnt++;
	pr_debug("%s: ista %02x\n", card->name, ista);
	ista &= ~card->imask;
	अगर (ista & W_INT_B1_EXI)
		W6692B_पूर्णांकerrupt(card, 0);
	अगर (ista & W_INT_B2_EXI)
		W6692B_पूर्णांकerrupt(card, 1);
	अगर (ista & W_INT_D_RME)
		handle_rxD(card);
	अगर (ista & W_INT_D_RMR)
		W6692_empty_Dfअगरo(card, W_D_FIFO_THRESH);
	अगर (ista & W_INT_D_XFR)
		handle_txD(card);
	अगर (ista & W_INT_D_EXI)
		handle_statusD(card);
	अगर (ista & (W_INT_XINT0 | W_INT_XINT1)) /* XINT0/1 - never */
		pr_debug("%s: W6692 spurious XINT!\n", card->name);
/* End IRQ Handler */
	spin_unlock(&card->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम
dbusy_समयr_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा dchannel *dch = from_समयr(dch, t, समयr);
	काष्ठा w6692_hw	*card = dch->hw;
	पूर्णांक		rbch, star;
	u_दीर्घ		flags;

	अगर (test_bit(FLG_BUSY_TIMER, &dch->Flags)) अणु
		spin_lock_irqsave(&card->lock, flags);
		rbch = ReadW6692(card, W_D_RBCH);
		star = ReadW6692(card, W_D_STAR);
		pr_debug("%s: D-Channel Busy RBCH %02x STAR %02x\n",
			 card->name, rbch, star);
		अगर (star & W_D_STAR_XBZ)	/* D-Channel Busy */
			test_and_set_bit(FLG_L1_BUSY, &dch->Flags);
		अन्यथा अणु
			/* discard frame; reset transceiver */
			test_and_clear_bit(FLG_BUSY_TIMER, &dch->Flags);
			अगर (dch->tx_idx)
				dch->tx_idx = 0;
			अन्यथा
				pr_info("%s: W6692 D-Channel Busy no tx_idx\n",
					card->name);
			/* Transmitter reset */
			WriteW6692(card, W_D_CMDR, W_D_CMDR_XRST);
		पूर्ण
		spin_unlock_irqrestore(&card->lock, flags);
	पूर्ण
पूर्ण

अटल व्योम initW6692(काष्ठा w6692_hw *card)
अणु
	u8	val;

	समयr_setup(&card->dch.समयr, dbusy_समयr_handler, 0);
	w6692_mode(&card->bc[0], ISDN_P_NONE);
	w6692_mode(&card->bc[1], ISDN_P_NONE);
	WriteW6692(card, W_D_CTL, 0x00);
	disable_hwirq(card);
	WriteW6692(card, W_D_SAM, 0xff);
	WriteW6692(card, W_D_TAM, 0xff);
	WriteW6692(card, W_D_MODE, W_D_MODE_RACT);
	card->state = W_L1CMD_RST;
	ph_command(card, W_L1CMD_RST);
	ph_command(card, W_L1CMD_ECK);
	/* enable all IRQ but बाह्य */
	card->imask = 0x18;
	WriteW6692(card, W_D_EXIM, 0x00);
	WriteW6692B(&card->bc[0], W_B_EXIM, 0);
	WriteW6692B(&card->bc[1], W_B_EXIM, 0);
	/* Reset D-chan receiver and transmitter */
	WriteW6692(card, W_D_CMDR, W_D_CMDR_RRST | W_D_CMDR_XRST);
	/* Reset B-chan receiver and transmitter */
	WriteW6692B(&card->bc[0], W_B_CMDR, W_B_CMDR_RRST | W_B_CMDR_XRST);
	WriteW6692B(&card->bc[1], W_B_CMDR, W_B_CMDR_RRST | W_B_CMDR_XRST);
	/* enable peripheral */
	अगर (card->subtype == W6692_USR) अणु
		/* seems that USR implemented some घातer control features
		 * Pin 79 is connected to the oscilator circuit so we
		 * have to handle it here
		 */
		card->pctl = 0x80;
		card->xdata = 0;
		WriteW6692(card, W_PCTL, card->pctl);
		WriteW6692(card, W_XDATA, card->xdata);
	पूर्ण अन्यथा अणु
		card->pctl = W_PCTL_OE5 | W_PCTL_OE4 | W_PCTL_OE2 |
			W_PCTL_OE1 | W_PCTL_OE0;
		card->xaddr = 0x00;/* all sw off */
		अगर (card->fmask & pots)
			card->xdata |= 0x06;	/*  POWER UP/ LED OFF / ALAW */
		अगर (card->fmask & led)
			card->xdata |= 0x04;	/* LED OFF */
		अगर ((card->fmask & pots) || (card->fmask & led)) अणु
			WriteW6692(card, W_PCTL, card->pctl);
			WriteW6692(card, W_XADDR, card->xaddr);
			WriteW6692(card, W_XDATA, card->xdata);
			val = ReadW6692(card, W_XADDR);
			अगर (debug & DEBUG_HW)
				pr_notice("%s: W_XADDR=%02x\n",
					  card->name, val);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
reset_w6692(काष्ठा w6692_hw *card)
अणु
	WriteW6692(card, W_D_CTL, W_D_CTL_SRST);
	mdelay(10);
	WriteW6692(card, W_D_CTL, 0);
पूर्ण

अटल पूर्णांक
init_card(काष्ठा w6692_hw *card)
अणु
	पूर्णांक	cnt = 3;
	u_दीर्घ	flags;

	spin_lock_irqsave(&card->lock, flags);
	disable_hwirq(card);
	spin_unlock_irqrestore(&card->lock, flags);
	अगर (request_irq(card->irq, w6692_irq, IRQF_SHARED, card->name, card)) अणु
		pr_info("%s: couldn't get interrupt %d\n", card->name,
			card->irq);
		वापस -EIO;
	पूर्ण
	जबतक (cnt--) अणु
		spin_lock_irqsave(&card->lock, flags);
		initW6692(card);
		enable_hwirq(card);
		spin_unlock_irqrestore(&card->lock, flags);
		/* Timeout 10ms */
		msleep_पूर्णांकerruptible(10);
		अगर (debug & DEBUG_HW)
			pr_notice("%s: IRQ %d count %d\n", card->name,
				  card->irq, card->irqcnt);
		अगर (!card->irqcnt) अणु
			pr_info("%s: IRQ(%d) getting no IRQs during init %d\n",
				card->name, card->irq, 3 - cnt);
			reset_w6692(card);
		पूर्ण अन्यथा
			वापस 0;
	पूर्ण
	मुक्त_irq(card->irq, card);
	वापस -EIO;
पूर्ण

अटल पूर्णांक
w6692_l2l1B(काष्ठा mISDNchannel *ch, काष्ठा sk_buff *skb)
अणु
	काष्ठा bchannel *bch = container_of(ch, काष्ठा bchannel, ch);
	काष्ठा w6692_ch	*bc = container_of(bch, काष्ठा w6692_ch, bch);
	काष्ठा w6692_hw *card = bch->hw;
	पूर्णांक ret = -EINVAL;
	काष्ठा mISDNhead *hh = mISDN_HEAD_P(skb);
	अचिन्हित दीर्घ flags;

	चयन (hh->prim) अणु
	हाल PH_DATA_REQ:
		spin_lock_irqsave(&card->lock, flags);
		ret = bchannel_senddata(bch, skb);
		अगर (ret > 0) अणु /* direct TX */
			ret = 0;
			W6692_fill_Bfअगरo(bc);
		पूर्ण
		spin_unlock_irqrestore(&card->lock, flags);
		वापस ret;
	हाल PH_ACTIVATE_REQ:
		spin_lock_irqsave(&card->lock, flags);
		अगर (!test_and_set_bit(FLG_ACTIVE, &bch->Flags))
			ret = w6692_mode(bc, ch->protocol);
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
		w6692_mode(bc, ISDN_P_NONE);
		spin_unlock_irqrestore(&card->lock, flags);
		_queue_data(ch, PH_DEACTIVATE_IND, MISDN_ID_ANY, 0,
			    शून्य, GFP_KERNEL);
		ret = 0;
		अवरोध;
	शेष:
		pr_info("%s: %s unknown prim(%x,%x)\n",
			card->name, __func__, hh->prim, hh->id);
		ret = -EINVAL;
	पूर्ण
	अगर (!ret)
		dev_kमुक्त_skb(skb);
	वापस ret;
पूर्ण

अटल पूर्णांक
channel_bctrl(काष्ठा bchannel *bch, काष्ठा mISDN_ctrl_req *cq)
अणु
	वापस mISDN_ctrl_bchannel(bch, cq);
पूर्ण

अटल पूर्णांक
खोलो_bchannel(काष्ठा w6692_hw *card, काष्ठा channel_req *rq)
अणु
	काष्ठा bchannel *bch;

	अगर (rq->adr.channel == 0 || rq->adr.channel > 2)
		वापस -EINVAL;
	अगर (rq->protocol == ISDN_P_NONE)
		वापस -EINVAL;
	bch = &card->bc[rq->adr.channel - 1].bch;
	अगर (test_and_set_bit(FLG_OPEN, &bch->Flags))
		वापस -EBUSY; /* b-channel can be only खोलो once */
	bch->ch.protocol = rq->protocol;
	rq->ch = &bch->ch;
	वापस 0;
पूर्ण

अटल पूर्णांक
channel_ctrl(काष्ठा w6692_hw *card, काष्ठा mISDN_ctrl_req *cq)
अणु
	पूर्णांक	ret = 0;

	चयन (cq->op) अणु
	हाल MISDN_CTRL_GETOP:
		cq->op = MISDN_CTRL_L1_TIMER3;
		अवरोध;
	हाल MISDN_CTRL_L1_TIMER3:
		ret = l1_event(card->dch.l1, HW_TIMER3_VALUE | (cq->p1 & 0xff));
		अवरोध;
	शेष:
		pr_info("%s: unknown CTRL OP %x\n", card->name, cq->op);
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
w6692_bctrl(काष्ठा mISDNchannel *ch, u32 cmd, व्योम *arg)
अणु
	काष्ठा bchannel *bch = container_of(ch, काष्ठा bchannel, ch);
	काष्ठा w6692_ch *bc = container_of(bch, काष्ठा w6692_ch, bch);
	काष्ठा w6692_hw *card = bch->hw;
	पूर्णांक ret = -EINVAL;
	u_दीर्घ flags;

	pr_debug("%s: %s cmd:%x %p\n", card->name, __func__, cmd, arg);
	चयन (cmd) अणु
	हाल CLOSE_CHANNEL:
		test_and_clear_bit(FLG_OPEN, &bch->Flags);
		cancel_work_sync(&bch->workq);
		spin_lock_irqsave(&card->lock, flags);
		mISDN_clear_bchannel(bch);
		w6692_mode(bc, ISDN_P_NONE);
		spin_unlock_irqrestore(&card->lock, flags);
		ch->protocol = ISDN_P_NONE;
		ch->peer = शून्य;
		module_put(THIS_MODULE);
		ret = 0;
		अवरोध;
	हाल CONTROL_CHANNEL:
		ret = channel_bctrl(bch, arg);
		अवरोध;
	शेष:
		pr_info("%s: %s unknown prim(%x)\n",
			card->name, __func__, cmd);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
w6692_l2l1D(काष्ठा mISDNchannel *ch, काष्ठा sk_buff *skb)
अणु
	काष्ठा mISDNdevice	*dev = container_of(ch, काष्ठा mISDNdevice, D);
	काष्ठा dchannel		*dch = container_of(dev, काष्ठा dchannel, dev);
	काष्ठा w6692_hw		*card = container_of(dch, काष्ठा w6692_hw, dch);
	पूर्णांक			ret = -EINVAL;
	काष्ठा mISDNhead	*hh = mISDN_HEAD_P(skb);
	u32			id;
	u_दीर्घ			flags;

	चयन (hh->prim) अणु
	हाल PH_DATA_REQ:
		spin_lock_irqsave(&card->lock, flags);
		ret = dchannel_senddata(dch, skb);
		अगर (ret > 0) अणु /* direct TX */
			id = hh->id; /* skb can be मुक्तd */
			W6692_fill_Dfअगरo(card);
			ret = 0;
			spin_unlock_irqrestore(&card->lock, flags);
			queue_ch_frame(ch, PH_DATA_CNF, id, शून्य);
		पूर्ण अन्यथा
			spin_unlock_irqrestore(&card->lock, flags);
		वापस ret;
	हाल PH_ACTIVATE_REQ:
		ret = l1_event(dch->l1, hh->prim);
		अवरोध;
	हाल PH_DEACTIVATE_REQ:
		test_and_clear_bit(FLG_L2_ACTIVATED, &dch->Flags);
		ret = l1_event(dch->l1, hh->prim);
		अवरोध;
	पूर्ण

	अगर (!ret)
		dev_kमुक्त_skb(skb);
	वापस ret;
पूर्ण

अटल पूर्णांक
w6692_l1callback(काष्ठा dchannel *dch, u32 cmd)
अणु
	काष्ठा w6692_hw *card = container_of(dch, काष्ठा w6692_hw, dch);
	u_दीर्घ flags;

	pr_debug("%s: cmd(%x) state(%02x)\n", card->name, cmd, card->state);
	चयन (cmd) अणु
	हाल INFO3_P8:
		spin_lock_irqsave(&card->lock, flags);
		ph_command(card, W_L1CMD_AR8);
		spin_unlock_irqrestore(&card->lock, flags);
		अवरोध;
	हाल INFO3_P10:
		spin_lock_irqsave(&card->lock, flags);
		ph_command(card, W_L1CMD_AR10);
		spin_unlock_irqrestore(&card->lock, flags);
		अवरोध;
	हाल HW_RESET_REQ:
		spin_lock_irqsave(&card->lock, flags);
		अगर (card->state != W_L1IND_DRD)
			ph_command(card, W_L1CMD_RST);
		ph_command(card, W_L1CMD_ECK);
		spin_unlock_irqrestore(&card->lock, flags);
		अवरोध;
	हाल HW_DEACT_REQ:
		skb_queue_purge(&dch->squeue);
		अगर (dch->tx_skb) अणु
			dev_kमुक्त_skb(dch->tx_skb);
			dch->tx_skb = शून्य;
		पूर्ण
		dch->tx_idx = 0;
		अगर (dch->rx_skb) अणु
			dev_kमुक्त_skb(dch->rx_skb);
			dch->rx_skb = शून्य;
		पूर्ण
		test_and_clear_bit(FLG_TX_BUSY, &dch->Flags);
		अगर (test_and_clear_bit(FLG_BUSY_TIMER, &dch->Flags))
			del_समयr(&dch->समयr);
		अवरोध;
	हाल HW_POWERUP_REQ:
		spin_lock_irqsave(&card->lock, flags);
		ph_command(card, W_L1CMD_ECK);
		spin_unlock_irqrestore(&card->lock, flags);
		अवरोध;
	हाल PH_ACTIVATE_IND:
		test_and_set_bit(FLG_ACTIVE, &dch->Flags);
		_queue_data(&dch->dev.D, cmd, MISDN_ID_ANY, 0, शून्य,
			    GFP_ATOMIC);
		अवरोध;
	हाल PH_DEACTIVATE_IND:
		test_and_clear_bit(FLG_ACTIVE, &dch->Flags);
		_queue_data(&dch->dev.D, cmd, MISDN_ID_ANY, 0, शून्य,
			    GFP_ATOMIC);
		अवरोध;
	शेष:
		pr_debug("%s: %s unknown command %x\n", card->name,
			 __func__, cmd);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
खोलो_dchannel(काष्ठा w6692_hw *card, काष्ठा channel_req *rq, व्योम *caller)
अणु
	pr_debug("%s: %s dev(%d) open from %p\n", card->name, __func__,
		 card->dch.dev.id, caller);
	अगर (rq->protocol != ISDN_P_TE_S0)
		वापस -EINVAL;
	अगर (rq->adr.channel == 1)
		/* E-Channel not supported */
		वापस -EINVAL;
	rq->ch = &card->dch.dev.D;
	rq->ch->protocol = rq->protocol;
	अगर (card->dch.state == 7)
		_queue_data(rq->ch, PH_ACTIVATE_IND, MISDN_ID_ANY,
			    0, शून्य, GFP_KERNEL);
	वापस 0;
पूर्ण

अटल पूर्णांक
w6692_dctrl(काष्ठा mISDNchannel *ch, u32 cmd, व्योम *arg)
अणु
	काष्ठा mISDNdevice *dev = container_of(ch, काष्ठा mISDNdevice, D);
	काष्ठा dchannel *dch = container_of(dev, काष्ठा dchannel, dev);
	काष्ठा w6692_hw *card = container_of(dch, काष्ठा w6692_hw, dch);
	काष्ठा channel_req *rq;
	पूर्णांक err = 0;

	pr_debug("%s: DCTRL: %x %p\n", card->name, cmd, arg);
	चयन (cmd) अणु
	हाल OPEN_CHANNEL:
		rq = arg;
		अगर (rq->protocol == ISDN_P_TE_S0)
			err = खोलो_dchannel(card, rq, __builtin_वापस_address(0));
		अन्यथा
			err = खोलो_bchannel(card, rq);
		अगर (err)
			अवरोध;
		अगर (!try_module_get(THIS_MODULE))
			pr_info("%s: cannot get module\n", card->name);
		अवरोध;
	हाल CLOSE_CHANNEL:
		pr_debug("%s: dev(%d) close from %p\n", card->name,
			 dch->dev.id, __builtin_वापस_address(0));
		module_put(THIS_MODULE);
		अवरोध;
	हाल CONTROL_CHANNEL:
		err = channel_ctrl(card, arg);
		अवरोध;
	शेष:
		pr_debug("%s: unknown DCTRL command %x\n", card->name, cmd);
		वापस -EINVAL;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक
setup_w6692(काष्ठा w6692_hw *card)
अणु
	u32	val;

	अगर (!request_region(card->addr, 256, card->name)) अणु
		pr_info("%s: config port %x-%x already in use\n", card->name,
			card->addr, card->addr + 255);
		वापस -EIO;
	पूर्ण
	W6692Version(card);
	card->bc[0].addr = card->addr;
	card->bc[1].addr = card->addr + 0x40;
	val = ReadW6692(card, W_ISTA);
	अगर (debug & DEBUG_HW)
		pr_notice("%s ISTA=%02x\n", card->name, val);
	val = ReadW6692(card, W_IMASK);
	अगर (debug & DEBUG_HW)
		pr_notice("%s IMASK=%02x\n", card->name, val);
	val = ReadW6692(card, W_D_EXIR);
	अगर (debug & DEBUG_HW)
		pr_notice("%s D_EXIR=%02x\n", card->name, val);
	val = ReadW6692(card, W_D_EXIM);
	अगर (debug & DEBUG_HW)
		pr_notice("%s D_EXIM=%02x\n", card->name, val);
	val = ReadW6692(card, W_D_RSTA);
	अगर (debug & DEBUG_HW)
		pr_notice("%s D_RSTA=%02x\n", card->name, val);
	वापस 0;
पूर्ण

अटल व्योम
release_card(काष्ठा w6692_hw *card)
अणु
	u_दीर्घ	flags;

	spin_lock_irqsave(&card->lock, flags);
	disable_hwirq(card);
	w6692_mode(&card->bc[0], ISDN_P_NONE);
	w6692_mode(&card->bc[1], ISDN_P_NONE);
	अगर ((card->fmask & led) || card->subtype == W6692_USR) अणु
		card->xdata |= 0x04;	/*  LED OFF */
		WriteW6692(card, W_XDATA, card->xdata);
	पूर्ण
	spin_unlock_irqrestore(&card->lock, flags);
	मुक्त_irq(card->irq, card);
	l1_event(card->dch.l1, CLOSE_CHANNEL);
	mISDN_unरेजिस्टर_device(&card->dch.dev);
	release_region(card->addr, 256);
	mISDN_मुक्तbchannel(&card->bc[1].bch);
	mISDN_मुक्तbchannel(&card->bc[0].bch);
	mISDN_मुक्तdchannel(&card->dch);
	ग_लिखो_lock_irqsave(&card_lock, flags);
	list_del(&card->list);
	ग_लिखो_unlock_irqrestore(&card_lock, flags);
	pci_disable_device(card->pdev);
	pci_set_drvdata(card->pdev, शून्य);
	kमुक्त(card);
पूर्ण

अटल पूर्णांक
setup_instance(काष्ठा w6692_hw *card)
अणु
	पूर्णांक		i, err;
	u_दीर्घ		flags;

	snम_लिखो(card->name, MISDN_MAX_IDLEN - 1, "w6692.%d", w6692_cnt + 1);
	ग_लिखो_lock_irqsave(&card_lock, flags);
	list_add_tail(&card->list, &Cards);
	ग_लिखो_unlock_irqrestore(&card_lock, flags);
	card->fmask = (1 << w6692_cnt);
	_set_debug(card);
	spin_lock_init(&card->lock);
	mISDN_initdchannel(&card->dch, MAX_DFRAME_LEN_L1, W6692_ph_bh);
	card->dch.dev.Dprotocols = (1 << ISDN_P_TE_S0);
	card->dch.dev.D.send = w6692_l2l1D;
	card->dch.dev.D.ctrl = w6692_dctrl;
	card->dch.dev.Bprotocols = (1 << (ISDN_P_B_RAW & ISDN_P_B_MASK)) |
		(1 << (ISDN_P_B_HDLC & ISDN_P_B_MASK));
	card->dch.hw = card;
	card->dch.dev.nrbchan = 2;
	क्रम (i = 0; i < 2; i++) अणु
		mISDN_initbchannel(&card->bc[i].bch, MAX_DATA_MEM,
				   W_B_FIFO_THRESH);
		card->bc[i].bch.hw = card;
		card->bc[i].bch.nr = i + 1;
		card->bc[i].bch.ch.nr = i + 1;
		card->bc[i].bch.ch.send = w6692_l2l1B;
		card->bc[i].bch.ch.ctrl = w6692_bctrl;
		set_channelmap(i + 1, card->dch.dev.channelmap);
		list_add(&card->bc[i].bch.ch.list, &card->dch.dev.bchannels);
	पूर्ण
	err = setup_w6692(card);
	अगर (err)
		जाओ error_setup;
	err = mISDN_रेजिस्टर_device(&card->dch.dev, &card->pdev->dev,
				    card->name);
	अगर (err)
		जाओ error_reg;
	err = init_card(card);
	अगर (err)
		जाओ error_init;
	err = create_l1(&card->dch, w6692_l1callback);
	अगर (!err) अणु
		w6692_cnt++;
		pr_notice("W6692 %d cards installed\n", w6692_cnt);
		वापस 0;
	पूर्ण

	मुक्त_irq(card->irq, card);
error_init:
	mISDN_unरेजिस्टर_device(&card->dch.dev);
error_reg:
	release_region(card->addr, 256);
error_setup:
	mISDN_मुक्तbchannel(&card->bc[1].bch);
	mISDN_मुक्तbchannel(&card->bc[0].bch);
	mISDN_मुक्तdchannel(&card->dch);
	ग_लिखो_lock_irqsave(&card_lock, flags);
	list_del(&card->list);
	ग_लिखो_unlock_irqrestore(&card_lock, flags);
	kमुक्त(card);
	वापस err;
पूर्ण

अटल पूर्णांक
w6692_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक		err = -ENOMEM;
	काष्ठा w6692_hw	*card;
	काष्ठा w6692map	*m = (काष्ठा w6692map *)ent->driver_data;

	card = kzalloc(माप(काष्ठा w6692_hw), GFP_KERNEL);
	अगर (!card) अणु
		pr_info("No kmem for w6692 card\n");
		वापस err;
	पूर्ण
	card->pdev = pdev;
	card->subtype = m->subtype;
	err = pci_enable_device(pdev);
	अगर (err) अणु
		kमुक्त(card);
		वापस err;
	पूर्ण

	prपूर्णांकk(KERN_INFO "mISDN_w6692: found adapter %s at %s\n",
	       m->name, pci_name(pdev));

	card->addr = pci_resource_start(pdev, 1);
	card->irq = pdev->irq;
	pci_set_drvdata(pdev, card);
	err = setup_instance(card);
	अगर (err)
		pci_set_drvdata(pdev, शून्य);
	वापस err;
पूर्ण

अटल व्योम
w6692_हटाओ_pci(काष्ठा pci_dev *pdev)
अणु
	काष्ठा w6692_hw	*card = pci_get_drvdata(pdev);

	अगर (card)
		release_card(card);
	अन्यथा
		अगर (debug)
			pr_notice("%s: drvdata already removed\n", __func__);
पूर्ण

अटल स्थिर काष्ठा pci_device_id w6692_ids[] = अणु
	अणु PCI_VENDOR_ID_DYNALINK, PCI_DEVICE_ID_DYNALINK_IS64PH,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, (uदीर्घ)&w6692_map[0]पूर्ण,
	अणु PCI_VENDOR_ID_WINBOND2, PCI_DEVICE_ID_WINBOND2_6692,
	  PCI_VENDOR_ID_USR, PCI_DEVICE_ID_USR_6692, 0, 0,
	  (uदीर्घ)&w6692_map[2]पूर्ण,
	अणु PCI_VENDOR_ID_WINBOND2, PCI_DEVICE_ID_WINBOND2_6692,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, (uदीर्घ)&w6692_map[1]पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, w6692_ids);

अटल काष्ठा pci_driver w6692_driver = अणु
	.name =  "w6692",
	.probe = w6692_probe,
	.हटाओ = w6692_हटाओ_pci,
	.id_table = w6692_ids,
पूर्ण;

अटल पूर्णांक __init w6692_init(व्योम)
अणु
	पूर्णांक err;

	pr_notice("Winbond W6692 PCI driver Rev. %s\n", W6692_REV);

	err = pci_रेजिस्टर_driver(&w6692_driver);
	वापस err;
पूर्ण

अटल व्योम __निकास w6692_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&w6692_driver);
पूर्ण

module_init(w6692_init);
module_निकास(w6692_cleanup);
