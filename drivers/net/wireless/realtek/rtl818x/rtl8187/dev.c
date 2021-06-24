<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Linux device driver क्रम RTL8187
 *
 * Copyright 2007 Michael Wu <flamingice@sourmilk.net>
 * Copyright 2007 Andrea Merello <andrea.merello@gmail.com>
 *
 * Based on the r8187 driver, which is:
 * Copyright 2005 Andrea Merello <andrea.merello@gmail.com>, et al.
 *
 * The driver was extended to the RTL8187B in 2008 by:
 *	Herton Ronalकरो Krzesinski <herton@mandriva.com.br>
 *	Hin-Tak Leung <htl10@users.sourceक्रमge.net>
 *	Larry Finger <Larry.Finger@lwfinger.net>
 *
 * Magic delays and रेजिस्टर offsets below are taken from the original
 * r8187 driver sources.  Thanks to Realtek क्रम their support!
 */

#समावेश <linux/usb.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/eeprom_93cx6.h>
#समावेश <linux/module.h>
#समावेश <net/mac80211.h>

#समावेश "rtl8187.h"
#समावेश "rtl8225.h"
#अगर_घोषित CONFIG_RTL8187_LEDS
#समावेश "leds.h"
#पूर्ण_अगर
#समावेश "rfkill.h"

MODULE_AUTHOR("Michael Wu <flamingice@sourmilk.net>");
MODULE_AUTHOR("Andrea Merello <andrea.merello@gmail.com>");
MODULE_AUTHOR("Herton Ronaldo Krzesinski <herton@mandriva.com.br>");
MODULE_AUTHOR("Hin-Tak Leung <htl10@users.sourceforge.net>");
MODULE_AUTHOR("Larry Finger <Larry.Finger@lwfinger.net>");
MODULE_DESCRIPTION("RTL8187/RTL8187B USB wireless driver");
MODULE_LICENSE("GPL");

अटल स्थिर काष्ठा usb_device_id rtl8187_table[] = अणु
	/* Asus */
	अणुUSB_DEVICE(0x0b05, 0x171d), .driver_info = DEVICE_RTL8187पूर्ण,
	/* Belkin */
	अणुUSB_DEVICE(0x050d, 0x705e), .driver_info = DEVICE_RTL8187Bपूर्ण,
	/* Realtek */
	अणुUSB_DEVICE(0x0bda, 0x8187), .driver_info = DEVICE_RTL8187पूर्ण,
	अणुUSB_DEVICE(0x0bda, 0x8189), .driver_info = DEVICE_RTL8187Bपूर्ण,
	अणुUSB_DEVICE(0x0bda, 0x8197), .driver_info = DEVICE_RTL8187Bपूर्ण,
	अणुUSB_DEVICE(0x0bda, 0x8198), .driver_info = DEVICE_RTL8187Bपूर्ण,
	/* Surecom */
	अणुUSB_DEVICE(0x0769, 0x11F2), .driver_info = DEVICE_RTL8187पूर्ण,
	/* Logitech */
	अणुUSB_DEVICE(0x0789, 0x010C), .driver_info = DEVICE_RTL8187पूर्ण,
	/* Netgear */
	अणुUSB_DEVICE(0x0846, 0x6100), .driver_info = DEVICE_RTL8187पूर्ण,
	अणुUSB_DEVICE(0x0846, 0x6a00), .driver_info = DEVICE_RTL8187पूर्ण,
	अणुUSB_DEVICE(0x0846, 0x4260), .driver_info = DEVICE_RTL8187Bपूर्ण,
	/* HP */
	अणुUSB_DEVICE(0x03f0, 0xca02), .driver_info = DEVICE_RTL8187पूर्ण,
	/* Sitecom */
	अणुUSB_DEVICE(0x0df6, 0x000d), .driver_info = DEVICE_RTL8187पूर्ण,
	अणुUSB_DEVICE(0x0df6, 0x0028), .driver_info = DEVICE_RTL8187Bपूर्ण,
	अणुUSB_DEVICE(0x0df6, 0x0029), .driver_info = DEVICE_RTL8187Bपूर्ण,
	/* Sphairon Access Systems GmbH */
	अणुUSB_DEVICE(0x114B, 0x0150), .driver_info = DEVICE_RTL8187पूर्ण,
	/* Dick Smith Electronics */
	अणुUSB_DEVICE(0x1371, 0x9401), .driver_info = DEVICE_RTL8187पूर्ण,
	/* Abocom */
	अणुUSB_DEVICE(0x13d1, 0xabe6), .driver_info = DEVICE_RTL8187पूर्ण,
	/* Qcom */
	अणुUSB_DEVICE(0x18E8, 0x6232), .driver_info = DEVICE_RTL8187पूर्ण,
	/* AirLive */
	अणुUSB_DEVICE(0x1b75, 0x8187), .driver_info = DEVICE_RTL8187पूर्ण,
	/* Linksys */
	अणुUSB_DEVICE(0x1737, 0x0073), .driver_info = DEVICE_RTL8187Bपूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, rtl8187_table);

अटल स्थिर काष्ठा ieee80211_rate rtl818x_rates[] = अणु
	अणु .bitrate = 10, .hw_value = 0, पूर्ण,
	अणु .bitrate = 20, .hw_value = 1, पूर्ण,
	अणु .bitrate = 55, .hw_value = 2, पूर्ण,
	अणु .bitrate = 110, .hw_value = 3, पूर्ण,
	अणु .bitrate = 60, .hw_value = 4, पूर्ण,
	अणु .bitrate = 90, .hw_value = 5, पूर्ण,
	अणु .bitrate = 120, .hw_value = 6, पूर्ण,
	अणु .bitrate = 180, .hw_value = 7, पूर्ण,
	अणु .bitrate = 240, .hw_value = 8, पूर्ण,
	अणु .bitrate = 360, .hw_value = 9, पूर्ण,
	अणु .bitrate = 480, .hw_value = 10, पूर्ण,
	अणु .bitrate = 540, .hw_value = 11, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_channel rtl818x_channels[] = अणु
	अणु .center_freq = 2412 पूर्ण,
	अणु .center_freq = 2417 पूर्ण,
	अणु .center_freq = 2422 पूर्ण,
	अणु .center_freq = 2427 पूर्ण,
	अणु .center_freq = 2432 पूर्ण,
	अणु .center_freq = 2437 पूर्ण,
	अणु .center_freq = 2442 पूर्ण,
	अणु .center_freq = 2447 पूर्ण,
	अणु .center_freq = 2452 पूर्ण,
	अणु .center_freq = 2457 पूर्ण,
	अणु .center_freq = 2462 पूर्ण,
	अणु .center_freq = 2467 पूर्ण,
	अणु .center_freq = 2472 पूर्ण,
	अणु .center_freq = 2484 पूर्ण,
पूर्ण;

अटल व्योम rtl8187_ioग_लिखो_async_cb(काष्ठा urb *urb)
अणु
	kमुक्त(urb->context);
पूर्ण

अटल व्योम rtl8187_ioग_लिखो_async(काष्ठा rtl8187_priv *priv, __le16 addr,
				  व्योम *data, u16 len)
अणु
	काष्ठा usb_ctrlrequest *dr;
	काष्ठा urb *urb;
	काष्ठा rtl8187_async_ग_लिखो_data अणु
		u8 data[4];
		काष्ठा usb_ctrlrequest dr;
	पूर्ण *buf;
	पूर्णांक rc;

	buf = kदो_स्मृति(माप(*buf), GFP_ATOMIC);
	अगर (!buf)
		वापस;

	urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!urb) अणु
		kमुक्त(buf);
		वापस;
	पूर्ण

	dr = &buf->dr;

	dr->bRequestType = RTL8187_REQT_WRITE;
	dr->bRequest = RTL8187_REQ_SET_REG;
	dr->wValue = addr;
	dr->wIndex = 0;
	dr->wLength = cpu_to_le16(len);

	स_नकल(buf, data, len);

	usb_fill_control_urb(urb, priv->udev, usb_sndctrlpipe(priv->udev, 0),
			     (अचिन्हित अक्षर *)dr, buf, len,
			     rtl8187_ioग_लिखो_async_cb, buf);
	usb_anchor_urb(urb, &priv->anchored);
	rc = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (rc < 0) अणु
		kमुक्त(buf);
		usb_unanchor_urb(urb);
	पूर्ण
	usb_मुक्त_urb(urb);
पूर्ण

अटल अंतरभूत व्योम rtl818x_ioग_लिखो32_async(काष्ठा rtl8187_priv *priv,
					   __le32 *addr, u32 val)
अणु
	__le32 buf = cpu_to_le32(val);

	rtl8187_ioग_लिखो_async(priv, cpu_to_le16((अचिन्हित दीर्घ)addr),
			      &buf, माप(buf));
पूर्ण

व्योम rtl8187_ग_लिखो_phy(काष्ठा ieee80211_hw *dev, u8 addr, u32 data)
अणु
	काष्ठा rtl8187_priv *priv = dev->priv;

	data <<= 8;
	data |= addr | 0x80;

	rtl818x_ioग_लिखो8(priv, &priv->map->PHY[3], (data >> 24) & 0xFF);
	rtl818x_ioग_लिखो8(priv, &priv->map->PHY[2], (data >> 16) & 0xFF);
	rtl818x_ioग_लिखो8(priv, &priv->map->PHY[1], (data >> 8) & 0xFF);
	rtl818x_ioग_लिखो8(priv, &priv->map->PHY[0], data & 0xFF);
पूर्ण

अटल व्योम rtl8187_tx_cb(काष्ठा urb *urb)
अणु
	काष्ठा sk_buff *skb = (काष्ठा sk_buff *)urb->context;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_hw *hw = info->rate_driver_data[0];
	काष्ठा rtl8187_priv *priv = hw->priv;

	skb_pull(skb, priv->is_rtl8187b ? माप(काष्ठा rtl8187b_tx_hdr) :
					  माप(काष्ठा rtl8187_tx_hdr));
	ieee80211_tx_info_clear_status(info);

	अगर (!(urb->status) && !(info->flags & IEEE80211_TX_CTL_NO_ACK)) अणु
		अगर (priv->is_rtl8187b) अणु
			skb_queue_tail(&priv->b_tx_status.queue, skb);

			/* queue is "full", discard last items */
			जबतक (skb_queue_len(&priv->b_tx_status.queue) > 5) अणु
				काष्ठा sk_buff *old_skb;

				dev_dbg(&priv->udev->dev,
					"transmit status queue full\n");

				old_skb = skb_dequeue(&priv->b_tx_status.queue);
				ieee80211_tx_status_irqsafe(hw, old_skb);
			पूर्ण
			वापस;
		पूर्ण अन्यथा अणु
			info->flags |= IEEE80211_TX_STAT_ACK;
		पूर्ण
	पूर्ण
	अगर (priv->is_rtl8187b)
		ieee80211_tx_status_irqsafe(hw, skb);
	अन्यथा अणु
		/* Retry inक्रमmation क्रम the RTI8187 is only available by
		 * पढ़ोing a रेजिस्टर in the device. We are in पूर्णांकerrupt mode
		 * here, thus queue the skb and finish on a work queue. */
		skb_queue_tail(&priv->b_tx_status.queue, skb);
		ieee80211_queue_delayed_work(hw, &priv->work, 0);
	पूर्ण
पूर्ण

अटल व्योम rtl8187_tx(काष्ठा ieee80211_hw *dev,
		       काष्ठा ieee80211_tx_control *control,
		       काष्ठा sk_buff *skb)
अणु
	काष्ठा rtl8187_priv *priv = dev->priv;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_hdr *tx_hdr =	(काष्ठा ieee80211_hdr *)(skb->data);
	अचिन्हित पूर्णांक ep;
	व्योम *buf;
	काष्ठा urb *urb;
	__le16 rts_dur = 0;
	u32 flags;
	पूर्णांक rc;

	urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!urb) अणु
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	flags = skb->len;
	flags |= RTL818X_TX_DESC_FLAG_NO_ENC;

	flags |= ieee80211_get_tx_rate(dev, info)->hw_value << 24;
	अगर (ieee80211_has_morefrags(tx_hdr->frame_control))
		flags |= RTL818X_TX_DESC_FLAG_MOREFRAG;

	/* HW will perक्रमm RTS-CTS when only RTS flags is set.
	 * HW will perक्रमm CTS-to-self when both RTS and CTS flags are set.
	 * RTS rate and RTS duration will be used also क्रम CTS-to-self.
	 */
	अगर (info->control.rates[0].flags & IEEE80211_TX_RC_USE_RTS_CTS) अणु
		flags |= RTL818X_TX_DESC_FLAG_RTS;
		flags |= ieee80211_get_rts_cts_rate(dev, info)->hw_value << 19;
		rts_dur = ieee80211_rts_duration(dev, priv->vअगर,
						 skb->len, info);
	पूर्ण अन्यथा अगर (info->control.rates[0].flags & IEEE80211_TX_RC_USE_CTS_PROTECT) अणु
		flags |= RTL818X_TX_DESC_FLAG_RTS | RTL818X_TX_DESC_FLAG_CTS;
		flags |= ieee80211_get_rts_cts_rate(dev, info)->hw_value << 19;
		rts_dur = ieee80211_ctstoself_duration(dev, priv->vअगर,
						 skb->len, info);
	पूर्ण

	अगर (info->flags & IEEE80211_TX_CTL_ASSIGN_SEQ) अणु
		अगर (info->flags & IEEE80211_TX_CTL_FIRST_FRAGMENT)
			priv->seqno += 0x10;
		tx_hdr->seq_ctrl &= cpu_to_le16(IEEE80211_SCTL_FRAG);
		tx_hdr->seq_ctrl |= cpu_to_le16(priv->seqno);
	पूर्ण

	अगर (!priv->is_rtl8187b) अणु
		काष्ठा rtl8187_tx_hdr *hdr = skb_push(skb, माप(*hdr));
		hdr->flags = cpu_to_le32(flags);
		hdr->len = 0;
		hdr->rts_duration = rts_dur;
		hdr->retry = cpu_to_le32((info->control.rates[0].count - 1) << 8);
		buf = hdr;

		ep = 2;
	पूर्ण अन्यथा अणु
		/* fc needs to be calculated beक्रमe skb_push() */
		अचिन्हित पूर्णांक epmap[4] = अणु 6, 7, 5, 4 पूर्ण;
		u16 fc = le16_to_cpu(tx_hdr->frame_control);

		काष्ठा rtl8187b_tx_hdr *hdr = skb_push(skb, माप(*hdr));
		काष्ठा ieee80211_rate *txrate =
			ieee80211_get_tx_rate(dev, info);
		स_रखो(hdr, 0, माप(*hdr));
		hdr->flags = cpu_to_le32(flags);
		hdr->rts_duration = rts_dur;
		hdr->retry = cpu_to_le32((info->control.rates[0].count - 1) << 8);
		hdr->tx_duration =
			ieee80211_generic_frame_duration(dev, priv->vअगर,
							 info->band,
							 skb->len, txrate);
		buf = hdr;

		अगर ((fc & IEEE80211_FCTL_FTYPE) == IEEE80211_FTYPE_MGMT)
			ep = 12;
		अन्यथा
			ep = epmap[skb_get_queue_mapping(skb)];
	पूर्ण

	info->rate_driver_data[0] = dev;
	info->rate_driver_data[1] = urb;

	usb_fill_bulk_urb(urb, priv->udev, usb_sndbulkpipe(priv->udev, ep),
			  buf, skb->len, rtl8187_tx_cb, skb);
	urb->transfer_flags |= URB_ZERO_PACKET;
	usb_anchor_urb(urb, &priv->anchored);
	rc = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (rc < 0) अणु
		usb_unanchor_urb(urb);
		kमुक्त_skb(skb);
	पूर्ण
	usb_मुक्त_urb(urb);
पूर्ण

अटल व्योम rtl8187_rx_cb(काष्ठा urb *urb)
अणु
	काष्ठा sk_buff *skb = (काष्ठा sk_buff *)urb->context;
	काष्ठा rtl8187_rx_info *info = (काष्ठा rtl8187_rx_info *)skb->cb;
	काष्ठा ieee80211_hw *dev = info->dev;
	काष्ठा rtl8187_priv *priv = dev->priv;
	काष्ठा ieee80211_rx_status rx_status = अणु 0 पूर्ण;
	पूर्णांक rate, संकेत;
	u32 flags;
	अचिन्हित दीर्घ f;

	spin_lock_irqsave(&priv->rx_queue.lock, f);
	__skb_unlink(skb, &priv->rx_queue);
	spin_unlock_irqrestore(&priv->rx_queue.lock, f);
	skb_put(skb, urb->actual_length);

	अगर (unlikely(urb->status)) अणु
		dev_kमुक्त_skb_irq(skb);
		वापस;
	पूर्ण

	अगर (!priv->is_rtl8187b) अणु
		काष्ठा rtl8187_rx_hdr *hdr =
			(typeof(hdr))(skb_tail_poपूर्णांकer(skb) - माप(*hdr));
		flags = le32_to_cpu(hdr->flags);
		/* As with the RTL8187B below, the AGC is used to calculate
		 * संकेत strength. In this हाल, the scaling
		 * स्थिरants are derived from the output of p54usb.
		 */
		संकेत = -4 - ((27 * hdr->agc) >> 6);
		rx_status.antenna = (hdr->संकेत >> 7) & 1;
		rx_status.maस_समय = le64_to_cpu(hdr->mac_समय);
	पूर्ण अन्यथा अणु
		काष्ठा rtl8187b_rx_hdr *hdr =
			(typeof(hdr))(skb_tail_poपूर्णांकer(skb) - माप(*hdr));
		/* The Realtek datasheet क्रम the RTL8187B shows that the RX
		 * header contains the following quantities: संकेत quality,
		 * RSSI, AGC, the received घातer in dB, and the measured SNR.
		 * In testing, none of these quantities show qualitative
		 * agreement with AP संकेत strength, except क्रम the AGC,
		 * which is inversely proportional to the strength of the
		 * संकेत. In the following, the संकेत strength
		 * is derived from the AGC. The arbitrary scaling स्थिरants
		 * are chosen to make the results बंद to the values obtained
		 * क्रम a BCM4312 using b43 as the driver. The noise is ignored
		 * क्रम now.
		 */
		flags = le32_to_cpu(hdr->flags);
		संकेत = 14 - hdr->agc / 2;
		rx_status.antenna = (hdr->rssi >> 7) & 1;
		rx_status.maस_समय = le64_to_cpu(hdr->mac_समय);
	पूर्ण

	rx_status.संकेत = संकेत;
	priv->संकेत = संकेत;
	rate = (flags >> 20) & 0xF;
	skb_trim(skb, flags & 0x0FFF);
	rx_status.rate_idx = rate;
	rx_status.freq = dev->conf.chandef.chan->center_freq;
	rx_status.band = dev->conf.chandef.chan->band;
	rx_status.flag |= RX_FLAG_MACTIME_START;
	अगर (flags & RTL818X_RX_DESC_FLAG_SPLCP)
		rx_status.enc_flags |= RX_ENC_FLAG_SHORTPRE;
	अगर (flags & RTL818X_RX_DESC_FLAG_CRC32_ERR)
		rx_status.flag |= RX_FLAG_FAILED_FCS_CRC;
	स_नकल(IEEE80211_SKB_RXCB(skb), &rx_status, माप(rx_status));
	ieee80211_rx_irqsafe(dev, skb);

	skb = dev_alloc_skb(RTL8187_MAX_RX);
	अगर (unlikely(!skb)) अणु
		/* TODO check rx queue length and refill *somewhere* */
		वापस;
	पूर्ण

	info = (काष्ठा rtl8187_rx_info *)skb->cb;
	info->urb = urb;
	info->dev = dev;
	urb->transfer_buffer = skb_tail_poपूर्णांकer(skb);
	urb->context = skb;
	skb_queue_tail(&priv->rx_queue, skb);

	usb_anchor_urb(urb, &priv->anchored);
	अगर (usb_submit_urb(urb, GFP_ATOMIC)) अणु
		usb_unanchor_urb(urb);
		skb_unlink(skb, &priv->rx_queue);
		dev_kमुक्त_skb_irq(skb);
	पूर्ण
पूर्ण

अटल पूर्णांक rtl8187_init_urbs(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा rtl8187_priv *priv = dev->priv;
	काष्ठा urb *entry = शून्य;
	काष्ठा sk_buff *skb;
	काष्ठा rtl8187_rx_info *info;
	पूर्णांक ret = 0;

	जबतक (skb_queue_len(&priv->rx_queue) < 32) अणु
		skb = __dev_alloc_skb(RTL8187_MAX_RX, GFP_KERNEL);
		अगर (!skb) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण
		entry = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!entry) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण
		usb_fill_bulk_urb(entry, priv->udev,
				  usb_rcvbulkpipe(priv->udev,
				  priv->is_rtl8187b ? 3 : 1),
				  skb_tail_poपूर्णांकer(skb),
				  RTL8187_MAX_RX, rtl8187_rx_cb, skb);
		info = (काष्ठा rtl8187_rx_info *)skb->cb;
		info->urb = entry;
		info->dev = dev;
		skb_queue_tail(&priv->rx_queue, skb);
		usb_anchor_urb(entry, &priv->anchored);
		ret = usb_submit_urb(entry, GFP_KERNEL);
		अगर (ret) अणु
			skb_unlink(skb, &priv->rx_queue);
			usb_unanchor_urb(entry);
			usb_put_urb(entry);
			जाओ err;
		पूर्ण
		usb_put_urb(entry);
	पूर्ण
	वापस ret;

err:
	kमुक्त_skb(skb);
	usb_समाप्त_anchored_urbs(&priv->anchored);
	वापस ret;
पूर्ण

अटल व्योम rtl8187b_status_cb(काष्ठा urb *urb)
अणु
	काष्ठा ieee80211_hw *hw = (काष्ठा ieee80211_hw *)urb->context;
	काष्ठा rtl8187_priv *priv = hw->priv;
	u64 val;
	अचिन्हित पूर्णांक cmd_type;

	अगर (unlikely(urb->status))
		वापस;

	/*
	 * Read from status buffer:
	 *
	 * bits [30:31] = cmd type:
	 * - 0 indicates tx beacon पूर्णांकerrupt
	 * - 1 indicates tx बंद descriptor
	 *
	 * In the हाल of tx beacon पूर्णांकerrupt:
	 * [0:9] = Last Beacon CW
	 * [10:29] = reserved
	 * [30:31] = 00b
	 * [32:63] = Last Beacon TSF
	 *
	 * If it's tx बंद descriptor:
	 * [0:7] = Packet Retry Count
	 * [8:14] = RTS Retry Count
	 * [15] = TOK
	 * [16:27] = Sequence No
	 * [28] = LS
	 * [29] = FS
	 * [30:31] = 01b
	 * [32:47] = unused (reserved?)
	 * [48:63] = MAC Used Time
	 */
	val = le64_to_cpu(priv->b_tx_status.buf);

	cmd_type = (val >> 30) & 0x3;
	अगर (cmd_type == 1) अणु
		अचिन्हित पूर्णांक pkt_rc, seq_no;
		bool tok;
		काष्ठा sk_buff *skb, *iter;
		काष्ठा ieee80211_hdr *ieee80211hdr;
		अचिन्हित दीर्घ flags;

		pkt_rc = val & 0xFF;
		tok = val & (1 << 15);
		seq_no = (val >> 16) & 0xFFF;

		spin_lock_irqsave(&priv->b_tx_status.queue.lock, flags);
		skb = शून्य;
		skb_queue_reverse_walk(&priv->b_tx_status.queue, iter) अणु
			ieee80211hdr = (काष्ठा ieee80211_hdr *)iter->data;

			/*
			 * While testing, it was discovered that the seq_no
			 * करोesn't actually contains the sequence number.
			 * Instead of वापसing just the 12 bits of sequence
			 * number, hardware is वापसing entire sequence control
			 * (fragment number plus sequence number) in a 12 bit
			 * only field overflowing after some समय. As a
			 * workaround, just consider the lower bits, and expect
			 * it's unlikely we wrongly ack some sent data
			 */
			अगर ((le16_to_cpu(ieee80211hdr->seq_ctrl)
			     & 0xFFF) == seq_no) अणु
				skb = iter;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (skb) अणु
			काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

			__skb_unlink(skb, &priv->b_tx_status.queue);
			अगर (tok)
				info->flags |= IEEE80211_TX_STAT_ACK;
			info->status.rates[0].count = pkt_rc + 1;

			ieee80211_tx_status_irqsafe(hw, skb);
		पूर्ण
		spin_unlock_irqrestore(&priv->b_tx_status.queue.lock, flags);
	पूर्ण

	usb_anchor_urb(urb, &priv->anchored);
	अगर (usb_submit_urb(urb, GFP_ATOMIC))
		usb_unanchor_urb(urb);
पूर्ण

अटल पूर्णांक rtl8187b_init_status_urb(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा rtl8187_priv *priv = dev->priv;
	काष्ठा urb *entry;
	पूर्णांक ret = 0;

	entry = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	usb_fill_bulk_urb(entry, priv->udev, usb_rcvbulkpipe(priv->udev, 9),
			  &priv->b_tx_status.buf, माप(priv->b_tx_status.buf),
			  rtl8187b_status_cb, dev);

	usb_anchor_urb(entry, &priv->anchored);
	ret = usb_submit_urb(entry, GFP_KERNEL);
	अगर (ret)
		usb_unanchor_urb(entry);
	usb_मुक्त_urb(entry);

	वापस ret;
पूर्ण

अटल व्योम rtl8187_set_anaparam(काष्ठा rtl8187_priv *priv, bool rfon)
अणु
	u32 anaparam, anaparam2;
	u8 anaparam3, reg;

	अगर (!priv->is_rtl8187b) अणु
		अगर (rfon) अणु
			anaparam = RTL8187_RTL8225_ANAPARAM_ON;
			anaparam2 = RTL8187_RTL8225_ANAPARAM2_ON;
		पूर्ण अन्यथा अणु
			anaparam = RTL8187_RTL8225_ANAPARAM_OFF;
			anaparam2 = RTL8187_RTL8225_ANAPARAM2_OFF;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (rfon) अणु
			anaparam = RTL8187B_RTL8225_ANAPARAM_ON;
			anaparam2 = RTL8187B_RTL8225_ANAPARAM2_ON;
			anaparam3 = RTL8187B_RTL8225_ANAPARAM3_ON;
		पूर्ण अन्यथा अणु
			anaparam = RTL8187B_RTL8225_ANAPARAM_OFF;
			anaparam2 = RTL8187B_RTL8225_ANAPARAM2_OFF;
			anaparam3 = RTL8187B_RTL8225_ANAPARAM3_OFF;
		पूर्ण
	पूर्ण

	rtl818x_ioग_लिखो8(priv, &priv->map->EEPROM_CMD,
			 RTL818X_EEPROM_CMD_CONFIG);
	reg = rtl818x_ioपढ़ो8(priv, &priv->map->CONFIG3);
	reg |= RTL818X_CONFIG3_ANAPARAM_WRITE;
	rtl818x_ioग_लिखो8(priv, &priv->map->CONFIG3, reg);
	rtl818x_ioग_लिखो32(priv, &priv->map->ANAPARAM, anaparam);
	rtl818x_ioग_लिखो32(priv, &priv->map->ANAPARAM2, anaparam2);
	अगर (priv->is_rtl8187b)
		rtl818x_ioग_लिखो8(priv, &priv->map->ANAPARAM3A, anaparam3);
	reg &= ~RTL818X_CONFIG3_ANAPARAM_WRITE;
	rtl818x_ioग_लिखो8(priv, &priv->map->CONFIG3, reg);
	rtl818x_ioग_लिखो8(priv, &priv->map->EEPROM_CMD,
			 RTL818X_EEPROM_CMD_NORMAL);
पूर्ण

अटल पूर्णांक rtl8187_cmd_reset(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा rtl8187_priv *priv = dev->priv;
	u8 reg;
	पूर्णांक i;

	reg = rtl818x_ioपढ़ो8(priv, &priv->map->CMD);
	reg &= (1 << 1);
	reg |= RTL818X_CMD_RESET;
	rtl818x_ioग_लिखो8(priv, &priv->map->CMD, reg);

	i = 10;
	करो अणु
		msleep(2);
		अगर (!(rtl818x_ioपढ़ो8(priv, &priv->map->CMD) &
		      RTL818X_CMD_RESET))
			अवरोध;
	पूर्ण जबतक (--i);

	अगर (!i) अणु
		wiphy_err(dev->wiphy, "Reset timeout!\n");
		वापस -ETIMEDOUT;
	पूर्ण

	/* reload रेजिस्टरs from eeprom */
	rtl818x_ioग_लिखो8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_LOAD);

	i = 10;
	करो अणु
		msleep(4);
		अगर (!(rtl818x_ioपढ़ो8(priv, &priv->map->EEPROM_CMD) &
		      RTL818X_EEPROM_CMD_CONFIG))
			अवरोध;
	पूर्ण जबतक (--i);

	अगर (!i) अणु
		wiphy_err(dev->wiphy, "eeprom reset timeout!\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtl8187_init_hw(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा rtl8187_priv *priv = dev->priv;
	u8 reg;
	पूर्णांक res;

	/* reset */
	rtl8187_set_anaparam(priv, true);

	rtl818x_ioग_लिखो16(priv, &priv->map->INT_MASK, 0);

	msleep(200);
	rtl818x_ioग_लिखो8(priv, (u8 *)0xFE18, 0x10);
	rtl818x_ioग_लिखो8(priv, (u8 *)0xFE18, 0x11);
	rtl818x_ioग_लिखो8(priv, (u8 *)0xFE18, 0x00);
	msleep(200);

	res = rtl8187_cmd_reset(dev);
	अगर (res)
		वापस res;

	rtl8187_set_anaparam(priv, true);

	/* setup card */
	rtl818x_ioग_लिखो16(priv, &priv->map->RFPinsSelect, 0);
	rtl818x_ioग_लिखो8(priv, &priv->map->GPIO0, 0);

	rtl818x_ioग_लिखो16(priv, &priv->map->RFPinsSelect, (4 << 8));
	rtl818x_ioग_लिखो8(priv, &priv->map->GPIO0, 1);
	rtl818x_ioग_लिखो8(priv, &priv->map->GP_ENABLE, 0);

	rtl818x_ioग_लिखो8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_CONFIG);

	rtl818x_ioग_लिखो16(priv, (__le16 *)0xFFF4, 0xFFFF);
	reg = rtl818x_ioपढ़ो8(priv, &priv->map->CONFIG1);
	reg &= 0x3F;
	reg |= 0x80;
	rtl818x_ioग_लिखो8(priv, &priv->map->CONFIG1, reg);

	rtl818x_ioग_लिखो8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_NORMAL);

	rtl818x_ioग_लिखो32(priv, &priv->map->INT_TIMEOUT, 0);
	rtl818x_ioग_लिखो8(priv, &priv->map->WPA_CONF, 0);
	rtl818x_ioग_लिखो8(priv, &priv->map->RATE_FALLBACK, 0);

	// TODO: set RESP_RATE and BRSR properly
	rtl818x_ioग_लिखो8(priv, &priv->map->RESP_RATE, (8 << 4) | 0);
	rtl818x_ioग_लिखो16(priv, &priv->map->BRSR, 0x01F3);

	/* host_usb_init */
	rtl818x_ioग_लिखो16(priv, &priv->map->RFPinsSelect, 0);
	rtl818x_ioग_लिखो8(priv, &priv->map->GPIO0, 0);
	reg = rtl818x_ioपढ़ो8(priv, (u8 *)0xFE53);
	rtl818x_ioग_लिखो8(priv, (u8 *)0xFE53, reg | (1 << 7));
	rtl818x_ioग_लिखो16(priv, &priv->map->RFPinsSelect, (4 << 8));
	rtl818x_ioग_लिखो8(priv, &priv->map->GPIO0, 0x20);
	rtl818x_ioग_लिखो8(priv, &priv->map->GP_ENABLE, 0);
	rtl818x_ioग_लिखो16(priv, &priv->map->RFPinsOutput, 0x80);
	rtl818x_ioग_लिखो16(priv, &priv->map->RFPinsSelect, 0x80);
	rtl818x_ioग_लिखो16(priv, &priv->map->RFPinsEnable, 0x80);
	msleep(100);

	rtl818x_ioग_लिखो32(priv, &priv->map->RF_TIMING, 0x000a8008);
	rtl818x_ioग_लिखो16(priv, &priv->map->BRSR, 0xFFFF);
	rtl818x_ioग_लिखो32(priv, &priv->map->RF_PARA, 0x00100044);
	rtl818x_ioग_लिखो8(priv, &priv->map->EEPROM_CMD,
			 RTL818X_EEPROM_CMD_CONFIG);
	rtl818x_ioग_लिखो8(priv, &priv->map->CONFIG3, 0x44);
	rtl818x_ioग_लिखो8(priv, &priv->map->EEPROM_CMD,
			 RTL818X_EEPROM_CMD_NORMAL);
	rtl818x_ioग_लिखो16(priv, &priv->map->RFPinsEnable, 0x1FF7);
	msleep(100);

	priv->rf->init(dev);

	rtl818x_ioग_लिखो16(priv, &priv->map->BRSR, 0x01F3);
	reg = rtl818x_ioपढ़ो8(priv, &priv->map->PGSELECT) & ~1;
	rtl818x_ioग_लिखो8(priv, &priv->map->PGSELECT, reg | 1);
	rtl818x_ioग_लिखो16(priv, (__le16 *)0xFFFE, 0x10);
	rtl818x_ioग_लिखो8(priv, &priv->map->TALLY_SEL, 0x80);
	rtl818x_ioग_लिखो8(priv, (u8 *)0xFFFF, 0x60);
	rtl818x_ioग_लिखो8(priv, &priv->map->PGSELECT, reg);

	वापस 0;
पूर्ण

अटल स्थिर u8 rtl8187b_reg_table[][3] = अणु
	अणु0xF0, 0x32, 0पूर्ण, अणु0xF1, 0x32, 0पूर्ण, अणु0xF2, 0x00, 0पूर्ण, अणु0xF3, 0x00, 0पूर्ण,
	अणु0xF4, 0x32, 0पूर्ण, अणु0xF5, 0x43, 0पूर्ण, अणु0xF6, 0x00, 0पूर्ण, अणु0xF7, 0x00, 0पूर्ण,
	अणु0xF8, 0x46, 0पूर्ण, अणु0xF9, 0xA4, 0पूर्ण, अणु0xFA, 0x00, 0पूर्ण, अणु0xFB, 0x00, 0पूर्ण,
	अणु0xFC, 0x96, 0पूर्ण, अणु0xFD, 0xA4, 0पूर्ण, अणु0xFE, 0x00, 0पूर्ण, अणु0xFF, 0x00, 0पूर्ण,

	अणु0x58, 0x4B, 1पूर्ण, अणु0x59, 0x00, 1पूर्ण, अणु0x5A, 0x4B, 1पूर्ण, अणु0x5B, 0x00, 1पूर्ण,
	अणु0x60, 0x4B, 1पूर्ण, अणु0x61, 0x09, 1पूर्ण, अणु0x62, 0x4B, 1पूर्ण, अणु0x63, 0x09, 1पूर्ण,
	अणु0xCE, 0x0F, 1पूर्ण, अणु0xCF, 0x00, 1पूर्ण, अणु0xF0, 0x4E, 1पूर्ण, अणु0xF1, 0x01, 1पूर्ण,
	अणु0xF2, 0x02, 1पूर्ण, अणु0xF3, 0x03, 1पूर्ण, अणु0xF4, 0x04, 1पूर्ण, अणु0xF5, 0x05, 1पूर्ण,
	अणु0xF6, 0x06, 1पूर्ण, अणु0xF7, 0x07, 1पूर्ण, अणु0xF8, 0x08, 1पूर्ण,

	अणु0x4E, 0x00, 2पूर्ण, अणु0x0C, 0x04, 2पूर्ण, अणु0x21, 0x61, 2पूर्ण, अणु0x22, 0x68, 2पूर्ण,
	अणु0x23, 0x6F, 2पूर्ण, अणु0x24, 0x76, 2पूर्ण, अणु0x25, 0x7D, 2पूर्ण, अणु0x26, 0x84, 2पूर्ण,
	अणु0x27, 0x8D, 2पूर्ण, अणु0x4D, 0x08, 2पूर्ण, अणु0x50, 0x05, 2पूर्ण, अणु0x51, 0xF5, 2पूर्ण,
	अणु0x52, 0x04, 2पूर्ण, अणु0x53, 0xA0, 2पूर्ण, अणु0x54, 0x1F, 2पूर्ण, अणु0x55, 0x23, 2पूर्ण,
	अणु0x56, 0x45, 2पूर्ण, अणु0x57, 0x67, 2पूर्ण, अणु0x58, 0x08, 2पूर्ण, अणु0x59, 0x08, 2पूर्ण,
	अणु0x5A, 0x08, 2पूर्ण, अणु0x5B, 0x08, 2पूर्ण, अणु0x60, 0x08, 2पूर्ण, अणु0x61, 0x08, 2पूर्ण,
	अणु0x62, 0x08, 2पूर्ण, अणु0x63, 0x08, 2पूर्ण, अणु0x64, 0xCF, 2पूर्ण,

	अणु0x5B, 0x40, 0पूर्ण, अणु0x84, 0x88, 0पूर्ण, अणु0x85, 0x24, 0पूर्ण, अणु0x88, 0x54, 0पूर्ण,
	अणु0x8B, 0xB8, 0पूर्ण, अणु0x8C, 0x07, 0पूर्ण, अणु0x8D, 0x00, 0पूर्ण, अणु0x94, 0x1B, 0पूर्ण,
	अणु0x95, 0x12, 0पूर्ण, अणु0x96, 0x00, 0पूर्ण, अणु0x97, 0x06, 0पूर्ण, अणु0x9D, 0x1A, 0पूर्ण,
	अणु0x9F, 0x10, 0पूर्ण, अणु0xB4, 0x22, 0पूर्ण, अणु0xBE, 0x80, 0पूर्ण, अणु0xDB, 0x00, 0पूर्ण,
	अणु0xEE, 0x00, 0पूर्ण, अणु0x4C, 0x00, 2पूर्ण,

	अणु0x9F, 0x00, 3पूर्ण, अणु0x8C, 0x01, 0पूर्ण, अणु0x8D, 0x10, 0पूर्ण, अणु0x8E, 0x08, 0पूर्ण,
	अणु0x8F, 0x00, 0पूर्ण
पूर्ण;

अटल पूर्णांक rtl8187b_init_hw(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा rtl8187_priv *priv = dev->priv;
	पूर्णांक res, i;
	u8 reg;

	rtl8187_set_anaparam(priv, true);

	/* Reset PLL sequence on 8187B. Realtek note: reduces घातer
	 * consumption about 30 mA */
	rtl818x_ioग_लिखो8(priv, (u8 *)0xFF61, 0x10);
	reg = rtl818x_ioपढ़ो8(priv, (u8 *)0xFF62);
	rtl818x_ioग_लिखो8(priv, (u8 *)0xFF62, reg & ~(1 << 5));
	rtl818x_ioग_लिखो8(priv, (u8 *)0xFF62, reg | (1 << 5));

	res = rtl8187_cmd_reset(dev);
	अगर (res)
		वापस res;

	rtl8187_set_anaparam(priv, true);

	/* BRSR (Basic Rate Set Register) on 8187B looks to be the same as
	 * RESP_RATE on 8187L in Realtek sources: each bit should be each
	 * one of the 12 rates, all are enabled */
	rtl818x_ioग_लिखो16(priv, (__le16 *)0xFF34, 0x0FFF);

	reg = rtl818x_ioपढ़ो8(priv, &priv->map->CW_CONF);
	reg |= RTL818X_CW_CONF_PERPACKET_RETRY;
	rtl818x_ioग_लिखो8(priv, &priv->map->CW_CONF, reg);

	/* Auto Rate Fallback Register (ARFR): 1M-54M setting */
	rtl818x_ioग_लिखो16_idx(priv, (__le16 *)0xFFE0, 0x0FFF, 1);
	rtl818x_ioग_लिखो8_idx(priv, (u8 *)0xFFE2, 0x00, 1);

	rtl818x_ioग_लिखो16_idx(priv, (__le16 *)0xFFD4, 0xFFFF, 1);

	rtl818x_ioग_लिखो8(priv, &priv->map->EEPROM_CMD,
			 RTL818X_EEPROM_CMD_CONFIG);
	reg = rtl818x_ioपढ़ो8(priv, &priv->map->CONFIG1);
	rtl818x_ioग_लिखो8(priv, &priv->map->CONFIG1, (reg & 0x3F) | 0x80);
	rtl818x_ioग_लिखो8(priv, &priv->map->EEPROM_CMD,
			 RTL818X_EEPROM_CMD_NORMAL);

	rtl818x_ioग_लिखो8(priv, &priv->map->WPA_CONF, 0);
	क्रम (i = 0; i < ARRAY_SIZE(rtl8187b_reg_table); i++) अणु
		rtl818x_ioग_लिखो8_idx(priv,
				     (u8 *)(uपूर्णांकptr_t)
				     (rtl8187b_reg_table[i][0] | 0xFF00),
				     rtl8187b_reg_table[i][1],
				     rtl8187b_reg_table[i][2]);
	पूर्ण

	rtl818x_ioग_लिखो16(priv, &priv->map->TID_AC_MAP, 0xFA50);
	rtl818x_ioग_लिखो16(priv, &priv->map->INT_MIG, 0);

	rtl818x_ioग_लिखो32_idx(priv, (__le32 *)0xFFF0, 0, 1);
	rtl818x_ioग_लिखो32_idx(priv, (__le32 *)0xFFF4, 0, 1);
	rtl818x_ioग_लिखो8_idx(priv, (u8 *)0xFFF8, 0, 1);

	rtl818x_ioग_लिखो32(priv, &priv->map->RF_TIMING, 0x00004001);

	/* RFSW_CTRL रेजिस्टर */
	rtl818x_ioग_लिखो16_idx(priv, (__le16 *)0xFF72, 0x569A, 2);

	rtl818x_ioग_लिखो16(priv, &priv->map->RFPinsOutput, 0x0480);
	rtl818x_ioग_लिखो16(priv, &priv->map->RFPinsSelect, 0x2488);
	rtl818x_ioग_लिखो16(priv, &priv->map->RFPinsEnable, 0x1FFF);
	msleep(100);

	priv->rf->init(dev);

	reg = RTL818X_CMD_TX_ENABLE | RTL818X_CMD_RX_ENABLE;
	rtl818x_ioग_लिखो8(priv, &priv->map->CMD, reg);
	rtl818x_ioग_लिखो16(priv, &priv->map->INT_MASK, 0xFFFF);

	rtl818x_ioग_लिखो8(priv, (u8 *)0xFE41, 0xF4);
	rtl818x_ioग_लिखो8(priv, (u8 *)0xFE40, 0x00);
	rtl818x_ioग_लिखो8(priv, (u8 *)0xFE42, 0x00);
	rtl818x_ioग_लिखो8(priv, (u8 *)0xFE42, 0x01);
	rtl818x_ioग_लिखो8(priv, (u8 *)0xFE40, 0x0F);
	rtl818x_ioग_लिखो8(priv, (u8 *)0xFE42, 0x00);
	rtl818x_ioग_लिखो8(priv, (u8 *)0xFE42, 0x01);

	reg = rtl818x_ioपढ़ो8(priv, (u8 *)0xFFDB);
	rtl818x_ioग_लिखो8(priv, (u8 *)0xFFDB, reg | (1 << 2));
	rtl818x_ioग_लिखो16_idx(priv, (__le16 *)0xFF72, 0x59FA, 3);
	rtl818x_ioग_लिखो16_idx(priv, (__le16 *)0xFF74, 0x59D2, 3);
	rtl818x_ioग_लिखो16_idx(priv, (__le16 *)0xFF76, 0x59D2, 3);
	rtl818x_ioग_लिखो16_idx(priv, (__le16 *)0xFF78, 0x19FA, 3);
	rtl818x_ioग_लिखो16_idx(priv, (__le16 *)0xFF7A, 0x19FA, 3);
	rtl818x_ioग_लिखो16_idx(priv, (__le16 *)0xFF7C, 0x00D0, 3);
	rtl818x_ioग_लिखो8(priv, (u8 *)0xFF61, 0);
	rtl818x_ioग_लिखो8_idx(priv, (u8 *)0xFF80, 0x0F, 1);
	rtl818x_ioग_लिखो8_idx(priv, (u8 *)0xFF83, 0x03, 1);
	rtl818x_ioग_लिखो8(priv, (u8 *)0xFFDA, 0x10);
	rtl818x_ioग_लिखो8_idx(priv, (u8 *)0xFF4D, 0x08, 2);

	rtl818x_ioग_लिखो32(priv, &priv->map->HSSI_PARA, 0x0600321B);

	rtl818x_ioग_लिखो16_idx(priv, (__le16 *)0xFFEC, 0x0800, 1);

	priv->slot_समय = 0x9;
	priv->aअगरsn[0] = 2; /* AIFSN[AC_VO] */
	priv->aअगरsn[1] = 2; /* AIFSN[AC_VI] */
	priv->aअगरsn[2] = 7; /* AIFSN[AC_BK] */
	priv->aअगरsn[3] = 3; /* AIFSN[AC_BE] */
	rtl818x_ioग_लिखो8(priv, &priv->map->ACM_CONTROL, 0);

	/* ENEDCA flag must always be set, transmit issues? */
	rtl818x_ioग_लिखो8(priv, &priv->map->MSR, RTL818X_MSR_ENEDCA);

	वापस 0;
पूर्ण

अटल व्योम rtl8187_work(काष्ठा work_काष्ठा *work)
अणु
	/* The RTL8187 वापसs the retry count through रेजिस्टर 0xFFFA. In
	 * addition, it appears to be a cumulative retry count, not the
	 * value क्रम the current TX packet. When multiple TX entries are
	 * रुकोing in the queue, the retry count will be the total क्रम all.
	 * The "error" may matter क्रम purposes of rate setting, but there is
	 * no other choice with this hardware.
	 */
	काष्ठा rtl8187_priv *priv = container_of(work, काष्ठा rtl8187_priv,
				    work.work);
	काष्ठा ieee80211_tx_info *info;
	काष्ठा ieee80211_hw *dev = priv->dev;
	अटल u16 retry;
	u16 पंचांगp;
	u16 avg_retry;
	पूर्णांक length;

	mutex_lock(&priv->conf_mutex);
	पंचांगp = rtl818x_ioपढ़ो16(priv, (__le16 *)0xFFFA);
	length = skb_queue_len(&priv->b_tx_status.queue);
	अगर (unlikely(!length))
		length = 1;
	अगर (unlikely(पंचांगp < retry))
		पंचांगp = retry;
	avg_retry = (पंचांगp - retry) / length;
	जबतक (skb_queue_len(&priv->b_tx_status.queue) > 0) अणु
		काष्ठा sk_buff *old_skb;

		old_skb = skb_dequeue(&priv->b_tx_status.queue);
		info = IEEE80211_SKB_CB(old_skb);
		info->status.rates[0].count = avg_retry + 1;
		अगर (info->status.rates[0].count > RETRY_COUNT)
			info->flags &= ~IEEE80211_TX_STAT_ACK;
		ieee80211_tx_status_irqsafe(dev, old_skb);
	पूर्ण
	retry = पंचांगp;
	mutex_unlock(&priv->conf_mutex);
पूर्ण

अटल पूर्णांक rtl8187_start(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा rtl8187_priv *priv = dev->priv;
	u32 reg;
	पूर्णांक ret;

	mutex_lock(&priv->conf_mutex);

	ret = (!priv->is_rtl8187b) ? rtl8187_init_hw(dev) :
				     rtl8187b_init_hw(dev);
	अगर (ret)
		जाओ rtl8187_start_निकास;

	init_usb_anchor(&priv->anchored);
	priv->dev = dev;

	अगर (priv->is_rtl8187b) अणु
		reg = RTL818X_RX_CONF_MGMT |
		      RTL818X_RX_CONF_DATA |
		      RTL818X_RX_CONF_BROADCAST |
		      RTL818X_RX_CONF_NICMAC |
		      RTL818X_RX_CONF_BSSID |
		      (7 << 13 /* RX FIFO threshold NONE */) |
		      (7 << 10 /* MAX RX DMA */) |
		      RTL818X_RX_CONF_RX_AUTORESETPHY |
		      RTL818X_RX_CONF_ONLYERLPKT;
		priv->rx_conf = reg;
		rtl818x_ioग_लिखो32(priv, &priv->map->RX_CONF, reg);

		reg = rtl818x_ioपढ़ो8(priv, &priv->map->TX_AGC_CTL);
		reg &= ~RTL818X_TX_AGC_CTL_PERPACKET_GAIN;
		reg &= ~RTL818X_TX_AGC_CTL_PERPACKET_ANTSEL;
		reg &= ~RTL818X_TX_AGC_CTL_FEEDBACK_ANT;
		rtl818x_ioग_लिखो8(priv, &priv->map->TX_AGC_CTL, reg);

		rtl818x_ioग_लिखो32(priv, &priv->map->TX_CONF,
				  RTL818X_TX_CONF_HW_SEQNUM |
				  RTL818X_TX_CONF_DISREQQSIZE |
				  (RETRY_COUNT << 8  /* लघु retry limit */) |
				  (RETRY_COUNT << 0  /* दीर्घ retry limit */) |
				  (7 << 21 /* MAX TX DMA */));
		ret = rtl8187_init_urbs(dev);
		अगर (ret)
			जाओ rtl8187_start_निकास;
		ret = rtl8187b_init_status_urb(dev);
		अगर (ret)
			usb_समाप्त_anchored_urbs(&priv->anchored);
		जाओ rtl8187_start_निकास;
	पूर्ण

	rtl818x_ioग_लिखो16(priv, &priv->map->INT_MASK, 0xFFFF);

	rtl818x_ioग_लिखो32(priv, &priv->map->MAR[0], ~0);
	rtl818x_ioग_लिखो32(priv, &priv->map->MAR[1], ~0);

	ret = rtl8187_init_urbs(dev);
	अगर (ret)
		जाओ rtl8187_start_निकास;

	reg = RTL818X_RX_CONF_ONLYERLPKT |
	      RTL818X_RX_CONF_RX_AUTORESETPHY |
	      RTL818X_RX_CONF_BSSID |
	      RTL818X_RX_CONF_MGMT |
	      RTL818X_RX_CONF_DATA |
	      (7 << 13 /* RX FIFO threshold NONE */) |
	      (7 << 10 /* MAX RX DMA */) |
	      RTL818X_RX_CONF_BROADCAST |
	      RTL818X_RX_CONF_NICMAC;

	priv->rx_conf = reg;
	rtl818x_ioग_लिखो32(priv, &priv->map->RX_CONF, reg);

	reg = rtl818x_ioपढ़ो8(priv, &priv->map->CW_CONF);
	reg &= ~RTL818X_CW_CONF_PERPACKET_CW;
	reg |= RTL818X_CW_CONF_PERPACKET_RETRY;
	rtl818x_ioग_लिखो8(priv, &priv->map->CW_CONF, reg);

	reg = rtl818x_ioपढ़ो8(priv, &priv->map->TX_AGC_CTL);
	reg &= ~RTL818X_TX_AGC_CTL_PERPACKET_GAIN;
	reg &= ~RTL818X_TX_AGC_CTL_PERPACKET_ANTSEL;
	reg &= ~RTL818X_TX_AGC_CTL_FEEDBACK_ANT;
	rtl818x_ioग_लिखो8(priv, &priv->map->TX_AGC_CTL, reg);

	reg  = RTL818X_TX_CONF_CW_MIN |
	       (7 << 21 /* MAX TX DMA */) |
	       RTL818X_TX_CONF_NO_ICV;
	rtl818x_ioग_लिखो32(priv, &priv->map->TX_CONF, reg);

	reg = rtl818x_ioपढ़ो8(priv, &priv->map->CMD);
	reg |= RTL818X_CMD_TX_ENABLE;
	reg |= RTL818X_CMD_RX_ENABLE;
	rtl818x_ioग_लिखो8(priv, &priv->map->CMD, reg);
	INIT_DELAYED_WORK(&priv->work, rtl8187_work);

rtl8187_start_निकास:
	mutex_unlock(&priv->conf_mutex);
	वापस ret;
पूर्ण

अटल व्योम rtl8187_stop(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा rtl8187_priv *priv = dev->priv;
	काष्ठा sk_buff *skb;
	u32 reg;

	mutex_lock(&priv->conf_mutex);
	rtl818x_ioग_लिखो16(priv, &priv->map->INT_MASK, 0);

	reg = rtl818x_ioपढ़ो8(priv, &priv->map->CMD);
	reg &= ~RTL818X_CMD_TX_ENABLE;
	reg &= ~RTL818X_CMD_RX_ENABLE;
	rtl818x_ioग_लिखो8(priv, &priv->map->CMD, reg);

	priv->rf->stop(dev);
	rtl8187_set_anaparam(priv, false);

	rtl818x_ioग_लिखो8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_CONFIG);
	reg = rtl818x_ioपढ़ो8(priv, &priv->map->CONFIG4);
	rtl818x_ioग_लिखो8(priv, &priv->map->CONFIG4, reg | RTL818X_CONFIG4_VCOOFF);
	rtl818x_ioग_लिखो8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_NORMAL);

	जबतक ((skb = skb_dequeue(&priv->b_tx_status.queue)))
		dev_kमुक्त_skb_any(skb);

	usb_समाप्त_anchored_urbs(&priv->anchored);
	mutex_unlock(&priv->conf_mutex);

	अगर (!priv->is_rtl8187b)
		cancel_delayed_work_sync(&priv->work);
पूर्ण

अटल u64 rtl8187_get_tsf(काष्ठा ieee80211_hw *dev, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rtl8187_priv *priv = dev->priv;

	वापस rtl818x_ioपढ़ो32(priv, &priv->map->TSFT[0]) |
	       (u64)(rtl818x_ioपढ़ो32(priv, &priv->map->TSFT[1])) << 32;
पूर्ण


अटल व्योम rtl8187_beacon_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtl8187_vअगर *vअगर_priv =
		container_of(work, काष्ठा rtl8187_vअगर, beacon_work.work);
	काष्ठा ieee80211_vअगर *vअगर =
		container_of((व्योम *)vअगर_priv, काष्ठा ieee80211_vअगर, drv_priv);
	काष्ठा ieee80211_hw *dev = vअगर_priv->dev;
	काष्ठा ieee80211_mgmt *mgmt;
	काष्ठा sk_buff *skb;

	/* करोn't overflow the tx ring */
	अगर (ieee80211_queue_stopped(dev, 0))
		जाओ resched;

	/* grab a fresh beacon */
	skb = ieee80211_beacon_get(dev, vअगर);
	अगर (!skb)
		जाओ resched;

	/*
	 * update beacon बारtamp w/ TSF value
	 * TODO: make hardware update beacon बारtamp
	 */
	mgmt = (काष्ठा ieee80211_mgmt *)skb->data;
	mgmt->u.beacon.बारtamp = cpu_to_le64(rtl8187_get_tsf(dev, vअगर));

	/* TODO: use actual beacon queue */
	skb_set_queue_mapping(skb, 0);

	rtl8187_tx(dev, शून्य, skb);

resched:
	/*
	 * schedule next beacon
	 * TODO: use hardware support क्रम beacon timing
	 */
	schedule_delayed_work(&vअगर_priv->beacon_work,
			usecs_to_jअगरfies(1024 * vअगर->bss_conf.beacon_पूर्णांक));
पूर्ण


अटल पूर्णांक rtl8187_add_पूर्णांकerface(काष्ठा ieee80211_hw *dev,
				 काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rtl8187_priv *priv = dev->priv;
	काष्ठा rtl8187_vअगर *vअगर_priv;
	पूर्णांक i;
	पूर्णांक ret = -EOPNOTSUPP;

	mutex_lock(&priv->conf_mutex);
	अगर (priv->vअगर)
		जाओ निकास;

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_ADHOC:
		अवरोध;
	शेष:
		जाओ निकास;
	पूर्ण

	ret = 0;
	priv->vअगर = vअगर;

	/* Initialize driver निजी area */
	vअगर_priv = (काष्ठा rtl8187_vअगर *)&vअगर->drv_priv;
	vअगर_priv->dev = dev;
	INIT_DELAYED_WORK(&vअगर_priv->beacon_work, rtl8187_beacon_work);
	vअगर_priv->enable_beacon = false;


	rtl818x_ioग_लिखो8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_CONFIG);
	क्रम (i = 0; i < ETH_ALEN; i++)
		rtl818x_ioग_लिखो8(priv, &priv->map->MAC[i],
				 ((u8 *)vअगर->addr)[i]);
	rtl818x_ioग_लिखो8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_NORMAL);

निकास:
	mutex_unlock(&priv->conf_mutex);
	वापस ret;
पूर्ण

अटल व्योम rtl8187_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *dev,
				     काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rtl8187_priv *priv = dev->priv;
	mutex_lock(&priv->conf_mutex);
	priv->vअगर = शून्य;
	mutex_unlock(&priv->conf_mutex);
पूर्ण

अटल पूर्णांक rtl8187_config(काष्ठा ieee80211_hw *dev, u32 changed)
अणु
	काष्ठा rtl8187_priv *priv = dev->priv;
	काष्ठा ieee80211_conf *conf = &dev->conf;
	u32 reg;

	mutex_lock(&priv->conf_mutex);
	reg = rtl818x_ioपढ़ो32(priv, &priv->map->TX_CONF);
	/* Enable TX loopback on MAC level to aव्योम TX during channel
	 * changes, as this has be seen to causes problems and the
	 * card will stop work until next reset
	 */
	rtl818x_ioग_लिखो32(priv, &priv->map->TX_CONF,
			  reg | RTL818X_TX_CONF_LOOPBACK_MAC);
	priv->rf->set_chan(dev, conf);
	msleep(10);
	rtl818x_ioग_लिखो32(priv, &priv->map->TX_CONF, reg);

	rtl818x_ioग_लिखो16(priv, &priv->map->ATIM_WND, 2);
	rtl818x_ioग_लिखो16(priv, &priv->map->ATIMTR_INTERVAL, 100);
	rtl818x_ioग_लिखो16(priv, &priv->map->BEACON_INTERVAL, 100);
	rtl818x_ioग_लिखो16(priv, &priv->map->BEACON_INTERVAL_TIME, 100);
	mutex_unlock(&priv->conf_mutex);
	वापस 0;
पूर्ण

/*
 * With 8187B, AC_*_PARAM clashes with FEMR definition in काष्ठा rtl818x_csr क्रम
 * example. Thus we have to use raw values क्रम AC_*_PARAM रेजिस्टर addresses.
 */
अटल __le32 *rtl8187b_ac_addr[4] = अणु
	(__le32 *) 0xFFF0, /* AC_VO */
	(__le32 *) 0xFFF4, /* AC_VI */
	(__le32 *) 0xFFFC, /* AC_BK */
	(__le32 *) 0xFFF8, /* AC_BE */
पूर्ण;

#घोषणा SIFS_TIME 0xa

अटल व्योम rtl8187_conf_erp(काष्ठा rtl8187_priv *priv, bool use_लघु_slot,
			     bool use_लघु_preamble)
अणु
	अगर (priv->is_rtl8187b) अणु
		u8 dअगरs, eअगरs;
		u16 ack_समयout;
		पूर्णांक queue;

		अगर (use_लघु_slot) अणु
			priv->slot_समय = 0x9;
			dअगरs = 0x1c;
			eअगरs = 0x53;
		पूर्ण अन्यथा अणु
			priv->slot_समय = 0x14;
			dअगरs = 0x32;
			eअगरs = 0x5b;
		पूर्ण
		rtl818x_ioग_लिखो8(priv, &priv->map->SIFS, 0x22);
		rtl818x_ioग_लिखो8(priv, &priv->map->SLOT, priv->slot_समय);
		rtl818x_ioग_लिखो8(priv, &priv->map->DIFS, dअगरs);

		/*
		 * BRSR+1 on 8187B is in fact EIFS रेजिस्टर
		 * Value in units of 4 us
		 */
		rtl818x_ioग_लिखो8(priv, (u8 *)&priv->map->BRSR + 1, eअगरs);

		/*
		 * For 8187B, CARRIER_SENSE_COUNTER is in fact ack समयout
		 * रेजिस्टर. In units of 4 us like eअगरs रेजिस्टर
		 * ack_समयout = ack duration + plcp + dअगरs + preamble
		 */
		ack_समयout = 112 + 48 + dअगरs;
		अगर (use_लघु_preamble)
			ack_समयout += 72;
		अन्यथा
			ack_समयout += 144;
		rtl818x_ioग_लिखो8(priv, &priv->map->CARRIER_SENSE_COUNTER,
				 DIV_ROUND_UP(ack_समयout, 4));

		क्रम (queue = 0; queue < 4; queue++)
			rtl818x_ioग_लिखो8(priv, (u8 *) rtl8187b_ac_addr[queue],
					 priv->aअगरsn[queue] * priv->slot_समय +
					 SIFS_TIME);
	पूर्ण अन्यथा अणु
		rtl818x_ioग_लिखो8(priv, &priv->map->SIFS, 0x22);
		अगर (use_लघु_slot) अणु
			rtl818x_ioग_लिखो8(priv, &priv->map->SLOT, 0x9);
			rtl818x_ioग_लिखो8(priv, &priv->map->DIFS, 0x14);
			rtl818x_ioग_लिखो8(priv, &priv->map->EIFS, 91 - 0x14);
		पूर्ण अन्यथा अणु
			rtl818x_ioग_लिखो8(priv, &priv->map->SLOT, 0x14);
			rtl818x_ioग_लिखो8(priv, &priv->map->DIFS, 0x24);
			rtl818x_ioग_लिखो8(priv, &priv->map->EIFS, 91 - 0x24);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rtl8187_bss_info_changed(काष्ठा ieee80211_hw *dev,
				     काष्ठा ieee80211_vअगर *vअगर,
				     काष्ठा ieee80211_bss_conf *info,
				     u32 changed)
अणु
	काष्ठा rtl8187_priv *priv = dev->priv;
	काष्ठा rtl8187_vअगर *vअगर_priv;
	पूर्णांक i;
	u8 reg;

	vअगर_priv = (काष्ठा rtl8187_vअगर *)&vअगर->drv_priv;

	अगर (changed & BSS_CHANGED_BSSID) अणु
		mutex_lock(&priv->conf_mutex);
		क्रम (i = 0; i < ETH_ALEN; i++)
			rtl818x_ioग_लिखो8(priv, &priv->map->BSSID[i],
					 info->bssid[i]);

		अगर (priv->is_rtl8187b)
			reg = RTL818X_MSR_ENEDCA;
		अन्यथा
			reg = 0;

		अगर (is_valid_ether_addr(info->bssid)) अणु
			अगर (vअगर->type == NL80211_IFTYPE_ADHOC)
				reg |= RTL818X_MSR_ADHOC;
			अन्यथा
				reg |= RTL818X_MSR_INFRA;
		पूर्ण
		अन्यथा
			reg |= RTL818X_MSR_NO_LINK;

		rtl818x_ioग_लिखो8(priv, &priv->map->MSR, reg);

		mutex_unlock(&priv->conf_mutex);
	पूर्ण

	अगर (changed & (BSS_CHANGED_ERP_SLOT | BSS_CHANGED_ERP_PREAMBLE))
		rtl8187_conf_erp(priv, info->use_लघु_slot,
				 info->use_लघु_preamble);

	अगर (changed & BSS_CHANGED_BEACON_ENABLED)
		vअगर_priv->enable_beacon = info->enable_beacon;

	अगर (changed & (BSS_CHANGED_BEACON_ENABLED | BSS_CHANGED_BEACON)) अणु
		cancel_delayed_work_sync(&vअगर_priv->beacon_work);
		अगर (vअगर_priv->enable_beacon)
			schedule_work(&vअगर_priv->beacon_work.work);
	पूर्ण

पूर्ण

अटल u64 rtl8187_prepare_multicast(काष्ठा ieee80211_hw *dev,
				     काष्ठा netdev_hw_addr_list *mc_list)
अणु
	वापस netdev_hw_addr_list_count(mc_list);
पूर्ण

अटल व्योम rtl8187_configure_filter(काष्ठा ieee80211_hw *dev,
				     अचिन्हित पूर्णांक changed_flags,
				     अचिन्हित पूर्णांक *total_flags,
				     u64 multicast)
अणु
	काष्ठा rtl8187_priv *priv = dev->priv;

	अगर (changed_flags & FIF_FCSFAIL)
		priv->rx_conf ^= RTL818X_RX_CONF_FCS;
	अगर (changed_flags & FIF_CONTROL)
		priv->rx_conf ^= RTL818X_RX_CONF_CTRL;
	अगर (*total_flags & FIF_OTHER_BSS ||
	    *total_flags & FIF_ALLMULTI || multicast > 0)
		priv->rx_conf |= RTL818X_RX_CONF_MONITOR;
	अन्यथा
		priv->rx_conf &= ~RTL818X_RX_CONF_MONITOR;

	*total_flags = 0;

	अगर (priv->rx_conf & RTL818X_RX_CONF_FCS)
		*total_flags |= FIF_FCSFAIL;
	अगर (priv->rx_conf & RTL818X_RX_CONF_CTRL)
		*total_flags |= FIF_CONTROL;
	अगर (priv->rx_conf & RTL818X_RX_CONF_MONITOR) अणु
		*total_flags |= FIF_OTHER_BSS;
		*total_flags |= FIF_ALLMULTI;
	पूर्ण

	rtl818x_ioग_लिखो32_async(priv, &priv->map->RX_CONF, priv->rx_conf);
पूर्ण

अटल पूर्णांक rtl8187_conf_tx(काष्ठा ieee80211_hw *dev,
			   काष्ठा ieee80211_vअगर *vअगर, u16 queue,
			   स्थिर काष्ठा ieee80211_tx_queue_params *params)
अणु
	काष्ठा rtl8187_priv *priv = dev->priv;
	u8 cw_min, cw_max;

	अगर (queue > 3)
		वापस -EINVAL;

	cw_min = fls(params->cw_min);
	cw_max = fls(params->cw_max);

	अगर (priv->is_rtl8187b) अणु
		priv->aअगरsn[queue] = params->aअगरs;

		/*
		 * This is the काष्ठाure of AC_*_PARAM रेजिस्टरs in 8187B:
		 * - TXOP limit field, bit offset = 16
		 * - ECWmax, bit offset = 12
		 * - ECWmin, bit offset = 8
		 * - AIFS, bit offset = 0
		 */
		rtl818x_ioग_लिखो32(priv, rtl8187b_ac_addr[queue],
				  (params->txop << 16) | (cw_max << 12) |
				  (cw_min << 8) | (params->aअगरs *
				  priv->slot_समय + SIFS_TIME));
	पूर्ण अन्यथा अणु
		अगर (queue != 0)
			वापस -EINVAL;

		rtl818x_ioग_लिखो8(priv, &priv->map->CW_VAL,
				 cw_min | (cw_max << 4));
	पूर्ण
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा ieee80211_ops rtl8187_ops = अणु
	.tx			= rtl8187_tx,
	.start			= rtl8187_start,
	.stop			= rtl8187_stop,
	.add_पूर्णांकerface		= rtl8187_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface	= rtl8187_हटाओ_पूर्णांकerface,
	.config			= rtl8187_config,
	.bss_info_changed	= rtl8187_bss_info_changed,
	.prepare_multicast	= rtl8187_prepare_multicast,
	.configure_filter	= rtl8187_configure_filter,
	.conf_tx		= rtl8187_conf_tx,
	.rfसमाप्त_poll		= rtl8187_rfसमाप्त_poll,
	.get_tsf		= rtl8187_get_tsf,
पूर्ण;

अटल व्योम rtl8187_eeprom_रेजिस्टर_पढ़ो(काष्ठा eeprom_93cx6 *eeprom)
अणु
	काष्ठा ieee80211_hw *dev = eeprom->data;
	काष्ठा rtl8187_priv *priv = dev->priv;
	u8 reg = rtl818x_ioपढ़ो8(priv, &priv->map->EEPROM_CMD);

	eeprom->reg_data_in = reg & RTL818X_EEPROM_CMD_WRITE;
	eeprom->reg_data_out = reg & RTL818X_EEPROM_CMD_READ;
	eeprom->reg_data_घड़ी = reg & RTL818X_EEPROM_CMD_CK;
	eeprom->reg_chip_select = reg & RTL818X_EEPROM_CMD_CS;
पूर्ण

अटल व्योम rtl8187_eeprom_रेजिस्टर_ग_लिखो(काष्ठा eeprom_93cx6 *eeprom)
अणु
	काष्ठा ieee80211_hw *dev = eeprom->data;
	काष्ठा rtl8187_priv *priv = dev->priv;
	u8 reg = RTL818X_EEPROM_CMD_PROGRAM;

	अगर (eeprom->reg_data_in)
		reg |= RTL818X_EEPROM_CMD_WRITE;
	अगर (eeprom->reg_data_out)
		reg |= RTL818X_EEPROM_CMD_READ;
	अगर (eeprom->reg_data_घड़ी)
		reg |= RTL818X_EEPROM_CMD_CK;
	अगर (eeprom->reg_chip_select)
		reg |= RTL818X_EEPROM_CMD_CS;

	rtl818x_ioग_लिखो8(priv, &priv->map->EEPROM_CMD, reg);
	udelay(10);
पूर्ण

अटल पूर्णांक rtl8187_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
				   स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा ieee80211_hw *dev;
	काष्ठा rtl8187_priv *priv;
	काष्ठा eeprom_93cx6 eeprom;
	काष्ठा ieee80211_channel *channel;
	स्थिर अक्षर *chip_name;
	u16 txpwr, reg;
	u16 product_id = le16_to_cpu(udev->descriptor.idProduct);
	पूर्णांक err, i;
	u8 mac_addr[ETH_ALEN];

	dev = ieee80211_alloc_hw(माप(*priv), &rtl8187_ops);
	अगर (!dev) अणु
		prपूर्णांकk(KERN_ERR "rtl8187: ieee80211 alloc failed\n");
		वापस -ENOMEM;
	पूर्ण

	priv = dev->priv;
	priv->is_rtl8187b = (id->driver_info == DEVICE_RTL8187B);

	/* allocate "DMA aware" buffer क्रम रेजिस्टर accesses */
	priv->io_dmabuf = kदो_स्मृति(माप(*priv->io_dmabuf), GFP_KERNEL);
	अगर (!priv->io_dmabuf) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_dev;
	पूर्ण
	mutex_init(&priv->io_mutex);
	mutex_init(&priv->conf_mutex);

	SET_IEEE80211_DEV(dev, &पूर्णांकf->dev);
	usb_set_पूर्णांकfdata(पूर्णांकf, dev);
	priv->udev = udev;

	usb_get_dev(udev);

	skb_queue_head_init(&priv->rx_queue);

	BUILD_BUG_ON(माप(priv->channels) != माप(rtl818x_channels));
	BUILD_BUG_ON(माप(priv->rates) != माप(rtl818x_rates));

	स_नकल(priv->channels, rtl818x_channels, माप(rtl818x_channels));
	स_नकल(priv->rates, rtl818x_rates, माप(rtl818x_rates));
	priv->map = (काष्ठा rtl818x_csr *)0xFF00;

	priv->band.band = NL80211_BAND_2GHZ;
	priv->band.channels = priv->channels;
	priv->band.n_channels = ARRAY_SIZE(rtl818x_channels);
	priv->band.bitrates = priv->rates;
	priv->band.n_bitrates = ARRAY_SIZE(rtl818x_rates);
	dev->wiphy->bands[NL80211_BAND_2GHZ] = &priv->band;


	ieee80211_hw_set(dev, RX_INCLUDES_FCS);
	ieee80211_hw_set(dev, HOST_BROADCAST_PS_BUFFERING);
	ieee80211_hw_set(dev, SIGNAL_DBM);
	/* Initialize rate-control variables */
	dev->max_rates = 1;
	dev->max_rate_tries = RETRY_COUNT;

	eeprom.data = dev;
	eeprom.रेजिस्टर_पढ़ो = rtl8187_eeprom_रेजिस्टर_पढ़ो;
	eeprom.रेजिस्टर_ग_लिखो = rtl8187_eeprom_रेजिस्टर_ग_लिखो;
	अगर (rtl818x_ioपढ़ो32(priv, &priv->map->RX_CONF) & (1 << 6))
		eeprom.width = PCI_EEPROM_WIDTH_93C66;
	अन्यथा
		eeprom.width = PCI_EEPROM_WIDTH_93C46;

	rtl818x_ioग_लिखो8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_CONFIG);
	udelay(10);

	eeprom_93cx6_multiपढ़ो(&eeprom, RTL8187_EEPROM_MAC_ADDR,
			       (__le16 __क्रमce *)mac_addr, 3);
	अगर (!is_valid_ether_addr(mac_addr)) अणु
		prपूर्णांकk(KERN_WARNING "rtl8187: Invalid hwaddr! Using randomly "
		       "generated MAC address\n");
		eth_अक्रमom_addr(mac_addr);
	पूर्ण
	SET_IEEE80211_PERM_ADDR(dev, mac_addr);

	channel = priv->channels;
	क्रम (i = 0; i < 3; i++) अणु
		eeprom_93cx6_पढ़ो(&eeprom, RTL8187_EEPROM_TXPWR_CHAN_1 + i,
				  &txpwr);
		(*channel++).hw_value = txpwr & 0xFF;
		(*channel++).hw_value = txpwr >> 8;
	पूर्ण
	क्रम (i = 0; i < 2; i++) अणु
		eeprom_93cx6_पढ़ो(&eeprom, RTL8187_EEPROM_TXPWR_CHAN_4 + i,
				  &txpwr);
		(*channel++).hw_value = txpwr & 0xFF;
		(*channel++).hw_value = txpwr >> 8;
	पूर्ण

	eeprom_93cx6_पढ़ो(&eeprom, RTL8187_EEPROM_TXPWR_BASE,
			  &priv->txpwr_base);

	reg = rtl818x_ioपढ़ो8(priv, &priv->map->PGSELECT) & ~1;
	rtl818x_ioग_लिखो8(priv, &priv->map->PGSELECT, reg | 1);
	/* 0 means asic B-cut, we should use SW 3 wire
	 * bit-by-bit banging क्रम radio. 1 means we can use
	 * USB specअगरic request to ग_लिखो radio रेजिस्टरs */
	priv->asic_rev = rtl818x_ioपढ़ो8(priv, (u8 *)0xFFFE) & 0x3;
	rtl818x_ioग_लिखो8(priv, &priv->map->PGSELECT, reg);
	rtl818x_ioग_लिखो8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_NORMAL);

	अगर (!priv->is_rtl8187b) अणु
		u32 reg32;
		reg32 = rtl818x_ioपढ़ो32(priv, &priv->map->TX_CONF);
		reg32 &= RTL818X_TX_CONF_HWVER_MASK;
		चयन (reg32) अणु
		हाल RTL818X_TX_CONF_R8187vD_B:
			/* Some RTL8187B devices have a USB ID of 0x8187
			 * detect them here */
			chip_name = "RTL8187BvB(early)";
			priv->is_rtl8187b = 1;
			priv->hw_rev = RTL8187BvB;
			अवरोध;
		हाल RTL818X_TX_CONF_R8187vD:
			chip_name = "RTL8187vD";
			अवरोध;
		शेष:
			chip_name = "RTL8187vB (default)";
		पूर्ण
       पूर्ण अन्यथा अणु
		/*
		 * Force USB request to ग_लिखो radio रेजिस्टरs क्रम 8187B, Realtek
		 * only uses it in their sources
		 */
		/*अगर (priv->asic_rev == 0) अणु
			prपूर्णांकk(KERN_WARNING "rtl8187: Forcing use of USB "
			       "requests to write to radio registers\n");
			priv->asic_rev = 1;
		पूर्ण*/
		चयन (rtl818x_ioपढ़ो8(priv, (u8 *)0xFFE1)) अणु
		हाल RTL818X_R8187B_B:
			chip_name = "RTL8187BvB";
			priv->hw_rev = RTL8187BvB;
			अवरोध;
		हाल RTL818X_R8187B_D:
			chip_name = "RTL8187BvD";
			priv->hw_rev = RTL8187BvD;
			अवरोध;
		हाल RTL818X_R8187B_E:
			chip_name = "RTL8187BvE";
			priv->hw_rev = RTL8187BvE;
			अवरोध;
		शेष:
			chip_name = "RTL8187BvB (default)";
			priv->hw_rev = RTL8187BvB;
		पूर्ण
	पूर्ण

	अगर (!priv->is_rtl8187b) अणु
		क्रम (i = 0; i < 2; i++) अणु
			eeprom_93cx6_पढ़ो(&eeprom,
					  RTL8187_EEPROM_TXPWR_CHAN_6 + i,
					  &txpwr);
			(*channel++).hw_value = txpwr & 0xFF;
			(*channel++).hw_value = txpwr >> 8;
		पूर्ण
	पूर्ण अन्यथा अणु
		eeprom_93cx6_पढ़ो(&eeprom, RTL8187_EEPROM_TXPWR_CHAN_6,
				  &txpwr);
		(*channel++).hw_value = txpwr & 0xFF;

		eeprom_93cx6_पढ़ो(&eeprom, 0x0A, &txpwr);
		(*channel++).hw_value = txpwr & 0xFF;

		eeprom_93cx6_पढ़ो(&eeprom, 0x1C, &txpwr);
		(*channel++).hw_value = txpwr & 0xFF;
		(*channel++).hw_value = txpwr >> 8;
	पूर्ण
	/* Handle the dअगरfering rfसमाप्त GPIO bit in dअगरferent models */
	priv->rfसमाप्त_mask = RFKILL_MASK_8187_89_97;
	अगर (product_id == 0x8197 || product_id == 0x8198) अणु
		eeprom_93cx6_पढ़ो(&eeprom, RTL8187_EEPROM_SELECT_GPIO, &reg);
		अगर (reg & 0xFF00)
			priv->rfसमाप्त_mask = RFKILL_MASK_8198;
	पूर्ण
	dev->vअगर_data_size = माप(काष्ठा rtl8187_vअगर);
	dev->wiphy->पूर्णांकerface_modes = BIT(NL80211_IFTYPE_STATION) |
				      BIT(NL80211_IFTYPE_ADHOC) ;

	wiphy_ext_feature_set(dev->wiphy, NL80211_EXT_FEATURE_CQM_RSSI_LIST);

	अगर ((id->driver_info == DEVICE_RTL8187) && priv->is_rtl8187b)
		prपूर्णांकk(KERN_INFO "rtl8187: inconsistency between id with OEM"
		       " info!\n");

	priv->rf = rtl8187_detect_rf(dev);
	dev->extra_tx_headroom = (!priv->is_rtl8187b) ?
				  माप(काष्ठा rtl8187_tx_hdr) :
				  माप(काष्ठा rtl8187b_tx_hdr);
	अगर (!priv->is_rtl8187b)
		dev->queues = 1;
	अन्यथा
		dev->queues = 4;

	err = ieee80211_रेजिस्टर_hw(dev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "rtl8187: Cannot register device\n");
		जाओ err_मुक्त_dmabuf;
	पूर्ण
	skb_queue_head_init(&priv->b_tx_status.queue);

	wiphy_info(dev->wiphy, "hwaddr %pM, %s V%d + %s, rfkill mask %d\n",
		   mac_addr, chip_name, priv->asic_rev, priv->rf->name,
		   priv->rfसमाप्त_mask);

#अगर_घोषित CONFIG_RTL8187_LEDS
	eeprom_93cx6_पढ़ो(&eeprom, 0x3F, &reg);
	reg &= 0xFF;
	rtl8187_leds_init(dev, reg);
#पूर्ण_अगर
	rtl8187_rfसमाप्त_init(dev);

	वापस 0;

 err_मुक्त_dmabuf:
	kमुक्त(priv->io_dmabuf);
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	usb_put_dev(udev);
 err_मुक्त_dev:
	ieee80211_मुक्त_hw(dev);
	वापस err;
पूर्ण

अटल व्योम rtl8187_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा ieee80211_hw *dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा rtl8187_priv *priv;

	अगर (!dev)
		वापस;

#अगर_घोषित CONFIG_RTL8187_LEDS
	rtl8187_leds_निकास(dev);
#पूर्ण_अगर
	rtl8187_rfसमाप्त_निकास(dev);
	ieee80211_unरेजिस्टर_hw(dev);

	priv = dev->priv;
	usb_reset_device(priv->udev);
	usb_put_dev(पूर्णांकerface_to_usbdev(पूर्णांकf));
	kमुक्त(priv->io_dmabuf);
	ieee80211_मुक्त_hw(dev);
पूर्ण

अटल काष्ठा usb_driver rtl8187_driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= rtl8187_table,
	.probe		= rtl8187_probe,
	.disconnect	= rtl8187_disconnect,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(rtl8187_driver);
