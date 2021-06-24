<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/* Driver क्रम Theobroma Systems UCAN devices, Protocol Version 3
 *
 * Copyright (C) 2018 Theobroma Systems Design und Consulting GmbH
 *
 *
 * General Description:
 *
 * The USB Device uses three Endpoपूर्णांकs:
 *
 *   CONTROL Endpoपूर्णांक: Is used the setup the device (start, stop,
 *   info, configure).
 *
 *   IN Endpoपूर्णांक: The device sends CAN Frame Messages and Device
 *   Inक्रमmation using the IN endpoपूर्णांक.
 *
 *   OUT Endpoपूर्णांक: The driver sends configuration requests, and CAN
 *   Frames on the out endpoपूर्णांक.
 *
 * Error Handling:
 *
 *   If error reporting is turned on the device encodes error पूर्णांकo CAN
 *   error frames (see uapi/linux/can/error.h) and sends it using the
 *   IN Endpoपूर्णांक. The driver updates statistics and क्रमward it.
 */

#समावेश <linux/can.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/can/error.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>

#घोषणा UCAN_DRIVER_NAME "ucan"
#घोषणा UCAN_MAX_RX_URBS 8
/* the CAN controller needs a जबतक to enable/disable the bus */
#घोषणा UCAN_USB_CTL_PIPE_TIMEOUT 1000
/* this driver currently supports protocol version 3 only */
#घोषणा UCAN_PROTOCOL_VERSION_MIN 3
#घोषणा UCAN_PROTOCOL_VERSION_MAX 3

/* UCAN Message Definitions
 * ------------------------
 *
 *  ucan_message_out_t and ucan_message_in_t define the messages
 *  transmitted on the OUT and IN endpoपूर्णांक.
 *
 *  Multibyte fields are transmitted with little endianness
 *
 *  INTR Endpoपूर्णांक: a single uपूर्णांक32_t storing the current space in the fअगरo
 *
 *  OUT Endpoपूर्णांक: single message of type ucan_message_out_t is
 *    transmitted on the out endpoपूर्णांक
 *
 *  IN Endpoपूर्णांक: multiple messages ucan_message_in_t concateted in
 *    the following way:
 *
 *	m[n].len <=> the length अगर message n(including the header in bytes)
 *	m[n] is is aligned to a 4 byte boundary, hence
 *	  offset(m[0])	 := 0;
 *	  offset(m[n+1]) := offset(m[n]) + (m[n].len + 3) & 3
 *
 *	this implies that
 *	  offset(m[n]) % 4 <=> 0
 */

/* Device Global Commands */
क्रमागत अणु
	UCAN_DEVICE_GET_FW_STRING = 0,
पूर्ण;

/* UCAN Commands */
क्रमागत अणु
	/* start the can transceiver - val defines the operation mode */
	UCAN_COMMAND_START = 0,
	/* cancel pending transmissions and stop the can transceiver */
	UCAN_COMMAND_STOP = 1,
	/* send can transceiver पूर्णांकo low-घातer sleep mode */
	UCAN_COMMAND_SLEEP = 2,
	/* wake up can transceiver from low-घातer sleep mode */
	UCAN_COMMAND_WAKEUP = 3,
	/* reset the can transceiver */
	UCAN_COMMAND_RESET = 4,
	/* get piece of info from the can transceiver - subcmd defines what
	 * piece
	 */
	UCAN_COMMAND_GET = 5,
	/* clear or disable hardware filter - subcmd defines which of the two */
	UCAN_COMMAND_FILTER = 6,
	/* Setup bittiming */
	UCAN_COMMAND_SET_BITTIMING = 7,
	/* recover from bus-off state */
	UCAN_COMMAND_RESTART = 8,
पूर्ण;

/* UCAN_COMMAND_START and UCAN_COMMAND_GET_INFO operation modes (biपंचांगap).
 * Undefined bits must be set to 0.
 */
क्रमागत अणु
	UCAN_MODE_LOOPBACK = BIT(0),
	UCAN_MODE_SILENT = BIT(1),
	UCAN_MODE_3_SAMPLES = BIT(2),
	UCAN_MODE_ONE_SHOT = BIT(3),
	UCAN_MODE_BERR_REPORT = BIT(4),
पूर्ण;

/* UCAN_COMMAND_GET subcommands */
क्रमागत अणु
	UCAN_COMMAND_GET_INFO = 0,
	UCAN_COMMAND_GET_PROTOCOL_VERSION = 1,
पूर्ण;

/* UCAN_COMMAND_FILTER subcommands */
क्रमागत अणु
	UCAN_FILTER_CLEAR = 0,
	UCAN_FILTER_DISABLE = 1,
	UCAN_FILTER_ENABLE = 2,
पूर्ण;

/* OUT endpoपूर्णांक message types */
क्रमागत अणु
	UCAN_OUT_TX = 2,     /* transmit a CAN frame */
पूर्ण;

/* IN endpoपूर्णांक message types */
क्रमागत अणु
	UCAN_IN_TX_COMPLETE = 1,  /* CAN frame transmission completed */
	UCAN_IN_RX = 2,           /* CAN frame received */
पूर्ण;

काष्ठा ucan_ctl_cmd_start अणु
	__le16 mode;         /* OR-ing any of UCAN_MODE_* */
पूर्ण __packed;

काष्ठा ucan_ctl_cmd_set_bittiming अणु
	__le32 tq;           /* Time quanta (TQ) in nanoseconds */
	__le16 brp;          /* TQ Prescaler */
	__le16 sample_poपूर्णांक; /* Samplepoपूर्णांक on tenth percent */
	u8 prop_seg;         /* Propagation segment in TQs */
	u8 phase_seg1;       /* Phase buffer segment 1 in TQs */
	u8 phase_seg2;       /* Phase buffer segment 2 in TQs */
	u8 sjw;              /* Synchronisation jump width in TQs */
पूर्ण __packed;

काष्ठा ucan_ctl_cmd_device_info अणु
	__le32 freq;         /* Clock Frequency क्रम tq generation */
	u8 tx_fअगरo;          /* Size of the transmission fअगरo */
	u8 sjw_max;          /* can_bittiming fields... */
	u8 tseg1_min;
	u8 tseg1_max;
	u8 tseg2_min;
	u8 tseg2_max;
	__le16 brp_inc;
	__le32 brp_min;
	__le32 brp_max;      /* ...can_bittiming fields */
	__le16 ctrlmodes;    /* supported control modes */
	__le16 hwfilter;     /* Number of HW filter banks */
	__le16 rxmboxes;     /* Number of receive Mailboxes */
पूर्ण __packed;

काष्ठा ucan_ctl_cmd_get_protocol_version अणु
	__le32 version;
पूर्ण __packed;

जोड़ ucan_ctl_payload अणु
	/* Setup Bittiming
	 * bmRequest == UCAN_COMMAND_START
	 */
	काष्ठा ucan_ctl_cmd_start cmd_start;
	/* Setup Bittiming
	 * bmRequest == UCAN_COMMAND_SET_BITTIMING
	 */
	काष्ठा ucan_ctl_cmd_set_bittiming cmd_set_bittiming;
	/* Get Device Inक्रमmation
	 * bmRequest == UCAN_COMMAND_GET; wValue = UCAN_COMMAND_GET_INFO
	 */
	काष्ठा ucan_ctl_cmd_device_info cmd_get_device_info;
	/* Get Protocol Version
	 * bmRequest == UCAN_COMMAND_GET;
	 * wValue = UCAN_COMMAND_GET_PROTOCOL_VERSION
	 */
	काष्ठा ucan_ctl_cmd_get_protocol_version cmd_get_protocol_version;

	u8 raw[128];
पूर्ण __packed;

क्रमागत अणु
	UCAN_TX_COMPLETE_SUCCESS = BIT(0),
पूर्ण;

/* Transmission Complete within ucan_message_in */
काष्ठा ucan_tx_complete_entry_t अणु
	u8 echo_index;
	u8 flags;
पूर्ण __packed __aligned(0x2);

/* CAN Data message क्रमmat within ucan_message_in/out */
काष्ठा ucan_can_msg अणु
	/* note DLC is computed by
	 *    msg.len - माप (msg.len)
	 *            - माप (msg.type)
	 *            - माप (msg.can_msg.id)
	 */
	__le32 id;

	जोड़ अणु
		u8 data[CAN_MAX_DLEN];  /* Data of CAN frames */
		u8 dlc;                 /* RTR dlc */
	पूर्ण;
पूर्ण __packed;

/* OUT Endpoपूर्णांक, outbound messages */
काष्ठा ucan_message_out अणु
	__le16 len; /* Length of the content include header */
	u8 type;    /* UCAN_OUT_TX and मित्रs */
	u8 subtype; /* command sub type */

	जोड़ अणु
		/* Transmit CAN frame
		 * (type == UCAN_TX) && ((msg.can_msg.id & CAN_RTR_FLAG) == 0)
		 * subtype stores the echo id
		 */
		काष्ठा ucan_can_msg can_msg;
	पूर्ण msg;
पूर्ण __packed __aligned(0x4);

/* IN Endpoपूर्णांक, inbound messages */
काष्ठा ucan_message_in अणु
	__le16 len; /* Length of the content include header */
	u8 type;    /* UCAN_IN_RX and मित्रs */
	u8 subtype; /* command sub type */

	जोड़ अणु
		/* CAN Frame received
		 * (type == UCAN_IN_RX)
		 * && ((msg.can_msg.id & CAN_RTR_FLAG) == 0)
		 */
		काष्ठा ucan_can_msg can_msg;

		/* CAN transmission complete
		 * (type == UCAN_IN_TX_COMPLETE)
		 */
		काष्ठा ucan_tx_complete_entry_t can_tx_complete_msg[0];
	पूर्ण __aligned(0x4) msg;
पूर्ण __packed __aligned(0x4);

/* Macros to calculate message lengths */
#घोषणा UCAN_OUT_HDR_SIZE दुरत्व(काष्ठा ucan_message_out, msg)

#घोषणा UCAN_IN_HDR_SIZE दुरत्व(काष्ठा ucan_message_in, msg)
#घोषणा UCAN_IN_LEN(member) (UCAN_OUT_HDR_SIZE + माप(member))

काष्ठा ucan_priv;

/* Context Inक्रमmation क्रम transmission URBs */
काष्ठा ucan_urb_context अणु
	काष्ठा ucan_priv *up;
	u8 dlc;
	bool allocated;
पूर्ण;

/* Inक्रमmation reported by the USB device */
काष्ठा ucan_device_info अणु
	काष्ठा can_bittiming_स्थिर bittiming_स्थिर;
	u8 tx_fअगरo;
पूर्ण;

/* Driver निजी data */
काष्ठा ucan_priv अणु
	/* must be the first member */
	काष्ठा can_priv can;

	/* linux USB device काष्ठाures */
	काष्ठा usb_device *udev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा net_device *netdev;

	/* lock क्रम can->echo_skb (used around
	 * can_put/get/मुक्त_echo_skb
	 */
	spinlock_t echo_skb_lock;

	/* usb device inक्रमmation inक्रमmation */
	u8 पूर्णांकf_index;
	u8 in_ep_addr;
	u8 out_ep_addr;
	u16 in_ep_size;

	/* transmission and reception buffers */
	काष्ठा usb_anchor rx_urbs;
	काष्ठा usb_anchor tx_urbs;

	जोड़ ucan_ctl_payload *ctl_msg_buffer;
	काष्ठा ucan_device_info device_info;

	/* transmission control inक्रमmation and locks */
	spinlock_t context_lock;
	अचिन्हित पूर्णांक available_tx_urbs;
	काष्ठा ucan_urb_context *context_array;
पूर्ण;

अटल u8 ucan_can_cc_dlc2len(काष्ठा ucan_can_msg *msg, u16 len)
अणु
	अगर (le32_to_cpu(msg->id) & CAN_RTR_FLAG)
		वापस can_cc_dlc2len(msg->dlc);
	अन्यथा
		वापस can_cc_dlc2len(len - (UCAN_IN_HDR_SIZE + माप(msg->id)));
पूर्ण

अटल व्योम ucan_release_context_array(काष्ठा ucan_priv *up)
अणु
	अगर (!up->context_array)
		वापस;

	/* lock is not needed because, driver is currently खोलोing or closing */
	up->available_tx_urbs = 0;

	kमुक्त(up->context_array);
	up->context_array = शून्य;
पूर्ण

अटल पूर्णांक ucan_alloc_context_array(काष्ठा ucan_priv *up)
अणु
	पूर्णांक i;

	/* release contexts अगर any */
	ucan_release_context_array(up);

	up->context_array = kसुस्मृति(up->device_info.tx_fअगरo,
				    माप(*up->context_array),
				    GFP_KERNEL);
	अगर (!up->context_array) अणु
		netdev_err(up->netdev,
			   "Not enough memory to allocate tx contexts\n");
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < up->device_info.tx_fअगरo; i++) अणु
		up->context_array[i].allocated = false;
		up->context_array[i].up = up;
	पूर्ण

	/* lock is not needed because, driver is currently खोलोing */
	up->available_tx_urbs = up->device_info.tx_fअगरo;

	वापस 0;
पूर्ण

अटल काष्ठा ucan_urb_context *ucan_alloc_context(काष्ठा ucan_priv *up)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ flags;
	काष्ठा ucan_urb_context *ret = शून्य;

	अगर (WARN_ON_ONCE(!up->context_array))
		वापस शून्य;

	/* execute context operation atomically */
	spin_lock_irqsave(&up->context_lock, flags);

	क्रम (i = 0; i < up->device_info.tx_fअगरo; i++) अणु
		अगर (!up->context_array[i].allocated) अणु
			/* update context */
			ret = &up->context_array[i];
			up->context_array[i].allocated = true;

			/* stop queue अगर necessary */
			up->available_tx_urbs--;
			अगर (!up->available_tx_urbs)
				netअगर_stop_queue(up->netdev);

			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&up->context_lock, flags);
	वापस ret;
पूर्ण

अटल bool ucan_release_context(काष्ठा ucan_priv *up,
				 काष्ठा ucan_urb_context *ctx)
अणु
	अचिन्हित दीर्घ flags;
	bool ret = false;

	अगर (WARN_ON_ONCE(!up->context_array))
		वापस false;

	/* execute context operation atomically */
	spin_lock_irqsave(&up->context_lock, flags);

	/* context was not allocated, maybe the device sent garbage */
	अगर (ctx->allocated) अणु
		ctx->allocated = false;

		/* check अगर the queue needs to be woken */
		अगर (!up->available_tx_urbs)
			netअगर_wake_queue(up->netdev);
		up->available_tx_urbs++;

		ret = true;
	पूर्ण

	spin_unlock_irqrestore(&up->context_lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक ucan_ctrl_command_out(काष्ठा ucan_priv *up,
				 u8 cmd, u16 subcmd, u16 datalen)
अणु
	वापस usb_control_msg(up->udev,
			       usb_sndctrlpipe(up->udev, 0),
			       cmd,
			       USB_सूची_OUT | USB_TYPE_VENDOR |
						USB_RECIP_INTERFACE,
			       subcmd,
			       up->पूर्णांकf_index,
			       up->ctl_msg_buffer,
			       datalen,
			       UCAN_USB_CTL_PIPE_TIMEOUT);
पूर्ण

अटल पूर्णांक ucan_device_request_in(काष्ठा ucan_priv *up,
				  u8 cmd, u16 subcmd, u16 datalen)
अणु
	वापस usb_control_msg(up->udev,
			       usb_rcvctrlpipe(up->udev, 0),
			       cmd,
			       USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			       subcmd,
			       0,
			       up->ctl_msg_buffer,
			       datalen,
			       UCAN_USB_CTL_PIPE_TIMEOUT);
पूर्ण

/* Parse the device inक्रमmation काष्ठाure reported by the device and
 * setup निजी variables accordingly
 */
अटल व्योम ucan_parse_device_info(काष्ठा ucan_priv *up,
				   काष्ठा ucan_ctl_cmd_device_info *device_info)
अणु
	काष्ठा can_bittiming_स्थिर *bittiming =
		&up->device_info.bittiming_स्थिर;
	u16 ctrlmodes;

	/* store the data */
	up->can.घड़ी.freq = le32_to_cpu(device_info->freq);
	up->device_info.tx_fअगरo = device_info->tx_fअगरo;
	म_नकल(bittiming->name, "ucan");
	bittiming->tseg1_min = device_info->tseg1_min;
	bittiming->tseg1_max = device_info->tseg1_max;
	bittiming->tseg2_min = device_info->tseg2_min;
	bittiming->tseg2_max = device_info->tseg2_max;
	bittiming->sjw_max = device_info->sjw_max;
	bittiming->brp_min = le32_to_cpu(device_info->brp_min);
	bittiming->brp_max = le32_to_cpu(device_info->brp_max);
	bittiming->brp_inc = le16_to_cpu(device_info->brp_inc);

	ctrlmodes = le16_to_cpu(device_info->ctrlmodes);

	up->can.ctrlmode_supported = 0;

	अगर (ctrlmodes & UCAN_MODE_LOOPBACK)
		up->can.ctrlmode_supported |= CAN_CTRLMODE_LOOPBACK;
	अगर (ctrlmodes & UCAN_MODE_SILENT)
		up->can.ctrlmode_supported |= CAN_CTRLMODE_LISTENONLY;
	अगर (ctrlmodes & UCAN_MODE_3_SAMPLES)
		up->can.ctrlmode_supported |= CAN_CTRLMODE_3_SAMPLES;
	अगर (ctrlmodes & UCAN_MODE_ONE_SHOT)
		up->can.ctrlmode_supported |= CAN_CTRLMODE_ONE_SHOT;
	अगर (ctrlmodes & UCAN_MODE_BERR_REPORT)
		up->can.ctrlmode_supported |= CAN_CTRLMODE_BERR_REPORTING;
पूर्ण

/* Handle a CAN error frame that we have received from the device.
 * Returns true अगर the can state has changed.
 */
अटल bool ucan_handle_error_frame(काष्ठा ucan_priv *up,
				    काष्ठा ucan_message_in *m,
				    canid_t canid)
अणु
	क्रमागत can_state new_state = up->can.state;
	काष्ठा net_device_stats *net_stats = &up->netdev->stats;
	काष्ठा can_device_stats *can_stats = &up->can.can_stats;

	अगर (canid & CAN_ERR_LOSTARB)
		can_stats->arbitration_lost++;

	अगर (canid & CAN_ERR_BUSERROR)
		can_stats->bus_error++;

	अगर (canid & CAN_ERR_ACK)
		net_stats->tx_errors++;

	अगर (canid & CAN_ERR_BUSOFF)
		new_state = CAN_STATE_BUS_OFF;

	/* controller problems, details in data[1] */
	अगर (canid & CAN_ERR_CRTL) अणु
		u8 d1 = m->msg.can_msg.data[1];

		अगर (d1 & CAN_ERR_CRTL_RX_OVERFLOW)
			net_stats->rx_over_errors++;

		/* controller state bits: अगर multiple are set the worst wins */
		अगर (d1 & CAN_ERR_CRTL_ACTIVE)
			new_state = CAN_STATE_ERROR_ACTIVE;

		अगर (d1 & (CAN_ERR_CRTL_RX_WARNING | CAN_ERR_CRTL_TX_WARNING))
			new_state = CAN_STATE_ERROR_WARNING;

		अगर (d1 & (CAN_ERR_CRTL_RX_PASSIVE | CAN_ERR_CRTL_TX_PASSIVE))
			new_state = CAN_STATE_ERROR_PASSIVE;
	पूर्ण

	/* protocol error, details in data[2] */
	अगर (canid & CAN_ERR_PROT) अणु
		u8 d2 = m->msg.can_msg.data[2];

		अगर (d2 & CAN_ERR_PROT_TX)
			net_stats->tx_errors++;
		अन्यथा
			net_stats->rx_errors++;
	पूर्ण

	/* no state change - we are करोne */
	अगर (up->can.state == new_state)
		वापस false;

	/* we चयनed पूर्णांकo a better state */
	अगर (up->can.state > new_state) अणु
		up->can.state = new_state;
		वापस true;
	पूर्ण

	/* we चयनed पूर्णांकo a worse state */
	up->can.state = new_state;
	चयन (new_state) अणु
	हाल CAN_STATE_BUS_OFF:
		can_stats->bus_off++;
		can_bus_off(up->netdev);
		अवरोध;
	हाल CAN_STATE_ERROR_PASSIVE:
		can_stats->error_passive++;
		अवरोध;
	हाल CAN_STATE_ERROR_WARNING:
		can_stats->error_warning++;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस true;
पूर्ण

/* Callback on reception of a can frame via the IN endpoपूर्णांक
 *
 * This function allocates an skb and transferres it to the Linux
 * network stack
 */
अटल व्योम ucan_rx_can_msg(काष्ठा ucan_priv *up, काष्ठा ucan_message_in *m)
अणु
	पूर्णांक len;
	canid_t canid;
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;
	काष्ठा net_device_stats *stats = &up->netdev->stats;

	/* get the contents of the length field */
	len = le16_to_cpu(m->len);

	/* check sanity */
	अगर (len < UCAN_IN_HDR_SIZE + माप(m->msg.can_msg.id)) अणु
		netdev_warn(up->netdev, "invalid input message len: %d\n", len);
		वापस;
	पूर्ण

	/* handle error frames */
	canid = le32_to_cpu(m->msg.can_msg.id);
	अगर (canid & CAN_ERR_FLAG) अणु
		bool busstate_changed = ucan_handle_error_frame(up, m, canid);

		/* अगर berr-reporting is off only state changes get through */
		अगर (!(up->can.ctrlmode & CAN_CTRLMODE_BERR_REPORTING) &&
		    !busstate_changed)
			वापस;
	पूर्ण अन्यथा अणु
		canid_t canid_mask;
		/* compute the mask क्रम canid */
		canid_mask = CAN_RTR_FLAG;
		अगर (canid & CAN_EFF_FLAG)
			canid_mask |= CAN_EFF_MASK | CAN_EFF_FLAG;
		अन्यथा
			canid_mask |= CAN_SFF_MASK;

		अगर (canid & ~canid_mask)
			netdev_warn(up->netdev,
				    "unexpected bits set (canid %x, mask %x)",
				    canid, canid_mask);

		canid &= canid_mask;
	पूर्ण

	/* allocate skb */
	skb = alloc_can_skb(up->netdev, &cf);
	अगर (!skb)
		वापस;

	/* fill the can frame */
	cf->can_id = canid;

	/* compute DLC taking RTR_FLAG पूर्णांकo account */
	cf->len = ucan_can_cc_dlc2len(&m->msg.can_msg, len);

	/* copy the payload of non RTR frames */
	अगर (!(cf->can_id & CAN_RTR_FLAG) || (cf->can_id & CAN_ERR_FLAG))
		स_नकल(cf->data, m->msg.can_msg.data, cf->len);

	/* करोn't count error frames as real packets */
	stats->rx_packets++;
	stats->rx_bytes += cf->len;

	/* pass it to Linux */
	netअगर_rx(skb);
पूर्ण

/* callback indicating completed transmission */
अटल व्योम ucan_tx_complete_msg(काष्ठा ucan_priv *up,
				 काष्ठा ucan_message_in *m)
अणु
	अचिन्हित दीर्घ flags;
	u16 count, i;
	u8 echo_index, dlc;
	u16 len = le16_to_cpu(m->len);

	काष्ठा ucan_urb_context *context;

	अगर (len < UCAN_IN_HDR_SIZE || (len % 2 != 0)) अणु
		netdev_err(up->netdev, "invalid tx complete length\n");
		वापस;
	पूर्ण

	count = (len - UCAN_IN_HDR_SIZE) / 2;
	क्रम (i = 0; i < count; i++) अणु
		/* we did not submit such echo ids */
		echo_index = m->msg.can_tx_complete_msg[i].echo_index;
		अगर (echo_index >= up->device_info.tx_fअगरo) अणु
			up->netdev->stats.tx_errors++;
			netdev_err(up->netdev,
				   "invalid echo_index %d received\n",
				   echo_index);
			जारी;
		पूर्ण

		/* gather inक्रमmation from the context */
		context = &up->context_array[echo_index];
		dlc = READ_ONCE(context->dlc);

		/* Release context and restart queue अगर necessary.
		 * Also check अगर the context was allocated
		 */
		अगर (!ucan_release_context(up, context))
			जारी;

		spin_lock_irqsave(&up->echo_skb_lock, flags);
		अगर (m->msg.can_tx_complete_msg[i].flags &
		    UCAN_TX_COMPLETE_SUCCESS) अणु
			/* update statistics */
			up->netdev->stats.tx_packets++;
			up->netdev->stats.tx_bytes += dlc;
			can_get_echo_skb(up->netdev, echo_index, शून्य);
		पूर्ण अन्यथा अणु
			up->netdev->stats.tx_dropped++;
			can_मुक्त_echo_skb(up->netdev, echo_index, शून्य);
		पूर्ण
		spin_unlock_irqrestore(&up->echo_skb_lock, flags);
	पूर्ण
पूर्ण

/* callback on reception of a USB message */
अटल व्योम ucan_पढ़ो_bulk_callback(काष्ठा urb *urb)
अणु
	पूर्णांक ret;
	पूर्णांक pos;
	काष्ठा ucan_priv *up = urb->context;
	काष्ठा net_device *netdev = up->netdev;
	काष्ठा ucan_message_in *m;

	/* the device is not up and the driver should not receive any
	 * data on the bulk in pipe
	 */
	अगर (WARN_ON(!up->context_array)) अणु
		usb_मुक्त_coherent(up->udev,
				  up->in_ep_size,
				  urb->transfer_buffer,
				  urb->transfer_dma);
		वापस;
	पूर्ण

	/* check URB status */
	चयन (urb->status) अणु
	हाल 0:
		अवरोध;
	हाल -ENOENT:
	हाल -EPIPE:
	हाल -EPROTO:
	हाल -ESHUTDOWN:
	हाल -ETIME:
		/* urb is not resubmitted -> मुक्त dma data */
		usb_मुक्त_coherent(up->udev,
				  up->in_ep_size,
				  urb->transfer_buffer,
				  urb->transfer_dma);
		netdev_dbg(up->netdev, "not resubmitting urb; status: %d\n",
			   urb->status);
		वापस;
	शेष:
		जाओ resubmit;
	पूर्ण

	/* sanity check */
	अगर (!netअगर_device_present(netdev))
		वापस;

	/* iterate over input */
	pos = 0;
	जबतक (pos < urb->actual_length) अणु
		पूर्णांक len;

		/* check sanity (length of header) */
		अगर ((urb->actual_length - pos) < UCAN_IN_HDR_SIZE) अणु
			netdev_warn(up->netdev,
				    "invalid message (short; no hdr; l:%d)\n",
				    urb->actual_length);
			जाओ resubmit;
		पूर्ण

		/* setup the message address */
		m = (काष्ठा ucan_message_in *)
			((u8 *)urb->transfer_buffer + pos);
		len = le16_to_cpu(m->len);

		/* check sanity (length of content) */
		अगर (urb->actual_length - pos < len) अणु
			netdev_warn(up->netdev,
				    "invalid message (short; no data; l:%d)\n",
				    urb->actual_length);
			prपूर्णांक_hex_dump(KERN_WARNING,
				       "raw data: ",
				       DUMP_PREFIX_ADDRESS,
				       16,
				       1,
				       urb->transfer_buffer,
				       urb->actual_length,
				       true);

			जाओ resubmit;
		पूर्ण

		चयन (m->type) अणु
		हाल UCAN_IN_RX:
			ucan_rx_can_msg(up, m);
			अवरोध;
		हाल UCAN_IN_TX_COMPLETE:
			ucan_tx_complete_msg(up, m);
			अवरोध;
		शेष:
			netdev_warn(up->netdev,
				    "invalid message (type; t:%d)\n",
				    m->type);
			अवरोध;
		पूर्ण

		/* proceed to next message */
		pos += len;
		/* align to 4 byte boundary */
		pos = round_up(pos, 4);
	पूर्ण

resubmit:
	/* resubmit urb when करोne */
	usb_fill_bulk_urb(urb, up->udev,
			  usb_rcvbulkpipe(up->udev,
					  up->in_ep_addr),
			  urb->transfer_buffer,
			  up->in_ep_size,
			  ucan_पढ़ो_bulk_callback,
			  up);

	usb_anchor_urb(urb, &up->rx_urbs);
	ret = usb_submit_urb(urb, GFP_ATOMIC);

	अगर (ret < 0) अणु
		netdev_err(up->netdev,
			   "failed resubmitting read bulk urb: %d\n",
			   ret);

		usb_unanchor_urb(urb);
		usb_मुक्त_coherent(up->udev,
				  up->in_ep_size,
				  urb->transfer_buffer,
				  urb->transfer_dma);

		अगर (ret == -ENODEV)
			netअगर_device_detach(netdev);
	पूर्ण
पूर्ण

/* callback after transmission of a USB message */
अटल व्योम ucan_ग_लिखो_bulk_callback(काष्ठा urb *urb)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ucan_priv *up;
	काष्ठा ucan_urb_context *context = urb->context;

	/* get the urb context */
	अगर (WARN_ON_ONCE(!context))
		वापस;

	/* मुक्त up our allocated buffer */
	usb_मुक्त_coherent(urb->dev,
			  माप(काष्ठा ucan_message_out),
			  urb->transfer_buffer,
			  urb->transfer_dma);

	up = context->up;
	अगर (WARN_ON_ONCE(!up))
		वापस;

	/* sanity check */
	अगर (!netअगर_device_present(up->netdev))
		वापस;

	/* transmission failed (USB - the device will not send a TX complete) */
	अगर (urb->status) अणु
		netdev_warn(up->netdev,
			    "failed to transmit USB message to device: %d\n",
			     urb->status);

		/* update counters an cleanup */
		spin_lock_irqsave(&up->echo_skb_lock, flags);
		can_मुक्त_echo_skb(up->netdev, context - up->context_array, शून्य);
		spin_unlock_irqrestore(&up->echo_skb_lock, flags);

		up->netdev->stats.tx_dropped++;

		/* release context and restart the queue अगर necessary */
		अगर (!ucan_release_context(up, context))
			netdev_err(up->netdev,
				   "urb failed, failed to release context\n");
	पूर्ण
पूर्ण

अटल व्योम ucan_cleanup_rx_urbs(काष्ठा ucan_priv *up, काष्ठा urb **urbs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < UCAN_MAX_RX_URBS; i++) अणु
		अगर (urbs[i]) अणु
			usb_unanchor_urb(urbs[i]);
			usb_मुक्त_coherent(up->udev,
					  up->in_ep_size,
					  urbs[i]->transfer_buffer,
					  urbs[i]->transfer_dma);
			usb_मुक्त_urb(urbs[i]);
		पूर्ण
	पूर्ण

	स_रखो(urbs, 0, माप(*urbs) * UCAN_MAX_RX_URBS);
पूर्ण

अटल पूर्णांक ucan_prepare_and_anchor_rx_urbs(काष्ठा ucan_priv *up,
					   काष्ठा urb **urbs)
अणु
	पूर्णांक i;

	स_रखो(urbs, 0, माप(*urbs) * UCAN_MAX_RX_URBS);

	क्रम (i = 0; i < UCAN_MAX_RX_URBS; i++) अणु
		व्योम *buf;

		urbs[i] = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!urbs[i])
			जाओ err;

		buf = usb_alloc_coherent(up->udev,
					 up->in_ep_size,
					 GFP_KERNEL, &urbs[i]->transfer_dma);
		अगर (!buf) अणु
			/* cleanup this urb */
			usb_मुक्त_urb(urbs[i]);
			urbs[i] = शून्य;
			जाओ err;
		पूर्ण

		usb_fill_bulk_urb(urbs[i], up->udev,
				  usb_rcvbulkpipe(up->udev,
						  up->in_ep_addr),
				  buf,
				  up->in_ep_size,
				  ucan_पढ़ो_bulk_callback,
				  up);

		urbs[i]->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

		usb_anchor_urb(urbs[i], &up->rx_urbs);
	पूर्ण
	वापस 0;

err:
	/* cleanup other unsubmitted urbs */
	ucan_cleanup_rx_urbs(up, urbs);
	वापस -ENOMEM;
पूर्ण

/* Submits rx urbs with the semantic: Either submit all, or cleanup
 * everything. I हाल of errors submitted urbs are समाप्तed and all urbs in
 * the array are मुक्तd. I हाल of no errors every entry in the urb
 * array is set to शून्य.
 */
अटल पूर्णांक ucan_submit_rx_urbs(काष्ठा ucan_priv *up, काष्ठा urb **urbs)
अणु
	पूर्णांक i, ret;

	/* Iterate over all urbs to submit. On success हटाओ the urb
	 * from the list.
	 */
	क्रम (i = 0; i < UCAN_MAX_RX_URBS; i++) अणु
		ret = usb_submit_urb(urbs[i], GFP_KERNEL);
		अगर (ret) अणु
			netdev_err(up->netdev,
				   "could not submit urb; code: %d\n",
				   ret);
			जाओ err;
		पूर्ण

		/* Anchor URB and drop reference, USB core will take
		 * care of मुक्तing it
		 */
		usb_मुक्त_urb(urbs[i]);
		urbs[i] = शून्य;
	पूर्ण
	वापस 0;

err:
	/* Cleanup unsubmitted urbs */
	ucan_cleanup_rx_urbs(up, urbs);

	/* Kill urbs that are alपढ़ोy submitted */
	usb_समाप्त_anchored_urbs(&up->rx_urbs);

	वापस ret;
पूर्ण

/* Open the network device */
अटल पूर्णांक ucan_खोलो(काष्ठा net_device *netdev)
अणु
	पूर्णांक ret, ret_cleanup;
	u16 ctrlmode;
	काष्ठा urb *urbs[UCAN_MAX_RX_URBS];
	काष्ठा ucan_priv *up = netdev_priv(netdev);

	ret = ucan_alloc_context_array(up);
	अगर (ret)
		वापस ret;

	/* Allocate and prepare IN URBS - allocated and anchored
	 * urbs are stored in urbs[] क्रम clean
	 */
	ret = ucan_prepare_and_anchor_rx_urbs(up, urbs);
	अगर (ret)
		जाओ err_contexts;

	/* Check the control mode */
	ctrlmode = 0;
	अगर (up->can.ctrlmode & CAN_CTRLMODE_LOOPBACK)
		ctrlmode |= UCAN_MODE_LOOPBACK;
	अगर (up->can.ctrlmode & CAN_CTRLMODE_LISTENONLY)
		ctrlmode |= UCAN_MODE_SILENT;
	अगर (up->can.ctrlmode & CAN_CTRLMODE_3_SAMPLES)
		ctrlmode |= UCAN_MODE_3_SAMPLES;
	अगर (up->can.ctrlmode & CAN_CTRLMODE_ONE_SHOT)
		ctrlmode |= UCAN_MODE_ONE_SHOT;

	/* Enable this in any हाल - filtering is करोwn within the
	 * receive path
	 */
	ctrlmode |= UCAN_MODE_BERR_REPORT;
	up->ctl_msg_buffer->cmd_start.mode = cpu_to_le16(ctrlmode);

	/* Driver is पढ़ोy to receive data - start the USB device */
	ret = ucan_ctrl_command_out(up, UCAN_COMMAND_START, 0, 2);
	अगर (ret < 0) अणु
		netdev_err(up->netdev,
			   "could not start device, code: %d\n",
			   ret);
		जाओ err_reset;
	पूर्ण

	/* Call CAN layer खोलो */
	ret = खोलो_candev(netdev);
	अगर (ret)
		जाओ err_stop;

	/* Driver is पढ़ोy to receive data. Submit RX URBS */
	ret = ucan_submit_rx_urbs(up, urbs);
	अगर (ret)
		जाओ err_stop;

	up->can.state = CAN_STATE_ERROR_ACTIVE;

	/* Start the network queue */
	netअगर_start_queue(netdev);

	वापस 0;

err_stop:
	/* The device have started alपढ़ोy stop it */
	ret_cleanup = ucan_ctrl_command_out(up, UCAN_COMMAND_STOP, 0, 0);
	अगर (ret_cleanup < 0)
		netdev_err(up->netdev,
			   "could not stop device, code: %d\n",
			   ret_cleanup);

err_reset:
	/* The device might have received data, reset it क्रम
	 * consistent state
	 */
	ret_cleanup = ucan_ctrl_command_out(up, UCAN_COMMAND_RESET, 0, 0);
	अगर (ret_cleanup < 0)
		netdev_err(up->netdev,
			   "could not reset device, code: %d\n",
			   ret_cleanup);

	/* clean up unsubmitted urbs */
	ucan_cleanup_rx_urbs(up, urbs);

err_contexts:
	ucan_release_context_array(up);
	वापस ret;
पूर्ण

अटल काष्ठा urb *ucan_prepare_tx_urb(काष्ठा ucan_priv *up,
				       काष्ठा ucan_urb_context *context,
				       काष्ठा can_frame *cf,
				       u8 echo_index)
अणु
	पूर्णांक mlen;
	काष्ठा urb *urb;
	काष्ठा ucan_message_out *m;

	/* create a URB, and a buffer क्रम it, and copy the data to the URB */
	urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!urb) अणु
		netdev_err(up->netdev, "no memory left for URBs\n");
		वापस शून्य;
	पूर्ण

	m = usb_alloc_coherent(up->udev,
			       माप(काष्ठा ucan_message_out),
			       GFP_ATOMIC,
			       &urb->transfer_dma);
	अगर (!m) अणु
		netdev_err(up->netdev, "no memory left for USB buffer\n");
		usb_मुक्त_urb(urb);
		वापस शून्य;
	पूर्ण

	/* build the USB message */
	m->type = UCAN_OUT_TX;
	m->msg.can_msg.id = cpu_to_le32(cf->can_id);

	अगर (cf->can_id & CAN_RTR_FLAG) अणु
		mlen = UCAN_OUT_HDR_SIZE +
			दुरत्व(काष्ठा ucan_can_msg, dlc) +
			माप(m->msg.can_msg.dlc);
		m->msg.can_msg.dlc = cf->len;
	पूर्ण अन्यथा अणु
		mlen = UCAN_OUT_HDR_SIZE +
			माप(m->msg.can_msg.id) + cf->len;
		स_नकल(m->msg.can_msg.data, cf->data, cf->len);
	पूर्ण
	m->len = cpu_to_le16(mlen);

	context->dlc = cf->len;

	m->subtype = echo_index;

	/* build the urb */
	usb_fill_bulk_urb(urb, up->udev,
			  usb_sndbulkpipe(up->udev,
					  up->out_ep_addr),
			  m, mlen, ucan_ग_लिखो_bulk_callback, context);
	urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	वापस urb;
पूर्ण

अटल व्योम ucan_clean_up_tx_urb(काष्ठा ucan_priv *up, काष्ठा urb *urb)
अणु
	usb_मुक्त_coherent(up->udev, माप(काष्ठा ucan_message_out),
			  urb->transfer_buffer, urb->transfer_dma);
	usb_मुक्त_urb(urb);
पूर्ण

/* callback when Linux needs to send a can frame */
अटल netdev_tx_t ucan_start_xmit(काष्ठा sk_buff *skb,
				   काष्ठा net_device *netdev)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;
	u8 echo_index;
	काष्ठा urb *urb;
	काष्ठा ucan_urb_context *context;
	काष्ठा ucan_priv *up = netdev_priv(netdev);
	काष्ठा can_frame *cf = (काष्ठा can_frame *)skb->data;

	/* check skb */
	अगर (can_dropped_invalid_skb(netdev, skb))
		वापस NETDEV_TX_OK;

	/* allocate a context and slow करोwn tx path, अगर fअगरo state is low */
	context = ucan_alloc_context(up);
	echo_index = context - up->context_array;

	अगर (WARN_ON_ONCE(!context))
		वापस NETDEV_TX_BUSY;

	/* prepare urb क्रम transmission */
	urb = ucan_prepare_tx_urb(up, context, cf, echo_index);
	अगर (!urb)
		जाओ drop;

	/* put the skb on can loopback stack */
	spin_lock_irqsave(&up->echo_skb_lock, flags);
	can_put_echo_skb(skb, up->netdev, echo_index, 0);
	spin_unlock_irqrestore(&up->echo_skb_lock, flags);

	/* transmit it */
	usb_anchor_urb(urb, &up->tx_urbs);
	ret = usb_submit_urb(urb, GFP_ATOMIC);

	/* cleanup urb */
	अगर (ret) अणु
		/* on error, clean up */
		usb_unanchor_urb(urb);
		ucan_clean_up_tx_urb(up, urb);
		अगर (!ucan_release_context(up, context))
			netdev_err(up->netdev,
				   "xmit err: failed to release context\n");

		/* हटाओ the skb from the echo stack - this also
		 * मुक्तs the skb
		 */
		spin_lock_irqsave(&up->echo_skb_lock, flags);
		can_मुक्त_echo_skb(up->netdev, echo_index, शून्य);
		spin_unlock_irqrestore(&up->echo_skb_lock, flags);

		अगर (ret == -ENODEV) अणु
			netअगर_device_detach(up->netdev);
		पूर्ण अन्यथा अणु
			netdev_warn(up->netdev,
				    "xmit err: failed to submit urb %d\n",
				    ret);
			up->netdev->stats.tx_dropped++;
		पूर्ण
		वापस NETDEV_TX_OK;
	पूर्ण

	netअगर_trans_update(netdev);

	/* release ref, as we करो not need the urb anymore */
	usb_मुक्त_urb(urb);

	वापस NETDEV_TX_OK;

drop:
	अगर (!ucan_release_context(up, context))
		netdev_err(up->netdev,
			   "xmit drop: failed to release context\n");
	dev_kमुक्त_skb(skb);
	up->netdev->stats.tx_dropped++;

	वापस NETDEV_TX_OK;
पूर्ण

/* Device goes करोwn
 *
 * Clean up used resources
 */
अटल पूर्णांक ucan_बंद(काष्ठा net_device *netdev)
अणु
	पूर्णांक ret;
	काष्ठा ucan_priv *up = netdev_priv(netdev);

	up->can.state = CAN_STATE_STOPPED;

	/* stop sending data */
	usb_समाप्त_anchored_urbs(&up->tx_urbs);

	/* stop receiving data */
	usb_समाप्त_anchored_urbs(&up->rx_urbs);

	/* stop and reset can device */
	ret = ucan_ctrl_command_out(up, UCAN_COMMAND_STOP, 0, 0);
	अगर (ret < 0)
		netdev_err(up->netdev,
			   "could not stop device, code: %d\n",
			   ret);

	ret = ucan_ctrl_command_out(up, UCAN_COMMAND_RESET, 0, 0);
	अगर (ret < 0)
		netdev_err(up->netdev,
			   "could not reset device, code: %d\n",
			   ret);

	netअगर_stop_queue(netdev);

	ucan_release_context_array(up);

	बंद_candev(up->netdev);
	वापस 0;
पूर्ण

/* CAN driver callbacks */
अटल स्थिर काष्ठा net_device_ops ucan_netdev_ops = अणु
	.nकरो_खोलो = ucan_खोलो,
	.nकरो_stop = ucan_बंद,
	.nकरो_start_xmit = ucan_start_xmit,
	.nकरो_change_mtu = can_change_mtu,
पूर्ण;

/* Request to set bittiming
 *
 * This function generates an USB set bittiming message and transmits
 * it to the device
 */
अटल पूर्णांक ucan_set_bittiming(काष्ठा net_device *netdev)
अणु
	पूर्णांक ret;
	काष्ठा ucan_priv *up = netdev_priv(netdev);
	काष्ठा ucan_ctl_cmd_set_bittiming *cmd_set_bittiming;

	cmd_set_bittiming = &up->ctl_msg_buffer->cmd_set_bittiming;
	cmd_set_bittiming->tq = cpu_to_le32(up->can.bittiming.tq);
	cmd_set_bittiming->brp = cpu_to_le16(up->can.bittiming.brp);
	cmd_set_bittiming->sample_poपूर्णांक =
	    cpu_to_le16(up->can.bittiming.sample_poपूर्णांक);
	cmd_set_bittiming->prop_seg = up->can.bittiming.prop_seg;
	cmd_set_bittiming->phase_seg1 = up->can.bittiming.phase_seg1;
	cmd_set_bittiming->phase_seg2 = up->can.bittiming.phase_seg2;
	cmd_set_bittiming->sjw = up->can.bittiming.sjw;

	ret = ucan_ctrl_command_out(up, UCAN_COMMAND_SET_BITTIMING, 0,
				    माप(*cmd_set_bittiming));
	वापस (ret < 0) ? ret : 0;
पूर्ण

/* Restart the device to get it out of BUS-OFF state.
 * Called when the user runs "ip link set can1 type can restart".
 */
अटल पूर्णांक ucan_set_mode(काष्ठा net_device *netdev, क्रमागत can_mode mode)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;
	काष्ठा ucan_priv *up = netdev_priv(netdev);

	चयन (mode) अणु
	हाल CAN_MODE_START:
		netdev_dbg(up->netdev, "restarting device\n");

		ret = ucan_ctrl_command_out(up, UCAN_COMMAND_RESTART, 0, 0);
		up->can.state = CAN_STATE_ERROR_ACTIVE;

		/* check अगर queue can be restarted,
		 * up->available_tx_urbs must be रक्षित by the
		 * lock
		 */
		spin_lock_irqsave(&up->context_lock, flags);

		अगर (up->available_tx_urbs > 0)
			netअगर_wake_queue(up->netdev);

		spin_unlock_irqrestore(&up->context_lock, flags);

		वापस ret;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

/* Probe the device, reset it and gather general device inक्रमmation */
अटल पूर्णांक ucan_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		      स्थिर काष्ठा usb_device_id *id)
अणु
	पूर्णांक ret;
	पूर्णांक i;
	u32 protocol_version;
	काष्ठा usb_device *udev;
	काष्ठा net_device *netdev;
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc;
	काष्ठा ucan_priv *up;
	काष्ठा usb_endpoपूर्णांक_descriptor *ep;
	u16 in_ep_size;
	u16 out_ep_size;
	u8 in_ep_addr;
	u8 out_ep_addr;
	जोड़ ucan_ctl_payload *ctl_msg_buffer;
	अक्षर firmware_str[माप(जोड़ ucan_ctl_payload) + 1];

	udev = पूर्णांकerface_to_usbdev(पूर्णांकf);

	/* Stage 1 - Interface Parsing
	 * ---------------------------
	 *
	 * Identअगरie the device USB पूर्णांकerface descriptor and its
	 * endpoपूर्णांकs. Probing is पातed on errors.
	 */

	/* check अगर the पूर्णांकerface is sane */
	अगरace_desc = पूर्णांकf->cur_altsetting;
	अगर (!अगरace_desc)
		वापस -ENODEV;

	dev_info(&udev->dev,
		 "%s: probing device on interface #%d\n",
		 UCAN_DRIVER_NAME,
		 अगरace_desc->desc.bInterfaceNumber);

	/* पूर्णांकerface sanity check */
	अगर (अगरace_desc->desc.bNumEndpoपूर्णांकs != 2) अणु
		dev_err(&udev->dev,
			"%s: invalid EP count (%d)",
			UCAN_DRIVER_NAME, अगरace_desc->desc.bNumEndpoपूर्णांकs);
		जाओ err_firmware_needs_update;
	पूर्ण

	/* check पूर्णांकerface endpoपूर्णांकs */
	in_ep_addr = 0;
	out_ep_addr = 0;
	in_ep_size = 0;
	out_ep_size = 0;
	क्रम (i = 0; i < अगरace_desc->desc.bNumEndpoपूर्णांकs; i++) अणु
		ep = &अगरace_desc->endpoपूर्णांक[i].desc;

		अगर (((ep->bEndpoपूर्णांकAddress & USB_ENDPOINT_सूची_MASK) != 0) &&
		    ((ep->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) ==
		     USB_ENDPOINT_XFER_BULK)) अणु
			/* In Endpoपूर्णांक */
			in_ep_addr = ep->bEndpoपूर्णांकAddress;
			in_ep_addr &= USB_ENDPOINT_NUMBER_MASK;
			in_ep_size = le16_to_cpu(ep->wMaxPacketSize);
		पूर्ण अन्यथा अगर (((ep->bEndpoपूर्णांकAddress & USB_ENDPOINT_सूची_MASK) ==
			    0) &&
			   ((ep->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) ==
			    USB_ENDPOINT_XFER_BULK)) अणु
			/* Out Endpoपूर्णांक */
			out_ep_addr = ep->bEndpoपूर्णांकAddress;
			out_ep_addr &= USB_ENDPOINT_NUMBER_MASK;
			out_ep_size = le16_to_cpu(ep->wMaxPacketSize);
		पूर्ण
	पूर्ण

	/* check अगर पूर्णांकerface is sane */
	अगर (!in_ep_addr || !out_ep_addr) अणु
		dev_err(&udev->dev, "%s: invalid endpoint configuration\n",
			UCAN_DRIVER_NAME);
		जाओ err_firmware_needs_update;
	पूर्ण
	अगर (in_ep_size < माप(काष्ठा ucan_message_in)) अणु
		dev_err(&udev->dev, "%s: invalid in_ep MaxPacketSize\n",
			UCAN_DRIVER_NAME);
		जाओ err_firmware_needs_update;
	पूर्ण
	अगर (out_ep_size < माप(काष्ठा ucan_message_out)) अणु
		dev_err(&udev->dev, "%s: invalid out_ep MaxPacketSize\n",
			UCAN_DRIVER_NAME);
		जाओ err_firmware_needs_update;
	पूर्ण

	/* Stage 2 - Device Identअगरication
	 * -------------------------------
	 *
	 * The device पूर्णांकerface seems to be a ucan device. Do further
	 * compatibility checks. On error probing is पातed, on
	 * success this stage leaves the ctl_msg_buffer with the
	 * reported contents of a GET_INFO command (supported
	 * bittimings, tx_fअगरo depth). This inक्रमmation is used in
	 * Stage 3 क्रम the final driver initialisation.
	 */

	/* Prepare Memory क्रम control transferes */
	ctl_msg_buffer = devm_kzalloc(&udev->dev,
				      माप(जोड़ ucan_ctl_payload),
				      GFP_KERNEL);
	अगर (!ctl_msg_buffer) अणु
		dev_err(&udev->dev,
			"%s: failed to allocate control pipe memory\n",
			UCAN_DRIVER_NAME);
		वापस -ENOMEM;
	पूर्ण

	/* get protocol version
	 *
	 * note: ucan_ctrl_command_* wrappers cannot be used yet
	 * because `up` is initialised in Stage 3
	 */
	ret = usb_control_msg(udev,
			      usb_rcvctrlpipe(udev, 0),
			      UCAN_COMMAND_GET,
			      USB_सूची_IN | USB_TYPE_VENDOR |
					USB_RECIP_INTERFACE,
			      UCAN_COMMAND_GET_PROTOCOL_VERSION,
			      अगरace_desc->desc.bInterfaceNumber,
			      ctl_msg_buffer,
			      माप(जोड़ ucan_ctl_payload),
			      UCAN_USB_CTL_PIPE_TIMEOUT);

	/* older firmware version करो not support this command - those
	 * are not supported by this drive
	 */
	अगर (ret != 4) अणु
		dev_err(&udev->dev,
			"%s: could not read protocol version, ret=%d\n",
			UCAN_DRIVER_NAME, ret);
		अगर (ret >= 0)
			ret = -EINVAL;
		जाओ err_firmware_needs_update;
	पूर्ण

	/* this driver currently supports protocol version 3 only */
	protocol_version =
		le32_to_cpu(ctl_msg_buffer->cmd_get_protocol_version.version);
	अगर (protocol_version < UCAN_PROTOCOL_VERSION_MIN ||
	    protocol_version > UCAN_PROTOCOL_VERSION_MAX) अणु
		dev_err(&udev->dev,
			"%s: device protocol version %d is not supported\n",
			UCAN_DRIVER_NAME, protocol_version);
		जाओ err_firmware_needs_update;
	पूर्ण

	/* request the device inक्रमmation and store it in ctl_msg_buffer
	 *
	 * note: ucan_ctrl_command_* wrappers cannot be used yet
	 * because `up` is initialised in Stage 3
	 */
	ret = usb_control_msg(udev,
			      usb_rcvctrlpipe(udev, 0),
			      UCAN_COMMAND_GET,
			      USB_सूची_IN | USB_TYPE_VENDOR |
					USB_RECIP_INTERFACE,
			      UCAN_COMMAND_GET_INFO,
			      अगरace_desc->desc.bInterfaceNumber,
			      ctl_msg_buffer,
			      माप(ctl_msg_buffer->cmd_get_device_info),
			      UCAN_USB_CTL_PIPE_TIMEOUT);

	अगर (ret < 0) अणु
		dev_err(&udev->dev, "%s: failed to retrieve device info\n",
			UCAN_DRIVER_NAME);
		जाओ err_firmware_needs_update;
	पूर्ण
	अगर (ret < माप(ctl_msg_buffer->cmd_get_device_info)) अणु
		dev_err(&udev->dev, "%s: device reported invalid device info\n",
			UCAN_DRIVER_NAME);
		जाओ err_firmware_needs_update;
	पूर्ण
	अगर (ctl_msg_buffer->cmd_get_device_info.tx_fअगरo == 0) अणु
		dev_err(&udev->dev,
			"%s: device reported invalid tx-fifo size\n",
			UCAN_DRIVER_NAME);
		जाओ err_firmware_needs_update;
	पूर्ण

	/* Stage 3 - Driver Initialisation
	 * -------------------------------
	 *
	 * Register device to Linux, prepare निजी काष्ठाures and
	 * reset the device.
	 */

	/* allocate driver resources */
	netdev = alloc_candev(माप(काष्ठा ucan_priv),
			      ctl_msg_buffer->cmd_get_device_info.tx_fअगरo);
	अगर (!netdev) अणु
		dev_err(&udev->dev,
			"%s: cannot allocate candev\n", UCAN_DRIVER_NAME);
		वापस -ENOMEM;
	पूर्ण

	up = netdev_priv(netdev);

	/* initialize data */
	up->udev = udev;
	up->पूर्णांकf = पूर्णांकf;
	up->netdev = netdev;
	up->पूर्णांकf_index = अगरace_desc->desc.bInterfaceNumber;
	up->in_ep_addr = in_ep_addr;
	up->out_ep_addr = out_ep_addr;
	up->in_ep_size = in_ep_size;
	up->ctl_msg_buffer = ctl_msg_buffer;
	up->context_array = शून्य;
	up->available_tx_urbs = 0;

	up->can.state = CAN_STATE_STOPPED;
	up->can.bittiming_स्थिर = &up->device_info.bittiming_स्थिर;
	up->can.करो_set_bittiming = ucan_set_bittiming;
	up->can.करो_set_mode = &ucan_set_mode;
	spin_lock_init(&up->context_lock);
	spin_lock_init(&up->echo_skb_lock);
	netdev->netdev_ops = &ucan_netdev_ops;

	usb_set_पूर्णांकfdata(पूर्णांकf, up);
	SET_NETDEV_DEV(netdev, &पूर्णांकf->dev);

	/* parse device inक्रमmation
	 * the data retrieved in Stage 2 is still available in
	 * up->ctl_msg_buffer
	 */
	ucan_parse_device_info(up, &ctl_msg_buffer->cmd_get_device_info);

	/* just prपूर्णांक some device inक्रमmation - अगर available */
	ret = ucan_device_request_in(up, UCAN_DEVICE_GET_FW_STRING, 0,
				     माप(जोड़ ucan_ctl_payload));
	अगर (ret > 0) अणु
		/* copy string जबतक ensuring zero terminiation */
		म_नकलन(firmware_str, up->ctl_msg_buffer->raw,
			माप(जोड़ ucan_ctl_payload));
		firmware_str[माप(जोड़ ucan_ctl_payload)] = '\0';
	पूर्ण अन्यथा अणु
		म_नकल(firmware_str, "unknown");
	पूर्ण

	/* device is compatible, reset it */
	ret = ucan_ctrl_command_out(up, UCAN_COMMAND_RESET, 0, 0);
	अगर (ret < 0)
		जाओ err_मुक्त_candev;

	init_usb_anchor(&up->rx_urbs);
	init_usb_anchor(&up->tx_urbs);

	up->can.state = CAN_STATE_STOPPED;

	/* रेजिस्टर the device */
	ret = रेजिस्टर_candev(netdev);
	अगर (ret)
		जाओ err_मुक्त_candev;

	/* initialisation complete, log device info */
	netdev_info(up->netdev, "registered device\n");
	netdev_info(up->netdev, "firmware string: %s\n", firmware_str);

	/* success */
	वापस 0;

err_मुक्त_candev:
	मुक्त_candev(netdev);
	वापस ret;

err_firmware_needs_update:
	dev_err(&udev->dev,
		"%s: probe failed; try to update the device firmware\n",
		UCAN_DRIVER_NAME);
	वापस -ENODEV;
पूर्ण

/* disconnect the device */
अटल व्योम ucan_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा ucan_priv *up = usb_get_पूर्णांकfdata(पूर्णांकf);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	अगर (up) अणु
		unरेजिस्टर_netdev(up->netdev);
		मुक्त_candev(up->netdev);
	पूर्ण
पूर्ण

अटल काष्ठा usb_device_id ucan_table[] = अणु
	/* Mule (soldered onto compute modules) */
	अणुUSB_DEVICE_INTERFACE_NUMBER(0x2294, 0x425a, 0)पूर्ण,
	/* Seal (standalone USB stick) */
	अणुUSB_DEVICE_INTERFACE_NUMBER(0x2294, 0x425b, 0)पूर्ण,
	अणुपूर्ण /* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, ucan_table);
/* driver callbacks */
अटल काष्ठा usb_driver ucan_driver = अणु
	.name = UCAN_DRIVER_NAME,
	.probe = ucan_probe,
	.disconnect = ucan_disconnect,
	.id_table = ucan_table,
पूर्ण;

module_usb_driver(ucan_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Martin Elshuber <martin.elshuber@theobroma-systems.com>");
MODULE_AUTHOR("Jakob Unterwurzacher <jakob.unterwurzacher@theobroma-systems.com>");
MODULE_DESCRIPTION("Driver for Theobroma Systems UCAN devices");
