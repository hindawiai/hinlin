<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * CAN driver क्रम PEAK System PCAN-USB FD / PCAN-USB Pro FD adapter
 *
 * Copyright (C) 2013-2014 Stephane Grosjean <s.grosjean@peak-प्रणाली.com>
 */
#समावेश <linux/netdevice.h>
#समावेश <linux/usb.h>
#समावेश <linux/module.h>
#समावेश <linux/ethtool.h>

#समावेश <linux/can.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/can/error.h>
#समावेश <linux/can/dev/peak_canfd.h>

#समावेश "pcan_usb_core.h"
#समावेश "pcan_usb_pro.h"

#घोषणा PCAN_USBPROFD_CHANNEL_COUNT	2
#घोषणा PCAN_USBFD_CHANNEL_COUNT	1

/* PCAN-USB Pro FD adapter पूर्णांकernal घड़ी (Hz) */
#घोषणा PCAN_UFD_CRYSTAL_HZ		80000000

#घोषणा PCAN_UFD_CMD_BUFFER_SIZE	512
#घोषणा PCAN_UFD_LOSPD_PKT_SIZE		64

/* PCAN-USB Pro FD command समयout (ms.) */
#घोषणा PCAN_UFD_CMD_TIMEOUT_MS		1000

/* PCAN-USB Pro FD rx/tx buffers size */
#घोषणा PCAN_UFD_RX_BUFFER_SIZE		2048
#घोषणा PCAN_UFD_TX_BUFFER_SIZE		512

/* पढ़ो some versions info from the hw device */
काष्ठा __packed pcan_ufd_fw_info अणु
	__le16	size_of;	/* माप this */
	__le16	type;		/* type of this काष्ठाure */
	u8	hw_type;	/* Type of hardware (HW_TYPE_xxx) */
	u8	bl_version[3];	/* Bootloader version */
	u8	hw_version;	/* Hardware version (PCB) */
	u8	fw_version[3];	/* Firmware version */
	__le32	dev_id[2];	/* "device id" per CAN */
	__le32	ser_no;		/* S/N */
	__le32	flags;		/* special functions */
पूर्ण;

/* handle device specअगरic info used by the netdevices */
काष्ठा pcan_usb_fd_अगर अणु
	काष्ठा peak_usb_device	*dev[PCAN_USB_MAX_CHANNEL];
	काष्ठा pcan_ufd_fw_info	fw_info;
	काष्ठा peak_समय_ref	समय_ref;
	पूर्णांक			cm_ignore_count;
	पूर्णांक			dev_खोलोed_count;
पूर्ण;

/* device inक्रमmation */
काष्ठा pcan_usb_fd_device अणु
	काष्ठा peak_usb_device	dev;
	काष्ठा can_berr_counter	bec;
	काष्ठा pcan_usb_fd_अगर	*usb_अगर;
	u8			*cmd_buffer_addr;
पूर्ण;

/* Extended USB commands (non uCAN commands) */

/* Clock Modes command */
#घोषणा PCAN_UFD_CMD_CLK_SET		0x80

#घोषणा PCAN_UFD_CLK_80MHZ		0x0
#घोषणा PCAN_UFD_CLK_60MHZ		0x1
#घोषणा PCAN_UFD_CLK_40MHZ		0x2
#घोषणा PCAN_UFD_CLK_30MHZ		0x3
#घोषणा PCAN_UFD_CLK_24MHZ		0x4
#घोषणा PCAN_UFD_CLK_20MHZ		0x5
#घोषणा PCAN_UFD_CLK_DEF		PCAN_UFD_CLK_80MHZ

काष्ठा __packed pcan_ufd_घड़ी अणु
	__le16	opcode_channel;

	u8	mode;
	u8	unused[5];
पूर्ण;

/* LED control command */
#घोषणा PCAN_UFD_CMD_LED_SET		0x86

#घोषणा PCAN_UFD_LED_DEV		0x00
#घोषणा PCAN_UFD_LED_FAST		0x01
#घोषणा PCAN_UFD_LED_SLOW		0x02
#घोषणा PCAN_UFD_LED_ON			0x03
#घोषणा PCAN_UFD_LED_OFF		0x04
#घोषणा PCAN_UFD_LED_DEF		PCAN_UFD_LED_DEV

काष्ठा __packed pcan_ufd_led अणु
	__le16	opcode_channel;

	u8	mode;
	u8	unused[5];
पूर्ण;

/* Extended usage of uCAN commands CMD_xxx_xx_OPTION क्रम PCAN-USB Pro FD */
#घोषणा PCAN_UFD_FLTEXT_CALIBRATION	0x8000

काष्ठा __packed pcan_ufd_options अणु
	__le16	opcode_channel;

	__le16	ucan_mask;
	u16	unused;
	__le16	usb_mask;
पूर्ण;

/* Extended usage of uCAN messages क्रम PCAN-USB Pro FD */
#घोषणा PCAN_UFD_MSG_CALIBRATION	0x100

काष्ठा __packed pcan_ufd_ts_msg अणु
	__le16	size;
	__le16	type;
	__le32	ts_low;
	__le32	ts_high;
	__le16	usb_frame_index;
	u16	unused;
पूर्ण;

#घोषणा PCAN_UFD_MSG_OVERRUN		0x101

#घोषणा PCAN_UFD_OVMSG_CHANNEL(o)	((o)->channel & 0xf)

काष्ठा __packed pcan_ufd_ovr_msg अणु
	__le16	size;
	__le16	type;
	__le32	ts_low;
	__le32	ts_high;
	u8	channel;
	u8	unused[3];
पूर्ण;

अटल अंतरभूत पूर्णांक pufd_omsg_get_channel(काष्ठा pcan_ufd_ovr_msg *om)
अणु
	वापस om->channel & 0xf;
पूर्ण

/* Clock mode frequency values */
अटल स्थिर u32 pcan_usb_fd_clk_freq[6] = अणु
	[PCAN_UFD_CLK_80MHZ] = 80000000,
	[PCAN_UFD_CLK_60MHZ] = 60000000,
	[PCAN_UFD_CLK_40MHZ] = 40000000,
	[PCAN_UFD_CLK_30MHZ] = 30000000,
	[PCAN_UFD_CLK_24MHZ] = 24000000,
	[PCAN_UFD_CLK_20MHZ] = 20000000
पूर्ण;

/* वापस a device USB पूर्णांकerface */
अटल अंतरभूत
काष्ठा pcan_usb_fd_अगर *pcan_usb_fd_dev_अगर(काष्ठा peak_usb_device *dev)
अणु
	काष्ठा pcan_usb_fd_device *pdev =
			container_of(dev, काष्ठा pcan_usb_fd_device, dev);
	वापस pdev->usb_अगर;
पूर्ण

/* वापस a device USB commands buffer */
अटल अंतरभूत व्योम *pcan_usb_fd_cmd_buffer(काष्ठा peak_usb_device *dev)
अणु
	काष्ठा pcan_usb_fd_device *pdev =
			container_of(dev, काष्ठा pcan_usb_fd_device, dev);
	वापस pdev->cmd_buffer_addr;
पूर्ण

/* send PCAN-USB Pro FD commands synchronously */
अटल पूर्णांक pcan_usb_fd_send_cmd(काष्ठा peak_usb_device *dev, व्योम *cmd_tail)
अणु
	व्योम *cmd_head = pcan_usb_fd_cmd_buffer(dev);
	पूर्णांक err = 0;
	u8 *packet_ptr;
	पूर्णांक packet_len;
	सूचक_भेद_प्रकार cmd_len;

	/* usb device unरेजिस्टरed? */
	अगर (!(dev->state & PCAN_USB_STATE_CONNECTED))
		वापस 0;

	/* अगर a packet is not filled completely by commands, the command list
	 * is terminated with an "end of collection" record.
	 */
	cmd_len = cmd_tail - cmd_head;
	अगर (cmd_len <= (PCAN_UFD_CMD_BUFFER_SIZE - माप(u64))) अणु
		स_रखो(cmd_tail, 0xff, माप(u64));
		cmd_len += माप(u64);
	पूर्ण

	packet_ptr = cmd_head;
	packet_len = cmd_len;

	/* firmware is not able to re-assemble 512 bytes buffer in full-speed */
	अगर (unlikely(dev->udev->speed != USB_SPEED_HIGH))
		packet_len = min(packet_len, PCAN_UFD_LOSPD_PKT_SIZE);

	करो अणु
		err = usb_bulk_msg(dev->udev,
				   usb_sndbulkpipe(dev->udev,
						   PCAN_USBPRO_EP_CMDOUT),
				   packet_ptr, packet_len,
				   शून्य, PCAN_UFD_CMD_TIMEOUT_MS);
		अगर (err) अणु
			netdev_err(dev->netdev,
				   "sending command failure: %d\n", err);
			अवरोध;
		पूर्ण

		packet_ptr += packet_len;
		cmd_len -= packet_len;

		अगर (cmd_len < PCAN_UFD_LOSPD_PKT_SIZE)
			packet_len = cmd_len;

	पूर्ण जबतक (packet_len > 0);

	वापस err;
पूर्ण

/* build the commands list in the given buffer, to enter operational mode */
अटल पूर्णांक pcan_usb_fd_build_restart_cmd(काष्ठा peak_usb_device *dev, u8 *buf)
अणु
	काष्ठा pucan_wr_err_cnt *prc;
	काष्ठा pucan_command *cmd;
	u8 *pc = buf;

	/* 1st, reset error counters: */
	prc = (काष्ठा pucan_wr_err_cnt *)pc;
	prc->opcode_channel = pucan_cmd_opcode_channel(dev->ctrl_idx,
						       PUCAN_CMD_WR_ERR_CNT);

	/* select both counters */
	prc->sel_mask = cpu_to_le16(PUCAN_WRERRCNT_TE|PUCAN_WRERRCNT_RE);

	/* and reset their values */
	prc->tx_counter = 0;
	prc->rx_counter = 0;

	/* moves the poपूर्णांकer क्रमward */
	pc += माप(काष्ठा pucan_wr_err_cnt);

	/* add command to चयन from ISO to non-ISO mode, अगर fw allows it */
	अगर (dev->can.ctrlmode_supported & CAN_CTRLMODE_FD_NON_ISO) अणु
		काष्ठा pucan_options *puo = (काष्ठा pucan_options *)pc;

		puo->opcode_channel =
			(dev->can.ctrlmode & CAN_CTRLMODE_FD_NON_ISO) ?
			pucan_cmd_opcode_channel(dev->ctrl_idx,
						 PUCAN_CMD_CLR_DIS_OPTION) :
			pucan_cmd_opcode_channel(dev->ctrl_idx,
						 PUCAN_CMD_SET_EN_OPTION);

		puo->options = cpu_to_le16(PUCAN_OPTION_CANDFDISO);

		/* to be sure that no other extended bits will be taken पूर्णांकo
		 * account
		 */
		puo->unused = 0;

		/* moves the poपूर्णांकer क्रमward */
		pc += माप(काष्ठा pucan_options);
	पूर्ण

	/* next, go back to operational mode */
	cmd = (काष्ठा pucan_command *)pc;
	cmd->opcode_channel = pucan_cmd_opcode_channel(dev->ctrl_idx,
				(dev->can.ctrlmode & CAN_CTRLMODE_LISTENONLY) ?
						PUCAN_CMD_LISTEN_ONLY_MODE :
						PUCAN_CMD_NORMAL_MODE);
	pc += माप(काष्ठा pucan_command);

	वापस pc - buf;
पूर्ण

/* set CAN bus on/off */
अटल पूर्णांक pcan_usb_fd_set_bus(काष्ठा peak_usb_device *dev, u8 onoff)
अणु
	u8 *pc = pcan_usb_fd_cmd_buffer(dev);
	पूर्णांक l;

	अगर (onoff) अणु
		/* build the cmds list to enter operational mode */
		l = pcan_usb_fd_build_restart_cmd(dev, pc);
	पूर्ण अन्यथा अणु
		काष्ठा pucan_command *cmd = (काष्ठा pucan_command *)pc;

		/* build cmd to go back to reset mode */
		cmd->opcode_channel = pucan_cmd_opcode_channel(dev->ctrl_idx,
							PUCAN_CMD_RESET_MODE);
		l = माप(काष्ठा pucan_command);
	पूर्ण

	/* send the command */
	वापस pcan_usb_fd_send_cmd(dev, pc + l);
पूर्ण

/* set filtering masks:
 *
 *	idx  in range [0..63] selects a row #idx, all rows otherwise
 *	mask in range [0..0xffffffff] defines up to 32 CANIDs in the row(s)
 *
 *	Each bit of this 64 x 32 bits array defines a CANID value:
 *
 *	bit[i,j] = 1 implies that CANID=(i x 32)+j will be received, जबतक
 *	bit[i,j] = 0 implies that CANID=(i x 32)+j will be discarded.
 */
अटल पूर्णांक pcan_usb_fd_set_filter_std(काष्ठा peak_usb_device *dev, पूर्णांक idx,
				      u32 mask)
अणु
	काष्ठा pucan_filter_std *cmd = pcan_usb_fd_cmd_buffer(dev);
	पूर्णांक i, n;

	/* select all rows when idx is out of range [0..63] */
	अगर ((idx < 0) || (idx >= (1 << PUCAN_FLTSTD_ROW_IDX_BITS))) अणु
		n = 1 << PUCAN_FLTSTD_ROW_IDX_BITS;
		idx = 0;

	/* select the row (and only the row) otherwise */
	पूर्ण अन्यथा अणु
		n = idx + 1;
	पूर्ण

	क्रम (i = idx; i < n; i++, cmd++) अणु
		cmd->opcode_channel = pucan_cmd_opcode_channel(dev->ctrl_idx,
							PUCAN_CMD_FILTER_STD);
		cmd->idx = cpu_to_le16(i);
		cmd->mask = cpu_to_le32(mask);
	पूर्ण

	/* send the command */
	वापस pcan_usb_fd_send_cmd(dev, cmd);
पूर्ण

/* set/unset options
 *
 *	onoff	set(1)/unset(0) options
 *	mask	each bit defines a kind of options to set/unset
 */
अटल पूर्णांक pcan_usb_fd_set_options(काष्ठा peak_usb_device *dev,
				   bool onoff, u16 ucan_mask, u16 usb_mask)
अणु
	काष्ठा pcan_ufd_options *cmd = pcan_usb_fd_cmd_buffer(dev);

	cmd->opcode_channel = pucan_cmd_opcode_channel(dev->ctrl_idx,
					(onoff) ? PUCAN_CMD_SET_EN_OPTION :
						  PUCAN_CMD_CLR_DIS_OPTION);

	cmd->ucan_mask = cpu_to_le16(ucan_mask);
	cmd->usb_mask = cpu_to_le16(usb_mask);

	/* send the command */
	वापस pcan_usb_fd_send_cmd(dev, ++cmd);
पूर्ण

/* setup LED control */
अटल पूर्णांक pcan_usb_fd_set_can_led(काष्ठा peak_usb_device *dev, u8 led_mode)
अणु
	काष्ठा pcan_ufd_led *cmd = pcan_usb_fd_cmd_buffer(dev);

	cmd->opcode_channel = pucan_cmd_opcode_channel(dev->ctrl_idx,
						       PCAN_UFD_CMD_LED_SET);
	cmd->mode = led_mode;

	/* send the command */
	वापस pcan_usb_fd_send_cmd(dev, ++cmd);
पूर्ण

/* set CAN घड़ी करोमुख्य */
अटल पूर्णांक pcan_usb_fd_set_घड़ी_करोमुख्य(काष्ठा peak_usb_device *dev,
					u8 clk_mode)
अणु
	काष्ठा pcan_ufd_घड़ी *cmd = pcan_usb_fd_cmd_buffer(dev);

	cmd->opcode_channel = pucan_cmd_opcode_channel(dev->ctrl_idx,
						       PCAN_UFD_CMD_CLK_SET);
	cmd->mode = clk_mode;

	/* send the command */
	वापस pcan_usb_fd_send_cmd(dev, ++cmd);
पूर्ण

/* set bittiming क्रम CAN and CAN-FD header */
अटल पूर्णांक pcan_usb_fd_set_bittiming_slow(काष्ठा peak_usb_device *dev,
					  काष्ठा can_bittiming *bt)
अणु
	काष्ठा pucan_timing_slow *cmd = pcan_usb_fd_cmd_buffer(dev);

	cmd->opcode_channel = pucan_cmd_opcode_channel(dev->ctrl_idx,
						       PUCAN_CMD_TIMING_SLOW);
	cmd->sjw_t = PUCAN_TSLOW_SJW_T(bt->sjw - 1,
				dev->can.ctrlmode & CAN_CTRLMODE_3_SAMPLES);

	cmd->tseg2 = PUCAN_TSLOW_TSEG2(bt->phase_seg2 - 1);
	cmd->tseg1 = PUCAN_TSLOW_TSEG1(bt->prop_seg + bt->phase_seg1 - 1);
	cmd->brp = cpu_to_le16(PUCAN_TSLOW_BRP(bt->brp - 1));

	cmd->ewl = 96;	/* शेष */

	/* send the command */
	वापस pcan_usb_fd_send_cmd(dev, ++cmd);
पूर्ण

/* set CAN-FD bittiming क्रम data */
अटल पूर्णांक pcan_usb_fd_set_bittiming_fast(काष्ठा peak_usb_device *dev,
					  काष्ठा can_bittiming *bt)
अणु
	काष्ठा pucan_timing_fast *cmd = pcan_usb_fd_cmd_buffer(dev);

	cmd->opcode_channel = pucan_cmd_opcode_channel(dev->ctrl_idx,
						       PUCAN_CMD_TIMING_FAST);
	cmd->sjw = PUCAN_TFAST_SJW(bt->sjw - 1);
	cmd->tseg2 = PUCAN_TFAST_TSEG2(bt->phase_seg2 - 1);
	cmd->tseg1 = PUCAN_TFAST_TSEG1(bt->prop_seg + bt->phase_seg1 - 1);
	cmd->brp = cpu_to_le16(PUCAN_TFAST_BRP(bt->brp - 1));

	/* send the command */
	वापस pcan_usb_fd_send_cmd(dev, ++cmd);
पूर्ण

/* handle restart but in asynchronously way
 * (uses PCAN-USB Pro code to complete asynchronous request)
 */
अटल पूर्णांक pcan_usb_fd_restart_async(काष्ठा peak_usb_device *dev,
				     काष्ठा urb *urb, u8 *buf)
अणु
	u8 *pc = buf;

	/* build the entire cmds list in the provided buffer, to go back पूर्णांकo
	 * operational mode.
	 */
	pc += pcan_usb_fd_build_restart_cmd(dev, pc);

	/* add EOC */
	स_रखो(pc, 0xff, माप(काष्ठा pucan_command));
	pc += माप(काष्ठा pucan_command);

	/* complete the URB */
	usb_fill_bulk_urb(urb, dev->udev,
			  usb_sndbulkpipe(dev->udev, PCAN_USBPRO_EP_CMDOUT),
			  buf, pc - buf,
			  pcan_usb_pro_restart_complete, dev);

	/* and submit it. */
	वापस usb_submit_urb(urb, GFP_ATOMIC);
पूर्ण

अटल पूर्णांक pcan_usb_fd_drv_loaded(काष्ठा peak_usb_device *dev, bool loaded)
अणु
	काष्ठा pcan_usb_fd_device *pdev =
			container_of(dev, काष्ठा pcan_usb_fd_device, dev);

	pdev->cmd_buffer_addr[0] = 0;
	pdev->cmd_buffer_addr[1] = !!loaded;

	वापस pcan_usb_pro_send_req(dev,
				PCAN_USBPRO_REQ_FCT,
				PCAN_USBPRO_FCT_DRVLD,
				pdev->cmd_buffer_addr,
				PCAN_USBPRO_FCT_DRVLD_REQ_LEN);
पूर्ण

अटल पूर्णांक pcan_usb_fd_decode_canmsg(काष्ठा pcan_usb_fd_अगर *usb_अगर,
				     काष्ठा pucan_msg *rx_msg)
अणु
	काष्ठा pucan_rx_msg *rm = (काष्ठा pucan_rx_msg *)rx_msg;
	काष्ठा peak_usb_device *dev;
	काष्ठा net_device *netdev;
	काष्ठा canfd_frame *cfd;
	काष्ठा sk_buff *skb;
	स्थिर u16 rx_msg_flags = le16_to_cpu(rm->flags);

	अगर (pucan_msg_get_channel(rm) >= ARRAY_SIZE(usb_अगर->dev))
		वापस -ENOMEM;

	dev = usb_अगर->dev[pucan_msg_get_channel(rm)];
	netdev = dev->netdev;

	अगर (rx_msg_flags & PUCAN_MSG_EXT_DATA_LEN) अणु
		/* CANFD frame हाल */
		skb = alloc_canfd_skb(netdev, &cfd);
		अगर (!skb)
			वापस -ENOMEM;

		अगर (rx_msg_flags & PUCAN_MSG_BITRATE_SWITCH)
			cfd->flags |= CANFD_BRS;

		अगर (rx_msg_flags & PUCAN_MSG_ERROR_STATE_IND)
			cfd->flags |= CANFD_ESI;

		cfd->len = can_fd_dlc2len(pucan_msg_get_dlc(rm));
	पूर्ण अन्यथा अणु
		/* CAN 2.0 frame हाल */
		skb = alloc_can_skb(netdev, (काष्ठा can_frame **)&cfd);
		अगर (!skb)
			वापस -ENOMEM;

		can_frame_set_cc_len((काष्ठा can_frame *)cfd,
				     pucan_msg_get_dlc(rm),
				     dev->can.ctrlmode);
	पूर्ण

	cfd->can_id = le32_to_cpu(rm->can_id);

	अगर (rx_msg_flags & PUCAN_MSG_EXT_ID)
		cfd->can_id |= CAN_EFF_FLAG;

	अगर (rx_msg_flags & PUCAN_MSG_RTR)
		cfd->can_id |= CAN_RTR_FLAG;
	अन्यथा
		स_नकल(cfd->data, rm->d, cfd->len);

	netdev->stats.rx_packets++;
	netdev->stats.rx_bytes += cfd->len;

	peak_usb_netअगर_rx(skb, &usb_अगर->समय_ref, le32_to_cpu(rm->ts_low));

	वापस 0;
पूर्ण

/* handle uCAN status message */
अटल पूर्णांक pcan_usb_fd_decode_status(काष्ठा pcan_usb_fd_अगर *usb_अगर,
				     काष्ठा pucan_msg *rx_msg)
अणु
	काष्ठा pucan_status_msg *sm = (काष्ठा pucan_status_msg *)rx_msg;
	काष्ठा pcan_usb_fd_device *pdev;
	क्रमागत can_state new_state = CAN_STATE_ERROR_ACTIVE;
	क्रमागत can_state rx_state, tx_state;
	काष्ठा peak_usb_device *dev;
	काष्ठा net_device *netdev;
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;

	अगर (pucan_sपंचांगsg_get_channel(sm) >= ARRAY_SIZE(usb_अगर->dev))
		वापस -ENOMEM;

	dev = usb_अगर->dev[pucan_sपंचांगsg_get_channel(sm)];
	pdev = container_of(dev, काष्ठा pcan_usb_fd_device, dev);
	netdev = dev->netdev;

	/* nothing should be sent जबतक in BUS_OFF state */
	अगर (dev->can.state == CAN_STATE_BUS_OFF)
		वापस 0;

	अगर (sm->channel_p_w_b & PUCAN_BUS_BUSOFF) अणु
		new_state = CAN_STATE_BUS_OFF;
	पूर्ण अन्यथा अगर (sm->channel_p_w_b & PUCAN_BUS_PASSIVE) अणु
		new_state = CAN_STATE_ERROR_PASSIVE;
	पूर्ण अन्यथा अगर (sm->channel_p_w_b & PUCAN_BUS_WARNING) अणु
		new_state = CAN_STATE_ERROR_WARNING;
	पूर्ण अन्यथा अणु
		/* no error bit (so, no error skb, back to active state) */
		dev->can.state = CAN_STATE_ERROR_ACTIVE;
		pdev->bec.txerr = 0;
		pdev->bec.rxerr = 0;
		वापस 0;
	पूर्ण

	/* state hasn't changed */
	अगर (new_state == dev->can.state)
		वापस 0;

	/* handle bus state change */
	tx_state = (pdev->bec.txerr >= pdev->bec.rxerr) ? new_state : 0;
	rx_state = (pdev->bec.txerr <= pdev->bec.rxerr) ? new_state : 0;

	/* allocate an skb to store the error frame */
	skb = alloc_can_err_skb(netdev, &cf);
	अगर (skb)
		can_change_state(netdev, cf, tx_state, rx_state);

	/* things must be करोne even in हाल of OOM */
	अगर (new_state == CAN_STATE_BUS_OFF)
		can_bus_off(netdev);

	अगर (!skb)
		वापस -ENOMEM;

	netdev->stats.rx_packets++;
	netdev->stats.rx_bytes += cf->len;

	peak_usb_netअगर_rx(skb, &usb_अगर->समय_ref, le32_to_cpu(sm->ts_low));

	वापस 0;
पूर्ण

/* handle uCAN error message */
अटल पूर्णांक pcan_usb_fd_decode_error(काष्ठा pcan_usb_fd_अगर *usb_अगर,
				    काष्ठा pucan_msg *rx_msg)
अणु
	काष्ठा pucan_error_msg *er = (काष्ठा pucan_error_msg *)rx_msg;
	काष्ठा pcan_usb_fd_device *pdev;
	काष्ठा peak_usb_device *dev;

	अगर (pucan_ermsg_get_channel(er) >= ARRAY_SIZE(usb_अगर->dev))
		वापस -EINVAL;

	dev = usb_अगर->dev[pucan_ermsg_get_channel(er)];
	pdev = container_of(dev, काष्ठा pcan_usb_fd_device, dev);

	/* keep a trace of tx and rx error counters क्रम later use */
	pdev->bec.txerr = er->tx_err_cnt;
	pdev->bec.rxerr = er->rx_err_cnt;

	वापस 0;
पूर्ण

/* handle uCAN overrun message */
अटल पूर्णांक pcan_usb_fd_decode_overrun(काष्ठा pcan_usb_fd_अगर *usb_अगर,
				      काष्ठा pucan_msg *rx_msg)
अणु
	काष्ठा pcan_ufd_ovr_msg *ov = (काष्ठा pcan_ufd_ovr_msg *)rx_msg;
	काष्ठा peak_usb_device *dev;
	काष्ठा net_device *netdev;
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;

	अगर (pufd_omsg_get_channel(ov) >= ARRAY_SIZE(usb_अगर->dev))
		वापस -EINVAL;

	dev = usb_अगर->dev[pufd_omsg_get_channel(ov)];
	netdev = dev->netdev;

	/* allocate an skb to store the error frame */
	skb = alloc_can_err_skb(netdev, &cf);
	अगर (!skb)
		वापस -ENOMEM;

	cf->can_id |= CAN_ERR_CRTL;
	cf->data[1] |= CAN_ERR_CRTL_RX_OVERFLOW;

	peak_usb_netअगर_rx(skb, &usb_अगर->समय_ref, le32_to_cpu(ov->ts_low));

	netdev->stats.rx_over_errors++;
	netdev->stats.rx_errors++;

	वापस 0;
पूर्ण

/* handle USB calibration message */
अटल व्योम pcan_usb_fd_decode_ts(काष्ठा pcan_usb_fd_अगर *usb_अगर,
				  काष्ठा pucan_msg *rx_msg)
अणु
	काष्ठा pcan_ufd_ts_msg *ts = (काष्ठा pcan_ufd_ts_msg *)rx_msg;

	/* should रुको until घड़ी is stabilized */
	अगर (usb_अगर->cm_ignore_count > 0)
		usb_अगर->cm_ignore_count--;
	अन्यथा
		peak_usb_set_ts_now(&usb_अगर->समय_ref, le32_to_cpu(ts->ts_low));
पूर्ण

/* callback क्रम bulk IN urb */
अटल पूर्णांक pcan_usb_fd_decode_buf(काष्ठा peak_usb_device *dev, काष्ठा urb *urb)
अणु
	काष्ठा pcan_usb_fd_अगर *usb_अगर = pcan_usb_fd_dev_अगर(dev);
	काष्ठा net_device *netdev = dev->netdev;
	काष्ठा pucan_msg *rx_msg;
	u8 *msg_ptr, *msg_end;
	पूर्णांक err = 0;

	/* loop पढ़ोing all the records from the incoming message */
	msg_ptr = urb->transfer_buffer;
	msg_end = urb->transfer_buffer + urb->actual_length;
	क्रम (; msg_ptr < msg_end;) अणु
		u16 rx_msg_type, rx_msg_size;

		rx_msg = (काष्ठा pucan_msg *)msg_ptr;
		अगर (!rx_msg->size) अणु
			/* null packet found: end of list */
			अवरोध;
		पूर्ण

		rx_msg_size = le16_to_cpu(rx_msg->size);
		rx_msg_type = le16_to_cpu(rx_msg->type);

		/* check अगर the record goes out of current packet */
		अगर (msg_ptr + rx_msg_size > msg_end) अणु
			netdev_err(netdev,
				   "got frag rec: should inc usb rx buf sze\n");
			err = -EBADMSG;
			अवरोध;
		पूर्ण

		चयन (rx_msg_type) अणु
		हाल PUCAN_MSG_CAN_RX:
			err = pcan_usb_fd_decode_canmsg(usb_अगर, rx_msg);
			अगर (err < 0)
				जाओ fail;
			अवरोध;

		हाल PCAN_UFD_MSG_CALIBRATION:
			pcan_usb_fd_decode_ts(usb_अगर, rx_msg);
			अवरोध;

		हाल PUCAN_MSG_ERROR:
			err = pcan_usb_fd_decode_error(usb_अगर, rx_msg);
			अगर (err < 0)
				जाओ fail;
			अवरोध;

		हाल PUCAN_MSG_STATUS:
			err = pcan_usb_fd_decode_status(usb_अगर, rx_msg);
			अगर (err < 0)
				जाओ fail;
			अवरोध;

		हाल PCAN_UFD_MSG_OVERRUN:
			err = pcan_usb_fd_decode_overrun(usb_अगर, rx_msg);
			अगर (err < 0)
				जाओ fail;
			अवरोध;

		शेष:
			netdev_err(netdev,
				   "unhandled msg type 0x%02x (%d): ignored\n",
				   rx_msg_type, rx_msg_type);
			अवरोध;
		पूर्ण

		msg_ptr += rx_msg_size;
	पूर्ण

fail:
	अगर (err)
		pcan_dump_mem("received msg",
			      urb->transfer_buffer, urb->actual_length);
	वापस err;
पूर्ण

/* CAN/CANFD frames encoding callback */
अटल पूर्णांक pcan_usb_fd_encode_msg(काष्ठा peak_usb_device *dev,
				  काष्ठा sk_buff *skb, u8 *obuf, माप_प्रकार *size)
अणु
	काष्ठा pucan_tx_msg *tx_msg = (काष्ठा pucan_tx_msg *)obuf;
	काष्ठा canfd_frame *cfd = (काष्ठा canfd_frame *)skb->data;
	u16 tx_msg_size, tx_msg_flags;
	u8 dlc;

	अगर (cfd->len > CANFD_MAX_DLEN)
		वापस -EINVAL;

	tx_msg_size = ALIGN(माप(काष्ठा pucan_tx_msg) + cfd->len, 4);
	tx_msg->size = cpu_to_le16(tx_msg_size);
	tx_msg->type = cpu_to_le16(PUCAN_MSG_CAN_TX);

	tx_msg_flags = 0;
	अगर (cfd->can_id & CAN_EFF_FLAG) अणु
		tx_msg_flags |= PUCAN_MSG_EXT_ID;
		tx_msg->can_id = cpu_to_le32(cfd->can_id & CAN_EFF_MASK);
	पूर्ण अन्यथा अणु
		tx_msg->can_id = cpu_to_le32(cfd->can_id & CAN_SFF_MASK);
	पूर्ण

	अगर (can_is_canfd_skb(skb)) अणु
		/* considering a CANFD frame */
		dlc = can_fd_len2dlc(cfd->len);

		tx_msg_flags |= PUCAN_MSG_EXT_DATA_LEN;

		अगर (cfd->flags & CANFD_BRS)
			tx_msg_flags |= PUCAN_MSG_BITRATE_SWITCH;

		अगर (cfd->flags & CANFD_ESI)
			tx_msg_flags |= PUCAN_MSG_ERROR_STATE_IND;
	पूर्ण अन्यथा अणु
		/* CAND 2.0 frames */
		dlc = can_get_cc_dlc((काष्ठा can_frame *)cfd,
				     dev->can.ctrlmode);

		अगर (cfd->can_id & CAN_RTR_FLAG)
			tx_msg_flags |= PUCAN_MSG_RTR;
	पूर्ण

	/* Single-Shot frame */
	अगर (dev->can.ctrlmode & CAN_CTRLMODE_ONE_SHOT)
		tx_msg_flags |= PUCAN_MSG_SINGLE_SHOT;

	tx_msg->flags = cpu_to_le16(tx_msg_flags);
	tx_msg->channel_dlc = PUCAN_MSG_CHANNEL_DLC(dev->ctrl_idx, dlc);
	स_नकल(tx_msg->d, cfd->data, cfd->len);

	/* add null size message to tag the end (messages are 32-bits aligned)
	 */
	tx_msg = (काष्ठा pucan_tx_msg *)(obuf + tx_msg_size);

	tx_msg->size = 0;

	/* set the whole size of the USB packet to send */
	*size = tx_msg_size + माप(u32);

	वापस 0;
पूर्ण

/* start the पूर्णांकerface (last chance beक्रमe set bus on) */
अटल पूर्णांक pcan_usb_fd_start(काष्ठा peak_usb_device *dev)
अणु
	काष्ठा pcan_usb_fd_device *pdev =
			container_of(dev, काष्ठा pcan_usb_fd_device, dev);
	पूर्णांक err;

	/* set filter mode: all acceptance */
	err = pcan_usb_fd_set_filter_std(dev, -1, 0xffffffff);
	अगर (err)
		वापस err;

	/* खोलोing first device: */
	अगर (pdev->usb_अगर->dev_खोलोed_count == 0) अणु
		/* reset समय_ref */
		peak_usb_init_समय_ref(&pdev->usb_अगर->समय_ref,
				       &pcan_usb_pro_fd);

		/* enable USB calibration messages */
		err = pcan_usb_fd_set_options(dev, 1,
					      PUCAN_OPTION_ERROR,
					      PCAN_UFD_FLTEXT_CALIBRATION);
	पूर्ण

	pdev->usb_अगर->dev_खोलोed_count++;

	/* reset cached error counters */
	pdev->bec.txerr = 0;
	pdev->bec.rxerr = 0;

	वापस err;
पूर्ण

/* socket callback used to copy berr counters values received through USB */
अटल पूर्णांक pcan_usb_fd_get_berr_counter(स्थिर काष्ठा net_device *netdev,
					काष्ठा can_berr_counter *bec)
अणु
	काष्ठा peak_usb_device *dev = netdev_priv(netdev);
	काष्ठा pcan_usb_fd_device *pdev =
			container_of(dev, काष्ठा pcan_usb_fd_device, dev);

	*bec = pdev->bec;

	/* must वापस 0 */
	वापस 0;
पूर्ण

/* stop पूर्णांकerface (last chance beक्रमe set bus off) */
अटल पूर्णांक pcan_usb_fd_stop(काष्ठा peak_usb_device *dev)
अणु
	काष्ठा pcan_usb_fd_device *pdev =
			container_of(dev, काष्ठा pcan_usb_fd_device, dev);

	/* turn off special msgs क्रम that पूर्णांकerface अगर no other dev खोलोed */
	अगर (pdev->usb_अगर->dev_खोलोed_count == 1)
		pcan_usb_fd_set_options(dev, 0,
					PUCAN_OPTION_ERROR,
					PCAN_UFD_FLTEXT_CALIBRATION);
	pdev->usb_अगर->dev_खोलोed_count--;

	वापस 0;
पूर्ण

/* called when probing, to initialize a device object */
अटल पूर्णांक pcan_usb_fd_init(काष्ठा peak_usb_device *dev)
अणु
	काष्ठा pcan_usb_fd_device *pdev =
			container_of(dev, काष्ठा pcan_usb_fd_device, dev);
	पूर्णांक i, err = -ENOMEM;

	/* करो this क्रम 1st channel only */
	अगर (!dev->prev_siblings) अणु
		/* allocate netdevices common काष्ठाure attached to first one */
		pdev->usb_अगर = kzalloc(माप(*pdev->usb_अगर), GFP_KERNEL);
		अगर (!pdev->usb_अगर)
			जाओ err_out;

		/* allocate command buffer once क्रम all क्रम the पूर्णांकerface */
		pdev->cmd_buffer_addr = kzalloc(PCAN_UFD_CMD_BUFFER_SIZE,
						GFP_KERNEL);
		अगर (!pdev->cmd_buffer_addr)
			जाओ err_out_1;

		/* number of ts msgs to ignore beक्रमe taking one पूर्णांकo account */
		pdev->usb_अगर->cm_ignore_count = 5;

		err = pcan_usb_pro_send_req(dev, PCAN_USBPRO_REQ_INFO,
					    PCAN_USBPRO_INFO_FW,
					    &pdev->usb_अगर->fw_info,
					    माप(pdev->usb_अगर->fw_info));
		अगर (err) अणु
			dev_err(dev->netdev->dev.parent,
				"unable to read %s firmware info (err %d)\n",
				dev->adapter->name, err);
			जाओ err_out_2;
		पूर्ण

		/* explicit use of dev_xxx() instead of netdev_xxx() here:
		 * inक्रमmation displayed are related to the device itself, not
		 * to the canx (channel) device.
		 */
		dev_info(dev->netdev->dev.parent,
			 "PEAK-System %s v%u fw v%u.%u.%u (%u channels)\n",
			 dev->adapter->name, pdev->usb_अगर->fw_info.hw_version,
			 pdev->usb_अगर->fw_info.fw_version[0],
			 pdev->usb_अगर->fw_info.fw_version[1],
			 pdev->usb_अगर->fw_info.fw_version[2],
			 dev->adapter->ctrl_count);

		/* check क्रम ability to चयन between ISO/non-ISO modes */
		अगर (pdev->usb_अगर->fw_info.fw_version[0] >= 2) अणु
			/* firmware >= 2.x supports ISO/non-ISO चयनing */
			dev->can.ctrlmode_supported |= CAN_CTRLMODE_FD_NON_ISO;
		पूर्ण अन्यथा अणु
			/* firmware < 2.x only supports fixed(!) non-ISO */
			dev->can.ctrlmode |= CAN_CTRLMODE_FD_NON_ISO;
		पूर्ण

		/* tell the hardware the can driver is running */
		err = pcan_usb_fd_drv_loaded(dev, 1);
		अगर (err) अणु
			dev_err(dev->netdev->dev.parent,
				"unable to tell %s driver is loaded (err %d)\n",
				dev->adapter->name, err);
			जाओ err_out_2;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* otherwise, simply copy previous sibling's values */
		काष्ठा pcan_usb_fd_device *ppdev =
			container_of(dev->prev_siblings,
				     काष्ठा pcan_usb_fd_device, dev);

		pdev->usb_अगर = ppdev->usb_अगर;
		pdev->cmd_buffer_addr = ppdev->cmd_buffer_addr;

		/* करो a copy of the ctrlmode[_supported] too */
		dev->can.ctrlmode = ppdev->dev.can.ctrlmode;
		dev->can.ctrlmode_supported = ppdev->dev.can.ctrlmode_supported;
	पूर्ण

	pdev->usb_अगर->dev[dev->ctrl_idx] = dev;
	dev->device_number =
		le32_to_cpu(pdev->usb_अगर->fw_info.dev_id[dev->ctrl_idx]);

	/* set घड़ी करोमुख्य */
	क्रम (i = 0; i < ARRAY_SIZE(pcan_usb_fd_clk_freq); i++)
		अगर (dev->adapter->घड़ी.freq == pcan_usb_fd_clk_freq[i])
			अवरोध;

	अगर (i >= ARRAY_SIZE(pcan_usb_fd_clk_freq)) अणु
		dev_warn(dev->netdev->dev.parent,
			 "incompatible clock frequencies\n");
		err = -EINVAL;
		जाओ err_out_2;
	पूर्ण

	pcan_usb_fd_set_घड़ी_करोमुख्य(dev, i);

	/* set LED in शेष state (end of init phase) */
	pcan_usb_fd_set_can_led(dev, PCAN_UFD_LED_DEF);

	वापस 0;

err_out_2:
	kमुक्त(pdev->cmd_buffer_addr);
err_out_1:
	kमुक्त(pdev->usb_अगर);
err_out:
	वापस err;
पूर्ण

/* called when driver module is being unloaded */
अटल व्योम pcan_usb_fd_निकास(काष्ठा peak_usb_device *dev)
अणु
	काष्ठा pcan_usb_fd_device *pdev =
			container_of(dev, काष्ठा pcan_usb_fd_device, dev);

	/* when rmmod called beक्रमe unplug and अगर करोwn, should reset things
	 * beक्रमe leaving
	 */
	अगर (dev->can.state != CAN_STATE_STOPPED) अणु
		/* set bus off on the corresponding channel */
		pcan_usb_fd_set_bus(dev, 0);
	पूर्ण

	/* चयन off corresponding CAN LEDs */
	pcan_usb_fd_set_can_led(dev, PCAN_UFD_LED_OFF);

	/* अगर channel #0 (only) */
	अगर (dev->ctrl_idx == 0) अणु
		/* turn off calibration message अगर any device were खोलोed */
		अगर (pdev->usb_अगर->dev_खोलोed_count > 0)
			pcan_usb_fd_set_options(dev, 0,
						PUCAN_OPTION_ERROR,
						PCAN_UFD_FLTEXT_CALIBRATION);

		/* tell USB adapter that the driver is being unloaded */
		pcan_usb_fd_drv_loaded(dev, 0);
	पूर्ण
पूर्ण

/* called when the USB adapter is unplugged */
अटल व्योम pcan_usb_fd_मुक्त(काष्ठा peak_usb_device *dev)
अणु
	/* last device: can मुक्त shared objects now */
	अगर (!dev->prev_siblings && !dev->next_siblings) अणु
		काष्ठा pcan_usb_fd_device *pdev =
			container_of(dev, काष्ठा pcan_usb_fd_device, dev);

		/* मुक्त commands buffer */
		kमुक्त(pdev->cmd_buffer_addr);

		/* मुक्त usb पूर्णांकerface object */
		kमुक्त(pdev->usb_अगर);
	पूर्ण
पूर्ण

/* blink LED's */
अटल पूर्णांक pcan_usb_fd_set_phys_id(काष्ठा net_device *netdev,
				   क्रमागत ethtool_phys_id_state state)
अणु
	काष्ठा peak_usb_device *dev = netdev_priv(netdev);
	पूर्णांक err = 0;

	चयन (state) अणु
	हाल ETHTOOL_ID_ACTIVE:
		err = pcan_usb_fd_set_can_led(dev, PCAN_UFD_LED_FAST);
		अवरोध;
	हाल ETHTOOL_ID_INACTIVE:
		err = pcan_usb_fd_set_can_led(dev, PCAN_UFD_LED_DEF);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops pcan_usb_fd_ethtool_ops = अणु
	.set_phys_id = pcan_usb_fd_set_phys_id,
पूर्ण;

/* describes the PCAN-USB FD adapter */
अटल स्थिर काष्ठा can_bittiming_स्थिर pcan_usb_fd_स्थिर = अणु
	.name = "pcan_usb_fd",
	.tseg1_min = 1,
	.tseg1_max = (1 << PUCAN_TSLOW_TSGEG1_BITS),
	.tseg2_min = 1,
	.tseg2_max = (1 << PUCAN_TSLOW_TSGEG2_BITS),
	.sjw_max = (1 << PUCAN_TSLOW_SJW_BITS),
	.brp_min = 1,
	.brp_max = (1 << PUCAN_TSLOW_BRP_BITS),
	.brp_inc = 1,
पूर्ण;

अटल स्थिर काष्ठा can_bittiming_स्थिर pcan_usb_fd_data_स्थिर = अणु
	.name = "pcan_usb_fd",
	.tseg1_min = 1,
	.tseg1_max = (1 << PUCAN_TFAST_TSGEG1_BITS),
	.tseg2_min = 1,
	.tseg2_max = (1 << PUCAN_TFAST_TSGEG2_BITS),
	.sjw_max = (1 << PUCAN_TFAST_SJW_BITS),
	.brp_min = 1,
	.brp_max = (1 << PUCAN_TFAST_BRP_BITS),
	.brp_inc = 1,
पूर्ण;

स्थिर काष्ठा peak_usb_adapter pcan_usb_fd = अणु
	.name = "PCAN-USB FD",
	.device_id = PCAN_USBFD_PRODUCT_ID,
	.ctrl_count = PCAN_USBFD_CHANNEL_COUNT,
	.ctrlmode_supported = CAN_CTRLMODE_FD |
			CAN_CTRLMODE_3_SAMPLES | CAN_CTRLMODE_LISTENONLY |
			CAN_CTRLMODE_ONE_SHOT | CAN_CTRLMODE_CC_LEN8_DLC,
	.घड़ी = अणु
		.freq = PCAN_UFD_CRYSTAL_HZ,
	पूर्ण,
	.bittiming_स्थिर = &pcan_usb_fd_स्थिर,
	.data_bittiming_स्थिर = &pcan_usb_fd_data_स्थिर,

	/* size of device निजी data */
	.माप_dev_निजी = माप(काष्ठा pcan_usb_fd_device),

	.ethtool_ops = &pcan_usb_fd_ethtool_ops,

	/* बारtamps usage */
	.ts_used_bits = 32,
	.us_per_ts_scale = 1, /* us = (ts * scale) >> shअगरt */
	.us_per_ts_shअगरt = 0,

	/* give here messages in/out endpoपूर्णांकs */
	.ep_msg_in = PCAN_USBPRO_EP_MSGIN,
	.ep_msg_out = अणुPCAN_USBPRO_EP_MSGOUT_0पूर्ण,

	/* size of rx/tx usb buffers */
	.rx_buffer_size = PCAN_UFD_RX_BUFFER_SIZE,
	.tx_buffer_size = PCAN_UFD_TX_BUFFER_SIZE,

	/* device callbacks */
	.पूर्णांकf_probe = pcan_usb_pro_probe,	/* same as PCAN-USB Pro */
	.dev_init = pcan_usb_fd_init,

	.dev_निकास = pcan_usb_fd_निकास,
	.dev_मुक्त = pcan_usb_fd_मुक्त,
	.dev_set_bus = pcan_usb_fd_set_bus,
	.dev_set_bittiming = pcan_usb_fd_set_bittiming_slow,
	.dev_set_data_bittiming = pcan_usb_fd_set_bittiming_fast,
	.dev_decode_buf = pcan_usb_fd_decode_buf,
	.dev_start = pcan_usb_fd_start,
	.dev_stop = pcan_usb_fd_stop,
	.dev_restart_async = pcan_usb_fd_restart_async,
	.dev_encode_msg = pcan_usb_fd_encode_msg,

	.करो_get_berr_counter = pcan_usb_fd_get_berr_counter,
पूर्ण;

/* describes the PCAN-CHIP USB */
अटल स्थिर काष्ठा can_bittiming_स्थिर pcan_usb_chip_स्थिर = अणु
	.name = "pcan_chip_usb",
	.tseg1_min = 1,
	.tseg1_max = (1 << PUCAN_TSLOW_TSGEG1_BITS),
	.tseg2_min = 1,
	.tseg2_max = (1 << PUCAN_TSLOW_TSGEG2_BITS),
	.sjw_max = (1 << PUCAN_TSLOW_SJW_BITS),
	.brp_min = 1,
	.brp_max = (1 << PUCAN_TSLOW_BRP_BITS),
	.brp_inc = 1,
पूर्ण;

अटल स्थिर काष्ठा can_bittiming_स्थिर pcan_usb_chip_data_स्थिर = अणु
	.name = "pcan_chip_usb",
	.tseg1_min = 1,
	.tseg1_max = (1 << PUCAN_TFAST_TSGEG1_BITS),
	.tseg2_min = 1,
	.tseg2_max = (1 << PUCAN_TFAST_TSGEG2_BITS),
	.sjw_max = (1 << PUCAN_TFAST_SJW_BITS),
	.brp_min = 1,
	.brp_max = (1 << PUCAN_TFAST_BRP_BITS),
	.brp_inc = 1,
पूर्ण;

स्थिर काष्ठा peak_usb_adapter pcan_usb_chip = अणु
	.name = "PCAN-Chip USB",
	.device_id = PCAN_USBCHIP_PRODUCT_ID,
	.ctrl_count = PCAN_USBFD_CHANNEL_COUNT,
	.ctrlmode_supported = CAN_CTRLMODE_FD |
		CAN_CTRLMODE_3_SAMPLES | CAN_CTRLMODE_LISTENONLY |
		CAN_CTRLMODE_ONE_SHOT | CAN_CTRLMODE_CC_LEN8_DLC,
	.घड़ी = अणु
		.freq = PCAN_UFD_CRYSTAL_HZ,
	पूर्ण,
	.bittiming_स्थिर = &pcan_usb_chip_स्थिर,
	.data_bittiming_स्थिर = &pcan_usb_chip_data_स्थिर,

	/* size of device निजी data */
	.माप_dev_निजी = माप(काष्ठा pcan_usb_fd_device),

	.ethtool_ops = &pcan_usb_fd_ethtool_ops,

	/* बारtamps usage */
	.ts_used_bits = 32,
	.us_per_ts_scale = 1, /* us = (ts * scale) >> shअगरt */
	.us_per_ts_shअगरt = 0,

	/* give here messages in/out endpoपूर्णांकs */
	.ep_msg_in = PCAN_USBPRO_EP_MSGIN,
	.ep_msg_out = अणुPCAN_USBPRO_EP_MSGOUT_0पूर्ण,

	/* size of rx/tx usb buffers */
	.rx_buffer_size = PCAN_UFD_RX_BUFFER_SIZE,
	.tx_buffer_size = PCAN_UFD_TX_BUFFER_SIZE,

	/* device callbacks */
	.पूर्णांकf_probe = pcan_usb_pro_probe,	/* same as PCAN-USB Pro */
	.dev_init = pcan_usb_fd_init,

	.dev_निकास = pcan_usb_fd_निकास,
	.dev_मुक्त = pcan_usb_fd_मुक्त,
	.dev_set_bus = pcan_usb_fd_set_bus,
	.dev_set_bittiming = pcan_usb_fd_set_bittiming_slow,
	.dev_set_data_bittiming = pcan_usb_fd_set_bittiming_fast,
	.dev_decode_buf = pcan_usb_fd_decode_buf,
	.dev_start = pcan_usb_fd_start,
	.dev_stop = pcan_usb_fd_stop,
	.dev_restart_async = pcan_usb_fd_restart_async,
	.dev_encode_msg = pcan_usb_fd_encode_msg,

	.करो_get_berr_counter = pcan_usb_fd_get_berr_counter,
पूर्ण;

/* describes the PCAN-USB Pro FD adapter */
अटल स्थिर काष्ठा can_bittiming_स्थिर pcan_usb_pro_fd_स्थिर = अणु
	.name = "pcan_usb_pro_fd",
	.tseg1_min = 1,
	.tseg1_max = (1 << PUCAN_TSLOW_TSGEG1_BITS),
	.tseg2_min = 1,
	.tseg2_max = (1 << PUCAN_TSLOW_TSGEG2_BITS),
	.sjw_max = (1 << PUCAN_TSLOW_SJW_BITS),
	.brp_min = 1,
	.brp_max = (1 << PUCAN_TSLOW_BRP_BITS),
	.brp_inc = 1,
पूर्ण;

अटल स्थिर काष्ठा can_bittiming_स्थिर pcan_usb_pro_fd_data_स्थिर = अणु
	.name = "pcan_usb_pro_fd",
	.tseg1_min = 1,
	.tseg1_max = (1 << PUCAN_TFAST_TSGEG1_BITS),
	.tseg2_min = 1,
	.tseg2_max = (1 << PUCAN_TFAST_TSGEG2_BITS),
	.sjw_max = (1 << PUCAN_TFAST_SJW_BITS),
	.brp_min = 1,
	.brp_max = (1 << PUCAN_TFAST_BRP_BITS),
	.brp_inc = 1,
पूर्ण;

स्थिर काष्ठा peak_usb_adapter pcan_usb_pro_fd = अणु
	.name = "PCAN-USB Pro FD",
	.device_id = PCAN_USBPROFD_PRODUCT_ID,
	.ctrl_count = PCAN_USBPROFD_CHANNEL_COUNT,
	.ctrlmode_supported = CAN_CTRLMODE_FD |
			CAN_CTRLMODE_3_SAMPLES | CAN_CTRLMODE_LISTENONLY |
			CAN_CTRLMODE_ONE_SHOT | CAN_CTRLMODE_CC_LEN8_DLC,
	.घड़ी = अणु
		.freq = PCAN_UFD_CRYSTAL_HZ,
	पूर्ण,
	.bittiming_स्थिर = &pcan_usb_pro_fd_स्थिर,
	.data_bittiming_स्थिर = &pcan_usb_pro_fd_data_स्थिर,

	/* size of device निजी data */
	.माप_dev_निजी = माप(काष्ठा pcan_usb_fd_device),

	.ethtool_ops = &pcan_usb_fd_ethtool_ops,

	/* बारtamps usage */
	.ts_used_bits = 32,
	.us_per_ts_scale = 1, /* us = (ts * scale) >> shअगरt */
	.us_per_ts_shअगरt = 0,

	/* give here messages in/out endpoपूर्णांकs */
	.ep_msg_in = PCAN_USBPRO_EP_MSGIN,
	.ep_msg_out = अणुPCAN_USBPRO_EP_MSGOUT_0, PCAN_USBPRO_EP_MSGOUT_1पूर्ण,

	/* size of rx/tx usb buffers */
	.rx_buffer_size = PCAN_UFD_RX_BUFFER_SIZE,
	.tx_buffer_size = PCAN_UFD_TX_BUFFER_SIZE,

	/* device callbacks */
	.पूर्णांकf_probe = pcan_usb_pro_probe,	/* same as PCAN-USB Pro */
	.dev_init = pcan_usb_fd_init,

	.dev_निकास = pcan_usb_fd_निकास,
	.dev_मुक्त = pcan_usb_fd_मुक्त,
	.dev_set_bus = pcan_usb_fd_set_bus,
	.dev_set_bittiming = pcan_usb_fd_set_bittiming_slow,
	.dev_set_data_bittiming = pcan_usb_fd_set_bittiming_fast,
	.dev_decode_buf = pcan_usb_fd_decode_buf,
	.dev_start = pcan_usb_fd_start,
	.dev_stop = pcan_usb_fd_stop,
	.dev_restart_async = pcan_usb_fd_restart_async,
	.dev_encode_msg = pcan_usb_fd_encode_msg,

	.करो_get_berr_counter = pcan_usb_fd_get_berr_counter,
पूर्ण;

/* describes the PCAN-USB X6 adapter */
अटल स्थिर काष्ठा can_bittiming_स्थिर pcan_usb_x6_स्थिर = अणु
	.name = "pcan_usb_x6",
	.tseg1_min = 1,
	.tseg1_max = (1 << PUCAN_TSLOW_TSGEG1_BITS),
	.tseg2_min = 1,
	.tseg2_max = (1 << PUCAN_TSLOW_TSGEG2_BITS),
	.sjw_max = (1 << PUCAN_TSLOW_SJW_BITS),
	.brp_min = 1,
	.brp_max = (1 << PUCAN_TSLOW_BRP_BITS),
	.brp_inc = 1,
पूर्ण;

अटल स्थिर काष्ठा can_bittiming_स्थिर pcan_usb_x6_data_स्थिर = अणु
	.name = "pcan_usb_x6",
	.tseg1_min = 1,
	.tseg1_max = (1 << PUCAN_TFAST_TSGEG1_BITS),
	.tseg2_min = 1,
	.tseg2_max = (1 << PUCAN_TFAST_TSGEG2_BITS),
	.sjw_max = (1 << PUCAN_TFAST_SJW_BITS),
	.brp_min = 1,
	.brp_max = (1 << PUCAN_TFAST_BRP_BITS),
	.brp_inc = 1,
पूर्ण;

स्थिर काष्ठा peak_usb_adapter pcan_usb_x6 = अणु
	.name = "PCAN-USB X6",
	.device_id = PCAN_USBX6_PRODUCT_ID,
	.ctrl_count = PCAN_USBPROFD_CHANNEL_COUNT,
	.ctrlmode_supported = CAN_CTRLMODE_FD |
			CAN_CTRLMODE_3_SAMPLES | CAN_CTRLMODE_LISTENONLY |
			CAN_CTRLMODE_ONE_SHOT | CAN_CTRLMODE_CC_LEN8_DLC,
	.घड़ी = अणु
		.freq = PCAN_UFD_CRYSTAL_HZ,
	पूर्ण,
	.bittiming_स्थिर = &pcan_usb_x6_स्थिर,
	.data_bittiming_स्थिर = &pcan_usb_x6_data_स्थिर,

	/* size of device निजी data */
	.माप_dev_निजी = माप(काष्ठा pcan_usb_fd_device),

	.ethtool_ops = &pcan_usb_fd_ethtool_ops,

	/* बारtamps usage */
	.ts_used_bits = 32,
	.us_per_ts_scale = 1, /* us = (ts * scale) >> shअगरt */
	.us_per_ts_shअगरt = 0,

	/* give here messages in/out endpoपूर्णांकs */
	.ep_msg_in = PCAN_USBPRO_EP_MSGIN,
	.ep_msg_out = अणुPCAN_USBPRO_EP_MSGOUT_0, PCAN_USBPRO_EP_MSGOUT_1पूर्ण,

	/* size of rx/tx usb buffers */
	.rx_buffer_size = PCAN_UFD_RX_BUFFER_SIZE,
	.tx_buffer_size = PCAN_UFD_TX_BUFFER_SIZE,

	/* device callbacks */
	.पूर्णांकf_probe = pcan_usb_pro_probe,	/* same as PCAN-USB Pro */
	.dev_init = pcan_usb_fd_init,

	.dev_निकास = pcan_usb_fd_निकास,
	.dev_मुक्त = pcan_usb_fd_मुक्त,
	.dev_set_bus = pcan_usb_fd_set_bus,
	.dev_set_bittiming = pcan_usb_fd_set_bittiming_slow,
	.dev_set_data_bittiming = pcan_usb_fd_set_bittiming_fast,
	.dev_decode_buf = pcan_usb_fd_decode_buf,
	.dev_start = pcan_usb_fd_start,
	.dev_stop = pcan_usb_fd_stop,
	.dev_restart_async = pcan_usb_fd_restart_async,
	.dev_encode_msg = pcan_usb_fd_encode_msg,

	.करो_get_berr_counter = pcan_usb_fd_get_berr_counter,
पूर्ण;
