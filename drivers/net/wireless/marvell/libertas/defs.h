<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This header file contains global स्थिरant/क्रमागत definitions,
 * global variable declaration.
 */
#अगर_अघोषित _LBS_DEFS_H_
#घोषणा _LBS_DEFS_H_

#समावेश <linux/spinlock.h>

#अगर_घोषित CONFIG_LIBERTAS_DEBUG
#घोषणा DEBUG
#घोषणा PROC_DEBUG
#पूर्ण_अगर

#अगर_अघोषित DRV_NAME
#घोषणा DRV_NAME "libertas"
#पूर्ण_अगर


#घोषणा LBS_DEB_ENTER	0x00000001
#घोषणा LBS_DEB_LEAVE	0x00000002
#घोषणा LBS_DEB_MAIN	0x00000004
#घोषणा LBS_DEB_NET	0x00000008
#घोषणा LBS_DEB_MESH	0x00000010
#घोषणा LBS_DEB_WEXT	0x00000020
#घोषणा LBS_DEB_IOCTL	0x00000040
#घोषणा LBS_DEB_SCAN	0x00000080
#घोषणा LBS_DEB_ASSOC	0x00000100
#घोषणा LBS_DEB_JOIN	0x00000200
#घोषणा LBS_DEB_11D	0x00000400
#घोषणा LBS_DEB_DEBUGFS	0x00000800
#घोषणा LBS_DEB_ETHTOOL	0x00001000
#घोषणा LBS_DEB_HOST	0x00002000
#घोषणा LBS_DEB_CMD	0x00004000
#घोषणा LBS_DEB_RX	0x00008000
#घोषणा LBS_DEB_TX	0x00010000
#घोषणा LBS_DEB_USB	0x00020000
#घोषणा LBS_DEB_CS	0x00040000
#घोषणा LBS_DEB_FW	0x00080000
#घोषणा LBS_DEB_THREAD	0x00100000
#घोषणा LBS_DEB_HEX	0x00200000
#घोषणा LBS_DEB_SDIO	0x00400000
#घोषणा LBS_DEB_SYSFS	0x00800000
#घोषणा LBS_DEB_SPI	0x01000000
#घोषणा LBS_DEB_CFG80211 0x02000000

बाह्य अचिन्हित पूर्णांक lbs_debug;

#अगर_घोषित DEBUG
#घोषणा LBS_DEB_LL(grp, grpnam, fmt, args...) \
करो अणु अगर ((lbs_debug & (grp)) == (grp)) \
  prपूर्णांकk(KERN_DEBUG DRV_NAME grpnam ": " fmt, ## args); पूर्ण जबतक (0)
#अन्यथा
#घोषणा LBS_DEB_LL(grp, grpnam, fmt, args...) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा lbs_deb_मुख्य(fmt, args...)      LBS_DEB_LL(LBS_DEB_MAIN, " main", fmt, ##args)
#घोषणा lbs_deb_net(fmt, args...)       LBS_DEB_LL(LBS_DEB_NET, " net", fmt, ##args)
#घोषणा lbs_deb_mesh(fmt, args...)      LBS_DEB_LL(LBS_DEB_MESH, " mesh", fmt, ##args)
#घोषणा lbs_deb_wext(fmt, args...)      LBS_DEB_LL(LBS_DEB_WEXT, " wext", fmt, ##args)
#घोषणा lbs_deb_ioctl(fmt, args...)     LBS_DEB_LL(LBS_DEB_IOCTL, " ioctl", fmt, ##args)
#घोषणा lbs_deb_scan(fmt, args...)      LBS_DEB_LL(LBS_DEB_SCAN, " scan", fmt, ##args)
#घोषणा lbs_deb_assoc(fmt, args...)     LBS_DEB_LL(LBS_DEB_ASSOC, " assoc", fmt, ##args)
#घोषणा lbs_deb_join(fmt, args...)      LBS_DEB_LL(LBS_DEB_JOIN, " join", fmt, ##args)
#घोषणा lbs_deb_11d(fmt, args...)       LBS_DEB_LL(LBS_DEB_11D, " 11d", fmt, ##args)
#घोषणा lbs_deb_debugfs(fmt, args...)   LBS_DEB_LL(LBS_DEB_DEBUGFS, " debugfs", fmt, ##args)
#घोषणा lbs_deb_ethtool(fmt, args...)   LBS_DEB_LL(LBS_DEB_ETHTOOL, " ethtool", fmt, ##args)
#घोषणा lbs_deb_host(fmt, args...)      LBS_DEB_LL(LBS_DEB_HOST, " host", fmt, ##args)
#घोषणा lbs_deb_cmd(fmt, args...)       LBS_DEB_LL(LBS_DEB_CMD, " cmd", fmt, ##args)
#घोषणा lbs_deb_rx(fmt, args...)        LBS_DEB_LL(LBS_DEB_RX, " rx", fmt, ##args)
#घोषणा lbs_deb_tx(fmt, args...)        LBS_DEB_LL(LBS_DEB_TX, " tx", fmt, ##args)
#घोषणा lbs_deb_fw(fmt, args...)        LBS_DEB_LL(LBS_DEB_FW, " fw", fmt, ##args)
#घोषणा lbs_deb_usb(fmt, args...)       LBS_DEB_LL(LBS_DEB_USB, " usb", fmt, ##args)
#घोषणा lbs_deb_usbd(dev, fmt, args...) LBS_DEB_LL(LBS_DEB_USB, " usbd", "%s:" fmt, dev_name(dev), ##args)
#घोषणा lbs_deb_cs(fmt, args...)        LBS_DEB_LL(LBS_DEB_CS, " cs", fmt, ##args)
#घोषणा lbs_deb_thपढ़ो(fmt, args...)    LBS_DEB_LL(LBS_DEB_THREAD, " thread", fmt, ##args)
#घोषणा lbs_deb_sdio(fmt, args...)      LBS_DEB_LL(LBS_DEB_SDIO, " sdio", fmt, ##args)
#घोषणा lbs_deb_sysfs(fmt, args...)     LBS_DEB_LL(LBS_DEB_SYSFS, " sysfs", fmt, ##args)
#घोषणा lbs_deb_spi(fmt, args...)       LBS_DEB_LL(LBS_DEB_SPI, " spi", fmt, ##args)
#घोषणा lbs_deb_cfg80211(fmt, args...)  LBS_DEB_LL(LBS_DEB_CFG80211, " cfg80211", fmt, ##args)

#अगर_घोषित DEBUG
अटल अंतरभूत व्योम lbs_deb_hex(अचिन्हित पूर्णांक grp, स्थिर अक्षर *prompt,
			       स्थिर u8 *buf, पूर्णांक len)
अणु
	पूर्णांक i = 0;

	अगर (len &&
	    (lbs_debug & LBS_DEB_HEX) &&
	    (lbs_debug & grp))
	अणु
		क्रम (i = 1; i <= len; i++) अणु
			अगर ((i & 0xf) == 1) अणु
				अगर (i != 1)
					prपूर्णांकk("\n");
				prपूर्णांकk(DRV_NAME " %s: ", prompt);
			पूर्ण
			prपूर्णांकk("%02x ", (u8) * buf);
			buf++;
		पूर्ण
		prपूर्णांकk("\n");
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा lbs_deb_hex(grp,prompt,buf,len)	करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर



/* Buffer Constants */

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
#घोषणा MRVDRV_ASSOCIATION_TIME_OUT	255
#घोषणा MRVDRV_SNAP_HEADER_LEN          8

#घोषणा	LBS_UPLD_SIZE			2312
#घोषणा DEV_NAME_LEN			32

/* Wake criteria क्रम HOST_SLEEP_CFG command */
#घोषणा EHS_WAKE_ON_BROADCAST_DATA	0x0001
#घोषणा EHS_WAKE_ON_UNICAST_DATA	0x0002
#घोषणा EHS_WAKE_ON_MAC_EVENT		0x0004
#घोषणा EHS_WAKE_ON_MULTICAST_DATA	0x0008
#घोषणा EHS_REMOVE_WAKEUP		0xFFFFFFFF
/* Wake rules क्रम Host_Sleep_CFG command */
#घोषणा WOL_RULE_NET_TYPE_INFRA_OR_IBSS	0x00
#घोषणा WOL_RULE_NET_TYPE_MESH		0x10
#घोषणा WOL_RULE_ADDR_TYPE_BCAST	0x01
#घोषणा WOL_RULE_ADDR_TYPE_MCAST	0x08
#घोषणा WOL_RULE_ADDR_TYPE_UCAST	0x02
#घोषणा WOL_RULE_OP_AND			0x01
#घोषणा WOL_RULE_OP_OR			0x02
#घोषणा WOL_RULE_OP_INVALID		0xFF
#घोषणा WOL_RESULT_VALID_CMD		0
#घोषणा WOL_RESULT_NOSPC_ERR		1
#घोषणा WOL_RESULT_EEXIST_ERR		2

/* Misc स्थिरants */
/* This section defines 802.11 specअगरic contants */

#घोषणा MRVDRV_MAX_BSS_DESCRIPTS		16
#घोषणा MRVDRV_MAX_REGION_CODE			6

#घोषणा MRVDRV_DEFAULT_LISTEN_INTERVAL		10

#घोषणा	MRVDRV_CHANNELS_PER_SCAN		4
#घोषणा	MRVDRV_MAX_CHANNELS_PER_SCAN		14

#घोषणा MRVDRV_MIN_BEACON_INTERVAL		20
#घोषणा MRVDRV_MAX_BEACON_INTERVAL		1000
#घोषणा MRVDRV_BEACON_INTERVAL			100

#घोषणा MARVELL_MESH_IE_LENGTH		9

/*
 * Values used to populate the काष्ठा mrvl_mesh_ie.  The only समय you need this
 * is when enabling the mesh using CMD_MESH_CONFIG.
 */
#घोषणा MARVELL_MESH_IE_TYPE		4
#घोषणा MARVELL_MESH_IE_SUBTYPE		0
#घोषणा MARVELL_MESH_IE_VERSION		0
#घोषणा MARVELL_MESH_PROTO_ID_HWMP	0
#घोषणा MARVELL_MESH_METRIC_ID		0
#घोषणा MARVELL_MESH_CAPABILITY		0

/* INT status Bit Definition */
#घोषणा MRVDRV_TX_DNLD_RDY		0x0001
#घोषणा MRVDRV_RX_UPLD_RDY		0x0002
#घोषणा MRVDRV_CMD_DNLD_RDY		0x0004
#घोषणा MRVDRV_CMD_UPLD_RDY		0x0008
#घोषणा MRVDRV_CARDEVENT		0x0010

/* Automatic TX control शेष levels */
#घोषणा POW_ADAPT_DEFAULT_P0 13
#घोषणा POW_ADAPT_DEFAULT_P1 15
#घोषणा POW_ADAPT_DEFAULT_P2 18
#घोषणा TPC_DEFAULT_P0 5
#घोषणा TPC_DEFAULT_P1 10
#घोषणा TPC_DEFAULT_P2 13

/* TxPD status */

/*
 *	Station firmware use TxPD status field to report final Tx transmit
 *	result, Bit masks are used to present combined situations.
 */

#घोषणा MRVDRV_TxPD_POWER_MGMT_शून्य_PACKET 0x01
#घोषणा MRVDRV_TxPD_POWER_MGMT_LAST_PACKET 0x08

/* Tx mesh flag */
/*
 * Currently we are using normal WDS flag as mesh flag.
 * TODO: change to proper mesh flag when MAC understands it.
 */
#घोषणा TxPD_CONTROL_WDS_FRAME (1<<17)
#घोषणा TxPD_MESH_FRAME TxPD_CONTROL_WDS_FRAME

/* Mesh पूर्णांकerface ID */
#घोषणा MESH_IFACE_ID					0x0001
/* Mesh id should be in bits 14-13-12 */
#घोषणा MESH_IFACE_BIT_OFFSET				0x000c
/* Mesh enable bit in FW capability */
#घोषणा MESH_CAPINFO_ENABLE_MASK			(1<<16)

/* FW definition from Marvell v4 */
#घोषणा MRVL_FW_V4					(0x04)
/* FW definition from Marvell v5 */
#घोषणा MRVL_FW_V5					(0x05)
/* FW definition from Marvell v10 */
#घोषणा MRVL_FW_V10					(0x0a)
/* FW major revision definition */
#घोषणा MRVL_FW_MAJOR_REV(x)				((x)>>24)

/* RxPD status */

#घोषणा MRVDRV_RXPD_STATUS_OK                0x0001

/* RxPD status - Received packet types */
/* Rx mesh flag */
/*
 * Currently we are using normal WDS flag as mesh flag.
 * TODO: change to proper mesh flag when MAC understands it.
 */
#घोषणा RxPD_CONTROL_WDS_FRAME (0x40)
#घोषणा RxPD_MESH_FRAME RxPD_CONTROL_WDS_FRAME

/* RSSI-related defines */
/*
 *	RSSI स्थिरants are used to implement 802.11 RSSI threshold
 *	indication. अगर the Rx packet संकेत got too weak क्रम 5 consecutive
 *	बार, miniport driver (driver) will report this event to wrapper
 */

#घोषणा MRVDRV_NF_DEFAULT_SCAN_VALUE		(-96)

/* RTS/FRAG related defines */
#घोषणा MRVDRV_RTS_MIN_VALUE		0
#घोषणा MRVDRV_RTS_MAX_VALUE		2347
#घोषणा MRVDRV_FRAG_MIN_VALUE		256
#घोषणा MRVDRV_FRAG_MAX_VALUE		2346

/* This is क्रम firmware specअगरic length */
#घोषणा EXTRA_LEN	36

#घोषणा MRVDRV_ETH_TX_PACKET_BUFFER_SIZE \
	(ETH_FRAME_LEN + माप(काष्ठा txpd) + EXTRA_LEN)

#घोषणा MRVDRV_ETH_RX_PACKET_BUFFER_SIZE \
	(ETH_FRAME_LEN + माप(काष्ठा rxpd) \
	 + MRVDRV_SNAP_HEADER_LEN + EXTRA_LEN)

#घोषणा	CMD_F_HOSTCMD		(1 << 0)
#घोषणा FW_CAPINFO_WPA  	(1 << 0)
#घोषणा FW_CAPINFO_PS  		(1 << 1)
#घोषणा FW_CAPINFO_FIRMWARE_UPGRADE	(1 << 13)
#घोषणा FW_CAPINFO_BOOT2_UPGRADE	(1<<14)
#घोषणा FW_CAPINFO_PERSISTENT_CONFIG	(1<<15)

#घोषणा KEY_LEN_WPA_AES			16
#घोषणा KEY_LEN_WPA_TKIP		32
#घोषणा KEY_LEN_WEP_104			13
#घोषणा KEY_LEN_WEP_40			5

#घोषणा RF_ANTENNA_1		0x1
#घोषणा RF_ANTENNA_2		0x2
#घोषणा RF_ANTENNA_AUTO		0xFFFF

#घोषणा	BAND_B			(0x01)
#घोषणा	BAND_G			(0x02)
#घोषणा ALL_802_11_BANDS	(BAND_B | BAND_G)

#घोषणा MAX_RATES			14

#घोषणा	MAX_LEDS			8

/* Global Variable Declaration */
बाह्य स्थिर अक्षर lbs_driver_version[];
बाह्य u16 lbs_region_code_to_index[MRVDRV_MAX_REGION_CODE];


/* ENUM definition */
/* SNRNF_TYPE */
क्रमागत SNRNF_TYPE अणु
	TYPE_BEACON = 0,
	TYPE_RXPD,
	MAX_TYPE_B
पूर्ण;

/* SNRNF_DATA */
क्रमागत SNRNF_DATA अणु
	TYPE_NOAVG = 0,
	TYPE_AVG,
	MAX_TYPE_AVG
पूर्ण;

/* LBS_802_11_POWER_MODE */
क्रमागत LBS_802_11_POWER_MODE अणु
	LBS802_11POWERMODECAM,
	LBS802_11POWERMODEMAX_PSP,
	LBS802_11POWERMODEFAST_PSP,
	/* not a real mode, defined as an upper bound */
	LBS802_11POWEMODEMAX
पूर्ण;

/* PS_STATE */
क्रमागत PS_STATE अणु
	PS_STATE_FULL_POWER,
	PS_STATE_AWAKE,
	PS_STATE_PRE_SLEEP,
	PS_STATE_SLEEP
पूर्ण;

/* DNLD_STATE */
क्रमागत DNLD_STATE अणु
	DNLD_RES_RECEIVED,
	DNLD_DATA_SENT,
	DNLD_CMD_SENT,
	DNLD_BOOTCMD_SENT,
पूर्ण;

/* LBS_MEDIA_STATE */
क्रमागत LBS_MEDIA_STATE अणु
	LBS_CONNECTED,
	LBS_DISCONNECTED
पूर्ण;

/* LBS_802_11_PRIVACY_FILTER */
क्रमागत LBS_802_11_PRIVACY_FILTER अणु
	LBS802_11PRIVFILTERACCEPTALL,
	LBS802_11PRIVFILTER8021XWEP
पूर्ण;

/* mv_ms_type */
क्रमागत mv_ms_type अणु
	MVMS_DAT = 0,
	MVMS_CMD = 1,
	MVMS_TXDONE = 2,
	MVMS_EVENT
पूर्ण;

/* KEY_TYPE_ID */
क्रमागत KEY_TYPE_ID अणु
	KEY_TYPE_ID_WEP = 0,
	KEY_TYPE_ID_TKIP,
	KEY_TYPE_ID_AES
पूर्ण;

/* KEY_INFO_WPA (applies to both TKIP and AES/CCMP) */
क्रमागत KEY_INFO_WPA अणु
	KEY_INFO_WPA_MCAST = 0x01,
	KEY_INFO_WPA_UNICAST = 0x02,
	KEY_INFO_WPA_ENABLED = 0x04
पूर्ण;

/* Default values क्रम fwt commands. */
#घोषणा FWT_DEFAULT_METRIC 0
#घोषणा FWT_DEFAULT_सूची 1
/* Default Rate, 11Mbps */
#घोषणा FWT_DEFAULT_RATE 3
#घोषणा FWT_DEFAULT_SSN 0xffffffff
#घोषणा FWT_DEFAULT_DSN 0
#घोषणा FWT_DEFAULT_HOPCOUNT 0
#घोषणा FWT_DEFAULT_TTL 0
#घोषणा FWT_DEFAULT_EXPIRATION 0
#घोषणा FWT_DEFAULT_SLEEPMODE 0
#घोषणा FWT_DEFAULT_SNR 0

#पूर्ण_अगर
