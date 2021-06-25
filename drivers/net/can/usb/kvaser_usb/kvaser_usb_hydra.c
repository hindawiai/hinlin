<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Parts of this driver are based on the following:
 *  - Kvaser linux mhydra driver (version 5.24)
 *  - CAN driver क्रम esd CAN-USB/2
 *
 * Copyright (C) 2018 KVASER AB, Sweden. All rights reserved.
 * Copyright (C) 2010 Matthias Fuchs <matthias.fuchs@esd.eu>, esd gmbh
 *
 * Known issues:
 *  - Transition from CAN_STATE_ERROR_WARNING to CAN_STATE_ERROR_ACTIVE is only
 *    reported after a call to करो_get_berr_counter(), since firmware करोes not
 *    distinguish between ERROR_WARNING and ERROR_ACTIVE.
 *  - Hardware बारtamps are not set क्रम CAN Tx frames.
 */

#समावेश <linux/completion.h>
#समावेश <linux/device.h>
#समावेश <linux/gfp.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/usb.h>

#समावेश <linux/can.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/can/error.h>
#समावेश <linux/can/netlink.h>

#समावेश "kvaser_usb.h"

/* Forward declarations */
अटल स्थिर काष्ठा kvaser_usb_dev_cfg kvaser_usb_hydra_dev_cfg_kcan;
अटल स्थिर काष्ठा kvaser_usb_dev_cfg kvaser_usb_hydra_dev_cfg_flexc;
अटल स्थिर काष्ठा kvaser_usb_dev_cfg kvaser_usb_hydra_dev_cfg_rt;

#घोषणा KVASER_USB_HYDRA_BULK_EP_IN_ADDR	0x82
#घोषणा KVASER_USB_HYDRA_BULK_EP_OUT_ADDR	0x02

#घोषणा KVASER_USB_HYDRA_MAX_TRANSID		0xff
#घोषणा KVASER_USB_HYDRA_MIN_TRANSID		0x01

/* Minihydra command IDs */
#घोषणा CMD_SET_BUSPARAMS_REQ			16
#घोषणा CMD_GET_CHIP_STATE_REQ			19
#घोषणा CMD_CHIP_STATE_EVENT			20
#घोषणा CMD_SET_DRIVERMODE_REQ			21
#घोषणा CMD_START_CHIP_REQ			26
#घोषणा CMD_START_CHIP_RESP			27
#घोषणा CMD_STOP_CHIP_REQ			28
#घोषणा CMD_STOP_CHIP_RESP			29
#घोषणा CMD_TX_CAN_MESSAGE			33
#घोषणा CMD_GET_CARD_INFO_REQ			34
#घोषणा CMD_GET_CARD_INFO_RESP			35
#घोषणा CMD_GET_SOFTWARE_INFO_REQ		38
#घोषणा CMD_GET_SOFTWARE_INFO_RESP		39
#घोषणा CMD_ERROR_EVENT				45
#घोषणा CMD_FLUSH_QUEUE				48
#घोषणा CMD_TX_ACKNOWLEDGE			50
#घोषणा CMD_FLUSH_QUEUE_RESP			66
#घोषणा CMD_SET_BUSPARAMS_FD_REQ		69
#घोषणा CMD_SET_BUSPARAMS_FD_RESP		70
#घोषणा CMD_SET_BUSPARAMS_RESP			85
#घोषणा CMD_GET_CAPABILITIES_REQ		95
#घोषणा CMD_GET_CAPABILITIES_RESP		96
#घोषणा CMD_RX_MESSAGE				106
#घोषणा CMD_MAP_CHANNEL_REQ			200
#घोषणा CMD_MAP_CHANNEL_RESP			201
#घोषणा CMD_GET_SOFTWARE_DETAILS_REQ		202
#घोषणा CMD_GET_SOFTWARE_DETAILS_RESP		203
#घोषणा CMD_EXTENDED				255

/* Minihydra extended command IDs */
#घोषणा CMD_TX_CAN_MESSAGE_FD			224
#घोषणा CMD_TX_ACKNOWLEDGE_FD			225
#घोषणा CMD_RX_MESSAGE_FD			226

/* Hydra commands are handled by dअगरferent thपढ़ोs in firmware.
 * The thपढ़ोs are denoted hydra entity (HE). Each HE got a unique 6-bit
 * address. The address is used in hydra commands to get/set source and
 * destination HE. There are two predefined HE addresses, the reमुख्यing
 * addresses are dअगरferent between devices and firmware versions. Hence, we need
 * to क्रमागतerate the addresses (see kvaser_usb_hydra_map_channel()).
 */

/* Well-known HE addresses */
#घोषणा KVASER_USB_HYDRA_HE_ADDRESS_ROUTER	0x00
#घोषणा KVASER_USB_HYDRA_HE_ADDRESS_ILLEGAL	0x3e

#घोषणा KVASER_USB_HYDRA_TRANSID_CANHE		0x40
#घोषणा KVASER_USB_HYDRA_TRANSID_SYSDBG		0x61

काष्ठा kvaser_cmd_map_ch_req अणु
	अक्षर name[16];
	u8 channel;
	u8 reserved[11];
पूर्ण __packed;

काष्ठा kvaser_cmd_map_ch_res अणु
	u8 he_addr;
	u8 channel;
	u8 reserved[26];
पूर्ण __packed;

काष्ठा kvaser_cmd_card_info अणु
	__le32 serial_number;
	__le32 घड़ी_res;
	__le32 mfg_date;
	__le32 ean[2];
	u8 hw_version;
	u8 usb_mode;
	u8 hw_type;
	u8 reserved0;
	u8 nchannels;
	u8 reserved1[3];
पूर्ण __packed;

काष्ठा kvaser_cmd_sw_info अणु
	u8 reserved0[8];
	__le16 max_outstanding_tx;
	u8 reserved1[18];
पूर्ण __packed;

काष्ठा kvaser_cmd_sw_detail_req अणु
	u8 use_ext_cmd;
	u8 reserved[27];
पूर्ण __packed;

/* Software detail flags */
#घोषणा KVASER_USB_HYDRA_SW_FLAG_FW_BETA	BIT(2)
#घोषणा KVASER_USB_HYDRA_SW_FLAG_FW_BAD		BIT(4)
#घोषणा KVASER_USB_HYDRA_SW_FLAG_FREQ_80M	BIT(5)
#घोषणा KVASER_USB_HYDRA_SW_FLAG_EXT_CMD	BIT(9)
#घोषणा KVASER_USB_HYDRA_SW_FLAG_CANFD		BIT(10)
#घोषणा KVASER_USB_HYDRA_SW_FLAG_NONISO		BIT(11)
#घोषणा KVASER_USB_HYDRA_SW_FLAG_EXT_CAP	BIT(12)
#घोषणा KVASER_USB_HYDRA_SW_FLAG_CAN_FREQ_80M	BIT(13)
काष्ठा kvaser_cmd_sw_detail_res अणु
	__le32 sw_flags;
	__le32 sw_version;
	__le32 sw_name;
	__le32 ean[2];
	__le32 max_bitrate;
	u8 reserved[4];
पूर्ण __packed;

/* Sub commands क्रम cap_req and cap_res */
#घोषणा KVASER_USB_HYDRA_CAP_CMD_LISTEN_MODE	0x02
#घोषणा KVASER_USB_HYDRA_CAP_CMD_ERR_REPORT	0x05
#घोषणा KVASER_USB_HYDRA_CAP_CMD_ONE_SHOT	0x06
काष्ठा kvaser_cmd_cap_req अणु
	__le16 cap_cmd;
	u8 reserved[26];
पूर्ण __packed;

/* Status codes क्रम cap_res */
#घोषणा KVASER_USB_HYDRA_CAP_STAT_OK		0x00
#घोषणा KVASER_USB_HYDRA_CAP_STAT_NOT_IMPL	0x01
#घोषणा KVASER_USB_HYDRA_CAP_STAT_UNAVAIL	0x02
काष्ठा kvaser_cmd_cap_res अणु
	__le16 cap_cmd;
	__le16 status;
	__le32 mask;
	__le32 value;
	u8 reserved[16];
पूर्ण __packed;

/* CMD_ERROR_EVENT error codes */
#घोषणा KVASER_USB_HYDRA_ERROR_EVENT_CAN	0x01
#घोषणा KVASER_USB_HYDRA_ERROR_EVENT_PARAM	0x09
काष्ठा kvaser_cmd_error_event अणु
	__le16 बारtamp[3];
	u8 reserved;
	u8 error_code;
	__le16 info1;
	__le16 info2;
पूर्ण __packed;

/* Chip state status flags. Used क्रम chip_state_event and err_frame_data. */
#घोषणा KVASER_USB_HYDRA_BUS_ERR_ACT		0x00
#घोषणा KVASER_USB_HYDRA_BUS_ERR_PASS		BIT(5)
#घोषणा KVASER_USB_HYDRA_BUS_BUS_OFF		BIT(6)
काष्ठा kvaser_cmd_chip_state_event अणु
	__le16 बारtamp[3];
	u8 tx_err_counter;
	u8 rx_err_counter;
	u8 bus_status;
	u8 reserved[19];
पूर्ण __packed;

/* Busparam modes */
#घोषणा KVASER_USB_HYDRA_BUS_MODE_CAN		0x00
#घोषणा KVASER_USB_HYDRA_BUS_MODE_CANFD_ISO	0x01
#घोषणा KVASER_USB_HYDRA_BUS_MODE_NONISO	0x02
काष्ठा kvaser_cmd_set_busparams अणु
	__le32 bitrate;
	u8 tseg1;
	u8 tseg2;
	u8 sjw;
	u8 nsamples;
	u8 reserved0[4];
	__le32 bitrate_d;
	u8 tseg1_d;
	u8 tseg2_d;
	u8 sjw_d;
	u8 nsamples_d;
	u8 canfd_mode;
	u8 reserved1[7];
पूर्ण __packed;

/* Ctrl modes */
#घोषणा KVASER_USB_HYDRA_CTRLMODE_NORMAL	0x01
#घोषणा KVASER_USB_HYDRA_CTRLMODE_LISTEN	0x02
काष्ठा kvaser_cmd_set_ctrlmode अणु
	u8 mode;
	u8 reserved[27];
पूर्ण __packed;

काष्ठा kvaser_err_frame_data अणु
	u8 bus_status;
	u8 reserved0;
	u8 tx_err_counter;
	u8 rx_err_counter;
	u8 reserved1[4];
पूर्ण __packed;

काष्ठा kvaser_cmd_rx_can अणु
	u8 cmd_len;
	u8 cmd_no;
	u8 channel;
	u8 flags;
	__le16 बारtamp[3];
	u8 dlc;
	u8 padding;
	__le32 id;
	जोड़ अणु
		u8 data[8];
		काष्ठा kvaser_err_frame_data err_frame_data;
	पूर्ण;
पूर्ण __packed;

/* Extended CAN ID flag. Used in rx_can and tx_can */
#घोषणा KVASER_USB_HYDRA_EXTENDED_FRAME_ID	BIT(31)
काष्ठा kvaser_cmd_tx_can अणु
	__le32 id;
	u8 data[8];
	u8 dlc;
	u8 flags;
	__le16 transid;
	u8 channel;
	u8 reserved[11];
पूर्ण __packed;

काष्ठा kvaser_cmd_header अणु
	u8 cmd_no;
	/* The destination HE address is stored in 0..5 of he_addr.
	 * The upper part of source HE address is stored in 6..7 of he_addr, and
	 * the lower part is stored in 12..15 of transid.
	 */
	u8 he_addr;
	__le16 transid;
पूर्ण __packed;

काष्ठा kvaser_cmd अणु
	काष्ठा kvaser_cmd_header header;
	जोड़ अणु
		काष्ठा kvaser_cmd_map_ch_req map_ch_req;
		काष्ठा kvaser_cmd_map_ch_res map_ch_res;

		काष्ठा kvaser_cmd_card_info card_info;
		काष्ठा kvaser_cmd_sw_info sw_info;
		काष्ठा kvaser_cmd_sw_detail_req sw_detail_req;
		काष्ठा kvaser_cmd_sw_detail_res sw_detail_res;

		काष्ठा kvaser_cmd_cap_req cap_req;
		काष्ठा kvaser_cmd_cap_res cap_res;

		काष्ठा kvaser_cmd_error_event error_event;

		काष्ठा kvaser_cmd_set_busparams set_busparams_req;

		काष्ठा kvaser_cmd_chip_state_event chip_state_event;

		काष्ठा kvaser_cmd_set_ctrlmode set_ctrlmode;

		काष्ठा kvaser_cmd_rx_can rx_can;
		काष्ठा kvaser_cmd_tx_can tx_can;
	पूर्ण __packed;
पूर्ण __packed;

/* CAN frame flags. Used in rx_can, ext_rx_can, tx_can and ext_tx_can */
#घोषणा KVASER_USB_HYDRA_CF_FLAG_ERROR_FRAME	BIT(0)
#घोषणा KVASER_USB_HYDRA_CF_FLAG_OVERRUN	BIT(1)
#घोषणा KVASER_USB_HYDRA_CF_FLAG_REMOTE_FRAME	BIT(4)
#घोषणा KVASER_USB_HYDRA_CF_FLAG_EXTENDED_ID	BIT(5)
/* CAN frame flags. Used in ext_rx_can and ext_tx_can */
#घोषणा KVASER_USB_HYDRA_CF_FLAG_OSM_NACK	BIT(12)
#घोषणा KVASER_USB_HYDRA_CF_FLAG_ABL		BIT(13)
#घोषणा KVASER_USB_HYDRA_CF_FLAG_FDF		BIT(16)
#घोषणा KVASER_USB_HYDRA_CF_FLAG_BRS		BIT(17)
#घोषणा KVASER_USB_HYDRA_CF_FLAG_ESI		BIT(18)

/* KCAN packet header macros. Used in ext_rx_can and ext_tx_can */
#घोषणा KVASER_USB_KCAN_DATA_DLC_BITS		4
#घोषणा KVASER_USB_KCAN_DATA_DLC_SHIFT		8
#घोषणा KVASER_USB_KCAN_DATA_DLC_MASK \
				GENMASK(KVASER_USB_KCAN_DATA_DLC_BITS - 1 + \
				KVASER_USB_KCAN_DATA_DLC_SHIFT, \
				KVASER_USB_KCAN_DATA_DLC_SHIFT)

#घोषणा KVASER_USB_KCAN_DATA_BRS		BIT(14)
#घोषणा KVASER_USB_KCAN_DATA_FDF		BIT(15)
#घोषणा KVASER_USB_KCAN_DATA_OSM		BIT(16)
#घोषणा KVASER_USB_KCAN_DATA_AREQ		BIT(31)
#घोषणा KVASER_USB_KCAN_DATA_SRR		BIT(31)
#घोषणा KVASER_USB_KCAN_DATA_RTR		BIT(29)
#घोषणा KVASER_USB_KCAN_DATA_IDE		BIT(30)
काष्ठा kvaser_cmd_ext_rx_can अणु
	__le32 flags;
	__le32 id;
	__le32 kcan_id;
	__le32 kcan_header;
	__le64 बारtamp;
	जोड़ अणु
		u8 kcan_payload[64];
		काष्ठा kvaser_err_frame_data err_frame_data;
	पूर्ण;
पूर्ण __packed;

काष्ठा kvaser_cmd_ext_tx_can अणु
	__le32 flags;
	__le32 id;
	__le32 kcan_id;
	__le32 kcan_header;
	u8 databytes;
	u8 dlc;
	u8 reserved[6];
	u8 kcan_payload[64];
पूर्ण __packed;

काष्ठा kvaser_cmd_ext_tx_ack अणु
	__le32 flags;
	u8 reserved0[4];
	__le64 बारtamp;
	u8 reserved1[8];
पूर्ण __packed;

/* काष्ठा क्रम extended commands (CMD_EXTENDED) */
काष्ठा kvaser_cmd_ext अणु
	काष्ठा kvaser_cmd_header header;
	__le16 len;
	u8 cmd_no_ext;
	u8 reserved;

	जोड़ अणु
		काष्ठा kvaser_cmd_ext_rx_can rx_can;
		काष्ठा kvaser_cmd_ext_tx_can tx_can;
		काष्ठा kvaser_cmd_ext_tx_ack tx_ack;
	पूर्ण __packed;
पूर्ण __packed;

अटल स्थिर काष्ठा can_bittiming_स्थिर kvaser_usb_hydra_kcan_bittiming_c = अणु
	.name = "kvaser_usb_kcan",
	.tseg1_min = 1,
	.tseg1_max = 255,
	.tseg2_min = 1,
	.tseg2_max = 32,
	.sjw_max = 16,
	.brp_min = 1,
	.brp_max = 8192,
	.brp_inc = 1,
पूर्ण;

अटल स्थिर काष्ठा can_bittiming_स्थिर kvaser_usb_hydra_flexc_bittiming_c = अणु
	.name = "kvaser_usb_flex",
	.tseg1_min = 4,
	.tseg1_max = 16,
	.tseg2_min = 2,
	.tseg2_max = 8,
	.sjw_max = 4,
	.brp_min = 1,
	.brp_max = 256,
	.brp_inc = 1,
पूर्ण;

अटल स्थिर काष्ठा can_bittiming_स्थिर kvaser_usb_hydra_rt_bittiming_c = अणु
	.name = "kvaser_usb_rt",
	.tseg1_min = 2,
	.tseg1_max = 96,
	.tseg2_min = 2,
	.tseg2_max = 32,
	.sjw_max = 32,
	.brp_min = 1,
	.brp_max = 1024,
	.brp_inc = 1,
पूर्ण;

अटल स्थिर काष्ठा can_bittiming_स्थिर kvaser_usb_hydra_rtd_bittiming_c = अणु
	.name = "kvaser_usb_rt",
	.tseg1_min = 2,
	.tseg1_max = 39,
	.tseg2_min = 2,
	.tseg2_max = 8,
	.sjw_max = 8,
	.brp_min = 1,
	.brp_max = 1024,
	.brp_inc = 1,
पूर्ण;

#घोषणा KVASER_USB_HYDRA_TRANSID_BITS		12
#घोषणा KVASER_USB_HYDRA_TRANSID_MASK \
				GENMASK(KVASER_USB_HYDRA_TRANSID_BITS - 1, 0)
#घोषणा KVASER_USB_HYDRA_HE_ADDR_SRC_MASK	GENMASK(7, 6)
#घोषणा KVASER_USB_HYDRA_HE_ADDR_DEST_MASK	GENMASK(5, 0)
#घोषणा KVASER_USB_HYDRA_HE_ADDR_SRC_BITS	2
अटल अंतरभूत u16 kvaser_usb_hydra_get_cmd_transid(स्थिर काष्ठा kvaser_cmd *cmd)
अणु
	वापस le16_to_cpu(cmd->header.transid) & KVASER_USB_HYDRA_TRANSID_MASK;
पूर्ण

अटल अंतरभूत व्योम kvaser_usb_hydra_set_cmd_transid(काष्ठा kvaser_cmd *cmd,
						    u16 transid)
अणु
	cmd->header.transid =
			cpu_to_le16(transid & KVASER_USB_HYDRA_TRANSID_MASK);
पूर्ण

अटल अंतरभूत u8 kvaser_usb_hydra_get_cmd_src_he(स्थिर काष्ठा kvaser_cmd *cmd)
अणु
	वापस (cmd->header.he_addr & KVASER_USB_HYDRA_HE_ADDR_SRC_MASK) >>
		KVASER_USB_HYDRA_HE_ADDR_SRC_BITS |
		le16_to_cpu(cmd->header.transid) >>
		KVASER_USB_HYDRA_TRANSID_BITS;
पूर्ण

अटल अंतरभूत व्योम kvaser_usb_hydra_set_cmd_dest_he(काष्ठा kvaser_cmd *cmd,
						    u8 dest_he)
अणु
	cmd->header.he_addr =
		(cmd->header.he_addr & KVASER_USB_HYDRA_HE_ADDR_SRC_MASK) |
		(dest_he & KVASER_USB_HYDRA_HE_ADDR_DEST_MASK);
पूर्ण

अटल u8 kvaser_usb_hydra_channel_from_cmd(स्थिर काष्ठा kvaser_usb *dev,
					    स्थिर काष्ठा kvaser_cmd *cmd)
अणु
	पूर्णांक i;
	u8 channel = 0xff;
	u8 src_he = kvaser_usb_hydra_get_cmd_src_he(cmd);

	क्रम (i = 0; i < KVASER_USB_MAX_NET_DEVICES; i++) अणु
		अगर (dev->card_data.hydra.channel_to_he[i] == src_he) अणु
			channel = i;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस channel;
पूर्ण

अटल u16 kvaser_usb_hydra_get_next_transid(काष्ठा kvaser_usb *dev)
अणु
	अचिन्हित दीर्घ flags;
	u16 transid;
	काष्ठा kvaser_usb_dev_card_data_hydra *card_data =
							&dev->card_data.hydra;

	spin_lock_irqsave(&card_data->transid_lock, flags);
	transid = card_data->transid;
	अगर (transid >= KVASER_USB_HYDRA_MAX_TRANSID)
		transid = KVASER_USB_HYDRA_MIN_TRANSID;
	अन्यथा
		transid++;
	card_data->transid = transid;
	spin_unlock_irqrestore(&card_data->transid_lock, flags);

	वापस transid;
पूर्ण

अटल माप_प्रकार kvaser_usb_hydra_cmd_size(काष्ठा kvaser_cmd *cmd)
अणु
	माप_प्रकार ret;

	अगर (cmd->header.cmd_no == CMD_EXTENDED)
		ret = le16_to_cpu(((काष्ठा kvaser_cmd_ext *)cmd)->len);
	अन्यथा
		ret = माप(काष्ठा kvaser_cmd);

	वापस ret;
पूर्ण

अटल काष्ठा kvaser_usb_net_priv *
kvaser_usb_hydra_net_priv_from_cmd(स्थिर काष्ठा kvaser_usb *dev,
				   स्थिर काष्ठा kvaser_cmd *cmd)
अणु
	काष्ठा kvaser_usb_net_priv *priv = शून्य;
	u8 channel = kvaser_usb_hydra_channel_from_cmd(dev, cmd);

	अगर (channel >= dev->nchannels)
		dev_err(&dev->पूर्णांकf->dev,
			"Invalid channel number (%d)\n", channel);
	अन्यथा
		priv = dev->nets[channel];

	वापस priv;
पूर्ण

अटल kसमय_प्रकार
kvaser_usb_hydra_kसमय_from_rx_cmd(स्थिर काष्ठा kvaser_usb_dev_cfg *cfg,
				   स्थिर काष्ठा kvaser_cmd *cmd)
अणु
	u64 ticks;

	अगर (cmd->header.cmd_no == CMD_EXTENDED) अणु
		काष्ठा kvaser_cmd_ext *cmd_ext = (काष्ठा kvaser_cmd_ext *)cmd;

		ticks = le64_to_cpu(cmd_ext->rx_can.बारtamp);
	पूर्ण अन्यथा अणु
		ticks = le16_to_cpu(cmd->rx_can.बारtamp[0]);
		ticks += (u64)(le16_to_cpu(cmd->rx_can.बारtamp[1])) << 16;
		ticks += (u64)(le16_to_cpu(cmd->rx_can.बारtamp[2])) << 32;
	पूर्ण

	वापस ns_to_kसमय(भाग_u64(ticks * 1000, cfg->बारtamp_freq));
पूर्ण

अटल पूर्णांक kvaser_usb_hydra_send_simple_cmd(काष्ठा kvaser_usb *dev,
					    u8 cmd_no, पूर्णांक channel)
अणु
	काष्ठा kvaser_cmd *cmd;
	पूर्णांक err;

	cmd = kसुस्मृति(1, माप(काष्ठा kvaser_cmd), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->header.cmd_no = cmd_no;
	अगर (channel < 0) अणु
		kvaser_usb_hydra_set_cmd_dest_he
				(cmd, KVASER_USB_HYDRA_HE_ADDRESS_ILLEGAL);
	पूर्ण अन्यथा अणु
		अगर (channel >= KVASER_USB_MAX_NET_DEVICES) अणु
			dev_err(&dev->पूर्णांकf->dev, "channel (%d) out of range.\n",
				channel);
			err = -EINVAL;
			जाओ end;
		पूर्ण
		kvaser_usb_hydra_set_cmd_dest_he
			(cmd, dev->card_data.hydra.channel_to_he[channel]);
	पूर्ण
	kvaser_usb_hydra_set_cmd_transid
				(cmd, kvaser_usb_hydra_get_next_transid(dev));

	err = kvaser_usb_send_cmd(dev, cmd, kvaser_usb_hydra_cmd_size(cmd));
	अगर (err)
		जाओ end;

end:
	kमुक्त(cmd);

	वापस err;
पूर्ण

अटल पूर्णांक
kvaser_usb_hydra_send_simple_cmd_async(काष्ठा kvaser_usb_net_priv *priv,
				       u8 cmd_no)
अणु
	काष्ठा kvaser_cmd *cmd;
	काष्ठा kvaser_usb *dev = priv->dev;
	पूर्णांक err;

	cmd = kसुस्मृति(1, माप(काष्ठा kvaser_cmd), GFP_ATOMIC);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->header.cmd_no = cmd_no;

	kvaser_usb_hydra_set_cmd_dest_he
		(cmd, dev->card_data.hydra.channel_to_he[priv->channel]);
	kvaser_usb_hydra_set_cmd_transid
				(cmd, kvaser_usb_hydra_get_next_transid(dev));

	err = kvaser_usb_send_cmd_async(priv, cmd,
					kvaser_usb_hydra_cmd_size(cmd));
	अगर (err)
		kमुक्त(cmd);

	वापस err;
पूर्ण

/* This function is used क्रम synchronously रुकोing on hydra control commands.
 * Note: Compared to kvaser_usb_hydra_पढ़ो_bulk_callback(), we never need to
 *       handle partial hydra commands. Since hydra control commands are always
 *       non-extended commands.
 */
अटल पूर्णांक kvaser_usb_hydra_रुको_cmd(स्थिर काष्ठा kvaser_usb *dev, u8 cmd_no,
				     काष्ठा kvaser_cmd *cmd)
अणु
	व्योम *buf;
	पूर्णांक err;
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(KVASER_USB_TIMEOUT);

	अगर (cmd->header.cmd_no == CMD_EXTENDED) अणु
		dev_err(&dev->पूर्णांकf->dev, "Wait for CMD_EXTENDED not allowed\n");
		वापस -EINVAL;
	पूर्ण

	buf = kzalloc(KVASER_USB_RX_BUFFER_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	करो अणु
		पूर्णांक actual_len = 0;
		पूर्णांक pos = 0;

		err = kvaser_usb_recv_cmd(dev, buf, KVASER_USB_RX_BUFFER_SIZE,
					  &actual_len);
		अगर (err < 0)
			जाओ end;

		जबतक (pos < actual_len) अणु
			काष्ठा kvaser_cmd *पंचांगp_cmd;
			माप_प्रकार cmd_len;

			पंचांगp_cmd = buf + pos;
			cmd_len = kvaser_usb_hydra_cmd_size(पंचांगp_cmd);
			अगर (pos + cmd_len > actual_len) अणु
				dev_err_ratelimited(&dev->पूर्णांकf->dev,
						    "Format error\n");
				अवरोध;
			पूर्ण

			अगर (पंचांगp_cmd->header.cmd_no == cmd_no) अणु
				स_नकल(cmd, पंचांगp_cmd, cmd_len);
				जाओ end;
			पूर्ण
			pos += cmd_len;
		पूर्ण
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	err = -EINVAL;

end:
	kमुक्त(buf);

	वापस err;
पूर्ण

अटल पूर्णांक kvaser_usb_hydra_map_channel_resp(काष्ठा kvaser_usb *dev,
					     स्थिर काष्ठा kvaser_cmd *cmd)
अणु
	u8 he, channel;
	u16 transid = kvaser_usb_hydra_get_cmd_transid(cmd);
	काष्ठा kvaser_usb_dev_card_data_hydra *card_data =
							&dev->card_data.hydra;

	अगर (transid > 0x007f || transid < 0x0040) अणु
		dev_err(&dev->पूर्णांकf->dev,
			"CMD_MAP_CHANNEL_RESP, invalid transid: 0x%x\n",
			transid);
		वापस -EINVAL;
	पूर्ण

	चयन (transid) अणु
	हाल KVASER_USB_HYDRA_TRANSID_CANHE:
	हाल KVASER_USB_HYDRA_TRANSID_CANHE + 1:
	हाल KVASER_USB_HYDRA_TRANSID_CANHE + 2:
	हाल KVASER_USB_HYDRA_TRANSID_CANHE + 3:
	हाल KVASER_USB_HYDRA_TRANSID_CANHE + 4:
		channel = transid & 0x000f;
		he = cmd->map_ch_res.he_addr;
		card_data->channel_to_he[channel] = he;
		अवरोध;
	हाल KVASER_USB_HYDRA_TRANSID_SYSDBG:
		card_data->sysdbg_he = cmd->map_ch_res.he_addr;
		अवरोध;
	शेष:
		dev_warn(&dev->पूर्णांकf->dev,
			 "Unknown CMD_MAP_CHANNEL_RESP transid=0x%x\n",
			 transid);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kvaser_usb_hydra_map_channel(काष्ठा kvaser_usb *dev, u16 transid,
					u8 channel, स्थिर अक्षर *name)
अणु
	काष्ठा kvaser_cmd *cmd;
	पूर्णांक err;

	cmd = kसुस्मृति(1, माप(काष्ठा kvaser_cmd), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	म_नकल(cmd->map_ch_req.name, name);
	cmd->header.cmd_no = CMD_MAP_CHANNEL_REQ;
	kvaser_usb_hydra_set_cmd_dest_he
				(cmd, KVASER_USB_HYDRA_HE_ADDRESS_ROUTER);
	cmd->map_ch_req.channel = channel;

	kvaser_usb_hydra_set_cmd_transid(cmd, transid);

	err = kvaser_usb_send_cmd(dev, cmd, kvaser_usb_hydra_cmd_size(cmd));
	अगर (err)
		जाओ end;

	err = kvaser_usb_hydra_रुको_cmd(dev, CMD_MAP_CHANNEL_RESP, cmd);
	अगर (err)
		जाओ end;

	err = kvaser_usb_hydra_map_channel_resp(dev, cmd);
	अगर (err)
		जाओ end;

end:
	kमुक्त(cmd);

	वापस err;
पूर्ण

अटल पूर्णांक kvaser_usb_hydra_get_single_capability(काष्ठा kvaser_usb *dev,
						  u16 cap_cmd_req, u16 *status)
अणु
	काष्ठा kvaser_usb_dev_card_data *card_data = &dev->card_data;
	काष्ठा kvaser_cmd *cmd;
	u32 value = 0;
	u32 mask = 0;
	u16 cap_cmd_res;
	पूर्णांक err;
	पूर्णांक i;

	cmd = kसुस्मृति(1, माप(काष्ठा kvaser_cmd), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->header.cmd_no = CMD_GET_CAPABILITIES_REQ;
	cmd->cap_req.cap_cmd = cpu_to_le16(cap_cmd_req);

	kvaser_usb_hydra_set_cmd_dest_he(cmd, card_data->hydra.sysdbg_he);
	kvaser_usb_hydra_set_cmd_transid
				(cmd, kvaser_usb_hydra_get_next_transid(dev));

	err = kvaser_usb_send_cmd(dev, cmd, kvaser_usb_hydra_cmd_size(cmd));
	अगर (err)
		जाओ end;

	err = kvaser_usb_hydra_रुको_cmd(dev, CMD_GET_CAPABILITIES_RESP, cmd);
	अगर (err)
		जाओ end;

	*status = le16_to_cpu(cmd->cap_res.status);

	अगर (*status != KVASER_USB_HYDRA_CAP_STAT_OK)
		जाओ end;

	cap_cmd_res = le16_to_cpu(cmd->cap_res.cap_cmd);
	चयन (cap_cmd_res) अणु
	हाल KVASER_USB_HYDRA_CAP_CMD_LISTEN_MODE:
	हाल KVASER_USB_HYDRA_CAP_CMD_ERR_REPORT:
	हाल KVASER_USB_HYDRA_CAP_CMD_ONE_SHOT:
		value = le32_to_cpu(cmd->cap_res.value);
		mask = le32_to_cpu(cmd->cap_res.mask);
		अवरोध;
	शेष:
		dev_warn(&dev->पूर्णांकf->dev, "Unknown capability command %u\n",
			 cap_cmd_res);
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < dev->nchannels; i++) अणु
		अगर (BIT(i) & (value & mask)) अणु
			चयन (cap_cmd_res) अणु
			हाल KVASER_USB_HYDRA_CAP_CMD_LISTEN_MODE:
				card_data->ctrlmode_supported |=
						CAN_CTRLMODE_LISTENONLY;
				अवरोध;
			हाल KVASER_USB_HYDRA_CAP_CMD_ERR_REPORT:
				card_data->capabilities |=
						KVASER_USB_CAP_BERR_CAP;
				अवरोध;
			हाल KVASER_USB_HYDRA_CAP_CMD_ONE_SHOT:
				card_data->ctrlmode_supported |=
						CAN_CTRLMODE_ONE_SHOT;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

end:
	kमुक्त(cmd);

	वापस err;
पूर्ण

अटल व्योम kvaser_usb_hydra_start_chip_reply(स्थिर काष्ठा kvaser_usb *dev,
					      स्थिर काष्ठा kvaser_cmd *cmd)
अणु
	काष्ठा kvaser_usb_net_priv *priv;

	priv = kvaser_usb_hydra_net_priv_from_cmd(dev, cmd);
	अगर (!priv)
		वापस;

	अगर (completion_करोne(&priv->start_comp) &&
	    netअगर_queue_stopped(priv->netdev)) अणु
		netअगर_wake_queue(priv->netdev);
	पूर्ण अन्यथा अणु
		netअगर_start_queue(priv->netdev);
		complete(&priv->start_comp);
	पूर्ण
पूर्ण

अटल व्योम kvaser_usb_hydra_stop_chip_reply(स्थिर काष्ठा kvaser_usb *dev,
					     स्थिर काष्ठा kvaser_cmd *cmd)
अणु
	काष्ठा kvaser_usb_net_priv *priv;

	priv = kvaser_usb_hydra_net_priv_from_cmd(dev, cmd);
	अगर (!priv)
		वापस;

	complete(&priv->stop_comp);
पूर्ण

अटल व्योम kvaser_usb_hydra_flush_queue_reply(स्थिर काष्ठा kvaser_usb *dev,
					       स्थिर काष्ठा kvaser_cmd *cmd)
अणु
	काष्ठा kvaser_usb_net_priv *priv;

	priv = kvaser_usb_hydra_net_priv_from_cmd(dev, cmd);
	अगर (!priv)
		वापस;

	complete(&priv->flush_comp);
पूर्ण

अटल व्योम
kvaser_usb_hydra_bus_status_to_can_state(स्थिर काष्ठा kvaser_usb_net_priv *priv,
					 u8 bus_status,
					 स्थिर काष्ठा can_berr_counter *bec,
					 क्रमागत can_state *new_state)
अणु
	अगर (bus_status & KVASER_USB_HYDRA_BUS_BUS_OFF) अणु
		*new_state = CAN_STATE_BUS_OFF;
	पूर्ण अन्यथा अगर (bus_status & KVASER_USB_HYDRA_BUS_ERR_PASS) अणु
		*new_state = CAN_STATE_ERROR_PASSIVE;
	पूर्ण अन्यथा अगर (bus_status == KVASER_USB_HYDRA_BUS_ERR_ACT) अणु
		अगर (bec->txerr >= 128 || bec->rxerr >= 128) अणु
			netdev_warn(priv->netdev,
				    "ERR_ACTIVE but err tx=%u or rx=%u >=128\n",
				    bec->txerr, bec->rxerr);
			*new_state = CAN_STATE_ERROR_PASSIVE;
		पूर्ण अन्यथा अगर (bec->txerr >= 96 || bec->rxerr >= 96) अणु
			*new_state = CAN_STATE_ERROR_WARNING;
		पूर्ण अन्यथा अणु
			*new_state = CAN_STATE_ERROR_ACTIVE;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम kvaser_usb_hydra_update_state(काष्ठा kvaser_usb_net_priv *priv,
					  u8 bus_status,
					  स्थिर काष्ठा can_berr_counter *bec)
अणु
	काष्ठा net_device *netdev = priv->netdev;
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;
	काष्ठा net_device_stats *stats;
	क्रमागत can_state new_state, old_state;

	old_state = priv->can.state;

	kvaser_usb_hydra_bus_status_to_can_state(priv, bus_status, bec,
						 &new_state);

	अगर (new_state == old_state)
		वापस;

	/* Ignore state change अगर previous state was STOPPED and the new state
	 * is BUS_OFF. Firmware always report this as BUS_OFF, since firmware
	 * करोes not distinguish between BUS_OFF and STOPPED.
	 */
	अगर (old_state == CAN_STATE_STOPPED && new_state == CAN_STATE_BUS_OFF)
		वापस;

	skb = alloc_can_err_skb(netdev, &cf);
	अगर (skb) अणु
		क्रमागत can_state tx_state, rx_state;

		tx_state = (bec->txerr >= bec->rxerr) ?
					new_state : CAN_STATE_ERROR_ACTIVE;
		rx_state = (bec->txerr <= bec->rxerr) ?
					new_state : CAN_STATE_ERROR_ACTIVE;
		can_change_state(netdev, cf, tx_state, rx_state);
	पूर्ण

	अगर (new_state == CAN_STATE_BUS_OFF && old_state < CAN_STATE_BUS_OFF) अणु
		अगर (!priv->can.restart_ms)
			kvaser_usb_hydra_send_simple_cmd_async
						(priv, CMD_STOP_CHIP_REQ);

		can_bus_off(netdev);
	पूर्ण

	अगर (!skb) अणु
		netdev_warn(netdev, "No memory left for err_skb\n");
		वापस;
	पूर्ण

	अगर (priv->can.restart_ms &&
	    old_state >= CAN_STATE_BUS_OFF &&
	    new_state < CAN_STATE_BUS_OFF)
		priv->can.can_stats.restarts++;

	cf->data[6] = bec->txerr;
	cf->data[7] = bec->rxerr;

	stats = &netdev->stats;
	stats->rx_packets++;
	stats->rx_bytes += cf->len;
	netअगर_rx(skb);
पूर्ण

अटल व्योम kvaser_usb_hydra_state_event(स्थिर काष्ठा kvaser_usb *dev,
					 स्थिर काष्ठा kvaser_cmd *cmd)
अणु
	काष्ठा kvaser_usb_net_priv *priv;
	काष्ठा can_berr_counter bec;
	u8 bus_status;

	priv = kvaser_usb_hydra_net_priv_from_cmd(dev, cmd);
	अगर (!priv)
		वापस;

	bus_status = cmd->chip_state_event.bus_status;
	bec.txerr = cmd->chip_state_event.tx_err_counter;
	bec.rxerr = cmd->chip_state_event.rx_err_counter;

	kvaser_usb_hydra_update_state(priv, bus_status, &bec);
	priv->bec.txerr = bec.txerr;
	priv->bec.rxerr = bec.rxerr;
पूर्ण

अटल व्योम kvaser_usb_hydra_error_event_parameter(स्थिर काष्ठा kvaser_usb *dev,
						   स्थिर काष्ठा kvaser_cmd *cmd)
अणु
	/* info1 will contain the offending cmd_no */
	चयन (le16_to_cpu(cmd->error_event.info1)) अणु
	हाल CMD_START_CHIP_REQ:
		dev_warn(&dev->पूर्णांकf->dev,
			 "CMD_START_CHIP_REQ error in parameter\n");
		अवरोध;

	हाल CMD_STOP_CHIP_REQ:
		dev_warn(&dev->पूर्णांकf->dev,
			 "CMD_STOP_CHIP_REQ error in parameter\n");
		अवरोध;

	हाल CMD_FLUSH_QUEUE:
		dev_warn(&dev->पूर्णांकf->dev,
			 "CMD_FLUSH_QUEUE error in parameter\n");
		अवरोध;

	हाल CMD_SET_BUSPARAMS_REQ:
		dev_warn(&dev->पूर्णांकf->dev,
			 "Set bittiming failed. Error in parameter\n");
		अवरोध;

	हाल CMD_SET_BUSPARAMS_FD_REQ:
		dev_warn(&dev->पूर्णांकf->dev,
			 "Set data bittiming failed. Error in parameter\n");
		अवरोध;

	शेष:
		dev_warn(&dev->पूर्णांकf->dev,
			 "Unhandled parameter error event cmd_no (%u)\n",
			 le16_to_cpu(cmd->error_event.info1));
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम kvaser_usb_hydra_error_event(स्थिर काष्ठा kvaser_usb *dev,
					 स्थिर काष्ठा kvaser_cmd *cmd)
अणु
	चयन (cmd->error_event.error_code) अणु
	हाल KVASER_USB_HYDRA_ERROR_EVENT_PARAM:
		kvaser_usb_hydra_error_event_parameter(dev, cmd);
		अवरोध;

	हाल KVASER_USB_HYDRA_ERROR_EVENT_CAN:
		/* Wrong channel mapping?! This should never happen!
		 * info1 will contain the offending cmd_no
		 */
		dev_err(&dev->पूर्णांकf->dev,
			"Received CAN error event for cmd_no (%u)\n",
			le16_to_cpu(cmd->error_event.info1));
		अवरोध;

	शेष:
		dev_warn(&dev->पूर्णांकf->dev,
			 "Unhandled error event (%d)\n",
			 cmd->error_event.error_code);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
kvaser_usb_hydra_error_frame(काष्ठा kvaser_usb_net_priv *priv,
			     स्थिर काष्ठा kvaser_err_frame_data *err_frame_data,
			     kसमय_प्रकार hwtstamp)
अणु
	काष्ठा net_device *netdev = priv->netdev;
	काष्ठा net_device_stats *stats = &netdev->stats;
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;
	काष्ठा skb_shared_hwtstamps *shhwtstamps;
	काष्ठा can_berr_counter bec;
	क्रमागत can_state new_state, old_state;
	u8 bus_status;

	priv->can.can_stats.bus_error++;
	stats->rx_errors++;

	bus_status = err_frame_data->bus_status;
	bec.txerr = err_frame_data->tx_err_counter;
	bec.rxerr = err_frame_data->rx_err_counter;

	old_state = priv->can.state;
	kvaser_usb_hydra_bus_status_to_can_state(priv, bus_status, &bec,
						 &new_state);

	skb = alloc_can_err_skb(netdev, &cf);

	अगर (new_state != old_state) अणु
		अगर (skb) अणु
			क्रमागत can_state tx_state, rx_state;

			tx_state = (bec.txerr >= bec.rxerr) ?
					new_state : CAN_STATE_ERROR_ACTIVE;
			rx_state = (bec.txerr <= bec.rxerr) ?
					new_state : CAN_STATE_ERROR_ACTIVE;

			can_change_state(netdev, cf, tx_state, rx_state);

			अगर (priv->can.restart_ms &&
			    old_state >= CAN_STATE_BUS_OFF &&
			    new_state < CAN_STATE_BUS_OFF)
				cf->can_id |= CAN_ERR_RESTARTED;
		पूर्ण

		अगर (new_state == CAN_STATE_BUS_OFF) अणु
			अगर (!priv->can.restart_ms)
				kvaser_usb_hydra_send_simple_cmd_async
						(priv, CMD_STOP_CHIP_REQ);

			can_bus_off(netdev);
		पूर्ण
	पूर्ण

	अगर (!skb) अणु
		stats->rx_dropped++;
		netdev_warn(netdev, "No memory left for err_skb\n");
		वापस;
	पूर्ण

	shhwtstamps = skb_hwtstamps(skb);
	shhwtstamps->hwtstamp = hwtstamp;

	cf->can_id |= CAN_ERR_BUSERROR;
	cf->data[6] = bec.txerr;
	cf->data[7] = bec.rxerr;

	stats->rx_packets++;
	stats->rx_bytes += cf->len;
	netअगर_rx(skb);

	priv->bec.txerr = bec.txerr;
	priv->bec.rxerr = bec.rxerr;
पूर्ण

अटल व्योम kvaser_usb_hydra_one_shot_fail(काष्ठा kvaser_usb_net_priv *priv,
					   स्थिर काष्ठा kvaser_cmd_ext *cmd)
अणु
	काष्ठा net_device *netdev = priv->netdev;
	काष्ठा net_device_stats *stats = &netdev->stats;
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;
	u32 flags;

	skb = alloc_can_err_skb(netdev, &cf);
	अगर (!skb) अणु
		stats->rx_dropped++;
		netdev_warn(netdev, "No memory left for err_skb\n");
		वापस;
	पूर्ण

	cf->can_id |= CAN_ERR_BUSERROR;
	flags = le32_to_cpu(cmd->tx_ack.flags);

	अगर (flags & KVASER_USB_HYDRA_CF_FLAG_OSM_NACK)
		cf->can_id |= CAN_ERR_ACK;
	अगर (flags & KVASER_USB_HYDRA_CF_FLAG_ABL) अणु
		cf->can_id |= CAN_ERR_LOSTARB;
		priv->can.can_stats.arbitration_lost++;
	पूर्ण

	stats->tx_errors++;
	stats->rx_packets++;
	stats->rx_bytes += cf->len;
	netअगर_rx(skb);
पूर्ण

अटल व्योम kvaser_usb_hydra_tx_acknowledge(स्थिर काष्ठा kvaser_usb *dev,
					    स्थिर काष्ठा kvaser_cmd *cmd)
अणु
	काष्ठा kvaser_usb_tx_urb_context *context;
	काष्ठा kvaser_usb_net_priv *priv;
	अचिन्हित दीर्घ irq_flags;
	bool one_shot_fail = false;
	u16 transid = kvaser_usb_hydra_get_cmd_transid(cmd);

	priv = kvaser_usb_hydra_net_priv_from_cmd(dev, cmd);
	अगर (!priv)
		वापस;

	अगर (!netअगर_device_present(priv->netdev))
		वापस;

	अगर (cmd->header.cmd_no == CMD_EXTENDED) अणु
		काष्ठा kvaser_cmd_ext *cmd_ext = (काष्ठा kvaser_cmd_ext *)cmd;
		u32 flags = le32_to_cpu(cmd_ext->tx_ack.flags);

		अगर (flags & (KVASER_USB_HYDRA_CF_FLAG_OSM_NACK |
			     KVASER_USB_HYDRA_CF_FLAG_ABL)) अणु
			kvaser_usb_hydra_one_shot_fail(priv, cmd_ext);
			one_shot_fail = true;
		पूर्ण
	पूर्ण

	context = &priv->tx_contexts[transid % dev->max_tx_urbs];
	अगर (!one_shot_fail) अणु
		काष्ठा net_device_stats *stats = &priv->netdev->stats;

		stats->tx_packets++;
		stats->tx_bytes += can_fd_dlc2len(context->dlc);
	पूर्ण

	spin_lock_irqsave(&priv->tx_contexts_lock, irq_flags);

	can_get_echo_skb(priv->netdev, context->echo_index, शून्य);
	context->echo_index = dev->max_tx_urbs;
	--priv->active_tx_contexts;
	netअगर_wake_queue(priv->netdev);

	spin_unlock_irqrestore(&priv->tx_contexts_lock, irq_flags);
पूर्ण

अटल व्योम kvaser_usb_hydra_rx_msg_std(स्थिर काष्ठा kvaser_usb *dev,
					स्थिर काष्ठा kvaser_cmd *cmd)
अणु
	काष्ठा kvaser_usb_net_priv *priv = शून्य;
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;
	काष्ठा skb_shared_hwtstamps *shhwtstamps;
	काष्ठा net_device_stats *stats;
	u8 flags;
	kसमय_प्रकार hwtstamp;

	priv = kvaser_usb_hydra_net_priv_from_cmd(dev, cmd);
	अगर (!priv)
		वापस;

	stats = &priv->netdev->stats;

	flags = cmd->rx_can.flags;
	hwtstamp = kvaser_usb_hydra_kसमय_from_rx_cmd(dev->cfg, cmd);

	अगर (flags & KVASER_USB_HYDRA_CF_FLAG_ERROR_FRAME) अणु
		kvaser_usb_hydra_error_frame(priv, &cmd->rx_can.err_frame_data,
					     hwtstamp);
		वापस;
	पूर्ण

	skb = alloc_can_skb(priv->netdev, &cf);
	अगर (!skb) अणु
		stats->rx_dropped++;
		वापस;
	पूर्ण

	shhwtstamps = skb_hwtstamps(skb);
	shhwtstamps->hwtstamp = hwtstamp;

	cf->can_id = le32_to_cpu(cmd->rx_can.id);

	अगर (cf->can_id &  KVASER_USB_HYDRA_EXTENDED_FRAME_ID) अणु
		cf->can_id &= CAN_EFF_MASK;
		cf->can_id |= CAN_EFF_FLAG;
	पूर्ण अन्यथा अणु
		cf->can_id &= CAN_SFF_MASK;
	पूर्ण

	अगर (flags & KVASER_USB_HYDRA_CF_FLAG_OVERRUN)
		kvaser_usb_can_rx_over_error(priv->netdev);

	cf->len = can_cc_dlc2len(cmd->rx_can.dlc);

	अगर (flags & KVASER_USB_HYDRA_CF_FLAG_REMOTE_FRAME)
		cf->can_id |= CAN_RTR_FLAG;
	अन्यथा
		स_नकल(cf->data, cmd->rx_can.data, cf->len);

	stats->rx_packets++;
	stats->rx_bytes += cf->len;
	netअगर_rx(skb);
पूर्ण

अटल व्योम kvaser_usb_hydra_rx_msg_ext(स्थिर काष्ठा kvaser_usb *dev,
					स्थिर काष्ठा kvaser_cmd_ext *cmd)
अणु
	काष्ठा kvaser_cmd *std_cmd = (काष्ठा kvaser_cmd *)cmd;
	काष्ठा kvaser_usb_net_priv *priv;
	काष्ठा canfd_frame *cf;
	काष्ठा sk_buff *skb;
	काष्ठा skb_shared_hwtstamps *shhwtstamps;
	काष्ठा net_device_stats *stats;
	u32 flags;
	u8 dlc;
	u32 kcan_header;
	kसमय_प्रकार hwtstamp;

	priv = kvaser_usb_hydra_net_priv_from_cmd(dev, std_cmd);
	अगर (!priv)
		वापस;

	stats = &priv->netdev->stats;

	kcan_header = le32_to_cpu(cmd->rx_can.kcan_header);
	dlc = (kcan_header & KVASER_USB_KCAN_DATA_DLC_MASK) >>
		KVASER_USB_KCAN_DATA_DLC_SHIFT;

	flags = le32_to_cpu(cmd->rx_can.flags);
	hwtstamp = kvaser_usb_hydra_kसमय_from_rx_cmd(dev->cfg, std_cmd);

	अगर (flags & KVASER_USB_HYDRA_CF_FLAG_ERROR_FRAME) अणु
		kvaser_usb_hydra_error_frame(priv, &cmd->rx_can.err_frame_data,
					     hwtstamp);
		वापस;
	पूर्ण

	अगर (flags & KVASER_USB_HYDRA_CF_FLAG_FDF)
		skb = alloc_canfd_skb(priv->netdev, &cf);
	अन्यथा
		skb = alloc_can_skb(priv->netdev, (काष्ठा can_frame **)&cf);

	अगर (!skb) अणु
		stats->rx_dropped++;
		वापस;
	पूर्ण

	shhwtstamps = skb_hwtstamps(skb);
	shhwtstamps->hwtstamp = hwtstamp;

	cf->can_id = le32_to_cpu(cmd->rx_can.id);

	अगर (flags & KVASER_USB_HYDRA_CF_FLAG_EXTENDED_ID) अणु
		cf->can_id &= CAN_EFF_MASK;
		cf->can_id |= CAN_EFF_FLAG;
	पूर्ण अन्यथा अणु
		cf->can_id &= CAN_SFF_MASK;
	पूर्ण

	अगर (flags & KVASER_USB_HYDRA_CF_FLAG_OVERRUN)
		kvaser_usb_can_rx_over_error(priv->netdev);

	अगर (flags & KVASER_USB_HYDRA_CF_FLAG_FDF) अणु
		cf->len = can_fd_dlc2len(dlc);
		अगर (flags & KVASER_USB_HYDRA_CF_FLAG_BRS)
			cf->flags |= CANFD_BRS;
		अगर (flags & KVASER_USB_HYDRA_CF_FLAG_ESI)
			cf->flags |= CANFD_ESI;
	पूर्ण अन्यथा अणु
		cf->len = can_cc_dlc2len(dlc);
	पूर्ण

	अगर (flags & KVASER_USB_HYDRA_CF_FLAG_REMOTE_FRAME)
		cf->can_id |= CAN_RTR_FLAG;
	अन्यथा
		स_नकल(cf->data, cmd->rx_can.kcan_payload, cf->len);

	stats->rx_packets++;
	stats->rx_bytes += cf->len;
	netअगर_rx(skb);
पूर्ण

अटल व्योम kvaser_usb_hydra_handle_cmd_std(स्थिर काष्ठा kvaser_usb *dev,
					    स्थिर काष्ठा kvaser_cmd *cmd)
अणु
	चयन (cmd->header.cmd_no) अणु
	हाल CMD_START_CHIP_RESP:
		kvaser_usb_hydra_start_chip_reply(dev, cmd);
		अवरोध;

	हाल CMD_STOP_CHIP_RESP:
		kvaser_usb_hydra_stop_chip_reply(dev, cmd);
		अवरोध;

	हाल CMD_FLUSH_QUEUE_RESP:
		kvaser_usb_hydra_flush_queue_reply(dev, cmd);
		अवरोध;

	हाल CMD_CHIP_STATE_EVENT:
		kvaser_usb_hydra_state_event(dev, cmd);
		अवरोध;

	हाल CMD_ERROR_EVENT:
		kvaser_usb_hydra_error_event(dev, cmd);
		अवरोध;

	हाल CMD_TX_ACKNOWLEDGE:
		kvaser_usb_hydra_tx_acknowledge(dev, cmd);
		अवरोध;

	हाल CMD_RX_MESSAGE:
		kvaser_usb_hydra_rx_msg_std(dev, cmd);
		अवरोध;

	/* Ignored commands */
	हाल CMD_SET_BUSPARAMS_RESP:
	हाल CMD_SET_BUSPARAMS_FD_RESP:
		अवरोध;

	शेष:
		dev_warn(&dev->पूर्णांकf->dev, "Unhandled command (%d)\n",
			 cmd->header.cmd_no);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम kvaser_usb_hydra_handle_cmd_ext(स्थिर काष्ठा kvaser_usb *dev,
					    स्थिर काष्ठा kvaser_cmd_ext *cmd)
अणु
	चयन (cmd->cmd_no_ext) अणु
	हाल CMD_TX_ACKNOWLEDGE_FD:
		kvaser_usb_hydra_tx_acknowledge(dev, (काष्ठा kvaser_cmd *)cmd);
		अवरोध;

	हाल CMD_RX_MESSAGE_FD:
		kvaser_usb_hydra_rx_msg_ext(dev, cmd);
		अवरोध;

	शेष:
		dev_warn(&dev->पूर्णांकf->dev, "Unhandled extended command (%d)\n",
			 cmd->header.cmd_no);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम kvaser_usb_hydra_handle_cmd(स्थिर काष्ठा kvaser_usb *dev,
					स्थिर काष्ठा kvaser_cmd *cmd)
अणु
		अगर (cmd->header.cmd_no == CMD_EXTENDED)
			kvaser_usb_hydra_handle_cmd_ext
					(dev, (काष्ठा kvaser_cmd_ext *)cmd);
		अन्यथा
			kvaser_usb_hydra_handle_cmd_std(dev, cmd);
पूर्ण

अटल व्योम *
kvaser_usb_hydra_frame_to_cmd_ext(स्थिर काष्ठा kvaser_usb_net_priv *priv,
				  स्थिर काष्ठा sk_buff *skb, पूर्णांक *frame_len,
				  पूर्णांक *cmd_len, u16 transid)
अणु
	काष्ठा kvaser_usb *dev = priv->dev;
	काष्ठा kvaser_cmd_ext *cmd;
	काष्ठा canfd_frame *cf = (काष्ठा canfd_frame *)skb->data;
	u8 dlc = can_fd_len2dlc(cf->len);
	u8 nbr_of_bytes = cf->len;
	u32 flags;
	u32 id;
	u32 kcan_id;
	u32 kcan_header;

	*frame_len = nbr_of_bytes;

	cmd = kसुस्मृति(1, माप(काष्ठा kvaser_cmd_ext), GFP_ATOMIC);
	अगर (!cmd)
		वापस शून्य;

	kvaser_usb_hydra_set_cmd_dest_he
			((काष्ठा kvaser_cmd *)cmd,
			 dev->card_data.hydra.channel_to_he[priv->channel]);
	kvaser_usb_hydra_set_cmd_transid((काष्ठा kvaser_cmd *)cmd, transid);

	cmd->header.cmd_no = CMD_EXTENDED;
	cmd->cmd_no_ext = CMD_TX_CAN_MESSAGE_FD;

	*cmd_len = ALIGN(माप(काष्ठा kvaser_cmd_ext) -
			 माप(cmd->tx_can.kcan_payload) + nbr_of_bytes,
			 8);

	cmd->len = cpu_to_le16(*cmd_len);

	cmd->tx_can.databytes = nbr_of_bytes;
	cmd->tx_can.dlc = dlc;

	अगर (cf->can_id & CAN_EFF_FLAG) अणु
		id = cf->can_id & CAN_EFF_MASK;
		flags = KVASER_USB_HYDRA_CF_FLAG_EXTENDED_ID;
		kcan_id = (cf->can_id & CAN_EFF_MASK) |
			  KVASER_USB_KCAN_DATA_IDE | KVASER_USB_KCAN_DATA_SRR;
	पूर्ण अन्यथा अणु
		id = cf->can_id & CAN_SFF_MASK;
		flags = 0;
		kcan_id = cf->can_id & CAN_SFF_MASK;
	पूर्ण

	अगर (cf->can_id & CAN_ERR_FLAG)
		flags |= KVASER_USB_HYDRA_CF_FLAG_ERROR_FRAME;

	kcan_header = ((dlc << KVASER_USB_KCAN_DATA_DLC_SHIFT) &
				KVASER_USB_KCAN_DATA_DLC_MASK) |
			KVASER_USB_KCAN_DATA_AREQ |
			(priv->can.ctrlmode & CAN_CTRLMODE_ONE_SHOT ?
				KVASER_USB_KCAN_DATA_OSM : 0);

	अगर (can_is_canfd_skb(skb)) अणु
		kcan_header |= KVASER_USB_KCAN_DATA_FDF |
			       (cf->flags & CANFD_BRS ?
					KVASER_USB_KCAN_DATA_BRS : 0);
	पूर्ण अन्यथा अणु
		अगर (cf->can_id & CAN_RTR_FLAG) अणु
			kcan_id |= KVASER_USB_KCAN_DATA_RTR;
			cmd->tx_can.databytes = 0;
			flags |= KVASER_USB_HYDRA_CF_FLAG_REMOTE_FRAME;
		पूर्ण
	पूर्ण

	cmd->tx_can.kcan_id = cpu_to_le32(kcan_id);
	cmd->tx_can.id = cpu_to_le32(id);
	cmd->tx_can.flags = cpu_to_le32(flags);
	cmd->tx_can.kcan_header = cpu_to_le32(kcan_header);

	स_नकल(cmd->tx_can.kcan_payload, cf->data, nbr_of_bytes);

	वापस cmd;
पूर्ण

अटल व्योम *
kvaser_usb_hydra_frame_to_cmd_std(स्थिर काष्ठा kvaser_usb_net_priv *priv,
				  स्थिर काष्ठा sk_buff *skb, पूर्णांक *frame_len,
				  पूर्णांक *cmd_len, u16 transid)
अणु
	काष्ठा kvaser_usb *dev = priv->dev;
	काष्ठा kvaser_cmd *cmd;
	काष्ठा can_frame *cf = (काष्ठा can_frame *)skb->data;
	u32 flags;
	u32 id;

	*frame_len = cf->len;

	cmd = kसुस्मृति(1, माप(काष्ठा kvaser_cmd), GFP_ATOMIC);
	अगर (!cmd)
		वापस शून्य;

	kvaser_usb_hydra_set_cmd_dest_he
		(cmd, dev->card_data.hydra.channel_to_he[priv->channel]);
	kvaser_usb_hydra_set_cmd_transid(cmd, transid);

	cmd->header.cmd_no = CMD_TX_CAN_MESSAGE;

	*cmd_len = ALIGN(माप(काष्ठा kvaser_cmd), 8);

	अगर (cf->can_id & CAN_EFF_FLAG) अणु
		id = (cf->can_id & CAN_EFF_MASK);
		id |= KVASER_USB_HYDRA_EXTENDED_FRAME_ID;
	पूर्ण अन्यथा अणु
		id = cf->can_id & CAN_SFF_MASK;
	पूर्ण

	cmd->tx_can.dlc = cf->len;

	flags = (cf->can_id & CAN_EFF_FLAG ?
		 KVASER_USB_HYDRA_CF_FLAG_EXTENDED_ID : 0);

	अगर (cf->can_id & CAN_RTR_FLAG)
		flags |= KVASER_USB_HYDRA_CF_FLAG_REMOTE_FRAME;

	flags |= (cf->can_id & CAN_ERR_FLAG ?
		  KVASER_USB_HYDRA_CF_FLAG_ERROR_FRAME : 0);

	cmd->tx_can.id = cpu_to_le32(id);
	cmd->tx_can.flags = flags;

	स_नकल(cmd->tx_can.data, cf->data, *frame_len);

	वापस cmd;
पूर्ण

अटल पूर्णांक kvaser_usb_hydra_set_mode(काष्ठा net_device *netdev,
				     क्रमागत can_mode mode)
अणु
	पूर्णांक err = 0;

	चयन (mode) अणु
	हाल CAN_MODE_START:
		/* CAN controller स्वतःmatically recovers from BUS_OFF */
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक kvaser_usb_hydra_set_bittiming(काष्ठा net_device *netdev)
अणु
	काष्ठा kvaser_cmd *cmd;
	काष्ठा kvaser_usb_net_priv *priv = netdev_priv(netdev);
	काष्ठा can_bittiming *bt = &priv->can.bittiming;
	काष्ठा kvaser_usb *dev = priv->dev;
	पूर्णांक tseg1 = bt->prop_seg + bt->phase_seg1;
	पूर्णांक tseg2 = bt->phase_seg2;
	पूर्णांक sjw = bt->sjw;
	पूर्णांक err;

	cmd = kसुस्मृति(1, माप(काष्ठा kvaser_cmd), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->header.cmd_no = CMD_SET_BUSPARAMS_REQ;
	cmd->set_busparams_req.bitrate = cpu_to_le32(bt->bitrate);
	cmd->set_busparams_req.sjw = (u8)sjw;
	cmd->set_busparams_req.tseg1 = (u8)tseg1;
	cmd->set_busparams_req.tseg2 = (u8)tseg2;
	cmd->set_busparams_req.nsamples = 1;

	kvaser_usb_hydra_set_cmd_dest_he
		(cmd, dev->card_data.hydra.channel_to_he[priv->channel]);
	kvaser_usb_hydra_set_cmd_transid
				(cmd, kvaser_usb_hydra_get_next_transid(dev));

	err = kvaser_usb_send_cmd(dev, cmd, kvaser_usb_hydra_cmd_size(cmd));

	kमुक्त(cmd);

	वापस err;
पूर्ण

अटल पूर्णांक kvaser_usb_hydra_set_data_bittiming(काष्ठा net_device *netdev)
अणु
	काष्ठा kvaser_cmd *cmd;
	काष्ठा kvaser_usb_net_priv *priv = netdev_priv(netdev);
	काष्ठा can_bittiming *dbt = &priv->can.data_bittiming;
	काष्ठा kvaser_usb *dev = priv->dev;
	पूर्णांक tseg1 = dbt->prop_seg + dbt->phase_seg1;
	पूर्णांक tseg2 = dbt->phase_seg2;
	पूर्णांक sjw = dbt->sjw;
	पूर्णांक err;

	cmd = kसुस्मृति(1, माप(काष्ठा kvaser_cmd), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->header.cmd_no = CMD_SET_BUSPARAMS_FD_REQ;
	cmd->set_busparams_req.bitrate_d = cpu_to_le32(dbt->bitrate);
	cmd->set_busparams_req.sjw_d = (u8)sjw;
	cmd->set_busparams_req.tseg1_d = (u8)tseg1;
	cmd->set_busparams_req.tseg2_d = (u8)tseg2;
	cmd->set_busparams_req.nsamples_d = 1;

	अगर (priv->can.ctrlmode & CAN_CTRLMODE_FD) अणु
		अगर (priv->can.ctrlmode & CAN_CTRLMODE_FD_NON_ISO)
			cmd->set_busparams_req.canfd_mode =
					KVASER_USB_HYDRA_BUS_MODE_NONISO;
		अन्यथा
			cmd->set_busparams_req.canfd_mode =
					KVASER_USB_HYDRA_BUS_MODE_CANFD_ISO;
	पूर्ण

	kvaser_usb_hydra_set_cmd_dest_he
		(cmd, dev->card_data.hydra.channel_to_he[priv->channel]);
	kvaser_usb_hydra_set_cmd_transid
				(cmd, kvaser_usb_hydra_get_next_transid(dev));

	err = kvaser_usb_send_cmd(dev, cmd, kvaser_usb_hydra_cmd_size(cmd));

	kमुक्त(cmd);

	वापस err;
पूर्ण

अटल पूर्णांक kvaser_usb_hydra_get_berr_counter(स्थिर काष्ठा net_device *netdev,
					     काष्ठा can_berr_counter *bec)
अणु
	काष्ठा kvaser_usb_net_priv *priv = netdev_priv(netdev);
	पूर्णांक err;

	err = kvaser_usb_hydra_send_simple_cmd(priv->dev,
					       CMD_GET_CHIP_STATE_REQ,
					       priv->channel);
	अगर (err)
		वापस err;

	*bec = priv->bec;

	वापस 0;
पूर्ण

अटल पूर्णांक kvaser_usb_hydra_setup_endpoपूर्णांकs(काष्ठा kvaser_usb *dev)
अणु
	स्थिर काष्ठा usb_host_पूर्णांकerface *अगरace_desc;
	काष्ठा usb_endpoपूर्णांक_descriptor *ep;
	पूर्णांक i;

	अगरace_desc = dev->पूर्णांकf->cur_altsetting;

	क्रम (i = 0; i < अगरace_desc->desc.bNumEndpoपूर्णांकs; ++i) अणु
		ep = &अगरace_desc->endpoपूर्णांक[i].desc;

		अगर (!dev->bulk_in && usb_endpoपूर्णांक_is_bulk_in(ep) &&
		    ep->bEndpoपूर्णांकAddress == KVASER_USB_HYDRA_BULK_EP_IN_ADDR)
			dev->bulk_in = ep;

		अगर (!dev->bulk_out && usb_endpoपूर्णांक_is_bulk_out(ep) &&
		    ep->bEndpoपूर्णांकAddress == KVASER_USB_HYDRA_BULK_EP_OUT_ADDR)
			dev->bulk_out = ep;

		अगर (dev->bulk_in && dev->bulk_out)
			वापस 0;
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक kvaser_usb_hydra_init_card(काष्ठा kvaser_usb *dev)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक i;
	काष्ठा kvaser_usb_dev_card_data_hydra *card_data =
							&dev->card_data.hydra;

	card_data->transid = KVASER_USB_HYDRA_MIN_TRANSID;
	spin_lock_init(&card_data->transid_lock);

	स_रखो(card_data->usb_rx_leftover, 0, KVASER_USB_HYDRA_MAX_CMD_LEN);
	card_data->usb_rx_leftover_len = 0;
	spin_lock_init(&card_data->usb_rx_leftover_lock);

	स_रखो(card_data->channel_to_he, KVASER_USB_HYDRA_HE_ADDRESS_ILLEGAL,
	       माप(card_data->channel_to_he));
	card_data->sysdbg_he = 0;

	क्रम (i = 0; i < KVASER_USB_MAX_NET_DEVICES; i++) अणु
		err = kvaser_usb_hydra_map_channel
					(dev,
					 (KVASER_USB_HYDRA_TRANSID_CANHE | i),
					 i, "CAN");
		अगर (err) अणु
			dev_err(&dev->पूर्णांकf->dev,
				"CMD_MAP_CHANNEL_REQ failed for CAN%u\n", i);
			वापस err;
		पूर्ण
	पूर्ण

	err = kvaser_usb_hydra_map_channel(dev, KVASER_USB_HYDRA_TRANSID_SYSDBG,
					   0, "SYSDBG");
	अगर (err) अणु
		dev_err(&dev->पूर्णांकf->dev,
			"CMD_MAP_CHANNEL_REQ failed for SYSDBG\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kvaser_usb_hydra_get_software_info(काष्ठा kvaser_usb *dev)
अणु
	काष्ठा kvaser_cmd cmd;
	पूर्णांक err;

	err = kvaser_usb_hydra_send_simple_cmd(dev, CMD_GET_SOFTWARE_INFO_REQ,
					       -1);
	अगर (err)
		वापस err;

	स_रखो(&cmd, 0, माप(काष्ठा kvaser_cmd));
	err = kvaser_usb_hydra_रुको_cmd(dev, CMD_GET_SOFTWARE_INFO_RESP, &cmd);
	अगर (err)
		वापस err;

	dev->max_tx_urbs = min_t(अचिन्हित पूर्णांक, KVASER_USB_MAX_TX_URBS,
				 le16_to_cpu(cmd.sw_info.max_outstanding_tx));

	वापस 0;
पूर्ण

अटल पूर्णांक kvaser_usb_hydra_get_software_details(काष्ठा kvaser_usb *dev)
अणु
	काष्ठा kvaser_cmd *cmd;
	पूर्णांक err;
	u32 flags;
	काष्ठा kvaser_usb_dev_card_data *card_data = &dev->card_data;

	cmd = kसुस्मृति(1, माप(काष्ठा kvaser_cmd), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->header.cmd_no = CMD_GET_SOFTWARE_DETAILS_REQ;
	cmd->sw_detail_req.use_ext_cmd = 1;
	kvaser_usb_hydra_set_cmd_dest_he
				(cmd, KVASER_USB_HYDRA_HE_ADDRESS_ILLEGAL);

	kvaser_usb_hydra_set_cmd_transid
				(cmd, kvaser_usb_hydra_get_next_transid(dev));

	err = kvaser_usb_send_cmd(dev, cmd, kvaser_usb_hydra_cmd_size(cmd));
	अगर (err)
		जाओ end;

	err = kvaser_usb_hydra_रुको_cmd(dev, CMD_GET_SOFTWARE_DETAILS_RESP,
					cmd);
	अगर (err)
		जाओ end;

	dev->fw_version = le32_to_cpu(cmd->sw_detail_res.sw_version);
	flags = le32_to_cpu(cmd->sw_detail_res.sw_flags);

	अगर (flags & KVASER_USB_HYDRA_SW_FLAG_FW_BAD) अणु
		dev_err(&dev->पूर्णांकf->dev,
			"Bad firmware, device refuse to run!\n");
		err = -EINVAL;
		जाओ end;
	पूर्ण

	अगर (flags & KVASER_USB_HYDRA_SW_FLAG_FW_BETA)
		dev_info(&dev->पूर्णांकf->dev, "Beta firmware in use\n");

	अगर (flags & KVASER_USB_HYDRA_SW_FLAG_EXT_CAP)
		card_data->capabilities |= KVASER_USB_CAP_EXT_CAP;

	अगर (flags & KVASER_USB_HYDRA_SW_FLAG_EXT_CMD)
		card_data->capabilities |= KVASER_USB_HYDRA_CAP_EXT_CMD;

	अगर (flags & KVASER_USB_HYDRA_SW_FLAG_CANFD)
		card_data->ctrlmode_supported |= CAN_CTRLMODE_FD;

	अगर (flags & KVASER_USB_HYDRA_SW_FLAG_NONISO)
		card_data->ctrlmode_supported |= CAN_CTRLMODE_FD_NON_ISO;

	अगर (flags &  KVASER_USB_HYDRA_SW_FLAG_FREQ_80M)
		dev->cfg = &kvaser_usb_hydra_dev_cfg_kcan;
	अन्यथा अगर (flags & KVASER_USB_HYDRA_SW_FLAG_CAN_FREQ_80M)
		dev->cfg = &kvaser_usb_hydra_dev_cfg_rt;
	अन्यथा
		dev->cfg = &kvaser_usb_hydra_dev_cfg_flexc;

end:
	kमुक्त(cmd);

	वापस err;
पूर्ण

अटल पूर्णांक kvaser_usb_hydra_get_card_info(काष्ठा kvaser_usb *dev)
अणु
	काष्ठा kvaser_cmd cmd;
	पूर्णांक err;

	err = kvaser_usb_hydra_send_simple_cmd(dev, CMD_GET_CARD_INFO_REQ, -1);
	अगर (err)
		वापस err;

	स_रखो(&cmd, 0, माप(काष्ठा kvaser_cmd));
	err = kvaser_usb_hydra_रुको_cmd(dev, CMD_GET_CARD_INFO_RESP, &cmd);
	अगर (err)
		वापस err;

	dev->nchannels = cmd.card_info.nchannels;
	अगर (dev->nchannels > KVASER_USB_MAX_NET_DEVICES)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक kvaser_usb_hydra_get_capabilities(काष्ठा kvaser_usb *dev)
अणु
	पूर्णांक err;
	u16 status;

	अगर (!(dev->card_data.capabilities & KVASER_USB_CAP_EXT_CAP)) अणु
		dev_info(&dev->पूर्णांकf->dev,
			 "No extended capability support. Upgrade your device.\n");
		वापस 0;
	पूर्ण

	err = kvaser_usb_hydra_get_single_capability
					(dev,
					 KVASER_USB_HYDRA_CAP_CMD_LISTEN_MODE,
					 &status);
	अगर (err)
		वापस err;
	अगर (status)
		dev_info(&dev->पूर्णांकf->dev,
			 "KVASER_USB_HYDRA_CAP_CMD_LISTEN_MODE failed %u\n",
			 status);

	err = kvaser_usb_hydra_get_single_capability
					(dev,
					 KVASER_USB_HYDRA_CAP_CMD_ERR_REPORT,
					 &status);
	अगर (err)
		वापस err;
	अगर (status)
		dev_info(&dev->पूर्णांकf->dev,
			 "KVASER_USB_HYDRA_CAP_CMD_ERR_REPORT failed %u\n",
			 status);

	err = kvaser_usb_hydra_get_single_capability
					(dev, KVASER_USB_HYDRA_CAP_CMD_ONE_SHOT,
					 &status);
	अगर (err)
		वापस err;
	अगर (status)
		dev_info(&dev->पूर्णांकf->dev,
			 "KVASER_USB_HYDRA_CAP_CMD_ONE_SHOT failed %u\n",
			 status);

	वापस 0;
पूर्ण

अटल पूर्णांक kvaser_usb_hydra_set_opt_mode(स्थिर काष्ठा kvaser_usb_net_priv *priv)
अणु
	काष्ठा kvaser_usb *dev = priv->dev;
	काष्ठा kvaser_cmd *cmd;
	पूर्णांक err;

	अगर ((priv->can.ctrlmode &
	    (CAN_CTRLMODE_FD | CAN_CTRLMODE_FD_NON_ISO)) ==
	    CAN_CTRLMODE_FD_NON_ISO) अणु
		netdev_warn(priv->netdev,
			    "CTRLMODE_FD shall be on if CTRLMODE_FD_NON_ISO is on\n");
		वापस -EINVAL;
	पूर्ण

	cmd = kसुस्मृति(1, माप(काष्ठा kvaser_cmd), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->header.cmd_no = CMD_SET_DRIVERMODE_REQ;
	kvaser_usb_hydra_set_cmd_dest_he
		(cmd, dev->card_data.hydra.channel_to_he[priv->channel]);
	kvaser_usb_hydra_set_cmd_transid
				(cmd, kvaser_usb_hydra_get_next_transid(dev));
	अगर (priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY)
		cmd->set_ctrlmode.mode = KVASER_USB_HYDRA_CTRLMODE_LISTEN;
	अन्यथा
		cmd->set_ctrlmode.mode = KVASER_USB_HYDRA_CTRLMODE_NORMAL;

	err = kvaser_usb_send_cmd(dev, cmd, kvaser_usb_hydra_cmd_size(cmd));
	kमुक्त(cmd);

	वापस err;
पूर्ण

अटल पूर्णांक kvaser_usb_hydra_start_chip(काष्ठा kvaser_usb_net_priv *priv)
अणु
	पूर्णांक err;

	init_completion(&priv->start_comp);

	err = kvaser_usb_hydra_send_simple_cmd(priv->dev, CMD_START_CHIP_REQ,
					       priv->channel);
	अगर (err)
		वापस err;

	अगर (!रुको_क्रम_completion_समयout(&priv->start_comp,
					 msecs_to_jअगरfies(KVASER_USB_TIMEOUT)))
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक kvaser_usb_hydra_stop_chip(काष्ठा kvaser_usb_net_priv *priv)
अणु
	पूर्णांक err;

	init_completion(&priv->stop_comp);

	/* Make sure we करो not report invalid BUS_OFF from CMD_CHIP_STATE_EVENT
	 * see comment in kvaser_usb_hydra_update_state()
	 */
	priv->can.state = CAN_STATE_STOPPED;

	err = kvaser_usb_hydra_send_simple_cmd(priv->dev, CMD_STOP_CHIP_REQ,
					       priv->channel);
	अगर (err)
		वापस err;

	अगर (!रुको_क्रम_completion_समयout(&priv->stop_comp,
					 msecs_to_jअगरfies(KVASER_USB_TIMEOUT)))
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक kvaser_usb_hydra_flush_queue(काष्ठा kvaser_usb_net_priv *priv)
अणु
	पूर्णांक err;

	init_completion(&priv->flush_comp);

	err = kvaser_usb_hydra_send_simple_cmd(priv->dev, CMD_FLUSH_QUEUE,
					       priv->channel);
	अगर (err)
		वापस err;

	अगर (!रुको_क्रम_completion_समयout(&priv->flush_comp,
					 msecs_to_jअगरfies(KVASER_USB_TIMEOUT)))
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

/* A single extended hydra command can be transmitted in multiple transfers
 * We have to buffer partial hydra commands, and handle them on next callback.
 */
अटल व्योम kvaser_usb_hydra_पढ़ो_bulk_callback(काष्ठा kvaser_usb *dev,
						व्योम *buf, पूर्णांक len)
अणु
	अचिन्हित दीर्घ irq_flags;
	काष्ठा kvaser_cmd *cmd;
	पूर्णांक pos = 0;
	माप_प्रकार cmd_len;
	काष्ठा kvaser_usb_dev_card_data_hydra *card_data =
							&dev->card_data.hydra;
	पूर्णांक usb_rx_leftover_len;
	spinlock_t *usb_rx_leftover_lock = &card_data->usb_rx_leftover_lock;

	spin_lock_irqsave(usb_rx_leftover_lock, irq_flags);
	usb_rx_leftover_len = card_data->usb_rx_leftover_len;
	अगर (usb_rx_leftover_len) अणु
		पूर्णांक reमुख्यing_bytes;

		cmd = (काष्ठा kvaser_cmd *)card_data->usb_rx_leftover;

		cmd_len = kvaser_usb_hydra_cmd_size(cmd);

		reमुख्यing_bytes = min_t(अचिन्हित पूर्णांक, len,
					cmd_len - usb_rx_leftover_len);
		/* Make sure we करो not overflow usb_rx_leftover */
		अगर (reमुख्यing_bytes + usb_rx_leftover_len >
						KVASER_USB_HYDRA_MAX_CMD_LEN) अणु
			dev_err(&dev->पूर्णांकf->dev, "Format error\n");
			spin_unlock_irqrestore(usb_rx_leftover_lock, irq_flags);
			वापस;
		पूर्ण

		स_नकल(card_data->usb_rx_leftover + usb_rx_leftover_len, buf,
		       reमुख्यing_bytes);
		pos += reमुख्यing_bytes;

		अगर (reमुख्यing_bytes + usb_rx_leftover_len == cmd_len) अणु
			kvaser_usb_hydra_handle_cmd(dev, cmd);
			usb_rx_leftover_len = 0;
		पूर्ण अन्यथा अणु
			/* Command still not complete */
			usb_rx_leftover_len += reमुख्यing_bytes;
		पूर्ण
		card_data->usb_rx_leftover_len = usb_rx_leftover_len;
	पूर्ण
	spin_unlock_irqrestore(usb_rx_leftover_lock, irq_flags);

	जबतक (pos < len) अणु
		cmd = buf + pos;

		cmd_len = kvaser_usb_hydra_cmd_size(cmd);

		अगर (pos + cmd_len > len) अणु
			/* We got first part of a command */
			पूर्णांक leftover_bytes;

			leftover_bytes = len - pos;
			/* Make sure we करो not overflow usb_rx_leftover */
			अगर (leftover_bytes > KVASER_USB_HYDRA_MAX_CMD_LEN) अणु
				dev_err(&dev->पूर्णांकf->dev, "Format error\n");
				वापस;
			पूर्ण
			spin_lock_irqsave(usb_rx_leftover_lock, irq_flags);
			स_नकल(card_data->usb_rx_leftover, buf + pos,
			       leftover_bytes);
			card_data->usb_rx_leftover_len = leftover_bytes;
			spin_unlock_irqrestore(usb_rx_leftover_lock, irq_flags);
			अवरोध;
		पूर्ण

		kvaser_usb_hydra_handle_cmd(dev, cmd);
		pos += cmd_len;
	पूर्ण
पूर्ण

अटल व्योम *
kvaser_usb_hydra_frame_to_cmd(स्थिर काष्ठा kvaser_usb_net_priv *priv,
			      स्थिर काष्ठा sk_buff *skb, पूर्णांक *frame_len,
			      पूर्णांक *cmd_len, u16 transid)
अणु
	व्योम *buf;

	अगर (priv->dev->card_data.capabilities & KVASER_USB_HYDRA_CAP_EXT_CMD)
		buf = kvaser_usb_hydra_frame_to_cmd_ext(priv, skb, frame_len,
							cmd_len, transid);
	अन्यथा
		buf = kvaser_usb_hydra_frame_to_cmd_std(priv, skb, frame_len,
							cmd_len, transid);

	वापस buf;
पूर्ण

स्थिर काष्ठा kvaser_usb_dev_ops kvaser_usb_hydra_dev_ops = अणु
	.dev_set_mode = kvaser_usb_hydra_set_mode,
	.dev_set_bittiming = kvaser_usb_hydra_set_bittiming,
	.dev_set_data_bittiming = kvaser_usb_hydra_set_data_bittiming,
	.dev_get_berr_counter = kvaser_usb_hydra_get_berr_counter,
	.dev_setup_endpoपूर्णांकs = kvaser_usb_hydra_setup_endpoपूर्णांकs,
	.dev_init_card = kvaser_usb_hydra_init_card,
	.dev_get_software_info = kvaser_usb_hydra_get_software_info,
	.dev_get_software_details = kvaser_usb_hydra_get_software_details,
	.dev_get_card_info = kvaser_usb_hydra_get_card_info,
	.dev_get_capabilities = kvaser_usb_hydra_get_capabilities,
	.dev_set_opt_mode = kvaser_usb_hydra_set_opt_mode,
	.dev_start_chip = kvaser_usb_hydra_start_chip,
	.dev_stop_chip = kvaser_usb_hydra_stop_chip,
	.dev_reset_chip = शून्य,
	.dev_flush_queue = kvaser_usb_hydra_flush_queue,
	.dev_पढ़ो_bulk_callback = kvaser_usb_hydra_पढ़ो_bulk_callback,
	.dev_frame_to_cmd = kvaser_usb_hydra_frame_to_cmd,
पूर्ण;

अटल स्थिर काष्ठा kvaser_usb_dev_cfg kvaser_usb_hydra_dev_cfg_kcan = अणु
	.घड़ी = अणु
		.freq = 80000000,
	पूर्ण,
	.बारtamp_freq = 80,
	.bittiming_स्थिर = &kvaser_usb_hydra_kcan_bittiming_c,
	.data_bittiming_स्थिर = &kvaser_usb_hydra_kcan_bittiming_c,
पूर्ण;

अटल स्थिर काष्ठा kvaser_usb_dev_cfg kvaser_usb_hydra_dev_cfg_flexc = अणु
	.घड़ी = अणु
		.freq = 24000000,
	पूर्ण,
	.बारtamp_freq = 1,
	.bittiming_स्थिर = &kvaser_usb_hydra_flexc_bittiming_c,
पूर्ण;

अटल स्थिर काष्ठा kvaser_usb_dev_cfg kvaser_usb_hydra_dev_cfg_rt = अणु
	.घड़ी = अणु
		.freq = 80000000,
	पूर्ण,
	.बारtamp_freq = 24,
	.bittiming_स्थिर = &kvaser_usb_hydra_rt_bittiming_c,
	.data_bittiming_स्थिर = &kvaser_usb_hydra_rtd_bittiming_c,
पूर्ण;
