<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This is part of rtl8187 OpenSource driver.
 * Copyright (C) Andrea Merello 2004-2005  <andrea.merello@gmail.com>
 * Released under the terms of GPL (General Public Licence)
 *
 * Parts of this driver are based on the GPL part of the
 * official realtek driver
 *
 * Parts of this driver are based on the rtl8192 driver skeleton
 * from Patric Schenke & Andres Salomon
 *
 * Parts of this driver are based on the Intel Pro Wireless 2100 GPL driver
 *
 * We want to thank the Authors of those projects and the Ndiswrapper
 * project Authors.
 */

#अगर_अघोषित R8192U_H
#घोषणा R8192U_H

#समावेश <linux/compiler.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ioport.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/usb.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/wireless.h>
#समावेश <linux/समयr.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/पन.स>
#समावेश "ieee80211/ieee80211.h"

#घोषणा RTL8192U
#घोषणा RTL819XU_MODULE_NAME "rtl819xU"
/* HW security */
#घोषणा MAX_KEY_LEN     61
#घोषणा KEY_BUF_SIZE    5

#घोषणा	RX_SMOOTH_FACTOR		20
#घोषणा DMESG(x, a...)  no_prपूर्णांकk(x, ##a)
#घोषणा DMESGW(x, a...) no_prपूर्णांकk(x, ##a)
#घोषणा DMESGE(x, a...) no_prपूर्णांकk(x, ##a)
बाह्य u32 rt_global_debug_component;
#घोषणा RT_TRACE(component, x, args...) \
	करो अणु							\
		अगर (rt_global_debug_component & (component))	\
			pr_debug("RTL8192U: " x "\n", ##args);	\
	पूर्ण जबतक (0)

#घोषणा COMP_TRACE              BIT(0)  /* Function call tracing. */
#घोषणा COMP_DBG                BIT(1)
#घोषणा COMP_INIT               BIT(2)  /* Driver initialization/halt/reset. */

#घोषणा COMP_RECV               BIT(3)  /* Receive data path. */
#घोषणा COMP_SEND               BIT(4)  /* Send data path. */
#घोषणा COMP_IO                 BIT(5)
/* 802.11 Power Save mode or System/Device Power state. */
#घोषणा COMP_POWER              BIT(6)
/* 802.11 link related: join/start BSS, leave BSS. */
#घोषणा COMP_EPROM              BIT(7)
#घोषणा COMP_SWBW               BIT(8)  /* Bandwidth चयन. */
#घोषणा COMP_POWER_TRACKING     BIT(9)  /* 8190 TX Power Tracking */
#घोषणा COMP_TURBO              BIT(10) /* Turbo Mode */
#घोषणा COMP_QOS                BIT(11)
#घोषणा COMP_RATE               BIT(12) /* Rate Adaptive mechanism */
#घोषणा COMP_RM                 BIT(13) /* Radio Measurement */
#घोषणा COMP_DIG                BIT(14)
#घोषणा COMP_PHY                BIT(15)
#घोषणा COMP_CH                 BIT(16) /* Channel setting debug */
#घोषणा COMP_TXAGC              BIT(17) /* Tx घातer */
#घोषणा COMP_HIPWR              BIT(18) /* High Power Mechanism */
#घोषणा COMP_HALDM              BIT(19) /* HW Dynamic Mechanism */
#घोषणा COMP_SEC                BIT(20) /* Event handling */
#घोषणा COMP_LED                BIT(21)
#घोषणा COMP_RF                 BIT(22)
#घोषणा COMP_RXDESC             BIT(23) /* Rx desc inक्रमmation क्रम SD3 debug */

/* 11n or 8190 specअगरic code */

#घोषणा COMP_FIRMWARE           BIT(24) /* Firmware करोwnloading */
#घोषणा COMP_HT                 BIT(25) /* 802.11n HT related inक्रमmation */
#घोषणा COMP_AMSDU              BIT(26) /* A-MSDU Debugging */
#घोषणा COMP_SCAN               BIT(27)
#घोषणा COMP_DOWN               BIT(29) /* rm driver module */
#घोषणा COMP_RESET              BIT(30) /* Silent reset */
#घोषणा COMP_ERR                BIT(31) /* Error out, always on */

#घोषणा RTL819x_DEBUG
#अगर_घोषित RTL819x_DEBUG
#घोषणा RTL8192U_ASSERT(expr) \
	करो अणु								\
		अगर (!(expr)) अणु						\
			pr_debug("Assertion failed! %s, %s, %s, line = %d\n", \
				 #expr, __खाता__, __func__, __LINE__);	\
		पूर्ण							\
	पूर्ण जबतक (0)
/*
 * Debug out data buf.
 * If you want to prपूर्णांक DATA buffer related BA,
 * please set ieee80211_debug_level to DATA|BA
 */
#घोषणा RT_DEBUG_DATA(level, data, datalen) \
	करो अणु								\
		अगर ((rt_global_debug_component & (level)) == (level)) अणु	\
			पूर्णांक i;						\
			u8 *pdata = (u8 *)data;				\
			pr_debug("RTL8192U: %s()\n", __func__);		\
			क्रम (i = 0; i < (पूर्णांक)(datalen); i++) अणु		\
				prपूर्णांकk("%2x ", pdata[i]);               \
				अगर ((i+1)%16 == 0)			\
					prपूर्णांकk("\n");			\
			पूर्ण						\
			prपूर्णांकk("\n");					\
		पूर्ण							\
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा RTL8192U_ASSERT(expr) करो अणुपूर्ण जबतक (0)
#घोषणा RT_DEBUG_DATA(level, data, datalen) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर /* RTL8169_DEBUG */

/* Queue Select Value in TxDesc */
#घोषणा QSLT_BK                                 0x1
#घोषणा QSLT_BE                                 0x0
#घोषणा QSLT_VI                                 0x4
#घोषणा QSLT_VO                                 0x6
#घोषणा QSLT_BEACON                             0x10
#घोषणा QSLT_HIGH                               0x11
#घोषणा QSLT_MGNT                               0x12
#घोषणा QSLT_CMD                                0x13

#घोषणा DESC90_RATE1M                           0x00
#घोषणा DESC90_RATE2M                           0x01
#घोषणा DESC90_RATE5_5M                         0x02
#घोषणा DESC90_RATE11M                          0x03
#घोषणा DESC90_RATE6M                           0x04
#घोषणा DESC90_RATE9M                           0x05
#घोषणा DESC90_RATE12M                          0x06
#घोषणा DESC90_RATE18M                          0x07
#घोषणा DESC90_RATE24M                          0x08
#घोषणा DESC90_RATE36M                          0x09
#घोषणा DESC90_RATE48M                          0x0a
#घोषणा DESC90_RATE54M                          0x0b
#घोषणा DESC90_RATEMCS0                         0x00
#घोषणा DESC90_RATEMCS1                         0x01
#घोषणा DESC90_RATEMCS2                         0x02
#घोषणा DESC90_RATEMCS3                         0x03
#घोषणा DESC90_RATEMCS4                         0x04
#घोषणा DESC90_RATEMCS5                         0x05
#घोषणा DESC90_RATEMCS6                         0x06
#घोषणा DESC90_RATEMCS7                         0x07
#घोषणा DESC90_RATEMCS8                         0x08
#घोषणा DESC90_RATEMCS9                         0x09
#घोषणा DESC90_RATEMCS10                        0x0a
#घोषणा DESC90_RATEMCS11                        0x0b
#घोषणा DESC90_RATEMCS12                        0x0c
#घोषणा DESC90_RATEMCS13                        0x0d
#घोषणा DESC90_RATEMCS14                        0x0e
#घोषणा DESC90_RATEMCS15                        0x0f
#घोषणा DESC90_RATEMCS32                        0x20

#घोषणा RTL819X_DEFAULT_RF_TYPE RF_1T2R

#घोषणा IEEE80211_WATCH_DOG_TIME    2000
#घोषणा		PHY_Beacon_RSSI_SLID_WIN_MAX		10
/* For Tx Power Tracking */
#घोषणा		OFDM_Table_Length	19
#घोषणा	CCK_Table_length	12

/* For rtl819x */
काष्ठा tx_desc_819x_usb अणु
	/* DWORD 0 */
	u16	PktSize;
	u8	Offset;
	u8	Reserved0:3;
	u8	CmdInit:1;
	u8	LastSeg:1;
	u8	FirstSeg:1;
	u8	LINIP:1;
	u8	OWN:1;

	/* DWORD 1 */
	u8	TxFWInfoSize;
	u8	RATid:3;
	u8	DISFB:1;
	u8	USERATE:1;
	u8	MOREFRAG:1;
	u8	NoEnc:1;
	u8	PIFS:1;
	u8	QueueSelect:5;
	u8	NoACM:1;
	u8	Reserved1:2;
	u8	SecCAMID:5;
	u8	SecDescAssign:1;
	u8	SecType:2;

	/* DWORD 2 */
	u16	TxBufferSize;
	u8	ResvForPaddingLen:7;
	u8	Reserved3:1;
	u8	Reserved4;

	/* DWORD 3, 4, 5 */
	u32	Reserved5;
	u32	Reserved6;
	u32	Reserved7;
पूर्ण;

काष्ठा tx_desc_cmd_819x_usb अणु
	/* DWORD 0 */
	u16	Reserved0;
	u8	Reserved1;
	u8	Reserved2:3;
	u8	CmdInit:1;
	u8	LastSeg:1;
	u8	FirstSeg:1;
	u8	LINIP:1;
	u8	OWN:1;

	/* DOWRD 1 */
	u8	TxFWInfoSize;
	u8	Reserved3;
	u8	QueueSelect;
	u8	Reserved4;

	/* DOWRD 2 */
	u16	TxBufferSize;
	u16	Reserved5;

	/* DWORD 3, 4, 5 */
	u32	Reserved6;
	u32	Reserved7;
	u32	Reserved8;
पूर्ण;

काष्ठा tx_fwinfo_819x_usb अणु
	/* DOWRD 0 */
	u8	TxRate:7;
	u8	CtsEnable:1;
	u8	RtsRate:7;
	u8	RtsEnable:1;
	u8	TxHT:1;
	u8	Short:1;        /* Error out, always on */
	u8	TxBandwidth:1;	/* Used क्रम HT MCS rate only */
	u8	TxSubCarrier:2; /* Used क्रम legacy OFDM rate only */
	u8	STBC:2;
	u8	AllowAggregation:1;
	/* Interpret RtsRate field as high throughput data rate */
	u8	RtsHT:1;
	u8	RtsShort:1;     /* Short PLCP क्रम CCK or लघु GI क्रम 11n MCS */
	u8	RtsBandwidth:1;	/* Used क्रम HT MCS rate only */
	u8	RtsSubcarrier:2;/* Used क्रम legacy OFDM rate only */
	u8	RtsSTBC:2;
	/* Enable firmware to recalculate and assign packet duration */
	u8	EnableCPUDur:1;

	/* DWORD 1 */
	u32	RxMF:2;
	u32	RxAMD:3;
	/* 1 indicate Tx info gathered by firmware and वापसed by Rx Cmd */
	u32	TxPerPktInfoFeedback:1;
	u32	Reserved1:2;
	u32	TxAGCOffSet:4;
	u32	TxAGCSign:1;
	u32	Tx_INFO_RSVD:6;
	u32	PacketID:13;
पूर्ण;

काष्ठा rtl8192_rx_info अणु
	काष्ठा urb *urb;
	काष्ठा net_device *dev;
	u8 out_pipe;
पूर्ण;

काष्ठा rx_desc_819x_usb अणु
	/* DOWRD 0 */
	u16                 Length:14;
	u16                 CRC32:1;
	u16                 ICV:1;
	u8                  RxDrvInfoSize;
	u8                  Shअगरt:2;
	u8                  PHYStatus:1;
	u8                  SWDec:1;
	u8                  Reserved1:4;

	/* DWORD 1 */
	u32                 Reserved2;
पूर्ण;

काष्ठा rx_drvinfo_819x_usb अणु
	/* DWORD 0 */
	u16                 Reserved1:12;
	u16                 PartAggr:1;
	u16                 FirstAGGR:1;
	u16                 Reserved2:2;

	u8                  RxRate:7;
	u8                  RxHT:1;

	u8                  BW:1;
	u8                  SPLCP:1;
	u8                  Reserved3:2;
	u8                  PAM:1;
	u8                  Mcast:1;
	u8                  Bcast:1;
	u8                  Reserved4:1;

	/* DWORD 1 */
	u32                  TSFL;

पूर्ण;

/* Support till 64 bit bus width OS */
#घोषणा MAX_DEV_ADDR_SIZE		8
/* For RTL8190 */
#घोषणा MAX_FIRMWARE_INFORMATION_SIZE   32
#घोषणा MAX_802_11_HEADER_LENGTH        (40 + MAX_FIRMWARE_INFORMATION_SIZE)
#घोषणा ENCRYPTION_MAX_OVERHEAD		128
#घोषणा	USB_HWDESC_HEADER_LEN		माप(काष्ठा tx_desc_819x_usb)
#घोषणा TX_PACKET_SHIFT_BYTES		(USB_HWDESC_HEADER_LEN + माप(काष्ठा tx_fwinfo_819x_usb))
#घोषणा MAX_FRAGMENT_COUNT		8
#अगर_घोषित USB_TX_DRIVER_AGGREGATION_ENABLE
#घोषणा MAX_TRANSMIT_BUFFER_SIZE			32000
#अन्यथा
#घोषणा MAX_TRANSMIT_BUFFER_SIZE			8000
#पूर्ण_अगर
/* Octets क्रम crc32 (FCS, ICV) */
#घोषणा scrclng					4

क्रमागत rf_op_type अणु
	RF_OP_By_SW_3wire = 0,
	RF_OP_By_FW,
	RF_OP_MAX
पूर्ण;

/* 8190 Loopback Mode definition */
प्रकार क्रमागत _rtl819xUsb_loopback अणु
	RTL819xU_NO_LOOPBACK = 0,
	RTL819xU_MAC_LOOPBACK = 1,
	RTL819xU_DMA_LOOPBACK = 2,
	RTL819xU_CCK_LOOPBACK = 3,
पूर्ण rtl819xUsb_loopback_e;

/* due to rtl8192 firmware */
प्रकार क्रमागत _desc_packet_type_e अणु
	DESC_PACKET_TYPE_INIT = 0,
	DESC_PACKET_TYPE_NORMAL = 1,
पूर्ण desc_packet_type_e;

प्रकार क्रमागत _firmware_status अणु
	FW_STATUS_0_INIT = 0,
	FW_STATUS_1_MOVE_BOOT_CODE = 1,
	FW_STATUS_2_MOVE_MAIN_CODE = 2,
	FW_STATUS_3_TURNON_CPU = 3,
	FW_STATUS_4_MOVE_DATA_CODE = 4,
	FW_STATUS_5_READY = 5,
पूर्ण firmware_status_e;

प्रकार काष्ठा _fw_seg_container अणु
	u16	seg_size;
	u8	*seg_ptr;
पूर्ण fw_seg_container, *pfw_seg_container;
प्रकार काष्ठा _rt_firmware अणु
	firmware_status_e firmware_status;
	u16               cmdpacket_frag_threshold;
#घोषणा RTL8190_MAX_FIRMWARE_CODE_SIZE  64000
	u8                firmware_buf[RTL8190_MAX_FIRMWARE_CODE_SIZE];
	u16               firmware_buf_size;
पूर्ण rt_firmware, *prt_firmware;

/* Add this to 9100 bytes to receive A-MSDU from RT-AP */
#घोषणा MAX_RECEIVE_BUFFER_SIZE	9100

प्रकार काष्ठा _rt_firmware_info_819xUsb अणु
	u8		sz_info[16];
पूर्ण rt_firmware_info_819xUsb, *prt_firmware_info_819xUsb;

/* Firmware Queue Layout */
#घोषणा NUM_OF_FIRMWARE_QUEUE		10
#घोषणा NUM_OF_PAGES_IN_FW		0x100

#अगर_घोषित USE_ONE_PIPE
#घोषणा NUM_OF_PAGE_IN_FW_QUEUE_BE	0x000
#घोषणा NUM_OF_PAGE_IN_FW_QUEUE_BK	0x000
#घोषणा NUM_OF_PAGE_IN_FW_QUEUE_VI	0x0ff
#घोषणा NUM_OF_PAGE_IN_FW_QUEUE_VO	0x000
#घोषणा NUM_OF_PAGE_IN_FW_QUEUE_HCCA	0
#घोषणा NUM_OF_PAGE_IN_FW_QUEUE_CMD	0x0
#घोषणा NUM_OF_PAGE_IN_FW_QUEUE_MGNT	0x00
#घोषणा NUM_OF_PAGE_IN_FW_QUEUE_HIGH	0
#घोषणा NUM_OF_PAGE_IN_FW_QUEUE_BCN	0x0
#घोषणा NUM_OF_PAGE_IN_FW_QUEUE_PUB	0x00
#अन्यथा

#घोषणा NUM_OF_PAGE_IN_FW_QUEUE_BE	0x020
#घोषणा NUM_OF_PAGE_IN_FW_QUEUE_BK	0x020
#घोषणा NUM_OF_PAGE_IN_FW_QUEUE_VI	0x040
#घोषणा NUM_OF_PAGE_IN_FW_QUEUE_VO	0x040
#घोषणा NUM_OF_PAGE_IN_FW_QUEUE_HCCA	0
#घोषणा NUM_OF_PAGE_IN_FW_QUEUE_CMD	0x4
#घोषणा NUM_OF_PAGE_IN_FW_QUEUE_MGNT	0x20
#घोषणा NUM_OF_PAGE_IN_FW_QUEUE_HIGH	0
#घोषणा NUM_OF_PAGE_IN_FW_QUEUE_BCN	0x4
#घोषणा NUM_OF_PAGE_IN_FW_QUEUE_PUB	0x18

#पूर्ण_अगर

#घोषणा APPLIED_RESERVED_QUEUE_IN_FW	0x80000000
#घोषणा RSVD_FW_QUEUE_PAGE_BK_SHIFT	0x00
#घोषणा RSVD_FW_QUEUE_PAGE_BE_SHIFT	0x08
#घोषणा RSVD_FW_QUEUE_PAGE_VI_SHIFT	0x10
#घोषणा RSVD_FW_QUEUE_PAGE_VO_SHIFT	0x18
#घोषणा RSVD_FW_QUEUE_PAGE_MGNT_SHIFT	0x10
#घोषणा RSVD_FW_QUEUE_PAGE_CMD_SHIFT	0x08
#घोषणा RSVD_FW_QUEUE_PAGE_BCN_SHIFT	0x00
#घोषणा RSVD_FW_QUEUE_PAGE_PUB_SHIFT	0x08

/*
 * =================================================================
 * =================================================================
 */

#घोषणा EPROM_93c46 0
#घोषणा EPROM_93c56 1

#घोषणा DEFAULT_FRAG_THRESHOLD 2342U
#घोषणा MIN_FRAG_THRESHOLD     256U
#घोषणा DEFAULT_BEACONINTERVAL 0x64U
#घोषणा DEFAULT_BEACON_ESSID "Rtl819xU"

#घोषणा DEFAULT_SSID ""
#घोषणा DEFAULT_RETRY_RTS 7
#घोषणा DEFAULT_RETRY_DATA 7
#घोषणा PRISM_HDR_SIZE 64

#घोषणा		PHY_RSSI_SLID_WIN_MAX				100

प्रकार क्रमागत _WIRELESS_MODE अणु
	WIRELESS_MODE_UNKNOWN = 0x00,
	WIRELESS_MODE_A = 0x01,
	WIRELESS_MODE_B = 0x02,
	WIRELESS_MODE_G = 0x04,
	WIRELESS_MODE_AUTO = 0x08,
	WIRELESS_MODE_N_24G = 0x10,
	WIRELESS_MODE_N_5G = 0x20
पूर्ण WIRELESS_MODE;

#घोषणा RTL_IOCTL_WPA_SUPPLICANT		(SIOCIWFIRSTPRIV + 30)

प्रकार काष्ठा buffer अणु
	काष्ठा buffer *next;
	u32 *buf;

पूर्ण buffer;

प्रकार काष्ठा rtl_reg_debug अणु
	अचिन्हित पूर्णांक  cmd;
	काष्ठा अणु
		अचिन्हित अक्षर type;
		अचिन्हित अक्षर addr;
		अचिन्हित अक्षर page;
		अचिन्हित अक्षर length;
	पूर्ण head;
	अचिन्हित अक्षर buf[0xff];
पूर्ण rtl_reg_debug;

प्रकार काष्ठा _rt_9x_tx_rate_history अणु
	u32             cck[4];
	u32             ofdm[8];
	u32             ht_mcs[4][16];
पूर्ण rt_tx_rahis_t, *prt_tx_rahis_t;
प्रकार काष्ठा _RT_SMOOTH_DATA_4RF अणु
	s8    elements[4][100]; /* array to store values */
	u32     index;            /* index to current array to store */
	u32     TotalNum;         /* num of valid elements */
	u32     TotalVal[4];      /* sum of valid elements */
पूर्ण RT_SMOOTH_DATA_4RF, *PRT_SMOOTH_DATA_4RF;

/* This maybe changed क्रम D-cut larger aggregation size */
#घोषणा MAX_8192U_RX_SIZE			8192
/* Stats seems messed up, clean it ASAP */
प्रकार काष्ठा Stats अणु
	अचिन्हित दीर्घ txrdu;
	अचिन्हित दीर्घ rxok;
	अचिन्हित दीर्घ rxframgment;
	अचिन्हित दीर्घ rxurberr;
	अचिन्हित दीर्घ rxstaterr;
	/* 0: Total, 1: OK, 2: CRC, 3: ICV */
	अचिन्हित दीर्घ received_rate_histogram[4][32];
	/* 0: Long preamble/GI, 1: Short preamble/GI */
	अचिन्हित दीर्घ received_preamble_GI[2][32];
	/* level: (<4K), (4K~8K), (8K~16K), (16K~32K), (32K~64K) */
	अचिन्हित दीर्घ rx_AMPDUsize_histogram[5];
	/* level: (<5), (5~10), (10~20), (20~40), (>40) */
	अचिन्हित दीर्घ rx_AMPDUnum_histogram[5];
	अचिन्हित दीर्घ numpacket_matchbssid;
	अचिन्हित दीर्घ numpacket_toself;
	अचिन्हित दीर्घ num_process_phyinfo;
	अचिन्हित दीर्घ numqry_phystatus;
	अचिन्हित दीर्घ numqry_phystatusCCK;
	अचिन्हित दीर्घ numqry_phystatusHT;
	/* 0: 20M, 1: funn40M, 2: upper20M, 3: lower20M, 4: duplicate */
	अचिन्हित दीर्घ received_bwtype[5];
	अचिन्हित दीर्घ txnperr;
	अचिन्हित दीर्घ txnpdrop;
	अचिन्हित दीर्घ txresumed;
	अचिन्हित दीर्घ txnpokपूर्णांक;
	अचिन्हित दीर्घ txoverflow;
	अचिन्हित दीर्घ txlpokपूर्णांक;
	अचिन्हित दीर्घ txlpdrop;
	अचिन्हित दीर्घ txlperr;
	अचिन्हित दीर्घ txbeokपूर्णांक;
	अचिन्हित दीर्घ txbedrop;
	अचिन्हित दीर्घ txbeerr;
	अचिन्हित दीर्घ txbkokपूर्णांक;
	अचिन्हित दीर्घ txbkdrop;
	अचिन्हित दीर्घ txbkerr;
	अचिन्हित दीर्घ txviokपूर्णांक;
	अचिन्हित दीर्घ txvidrop;
	अचिन्हित दीर्घ txvierr;
	अचिन्हित दीर्घ txvookपूर्णांक;
	अचिन्हित दीर्घ txvodrop;
	अचिन्हित दीर्घ txvoerr;
	अचिन्हित दीर्घ txbeaconokपूर्णांक;
	अचिन्हित दीर्घ txbeacondrop;
	अचिन्हित दीर्घ txbeaconerr;
	अचिन्हित दीर्घ txmanageokपूर्णांक;
	अचिन्हित दीर्घ txmanagedrop;
	अचिन्हित दीर्घ txmanageerr;
	अचिन्हित दीर्घ txdatapkt;
	अचिन्हित दीर्घ txfeedback;
	अचिन्हित दीर्घ txfeedbackok;

	अचिन्हित दीर्घ txoktotal;
	अचिन्हित दीर्घ txokbytestotal;
	अचिन्हित दीर्घ txokinperiod;
	अचिन्हित दीर्घ txmulticast;
	अचिन्हित दीर्घ txbytesmulticast;
	अचिन्हित दीर्घ txbroadcast;
	अचिन्हित दीर्घ txbytesbroadcast;
	अचिन्हित दीर्घ txunicast;
	अचिन्हित दीर्घ txbytesunicast;

	अचिन्हित दीर्घ rxoktotal;
	अचिन्हित दीर्घ rxbytesunicast;
	अचिन्हित दीर्घ txfeedbackfail;
	अचिन्हित दीर्घ txerrtotal;
	अचिन्हित दीर्घ txerrbytestotal;
	अचिन्हित दीर्घ txerrmulticast;
	अचिन्हित दीर्घ txerrbroadcast;
	अचिन्हित दीर्घ txerrunicast;
	अचिन्हित दीर्घ txretrycount;
	अचिन्हित दीर्घ txfeedbackretry;
	u8	      last_packet_rate;
	अचिन्हित दीर्घ slide_संकेत_strength[100];
	अचिन्हित दीर्घ slide_evm[100];
	/* For recording sliding winकरोw's RSSI value */
	अचिन्हित दीर्घ slide_rssi_total;
	/* For recording sliding winकरोw's EVM value */
	अचिन्हित दीर्घ slide_evm_total;
	/* Transक्रमmed in dbm. Beautअगरied संकेत strength क्रम UI, not correct */
	दीर्घ संकेत_strength;
	दीर्घ संकेत_quality;
	दीर्घ last_संकेत_strength_inpercent;
	/* Correct smoothed ss in dbm, only used in driver
	 * to report real घातer now
	 */
	दीर्घ recv_संकेत_घातer;
	u8 rx_rssi_percentage[4];
	u8 rx_evm_percentage[2];
	दीर्घ rxSNRdB[4];
	rt_tx_rahis_t txrate;
	/* For beacon RSSI */
	u32 Slide_Beacon_pwdb[100];
	u32 Slide_Beacon_Total;
	RT_SMOOTH_DATA_4RF              cck_adc_pwdb;

	u32	CurrentShowTxate;
पूर्ण Stats;

/* Bandwidth Offset */
#घोषणा HAL_PRIME_CHNL_OFFSET_DONT_CARE		0
#घोषणा HAL_PRIME_CHNL_OFFSET_LOWER			1
#घोषणा HAL_PRIME_CHNL_OFFSET_UPPER			2

प्रकार काष्ठा	ChnlAccessSetting अणु
	u16 SIFS_Timer;
	u16 DIFS_Timer;
	u16 SlotTimeTimer;
	u16 EIFS_Timer;
	u16 CWminIndex;
	u16 CWmaxIndex;
पूर्ण *PCHANNEL_ACCESS_SETTING, CHANNEL_ACCESS_SETTING;

प्रकार काष्ठा _BB_REGISTER_DEFINITION अणु
	/* set software control:        0x870~0x877 [8 bytes]  */
	u32 rfपूर्णांकfs;
	/* पढ़ोback data:               0x8e0~0x8e7 [8 bytes]  */
	u32 rfपूर्णांकfi;
	/* output data:                 0x860~0x86f [16 bytes] */
	u32 rfपूर्णांकfo;
	/* output enable:               0x860~0x86f [16 bytes] */
	u32 rfपूर्णांकfe;
	/* LSSI data:                   0x840~0x84f [16 bytes] */
	u32 rf3wireOffset;
	/* BB Band Select:              0x878~0x87f [8 bytes]  */
	u32 rfLSSI_Select;
	/* Tx gain stage:               0x80c~0x80f [4 bytes]  */
	u32 rfTxGainStage;
	/* wire parameter control1:     0x820~0x823, 0x828~0x82b,
	 *                              0x830~0x833, 0x838~0x83b [16 bytes]
	 */
	u32 rfHSSIPara1;
	/* wire parameter control2:     0x824~0x827, 0x82c~0x82f,
	 *                              0x834~0x837, 0x83c~0x83f [16 bytes]
	 */
	u32 rfHSSIPara2;
	/* Tx Rx antenna control:       0x858~0x85f [16 bytes] */
	u32 rfSwitchControl;
	/* AGC parameter control1:	0xc50~0xc53, 0xc58~0xc5b,
	 *                              0xc60~0xc63, 0xc68~0xc6b [16 bytes]
	 */
	u32 rfAGCControl1;
	/* AGC parameter control2:      0xc54~0xc57, 0xc5c~0xc5f,
	 *                              0xc64~0xc67, 0xc6c~0xc6f [16 bytes]
	 */
	u32 rfAGCControl2;
	/* OFDM Rx IQ imbalance matrix:	0xc14~0xc17, 0xc1c~0xc1f,
	 *                              0xc24~0xc27, 0xc2c~0xc2f [16 bytes]
	 */
	u32 rfRxIQImbalance;
	/* Rx IQ DC offset and Rx digital filter, Rx DC notch filter:
	 *                              0xc10~0xc13, 0xc18~0xc1b,
	 *                              0xc20~0xc23, 0xc28~0xc2b [16 bytes]
	 */
	u32 rfRxAFE;
	/* OFDM Tx IQ imbalance matrix:	0xc80~0xc83, 0xc88~0xc8b,
	 *                              0xc90~0xc93, 0xc98~0xc9b [16 bytes]
	 */
	u32 rfTxIQImbalance;
	/* Tx IQ DC Offset and Tx DFIR type:
	 *                              0xc84~0xc87, 0xc8c~0xc8f,
	 *                              0xc94~0xc97, 0xc9c~0xc9f [16 bytes]
	 */
	u32 rfTxAFE;
	/* LSSI RF पढ़ोback data:       0x8a0~0x8af [16 bytes] */
	u32 rfLSSIReadBack;
पूर्ण BB_REGISTER_DEFINITION_T, *PBB_REGISTER_DEFINITION_T;

प्रकार क्रमागत _RT_RF_TYPE_819xU अणु
	RF_TYPE_MIN = 0,
	RF_8225,
	RF_8256,
	RF_8258,
	RF_PSEUDO_11N = 4,
पूर्ण RT_RF_TYPE_819xU, *PRT_RF_TYPE_819xU;

/* 2007/10/08 MH Define RATR state. */
क्रमागत dynamic_ratr_state अणु
	DM_RATR_STA_HIGH = 0,
	DM_RATR_STA_MIDDLE = 1,
	DM_RATR_STA_LOW = 2,
	DM_RATR_STA_MAX
पूर्ण;

प्रकार काष्ठा _rate_adaptive अणु
	u8				rate_adaptive_disabled;
	क्रमागत dynamic_ratr_state		ratr_state;
	u16				reserve;

	u32				high_rssi_thresh_क्रम_ra;
	u32				high2low_rssi_thresh_क्रम_ra;
	u8				low2high_rssi_thresh_क्रम_ra40M;
	u32				low_rssi_thresh_क्रम_ra40M;
	u8				low2high_rssi_thresh_क्रम_ra20M;
	u32				low_rssi_thresh_क्रम_ra20M;
	u32				upper_rssi_threshold_ratr;
	u32				middle_rssi_threshold_ratr;
	u32				low_rssi_threshold_ratr;
	u32				low_rssi_threshold_ratr_40M;
	u32				low_rssi_threshold_ratr_20M;
	u8				ping_rssi_enable;
	u32				ping_rssi_ratr;
	u32				ping_rssi_thresh_क्रम_ra;
	u32				last_ratr;

पूर्ण rate_adaptive, *prate_adaptive;

#घोषणा TxBBGainTableLength 37
#घोषणा	CCKTxBBGainTableLength 23

प्रकार काष्ठा _txbbgain_काष्ठा अणु
	दीर्घ	txbb_iq_amplअगरygain;
	u32	txbbgain_value;
पूर्ण txbbgain_काष्ठा, *ptxbbgain_काष्ठा;

प्रकार काष्ठा _ccktxbbgain_काष्ठा अणु
	/* The value is from a22 to a29, one byte one समय is much safer */
	u8	ccktxbb_valuearray[8];
पूर्ण ccktxbbgain_काष्ठा, *pccktxbbgain_काष्ठा;

प्रकार काष्ठा _init_gain अणु
	u8				xaagccore1;
	u8				xbagccore1;
	u8				xcagccore1;
	u8				xdagccore1;
	u8				cca;

पूर्ण init_gain, *pinit_gain;

प्रकार काष्ठा _phy_ofdm_rx_status_report_819xusb अणु
	u8	trsw_gain_X[4];
	u8	pwdb_all;
	u8	cfosho_X[4];
	u8	cfotail_X[4];
	u8	rxevm_X[2];
	u8	rxsnr_X[4];
	u8	pdsnr_X[2];
	u8	csi_current_X[2];
	u8	csi_target_X[2];
	u8	sigevm;
	u8	max_ex_pwr;
	u8	sgi_en;
	u8  rxsc_sgien_exflg;
पूर्ण phy_sts_ofdm_819xusb_t;

प्रकार काष्ठा _phy_cck_rx_status_report_819xusb अणु
	/* For CCK rate descriptor. This is an अचिन्हित 8:1 variable.
	 * LSB bit presend 0.5. And MSB 7 bts presend a चिन्हित value.
	 * Range from -64~+63.5.
	 */
	u8	adc_pwdb_X[4];
	u8	sq_rpt;
	u8	cck_agc_rpt;
पूर्ण phy_sts_cck_819xusb_t;

काष्ठा phy_ofdm_rx_status_rxsc_sgien_exपूर्णांकfflag अणु
	u8			reserved:4;
	u8			rxsc:2;
	u8			sgi_en:1;
	u8			ex_पूर्णांकf_flag:1;
पूर्ण;

प्रकार क्रमागत _RT_CUSTOMER_ID अणु
	RT_CID_DEFAULT = 0,
	RT_CID_8187_ALPHA0 = 1,
	RT_CID_8187_SERCOMM_PS = 2,
	RT_CID_8187_HW_LED = 3,
	RT_CID_8187_NETGEAR = 4,
	RT_CID_WHQL = 5,
	RT_CID_819x_CAMEO  = 6,
	RT_CID_819x_RUNTOP = 7,
	RT_CID_819x_Senao = 8,
	RT_CID_TOSHIBA = 9,
	RT_CID_819x_Netcore = 10,
	RT_CID_Nettronix = 11,
	RT_CID_DLINK = 12,
	RT_CID_PRONET = 13,
पूर्ण RT_CUSTOMER_ID, *PRT_CUSTOMER_ID;

/*
 * ==========================================================================
 * LED customization.
 * ==========================================================================
 */

प्रकार	क्रमागत _LED_STRATEGY_8190 अणु
	SW_LED_MODE0, /* SW control 1 LED via GPIO0. It is शेष option. */
	SW_LED_MODE1, /* SW control क्रम PCI Express */
	SW_LED_MODE2, /* SW control क्रम Cameo. */
	SW_LED_MODE3, /* SW control क्रम RunTop. */
	SW_LED_MODE4, /* SW control क्रम Netcore. */
	/* HW control 2 LEDs, LED0 and LED1 (4 dअगरferent control modes) */
	HW_LED,
पूर्ण LED_STRATEGY_8190, *PLED_STRATEGY_8190;

प्रकार क्रमागत _RESET_TYPE अणु
	RESET_TYPE_NORESET = 0x00,
	RESET_TYPE_NORMAL = 0x01,
	RESET_TYPE_SILENT = 0x02
पूर्ण RESET_TYPE;

/* The simple tx command OP code. */
प्रकार क्रमागत _tag_TxCmd_Config_Index अणु
	TXCMD_TXRA_HISTORY_CTRL				= 0xFF900000,
	TXCMD_RESET_TX_PKT_BUFF				= 0xFF900001,
	TXCMD_RESET_RX_PKT_BUFF				= 0xFF900002,
	TXCMD_SET_TX_DURATION				= 0xFF900003,
	TXCMD_SET_RX_RSSI						= 0xFF900004,
	TXCMD_SET_TX_PWR_TRACKING			= 0xFF900005,
	TXCMD_XXXX_CTRL,
पूर्ण DCMD_TXCMD_OP;

क्रमागत version_819xu अणु
	VERSION_819XU_A, // A-cut
	VERSION_819XU_B, // B-cut
	VERSION_819XU_C,// C-cut
पूर्ण;

//added क्रम dअगरferent RF type
क्रमागत rt_rf_type अणु
	RF_1T2R = 0,
	RF_2T4R,
पूर्ण;

प्रकार काष्ठा r8192_priv अणु
	काष्ठा usb_device *udev;
	/* For मुख्यtain info from eeprom */
	लघु epromtype;
	u16 eeprom_vid;
	u16 eeprom_pid;
	u8  eeprom_CustomerID;
	u8  eeprom_ChannelPlan;
	RT_CUSTOMER_ID CustomerID;
	LED_STRATEGY_8190	LedStrategy;
	u8  txqueue_to_outpipemap[9];
	पूर्णांक irq;
	काष्ठा ieee80211_device *ieee80211;

	/* O: rtl8192, 1: rtl8185 V B/C, 2: rtl8185 V D */
	लघु card_8192;
	/* If TCR reports card V B/C, this discriminates */
	क्रमागत version_819xu card_8192_version;
	लघु enable_gpio0;
	क्रमागत card_type अणु
		PCI, MINIPCI, CARDBUS, USB
	पूर्ण card_type;
	लघु hw_plcp_len;
	लघु plcp_preamble_mode;

	spinlock_t irq_lock;
	spinlock_t tx_lock;
	काष्ठा mutex mutex;

	u16 irq_mask;
	लघु chan;
	लघु sens;
	लघु max_sens;

	लघु up;
	/* If 1, allow bad crc frame, reception in monitor mode */
	लघु crcmon;

	काष्ठा mutex wx_mutex;

	क्रमागत rt_rf_type   rf_type;	    /* 0: 1T2R, 1: 2T4R */
	RT_RF_TYPE_819xU rf_chip;

	लघु (*rf_set_sens)(काष्ठा net_device *dev, लघु sens);
	u8 (*rf_set_chan)(काष्ठा net_device *dev, u8 ch);
	व्योम (*rf_बंद)(काष्ठा net_device *dev);
	व्योम (*rf_init)(काष्ठा net_device *dev);
	लघु promisc;
	/* Stats */
	काष्ठा Stats stats;
	काष्ठा iw_statistics wstats;

	/* RX stuff */
	काष्ठा urb **rx_urb;
	काष्ठा urb **rx_cmd_urb;
#अगर_घोषित THOMAS_BEACON
	u32 *oldaddr;
#पूर्ण_अगर
#अगर_घोषित THOMAS_TASKLET
	atomic_t irt_counter; /* count क्रम irq_rx_tasklet */
#पूर्ण_अगर
#अगर_घोषित JACKSON_NEW_RX
	काष्ठा sk_buff **pp_rxskb;
	पूर्णांक     rx_inx;
#पूर्ण_अगर

	काष्ठा sk_buff_head rx_queue;
	काष्ठा sk_buff_head skb_queue;
	काष्ठा work_काष्ठा qos_activate;
	लघु  tx_urb_index;
	atomic_t tx_pending[0x10]; /* UART_PRIORITY + 1 */

	काष्ठा tasklet_काष्ठा irq_rx_tasklet;
	काष्ठा urb *rxurb_task;

	/* Tx Related variables */
	u16	ShortRetryLimit;
	u16	LongRetryLimit;
	u32	TransmitConfig;
	u8	RegCWinMin;	/* For turbo mode CW adaptive */

	u32     LastRxDescTSFHigh;
	u32     LastRxDescTSFLow;

	/* Rx Related variables */
	u16	EarlyRxThreshold;
	u32	ReceiveConfig;
	u8	AcmControl;

	u8	RFProgType;

	u8 retry_data;
	u8 retry_rts;
	u16 rts;

	काष्ठा	ChnlAccessSetting  ChannelAccessSetting;
	काष्ठा work_काष्ठा reset_wq;

/**********************************************************/
	/* For rtl819xUsb */
	u16     basic_rate;
	u8      लघु_preamble;
	u8      slot_समय;
	bool	bDcut;
	bool bCurrentRxAggrEnable;
	क्रमागत rf_op_type Rf_Mode;	/* For Firmware RF -R/W चयन */
	prt_firmware		pFirmware;
	rtl819xUsb_loopback_e	LoopbackMode;
	u16 EEPROMTxPowerDअगरf;
	u8 EEPROMThermalMeter;
	u8 EEPROMPwDअगरf;
	u8 EEPROMCrystalCap;
	u8 EEPROM_Def_Ver;
	u8 EEPROMTxPowerLevelCCK;		/* CCK channel 1~14 */
	u8 EEPROMTxPowerLevelCCK_V1[3];
	u8 EEPROMTxPowerLevelOFDM24G[3];	/* OFDM 2.4G channel 1~14 */
	u8 EEPROMTxPowerLevelOFDM5G[24];	/* OFDM 5G */

	/* PHY related */
	BB_REGISTER_DEFINITION_T PHYRegDef[4];	/* Radio A/B/C/D */
	/* Read/ग_लिखो are allow क्रम following hardware inक्रमmation variables */
	u32	MCSTxPowerLevelOriginalOffset[6];
	u32	CCKTxPowerLevelOriginalOffset;
	u8	TxPowerLevelCCK[14];		/* CCK channel 1~14 */
	u8	TxPowerLevelOFDM24G[14];	/* OFDM 2.4G channel 1~14 */
	u8	TxPowerLevelOFDM5G[14];		/* OFDM 5G */
	u32	Pwr_Track;
	u8	TxPowerDअगरf;
	u8	AntennaTxPwDअगरf[2]; /* Antenna gain offset, 0: B, 1: C, 2: D */
	u8	CrystalCap;
	u8	ThermalMeter[2];    /* index 0: RFIC0, index 1: RFIC1 */

	u8	CckPwEnl;
	/* Use to calculate PWBD */
	u8	bCckHighPower;
	दीर्घ	undecorated_smoothed_pwdb;

	/* For set channel */
	u8	SwChnlInProgress;
	u8	SwChnlStage;
	u8	SwChnlStep;
	u8	SetBWModeInProgress;
	क्रमागत ht_channel_width 	CurrentChannelBW;
	u8      ChannelPlan;
	/* 8190 40MHz mode */
	/* Control channel sub-carrier */
	u8	nCur40MhzPrimeSC;
	/* Test क्रम लघुen RF configuration समय.
	 * We save RF reg0 in this variable to reduce RF पढ़ोing.
	 */
	u32					RfReg0Value[4];
	u8					NumTotalRFPath;
	bool				brfpath_rxenable[4];
	/* RF set related */
	bool				SetRFPowerStateInProgress;
	काष्ठा समयr_list watch_करोg_समयr;

	/* For dynamic mechanism */
	/* Tx Power Control क्रम Near/Far Range */
	bool	bdynamic_txघातer;
	bool	bDynamicTxHighPower;
	bool	bDynamicTxLowPower;
	bool	bLastDTPFlag_High;
	bool	bLastDTPFlag_Low;

	bool	bstore_last_dtpflag;
	/* Define to discriminate on High घातer State or
	 * on sitesurvey to change Tx gain index
	 */
	bool	bstart_txctrl_bydtp;
	rate_adaptive rate_adaptive;
	/* TX घातer tracking
	 * OPEN/CLOSE TX POWER TRACKING
	 */
	txbbgain_काष्ठा txbbgain_table[TxBBGainTableLength];
	u8		txघातer_count; /* For 6 sec करो tracking again */
	bool		btxघातer_trackingInit;
	u8		OFDM_index;
	u8		CCK_index;
	/* CCK TX Power Tracking */
	ccktxbbgain_काष्ठा	cck_txbbgain_table[CCKTxBBGainTableLength];
	ccktxbbgain_काष्ठा	cck_txbbgain_ch14_table[CCKTxBBGainTableLength];
	u8 rfa_txघातertrackingindex;
	u8 rfa_txघातertrackingindex_real;
	u8 rfa_txघातertracking_शेष;
	u8 rfc_txघातertrackingindex;
	u8 rfc_txघातertrackingindex_real;

	s8 cck_present_attenuation;
	u8 cck_present_attenuation_20Mशेष;
	u8 cck_present_attenuation_40Mशेष;
	s8 cck_present_attenuation_dअगरference;
	bool btxघातer_tracking;
	bool bcck_in_ch14;
	bool btxघातerdata_पढ़ोfromEEPORM;
	u16	TSSI_13dBm;
	init_gain initgain_backup;
	u8 DefaultInitialGain[4];
	/* For EDCA Turbo mode */
	bool		bis_any_nonbepkts;
	bool		bcurrent_turbo_EDCA;
	bool		bis_cur_rdlstate;
	काष्ठा समयr_list fsync_समयr;
	bool bfsync_processing;	/* 500ms Fsync समयr is active or not */
	u32	rate_record;
	u32	rateCountDअगरfRecord;
	u32	ContinueDअगरfCount;
	bool bचयन_fsync;

	u8	framesync;
	u32	framesyncC34;
	u8	framesyncMonitor;
	u16	nrxAMPDU_size;
	u8	nrxAMPDU_aggr_num;

	/* For gpio */
	bool bHwRadioOff;

	u32 reset_count;
	bool bpbc_pressed;
	u32 txघातer_checkcnt;
	u32 txघातer_tracking_callback_cnt;
	u8 thermal_पढ़ो_val[40];
	u8 thermal_पढ़ोback_index;
	u32 ccktxघातer_adjustcnt_not_ch14;
	u32 ccktxघातer_adjustcnt_ch14;
	u8 tx_fwinfo_क्रमce_subcarriermode;
	u8 tx_fwinfo_क्रमce_subcarrierval;
	/* For silent reset */
	RESET_TYPE	ResetProgress;
	bool		bForcedSilentReset;
	bool		bDisableNormalResetCheck;
	u16		TxCounter;
	u16		RxCounter;
	पूर्णांक		IrpPendingCount;
	bool		bResetInProgress;
	bool		क्रमce_reset;
	u8		InitialGainOperateType;

	u16		SअगरsTime;

	/* Define work item */

	काष्ठा delayed_work update_beacon_wq;
	काष्ठा delayed_work watch_करोg_wq;
	काष्ठा delayed_work txघातer_tracking_wq;
	काष्ठा delayed_work rfpath_check_wq;
	काष्ठा delayed_work gpio_change_rf_wq;
	काष्ठा delayed_work initialgain_operate_wq;
	काष्ठा workqueue_काष्ठा *priv_wq;
पूर्ण r8192_priv;

/* For rtl8187B */
प्रकार क्रमागतअणु
	BULK_PRIORITY = 0x01,
	LOW_PRIORITY,
	NORM_PRIORITY,
	VO_PRIORITY,
	VI_PRIORITY,
	BE_PRIORITY,
	BK_PRIORITY,
	RSVD2,
	RSVD3,
	BEACON_PRIORITY,
	HIGH_PRIORITY,
	MANAGE_PRIORITY,
	RSVD4,
	RSVD5,
	UART_PRIORITY
पूर्ण priority_t;

प्रकार क्रमागत अणु
	NIC_8192U = 1,
	NIC_8190P = 2,
	NIC_8192E = 3,
पूर्ण nic_t;

bool init_firmware(काष्ठा net_device *dev);
लघु rtl819xU_tx_cmd(काष्ठा net_device *dev, काष्ठा sk_buff *skb);
लघु rtl8192_tx(काष्ठा net_device *dev, काष्ठा sk_buff *skb);

पूर्णांक पढ़ो_nic_byte(काष्ठा net_device *dev, पूर्णांक x, u8 *data);
पूर्णांक पढ़ो_nic_byte_E(काष्ठा net_device *dev, पूर्णांक x, u8 *data);
पूर्णांक पढ़ो_nic_dword(काष्ठा net_device *dev, पूर्णांक x, u32 *data);
पूर्णांक पढ़ो_nic_word(काष्ठा net_device *dev, पूर्णांक x, u16 *data);
पूर्णांक ग_लिखो_nic_byte(काष्ठा net_device *dev, पूर्णांक x, u8 y);
पूर्णांक ग_लिखो_nic_byte_E(काष्ठा net_device *dev, पूर्णांक x, u8 y);
पूर्णांक ग_लिखो_nic_word(काष्ठा net_device *dev, पूर्णांक x, u16 y);
पूर्णांक ग_लिखो_nic_dword(काष्ठा net_device *dev, पूर्णांक x, u32 y);
व्योम क्रमce_pci_posting(काष्ठा net_device *dev);

व्योम rtl8192_rtx_disable(काष्ठा net_device *dev);
व्योम rtl8192_rx_enable(काष्ठा net_device *dev);

व्योम rtl8192_update_msr(काष्ठा net_device *dev);
पूर्णांक rtl8192_करोwn(काष्ठा net_device *dev);
पूर्णांक rtl8192_up(काष्ठा net_device *dev);
व्योम rtl8192_commit(काष्ठा net_device *dev);
व्योम rtl8192_set_chan(काष्ठा net_device *dev, लघु ch);
व्योम rtl8192_set_rxconf(काष्ठा net_device *dev);
व्योम rtl819xusb_beacon_tx(काष्ठा net_device *dev, u16 tx_rate);

व्योम EnableHWSecurityConfig8192(काष्ठा net_device *dev);
व्योम setKey(काष्ठा net_device *dev, u8 EntryNo, u8 KeyIndex, u16 KeyType, u8 *MacAddr, u8 DefaultKey, u32 *KeyContent);

#पूर्ण_अगर
