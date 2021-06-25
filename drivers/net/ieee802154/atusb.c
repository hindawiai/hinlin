<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * atusb.c - Driver क्रम the ATUSB IEEE 802.15.4 करोngle
 *
 * Written 2013 by Werner Almesberger <werner@almesberger.net>
 *
 * Copyright (c) 2015 - 2016 Stefan Schmidt <stefan@datenfreihafen.org>
 *
 * Based on at86rf230.c and spi_atusb.c.
 * at86rf230.c is
 * Copyright (C) 2009 Siemens AG
 * Written by: Dmitry Eremin-Solenikov <dmitry.baryshkov@siemens.com>
 *
 * spi_atusb.c is
 * Copyright (c) 2011 Riअक्षरd Sharpe <realriअक्षरdsharpe@gmail.com>
 * Copyright (c) 2011 Stefan Schmidt <stefan@datenfreihafen.org>
 * Copyright (c) 2011 Werner Almesberger <werner@almesberger.net>
 *
 * USB initialization is
 * Copyright (c) 2013 Alexander Aring <alex.aring@gmail.com>
 *
 * Busware HUL support is
 * Copyright (c) 2017 Josef Filzmaier <j.filzmaier@gmx.at>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/usb.h>
#समावेश <linux/skbuff.h>

#समावेश <net/cfg802154.h>
#समावेश <net/mac802154.h>

#समावेश "at86rf230.h"
#समावेश "atusb.h"

#घोषणा ATUSB_JEDEC_ATMEL	0x1f	/* JEDEC manufacturer ID */

#घोषणा ATUSB_NUM_RX_URBS	4	/* allow क्रम a bit of local latency */
#घोषणा ATUSB_ALLOC_DELAY_MS	100	/* delay after failed allocation */
#घोषणा ATUSB_TX_TIMEOUT_MS	200	/* on the air समयout */

काष्ठा atusb अणु
	काष्ठा ieee802154_hw *hw;
	काष्ठा usb_device *usb_dev;
	काष्ठा atusb_chip_data *data;
	पूर्णांक shutकरोwn;			/* non-zero अगर shutting करोwn */
	पूर्णांक err;			/* set by first error */

	/* RX variables */
	काष्ठा delayed_work work;	/* memory allocations */
	काष्ठा usb_anchor idle_urbs;	/* URBs रुकोing to be submitted */
	काष्ठा usb_anchor rx_urbs;	/* URBs रुकोing क्रम reception */

	/* TX variables */
	काष्ठा usb_ctrlrequest tx_dr;
	काष्ठा urb *tx_urb;
	काष्ठा sk_buff *tx_skb;
	u8 tx_ack_seq;		/* current TX ACK sequence number */

	/* Firmware variable */
	अचिन्हित अक्षर fw_ver_maj;	/* Firmware major version number */
	अचिन्हित अक्षर fw_ver_min;	/* Firmware minor version number */
	अचिन्हित अक्षर fw_hw_type;	/* Firmware hardware type */
पूर्ण;

काष्ठा atusb_chip_data अणु
	u16 t_channel_चयन;
	पूर्णांक rssi_base_val;

	पूर्णांक (*set_channel)(काष्ठा ieee802154_hw*, u8, u8);
	पूर्णांक (*set_txघातer)(काष्ठा ieee802154_hw*, s32);
पूर्ण;

/* ----- USB commands without data ----------------------------------------- */

/* To reduce the number of error checks in the code, we record the first error
 * in atusb->err and reject all subsequent requests until the error is cleared.
 */

अटल पूर्णांक atusb_control_msg(काष्ठा atusb *atusb, अचिन्हित पूर्णांक pipe,
			     __u8 request, __u8 requesttype,
			     __u16 value, __u16 index,
			     व्योम *data, __u16 size, पूर्णांक समयout)
अणु
	काष्ठा usb_device *usb_dev = atusb->usb_dev;
	पूर्णांक ret;

	अगर (atusb->err)
		वापस atusb->err;

	ret = usb_control_msg(usb_dev, pipe, request, requesttype,
			      value, index, data, size, समयout);
	अगर (ret < 0) अणु
		atusb->err = ret;
		dev_err(&usb_dev->dev,
			"%s: req 0x%02x val 0x%x idx 0x%x, error %d\n",
			__func__, request, value, index, ret);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक atusb_command(काष्ठा atusb *atusb, u8 cmd, u8 arg)
अणु
	काष्ठा usb_device *usb_dev = atusb->usb_dev;

	dev_dbg(&usb_dev->dev, "%s: cmd = 0x%x\n", __func__, cmd);
	वापस atusb_control_msg(atusb, usb_sndctrlpipe(usb_dev, 0),
				 cmd, ATUSB_REQ_TO_DEV, arg, 0, शून्य, 0, 1000);
पूर्ण

अटल पूर्णांक atusb_ग_लिखो_reg(काष्ठा atusb *atusb, u8 reg, u8 value)
अणु
	काष्ठा usb_device *usb_dev = atusb->usb_dev;

	dev_dbg(&usb_dev->dev, "%s: 0x%02x <- 0x%02x\n", __func__, reg, value);
	वापस atusb_control_msg(atusb, usb_sndctrlpipe(usb_dev, 0),
				 ATUSB_REG_WRITE, ATUSB_REQ_TO_DEV,
				 value, reg, शून्य, 0, 1000);
पूर्ण

अटल पूर्णांक atusb_पढ़ो_reg(काष्ठा atusb *atusb, u8 reg)
अणु
	काष्ठा usb_device *usb_dev = atusb->usb_dev;
	पूर्णांक ret;
	u8 *buffer;
	u8 value;

	buffer = kदो_स्मृति(1, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	dev_dbg(&usb_dev->dev, "%s: reg = 0x%x\n", __func__, reg);
	ret = atusb_control_msg(atusb, usb_rcvctrlpipe(usb_dev, 0),
				ATUSB_REG_READ, ATUSB_REQ_FROM_DEV,
				0, reg, buffer, 1, 1000);

	अगर (ret >= 0) अणु
		value = buffer[0];
		kमुक्त(buffer);
		वापस value;
	पूर्ण अन्यथा अणु
		kमुक्त(buffer);
		वापस ret;
	पूर्ण
पूर्ण

अटल पूर्णांक atusb_ग_लिखो_subreg(काष्ठा atusb *atusb, u8 reg, u8 mask,
			      u8 shअगरt, u8 value)
अणु
	काष्ठा usb_device *usb_dev = atusb->usb_dev;
	u8 orig, पंचांगp;
	पूर्णांक ret = 0;

	dev_dbg(&usb_dev->dev, "%s: 0x%02x <- 0x%02x\n", __func__, reg, value);

	orig = atusb_पढ़ो_reg(atusb, reg);

	/* Write the value only पूर्णांकo that part of the रेजिस्टर which is allowed
	 * by the mask. All other bits stay as beक्रमe.
	 */
	पंचांगp = orig & ~mask;
	पंचांगp |= (value << shअगरt) & mask;

	अगर (पंचांगp != orig)
		ret = atusb_ग_लिखो_reg(atusb, reg, पंचांगp);

	वापस ret;
पूर्ण

अटल पूर्णांक atusb_पढ़ो_subreg(काष्ठा atusb *lp,
			     अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक mask,
			     अचिन्हित पूर्णांक shअगरt)
अणु
	पूर्णांक rc;

	rc = atusb_पढ़ो_reg(lp, addr);
	rc = (rc & mask) >> shअगरt;

	वापस rc;
पूर्ण

अटल पूर्णांक atusb_get_and_clear_error(काष्ठा atusb *atusb)
अणु
	पूर्णांक err = atusb->err;

	atusb->err = 0;
	वापस err;
पूर्ण

/* ----- skb allocation ---------------------------------------------------- */

#घोषणा MAX_PSDU	127
#घोषणा MAX_RX_XFER	(1 + MAX_PSDU + 2 + 1)	/* PHR+PSDU+CRC+LQI */

#घोषणा SKB_ATUSB(skb)	(*(काष्ठा atusb **)(skb)->cb)

अटल व्योम atusb_in(काष्ठा urb *urb);

अटल पूर्णांक atusb_submit_rx_urb(काष्ठा atusb *atusb, काष्ठा urb *urb)
अणु
	काष्ठा usb_device *usb_dev = atusb->usb_dev;
	काष्ठा sk_buff *skb = urb->context;
	पूर्णांक ret;

	अगर (!skb) अणु
		skb = alloc_skb(MAX_RX_XFER, GFP_KERNEL);
		अगर (!skb) अणु
			dev_warn_ratelimited(&usb_dev->dev,
					     "atusb_in: can't allocate skb\n");
			वापस -ENOMEM;
		पूर्ण
		skb_put(skb, MAX_RX_XFER);
		SKB_ATUSB(skb) = atusb;
	पूर्ण

	usb_fill_bulk_urb(urb, usb_dev, usb_rcvbulkpipe(usb_dev, 1),
			  skb->data, MAX_RX_XFER, atusb_in, skb);
	usb_anchor_urb(urb, &atusb->rx_urbs);

	ret = usb_submit_urb(urb, GFP_KERNEL);
	अगर (ret) अणु
		usb_unanchor_urb(urb);
		kमुक्त_skb(skb);
		urb->context = शून्य;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम atusb_work_urbs(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा atusb *atusb =
	    container_of(to_delayed_work(work), काष्ठा atusb, work);
	काष्ठा usb_device *usb_dev = atusb->usb_dev;
	काष्ठा urb *urb;
	पूर्णांक ret;

	अगर (atusb->shutकरोwn)
		वापस;

	करो अणु
		urb = usb_get_from_anchor(&atusb->idle_urbs);
		अगर (!urb)
			वापस;
		ret = atusb_submit_rx_urb(atusb, urb);
	पूर्ण जबतक (!ret);

	usb_anchor_urb(urb, &atusb->idle_urbs);
	dev_warn_ratelimited(&usb_dev->dev,
			     "atusb_in: can't allocate/submit URB (%d)\n", ret);
	schedule_delayed_work(&atusb->work,
			      msecs_to_jअगरfies(ATUSB_ALLOC_DELAY_MS) + 1);
पूर्ण

/* ----- Asynchronous USB -------------------------------------------------- */

अटल व्योम atusb_tx_करोne(काष्ठा atusb *atusb, u8 seq)
अणु
	काष्ठा usb_device *usb_dev = atusb->usb_dev;
	u8 expect = atusb->tx_ack_seq;

	dev_dbg(&usb_dev->dev, "%s (0x%02x/0x%02x)\n", __func__, seq, expect);
	अगर (seq == expect) अणु
		/* TODO check क्रम अगरs handling in firmware */
		ieee802154_xmit_complete(atusb->hw, atusb->tx_skb, false);
	पूर्ण अन्यथा अणु
		/* TODO I experience this हाल when atusb has a tx complete
		 * irq beक्रमe probing, we should fix the firmware it's an
		 * unlikely हाल now that seq == expect is then true, but can
		 * happen and fail with a tx_skb = शून्य;
		 */
		ieee802154_wake_queue(atusb->hw);
		अगर (atusb->tx_skb)
			dev_kमुक्त_skb_irq(atusb->tx_skb);
	पूर्ण
पूर्ण

अटल व्योम atusb_in_good(काष्ठा urb *urb)
अणु
	काष्ठा usb_device *usb_dev = urb->dev;
	काष्ठा sk_buff *skb = urb->context;
	काष्ठा atusb *atusb = SKB_ATUSB(skb);
	u8 len, lqi;

	अगर (!urb->actual_length) अणु
		dev_dbg(&usb_dev->dev, "atusb_in: zero-sized URB ?\n");
		वापस;
	पूर्ण

	len = *skb->data;

	अगर (urb->actual_length == 1) अणु
		atusb_tx_करोne(atusb, len);
		वापस;
	पूर्ण

	अगर (len + 1 > urb->actual_length - 1) अणु
		dev_dbg(&usb_dev->dev, "atusb_in: frame len %d+1 > URB %u-1\n",
			len, urb->actual_length);
		वापस;
	पूर्ण

	अगर (!ieee802154_is_valid_psdu_len(len)) अणु
		dev_dbg(&usb_dev->dev, "atusb_in: frame corrupted\n");
		वापस;
	पूर्ण

	lqi = skb->data[len + 1];
	dev_dbg(&usb_dev->dev, "atusb_in: rx len %d lqi 0x%02x\n", len, lqi);
	skb_pull(skb, 1);	/* हटाओ PHR */
	skb_trim(skb, len);	/* get payload only */
	ieee802154_rx_irqsafe(atusb->hw, skb, lqi);
	urb->context = शून्य;	/* skb is gone */
पूर्ण

अटल व्योम atusb_in(काष्ठा urb *urb)
अणु
	काष्ठा usb_device *usb_dev = urb->dev;
	काष्ठा sk_buff *skb = urb->context;
	काष्ठा atusb *atusb = SKB_ATUSB(skb);

	dev_dbg(&usb_dev->dev, "%s: status %d len %d\n", __func__,
		urb->status, urb->actual_length);
	अगर (urb->status) अणु
		अगर (urb->status == -ENOENT) अणु /* being समाप्तed */
			kमुक्त_skb(skb);
			urb->context = शून्य;
			वापस;
		पूर्ण
		dev_dbg(&usb_dev->dev, "%s: URB error %d\n", __func__, urb->status);
	पूर्ण अन्यथा अणु
		atusb_in_good(urb);
	पूर्ण

	usb_anchor_urb(urb, &atusb->idle_urbs);
	अगर (!atusb->shutकरोwn)
		schedule_delayed_work(&atusb->work, 0);
पूर्ण

/* ----- URB allocation/deallocation --------------------------------------- */

अटल व्योम atusb_मुक्त_urbs(काष्ठा atusb *atusb)
अणु
	काष्ठा urb *urb;

	जबतक (1) अणु
		urb = usb_get_from_anchor(&atusb->idle_urbs);
		अगर (!urb)
			अवरोध;
		kमुक्त_skb(urb->context);
		usb_मुक्त_urb(urb);
	पूर्ण
पूर्ण

अटल पूर्णांक atusb_alloc_urbs(काष्ठा atusb *atusb, पूर्णांक n)
अणु
	काष्ठा urb *urb;

	जबतक (n) अणु
		urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!urb) अणु
			atusb_मुक्त_urbs(atusb);
			वापस -ENOMEM;
		पूर्ण
		usb_anchor_urb(urb, &atusb->idle_urbs);
		usb_मुक्त_urb(urb);
		n--;
	पूर्ण
	वापस 0;
पूर्ण

/* ----- IEEE 802.15.4 पूर्णांकerface operations -------------------------------- */

अटल व्योम atusb_xmit_complete(काष्ठा urb *urb)
अणु
	dev_dbg(&urb->dev->dev, "atusb_xmit urb completed");
पूर्ण

अटल पूर्णांक atusb_xmit(काष्ठा ieee802154_hw *hw, काष्ठा sk_buff *skb)
अणु
	काष्ठा atusb *atusb = hw->priv;
	काष्ठा usb_device *usb_dev = atusb->usb_dev;
	पूर्णांक ret;

	dev_dbg(&usb_dev->dev, "%s (%d)\n", __func__, skb->len);
	atusb->tx_skb = skb;
	atusb->tx_ack_seq++;
	atusb->tx_dr.wIndex = cpu_to_le16(atusb->tx_ack_seq);
	atusb->tx_dr.wLength = cpu_to_le16(skb->len);

	usb_fill_control_urb(atusb->tx_urb, usb_dev,
			     usb_sndctrlpipe(usb_dev, 0),
			     (अचिन्हित अक्षर *)&atusb->tx_dr, skb->data,
			     skb->len, atusb_xmit_complete, शून्य);
	ret = usb_submit_urb(atusb->tx_urb, GFP_ATOMIC);
	dev_dbg(&usb_dev->dev, "%s done (%d)\n", __func__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक atusb_ed(काष्ठा ieee802154_hw *hw, u8 *level)
अणु
	WARN_ON(!level);
	*level = 0xbe;
	वापस 0;
पूर्ण

अटल पूर्णांक atusb_set_hw_addr_filt(काष्ठा ieee802154_hw *hw,
				  काष्ठा ieee802154_hw_addr_filt *filt,
				  अचिन्हित दीर्घ changed)
अणु
	काष्ठा atusb *atusb = hw->priv;
	काष्ठा device *dev = &atusb->usb_dev->dev;

	अगर (changed & IEEE802154_AFILT_SADDR_CHANGED) अणु
		u16 addr = le16_to_cpu(filt->लघु_addr);

		dev_vdbg(dev, "%s called for saddr\n", __func__);
		atusb_ग_लिखो_reg(atusb, RG_SHORT_ADDR_0, addr);
		atusb_ग_लिखो_reg(atusb, RG_SHORT_ADDR_1, addr >> 8);
	पूर्ण

	अगर (changed & IEEE802154_AFILT_PANID_CHANGED) अणु
		u16 pan = le16_to_cpu(filt->pan_id);

		dev_vdbg(dev, "%s called for pan id\n", __func__);
		atusb_ग_लिखो_reg(atusb, RG_PAN_ID_0, pan);
		atusb_ग_लिखो_reg(atusb, RG_PAN_ID_1, pan >> 8);
	पूर्ण

	अगर (changed & IEEE802154_AFILT_IEEEADDR_CHANGED) अणु
		u8 i, addr[IEEE802154_EXTENDED_ADDR_LEN];

		स_नकल(addr, &filt->ieee_addr, IEEE802154_EXTENDED_ADDR_LEN);
		dev_vdbg(dev, "%s called for IEEE addr\n", __func__);
		क्रम (i = 0; i < 8; i++)
			atusb_ग_लिखो_reg(atusb, RG_IEEE_ADDR_0 + i, addr[i]);
	पूर्ण

	अगर (changed & IEEE802154_AFILT_PANC_CHANGED) अणु
		dev_vdbg(dev, "%s called for panc change\n", __func__);
		अगर (filt->pan_coord)
			atusb_ग_लिखो_subreg(atusb, SR_AACK_I_AM_COORD, 1);
		अन्यथा
			atusb_ग_लिखो_subreg(atusb, SR_AACK_I_AM_COORD, 0);
	पूर्ण

	वापस atusb_get_and_clear_error(atusb);
पूर्ण

अटल पूर्णांक atusb_start(काष्ठा ieee802154_hw *hw)
अणु
	काष्ठा atusb *atusb = hw->priv;
	काष्ठा usb_device *usb_dev = atusb->usb_dev;
	पूर्णांक ret;

	dev_dbg(&usb_dev->dev, "%s\n", __func__);
	schedule_delayed_work(&atusb->work, 0);
	atusb_command(atusb, ATUSB_RX_MODE, 1);
	ret = atusb_get_and_clear_error(atusb);
	अगर (ret < 0)
		usb_समाप्त_anchored_urbs(&atusb->idle_urbs);
	वापस ret;
पूर्ण

अटल व्योम atusb_stop(काष्ठा ieee802154_hw *hw)
अणु
	काष्ठा atusb *atusb = hw->priv;
	काष्ठा usb_device *usb_dev = atusb->usb_dev;

	dev_dbg(&usb_dev->dev, "%s\n", __func__);
	usb_समाप्त_anchored_urbs(&atusb->idle_urbs);
	atusb_command(atusb, ATUSB_RX_MODE, 0);
	atusb_get_and_clear_error(atusb);
पूर्ण

#घोषणा ATUSB_MAX_TX_POWERS 0xF
अटल स्थिर s32 atusb_घातers[ATUSB_MAX_TX_POWERS + 1] = अणु
	300, 280, 230, 180, 130, 70, 0, -100, -200, -300, -400, -500, -700,
	-900, -1200, -1700,
पूर्ण;

अटल पूर्णांक
atusb_txघातer(काष्ठा ieee802154_hw *hw, s32 mbm)
अणु
	काष्ठा atusb *atusb = hw->priv;

	अगर (atusb->data)
		वापस atusb->data->set_txघातer(hw, mbm);
	अन्यथा
		वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक
atusb_set_txघातer(काष्ठा ieee802154_hw *hw, s32 mbm)
अणु
	काष्ठा atusb *atusb = hw->priv;
	u32 i;

	क्रम (i = 0; i < hw->phy->supported.tx_घातers_size; i++) अणु
		अगर (hw->phy->supported.tx_घातers[i] == mbm)
			वापस atusb_ग_लिखो_subreg(atusb, SR_TX_PWR_23X, i);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
hulusb_set_txघातer(काष्ठा ieee802154_hw *hw, s32 mbm)
अणु
	u32 i;

	क्रम (i = 0; i < hw->phy->supported.tx_घातers_size; i++) अणु
		अगर (hw->phy->supported.tx_घातers[i] == mbm)
			वापस atusb_ग_लिखो_subreg(hw->priv, SR_TX_PWR_212, i);
	पूर्ण

	वापस -EINVAL;
पूर्ण

#घोषणा ATUSB_MAX_ED_LEVELS 0xF
अटल स्थिर s32 atusb_ed_levels[ATUSB_MAX_ED_LEVELS + 1] = अणु
	-9100, -8900, -8700, -8500, -8300, -8100, -7900, -7700, -7500, -7300,
	-7100, -6900, -6700, -6500, -6300, -6100,
पूर्ण;

#घोषणा AT86RF212_MAX_TX_POWERS 0x1F
अटल स्थिर s32 at86rf212_घातers[AT86RF212_MAX_TX_POWERS + 1] = अणु
	500, 400, 300, 200, 100, 0, -100, -200, -300, -400, -500, -600, -700,
	-800, -900, -1000, -1100, -1200, -1300, -1400, -1500, -1600, -1700,
	-1800, -1900, -2000, -2100, -2200, -2300, -2400, -2500, -2600,
पूर्ण;

#घोषणा AT86RF2XX_MAX_ED_LEVELS 0xF
अटल स्थिर s32 at86rf212_ed_levels_100[AT86RF2XX_MAX_ED_LEVELS + 1] = अणु
	-10000, -9800, -9600, -9400, -9200, -9000, -8800, -8600, -8400, -8200,
	-8000, -7800, -7600, -7400, -7200, -7000,
पूर्ण;

अटल स्थिर s32 at86rf212_ed_levels_98[AT86RF2XX_MAX_ED_LEVELS + 1] = अणु
	-9800, -9600, -9400, -9200, -9000, -8800, -8600, -8400, -8200, -8000,
	-7800, -7600, -7400, -7200, -7000, -6800,
पूर्ण;

अटल पूर्णांक
atusb_set_cca_mode(काष्ठा ieee802154_hw *hw, स्थिर काष्ठा wpan_phy_cca *cca)
अणु
	काष्ठा atusb *atusb = hw->priv;
	u8 val;

	/* mapping 802.15.4 to driver spec */
	चयन (cca->mode) अणु
	हाल NL802154_CCA_ENERGY:
		val = 1;
		अवरोध;
	हाल NL802154_CCA_CARRIER:
		val = 2;
		अवरोध;
	हाल NL802154_CCA_ENERGY_CARRIER:
		चयन (cca->opt) अणु
		हाल NL802154_CCA_OPT_ENERGY_CARRIER_AND:
			val = 3;
			अवरोध;
		हाल NL802154_CCA_OPT_ENERGY_CARRIER_OR:
			val = 0;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस atusb_ग_लिखो_subreg(atusb, SR_CCA_MODE, val);
पूर्ण

अटल पूर्णांक hulusb_set_cca_ed_level(काष्ठा atusb *lp, पूर्णांक rssi_base_val)
अणु
	अचिन्हित पूर्णांक cca_ed_thres;

	cca_ed_thres = atusb_पढ़ो_subreg(lp, SR_CCA_ED_THRES);

	चयन (rssi_base_val) अणु
	हाल -98:
		lp->hw->phy->supported.cca_ed_levels = at86rf212_ed_levels_98;
		lp->hw->phy->supported.cca_ed_levels_size = ARRAY_SIZE(at86rf212_ed_levels_98);
		lp->hw->phy->cca_ed_level = at86rf212_ed_levels_98[cca_ed_thres];
		अवरोध;
	हाल -100:
		lp->hw->phy->supported.cca_ed_levels = at86rf212_ed_levels_100;
		lp->hw->phy->supported.cca_ed_levels_size = ARRAY_SIZE(at86rf212_ed_levels_100);
		lp->hw->phy->cca_ed_level = at86rf212_ed_levels_100[cca_ed_thres];
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
atusb_set_cca_ed_level(काष्ठा ieee802154_hw *hw, s32 mbm)
अणु
	काष्ठा atusb *atusb = hw->priv;
	u32 i;

	क्रम (i = 0; i < hw->phy->supported.cca_ed_levels_size; i++) अणु
		अगर (hw->phy->supported.cca_ed_levels[i] == mbm)
			वापस atusb_ग_लिखो_subreg(atusb, SR_CCA_ED_THRES, i);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक atusb_channel(काष्ठा ieee802154_hw *hw, u8 page, u8 channel)
अणु
	काष्ठा atusb *atusb = hw->priv;
	पूर्णांक ret = -ENOTSUPP;

	अगर (atusb->data) अणु
		ret = atusb->data->set_channel(hw, page, channel);
		/* @@@ ugly synchronization */
		msleep(atusb->data->t_channel_चयन);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक atusb_set_channel(काष्ठा ieee802154_hw *hw, u8 page, u8 channel)
अणु
	काष्ठा atusb *atusb = hw->priv;
	पूर्णांक ret;

	ret = atusb_ग_लिखो_subreg(atusb, SR_CHANNEL, channel);
	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण

अटल पूर्णांक hulusb_set_channel(काष्ठा ieee802154_hw *hw, u8 page, u8 channel)
अणु
	पूर्णांक rc;
	पूर्णांक rssi_base_val;

	काष्ठा atusb *lp = hw->priv;

	अगर (channel == 0)
		rc = atusb_ग_लिखो_subreg(lp, SR_SUB_MODE, 0);
	अन्यथा
		rc = atusb_ग_लिखो_subreg(lp, SR_SUB_MODE, 1);
	अगर (rc < 0)
		वापस rc;

	अगर (page == 0) अणु
		rc = atusb_ग_लिखो_subreg(lp, SR_BPSK_QPSK, 0);
		rssi_base_val = -100;
	पूर्ण अन्यथा अणु
		rc = atusb_ग_लिखो_subreg(lp, SR_BPSK_QPSK, 1);
		rssi_base_val = -98;
	पूर्ण
	अगर (rc < 0)
		वापस rc;

	rc = hulusb_set_cca_ed_level(lp, rssi_base_val);
	अगर (rc < 0)
		वापस rc;

	/* This sets the symbol_duration according frequency on the 212.
	 * TODO move this handling जबतक set channel and page in cfg802154.
	 * We can करो that, this timings are according 802.15.4 standard.
	 * If we करो that in cfg802154, this is a more generic calculation.
	 *
	 * This should also रक्षित from अगरs_समयr. Means cancel समयr and
	 * init with a new value. For now, this is okay.
	 */
	अगर (channel == 0) अणु
		अगर (page == 0) अणु
			/* SUB:0 and BPSK:0 -> BPSK-20 */
			lp->hw->phy->symbol_duration = 50;
		पूर्ण अन्यथा अणु
			/* SUB:1 and BPSK:0 -> BPSK-40 */
			lp->hw->phy->symbol_duration = 25;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (page == 0)
			/* SUB:0 and BPSK:1 -> OQPSK-100/200/400 */
			lp->hw->phy->symbol_duration = 40;
		अन्यथा
			/* SUB:1 and BPSK:1 -> OQPSK-250/500/1000 */
			lp->hw->phy->symbol_duration = 16;
	पूर्ण

	lp->hw->phy->lअगरs_period = IEEE802154_LIFS_PERIOD *
				   lp->hw->phy->symbol_duration;
	lp->hw->phy->sअगरs_period = IEEE802154_SIFS_PERIOD *
				   lp->hw->phy->symbol_duration;

	वापस atusb_ग_लिखो_subreg(lp, SR_CHANNEL, channel);
पूर्ण

अटल पूर्णांक
atusb_set_csma_params(काष्ठा ieee802154_hw *hw, u8 min_be, u8 max_be, u8 retries)
अणु
	काष्ठा atusb *atusb = hw->priv;
	पूर्णांक ret;

	ret = atusb_ग_लिखो_subreg(atusb, SR_MIN_BE, min_be);
	अगर (ret)
		वापस ret;

	ret = atusb_ग_लिखो_subreg(atusb, SR_MAX_BE, max_be);
	अगर (ret)
		वापस ret;

	वापस atusb_ग_लिखो_subreg(atusb, SR_MAX_CSMA_RETRIES, retries);
पूर्ण

अटल पूर्णांक
hulusb_set_lbt(काष्ठा ieee802154_hw *hw, bool on)
अणु
	काष्ठा atusb *atusb = hw->priv;

	वापस atusb_ग_लिखो_subreg(atusb, SR_CSMA_LBT_MODE, on);
पूर्ण

अटल पूर्णांक
atusb_set_frame_retries(काष्ठा ieee802154_hw *hw, s8 retries)
अणु
	काष्ठा atusb *atusb = hw->priv;

	वापस atusb_ग_लिखो_subreg(atusb, SR_MAX_FRAME_RETRIES, retries);
पूर्ण

अटल पूर्णांक
atusb_set_promiscuous_mode(काष्ठा ieee802154_hw *hw, स्थिर bool on)
अणु
	काष्ठा atusb *atusb = hw->priv;
	पूर्णांक ret;

	अगर (on) अणु
		ret = atusb_ग_लिखो_subreg(atusb, SR_AACK_DIS_ACK, 1);
		अगर (ret < 0)
			वापस ret;

		ret = atusb_ग_लिखो_subreg(atusb, SR_AACK_PROM_MODE, 1);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = atusb_ग_लिखो_subreg(atusb, SR_AACK_PROM_MODE, 0);
		अगर (ret < 0)
			वापस ret;

		ret = atusb_ग_लिखो_subreg(atusb, SR_AACK_DIS_ACK, 0);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा atusb_chip_data atusb_chip_data = अणु
	.t_channel_चयन = 1,
	.rssi_base_val = -91,
	.set_txघातer = atusb_set_txघातer,
	.set_channel = atusb_set_channel,
पूर्ण;

अटल काष्ठा atusb_chip_data hulusb_chip_data = अणु
	.t_channel_चयन = 11,
	.rssi_base_val = -100,
	.set_txघातer = hulusb_set_txघातer,
	.set_channel = hulusb_set_channel,
पूर्ण;

अटल स्थिर काष्ठा ieee802154_ops atusb_ops = अणु
	.owner			= THIS_MODULE,
	.xmit_async		= atusb_xmit,
	.ed			= atusb_ed,
	.set_channel		= atusb_channel,
	.start			= atusb_start,
	.stop			= atusb_stop,
	.set_hw_addr_filt	= atusb_set_hw_addr_filt,
	.set_txघातer		= atusb_txघातer,
	.set_lbt		= hulusb_set_lbt,
	.set_cca_mode		= atusb_set_cca_mode,
	.set_cca_ed_level	= atusb_set_cca_ed_level,
	.set_csma_params	= atusb_set_csma_params,
	.set_frame_retries	= atusb_set_frame_retries,
	.set_promiscuous_mode	= atusb_set_promiscuous_mode,
पूर्ण;

/* ----- Firmware and chip version inक्रमmation ----------------------------- */

अटल पूर्णांक atusb_get_and_show_revision(काष्ठा atusb *atusb)
अणु
	काष्ठा usb_device *usb_dev = atusb->usb_dev;
	अक्षर *hw_name;
	अचिन्हित अक्षर *buffer;
	पूर्णांक ret;

	buffer = kदो_स्मृति(3, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	/* Get a couple of the ATMega Firmware values */
	ret = atusb_control_msg(atusb, usb_rcvctrlpipe(usb_dev, 0),
				ATUSB_ID, ATUSB_REQ_FROM_DEV, 0, 0,
				buffer, 3, 1000);
	अगर (ret >= 0) अणु
		atusb->fw_ver_maj = buffer[0];
		atusb->fw_ver_min = buffer[1];
		atusb->fw_hw_type = buffer[2];

		चयन (atusb->fw_hw_type) अणु
		हाल ATUSB_HW_TYPE_100813:
		हाल ATUSB_HW_TYPE_101216:
		हाल ATUSB_HW_TYPE_110131:
			hw_name = "ATUSB";
			atusb->data = &atusb_chip_data;
			अवरोध;
		हाल ATUSB_HW_TYPE_RZUSB:
			hw_name = "RZUSB";
			atusb->data = &atusb_chip_data;
			अवरोध;
		हाल ATUSB_HW_TYPE_HULUSB:
			hw_name = "HULUSB";
			atusb->data = &hulusb_chip_data;
			अवरोध;
		शेष:
			hw_name = "UNKNOWN";
			atusb->err = -ENOTSUPP;
			ret = -ENOTSUPP;
			अवरोध;
		पूर्ण

		dev_info(&usb_dev->dev,
			 "Firmware: major: %u, minor: %u, hardware type: %s (%d)\n",
			 atusb->fw_ver_maj, atusb->fw_ver_min, hw_name,
			 atusb->fw_hw_type);
	पूर्ण
	अगर (atusb->fw_ver_maj == 0 && atusb->fw_ver_min < 2) अणु
		dev_info(&usb_dev->dev,
			 "Firmware version (%u.%u) predates our first public release.",
			 atusb->fw_ver_maj, atusb->fw_ver_min);
		dev_info(&usb_dev->dev, "Please update to version 0.2 or newer");
	पूर्ण

	kमुक्त(buffer);
	वापस ret;
पूर्ण

अटल पूर्णांक atusb_get_and_show_build(काष्ठा atusb *atusb)
अणु
	काष्ठा usb_device *usb_dev = atusb->usb_dev;
	अक्षर *build;
	पूर्णांक ret;

	build = kदो_स्मृति(ATUSB_BUILD_SIZE + 1, GFP_KERNEL);
	अगर (!build)
		वापस -ENOMEM;

	ret = atusb_control_msg(atusb, usb_rcvctrlpipe(usb_dev, 0),
				ATUSB_BUILD, ATUSB_REQ_FROM_DEV, 0, 0,
				build, ATUSB_BUILD_SIZE, 1000);
	अगर (ret >= 0) अणु
		build[ret] = 0;
		dev_info(&usb_dev->dev, "Firmware: build %s\n", build);
	पूर्ण

	kमुक्त(build);
	वापस ret;
पूर्ण

अटल पूर्णांक atusb_get_and_conf_chip(काष्ठा atusb *atusb)
अणु
	काष्ठा usb_device *usb_dev = atusb->usb_dev;
	u8 man_id_0, man_id_1, part_num, version_num;
	स्थिर अक्षर *chip;
	काष्ठा ieee802154_hw *hw = atusb->hw;

	man_id_0 = atusb_पढ़ो_reg(atusb, RG_MAN_ID_0);
	man_id_1 = atusb_पढ़ो_reg(atusb, RG_MAN_ID_1);
	part_num = atusb_पढ़ो_reg(atusb, RG_PART_NUM);
	version_num = atusb_पढ़ो_reg(atusb, RG_VERSION_NUM);

	अगर (atusb->err)
		वापस atusb->err;

	hw->flags = IEEE802154_HW_TX_OMIT_CKSUM | IEEE802154_HW_AFILT |
		    IEEE802154_HW_PROMISCUOUS | IEEE802154_HW_CSMA_PARAMS;

	hw->phy->flags = WPAN_PHY_FLAG_TXPOWER | WPAN_PHY_FLAG_CCA_ED_LEVEL |
			 WPAN_PHY_FLAG_CCA_MODE;

	hw->phy->supported.cca_modes = BIT(NL802154_CCA_ENERGY) |
				       BIT(NL802154_CCA_CARRIER) |
				       BIT(NL802154_CCA_ENERGY_CARRIER);
	hw->phy->supported.cca_opts = BIT(NL802154_CCA_OPT_ENERGY_CARRIER_AND) |
				      BIT(NL802154_CCA_OPT_ENERGY_CARRIER_OR);

	hw->phy->cca.mode = NL802154_CCA_ENERGY;

	hw->phy->current_page = 0;

	अगर ((man_id_1 << 8 | man_id_0) != ATUSB_JEDEC_ATMEL) अणु
		dev_err(&usb_dev->dev,
			"non-Atmel transceiver xxxx%02x%02x\n",
			man_id_1, man_id_0);
		जाओ fail;
	पूर्ण

	चयन (part_num) अणु
	हाल 2:
		chip = "AT86RF230";
		atusb->hw->phy->supported.channels[0] = 0x7FFF800;
		atusb->hw->phy->current_channel = 11;	/* reset शेष */
		atusb->hw->phy->symbol_duration = 16;
		atusb->hw->phy->supported.tx_घातers = atusb_घातers;
		atusb->hw->phy->supported.tx_घातers_size = ARRAY_SIZE(atusb_घातers);
		hw->phy->supported.cca_ed_levels = atusb_ed_levels;
		hw->phy->supported.cca_ed_levels_size = ARRAY_SIZE(atusb_ed_levels);
		अवरोध;
	हाल 3:
		chip = "AT86RF231";
		atusb->hw->phy->supported.channels[0] = 0x7FFF800;
		atusb->hw->phy->current_channel = 11;	/* reset शेष */
		atusb->hw->phy->symbol_duration = 16;
		atusb->hw->phy->supported.tx_घातers = atusb_घातers;
		atusb->hw->phy->supported.tx_घातers_size = ARRAY_SIZE(atusb_घातers);
		hw->phy->supported.cca_ed_levels = atusb_ed_levels;
		hw->phy->supported.cca_ed_levels_size = ARRAY_SIZE(atusb_ed_levels);
		अवरोध;
	हाल 7:
		chip = "AT86RF212";
		atusb->hw->flags |= IEEE802154_HW_LBT;
		atusb->hw->phy->supported.channels[0] = 0x00007FF;
		atusb->hw->phy->supported.channels[2] = 0x00007FF;
		atusb->hw->phy->current_channel = 5;
		atusb->hw->phy->symbol_duration = 25;
		atusb->hw->phy->supported.lbt = NL802154_SUPPORTED_BOOL_BOTH;
		atusb->hw->phy->supported.tx_घातers = at86rf212_घातers;
		atusb->hw->phy->supported.tx_घातers_size = ARRAY_SIZE(at86rf212_घातers);
		atusb->hw->phy->supported.cca_ed_levels = at86rf212_ed_levels_100;
		atusb->hw->phy->supported.cca_ed_levels_size = ARRAY_SIZE(at86rf212_ed_levels_100);
		अवरोध;
	शेष:
		dev_err(&usb_dev->dev,
			"unexpected transceiver, part 0x%02x version 0x%02x\n",
			part_num, version_num);
		जाओ fail;
	पूर्ण

	hw->phy->transmit_घातer = hw->phy->supported.tx_घातers[0];
	hw->phy->cca_ed_level = hw->phy->supported.cca_ed_levels[7];

	dev_info(&usb_dev->dev, "ATUSB: %s version %d\n", chip, version_num);

	वापस 0;

fail:
	atusb->err = -ENODEV;
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक atusb_set_extended_addr(काष्ठा atusb *atusb)
अणु
	काष्ठा usb_device *usb_dev = atusb->usb_dev;
	अचिन्हित अक्षर *buffer;
	__le64 extended_addr;
	u64 addr;
	पूर्णांक ret;

	/* Firmware versions beक्रमe 0.3 करो not support the EUI64_READ command.
	 * Just use a अक्रमom address and be करोne.
	 */
	अगर (atusb->fw_ver_maj == 0 && atusb->fw_ver_min < 3) अणु
		ieee802154_अक्रमom_extended_addr(&atusb->hw->phy->perm_extended_addr);
		वापस 0;
	पूर्ण

	buffer = kदो_स्मृति(IEEE802154_EXTENDED_ADDR_LEN, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	/* Firmware is new enough so we fetch the address from EEPROM */
	ret = atusb_control_msg(atusb, usb_rcvctrlpipe(usb_dev, 0),
				ATUSB_EUI64_READ, ATUSB_REQ_FROM_DEV, 0, 0,
				buffer, IEEE802154_EXTENDED_ADDR_LEN, 1000);
	अगर (ret < 0) अणु
		dev_err(&usb_dev->dev, "failed to fetch extended address, random address set\n");
		ieee802154_अक्रमom_extended_addr(&atusb->hw->phy->perm_extended_addr);
		kमुक्त(buffer);
		वापस ret;
	पूर्ण

	स_नकल(&extended_addr, buffer, IEEE802154_EXTENDED_ADDR_LEN);
	/* Check अगर पढ़ो address is not empty and the unicast bit is set correctly */
	अगर (!ieee802154_is_valid_extended_unicast_addr(extended_addr)) अणु
		dev_info(&usb_dev->dev, "no permanent extended address found, random address set\n");
		ieee802154_अक्रमom_extended_addr(&atusb->hw->phy->perm_extended_addr);
	पूर्ण अन्यथा अणु
		atusb->hw->phy->perm_extended_addr = extended_addr;
		addr = swab64((__क्रमce u64)atusb->hw->phy->perm_extended_addr);
		dev_info(&usb_dev->dev, "Read permanent extended address %8phC from device\n",
			 &addr);
	पूर्ण

	kमुक्त(buffer);
	वापस ret;
पूर्ण

/* ----- Setup ------------------------------------------------------------- */

अटल पूर्णांक atusb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
		       स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(पूर्णांकerface);
	काष्ठा ieee802154_hw *hw;
	काष्ठा atusb *atusb = शून्य;
	पूर्णांक ret = -ENOMEM;

	hw = ieee802154_alloc_hw(माप(काष्ठा atusb), &atusb_ops);
	अगर (!hw)
		वापस -ENOMEM;

	atusb = hw->priv;
	atusb->hw = hw;
	atusb->usb_dev = usb_get_dev(usb_dev);
	usb_set_पूर्णांकfdata(पूर्णांकerface, atusb);

	atusb->shutकरोwn = 0;
	atusb->err = 0;
	INIT_DELAYED_WORK(&atusb->work, atusb_work_urbs);
	init_usb_anchor(&atusb->idle_urbs);
	init_usb_anchor(&atusb->rx_urbs);

	अगर (atusb_alloc_urbs(atusb, ATUSB_NUM_RX_URBS))
		जाओ fail;

	atusb->tx_dr.bRequestType = ATUSB_REQ_TO_DEV;
	atusb->tx_dr.bRequest = ATUSB_TX;
	atusb->tx_dr.wValue = cpu_to_le16(0);

	atusb->tx_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!atusb->tx_urb)
		जाओ fail;

	hw->parent = &usb_dev->dev;

	atusb_command(atusb, ATUSB_RF_RESET, 0);
	atusb_get_and_conf_chip(atusb);
	atusb_get_and_show_revision(atusb);
	atusb_get_and_show_build(atusb);
	atusb_set_extended_addr(atusb);

	अगर ((atusb->fw_ver_maj == 0 && atusb->fw_ver_min >= 3) || atusb->fw_ver_maj > 0)
		hw->flags |= IEEE802154_HW_FRAME_RETRIES;

	ret = atusb_get_and_clear_error(atusb);
	अगर (ret) अणु
		dev_err(&atusb->usb_dev->dev,
			"%s: initialization failed, error = %d\n",
			__func__, ret);
		जाओ fail;
	पूर्ण

	ret = ieee802154_रेजिस्टर_hw(hw);
	अगर (ret)
		जाओ fail;

	/* If we just घातered on, we're now in P_ON and need to enter TRX_OFF
	 * explicitly. Any resets after that will send us straight to TRX_OFF,
	 * making the command below redundant.
	 */
	atusb_ग_लिखो_reg(atusb, RG_TRX_STATE, STATE_FORCE_TRX_OFF);
	msleep(1);	/* reset => TRX_OFF, tTR13 = 37 us */

#अगर 0
	/* Calculating the maximum समय available to empty the frame buffer
	 * on reception:
	 *
	 * According to [1], the पूर्णांकer-frame gap is
	 * R * 20 * 16 us + 128 us
	 * where R is a अक्रमom number from 0 to 7. Furthermore, we have 20 bit
	 * बार (80 us at 250 kbps) of SHR of the next frame beक्रमe the
	 * transceiver begins storing data in the frame buffer.
	 *
	 * This yields a minimum समय of 208 us between the last data of a
	 * frame and the first data of the next frame. This समय is further
	 * reduced by पूर्णांकerrupt latency in the atusb firmware.
	 *
	 * atusb currently needs about 500 us to retrieve a maximum-sized
	 * frame. We thereक्रमe have to allow reception of a new frame to begin
	 * जबतक we retrieve the previous frame.
	 *
	 * [1] "JN-AN-1035 Calculating data rates in an IEEE 802.15.4-based
	 *      network", Jennic 2006.
	 *     http://www.jennic.com/करोwnload_file.php?supportFile=JN-AN-1035%20Calculating%20802-15-4%20Data%20Rates-1v0.pdf
	 */

	atusb_ग_लिखो_subreg(atusb, SR_RX_SAFE_MODE, 1);
#पूर्ण_अगर
	atusb_ग_लिखो_reg(atusb, RG_IRQ_MASK, 0xff);

	ret = atusb_get_and_clear_error(atusb);
	अगर (!ret)
		वापस 0;

	dev_err(&atusb->usb_dev->dev,
		"%s: setup failed, error = %d\n",
		__func__, ret);

	ieee802154_unरेजिस्टर_hw(hw);
fail:
	atusb_मुक्त_urbs(atusb);
	usb_समाप्त_urb(atusb->tx_urb);
	usb_मुक्त_urb(atusb->tx_urb);
	usb_put_dev(usb_dev);
	ieee802154_मुक्त_hw(hw);
	वापस ret;
पूर्ण

अटल व्योम atusb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा atusb *atusb = usb_get_पूर्णांकfdata(पूर्णांकerface);

	dev_dbg(&atusb->usb_dev->dev, "%s\n", __func__);

	atusb->shutकरोwn = 1;
	cancel_delayed_work_sync(&atusb->work);

	usb_समाप्त_anchored_urbs(&atusb->rx_urbs);
	atusb_मुक्त_urbs(atusb);
	usb_समाप्त_urb(atusb->tx_urb);
	usb_मुक्त_urb(atusb->tx_urb);

	ieee802154_unरेजिस्टर_hw(atusb->hw);

	usb_put_dev(atusb->usb_dev);

	ieee802154_मुक्त_hw(atusb->hw);

	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);

	pr_debug("%s done\n", __func__);
पूर्ण

/* The devices we work with */
अटल स्थिर काष्ठा usb_device_id atusb_device_table[] = अणु
	अणु
		.match_flags		= USB_DEVICE_ID_MATCH_DEVICE |
					  USB_DEVICE_ID_MATCH_INT_INFO,
		.idVenकरोr		= ATUSB_VENDOR_ID,
		.idProduct		= ATUSB_PRODUCT_ID,
		.bInterfaceClass	= USB_CLASS_VENDOR_SPEC
	पूर्ण,
	/* end with null element */
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, atusb_device_table);

अटल काष्ठा usb_driver atusb_driver = अणु
	.name		= "atusb",
	.probe		= atusb_probe,
	.disconnect	= atusb_disconnect,
	.id_table	= atusb_device_table,
पूर्ण;
module_usb_driver(atusb_driver);

MODULE_AUTHOR("Alexander Aring <alex.aring@gmail.com>");
MODULE_AUTHOR("Richard Sharpe <realrichardsharpe@gmail.com>");
MODULE_AUTHOR("Stefan Schmidt <stefan@datenfreihafen.org>");
MODULE_AUTHOR("Werner Almesberger <werner@almesberger.net>");
MODULE_AUTHOR("Josef Filzmaier <j.filzmaier@gmx.at>");
MODULE_DESCRIPTION("ATUSB IEEE 802.15.4 Driver");
MODULE_LICENSE("GPL");
