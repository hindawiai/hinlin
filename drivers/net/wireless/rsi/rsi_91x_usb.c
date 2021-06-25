<शैली गुरु>
/*
 * Copyright (c) 2014 Redpine Signals Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <net/rsi_91x.h>
#समावेश "rsi_usb.h"
#समावेश "rsi_hal.h"
#समावेश "rsi_coex.h"

/* Default operating mode is wlan STA + BT */
अटल u16 dev_oper_mode = DEV_OPMODE_STA_BT_DUAL;
module_param(dev_oper_mode, uलघु, 0444);
MODULE_PARM_DESC(dev_oper_mode,
		 "1[Wi-Fi], 4[BT], 8[BT LE], 5[Wi-Fi STA + BT classic]\n"
		 "9[Wi-Fi STA + BT LE], 13[Wi-Fi STA + BT classic + BT LE]\n"
		 "6[AP + BT classic], 14[AP + BT classic + BT LE]");

अटल पूर्णांक rsi_rx_urb_submit(काष्ठा rsi_hw *adapter, u8 ep_num, gfp_t flags);

/**
 * rsi_usb_card_ग_लिखो() - This function ग_लिखोs to the USB Card.
 * @adapter: Poपूर्णांकer to the adapter काष्ठाure.
 * @buf: Poपूर्णांकer to the buffer from where the data has to be taken.
 * @len: Length to be written.
 * @endpoपूर्णांक: Type of endpoपूर्णांक.
 *
 * Return: status: 0 on success, a negative error code on failure.
 */
अटल पूर्णांक rsi_usb_card_ग_लिखो(काष्ठा rsi_hw *adapter,
			      u8 *buf,
			      u16 len,
			      u8 endpoपूर्णांक)
अणु
	काष्ठा rsi_91x_usbdev *dev = (काष्ठा rsi_91x_usbdev *)adapter->rsi_dev;
	पूर्णांक status;
	u8 *seg = dev->tx_buffer;
	पूर्णांक transfer;
	पूर्णांक ep = dev->bulkout_endpoपूर्णांक_addr[endpoपूर्णांक - 1];

	स_रखो(seg, 0, len + RSI_USB_TX_HEAD_ROOM);
	स_नकल(seg + RSI_USB_TX_HEAD_ROOM, buf, len);
	len += RSI_USB_TX_HEAD_ROOM;
	transfer = len;
	status = usb_bulk_msg(dev->usbdev,
			      usb_sndbulkpipe(dev->usbdev, ep),
			      (व्योम *)seg,
			      (पूर्णांक)len,
			      &transfer,
			      HZ * 5);

	अगर (status < 0) अणु
		rsi_dbg(ERR_ZONE,
			"Card write failed with error code :%10d\n", status);
		dev->ग_लिखो_fail = 1;
	पूर्ण
	वापस status;
पूर्ण

/**
 * rsi_ग_लिखो_multiple() - This function ग_लिखोs multiple bytes of inक्रमmation
 *			  to the USB card.
 * @adapter: Poपूर्णांकer to the adapter काष्ठाure.
 * @endpoपूर्णांक: Type of endpoपूर्णांक.
 * @data: Poपूर्णांकer to the data that has to be written.
 * @count: Number of multiple bytes to be written.
 *
 * Return: 0 on success, a negative error code on failure.
 */
अटल पूर्णांक rsi_ग_लिखो_multiple(काष्ठा rsi_hw *adapter,
			      u8 endpoपूर्णांक,
			      u8 *data,
			      u32 count)
अणु
	काष्ठा rsi_91x_usbdev *dev;

	अगर (!adapter)
		वापस -ENODEV;

	अगर (endpoपूर्णांक == 0)
		वापस -EINVAL;

	dev = (काष्ठा rsi_91x_usbdev *)adapter->rsi_dev;
	अगर (dev->ग_लिखो_fail)
		वापस -ENETDOWN;

	वापस rsi_usb_card_ग_लिखो(adapter, data, count, endpoपूर्णांक);
पूर्ण

/**
 * rsi_find_bulk_in_and_out_endpoपूर्णांकs() - This function initializes the bulk
 *					  endpoपूर्णांकs to the device.
 * @पूर्णांकerface: Poपूर्णांकer to the USB पूर्णांकerface काष्ठाure.
 * @adapter: Poपूर्णांकer to the adapter काष्ठाure.
 *
 * Return: ret_val: 0 on success, -ENOMEM on failure.
 */
अटल पूर्णांक rsi_find_bulk_in_and_out_endpoपूर्णांकs(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
					      काष्ठा rsi_hw *adapter)
अणु
	काष्ठा rsi_91x_usbdev *dev = (काष्ठा rsi_91x_usbdev *)adapter->rsi_dev;
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	__le16 buffer_size;
	पूर्णांक ii, bin_found = 0, bout_found = 0;

	अगरace_desc = पूर्णांकerface->cur_altsetting;

	क्रम (ii = 0; ii < अगरace_desc->desc.bNumEndpoपूर्णांकs; ++ii) अणु
		endpoपूर्णांक = &(अगरace_desc->endpoपूर्णांक[ii].desc);

		अगर (!dev->bulkin_endpoपूर्णांक_addr[bin_found] &&
		    (endpoपूर्णांक->bEndpoपूर्णांकAddress & USB_सूची_IN) &&
		    ((endpoपूर्णांक->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) ==
		    USB_ENDPOINT_XFER_BULK)) अणु
			buffer_size = endpoपूर्णांक->wMaxPacketSize;
			dev->bulkin_size[bin_found] = buffer_size;
			dev->bulkin_endpoपूर्णांक_addr[bin_found] =
				endpoपूर्णांक->bEndpoपूर्णांकAddress;
			bin_found++;
		पूर्ण

		अगर (!dev->bulkout_endpoपूर्णांक_addr[bout_found] &&
		    !(endpoपूर्णांक->bEndpoपूर्णांकAddress & USB_सूची_IN) &&
		    ((endpoपूर्णांक->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) ==
		    USB_ENDPOINT_XFER_BULK)) अणु
			buffer_size = endpoपूर्णांक->wMaxPacketSize;
			dev->bulkout_endpoपूर्णांक_addr[bout_found] =
				endpoपूर्णांक->bEndpoपूर्णांकAddress;
			dev->bulkout_size[bout_found] = buffer_size;
			bout_found++;
		पूर्ण

		अगर (bin_found >= MAX_BULK_EP || bout_found >= MAX_BULK_EP)
			अवरोध;
	पूर्ण

	अगर (!(dev->bulkin_endpoपूर्णांक_addr[0] && dev->bulkout_endpoपूर्णांक_addr[0])) अणु
		dev_err(&पूर्णांकerface->dev, "missing wlan bulk endpoints\n");
		वापस -EINVAL;
	पूर्ण

	अगर (adapter->priv->coex_mode > 1) अणु
		अगर (!dev->bulkin_endpoपूर्णांक_addr[1]) अणु
			dev_err(&पूर्णांकerface->dev, "missing bt bulk-in endpoint\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा RSI_USB_REQ_OUT	(USB_TYPE_VENDOR | USB_सूची_OUT | USB_RECIP_DEVICE)
#घोषणा RSI_USB_REQ_IN	(USB_TYPE_VENDOR | USB_सूची_IN | USB_RECIP_DEVICE)

/* rsi_usb_reg_पढ़ो() - This function पढ़ोs data from given रेजिस्टर address.
 * @usbdev: Poपूर्णांकer to the usb_device काष्ठाure.
 * @reg: Address of the रेजिस्टर to be पढ़ो.
 * @value: Value to be पढ़ो.
 * @len: length of data to be पढ़ो.
 *
 * Return: status: 0 on success, a negative error code on failure.
 */
अटल पूर्णांक rsi_usb_reg_पढ़ो(काष्ठा usb_device *usbdev,
			    u32 reg,
			    u16 *value,
			    u16 len)
अणु
	u8 *buf;
	पूर्णांक status = -ENOMEM;

	अगर (len > RSI_USB_CTRL_BUF_SIZE)
		वापस -EINVAL;

	buf  = kदो_स्मृति(RSI_USB_CTRL_BUF_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस status;

	status = usb_control_msg(usbdev,
				 usb_rcvctrlpipe(usbdev, 0),
				 USB_VENDOR_REGISTER_READ,
				 RSI_USB_REQ_IN,
				 ((reg & 0xffff0000) >> 16), (reg & 0xffff),
				 (व्योम *)buf,
				 len,
				 USB_CTRL_GET_TIMEOUT);

	*value = (buf[0] | (buf[1] << 8));
	अगर (status < 0) अणु
		rsi_dbg(ERR_ZONE,
			"%s: Reg read failed with error code :%d\n",
			__func__, status);
	पूर्ण
	kमुक्त(buf);

	वापस status;
पूर्ण

/**
 * rsi_usb_reg_ग_लिखो() - This function ग_लिखोs the given data पूर्णांकo the given
 *			 रेजिस्टर address.
 * @usbdev: Poपूर्णांकer to the usb_device काष्ठाure.
 * @reg: Address of the रेजिस्टर.
 * @value: Value to ग_लिखो.
 * @len: Length of data to be written.
 *
 * Return: status: 0 on success, a negative error code on failure.
 */
अटल पूर्णांक rsi_usb_reg_ग_लिखो(काष्ठा usb_device *usbdev,
			     u32 reg,
			     u32 value,
			     u16 len)
अणु
	u8 *usb_reg_buf;
	पूर्णांक status = -ENOMEM;

	अगर (len > RSI_USB_CTRL_BUF_SIZE)
		वापस -EINVAL;

	usb_reg_buf  = kदो_स्मृति(RSI_USB_CTRL_BUF_SIZE, GFP_KERNEL);
	अगर (!usb_reg_buf)
		वापस status;

	usb_reg_buf[0] = (cpu_to_le32(value) & 0x00ff);
	usb_reg_buf[1] = (cpu_to_le32(value) & 0xff00) >> 8;
	usb_reg_buf[2] = (cpu_to_le32(value) & 0x00ff0000) >> 16;
	usb_reg_buf[3] = (cpu_to_le32(value) & 0xff000000) >> 24;

	status = usb_control_msg(usbdev,
				 usb_sndctrlpipe(usbdev, 0),
				 USB_VENDOR_REGISTER_WRITE,
				 RSI_USB_REQ_OUT,
				 ((cpu_to_le32(reg) & 0xffff0000) >> 16),
				 (cpu_to_le32(reg) & 0xffff),
				 (व्योम *)usb_reg_buf,
				 len,
				 USB_CTRL_SET_TIMEOUT);
	अगर (status < 0) अणु
		rsi_dbg(ERR_ZONE,
			"%s: Reg write failed with error code :%d\n",
			__func__, status);
	पूर्ण
	kमुक्त(usb_reg_buf);

	वापस status;
पूर्ण

/**
 * rsi_rx_करोne_handler() - This function is called when a packet is received
 *			   from USB stack. This is callback to receive करोne.
 * @urb: Received URB.
 *
 * Return: None.
 */
अटल व्योम rsi_rx_करोne_handler(काष्ठा urb *urb)
अणु
	काष्ठा rx_usb_ctrl_block *rx_cb = urb->context;
	काष्ठा rsi_91x_usbdev *dev = (काष्ठा rsi_91x_usbdev *)rx_cb->data;
	पूर्णांक status = -EINVAL;

	अगर (urb->status) अणु
		dev_kमुक्त_skb(rx_cb->rx_skb);
		वापस;
	पूर्ण

	अगर (urb->actual_length <= 0 ||
	    urb->actual_length > rx_cb->rx_skb->len) अणु
		rsi_dbg(INFO_ZONE, "%s: Invalid packet length = %d\n",
			__func__, urb->actual_length);
		जाओ out;
	पूर्ण
	अगर (skb_queue_len(&dev->rx_q) >= RSI_MAX_RX_PKTS) अणु
		rsi_dbg(INFO_ZONE, "Max RX packets reached\n");
		जाओ out;
	पूर्ण
	skb_trim(rx_cb->rx_skb, urb->actual_length);
	skb_queue_tail(&dev->rx_q, rx_cb->rx_skb);

	rsi_set_event(&dev->rx_thपढ़ो.event);
	status = 0;

out:
	अगर (rsi_rx_urb_submit(dev->priv, rx_cb->ep_num, GFP_ATOMIC))
		rsi_dbg(ERR_ZONE, "%s: Failed in urb submission", __func__);

	अगर (status)
		dev_kमुक्त_skb(rx_cb->rx_skb);
पूर्ण

अटल व्योम rsi_rx_urb_समाप्त(काष्ठा rsi_hw *adapter, u8 ep_num)
अणु
	काष्ठा rsi_91x_usbdev *dev = (काष्ठा rsi_91x_usbdev *)adapter->rsi_dev;
	काष्ठा rx_usb_ctrl_block *rx_cb = &dev->rx_cb[ep_num - 1];
	काष्ठा urb *urb = rx_cb->rx_urb;

	usb_समाप्त_urb(urb);
पूर्ण

/**
 * rsi_rx_urb_submit() - This function submits the given URB to the USB stack.
 * @adapter: Poपूर्णांकer to the adapter काष्ठाure.
 * @ep_num: Endpoपूर्णांक number.
 * @mem_flags: The type of memory to allocate.
 *
 * Return: 0 on success, a negative error code on failure.
 */
अटल पूर्णांक rsi_rx_urb_submit(काष्ठा rsi_hw *adapter, u8 ep_num, gfp_t mem_flags)
अणु
	काष्ठा rsi_91x_usbdev *dev = (काष्ठा rsi_91x_usbdev *)adapter->rsi_dev;
	काष्ठा rx_usb_ctrl_block *rx_cb = &dev->rx_cb[ep_num - 1];
	काष्ठा urb *urb = rx_cb->rx_urb;
	पूर्णांक status;
	काष्ठा sk_buff *skb;
	u8 dword_align_bytes = 0;

#घोषणा RSI_MAX_RX_USB_PKT_SIZE	3000
	skb = dev_alloc_skb(RSI_MAX_RX_USB_PKT_SIZE);
	अगर (!skb)
		वापस -ENOMEM;
	skb_reserve(skb, MAX_DWORD_ALIGN_BYTES);
	skb_put(skb, RSI_MAX_RX_USB_PKT_SIZE - MAX_DWORD_ALIGN_BYTES);
	dword_align_bytes = (अचिन्हित दीर्घ)skb->data & 0x3f;
	अगर (dword_align_bytes > 0)
		skb_push(skb, dword_align_bytes);
	urb->transfer_buffer = skb->data;
	rx_cb->rx_skb = skb;

	usb_fill_bulk_urb(urb,
			  dev->usbdev,
			  usb_rcvbulkpipe(dev->usbdev,
			  dev->bulkin_endpoपूर्णांक_addr[ep_num - 1]),
			  urb->transfer_buffer,
			  skb->len,
			  rsi_rx_करोne_handler,
			  rx_cb);

	status = usb_submit_urb(urb, mem_flags);
	अगर (status) अणु
		rsi_dbg(ERR_ZONE, "%s: Failed in urb submission\n", __func__);
		dev_kमुक्त_skb(skb);
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक rsi_usb_पढ़ो_रेजिस्टर_multiple(काष्ठा rsi_hw *adapter, u32 addr,
					  u8 *data, u16 count)
अणु
	काष्ठा rsi_91x_usbdev *dev = (काष्ठा rsi_91x_usbdev *)adapter->rsi_dev;
	u8 *buf;
	u16 transfer;
	पूर्णांक status;

	अगर (!addr)
		वापस -EINVAL;

	buf = kzalloc(RSI_USB_BUF_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	जबतक (count) अणु
		transfer = min_t(u16, count, RSI_USB_BUF_SIZE);
		status = usb_control_msg(dev->usbdev,
					 usb_rcvctrlpipe(dev->usbdev, 0),
					 USB_VENDOR_REGISTER_READ,
					 RSI_USB_REQ_IN,
					 ((addr & 0xffff0000) >> 16),
					 (addr & 0xffff), (व्योम *)buf,
					 transfer, USB_CTRL_GET_TIMEOUT);
		अगर (status < 0) अणु
			rsi_dbg(ERR_ZONE,
				"Reg read failed with error code :%d\n",
				 status);
			kमुक्त(buf);
			वापस status;
		पूर्ण
		स_नकल(data, buf, transfer);
		count -= transfer;
		data += transfer;
		addr += transfer;
	पूर्ण
	kमुक्त(buf);
	वापस 0;
पूर्ण

/**
 * rsi_usb_ग_लिखो_रेजिस्टर_multiple() - This function ग_लिखोs multiple bytes of
 *				       inक्रमmation to multiple रेजिस्टरs.
 * @adapter: Poपूर्णांकer to the adapter काष्ठाure.
 * @addr: Address of the रेजिस्टर.
 * @data: Poपूर्णांकer to the data that has to be written.
 * @count: Number of multiple bytes to be written on to the रेजिस्टरs.
 *
 * Return: status: 0 on success, a negative error code on failure.
 */
अटल पूर्णांक rsi_usb_ग_लिखो_रेजिस्टर_multiple(काष्ठा rsi_hw *adapter, u32 addr,
					   u8 *data, u16 count)
अणु
	काष्ठा rsi_91x_usbdev *dev = (काष्ठा rsi_91x_usbdev *)adapter->rsi_dev;
	u8 *buf;
	u16 transfer;
	पूर्णांक status = 0;

	buf = kzalloc(RSI_USB_BUF_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	जबतक (count) अणु
		transfer = min_t(u16, count, RSI_USB_BUF_SIZE);
		स_नकल(buf, data, transfer);
		status = usb_control_msg(dev->usbdev,
					 usb_sndctrlpipe(dev->usbdev, 0),
					 USB_VENDOR_REGISTER_WRITE,
					 RSI_USB_REQ_OUT,
					 ((addr & 0xffff0000) >> 16),
					 (addr & 0xffff),
					 (व्योम *)buf,
					 transfer,
					 USB_CTRL_SET_TIMEOUT);
		अगर (status < 0) अणु
			rsi_dbg(ERR_ZONE,
				"Reg write failed with error code :%d\n",
				status);
			kमुक्त(buf);
			वापस status;
		पूर्ण
		count -= transfer;
		data += transfer;
		addr += transfer;
	पूर्ण

	kमुक्त(buf);
	वापस 0;
पूर्ण

/**
 *rsi_usb_host_पूर्णांकf_ग_लिखो_pkt() - This function ग_लिखोs the packet to the
 *				   USB card.
 * @adapter: Poपूर्णांकer to the adapter काष्ठाure.
 * @pkt: Poपूर्णांकer to the data to be written on to the card.
 * @len: Length of the data to be written on to the card.
 *
 * Return: 0 on success, a negative error code on failure.
 */
अटल पूर्णांक rsi_usb_host_पूर्णांकf_ग_लिखो_pkt(काष्ठा rsi_hw *adapter,
				       u8 *pkt,
				       u32 len)
अणु
	u32 queueno = ((pkt[1] >> 4) & 0x7);
	u8 endpoपूर्णांक;

	endpoपूर्णांक = ((queueno == RSI_WIFI_MGMT_Q || queueno == RSI_WIFI_DATA_Q ||
		     queueno == RSI_COEX_Q) ? WLAN_EP : BT_EP);

	वापस rsi_ग_लिखो_multiple(adapter,
				  endpoपूर्णांक,
				  (u8 *)pkt,
				  len);
पूर्ण

अटल पूर्णांक rsi_usb_master_reg_पढ़ो(काष्ठा rsi_hw *adapter, u32 reg,
				   u32 *value, u16 len)
अणु
	काष्ठा usb_device *usbdev =
		((काष्ठा rsi_91x_usbdev *)adapter->rsi_dev)->usbdev;
	u16 temp;
	पूर्णांक ret;

	ret = rsi_usb_reg_पढ़ो(usbdev, reg, &temp, len);
	अगर (ret < 0)
		वापस ret;
	*value = temp;

	वापस 0;
पूर्ण

अटल पूर्णांक rsi_usb_master_reg_ग_लिखो(काष्ठा rsi_hw *adapter,
				    अचिन्हित दीर्घ reg,
				    अचिन्हित दीर्घ value, u16 len)
अणु
	काष्ठा usb_device *usbdev =
		((काष्ठा rsi_91x_usbdev *)adapter->rsi_dev)->usbdev;

	वापस rsi_usb_reg_ग_लिखो(usbdev, reg, value, len);
पूर्ण

अटल पूर्णांक rsi_usb_load_data_master_ग_लिखो(काष्ठा rsi_hw *adapter,
					  u32 base_address,
					  u32 inकाष्ठाions_sz, u16 block_size,
					  u8 *ta_firmware)
अणु
	u16 num_blocks;
	u32 cur_indx, i;
	u8 temp_buf[256];
	पूर्णांक status;

	num_blocks = inकाष्ठाions_sz / block_size;
	rsi_dbg(INFO_ZONE, "num_blocks: %d\n", num_blocks);

	क्रम (cur_indx = 0, i = 0; i < num_blocks; i++, cur_indx += block_size) अणु
		स_नकल(temp_buf, ta_firmware + cur_indx, block_size);
		status = rsi_usb_ग_लिखो_रेजिस्टर_multiple(adapter, base_address,
							 (u8 *)(temp_buf),
							 block_size);
		अगर (status < 0)
			वापस status;

		rsi_dbg(INFO_ZONE, "%s: loading block: %d\n", __func__, i);
		base_address += block_size;
	पूर्ण

	अगर (inकाष्ठाions_sz % block_size) अणु
		स_रखो(temp_buf, 0, block_size);
		स_नकल(temp_buf, ta_firmware + cur_indx,
		       inकाष्ठाions_sz % block_size);
		status = rsi_usb_ग_लिखो_रेजिस्टर_multiple
						(adapter, base_address,
						 (u8 *)temp_buf,
						 inकाष्ठाions_sz % block_size);
		अगर (status < 0)
			वापस status;
		rsi_dbg(INFO_ZONE,
			"Written Last Block in Address 0x%x Successfully\n",
			cur_indx);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा rsi_host_पूर्णांकf_ops usb_host_पूर्णांकf_ops = अणु
	.ग_लिखो_pkt		= rsi_usb_host_पूर्णांकf_ग_लिखो_pkt,
	.पढ़ो_reg_multiple	= rsi_usb_पढ़ो_रेजिस्टर_multiple,
	.ग_लिखो_reg_multiple	= rsi_usb_ग_लिखो_रेजिस्टर_multiple,
	.master_reg_पढ़ो	= rsi_usb_master_reg_पढ़ो,
	.master_reg_ग_लिखो	= rsi_usb_master_reg_ग_लिखो,
	.load_data_master_ग_लिखो	= rsi_usb_load_data_master_ग_लिखो,
पूर्ण;

/**
 * rsi_deinit_usb_पूर्णांकerface() - This function deinitializes the usb पूर्णांकerface.
 * @adapter: Poपूर्णांकer to the adapter काष्ठाure.
 *
 * Return: None.
 */
अटल व्योम rsi_deinit_usb_पूर्णांकerface(काष्ठा rsi_hw *adapter)
अणु
	काष्ठा rsi_91x_usbdev *dev = (काष्ठा rsi_91x_usbdev *)adapter->rsi_dev;

	rsi_समाप्त_thपढ़ो(&dev->rx_thपढ़ो);

	usb_मुक्त_urb(dev->rx_cb[0].rx_urb);
	अगर (adapter->priv->coex_mode > 1)
		usb_मुक्त_urb(dev->rx_cb[1].rx_urb);

	kमुक्त(dev->tx_buffer);
पूर्ण

अटल पूर्णांक rsi_usb_init_rx(काष्ठा rsi_hw *adapter)
अणु
	काष्ठा rsi_91x_usbdev *dev = (काष्ठा rsi_91x_usbdev *)adapter->rsi_dev;
	काष्ठा rx_usb_ctrl_block *rx_cb;
	u8 idx, num_rx_cb;

	num_rx_cb = (adapter->priv->coex_mode > 1 ? 2 : 1);

	क्रम (idx = 0; idx < num_rx_cb; idx++) अणु
		rx_cb = &dev->rx_cb[idx];

		rx_cb->rx_urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!rx_cb->rx_urb) अणु
			rsi_dbg(ERR_ZONE, "Failed alloc rx urb[%d]\n", idx);
			जाओ err;
		पूर्ण
		rx_cb->ep_num = idx + 1;
		rx_cb->data = (व्योम *)dev;
	पूर्ण
	skb_queue_head_init(&dev->rx_q);
	rsi_init_event(&dev->rx_thपढ़ो.event);
	अगर (rsi_create_kthपढ़ो(adapter->priv, &dev->rx_thपढ़ो,
			       rsi_usb_rx_thपढ़ो, "RX-Thread")) अणु
		rsi_dbg(ERR_ZONE, "%s: Unable to init rx thrd\n", __func__);
		जाओ err;
	पूर्ण

	वापस 0;

err:
	usb_मुक्त_urb(dev->rx_cb[0].rx_urb);
	अगर (adapter->priv->coex_mode > 1)
		usb_मुक्त_urb(dev->rx_cb[1].rx_urb);

	वापस -1;
पूर्ण

/**
 * rsi_init_usb_पूर्णांकerface() - This function initializes the usb पूर्णांकerface.
 * @adapter: Poपूर्णांकer to the adapter काष्ठाure.
 * @pfunction: Poपूर्णांकer to USB पूर्णांकerface काष्ठाure.
 *
 * Return: 0 on success, a negative error code on failure.
 */
अटल पूर्णांक rsi_init_usb_पूर्णांकerface(काष्ठा rsi_hw *adapter,
				  काष्ठा usb_पूर्णांकerface *pfunction)
अणु
	काष्ठा rsi_91x_usbdev *rsi_dev;
	पूर्णांक status;

	rsi_dev = kzalloc(माप(*rsi_dev), GFP_KERNEL);
	अगर (!rsi_dev)
		वापस -ENOMEM;

	adapter->rsi_dev = rsi_dev;
	rsi_dev->usbdev = पूर्णांकerface_to_usbdev(pfunction);
	rsi_dev->priv = (व्योम *)adapter;

	अगर (rsi_find_bulk_in_and_out_endpoपूर्णांकs(pfunction, adapter)) अणु
		status = -EINVAL;
		जाओ fail_eps;
	पूर्ण

	adapter->device = &pfunction->dev;
	usb_set_पूर्णांकfdata(pfunction, adapter);

	rsi_dev->tx_buffer = kदो_स्मृति(2048, GFP_KERNEL);
	अगर (!rsi_dev->tx_buffer) अणु
		status = -ENOMEM;
		जाओ fail_eps;
	पूर्ण

	अगर (rsi_usb_init_rx(adapter)) अणु
		rsi_dbg(ERR_ZONE, "Failed to init RX handle\n");
		status = -ENOMEM;
		जाओ fail_rx;
	पूर्ण

	rsi_dev->tx_blk_size = 252;
	adapter->block_size = rsi_dev->tx_blk_size;

	/* Initializing function callbacks */
	adapter->check_hw_queue_status = rsi_usb_check_queue_status;
	adapter->determine_event_समयout = rsi_usb_event_समयout;
	adapter->rsi_host_पूर्णांकf = RSI_HOST_INTF_USB;
	adapter->host_पूर्णांकf_ops = &usb_host_पूर्णांकf_ops;

#अगर_घोषित CONFIG_RSI_DEBUGFS
	/* In USB, one less than the MAX_DEBUGFS_ENTRIES entries is required */
	adapter->num_debugfs_entries = (MAX_DEBUGFS_ENTRIES - 1);
#पूर्ण_अगर

	rsi_dbg(INIT_ZONE, "%s: Enabled the interface\n", __func__);
	वापस 0;

fail_rx:
	kमुक्त(rsi_dev->tx_buffer);

fail_eps:

	वापस status;
पूर्ण

अटल पूर्णांक usb_ulp_पढ़ो_ग_लिखो(काष्ठा rsi_hw *adapter, u16 addr, u32 data,
			      u16 len_in_bits)
अणु
	पूर्णांक ret;

	ret = rsi_usb_master_reg_ग_लिखो
			(adapter, RSI_GSPI_DATA_REG1,
			 ((addr << 6) | ((data >> 16) & 0xffff)), 2);
	अगर (ret < 0)
		वापस ret;

	ret = rsi_usb_master_reg_ग_लिखो(adapter, RSI_GSPI_DATA_REG0,
				       (data & 0xffff), 2);
	अगर (ret < 0)
		वापस ret;

	/* Initializing GSPI क्रम ULP पढ़ो/ग_लिखोs */
	rsi_usb_master_reg_ग_लिखो(adapter, RSI_GSPI_CTRL_REG0,
				 RSI_GSPI_CTRL_REG0_VALUE, 2);

	ret = rsi_usb_master_reg_ग_लिखो(adapter, RSI_GSPI_CTRL_REG1,
				       ((len_in_bits - 1) | RSI_GSPI_TRIG), 2);
	अगर (ret < 0)
		वापस ret;

	msleep(20);

	वापस 0;
पूर्ण

अटल पूर्णांक rsi_reset_card(काष्ठा rsi_hw *adapter)
अणु
	पूर्णांक ret;

	rsi_dbg(INFO_ZONE, "Resetting Card...\n");
	rsi_usb_master_reg_ग_लिखो(adapter, RSI_TA_HOLD_REG, 0xE, 4);

	/* This msleep will ensure Thपढ़ो-Arch processor to go to hold
	 * and any pending dma transfers to rf in device to finish.
	 */
	msleep(100);

	ret = rsi_usb_master_reg_ग_लिखो(adapter, SWBL_REGOUT,
				       RSI_FW_WDT_DISABLE_REQ,
				       RSI_COMMON_REG_SIZE);
	अगर (ret < 0) अणु
		rsi_dbg(ERR_ZONE, "Disabling firmware watchdog timer failed\n");
		जाओ fail;
	पूर्ण

	अगर (adapter->device_model != RSI_DEV_9116) अणु
		ret = usb_ulp_पढ़ो_ग_लिखो(adapter, RSI_WATCH_DOG_TIMER_1,
					 RSI_ULP_WRITE_2, 32);
		अगर (ret < 0)
			जाओ fail;
		ret = usb_ulp_पढ़ो_ग_लिखो(adapter, RSI_WATCH_DOG_TIMER_2,
					 RSI_ULP_WRITE_0, 32);
		अगर (ret < 0)
			जाओ fail;
		ret = usb_ulp_पढ़ो_ग_लिखो(adapter, RSI_WATCH_DOG_DELAY_TIMER_1,
					 RSI_ULP_WRITE_50, 32);
		अगर (ret < 0)
			जाओ fail;
		ret = usb_ulp_पढ़ो_ग_लिखो(adapter, RSI_WATCH_DOG_DELAY_TIMER_2,
					 RSI_ULP_WRITE_0, 32);
		अगर (ret < 0)
			जाओ fail;
		ret = usb_ulp_पढ़ो_ग_लिखो(adapter, RSI_WATCH_DOG_TIMER_ENABLE,
					 RSI_ULP_TIMER_ENABLE, 32);
		अगर (ret < 0)
			जाओ fail;
	पूर्ण अन्यथा अणु
		ret = rsi_usb_master_reg_ग_लिखो(adapter,
					       NWP_WWD_INTERRUPT_TIMER,
					       NWP_WWD_INT_TIMER_CLKS,
					       RSI_9116_REG_SIZE);
		अगर (ret < 0)
			जाओ fail;
		ret = rsi_usb_master_reg_ग_लिखो(adapter,
					       NWP_WWD_SYSTEM_RESET_TIMER,
					       NWP_WWD_SYS_RESET_TIMER_CLKS,
					       RSI_9116_REG_SIZE);
		अगर (ret < 0)
			जाओ fail;
		ret = rsi_usb_master_reg_ग_लिखो(adapter,
					       NWP_WWD_MODE_AND_RSTART,
					       NWP_WWD_TIMER_DISABLE,
					       RSI_9116_REG_SIZE);
		अगर (ret < 0)
			जाओ fail;
	पूर्ण

	rsi_dbg(INFO_ZONE, "Reset card done\n");
	वापस ret;

fail:
	rsi_dbg(ERR_ZONE, "Reset card failed\n");
	वापस ret;
पूर्ण

/**
 * rsi_probe() - This function is called by kernel when the driver provided
 *		 Venकरोr and device IDs are matched. All the initialization
 *		 work is करोne here.
 * @pfunction: Poपूर्णांकer to the USB पूर्णांकerface काष्ठाure.
 * @id: Poपूर्णांकer to the usb_device_id काष्ठाure.
 *
 * Return: 0 on success, a negative error code on failure.
 */
अटल पूर्णांक rsi_probe(काष्ठा usb_पूर्णांकerface *pfunction,
		     स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा rsi_hw *adapter;
	काष्ठा rsi_91x_usbdev *dev;
	u16 fw_status;
	पूर्णांक status;

	rsi_dbg(INIT_ZONE, "%s: Init function called\n", __func__);

	adapter = rsi_91x_init(dev_oper_mode);
	अगर (!adapter) अणु
		rsi_dbg(ERR_ZONE, "%s: Failed to init os intf ops\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण
	adapter->rsi_host_पूर्णांकf = RSI_HOST_INTF_USB;

	status = rsi_init_usb_पूर्णांकerface(adapter, pfunction);
	अगर (status) अणु
		rsi_dbg(ERR_ZONE, "%s: Failed to init usb interface\n",
			__func__);
		जाओ err;
	पूर्ण

	rsi_dbg(ERR_ZONE, "%s: Initialized os intf ops\n", __func__);

	अगर (id->idProduct == RSI_USB_PID_9113) अणु
		rsi_dbg(INIT_ZONE, "%s: 9113 module detected\n", __func__);
		adapter->device_model = RSI_DEV_9113;
	पूर्ण अन्यथा अगर (id->idProduct == RSI_USB_PID_9116) अणु
		rsi_dbg(INIT_ZONE, "%s: 9116 module detected\n", __func__);
		adapter->device_model = RSI_DEV_9116;
	पूर्ण अन्यथा अणु
		rsi_dbg(ERR_ZONE, "%s: Unsupported RSI device id 0x%x\n",
			__func__, id->idProduct);
		जाओ err1;
	पूर्ण

	dev = (काष्ठा rsi_91x_usbdev *)adapter->rsi_dev;

	status = rsi_usb_reg_पढ़ो(dev->usbdev, FW_STATUS_REG, &fw_status, 2);
	अगर (status < 0)
		जाओ err1;
	अन्यथा
		fw_status &= 1;

	अगर (!fw_status) अणु
		rsi_dbg(INIT_ZONE, "Loading firmware...\n");
		status = rsi_hal_device_init(adapter);
		अगर (status) अणु
			rsi_dbg(ERR_ZONE, "%s: Failed in device init\n",
				__func__);
			जाओ err1;
		पूर्ण
		rsi_dbg(INIT_ZONE, "%s: Device Init Done\n", __func__);
	पूर्ण

	status = rsi_rx_urb_submit(adapter, WLAN_EP, GFP_KERNEL);
	अगर (status)
		जाओ err1;

	अगर (adapter->priv->coex_mode > 1) अणु
		status = rsi_rx_urb_submit(adapter, BT_EP, GFP_KERNEL);
		अगर (status)
			जाओ err_समाप्त_wlan_urb;
	पूर्ण

	वापस 0;

err_समाप्त_wlan_urb:
	rsi_rx_urb_समाप्त(adapter, WLAN_EP);
err1:
	rsi_deinit_usb_पूर्णांकerface(adapter);
err:
	rsi_91x_deinit(adapter);
	rsi_dbg(ERR_ZONE, "%s: Failed in probe...Exiting\n", __func__);
	वापस status;
पूर्ण

/**
 * rsi_disconnect() - This function perक्रमms the reverse of the probe function,
 *		      it deinitialize the driver काष्ठाure.
 * @pfunction: Poपूर्णांकer to the USB पूर्णांकerface काष्ठाure.
 *
 * Return: None.
 */
अटल व्योम rsi_disconnect(काष्ठा usb_पूर्णांकerface *pfunction)
अणु
	काष्ठा rsi_hw *adapter = usb_get_पूर्णांकfdata(pfunction);

	अगर (!adapter)
		वापस;

	rsi_mac80211_detach(adapter);

	अगर (IS_ENABLED(CONFIG_RSI_COEX) && adapter->priv->coex_mode > 1 &&
	    adapter->priv->bt_adapter) अणु
		rsi_bt_ops.detach(adapter->priv->bt_adapter);
		adapter->priv->bt_adapter = शून्य;
	पूर्ण

	अगर (adapter->priv->coex_mode > 1)
		rsi_rx_urb_समाप्त(adapter, BT_EP);
	rsi_rx_urb_समाप्त(adapter, WLAN_EP);

	rsi_reset_card(adapter);
	rsi_deinit_usb_पूर्णांकerface(adapter);
	rsi_91x_deinit(adapter);

	rsi_dbg(INFO_ZONE, "%s: Deinitialization completed\n", __func__);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक rsi_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	/* Not yet implemented */
	वापस -ENOSYS;
पूर्ण

अटल पूर्णांक rsi_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	/* Not yet implemented */
	वापस -ENOSYS;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा usb_device_id rsi_dev_table[] = अणु
	अणु USB_DEVICE(RSI_USB_VENDOR_ID, RSI_USB_PID_9113) पूर्ण,
	अणु USB_DEVICE(RSI_USB_VENDOR_ID, RSI_USB_PID_9116) पूर्ण,
	अणु /* Blank */पूर्ण,
पूर्ण;

अटल काष्ठा usb_driver rsi_driver = अणु
	.name       = "RSI-USB WLAN",
	.probe      = rsi_probe,
	.disconnect = rsi_disconnect,
	.id_table   = rsi_dev_table,
#अगर_घोषित CONFIG_PM
	.suspend    = rsi_suspend,
	.resume     = rsi_resume,
#पूर्ण_अगर
पूर्ण;

module_usb_driver(rsi_driver);

MODULE_AUTHOR("Redpine Signals Inc");
MODULE_DESCRIPTION("Common USB layer for RSI drivers");
MODULE_DEVICE_TABLE(usb, rsi_dev_table);
MODULE_FIRMWARE(FIRMWARE_RSI9113);
MODULE_VERSION("0.1");
MODULE_LICENSE("Dual BSD/GPL");
