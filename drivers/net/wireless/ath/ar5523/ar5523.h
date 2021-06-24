<शैली गुरु>
/*
 * Copyright (c) 2006 Damien Bergamini <damien.bergamini@मुक्त.fr>
 * Copyright (c) 2006 Sam Leffler, Errno Consulting
 * Copyright (c) 2007 Christoph Hellwig <hch@lst.de>
 * Copyright (c) 2008-2009 Weongyo Jeong <weongyo@मुक्तbsd.org>
 * Copyright (c) 2012 Pontus Fuchs <pontus.fuchs@gmail.com>
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
 */

#घोषणा AR5523_FLAG_PRE_FIRMWARE	(1 << 0)
#घोषणा AR5523_FLAG_ABG			(1 << 1)

#घोषणा AR5523_FIRMWARE_खाता	"ar5523.bin"

#घोषणा AR5523_CMD_TX_PIPE	0x01
#घोषणा	AR5523_DATA_TX_PIPE	0x02
#घोषणा	AR5523_CMD_RX_PIPE	0x81
#घोषणा	AR5523_DATA_RX_PIPE	0x82

#घोषणा ar5523_cmd_tx_pipe(dev) \
	usb_sndbulkpipe((dev), AR5523_CMD_TX_PIPE)
#घोषणा ar5523_data_tx_pipe(dev) \
	usb_sndbulkpipe((dev), AR5523_DATA_TX_PIPE)
#घोषणा ar5523_cmd_rx_pipe(dev) \
	usb_rcvbulkpipe((dev), AR5523_CMD_RX_PIPE)
#घोषणा ar5523_data_rx_pipe(dev) \
	usb_rcvbulkpipe((dev), AR5523_DATA_RX_PIPE)

#घोषणा	AR5523_DATA_TIMEOUT	10000
#घोषणा	AR5523_CMD_TIMEOUT	1000

#घोषणा AR5523_TX_DATA_COUNT		8
#घोषणा AR5523_TX_DATA_RESTART_COUNT	2
#घोषणा AR5523_RX_DATA_COUNT		16
#घोषणा AR5523_RX_DATA_REFILL_COUNT	8

#घोषणा AR5523_CMD_ID	1
#घोषणा AR5523_DATA_ID	2

#घोषणा AR5523_TX_WD_TIMEOUT	(HZ * 2)
#घोषणा AR5523_FLUSH_TIMEOUT	(HZ * 3)

क्रमागत AR5523_flags अणु
	AR5523_HW_UP,
	AR5523_USB_DISCONNECTED,
	AR5523_CONNECTED
पूर्ण;

काष्ठा ar5523_tx_cmd अणु
	काष्ठा ar5523		*ar;
	काष्ठा urb		*urb_tx;
	व्योम			*buf_tx;
	व्योम			*odata;
	पूर्णांक			olen;
	पूर्णांक			flags;
	पूर्णांक			res;
	काष्ठा completion	करोne;
पूर्ण;

/* This काष्ठा is placed in tx_info->driver_data. It must not be larger
 *  than IEEE80211_TX_INFO_DRIVER_DATA_SIZE.
 */
काष्ठा ar5523_tx_data अणु
	काष्ठा list_head	list;
	काष्ठा ar5523		*ar;
	काष्ठा urb		*urb;
पूर्ण;

काष्ठा ar5523_rx_data अणु
	काष्ठा	list_head	list;
	काष्ठा ar5523		*ar;
	काष्ठा urb		*urb;
	काष्ठा sk_buff		*skb;
पूर्ण;

काष्ठा ar5523 अणु
	काष्ठा usb_device	*dev;
	काष्ठा ieee80211_hw	*hw;

	अचिन्हित दीर्घ		flags;
	काष्ठा mutex		mutex;
	काष्ठा workqueue_काष्ठा *wq;

	काष्ठा ar5523_tx_cmd	tx_cmd;

	काष्ठा delayed_work	stat_work;

	काष्ठा समयr_list	tx_wd_समयr;
	काष्ठा work_काष्ठा	tx_wd_work;
	काष्ठा work_काष्ठा	tx_work;
	काष्ठा list_head	tx_queue_pending;
	काष्ठा list_head	tx_queue_submitted;
	spinlock_t		tx_data_list_lock;
	रुको_queue_head_t	tx_flush_रुकोq;

	/* Queued + Submitted TX frames */
	atomic_t		tx_nr_total;

	/* Submitted TX frames */
	atomic_t		tx_nr_pending;

	व्योम			*rx_cmd_buf;
	काष्ठा urb		*rx_cmd_urb;

	काष्ठा ar5523_rx_data	rx_data[AR5523_RX_DATA_COUNT];
	spinlock_t		rx_data_list_lock;
	काष्ठा list_head	rx_data_मुक्त;
	काष्ठा list_head	rx_data_used;
	atomic_t		rx_data_मुक्त_cnt;

	काष्ठा work_काष्ठा	rx_refill_work;

	अचिन्हित पूर्णांक		rxbufsz;
	u8			serial[16];

	काष्ठा ieee80211_channel channels[14];
	काष्ठा ieee80211_rate	rates[12];
	काष्ठा ieee80211_supported_band band;
	काष्ठा ieee80211_vअगर	*vअगर;
पूर्ण;

/* flags क्रम sending firmware commands */
#घोषणा AR5523_CMD_FLAG_READ	(1 << 1)
#घोषणा AR5523_CMD_FLAG_MAGIC	(1 << 2)

#घोषणा ar5523_dbg(ar, क्रमmat, arg...) \
	dev_dbg(&(ar)->dev->dev, क्रमmat, ## arg)

/* On USB hot-unplug there can be a lot of URBs in flight and they'll all
 * fail. Instead of dealing with them in every possible place just surpress
 * any messages on USB disconnect.
 */
#घोषणा ar5523_err(ar, क्रमmat, arg...) \
करो अणु \
	अगर (!test_bit(AR5523_USB_DISCONNECTED, &ar->flags)) अणु \
		dev_err(&(ar)->dev->dev, क्रमmat, ## arg); \
	पूर्ण \
पूर्ण जबतक (0)
#घोषणा ar5523_info(ar, क्रमmat, arg...)	\
	dev_info(&(ar)->dev->dev, क्रमmat, ## arg)
