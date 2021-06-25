<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  PS3 gelic network driver.
 *
 * Copyright (C) 2007 Sony Computer Entertainment Inc.
 * Copyright 2007 Sony Corporation
 */
#अगर_अघोषित _GELIC_WIRELESS_H
#घोषणा _GELIC_WIRELESS_H

#समावेश <linux/wireless.h>
#समावेश <net/iw_handler.h>


/* वापस value from  GELIC_LV1_GET_WLAN_EVENT netcontrol */
क्रमागत gelic_lv1_wl_event अणु
	GELIC_LV1_WL_EVENT_DEVICE_READY   = 0x01, /* Eurus पढ़ोy */
	GELIC_LV1_WL_EVENT_SCAN_COMPLETED = 0x02, /* Scan has completed */
	GELIC_LV1_WL_EVENT_DEAUTH         = 0x04, /* Deauthed by the AP */
	GELIC_LV1_WL_EVENT_BEACON_LOST    = 0x08, /* Beacon lost detected */
	GELIC_LV1_WL_EVENT_CONNECTED      = 0x10, /* Connected to AP */
	GELIC_LV1_WL_EVENT_WPA_CONNECTED  = 0x20, /* WPA connection */
	GELIC_LV1_WL_EVENT_WPA_ERROR      = 0x40, /* MIC error */
पूर्ण;

/* arguments क्रम GELIC_LV1_POST_WLAN_COMMAND netcontrol */
क्रमागत gelic_eurus_command अणु
	GELIC_EURUS_CMD_ASSOC		=  1, /* association start */
	GELIC_EURUS_CMD_DISASSOC	=  2, /* disassociate      */
	GELIC_EURUS_CMD_START_SCAN	=  3, /* scan start        */
	GELIC_EURUS_CMD_GET_SCAN	=  4, /* get scan result   */
	GELIC_EURUS_CMD_SET_COMMON_CFG	=  5, /* set common config */
	GELIC_EURUS_CMD_GET_COMMON_CFG	=  6, /* set common config */
	GELIC_EURUS_CMD_SET_WEP_CFG	=  7, /* set WEP config    */
	GELIC_EURUS_CMD_GET_WEP_CFG	=  8, /* get WEP config    */
	GELIC_EURUS_CMD_SET_WPA_CFG	=  9, /* set WPA config    */
	GELIC_EURUS_CMD_GET_WPA_CFG	= 10, /* get WPA config    */
	GELIC_EURUS_CMD_GET_RSSI_CFG	= 11, /* get RSSI info.    */
	GELIC_EURUS_CMD_MAX_INDEX
पूर्ण;

/* क्रम GELIC_EURUS_CMD_COMMON_CFG */
क्रमागत gelic_eurus_bss_type अणु
	GELIC_EURUS_BSS_INFRA = 0,
	GELIC_EURUS_BSS_ADHOC = 1, /* not supported */
पूर्ण;

क्रमागत gelic_eurus_auth_method अणु
	GELIC_EURUS_AUTH_OPEN = 0, /* FIXME: WLAN_AUTH_OPEN */
	GELIC_EURUS_AUTH_SHARED = 1, /* not supported */
पूर्ण;

क्रमागत gelic_eurus_opmode अणु
	GELIC_EURUS_OPMODE_11BG = 0, /* 802.11b/g */
	GELIC_EURUS_OPMODE_11B = 1, /* 802.11b only */
	GELIC_EURUS_OPMODE_11G = 2, /* 802.11g only */
पूर्ण;

काष्ठा gelic_eurus_common_cfg अणु
	/* all fields are big endian */
	u16 scan_index;
	u16 bss_type;    /* infra or adhoc */
	u16 auth_method; /* shared key or खोलो */
	u16 op_mode; /* B/G */
पूर्ण __packed;


/* क्रम GELIC_EURUS_CMD_WEP_CFG */
क्रमागत gelic_eurus_wep_security अणु
	GELIC_EURUS_WEP_SEC_NONE	= 0,
	GELIC_EURUS_WEP_SEC_40BIT	= 1,
	GELIC_EURUS_WEP_SEC_104BIT	= 2,
पूर्ण;

काष्ठा gelic_eurus_wep_cfg अणु
	/* all fields are big endian */
	u16 security;
	u8 key[4][16];
पूर्ण __packed;

/* क्रम GELIC_EURUS_CMD_WPA_CFG */
क्रमागत gelic_eurus_wpa_security अणु
	GELIC_EURUS_WPA_SEC_NONE		= 0x0000,
	/* group=TKIP, pairwise=TKIP */
	GELIC_EURUS_WPA_SEC_WPA_TKIP_TKIP	= 0x0001,
	/* group=AES, pairwise=AES */
	GELIC_EURUS_WPA_SEC_WPA_AES_AES		= 0x0002,
	/* group=TKIP, pairwise=TKIP */
	GELIC_EURUS_WPA_SEC_WPA2_TKIP_TKIP	= 0x0004,
	/* group=AES, pairwise=AES */
	GELIC_EURUS_WPA_SEC_WPA2_AES_AES	= 0x0008,
	/* group=TKIP, pairwise=AES */
	GELIC_EURUS_WPA_SEC_WPA_TKIP_AES	= 0x0010,
	/* group=TKIP, pairwise=AES */
	GELIC_EURUS_WPA_SEC_WPA2_TKIP_AES	= 0x0020,
पूर्ण;

क्रमागत gelic_eurus_wpa_psk_type अणु
	GELIC_EURUS_WPA_PSK_PASSPHRASE	= 0, /* passphrase string   */
	GELIC_EURUS_WPA_PSK_BIN		= 1, /* 32 bytes binary key */
पूर्ण;

#घोषणा GELIC_WL_EURUS_PSK_MAX_LEN	64
#घोषणा WPA_PSK_LEN			32 /* WPA spec says 256bit */

काष्ठा gelic_eurus_wpa_cfg अणु
	/* all fields are big endian */
	u16 security;
	u16 psk_type; /* psk key encoding type */
	u8 psk[GELIC_WL_EURUS_PSK_MAX_LEN]; /* psk key; hex or passphrase */
पूर्ण __packed;

/* क्रम GELIC_EURUS_CMD_अणुSTART,GETपूर्ण_SCAN */
क्रमागत gelic_eurus_scan_capability अणु
	GELIC_EURUS_SCAN_CAP_ADHOC	= 0x0000,
	GELIC_EURUS_SCAN_CAP_INFRA	= 0x0001,
	GELIC_EURUS_SCAN_CAP_MASK	= 0x0001,
पूर्ण;

क्रमागत gelic_eurus_scan_sec_type अणु
	GELIC_EURUS_SCAN_SEC_NONE	= 0x0000,
	GELIC_EURUS_SCAN_SEC_WEP	= 0x0100,
	GELIC_EURUS_SCAN_SEC_WPA	= 0x0200,
	GELIC_EURUS_SCAN_SEC_WPA2	= 0x0400,
	GELIC_EURUS_SCAN_SEC_MASK	= 0x0f00,
पूर्ण;

क्रमागत gelic_eurus_scan_sec_wep_type अणु
	GELIC_EURUS_SCAN_SEC_WEP_UNKNOWN	= 0x0000,
	GELIC_EURUS_SCAN_SEC_WEP_40		= 0x0001,
	GELIC_EURUS_SCAN_SEC_WEP_104		= 0x0002,
	GELIC_EURUS_SCAN_SEC_WEP_MASK		= 0x0003,
पूर्ण;

क्रमागत gelic_eurus_scan_sec_wpa_type अणु
	GELIC_EURUS_SCAN_SEC_WPA_UNKNOWN	= 0x0000,
	GELIC_EURUS_SCAN_SEC_WPA_TKIP		= 0x0001,
	GELIC_EURUS_SCAN_SEC_WPA_AES		= 0x0002,
	GELIC_EURUS_SCAN_SEC_WPA_MASK		= 0x0003,
पूर्ण;

/*
 * hw BSS inक्रमmation काष्ठाure वापसed from GELIC_EURUS_CMD_GET_SCAN
 */
काष्ठा gelic_eurus_scan_info अणु
	/* all fields are big endian */
	__be16 size;
	__be16 rssi; /* percentage */
	__be16 channel; /* channel number */
	__be16 beacon_period; /* FIXME: in msec unit */
	__be16 capability;
	__be16 security;
	u8  bssid[8]; /* last ETH_ALEN are valid. bssid[0],[1] are unused */
	u8  essid[32]; /* IW_ESSID_MAX_SIZE */
	u8  rate[16]; /* first 12 are valid */
	u8  ext_rate[16]; /* first 16 are valid */
	__be32 reserved1;
	__be32 reserved2;
	__be32 reserved3;
	__be32 reserved4;
	u8 elements[]; /* ie */
पूर्ण __packed;

/* the hypervisor वापसs bbs up to 16 */
#घोषणा GELIC_EURUS_MAX_SCAN  (16)
काष्ठा gelic_wl_scan_info अणु
	काष्ठा list_head list;
	काष्ठा gelic_eurus_scan_info *hwinfo;

	पूर्णांक valid; /* set 1 अगर this entry was in latest scanned list
		     * from Eurus */
	अचिन्हित पूर्णांक eurus_index; /* index in the Eurus list */
	अचिन्हित दीर्घ last_scanned; /* acquired समय */

	अचिन्हित पूर्णांक rate_len;
	अचिन्हित पूर्णांक rate_ext_len;
	अचिन्हित पूर्णांक essid_len;
पूर्ण;

/* क्रम GELIC_EURUS_CMD_GET_RSSI */
काष्ठा gelic_eurus_rssi_info अणु
	/* big endian */
	__be16 rssi;
पूर्ण __packed;


/* क्रम 'stat' member of gelic_wl_info */
क्रमागत gelic_wl_info_status_bit अणु
	GELIC_WL_STAT_CONFIGURED,
	GELIC_WL_STAT_CH_INFO,   /* ch info acquired */
	GELIC_WL_STAT_ESSID_SET, /* ESSID specअगरied by userspace */
	GELIC_WL_STAT_BSSID_SET, /* BSSID specअगरied by userspace */
	GELIC_WL_STAT_WPA_PSK_SET, /* PMK specअगरied by userspace */
	GELIC_WL_STAT_WPA_LEVEL_SET, /* WEP or WPA[2] selected */
पूर्ण;

/* क्रम 'scan_stat' member of gelic_wl_info */
क्रमागत gelic_wl_scan_state अणु
	/* just initialized or get last scan result failed */
	GELIC_WL_SCAN_STAT_INIT,
	/* scan request issued, accepted or chip is scanning */
	GELIC_WL_SCAN_STAT_SCANNING,
	/* scan results retrieved */
	GELIC_WL_SCAN_STAT_GOT_LIST,
पूर्ण;

/* क्रम 'cipher_method' */
क्रमागत gelic_wl_cipher_method अणु
	GELIC_WL_CIPHER_NONE,
	GELIC_WL_CIPHER_WEP,
	GELIC_WL_CIPHER_TKIP,
	GELIC_WL_CIPHER_AES,
पूर्ण;

/* क्रम 'wpa_level' */
क्रमागत gelic_wl_wpa_level अणु
	GELIC_WL_WPA_LEVEL_NONE,
	GELIC_WL_WPA_LEVEL_WPA,
	GELIC_WL_WPA_LEVEL_WPA2,
पूर्ण;

/* क्रम 'assoc_stat' */
क्रमागत gelic_wl_assoc_state अणु
	GELIC_WL_ASSOC_STAT_DISCONN,
	GELIC_WL_ASSOC_STAT_ASSOCIATING,
	GELIC_WL_ASSOC_STAT_ASSOCIATED,
पूर्ण;
/* part of निजी data alloc_etherdev() allocated */
#घोषणा GELIC_WEP_KEYS 4
काष्ठा gelic_wl_info अणु
	/* bss list */
	काष्ठा mutex scan_lock;
	काष्ठा list_head network_list;
	काष्ठा list_head network_मुक्त_list;
	काष्ठा gelic_wl_scan_info *networks;

	अचिन्हित दीर्घ scan_age; /* last scanned समय */
	क्रमागत gelic_wl_scan_state scan_stat;
	काष्ठा completion scan_करोne;

	/* eurus command queue */
	काष्ठा workqueue_काष्ठा *eurus_cmd_queue;
	काष्ठा completion cmd_करोne_पूर्णांकr;

	/* eurus event handling */
	काष्ठा workqueue_काष्ठा *event_queue;
	काष्ठा delayed_work event_work;

	/* wl status bits */
	अचिन्हित दीर्घ stat;
	क्रमागत gelic_eurus_auth_method auth_method; /* खोलो/shared */
	क्रमागत gelic_wl_cipher_method group_cipher_method;
	क्रमागत gelic_wl_cipher_method pairwise_cipher_method;
	क्रमागत gelic_wl_wpa_level wpa_level; /* wpa/wpa2 */

	/* association handling */
	काष्ठा mutex assoc_stat_lock;
	काष्ठा delayed_work assoc_work;
	क्रमागत gelic_wl_assoc_state assoc_stat;
	काष्ठा completion assoc_करोne;

	spinlock_t lock;
	u16 ch_info; /* available channels. bit0 = ch1 */
	/* WEP keys */
	u8 key[GELIC_WEP_KEYS][IW_ENCODING_TOKEN_MAX];
	अचिन्हित दीर्घ key_enabled;
	अचिन्हित पूर्णांक key_len[GELIC_WEP_KEYS];
	अचिन्हित पूर्णांक current_key;
	/* WWPA PSK */
	u8 psk[GELIC_WL_EURUS_PSK_MAX_LEN];
	क्रमागत gelic_eurus_wpa_psk_type psk_type;
	अचिन्हित पूर्णांक psk_len;

	u8 essid[IW_ESSID_MAX_SIZE];
	u8 bssid[ETH_ALEN]; /* userland requested */
	u8 active_bssid[ETH_ALEN]; /* associated bssid */
	अचिन्हित पूर्णांक essid_len;

	काष्ठा iw_खुला_data wireless_data;
	काष्ठा iw_statistics iwstat;
पूर्ण;

#घोषणा GELIC_WL_BSS_MAX_ENT 32
#घोषणा GELIC_WL_ASSOC_RETRY 50
अटल अंतरभूत काष्ठा gelic_port *wl_port(काष्ठा gelic_wl_info *wl)
अणु
	वापस container_of((व्योम *)wl, काष्ठा gelic_port, priv);
पूर्ण
अटल अंतरभूत काष्ठा gelic_wl_info *port_wl(काष्ठा gelic_port *port)
अणु
	वापस port_priv(port);
पूर्ण

काष्ठा gelic_eurus_cmd अणु
	काष्ठा work_काष्ठा work;
	काष्ठा gelic_wl_info *wl;
	अचिन्हित पूर्णांक cmd; /* command code */
	u64 tag;
	u64 size;
	व्योम *buffer;
	अचिन्हित पूर्णांक buf_size;
	काष्ठा completion करोne;
	पूर्णांक status;
	u64 cmd_status;
पूर्ण;

/* निजी ioctls to pass PSK */
#घोषणा GELIC_WL_PRIV_SET_PSK		(SIOCIWFIRSTPRIV + 0)
#घोषणा GELIC_WL_PRIV_GET_PSK		(SIOCIWFIRSTPRIV + 1)

पूर्णांक gelic_wl_driver_probe(काष्ठा gelic_card *card);
पूर्णांक gelic_wl_driver_हटाओ(काष्ठा gelic_card *card);
व्योम gelic_wl_पूर्णांकerrupt(काष्ठा net_device *netdev, u64 status);
#पूर्ण_अगर /* _GELIC_WIRELESS_H */
