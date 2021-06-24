<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* hfcsusb.c
 * mISDN driver क्रम Colognechip HFC-S USB chip
 *
 * Copyright 2001 by Peter Sprenger (sprenger@moving-bytes.de)
 * Copyright 2008 by Martin Bachem (info@bachem-it.com)
 *
 * module params
 *   debug=<n>, शेष=0, with n=0xHHHHGGGG
 *      H - l1 driver flags described in hfcsusb.h
 *      G - common mISDN debug flags described at mISDNhw.h
 *
 *   poll=<n>, शेष 128
 *     n : burst size of PH_DATA_IND at transparent rx data
 *
 * Revision: 0.3.3 (socket), 2008-11-05
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/usb.h>
#समावेश <linux/mISDNhw.h>
#समावेश <linux/slab.h>
#समावेश "hfcsusb.h"

अटल अचिन्हित पूर्णांक debug;
अटल पूर्णांक poll = DEFAULT_TRANSP_BURST_SZ;

अटल LIST_HEAD(HFClist);
अटल DEFINE_RWLOCK(HFClock);


MODULE_AUTHOR("Martin Bachem");
MODULE_LICENSE("GPL");
module_param(debug, uपूर्णांक, S_IRUGO | S_IWUSR);
module_param(poll, पूर्णांक, 0);

अटल पूर्णांक hfcsusb_cnt;

/* some function prototypes */
अटल व्योम hfcsusb_ph_command(काष्ठा hfcsusb *hw, u_अक्षर command);
अटल व्योम release_hw(काष्ठा hfcsusb *hw);
अटल व्योम reset_hfcsusb(काष्ठा hfcsusb *hw);
अटल व्योम setPortMode(काष्ठा hfcsusb *hw);
अटल व्योम hfcsusb_start_endpoपूर्णांक(काष्ठा hfcsusb *hw, पूर्णांक channel);
अटल व्योम hfcsusb_stop_endpoपूर्णांक(काष्ठा hfcsusb *hw, पूर्णांक channel);
अटल पूर्णांक  hfcsusb_setup_bch(काष्ठा bchannel *bch, पूर्णांक protocol);
अटल व्योम deactivate_bchannel(काष्ठा bchannel *bch);
अटल पूर्णांक  hfcsusb_ph_info(काष्ठा hfcsusb *hw);

/* start next background transfer क्रम control channel */
अटल व्योम
ctrl_start_transfer(काष्ठा hfcsusb *hw)
अणु
	अगर (debug & DBG_HFC_CALL_TRACE)
		prपूर्णांकk(KERN_DEBUG "%s: %s\n", hw->name, __func__);

	अगर (hw->ctrl_cnt) अणु
		hw->ctrl_urb->pipe = hw->ctrl_out_pipe;
		hw->ctrl_urb->setup_packet = (u_अक्षर *)&hw->ctrl_ग_लिखो;
		hw->ctrl_urb->transfer_buffer = शून्य;
		hw->ctrl_urb->transfer_buffer_length = 0;
		hw->ctrl_ग_लिखो.wIndex =
			cpu_to_le16(hw->ctrl_buff[hw->ctrl_out_idx].hfcs_reg);
		hw->ctrl_ग_लिखो.wValue =
			cpu_to_le16(hw->ctrl_buff[hw->ctrl_out_idx].reg_val);

		usb_submit_urb(hw->ctrl_urb, GFP_ATOMIC);
	पूर्ण
पूर्ण

/*
 * queue a control transfer request to ग_लिखो HFC-S USB
 * chip रेजिस्टर using CTRL resuest queue
 */
अटल पूर्णांक ग_लिखो_reg(काष्ठा hfcsusb *hw, __u8 reg, __u8 val)
अणु
	काष्ठा ctrl_buf *buf;

	अगर (debug & DBG_HFC_CALL_TRACE)
		prपूर्णांकk(KERN_DEBUG "%s: %s reg(0x%02x) val(0x%02x)\n",
		       hw->name, __func__, reg, val);

	spin_lock(&hw->ctrl_lock);
	अगर (hw->ctrl_cnt >= HFC_CTRL_बफ_मानE) अणु
		spin_unlock(&hw->ctrl_lock);
		वापस 1;
	पूर्ण
	buf = &hw->ctrl_buff[hw->ctrl_in_idx];
	buf->hfcs_reg = reg;
	buf->reg_val = val;
	अगर (++hw->ctrl_in_idx >= HFC_CTRL_बफ_मानE)
		hw->ctrl_in_idx = 0;
	अगर (++hw->ctrl_cnt == 1)
		ctrl_start_transfer(hw);
	spin_unlock(&hw->ctrl_lock);

	वापस 0;
पूर्ण

/* control completion routine handling background control cmds */
अटल व्योम
ctrl_complete(काष्ठा urb *urb)
अणु
	काष्ठा hfcsusb *hw = (काष्ठा hfcsusb *) urb->context;

	अगर (debug & DBG_HFC_CALL_TRACE)
		prपूर्णांकk(KERN_DEBUG "%s: %s\n", hw->name, __func__);

	urb->dev = hw->dev;
	अगर (hw->ctrl_cnt) अणु
		hw->ctrl_cnt--;	/* decrement actual count */
		अगर (++hw->ctrl_out_idx >= HFC_CTRL_बफ_मानE)
			hw->ctrl_out_idx = 0;	/* poपूर्णांकer wrap */

		ctrl_start_transfer(hw); /* start next transfer */
	पूर्ण
पूर्ण

/* handle LED bits   */
अटल व्योम
set_led_bit(काष्ठा hfcsusb *hw, चिन्हित लघु led_bits, पूर्णांक set_on)
अणु
	अगर (set_on) अणु
		अगर (led_bits < 0)
			hw->led_state &= ~असल(led_bits);
		अन्यथा
			hw->led_state |= led_bits;
	पूर्ण अन्यथा अणु
		अगर (led_bits < 0)
			hw->led_state |= असल(led_bits);
		अन्यथा
			hw->led_state &= ~led_bits;
	पूर्ण
पूर्ण

/* handle LED requests  */
अटल व्योम
handle_led(काष्ठा hfcsusb *hw, पूर्णांक event)
अणु
	काष्ठा hfcsusb_vdata *driver_info = (काष्ठा hfcsusb_vdata *)
		hfcsusb_idtab[hw->vend_idx].driver_info;
	__u8 पंचांगpled;

	अगर (driver_info->led_scheme == LED_OFF)
		वापस;
	पंचांगpled = hw->led_state;

	चयन (event) अणु
	हाल LED_POWER_ON:
		set_led_bit(hw, driver_info->led_bits[0], 1);
		set_led_bit(hw, driver_info->led_bits[1], 0);
		set_led_bit(hw, driver_info->led_bits[2], 0);
		set_led_bit(hw, driver_info->led_bits[3], 0);
		अवरोध;
	हाल LED_POWER_OFF:
		set_led_bit(hw, driver_info->led_bits[0], 0);
		set_led_bit(hw, driver_info->led_bits[1], 0);
		set_led_bit(hw, driver_info->led_bits[2], 0);
		set_led_bit(hw, driver_info->led_bits[3], 0);
		अवरोध;
	हाल LED_S0_ON:
		set_led_bit(hw, driver_info->led_bits[1], 1);
		अवरोध;
	हाल LED_S0_OFF:
		set_led_bit(hw, driver_info->led_bits[1], 0);
		अवरोध;
	हाल LED_B1_ON:
		set_led_bit(hw, driver_info->led_bits[2], 1);
		अवरोध;
	हाल LED_B1_OFF:
		set_led_bit(hw, driver_info->led_bits[2], 0);
		अवरोध;
	हाल LED_B2_ON:
		set_led_bit(hw, driver_info->led_bits[3], 1);
		अवरोध;
	हाल LED_B2_OFF:
		set_led_bit(hw, driver_info->led_bits[3], 0);
		अवरोध;
	पूर्ण

	अगर (hw->led_state != पंचांगpled) अणु
		अगर (debug & DBG_HFC_CALL_TRACE)
			prपूर्णांकk(KERN_DEBUG "%s: %s reg(0x%02x) val(x%02x)\n",
			       hw->name, __func__,
			       HFCUSB_P_DATA, hw->led_state);

		ग_लिखो_reg(hw, HFCUSB_P_DATA, hw->led_state);
	पूर्ण
पूर्ण

/*
 * Layer2 -> Layer 1 Bchannel data
 */
अटल पूर्णांक
hfcusb_l2l1B(काष्ठा mISDNchannel *ch, काष्ठा sk_buff *skb)
अणु
	काष्ठा bchannel		*bch = container_of(ch, काष्ठा bchannel, ch);
	काष्ठा hfcsusb		*hw = bch->hw;
	पूर्णांक			ret = -EINVAL;
	काष्ठा mISDNhead	*hh = mISDN_HEAD_P(skb);
	u_दीर्घ			flags;

	अगर (debug & DBG_HFC_CALL_TRACE)
		prपूर्णांकk(KERN_DEBUG "%s: %s\n", hw->name, __func__);

	चयन (hh->prim) अणु
	हाल PH_DATA_REQ:
		spin_lock_irqsave(&hw->lock, flags);
		ret = bchannel_senddata(bch, skb);
		spin_unlock_irqrestore(&hw->lock, flags);
		अगर (debug & DBG_HFC_CALL_TRACE)
			prपूर्णांकk(KERN_DEBUG "%s: %s PH_DATA_REQ ret(%i)\n",
			       hw->name, __func__, ret);
		अगर (ret > 0)
			ret = 0;
		वापस ret;
	हाल PH_ACTIVATE_REQ:
		अगर (!test_and_set_bit(FLG_ACTIVE, &bch->Flags)) अणु
			hfcsusb_start_endpoपूर्णांक(hw, bch->nr - 1);
			ret = hfcsusb_setup_bch(bch, ch->protocol);
		पूर्ण अन्यथा
			ret = 0;
		अगर (!ret)
			_queue_data(ch, PH_ACTIVATE_IND, MISDN_ID_ANY,
				    0, शून्य, GFP_KERNEL);
		अवरोध;
	हाल PH_DEACTIVATE_REQ:
		deactivate_bchannel(bch);
		_queue_data(ch, PH_DEACTIVATE_IND, MISDN_ID_ANY,
			    0, शून्य, GFP_KERNEL);
		ret = 0;
		अवरोध;
	पूर्ण
	अगर (!ret)
		dev_kमुक्त_skb(skb);
	वापस ret;
पूर्ण

/*
 * send full D/B channel status inक्रमmation
 * as MPH_INFORMATION_IND
 */
अटल पूर्णांक
hfcsusb_ph_info(काष्ठा hfcsusb *hw)
अणु
	काष्ठा ph_info *phi;
	काष्ठा dchannel *dch = &hw->dch;
	पूर्णांक i;

	phi = kzalloc(काष्ठा_size(phi, bch, dch->dev.nrbchan), GFP_ATOMIC);
	अगर (!phi)
		वापस -ENOMEM;

	phi->dch.ch.protocol = hw->protocol;
	phi->dch.ch.Flags = dch->Flags;
	phi->dch.state = dch->state;
	phi->dch.num_bch = dch->dev.nrbchan;
	क्रम (i = 0; i < dch->dev.nrbchan; i++) अणु
		phi->bch[i].protocol = hw->bch[i].ch.protocol;
		phi->bch[i].Flags = hw->bch[i].Flags;
	पूर्ण
	_queue_data(&dch->dev.D, MPH_INFORMATION_IND, MISDN_ID_ANY,
		    काष्ठा_size(phi, bch, dch->dev.nrbchan), phi, GFP_ATOMIC);
	kमुक्त(phi);

	वापस 0;
पूर्ण

/*
 * Layer2 -> Layer 1 Dchannel data
 */
अटल पूर्णांक
hfcusb_l2l1D(काष्ठा mISDNchannel *ch, काष्ठा sk_buff *skb)
अणु
	काष्ठा mISDNdevice	*dev = container_of(ch, काष्ठा mISDNdevice, D);
	काष्ठा dchannel		*dch = container_of(dev, काष्ठा dchannel, dev);
	काष्ठा mISDNhead	*hh = mISDN_HEAD_P(skb);
	काष्ठा hfcsusb		*hw = dch->hw;
	पूर्णांक			ret = -EINVAL;
	u_दीर्घ			flags;

	चयन (hh->prim) अणु
	हाल PH_DATA_REQ:
		अगर (debug & DBG_HFC_CALL_TRACE)
			prपूर्णांकk(KERN_DEBUG "%s: %s: PH_DATA_REQ\n",
			       hw->name, __func__);

		spin_lock_irqsave(&hw->lock, flags);
		ret = dchannel_senddata(dch, skb);
		spin_unlock_irqrestore(&hw->lock, flags);
		अगर (ret > 0) अणु
			ret = 0;
			queue_ch_frame(ch, PH_DATA_CNF, hh->id, शून्य);
		पूर्ण
		अवरोध;

	हाल PH_ACTIVATE_REQ:
		अगर (debug & DBG_HFC_CALL_TRACE)
			prपूर्णांकk(KERN_DEBUG "%s: %s: PH_ACTIVATE_REQ %s\n",
			       hw->name, __func__,
			       (hw->protocol == ISDN_P_NT_S0) ? "NT" : "TE");

		अगर (hw->protocol == ISDN_P_NT_S0) अणु
			ret = 0;
			अगर (test_bit(FLG_ACTIVE, &dch->Flags)) अणु
				_queue_data(&dch->dev.D,
					    PH_ACTIVATE_IND, MISDN_ID_ANY, 0,
					    शून्य, GFP_ATOMIC);
			पूर्ण अन्यथा अणु
				hfcsusb_ph_command(hw,
						   HFC_L1_ACTIVATE_NT);
				test_and_set_bit(FLG_L2_ACTIVATED,
						 &dch->Flags);
			पूर्ण
		पूर्ण अन्यथा अणु
			hfcsusb_ph_command(hw, HFC_L1_ACTIVATE_TE);
			ret = l1_event(dch->l1, hh->prim);
		पूर्ण
		अवरोध;

	हाल PH_DEACTIVATE_REQ:
		अगर (debug & DBG_HFC_CALL_TRACE)
			prपूर्णांकk(KERN_DEBUG "%s: %s: PH_DEACTIVATE_REQ\n",
			       hw->name, __func__);
		test_and_clear_bit(FLG_L2_ACTIVATED, &dch->Flags);

		अगर (hw->protocol == ISDN_P_NT_S0) अणु
			hfcsusb_ph_command(hw, HFC_L1_DEACTIVATE_NT);
			spin_lock_irqsave(&hw->lock, flags);
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
			spin_unlock_irqrestore(&hw->lock, flags);
#अगर_घोषित FIXME
			अगर (test_and_clear_bit(FLG_L1_BUSY, &dch->Flags))
				dchannel_sched_event(&hc->dch, D_CLEARBUSY);
#पूर्ण_अगर
			ret = 0;
		पूर्ण अन्यथा
			ret = l1_event(dch->l1, hh->prim);
		अवरोध;
	हाल MPH_INFORMATION_REQ:
		ret = hfcsusb_ph_info(hw);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Layer 1 callback function
 */
अटल पूर्णांक
hfc_l1callback(काष्ठा dchannel *dch, u_पूर्णांक cmd)
अणु
	काष्ठा hfcsusb *hw = dch->hw;

	अगर (debug & DBG_HFC_CALL_TRACE)
		prपूर्णांकk(KERN_DEBUG "%s: %s cmd 0x%x\n",
		       hw->name, __func__, cmd);

	चयन (cmd) अणु
	हाल INFO3_P8:
	हाल INFO3_P10:
	हाल HW_RESET_REQ:
	हाल HW_POWERUP_REQ:
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
		अगर (dch->debug & DEBUG_HW)
			prपूर्णांकk(KERN_DEBUG "%s: %s: unknown cmd %x\n",
			       hw->name, __func__, cmd);
		वापस -1;
	पूर्ण
	वापस hfcsusb_ph_info(hw);
पूर्ण

अटल पूर्णांक
खोलो_dchannel(काष्ठा hfcsusb *hw, काष्ठा mISDNchannel *ch,
	      काष्ठा channel_req *rq)
अणु
	पूर्णांक err = 0;

	अगर (debug & DEBUG_HW_OPEN)
		prपूर्णांकk(KERN_DEBUG "%s: %s: dev(%d) open addr(%i) from %p\n",
		       hw->name, __func__, hw->dch.dev.id, rq->adr.channel,
		       __builtin_वापस_address(0));
	अगर (rq->protocol == ISDN_P_NONE)
		वापस -EINVAL;

	test_and_clear_bit(FLG_ACTIVE, &hw->dch.Flags);
	test_and_clear_bit(FLG_ACTIVE, &hw->ech.Flags);
	hfcsusb_start_endpoपूर्णांक(hw, HFC_CHAN_D);

	/* E-Channel logging */
	अगर (rq->adr.channel == 1) अणु
		अगर (hw->fअगरos[HFCUSB_PCM_RX].pipe) अणु
			hfcsusb_start_endpoपूर्णांक(hw, HFC_CHAN_E);
			set_bit(FLG_ACTIVE, &hw->ech.Flags);
			_queue_data(&hw->ech.dev.D, PH_ACTIVATE_IND,
				    MISDN_ID_ANY, 0, शून्य, GFP_ATOMIC);
		पूर्ण अन्यथा
			वापस -EINVAL;
	पूर्ण

	अगर (!hw->initकरोne) अणु
		hw->protocol = rq->protocol;
		अगर (rq->protocol == ISDN_P_TE_S0) अणु
			err = create_l1(&hw->dch, hfc_l1callback);
			अगर (err)
				वापस err;
		पूर्ण
		setPortMode(hw);
		ch->protocol = rq->protocol;
		hw->initकरोne = 1;
	पूर्ण अन्यथा अणु
		अगर (rq->protocol != ch->protocol)
			वापस -EPROTONOSUPPORT;
	पूर्ण

	अगर (((ch->protocol == ISDN_P_NT_S0) && (hw->dch.state == 3)) ||
	    ((ch->protocol == ISDN_P_TE_S0) && (hw->dch.state == 7)))
		_queue_data(ch, PH_ACTIVATE_IND, MISDN_ID_ANY,
			    0, शून्य, GFP_KERNEL);
	rq->ch = ch;
	अगर (!try_module_get(THIS_MODULE))
		prपूर्णांकk(KERN_WARNING "%s: %s: cannot get module\n",
		       hw->name, __func__);
	वापस 0;
पूर्ण

अटल पूर्णांक
खोलो_bchannel(काष्ठा hfcsusb *hw, काष्ठा channel_req *rq)
अणु
	काष्ठा bchannel		*bch;

	अगर (rq->adr.channel == 0 || rq->adr.channel > 2)
		वापस -EINVAL;
	अगर (rq->protocol == ISDN_P_NONE)
		वापस -EINVAL;

	अगर (debug & DBG_HFC_CALL_TRACE)
		prपूर्णांकk(KERN_DEBUG "%s: %s B%i\n",
		       hw->name, __func__, rq->adr.channel);

	bch = &hw->bch[rq->adr.channel - 1];
	अगर (test_and_set_bit(FLG_OPEN, &bch->Flags))
		वापस -EBUSY; /* b-channel can be only खोलो once */
	bch->ch.protocol = rq->protocol;
	rq->ch = &bch->ch;

	अगर (!try_module_get(THIS_MODULE))
		prपूर्णांकk(KERN_WARNING "%s: %s:cannot get module\n",
		       hw->name, __func__);
	वापस 0;
पूर्ण

अटल पूर्णांक
channel_ctrl(काष्ठा hfcsusb *hw, काष्ठा mISDN_ctrl_req *cq)
अणु
	पूर्णांक ret = 0;

	अगर (debug & DBG_HFC_CALL_TRACE)
		prपूर्णांकk(KERN_DEBUG "%s: %s op(0x%x) channel(0x%x)\n",
		       hw->name, __func__, (cq->op), (cq->channel));

	चयन (cq->op) अणु
	हाल MISDN_CTRL_GETOP:
		cq->op = MISDN_CTRL_LOOP | MISDN_CTRL_CONNECT |
			MISDN_CTRL_DISCONNECT;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "%s: %s: unknown Op %x\n",
		       hw->name, __func__, cq->op);
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * device control function
 */
अटल पूर्णांक
hfc_dctrl(काष्ठा mISDNchannel *ch, u_पूर्णांक cmd, व्योम *arg)
अणु
	काष्ठा mISDNdevice	*dev = container_of(ch, काष्ठा mISDNdevice, D);
	काष्ठा dchannel		*dch = container_of(dev, काष्ठा dchannel, dev);
	काष्ठा hfcsusb		*hw = dch->hw;
	काष्ठा channel_req	*rq;
	पूर्णांक			err = 0;

	अगर (dch->debug & DEBUG_HW)
		prपूर्णांकk(KERN_DEBUG "%s: %s: cmd:%x %p\n",
		       hw->name, __func__, cmd, arg);
	चयन (cmd) अणु
	हाल OPEN_CHANNEL:
		rq = arg;
		अगर ((rq->protocol == ISDN_P_TE_S0) ||
		    (rq->protocol == ISDN_P_NT_S0))
			err = खोलो_dchannel(hw, ch, rq);
		अन्यथा
			err = खोलो_bchannel(hw, rq);
		अगर (!err)
			hw->खोलो++;
		अवरोध;
	हाल CLOSE_CHANNEL:
		hw->खोलो--;
		अगर (debug & DEBUG_HW_OPEN)
			prपूर्णांकk(KERN_DEBUG
			       "%s: %s: dev(%d) close from %p (open %d)\n",
			       hw->name, __func__, hw->dch.dev.id,
			       __builtin_वापस_address(0), hw->खोलो);
		अगर (!hw->खोलो) अणु
			hfcsusb_stop_endpoपूर्णांक(hw, HFC_CHAN_D);
			अगर (hw->fअगरos[HFCUSB_PCM_RX].pipe)
				hfcsusb_stop_endpoपूर्णांक(hw, HFC_CHAN_E);
			handle_led(hw, LED_POWER_ON);
		पूर्ण
		module_put(THIS_MODULE);
		अवरोध;
	हाल CONTROL_CHANNEL:
		err = channel_ctrl(hw, arg);
		अवरोध;
	शेष:
		अगर (dch->debug & DEBUG_HW)
			prपूर्णांकk(KERN_DEBUG "%s: %s: unknown command %x\n",
			       hw->name, __func__, cmd);
		वापस -EINVAL;
	पूर्ण
	वापस err;
पूर्ण

/*
 * S0 TE state change event handler
 */
अटल व्योम
ph_state_te(काष्ठा dchannel *dch)
अणु
	काष्ठा hfcsusb *hw = dch->hw;

	अगर (debug & DEBUG_HW) अणु
		अगर (dch->state <= HFC_MAX_TE_LAYER1_STATE)
			prपूर्णांकk(KERN_DEBUG "%s: %s: %s\n", hw->name, __func__,
			       HFC_TE_LAYER1_STATES[dch->state]);
		अन्यथा
			prपूर्णांकk(KERN_DEBUG "%s: %s: TE F%d\n",
			       hw->name, __func__, dch->state);
	पूर्ण

	चयन (dch->state) अणु
	हाल 0:
		l1_event(dch->l1, HW_RESET_IND);
		अवरोध;
	हाल 3:
		l1_event(dch->l1, HW_DEACT_IND);
		अवरोध;
	हाल 5:
	हाल 8:
		l1_event(dch->l1, ANYSIGNAL);
		अवरोध;
	हाल 6:
		l1_event(dch->l1, INFO2);
		अवरोध;
	हाल 7:
		l1_event(dch->l1, INFO4_P8);
		अवरोध;
	पूर्ण
	अगर (dch->state == 7)
		handle_led(hw, LED_S0_ON);
	अन्यथा
		handle_led(hw, LED_S0_OFF);
पूर्ण

/*
 * S0 NT state change event handler
 */
अटल व्योम
ph_state_nt(काष्ठा dchannel *dch)
अणु
	काष्ठा hfcsusb *hw = dch->hw;

	अगर (debug & DEBUG_HW) अणु
		अगर (dch->state <= HFC_MAX_NT_LAYER1_STATE)
			prपूर्णांकk(KERN_DEBUG "%s: %s: %s\n",
			       hw->name, __func__,
			       HFC_NT_LAYER1_STATES[dch->state]);

		अन्यथा
			prपूर्णांकk(KERN_INFO DRIVER_NAME "%s: %s: NT G%d\n",
			       hw->name, __func__, dch->state);
	पूर्ण

	चयन (dch->state) अणु
	हाल (1):
		test_and_clear_bit(FLG_ACTIVE, &dch->Flags);
		test_and_clear_bit(FLG_L2_ACTIVATED, &dch->Flags);
		hw->nt_समयr = 0;
		hw->समयrs &= ~NT_ACTIVATION_TIMER;
		handle_led(hw, LED_S0_OFF);
		अवरोध;

	हाल (2):
		अगर (hw->nt_समयr < 0) अणु
			hw->nt_समयr = 0;
			hw->समयrs &= ~NT_ACTIVATION_TIMER;
			hfcsusb_ph_command(dch->hw, HFC_L1_DEACTIVATE_NT);
		पूर्ण अन्यथा अणु
			hw->समयrs |= NT_ACTIVATION_TIMER;
			hw->nt_समयr = NT_T1_COUNT;
			/* allow G2 -> G3 transition */
			ग_लिखो_reg(hw, HFCUSB_STATES, 2 | HFCUSB_NT_G2_G3);
		पूर्ण
		अवरोध;
	हाल (3):
		hw->nt_समयr = 0;
		hw->समयrs &= ~NT_ACTIVATION_TIMER;
		test_and_set_bit(FLG_ACTIVE, &dch->Flags);
		_queue_data(&dch->dev.D, PH_ACTIVATE_IND,
			    MISDN_ID_ANY, 0, शून्य, GFP_ATOMIC);
		handle_led(hw, LED_S0_ON);
		अवरोध;
	हाल (4):
		hw->nt_समयr = 0;
		hw->समयrs &= ~NT_ACTIVATION_TIMER;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	hfcsusb_ph_info(hw);
पूर्ण

अटल व्योम
ph_state(काष्ठा dchannel *dch)
अणु
	काष्ठा hfcsusb *hw = dch->hw;

	अगर (hw->protocol == ISDN_P_NT_S0)
		ph_state_nt(dch);
	अन्यथा अगर (hw->protocol == ISDN_P_TE_S0)
		ph_state_te(dch);
पूर्ण

/*
 * disable/enable BChannel क्रम desired protocoll
 */
अटल पूर्णांक
hfcsusb_setup_bch(काष्ठा bchannel *bch, पूर्णांक protocol)
अणु
	काष्ठा hfcsusb *hw = bch->hw;
	__u8 conhdlc, sctrl, sctrl_r;

	अगर (debug & DEBUG_HW)
		prपूर्णांकk(KERN_DEBUG "%s: %s: protocol %x-->%x B%d\n",
		       hw->name, __func__, bch->state, protocol,
		       bch->nr);

	/* setup val क्रम CON_HDLC */
	conhdlc = 0;
	अगर (protocol > ISDN_P_NONE)
		conhdlc = 8;	/* enable FIFO */

	चयन (protocol) अणु
	हाल (-1):	/* used क्रम init */
		bch->state = -1;
		fallthrough;
	हाल (ISDN_P_NONE):
		अगर (bch->state == ISDN_P_NONE)
			वापस 0; /* alपढ़ोy in idle state */
		bch->state = ISDN_P_NONE;
		clear_bit(FLG_HDLC, &bch->Flags);
		clear_bit(FLG_TRANSPARENT, &bch->Flags);
		अवरोध;
	हाल (ISDN_P_B_RAW):
		conhdlc |= 2;
		bch->state = protocol;
		set_bit(FLG_TRANSPARENT, &bch->Flags);
		अवरोध;
	हाल (ISDN_P_B_HDLC):
		bch->state = protocol;
		set_bit(FLG_HDLC, &bch->Flags);
		अवरोध;
	शेष:
		अगर (debug & DEBUG_HW)
			prपूर्णांकk(KERN_DEBUG "%s: %s: prot not known %x\n",
			       hw->name, __func__, protocol);
		वापस -ENOPROTOOPT;
	पूर्ण

	अगर (protocol >= ISDN_P_NONE) अणु
		ग_लिखो_reg(hw, HFCUSB_FIFO, (bch->nr == 1) ? 0 : 2);
		ग_लिखो_reg(hw, HFCUSB_CON_HDLC, conhdlc);
		ग_लिखो_reg(hw, HFCUSB_INC_RES_F, 2);
		ग_लिखो_reg(hw, HFCUSB_FIFO, (bch->nr == 1) ? 1 : 3);
		ग_लिखो_reg(hw, HFCUSB_CON_HDLC, conhdlc);
		ग_लिखो_reg(hw, HFCUSB_INC_RES_F, 2);

		sctrl = 0x40 + ((hw->protocol == ISDN_P_TE_S0) ? 0x00 : 0x04);
		sctrl_r = 0x0;
		अगर (test_bit(FLG_ACTIVE, &hw->bch[0].Flags)) अणु
			sctrl |= 1;
			sctrl_r |= 1;
		पूर्ण
		अगर (test_bit(FLG_ACTIVE, &hw->bch[1].Flags)) अणु
			sctrl |= 2;
			sctrl_r |= 2;
		पूर्ण
		ग_लिखो_reg(hw, HFCUSB_SCTRL, sctrl);
		ग_लिखो_reg(hw, HFCUSB_SCTRL_R, sctrl_r);

		अगर (protocol > ISDN_P_NONE)
			handle_led(hw, (bch->nr == 1) ? LED_B1_ON : LED_B2_ON);
		अन्यथा
			handle_led(hw, (bch->nr == 1) ? LED_B1_OFF :
				   LED_B2_OFF);
	पूर्ण
	वापस hfcsusb_ph_info(hw);
पूर्ण

अटल व्योम
hfcsusb_ph_command(काष्ठा hfcsusb *hw, u_अक्षर command)
अणु
	अगर (debug & DEBUG_HW)
		prपूर्णांकk(KERN_DEBUG "%s: %s: %x\n",
		       hw->name, __func__, command);

	चयन (command) अणु
	हाल HFC_L1_ACTIVATE_TE:
		/* क्रमce sending sending INFO1 */
		ग_लिखो_reg(hw, HFCUSB_STATES, 0x14);
		/* start l1 activation */
		ग_लिखो_reg(hw, HFCUSB_STATES, 0x04);
		अवरोध;

	हाल HFC_L1_FORCE_DEACTIVATE_TE:
		ग_लिखो_reg(hw, HFCUSB_STATES, 0x10);
		ग_लिखो_reg(hw, HFCUSB_STATES, 0x03);
		अवरोध;

	हाल HFC_L1_ACTIVATE_NT:
		अगर (hw->dch.state == 3)
			_queue_data(&hw->dch.dev.D, PH_ACTIVATE_IND,
				    MISDN_ID_ANY, 0, शून्य, GFP_ATOMIC);
		अन्यथा
			ग_लिखो_reg(hw, HFCUSB_STATES, HFCUSB_ACTIVATE |
				  HFCUSB_DO_ACTION | HFCUSB_NT_G2_G3);
		अवरोध;

	हाल HFC_L1_DEACTIVATE_NT:
		ग_लिखो_reg(hw, HFCUSB_STATES,
			  HFCUSB_DO_ACTION);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Layer 1 B-channel hardware access
 */
अटल पूर्णांक
channel_bctrl(काष्ठा bchannel *bch, काष्ठा mISDN_ctrl_req *cq)
अणु
	वापस mISDN_ctrl_bchannel(bch, cq);
पूर्ण

/* collect data from incoming पूर्णांकerrupt or isochron USB data */
अटल व्योम
hfcsusb_rx_frame(काष्ठा usb_fअगरo *fअगरo, __u8 *data, अचिन्हित पूर्णांक len,
		 पूर्णांक finish)
अणु
	काष्ठा hfcsusb	*hw = fअगरo->hw;
	काष्ठा sk_buff	*rx_skb = शून्य;
	पूर्णांक		maxlen = 0;
	पूर्णांक		fअगरon = fअगरo->fअगरonum;
	पूर्णांक		i;
	पूर्णांक		hdlc = 0;
	अचिन्हित दीर्घ	flags;

	अगर (debug & DBG_HFC_CALL_TRACE)
		prपूर्णांकk(KERN_DEBUG "%s: %s: fifo(%i) len(%i) "
		       "dch(%p) bch(%p) ech(%p)\n",
		       hw->name, __func__, fअगरon, len,
		       fअगरo->dch, fअगरo->bch, fअगरo->ech);

	अगर (!len)
		वापस;

	अगर ((!!fअगरo->dch + !!fअगरo->bch + !!fअगरo->ech) != 1) अणु
		prपूर्णांकk(KERN_DEBUG "%s: %s: undefined channel\n",
		       hw->name, __func__);
		वापस;
	पूर्ण

	spin_lock_irqsave(&hw->lock, flags);
	अगर (fअगरo->dch) अणु
		rx_skb = fअगरo->dch->rx_skb;
		maxlen = fअगरo->dch->maxlen;
		hdlc = 1;
	पूर्ण
	अगर (fअगरo->bch) अणु
		अगर (test_bit(FLG_RX_OFF, &fअगरo->bch->Flags)) अणु
			fअगरo->bch->dropcnt += len;
			spin_unlock_irqrestore(&hw->lock, flags);
			वापस;
		पूर्ण
		maxlen = bchannel_get_rxbuf(fअगरo->bch, len);
		rx_skb = fअगरo->bch->rx_skb;
		अगर (maxlen < 0) अणु
			अगर (rx_skb)
				skb_trim(rx_skb, 0);
			pr_warn("%s.B%d: No bufferspace for %d bytes\n",
				hw->name, fअगरo->bch->nr, len);
			spin_unlock_irqrestore(&hw->lock, flags);
			वापस;
		पूर्ण
		maxlen = fअगरo->bch->maxlen;
		hdlc = test_bit(FLG_HDLC, &fअगरo->bch->Flags);
	पूर्ण
	अगर (fअगरo->ech) अणु
		rx_skb = fअगरo->ech->rx_skb;
		maxlen = fअगरo->ech->maxlen;
		hdlc = 1;
	पूर्ण

	अगर (fअगरo->dch || fअगरo->ech) अणु
		अगर (!rx_skb) अणु
			rx_skb = mI_alloc_skb(maxlen, GFP_ATOMIC);
			अगर (rx_skb) अणु
				अगर (fअगरo->dch)
					fअगरo->dch->rx_skb = rx_skb;
				अगर (fअगरo->ech)
					fअगरo->ech->rx_skb = rx_skb;
				skb_trim(rx_skb, 0);
			पूर्ण अन्यथा अणु
				prपूर्णांकk(KERN_DEBUG "%s: %s: No mem for rx_skb\n",
				       hw->name, __func__);
				spin_unlock_irqrestore(&hw->lock, flags);
				वापस;
			पूर्ण
		पूर्ण
		/* D/E-Channel SKB range check */
		अगर ((rx_skb->len + len) >= MAX_DFRAME_LEN_L1) अणु
			prपूर्णांकk(KERN_DEBUG "%s: %s: sbk mem exceeded "
			       "for fifo(%d) HFCUSB_D_RX\n",
			       hw->name, __func__, fअगरon);
			skb_trim(rx_skb, 0);
			spin_unlock_irqrestore(&hw->lock, flags);
			वापस;
		पूर्ण
	पूर्ण

	skb_put_data(rx_skb, data, len);

	अगर (hdlc) अणु
		/* we have a complete hdlc packet */
		अगर (finish) अणु
			अगर ((rx_skb->len > 3) &&
			    (!(rx_skb->data[rx_skb->len - 1]))) अणु
				अगर (debug & DBG_HFC_FIFO_VERBOSE) अणु
					prपूर्णांकk(KERN_DEBUG "%s: %s: fifon(%i)"
					       " new RX len(%i): ",
					       hw->name, __func__, fअगरon,
					       rx_skb->len);
					i = 0;
					जबतक (i < rx_skb->len)
						prपूर्णांकk("%02x ",
						       rx_skb->data[i++]);
					prपूर्णांकk("\n");
				पूर्ण

				/* हटाओ CRC & status */
				skb_trim(rx_skb, rx_skb->len - 3);

				अगर (fअगरo->dch)
					recv_Dchannel(fअगरo->dch);
				अगर (fअगरo->bch)
					recv_Bchannel(fअगरo->bch, MISDN_ID_ANY,
						      0);
				अगर (fअगरo->ech)
					recv_Echannel(fअगरo->ech,
						      &hw->dch);
			पूर्ण अन्यथा अणु
				अगर (debug & DBG_HFC_FIFO_VERBOSE) अणु
					prपूर्णांकk(KERN_DEBUG
					       "%s: CRC or minlen ERROR fifon(%i) "
					       "RX len(%i): ",
					       hw->name, fअगरon, rx_skb->len);
					i = 0;
					जबतक (i < rx_skb->len)
						prपूर्णांकk("%02x ",
						       rx_skb->data[i++]);
					prपूर्णांकk("\n");
				पूर्ण
				skb_trim(rx_skb, 0);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* deliver transparent data to layer2 */
		recv_Bchannel(fअगरo->bch, MISDN_ID_ANY, false);
	पूर्ण
	spin_unlock_irqrestore(&hw->lock, flags);
पूर्ण

अटल व्योम
fill_isoc_urb(काष्ठा urb *urb, काष्ठा usb_device *dev, अचिन्हित पूर्णांक pipe,
	      व्योम *buf, पूर्णांक num_packets, पूर्णांक packet_size, पूर्णांक पूर्णांकerval,
	      usb_complete_t complete, व्योम *context)
अणु
	पूर्णांक k;

	usb_fill_bulk_urb(urb, dev, pipe, buf, packet_size * num_packets,
			  complete, context);

	urb->number_of_packets = num_packets;
	urb->transfer_flags = URB_ISO_ASAP;
	urb->actual_length = 0;
	urb->पूर्णांकerval = पूर्णांकerval;

	क्रम (k = 0; k < num_packets; k++) अणु
		urb->iso_frame_desc[k].offset = packet_size * k;
		urb->iso_frame_desc[k].length = packet_size;
		urb->iso_frame_desc[k].actual_length = 0;
	पूर्ण
पूर्ण

/* receive completion routine क्रम all ISO tx fअगरos   */
अटल व्योम
rx_iso_complete(काष्ठा urb *urb)
अणु
	काष्ठा iso_urb *context_iso_urb = (काष्ठा iso_urb *) urb->context;
	काष्ठा usb_fअगरo *fअगरo = context_iso_urb->owner_fअगरo;
	काष्ठा hfcsusb *hw = fअगरo->hw;
	पूर्णांक k, len, errcode, offset, num_isoc_packets, fअगरon, maxlen,
		status, iso_status, i;
	__u8 *buf;
	अटल __u8 eof[8];
	__u8 s0_state;
	अचिन्हित दीर्घ flags;

	fअगरon = fअगरo->fअगरonum;
	status = urb->status;

	spin_lock_irqsave(&hw->lock, flags);
	अगर (fअगरo->stop_gracefull) अणु
		fअगरo->stop_gracefull = 0;
		fअगरo->active = 0;
		spin_unlock_irqrestore(&hw->lock, flags);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&hw->lock, flags);

	/*
	 * ISO transfer only partially completed,
	 * look at inभागidual frame status क्रम details
	 */
	अगर (status == -EXDEV) अणु
		अगर (debug & DEBUG_HW)
			prपूर्णांकk(KERN_DEBUG "%s: %s: with -EXDEV "
			       "urb->status %d, fifonum %d\n",
			       hw->name, __func__,  status, fअगरon);

		/* clear status, so go on with ISO transfers */
		status = 0;
	पूर्ण

	s0_state = 0;
	अगर (fअगरo->active && !status) अणु
		num_isoc_packets = iso_packets[fअगरon];
		maxlen = fअगरo->usb_packet_maxlen;

		क्रम (k = 0; k < num_isoc_packets; ++k) अणु
			len = urb->iso_frame_desc[k].actual_length;
			offset = urb->iso_frame_desc[k].offset;
			buf = context_iso_urb->buffer + offset;
			iso_status = urb->iso_frame_desc[k].status;

			अगर (iso_status && (debug & DBG_HFC_FIFO_VERBOSE)) अणु
				prपूर्णांकk(KERN_DEBUG "%s: %s: "
				       "ISO packet %i, status: %i\n",
				       hw->name, __func__, k, iso_status);
			पूर्ण

			/* USB data log क्रम every D ISO in */
			अगर ((fअगरon == HFCUSB_D_RX) &&
			    (debug & DBG_HFC_USB_VERBOSE)) अणु
				prपूर्णांकk(KERN_DEBUG
				       "%s: %s: %d (%d/%d) len(%d) ",
				       hw->name, __func__, urb->start_frame,
				       k, num_isoc_packets - 1,
				       len);
				क्रम (i = 0; i < len; i++)
					prपूर्णांकk("%x ", buf[i]);
				prपूर्णांकk("\n");
			पूर्ण

			अगर (!iso_status) अणु
				अगर (fअगरo->last_urblen != maxlen) अणु
					/*
					 * save fअगरo fill-level threshold bits
					 * to use them later in TX ISO URB
					 * completions
					 */
					hw->threshold_mask = buf[1];

					अगर (fअगरon == HFCUSB_D_RX)
						s0_state = (buf[0] >> 4);

					eof[fअगरon] = buf[0] & 1;
					अगर (len > 2)
						hfcsusb_rx_frame(fअगरo, buf + 2,
								 len - 2, (len < maxlen)
								 ? eof[fअगरon] : 0);
				पूर्ण अन्यथा
					hfcsusb_rx_frame(fअगरo, buf, len,
							 (len < maxlen) ?
							 eof[fअगरon] : 0);
				fअगरo->last_urblen = len;
			पूर्ण
		पूर्ण

		/* संकेत S0 layer1 state change */
		अगर ((s0_state) && (hw->initकरोne) &&
		    (s0_state != hw->dch.state)) अणु
			hw->dch.state = s0_state;
			schedule_event(&hw->dch, FLG_PHCHANGE);
		पूर्ण

		fill_isoc_urb(urb, fअगरo->hw->dev, fअगरo->pipe,
			      context_iso_urb->buffer, num_isoc_packets,
			      fअगरo->usb_packet_maxlen, fअगरo->पूर्णांकervall,
			      (usb_complete_t)rx_iso_complete, urb->context);
		errcode = usb_submit_urb(urb, GFP_ATOMIC);
		अगर (errcode < 0) अणु
			अगर (debug & DEBUG_HW)
				prपूर्णांकk(KERN_DEBUG "%s: %s: error submitting "
				       "ISO URB: %d\n",
				       hw->name, __func__, errcode);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (status && (debug & DBG_HFC_URB_INFO))
			prपूर्णांकk(KERN_DEBUG "%s: %s: rx_iso_complete : "
			       "urb->status %d, fifonum %d\n",
			       hw->name, __func__, status, fअगरon);
	पूर्ण
पूर्ण

/* receive completion routine क्रम all पूर्णांकerrupt rx fअगरos */
अटल व्योम
rx_पूर्णांक_complete(काष्ठा urb *urb)
अणु
	पूर्णांक len, status, i;
	__u8 *buf, maxlen, fअगरon;
	काष्ठा usb_fअगरo *fअगरo = (काष्ठा usb_fअगरo *) urb->context;
	काष्ठा hfcsusb *hw = fअगरo->hw;
	अटल __u8 eof[8];
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hw->lock, flags);
	अगर (fअगरo->stop_gracefull) अणु
		fअगरo->stop_gracefull = 0;
		fअगरo->active = 0;
		spin_unlock_irqrestore(&hw->lock, flags);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&hw->lock, flags);

	fअगरon = fअगरo->fअगरonum;
	अगर ((!fअगरo->active) || (urb->status)) अणु
		अगर (debug & DBG_HFC_URB_ERROR)
			prपूर्णांकk(KERN_DEBUG
			       "%s: %s: RX-Fifo %i is going down (%i)\n",
			       hw->name, __func__, fअगरon, urb->status);

		fअगरo->urb->पूर्णांकerval = 0; /* cancel स्वतःmatic rescheduling */
		वापस;
	पूर्ण
	len = urb->actual_length;
	buf = fअगरo->buffer;
	maxlen = fअगरo->usb_packet_maxlen;

	/* USB data log क्रम every D INT in */
	अगर ((fअगरon == HFCUSB_D_RX) && (debug & DBG_HFC_USB_VERBOSE)) अणु
		prपूर्णांकk(KERN_DEBUG "%s: %s: D RX INT len(%d) ",
		       hw->name, __func__, len);
		क्रम (i = 0; i < len; i++)
			prपूर्णांकk("%02x ", buf[i]);
		prपूर्णांकk("\n");
	पूर्ण

	अगर (fअगरo->last_urblen != fअगरo->usb_packet_maxlen) अणु
		/* the threshold mask is in the 2nd status byte */
		hw->threshold_mask = buf[1];

		/* संकेत S0 layer1 state change */
		अगर (hw->initकरोne && ((buf[0] >> 4) != hw->dch.state)) अणु
			hw->dch.state = (buf[0] >> 4);
			schedule_event(&hw->dch, FLG_PHCHANGE);
		पूर्ण

		eof[fअगरon] = buf[0] & 1;
		/* अगर we have more than the 2 status bytes -> collect data */
		अगर (len > 2)
			hfcsusb_rx_frame(fअगरo, buf + 2,
					 urb->actual_length - 2,
					 (len < maxlen) ? eof[fअगरon] : 0);
	पूर्ण अन्यथा अणु
		hfcsusb_rx_frame(fअगरo, buf, urb->actual_length,
				 (len < maxlen) ? eof[fअगरon] : 0);
	पूर्ण
	fअगरo->last_urblen = urb->actual_length;

	status = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (status) अणु
		अगर (debug & DEBUG_HW)
			prपूर्णांकk(KERN_DEBUG "%s: %s: error resubmitting USB\n",
			       hw->name, __func__);
	पूर्ण
पूर्ण

/* transmit completion routine क्रम all ISO tx fअगरos */
अटल व्योम
tx_iso_complete(काष्ठा urb *urb)
अणु
	काष्ठा iso_urb *context_iso_urb = (काष्ठा iso_urb *) urb->context;
	काष्ठा usb_fअगरo *fअगरo = context_iso_urb->owner_fअगरo;
	काष्ठा hfcsusb *hw = fअगरo->hw;
	काष्ठा sk_buff *tx_skb;
	पूर्णांक k, tx_offset, num_isoc_packets, sink, reमुख्य, current_len,
		errcode, hdlc, i;
	पूर्णांक *tx_idx;
	पूर्णांक frame_complete, fअगरon, status, fillempty = 0;
	__u8 threshbit, *p;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hw->lock, flags);
	अगर (fअगरo->stop_gracefull) अणु
		fअगरo->stop_gracefull = 0;
		fअगरo->active = 0;
		spin_unlock_irqrestore(&hw->lock, flags);
		वापस;
	पूर्ण

	अगर (fअगरo->dch) अणु
		tx_skb = fअगरo->dch->tx_skb;
		tx_idx = &fअगरo->dch->tx_idx;
		hdlc = 1;
	पूर्ण अन्यथा अगर (fअगरo->bch) अणु
		tx_skb = fअगरo->bch->tx_skb;
		tx_idx = &fअगरo->bch->tx_idx;
		hdlc = test_bit(FLG_HDLC, &fअगरo->bch->Flags);
		अगर (!tx_skb && !hdlc &&
		    test_bit(FLG_FILLEMPTY, &fअगरo->bch->Flags))
			fillempty = 1;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_DEBUG "%s: %s: neither BCH nor DCH\n",
		       hw->name, __func__);
		spin_unlock_irqrestore(&hw->lock, flags);
		वापस;
	पूर्ण

	fअगरon = fअगरo->fअगरonum;
	status = urb->status;

	tx_offset = 0;

	/*
	 * ISO transfer only partially completed,
	 * look at inभागidual frame status क्रम details
	 */
	अगर (status == -EXDEV) अणु
		अगर (debug & DBG_HFC_URB_ERROR)
			prपूर्णांकk(KERN_DEBUG "%s: %s: "
			       "-EXDEV (%i) fifon (%d)\n",
			       hw->name, __func__, status, fअगरon);

		/* clear status, so go on with ISO transfers */
		status = 0;
	पूर्ण

	अगर (fअगरo->active && !status) अणु
		/* is FअगरoFull-threshold set क्रम our channel? */
		threshbit = (hw->threshold_mask & (1 << fअगरon));
		num_isoc_packets = iso_packets[fअगरon];

		/* predict dataflow to aव्योम fअगरo overflow */
		अगर (fअगरon >= HFCUSB_D_TX)
			sink = (threshbit) ? SINK_DMIN : SINK_DMAX;
		अन्यथा
			sink = (threshbit) ? SINK_MIN : SINK_MAX;
		fill_isoc_urb(urb, fअगरo->hw->dev, fअगरo->pipe,
			      context_iso_urb->buffer, num_isoc_packets,
			      fअगरo->usb_packet_maxlen, fअगरo->पूर्णांकervall,
			      (usb_complete_t)tx_iso_complete, urb->context);
		स_रखो(context_iso_urb->buffer, 0,
		       माप(context_iso_urb->buffer));
		frame_complete = 0;

		क्रम (k = 0; k < num_isoc_packets; ++k) अणु
			/* analyze tx success of previous ISO packets */
			अगर (debug & DBG_HFC_URB_ERROR) अणु
				errcode = urb->iso_frame_desc[k].status;
				अगर (errcode) अणु
					prपूर्णांकk(KERN_DEBUG "%s: %s: "
					       "ISO packet %i, status: %i\n",
					       hw->name, __func__, k, errcode);
				पूर्ण
			पूर्ण

			/* Generate next ISO Packets */
			अगर (tx_skb)
				reमुख्य = tx_skb->len - *tx_idx;
			अन्यथा अगर (fillempty)
				reमुख्य = 15; /* > not complete */
			अन्यथा
				reमुख्य = 0;

			अगर (reमुख्य > 0) अणु
				fअगरo->bit_line -= sink;
				current_len = (0 - fअगरo->bit_line) / 8;
				अगर (current_len > 14)
					current_len = 14;
				अगर (current_len < 0)
					current_len = 0;
				अगर (reमुख्य < current_len)
					current_len = reमुख्य;

				/* how much bit करो we put on the line? */
				fअगरo->bit_line += current_len * 8;

				context_iso_urb->buffer[tx_offset] = 0;
				अगर (current_len == reमुख्य) अणु
					अगर (hdlc) अणु
						/* संकेत frame completion */
						context_iso_urb->
							buffer[tx_offset] = 1;
						/* add 2 byte flags and 16bit
						 * CRC at end of ISDN frame */
						fअगरo->bit_line += 32;
					पूर्ण
					frame_complete = 1;
				पूर्ण

				/* copy tx data to iso-urb buffer */
				p = context_iso_urb->buffer + tx_offset + 1;
				अगर (fillempty) अणु
					स_रखो(p, fअगरo->bch->fill[0],
					       current_len);
				पूर्ण अन्यथा अणु
					स_नकल(p, (tx_skb->data + *tx_idx),
					       current_len);
					*tx_idx += current_len;
				पूर्ण
				urb->iso_frame_desc[k].offset = tx_offset;
				urb->iso_frame_desc[k].length = current_len + 1;

				/* USB data log क्रम every D ISO out */
				अगर ((fअगरon == HFCUSB_D_RX) && !fillempty &&
				    (debug & DBG_HFC_USB_VERBOSE)) अणु
					prपूर्णांकk(KERN_DEBUG
					       "%s: %s (%d/%d) offs(%d) len(%d) ",
					       hw->name, __func__,
					       k, num_isoc_packets - 1,
					       urb->iso_frame_desc[k].offset,
					       urb->iso_frame_desc[k].length);

					क्रम (i = urb->iso_frame_desc[k].offset;
					     i < (urb->iso_frame_desc[k].offset
						  + urb->iso_frame_desc[k].length);
					     i++)
						prपूर्णांकk("%x ",
						       context_iso_urb->buffer[i]);

					prपूर्णांकk(" skb->len(%i) tx-idx(%d)\n",
					       tx_skb->len, *tx_idx);
				पूर्ण

				tx_offset += (current_len + 1);
			पूर्ण अन्यथा अणु
				urb->iso_frame_desc[k].offset = tx_offset++;
				urb->iso_frame_desc[k].length = 1;
				/* we lower data margin every msec */
				fअगरo->bit_line -= sink;
				अगर (fअगरo->bit_line < BITLINE_INF)
					fअगरo->bit_line = BITLINE_INF;
			पूर्ण

			अगर (frame_complete) अणु
				frame_complete = 0;

				अगर (debug & DBG_HFC_FIFO_VERBOSE) अणु
					prपूर्णांकk(KERN_DEBUG  "%s: %s: "
					       "fifon(%i) new TX len(%i): ",
					       hw->name, __func__,
					       fअगरon, tx_skb->len);
					i = 0;
					जबतक (i < tx_skb->len)
						prपूर्णांकk("%02x ",
						       tx_skb->data[i++]);
					prपूर्णांकk("\n");
				पूर्ण

				dev_kमुक्त_skb(tx_skb);
				tx_skb = शून्य;
				अगर (fअगरo->dch && get_next_dframe(fअगरo->dch))
					tx_skb = fअगरo->dch->tx_skb;
				अन्यथा अगर (fअगरo->bch &&
					 get_next_bframe(fअगरo->bch))
					tx_skb = fअगरo->bch->tx_skb;
			पूर्ण
		पूर्ण
		errcode = usb_submit_urb(urb, GFP_ATOMIC);
		अगर (errcode < 0) अणु
			अगर (debug & DEBUG_HW)
				prपूर्णांकk(KERN_DEBUG
				       "%s: %s: error submitting ISO URB: %d \n",
				       hw->name, __func__, errcode);
		पूर्ण

		/*
		 * abuse DChannel tx iso completion to trigger NT mode state
		 * changes tx_iso_complete is assumed to be called every
		 * fअगरo->पूर्णांकervall (ms)
		 */
		अगर ((fअगरon == HFCUSB_D_TX) && (hw->protocol == ISDN_P_NT_S0)
		    && (hw->समयrs & NT_ACTIVATION_TIMER)) अणु
			अगर ((--hw->nt_समयr) < 0)
				schedule_event(&hw->dch, FLG_PHCHANGE);
		पूर्ण

	पूर्ण अन्यथा अणु
		अगर (status && (debug & DBG_HFC_URB_ERROR))
			prपूर्णांकk(KERN_DEBUG  "%s: %s: urb->status %s (%i)"
			       "fifonum=%d\n",
			       hw->name, __func__,
			       symbolic(urb_errlist, status), status, fअगरon);
	पूर्ण
	spin_unlock_irqrestore(&hw->lock, flags);
पूर्ण

/*
 * allocs urbs and start isoc transfer with two pending urbs to aव्योम
 * gaps in the transfer chain
 */
अटल पूर्णांक
start_isoc_chain(काष्ठा usb_fअगरo *fअगरo, पूर्णांक num_packets_per_urb,
		 usb_complete_t complete, पूर्णांक packet_size)
अणु
	काष्ठा hfcsusb *hw = fअगरo->hw;
	पूर्णांक i, k, errcode;

	अगर (debug)
		prपूर्णांकk(KERN_DEBUG "%s: %s: fifo %i\n",
		       hw->name, __func__, fअगरo->fअगरonum);

	/* allocate Memory क्रम Iso out Urbs */
	क्रम (i = 0; i < 2; i++) अणु
		अगर (!(fअगरo->iso[i].urb)) अणु
			fअगरo->iso[i].urb =
				usb_alloc_urb(num_packets_per_urb, GFP_KERNEL);
			अगर (!(fअगरo->iso[i].urb)) अणु
				prपूर्णांकk(KERN_DEBUG
				       "%s: %s: alloc urb for fifo %i failed",
				       hw->name, __func__, fअगरo->fअगरonum);
				जारी;
			पूर्ण
			fअगरo->iso[i].owner_fअगरo = (काष्ठा usb_fअगरo *) fअगरo;
			fअगरo->iso[i].indx = i;

			/* Init the first iso */
			अगर (ISO_BUFFER_SIZE >=
			    (fअगरo->usb_packet_maxlen *
			     num_packets_per_urb)) अणु
				fill_isoc_urb(fअगरo->iso[i].urb,
					      fअगरo->hw->dev, fअगरo->pipe,
					      fअगरo->iso[i].buffer,
					      num_packets_per_urb,
					      fअगरo->usb_packet_maxlen,
					      fअगरo->पूर्णांकervall, complete,
					      &fअगरo->iso[i]);
				स_रखो(fअगरo->iso[i].buffer, 0,
				       माप(fअगरo->iso[i].buffer));

				क्रम (k = 0; k < num_packets_per_urb; k++) अणु
					fअगरo->iso[i].urb->
						iso_frame_desc[k].offset =
						k * packet_size;
					fअगरo->iso[i].urb->
						iso_frame_desc[k].length =
						packet_size;
				पूर्ण
			पूर्ण अन्यथा अणु
				prपूर्णांकk(KERN_DEBUG
				       "%s: %s: ISO Buffer size to small!\n",
				       hw->name, __func__);
			पूर्ण
		पूर्ण
		fअगरo->bit_line = BITLINE_INF;

		errcode = usb_submit_urb(fअगरo->iso[i].urb, GFP_KERNEL);
		fअगरo->active = (errcode >= 0) ? 1 : 0;
		fअगरo->stop_gracefull = 0;
		अगर (errcode < 0) अणु
			prपूर्णांकk(KERN_DEBUG "%s: %s: %s URB nr:%d\n",
			       hw->name, __func__,
			       symbolic(urb_errlist, errcode), i);
		पूर्ण
	पूर्ण
	वापस fअगरo->active;
पूर्ण

अटल व्योम
stop_iso_gracefull(काष्ठा usb_fअगरo *fअगरo)
अणु
	काष्ठा hfcsusb *hw = fअगरo->hw;
	पूर्णांक i, समयout;
	u_दीर्घ flags;

	क्रम (i = 0; i < 2; i++) अणु
		spin_lock_irqsave(&hw->lock, flags);
		अगर (debug)
			prपूर्णांकk(KERN_DEBUG "%s: %s for fifo %i.%i\n",
			       hw->name, __func__, fअगरo->fअगरonum, i);
		fअगरo->stop_gracefull = 1;
		spin_unlock_irqrestore(&hw->lock, flags);
	पूर्ण

	क्रम (i = 0; i < 2; i++) अणु
		समयout = 3;
		जबतक (fअगरo->stop_gracefull && समयout--)
			schedule_समयout_पूर्णांकerruptible((HZ / 1000) * 16);
		अगर (debug && fअगरo->stop_gracefull)
			prपूर्णांकk(KERN_DEBUG "%s: ERROR %s for fifo %i.%i\n",
			       hw->name, __func__, fअगरo->fअगरonum, i);
	पूर्ण
पूर्ण

अटल व्योम
stop_पूर्णांक_gracefull(काष्ठा usb_fअगरo *fअगरo)
अणु
	काष्ठा hfcsusb *hw = fअगरo->hw;
	पूर्णांक समयout;
	u_दीर्घ flags;

	spin_lock_irqsave(&hw->lock, flags);
	अगर (debug)
		prपूर्णांकk(KERN_DEBUG "%s: %s for fifo %i\n",
		       hw->name, __func__, fअगरo->fअगरonum);
	fअगरo->stop_gracefull = 1;
	spin_unlock_irqrestore(&hw->lock, flags);

	समयout = 3;
	जबतक (fअगरo->stop_gracefull && समयout--)
		schedule_समयout_पूर्णांकerruptible((HZ / 1000) * 3);
	अगर (debug && fअगरo->stop_gracefull)
		prपूर्णांकk(KERN_DEBUG "%s: ERROR %s for fifo %i\n",
		       hw->name, __func__, fअगरo->fअगरonum);
पूर्ण

/* start the पूर्णांकerrupt transfer क्रम the given fअगरo */
अटल व्योम
start_पूर्णांक_fअगरo(काष्ठा usb_fअगरo *fअगरo)
अणु
	काष्ठा hfcsusb *hw = fअगरo->hw;
	पूर्णांक errcode;

	अगर (debug)
		prपूर्णांकk(KERN_DEBUG "%s: %s: INT IN fifo:%d\n",
		       hw->name, __func__, fअगरo->fअगरonum);

	अगर (!fअगरo->urb) अणु
		fअगरo->urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!fअगरo->urb)
			वापस;
	पूर्ण
	usb_fill_पूर्णांक_urb(fअगरo->urb, fअगरo->hw->dev, fअगरo->pipe,
			 fअगरo->buffer, fअगरo->usb_packet_maxlen,
			 (usb_complete_t)rx_पूर्णांक_complete, fअगरo, fअगरo->पूर्णांकervall);
	fअगरo->active = 1;
	fअगरo->stop_gracefull = 0;
	errcode = usb_submit_urb(fअगरo->urb, GFP_KERNEL);
	अगर (errcode) अणु
		prपूर्णांकk(KERN_DEBUG "%s: %s: submit URB: status:%i\n",
		       hw->name, __func__, errcode);
		fअगरo->active = 0;
	पूर्ण
पूर्ण

अटल व्योम
setPortMode(काष्ठा hfcsusb *hw)
अणु
	अगर (debug & DEBUG_HW)
		prपूर्णांकk(KERN_DEBUG "%s: %s %s\n", hw->name, __func__,
		       (hw->protocol == ISDN_P_TE_S0) ? "TE" : "NT");

	अगर (hw->protocol == ISDN_P_TE_S0) अणु
		ग_लिखो_reg(hw, HFCUSB_SCTRL, 0x40);
		ग_लिखो_reg(hw, HFCUSB_SCTRL_E, 0x00);
		ग_लिखो_reg(hw, HFCUSB_CLKDEL, CLKDEL_TE);
		ग_लिखो_reg(hw, HFCUSB_STATES, 3 | 0x10);
		ग_लिखो_reg(hw, HFCUSB_STATES, 3);
	पूर्ण अन्यथा अणु
		ग_लिखो_reg(hw, HFCUSB_SCTRL, 0x44);
		ग_लिखो_reg(hw, HFCUSB_SCTRL_E, 0x09);
		ग_लिखो_reg(hw, HFCUSB_CLKDEL, CLKDEL_NT);
		ग_लिखो_reg(hw, HFCUSB_STATES, 1 | 0x10);
		ग_लिखो_reg(hw, HFCUSB_STATES, 1);
	पूर्ण
पूर्ण

अटल व्योम
reset_hfcsusb(काष्ठा hfcsusb *hw)
अणु
	काष्ठा usb_fअगरo *fअगरo;
	पूर्णांक i;

	अगर (debug & DEBUG_HW)
		prपूर्णांकk(KERN_DEBUG "%s: %s\n", hw->name, __func__);

	/* करो Chip reset */
	ग_लिखो_reg(hw, HFCUSB_CIRM, 8);

	/* aux = output, reset off */
	ग_लिखो_reg(hw, HFCUSB_CIRM, 0x10);

	/* set USB_SIZE to match the wMaxPacketSize क्रम INT or BULK transfers */
	ग_लिखो_reg(hw, HFCUSB_USB_SIZE, (hw->packet_size / 8) |
		  ((hw->packet_size / 8) << 4));

	/* set USB_SIZE_I to match the the wMaxPacketSize क्रम ISO transfers */
	ग_लिखो_reg(hw, HFCUSB_USB_SIZE_I, hw->iso_packet_size);

	/* enable PCM/GCI master mode */
	ग_लिखो_reg(hw, HFCUSB_MST_MODE1, 0);	/* set शेष values */
	ग_लिखो_reg(hw, HFCUSB_MST_MODE0, 1);	/* enable master mode */

	/* init the fअगरos */
	ग_लिखो_reg(hw, HFCUSB_F_THRES,
		  (HFCUSB_TX_THRESHOLD / 8) | ((HFCUSB_RX_THRESHOLD / 8) << 4));

	fअगरo = hw->fअगरos;
	क्रम (i = 0; i < HFCUSB_NUM_FIFOS; i++) अणु
		ग_लिखो_reg(hw, HFCUSB_FIFO, i);	/* select the desired fअगरo */
		fअगरo[i].max_size =
			(i <= HFCUSB_B2_RX) ? MAX_BCH_SIZE : MAX_DFRAME_LEN;
		fअगरo[i].last_urblen = 0;

		/* set 2 bit क्रम D- & E-channel */
		ग_लिखो_reg(hw, HFCUSB_HDLC_PAR, ((i <= HFCUSB_B2_RX) ? 0 : 2));

		/* enable all fअगरos */
		अगर (i == HFCUSB_D_TX)
			ग_लिखो_reg(hw, HFCUSB_CON_HDLC,
				  (hw->protocol == ISDN_P_NT_S0) ? 0x08 : 0x09);
		अन्यथा
			ग_लिखो_reg(hw, HFCUSB_CON_HDLC, 0x08);
		ग_लिखो_reg(hw, HFCUSB_INC_RES_F, 2); /* reset the fअगरo */
	पूर्ण

	ग_लिखो_reg(hw, HFCUSB_SCTRL_R, 0); /* disable both B receivers */
	handle_led(hw, LED_POWER_ON);
पूर्ण

/* start USB data pipes dependand on device's endpoपूर्णांक configuration */
अटल व्योम
hfcsusb_start_endpoपूर्णांक(काष्ठा hfcsusb *hw, पूर्णांक channel)
अणु
	/* quick check अगर endpoपूर्णांक alपढ़ोy running */
	अगर ((channel == HFC_CHAN_D) && (hw->fअगरos[HFCUSB_D_RX].active))
		वापस;
	अगर ((channel == HFC_CHAN_B1) && (hw->fअगरos[HFCUSB_B1_RX].active))
		वापस;
	अगर ((channel == HFC_CHAN_B2) && (hw->fअगरos[HFCUSB_B2_RX].active))
		वापस;
	अगर ((channel == HFC_CHAN_E) && (hw->fअगरos[HFCUSB_PCM_RX].active))
		वापस;

	/* start rx endpoपूर्णांकs using USB INT IN method */
	अगर (hw->cfg_used == CNF_3INT3ISO || hw->cfg_used == CNF_4INT3ISO)
		start_पूर्णांक_fअगरo(hw->fअगरos + channel * 2 + 1);

	/* start rx endpoपूर्णांकs using USB ISO IN method */
	अगर (hw->cfg_used == CNF_3ISO3ISO || hw->cfg_used == CNF_4ISO3ISO) अणु
		चयन (channel) अणु
		हाल HFC_CHAN_D:
			start_isoc_chain(hw->fअगरos + HFCUSB_D_RX,
					 ISOC_PACKETS_D,
					 (usb_complete_t)rx_iso_complete,
					 16);
			अवरोध;
		हाल HFC_CHAN_E:
			start_isoc_chain(hw->fअगरos + HFCUSB_PCM_RX,
					 ISOC_PACKETS_D,
					 (usb_complete_t)rx_iso_complete,
					 16);
			अवरोध;
		हाल HFC_CHAN_B1:
			start_isoc_chain(hw->fअगरos + HFCUSB_B1_RX,
					 ISOC_PACKETS_B,
					 (usb_complete_t)rx_iso_complete,
					 16);
			अवरोध;
		हाल HFC_CHAN_B2:
			start_isoc_chain(hw->fअगरos + HFCUSB_B2_RX,
					 ISOC_PACKETS_B,
					 (usb_complete_t)rx_iso_complete,
					 16);
			अवरोध;
		पूर्ण
	पूर्ण

	/* start tx endpoपूर्णांकs using USB ISO OUT method */
	चयन (channel) अणु
	हाल HFC_CHAN_D:
		start_isoc_chain(hw->fअगरos + HFCUSB_D_TX,
				 ISOC_PACKETS_B,
				 (usb_complete_t)tx_iso_complete, 1);
		अवरोध;
	हाल HFC_CHAN_B1:
		start_isoc_chain(hw->fअगरos + HFCUSB_B1_TX,
				 ISOC_PACKETS_D,
				 (usb_complete_t)tx_iso_complete, 1);
		अवरोध;
	हाल HFC_CHAN_B2:
		start_isoc_chain(hw->fअगरos + HFCUSB_B2_TX,
				 ISOC_PACKETS_B,
				 (usb_complete_t)tx_iso_complete, 1);
		अवरोध;
	पूर्ण
पूर्ण

/* stop USB data pipes dependand on device's endpoपूर्णांक configuration */
अटल व्योम
hfcsusb_stop_endpoपूर्णांक(काष्ठा hfcsusb *hw, पूर्णांक channel)
अणु
	/* quick check अगर endpoपूर्णांक currently running */
	अगर ((channel == HFC_CHAN_D) && (!hw->fअगरos[HFCUSB_D_RX].active))
		वापस;
	अगर ((channel == HFC_CHAN_B1) && (!hw->fअगरos[HFCUSB_B1_RX].active))
		वापस;
	अगर ((channel == HFC_CHAN_B2) && (!hw->fअगरos[HFCUSB_B2_RX].active))
		वापस;
	अगर ((channel == HFC_CHAN_E) && (!hw->fअगरos[HFCUSB_PCM_RX].active))
		वापस;

	/* rx endpoपूर्णांकs using USB INT IN method */
	अगर (hw->cfg_used == CNF_3INT3ISO || hw->cfg_used == CNF_4INT3ISO)
		stop_पूर्णांक_gracefull(hw->fअगरos + channel * 2 + 1);

	/* rx endpoपूर्णांकs using USB ISO IN method */
	अगर (hw->cfg_used == CNF_3ISO3ISO || hw->cfg_used == CNF_4ISO3ISO)
		stop_iso_gracefull(hw->fअगरos + channel * 2 + 1);

	/* tx endpoपूर्णांकs using USB ISO OUT method */
	अगर (channel != HFC_CHAN_E)
		stop_iso_gracefull(hw->fअगरos + channel * 2);
पूर्ण


/* Hardware Initialization */
अटल पूर्णांक
setup_hfcsusb(काष्ठा hfcsusb *hw)
अणु
	व्योम *dmabuf = kदो_स्मृति(माप(u_अक्षर), GFP_KERNEL);
	u_अक्षर b;
	पूर्णांक ret;

	अगर (debug & DBG_HFC_CALL_TRACE)
		prपूर्णांकk(KERN_DEBUG "%s: %s\n", hw->name, __func__);

	अगर (!dmabuf)
		वापस -ENOMEM;

	ret = पढ़ो_reg_atomic(hw, HFCUSB_CHIP_ID, dmabuf);

	स_नकल(&b, dmabuf, माप(u_अक्षर));
	kमुक्त(dmabuf);

	/* check the chip id */
	अगर (ret != 1) अणु
		prपूर्णांकk(KERN_DEBUG "%s: %s: cannot read chip id\n",
		       hw->name, __func__);
		वापस 1;
	पूर्ण
	अगर (b != HFCUSB_CHIPID) अणु
		prपूर्णांकk(KERN_DEBUG "%s: %s: Invalid chip id 0x%02x\n",
		       hw->name, __func__, b);
		वापस 1;
	पूर्ण

	/* first set the needed config, पूर्णांकerface and alternate */
	(व्योम) usb_set_पूर्णांकerface(hw->dev, hw->अगर_used, hw->alt_used);

	hw->led_state = 0;

	/* init the background machinery क्रम control requests */
	hw->ctrl_पढ़ो.bRequestType = 0xc0;
	hw->ctrl_पढ़ो.bRequest = 1;
	hw->ctrl_पढ़ो.wLength = cpu_to_le16(1);
	hw->ctrl_ग_लिखो.bRequestType = 0x40;
	hw->ctrl_ग_लिखो.bRequest = 0;
	hw->ctrl_ग_लिखो.wLength = 0;
	usb_fill_control_urb(hw->ctrl_urb, hw->dev, hw->ctrl_out_pipe,
			     (u_अक्षर *)&hw->ctrl_ग_लिखो, शून्य, 0,
			     (usb_complete_t)ctrl_complete, hw);

	reset_hfcsusb(hw);
	वापस 0;
पूर्ण

अटल व्योम
release_hw(काष्ठा hfcsusb *hw)
अणु
	अगर (debug & DBG_HFC_CALL_TRACE)
		prपूर्णांकk(KERN_DEBUG "%s: %s\n", hw->name, __func__);

	/*
	 * stop all endpoपूर्णांकs gracefully
	 * TODO: mISDN_core should generate CLOSE_CHANNEL
	 *       संकेतs after calling mISDN_unरेजिस्टर_device()
	 */
	hfcsusb_stop_endpoपूर्णांक(hw, HFC_CHAN_D);
	hfcsusb_stop_endpoपूर्णांक(hw, HFC_CHAN_B1);
	hfcsusb_stop_endpoपूर्णांक(hw, HFC_CHAN_B2);
	अगर (hw->fअगरos[HFCUSB_PCM_RX].pipe)
		hfcsusb_stop_endpoपूर्णांक(hw, HFC_CHAN_E);
	अगर (hw->protocol == ISDN_P_TE_S0)
		l1_event(hw->dch.l1, CLOSE_CHANNEL);

	mISDN_unरेजिस्टर_device(&hw->dch.dev);
	mISDN_मुक्तbchannel(&hw->bch[1]);
	mISDN_मुक्तbchannel(&hw->bch[0]);
	mISDN_मुक्तdchannel(&hw->dch);

	अगर (hw->ctrl_urb) अणु
		usb_समाप्त_urb(hw->ctrl_urb);
		usb_मुक्त_urb(hw->ctrl_urb);
		hw->ctrl_urb = शून्य;
	पूर्ण

	अगर (hw->पूर्णांकf)
		usb_set_पूर्णांकfdata(hw->पूर्णांकf, शून्य);
	list_del(&hw->list);
	kमुक्त(hw);
	hw = शून्य;
पूर्ण

अटल व्योम
deactivate_bchannel(काष्ठा bchannel *bch)
अणु
	काष्ठा hfcsusb *hw = bch->hw;
	u_दीर्घ flags;

	अगर (bch->debug & DEBUG_HW)
		prपूर्णांकk(KERN_DEBUG "%s: %s: bch->nr(%i)\n",
		       hw->name, __func__, bch->nr);

	spin_lock_irqsave(&hw->lock, flags);
	mISDN_clear_bchannel(bch);
	spin_unlock_irqrestore(&hw->lock, flags);
	hfcsusb_setup_bch(bch, ISDN_P_NONE);
	hfcsusb_stop_endpoपूर्णांक(hw, bch->nr - 1);
पूर्ण

/*
 * Layer 1 B-channel hardware access
 */
अटल पूर्णांक
hfc_bctrl(काष्ठा mISDNchannel *ch, u_पूर्णांक cmd, व्योम *arg)
अणु
	काष्ठा bchannel	*bch = container_of(ch, काष्ठा bchannel, ch);
	पूर्णांक		ret = -EINVAL;

	अगर (bch->debug & DEBUG_HW)
		prपूर्णांकk(KERN_DEBUG "%s: cmd:%x %p\n", __func__, cmd, arg);

	चयन (cmd) अणु
	हाल HW_TESTRX_RAW:
	हाल HW_TESTRX_HDLC:
	हाल HW_TESTRX_OFF:
		ret = -EINVAL;
		अवरोध;

	हाल CLOSE_CHANNEL:
		test_and_clear_bit(FLG_OPEN, &bch->Flags);
		deactivate_bchannel(bch);
		ch->protocol = ISDN_P_NONE;
		ch->peer = शून्य;
		module_put(THIS_MODULE);
		ret = 0;
		अवरोध;
	हाल CONTROL_CHANNEL:
		ret = channel_bctrl(bch, arg);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "%s: unknown prim(%x)\n",
		       __func__, cmd);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
setup_instance(काष्ठा hfcsusb *hw, काष्ठा device *parent)
अणु
	u_दीर्घ	flags;
	पूर्णांक	err, i;

	अगर (debug & DBG_HFC_CALL_TRACE)
		prपूर्णांकk(KERN_DEBUG "%s: %s\n", hw->name, __func__);

	spin_lock_init(&hw->ctrl_lock);
	spin_lock_init(&hw->lock);

	mISDN_initdchannel(&hw->dch, MAX_DFRAME_LEN_L1, ph_state);
	hw->dch.debug = debug & 0xFFFF;
	hw->dch.hw = hw;
	hw->dch.dev.Dprotocols = (1 << ISDN_P_TE_S0) | (1 << ISDN_P_NT_S0);
	hw->dch.dev.D.send = hfcusb_l2l1D;
	hw->dch.dev.D.ctrl = hfc_dctrl;

	/* enable E-Channel logging */
	अगर (hw->fअगरos[HFCUSB_PCM_RX].pipe)
		mISDN_initdchannel(&hw->ech, MAX_DFRAME_LEN_L1, शून्य);

	hw->dch.dev.Bprotocols = (1 << (ISDN_P_B_RAW & ISDN_P_B_MASK)) |
		(1 << (ISDN_P_B_HDLC & ISDN_P_B_MASK));
	hw->dch.dev.nrbchan = 2;
	क्रम (i = 0; i < 2; i++) अणु
		hw->bch[i].nr = i + 1;
		set_channelmap(i + 1, hw->dch.dev.channelmap);
		hw->bch[i].debug = debug;
		mISDN_initbchannel(&hw->bch[i], MAX_DATA_MEM, poll >> 1);
		hw->bch[i].hw = hw;
		hw->bch[i].ch.send = hfcusb_l2l1B;
		hw->bch[i].ch.ctrl = hfc_bctrl;
		hw->bch[i].ch.nr = i + 1;
		list_add(&hw->bch[i].ch.list, &hw->dch.dev.bchannels);
	पूर्ण

	hw->fअगरos[HFCUSB_B1_TX].bch = &hw->bch[0];
	hw->fअगरos[HFCUSB_B1_RX].bch = &hw->bch[0];
	hw->fअगरos[HFCUSB_B2_TX].bch = &hw->bch[1];
	hw->fअगरos[HFCUSB_B2_RX].bch = &hw->bch[1];
	hw->fअगरos[HFCUSB_D_TX].dch = &hw->dch;
	hw->fअगरos[HFCUSB_D_RX].dch = &hw->dch;
	hw->fअगरos[HFCUSB_PCM_RX].ech = &hw->ech;
	hw->fअगरos[HFCUSB_PCM_TX].ech = &hw->ech;

	err = setup_hfcsusb(hw);
	अगर (err)
		जाओ out;

	snम_लिखो(hw->name, MISDN_MAX_IDLEN - 1, "%s.%d", DRIVER_NAME,
		 hfcsusb_cnt + 1);
	prपूर्णांकk(KERN_INFO "%s: registered as '%s'\n",
	       DRIVER_NAME, hw->name);

	err = mISDN_रेजिस्टर_device(&hw->dch.dev, parent, hw->name);
	अगर (err)
		जाओ out;

	hfcsusb_cnt++;
	ग_लिखो_lock_irqsave(&HFClock, flags);
	list_add_tail(&hw->list, &HFClist);
	ग_लिखो_unlock_irqrestore(&HFClock, flags);
	वापस 0;

out:
	mISDN_मुक्तbchannel(&hw->bch[1]);
	mISDN_मुक्तbchannel(&hw->bch[0]);
	mISDN_मुक्तdchannel(&hw->dch);
	kमुक्त(hw);
	वापस err;
पूर्ण

अटल पूर्णांक
hfcsusb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा hfcsusb			*hw;
	काष्ठा usb_device		*dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा usb_host_पूर्णांकerface	*अगरace = पूर्णांकf->cur_altsetting;
	काष्ठा usb_host_पूर्णांकerface	*अगरace_used = शून्य;
	काष्ठा usb_host_endpoपूर्णांक	*ep;
	काष्ठा hfcsusb_vdata		*driver_info;
	पूर्णांक अगरnum = अगरace->desc.bInterfaceNumber, i, idx, alt_idx,
		probe_alt_setting, vend_idx, cfg_used, *vcf, attr, cfg_found,
		ep_addr, cmptbl[16], small_match, iso_packet_size, packet_size,
		alt_used = 0;

	vend_idx = 0xffff;
	क्रम (i = 0; hfcsusb_idtab[i].idVenकरोr; i++) अणु
		अगर ((le16_to_cpu(dev->descriptor.idVenकरोr)
		     == hfcsusb_idtab[i].idVenकरोr) &&
		    (le16_to_cpu(dev->descriptor.idProduct)
		     == hfcsusb_idtab[i].idProduct)) अणु
			vend_idx = i;
			जारी;
		पूर्ण
	पूर्ण

	prपूर्णांकk(KERN_DEBUG
	       "%s: interface(%d) actalt(%d) minor(%d) vend_idx(%d)\n",
	       __func__, अगरnum, अगरace->desc.bAlternateSetting,
	       पूर्णांकf->minor, vend_idx);

	अगर (vend_idx == 0xffff) अणु
		prपूर्णांकk(KERN_WARNING
		       "%s: no valid vendor found in USB descriptor\n",
		       __func__);
		वापस -EIO;
	पूर्ण
	/* अगर venकरोr and product ID is OK, start probing alternate settings */
	alt_idx = 0;
	small_match = -1;

	/* शेष settings */
	iso_packet_size = 16;
	packet_size = 64;

	जबतक (alt_idx < पूर्णांकf->num_altsetting) अणु
		अगरace = पूर्णांकf->altsetting + alt_idx;
		probe_alt_setting = अगरace->desc.bAlternateSetting;
		cfg_used = 0;

		जबतक (validconf[cfg_used][0]) अणु
			cfg_found = 1;
			vcf = validconf[cfg_used];
			ep = अगरace->endpoपूर्णांक;
			स_नकल(cmptbl, vcf, 16 * माप(पूर्णांक));

			/* check क्रम all endpoपूर्णांकs in this alternate setting */
			क्रम (i = 0; i < अगरace->desc.bNumEndpoपूर्णांकs; i++) अणु
				ep_addr = ep->desc.bEndpoपूर्णांकAddress;

				/* get endpoपूर्णांक base */
				idx = ((ep_addr & 0x7f) - 1) * 2;
				अगर (idx > 15)
					वापस -EIO;

				अगर (ep_addr & 0x80)
					idx++;
				attr = ep->desc.bmAttributes;

				अगर (cmptbl[idx] != EP_NOP) अणु
					अगर (cmptbl[idx] == EP_NUL)
						cfg_found = 0;
					अगर (attr == USB_ENDPOINT_XFER_INT
					    && cmptbl[idx] == EP_INT)
						cmptbl[idx] = EP_NUL;
					अगर (attr == USB_ENDPOINT_XFER_BULK
					    && cmptbl[idx] == EP_BLK)
						cmptbl[idx] = EP_NUL;
					अगर (attr == USB_ENDPOINT_XFER_ISOC
					    && cmptbl[idx] == EP_ISO)
						cmptbl[idx] = EP_NUL;

					अगर (attr == USB_ENDPOINT_XFER_INT &&
					    ep->desc.bInterval < vcf[17]) अणु
						cfg_found = 0;
					पूर्ण
				पूर्ण
				ep++;
			पूर्ण

			क्रम (i = 0; i < 16; i++)
				अगर (cmptbl[i] != EP_NOP && cmptbl[i] != EP_NUL)
					cfg_found = 0;

			अगर (cfg_found) अणु
				अगर (small_match < cfg_used) अणु
					small_match = cfg_used;
					alt_used = probe_alt_setting;
					अगरace_used = अगरace;
				पूर्ण
			पूर्ण
			cfg_used++;
		पूर्ण
		alt_idx++;
	पूर्ण	/* (alt_idx < पूर्णांकf->num_altsetting) */

	/* not found a valid USB Ta Endpoपूर्णांक config */
	अगर (small_match == -1)
		वापस -EIO;

	अगरace = अगरace_used;
	hw = kzalloc(माप(काष्ठा hfcsusb), GFP_KERNEL);
	अगर (!hw)
		वापस -ENOMEM;	/* got no mem */
	snम_लिखो(hw->name, MISDN_MAX_IDLEN - 1, "%s", DRIVER_NAME);

	ep = अगरace->endpoपूर्णांक;
	vcf = validconf[small_match];

	क्रम (i = 0; i < अगरace->desc.bNumEndpoपूर्णांकs; i++) अणु
		काष्ठा usb_fअगरo *f;

		ep_addr = ep->desc.bEndpoपूर्णांकAddress;
		/* get endpoपूर्णांक base */
		idx = ((ep_addr & 0x7f) - 1) * 2;
		अगर (ep_addr & 0x80)
			idx++;
		f = &hw->fअगरos[idx & 7];

		/* init Endpoपूर्णांकs */
		अगर (vcf[idx] == EP_NOP || vcf[idx] == EP_NUL) अणु
			ep++;
			जारी;
		पूर्ण
		चयन (ep->desc.bmAttributes) अणु
		हाल USB_ENDPOINT_XFER_INT:
			f->pipe = usb_rcvपूर्णांकpipe(dev,
						 ep->desc.bEndpoपूर्णांकAddress);
			f->usb_transfer_mode = USB_INT;
			packet_size = le16_to_cpu(ep->desc.wMaxPacketSize);
			अवरोध;
		हाल USB_ENDPOINT_XFER_BULK:
			अगर (ep_addr & 0x80)
				f->pipe = usb_rcvbulkpipe(dev,
							  ep->desc.bEndpoपूर्णांकAddress);
			अन्यथा
				f->pipe = usb_sndbulkpipe(dev,
							  ep->desc.bEndpoपूर्णांकAddress);
			f->usb_transfer_mode = USB_BULK;
			packet_size = le16_to_cpu(ep->desc.wMaxPacketSize);
			अवरोध;
		हाल USB_ENDPOINT_XFER_ISOC:
			अगर (ep_addr & 0x80)
				f->pipe = usb_rcvisocpipe(dev,
							  ep->desc.bEndpoपूर्णांकAddress);
			अन्यथा
				f->pipe = usb_sndisocpipe(dev,
							  ep->desc.bEndpoपूर्णांकAddress);
			f->usb_transfer_mode = USB_ISOC;
			iso_packet_size = le16_to_cpu(ep->desc.wMaxPacketSize);
			अवरोध;
		शेष:
			f->pipe = 0;
		पूर्ण

		अगर (f->pipe) अणु
			f->fअगरonum = idx & 7;
			f->hw = hw;
			f->usb_packet_maxlen =
				le16_to_cpu(ep->desc.wMaxPacketSize);
			f->पूर्णांकervall = ep->desc.bInterval;
		पूर्ण
		ep++;
	पूर्ण
	hw->dev = dev; /* save device */
	hw->अगर_used = अगरnum; /* save used पूर्णांकerface */
	hw->alt_used = alt_used; /* and alternate config */
	hw->ctrl_paksize = dev->descriptor.bMaxPacketSize0; /* control size */
	hw->cfg_used = vcf[16];	/* store used config */
	hw->vend_idx = vend_idx; /* store found venकरोr */
	hw->packet_size = packet_size;
	hw->iso_packet_size = iso_packet_size;

	/* create the control pipes needed क्रम रेजिस्टर access */
	hw->ctrl_in_pipe = usb_rcvctrlpipe(hw->dev, 0);
	hw->ctrl_out_pipe = usb_sndctrlpipe(hw->dev, 0);

	driver_info = (काष्ठा hfcsusb_vdata *)
		      hfcsusb_idtab[vend_idx].driver_info;

	hw->ctrl_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!hw->ctrl_urb) अणु
		pr_warn("%s: No memory for control urb\n",
			driver_info->vend_name);
		kमुक्त(hw);
		वापस -ENOMEM;
	पूर्ण

	pr_info("%s: %s: detected \"%s\" (%s, if=%d alt=%d)\n",
		hw->name, __func__, driver_info->vend_name,
		conf_str[small_match], अगरnum, alt_used);

	अगर (setup_instance(hw, dev->dev.parent))
		वापस -EIO;

	hw->पूर्णांकf = पूर्णांकf;
	usb_set_पूर्णांकfdata(hw->पूर्णांकf, hw);
	वापस 0;
पूर्ण

/* function called when an active device is हटाओd */
अटल व्योम
hfcsusb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा hfcsusb *hw = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा hfcsusb *next;
	पूर्णांक cnt = 0;

	prपूर्णांकk(KERN_INFO "%s: device disconnected\n", hw->name);

	handle_led(hw, LED_POWER_OFF);
	release_hw(hw);

	list_क्रम_each_entry_safe(hw, next, &HFClist, list)
		cnt++;
	अगर (!cnt)
		hfcsusb_cnt = 0;

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
पूर्ण

अटल काष्ठा usb_driver hfcsusb_drv = अणु
	.name = DRIVER_NAME,
	.id_table = hfcsusb_idtab,
	.probe = hfcsusb_probe,
	.disconnect = hfcsusb_disconnect,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(hfcsusb_drv);
