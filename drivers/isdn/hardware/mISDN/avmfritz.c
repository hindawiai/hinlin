<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * avm_fritz.c    low level stuff क्रम AVM FRITZ!CARD PCI ISDN cards
 *                Thanks to AVM, Berlin क्रम inक्रमmations
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
#समावेश <यंत्र/unaligned.h>
#समावेश "ipac.h"


#घोषणा AVMFRITZ_REV	"2.3"

अटल पूर्णांक AVM_cnt;
अटल पूर्णांक debug;

क्रमागत अणु
	AVM_FRITZ_PCI,
	AVM_FRITZ_PCIV2,
पूर्ण;

#घोषणा HDLC_FIFO		0x0
#घोषणा HDLC_STATUS		0x4
#घोषणा CHIP_WINDOW		0x10

#घोषणा CHIP_INDEX		0x4
#घोषणा AVM_HDLC_1		0x00
#घोषणा AVM_HDLC_2		0x01
#घोषणा AVM_ISAC_FIFO		0x02
#घोषणा AVM_ISAC_REG_LOW	0x04
#घोषणा AVM_ISAC_REG_HIGH	0x06

#घोषणा AVM_STATUS0_IRQ_ISAC	0x01
#घोषणा AVM_STATUS0_IRQ_HDLC	0x02
#घोषणा AVM_STATUS0_IRQ_TIMER	0x04
#घोषणा AVM_STATUS0_IRQ_MASK	0x07

#घोषणा AVM_STATUS0_RESET	0x01
#घोषणा AVM_STATUS0_DIS_TIMER	0x02
#घोषणा AVM_STATUS0_RES_TIMER	0x04
#घोषणा AVM_STATUS0_ENA_IRQ	0x08
#घोषणा AVM_STATUS0_TESTBIT	0x10

#घोषणा AVM_STATUS1_INT_SEL	0x0f
#घोषणा AVM_STATUS1_ENA_IOM	0x80

#घोषणा HDLC_MODE_ITF_FLG	0x01
#घोषणा HDLC_MODE_TRANS		0x02
#घोषणा HDLC_MODE_CCR_7		0x04
#घोषणा HDLC_MODE_CCR_16	0x08
#घोषणा HDLC_FIFO_SIZE_128	0x20
#घोषणा HDLC_MODE_TESTLOOP	0x80

#घोषणा HDLC_INT_XPR		0x80
#घोषणा HDLC_INT_XDU		0x40
#घोषणा HDLC_INT_RPR		0x20
#घोषणा HDLC_INT_MASK		0xE0

#घोषणा HDLC_STAT_RME		0x01
#घोषणा HDLC_STAT_RDO		0x10
#घोषणा HDLC_STAT_CRCVFRRAB	0x0E
#घोषणा HDLC_STAT_CRCVFR	0x06
#घोषणा HDLC_STAT_RML_MASK_V1	0x3f00
#घोषणा HDLC_STAT_RML_MASK_V2	0x7f00

#घोषणा HDLC_CMD_XRS		0x80
#घोषणा HDLC_CMD_XME		0x01
#घोषणा HDLC_CMD_RRS		0x20
#घोषणा HDLC_CMD_XML_MASK	0x3f00

#घोषणा HDLC_FIFO_SIZE_V1	32
#घोषणा HDLC_FIFO_SIZE_V2	128

/* Fritz PCI v2.0 */

#घोषणा AVM_HDLC_FIFO_1		0x10
#घोषणा AVM_HDLC_FIFO_2		0x18

#घोषणा AVM_HDLC_STATUS_1	0x14
#घोषणा AVM_HDLC_STATUS_2	0x1c

#घोषणा AVM_ISACX_INDEX		0x04
#घोषणा AVM_ISACX_DATA		0x08

/* data काष्ठा */
#घोषणा LOG_SIZE		63

काष्ठा hdlc_stat_reg अणु
#अगर_घोषित __BIG_ENDIAN
	u8 fill;
	u8 mode;
	u8 xml;
	u8 cmd;
#अन्यथा
	u8 cmd;
	u8 xml;
	u8 mode;
	u8 fill;
#पूर्ण_अगर
पूर्ण __attribute__((packed));

काष्ठा hdlc_hw अणु
	जोड़ अणु
		u32 ctrl;
		काष्ठा hdlc_stat_reg sr;
	पूर्ण ctrl;
	u32 stat;
पूर्ण;

काष्ठा fritzcard अणु
	काष्ठा list_head	list;
	काष्ठा pci_dev		*pdev;
	अक्षर			name[MISDN_MAX_IDLEN];
	u8			type;
	u8			ctrlreg;
	u16			irq;
	u32			irqcnt;
	u32			addr;
	spinlock_t		lock; /* hw lock */
	काष्ठा isac_hw		isac;
	काष्ठा hdlc_hw		hdlc[2];
	काष्ठा bchannel		bch[2];
	अक्षर			log[LOG_SIZE + 1];
पूर्ण;

अटल LIST_HEAD(Cards);
अटल DEFINE_RWLOCK(card_lock); /* protect Cards */

अटल व्योम
_set_debug(काष्ठा fritzcard *card)
अणु
	card->isac.dch.debug = debug;
	card->bch[0].debug = debug;
	card->bch[1].debug = debug;
पूर्ण

अटल पूर्णांक
set_debug(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक ret;
	काष्ठा fritzcard *card;

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
MODULE_VERSION(AVMFRITZ_REV);
module_param_call(debug, set_debug, param_get_uपूर्णांक, &debug, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(debug, "avmfritz debug mask");

/* Interface functions */

अटल u8
ReadISAC_V1(व्योम *p, u8 offset)
अणु
	काष्ठा fritzcard *fc = p;
	u8 idx = (offset > 0x2f) ? AVM_ISAC_REG_HIGH : AVM_ISAC_REG_LOW;

	outb(idx, fc->addr + CHIP_INDEX);
	वापस inb(fc->addr + CHIP_WINDOW + (offset & 0xf));
पूर्ण

अटल व्योम
WriteISAC_V1(व्योम *p, u8 offset, u8 value)
अणु
	काष्ठा fritzcard *fc = p;
	u8 idx = (offset > 0x2f) ? AVM_ISAC_REG_HIGH : AVM_ISAC_REG_LOW;

	outb(idx, fc->addr + CHIP_INDEX);
	outb(value, fc->addr + CHIP_WINDOW + (offset & 0xf));
पूर्ण

अटल व्योम
ReadFiFoISAC_V1(व्योम *p, u8 off, u8 *data, पूर्णांक size)
अणु
	काष्ठा fritzcard *fc = p;

	outb(AVM_ISAC_FIFO, fc->addr + CHIP_INDEX);
	insb(fc->addr + CHIP_WINDOW, data, size);
पूर्ण

अटल व्योम
WriteFiFoISAC_V1(व्योम *p, u8 off, u8 *data, पूर्णांक size)
अणु
	काष्ठा fritzcard *fc = p;

	outb(AVM_ISAC_FIFO, fc->addr + CHIP_INDEX);
	outsb(fc->addr + CHIP_WINDOW, data, size);
पूर्ण

अटल u8
ReadISAC_V2(व्योम *p, u8 offset)
अणु
	काष्ठा fritzcard *fc = p;

	outl(offset, fc->addr + AVM_ISACX_INDEX);
	वापस 0xff & inl(fc->addr + AVM_ISACX_DATA);
पूर्ण

अटल व्योम
WriteISAC_V2(व्योम *p, u8 offset, u8 value)
अणु
	काष्ठा fritzcard *fc = p;

	outl(offset, fc->addr + AVM_ISACX_INDEX);
	outl(value, fc->addr + AVM_ISACX_DATA);
पूर्ण

अटल व्योम
ReadFiFoISAC_V2(व्योम *p, u8 off, u8 *data, पूर्णांक size)
अणु
	काष्ठा fritzcard *fc = p;
	पूर्णांक i;

	outl(off, fc->addr + AVM_ISACX_INDEX);
	क्रम (i = 0; i < size; i++)
		data[i] = 0xff & inl(fc->addr + AVM_ISACX_DATA);
पूर्ण

अटल व्योम
WriteFiFoISAC_V2(व्योम *p, u8 off, u8 *data, पूर्णांक size)
अणु
	काष्ठा fritzcard *fc = p;
	पूर्णांक i;

	outl(off, fc->addr + AVM_ISACX_INDEX);
	क्रम (i = 0; i < size; i++)
		outl(data[i], fc->addr + AVM_ISACX_DATA);
पूर्ण

अटल काष्ठा bchannel *
Sel_BCS(काष्ठा fritzcard *fc, u32 channel)
अणु
	अगर (test_bit(FLG_ACTIVE, &fc->bch[0].Flags) &&
	    (fc->bch[0].nr & channel))
		वापस &fc->bch[0];
	अन्यथा अगर (test_bit(FLG_ACTIVE, &fc->bch[1].Flags) &&
		 (fc->bch[1].nr & channel))
		वापस &fc->bch[1];
	अन्यथा
		वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम
__ग_लिखो_ctrl_pci(काष्ठा fritzcard *fc, काष्ठा hdlc_hw *hdlc, u32 channel) अणु
	u32 idx = channel == 2 ? AVM_HDLC_2 : AVM_HDLC_1;

	outl(idx, fc->addr + CHIP_INDEX);
	outl(hdlc->ctrl.ctrl, fc->addr + CHIP_WINDOW + HDLC_STATUS);
पूर्ण

अटल अंतरभूत व्योम
__ग_लिखो_ctrl_pciv2(काष्ठा fritzcard *fc, काष्ठा hdlc_hw *hdlc, u32 channel) अणु
	outl(hdlc->ctrl.ctrl, fc->addr + (channel == 2 ? AVM_HDLC_STATUS_2 :
					  AVM_HDLC_STATUS_1));
पूर्ण

अटल व्योम
ग_लिखो_ctrl(काष्ठा bchannel *bch, पूर्णांक which) अणु
	काष्ठा fritzcard *fc = bch->hw;
	काष्ठा hdlc_hw *hdlc;

	hdlc = &fc->hdlc[(bch->nr - 1) & 1];
	pr_debug("%s: hdlc %c wr%x ctrl %x\n", fc->name, '@' + bch->nr,
		 which, hdlc->ctrl.ctrl);
	चयन (fc->type) अणु
	हाल AVM_FRITZ_PCIV2:
		__ग_लिखो_ctrl_pciv2(fc, hdlc, bch->nr);
		अवरोध;
	हाल AVM_FRITZ_PCI:
		__ग_लिखो_ctrl_pci(fc, hdlc, bch->nr);
		अवरोध;
	पूर्ण
पूर्ण


अटल अंतरभूत u32
__पढ़ो_status_pci(u_दीर्घ addr, u32 channel)
अणु
	outl(channel == 2 ? AVM_HDLC_2 : AVM_HDLC_1, addr + CHIP_INDEX);
	वापस inl(addr + CHIP_WINDOW + HDLC_STATUS);
पूर्ण

अटल अंतरभूत u32
__पढ़ो_status_pciv2(u_दीर्घ addr, u32 channel)
अणु
	वापस inl(addr + (channel == 2 ? AVM_HDLC_STATUS_2 :
			   AVM_HDLC_STATUS_1));
पूर्ण


अटल u32
पढ़ो_status(काष्ठा fritzcard *fc, u32 channel)
अणु
	चयन (fc->type) अणु
	हाल AVM_FRITZ_PCIV2:
		वापस __पढ़ो_status_pciv2(fc->addr, channel);
	हाल AVM_FRITZ_PCI:
		वापस __पढ़ो_status_pci(fc->addr, channel);
	पूर्ण
	/* dummy */
	वापस 0;
पूर्ण

अटल व्योम
enable_hwirq(काष्ठा fritzcard *fc)
अणु
	fc->ctrlreg |= AVM_STATUS0_ENA_IRQ;
	outb(fc->ctrlreg, fc->addr + 2);
पूर्ण

अटल व्योम
disable_hwirq(काष्ठा fritzcard *fc)
अणु
	fc->ctrlreg &= ~AVM_STATUS0_ENA_IRQ;
	outb(fc->ctrlreg, fc->addr + 2);
पूर्ण

अटल पूर्णांक
modehdlc(काष्ठा bchannel *bch, पूर्णांक protocol)
अणु
	काष्ठा fritzcard *fc = bch->hw;
	काष्ठा hdlc_hw *hdlc;
	u8 mode;

	hdlc = &fc->hdlc[(bch->nr - 1) & 1];
	pr_debug("%s: hdlc %c protocol %x-->%x ch %d\n", fc->name,
		 '@' + bch->nr, bch->state, protocol, bch->nr);
	hdlc->ctrl.ctrl = 0;
	mode = (fc->type == AVM_FRITZ_PCIV2) ? HDLC_FIFO_SIZE_128 : 0;

	चयन (protocol) अणु
	हाल -1: /* used क्रम init */
		bch->state = -1;
		fallthrough;
	हाल ISDN_P_NONE:
		अगर (bch->state == ISDN_P_NONE)
			अवरोध;
		hdlc->ctrl.sr.cmd  = HDLC_CMD_XRS | HDLC_CMD_RRS;
		hdlc->ctrl.sr.mode = mode | HDLC_MODE_TRANS;
		ग_लिखो_ctrl(bch, 5);
		bch->state = ISDN_P_NONE;
		test_and_clear_bit(FLG_HDLC, &bch->Flags);
		test_and_clear_bit(FLG_TRANSPARENT, &bch->Flags);
		अवरोध;
	हाल ISDN_P_B_RAW:
		bch->state = protocol;
		hdlc->ctrl.sr.cmd  = HDLC_CMD_XRS | HDLC_CMD_RRS;
		hdlc->ctrl.sr.mode = mode | HDLC_MODE_TRANS;
		ग_लिखो_ctrl(bch, 5);
		hdlc->ctrl.sr.cmd = HDLC_CMD_XRS;
		ग_लिखो_ctrl(bch, 1);
		hdlc->ctrl.sr.cmd = 0;
		test_and_set_bit(FLG_TRANSPARENT, &bch->Flags);
		अवरोध;
	हाल ISDN_P_B_HDLC:
		bch->state = protocol;
		hdlc->ctrl.sr.cmd  = HDLC_CMD_XRS | HDLC_CMD_RRS;
		hdlc->ctrl.sr.mode = mode | HDLC_MODE_ITF_FLG;
		ग_लिखो_ctrl(bch, 5);
		hdlc->ctrl.sr.cmd = HDLC_CMD_XRS;
		ग_लिखो_ctrl(bch, 1);
		hdlc->ctrl.sr.cmd = 0;
		test_and_set_bit(FLG_HDLC, &bch->Flags);
		अवरोध;
	शेष:
		pr_info("%s: protocol not known %x\n", fc->name, protocol);
		वापस -ENOPROTOOPT;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
hdlc_empty_fअगरo(काष्ठा bchannel *bch, पूर्णांक count)
अणु
	u32 *ptr;
	u8 *p;
	u32  val, addr;
	पूर्णांक cnt;
	काष्ठा fritzcard *fc = bch->hw;

	pr_debug("%s: %s %d\n", fc->name, __func__, count);
	अगर (test_bit(FLG_RX_OFF, &bch->Flags)) अणु
		p = शून्य;
		bch->dropcnt += count;
	पूर्ण अन्यथा अणु
		cnt = bchannel_get_rxbuf(bch, count);
		अगर (cnt < 0) अणु
			pr_warn("%s.B%d: No bufferspace for %d bytes\n",
				fc->name, bch->nr, count);
			वापस;
		पूर्ण
		p = skb_put(bch->rx_skb, count);
	पूर्ण
	ptr = (u32 *)p;
	अगर (fc->type == AVM_FRITZ_PCIV2)
		addr = fc->addr + (bch->nr == 2 ?
				   AVM_HDLC_FIFO_2 : AVM_HDLC_FIFO_1);
	अन्यथा अणु
		addr = fc->addr + CHIP_WINDOW;
		outl(bch->nr == 2 ? AVM_HDLC_2 : AVM_HDLC_1, fc->addr);
	पूर्ण
	cnt = 0;
	जबतक (cnt < count) अणु
		val = le32_to_cpu(inl(addr));
		अगर (p) अणु
			put_unaligned(val, ptr);
			ptr++;
		पूर्ण
		cnt += 4;
	पूर्ण
	अगर (p && (debug & DEBUG_HW_BFIFO)) अणु
		snम_लिखो(fc->log, LOG_SIZE, "B%1d-recv %s %d ",
			 bch->nr, fc->name, count);
		prपूर्णांक_hex_dump_bytes(fc->log, DUMP_PREFIX_OFFSET, p, count);
	पूर्ण
पूर्ण

अटल व्योम
hdlc_fill_fअगरo(काष्ठा bchannel *bch)
अणु
	काष्ठा fritzcard *fc = bch->hw;
	काष्ठा hdlc_hw *hdlc;
	पूर्णांक count, fs, cnt = 0, idx;
	bool fillempty = false;
	u8 *p;
	u32 *ptr, val, addr;

	idx = (bch->nr - 1) & 1;
	hdlc = &fc->hdlc[idx];
	fs = (fc->type == AVM_FRITZ_PCIV2) ?
		HDLC_FIFO_SIZE_V2 : HDLC_FIFO_SIZE_V1;
	अगर (!bch->tx_skb) अणु
		अगर (!test_bit(FLG_TX_EMPTY, &bch->Flags))
			वापस;
		count = fs;
		p = bch->fill;
		fillempty = true;
	पूर्ण अन्यथा अणु
		count = bch->tx_skb->len - bch->tx_idx;
		अगर (count <= 0)
			वापस;
		p = bch->tx_skb->data + bch->tx_idx;
	पूर्ण
	hdlc->ctrl.sr.cmd &= ~HDLC_CMD_XME;
	अगर (count > fs) अणु
		count = fs;
	पूर्ण अन्यथा अणु
		अगर (test_bit(FLG_HDLC, &bch->Flags))
			hdlc->ctrl.sr.cmd |= HDLC_CMD_XME;
	पूर्ण
	ptr = (u32 *)p;
	अगर (!fillempty) अणु
		pr_debug("%s.B%d: %d/%d/%d", fc->name, bch->nr, count,
			 bch->tx_idx, bch->tx_skb->len);
		bch->tx_idx += count;
	पूर्ण अन्यथा अणु
		pr_debug("%s.B%d: fillempty %d\n", fc->name, bch->nr, count);
	पूर्ण
	hdlc->ctrl.sr.xml = ((count == fs) ? 0 : count);
	अगर (fc->type == AVM_FRITZ_PCIV2) अणु
		__ग_लिखो_ctrl_pciv2(fc, hdlc, bch->nr);
		addr = fc->addr + (bch->nr == 2 ?
				   AVM_HDLC_FIFO_2 : AVM_HDLC_FIFO_1);
	पूर्ण अन्यथा अणु
		__ग_लिखो_ctrl_pci(fc, hdlc, bch->nr);
		addr = fc->addr + CHIP_WINDOW;
	पूर्ण
	अगर (fillempty) अणु
		जबतक (cnt < count) अणु
			/* all bytes the same - no worry about endian */
			outl(*ptr, addr);
			cnt += 4;
		पूर्ण
	पूर्ण अन्यथा अणु
		जबतक (cnt < count) अणु
			val = get_unaligned(ptr);
			outl(cpu_to_le32(val), addr);
			ptr++;
			cnt += 4;
		पूर्ण
	पूर्ण
	अगर ((debug & DEBUG_HW_BFIFO) && !fillempty) अणु
		snम_लिखो(fc->log, LOG_SIZE, "B%1d-send %s %d ",
			 bch->nr, fc->name, count);
		prपूर्णांक_hex_dump_bytes(fc->log, DUMP_PREFIX_OFFSET, p, count);
	पूर्ण
पूर्ण

अटल व्योम
HDLC_irq_xpr(काष्ठा bchannel *bch)
अणु
	अगर (bch->tx_skb && bch->tx_idx < bch->tx_skb->len) अणु
		hdlc_fill_fअगरo(bch);
	पूर्ण अन्यथा अणु
		dev_kमुक्त_skb(bch->tx_skb);
		अगर (get_next_bframe(bch)) अणु
			hdlc_fill_fअगरo(bch);
			test_and_clear_bit(FLG_TX_EMPTY, &bch->Flags);
		पूर्ण अन्यथा अगर (test_bit(FLG_TX_EMPTY, &bch->Flags)) अणु
			hdlc_fill_fअगरo(bch);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
HDLC_irq(काष्ठा bchannel *bch, u32 stat)
अणु
	काष्ठा fritzcard *fc = bch->hw;
	पूर्णांक		len, fs;
	u32		rmlMask;
	काष्ठा hdlc_hw	*hdlc;

	hdlc = &fc->hdlc[(bch->nr - 1) & 1];
	pr_debug("%s: ch%d stat %#x\n", fc->name, bch->nr, stat);
	अगर (fc->type == AVM_FRITZ_PCIV2) अणु
		rmlMask = HDLC_STAT_RML_MASK_V2;
		fs = HDLC_FIFO_SIZE_V2;
	पूर्ण अन्यथा अणु
		rmlMask = HDLC_STAT_RML_MASK_V1;
		fs = HDLC_FIFO_SIZE_V1;
	पूर्ण
	अगर (stat & HDLC_INT_RPR) अणु
		अगर (stat & HDLC_STAT_RDO) अणु
			pr_warn("%s: ch%d stat %x RDO\n",
				fc->name, bch->nr, stat);
			hdlc->ctrl.sr.xml = 0;
			hdlc->ctrl.sr.cmd |= HDLC_CMD_RRS;
			ग_लिखो_ctrl(bch, 1);
			hdlc->ctrl.sr.cmd &= ~HDLC_CMD_RRS;
			ग_लिखो_ctrl(bch, 1);
			अगर (bch->rx_skb)
				skb_trim(bch->rx_skb, 0);
		पूर्ण अन्यथा अणु
			len = (stat & rmlMask) >> 8;
			अगर (!len)
				len = fs;
			hdlc_empty_fअगरo(bch, len);
			अगर (!bch->rx_skb)
				जाओ handle_tx;
			अगर (test_bit(FLG_TRANSPARENT, &bch->Flags)) अणु
				recv_Bchannel(bch, 0, false);
			पूर्ण अन्यथा अगर (stat & HDLC_STAT_RME) अणु
				अगर ((stat & HDLC_STAT_CRCVFRRAB) ==
				    HDLC_STAT_CRCVFR) अणु
					recv_Bchannel(bch, 0, false);
				पूर्ण अन्यथा अणु
					pr_warn("%s: got invalid frame\n",
						fc->name);
					skb_trim(bch->rx_skb, 0);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
handle_tx:
	अगर (stat & HDLC_INT_XDU) अणु
		/* Here we lost an TX पूर्णांकerrupt, so
		 * restart transmitting the whole frame on HDLC
		 * in transparent mode we send the next data
		 */
		pr_warn("%s: ch%d stat %x XDU %s\n", fc->name, bch->nr,
			stat, bch->tx_skb ? "tx_skb" : "no tx_skb");
		अगर (bch->tx_skb && bch->tx_skb->len) अणु
			अगर (!test_bit(FLG_TRANSPARENT, &bch->Flags))
				bch->tx_idx = 0;
		पूर्ण अन्यथा अगर (test_bit(FLG_FILLEMPTY, &bch->Flags)) अणु
			test_and_set_bit(FLG_TX_EMPTY, &bch->Flags);
		पूर्ण
		hdlc->ctrl.sr.xml = 0;
		hdlc->ctrl.sr.cmd |= HDLC_CMD_XRS;
		ग_लिखो_ctrl(bch, 1);
		hdlc->ctrl.sr.cmd &= ~HDLC_CMD_XRS;
		HDLC_irq_xpr(bch);
		वापस;
	पूर्ण अन्यथा अगर (stat & HDLC_INT_XPR)
		HDLC_irq_xpr(bch);
पूर्ण

अटल अंतरभूत व्योम
HDLC_irq_मुख्य(काष्ठा fritzcard *fc)
अणु
	u32 stat;
	काष्ठा bchannel *bch;

	stat = पढ़ो_status(fc, 1);
	अगर (stat & HDLC_INT_MASK) अणु
		bch = Sel_BCS(fc, 1);
		अगर (bch)
			HDLC_irq(bch, stat);
		अन्यथा
			pr_debug("%s: spurious ch1 IRQ\n", fc->name);
	पूर्ण
	stat = पढ़ो_status(fc, 2);
	अगर (stat & HDLC_INT_MASK) अणु
		bch = Sel_BCS(fc, 2);
		अगर (bch)
			HDLC_irq(bch, stat);
		अन्यथा
			pr_debug("%s: spurious ch2 IRQ\n", fc->name);
	पूर्ण
पूर्ण

अटल irqवापस_t
avm_fritz_पूर्णांकerrupt(पूर्णांक पूर्णांकno, व्योम *dev_id)
अणु
	काष्ठा fritzcard *fc = dev_id;
	u8 val;
	u8 sval;

	spin_lock(&fc->lock);
	sval = inb(fc->addr + 2);
	pr_debug("%s: irq stat0 %x\n", fc->name, sval);
	अगर ((sval & AVM_STATUS0_IRQ_MASK) == AVM_STATUS0_IRQ_MASK) अणु
		/* shared  IRQ from other HW */
		spin_unlock(&fc->lock);
		वापस IRQ_NONE;
	पूर्ण
	fc->irqcnt++;

	अगर (!(sval & AVM_STATUS0_IRQ_ISAC)) अणु
		val = ReadISAC_V1(fc, ISAC_ISTA);
		mISDNisac_irq(&fc->isac, val);
	पूर्ण
	अगर (!(sval & AVM_STATUS0_IRQ_HDLC))
		HDLC_irq_मुख्य(fc);
	spin_unlock(&fc->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t
avm_fritzv2_पूर्णांकerrupt(पूर्णांक पूर्णांकno, व्योम *dev_id)
अणु
	काष्ठा fritzcard *fc = dev_id;
	u8 val;
	u8 sval;

	spin_lock(&fc->lock);
	sval = inb(fc->addr + 2);
	pr_debug("%s: irq stat0 %x\n", fc->name, sval);
	अगर (!(sval & AVM_STATUS0_IRQ_MASK)) अणु
		/* shared  IRQ from other HW */
		spin_unlock(&fc->lock);
		वापस IRQ_NONE;
	पूर्ण
	fc->irqcnt++;

	अगर (sval & AVM_STATUS0_IRQ_HDLC)
		HDLC_irq_मुख्य(fc);
	अगर (sval & AVM_STATUS0_IRQ_ISAC) अणु
		val = ReadISAC_V2(fc, ISACX_ISTA);
		mISDNisac_irq(&fc->isac, val);
	पूर्ण
	अगर (sval & AVM_STATUS0_IRQ_TIMER) अणु
		pr_debug("%s: timer irq\n", fc->name);
		outb(fc->ctrlreg | AVM_STATUS0_RES_TIMER, fc->addr + 2);
		udelay(1);
		outb(fc->ctrlreg, fc->addr + 2);
	पूर्ण
	spin_unlock(&fc->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक
avm_l2l1B(काष्ठा mISDNchannel *ch, काष्ठा sk_buff *skb)
अणु
	काष्ठा bchannel *bch = container_of(ch, काष्ठा bchannel, ch);
	काष्ठा fritzcard *fc = bch->hw;
	पूर्णांक ret = -EINVAL;
	काष्ठा mISDNhead *hh = mISDN_HEAD_P(skb);
	अचिन्हित दीर्घ flags;

	चयन (hh->prim) अणु
	हाल PH_DATA_REQ:
		spin_lock_irqsave(&fc->lock, flags);
		ret = bchannel_senddata(bch, skb);
		अगर (ret > 0) अणु /* direct TX */
			hdlc_fill_fअगरo(bch);
			ret = 0;
		पूर्ण
		spin_unlock_irqrestore(&fc->lock, flags);
		वापस ret;
	हाल PH_ACTIVATE_REQ:
		spin_lock_irqsave(&fc->lock, flags);
		अगर (!test_and_set_bit(FLG_ACTIVE, &bch->Flags))
			ret = modehdlc(bch, ch->protocol);
		अन्यथा
			ret = 0;
		spin_unlock_irqrestore(&fc->lock, flags);
		अगर (!ret)
			_queue_data(ch, PH_ACTIVATE_IND, MISDN_ID_ANY, 0,
				    शून्य, GFP_KERNEL);
		अवरोध;
	हाल PH_DEACTIVATE_REQ:
		spin_lock_irqsave(&fc->lock, flags);
		mISDN_clear_bchannel(bch);
		modehdlc(bch, ISDN_P_NONE);
		spin_unlock_irqrestore(&fc->lock, flags);
		_queue_data(ch, PH_DEACTIVATE_IND, MISDN_ID_ANY, 0,
			    शून्य, GFP_KERNEL);
		ret = 0;
		अवरोध;
	पूर्ण
	अगर (!ret)
		dev_kमुक्त_skb(skb);
	वापस ret;
पूर्ण

अटल व्योम
inithdlc(काष्ठा fritzcard *fc)
अणु
	modehdlc(&fc->bch[0], -1);
	modehdlc(&fc->bch[1], -1);
पूर्ण

अटल व्योम
clear_pending_hdlc_पूर्णांकs(काष्ठा fritzcard *fc)
अणु
	u32 val;

	val = पढ़ो_status(fc, 1);
	pr_debug("%s: HDLC 1 STA %x\n", fc->name, val);
	val = पढ़ो_status(fc, 2);
	pr_debug("%s: HDLC 2 STA %x\n", fc->name, val);
पूर्ण

अटल व्योम
reset_avm(काष्ठा fritzcard *fc)
अणु
	चयन (fc->type) अणु
	हाल AVM_FRITZ_PCI:
		fc->ctrlreg = AVM_STATUS0_RESET | AVM_STATUS0_DIS_TIMER;
		अवरोध;
	हाल AVM_FRITZ_PCIV2:
		fc->ctrlreg = AVM_STATUS0_RESET;
		अवरोध;
	पूर्ण
	अगर (debug & DEBUG_HW)
		pr_notice("%s: reset\n", fc->name);
	disable_hwirq(fc);
	mdelay(5);
	चयन (fc->type) अणु
	हाल AVM_FRITZ_PCI:
		fc->ctrlreg = AVM_STATUS0_DIS_TIMER | AVM_STATUS0_RES_TIMER;
		disable_hwirq(fc);
		outb(AVM_STATUS1_ENA_IOM, fc->addr + 3);
		अवरोध;
	हाल AVM_FRITZ_PCIV2:
		fc->ctrlreg = 0;
		disable_hwirq(fc);
		अवरोध;
	पूर्ण
	mdelay(1);
	अगर (debug & DEBUG_HW)
		pr_notice("%s: S0/S1 %x/%x\n", fc->name,
			  inb(fc->addr + 2), inb(fc->addr + 3));
पूर्ण

अटल पूर्णांक
init_card(काष्ठा fritzcard *fc)
अणु
	पूर्णांक		ret, cnt = 3;
	u_दीर्घ		flags;

	reset_avm(fc); /* disable IRQ */
	अगर (fc->type == AVM_FRITZ_PCIV2)
		ret = request_irq(fc->irq, avm_fritzv2_पूर्णांकerrupt,
				  IRQF_SHARED, fc->name, fc);
	अन्यथा
		ret = request_irq(fc->irq, avm_fritz_पूर्णांकerrupt,
				  IRQF_SHARED, fc->name, fc);
	अगर (ret) अणु
		pr_info("%s: couldn't get interrupt %d\n",
			fc->name, fc->irq);
		वापस ret;
	पूर्ण
	जबतक (cnt--) अणु
		spin_lock_irqsave(&fc->lock, flags);
		ret = fc->isac.init(&fc->isac);
		अगर (ret) अणु
			spin_unlock_irqrestore(&fc->lock, flags);
			pr_info("%s: ISAC init failed with %d\n",
				fc->name, ret);
			अवरोध;
		पूर्ण
		clear_pending_hdlc_पूर्णांकs(fc);
		inithdlc(fc);
		enable_hwirq(fc);
		/* RESET Receiver and Transmitter */
		अगर (fc->type == AVM_FRITZ_PCIV2) अणु
			WriteISAC_V2(fc, ISACX_MASK, 0);
			WriteISAC_V2(fc, ISACX_CMDRD, 0x41);
		पूर्ण अन्यथा अणु
			WriteISAC_V1(fc, ISAC_MASK, 0);
			WriteISAC_V1(fc, ISAC_CMDR, 0x41);
		पूर्ण
		spin_unlock_irqrestore(&fc->lock, flags);
		/* Timeout 10ms */
		msleep_पूर्णांकerruptible(10);
		अगर (debug & DEBUG_HW)
			pr_notice("%s: IRQ %d count %d\n", fc->name,
				  fc->irq, fc->irqcnt);
		अगर (!fc->irqcnt) अणु
			pr_info("%s: IRQ(%d) getting no IRQs during init %d\n",
				fc->name, fc->irq, 3 - cnt);
			reset_avm(fc);
		पूर्ण अन्यथा
			वापस 0;
	पूर्ण
	मुक्त_irq(fc->irq, fc);
	वापस -EIO;
पूर्ण

अटल पूर्णांक
channel_bctrl(काष्ठा bchannel *bch, काष्ठा mISDN_ctrl_req *cq)
अणु
	वापस mISDN_ctrl_bchannel(bch, cq);
पूर्ण

अटल पूर्णांक
avm_bctrl(काष्ठा mISDNchannel *ch, u32 cmd, व्योम *arg)
अणु
	काष्ठा bchannel *bch = container_of(ch, काष्ठा bchannel, ch);
	काष्ठा fritzcard *fc = bch->hw;
	पूर्णांक ret = -EINVAL;
	u_दीर्घ flags;

	pr_debug("%s: %s cmd:%x %p\n", fc->name, __func__, cmd, arg);
	चयन (cmd) अणु
	हाल CLOSE_CHANNEL:
		test_and_clear_bit(FLG_OPEN, &bch->Flags);
		cancel_work_sync(&bch->workq);
		spin_lock_irqsave(&fc->lock, flags);
		mISDN_clear_bchannel(bch);
		modehdlc(bch, ISDN_P_NONE);
		spin_unlock_irqrestore(&fc->lock, flags);
		ch->protocol = ISDN_P_NONE;
		ch->peer = शून्य;
		module_put(THIS_MODULE);
		ret = 0;
		अवरोध;
	हाल CONTROL_CHANNEL:
		ret = channel_bctrl(bch, arg);
		अवरोध;
	शेष:
		pr_info("%s: %s unknown prim(%x)\n", fc->name, __func__, cmd);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
channel_ctrl(काष्ठा fritzcard  *fc, काष्ठा mISDN_ctrl_req *cq)
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
		ret = fc->isac.ctrl(&fc->isac, HW_TESTLOOP, cq->channel);
		अवरोध;
	हाल MISDN_CTRL_L1_TIMER3:
		ret = fc->isac.ctrl(&fc->isac, HW_TIMER3_VALUE, cq->p1);
		अवरोध;
	शेष:
		pr_info("%s: %s unknown Op %x\n", fc->name, __func__, cq->op);
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
खोलो_bchannel(काष्ठा fritzcard *fc, काष्ठा channel_req *rq)
अणु
	काष्ठा bchannel		*bch;

	अगर (rq->adr.channel == 0 || rq->adr.channel > 2)
		वापस -EINVAL;
	अगर (rq->protocol == ISDN_P_NONE)
		वापस -EINVAL;
	bch = &fc->bch[rq->adr.channel - 1];
	अगर (test_and_set_bit(FLG_OPEN, &bch->Flags))
		वापस -EBUSY; /* b-channel can be only खोलो once */
	bch->ch.protocol = rq->protocol;
	rq->ch = &bch->ch;
	वापस 0;
पूर्ण

/*
 * device control function
 */
अटल पूर्णांक
avm_dctrl(काष्ठा mISDNchannel *ch, u32 cmd, व्योम *arg)
अणु
	काष्ठा mISDNdevice	*dev = container_of(ch, काष्ठा mISDNdevice, D);
	काष्ठा dchannel		*dch = container_of(dev, काष्ठा dchannel, dev);
	काष्ठा fritzcard	*fc = dch->hw;
	काष्ठा channel_req	*rq;
	पूर्णांक			err = 0;

	pr_debug("%s: %s cmd:%x %p\n", fc->name, __func__, cmd, arg);
	चयन (cmd) अणु
	हाल OPEN_CHANNEL:
		rq = arg;
		अगर (rq->protocol == ISDN_P_TE_S0)
			err = fc->isac.खोलो(&fc->isac, rq);
		अन्यथा
			err = खोलो_bchannel(fc, rq);
		अगर (err)
			अवरोध;
		अगर (!try_module_get(THIS_MODULE))
			pr_info("%s: cannot get module\n", fc->name);
		अवरोध;
	हाल CLOSE_CHANNEL:
		pr_debug("%s: dev(%d) close from %p\n", fc->name, dch->dev.id,
			 __builtin_वापस_address(0));
		module_put(THIS_MODULE);
		अवरोध;
	हाल CONTROL_CHANNEL:
		err = channel_ctrl(fc, arg);
		अवरोध;
	शेष:
		pr_debug("%s: %s unknown command %x\n",
			 fc->name, __func__, cmd);
		वापस -EINVAL;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक
setup_fritz(काष्ठा fritzcard *fc)
अणु
	u32 val, ver;

	अगर (!request_region(fc->addr, 32, fc->name)) अणु
		pr_info("%s: AVM config port %x-%x already in use\n",
			fc->name, fc->addr, fc->addr + 31);
		वापस -EIO;
	पूर्ण
	चयन (fc->type) अणु
	हाल AVM_FRITZ_PCI:
		val = inl(fc->addr);
		outl(AVM_HDLC_1, fc->addr + CHIP_INDEX);
		ver = inl(fc->addr + CHIP_WINDOW + HDLC_STATUS) >> 24;
		अगर (debug & DEBUG_HW) अणु
			pr_notice("%s: PCI stat %#x\n", fc->name, val);
			pr_notice("%s: PCI Class %X Rev %d\n", fc->name,
				  val & 0xff, (val >> 8) & 0xff);
			pr_notice("%s: HDLC version %x\n", fc->name, ver & 0xf);
		पूर्ण
		ASSIGN_FUNC(V1, ISAC, fc->isac);
		fc->isac.type = IPAC_TYPE_ISAC;
		अवरोध;
	हाल AVM_FRITZ_PCIV2:
		val = inl(fc->addr);
		ver = inl(fc->addr + AVM_HDLC_STATUS_1) >> 24;
		अगर (debug & DEBUG_HW) अणु
			pr_notice("%s: PCI V2 stat %#x\n", fc->name, val);
			pr_notice("%s: PCI V2 Class %X Rev %d\n", fc->name,
				  val & 0xff, (val >> 8) & 0xff);
			pr_notice("%s: HDLC version %x\n", fc->name, ver & 0xf);
		पूर्ण
		ASSIGN_FUNC(V2, ISAC, fc->isac);
		fc->isac.type = IPAC_TYPE_ISACX;
		अवरोध;
	शेष:
		release_region(fc->addr, 32);
		pr_info("%s: AVM unknown type %d\n", fc->name, fc->type);
		वापस -ENODEV;
	पूर्ण
	pr_notice("%s: %s config irq:%d base:0x%X\n", fc->name,
		  (fc->type == AVM_FRITZ_PCI) ? "AVM Fritz!CARD PCI" :
		  "AVM Fritz!CARD PCIv2", fc->irq, fc->addr);
	वापस 0;
पूर्ण

अटल व्योम
release_card(काष्ठा fritzcard *card)
अणु
	u_दीर्घ flags;

	disable_hwirq(card);
	spin_lock_irqsave(&card->lock, flags);
	modehdlc(&card->bch[0], ISDN_P_NONE);
	modehdlc(&card->bch[1], ISDN_P_NONE);
	spin_unlock_irqrestore(&card->lock, flags);
	card->isac.release(&card->isac);
	मुक्त_irq(card->irq, card);
	mISDN_मुक्तbchannel(&card->bch[1]);
	mISDN_मुक्तbchannel(&card->bch[0]);
	mISDN_unरेजिस्टर_device(&card->isac.dch.dev);
	release_region(card->addr, 32);
	pci_disable_device(card->pdev);
	pci_set_drvdata(card->pdev, शून्य);
	ग_लिखो_lock_irqsave(&card_lock, flags);
	list_del(&card->list);
	ग_लिखो_unlock_irqrestore(&card_lock, flags);
	kमुक्त(card);
	AVM_cnt--;
पूर्ण

अटल पूर्णांक
setup_instance(काष्ठा fritzcard *card)
अणु
	पूर्णांक i, err;
	अचिन्हित लघु minsize;
	u_दीर्घ flags;

	snम_लिखो(card->name, MISDN_MAX_IDLEN - 1, "AVM.%d", AVM_cnt + 1);
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
	card->isac.dch.dev.D.ctrl = avm_dctrl;
	क्रम (i = 0; i < 2; i++) अणु
		card->bch[i].nr = i + 1;
		set_channelmap(i + 1, card->isac.dch.dev.channelmap);
		अगर (AVM_FRITZ_PCIV2 == card->type)
			minsize = HDLC_FIFO_SIZE_V2;
		अन्यथा
			minsize = HDLC_FIFO_SIZE_V1;
		mISDN_initbchannel(&card->bch[i], MAX_DATA_MEM, minsize);
		card->bch[i].hw = card;
		card->bch[i].ch.send = avm_l2l1B;
		card->bch[i].ch.ctrl = avm_bctrl;
		card->bch[i].ch.nr = i + 1;
		list_add(&card->bch[i].ch.list, &card->isac.dch.dev.bchannels);
	पूर्ण
	err = setup_fritz(card);
	अगर (err)
		जाओ error;
	err = mISDN_रेजिस्टर_device(&card->isac.dch.dev, &card->pdev->dev,
				    card->name);
	अगर (err)
		जाओ error_reg;
	err = init_card(card);
	अगर (!err)  अणु
		AVM_cnt++;
		pr_notice("AVM %d cards installed DEBUG\n", AVM_cnt);
		वापस 0;
	पूर्ण
	mISDN_unरेजिस्टर_device(&card->isac.dch.dev);
error_reg:
	release_region(card->addr, 32);
error:
	card->isac.release(&card->isac);
	mISDN_मुक्तbchannel(&card->bch[1]);
	mISDN_मुक्तbchannel(&card->bch[0]);
	ग_लिखो_lock_irqsave(&card_lock, flags);
	list_del(&card->list);
	ग_लिखो_unlock_irqrestore(&card_lock, flags);
	kमुक्त(card);
	वापस err;
पूर्ण

अटल पूर्णांक
fritzpci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक err = -ENOMEM;
	काष्ठा fritzcard *card;

	card = kzalloc(माप(काष्ठा fritzcard), GFP_KERNEL);
	अगर (!card) अणु
		pr_info("No kmem for fritzcard\n");
		वापस err;
	पूर्ण
	अगर (pdev->device == PCI_DEVICE_ID_AVM_A1_V2)
		card->type = AVM_FRITZ_PCIV2;
	अन्यथा
		card->type = AVM_FRITZ_PCI;
	card->pdev = pdev;
	err = pci_enable_device(pdev);
	अगर (err) अणु
		kमुक्त(card);
		वापस err;
	पूर्ण

	pr_notice("mISDN: found adapter %s at %s\n",
		  (अक्षर *) ent->driver_data, pci_name(pdev));

	card->addr = pci_resource_start(pdev, 1);
	card->irq = pdev->irq;
	pci_set_drvdata(pdev, card);
	err = setup_instance(card);
	अगर (err)
		pci_set_drvdata(pdev, शून्य);
	वापस err;
पूर्ण

अटल व्योम
fritz_हटाओ_pci(काष्ठा pci_dev *pdev)
अणु
	काष्ठा fritzcard *card = pci_get_drvdata(pdev);

	अगर (card)
		release_card(card);
	अन्यथा
		अगर (debug)
			pr_info("%s: drvdata already removed\n", __func__);
पूर्ण

अटल स्थिर काष्ठा pci_device_id fcpci_ids[] = अणु
	अणु PCI_VENDOR_ID_AVM, PCI_DEVICE_ID_AVM_A1, PCI_ANY_ID, PCI_ANY_ID,
	  0, 0, (अचिन्हित दीर्घ) "Fritz!Card PCI"पूर्ण,
	अणु PCI_VENDOR_ID_AVM, PCI_DEVICE_ID_AVM_A1_V2, PCI_ANY_ID, PCI_ANY_ID,
	  0, 0, (अचिन्हित दीर्घ) "Fritz!Card PCI v2" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, fcpci_ids);

अटल काष्ठा pci_driver fcpci_driver = अणु
	.name = "fcpci",
	.probe = fritzpci_probe,
	.हटाओ = fritz_हटाओ_pci,
	.id_table = fcpci_ids,
पूर्ण;

अटल पूर्णांक __init AVM_init(व्योम)
अणु
	पूर्णांक err;

	pr_notice("AVM Fritz PCI driver Rev. %s\n", AVMFRITZ_REV);
	err = pci_रेजिस्टर_driver(&fcpci_driver);
	वापस err;
पूर्ण

अटल व्योम __निकास AVM_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&fcpci_driver);
पूर्ण

module_init(AVM_init);
module_निकास(AVM_cleanup);
