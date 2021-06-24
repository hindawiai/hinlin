<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/* Driver क्रम ETAS GmbH ES58X USB CAN(-FD) Bus Interfaces.
 *
 * File es58x_core.c: Core logic to manage the network devices and the
 * USB पूर्णांकerface.
 *
 * Copyright (c) 2019 Robert Bosch Engineering and Business Solutions. All rights reserved.
 * Copyright (c) 2020 ETAS K.K.. All rights reserved.
 * Copyright (c) 2020, 2021 Vincent Mailhol <mailhol.vincent@wanaकरोo.fr>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/crc16.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "es58x_core.h"

#घोषणा DRV_VERSION "1.00"
MODULE_AUTHOR("Mailhol Vincent <mailhol.vincent@wanadoo.fr>");
MODULE_AUTHOR("Arunachalam Santhanam <arunachalam.santhanam@in.bosch.com>");
MODULE_DESCRIPTION("Socket CAN driver for ETAS ES58X USB adapters");
MODULE_VERSION(DRV_VERSION);
MODULE_LICENSE("GPL v2");

#घोषणा ES58X_MODULE_NAME "etas_es58x"
#घोषणा ES58X_VENDOR_ID 0x108C
#घोषणा ES581_4_PRODUCT_ID 0x0159
#घोषणा ES582_1_PRODUCT_ID 0x0168
#घोषणा ES584_1_PRODUCT_ID 0x0169

/* ES58X FD has some पूर्णांकerface protocols unsupported by this driver. */
#घोषणा ES58X_FD_INTERFACE_PROTOCOL 0

/* Table of devices which work with this driver. */
अटल स्थिर काष्ठा usb_device_id es58x_id_table[] = अणु
	अणु
		/* ETAS GmbH ES581.4 USB dual-channel CAN Bus Interface module. */
		USB_DEVICE(ES58X_VENDOR_ID, ES581_4_PRODUCT_ID),
		.driver_info = ES58X_DUAL_CHANNEL
	पूर्ण, अणु
		/* ETAS GmbH ES582.1 USB dual-channel CAN FD Bus Interface module. */
		USB_DEVICE_INTERFACE_PROTOCOL(ES58X_VENDOR_ID, ES582_1_PRODUCT_ID,
					      ES58X_FD_INTERFACE_PROTOCOL),
		.driver_info = ES58X_DUAL_CHANNEL | ES58X_FD_FAMILY
	पूर्ण, अणु
		/* ETAS GmbH ES584.1 USB single-channel CAN FD Bus Interface module. */
		USB_DEVICE_INTERFACE_PROTOCOL(ES58X_VENDOR_ID, ES584_1_PRODUCT_ID,
					      ES58X_FD_INTERFACE_PROTOCOL),
		.driver_info = ES58X_FD_FAMILY
	पूर्ण, अणु
		/* Terminating entry */
	पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, es58x_id_table);

#घोषणा es58x_prपूर्णांक_hex_dump(buf, len)					\
	prपूर्णांक_hex_dump(KERN_DEBUG,					\
		       ES58X_MODULE_NAME " " __stringअगरy(buf) ": ",	\
		       DUMP_PREFIX_NONE, 16, 1, buf, len, false)

#घोषणा es58x_prपूर्णांक_hex_dump_debug(buf, len)				 \
	prपूर्णांक_hex_dump_debug(ES58X_MODULE_NAME " " __stringअगरy(buf) ": ",\
			     DUMP_PREFIX_NONE, 16, 1, buf, len, false)

/* The last two bytes of an ES58X command is a CRC16. The first two
 * bytes (the start of frame) are skipped and the CRC calculation
 * starts on the third byte.
 */
#घोषणा ES58X_CRC_CALC_OFFSET 2

/**
 * es58x_calculate_crc() - Compute the crc16 of a given URB.
 * @urb_cmd: The URB command क्रम which we want to calculate the CRC.
 * @urb_len: Length of @urb_cmd. Must be at least bigger than 4
 *	(ES58X_CRC_CALC_OFFSET + माप(crc))
 *
 * Return: crc16 value.
 */
अटल u16 es58x_calculate_crc(स्थिर जोड़ es58x_urb_cmd *urb_cmd, u16 urb_len)
अणु
	u16 crc;
	sमाप_प्रकार len = urb_len - ES58X_CRC_CALC_OFFSET - माप(crc);

	crc = crc16(0, &urb_cmd->raw_cmd[ES58X_CRC_CALC_OFFSET], len);
	वापस crc;
पूर्ण

/**
 * es58x_get_crc() - Get the CRC value of a given URB.
 * @urb_cmd: The URB command क्रम which we want to get the CRC.
 * @urb_len: Length of @urb_cmd. Must be at least bigger than 4
 *	(ES58X_CRC_CALC_OFFSET + माप(crc))
 *
 * Return: crc16 value.
 */
अटल u16 es58x_get_crc(स्थिर जोड़ es58x_urb_cmd *urb_cmd, u16 urb_len)
अणु
	u16 crc;
	स्थिर __le16 *crc_addr;

	crc_addr = (__le16 *)&urb_cmd->raw_cmd[urb_len - माप(crc)];
	crc = get_unaligned_le16(crc_addr);
	वापस crc;
पूर्ण

/**
 * es58x_set_crc() - Set the CRC value of a given URB.
 * @urb_cmd: The URB command क्रम which we want to get the CRC.
 * @urb_len: Length of @urb_cmd. Must be at least bigger than 4
 *	(ES58X_CRC_CALC_OFFSET + माप(crc))
 */
अटल व्योम es58x_set_crc(जोड़ es58x_urb_cmd *urb_cmd, u16 urb_len)
अणु
	u16 crc;
	__le16 *crc_addr;

	crc = es58x_calculate_crc(urb_cmd, urb_len);
	crc_addr = (__le16 *)&urb_cmd->raw_cmd[urb_len - माप(crc)];
	put_unaligned_le16(crc, crc_addr);
पूर्ण

/**
 * es58x_check_crc() - Validate the CRC value of a given URB.
 * @es58x_dev: ES58X device.
 * @urb_cmd: The URB command क्रम which we want to check the CRC.
 * @urb_len: Length of @urb_cmd. Must be at least bigger than 4
 *	(ES58X_CRC_CALC_OFFSET + माप(crc))
 *
 * Return: zero on success, -EBADMSG अगर the CRC check fails.
 */
अटल पूर्णांक es58x_check_crc(काष्ठा es58x_device *es58x_dev,
			   स्थिर जोड़ es58x_urb_cmd *urb_cmd, u16 urb_len)
अणु
	u16 calculated_crc = es58x_calculate_crc(urb_cmd, urb_len);
	u16 expected_crc = es58x_get_crc(urb_cmd, urb_len);

	अगर (expected_crc != calculated_crc) अणु
		dev_err_ratelimited(es58x_dev->dev,
				    "%s: Bad CRC, urb_len: %d\n",
				    __func__, urb_len);
		वापस -EBADMSG;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * es58x_बारtamp_to_ns() - Convert a बारtamp value received from a
 *	ES58X device to nanoseconds.
 * @बारtamp: Timestamp received from a ES58X device.
 *
 * The बारtamp received from ES58X is expressed in multiples of 0.5
 * micro seconds. This function converts it in to nanoseconds.
 *
 * Return: Timestamp value in nanoseconds.
 */
अटल u64 es58x_बारtamp_to_ns(u64 बारtamp)
अणु
	स्थिर u64 es58x_बारtamp_ns_mult_coef = 500ULL;

	वापस es58x_बारtamp_ns_mult_coef * बारtamp;
पूर्ण

/**
 * es58x_set_skb_बारtamp() - Set the hardware बारtamp of an skb.
 * @netdev: CAN network device.
 * @skb: socket buffer of a CAN message.
 * @बारtamp: Timestamp received from an ES58X device.
 *
 * Used क्रम both received and echo messages.
 */
अटल व्योम es58x_set_skb_बारtamp(काष्ठा net_device *netdev,
				    काष्ठा sk_buff *skb, u64 बारtamp)
अणु
	काष्ठा es58x_device *es58x_dev = es58x_priv(netdev)->es58x_dev;
	काष्ठा skb_shared_hwtstamps *hwts;

	hwts = skb_hwtstamps(skb);
	/* Ignoring overflow (overflow on 64 bits बारtamp with nano
	 * second precision would occur after more than 500 years).
	 */
	hwts->hwtstamp = ns_to_kसमय(es58x_बारtamp_to_ns(बारtamp) +
				     es58x_dev->realसमय_dअगरf_ns);
पूर्ण

/**
 * es58x_rx_बारtamp() - Handle a received बारtamp.
 * @es58x_dev: ES58X device.
 * @बारtamp: Timestamp received from a ES58X device.
 *
 * Calculate the dअगरference between the ES58X device and the kernel
 * पूर्णांकernal घड़ीs. This dअगरference will be later used as an offset to
 * convert the बारtamps of RX and echo messages to match the kernel
 * प्रणाली समय (e.g. convert to UNIX समय).
 */
व्योम es58x_rx_बारtamp(काष्ठा es58x_device *es58x_dev, u64 बारtamp)
अणु
	u64 kसमय_real_ns = kसमय_get_real_ns();
	u64 device_बारtamp = es58x_बारtamp_to_ns(बारtamp);

	dev_dbg(es58x_dev->dev, "%s: request round-trip time: %llu ns\n",
		__func__, kसमय_real_ns - es58x_dev->kसमय_req_ns);

	es58x_dev->realसमय_dअगरf_ns =
	    (es58x_dev->kसमय_req_ns + kसमय_real_ns) / 2 - device_बारtamp;
	es58x_dev->kसमय_req_ns = 0;

	dev_dbg(es58x_dev->dev,
		"%s: Device timestamp: %llu, diff with kernel: %llu\n",
		__func__, device_बारtamp, es58x_dev->realसमय_dअगरf_ns);
पूर्ण

/**
 * es58x_set_realसमय_dअगरf_ns() - Calculate dअगरference between the
 *	घड़ीs of the ES58X device and the kernel
 * @es58x_dev: ES58X device.
 *
 * Request a बारtamp from the ES58X device. Once the answer is
 * received, the बारtamp dअगरference will be set by the callback
 * function es58x_rx_बारtamp().
 *
 * Return: zero on success, त्रुटि_सं when any error occurs.
 */
अटल पूर्णांक es58x_set_realसमय_dअगरf_ns(काष्ठा es58x_device *es58x_dev)
अणु
	अगर (es58x_dev->kसमय_req_ns) अणु
		dev_warn(es58x_dev->dev,
			 "%s: Previous request to set timestamp has not completed yet\n",
			 __func__);
		वापस -EBUSY;
	पूर्ण

	es58x_dev->kसमय_req_ns = kसमय_get_real_ns();
	वापस es58x_dev->ops->get_बारtamp(es58x_dev);
पूर्ण

/**
 * es58x_is_can_state_active() - Is the network device in an active
 *	CAN state?
 * @netdev: CAN network device.
 *
 * The device is considered active अगर it is able to send or receive
 * CAN frames, that is to say अगर it is in any of
 * CAN_STATE_ERROR_ACTIVE, CAN_STATE_ERROR_WARNING or
 * CAN_STATE_ERROR_PASSIVE states.
 *
 * Caution: when recovering from a bus-off,
 * net/core/dev.c#can_restart() will call
 * net/core/dev.c#can_flush_echo_skb() without using any kind of
 * locks. For this reason, it is critical to guarantee that no TX or
 * echo operations (i.e. any access to priv->echo_skb[]) can be करोne
 * जबतक this function is वापसing false.
 *
 * Return: true अगर the device is active, अन्यथा वापसs false.
 */
अटल bool es58x_is_can_state_active(काष्ठा net_device *netdev)
अणु
	वापस es58x_priv(netdev)->can.state < CAN_STATE_BUS_OFF;
पूर्ण

/**
 * es58x_is_echo_skb_threshold_reached() - Determine the limit of how
 *	many skb slots can be taken beक्रमe we should stop the network
 *	queue.
 * @priv: ES58X निजी parameters related to the network device.
 *
 * We need to save enough मुक्त skb slots in order to be able to करो
 * bulk send. This function can be used to determine when to wake or
 * stop the network queue in regard to the number of skb slots alपढ़ोy
 * taken अगर the echo FIFO.
 *
 * Return: boolean.
 */
अटल bool es58x_is_echo_skb_threshold_reached(काष्ठा es58x_priv *priv)
अणु
	u32 num_echo_skb =  priv->tx_head - priv->tx_tail;
	u32 threshold = priv->can.echo_skb_max -
		priv->es58x_dev->param->tx_bulk_max + 1;

	वापस num_echo_skb >= threshold;
पूर्ण

/**
 * es58x_can_मुक्त_echo_skb_tail() - Remove the oldest echo skb of the
 *	echo FIFO.
 * @netdev: CAN network device.
 *
 * Naming convention: the tail is the beginning of the FIFO, i.e. the
 * first skb to have entered the FIFO.
 */
अटल व्योम es58x_can_मुक्त_echo_skb_tail(काष्ठा net_device *netdev)
अणु
	काष्ठा es58x_priv *priv = es58x_priv(netdev);
	u16 fअगरo_mask = priv->es58x_dev->param->fअगरo_mask;
	अचिन्हित पूर्णांक frame_len = 0;

	can_मुक्त_echo_skb(netdev, priv->tx_tail & fअगरo_mask, &frame_len);
	netdev_completed_queue(netdev, 1, frame_len);

	priv->tx_tail++;

	netdev->stats.tx_dropped++;
पूर्ण

/**
 * es58x_can_get_echo_skb_recovery() - Try to re-sync the echo FIFO.
 * @netdev: CAN network device.
 * @rcv_packet_idx: Index
 *
 * This function should not be called under normal circumstances. In
 * the unlikely हाल that one or several URB packages get dropped by
 * the device, the index will get out of sync. Try to recover by
 * dropping the echo skb packets with older indexes.
 *
 * Return: zero अगर recovery was successful, -EINVAL otherwise.
 */
अटल पूर्णांक es58x_can_get_echo_skb_recovery(काष्ठा net_device *netdev,
					   u32 rcv_packet_idx)
अणु
	काष्ठा es58x_priv *priv = es58x_priv(netdev);
	पूर्णांक ret = 0;

	netdev->stats.tx_errors++;

	अगर (net_ratelimit())
		netdev_warn(netdev,
			    "Bad echo packet index: %u. First index: %u, end index %u, num_echo_skb: %02u/%02u\n",
			    rcv_packet_idx, priv->tx_tail, priv->tx_head,
			    priv->tx_head - priv->tx_tail,
			    priv->can.echo_skb_max);

	अगर ((s32)(rcv_packet_idx - priv->tx_tail) < 0) अणु
		अगर (net_ratelimit())
			netdev_warn(netdev,
				    "Received echo index is from the past. Ignoring it\n");
		ret = -EINVAL;
	पूर्ण अन्यथा अगर ((s32)(rcv_packet_idx - priv->tx_head) >= 0) अणु
		अगर (net_ratelimit())
			netdev_err(netdev,
				   "Received echo index is from the future. Ignoring it\n");
		ret = -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (net_ratelimit())
			netdev_warn(netdev,
				    "Recovery: dropping %u echo skb from index %u to %u\n",
				    rcv_packet_idx - priv->tx_tail,
				    priv->tx_tail, rcv_packet_idx - 1);
		जबतक (priv->tx_tail != rcv_packet_idx) अणु
			अगर (priv->tx_tail == priv->tx_head)
				वापस -EINVAL;
			es58x_can_मुक्त_echo_skb_tail(netdev);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/**
 * es58x_can_get_echo_skb() - Get the skb from the echo FIFO and loop
 *	it back locally.
 * @netdev: CAN network device.
 * @rcv_packet_idx: Index of the first packet received from the device.
 * @tstamps: Array of hardware बारtamps received from a ES58X device.
 * @pkts: Number of packets (and so, length of @tstamps).
 *
 * Callback function क्रम when we receive a self reception
 * acknowledgment.  Retrieves the skb from the echo FIFO, sets its
 * hardware बारtamp (the actual समय it was sent) and loops it back
 * locally.
 *
 * The device has to be active (i.e. network पूर्णांकerface UP and not in
 * bus off state or restarting).
 *
 * Packet indexes must be consecutive (i.e. index of first packet is
 * @rcv_packet_idx, index of second packet is @rcv_packet_idx + 1 and
 * index of last packet is @rcv_packet_idx + @pkts - 1).
 *
 * Return: zero on success.
 */
पूर्णांक es58x_can_get_echo_skb(काष्ठा net_device *netdev, u32 rcv_packet_idx,
			   u64 *tstamps, अचिन्हित पूर्णांक pkts)
अणु
	काष्ठा es58x_priv *priv = es58x_priv(netdev);
	अचिन्हित पूर्णांक rx_total_frame_len = 0;
	अचिन्हित पूर्णांक num_echo_skb = priv->tx_head - priv->tx_tail;
	पूर्णांक i;
	u16 fअगरo_mask = priv->es58x_dev->param->fअगरo_mask;

	अगर (!netअगर_running(netdev)) अणु
		अगर (net_ratelimit())
			netdev_info(netdev,
				    "%s: %s is down, dropping %d echo packets\n",
				    __func__, netdev->name, pkts);
		netdev->stats.tx_dropped += pkts;
		वापस 0;
	पूर्ण अन्यथा अगर (!es58x_is_can_state_active(netdev)) अणु
		अगर (net_ratelimit())
			netdev_dbg(netdev,
				   "Bus is off or device is restarting. Ignoring %u echo packets from index %u\n",
				   pkts, rcv_packet_idx);
		/* stats.tx_dropped will be (or was alपढ़ोy)
		 * incremented by
		 * drivers/net/can/net/dev.c:can_flush_echo_skb().
		 */
		वापस 0;
	पूर्ण अन्यथा अगर (num_echo_skb == 0) अणु
		अगर (net_ratelimit())
			netdev_warn(netdev,
				    "Received %u echo packets from index: %u but echo skb queue is empty.\n",
				    pkts, rcv_packet_idx);
		netdev->stats.tx_dropped += pkts;
		वापस 0;
	पूर्ण

	अगर (priv->tx_tail != rcv_packet_idx) अणु
		अगर (es58x_can_get_echo_skb_recovery(netdev, rcv_packet_idx) < 0) अणु
			अगर (net_ratelimit())
				netdev_warn(netdev,
					    "Could not find echo skb for echo packet index: %u\n",
					    rcv_packet_idx);
			वापस 0;
		पूर्ण
	पूर्ण
	अगर (num_echo_skb < pkts) अणु
		पूर्णांक pkts_drop = pkts - num_echo_skb;

		अगर (net_ratelimit())
			netdev_err(netdev,
				   "Received %u echo packets but have only %d echo skb. Dropping %d echo skb\n",
				   pkts, num_echo_skb, pkts_drop);
		netdev->stats.tx_dropped += pkts_drop;
		pkts -= pkts_drop;
	पूर्ण

	क्रम (i = 0; i < pkts; i++) अणु
		अचिन्हित पूर्णांक skb_idx = priv->tx_tail & fअगरo_mask;
		काष्ठा sk_buff *skb = priv->can.echo_skb[skb_idx];
		अचिन्हित पूर्णांक frame_len = 0;

		अगर (skb)
			es58x_set_skb_बारtamp(netdev, skb, tstamps[i]);

		netdev->stats.tx_bytes += can_get_echo_skb(netdev, skb_idx,
							   &frame_len);
		rx_total_frame_len += frame_len;

		priv->tx_tail++;
	पूर्ण

	netdev_completed_queue(netdev, pkts, rx_total_frame_len);
	netdev->stats.tx_packets += pkts;

	priv->err_passive_beक्रमe_rtx_success = 0;
	अगर (!es58x_is_echo_skb_threshold_reached(priv))
		netअगर_wake_queue(netdev);

	वापस 0;
पूर्ण

/**
 * es58x_can_reset_echo_fअगरo() - Reset the echo FIFO.
 * @netdev: CAN network device.
 *
 * The echo_skb array of काष्ठा can_priv will be flushed by
 * drivers/net/can/dev.c:can_flush_echo_skb(). This function resets
 * the parameters of the काष्ठा es58x_priv of our device and reset the
 * queue (c.f. BQL).
 */
अटल व्योम es58x_can_reset_echo_fअगरo(काष्ठा net_device *netdev)
अणु
	काष्ठा es58x_priv *priv = es58x_priv(netdev);

	priv->tx_tail = 0;
	priv->tx_head = 0;
	priv->tx_urb = शून्य;
	priv->err_passive_beक्रमe_rtx_success = 0;
	netdev_reset_queue(netdev);
पूर्ण

/**
 * es58x_flush_pending_tx_msg() - Reset the buffer क्रम transmission messages.
 * @netdev: CAN network device.
 *
 * es58x_start_xmit() will queue up to tx_bulk_max messages in
 * &tx_urb buffer and करो a bulk send of all messages in one single URB
 * (c.f. xmit_more flag). When the device recovers from a bus off
 * state or when the device stops, the tx_urb buffer might still have
 * pending messages in it and thus need to be flushed.
 */
अटल व्योम es58x_flush_pending_tx_msg(काष्ठा net_device *netdev)
अणु
	काष्ठा es58x_priv *priv = es58x_priv(netdev);
	काष्ठा es58x_device *es58x_dev = priv->es58x_dev;

	अगर (priv->tx_urb) अणु
		netdev_warn(netdev, "%s: dropping %d TX messages\n",
			    __func__, priv->tx_can_msg_cnt);
		netdev->stats.tx_dropped += priv->tx_can_msg_cnt;
		जबतक (priv->tx_can_msg_cnt > 0) अणु
			अचिन्हित पूर्णांक frame_len = 0;
			u16 fअगरo_mask = priv->es58x_dev->param->fअगरo_mask;

			priv->tx_head--;
			priv->tx_can_msg_cnt--;
			can_मुक्त_echo_skb(netdev, priv->tx_head & fअगरo_mask,
					  &frame_len);
			netdev_completed_queue(netdev, 1, frame_len);
		पूर्ण
		usb_anchor_urb(priv->tx_urb, &priv->es58x_dev->tx_urbs_idle);
		atomic_inc(&es58x_dev->tx_urbs_idle_cnt);
		usb_मुक्त_urb(priv->tx_urb);
	पूर्ण
	priv->tx_urb = शून्य;
पूर्ण

/**
 * es58x_tx_ack_msg() - Handle acknowledgment messages.
 * @netdev: CAN network device.
 * @tx_मुक्त_entries: Number of मुक्त entries in the device transmit FIFO.
 * @rx_cmd_ret_u32: error code as वापसed by the ES58X device.
 *
 * ES58X sends an acknowledgment message after a transmission request
 * is करोne. This is mandatory क्रम the ES581.4 but is optional (and
 * deactivated in this driver) क्रम the ES58X_FD family.
 *
 * Under normal circumstances, this function should never throw an
 * error message.
 *
 * Return: zero on success, त्रुटि_सं when any error occurs.
 */
पूर्णांक es58x_tx_ack_msg(काष्ठा net_device *netdev, u16 tx_मुक्त_entries,
		     क्रमागत es58x_ret_u32 rx_cmd_ret_u32)
अणु
	काष्ठा es58x_priv *priv = es58x_priv(netdev);

	अगर (tx_मुक्त_entries <= priv->es58x_dev->param->tx_bulk_max) अणु
		अगर (net_ratelimit())
			netdev_err(netdev,
				   "Only %d entries left in device queue, num_echo_skb: %d/%d\n",
				   tx_मुक्त_entries,
				   priv->tx_head - priv->tx_tail,
				   priv->can.echo_skb_max);
		netअगर_stop_queue(netdev);
	पूर्ण

	वापस es58x_rx_cmd_ret_u32(netdev, ES58X_RET_TYPE_TX_MSG,
				    rx_cmd_ret_u32);
पूर्ण

/**
 * es58x_rx_can_msg() - Handle a received a CAN message.
 * @netdev: CAN network device.
 * @बारtamp: Hardware समय stamp (only relevant in rx branches).
 * @data: CAN payload.
 * @can_id: CAN ID.
 * @es58x_flags: Please refer to क्रमागत es58x_flag.
 * @dlc: Data Length Code (raw value).
 *
 * Fill up a CAN skb and post it.
 *
 * This function handles the हाल where the DLC of a classical CAN
 * frame is greater than CAN_MAX_DLEN (c.f. the len8_dlc field of
 * काष्ठा can_frame).
 *
 * Return: zero on success.
 */
पूर्णांक es58x_rx_can_msg(काष्ठा net_device *netdev, u64 बारtamp, स्थिर u8 *data,
		     canid_t can_id, क्रमागत es58x_flag es58x_flags, u8 dlc)
अणु
	काष्ठा canfd_frame *cfd;
	काष्ठा can_frame *ccf;
	काष्ठा sk_buff *skb;
	u8 len;
	bool is_can_fd = !!(es58x_flags & ES58X_FLAG_FD_DATA);

	अगर (dlc > CAN_MAX_RAW_DLC) अणु
		netdev_err(netdev,
			   "%s: DLC is %d but maximum should be %d\n",
			   __func__, dlc, CAN_MAX_RAW_DLC);
		वापस -EMSGSIZE;
	पूर्ण

	अगर (is_can_fd) अणु
		len = can_fd_dlc2len(dlc);
		skb = alloc_canfd_skb(netdev, &cfd);
	पूर्ण अन्यथा अणु
		len = can_cc_dlc2len(dlc);
		skb = alloc_can_skb(netdev, &ccf);
		cfd = (काष्ठा canfd_frame *)ccf;
	पूर्ण
	अगर (!skb) अणु
		netdev->stats.rx_dropped++;
		वापस 0;
	पूर्ण

	cfd->can_id = can_id;
	अगर (es58x_flags & ES58X_FLAG_EFF)
		cfd->can_id |= CAN_EFF_FLAG;
	अगर (is_can_fd) अणु
		cfd->len = len;
		अगर (es58x_flags & ES58X_FLAG_FD_BRS)
			cfd->flags |= CANFD_BRS;
		अगर (es58x_flags & ES58X_FLAG_FD_ESI)
			cfd->flags |= CANFD_ESI;
	पूर्ण अन्यथा अणु
		can_frame_set_cc_len(ccf, dlc, es58x_priv(netdev)->can.ctrlmode);
		अगर (es58x_flags & ES58X_FLAG_RTR) अणु
			ccf->can_id |= CAN_RTR_FLAG;
			len = 0;
		पूर्ण
	पूर्ण
	स_नकल(cfd->data, data, len);
	netdev->stats.rx_packets++;
	netdev->stats.rx_bytes += len;

	es58x_set_skb_बारtamp(netdev, skb, बारtamp);
	netअगर_rx(skb);

	es58x_priv(netdev)->err_passive_beक्रमe_rtx_success = 0;

	वापस 0;
पूर्ण

/**
 * es58x_rx_err_msg() - Handle a received CAN event or error message.
 * @netdev: CAN network device.
 * @error: Error code.
 * @event: Event code.
 * @बारtamp: Timestamp received from a ES58X device.
 *
 * Handle the errors and events received by the ES58X device, create
 * a CAN error skb and post it.
 *
 * In some rare हालs the devices might get stuck alternating between
 * CAN_STATE_ERROR_PASSIVE and CAN_STATE_ERROR_WARNING. To prevent
 * this behavior, we क्रमce a bus off state अगर the device goes in
 * CAN_STATE_ERROR_WARNING क्रम ES58X_MAX_CONSECUTIVE_WARN consecutive
 * बार with no successful transmission or reception in between.
 *
 * Once the device is in bus off state, the only way to restart it is
 * through the drivers/net/can/dev.c:can_restart() function. The
 * device is technically capable to recover by itself under certain
 * circumstances, however, allowing self recovery would create
 * complex race conditions with drivers/net/can/dev.c:can_restart()
 * and thus was not implemented. To activate स्वतःmatic restart, please
 * set the restart-ms parameter (e.g. ip link set can0 type can
 * restart-ms 100).
 *
 * If the bus is really instable, this function would try to send a
 * lot of log messages. Those are rate limited (i.e. you will see
 * messages such as "net_ratelimit: XXX callbacks suppressed" in
 * dmesg).
 *
 * Return: zero on success, त्रुटि_सं when any error occurs.
 */
पूर्णांक es58x_rx_err_msg(काष्ठा net_device *netdev, क्रमागत es58x_err error,
		     क्रमागत es58x_event event, u64 बारtamp)
अणु
	काष्ठा es58x_priv *priv = es58x_priv(netdev);
	काष्ठा can_priv *can = netdev_priv(netdev);
	काष्ठा can_device_stats *can_stats = &can->can_stats;
	काष्ठा can_frame *cf = शून्य;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	अगर (!netअगर_running(netdev)) अणु
		अगर (net_ratelimit())
			netdev_info(netdev, "%s: %s is down, dropping packet\n",
				    __func__, netdev->name);
		netdev->stats.rx_dropped++;
		वापस 0;
	पूर्ण

	अगर (error == ES58X_ERR_OK && event == ES58X_EVENT_OK) अणु
		netdev_err(netdev, "%s: Both error and event are zero\n",
			   __func__);
		वापस -EINVAL;
	पूर्ण

	skb = alloc_can_err_skb(netdev, &cf);

	चयन (error) अणु
	हाल ES58X_ERR_OK:	/* 0: No error */
		अवरोध;

	हाल ES58X_ERR_PROT_STUFF:
		अगर (net_ratelimit())
			netdev_dbg(netdev, "Error BITSTUFF\n");
		अगर (cf)
			cf->data[2] |= CAN_ERR_PROT_STUFF;
		अवरोध;

	हाल ES58X_ERR_PROT_FORM:
		अगर (net_ratelimit())
			netdev_dbg(netdev, "Error FORMAT\n");
		अगर (cf)
			cf->data[2] |= CAN_ERR_PROT_FORM;
		अवरोध;

	हाल ES58X_ERR_ACK:
		अगर (net_ratelimit())
			netdev_dbg(netdev, "Error ACK\n");
		अगर (cf)
			cf->can_id |= CAN_ERR_ACK;
		अवरोध;

	हाल ES58X_ERR_PROT_BIT:
		अगर (net_ratelimit())
			netdev_dbg(netdev, "Error BIT\n");
		अगर (cf)
			cf->data[2] |= CAN_ERR_PROT_BIT;
		अवरोध;

	हाल ES58X_ERR_PROT_CRC:
		अगर (net_ratelimit())
			netdev_dbg(netdev, "Error CRC\n");
		अगर (cf)
			cf->data[3] |= CAN_ERR_PROT_LOC_CRC_SEQ;
		अवरोध;

	हाल ES58X_ERR_PROT_BIT1:
		अगर (net_ratelimit())
			netdev_dbg(netdev,
				   "Error: expected a recessive bit but monitored a dominant one\n");
		अगर (cf)
			cf->data[2] |= CAN_ERR_PROT_BIT1;
		अवरोध;

	हाल ES58X_ERR_PROT_BIT0:
		अगर (net_ratelimit())
			netdev_dbg(netdev,
				   "Error expected a dominant bit but monitored a recessive one\n");
		अगर (cf)
			cf->data[2] |= CAN_ERR_PROT_BIT0;
		अवरोध;

	हाल ES58X_ERR_PROT_OVERLOAD:
		अगर (net_ratelimit())
			netdev_dbg(netdev, "Error OVERLOAD\n");
		अगर (cf)
			cf->data[2] |= CAN_ERR_PROT_OVERLOAD;
		अवरोध;

	हाल ES58X_ERR_PROT_UNSPEC:
		अगर (net_ratelimit())
			netdev_dbg(netdev, "Unspecified error\n");
		अगर (cf)
			cf->can_id |= CAN_ERR_PROT;
		अवरोध;

	शेष:
		अगर (net_ratelimit())
			netdev_err(netdev,
				   "%s: Unspecified error code 0x%04X\n",
				   __func__, (पूर्णांक)error);
		अगर (cf)
			cf->can_id |= CAN_ERR_PROT;
		अवरोध;
	पूर्ण

	चयन (event) अणु
	हाल ES58X_EVENT_OK:	/* 0: No event */
		अवरोध;

	हाल ES58X_EVENT_CRTL_ACTIVE:
		अगर (can->state == CAN_STATE_BUS_OFF) अणु
			netdev_err(netdev,
				   "%s: state transition: BUS OFF -> ACTIVE\n",
				   __func__);
		पूर्ण
		अगर (net_ratelimit())
			netdev_dbg(netdev, "Event CAN BUS ACTIVE\n");
		अगर (cf)
			cf->data[1] |= CAN_ERR_CRTL_ACTIVE;
		can->state = CAN_STATE_ERROR_ACTIVE;
		अवरोध;

	हाल ES58X_EVENT_CRTL_PASSIVE:
		अगर (net_ratelimit())
			netdev_dbg(netdev, "Event CAN BUS PASSIVE\n");
		/* Either TX or RX error count reached passive state
		 * but we करो not know which. Setting both flags by
		 * शेष.
		 */
		अगर (cf) अणु
			cf->data[1] |= CAN_ERR_CRTL_RX_PASSIVE;
			cf->data[1] |= CAN_ERR_CRTL_TX_PASSIVE;
		पूर्ण
		अगर (can->state < CAN_STATE_BUS_OFF)
			can->state = CAN_STATE_ERROR_PASSIVE;
		can_stats->error_passive++;
		अगर (priv->err_passive_beक्रमe_rtx_success < U8_MAX)
			priv->err_passive_beक्रमe_rtx_success++;
		अवरोध;

	हाल ES58X_EVENT_CRTL_WARNING:
		अगर (net_ratelimit())
			netdev_dbg(netdev, "Event CAN BUS WARNING\n");
		/* Either TX or RX error count reached warning state
		 * but we करो not know which. Setting both flags by
		 * शेष.
		 */
		अगर (cf) अणु
			cf->data[1] |= CAN_ERR_CRTL_RX_WARNING;
			cf->data[1] |= CAN_ERR_CRTL_TX_WARNING;
		पूर्ण
		अगर (can->state < CAN_STATE_BUS_OFF)
			can->state = CAN_STATE_ERROR_WARNING;
		can_stats->error_warning++;
		अवरोध;

	हाल ES58X_EVENT_BUSOFF:
		अगर (net_ratelimit())
			netdev_dbg(netdev, "Event CAN BUS OFF\n");
		अगर (cf)
			cf->can_id |= CAN_ERR_BUSOFF;
		can_stats->bus_off++;
		netअगर_stop_queue(netdev);
		अगर (can->state != CAN_STATE_BUS_OFF) अणु
			can->state = CAN_STATE_BUS_OFF;
			can_bus_off(netdev);
			ret = can->करो_set_mode(netdev, CAN_MODE_STOP);
			अगर (ret)
				वापस ret;
		पूर्ण
		अवरोध;

	हाल ES58X_EVENT_SINGLE_WIRE:
		अगर (net_ratelimit())
			netdev_warn(netdev,
				    "Lost connection on either CAN high or CAN low\n");
		/* Lost connection on either CAN high or CAN
		 * low. Setting both flags by शेष.
		 */
		अगर (cf) अणु
			cf->data[4] |= CAN_ERR_TRX_CANH_NO_WIRE;
			cf->data[4] |= CAN_ERR_TRX_CANL_NO_WIRE;
		पूर्ण
		अवरोध;

	शेष:
		अगर (net_ratelimit())
			netdev_err(netdev,
				   "%s: Unspecified event code 0x%04X\n",
				   __func__, (पूर्णांक)event);
		अगर (cf)
			cf->can_id |= CAN_ERR_CRTL;
		अवरोध;
	पूर्ण

	/* driver/net/can/dev.c:can_restart() takes in account error
	 * messages in the RX stats. Doing the same here क्रम
	 * consistency.
	 */
	netdev->stats.rx_packets++;
	netdev->stats.rx_bytes += CAN_ERR_DLC;

	अगर (cf) अणु
		अगर (cf->data[1])
			cf->can_id |= CAN_ERR_CRTL;
		अगर (cf->data[2] || cf->data[3]) अणु
			cf->can_id |= CAN_ERR_PROT;
			can_stats->bus_error++;
		पूर्ण
		अगर (cf->data[4])
			cf->can_id |= CAN_ERR_TRX;

		es58x_set_skb_बारtamp(netdev, skb, बारtamp);
		netअगर_rx(skb);
	पूर्ण

	अगर ((event & ES58X_EVENT_CRTL_PASSIVE) &&
	    priv->err_passive_beक्रमe_rtx_success == ES58X_CONSECUTIVE_ERR_PASSIVE_MAX) अणु
		netdev_info(netdev,
			    "Got %d consecutive warning events with no successful RX or TX. Forcing bus-off\n",
			    priv->err_passive_beक्रमe_rtx_success);
		वापस es58x_rx_err_msg(netdev, ES58X_ERR_OK,
					ES58X_EVENT_BUSOFF, बारtamp);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * es58x_cmd_ret_desc() - Convert a command type to a string.
 * @cmd_ret_type: Type of the command which triggered the वापस code.
 *
 * The final line (वापस "<unknown>") should not be reached. If this
 * is the हाल, there is an implementation bug.
 *
 * Return: a पढ़ोable description of the @cmd_ret_type.
 */
अटल स्थिर अक्षर *es58x_cmd_ret_desc(क्रमागत es58x_ret_type cmd_ret_type)
अणु
	चयन (cmd_ret_type) अणु
	हाल ES58X_RET_TYPE_SET_BITTIMING:
		वापस "Set bittiming";
	हाल ES58X_RET_TYPE_ENABLE_CHANNEL:
		वापस "Enable channel";
	हाल ES58X_RET_TYPE_DISABLE_CHANNEL:
		वापस "Disable channel";
	हाल ES58X_RET_TYPE_TX_MSG:
		वापस "Transmit message";
	हाल ES58X_RET_TYPE_RESET_RX:
		वापस "Reset RX";
	हाल ES58X_RET_TYPE_RESET_TX:
		वापस "Reset TX";
	हाल ES58X_RET_TYPE_DEVICE_ERR:
		वापस "Device error";
	पूर्ण

	वापस "<unknown>";
पूर्ण;

/**
 * es58x_rx_cmd_ret_u8() - Handle the command's वापस code received
 *	from the ES58X device.
 * @dev: Device, only used क्रम the dev_XXX() prपूर्णांक functions.
 * @cmd_ret_type: Type of the command which triggered the वापस code.
 * @rx_cmd_ret_u8: Command error code as वापसed by the ES58X device.
 *
 * Handles the 8 bits command वापस code. Those are specअगरic to the
 * ES581.4 device. The वापस value will eventually be used by
 * es58x_handle_urb_cmd() function which will take proper actions in
 * हाल of critical issues such and memory errors or bad CRC values.
 *
 * In contrast with es58x_rx_cmd_ret_u32(), the network device is
 * unknown.
 *
 * Return: zero on success, वापस त्रुटि_सं when any error occurs.
 */
पूर्णांक es58x_rx_cmd_ret_u8(काष्ठा device *dev,
			क्रमागत es58x_ret_type cmd_ret_type,
			क्रमागत es58x_ret_u8 rx_cmd_ret_u8)
अणु
	स्थिर अक्षर *ret_desc = es58x_cmd_ret_desc(cmd_ret_type);

	चयन (rx_cmd_ret_u8) अणु
	हाल ES58X_RET_U8_OK:
		dev_dbg_ratelimited(dev, "%s: OK\n", ret_desc);
		वापस 0;

	हाल ES58X_RET_U8_ERR_UNSPECIFIED_FAILURE:
		dev_err(dev, "%s: unspecified failure\n", ret_desc);
		वापस -EBADMSG;

	हाल ES58X_RET_U8_ERR_NO_MEM:
		dev_err(dev, "%s: device ran out of memory\n", ret_desc);
		वापस -ENOMEM;

	हाल ES58X_RET_U8_ERR_BAD_CRC:
		dev_err(dev, "%s: CRC of previous command is incorrect\n",
			ret_desc);
		वापस -EIO;

	शेष:
		dev_err(dev, "%s: returned unknown value: 0x%02X\n",
			ret_desc, rx_cmd_ret_u8);
		वापस -EBADMSG;
	पूर्ण
पूर्ण

/**
 * es58x_rx_cmd_ret_u32() - Handle the command वापस code received
 *	from the ES58X device.
 * @netdev: CAN network device.
 * @cmd_ret_type: Type of the command which triggered the वापस code.
 * @rx_cmd_ret_u32: error code as वापसed by the ES58X device.
 *
 * Handles the 32 bits command वापस code. The वापस value will
 * eventually be used by es58x_handle_urb_cmd() function which will
 * take proper actions in हाल of critical issues such and memory
 * errors or bad CRC values.
 *
 * Return: zero on success, त्रुटि_सं when any error occurs.
 */
पूर्णांक es58x_rx_cmd_ret_u32(काष्ठा net_device *netdev,
			 क्रमागत es58x_ret_type cmd_ret_type,
			 क्रमागत es58x_ret_u32 rx_cmd_ret_u32)
अणु
	काष्ठा es58x_priv *priv = es58x_priv(netdev);
	स्थिर काष्ठा es58x_चालकs *ops = priv->es58x_dev->ops;
	स्थिर अक्षर *ret_desc = es58x_cmd_ret_desc(cmd_ret_type);

	चयन (rx_cmd_ret_u32) अणु
	हाल ES58X_RET_U32_OK:
		चयन (cmd_ret_type) अणु
		हाल ES58X_RET_TYPE_ENABLE_CHANNEL:
			es58x_can_reset_echo_fअगरo(netdev);
			priv->can.state = CAN_STATE_ERROR_ACTIVE;
			netअगर_wake_queue(netdev);
			netdev_info(netdev,
				    "%s: %s (Serial Number %s): CAN%d channel becomes ready\n",
				    ret_desc, priv->es58x_dev->udev->product,
				    priv->es58x_dev->udev->serial,
				    priv->channel_idx + 1);
			अवरोध;

		हाल ES58X_RET_TYPE_TX_MSG:
			अगर (IS_ENABLED(CONFIG_VERBOSE_DEBUG) && net_ratelimit())
				netdev_vdbg(netdev, "%s: OK\n", ret_desc);
			अवरोध;

		शेष:
			netdev_dbg(netdev, "%s: OK\n", ret_desc);
			अवरोध;
		पूर्ण
		वापस 0;

	हाल ES58X_RET_U32_ERR_UNSPECIFIED_FAILURE:
		अगर (cmd_ret_type == ES58X_RET_TYPE_ENABLE_CHANNEL) अणु
			पूर्णांक ret;

			netdev_warn(netdev,
				    "%s: channel is already opened, closing and re-opening it to reflect new configuration\n",
				    ret_desc);
			ret = ops->disable_channel(es58x_priv(netdev));
			अगर (ret)
				वापस ret;
			वापस ops->enable_channel(es58x_priv(netdev));
		पूर्ण
		अगर (cmd_ret_type == ES58X_RET_TYPE_DISABLE_CHANNEL) अणु
			netdev_info(netdev,
				    "%s: channel is already closed\n", ret_desc);
			वापस 0;
		पूर्ण
		netdev_err(netdev,
			   "%s: unspecified failure\n", ret_desc);
		वापस -EBADMSG;

	हाल ES58X_RET_U32_ERR_NO_MEM:
		netdev_err(netdev, "%s: device ran out of memory\n", ret_desc);
		वापस -ENOMEM;

	हाल ES58X_RET_U32_WARN_PARAM_ADJUSTED:
		netdev_warn(netdev,
			    "%s: some incompatible parameters have been adjusted\n",
			    ret_desc);
		वापस 0;

	हाल ES58X_RET_U32_WARN_TX_MAYBE_REORDER:
		netdev_warn(netdev,
			    "%s: TX messages might have been reordered\n",
			    ret_desc);
		वापस 0;

	हाल ES58X_RET_U32_ERR_TIMEDOUT:
		netdev_err(netdev, "%s: command timed out\n", ret_desc);
		वापस -ETIMEDOUT;

	हाल ES58X_RET_U32_ERR_FIFO_FULL:
		netdev_warn(netdev, "%s: fifo is full\n", ret_desc);
		वापस 0;

	हाल ES58X_RET_U32_ERR_BAD_CONFIG:
		netdev_err(netdev, "%s: bad configuration\n", ret_desc);
		वापस -EINVAL;

	हाल ES58X_RET_U32_ERR_NO_RESOURCE:
		netdev_err(netdev, "%s: no resource available\n", ret_desc);
		वापस -EBUSY;

	शेष:
		netdev_err(netdev, "%s returned unknown value: 0x%08X\n",
			   ret_desc, rx_cmd_ret_u32);
		वापस -EBADMSG;
	पूर्ण
पूर्ण

/**
 * es58x_increment_rx_errors() - Increment the network devices' error
 *	count.
 * @es58x_dev: ES58X device.
 *
 * If an error occurs on the early stages on receiving an URB command,
 * we might not be able to figure out on which network device the
 * error occurred. In such हाल, we arbitrarily increment the error
 * count of all the network devices attached to our ES58X device.
 */
अटल व्योम es58x_increment_rx_errors(काष्ठा es58x_device *es58x_dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < es58x_dev->num_can_ch; i++)
		अगर (es58x_dev->netdev[i])
			es58x_dev->netdev[i]->stats.rx_errors++;
पूर्ण

/**
 * es58x_handle_urb_cmd() - Handle the URB command
 * @es58x_dev: ES58X device.
 * @urb_cmd: The URB command received from the ES58X device, might not
 *	be aligned.
 *
 * Sends the URB command to the device specअगरic function. Manages the
 * errors thrown back by those functions.
 */
अटल व्योम es58x_handle_urb_cmd(काष्ठा es58x_device *es58x_dev,
				 स्थिर जोड़ es58x_urb_cmd *urb_cmd)
अणु
	स्थिर काष्ठा es58x_चालकs *ops = es58x_dev->ops;
	माप_प्रकार cmd_len;
	पूर्णांक i, ret;

	ret = ops->handle_urb_cmd(es58x_dev, urb_cmd);
	चयन (ret) अणु
	हाल 0:		/* OK */
		वापस;

	हाल -ENODEV:
		dev_err_ratelimited(es58x_dev->dev, "Device is not ready\n");
		अवरोध;

	हाल -EINVAL:
	हाल -EMSGSIZE:
	हाल -EBADRQC:
	हाल -EBADMSG:
	हाल -ECHRNG:
	हाल -ETIMEDOUT:
		cmd_len = es58x_get_urb_cmd_len(es58x_dev,
						ops->get_msg_len(urb_cmd));
		dev_err(es58x_dev->dev,
			"ops->handle_urb_cmd() returned error %pe",
			ERR_PTR(ret));
		es58x_prपूर्णांक_hex_dump(urb_cmd, cmd_len);
		अवरोध;

	हाल -EFAULT:
	हाल -ENOMEM:
	हाल -EIO:
	शेष:
		dev_crit(es58x_dev->dev,
			 "ops->handle_urb_cmd() returned error %pe, detaching all network devices\n",
			 ERR_PTR(ret));
		क्रम (i = 0; i < es58x_dev->num_can_ch; i++)
			अगर (es58x_dev->netdev[i])
				netअगर_device_detach(es58x_dev->netdev[i]);
		अगर (es58x_dev->ops->reset_device)
			es58x_dev->ops->reset_device(es58x_dev);
		अवरोध;
	पूर्ण

	/* Because the urb command could not fully be parsed,
	 * channel_id is not confirmed. Incrementing rx_errors count
	 * of all channels.
	 */
	es58x_increment_rx_errors(es58x_dev);
पूर्ण

/**
 * es58x_check_rx_urb() - Check the length and क्रमmat of the URB command.
 * @es58x_dev: ES58X device.
 * @urb_cmd: The URB command received from the ES58X device, might not
 *	be aligned.
 * @urb_actual_len: The actual length of the URB command.
 *
 * Check अगर the first message of the received urb is valid, that is to
 * say that both the header and the length are coherent.
 *
 * Return:
 * the length of the first message of the URB on success.
 *
 * -ENODATA अगर the URB command is incomplete (in which हाल, the URB
 * command should be buffered and combined with the next URB to try to
 * reस्थिरitute the URB command).
 *
 * -EOVERFLOW अगर the length is bigger than the maximum expected one.
 *
 * -EBADRQC अगर the start of frame करोes not match the expected value.
 */
अटल चिन्हित पूर्णांक es58x_check_rx_urb(काष्ठा es58x_device *es58x_dev,
				     स्थिर जोड़ es58x_urb_cmd *urb_cmd,
				     u32 urb_actual_len)
अणु
	स्थिर काष्ठा device *dev = es58x_dev->dev;
	स्थिर काष्ठा es58x_parameters *param = es58x_dev->param;
	u16 sof, msg_len;
	चिन्हित पूर्णांक urb_cmd_len, ret;

	अगर (urb_actual_len < param->urb_cmd_header_len) अणु
		dev_vdbg(dev,
			 "%s: Received %d bytes [%*ph]: header incomplete\n",
			 __func__, urb_actual_len, urb_actual_len,
			 urb_cmd->raw_cmd);
		वापस -ENODATA;
	पूर्ण

	sof = get_unaligned_le16(&urb_cmd->sof);
	अगर (sof != param->rx_start_of_frame) अणु
		dev_err_ratelimited(es58x_dev->dev,
				    "%s: Expected sequence 0x%04X for start of frame but got 0x%04X.\n",
				    __func__, param->rx_start_of_frame, sof);
		वापस -EBADRQC;
	पूर्ण

	msg_len = es58x_dev->ops->get_msg_len(urb_cmd);
	urb_cmd_len = es58x_get_urb_cmd_len(es58x_dev, msg_len);
	अगर (urb_cmd_len > param->rx_urb_cmd_max_len) अणु
		dev_err_ratelimited(es58x_dev->dev,
				    "%s: Biggest expected size for rx urb_cmd is %u but receive a command of size %d\n",
				    __func__,
				    param->rx_urb_cmd_max_len, urb_cmd_len);
		वापस -EOVERFLOW;
	पूर्ण अन्यथा अगर (urb_actual_len < urb_cmd_len) अणु
		dev_vdbg(dev, "%s: Received %02d/%02d bytes\n",
			 __func__, urb_actual_len, urb_cmd_len);
		वापस -ENODATA;
	पूर्ण

	ret = es58x_check_crc(es58x_dev, urb_cmd, urb_cmd_len);
	अगर (ret)
		वापस ret;

	वापस urb_cmd_len;
पूर्ण

/**
 * es58x_copy_to_cmd_buf() - Copy an array to the URB command buffer.
 * @es58x_dev: ES58X device.
 * @raw_cmd: the buffer we want to copy.
 * @raw_cmd_len: length of @raw_cmd.
 *
 * Concatenates @raw_cmd_len bytes of @raw_cmd to the end of the URB
 * command buffer.
 *
 * Return: zero on success, -EMSGSIZE अगर not enough space is available
 * to करो the copy.
 */
अटल पूर्णांक es58x_copy_to_cmd_buf(काष्ठा es58x_device *es58x_dev,
				 u8 *raw_cmd, पूर्णांक raw_cmd_len)
अणु
	अगर (es58x_dev->rx_cmd_buf_len + raw_cmd_len >
	    es58x_dev->param->rx_urb_cmd_max_len)
		वापस -EMSGSIZE;

	स_नकल(&es58x_dev->rx_cmd_buf.raw_cmd[es58x_dev->rx_cmd_buf_len],
	       raw_cmd, raw_cmd_len);
	es58x_dev->rx_cmd_buf_len += raw_cmd_len;

	वापस 0;
पूर्ण

/**
 * es58x_split_urb_try_recovery() - Try to recover bad URB sequences.
 * @es58x_dev: ES58X device.
 * @raw_cmd: poपूर्णांकer to the buffer we want to copy.
 * @raw_cmd_len: length of @raw_cmd.
 *
 * Under some rare conditions, we might get incorrect URBs from the
 * device. From our observations, one of the valid URB माला_लो replaced
 * by one from the past. The full root cause is not identअगरied.
 *
 * This function looks क्रम the next start of frame in the urb buffer
 * in order to try to recover.
 *
 * Such behavior was not observed on the devices of the ES58X FD
 * family and only seems to impact the ES581.4.
 *
 * Return: the number of bytes dropped on success, -EBADMSG अगर recovery failed.
 */
अटल पूर्णांक es58x_split_urb_try_recovery(काष्ठा es58x_device *es58x_dev,
					u8 *raw_cmd, माप_प्रकार raw_cmd_len)
अणु
	जोड़ es58x_urb_cmd *urb_cmd;
	चिन्हित पूर्णांक urb_cmd_len;
	u16 sof;
	पूर्णांक dropped_bytes = 0;

	es58x_increment_rx_errors(es58x_dev);

	जबतक (raw_cmd_len > माप(sof)) अणु
		urb_cmd = (जोड़ es58x_urb_cmd *)raw_cmd;
		sof = get_unaligned_le16(&urb_cmd->sof);

		अगर (sof == es58x_dev->param->rx_start_of_frame) अणु
			urb_cmd_len = es58x_check_rx_urb(es58x_dev,
							 urb_cmd, raw_cmd_len);
			अगर ((urb_cmd_len == -ENODATA) || urb_cmd_len > 0) अणु
				dev_info_ratelimited(es58x_dev->dev,
						     "Recovery successful! Dropped %d bytes (urb_cmd_len: %d)\n",
						     dropped_bytes,
						     urb_cmd_len);
				वापस dropped_bytes;
			पूर्ण
		पूर्ण
		raw_cmd++;
		raw_cmd_len--;
		dropped_bytes++;
	पूर्ण

	dev_warn_ratelimited(es58x_dev->dev, "%s: Recovery failed\n", __func__);
	वापस -EBADMSG;
पूर्ण

/**
 * es58x_handle_incomplete_cmd() - Reस्थिरitute an URB command from
 *	dअगरferent URB pieces.
 * @es58x_dev: ES58X device.
 * @urb: last urb buffer received.
 *
 * The device might split the URB commands in an arbitrary amount of
 * pieces. This function concatenates those in an URB buffer until a
 * full URB command is reस्थिरituted and consume it.
 *
 * Return:
 * number of bytes consumed from @urb अगर successful.
 *
 * -ENODATA अगर the URB command is still incomplete.
 *
 * -EBADMSG अगर the URB command is incorrect.
 */
अटल चिन्हित पूर्णांक es58x_handle_incomplete_cmd(काष्ठा es58x_device *es58x_dev,
					      काष्ठा urb *urb)
अणु
	माप_प्रकार cpy_len;
	चिन्हित पूर्णांक urb_cmd_len, पंचांगp_cmd_buf_len, ret;

	पंचांगp_cmd_buf_len = es58x_dev->rx_cmd_buf_len;
	cpy_len = min_t(पूर्णांक, es58x_dev->param->rx_urb_cmd_max_len -
			es58x_dev->rx_cmd_buf_len, urb->actual_length);
	ret = es58x_copy_to_cmd_buf(es58x_dev, urb->transfer_buffer, cpy_len);
	अगर (ret < 0)
		वापस ret;

	urb_cmd_len = es58x_check_rx_urb(es58x_dev, &es58x_dev->rx_cmd_buf,
					 es58x_dev->rx_cmd_buf_len);
	अगर (urb_cmd_len == -ENODATA) अणु
		वापस -ENODATA;
	पूर्ण अन्यथा अगर (urb_cmd_len < 0) अणु
		dev_err_ratelimited(es58x_dev->dev,
				    "Could not reconstitute incomplete command from previous URB, dropping %d bytes\n",
				    पंचांगp_cmd_buf_len + urb->actual_length);
		dev_err_ratelimited(es58x_dev->dev,
				    "Error code: %pe, es58x_dev->rx_cmd_buf_len: %d, urb->actual_length: %u\n",
				    ERR_PTR(urb_cmd_len),
				    पंचांगp_cmd_buf_len, urb->actual_length);
		es58x_prपूर्णांक_hex_dump(&es58x_dev->rx_cmd_buf, पंचांगp_cmd_buf_len);
		es58x_prपूर्णांक_hex_dump(urb->transfer_buffer, urb->actual_length);
		वापस urb->actual_length;
	पूर्ण

	es58x_handle_urb_cmd(es58x_dev, &es58x_dev->rx_cmd_buf);
	वापस urb_cmd_len - पंचांगp_cmd_buf_len;	/* consumed length */
पूर्ण

/**
 * es58x_split_urb() - Cut the received URB in inभागidual URB commands.
 * @es58x_dev: ES58X device.
 * @urb: last urb buffer received.
 *
 * The device might send urb in bulk क्रमmat (i.e. several URB commands
 * concatenated together). This function will split all the commands
 * contained in the urb.
 *
 * Return:
 * number of bytes consumed from @urb अगर successful.
 *
 * -ENODATA अगर the URB command is incomplete.
 *
 * -EBADMSG अगर the URB command is incorrect.
 */
अटल चिन्हित पूर्णांक es58x_split_urb(काष्ठा es58x_device *es58x_dev,
				  काष्ठा urb *urb)
अणु
	जोड़ es58x_urb_cmd *urb_cmd;
	u8 *raw_cmd = urb->transfer_buffer;
	s32 raw_cmd_len = urb->actual_length;
	पूर्णांक ret;

	अगर (es58x_dev->rx_cmd_buf_len != 0) अणु
		ret = es58x_handle_incomplete_cmd(es58x_dev, urb);
		अगर (ret != -ENODATA)
			es58x_dev->rx_cmd_buf_len = 0;
		अगर (ret < 0)
			वापस ret;

		raw_cmd += ret;
		raw_cmd_len -= ret;
	पूर्ण

	जबतक (raw_cmd_len > 0) अणु
		अगर (raw_cmd[0] == ES58X_HEARTBEAT) अणु
			raw_cmd++;
			raw_cmd_len--;
			जारी;
		पूर्ण
		urb_cmd = (जोड़ es58x_urb_cmd *)raw_cmd;
		ret = es58x_check_rx_urb(es58x_dev, urb_cmd, raw_cmd_len);
		अगर (ret > 0) अणु
			es58x_handle_urb_cmd(es58x_dev, urb_cmd);
		पूर्ण अन्यथा अगर (ret == -ENODATA) अणु
			es58x_copy_to_cmd_buf(es58x_dev, raw_cmd, raw_cmd_len);
			वापस -ENODATA;
		पूर्ण अन्यथा अगर (ret < 0) अणु
			ret = es58x_split_urb_try_recovery(es58x_dev, raw_cmd,
							   raw_cmd_len);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
		raw_cmd += ret;
		raw_cmd_len -= ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * es58x_पढ़ो_bulk_callback() - Callback क्रम पढ़ोing data from device.
 * @urb: last urb buffer received.
 *
 * This function माला_लो eventually called each समय an URB is received
 * from the ES58X device.
 *
 * Checks urb status, calls पढ़ो function and resubmits urb पढ़ो
 * operation.
 */
अटल व्योम es58x_पढ़ो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा es58x_device *es58x_dev = urb->context;
	स्थिर काष्ठा device *dev = es58x_dev->dev;
	पूर्णांक i, ret;

	चयन (urb->status) अणु
	हाल 0:		/* success */
		अवरोध;

	हाल -EOVERFLOW:
		dev_err_ratelimited(dev, "%s: error %pe\n",
				    __func__, ERR_PTR(urb->status));
		es58x_prपूर्णांक_hex_dump_debug(urb->transfer_buffer,
					   urb->transfer_buffer_length);
		जाओ resubmit_urb;

	हाल -EPROTO:
		dev_warn_ratelimited(dev, "%s: error %pe. Device unplugged?\n",
				     __func__, ERR_PTR(urb->status));
		जाओ मुक्त_urb;

	हाल -ENOENT:
	हाल -EPIPE:
		dev_err_ratelimited(dev, "%s: error %pe\n",
				    __func__, ERR_PTR(urb->status));
		जाओ मुक्त_urb;

	हाल -ESHUTDOWN:
		dev_dbg_ratelimited(dev, "%s: error %pe\n",
				    __func__, ERR_PTR(urb->status));
		जाओ मुक्त_urb;

	शेष:
		dev_err_ratelimited(dev, "%s: error %pe\n",
				    __func__, ERR_PTR(urb->status));
		जाओ resubmit_urb;
	पूर्ण

	ret = es58x_split_urb(es58x_dev, urb);
	अगर ((ret != -ENODATA) && ret < 0) अणु
		dev_err(es58x_dev->dev, "es58x_split_urb() returned error %pe",
			ERR_PTR(ret));
		es58x_prपूर्णांक_hex_dump_debug(urb->transfer_buffer,
					   urb->actual_length);

		/* Because the urb command could not be parsed,
		 * channel_id is not confirmed. Incrementing rx_errors
		 * count of all channels.
		 */
		es58x_increment_rx_errors(es58x_dev);
	पूर्ण

 resubmit_urb:
	usb_fill_bulk_urb(urb, es58x_dev->udev, es58x_dev->rx_pipe,
			  urb->transfer_buffer, urb->transfer_buffer_length,
			  es58x_पढ़ो_bulk_callback, es58x_dev);

	ret = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (ret == -ENODEV) अणु
		क्रम (i = 0; i < es58x_dev->num_can_ch; i++)
			अगर (es58x_dev->netdev[i])
				netअगर_device_detach(es58x_dev->netdev[i]);
	पूर्ण अन्यथा अगर (ret)
		dev_err_ratelimited(dev,
				    "Failed resubmitting read bulk urb: %pe\n",
				    ERR_PTR(ret));
	वापस;

 मुक्त_urb:
	usb_मुक्त_coherent(urb->dev, urb->transfer_buffer_length,
			  urb->transfer_buffer, urb->transfer_dma);
पूर्ण

/**
 * es58x_ग_लिखो_bulk_callback() - Callback after writing data to the device.
 * @urb: urb buffer which was previously submitted.
 *
 * This function माला_लो eventually called each समय an URB was sent to
 * the ES58X device.
 *
 * Puts the @urb back to the urbs idle anchor and tries to restart the
 * network queue.
 */
अटल व्योम es58x_ग_लिखो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा net_device *netdev = urb->context;
	काष्ठा es58x_device *es58x_dev = es58x_priv(netdev)->es58x_dev;

	चयन (urb->status) अणु
	हाल 0:		/* success */
		अवरोध;

	हाल -EOVERFLOW:
		अगर (net_ratelimit())
			netdev_err(netdev, "%s: error %pe\n",
				   __func__, ERR_PTR(urb->status));
		es58x_prपूर्णांक_hex_dump(urb->transfer_buffer,
				     urb->transfer_buffer_length);
		अवरोध;

	हाल -ENOENT:
		अगर (net_ratelimit())
			netdev_dbg(netdev, "%s: error %pe\n",
				   __func__, ERR_PTR(urb->status));
		usb_मुक्त_coherent(urb->dev,
				  es58x_dev->param->tx_urb_cmd_max_len,
				  urb->transfer_buffer, urb->transfer_dma);
		वापस;

	शेष:
		अगर (net_ratelimit())
			netdev_info(netdev, "%s: error %pe\n",
				    __func__, ERR_PTR(urb->status));
		अवरोध;
	पूर्ण

	usb_anchor_urb(urb, &es58x_dev->tx_urbs_idle);
	atomic_inc(&es58x_dev->tx_urbs_idle_cnt);
पूर्ण

/**
 * es58x_alloc_urb() - Allocate memory क्रम an URB and its transfer
 *	buffer.
 * @es58x_dev: ES58X device.
 * @urb: URB to be allocated.
 * @buf: used to वापस DMA address of buffer.
 * @buf_len: requested buffer size.
 * @mem_flags: affect whether allocation may block.
 *
 * Allocates an URB and its @transfer_buffer and set its @transfer_dma
 * address.
 *
 * This function is used at start-up to allocate all RX URBs at once
 * and during run समय क्रम TX URBs.
 *
 * Return: zero on success, -ENOMEM अगर no memory is available.
 */
अटल पूर्णांक es58x_alloc_urb(काष्ठा es58x_device *es58x_dev, काष्ठा urb **urb,
			   u8 **buf, माप_प्रकार buf_len, gfp_t mem_flags)
अणु
	*urb = usb_alloc_urb(0, mem_flags);
	अगर (!*urb) अणु
		dev_err(es58x_dev->dev, "No memory left for URBs\n");
		वापस -ENOMEM;
	पूर्ण

	*buf = usb_alloc_coherent(es58x_dev->udev, buf_len,
				  mem_flags, &(*urb)->transfer_dma);
	अगर (!*buf) अणु
		dev_err(es58x_dev->dev, "No memory left for USB buffer\n");
		usb_मुक्त_urb(*urb);
		वापस -ENOMEM;
	पूर्ण

	(*urb)->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	वापस 0;
पूर्ण

/**
 * es58x_get_tx_urb() - Get an URB क्रम transmission.
 * @es58x_dev: ES58X device.
 *
 * Gets an URB from the idle urbs anchor or allocate a new one अगर the
 * anchor is empty.
 *
 * If there are more than ES58X_TX_URBS_MAX in the idle anchor, करो
 * some garbage collection. The garbage collection is करोne here
 * instead of within es58x_ग_लिखो_bulk_callback() because
 * usb_मुक्त_coherent() should not be used in IRQ context:
 * c.f. WARN_ON(irqs_disabled()) in dma_मुक्त_attrs().
 *
 * Return: a poपूर्णांकer to an URB on success, शून्य अगर no memory is
 * available.
 */
अटल काष्ठा urb *es58x_get_tx_urb(काष्ठा es58x_device *es58x_dev)
अणु
	atomic_t *idle_cnt = &es58x_dev->tx_urbs_idle_cnt;
	काष्ठा urb *urb = usb_get_from_anchor(&es58x_dev->tx_urbs_idle);

	अगर (!urb) अणु
		माप_प्रकार tx_buf_len;
		u8 *buf;

		tx_buf_len = es58x_dev->param->tx_urb_cmd_max_len;
		अगर (es58x_alloc_urb(es58x_dev, &urb, &buf, tx_buf_len,
				    GFP_ATOMIC))
			वापस शून्य;

		usb_fill_bulk_urb(urb, es58x_dev->udev, es58x_dev->tx_pipe,
				  buf, tx_buf_len, शून्य, शून्य);
		वापस urb;
	पूर्ण

	जबतक (atomic_dec_वापस(idle_cnt) > ES58X_TX_URBS_MAX) अणु
		/* Garbage collector */
		काष्ठा urb *पंचांगp = usb_get_from_anchor(&es58x_dev->tx_urbs_idle);

		अगर (!पंचांगp)
			अवरोध;
		usb_मुक्त_coherent(पंचांगp->dev,
				  es58x_dev->param->tx_urb_cmd_max_len,
				  पंचांगp->transfer_buffer, पंचांगp->transfer_dma);
		usb_मुक्त_urb(पंचांगp);
	पूर्ण

	वापस urb;
पूर्ण

/**
 * es58x_submit_urb() - Send data to the device.
 * @es58x_dev: ES58X device.
 * @urb: URB to be sent.
 * @netdev: CAN network device.
 *
 * Return: zero on success, त्रुटि_सं when any error occurs.
 */
अटल पूर्णांक es58x_submit_urb(काष्ठा es58x_device *es58x_dev, काष्ठा urb *urb,
			    काष्ठा net_device *netdev)
अणु
	पूर्णांक ret;

	es58x_set_crc(urb->transfer_buffer, urb->transfer_buffer_length);
	usb_fill_bulk_urb(urb, es58x_dev->udev, es58x_dev->tx_pipe,
			  urb->transfer_buffer, urb->transfer_buffer_length,
			  es58x_ग_लिखो_bulk_callback, netdev);
	usb_anchor_urb(urb, &es58x_dev->tx_urbs_busy);
	ret = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (ret) अणु
		netdev_err(netdev, "%s: USB send urb failure: %pe\n",
			   __func__, ERR_PTR(ret));
		usb_unanchor_urb(urb);
		usb_मुक्त_coherent(urb->dev,
				  es58x_dev->param->tx_urb_cmd_max_len,
				  urb->transfer_buffer, urb->transfer_dma);
	पूर्ण
	usb_मुक्त_urb(urb);

	वापस ret;
पूर्ण

/**
 * es58x_send_msg() - Prepare an URB and submit it.
 * @es58x_dev: ES58X device.
 * @cmd_type: Command type.
 * @cmd_id: Command ID.
 * @msg: ES58X message to be sent.
 * @msg_len: Length of @msg.
 * @channel_idx: Index of the network device.
 *
 * Creates an URB command from a given message, sets the header and the
 * CRC and then submits it.
 *
 * Return: zero on success, त्रुटि_सं when any error occurs.
 */
पूर्णांक es58x_send_msg(काष्ठा es58x_device *es58x_dev, u8 cmd_type, u8 cmd_id,
		   स्थिर व्योम *msg, u16 msg_len, पूर्णांक channel_idx)
अणु
	काष्ठा net_device *netdev;
	जोड़ es58x_urb_cmd *urb_cmd;
	काष्ठा urb *urb;
	पूर्णांक urb_cmd_len;

	अगर (channel_idx == ES58X_CHANNEL_IDX_NA)
		netdev = es58x_dev->netdev[0];	/* Default to first channel */
	अन्यथा
		netdev = es58x_dev->netdev[channel_idx];

	urb_cmd_len = es58x_get_urb_cmd_len(es58x_dev, msg_len);
	अगर (urb_cmd_len > es58x_dev->param->tx_urb_cmd_max_len)
		वापस -EOVERFLOW;

	urb = es58x_get_tx_urb(es58x_dev);
	अगर (!urb)
		वापस -ENOMEM;

	urb_cmd = urb->transfer_buffer;
	es58x_dev->ops->fill_urb_header(urb_cmd, cmd_type, cmd_id,
					channel_idx, msg_len);
	स_नकल(&urb_cmd->raw_cmd[es58x_dev->param->urb_cmd_header_len],
	       msg, msg_len);
	urb->transfer_buffer_length = urb_cmd_len;

	वापस es58x_submit_urb(es58x_dev, urb, netdev);
पूर्ण

/**
 * es58x_alloc_rx_urbs() - Allocate RX URBs.
 * @es58x_dev: ES58X device.
 *
 * Allocate URBs क्रम reception and anchor them.
 *
 * Return: zero on success, त्रुटि_सं when any error occurs.
 */
अटल पूर्णांक es58x_alloc_rx_urbs(काष्ठा es58x_device *es58x_dev)
अणु
	स्थिर काष्ठा device *dev = es58x_dev->dev;
	स्थिर काष्ठा es58x_parameters *param = es58x_dev->param;
	माप_प्रकार rx_buf_len = es58x_dev->rx_max_packet_size;
	काष्ठा urb *urb;
	u8 *buf;
	पूर्णांक i;
	पूर्णांक ret = -EINVAL;

	क्रम (i = 0; i < param->rx_urb_max; i++) अणु
		ret = es58x_alloc_urb(es58x_dev, &urb, &buf, rx_buf_len,
				      GFP_KERNEL);
		अगर (ret)
			अवरोध;

		usb_fill_bulk_urb(urb, es58x_dev->udev, es58x_dev->rx_pipe,
				  buf, rx_buf_len, es58x_पढ़ो_bulk_callback,
				  es58x_dev);
		usb_anchor_urb(urb, &es58x_dev->rx_urbs);

		ret = usb_submit_urb(urb, GFP_KERNEL);
		अगर (ret) अणु
			usb_unanchor_urb(urb);
			usb_मुक्त_coherent(es58x_dev->udev, rx_buf_len,
					  buf, urb->transfer_dma);
			usb_मुक्त_urb(urb);
			अवरोध;
		पूर्ण
		usb_मुक्त_urb(urb);
	पूर्ण

	अगर (i == 0) अणु
		dev_err(dev, "%s: Could not setup any rx URBs\n", __func__);
		वापस ret;
	पूर्ण
	dev_dbg(dev, "%s: Allocated %d rx URBs each of size %zu\n",
		__func__, i, rx_buf_len);

	वापस ret;
पूर्ण

/**
 * es58x_मुक्त_urbs() - Free all the TX and RX URBs.
 * @es58x_dev: ES58X device.
 */
अटल व्योम es58x_मुक्त_urbs(काष्ठा es58x_device *es58x_dev)
अणु
	काष्ठा urb *urb;

	अगर (!usb_रुको_anchor_empty_समयout(&es58x_dev->tx_urbs_busy, 1000)) अणु
		dev_err(es58x_dev->dev, "%s: Timeout, some TX urbs still remain\n",
			__func__);
		usb_समाप्त_anchored_urbs(&es58x_dev->tx_urbs_busy);
	पूर्ण

	जबतक ((urb = usb_get_from_anchor(&es58x_dev->tx_urbs_idle)) != शून्य) अणु
		usb_मुक्त_coherent(urb->dev, es58x_dev->param->tx_urb_cmd_max_len,
				  urb->transfer_buffer, urb->transfer_dma);
		usb_मुक्त_urb(urb);
		atomic_dec(&es58x_dev->tx_urbs_idle_cnt);
	पूर्ण
	अगर (atomic_पढ़ो(&es58x_dev->tx_urbs_idle_cnt))
		dev_err(es58x_dev->dev,
			"All idle urbs were freed but tx_urb_idle_cnt is %d\n",
			atomic_पढ़ो(&es58x_dev->tx_urbs_idle_cnt));

	usb_समाप्त_anchored_urbs(&es58x_dev->rx_urbs);
पूर्ण

/**
 * es58x_खोलो() - Enable the network device.
 * @netdev: CAN network device.
 *
 * Called when the network transitions to the up state. Allocate the
 * URB resources अगर needed and खोलो the channel.
 *
 * Return: zero on success, त्रुटि_सं when any error occurs.
 */
अटल पूर्णांक es58x_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा es58x_device *es58x_dev = es58x_priv(netdev)->es58x_dev;
	पूर्णांक ret;

	अगर (atomic_inc_वापस(&es58x_dev->खोलोed_channel_cnt) == 1) अणु
		ret = es58x_alloc_rx_urbs(es58x_dev);
		अगर (ret)
			वापस ret;

		ret = es58x_set_realसमय_dअगरf_ns(es58x_dev);
		अगर (ret)
			जाओ मुक्त_urbs;
	पूर्ण

	ret = खोलो_candev(netdev);
	अगर (ret)
		जाओ मुक्त_urbs;

	ret = es58x_dev->ops->enable_channel(es58x_priv(netdev));
	अगर (ret)
		जाओ मुक्त_urbs;

	netअगर_start_queue(netdev);

	वापस ret;

 मुक्त_urbs:
	अगर (atomic_dec_and_test(&es58x_dev->खोलोed_channel_cnt))
		es58x_मुक्त_urbs(es58x_dev);
	netdev_err(netdev, "%s: Could not open the network device: %pe\n",
		   __func__, ERR_PTR(ret));

	वापस ret;
पूर्ण

/**
 * es58x_stop() - Disable the network device.
 * @netdev: CAN network device.
 *
 * Called when the network transitions to the करोwn state. If all the
 * channels of the device are बंदd, मुक्त the URB resources which are
 * not needed anymore.
 *
 * Return: zero on success, त्रुटि_सं when any error occurs.
 */
अटल पूर्णांक es58x_stop(काष्ठा net_device *netdev)
अणु
	काष्ठा es58x_priv *priv = es58x_priv(netdev);
	काष्ठा es58x_device *es58x_dev = priv->es58x_dev;
	पूर्णांक ret;

	netअगर_stop_queue(netdev);
	ret = es58x_dev->ops->disable_channel(priv);
	अगर (ret)
		वापस ret;

	priv->can.state = CAN_STATE_STOPPED;
	es58x_can_reset_echo_fअगरo(netdev);
	बंद_candev(netdev);

	es58x_flush_pending_tx_msg(netdev);

	अगर (atomic_dec_and_test(&es58x_dev->खोलोed_channel_cnt))
		es58x_मुक्त_urbs(es58x_dev);

	वापस 0;
पूर्ण

/**
 * es58x_xmit_commit() - Send the bulk urb.
 * @netdev: CAN network device.
 *
 * Do the bulk send. This function should be called only once by bulk
 * transmission.
 *
 * Return: zero on success, त्रुटि_सं when any error occurs.
 */
अटल पूर्णांक es58x_xmit_commit(काष्ठा net_device *netdev)
अणु
	काष्ठा es58x_priv *priv = es58x_priv(netdev);
	पूर्णांक ret;

	अगर (!es58x_is_can_state_active(netdev))
		वापस -ENETDOWN;

	अगर (es58x_is_echo_skb_threshold_reached(priv))
		netअगर_stop_queue(netdev);

	ret = es58x_submit_urb(priv->es58x_dev, priv->tx_urb, netdev);
	अगर (ret == 0)
		priv->tx_urb = शून्य;

	वापस ret;
पूर्ण

/**
 * es58x_xmit_more() - Can we put more packets?
 * @priv: ES58X निजी parameters related to the network device.
 *
 * Return: true अगर we can put more, false अगर it is समय to send.
 */
अटल bool es58x_xmit_more(काष्ठा es58x_priv *priv)
अणु
	अचिन्हित पूर्णांक मुक्त_slots =
	    priv->can.echo_skb_max - (priv->tx_head - priv->tx_tail);

	वापस netdev_xmit_more() && मुक्त_slots > 0 &&
		priv->tx_can_msg_cnt < priv->es58x_dev->param->tx_bulk_max;
पूर्ण

/**
 * es58x_start_xmit() - Transmit an skb.
 * @skb: socket buffer of a CAN message.
 * @netdev: CAN network device.
 *
 * Called when a packet needs to be transmitted.
 *
 * This function relies on Byte Queue Limits (BQL). The मुख्य benefit
 * is to increase the throughput by allowing bulk transfers
 * (c.f. xmit_more flag).
 *
 * Queues up to tx_bulk_max messages in &tx_urb buffer and करोes
 * a bulk send of all messages in one single URB.
 *
 * Return: NETDEV_TX_OK regardless of अगर we could transmit the @skb or
 *	had to drop it.
 */
अटल netdev_tx_t es58x_start_xmit(काष्ठा sk_buff *skb,
				    काष्ठा net_device *netdev)
अणु
	काष्ठा es58x_priv *priv = es58x_priv(netdev);
	काष्ठा es58x_device *es58x_dev = priv->es58x_dev;
	अचिन्हित पूर्णांक frame_len;
	पूर्णांक ret;

	अगर (can_dropped_invalid_skb(netdev, skb)) अणु
		अगर (priv->tx_urb)
			जाओ xmit_commit;
		वापस NETDEV_TX_OK;
	पूर्ण

	अगर (priv->tx_urb && priv->tx_can_msg_is_fd != can_is_canfd_skb(skb)) अणु
		/* Can not करो bulk send with mixed CAN and CAN FD frames. */
		ret = es58x_xmit_commit(netdev);
		अगर (ret)
			जाओ drop_skb;
	पूर्ण

	अगर (!priv->tx_urb) अणु
		priv->tx_urb = es58x_get_tx_urb(es58x_dev);
		अगर (!priv->tx_urb) अणु
			ret = -ENOMEM;
			जाओ drop_skb;
		पूर्ण
		priv->tx_can_msg_cnt = 0;
		priv->tx_can_msg_is_fd = can_is_canfd_skb(skb);
	पूर्ण

	ret = es58x_dev->ops->tx_can_msg(priv, skb);
	अगर (ret)
		जाओ drop_skb;

	frame_len = can_skb_get_frame_len(skb);
	ret = can_put_echo_skb(skb, netdev,
			       priv->tx_head & es58x_dev->param->fअगरo_mask,
			       frame_len);
	अगर (ret)
		जाओ xmit_failure;
	netdev_sent_queue(netdev, frame_len);

	priv->tx_head++;
	priv->tx_can_msg_cnt++;

 xmit_commit:
	अगर (!es58x_xmit_more(priv)) अणु
		ret = es58x_xmit_commit(netdev);
		अगर (ret)
			जाओ xmit_failure;
	पूर्ण

	वापस NETDEV_TX_OK;

 drop_skb:
	dev_kमुक्त_skb(skb);
	netdev->stats.tx_dropped++;
 xmit_failure:
	netdev_warn(netdev, "%s: send message failure: %pe\n",
		    __func__, ERR_PTR(ret));
	netdev->stats.tx_errors++;
	es58x_flush_pending_tx_msg(netdev);
	वापस NETDEV_TX_OK;
पूर्ण

अटल स्थिर काष्ठा net_device_ops es58x_netdev_ops = अणु
	.nकरो_खोलो = es58x_खोलो,
	.nकरो_stop = es58x_stop,
	.nकरो_start_xmit = es58x_start_xmit
पूर्ण;

/**
 * es58x_set_mode() - Change network device mode.
 * @netdev: CAN network device.
 * @mode: either %CAN_MODE_START, %CAN_MODE_STOP or %CAN_MODE_SLEEP
 *
 * Currently, this function is only used to stop and restart the
 * channel during a bus off event (c.f. es58x_rx_err_msg() and
 * drivers/net/can/dev.c:can_restart() which are the two only
 * callers).
 *
 * Return: zero on success, त्रुटि_सं when any error occurs.
 */
अटल पूर्णांक es58x_set_mode(काष्ठा net_device *netdev, क्रमागत can_mode mode)
अणु
	काष्ठा es58x_priv *priv = es58x_priv(netdev);

	चयन (mode) अणु
	हाल CAN_MODE_START:
		चयन (priv->can.state) अणु
		हाल CAN_STATE_BUS_OFF:
			वापस priv->es58x_dev->ops->enable_channel(priv);

		हाल CAN_STATE_STOPPED:
			वापस es58x_खोलो(netdev);

		हाल CAN_STATE_ERROR_ACTIVE:
		हाल CAN_STATE_ERROR_WARNING:
		हाल CAN_STATE_ERROR_PASSIVE:
		शेष:
			वापस 0;
		पूर्ण

	हाल CAN_MODE_STOP:
		चयन (priv->can.state) अणु
		हाल CAN_STATE_STOPPED:
			वापस 0;

		हाल CAN_STATE_ERROR_ACTIVE:
		हाल CAN_STATE_ERROR_WARNING:
		हाल CAN_STATE_ERROR_PASSIVE:
		हाल CAN_STATE_BUS_OFF:
		शेष:
			वापस priv->es58x_dev->ops->disable_channel(priv);
		पूर्ण

	हाल CAN_MODE_SLEEP:
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

/**
 * es58x_init_priv() - Initialize निजी parameters.
 * @es58x_dev: ES58X device.
 * @priv: ES58X निजी parameters related to the network device.
 * @channel_idx: Index of the network device.
 */
अटल व्योम es58x_init_priv(काष्ठा es58x_device *es58x_dev,
			    काष्ठा es58x_priv *priv, पूर्णांक channel_idx)
अणु
	स्थिर काष्ठा es58x_parameters *param = es58x_dev->param;
	काष्ठा can_priv *can = &priv->can;

	priv->es58x_dev = es58x_dev;
	priv->channel_idx = channel_idx;
	priv->tx_urb = शून्य;
	priv->tx_can_msg_cnt = 0;

	can->bittiming_स्थिर = param->bittiming_स्थिर;
	अगर (param->ctrlmode_supported & CAN_CTRLMODE_FD) अणु
		can->data_bittiming_स्थिर = param->data_bittiming_स्थिर;
		can->tdc_स्थिर = param->tdc_स्थिर;
	पूर्ण
	can->bitrate_max = param->bitrate_max;
	can->घड़ी = param->घड़ी;
	can->state = CAN_STATE_STOPPED;
	can->ctrlmode_supported = param->ctrlmode_supported;
	can->करो_set_mode = es58x_set_mode;
पूर्ण

/**
 * es58x_init_netdev() - Initialize the network device.
 * @es58x_dev: ES58X device.
 * @channel_idx: Index of the network device.
 *
 * Return: zero on success, त्रुटि_सं when any error occurs.
 */
अटल पूर्णांक es58x_init_netdev(काष्ठा es58x_device *es58x_dev, पूर्णांक channel_idx)
अणु
	काष्ठा net_device *netdev;
	काष्ठा device *dev = es58x_dev->dev;
	पूर्णांक ret;

	netdev = alloc_candev(माप(काष्ठा es58x_priv),
			      es58x_dev->param->fअगरo_mask + 1);
	अगर (!netdev) अणु
		dev_err(dev, "Could not allocate candev\n");
		वापस -ENOMEM;
	पूर्ण
	SET_NETDEV_DEV(netdev, dev);
	es58x_dev->netdev[channel_idx] = netdev;
	es58x_init_priv(es58x_dev, es58x_priv(netdev), channel_idx);

	netdev->netdev_ops = &es58x_netdev_ops;
	netdev->flags |= IFF_ECHO;	/* We support local echo */

	ret = रेजिस्टर_candev(netdev);
	अगर (ret)
		वापस ret;

	netdev_queue_set_dql_min_limit(netdev_get_tx_queue(netdev, 0),
				       es58x_dev->param->dql_min_limit);

	वापस ret;
पूर्ण

/**
 * es58x_get_product_info() - Get the product inक्रमmation and prपूर्णांक them.
 * @es58x_dev: ES58X device.
 *
 * Do a synchronous call to get the product inक्रमmation.
 *
 * Return: zero on success, त्रुटि_सं when any error occurs.
 */
अटल पूर्णांक es58x_get_product_info(काष्ठा es58x_device *es58x_dev)
अणु
	काष्ठा usb_device *udev = es58x_dev->udev;
	स्थिर पूर्णांक es58x_prod_info_idx = 6;
	/* Empirical tests show a prod_info length of maximum 83,
	 * below should be more than enough.
	 */
	स्थिर माप_प्रकार prod_info_len = 127;
	अक्षर *prod_info;
	पूर्णांक ret;

	prod_info = kदो_स्मृति(prod_info_len, GFP_KERNEL);
	अगर (!prod_info)
		वापस -ENOMEM;

	ret = usb_string(udev, es58x_prod_info_idx, prod_info, prod_info_len);
	अगर (ret < 0) अणु
		dev_err(es58x_dev->dev,
			"%s: Could not read the product info: %pe\n",
			__func__, ERR_PTR(ret));
		जाओ out_मुक्त;
	पूर्ण
	अगर (ret >= prod_info_len - 1) अणु
		dev_warn(es58x_dev->dev,
			 "%s: Buffer is too small, result might be truncated\n",
			 __func__);
	पूर्ण
	dev_info(es58x_dev->dev, "Product info: %s\n", prod_info);

 out_मुक्त:
	kमुक्त(prod_info);
	वापस ret < 0 ? ret : 0;
पूर्ण

/**
 * es58x_init_es58x_dev() - Initialize the ES58X device.
 * @पूर्णांकf: USB पूर्णांकerface.
 * @p_es58x_dev: poपूर्णांकer to the address of the ES58X device.
 * @driver_info: Quirks of the device.
 *
 * Return: zero on success, त्रुटि_सं when any error occurs.
 */
अटल पूर्णांक es58x_init_es58x_dev(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
				काष्ठा es58x_device **p_es58x_dev,
				kernel_uदीर्घ_t driver_info)
अणु
	काष्ठा device *dev = &पूर्णांकf->dev;
	काष्ठा es58x_device *es58x_dev;
	स्थिर काष्ठा es58x_parameters *param;
	स्थिर काष्ठा es58x_चालकs *ops;
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा usb_endpoपूर्णांक_descriptor *ep_in, *ep_out;
	पूर्णांक ret;

	dev_info(dev,
		 "Starting %s %s (Serial Number %s) driver version %s\n",
		 udev->manufacturer, udev->product, udev->serial, DRV_VERSION);

	ret = usb_find_common_endpoपूर्णांकs(पूर्णांकf->cur_altsetting, &ep_in, &ep_out,
					शून्य, शून्य);
	अगर (ret)
		वापस ret;

	अगर (driver_info & ES58X_FD_FAMILY) अणु
		param = &es58x_fd_param;
		ops = &es58x_fd_ops;
	पूर्ण अन्यथा अणु
		param = &es581_4_param;
		ops = &es581_4_ops;
	पूर्ण

	es58x_dev = kzalloc(es58x_माप_es58x_device(param), GFP_KERNEL);
	अगर (!es58x_dev)
		वापस -ENOMEM;

	es58x_dev->param = param;
	es58x_dev->ops = ops;
	es58x_dev->dev = dev;
	es58x_dev->udev = udev;

	अगर (driver_info & ES58X_DUAL_CHANNEL)
		es58x_dev->num_can_ch = 2;
	अन्यथा
		es58x_dev->num_can_ch = 1;

	init_usb_anchor(&es58x_dev->rx_urbs);
	init_usb_anchor(&es58x_dev->tx_urbs_idle);
	init_usb_anchor(&es58x_dev->tx_urbs_busy);
	atomic_set(&es58x_dev->tx_urbs_idle_cnt, 0);
	atomic_set(&es58x_dev->खोलोed_channel_cnt, 0);
	usb_set_पूर्णांकfdata(पूर्णांकf, es58x_dev);

	es58x_dev->rx_pipe = usb_rcvbulkpipe(es58x_dev->udev,
					     ep_in->bEndpoपूर्णांकAddress);
	es58x_dev->tx_pipe = usb_sndbulkpipe(es58x_dev->udev,
					     ep_out->bEndpoपूर्णांकAddress);
	es58x_dev->rx_max_packet_size = le16_to_cpu(ep_in->wMaxPacketSize);

	*p_es58x_dev = es58x_dev;

	वापस 0;
पूर्ण

/**
 * es58x_probe() - Initialize the USB device.
 * @पूर्णांकf: USB पूर्णांकerface.
 * @id: USB device ID.
 *
 * Return: zero on success, -ENODEV अगर the पूर्णांकerface is not supported
 * or त्रुटि_सं when any other error occurs.
 */
अटल पूर्णांक es58x_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		       स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा es58x_device *es58x_dev;
	पूर्णांक ch_idx, ret;

	ret = es58x_init_es58x_dev(पूर्णांकf, &es58x_dev, id->driver_info);
	अगर (ret)
		वापस ret;

	ret = es58x_get_product_info(es58x_dev);
	अगर (ret)
		जाओ cleanup_es58x_dev;

	क्रम (ch_idx = 0; ch_idx < es58x_dev->num_can_ch; ch_idx++) अणु
		ret = es58x_init_netdev(es58x_dev, ch_idx);
		अगर (ret)
			जाओ cleanup_candev;
	पूर्ण

	वापस ret;

 cleanup_candev:
	क्रम (ch_idx = 0; ch_idx < es58x_dev->num_can_ch; ch_idx++)
		अगर (es58x_dev->netdev[ch_idx]) अणु
			unरेजिस्टर_candev(es58x_dev->netdev[ch_idx]);
			मुक्त_candev(es58x_dev->netdev[ch_idx]);
		पूर्ण
 cleanup_es58x_dev:
	kमुक्त(es58x_dev);

	वापस ret;
पूर्ण

/**
 * es58x_disconnect() - Disconnect the USB device.
 * @पूर्णांकf: USB पूर्णांकerface
 *
 * Called by the usb core when driver is unloaded or device is
 * हटाओd.
 */
अटल व्योम es58x_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा es58x_device *es58x_dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा net_device *netdev;
	पूर्णांक i;

	dev_info(&पूर्णांकf->dev, "Disconnecting %s %s\n",
		 es58x_dev->udev->manufacturer, es58x_dev->udev->product);

	क्रम (i = 0; i < es58x_dev->num_can_ch; i++) अणु
		netdev = es58x_dev->netdev[i];
		अगर (!netdev)
			जारी;
		unरेजिस्टर_candev(netdev);
		es58x_dev->netdev[i] = शून्य;
		मुक्त_candev(netdev);
	पूर्ण

	es58x_मुक्त_urbs(es58x_dev);

	kमुक्त(es58x_dev);
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
पूर्ण

अटल काष्ठा usb_driver es58x_driver = अणु
	.name = ES58X_MODULE_NAME,
	.probe = es58x_probe,
	.disconnect = es58x_disconnect,
	.id_table = es58x_id_table
पूर्ण;

module_usb_driver(es58x_driver);
