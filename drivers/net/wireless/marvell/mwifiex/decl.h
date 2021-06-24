<शैली गुरु>
/*
 * NXP Wireless LAN device driver: generic data काष्ठाures and APIs
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

#अगर_अघोषित _MWIFIEX_DECL_H_
#घोषणा _MWIFIEX_DECL_H_

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/रुको.h>
#समावेश <linux/समयr.h>
#समावेश <linux/ieee80211.h>
#समावेश <uapi/linux/अगर_arp.h>
#समावेश <net/cfg80211.h>

#घोषणा MWIFIEX_BSS_COEX_COUNT	     2
#घोषणा MWIFIEX_MAX_BSS_NUM         (3)

#घोषणा MWIFIEX_DMA_ALIGN_SZ	    64
#घोषणा MWIFIEX_RX_HEADROOM	    64
#घोषणा MAX_TXPD_SZ		    32
#घोषणा INTF_HDR_ALIGN		     4

#घोषणा MWIFIEX_MIN_DATA_HEADER_LEN (MWIFIEX_DMA_ALIGN_SZ + INTF_HDR_ALIGN + \
				     MAX_TXPD_SZ)
#घोषणा MWIFIEX_MGMT_FRAME_HEADER_SIZE	8	/* माप(pkt_type)
						 *   + माप(tx_control)
						 */

#घोषणा MWIFIEX_MAX_TX_BASTREAM_SUPPORTED	2
#घोषणा MWIFIEX_MAX_RX_BASTREAM_SUPPORTED	16
#घोषणा MWIFIEX_MAX_TDLS_PEER_SUPPORTED 8

#घोषणा MWIFIEX_STA_AMPDU_DEF_TXWINSIZE        64
#घोषणा MWIFIEX_STA_AMPDU_DEF_RXWINSIZE        64
#घोषणा MWIFIEX_STA_COEX_AMPDU_DEF_RXWINSIZE   16

#घोषणा MWIFIEX_UAP_AMPDU_DEF_TXWINSIZE        32

#घोषणा MWIFIEX_UAP_COEX_AMPDU_DEF_RXWINSIZE   16

#घोषणा MWIFIEX_UAP_AMPDU_DEF_RXWINSIZE        16
#घोषणा MWIFIEX_11AC_STA_AMPDU_DEF_TXWINSIZE   64
#घोषणा MWIFIEX_11AC_STA_AMPDU_DEF_RXWINSIZE   64
#घोषणा MWIFIEX_11AC_UAP_AMPDU_DEF_TXWINSIZE   64
#घोषणा MWIFIEX_11AC_UAP_AMPDU_DEF_RXWINSIZE   64

#घोषणा MWIFIEX_DEFAULT_BLOCK_ACK_TIMEOUT  0xffff

#घोषणा MWIFIEX_RATE_BITMAP_MCS0   32

#घोषणा MWIFIEX_RX_DATA_BUF_SIZE     (4 * 1024)
#घोषणा MWIFIEX_RX_CMD_BUF_SIZE	     (2 * 1024)

#घोषणा MAX_BEACON_PERIOD                  (4000)
#घोषणा MIN_BEACON_PERIOD                  (50)
#घोषणा MAX_DTIM_PERIOD                    (100)
#घोषणा MIN_DTIM_PERIOD                    (1)

#घोषणा MWIFIEX_RTS_MIN_VALUE              (0)
#घोषणा MWIFIEX_RTS_MAX_VALUE              (2347)
#घोषणा MWIFIEX_FRAG_MIN_VALUE             (256)
#घोषणा MWIFIEX_FRAG_MAX_VALUE             (2346)
#घोषणा MWIFIEX_WMM_VERSION                0x01
#घोषणा MWIFIEX_WMM_SUBTYPE                0x01

#घोषणा MWIFIEX_RETRY_LIMIT                14
#घोषणा MWIFIEX_SDIO_BLOCK_SIZE            256

#घोषणा MWIFIEX_BUF_FLAG_REQUEUED_PKT      BIT(0)
#घोषणा MWIFIEX_BUF_FLAG_BRIDGED_PKT	   BIT(1)
#घोषणा MWIFIEX_BUF_FLAG_TDLS_PKT	   BIT(2)
#घोषणा MWIFIEX_BUF_FLAG_EAPOL_TX_STATUS   BIT(3)
#घोषणा MWIFIEX_BUF_FLAG_ACTION_TX_STATUS  BIT(4)
#घोषणा MWIFIEX_BUF_FLAG_AGGR_PKT          BIT(5)

#घोषणा MWIFIEX_BRIDGED_PKTS_THR_HIGH      1024
#घोषणा MWIFIEX_BRIDGED_PKTS_THR_LOW        128

#घोषणा MWIFIEX_TDLS_DISABLE_LINK             0x00
#घोषणा MWIFIEX_TDLS_ENABLE_LINK              0x01
#घोषणा MWIFIEX_TDLS_CREATE_LINK              0x02
#घोषणा MWIFIEX_TDLS_CONFIG_LINK              0x03

#घोषणा MWIFIEX_TDLS_RSSI_HIGH		50
#घोषणा MWIFIEX_TDLS_RSSI_LOW		55
#घोषणा MWIFIEX_TDLS_MAX_FAIL_COUNT      4
#घोषणा MWIFIEX_AUTO_TDLS_IDLE_TIME     10

/* 54M rates, index from 0 to 11 */
#घोषणा MWIFIEX_RATE_INDEX_MCS0 12
/* 12-27=MCS0-15(BW20) */
#घोषणा MWIFIEX_BW20_MCS_NUM 15

/* Rate index क्रम OFDM 0 */
#घोषणा MWIFIEX_RATE_INDEX_OFDM0   4

#घोषणा MWIFIEX_MAX_STA_NUM		3
#घोषणा MWIFIEX_MAX_UAP_NUM		3
#घोषणा MWIFIEX_MAX_P2P_NUM		3

#घोषणा MWIFIEX_A_BAND_START_FREQ	5000

/* SDIO Aggr data packet special info */
#घोषणा SDIO_MAX_AGGR_BUF_SIZE		(256 * 255)
#घोषणा BLOCK_NUMBER_OFFSET		15
#घोषणा SDIO_HEADER_OFFSET		28

#घोषणा MWIFIEX_SIZE_4K 0x4000

क्रमागत mwअगरiex_bss_type अणु
	MWIFIEX_BSS_TYPE_STA = 0,
	MWIFIEX_BSS_TYPE_UAP = 1,
	MWIFIEX_BSS_TYPE_P2P = 2,
	MWIFIEX_BSS_TYPE_ANY = 0xff,
पूर्ण;

क्रमागत mwअगरiex_bss_role अणु
	MWIFIEX_BSS_ROLE_STA = 0,
	MWIFIEX_BSS_ROLE_UAP = 1,
	MWIFIEX_BSS_ROLE_ANY = 0xff,
पूर्ण;

क्रमागत mwअगरiex_tdls_status अणु
	TDLS_NOT_SETUP = 0,
	TDLS_SETUP_INPROGRESS,
	TDLS_SETUP_COMPLETE,
	TDLS_SETUP_FAILURE,
	TDLS_LINK_TEARDOWN,
	TDLS_CHAN_SWITCHING,
	TDLS_IN_BASE_CHAN,
	TDLS_IN_OFF_CHAN,
पूर्ण;

क्रमागत mwअगरiex_tdls_error_code अणु
	TDLS_ERR_NO_ERROR = 0,
	TDLS_ERR_INTERNAL_ERROR,
	TDLS_ERR_MAX_LINKS_EST,
	TDLS_ERR_LINK_EXISTS,
	TDLS_ERR_LINK_NONEXISTENT,
	TDLS_ERR_PEER_STA_UNREACHABLE = 25,
पूर्ण;

#घोषणा BSS_ROLE_BIT_MASK    BIT(0)

#घोषणा GET_BSS_ROLE(priv)   ((priv)->bss_role & BSS_ROLE_BIT_MASK)

क्रमागत mwअगरiex_data_frame_type अणु
	MWIFIEX_DATA_FRAME_TYPE_ETH_II = 0,
	MWIFIEX_DATA_FRAME_TYPE_802_11,
पूर्ण;

काष्ठा mwअगरiex_fw_image अणु
	u8 *helper_buf;
	u32 helper_len;
	u8 *fw_buf;
	u32 fw_len;
पूर्ण;

काष्ठा mwअगरiex_802_11_ssid अणु
	u32 ssid_len;
	u8 ssid[IEEE80211_MAX_SSID_LEN];
पूर्ण;

काष्ठा mwअगरiex_रुको_queue अणु
	रुको_queue_head_t रुको;
	पूर्णांक status;
पूर्ण;

काष्ठा mwअगरiex_rxinfo अणु
	काष्ठा sk_buff *parent;
	u8 bss_num;
	u8 bss_type;
	u8 use_count;
	u8 buf_type;
पूर्ण;

काष्ठा mwअगरiex_txinfo अणु
	u32 status_code;
	u8 flags;
	u8 bss_num;
	u8 bss_type;
	u8 aggr_num;
	u32 pkt_len;
	u8 ack_frame_id;
	u64 cookie;
पूर्ण;

क्रमागत mwअगरiex_wmm_ac_e अणु
	WMM_AC_BK,
	WMM_AC_BE,
	WMM_AC_VI,
	WMM_AC_VO
पूर्ण __packed;

काष्ठा ieee_types_wmm_ac_parameters अणु
	u8 aci_aअगरsn_biपंचांगap;
	u8 ecw_biपंचांगap;
	__le16 tx_op_limit;
पूर्ण __packed;

काष्ठा mwअगरiex_types_wmm_info अणु
	u8 oui[4];
	u8 subtype;
	u8 version;
	u8 qos_info;
	u8 reserved;
	काष्ठा ieee_types_wmm_ac_parameters ac_params[IEEE80211_NUM_ACS];
पूर्ण __packed;

काष्ठा mwअगरiex_arp_eth_header अणु
	काष्ठा arphdr hdr;
	u8 ar_sha[ETH_ALEN];
	u8 ar_sip[4];
	u8 ar_tha[ETH_ALEN];
	u8 ar_tip[4];
पूर्ण __packed;

काष्ठा mwअगरiex_chan_stats अणु
	u8 chan_num;
	u8 bandcfg;
	u8 flags;
	s8 noise;
	u16 total_bss;
	u16 cca_scan_dur;
	u16 cca_busy_dur;
पूर्ण __packed;

#घोषणा MWIFIEX_HIST_MAX_SAMPLES	1048576
#घोषणा MWIFIEX_MAX_RX_RATES		     44
#घोषणा MWIFIEX_MAX_AC_RX_RATES		     74
#घोषणा MWIFIEX_MAX_SNR			    256
#घोषणा MWIFIEX_MAX_NOISE_FLR		    256
#घोषणा MWIFIEX_MAX_SIG_STRENGTH	    256

काष्ठा mwअगरiex_histogram_data अणु
	atomic_t rx_rate[MWIFIEX_MAX_AC_RX_RATES];
	atomic_t snr[MWIFIEX_MAX_SNR];
	atomic_t noise_flr[MWIFIEX_MAX_NOISE_FLR];
	atomic_t sig_str[MWIFIEX_MAX_SIG_STRENGTH];
	atomic_t num_samples;
पूर्ण;

काष्ठा mwअगरiex_अगरace_comb अणु
	u8 sta_पूर्णांकf;
	u8 uap_पूर्णांकf;
	u8 p2p_पूर्णांकf;
पूर्ण;

काष्ठा mwअगरiex_radar_params अणु
	काष्ठा cfg80211_chan_def *chandef;
	u32 cac_समय_ms;
पूर्ण __packed;

काष्ठा mwअगरiex_11h_पूर्णांकf_state अणु
	bool is_11h_enabled;
	bool is_11h_active;
पूर्ण __packed;

#घोषणा MWIFIEX_FW_DUMP_IDX		0xff
#घोषणा MWIFIEX_FW_DUMP_MAX_MEMSIZE     0x160000
#घोषणा MWIFIEX_DRV_INFO_IDX		20
#घोषणा FW_DUMP_MAX_NAME_LEN		8
#घोषणा FW_DUMP_HOST_READY      0xEE
#घोषणा FW_DUMP_DONE			0xFF
#घोषणा FW_DUMP_READ_DONE		0xFE

काष्ठा memory_type_mapping अणु
	u8 mem_name[FW_DUMP_MAX_NAME_LEN];
	u8 *mem_ptr;
	u32 mem_size;
	u8 करोne_flag;
पूर्ण;

क्रमागत rdwr_status अणु
	RDWR_STATUS_SUCCESS = 0,
	RDWR_STATUS_FAILURE = 1,
	RDWR_STATUS_DONE = 2
पूर्ण;

क्रमागत mwअगरiex_chan_width अणु
	CHAN_BW_20MHZ = 0,
	CHAN_BW_10MHZ,
	CHAN_BW_40MHZ,
	CHAN_BW_80MHZ,
	CHAN_BW_8080MHZ,
	CHAN_BW_160MHZ,
	CHAN_BW_5MHZ,
पूर्ण;

क्रमागत mwअगरiex_chan_offset अणु
	SEC_CHAN_NONE = 0,
	SEC_CHAN_ABOVE = 1,
	SEC_CHAN_5MHZ = 2,
	SEC_CHAN_BELOW = 3
पूर्ण;

#पूर्ण_अगर /* !_MWIFIEX_DECL_H_ */
