<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Copyright (C) 2010 Willow Garage <http://www.willowgarage.com>
	Copyright (C) 2009 - 2010 Ivo van Doorn <IvDoorn@gmail.com>
	Copyright (C) 2009 Mattias Nissler <mattias.nissler@gmx.de>
	Copyright (C) 2009 Felix Fietkau <nbd@खोलोwrt.org>
	Copyright (C) 2009 Xose Vazquez Perez <xose.vazquez@gmail.com>
	Copyright (C) 2009 Axel Kollhofer <rain_maker@root-क्रमum.org>
	<http://rt2x00.serialmonkey.com>

 */

/*
	Module: rt2800usb
	Abstract: rt2800usb device specअगरic routines.
	Supported chipsets: RT2800U.
 */

#समावेश <linux/delay.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>

#समावेश "rt2x00.h"
#समावेश "rt2x00usb.h"
#समावेश "rt2800lib.h"
#समावेश "rt2800.h"
#समावेश "rt2800usb.h"

/*
 * Allow hardware encryption to be disabled.
 */
अटल bool modparam_nohwcrypt;
module_param_named(nohwcrypt, modparam_nohwcrypt, bool, 0444);
MODULE_PARM_DESC(nohwcrypt, "Disable hardware encryption.");

अटल bool rt2800usb_hwcrypt_disabled(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	वापस modparam_nohwcrypt;
पूर्ण

/*
 * Queue handlers.
 */
अटल व्योम rt2800usb_start_queue(काष्ठा data_queue *queue)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = queue->rt2x00dev;
	u32 reg;

	चयन (queue->qid) अणु
	हाल QID_RX:
		reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, MAC_SYS_CTRL);
		rt2x00_set_field32(&reg, MAC_SYS_CTRL_ENABLE_RX, 1);
		rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_SYS_CTRL, reg);
		अवरोध;
	हाल QID_BEACON:
		reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, BCN_TIME_CFG);
		rt2x00_set_field32(&reg, BCN_TIME_CFG_TSF_TICKING, 1);
		rt2x00_set_field32(&reg, BCN_TIME_CFG_TBTT_ENABLE, 1);
		rt2x00_set_field32(&reg, BCN_TIME_CFG_BEACON_GEN, 1);
		rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, BCN_TIME_CFG, reg);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम rt2800usb_stop_queue(काष्ठा data_queue *queue)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = queue->rt2x00dev;
	u32 reg;

	चयन (queue->qid) अणु
	हाल QID_RX:
		reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, MAC_SYS_CTRL);
		rt2x00_set_field32(&reg, MAC_SYS_CTRL_ENABLE_RX, 0);
		rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_SYS_CTRL, reg);
		अवरोध;
	हाल QID_BEACON:
		reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, BCN_TIME_CFG);
		rt2x00_set_field32(&reg, BCN_TIME_CFG_TSF_TICKING, 0);
		rt2x00_set_field32(&reg, BCN_TIME_CFG_TBTT_ENABLE, 0);
		rt2x00_set_field32(&reg, BCN_TIME_CFG_BEACON_GEN, 0);
		rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, BCN_TIME_CFG, reg);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

#घोषणा TXSTATUS_READ_INTERVAL 1000000

अटल bool rt2800usb_tx_sta_fअगरo_पढ़ो_completed(काष्ठा rt2x00_dev *rt2x00dev,
						 पूर्णांक urb_status, u32 tx_status)
अणु
	bool valid;

	अगर (urb_status) अणु
		rt2x00_warn(rt2x00dev, "TX status read failed %d\n",
			    urb_status);

		जाओ stop_पढ़ोing;
	पूर्ण

	valid = rt2x00_get_field32(tx_status, TX_STA_FIFO_VALID);
	अगर (valid) अणु
		अगर (!kfअगरo_put(&rt2x00dev->txstatus_fअगरo, tx_status))
			rt2x00_warn(rt2x00dev, "TX status FIFO overrun\n");

		queue_work(rt2x00dev->workqueue, &rt2x00dev->txकरोne_work);

		/* Reschedule urb to पढ़ो TX status again instantly */
		वापस true;
	पूर्ण

	/* Check अगर there is any entry that समयकरोut रुकोing on TX status */
	अगर (rt2800_txstatus_समयout(rt2x00dev))
		queue_work(rt2x00dev->workqueue, &rt2x00dev->txकरोne_work);

	अगर (rt2800_txstatus_pending(rt2x00dev)) अणु
		/* Read रेजिस्टर after 1 ms */
		hrसमयr_start(&rt2x00dev->txstatus_समयr,
			      TXSTATUS_READ_INTERVAL,
			      HRTIMER_MODE_REL);
		वापस false;
	पूर्ण

stop_पढ़ोing:
	clear_bit(TX_STATUS_READING, &rt2x00dev->flags);
	/*
	 * There is small race winकरोw above, between txstatus pending check and
	 * clear_bit someone could करो rt2x00usb_पूर्णांकerrupt_txकरोne, so recheck
	 * here again अगर status पढ़ोing is needed.
	 */
	अगर (rt2800_txstatus_pending(rt2x00dev) &&
	    !test_and_set_bit(TX_STATUS_READING, &rt2x00dev->flags))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल व्योम rt2800usb_async_पढ़ो_tx_status(काष्ठा rt2x00_dev *rt2x00dev)
अणु

	अगर (test_and_set_bit(TX_STATUS_READING, &rt2x00dev->flags))
		वापस;

	/* Read TX_STA_FIFO रेजिस्टर after 2 ms */
	hrसमयr_start(&rt2x00dev->txstatus_समयr,
		      2 * TXSTATUS_READ_INTERVAL,
		      HRTIMER_MODE_REL);
पूर्ण

अटल व्योम rt2800usb_tx_dma_करोne(काष्ठा queue_entry *entry)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;

	rt2800usb_async_पढ़ो_tx_status(rt2x00dev);
पूर्ण

अटल क्रमागत hrसमयr_restart rt2800usb_tx_sta_fअगरo_समयout(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा rt2x00_dev *rt2x00dev =
	    container_of(समयr, काष्ठा rt2x00_dev, txstatus_समयr);

	rt2x00usb_रेजिस्टर_पढ़ो_async(rt2x00dev, TX_STA_FIFO,
				      rt2800usb_tx_sta_fअगरo_पढ़ो_completed);

	वापस HRTIMER_NORESTART;
पूर्ण

/*
 * Firmware functions
 */
अटल पूर्णांक rt2800usb_स्वतःrun_detect(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	__le32 *reg;
	u32 fw_mode;
	पूर्णांक ret;

	reg = kदो_स्मृति(माप(*reg), GFP_KERNEL);
	अगर (reg == शून्य)
		वापस -ENOMEM;
	/* cannot use rt2x00usb_रेजिस्टर_पढ़ो here as it uses dअगरferent
	 * mode (MULTI_READ vs. DEVICE_MODE) and करोes not pass the
	 * magic value USB_MODE_AUTORUN (0x11) to the device, thus the
	 * वापसed value would be invalid.
	 */
	ret = rt2x00usb_venकरोr_request(rt2x00dev, USB_DEVICE_MODE,
				       USB_VENDOR_REQUEST_IN, 0,
				       USB_MODE_AUTORUN, reg, माप(*reg),
				       REGISTER_TIMEOUT_FIRMWARE);
	fw_mode = le32_to_cpu(*reg);
	kमुक्त(reg);
	अगर (ret < 0)
		वापस ret;

	अगर ((fw_mode & 0x00000003) == 2)
		वापस 1;

	वापस 0;
पूर्ण

अटल अक्षर *rt2800usb_get_firmware_name(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	वापस FIRMWARE_RT2870;
पूर्ण

अटल पूर्णांक rt2800usb_ग_लिखो_firmware(काष्ठा rt2x00_dev *rt2x00dev,
				    स्थिर u8 *data, स्थिर माप_प्रकार len)
अणु
	पूर्णांक status;
	u32 offset;
	u32 length;
	पूर्णांक retval;

	/*
	 * Check which section of the firmware we need.
	 */
	अगर (rt2x00_rt(rt2x00dev, RT2860) ||
	    rt2x00_rt(rt2x00dev, RT2872) ||
	    rt2x00_rt(rt2x00dev, RT3070)) अणु
		offset = 0;
		length = 4096;
	पूर्ण अन्यथा अणु
		offset = 4096;
		length = 4096;
	पूर्ण

	/*
	 * Write firmware to device.
	 */
	retval = rt2800usb_स्वतःrun_detect(rt2x00dev);
	अगर (retval < 0)
		वापस retval;
	अगर (retval) अणु
		rt2x00_info(rt2x00dev,
			    "Firmware loading not required - NIC in AutoRun mode\n");
		__clear_bit(REQUIRE_FIRMWARE, &rt2x00dev->cap_flags);
	पूर्ण अन्यथा अणु
		rt2x00usb_रेजिस्टर_multiग_लिखो(rt2x00dev, FIRMWARE_IMAGE_BASE,
					      data + offset, length);
	पूर्ण

	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, H2M_MAILBOX_CID, ~0);
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, H2M_MAILBOX_STATUS, ~0);

	/*
	 * Send firmware request to device to load firmware,
	 * we need to specअगरy a दीर्घ समयout समय.
	 */
	status = rt2x00usb_venकरोr_request_sw(rt2x00dev, USB_DEVICE_MODE,
					     0, USB_MODE_FIRMWARE,
					     REGISTER_TIMEOUT_FIRMWARE);
	अगर (status < 0) अणु
		rt2x00_err(rt2x00dev, "Failed to write Firmware to device\n");
		वापस status;
	पूर्ण

	msleep(10);
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, H2M_MAILBOX_CSR, 0);

	वापस 0;
पूर्ण

/*
 * Device state चयन handlers.
 */
अटल पूर्णांक rt2800usb_init_रेजिस्टरs(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u32 reg;

	/*
	 * Wait until BBP and RF are पढ़ोy.
	 */
	अगर (rt2800_रुको_csr_पढ़ोy(rt2x00dev))
		वापस -EBUSY;

	reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, PBF_SYS_CTRL);
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, PBF_SYS_CTRL, reg & ~0x00002000);

	reg = 0;
	rt2x00_set_field32(&reg, MAC_SYS_CTRL_RESET_CSR, 1);
	rt2x00_set_field32(&reg, MAC_SYS_CTRL_RESET_BBP, 1);
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_SYS_CTRL, reg);

	rt2x00usb_venकरोr_request_sw(rt2x00dev, USB_DEVICE_MODE, 0,
				    USB_MODE_RESET, REGISTER_TIMEOUT);

	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_SYS_CTRL, 0x00000000);

	वापस 0;
पूर्ण

अटल पूर्णांक rt2800usb_enable_radio(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u32 reg = 0;

	अगर (unlikely(rt2800_रुको_wpdma_पढ़ोy(rt2x00dev)))
		वापस -EIO;

	rt2x00_set_field32(&reg, USB_DMA_CFG_PHY_CLEAR, 0);
	rt2x00_set_field32(&reg, USB_DMA_CFG_RX_BULK_AGG_EN, 0);
	rt2x00_set_field32(&reg, USB_DMA_CFG_RX_BULK_AGG_TIMEOUT, 128);
	/*
	 * Total room क्रम RX frames in kilobytes, PBF might still exceed
	 * this limit so reduce the number to prevent errors.
	 */
	rt2x00_set_field32(&reg, USB_DMA_CFG_RX_BULK_AGG_LIMIT,
			   ((rt2x00dev->rx->limit * DATA_FRAME_SIZE)
			    / 1024) - 3);
	rt2x00_set_field32(&reg, USB_DMA_CFG_RX_BULK_EN, 1);
	rt2x00_set_field32(&reg, USB_DMA_CFG_TX_BULK_EN, 1);
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, USB_DMA_CFG, reg);

	वापस rt2800_enable_radio(rt2x00dev);
पूर्ण

अटल व्योम rt2800usb_disable_radio(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	rt2800_disable_radio(rt2x00dev);
पूर्ण

अटल पूर्णांक rt2800usb_set_state(काष्ठा rt2x00_dev *rt2x00dev,
			       क्रमागत dev_state state)
अणु
	अगर (state == STATE_AWAKE)
		rt2800_mcu_request(rt2x00dev, MCU_WAKEUP, 0xff, 0, 2);
	अन्यथा
		rt2800_mcu_request(rt2x00dev, MCU_SLEEP, 0xff, 0xff, 2);

	वापस 0;
पूर्ण

अटल पूर्णांक rt2800usb_set_device_state(काष्ठा rt2x00_dev *rt2x00dev,
				      क्रमागत dev_state state)
अणु
	पूर्णांक retval = 0;

	चयन (state) अणु
	हाल STATE_RADIO_ON:
		/*
		 * Beक्रमe the radio can be enabled, the device first has
		 * to be woken up. After that it needs a bit of समय
		 * to be fully awake and then the radio can be enabled.
		 */
		rt2800usb_set_state(rt2x00dev, STATE_AWAKE);
		msleep(1);
		retval = rt2800usb_enable_radio(rt2x00dev);
		अवरोध;
	हाल STATE_RADIO_OFF:
		/*
		 * After the radio has been disabled, the device should
		 * be put to sleep क्रम घातersaving.
		 */
		rt2800usb_disable_radio(rt2x00dev);
		rt2800usb_set_state(rt2x00dev, STATE_SLEEP);
		अवरोध;
	हाल STATE_RADIO_IRQ_ON:
	हाल STATE_RADIO_IRQ_OFF:
		/* No support, but no error either */
		अवरोध;
	हाल STATE_DEEP_SLEEP:
	हाल STATE_SLEEP:
	हाल STATE_STANDBY:
	हाल STATE_AWAKE:
		retval = rt2800usb_set_state(rt2x00dev, state);
		अवरोध;
	शेष:
		retval = -ENOTSUPP;
		अवरोध;
	पूर्ण

	अगर (unlikely(retval))
		rt2x00_err(rt2x00dev, "Device failed to enter state %d (%d)\n",
			   state, retval);

	वापस retval;
पूर्ण

अटल अचिन्हित पूर्णांक rt2800usb_get_dma_करोne(काष्ठा data_queue *queue)
अणु
	काष्ठा queue_entry *entry;

	entry = rt2x00queue_get_entry(queue, Q_INDEX_DMA_DONE);
	वापस entry->entry_idx;
पूर्ण

/*
 * TX descriptor initialization
 */
अटल __le32 *rt2800usb_get_txwi(काष्ठा queue_entry *entry)
अणु
	अगर (entry->queue->qid == QID_BEACON)
		वापस (__le32 *) (entry->skb->data);
	अन्यथा
		वापस (__le32 *) (entry->skb->data + TXINFO_DESC_SIZE);
पूर्ण

अटल व्योम rt2800usb_ग_लिखो_tx_desc(काष्ठा queue_entry *entry,
				    काष्ठा txentry_desc *txdesc)
अणु
	काष्ठा skb_frame_desc *skbdesc = get_skb_frame_desc(entry->skb);
	__le32 *txi = (__le32 *) entry->skb->data;
	u32 word;

	/*
	 * Initialize TXINFO descriptor
	 */
	word = rt2x00_desc_पढ़ो(txi, 0);

	/*
	 * The size of TXINFO_W0_USB_DMA_TX_PKT_LEN is
	 * TXWI + 802.11 header + L2 pad + payload + pad,
	 * so need to decrease size of TXINFO.
	 */
	rt2x00_set_field32(&word, TXINFO_W0_USB_DMA_TX_PKT_LEN,
			   roundup(entry->skb->len, 4) - TXINFO_DESC_SIZE);
	rt2x00_set_field32(&word, TXINFO_W0_WIV,
			   !test_bit(ENTRY_TXD_ENCRYPT_IV, &txdesc->flags));
	rt2x00_set_field32(&word, TXINFO_W0_QSEL, 2);
	rt2x00_set_field32(&word, TXINFO_W0_SW_USE_LAST_ROUND, 0);
	rt2x00_set_field32(&word, TXINFO_W0_USB_DMA_NEXT_VALID, 0);
	rt2x00_set_field32(&word, TXINFO_W0_USB_DMA_TX_BURST,
			   test_bit(ENTRY_TXD_BURST, &txdesc->flags));
	rt2x00_desc_ग_लिखो(txi, 0, word);

	/*
	 * Register descriptor details in skb frame descriptor.
	 */
	skbdesc->flags |= SKBDESC_DESC_IN_SKB;
	skbdesc->desc = txi;
	skbdesc->desc_len = TXINFO_DESC_SIZE + entry->queue->winfo_size;
पूर्ण

/*
 * TX data initialization
 */
अटल पूर्णांक rt2800usb_get_tx_data_len(काष्ठा queue_entry *entry)
अणु
	/*
	 * pad(1~3 bytes) is needed after each 802.11 payload.
	 * USB end pad(4 bytes) is needed at each USB bulk out packet end.
	 * TX frame क्रमmat is :
	 * | TXINFO | TXWI | 802.11 header | L2 pad | payload | pad | USB end pad |
	 *                 |<------------- tx_pkt_len ------------->|
	 */

	वापस roundup(entry->skb->len, 4) + 4;
पूर्ण

/*
 * TX control handlers
 */
अटल व्योम rt2800usb_work_txकरोne(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt2x00_dev *rt2x00dev =
	    container_of(work, काष्ठा rt2x00_dev, txकरोne_work);

	जबतक (!kfअगरo_is_empty(&rt2x00dev->txstatus_fअगरo) ||
	       rt2800_txstatus_समयout(rt2x00dev)) अणु

		rt2800_txकरोne(rt2x00dev, अच_पूर्णांक_उच्च);

		rt2800_txकरोne_nostatus(rt2x00dev);

		/*
		 * The hw may delay sending the packet after DMA complete
		 * अगर the medium is busy, thus the TX_STA_FIFO entry is
		 * also delayed -> use a समयr to retrieve it.
		 */
		अगर (rt2800_txstatus_pending(rt2x00dev))
			rt2800usb_async_पढ़ो_tx_status(rt2x00dev);
	पूर्ण
पूर्ण

/*
 * RX control handlers
 */
अटल व्योम rt2800usb_fill_rxकरोne(काष्ठा queue_entry *entry,
				  काष्ठा rxकरोne_entry_desc *rxdesc)
अणु
	काष्ठा skb_frame_desc *skbdesc = get_skb_frame_desc(entry->skb);
	__le32 *rxi = (__le32 *)entry->skb->data;
	__le32 *rxd;
	u32 word;
	पूर्णांक rx_pkt_len;

	/*
	 * Copy descriptor to the skbdesc->desc buffer, making it safe from
	 * moving of frame data in rt2x00usb.
	 */
	स_नकल(skbdesc->desc, rxi, skbdesc->desc_len);

	/*
	 * RX frame क्रमmat is :
	 * | RXINFO | RXWI | header | L2 pad | payload | pad | RXD | USB pad |
	 *          |<------------ rx_pkt_len -------------->|
	 */
	word = rt2x00_desc_पढ़ो(rxi, 0);
	rx_pkt_len = rt2x00_get_field32(word, RXINFO_W0_USB_DMA_RX_PKT_LEN);

	/*
	 * Remove the RXINFO काष्ठाure from the sbk.
	 */
	skb_pull(entry->skb, RXINFO_DESC_SIZE);

	/*
	 * Check क्रम rx_pkt_len validity. Return अगर invalid, leaving
	 * rxdesc->size zeroed out by the upper level.
	 */
	अगर (unlikely(rx_pkt_len == 0 ||
			rx_pkt_len > entry->queue->data_size)) अणु
		rt2x00_err(entry->queue->rt2x00dev,
			   "Bad frame size %d, forcing to 0\n", rx_pkt_len);
		वापस;
	पूर्ण

	rxd = (__le32 *)(entry->skb->data + rx_pkt_len);

	/*
	 * It is now safe to पढ़ो the descriptor on all architectures.
	 */
	word = rt2x00_desc_पढ़ो(rxd, 0);

	अगर (rt2x00_get_field32(word, RXD_W0_CRC_ERROR))
		rxdesc->flags |= RX_FLAG_FAILED_FCS_CRC;

	rxdesc->cipher_status = rt2x00_get_field32(word, RXD_W0_CIPHER_ERROR);

	अगर (rt2x00_get_field32(word, RXD_W0_DECRYPTED)) अणु
		/*
		 * Hardware has stripped IV/EIV data from 802.11 frame during
		 * decryption. Unक्रमtunately the descriptor करोesn't contain
		 * any fields with the EIV/IV data either, so they can't
		 * be restored by rt2x00lib.
		 */
		rxdesc->flags |= RX_FLAG_IV_STRIPPED;

		/*
		 * The hardware has alपढ़ोy checked the Michael Mic and has
		 * stripped it from the frame. Signal this to mac80211.
		 */
		rxdesc->flags |= RX_FLAG_MMIC_STRIPPED;

		अगर (rxdesc->cipher_status == RX_CRYPTO_SUCCESS) अणु
			rxdesc->flags |= RX_FLAG_DECRYPTED;
		पूर्ण अन्यथा अगर (rxdesc->cipher_status == RX_CRYPTO_FAIL_MIC) अणु
			/*
			 * In order to check the Michael Mic, the packet must have
			 * been decrypted.  Mac80211 करोesnt check the MMIC failure
			 * flag to initiate MMIC countermeasures अगर the decoded flag
			 * has not been set.
			 */
			rxdesc->flags |= RX_FLAG_DECRYPTED;

			rxdesc->flags |= RX_FLAG_MMIC_ERROR;
		पूर्ण
	पूर्ण

	अगर (rt2x00_get_field32(word, RXD_W0_MY_BSS))
		rxdesc->dev_flags |= RXDONE_MY_BSS;

	अगर (rt2x00_get_field32(word, RXD_W0_L2PAD))
		rxdesc->dev_flags |= RXDONE_L2PAD;

	/*
	 * Remove RXD descriptor from end of buffer.
	 */
	skb_trim(entry->skb, rx_pkt_len);

	/*
	 * Process the RXWI काष्ठाure.
	 */
	rt2800_process_rxwi(entry, rxdesc);
पूर्ण

/*
 * Device probe functions.
 */
अटल पूर्णांक rt2800usb_efuse_detect(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	पूर्णांक retval;

	retval = rt2800usb_स्वतःrun_detect(rt2x00dev);
	अगर (retval < 0)
		वापस retval;
	अगर (retval)
		वापस 1;
	वापस rt2800_efuse_detect(rt2x00dev);
पूर्ण

अटल पूर्णांक rt2800usb_पढ़ो_eeprom(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	पूर्णांक retval;

	retval = rt2800usb_efuse_detect(rt2x00dev);
	अगर (retval < 0)
		वापस retval;
	अगर (retval)
		retval = rt2800_पढ़ो_eeprom_efuse(rt2x00dev);
	अन्यथा
		retval = rt2x00usb_eeprom_पढ़ो(rt2x00dev, rt2x00dev->eeprom,
					       EEPROM_SIZE);

	वापस retval;
पूर्ण

अटल पूर्णांक rt2800usb_probe_hw(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	पूर्णांक retval;

	retval = rt2800_probe_hw(rt2x00dev);
	अगर (retval)
		वापस retval;

	/*
	 * Set txstatus समयr function.
	 */
	rt2x00dev->txstatus_समयr.function = rt2800usb_tx_sta_fअगरo_समयout;

	/*
	 * Overग_लिखो TX करोne handler
	 */
	INIT_WORK(&rt2x00dev->txकरोne_work, rt2800usb_work_txकरोne);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ieee80211_ops rt2800usb_mac80211_ops = अणु
	.tx			= rt2x00mac_tx,
	.start			= rt2x00mac_start,
	.stop			= rt2x00mac_stop,
	.add_पूर्णांकerface		= rt2x00mac_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface	= rt2x00mac_हटाओ_पूर्णांकerface,
	.config			= rt2x00mac_config,
	.configure_filter	= rt2x00mac_configure_filter,
	.set_tim		= rt2x00mac_set_tim,
	.set_key		= rt2x00mac_set_key,
	.sw_scan_start		= rt2x00mac_sw_scan_start,
	.sw_scan_complete	= rt2x00mac_sw_scan_complete,
	.get_stats		= rt2x00mac_get_stats,
	.get_key_seq		= rt2800_get_key_seq,
	.set_rts_threshold	= rt2800_set_rts_threshold,
	.sta_add		= rt2800_sta_add,
	.sta_हटाओ		= rt2800_sta_हटाओ,
	.bss_info_changed	= rt2x00mac_bss_info_changed,
	.conf_tx		= rt2800_conf_tx,
	.get_tsf		= rt2800_get_tsf,
	.rfसमाप्त_poll		= rt2x00mac_rfसमाप्त_poll,
	.ampdu_action		= rt2800_ampdu_action,
	.flush			= rt2x00mac_flush,
	.get_survey		= rt2800_get_survey,
	.get_ringparam		= rt2x00mac_get_ringparam,
	.tx_frames_pending	= rt2x00mac_tx_frames_pending,
	.reconfig_complete	= rt2x00mac_reconfig_complete,
पूर्ण;

अटल स्थिर काष्ठा rt2800_ops rt2800usb_rt2800_ops = अणु
	.रेजिस्टर_पढ़ो		= rt2x00usb_रेजिस्टर_पढ़ो,
	.रेजिस्टर_पढ़ो_lock	= rt2x00usb_रेजिस्टर_पढ़ो_lock,
	.रेजिस्टर_ग_लिखो		= rt2x00usb_रेजिस्टर_ग_लिखो,
	.रेजिस्टर_ग_लिखो_lock	= rt2x00usb_रेजिस्टर_ग_लिखो_lock,
	.रेजिस्टर_multiपढ़ो	= rt2x00usb_रेजिस्टर_multiपढ़ो,
	.रेजिस्टर_multiग_लिखो	= rt2x00usb_रेजिस्टर_multiग_लिखो,
	.regbusy_पढ़ो		= rt2x00usb_regbusy_पढ़ो,
	.पढ़ो_eeprom		= rt2800usb_पढ़ो_eeprom,
	.hwcrypt_disabled	= rt2800usb_hwcrypt_disabled,
	.drv_ग_लिखो_firmware	= rt2800usb_ग_लिखो_firmware,
	.drv_init_रेजिस्टरs	= rt2800usb_init_रेजिस्टरs,
	.drv_get_txwi		= rt2800usb_get_txwi,
	.drv_get_dma_करोne	= rt2800usb_get_dma_करोne,
पूर्ण;

अटल स्थिर काष्ठा rt2x00lib_ops rt2800usb_rt2x00_ops = अणु
	.probe_hw		= rt2800usb_probe_hw,
	.get_firmware_name	= rt2800usb_get_firmware_name,
	.check_firmware		= rt2800_check_firmware,
	.load_firmware		= rt2800_load_firmware,
	.initialize		= rt2x00usb_initialize,
	.uninitialize		= rt2x00usb_uninitialize,
	.clear_entry		= rt2x00usb_clear_entry,
	.set_device_state	= rt2800usb_set_device_state,
	.rfसमाप्त_poll		= rt2800_rfसमाप्त_poll,
	.link_stats		= rt2800_link_stats,
	.reset_tuner		= rt2800_reset_tuner,
	.link_tuner		= rt2800_link_tuner,
	.gain_calibration	= rt2800_gain_calibration,
	.vco_calibration	= rt2800_vco_calibration,
	.watchकरोg		= rt2800_watchकरोg,
	.start_queue		= rt2800usb_start_queue,
	.kick_queue		= rt2x00usb_kick_queue,
	.stop_queue		= rt2800usb_stop_queue,
	.flush_queue		= rt2x00usb_flush_queue,
	.tx_dma_करोne		= rt2800usb_tx_dma_करोne,
	.ग_लिखो_tx_desc		= rt2800usb_ग_लिखो_tx_desc,
	.ग_लिखो_tx_data		= rt2800_ग_लिखो_tx_data,
	.ग_लिखो_beacon		= rt2800_ग_लिखो_beacon,
	.clear_beacon		= rt2800_clear_beacon,
	.get_tx_data_len	= rt2800usb_get_tx_data_len,
	.fill_rxकरोne		= rt2800usb_fill_rxकरोne,
	.config_shared_key	= rt2800_config_shared_key,
	.config_pairwise_key	= rt2800_config_pairwise_key,
	.config_filter		= rt2800_config_filter,
	.config_पूर्णांकf		= rt2800_config_पूर्णांकf,
	.config_erp		= rt2800_config_erp,
	.config_ant		= rt2800_config_ant,
	.config			= rt2800_config,
	.pre_reset_hw		= rt2800_pre_reset_hw,
पूर्ण;

अटल व्योम rt2800usb_queue_init(काष्ठा data_queue *queue)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = queue->rt2x00dev;
	अचिन्हित लघु txwi_size, rxwi_size;

	rt2800_get_txwi_rxwi_size(rt2x00dev, &txwi_size, &rxwi_size);

	चयन (queue->qid) अणु
	हाल QID_RX:
		queue->limit = 128;
		queue->data_size = AGGREGATION_SIZE;
		queue->desc_size = RXINFO_DESC_SIZE;
		queue->winfo_size = rxwi_size;
		queue->priv_size = माप(काष्ठा queue_entry_priv_usb);
		अवरोध;

	हाल QID_AC_VO:
	हाल QID_AC_VI:
	हाल QID_AC_BE:
	हाल QID_AC_BK:
		queue->limit = 16;
		queue->data_size = AGGREGATION_SIZE;
		queue->desc_size = TXINFO_DESC_SIZE;
		queue->winfo_size = txwi_size;
		queue->priv_size = माप(काष्ठा queue_entry_priv_usb);
		अवरोध;

	हाल QID_BEACON:
		queue->limit = 8;
		queue->data_size = MGMT_FRAME_SIZE;
		queue->desc_size = TXINFO_DESC_SIZE;
		queue->winfo_size = txwi_size;
		queue->priv_size = माप(काष्ठा queue_entry_priv_usb);
		अवरोध;

	हाल QID_ATIM:
	शेष:
		BUG();
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा rt2x00_ops rt2800usb_ops = अणु
	.name			= KBUILD_MODNAME,
	.drv_data_size		= माप(काष्ठा rt2800_drv_data),
	.max_ap_पूर्णांकf		= 8,
	.eeprom_size		= EEPROM_SIZE,
	.rf_size		= RF_SIZE,
	.tx_queues		= NUM_TX_QUEUES,
	.queue_init		= rt2800usb_queue_init,
	.lib			= &rt2800usb_rt2x00_ops,
	.drv			= &rt2800usb_rt2800_ops,
	.hw			= &rt2800usb_mac80211_ops,
#अगर_घोषित CONFIG_RT2X00_LIB_DEBUGFS
	.debugfs		= &rt2800_rt2x00debug,
#पूर्ण_अगर /* CONFIG_RT2X00_LIB_DEBUGFS */
पूर्ण;

/*
 * rt2800usb module inक्रमmation.
 */
अटल स्थिर काष्ठा usb_device_id rt2800usb_device_table[] = अणु
	/* Abocom */
	अणु USB_DEVICE(0x07b8, 0x2870) पूर्ण,
	अणु USB_DEVICE(0x07b8, 0x2770) पूर्ण,
	अणु USB_DEVICE(0x07b8, 0x3070) पूर्ण,
	अणु USB_DEVICE(0x07b8, 0x3071) पूर्ण,
	अणु USB_DEVICE(0x07b8, 0x3072) पूर्ण,
	अणु USB_DEVICE(0x1482, 0x3c09) पूर्ण,
	/* AirTies */
	अणु USB_DEVICE(0x1eda, 0x2012) पूर्ण,
	अणु USB_DEVICE(0x1eda, 0x2210) पूर्ण,
	अणु USB_DEVICE(0x1eda, 0x2310) पूर्ण,
	/* Allwin */
	अणु USB_DEVICE(0x8516, 0x2070) पूर्ण,
	अणु USB_DEVICE(0x8516, 0x2770) पूर्ण,
	अणु USB_DEVICE(0x8516, 0x2870) पूर्ण,
	अणु USB_DEVICE(0x8516, 0x3070) पूर्ण,
	अणु USB_DEVICE(0x8516, 0x3071) पूर्ण,
	अणु USB_DEVICE(0x8516, 0x3072) पूर्ण,
	/* Alpha Networks */
	अणु USB_DEVICE(0x14b2, 0x3c06) पूर्ण,
	अणु USB_DEVICE(0x14b2, 0x3c07) पूर्ण,
	अणु USB_DEVICE(0x14b2, 0x3c09) पूर्ण,
	अणु USB_DEVICE(0x14b2, 0x3c12) पूर्ण,
	अणु USB_DEVICE(0x14b2, 0x3c23) पूर्ण,
	अणु USB_DEVICE(0x14b2, 0x3c25) पूर्ण,
	अणु USB_DEVICE(0x14b2, 0x3c27) पूर्ण,
	अणु USB_DEVICE(0x14b2, 0x3c28) पूर्ण,
	अणु USB_DEVICE(0x14b2, 0x3c2c) पूर्ण,
	/* Amit */
	अणु USB_DEVICE(0x15c5, 0x0008) पूर्ण,
	/* Askey */
	अणु USB_DEVICE(0x1690, 0x0740) पूर्ण,
	/* ASUS */
	अणु USB_DEVICE(0x0b05, 0x1731) पूर्ण,
	अणु USB_DEVICE(0x0b05, 0x1732) पूर्ण,
	अणु USB_DEVICE(0x0b05, 0x1742) पूर्ण,
	अणु USB_DEVICE(0x0b05, 0x1784) पूर्ण,
	अणु USB_DEVICE(0x1761, 0x0b05) पूर्ण,
	/* AzureWave */
	अणु USB_DEVICE(0x13d3, 0x3247) पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3273) पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3305) पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3307) पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3321) पूर्ण,
	/* Belkin */
	अणु USB_DEVICE(0x050d, 0x8053) पूर्ण,
	अणु USB_DEVICE(0x050d, 0x805c) पूर्ण,
	अणु USB_DEVICE(0x050d, 0x815c) पूर्ण,
	अणु USB_DEVICE(0x050d, 0x825a) पूर्ण,
	अणु USB_DEVICE(0x050d, 0x825b) पूर्ण,
	अणु USB_DEVICE(0x050d, 0x935a) पूर्ण,
	अणु USB_DEVICE(0x050d, 0x935b) पूर्ण,
	/* Buffalo */
	अणु USB_DEVICE(0x0411, 0x00e8) पूर्ण,
	अणु USB_DEVICE(0x0411, 0x0158) पूर्ण,
	अणु USB_DEVICE(0x0411, 0x015d) पूर्ण,
	अणु USB_DEVICE(0x0411, 0x016f) पूर्ण,
	अणु USB_DEVICE(0x0411, 0x01a2) पूर्ण,
	अणु USB_DEVICE(0x0411, 0x01ee) पूर्ण,
	अणु USB_DEVICE(0x0411, 0x01a8) पूर्ण,
	अणु USB_DEVICE(0x0411, 0x01fd) पूर्ण,
	/* Corega */
	अणु USB_DEVICE(0x07aa, 0x002f) पूर्ण,
	अणु USB_DEVICE(0x07aa, 0x003c) पूर्ण,
	अणु USB_DEVICE(0x07aa, 0x003f) पूर्ण,
	अणु USB_DEVICE(0x18c5, 0x0012) पूर्ण,
	/* D-Link */
	अणु USB_DEVICE(0x07d1, 0x3c09) पूर्ण,
	अणु USB_DEVICE(0x07d1, 0x3c0a) पूर्ण,
	अणु USB_DEVICE(0x07d1, 0x3c0d) पूर्ण,
	अणु USB_DEVICE(0x07d1, 0x3c0e) पूर्ण,
	अणु USB_DEVICE(0x07d1, 0x3c0f) पूर्ण,
	अणु USB_DEVICE(0x07d1, 0x3c11) पूर्ण,
	अणु USB_DEVICE(0x07d1, 0x3c13) पूर्ण,
	अणु USB_DEVICE(0x07d1, 0x3c15) पूर्ण,
	अणु USB_DEVICE(0x07d1, 0x3c16) पूर्ण,
	अणु USB_DEVICE(0x07d1, 0x3c17) पूर्ण,
	अणु USB_DEVICE(0x2001, 0x3317) पूर्ण,
	अणु USB_DEVICE(0x2001, 0x3c1b) पूर्ण,
	अणु USB_DEVICE(0x2001, 0x3c25) पूर्ण,
	/* Draytek */
	अणु USB_DEVICE(0x07fa, 0x7712) पूर्ण,
	/* DVICO */
	अणु USB_DEVICE(0x0fe9, 0xb307) पूर्ण,
	/* Edimax */
	अणु USB_DEVICE(0x7392, 0x4085) पूर्ण,
	अणु USB_DEVICE(0x7392, 0x7711) पूर्ण,
	अणु USB_DEVICE(0x7392, 0x7717) पूर्ण,
	अणु USB_DEVICE(0x7392, 0x7718) पूर्ण,
	अणु USB_DEVICE(0x7392, 0x7722) पूर्ण,
	/* Encore */
	अणु USB_DEVICE(0x203d, 0x1480) पूर्ण,
	अणु USB_DEVICE(0x203d, 0x14a9) पूर्ण,
	/* EnGenius */
	अणु USB_DEVICE(0x1740, 0x9701) पूर्ण,
	अणु USB_DEVICE(0x1740, 0x9702) पूर्ण,
	अणु USB_DEVICE(0x1740, 0x9703) पूर्ण,
	अणु USB_DEVICE(0x1740, 0x9705) पूर्ण,
	अणु USB_DEVICE(0x1740, 0x9706) पूर्ण,
	अणु USB_DEVICE(0x1740, 0x9707) पूर्ण,
	अणु USB_DEVICE(0x1740, 0x9708) पूर्ण,
	अणु USB_DEVICE(0x1740, 0x9709) पूर्ण,
	/* Gemtek */
	अणु USB_DEVICE(0x15a9, 0x0012) पूर्ण,
	/* Gigabyte */
	अणु USB_DEVICE(0x1044, 0x800b) पूर्ण,
	अणु USB_DEVICE(0x1044, 0x800d) पूर्ण,
	/* Hawking */
	अणु USB_DEVICE(0x0e66, 0x0001) पूर्ण,
	अणु USB_DEVICE(0x0e66, 0x0003) पूर्ण,
	अणु USB_DEVICE(0x0e66, 0x0009) पूर्ण,
	अणु USB_DEVICE(0x0e66, 0x000b) पूर्ण,
	अणु USB_DEVICE(0x0e66, 0x0013) पूर्ण,
	अणु USB_DEVICE(0x0e66, 0x0017) पूर्ण,
	अणु USB_DEVICE(0x0e66, 0x0018) पूर्ण,
	/* I-O DATA */
	अणु USB_DEVICE(0x04bb, 0x0945) पूर्ण,
	अणु USB_DEVICE(0x04bb, 0x0947) पूर्ण,
	अणु USB_DEVICE(0x04bb, 0x0948) पूर्ण,
	/* Linksys */
	अणु USB_DEVICE(0x13b1, 0x0031) पूर्ण,
	अणु USB_DEVICE(0x1737, 0x0070) पूर्ण,
	अणु USB_DEVICE(0x1737, 0x0071) पूर्ण,
	अणु USB_DEVICE(0x1737, 0x0077) पूर्ण,
	अणु USB_DEVICE(0x1737, 0x0078) पूर्ण,
	/* Logitec */
	अणु USB_DEVICE(0x0789, 0x0162) पूर्ण,
	अणु USB_DEVICE(0x0789, 0x0163) पूर्ण,
	अणु USB_DEVICE(0x0789, 0x0164) पूर्ण,
	अणु USB_DEVICE(0x0789, 0x0166) पूर्ण,
	/* Motorola */
	अणु USB_DEVICE(0x100d, 0x9031) पूर्ण,
	/* MSI */
	अणु USB_DEVICE(0x0db0, 0x3820) पूर्ण,
	अणु USB_DEVICE(0x0db0, 0x3821) पूर्ण,
	अणु USB_DEVICE(0x0db0, 0x3822) पूर्ण,
	अणु USB_DEVICE(0x0db0, 0x3870) पूर्ण,
	अणु USB_DEVICE(0x0db0, 0x3871) पूर्ण,
	अणु USB_DEVICE(0x0db0, 0x6899) पूर्ण,
	अणु USB_DEVICE(0x0db0, 0x821a) पूर्ण,
	अणु USB_DEVICE(0x0db0, 0x822a) पूर्ण,
	अणु USB_DEVICE(0x0db0, 0x822b) पूर्ण,
	अणु USB_DEVICE(0x0db0, 0x822c) पूर्ण,
	अणु USB_DEVICE(0x0db0, 0x870a) पूर्ण,
	अणु USB_DEVICE(0x0db0, 0x871a) पूर्ण,
	अणु USB_DEVICE(0x0db0, 0x871b) पूर्ण,
	अणु USB_DEVICE(0x0db0, 0x871c) पूर्ण,
	अणु USB_DEVICE(0x0db0, 0x899a) पूर्ण,
	/* Ovislink */
	अणु USB_DEVICE(0x1b75, 0x3070) पूर्ण,
	अणु USB_DEVICE(0x1b75, 0x3071) पूर्ण,
	अणु USB_DEVICE(0x1b75, 0x3072) पूर्ण,
	अणु USB_DEVICE(0x1b75, 0xa200) पूर्ण,
	/* Para */
	अणु USB_DEVICE(0x20b8, 0x8888) पूर्ण,
	/* Pegatron */
	अणु USB_DEVICE(0x1d4d, 0x0002) पूर्ण,
	अणु USB_DEVICE(0x1d4d, 0x000c) पूर्ण,
	अणु USB_DEVICE(0x1d4d, 0x000e) पूर्ण,
	अणु USB_DEVICE(0x1d4d, 0x0011) पूर्ण,
	/* Philips */
	अणु USB_DEVICE(0x0471, 0x200f) पूर्ण,
	/* Planex */
	अणु USB_DEVICE(0x2019, 0x5201) पूर्ण,
	अणु USB_DEVICE(0x2019, 0xab25) पूर्ण,
	अणु USB_DEVICE(0x2019, 0xed06) पूर्ण,
	/* Quanta */
	अणु USB_DEVICE(0x1a32, 0x0304) पूर्ण,
	/* Ralink */
	अणु USB_DEVICE(0x148f, 0x2070) पूर्ण,
	अणु USB_DEVICE(0x148f, 0x2770) पूर्ण,
	अणु USB_DEVICE(0x148f, 0x2870) पूर्ण,
	अणु USB_DEVICE(0x148f, 0x3070) पूर्ण,
	अणु USB_DEVICE(0x148f, 0x3071) पूर्ण,
	अणु USB_DEVICE(0x148f, 0x3072) पूर्ण,
	/* Samsung */
	अणु USB_DEVICE(0x04e8, 0x2018) पूर्ण,
	/* Siemens */
	अणु USB_DEVICE(0x129b, 0x1828) पूर्ण,
	/* Sitecom */
	अणु USB_DEVICE(0x0df6, 0x0017) पूर्ण,
	अणु USB_DEVICE(0x0df6, 0x002b) पूर्ण,
	अणु USB_DEVICE(0x0df6, 0x002c) पूर्ण,
	अणु USB_DEVICE(0x0df6, 0x002d) पूर्ण,
	अणु USB_DEVICE(0x0df6, 0x0039) पूर्ण,
	अणु USB_DEVICE(0x0df6, 0x003b) पूर्ण,
	अणु USB_DEVICE(0x0df6, 0x003d) पूर्ण,
	अणु USB_DEVICE(0x0df6, 0x003e) पूर्ण,
	अणु USB_DEVICE(0x0df6, 0x003f) पूर्ण,
	अणु USB_DEVICE(0x0df6, 0x0040) पूर्ण,
	अणु USB_DEVICE(0x0df6, 0x0042) पूर्ण,
	अणु USB_DEVICE(0x0df6, 0x0047) पूर्ण,
	अणु USB_DEVICE(0x0df6, 0x0048) पूर्ण,
	अणु USB_DEVICE(0x0df6, 0x0051) पूर्ण,
	अणु USB_DEVICE(0x0df6, 0x005f) पूर्ण,
	अणु USB_DEVICE(0x0df6, 0x0060) पूर्ण,
	/* SMC */
	अणु USB_DEVICE(0x083a, 0x6618) पूर्ण,
	अणु USB_DEVICE(0x083a, 0x7511) पूर्ण,
	अणु USB_DEVICE(0x083a, 0x7512) पूर्ण,
	अणु USB_DEVICE(0x083a, 0x7522) पूर्ण,
	अणु USB_DEVICE(0x083a, 0x8522) पूर्ण,
	अणु USB_DEVICE(0x083a, 0xa618) पूर्ण,
	अणु USB_DEVICE(0x083a, 0xa701) पूर्ण,
	अणु USB_DEVICE(0x083a, 0xa702) पूर्ण,
	अणु USB_DEVICE(0x083a, 0xa703) पूर्ण,
	अणु USB_DEVICE(0x083a, 0xb522) पूर्ण,
	/* Sparklan */
	अणु USB_DEVICE(0x15a9, 0x0006) पूर्ण,
	/* Sweex */
	अणु USB_DEVICE(0x177f, 0x0153) पूर्ण,
	अणु USB_DEVICE(0x177f, 0x0164) पूर्ण,
	अणु USB_DEVICE(0x177f, 0x0302) पूर्ण,
	अणु USB_DEVICE(0x177f, 0x0313) पूर्ण,
	अणु USB_DEVICE(0x177f, 0x0323) पूर्ण,
	अणु USB_DEVICE(0x177f, 0x0324) पूर्ण,
	अणु USB_DEVICE(0x177f, 0x1163) पूर्ण,
	/* U-Media */
	अणु USB_DEVICE(0x157e, 0x300e) पूर्ण,
	अणु USB_DEVICE(0x157e, 0x3013) पूर्ण,
	/* ZCOM */
	अणु USB_DEVICE(0x0cde, 0x0022) पूर्ण,
	अणु USB_DEVICE(0x0cde, 0x0025) पूर्ण,
	/* Zinwell */
	अणु USB_DEVICE(0x5a57, 0x0280) पूर्ण,
	अणु USB_DEVICE(0x5a57, 0x0282) पूर्ण,
	अणु USB_DEVICE(0x5a57, 0x0283) पूर्ण,
	अणु USB_DEVICE(0x5a57, 0x5257) पूर्ण,
	/* Zyxel */
	अणु USB_DEVICE(0x0586, 0x3416) पूर्ण,
	अणु USB_DEVICE(0x0586, 0x3418) पूर्ण,
	अणु USB_DEVICE(0x0586, 0x341a) पूर्ण,
	अणु USB_DEVICE(0x0586, 0x341e) पूर्ण,
	अणु USB_DEVICE(0x0586, 0x343e) पूर्ण,
#अगर_घोषित CONFIG_RT2800USB_RT33XX
	/* Belkin */
	अणु USB_DEVICE(0x050d, 0x945b) पूर्ण,
	/* D-Link */
	अणु USB_DEVICE(0x2001, 0x3c17) पूर्ण,
	/* Panasonic */
	अणु USB_DEVICE(0x083a, 0xb511) पूर्ण,
	/* Accton/Arcadyan/Epson */
	अणु USB_DEVICE(0x083a, 0xb512) पूर्ण,
	/* Philips */
	अणु USB_DEVICE(0x0471, 0x20dd) पूर्ण,
	/* Ralink */
	अणु USB_DEVICE(0x148f, 0x3370) पूर्ण,
	अणु USB_DEVICE(0x148f, 0x8070) पूर्ण,
	/* Sitecom */
	अणु USB_DEVICE(0x0df6, 0x0050) पूर्ण,
	/* Sweex */
	अणु USB_DEVICE(0x177f, 0x0163) पूर्ण,
	अणु USB_DEVICE(0x177f, 0x0165) पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_RT2800USB_RT35XX
	/* Allwin */
	अणु USB_DEVICE(0x8516, 0x3572) पूर्ण,
	/* Askey */
	अणु USB_DEVICE(0x1690, 0x0744) पूर्ण,
	अणु USB_DEVICE(0x1690, 0x0761) पूर्ण,
	अणु USB_DEVICE(0x1690, 0x0764) पूर्ण,
	/* ASUS */
	अणु USB_DEVICE(0x0b05, 0x179d) पूर्ण,
	/* Cisco */
	अणु USB_DEVICE(0x167b, 0x4001) पूर्ण,
	/* EnGenius */
	अणु USB_DEVICE(0x1740, 0x9801) पूर्ण,
	/* I-O DATA */
	अणु USB_DEVICE(0x04bb, 0x0944) पूर्ण,
	/* Linksys */
	अणु USB_DEVICE(0x13b1, 0x002f) पूर्ण,
	अणु USB_DEVICE(0x1737, 0x0079) पूर्ण,
	/* Logitec */
	अणु USB_DEVICE(0x0789, 0x0170) पूर्ण,
	/* Ralink */
	अणु USB_DEVICE(0x148f, 0x3572) पूर्ण,
	/* Sitecom */
	अणु USB_DEVICE(0x0df6, 0x0041) पूर्ण,
	अणु USB_DEVICE(0x0df6, 0x0062) पूर्ण,
	अणु USB_DEVICE(0x0df6, 0x0065) पूर्ण,
	अणु USB_DEVICE(0x0df6, 0x0066) पूर्ण,
	अणु USB_DEVICE(0x0df6, 0x0068) पूर्ण,
	/* Toshiba */
	अणु USB_DEVICE(0x0930, 0x0a07) पूर्ण,
	/* Zinwell */
	अणु USB_DEVICE(0x5a57, 0x0284) पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_RT2800USB_RT3573
	/* AirLive */
	अणु USB_DEVICE(0x1b75, 0x7733) पूर्ण,
	/* ASUS */
	अणु USB_DEVICE(0x0b05, 0x17bc) पूर्ण,
	अणु USB_DEVICE(0x0b05, 0x17ad) पूर्ण,
	/* Belkin */
	अणु USB_DEVICE(0x050d, 0x1103) पूर्ण,
	/* Cameo */
	अणु USB_DEVICE(0x148f, 0xf301) पूर्ण,
	/* D-Link */
	अणु USB_DEVICE(0x2001, 0x3c1f) पूर्ण,
	/* Edimax */
	अणु USB_DEVICE(0x7392, 0x7733) पूर्ण,
	/* Hawking */
	अणु USB_DEVICE(0x0e66, 0x0020) पूर्ण,
	अणु USB_DEVICE(0x0e66, 0x0021) पूर्ण,
	/* I-O DATA */
	अणु USB_DEVICE(0x04bb, 0x094e) पूर्ण,
	/* Linksys */
	अणु USB_DEVICE(0x13b1, 0x003b) पूर्ण,
	/* Logitec */
	अणु USB_DEVICE(0x0789, 0x016b) पूर्ण,
	/* NETGEAR */
	अणु USB_DEVICE(0x0846, 0x9012) पूर्ण,
	अणु USB_DEVICE(0x0846, 0x9013) पूर्ण,
	अणु USB_DEVICE(0x0846, 0x9019) पूर्ण,
	/* Planex */
	अणु USB_DEVICE(0x2019, 0xed14) पूर्ण,
	अणु USB_DEVICE(0x2019, 0xed19) पूर्ण,
	/* Ralink */
	अणु USB_DEVICE(0x148f, 0x3573) पूर्ण,
	/* Sitecom */
	अणु USB_DEVICE(0x0df6, 0x0067) पूर्ण,
	अणु USB_DEVICE(0x0df6, 0x006a) पूर्ण,
	अणु USB_DEVICE(0x0df6, 0x006e) पूर्ण,
	/* ZyXEL */
	अणु USB_DEVICE(0x0586, 0x3421) पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_RT2800USB_RT53XX
	/* Arcadyan */
	अणु USB_DEVICE(0x043e, 0x7a12) पूर्ण,
	अणु USB_DEVICE(0x043e, 0x7a32) पूर्ण,
	/* ASUS */
	अणु USB_DEVICE(0x0b05, 0x17e8) पूर्ण,
	/* Azurewave */
	अणु USB_DEVICE(0x13d3, 0x3329) पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3365) पूर्ण,
	/* D-Link */
	अणु USB_DEVICE(0x2001, 0x3c15) पूर्ण,
	अणु USB_DEVICE(0x2001, 0x3c19) पूर्ण,
	अणु USB_DEVICE(0x2001, 0x3c1c) पूर्ण,
	अणु USB_DEVICE(0x2001, 0x3c1d) पूर्ण,
	अणु USB_DEVICE(0x2001, 0x3c1e) पूर्ण,
	अणु USB_DEVICE(0x2001, 0x3c20) पूर्ण,
	अणु USB_DEVICE(0x2001, 0x3c22) पूर्ण,
	अणु USB_DEVICE(0x2001, 0x3c23) पूर्ण,
	/* LG innotek */
	अणु USB_DEVICE(0x043e, 0x7a22) पूर्ण,
	अणु USB_DEVICE(0x043e, 0x7a42) पूर्ण,
	/* Panasonic */
	अणु USB_DEVICE(0x04da, 0x1801) पूर्ण,
	अणु USB_DEVICE(0x04da, 0x1800) पूर्ण,
	अणु USB_DEVICE(0x04da, 0x23f6) पूर्ण,
	/* Philips */
	अणु USB_DEVICE(0x0471, 0x2104) पूर्ण,
	अणु USB_DEVICE(0x0471, 0x2126) पूर्ण,
	अणु USB_DEVICE(0x0471, 0x2180) पूर्ण,
	अणु USB_DEVICE(0x0471, 0x2181) पूर्ण,
	अणु USB_DEVICE(0x0471, 0x2182) पूर्ण,
	/* Ralink */
	अणु USB_DEVICE(0x148f, 0x5370) पूर्ण,
	अणु USB_DEVICE(0x148f, 0x5372) पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_RT2800USB_RT55XX
	/* Arcadyan */
	अणु USB_DEVICE(0x043e, 0x7a32) पूर्ण,
	/* AVM GmbH */
	अणु USB_DEVICE(0x057c, 0x8501) पूर्ण,
	/* Buffalo */
	अणु USB_DEVICE(0x0411, 0x0241) पूर्ण,
	अणु USB_DEVICE(0x0411, 0x0253) पूर्ण,
	/* D-Link */
	अणु USB_DEVICE(0x2001, 0x3c1a) पूर्ण,
	अणु USB_DEVICE(0x2001, 0x3c21) पूर्ण,
	/* Proware */
	अणु USB_DEVICE(0x043e, 0x7a13) पूर्ण,
	/* Ralink */
	अणु USB_DEVICE(0x148f, 0x5572) पूर्ण,
	/* TRENDnet */
	अणु USB_DEVICE(0x20f4, 0x724a) पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_RT2800USB_UNKNOWN
	/*
	 * Unclear what kind of devices these are (they aren't supported by the
	 * venकरोr linux driver).
	 */
	/* Abocom */
	अणु USB_DEVICE(0x07b8, 0x3073) पूर्ण,
	अणु USB_DEVICE(0x07b8, 0x3074) पूर्ण,
	/* Alpha Networks */
	अणु USB_DEVICE(0x14b2, 0x3c08) पूर्ण,
	अणु USB_DEVICE(0x14b2, 0x3c11) पूर्ण,
	/* Amigo */
	अणु USB_DEVICE(0x0e0b, 0x9031) पूर्ण,
	अणु USB_DEVICE(0x0e0b, 0x9041) पूर्ण,
	/* ASUS */
	अणु USB_DEVICE(0x0b05, 0x166a) पूर्ण,
	अणु USB_DEVICE(0x0b05, 0x1760) पूर्ण,
	अणु USB_DEVICE(0x0b05, 0x1761) पूर्ण,
	अणु USB_DEVICE(0x0b05, 0x1790) पूर्ण,
	अणु USB_DEVICE(0x0b05, 0x17a7) पूर्ण,
	/* AzureWave */
	अणु USB_DEVICE(0x13d3, 0x3262) पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3284) पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3322) पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3340) पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3399) पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3400) पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3401) पूर्ण,
	/* Belkin */
	अणु USB_DEVICE(0x050d, 0x1003) पूर्ण,
	/* Buffalo */
	अणु USB_DEVICE(0x0411, 0x012e) पूर्ण,
	अणु USB_DEVICE(0x0411, 0x0148) पूर्ण,
	अणु USB_DEVICE(0x0411, 0x0150) पूर्ण,
	/* Corega */
	अणु USB_DEVICE(0x07aa, 0x0041) पूर्ण,
	अणु USB_DEVICE(0x07aa, 0x0042) पूर्ण,
	अणु USB_DEVICE(0x18c5, 0x0008) पूर्ण,
	/* D-Link */
	अणु USB_DEVICE(0x07d1, 0x3c0b) पूर्ण,
	/* Encore */
	अणु USB_DEVICE(0x203d, 0x14a1) पूर्ण,
	/* EnGenius */
	अणु USB_DEVICE(0x1740, 0x0600) पूर्ण,
	अणु USB_DEVICE(0x1740, 0x0602) पूर्ण,
	/* Gemtek */
	अणु USB_DEVICE(0x15a9, 0x0010) पूर्ण,
	/* Gigabyte */
	अणु USB_DEVICE(0x1044, 0x800c) पूर्ण,
	/* Hercules */
	अणु USB_DEVICE(0x06f8, 0xe036) पूर्ण,
	/* Huawei */
	अणु USB_DEVICE(0x148f, 0xf101) पूर्ण,
	/* I-O DATA */
	अणु USB_DEVICE(0x04bb, 0x094b) पूर्ण,
	/* LevelOne */
	अणु USB_DEVICE(0x1740, 0x0605) पूर्ण,
	अणु USB_DEVICE(0x1740, 0x0615) पूर्ण,
	/* Logitec */
	अणु USB_DEVICE(0x0789, 0x0168) पूर्ण,
	अणु USB_DEVICE(0x0789, 0x0169) पूर्ण,
	/* Motorola */
	अणु USB_DEVICE(0x100d, 0x9032) पूर्ण,
	/* Pegatron */
	अणु USB_DEVICE(0x05a6, 0x0101) पूर्ण,
	अणु USB_DEVICE(0x1d4d, 0x0010) पूर्ण,
	/* Planex */
	अणु USB_DEVICE(0x2019, 0xab24) पूर्ण,
	अणु USB_DEVICE(0x2019, 0xab29) पूर्ण,
	/* Qcom */
	अणु USB_DEVICE(0x18e8, 0x6259) पूर्ण,
	/* RadioShack */
	अणु USB_DEVICE(0x08b9, 0x1197) पूर्ण,
	/* Sitecom */
	अणु USB_DEVICE(0x0df6, 0x003c) पूर्ण,
	अणु USB_DEVICE(0x0df6, 0x004a) पूर्ण,
	अणु USB_DEVICE(0x0df6, 0x004d) पूर्ण,
	अणु USB_DEVICE(0x0df6, 0x0053) पूर्ण,
	अणु USB_DEVICE(0x0df6, 0x0069) पूर्ण,
	अणु USB_DEVICE(0x0df6, 0x006f) पूर्ण,
	अणु USB_DEVICE(0x0df6, 0x0078) पूर्ण,
	/* SMC */
	अणु USB_DEVICE(0x083a, 0xa512) पूर्ण,
	अणु USB_DEVICE(0x083a, 0xc522) पूर्ण,
	अणु USB_DEVICE(0x083a, 0xd522) पूर्ण,
	अणु USB_DEVICE(0x083a, 0xf511) पूर्ण,
	/* Sweex */
	अणु USB_DEVICE(0x177f, 0x0254) पूर्ण,
	/* TP-LINK */
	अणु USB_DEVICE(0xf201, 0x5370) पूर्ण,
#पूर्ण_अगर
	अणु 0, पूर्ण
पूर्ण;

MODULE_AUTHOR(DRV_PROJECT);
MODULE_VERSION(DRV_VERSION);
MODULE_DESCRIPTION("Ralink RT2800 USB Wireless LAN driver.");
MODULE_DEVICE_TABLE(usb, rt2800usb_device_table);
MODULE_FIRMWARE(FIRMWARE_RT2870);
MODULE_LICENSE("GPL");

अटल पूर्णांक rt2800usb_probe(काष्ठा usb_पूर्णांकerface *usb_पूर्णांकf,
			   स्थिर काष्ठा usb_device_id *id)
अणु
	वापस rt2x00usb_probe(usb_पूर्णांकf, &rt2800usb_ops);
पूर्ण

अटल काष्ठा usb_driver rt2800usb_driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= rt2800usb_device_table,
	.probe		= rt2800usb_probe,
	.disconnect	= rt2x00usb_disconnect,
	.suspend	= rt2x00usb_suspend,
	.resume		= rt2x00usb_resume,
	.reset_resume	= rt2x00usb_resume,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(rt2800usb_driver);
