<शैली गुरु>
/*
 * NXP Wireless LAN device driver: Firmware specअगरic macros & काष्ठाures
 *
 * Copyright 2011-2020 NXP
 *
 * This software file (the "File") is distributed by NXP
 * under the terms of the GNU General Public License Version 2, June 1991
 * (the "License").  You may use, redistribute and/or modअगरy this File in
 * accordance with the terms and conditions of the License, a copy of which
 * is available by writing to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fअगरth Floor, Boston, MA 02110-1301 USA or on the
 * worldwide web at http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 * THE खाता IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE
 * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about
 * this warranty disclaimer.
 */

#अगर_अघोषित _MWIFIEX_FW_H_
#घोषणा _MWIFIEX_FW_H_

#समावेश <linux/अगर_ether.h>


#घोषणा INTF_HEADER_LEN     4

काष्ठा rfc_1042_hdr अणु
	u8 llc_dsap;
	u8 llc_ssap;
	u8 llc_ctrl;
	u8 snap_oui[3];
	__be16 snap_type;
पूर्ण __packed;

काष्ठा rx_packet_hdr अणु
	काष्ठा ethhdr eth803_hdr;
	काष्ठा rfc_1042_hdr rfc1042_hdr;
पूर्ण __packed;

काष्ठा tx_packet_hdr अणु
	काष्ठा ethhdr eth803_hdr;
	काष्ठा rfc_1042_hdr rfc1042_hdr;
पूर्ण __packed;

काष्ठा mwअगरiex_fw_header अणु
	__le32 dnld_cmd;
	__le32 base_addr;
	__le32 data_length;
	__le32 crc;
पूर्ण __packed;

काष्ठा mwअगरiex_fw_data अणु
	काष्ठा mwअगरiex_fw_header header;
	__le32 seq_num;
	u8 data[1];
पूर्ण __packed;

काष्ठा mwअगरiex_fw_dump_header अणु
	__le16          seq_num;
	__le16          reserved;
	__le16          type;
	__le16          len;
पूर्ण __packed;

#घोषणा FW_DUMP_INFO_ENDED 0x0002

#घोषणा MWIFIEX_FW_DNLD_CMD_1 0x1
#घोषणा MWIFIEX_FW_DNLD_CMD_5 0x5
#घोषणा MWIFIEX_FW_DNLD_CMD_6 0x6
#घोषणा MWIFIEX_FW_DNLD_CMD_7 0x7

#घोषणा B_SUPPORTED_RATES               5
#घोषणा G_SUPPORTED_RATES               9
#घोषणा BG_SUPPORTED_RATES              13
#घोषणा A_SUPPORTED_RATES               9
#घोषणा HOSTCMD_SUPPORTED_RATES         14
#घोषणा N_SUPPORTED_RATES               3
#घोषणा ALL_802_11_BANDS           (BAND_A | BAND_B | BAND_G | BAND_GN | \
				    BAND_AN | BAND_AAC)

#घोषणा FW_MULTI_BANDS_SUPPORT  (BIT(8) | BIT(9) | BIT(10) | BIT(11) | \
				 BIT(13))
#घोषणा IS_SUPPORT_MULTI_BANDS(adapter)        \
	(adapter->fw_cap_info & FW_MULTI_BANDS_SUPPORT)

/* bit 13: 11ac BAND_AAC
 * bit 12: reserved क्रम lab testing, will be reused क्रम BAND_AN
 * bit 11: 11n  BAND_GN
 * bit 10: 11a  BAND_A
 * bit 9: 11g   BAND_G
 * bit 8: 11b   BAND_B
 * Map these bits to band capability by right shअगरting 8 bits.
 */
#घोषणा GET_FW_DEFAULT_BANDS(adapter)  \
	    (((adapter->fw_cap_info & 0x2f00) >> 8) & \
	     ALL_802_11_BANDS)

#घोषणा HostCmd_WEP_KEY_INDEX_MASK              0x3fff

#घोषणा KEY_INFO_ENABLED        0x01
क्रमागत KEY_TYPE_ID अणु
	KEY_TYPE_ID_WEP = 0,
	KEY_TYPE_ID_TKIP,
	KEY_TYPE_ID_AES,
	KEY_TYPE_ID_WAPI,
	KEY_TYPE_ID_AES_CMAC,
	KEY_TYPE_ID_AES_CMAC_DEF,
पूर्ण;

#घोषणा WPA_PN_SIZE		8
#घोषणा KEY_PARAMS_FIXED_LEN	10
#घोषणा KEY_INDEX_MASK		0xf
#घोषणा KEY_API_VER_MAJOR_V2	2

#घोषणा KEY_MCAST	BIT(0)
#घोषणा KEY_UNICAST	BIT(1)
#घोषणा KEY_ENABLED	BIT(2)
#घोषणा KEY_DEFAULT	BIT(3)
#घोषणा KEY_TX_KEY	BIT(4)
#घोषणा KEY_RX_KEY	BIT(5)
#घोषणा KEY_IGTK	BIT(10)

#घोषणा WAPI_KEY_LEN			(WLAN_KEY_LEN_SMS4 + PN_LEN + 2)

#घोषणा MAX_POLL_TRIES			100
#घोषणा MAX_FIRMWARE_POLL_TRIES			150

#घोषणा FIRMWARE_READY_SDIO				0xfedc
#घोषणा FIRMWARE_READY_PCIE				0xfedcba00

#घोषणा MWIFIEX_COEX_MODE_TIMESHARE			0x01
#घोषणा MWIFIEX_COEX_MODE_SPATIAL			0x82

क्रमागत mwअगरiex_usb_ep अणु
	MWIFIEX_USB_EP_CMD_EVENT = 1,
	MWIFIEX_USB_EP_DATA = 2,
	MWIFIEX_USB_EP_DATA_CH2 = 3,
पूर्ण;

क्रमागत MWIFIEX_802_11_PRIVACY_FILTER अणु
	MWIFIEX_802_11_PRIV_FILTER_ACCEPT_ALL,
	MWIFIEX_802_11_PRIV_FILTER_8021X_WEP
पूर्ण;

#घोषणा CAL_SNR(RSSI, NF)		((s16)((s16)(RSSI)-(s16)(NF)))
#घोषणा CAL_RSSI(SNR, NF)		((s16)((s16)(SNR)+(s16)(NF)))

#घोषणा UAP_BSS_PARAMS_I			0
#घोषणा UAP_CUSTOM_IE_I				1
#घोषणा MWIFIEX_AUTO_IDX_MASK			0xffff
#घोषणा MWIFIEX_DELETE_MASK			0x0000
#घोषणा MGMT_MASK_ASSOC_REQ			0x01
#घोषणा MGMT_MASK_REASSOC_REQ			0x04
#घोषणा MGMT_MASK_ASSOC_RESP			0x02
#घोषणा MGMT_MASK_REASSOC_RESP			0x08
#घोषणा MGMT_MASK_PROBE_REQ			0x10
#घोषणा MGMT_MASK_PROBE_RESP			0x20
#घोषणा MGMT_MASK_BEACON			0x100

#घोषणा TLV_TYPE_UAP_SSID			0x0000
#घोषणा TLV_TYPE_UAP_RATES			0x0001
#घोषणा TLV_TYPE_PWR_CONSTRAINT			0x0020

#घोषणा PROPRIETARY_TLV_BASE_ID                 0x0100
#घोषणा TLV_TYPE_KEY_MATERIAL       (PROPRIETARY_TLV_BASE_ID + 0)
#घोषणा TLV_TYPE_CHANLIST           (PROPRIETARY_TLV_BASE_ID + 1)
#घोषणा TLV_TYPE_NUMPROBES          (PROPRIETARY_TLV_BASE_ID + 2)
#घोषणा TLV_TYPE_RSSI_LOW           (PROPRIETARY_TLV_BASE_ID + 4)
#घोषणा TLV_TYPE_PASSTHROUGH        (PROPRIETARY_TLV_BASE_ID + 10)
#घोषणा TLV_TYPE_WMMQSTATUS         (PROPRIETARY_TLV_BASE_ID + 16)
#घोषणा TLV_TYPE_WILDCARDSSID       (PROPRIETARY_TLV_BASE_ID + 18)
#घोषणा TLV_TYPE_TSFTIMESTAMP       (PROPRIETARY_TLV_BASE_ID + 19)
#घोषणा TLV_TYPE_RSSI_HIGH          (PROPRIETARY_TLV_BASE_ID + 22)
#घोषणा TLV_TYPE_BGSCAN_START_LATER (PROPRIETARY_TLV_BASE_ID + 30)
#घोषणा TLV_TYPE_AUTH_TYPE          (PROPRIETARY_TLV_BASE_ID + 31)
#घोषणा TLV_TYPE_STA_MAC_ADDR       (PROPRIETARY_TLV_BASE_ID + 32)
#घोषणा TLV_TYPE_BSSID              (PROPRIETARY_TLV_BASE_ID + 35)
#घोषणा TLV_TYPE_CHANNELBANDLIST    (PROPRIETARY_TLV_BASE_ID + 42)
#घोषणा TLV_TYPE_UAP_BEACON_PERIOD  (PROPRIETARY_TLV_BASE_ID + 44)
#घोषणा TLV_TYPE_UAP_DTIM_PERIOD    (PROPRIETARY_TLV_BASE_ID + 45)
#घोषणा TLV_TYPE_UAP_BCAST_SSID     (PROPRIETARY_TLV_BASE_ID + 48)
#घोषणा TLV_TYPE_UAP_RTS_THRESHOLD  (PROPRIETARY_TLV_BASE_ID + 51)
#घोषणा TLV_TYPE_UAP_AO_TIMER       (PROPRIETARY_TLV_BASE_ID + 57)
#घोषणा TLV_TYPE_UAP_WEP_KEY        (PROPRIETARY_TLV_BASE_ID + 59)
#घोषणा TLV_TYPE_UAP_WPA_PASSPHRASE (PROPRIETARY_TLV_BASE_ID + 60)
#घोषणा TLV_TYPE_UAP_ENCRY_PROTOCOL (PROPRIETARY_TLV_BASE_ID + 64)
#घोषणा TLV_TYPE_UAP_AKMP           (PROPRIETARY_TLV_BASE_ID + 65)
#घोषणा TLV_TYPE_UAP_FRAG_THRESHOLD (PROPRIETARY_TLV_BASE_ID + 70)
#घोषणा TLV_TYPE_RATE_DROP_CONTROL  (PROPRIETARY_TLV_BASE_ID + 82)
#घोषणा TLV_TYPE_RATE_SCOPE         (PROPRIETARY_TLV_BASE_ID + 83)
#घोषणा TLV_TYPE_POWER_GROUP        (PROPRIETARY_TLV_BASE_ID + 84)
#घोषणा TLV_TYPE_BSS_SCAN_RSP       (PROPRIETARY_TLV_BASE_ID + 86)
#घोषणा TLV_TYPE_BSS_SCAN_INFO      (PROPRIETARY_TLV_BASE_ID + 87)
#घोषणा TLV_TYPE_CHANRPT_11H_BASIC  (PROPRIETARY_TLV_BASE_ID + 91)
#घोषणा TLV_TYPE_UAP_RETRY_LIMIT    (PROPRIETARY_TLV_BASE_ID + 93)
#घोषणा TLV_TYPE_WAPI_IE            (PROPRIETARY_TLV_BASE_ID + 94)
#घोषणा TLV_TYPE_ROBUST_COEX        (PROPRIETARY_TLV_BASE_ID + 96)
#घोषणा TLV_TYPE_UAP_MGMT_FRAME     (PROPRIETARY_TLV_BASE_ID + 104)
#घोषणा TLV_TYPE_MGMT_IE            (PROPRIETARY_TLV_BASE_ID + 105)
#घोषणा TLV_TYPE_AUTO_DS_PARAM      (PROPRIETARY_TLV_BASE_ID + 113)
#घोषणा TLV_TYPE_PS_PARAM           (PROPRIETARY_TLV_BASE_ID + 114)
#घोषणा TLV_TYPE_UAP_PS_AO_TIMER    (PROPRIETARY_TLV_BASE_ID + 123)
#घोषणा TLV_TYPE_PWK_CIPHER         (PROPRIETARY_TLV_BASE_ID + 145)
#घोषणा TLV_TYPE_GWK_CIPHER         (PROPRIETARY_TLV_BASE_ID + 146)
#घोषणा TLV_TYPE_TX_PAUSE           (PROPRIETARY_TLV_BASE_ID + 148)
#घोषणा TLV_TYPE_RXBA_SYNC          (PROPRIETARY_TLV_BASE_ID + 153)
#घोषणा TLV_TYPE_COALESCE_RULE      (PROPRIETARY_TLV_BASE_ID + 154)
#घोषणा TLV_TYPE_KEY_PARAM_V2       (PROPRIETARY_TLV_BASE_ID + 156)
#घोषणा TLV_TYPE_REPEAT_COUNT       (PROPRIETARY_TLV_BASE_ID + 176)
#घोषणा TLV_TYPE_PS_PARAMS_IN_HS    (PROPRIETARY_TLV_BASE_ID + 181)
#घोषणा TLV_TYPE_MULTI_CHAN_INFO    (PROPRIETARY_TLV_BASE_ID + 183)
#घोषणा TLV_TYPE_MC_GROUP_INFO      (PROPRIETARY_TLV_BASE_ID + 184)
#घोषणा TLV_TYPE_TDLS_IDLE_TIMEOUT  (PROPRIETARY_TLV_BASE_ID + 194)
#घोषणा TLV_TYPE_SCAN_CHANNEL_GAP   (PROPRIETARY_TLV_BASE_ID + 197)
#घोषणा TLV_TYPE_API_REV            (PROPRIETARY_TLV_BASE_ID + 199)
#घोषणा TLV_TYPE_CHANNEL_STATS      (PROPRIETARY_TLV_BASE_ID + 198)
#घोषणा TLV_BTCOEX_WL_AGGR_WINSIZE  (PROPRIETARY_TLV_BASE_ID + 202)
#घोषणा TLV_BTCOEX_WL_SCANTIME      (PROPRIETARY_TLV_BASE_ID + 203)
#घोषणा TLV_TYPE_BSS_MODE           (PROPRIETARY_TLV_BASE_ID + 206)
#घोषणा TLV_TYPE_RANDOM_MAC         (PROPRIETARY_TLV_BASE_ID + 236)
#घोषणा TLV_TYPE_CHAN_ATTR_CFG      (PROPRIETARY_TLV_BASE_ID + 237)
#घोषणा TLV_TYPE_MAX_CONN           (PROPRIETARY_TLV_BASE_ID + 279)

#घोषणा MWIFIEX_TX_DATA_BUF_SIZE_2K        2048

#घोषणा SSN_MASK         0xfff0

#घोषणा BA_RESULT_SUCCESS        0x0
#घोषणा BA_RESULT_TIMEOUT        0x2

#घोषणा IS_BASTREAM_SETUP(ptr)  (ptr->ba_status)

#घोषणा BA_STREAM_NOT_ALLOWED   0xff

#घोषणा IS_11N_ENABLED(priv) ((priv->adapter->config_bands & BAND_GN || \
			priv->adapter->config_bands & BAND_AN) && \
			priv->curr_bss_params.bss_descriptor.bcn_ht_cap && \
			!priv->curr_bss_params.bss_descriptor.disable_11n)
#घोषणा INITIATOR_BIT(DelBAParamSet) (((DelBAParamSet) &\
			BIT(DELBA_INITIATOR_POS)) >> DELBA_INITIATOR_POS)

#घोषणा MWIFIEX_TX_DATA_BUF_SIZE_4K        4096
#घोषणा MWIFIEX_TX_DATA_BUF_SIZE_8K        8192
#घोषणा MWIFIEX_TX_DATA_BUF_SIZE_12K       12288

#घोषणा ISSUPP_11NENABLED(FwCapInfo) (FwCapInfo & BIT(11))
#घोषणा ISSUPP_TDLS_ENABLED(FwCapInfo) (FwCapInfo & BIT(14))
#घोषणा ISSUPP_DRCS_ENABLED(FwCapInfo) (FwCapInfo & BIT(15))
#घोषणा ISSUPP_SDIO_SPA_ENABLED(FwCapInfo) (FwCapInfo & BIT(16))
#घोषणा ISSUPP_ADHOC_ENABLED(FwCapInfo) (FwCapInfo & BIT(25))
#घोषणा ISSUPP_RANDOM_MAC(FwCapInfo) (FwCapInfo & BIT(27))
#घोषणा ISSUPP_FIRMWARE_SUPPLICANT(FwCapInfo) (FwCapInfo & BIT(21))

#घोषणा MWIFIEX_DEF_HT_CAP	(IEEE80211_HT_CAP_DSSSCCK40 | \
				 (1 << IEEE80211_HT_CAP_RX_STBC_SHIFT) | \
				 IEEE80211_HT_CAP_SM_PS)

#घोषणा MWIFIEX_DEF_11N_TX_BF_CAP	0x09E1E008

#घोषणा MWIFIEX_DEF_AMPDU	IEEE80211_HT_AMPDU_PARM_FACTOR

/* dev_cap biपंचांगap
 * BIT
 * 0-16		reserved
 * 17		IEEE80211_HT_CAP_SUP_WIDTH_20_40
 * 18-22	reserved
 * 23		IEEE80211_HT_CAP_SGI_20
 * 24		IEEE80211_HT_CAP_SGI_40
 * 25		IEEE80211_HT_CAP_TX_STBC
 * 26		IEEE80211_HT_CAP_RX_STBC
 * 27-28	reserved
 * 29		IEEE80211_HT_CAP_GRN_FLD
 * 30-31	reserved
 */
#घोषणा ISSUPP_CHANWIDTH40(Dot11nDevCap) (Dot11nDevCap & BIT(17))
#घोषणा ISSUPP_SHORTGI20(Dot11nDevCap) (Dot11nDevCap & BIT(23))
#घोषणा ISSUPP_SHORTGI40(Dot11nDevCap) (Dot11nDevCap & BIT(24))
#घोषणा ISSUPP_TXSTBC(Dot11nDevCap) (Dot11nDevCap & BIT(25))
#घोषणा ISSUPP_RXSTBC(Dot11nDevCap) (Dot11nDevCap & BIT(26))
#घोषणा ISSUPP_GREENFIELD(Dot11nDevCap) (Dot11nDevCap & BIT(29))
#घोषणा ISENABLED_40MHZ_INTOLERANT(Dot11nDevCap) (Dot11nDevCap & BIT(8))
#घोषणा ISSUPP_RXLDPC(Dot11nDevCap) (Dot11nDevCap & BIT(22))
#घोषणा ISSUPP_BEAMFORMING(Dot11nDevCap) (Dot11nDevCap & BIT(30))
#घोषणा ISALLOWED_CHANWIDTH40(ht_param) (ht_param & BIT(2))
#घोषणा GETSUPP_TXBASTREAMS(Dot11nDevCap) ((Dot11nDevCap >> 18) & 0xF)

/* httxcfg biपंचांगap
 * 0		reserved
 * 1		20/40 Mhz enable(1)/disable(0)
 * 2-3		reserved
 * 4		green field enable(1)/disable(0)
 * 5		लघु GI in 20 Mhz enable(1)/disable(0)
 * 6		लघु GI in 40 Mhz enable(1)/disable(0)
 * 7-15		reserved
 */
#घोषणा MWIFIEX_FW_DEF_HTTXCFG (BIT(1) | BIT(4) | BIT(5) | BIT(6))

/* 11AC Tx and Rx MCS map क्रम 1x1 mode:
 * IEEE80211_VHT_MCS_SUPPORT_0_9 क्रम stream 1
 * IEEE80211_VHT_MCS_NOT_SUPPORTED क्रम reमुख्यing 7 streams
 */
#घोषणा MWIFIEX_11AC_MCS_MAP_1X1	0xfffefffe

/* 11AC Tx and Rx MCS map क्रम 2x2 mode:
 * IEEE80211_VHT_MCS_SUPPORT_0_9 क्रम stream 1 and 2
 * IEEE80211_VHT_MCS_NOT_SUPPORTED क्रम reमुख्यing 6 streams
 */
#घोषणा MWIFIEX_11AC_MCS_MAP_2X2	0xfffafffa

#घोषणा GET_RXMCSSUPP(DevMCSSupported) (DevMCSSupported & 0x0f)
#घोषणा SETHT_MCS32(x) (x[4] |= 1)
#घोषणा HT_STREAM_1X1	0x11
#घोषणा HT_STREAM_2X2	0x22

#घोषणा SET_SECONDARYCHAN(RadioType, SECCHAN) (RadioType |= (SECCHAN << 4))

#घोषणा LLC_SNAP_LEN    8

/* HW_SPEC fw_cap_info */

#घोषणा ISSUPP_11ACENABLED(fw_cap_info) (fw_cap_info & BIT(13))

#घोषणा GET_VHTCAP_CHWDSET(vht_cap_info)    ((vht_cap_info >> 2) & 0x3)
#घोषणा GET_VHTNSSMCS(mcs_mapset, nss) ((mcs_mapset >> (2 * (nss - 1))) & 0x3)
#घोषणा SET_VHTNSSMCS(mcs_mapset, nss, value) (mcs_mapset |= (value & 0x3) << \
					      (2 * (nss - 1)))
#घोषणा GET_DEVTXMCSMAP(dev_mcs_map)      (dev_mcs_map >> 16)
#घोषणा GET_DEVRXMCSMAP(dev_mcs_map)      (dev_mcs_map & 0xFFFF)

/* Clear SU Beanक्रमmer, MU beanक्रमmer, MU beanक्रमmee and
 * sounding dimensions bits
 */
#घोषणा MWIFIEX_DEF_11AC_CAP_BF_RESET_MASK \
			(IEEE80211_VHT_CAP_SU_BEAMFORMER_CAPABLE | \
			 IEEE80211_VHT_CAP_MU_BEAMFORMER_CAPABLE | \
			 IEEE80211_VHT_CAP_MU_BEAMFORMEE_CAPABLE | \
			 IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_MASK)

#घोषणा MOD_CLASS_HR_DSSS       0x03
#घोषणा MOD_CLASS_OFDM          0x07
#घोषणा MOD_CLASS_HT            0x08
#घोषणा HT_BW_20    0
#घोषणा HT_BW_40    1

#घोषणा DFS_CHAN_MOVE_TIME      10000

#घोषणा HostCmd_CMD_GET_HW_SPEC                       0x0003
#घोषणा HostCmd_CMD_802_11_SCAN                       0x0006
#घोषणा HostCmd_CMD_802_11_GET_LOG                    0x000b
#घोषणा HostCmd_CMD_MAC_MULTICAST_ADR                 0x0010
#घोषणा HostCmd_CMD_802_11_EEPROM_ACCESS              0x0059
#घोषणा HostCmd_CMD_802_11_ASSOCIATE                  0x0012
#घोषणा HostCmd_CMD_802_11_SNMP_MIB                   0x0016
#घोषणा HostCmd_CMD_MAC_REG_ACCESS                    0x0019
#घोषणा HostCmd_CMD_BBP_REG_ACCESS                    0x001a
#घोषणा HostCmd_CMD_RF_REG_ACCESS                     0x001b
#घोषणा HostCmd_CMD_PMIC_REG_ACCESS                   0x00ad
#घोषणा HostCmd_CMD_RF_TX_PWR                         0x001e
#घोषणा HostCmd_CMD_RF_ANTENNA                        0x0020
#घोषणा HostCmd_CMD_802_11_DEAUTHENTICATE             0x0024
#घोषणा HostCmd_CMD_MAC_CONTROL                       0x0028
#घोषणा HostCmd_CMD_802_11_AD_HOC_START               0x002b
#घोषणा HostCmd_CMD_802_11_AD_HOC_JOIN                0x002c
#घोषणा HostCmd_CMD_802_11_AD_HOC_STOP                0x0040
#घोषणा HostCmd_CMD_802_11_MAC_ADDRESS                0x004D
#घोषणा HostCmd_CMD_802_11D_DOMAIN_INFO               0x005b
#घोषणा HostCmd_CMD_802_11_KEY_MATERIAL               0x005e
#घोषणा HostCmd_CMD_802_11_BG_SCAN_CONFIG             0x006b
#घोषणा HostCmd_CMD_802_11_BG_SCAN_QUERY              0x006c
#घोषणा HostCmd_CMD_WMM_GET_STATUS                    0x0071
#घोषणा HostCmd_CMD_802_11_SUBSCRIBE_EVENT            0x0075
#घोषणा HostCmd_CMD_802_11_TX_RATE_QUERY              0x007f
#घोषणा HostCmd_CMD_802_11_IBSS_COALESCING_STATUS     0x0083
#घोषणा HostCmd_CMD_MEM_ACCESS                        0x0086
#घोषणा HostCmd_CMD_CFG_DATA                          0x008f
#घोषणा HostCmd_CMD_VERSION_EXT                       0x0097
#घोषणा HostCmd_CMD_MEF_CFG                           0x009a
#घोषणा HostCmd_CMD_RSSI_INFO                         0x00a4
#घोषणा HostCmd_CMD_FUNC_INIT                         0x00a9
#घोषणा HostCmd_CMD_FUNC_SHUTDOWN                     0x00aa
#घोषणा HOST_CMD_APCMD_SYS_RESET                      0x00af
#घोषणा HostCmd_CMD_UAP_SYS_CONFIG                    0x00b0
#घोषणा HostCmd_CMD_UAP_BSS_START                     0x00b1
#घोषणा HostCmd_CMD_UAP_BSS_STOP                      0x00b2
#घोषणा HOST_CMD_APCMD_STA_LIST                       0x00b3
#घोषणा HostCmd_CMD_UAP_STA_DEAUTH                    0x00b5
#घोषणा HostCmd_CMD_11N_CFG                           0x00cd
#घोषणा HostCmd_CMD_11N_ADDBA_REQ                     0x00ce
#घोषणा HostCmd_CMD_11N_ADDBA_RSP                     0x00cf
#घोषणा HostCmd_CMD_11N_DELBA                         0x00d0
#घोषणा HostCmd_CMD_RECONFIGURE_TX_BUFF               0x00d9
#घोषणा HostCmd_CMD_CHAN_REPORT_REQUEST               0x00dd
#घोषणा HostCmd_CMD_AMSDU_AGGR_CTRL                   0x00df
#घोषणा HostCmd_CMD_TXPWR_CFG                         0x00d1
#घोषणा HostCmd_CMD_TX_RATE_CFG                       0x00d6
#घोषणा HostCmd_CMD_ROBUST_COEX                       0x00e0
#घोषणा HostCmd_CMD_802_11_PS_MODE_ENH                0x00e4
#घोषणा HostCmd_CMD_802_11_HS_CFG_ENH                 0x00e5
#घोषणा HostCmd_CMD_P2P_MODE_CFG                      0x00eb
#घोषणा HostCmd_CMD_CAU_REG_ACCESS                    0x00ed
#घोषणा HostCmd_CMD_SET_BSS_MODE                      0x00f7
#घोषणा HostCmd_CMD_PCIE_DESC_DETAILS                 0x00fa
#घोषणा HostCmd_CMD_802_11_SCAN_EXT                   0x0107
#घोषणा HostCmd_CMD_COALESCE_CFG                      0x010a
#घोषणा HostCmd_CMD_MGMT_FRAME_REG                    0x010c
#घोषणा HostCmd_CMD_REMAIN_ON_CHAN                    0x010d
#घोषणा HostCmd_CMD_GTK_REKEY_OFFLOAD_CFG             0x010f
#घोषणा HostCmd_CMD_11AC_CFG			      0x0112
#घोषणा HostCmd_CMD_HS_WAKEUP_REASON                  0x0116
#घोषणा HostCmd_CMD_TDLS_CONFIG                       0x0100
#घोषणा HostCmd_CMD_MC_POLICY                         0x0121
#घोषणा HostCmd_CMD_TDLS_OPER                         0x0122
#घोषणा HostCmd_CMD_FW_DUMP_EVENT		      0x0125
#घोषणा HostCmd_CMD_SDIO_SP_RX_AGGR_CFG               0x0223
#घोषणा HostCmd_CMD_STA_CONFIGURE		      0x023f
#घोषणा HostCmd_CMD_CHAN_REGION_CFG		      0x0242
#घोषणा HostCmd_CMD_PACKET_AGGR_CTRL		      0x0251

#घोषणा PROTOCOL_NO_SECURITY        0x01
#घोषणा PROTOCOL_STATIC_WEP         0x02
#घोषणा PROTOCOL_WPA                0x08
#घोषणा PROTOCOL_WPA2               0x20
#घोषणा PROTOCOL_WPA2_MIXED         0x28
#घोषणा PROTOCOL_EAP                0x40
#घोषणा KEY_MGMT_NONE               0x04
#घोषणा KEY_MGMT_PSK                0x02
#घोषणा KEY_MGMT_EAP                0x01
#घोषणा CIPHER_TKIP                 0x04
#घोषणा CIPHER_AES_CCMP             0x08
#घोषणा VALID_CIPHER_BITMAP         0x0c

क्रमागत ENH_PS_MODES अणु
	EN_PS = 1,
	DIS_PS = 2,
	EN_AUTO_DS = 3,
	DIS_AUTO_DS = 4,
	SLEEP_CONFIRM = 5,
	GET_PS = 0,
	EN_AUTO_PS = 0xff,
	DIS_AUTO_PS = 0xfe,
पूर्ण;

क्रमागत P2P_MODES अणु
	P2P_MODE_DISABLE = 0,
	P2P_MODE_DEVICE = 1,
	P2P_MODE_GO = 2,
	P2P_MODE_CLIENT = 3,
पूर्ण;

क्रमागत mwअगरiex_channel_flags अणु
	MWIFIEX_CHANNEL_PASSIVE = BIT(0),
	MWIFIEX_CHANNEL_DFS = BIT(1),
	MWIFIEX_CHANNEL_NOHT40 = BIT(2),
	MWIFIEX_CHANNEL_NOHT80 = BIT(3),
	MWIFIEX_CHANNEL_DISABLED = BIT(7),
पूर्ण;

#घोषणा HostCmd_RET_BIT                       0x8000
#घोषणा HostCmd_ACT_GEN_GET                   0x0000
#घोषणा HostCmd_ACT_GEN_SET                   0x0001
#घोषणा HostCmd_ACT_GEN_REMOVE                0x0004
#घोषणा HostCmd_ACT_BITWISE_SET               0x0002
#घोषणा HostCmd_ACT_BITWISE_CLR               0x0003
#घोषणा HostCmd_RESULT_OK                     0x0000
#घोषणा HostCmd_ACT_MAC_RX_ON                 BIT(0)
#घोषणा HostCmd_ACT_MAC_TX_ON                 BIT(1)
#घोषणा HostCmd_ACT_MAC_WEP_ENABLE            BIT(3)
#घोषणा HostCmd_ACT_MAC_ETHERNETII_ENABLE     BIT(4)
#घोषणा HostCmd_ACT_MAC_PROMISCUOUS_ENABLE    BIT(7)
#घोषणा HostCmd_ACT_MAC_ALL_MULTICAST_ENABLE  BIT(8)
#घोषणा HostCmd_ACT_MAC_ADHOC_G_PROTECTION_ON BIT(13)
#घोषणा HostCmd_ACT_MAC_DYNAMIC_BW_ENABLE     BIT(16)

#घोषणा HostCmd_BSS_MODE_IBSS               0x0002
#घोषणा HostCmd_BSS_MODE_ANY                0x0003

#घोषणा HostCmd_SCAN_RADIO_TYPE_BG          0
#घोषणा HostCmd_SCAN_RADIO_TYPE_A           1

#घोषणा HS_CFG_CANCEL			0xffffffff
#घोषणा HS_CFG_COND_DEF			0x00000000
#घोषणा HS_CFG_GPIO_DEF			0xff
#घोषणा HS_CFG_GAP_DEF			0xff
#घोषणा HS_CFG_COND_BROADCAST_DATA	0x00000001
#घोषणा HS_CFG_COND_UNICAST_DATA	0x00000002
#घोषणा HS_CFG_COND_MAC_EVENT		0x00000004
#घोषणा HS_CFG_COND_MULTICAST_DATA	0x00000008

#घोषणा CONNECT_ERR_AUTH_ERR_STA_FAILURE	0xFFFB
#घोषणा CONNECT_ERR_ASSOC_ERR_TIMEOUT		0xFFFC
#घोषणा CONNECT_ERR_ASSOC_ERR_AUTH_REFUSED	0xFFFD
#घोषणा CONNECT_ERR_AUTH_MSG_UNHANDLED		0xFFFE
#घोषणा CONNECT_ERR_STA_FAILURE			0xFFFF


#घोषणा CMD_F_HOSTCMD           (1 << 0)

#घोषणा HostCmd_CMD_ID_MASK             0x0fff

#घोषणा HostCmd_SEQ_NUM_MASK            0x00ff

#घोषणा HostCmd_BSS_NUM_MASK            0x0f00

#घोषणा HostCmd_BSS_TYPE_MASK           0xf000

#घोषणा HostCmd_ACT_SET_RX              0x0001
#घोषणा HostCmd_ACT_SET_TX              0x0002
#घोषणा HostCmd_ACT_SET_BOTH            0x0003
#घोषणा HostCmd_ACT_GET_RX              0x0004
#घोषणा HostCmd_ACT_GET_TX              0x0008
#घोषणा HostCmd_ACT_GET_BOTH            0x000c

#घोषणा RF_ANTENNA_AUTO                 0xFFFF

#घोषणा HostCmd_SET_SEQ_NO_BSS_INFO(seq, num, type) \
	((((seq) & 0x00ff) |                        \
	 (((num) & 0x000f) << 8)) |                 \
	(((type) & 0x000f) << 12))

#घोषणा HostCmd_GET_SEQ_NO(seq)       \
	((seq) & HostCmd_SEQ_NUM_MASK)

#घोषणा HostCmd_GET_BSS_NO(seq)         \
	(((seq) & HostCmd_BSS_NUM_MASK) >> 8)

#घोषणा HostCmd_GET_BSS_TYPE(seq)       \
	(((seq) & HostCmd_BSS_TYPE_MASK) >> 12)

#घोषणा EVENT_DUMMY_HOST_WAKEUP_SIGNAL  0x00000001
#घोषणा EVENT_LINK_LOST                 0x00000003
#घोषणा EVENT_LINK_SENSED               0x00000004
#घोषणा EVENT_MIB_CHANGED               0x00000006
#घोषणा EVENT_INIT_DONE                 0x00000007
#घोषणा EVENT_DEAUTHENTICATED           0x00000008
#घोषणा EVENT_DISASSOCIATED             0x00000009
#घोषणा EVENT_PS_AWAKE                  0x0000000a
#घोषणा EVENT_PS_SLEEP                  0x0000000b
#घोषणा EVENT_MIC_ERR_MULTICAST         0x0000000d
#घोषणा EVENT_MIC_ERR_UNICAST           0x0000000e
#घोषणा EVENT_DEEP_SLEEP_AWAKE          0x00000010
#घोषणा EVENT_ADHOC_BCN_LOST            0x00000011

#घोषणा EVENT_WMM_STATUS_CHANGE         0x00000017
#घोषणा EVENT_BG_SCAN_REPORT            0x00000018
#घोषणा EVENT_RSSI_LOW                  0x00000019
#घोषणा EVENT_SNR_LOW                   0x0000001a
#घोषणा EVENT_MAX_FAIL                  0x0000001b
#घोषणा EVENT_RSSI_HIGH                 0x0000001c
#घोषणा EVENT_SNR_HIGH                  0x0000001d
#घोषणा EVENT_IBSS_COALESCED            0x0000001e
#घोषणा EVENT_IBSS_STA_CONNECT          0x00000020
#घोषणा EVENT_IBSS_STA_DISCONNECT       0x00000021
#घोषणा EVENT_DATA_RSSI_LOW             0x00000024
#घोषणा EVENT_DATA_SNR_LOW              0x00000025
#घोषणा EVENT_DATA_RSSI_HIGH            0x00000026
#घोषणा EVENT_DATA_SNR_HIGH             0x00000027
#घोषणा EVENT_LINK_QUALITY              0x00000028
#घोषणा EVENT_PORT_RELEASE              0x0000002b
#घोषणा EVENT_UAP_STA_DEAUTH            0x0000002c
#घोषणा EVENT_UAP_STA_ASSOC             0x0000002d
#घोषणा EVENT_UAP_BSS_START             0x0000002e
#घोषणा EVENT_PRE_BEACON_LOST           0x00000031
#घोषणा EVENT_ADDBA                     0x00000033
#घोषणा EVENT_DELBA                     0x00000034
#घोषणा EVENT_BA_STREAM_TIEMOUT         0x00000037
#घोषणा EVENT_AMSDU_AGGR_CTRL           0x00000042
#घोषणा EVENT_UAP_BSS_IDLE              0x00000043
#घोषणा EVENT_UAP_BSS_ACTIVE            0x00000044
#घोषणा EVENT_WEP_ICV_ERR               0x00000046
#घोषणा EVENT_HS_ACT_REQ                0x00000047
#घोषणा EVENT_BW_CHANGE                 0x00000048
#घोषणा EVENT_UAP_MIC_COUNTERMEASURES   0x0000004c
#घोषणा EVENT_HOSTWAKE_STAIE		0x0000004d
#घोषणा EVENT_CHANNEL_SWITCH_ANN        0x00000050
#घोषणा EVENT_TDLS_GENERIC_EVENT        0x00000052
#घोषणा EVENT_RADAR_DETECTED		0x00000053
#घोषणा EVENT_CHANNEL_REPORT_RDY        0x00000054
#घोषणा EVENT_TX_DATA_PAUSE             0x00000055
#घोषणा EVENT_EXT_SCAN_REPORT           0x00000058
#घोषणा EVENT_RXBA_SYNC                 0x00000059
#घोषणा EVENT_UNKNOWN_DEBUG             0x00000063
#घोषणा EVENT_BG_SCAN_STOPPED           0x00000065
#घोषणा EVENT_REMAIN_ON_CHAN_EXPIRED    0x0000005f
#घोषणा EVENT_MULTI_CHAN_INFO           0x0000006a
#घोषणा EVENT_FW_DUMP_INFO		0x00000073
#घोषणा EVENT_TX_STATUS_REPORT		0x00000074
#घोषणा EVENT_BT_COEX_WLAN_PARA_CHANGE	0X00000076

#घोषणा EVENT_ID_MASK                   0xffff
#घोषणा BSS_NUM_MASK                    0xf

#घोषणा EVENT_GET_BSS_NUM(event_cause)          \
	(((event_cause) >> 16) & BSS_NUM_MASK)

#घोषणा EVENT_GET_BSS_TYPE(event_cause)         \
	(((event_cause) >> 24) & 0x00ff)

#घोषणा MWIFIEX_MAX_PATTERN_LEN		40
#घोषणा MWIFIEX_MAX_OFFSET_LEN		100
#घोषणा MWIFIEX_MAX_ND_MATCH_SETS	10

#घोषणा STACK_NBYTES			100
#घोषणा TYPE_DNUM			1
#घोषणा TYPE_BYTESEQ			2
#घोषणा MAX_OPERAND			0x40
#घोषणा TYPE_EQ				(MAX_OPERAND+1)
#घोषणा TYPE_EQ_DNUM			(MAX_OPERAND+2)
#घोषणा TYPE_EQ_BIT			(MAX_OPERAND+3)
#घोषणा TYPE_AND			(MAX_OPERAND+4)
#घोषणा TYPE_OR				(MAX_OPERAND+5)
#घोषणा MEF_MODE_HOST_SLEEP			1
#घोषणा MEF_ACTION_ALLOW_AND_WAKEUP_HOST	3
#घोषणा MEF_ACTION_AUTO_ARP                    0x10
#घोषणा MWIFIEX_CRITERIA_BROADCAST	BIT(0)
#घोषणा MWIFIEX_CRITERIA_UNICAST	BIT(1)
#घोषणा MWIFIEX_CRITERIA_MULTICAST	BIT(3)
#घोषणा MWIFIEX_MAX_SUPPORTED_IPADDR              4

#घोषणा ACT_TDLS_DELETE            0x00
#घोषणा ACT_TDLS_CREATE            0x01
#घोषणा ACT_TDLS_CONFIG            0x02

#घोषणा TDLS_EVENT_LINK_TEAR_DOWN      3
#घोषणा TDLS_EVENT_CHAN_SWITCH_RESULT  7
#घोषणा TDLS_EVENT_START_CHAN_SWITCH   8
#घोषणा TDLS_EVENT_CHAN_SWITCH_STOPPED 9

#घोषणा TDLS_BASE_CHANNEL	       0
#घोषणा TDLS_OFF_CHANNEL	       1

#घोषणा ACT_TDLS_CS_ENABLE_CONFIG 0x00
#घोषणा ACT_TDLS_CS_INIT	  0x06
#घोषणा ACT_TDLS_CS_STOP	  0x07
#घोषणा ACT_TDLS_CS_PARAMS	  0x08

#घोषणा MWIFIEX_DEF_CS_UNIT_TIME	2
#घोषणा MWIFIEX_DEF_CS_THR_OTHERLINK	10
#घोषणा MWIFIEX_DEF_THR_सूचीECTLINK	0
#घोषणा MWIFIEX_DEF_CS_TIME		10
#घोषणा MWIFIEX_DEF_CS_TIMEOUT		16
#घोषणा MWIFIEX_DEF_CS_REG_CLASS	12
#घोषणा MWIFIEX_DEF_CS_PERIODICITY	1

#घोषणा MWIFIEX_FW_V15		   15

#घोषणा MWIFIEX_MASTER_RADAR_DET_MASK BIT(1)

काष्ठा mwअगरiex_ie_types_header अणु
	__le16 type;
	__le16 len;
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_data अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 data[1];
पूर्ण __packed;

#घोषणा MWIFIEX_TxPD_POWER_MGMT_शून्य_PACKET 0x01
#घोषणा MWIFIEX_TxPD_POWER_MGMT_LAST_PACKET 0x08
#घोषणा MWIFIEX_TXPD_FLAGS_TDLS_PACKET      0x10
#घोषणा MWIFIEX_RXPD_FLAGS_TDLS_PACKET      0x01
#घोषणा MWIFIEX_TXPD_FLAGS_REQ_TX_STATUS    0x20

क्रमागत HS_WAKEUP_REASON अणु
	NO_HSWAKEUP_REASON = 0,
	BCAST_DATA_MATCHED,
	MCAST_DATA_MATCHED,
	UCAST_DATA_MATCHED,
	MASKTABLE_EVENT_MATCHED,
	NON_MASKABLE_EVENT_MATCHED,
	NON_MASKABLE_CONDITION_MATCHED,
	MAGIC_PATTERN_MATCHED,
	CONTROL_FRAME_MATCHED,
	MANAGEMENT_FRAME_MATCHED,
	GTK_REKEY_FAILURE,
	RESERVED
पूर्ण;

काष्ठा txpd अणु
	u8 bss_type;
	u8 bss_num;
	__le16 tx_pkt_length;
	__le16 tx_pkt_offset;
	__le16 tx_pkt_type;
	__le32 tx_control;
	u8 priority;
	u8 flags;
	u8 pkt_delay_2ms;
	u8 reserved1[2];
	u8 tx_token_id;
	u8 reserved[2];
पूर्ण __packed;

काष्ठा rxpd अणु
	u8 bss_type;
	u8 bss_num;
	__le16 rx_pkt_length;
	__le16 rx_pkt_offset;
	__le16 rx_pkt_type;
	__le16 seq_num;
	u8 priority;
	u8 rx_rate;
	s8 snr;
	s8 nf;

	/* For: Non-802.11 AC cards
	 *
	 * Ht Info [Bit 0] RxRate क्रमmat: LG=0, HT=1
	 * [Bit 1]  HT Bandwidth: BW20 = 0, BW40 = 1
	 * [Bit 2]  HT Guard Interval: LGI = 0, SGI = 1
	 *
	 * For: 802.11 AC cards
	 * [Bit 1] [Bit 0] RxRate क्रमmat: legacy rate = 00 HT = 01 VHT = 10
	 * [Bit 3] [Bit 2] HT/VHT Bandwidth BW20 = 00 BW40 = 01
	 *						BW80 = 10  BW160 = 11
	 * [Bit 4] HT/VHT Guard पूर्णांकerval LGI = 0 SGI = 1
	 * [Bit 5] STBC support Enabled = 1
	 * [Bit 6] LDPC support Enabled = 1
	 * [Bit 7] Reserved
	 */
	u8 ht_info;
	u8 reserved[3];
	u8 flags;
पूर्ण __packed;

काष्ठा uap_txpd अणु
	u8 bss_type;
	u8 bss_num;
	__le16 tx_pkt_length;
	__le16 tx_pkt_offset;
	__le16 tx_pkt_type;
	__le32 tx_control;
	u8 priority;
	u8 flags;
	u8 pkt_delay_2ms;
	u8 reserved1[2];
	u8 tx_token_id;
	u8 reserved[2];
पूर्ण __packed;

काष्ठा uap_rxpd अणु
	u8 bss_type;
	u8 bss_num;
	__le16 rx_pkt_length;
	__le16 rx_pkt_offset;
	__le16 rx_pkt_type;
	__le16 seq_num;
	u8 priority;
	u8 rx_rate;
	s8 snr;
	s8 nf;
	u8 ht_info;
	u8 reserved[3];
	u8 flags;
पूर्ण __packed;

काष्ठा mwअगरiex_fw_chan_stats अणु
	u8 chan_num;
	u8 bandcfg;
	u8 flags;
	s8 noise;
	__le16 total_bss;
	__le16 cca_scan_dur;
	__le16 cca_busy_dur;
पूर्ण __packed;

क्रमागत mwअगरiex_chan_scan_mode_biपंचांगasks अणु
	MWIFIEX_PASSIVE_SCAN = BIT(0),
	MWIFIEX_DISABLE_CHAN_FILT = BIT(1),
	MWIFIEX_HIDDEN_SSID_REPORT = BIT(4),
पूर्ण;

काष्ठा mwअगरiex_chan_scan_param_set अणु
	u8 radio_type;
	u8 chan_number;
	u8 chan_scan_mode_biपंचांगap;
	__le16 min_scan_समय;
	__le16 max_scan_समय;
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_chan_list_param_set अणु
	काष्ठा mwअगरiex_ie_types_header header;
	काष्ठा mwअगरiex_chan_scan_param_set chan_scan_param[1];
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_rxba_sync अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 mac[ETH_ALEN];
	u8 tid;
	u8 reserved;
	__le16 seq_num;
	__le16 biपंचांगap_len;
	u8 biपंचांगap[1];
पूर्ण __packed;

काष्ठा chan_band_param_set अणु
	u8 radio_type;
	u8 chan_number;
पूर्ण;

काष्ठा mwअगरiex_ie_types_chan_band_list_param_set अणु
	काष्ठा mwअगरiex_ie_types_header header;
	काष्ठा chan_band_param_set chan_band_param[1];
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_rates_param_set अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 rates[1];
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_ssid_param_set अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 ssid[1];
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_num_probes अणु
	काष्ठा mwअगरiex_ie_types_header header;
	__le16 num_probes;
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_repeat_count अणु
	काष्ठा mwअगरiex_ie_types_header header;
	__le16 repeat_count;
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_min_rssi_threshold अणु
	काष्ठा mwअगरiex_ie_types_header header;
	__le16 rssi_threshold;
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_bgscan_start_later अणु
	काष्ठा mwअगरiex_ie_types_header header;
	__le16 start_later;
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_scan_chan_gap अणु
	काष्ठा mwअगरiex_ie_types_header header;
	/* समय gap in TUs to be used between two consecutive channels scan */
	__le16 chan_gap;
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_अक्रमom_mac अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 mac[ETH_ALEN];
पूर्ण __packed;

काष्ठा mwअगरiex_ietypes_chanstats अणु
	काष्ठा mwअगरiex_ie_types_header header;
	काष्ठा mwअगरiex_fw_chan_stats chanstats[];
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_wildcard_ssid_params अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 max_ssid_length;
	u8 ssid[1];
पूर्ण __packed;

#घोषणा TSF_DATA_SIZE            8
काष्ठा mwअगरiex_ie_types_tsf_बारtamp अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 tsf_data[1];
पूर्ण __packed;

काष्ठा mwअगरiex_cf_param_set अणु
	u8 cfp_cnt;
	u8 cfp_period;
	__le16 cfp_max_duration;
	__le16 cfp_duration_reमुख्यing;
पूर्ण __packed;

काष्ठा mwअगरiex_ibss_param_set अणु
	__le16 atim_winकरोw;
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_ss_param_set अणु
	काष्ठा mwअगरiex_ie_types_header header;
	जोड़ अणु
		काष्ठा mwअगरiex_cf_param_set cf_param_set[1];
		काष्ठा mwअगरiex_ibss_param_set ibss_param_set[1];
	पूर्ण cf_ibss;
पूर्ण __packed;

काष्ठा mwअगरiex_fh_param_set अणु
	__le16 dwell_समय;
	u8 hop_set;
	u8 hop_pattern;
	u8 hop_index;
पूर्ण __packed;

काष्ठा mwअगरiex_ds_param_set अणु
	u8 current_chan;
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_phy_param_set अणु
	काष्ठा mwअगरiex_ie_types_header header;
	जोड़ अणु
		काष्ठा mwअगरiex_fh_param_set fh_param_set[1];
		काष्ठा mwअगरiex_ds_param_set ds_param_set[1];
	पूर्ण fh_ds;
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_auth_type अणु
	काष्ठा mwअगरiex_ie_types_header header;
	__le16 auth_type;
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_venकरोr_param_set अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 ie[MWIFIEX_MAX_VSIE_LEN];
पूर्ण;

#घोषणा MWIFIEX_TDLS_IDLE_TIMEOUT_IN_SEC	60

काष्ठा mwअगरiex_ie_types_tdls_idle_समयout अणु
	काष्ठा mwअगरiex_ie_types_header header;
	__le16 value;
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_rsn_param_set अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 rsn_ie[1];
पूर्ण __packed;

#घोषणा KEYPARAMSET_FIXED_LEN 6

काष्ठा mwअगरiex_ie_type_key_param_set अणु
	__le16 type;
	__le16 length;
	__le16 key_type_id;
	__le16 key_info;
	__le16 key_len;
	u8 key[50];
पूर्ण __packed;

#घोषणा IGTK_PN_LEN		8

काष्ठा mwअगरiex_cmac_param अणु
	u8 ipn[IGTK_PN_LEN];
	u8 key[WLAN_KEY_LEN_AES_CMAC];
पूर्ण __packed;

काष्ठा mwअगरiex_wep_param अणु
	__le16 key_len;
	u8 key[WLAN_KEY_LEN_WEP104];
पूर्ण __packed;

काष्ठा mwअगरiex_tkip_param अणु
	u8 pn[WPA_PN_SIZE];
	__le16 key_len;
	u8 key[WLAN_KEY_LEN_TKIP];
पूर्ण __packed;

काष्ठा mwअगरiex_aes_param अणु
	u8 pn[WPA_PN_SIZE];
	__le16 key_len;
	u8 key[WLAN_KEY_LEN_CCMP_256];
पूर्ण __packed;

काष्ठा mwअगरiex_wapi_param अणु
	u8 pn[PN_LEN];
	__le16 key_len;
	u8 key[WLAN_KEY_LEN_SMS4];
पूर्ण __packed;

काष्ठा mwअगरiex_cmac_aes_param अणु
	u8 ipn[IGTK_PN_LEN];
	__le16 key_len;
	u8 key[WLAN_KEY_LEN_AES_CMAC];
पूर्ण __packed;

काष्ठा mwअगरiex_ie_type_key_param_set_v2 अणु
	__le16 type;
	__le16 len;
	u8 mac_addr[ETH_ALEN];
	u8 key_idx;
	u8 key_type;
	__le16 key_info;
	जोड़ अणु
		काष्ठा mwअगरiex_wep_param wep;
		काष्ठा mwअगरiex_tkip_param tkip;
		काष्ठा mwअगरiex_aes_param aes;
		काष्ठा mwअगरiex_wapi_param wapi;
		काष्ठा mwअगरiex_cmac_aes_param cmac_aes;
	पूर्ण key_params;
पूर्ण __packed;

काष्ठा host_cmd_ds_802_11_key_material_v2 अणु
	__le16 action;
	काष्ठा mwअगरiex_ie_type_key_param_set_v2 key_param_set;
पूर्ण __packed;

काष्ठा host_cmd_ds_802_11_key_material अणु
	__le16 action;
	काष्ठा mwअगरiex_ie_type_key_param_set key_param_set;
पूर्ण __packed;

काष्ठा host_cmd_ds_gen अणु
	__le16 command;
	__le16 size;
	__le16 seq_num;
	__le16 result;
पूर्ण;

#घोषणा S_DS_GEN        माप(काष्ठा host_cmd_ds_gen)

क्रमागत sleep_resp_ctrl अणु
	RESP_NOT_NEEDED = 0,
	RESP_NEEDED,
पूर्ण;

काष्ठा mwअगरiex_ps_param अणु
	__le16 null_pkt_पूर्णांकerval;
	__le16 multiple_dtims;
	__le16 bcn_miss_समयout;
	__le16 local_listen_पूर्णांकerval;
	__le16 adhoc_wake_period;
	__le16 mode;
	__le16 delay_to_ps;
पूर्ण __packed;

#घोषणा HS_DEF_WAKE_INTERVAL          100
#घोषणा HS_DEF_INACTIVITY_TIMEOUT      50

काष्ठा mwअगरiex_ps_param_in_hs अणु
	काष्ठा mwअगरiex_ie_types_header header;
	__le32 hs_wake_पूर्णांक;
	__le32 hs_inact_समयout;
पूर्ण __packed;

#घोषणा BITMAP_AUTO_DS         0x01
#घोषणा BITMAP_STA_PS          0x10

काष्ठा mwअगरiex_ie_types_स्वतः_ds_param अणु
	काष्ठा mwअगरiex_ie_types_header header;
	__le16 deep_sleep_समयout;
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_ps_param अणु
	काष्ठा mwअगरiex_ie_types_header header;
	काष्ठा mwअगरiex_ps_param param;
पूर्ण __packed;

काष्ठा host_cmd_ds_802_11_ps_mode_enh अणु
	__le16 action;

	जोड़ अणु
		काष्ठा mwअगरiex_ps_param opt_ps;
		__le16 ps_biपंचांगap;
	पूर्ण params;
पूर्ण __packed;

क्रमागत API_VER_ID अणु
	KEY_API_VER_ID = 1,
	FW_API_VER_ID = 2,
	UAP_FW_API_VER_ID = 3,
	CHANRPT_API_VER_ID = 4,
पूर्ण;

काष्ठा hw_spec_api_rev अणु
	काष्ठा mwअगरiex_ie_types_header header;
	__le16 api_id;
	u8 major_ver;
	u8 minor_ver;
पूर्ण __packed;

काष्ठा host_cmd_ds_get_hw_spec अणु
	__le16 hw_अगर_version;
	__le16 version;
	__le16 reserved;
	__le16 num_of_mcast_adr;
	u8 permanent_addr[ETH_ALEN];
	__le16 region_code;
	__le16 number_of_antenna;
	__le32 fw_release_number;
	__le32 reserved_1;
	__le32 reserved_2;
	__le32 reserved_3;
	__le32 fw_cap_info;
	__le32 करोt_11n_dev_cap;
	u8 dev_mcs_support;
	__le16 mp_end_port;	/* SDIO only, reserved क्रम other पूर्णांकerfacces */
	__le16 mgmt_buf_count;	/* mgmt IE buffer count */
	__le32 reserved_5;
	__le32 reserved_6;
	__le32 करोt_11ac_dev_cap;
	__le32 करोt_11ac_mcs_support;
	u8 tlvs[];
पूर्ण __packed;

काष्ठा host_cmd_ds_802_11_rssi_info अणु
	__le16 action;
	__le16 ndata;
	__le16 nbcn;
	__le16 reserved[9];
	दीर्घ दीर्घ reserved_1;
पूर्ण __packed;

काष्ठा host_cmd_ds_802_11_rssi_info_rsp अणु
	__le16 action;
	__le16 ndata;
	__le16 nbcn;
	__le16 data_rssi_last;
	__le16 data_nf_last;
	__le16 data_rssi_avg;
	__le16 data_nf_avg;
	__le16 bcn_rssi_last;
	__le16 bcn_nf_last;
	__le16 bcn_rssi_avg;
	__le16 bcn_nf_avg;
	दीर्घ दीर्घ tsf_bcn;
पूर्ण __packed;

काष्ठा host_cmd_ds_802_11_mac_address अणु
	__le16 action;
	u8 mac_addr[ETH_ALEN];
पूर्ण __packed;

काष्ठा host_cmd_ds_mac_control अणु
	__le32 action;
पूर्ण;

काष्ठा host_cmd_ds_mac_multicast_adr अणु
	__le16 action;
	__le16 num_of_adrs;
	u8 mac_list[MWIFIEX_MAX_MULTICAST_LIST_SIZE][ETH_ALEN];
पूर्ण __packed;

काष्ठा host_cmd_ds_802_11_deauthenticate अणु
	u8 mac_addr[ETH_ALEN];
	__le16 reason_code;
पूर्ण __packed;

काष्ठा host_cmd_ds_802_11_associate अणु
	u8 peer_sta_addr[ETH_ALEN];
	__le16 cap_info_biपंचांगap;
	__le16 listen_पूर्णांकerval;
	__le16 beacon_period;
	u8 dtim_period;
पूर्ण __packed;

काष्ठा ieee_types_assoc_rsp अणु
	__le16 cap_info_biपंचांगap;
	__le16 status_code;
	__le16 a_id;
	u8 ie_buffer[];
पूर्ण __packed;

काष्ठा host_cmd_ds_802_11_associate_rsp अणु
	काष्ठा ieee_types_assoc_rsp assoc_rsp;
पूर्ण __packed;

काष्ठा ieee_types_cf_param_set अणु
	u8 element_id;
	u8 len;
	u8 cfp_cnt;
	u8 cfp_period;
	__le16 cfp_max_duration;
	__le16 cfp_duration_reमुख्यing;
पूर्ण __packed;

काष्ठा ieee_types_ibss_param_set अणु
	u8 element_id;
	u8 len;
	__le16 atim_winकरोw;
पूर्ण __packed;

जोड़ ieee_types_ss_param_set अणु
	काष्ठा ieee_types_cf_param_set cf_param_set;
	काष्ठा ieee_types_ibss_param_set ibss_param_set;
पूर्ण __packed;

काष्ठा ieee_types_fh_param_set अणु
	u8 element_id;
	u8 len;
	__le16 dwell_समय;
	u8 hop_set;
	u8 hop_pattern;
	u8 hop_index;
पूर्ण __packed;

काष्ठा ieee_types_ds_param_set अणु
	u8 element_id;
	u8 len;
	u8 current_chan;
पूर्ण __packed;

जोड़ ieee_types_phy_param_set अणु
	काष्ठा ieee_types_fh_param_set fh_param_set;
	काष्ठा ieee_types_ds_param_set ds_param_set;
पूर्ण __packed;

काष्ठा ieee_types_oper_mode_ntf अणु
	u8 element_id;
	u8 len;
	u8 oper_mode;
पूर्ण __packed;

काष्ठा host_cmd_ds_802_11_ad_hoc_start अणु
	u8 ssid[IEEE80211_MAX_SSID_LEN];
	u8 bss_mode;
	__le16 beacon_period;
	u8 dtim_period;
	जोड़ ieee_types_ss_param_set ss_param_set;
	जोड़ ieee_types_phy_param_set phy_param_set;
	u16 reserved1;
	__le16 cap_info_biपंचांगap;
	u8 data_rate[HOSTCMD_SUPPORTED_RATES];
पूर्ण __packed;

काष्ठा host_cmd_ds_802_11_ad_hoc_start_result अणु
	u8 pad[3];
	u8 bssid[ETH_ALEN];
	u8 pad2[2];
	u8 result;
पूर्ण __packed;

काष्ठा host_cmd_ds_802_11_ad_hoc_join_result अणु
	u8 result;
पूर्ण __packed;

काष्ठा adhoc_bss_desc अणु
	u8 bssid[ETH_ALEN];
	u8 ssid[IEEE80211_MAX_SSID_LEN];
	u8 bss_mode;
	__le16 beacon_period;
	u8 dtim_period;
	u8 समय_stamp[8];
	u8 local_समय[8];
	जोड़ ieee_types_phy_param_set phy_param_set;
	जोड़ ieee_types_ss_param_set ss_param_set;
	__le16 cap_info_biपंचांगap;
	u8 data_rates[HOSTCMD_SUPPORTED_RATES];

	/*
	 *  DO NOT ADD ANY FIELDS TO THIS STRUCTURE.
	 *  It is used in the Adhoc join command and will cause a
	 *  binary layout mismatch with the firmware
	 */
पूर्ण __packed;

काष्ठा host_cmd_ds_802_11_ad_hoc_join अणु
	काष्ठा adhoc_bss_desc bss_descriptor;
	u16 reserved1;
	u16 reserved2;
पूर्ण __packed;

काष्ठा host_cmd_ds_802_11_get_log अणु
	__le32 mcast_tx_frame;
	__le32 failed;
	__le32 retry;
	__le32 multi_retry;
	__le32 frame_dup;
	__le32 rts_success;
	__le32 rts_failure;
	__le32 ack_failure;
	__le32 rx_frag;
	__le32 mcast_rx_frame;
	__le32 fcs_error;
	__le32 tx_frame;
	__le32 reserved;
	__le32 wep_icv_err_cnt[4];
	__le32 bcn_rcv_cnt;
	__le32 bcn_miss_cnt;
पूर्ण __packed;

/* Enumeration क्रम rate क्रमmat */
क्रमागत _mwअगरiex_rate_क्रमmat अणु
	MWIFIEX_RATE_FORMAT_LG = 0,
	MWIFIEX_RATE_FORMAT_HT,
	MWIFIEX_RATE_FORMAT_VHT,
	MWIFIEX_RATE_FORMAT_AUTO = 0xFF,
पूर्ण;

काष्ठा host_cmd_ds_tx_rate_query अणु
	u8 tx_rate;
	/* Tx Rate Info: For 802.11 AC cards
	 *
	 * [Bit 0-1] tx rate क्रमmate: LG = 0, HT = 1, VHT = 2
	 * [Bit 2-3] HT/VHT Bandwidth: BW20 = 0, BW40 = 1, BW80 = 2, BW160 = 3
	 * [Bit 4]   HT/VHT Guard Interval: LGI = 0, SGI = 1
	 *
	 * For non-802.11 AC cards
	 * Ht Info [Bit 0] RxRate क्रमmat: LG=0, HT=1
	 * [Bit 1]  HT Bandwidth: BW20 = 0, BW40 = 1
	 * [Bit 2]  HT Guard Interval: LGI = 0, SGI = 1
	 */
	u8 ht_info;
पूर्ण __packed;

काष्ठा mwअगरiex_tx_छोड़ो_tlv अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 peermac[ETH_ALEN];
	u8 tx_छोड़ो;
	u8 pkt_cnt;
पूर्ण __packed;

क्रमागत Host_Sleep_Action अणु
	HS_CONFIGURE = 0x0001,
	HS_ACTIVATE  = 0x0002,
पूर्ण;

काष्ठा mwअगरiex_hs_config_param अणु
	__le32 conditions;
	u8 gpio;
	u8 gap;
पूर्ण __packed;

काष्ठा hs_activate_param अणु
	__le16 resp_ctrl;
पूर्ण __packed;

काष्ठा host_cmd_ds_802_11_hs_cfg_enh अणु
	__le16 action;

	जोड़ अणु
		काष्ठा mwअगरiex_hs_config_param hs_config;
		काष्ठा hs_activate_param hs_activate;
	पूर्ण params;
पूर्ण __packed;

क्रमागत SNMP_MIB_INDEX अणु
	OP_RATE_SET_I = 1,
	DTIM_PERIOD_I = 3,
	RTS_THRESH_I = 5,
	SHORT_RETRY_LIM_I = 6,
	LONG_RETRY_LIM_I = 7,
	FRAG_THRESH_I = 8,
	DOT11D_I = 9,
	DOT11H_I = 10,
पूर्ण;

क्रमागत mwअगरiex_assocmd_failurepoपूर्णांक अणु
	MWIFIEX_ASSOC_CMD_SUCCESS = 0,
	MWIFIEX_ASSOC_CMD_FAILURE_ASSOC,
	MWIFIEX_ASSOC_CMD_FAILURE_AUTH,
	MWIFIEX_ASSOC_CMD_FAILURE_JOIN
पूर्ण;

#घोषणा MAX_SNMP_BUF_SIZE   128

काष्ठा host_cmd_ds_802_11_snmp_mib अणु
	__le16 query_type;
	__le16 oid;
	__le16 buf_size;
	u8 value[1];
पूर्ण __packed;

काष्ठा mwअगरiex_rate_scope अणु
	__le16 type;
	__le16 length;
	__le16 hr_dsss_rate_biपंचांगap;
	__le16 ofdm_rate_biपंचांगap;
	__le16 ht_mcs_rate_biपंचांगap[8];
	__le16 vht_mcs_rate_biपंचांगap[8];
पूर्ण __packed;

काष्ठा mwअगरiex_rate_drop_pattern अणु
	__le16 type;
	__le16 length;
	__le32 rate_drop_mode;
पूर्ण __packed;

काष्ठा host_cmd_ds_tx_rate_cfg अणु
	__le16 action;
	__le16 cfg_index;
पूर्ण __packed;

काष्ठा mwअगरiex_घातer_group अणु
	u8 modulation_class;
	u8 first_rate_code;
	u8 last_rate_code;
	s8 घातer_step;
	s8 घातer_min;
	s8 घातer_max;
	u8 ht_bandwidth;
	u8 reserved;
पूर्ण __packed;

काष्ठा mwअगरiex_types_घातer_group अणु
	__le16 type;
	__le16 length;
पूर्ण __packed;

काष्ठा host_cmd_ds_txpwr_cfg अणु
	__le16 action;
	__le16 cfg_index;
	__le32 mode;
पूर्ण __packed;

काष्ठा host_cmd_ds_rf_tx_pwr अणु
	__le16 action;
	__le16 cur_level;
	u8 max_घातer;
	u8 min_घातer;
पूर्ण __packed;

काष्ठा host_cmd_ds_rf_ant_mimo अणु
	__le16 action_tx;
	__le16 tx_ant_mode;
	__le16 action_rx;
	__le16 rx_ant_mode;
पूर्ण __packed;

काष्ठा host_cmd_ds_rf_ant_siso अणु
	__le16 action;
	__le16 ant_mode;
पूर्ण __packed;

काष्ठा host_cmd_ds_tdls_oper अणु
	__le16 tdls_action;
	__le16 reason;
	u8 peer_mac[ETH_ALEN];
पूर्ण __packed;

काष्ठा mwअगरiex_tdls_config अणु
	__le16 enable;
पूर्ण __packed;

काष्ठा mwअगरiex_tdls_config_cs_params अणु
	u8 unit_समय;
	u8 thr_otherlink;
	u8 thr_directlink;
पूर्ण __packed;

काष्ठा mwअगरiex_tdls_init_cs_params अणु
	u8 peer_mac[ETH_ALEN];
	u8 primary_chan;
	u8 second_chan_offset;
	u8 band;
	__le16 चयन_समय;
	__le16 चयन_समयout;
	u8 reg_class;
	u8 periodicity;
पूर्ण __packed;

काष्ठा mwअगरiex_tdls_stop_cs_params अणु
	u8 peer_mac[ETH_ALEN];
पूर्ण __packed;

काष्ठा host_cmd_ds_tdls_config अणु
	__le16 tdls_action;
	u8 tdls_data[1];
पूर्ण __packed;

काष्ठा mwअगरiex_chan_desc अणु
	__le16 start_freq;
	u8 chan_width;
	u8 chan_num;
पूर्ण __packed;

काष्ठा host_cmd_ds_chan_rpt_req अणु
	काष्ठा mwअगरiex_chan_desc chan_desc;
	__le32 msec_dwell_समय;
पूर्ण __packed;

काष्ठा host_cmd_ds_chan_rpt_event अणु
	__le32 result;
	__le64 start_tsf;
	__le32 duration;
	u8 tlvbuf[];
पूर्ण __packed;

काष्ठा host_cmd_sdio_sp_rx_aggr_cfg अणु
	u8 action;
	u8 enable;
	__le16 block_size;
पूर्ण __packed;

काष्ठा mwअगरiex_fixed_bcn_param अणु
	__le64 बारtamp;
	__le16 beacon_period;
	__le16 cap_info_biपंचांगap;
पूर्ण __packed;

काष्ठा mwअगरiex_event_scan_result अणु
	__le16 event_id;
	u8 bss_index;
	u8 bss_type;
	u8 more_event;
	u8 reserved[3];
	__le16 buf_size;
	u8 num_of_set;
पूर्ण __packed;

काष्ठा tx_status_event अणु
	u8 packet_type;
	u8 tx_token_id;
	u8 status;
पूर्ण __packed;

#घोषणा MWIFIEX_USER_SCAN_CHAN_MAX             50

#घोषणा MWIFIEX_MAX_SSID_LIST_LENGTH         10

काष्ठा mwअगरiex_scan_cmd_config अणु
	/*
	 *  BSS mode to be sent in the firmware command
	 */
	u8 bss_mode;

	/* Specअगरic BSSID used to filter scan results in the firmware */
	u8 specअगरic_bssid[ETH_ALEN];

	/* Length of TLVs sent in command starting at tlvBuffer */
	u32 tlv_buf_len;

	/*
	 *  SSID TLV(s) and ChanList TLVs to be sent in the firmware command
	 *
	 *  TLV_TYPE_CHANLIST, mwअगरiex_ie_types_chan_list_param_set
	 *  WLAN_EID_SSID, mwअगरiex_ie_types_ssid_param_set
	 */
	u8 tlv_buf[1];	/* SSID TLV(s) and ChanList TLVs are stored
				   here */
पूर्ण __packed;

काष्ठा mwअगरiex_user_scan_chan अणु
	u8 chan_number;
	u8 radio_type;
	u8 scan_type;
	u8 reserved;
	u32 scan_समय;
पूर्ण __packed;

काष्ठा mwअगरiex_user_scan_cfg अणु
	/*
	 *  BSS mode to be sent in the firmware command
	 */
	u8 bss_mode;
	/* Configure the number of probe requests क्रम active chan scans */
	u8 num_probes;
	u8 reserved;
	/* BSSID filter sent in the firmware command to limit the results */
	u8 specअगरic_bssid[ETH_ALEN];
	/* SSID filter list used in the firmware to limit the scan results */
	काष्ठा cfg80211_ssid *ssid_list;
	u8 num_ssids;
	/* Variable number (fixed maximum) of channels to scan up */
	काष्ठा mwअगरiex_user_scan_chan chan_list[MWIFIEX_USER_SCAN_CHAN_MAX];
	u16 scan_chan_gap;
	u8 अक्रमom_mac[ETH_ALEN];
पूर्ण __packed;

#घोषणा MWIFIEX_BG_SCAN_CHAN_MAX 38
#घोषणा MWIFIEX_BSS_MODE_INFRA 1
#घोषणा MWIFIEX_BGSCAN_ACT_GET     0x0000
#घोषणा MWIFIEX_BGSCAN_ACT_SET     0x0001
#घोषणा MWIFIEX_BGSCAN_ACT_SET_ALL 0xff01
/** ssid match */
#घोषणा MWIFIEX_BGSCAN_SSID_MATCH          0x0001
/** ssid match and RSSI exceeded */
#घोषणा MWIFIEX_BGSCAN_SSID_RSSI_MATCH     0x0004
/**रुको क्रम all channel scan to complete to report scan result*/
#घोषणा MWIFIEX_BGSCAN_WAIT_ALL_CHAN_DONE  0x80000000

काष्ठा mwअगरiex_bg_scan_cfg अणु
	u16 action;
	u8 enable;
	u8 bss_type;
	u8 chan_per_scan;
	u32 scan_पूर्णांकerval;
	u32 report_condition;
	u8 num_probes;
	u8 rssi_threshold;
	u8 snr_threshold;
	u16 repeat_count;
	u16 start_later;
	काष्ठा cfg80211_match_set *ssid_list;
	u8 num_ssids;
	काष्ठा mwअगरiex_user_scan_chan chan_list[MWIFIEX_BG_SCAN_CHAN_MAX];
	u16 scan_chan_gap;
पूर्ण __packed;

काष्ठा ie_body अणु
	u8 grp_key_oui[4];
	u8 ptk_cnt[2];
	u8 ptk_body[4];
पूर्ण __packed;

काष्ठा host_cmd_ds_802_11_scan अणु
	u8 bss_mode;
	u8 bssid[ETH_ALEN];
	u8 tlv_buffer[1];
पूर्ण __packed;

काष्ठा host_cmd_ds_802_11_scan_rsp अणु
	__le16 bss_descript_size;
	u8 number_of_sets;
	u8 bss_desc_and_tlv_buffer[1];
पूर्ण __packed;

काष्ठा host_cmd_ds_802_11_scan_ext अणु
	u32   reserved;
	u8    tlv_buffer[1];
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_bss_mode अणु
	काष्ठा mwअगरiex_ie_types_header  header;
	u8 bss_mode;
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_bss_scan_rsp अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 bssid[ETH_ALEN];
	u8 frame_body[1];
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_bss_scan_info अणु
	काष्ठा mwअगरiex_ie_types_header header;
	__le16 rssi;
	__le16 anpi;
	u8 cca_busy_fraction;
	u8 radio_type;
	u8 channel;
	u8 reserved;
	__le64 tsf;
पूर्ण __packed;

काष्ठा host_cmd_ds_802_11_bg_scan_config अणु
	__le16 action;
	u8 enable;
	u8 bss_type;
	u8 chan_per_scan;
	u8 reserved;
	__le16 reserved1;
	__le32 scan_पूर्णांकerval;
	__le32 reserved2;
	__le32 report_condition;
	__le16 reserved3;
	u8 tlv[];
पूर्ण __packed;

काष्ठा host_cmd_ds_802_11_bg_scan_query अणु
	u8 flush;
पूर्ण __packed;

काष्ठा host_cmd_ds_802_11_bg_scan_query_rsp अणु
	__le32 report_condition;
	काष्ठा host_cmd_ds_802_11_scan_rsp scan_resp;
पूर्ण __packed;

काष्ठा mwअगरiex_ietypes_करोमुख्य_param_set अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 country_code[IEEE80211_COUNTRY_STRING_LEN];
	काष्ठा ieee80211_country_ie_triplet triplet[1];
पूर्ण __packed;

काष्ठा host_cmd_ds_802_11d_करोमुख्य_info अणु
	__le16 action;
	काष्ठा mwअगरiex_ietypes_करोमुख्य_param_set करोमुख्य;
पूर्ण __packed;

काष्ठा host_cmd_ds_802_11d_करोमुख्य_info_rsp अणु
	__le16 action;
	काष्ठा mwअगरiex_ietypes_करोमुख्य_param_set करोमुख्य;
पूर्ण __packed;

काष्ठा host_cmd_ds_11n_addba_req अणु
	u8 add_req_result;
	u8 peer_mac_addr[ETH_ALEN];
	u8 dialog_token;
	__le16 block_ack_param_set;
	__le16 block_ack_पंचांगo;
	__le16 ssn;
पूर्ण __packed;

काष्ठा host_cmd_ds_11n_addba_rsp अणु
	u8 add_rsp_result;
	u8 peer_mac_addr[ETH_ALEN];
	u8 dialog_token;
	__le16 status_code;
	__le16 block_ack_param_set;
	__le16 block_ack_पंचांगo;
	__le16 ssn;
पूर्ण __packed;

काष्ठा host_cmd_ds_11n_delba अणु
	u8 del_result;
	u8 peer_mac_addr[ETH_ALEN];
	__le16 del_ba_param_set;
	__le16 reason_code;
	u8 reserved;
पूर्ण __packed;

काष्ठा host_cmd_ds_11n_baसमयout अणु
	u8 tid;
	u8 peer_mac_addr[ETH_ALEN];
	u8 origninator;
पूर्ण __packed;

काष्ठा host_cmd_ds_11n_cfg अणु
	__le16 action;
	__le16 ht_tx_cap;
	__le16 ht_tx_info;
	__le16 misc_config;	/* Needed क्रम 802.11AC cards only */
पूर्ण __packed;

काष्ठा host_cmd_ds_txbuf_cfg अणु
	__le16 action;
	__le16 buff_size;
	__le16 mp_end_port;	/* SDIO only, reserved क्रम other पूर्णांकerfacces */
	__le16 reserved3;
पूर्ण __packed;

काष्ठा host_cmd_ds_amsdu_aggr_ctrl अणु
	__le16 action;
	__le16 enable;
	__le16 curr_buf_size;
पूर्ण __packed;

काष्ठा host_cmd_ds_sta_deauth अणु
	u8 mac[ETH_ALEN];
	__le16 reason;
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_sta_info अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 mac[ETH_ALEN];
	u8 घातer_mfg_status;
	s8 rssi;
पूर्ण;

काष्ठा host_cmd_ds_sta_list अणु
	__le16 sta_count;
	u8 tlv[];
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_pwr_capability अणु
	काष्ठा mwअगरiex_ie_types_header header;
	s8 min_pwr;
	s8 max_pwr;
पूर्ण;

काष्ठा mwअगरiex_ie_types_local_pwr_स्थिरraपूर्णांक अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 chan;
	u8 स्थिरraपूर्णांक;
पूर्ण;

काष्ठा mwअगरiex_ie_types_wmm_param_set अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 wmm_ie[1];
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_mgmt_frame अणु
	काष्ठा mwअगरiex_ie_types_header header;
	__le16 frame_control;
	u8 frame_contents[];
पूर्ण;

काष्ठा mwअगरiex_ie_types_wmm_queue_status अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 queue_index;
	u8 disabled;
	__le16 medium_समय;
	u8 flow_required;
	u8 flow_created;
	u32 reserved;
पूर्ण;

काष्ठा ieee_types_venकरोr_header अणु
	u8 element_id;
	u8 len;
	काष्ठा अणु
		u8 oui[3];
		u8 oui_type;
	पूर्ण __packed oui;
पूर्ण __packed;

काष्ठा ieee_types_wmm_parameter अणु
	/*
	 * WMM Parameter IE - Venकरोr Specअगरic Header:
	 *   element_id  [221/0xdd]
	 *   Len         [24]
	 *   Oui         [00:50:f2]
	 *   OuiType     [2]
	 *   OuiSubType  [1]
	 *   Version     [1]
	 */
	काष्ठा ieee_types_venकरोr_header vend_hdr;
	u8 oui_subtype;
	u8 version;

	u8 qos_info_biपंचांगap;
	u8 reserved;
	काष्ठा ieee_types_wmm_ac_parameters ac_params[IEEE80211_NUM_ACS];
पूर्ण __packed;

काष्ठा ieee_types_wmm_info अणु

	/*
	 * WMM Info IE - Venकरोr Specअगरic Header:
	 *   element_id  [221/0xdd]
	 *   Len         [7]
	 *   Oui         [00:50:f2]
	 *   OuiType     [2]
	 *   OuiSubType  [0]
	 *   Version     [1]
	 */
	काष्ठा ieee_types_venकरोr_header vend_hdr;
	u8 oui_subtype;
	u8 version;

	u8 qos_info_biपंचांगap;
पूर्ण __packed;

काष्ठा host_cmd_ds_wmm_get_status अणु
	u8 queue_status_tlv[माप(काष्ठा mwअगरiex_ie_types_wmm_queue_status) *
			      IEEE80211_NUM_ACS];
	u8 wmm_param_tlv[माप(काष्ठा ieee_types_wmm_parameter) + 2];
पूर्ण __packed;

काष्ठा mwअगरiex_wmm_ac_status अणु
	u8 disabled;
	u8 flow_required;
	u8 flow_created;
पूर्ण;

काष्ठा mwअगरiex_ie_types_htcap अणु
	काष्ठा mwअगरiex_ie_types_header header;
	काष्ठा ieee80211_ht_cap ht_cap;
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_vhtcap अणु
	काष्ठा mwअगरiex_ie_types_header header;
	काष्ठा ieee80211_vht_cap vht_cap;
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_aid अणु
	काष्ठा mwअगरiex_ie_types_header header;
	__le16 aid;
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_oper_mode_ntf अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 oper_mode;
पूर्ण __packed;

/* VHT Operations IE */
काष्ठा mwअगरiex_ie_types_vht_oper अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 chan_width;
	u8 chan_center_freq_1;
	u8 chan_center_freq_2;
	/* Basic MCS set map, each 2 bits stands क्रम a NSS */
	__le16 basic_mcs_map;
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_wmmcap अणु
	काष्ठा mwअगरiex_ie_types_header header;
	काष्ठा mwअगरiex_types_wmm_info wmm_info;
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_htinfo अणु
	काष्ठा mwअगरiex_ie_types_header header;
	काष्ठा ieee80211_ht_operation ht_oper;
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_2040bssco अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 bss_co_2040;
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_extcap अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 ext_capab[];
पूर्ण __packed;

काष्ठा host_cmd_ds_mem_access अणु
	__le16 action;
	__le16 reserved;
	__le32 addr;
	__le32 value;
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_qos_info अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 qos_info;
पूर्ण __packed;

काष्ठा host_cmd_ds_mac_reg_access अणु
	__le16 action;
	__le16 offset;
	__le32 value;
पूर्ण __packed;

काष्ठा host_cmd_ds_bbp_reg_access अणु
	__le16 action;
	__le16 offset;
	u8 value;
	u8 reserved[3];
पूर्ण __packed;

काष्ठा host_cmd_ds_rf_reg_access अणु
	__le16 action;
	__le16 offset;
	u8 value;
	u8 reserved[3];
पूर्ण __packed;

काष्ठा host_cmd_ds_pmic_reg_access अणु
	__le16 action;
	__le16 offset;
	u8 value;
	u8 reserved[3];
पूर्ण __packed;

काष्ठा host_cmd_ds_802_11_eeprom_access अणु
	__le16 action;

	__le16 offset;
	__le16 byte_count;
	u8 value;
पूर्ण __packed;

काष्ठा mwअगरiex_assoc_event अणु
	u8 sta_addr[ETH_ALEN];
	__le16 type;
	__le16 len;
	__le16 frame_control;
	__le16 cap_info;
	__le16 listen_पूर्णांकerval;
	u8 data[];
पूर्ण __packed;

काष्ठा host_cmd_ds_sys_config अणु
	__le16 action;
	u8 tlv[];
पूर्ण;

काष्ठा host_cmd_11ac_vht_cfg अणु
	__le16 action;
	u8 band_config;
	u8 misc_config;
	__le32 cap_info;
	__le32 mcs_tx_set;
	__le32 mcs_rx_set;
पूर्ण __packed;

काष्ठा host_cmd_tlv_akmp अणु
	काष्ठा mwअगरiex_ie_types_header header;
	__le16 key_mgmt;
	__le16 key_mgmt_operation;
पूर्ण __packed;

काष्ठा host_cmd_tlv_pwk_cipher अणु
	काष्ठा mwअगरiex_ie_types_header header;
	__le16 proto;
	u8 cipher;
	u8 reserved;
पूर्ण __packed;

काष्ठा host_cmd_tlv_gwk_cipher अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 cipher;
	u8 reserved;
पूर्ण __packed;

काष्ठा host_cmd_tlv_passphrase अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 passphrase[];
पूर्ण __packed;

काष्ठा host_cmd_tlv_wep_key अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 key_index;
	u8 is_शेष;
	u8 key[1];
पूर्ण;

काष्ठा host_cmd_tlv_auth_type अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 auth_type;
पूर्ण __packed;

काष्ठा host_cmd_tlv_encrypt_protocol अणु
	काष्ठा mwअगरiex_ie_types_header header;
	__le16 proto;
पूर्ण __packed;

काष्ठा host_cmd_tlv_ssid अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 ssid[];
पूर्ण __packed;

काष्ठा host_cmd_tlv_rates अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 rates[];
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_bssid_list अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 bssid[ETH_ALEN];
पूर्ण __packed;

काष्ठा host_cmd_tlv_bcast_ssid अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 bcast_ctl;
पूर्ण __packed;

काष्ठा host_cmd_tlv_beacon_period अणु
	काष्ठा mwअगरiex_ie_types_header header;
	__le16 period;
पूर्ण __packed;

काष्ठा host_cmd_tlv_dtim_period अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 period;
पूर्ण __packed;

काष्ठा host_cmd_tlv_frag_threshold अणु
	काष्ठा mwअगरiex_ie_types_header header;
	__le16 frag_thr;
पूर्ण __packed;

काष्ठा host_cmd_tlv_rts_threshold अणु
	काष्ठा mwअगरiex_ie_types_header header;
	__le16 rts_thr;
पूर्ण __packed;

काष्ठा host_cmd_tlv_retry_limit अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 limit;
पूर्ण __packed;

काष्ठा host_cmd_tlv_mac_addr अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 mac_addr[ETH_ALEN];
पूर्ण __packed;

काष्ठा host_cmd_tlv_channel_band अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 band_config;
	u8 channel;
पूर्ण __packed;

काष्ठा host_cmd_tlv_ageout_समयr अणु
	काष्ठा mwअगरiex_ie_types_header header;
	__le32 sta_ao_समयr;
पूर्ण __packed;

काष्ठा host_cmd_tlv_घातer_स्थिरraपूर्णांक अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 स्थिरraपूर्णांक;
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_btcoex_scan_समय अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 coex_scan;
	u8 reserved;
	__le16 min_scan_समय;
	__le16 max_scan_समय;
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_btcoex_aggr_win_size अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 coex_win_size;
	u8 tx_win_size;
	u8 rx_win_size;
	u8 reserved;
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_robust_coex अणु
	काष्ठा mwअगरiex_ie_types_header header;
	__le32 mode;
पूर्ण __packed;

काष्ठा host_cmd_ds_version_ext अणु
	u8 version_str_sel;
	अक्षर version_str[128];
पूर्ण __packed;

काष्ठा host_cmd_ds_mgmt_frame_reg अणु
	__le16 action;
	__le32 mask;
पूर्ण __packed;

काष्ठा host_cmd_ds_p2p_mode_cfg अणु
	__le16 action;
	__le16 mode;
पूर्ण __packed;

काष्ठा host_cmd_ds_reमुख्य_on_chan अणु
	__le16 action;
	u8 status;
	u8 reserved;
	u8 band_cfg;
	u8 channel;
	__le32 duration;
पूर्ण __packed;

काष्ठा host_cmd_ds_802_11_ibss_status अणु
	__le16 action;
	__le16 enable;
	u8 bssid[ETH_ALEN];
	__le16 beacon_पूर्णांकerval;
	__le16 atim_winकरोw;
	__le16 use_g_rate_protect;
पूर्ण __packed;

काष्ठा mwअगरiex_fw_mef_entry अणु
	u8 mode;
	u8 action;
	__le16 exprsize;
	u8 expr[];
पूर्ण __packed;

काष्ठा host_cmd_ds_mef_cfg अणु
	__le32 criteria;
	__le16 num_entries;
	काष्ठा mwअगरiex_fw_mef_entry mef_entry[];
पूर्ण __packed;

#घोषणा CONNECTION_TYPE_INFRA   0
#घोषणा CONNECTION_TYPE_ADHOC   1
#घोषणा CONNECTION_TYPE_AP      2

काष्ठा host_cmd_ds_set_bss_mode अणु
	u8 con_type;
पूर्ण __packed;

काष्ठा host_cmd_ds_pcie_details अणु
	/* TX buffer descriptor ring address */
	__le32 txbd_addr_lo;
	__le32 txbd_addr_hi;
	/* TX buffer descriptor ring count */
	__le32 txbd_count;

	/* RX buffer descriptor ring address */
	__le32 rxbd_addr_lo;
	__le32 rxbd_addr_hi;
	/* RX buffer descriptor ring count */
	__le32 rxbd_count;

	/* Event buffer descriptor ring address */
	__le32 evtbd_addr_lo;
	__le32 evtbd_addr_hi;
	/* Event buffer descriptor ring count */
	__le32 evtbd_count;

	/* Sleep cookie buffer physical address */
	__le32 sleep_cookie_addr_lo;
	__le32 sleep_cookie_addr_hi;
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_rssi_threshold अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 असल_value;
	u8 evt_freq;
पूर्ण __packed;

#घोषणा MWIFIEX_DFS_REC_HDR_LEN		8
#घोषणा MWIFIEX_DFS_REC_HDR_NUM		10
#घोषणा MWIFIEX_BIN_COUNTER_LEN		7

काष्ठा mwअगरiex_radar_det_event अणु
	__le32 detect_count;
	u8 reg_करोमुख्य;  /*1=fcc, 2=etsi, 3=mic*/
	u8 det_type;  /*0=none, 1=pw(chirp), 2=pri(radar)*/
	__le16 pw_chirp_type;
	u8 pw_chirp_idx;
	u8 pw_value;
	u8 pri_radar_type;
	u8 pri_bincnt;
	u8 bin_counter[MWIFIEX_BIN_COUNTER_LEN];
	u8 num_dfs_records;
	u8 dfs_record_hdr[MWIFIEX_DFS_REC_HDR_NUM][MWIFIEX_DFS_REC_HDR_LEN];
	__le32 passed;
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_multi_chan_info अणु
	काष्ठा mwअगरiex_ie_types_header header;
	__le16 status;
	u8 tlv_buffer[];
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_mc_group_info अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 chan_group_id;
	u8 chan_buf_weight;
	u8 band_config;
	u8 chan_num;
	__le32 chan_समय;
	__le32 reserved;
	जोड़ अणु
		u8 sdio_func_num;
		u8 usb_ep_num;
	पूर्ण hid_num;
	u8 पूर्णांकf_num;
	u8 bss_type_numlist[];
पूर्ण __packed;

काष्ठा meas_rpt_map अणु
	u8 rssi:3;
	u8 unmeasured:1;
	u8 radar:1;
	u8 unidentअगरied_sig:1;
	u8 ofdm_preamble:1;
	u8 bss:1;
पूर्ण __packed;

काष्ठा mwअगरiex_ie_types_chan_rpt_data अणु
	काष्ठा mwअगरiex_ie_types_header header;
	काष्ठा meas_rpt_map map;
पूर्ण __packed;

काष्ठा host_cmd_ds_802_11_subsc_evt अणु
	__le16 action;
	__le16 events;
पूर्ण __packed;

काष्ठा chan_चयन_result अणु
	u8 cur_chan;
	u8 status;
	u8 reason;
पूर्ण __packed;

काष्ठा mwअगरiex_tdls_generic_event अणु
	__le16 type;
	u8 peer_mac[ETH_ALEN];
	जोड़ अणु
		काष्ठा chan_चयन_result चयन_result;
		u8 cs_stop_reason;
		__le16 reason_code;
		__le16 reserved;
	पूर्ण u;
पूर्ण __packed;

काष्ठा mwअगरiex_ie अणु
	__le16 ie_index;
	__le16 mgmt_subtype_mask;
	__le16 ie_length;
	u8 ie_buffer[IEEE_MAX_IE_SIZE];
पूर्ण __packed;

#घोषणा MAX_MGMT_IE_INDEX	16
काष्ठा mwअगरiex_ie_list अणु
	__le16 type;
	__le16 len;
	काष्ठा mwअगरiex_ie ie_list[MAX_MGMT_IE_INDEX];
पूर्ण __packed;

काष्ठा coalesce_filt_field_param अणु
	u8 operation;
	u8 opeअक्रम_len;
	__le16 offset;
	u8 opeअक्रम_byte_stream[4];
पूर्ण;

काष्ठा coalesce_receive_filt_rule अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 num_of_fields;
	u8 pkt_type;
	__le16 max_coalescing_delay;
	काष्ठा coalesce_filt_field_param params[];
पूर्ण __packed;

काष्ठा host_cmd_ds_coalesce_cfg अणु
	__le16 action;
	__le16 num_of_rules;
	काष्ठा coalesce_receive_filt_rule rule[];
पूर्ण __packed;

काष्ठा host_cmd_ds_multi_chan_policy अणु
	__le16 action;
	__le16 policy;
पूर्ण __packed;

काष्ठा host_cmd_ds_robust_coex अणु
	__le16 action;
	__le16 reserved;
पूर्ण __packed;

काष्ठा host_cmd_ds_wakeup_reason अणु
	__le16  wakeup_reason;
पूर्ण __packed;

काष्ठा host_cmd_ds_gtk_rekey_params अणु
	__le16 action;
	u8 kck[NL80211_KCK_LEN];
	u8 kek[NL80211_KEK_LEN];
	__le32 replay_ctr_low;
	__le32 replay_ctr_high;
पूर्ण __packed;

काष्ठा host_cmd_ds_chan_region_cfg अणु
	__le16 action;
पूर्ण __packed;

काष्ठा host_cmd_ds_pkt_aggr_ctrl अणु
	__le16 action;
	__le16 enable;
	__le16 tx_aggr_max_size;
	__le16 tx_aggr_max_num;
	__le16 tx_aggr_align;
पूर्ण __packed;

काष्ठा host_cmd_ds_sta_configure अणु
	__le16 action;
	u8 tlv_buffer[];
पूर्ण __packed;

काष्ठा host_cmd_ds_command अणु
	__le16 command;
	__le16 size;
	__le16 seq_num;
	__le16 result;
	जोड़ अणु
		काष्ठा host_cmd_ds_get_hw_spec hw_spec;
		काष्ठा host_cmd_ds_mac_control mac_ctrl;
		काष्ठा host_cmd_ds_802_11_mac_address mac_addr;
		काष्ठा host_cmd_ds_mac_multicast_adr mc_addr;
		काष्ठा host_cmd_ds_802_11_get_log get_log;
		काष्ठा host_cmd_ds_802_11_rssi_info rssi_info;
		काष्ठा host_cmd_ds_802_11_rssi_info_rsp rssi_info_rsp;
		काष्ठा host_cmd_ds_802_11_snmp_mib smib;
		काष्ठा host_cmd_ds_tx_rate_query tx_rate;
		काष्ठा host_cmd_ds_tx_rate_cfg tx_rate_cfg;
		काष्ठा host_cmd_ds_txpwr_cfg txp_cfg;
		काष्ठा host_cmd_ds_rf_tx_pwr txp;
		काष्ठा host_cmd_ds_rf_ant_mimo ant_mimo;
		काष्ठा host_cmd_ds_rf_ant_siso ant_siso;
		काष्ठा host_cmd_ds_802_11_ps_mode_enh psmode_enh;
		काष्ठा host_cmd_ds_802_11_hs_cfg_enh opt_hs_cfg;
		काष्ठा host_cmd_ds_802_11_scan scan;
		काष्ठा host_cmd_ds_802_11_scan_ext ext_scan;
		काष्ठा host_cmd_ds_802_11_scan_rsp scan_resp;
		काष्ठा host_cmd_ds_802_11_bg_scan_config bg_scan_config;
		काष्ठा host_cmd_ds_802_11_bg_scan_query bg_scan_query;
		काष्ठा host_cmd_ds_802_11_bg_scan_query_rsp bg_scan_query_resp;
		काष्ठा host_cmd_ds_802_11_associate associate;
		काष्ठा host_cmd_ds_802_11_associate_rsp associate_rsp;
		काष्ठा host_cmd_ds_802_11_deauthenticate deauth;
		काष्ठा host_cmd_ds_802_11_ad_hoc_start adhoc_start;
		काष्ठा host_cmd_ds_802_11_ad_hoc_start_result start_result;
		काष्ठा host_cmd_ds_802_11_ad_hoc_join_result join_result;
		काष्ठा host_cmd_ds_802_11_ad_hoc_join adhoc_join;
		काष्ठा host_cmd_ds_802_11d_करोमुख्य_info करोमुख्य_info;
		काष्ठा host_cmd_ds_802_11d_करोमुख्य_info_rsp करोमुख्य_info_resp;
		काष्ठा host_cmd_ds_11n_addba_req add_ba_req;
		काष्ठा host_cmd_ds_11n_addba_rsp add_ba_rsp;
		काष्ठा host_cmd_ds_11n_delba del_ba;
		काष्ठा host_cmd_ds_txbuf_cfg tx_buf;
		काष्ठा host_cmd_ds_amsdu_aggr_ctrl amsdu_aggr_ctrl;
		काष्ठा host_cmd_ds_11n_cfg htcfg;
		काष्ठा host_cmd_ds_wmm_get_status get_wmm_status;
		काष्ठा host_cmd_ds_802_11_key_material key_material;
		काष्ठा host_cmd_ds_802_11_key_material_v2 key_material_v2;
		काष्ठा host_cmd_ds_version_ext verext;
		काष्ठा host_cmd_ds_mgmt_frame_reg reg_mask;
		काष्ठा host_cmd_ds_reमुख्य_on_chan roc_cfg;
		काष्ठा host_cmd_ds_p2p_mode_cfg mode_cfg;
		काष्ठा host_cmd_ds_802_11_ibss_status ibss_coalescing;
		काष्ठा host_cmd_ds_mef_cfg mef_cfg;
		काष्ठा host_cmd_ds_mem_access mem;
		काष्ठा host_cmd_ds_mac_reg_access mac_reg;
		काष्ठा host_cmd_ds_bbp_reg_access bbp_reg;
		काष्ठा host_cmd_ds_rf_reg_access rf_reg;
		काष्ठा host_cmd_ds_pmic_reg_access pmic_reg;
		काष्ठा host_cmd_ds_set_bss_mode bss_mode;
		काष्ठा host_cmd_ds_pcie_details pcie_host_spec;
		काष्ठा host_cmd_ds_802_11_eeprom_access eeprom;
		काष्ठा host_cmd_ds_802_11_subsc_evt subsc_evt;
		काष्ठा host_cmd_ds_sys_config uap_sys_config;
		काष्ठा host_cmd_ds_sta_deauth sta_deauth;
		काष्ठा host_cmd_ds_sta_list sta_list;
		काष्ठा host_cmd_11ac_vht_cfg vht_cfg;
		काष्ठा host_cmd_ds_coalesce_cfg coalesce_cfg;
		काष्ठा host_cmd_ds_tdls_config tdls_config;
		काष्ठा host_cmd_ds_tdls_oper tdls_oper;
		काष्ठा host_cmd_ds_chan_rpt_req chan_rpt_req;
		काष्ठा host_cmd_sdio_sp_rx_aggr_cfg sdio_rx_aggr_cfg;
		काष्ठा host_cmd_ds_multi_chan_policy mc_policy;
		काष्ठा host_cmd_ds_robust_coex coex;
		काष्ठा host_cmd_ds_wakeup_reason hs_wakeup_reason;
		काष्ठा host_cmd_ds_gtk_rekey_params rekey;
		काष्ठा host_cmd_ds_chan_region_cfg reg_cfg;
		काष्ठा host_cmd_ds_pkt_aggr_ctrl pkt_aggr_ctrl;
		काष्ठा host_cmd_ds_sta_configure sta_cfg;
	पूर्ण params;
पूर्ण __packed;

काष्ठा mwअगरiex_opt_sleep_confirm अणु
	__le16 command;
	__le16 size;
	__le16 seq_num;
	__le16 result;
	__le16 action;
	__le16 resp_ctrl;
पूर्ण __packed;

काष्ठा hw_spec_max_conn अणु
	काष्ठा mwअगरiex_ie_types_header header;
	u8 max_p2p_conn;
	u8 max_sta_conn;
पूर्ण __packed;

#पूर्ण_अगर /* !_MWIFIEX_FW_H_ */
