<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2013  Realtek Corporation.*/

#अगर_अघोषित __RTL92CE_TRX_H__
#घोषणा __RTL92CE_TRX_H__

#घोषणा TX_DESC_SIZE					64
#घोषणा TX_DESC_AGGR_SUBFRAME_SIZE		32

#घोषणा RX_DESC_SIZE					32
#घोषणा RX_DRV_INFO_SIZE_UNIT			8

#घोषणा	TX_DESC_NEXT_DESC_OFFSET		40
#घोषणा USB_HWDESC_HEADER_LEN			32
#घोषणा CRCLENGTH						4

अटल अंतरभूत व्योम set_tx_desc_pkt_size(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc, __val, GENMASK(15, 0));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_offset(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc, __val, GENMASK(23, 16));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_bmc(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc, __val, BIT(24));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_htc(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc, __val, BIT(25));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_last_seg(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc, __val, BIT(26));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_first_seg(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc, __val, BIT(27));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_linip(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc, __val, BIT(28));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_own(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc, __val, BIT(31));
पूर्ण

अटल अंतरभूत पूर्णांक get_tx_desc_own(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc), BIT(31));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_macid(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc + 1, __val, GENMASK(5, 0));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_queue_sel(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc + 1, __val, GENMASK(12, 8));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_rate_id(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc + 1, __val, GENMASK(19, 16));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_nav_use_hdr(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc + 1, __val, BIT(20));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_sec_type(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc + 1, __val, GENMASK(23, 22));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_pkt_offset(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc + 1, __val, GENMASK(30, 26));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_agg_enable(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc + 2, __val, BIT(12));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_rdg_enable(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc + 2, __val, BIT(13));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_more_frag(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc + 2, __val, BIT(17));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_ampdu_density(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc + 2, __val, GENMASK(22, 20));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_antsel_a(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc + 2, __val, BIT(24));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_antsel_b(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc + 2, __val, BIT(25));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_seq(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc + 3, __val, GENMASK(27, 16));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_hwseq_en(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc + 3, __val, BIT(31));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_rts_rate(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc + 4, __val, GENMASK(4, 0));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_qos(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc + 4, __val, BIT(6));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_use_rate(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc + 4, __val, BIT(8));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_disable_fb(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc + 4, __val, BIT(10));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_cts2self(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc + 4, __val, BIT(11));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_rts_enable(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc + 4, __val, BIT(12));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_hw_rts_enable(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc + 4, __val, BIT(13));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_tx_sub_carrier(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc + 4, __val, GENMASK(21, 20));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_tx_stbc(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc + 4, __val, GENMASK(23, 22));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_data_bw(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc + 4, __val, BIT(25));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_rts_लघु(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc + 4, __val, BIT(26));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_rts_bw(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc + 4, __val, BIT(27));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_rts_sc(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc + 4, __val, GENMASK(29, 28));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_rts_stbc(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc + 4, __val, GENMASK(31, 30));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_tx_rate(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc + 5, __val, GENMASK(5, 0));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_data_लघुgi(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc + 5, __val, BIT(6));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_data_rate_fb_limit(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc + 5, __val, GENMASK(12, 8));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_rts_rate_fb_limit(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc + 5, __val, GENMASK(16, 13));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_max_agg_num(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc + 6, __val, GENMASK(15, 11));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_antsel_c(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc + 7, __val, BIT(29));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_tx_buffer_size(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc + 7, __val, GENMASK(15, 0));
पूर्ण

अटल अंतरभूत पूर्णांक get_tx_desc_tx_buffer_size(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc + 7), GENMASK(15, 0));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_tx_buffer_address(__le32 *__pdesc, u32 __val)
अणु
	*(__pdesc + 8) = cpu_to_le32(__val);
पूर्ण

अटल अंतरभूत u32 get_tx_desc_tx_buffer_address(__le32 *__pdesc)
अणु
	वापस le32_to_cpu(*(__pdesc + 8));
पूर्ण

अटल अंतरभूत व्योम set_tx_desc_next_desc_address(__le32 *__pdesc, u32 __val)
अणु
	*(__pdesc + 10) = cpu_to_le32(__val);
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_desc_pkt_len(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc), GENMASK(13, 0));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_desc_crc32(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc), BIT(14));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_desc_icv(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc), BIT(15));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_desc_drv_info_size(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc), GENMASK(19, 16));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_desc_security(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc), GENMASK(22, 20));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_desc_qos(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc), BIT(23));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_desc_shअगरt(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc), GENMASK(25, 24));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_desc_physt(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc), BIT(26));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_desc_swdec(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc), BIT(27));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_desc_ls(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc), BIT(28));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_desc_fs(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc), BIT(29));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_desc_eor(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc), BIT(30));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_desc_own(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc), BIT(31));
पूर्ण

अटल अंतरभूत व्योम set_rx_desc_pkt_len(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc, __val, GENMASK(13, 0));
पूर्ण

अटल अंतरभूत व्योम set_rx_desc_eor(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc, __val, BIT(30));
पूर्ण

अटल अंतरभूत व्योम set_rx_desc_own(__le32 *__pdesc, u32 __val)
अणु
	le32p_replace_bits(__pdesc, __val, BIT(31));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_desc_macid(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc + 1), GENMASK(5, 0));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_desc_paggr(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc + 1), BIT(14));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_desc_faggr(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc + 1), BIT(15));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_desc_a1_fit(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc + 1), GENMASK(19, 16));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_desc_a2_fit(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc + 1), GENMASK(23, 20));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_desc_pam(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc + 1), BIT(24));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_desc_pwr(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc + 1), BIT(25));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_desc_md(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc + 1), BIT(26));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_desc_mf(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc + 1), BIT(27));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_desc_type(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc + 1), GENMASK(29, 28));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_desc_mc(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc + 1), BIT(30));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_desc_bc(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc + 1), BIT(31));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_desc_seq(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc + 2), GENMASK(11, 0));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_desc_frag(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc + 2), GENMASK(15, 12));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_desc_rxmcs(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc + 3), GENMASK(5, 0));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_desc_rxht(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc + 3), BIT(6));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_status_desc_rx_gf(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc + 3), BIT(7));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_desc_splcp(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc + 3), BIT(8));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_desc_bw(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc + 3), BIT(9));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_desc_htc(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc + 3), BIT(10));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_status_desc_eosp(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc + 3), BIT(11));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_status_desc_bssid_fit(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc + 3), GENMASK(13, 12));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_status_desc_rpt_sel(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc + 3), GENMASK(15, 14));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_status_desc_pattern_match(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc + 3), BIT(29));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_status_desc_unicast_match(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc + 3), BIT(30));
पूर्ण

अटल अंतरभूत पूर्णांक get_rx_status_desc_magic_match(__le32 *__pdesc)
अणु
	वापस le32_get_bits(*(__pdesc + 3), BIT(31));
पूर्ण

अटल अंतरभूत u32 get_rx_desc_iv1(__le32 *__pdesc)
अणु
	वापस le32_to_cpu(*(__pdesc + 4));
पूर्ण

अटल अंतरभूत u32 get_rx_desc_tsfl(__le32 *__pdesc)
अणु
	वापस le32_to_cpu(*(__pdesc + 5));
पूर्ण

अटल अंतरभूत u32 get_rx_desc_buff_addr(__le32 *__pdesc)
अणु
	वापस le32_to_cpu(*(__pdesc + 6));
पूर्ण

अटल अंतरभूत u32 get_rx_desc_buff_addr64(__le32 *__pdesc)
अणु
	वापस le32_to_cpu(*(__pdesc + 7));
पूर्ण

अटल अंतरभूत व्योम set_rx_desc_buff_addr(__le32 *__pdesc, u32 __val)
अणु
	*(__pdesc + 6) = cpu_to_le32(__val);
पूर्ण

अटल अंतरभूत व्योम set_rx_desc_buff_addr64(__le32 *__pdesc, u32 __val)
अणु
	*(__pdesc + 7) = cpu_to_le32(__val);
पूर्ण

/* TX report 2 क्रमmat in Rx desc*/

अटल अंतरभूत पूर्णांक get_rx_rpt2_desc_pkt_len(__le32 *__status)
अणु
	वापस le32_get_bits(*(__status), GENMASK(8, 0));
पूर्ण

अटल अंतरभूत u32 get_rx_rpt2_desc_macid_valid_1(__le32 *__status)
अणु
	वापस le32_to_cpu(*(__status + 4));
पूर्ण

अटल अंतरभूत u32 get_rx_rpt2_desc_macid_valid_2(__le32 *__status)
अणु
	वापस le32_to_cpu(*(__status + 5));
पूर्ण

अटल अंतरभूत व्योम set_earlymode_pktnum(__le32 *__paddr, u32 __value)
अणु
	le32p_replace_bits(__paddr, __value, GENMASK(3, 0));
पूर्ण

अटल अंतरभूत व्योम set_earlymode_len0(__le32 *__paddr, u32 __value)
अणु
	le32p_replace_bits(__paddr, __value, GENMASK(15, 4));
पूर्ण

अटल अंतरभूत व्योम set_earlymode_len1(__le32 *__paddr, u32 __value)
अणु
	le32p_replace_bits(__paddr, __value, GENMASK(27, 16));
पूर्ण

अटल अंतरभूत व्योम set_earlymode_len2_1(__le32 *__paddr, u32 __value)
अणु
	le32p_replace_bits(__paddr, __value, GENMASK(31, 28));
पूर्ण

अटल अंतरभूत व्योम set_earlymode_len2_2(__le32 *__paddr, u32 __value)
अणु
	le32p_replace_bits(__paddr + 1, __value, GENMASK(7, 0));
पूर्ण

अटल अंतरभूत व्योम set_earlymode_len3(__le32 *__paddr, u32 __value)
अणु
	le32p_replace_bits(__paddr + 1, __value, GENMASK(19, 8));
पूर्ण

अटल अंतरभूत व्योम set_earlymode_len4(__le32 *__paddr, u32 __value)
अणु
	le32p_replace_bits(__paddr + 1, __value, GENMASK(31, 20));
पूर्ण

अटल अंतरभूत व्योम clear_pci_tx_desc_content(__le32 *__pdesc, पूर्णांक _size)
अणु
	अगर (_size > TX_DESC_NEXT_DESC_OFFSET)
		स_रखो(__pdesc, 0, TX_DESC_NEXT_DESC_OFFSET);
	अन्यथा
		स_रखो(__pdesc, 0, _size);
पूर्ण

#घोषणा RTL8188_RX_HAL_IS_CCK_RATE(rxmcs)\
	(rxmcs == DESC92C_RATE1M ||\
	 rxmcs == DESC92C_RATE2M ||\
	 rxmcs == DESC92C_RATE5_5M ||\
	 rxmcs == DESC92C_RATE11M)

काष्ठा phy_status_rpt अणु
	u8	padding[2];
	u8	ch_corr[2];
	u8	cck_sig_qual_ofdm_pwdb_all;
	u8	cck_agc_rpt_ofdm_cfosho_a;
	u8	cck_rpt_b_ofdm_cfosho_b;
	u8	rsvd_1;/* ch_corr_msb; */
	u8	noise_घातer_db_msb;
	u8	path_cfotail[2];
	u8	pcts_mask[2];
	u8	stream_rxevm[2];
	u8	path_rxsnr[2];
	u8	noise_घातer_db_lsb;
	u8	rsvd_2[3];
	u8	stream_csi[2];
	u8	stream_target_csi[2];
	u8	sig_evm;
	u8	rsvd_3;
#अगर defined(__LITTLE_ENDIAN)
	u8	antsel_rx_keep_2:1;	/*ex_पूर्णांकf_flg:1;*/
	u8	sgi_en:1;
	u8	rxsc:2;
	u8	idle_दीर्घ:1;
	u8	r_ant_train_en:1;
	u8	ant_sel_b:1;
	u8	ant_sel:1;
#अन्यथा	/* __BIG_ENDIAN	*/
	u8	ant_sel:1;
	u8	ant_sel_b:1;
	u8	r_ant_train_en:1;
	u8	idle_दीर्घ:1;
	u8	rxsc:2;
	u8	sgi_en:1;
	u8	antsel_rx_keep_2:1;	/*ex_पूर्णांकf_flg:1;*/
#पूर्ण_अगर
पूर्ण __packed;

काष्ठा rx_fwinfo_88e अणु
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

काष्ठा tx_desc_88e अणु
	u32 pktsize:16;
	u32 offset:8;
	u32 bmc:1;
	u32 htc:1;
	u32 lastseg:1;
	u32 firstseg:1;
	u32 linip:1;
	u32 noacm:1;
	u32 gf:1;
	u32 own:1;

	u32 macid:6;
	u32 rsvd0:2;
	u32 queuesel:5;
	u32 rd_nav_ext:1;
	u32 lsig_txop_en:1;
	u32 pअगरs:1;
	u32 rateid:4;
	u32 nav_usehdr:1;
	u32 en_descid:1;
	u32 sectype:2;
	u32 pktoffset:8;

	u32 rts_rc:6;
	u32 data_rc:6;
	u32 agg_en:1;
	u32 rdg_en:1;
	u32 bar_retryht:2;
	u32 agg_अवरोध:1;
	u32 morefrag:1;
	u32 raw:1;
	u32 ccx:1;
	u32 ampdudensity:3;
	u32 bt_पूर्णांक:1;
	u32 ant_sela:1;
	u32 ant_selb:1;
	u32 txant_cck:2;
	u32 txant_l:2;
	u32 txant_ht:2;

	u32 nextheadpage:8;
	u32 tailpage:8;
	u32 seq:12;
	u32 cpu_handle:1;
	u32 tag1:1;
	u32 trigger_पूर्णांक:1;
	u32 hwseq_en:1;

	u32 rtsrate:5;
	u32 apdcfe:1;
	u32 qos:1;
	u32 hwseq_ssn:1;
	u32 userrate:1;
	u32 dis_rtsfb:1;
	u32 dis_datafb:1;
	u32 cts2self:1;
	u32 rts_en:1;
	u32 hwrts_en:1;
	u32 portid:1;
	u32 pwr_status:3;
	u32 रुकोdcts:1;
	u32 cts2ap_en:1;
	u32 txsc:2;
	u32 stbc:2;
	u32 txलघु:1;
	u32 txbw:1;
	u32 rtsलघु:1;
	u32 rtsbw:1;
	u32 rtssc:2;
	u32 rtsstbc:2;

	u32 txrate:6;
	u32 लघुgi:1;
	u32 ccxt:1;
	u32 txrate_fb_lmt:5;
	u32 rtsrate_fb_lmt:4;
	u32 retrylmt_en:1;
	u32 txretrylmt:6;
	u32 usb_txaggnum:8;

	u32 txagca:5;
	u32 txagcb:5;
	u32 usemaxlen:1;
	u32 maxaggnum:5;
	u32 mcsg1maxlen:4;
	u32 mcsg2maxlen:4;
	u32 mcsg3maxlen:4;
	u32 mcs7sgimaxlen:4;

	u32 txbuffersize:16;
	u32 sw_offset30:8;
	u32 sw_offset31:4;
	u32 rsvd1:1;
	u32 antsel_c:1;
	u32 null_0:1;
	u32 null_1:1;

	u32 txbuffaddr;
	u32 txbufferaddr64;
	u32 nextdescaddress;
	u32 nextdescaddress64;

	u32 reserve_pass_pcie_mm_limit[4];
पूर्ण __packed;

काष्ठा rx_desc_88e अणु
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

	u32 macid:6;
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

	u32 seq:12;
	u32 frag:4;
	u32 nextpktlen:14;
	u32 nextind:1;
	u32 rsvd:1;

	u32 rxmcs:6;
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

	u32 iv1;

	u32 tsfl;

	u32 bufferaddress;
	u32 bufferaddress64;

पूर्ण __packed;

व्योम rtl88ee_tx_fill_desc(काष्ठा ieee80211_hw *hw,
			  काष्ठा ieee80211_hdr *hdr, u8 *pdesc_tx,
			  u8 *txbd, काष्ठा ieee80211_tx_info *info,
			  काष्ठा ieee80211_sta *sta,
			  काष्ठा sk_buff *skb,
			  u8 hw_queue, काष्ठा rtl_tcb_desc *ptcb_desc);
bool rtl88ee_rx_query_desc(काष्ठा ieee80211_hw *hw,
			   काष्ठा rtl_stats *status,
			   काष्ठा ieee80211_rx_status *rx_status,
			   u8 *pdesc, काष्ठा sk_buff *skb);
व्योम rtl88ee_set_desc(काष्ठा ieee80211_hw *hw, u8 *pdesc,
		      bool istx, u8 desc_name, u8 *val);
u64 rtl88ee_get_desc(काष्ठा ieee80211_hw *hw,
		     u8 *pdesc, bool istx, u8 desc_name);
bool rtl88ee_is_tx_desc_बंदd(काष्ठा ieee80211_hw *hw,
			       u8 hw_queue, u16 index);
व्योम rtl88ee_tx_polling(काष्ठा ieee80211_hw *hw, u8 hw_queue);
व्योम rtl88ee_tx_fill_cmddesc(काष्ठा ieee80211_hw *hw, u8 *pdesc,
			     bool firstseg, bool lastseg,
			     काष्ठा sk_buff *skb);
#पूर्ण_अगर
