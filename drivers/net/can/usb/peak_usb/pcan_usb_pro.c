<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * CAN driver क्रम PEAK System PCAN-USB Pro adapter
 * Derived from the PCAN project file driver/src/pcan_usbpro.c
 *
 * Copyright (C) 2003-2011 PEAK System-Technik GmbH
 * Copyright (C) 2011-2012 Stephane Grosjean <s.grosjean@peak-प्रणाली.com>
 */
#समावेश <linux/netdevice.h>
#समावेश <linux/usb.h>
#समावेश <linux/module.h>
#समावेश <linux/ethtool.h>

#समावेश <linux/can.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/can/error.h>

#समावेश "pcan_usb_core.h"
#समावेश "pcan_usb_pro.h"

#घोषणा PCAN_USBPRO_CHANNEL_COUNT	2

/* PCAN-USB Pro adapter पूर्णांकernal घड़ी (MHz) */
#घोषणा PCAN_USBPRO_CRYSTAL_HZ		56000000

/* PCAN-USB Pro command समयout (ms.) */
#घोषणा PCAN_USBPRO_COMMAND_TIMEOUT	1000

/* PCAN-USB Pro rx/tx buffers size */
#घोषणा PCAN_USBPRO_RX_BUFFER_SIZE	1024
#घोषणा PCAN_USBPRO_TX_BUFFER_SIZE	64

#घोषणा PCAN_USBPRO_MSG_HEADER_LEN	4

/* some commands responses need to be re-submitted */
#घोषणा PCAN_USBPRO_RSP_SUBMIT_MAX	2

#घोषणा PCAN_USBPRO_RTR			0x01
#घोषणा PCAN_USBPRO_EXT			0x02
#घोषणा PCAN_USBPRO_SS			0x08

#घोषणा PCAN_USBPRO_CMD_BUFFER_SIZE	512

/* handle device specअगरic info used by the netdevices */
काष्ठा pcan_usb_pro_पूर्णांकerface अणु
	काष्ठा peak_usb_device *dev[PCAN_USBPRO_CHANNEL_COUNT];
	काष्ठा peak_समय_ref समय_ref;
	पूर्णांक cm_ignore_count;
	पूर्णांक dev_खोलोed_count;
पूर्ण;

/* device inक्रमmation */
काष्ठा pcan_usb_pro_device अणु
	काष्ठा peak_usb_device dev;
	काष्ठा pcan_usb_pro_पूर्णांकerface *usb_अगर;
	u32 cached_ccbt;
पूर्ण;

/* पूर्णांकernal काष्ठाure used to handle messages sent to bulk urb */
काष्ठा pcan_usb_pro_msg अणु
	u8 *rec_ptr;
	पूर्णांक rec_buffer_size;
	पूर्णांक rec_buffer_len;
	जोड़ अणु
		__le16 *rec_cnt_rd;
		__le32 *rec_cnt;
		u8 *rec_buffer;
	पूर्ण u;
पूर्ण;

/* records sizes table indexed on message id. (8-bits value) */
अटल u16 pcan_usb_pro_माप_rec[256] = अणु
	[PCAN_USBPRO_SETBTR] = माप(काष्ठा pcan_usb_pro_btr),
	[PCAN_USBPRO_SETBUSACT] = माप(काष्ठा pcan_usb_pro_busact),
	[PCAN_USBPRO_SETSILENT] = माप(काष्ठा pcan_usb_pro_silent),
	[PCAN_USBPRO_SETFILTR] = माप(काष्ठा pcan_usb_pro_filter),
	[PCAN_USBPRO_SETTS] = माप(काष्ठा pcan_usb_pro_setts),
	[PCAN_USBPRO_GETDEVID] = माप(काष्ठा pcan_usb_pro_devid),
	[PCAN_USBPRO_SETLED] = माप(काष्ठा pcan_usb_pro_setled),
	[PCAN_USBPRO_RXMSG8] = माप(काष्ठा pcan_usb_pro_rxmsg),
	[PCAN_USBPRO_RXMSG4] = माप(काष्ठा pcan_usb_pro_rxmsg) - 4,
	[PCAN_USBPRO_RXMSG0] = माप(काष्ठा pcan_usb_pro_rxmsg) - 8,
	[PCAN_USBPRO_RXRTR] = माप(काष्ठा pcan_usb_pro_rxmsg) - 8,
	[PCAN_USBPRO_RXSTATUS] = माप(काष्ठा pcan_usb_pro_rxstatus),
	[PCAN_USBPRO_RXTS] = माप(काष्ठा pcan_usb_pro_rxts),
	[PCAN_USBPRO_TXMSG8] = माप(काष्ठा pcan_usb_pro_txmsg),
	[PCAN_USBPRO_TXMSG4] = माप(काष्ठा pcan_usb_pro_txmsg) - 4,
	[PCAN_USBPRO_TXMSG0] = माप(काष्ठा pcan_usb_pro_txmsg) - 8,
पूर्ण;

/*
 * initialize PCAN-USB Pro message data काष्ठाure
 */
अटल u8 *pcan_msg_init(काष्ठा pcan_usb_pro_msg *pm, व्योम *buffer_addr,
			 पूर्णांक buffer_size)
अणु
	अगर (buffer_size < PCAN_USBPRO_MSG_HEADER_LEN)
		वापस शून्य;

	pm->u.rec_buffer = (u8 *)buffer_addr;
	pm->rec_buffer_size = pm->rec_buffer_len = buffer_size;
	pm->rec_ptr = pm->u.rec_buffer + PCAN_USBPRO_MSG_HEADER_LEN;

	वापस pm->rec_ptr;
पूर्ण

अटल u8 *pcan_msg_init_empty(काष्ठा pcan_usb_pro_msg *pm,
			       व्योम *buffer_addr, पूर्णांक buffer_size)
अणु
	u8 *pr = pcan_msg_init(pm, buffer_addr, buffer_size);

	अगर (pr) अणु
		pm->rec_buffer_len = PCAN_USBPRO_MSG_HEADER_LEN;
		*pm->u.rec_cnt = 0;
	पूर्ण
	वापस pr;
पूर्ण

/*
 * add one record to a message being built
 */
अटल पूर्णांक pcan_msg_add_rec(काष्ठा pcan_usb_pro_msg *pm, पूर्णांक id, ...)
अणु
	पूर्णांक len, i;
	u8 *pc;
	बहु_सूची ap;

	बहु_शुरू(ap, id);

	pc = pm->rec_ptr + 1;

	i = 0;
	चयन (id) अणु
	हाल PCAN_USBPRO_TXMSG8:
		i += 4;
		fallthrough;
	हाल PCAN_USBPRO_TXMSG4:
		i += 4;
		fallthrough;
	हाल PCAN_USBPRO_TXMSG0:
		*pc++ = बहु_तर्क(ap, पूर्णांक);
		*pc++ = बहु_तर्क(ap, पूर्णांक);
		*pc++ = बहु_तर्क(ap, पूर्णांक);
		*(__le32 *)pc = cpu_to_le32(बहु_तर्क(ap, u32));
		pc += 4;
		स_नकल(pc, बहु_तर्क(ap, पूर्णांक *), i);
		pc += i;
		अवरोध;

	हाल PCAN_USBPRO_SETBTR:
	हाल PCAN_USBPRO_GETDEVID:
		*pc++ = बहु_तर्क(ap, पूर्णांक);
		pc += 2;
		*(__le32 *)pc = cpu_to_le32(बहु_तर्क(ap, u32));
		pc += 4;
		अवरोध;

	हाल PCAN_USBPRO_SETFILTR:
	हाल PCAN_USBPRO_SETBUSACT:
	हाल PCAN_USBPRO_SETSILENT:
		*pc++ = बहु_तर्क(ap, पूर्णांक);
		*(__le16 *)pc = cpu_to_le16(बहु_तर्क(ap, पूर्णांक));
		pc += 2;
		अवरोध;

	हाल PCAN_USBPRO_SETLED:
		*pc++ = बहु_तर्क(ap, पूर्णांक);
		*(__le16 *)pc = cpu_to_le16(बहु_तर्क(ap, पूर्णांक));
		pc += 2;
		*(__le32 *)pc = cpu_to_le32(बहु_तर्क(ap, u32));
		pc += 4;
		अवरोध;

	हाल PCAN_USBPRO_SETTS:
		pc++;
		*(__le16 *)pc = cpu_to_le16(बहु_तर्क(ap, पूर्णांक));
		pc += 2;
		अवरोध;

	शेष:
		pr_err("%s: %s(): unknown data type %02Xh (%d)\n",
			PCAN_USB_DRIVER_NAME, __func__, id, id);
		pc--;
		अवरोध;
	पूर्ण

	len = pc - pm->rec_ptr;
	अगर (len > 0) अणु
		le32_add_cpu(pm->u.rec_cnt, 1);
		*pm->rec_ptr = id;

		pm->rec_ptr = pc;
		pm->rec_buffer_len += len;
	पूर्ण

	बहु_पूर्ण(ap);

	वापस len;
पूर्ण

/*
 * send PCAN-USB Pro command synchronously
 */
अटल पूर्णांक pcan_usb_pro_send_cmd(काष्ठा peak_usb_device *dev,
				 काष्ठा pcan_usb_pro_msg *pum)
अणु
	पूर्णांक actual_length;
	पूर्णांक err;

	/* usb device unरेजिस्टरed? */
	अगर (!(dev->state & PCAN_USB_STATE_CONNECTED))
		वापस 0;

	err = usb_bulk_msg(dev->udev,
		usb_sndbulkpipe(dev->udev, PCAN_USBPRO_EP_CMDOUT),
		pum->u.rec_buffer, pum->rec_buffer_len,
		&actual_length, PCAN_USBPRO_COMMAND_TIMEOUT);
	अगर (err)
		netdev_err(dev->netdev, "sending command failure: %d\n", err);

	वापस err;
पूर्ण

/*
 * रुको क्रम PCAN-USB Pro command response
 */
अटल पूर्णांक pcan_usb_pro_रुको_rsp(काष्ठा peak_usb_device *dev,
				 काष्ठा pcan_usb_pro_msg *pum)
अणु
	u8 req_data_type, req_channel;
	पूर्णांक actual_length;
	पूर्णांक i, err = 0;

	/* usb device unरेजिस्टरed? */
	अगर (!(dev->state & PCAN_USB_STATE_CONNECTED))
		वापस 0;

	req_data_type = pum->u.rec_buffer[4];
	req_channel = pum->u.rec_buffer[5];

	*pum->u.rec_cnt = 0;
	क्रम (i = 0; !err && i < PCAN_USBPRO_RSP_SUBMIT_MAX; i++) अणु
		काष्ठा pcan_usb_pro_msg rsp;
		जोड़ pcan_usb_pro_rec *pr;
		u32 r, rec_cnt;
		u16 rec_len;
		u8 *pc;

		err = usb_bulk_msg(dev->udev,
			usb_rcvbulkpipe(dev->udev, PCAN_USBPRO_EP_CMDIN),
			pum->u.rec_buffer, pum->rec_buffer_len,
			&actual_length, PCAN_USBPRO_COMMAND_TIMEOUT);
		अगर (err) अणु
			netdev_err(dev->netdev, "waiting rsp error %d\n", err);
			अवरोध;
		पूर्ण

		अगर (actual_length == 0)
			जारी;

		err = -EBADMSG;
		अगर (actual_length < PCAN_USBPRO_MSG_HEADER_LEN) अणु
			netdev_err(dev->netdev,
				   "got abnormal too small rsp (len=%d)\n",
				   actual_length);
			अवरोध;
		पूर्ण

		pc = pcan_msg_init(&rsp, pum->u.rec_buffer,
			actual_length);

		rec_cnt = le32_to_cpu(*rsp.u.rec_cnt);

		/* loop on records stored पूर्णांकo message */
		क्रम (r = 0; r < rec_cnt; r++) अणु
			pr = (जोड़ pcan_usb_pro_rec *)pc;
			rec_len = pcan_usb_pro_माप_rec[pr->data_type];
			अगर (!rec_len) अणु
				netdev_err(dev->netdev,
					   "got unprocessed record in msg\n");
				pcan_dump_mem("rcvd rsp msg", pum->u.rec_buffer,
					      actual_length);
				अवरोध;
			पूर्ण

			/* check अगर response corresponds to request */
			अगर (pr->data_type != req_data_type)
				netdev_err(dev->netdev,
					   "got unwanted rsp %xh: ignored\n",
					   pr->data_type);

			/* check अगर channel in response corresponds too */
			अन्यथा अगर ((req_channel != 0xff) &&
				(pr->bus_act.channel != req_channel))
				netdev_err(dev->netdev,
					"got rsp %xh but on chan%u: ignored\n",
					req_data_type, pr->bus_act.channel);

			/* got the response */
			अन्यथा
				वापस 0;

			/* otherwise, go on with next record in message */
			pc += rec_len;
		पूर्ण
	पूर्ण

	वापस (i >= PCAN_USBPRO_RSP_SUBMIT_MAX) ? -दुस्फल : err;
पूर्ण

पूर्णांक pcan_usb_pro_send_req(काष्ठा peak_usb_device *dev, पूर्णांक req_id,
			  पूर्णांक req_value, व्योम *req_addr, पूर्णांक req_size)
अणु
	पूर्णांक err;
	u8 req_type;
	अचिन्हित पूर्णांक p;

	/* usb device unरेजिस्टरed? */
	अगर (!(dev->state & PCAN_USB_STATE_CONNECTED))
		वापस 0;

	req_type = USB_TYPE_VENDOR | USB_RECIP_OTHER;

	चयन (req_id) अणु
	हाल PCAN_USBPRO_REQ_FCT:
		p = usb_sndctrlpipe(dev->udev, 0);
		अवरोध;

	शेष:
		p = usb_rcvctrlpipe(dev->udev, 0);
		req_type |= USB_सूची_IN;
		स_रखो(req_addr, '\0', req_size);
		अवरोध;
	पूर्ण

	err = usb_control_msg(dev->udev, p, req_id, req_type, req_value, 0,
			      req_addr, req_size, 2 * USB_CTRL_GET_TIMEOUT);
	अगर (err < 0) अणु
		netdev_info(dev->netdev,
			    "unable to request usb[type=%d value=%d] err=%d\n",
			    req_id, req_value, err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pcan_usb_pro_set_ts(काष्ठा peak_usb_device *dev, u16 onoff)
अणु
	काष्ठा pcan_usb_pro_msg um;

	pcan_msg_init_empty(&um, dev->cmd_buf, PCAN_USB_MAX_CMD_LEN);
	pcan_msg_add_rec(&um, PCAN_USBPRO_SETTS, onoff);

	वापस pcan_usb_pro_send_cmd(dev, &um);
पूर्ण

अटल पूर्णांक pcan_usb_pro_set_bitrate(काष्ठा peak_usb_device *dev, u32 ccbt)
अणु
	काष्ठा pcan_usb_pro_device *pdev =
			container_of(dev, काष्ठा pcan_usb_pro_device, dev);
	काष्ठा pcan_usb_pro_msg um;

	pcan_msg_init_empty(&um, dev->cmd_buf, PCAN_USB_MAX_CMD_LEN);
	pcan_msg_add_rec(&um, PCAN_USBPRO_SETBTR, dev->ctrl_idx, ccbt);

	/* cache the CCBT value to reuse it beक्रमe next buson */
	pdev->cached_ccbt = ccbt;

	वापस pcan_usb_pro_send_cmd(dev, &um);
पूर्ण

अटल पूर्णांक pcan_usb_pro_set_bus(काष्ठा peak_usb_device *dev, u8 onoff)
अणु
	काष्ठा pcan_usb_pro_msg um;

	/* अगर bus=on, be sure the bitrate being set beक्रमe! */
	अगर (onoff) अणु
		काष्ठा pcan_usb_pro_device *pdev =
			     container_of(dev, काष्ठा pcan_usb_pro_device, dev);

		pcan_usb_pro_set_bitrate(dev, pdev->cached_ccbt);
	पूर्ण

	pcan_msg_init_empty(&um, dev->cmd_buf, PCAN_USB_MAX_CMD_LEN);
	pcan_msg_add_rec(&um, PCAN_USBPRO_SETBUSACT, dev->ctrl_idx, onoff);

	वापस pcan_usb_pro_send_cmd(dev, &um);
पूर्ण

अटल पूर्णांक pcan_usb_pro_set_silent(काष्ठा peak_usb_device *dev, u8 onoff)
अणु
	काष्ठा pcan_usb_pro_msg um;

	pcan_msg_init_empty(&um, dev->cmd_buf, PCAN_USB_MAX_CMD_LEN);
	pcan_msg_add_rec(&um, PCAN_USBPRO_SETSILENT, dev->ctrl_idx, onoff);

	वापस pcan_usb_pro_send_cmd(dev, &um);
पूर्ण

अटल पूर्णांक pcan_usb_pro_set_filter(काष्ठा peak_usb_device *dev, u16 filter_mode)
अणु
	काष्ठा pcan_usb_pro_msg um;

	pcan_msg_init_empty(&um, dev->cmd_buf, PCAN_USB_MAX_CMD_LEN);
	pcan_msg_add_rec(&um, PCAN_USBPRO_SETFILTR, dev->ctrl_idx, filter_mode);

	वापस pcan_usb_pro_send_cmd(dev, &um);
पूर्ण

अटल पूर्णांक pcan_usb_pro_set_led(काष्ठा peak_usb_device *dev, u8 mode,
				u32 समयout)
अणु
	काष्ठा pcan_usb_pro_msg um;

	pcan_msg_init_empty(&um, dev->cmd_buf, PCAN_USB_MAX_CMD_LEN);
	pcan_msg_add_rec(&um, PCAN_USBPRO_SETLED, dev->ctrl_idx, mode, समयout);

	वापस pcan_usb_pro_send_cmd(dev, &um);
पूर्ण

अटल पूर्णांक pcan_usb_pro_get_device_id(काष्ठा peak_usb_device *dev,
				      u32 *device_id)
अणु
	काष्ठा pcan_usb_pro_devid *pdn;
	काष्ठा pcan_usb_pro_msg um;
	पूर्णांक err;
	u8 *pc;

	pc = pcan_msg_init_empty(&um, dev->cmd_buf, PCAN_USB_MAX_CMD_LEN);
	pcan_msg_add_rec(&um, PCAN_USBPRO_GETDEVID, dev->ctrl_idx);

	err =  pcan_usb_pro_send_cmd(dev, &um);
	अगर (err)
		वापस err;

	err = pcan_usb_pro_रुको_rsp(dev, &um);
	अगर (err)
		वापस err;

	pdn = (काष्ठा pcan_usb_pro_devid *)pc;
	*device_id = le32_to_cpu(pdn->serial_num);

	वापस err;
पूर्ण

अटल पूर्णांक pcan_usb_pro_set_bittiming(काष्ठा peak_usb_device *dev,
				      काष्ठा can_bittiming *bt)
अणु
	u32 ccbt;

	ccbt = (dev->can.ctrlmode & CAN_CTRLMODE_3_SAMPLES) ? 0x00800000 : 0;
	ccbt |= (bt->sjw - 1) << 24;
	ccbt |= (bt->phase_seg2 - 1) << 20;
	ccbt |= (bt->prop_seg + bt->phase_seg1 - 1) << 16; /* = tseg1 */
	ccbt |= bt->brp - 1;

	netdev_info(dev->netdev, "setting ccbt=0x%08x\n", ccbt);

	वापस pcan_usb_pro_set_bitrate(dev, ccbt);
पूर्ण

व्योम pcan_usb_pro_restart_complete(काष्ठा urb *urb)
अणु
	/* can delete usb resources */
	peak_usb_async_complete(urb);

	/* notअगरy candev and netdev */
	peak_usb_restart_complete(urb->context);
पूर्ण

/*
 * handle restart but in asynchronously way
 */
अटल पूर्णांक pcan_usb_pro_restart_async(काष्ठा peak_usb_device *dev,
				      काष्ठा urb *urb, u8 *buf)
अणु
	काष्ठा pcan_usb_pro_msg um;

	pcan_msg_init_empty(&um, buf, PCAN_USB_MAX_CMD_LEN);
	pcan_msg_add_rec(&um, PCAN_USBPRO_SETBUSACT, dev->ctrl_idx, 1);

	usb_fill_bulk_urb(urb, dev->udev,
			usb_sndbulkpipe(dev->udev, PCAN_USBPRO_EP_CMDOUT),
			buf, PCAN_USB_MAX_CMD_LEN,
			pcan_usb_pro_restart_complete, dev);

	वापस usb_submit_urb(urb, GFP_ATOMIC);
पूर्ण

अटल पूर्णांक pcan_usb_pro_drv_loaded(काष्ठा peak_usb_device *dev, पूर्णांक loaded)
अणु
	u8 *buffer;
	पूर्णांक err;

	buffer = kzalloc(PCAN_USBPRO_FCT_DRVLD_REQ_LEN, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	buffer[0] = 0;
	buffer[1] = !!loaded;

	err = pcan_usb_pro_send_req(dev, PCAN_USBPRO_REQ_FCT,
				    PCAN_USBPRO_FCT_DRVLD, buffer,
				    PCAN_USBPRO_FCT_DRVLD_REQ_LEN);
	kमुक्त(buffer);

	वापस err;
पूर्ण

अटल अंतरभूत
काष्ठा pcan_usb_pro_पूर्णांकerface *pcan_usb_pro_dev_अगर(काष्ठा peak_usb_device *dev)
अणु
	काष्ठा pcan_usb_pro_device *pdev =
			container_of(dev, काष्ठा pcan_usb_pro_device, dev);
	वापस pdev->usb_अगर;
पूर्ण

अटल पूर्णांक pcan_usb_pro_handle_canmsg(काष्ठा pcan_usb_pro_पूर्णांकerface *usb_अगर,
				      काष्ठा pcan_usb_pro_rxmsg *rx)
अणु
	स्थिर अचिन्हित पूर्णांक ctrl_idx = (rx->len >> 4) & 0x0f;
	काष्ठा peak_usb_device *dev = usb_अगर->dev[ctrl_idx];
	काष्ठा net_device *netdev = dev->netdev;
	काष्ठा can_frame *can_frame;
	काष्ठा sk_buff *skb;
	काष्ठा skb_shared_hwtstamps *hwts;

	skb = alloc_can_skb(netdev, &can_frame);
	अगर (!skb)
		वापस -ENOMEM;

	can_frame->can_id = le32_to_cpu(rx->id);
	can_frame->len = rx->len & 0x0f;

	अगर (rx->flags & PCAN_USBPRO_EXT)
		can_frame->can_id |= CAN_EFF_FLAG;

	अगर (rx->flags & PCAN_USBPRO_RTR)
		can_frame->can_id |= CAN_RTR_FLAG;
	अन्यथा
		स_नकल(can_frame->data, rx->data, can_frame->len);

	hwts = skb_hwtstamps(skb);
	peak_usb_get_ts_समय(&usb_अगर->समय_ref, le32_to_cpu(rx->ts32),
			     &hwts->hwtstamp);

	netdev->stats.rx_packets++;
	netdev->stats.rx_bytes += can_frame->len;
	netअगर_rx(skb);

	वापस 0;
पूर्ण

अटल पूर्णांक pcan_usb_pro_handle_error(काष्ठा pcan_usb_pro_पूर्णांकerface *usb_अगर,
				     काष्ठा pcan_usb_pro_rxstatus *er)
अणु
	स्थिर u16 raw_status = le16_to_cpu(er->status);
	स्थिर अचिन्हित पूर्णांक ctrl_idx = (er->channel >> 4) & 0x0f;
	काष्ठा peak_usb_device *dev = usb_अगर->dev[ctrl_idx];
	काष्ठा net_device *netdev = dev->netdev;
	काष्ठा can_frame *can_frame;
	क्रमागत can_state new_state = CAN_STATE_ERROR_ACTIVE;
	u8 err_mask = 0;
	काष्ठा sk_buff *skb;
	काष्ठा skb_shared_hwtstamps *hwts;

	/* nothing should be sent जबतक in BUS_OFF state */
	अगर (dev->can.state == CAN_STATE_BUS_OFF)
		वापस 0;

	अगर (!raw_status) अणु
		/* no error bit (back to active state) */
		dev->can.state = CAN_STATE_ERROR_ACTIVE;
		वापस 0;
	पूर्ण

	अगर (raw_status & (PCAN_USBPRO_STATUS_OVERRUN |
			  PCAN_USBPRO_STATUS_QOVERRUN)) अणु
		/* trick to bypass next comparison and process other errors */
		new_state = CAN_STATE_MAX;
	पूर्ण

	अगर (raw_status & PCAN_USBPRO_STATUS_BUS) अणु
		new_state = CAN_STATE_BUS_OFF;
	पूर्ण अन्यथा अगर (raw_status & PCAN_USBPRO_STATUS_ERROR) अणु
		u32 rx_err_cnt = (le32_to_cpu(er->err_frm) & 0x00ff0000) >> 16;
		u32 tx_err_cnt = (le32_to_cpu(er->err_frm) & 0xff000000) >> 24;

		अगर (rx_err_cnt > 127)
			err_mask |= CAN_ERR_CRTL_RX_PASSIVE;
		अन्यथा अगर (rx_err_cnt > 96)
			err_mask |= CAN_ERR_CRTL_RX_WARNING;

		अगर (tx_err_cnt > 127)
			err_mask |= CAN_ERR_CRTL_TX_PASSIVE;
		अन्यथा अगर (tx_err_cnt > 96)
			err_mask |= CAN_ERR_CRTL_TX_WARNING;

		अगर (err_mask & (CAN_ERR_CRTL_RX_WARNING |
				CAN_ERR_CRTL_TX_WARNING))
			new_state = CAN_STATE_ERROR_WARNING;
		अन्यथा अगर (err_mask & (CAN_ERR_CRTL_RX_PASSIVE |
				     CAN_ERR_CRTL_TX_PASSIVE))
			new_state = CAN_STATE_ERROR_PASSIVE;
	पूर्ण

	/* करोnot post any error अगर current state didn't change */
	अगर (dev->can.state == new_state)
		वापस 0;

	/* allocate an skb to store the error frame */
	skb = alloc_can_err_skb(netdev, &can_frame);
	अगर (!skb)
		वापस -ENOMEM;

	चयन (new_state) अणु
	हाल CAN_STATE_BUS_OFF:
		can_frame->can_id |= CAN_ERR_BUSOFF;
		dev->can.can_stats.bus_off++;
		can_bus_off(netdev);
		अवरोध;

	हाल CAN_STATE_ERROR_PASSIVE:
		can_frame->can_id |= CAN_ERR_CRTL;
		can_frame->data[1] |= err_mask;
		dev->can.can_stats.error_passive++;
		अवरोध;

	हाल CAN_STATE_ERROR_WARNING:
		can_frame->can_id |= CAN_ERR_CRTL;
		can_frame->data[1] |= err_mask;
		dev->can.can_stats.error_warning++;
		अवरोध;

	हाल CAN_STATE_ERROR_ACTIVE:
		अवरोध;

	शेष:
		/* CAN_STATE_MAX (trick to handle other errors) */
		अगर (raw_status & PCAN_USBPRO_STATUS_OVERRUN) अणु
			can_frame->can_id |= CAN_ERR_PROT;
			can_frame->data[2] |= CAN_ERR_PROT_OVERLOAD;
			netdev->stats.rx_over_errors++;
			netdev->stats.rx_errors++;
		पूर्ण

		अगर (raw_status & PCAN_USBPRO_STATUS_QOVERRUN) अणु
			can_frame->can_id |= CAN_ERR_CRTL;
			can_frame->data[1] |= CAN_ERR_CRTL_RX_OVERFLOW;
			netdev->stats.rx_over_errors++;
			netdev->stats.rx_errors++;
		पूर्ण

		new_state = CAN_STATE_ERROR_ACTIVE;
		अवरोध;
	पूर्ण

	dev->can.state = new_state;

	hwts = skb_hwtstamps(skb);
	peak_usb_get_ts_समय(&usb_अगर->समय_ref, le32_to_cpu(er->ts32), &hwts->hwtstamp);
	netdev->stats.rx_packets++;
	netdev->stats.rx_bytes += can_frame->len;
	netअगर_rx(skb);

	वापस 0;
पूर्ण

अटल व्योम pcan_usb_pro_handle_ts(काष्ठा pcan_usb_pro_पूर्णांकerface *usb_अगर,
				   काष्ठा pcan_usb_pro_rxts *ts)
अणु
	/* should रुको until घड़ी is stabilized */
	अगर (usb_अगर->cm_ignore_count > 0)
		usb_अगर->cm_ignore_count--;
	अन्यथा
		peak_usb_set_ts_now(&usb_अगर->समय_ref,
				    le32_to_cpu(ts->ts64[1]));
पूर्ण

/*
 * callback क्रम bulk IN urb
 */
अटल पूर्णांक pcan_usb_pro_decode_buf(काष्ठा peak_usb_device *dev, काष्ठा urb *urb)
अणु
	काष्ठा pcan_usb_pro_पूर्णांकerface *usb_अगर = pcan_usb_pro_dev_अगर(dev);
	काष्ठा net_device *netdev = dev->netdev;
	काष्ठा pcan_usb_pro_msg usb_msg;
	u8 *rec_ptr, *msg_end;
	u16 rec_cnt;
	पूर्णांक err = 0;

	rec_ptr = pcan_msg_init(&usb_msg, urb->transfer_buffer,
					urb->actual_length);
	अगर (!rec_ptr) अणु
		netdev_err(netdev, "bad msg hdr len %d\n", urb->actual_length);
		वापस -EINVAL;
	पूर्ण

	/* loop पढ़ोing all the records from the incoming message */
	msg_end = urb->transfer_buffer + urb->actual_length;
	rec_cnt = le16_to_cpu(*usb_msg.u.rec_cnt_rd);
	क्रम (; rec_cnt > 0; rec_cnt--) अणु
		जोड़ pcan_usb_pro_rec *pr = (जोड़ pcan_usb_pro_rec *)rec_ptr;
		u16 माप_rec = pcan_usb_pro_माप_rec[pr->data_type];

		अगर (!माप_rec) अणु
			netdev_err(netdev,
				   "got unsupported rec in usb msg:\n");
			err = -ENOTSUPP;
			अवरोध;
		पूर्ण

		/* check अगर the record goes out of current packet */
		अगर (rec_ptr + माप_rec > msg_end) अणु
			netdev_err(netdev,
				"got frag rec: should inc usb rx buf size\n");
			err = -EBADMSG;
			अवरोध;
		पूर्ण

		चयन (pr->data_type) अणु
		हाल PCAN_USBPRO_RXMSG8:
		हाल PCAN_USBPRO_RXMSG4:
		हाल PCAN_USBPRO_RXMSG0:
		हाल PCAN_USBPRO_RXRTR:
			err = pcan_usb_pro_handle_canmsg(usb_अगर, &pr->rx_msg);
			अगर (err < 0)
				जाओ fail;
			अवरोध;

		हाल PCAN_USBPRO_RXSTATUS:
			err = pcan_usb_pro_handle_error(usb_अगर, &pr->rx_status);
			अगर (err < 0)
				जाओ fail;
			अवरोध;

		हाल PCAN_USBPRO_RXTS:
			pcan_usb_pro_handle_ts(usb_अगर, &pr->rx_ts);
			अवरोध;

		शेष:
			netdev_err(netdev,
				   "unhandled rec type 0x%02x (%d): ignored\n",
				   pr->data_type, pr->data_type);
			अवरोध;
		पूर्ण

		rec_ptr += माप_rec;
	पूर्ण

fail:
	अगर (err)
		pcan_dump_mem("received msg",
			      urb->transfer_buffer, urb->actual_length);

	वापस err;
पूर्ण

अटल पूर्णांक pcan_usb_pro_encode_msg(काष्ठा peak_usb_device *dev,
				   काष्ठा sk_buff *skb, u8 *obuf, माप_प्रकार *size)
अणु
	काष्ठा can_frame *cf = (काष्ठा can_frame *)skb->data;
	u8 data_type, len, flags;
	काष्ठा pcan_usb_pro_msg usb_msg;

	pcan_msg_init_empty(&usb_msg, obuf, *size);

	अगर ((cf->can_id & CAN_RTR_FLAG) || (cf->len == 0))
		data_type = PCAN_USBPRO_TXMSG0;
	अन्यथा अगर (cf->len <= 4)
		data_type = PCAN_USBPRO_TXMSG4;
	अन्यथा
		data_type = PCAN_USBPRO_TXMSG8;

	len = (dev->ctrl_idx << 4) | (cf->len & 0x0f);

	flags = 0;
	अगर (cf->can_id & CAN_EFF_FLAG)
		flags |= PCAN_USBPRO_EXT;
	अगर (cf->can_id & CAN_RTR_FLAG)
		flags |= PCAN_USBPRO_RTR;

	/* Single-Shot frame */
	अगर (dev->can.ctrlmode & CAN_CTRLMODE_ONE_SHOT)
		flags |= PCAN_USBPRO_SS;

	pcan_msg_add_rec(&usb_msg, data_type, 0, flags, len, cf->can_id,
			 cf->data);

	*size = usb_msg.rec_buffer_len;

	वापस 0;
पूर्ण

अटल पूर्णांक pcan_usb_pro_start(काष्ठा peak_usb_device *dev)
अणु
	काष्ठा pcan_usb_pro_device *pdev =
			container_of(dev, काष्ठा pcan_usb_pro_device, dev);
	पूर्णांक err;

	err = pcan_usb_pro_set_silent(dev,
				dev->can.ctrlmode & CAN_CTRLMODE_LISTENONLY);
	अगर (err)
		वापस err;

	/* filter mode: 0-> All OFF; 1->bypass */
	err = pcan_usb_pro_set_filter(dev, 1);
	अगर (err)
		वापस err;

	/* खोलोing first device: */
	अगर (pdev->usb_अगर->dev_खोलोed_count == 0) अणु
		/* reset समय_ref */
		peak_usb_init_समय_ref(&pdev->usb_अगर->समय_ref, &pcan_usb_pro);

		/* ask device to send ts messages */
		err = pcan_usb_pro_set_ts(dev, 1);
	पूर्ण

	pdev->usb_अगर->dev_खोलोed_count++;

	वापस err;
पूर्ण

/*
 * stop पूर्णांकerface
 * (last chance beक्रमe set bus off)
 */
अटल पूर्णांक pcan_usb_pro_stop(काष्ठा peak_usb_device *dev)
अणु
	काष्ठा pcan_usb_pro_device *pdev =
			container_of(dev, काष्ठा pcan_usb_pro_device, dev);

	/* turn off ts msgs क्रम that पूर्णांकerface अगर no other dev खोलोed */
	अगर (pdev->usb_अगर->dev_खोलोed_count == 1)
		pcan_usb_pro_set_ts(dev, 0);

	pdev->usb_अगर->dev_खोलोed_count--;

	वापस 0;
पूर्ण

/*
 * called when probing to initialize a device object.
 */
अटल पूर्णांक pcan_usb_pro_init(काष्ठा peak_usb_device *dev)
अणु
	काष्ठा pcan_usb_pro_device *pdev =
			container_of(dev, काष्ठा pcan_usb_pro_device, dev);
	काष्ठा pcan_usb_pro_पूर्णांकerface *usb_अगर = शून्य;
	काष्ठा pcan_usb_pro_fwinfo *fi = शून्य;
	काष्ठा pcan_usb_pro_blinfo *bi = शून्य;
	पूर्णांक err;

	/* करो this क्रम 1st channel only */
	अगर (!dev->prev_siblings) अणु
		/* allocate netdevices common काष्ठाure attached to first one */
		usb_अगर = kzalloc(माप(काष्ठा pcan_usb_pro_पूर्णांकerface),
				 GFP_KERNEL);
		fi = kदो_स्मृति(माप(काष्ठा pcan_usb_pro_fwinfo), GFP_KERNEL);
		bi = kदो_स्मृति(माप(काष्ठा pcan_usb_pro_blinfo), GFP_KERNEL);
		अगर (!usb_अगर || !fi || !bi) अणु
			err = -ENOMEM;
			जाओ err_out;
		पूर्ण

		/* number of ts msgs to ignore beक्रमe taking one पूर्णांकo account */
		usb_अगर->cm_ignore_count = 5;

		/*
		 * explicit use of dev_xxx() instead of netdev_xxx() here:
		 * inक्रमmation displayed are related to the device itself, not
		 * to the canx netdevices.
		 */
		err = pcan_usb_pro_send_req(dev, PCAN_USBPRO_REQ_INFO,
					    PCAN_USBPRO_INFO_FW,
					    fi, माप(*fi));
		अगर (err) अणु
			dev_err(dev->netdev->dev.parent,
				"unable to read %s firmware info (err %d)\n",
				pcan_usb_pro.name, err);
			जाओ err_out;
		पूर्ण

		err = pcan_usb_pro_send_req(dev, PCAN_USBPRO_REQ_INFO,
					    PCAN_USBPRO_INFO_BL,
					    bi, माप(*bi));
		अगर (err) अणु
			dev_err(dev->netdev->dev.parent,
				"unable to read %s bootloader info (err %d)\n",
				pcan_usb_pro.name, err);
			जाओ err_out;
		पूर्ण

		/* tell the device the can driver is running */
		err = pcan_usb_pro_drv_loaded(dev, 1);
		अगर (err)
			जाओ err_out;

		dev_info(dev->netdev->dev.parent,
		     "PEAK-System %s hwrev %u serial %08X.%08X (%u channels)\n",
		     pcan_usb_pro.name,
		     bi->hw_rev, bi->serial_num_hi, bi->serial_num_lo,
		     pcan_usb_pro.ctrl_count);
	पूर्ण अन्यथा अणु
		usb_अगर = pcan_usb_pro_dev_अगर(dev->prev_siblings);
	पूर्ण

	pdev->usb_अगर = usb_अगर;
	usb_अगर->dev[dev->ctrl_idx] = dev;

	/* set LED in शेष state (end of init phase) */
	pcan_usb_pro_set_led(dev, PCAN_USBPRO_LED_DEVICE, 1);

	kमुक्त(bi);
	kमुक्त(fi);

	वापस 0;

 err_out:
	kमुक्त(bi);
	kमुक्त(fi);
	kमुक्त(usb_अगर);

	वापस err;
पूर्ण

अटल व्योम pcan_usb_pro_निकास(काष्ठा peak_usb_device *dev)
अणु
	काष्ठा pcan_usb_pro_device *pdev =
			container_of(dev, काष्ठा pcan_usb_pro_device, dev);

	/*
	 * when rmmod called beक्रमe unplug and अगर करोwn, should reset things
	 * beक्रमe leaving
	 */
	अगर (dev->can.state != CAN_STATE_STOPPED) अणु
		/* set bus off on the corresponding channel */
		pcan_usb_pro_set_bus(dev, 0);
	पूर्ण

	/* अगर channel #0 (only) */
	अगर (dev->ctrl_idx == 0) अणु
		/* turn off calibration message अगर any device were खोलोed */
		अगर (pdev->usb_अगर->dev_खोलोed_count > 0)
			pcan_usb_pro_set_ts(dev, 0);

		/* tell the PCAN-USB Pro device the driver is being unloaded */
		pcan_usb_pro_drv_loaded(dev, 0);
	पूर्ण
पूर्ण

/*
 * called when PCAN-USB Pro adapter is unplugged
 */
अटल व्योम pcan_usb_pro_मुक्त(काष्ठा peak_usb_device *dev)
अणु
	/* last device: can मुक्त pcan_usb_pro_पूर्णांकerface object now */
	अगर (!dev->prev_siblings && !dev->next_siblings)
		kमुक्त(pcan_usb_pro_dev_अगर(dev));
पूर्ण

/*
 * probe function क्रम new PCAN-USB Pro usb पूर्णांकerface
 */
पूर्णांक pcan_usb_pro_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_host_पूर्णांकerface *अगर_desc;
	पूर्णांक i;

	अगर_desc = पूर्णांकf->altsetting;

	/* check पूर्णांकerface endpoपूर्णांक addresses */
	क्रम (i = 0; i < अगर_desc->desc.bNumEndpoपूर्णांकs; i++) अणु
		काष्ठा usb_endpoपूर्णांक_descriptor *ep = &अगर_desc->endpoपूर्णांक[i].desc;

		/*
		 * below is the list of valid ep addresses. Any other ep address
		 * is considered as not-CAN पूर्णांकerface address => no dev created
		 */
		चयन (ep->bEndpoपूर्णांकAddress) अणु
		हाल PCAN_USBPRO_EP_CMDOUT:
		हाल PCAN_USBPRO_EP_CMDIN:
		हाल PCAN_USBPRO_EP_MSGOUT_0:
		हाल PCAN_USBPRO_EP_MSGOUT_1:
		हाल PCAN_USBPRO_EP_MSGIN:
		हाल PCAN_USBPRO_EP_UNUSED:
			अवरोध;
		शेष:
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pcan_usb_pro_set_phys_id(काष्ठा net_device *netdev,
				    क्रमागत ethtool_phys_id_state state)
अणु
	काष्ठा peak_usb_device *dev = netdev_priv(netdev);
	पूर्णांक err = 0;

	चयन (state) अणु
	हाल ETHTOOL_ID_ACTIVE:
		/* fast blinking क्रमever */
		err = pcan_usb_pro_set_led(dev, PCAN_USBPRO_LED_BLINK_FAST,
					   0xffffffff);
		अवरोध;

	हाल ETHTOOL_ID_INACTIVE:
		/* restore LED शेष */
		err = pcan_usb_pro_set_led(dev, PCAN_USBPRO_LED_DEVICE, 1);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops pcan_usb_pro_ethtool_ops = अणु
	.set_phys_id = pcan_usb_pro_set_phys_id,
पूर्ण;

/*
 * describe the PCAN-USB Pro adapter
 */
अटल स्थिर काष्ठा can_bittiming_स्थिर pcan_usb_pro_स्थिर = अणु
	.name = "pcan_usb_pro",
	.tseg1_min = 1,
	.tseg1_max = 16,
	.tseg2_min = 1,
	.tseg2_max = 8,
	.sjw_max = 4,
	.brp_min = 1,
	.brp_max = 1024,
	.brp_inc = 1,
पूर्ण;

स्थिर काष्ठा peak_usb_adapter pcan_usb_pro = अणु
	.name = "PCAN-USB Pro",
	.device_id = PCAN_USBPRO_PRODUCT_ID,
	.ctrl_count = PCAN_USBPRO_CHANNEL_COUNT,
	.ctrlmode_supported = CAN_CTRLMODE_3_SAMPLES | CAN_CTRLMODE_LISTENONLY |
			      CAN_CTRLMODE_ONE_SHOT,
	.घड़ी = अणु
		.freq = PCAN_USBPRO_CRYSTAL_HZ,
	पूर्ण,
	.bittiming_स्थिर = &pcan_usb_pro_स्थिर,

	/* size of device निजी data */
	.माप_dev_निजी = माप(काष्ठा pcan_usb_pro_device),

	.ethtool_ops = &pcan_usb_pro_ethtool_ops,

	/* बारtamps usage */
	.ts_used_bits = 32,
	.us_per_ts_scale = 1, /* us = (ts * scale) >> shअगरt */
	.us_per_ts_shअगरt = 0,

	/* give here messages in/out endpoपूर्णांकs */
	.ep_msg_in = PCAN_USBPRO_EP_MSGIN,
	.ep_msg_out = अणुPCAN_USBPRO_EP_MSGOUT_0, PCAN_USBPRO_EP_MSGOUT_1पूर्ण,

	/* size of rx/tx usb buffers */
	.rx_buffer_size = PCAN_USBPRO_RX_BUFFER_SIZE,
	.tx_buffer_size = PCAN_USBPRO_TX_BUFFER_SIZE,

	/* device callbacks */
	.पूर्णांकf_probe = pcan_usb_pro_probe,
	.dev_init = pcan_usb_pro_init,
	.dev_निकास = pcan_usb_pro_निकास,
	.dev_मुक्त = pcan_usb_pro_मुक्त,
	.dev_set_bus = pcan_usb_pro_set_bus,
	.dev_set_bittiming = pcan_usb_pro_set_bittiming,
	.dev_get_device_id = pcan_usb_pro_get_device_id,
	.dev_decode_buf = pcan_usb_pro_decode_buf,
	.dev_encode_msg = pcan_usb_pro_encode_msg,
	.dev_start = pcan_usb_pro_start,
	.dev_stop = pcan_usb_pro_stop,
	.dev_restart_async = pcan_usb_pro_restart_async,
पूर्ण;
