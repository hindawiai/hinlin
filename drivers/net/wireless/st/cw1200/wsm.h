<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * WSM host पूर्णांकerface (HI) पूर्णांकerface क्रम ST-Ericsson CW1200 mac80211 drivers
 *
 * Copyright (c) 2010, ST-Ericsson
 * Author: Dmitry Tarnyagin <dmitry.tarnyagin@lockless.no>
 *
 * Based on CW1200 UMAC WSM API, which is
 * Copyright (C) ST-Ericsson SA 2010
 * Author: Stewart Mathers <stewart.mathers@stericsson.com>
 */

#अगर_अघोषित CW1200_WSM_H_INCLUDED
#घोषणा CW1200_WSM_H_INCLUDED

#समावेश <linux/spinlock.h>

काष्ठा cw1200_common;

/* Bands */
/* Radio band 2.412 -2.484 GHz. */
#घोषणा WSM_PHY_BAND_2_4G		(0)

/* Radio band 4.9375-5.8250 GHz. */
#घोषणा WSM_PHY_BAND_5G			(1)

/* Transmit rates */
/* 1   Mbps            ERP-DSSS */
#घोषणा WSM_TRANSMIT_RATE_1		(0)

/* 2   Mbps            ERP-DSSS */
#घोषणा WSM_TRANSMIT_RATE_2		(1)

/* 5.5 Mbps            ERP-CCK */
#घोषणा WSM_TRANSMIT_RATE_5		(2)

/* 11  Mbps            ERP-CCK */
#घोषणा WSM_TRANSMIT_RATE_11		(3)

/* 22  Mbps            ERP-PBCC (Not supported) */
/* #घोषणा WSM_TRANSMIT_RATE_22		(4) */

/* 33  Mbps            ERP-PBCC (Not supported) */
/* #घोषणा WSM_TRANSMIT_RATE_33		(5) */

/* 6   Mbps   (3 Mbps) ERP-OFDM, BPSK coding rate 1/2 */
#घोषणा WSM_TRANSMIT_RATE_6		(6)

/* 9   Mbps (4.5 Mbps) ERP-OFDM, BPSK coding rate 3/4 */
#घोषणा WSM_TRANSMIT_RATE_9		(7)

/* 12  Mbps  (6 Mbps)  ERP-OFDM, QPSK coding rate 1/2 */
#घोषणा WSM_TRANSMIT_RATE_12		(8)

/* 18  Mbps  (9 Mbps)  ERP-OFDM, QPSK coding rate 3/4 */
#घोषणा WSM_TRANSMIT_RATE_18		(9)

/* 24  Mbps (12 Mbps)  ERP-OFDM, 16QAM coding rate 1/2 */
#घोषणा WSM_TRANSMIT_RATE_24		(10)

/* 36  Mbps (18 Mbps)  ERP-OFDM, 16QAM coding rate 3/4 */
#घोषणा WSM_TRANSMIT_RATE_36		(11)

/* 48  Mbps (24 Mbps)  ERP-OFDM, 64QAM coding rate 1/2 */
#घोषणा WSM_TRANSMIT_RATE_48		(12)

/* 54  Mbps (27 Mbps)  ERP-OFDM, 64QAM coding rate 3/4 */
#घोषणा WSM_TRANSMIT_RATE_54		(13)

/* 6.5 Mbps            HT-OFDM, BPSK coding rate 1/2 */
#घोषणा WSM_TRANSMIT_RATE_HT_6		(14)

/* 13  Mbps            HT-OFDM, QPSK coding rate 1/2 */
#घोषणा WSM_TRANSMIT_RATE_HT_13		(15)

/* 19.5 Mbps           HT-OFDM, QPSK coding rate 3/4 */
#घोषणा WSM_TRANSMIT_RATE_HT_19		(16)

/* 26  Mbps            HT-OFDM, 16QAM coding rate 1/2 */
#घोषणा WSM_TRANSMIT_RATE_HT_26		(17)

/* 39  Mbps            HT-OFDM, 16QAM coding rate 3/4 */
#घोषणा WSM_TRANSMIT_RATE_HT_39		(18)

/* 52  Mbps            HT-OFDM, 64QAM coding rate 2/3 */
#घोषणा WSM_TRANSMIT_RATE_HT_52		(19)

/* 58.5 Mbps           HT-OFDM, 64QAM coding rate 3/4 */
#घोषणा WSM_TRANSMIT_RATE_HT_58		(20)

/* 65  Mbps            HT-OFDM, 64QAM coding rate 5/6 */
#घोषणा WSM_TRANSMIT_RATE_HT_65		(21)

/* Scan types */
/* Foreground scan */
#घोषणा WSM_SCAN_TYPE_FOREGROUND	(0)

/* Background scan */
#घोषणा WSM_SCAN_TYPE_BACKGROUND	(1)

/* Auto scan */
#घोषणा WSM_SCAN_TYPE_AUTO		(2)

/* Scan flags */
/* Forced background scan means अगर the station cannot */
/* enter the घातer-save mode, it shall क्रमce to perक्रमm a */
/* background scan. Only valid when ScanType is */
/* background scan. */
#घोषणा WSM_SCAN_FLAG_FORCE_BACKGROUND	(BIT(0))

/* The WLAN device scans one channel at a समय so */
/* that disturbance to the data traffic is minimized. */
#घोषणा WSM_SCAN_FLAG_SPLIT_METHOD	(BIT(1))

/* Preamble Type. Long अगर not set. */
#घोषणा WSM_SCAN_FLAG_SHORT_PREAMBLE	(BIT(2))

/* 11n Tx Mode. Mixed अगर not set. */
#घोषणा WSM_SCAN_FLAG_11N_GREENFIELD	(BIT(3))

/* Scan स्थिरraपूर्णांकs */
/* Maximum number of channels to be scanned. */
#घोषणा WSM_SCAN_MAX_NUM_OF_CHANNELS	(48)

/* The maximum number of SSIDs that the device can scan क्रम. */
#घोषणा WSM_SCAN_MAX_NUM_OF_SSIDS	(2)

/* Power management modes */
/* 802.11 Active mode */
#घोषणा WSM_PSM_ACTIVE			(0)

/* 802.11 PS mode */
#घोषणा WSM_PSM_PS			BIT(0)

/* Fast Power Save bit */
#घोषणा WSM_PSM_FAST_PS_FLAG		BIT(7)

/* Dynamic aka Fast घातer save */
#घोषणा WSM_PSM_FAST_PS			(BIT(0) | BIT(7))

/* Undetermined */
/* Note : Undetermined status is reported when the */
/* शून्य data frame used to advertise the PM mode to */
/* the AP at Pre or Post Background Scan is not Acknowledged */
#घोषणा WSM_PSM_UNKNOWN			BIT(1)

/* Queue IDs */
/* best efक्रमt/legacy */
#घोषणा WSM_QUEUE_BEST_EFFORT		(0)

/* background */
#घोषणा WSM_QUEUE_BACKGROUND		(1)

/* video */
#घोषणा WSM_QUEUE_VIDEO			(2)

/* voice */
#घोषणा WSM_QUEUE_VOICE			(3)

/* HT TX parameters */
/* Non-HT */
#घोषणा WSM_HT_TX_NON_HT		(0)

/* Mixed क्रमmat */
#घोषणा WSM_HT_TX_MIXED			(1)

/* Greenfield क्रमmat */
#घोषणा WSM_HT_TX_GREENFIELD		(2)

/* STBC allowed */
#घोषणा WSM_HT_TX_STBC			(BIT(7))

/* EPTA prioirty flags क्रम BT Coex */
/* शेष epta priority */
#घोषणा WSM_EPTA_PRIORITY_DEFAULT	4
/* use क्रम normal data */
#घोषणा WSM_EPTA_PRIORITY_DATA		4
/* use क्रम connect/disconnect/roaming*/
#घोषणा WSM_EPTA_PRIORITY_MGT		5
/* use क्रम action frames */
#घोषणा WSM_EPTA_PRIORITY_ACTION	5
/* use क्रम AC_VI data */
#घोषणा WSM_EPTA_PRIORITY_VIDEO		5
/* use क्रम AC_VO data */
#घोषणा WSM_EPTA_PRIORITY_VOICE		6
/* use क्रम EAPOL exchange */
#घोषणा WSM_EPTA_PRIORITY_EAPOL		7

/* TX status */
/* Frame was sent aggregated */
/* Only valid क्रम WSM_SUCCESS status. */
#घोषणा WSM_TX_STATUS_AGGREGATION	(BIT(0))

/* Host should requeue this frame later. */
/* Valid only when status is WSM_REQUEUE. */
#घोषणा WSM_TX_STATUS_REQUEUE		(BIT(1))

/* Normal Ack */
#घोषणा WSM_TX_STATUS_NORMAL_ACK	(0<<2)

/* No Ack */
#घोषणा WSM_TX_STATUS_NO_ACK		(1<<2)

/* No explicit acknowledgement */
#घोषणा WSM_TX_STATUS_NO_EXPLICIT_ACK	(2<<2)

/* Block Ack */
/* Only valid क्रम WSM_SUCCESS status. */
#घोषणा WSM_TX_STATUS_BLOCK_ACK		(3<<2)

/* RX status */
/* Unencrypted */
#घोषणा WSM_RX_STATUS_UNENCRYPTED	(0<<0)

/* WEP */
#घोषणा WSM_RX_STATUS_WEP		(1<<0)

/* TKIP */
#घोषणा WSM_RX_STATUS_TKIP		(2<<0)

/* AES */
#घोषणा WSM_RX_STATUS_AES		(3<<0)

/* WAPI */
#घोषणा WSM_RX_STATUS_WAPI		(4<<0)

/* Macro to fetch encryption subfield. */
#घोषणा WSM_RX_STATUS_ENCRYPTION(status) ((status) & 0x07)

/* Frame was part of an aggregation */
#घोषणा WSM_RX_STATUS_AGGREGATE		(BIT(3))

/* Frame was first in the aggregation */
#घोषणा WSM_RX_STATUS_AGGREGATE_FIRST	(BIT(4))

/* Frame was last in the aggregation */
#घोषणा WSM_RX_STATUS_AGGREGATE_LAST	(BIT(5))

/* Indicates a defragmented frame */
#घोषणा WSM_RX_STATUS_DEFRAGMENTED	(BIT(6))

/* Indicates a Beacon frame */
#घोषणा WSM_RX_STATUS_BEACON		(BIT(7))

/* Indicates STA bit beacon TIM field */
#घोषणा WSM_RX_STATUS_TIM		(BIT(8))

/* Indicates Beacon frame's भव biपंचांगap contains multicast bit */
#घोषणा WSM_RX_STATUS_MULTICAST		(BIT(9))

/* Indicates frame contains a matching SSID */
#घोषणा WSM_RX_STATUS_MATCHING_SSID	(BIT(10))

/* Indicates frame contains a matching BSSI */
#घोषणा WSM_RX_STATUS_MATCHING_BSSI	(BIT(11))

/* Indicates More bit set in Framectl field */
#घोषणा WSM_RX_STATUS_MORE_DATA		(BIT(12))

/* Indicates frame received during a measurement process */
#घोषणा WSM_RX_STATUS_MEASUREMENT	(BIT(13))

/* Indicates frame received as an HT packet */
#घोषणा WSM_RX_STATUS_HT		(BIT(14))

/* Indicates frame received with STBC */
#घोषणा WSM_RX_STATUS_STBC		(BIT(15))

/* Indicates Address 1 field matches करोt11StationId */
#घोषणा WSM_RX_STATUS_ADDRESS1		(BIT(16))

/* Indicates Group address present in the Address 1 field */
#घोषणा WSM_RX_STATUS_GROUP		(BIT(17))

/* Indicates Broadcast address present in the Address 1 field */
#घोषणा WSM_RX_STATUS_BROADCAST		(BIT(18))

/* Indicates group key used with encrypted frames */
#घोषणा WSM_RX_STATUS_GROUP_KEY		(BIT(19))

/* Macro to fetch encryption key index. */
#घोषणा WSM_RX_STATUS_KEY_IDX(status)	(((status >> 20)) & 0x0F)

/* Indicates TSF inclusion after 802.11 frame body */
#घोषणा WSM_RX_STATUS_TSF_INCLUDED	(BIT(24))

/* Frame Control field starts at Frame offset + 2 */
#घोषणा WSM_TX_2BYTES_SHIFT		(BIT(7))

/* Join mode */
/* IBSS */
#घोषणा WSM_JOIN_MODE_IBSS		(0)

/* BSS */
#घोषणा WSM_JOIN_MODE_BSS		(1)

/* PLCP preamble type */
/* For दीर्घ preamble */
#घोषणा WSM_JOIN_PREAMBLE_LONG		(0)

/* For लघु preamble (Long क्रम 1Mbps) */
#घोषणा WSM_JOIN_PREAMBLE_SHORT		(1)

/* For लघु preamble (Long क्रम 1 and 2Mbps) */
#घोषणा WSM_JOIN_PREAMBLE_SHORT_2	(2)

/* Join flags */
/* Unsynchronized */
#घोषणा WSM_JOIN_FLAGS_UNSYNCRONIZED	BIT(0)
/* The BSS owner is a P2P GO */
#घोषणा WSM_JOIN_FLAGS_P2P_GO		BIT(1)
/* Force to join BSS with the BSSID and the
 * SSID specअगरied without रुकोing क्रम beacons. The
 * ProbeForJoin parameter is ignored.
 */
#घोषणा WSM_JOIN_FLAGS_FORCE		BIT(2)
/* Give probe request/response higher
 * priority over the BT traffic
 */
#घोषणा WSM_JOIN_FLAGS_PRIO		BIT(3)
/* Issue immediate join confirmation and use
 * join complete to notअगरy about completion
 */
#घोषणा WSM_JOIN_FLAGS_FORCE_WITH_COMPLETE_IND BIT(5)

/* Key types */
#घोषणा WSM_KEY_TYPE_WEP_DEFAULT	(0)
#घोषणा WSM_KEY_TYPE_WEP_PAIRWISE	(1)
#घोषणा WSM_KEY_TYPE_TKIP_GROUP		(2)
#घोषणा WSM_KEY_TYPE_TKIP_PAIRWISE	(3)
#घोषणा WSM_KEY_TYPE_AES_GROUP		(4)
#घोषणा WSM_KEY_TYPE_AES_PAIRWISE	(5)
#घोषणा WSM_KEY_TYPE_WAPI_GROUP		(6)
#घोषणा WSM_KEY_TYPE_WAPI_PAIRWISE	(7)

/* Key indexes */
#घोषणा WSM_KEY_MAX_INDEX		(10)

/* ACK policy */
#घोषणा WSM_ACK_POLICY_NORMAL		(0)
#घोषणा WSM_ACK_POLICY_NO_ACK		(1)

/* Start modes */
#घोषणा WSM_START_MODE_AP		(0)	/* Mini AP */
#घोषणा WSM_START_MODE_P2P_GO		(1)	/* P2P GO */
#घोषणा WSM_START_MODE_P2P_DEV		(2)	/* P2P device */

/* SetAssociationMode MIB flags */
#घोषणा WSM_ASSOCIATION_MODE_USE_PREAMBLE_TYPE		(BIT(0))
#घोषणा WSM_ASSOCIATION_MODE_USE_HT_MODE		(BIT(1))
#घोषणा WSM_ASSOCIATION_MODE_USE_BASIC_RATE_SET		(BIT(2))
#घोषणा WSM_ASSOCIATION_MODE_USE_MPDU_START_SPACING	(BIT(3))
#घोषणा WSM_ASSOCIATION_MODE_SNOOP_ASSOC_FRAMES		(BIT(4))

/* RcpiRssiThreshold MIB flags */
#घोषणा WSM_RCPI_RSSI_THRESHOLD_ENABLE	(BIT(0))
#घोषणा WSM_RCPI_RSSI_USE_RSSI		(BIT(1))
#घोषणा WSM_RCPI_RSSI_DONT_USE_UPPER	(BIT(2))
#घोषणा WSM_RCPI_RSSI_DONT_USE_LOWER	(BIT(3))

/* Update-ie स्थिरants */
#घोषणा WSM_UPDATE_IE_BEACON		(BIT(0))
#घोषणा WSM_UPDATE_IE_PROBE_RESP	(BIT(1))
#घोषणा WSM_UPDATE_IE_PROBE_REQ		(BIT(2))

/* WSM events */
/* Error */
#घोषणा WSM_EVENT_ERROR			(0)

/* BSS lost */
#घोषणा WSM_EVENT_BSS_LOST		(1)

/* BSS regained */
#घोषणा WSM_EVENT_BSS_REGAINED		(2)

/* Radar detected */
#घोषणा WSM_EVENT_RADAR_DETECTED	(3)

/* RCPI or RSSI threshold triggered */
#घोषणा WSM_EVENT_RCPI_RSSI		(4)

/* BT inactive */
#घोषणा WSM_EVENT_BT_INACTIVE		(5)

/* BT active */
#घोषणा WSM_EVENT_BT_ACTIVE		(6)

/* MIB IDs */
/* 4.1  करोt11StationId */
#घोषणा WSM_MIB_ID_DOT11_STATION_ID		0x0000

/* 4.2  करोt11MaxtransmitMsduLअगरeTime */
#घोषणा WSM_MIB_ID_DOT11_MAX_TRANSMIT_LIFTIME	0x0001

/* 4.3  करोt11MaxReceiveLअगरeTime */
#घोषणा WSM_MIB_ID_DOT11_MAX_RECEIVE_LIFETIME	0x0002

/* 4.4  करोt11SlotTime */
#घोषणा WSM_MIB_ID_DOT11_SLOT_TIME		0x0003

/* 4.5  करोt11GroupAddressesTable */
#घोषणा WSM_MIB_ID_DOT11_GROUP_ADDRESSES_TABLE	0x0004
#घोषणा WSM_MAX_GRP_ADDRTABLE_ENTRIES		8

/* 4.6  करोt11WepDefaultKeyId */
#घोषणा WSM_MIB_ID_DOT11_WEP_DEFAULT_KEY_ID	0x0005

/* 4.7  करोt11CurrentTxPowerLevel */
#घोषणा WSM_MIB_ID_DOT11_CURRENT_TX_POWER_LEVEL	0x0006

/* 4.8  करोt11RTSThreshold */
#घोषणा WSM_MIB_ID_DOT11_RTS_THRESHOLD		0x0007

/* 4.9  NonErpProtection */
#घोषणा WSM_MIB_ID_NON_ERP_PROTECTION		0x1000

/* 4.10 ArpIpAddressesTable */
#घोषणा WSM_MIB_ID_ARP_IP_ADDRESSES_TABLE	0x1001
#घोषणा WSM_MAX_ARP_IP_ADDRTABLE_ENTRIES	1

/* 4.11 TemplateFrame */
#घोषणा WSM_MIB_ID_TEMPLATE_FRAME		0x1002

/* 4.12 RxFilter */
#घोषणा WSM_MIB_ID_RX_FILTER			0x1003

/* 4.13 BeaconFilterTable */
#घोषणा WSM_MIB_ID_BEACON_FILTER_TABLE		0x1004

/* 4.14 BeaconFilterEnable */
#घोषणा WSM_MIB_ID_BEACON_FILTER_ENABLE		0x1005

/* 4.15 OperationalPowerMode */
#घोषणा WSM_MIB_ID_OPERATIONAL_POWER_MODE	0x1006

/* 4.16 BeaconWakeUpPeriod */
#घोषणा WSM_MIB_ID_BEACON_WAKEUP_PERIOD		0x1007

/* 4.17 RcpiRssiThreshold */
#घोषणा WSM_MIB_ID_RCPI_RSSI_THRESHOLD		0x1009

/* 4.18 StatisticsTable */
#घोषणा WSM_MIB_ID_STATISTICS_TABLE		0x100A

/* 4.19 IbssPsConfig */
#घोषणा WSM_MIB_ID_IBSS_PS_CONFIG		0x100B

/* 4.20 CountersTable */
#घोषणा WSM_MIB_ID_COUNTERS_TABLE		0x100C

/* 4.21 BlockAckPolicy */
#घोषणा WSM_MIB_ID_BLOCK_ACK_POLICY		0x100E

/* 4.22 OverrideInternalTxRate */
#घोषणा WSM_MIB_ID_OVERRIDE_INTERNAL_TX_RATE	0x100F

/* 4.23 SetAssociationMode */
#घोषणा WSM_MIB_ID_SET_ASSOCIATION_MODE		0x1010

/* 4.24 UpdateEptaConfigData */
#घोषणा WSM_MIB_ID_UPDATE_EPTA_CONFIG_DATA	0x1011

/* 4.25 SelectCcaMethod */
#घोषणा WSM_MIB_ID_SELECT_CCA_METHOD		0x1012

/* 4.26 SetUpasdInक्रमmation */
#घोषणा WSM_MIB_ID_SET_UAPSD_INFORMATION	0x1013

/* 4.27 SetAutoCalibrationMode  WBF00004073 */
#घोषणा WSM_MIB_ID_SET_AUTO_CALIBRATION_MODE	0x1015

/* 4.28 SetTxRateRetryPolicy */
#घोषणा WSM_MIB_ID_SET_TX_RATE_RETRY_POLICY	0x1016

/* 4.29 SetHostMessageTypeFilter */
#घोषणा WSM_MIB_ID_SET_HOST_MSG_TYPE_FILTER	0x1017

/* 4.30 P2PFindInfo */
#घोषणा WSM_MIB_ID_P2P_FIND_INFO		0x1018

/* 4.31 P2PPsModeInfo */
#घोषणा WSM_MIB_ID_P2P_PS_MODE_INFO		0x1019

/* 4.32 SetEtherTypeDataFrameFilter */
#घोषणा WSM_MIB_ID_SET_ETHERTYPE_DATAFRAME_FILTER 0x101A

/* 4.33 SetUDPPortDataFrameFilter */
#घोषणा WSM_MIB_ID_SET_UDPPORT_DATAFRAME_FILTER	0x101B

/* 4.34 SetMagicDataFrameFilter */
#घोषणा WSM_MIB_ID_SET_MAGIC_DATAFRAME_FILTER	0x101C

/* 4.35 P2PDeviceInfo */
#घोषणा WSM_MIB_ID_P2P_DEVICE_INFO		0x101D

/* 4.36 SetWCDMABand */
#घोषणा WSM_MIB_ID_SET_WCDMA_BAND		0x101E

/* 4.37 GroupTxSequenceCounter */
#घोषणा WSM_MIB_ID_GRP_SEQ_COUNTER		0x101F

/* 4.38 ProtectedMgmtPolicy */
#घोषणा WSM_MIB_ID_PROTECTED_MGMT_POLICY	0x1020

/* 4.39 SetHtProtection */
#घोषणा WSM_MIB_ID_SET_HT_PROTECTION		0x1021

/* 4.40 GPIO Command */
#घोषणा WSM_MIB_ID_GPIO_COMMAND			0x1022

/* 4.41 TSF Counter Value */
#घोषणा WSM_MIB_ID_TSF_COUNTER			0x1023

/* Test Purposes Only */
#घोषणा WSM_MIB_ID_BLOCK_ACK_INFO		0x100D

/* 4.42 UseMultiTxConfMessage */
#घोषणा WSM_MIB_USE_MULTI_TX_CONF		0x1024

/* 4.43 Keep-alive period */
#घोषणा WSM_MIB_ID_KEEP_ALIVE_PERIOD		0x1025

/* 4.44 Disable BSSID filter */
#घोषणा WSM_MIB_ID_DISABLE_BSSID_FILTER		0x1026

/* Frame ढाँचा types */
#घोषणा WSM_FRAME_TYPE_PROBE_REQUEST	(0)
#घोषणा WSM_FRAME_TYPE_BEACON		(1)
#घोषणा WSM_FRAME_TYPE_शून्य		(2)
#घोषणा WSM_FRAME_TYPE_QOS_शून्य		(3)
#घोषणा WSM_FRAME_TYPE_PS_POLL		(4)
#घोषणा WSM_FRAME_TYPE_PROBE_RESPONSE	(5)

#घोषणा WSM_FRAME_GREENFIELD		(0x80)	/* See 4.11 */

/* Status */
/* The WSM firmware has completed a request */
/* successfully. */
#घोषणा WSM_STATUS_SUCCESS              (0)

/* This is a generic failure code अगर other error codes करो */
/* not apply. */
#घोषणा WSM_STATUS_FAILURE              (1)

/* A request contains one or more invalid parameters. */
#घोषणा WSM_INVALID_PARAMETER           (2)

/* The request cannot perक्रमm because the device is in */
/* an inappropriate mode. */
#घोषणा WSM_ACCESS_DENIED               (3)

/* The frame received includes a decryption error. */
#घोषणा WSM_STATUS_DECRYPTFAILURE       (4)

/* A MIC failure is detected in the received packets. */
#घोषणा WSM_STATUS_MICFAILURE           (5)

/* The transmit request failed due to retry limit being */
/* exceeded. */
#घोषणा WSM_STATUS_RETRY_EXCEEDED       (6)

/* The transmit request failed due to MSDU lअगरe समय */
/* being exceeded. */
#घोषणा WSM_STATUS_TX_LIFETIME_EXCEEDED (7)

/* The link to the AP is lost. */
#घोषणा WSM_STATUS_LINK_LOST            (8)

/* No key was found क्रम the encrypted frame */
#घोषणा WSM_STATUS_NO_KEY_FOUND         (9)

/* Jammer was detected when transmitting this frame */
#घोषणा WSM_STATUS_JAMMER_DETECTED      (10)

/* The message should be requeued later. */
/* This is applicable only to Transmit */
#घोषणा WSM_REQUEUE                     (11)

/* Advanced filtering options */
#घोषणा WSM_MAX_FILTER_ELEMENTS		(4)

#घोषणा WSM_FILTER_ACTION_IGNORE	(0)
#घोषणा WSM_FILTER_ACTION_FILTER_IN	(1)
#घोषणा WSM_FILTER_ACTION_FILTER_OUT	(2)

#घोषणा WSM_FILTER_PORT_TYPE_DST	(0)
#घोषणा WSM_FILTER_PORT_TYPE_SRC	(1)

/* Actual header of WSM messages */
काष्ठा wsm_hdr अणु
	__le16 len;
	__le16 id;
पूर्ण;

#घोषणा WSM_TX_SEQ_MAX			(7)
#घोषणा WSM_TX_SEQ(seq)			\
		((seq & WSM_TX_SEQ_MAX) << 13)
#घोषणा WSM_TX_LINK_ID_MAX		(0x0F)
#घोषणा WSM_TX_LINK_ID(link_id)		\
		((link_id & WSM_TX_LINK_ID_MAX) << 6)

#घोषणा MAX_BEACON_SKIP_TIME_MS 1000

#घोषणा WSM_CMD_LAST_CHANCE_TIMEOUT (HZ * 3 / 2)

/* ******************************************************************** */
/* WSM capability							*/

#घोषणा WSM_STARTUP_IND_ID 0x0801

काष्ठा wsm_startup_ind अणु
	u16 input_buffers;
	u16 input_buffer_size;
	u16 status;
	u16 hw_id;
	u16 hw_subid;
	u16 fw_cap;
	u16 fw_type;
	u16 fw_api;
	u16 fw_build;
	u16 fw_ver;
	अक्षर fw_label[128];
	u32 config[4];
पूर्ण;

/* ******************************************************************** */
/* WSM commands								*/

/* 3.1 */
#घोषणा WSM_CONFIGURATION_REQ_ID 0x0009
#घोषणा WSM_CONFIGURATION_RESP_ID 0x0409

काष्ठा wsm_tx_घातer_range अणु
	पूर्णांक min_घातer_level;
	पूर्णांक max_घातer_level;
	u32 stepping;
पूर्ण;

काष्ठा wsm_configuration अणु
	/* [in] */ u32 करोt11MaxTransmitMsduLअगरeTime;
	/* [in] */ u32 करोt11MaxReceiveLअगरeTime;
	/* [in] */ u32 करोt11RtsThreshold;
	/* [in, out] */ u8 *करोt11StationId;
	/* [in] */ स्थिर व्योम *dpdData;
	/* [in] */ माप_प्रकार dpdData_size;
	/* [out] */ u8 करोt11FrequencyBandsSupported;
	/* [out] */ u32 supportedRateMask;
	/* [out] */ काष्ठा wsm_tx_घातer_range txPowerRange[2];
पूर्ण;

पूर्णांक wsm_configuration(काष्ठा cw1200_common *priv,
		      काष्ठा wsm_configuration *arg);

/* 3.3 */
#घोषणा WSM_RESET_REQ_ID 0x000A
#घोषणा WSM_RESET_RESP_ID 0x040A
काष्ठा wsm_reset अणु
	/* [in] */ पूर्णांक link_id;
	/* [in] */ bool reset_statistics;
पूर्ण;

पूर्णांक wsm_reset(काष्ठा cw1200_common *priv, स्थिर काष्ठा wsm_reset *arg);

/* 3.5 */
#घोषणा WSM_READ_MIB_REQ_ID 0x0005
#घोषणा WSM_READ_MIB_RESP_ID 0x0405
पूर्णांक wsm_पढ़ो_mib(काष्ठा cw1200_common *priv, u16 mib_id, व्योम *buf,
		 माप_प्रकार buf_size);

/* 3.7 */
#घोषणा WSM_WRITE_MIB_REQ_ID 0x0006
#घोषणा WSM_WRITE_MIB_RESP_ID 0x0406
पूर्णांक wsm_ग_लिखो_mib(काष्ठा cw1200_common *priv, u16 mib_id, व्योम *buf,
		  माप_प्रकार buf_size);

/* 3.9 */
#घोषणा WSM_START_SCAN_REQ_ID 0x0007
#घोषणा WSM_START_SCAN_RESP_ID 0x0407

काष्ठा wsm_ssid अणु
	u8 ssid[32];
	u32 length;
पूर्ण;

काष्ठा wsm_scan_ch अणु
	u16 number;
	u32 min_chan_समय;
	u32 max_chan_समय;
	u32 tx_घातer_level;
पूर्ण;

काष्ठा wsm_scan अणु
	/* WSM_PHY_BAND_... */
	u8 band;

	/* WSM_SCAN_TYPE_... */
	u8 type;

	/* WSM_SCAN_FLAG_... */
	u8 flags;

	/* WSM_TRANSMIT_RATE_... */
	u8 max_tx_rate;

	/* Interval period in TUs that the device shall the re- */
	/* execute the requested scan. Max value supported by the device */
	/* is 256s. */
	u32 स्वतः_scan_पूर्णांकerval;

	/* Number of probe requests (per SSID) sent to one (1) */
	/* channel. Zero (0) means that none is send, which */
	/* means that a passive scan is to be करोne. Value */
	/* greater than zero (0) means that an active scan is to */
	/* be करोne. */
	u32 num_probes;

	/* Number of channels to be scanned. */
	/* Maximum value is WSM_SCAN_MAX_NUM_OF_CHANNELS. */
	u8 num_channels;

	/* Number of SSID provided in the scan command (this */
	/* is zero (0) in broadcast scan) */
	/* The maximum number of SSIDs is WSM_SCAN_MAX_NUM_OF_SSIDS. */
	u8 num_ssids;

	/* The delay समय (in microseconds) period */
	/* beक्रमe sending a probe-request. */
	u8 probe_delay;

	/* SSIDs to be scanned [numOfSSIDs]; */
	काष्ठा wsm_ssid *ssids;

	/* Channels to be scanned [numOfChannels]; */
	काष्ठा wsm_scan_ch *ch;
पूर्ण;

पूर्णांक wsm_scan(काष्ठा cw1200_common *priv, स्थिर काष्ठा wsm_scan *arg);

/* 3.11 */
#घोषणा WSM_STOP_SCAN_REQ_ID 0x0008
#घोषणा WSM_STOP_SCAN_RESP_ID 0x0408
पूर्णांक wsm_stop_scan(काष्ठा cw1200_common *priv);

/* 3.13 */
#घोषणा WSM_SCAN_COMPLETE_IND_ID 0x0806
काष्ठा wsm_scan_complete अणु
	/* WSM_STATUS_... */
	u32 status;

	/* WSM_PSM_... */
	u8 psm;

	/* Number of channels that the scan operation completed. */
	u8 num_channels;
पूर्ण;

/* 3.14 */
#घोषणा WSM_TX_CONFIRM_IND_ID 0x0404
#घोषणा WSM_MULTI_TX_CONFIRM_ID 0x041E

काष्ठा wsm_tx_confirm अणु
	/* Packet identअगरier used in wsm_tx. */
	u32 packet_id;

	/* WSM_STATUS_... */
	u32 status;

	/* WSM_TRANSMIT_RATE_... */
	u8 tx_rate;

	/* The number of बार the frame was transmitted */
	/* without receiving an acknowledgement. */
	u8 ack_failures;

	/* WSM_TX_STATUS_... */
	u16 flags;

	/* The total समय in microseconds that the frame spent in */
	/* the WLAN device beक्रमe transmission as completed. */
	u32 media_delay;

	/* The total समय in microseconds that the frame spent in */
	/* the WLAN device beक्रमe transmission was started. */
	u32 tx_queue_delay;
पूर्ण;

/* 3.15 */

/* Note that ideology of wsm_tx काष्ठा is dअगरferent against the rest of
 * WSM API. wsm_hdr is /not/ a caller-adapted काष्ठा to be used as an input
 * argument क्रम WSM call, but a prepared bytestream to be sent to firmware.
 * It is filled partly in cw1200_tx, partly in low-level WSM code.
 * Please pay attention once again: ideology is dअगरferent.
 *
 * Legend:
 * - [in]: cw1200_tx must fill this field.
 * - [wsm]: the field is filled by low-level WSM.
 */
काष्ठा wsm_tx अणु
	/* common WSM header */
	काष्ठा wsm_hdr hdr;

	/* Packet identअगरier that meant to be used in completion. */
	u32 packet_id;  /* Note this is actually a cookie */

	/* WSM_TRANSMIT_RATE_... */
	u8 max_tx_rate;

	/* WSM_QUEUE_... */
	u8 queue_id;

	/* True: another packet is pending on the host क्रम transmission. */
	u8 more;

	/* Bit 0 = 0 - Start expiry समय from first Tx attempt (शेष) */
	/* Bit 0 = 1 - Start expiry समय from receipt of Tx Request */
	/* Bits 3:1  - PTA Priority */
	/* Bits 6:4  - Tx Rate Retry Policy */
	/* Bit 7 - Reserved */
	u8 flags;

	/* Should be 0. */
	u32 reserved;

	/* The elapsed समय in TUs, after the initial transmission */
	/* of an MSDU, after which further attempts to transmit */
	/* the MSDU shall be terminated. Overrides the global */
	/* करोt11MaxTransmitMsduLअगरeTime setting [optional] */
	/* Device will set the शेष value अगर this is 0. */
	__le32 expire_समय;

	/* WSM_HT_TX_... */
	__le32 ht_tx_parameters;
पूर्ण __packed;

/* = माप(generic hi hdr) + माप(wsm hdr) + माप(alignment) */
#घोषणा WSM_TX_EXTRA_HEADROOM (28)

/* 3.16 */
#घोषणा WSM_RECEIVE_IND_ID 0x0804

काष्ठा wsm_rx अणु
	/* WSM_STATUS_... */
	u32 status;

	/* Specअगरies the channel of the received packet. */
	u16 channel_number;

	/* WSM_TRANSMIT_RATE_... */
	u8 rx_rate;

	/* This value is expressed in चिन्हित Q8.0 क्रमmat क्रम */
	/* RSSI and अचिन्हित Q7.1 क्रमmat क्रम RCPI. */
	u8 rcpi_rssi;

	/* WSM_RX_STATUS_... */
	u32 flags;
पूर्ण;

/* = माप(generic hi hdr) + माप(wsm hdr) */
#घोषणा WSM_RX_EXTRA_HEADROOM (16)

/* 3.17 */
काष्ठा wsm_event अणु
	/* WSM_STATUS_... */
	/* [out] */ u32 id;

	/* Indication parameters. */
	/* For error indication, this shall be a 32-bit WSM status. */
	/* For RCPI or RSSI indication, this should be an 8-bit */
	/* RCPI or RSSI value. */
	/* [out] */ u32 data;
पूर्ण;

काष्ठा cw1200_wsm_event अणु
	काष्ठा list_head link;
	काष्ठा wsm_event evt;
पूर्ण;

/* 3.18 - 3.22 */
/* Measurement. Skipped क्रम now. Irrelevent. */

प्रकार व्योम (*wsm_event_cb) (काष्ठा cw1200_common *priv,
			      काष्ठा wsm_event *arg);

/* 3.23 */
#घोषणा WSM_JOIN_REQ_ID 0x000B
#घोषणा WSM_JOIN_RESP_ID 0x040B

काष्ठा wsm_join अणु
	/* WSM_JOIN_MODE_... */
	u8 mode;

	/* WSM_PHY_BAND_... */
	u8 band;

	/* Specअगरies the channel number to join. The channel */
	/* number will be mapped to an actual frequency */
	/* according to the band */
	u16 channel_number;

	/* Specअगरies the BSSID of the BSS or IBSS to be joined */
	/* or the IBSS to be started. */
	u8 bssid[6];

	/* ATIM winकरोw of IBSS */
	/* When ATIM winकरोw is zero the initiated IBSS करोes */
	/* not support घातer saving. */
	u16 atim_winकरोw;

	/* WSM_JOIN_PREAMBLE_... */
	u8 preamble_type;

	/* Specअगरies अगर a probe request should be send with the */
	/* specअगरied SSID when joining to the network. */
	u8 probe_क्रम_join;

	/* DTIM Period (In multiples of beacon पूर्णांकerval) */
	u8 dtim_period;

	/* WSM_JOIN_FLAGS_... */
	u8 flags;

	/* Length of the SSID */
	u32 ssid_len;

	/* Specअगरies the SSID of the IBSS to join or start */
	u8 ssid[32];

	/* Specअगरies the समय between TBTTs in TUs */
	u32 beacon_पूर्णांकerval;

	/* A bit mask that defines the BSS basic rate set. */
	u32 basic_rate_set;
पूर्ण;

काष्ठा wsm_join_cnf अणु
	u32 status;

	/* Minimum transmission घातer level in units of 0.1dBm */
	u32 min_घातer_level;

	/* Maximum transmission घातer level in units of 0.1dBm */
	u32 max_घातer_level;
पूर्ण;

पूर्णांक wsm_join(काष्ठा cw1200_common *priv, काष्ठा wsm_join *arg);

/* 3.24 */
काष्ठा wsm_join_complete अणु
	/* WSM_STATUS_... */
	u32 status;
पूर्ण;

/* 3.25 */
#घोषणा WSM_SET_PM_REQ_ID 0x0010
#घोषणा WSM_SET_PM_RESP_ID 0x0410
काष्ठा wsm_set_pm अणु
	/* WSM_PSM_... */
	u8 mode;

	/* in unit of 500us; 0 to use शेष */
	u8 fast_psm_idle_period;

	/* in unit of 500us; 0 to use शेष */
	u8 ap_psm_change_period;

	/* in unit of 500us; 0 to disable स्वतः-pspoll */
	u8 min_स्वतः_pspoll_period;
पूर्ण;

पूर्णांक wsm_set_pm(काष्ठा cw1200_common *priv, स्थिर काष्ठा wsm_set_pm *arg);

/* 3.27 */
काष्ठा wsm_set_pm_complete अणु
	u8 psm;			/* WSM_PSM_... */
पूर्ण;

/* 3.28 */
#घोषणा WSM_SET_BSS_PARAMS_REQ_ID 0x0011
#घोषणा WSM_SET_BSS_PARAMS_RESP_ID 0x0411
काष्ठा wsm_set_bss_params अणु
	/* This resets the beacon loss counters only */
	u8 reset_beacon_loss;

	/* The number of lost consecutive beacons after which */
	/* the WLAN device should indicate the BSS-Lost event */
	/* to the WLAN host driver. */
	u8 beacon_lost_count;

	/* The AID received during the association process. */
	u16 aid;

	/* The operational rate set mask */
	u32 operational_rate_set;
पूर्ण;

पूर्णांक wsm_set_bss_params(काष्ठा cw1200_common *priv,
		       स्थिर काष्ठा wsm_set_bss_params *arg);

/* 3.30 */
#घोषणा WSM_ADD_KEY_REQ_ID         0x000C
#घोषणा WSM_ADD_KEY_RESP_ID        0x040C
काष्ठा wsm_add_key अणु
	u8 type;		/* WSM_KEY_TYPE_... */
	u8 index;		/* Key entry index: 0 -- WSM_KEY_MAX_INDEX */
	u16 reserved;
	जोड़ अणु
		काष्ठा अणु
			u8 peer[6];	/* MAC address of the peer station */
			u8 reserved;
			u8 keylen;		/* Key length in bytes */
			u8 keydata[16];		/* Key data */
		पूर्ण __packed wep_pairwise;
		काष्ठा अणु
			u8 keyid;	/* Unique per key identअगरier (0..3) */
			u8 keylen;		/* Key length in bytes */
			u16 reserved;
			u8 keydata[16];		/* Key data */
		पूर्ण __packed wep_group;
		काष्ठा अणु
			u8 peer[6];	/* MAC address of the peer station */
			u16 reserved;
			u8 keydata[16];	/* TKIP key data */
			u8 rx_mic_key[8];		/* Rx MIC key */
			u8 tx_mic_key[8];		/* Tx MIC key */
		पूर्ण __packed tkip_pairwise;
		काष्ठा अणु
			u8 keydata[16];	/* TKIP key data */
			u8 rx_mic_key[8];		/* Rx MIC key */
			u8 keyid;		/* Key ID */
			u8 reserved[3];
			u8 rx_seqnum[8];	/* Receive Sequence Counter */
		पूर्ण __packed tkip_group;
		काष्ठा अणु
			u8 peer[6];	/* MAC address of the peer station */
			u16 reserved;
			u8 keydata[16];	/* AES key data */
		पूर्ण __packed aes_pairwise;
		काष्ठा अणु
			u8 keydata[16];	/* AES key data */
			u8 keyid;		/* Key ID */
			u8 reserved[3];
			u8 rx_seqnum[8];	/* Receive Sequence Counter */
		पूर्ण __packed aes_group;
		काष्ठा अणु
			u8 peer[6];	/* MAC address of the peer station */
			u8 keyid;		/* Key ID */
			u8 reserved;
			u8 keydata[16];	/* WAPI key data */
			u8 mic_key[16];	/* MIC key data */
		पूर्ण __packed wapi_pairwise;
		काष्ठा अणु
			u8 keydata[16];	/* WAPI key data */
			u8 mic_key[16];	/* MIC key data */
			u8 keyid;		/* Key ID */
			u8 reserved[3];
		पूर्ण __packed wapi_group;
	पूर्ण __packed;
पूर्ण __packed;

पूर्णांक wsm_add_key(काष्ठा cw1200_common *priv, स्थिर काष्ठा wsm_add_key *arg);

/* 3.32 */
#घोषणा WSM_REMOVE_KEY_REQ_ID         0x000D
#घोषणा WSM_REMOVE_KEY_RESP_ID        0x040D
काष्ठा wsm_हटाओ_key अणु
	u8 index; /* Key entry index : 0-10 */
पूर्ण;

पूर्णांक wsm_हटाओ_key(काष्ठा cw1200_common *priv,
		   स्थिर काष्ठा wsm_हटाओ_key *arg);

/* 3.34 */
काष्ठा wsm_set_tx_queue_params अणु
	/* WSM_ACK_POLICY_... */
	u8 ackPolicy;

	/* Medium Time of TSPEC (in 32us units) allowed per */
	/* One Second Averaging Period क्रम this queue. */
	u16 allowedMediumTime;

	/* करोt11MaxTransmitMsduLअगरeसमय to be used क्रम the */
	/* specअगरied queue. */
	u32 maxTransmitLअगरeसमय;
पूर्ण;

काष्ठा wsm_tx_queue_params अणु
	/* NOTE: index is a linux queue id. */
	काष्ठा wsm_set_tx_queue_params params[4];
पूर्ण;


#घोषणा WSM_TX_QUEUE_SET(queue_params, queue, ack_policy, allowed_समय,\
		max_lअगरe_समय)	\
करो अणु							\
	काष्ठा wsm_set_tx_queue_params *p = &(queue_params)->params[queue]; \
	p->ackPolicy = (ack_policy);				\
	p->allowedMediumTime = (allowed_समय);				\
	p->maxTransmitLअगरeसमय = (max_lअगरe_समय);			\
पूर्ण जबतक (0)

पूर्णांक wsm_set_tx_queue_params(काष्ठा cw1200_common *priv,
			    स्थिर काष्ठा wsm_set_tx_queue_params *arg, u8 id);

/* 3.36 */
#घोषणा WSM_EDCA_PARAMS_REQ_ID 0x0013
#घोषणा WSM_EDCA_PARAMS_RESP_ID 0x0413
काष्ठा wsm_edca_queue_params अणु
	/* CWmin (in slots) क्रम the access class. */
	u16 cwmin;

	/* CWmax (in slots) क्रम the access class. */
	u16 cwmax;

	/* AIFS (in slots) क्रम the access class. */
	u16 aअगरns;

	/* TX OP Limit (in microseconds) क्रम the access class. */
	u16 txop_limit;

	/* करोt11MaxReceiveLअगरeसमय to be used क्रम the specअगरied */
	/* the access class. Overrides the global */
	/* करोt11MaxReceiveLअगरeसमय value */
	u32 max_rx_lअगरeसमय;
पूर्ण;

काष्ठा wsm_edca_params अणु
	/* NOTE: index is a linux queue id. */
	काष्ठा wsm_edca_queue_params params[4];
	bool uapsd_enable[4];
पूर्ण;

#घोषणा TXOP_UNIT 32
#घोषणा WSM_EDCA_SET(__edca, __queue, __aअगरs, __cw_min, __cw_max, __txop, __lअगरeसमय,\
		     __uapsd) \
	करो अणु							\
		काष्ठा wsm_edca_queue_params *p = &(__edca)->params[__queue]; \
		p->cwmin = __cw_min;					\
		p->cwmax = __cw_max;					\
		p->aअगरns = __aअगरs;					\
		p->txop_limit = ((__txop) * TXOP_UNIT);			\
		p->max_rx_lअगरeसमय = __lअगरeसमय;			\
		(__edca)->uapsd_enable[__queue] = (__uapsd);		\
	पूर्ण जबतक (0)

पूर्णांक wsm_set_edca_params(काष्ठा cw1200_common *priv,
			स्थिर काष्ठा wsm_edca_params *arg);

पूर्णांक wsm_set_uapsd_param(काष्ठा cw1200_common *priv,
			स्थिर काष्ठा wsm_edca_params *arg);

/* 3.38 */
/* Set-System info. Skipped क्रम now. Irrelevent. */

/* 3.40 */
#घोषणा WSM_SWITCH_CHANNEL_REQ_ID 0x0016
#घोषणा WSM_SWITCH_CHANNEL_RESP_ID 0x0416

काष्ठा wsm_चयन_channel अणु
	/* 1 - means the STA shall not transmit any further */
	/* frames until the channel चयन has completed */
	u8 mode;

	/* Number of TBTTs until channel चयन occurs. */
	/* 0 - indicates चयन shall occur at any समय */
	/* 1 - occurs immediately beक्रमe the next TBTT */
	u8 चयन_count;

	/* The new channel number to चयन to. */
	/* Note this is defined as per section 2.7. */
	u16 channel_number;
पूर्ण;

पूर्णांक wsm_चयन_channel(काष्ठा cw1200_common *priv,
		       स्थिर काष्ठा wsm_चयन_channel *arg);

#घोषणा WSM_START_REQ_ID 0x0017
#घोषणा WSM_START_RESP_ID 0x0417

काष्ठा wsm_start अणु
	/* WSM_START_MODE_... */
	/* [in] */ u8 mode;

	/* WSM_PHY_BAND_... */
	/* [in] */ u8 band;

	/* Channel number */
	/* [in] */ u16 channel_number;

	/* Client Traffic winकरोw in units of TU */
	/* Valid only when mode == ..._P2P */
	/* [in] */ u32 ct_winकरोw;

	/* Interval between two consecutive */
	/* beacon transmissions in TU. */
	/* [in] */ u32 beacon_पूर्णांकerval;

	/* DTIM period in terms of beacon पूर्णांकervals */
	/* [in] */ u8 dtim_period;

	/* WSM_JOIN_PREAMBLE_... */
	/* [in] */ u8 preamble;

	/* The delay समय (in microseconds) period */
	/* beक्रमe sending a probe-request. */
	/* [in] */ u8 probe_delay;

	/* Length of the SSID */
	/* [in] */ u8 ssid_len;

	/* SSID of the BSS or P2P_GO to be started now. */
	/* [in] */ u8 ssid[32];

	/* The basic supported rates क्रम the MiniAP. */
	/* [in] */ u32 basic_rate_set;
पूर्ण;

पूर्णांक wsm_start(काष्ठा cw1200_common *priv, स्थिर काष्ठा wsm_start *arg);

#घोषणा WSM_BEACON_TRANSMIT_REQ_ID 0x0018
#घोषणा WSM_BEACON_TRANSMIT_RESP_ID 0x0418

काष्ठा wsm_beacon_transmit अणु
	/* 1: enable; 0: disable */
	/* [in] */ u8 enable_beaconing;
पूर्ण;

पूर्णांक wsm_beacon_transmit(काष्ठा cw1200_common *priv,
			स्थिर काष्ठा wsm_beacon_transmit *arg);

पूर्णांक wsm_start_find(काष्ठा cw1200_common *priv);

पूर्णांक wsm_stop_find(काष्ठा cw1200_common *priv);

काष्ठा wsm_suspend_resume अणु
	/* See 3.52 */
	/* Link ID */
	/* [out] */ पूर्णांक link_id;
	/* Stop sending further Tx requests करोwn to device क्रम this link */
	/* [out] */ bool stop;
	/* Transmit multicast Frames */
	/* [out] */ bool multicast;
	/* The AC on which Tx to be suspended /resumed. */
	/* This is applicable only क्रम U-APSD */
	/* WSM_QUEUE_... */
	/* [out] */ पूर्णांक queue;
पूर्ण;

/* 3.54 Update-IE request. */
काष्ठा wsm_update_ie अणु
	/* WSM_UPDATE_IE_... */
	/* [in] */ u16 what;
	/* [in] */ u16 count;
	/* [in] */ u8 *ies;
	/* [in] */ माप_प्रकार length;
पूर्ण;

पूर्णांक wsm_update_ie(काष्ठा cw1200_common *priv,
		  स्थिर काष्ठा wsm_update_ie *arg);

/* 3.56 */
काष्ठा wsm_map_link अणु
	/* MAC address of the remote device */
	/* [in] */ u8 mac_addr[6];
	/* [in] */ u8 link_id;
पूर्ण;

पूर्णांक wsm_map_link(काष्ठा cw1200_common *priv, स्थिर काष्ठा wsm_map_link *arg);

/* ******************************************************************** */
/* MIB लघुcats							*/

अटल अंतरभूत पूर्णांक wsm_set_output_घातer(काष्ठा cw1200_common *priv,
				       पूर्णांक घातer_level)
अणु
	__le32 val = __cpu_to_le32(घातer_level);
	वापस wsm_ग_लिखो_mib(priv, WSM_MIB_ID_DOT11_CURRENT_TX_POWER_LEVEL,
			     &val, माप(val));
पूर्ण

अटल अंतरभूत पूर्णांक wsm_set_beacon_wakeup_period(काष्ठा cw1200_common *priv,
					       अचिन्हित dtim_पूर्णांकerval,
					       अचिन्हित listen_पूर्णांकerval)
अणु
	काष्ठा अणु
		u8 numBeaconPeriods;
		u8 reserved;
		__le16 listenInterval;
	पूर्ण val = अणु
		dtim_पूर्णांकerval, 0, __cpu_to_le16(listen_पूर्णांकerval)
	पूर्ण;

	अगर (dtim_पूर्णांकerval > 0xFF || listen_पूर्णांकerval > 0xFFFF)
		वापस -EINVAL;
	अन्यथा
		वापस wsm_ग_लिखो_mib(priv, WSM_MIB_ID_BEACON_WAKEUP_PERIOD,
				     &val, माप(val));
पूर्ण

काष्ठा wsm_rcpi_rssi_threshold अणु
	u8 rssiRcpiMode;	/* WSM_RCPI_RSSI_... */
	u8 lowerThreshold;
	u8 upperThreshold;
	u8 rollingAverageCount;
पूर्ण;

अटल अंतरभूत पूर्णांक wsm_set_rcpi_rssi_threshold(काष्ठा cw1200_common *priv,
					काष्ठा wsm_rcpi_rssi_threshold *arg)
अणु
	वापस wsm_ग_लिखो_mib(priv, WSM_MIB_ID_RCPI_RSSI_THRESHOLD, arg,
			     माप(*arg));
पूर्ण

काष्ठा wsm_mib_counters_table अणु
	__le32 plcp_errors;
	__le32 fcs_errors;
	__le32 tx_packets;
	__le32 rx_packets;
	__le32 rx_packet_errors;
	__le32 rx_decryption_failures;
	__le32 rx_mic_failures;
	__le32 rx_no_key_failures;
	__le32 tx_multicast_frames;
	__le32 tx_frames_success;
	__le32 tx_frame_failures;
	__le32 tx_frames_retried;
	__le32 tx_frames_multi_retried;
	__le32 rx_frame_duplicates;
	__le32 rts_success;
	__le32 rts_failures;
	__le32 ack_failures;
	__le32 rx_multicast_frames;
	__le32 rx_frames_success;
	__le32 rx_cmac_icv_errors;
	__le32 rx_cmac_replays;
	__le32 rx_mgmt_ccmp_replays;
पूर्ण __packed;

अटल अंतरभूत पूर्णांक wsm_get_counters_table(काष्ठा cw1200_common *priv,
					 काष्ठा wsm_mib_counters_table *arg)
अणु
	वापस wsm_पढ़ो_mib(priv, WSM_MIB_ID_COUNTERS_TABLE,
			    arg, माप(*arg));
पूर्ण

अटल अंतरभूत पूर्णांक wsm_get_station_id(काष्ठा cw1200_common *priv, u8 *mac)
अणु
	वापस wsm_पढ़ो_mib(priv, WSM_MIB_ID_DOT11_STATION_ID, mac, ETH_ALEN);
पूर्ण

काष्ठा wsm_rx_filter अणु
	bool promiscuous;
	bool bssid;
	bool fcs;
	bool probeResponder;
पूर्ण;

अटल अंतरभूत पूर्णांक wsm_set_rx_filter(काष्ठा cw1200_common *priv,
				    स्थिर काष्ठा wsm_rx_filter *arg)
अणु
	__le32 val = 0;
	अगर (arg->promiscuous)
		val |= __cpu_to_le32(BIT(0));
	अगर (arg->bssid)
		val |= __cpu_to_le32(BIT(1));
	अगर (arg->fcs)
		val |= __cpu_to_le32(BIT(2));
	अगर (arg->probeResponder)
		val |= __cpu_to_le32(BIT(3));
	वापस wsm_ग_लिखो_mib(priv, WSM_MIB_ID_RX_FILTER, &val, माप(val));
पूर्ण

पूर्णांक wsm_set_probe_responder(काष्ठा cw1200_common *priv, bool enable);

#घोषणा WSM_BEACON_FILTER_IE_HAS_CHANGED	BIT(0)
#घोषणा WSM_BEACON_FILTER_IE_NO_LONGER_PRESENT	BIT(1)
#घोषणा WSM_BEACON_FILTER_IE_HAS_APPEARED	BIT(2)

काष्ठा wsm_beacon_filter_table_entry अणु
	u8	ie_id;
	u8	flags;
	u8	oui[3];
	u8	match_data[3];
पूर्ण __packed;

काष्ठा wsm_mib_beacon_filter_table अणु
	__le32 num;
	काष्ठा wsm_beacon_filter_table_entry entry[10];
पूर्ण __packed;

अटल अंतरभूत पूर्णांक wsm_set_beacon_filter_table(काष्ठा cw1200_common *priv,
					      काष्ठा wsm_mib_beacon_filter_table *ft)
अणु
	माप_प्रकार size = __le32_to_cpu(ft->num) *
		     माप(काष्ठा wsm_beacon_filter_table_entry) +
		     माप(__le32);

	वापस wsm_ग_लिखो_mib(priv, WSM_MIB_ID_BEACON_FILTER_TABLE, ft, size);
पूर्ण

#घोषणा WSM_BEACON_FILTER_ENABLE	BIT(0) /* Enable/disable beacon filtering */
#घोषणा WSM_BEACON_FILTER_AUTO_ERP	BIT(1) /* If 1 FW will handle ERP IE changes पूर्णांकernally */

काष्ठा wsm_beacon_filter_control अणु
	पूर्णांक enabled;
	पूर्णांक bcn_count;
पूर्ण;

अटल अंतरभूत पूर्णांक wsm_beacon_filter_control(काष्ठा cw1200_common *priv,
					काष्ठा wsm_beacon_filter_control *arg)
अणु
	काष्ठा अणु
		__le32 enabled;
		__le32 bcn_count;
	पूर्ण val;
	val.enabled = __cpu_to_le32(arg->enabled);
	val.bcn_count = __cpu_to_le32(arg->bcn_count);
	वापस wsm_ग_लिखो_mib(priv, WSM_MIB_ID_BEACON_FILTER_ENABLE, &val,
			     माप(val));
पूर्ण

क्रमागत wsm_घातer_mode अणु
	wsm_घातer_mode_active = 0,
	wsm_घातer_mode_करोze = 1,
	wsm_घातer_mode_quiescent = 2,
पूर्ण;

काष्ठा wsm_operational_mode अणु
	क्रमागत wsm_घातer_mode घातer_mode;
	पूर्णांक disable_more_flag_usage;
	पूर्णांक perक्रमm_ant_भागersity;
पूर्ण;

अटल अंतरभूत पूर्णांक wsm_set_operational_mode(काष्ठा cw1200_common *priv,
					स्थिर काष्ठा wsm_operational_mode *arg)
अणु
	u8 val = arg->घातer_mode;
	अगर (arg->disable_more_flag_usage)
		val |= BIT(4);
	अगर (arg->perक्रमm_ant_भागersity)
		val |= BIT(5);
	वापस wsm_ग_लिखो_mib(priv, WSM_MIB_ID_OPERATIONAL_POWER_MODE, &val,
			     माप(val));
पूर्ण

काष्ठा wsm_ढाँचा_frame अणु
	u8 frame_type;
	u8 rate;
	काष्ठा sk_buff *skb;
पूर्ण;

अटल अंतरभूत पूर्णांक wsm_set_ढाँचा_frame(काष्ठा cw1200_common *priv,
					 काष्ठा wsm_ढाँचा_frame *arg)
अणु
	पूर्णांक ret;
	u8 *p = skb_push(arg->skb, 4);
	p[0] = arg->frame_type;
	p[1] = arg->rate;
	((__le16 *)p)[1] = __cpu_to_le16(arg->skb->len - 4);
	ret = wsm_ग_लिखो_mib(priv, WSM_MIB_ID_TEMPLATE_FRAME, p, arg->skb->len);
	skb_pull(arg->skb, 4);
	वापस ret;
पूर्ण


काष्ठा wsm_रक्षित_mgmt_policy अणु
	bool रक्षितMgmtEnable;
	bool unरक्षितMgmtFramesAllowed;
	bool encryptionForAuthFrame;
पूर्ण;

अटल अंतरभूत पूर्णांक wsm_set_रक्षित_mgmt_policy(काष्ठा cw1200_common *priv,
		काष्ठा wsm_रक्षित_mgmt_policy *arg)
अणु
	__le32 val = 0;
	पूर्णांक ret;
	अगर (arg->रक्षितMgmtEnable)
		val |= __cpu_to_le32(BIT(0));
	अगर (arg->unरक्षितMgmtFramesAllowed)
		val |= __cpu_to_le32(BIT(1));
	अगर (arg->encryptionForAuthFrame)
		val |= __cpu_to_le32(BIT(2));
	ret = wsm_ग_लिखो_mib(priv, WSM_MIB_ID_PROTECTED_MGMT_POLICY,
			&val, माप(val));
	वापस ret;
पूर्ण

काष्ठा wsm_mib_block_ack_policy अणु
	u8 tx_tid;
	u8 reserved1;
	u8 rx_tid;
	u8 reserved2;
पूर्ण __packed;

अटल अंतरभूत पूर्णांक wsm_set_block_ack_policy(काष्ठा cw1200_common *priv,
					   u8 tx_tid_policy,
					   u8 rx_tid_policy)
अणु
	काष्ठा wsm_mib_block_ack_policy val = अणु
		.tx_tid = tx_tid_policy,
		.rx_tid = rx_tid_policy,
	पूर्ण;
	वापस wsm_ग_लिखो_mib(priv, WSM_MIB_ID_BLOCK_ACK_POLICY, &val,
			     माप(val));
पूर्ण

काष्ठा wsm_mib_association_mode अणु
	u8 flags;		/* WSM_ASSOCIATION_MODE_... */
	u8 preamble;	/* WSM_JOIN_PREAMBLE_... */
	u8 greenfield;	/* 1 क्रम greenfield */
	u8 mpdu_start_spacing;
	__le32 basic_rate_set;
पूर्ण __packed;

अटल अंतरभूत पूर्णांक wsm_set_association_mode(काष्ठा cw1200_common *priv,
					   काष्ठा wsm_mib_association_mode *arg)
अणु
	वापस wsm_ग_लिखो_mib(priv, WSM_MIB_ID_SET_ASSOCIATION_MODE, arg,
			     माप(*arg));
पूर्ण

#घोषणा WSM_TX_RATE_POLICY_FLAG_TERMINATE_WHEN_FINISHED BIT(2)
#घोषणा WSM_TX_RATE_POLICY_FLAG_COUNT_INITIAL_TRANSMIT BIT(3)
काष्ठा wsm_tx_rate_retry_policy अणु
	u8 index;
	u8 लघु_retries;
	u8 दीर्घ_retries;
	/* BIT(2) - Terminate retries when Tx rate retry policy
	 *          finishes.
	 * BIT(3) - Count initial frame transmission as part of
	 *          rate retry counting but not as a retry
	 *          attempt
	 */
	u8 flags;
	u8 rate_recoveries;
	u8 reserved[3];
	__le32 rate_count_indices[3];
पूर्ण __packed;

काष्ठा wsm_set_tx_rate_retry_policy अणु
	u8 num;
	u8 reserved[3];
	काष्ठा wsm_tx_rate_retry_policy tbl[8];
पूर्ण __packed;

अटल अंतरभूत पूर्णांक wsm_set_tx_rate_retry_policy(काष्ठा cw1200_common *priv,
				काष्ठा wsm_set_tx_rate_retry_policy *arg)
अणु
	माप_प्रकार size = 4 + arg->num * माप(काष्ठा wsm_tx_rate_retry_policy);
	वापस wsm_ग_लिखो_mib(priv, WSM_MIB_ID_SET_TX_RATE_RETRY_POLICY, arg,
			     size);
पूर्ण

/* 4.32 SetEtherTypeDataFrameFilter */
काष्ठा wsm_ether_type_filter_hdr अणु
	u8 num;		/* Up to WSM_MAX_FILTER_ELEMENTS */
	u8 reserved[3];
पूर्ण __packed;

काष्ठा wsm_ether_type_filter अणु
	u8 action;	/* WSM_FILTER_ACTION_XXX */
	u8 reserved;
	__le16 type;	/* Type of ethernet frame */
पूर्ण __packed;

अटल अंतरभूत पूर्णांक wsm_set_ether_type_filter(काष्ठा cw1200_common *priv,
				काष्ठा wsm_ether_type_filter_hdr *arg)
अणु
	माप_प्रकार size = माप(काष्ठा wsm_ether_type_filter_hdr) +
		arg->num * माप(काष्ठा wsm_ether_type_filter);
	वापस wsm_ग_लिखो_mib(priv, WSM_MIB_ID_SET_ETHERTYPE_DATAFRAME_FILTER,
		arg, size);
पूर्ण

/* 4.33 SetUDPPortDataFrameFilter */
काष्ठा wsm_udp_port_filter_hdr अणु
	u8 num;		/* Up to WSM_MAX_FILTER_ELEMENTS */
	u8 reserved[3];
पूर्ण __packed;

काष्ठा wsm_udp_port_filter अणु
	u8 action;	/* WSM_FILTER_ACTION_XXX */
	u8 type;		/* WSM_FILTER_PORT_TYPE_XXX */
	__le16 port;		/* Port number */
पूर्ण __packed;

अटल अंतरभूत पूर्णांक wsm_set_udp_port_filter(काष्ठा cw1200_common *priv,
				काष्ठा wsm_udp_port_filter_hdr *arg)
अणु
	माप_प्रकार size = माप(काष्ठा wsm_udp_port_filter_hdr) +
		arg->num * माप(काष्ठा wsm_udp_port_filter);
	वापस wsm_ग_लिखो_mib(priv, WSM_MIB_ID_SET_UDPPORT_DATAFRAME_FILTER,
		arg, size);
पूर्ण

/* Unकरोcumented MIBs: */
/* 4.35 P2PDeviceInfo */
#घोषणा D11_MAX_SSID_LEN		(32)

काष्ठा wsm_p2p_device_type अणु
	__le16 category_id;
	u8 oui[4];
	__le16 subcategory_id;
पूर्ण __packed;

काष्ठा wsm_p2p_device_info अणु
	काष्ठा wsm_p2p_device_type primaryDevice;
	u8 reserved1[3];
	u8 devname_size;
	u8 local_devname[D11_MAX_SSID_LEN];
	u8 reserved2[3];
	u8 num_secdev_supported;
	काष्ठा wsm_p2p_device_type secdevs[];
पूर्ण __packed;

/* 4.36 SetWCDMABand - WO */
काष्ठा wsm_cdma_band अणु
	u8 wcdma_band;
	u8 reserved[3];
पूर्ण __packed;

/* 4.37 GroupTxSequenceCounter - RO */
काष्ठा wsm_group_tx_seq अणु
	__le32 bits_47_16;
	__le16 bits_15_00;
	__le16 reserved;
पूर्ण __packed;

/* 4.39 SetHtProtection - WO */
#घोषणा WSM_DUAL_CTS_PROT_ENB		(1 << 0)
#घोषणा WSM_NON_GREENFIELD_STA_PRESENT  (1 << 1)
#घोषणा WSM_HT_PROT_MODE__NO_PROT	(0 << 2)
#घोषणा WSM_HT_PROT_MODE__NON_MEMBER	(1 << 2)
#घोषणा WSM_HT_PROT_MODE__20_MHZ	(2 << 2)
#घोषणा WSM_HT_PROT_MODE__NON_HT_MIXED	(3 << 2)
#घोषणा WSM_LSIG_TXOP_PROT_FULL		(1 << 4)
#घोषणा WSM_LARGE_L_LENGTH_PROT		(1 << 5)

काष्ठा wsm_ht_protection अणु
	__le32 flags;
पूर्ण __packed;

/* 4.40 GPIO Command - R/W */
#घोषणा WSM_GPIO_COMMAND_SETUP	0
#घोषणा WSM_GPIO_COMMAND_READ	1
#घोषणा WSM_GPIO_COMMAND_WRITE	2
#घोषणा WSM_GPIO_COMMAND_RESET	3
#घोषणा WSM_GPIO_ALL_PINS	0xFF

काष्ठा wsm_gpio_command अणु
	u8 command;
	u8 pin;
	__le16 config;
पूर्ण __packed;

/* 4.41 TSFCounter - RO */
काष्ठा wsm_tsf_counter अणु
	__le64 tsf_counter;
पूर्ण __packed;

/* 4.43 Keep alive period */
काष्ठा wsm_keep_alive_period अणु
	__le16 period;
	u8 reserved[2];
पूर्ण __packed;

अटल अंतरभूत पूर्णांक wsm_keep_alive_period(काष्ठा cw1200_common *priv,
					पूर्णांक period)
अणु
	काष्ठा wsm_keep_alive_period arg = अणु
		.period = __cpu_to_le16(period),
	पूर्ण;
	वापस wsm_ग_लिखो_mib(priv, WSM_MIB_ID_KEEP_ALIVE_PERIOD,
			&arg, माप(arg));
पूर्ण;

/* BSSID filtering */
काष्ठा wsm_set_bssid_filtering अणु
	u8 filter;
	u8 reserved[3];
पूर्ण __packed;

अटल अंतरभूत पूर्णांक wsm_set_bssid_filtering(काष्ठा cw1200_common *priv,
					  bool enabled)
अणु
	काष्ठा wsm_set_bssid_filtering arg = अणु
		.filter = !enabled,
	पूर्ण;
	वापस wsm_ग_लिखो_mib(priv, WSM_MIB_ID_DISABLE_BSSID_FILTER,
			&arg, माप(arg));
पूर्ण

/* Multicast filtering - 4.5 */
काष्ठा wsm_mib_multicast_filter अणु
	__le32 enable;
	__le32 num_addrs;
	u8 macaddrs[WSM_MAX_GRP_ADDRTABLE_ENTRIES][ETH_ALEN];
पूर्ण __packed;

अटल अंतरभूत पूर्णांक wsm_set_multicast_filter(काष्ठा cw1200_common *priv,
					   काष्ठा wsm_mib_multicast_filter *fp)
अणु
	वापस wsm_ग_लिखो_mib(priv, WSM_MIB_ID_DOT11_GROUP_ADDRESSES_TABLE,
			     fp, माप(*fp));
पूर्ण

/* ARP IPv4 filtering - 4.10 */
काष्ठा wsm_mib_arp_ipv4_filter अणु
	__le32 enable;
	__be32 ipv4addrs[WSM_MAX_ARP_IP_ADDRTABLE_ENTRIES];
पूर्ण __packed;

अटल अंतरभूत पूर्णांक wsm_set_arp_ipv4_filter(काष्ठा cw1200_common *priv,
					  काष्ठा wsm_mib_arp_ipv4_filter *fp)
अणु
	वापस wsm_ग_लिखो_mib(priv, WSM_MIB_ID_ARP_IP_ADDRESSES_TABLE,
			    fp, माप(*fp));
पूर्ण

/* P2P Power Save Mode Info - 4.31 */
काष्ठा wsm_p2p_ps_modeinfo अणु
	u8	opp_ps_ct_winकरोw;
	u8	count;
	u8	reserved;
	u8	dtim_count;
	__le32	duration;
	__le32	पूर्णांकerval;
	__le32	start_समय;
पूर्ण __packed;

अटल अंतरभूत पूर्णांक wsm_set_p2p_ps_modeinfo(काष्ठा cw1200_common *priv,
					  काष्ठा wsm_p2p_ps_modeinfo *mi)
अणु
	वापस wsm_ग_लिखो_mib(priv, WSM_MIB_ID_P2P_PS_MODE_INFO,
			     mi, माप(*mi));
पूर्ण

अटल अंतरभूत पूर्णांक wsm_get_p2p_ps_modeinfo(काष्ठा cw1200_common *priv,
					  काष्ठा wsm_p2p_ps_modeinfo *mi)
अणु
	वापस wsm_पढ़ो_mib(priv, WSM_MIB_ID_P2P_PS_MODE_INFO,
			    mi, माप(*mi));
पूर्ण

/* UseMultiTxConfMessage */

अटल अंतरभूत पूर्णांक wsm_use_multi_tx_conf(काष्ठा cw1200_common *priv,
					bool enabled)
अणु
	__le32 arg = enabled ? __cpu_to_le32(1) : 0;

	वापस wsm_ग_लिखो_mib(priv, WSM_MIB_USE_MULTI_TX_CONF,
			&arg, माप(arg));
पूर्ण


/* 4.26 SetUpasdInक्रमmation */
काष्ठा wsm_uapsd_info अणु
	__le16 uapsd_flags;
	__le16 min_स्वतः_trigger_पूर्णांकerval;
	__le16 max_स्वतः_trigger_पूर्णांकerval;
	__le16 स्वतः_trigger_step;
पूर्ण;

अटल अंतरभूत पूर्णांक wsm_set_uapsd_info(काष्ठा cw1200_common *priv,
				     काष्ठा wsm_uapsd_info *arg)
अणु
	वापस wsm_ग_लिखो_mib(priv, WSM_MIB_ID_SET_UAPSD_INFORMATION,
				arg, माप(*arg));
पूर्ण

/* 4.22 OverrideInternalTxRate */
काष्ठा wsm_override_पूर्णांकernal_txrate अणु
	u8 पूर्णांकernalTxRate;
	u8 nonErpInternalTxRate;
	u8 reserved[2];
पूर्ण __packed;

अटल अंतरभूत पूर्णांक wsm_set_override_पूर्णांकernal_txrate(काष्ठा cw1200_common *priv,
				     काष्ठा wsm_override_पूर्णांकernal_txrate *arg)
अणु
	वापस wsm_ग_लिखो_mib(priv, WSM_MIB_ID_OVERRIDE_INTERNAL_TX_RATE,
				arg, माप(*arg));
पूर्ण

/* ******************************************************************** */
/* WSM TX port control							*/

व्योम wsm_lock_tx(काष्ठा cw1200_common *priv);
व्योम wsm_lock_tx_async(काष्ठा cw1200_common *priv);
bool wsm_flush_tx(काष्ठा cw1200_common *priv);
व्योम wsm_unlock_tx(काष्ठा cw1200_common *priv);

/* ******************************************************************** */
/* WSM / BH API								*/

पूर्णांक wsm_handle_exception(काष्ठा cw1200_common *priv, u8 *data, माप_प्रकार len);
पूर्णांक wsm_handle_rx(काष्ठा cw1200_common *priv, u16 id, काष्ठा wsm_hdr *wsm,
		  काष्ठा sk_buff **skb_p);

/* ******************************************************************** */
/* wsm_buf API								*/

काष्ठा wsm_buf अणु
	u8 *begin;
	u8 *data;
	u8 *end;
पूर्ण;

व्योम wsm_buf_init(काष्ठा wsm_buf *buf);
व्योम wsm_buf_deinit(काष्ठा wsm_buf *buf);

/* ******************************************************************** */
/* wsm_cmd API								*/

काष्ठा wsm_cmd अणु
	spinlock_t lock; /* Protect काष्ठाure from multiple access */
	पूर्णांक करोne;
	u8 *ptr;
	माप_प्रकार len;
	व्योम *arg;
	पूर्णांक ret;
	u16 cmd;
पूर्ण;

/* ******************************************************************** */
/* WSM TX buffer access							*/

पूर्णांक wsm_get_tx(काष्ठा cw1200_common *priv, u8 **data,
	       माप_प्रकार *tx_len, पूर्णांक *burst);
व्योम wsm_txed(काष्ठा cw1200_common *priv, u8 *data);

/* ******************************************************************** */
/* Queue mapping: WSM <---> linux					*/
/* Linux: VO VI BE BK							*/
/* WSM:   BE BK VI VO							*/

अटल अंतरभूत u8 wsm_queue_id_to_linux(u8 queue_id)
अणु
	अटल स्थिर u8 queue_mapping[] = अणु
		2, 3, 1, 0
	पूर्ण;
	वापस queue_mapping[queue_id];
पूर्ण

अटल अंतरभूत u8 wsm_queue_id_to_wsm(u8 queue_id)
अणु
	अटल स्थिर u8 queue_mapping[] = अणु
		3, 2, 0, 1
	पूर्ण;
	वापस queue_mapping[queue_id];
पूर्ण

#पूर्ण_अगर /* CW1200_HWIO_H_INCLUDED */
