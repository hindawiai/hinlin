<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * isac.c   ISAC specअगरic routines
 *
 * Author       Karsten Keil <keil@isdn4linux.de>
 *
 * Copyright 2009  by Karsten Keil <keil@isdn4linux.de>
 */

#समावेश <linux/irqवापस.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/mISDNhw.h>
#समावेश "ipac.h"


#घोषणा DBUSY_TIMER_VALUE	80
#घोषणा ARCOFI_USE		1

#घोषणा ISAC_REV		"2.0"

MODULE_AUTHOR("Karsten Keil");
MODULE_VERSION(ISAC_REV);
MODULE_LICENSE("GPL v2");

#घोषणा ReadISAC(is, o)		(is->पढ़ो_reg(is->dch.hw, o + is->off))
#घोषणा	WriteISAC(is, o, v)	(is->ग_लिखो_reg(is->dch.hw, o + is->off, v))
#घोषणा ReadHSCX(h, o)		(h->ip->पढ़ो_reg(h->ip->hw, h->off + o))
#घोषणा WriteHSCX(h, o, v)	(h->ip->ग_लिखो_reg(h->ip->hw, h->off + o, v))
#घोषणा ReadIPAC(ip, o)		(ip->पढ़ो_reg(ip->hw, o))
#घोषणा WriteIPAC(ip, o, v)	(ip->ग_लिखो_reg(ip->hw, o, v))

अटल अंतरभूत व्योम
ph_command(काष्ठा isac_hw *isac, u8 command)
अणु
	pr_debug("%s: ph_command %x\n", isac->name, command);
	अगर (isac->type & IPAC_TYPE_ISACX)
		WriteISAC(isac, ISACX_CIX0, (command << 4) | 0xE);
	अन्यथा
		WriteISAC(isac, ISAC_CIX0, (command << 2) | 3);
पूर्ण

अटल व्योम
isac_ph_state_change(काष्ठा isac_hw *isac)
अणु
	चयन (isac->state) अणु
	हाल (ISAC_IND_RS):
	हाल (ISAC_IND_EI):
		ph_command(isac, ISAC_CMD_DUI);
	पूर्ण
	schedule_event(&isac->dch, FLG_PHCHANGE);
पूर्ण

अटल व्योम
isac_ph_state_bh(काष्ठा dchannel *dch)
अणु
	काष्ठा isac_hw *isac = container_of(dch, काष्ठा isac_hw, dch);

	चयन (isac->state) अणु
	हाल ISAC_IND_RS:
	हाल ISAC_IND_EI:
		dch->state = 0;
		l1_event(dch->l1, HW_RESET_IND);
		अवरोध;
	हाल ISAC_IND_DID:
		dch->state = 3;
		l1_event(dch->l1, HW_DEACT_CNF);
		अवरोध;
	हाल ISAC_IND_DR:
	हाल ISAC_IND_DR6:
		dch->state = 3;
		l1_event(dch->l1, HW_DEACT_IND);
		अवरोध;
	हाल ISAC_IND_PU:
		dch->state = 4;
		l1_event(dch->l1, HW_POWERUP_IND);
		अवरोध;
	हाल ISAC_IND_RSY:
		अगर (dch->state <= 5) अणु
			dch->state = 5;
			l1_event(dch->l1, ANYSIGNAL);
		पूर्ण अन्यथा अणु
			dch->state = 8;
			l1_event(dch->l1, LOSTFRAMING);
		पूर्ण
		अवरोध;
	हाल ISAC_IND_ARD:
		dch->state = 6;
		l1_event(dch->l1, INFO2);
		अवरोध;
	हाल ISAC_IND_AI8:
		dch->state = 7;
		l1_event(dch->l1, INFO4_P8);
		अवरोध;
	हाल ISAC_IND_AI10:
		dch->state = 7;
		l1_event(dch->l1, INFO4_P10);
		अवरोध;
	पूर्ण
	pr_debug("%s: TE newstate %x\n", isac->name, dch->state);
पूर्ण

अटल व्योम
isac_empty_fअगरo(काष्ठा isac_hw *isac, पूर्णांक count)
अणु
	u8 *ptr;

	pr_debug("%s: %s  %d\n", isac->name, __func__, count);

	अगर (!isac->dch.rx_skb) अणु
		isac->dch.rx_skb = mI_alloc_skb(isac->dch.maxlen, GFP_ATOMIC);
		अगर (!isac->dch.rx_skb) अणु
			pr_info("%s: D receive out of memory\n", isac->name);
			WriteISAC(isac, ISAC_CMDR, 0x80);
			वापस;
		पूर्ण
	पूर्ण
	अगर ((isac->dch.rx_skb->len + count) >= isac->dch.maxlen) अणु
		pr_debug("%s: %s overrun %d\n", isac->name, __func__,
			 isac->dch.rx_skb->len + count);
		WriteISAC(isac, ISAC_CMDR, 0x80);
		वापस;
	पूर्ण
	ptr = skb_put(isac->dch.rx_skb, count);
	isac->पढ़ो_fअगरo(isac->dch.hw, isac->off, ptr, count);
	WriteISAC(isac, ISAC_CMDR, 0x80);
	अगर (isac->dch.debug & DEBUG_HW_DFIFO) अणु
		अक्षर	pfx[MISDN_MAX_IDLEN + 16];

		snम_लिखो(pfx, MISDN_MAX_IDLEN + 15, "D-recv %s %d ",
			 isac->name, count);
		prपूर्णांक_hex_dump_bytes(pfx, DUMP_PREFIX_OFFSET, ptr, count);
	पूर्ण
पूर्ण

अटल व्योम
isac_fill_fअगरo(काष्ठा isac_hw *isac)
अणु
	पूर्णांक count, more;
	u8 *ptr;

	अगर (!isac->dch.tx_skb)
		वापस;
	count = isac->dch.tx_skb->len - isac->dch.tx_idx;
	अगर (count <= 0)
		वापस;

	more = 0;
	अगर (count > 32) अणु
		more = !0;
		count = 32;
	पूर्ण
	pr_debug("%s: %s  %d\n", isac->name, __func__, count);
	ptr = isac->dch.tx_skb->data + isac->dch.tx_idx;
	isac->dch.tx_idx += count;
	isac->ग_लिखो_fअगरo(isac->dch.hw, isac->off, ptr, count);
	WriteISAC(isac, ISAC_CMDR, more ? 0x8 : 0xa);
	अगर (test_and_set_bit(FLG_BUSY_TIMER, &isac->dch.Flags)) अणु
		pr_debug("%s: %s dbusytimer running\n", isac->name, __func__);
		del_समयr(&isac->dch.समयr);
	पूर्ण
	isac->dch.समयr.expires = jअगरfies + ((DBUSY_TIMER_VALUE * HZ)/1000);
	add_समयr(&isac->dch.समयr);
	अगर (isac->dch.debug & DEBUG_HW_DFIFO) अणु
		अक्षर	pfx[MISDN_MAX_IDLEN + 16];

		snम_लिखो(pfx, MISDN_MAX_IDLEN + 15, "D-send %s %d ",
			 isac->name, count);
		prपूर्णांक_hex_dump_bytes(pfx, DUMP_PREFIX_OFFSET, ptr, count);
	पूर्ण
पूर्ण

अटल व्योम
isac_rme_irq(काष्ठा isac_hw *isac)
अणु
	u8 val, count;

	val = ReadISAC(isac, ISAC_RSTA);
	अगर ((val & 0x70) != 0x20) अणु
		अगर (val & 0x40) अणु
			pr_debug("%s: ISAC RDO\n", isac->name);
#अगर_घोषित ERROR_STATISTIC
			isac->dch.err_rx++;
#पूर्ण_अगर
		पूर्ण
		अगर (!(val & 0x20)) अणु
			pr_debug("%s: ISAC CRC error\n", isac->name);
#अगर_घोषित ERROR_STATISTIC
			isac->dch.err_crc++;
#पूर्ण_अगर
		पूर्ण
		WriteISAC(isac, ISAC_CMDR, 0x80);
		dev_kमुक्त_skb(isac->dch.rx_skb);
		isac->dch.rx_skb = शून्य;
	पूर्ण अन्यथा अणु
		count = ReadISAC(isac, ISAC_RBCL) & 0x1f;
		अगर (count == 0)
			count = 32;
		isac_empty_fअगरo(isac, count);
		recv_Dchannel(&isac->dch);
	पूर्ण
पूर्ण

अटल व्योम
isac_xpr_irq(काष्ठा isac_hw *isac)
अणु
	अगर (test_and_clear_bit(FLG_BUSY_TIMER, &isac->dch.Flags))
		del_समयr(&isac->dch.समयr);
	अगर (isac->dch.tx_skb && isac->dch.tx_idx < isac->dch.tx_skb->len) अणु
		isac_fill_fअगरo(isac);
	पूर्ण अन्यथा अणु
		dev_kमुक्त_skb(isac->dch.tx_skb);
		अगर (get_next_dframe(&isac->dch))
			isac_fill_fअगरo(isac);
	पूर्ण
पूर्ण

अटल व्योम
isac_retransmit(काष्ठा isac_hw *isac)
अणु
	अगर (test_and_clear_bit(FLG_BUSY_TIMER, &isac->dch.Flags))
		del_समयr(&isac->dch.समयr);
	अगर (test_bit(FLG_TX_BUSY, &isac->dch.Flags)) अणु
		/* Restart frame */
		isac->dch.tx_idx = 0;
		isac_fill_fअगरo(isac);
	पूर्ण अन्यथा अगर (isac->dch.tx_skb) अणु /* should not happen */
		pr_info("%s: tx_skb exist but not busy\n", isac->name);
		test_and_set_bit(FLG_TX_BUSY, &isac->dch.Flags);
		isac->dch.tx_idx = 0;
		isac_fill_fअगरo(isac);
	पूर्ण अन्यथा अणु
		pr_info("%s: ISAC XDU no TX_BUSY\n", isac->name);
		अगर (get_next_dframe(&isac->dch))
			isac_fill_fअगरo(isac);
	पूर्ण
पूर्ण

अटल व्योम
isac_mos_irq(काष्ठा isac_hw *isac)
अणु
	u8 val;
	पूर्णांक ret;

	val = ReadISAC(isac, ISAC_MOSR);
	pr_debug("%s: ISAC MOSR %02x\n", isac->name, val);
#अगर ARCOFI_USE
	अगर (val & 0x08) अणु
		अगर (!isac->mon_rx) अणु
			isac->mon_rx = kदो_स्मृति(MAX_MON_FRAME, GFP_ATOMIC);
			अगर (!isac->mon_rx) अणु
				pr_info("%s: ISAC MON RX out of memory!\n",
					isac->name);
				isac->mocr &= 0xf0;
				isac->mocr |= 0x0a;
				WriteISAC(isac, ISAC_MOCR, isac->mocr);
				जाओ afterMONR0;
			पूर्ण अन्यथा
				isac->mon_rxp = 0;
		पूर्ण
		अगर (isac->mon_rxp >= MAX_MON_FRAME) अणु
			isac->mocr &= 0xf0;
			isac->mocr |= 0x0a;
			WriteISAC(isac, ISAC_MOCR, isac->mocr);
			isac->mon_rxp = 0;
			pr_debug("%s: ISAC MON RX overflow!\n", isac->name);
			जाओ afterMONR0;
		पूर्ण
		isac->mon_rx[isac->mon_rxp++] = ReadISAC(isac, ISAC_MOR0);
		pr_debug("%s: ISAC MOR0 %02x\n", isac->name,
			 isac->mon_rx[isac->mon_rxp - 1]);
		अगर (isac->mon_rxp == 1) अणु
			isac->mocr |= 0x04;
			WriteISAC(isac, ISAC_MOCR, isac->mocr);
		पूर्ण
	पूर्ण
afterMONR0:
	अगर (val & 0x80) अणु
		अगर (!isac->mon_rx) अणु
			isac->mon_rx = kदो_स्मृति(MAX_MON_FRAME, GFP_ATOMIC);
			अगर (!isac->mon_rx) अणु
				pr_info("%s: ISAC MON RX out of memory!\n",
					isac->name);
				isac->mocr &= 0x0f;
				isac->mocr |= 0xa0;
				WriteISAC(isac, ISAC_MOCR, isac->mocr);
				जाओ afterMONR1;
			पूर्ण अन्यथा
				isac->mon_rxp = 0;
		पूर्ण
		अगर (isac->mon_rxp >= MAX_MON_FRAME) अणु
			isac->mocr &= 0x0f;
			isac->mocr |= 0xa0;
			WriteISAC(isac, ISAC_MOCR, isac->mocr);
			isac->mon_rxp = 0;
			pr_debug("%s: ISAC MON RX overflow!\n", isac->name);
			जाओ afterMONR1;
		पूर्ण
		isac->mon_rx[isac->mon_rxp++] = ReadISAC(isac, ISAC_MOR1);
		pr_debug("%s: ISAC MOR1 %02x\n", isac->name,
			 isac->mon_rx[isac->mon_rxp - 1]);
		isac->mocr |= 0x40;
		WriteISAC(isac, ISAC_MOCR, isac->mocr);
	पूर्ण
afterMONR1:
	अगर (val & 0x04) अणु
		isac->mocr &= 0xf0;
		WriteISAC(isac, ISAC_MOCR, isac->mocr);
		isac->mocr |= 0x0a;
		WriteISAC(isac, ISAC_MOCR, isac->mocr);
		अगर (isac->monitor) अणु
			ret = isac->monitor(isac->dch.hw, MONITOR_RX_0,
					    isac->mon_rx, isac->mon_rxp);
			अगर (ret)
				kमुक्त(isac->mon_rx);
		पूर्ण अन्यथा अणु
			pr_info("%s: MONITOR 0 received %d but no user\n",
				isac->name, isac->mon_rxp);
			kमुक्त(isac->mon_rx);
		पूर्ण
		isac->mon_rx = शून्य;
		isac->mon_rxp = 0;
	पूर्ण
	अगर (val & 0x40) अणु
		isac->mocr &= 0x0f;
		WriteISAC(isac, ISAC_MOCR, isac->mocr);
		isac->mocr |= 0xa0;
		WriteISAC(isac, ISAC_MOCR, isac->mocr);
		अगर (isac->monitor) अणु
			ret = isac->monitor(isac->dch.hw, MONITOR_RX_1,
					    isac->mon_rx, isac->mon_rxp);
			अगर (ret)
				kमुक्त(isac->mon_rx);
		पूर्ण अन्यथा अणु
			pr_info("%s: MONITOR 1 received %d but no user\n",
				isac->name, isac->mon_rxp);
			kमुक्त(isac->mon_rx);
		पूर्ण
		isac->mon_rx = शून्य;
		isac->mon_rxp = 0;
	पूर्ण
	अगर (val & 0x02) अणु
		अगर ((!isac->mon_tx) || (isac->mon_txc &&
					(isac->mon_txp >= isac->mon_txc) && !(val & 0x08))) अणु
			isac->mocr &= 0xf0;
			WriteISAC(isac, ISAC_MOCR, isac->mocr);
			isac->mocr |= 0x0a;
			WriteISAC(isac, ISAC_MOCR, isac->mocr);
			अगर (isac->mon_txc && (isac->mon_txp >= isac->mon_txc)) अणु
				अगर (isac->monitor)
					isac->monitor(isac->dch.hw,
						      MONITOR_TX_0, शून्य, 0);
			पूर्ण
			kमुक्त(isac->mon_tx);
			isac->mon_tx = शून्य;
			isac->mon_txc = 0;
			isac->mon_txp = 0;
			जाओ AfterMOX0;
		पूर्ण
		अगर (isac->mon_txc && (isac->mon_txp >= isac->mon_txc)) अणु
			अगर (isac->monitor)
				isac->monitor(isac->dch.hw,
					      MONITOR_TX_0, शून्य, 0);
			kमुक्त(isac->mon_tx);
			isac->mon_tx = शून्य;
			isac->mon_txc = 0;
			isac->mon_txp = 0;
			जाओ AfterMOX0;
		पूर्ण
		WriteISAC(isac, ISAC_MOX0, isac->mon_tx[isac->mon_txp++]);
		pr_debug("%s: ISAC %02x -> MOX0\n", isac->name,
			 isac->mon_tx[isac->mon_txp - 1]);
	पूर्ण
AfterMOX0:
	अगर (val & 0x20) अणु
		अगर ((!isac->mon_tx) || (isac->mon_txc &&
					(isac->mon_txp >= isac->mon_txc) && !(val & 0x80))) अणु
			isac->mocr &= 0x0f;
			WriteISAC(isac, ISAC_MOCR, isac->mocr);
			isac->mocr |= 0xa0;
			WriteISAC(isac, ISAC_MOCR, isac->mocr);
			अगर (isac->mon_txc && (isac->mon_txp >= isac->mon_txc)) अणु
				अगर (isac->monitor)
					isac->monitor(isac->dch.hw,
						      MONITOR_TX_1, शून्य, 0);
			पूर्ण
			kमुक्त(isac->mon_tx);
			isac->mon_tx = शून्य;
			isac->mon_txc = 0;
			isac->mon_txp = 0;
			जाओ AfterMOX1;
		पूर्ण
		अगर (isac->mon_txc && (isac->mon_txp >= isac->mon_txc)) अणु
			अगर (isac->monitor)
				isac->monitor(isac->dch.hw,
					      MONITOR_TX_1, शून्य, 0);
			kमुक्त(isac->mon_tx);
			isac->mon_tx = शून्य;
			isac->mon_txc = 0;
			isac->mon_txp = 0;
			जाओ AfterMOX1;
		पूर्ण
		WriteISAC(isac, ISAC_MOX1, isac->mon_tx[isac->mon_txp++]);
		pr_debug("%s: ISAC %02x -> MOX1\n", isac->name,
			 isac->mon_tx[isac->mon_txp - 1]);
	पूर्ण
AfterMOX1:
	val = 0; /* dummy to aव्योम warning */
#पूर्ण_अगर
पूर्ण

अटल व्योम
isac_cisq_irq(काष्ठा isac_hw *isac) अणु
	u8 val;

	val = ReadISAC(isac, ISAC_CIR0);
	pr_debug("%s: ISAC CIR0 %02X\n", isac->name, val);
	अगर (val & 2) अणु
		pr_debug("%s: ph_state change %x->%x\n", isac->name,
			 isac->state, (val >> 2) & 0xf);
		isac->state = (val >> 2) & 0xf;
		isac_ph_state_change(isac);
	पूर्ण
	अगर (val & 1) अणु
		val = ReadISAC(isac, ISAC_CIR1);
		pr_debug("%s: ISAC CIR1 %02X\n", isac->name, val);
	पूर्ण
पूर्ण

अटल व्योम
isacsx_cic_irq(काष्ठा isac_hw *isac)
अणु
	u8 val;

	val = ReadISAC(isac, ISACX_CIR0);
	pr_debug("%s: ISACX CIR0 %02X\n", isac->name, val);
	अगर (val & ISACX_CIR0_CIC0) अणु
		pr_debug("%s: ph_state change %x->%x\n", isac->name,
			 isac->state, val >> 4);
		isac->state = val >> 4;
		isac_ph_state_change(isac);
	पूर्ण
पूर्ण

अटल व्योम
isacsx_rme_irq(काष्ठा isac_hw *isac)
अणु
	पूर्णांक count;
	u8 val;

	val = ReadISAC(isac, ISACX_RSTAD);
	अगर ((val & (ISACX_RSTAD_VFR |
		    ISACX_RSTAD_RDO |
		    ISACX_RSTAD_CRC |
		    ISACX_RSTAD_RAB))
	    != (ISACX_RSTAD_VFR | ISACX_RSTAD_CRC)) अणु
		pr_debug("%s: RSTAD %#x, dropped\n", isac->name, val);
#अगर_घोषित ERROR_STATISTIC
		अगर (val & ISACX_RSTAD_CRC)
			isac->dch.err_rx++;
		अन्यथा
			isac->dch.err_crc++;
#पूर्ण_अगर
		WriteISAC(isac, ISACX_CMDRD, ISACX_CMDRD_RMC);
		dev_kमुक्त_skb(isac->dch.rx_skb);
		isac->dch.rx_skb = शून्य;
	पूर्ण अन्यथा अणु
		count = ReadISAC(isac, ISACX_RBCLD) & 0x1f;
		अगर (count == 0)
			count = 32;
		isac_empty_fअगरo(isac, count);
		अगर (isac->dch.rx_skb) अणु
			skb_trim(isac->dch.rx_skb, isac->dch.rx_skb->len - 1);
			pr_debug("%s: dchannel received %d\n", isac->name,
				 isac->dch.rx_skb->len);
			recv_Dchannel(&isac->dch);
		पूर्ण
	पूर्ण
पूर्ण

irqवापस_t
mISDNisac_irq(काष्ठा isac_hw *isac, u8 val)
अणु
	अगर (unlikely(!val))
		वापस IRQ_NONE;
	pr_debug("%s: ISAC interrupt %02x\n", isac->name, val);
	अगर (isac->type & IPAC_TYPE_ISACX) अणु
		अगर (val & ISACX__CIC)
			isacsx_cic_irq(isac);
		अगर (val & ISACX__ICD) अणु
			val = ReadISAC(isac, ISACX_ISTAD);
			pr_debug("%s: ISTAD %02x\n", isac->name, val);
			अगर (val & ISACX_D_XDU) अणु
				pr_debug("%s: ISAC XDU\n", isac->name);
#अगर_घोषित ERROR_STATISTIC
				isac->dch.err_tx++;
#पूर्ण_अगर
				isac_retransmit(isac);
			पूर्ण
			अगर (val & ISACX_D_XMR) अणु
				pr_debug("%s: ISAC XMR\n", isac->name);
#अगर_घोषित ERROR_STATISTIC
				isac->dch.err_tx++;
#पूर्ण_अगर
				isac_retransmit(isac);
			पूर्ण
			अगर (val & ISACX_D_XPR)
				isac_xpr_irq(isac);
			अगर (val & ISACX_D_RFO) अणु
				pr_debug("%s: ISAC RFO\n", isac->name);
				WriteISAC(isac, ISACX_CMDRD, ISACX_CMDRD_RMC);
			पूर्ण
			अगर (val & ISACX_D_RME)
				isacsx_rme_irq(isac);
			अगर (val & ISACX_D_RPF)
				isac_empty_fअगरo(isac, 0x20);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (val & 0x80)	/* RME */
			isac_rme_irq(isac);
		अगर (val & 0x40)	/* RPF */
			isac_empty_fअगरo(isac, 32);
		अगर (val & 0x10)	/* XPR */
			isac_xpr_irq(isac);
		अगर (val & 0x04)	/* CISQ */
			isac_cisq_irq(isac);
		अगर (val & 0x20)	/* RSC - never */
			pr_debug("%s: ISAC RSC interrupt\n", isac->name);
		अगर (val & 0x02)	/* SIN - never */
			pr_debug("%s: ISAC SIN interrupt\n", isac->name);
		अगर (val & 0x01) अणु	/* EXI */
			val = ReadISAC(isac, ISAC_EXIR);
			pr_debug("%s: ISAC EXIR %02x\n", isac->name, val);
			अगर (val & 0x80)	/* XMR */
				pr_debug("%s: ISAC XMR\n", isac->name);
			अगर (val & 0x40) अणु /* XDU */
				pr_debug("%s: ISAC XDU\n", isac->name);
#अगर_घोषित ERROR_STATISTIC
				isac->dch.err_tx++;
#पूर्ण_अगर
				isac_retransmit(isac);
			पूर्ण
			अगर (val & 0x04)	/* MOS */
				isac_mos_irq(isac);
		पूर्ण
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण
EXPORT_SYMBOL(mISDNisac_irq);

अटल पूर्णांक
isac_l1hw(काष्ठा mISDNchannel *ch, काष्ठा sk_buff *skb)
अणु
	काष्ठा mISDNdevice	*dev = container_of(ch, काष्ठा mISDNdevice, D);
	काष्ठा dchannel		*dch = container_of(dev, काष्ठा dchannel, dev);
	काष्ठा isac_hw		*isac = container_of(dch, काष्ठा isac_hw, dch);
	पूर्णांक			ret = -EINVAL;
	काष्ठा mISDNhead	*hh = mISDN_HEAD_P(skb);
	u32			id;
	u_दीर्घ			flags;

	चयन (hh->prim) अणु
	हाल PH_DATA_REQ:
		spin_lock_irqsave(isac->hwlock, flags);
		ret = dchannel_senddata(dch, skb);
		अगर (ret > 0) अणु /* direct TX */
			id = hh->id; /* skb can be मुक्तd */
			isac_fill_fअगरo(isac);
			ret = 0;
			spin_unlock_irqrestore(isac->hwlock, flags);
			queue_ch_frame(ch, PH_DATA_CNF, id, शून्य);
		पूर्ण अन्यथा
			spin_unlock_irqrestore(isac->hwlock, flags);
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
isac_ctrl(काष्ठा isac_hw *isac, u32 cmd, अचिन्हित दीर्घ para)
अणु
	u8 tl = 0;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	चयन (cmd) अणु
	हाल HW_TESTLOOP:
		spin_lock_irqsave(isac->hwlock, flags);
		अगर (!(isac->type & IPAC_TYPE_ISACX)) अणु
			/* TODO: implement क्रम IPAC_TYPE_ISACX */
			अगर (para & 1) /* B1 */
				tl |= 0x0c;
			अन्यथा अगर (para & 2) /* B2 */
				tl |= 0x3;
			/* we only support IOM2 mode */
			WriteISAC(isac, ISAC_SPCR, tl);
			अगर (tl)
				WriteISAC(isac, ISAC_ADF1, 0x8);
			अन्यथा
				WriteISAC(isac, ISAC_ADF1, 0x0);
		पूर्ण
		spin_unlock_irqrestore(isac->hwlock, flags);
		अवरोध;
	हाल HW_TIMER3_VALUE:
		ret = l1_event(isac->dch.l1, HW_TIMER3_VALUE | (para & 0xff));
		अवरोध;
	शेष:
		pr_debug("%s: %s unknown command %x %lx\n", isac->name,
			 __func__, cmd, para);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
isac_l1cmd(काष्ठा dchannel *dch, u32 cmd)
अणु
	काष्ठा isac_hw *isac = container_of(dch, काष्ठा isac_hw, dch);
	u_दीर्घ flags;

	pr_debug("%s: cmd(%x) state(%02x)\n", isac->name, cmd, isac->state);
	चयन (cmd) अणु
	हाल INFO3_P8:
		spin_lock_irqsave(isac->hwlock, flags);
		ph_command(isac, ISAC_CMD_AR8);
		spin_unlock_irqrestore(isac->hwlock, flags);
		अवरोध;
	हाल INFO3_P10:
		spin_lock_irqsave(isac->hwlock, flags);
		ph_command(isac, ISAC_CMD_AR10);
		spin_unlock_irqrestore(isac->hwlock, flags);
		अवरोध;
	हाल HW_RESET_REQ:
		spin_lock_irqsave(isac->hwlock, flags);
		अगर ((isac->state == ISAC_IND_EI) ||
		    (isac->state == ISAC_IND_DR) ||
		    (isac->state == ISAC_IND_DR6) ||
		    (isac->state == ISAC_IND_RS))
			ph_command(isac, ISAC_CMD_TIM);
		अन्यथा
			ph_command(isac, ISAC_CMD_RS);
		spin_unlock_irqrestore(isac->hwlock, flags);
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
		spin_lock_irqsave(isac->hwlock, flags);
		ph_command(isac, ISAC_CMD_TIM);
		spin_unlock_irqrestore(isac->hwlock, flags);
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
		pr_debug("%s: %s unknown command %x\n", isac->name,
			 __func__, cmd);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
isac_release(काष्ठा isac_hw *isac)
अणु
	अगर (isac->type & IPAC_TYPE_ISACX)
		WriteISAC(isac, ISACX_MASK, 0xff);
	अन्यथा अगर (isac->type != 0)
		WriteISAC(isac, ISAC_MASK, 0xff);
	अगर (isac->dch.समयr.function != शून्य) अणु
		del_समयr(&isac->dch.समयr);
		isac->dch.समयr.function = शून्य;
	पूर्ण
	kमुक्त(isac->mon_rx);
	isac->mon_rx = शून्य;
	kमुक्त(isac->mon_tx);
	isac->mon_tx = शून्य;
	अगर (isac->dch.l1)
		l1_event(isac->dch.l1, CLOSE_CHANNEL);
	mISDN_मुक्तdchannel(&isac->dch);
पूर्ण

अटल व्योम
dbusy_समयr_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा isac_hw *isac = from_समयr(isac, t, dch.समयr);
	पूर्णांक rbch, star;
	u_दीर्घ flags;

	अगर (test_bit(FLG_BUSY_TIMER, &isac->dch.Flags)) अणु
		spin_lock_irqsave(isac->hwlock, flags);
		rbch = ReadISAC(isac, ISAC_RBCH);
		star = ReadISAC(isac, ISAC_STAR);
		pr_debug("%s: D-Channel Busy RBCH %02x STAR %02x\n",
			 isac->name, rbch, star);
		अगर (rbch & ISAC_RBCH_XAC) /* D-Channel Busy */
			test_and_set_bit(FLG_L1_BUSY, &isac->dch.Flags);
		अन्यथा अणु
			/* discard frame; reset transceiver */
			test_and_clear_bit(FLG_BUSY_TIMER, &isac->dch.Flags);
			अगर (isac->dch.tx_idx)
				isac->dch.tx_idx = 0;
			अन्यथा
				pr_info("%s: ISAC D-Channel Busy no tx_idx\n",
					isac->name);
			/* Transmitter reset */
			WriteISAC(isac, ISAC_CMDR, 0x01);
		पूर्ण
		spin_unlock_irqrestore(isac->hwlock, flags);
	पूर्ण
पूर्ण

अटल पूर्णांक
खोलो_dchannel_caller(काष्ठा isac_hw *isac, काष्ठा channel_req *rq, व्योम *caller)
अणु
	pr_debug("%s: %s dev(%d) open from %p\n", isac->name, __func__,
		 isac->dch.dev.id, caller);
	अगर (rq->protocol != ISDN_P_TE_S0)
		वापस -EINVAL;
	अगर (rq->adr.channel == 1)
		/* E-Channel not supported */
		वापस -EINVAL;
	rq->ch = &isac->dch.dev.D;
	rq->ch->protocol = rq->protocol;
	अगर (isac->dch.state == 7)
		_queue_data(rq->ch, PH_ACTIVATE_IND, MISDN_ID_ANY,
			    0, शून्य, GFP_KERNEL);
	वापस 0;
पूर्ण

अटल पूर्णांक
खोलो_dchannel(काष्ठा isac_hw *isac, काष्ठा channel_req *rq)
अणु
	वापस खोलो_dchannel_caller(isac, rq, __builtin_वापस_address(0));
पूर्ण

अटल स्थिर अक्षर *ISACVer[] =
अणु"2086/2186 V1.1", "2085 B1", "2085 B2",
 "2085 V2.3"पूर्ण;

अटल पूर्णांक
isac_init(काष्ठा isac_hw *isac)
अणु
	u8 val;
	पूर्णांक err = 0;

	अगर (!isac->dch.l1) अणु
		err = create_l1(&isac->dch, isac_l1cmd);
		अगर (err)
			वापस err;
	पूर्ण
	isac->mon_tx = शून्य;
	isac->mon_rx = शून्य;
	समयr_setup(&isac->dch.समयr, dbusy_समयr_handler, 0);
	isac->mocr = 0xaa;
	अगर (isac->type & IPAC_TYPE_ISACX) अणु
		/* Disable all IRQ */
		WriteISAC(isac, ISACX_MASK, 0xff);
		val = ReadISAC(isac, ISACX_STARD);
		pr_debug("%s: ISACX STARD %x\n", isac->name, val);
		val = ReadISAC(isac, ISACX_ISTAD);
		pr_debug("%s: ISACX ISTAD %x\n", isac->name, val);
		val = ReadISAC(isac, ISACX_ISTA);
		pr_debug("%s: ISACX ISTA %x\n", isac->name, val);
		/* clear LDD */
		WriteISAC(isac, ISACX_TR_CONF0, 0x00);
		/* enable transmitter */
		WriteISAC(isac, ISACX_TR_CONF2, 0x00);
		/* transparent mode 0, RAC, stop/go */
		WriteISAC(isac, ISACX_MODED, 0xc9);
		/* all HDLC IRQ unmasked */
		val = ReadISAC(isac, ISACX_ID);
		अगर (isac->dch.debug & DEBUG_HW)
			pr_notice("%s: ISACX Design ID %x\n",
				  isac->name, val & 0x3f);
		val = ReadISAC(isac, ISACX_CIR0);
		pr_debug("%s: ISACX CIR0 %02X\n", isac->name, val);
		isac->state = val >> 4;
		isac_ph_state_change(isac);
		ph_command(isac, ISAC_CMD_RS);
		WriteISAC(isac, ISACX_MASK, IPACX__ON);
		WriteISAC(isac, ISACX_MASKD, 0x00);
	पूर्ण अन्यथा अणु /* old isac */
		WriteISAC(isac, ISAC_MASK, 0xff);
		val = ReadISAC(isac, ISAC_STAR);
		pr_debug("%s: ISAC STAR %x\n", isac->name, val);
		val = ReadISAC(isac, ISAC_MODE);
		pr_debug("%s: ISAC MODE %x\n", isac->name, val);
		val = ReadISAC(isac, ISAC_ADF2);
		pr_debug("%s: ISAC ADF2 %x\n", isac->name, val);
		val = ReadISAC(isac, ISAC_ISTA);
		pr_debug("%s: ISAC ISTA %x\n", isac->name, val);
		अगर (val & 0x01) अणु
			val = ReadISAC(isac, ISAC_EXIR);
			pr_debug("%s: ISAC EXIR %x\n", isac->name, val);
		पूर्ण
		val = ReadISAC(isac, ISAC_RBCH);
		अगर (isac->dch.debug & DEBUG_HW)
			pr_notice("%s: ISAC version (%x): %s\n", isac->name,
				  val, ISACVer[(val >> 5) & 3]);
		isac->type |= ((val >> 5) & 3);
		अगर (!isac->adf2)
			isac->adf2 = 0x80;
		अगर (!(isac->adf2 & 0x80)) अणु /* only IOM 2 Mode */
			pr_info("%s: only support IOM2 mode but adf2=%02x\n",
				isac->name, isac->adf2);
			isac_release(isac);
			वापस -EINVAL;
		पूर्ण
		WriteISAC(isac, ISAC_ADF2, isac->adf2);
		WriteISAC(isac, ISAC_SQXR, 0x2f);
		WriteISAC(isac, ISAC_SPCR, 0x00);
		WriteISAC(isac, ISAC_STCR, 0x70);
		WriteISAC(isac, ISAC_MODE, 0xc9);
		WriteISAC(isac, ISAC_TIMR, 0x00);
		WriteISAC(isac, ISAC_ADF1, 0x00);
		val = ReadISAC(isac, ISAC_CIR0);
		pr_debug("%s: ISAC CIR0 %x\n", isac->name, val);
		isac->state = (val >> 2) & 0xf;
		isac_ph_state_change(isac);
		ph_command(isac, ISAC_CMD_RS);
		WriteISAC(isac, ISAC_MASK, 0);
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक
mISDNisac_init(काष्ठा isac_hw *isac, व्योम *hw)
अणु
	mISDN_initdchannel(&isac->dch, MAX_DFRAME_LEN_L1, isac_ph_state_bh);
	isac->dch.hw = hw;
	isac->dch.dev.D.send = isac_l1hw;
	isac->init = isac_init;
	isac->release = isac_release;
	isac->ctrl = isac_ctrl;
	isac->खोलो = खोलो_dchannel;
	isac->dch.dev.Dprotocols = (1 << ISDN_P_TE_S0);
	isac->dch.dev.nrbchan = 2;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mISDNisac_init);

अटल व्योम
रुकोक्रमCEC(काष्ठा hscx_hw *hx)
अणु
	u8 starb, to = 50;

	जबतक (to) अणु
		starb = ReadHSCX(hx, IPAC_STARB);
		अगर (!(starb & 0x04))
			अवरोध;
		udelay(1);
		to--;
	पूर्ण
	अगर (to < 50)
		pr_debug("%s: B%1d CEC %d us\n", hx->ip->name, hx->bch.nr,
			 50 - to);
	अगर (!to)
		pr_info("%s: B%1d CEC timeout\n", hx->ip->name, hx->bch.nr);
पूर्ण


अटल व्योम
रुकोक्रमXFW(काष्ठा hscx_hw *hx)
अणु
	u8 starb, to = 50;

	जबतक (to) अणु
		starb = ReadHSCX(hx, IPAC_STARB);
		अगर ((starb & 0x44) == 0x40)
			अवरोध;
		udelay(1);
		to--;
	पूर्ण
	अगर (to < 50)
		pr_debug("%s: B%1d XFW %d us\n", hx->ip->name, hx->bch.nr,
			 50 - to);
	अगर (!to)
		pr_info("%s: B%1d XFW timeout\n", hx->ip->name, hx->bch.nr);
पूर्ण

अटल व्योम
hscx_cmdr(काष्ठा hscx_hw *hx, u8 cmd)
अणु
	अगर (hx->ip->type & IPAC_TYPE_IPACX)
		WriteHSCX(hx, IPACX_CMDRB, cmd);
	अन्यथा अणु
		रुकोक्रमCEC(hx);
		WriteHSCX(hx, IPAC_CMDRB, cmd);
	पूर्ण
पूर्ण

अटल व्योम
hscx_empty_fअगरo(काष्ठा hscx_hw *hscx, u8 count)
अणु
	u8 *p;
	पूर्णांक maxlen;

	pr_debug("%s: B%1d %d\n", hscx->ip->name, hscx->bch.nr, count);
	अगर (test_bit(FLG_RX_OFF, &hscx->bch.Flags)) अणु
		hscx->bch.dropcnt += count;
		hscx_cmdr(hscx, 0x80); /* RMC */
		वापस;
	पूर्ण
	maxlen = bchannel_get_rxbuf(&hscx->bch, count);
	अगर (maxlen < 0) अणु
		hscx_cmdr(hscx, 0x80); /* RMC */
		अगर (hscx->bch.rx_skb)
			skb_trim(hscx->bch.rx_skb, 0);
		pr_warn("%s.B%d: No bufferspace for %d bytes\n",
			hscx->ip->name, hscx->bch.nr, count);
		वापस;
	पूर्ण
	p = skb_put(hscx->bch.rx_skb, count);

	अगर (hscx->ip->type & IPAC_TYPE_IPACX)
		hscx->ip->पढ़ो_fअगरo(hscx->ip->hw,
				    hscx->off + IPACX_RFIFOB, p, count);
	अन्यथा
		hscx->ip->पढ़ो_fअगरo(hscx->ip->hw,
				    hscx->off, p, count);

	hscx_cmdr(hscx, 0x80); /* RMC */

	अगर (hscx->bch.debug & DEBUG_HW_BFIFO) अणु
		snम_लिखो(hscx->log, 64, "B%1d-recv %s %d ",
			 hscx->bch.nr, hscx->ip->name, count);
		prपूर्णांक_hex_dump_bytes(hscx->log, DUMP_PREFIX_OFFSET, p, count);
	पूर्ण
पूर्ण

अटल व्योम
hscx_fill_fअगरo(काष्ठा hscx_hw *hscx)
अणु
	पूर्णांक count, more;
	u8 *p;

	अगर (!hscx->bch.tx_skb) अणु
		अगर (!test_bit(FLG_TX_EMPTY, &hscx->bch.Flags))
			वापस;
		count = hscx->fअगरo_size;
		more = 1;
		p = hscx->log;
		स_रखो(p, hscx->bch.fill[0], count);
	पूर्ण अन्यथा अणु
		count = hscx->bch.tx_skb->len - hscx->bch.tx_idx;
		अगर (count <= 0)
			वापस;
		p = hscx->bch.tx_skb->data + hscx->bch.tx_idx;

		more = test_bit(FLG_TRANSPARENT, &hscx->bch.Flags) ? 1 : 0;
		अगर (count > hscx->fअगरo_size) अणु
			count = hscx->fअगरo_size;
			more = 1;
		पूर्ण
		pr_debug("%s: B%1d %d/%d/%d\n", hscx->ip->name, hscx->bch.nr,
			 count, hscx->bch.tx_idx, hscx->bch.tx_skb->len);
		hscx->bch.tx_idx += count;
	पूर्ण
	अगर (hscx->ip->type & IPAC_TYPE_IPACX)
		hscx->ip->ग_लिखो_fअगरo(hscx->ip->hw,
				     hscx->off + IPACX_XFIFOB, p, count);
	अन्यथा अणु
		रुकोक्रमXFW(hscx);
		hscx->ip->ग_लिखो_fअगरo(hscx->ip->hw,
				     hscx->off, p, count);
	पूर्ण
	hscx_cmdr(hscx, more ? 0x08 : 0x0a);

	अगर (hscx->bch.tx_skb && (hscx->bch.debug & DEBUG_HW_BFIFO)) अणु
		snम_लिखो(hscx->log, 64, "B%1d-send %s %d ",
			 hscx->bch.nr, hscx->ip->name, count);
		prपूर्णांक_hex_dump_bytes(hscx->log, DUMP_PREFIX_OFFSET, p, count);
	पूर्ण
पूर्ण

अटल व्योम
hscx_xpr(काष्ठा hscx_hw *hx)
अणु
	अगर (hx->bch.tx_skb && hx->bch.tx_idx < hx->bch.tx_skb->len) अणु
		hscx_fill_fअगरo(hx);
	पूर्ण अन्यथा अणु
		dev_kमुक्त_skb(hx->bch.tx_skb);
		अगर (get_next_bframe(&hx->bch)) अणु
			hscx_fill_fअगरo(hx);
			test_and_clear_bit(FLG_TX_EMPTY, &hx->bch.Flags);
		पूर्ण अन्यथा अगर (test_bit(FLG_TX_EMPTY, &hx->bch.Flags)) अणु
			hscx_fill_fअगरo(hx);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
ipac_rme(काष्ठा hscx_hw *hx)
अणु
	पूर्णांक count;
	u8 rstab;

	अगर (hx->ip->type & IPAC_TYPE_IPACX)
		rstab = ReadHSCX(hx, IPACX_RSTAB);
	अन्यथा
		rstab = ReadHSCX(hx, IPAC_RSTAB);
	pr_debug("%s: B%1d RSTAB %02x\n", hx->ip->name, hx->bch.nr, rstab);
	अगर ((rstab & 0xf0) != 0xa0) अणु
		/* !(VFR && !RDO && CRC && !RAB) */
		अगर (!(rstab & 0x80)) अणु
			अगर (hx->bch.debug & DEBUG_HW_BCHANNEL)
				pr_notice("%s: B%1d invalid frame\n",
					  hx->ip->name, hx->bch.nr);
		पूर्ण
		अगर (rstab & 0x40) अणु
			अगर (hx->bch.debug & DEBUG_HW_BCHANNEL)
				pr_notice("%s: B%1d RDO proto=%x\n",
					  hx->ip->name, hx->bch.nr,
					  hx->bch.state);
		पूर्ण
		अगर (!(rstab & 0x20)) अणु
			अगर (hx->bch.debug & DEBUG_HW_BCHANNEL)
				pr_notice("%s: B%1d CRC error\n",
					  hx->ip->name, hx->bch.nr);
		पूर्ण
		hscx_cmdr(hx, 0x80); /* Do RMC */
		वापस;
	पूर्ण
	अगर (hx->ip->type & IPAC_TYPE_IPACX)
		count = ReadHSCX(hx, IPACX_RBCLB);
	अन्यथा
		count = ReadHSCX(hx, IPAC_RBCLB);
	count &= (hx->fअगरo_size - 1);
	अगर (count == 0)
		count = hx->fअगरo_size;
	hscx_empty_fअगरo(hx, count);
	अगर (!hx->bch.rx_skb)
		वापस;
	अगर (hx->bch.rx_skb->len < 2) अणु
		pr_debug("%s: B%1d frame to short %d\n",
			 hx->ip->name, hx->bch.nr, hx->bch.rx_skb->len);
		skb_trim(hx->bch.rx_skb, 0);
	पूर्ण अन्यथा अणु
		skb_trim(hx->bch.rx_skb, hx->bch.rx_skb->len - 1);
		recv_Bchannel(&hx->bch, 0, false);
	पूर्ण
पूर्ण

अटल व्योम
ipac_irq(काष्ठा hscx_hw *hx, u8 ista)
अणु
	u8 istab, m, exirb = 0;

	अगर (hx->ip->type & IPAC_TYPE_IPACX)
		istab = ReadHSCX(hx, IPACX_ISTAB);
	अन्यथा अगर (hx->ip->type & IPAC_TYPE_IPAC) अणु
		istab = ReadHSCX(hx, IPAC_ISTAB);
		m = (hx->bch.nr & 1) ? IPAC__EXA : IPAC__EXB;
		अगर (m & ista) अणु
			exirb = ReadHSCX(hx, IPAC_EXIRB);
			pr_debug("%s: B%1d EXIRB %02x\n", hx->ip->name,
				 hx->bch.nr, exirb);
		पूर्ण
	पूर्ण अन्यथा अगर (hx->bch.nr & 2) अणु /* HSCX B */
		अगर (ista & (HSCX__EXA | HSCX__ICA))
			ipac_irq(&hx->ip->hscx[0], ista);
		अगर (ista & HSCX__EXB) अणु
			exirb = ReadHSCX(hx, IPAC_EXIRB);
			pr_debug("%s: B%1d EXIRB %02x\n", hx->ip->name,
				 hx->bch.nr, exirb);
		पूर्ण
		istab = ista & 0xF8;
	पूर्ण अन्यथा अणु /* HSCX A */
		istab = ReadHSCX(hx, IPAC_ISTAB);
		अगर (ista & HSCX__EXA) अणु
			exirb = ReadHSCX(hx, IPAC_EXIRB);
			pr_debug("%s: B%1d EXIRB %02x\n", hx->ip->name,
				 hx->bch.nr, exirb);
		पूर्ण
		istab = istab & 0xF8;
	पूर्ण
	अगर (exirb & IPAC_B_XDU)
		istab |= IPACX_B_XDU;
	अगर (exirb & IPAC_B_RFO)
		istab |= IPACX_B_RFO;
	pr_debug("%s: B%1d ISTAB %02x\n", hx->ip->name, hx->bch.nr, istab);

	अगर (!test_bit(FLG_ACTIVE, &hx->bch.Flags))
		वापस;

	अगर (istab & IPACX_B_RME)
		ipac_rme(hx);

	अगर (istab & IPACX_B_RPF) अणु
		hscx_empty_fअगरo(hx, hx->fअगरo_size);
		अगर (test_bit(FLG_TRANSPARENT, &hx->bch.Flags))
			recv_Bchannel(&hx->bch, 0, false);
	पूर्ण

	अगर (istab & IPACX_B_RFO) अणु
		pr_debug("%s: B%1d RFO error\n", hx->ip->name, hx->bch.nr);
		hscx_cmdr(hx, 0x40);	/* RRES */
	पूर्ण

	अगर (istab & IPACX_B_XPR)
		hscx_xpr(hx);

	अगर (istab & IPACX_B_XDU) अणु
		अगर (test_bit(FLG_TRANSPARENT, &hx->bch.Flags)) अणु
			अगर (test_bit(FLG_FILLEMPTY, &hx->bch.Flags))
				test_and_set_bit(FLG_TX_EMPTY, &hx->bch.Flags);
			hscx_xpr(hx);
			वापस;
		पूर्ण
		pr_debug("%s: B%1d XDU error at len %d\n", hx->ip->name,
			 hx->bch.nr, hx->bch.tx_idx);
		hx->bch.tx_idx = 0;
		hscx_cmdr(hx, 0x01);	/* XRES */
	पूर्ण
पूर्ण

irqवापस_t
mISDNipac_irq(काष्ठा ipac_hw *ipac, पूर्णांक maxloop)
अणु
	पूर्णांक cnt = maxloop + 1;
	u8 ista, istad;
	काष्ठा isac_hw  *isac = &ipac->isac;

	अगर (ipac->type & IPAC_TYPE_IPACX) अणु
		ista = ReadIPAC(ipac, ISACX_ISTA);
		जबतक (ista && --cnt) अणु
			pr_debug("%s: ISTA %02x\n", ipac->name, ista);
			अगर (ista & IPACX__ICA)
				ipac_irq(&ipac->hscx[0], ista);
			अगर (ista & IPACX__ICB)
				ipac_irq(&ipac->hscx[1], ista);
			अगर (ista & (ISACX__ICD | ISACX__CIC))
				mISDNisac_irq(&ipac->isac, ista);
			ista = ReadIPAC(ipac, ISACX_ISTA);
		पूर्ण
	पूर्ण अन्यथा अगर (ipac->type & IPAC_TYPE_IPAC) अणु
		ista = ReadIPAC(ipac, IPAC_ISTA);
		जबतक (ista && --cnt) अणु
			pr_debug("%s: ISTA %02x\n", ipac->name, ista);
			अगर (ista & (IPAC__ICD | IPAC__EXD)) अणु
				istad = ReadISAC(isac, ISAC_ISTA);
				pr_debug("%s: ISTAD %02x\n", ipac->name, istad);
				अगर (istad & IPAC_D_TIN2)
					pr_debug("%s TIN2 irq\n", ipac->name);
				अगर (ista & IPAC__EXD)
					istad |= 1; /* ISAC EXI */
				mISDNisac_irq(isac, istad);
			पूर्ण
			अगर (ista & (IPAC__ICA | IPAC__EXA))
				ipac_irq(&ipac->hscx[0], ista);
			अगर (ista & (IPAC__ICB | IPAC__EXB))
				ipac_irq(&ipac->hscx[1], ista);
			ista = ReadIPAC(ipac, IPAC_ISTA);
		पूर्ण
	पूर्ण अन्यथा अगर (ipac->type & IPAC_TYPE_HSCX) अणु
		जबतक (--cnt) अणु
			ista = ReadIPAC(ipac, IPAC_ISTAB + ipac->hscx[1].off);
			pr_debug("%s: B2 ISTA %02x\n", ipac->name, ista);
			अगर (ista)
				ipac_irq(&ipac->hscx[1], ista);
			istad = ReadISAC(isac, ISAC_ISTA);
			pr_debug("%s: ISTAD %02x\n", ipac->name, istad);
			अगर (istad)
				mISDNisac_irq(isac, istad);
			अगर (0 == (ista | istad))
				अवरोध;
		पूर्ण
	पूर्ण
	अगर (cnt > maxloop) /* only क्रम ISAC/HSCX without PCI IRQ test */
		वापस IRQ_NONE;
	अगर (cnt < maxloop)
		pr_debug("%s: %d irqloops cpu%d\n", ipac->name,
			 maxloop - cnt, smp_processor_id());
	अगर (maxloop && !cnt)
		pr_notice("%s: %d IRQ LOOP cpu%d\n", ipac->name,
			  maxloop, smp_processor_id());
	वापस IRQ_HANDLED;
पूर्ण
EXPORT_SYMBOL(mISDNipac_irq);

अटल पूर्णांक
hscx_mode(काष्ठा hscx_hw *hscx, u32 bprotocol)
अणु
	pr_debug("%s: HSCX %c protocol %x-->%x ch %d\n", hscx->ip->name,
		 '@' + hscx->bch.nr, hscx->bch.state, bprotocol, hscx->bch.nr);
	अगर (hscx->ip->type & IPAC_TYPE_IPACX) अणु
		अगर (hscx->bch.nr & 1) अणु /* B1 and ICA */
			WriteIPAC(hscx->ip, ISACX_BCHA_TSDP_BC1, 0x80);
			WriteIPAC(hscx->ip, ISACX_BCHA_CR, 0x88);
		पूर्ण अन्यथा अणु /* B2 and ICB */
			WriteIPAC(hscx->ip, ISACX_BCHB_TSDP_BC1, 0x81);
			WriteIPAC(hscx->ip, ISACX_BCHB_CR, 0x88);
		पूर्ण
		चयन (bprotocol) अणु
		हाल ISDN_P_NONE: /* init */
			WriteHSCX(hscx, IPACX_MODEB, 0xC0);	/* rec off */
			WriteHSCX(hscx, IPACX_EXMB,  0x30);	/* std adj. */
			WriteHSCX(hscx, IPACX_MASKB, 0xFF);	/* पूर्णांकs off */
			hscx_cmdr(hscx, 0x41);
			test_and_clear_bit(FLG_HDLC, &hscx->bch.Flags);
			test_and_clear_bit(FLG_TRANSPARENT, &hscx->bch.Flags);
			अवरोध;
		हाल ISDN_P_B_RAW:
			WriteHSCX(hscx, IPACX_MODEB, 0x88);	/* ex trans */
			WriteHSCX(hscx, IPACX_EXMB,  0x00);	/* trans */
			hscx_cmdr(hscx, 0x41);
			WriteHSCX(hscx, IPACX_MASKB, IPACX_B_ON);
			test_and_set_bit(FLG_TRANSPARENT, &hscx->bch.Flags);
			अवरोध;
		हाल ISDN_P_B_HDLC:
			WriteHSCX(hscx, IPACX_MODEB, 0xC0);	/* trans */
			WriteHSCX(hscx, IPACX_EXMB,  0x00);	/* hdlc,crc */
			hscx_cmdr(hscx, 0x41);
			WriteHSCX(hscx, IPACX_MASKB, IPACX_B_ON);
			test_and_set_bit(FLG_HDLC, &hscx->bch.Flags);
			अवरोध;
		शेष:
			pr_info("%s: protocol not known %x\n", hscx->ip->name,
				bprotocol);
			वापस -ENOPROTOOPT;
		पूर्ण
	पूर्ण अन्यथा अगर (hscx->ip->type & IPAC_TYPE_IPAC) अणु /* IPAC */
		WriteHSCX(hscx, IPAC_CCR1, 0x82);
		WriteHSCX(hscx, IPAC_CCR2, 0x30);
		WriteHSCX(hscx, IPAC_XCCR, 0x07);
		WriteHSCX(hscx, IPAC_RCCR, 0x07);
		WriteHSCX(hscx, IPAC_TSAX, hscx->slot);
		WriteHSCX(hscx, IPAC_TSAR, hscx->slot);
		चयन (bprotocol) अणु
		हाल ISDN_P_NONE:
			WriteHSCX(hscx, IPAC_TSAX, 0x1F);
			WriteHSCX(hscx, IPAC_TSAR, 0x1F);
			WriteHSCX(hscx, IPAC_MODEB, 0x84);
			WriteHSCX(hscx, IPAC_CCR1, 0x82);
			WriteHSCX(hscx, IPAC_MASKB, 0xFF);	/* पूर्णांकs off */
			test_and_clear_bit(FLG_HDLC, &hscx->bch.Flags);
			test_and_clear_bit(FLG_TRANSPARENT, &hscx->bch.Flags);
			अवरोध;
		हाल ISDN_P_B_RAW:
			WriteHSCX(hscx, IPAC_MODEB, 0xe4);	/* ex trans */
			WriteHSCX(hscx, IPAC_CCR1, 0x82);
			hscx_cmdr(hscx, 0x41);
			WriteHSCX(hscx, IPAC_MASKB, 0);
			test_and_set_bit(FLG_TRANSPARENT, &hscx->bch.Flags);
			अवरोध;
		हाल ISDN_P_B_HDLC:
			WriteHSCX(hscx, IPAC_MODEB, 0x8c);
			WriteHSCX(hscx, IPAC_CCR1, 0x8a);
			hscx_cmdr(hscx, 0x41);
			WriteHSCX(hscx, IPAC_MASKB, 0);
			test_and_set_bit(FLG_HDLC, &hscx->bch.Flags);
			अवरोध;
		शेष:
			pr_info("%s: protocol not known %x\n", hscx->ip->name,
				bprotocol);
			वापस -ENOPROTOOPT;
		पूर्ण
	पूर्ण अन्यथा अगर (hscx->ip->type & IPAC_TYPE_HSCX) अणु /* HSCX */
		WriteHSCX(hscx, IPAC_CCR1, 0x85);
		WriteHSCX(hscx, IPAC_CCR2, 0x30);
		WriteHSCX(hscx, IPAC_XCCR, 0x07);
		WriteHSCX(hscx, IPAC_RCCR, 0x07);
		WriteHSCX(hscx, IPAC_TSAX, hscx->slot);
		WriteHSCX(hscx, IPAC_TSAR, hscx->slot);
		चयन (bprotocol) अणु
		हाल ISDN_P_NONE:
			WriteHSCX(hscx, IPAC_TSAX, 0x1F);
			WriteHSCX(hscx, IPAC_TSAR, 0x1F);
			WriteHSCX(hscx, IPAC_MODEB, 0x84);
			WriteHSCX(hscx, IPAC_CCR1, 0x85);
			WriteHSCX(hscx, IPAC_MASKB, 0xFF);	/* पूर्णांकs off */
			test_and_clear_bit(FLG_HDLC, &hscx->bch.Flags);
			test_and_clear_bit(FLG_TRANSPARENT, &hscx->bch.Flags);
			अवरोध;
		हाल ISDN_P_B_RAW:
			WriteHSCX(hscx, IPAC_MODEB, 0xe4);	/* ex trans */
			WriteHSCX(hscx, IPAC_CCR1, 0x85);
			hscx_cmdr(hscx, 0x41);
			WriteHSCX(hscx, IPAC_MASKB, 0);
			test_and_set_bit(FLG_TRANSPARENT, &hscx->bch.Flags);
			अवरोध;
		हाल ISDN_P_B_HDLC:
			WriteHSCX(hscx, IPAC_MODEB, 0x8c);
			WriteHSCX(hscx, IPAC_CCR1, 0x8d);
			hscx_cmdr(hscx, 0x41);
			WriteHSCX(hscx, IPAC_MASKB, 0);
			test_and_set_bit(FLG_HDLC, &hscx->bch.Flags);
			अवरोध;
		शेष:
			pr_info("%s: protocol not known %x\n", hscx->ip->name,
				bprotocol);
			वापस -ENOPROTOOPT;
		पूर्ण
	पूर्ण अन्यथा
		वापस -EINVAL;
	hscx->bch.state = bprotocol;
	वापस 0;
पूर्ण

अटल पूर्णांक
hscx_l2l1(काष्ठा mISDNchannel *ch, काष्ठा sk_buff *skb)
अणु
	काष्ठा bchannel *bch = container_of(ch, काष्ठा bchannel, ch);
	काष्ठा hscx_hw	*hx = container_of(bch, काष्ठा hscx_hw, bch);
	पूर्णांक ret = -EINVAL;
	काष्ठा mISDNhead *hh = mISDN_HEAD_P(skb);
	अचिन्हित दीर्घ flags;

	चयन (hh->prim) अणु
	हाल PH_DATA_REQ:
		spin_lock_irqsave(hx->ip->hwlock, flags);
		ret = bchannel_senddata(bch, skb);
		अगर (ret > 0) अणु /* direct TX */
			ret = 0;
			hscx_fill_fअगरo(hx);
		पूर्ण
		spin_unlock_irqrestore(hx->ip->hwlock, flags);
		वापस ret;
	हाल PH_ACTIVATE_REQ:
		spin_lock_irqsave(hx->ip->hwlock, flags);
		अगर (!test_and_set_bit(FLG_ACTIVE, &bch->Flags))
			ret = hscx_mode(hx, ch->protocol);
		अन्यथा
			ret = 0;
		spin_unlock_irqrestore(hx->ip->hwlock, flags);
		अगर (!ret)
			_queue_data(ch, PH_ACTIVATE_IND, MISDN_ID_ANY, 0,
				    शून्य, GFP_KERNEL);
		अवरोध;
	हाल PH_DEACTIVATE_REQ:
		spin_lock_irqsave(hx->ip->hwlock, flags);
		mISDN_clear_bchannel(bch);
		hscx_mode(hx, ISDN_P_NONE);
		spin_unlock_irqrestore(hx->ip->hwlock, flags);
		_queue_data(ch, PH_DEACTIVATE_IND, MISDN_ID_ANY, 0,
			    शून्य, GFP_KERNEL);
		ret = 0;
		अवरोध;
	शेष:
		pr_info("%s: %s unknown prim(%x,%x)\n",
			hx->ip->name, __func__, hh->prim, hh->id);
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
hscx_bctrl(काष्ठा mISDNchannel *ch, u32 cmd, व्योम *arg)
अणु
	काष्ठा bchannel *bch = container_of(ch, काष्ठा bchannel, ch);
	काष्ठा hscx_hw	*hx = container_of(bch, काष्ठा hscx_hw, bch);
	पूर्णांक ret = -EINVAL;
	u_दीर्घ flags;

	pr_debug("%s: %s cmd:%x %p\n", hx->ip->name, __func__, cmd, arg);
	चयन (cmd) अणु
	हाल CLOSE_CHANNEL:
		test_and_clear_bit(FLG_OPEN, &bch->Flags);
		cancel_work_sync(&bch->workq);
		spin_lock_irqsave(hx->ip->hwlock, flags);
		mISDN_clear_bchannel(bch);
		hscx_mode(hx, ISDN_P_NONE);
		spin_unlock_irqrestore(hx->ip->hwlock, flags);
		ch->protocol = ISDN_P_NONE;
		ch->peer = शून्य;
		module_put(hx->ip->owner);
		ret = 0;
		अवरोध;
	हाल CONTROL_CHANNEL:
		ret = channel_bctrl(bch, arg);
		अवरोध;
	शेष:
		pr_info("%s: %s unknown prim(%x)\n",
			hx->ip->name, __func__, cmd);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम
मुक्त_ipac(काष्ठा ipac_hw *ipac)
अणु
	isac_release(&ipac->isac);
पूर्ण

अटल स्थिर अक्षर *HSCXVer[] =
अणु"A1", "?1", "A2", "?3", "A3", "V2.1", "?6", "?7",
 "?8", "?9", "?10", "?11", "?12", "?13", "?14", "???"पूर्ण;



अटल व्योम
hscx_init(काष्ठा hscx_hw *hx)
अणु
	u8 val;

	WriteHSCX(hx, IPAC_RAH2, 0xFF);
	WriteHSCX(hx, IPAC_XBCH, 0x00);
	WriteHSCX(hx, IPAC_RLCR, 0x00);

	अगर (hx->ip->type & IPAC_TYPE_HSCX) अणु
		WriteHSCX(hx, IPAC_CCR1, 0x85);
		val = ReadHSCX(hx, HSCX_VSTR);
		pr_debug("%s: HSCX VSTR %02x\n", hx->ip->name, val);
		अगर (hx->bch.debug & DEBUG_HW)
			pr_notice("%s: HSCX version %s\n", hx->ip->name,
				  HSCXVer[val & 0x0f]);
	पूर्ण अन्यथा
		WriteHSCX(hx, IPAC_CCR1, 0x82);
	WriteHSCX(hx, IPAC_CCR2, 0x30);
	WriteHSCX(hx, IPAC_XCCR, 0x07);
	WriteHSCX(hx, IPAC_RCCR, 0x07);
पूर्ण

अटल पूर्णांक
ipac_init(काष्ठा ipac_hw *ipac)
अणु
	u8 val;

	अगर (ipac->type & IPAC_TYPE_HSCX) अणु
		hscx_init(&ipac->hscx[0]);
		hscx_init(&ipac->hscx[1]);
		val = ReadIPAC(ipac, IPAC_ID);
	पूर्ण अन्यथा अगर (ipac->type & IPAC_TYPE_IPAC) अणु
		hscx_init(&ipac->hscx[0]);
		hscx_init(&ipac->hscx[1]);
		WriteIPAC(ipac, IPAC_MASK, IPAC__ON);
		val = ReadIPAC(ipac, IPAC_CONF);
		/* conf is शेष 0, but can be overwritten by card setup */
		pr_debug("%s: IPAC CONF %02x/%02x\n", ipac->name,
			 val, ipac->conf);
		WriteIPAC(ipac, IPAC_CONF, ipac->conf);
		val = ReadIPAC(ipac, IPAC_ID);
		अगर (ipac->hscx[0].bch.debug & DEBUG_HW)
			pr_notice("%s: IPAC Design ID %02x\n", ipac->name, val);
	पूर्ण
	/* nothing special क्रम IPACX to करो here */
	वापस isac_init(&ipac->isac);
पूर्ण

अटल पूर्णांक
खोलो_bchannel(काष्ठा ipac_hw *ipac, काष्ठा channel_req *rq)
अणु
	काष्ठा bchannel		*bch;

	अगर (rq->adr.channel == 0 || rq->adr.channel > 2)
		वापस -EINVAL;
	अगर (rq->protocol == ISDN_P_NONE)
		वापस -EINVAL;
	bch = &ipac->hscx[rq->adr.channel - 1].bch;
	अगर (test_and_set_bit(FLG_OPEN, &bch->Flags))
		वापस -EBUSY; /* b-channel can be only खोलो once */
	test_and_clear_bit(FLG_FILLEMPTY, &bch->Flags);
	bch->ch.protocol = rq->protocol;
	rq->ch = &bch->ch;
	वापस 0;
पूर्ण

अटल पूर्णांक
channel_ctrl(काष्ठा ipac_hw *ipac, काष्ठा mISDN_ctrl_req *cq)
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
		ret = ipac->ctrl(ipac, HW_TESTLOOP, cq->channel);
		अवरोध;
	हाल MISDN_CTRL_L1_TIMER3:
		ret = ipac->isac.ctrl(&ipac->isac, HW_TIMER3_VALUE, cq->p1);
		अवरोध;
	शेष:
		pr_info("%s: unknown CTRL OP %x\n", ipac->name, cq->op);
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
ipac_dctrl(काष्ठा mISDNchannel *ch, u32 cmd, व्योम *arg)
अणु
	काष्ठा mISDNdevice *dev = container_of(ch, काष्ठा mISDNdevice, D);
	काष्ठा dchannel *dch = container_of(dev, काष्ठा dchannel, dev);
	काष्ठा isac_hw *isac = container_of(dch, काष्ठा isac_hw, dch);
	काष्ठा ipac_hw *ipac = container_of(isac, काष्ठा ipac_hw, isac);
	काष्ठा channel_req *rq;
	पूर्णांक err = 0;

	pr_debug("%s: DCTRL: %x %p\n", ipac->name, cmd, arg);
	चयन (cmd) अणु
	हाल OPEN_CHANNEL:
		rq = arg;
		अगर (rq->protocol == ISDN_P_TE_S0)
			err = खोलो_dchannel_caller(isac, rq, __builtin_वापस_address(0));
		अन्यथा
			err = खोलो_bchannel(ipac, rq);
		अगर (err)
			अवरोध;
		अगर (!try_module_get(ipac->owner))
			pr_info("%s: cannot get module\n", ipac->name);
		अवरोध;
	हाल CLOSE_CHANNEL:
		pr_debug("%s: dev(%d) close from %p\n", ipac->name,
			 dch->dev.id, __builtin_वापस_address(0));
		module_put(ipac->owner);
		अवरोध;
	हाल CONTROL_CHANNEL:
		err = channel_ctrl(ipac, arg);
		अवरोध;
	शेष:
		pr_debug("%s: unknown DCTRL command %x\n", ipac->name, cmd);
		वापस -EINVAL;
	पूर्ण
	वापस err;
पूर्ण

u32
mISDNipac_init(काष्ठा ipac_hw *ipac, व्योम *hw)
अणु
	u32 ret;
	u8 i;

	ipac->hw = hw;
	अगर (ipac->isac.dch.debug & DEBUG_HW)
		pr_notice("%s: ipac type %x\n", ipac->name, ipac->type);
	अगर (ipac->type & IPAC_TYPE_HSCX) अणु
		ipac->isac.type = IPAC_TYPE_ISAC;
		ipac->hscx[0].off = 0;
		ipac->hscx[1].off = 0x40;
		ipac->hscx[0].fअगरo_size = 32;
		ipac->hscx[1].fअगरo_size = 32;
	पूर्ण अन्यथा अगर (ipac->type & IPAC_TYPE_IPAC) अणु
		ipac->isac.type = IPAC_TYPE_IPAC | IPAC_TYPE_ISAC;
		ipac->hscx[0].off = 0;
		ipac->hscx[1].off = 0x40;
		ipac->hscx[0].fअगरo_size = 64;
		ipac->hscx[1].fअगरo_size = 64;
	पूर्ण अन्यथा अगर (ipac->type & IPAC_TYPE_IPACX) अणु
		ipac->isac.type = IPAC_TYPE_IPACX | IPAC_TYPE_ISACX;
		ipac->hscx[0].off = IPACX_OFF_ICA;
		ipac->hscx[1].off = IPACX_OFF_ICB;
		ipac->hscx[0].fअगरo_size = 64;
		ipac->hscx[1].fअगरo_size = 64;
	पूर्ण अन्यथा
		वापस 0;

	mISDNisac_init(&ipac->isac, hw);

	ipac->isac.dch.dev.D.ctrl = ipac_dctrl;

	क्रम (i = 0; i < 2; i++) अणु
		ipac->hscx[i].bch.nr = i + 1;
		set_channelmap(i + 1, ipac->isac.dch.dev.channelmap);
		list_add(&ipac->hscx[i].bch.ch.list,
			 &ipac->isac.dch.dev.bchannels);
		mISDN_initbchannel(&ipac->hscx[i].bch, MAX_DATA_MEM,
				   ipac->hscx[i].fअगरo_size);
		ipac->hscx[i].bch.ch.nr = i + 1;
		ipac->hscx[i].bch.ch.send = &hscx_l2l1;
		ipac->hscx[i].bch.ch.ctrl = hscx_bctrl;
		ipac->hscx[i].bch.hw = hw;
		ipac->hscx[i].ip = ipac;
		/* शेष values क्रम IOM समय slots
		 * can be overwritten by card */
		ipac->hscx[i].slot = (i == 0) ? 0x2f : 0x03;
	पूर्ण

	ipac->init = ipac_init;
	ipac->release = मुक्त_ipac;

	ret =	(1 << (ISDN_P_B_RAW & ISDN_P_B_MASK)) |
		(1 << (ISDN_P_B_HDLC & ISDN_P_B_MASK));
	वापस ret;
पूर्ण
EXPORT_SYMBOL(mISDNipac_init);

अटल पूर्णांक __init
isac_mod_init(व्योम)
अणु
	pr_notice("mISDNipac module version %s\n", ISAC_REV);
	वापस 0;
पूर्ण

अटल व्योम __निकास
isac_mod_cleanup(व्योम)
अणु
	pr_notice("mISDNipac module unloaded\n");
पूर्ण
module_init(isac_mod_init);
module_निकास(isac_mod_cleanup);
