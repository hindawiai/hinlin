<शैली गुरु>
/*
 * Copyright (c) 2013 Eugene Krasnikov <k.eugene.e@gmail.com>
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित _WCN36XX_H_
#घोषणा _WCN36XX_H_

#समावेश <linux/completion.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/spinlock.h>
#समावेश <net/mac80211.h>

#समावेश "hal.h"
#समावेश "smd.h"
#समावेश "txrx.h"
#समावेश "dxe.h"
#समावेश "pmc.h"
#समावेश "debug.h"

#घोषणा WLAN_NV_खाता               "wlan/prima/WCNSS_qcom_wlan_nv.bin"
#घोषणा WCN36XX_AGGR_BUFFER_SIZE 64

बाह्य अचिन्हित पूर्णांक wcn36xx_dbg_mask;

क्रमागत wcn36xx_debug_mask अणु
	WCN36XX_DBG_DXE		= 0x00000001,
	WCN36XX_DBG_DXE_DUMP	= 0x00000002,
	WCN36XX_DBG_SMD		= 0x00000004,
	WCN36XX_DBG_SMD_DUMP	= 0x00000008,
	WCN36XX_DBG_RX		= 0x00000010,
	WCN36XX_DBG_RX_DUMP	= 0x00000020,
	WCN36XX_DBG_TX		= 0x00000040,
	WCN36XX_DBG_TX_DUMP	= 0x00000080,
	WCN36XX_DBG_HAL		= 0x00000100,
	WCN36XX_DBG_HAL_DUMP	= 0x00000200,
	WCN36XX_DBG_MAC		= 0x00000400,
	WCN36XX_DBG_BEACON	= 0x00000800,
	WCN36XX_DBG_BEACON_DUMP	= 0x00001000,
	WCN36XX_DBG_PMC		= 0x00002000,
	WCN36XX_DBG_PMC_DUMP	= 0x00004000,
	WCN36XX_DBG_TESTMODE		= 0x00008000,
	WCN36XX_DBG_TESTMODE_DUMP	= 0x00010000,
	WCN36XX_DBG_ANY		= 0xffffffff,
पूर्ण;

#घोषणा wcn36xx_err(fmt, arg...)				\
	prपूर्णांकk(KERN_ERR pr_fmt("ERROR " fmt), ##arg)

#घोषणा wcn36xx_warn(fmt, arg...)				\
	prपूर्णांकk(KERN_WARNING pr_fmt("WARNING " fmt), ##arg)

#घोषणा wcn36xx_info(fmt, arg...)		\
	prपूर्णांकk(KERN_INFO pr_fmt(fmt), ##arg)

#घोषणा wcn36xx_dbg(mask, fmt, arg...) करो अणु			\
	अगर (wcn36xx_dbg_mask & mask)					\
		prपूर्णांकk(KERN_DEBUG pr_fmt(fmt), ##arg);	\
पूर्ण जबतक (0)

#घोषणा wcn36xx_dbg_dump(mask, prefix_str, buf, len) करो अणु	\
	अगर (wcn36xx_dbg_mask & mask)					\
		prपूर्णांक_hex_dump(KERN_DEBUG, pr_fmt(prefix_str),	\
			       DUMP_PREFIX_OFFSET, 32, 1,	\
			       buf, len, false);		\
पूर्ण जबतक (0)

क्रमागत wcn36xx_ampdu_state अणु
	WCN36XX_AMPDU_NONE,
	WCN36XX_AMPDU_INIT,
	WCN36XX_AMPDU_START,
	WCN36XX_AMPDU_OPERATIONAL,
पूर्ण;

#घोषणा HW_VALUE_PHY_SHIFT 8
#घोषणा HW_VALUE_PHY(hw_value) ((hw_value) >> HW_VALUE_PHY_SHIFT)
#घोषणा HW_VALUE_CHANNEL(hw_value) ((hw_value) & 0xFF)
#घोषणा WCN36XX_HW_CHANNEL(__wcn)\
	HW_VALUE_CHANNEL(__wcn->hw->conf.chandef.chan->hw_value)
#घोषणा WCN36XX_BAND(__wcn) (__wcn->hw->conf.chandef.chan->band)
#घोषणा WCN36XX_CENTER_FREQ(__wcn) (__wcn->hw->conf.chandef.chan->center_freq)
#घोषणा WCN36XX_LISTEN_INTERVAL(__wcn) (__wcn->hw->conf.listen_पूर्णांकerval)
#घोषणा WCN36XX_FLAGS(__wcn) (__wcn->hw->flags)
#घोषणा WCN36XX_MAX_POWER(__wcn) (__wcn->hw->conf.chandef.chan->max_घातer)

#घोषणा RF_UNKNOWN	0x0000
#घोषणा RF_IRIS_WCN3620	0x3620
#घोषणा RF_IRIS_WCN3680	0x3680

अटल अंतरभूत व्योम buff_to_be(u32 *buf, माप_प्रकार len)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < len; i++)
		buf[i] = cpu_to_be32(buf[i]);
पूर्ण

काष्ठा nv_data अणु
	पूर्णांक	is_valid;
	u8	table;
पूर्ण;

/**
 * काष्ठा wcn36xx_vअगर - holds VIF related fields
 *
 * @bss_index: bss_index is initially set to 0xFF. bss_index is received from
 * HW after first config_bss call and must be used in delete_bss and
 * enter/निकास_bmps.
 */
काष्ठा wcn36xx_vअगर अणु
	काष्ठा list_head list;
	u8 dtim_period;
	क्रमागत ani_ed_type encrypt_type;
	bool is_joining;
	bool sta_assoc;
	काष्ठा wcn36xx_hal_mac_ssid ssid;
	क्रमागत wcn36xx_hal_bss_type bss_type;

	/* Power management */
	bool allow_bmps;
	क्रमागत wcn36xx_घातer_state pw_state;

	u8 bss_index;
	/* Returned from WCN36XX_HAL_ADD_STA_SELF_RSP */
	u8 self_sta_index;
	u8 self_dpu_desc_index;
	u8 self_ucast_dpu_sign;

	काष्ठा list_head sta_list;
पूर्ण;

/**
 * काष्ठा wcn36xx_sta - holds STA related fields
 *
 * @tid: traffic ID that is used during AMPDU and in TX BD.
 * @sta_index: STA index is वापसed from HW after config_sta call and is
 * used in both SMD channel and TX BD.
 * @dpu_desc_index: DPU descriptor index is वापसed from HW after config_sta
 * call and is used in TX BD.
 * @bss_sta_index: STA index is वापसed from HW after config_bss call and is
 * used in both SMD channel and TX BD. See table bellow when it is used.
 * @bss_dpu_desc_index: DPU descriptor index is वापसed from HW after
 * config_bss call and is used in TX BD.
 * ______________________________________________
 * |		  |	STA	|	AP	|
 * |______________|_____________|_______________|
 * |    TX BD     |bss_sta_index|   sta_index   |
 * |______________|_____________|_______________|
 * |all SMD calls |bss_sta_index|   sta_index	|
 * |______________|_____________|_______________|
 * |smd_delete_sta|  sta_index  |   sta_index	|
 * |______________|_____________|_______________|
 */
काष्ठा wcn36xx_sta अणु
	काष्ठा list_head list;
	काष्ठा wcn36xx_vअगर *vअगर;
	u16 aid;
	u16 tid;
	u8 sta_index;
	u8 dpu_desc_index;
	u8 ucast_dpu_sign;
	u8 bss_sta_index;
	u8 bss_dpu_desc_index;
	bool is_data_encrypted;
	/* Rates */
	काष्ठा wcn36xx_hal_supported_rates_v1 supported_rates;

	spinlock_t ampdu_lock;		/* protects next two fields */
	क्रमागत wcn36xx_ampdu_state ampdu_state[16];
	पूर्णांक non_agg_frame_ct;
पूर्ण;
काष्ठा wcn36xx_dxe_ch;
काष्ठा wcn36xx अणु
	काष्ठा ieee80211_hw	*hw;
	काष्ठा device		*dev;
	काष्ठा list_head	vअगर_list;

	स्थिर काष्ठा firmware	*nv;

	u8			fw_revision;
	u8			fw_version;
	u8			fw_minor;
	u8			fw_major;
	u32			fw_feat_caps[WCN36XX_HAL_CAPS_SIZE];
	bool			is_pronto;

	/* extra byte क्रम the शून्य termination */
	u8			crm_version[WCN36XX_HAL_VERSION_LENGTH + 1];
	u8			wlan_version[WCN36XX_HAL_VERSION_LENGTH + 1];

	bool		first_boot;

	/* IRQs */
	पूर्णांक			tx_irq;
	पूर्णांक			rx_irq;
	व्योम __iomem		*ccu_base;
	व्योम __iomem		*dxe_base;

	काष्ठा rpmsg_endpoपूर्णांक	*smd_channel;

	काष्ठा qcom_smem_state  *tx_enable_state;
	अचिन्हित		tx_enable_state_bit;
	काष्ठा qcom_smem_state	*tx_rings_empty_state;
	अचिन्हित		tx_rings_empty_state_bit;

	/* prevents concurrent FW reconfiguration */
	काष्ठा mutex		conf_mutex;

	/*
	 * smd_buf must be रक्षित with smd_mutex to garantee
	 * that all messages are sent one after another
	 */
	u8			*hal_buf;
	माप_प्रकार			hal_rsp_len;
	काष्ठा mutex		hal_mutex;
	काष्ठा completion	hal_rsp_compl;
	काष्ठा workqueue_काष्ठा	*hal_ind_wq;
	काष्ठा work_काष्ठा	hal_ind_work;
	spinlock_t		hal_ind_lock;
	काष्ठा list_head	hal_ind_queue;

	काष्ठा cfg80211_scan_request *scan_req;
	bool			sw_scan;
	u8			sw_scan_opchannel;
	काष्ठा ieee80211_vअगर	*sw_scan_vअगर;
	काष्ठा mutex		scan_lock;
	bool			scan_पातed;

	/* DXE channels */
	काष्ठा wcn36xx_dxe_ch	dxe_tx_l_ch;	/* TX low */
	काष्ठा wcn36xx_dxe_ch	dxe_tx_h_ch;	/* TX high */
	काष्ठा wcn36xx_dxe_ch	dxe_rx_l_ch;	/* RX low */
	काष्ठा wcn36xx_dxe_ch	dxe_rx_h_ch;	/* RX high */

	/* For synchronization of DXE resources from BH, IRQ and WQ contexts */
	spinlock_t	dxe_lock;
	bool                    queues_stopped;

	/* Memory pools */
	काष्ठा wcn36xx_dxe_mem_pool mgmt_mem_pool;
	काष्ठा wcn36xx_dxe_mem_pool data_mem_pool;

	काष्ठा sk_buff		*tx_ack_skb;
	काष्ठा समयr_list	tx_ack_समयr;

	/* RF module */
	अचिन्हित		rf_id;

#अगर_घोषित CONFIG_WCN36XX_DEBUGFS
	/* Debug file प्रणाली entry */
	काष्ठा wcn36xx_dfs_entry    dfs;
#पूर्ण_अगर /* CONFIG_WCN36XX_DEBUGFS */

पूर्ण;

अटल अंतरभूत bool wcn36xx_is_fw_version(काष्ठा wcn36xx *wcn,
					 u8 major,
					 u8 minor,
					 u8 version,
					 u8 revision)
अणु
	वापस (wcn->fw_major == major &&
		wcn->fw_minor == minor &&
		wcn->fw_version == version &&
		wcn->fw_revision == revision);
पूर्ण
व्योम wcn36xx_set_शेष_rates(काष्ठा wcn36xx_hal_supported_rates *rates);
व्योम wcn36xx_set_शेष_rates_v1(काष्ठा wcn36xx_hal_supported_rates_v1 *rates);

अटल अंतरभूत
काष्ठा ieee80211_sta *wcn36xx_priv_to_sta(काष्ठा wcn36xx_sta *sta_priv)
अणु
	वापस container_of((व्योम *)sta_priv, काष्ठा ieee80211_sta, drv_priv);
पूर्ण

अटल अंतरभूत
काष्ठा wcn36xx_vअगर *wcn36xx_vअगर_to_priv(काष्ठा ieee80211_vअगर *vअगर)
अणु
	वापस (काष्ठा wcn36xx_vअगर *) vअगर->drv_priv;
पूर्ण

अटल अंतरभूत
काष्ठा ieee80211_vअगर *wcn36xx_priv_to_vअगर(काष्ठा wcn36xx_vअगर *vअगर_priv)
अणु
	वापस container_of((व्योम *) vअगर_priv, काष्ठा ieee80211_vअगर, drv_priv);
पूर्ण

अटल अंतरभूत
काष्ठा wcn36xx_sta *wcn36xx_sta_to_priv(काष्ठा ieee80211_sta *sta)
अणु
	वापस (काष्ठा wcn36xx_sta *)sta->drv_priv;
पूर्ण

#पूर्ण_अगर	/* _WCN36XX_H_ */
