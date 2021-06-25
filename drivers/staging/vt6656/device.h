<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * File: device.h
 *
 * Purpose: MAC Data काष्ठाure
 *
 * Author: Tevin Chen
 *
 * Date: Mar 17, 1997
 *
 */

#अगर_अघोषित __DEVICE_H__
#घोषणा __DEVICE_H__

#समावेश <linux/bits.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/firmware.h>
#समावेश <linux/suspend.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/wireless.h>
#समावेश <linux/समयr.h>
#समावेश <linux/usb.h>
#समावेश <linux/crc32.h>
#समावेश <net/mac80211.h>

#अगर_घोषित SIOCETHTOOL
#घोषणा DEVICE_ETHTOOL_IOCTL_SUPPORT
#समावेश <linux/ethtool.h>
#अन्यथा
#अघोषित DEVICE_ETHTOOL_IOCTL_SUPPORT
#पूर्ण_अगर

#घोषणा RATE_1M		0
#घोषणा RATE_2M		1
#घोषणा RATE_5M		2
#घोषणा RATE_11M	3
#घोषणा RATE_6M		4
#घोषणा RATE_9M		5
#घोषणा RATE_12M	6
#घोषणा RATE_18M	7
#घोषणा RATE_24M	8
#घोषणा RATE_36M	9
#घोषणा RATE_48M	10
#घोषणा RATE_54M	11
#घोषणा RATE_AUTO	12

#घोषणा MAX_RATE			12
#घोषणा VNT_B_RATES	(BIT(RATE_1M) | BIT(RATE_2M) |\
			BIT(RATE_5M) | BIT(RATE_11M))

/*
 * device specअगरic
 */

#समावेश "wcmd.h"
#समावेश "desc.h"
#समावेश "key.h"
#समावेश "card.h"

#घोषणा VNT_USB_VENDOR_ID                     0x160a
#घोषणा VNT_USB_PRODUCT_ID                    0x3184

#घोषणा DEVICE_NAME			"vt6656"
#घोषणा DEVICE_FULL_DRV_NAM		"VIA Networking Wireless LAN USB Driver"

#घोषणा DEVICE_VERSION			"mac80211"

#घोषणा FIRMWARE_VERSION		0x133		/* version 1.51 */
#घोषणा FIRMWARE_NAME			"vntwusb.fw"
#घोषणा FIRMWARE_CHUNK_SIZE		0x400

#घोषणा CONFIG_PATH			"/etc/vntconfiguration.dat"

#घोषणा MAX_UINTS			8
#घोषणा OPTION_DEFAULT			अणु [0 ... MAX_UINTS - 1] = -1पूर्ण

#घोषणा DUPLICATE_RX_CACHE_LENGTH       5

#घोषणा AUTO_FB_NONE            0
#घोषणा AUTO_FB_0               1
#घोषणा AUTO_FB_1               2

#घोषणा FB_RATE0                0
#घोषणा FB_RATE1                1

/* Antenna Mode */
#घोषणा ANT_A                   0
#घोषणा ANT_B                   1
#घोषणा ANT_DIVERSITY           2
#घोषणा ANT_RXD_TXA             3
#घोषणा ANT_RXD_TXB             4
#घोषणा ANT_UNKNOWN             0xFF
#घोषणा ANT_TXA                 0
#घोषणा ANT_TXB                 1
#घोषणा ANT_RXA                 2
#घोषणा ANT_RXB                 3

#घोषणा BB_VGA_LEVEL            4
#घोषणा BB_VGA_CHANGE_THRESHOLD 3

#घोषणा EEP_MAX_CONTEXT_SIZE    256

/* Contents in the EEPROM */
#घोषणा EEP_OFS_PAR		0x0
#घोषणा EEP_OFS_ANTENNA		0x17
#घोषणा EEP_OFS_RADIOCTL	0x18
#घोषणा EEP_OFS_RFTYPE		0x1b
#घोषणा EEP_OFS_MINCHANNEL	0x1c
#घोषणा EEP_OFS_MAXCHANNEL	0x1d
#घोषणा EEP_OFS_SIGNATURE	0x1e
#घोषणा EEP_OFS_ZONETYPE	0x1f
#घोषणा EEP_OFS_RFTABLE		0x20
#घोषणा EEP_OFS_PWR_CCK		0x20
#घोषणा EEP_OFS_SETPT_CCK	0x21
#घोषणा EEP_OFS_PWR_OFDMG	0x23

#घोषणा EEP_OFS_CALIB_TX_IQ	0x24
#घोषणा EEP_OFS_CALIB_TX_DC	0x25
#घोषणा EEP_OFS_CALIB_RX_IQ	0x26

#घोषणा EEP_OFS_MAJOR_VER	0x2e
#घोषणा EEP_OFS_MINOR_VER	0x2f

#घोषणा EEP_OFS_CCK_PWR_TBL	0x30
#घोषणा EEP_OFS_OFDM_PWR_TBL	0x40
#घोषणा EEP_OFS_OFDMA_PWR_TBL	0x50

/* Bits in EEP_OFS_ANTENNA */
#घोषणा EEP_ANTENNA_MAIN	BIT(0)
#घोषणा EEP_ANTENNA_AUX		BIT(1)
#घोषणा EEP_ANTINV		BIT(2)

/* Bits in EEP_OFS_RADIOCTL */
#घोषणा EEP_RADIOCTL_ENABLE	BIT(7)

/* control commands */
#घोषणा MESSAGE_TYPE_READ		0x1
#घोषणा MESSAGE_TYPE_WRITE		0x0
#घोषणा MESSAGE_TYPE_LOCK_OR		0x2
#घोषणा MESSAGE_TYPE_LOCK_AND		0x3
#घोषणा MESSAGE_TYPE_WRITE_MASK		0x4
#घोषणा MESSAGE_TYPE_CARDINIT		0x5
#घोषणा MESSAGE_TYPE_INIT_RSP		0x6
#घोषणा MESSAGE_TYPE_MACSHUTDOWN	0x7
#घोषणा MESSAGE_TYPE_SETKEY		0x8
#घोषणा MESSAGE_TYPE_CLRKEYENTRY	0x9
#घोषणा MESSAGE_TYPE_WRITE_MISCFF	0xa
#घोषणा MESSAGE_TYPE_SET_ANTMD		0xb
#घोषणा MESSAGE_TYPE_SELECT_CHANNEL	0xc
#घोषणा MESSAGE_TYPE_SET_TSFTBTT	0xd
#घोषणा MESSAGE_TYPE_SET_SSTIFS		0xe
#घोषणा MESSAGE_TYPE_CHANGE_BBTYPE	0xf
#घोषणा MESSAGE_TYPE_DISABLE_PS		0x10
#घोषणा MESSAGE_TYPE_WRITE_IFRF		0x11

/* command पढ़ो/ग_लिखो(index) */
#घोषणा MESSAGE_REQUEST_MEM		0x1
#घोषणा MESSAGE_REQUEST_BBREG		0x2
#घोषणा MESSAGE_REQUEST_MACREG		0x3
#घोषणा MESSAGE_REQUEST_EEPROM		0x4
#घोषणा MESSAGE_REQUEST_TSF		0x5
#घोषणा MESSAGE_REQUEST_TBTT		0x6
#घोषणा MESSAGE_REQUEST_BBAGC		0x7
#घोषणा MESSAGE_REQUEST_VERSION		0x8
#घोषणा MESSAGE_REQUEST_RF_INIT		0x9
#घोषणा MESSAGE_REQUEST_RF_INIT2	0xa
#घोषणा MESSAGE_REQUEST_RF_CH0		0xb
#घोषणा MESSAGE_REQUEST_RF_CH1		0xc
#घोषणा MESSAGE_REQUEST_RF_CH2		0xd

/* USB रेजिस्टरs */
#घोषणा USB_REG4			0x604

#घोषणा DEVICE_INIT_COLD	0x0 /* cold init */
#घोषणा DEVICE_INIT_RESET	0x1 /* reset init or Dx to D0 घातer reमुख्य */
#घोषणा DEVICE_INIT_DXPL	0x2 /* Dx to D0 घातer lost init */

/* Device init */
काष्ठा vnt_cmd_card_init अणु
	u8 init_class;
	u8 exist_sw_net_addr;
	u8 sw_net_addr[6];
	u8 लघु_retry_limit;
	u8 दीर्घ_retry_limit;
पूर्ण;

काष्ठा vnt_rsp_card_init अणु
	u8 status;
	u8 net_addr[6];
	u8 rf_type;
	u8 min_channel;
	u8 max_channel;
पूर्ण;

/* USB */

/*
 * Enum of context types क्रम SendPacket
 */
क्रमागत अणु
	CONTEXT_DATA_PACKET = 0,
	CONTEXT_BEACON_PACKET
पूर्ण;

काष्ठा vnt_rx_header अणु
	u32 wbk_status;
	u8 rx_sts;
	u8 rx_rate;
	u16 pay_load_len;
पूर्ण __packed;

काष्ठा vnt_rx_tail अणु
	__le64 tsf_समय;
	u8 sq;
	u8 new_rsr;
	u8 rssi;
	u8 rsr;
	u8 sq_3;
पूर्ण __packed;

/* RCB (Receive Control Block) */
काष्ठा vnt_rcb अणु
	व्योम *priv;
	काष्ठा urb *urb;
	काष्ठा sk_buff *skb;
पूर्ण;

/* used to track bulk out irps */
काष्ठा vnt_usb_send_context अणु
	व्योम *priv;
	काष्ठा sk_buff *skb;
	व्योम *tx_buffer;
	u32 frame_len;
	u16 tx_hdr_size;
	u16 tx_rate;
	u8 type;
	u8 pkt_no;
	u8 pkt_type;
	bool in_use;
पूर्ण;

/*
 * Structure to keep track of USB पूर्णांकerrupt packets
 */
काष्ठा vnt_पूर्णांकerrupt_buffer अणु
	u8 *data_buf;
पूर्ण;

/* flags क्रम options */
#घोषणा DEVICE_FLAGS_UNPLUG		0
#घोषणा DEVICE_FLAGS_DISCONNECTED	1

काष्ठा vnt_निजी अणु
	/* mac80211 */
	काष्ठा ieee80211_hw *hw;
	काष्ठा ieee80211_vअगर *vअगर;
	u8 mac_hw;
	/* netdev */
	काष्ठा usb_device *usb;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;

	u64 tsf_समय;

	u32 rx_buf_sz;
	पूर्णांक mc_list_count;

	spinlock_t lock;
	काष्ठा mutex usb_lock;

	अचिन्हित दीर्घ flags;

	/* USB */
	काष्ठा urb *पूर्णांकerrupt_urb;
	u32 पूर्णांक_पूर्णांकerval;

	/* Variables to track resources क्रम the BULK In Pipe */
	काष्ठा vnt_rcb *rcb[CB_MAX_RX_DESC];
	u32 num_rcb;

	/* Variables to track resources क्रम the BULK Out Pipe */
	काष्ठा vnt_usb_send_context *tx_context[CB_MAX_TX_DESC];
	काष्ठा usb_anchor tx_submitted;
	u32 num_tx_context;

	/* Variables to track resources क्रम the Interrupt In Pipe */
	काष्ठा vnt_पूर्णांकerrupt_buffer पूर्णांक_buf;

	/* Version control */
	u16 firmware_version;
	u8 local_id;
	u8 rf_type;
	u8 bb_rx_conf;

	काष्ठा vnt_cmd_card_init init_command;
	काष्ठा vnt_rsp_card_init init_response;
	u8 current_net_addr[ETH_ALEN] __aligned(2);
	u8 permanent_net_addr[ETH_ALEN] __aligned(2);

	u8 exist_sw_net_addr;

	u64 current_tsf;

	/* 802.11 MAC specअगरic */
	u32 current_rssi;

	/* Antenna Diversity */
	पूर्णांक tx_rx_ant_inv;
	u32 rx_antenna_sel;
	u8 rx_antenna_mode;
	u8 tx_antenna_mode;
	u8 radio_ctl;

	/* IFS & Cw */
	u32 sअगरs;  /* Current SIFS */
	u32 dअगरs;  /* Current DIFS */
	u32 eअगरs;  /* Current EIFS */
	u32 slot;  /* Current SlotTime */

	/* Rate */
	u8 bb_type; /* 0: 11A, 1:11B, 2:11G */
	u8 packet_type; /* 0:11a 1:11b 2:11gb 3:11ga */
	u32 basic_rates;
	u8 top_ofdm_basic_rate;
	u8 top_cck_basic_rate;

	u8 eeprom[EEP_MAX_CONTEXT_SIZE];  /*u32 alignment */

	u8 preamble_type;

	/* For RF Power table */
	u8 cck_pwr;
	u8 ofdm_pwr_g;
	u8 ofdm_pwr_a;
	u8 घातer;
	u8 cck_pwr_tbl[14];
	u8 ofdm_pwr_tbl[14];
	u8 ofdm_a_pwr_tbl[42];

	u16 tx_rate_fb0;
	u16 tx_rate_fb1;

	क्रमागत nl80211_अगरtype op_mode;

	पूर्णांक लघु_slot_समय;

	/* Power save */
	u16 current_aid;

	/* Beacon related */
	u16 seq_counter;

	क्रमागत vnt_cmd_state command_state;

	क्रमागत vnt_cmd command;

	/* 802.11 counter */

	क्रमागत vnt_cmd cmd_queue[CMD_Q_SIZE];
	u32 cmd_dequeue_idx;
	u32 cmd_enqueue_idx;
	u32 मुक्त_cmd_queue;
	पूर्णांक cmd_running;

	अचिन्हित दीर्घ key_entry_inuse;

	u8 स्वतः_fb_ctrl;

	/* For Update BaseBand VGA Gain Offset */
	u8 bb_vga[BB_VGA_LEVEL];

	u8 bb_pre_ed_rssi;
	u8 bb_pre_ed_index;

	/* command समयr */
	काष्ठा delayed_work run_command_work;

	काष्ठा ieee80211_low_level_stats low_stats;
पूर्ण;

#घोषणा ADD_ONE_WITH_WRAP_AROUND(uVar, uModulo) अणु	\
	अगर ((uVar) >= ((uModulo) - 1))			\
		(uVar) = 0;				\
	अन्यथा						\
		(uVar)++;				\
पूर्ण

पूर्णांक vnt_init(काष्ठा vnt_निजी *priv);

#पूर्ण_अगर
