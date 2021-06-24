<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 2001 Vojtech Pavlik
 *
 *  CATC EL1210A NetMate USB Ethernet driver
 *
 *  Sponsored by SuSE
 *
 *  Based on the work of
 *		Donald Becker
 * 
 *  Old chipset support added by Simon Evans <spse@secret.org.uk> 2002
 *    - adds support क्रम Belkin F5U011
 */

/*
 * 
 * Should you need to contact me, the author, you can करो so either by
 * e-mail - mail your message to <vojtech@suse.cz>, or by paper mail:
 * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Reखुला
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/crc32.h>
#समावेश <linux/bitops.h>
#समावेश <linux/gfp.h>
#समावेश <linux/uaccess.h>

#अघोषित DEBUG

#समावेश <linux/usb.h>

/*
 * Version inक्रमmation.
 */

#घोषणा DRIVER_VERSION "v2.8"
#घोषणा DRIVER_AUTHOR "Vojtech Pavlik <vojtech@suse.cz>"
#घोषणा DRIVER_DESC "CATC EL1210A NetMate USB Ethernet driver"
#घोषणा SHORT_DRIVER_DESC "EL1210A NetMate USB Ethernet"

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

अटल स्थिर अक्षर driver_name[] = "catc";

/*
 * Some defines.
 */ 

#घोषणा STATS_UPDATE		(HZ)	/* Time between stats updates */
#घोषणा TX_TIMEOUT		(5*HZ)	/* Max समय the queue can be stopped */
#घोषणा PKT_SZ			1536	/* Max Ethernet packet size */
#घोषणा RX_MAX_BURST		15	/* Max packets per rx buffer (> 0, < 16) */
#घोषणा TX_MAX_BURST		15	/* Max full sized packets per tx buffer (> 0) */
#घोषणा CTRL_QUEUE		16	/* Max control requests in flight (घातer of two) */
#घोषणा RX_PKT_SZ		1600	/* Max size of receive packet क्रम F5U011 */

/*
 * Control requests.
 */

क्रमागत control_requests अणु
	ReadMem =	0xf1,
	GetMac =	0xf2,
	Reset =		0xf4,
	SetMac =	0xf5,
	SetRxMode =     0xf5,  /* F5U011 only */
	WriteROM =	0xf8,
	SetReg =	0xfa,
	GetReg =	0xfb,
	WriteMem =	0xfc,
	ReadROM =	0xfd,
पूर्ण;

/*
 * Registers.
 */

क्रमागत रेजिस्टर_offsets अणु
	TxBufCount =	0x20,
	RxBufCount =	0x21,
	OpModes =	0x22,
	TxQed =		0x23,
	RxQed =		0x24,
	MaxBurst =	0x25,
	RxUnit =	0x60,
	EthStatus =	0x61,
	StationAddr0 =	0x67,
	EthStats =	0x69,
	LEDCtrl =	0x81,
पूर्ण;

क्रमागत eth_stats अणु
	TxSingleColl =	0x00,
        TxMultiColl =	0x02,
        TxExcessColl =	0x04,
        RxFramErr =	0x06,
पूर्ण;

क्रमागत op_mode_bits अणु
	Op3MemWaits =	0x03,
	OpLenInclude =	0x08,
	OpRxMerge =	0x10,
	OpTxMerge =	0x20,
	OpWin95bugfix =	0x40,
	OpLoopback =	0x80,
पूर्ण;

क्रमागत rx_filter_bits अणु
	RxEnable =	0x01,
	RxPolarity =	0x02,
	RxForceOK =	0x04,
	RxMultiCast =	0x08,
	RxPromisc =	0x10,
	AltRxPromisc =  0x20, /* F5U011 uses dअगरferent bit */
पूर्ण;

क्रमागत led_values अणु
	LEDFast = 	0x01,
	LEDSlow =	0x02,
	LEDFlash =	0x03,
	LEDPulse =	0x04,
	LEDLink =	0x08,
पूर्ण;

क्रमागत link_status अणु
	LinkNoChange = 0,
	LinkGood     = 1,
	LinkBad      = 2
पूर्ण;

/*
 * The catc काष्ठा.
 */

#घोषणा CTRL_RUNNING	0
#घोषणा RX_RUNNING	1
#घोषणा TX_RUNNING	2

काष्ठा catc अणु
	काष्ठा net_device *netdev;
	काष्ठा usb_device *usbdev;

	अचिन्हित दीर्घ flags;

	अचिन्हित पूर्णांक tx_ptr, tx_idx;
	अचिन्हित पूर्णांक ctrl_head, ctrl_tail;
	spinlock_t tx_lock, ctrl_lock;

	u8 tx_buf[2][TX_MAX_BURST * (PKT_SZ + 2)];
	u8 rx_buf[RX_MAX_BURST * (PKT_SZ + 2)];
	u8 irq_buf[2];
	u8 ctrl_buf[64];
	काष्ठा usb_ctrlrequest ctrl_dr;

	काष्ठा समयr_list समयr;
	u8 stats_buf[8];
	u16 stats_vals[4];
	अचिन्हित दीर्घ last_stats;

	u8 multicast[64];

	काष्ठा ctrl_queue अणु
		u8 dir;
		u8 request;
		u16 value;
		u16 index;
		व्योम *buf;
		पूर्णांक len;
		व्योम (*callback)(काष्ठा catc *catc, काष्ठा ctrl_queue *q);
	पूर्ण ctrl_queue[CTRL_QUEUE];

	काष्ठा urb *tx_urb, *rx_urb, *irq_urb, *ctrl_urb;

	u8 is_f5u011;	/* Set अगर device is an F5U011 */
	u8 rxmode[2];	/* Used क्रम F5U011 */
	atomic_t recq_sz; /* Used क्रम F5U011 - counter of रुकोing rx packets */
पूर्ण;

/*
 * Useful macros.
 */

#घोषणा catc_get_mac(catc, mac)				catc_ctrl_msg(catc, USB_सूची_IN,  GetMac, 0, 0, mac,  6)
#घोषणा catc_reset(catc)				catc_ctrl_msg(catc, USB_सूची_OUT, Reset, 0, 0, शून्य, 0)
#घोषणा catc_set_reg(catc, reg, val)			catc_ctrl_msg(catc, USB_सूची_OUT, SetReg, val, reg, शून्य, 0)
#घोषणा catc_get_reg(catc, reg, buf)			catc_ctrl_msg(catc, USB_सूची_IN,  GetReg, 0, reg, buf, 1)
#घोषणा catc_ग_लिखो_mem(catc, addr, buf, size)		catc_ctrl_msg(catc, USB_सूची_OUT, WriteMem, 0, addr, buf, size)
#घोषणा catc_पढ़ो_mem(catc, addr, buf, size)		catc_ctrl_msg(catc, USB_सूची_IN,  ReadMem, 0, addr, buf, size)

#घोषणा f5u011_rxmode(catc, rxmode)			catc_ctrl_msg(catc, USB_सूची_OUT, SetRxMode, 0, 1, rxmode, 2)
#घोषणा f5u011_rxmode_async(catc, rxmode)		catc_ctrl_async(catc, USB_सूची_OUT, SetRxMode, 0, 1, &rxmode, 2, शून्य)
#घोषणा f5u011_mchash_async(catc, hash)			catc_ctrl_async(catc, USB_सूची_OUT, SetRxMode, 0, 2, &hash, 8, शून्य)

#घोषणा catc_set_reg_async(catc, reg, val)		catc_ctrl_async(catc, USB_सूची_OUT, SetReg, val, reg, शून्य, 0, शून्य)
#घोषणा catc_get_reg_async(catc, reg, cb)		catc_ctrl_async(catc, USB_सूची_IN, GetReg, 0, reg, शून्य, 1, cb)
#घोषणा catc_ग_लिखो_mem_async(catc, addr, buf, size)	catc_ctrl_async(catc, USB_सूची_OUT, WriteMem, 0, addr, buf, size, शून्य)

/*
 * Receive routines.
 */

अटल व्योम catc_rx_करोne(काष्ठा urb *urb)
अणु
	काष्ठा catc *catc = urb->context;
	u8 *pkt_start = urb->transfer_buffer;
	काष्ठा sk_buff *skb;
	पूर्णांक pkt_len, pkt_offset = 0;
	पूर्णांक status = urb->status;

	अगर (!catc->is_f5u011) अणु
		clear_bit(RX_RUNNING, &catc->flags);
		pkt_offset = 2;
	पूर्ण

	अगर (status) अणु
		dev_dbg(&urb->dev->dev, "rx_done, status %d, length %d\n",
			status, urb->actual_length);
		वापस;
	पूर्ण

	करो अणु
		अगर(!catc->is_f5u011) अणु
			pkt_len = le16_to_cpup((__le16*)pkt_start);
			अगर (pkt_len > urb->actual_length) अणु
				catc->netdev->stats.rx_length_errors++;
				catc->netdev->stats.rx_errors++;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			pkt_len = urb->actual_length;
		पूर्ण

		अगर (!(skb = dev_alloc_skb(pkt_len)))
			वापस;

		skb_copy_to_linear_data(skb, pkt_start + pkt_offset, pkt_len);
		skb_put(skb, pkt_len);

		skb->protocol = eth_type_trans(skb, catc->netdev);
		netअगर_rx(skb);

		catc->netdev->stats.rx_packets++;
		catc->netdev->stats.rx_bytes += pkt_len;

		/* F5U011 only करोes one packet per RX */
		अगर (catc->is_f5u011)
			अवरोध;
		pkt_start += (((pkt_len + 1) >> 6) + 1) << 6;

	पूर्ण जबतक (pkt_start - (u8 *) urb->transfer_buffer < urb->actual_length);

	अगर (catc->is_f5u011) अणु
		अगर (atomic_पढ़ो(&catc->recq_sz)) अणु
			पूर्णांक state;
			atomic_dec(&catc->recq_sz);
			netdev_dbg(catc->netdev, "getting extra packet\n");
			urb->dev = catc->usbdev;
			अगर ((state = usb_submit_urb(urb, GFP_ATOMIC)) < 0) अणु
				netdev_dbg(catc->netdev,
					   "submit(rx_urb) status %d\n", state);
			पूर्ण
		पूर्ण अन्यथा अणु
			clear_bit(RX_RUNNING, &catc->flags);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम catc_irq_करोne(काष्ठा urb *urb)
अणु
	काष्ठा catc *catc = urb->context;
	u8 *data = urb->transfer_buffer;
	पूर्णांक status = urb->status;
	अचिन्हित पूर्णांक hasdata = 0, linksts = LinkNoChange;
	पूर्णांक res;

	अगर (!catc->is_f5u011) अणु
		hasdata = data[1] & 0x80;
		अगर (data[1] & 0x40)
			linksts = LinkGood;
		अन्यथा अगर (data[1] & 0x20)
			linksts = LinkBad;
	पूर्ण अन्यथा अणु
		hasdata = (अचिन्हित पूर्णांक)(be16_to_cpup((__be16*)data) & 0x0fff);
		अगर (data[0] == 0x90)
			linksts = LinkGood;
		अन्यथा अगर (data[0] == 0xA0)
			linksts = LinkBad;
	पूर्ण

	चयन (status) अणु
	हाल 0:			/* success */
		अवरोध;
	हाल -ECONNRESET:	/* unlink */
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		वापस;
	/* -EPIPE:  should clear the halt */
	शेष:		/* error */
		dev_dbg(&urb->dev->dev,
			"irq_done, status %d, data %02x %02x.\n",
			status, data[0], data[1]);
		जाओ resubmit;
	पूर्ण

	अगर (linksts == LinkGood) अणु
		netअगर_carrier_on(catc->netdev);
		netdev_dbg(catc->netdev, "link ok\n");
	पूर्ण

	अगर (linksts == LinkBad) अणु
		netअगर_carrier_off(catc->netdev);
		netdev_dbg(catc->netdev, "link bad\n");
	पूर्ण

	अगर (hasdata) अणु
		अगर (test_and_set_bit(RX_RUNNING, &catc->flags)) अणु
			अगर (catc->is_f5u011)
				atomic_inc(&catc->recq_sz);
		पूर्ण अन्यथा अणु
			catc->rx_urb->dev = catc->usbdev;
			अगर ((res = usb_submit_urb(catc->rx_urb, GFP_ATOMIC)) < 0) अणु
				dev_err(&catc->usbdev->dev,
					"submit(rx_urb) status %d\n", res);
			पूर्ण
		पूर्ण 
	पूर्ण
resubmit:
	res = usb_submit_urb (urb, GFP_ATOMIC);
	अगर (res)
		dev_err(&catc->usbdev->dev,
			"can't resubmit intr, %s-%s, status %d\n",
			catc->usbdev->bus->bus_name,
			catc->usbdev->devpath, res);
पूर्ण

/*
 * Transmit routines.
 */

अटल पूर्णांक catc_tx_run(काष्ठा catc *catc)
अणु
	पूर्णांक status;

	अगर (catc->is_f5u011)
		catc->tx_ptr = (catc->tx_ptr + 63) & ~63;

	catc->tx_urb->transfer_buffer_length = catc->tx_ptr;
	catc->tx_urb->transfer_buffer = catc->tx_buf[catc->tx_idx];
	catc->tx_urb->dev = catc->usbdev;

	अगर ((status = usb_submit_urb(catc->tx_urb, GFP_ATOMIC)) < 0)
		dev_err(&catc->usbdev->dev, "submit(tx_urb), status %d\n",
			status);

	catc->tx_idx = !catc->tx_idx;
	catc->tx_ptr = 0;

	netअगर_trans_update(catc->netdev);
	वापस status;
पूर्ण

अटल व्योम catc_tx_करोne(काष्ठा urb *urb)
अणु
	काष्ठा catc *catc = urb->context;
	अचिन्हित दीर्घ flags;
	पूर्णांक r, status = urb->status;

	अगर (status == -ECONNRESET) अणु
		dev_dbg(&urb->dev->dev, "Tx Reset.\n");
		urb->status = 0;
		netअगर_trans_update(catc->netdev);
		catc->netdev->stats.tx_errors++;
		clear_bit(TX_RUNNING, &catc->flags);
		netअगर_wake_queue(catc->netdev);
		वापस;
	पूर्ण

	अगर (status) अणु
		dev_dbg(&urb->dev->dev, "tx_done, status %d, length %d\n",
			status, urb->actual_length);
		वापस;
	पूर्ण

	spin_lock_irqsave(&catc->tx_lock, flags);

	अगर (catc->tx_ptr) अणु
		r = catc_tx_run(catc);
		अगर (unlikely(r < 0))
			clear_bit(TX_RUNNING, &catc->flags);
	पूर्ण अन्यथा अणु
		clear_bit(TX_RUNNING, &catc->flags);
	पूर्ण

	netअगर_wake_queue(catc->netdev);

	spin_unlock_irqrestore(&catc->tx_lock, flags);
पूर्ण

अटल netdev_tx_t catc_start_xmit(काष्ठा sk_buff *skb,
					 काष्ठा net_device *netdev)
अणु
	काष्ठा catc *catc = netdev_priv(netdev);
	अचिन्हित दीर्घ flags;
	पूर्णांक r = 0;
	अक्षर *tx_buf;

	spin_lock_irqsave(&catc->tx_lock, flags);

	catc->tx_ptr = (((catc->tx_ptr - 1) >> 6) + 1) << 6;
	tx_buf = catc->tx_buf[catc->tx_idx] + catc->tx_ptr;
	अगर (catc->is_f5u011)
		*(__be16 *)tx_buf = cpu_to_be16(skb->len);
	अन्यथा
		*(__le16 *)tx_buf = cpu_to_le16(skb->len);
	skb_copy_from_linear_data(skb, tx_buf + 2, skb->len);
	catc->tx_ptr += skb->len + 2;

	अगर (!test_and_set_bit(TX_RUNNING, &catc->flags)) अणु
		r = catc_tx_run(catc);
		अगर (r < 0)
			clear_bit(TX_RUNNING, &catc->flags);
	पूर्ण

	अगर ((catc->is_f5u011 && catc->tx_ptr) ||
	    (catc->tx_ptr >= ((TX_MAX_BURST - 1) * (PKT_SZ + 2))))
		netअगर_stop_queue(netdev);

	spin_unlock_irqrestore(&catc->tx_lock, flags);

	अगर (r >= 0) अणु
		catc->netdev->stats.tx_bytes += skb->len;
		catc->netdev->stats.tx_packets++;
	पूर्ण

	dev_kमुक्त_skb(skb);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम catc_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा catc *catc = netdev_priv(netdev);

	dev_warn(&netdev->dev, "Transmit timed out.\n");
	usb_unlink_urb(catc->tx_urb);
पूर्ण

/*
 * Control messages.
 */

अटल पूर्णांक catc_ctrl_msg(काष्ठा catc *catc, u8 dir, u8 request, u16 value, u16 index, व्योम *buf, पूर्णांक len)
अणु
        पूर्णांक retval = usb_control_msg(catc->usbdev,
		dir ? usb_rcvctrlpipe(catc->usbdev, 0) : usb_sndctrlpipe(catc->usbdev, 0),
		 request, 0x40 | dir, value, index, buf, len, 1000);
        वापस retval < 0 ? retval : 0;
पूर्ण

अटल व्योम catc_ctrl_run(काष्ठा catc *catc)
अणु
	काष्ठा ctrl_queue *q = catc->ctrl_queue + catc->ctrl_tail;
	काष्ठा usb_device *usbdev = catc->usbdev;
	काष्ठा urb *urb = catc->ctrl_urb;
	काष्ठा usb_ctrlrequest *dr = &catc->ctrl_dr;
	पूर्णांक status;

	dr->bRequest = q->request;
	dr->bRequestType = 0x40 | q->dir;
	dr->wValue = cpu_to_le16(q->value);
	dr->wIndex = cpu_to_le16(q->index);
	dr->wLength = cpu_to_le16(q->len);

        urb->pipe = q->dir ? usb_rcvctrlpipe(usbdev, 0) : usb_sndctrlpipe(usbdev, 0);
	urb->transfer_buffer_length = q->len;
	urb->transfer_buffer = catc->ctrl_buf;
	urb->setup_packet = (व्योम *) dr;
	urb->dev = usbdev;

	अगर (!q->dir && q->buf && q->len)
		स_नकल(catc->ctrl_buf, q->buf, q->len);

	अगर ((status = usb_submit_urb(catc->ctrl_urb, GFP_ATOMIC)))
		dev_err(&catc->usbdev->dev, "submit(ctrl_urb) status %d\n",
			status);
पूर्ण

अटल व्योम catc_ctrl_करोne(काष्ठा urb *urb)
अणु
	काष्ठा catc *catc = urb->context;
	काष्ठा ctrl_queue *q;
	अचिन्हित दीर्घ flags;
	पूर्णांक status = urb->status;

	अगर (status)
		dev_dbg(&urb->dev->dev, "ctrl_done, status %d, len %d.\n",
			status, urb->actual_length);

	spin_lock_irqsave(&catc->ctrl_lock, flags);

	q = catc->ctrl_queue + catc->ctrl_tail;

	अगर (q->dir) अणु
		अगर (q->buf && q->len)
			स_नकल(q->buf, catc->ctrl_buf, q->len);
		अन्यथा
			q->buf = catc->ctrl_buf;
	पूर्ण

	अगर (q->callback)
		q->callback(catc, q);

	catc->ctrl_tail = (catc->ctrl_tail + 1) & (CTRL_QUEUE - 1);

	अगर (catc->ctrl_head != catc->ctrl_tail)
		catc_ctrl_run(catc);
	अन्यथा
		clear_bit(CTRL_RUNNING, &catc->flags);

	spin_unlock_irqrestore(&catc->ctrl_lock, flags);
पूर्ण

अटल पूर्णांक catc_ctrl_async(काष्ठा catc *catc, u8 dir, u8 request, u16 value,
	u16 index, व्योम *buf, पूर्णांक len, व्योम (*callback)(काष्ठा catc *catc, काष्ठा ctrl_queue *q))
अणु
	काष्ठा ctrl_queue *q;
	पूर्णांक retval = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&catc->ctrl_lock, flags);
	
	q = catc->ctrl_queue + catc->ctrl_head;

	q->dir = dir;
	q->request = request;
	q->value = value;
	q->index = index;
	q->buf = buf;
	q->len = len;
	q->callback = callback;

	catc->ctrl_head = (catc->ctrl_head + 1) & (CTRL_QUEUE - 1);

	अगर (catc->ctrl_head == catc->ctrl_tail) अणु
		dev_err(&catc->usbdev->dev, "ctrl queue full\n");
		catc->ctrl_tail = (catc->ctrl_tail + 1) & (CTRL_QUEUE - 1);
		retval = -1;
	पूर्ण

	अगर (!test_and_set_bit(CTRL_RUNNING, &catc->flags))
		catc_ctrl_run(catc);

	spin_unlock_irqrestore(&catc->ctrl_lock, flags);

	वापस retval;
पूर्ण

/*
 * Statistics.
 */

अटल व्योम catc_stats_करोne(काष्ठा catc *catc, काष्ठा ctrl_queue *q)
अणु
	पूर्णांक index = q->index - EthStats;
	u16 data, last;

	catc->stats_buf[index] = *((अक्षर *)q->buf);

	अगर (index & 1)
		वापस;

	data = ((u16)catc->stats_buf[index] << 8) | catc->stats_buf[index + 1];
	last = catc->stats_vals[index >> 1];

	चयन (index) अणु
		हाल TxSingleColl:
		हाल TxMultiColl:
			catc->netdev->stats.collisions += data - last;
			अवरोध;
		हाल TxExcessColl:
			catc->netdev->stats.tx_पातed_errors += data - last;
			catc->netdev->stats.tx_errors += data - last;
			अवरोध;
		हाल RxFramErr:
			catc->netdev->stats.rx_frame_errors += data - last;
			catc->netdev->stats.rx_errors += data - last;
			अवरोध;
	पूर्ण

	catc->stats_vals[index >> 1] = data;
पूर्ण

अटल व्योम catc_stats_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा catc *catc = from_समयr(catc, t, समयr);
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++)
		catc_get_reg_async(catc, EthStats + 7 - i, catc_stats_करोne);

	mod_समयr(&catc->समयr, jअगरfies + STATS_UPDATE);
पूर्ण

/*
 * Receive modes. Broadcast, Multicast, Promisc.
 */

अटल व्योम catc_multicast(अचिन्हित अक्षर *addr, u8 *multicast)
अणु
	u32 crc;

	crc = ether_crc_le(6, addr);
	multicast[(crc >> 3) & 0x3f] |= 1 << (crc & 7);
पूर्ण

अटल व्योम catc_set_multicast_list(काष्ठा net_device *netdev)
अणु
	काष्ठा catc *catc = netdev_priv(netdev);
	काष्ठा netdev_hw_addr *ha;
	u8 broadcast[ETH_ALEN];
	u8 rx = RxEnable | RxPolarity | RxMultiCast;

	eth_broadcast_addr(broadcast);
	स_रखो(catc->multicast, 0, 64);

	catc_multicast(broadcast, catc->multicast);
	catc_multicast(netdev->dev_addr, catc->multicast);

	अगर (netdev->flags & IFF_PROMISC) अणु
		स_रखो(catc->multicast, 0xff, 64);
		rx |= (!catc->is_f5u011) ? RxPromisc : AltRxPromisc;
	पूर्ण 

	अगर (netdev->flags & IFF_ALLMULTI) अणु
		स_रखो(catc->multicast, 0xff, 64);
	पूर्ण अन्यथा अणु
		netdev_क्रम_each_mc_addr(ha, netdev) अणु
			u32 crc = ether_crc_le(6, ha->addr);
			अगर (!catc->is_f5u011) अणु
				catc->multicast[(crc >> 3) & 0x3f] |= 1 << (crc & 7);
			पूर्ण अन्यथा अणु
				catc->multicast[7-(crc >> 29)] |= 1 << ((crc >> 26) & 7);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (!catc->is_f5u011) अणु
		catc_set_reg_async(catc, RxUnit, rx);
		catc_ग_लिखो_mem_async(catc, 0xfa80, catc->multicast, 64);
	पूर्ण अन्यथा अणु
		f5u011_mchash_async(catc, catc->multicast);
		अगर (catc->rxmode[0] != rx) अणु
			catc->rxmode[0] = rx;
			netdev_dbg(catc->netdev,
				   "Setting RX mode to %2.2X %2.2X\n",
				   catc->rxmode[0], catc->rxmode[1]);
			f5u011_rxmode_async(catc, catc->rxmode);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम catc_get_drvinfo(काष्ठा net_device *dev,
			     काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा catc *catc = netdev_priv(dev);
	strlcpy(info->driver, driver_name, माप(info->driver));
	strlcpy(info->version, DRIVER_VERSION, माप(info->version));
	usb_make_path(catc->usbdev, info->bus_info, माप(info->bus_info));
पूर्ण

अटल पूर्णांक catc_get_link_ksettings(काष्ठा net_device *dev,
				   काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा catc *catc = netdev_priv(dev);
	अगर (!catc->is_f5u011)
		वापस -EOPNOTSUPP;

	ethtool_link_ksettings_zero_link_mode(cmd, supported);
	ethtool_link_ksettings_add_link_mode(cmd, supported, 10baseT_Half);
	ethtool_link_ksettings_add_link_mode(cmd, supported, TP);

	ethtool_link_ksettings_zero_link_mode(cmd, advertising);
	ethtool_link_ksettings_add_link_mode(cmd, advertising, 10baseT_Half);
	ethtool_link_ksettings_add_link_mode(cmd, advertising, TP);

	cmd->base.speed = SPEED_10;
	cmd->base.duplex = DUPLEX_HALF;
	cmd->base.port = PORT_TP;
	cmd->base.phy_address = 0;
	cmd->base.स्वतःneg = AUTONEG_DISABLE;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ops = अणु
	.get_drvinfo = catc_get_drvinfo,
	.get_link = ethtool_op_get_link,
	.get_link_ksettings = catc_get_link_ksettings,
पूर्ण;

/*
 * Open, बंद.
 */

अटल पूर्णांक catc_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा catc *catc = netdev_priv(netdev);
	पूर्णांक status;

	catc->irq_urb->dev = catc->usbdev;
	अगर ((status = usb_submit_urb(catc->irq_urb, GFP_KERNEL)) < 0) अणु
		dev_err(&catc->usbdev->dev, "submit(irq_urb) status %d\n",
			status);
		वापस -1;
	पूर्ण

	netअगर_start_queue(netdev);

	अगर (!catc->is_f5u011)
		mod_समयr(&catc->समयr, jअगरfies + STATS_UPDATE);

	वापस 0;
पूर्ण

अटल पूर्णांक catc_stop(काष्ठा net_device *netdev)
अणु
	काष्ठा catc *catc = netdev_priv(netdev);

	netअगर_stop_queue(netdev);

	अगर (!catc->is_f5u011)
		del_समयr_sync(&catc->समयr);

	usb_समाप्त_urb(catc->rx_urb);
	usb_समाप्त_urb(catc->tx_urb);
	usb_समाप्त_urb(catc->irq_urb);
	usb_समाप्त_urb(catc->ctrl_urb);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops catc_netdev_ops = अणु
	.nकरो_खोलो		= catc_खोलो,
	.nकरो_stop		= catc_stop,
	.nकरो_start_xmit		= catc_start_xmit,

	.nकरो_tx_समयout		= catc_tx_समयout,
	.nकरो_set_rx_mode	= catc_set_multicast_list,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

/*
 * USB probe, disconnect.
 */

अटल पूर्णांक catc_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा device *dev = &पूर्णांकf->dev;
	काष्ठा usb_device *usbdev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा net_device *netdev;
	काष्ठा catc *catc;
	u8 broadcast[ETH_ALEN];
	पूर्णांक pktsz, ret;

	अगर (usb_set_पूर्णांकerface(usbdev,
			पूर्णांकf->altsetting->desc.bInterfaceNumber, 1)) अणु
		dev_err(dev, "Can't set altsetting 1.\n");
		वापस -EIO;
	पूर्ण

	netdev = alloc_etherdev(माप(काष्ठा catc));
	अगर (!netdev)
		वापस -ENOMEM;

	catc = netdev_priv(netdev);

	netdev->netdev_ops = &catc_netdev_ops;
	netdev->watchकरोg_समयo = TX_TIMEOUT;
	netdev->ethtool_ops = &ops;

	catc->usbdev = usbdev;
	catc->netdev = netdev;

	spin_lock_init(&catc->tx_lock);
	spin_lock_init(&catc->ctrl_lock);

	समयr_setup(&catc->समयr, catc_stats_समयr, 0);

	catc->ctrl_urb = usb_alloc_urb(0, GFP_KERNEL);
	catc->tx_urb = usb_alloc_urb(0, GFP_KERNEL);
	catc->rx_urb = usb_alloc_urb(0, GFP_KERNEL);
	catc->irq_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर ((!catc->ctrl_urb) || (!catc->tx_urb) || 
	    (!catc->rx_urb) || (!catc->irq_urb)) अणु
		dev_err(&पूर्णांकf->dev, "No free urbs available.\n");
		ret = -ENOMEM;
		जाओ fail_मुक्त;
	पूर्ण

	/* The F5U011 has the same venकरोr/product as the neपंचांगate but a device version of 0x130 */
	अगर (le16_to_cpu(usbdev->descriptor.idVenकरोr) == 0x0423 && 
	    le16_to_cpu(usbdev->descriptor.idProduct) == 0xa &&
	    le16_to_cpu(catc->usbdev->descriptor.bcdDevice) == 0x0130) अणु
		dev_dbg(dev, "Testing for f5u011\n");
		catc->is_f5u011 = 1;		
		atomic_set(&catc->recq_sz, 0);
		pktsz = RX_PKT_SZ;
	पूर्ण अन्यथा अणु
		pktsz = RX_MAX_BURST * (PKT_SZ + 2);
	पूर्ण
	
	usb_fill_control_urb(catc->ctrl_urb, usbdev, usb_sndctrlpipe(usbdev, 0),
		शून्य, शून्य, 0, catc_ctrl_करोne, catc);

	usb_fill_bulk_urb(catc->tx_urb, usbdev, usb_sndbulkpipe(usbdev, 1),
		शून्य, 0, catc_tx_करोne, catc);

	usb_fill_bulk_urb(catc->rx_urb, usbdev, usb_rcvbulkpipe(usbdev, 1),
		catc->rx_buf, pktsz, catc_rx_करोne, catc);

	usb_fill_पूर्णांक_urb(catc->irq_urb, usbdev, usb_rcvपूर्णांकpipe(usbdev, 2),
                catc->irq_buf, 2, catc_irq_करोne, catc, 1);

	अगर (!catc->is_f5u011) अणु
		u32 *buf;
		पूर्णांक i;

		dev_dbg(dev, "Checking memory size\n");

		buf = kदो_स्मृति(4, GFP_KERNEL);
		अगर (!buf) अणु
			ret = -ENOMEM;
			जाओ fail_मुक्त;
		पूर्ण

		*buf = 0x12345678;
		catc_ग_लिखो_mem(catc, 0x7a80, buf, 4);
		*buf = 0x87654321;
		catc_ग_लिखो_mem(catc, 0xfa80, buf, 4);
		catc_पढ़ो_mem(catc, 0x7a80, buf, 4);
	  
		चयन (*buf) अणु
		हाल 0x12345678:
			catc_set_reg(catc, TxBufCount, 8);
			catc_set_reg(catc, RxBufCount, 32);
			dev_dbg(dev, "64k Memory\n");
			अवरोध;
		शेष:
			dev_warn(&पूर्णांकf->dev,
				 "Couldn't detect memory size, assuming 32k\n");
			fallthrough;
		हाल 0x87654321:
			catc_set_reg(catc, TxBufCount, 4);
			catc_set_reg(catc, RxBufCount, 16);
			dev_dbg(dev, "32k Memory\n");
			अवरोध;
		पूर्ण

		kमुक्त(buf);
	  
		dev_dbg(dev, "Getting MAC from SEEROM.\n");
	  
		catc_get_mac(catc, netdev->dev_addr);
		
		dev_dbg(dev, "Setting MAC into registers.\n");
	  
		क्रम (i = 0; i < 6; i++)
			catc_set_reg(catc, StationAddr0 - i, netdev->dev_addr[i]);
		
		dev_dbg(dev, "Filling the multicast list.\n");
	  
		eth_broadcast_addr(broadcast);
		catc_multicast(broadcast, catc->multicast);
		catc_multicast(netdev->dev_addr, catc->multicast);
		catc_ग_लिखो_mem(catc, 0xfa80, catc->multicast, 64);
		
		dev_dbg(dev, "Clearing error counters.\n");
		
		क्रम (i = 0; i < 8; i++)
			catc_set_reg(catc, EthStats + i, 0);
		catc->last_stats = jअगरfies;
		
		dev_dbg(dev, "Enabling.\n");
		
		catc_set_reg(catc, MaxBurst, RX_MAX_BURST);
		catc_set_reg(catc, OpModes, OpTxMerge | OpRxMerge | OpLenInclude | Op3MemWaits);
		catc_set_reg(catc, LEDCtrl, LEDLink);
		catc_set_reg(catc, RxUnit, RxEnable | RxPolarity | RxMultiCast);
	पूर्ण अन्यथा अणु
		dev_dbg(dev, "Performing reset\n");
		catc_reset(catc);
		catc_get_mac(catc, netdev->dev_addr);
		
		dev_dbg(dev, "Setting RX Mode\n");
		catc->rxmode[0] = RxEnable | RxPolarity | RxMultiCast;
		catc->rxmode[1] = 0;
		f5u011_rxmode(catc, catc->rxmode);
	पूर्ण
	dev_dbg(dev, "Init done.\n");
	prपूर्णांकk(KERN_INFO "%s: %s USB Ethernet at usb-%s-%s, %pM.\n",
	       netdev->name, (catc->is_f5u011) ? "Belkin F5U011" : "CATC EL1210A NetMate",
	       usbdev->bus->bus_name, usbdev->devpath, netdev->dev_addr);
	usb_set_पूर्णांकfdata(पूर्णांकf, catc);

	SET_NETDEV_DEV(netdev, &पूर्णांकf->dev);
	ret = रेजिस्टर_netdev(netdev);
	अगर (ret)
		जाओ fail_clear_पूर्णांकfdata;

	वापस 0;

fail_clear_पूर्णांकfdata:
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
fail_मुक्त:
	usb_मुक्त_urb(catc->ctrl_urb);
	usb_मुक्त_urb(catc->tx_urb);
	usb_मुक्त_urb(catc->rx_urb);
	usb_मुक्त_urb(catc->irq_urb);
	मुक्त_netdev(netdev);
	वापस ret;
पूर्ण

अटल व्योम catc_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा catc *catc = usb_get_पूर्णांकfdata(पूर्णांकf);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	अगर (catc) अणु
		unरेजिस्टर_netdev(catc->netdev);
		usb_मुक्त_urb(catc->ctrl_urb);
		usb_मुक्त_urb(catc->tx_urb);
		usb_मुक्त_urb(catc->rx_urb);
		usb_मुक्त_urb(catc->irq_urb);
		मुक्त_netdev(catc->netdev);
	पूर्ण
पूर्ण

/*
 * Module functions and tables.
 */

अटल स्थिर काष्ठा usb_device_id catc_id_table[] = अणु
	अणु USB_DEVICE(0x0423, 0xa) पूर्ण,	/* CATC Neपंचांगate, Belkin F5U011 */
	अणु USB_DEVICE(0x0423, 0xc) पूर्ण,	/* CATC Neपंचांगate II, Belkin F5U111 */
	अणु USB_DEVICE(0x08d1, 0x1) पूर्ण,	/* smartBridges smartNIC */
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, catc_id_table);

अटल काष्ठा usb_driver catc_driver = अणु
	.name =		driver_name,
	.probe =	catc_probe,
	.disconnect =	catc_disconnect,
	.id_table =	catc_id_table,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(catc_driver);
