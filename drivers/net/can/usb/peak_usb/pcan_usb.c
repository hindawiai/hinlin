<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * CAN driver क्रम PEAK System PCAN-USB adapter
 * Derived from the PCAN project file driver/src/pcan_usb.c
 *
 * Copyright (C) 2003-2010 PEAK System-Technik GmbH
 * Copyright (C) 2011-2012 Stephane Grosjean <s.grosjean@peak-प्रणाली.com>
 *
 * Many thanks to Klaus Hitschler <klaus.hitschler@gmx.de>
 */
#समावेश <linux/netdevice.h>
#समावेश <linux/usb.h>
#समावेश <linux/module.h>
#समावेश <linux/ethtool.h>

#समावेश <linux/can.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/can/error.h>

#समावेश "pcan_usb_core.h"

/* PCAN-USB Endpoपूर्णांकs */
#घोषणा PCAN_USB_EP_CMDOUT		1
#घोषणा PCAN_USB_EP_CMDIN		(PCAN_USB_EP_CMDOUT | USB_सूची_IN)
#घोषणा PCAN_USB_EP_MSGOUT		2
#घोषणा PCAN_USB_EP_MSGIN		(PCAN_USB_EP_MSGOUT | USB_सूची_IN)

/* PCAN-USB command काष्ठा */
#घोषणा PCAN_USB_CMD_FUNC		0
#घोषणा PCAN_USB_CMD_NUM		1
#घोषणा PCAN_USB_CMD_ARGS		2
#घोषणा PCAN_USB_CMD_ARGS_LEN		14
#घोषणा PCAN_USB_CMD_LEN		(PCAN_USB_CMD_ARGS + \
					 PCAN_USB_CMD_ARGS_LEN)

/* PCAN-USB commands */
#घोषणा PCAN_USB_CMD_BITRATE	1
#घोषणा PCAN_USB_CMD_SET_BUS	3
#घोषणा PCAN_USB_CMD_DEVID	4
#घोषणा PCAN_USB_CMD_SN		6
#घोषणा PCAN_USB_CMD_REGISTER	9
#घोषणा PCAN_USB_CMD_EXT_VCC	10
#घोषणा PCAN_USB_CMD_ERR_FR	11
#घोषणा PCAN_USB_CMD_LED	12

/* PCAN_USB_CMD_SET_BUS number arg */
#घोषणा PCAN_USB_BUS_XCVER		2
#घोषणा PCAN_USB_BUS_SILENT_MODE	3

/* PCAN_USB_CMD_xxx functions */
#घोषणा PCAN_USB_GET		1
#घोषणा PCAN_USB_SET		2

/* PCAN-USB command समयout (ms.) */
#घोषणा PCAN_USB_COMMAND_TIMEOUT	1000

/* PCAN-USB startup समयout (ms.) */
#घोषणा PCAN_USB_STARTUP_TIMEOUT	10

/* PCAN-USB rx/tx buffers size */
#घोषणा PCAN_USB_RX_BUFFER_SIZE		64
#घोषणा PCAN_USB_TX_BUFFER_SIZE		64

#घोषणा PCAN_USB_MSG_HEADER_LEN		2

/* PCAN-USB adapter पूर्णांकernal घड़ी (MHz) */
#घोषणा PCAN_USB_CRYSTAL_HZ		16000000

/* PCAN-USB USB message record status/len field */
#घोषणा PCAN_USB_STATUSLEN_TIMESTAMP	(1 << 7)
#घोषणा PCAN_USB_STATUSLEN_INTERNAL	(1 << 6)
#घोषणा PCAN_USB_STATUSLEN_EXT_ID	(1 << 5)
#घोषणा PCAN_USB_STATUSLEN_RTR		(1 << 4)
#घोषणा PCAN_USB_STATUSLEN_DLC		(0xf)

/* PCAN-USB error flags */
#घोषणा PCAN_USB_ERROR_TXFULL		0x01
#घोषणा PCAN_USB_ERROR_RXQOVR		0x02
#घोषणा PCAN_USB_ERROR_BUS_LIGHT	0x04
#घोषणा PCAN_USB_ERROR_BUS_HEAVY	0x08
#घोषणा PCAN_USB_ERROR_BUS_OFF		0x10
#घोषणा PCAN_USB_ERROR_RXQEMPTY		0x20
#घोषणा PCAN_USB_ERROR_QOVR		0x40
#घोषणा PCAN_USB_ERROR_TXQFULL		0x80

#घोषणा PCAN_USB_ERROR_BUS		(PCAN_USB_ERROR_BUS_LIGHT | \
					 PCAN_USB_ERROR_BUS_HEAVY | \
					 PCAN_USB_ERROR_BUS_OFF)

/* SJA1000 modes */
#घोषणा SJA1000_MODE_NORMAL		0x00
#घोषणा SJA1000_MODE_INIT		0x01

/*
 * tick duration = 42.666 us =>
 * (tick_number * 44739243) >> 20 ~ (tick_number * 42666) / 1000
 * accuracy = 10^-7
 */
#घोषणा PCAN_USB_TS_DIV_SHIFTER		20
#घोषणा PCAN_USB_TS_US_PER_TICK		44739243

/* PCAN-USB messages record types */
#घोषणा PCAN_USB_REC_ERROR		1
#घोषणा PCAN_USB_REC_ANALOG		2
#घोषणा PCAN_USB_REC_BUSLOAD		3
#घोषणा PCAN_USB_REC_TS			4
#घोषणा PCAN_USB_REC_BUSEVT		5

/* CAN bus events notअगरications selection mask */
#घोषणा PCAN_USB_ERR_RXERR		0x02	/* ask क्रम rxerr counter */
#घोषणा PCAN_USB_ERR_TXERR		0x04	/* ask क्रम txerr counter */

/* This mask generates an usb packet each समय the state of the bus changes.
 * In other words, its पूर्णांकerest is to know which side among rx and tx is
 * responsible of the change of the bus state.
 */
#घोषणा PCAN_USB_BERR_MASK	(PCAN_USB_ERR_RXERR | PCAN_USB_ERR_TXERR)

/* identअगरy bus event packets with rx/tx error counters */
#घोषणा PCAN_USB_ERR_CNT		0x80

/* निजी to PCAN-USB adapter */
काष्ठा pcan_usb अणु
	काष्ठा peak_usb_device dev;
	काष्ठा peak_समय_ref समय_ref;
	काष्ठा समयr_list restart_समयr;
	काष्ठा can_berr_counter bec;
पूर्ण;

/* incoming message context क्रम decoding */
काष्ठा pcan_usb_msg_context अणु
	u16 ts16;
	u8 prev_ts8;
	u8 *ptr;
	u8 *end;
	u8 rec_cnt;
	u8 rec_idx;
	u8 rec_ts_idx;
	काष्ठा net_device *netdev;
	काष्ठा pcan_usb *pdev;
पूर्ण;

/*
 * send a command
 */
अटल पूर्णांक pcan_usb_send_cmd(काष्ठा peak_usb_device *dev, u8 f, u8 n, u8 *p)
अणु
	पूर्णांक err;
	पूर्णांक actual_length;

	/* usb device unरेजिस्टरed? */
	अगर (!(dev->state & PCAN_USB_STATE_CONNECTED))
		वापस 0;

	dev->cmd_buf[PCAN_USB_CMD_FUNC] = f;
	dev->cmd_buf[PCAN_USB_CMD_NUM] = n;

	अगर (p)
		स_नकल(dev->cmd_buf + PCAN_USB_CMD_ARGS,
			p, PCAN_USB_CMD_ARGS_LEN);

	err = usb_bulk_msg(dev->udev,
			usb_sndbulkpipe(dev->udev, PCAN_USB_EP_CMDOUT),
			dev->cmd_buf, PCAN_USB_CMD_LEN, &actual_length,
			PCAN_USB_COMMAND_TIMEOUT);
	अगर (err)
		netdev_err(dev->netdev,
			"sending cmd f=0x%x n=0x%x failure: %d\n",
			f, n, err);
	वापस err;
पूर्ण

/*
 * send a command then रुको क्रम its response
 */
अटल पूर्णांक pcan_usb_रुको_rsp(काष्ठा peak_usb_device *dev, u8 f, u8 n, u8 *p)
अणु
	पूर्णांक err;
	पूर्णांक actual_length;

	/* usb device unरेजिस्टरed? */
	अगर (!(dev->state & PCAN_USB_STATE_CONNECTED))
		वापस 0;

	/* first, send command */
	err = pcan_usb_send_cmd(dev, f, n, शून्य);
	अगर (err)
		वापस err;

	err = usb_bulk_msg(dev->udev,
		usb_rcvbulkpipe(dev->udev, PCAN_USB_EP_CMDIN),
		dev->cmd_buf, PCAN_USB_CMD_LEN, &actual_length,
		PCAN_USB_COMMAND_TIMEOUT);
	अगर (err)
		netdev_err(dev->netdev,
			"waiting rsp f=0x%x n=0x%x failure: %d\n", f, n, err);
	अन्यथा अगर (p)
		स_नकल(p, dev->cmd_buf + PCAN_USB_CMD_ARGS,
			PCAN_USB_CMD_ARGS_LEN);

	वापस err;
पूर्ण

अटल पूर्णांक pcan_usb_set_sja1000(काष्ठा peak_usb_device *dev, u8 mode)
अणु
	u8 args[PCAN_USB_CMD_ARGS_LEN] = अणु
		[1] = mode,
	पूर्ण;

	वापस pcan_usb_send_cmd(dev, PCAN_USB_CMD_REGISTER, PCAN_USB_SET,
				 args);
पूर्ण

अटल पूर्णांक pcan_usb_set_bus(काष्ठा peak_usb_device *dev, u8 onoff)
अणु
	u8 args[PCAN_USB_CMD_ARGS_LEN] = अणु
		[0] = !!onoff,
	पूर्ण;

	वापस pcan_usb_send_cmd(dev, PCAN_USB_CMD_SET_BUS, PCAN_USB_BUS_XCVER,
				 args);
पूर्ण

अटल पूर्णांक pcan_usb_set_silent(काष्ठा peak_usb_device *dev, u8 onoff)
अणु
	u8 args[PCAN_USB_CMD_ARGS_LEN] = अणु
		[0] = !!onoff,
	पूर्ण;

	वापस pcan_usb_send_cmd(dev, PCAN_USB_CMD_SET_BUS,
				 PCAN_USB_BUS_SILENT_MODE, args);
पूर्ण

/* send the cmd to be notअगरied from bus errors */
अटल पूर्णांक pcan_usb_set_err_frame(काष्ठा peak_usb_device *dev, u8 err_mask)
अणु
	u8 args[PCAN_USB_CMD_ARGS_LEN] = अणु
		[0] = err_mask,
	पूर्ण;

	वापस pcan_usb_send_cmd(dev, PCAN_USB_CMD_ERR_FR, PCAN_USB_SET, args);
पूर्ण

अटल पूर्णांक pcan_usb_set_ext_vcc(काष्ठा peak_usb_device *dev, u8 onoff)
अणु
	u8 args[PCAN_USB_CMD_ARGS_LEN] = अणु
		[0] = !!onoff,
	पूर्ण;

	वापस pcan_usb_send_cmd(dev, PCAN_USB_CMD_EXT_VCC, PCAN_USB_SET, args);
पूर्ण

अटल पूर्णांक pcan_usb_set_led(काष्ठा peak_usb_device *dev, u8 onoff)
अणु
	u8 args[PCAN_USB_CMD_ARGS_LEN] = अणु
		[0] = !!onoff,
	पूर्ण;

	वापस pcan_usb_send_cmd(dev, PCAN_USB_CMD_LED, PCAN_USB_SET, args);
पूर्ण

/*
 * set bittiming value to can
 */
अटल पूर्णांक pcan_usb_set_bittiming(काष्ठा peak_usb_device *dev,
				  काष्ठा can_bittiming *bt)
अणु
	u8 args[PCAN_USB_CMD_ARGS_LEN];
	u8 btr0, btr1;

	btr0 = ((bt->brp - 1) & 0x3f) | (((bt->sjw - 1) & 0x3) << 6);
	btr1 = ((bt->prop_seg + bt->phase_seg1 - 1) & 0xf) |
		(((bt->phase_seg2 - 1) & 0x7) << 4);
	अगर (dev->can.ctrlmode & CAN_CTRLMODE_3_SAMPLES)
		btr1 |= 0x80;

	netdev_info(dev->netdev, "setting BTR0=0x%02x BTR1=0x%02x\n",
		btr0, btr1);

	args[0] = btr1;
	args[1] = btr0;

	वापस pcan_usb_send_cmd(dev, PCAN_USB_CMD_BITRATE, PCAN_USB_SET, args);
पूर्ण

/*
 * init/reset can
 */
अटल पूर्णांक pcan_usb_ग_लिखो_mode(काष्ठा peak_usb_device *dev, u8 onoff)
अणु
	पूर्णांक err;

	err = pcan_usb_set_bus(dev, onoff);
	अगर (err)
		वापस err;

	अगर (!onoff) अणु
		err = pcan_usb_set_sja1000(dev, SJA1000_MODE_INIT);
	पूर्ण अन्यथा अणु
		/* the PCAN-USB needs समय to init */
		set_current_state(TASK_INTERRUPTIBLE);
		schedule_समयout(msecs_to_jअगरfies(PCAN_USB_STARTUP_TIMEOUT));
	पूर्ण

	वापस err;
पूर्ण

/*
 * handle end of रुकोing क्रम the device to reset
 */
अटल व्योम pcan_usb_restart(काष्ठा समयr_list *t)
अणु
	काष्ठा pcan_usb *pdev = from_समयr(pdev, t, restart_समयr);
	काष्ठा peak_usb_device *dev = &pdev->dev;

	/* notअगरy candev and netdev */
	peak_usb_restart_complete(dev);
पूर्ण

/*
 * handle the submission of the restart urb
 */
अटल व्योम pcan_usb_restart_pending(काष्ठा urb *urb)
अणु
	काष्ठा pcan_usb *pdev = urb->context;

	/* the PCAN-USB needs समय to restart */
	mod_समयr(&pdev->restart_समयr,
			jअगरfies + msecs_to_jअगरfies(PCAN_USB_STARTUP_TIMEOUT));

	/* can delete usb resources */
	peak_usb_async_complete(urb);
पूर्ण

/*
 * handle asynchronous restart
 */
अटल पूर्णांक pcan_usb_restart_async(काष्ठा peak_usb_device *dev, काष्ठा urb *urb,
				  u8 *buf)
अणु
	काष्ठा pcan_usb *pdev = container_of(dev, काष्ठा pcan_usb, dev);

	अगर (समयr_pending(&pdev->restart_समयr))
		वापस -EBUSY;

	/* set bus on */
	buf[PCAN_USB_CMD_FUNC] = 3;
	buf[PCAN_USB_CMD_NUM] = 2;
	buf[PCAN_USB_CMD_ARGS] = 1;

	usb_fill_bulk_urb(urb, dev->udev,
			usb_sndbulkpipe(dev->udev, PCAN_USB_EP_CMDOUT),
			buf, PCAN_USB_CMD_LEN,
			pcan_usb_restart_pending, pdev);

	वापस usb_submit_urb(urb, GFP_ATOMIC);
पूर्ण

/*
 * पढ़ो serial number from device
 */
अटल पूर्णांक pcan_usb_get_serial(काष्ठा peak_usb_device *dev, u32 *serial_number)
अणु
	u8 args[PCAN_USB_CMD_ARGS_LEN];
	पूर्णांक err;

	err = pcan_usb_रुको_rsp(dev, PCAN_USB_CMD_SN, PCAN_USB_GET, args);
	अगर (err)
		वापस err;
	*serial_number = le32_to_cpup((__le32 *)args);

	वापस 0;
पूर्ण

/*
 * पढ़ो device id from device
 */
अटल पूर्णांक pcan_usb_get_device_id(काष्ठा peak_usb_device *dev, u32 *device_id)
अणु
	u8 args[PCAN_USB_CMD_ARGS_LEN];
	पूर्णांक err;

	err = pcan_usb_रुको_rsp(dev, PCAN_USB_CMD_DEVID, PCAN_USB_GET, args);
	अगर (err)
		netdev_err(dev->netdev, "getting device id failure: %d\n", err);

	*device_id = args[0];

	वापस err;
पूर्ण

/*
 * update current समय ref with received बारtamp
 */
अटल पूर्णांक pcan_usb_update_ts(काष्ठा pcan_usb_msg_context *mc)
अणु
	अगर ((mc->ptr + 2) > mc->end)
		वापस -EINVAL;

	mc->ts16 = get_unaligned_le16(mc->ptr);

	अगर (mc->rec_idx > 0)
		peak_usb_update_ts_now(&mc->pdev->समय_ref, mc->ts16);
	अन्यथा
		peak_usb_set_ts_now(&mc->pdev->समय_ref, mc->ts16);

	वापस 0;
पूर्ण

/*
 * decode received बारtamp
 */
अटल पूर्णांक pcan_usb_decode_ts(काष्ठा pcan_usb_msg_context *mc, u8 first_packet)
अणु
	/* only 1st packet supplies a word बारtamp */
	अगर (first_packet) अणु
		अगर ((mc->ptr + 2) > mc->end)
			वापस -EINVAL;

		mc->ts16 = get_unaligned_le16(mc->ptr);
		mc->prev_ts8 = mc->ts16 & 0x00ff;

		mc->ptr += 2;
	पूर्ण अन्यथा अणु
		u8 ts8;

		अगर ((mc->ptr + 1) > mc->end)
			वापस -EINVAL;

		ts8 = *mc->ptr++;

		अगर (ts8 < mc->prev_ts8)
			mc->ts16 += 0x100;

		mc->ts16 &= 0xff00;
		mc->ts16 |= ts8;
		mc->prev_ts8 = ts8;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pcan_usb_decode_error(काष्ठा pcan_usb_msg_context *mc, u8 n,
				 u8 status_len)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा can_frame *cf;
	क्रमागत can_state new_state;

	/* ignore this error until 1st ts received */
	अगर (n == PCAN_USB_ERROR_QOVR)
		अगर (!mc->pdev->समय_ref.tick_count)
			वापस 0;

	new_state = mc->pdev->dev.can.state;

	चयन (mc->pdev->dev.can.state) अणु
	हाल CAN_STATE_ERROR_ACTIVE:
		अगर (n & PCAN_USB_ERROR_BUS_LIGHT) अणु
			new_state = CAN_STATE_ERROR_WARNING;
			अवरोध;
		पूर्ण
		fallthrough;

	हाल CAN_STATE_ERROR_WARNING:
		अगर (n & PCAN_USB_ERROR_BUS_HEAVY) अणु
			new_state = CAN_STATE_ERROR_PASSIVE;
			अवरोध;
		पूर्ण
		अगर (n & PCAN_USB_ERROR_BUS_OFF) अणु
			new_state = CAN_STATE_BUS_OFF;
			अवरोध;
		पूर्ण
		अगर (n & ~PCAN_USB_ERROR_BUS) अणु
			/*
			 * trick to bypass next comparison and process other
			 * errors
			 */
			new_state = CAN_STATE_MAX;
			अवरोध;
		पूर्ण
		अगर ((n & PCAN_USB_ERROR_BUS_LIGHT) == 0) अणु
			/* no error (back to active state) */
			new_state = CAN_STATE_ERROR_ACTIVE;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल CAN_STATE_ERROR_PASSIVE:
		अगर (n & PCAN_USB_ERROR_BUS_OFF) अणु
			new_state = CAN_STATE_BUS_OFF;
			अवरोध;
		पूर्ण
		अगर (n & PCAN_USB_ERROR_BUS_LIGHT) अणु
			new_state = CAN_STATE_ERROR_WARNING;
			अवरोध;
		पूर्ण
		अगर (n & ~PCAN_USB_ERROR_BUS) अणु
			/*
			 * trick to bypass next comparison and process other
			 * errors
			 */
			new_state = CAN_STATE_MAX;
			अवरोध;
		पूर्ण

		अगर ((n & PCAN_USB_ERROR_BUS_HEAVY) == 0) अणु
			/* no error (back to warning state) */
			new_state = CAN_STATE_ERROR_WARNING;
			अवरोध;
		पूर्ण
		अवरोध;

	शेष:
		/* करो nothing रुकोing क्रम restart */
		वापस 0;
	पूर्ण

	/* करोnot post any error अगर current state didn't change */
	अगर (mc->pdev->dev.can.state == new_state)
		वापस 0;

	/* allocate an skb to store the error frame */
	skb = alloc_can_err_skb(mc->netdev, &cf);
	अगर (!skb)
		वापस -ENOMEM;

	चयन (new_state) अणु
	हाल CAN_STATE_BUS_OFF:
		cf->can_id |= CAN_ERR_BUSOFF;
		mc->pdev->dev.can.can_stats.bus_off++;
		can_bus_off(mc->netdev);
		अवरोध;

	हाल CAN_STATE_ERROR_PASSIVE:
		cf->can_id |= CAN_ERR_CRTL;
		cf->data[1] = (mc->pdev->bec.txerr > mc->pdev->bec.rxerr) ?
				CAN_ERR_CRTL_TX_PASSIVE :
				CAN_ERR_CRTL_RX_PASSIVE;
		cf->data[6] = mc->pdev->bec.txerr;
		cf->data[7] = mc->pdev->bec.rxerr;

		mc->pdev->dev.can.can_stats.error_passive++;
		अवरोध;

	हाल CAN_STATE_ERROR_WARNING:
		cf->can_id |= CAN_ERR_CRTL;
		cf->data[1] = (mc->pdev->bec.txerr > mc->pdev->bec.rxerr) ?
				CAN_ERR_CRTL_TX_WARNING :
				CAN_ERR_CRTL_RX_WARNING;
		cf->data[6] = mc->pdev->bec.txerr;
		cf->data[7] = mc->pdev->bec.rxerr;

		mc->pdev->dev.can.can_stats.error_warning++;
		अवरोध;

	हाल CAN_STATE_ERROR_ACTIVE:
		cf->can_id |= CAN_ERR_CRTL;
		cf->data[1] = CAN_ERR_CRTL_ACTIVE;

		/* sync local copies of rxerr/txerr counters */
		mc->pdev->bec.txerr = 0;
		mc->pdev->bec.rxerr = 0;
		अवरोध;

	शेष:
		/* CAN_STATE_MAX (trick to handle other errors) */
		अगर (n & PCAN_USB_ERROR_TXQFULL)
			netdev_dbg(mc->netdev, "device Tx queue full)\n");

		अगर (n & PCAN_USB_ERROR_RXQOVR) अणु
			netdev_dbg(mc->netdev, "data overrun interrupt\n");
			cf->can_id |= CAN_ERR_CRTL;
			cf->data[1] |= CAN_ERR_CRTL_RX_OVERFLOW;
			mc->netdev->stats.rx_over_errors++;
			mc->netdev->stats.rx_errors++;
		पूर्ण

		cf->data[6] = mc->pdev->bec.txerr;
		cf->data[7] = mc->pdev->bec.rxerr;

		new_state = mc->pdev->dev.can.state;
		अवरोध;
	पूर्ण

	mc->pdev->dev.can.state = new_state;

	अगर (status_len & PCAN_USB_STATUSLEN_TIMESTAMP) अणु
		काष्ठा skb_shared_hwtstamps *hwts = skb_hwtstamps(skb);

		peak_usb_get_ts_समय(&mc->pdev->समय_ref, mc->ts16,
				     &hwts->hwtstamp);
	पूर्ण

	mc->netdev->stats.rx_packets++;
	mc->netdev->stats.rx_bytes += cf->len;
	netअगर_rx(skb);

	वापस 0;
पूर्ण

/* decode bus event usb packet: first byte contains rxerr जबतक 2nd one contains
 * txerr.
 */
अटल पूर्णांक pcan_usb_handle_bus_evt(काष्ठा pcan_usb_msg_context *mc, u8 ir)
अणु
	काष्ठा pcan_usb *pdev = mc->pdev;

	/* acccording to the content of the packet */
	चयन (ir) अणु
	हाल PCAN_USB_ERR_CNT:

		/* save rx/tx error counters from in the device context */
		pdev->bec.rxerr = mc->ptr[0];
		pdev->bec.txerr = mc->ptr[1];
		अवरोध;

	शेष:
		/* reserved */
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * decode non-data usb message
 */
अटल पूर्णांक pcan_usb_decode_status(काष्ठा pcan_usb_msg_context *mc,
				  u8 status_len)
अणु
	u8 rec_len = status_len & PCAN_USB_STATUSLEN_DLC;
	u8 f, n;
	पूर्णांक err;

	/* check whether function and number can be पढ़ो */
	अगर ((mc->ptr + 2) > mc->end)
		वापस -EINVAL;

	f = mc->ptr[PCAN_USB_CMD_FUNC];
	n = mc->ptr[PCAN_USB_CMD_NUM];
	mc->ptr += PCAN_USB_CMD_ARGS;

	अगर (status_len & PCAN_USB_STATUSLEN_TIMESTAMP) अणु
		पूर्णांक err = pcan_usb_decode_ts(mc, !mc->rec_ts_idx);

		अगर (err)
			वापस err;

		/* Next packet in the buffer will have a बारtamp on a single
		 * byte
		 */
		mc->rec_ts_idx++;
	पूर्ण

	चयन (f) अणु
	हाल PCAN_USB_REC_ERROR:
		err = pcan_usb_decode_error(mc, n, status_len);
		अगर (err)
			वापस err;
		अवरोध;

	हाल PCAN_USB_REC_ANALOG:
		/* analog values (ignored) */
		rec_len = 2;
		अवरोध;

	हाल PCAN_USB_REC_BUSLOAD:
		/* bus load (ignored) */
		rec_len = 1;
		अवरोध;

	हाल PCAN_USB_REC_TS:
		/* only बारtamp */
		अगर (pcan_usb_update_ts(mc))
			वापस -EINVAL;
		अवरोध;

	हाल PCAN_USB_REC_BUSEVT:
		/* bus event notअगरications (get rxerr/txerr) */
		err = pcan_usb_handle_bus_evt(mc, n);
		अगर (err)
			वापस err;
		अवरोध;
	शेष:
		netdev_err(mc->netdev, "unexpected function %u\n", f);
		अवरोध;
	पूर्ण

	अगर ((mc->ptr + rec_len) > mc->end)
		वापस -EINVAL;

	mc->ptr += rec_len;

	वापस 0;
पूर्ण

/*
 * decode data usb message
 */
अटल पूर्णांक pcan_usb_decode_data(काष्ठा pcan_usb_msg_context *mc, u8 status_len)
अणु
	u8 rec_len = status_len & PCAN_USB_STATUSLEN_DLC;
	काष्ठा sk_buff *skb;
	काष्ठा can_frame *cf;
	काष्ठा skb_shared_hwtstamps *hwts;

	skb = alloc_can_skb(mc->netdev, &cf);
	अगर (!skb)
		वापस -ENOMEM;

	अगर (status_len & PCAN_USB_STATUSLEN_EXT_ID) अणु
		अगर ((mc->ptr + 4) > mc->end)
			जाओ decode_failed;

		cf->can_id = get_unaligned_le32(mc->ptr) >> 3 | CAN_EFF_FLAG;
		mc->ptr += 4;
	पूर्ण अन्यथा अणु
		अगर ((mc->ptr + 2) > mc->end)
			जाओ decode_failed;

		cf->can_id = get_unaligned_le16(mc->ptr) >> 5;
		mc->ptr += 2;
	पूर्ण

	can_frame_set_cc_len(cf, rec_len, mc->pdev->dev.can.ctrlmode);

	/* Only first packet बारtamp is a word */
	अगर (pcan_usb_decode_ts(mc, !mc->rec_ts_idx))
		जाओ decode_failed;

	/* Next packet in the buffer will have a बारtamp on a single byte */
	mc->rec_ts_idx++;

	/* पढ़ो data */
	स_रखो(cf->data, 0x0, माप(cf->data));
	अगर (status_len & PCAN_USB_STATUSLEN_RTR) अणु
		cf->can_id |= CAN_RTR_FLAG;
	पूर्ण अन्यथा अणु
		अगर ((mc->ptr + rec_len) > mc->end)
			जाओ decode_failed;

		स_नकल(cf->data, mc->ptr, cf->len);
		mc->ptr += rec_len;
	पूर्ण

	/* convert बारtamp पूर्णांकo kernel समय */
	hwts = skb_hwtstamps(skb);
	peak_usb_get_ts_समय(&mc->pdev->समय_ref, mc->ts16, &hwts->hwtstamp);

	/* update statistics */
	mc->netdev->stats.rx_packets++;
	mc->netdev->stats.rx_bytes += cf->len;
	/* push the skb */
	netअगर_rx(skb);

	वापस 0;

decode_failed:
	dev_kमुक्त_skb(skb);
	वापस -EINVAL;
पूर्ण

/*
 * process incoming message
 */
अटल पूर्णांक pcan_usb_decode_msg(काष्ठा peak_usb_device *dev, u8 *ibuf, u32 lbuf)
अणु
	काष्ठा pcan_usb_msg_context mc = अणु
		.rec_cnt = ibuf[1],
		.ptr = ibuf + PCAN_USB_MSG_HEADER_LEN,
		.end = ibuf + lbuf,
		.netdev = dev->netdev,
		.pdev = container_of(dev, काष्ठा pcan_usb, dev),
	पूर्ण;
	पूर्णांक err;

	क्रम (err = 0; mc.rec_idx < mc.rec_cnt && !err; mc.rec_idx++) अणु
		u8 sl = *mc.ptr++;

		/* handle status and error frames here */
		अगर (sl & PCAN_USB_STATUSLEN_INTERNAL) अणु
			err = pcan_usb_decode_status(&mc, sl);
		/* handle normal can frames here */
		पूर्ण अन्यथा अणु
			err = pcan_usb_decode_data(&mc, sl);
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

/*
 * process any incoming buffer
 */
अटल पूर्णांक pcan_usb_decode_buf(काष्ठा peak_usb_device *dev, काष्ठा urb *urb)
अणु
	पूर्णांक err = 0;

	अगर (urb->actual_length > PCAN_USB_MSG_HEADER_LEN) अणु
		err = pcan_usb_decode_msg(dev, urb->transfer_buffer,
			urb->actual_length);

	पूर्ण अन्यथा अगर (urb->actual_length > 0) अणु
		netdev_err(dev->netdev, "usb message length error (%u)\n",
			urb->actual_length);
		err = -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

/*
 * process outgoing packet
 */
अटल पूर्णांक pcan_usb_encode_msg(काष्ठा peak_usb_device *dev, काष्ठा sk_buff *skb,
			       u8 *obuf, माप_प्रकार *size)
अणु
	काष्ठा net_device *netdev = dev->netdev;
	काष्ठा net_device_stats *stats = &netdev->stats;
	काष्ठा can_frame *cf = (काष्ठा can_frame *)skb->data;
	u8 *pc;

	obuf[0] = 2;
	obuf[1] = 1;

	pc = obuf + PCAN_USB_MSG_HEADER_LEN;

	/* status/len byte */
	*pc = can_get_cc_dlc(cf, dev->can.ctrlmode);

	अगर (cf->can_id & CAN_RTR_FLAG)
		*pc |= PCAN_USB_STATUSLEN_RTR;

	/* can id */
	अगर (cf->can_id & CAN_EFF_FLAG) अणु
		*pc |= PCAN_USB_STATUSLEN_EXT_ID;
		pc++;

		put_unaligned_le32((cf->can_id & CAN_ERR_MASK) << 3, pc);
		pc += 4;
	पूर्ण अन्यथा अणु
		pc++;

		put_unaligned_le16((cf->can_id & CAN_ERR_MASK) << 5, pc);
		pc += 2;
	पूर्ण

	/* can data */
	अगर (!(cf->can_id & CAN_RTR_FLAG)) अणु
		स_नकल(pc, cf->data, cf->len);
		pc += cf->len;
	पूर्ण

	obuf[(*size)-1] = (u8)(stats->tx_packets & 0xff);

	वापस 0;
पूर्ण

/* socket callback used to copy berr counters values received through USB */
अटल पूर्णांक pcan_usb_get_berr_counter(स्थिर काष्ठा net_device *netdev,
				     काष्ठा can_berr_counter *bec)
अणु
	काष्ठा peak_usb_device *dev = netdev_priv(netdev);
	काष्ठा pcan_usb *pdev = container_of(dev, काष्ठा pcan_usb, dev);

	*bec = pdev->bec;

	/* must वापस 0 */
	वापस 0;
पूर्ण

/*
 * start पूर्णांकerface
 */
अटल पूर्णांक pcan_usb_start(काष्ठा peak_usb_device *dev)
अणु
	काष्ठा pcan_usb *pdev = container_of(dev, काष्ठा pcan_usb, dev);
	पूर्णांक err;

	/* number of bits used in बारtamps पढ़ो from adapter काष्ठा */
	peak_usb_init_समय_ref(&pdev->समय_ref, &pcan_usb);

	pdev->bec.rxerr = 0;
	pdev->bec.txerr = 0;

	/* be notअगरied on error counter changes (अगर requested by user) */
	अगर (dev->can.ctrlmode & CAN_CTRLMODE_BERR_REPORTING) अणु
		err = pcan_usb_set_err_frame(dev, PCAN_USB_BERR_MASK);
		अगर (err)
			netdev_warn(dev->netdev,
				    "Asking for BERR reporting error %u\n",
				    err);
	पूर्ण

	/* अगर revision greater than 3, can put silent mode on/off */
	अगर (dev->device_rev > 3) अणु
		err = pcan_usb_set_silent(dev,
				dev->can.ctrlmode & CAN_CTRLMODE_LISTENONLY);
		अगर (err)
			वापस err;
	पूर्ण

	वापस pcan_usb_set_ext_vcc(dev, 0);
पूर्ण

अटल पूर्णांक pcan_usb_init(काष्ठा peak_usb_device *dev)
अणु
	काष्ठा pcan_usb *pdev = container_of(dev, काष्ठा pcan_usb, dev);
	u32 serial_number;
	पूर्णांक err;

	/* initialize a समयr needed to रुको क्रम hardware restart */
	समयr_setup(&pdev->restart_समयr, pcan_usb_restart, 0);

	/*
	 * explicit use of dev_xxx() instead of netdev_xxx() here:
	 * inक्रमmation displayed are related to the device itself, not
	 * to the canx netdevice.
	 */
	err = pcan_usb_get_serial(dev, &serial_number);
	अगर (err) अणु
		dev_err(dev->netdev->dev.parent,
			"unable to read %s serial number (err %d)\n",
			pcan_usb.name, err);
		वापस err;
	पूर्ण

	dev_info(dev->netdev->dev.parent,
		 "PEAK-System %s adapter hwrev %u serial %08X (%u channel)\n",
		 pcan_usb.name, dev->device_rev, serial_number,
		 pcan_usb.ctrl_count);

	वापस 0;
पूर्ण

/*
 * probe function क्रम new PCAN-USB usb पूर्णांकerface
 */
अटल पूर्णांक pcan_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_host_पूर्णांकerface *अगर_desc;
	पूर्णांक i;

	अगर_desc = पूर्णांकf->altsetting;

	/* check पूर्णांकerface endpoपूर्णांक addresses */
	क्रम (i = 0; i < अगर_desc->desc.bNumEndpoपूर्णांकs; i++) अणु
		काष्ठा usb_endpoपूर्णांक_descriptor *ep = &अगर_desc->endpoपूर्णांक[i].desc;

		चयन (ep->bEndpoपूर्णांकAddress) अणु
		हाल PCAN_USB_EP_CMDOUT:
		हाल PCAN_USB_EP_CMDIN:
		हाल PCAN_USB_EP_MSGOUT:
		हाल PCAN_USB_EP_MSGIN:
			अवरोध;
		शेष:
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pcan_usb_set_phys_id(काष्ठा net_device *netdev,
				क्रमागत ethtool_phys_id_state state)
अणु
	काष्ठा peak_usb_device *dev = netdev_priv(netdev);
	पूर्णांक err = 0;

	चयन (state) अणु
	हाल ETHTOOL_ID_ACTIVE:
		/* call ON/OFF twice a second */
		वापस 2;

	हाल ETHTOOL_ID_OFF:
		err = pcan_usb_set_led(dev, 0);
		अवरोध;

	हाल ETHTOOL_ID_ON:
		fallthrough;

	हाल ETHTOOL_ID_INACTIVE:
		/* restore LED शेष */
		err = pcan_usb_set_led(dev, 1);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops pcan_usb_ethtool_ops = अणु
	.set_phys_id = pcan_usb_set_phys_id,
पूर्ण;

/*
 * describe the PCAN-USB adapter
 */
अटल स्थिर काष्ठा can_bittiming_स्थिर pcan_usb_स्थिर = अणु
	.name = "pcan_usb",
	.tseg1_min = 1,
	.tseg1_max = 16,
	.tseg2_min = 1,
	.tseg2_max = 8,
	.sjw_max = 4,
	.brp_min = 1,
	.brp_max = 64,
	.brp_inc = 1,
पूर्ण;

स्थिर काष्ठा peak_usb_adapter pcan_usb = अणु
	.name = "PCAN-USB",
	.device_id = PCAN_USB_PRODUCT_ID,
	.ctrl_count = 1,
	.ctrlmode_supported = CAN_CTRLMODE_3_SAMPLES | CAN_CTRLMODE_LISTENONLY |
			      CAN_CTRLMODE_BERR_REPORTING |
			      CAN_CTRLMODE_CC_LEN8_DLC,
	.घड़ी = अणु
		.freq = PCAN_USB_CRYSTAL_HZ / 2,
	पूर्ण,
	.bittiming_स्थिर = &pcan_usb_स्थिर,

	/* size of device निजी data */
	.माप_dev_निजी = माप(काष्ठा pcan_usb),

	.ethtool_ops = &pcan_usb_ethtool_ops,

	/* बारtamps usage */
	.ts_used_bits = 16,
	.us_per_ts_scale = PCAN_USB_TS_US_PER_TICK, /* us=(ts*scale) */
	.us_per_ts_shअगरt = PCAN_USB_TS_DIV_SHIFTER, /*  >> shअगरt     */

	/* give here messages in/out endpoपूर्णांकs */
	.ep_msg_in = PCAN_USB_EP_MSGIN,
	.ep_msg_out = अणुPCAN_USB_EP_MSGOUTपूर्ण,

	/* size of rx/tx usb buffers */
	.rx_buffer_size = PCAN_USB_RX_BUFFER_SIZE,
	.tx_buffer_size = PCAN_USB_TX_BUFFER_SIZE,

	/* device callbacks */
	.पूर्णांकf_probe = pcan_usb_probe,
	.dev_init = pcan_usb_init,
	.dev_set_bus = pcan_usb_ग_लिखो_mode,
	.dev_set_bittiming = pcan_usb_set_bittiming,
	.dev_get_device_id = pcan_usb_get_device_id,
	.dev_decode_buf = pcan_usb_decode_buf,
	.dev_encode_msg = pcan_usb_encode_msg,
	.dev_start = pcan_usb_start,
	.dev_restart_async = pcan_usb_restart_async,
	.करो_get_berr_counter = pcan_usb_get_berr_counter,
पूर्ण;
