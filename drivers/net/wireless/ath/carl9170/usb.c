<शैली गुरु>
/*
 * Atheros CARL9170 driver
 *
 * USB - frontend
 *
 * Copyright 2008, Johannes Berg <johannes@sipsolutions.net>
 * Copyright 2009, 2010, Christian Lamparter <chunkeey@googlemail.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; see the file COPYING.  If not, see
 * http://www.gnu.org/licenses/.
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *    Copyright (c) 2007-2008 Atheros Communications, Inc.
 *
 *    Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <linux/firmware.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/device.h>
#समावेश <net/mac80211.h>
#समावेश "carl9170.h"
#समावेश "cmd.h"
#समावेश "hw.h"
#समावेश "fwcmd.h"

MODULE_AUTHOR("Johannes Berg <johannes@sipsolutions.net>");
MODULE_AUTHOR("Christian Lamparter <chunkeey@googlemail.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Atheros AR9170 802.11n USB wireless");
MODULE_FIRMWARE(CARL9170FW_NAME);
MODULE_ALIAS("ar9170usb");
MODULE_ALIAS("arusb_lnx");

/*
 * Note:
 *
 * Always update our wiki's device list (located at:
 * https://wireless.wiki.kernel.org/en/users/Drivers/ar9170/devices ),
 * whenever you add a new device.
 */
अटल स्थिर काष्ठा usb_device_id carl9170_usb_ids[] = अणु
	/* Atheros 9170 */
	अणु USB_DEVICE(0x0cf3, 0x9170) पूर्ण,
	/* Atheros TG121N */
	अणु USB_DEVICE(0x0cf3, 0x1001) पूर्ण,
	/* TP-Link TL-WN821N v2 */
	अणु USB_DEVICE(0x0cf3, 0x1002), .driver_info = CARL9170_WPS_BUTTON |
		 CARL9170_ONE_LED पूर्ण,
	/* 3Com Dual Band 802.11n USB Adapter */
	अणु USB_DEVICE(0x0cf3, 0x1010) पूर्ण,
	/* H3C Dual Band 802.11n USB Adapter */
	अणु USB_DEVICE(0x0cf3, 0x1011) पूर्ण,
	/* Cace Airpcap NX */
	अणु USB_DEVICE(0xcace, 0x0300) पूर्ण,
	/* D-Link DWA 160 A1 */
	अणु USB_DEVICE(0x07d1, 0x3c10) पूर्ण,
	/* D-Link DWA 160 A2 */
	अणु USB_DEVICE(0x07d1, 0x3a09) पूर्ण,
	/* D-Link DWA 130 D */
	अणु USB_DEVICE(0x07d1, 0x3a0f) पूर्ण,
	/* Netgear WNA1000 */
	अणु USB_DEVICE(0x0846, 0x9040) पूर्ण,
	/* Netgear WNDA3100 (v1) */
	अणु USB_DEVICE(0x0846, 0x9010) पूर्ण,
	/* Netgear WN111 v2 */
	अणु USB_DEVICE(0x0846, 0x9001), .driver_info = CARL9170_ONE_LED पूर्ण,
	/* Zydas ZD1221 */
	अणु USB_DEVICE(0x0ace, 0x1221) पूर्ण,
	/* Proxim ORiNOCO 802.11n USB */
	अणु USB_DEVICE(0x1435, 0x0804) पूर्ण,
	/* WNC Generic 11n USB Dongle */
	अणु USB_DEVICE(0x1435, 0x0326) पूर्ण,
	/* ZyXEL NWD271N */
	अणु USB_DEVICE(0x0586, 0x3417) पूर्ण,
	/* Z-Com UB81 BG */
	अणु USB_DEVICE(0x0cde, 0x0023) पूर्ण,
	/* Z-Com UB82 ABG */
	अणु USB_DEVICE(0x0cde, 0x0026) पूर्ण,
	/* Sphairon Homelink 1202 */
	अणु USB_DEVICE(0x0cde, 0x0027) पूर्ण,
	/* Arcadyan WN7512 */
	अणु USB_DEVICE(0x083a, 0xf522) पूर्ण,
	/* Planex GWUS300 */
	अणु USB_DEVICE(0x2019, 0x5304) पूर्ण,
	/* IO-Data WNGDNUS2 */
	अणु USB_DEVICE(0x04bb, 0x093f) पूर्ण,
	/* NEC WL300NU-G */
	अणु USB_DEVICE(0x0409, 0x0249) पूर्ण,
	/* NEC WL300NU-AG */
	अणु USB_DEVICE(0x0409, 0x02b4) पूर्ण,
	/* AVM FRITZ!WLAN USB Stick N */
	अणु USB_DEVICE(0x057c, 0x8401) पूर्ण,
	/* AVM FRITZ!WLAN USB Stick N 2.4 */
	अणु USB_DEVICE(0x057c, 0x8402) पूर्ण,
	/* Qwest/Actiontec 802AIN Wireless N USB Network Adapter */
	अणु USB_DEVICE(0x1668, 0x1200) पूर्ण,
	/* Airlive X.USB a/b/g/n */
	अणु USB_DEVICE(0x1b75, 0x9170) पूर्ण,

	/* terminate */
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, carl9170_usb_ids);

अटल काष्ठा usb_driver carl9170_driver;

अटल व्योम carl9170_usb_submit_data_urb(काष्ठा ar9170 *ar)
अणु
	काष्ठा urb *urb;
	पूर्णांक err;

	अगर (atomic_inc_वापस(&ar->tx_anch_urbs) > AR9170_NUM_TX_URBS)
		जाओ err_acc;

	urb = usb_get_from_anchor(&ar->tx_रुको);
	अगर (!urb)
		जाओ err_acc;

	usb_anchor_urb(urb, &ar->tx_anch);

	err = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (unlikely(err)) अणु
		अगर (net_ratelimit()) अणु
			dev_err(&ar->udev->dev, "tx submit failed (%d)\n",
				urb->status);
		पूर्ण

		usb_unanchor_urb(urb);
		usb_anchor_urb(urb, &ar->tx_err);
	पूर्ण

	usb_मुक्त_urb(urb);

	अगर (likely(err == 0))
		वापस;

err_acc:
	atomic_dec(&ar->tx_anch_urbs);
पूर्ण

अटल व्योम carl9170_usb_tx_data_complete(काष्ठा urb *urb)
अणु
	काष्ठा ar9170 *ar = usb_get_पूर्णांकfdata(usb_अगरnum_to_अगर(urb->dev, 0));

	अगर (WARN_ON_ONCE(!ar)) अणु
		dev_kमुक्त_skb_irq(urb->context);
		वापस;
	पूर्ण

	atomic_dec(&ar->tx_anch_urbs);

	चयन (urb->status) अणु
	/* everything is fine */
	हाल 0:
		carl9170_tx_callback(ar, (व्योम *)urb->context);
		अवरोध;

	/* disconnect */
	हाल -ENOENT:
	हाल -ECONNRESET:
	हाल -ENODEV:
	हाल -ESHUTDOWN:
		/*
		 * Defer the frame clean-up to the tasklet worker.
		 * This is necessary, because carl9170_tx_drop
		 * करोes not work in an irqsave context.
		 */
		usb_anchor_urb(urb, &ar->tx_err);
		वापस;

	/* a अक्रमom transmission error has occurred? */
	शेष:
		अगर (net_ratelimit()) अणु
			dev_err(&ar->udev->dev, "tx failed (%d)\n",
				urb->status);
		पूर्ण

		usb_anchor_urb(urb, &ar->tx_err);
		अवरोध;
	पूर्ण

	अगर (likely(IS_STARTED(ar)))
		carl9170_usb_submit_data_urb(ar);
पूर्ण

अटल पूर्णांक carl9170_usb_submit_cmd_urb(काष्ठा ar9170 *ar)
अणु
	काष्ठा urb *urb;
	पूर्णांक err;

	अगर (atomic_inc_वापस(&ar->tx_cmd_urbs) != 1) अणु
		atomic_dec(&ar->tx_cmd_urbs);
		वापस 0;
	पूर्ण

	urb = usb_get_from_anchor(&ar->tx_cmd);
	अगर (!urb) अणु
		atomic_dec(&ar->tx_cmd_urbs);
		वापस 0;
	पूर्ण

	usb_anchor_urb(urb, &ar->tx_anch);
	err = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (unlikely(err)) अणु
		usb_unanchor_urb(urb);
		atomic_dec(&ar->tx_cmd_urbs);
	पूर्ण
	usb_मुक्त_urb(urb);

	वापस err;
पूर्ण

अटल व्योम carl9170_usb_cmd_complete(काष्ठा urb *urb)
अणु
	काष्ठा ar9170 *ar = urb->context;
	पूर्णांक err = 0;

	अगर (WARN_ON_ONCE(!ar))
		वापस;

	atomic_dec(&ar->tx_cmd_urbs);

	चयन (urb->status) अणु
	/* everything is fine */
	हाल 0:
		अवरोध;

	/* disconnect */
	हाल -ENOENT:
	हाल -ECONNRESET:
	हाल -ENODEV:
	हाल -ESHUTDOWN:
		वापस;

	शेष:
		err = urb->status;
		अवरोध;
	पूर्ण

	अगर (!IS_INITIALIZED(ar))
		वापस;

	अगर (err)
		dev_err(&ar->udev->dev, "submit cmd cb failed (%d).\n", err);

	err = carl9170_usb_submit_cmd_urb(ar);
	अगर (err)
		dev_err(&ar->udev->dev, "submit cmd failed (%d).\n", err);
पूर्ण

अटल व्योम carl9170_usb_rx_irq_complete(काष्ठा urb *urb)
अणु
	काष्ठा ar9170 *ar = urb->context;

	अगर (WARN_ON_ONCE(!ar))
		वापस;

	चयन (urb->status) अणु
	/* everything is fine */
	हाल 0:
		अवरोध;

	/* disconnect */
	हाल -ENOENT:
	हाल -ECONNRESET:
	हाल -ENODEV:
	हाल -ESHUTDOWN:
		वापस;

	शेष:
		जाओ resubmit;
	पूर्ण

	/*
	 * While the carl9170 firmware करोes not use this EP, the
	 * firmware loader in the EEPROM unक्रमtunately करोes.
	 * Thereक्रमe we need to be पढ़ोy to handle out-of-band
	 * responses and traps in हाल the firmware crashed and
	 * the loader took over again.
	 */
	carl9170_handle_command_response(ar, urb->transfer_buffer,
					 urb->actual_length);

resubmit:
	usb_anchor_urb(urb, &ar->rx_anch);
	अगर (unlikely(usb_submit_urb(urb, GFP_ATOMIC)))
		usb_unanchor_urb(urb);
पूर्ण

अटल पूर्णांक carl9170_usb_submit_rx_urb(काष्ठा ar9170 *ar, gfp_t gfp)
अणु
	काष्ठा urb *urb;
	पूर्णांक err = 0, runs = 0;

	जबतक ((atomic_पढ़ो(&ar->rx_anch_urbs) < AR9170_NUM_RX_URBS) &&
		(runs++ < AR9170_NUM_RX_URBS)) अणु
		err = -ENOSPC;
		urb = usb_get_from_anchor(&ar->rx_pool);
		अगर (urb) अणु
			usb_anchor_urb(urb, &ar->rx_anch);
			err = usb_submit_urb(urb, gfp);
			अगर (unlikely(err)) अणु
				usb_unanchor_urb(urb);
				usb_anchor_urb(urb, &ar->rx_pool);
			पूर्ण अन्यथा अणु
				atomic_dec(&ar->rx_pool_urbs);
				atomic_inc(&ar->rx_anch_urbs);
			पूर्ण
			usb_मुक्त_urb(urb);
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम carl9170_usb_rx_work(काष्ठा ar9170 *ar)
अणु
	काष्ठा urb *urb;
	पूर्णांक i;

	क्रम (i = 0; i < AR9170_NUM_RX_URBS_POOL; i++) अणु
		urb = usb_get_from_anchor(&ar->rx_work);
		अगर (!urb)
			अवरोध;

		atomic_dec(&ar->rx_work_urbs);
		अगर (IS_INITIALIZED(ar)) अणु
			carl9170_rx(ar, urb->transfer_buffer,
				    urb->actual_length);
		पूर्ण

		usb_anchor_urb(urb, &ar->rx_pool);
		atomic_inc(&ar->rx_pool_urbs);

		usb_मुक्त_urb(urb);

		carl9170_usb_submit_rx_urb(ar, GFP_ATOMIC);
	पूर्ण
पूर्ण

व्योम carl9170_usb_handle_tx_err(काष्ठा ar9170 *ar)
अणु
	काष्ठा urb *urb;

	जबतक ((urb = usb_get_from_anchor(&ar->tx_err))) अणु
		काष्ठा sk_buff *skb = (व्योम *)urb->context;

		carl9170_tx_drop(ar, skb);
		carl9170_tx_callback(ar, skb);
		usb_मुक्त_urb(urb);
	पूर्ण
पूर्ण

अटल व्योम carl9170_usb_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा ar9170 *ar = from_tasklet(ar, t, usb_tasklet);

	अगर (!IS_INITIALIZED(ar))
		वापस;

	carl9170_usb_rx_work(ar);

	/*
	 * Strictly speaking: The tx scheduler is not part of the USB प्रणाली.
	 * But the rx worker वापसs frames back to the mac80211-stack and
	 * this is the _perfect_ place to generate the next transmissions.
	 */
	अगर (IS_STARTED(ar))
		carl9170_tx_scheduler(ar);
पूर्ण

अटल व्योम carl9170_usb_rx_complete(काष्ठा urb *urb)
अणु
	काष्ठा ar9170 *ar = (काष्ठा ar9170 *)urb->context;
	पूर्णांक err;

	अगर (WARN_ON_ONCE(!ar))
		वापस;

	atomic_dec(&ar->rx_anch_urbs);

	चयन (urb->status) अणु
	हाल 0:
		/* rx path */
		usb_anchor_urb(urb, &ar->rx_work);
		atomic_inc(&ar->rx_work_urbs);
		अवरोध;

	हाल -ENOENT:
	हाल -ECONNRESET:
	हाल -ENODEV:
	हाल -ESHUTDOWN:
		/* handle disconnect events*/
		वापस;

	शेष:
		/* handle all other errors */
		usb_anchor_urb(urb, &ar->rx_pool);
		atomic_inc(&ar->rx_pool_urbs);
		अवरोध;
	पूर्ण

	err = carl9170_usb_submit_rx_urb(ar, GFP_ATOMIC);
	अगर (unlikely(err)) अणु
		/*
		 * usb_submit_rx_urb reported a problem.
		 * In हाल this is due to a rx buffer लघुage,
		 * elevate the tasklet worker priority to
		 * the highest available level.
		 */
		tasklet_hi_schedule(&ar->usb_tasklet);

		अगर (atomic_पढ़ो(&ar->rx_anch_urbs) == 0) अणु
			/*
			 * The प्रणाली is too slow to cope with
			 * the enormous workload. We have simply
			 * run out of active rx urbs and this
			 * unक्रमtunately leads to an unpredictable
			 * device.
			 */

			ieee80211_queue_work(ar->hw, &ar->ping_work);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Using anything less than _high_ priority असलolutely
		 * समाप्तs the rx perक्रमmance my UP-System...
		 */
		tasklet_hi_schedule(&ar->usb_tasklet);
	पूर्ण
पूर्ण

अटल काष्ठा urb *carl9170_usb_alloc_rx_urb(काष्ठा ar9170 *ar, gfp_t gfp)
अणु
	काष्ठा urb *urb;
	व्योम *buf;

	buf = kदो_स्मृति(ar->fw.rx_size, gfp);
	अगर (!buf)
		वापस शून्य;

	urb = usb_alloc_urb(0, gfp);
	अगर (!urb) अणु
		kमुक्त(buf);
		वापस शून्य;
	पूर्ण

	usb_fill_bulk_urb(urb, ar->udev, usb_rcvbulkpipe(ar->udev,
			  AR9170_USB_EP_RX), buf, ar->fw.rx_size,
			  carl9170_usb_rx_complete, ar);

	urb->transfer_flags |= URB_FREE_BUFFER;

	वापस urb;
पूर्ण

अटल पूर्णांक carl9170_usb_send_rx_irq_urb(काष्ठा ar9170 *ar)
अणु
	काष्ठा urb *urb = शून्य;
	व्योम *ibuf;
	पूर्णांक err = -ENOMEM;

	urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!urb)
		जाओ out;

	ibuf = kदो_स्मृति(AR9170_USB_EP_CTRL_MAX, GFP_KERNEL);
	अगर (!ibuf)
		जाओ out;

	usb_fill_पूर्णांक_urb(urb, ar->udev, usb_rcvपूर्णांकpipe(ar->udev,
			 AR9170_USB_EP_IRQ), ibuf, AR9170_USB_EP_CTRL_MAX,
			 carl9170_usb_rx_irq_complete, ar, 1);

	urb->transfer_flags |= URB_FREE_BUFFER;

	usb_anchor_urb(urb, &ar->rx_anch);
	err = usb_submit_urb(urb, GFP_KERNEL);
	अगर (err)
		usb_unanchor_urb(urb);

out:
	usb_मुक्त_urb(urb);
	वापस err;
पूर्ण

अटल पूर्णांक carl9170_usb_init_rx_bulk_urbs(काष्ठा ar9170 *ar)
अणु
	काष्ठा urb *urb;
	पूर्णांक i, err = -EINVAL;

	/*
	 * The driver actively मुख्यtains a second shaकरोw
	 * pool क्रम inactive, but fully-prepared rx urbs.
	 *
	 * The pool should help the driver to master huge
	 * workload spikes without running the risk of
	 * undersupplying the hardware or wasting समय by
	 * processing rx data (streams) inside the urb
	 * completion (hardirq context).
	 */
	क्रम (i = 0; i < AR9170_NUM_RX_URBS_POOL; i++) अणु
		urb = carl9170_usb_alloc_rx_urb(ar, GFP_KERNEL);
		अगर (!urb) अणु
			err = -ENOMEM;
			जाओ err_out;
		पूर्ण

		usb_anchor_urb(urb, &ar->rx_pool);
		atomic_inc(&ar->rx_pool_urbs);
		usb_मुक्त_urb(urb);
	पूर्ण

	err = carl9170_usb_submit_rx_urb(ar, GFP_KERNEL);
	अगर (err)
		जाओ err_out;

	/* the device now रुकोing क्रम the firmware. */
	carl9170_set_state_when(ar, CARL9170_STOPPED, CARL9170_IDLE);
	वापस 0;

err_out:

	usb_scuttle_anchored_urbs(&ar->rx_pool);
	usb_scuttle_anchored_urbs(&ar->rx_work);
	usb_समाप्त_anchored_urbs(&ar->rx_anch);
	वापस err;
पूर्ण

अटल पूर्णांक carl9170_usb_flush(काष्ठा ar9170 *ar)
अणु
	काष्ठा urb *urb;
	पूर्णांक ret, err = 0;

	जबतक ((urb = usb_get_from_anchor(&ar->tx_रुको))) अणु
		काष्ठा sk_buff *skb = (व्योम *)urb->context;
		carl9170_tx_drop(ar, skb);
		carl9170_tx_callback(ar, skb);
		usb_मुक्त_urb(urb);
	पूर्ण

	ret = usb_रुको_anchor_empty_समयout(&ar->tx_cmd, 1000);
	अगर (ret == 0)
		err = -ETIMEDOUT;

	/* lets रुको a जबतक until the tx - queues are dried out */
	ret = usb_रुको_anchor_empty_समयout(&ar->tx_anch, 1000);
	अगर (ret == 0)
		err = -ETIMEDOUT;

	usb_समाप्त_anchored_urbs(&ar->tx_anch);
	carl9170_usb_handle_tx_err(ar);

	वापस err;
पूर्ण

अटल व्योम carl9170_usb_cancel_urbs(काष्ठा ar9170 *ar)
अणु
	पूर्णांक err;

	carl9170_set_state(ar, CARL9170_UNKNOWN_STATE);

	err = carl9170_usb_flush(ar);
	अगर (err)
		dev_err(&ar->udev->dev, "stuck tx urbs!\n");

	usb_poison_anchored_urbs(&ar->tx_anch);
	carl9170_usb_handle_tx_err(ar);
	usb_poison_anchored_urbs(&ar->rx_anch);

	tasklet_समाप्त(&ar->usb_tasklet);

	usb_scuttle_anchored_urbs(&ar->rx_work);
	usb_scuttle_anchored_urbs(&ar->rx_pool);
	usb_scuttle_anchored_urbs(&ar->tx_cmd);
पूर्ण

पूर्णांक __carl9170_exec_cmd(काष्ठा ar9170 *ar, काष्ठा carl9170_cmd *cmd,
			स्थिर bool मुक्त_buf)
अणु
	काष्ठा urb *urb;
	पूर्णांक err = 0;

	अगर (!IS_INITIALIZED(ar)) अणु
		err = -EPERM;
		जाओ err_मुक्त;
	पूर्ण

	अगर (WARN_ON(cmd->hdr.len > CARL9170_MAX_CMD_LEN - 4)) अणु
		err = -EINVAL;
		जाओ err_मुक्त;
	पूर्ण

	urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!urb) अणु
		err = -ENOMEM;
		जाओ err_मुक्त;
	पूर्ण

	अगर (ar->usb_ep_cmd_is_bulk)
		usb_fill_bulk_urb(urb, ar->udev,
				  usb_sndbulkpipe(ar->udev, AR9170_USB_EP_CMD),
				  cmd, cmd->hdr.len + 4,
				  carl9170_usb_cmd_complete, ar);
	अन्यथा
		usb_fill_पूर्णांक_urb(urb, ar->udev,
				 usb_sndपूर्णांकpipe(ar->udev, AR9170_USB_EP_CMD),
				 cmd, cmd->hdr.len + 4,
				 carl9170_usb_cmd_complete, ar, 1);

	अगर (मुक्त_buf)
		urb->transfer_flags |= URB_FREE_BUFFER;

	usb_anchor_urb(urb, &ar->tx_cmd);
	usb_मुक्त_urb(urb);

	वापस carl9170_usb_submit_cmd_urb(ar);

err_मुक्त:
	अगर (मुक्त_buf)
		kमुक्त(cmd);

	वापस err;
पूर्ण

पूर्णांक carl9170_exec_cmd(काष्ठा ar9170 *ar, स्थिर क्रमागत carl9170_cmd_oids cmd,
	अचिन्हित पूर्णांक plen, व्योम *payload, अचिन्हित पूर्णांक outlen, व्योम *out)
अणु
	पूर्णांक err = -ENOMEM;
	अचिन्हित दीर्घ समय_left;

	अगर (!IS_ACCEPTING_CMD(ar))
		वापस -EIO;

	अगर (!(cmd & CARL9170_CMD_ASYNC_FLAG))
		might_sleep();

	ar->cmd.hdr.len = plen;
	ar->cmd.hdr.cmd = cmd;
	/* writing multiple regs fills this buffer alपढ़ोy */
	अगर (plen && payload != (u8 *)(ar->cmd.data))
		स_नकल(ar->cmd.data, payload, plen);

	spin_lock_bh(&ar->cmd_lock);
	ar->पढ़ोbuf = (u8 *)out;
	ar->पढ़ोlen = outlen;
	spin_unlock_bh(&ar->cmd_lock);

	reinit_completion(&ar->cmd_रुको);
	err = __carl9170_exec_cmd(ar, &ar->cmd, false);

	अगर (!(cmd & CARL9170_CMD_ASYNC_FLAG)) अणु
		समय_left = रुको_क्रम_completion_समयout(&ar->cmd_रुको, HZ);
		अगर (समय_left == 0) अणु
			err = -ETIMEDOUT;
			जाओ err_unbuf;
		पूर्ण

		अगर (ar->पढ़ोlen != outlen) अणु
			err = -EMSGSIZE;
			जाओ err_unbuf;
		पूर्ण
	पूर्ण

	वापस 0;

err_unbuf:
	/* Maybe the device was हटाओd in the moment we were रुकोing? */
	अगर (IS_STARTED(ar)) अणु
		dev_err(&ar->udev->dev, "no command feedback "
			"received (%d).\n", err);

		/* provide some maybe useful debug inक्रमmation */
		prपूर्णांक_hex_dump_bytes("carl9170 cmd: ", DUMP_PREFIX_NONE,
				     &ar->cmd, plen + 4);

		carl9170_restart(ar, CARL9170_RR_COMMAND_TIMEOUT);
	पूर्ण

	/* invalidate to aव्योम completing the next command prematurely */
	spin_lock_bh(&ar->cmd_lock);
	ar->पढ़ोbuf = शून्य;
	ar->पढ़ोlen = 0;
	spin_unlock_bh(&ar->cmd_lock);

	वापस err;
पूर्ण

व्योम carl9170_usb_tx(काष्ठा ar9170 *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा urb *urb;
	काष्ठा ar9170_stream *tx_stream;
	व्योम *data;
	अचिन्हित पूर्णांक len;

	अगर (!IS_STARTED(ar))
		जाओ err_drop;

	urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!urb)
		जाओ err_drop;

	अगर (ar->fw.tx_stream) अणु
		tx_stream = (व्योम *) (skb->data - माप(*tx_stream));

		len = skb->len + माप(*tx_stream);
		tx_stream->length = cpu_to_le16(len);
		tx_stream->tag = cpu_to_le16(AR9170_TX_STREAM_TAG);
		data = tx_stream;
	पूर्ण अन्यथा अणु
		data = skb->data;
		len = skb->len;
	पूर्ण

	usb_fill_bulk_urb(urb, ar->udev, usb_sndbulkpipe(ar->udev,
		AR9170_USB_EP_TX), data, len,
		carl9170_usb_tx_data_complete, skb);

	urb->transfer_flags |= URB_ZERO_PACKET;

	usb_anchor_urb(urb, &ar->tx_रुको);

	usb_मुक्त_urb(urb);

	carl9170_usb_submit_data_urb(ar);
	वापस;

err_drop:
	carl9170_tx_drop(ar, skb);
	carl9170_tx_callback(ar, skb);
पूर्ण

अटल व्योम carl9170_release_firmware(काष्ठा ar9170 *ar)
अणु
	अगर (ar->fw.fw) अणु
		release_firmware(ar->fw.fw);
		स_रखो(&ar->fw, 0, माप(ar->fw));
	पूर्ण
पूर्ण

व्योम carl9170_usb_stop(काष्ठा ar9170 *ar)
अणु
	पूर्णांक ret;

	carl9170_set_state_when(ar, CARL9170_IDLE, CARL9170_STOPPED);

	ret = carl9170_usb_flush(ar);
	अगर (ret)
		dev_err(&ar->udev->dev, "kill pending tx urbs.\n");

	usb_poison_anchored_urbs(&ar->tx_anch);
	carl9170_usb_handle_tx_err(ar);

	/* समाप्त any pending command */
	spin_lock_bh(&ar->cmd_lock);
	ar->पढ़ोlen = 0;
	spin_unlock_bh(&ar->cmd_lock);
	complete(&ar->cmd_रुको);

	/*
	 * Note:
	 * So far we मुक्तd all tx urbs, but we won't dare to touch any rx urbs.
	 * Else we would end up with a unresponsive device...
	 */
पूर्ण

पूर्णांक carl9170_usb_खोलो(काष्ठा ar9170 *ar)
अणु
	usb_unpoison_anchored_urbs(&ar->tx_anch);

	carl9170_set_state_when(ar, CARL9170_STOPPED, CARL9170_IDLE);
	वापस 0;
पूर्ण

अटल पूर्णांक carl9170_usb_load_firmware(काष्ठा ar9170 *ar)
अणु
	स्थिर u8 *data;
	u8 *buf;
	अचिन्हित पूर्णांक transfer;
	माप_प्रकार len;
	u32 addr;
	पूर्णांक err = 0;

	buf = kदो_स्मृति(4096, GFP_KERNEL);
	अगर (!buf) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण

	data = ar->fw.fw->data;
	len = ar->fw.fw->size;
	addr = ar->fw.address;

	/* this हटाओs the miniboot image */
	data += ar->fw.offset;
	len -= ar->fw.offset;

	जबतक (len) अणु
		transfer = min_t(अचिन्हित पूर्णांक, len, 4096u);
		स_नकल(buf, data, transfer);

		err = usb_control_msg(ar->udev, usb_sndctrlpipe(ar->udev, 0),
				      0x30 /* FW DL */, 0x40 | USB_सूची_OUT,
				      addr >> 8, 0, buf, transfer, 100);

		अगर (err < 0) अणु
			kमुक्त(buf);
			जाओ err_out;
		पूर्ण

		len -= transfer;
		data += transfer;
		addr += transfer;
	पूर्ण
	kमुक्त(buf);

	err = usb_control_msg(ar->udev, usb_sndctrlpipe(ar->udev, 0),
			      0x31 /* FW DL COMPLETE */,
			      0x40 | USB_सूची_OUT, 0, 0, शून्य, 0, 200);

	अगर (रुको_क्रम_completion_समयout(&ar->fw_boot_रुको, HZ) == 0) अणु
		err = -ETIMEDOUT;
		जाओ err_out;
	पूर्ण

	err = carl9170_echo_test(ar, 0x4a110123);
	अगर (err)
		जाओ err_out;

	/* now, start the command response counter */
	ar->cmd_seq = -1;

	वापस 0;

err_out:
	dev_err(&ar->udev->dev, "firmware upload failed (%d).\n", err);
	वापस err;
पूर्ण

पूर्णांक carl9170_usb_restart(काष्ठा ar9170 *ar)
अणु
	पूर्णांक err = 0;

	अगर (ar->पूर्णांकf->condition != USB_INTERFACE_BOUND)
		वापस 0;

	/*
	 * Disable the command response sequence counter check.
	 * We alपढ़ोy know that the device/firmware is in a bad state.
	 * So, no extra poपूर्णांकs are awarded to anyone who reminds the
	 * driver about that.
	 */
	ar->cmd_seq = -2;

	err = carl9170_reboot(ar);

	carl9170_usb_stop(ar);

	अगर (err)
		जाओ err_out;

	tasklet_schedule(&ar->usb_tasklet);

	/* The reboot procedure can take quite a जबतक to complete. */
	msleep(1100);

	err = carl9170_usb_खोलो(ar);
	अगर (err)
		जाओ err_out;

	err = carl9170_usb_load_firmware(ar);
	अगर (err)
		जाओ err_out;

	वापस 0;

err_out:
	carl9170_usb_cancel_urbs(ar);
	वापस err;
पूर्ण

व्योम carl9170_usb_reset(काष्ठा ar9170 *ar)
अणु
	/*
	 * This is the last resort to get the device going again
	 * without any *user replugging action*.
	 *
	 * But there is a catch: usb_reset really is like a physical
	 * *reconnect*. The mac80211 state will be lost in the process.
	 * Thereक्रमe a userspace application, which is monitoring
	 * the link must step in.
	 */
	carl9170_usb_cancel_urbs(ar);

	carl9170_usb_stop(ar);

	usb_queue_reset_device(ar->पूर्णांकf);
पूर्ण

अटल पूर्णांक carl9170_usb_init_device(काष्ठा ar9170 *ar)
अणु
	पूर्णांक err;

	/*
	 * The carl9170 firmware let's the driver know when it's
	 * पढ़ोy क्रम action. But we have to be prepared to gracefully
	 * handle all spurious [flushed] messages after each (re-)boot.
	 * Thus the command response counter reमुख्यs disabled until it
	 * can be safely synchronized.
	 */
	ar->cmd_seq = -2;

	err = carl9170_usb_send_rx_irq_urb(ar);
	अगर (err)
		जाओ err_out;

	err = carl9170_usb_init_rx_bulk_urbs(ar);
	अगर (err)
		जाओ err_unrx;

	err = carl9170_usb_खोलो(ar);
	अगर (err)
		जाओ err_unrx;

	mutex_lock(&ar->mutex);
	err = carl9170_usb_load_firmware(ar);
	mutex_unlock(&ar->mutex);
	अगर (err)
		जाओ err_stop;

	वापस 0;

err_stop:
	carl9170_usb_stop(ar);

err_unrx:
	carl9170_usb_cancel_urbs(ar);

err_out:
	वापस err;
पूर्ण

अटल व्योम carl9170_usb_firmware_failed(काष्ठा ar9170 *ar)
अणु
	/* Store a copies of the usb_पूर्णांकerface and usb_device poपूर्णांकer locally.
	 * This is because release_driver initiates carl9170_usb_disconnect,
	 * which in turn मुक्तs our driver context (ar).
	 */
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = ar->पूर्णांकf;
	काष्ठा usb_device *udev = ar->udev;

	complete(&ar->fw_load_रुको);
	/* at this poपूर्णांक 'ar' could be already freed. Don't use it anymore */
	ar = शून्य;

	/* unbind anything failed */
	usb_lock_device(udev);
	usb_driver_release_पूर्णांकerface(&carl9170_driver, पूर्णांकf);
	usb_unlock_device(udev);

	usb_put_पूर्णांकf(पूर्णांकf);
पूर्ण

अटल व्योम carl9170_usb_firmware_finish(काष्ठा ar9170 *ar)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = ar->पूर्णांकf;
	पूर्णांक err;

	err = carl9170_parse_firmware(ar);
	अगर (err)
		जाओ err_मुक्तfw;

	err = carl9170_usb_init_device(ar);
	अगर (err)
		जाओ err_मुक्तfw;

	err = carl9170_रेजिस्टर(ar);

	carl9170_usb_stop(ar);
	अगर (err)
		जाओ err_unrx;

	complete(&ar->fw_load_रुको);
	usb_put_पूर्णांकf(पूर्णांकf);
	वापस;

err_unrx:
	carl9170_usb_cancel_urbs(ar);

err_मुक्तfw:
	carl9170_release_firmware(ar);
	carl9170_usb_firmware_failed(ar);
पूर्ण

अटल व्योम carl9170_usb_firmware_step2(स्थिर काष्ठा firmware *fw,
					व्योम *context)
अणु
	काष्ठा ar9170 *ar = context;

	अगर (fw) अणु
		ar->fw.fw = fw;
		carl9170_usb_firmware_finish(ar);
		वापस;
	पूर्ण

	dev_err(&ar->udev->dev, "firmware not found.\n");
	carl9170_usb_firmware_failed(ar);
पूर्ण

अटल पूर्णांक carl9170_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			      स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_endpoपूर्णांक_descriptor *ep;
	काष्ठा ar9170 *ar;
	काष्ठा usb_device *udev;
	पूर्णांक i, err;

	err = usb_reset_device(पूर्णांकerface_to_usbdev(पूर्णांकf));
	अगर (err)
		वापस err;

	ar = carl9170_alloc(माप(*ar));
	अगर (IS_ERR(ar))
		वापस PTR_ERR(ar);

	udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	ar->udev = udev;
	ar->पूर्णांकf = पूर्णांकf;
	ar->features = id->driver_info;

	/* We need to remember the type of endpoपूर्णांक 4 because it dअगरfers
	 * between high- and full-speed configuration. The high-speed
	 * configuration specअगरies it as पूर्णांकerrupt and the full-speed
	 * configuration as bulk endpoपूर्णांक. This inक्रमmation is required
	 * later when sending urbs to that endpoपूर्णांक.
	 */
	क्रम (i = 0; i < पूर्णांकf->cur_altsetting->desc.bNumEndpoपूर्णांकs; ++i) अणु
		ep = &पूर्णांकf->cur_altsetting->endpoपूर्णांक[i].desc;

		अगर (usb_endpoपूर्णांक_num(ep) == AR9170_USB_EP_CMD &&
		    usb_endpoपूर्णांक_dir_out(ep) &&
		    usb_endpoपूर्णांक_type(ep) == USB_ENDPOINT_XFER_BULK)
			ar->usb_ep_cmd_is_bulk = true;
	पूर्ण

	usb_set_पूर्णांकfdata(पूर्णांकf, ar);
	SET_IEEE80211_DEV(ar->hw, &पूर्णांकf->dev);

	init_usb_anchor(&ar->rx_anch);
	init_usb_anchor(&ar->rx_pool);
	init_usb_anchor(&ar->rx_work);
	init_usb_anchor(&ar->tx_रुको);
	init_usb_anchor(&ar->tx_anch);
	init_usb_anchor(&ar->tx_cmd);
	init_usb_anchor(&ar->tx_err);
	init_completion(&ar->cmd_रुको);
	init_completion(&ar->fw_boot_रुको);
	init_completion(&ar->fw_load_रुको);
	tasklet_setup(&ar->usb_tasklet, carl9170_usb_tasklet);

	atomic_set(&ar->tx_cmd_urbs, 0);
	atomic_set(&ar->tx_anch_urbs, 0);
	atomic_set(&ar->rx_work_urbs, 0);
	atomic_set(&ar->rx_anch_urbs, 0);
	atomic_set(&ar->rx_pool_urbs, 0);

	usb_get_पूर्णांकf(पूर्णांकf);

	carl9170_set_state(ar, CARL9170_STOPPED);

	err = request_firmware_noरुको(THIS_MODULE, 1, CARL9170FW_NAME,
		&ar->udev->dev, GFP_KERNEL, ar, carl9170_usb_firmware_step2);
	अगर (err) अणु
		usb_put_पूर्णांकf(पूर्णांकf);
		carl9170_मुक्त(ar);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम carl9170_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा ar9170 *ar = usb_get_पूर्णांकfdata(पूर्णांकf);

	अगर (WARN_ON(!ar))
		वापस;

	रुको_क्रम_completion(&ar->fw_load_रुको);

	अगर (IS_INITIALIZED(ar)) अणु
		carl9170_reboot(ar);
		carl9170_usb_stop(ar);
	पूर्ण

	carl9170_usb_cancel_urbs(ar);
	carl9170_unरेजिस्टर(ar);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	carl9170_release_firmware(ar);
	carl9170_मुक्त(ar);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक carl9170_usb_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
				pm_message_t message)
अणु
	काष्ठा ar9170 *ar = usb_get_पूर्णांकfdata(पूर्णांकf);

	अगर (!ar)
		वापस -ENODEV;

	carl9170_usb_cancel_urbs(ar);

	वापस 0;
पूर्ण

अटल पूर्णांक carl9170_usb_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा ar9170 *ar = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक err;

	अगर (!ar)
		वापस -ENODEV;

	usb_unpoison_anchored_urbs(&ar->rx_anch);
	carl9170_set_state(ar, CARL9170_STOPPED);

	/*
	 * The USB करोcumentation demands that [क्रम suspend] all traffic
	 * to and from the device has to stop. This would be fine, but
	 * there's a catch: the device[usb phy] करोes not come back.
	 *
	 * Upon resume the firmware will "kill" itself and the
	 * boot-code sorts out the magic vooकरोo.
	 * Not very nice, but there's not much what could go wrong.
	 */
	msleep(1100);

	err = carl9170_usb_init_device(ar);
	अगर (err)
		जाओ err_unrx;

	वापस 0;

err_unrx:
	carl9170_usb_cancel_urbs(ar);

	वापस err;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल काष्ठा usb_driver carl9170_driver = अणु
	.name = KBUILD_MODNAME,
	.probe = carl9170_usb_probe,
	.disconnect = carl9170_usb_disconnect,
	.id_table = carl9170_usb_ids,
	.soft_unbind = 1,
#अगर_घोषित CONFIG_PM
	.suspend = carl9170_usb_suspend,
	.resume = carl9170_usb_resume,
	.reset_resume = carl9170_usb_resume,
#पूर्ण_अगर /* CONFIG_PM */
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(carl9170_driver);
