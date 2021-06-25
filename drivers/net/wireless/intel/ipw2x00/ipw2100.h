<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/******************************************************************************

  Copyright(c) 2003 - 2006 Intel Corporation. All rights reserved.


  Contact Inक्रमmation:
  Intel Linux Wireless <ilw@linux.पूर्णांकel.com>
  Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497

******************************************************************************/
#अगर_अघोषित _IPW2100_H
#घोषणा _IPW2100_H

#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/list.h>
#समावेश <linux/delay.h>
#समावेश <linux/skbuff.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/socket.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/wireless.h>
#समावेश <net/iw_handler.h>	// new driver API

#अगर_घोषित CONFIG_IPW2100_MONITOR
#समावेश <net/ieee80211_radiotap.h>
#पूर्ण_अगर

#समावेश <linux/workqueue.h>
#समावेश <linux/mutex.h>

#समावेश "libipw.h"

काष्ठा ipw2100_priv;
काष्ठा ipw2100_tx_packet;
काष्ठा ipw2100_rx_packet;

#घोषणा IPW_DL_UNINIT    0x80000000
#घोषणा IPW_DL_NONE      0x00000000
#घोषणा IPW_DL_ALL       0x7FFFFFFF

/*
 * To use the debug प्रणाली;
 *
 * If you are defining a new debug classअगरication, simply add it to the #घोषणा
 * list here in the क्रमm of:
 *
 * #घोषणा IPW_DL_xxxx VALUE
 *
 * shअगरting value to the left one bit from the previous entry.  xxxx should be
 * the name of the classअगरication (क्रम example, WEP)
 *
 * You then need to either add a IPW2100_xxxx_DEBUG() macro definition क्रम your
 * classअगरication, or use IPW_DEBUG(IPW_DL_xxxx, ...) whenever you want
 * to send output to that classअगरication.
 *
 * To add your debug level to the list of levels seen when you perक्रमm
 *
 * % cat /proc/net/ipw2100/debug_level
 *
 * you simply need to add your entry to the ipw2100_debug_levels array.
 *
 * If you करो not see debug_level in /proc/net/ipw2100 then you करो not have
 * CONFIG_IPW2100_DEBUG defined in your kernel configuration
 *
 */

#घोषणा IPW_DL_ERROR         (1<<0)
#घोषणा IPW_DL_WARNING       (1<<1)
#घोषणा IPW_DL_INFO          (1<<2)
#घोषणा IPW_DL_WX            (1<<3)
#घोषणा IPW_DL_HC            (1<<5)
#घोषणा IPW_DL_STATE         (1<<6)

#घोषणा IPW_DL_NOTIF         (1<<10)
#घोषणा IPW_DL_SCAN          (1<<11)
#घोषणा IPW_DL_ASSOC         (1<<12)
#घोषणा IPW_DL_DROP          (1<<13)

#घोषणा IPW_DL_IOCTL         (1<<14)
#घोषणा IPW_DL_RF_KILL       (1<<17)

#घोषणा IPW_DL_MANAGE        (1<<15)
#घोषणा IPW_DL_FW            (1<<16)

#घोषणा IPW_DL_FRAG          (1<<21)
#घोषणा IPW_DL_WEP           (1<<22)
#घोषणा IPW_DL_TX            (1<<23)
#घोषणा IPW_DL_RX            (1<<24)
#घोषणा IPW_DL_ISR           (1<<25)
#घोषणा IPW_DL_IO            (1<<26)
#घोषणा IPW_DL_TRACE         (1<<28)

#घोषणा IPW_DEBUG_ERROR(f, a...) prपूर्णांकk(KERN_ERR DRV_NAME ": " f, ## a)
#घोषणा IPW_DEBUG_WARNING(f, a...) prपूर्णांकk(KERN_WARNING DRV_NAME ": " f, ## a)
#घोषणा IPW_DEBUG_INFO(f...)    IPW_DEBUG(IPW_DL_INFO, ## f)
#घोषणा IPW_DEBUG_WX(f...)     IPW_DEBUG(IPW_DL_WX, ## f)
#घोषणा IPW_DEBUG_SCAN(f...)   IPW_DEBUG(IPW_DL_SCAN, ## f)
#घोषणा IPW_DEBUG_NOTIF(f...) IPW_DEBUG(IPW_DL_NOTIF, ## f)
#घोषणा IPW_DEBUG_TRACE(f...)  IPW_DEBUG(IPW_DL_TRACE, ## f)
#घोषणा IPW_DEBUG_RX(f...)     IPW_DEBUG(IPW_DL_RX, ## f)
#घोषणा IPW_DEBUG_TX(f...)     IPW_DEBUG(IPW_DL_TX, ## f)
#घोषणा IPW_DEBUG_ISR(f...)    IPW_DEBUG(IPW_DL_ISR, ## f)
#घोषणा IPW_DEBUG_MANAGEMENT(f...) IPW_DEBUG(IPW_DL_MANAGE, ## f)
#घोषणा IPW_DEBUG_WEP(f...)    IPW_DEBUG(IPW_DL_WEP, ## f)
#घोषणा IPW_DEBUG_HC(f...) IPW_DEBUG(IPW_DL_HC, ## f)
#घोषणा IPW_DEBUG_FRAG(f...) IPW_DEBUG(IPW_DL_FRAG, ## f)
#घोषणा IPW_DEBUG_FW(f...) IPW_DEBUG(IPW_DL_FW, ## f)
#घोषणा IPW_DEBUG_RF_KILL(f...) IPW_DEBUG(IPW_DL_RF_KILL, ## f)
#घोषणा IPW_DEBUG_DROP(f...) IPW_DEBUG(IPW_DL_DROP, ## f)
#घोषणा IPW_DEBUG_IO(f...) IPW_DEBUG(IPW_DL_IO, ## f)
#घोषणा IPW_DEBUG_IOCTL(f...) IPW_DEBUG(IPW_DL_IOCTL, ## f)
#घोषणा IPW_DEBUG_STATE(f, a...) IPW_DEBUG(IPW_DL_STATE | IPW_DL_ASSOC | IPW_DL_INFO, f, ## a)
#घोषणा IPW_DEBUG_ASSOC(f, a...) IPW_DEBUG(IPW_DL_ASSOC | IPW_DL_INFO, f, ## a)

क्रमागत अणु
	IPW_HW_STATE_DISABLED = 1,
	IPW_HW_STATE_ENABLED = 0
पूर्ण;

बाह्य स्थिर अक्षर *port_type_str[];
बाह्य स्थिर अक्षर *band_str[];

#घोषणा NUMBER_OF_BD_PER_COMMAND_PACKET		1
#घोषणा NUMBER_OF_BD_PER_DATA_PACKET		2

#घोषणा IPW_MAX_BDS 6
#घोषणा NUMBER_OF_OVERHEAD_BDS_PER_PACKETR	2
#घोषणा NUMBER_OF_BDS_TO_LEAVE_FOR_COMMANDS	1

#घोषणा REQUIRED_SPACE_IN_RING_FOR_COMMAND_PACKET \
    (IPW_BD_QUEUE_W_R_MIN_SPARE + NUMBER_OF_BD_PER_COMMAND_PACKET)

काष्ठा bd_status अणु
	जोड़ अणु
		काष्ठा अणु
			u8 nlf:1, txType:2, पूर्णांकEnabled:1, reserved:4;
		पूर्ण fields;
		u8 field;
	पूर्ण info;
पूर्ण __packed;

काष्ठा ipw2100_bd अणु
	u32 host_addr;
	u32 buf_length;
	काष्ठा bd_status status;
	/* number of fragments क्रम frame (should be set only क्रम
	 * 1st TBD) */
	u8 num_fragments;
	u8 reserved[6];
पूर्ण __packed;

#घोषणा IPW_BD_QUEUE_LENGTH(n) (1<<n)
#घोषणा IPW_BD_ALIGNMENT(L)    (L*माप(काष्ठा ipw2100_bd))

#घोषणा IPW_BD_STATUS_TX_FRAME_802_3             0x00
#घोषणा IPW_BD_STATUS_TX_FRAME_NOT_LAST_FRAGMENT 0x01
#घोषणा IPW_BD_STATUS_TX_FRAME_COMMAND		 0x02
#घोषणा IPW_BD_STATUS_TX_FRAME_802_11	         0x04
#घोषणा IPW_BD_STATUS_TX_INTERRUPT_ENABLE	 0x08

काष्ठा ipw2100_bd_queue अणु
	/* driver (भव) poपूर्णांकer to queue */
	काष्ठा ipw2100_bd *drv;

	/* firmware (physical) poपूर्णांकer to queue */
	dma_addr_t nic;

	/* Length of phy memory allocated क्रम BDs */
	u32 size;

	/* Number of BDs in queue (and in array) */
	u32 entries;

	/* Number of available BDs (invalid क्रम NIC BDs) */
	u32 available;

	/* Offset of oldest used BD in array (next one to
	 * check क्रम completion) */
	u32 oldest;

	/* Offset of next available (unused) BD */
	u32 next;
पूर्ण;

#घोषणा RX_QUEUE_LENGTH 256
#घोषणा TX_QUEUE_LENGTH 256
#घोषणा HW_QUEUE_LENGTH 256

#घोषणा TX_PENDED_QUEUE_LENGTH (TX_QUEUE_LENGTH / NUMBER_OF_BD_PER_DATA_PACKET)

#घोषणा STATUS_TYPE_MASK	0x0000000f
#घोषणा COMMAND_STATUS_VAL	0
#घोषणा STATUS_CHANGE_VAL	1
#घोषणा P80211_DATA_VAL 	2
#घोषणा P8023_DATA_VAL		3
#घोषणा HOST_NOTIFICATION_VAL	4

#घोषणा IPW2100_RSSI_TO_DBM (-98)

काष्ठा ipw2100_status अणु
	u32 frame_size;
	u16 status_fields;
	u8 flags;
#घोषणा IPW_STATUS_FLAG_DECRYPTED	(1<<0)
#घोषणा IPW_STATUS_FLAG_WEP_ENCRYPTED	(1<<1)
#घोषणा IPW_STATUS_FLAG_CRC_ERROR       (1<<2)
	u8 rssi;
पूर्ण __packed;

काष्ठा ipw2100_status_queue अणु
	/* driver (भव) poपूर्णांकer to queue */
	काष्ठा ipw2100_status *drv;

	/* firmware (physical) poपूर्णांकer to queue */
	dma_addr_t nic;

	/* Length of phy memory allocated क्रम BDs */
	u32 size;
पूर्ण;

#घोषणा HOST_COMMAND_PARAMS_REG_LEN	100
#घोषणा CMD_STATUS_PARAMS_REG_LEN 	3

#घोषणा IPW_WPA_CAPABILITIES   0x1
#घोषणा IPW_WPA_LISTENINTERVAL 0x2
#घोषणा IPW_WPA_AP_ADDRESS     0x4

#घोषणा IPW_MAX_VAR_IE_LEN ((HOST_COMMAND_PARAMS_REG_LEN - 4) * माप(u32))

काष्ठा ipw2100_wpa_assoc_frame अणु
	u16 fixed_ie_mask;
	काष्ठा अणु
		u16 capab_info;
		u16 listen_पूर्णांकerval;
		u8 current_ap[ETH_ALEN];
	पूर्ण fixed_ies;
	u32 var_ie_len;
	u8 var_ie[IPW_MAX_VAR_IE_LEN];
पूर्ण;

#घोषणा IPW_BSS     1
#घोषणा IPW_MONITOR 2
#घोषणा IPW_IBSS    3

/**
 * @काष्ठा _tx_cmd - HWCommand
 * @brief H/W command काष्ठाure.
 */
काष्ठा ipw2100_cmd_header अणु
	u32 host_command_reg;
	u32 host_command_reg1;
	u32 sequence;
	u32 host_command_len_reg;
	u32 host_command_params_reg[HOST_COMMAND_PARAMS_REG_LEN];
	u32 cmd_status_reg;
	u32 cmd_status_params_reg[CMD_STATUS_PARAMS_REG_LEN];
	u32 rxq_base_ptr;
	u32 rxq_next_ptr;
	u32 rxq_host_ptr;
	u32 txq_base_ptr;
	u32 txq_next_ptr;
	u32 txq_host_ptr;
	u32 tx_status_reg;
	u32 reserved;
	u32 status_change_reg;
	u32 reserved1[3];
	u32 *ordinal1_ptr;
	u32 *ordinal2_ptr;
पूर्ण __packed;

काष्ठा ipw2100_data_header अणु
	u32 host_command_reg;
	u32 host_command_reg1;
	u8 encrypted;		// BOOLEAN in win! TRUE अगर frame is enc by driver
	u8 needs_encryption;	// BOOLEAN in win! TRUE अगर frma need to be enc in NIC
	u8 wep_index;		// 0 no key, 1-4 key index, 0xff immediate key
	u8 key_size;		// 0 no imm key, 0x5 64bit encr, 0xd 128bit encr, 0x10 128bit encr and 128bit IV
	u8 key[16];
	u8 reserved[10];	// f/w reserved
	u8 src_addr[ETH_ALEN];
	u8 dst_addr[ETH_ALEN];
	u16 fragment_size;
पूर्ण __packed;

/* Host command data काष्ठाure */
काष्ठा host_command अणु
	u32 host_command;	// COMMAND ID
	u32 host_command1;	// COMMAND ID
	u32 host_command_sequence;	// UNIQUE COMMAND NUMBER (ID)
	u32 host_command_length;	// LENGTH
	u32 host_command_parameters[HOST_COMMAND_PARAMS_REG_LEN];	// COMMAND PARAMETERS
पूर्ण __packed;

प्रकार क्रमागत अणु
	POWER_ON_RESET,
	EXIT_POWER_DOWN_RESET,
	SW_RESET,
	EEPROM_RW,
	SW_RE_INIT
पूर्ण ipw2100_reset_event;

क्रमागत अणु
	COMMAND = 0xCAFE,
	DATA,
	RX
पूर्ण;

काष्ठा ipw2100_tx_packet अणु
	पूर्णांक type;
	पूर्णांक index;
	जोड़ अणु
		काष्ठा अणु	/* COMMAND */
			काष्ठा ipw2100_cmd_header *cmd;
			dma_addr_t cmd_phys;
		पूर्ण c_काष्ठा;
		काष्ठा अणु	/* DATA */
			काष्ठा ipw2100_data_header *data;
			dma_addr_t data_phys;
			काष्ठा libipw_txb *txb;
		पूर्ण d_काष्ठा;
	पूर्ण info;
	पूर्णांक jअगरfy_start;

	काष्ठा list_head list;
पूर्ण;

काष्ठा ipw2100_rx_packet अणु
	काष्ठा ipw2100_rx *rxp;
	dma_addr_t dma_addr;
	पूर्णांक jअगरfy_start;
	काष्ठा sk_buff *skb;
	काष्ठा list_head list;
पूर्ण;

#घोषणा FRAG_DISABLED             (1<<31)
#घोषणा RTS_DISABLED              (1<<31)
#घोषणा MAX_RTS_THRESHOLD         2304U
#घोषणा MIN_RTS_THRESHOLD         1U
#घोषणा DEFAULT_RTS_THRESHOLD     1000U

#घोषणा DEFAULT_BEACON_INTERVAL   100U
#घोषणा	DEFAULT_SHORT_RETRY_LIMIT 7U
#घोषणा	DEFAULT_LONG_RETRY_LIMIT  4U

काष्ठा ipw2100_ordinals अणु
	u32 table1_addr;
	u32 table2_addr;
	u32 table1_size;
	u32 table2_size;
पूर्ण;

/* Host Notअगरication header */
काष्ठा ipw2100_notअगरication अणु
	u32 hnhdr_subtype;	/* type of host notअगरication */
	u32 hnhdr_size;		/* size in bytes of data
				   or number of entries, अगर table.
				   Does NOT include header */
पूर्ण __packed;

#घोषणा MAX_KEY_SIZE	16
#घोषणा	MAX_KEYS	8

#घोषणा IPW2100_WEP_ENABLE     (1<<1)
#घोषणा IPW2100_WEP_DROP_CLEAR (1<<2)

#घोषणा IPW_NONE_CIPHER   (1<<0)
#घोषणा IPW_WEP40_CIPHER  (1<<1)
#घोषणा IPW_TKIP_CIPHER   (1<<2)
#घोषणा IPW_CCMP_CIPHER   (1<<4)
#घोषणा IPW_WEP104_CIPHER (1<<5)
#घोषणा IPW_CKIP_CIPHER   (1<<6)

#घोषणा	IPW_AUTH_OPEN     	0
#घोषणा	IPW_AUTH_SHARED   	1
#घोषणा IPW_AUTH_LEAP	  	2
#घोषणा IPW_AUTH_LEAP_CISCO_ID	0x80

काष्ठा statistic अणु
	पूर्णांक value;
	पूर्णांक hi;
	पूर्णांक lo;
पूर्ण;

#घोषणा INIT_STAT(x) करो अणु  \
  (x)->value = (x)->hi = 0; \
  (x)->lo = 0x7fffffff; \
पूर्ण जबतक (0)
#घोषणा SET_STAT(x,y) करो अणु \
  (x)->value = y; \
  अगर ((x)->value > (x)->hi) (x)->hi = (x)->value; \
  अगर ((x)->value < (x)->lo) (x)->lo = (x)->value; \
पूर्ण जबतक (0)
#घोषणा INC_STAT(x) करो अणु अगर (++(x)->value > (x)->hi) (x)->hi = (x)->value; पूर्ण \
जबतक (0)
#घोषणा DEC_STAT(x) करो अणु अगर (--(x)->value < (x)->lo) (x)->lo = (x)->value; पूर्ण \
जबतक (0)

#घोषणा IPW2100_ERROR_QUEUE 5

/* Power management code: enable or disable? */
क्रमागत अणु
#अगर_घोषित CONFIG_PM
	IPW2100_PM_DISABLED = 0,
	PM_STATE_SIZE = 16,
#अन्यथा
	IPW2100_PM_DISABLED = 1,
	PM_STATE_SIZE = 0,
#पूर्ण_अगर
पूर्ण;

#घोषणा STATUS_POWERED          (1<<0)
#घोषणा STATUS_CMD_ACTIVE       (1<<1)	/**< host command in progress */
#घोषणा STATUS_RUNNING          (1<<2)	/* Card initialized, but not enabled */
#घोषणा STATUS_ENABLED          (1<<3)	/* Card enabled -- can scan,Tx,Rx */
#घोषणा STATUS_STOPPING         (1<<4)	/* Card is in shutकरोwn phase */
#घोषणा STATUS_INITIALIZED      (1<<5)	/* Card is पढ़ोy क्रम बाह्यal calls */
#घोषणा STATUS_ASSOCIATING      (1<<9)	/* Associated, but no BSSID yet */
#घोषणा STATUS_ASSOCIATED       (1<<10)	/* Associated and BSSID valid */
#घोषणा STATUS_INT_ENABLED      (1<<11)
#घोषणा STATUS_RF_KILL_HW       (1<<12)
#घोषणा STATUS_RF_KILL_SW       (1<<13)
#घोषणा STATUS_RF_KILL_MASK     (STATUS_RF_KILL_HW | STATUS_RF_KILL_SW)
#घोषणा STATUS_EXIT_PENDING     (1<<14)

#घोषणा STATUS_SCAN_PENDING     (1<<23)
#घोषणा STATUS_SCANNING         (1<<24)
#घोषणा STATUS_SCAN_ABORTING    (1<<25)
#घोषणा STATUS_SCAN_COMPLETE    (1<<26)
#घोषणा STATUS_WX_EVENT_PENDING (1<<27)
#घोषणा STATUS_RESET_PENDING    (1<<29)
#घोषणा STATUS_SECURITY_UPDATED (1<<30)	/* Security sync needed */

/* Internal NIC states */
#घोषणा IPW_STATE_INITIALIZED	(1<<0)
#घोषणा IPW_STATE_COUNTRY_FOUND	(1<<1)
#घोषणा IPW_STATE_ASSOCIATED    (1<<2)
#घोषणा IPW_STATE_ASSN_LOST	(1<<3)
#घोषणा IPW_STATE_ASSN_CHANGED 	(1<<4)
#घोषणा IPW_STATE_SCAN_COMPLETE	(1<<5)
#घोषणा IPW_STATE_ENTERED_PSP 	(1<<6)
#घोषणा IPW_STATE_LEFT_PSP 	(1<<7)
#घोषणा IPW_STATE_RF_KILL       (1<<8)
#घोषणा IPW_STATE_DISABLED	(1<<9)
#घोषणा IPW_STATE_POWER_DOWN	(1<<10)
#घोषणा IPW_STATE_SCANNING      (1<<11)

#घोषणा CFG_STATIC_CHANNEL      (1<<0)	/* Restrict assoc. to single channel */
#घोषणा CFG_STATIC_ESSID        (1<<1)	/* Restrict assoc. to single SSID */
#घोषणा CFG_STATIC_BSSID        (1<<2)	/* Restrict assoc. to single BSSID */
#घोषणा CFG_CUSTOM_MAC          (1<<3)
#घोषणा CFG_LONG_PREAMBLE       (1<<4)
#घोषणा CFG_ASSOCIATE           (1<<6)
#घोषणा CFG_FIXED_RATE          (1<<7)
#घोषणा CFG_ADHOC_CREATE        (1<<8)
#घोषणा CFG_PASSIVE_SCAN        (1<<10)
#अगर_घोषित CONFIG_IPW2100_MONITOR
#घोषणा CFG_CRC_CHECK           (1<<11)
#पूर्ण_अगर

#घोषणा CAP_SHARED_KEY          (1<<0)	/* Off = OPEN */
#घोषणा CAP_PRIVACY_ON          (1<<1)	/* Off = No privacy */

काष्ठा ipw2100_priv अणु
	व्योम __iomem *ioaddr;

	पूर्णांक stop_hang_check;	/* Set 1 when shutting करोwn to समाप्त hang_check */
	पूर्णांक stop_rf_समाप्त;	/* Set 1 when shutting करोwn to समाप्त rf_समाप्त */

	काष्ठा libipw_device *ieee;
	अचिन्हित दीर्घ status;
	अचिन्हित दीर्घ config;
	अचिन्हित दीर्घ capability;

	/* Statistics */
	पूर्णांक resets;
	समय64_t reset_backoff;

	/* Context */
	u8 essid[IW_ESSID_MAX_SIZE];
	u8 essid_len;
	u8 bssid[ETH_ALEN];
	u8 channel;
	पूर्णांक last_mode;

	समय64_t connect_start;
	समय64_t last_reset;

	u32 channel_mask;
	u32 fatal_error;
	u32 fatal_errors[IPW2100_ERROR_QUEUE];
	u32 fatal_index;
	पूर्णांक eeprom_version;
	पूर्णांक firmware_version;
	अचिन्हित दीर्घ hw_features;
	पूर्णांक hangs;
	u32 last_rtc;
	पूर्णांक dump_raw;		/* 1 to dump raw bytes in /sys/.../memory */
	u8 *snapshot[0x30];

	u8 mandatory_bssid_mac[ETH_ALEN];
	u8 mac_addr[ETH_ALEN];

	पूर्णांक घातer_mode;

	पूर्णांक messages_sent;

	पूर्णांक लघु_retry_limit;
	पूर्णांक दीर्घ_retry_limit;

	u32 rts_threshold;
	u32 frag_threshold;

	पूर्णांक in_isr;

	u32 tx_rates;
	पूर्णांक tx_घातer;
	u32 beacon_पूर्णांकerval;

	अक्षर nick[IW_ESSID_MAX_SIZE + 1];

	काष्ठा ipw2100_status_queue status_queue;

	काष्ठा statistic txq_stat;
	काष्ठा statistic rxq_stat;
	काष्ठा ipw2100_bd_queue rx_queue;
	काष्ठा ipw2100_bd_queue tx_queue;
	काष्ठा ipw2100_rx_packet *rx_buffers;

	काष्ठा statistic fw_pend_stat;
	काष्ठा list_head fw_pend_list;

	काष्ठा statistic msg_मुक्त_stat;
	काष्ठा statistic msg_pend_stat;
	काष्ठा list_head msg_मुक्त_list;
	काष्ठा list_head msg_pend_list;
	काष्ठा ipw2100_tx_packet *msg_buffers;

	काष्ठा statistic tx_मुक्त_stat;
	काष्ठा statistic tx_pend_stat;
	काष्ठा list_head tx_मुक्त_list;
	काष्ठा list_head tx_pend_list;
	काष्ठा ipw2100_tx_packet *tx_buffers;

	काष्ठा ipw2100_ordinals ordinals;

	काष्ठा pci_dev *pci_dev;

	काष्ठा proc_dir_entry *dir_dev;

	काष्ठा net_device *net_dev;
	काष्ठा iw_statistics wstats;

	काष्ठा iw_खुला_data wireless_data;

	काष्ठा tasklet_काष्ठा irq_tasklet;

	काष्ठा delayed_work reset_work;
	काष्ठा delayed_work security_work;
	काष्ठा delayed_work wx_event_work;
	काष्ठा delayed_work hang_check;
	काष्ठा delayed_work rf_समाप्त;
	काष्ठा delayed_work scan_event;

	पूर्णांक user_requested_scan;

	/* Track समय in suspend, using CLOCK_BOOTTIME */
	समय64_t suspend_at;
	समय64_t suspend_समय;

	u32 पूर्णांकerrupts;
	पूर्णांक tx_पूर्णांकerrupts;
	पूर्णांक rx_पूर्णांकerrupts;
	पूर्णांक पूर्णांकa_other;

	spinlock_t low_lock;
	काष्ठा mutex action_mutex;
	काष्ठा mutex adapter_mutex;

	रुको_queue_head_t रुको_command_queue;
पूर्ण;

/*********************************************************
 * Host Command -> From Driver to FW
 *********************************************************/

/**
 * Host command identअगरiers
 */
#घोषणा HOST_COMPLETE           2
#घोषणा SYSTEM_CONFIG           6
#घोषणा SSID                    8
#घोषणा MANDATORY_BSSID         9
#घोषणा AUTHENTICATION_TYPE    10
#घोषणा ADAPTER_ADDRESS        11
#घोषणा PORT_TYPE              12
#घोषणा INTERNATIONAL_MODE     13
#घोषणा CHANNEL                14
#घोषणा RTS_THRESHOLD          15
#घोषणा FRAG_THRESHOLD         16
#घोषणा POWER_MODE             17
#घोषणा TX_RATES               18
#घोषणा BASIC_TX_RATES         19
#घोषणा WEP_KEY_INFO           20
#घोषणा WEP_KEY_INDEX          25
#घोषणा WEP_FLAGS              26
#घोषणा ADD_MULTICAST          27
#घोषणा CLEAR_ALL_MULTICAST    28
#घोषणा BEACON_INTERVAL        29
#घोषणा ATIM_WINDOW            30
#घोषणा CLEAR_STATISTICS       31
#घोषणा SEND		       33
#घोषणा TX_POWER_INDEX         36
#घोषणा BROADCAST_SCAN         43
#घोषणा CARD_DISABLE           44
#घोषणा PREFERRED_BSSID        45
#घोषणा SET_SCAN_OPTIONS       46
#घोषणा SCAN_DWELL_TIME        47
#घोषणा SWEEP_TABLE            48
#घोषणा AP_OR_STATION_TABLE    49
#घोषणा GROUP_ORDINALS         50
#घोषणा SHORT_RETRY_LIMIT      51
#घोषणा LONG_RETRY_LIMIT       52

#घोषणा HOST_PRE_POWER_DOWN    58
#घोषणा CARD_DISABLE_PHY_OFF   61
#घोषणा MSDU_TX_RATES          62

/* Rogue AP Detection */
#घोषणा SET_STATION_STAT_BITS      64
#घोषणा CLEAR_STATIONS_STAT_BITS   65
#घोषणा LEAP_ROGUE_MODE            66	//TODO tbw replaced by CFG_LEAP_ROGUE_AP
#घोषणा SET_SECURITY_INFORMATION   67
#घोषणा DISASSOCIATION_BSSID	   68
#घोषणा SET_WPA_IE                 69

/* प्रणाली configuration bit mask: */
#घोषणा IPW_CFG_MONITOR               0x00004
#घोषणा IPW_CFG_PREAMBLE_AUTO        0x00010
#घोषणा IPW_CFG_IBSS_AUTO_START     0x00020
#घोषणा IPW_CFG_LOOPBACK            0x00100
#घोषणा IPW_CFG_ANSWER_BCSSID_PROBE 0x00800
#घोषणा IPW_CFG_BT_SIDEBAND_SIGNAL	0x02000
#घोषणा IPW_CFG_802_1x_ENABLE       0x04000
#घोषणा IPW_CFG_BSS_MASK		0x08000
#घोषणा IPW_CFG_IBSS_MASK		0x10000

#घोषणा IPW_SCAN_NOASSOCIATE (1<<0)
#घोषणा IPW_SCAN_MIXED_CELL (1<<1)
/* RESERVED (1<<2) */
#घोषणा IPW_SCAN_PASSIVE (1<<3)

#घोषणा IPW_NIC_FATAL_ERROR 0x2A7F0
#घोषणा IPW_ERROR_ADDR(x) (x & 0x3FFFF)
#घोषणा IPW_ERROR_CODE(x) ((x & 0xFF000000) >> 24)
#घोषणा IPW2100_ERR_C3_CORRUPTION (0x10 << 24)
#घोषणा IPW2100_ERR_MSG_TIMEOUT   (0x11 << 24)
#घोषणा IPW2100_ERR_FW_LOAD       (0x12 << 24)

#घोषणा IPW_MEM_SRAM_HOST_SHARED_LOWER_BOUND			0x200
#घोषणा IPW_MEM_SRAM_HOST_INTERRUPT_AREA_LOWER_BOUND  	IPW_MEM_SRAM_HOST_SHARED_LOWER_BOUND + 0x0D80

#घोषणा IPW_MEM_HOST_SHARED_RX_BD_BASE                  (IPW_MEM_SRAM_HOST_SHARED_LOWER_BOUND + 0x40)
#घोषणा IPW_MEM_HOST_SHARED_RX_STATUS_BASE              (IPW_MEM_SRAM_HOST_SHARED_LOWER_BOUND + 0x44)
#घोषणा IPW_MEM_HOST_SHARED_RX_BD_SIZE                  (IPW_MEM_SRAM_HOST_SHARED_LOWER_BOUND + 0x48)
#घोषणा IPW_MEM_HOST_SHARED_RX_READ_INDEX               (IPW_MEM_SRAM_HOST_SHARED_LOWER_BOUND + 0xa0)

#घोषणा IPW_MEM_HOST_SHARED_TX_QUEUE_BD_BASE          (IPW_MEM_SRAM_HOST_SHARED_LOWER_BOUND + 0x00)
#घोषणा IPW_MEM_HOST_SHARED_TX_QUEUE_BD_SIZE          (IPW_MEM_SRAM_HOST_SHARED_LOWER_BOUND + 0x04)
#घोषणा IPW_MEM_HOST_SHARED_TX_QUEUE_READ_INDEX       (IPW_MEM_SRAM_HOST_SHARED_LOWER_BOUND + 0x80)

#घोषणा IPW_MEM_HOST_SHARED_RX_WRITE_INDEX \
    (IPW_MEM_SRAM_HOST_INTERRUPT_AREA_LOWER_BOUND + 0x20)

#घोषणा IPW_MEM_HOST_SHARED_TX_QUEUE_WRITE_INDEX \
    (IPW_MEM_SRAM_HOST_INTERRUPT_AREA_LOWER_BOUND)

#घोषणा IPW_MEM_HOST_SHARED_ORDINALS_TABLE_1   (IPW_MEM_SRAM_HOST_SHARED_LOWER_BOUND + 0x180)
#घोषणा IPW_MEM_HOST_SHARED_ORDINALS_TABLE_2   (IPW_MEM_SRAM_HOST_SHARED_LOWER_BOUND + 0x184)

#घोषणा IPW2100_INTA_TX_TRANSFER               (0x00000001)	// Bit 0 (LSB)
#घोषणा IPW2100_INTA_RX_TRANSFER               (0x00000002)	// Bit 1
#घोषणा IPW2100_INTA_TX_COMPLETE	       (0x00000004)	// Bit 2
#घोषणा IPW2100_INTA_EVENT_INTERRUPT           (0x00000008)	// Bit 3
#घोषणा IPW2100_INTA_STATUS_CHANGE             (0x00000010)	// Bit 4
#घोषणा IPW2100_INTA_BEACON_PERIOD_EXPIRED     (0x00000020)	// Bit 5
#घोषणा IPW2100_INTA_SLAVE_MODE_HOST_COMMAND_DONE  (0x00010000)	// Bit 16
#घोषणा IPW2100_INTA_FW_INIT_DONE              (0x01000000)	// Bit 24
#घोषणा IPW2100_INTA_FW_CALIBRATION_CALC       (0x02000000)	// Bit 25
#घोषणा IPW2100_INTA_FATAL_ERROR               (0x40000000)	// Bit 30
#घोषणा IPW2100_INTA_PARITY_ERROR              (0x80000000)	// Bit 31 (MSB)

#घोषणा IPW_AUX_HOST_RESET_REG_PRINCETON_RESET              (0x00000001)
#घोषणा IPW_AUX_HOST_RESET_REG_FORCE_NMI                    (0x00000002)
#घोषणा IPW_AUX_HOST_RESET_REG_PCI_HOST_CLUSTER_FATAL_NMI   (0x00000004)
#घोषणा IPW_AUX_HOST_RESET_REG_CORE_FATAL_NMI               (0x00000008)
#घोषणा IPW_AUX_HOST_RESET_REG_SW_RESET                     (0x00000080)
#घोषणा IPW_AUX_HOST_RESET_REG_MASTER_DISABLED              (0x00000100)
#घोषणा IPW_AUX_HOST_RESET_REG_STOP_MASTER                  (0x00000200)

#घोषणा IPW_AUX_HOST_GP_CNTRL_BIT_CLOCK_READY           (0x00000001)	// Bit 0 (LSB)
#घोषणा IPW_AUX_HOST_GP_CNTRL_BIT_HOST_ALLOWS_STANDBY   (0x00000002)	// Bit 1
#घोषणा IPW_AUX_HOST_GP_CNTRL_BIT_INIT_DONE             (0x00000004)	// Bit 2
#घोषणा IPW_AUX_HOST_GP_CNTRL_BITS_SYS_CONFIG           (0x000007c0)	// Bits 6-10
#घोषणा IPW_AUX_HOST_GP_CNTRL_BIT_BUS_TYPE              (0x00000200)	// Bit 9
#घोषणा IPW_AUX_HOST_GP_CNTRL_BIT_BAR0_BLOCK_SIZE       (0x00000400)	// Bit 10
#घोषणा IPW_AUX_HOST_GP_CNTRL_BIT_USB_MODE              (0x20000000)	// Bit 29
#घोषणा IPW_AUX_HOST_GP_CNTRL_BIT_HOST_FORCES_SYS_CLK   (0x40000000)	// Bit 30
#घोषणा IPW_AUX_HOST_GP_CNTRL_BIT_FW_FORCES_SYS_CLK     (0x80000000)	// Bit 31 (MSB)

#घोषणा IPW_BIT_GPIO_GPIO1_MASK         0x0000000C
#घोषणा IPW_BIT_GPIO_GPIO3_MASK         0x000000C0
#घोषणा IPW_BIT_GPIO_GPIO1_ENABLE       0x00000008
#घोषणा IPW_BIT_GPIO_RF_KILL            0x00010000

#घोषणा IPW_BIT_GPIO_LED_OFF            0x00002000	// Bit 13 = 1

#घोषणा IPW_REG_DOMAIN_0_OFFSET 	0x0000
#घोषणा IPW_REG_DOMAIN_1_OFFSET 	IPW_MEM_SRAM_HOST_SHARED_LOWER_BOUND

#घोषणा IPW_REG_INTA			IPW_REG_DOMAIN_0_OFFSET + 0x0008
#घोषणा IPW_REG_INTA_MASK		IPW_REG_DOMAIN_0_OFFSET + 0x000C
#घोषणा IPW_REG_INसूचीECT_ACCESS_ADDRESS	IPW_REG_DOMAIN_0_OFFSET + 0x0010
#घोषणा IPW_REG_INसूचीECT_ACCESS_DATA	IPW_REG_DOMAIN_0_OFFSET + 0x0014
#घोषणा IPW_REG_AUTOINCREMENT_ADDRESS	IPW_REG_DOMAIN_0_OFFSET + 0x0018
#घोषणा IPW_REG_AUTOINCREMENT_DATA	IPW_REG_DOMAIN_0_OFFSET + 0x001C
#घोषणा IPW_REG_RESET_REG		IPW_REG_DOMAIN_0_OFFSET + 0x0020
#घोषणा IPW_REG_GP_CNTRL		IPW_REG_DOMAIN_0_OFFSET + 0x0024
#घोषणा IPW_REG_GPIO			IPW_REG_DOMAIN_0_OFFSET + 0x0030
#घोषणा IPW_REG_FW_TYPE                 IPW_REG_DOMAIN_1_OFFSET + 0x0188
#घोषणा IPW_REG_FW_VERSION 		IPW_REG_DOMAIN_1_OFFSET + 0x018C
#घोषणा IPW_REG_FW_COMPATIBILITY_VERSION IPW_REG_DOMAIN_1_OFFSET + 0x0190

#घोषणा IPW_REG_INसूचीECT_ADDR_MASK	0x00FFFFFC

#घोषणा IPW_INTERRUPT_MASK		0xC1010013

#घोषणा IPW2100_CONTROL_REG             0x220000
#घोषणा IPW2100_CONTROL_PHY_OFF         0x8

#घोषणा IPW2100_COMMAND			0x00300004
#घोषणा IPW2100_COMMAND_PHY_ON		0x0
#घोषणा IPW2100_COMMAND_PHY_OFF		0x1

/* in DEBUG_AREA, values of memory always 0xd55555d5 */
#घोषणा IPW_REG_DOA_DEBUG_AREA_START    IPW_REG_DOMAIN_0_OFFSET + 0x0090
#घोषणा IPW_REG_DOA_DEBUG_AREA_END      IPW_REG_DOMAIN_0_OFFSET + 0x00FF
#घोषणा IPW_DATA_DOA_DEBUG_VALUE        0xd55555d5

#घोषणा IPW_INTERNAL_REGISTER_HALT_AND_RESET	0x003000e0

#घोषणा IPW_WAIT_CLOCK_STABILIZATION_DELAY	    50	// micro seconds
#घोषणा IPW_WAIT_RESET_ARC_COMPLETE_DELAY	    10	// micro seconds
#घोषणा IPW_WAIT_RESET_MASTER_ASSERT_COMPLETE_DELAY 10	// micro seconds

// BD ring queue पढ़ो/ग_लिखो dअगरference
#घोषणा IPW_BD_QUEUE_W_R_MIN_SPARE 2

#घोषणा IPW_CACHE_LINE_LENGTH_DEFAULT		    0x80

#घोषणा IPW_CARD_DISABLE_PHY_OFF_COMPLETE_WAIT	    100	// 100 milli
#घोषणा IPW_PREPARE_POWER_DOWN_COMPLETE_WAIT	    100	// 100 milli

#घोषणा IPW_HEADER_802_11_SIZE		 माप(काष्ठा libipw_hdr_3addr)
#घोषणा IPW_MAX_80211_PAYLOAD_SIZE              2304U
#घोषणा IPW_MAX_802_11_PAYLOAD_LENGTH		2312
#घोषणा IPW_MAX_ACCEPTABLE_TX_FRAME_LENGTH	1536
#घोषणा IPW_MIN_ACCEPTABLE_RX_FRAME_LENGTH	60
#घोषणा IPW_MAX_ACCEPTABLE_RX_FRAME_LENGTH \
	(IPW_MAX_ACCEPTABLE_TX_FRAME_LENGTH + IPW_HEADER_802_11_SIZE - \
        माप(काष्ठा ethhdr))

#घोषणा IPW_802_11_FCS_LENGTH 4
#घोषणा IPW_RX_NIC_BUFFER_LENGTH \
        (IPW_MAX_802_11_PAYLOAD_LENGTH + IPW_HEADER_802_11_SIZE + \
		IPW_802_11_FCS_LENGTH)

#घोषणा IPW_802_11_PAYLOAD_OFFSET \
        (माप(काष्ठा libipw_hdr_3addr) + \
         माप(काष्ठा libipw_snap_hdr))

काष्ठा ipw2100_rx अणु
	जोड़ अणु
		अचिन्हित अक्षर payload[IPW_RX_NIC_BUFFER_LENGTH];
		काष्ठा libipw_hdr_4addr header;
		u32 status;
		काष्ठा ipw2100_notअगरication notअगरication;
		काष्ठा ipw2100_cmd_header command;
	पूर्ण rx_data;
पूर्ण __packed;

/* Bit 0-7 are क्रम 802.11b tx rates - .  Bit 5-7 are reserved */
#घोषणा TX_RATE_1_MBIT              0x0001
#घोषणा TX_RATE_2_MBIT              0x0002
#घोषणा TX_RATE_5_5_MBIT            0x0004
#घोषणा TX_RATE_11_MBIT             0x0008
#घोषणा TX_RATE_MASK                0x000F
#घोषणा DEFAULT_TX_RATES            0x000F

#घोषणा IPW_POWER_MODE_CAM           0x00	//(always on)
#घोषणा IPW_POWER_INDEX_1            0x01
#घोषणा IPW_POWER_INDEX_2            0x02
#घोषणा IPW_POWER_INDEX_3            0x03
#घोषणा IPW_POWER_INDEX_4            0x04
#घोषणा IPW_POWER_INDEX_5            0x05
#घोषणा IPW_POWER_AUTO               0x06
#घोषणा IPW_POWER_MASK               0x0F
#घोषणा IPW_POWER_ENABLED            0x10
#घोषणा IPW_POWER_LEVEL(x)           ((x) & IPW_POWER_MASK)

#घोषणा IPW_TX_POWER_AUTO            0
#घोषणा IPW_TX_POWER_ENHANCED        1

#घोषणा IPW_TX_POWER_DEFAULT         32
#घोषणा IPW_TX_POWER_MIN             0
#घोषणा IPW_TX_POWER_MAX             16
#घोषणा IPW_TX_POWER_MIN_DBM         (-12)
#घोषणा IPW_TX_POWER_MAX_DBM         16

#घोषणा FW_SCAN_DONOT_ASSOCIATE     0x0001	// Dont Attempt to Associate after Scan
#घोषणा FW_SCAN_PASSIVE             0x0008	// Force PASSSIVE Scan

#घोषणा REG_MIN_CHANNEL             0
#घोषणा REG_MAX_CHANNEL             14

#घोषणा REG_CHANNEL_MASK            0x00003FFF
#घोषणा IPW_IBSS_11B_DEFAULT_MASK   0x87ff

#घोषणा DIVERSITY_EITHER            0	// Use both antennas
#घोषणा DIVERSITY_ANTENNA_A         1	// Use antenna A
#घोषणा DIVERSITY_ANTENNA_B         2	// Use antenna B

#घोषणा HOST_COMMAND_WAIT 0
#घोषणा HOST_COMMAND_NO_WAIT 1

#घोषणा LOCK_NONE 0
#घोषणा LOCK_DRIVER 1
#घोषणा LOCK_FW 2

#घोषणा TYPE_SWEEP_ORD                  0x000D
#घोषणा TYPE_IBSS_STTN_ORD              0x000E
#घोषणा TYPE_BSS_AP_ORD                 0x000F
#घोषणा TYPE_RAW_BEACON_ENTRY           0x0010
#घोषणा TYPE_CALIBRATION_DATA           0x0011
#घोषणा TYPE_ROGUE_AP_DATA              0x0012
#घोषणा TYPE_ASSOCIATION_REQUEST	0x0013
#घोषणा TYPE_REASSOCIATION_REQUEST	0x0014

#घोषणा HW_FEATURE_RFKILL 0x0001
#घोषणा RF_KILLSWITCH_OFF 1
#घोषणा RF_KILLSWITCH_ON  0

#घोषणा IPW_COMMAND_POOL_SIZE        40

#घोषणा IPW_START_ORD_TAB_1			1
#घोषणा IPW_START_ORD_TAB_2			1000

#घोषणा IPW_ORD_TAB_1_ENTRY_SIZE		माप(u32)

#घोषणा IS_ORDINAL_TABLE_ONE(mgr,id) \
    ((id >= IPW_START_ORD_TAB_1) && (id < mgr->table1_size))
#घोषणा IS_ORDINAL_TABLE_TWO(mgr,id) \
    ((id >= IPW_START_ORD_TAB_2) && (id < (mgr->table2_size + IPW_START_ORD_TAB_2)))

#घोषणा BSS_ID_LENGTH               6

// Fixed size data: Ordinal Table 1
प्रकार क्रमागत _ORDINAL_TABLE_1 अणु	// NS - means Not Supported by FW
// Transmit statistics
	IPW_ORD_STAT_TX_HOST_REQUESTS = 1,	// # of requested Host Tx's (MSDU)
	IPW_ORD_STAT_TX_HOST_COMPLETE,	// # of successful Host Tx's (MSDU)
	IPW_ORD_STAT_TX_सूची_DATA,	// # of successful Directed Tx's (MSDU)

	IPW_ORD_STAT_TX_सूची_DATA1 = 4,	// # of successful Directed Tx's (MSDU) @ 1MB
	IPW_ORD_STAT_TX_सूची_DATA2,	// # of successful Directed Tx's (MSDU) @ 2MB
	IPW_ORD_STAT_TX_सूची_DATA5_5,	// # of successful Directed Tx's (MSDU) @ 5_5MB
	IPW_ORD_STAT_TX_सूची_DATA11,	// # of successful Directed Tx's (MSDU) @ 11MB
	IPW_ORD_STAT_TX_सूची_DATA22,	// # of successful Directed Tx's (MSDU) @ 22MB

	IPW_ORD_STAT_TX_NOसूची_DATA1 = 13,	// # of successful Non_Directed Tx's (MSDU) @ 1MB
	IPW_ORD_STAT_TX_NOसूची_DATA2,	// # of successful Non_Directed Tx's (MSDU) @ 2MB
	IPW_ORD_STAT_TX_NOसूची_DATA5_5,	// # of successful Non_Directed Tx's (MSDU) @ 5.5MB
	IPW_ORD_STAT_TX_NOसूची_DATA11,	// # of successful Non_Directed Tx's (MSDU) @ 11MB

	IPW_ORD_STAT_शून्य_DATA = 21,	// # of successful शून्य data Tx's
	IPW_ORD_STAT_TX_RTS,	// # of successful Tx RTS
	IPW_ORD_STAT_TX_CTS,	// # of successful Tx CTS
	IPW_ORD_STAT_TX_ACK,	// # of successful Tx ACK
	IPW_ORD_STAT_TX_ASSN,	// # of successful Association Tx's
	IPW_ORD_STAT_TX_ASSN_RESP,	// # of successful Association response Tx's
	IPW_ORD_STAT_TX_REASSN,	// # of successful Reassociation Tx's
	IPW_ORD_STAT_TX_REASSN_RESP,	// # of successful Reassociation response Tx's
	IPW_ORD_STAT_TX_PROBE,	// # of probes successfully transmitted
	IPW_ORD_STAT_TX_PROBE_RESP,	// # of probe responses successfully transmitted
	IPW_ORD_STAT_TX_BEACON,	// # of tx beacon
	IPW_ORD_STAT_TX_ATIM,	// # of Tx ATIM
	IPW_ORD_STAT_TX_DISASSN,	// # of successful Disassociation TX
	IPW_ORD_STAT_TX_AUTH,	// # of successful Authentication Tx
	IPW_ORD_STAT_TX_DEAUTH,	// # of successful Deauthentication TX

	IPW_ORD_STAT_TX_TOTAL_BYTES = 41,	// Total successful Tx data bytes
	IPW_ORD_STAT_TX_RETRIES,	// # of Tx retries
	IPW_ORD_STAT_TX_RETRY1,	// # of Tx retries at 1MBPS
	IPW_ORD_STAT_TX_RETRY2,	// # of Tx retries at 2MBPS
	IPW_ORD_STAT_TX_RETRY5_5,	// # of Tx retries at 5.5MBPS
	IPW_ORD_STAT_TX_RETRY11,	// # of Tx retries at 11MBPS

	IPW_ORD_STAT_TX_FAILURES = 51,	// # of Tx Failures
	IPW_ORD_STAT_TX_ABORT_AT_HOP,	//NS // # of Tx's पातed at hop समय
	IPW_ORD_STAT_TX_MAX_TRIES_IN_HOP,	// # of बार max tries in a hop failed
	IPW_ORD_STAT_TX_ABORT_LATE_DMA,	//NS // # of बार tx पातed due to late dma setup
	IPW_ORD_STAT_TX_ABORT_STX,	//NS // # of बार backoff पातed
	IPW_ORD_STAT_TX_DISASSN_FAIL,	// # of बार disassociation failed
	IPW_ORD_STAT_TX_ERR_CTS,	// # of missed/bad CTS frames
	IPW_ORD_STAT_TX_BPDU,	//NS // # of spanning tree BPDUs sent
	IPW_ORD_STAT_TX_ERR_ACK,	// # of tx err due to acks

	// Receive statistics
	IPW_ORD_STAT_RX_HOST = 61,	// # of packets passed to host
	IPW_ORD_STAT_RX_सूची_DATA,	// # of directed packets
	IPW_ORD_STAT_RX_सूची_DATA1,	// # of directed packets at 1MB
	IPW_ORD_STAT_RX_सूची_DATA2,	// # of directed packets at 2MB
	IPW_ORD_STAT_RX_सूची_DATA5_5,	// # of directed packets at 5.5MB
	IPW_ORD_STAT_RX_सूची_DATA11,	// # of directed packets at 11MB
	IPW_ORD_STAT_RX_सूची_DATA22,	// # of directed packets at 22MB

	IPW_ORD_STAT_RX_NOसूची_DATA = 71,	// # of nondirected packets
	IPW_ORD_STAT_RX_NOसूची_DATA1,	// # of nondirected packets at 1MB
	IPW_ORD_STAT_RX_NOसूची_DATA2,	// # of nondirected packets at 2MB
	IPW_ORD_STAT_RX_NOसूची_DATA5_5,	// # of nondirected packets at 5.5MB
	IPW_ORD_STAT_RX_NOसूची_DATA11,	// # of nondirected packets at 11MB

	IPW_ORD_STAT_RX_शून्य_DATA = 80,	// # of null data rx's
	IPW_ORD_STAT_RX_POLL,	//NS // # of poll rx
	IPW_ORD_STAT_RX_RTS,	// # of Rx RTS
	IPW_ORD_STAT_RX_CTS,	// # of Rx CTS
	IPW_ORD_STAT_RX_ACK,	// # of Rx ACK
	IPW_ORD_STAT_RX_CFEND,	// # of Rx CF End
	IPW_ORD_STAT_RX_CFEND_ACK,	// # of Rx CF End + CF Ack
	IPW_ORD_STAT_RX_ASSN,	// # of Association Rx's
	IPW_ORD_STAT_RX_ASSN_RESP,	// # of Association response Rx's
	IPW_ORD_STAT_RX_REASSN,	// # of Reassociation Rx's
	IPW_ORD_STAT_RX_REASSN_RESP,	// # of Reassociation response Rx's
	IPW_ORD_STAT_RX_PROBE,	// # of probe Rx's
	IPW_ORD_STAT_RX_PROBE_RESP,	// # of probe response Rx's
	IPW_ORD_STAT_RX_BEACON,	// # of Rx beacon
	IPW_ORD_STAT_RX_ATIM,	// # of Rx ATIM
	IPW_ORD_STAT_RX_DISASSN,	// # of disassociation Rx
	IPW_ORD_STAT_RX_AUTH,	// # of authentication Rx
	IPW_ORD_STAT_RX_DEAUTH,	// # of deauthentication Rx

	IPW_ORD_STAT_RX_TOTAL_BYTES = 101,	// Total rx data bytes received
	IPW_ORD_STAT_RX_ERR_CRC,	// # of packets with Rx CRC error
	IPW_ORD_STAT_RX_ERR_CRC1,	// # of Rx CRC errors at 1MB
	IPW_ORD_STAT_RX_ERR_CRC2,	// # of Rx CRC errors at 2MB
	IPW_ORD_STAT_RX_ERR_CRC5_5,	// # of Rx CRC errors at 5.5MB
	IPW_ORD_STAT_RX_ERR_CRC11,	// # of Rx CRC errors at 11MB

	IPW_ORD_STAT_RX_DUPLICATE1 = 112,	// # of duplicate rx packets at 1MB
	IPW_ORD_STAT_RX_DUPLICATE2,	// # of duplicate rx packets at 2MB
	IPW_ORD_STAT_RX_DUPLICATE5_5,	// # of duplicate rx packets at 5.5MB
	IPW_ORD_STAT_RX_DUPLICATE11,	// # of duplicate rx packets at 11MB
	IPW_ORD_STAT_RX_DUPLICATE = 119,	// # of duplicate rx packets

	IPW_ORD_PERS_DB_LOCK = 120,	// # locking fw permanent  db
	IPW_ORD_PERS_DB_SIZE,	// # size of fw permanent  db
	IPW_ORD_PERS_DB_ADDR,	// # address of fw permanent  db
	IPW_ORD_STAT_RX_INVALID_PROTOCOL,	// # of rx frames with invalid protocol
	IPW_ORD_SYS_BOOT_TIME,	// # Boot समय
	IPW_ORD_STAT_RX_NO_BUFFER,	// # of rx frames rejected due to no buffer
	IPW_ORD_STAT_RX_ABORT_LATE_DMA,	//NS // # of rx frames rejected due to dma setup too late
	IPW_ORD_STAT_RX_ABORT_AT_HOP,	//NS // # of rx frames पातed due to hop
	IPW_ORD_STAT_RX_MISSING_FRAG,	// # of rx frames dropped due to missing fragment
	IPW_ORD_STAT_RX_ORPHAN_FRAG,	// # of rx frames dropped due to non-sequential fragment
	IPW_ORD_STAT_RX_ORPHAN_FRAME,	// # of rx frames dropped due to unmatched 1st frame
	IPW_ORD_STAT_RX_FRAG_AGEOUT,	// # of rx frames dropped due to uncompleted frame
	IPW_ORD_STAT_RX_BAD_SSID,	//NS // Bad SSID (unused)
	IPW_ORD_STAT_RX_ICV_ERRORS,	// # of ICV errors during decryption

// PSP Statistics
	IPW_ORD_STAT_PSP_SUSPENSION = 137,	// # of बार adapter suspended
	IPW_ORD_STAT_PSP_BCN_TIMEOUT,	// # of beacon समयout
	IPW_ORD_STAT_PSP_POLL_TIMEOUT,	// # of poll response समयouts
	IPW_ORD_STAT_PSP_NONसूची_TIMEOUT,	// # of समयouts रुकोing क्रम last broadcast/muticast pkt
	IPW_ORD_STAT_PSP_RX_DTIMS,	// # of PSP DTIMs received
	IPW_ORD_STAT_PSP_RX_TIMS,	// # of PSP TIMs received
	IPW_ORD_STAT_PSP_STATION_ID,	// PSP Station ID

// Association and roaming
	IPW_ORD_LAST_ASSN_TIME = 147,	// RTC समय of last association
	IPW_ORD_STAT_PERCENT_MISSED_BCNS,	// current calculation of % missed beacons
	IPW_ORD_STAT_PERCENT_RETRIES,	// current calculation of % missed tx retries
	IPW_ORD_ASSOCIATED_AP_PTR,	// If associated, this is ptr to the associated
	// AP table entry. set to 0 अगर not associated
	IPW_ORD_AVAILABLE_AP_CNT,	// # of AP's described in the AP table
	IPW_ORD_AP_LIST_PTR,	// Ptr to list of available APs
	IPW_ORD_STAT_AP_ASSNS,	// # of associations
	IPW_ORD_STAT_ASSN_FAIL,	// # of association failures
	IPW_ORD_STAT_ASSN_RESP_FAIL,	// # of failuresdue to response fail
	IPW_ORD_STAT_FULL_SCANS,	// # of full scans

	IPW_ORD_CARD_DISABLED,	// # Card Disabled
	IPW_ORD_STAT_ROAM_INHIBIT,	// # of बार roaming was inhibited due to ongoing activity
	IPW_FILLER_40,
	IPW_ORD_RSSI_AT_ASSN = 160,	// RSSI of associated AP at समय of association
	IPW_ORD_STAT_ASSN_CAUSE1,	// # of reassociations due to no tx from AP in last N
	// hops or no prob_ responses in last 3 minutes
	IPW_ORD_STAT_ASSN_CAUSE2,	// # of reassociations due to poor tx/rx quality
	IPW_ORD_STAT_ASSN_CAUSE3,	// # of reassociations due to tx/rx quality with excessive
	// load at the AP
	IPW_ORD_STAT_ASSN_CAUSE4,	// # of reassociations due to AP RSSI level fell below
	// eligible group
	IPW_ORD_STAT_ASSN_CAUSE5,	// # of reassociations due to load leveling
	IPW_ORD_STAT_ASSN_CAUSE6,	//NS // # of reassociations due to dropped by Ap
	IPW_FILLER_41,
	IPW_FILLER_42,
	IPW_FILLER_43,
	IPW_ORD_STAT_AUTH_FAIL,	// # of बार authentication failed
	IPW_ORD_STAT_AUTH_RESP_FAIL,	// # of बार authentication response failed
	IPW_ORD_STATION_TABLE_CNT,	// # of entries in association table

// Other statistics
	IPW_ORD_RSSI_AVG_CURR = 173,	// Current avg RSSI
	IPW_ORD_STEST_RESULTS_CURR,	//NS // Current self test results word
	IPW_ORD_STEST_RESULTS_CUM,	//NS // Cummulative self test results word
	IPW_ORD_SELF_TEST_STATUS,	//NS //
	IPW_ORD_POWER_MGMT_MODE,	// Power mode - 0=CAM, 1=PSP
	IPW_ORD_POWER_MGMT_INDEX,	//NS //
	IPW_ORD_COUNTRY_CODE,	// IEEE country code as recv'd from beacon
	IPW_ORD_COUNTRY_CHANNELS,	// channels supported by country
// IPW_ORD_COUNTRY_CHANNELS:
// For 11b the lower 2-byte are used क्रम channels from 1-14
//   and the higher 2-byte are not used.
	IPW_ORD_RESET_CNT,	// # of adapter resets (warm)
	IPW_ORD_BEACON_INTERVAL,	// Beacon पूर्णांकerval

	IPW_ORD_PRINCETON_VERSION = 184,	//NS // Princeton Version
	IPW_ORD_ANTENNA_DIVERSITY,	// TRUE अगर antenna भागersity is disabled
	IPW_ORD_CCA_RSSI,	//NS // CCA RSSI value (factory programmed)
	IPW_ORD_STAT_EEPROM_UPDATE,	//NS // # of बार config EEPROM updated
	IPW_ORD_DTIM_PERIOD,	// # of beacon पूर्णांकervals between DTIMs
	IPW_ORD_OUR_FREQ,	// current radio freq lower digits - channel ID

	IPW_ORD_RTC_TIME = 190,	// current RTC समय
	IPW_ORD_PORT_TYPE,	// operating mode
	IPW_ORD_CURRENT_TX_RATE,	// current tx rate
	IPW_ORD_SUPPORTED_RATES,	// Biपंचांगap of supported tx rates
	IPW_ORD_ATIM_WINDOW,	// current ATIM Winकरोw
	IPW_ORD_BASIC_RATES,	// biपंचांगap of basic tx rates
	IPW_ORD_NIC_HIGHEST_RATE,	// biपंचांगap of basic tx rates
	IPW_ORD_AP_HIGHEST_RATE,	// biपंचांगap of basic tx rates
	IPW_ORD_CAPABILITIES,	// Management frame capability field
	IPW_ORD_AUTH_TYPE,	// Type of authentication
	IPW_ORD_RADIO_TYPE,	// Adapter card platक्रमm type
	IPW_ORD_RTS_THRESHOLD = 201,	// Min length of packet after which RTS handshaking is used
	IPW_ORD_INT_MODE,	// International mode
	IPW_ORD_FRAGMENTATION_THRESHOLD,	// protocol frag threshold
	IPW_ORD_EEPROM_SRAM_DB_BLOCK_START_ADDRESS,	// EEPROM offset in SRAM
	IPW_ORD_EEPROM_SRAM_DB_BLOCK_SIZE,	// EEPROM size in SRAM
	IPW_ORD_EEPROM_SKU_CAPABILITY,	// EEPROM SKU Capability    206 =
	IPW_ORD_EEPROM_IBSS_11B_CHANNELS,	// EEPROM IBSS 11b channel set

	IPW_ORD_MAC_VERSION = 209,	// MAC Version
	IPW_ORD_MAC_REVISION,	// MAC Revision
	IPW_ORD_RADIO_VERSION,	// Radio Version
	IPW_ORD_NIC_MANF_DATE_TIME,	// MANF Date/Time STAMP
	IPW_ORD_UCODE_VERSION,	// Ucode Version
	IPW_ORD_HW_RF_SWITCH_STATE = 214,	// HW RF Kill Switch State
पूर्ण ORDINALTABLE1;

// ordinal table 2
// Variable length data:
#घोषणा IPW_FIRST_VARIABLE_LENGTH_ORDINAL   1001

प्रकार क्रमागत _ORDINAL_TABLE_2 अणु	// NS - means Not Supported by FW
	IPW_ORD_STAT_BASE = 1000,	// contains number of variable ORDs
	IPW_ORD_STAT_ADAPTER_MAC = 1001,	// 6 bytes: our adapter MAC address
	IPW_ORD_STAT_PREFERRED_BSSID = 1002,	// 6 bytes: BSSID of the preferred AP
	IPW_ORD_STAT_MANDATORY_BSSID = 1003,	// 6 bytes: BSSID of the mandatory AP
	IPW_FILL_1,		//NS //
	IPW_ORD_STAT_COUNTRY_TEXT = 1005,	// 36 bytes: Country name text, First two bytes are Country code
	IPW_ORD_STAT_ASSN_SSID = 1006,	// 32 bytes: ESSID String
	IPW_ORD_STATION_TABLE = 1007,	// ? bytes: Station/AP table (via Direct SSID Scans)
	IPW_ORD_STAT_SWEEP_TABLE = 1008,	// ? bytes: Sweep/Host Table table (via Broadcast Scans)
	IPW_ORD_STAT_ROAM_LOG = 1009,	// ? bytes: Roaming log
	IPW_ORD_STAT_RATE_LOG = 1010,	//NS // 0 bytes: Rate log
	IPW_ORD_STAT_FIFO = 1011,	//NS // 0 bytes: Fअगरo buffer data काष्ठाures
	IPW_ORD_STAT_FW_VER_NUM = 1012,	// 14 bytes: fw version ID string as in (a.bb.ccc; "0.08.011")
	IPW_ORD_STAT_FW_DATE = 1013,	// 14 bytes: fw date string (mmm dd yyyy; "Mar 13 2002")
	IPW_ORD_STAT_ASSN_AP_BSSID = 1014,	// 6 bytes: MAC address of associated AP
	IPW_ORD_STAT_DEBUG = 1015,	//NS // ? bytes:
	IPW_ORD_STAT_NIC_BPA_NUM = 1016,	// 11 bytes: NIC BPA number in ASCII
	IPW_ORD_STAT_UCODE_DATE = 1017,	// 5 bytes: uCode date
	IPW_ORD_SECURITY_NGOTIATION_RESULT = 1018,
पूर्ण ORDINALTABLE2;		// NS - means Not Supported by FW

#घोषणा IPW_LAST_VARIABLE_LENGTH_ORDINAL   1018

#अगर_अघोषित WIRELESS_SPY
#घोषणा WIRELESS_SPY		// enable iwspy support
#पूर्ण_अगर

#घोषणा IPW_HOST_FW_SHARED_AREA0 	0x0002f200
#घोषणा IPW_HOST_FW_SHARED_AREA0_END 	0x0002f510	// 0x310 bytes

#घोषणा IPW_HOST_FW_SHARED_AREA1 	0x0002f610
#घोषणा IPW_HOST_FW_SHARED_AREA1_END 	0x0002f630	// 0x20 bytes

#घोषणा IPW_HOST_FW_SHARED_AREA2 	0x0002fa00
#घोषणा IPW_HOST_FW_SHARED_AREA2_END 	0x0002fa20	// 0x20 bytes

#घोषणा IPW_HOST_FW_SHARED_AREA3 	0x0002fc00
#घोषणा IPW_HOST_FW_SHARED_AREA3_END 	0x0002fc10	// 0x10 bytes

#घोषणा IPW_HOST_FW_INTERRUPT_AREA 	0x0002ff80
#घोषणा IPW_HOST_FW_INTERRUPT_AREA_END 	0x00030000	// 0x80 bytes

काष्ठा ipw2100_fw_chunk अणु
	अचिन्हित अक्षर *buf;
	दीर्घ len;
	दीर्घ pos;
	काष्ठा list_head list;
पूर्ण;

काष्ठा ipw2100_fw_chunk_set अणु
	स्थिर व्योम *data;
	अचिन्हित दीर्घ size;
पूर्ण;

काष्ठा ipw2100_fw अणु
	पूर्णांक version;
	काष्ठा ipw2100_fw_chunk_set fw;
	काष्ठा ipw2100_fw_chunk_set uc;
	स्थिर काष्ठा firmware *fw_entry;
पूर्ण;

#घोषणा MAX_FW_VERSION_LEN 14

#पूर्ण_अगर				/* _IPW2100_H */
