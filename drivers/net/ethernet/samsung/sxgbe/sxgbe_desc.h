<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* 10G controller driver क्रम Samsung SoCs
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Author: Siva Reddy Kallam <siva.kallam@samsung.com>
 */
#अगर_अघोषित __SXGBE_DESC_H__
#घोषणा __SXGBE_DESC_H__

#घोषणा SXGBE_DESC_SIZE_BYTES	16

/* क्रमward declaration */
काष्ठा sxgbe_extra_stats;

/* Transmit checksum insertion control */
क्रमागत tdes_csum_insertion अणु
	cic_disabled		= 0,	/* Checksum Insertion Control */
	cic_only_ip		= 1,	/* Only IP header */
	/* IP header but pseuकरोheader is not calculated */
	cic_no_pseuकरोheader	= 2,
	cic_full		= 3,	/* IP header and pseuकरोheader */
पूर्ण;

काष्ठा sxgbe_tx_norm_desc अणु
	u64 tdes01; /* buf1 address */
	जोड़ अणु
		/* TX Read-Format Desc 2,3 */
		काष्ठा अणु
			/* TDES2 */
			u32 buf1_size:14;
			u32 vlan_tag_ctl:2;
			u32 buf2_size:14;
			u32 बारपंचांगp_enable:1;
			u32 पूर्णांक_on_com:1;
			/* TDES3 */
			जोड़ अणु
				u16 tcp_payload_len;
				काष्ठा अणु
					u32 total_pkt_len:15;
					u32 reserved1:1;
				पूर्ण pkt_len;
			पूर्ण tx_pkt_len;

			u16 cksum_ctl:2;
			u16 tse_bit:1;
			u16 tcp_hdr_len:4;
			u16 sa_insert_ctl:3;
			u16 crc_pad_ctl:2;
			u16 last_desc:1;
			u16 first_desc:1;
			u16 ctxt_bit:1;
			u16 own_bit:1;
		पूर्ण tx_rd_des23;

		/* tx ग_लिखो back Desc 2,3 */
		काष्ठा अणु
			/* WB TES2 */
			u32 reserved1;
			/* WB TES3 */
			u32 reserved2:31;
			u32 own_bit:1;
		पूर्ण tx_wb_des23;
	पूर्ण tdes23;
पूर्ण;

काष्ठा sxgbe_rx_norm_desc अणु
	जोड़ अणु
		u64 rdes01; /* buf1 address */
		जोड़ अणु
			u32 out_vlan_tag:16;
			u32 in_vlan_tag:16;
			u32 rss_hash;
		पूर्ण rx_wb_des01;
	पूर्ण rdes01;

	जोड़ अणु
		/* RX Read क्रमmat Desc 2,3 */
		काष्ठाअणु
			/* RDES2 */
			u64 buf2_addr:62;
			/* RDES3 */
			u32 पूर्णांक_on_com:1;
			u32 own_bit:1;
		पूर्ण rx_rd_des23;

		/* RX ग_लिखो back */
		काष्ठाअणु
			/* WB RDES2 */
			u32 hdr_len:10;
			u32 rdes2_reserved:2;
			u32 elrd_val:1;
			u32 iovt_sel:1;
			u32 res_pkt:1;
			u32 vlan_filter_match:1;
			u32 sa_filter_fail:1;
			u32 da_filter_fail:1;
			u32 hash_filter_pass:1;
			u32 macaddr_filter_match:8;
			u32 l3_filter_match:1;
			u32 l4_filter_match:1;
			u32 l34_filter_num:3;

			/* WB RDES3 */
			u32 pkt_len:14;
			u32 rdes3_reserved:1;
			u32 err_summary:1;
			u32 err_l2_type:4;
			u32 layer34_pkt_type:4;
			u32 no_coagulation_pkt:1;
			u32 in_seq_pkt:1;
			u32 rss_valid:1;
			u32 context_des_avail:1;
			u32 last_desc:1;
			u32 first_desc:1;
			u32 recv_context_desc:1;
			u32 own_bit:1;
		पूर्ण rx_wb_des23;
	पूर्ण rdes23;
पूर्ण;

/* Context descriptor काष्ठाure */
काष्ठा sxgbe_tx_ctxt_desc अणु
	u32 tstamp_lo;
	u32 tstamp_hi;
	u32 maxseg_size:15;
	u32 reserved1:1;
	u32 ivlan_tag:16;
	u32 vlan_tag:16;
	u32 vltag_valid:1;
	u32 ivlan_tag_valid:1;
	u32 ivlan_tag_ctl:2;
	u32 reserved2:3;
	u32 ctxt_desc_err:1;
	u32 reserved3:2;
	u32 ostc:1;
	u32 tcmssv:1;
	u32 reserved4:2;
	u32 ctxt_bit:1;
	u32 own_bit:1;
पूर्ण;

काष्ठा sxgbe_rx_ctxt_desc अणु
	u32 tstamp_lo;
	u32 tstamp_hi;
	u32 reserved1;
	u32 ptp_msgtype:4;
	u32 tstamp_available:1;
	u32 ptp_rsp_err:1;
	u32 tstamp_dropped:1;
	u32 reserved2:23;
	u32 rx_ctxt_desc:1;
	u32 own_bit:1;
पूर्ण;

काष्ठा sxgbe_desc_ops अणु
	/* DMA TX descriptor ring initialization */
	व्योम (*init_tx_desc)(काष्ठा sxgbe_tx_norm_desc *p);

	/* Invoked by the xmit function to prepare the tx descriptor */
	व्योम (*tx_desc_enable_tse)(काष्ठा sxgbe_tx_norm_desc *p, u8 is_tse,
				   u32 total_hdr_len, u32 tcp_hdr_len,
				   u32 tcp_payload_len);

	/* Assign buffer lengths क्रम descriptor */
	व्योम (*prepare_tx_desc)(काष्ठा sxgbe_tx_norm_desc *p, u8 is_fd,
				पूर्णांक buf1_len, पूर्णांक pkt_len, पूर्णांक cksum);

	/* Set VLAN control inक्रमmation */
	व्योम (*tx_vlanctl_desc)(काष्ठा sxgbe_tx_norm_desc *p, पूर्णांक vlan_ctl);

	/* Set the owner of the descriptor */
	व्योम (*set_tx_owner)(काष्ठा sxgbe_tx_norm_desc *p);

	/* Get the owner of the descriptor */
	पूर्णांक (*get_tx_owner)(काष्ठा sxgbe_tx_norm_desc *p);

	/* Invoked by the xmit function to बंद the tx descriptor */
	व्योम (*बंद_tx_desc)(काष्ठा sxgbe_tx_norm_desc *p);

	/* Clean the tx descriptor as soon as the tx irq is received */
	व्योम (*release_tx_desc)(काष्ठा sxgbe_tx_norm_desc *p);

	/* Clear पूर्णांकerrupt on tx frame completion. When this bit is
	 * set an पूर्णांकerrupt happens as soon as the frame is transmitted
	 */
	व्योम (*clear_tx_ic)(काष्ठा sxgbe_tx_norm_desc *p);

	/* Last tx segment reports the transmit status */
	पूर्णांक (*get_tx_ls)(काष्ठा sxgbe_tx_norm_desc *p);

	/* Get the buffer size from the descriptor */
	पूर्णांक (*get_tx_len)(काष्ठा sxgbe_tx_norm_desc *p);

	/* Set tx बारtamp enable bit */
	व्योम (*tx_enable_tstamp)(काष्ठा sxgbe_tx_norm_desc *p);

	/* get tx बारtamp status */
	पूर्णांक (*get_tx_बारtamp_status)(काष्ठा sxgbe_tx_norm_desc *p);

	/* TX Context Descripto Specअगरic */
	व्योम (*tx_ctxt_desc_set_ctxt)(काष्ठा sxgbe_tx_ctxt_desc *p);

	/* Set the owner of the TX context descriptor */
	व्योम (*tx_ctxt_desc_set_owner)(काष्ठा sxgbe_tx_ctxt_desc *p);

	/* Get the owner of the TX context descriptor */
	पूर्णांक (*get_tx_ctxt_owner)(काष्ठा sxgbe_tx_ctxt_desc *p);

	/* Set TX mss */
	व्योम (*tx_ctxt_desc_set_mss)(काष्ठा sxgbe_tx_ctxt_desc *p, u16 mss);

	/* Set TX mss */
	पूर्णांक (*tx_ctxt_desc_get_mss)(काष्ठा sxgbe_tx_ctxt_desc *p);

	/* Set TX tcmssv */
	व्योम (*tx_ctxt_desc_set_tcmssv)(काष्ठा sxgbe_tx_ctxt_desc *p);

	/* Reset TX ostc */
	व्योम (*tx_ctxt_desc_reset_ostc)(काष्ठा sxgbe_tx_ctxt_desc *p);

	/* Set IVLAN inक्रमmation */
	व्योम (*tx_ctxt_desc_set_ivlantag)(काष्ठा sxgbe_tx_ctxt_desc *p,
					  पूर्णांक is_ivlanvalid, पूर्णांक ivlan_tag,
					  पूर्णांक ivlan_ctl);

	/* Return IVLAN Tag */
	पूर्णांक (*tx_ctxt_desc_get_ivlantag)(काष्ठा sxgbe_tx_ctxt_desc *p);

	/* Set VLAN Tag */
	व्योम (*tx_ctxt_desc_set_vlantag)(काष्ठा sxgbe_tx_ctxt_desc *p,
					 पूर्णांक is_vlanvalid, पूर्णांक vlan_tag);

	/* Return VLAN Tag */
	पूर्णांक (*tx_ctxt_desc_get_vlantag)(काष्ठा sxgbe_tx_ctxt_desc *p);

	/* Set Time stamp */
	व्योम (*tx_ctxt_set_tstamp)(काष्ठा sxgbe_tx_ctxt_desc *p,
				   u8 ostc_enable, u64 tstamp);

	/* Close TX context descriptor */
	व्योम (*बंद_tx_ctxt_desc)(काष्ठा sxgbe_tx_ctxt_desc *p);

	/* WB status of context descriptor */
	पूर्णांक (*get_tx_ctxt_cde)(काष्ठा sxgbe_tx_ctxt_desc *p);

	/* DMA RX descriptor ring initialization */
	व्योम (*init_rx_desc)(काष्ठा sxgbe_rx_norm_desc *p, पूर्णांक disable_rx_ic,
			     पूर्णांक mode, पूर्णांक end);

	/* Get own bit */
	पूर्णांक (*get_rx_owner)(काष्ठा sxgbe_rx_norm_desc *p);

	/* Set own bit */
	व्योम (*set_rx_owner)(काष्ठा sxgbe_rx_norm_desc *p);

	/* Set Interrupt on completion bit */
	व्योम (*set_rx_पूर्णांक_on_com)(काष्ठा sxgbe_rx_norm_desc *p);

	/* Get the receive frame size */
	पूर्णांक (*get_rx_frame_len)(काष्ठा sxgbe_rx_norm_desc *p);

	/* Return first Descriptor status */
	पूर्णांक (*get_rx_fd_status)(काष्ठा sxgbe_rx_norm_desc *p);

	/* Return first Descriptor status */
	पूर्णांक (*get_rx_ld_status)(काष्ठा sxgbe_rx_norm_desc *p);

	/* Return the reception status looking at the RDES1 */
	पूर्णांक (*rx_wbstatus)(काष्ठा sxgbe_rx_norm_desc *p,
			   काष्ठा sxgbe_extra_stats *x, पूर्णांक *checksum);

	/* Get own bit */
	पूर्णांक (*get_rx_ctxt_owner)(काष्ठा sxgbe_rx_ctxt_desc *p);

	/* Set own bit */
	व्योम (*set_rx_ctxt_owner)(काष्ठा sxgbe_rx_ctxt_desc *p);

	/* Return the reception status looking at Context control inक्रमmation */
	व्योम (*rx_ctxt_wbstatus)(काष्ठा sxgbe_rx_ctxt_desc *p,
				 काष्ठा sxgbe_extra_stats *x);

	/* Get rx बारtamp status */
	पूर्णांक (*get_rx_ctxt_tstamp_status)(काष्ठा sxgbe_rx_ctxt_desc *p);

	/* Get बारtamp value क्रम rx, need to check this */
	u64 (*get_बारtamp)(काष्ठा sxgbe_rx_ctxt_desc *p);
पूर्ण;

स्थिर काष्ठा sxgbe_desc_ops *sxgbe_get_desc_ops(व्योम);

#पूर्ण_अगर /* __SXGBE_DESC_H__ */
