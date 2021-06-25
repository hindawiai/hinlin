<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * mISDNisar.c   ISAR (Siemens PSB 7110) specअगरic functions
 *
 * Author Karsten Keil (keil@isdn4linux.de)
 *
 * Copyright 2009  by Karsten Keil <keil@isdn4linux.de>
 */

/* define this to enable अटल debug messages, अगर you kernel supports
 * dynamic debugging, you should use debugfs क्रम this
 */
/* #घोषणा DEBUG */

#समावेश <linux/gfp.h>
#समावेश <linux/delay.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mISDNhw.h>
#समावेश <linux/module.h>
#समावेश "isar.h"

#घोषणा ISAR_REV	"2.1"

MODULE_AUTHOR("Karsten Keil");
MODULE_LICENSE("GPL v2");
MODULE_VERSION(ISAR_REV);

#घोषणा DEBUG_HW_FIRMWARE_FIFO	0x10000

अटल स्थिर u8 faxmodulation[] = अणु3, 24, 48, 72, 73, 74, 96, 97, 98, 121,
				   122, 145, 146पूर्ण;
#घोषणा FAXMODCNT 13

अटल व्योम isar_setup(काष्ठा isar_hw *);

अटल अंतरभूत पूर्णांक
रुकोक्रमHIA(काष्ठा isar_hw *isar, पूर्णांक समयout)
अणु
	पूर्णांक t = समयout;
	u8 val = isar->पढ़ो_reg(isar->hw, ISAR_HIA);

	जबतक ((val & 1) && t) अणु
		udelay(1);
		t--;
		val = isar->पढ़ो_reg(isar->hw, ISAR_HIA);
	पूर्ण
	pr_debug("%s: HIA after %dus\n", isar->name, समयout - t);
	वापस समयout;
पूर्ण

/*
 * send msg to ISAR mailbox
 * अगर msg is शून्य use isar->buf
 */
अटल पूर्णांक
send_mbox(काष्ठा isar_hw *isar, u8 his, u8 creg, u8 len, u8 *msg)
अणु
	अगर (!रुकोक्रमHIA(isar, 1000))
		वापस 0;
	pr_debug("send_mbox(%02x,%02x,%d)\n", his, creg, len);
	isar->ग_लिखो_reg(isar->hw, ISAR_CTRL_H, creg);
	isar->ग_लिखो_reg(isar->hw, ISAR_CTRL_L, len);
	isar->ग_लिखो_reg(isar->hw, ISAR_WADR, 0);
	अगर (!msg)
		msg = isar->buf;
	अगर (msg && len) अणु
		isar->ग_लिखो_fअगरo(isar->hw, ISAR_MBOX, msg, len);
		अगर (isar->ch[0].bch.debug & DEBUG_HW_BFIFO) अणु
			पूर्णांक l = 0;

			जबतक (l < (पूर्णांक)len) अणु
				hex_dump_to_buffer(msg + l, len - l, 32, 1,
						   isar->log, 256, 1);
				pr_debug("%s: %s %02x: %s\n", isar->name,
					 __func__, l, isar->log);
				l += 32;
			पूर्ण
		पूर्ण
	पूर्ण
	isar->ग_लिखो_reg(isar->hw, ISAR_HIS, his);
	रुकोक्रमHIA(isar, 1000);
	वापस 1;
पूर्ण

/*
 * receive message from ISAR mailbox
 * अगर msg is शून्य use isar->buf
 */
अटल व्योम
rcv_mbox(काष्ठा isar_hw *isar, u8 *msg)
अणु
	अगर (!msg)
		msg = isar->buf;
	isar->ग_लिखो_reg(isar->hw, ISAR_RADR, 0);
	अगर (msg && isar->clsb) अणु
		isar->पढ़ो_fअगरo(isar->hw, ISAR_MBOX, msg, isar->clsb);
		अगर (isar->ch[0].bch.debug & DEBUG_HW_BFIFO) अणु
			पूर्णांक l = 0;

			जबतक (l < (पूर्णांक)isar->clsb) अणु
				hex_dump_to_buffer(msg + l, isar->clsb - l, 32,
						   1, isar->log, 256, 1);
				pr_debug("%s: %s %02x: %s\n", isar->name,
					 __func__, l, isar->log);
				l += 32;
			पूर्ण
		पूर्ण
	पूर्ण
	isar->ग_लिखो_reg(isar->hw, ISAR_IIA, 0);
पूर्ण

अटल अंतरभूत व्योम
get_irq_infos(काष्ठा isar_hw *isar)
अणु
	isar->iis = isar->पढ़ो_reg(isar->hw, ISAR_IIS);
	isar->cmsb = isar->पढ़ो_reg(isar->hw, ISAR_CTRL_H);
	isar->clsb = isar->पढ़ो_reg(isar->hw, ISAR_CTRL_L);
	pr_debug("%s: rcv_mbox(%02x,%02x,%d)\n", isar->name,
		 isar->iis, isar->cmsb, isar->clsb);
पूर्ण

/*
 * poll answer message from ISAR mailbox
 * should be used only with ISAR IRQs disabled beक्रमe DSP was started
 *
 */
अटल पूर्णांक
poll_mbox(काष्ठा isar_hw *isar, पूर्णांक maxdelay)
अणु
	पूर्णांक t = maxdelay;
	u8 irq;

	irq = isar->पढ़ो_reg(isar->hw, ISAR_IRQBIT);
	जबतक (t && !(irq & ISAR_IRQSTA)) अणु
		udelay(1);
		t--;
	पूर्ण
	अगर (t)	अणु
		get_irq_infos(isar);
		rcv_mbox(isar, शून्य);
	पूर्ण
	pr_debug("%s: pulled %d bytes after %d us\n",
		 isar->name, isar->clsb, maxdelay - t);
	वापस t;
पूर्ण

अटल पूर्णांक
ISARVersion(काष्ठा isar_hw *isar)
अणु
	पूर्णांक ver;

	/* disable ISAR IRQ */
	isar->ग_लिखो_reg(isar->hw, ISAR_IRQBIT, 0);
	isar->buf[0] = ISAR_MSG_HWVER;
	isar->buf[1] = 0;
	isar->buf[2] = 1;
	अगर (!send_mbox(isar, ISAR_HIS_VNR, 0, 3, शून्य))
		वापस -1;
	अगर (!poll_mbox(isar, 1000))
		वापस -2;
	अगर (isar->iis == ISAR_IIS_VNR) अणु
		अगर (isar->clsb == 1) अणु
			ver = isar->buf[0] & 0xf;
			वापस ver;
		पूर्ण
		वापस -3;
	पूर्ण
	वापस -4;
पूर्ण

अटल पूर्णांक
load_firmware(काष्ठा isar_hw *isar, स्थिर u8 *buf, पूर्णांक size)
अणु
	u32	saved_debug = isar->ch[0].bch.debug;
	पूर्णांक	ret, cnt;
	u8	nom, noc;
	u16	left, val, *sp = (u16 *)buf;
	u8	*mp;
	u_दीर्घ	flags;

	काष्ठा अणु
		u16 sadr;
		u16 len;
		u16 d_key;
	पूर्ण blk_head;

	अगर (1 != isar->version) अणु
		pr_err("%s: ISAR wrong version %d firmware download aborted\n",
		       isar->name, isar->version);
		वापस -EINVAL;
	पूर्ण
	अगर (!(saved_debug & DEBUG_HW_FIRMWARE_FIFO))
		isar->ch[0].bch.debug &= ~DEBUG_HW_BFIFO;
	pr_debug("%s: load firmware %d words (%d bytes)\n",
		 isar->name, size / 2, size);
	cnt = 0;
	size /= 2;
	/* disable ISAR IRQ */
	spin_lock_irqsave(isar->hwlock, flags);
	isar->ग_लिखो_reg(isar->hw, ISAR_IRQBIT, 0);
	spin_unlock_irqrestore(isar->hwlock, flags);
	जबतक (cnt < size) अणु
		blk_head.sadr = le16_to_cpu(*sp++);
		blk_head.len = le16_to_cpu(*sp++);
		blk_head.d_key = le16_to_cpu(*sp++);
		cnt += 3;
		pr_debug("ISAR firmware block (%#x,%d,%#x)\n",
			 blk_head.sadr, blk_head.len, blk_head.d_key & 0xff);
		left = blk_head.len;
		अगर (cnt + left > size) अणु
			pr_info("%s: firmware error have %d need %d words\n",
				isar->name, size, cnt + left);
			ret = -EINVAL;
			जाओ reterrflg;
		पूर्ण
		spin_lock_irqsave(isar->hwlock, flags);
		अगर (!send_mbox(isar, ISAR_HIS_DKEY, blk_head.d_key & 0xff,
			       0, शून्य)) अणु
			pr_info("ISAR send_mbox dkey failed\n");
			ret = -ETIME;
			जाओ reterror;
		पूर्ण
		अगर (!poll_mbox(isar, 1000)) अणु
			pr_warn("ISAR poll_mbox dkey failed\n");
			ret = -ETIME;
			जाओ reterror;
		पूर्ण
		spin_unlock_irqrestore(isar->hwlock, flags);
		अगर ((isar->iis != ISAR_IIS_DKEY) || isar->cmsb || isar->clsb) अणु
			pr_info("ISAR wrong dkey response (%x,%x,%x)\n",
				isar->iis, isar->cmsb, isar->clsb);
			ret = 1;
			जाओ reterrflg;
		पूर्ण
		जबतक (left > 0) अणु
			अगर (left > 126)
				noc = 126;
			अन्यथा
				noc = left;
			nom = (2 * noc) + 3;
			mp  = isar->buf;
			/* the ISAR is big endian */
			*mp++ = blk_head.sadr >> 8;
			*mp++ = blk_head.sadr & 0xFF;
			left -= noc;
			cnt += noc;
			*mp++ = noc;
			pr_debug("%s: load %3d words at %04x\n", isar->name,
				 noc, blk_head.sadr);
			blk_head.sadr += noc;
			जबतक (noc) अणु
				val = le16_to_cpu(*sp++);
				*mp++ = val >> 8;
				*mp++ = val & 0xFF;
				noc--;
			पूर्ण
			spin_lock_irqsave(isar->hwlock, flags);
			अगर (!send_mbox(isar, ISAR_HIS_FIRM, 0, nom, शून्य)) अणु
				pr_info("ISAR send_mbox prog failed\n");
				ret = -ETIME;
				जाओ reterror;
			पूर्ण
			अगर (!poll_mbox(isar, 1000)) अणु
				pr_info("ISAR poll_mbox prog failed\n");
				ret = -ETIME;
				जाओ reterror;
			पूर्ण
			spin_unlock_irqrestore(isar->hwlock, flags);
			अगर ((isar->iis != ISAR_IIS_FIRM) ||
			    isar->cmsb || isar->clsb) अणु
				pr_info("ISAR wrong prog response (%x,%x,%x)\n",
					isar->iis, isar->cmsb, isar->clsb);
				ret = -EIO;
				जाओ reterrflg;
			पूर्ण
		पूर्ण
		pr_debug("%s: ISAR firmware block %d words loaded\n",
			 isar->name, blk_head.len);
	पूर्ण
	isar->ch[0].bch.debug = saved_debug;
	/* 10ms delay */
	cnt = 10;
	जबतक (cnt--)
		mdelay(1);
	isar->buf[0] = 0xff;
	isar->buf[1] = 0xfe;
	isar->bstat = 0;
	spin_lock_irqsave(isar->hwlock, flags);
	अगर (!send_mbox(isar, ISAR_HIS_STDSP, 0, 2, शून्य)) अणु
		pr_info("ISAR send_mbox start dsp failed\n");
		ret = -ETIME;
		जाओ reterror;
	पूर्ण
	अगर (!poll_mbox(isar, 1000)) अणु
		pr_info("ISAR poll_mbox start dsp failed\n");
		ret = -ETIME;
		जाओ reterror;
	पूर्ण
	अगर ((isar->iis != ISAR_IIS_STDSP) || isar->cmsb || isar->clsb) अणु
		pr_info("ISAR wrong start dsp response (%x,%x,%x)\n",
			isar->iis, isar->cmsb, isar->clsb);
		ret = -EIO;
		जाओ reterror;
	पूर्ण अन्यथा
		pr_debug("%s: ISAR start dsp success\n", isar->name);

	/* NORMAL mode entered */
	/* Enable IRQs of ISAR */
	isar->ग_लिखो_reg(isar->hw, ISAR_IRQBIT, ISAR_IRQSTA);
	spin_unlock_irqrestore(isar->hwlock, flags);
	cnt = 1000; /* max 1s */
	जबतक ((!isar->bstat) && cnt) अणु
		mdelay(1);
		cnt--;
	पूर्ण
	अगर (!cnt) अणु
		pr_info("ISAR no general status event received\n");
		ret = -ETIME;
		जाओ reterrflg;
	पूर्ण अन्यथा
		pr_debug("%s: ISAR general status event %x\n",
			 isar->name, isar->bstat);
	/* 10ms delay */
	cnt = 10;
	जबतक (cnt--)
		mdelay(1);
	isar->iis = 0;
	spin_lock_irqsave(isar->hwlock, flags);
	अगर (!send_mbox(isar, ISAR_HIS_DIAG, ISAR_CTRL_STST, 0, शून्य)) अणु
		pr_info("ISAR send_mbox self tst failed\n");
		ret = -ETIME;
		जाओ reterror;
	पूर्ण
	spin_unlock_irqrestore(isar->hwlock, flags);
	cnt = 10000; /* max 100 ms */
	जबतक ((isar->iis != ISAR_IIS_DIAG) && cnt) अणु
		udelay(10);
		cnt--;
	पूर्ण
	mdelay(1);
	अगर (!cnt) अणु
		pr_info("ISAR no self tst response\n");
		ret = -ETIME;
		जाओ reterrflg;
	पूर्ण
	अगर ((isar->cmsb == ISAR_CTRL_STST) && (isar->clsb == 1)
	    && (isar->buf[0] == 0))
		pr_debug("%s: ISAR selftest OK\n", isar->name);
	अन्यथा अणु
		pr_info("ISAR selftest not OK %x/%x/%x\n",
			isar->cmsb, isar->clsb, isar->buf[0]);
		ret = -EIO;
		जाओ reterrflg;
	पूर्ण
	spin_lock_irqsave(isar->hwlock, flags);
	isar->iis = 0;
	अगर (!send_mbox(isar, ISAR_HIS_DIAG, ISAR_CTRL_SWVER, 0, शून्य)) अणु
		pr_info("ISAR RQST SVN failed\n");
		ret = -ETIME;
		जाओ reterror;
	पूर्ण
	spin_unlock_irqrestore(isar->hwlock, flags);
	cnt = 30000; /* max 300 ms */
	जबतक ((isar->iis != ISAR_IIS_DIAG) && cnt) अणु
		udelay(10);
		cnt--;
	पूर्ण
	mdelay(1);
	अगर (!cnt) अणु
		pr_info("ISAR no SVN response\n");
		ret = -ETIME;
		जाओ reterrflg;
	पूर्ण अन्यथा अणु
		अगर ((isar->cmsb == ISAR_CTRL_SWVER) && (isar->clsb == 1)) अणु
			pr_notice("%s: ISAR software version %#x\n",
				  isar->name, isar->buf[0]);
		पूर्ण अन्यथा अणु
			pr_info("%s: ISAR wrong swver response (%x,%x)"
				" cnt(%d)\n", isar->name, isar->cmsb,
				isar->clsb, cnt);
			ret = -EIO;
			जाओ reterrflg;
		पूर्ण
	पूर्ण
	spin_lock_irqsave(isar->hwlock, flags);
	isar_setup(isar);
	spin_unlock_irqrestore(isar->hwlock, flags);
	ret = 0;
reterrflg:
	spin_lock_irqsave(isar->hwlock, flags);
reterror:
	isar->ch[0].bch.debug = saved_debug;
	अगर (ret)
		/* disable ISAR IRQ */
		isar->ग_लिखो_reg(isar->hw, ISAR_IRQBIT, 0);
	spin_unlock_irqrestore(isar->hwlock, flags);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम
deliver_status(काष्ठा isar_ch *ch, पूर्णांक status)
अणु
	pr_debug("%s: HL->LL FAXIND %x\n", ch->is->name, status);
	_queue_data(&ch->bch.ch, PH_CONTROL_IND, status, 0, शून्य, GFP_ATOMIC);
पूर्ण

अटल अंतरभूत व्योम
isar_rcv_frame(काष्ठा isar_ch *ch)
अणु
	u8	*ptr;
	पूर्णांक	maxlen;

	अगर (!ch->is->clsb) अणु
		pr_debug("%s; ISAR zero len frame\n", ch->is->name);
		ch->is->ग_लिखो_reg(ch->is->hw, ISAR_IIA, 0);
		वापस;
	पूर्ण
	अगर (test_bit(FLG_RX_OFF, &ch->bch.Flags)) अणु
		ch->bch.dropcnt += ch->is->clsb;
		ch->is->ग_लिखो_reg(ch->is->hw, ISAR_IIA, 0);
		वापस;
	पूर्ण
	चयन (ch->bch.state) अणु
	हाल ISDN_P_NONE:
		pr_debug("%s: ISAR protocol 0 spurious IIS_RDATA %x/%x/%x\n",
			 ch->is->name, ch->is->iis, ch->is->cmsb, ch->is->clsb);
		ch->is->ग_लिखो_reg(ch->is->hw, ISAR_IIA, 0);
		अवरोध;
	हाल ISDN_P_B_RAW:
	हाल ISDN_P_B_L2DTMF:
	हाल ISDN_P_B_MODEM_ASYNC:
		maxlen = bchannel_get_rxbuf(&ch->bch, ch->is->clsb);
		अगर (maxlen < 0) अणु
			pr_warn("%s.B%d: No bufferspace for %d bytes\n",
				ch->is->name, ch->bch.nr, ch->is->clsb);
			ch->is->ग_लिखो_reg(ch->is->hw, ISAR_IIA, 0);
			अवरोध;
		पूर्ण
		rcv_mbox(ch->is, skb_put(ch->bch.rx_skb, ch->is->clsb));
		recv_Bchannel(&ch->bch, 0, false);
		अवरोध;
	हाल ISDN_P_B_HDLC:
		maxlen = bchannel_get_rxbuf(&ch->bch, ch->is->clsb);
		अगर (maxlen < 0) अणु
			pr_warn("%s.B%d: No bufferspace for %d bytes\n",
				ch->is->name, ch->bch.nr, ch->is->clsb);
			ch->is->ग_लिखो_reg(ch->is->hw, ISAR_IIA, 0);
			अवरोध;
		पूर्ण
		अगर (ch->is->cmsb & HDLC_ERROR) अणु
			pr_debug("%s: ISAR frame error %x len %d\n",
				 ch->is->name, ch->is->cmsb, ch->is->clsb);
#अगर_घोषित ERROR_STATISTIC
			अगर (ch->is->cmsb & HDLC_ERR_RER)
				ch->bch.err_inv++;
			अगर (ch->is->cmsb & HDLC_ERR_CER)
				ch->bch.err_crc++;
#पूर्ण_अगर
			skb_trim(ch->bch.rx_skb, 0);
			ch->is->ग_लिखो_reg(ch->is->hw, ISAR_IIA, 0);
			अवरोध;
		पूर्ण
		अगर (ch->is->cmsb & HDLC_FSD)
			skb_trim(ch->bch.rx_skb, 0);
		ptr = skb_put(ch->bch.rx_skb, ch->is->clsb);
		rcv_mbox(ch->is, ptr);
		अगर (ch->is->cmsb & HDLC_FED) अणु
			अगर (ch->bch.rx_skb->len < 3) अणु /* last 2 are the FCS */
				pr_debug("%s: ISAR frame to short %d\n",
					 ch->is->name, ch->bch.rx_skb->len);
				skb_trim(ch->bch.rx_skb, 0);
				अवरोध;
			पूर्ण
			skb_trim(ch->bch.rx_skb, ch->bch.rx_skb->len - 2);
			recv_Bchannel(&ch->bch, 0, false);
		पूर्ण
		अवरोध;
	हाल ISDN_P_B_T30_FAX:
		अगर (ch->state != STFAX_ACTIV) अणु
			pr_debug("%s: isar_rcv_frame: not ACTIV\n",
				 ch->is->name);
			ch->is->ग_लिखो_reg(ch->is->hw, ISAR_IIA, 0);
			अगर (ch->bch.rx_skb)
				skb_trim(ch->bch.rx_skb, 0);
			अवरोध;
		पूर्ण
		अगर (!ch->bch.rx_skb) अणु
			ch->bch.rx_skb = mI_alloc_skb(ch->bch.maxlen,
						      GFP_ATOMIC);
			अगर (unlikely(!ch->bch.rx_skb)) अणु
				pr_info("%s: B receive out of memory\n",
					__func__);
				ch->is->ग_लिखो_reg(ch->is->hw, ISAR_IIA, 0);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (ch->cmd == PCTRL_CMD_FRM) अणु
			rcv_mbox(ch->is, skb_put(ch->bch.rx_skb, ch->is->clsb));
			pr_debug("%s: isar_rcv_frame: %d\n",
				 ch->is->name, ch->bch.rx_skb->len);
			अगर (ch->is->cmsb & SART_NMD) अणु /* ABORT */
				pr_debug("%s: isar_rcv_frame: no more data\n",
					 ch->is->name);
				ch->is->ग_लिखो_reg(ch->is->hw, ISAR_IIA, 0);
				send_mbox(ch->is, SET_DPS(ch->dpath) |
					  ISAR_HIS_PUMPCTRL, PCTRL_CMD_ESC,
					  0, शून्य);
				ch->state = STFAX_ESCAPE;
				/* set_skb_flag(skb, DF_NOMOREDATA); */
			पूर्ण
			recv_Bchannel(&ch->bch, 0, false);
			अगर (ch->is->cmsb & SART_NMD)
				deliver_status(ch, HW_MOD_NOCARR);
			अवरोध;
		पूर्ण
		अगर (ch->cmd != PCTRL_CMD_FRH) अणु
			pr_debug("%s: isar_rcv_frame: unknown fax mode %x\n",
				 ch->is->name, ch->cmd);
			ch->is->ग_लिखो_reg(ch->is->hw, ISAR_IIA, 0);
			अगर (ch->bch.rx_skb)
				skb_trim(ch->bch.rx_skb, 0);
			अवरोध;
		पूर्ण
		/* PCTRL_CMD_FRH */
		अगर ((ch->bch.rx_skb->len + ch->is->clsb) >
		    (ch->bch.maxlen + 2)) अणु
			pr_info("%s: %s incoming packet too large\n",
				ch->is->name, __func__);
			ch->is->ग_लिखो_reg(ch->is->hw, ISAR_IIA, 0);
			skb_trim(ch->bch.rx_skb, 0);
			अवरोध;
		पूर्ण  अन्यथा अगर (ch->is->cmsb & HDLC_ERROR) अणु
			pr_info("%s: ISAR frame error %x len %d\n",
				ch->is->name, ch->is->cmsb, ch->is->clsb);
			skb_trim(ch->bch.rx_skb, 0);
			ch->is->ग_लिखो_reg(ch->is->hw, ISAR_IIA, 0);
			अवरोध;
		पूर्ण
		अगर (ch->is->cmsb & HDLC_FSD)
			skb_trim(ch->bch.rx_skb, 0);
		ptr = skb_put(ch->bch.rx_skb, ch->is->clsb);
		rcv_mbox(ch->is, ptr);
		अगर (ch->is->cmsb & HDLC_FED) अणु
			अगर (ch->bch.rx_skb->len < 3) अणु /* last 2 are the FCS */
				pr_info("%s: ISAR frame to short %d\n",
					ch->is->name, ch->bch.rx_skb->len);
				skb_trim(ch->bch.rx_skb, 0);
				अवरोध;
			पूर्ण
			skb_trim(ch->bch.rx_skb, ch->bch.rx_skb->len - 2);
			recv_Bchannel(&ch->bch, 0, false);
		पूर्ण
		अगर (ch->is->cmsb & SART_NMD) अणु /* ABORT */
			pr_debug("%s: isar_rcv_frame: no more data\n",
				 ch->is->name);
			ch->is->ग_लिखो_reg(ch->is->hw, ISAR_IIA, 0);
			अगर (ch->bch.rx_skb)
				skb_trim(ch->bch.rx_skb, 0);
			send_mbox(ch->is, SET_DPS(ch->dpath) |
				  ISAR_HIS_PUMPCTRL, PCTRL_CMD_ESC, 0, शून्य);
			ch->state = STFAX_ESCAPE;
			deliver_status(ch, HW_MOD_NOCARR);
		पूर्ण
		अवरोध;
	शेष:
		pr_info("isar_rcv_frame protocol (%x)error\n", ch->bch.state);
		ch->is->ग_लिखो_reg(ch->is->hw, ISAR_IIA, 0);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
isar_fill_fअगरo(काष्ठा isar_ch *ch)
अणु
	पूर्णांक count;
	u8 msb;
	u8 *ptr;

	pr_debug("%s: ch%d  tx_skb %d tx_idx %d\n", ch->is->name, ch->bch.nr,
		 ch->bch.tx_skb ? ch->bch.tx_skb->len : -1, ch->bch.tx_idx);
	अगर (!(ch->is->bstat &
	      (ch->dpath == 1 ? BSTAT_RDM1 : BSTAT_RDM2)))
		वापस;
	अगर (!ch->bch.tx_skb) अणु
		अगर (!test_bit(FLG_TX_EMPTY, &ch->bch.Flags) ||
		    (ch->bch.state != ISDN_P_B_RAW))
			वापस;
		count = ch->mml;
		/* use the card buffer */
		स_रखो(ch->is->buf, ch->bch.fill[0], count);
		send_mbox(ch->is, SET_DPS(ch->dpath) | ISAR_HIS_SDATA,
			  0, count, ch->is->buf);
		वापस;
	पूर्ण
	count = ch->bch.tx_skb->len - ch->bch.tx_idx;
	अगर (count <= 0)
		वापस;
	अगर (count > ch->mml) अणु
		msb = 0;
		count = ch->mml;
	पूर्ण अन्यथा अणु
		msb = HDLC_FED;
	पूर्ण
	ptr = ch->bch.tx_skb->data + ch->bch.tx_idx;
	अगर (!ch->bch.tx_idx) अणु
		pr_debug("%s: frame start\n", ch->is->name);
		अगर ((ch->bch.state == ISDN_P_B_T30_FAX) &&
		    (ch->cmd == PCTRL_CMD_FTH)) अणु
			अगर (count > 1) अणु
				अगर ((ptr[0] == 0xff) && (ptr[1] == 0x13)) अणु
					/* last frame */
					test_and_set_bit(FLG_LASTDATA,
							 &ch->bch.Flags);
					pr_debug("%s: set LASTDATA\n",
						 ch->is->name);
					अगर (msb == HDLC_FED)
						test_and_set_bit(FLG_DLEETX,
								 &ch->bch.Flags);
				पूर्ण
			पूर्ण
		पूर्ण
		msb |= HDLC_FST;
	पूर्ण
	ch->bch.tx_idx += count;
	चयन (ch->bch.state) अणु
	हाल ISDN_P_NONE:
		pr_info("%s: wrong protocol 0\n", __func__);
		अवरोध;
	हाल ISDN_P_B_RAW:
	हाल ISDN_P_B_L2DTMF:
	हाल ISDN_P_B_MODEM_ASYNC:
		send_mbox(ch->is, SET_DPS(ch->dpath) | ISAR_HIS_SDATA,
			  0, count, ptr);
		अवरोध;
	हाल ISDN_P_B_HDLC:
		send_mbox(ch->is, SET_DPS(ch->dpath) | ISAR_HIS_SDATA,
			  msb, count, ptr);
		अवरोध;
	हाल ISDN_P_B_T30_FAX:
		अगर (ch->state != STFAX_ACTIV)
			pr_debug("%s: not ACTIV\n", ch->is->name);
		अन्यथा अगर (ch->cmd == PCTRL_CMD_FTH)
			send_mbox(ch->is, SET_DPS(ch->dpath) | ISAR_HIS_SDATA,
				  msb, count, ptr);
		अन्यथा अगर (ch->cmd == PCTRL_CMD_FTM)
			send_mbox(ch->is, SET_DPS(ch->dpath) | ISAR_HIS_SDATA,
				  0, count, ptr);
		अन्यथा
			pr_debug("%s: not FTH/FTM\n", ch->is->name);
		अवरोध;
	शेष:
		pr_info("%s: protocol(%x) error\n",
			__func__, ch->bch.state);
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा isar_ch *
sel_bch_isar(काष्ठा isar_hw *isar, u8 dpath)
अणु
	काष्ठा isar_ch	*base = &isar->ch[0];

	अगर ((!dpath) || (dpath > 2))
		वापस शून्य;
	अगर (base->dpath == dpath)
		वापस base;
	base++;
	अगर (base->dpath == dpath)
		वापस base;
	वापस शून्य;
पूर्ण

अटल व्योम
send_next(काष्ठा isar_ch *ch)
अणु
	pr_debug("%s: %s ch%d tx_skb %d tx_idx %d\n", ch->is->name, __func__,
		 ch->bch.nr, ch->bch.tx_skb ? ch->bch.tx_skb->len : -1,
		 ch->bch.tx_idx);
	अगर (ch->bch.state == ISDN_P_B_T30_FAX) अणु
		अगर (ch->cmd == PCTRL_CMD_FTH) अणु
			अगर (test_bit(FLG_LASTDATA, &ch->bch.Flags)) अणु
				pr_debug("set NMD_DATA\n");
				test_and_set_bit(FLG_NMD_DATA, &ch->bch.Flags);
			पूर्ण
		पूर्ण अन्यथा अगर (ch->cmd == PCTRL_CMD_FTM) अणु
			अगर (test_bit(FLG_DLEETX, &ch->bch.Flags)) अणु
				test_and_set_bit(FLG_LASTDATA, &ch->bch.Flags);
				test_and_set_bit(FLG_NMD_DATA, &ch->bch.Flags);
			पूर्ण
		पूर्ण
	पूर्ण
	dev_kमुक्त_skb(ch->bch.tx_skb);
	अगर (get_next_bframe(&ch->bch)) अणु
		isar_fill_fअगरo(ch);
		test_and_clear_bit(FLG_TX_EMPTY, &ch->bch.Flags);
	पूर्ण अन्यथा अगर (test_bit(FLG_TX_EMPTY, &ch->bch.Flags)) अणु
		isar_fill_fअगरo(ch);
	पूर्ण अन्यथा अणु
		अगर (test_and_clear_bit(FLG_DLEETX, &ch->bch.Flags)) अणु
			अगर (test_and_clear_bit(FLG_LASTDATA,
					       &ch->bch.Flags)) अणु
				अगर (test_and_clear_bit(FLG_NMD_DATA,
						       &ch->bch.Flags)) अणु
					u8 zd = 0;
					send_mbox(ch->is, SET_DPS(ch->dpath) |
						  ISAR_HIS_SDATA, 0x01, 1, &zd);
				पूर्ण
				test_and_set_bit(FLG_LL_OK, &ch->bch.Flags);
			पूर्ण अन्यथा अणु
				deliver_status(ch, HW_MOD_CONNECT);
			पूर्ण
		पूर्ण अन्यथा अगर (test_bit(FLG_FILLEMPTY, &ch->bch.Flags)) अणु
			test_and_set_bit(FLG_TX_EMPTY, &ch->bch.Flags);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
check_send(काष्ठा isar_hw *isar, u8 rdm)
अणु
	काष्ठा isar_ch	*ch;

	pr_debug("%s: rdm %x\n", isar->name, rdm);
	अगर (rdm & BSTAT_RDM1) अणु
		ch = sel_bch_isar(isar, 1);
		अगर (ch && test_bit(FLG_ACTIVE, &ch->bch.Flags)) अणु
			अगर (ch->bch.tx_skb && (ch->bch.tx_skb->len >
					       ch->bch.tx_idx))
				isar_fill_fअगरo(ch);
			अन्यथा
				send_next(ch);
		पूर्ण
	पूर्ण
	अगर (rdm & BSTAT_RDM2) अणु
		ch = sel_bch_isar(isar, 2);
		अगर (ch && test_bit(FLG_ACTIVE, &ch->bch.Flags)) अणु
			अगर (ch->bch.tx_skb && (ch->bch.tx_skb->len >
					       ch->bch.tx_idx))
				isar_fill_fअगरo(ch);
			अन्यथा
				send_next(ch);
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *dmril[] = अणु"NO SPEED", "1200/75", "NODEF2", "75/1200", "NODEF4",
		       "300", "600", "1200", "2400", "4800", "7200",
		       "9600nt", "9600t", "12000", "14400", "WRONG"पूर्ण;
अटल स्थिर अक्षर *dmrim[] = अणु"NO MOD", "NO DEF", "V32/V32b", "V22", "V21",
		       "Bell103", "V23", "Bell202", "V17", "V29", "V27ter"पूर्ण;

अटल व्योम
isar_pump_status_rsp(काष्ठा isar_ch *ch) अणु
	u8 ril = ch->is->buf[0];
	u8 rim;

	अगर (!test_and_clear_bit(ISAR_RATE_REQ, &ch->is->Flags))
		वापस;
	अगर (ril > 14) अणु
		pr_info("%s: wrong pstrsp ril=%d\n", ch->is->name, ril);
		ril = 15;
	पूर्ण
	चयन (ch->is->buf[1]) अणु
	हाल 0:
		rim = 0;
		अवरोध;
	हाल 0x20:
		rim = 2;
		अवरोध;
	हाल 0x40:
		rim = 3;
		अवरोध;
	हाल 0x41:
		rim = 4;
		अवरोध;
	हाल 0x51:
		rim = 5;
		अवरोध;
	हाल 0x61:
		rim = 6;
		अवरोध;
	हाल 0x71:
		rim = 7;
		अवरोध;
	हाल 0x82:
		rim = 8;
		अवरोध;
	हाल 0x92:
		rim = 9;
		अवरोध;
	हाल 0xa2:
		rim = 10;
		अवरोध;
	शेष:
		rim = 1;
		अवरोध;
	पूर्ण
	प्र_लिखो(ch->conmsg, "%s %s", dmril[ril], dmrim[rim]);
	pr_debug("%s: pump strsp %s\n", ch->is->name, ch->conmsg);
पूर्ण

अटल व्योम
isar_pump_statev_modem(काष्ठा isar_ch *ch, u8 devt) अणु
	u8 dps = SET_DPS(ch->dpath);

	चयन (devt) अणु
	हाल PSEV_10MS_TIMER:
		pr_debug("%s: pump stev TIMER\n", ch->is->name);
		अवरोध;
	हाल PSEV_CON_ON:
		pr_debug("%s: pump stev CONNECT\n", ch->is->name);
		deliver_status(ch, HW_MOD_CONNECT);
		अवरोध;
	हाल PSEV_CON_OFF:
		pr_debug("%s: pump stev NO CONNECT\n", ch->is->name);
		send_mbox(ch->is, dps | ISAR_HIS_PSTREQ, 0, 0, शून्य);
		deliver_status(ch, HW_MOD_NOCARR);
		अवरोध;
	हाल PSEV_V24_OFF:
		pr_debug("%s: pump stev V24 OFF\n", ch->is->name);
		अवरोध;
	हाल PSEV_CTS_ON:
		pr_debug("%s: pump stev CTS ON\n", ch->is->name);
		अवरोध;
	हाल PSEV_CTS_OFF:
		pr_debug("%s pump stev CTS OFF\n", ch->is->name);
		अवरोध;
	हाल PSEV_DCD_ON:
		pr_debug("%s: pump stev CARRIER ON\n", ch->is->name);
		test_and_set_bit(ISAR_RATE_REQ, &ch->is->Flags);
		send_mbox(ch->is, dps | ISAR_HIS_PSTREQ, 0, 0, शून्य);
		अवरोध;
	हाल PSEV_DCD_OFF:
		pr_debug("%s: pump stev CARRIER OFF\n", ch->is->name);
		अवरोध;
	हाल PSEV_DSR_ON:
		pr_debug("%s: pump stev DSR ON\n", ch->is->name);
		अवरोध;
	हाल PSEV_DSR_OFF:
		pr_debug("%s: pump stev DSR_OFF\n", ch->is->name);
		अवरोध;
	हाल PSEV_REM_RET:
		pr_debug("%s: pump stev REMOTE RETRAIN\n", ch->is->name);
		अवरोध;
	हाल PSEV_REM_REN:
		pr_debug("%s: pump stev REMOTE RENEGOTIATE\n", ch->is->name);
		अवरोध;
	हाल PSEV_GSTN_CLR:
		pr_debug("%s: pump stev GSTN CLEAR\n", ch->is->name);
		अवरोध;
	शेष:
		pr_info("u%s: unknown pump stev %x\n", ch->is->name, devt);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
isar_pump_statev_fax(काष्ठा isar_ch *ch, u8 devt) अणु
	u8 dps = SET_DPS(ch->dpath);
	u8 p1;

	चयन (devt) अणु
	हाल PSEV_10MS_TIMER:
		pr_debug("%s: pump stev TIMER\n", ch->is->name);
		अवरोध;
	हाल PSEV_RSP_READY:
		pr_debug("%s: pump stev RSP_READY\n", ch->is->name);
		ch->state = STFAX_READY;
		deliver_status(ch, HW_MOD_READY);
#अगर_घोषित AUTOCON
		अगर (test_bit(BC_FLG_ORIG, &ch->bch.Flags))
			isar_pump_cmd(bch, HW_MOD_FRH, 3);
		अन्यथा
			isar_pump_cmd(bch, HW_MOD_FTH, 3);
#पूर्ण_अगर
		अवरोध;
	हाल PSEV_LINE_TX_H:
		अगर (ch->state == STFAX_LINE) अणु
			pr_debug("%s: pump stev LINE_TX_H\n", ch->is->name);
			ch->state = STFAX_CONT;
			send_mbox(ch->is, dps | ISAR_HIS_PUMPCTRL,
				  PCTRL_CMD_CONT, 0, शून्य);
		पूर्ण अन्यथा अणु
			pr_debug("%s: pump stev LINE_TX_H wrong st %x\n",
				 ch->is->name, ch->state);
		पूर्ण
		अवरोध;
	हाल PSEV_LINE_RX_H:
		अगर (ch->state == STFAX_LINE) अणु
			pr_debug("%s: pump stev LINE_RX_H\n", ch->is->name);
			ch->state = STFAX_CONT;
			send_mbox(ch->is, dps | ISAR_HIS_PUMPCTRL,
				  PCTRL_CMD_CONT, 0, शून्य);
		पूर्ण अन्यथा अणु
			pr_debug("%s: pump stev LINE_RX_H wrong st %x\n",
				 ch->is->name, ch->state);
		पूर्ण
		अवरोध;
	हाल PSEV_LINE_TX_B:
		अगर (ch->state == STFAX_LINE) अणु
			pr_debug("%s: pump stev LINE_TX_B\n", ch->is->name);
			ch->state = STFAX_CONT;
			send_mbox(ch->is, dps | ISAR_HIS_PUMPCTRL,
				  PCTRL_CMD_CONT, 0, शून्य);
		पूर्ण अन्यथा अणु
			pr_debug("%s: pump stev LINE_TX_B wrong st %x\n",
				 ch->is->name, ch->state);
		पूर्ण
		अवरोध;
	हाल PSEV_LINE_RX_B:
		अगर (ch->state == STFAX_LINE) अणु
			pr_debug("%s: pump stev LINE_RX_B\n", ch->is->name);
			ch->state = STFAX_CONT;
			send_mbox(ch->is, dps | ISAR_HIS_PUMPCTRL,
				  PCTRL_CMD_CONT, 0, शून्य);
		पूर्ण अन्यथा अणु
			pr_debug("%s: pump stev LINE_RX_B wrong st %x\n",
				 ch->is->name, ch->state);
		पूर्ण
		अवरोध;
	हाल PSEV_RSP_CONN:
		अगर (ch->state == STFAX_CONT) अणु
			pr_debug("%s: pump stev RSP_CONN\n", ch->is->name);
			ch->state = STFAX_ACTIV;
			test_and_set_bit(ISAR_RATE_REQ, &ch->is->Flags);
			send_mbox(ch->is, dps | ISAR_HIS_PSTREQ, 0, 0, शून्य);
			अगर (ch->cmd == PCTRL_CMD_FTH) अणु
				पूर्णांक delay = (ch->mod == 3) ? 1000 : 200;
				/* 1s (200 ms) Flags beक्रमe data */
				अगर (test_and_set_bit(FLG_FTI_RUN,
						     &ch->bch.Flags))
					del_समयr(&ch->fसमयr);
				ch->fसमयr.expires =
					jअगरfies + ((delay * HZ) / 1000);
				test_and_set_bit(FLG_LL_CONN,
						 &ch->bch.Flags);
				add_समयr(&ch->fसमयr);
			पूर्ण अन्यथा अणु
				deliver_status(ch, HW_MOD_CONNECT);
			पूर्ण
		पूर्ण अन्यथा अणु
			pr_debug("%s: pump stev RSP_CONN wrong st %x\n",
				 ch->is->name, ch->state);
		पूर्ण
		अवरोध;
	हाल PSEV_FLAGS_DET:
		pr_debug("%s: pump stev FLAGS_DET\n", ch->is->name);
		अवरोध;
	हाल PSEV_RSP_DISC:
		pr_debug("%s: pump stev RSP_DISC state(%d)\n",
			 ch->is->name, ch->state);
		अगर (ch->state == STFAX_ESCAPE) अणु
			p1 = 5;
			चयन (ch->newcmd) अणु
			हाल 0:
				ch->state = STFAX_READY;
				अवरोध;
			हाल PCTRL_CMD_FTM:
				p1 = 2;
				fallthrough;
			हाल PCTRL_CMD_FTH:
				send_mbox(ch->is, dps | ISAR_HIS_PUMPCTRL,
					  PCTRL_CMD_SILON, 1, &p1);
				ch->state = STFAX_SILDET;
				अवरोध;
			हाल PCTRL_CMD_FRH:
			हाल PCTRL_CMD_FRM:
				ch->mod = ch->newmod;
				p1 = ch->newmod;
				ch->newmod = 0;
				ch->cmd = ch->newcmd;
				ch->newcmd = 0;
				send_mbox(ch->is, dps | ISAR_HIS_PUMPCTRL,
					  ch->cmd, 1, &p1);
				ch->state = STFAX_LINE;
				ch->try_mod = 3;
				अवरोध;
			शेष:
				pr_debug("%s: RSP_DISC unknown newcmd %x\n",
					 ch->is->name, ch->newcmd);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (ch->state == STFAX_ACTIV) अणु
			अगर (test_and_clear_bit(FLG_LL_OK, &ch->bch.Flags))
				deliver_status(ch, HW_MOD_OK);
			अन्यथा अगर (ch->cmd == PCTRL_CMD_FRM)
				deliver_status(ch, HW_MOD_NOCARR);
			अन्यथा
				deliver_status(ch, HW_MOD_FCERROR);
			ch->state = STFAX_READY;
		पूर्ण अन्यथा अगर (ch->state != STFAX_SILDET) अणु
			/* ignore in STFAX_SILDET */
			ch->state = STFAX_READY;
			deliver_status(ch, HW_MOD_FCERROR);
		पूर्ण
		अवरोध;
	हाल PSEV_RSP_SILDET:
		pr_debug("%s: pump stev RSP_SILDET\n", ch->is->name);
		अगर (ch->state == STFAX_SILDET) अणु
			ch->mod = ch->newmod;
			p1 = ch->newmod;
			ch->newmod = 0;
			ch->cmd = ch->newcmd;
			ch->newcmd = 0;
			send_mbox(ch->is, dps | ISAR_HIS_PUMPCTRL,
				  ch->cmd, 1, &p1);
			ch->state = STFAX_LINE;
			ch->try_mod = 3;
		पूर्ण
		अवरोध;
	हाल PSEV_RSP_SILOFF:
		pr_debug("%s: pump stev RSP_SILOFF\n", ch->is->name);
		अवरोध;
	हाल PSEV_RSP_FCERR:
		अगर (ch->state == STFAX_LINE) अणु
			pr_debug("%s: pump stev RSP_FCERR try %d\n",
				 ch->is->name, ch->try_mod);
			अगर (ch->try_mod--) अणु
				send_mbox(ch->is, dps | ISAR_HIS_PUMPCTRL,
					  ch->cmd, 1, &ch->mod);
				अवरोध;
			पूर्ण
		पूर्ण
		pr_debug("%s: pump stev RSP_FCERR\n", ch->is->name);
		ch->state = STFAX_ESCAPE;
		send_mbox(ch->is, dps | ISAR_HIS_PUMPCTRL, PCTRL_CMD_ESC,
			  0, शून्य);
		deliver_status(ch, HW_MOD_FCERROR);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम
mISDNisar_irq(काष्ठा isar_hw *isar)
अणु
	काष्ठा isar_ch *ch;

	get_irq_infos(isar);
	चयन (isar->iis & ISAR_IIS_MSCMSD) अणु
	हाल ISAR_IIS_RDATA:
		ch = sel_bch_isar(isar, isar->iis >> 6);
		अगर (ch)
			isar_rcv_frame(ch);
		अन्यथा अणु
			pr_debug("%s: ISAR spurious IIS_RDATA %x/%x/%x\n",
				 isar->name, isar->iis, isar->cmsb,
				 isar->clsb);
			isar->ग_लिखो_reg(isar->hw, ISAR_IIA, 0);
		पूर्ण
		अवरोध;
	हाल ISAR_IIS_GSTEV:
		isar->ग_लिखो_reg(isar->hw, ISAR_IIA, 0);
		isar->bstat |= isar->cmsb;
		check_send(isar, isar->cmsb);
		अवरोध;
	हाल ISAR_IIS_BSTEV:
#अगर_घोषित ERROR_STATISTIC
		ch = sel_bch_isar(isar, isar->iis >> 6);
		अगर (ch) अणु
			अगर (isar->cmsb == BSTEV_TBO)
				ch->bch.err_tx++;
			अगर (isar->cmsb == BSTEV_RBO)
				ch->bch.err_rकरो++;
		पूर्ण
#पूर्ण_अगर
		pr_debug("%s: Buffer STEV dpath%d msb(%x)\n",
			 isar->name, isar->iis >> 6, isar->cmsb);
		isar->ग_लिखो_reg(isar->hw, ISAR_IIA, 0);
		अवरोध;
	हाल ISAR_IIS_PSTEV:
		ch = sel_bch_isar(isar, isar->iis >> 6);
		अगर (ch) अणु
			rcv_mbox(isar, शून्य);
			अगर (ch->bch.state == ISDN_P_B_MODEM_ASYNC)
				isar_pump_statev_modem(ch, isar->cmsb);
			अन्यथा अगर (ch->bch.state == ISDN_P_B_T30_FAX)
				isar_pump_statev_fax(ch, isar->cmsb);
			अन्यथा अगर (ch->bch.state == ISDN_P_B_RAW) अणु
				पूर्णांक	tt;
				tt = isar->cmsb | 0x30;
				अगर (tt == 0x3e)
					tt = '*';
				अन्यथा अगर (tt == 0x3f)
					tt = '#';
				अन्यथा अगर (tt > '9')
					tt += 7;
				tt |= DTMF_TONE_VAL;
				_queue_data(&ch->bch.ch, PH_CONTROL_IND,
					    MISDN_ID_ANY, माप(tt), &tt,
					    GFP_ATOMIC);
			पूर्ण अन्यथा
				pr_debug("%s: ISAR IIS_PSTEV pm %d sta %x\n",
					 isar->name, ch->bch.state,
					 isar->cmsb);
		पूर्ण अन्यथा अणु
			pr_debug("%s: ISAR spurious IIS_PSTEV %x/%x/%x\n",
				 isar->name, isar->iis, isar->cmsb,
				 isar->clsb);
			isar->ग_लिखो_reg(isar->hw, ISAR_IIA, 0);
		पूर्ण
		अवरोध;
	हाल ISAR_IIS_PSTRSP:
		ch = sel_bch_isar(isar, isar->iis >> 6);
		अगर (ch) अणु
			rcv_mbox(isar, शून्य);
			isar_pump_status_rsp(ch);
		पूर्ण अन्यथा अणु
			pr_debug("%s: ISAR spurious IIS_PSTRSP %x/%x/%x\n",
				 isar->name, isar->iis, isar->cmsb,
				 isar->clsb);
			isar->ग_लिखो_reg(isar->hw, ISAR_IIA, 0);
		पूर्ण
		अवरोध;
	हाल ISAR_IIS_DIAG:
	हाल ISAR_IIS_BSTRSP:
	हाल ISAR_IIS_IOM2RSP:
		rcv_mbox(isar, शून्य);
		अवरोध;
	हाल ISAR_IIS_INVMSG:
		rcv_mbox(isar, शून्य);
		pr_debug("%s: invalid msg his:%x\n", isar->name, isar->cmsb);
		अवरोध;
	शेष:
		rcv_mbox(isar, शून्य);
		pr_debug("%s: unhandled msg iis(%x) ctrl(%x/%x)\n",
			 isar->name, isar->iis, isar->cmsb, isar->clsb);
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(mISDNisar_irq);

अटल व्योम
fसमयr_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा isar_ch *ch = from_समयr(ch, t, fसमयr);

	pr_debug("%s: ftimer flags %lx\n", ch->is->name, ch->bch.Flags);
	test_and_clear_bit(FLG_FTI_RUN, &ch->bch.Flags);
	अगर (test_and_clear_bit(FLG_LL_CONN, &ch->bch.Flags))
		deliver_status(ch, HW_MOD_CONNECT);
पूर्ण

अटल व्योम
setup_pump(काष्ठा isar_ch *ch) अणु
	u8 dps = SET_DPS(ch->dpath);
	u8 ctrl, param[6];

	चयन (ch->bch.state) अणु
	हाल ISDN_P_NONE:
	हाल ISDN_P_B_RAW:
	हाल ISDN_P_B_HDLC:
		send_mbox(ch->is, dps | ISAR_HIS_PUMPCFG, PMOD_BYPASS, 0, शून्य);
		अवरोध;
	हाल ISDN_P_B_L2DTMF:
		अगर (test_bit(FLG_DTMFSEND, &ch->bch.Flags)) अणु
			param[0] = 5; /* TOA 5 db */
			send_mbox(ch->is, dps | ISAR_HIS_PUMPCFG,
				  PMOD_DTMF_TRANS, 1, param);
		पूर्ण अन्यथा अणु
			param[0] = 40; /* REL -46 dbm */
			send_mbox(ch->is, dps | ISAR_HIS_PUMPCFG,
				  PMOD_DTMF, 1, param);
		पूर्ण
		fallthrough;
	हाल ISDN_P_B_MODEM_ASYNC:
		ctrl = PMOD_DATAMODEM;
		अगर (test_bit(FLG_ORIGIN, &ch->bch.Flags)) अणु
			ctrl |= PCTRL_ORIG;
			param[5] = PV32P6_CTN;
		पूर्ण अन्यथा अणु
			param[5] = PV32P6_ATN;
		पूर्ण
		param[0] = 6; /* 6 db */
		param[1] = PV32P2_V23R | PV32P2_V22A | PV32P2_V22B |
			PV32P2_V22C | PV32P2_V21 | PV32P2_BEL;
		param[2] = PV32P3_AMOD | PV32P3_V32B | PV32P3_V23B;
		param[3] = PV32P4_UT144;
		param[4] = PV32P5_UT144;
		send_mbox(ch->is, dps | ISAR_HIS_PUMPCFG, ctrl, 6, param);
		अवरोध;
	हाल ISDN_P_B_T30_FAX:
		ctrl = PMOD_FAX;
		अगर (test_bit(FLG_ORIGIN, &ch->bch.Flags)) अणु
			ctrl |= PCTRL_ORIG;
			param[1] = PFAXP2_CTN;
		पूर्ण अन्यथा अणु
			param[1] = PFAXP2_ATN;
		पूर्ण
		param[0] = 6; /* 6 db */
		send_mbox(ch->is, dps | ISAR_HIS_PUMPCFG, ctrl, 2, param);
		ch->state = STFAX_शून्य;
		ch->newcmd = 0;
		ch->newmod = 0;
		test_and_set_bit(FLG_FTI_RUN, &ch->bch.Flags);
		अवरोध;
	पूर्ण
	udelay(1000);
	send_mbox(ch->is, dps | ISAR_HIS_PSTREQ, 0, 0, शून्य);
	udelay(1000);
पूर्ण

अटल व्योम
setup_sart(काष्ठा isar_ch *ch) अणु
	u8 dps = SET_DPS(ch->dpath);
	u8 ctrl, param[2] = अणु0, 0पूर्ण;

	चयन (ch->bch.state) अणु
	हाल ISDN_P_NONE:
		send_mbox(ch->is, dps | ISAR_HIS_SARTCFG, SMODE_DISABLE,
			  0, शून्य);
		अवरोध;
	हाल ISDN_P_B_RAW:
	हाल ISDN_P_B_L2DTMF:
		send_mbox(ch->is, dps | ISAR_HIS_SARTCFG, SMODE_BINARY,
			  2, param);
		अवरोध;
	हाल ISDN_P_B_HDLC:
	हाल ISDN_P_B_T30_FAX:
		send_mbox(ch->is, dps | ISAR_HIS_SARTCFG, SMODE_HDLC,
			  1, param);
		अवरोध;
	हाल ISDN_P_B_MODEM_ASYNC:
		ctrl = SMODE_V14 | SCTRL_HDMC_BOTH;
		param[0] = S_P1_CHS_8;
		param[1] = S_P2_BFT_DEF;
		send_mbox(ch->is, dps | ISAR_HIS_SARTCFG, ctrl, 2, param);
		अवरोध;
	पूर्ण
	udelay(1000);
	send_mbox(ch->is, dps | ISAR_HIS_BSTREQ, 0, 0, शून्य);
	udelay(1000);
पूर्ण

अटल व्योम
setup_iom2(काष्ठा isar_ch *ch) अणु
	u8 dps = SET_DPS(ch->dpath);
	u8 cmsb = IOM_CTRL_ENA, msg[5] = अणुIOM_P1_TXD, 0, 0, 0, 0पूर्ण;

	अगर (ch->bch.nr == 2) अणु
		msg[1] = 1;
		msg[3] = 1;
	पूर्ण
	चयन (ch->bch.state) अणु
	हाल ISDN_P_NONE:
		cmsb = 0;
		/* dummy slot */
		msg[1] = ch->dpath + 2;
		msg[3] = ch->dpath + 2;
		अवरोध;
	हाल ISDN_P_B_RAW:
	हाल ISDN_P_B_HDLC:
		अवरोध;
	हाल ISDN_P_B_MODEM_ASYNC:
	हाल ISDN_P_B_T30_FAX:
		cmsb |= IOM_CTRL_RCV;
		fallthrough;
	हाल ISDN_P_B_L2DTMF:
		अगर (test_bit(FLG_DTMFSEND, &ch->bch.Flags))
			cmsb |= IOM_CTRL_RCV;
		cmsb |= IOM_CTRL_ALAW;
		अवरोध;
	पूर्ण
	send_mbox(ch->is, dps | ISAR_HIS_IOM2CFG, cmsb, 5, msg);
	udelay(1000);
	send_mbox(ch->is, dps | ISAR_HIS_IOM2REQ, 0, 0, शून्य);
	udelay(1000);
पूर्ण

अटल पूर्णांक
modeisar(काष्ठा isar_ch *ch, u32 bprotocol)
अणु
	/* Here we are selecting the best datapath क्रम requested protocol */
	अगर (ch->bch.state == ISDN_P_NONE) अणु /* New Setup */
		चयन (bprotocol) अणु
		हाल ISDN_P_NONE: /* init */
			अगर (!ch->dpath)
				/* no init क्रम dpath 0 */
				वापस 0;
			test_and_clear_bit(FLG_HDLC, &ch->bch.Flags);
			test_and_clear_bit(FLG_TRANSPARENT, &ch->bch.Flags);
			अवरोध;
		हाल ISDN_P_B_RAW:
		हाल ISDN_P_B_HDLC:
			/* best is datapath 2 */
			अगर (!test_and_set_bit(ISAR_DP2_USE, &ch->is->Flags))
				ch->dpath = 2;
			अन्यथा अगर (!test_and_set_bit(ISAR_DP1_USE,
						   &ch->is->Flags))
				ch->dpath = 1;
			अन्यथा अणु
				pr_info("modeisar both paths in use\n");
				वापस -EBUSY;
			पूर्ण
			अगर (bprotocol == ISDN_P_B_HDLC)
				test_and_set_bit(FLG_HDLC, &ch->bch.Flags);
			अन्यथा
				test_and_set_bit(FLG_TRANSPARENT,
						 &ch->bch.Flags);
			अवरोध;
		हाल ISDN_P_B_MODEM_ASYNC:
		हाल ISDN_P_B_T30_FAX:
		हाल ISDN_P_B_L2DTMF:
			/* only datapath 1 */
			अगर (!test_and_set_bit(ISAR_DP1_USE, &ch->is->Flags))
				ch->dpath = 1;
			अन्यथा अणु
				pr_info("%s: ISAR modeisar analog functions"
					"only with DP1\n", ch->is->name);
				वापस -EBUSY;
			पूर्ण
			अवरोध;
		शेष:
			pr_info("%s: protocol not known %x\n", ch->is->name,
				bprotocol);
			वापस -ENOPROTOOPT;
		पूर्ण
	पूर्ण
	pr_debug("%s: ISAR ch%d dp%d protocol %x->%x\n", ch->is->name,
		 ch->bch.nr, ch->dpath, ch->bch.state, bprotocol);
	ch->bch.state = bprotocol;
	setup_pump(ch);
	setup_iom2(ch);
	setup_sart(ch);
	अगर (ch->bch.state == ISDN_P_NONE) अणु
		/* Clear resources */
		अगर (ch->dpath == 1)
			test_and_clear_bit(ISAR_DP1_USE, &ch->is->Flags);
		अन्यथा अगर (ch->dpath == 2)
			test_and_clear_bit(ISAR_DP2_USE, &ch->is->Flags);
		ch->dpath = 0;
		ch->is->ctrl(ch->is->hw, HW_DEACT_IND, ch->bch.nr);
	पूर्ण अन्यथा
		ch->is->ctrl(ch->is->hw, HW_ACTIVATE_IND, ch->bch.nr);
	वापस 0;
पूर्ण

अटल व्योम
isar_pump_cmd(काष्ठा isar_ch *ch, u32 cmd, u8 para)
अणु
	u8 dps = SET_DPS(ch->dpath);
	u8 ctrl = 0, nom = 0, p1 = 0;

	pr_debug("%s: isar_pump_cmd %x/%x state(%x)\n",
		 ch->is->name, cmd, para, ch->bch.state);
	चयन (cmd) अणु
	हाल HW_MOD_FTM:
		अगर (ch->state == STFAX_READY) अणु
			p1 = para;
			ctrl = PCTRL_CMD_FTM;
			nom = 1;
			ch->state = STFAX_LINE;
			ch->cmd = ctrl;
			ch->mod = para;
			ch->newmod = 0;
			ch->newcmd = 0;
			ch->try_mod = 3;
		पूर्ण अन्यथा अगर ((ch->state == STFAX_ACTIV) &&
			   (ch->cmd == PCTRL_CMD_FTM) && (ch->mod == para))
			deliver_status(ch, HW_MOD_CONNECT);
		अन्यथा अणु
			ch->newmod = para;
			ch->newcmd = PCTRL_CMD_FTM;
			nom = 0;
			ctrl = PCTRL_CMD_ESC;
			ch->state = STFAX_ESCAPE;
		पूर्ण
		अवरोध;
	हाल HW_MOD_FTH:
		अगर (ch->state == STFAX_READY) अणु
			p1 = para;
			ctrl = PCTRL_CMD_FTH;
			nom = 1;
			ch->state = STFAX_LINE;
			ch->cmd = ctrl;
			ch->mod = para;
			ch->newmod = 0;
			ch->newcmd = 0;
			ch->try_mod = 3;
		पूर्ण अन्यथा अगर ((ch->state == STFAX_ACTIV) &&
			   (ch->cmd == PCTRL_CMD_FTH) && (ch->mod == para))
			deliver_status(ch, HW_MOD_CONNECT);
		अन्यथा अणु
			ch->newmod = para;
			ch->newcmd = PCTRL_CMD_FTH;
			nom = 0;
			ctrl = PCTRL_CMD_ESC;
			ch->state = STFAX_ESCAPE;
		पूर्ण
		अवरोध;
	हाल HW_MOD_FRM:
		अगर (ch->state == STFAX_READY) अणु
			p1 = para;
			ctrl = PCTRL_CMD_FRM;
			nom = 1;
			ch->state = STFAX_LINE;
			ch->cmd = ctrl;
			ch->mod = para;
			ch->newmod = 0;
			ch->newcmd = 0;
			ch->try_mod = 3;
		पूर्ण अन्यथा अगर ((ch->state == STFAX_ACTIV) &&
			   (ch->cmd == PCTRL_CMD_FRM) && (ch->mod == para))
			deliver_status(ch, HW_MOD_CONNECT);
		अन्यथा अणु
			ch->newmod = para;
			ch->newcmd = PCTRL_CMD_FRM;
			nom = 0;
			ctrl = PCTRL_CMD_ESC;
			ch->state = STFAX_ESCAPE;
		पूर्ण
		अवरोध;
	हाल HW_MOD_FRH:
		अगर (ch->state == STFAX_READY) अणु
			p1 = para;
			ctrl = PCTRL_CMD_FRH;
			nom = 1;
			ch->state = STFAX_LINE;
			ch->cmd = ctrl;
			ch->mod = para;
			ch->newmod = 0;
			ch->newcmd = 0;
			ch->try_mod = 3;
		पूर्ण अन्यथा अगर ((ch->state == STFAX_ACTIV) &&
			   (ch->cmd == PCTRL_CMD_FRH) && (ch->mod == para))
			deliver_status(ch, HW_MOD_CONNECT);
		अन्यथा अणु
			ch->newmod = para;
			ch->newcmd = PCTRL_CMD_FRH;
			nom = 0;
			ctrl = PCTRL_CMD_ESC;
			ch->state = STFAX_ESCAPE;
		पूर्ण
		अवरोध;
	हाल PCTRL_CMD_TDTMF:
		p1 = para;
		nom = 1;
		ctrl = PCTRL_CMD_TDTMF;
		अवरोध;
	पूर्ण
	अगर (ctrl)
		send_mbox(ch->is, dps | ISAR_HIS_PUMPCTRL, ctrl, nom, &p1);
पूर्ण

अटल व्योम
isar_setup(काष्ठा isar_hw *isar)
अणु
	u8 msg;
	पूर्णांक i;

	/* Dpath 1, 2 */
	msg = 61;
	क्रम (i = 0; i < 2; i++) अणु
		/* Buffer Config */
		send_mbox(isar, (i ? ISAR_HIS_DPS2 : ISAR_HIS_DPS1) |
			  ISAR_HIS_P12CFG, 4, 1, &msg);
		isar->ch[i].mml = msg;
		isar->ch[i].bch.state = 0;
		isar->ch[i].dpath = i + 1;
		modeisar(&isar->ch[i], ISDN_P_NONE);
	पूर्ण
पूर्ण

अटल पूर्णांक
isar_l2l1(काष्ठा mISDNchannel *ch, काष्ठा sk_buff *skb)
अणु
	काष्ठा bchannel *bch = container_of(ch, काष्ठा bchannel, ch);
	काष्ठा isar_ch *ich = container_of(bch, काष्ठा isar_ch, bch);
	पूर्णांक ret = -EINVAL;
	काष्ठा mISDNhead *hh = mISDN_HEAD_P(skb);
	u32 id, *val;
	u_दीर्घ flags;

	चयन (hh->prim) अणु
	हाल PH_DATA_REQ:
		spin_lock_irqsave(ich->is->hwlock, flags);
		ret = bchannel_senddata(bch, skb);
		अगर (ret > 0) अणु /* direct TX */
			ret = 0;
			isar_fill_fअगरo(ich);
		पूर्ण
		spin_unlock_irqrestore(ich->is->hwlock, flags);
		वापस ret;
	हाल PH_ACTIVATE_REQ:
		spin_lock_irqsave(ich->is->hwlock, flags);
		अगर (!test_and_set_bit(FLG_ACTIVE, &bch->Flags))
			ret = modeisar(ich, ch->protocol);
		अन्यथा
			ret = 0;
		spin_unlock_irqrestore(ich->is->hwlock, flags);
		अगर (!ret)
			_queue_data(ch, PH_ACTIVATE_IND, MISDN_ID_ANY, 0,
				    शून्य, GFP_KERNEL);
		अवरोध;
	हाल PH_DEACTIVATE_REQ:
		spin_lock_irqsave(ich->is->hwlock, flags);
		mISDN_clear_bchannel(bch);
		modeisar(ich, ISDN_P_NONE);
		spin_unlock_irqrestore(ich->is->hwlock, flags);
		_queue_data(ch, PH_DEACTIVATE_IND, MISDN_ID_ANY, 0,
			    शून्य, GFP_KERNEL);
		ret = 0;
		अवरोध;
	हाल PH_CONTROL_REQ:
		val = (u32 *)skb->data;
		pr_debug("%s: PH_CONTROL | REQUEST %x/%x\n", ich->is->name,
			 hh->id, *val);
		अगर ((hh->id == 0) && ((*val & ~DTMF_TONE_MASK) ==
				      DTMF_TONE_VAL)) अणु
			अगर (bch->state == ISDN_P_B_L2DTMF) अणु
				अक्षर tt = *val & DTMF_TONE_MASK;

				अगर (tt == '*')
					tt = 0x1e;
				अन्यथा अगर (tt == '#')
					tt = 0x1f;
				अन्यथा अगर (tt > '9')
					tt -= 7;
				tt &= 0x1f;
				spin_lock_irqsave(ich->is->hwlock, flags);
				isar_pump_cmd(ich, PCTRL_CMD_TDTMF, tt);
				spin_unlock_irqrestore(ich->is->hwlock, flags);
			पूर्ण अन्यथा अणु
				pr_info("%s: DTMF send wrong protocol %x\n",
					__func__, bch->state);
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अगर ((hh->id == HW_MOD_FRM) || (hh->id == HW_MOD_FRH) ||
			   (hh->id == HW_MOD_FTM) || (hh->id == HW_MOD_FTH)) अणु
			क्रम (id = 0; id < FAXMODCNT; id++)
				अगर (faxmodulation[id] == *val)
					अवरोध;
			अगर ((FAXMODCNT > id) &&
			    test_bit(FLG_INITIALIZED, &bch->Flags)) अणु
				pr_debug("%s: isar: new mod\n", ich->is->name);
				isar_pump_cmd(ich, hh->id, *val);
				ret = 0;
			पूर्ण अन्यथा अणु
				pr_info("%s: wrong modulation\n",
					ich->is->name);
				ret = -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अगर (hh->id == HW_MOD_LASTDATA)
			test_and_set_bit(FLG_DLEETX, &bch->Flags);
		अन्यथा अणु
			pr_info("%s: unknown PH_CONTROL_REQ %x\n",
				ich->is->name, hh->id);
			ret = -EINVAL;
		पूर्ण
		fallthrough;
	शेष:
		pr_info("%s: %s unknown prim(%x,%x)\n",
			ich->is->name, __func__, hh->prim, hh->id);
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
isar_bctrl(काष्ठा mISDNchannel *ch, u32 cmd, व्योम *arg)
अणु
	काष्ठा bchannel *bch = container_of(ch, काष्ठा bchannel, ch);
	काष्ठा isar_ch *ich = container_of(bch, काष्ठा isar_ch, bch);
	पूर्णांक ret = -EINVAL;
	u_दीर्घ flags;

	pr_debug("%s: %s cmd:%x %p\n", ich->is->name, __func__, cmd, arg);
	चयन (cmd) अणु
	हाल CLOSE_CHANNEL:
		test_and_clear_bit(FLG_OPEN, &bch->Flags);
		cancel_work_sync(&bch->workq);
		spin_lock_irqsave(ich->is->hwlock, flags);
		mISDN_clear_bchannel(bch);
		modeisar(ich, ISDN_P_NONE);
		spin_unlock_irqrestore(ich->is->hwlock, flags);
		ch->protocol = ISDN_P_NONE;
		ch->peer = शून्य;
		module_put(ich->is->owner);
		ret = 0;
		अवरोध;
	हाल CONTROL_CHANNEL:
		ret = channel_bctrl(bch, arg);
		अवरोध;
	शेष:
		pr_info("%s: %s unknown prim(%x)\n",
			ich->is->name, __func__, cmd);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम
मुक्त_isar(काष्ठा isar_hw *isar)
अणु
	modeisar(&isar->ch[0], ISDN_P_NONE);
	modeisar(&isar->ch[1], ISDN_P_NONE);
	del_समयr(&isar->ch[0].fसमयr);
	del_समयr(&isar->ch[1].fसमयr);
	test_and_clear_bit(FLG_INITIALIZED, &isar->ch[0].bch.Flags);
	test_and_clear_bit(FLG_INITIALIZED, &isar->ch[1].bch.Flags);
पूर्ण

अटल पूर्णांक
init_isar(काष्ठा isar_hw *isar)
अणु
	पूर्णांक	cnt = 3;

	जबतक (cnt--) अणु
		isar->version = ISARVersion(isar);
		अगर (isar->ch[0].bch.debug & DEBUG_HW)
			pr_notice("%s: Testing version %d (%d time)\n",
				  isar->name, isar->version, 3 - cnt);
		अगर (isar->version == 1)
			अवरोध;
		isar->ctrl(isar->hw, HW_RESET_REQ, 0);
	पूर्ण
	अगर (isar->version != 1)
		वापस -EINVAL;
	समयr_setup(&isar->ch[0].fसमयr, fसमयr_handler, 0);
	test_and_set_bit(FLG_INITIALIZED, &isar->ch[0].bch.Flags);
	समयr_setup(&isar->ch[1].fसमयr, fसमयr_handler, 0);
	test_and_set_bit(FLG_INITIALIZED, &isar->ch[1].bch.Flags);
	वापस 0;
पूर्ण

अटल पूर्णांक
isar_खोलो(काष्ठा isar_hw *isar, काष्ठा channel_req *rq)
अणु
	काष्ठा bchannel		*bch;

	अगर (rq->adr.channel == 0 || rq->adr.channel > 2)
		वापस -EINVAL;
	अगर (rq->protocol == ISDN_P_NONE)
		वापस -EINVAL;
	bch = &isar->ch[rq->adr.channel - 1].bch;
	अगर (test_and_set_bit(FLG_OPEN, &bch->Flags))
		वापस -EBUSY; /* b-channel can be only खोलो once */
	bch->ch.protocol = rq->protocol;
	rq->ch = &bch->ch;
	वापस 0;
पूर्ण

u32
mISDNisar_init(काष्ठा isar_hw *isar, व्योम *hw)
अणु
	u32 ret, i;

	isar->hw = hw;
	क्रम (i = 0; i < 2; i++) अणु
		isar->ch[i].bch.nr = i + 1;
		mISDN_initbchannel(&isar->ch[i].bch, MAX_DATA_MEM, 32);
		isar->ch[i].bch.ch.nr = i + 1;
		isar->ch[i].bch.ch.send = &isar_l2l1;
		isar->ch[i].bch.ch.ctrl = isar_bctrl;
		isar->ch[i].bch.hw = hw;
		isar->ch[i].is = isar;
	पूर्ण

	isar->init = &init_isar;
	isar->release = &मुक्त_isar;
	isar->firmware = &load_firmware;
	isar->खोलो = &isar_खोलो;

	ret =	(1 << (ISDN_P_B_RAW & ISDN_P_B_MASK)) |
		(1 << (ISDN_P_B_HDLC & ISDN_P_B_MASK)) |
		(1 << (ISDN_P_B_L2DTMF & ISDN_P_B_MASK)) |
		(1 << (ISDN_P_B_MODEM_ASYNC & ISDN_P_B_MASK)) |
		(1 << (ISDN_P_B_T30_FAX & ISDN_P_B_MASK));

	वापस ret;
पूर्ण
EXPORT_SYMBOL(mISDNisar_init);

अटल पूर्णांक __init isar_mod_init(व्योम)
अणु
	pr_notice("mISDN: ISAR driver Rev. %s\n", ISAR_REV);
	वापस 0;
पूर्ण

अटल व्योम __निकास isar_mod_cleanup(व्योम)
अणु
	pr_notice("mISDN: ISAR module unloaded\n");
पूर्ण
module_init(isar_mod_init);
module_निकास(isar_mod_cleanup);
