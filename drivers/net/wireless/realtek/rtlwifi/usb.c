<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#समावेश "wifi.h"
#समावेश "core.h"
#समावेश "usb.h"
#समावेश "base.h"
#समावेश "ps.h"
#समावेश "rtl8192c/fw_common.h"
#समावेश <linux/export.h>
#समावेश <linux/module.h>

MODULE_AUTHOR("lizhaoming	<chaoming_li@realsil.com.cn>");
MODULE_AUTHOR("Realtek WlanFAE	<wlanfae@realtek.com>");
MODULE_AUTHOR("Larry Finger	<Larry.FInger@lwfinger.net>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("USB basic driver for rtlwifi");

#घोषणा	REALTEK_USB_VENQT_READ			0xC0
#घोषणा	REALTEK_USB_VENQT_WRITE			0x40
#घोषणा REALTEK_USB_VENQT_CMD_REQ		0x05
#घोषणा	REALTEK_USB_VENQT_CMD_IDX		0x00

#घोषणा MAX_USBCTRL_VENDORREQ_TIMES		10

अटल व्योम usbctrl_async_callback(काष्ठा urb *urb)
अणु
	अगर (urb) अणु
		/* मुक्त dr */
		kमुक्त(urb->setup_packet);
		/* मुक्त databuf */
		kमुक्त(urb->transfer_buffer);
	पूर्ण
पूर्ण

अटल पूर्णांक _usbctrl_venकरोrreq_async_ग_लिखो(काष्ठा usb_device *udev, u8 request,
					  u16 value, u16 index, व्योम *pdata,
					  u16 len)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक pipe;
	u8 reqtype;
	काष्ठा usb_ctrlrequest *dr;
	काष्ठा urb *urb;
	स्थिर u16 databuf_maxlen = REALTEK_USB_VENQT_MAX_BUF_SIZE;
	u8 *databuf;

	अगर (WARN_ON_ONCE(len > databuf_maxlen))
		len = databuf_maxlen;

	pipe = usb_sndctrlpipe(udev, 0); /* ग_लिखो_out */
	reqtype =  REALTEK_USB_VENQT_WRITE;

	dr = kzalloc(माप(*dr), GFP_ATOMIC);
	अगर (!dr)
		वापस -ENOMEM;

	databuf = kzalloc(databuf_maxlen, GFP_ATOMIC);
	अगर (!databuf) अणु
		kमुक्त(dr);
		वापस -ENOMEM;
	पूर्ण

	urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!urb) अणु
		kमुक्त(databuf);
		kमुक्त(dr);
		वापस -ENOMEM;
	पूर्ण

	dr->bRequestType = reqtype;
	dr->bRequest = request;
	dr->wValue = cpu_to_le16(value);
	dr->wIndex = cpu_to_le16(index);
	dr->wLength = cpu_to_le16(len);
	/* data are alपढ़ोy in little-endian order */
	स_नकल(databuf, pdata, len);
	usb_fill_control_urb(urb, udev, pipe,
			     (अचिन्हित अक्षर *)dr, databuf, len,
			     usbctrl_async_callback, शून्य);
	rc = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (rc < 0) अणु
		kमुक्त(databuf);
		kमुक्त(dr);
	पूर्ण
	usb_मुक्त_urb(urb);
	वापस rc;
पूर्ण

अटल पूर्णांक _usbctrl_venकरोrreq_sync_पढ़ो(काष्ठा usb_device *udev, u8 request,
					u16 value, u16 index, व्योम *pdata,
					u16 len)
अणु
	अचिन्हित पूर्णांक pipe;
	पूर्णांक status;
	u8 reqtype;
	पूर्णांक venकरोrreq_बार = 0;
	अटल पूर्णांक count;

	pipe = usb_rcvctrlpipe(udev, 0); /* पढ़ो_in */
	reqtype =  REALTEK_USB_VENQT_READ;

	करो अणु
		status = usb_control_msg(udev, pipe, request, reqtype, value,
					 index, pdata, len, 1000);
		अगर (status < 0) अणु
			/* firmware करोwnload is checksumed, करोn't retry */
			अगर ((value >= FW_8192C_START_ADDRESS &&
			    value <= FW_8192C_END_ADDRESS))
				अवरोध;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण जबतक (++venकरोrreq_बार < MAX_USBCTRL_VENDORREQ_TIMES);

	अगर (status < 0 && count++ < 4)
		pr_err("reg 0x%x, usbctrl_vendorreq TimeOut! status:0x%x value=0x%x\n",
		       value, status, *(u32 *)pdata);
	वापस status;
पूर्ण

अटल u32 _usb_पढ़ो_sync(काष्ठा rtl_priv *rtlpriv, u32 addr, u16 len)
अणु
	काष्ठा device *dev = rtlpriv->io.dev;
	काष्ठा usb_device *udev = to_usb_device(dev);
	u8 request;
	u16 wvalue;
	u16 index;
	__le32 *data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rtlpriv->locks.usb_lock, flags);
	अगर (++rtlpriv->usb_data_index >= RTL_USB_MAX_RX_COUNT)
		rtlpriv->usb_data_index = 0;
	data = &rtlpriv->usb_data[rtlpriv->usb_data_index];
	spin_unlock_irqrestore(&rtlpriv->locks.usb_lock, flags);
	request = REALTEK_USB_VENQT_CMD_REQ;
	index = REALTEK_USB_VENQT_CMD_IDX; /* n/a */

	wvalue = (u16)addr;
	_usbctrl_venकरोrreq_sync_पढ़ो(udev, request, wvalue, index, data, len);
	वापस le32_to_cpu(*data);
पूर्ण

अटल u8 _usb_पढ़ो8_sync(काष्ठा rtl_priv *rtlpriv, u32 addr)
अणु
	वापस (u8)_usb_पढ़ो_sync(rtlpriv, addr, 1);
पूर्ण

अटल u16 _usb_पढ़ो16_sync(काष्ठा rtl_priv *rtlpriv, u32 addr)
अणु
	वापस (u16)_usb_पढ़ो_sync(rtlpriv, addr, 2);
पूर्ण

अटल u32 _usb_पढ़ो32_sync(काष्ठा rtl_priv *rtlpriv, u32 addr)
अणु
	वापस _usb_पढ़ो_sync(rtlpriv, addr, 4);
पूर्ण

अटल व्योम _usb_ग_लिखो_async(काष्ठा usb_device *udev, u32 addr, u32 val,
			     u16 len)
अणु
	u8 request;
	u16 wvalue;
	u16 index;
	__le32 data;

	request = REALTEK_USB_VENQT_CMD_REQ;
	index = REALTEK_USB_VENQT_CMD_IDX; /* n/a */
	wvalue = (u16)(addr&0x0000ffff);
	data = cpu_to_le32(val);
	_usbctrl_venकरोrreq_async_ग_लिखो(udev, request, wvalue, index, &data,
				       len);
पूर्ण

अटल व्योम _usb_ग_लिखो8_async(काष्ठा rtl_priv *rtlpriv, u32 addr, u8 val)
अणु
	काष्ठा device *dev = rtlpriv->io.dev;

	_usb_ग_लिखो_async(to_usb_device(dev), addr, val, 1);
पूर्ण

अटल व्योम _usb_ग_लिखो16_async(काष्ठा rtl_priv *rtlpriv, u32 addr, u16 val)
अणु
	काष्ठा device *dev = rtlpriv->io.dev;

	_usb_ग_लिखो_async(to_usb_device(dev), addr, val, 2);
पूर्ण

अटल व्योम _usb_ग_लिखो32_async(काष्ठा rtl_priv *rtlpriv, u32 addr, u32 val)
अणु
	काष्ठा device *dev = rtlpriv->io.dev;

	_usb_ग_लिखो_async(to_usb_device(dev), addr, val, 4);
पूर्ण

अटल व्योम _usb_ग_लिखोn_sync(काष्ठा rtl_priv *rtlpriv, u32 addr, व्योम *data,
			     u16 len)
अणु
	काष्ठा device *dev = rtlpriv->io.dev;
	काष्ठा usb_device *udev = to_usb_device(dev);
	u8 request = REALTEK_USB_VENQT_CMD_REQ;
	u8 reqtype =  REALTEK_USB_VENQT_WRITE;
	u16 wvalue;
	u16 index = REALTEK_USB_VENQT_CMD_IDX;
	पूर्णांक pipe = usb_sndctrlpipe(udev, 0); /* ग_लिखो_out */
	u8 *buffer;

	wvalue = (u16)(addr & 0x0000ffff);
	buffer = kmemdup(data, len, GFP_ATOMIC);
	अगर (!buffer)
		वापस;
	usb_control_msg(udev, pipe, request, reqtype, wvalue,
			index, buffer, len, 50);

	kमुक्त(buffer);
पूर्ण

अटल व्योम _rtl_usb_io_handler_init(काष्ठा device *dev,
				     काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->io.dev = dev;
	mutex_init(&rtlpriv->io.bb_mutex);
	rtlpriv->io.ग_लिखो8_async	= _usb_ग_लिखो8_async;
	rtlpriv->io.ग_लिखो16_async	= _usb_ग_लिखो16_async;
	rtlpriv->io.ग_लिखो32_async	= _usb_ग_लिखो32_async;
	rtlpriv->io.पढ़ो8_sync		= _usb_पढ़ो8_sync;
	rtlpriv->io.पढ़ो16_sync		= _usb_पढ़ो16_sync;
	rtlpriv->io.पढ़ो32_sync		= _usb_पढ़ो32_sync;
	rtlpriv->io.ग_लिखोn_sync		= _usb_ग_लिखोn_sync;
पूर्ण

अटल व्योम _rtl_usb_io_handler_release(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv __maybe_unused *rtlpriv = rtl_priv(hw);

	mutex_destroy(&rtlpriv->io.bb_mutex);
पूर्ण

/*	Default aggregation handler. Do nothing and just वापस the oldest skb.  */
अटल काष्ठा sk_buff *_none_usb_tx_aggregate_hdl(काष्ठा ieee80211_hw *hw,
						  काष्ठा sk_buff_head *list)
अणु
	वापस skb_dequeue(list);
पूर्ण

#घोषणा IS_HIGH_SPEED_USB(udev) \
		((USB_SPEED_HIGH == (udev)->speed) ? true : false)

अटल पूर्णांक _rtl_usb_init_tx(काष्ठा ieee80211_hw *hw)
अणु
	u32 i;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_usb *rtlusb = rtl_usbdev(rtl_usbpriv(hw));

	rtlusb->max_bulk_out_size = IS_HIGH_SPEED_USB(rtlusb->udev)
						    ? USB_HIGH_SPEED_BULK_SIZE
						    : USB_FULL_SPEED_BULK_SIZE;

	rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG, "USB Max Bulk-out Size=%d\n",
		rtlusb->max_bulk_out_size);

	क्रम (i = 0; i < __RTL_TXQ_NUM; i++) अणु
		u32 ep_num = rtlusb->ep_map.ep_mapping[i];

		अगर (!ep_num) अणु
			rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG,
				"Invalid endpoint map setting!\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	rtlusb->usb_tx_post_hdl =
		 rtlpriv->cfg->usb_पूर्णांकerface_cfg->usb_tx_post_hdl;
	rtlusb->usb_tx_cleanup	=
		 rtlpriv->cfg->usb_पूर्णांकerface_cfg->usb_tx_cleanup;
	rtlusb->usb_tx_aggregate_hdl =
		 (rtlpriv->cfg->usb_पूर्णांकerface_cfg->usb_tx_aggregate_hdl)
		 ? rtlpriv->cfg->usb_पूर्णांकerface_cfg->usb_tx_aggregate_hdl
		 : &_none_usb_tx_aggregate_hdl;

	init_usb_anchor(&rtlusb->tx_submitted);
	क्रम (i = 0; i < RTL_USB_MAX_EP_NUM; i++) अणु
		skb_queue_head_init(&rtlusb->tx_skb_queue[i]);
		init_usb_anchor(&rtlusb->tx_pending[i]);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम _rtl_rx_work(काष्ठा tasklet_काष्ठा *t);

अटल पूर्णांक _rtl_usb_init_rx(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_usb_priv *usb_priv = rtl_usbpriv(hw);
	काष्ठा rtl_usb *rtlusb = rtl_usbdev(usb_priv);

	rtlusb->rx_max_size = rtlpriv->cfg->usb_पूर्णांकerface_cfg->rx_max_size;
	rtlusb->rx_urb_num = rtlpriv->cfg->usb_पूर्णांकerface_cfg->rx_urb_num;
	rtlusb->in_ep = rtlpriv->cfg->usb_पूर्णांकerface_cfg->in_ep_num;
	rtlusb->usb_rx_hdl = rtlpriv->cfg->usb_पूर्णांकerface_cfg->usb_rx_hdl;
	rtlusb->usb_rx_segregate_hdl =
		rtlpriv->cfg->usb_पूर्णांकerface_cfg->usb_rx_segregate_hdl;

	pr_info("rx_max_size %d, rx_urb_num %d, in_ep %d\n",
		rtlusb->rx_max_size, rtlusb->rx_urb_num, rtlusb->in_ep);
	init_usb_anchor(&rtlusb->rx_submitted);
	init_usb_anchor(&rtlusb->rx_cleanup_urbs);

	skb_queue_head_init(&rtlusb->rx_queue);
	tasklet_setup(&rtlusb->rx_work_tasklet, _rtl_rx_work);

	वापस 0;
पूर्ण

अटल पूर्णांक _rtl_usb_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_usb_priv *usb_priv = rtl_usbpriv(hw);
	काष्ठा rtl_usb *rtlusb = rtl_usbdev(usb_priv);
	पूर्णांक err;
	u8 epidx;
	काष्ठा usb_पूर्णांकerface	*usb_पूर्णांकf = rtlusb->पूर्णांकf;
	u8 epnums = usb_पूर्णांकf->cur_altsetting->desc.bNumEndpoपूर्णांकs;

	rtlusb->out_ep_nums = rtlusb->in_ep_nums = 0;
	क्रम (epidx = 0; epidx < epnums; epidx++) अणु
		काष्ठा usb_endpoपूर्णांक_descriptor *pep_desc;

		pep_desc = &usb_पूर्णांकf->cur_altsetting->endpoपूर्णांक[epidx].desc;

		अगर (usb_endpoपूर्णांक_dir_in(pep_desc))
			rtlusb->in_ep_nums++;
		अन्यथा अगर (usb_endpoपूर्णांक_dir_out(pep_desc))
			rtlusb->out_ep_nums++;

		rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG,
			"USB EP(0x%02x), MaxPacketSize=%d, Interval=%d\n",
			pep_desc->bEndpoपूर्णांकAddress, pep_desc->wMaxPacketSize,
			pep_desc->bInterval);
	पूर्ण
	अगर (rtlusb->in_ep_nums <  rtlpriv->cfg->usb_पूर्णांकerface_cfg->in_ep_num) अणु
		pr_err("Too few input end points found\n");
		वापस -EINVAL;
	पूर्ण
	अगर (rtlusb->out_ep_nums == 0) अणु
		pr_err("No output end points found\n");
		वापस -EINVAL;
	पूर्ण
	/* usb endpoपूर्णांक mapping */
	err = rtlpriv->cfg->usb_पूर्णांकerface_cfg->usb_endpoपूर्णांक_mapping(hw);
	rtlusb->usb_mq_to_hwq =  rtlpriv->cfg->usb_पूर्णांकerface_cfg->usb_mq_to_hwq;
	_rtl_usb_init_tx(hw);
	_rtl_usb_init_rx(hw);
	वापस err;
पूर्ण

अटल व्योम rtl_usb_init_sw(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_usb *rtlusb = rtl_usbdev(rtl_usbpriv(hw));

	rtlhal->hw = hw;
	ppsc->inactiveps = false;
	ppsc->leisure_ps = false;
	ppsc->fwctrl_lps = false;
	ppsc->reg_fwctrl_lps = 3;
	ppsc->reg_max_lps_awakeपूर्णांकvl = 5;
	ppsc->fwctrl_psmode = FW_PS_DTIM_MODE;

	 /* IBSS */
	mac->beacon_पूर्णांकerval = 100;

	 /* AMPDU */
	mac->min_space_cfg = 0;
	mac->max_mss_density = 0;

	/* set sane AMPDU शेषs */
	mac->current_ampdu_density = 7;
	mac->current_ampdu_factor = 3;

	/* QOS */
	rtlusb->acm_method = EACMWAY2_SW;

	/* IRQ */
	/* HIMR - turn all on */
	rtlusb->irq_mask[0] = 0xFFFFFFFF;
	/* HIMR_EX - turn all on */
	rtlusb->irq_mask[1] = 0xFFFFFFFF;
	rtlusb->disablehwsm =  true;
पूर्ण

अटल व्योम _rtl_rx_completed(काष्ठा urb *urb);

अटल पूर्णांक _rtl_prep_rx_urb(काष्ठा ieee80211_hw *hw, काष्ठा rtl_usb *rtlusb,
			      काष्ठा urb *urb, gfp_t gfp_mask)
अणु
	व्योम *buf;

	buf = usb_alloc_coherent(rtlusb->udev, rtlusb->rx_max_size, gfp_mask,
				 &urb->transfer_dma);
	अगर (!buf) अणु
		pr_err("Failed to usb_alloc_coherent!!\n");
		वापस -ENOMEM;
	पूर्ण

	usb_fill_bulk_urb(urb, rtlusb->udev,
			  usb_rcvbulkpipe(rtlusb->udev, rtlusb->in_ep),
			  buf, rtlusb->rx_max_size, _rtl_rx_completed, rtlusb);
	urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	वापस 0;
पूर्ण

अटल व्योम _rtl_usb_rx_process_agg(काष्ठा ieee80211_hw *hw,
				    काष्ठा sk_buff *skb)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 *rxdesc = skb->data;
	काष्ठा ieee80211_hdr *hdr;
	bool unicast = false;
	__le16 fc;
	काष्ठा ieee80211_rx_status rx_status = अणु0पूर्ण;
	काष्ठा rtl_stats stats = अणु
		.संकेत = 0,
		.rate = 0,
	पूर्ण;

	skb_pull(skb, RTL_RX_DESC_SIZE);
	rtlpriv->cfg->ops->query_rx_desc(hw, &stats, &rx_status, rxdesc, skb);
	skb_pull(skb, (stats.rx_drvinfo_size + stats.rx_bufshअगरt));
	hdr = (काष्ठा ieee80211_hdr *)(skb->data);
	fc = hdr->frame_control;
	अगर (!stats.crc) अणु
		स_नकल(IEEE80211_SKB_RXCB(skb), &rx_status, माप(rx_status));

		अगर (is_broadcast_ether_addr(hdr->addr1)) अणु
			/*TODO*/;
		पूर्ण अन्यथा अगर (is_multicast_ether_addr(hdr->addr1)) अणु
			/*TODO*/
		पूर्ण अन्यथा अणु
			unicast = true;
			rtlpriv->stats.rxbytesunicast +=  skb->len;
		पूर्ण

		अगर (ieee80211_is_data(fc)) अणु
			rtlpriv->cfg->ops->led_control(hw, LED_CTL_RX);

			अगर (unicast)
				rtlpriv->link_info.num_rx_inperiod++;
		पूर्ण
		/* अटल bcn क्रम roaming */
		rtl_beacon_statistic(hw, skb);
	पूर्ण
पूर्ण

अटल व्योम _rtl_usb_rx_process_noagg(काष्ठा ieee80211_hw *hw,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 *rxdesc = skb->data;
	काष्ठा ieee80211_hdr *hdr;
	bool unicast = false;
	__le16 fc;
	काष्ठा ieee80211_rx_status rx_status = अणु0पूर्ण;
	काष्ठा rtl_stats stats = अणु
		.संकेत = 0,
		.rate = 0,
	पूर्ण;

	skb_pull(skb, RTL_RX_DESC_SIZE);
	rtlpriv->cfg->ops->query_rx_desc(hw, &stats, &rx_status, rxdesc, skb);
	skb_pull(skb, (stats.rx_drvinfo_size + stats.rx_bufshअगरt));
	hdr = (काष्ठा ieee80211_hdr *)(skb->data);
	fc = hdr->frame_control;
	अगर (!stats.crc) अणु
		स_नकल(IEEE80211_SKB_RXCB(skb), &rx_status, माप(rx_status));

		अगर (is_broadcast_ether_addr(hdr->addr1)) अणु
			/*TODO*/;
		पूर्ण अन्यथा अगर (is_multicast_ether_addr(hdr->addr1)) अणु
			/*TODO*/
		पूर्ण अन्यथा अणु
			unicast = true;
			rtlpriv->stats.rxbytesunicast +=  skb->len;
		पूर्ण

		अगर (ieee80211_is_data(fc)) अणु
			rtlpriv->cfg->ops->led_control(hw, LED_CTL_RX);

			अगर (unicast)
				rtlpriv->link_info.num_rx_inperiod++;
		पूर्ण

		/* अटल bcn क्रम roaming */
		rtl_beacon_statistic(hw, skb);

		अगर (likely(rtl_action_proc(hw, skb, false)))
			ieee80211_rx(hw, skb);
		अन्यथा
			dev_kमुक्त_skb_any(skb);
	पूर्ण अन्यथा अणु
		dev_kमुक्त_skb_any(skb);
	पूर्ण
पूर्ण

अटल व्योम _rtl_rx_pre_process(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *_skb;
	काष्ठा sk_buff_head rx_queue;
	काष्ठा rtl_usb *rtlusb = rtl_usbdev(rtl_usbpriv(hw));

	skb_queue_head_init(&rx_queue);
	अगर (rtlusb->usb_rx_segregate_hdl)
		rtlusb->usb_rx_segregate_hdl(hw, skb, &rx_queue);
	WARN_ON(skb_queue_empty(&rx_queue));
	जबतक (!skb_queue_empty(&rx_queue)) अणु
		_skb = skb_dequeue(&rx_queue);
		_rtl_usb_rx_process_agg(hw, _skb);
		ieee80211_rx(hw, _skb);
	पूर्ण
पूर्ण

#घोषणा __RX_SKB_MAX_QUEUED	64

अटल व्योम _rtl_rx_work(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा rtl_usb *rtlusb = from_tasklet(rtlusb, t, rx_work_tasklet);
	काष्ठा ieee80211_hw *hw = usb_get_पूर्णांकfdata(rtlusb->पूर्णांकf);
	काष्ठा sk_buff *skb;

	जबतक ((skb = skb_dequeue(&rtlusb->rx_queue))) अणु
		अगर (unlikely(IS_USB_STOP(rtlusb))) अणु
			dev_kमुक्त_skb_any(skb);
			जारी;
		पूर्ण

		अगर (likely(!rtlusb->usb_rx_segregate_hdl)) अणु
			_rtl_usb_rx_process_noagg(hw, skb);
		पूर्ण अन्यथा अणु
			/* TO DO */
			_rtl_rx_pre_process(hw, skb);
			pr_err("rx agg not supported\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक _rtl_rx_get_padding(काष्ठा ieee80211_hdr *hdr,
					अचिन्हित पूर्णांक len)
अणु
#अगर NET_IP_ALIGN != 0
	अचिन्हित पूर्णांक padding = 0;
#पूर्ण_अगर

	/* make function no-op when possible */
	अगर (NET_IP_ALIGN == 0 || len < माप(*hdr))
		वापस 0;

#अगर NET_IP_ALIGN != 0
	/* alignment calculation as in lbtf_rx() / carl9170_rx_copy_data() */
	/* TODO: deduplicate common code, define helper function instead? */

	अगर (ieee80211_is_data_qos(hdr->frame_control)) अणु
		u8 *qc = ieee80211_get_qos_ctl(hdr);

		padding ^= NET_IP_ALIGN;

		/* Input might be invalid, aव्योम accessing memory outside
		 * the buffer.
		 */
		अगर ((अचिन्हित दीर्घ)qc - (अचिन्हित दीर्घ)hdr < len &&
		    *qc & IEEE80211_QOS_CTL_A_MSDU_PRESENT)
			padding ^= NET_IP_ALIGN;
	पूर्ण

	अगर (ieee80211_has_a4(hdr->frame_control))
		padding ^= NET_IP_ALIGN;

	वापस padding;
#पूर्ण_अगर
पूर्ण

#घोषणा __RADIO_TAP_SIZE_RSV	32

अटल व्योम _rtl_rx_completed(काष्ठा urb *_urb)
अणु
	काष्ठा rtl_usb *rtlusb = (काष्ठा rtl_usb *)_urb->context;
	पूर्णांक err = 0;

	अगर (unlikely(IS_USB_STOP(rtlusb)))
		जाओ मुक्त;

	अगर (likely(0 == _urb->status)) अणु
		अचिन्हित पूर्णांक padding;
		काष्ठा sk_buff *skb;
		अचिन्हित पूर्णांक qlen;
		अचिन्हित पूर्णांक size = _urb->actual_length;
		काष्ठा ieee80211_hdr *hdr;

		अगर (size < RTL_RX_DESC_SIZE + माप(काष्ठा ieee80211_hdr)) अणु
			pr_err("Too short packet from bulk IN! (len: %d)\n",
			       size);
			जाओ resubmit;
		पूर्ण

		qlen = skb_queue_len(&rtlusb->rx_queue);
		अगर (qlen >= __RX_SKB_MAX_QUEUED) अणु
			pr_err("Pending RX skbuff queue full! (qlen: %d)\n",
			       qlen);
			जाओ resubmit;
		पूर्ण

		hdr = (व्योम *)(_urb->transfer_buffer + RTL_RX_DESC_SIZE);
		padding = _rtl_rx_get_padding(hdr, size - RTL_RX_DESC_SIZE);

		skb = dev_alloc_skb(size + __RADIO_TAP_SIZE_RSV + padding);
		अगर (!skb) अणु
			pr_err("Can't allocate skb for bulk IN!\n");
			जाओ resubmit;
		पूर्ण

		_rtl_install_trx_info(rtlusb, skb, rtlusb->in_ep);

		/* Make sure the payload data is 4 byte aligned. */
		skb_reserve(skb, padding);

		/* reserve some space क्रम mac80211's radiotap */
		skb_reserve(skb, __RADIO_TAP_SIZE_RSV);

		skb_put_data(skb, _urb->transfer_buffer, size);

		skb_queue_tail(&rtlusb->rx_queue, skb);
		tasklet_schedule(&rtlusb->rx_work_tasklet);

		जाओ resubmit;
	पूर्ण

	चयन (_urb->status) अणु
	/* disconnect */
	हाल -ENOENT:
	हाल -ECONNRESET:
	हाल -ENODEV:
	हाल -ESHUTDOWN:
		जाओ मुक्त;
	शेष:
		अवरोध;
	पूर्ण

resubmit:
	usb_anchor_urb(_urb, &rtlusb->rx_submitted);
	err = usb_submit_urb(_urb, GFP_ATOMIC);
	अगर (unlikely(err)) अणु
		usb_unanchor_urb(_urb);
		जाओ मुक्त;
	पूर्ण
	वापस;

मुक्त:
	/* On some architectures, usb_मुक्त_coherent must not be called from
	 * hardirq context. Queue urb to cleanup list.
	 */
	usb_anchor_urb(_urb, &rtlusb->rx_cleanup_urbs);
पूर्ण

#अघोषित __RADIO_TAP_SIZE_RSV

अटल व्योम _rtl_usb_cleanup_rx(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_usb *rtlusb = rtl_usbdev(rtl_usbpriv(hw));
	काष्ठा urb *urb;

	usb_समाप्त_anchored_urbs(&rtlusb->rx_submitted);

	tasklet_समाप्त(&rtlusb->rx_work_tasklet);
	cancel_work_sync(&rtlpriv->works.lps_change_work);

	अगर (rtlpriv->works.rtl_wq) अणु
		destroy_workqueue(rtlpriv->works.rtl_wq);
		rtlpriv->works.rtl_wq = शून्य;
	पूर्ण

	skb_queue_purge(&rtlusb->rx_queue);

	जबतक ((urb = usb_get_from_anchor(&rtlusb->rx_cleanup_urbs))) अणु
		usb_मुक्त_coherent(urb->dev, urb->transfer_buffer_length,
				urb->transfer_buffer, urb->transfer_dma);
		usb_मुक्त_urb(urb);
	पूर्ण
पूर्ण

अटल पूर्णांक _rtl_usb_receive(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा urb *urb;
	पूर्णांक err;
	पूर्णांक i;
	काष्ठा rtl_usb *rtlusb = rtl_usbdev(rtl_usbpriv(hw));

	WARN_ON(0 == rtlusb->rx_urb_num);
	/* 1600 == 1514 + max WLAN header + rtk info */
	WARN_ON(rtlusb->rx_max_size < 1600);

	क्रम (i = 0; i < rtlusb->rx_urb_num; i++) अणु
		err = -ENOMEM;
		urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!urb)
			जाओ err_out;

		err = _rtl_prep_rx_urb(hw, rtlusb, urb, GFP_KERNEL);
		अगर (err < 0) अणु
			pr_err("Failed to prep_rx_urb!!\n");
			usb_मुक्त_urb(urb);
			जाओ err_out;
		पूर्ण

		usb_anchor_urb(urb, &rtlusb->rx_submitted);
		err = usb_submit_urb(urb, GFP_KERNEL);
		अगर (err) अणु
			usb_unanchor_urb(urb);
			usb_मुक्त_urb(urb);
			जाओ err_out;
		पूर्ण
		usb_मुक्त_urb(urb);
	पूर्ण
	वापस 0;

err_out:
	usb_समाप्त_anchored_urbs(&rtlusb->rx_submitted);
	वापस err;
पूर्ण

अटल पूर्णांक rtl_usb_start(काष्ठा ieee80211_hw *hw)
अणु
	पूर्णांक err;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_usb *rtlusb = rtl_usbdev(rtl_usbpriv(hw));

	err = rtlpriv->cfg->ops->hw_init(hw);
	अगर (!err) अणु
		rtl_init_rx_config(hw);

		/* Enable software */
		SET_USB_START(rtlusb);
		/* should after adapter start and पूर्णांकerrupt enable. */
		set_hal_start(rtlhal);

		/* Start bulk IN */
		err = _rtl_usb_receive(hw);
	पूर्ण

	वापस err;
पूर्ण

/*=======================  tx =========================================*/
अटल व्योम rtl_usb_cleanup(काष्ठा ieee80211_hw *hw)
अणु
	u32 i;
	काष्ठा sk_buff *_skb;
	काष्ठा rtl_usb *rtlusb = rtl_usbdev(rtl_usbpriv(hw));
	काष्ठा ieee80211_tx_info *txinfo;

	/* clean up rx stuff. */
	_rtl_usb_cleanup_rx(hw);

	/* clean up tx stuff */
	क्रम (i = 0; i < RTL_USB_MAX_EP_NUM; i++) अणु
		जबतक ((_skb = skb_dequeue(&rtlusb->tx_skb_queue[i]))) अणु
			rtlusb->usb_tx_cleanup(hw, _skb);
			txinfo = IEEE80211_SKB_CB(_skb);
			ieee80211_tx_info_clear_status(txinfo);
			txinfo->flags |= IEEE80211_TX_STAT_ACK;
			ieee80211_tx_status_irqsafe(hw, _skb);
		पूर्ण
		usb_समाप्त_anchored_urbs(&rtlusb->tx_pending[i]);
	पूर्ण
	usb_समाप्त_anchored_urbs(&rtlusb->tx_submitted);
पूर्ण

/* We may add some काष्ठा पूर्णांकo काष्ठा rtl_usb later. Do deinit here.  */
अटल व्योम rtl_usb_deinit(काष्ठा ieee80211_hw *hw)
अणु
	rtl_usb_cleanup(hw);
पूर्ण

अटल व्योम rtl_usb_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_usb *rtlusb = rtl_usbdev(rtl_usbpriv(hw));
	काष्ठा urb *urb;

	/* should after adapter start and पूर्णांकerrupt enable. */
	set_hal_stop(rtlhal);
	cancel_work_sync(&rtlpriv->works.fill_h2c_cmd);
	/* Enable software */
	SET_USB_STOP(rtlusb);

	/* मुक्त pre-allocated URBs from rtl_usb_start() */
	usb_समाप्त_anchored_urbs(&rtlusb->rx_submitted);

	tasklet_समाप्त(&rtlusb->rx_work_tasklet);
	cancel_work_sync(&rtlpriv->works.lps_change_work);
	cancel_work_sync(&rtlpriv->works.update_beacon_work);

	flush_workqueue(rtlpriv->works.rtl_wq);

	skb_queue_purge(&rtlusb->rx_queue);

	जबतक ((urb = usb_get_from_anchor(&rtlusb->rx_cleanup_urbs))) अणु
		usb_मुक्त_coherent(urb->dev, urb->transfer_buffer_length,
				urb->transfer_buffer, urb->transfer_dma);
		usb_मुक्त_urb(urb);
	पूर्ण

	rtlpriv->cfg->ops->hw_disable(hw);
पूर्ण

अटल व्योम _rtl_submit_tx_urb(काष्ठा ieee80211_hw *hw, काष्ठा urb *_urb)
अणु
	पूर्णांक err;
	काष्ठा rtl_usb *rtlusb = rtl_usbdev(rtl_usbpriv(hw));

	usb_anchor_urb(_urb, &rtlusb->tx_submitted);
	err = usb_submit_urb(_urb, GFP_ATOMIC);
	अगर (err < 0) अणु
		काष्ठा sk_buff *skb;

		pr_err("Failed to submit urb\n");
		usb_unanchor_urb(_urb);
		skb = (काष्ठा sk_buff *)_urb->context;
		kमुक्त_skb(skb);
	पूर्ण
	usb_मुक्त_urb(_urb);
पूर्ण

अटल पूर्णांक _usb_tx_post(काष्ठा ieee80211_hw *hw, काष्ठा urb *urb,
			काष्ठा sk_buff *skb)
अणु
	काष्ठा rtl_usb *rtlusb = rtl_usbdev(rtl_usbpriv(hw));
	काष्ठा ieee80211_tx_info *txinfo;

	rtlusb->usb_tx_post_hdl(hw, urb, skb);
	skb_pull(skb, RTL_TX_HEADER_SIZE);
	txinfo = IEEE80211_SKB_CB(skb);
	ieee80211_tx_info_clear_status(txinfo);
	txinfo->flags |= IEEE80211_TX_STAT_ACK;

	अगर (urb->status) अणु
		pr_err("Urb has error status 0x%X\n", urb->status);
		जाओ out;
	पूर्ण
	/*  TODO:	statistics */
out:
	ieee80211_tx_status_irqsafe(hw, skb);
	वापस urb->status;
पूर्ण

अटल व्योम _rtl_tx_complete(काष्ठा urb *urb)
अणु
	काष्ठा sk_buff *skb = (काष्ठा sk_buff *)urb->context;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा rtl_usb *rtlusb = (काष्ठा rtl_usb *)info->rate_driver_data[0];
	काष्ठा ieee80211_hw *hw = usb_get_पूर्णांकfdata(rtlusb->पूर्णांकf);
	पूर्णांक err;

	अगर (unlikely(IS_USB_STOP(rtlusb)))
		वापस;
	err = _usb_tx_post(hw, urb, skb);
	अगर (err) अणु
		/* Ignore error and keep issuiing other urbs */
		वापस;
	पूर्ण
पूर्ण

अटल काष्ठा urb *_rtl_usb_tx_urb_setup(काष्ठा ieee80211_hw *hw,
				काष्ठा sk_buff *skb, u32 ep_num)
अणु
	काष्ठा rtl_usb *rtlusb = rtl_usbdev(rtl_usbpriv(hw));
	काष्ठा urb *_urb;

	WARN_ON(शून्य == skb);
	_urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!_urb)
		वापस शून्य;
	_rtl_install_trx_info(rtlusb, skb, ep_num);
	usb_fill_bulk_urb(_urb, rtlusb->udev, usb_sndbulkpipe(rtlusb->udev,
			  ep_num), skb->data, skb->len, _rtl_tx_complete, skb);
	_urb->transfer_flags |= URB_ZERO_PACKET;
	वापस _urb;
पूर्ण

अटल व्योम _rtl_usb_transmit(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb,
		       क्रमागत rtl_txq qnum)
अणु
	काष्ठा rtl_usb *rtlusb = rtl_usbdev(rtl_usbpriv(hw));
	u32 ep_num;
	काष्ठा urb *_urb = शून्य;

	WARN_ON(शून्य == rtlusb->usb_tx_aggregate_hdl);
	अगर (unlikely(IS_USB_STOP(rtlusb))) अणु
		pr_err("USB device is stopping...\n");
		kमुक्त_skb(skb);
		वापस;
	पूर्ण
	ep_num = rtlusb->ep_map.ep_mapping[qnum];
	_urb = _rtl_usb_tx_urb_setup(hw, skb, ep_num);
	अगर (unlikely(!_urb)) अणु
		pr_err("Can't allocate urb. Drop skb!\n");
		kमुक्त_skb(skb);
		वापस;
	पूर्ण
	_rtl_submit_tx_urb(hw, _urb);
पूर्ण

अटल व्योम _rtl_usb_tx_preprocess(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_sta *sta,
				   काष्ठा sk_buff *skb,
				   u16 hw_queue)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा rtl_tx_desc *pdesc = शून्य;
	काष्ठा rtl_tcb_desc tcb_desc;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)(skb->data);
	__le16 fc = hdr->frame_control;
	u8 *pda_addr = hdr->addr1;

	स_रखो(&tcb_desc, 0, माप(काष्ठा rtl_tcb_desc));
	अगर (ieee80211_is_auth(fc)) अणु
		rtl_dbg(rtlpriv, COMP_SEND, DBG_DMESG, "MAC80211_LINKING\n");
	पूर्ण

	अगर (rtlpriv->psc.sw_ps_enabled) अणु
		अगर (ieee80211_is_data(fc) && !ieee80211_is_nullfunc(fc) &&
		    !ieee80211_has_pm(fc))
			hdr->frame_control |= cpu_to_le16(IEEE80211_FCTL_PM);
	पूर्ण

	rtl_action_proc(hw, skb, true);
	अगर (is_multicast_ether_addr(pda_addr))
		rtlpriv->stats.txbytesmulticast += skb->len;
	अन्यथा अगर (is_broadcast_ether_addr(pda_addr))
		rtlpriv->stats.txbytesbroadcast += skb->len;
	अन्यथा
		rtlpriv->stats.txbytesunicast += skb->len;
	rtlpriv->cfg->ops->fill_tx_desc(hw, hdr, (u8 *)pdesc, शून्य, info, sta, skb,
					hw_queue, &tcb_desc);
	अगर (ieee80211_is_data(fc))
		rtlpriv->cfg->ops->led_control(hw, LED_CTL_TX);
पूर्ण

अटल पूर्णांक rtl_usb_tx(काष्ठा ieee80211_hw *hw,
		      काष्ठा ieee80211_sta *sta,
		      काष्ठा sk_buff *skb,
		      काष्ठा rtl_tcb_desc *dummy)
अणु
	काष्ठा rtl_usb *rtlusb = rtl_usbdev(rtl_usbpriv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)(skb->data);
	__le16 fc = hdr->frame_control;
	u16 hw_queue;

	अगर (unlikely(is_hal_stop(rtlhal)))
		जाओ err_मुक्त;
	hw_queue = rtlusb->usb_mq_to_hwq(fc, skb_get_queue_mapping(skb));
	_rtl_usb_tx_preprocess(hw, sta, skb, hw_queue);
	_rtl_usb_transmit(hw, skb, hw_queue);
	वापस NETDEV_TX_OK;

err_मुक्त:
	dev_kमुक्त_skb_any(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल bool rtl_usb_tx_chk_रुकोq_insert(काष्ठा ieee80211_hw *hw,
					काष्ठा ieee80211_sta *sta,
					काष्ठा sk_buff *skb)
अणु
	वापस false;
पूर्ण

अटल व्योम rtl_fill_h2c_cmd_work_callback(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtl_works *rtlworks =
	    container_of(work, काष्ठा rtl_works, fill_h2c_cmd);
	काष्ठा ieee80211_hw *hw = rtlworks->hw;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->cfg->ops->fill_h2c_cmd(hw, H2C_RA_MASK, 5, rtlpriv->rate_mask);
पूर्ण

अटल स्थिर काष्ठा rtl_पूर्णांकf_ops rtl_usb_ops = अणु
	.adapter_start = rtl_usb_start,
	.adapter_stop = rtl_usb_stop,
	.adapter_tx = rtl_usb_tx,
	.रुकोq_insert = rtl_usb_tx_chk_रुकोq_insert,
पूर्ण;

पूर्णांक rtl_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		  स्थिर काष्ठा usb_device_id *id,
		  काष्ठा rtl_hal_cfg *rtl_hal_cfg)
अणु
	पूर्णांक err;
	काष्ठा ieee80211_hw *hw = शून्य;
	काष्ठा rtl_priv *rtlpriv = शून्य;
	काष्ठा usb_device	*udev;
	काष्ठा rtl_usb_priv *usb_priv;

	hw = ieee80211_alloc_hw(माप(काष्ठा rtl_priv) +
				माप(काष्ठा rtl_usb_priv), &rtl_ops);
	अगर (!hw) अणु
		WARN_ONCE(true, "rtl_usb: ieee80211 alloc failed\n");
		वापस -ENOMEM;
	पूर्ण
	rtlpriv = hw->priv;
	rtlpriv->hw = hw;
	rtlpriv->usb_data = kसुस्मृति(RTL_USB_MAX_RX_COUNT, माप(u32),
				    GFP_KERNEL);
	अगर (!rtlpriv->usb_data) अणु
		ieee80211_मुक्त_hw(hw);
		वापस -ENOMEM;
	पूर्ण

	/* this spin lock must be initialized early */
	spin_lock_init(&rtlpriv->locks.usb_lock);
	INIT_WORK(&rtlpriv->works.fill_h2c_cmd,
		  rtl_fill_h2c_cmd_work_callback);
	INIT_WORK(&rtlpriv->works.lps_change_work,
		  rtl_lps_change_work_callback);
	INIT_WORK(&rtlpriv->works.update_beacon_work,
		  rtl_update_beacon_work_callback);

	rtlpriv->usb_data_index = 0;
	init_completion(&rtlpriv->firmware_loading_complete);
	SET_IEEE80211_DEV(hw, &पूर्णांकf->dev);
	udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	usb_get_dev(udev);
	usb_priv = rtl_usbpriv(hw);
	स_रखो(usb_priv, 0, माप(*usb_priv));
	usb_priv->dev.पूर्णांकf = पूर्णांकf;
	usb_priv->dev.udev = udev;
	usb_set_पूर्णांकfdata(पूर्णांकf, hw);
	/* init cfg & पूर्णांकf_ops */
	rtlpriv->rtlhal.पूर्णांकerface = INTF_USB;
	rtlpriv->cfg = rtl_hal_cfg;
	rtlpriv->पूर्णांकf_ops = &rtl_usb_ops;
	/* Init IO handler */
	_rtl_usb_io_handler_init(&udev->dev, hw);
	rtlpriv->cfg->ops->पढ़ो_chip_version(hw);
	/*like पढ़ो eeprom and so on */
	rtlpriv->cfg->ops->पढ़ो_eeprom_info(hw);
	err = _rtl_usb_init(hw);
	अगर (err)
		जाओ error_out2;
	rtl_usb_init_sw(hw);
	/* Init mac80211 sw */
	err = rtl_init_core(hw);
	अगर (err) अणु
		pr_err("Can't allocate sw for mac80211\n");
		जाओ error_out2;
	पूर्ण
	अगर (rtlpriv->cfg->ops->init_sw_vars(hw)) अणु
		pr_err("Can't init_sw_vars\n");
		जाओ error_out;
	पूर्ण
	rtlpriv->cfg->ops->init_sw_leds(hw);

	err = ieee80211_रेजिस्टर_hw(hw);
	अगर (err) अणु
		pr_err("Can't register mac80211 hw.\n");
		जाओ error_out;
	पूर्ण
	rtlpriv->mac80211.mac80211_रेजिस्टरed = 1;

	set_bit(RTL_STATUS_INTERFACE_START, &rtlpriv->status);
	वापस 0;

error_out:
	rtl_deinit_core(hw);
error_out2:
	_rtl_usb_io_handler_release(hw);
	usb_put_dev(udev);
	complete(&rtlpriv->firmware_loading_complete);
	kमुक्त(rtlpriv->usb_data);
	ieee80211_मुक्त_hw(hw);
	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL(rtl_usb_probe);

व्योम rtl_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा ieee80211_hw *hw = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *rtlmac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_usb *rtlusb = rtl_usbdev(rtl_usbpriv(hw));

	अगर (unlikely(!rtlpriv))
		वापस;
	/* just in हाल driver is हटाओd beक्रमe firmware callback */
	रुको_क्रम_completion(&rtlpriv->firmware_loading_complete);
	clear_bit(RTL_STATUS_INTERFACE_START, &rtlpriv->status);
	/*ieee80211_unरेजिस्टर_hw will call ops_stop */
	अगर (rtlmac->mac80211_रेजिस्टरed == 1) अणु
		ieee80211_unरेजिस्टर_hw(hw);
		rtlmac->mac80211_रेजिस्टरed = 0;
	पूर्ण अन्यथा अणु
		rtl_deinit_deferred_work(hw, false);
		rtlpriv->पूर्णांकf_ops->adapter_stop(hw);
	पूर्ण
	/*deinit rfसमाप्त */
	/* rtl_deinit_rfसमाप्त(hw); */
	rtl_usb_deinit(hw);
	rtl_deinit_core(hw);
	kमुक्त(rtlpriv->usb_data);
	rtlpriv->cfg->ops->deinit_sw_leds(hw);
	rtlpriv->cfg->ops->deinit_sw_vars(hw);
	_rtl_usb_io_handler_release(hw);
	usb_put_dev(rtlusb->udev);
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	ieee80211_मुक्त_hw(hw);
पूर्ण
EXPORT_SYMBOL(rtl_usb_disconnect);

पूर्णांक rtl_usb_suspend(काष्ठा usb_पूर्णांकerface *pusb_पूर्णांकf, pm_message_t message)
अणु
	वापस 0;
पूर्ण
EXPORT_SYMBOL(rtl_usb_suspend);

पूर्णांक rtl_usb_resume(काष्ठा usb_पूर्णांकerface *pusb_पूर्णांकf)
अणु
	वापस 0;
पूर्ण
EXPORT_SYMBOL(rtl_usb_resume);
