<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#अगर_अघोषित __RTL92C_MAC_H__
#घोषणा __RTL92C_MAC_H__

#घोषणा LLT_LAST_ENTRY_OF_TX_PKT_BUFFER		255
#घोषणा DRIVER_EARLY_INT_TIME					0x05
#घोषणा BCN_DMA_ATIME_INT_TIME				0x02

व्योम rtl92c_पढ़ो_chip_version(काष्ठा ieee80211_hw *hw);
bool rtl92c_llt_ग_लिखो(काष्ठा ieee80211_hw *hw, u32 address, u32 data);
bool rtl92c_init_llt_table(काष्ठा ieee80211_hw *hw, u32 boundary);
व्योम rtl92c_set_key(काष्ठा ieee80211_hw *hw, u32 key_index,
		     u8 *p_macaddr, bool is_group, u8 enc_algo,
		     bool is_wepkey, bool clear_all);
व्योम rtl92c_enable_पूर्णांकerrupt(काष्ठा ieee80211_hw *hw);
व्योम rtl92c_disable_पूर्णांकerrupt(काष्ठा ieee80211_hw *hw);
व्योम rtl92c_set_qos(काष्ठा ieee80211_hw *hw, पूर्णांक aci);

/*---------------------------------------------------------------
 *	Hardware init functions
 *---------------------------------------------------------------*/
व्योम rtl92c_init_पूर्णांकerrupt(काष्ठा ieee80211_hw *hw);
व्योम rtl92c_init_driver_info_size(काष्ठा ieee80211_hw *hw, u8 size);

पूर्णांक rtl92c_set_network_type(काष्ठा ieee80211_hw *hw, क्रमागत nl80211_अगरtype type);
व्योम rtl92c_init_network_type(काष्ठा ieee80211_hw *hw);
व्योम rtl92c_init_adaptive_ctrl(काष्ठा ieee80211_hw *hw);
व्योम rtl92c_init_rate_fallback(काष्ठा ieee80211_hw *hw);

व्योम rtl92c_init_edca_param(काष्ठा ieee80211_hw *hw,
							u16 queue,
							u16 txop,
							u8 ecwmax,
							u8 ecwmin,
							u8 aअगरs);

व्योम rtl92c_init_edca(काष्ठा ieee80211_hw *hw);
व्योम rtl92c_init_ampdu_aggregation(काष्ठा ieee80211_hw *hw);
व्योम rtl92c_init_beacon_max_error(काष्ठा ieee80211_hw *hw);
व्योम rtl92c_init_rdg_setting(काष्ठा ieee80211_hw *hw);
व्योम rtl92c_init_retry_function(काष्ठा ieee80211_hw *hw);

व्योम rtl92c_disable_fast_edca(काष्ठा ieee80211_hw *hw);
व्योम rtl92c_set_min_space(काष्ठा ieee80211_hw *hw, bool is2T);

u32 rtl92c_get_txdma_status(काष्ठा ieee80211_hw *hw);

काष्ठा rx_fwinfo_92c अणु
	u8 gain_trsw[4];
	u8 pwdb_all;
	u8 cfosho[4];
	u8 cfotail[4];
	s8 rxevm[2];
	s8 rxsnr[4];
	u8 pdsnr[2];
	u8 csi_current[2];
	u8 csi_target[2];
	u8 sigevm;
	u8 max_ex_pwr;
	u8 ex_पूर्णांकf_flag:1;
	u8 sgi_en:1;
	u8 rxsc:2;
	u8 reserve:4;
पूर्ण __packed;

काष्ठा rx_desc_92c अणु
	u32 length:14;
	u32 crc32:1;
	u32 icverror:1;
	u32 drv_infosize:4;
	u32 security:3;
	u32 qos:1;
	u32 shअगरt:2;
	u32 phystatus:1;
	u32 swdec:1;
	u32 lastseg:1;
	u32 firstseg:1;
	u32 eor:1;
	u32 own:1;
	u32 macid:5;	/* word 1 */
	u32 tid:4;
	u32 hwrsvd:5;
	u32 paggr:1;
	u32 faggr:1;
	u32 a1_fit:4;
	u32 a2_fit:4;
	u32 pam:1;
	u32 pwr:1;
	u32 moredata:1;
	u32 morefrag:1;
	u32 type:2;
	u32 mc:1;
	u32 bc:1;
	u32 seq:12;	/* word 2 */
	u32 frag:4;
	u32 nextpktlen:14;
	u32 nextind:1;
	u32 rsvd:1;
	u32 rxmcs:6;	/* word 3 */
	u32 rxht:1;
	u32 amsdu:1;
	u32 splcp:1;
	u32 bandwidth:1;
	u32 htc:1;
	u32 tcpchk_rpt:1;
	u32 ipcchk_rpt:1;
	u32 tcpchk_valid:1;
	u32 hwpcerr:1;
	u32 hwpcind:1;
	u32 iv0:16;
	u32 iv1;	/* word 4 */
	u32 tsfl;	/* word 5 */
	u32 bufferaddress;	/* word 6 */
	u32 bufferaddress64;	/* word 7 */
पूर्ण __packed;

क्रमागत rtl_desc_qsel rtl92c_map_hwqueue_to_fwqueue(u16 fc,
							  अचिन्हित पूर्णांक
							  skb_queue);
व्योम rtl92c_translate_rx_संकेत_stuff(काष्ठा ieee80211_hw *hw,
				      काष्ठा sk_buff *skb,
				      काष्ठा rtl_stats *pstats,
				      काष्ठा rx_desc_92c *pdesc,
				      काष्ठा rx_fwinfo_92c *p_drvinfo);

/*---------------------------------------------------------------
 *	Card disable functions
 *---------------------------------------------------------------*/

#पूर्ण_अगर
