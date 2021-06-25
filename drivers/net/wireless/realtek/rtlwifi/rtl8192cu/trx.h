<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#अगर_अघोषित __RTL92CU_TRX_H__
#घोषणा __RTL92CU_TRX_H__

#घोषणा RTL92C_USB_BULK_IN_NUM			1
#घोषणा RTL92C_NUM_RX_URBS			8
#घोषणा RTL92C_NUM_TX_URBS			32

#घोषणा RTL92C_SIZE_MAX_RX_BUFFER		15360   /* 8192 */
#घोषणा RX_DRV_INFO_SIZE_UNIT			8

#घोषणा RTL_AGG_ON				1

क्रमागत usb_rx_agg_mode अणु
	USB_RX_AGG_DISABLE,
	USB_RX_AGG_DMA,
	USB_RX_AGG_USB,
	USB_RX_AGG_DMA_USB
पूर्ण;

#घोषणा TX_SELE_HQ				BIT(0)	/* High Queue */
#घोषणा TX_SELE_LQ				BIT(1)	/* Low Queue */
#घोषणा TX_SELE_NQ				BIT(2)	/* Normal Queue */

#घोषणा RTL_USB_TX_AGG_NUM_DESC			5

#घोषणा RTL_USB_RX_AGG_PAGE_NUM			4
#घोषणा RTL_USB_RX_AGG_PAGE_TIMEOUT		3

#घोषणा RTL_USB_RX_AGG_BLOCK_NUM		5
#घोषणा RTL_USB_RX_AGG_BLOCK_TIMEOUT		3

/*======================== rx status =========================================*/

काष्ठा rx_drv_info_92c अणु
	/*
	 * Driver info contain PHY status and other variabel size info
	 * PHY Status content as below
	 */

	/* DWORD 0 */
	u8 gain_trsw[4];

	/* DWORD 1 */
	u8 pwdb_all;
	u8 cfosho[4];

	/* DWORD 2 */
	u8 cfotail[4];

	/* DWORD 3 */
	s8 rxevm[2];
	s8 rxsnr[4];

	/* DWORD 4 */
	u8 pdsnr[2];

	/* DWORD 5 */
	u8 csi_current[2];
	u8 csi_target[2];

	/* DWORD 6 */
	u8 sigevm;
	u8 max_ex_pwr;
	u8 ex_पूर्णांकf_flag:1;
	u8 sgi_en:1;
	u8 rxsc:2;
	u8 reserve:4;
पूर्ण __packed;

/* macros to पढ़ो various fields in RX descriptor */

/* DWORD 0 */
अटल अंतरभूत u32 get_rx_desc_pkt_len(__le32 *__rxdesc)
अणु
	वापस le32_get_bits(*__rxdesc, GENMASK(13, 0));
पूर्ण

अटल अंतरभूत u32 get_rx_desc_crc32(__le32 *__rxdesc)
अणु
	वापस le32_get_bits(*__rxdesc, BIT(14));
पूर्ण

अटल अंतरभूत u32 get_rx_desc_icv(__le32 *__rxdesc)
अणु
	वापस le32_get_bits(*__rxdesc, BIT(15));
पूर्ण

अटल अंतरभूत u32 get_rx_desc_drvinfo_size(__le32 *__rxdesc)
अणु
	वापस le32_get_bits(*__rxdesc, GENMASK(19, 16));
पूर्ण

अटल अंतरभूत u32 get_rx_desc_shअगरt(__le32 *__rxdesc)
अणु
	वापस le32_get_bits(*__rxdesc, GENMASK(25, 24));
पूर्ण

अटल अंतरभूत u32 get_rx_desc_phy_status(__le32 *__rxdesc)
अणु
	वापस le32_get_bits(*__rxdesc, BIT(26));
पूर्ण

अटल अंतरभूत u32 get_rx_desc_swdec(__le32 *__rxdesc)
अणु
	वापस le32_get_bits(*__rxdesc, BIT(27));
पूर्ण


/* DWORD 1 */
अटल अंतरभूत u32 get_rx_desc_paggr(__le32 *__rxdesc)
अणु
	वापस le32_get_bits(*(__rxdesc + 1), BIT(14));
पूर्ण

अटल अंतरभूत u32 get_rx_desc_faggr(__le32 *__rxdesc)
अणु
	वापस le32_get_bits(*(__rxdesc + 1), BIT(15));
पूर्ण


/* DWORD 3 */
अटल अंतरभूत u32 get_rx_desc_rx_mcs(__le32 *__rxdesc)
अणु
	वापस le32_get_bits(*(__rxdesc + 3), GENMASK(5, 0));
पूर्ण

अटल अंतरभूत u32 get_rx_desc_rx_ht(__le32 *__rxdesc)
अणु
	वापस le32_get_bits(*(__rxdesc + 3), BIT(6));
पूर्ण

अटल अंतरभूत u32 get_rx_desc_splcp(__le32 *__rxdesc)
अणु
	वापस le32_get_bits(*(__rxdesc + 3), BIT(8));
पूर्ण

अटल अंतरभूत u32 get_rx_desc_bw(__le32 *__rxdesc)
अणु
	वापस le32_get_bits(*(__rxdesc + 3), BIT(9));
पूर्ण


/* DWORD 5 */
अटल अंतरभूत u32 get_rx_desc_tsfl(__le32 *__rxdesc)
अणु
	वापस le32_to_cpu(*((__rxdesc + 5)));
पूर्ण


/*======================= tx desc ============================================*/

/* macros to set various fields in TX descriptor */

/* Dword 0 */
अटल अंतरभूत व्योम set_tx_desc_pkt_size(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits(__txdesc, __value, GENMASK(15, 0));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_offset(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits(__txdesc, __value, GENMASK(23, 16));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_bmc(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits(__txdesc, __value, BIT(24));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_htc(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits(__txdesc, __value, BIT(25));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_last_seg(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits(__txdesc, __value, BIT(26));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_first_seg(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits(__txdesc, __value, BIT(27));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_linip(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits(__txdesc, __value, BIT(28));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_own(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits(__txdesc, __value, BIT(31));
पूर्ण


/* Dword 1 */
अटल अंतरभूत व्योम set_tx_desc_macid(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits((__txdesc + 1), __value, GENMASK(4, 0));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_agg_enable(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits((__txdesc + 1), __value, BIT(5));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_agg_अवरोध(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits((__txdesc + 1), __value, BIT(6));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_rdg_enable(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits((__txdesc + 1), __value, BIT(7));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_queue_sel(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits((__txdesc + 1), __value, GENMASK(12, 8));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_rate_id(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits((__txdesc + 1), __value, GENMASK(19, 16));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_nav_use_hdr(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits((__txdesc + 1), __value, BIT(20));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_sec_type(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits((__txdesc + 1), __value, GENMASK(23, 22));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_pkt_offset(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits((__txdesc + 1), __value, GENMASK(30, 26));
पूर्ण


/* Dword 2 */
अटल अंतरभूत व्योम set_tx_desc_more_frag(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits((__txdesc + 2), __value, BIT(17));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_ampdu_density(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits((__txdesc + 2), __value, GENMASK(22, 20));
पूर्ण


/* Dword 3 */
अटल अंतरभूत व्योम set_tx_desc_seq(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits((__txdesc + 3), __value, GENMASK(27, 16));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_pkt_id(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits((__txdesc + 3), __value, GENMASK(31, 28));
पूर्ण


/* Dword 4 */
अटल अंतरभूत व्योम set_tx_desc_rts_rate(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits((__txdesc + 4), __value, GENMASK(4, 0));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_qos(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits((__txdesc + 4), __value, BIT(6));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_hwseq_en(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits((__txdesc + 4), __value, BIT(7));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_use_rate(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits((__txdesc + 4), __value, BIT(8));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_disable_fb(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits((__txdesc + 4), __value, BIT(10));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_cts2self(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits((__txdesc + 4), __value, BIT(11));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_rts_enable(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits((__txdesc + 4), __value, BIT(12));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_hw_rts_enable(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits((__txdesc + 4), __value, BIT(13));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_data_sc(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits((__txdesc + 4), __value, GENMASK(21, 20));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_data_bw(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits((__txdesc + 4), __value, BIT(25));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_rts_लघु(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits((__txdesc + 4), __value, BIT(26));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_rts_bw(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits((__txdesc + 4), __value, BIT(27));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_rts_sc(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits((__txdesc + 4), __value, GENMASK(29, 28));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_rts_stbc(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits((__txdesc + 4), __value, GENMASK(31, 30));
पूर्ण


/* Dword 5 */
अटल अंतरभूत व्योम set_tx_desc_tx_rate(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits((__pdesc + 5), __val, GENMASK(5, 0));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_data_लघुgi(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits((__pdesc + 5), __val, BIT(6));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_data_rate_fb_limit(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits((__txdesc + 5), __value, GENMASK(12, 8));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_rts_rate_fb_limit(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits((__txdesc + 5), __value, GENMASK(16, 13));
पूर्ण


/* Dword 6 */
अटल अंतरभूत व्योम set_tx_desc_max_agg_num(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits((__txdesc + 6), __value, GENMASK(15, 11));
पूर्ण


/* Dword 7 */
अटल अंतरभूत व्योम set_tx_desc_tx_desc_checksum(__le32 *__txdesc, u32 __value)
अणु
	le32p_replace_bits((__txdesc + 7), __value, GENMASK(15, 0));
पूर्ण


पूर्णांक  rtl8192cu_endpoपूर्णांक_mapping(काष्ठा ieee80211_hw *hw);
u16 rtl8192cu_mq_to_hwq(__le16 fc, u16 mac80211_queue_index);
bool rtl92cu_rx_query_desc(काष्ठा ieee80211_hw *hw,
			   काष्ठा rtl_stats *stats,
			   काष्ठा ieee80211_rx_status *rx_status,
			   u8 *p_desc, काष्ठा sk_buff *skb);
व्योम  rtl8192cu_rx_hdl(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff * skb);
व्योम rtl8192c_tx_cleanup(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff  *skb);
पूर्णांक rtl8192c_tx_post_hdl(काष्ठा ieee80211_hw *hw, काष्ठा urb *urb,
			 काष्ठा sk_buff *skb);
काष्ठा sk_buff *rtl8192c_tx_aggregate_hdl(काष्ठा ieee80211_hw *,
					   काष्ठा sk_buff_head *);
व्योम rtl92cu_tx_fill_desc(काष्ठा ieee80211_hw *hw,
			  काष्ठा ieee80211_hdr *hdr, u8 *pdesc_tx,
			  u8 *pbd_desc_tx, काष्ठा ieee80211_tx_info *info,
			  काष्ठा ieee80211_sta *sta,
			  काष्ठा sk_buff *skb,
			  u8 queue_index,
			  काष्ठा rtl_tcb_desc *tcb_desc);
व्योम rtl92cu_fill_fake_txdesc(काष्ठा ieee80211_hw *hw, u8 *pdesc,
			       u32 buffer_len, bool ispspoll);
व्योम rtl92cu_tx_fill_cmddesc(काष्ठा ieee80211_hw *hw,
			     u8 *pdesc, bool b_firstseg,
			     bool b_lastseg, काष्ठा sk_buff *skb);

#पूर्ण_अगर
