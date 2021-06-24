<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 */

#अगर_अघोषित __MT76_H
#घोषणा __MT76_H

#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/leds.h>
#समावेश <linux/usb.h>
#समावेश <linux/average.h>
#समावेश <net/mac80211.h>
#समावेश "util.h"
#समावेश "testmode.h"

#घोषणा MT_MCU_RING_SIZE	32
#घोषणा MT_RX_BUF_SIZE		2048
#घोषणा MT_SKB_HEAD_LEN		128

#घोषणा MT_MAX_NON_AQL_PKT	16
#घोषणा MT_TXQ_FREE_THR		32

#घोषणा MT76_TOKEN_FREE_THR	64

काष्ठा mt76_dev;
काष्ठा mt76_phy;
काष्ठा mt76_wcid;

काष्ठा mt76_reg_pair अणु
	u32 reg;
	u32 value;
पूर्ण;

क्रमागत mt76_bus_type अणु
	MT76_BUS_MMIO,
	MT76_BUS_USB,
	MT76_BUS_SDIO,
पूर्ण;

काष्ठा mt76_bus_ops अणु
	u32 (*rr)(काष्ठा mt76_dev *dev, u32 offset);
	व्योम (*wr)(काष्ठा mt76_dev *dev, u32 offset, u32 val);
	u32 (*rmw)(काष्ठा mt76_dev *dev, u32 offset, u32 mask, u32 val);
	व्योम (*ग_लिखो_copy)(काष्ठा mt76_dev *dev, u32 offset, स्थिर व्योम *data,
			   पूर्णांक len);
	व्योम (*पढ़ो_copy)(काष्ठा mt76_dev *dev, u32 offset, व्योम *data,
			  पूर्णांक len);
	पूर्णांक (*wr_rp)(काष्ठा mt76_dev *dev, u32 base,
		     स्थिर काष्ठा mt76_reg_pair *rp, पूर्णांक len);
	पूर्णांक (*rd_rp)(काष्ठा mt76_dev *dev, u32 base,
		     काष्ठा mt76_reg_pair *rp, पूर्णांक len);
	क्रमागत mt76_bus_type type;
पूर्ण;

#घोषणा mt76_is_usb(dev) ((dev)->bus->type == MT76_BUS_USB)
#घोषणा mt76_is_mmio(dev) ((dev)->bus->type == MT76_BUS_MMIO)
#घोषणा mt76_is_sdio(dev) ((dev)->bus->type == MT76_BUS_SDIO)

क्रमागत mt76_txq_id अणु
	MT_TXQ_VO = IEEE80211_AC_VO,
	MT_TXQ_VI = IEEE80211_AC_VI,
	MT_TXQ_BE = IEEE80211_AC_BE,
	MT_TXQ_BK = IEEE80211_AC_BK,
	MT_TXQ_PSD,
	MT_TXQ_BEACON,
	MT_TXQ_CAB,
	__MT_TXQ_MAX
पूर्ण;

क्रमागत mt76_mcuq_id अणु
	MT_MCUQ_WM,
	MT_MCUQ_WA,
	MT_MCUQ_FWDL,
	__MT_MCUQ_MAX
पूर्ण;

क्रमागत mt76_rxq_id अणु
	MT_RXQ_MAIN,
	MT_RXQ_MCU,
	MT_RXQ_MCU_WA,
	MT_RXQ_EXT,
	MT_RXQ_EXT_WA,
	__MT_RXQ_MAX
पूर्ण;

काष्ठा mt76_queue_buf अणु
	dma_addr_t addr;
	u16 len;
	bool skip_unmap;
पूर्ण;

काष्ठा mt76_tx_info अणु
	काष्ठा mt76_queue_buf buf[32];
	काष्ठा sk_buff *skb;
	पूर्णांक nbuf;
	u32 info;
पूर्ण;

काष्ठा mt76_queue_entry अणु
	जोड़ अणु
		व्योम *buf;
		काष्ठा sk_buff *skb;
	पूर्ण;
	जोड़ अणु
		काष्ठा mt76_txwi_cache *txwi;
		काष्ठा urb *urb;
		पूर्णांक buf_sz;
	पूर्ण;
	u32 dma_addr[2];
	u16 dma_len[2];
	u16 wcid;
	bool skip_buf0:1;
	bool skip_buf1:1;
	bool करोne:1;
पूर्ण;

काष्ठा mt76_queue_regs अणु
	u32 desc_base;
	u32 ring_size;
	u32 cpu_idx;
	u32 dma_idx;
पूर्ण __packed __aligned(4);

काष्ठा mt76_queue अणु
	काष्ठा mt76_queue_regs __iomem *regs;

	spinlock_t lock;
	spinlock_t cleanup_lock;
	काष्ठा mt76_queue_entry *entry;
	काष्ठा mt76_desc *desc;

	u16 first;
	u16 head;
	u16 tail;
	पूर्णांक ndesc;
	पूर्णांक queued;
	पूर्णांक buf_size;
	bool stopped;
	bool blocked;

	u8 buf_offset;
	u8 hw_idx;
	u8 qid;

	dma_addr_t desc_dma;
	काष्ठा sk_buff *rx_head;
	काष्ठा page_frag_cache rx_page;
पूर्ण;

काष्ठा mt76_mcu_ops अणु
	u32 headroom;
	u32 tailroom;

	पूर्णांक (*mcu_send_msg)(काष्ठा mt76_dev *dev, पूर्णांक cmd, स्थिर व्योम *data,
			    पूर्णांक len, bool रुको_resp);
	पूर्णांक (*mcu_skb_send_msg)(काष्ठा mt76_dev *dev, काष्ठा sk_buff *skb,
				पूर्णांक cmd, पूर्णांक *seq);
	पूर्णांक (*mcu_parse_response)(काष्ठा mt76_dev *dev, पूर्णांक cmd,
				  काष्ठा sk_buff *skb, पूर्णांक seq);
	u32 (*mcu_rr)(काष्ठा mt76_dev *dev, u32 offset);
	व्योम (*mcu_wr)(काष्ठा mt76_dev *dev, u32 offset, u32 val);
	पूर्णांक (*mcu_wr_rp)(काष्ठा mt76_dev *dev, u32 base,
			 स्थिर काष्ठा mt76_reg_pair *rp, पूर्णांक len);
	पूर्णांक (*mcu_rd_rp)(काष्ठा mt76_dev *dev, u32 base,
			 काष्ठा mt76_reg_pair *rp, पूर्णांक len);
	पूर्णांक (*mcu_restart)(काष्ठा mt76_dev *dev);
पूर्ण;

काष्ठा mt76_queue_ops अणु
	पूर्णांक (*init)(काष्ठा mt76_dev *dev,
		    पूर्णांक (*poll)(काष्ठा napi_काष्ठा *napi, पूर्णांक budget));

	पूर्णांक (*alloc)(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q,
		     पूर्णांक idx, पूर्णांक n_desc, पूर्णांक bufsize,
		     u32 ring_base);

	पूर्णांक (*tx_queue_skb)(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q,
			    काष्ठा sk_buff *skb, काष्ठा mt76_wcid *wcid,
			    काष्ठा ieee80211_sta *sta);

	पूर्णांक (*tx_queue_skb_raw)(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q,
				काष्ठा sk_buff *skb, u32 tx_info);

	व्योम *(*dequeue)(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q, bool flush,
			 पूर्णांक *len, u32 *info, bool *more);

	व्योम (*rx_reset)(काष्ठा mt76_dev *dev, क्रमागत mt76_rxq_id qid);

	व्योम (*tx_cleanup)(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q,
			   bool flush);

	व्योम (*rx_cleanup)(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q);

	व्योम (*kick)(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q);

	व्योम (*reset_q)(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q);
पूर्ण;

क्रमागत mt76_wcid_flags अणु
	MT_WCID_FLAG_CHECK_PS,
	MT_WCID_FLAG_PS,
	MT_WCID_FLAG_4ADDR,
	MT_WCID_FLAG_HDR_TRANS,
पूर्ण;

#घोषणा MT76_N_WCIDS 288

/* stored in ieee80211_tx_info::hw_queue */
#घोषणा MT_TX_HW_QUEUE_EXT_PHY		BIT(3)

DECLARE_EWMA(संकेत, 10, 8);

#घोषणा MT_WCID_TX_INFO_RATE		GENMASK(15, 0)
#घोषणा MT_WCID_TX_INFO_NSS		GENMASK(17, 16)
#घोषणा MT_WCID_TX_INFO_TXPWR_ADJ	GENMASK(25, 18)
#घोषणा MT_WCID_TX_INFO_SET		BIT(31)

काष्ठा mt76_wcid अणु
	काष्ठा mt76_rx_tid __rcu *aggr[IEEE80211_NUM_TIDS];

	atomic_t non_aql_packets;
	अचिन्हित दीर्घ flags;

	काष्ठा ewma_संकेत rssi;
	पूर्णांक inactive_count;

	u16 idx;
	u8 hw_key_idx;
	u8 hw_key_idx2;

	u8 sta:1;
	u8 ext_phy:1;
	u8 amsdu:1;

	u8 rx_check_pn;
	u8 rx_key_pn[IEEE80211_NUM_TIDS][6];
	u16 cipher;

	u32 tx_info;
	bool sw_iv;

	u8 packet_id;
पूर्ण;

काष्ठा mt76_txq अणु
	काष्ठा mt76_wcid *wcid;

	u16 agg_ssn;
	bool send_bar;
	bool aggr;
पूर्ण;

काष्ठा mt76_txwi_cache अणु
	काष्ठा list_head list;
	dma_addr_t dma_addr;

	काष्ठा sk_buff *skb;
पूर्ण;

काष्ठा mt76_rx_tid अणु
	काष्ठा rcu_head rcu_head;

	काष्ठा mt76_dev *dev;

	spinlock_t lock;
	काष्ठा delayed_work reorder_work;

	u16 head;
	u16 size;
	u16 nframes;

	u8 num;

	u8 started:1, stopped:1, समयr_pending:1;

	काष्ठा sk_buff *reorder_buf[];
पूर्ण;

#घोषणा MT_TX_CB_DMA_DONE		BIT(0)
#घोषणा MT_TX_CB_TXS_DONE		BIT(1)
#घोषणा MT_TX_CB_TXS_FAILED		BIT(2)

#घोषणा MT_PACKET_ID_MASK		GENMASK(6, 0)
#घोषणा MT_PACKET_ID_NO_ACK		0
#घोषणा MT_PACKET_ID_NO_SKB		1
#घोषणा MT_PACKET_ID_FIRST		2
#घोषणा MT_PACKET_ID_HAS_RATE		BIT(7)

#घोषणा MT_TX_STATUS_SKB_TIMEOUT	HZ

काष्ठा mt76_tx_cb अणु
	अचिन्हित दीर्घ jअगरfies;
	u16 wcid;
	u8 pktid;
	u8 flags;
पूर्ण;

क्रमागत अणु
	MT76_STATE_INITIALIZED,
	MT76_STATE_RUNNING,
	MT76_STATE_MCU_RUNNING,
	MT76_SCANNING,
	MT76_HW_SCANNING,
	MT76_HW_SCHED_SCANNING,
	MT76_RESTART,
	MT76_RESET,
	MT76_MCU_RESET,
	MT76_REMOVED,
	MT76_READING_STATS,
	MT76_STATE_POWER_OFF,
	MT76_STATE_SUSPEND,
	MT76_STATE_ROC,
	MT76_STATE_PM,
पूर्ण;

काष्ठा mt76_hw_cap अणु
	bool has_2ghz;
	bool has_5ghz;
पूर्ण;

#घोषणा MT_DRV_TXWI_NO_FREE		BIT(0)
#घोषणा MT_DRV_TX_ALIGNED4_SKBS		BIT(1)
#घोषणा MT_DRV_SW_RX_AIRTIME		BIT(2)
#घोषणा MT_DRV_RX_DMA_HDR		BIT(3)
#घोषणा MT_DRV_HW_MGMT_TXQ		BIT(4)
#घोषणा MT_DRV_AMSDU_OFFLOAD		BIT(5)

काष्ठा mt76_driver_ops अणु
	u32 drv_flags;
	u32 survey_flags;
	u16 txwi_size;
	u16 token_size;
	u8 mcs_rates;

	व्योम (*update_survey)(काष्ठा mt76_dev *dev);

	पूर्णांक (*tx_prepare_skb)(काष्ठा mt76_dev *dev, व्योम *txwi_ptr,
			      क्रमागत mt76_txq_id qid, काष्ठा mt76_wcid *wcid,
			      काष्ठा ieee80211_sta *sta,
			      काष्ठा mt76_tx_info *tx_info);

	व्योम (*tx_complete_skb)(काष्ठा mt76_dev *dev,
				काष्ठा mt76_queue_entry *e);

	bool (*tx_status_data)(काष्ठा mt76_dev *dev, u8 *update);

	व्योम (*rx_skb)(काष्ठा mt76_dev *dev, क्रमागत mt76_rxq_id q,
		       काष्ठा sk_buff *skb);

	व्योम (*rx_poll_complete)(काष्ठा mt76_dev *dev, क्रमागत mt76_rxq_id q);

	व्योम (*sta_ps)(काष्ठा mt76_dev *dev, काष्ठा ieee80211_sta *sta,
		       bool ps);

	पूर्णांक (*sta_add)(काष्ठा mt76_dev *dev, काष्ठा ieee80211_vअगर *vअगर,
		       काष्ठा ieee80211_sta *sta);

	व्योम (*sta_assoc)(काष्ठा mt76_dev *dev, काष्ठा ieee80211_vअगर *vअगर,
			  काष्ठा ieee80211_sta *sta);

	व्योम (*sta_हटाओ)(काष्ठा mt76_dev *dev, काष्ठा ieee80211_vअगर *vअगर,
			   काष्ठा ieee80211_sta *sta);
पूर्ण;

काष्ठा mt76_channel_state अणु
	u64 cc_active;
	u64 cc_busy;
	u64 cc_rx;
	u64 cc_bss_rx;
	u64 cc_tx;

	s8 noise;
पूर्ण;

काष्ठा mt76_sband अणु
	काष्ठा ieee80211_supported_band sband;
	काष्ठा mt76_channel_state *chan;
पूर्ण;

काष्ठा mt76_rate_घातer अणु
	जोड़ अणु
		काष्ठा अणु
			s8 cck[4];
			s8 ofdm[8];
			s8 stbc[10];
			s8 ht[16];
			s8 vht[10];
		पूर्ण;
		s8 all[48];
	पूर्ण;
पूर्ण;

/* addr req mask */
#घोषणा MT_VEND_TYPE_EEPROM	BIT(31)
#घोषणा MT_VEND_TYPE_CFG	BIT(30)
#घोषणा MT_VEND_TYPE_MASK	(MT_VEND_TYPE_EEPROM | MT_VEND_TYPE_CFG)

#घोषणा MT_VEND_ADDR(type, n)	(MT_VEND_TYPE_##type | (n))
क्रमागत mt_venकरोr_req अणु
	MT_VEND_DEV_MODE =	0x1,
	MT_VEND_WRITE =		0x2,
	MT_VEND_POWER_ON =	0x4,
	MT_VEND_MULTI_WRITE =	0x6,
	MT_VEND_MULTI_READ =	0x7,
	MT_VEND_READ_EEPROM =	0x9,
	MT_VEND_WRITE_FCE =	0x42,
	MT_VEND_WRITE_CFG =	0x46,
	MT_VEND_READ_CFG =	0x47,
	MT_VEND_READ_EXT =	0x63,
	MT_VEND_WRITE_EXT =	0x66,
	MT_VEND_FEATURE_SET =	0x91,
पूर्ण;

क्रमागत mt76u_in_ep अणु
	MT_EP_IN_PKT_RX,
	MT_EP_IN_CMD_RESP,
	__MT_EP_IN_MAX,
पूर्ण;

क्रमागत mt76u_out_ep अणु
	MT_EP_OUT_INBAND_CMD,
	MT_EP_OUT_AC_BE,
	MT_EP_OUT_AC_BK,
	MT_EP_OUT_AC_VI,
	MT_EP_OUT_AC_VO,
	MT_EP_OUT_HCCA,
	__MT_EP_OUT_MAX,
पूर्ण;

काष्ठा mt76_mcu अणु
	काष्ठा mutex mutex;
	u32 msg_seq;
	पूर्णांक समयout;

	काष्ठा sk_buff_head res_q;
	रुको_queue_head_t रुको;
पूर्ण;

#घोषणा MT_TX_SG_MAX_SIZE	8
#घोषणा MT_RX_SG_MAX_SIZE	4
#घोषणा MT_NUM_TX_ENTRIES	256
#घोषणा MT_NUM_RX_ENTRIES	128
#घोषणा MCU_RESP_URB_SIZE	1024
काष्ठा mt76_usb अणु
	काष्ठा mutex usb_ctrl_mtx;
	u8 *data;
	u16 data_len;

	काष्ठा mt76_worker status_worker;
	काष्ठा mt76_worker rx_worker;

	काष्ठा work_काष्ठा stat_work;

	u8 out_ep[__MT_EP_OUT_MAX];
	u8 in_ep[__MT_EP_IN_MAX];
	bool sg_en;

	काष्ठा mt76u_mcu अणु
		u8 *data;
		/* multiple पढ़ोs */
		काष्ठा mt76_reg_pair *rp;
		पूर्णांक rp_len;
		u32 base;
		bool burst;
	पूर्ण mcu;
पूर्ण;

#घोषणा MT76S_XMIT_BUF_SZ	(16 * PAGE_SIZE)
काष्ठा mt76_sdio अणु
	काष्ठा mt76_worker txrx_worker;
	काष्ठा mt76_worker status_worker;
	काष्ठा mt76_worker net_worker;

	काष्ठा work_काष्ठा stat_work;

	u8 *xmit_buf[IEEE80211_NUM_ACS + 2];

	काष्ठा sdio_func *func;
	व्योम *पूर्णांकr_data;

	काष्ठा अणु
		पूर्णांक pse_data_quota;
		पूर्णांक ple_data_quota;
		पूर्णांक pse_mcu_quota;
		पूर्णांक deficit;
	पूर्ण sched;
पूर्ण;

काष्ठा mt76_mmio अणु
	व्योम __iomem *regs;
	spinlock_t irq_lock;
	u32 irqmask;
पूर्ण;

काष्ठा mt76_rx_status अणु
	जोड़ अणु
		काष्ठा mt76_wcid *wcid;
		u16 wcid_idx;
	पूर्ण;

	u32 reorder_समय;

	u32 ampdu_ref;
	u32 बारtamp;

	u8 iv[6];

	u8 ext_phy:1;
	u8 aggr:1;
	u8 qos_ctl;
	u16 seqno;

	u16 freq;
	u32 flag;
	u8 enc_flags;
	u8 encoding:2, bw:3, he_ru:3;
	u8 he_gi:2, he_dcm:1;
	u8 amsdu:1, first_amsdu:1, last_amsdu:1;
	u8 rate_idx;
	u8 nss;
	u8 band;
	s8 संकेत;
	u8 chains;
	s8 chain_संकेत[IEEE80211_MAX_CHAINS];
पूर्ण;

काष्ठा mt76_tesपंचांगode_ops अणु
	पूर्णांक (*set_state)(काष्ठा mt76_phy *phy, क्रमागत mt76_tesपंचांगode_state state);
	पूर्णांक (*set_params)(काष्ठा mt76_phy *phy, काष्ठा nlattr **tb,
			  क्रमागत mt76_tesपंचांगode_state new_state);
	पूर्णांक (*dump_stats)(काष्ठा mt76_phy *phy, काष्ठा sk_buff *msg);
पूर्ण;

काष्ठा mt76_tesपंचांगode_data अणु
	क्रमागत mt76_tesपंचांगode_state state;

	u32 param_set[DIV_ROUND_UP(NUM_MT76_TM_ATTRS, 32)];
	काष्ठा sk_buff *tx_skb;

	u32 tx_count;
	u16 tx_mpdu_len;

	u8 tx_rate_mode;
	u8 tx_rate_idx;
	u8 tx_rate_nss;
	u8 tx_rate_sgi;
	u8 tx_rate_ldpc;
	u8 tx_rate_stbc;
	u8 tx_ltf;

	u8 tx_antenna_mask;
	u8 tx_spe_idx;

	u8 tx_duty_cycle;
	u32 tx_समय;
	u32 tx_ipg;

	u32 freq_offset;

	u8 tx_घातer[4];
	u8 tx_घातer_control;

	u32 tx_pending;
	u32 tx_queued;
	u16 tx_queued_limit;
	u32 tx_करोne;
	काष्ठा अणु
		u64 packets[__MT_RXQ_MAX];
		u64 fcs_error[__MT_RXQ_MAX];
	पूर्ण rx_stats;
पूर्ण;

काष्ठा mt76_vअगर अणु
	u8 idx;
	u8 omac_idx;
	u8 band_idx;
	u8 wmm_idx;
	u8 scan_seq_num;
पूर्ण;

काष्ठा mt76_phy अणु
	काष्ठा ieee80211_hw *hw;
	काष्ठा mt76_dev *dev;
	व्योम *priv;

	अचिन्हित दीर्घ state;

	काष्ठा mt76_queue *q_tx[__MT_TXQ_MAX];

	काष्ठा cfg80211_chan_def chandef;
	काष्ठा ieee80211_channel *मुख्य_chan;

	काष्ठा mt76_channel_state *chan_state;
	kसमय_प्रकार survey_समय;

	काष्ठा mt76_hw_cap cap;
	काष्ठा mt76_sband sband_2g;
	काष्ठा mt76_sband sband_5g;

	u8 macaddr[ETH_ALEN];

	पूर्णांक txघातer_cur;
	u8 antenna_mask;
	u16 chainmask;

#अगर_घोषित CONFIG_NL80211_TESTMODE
	काष्ठा mt76_tesपंचांगode_data test;
#पूर्ण_अगर

	काष्ठा delayed_work mac_work;
	u8 mac_work_count;

	काष्ठा अणु
		काष्ठा sk_buff *head;
		काष्ठा sk_buff **tail;
		u16 seqno;
	पूर्ण rx_amsdu[__MT_RXQ_MAX];
पूर्ण;

काष्ठा mt76_dev अणु
	काष्ठा mt76_phy phy; /* must be first */

	काष्ठा mt76_phy *phy2;

	काष्ठा ieee80211_hw *hw;

	spinlock_t lock;
	spinlock_t cc_lock;

	u32 cur_cc_bss_rx;

	काष्ठा mt76_rx_status rx_ampdu_status;
	u32 rx_ampdu_len;
	u32 rx_ampdu_ref;

	काष्ठा mutex mutex;

	स्थिर काष्ठा mt76_bus_ops *bus;
	स्थिर काष्ठा mt76_driver_ops *drv;
	स्थिर काष्ठा mt76_mcu_ops *mcu_ops;
	काष्ठा device *dev;

	काष्ठा mt76_mcu mcu;

	काष्ठा net_device napi_dev;
	काष्ठा net_device tx_napi_dev;
	spinlock_t rx_lock;
	काष्ठा napi_काष्ठा napi[__MT_RXQ_MAX];
	काष्ठा sk_buff_head rx_skb[__MT_RXQ_MAX];

	काष्ठा list_head txwi_cache;
	काष्ठा mt76_queue *q_mcu[__MT_MCUQ_MAX];
	काष्ठा mt76_queue q_rx[__MT_RXQ_MAX];
	स्थिर काष्ठा mt76_queue_ops *queue_ops;
	पूर्णांक tx_dma_idx[4];

	काष्ठा mt76_worker tx_worker;
	काष्ठा napi_काष्ठा tx_napi;

	spinlock_t token_lock;
	काष्ठा idr token;
	पूर्णांक token_count;

	रुको_queue_head_t tx_रुको;
	काष्ठा sk_buff_head status_list;

	u32 wcid_mask[DIV_ROUND_UP(MT76_N_WCIDS, 32)];
	u32 wcid_phy_mask[DIV_ROUND_UP(MT76_N_WCIDS, 32)];

	u32 vअगर_mask;

	काष्ठा mt76_wcid global_wcid;
	काष्ठा mt76_wcid __rcu *wcid[MT76_N_WCIDS];

	u32 rev;

	u32 aggr_stats[32];

	काष्ठा tasklet_काष्ठा pre_tbtt_tasklet;
	पूर्णांक beacon_पूर्णांक;
	u8 beacon_mask;

	काष्ठा debugfs_blob_wrapper eeprom;
	काष्ठा debugfs_blob_wrapper otp;

	काष्ठा mt76_rate_घातer rate_घातer;

	अक्षर alpha2[3];
	क्रमागत nl80211_dfs_regions region;

	u32 debugfs_reg;

	काष्ठा led_classdev led_cdev;
	अक्षर led_name[32];
	bool led_al;
	u8 led_pin;

	u8 csa_complete;

	u32 rxfilter;

#अगर_घोषित CONFIG_NL80211_TESTMODE
	स्थिर काष्ठा mt76_tesपंचांगode_ops *test_ops;
	काष्ठा अणु
		स्थिर अक्षर *name;
		u32 offset;
	पूर्ण test_mtd;
#पूर्ण_अगर
	काष्ठा workqueue_काष्ठा *wq;

	जोड़ अणु
		काष्ठा mt76_mmio mmio;
		काष्ठा mt76_usb usb;
		काष्ठा mt76_sdio sdio;
	पूर्ण;
पूर्ण;

काष्ठा mt76_घातer_limits अणु
	s8 cck[4];
	s8 ofdm[8];
	s8 mcs[4][10];
	s8 ru[7][12];
पूर्ण;

क्रमागत mt76_phy_type अणु
	MT_PHY_TYPE_CCK,
	MT_PHY_TYPE_OFDM,
	MT_PHY_TYPE_HT,
	MT_PHY_TYPE_HT_GF,
	MT_PHY_TYPE_VHT,
	MT_PHY_TYPE_HE_SU = 8,
	MT_PHY_TYPE_HE_EXT_SU,
	MT_PHY_TYPE_HE_TB,
	MT_PHY_TYPE_HE_MU,
पूर्ण;

#घोषणा __mt76_rr(dev, ...)	(dev)->bus->rr((dev), __VA_ARGS__)
#घोषणा __mt76_wr(dev, ...)	(dev)->bus->wr((dev), __VA_ARGS__)
#घोषणा __mt76_rmw(dev, ...)	(dev)->bus->rmw((dev), __VA_ARGS__)
#घोषणा __mt76_wr_copy(dev, ...)	(dev)->bus->ग_लिखो_copy((dev), __VA_ARGS__)
#घोषणा __mt76_rr_copy(dev, ...)	(dev)->bus->पढ़ो_copy((dev), __VA_ARGS__)

#घोषणा __mt76_set(dev, offset, val)	__mt76_rmw(dev, offset, 0, val)
#घोषणा __mt76_clear(dev, offset, val)	__mt76_rmw(dev, offset, val, 0)

#घोषणा mt76_rr(dev, ...)	(dev)->mt76.bus->rr(&((dev)->mt76), __VA_ARGS__)
#घोषणा mt76_wr(dev, ...)	(dev)->mt76.bus->wr(&((dev)->mt76), __VA_ARGS__)
#घोषणा mt76_rmw(dev, ...)	(dev)->mt76.bus->rmw(&((dev)->mt76), __VA_ARGS__)
#घोषणा mt76_wr_copy(dev, ...)	(dev)->mt76.bus->ग_लिखो_copy(&((dev)->mt76), __VA_ARGS__)
#घोषणा mt76_rr_copy(dev, ...)	(dev)->mt76.bus->पढ़ो_copy(&((dev)->mt76), __VA_ARGS__)
#घोषणा mt76_wr_rp(dev, ...)	(dev)->mt76.bus->wr_rp(&((dev)->mt76), __VA_ARGS__)
#घोषणा mt76_rd_rp(dev, ...)	(dev)->mt76.bus->rd_rp(&((dev)->mt76), __VA_ARGS__)


#घोषणा mt76_mcu_restart(dev, ...)	(dev)->mt76.mcu_ops->mcu_restart(&((dev)->mt76))
#घोषणा __mt76_mcu_restart(dev, ...)	(dev)->mcu_ops->mcu_restart((dev))

#घोषणा mt76_set(dev, offset, val)	mt76_rmw(dev, offset, 0, val)
#घोषणा mt76_clear(dev, offset, val)	mt76_rmw(dev, offset, val, 0)

#घोषणा mt76_get_field(_dev, _reg, _field)		\
	FIELD_GET(_field, mt76_rr(dev, _reg))

#घोषणा mt76_rmw_field(_dev, _reg, _field, _val)	\
	mt76_rmw(_dev, _reg, _field, FIELD_PREP(_field, _val))

#घोषणा __mt76_rmw_field(_dev, _reg, _field, _val)	\
	__mt76_rmw(_dev, _reg, _field, FIELD_PREP(_field, _val))

#घोषणा mt76_hw(dev) (dev)->mphy.hw

अटल अंतरभूत काष्ठा ieee80211_hw *
mt76_wcid_hw(काष्ठा mt76_dev *dev, u16 wcid)
अणु
	अगर (wcid <= MT76_N_WCIDS &&
	    mt76_wcid_mask_test(dev->wcid_phy_mask, wcid))
		वापस dev->phy2->hw;

	वापस dev->phy.hw;
पूर्ण

bool __mt76_poll(काष्ठा mt76_dev *dev, u32 offset, u32 mask, u32 val,
		 पूर्णांक समयout);

#घोषणा mt76_poll(dev, ...) __mt76_poll(&((dev)->mt76), __VA_ARGS__)

bool __mt76_poll_msec(काष्ठा mt76_dev *dev, u32 offset, u32 mask, u32 val,
		      पूर्णांक समयout);

#घोषणा mt76_poll_msec(dev, ...) __mt76_poll_msec(&((dev)->mt76), __VA_ARGS__)

व्योम mt76_mmio_init(काष्ठा mt76_dev *dev, व्योम __iomem *regs);
व्योम mt76_pci_disable_aspm(काष्ठा pci_dev *pdev);

अटल अंतरभूत u16 mt76_chip(काष्ठा mt76_dev *dev)
अणु
	वापस dev->rev >> 16;
पूर्ण

अटल अंतरभूत u16 mt76_rev(काष्ठा mt76_dev *dev)
अणु
	वापस dev->rev & 0xffff;
पूर्ण

#घोषणा mt76xx_chip(dev) mt76_chip(&((dev)->mt76))
#घोषणा mt76xx_rev(dev) mt76_rev(&((dev)->mt76))

#घोषणा mt76_init_queues(dev, ...)		(dev)->mt76.queue_ops->init(&((dev)->mt76), __VA_ARGS__)
#घोषणा mt76_queue_alloc(dev, ...)	(dev)->mt76.queue_ops->alloc(&((dev)->mt76), __VA_ARGS__)
#घोषणा mt76_tx_queue_skb_raw(dev, ...)	(dev)->mt76.queue_ops->tx_queue_skb_raw(&((dev)->mt76), __VA_ARGS__)
#घोषणा mt76_tx_queue_skb(dev, ...)	(dev)->mt76.queue_ops->tx_queue_skb(&((dev)->mt76), __VA_ARGS__)
#घोषणा mt76_queue_rx_reset(dev, ...)	(dev)->mt76.queue_ops->rx_reset(&((dev)->mt76), __VA_ARGS__)
#घोषणा mt76_queue_tx_cleanup(dev, ...)	(dev)->mt76.queue_ops->tx_cleanup(&((dev)->mt76), __VA_ARGS__)
#घोषणा mt76_queue_rx_cleanup(dev, ...)	(dev)->mt76.queue_ops->rx_cleanup(&((dev)->mt76), __VA_ARGS__)
#घोषणा mt76_queue_kick(dev, ...)	(dev)->mt76.queue_ops->kick(&((dev)->mt76), __VA_ARGS__)
#घोषणा mt76_queue_reset(dev, ...)	(dev)->mt76.queue_ops->reset_q(&((dev)->mt76), __VA_ARGS__)

#घोषणा mt76_क्रम_each_q_rx(dev, i)	\
	क्रम (i = 0; i < ARRAY_SIZE((dev)->q_rx) && \
		    (dev)->q_rx[i].ndesc; i++)

काष्ठा mt76_dev *mt76_alloc_device(काष्ठा device *pdev, अचिन्हित पूर्णांक size,
				   स्थिर काष्ठा ieee80211_ops *ops,
				   स्थिर काष्ठा mt76_driver_ops *drv_ops);
पूर्णांक mt76_रेजिस्टर_device(काष्ठा mt76_dev *dev, bool vht,
			 काष्ठा ieee80211_rate *rates, पूर्णांक n_rates);
व्योम mt76_unरेजिस्टर_device(काष्ठा mt76_dev *dev);
व्योम mt76_मुक्त_device(काष्ठा mt76_dev *dev);
व्योम mt76_unरेजिस्टर_phy(काष्ठा mt76_phy *phy);

काष्ठा mt76_phy *mt76_alloc_phy(काष्ठा mt76_dev *dev, अचिन्हित पूर्णांक size,
				स्थिर काष्ठा ieee80211_ops *ops);
पूर्णांक mt76_रेजिस्टर_phy(काष्ठा mt76_phy *phy, bool vht,
		      काष्ठा ieee80211_rate *rates, पूर्णांक n_rates);

काष्ठा dentry *mt76_रेजिस्टर_debugfs(काष्ठा mt76_dev *dev);
पूर्णांक mt76_queues_पढ़ो(काष्ठा seq_file *s, व्योम *data);
व्योम mt76_seq_माला_दो_array(काष्ठा seq_file *file, स्थिर अक्षर *str,
			 s8 *val, पूर्णांक len);

पूर्णांक mt76_eeprom_init(काष्ठा mt76_dev *dev, पूर्णांक len);
व्योम mt76_eeprom_override(काष्ठा mt76_phy *phy);
पूर्णांक mt76_get_of_eeprom(काष्ठा mt76_dev *dev, व्योम *data, पूर्णांक offset, पूर्णांक len);

काष्ठा mt76_queue *
mt76_init_queue(काष्ठा mt76_dev *dev, पूर्णांक qid, पूर्णांक idx, पूर्णांक n_desc,
		पूर्णांक ring_base);
अटल अंतरभूत पूर्णांक mt76_init_tx_queue(काष्ठा mt76_phy *phy, पूर्णांक qid, पूर्णांक idx,
				     पूर्णांक n_desc, पूर्णांक ring_base)
अणु
	काष्ठा mt76_queue *q;

	q = mt76_init_queue(phy->dev, qid, idx, n_desc, ring_base);
	अगर (IS_ERR(q))
		वापस PTR_ERR(q);

	q->qid = qid;
	phy->q_tx[qid] = q;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक mt76_init_mcu_queue(काष्ठा mt76_dev *dev, पूर्णांक qid, पूर्णांक idx,
				      पूर्णांक n_desc, पूर्णांक ring_base)
अणु
	काष्ठा mt76_queue *q;

	q = mt76_init_queue(dev, qid, idx, n_desc, ring_base);
	अगर (IS_ERR(q))
		वापस PTR_ERR(q);

	q->qid = __MT_TXQ_MAX + qid;
	dev->q_mcu[qid] = q;

	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा mt76_phy *
mt76_dev_phy(काष्ठा mt76_dev *dev, bool phy_ext)
अणु
	अगर (phy_ext && dev->phy2)
		वापस dev->phy2;
	वापस &dev->phy;
पूर्ण

अटल अंतरभूत काष्ठा ieee80211_hw *
mt76_phy_hw(काष्ठा mt76_dev *dev, bool phy_ext)
अणु
	वापस mt76_dev_phy(dev, phy_ext)->hw;
पूर्ण

अटल अंतरभूत u8 *
mt76_get_txwi_ptr(काष्ठा mt76_dev *dev, काष्ठा mt76_txwi_cache *t)
अणु
	वापस (u8 *)t - dev->drv->txwi_size;
पूर्ण

/* increment with wrap-around */
अटल अंतरभूत पूर्णांक mt76_incr(पूर्णांक val, पूर्णांक size)
अणु
	वापस (val + 1) & (size - 1);
पूर्ण

/* decrement with wrap-around */
अटल अंतरभूत पूर्णांक mt76_decr(पूर्णांक val, पूर्णांक size)
अणु
	वापस (val - 1) & (size - 1);
पूर्ण

u8 mt76_ac_to_hwq(u8 ac);

अटल अंतरभूत काष्ठा ieee80211_txq *
mtxq_to_txq(काष्ठा mt76_txq *mtxq)
अणु
	व्योम *ptr = mtxq;

	वापस container_of(ptr, काष्ठा ieee80211_txq, drv_priv);
पूर्ण

अटल अंतरभूत काष्ठा ieee80211_sta *
wcid_to_sta(काष्ठा mt76_wcid *wcid)
अणु
	व्योम *ptr = wcid;

	अगर (!wcid || !wcid->sta)
		वापस शून्य;

	वापस container_of(ptr, काष्ठा ieee80211_sta, drv_priv);
पूर्ण

अटल अंतरभूत काष्ठा mt76_tx_cb *mt76_tx_skb_cb(काष्ठा sk_buff *skb)
अणु
	BUILD_BUG_ON(माप(काष्ठा mt76_tx_cb) >
		     माप(IEEE80211_SKB_CB(skb)->status.status_driver_data));
	वापस ((व्योम *)IEEE80211_SKB_CB(skb)->status.status_driver_data);
पूर्ण

अटल अंतरभूत व्योम *mt76_skb_get_hdr(काष्ठा sk_buff *skb)
अणु
	काष्ठा mt76_rx_status mstat;
	u8 *data = skb->data;

	/* Alignment concerns */
	BUILD_BUG_ON(माप(काष्ठा ieee80211_radiotap_he) % 4);
	BUILD_BUG_ON(माप(काष्ठा ieee80211_radiotap_he_mu) % 4);

	mstat = *((काष्ठा mt76_rx_status *)skb->cb);

	अगर (mstat.flag & RX_FLAG_RADIOTAP_HE)
		data += माप(काष्ठा ieee80211_radiotap_he);
	अगर (mstat.flag & RX_FLAG_RADIOTAP_HE_MU)
		data += माप(काष्ठा ieee80211_radiotap_he_mu);

	वापस data;
पूर्ण

अटल अंतरभूत व्योम mt76_insert_hdr_pad(काष्ठा sk_buff *skb)
अणु
	पूर्णांक len = ieee80211_get_hdrlen_from_skb(skb);

	अगर (len % 4 == 0)
		वापस;

	skb_push(skb, 2);
	स_हटाओ(skb->data, skb->data + 2, len);

	skb->data[len] = 0;
	skb->data[len + 1] = 0;
पूर्ण

अटल अंतरभूत bool mt76_is_skb_pktid(u8 pktid)
अणु
	अगर (pktid & MT_PACKET_ID_HAS_RATE)
		वापस false;

	वापस pktid >= MT_PACKET_ID_FIRST;
पूर्ण

अटल अंतरभूत u8 mt76_tx_घातer_nss_delta(u8 nss)
अणु
	अटल स्थिर u8 nss_delta[4] = अणु 0, 6, 9, 12 पूर्ण;

	वापस nss_delta[nss - 1];
पूर्ण

अटल अंतरभूत bool mt76_tesपंचांगode_enabled(काष्ठा mt76_phy *phy)
अणु
#अगर_घोषित CONFIG_NL80211_TESTMODE
	वापस phy->test.state != MT76_TM_STATE_OFF;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत bool mt76_is_tesपंचांगode_skb(काष्ठा mt76_dev *dev,
					काष्ठा sk_buff *skb,
					काष्ठा ieee80211_hw **hw)
अणु
#अगर_घोषित CONFIG_NL80211_TESTMODE
	अगर (skb == dev->phy.test.tx_skb)
		*hw = dev->phy.hw;
	अन्यथा अगर (dev->phy2 && skb == dev->phy2->test.tx_skb)
		*hw = dev->phy2->hw;
	अन्यथा
		वापस false;
	वापस true;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

व्योम mt76_rx(काष्ठा mt76_dev *dev, क्रमागत mt76_rxq_id q, काष्ठा sk_buff *skb);
व्योम mt76_tx(काष्ठा mt76_phy *dev, काष्ठा ieee80211_sta *sta,
	     काष्ठा mt76_wcid *wcid, काष्ठा sk_buff *skb);
व्योम mt76_wake_tx_queue(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_txq *txq);
व्योम mt76_stop_tx_queues(काष्ठा mt76_phy *phy, काष्ठा ieee80211_sta *sta,
			 bool send_bar);
व्योम mt76_tx_check_agg_ssn(काष्ठा ieee80211_sta *sta, काष्ठा sk_buff *skb);
व्योम mt76_txq_schedule(काष्ठा mt76_phy *phy, क्रमागत mt76_txq_id qid);
व्योम mt76_txq_schedule_all(काष्ठा mt76_phy *phy);
व्योम mt76_tx_worker_run(काष्ठा mt76_dev *dev);
व्योम mt76_tx_worker(काष्ठा mt76_worker *w);
व्योम mt76_release_buffered_frames(काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_sta *sta,
				  u16 tids, पूर्णांक nframes,
				  क्रमागत ieee80211_frame_release_type reason,
				  bool more_data);
bool mt76_has_tx_pending(काष्ठा mt76_phy *phy);
व्योम mt76_set_channel(काष्ठा mt76_phy *phy);
व्योम mt76_update_survey(काष्ठा mt76_dev *dev);
व्योम mt76_update_survey_active_समय(काष्ठा mt76_phy *phy, kसमय_प्रकार समय);
पूर्णांक mt76_get_survey(काष्ठा ieee80211_hw *hw, पूर्णांक idx,
		    काष्ठा survey_info *survey);
व्योम mt76_set_stream_caps(काष्ठा mt76_phy *phy, bool vht);

पूर्णांक mt76_rx_aggr_start(काष्ठा mt76_dev *dev, काष्ठा mt76_wcid *wcid, u8 tid,
		       u16 ssn, u16 size);
व्योम mt76_rx_aggr_stop(काष्ठा mt76_dev *dev, काष्ठा mt76_wcid *wcid, u8 tid);

व्योम mt76_wcid_key_setup(काष्ठा mt76_dev *dev, काष्ठा mt76_wcid *wcid,
			 काष्ठा ieee80211_key_conf *key);

व्योम mt76_tx_status_lock(काष्ठा mt76_dev *dev, काष्ठा sk_buff_head *list)
			 __acquires(&dev->status_list.lock);
व्योम mt76_tx_status_unlock(काष्ठा mt76_dev *dev, काष्ठा sk_buff_head *list)
			   __releases(&dev->status_list.lock);

पूर्णांक mt76_tx_status_skb_add(काष्ठा mt76_dev *dev, काष्ठा mt76_wcid *wcid,
			   काष्ठा sk_buff *skb);
काष्ठा sk_buff *mt76_tx_status_skb_get(काष्ठा mt76_dev *dev,
				       काष्ठा mt76_wcid *wcid, पूर्णांक pktid,
				       काष्ठा sk_buff_head *list);
व्योम mt76_tx_status_skb_करोne(काष्ठा mt76_dev *dev, काष्ठा sk_buff *skb,
			     काष्ठा sk_buff_head *list);
व्योम mt76_tx_complete_skb(काष्ठा mt76_dev *dev, u16 wcid, काष्ठा sk_buff *skb);
व्योम mt76_tx_status_check(काष्ठा mt76_dev *dev, काष्ठा mt76_wcid *wcid,
			  bool flush);
पूर्णांक mt76_sta_state(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		   काष्ठा ieee80211_sta *sta,
		   क्रमागत ieee80211_sta_state old_state,
		   क्रमागत ieee80211_sta_state new_state);
व्योम __mt76_sta_हटाओ(काष्ठा mt76_dev *dev, काष्ठा ieee80211_vअगर *vअगर,
		       काष्ठा ieee80211_sta *sta);
व्योम mt76_sta_pre_rcu_हटाओ(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			     काष्ठा ieee80211_sta *sta);

पूर्णांक mt76_get_min_avg_rssi(काष्ठा mt76_dev *dev, bool ext_phy);

पूर्णांक mt76_get_txघातer(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		     पूर्णांक *dbm);

व्योम mt76_csa_check(काष्ठा mt76_dev *dev);
व्योम mt76_csa_finish(काष्ठा mt76_dev *dev);

पूर्णांक mt76_get_antenna(काष्ठा ieee80211_hw *hw, u32 *tx_ant, u32 *rx_ant);
पूर्णांक mt76_set_tim(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_sta *sta, bool set);
व्योम mt76_insert_ccmp_hdr(काष्ठा sk_buff *skb, u8 key_id);
पूर्णांक mt76_get_rate(काष्ठा mt76_dev *dev,
		  काष्ठा ieee80211_supported_band *sband,
		  पूर्णांक idx, bool cck);
व्योम mt76_sw_scan(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		  स्थिर u8 *mac);
व्योम mt76_sw_scan_complete(काष्ठा ieee80211_hw *hw,
			   काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक mt76_tesपंचांगode_cmd(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		      व्योम *data, पूर्णांक len);
पूर्णांक mt76_tesपंचांगode_dump(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb,
		       काष्ठा netlink_callback *cb, व्योम *data, पूर्णांक len);
पूर्णांक mt76_tesपंचांगode_set_state(काष्ठा mt76_phy *phy, क्रमागत mt76_tesपंचांगode_state state);
पूर्णांक mt76_tesपंचांगode_alloc_skb(काष्ठा mt76_phy *phy, u32 len);

अटल अंतरभूत व्योम mt76_tesपंचांगode_reset(काष्ठा mt76_phy *phy, bool disable)
अणु
#अगर_घोषित CONFIG_NL80211_TESTMODE
	क्रमागत mt76_tesपंचांगode_state state = MT76_TM_STATE_IDLE;

	अगर (disable || phy->test.state == MT76_TM_STATE_OFF)
		state = MT76_TM_STATE_OFF;

	mt76_tesपंचांगode_set_state(phy, state);
#पूर्ण_अगर
पूर्ण


/* पूर्णांकernal */
अटल अंतरभूत काष्ठा ieee80211_hw *
mt76_tx_status_get_hw(काष्ठा mt76_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_hw *hw = dev->phy.hw;

	अगर ((info->hw_queue & MT_TX_HW_QUEUE_EXT_PHY) && dev->phy2)
		hw = dev->phy2->hw;

	info->hw_queue &= ~MT_TX_HW_QUEUE_EXT_PHY;

	वापस hw;
पूर्ण

व्योम mt76_put_txwi(काष्ठा mt76_dev *dev, काष्ठा mt76_txwi_cache *t);
व्योम mt76_rx_complete(काष्ठा mt76_dev *dev, काष्ठा sk_buff_head *frames,
		      काष्ठा napi_काष्ठा *napi);
व्योम mt76_rx_poll_complete(काष्ठा mt76_dev *dev, क्रमागत mt76_rxq_id q,
			   काष्ठा napi_काष्ठा *napi);
व्योम mt76_rx_aggr_reorder(काष्ठा sk_buff *skb, काष्ठा sk_buff_head *frames);
व्योम mt76_tesपंचांगode_tx_pending(काष्ठा mt76_phy *phy);
व्योम mt76_queue_tx_complete(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q,
			    काष्ठा mt76_queue_entry *e);

/* usb */
अटल अंतरभूत bool mt76u_urb_error(काष्ठा urb *urb)
अणु
	वापस urb->status &&
	       urb->status != -ECONNRESET &&
	       urb->status != -ESHUTDOWN &&
	       urb->status != -ENOENT;
पूर्ण

/* Map hardware queues to usb endpoपूर्णांकs */
अटल अंतरभूत u8 q2ep(u8 qid)
अणु
	/* TODO: take management packets to queue 5 */
	वापस qid + 1;
पूर्ण

अटल अंतरभूत पूर्णांक
mt76u_bulk_msg(काष्ठा mt76_dev *dev, व्योम *data, पूर्णांक len, पूर्णांक *actual_len,
	       पूर्णांक समयout, पूर्णांक ep)
अणु
	काष्ठा usb_पूर्णांकerface *uपूर्णांकf = to_usb_पूर्णांकerface(dev->dev);
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(uपूर्णांकf);
	काष्ठा mt76_usb *usb = &dev->usb;
	अचिन्हित पूर्णांक pipe;

	अगर (actual_len)
		pipe = usb_rcvbulkpipe(udev, usb->in_ep[ep]);
	अन्यथा
		pipe = usb_sndbulkpipe(udev, usb->out_ep[ep]);

	वापस usb_bulk_msg(udev, pipe, data, len, actual_len, समयout);
पूर्ण

पूर्णांक mt76_skb_adjust_pad(काष्ठा sk_buff *skb, पूर्णांक pad);
पूर्णांक mt76u_venकरोr_request(काष्ठा mt76_dev *dev, u8 req,
			 u8 req_type, u16 val, u16 offset,
			 व्योम *buf, माप_प्रकार len);
व्योम mt76u_single_wr(काष्ठा mt76_dev *dev, स्थिर u8 req,
		     स्थिर u16 offset, स्थिर u32 val);
पूर्णांक mt76u_init(काष्ठा mt76_dev *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf,
	       bool ext);
पूर्णांक mt76u_alloc_mcu_queue(काष्ठा mt76_dev *dev);
पूर्णांक mt76u_alloc_queues(काष्ठा mt76_dev *dev);
व्योम mt76u_stop_tx(काष्ठा mt76_dev *dev);
व्योम mt76u_stop_rx(काष्ठा mt76_dev *dev);
पूर्णांक mt76u_resume_rx(काष्ठा mt76_dev *dev);
व्योम mt76u_queues_deinit(काष्ठा mt76_dev *dev);

पूर्णांक mt76s_init(काष्ठा mt76_dev *dev, काष्ठा sdio_func *func,
	       स्थिर काष्ठा mt76_bus_ops *bus_ops);
पूर्णांक mt76s_alloc_queues(काष्ठा mt76_dev *dev);
व्योम mt76s_deinit(काष्ठा mt76_dev *dev);

काष्ठा sk_buff *
mt76_mcu_msg_alloc(काष्ठा mt76_dev *dev, स्थिर व्योम *data,
		   पूर्णांक data_len);
व्योम mt76_mcu_rx_event(काष्ठा mt76_dev *dev, काष्ठा sk_buff *skb);
काष्ठा sk_buff *mt76_mcu_get_response(काष्ठा mt76_dev *dev,
				      अचिन्हित दीर्घ expires);
पूर्णांक mt76_mcu_send_and_get_msg(काष्ठा mt76_dev *dev, पूर्णांक cmd, स्थिर व्योम *data,
			      पूर्णांक len, bool रुको_resp, काष्ठा sk_buff **ret);
पूर्णांक mt76_mcu_skb_send_and_get_msg(काष्ठा mt76_dev *dev, काष्ठा sk_buff *skb,
				  पूर्णांक cmd, bool रुको_resp, काष्ठा sk_buff **ret);
पूर्णांक mt76_mcu_send_firmware(काष्ठा mt76_dev *dev, पूर्णांक cmd, स्थिर व्योम *data,
			   पूर्णांक len);
अटल अंतरभूत पूर्णांक
mt76_mcu_send_msg(काष्ठा mt76_dev *dev, पूर्णांक cmd, स्थिर व्योम *data, पूर्णांक len,
		  bool रुको_resp)
अणु
	वापस mt76_mcu_send_and_get_msg(dev, cmd, data, len, रुको_resp, शून्य);
पूर्ण

अटल अंतरभूत पूर्णांक
mt76_mcu_skb_send_msg(काष्ठा mt76_dev *dev, काष्ठा sk_buff *skb, पूर्णांक cmd,
		      bool रुको_resp)
अणु
	वापस mt76_mcu_skb_send_and_get_msg(dev, skb, cmd, रुको_resp, शून्य);
पूर्ण

व्योम mt76_set_irq_mask(काष्ठा mt76_dev *dev, u32 addr, u32 clear, u32 set);

s8 mt76_get_rate_घातer_limits(काष्ठा mt76_phy *phy,
			      काष्ठा ieee80211_channel *chan,
			      काष्ठा mt76_घातer_limits *dest,
			      s8 target_घातer);

काष्ठा mt76_txwi_cache *
mt76_token_release(काष्ठा mt76_dev *dev, पूर्णांक token, bool *wake);
पूर्णांक mt76_token_consume(काष्ठा mt76_dev *dev, काष्ठा mt76_txwi_cache **ptxwi);
व्योम __mt76_set_tx_blocked(काष्ठा mt76_dev *dev, bool blocked);

अटल अंतरभूत व्योम mt76_set_tx_blocked(काष्ठा mt76_dev *dev, bool blocked)
अणु
	spin_lock_bh(&dev->token_lock);
	__mt76_set_tx_blocked(dev, blocked);
	spin_unlock_bh(&dev->token_lock);
पूर्ण

अटल अंतरभूत पूर्णांक
mt76_token_get(काष्ठा mt76_dev *dev, काष्ठा mt76_txwi_cache **ptxwi)
अणु
	पूर्णांक token;

	spin_lock_bh(&dev->token_lock);
	token = idr_alloc(&dev->token, *ptxwi, 0, dev->drv->token_size,
			  GFP_ATOMIC);
	spin_unlock_bh(&dev->token_lock);

	वापस token;
पूर्ण

अटल अंतरभूत काष्ठा mt76_txwi_cache *
mt76_token_put(काष्ठा mt76_dev *dev, पूर्णांक token)
अणु
	काष्ठा mt76_txwi_cache *txwi;

	spin_lock_bh(&dev->token_lock);
	txwi = idr_हटाओ(&dev->token, token);
	spin_unlock_bh(&dev->token_lock);

	वापस txwi;
पूर्ण
#पूर्ण_अगर
