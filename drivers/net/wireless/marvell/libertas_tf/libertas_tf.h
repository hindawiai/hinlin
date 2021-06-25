<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Copyright (C) 2008, cozybit Inc.
 *  Copyright (C) 2007, Red Hat, Inc.
 *  Copyright (C) 2003-2006, Marvell International Ltd.
 */
#समावेश <linux/spinlock.h>
#समावेश <linux/device.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <net/mac80211.h>

#समावेश "deb_defs.h"

#अगर_अघोषित DRV_NAME
#घोषणा DRV_NAME "libertas_tf"
#पूर्ण_अगर

#घोषणा	MRVL_DEFAULT_RETRIES			9
#घोषणा MRVL_PER_PACKET_RATE			0x10
#घोषणा MRVL_MAX_BCN_SIZE			440
#घोषणा CMD_OPTION_WAITFORRSP			0x0002

/* Return command are almost always the same as the host command, but with
 * bit 15 set high.  There are a few exceptions, though...
 */
#घोषणा CMD_RET(cmd)			(0x8000 | cmd)

/* Command codes */
#घोषणा CMD_GET_HW_SPEC				0x0003
#घोषणा CMD_802_11_RESET			0x0005
#घोषणा CMD_MAC_MULTICAST_ADR			0x0010
#घोषणा CMD_802_11_RADIO_CONTROL		0x001c
#घोषणा CMD_802_11_RF_CHANNEL			0x001d
#घोषणा CMD_802_11_RF_TX_POWER			0x001e
#घोषणा CMD_MAC_CONTROL				0x0028
#घोषणा CMD_802_11_MAC_ADDRESS			0x004d
#घोषणा	CMD_SET_BOOT2_VER			0x00a5
#घोषणा CMD_802_11_BEACON_CTRL			0x00b0
#घोषणा CMD_802_11_BEACON_SET			0x00cb
#घोषणा CMD_802_11_SET_MODE			0x00cc
#घोषणा CMD_802_11_SET_BSSID			0x00cd

#घोषणा CMD_ACT_GET			0x0000
#घोषणा CMD_ACT_SET			0x0001

/* Define action or option क्रम CMD_802_11_RESET */
#घोषणा CMD_ACT_HALT			0x0003

/* Define action or option क्रम CMD_MAC_CONTROL */
#घोषणा CMD_ACT_MAC_RX_ON			0x0001
#घोषणा CMD_ACT_MAC_TX_ON			0x0002
#घोषणा CMD_ACT_MAC_MULTICAST_ENABLE		0x0020
#घोषणा CMD_ACT_MAC_BROADCAST_ENABLE		0x0040
#घोषणा CMD_ACT_MAC_PROMISCUOUS_ENABLE		0x0080
#घोषणा CMD_ACT_MAC_ALL_MULTICAST_ENABLE	0x0100

/* Define action or option क्रम CMD_802_11_RADIO_CONTROL */
#घोषणा CMD_TYPE_AUTO_PREAMBLE		0x0001
#घोषणा CMD_TYPE_SHORT_PREAMBLE		0x0002
#घोषणा CMD_TYPE_LONG_PREAMBLE		0x0003

#घोषणा TURN_ON_RF			0x01
#घोषणा RADIO_ON			0x01
#घोषणा RADIO_OFF			0x00

#घोषणा SET_AUTO_PREAMBLE		0x05
#घोषणा SET_SHORT_PREAMBLE		0x03
#घोषणा SET_LONG_PREAMBLE		0x01

/* Define action or option क्रम CMD_802_11_RF_CHANNEL */
#घोषणा CMD_OPT_802_11_RF_CHANNEL_GET	0x00
#घोषणा CMD_OPT_802_11_RF_CHANNEL_SET	0x01

/* Codes क्रम CMD_802_11_SET_MODE */
क्रमागत lbtf_mode अणु
	LBTF_PASSIVE_MODE,
	LBTF_STA_MODE,
	LBTF_AP_MODE,
पूर्ण;

/** Card Event definition */
#घोषणा MACREG_INT_CODE_FIRMWARE_READY		48
/** Buffer Constants */

/*	The size of SQ memory PPA, DPA are 8 DWORDs, that keep the physical
*	addresses of TxPD buffers. Station has only 8 TxPD available, Whereas
*	driver has more local TxPDs. Each TxPD on the host memory is associated
*	with a Tx control node. The driver मुख्यtains 8 RxPD descriptors क्रम
*	station firmware to store Rx packet inक्रमmation.
*
*	Current version of MAC has a 32x6 multicast address buffer.
*
*	802.11b can have up to  14 channels, the driver keeps the
*	BSSID(MAC address) of each APs or Ad hoc stations it has sensed.
*/

#घोषणा MRVDRV_MAX_MULTICAST_LIST_SIZE	32
#घोषणा LBS_NUM_CMD_BUFFERS             10
#घोषणा LBS_CMD_BUFFER_SIZE             (2 * 1024)
#घोषणा MRVDRV_MAX_CHANNEL_SIZE		14
#घोषणा MRVDRV_SNAP_HEADER_LEN          8

#घोषणा	LBS_UPLD_SIZE			2312
#घोषणा DEV_NAME_LEN			32

/** Misc स्थिरants */
/* This section defines 802.11 specअगरic contants */

#घोषणा MRVDRV_MAX_REGION_CODE			6
/**
 * the table to keep region code
 */
#घोषणा LBTF_REGDOMAIN_US	0x10
#घोषणा LBTF_REGDOMAIN_CA	0x20
#घोषणा LBTF_REGDOMAIN_EU	0x30
#घोषणा LBTF_REGDOMAIN_SP	0x31
#घोषणा LBTF_REGDOMAIN_FR	0x32
#घोषणा LBTF_REGDOMAIN_JP	0x40

#घोषणा SBI_EVENT_CAUSE_SHIFT		3

/** RxPD status */

#घोषणा MRVDRV_RXPD_STATUS_OK                0x0001


/* This is क्रम firmware specअगरic length */
#घोषणा EXTRA_LEN	36

#घोषणा MRVDRV_ETH_TX_PACKET_BUFFER_SIZE \
	(ETH_FRAME_LEN + माप(काष्ठा txpd) + EXTRA_LEN)

#घोषणा MRVDRV_ETH_RX_PACKET_BUFFER_SIZE \
	(ETH_FRAME_LEN + माप(काष्ठा rxpd) \
	 + MRVDRV_SNAP_HEADER_LEN + EXTRA_LEN)

#घोषणा	CMD_F_HOSTCMD		(1 << 0)
#घोषणा FW_CAPINFO_WPA  	(1 << 0)

#घोषणा RF_ANTENNA_1		0x1
#घोषणा RF_ANTENNA_2		0x2
#घोषणा RF_ANTENNA_AUTO		0xFFFF

#घोषणा LBTF_EVENT_BCN_SENT	55

/** Global Variable Declaration */
/** mv_ms_type */
क्रमागत mv_ms_type अणु
	MVMS_DAT = 0,
	MVMS_CMD = 1,
	MVMS_TXDONE = 2,
	MVMS_EVENT
पूर्ण;

बाह्य काष्ठा workqueue_काष्ठा *lbtf_wq;

काष्ठा lbtf_निजी;

काष्ठा lbtf_offset_value अणु
	u32 offset;
	u32 value;
पूर्ण;

काष्ठा channel_range अणु
	u8 regकरोमुख्य;
	u8 start;
	u8 end; /* exclusive (channel must be less than end) */
पूर्ण;

काष्ठा अगर_usb_card;

काष्ठा lbtf_ops अणु
	/** Hardware access */
	पूर्णांक (*hw_host_to_card)(काष्ठा lbtf_निजी *priv, u8 type,
			       u8 *payload, u16 nb);
	पूर्णांक (*hw_prog_firmware)(काष्ठा lbtf_निजी *priv);
	पूर्णांक (*hw_reset_device)(काष्ठा lbtf_निजी *priv);
पूर्ण;

/** Private काष्ठाure क्रम the MV device */
काष्ठा lbtf_निजी अणु
	व्योम *card;
	काष्ठा ieee80211_hw *hw;
	स्थिर काष्ठा lbtf_ops *ops;

	/* Command response buffer */
	u8 cmd_resp_buff[LBS_UPLD_SIZE];
	/* Download sent:
	   bit0 1/0=data_sent/data_tx_करोne,
	   bit1 1/0=cmd_sent/cmd_tx_करोne,
	   all other bits reserved 0 */
	काष्ठा ieee80211_vअगर *vअगर;

	काष्ठा work_काष्ठा cmd_work;
	काष्ठा work_काष्ठा tx_work;

	/** Wlan adapter data काष्ठाure*/
	/** STATUS variables */
	u32 fwrelease;
	u32 fwcapinfo;
	/* रक्षित with big lock */

	काष्ठा mutex lock;

	/** command-related variables */
	u16 seqnum;
	/* रक्षित by big lock */

	काष्ठा cmd_ctrl_node *cmd_array;
	/** Current command */
	काष्ठा cmd_ctrl_node *cur_cmd;
	/** command Queues */
	/** Free command buffers */
	काष्ठा list_head cmdमुक्तq;
	/** Pending command buffers */
	काष्ठा list_head cmdpendingq;

	/** spin locks */
	spinlock_t driver_lock;

	/** Timers */
	काष्ठा समयr_list command_समयr;
	पूर्णांक nr_retries;
	पूर्णांक cmd_समयd_out;

	u8 cmd_response_rxed;

	/** capability Info used in Association, start, join */
	u16 capability;

	/** MAC address inक्रमmation */
	u8 current_addr[ETH_ALEN];
	u8 multicastlist[MRVDRV_MAX_MULTICAST_LIST_SIZE][ETH_ALEN];
	u32 nr_of_multicasपंचांगacaddr;
	पूर्णांक cur_freq;

	काष्ठा sk_buff *skb_to_tx;
	काष्ठा sk_buff *tx_skb;

	/** NIC Operation अक्षरacteristics */
	u16 mac_control;
	u16 regioncode;
	काष्ठा channel_range range;

	u8 radioon;
	u32 preamble;

	काष्ठा ieee80211_channel channels[14];
	काष्ठा ieee80211_rate rates[12];
	काष्ठा ieee80211_supported_band band;
	काष्ठा lbtf_offset_value offsetvalue;

	u8 surpriseहटाओd;
	काष्ठा sk_buff_head bc_ps_buf;

	/* Most recently reported noise in dBm */
	s8 noise;
पूर्ण;

/* 802.11-related definitions */

/* TxPD descriptor */
काष्ठा txpd अणु
	/* Current Tx packet status */
	__le32 tx_status;
	/* Tx control */
	__le32 tx_control;
	__le32 tx_packet_location;
	/* Tx packet length */
	__le16 tx_packet_length;
	/* First 2 byte of destination MAC address */
	u8 tx_dest_addr_high[2];
	/* Last 4 byte of destination MAC address */
	u8 tx_dest_addr_low[4];
	/* Pkt Priority */
	u8 priority;
	/* Pkt Trasnit Power control */
	u8 घातermgmt;
	/* Time the packet has been queued in the driver (units = 2ms) */
	u8 pktdelay_2ms;
	/* reserved */
	u8 reserved1;
पूर्ण;

/* RxPD Descriptor */
काष्ठा rxpd अणु
	/* Current Rx packet status */
	__le16 status;

	/* SNR */
	u8 snr;

	/* Tx control */
	u8 rx_control;

	/* Pkt length */
	__le16 pkt_len;

	/* Noise Floor */
	u8 nf;

	/* Rx Packet Rate */
	u8 rx_rate;

	/* Pkt addr */
	__le32 pkt_ptr;

	/* Next Rx RxPD addr */
	__le32 next_rxpd_ptr;

	/* Pkt Priority */
	u8 priority;
	u8 reserved[3];
पूर्ण;

काष्ठा cmd_header अणु
	__le16 command;
	__le16 size;
	__le16 seqnum;
	__le16 result;
पूर्ण __packed;

काष्ठा cmd_ctrl_node अणु
	काष्ठा list_head list;
	पूर्णांक result;
	/* command response */
	पूर्णांक (*callback)(काष्ठा lbtf_निजी *,
			अचिन्हित दीर्घ, काष्ठा cmd_header *);
	अचिन्हित दीर्घ callback_arg;
	/* command data */
	काष्ठा cmd_header *cmdbuf;
	/* रुको queue */
	u16 cmdरुकोqwoken;
	रुको_queue_head_t cmdरुको_q;
पूर्ण;

/*
 * Define data काष्ठाure क्रम CMD_GET_HW_SPEC
 * This काष्ठाure defines the response क्रम the GET_HW_SPEC command
 */
काष्ठा cmd_ds_get_hw_spec अणु
	काष्ठा cmd_header hdr;

	/* HW Interface version number */
	__le16 hwअगरversion;
	/* HW version number */
	__le16 version;
	/* Max number of TxPD FW can handle */
	__le16 nr_txpd;
	/* Max no of Multicast address */
	__le16 nr_mcast_adr;
	/* MAC address */
	u8 permanentaddr[6];

	/* region Code */
	__le16 regioncode;

	/* Number of antenna used */
	__le16 nr_antenna;

	/* FW release number, example 0x01030304 = 2.3.4p1 */
	__le32 fwrelease;

	/* Base Address of TxPD queue */
	__le32 wcb_base;
	/* Read Poपूर्णांकer of RxPd queue */
	__le32 rxpd_rdptr;

	/* Write Poपूर्णांकer of RxPd queue */
	__le32 rxpd_wrptr;

	/*FW/HW capability */
	__le32 fwcapinfo;
पूर्ण __packed;

काष्ठा cmd_ds_mac_control अणु
	काष्ठा cmd_header hdr;
	__le16 action;
	u16 reserved;
पूर्ण;

काष्ठा cmd_ds_802_11_mac_address अणु
	काष्ठा cmd_header hdr;

	__le16 action;
	uपूर्णांक8_t macadd[ETH_ALEN];
पूर्ण;

काष्ठा cmd_ds_mac_multicast_addr अणु
	काष्ठा cmd_header hdr;

	__le16 action;
	__le16 nr_of_adrs;
	u8 maclist[ETH_ALEN * MRVDRV_MAX_MULTICAST_LIST_SIZE];
पूर्ण;

काष्ठा cmd_ds_set_mode अणु
	काष्ठा cmd_header hdr;

	__le16 mode;
पूर्ण;

काष्ठा cmd_ds_set_bssid अणु
	काष्ठा cmd_header hdr;

	u8 bssid[6];
	u8 activate;
पूर्ण;

काष्ठा cmd_ds_802_11_radio_control अणु
	काष्ठा cmd_header hdr;

	__le16 action;
	__le16 control;
पूर्ण;


काष्ठा cmd_ds_802_11_rf_channel अणु
	काष्ठा cmd_header hdr;

	__le16 action;
	__le16 channel;
	__le16 rftype;      /* unused */
	__le16 reserved;    /* unused */
	u8 channellist[32]; /* unused */
पूर्ण;

काष्ठा cmd_ds_set_boot2_ver अणु
	काष्ठा cmd_header hdr;

	__le16 action;
	__le16 version;
पूर्ण;

काष्ठा cmd_ds_802_11_reset अणु
	काष्ठा cmd_header hdr;

	__le16 action;
पूर्ण;

काष्ठा cmd_ds_802_11_beacon_control अणु
	काष्ठा cmd_header hdr;

	__le16 action;
	__le16 beacon_enable;
	__le16 beacon_period;
पूर्ण;

काष्ठा cmd_ds_802_11_beacon_set अणु
	काष्ठा cmd_header hdr;

	__le16 len;
	u8 beacon[MRVL_MAX_BCN_SIZE];
पूर्ण;

काष्ठा cmd_ctrl_node;

/** Function Prototype Declaration */
व्योम lbtf_set_mac_control(काष्ठा lbtf_निजी *priv);

पूर्णांक lbtf_मुक्त_cmd_buffer(काष्ठा lbtf_निजी *priv);

पूर्णांक lbtf_allocate_cmd_buffer(काष्ठा lbtf_निजी *priv);
पूर्णांक lbtf_execute_next_command(काष्ठा lbtf_निजी *priv);
पूर्णांक lbtf_set_radio_control(काष्ठा lbtf_निजी *priv);
पूर्णांक lbtf_update_hw_spec(काष्ठा lbtf_निजी *priv);
पूर्णांक lbtf_cmd_set_mac_multicast_addr(काष्ठा lbtf_निजी *priv);
व्योम lbtf_set_mode(काष्ठा lbtf_निजी *priv, क्रमागत lbtf_mode mode);
व्योम lbtf_set_bssid(काष्ठा lbtf_निजी *priv, bool activate, स्थिर u8 *bssid);
पूर्णांक lbtf_set_mac_address(काष्ठा lbtf_निजी *priv, uपूर्णांक8_t *mac_addr);

पूर्णांक lbtf_set_channel(काष्ठा lbtf_निजी *priv, u8 channel);

पूर्णांक lbtf_beacon_set(काष्ठा lbtf_निजी *priv, काष्ठा sk_buff *beacon);
पूर्णांक lbtf_beacon_ctrl(काष्ठा lbtf_निजी *priv, bool beacon_enable,
		     पूर्णांक beacon_पूर्णांक);


पूर्णांक lbtf_process_rx_command(काष्ठा lbtf_निजी *priv);
व्योम lbtf_complete_command(काष्ठा lbtf_निजी *priv, काष्ठा cmd_ctrl_node *cmd,
			  पूर्णांक result);
व्योम lbtf_cmd_response_rx(काष्ठा lbtf_निजी *priv);

/* मुख्य.c */
काष्ठा chan_freq_घातer *lbtf_get_region_cfp_table(u8 region,
	पूर्णांक *cfp_no);
काष्ठा lbtf_निजी *lbtf_add_card(व्योम *card, काष्ठा device *dmdev,
				   स्थिर काष्ठा lbtf_ops *ops);
पूर्णांक lbtf_हटाओ_card(काष्ठा lbtf_निजी *priv);
पूर्णांक lbtf_start_card(काष्ठा lbtf_निजी *priv);
पूर्णांक lbtf_rx(काष्ठा lbtf_निजी *priv, काष्ठा sk_buff *skb);
व्योम lbtf_send_tx_feedback(काष्ठा lbtf_निजी *priv, u8 retrycnt, u8 fail);
व्योम lbtf_bcn_sent(काष्ठा lbtf_निजी *priv);

/* support functions क्रम cmd.c */
/* lbtf_cmd() infers the size of the buffer to copy data back पूर्णांकo, from
   the size of the target of the poपूर्णांकer. Since the command to be sent
   may often be smaller, that size is set in cmd->size by the caller.*/
#घोषणा lbtf_cmd(priv, cmdnr, cmd, cb, cb_arg)	(अणु		\
	uपूर्णांक16_t __sz = le16_to_cpu((cmd)->hdr.size);		\
	(cmd)->hdr.size = cpu_to_le16(माप(*(cmd)));		\
	__lbtf_cmd(priv, cmdnr, &(cmd)->hdr, __sz, cb, cb_arg);	\
पूर्ण)

#घोषणा lbtf_cmd_with_response(priv, cmdnr, cmd)	\
	lbtf_cmd(priv, cmdnr, cmd, lbtf_cmd_copyback, (अचिन्हित दीर्घ) (cmd))

व्योम lbtf_cmd_async(काष्ठा lbtf_निजी *priv, uपूर्णांक16_t command,
	काष्ठा cmd_header *in_cmd, पूर्णांक in_cmd_size);

पूर्णांक __lbtf_cmd(काष्ठा lbtf_निजी *priv, uपूर्णांक16_t command,
	      काष्ठा cmd_header *in_cmd, पूर्णांक in_cmd_size,
	      पूर्णांक (*callback)(काष्ठा lbtf_निजी *, अचिन्हित दीर्घ,
			      काष्ठा cmd_header *),
	      अचिन्हित दीर्घ callback_arg);

पूर्णांक lbtf_cmd_copyback(काष्ठा lbtf_निजी *priv, अचिन्हित दीर्घ extra,
		     काष्ठा cmd_header *resp);
