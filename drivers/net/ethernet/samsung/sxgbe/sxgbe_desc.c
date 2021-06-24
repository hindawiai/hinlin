<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* 10G controller driver क्रम Samsung SoCs
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Author: Siva Reddy Kallam <siva.kallam@samsung.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/bitops.h>
#समावेश <linux/export.h>
#समावेश <linux/पन.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/phy.h>

#समावेश "sxgbe_common.h"
#समावेश "sxgbe_dma.h"
#समावेश "sxgbe_desc.h"

/* DMA TX descriptor ring initialization */
अटल व्योम sxgbe_init_tx_desc(काष्ठा sxgbe_tx_norm_desc *p)
अणु
	p->tdes23.tx_rd_des23.own_bit = 0;
पूर्ण

अटल व्योम sxgbe_tx_desc_enable_tse(काष्ठा sxgbe_tx_norm_desc *p, u8 is_tse,
				     u32 total_hdr_len, u32 tcp_hdr_len,
				     u32 tcp_payload_len)
अणु
	p->tdes23.tx_rd_des23.tse_bit = is_tse;
	p->tdes23.tx_rd_des23.buf1_size = total_hdr_len;
	p->tdes23.tx_rd_des23.tcp_hdr_len = tcp_hdr_len / 4;
	p->tdes23.tx_rd_des23.tx_pkt_len.tcp_payload_len  = tcp_payload_len;
पूर्ण

/* Assign buffer lengths क्रम descriptor */
अटल व्योम sxgbe_prepare_tx_desc(काष्ठा sxgbe_tx_norm_desc *p, u8 is_fd,
				  पूर्णांक buf1_len, पूर्णांक pkt_len, पूर्णांक cksum)
अणु
	p->tdes23.tx_rd_des23.first_desc = is_fd;
	p->tdes23.tx_rd_des23.buf1_size = buf1_len;

	p->tdes23.tx_rd_des23.tx_pkt_len.pkt_len.total_pkt_len = pkt_len;

	अगर (cksum)
		p->tdes23.tx_rd_des23.cksum_ctl = cic_full;
पूर्ण

/* Set VLAN control inक्रमmation */
अटल व्योम sxgbe_tx_vlanctl_desc(काष्ठा sxgbe_tx_norm_desc *p, पूर्णांक vlan_ctl)
अणु
	p->tdes23.tx_rd_des23.vlan_tag_ctl = vlan_ctl;
पूर्ण

/* Set the owner of Normal descriptor */
अटल व्योम sxgbe_set_tx_owner(काष्ठा sxgbe_tx_norm_desc *p)
अणु
	p->tdes23.tx_rd_des23.own_bit = 1;
पूर्ण

/* Get the owner of Normal descriptor */
अटल पूर्णांक sxgbe_get_tx_owner(काष्ठा sxgbe_tx_norm_desc *p)
अणु
	वापस p->tdes23.tx_rd_des23.own_bit;
पूर्ण

/* Invoked by the xmit function to बंद the tx descriptor */
अटल व्योम sxgbe_बंद_tx_desc(काष्ठा sxgbe_tx_norm_desc *p)
अणु
	p->tdes23.tx_rd_des23.last_desc = 1;
	p->tdes23.tx_rd_des23.पूर्णांक_on_com = 1;
पूर्ण

/* Clean the tx descriptor as soon as the tx irq is received */
अटल व्योम sxgbe_release_tx_desc(काष्ठा sxgbe_tx_norm_desc *p)
अणु
	स_रखो(p, 0, माप(*p));
पूर्ण

/* Clear पूर्णांकerrupt on tx frame completion. When this bit is
 * set an पूर्णांकerrupt happens as soon as the frame is transmitted
 */
अटल व्योम sxgbe_clear_tx_ic(काष्ठा sxgbe_tx_norm_desc *p)
अणु
	p->tdes23.tx_rd_des23.पूर्णांक_on_com = 0;
पूर्ण

/* Last tx segment reports the transmit status */
अटल पूर्णांक sxgbe_get_tx_ls(काष्ठा sxgbe_tx_norm_desc *p)
अणु
	वापस p->tdes23.tx_rd_des23.last_desc;
पूर्ण

/* Get the buffer size from the descriptor */
अटल पूर्णांक sxgbe_get_tx_len(काष्ठा sxgbe_tx_norm_desc *p)
अणु
	वापस p->tdes23.tx_rd_des23.buf1_size;
पूर्ण

/* Set tx बारtamp enable bit */
अटल व्योम sxgbe_tx_enable_tstamp(काष्ठा sxgbe_tx_norm_desc *p)
अणु
	p->tdes23.tx_rd_des23.बारपंचांगp_enable = 1;
पूर्ण

/* get tx बारtamp status */
अटल पूर्णांक sxgbe_get_tx_बारtamp_status(काष्ठा sxgbe_tx_norm_desc *p)
अणु
	वापस p->tdes23.tx_rd_des23.बारपंचांगp_enable;
पूर्ण

/* TX Context Descripto Specअगरic */
अटल व्योम sxgbe_tx_ctxt_desc_set_ctxt(काष्ठा sxgbe_tx_ctxt_desc *p)
अणु
	p->ctxt_bit = 1;
पूर्ण

/* Set the owner of TX context descriptor */
अटल व्योम sxgbe_tx_ctxt_desc_set_owner(काष्ठा sxgbe_tx_ctxt_desc *p)
अणु
	p->own_bit = 1;
पूर्ण

/* Get the owner of TX context descriptor */
अटल पूर्णांक sxgbe_tx_ctxt_desc_get_owner(काष्ठा sxgbe_tx_ctxt_desc *p)
अणु
	वापस p->own_bit;
पूर्ण

/* Set TX mss in TX context Descriptor */
अटल व्योम sxgbe_tx_ctxt_desc_set_mss(काष्ठा sxgbe_tx_ctxt_desc *p, u16 mss)
अणु
	p->maxseg_size = mss;
पूर्ण

/* Get TX mss from TX context Descriptor */
अटल पूर्णांक sxgbe_tx_ctxt_desc_get_mss(काष्ठा sxgbe_tx_ctxt_desc *p)
अणु
	वापस p->maxseg_size;
पूर्ण

/* Set TX tcmssv in TX context Descriptor */
अटल व्योम sxgbe_tx_ctxt_desc_set_tcmssv(काष्ठा sxgbe_tx_ctxt_desc *p)
अणु
	p->tcmssv = 1;
पूर्ण

/* Reset TX ostc in TX context Descriptor */
अटल व्योम sxgbe_tx_ctxt_desc_reset_ostc(काष्ठा sxgbe_tx_ctxt_desc *p)
अणु
	p->ostc = 0;
पूर्ण

/* Set IVLAN inक्रमmation */
अटल व्योम sxgbe_tx_ctxt_desc_set_ivlantag(काष्ठा sxgbe_tx_ctxt_desc *p,
					    पूर्णांक is_ivlanvalid, पूर्णांक ivlan_tag,
					    पूर्णांक ivlan_ctl)
अणु
	अगर (is_ivlanvalid) अणु
		p->ivlan_tag_valid = is_ivlanvalid;
		p->ivlan_tag = ivlan_tag;
		p->ivlan_tag_ctl = ivlan_ctl;
	पूर्ण
पूर्ण

/* Return IVLAN Tag */
अटल पूर्णांक sxgbe_tx_ctxt_desc_get_ivlantag(काष्ठा sxgbe_tx_ctxt_desc *p)
अणु
	वापस p->ivlan_tag;
पूर्ण

/* Set VLAN Tag */
अटल व्योम sxgbe_tx_ctxt_desc_set_vlantag(काष्ठा sxgbe_tx_ctxt_desc *p,
					   पूर्णांक is_vlanvalid, पूर्णांक vlan_tag)
अणु
	अगर (is_vlanvalid) अणु
		p->vltag_valid = is_vlanvalid;
		p->vlan_tag = vlan_tag;
	पूर्ण
पूर्ण

/* Return VLAN Tag */
अटल पूर्णांक sxgbe_tx_ctxt_desc_get_vlantag(काष्ठा sxgbe_tx_ctxt_desc *p)
अणु
	वापस p->vlan_tag;
पूर्ण

/* Set Time stamp */
अटल व्योम sxgbe_tx_ctxt_desc_set_tstamp(काष्ठा sxgbe_tx_ctxt_desc *p,
					  u8 ostc_enable, u64 tstamp)
अणु
	अगर (ostc_enable) अणु
		p->ostc = ostc_enable;
		p->tstamp_lo = (u32) tstamp;
		p->tstamp_hi = (u32) (tstamp>>32);
	पूर्ण
पूर्ण
/* Close TX context descriptor */
अटल व्योम sxgbe_tx_ctxt_desc_बंद(काष्ठा sxgbe_tx_ctxt_desc *p)
अणु
	p->own_bit = 1;
पूर्ण

/* WB status of context descriptor */
अटल पूर्णांक sxgbe_tx_ctxt_desc_get_cde(काष्ठा sxgbe_tx_ctxt_desc *p)
अणु
	वापस p->ctxt_desc_err;
पूर्ण

/* DMA RX descriptor ring initialization */
अटल व्योम sxgbe_init_rx_desc(काष्ठा sxgbe_rx_norm_desc *p, पूर्णांक disable_rx_ic,
			       पूर्णांक mode, पूर्णांक end)
अणु
	p->rdes23.rx_rd_des23.own_bit = 1;
	अगर (disable_rx_ic)
		p->rdes23.rx_rd_des23.पूर्णांक_on_com = disable_rx_ic;
पूर्ण

/* Get RX own bit */
अटल पूर्णांक sxgbe_get_rx_owner(काष्ठा sxgbe_rx_norm_desc *p)
अणु
	वापस p->rdes23.rx_rd_des23.own_bit;
पूर्ण

/* Set RX own bit */
अटल व्योम sxgbe_set_rx_owner(काष्ठा sxgbe_rx_norm_desc *p)
अणु
	p->rdes23.rx_rd_des23.own_bit = 1;
पूर्ण

/* Set Interrupt on completion bit */
अटल व्योम sxgbe_set_rx_पूर्णांक_on_com(काष्ठा sxgbe_rx_norm_desc *p)
अणु
	p->rdes23.rx_rd_des23.पूर्णांक_on_com = 1;
पूर्ण

/* Get the receive frame size */
अटल पूर्णांक sxgbe_get_rx_frame_len(काष्ठा sxgbe_rx_norm_desc *p)
अणु
	वापस p->rdes23.rx_wb_des23.pkt_len;
पूर्ण

/* Return first Descriptor status */
अटल पूर्णांक sxgbe_get_rx_fd_status(काष्ठा sxgbe_rx_norm_desc *p)
अणु
	वापस p->rdes23.rx_wb_des23.first_desc;
पूर्ण

/* Return Last Descriptor status */
अटल पूर्णांक sxgbe_get_rx_ld_status(काष्ठा sxgbe_rx_norm_desc *p)
अणु
	वापस p->rdes23.rx_wb_des23.last_desc;
पूर्ण


/* Return the RX status looking at the WB fields */
अटल पूर्णांक sxgbe_rx_wbstatus(काष्ठा sxgbe_rx_norm_desc *p,
			     काष्ठा sxgbe_extra_stats *x, पूर्णांक *checksum)
अणु
	पूर्णांक status = 0;

	*checksum = CHECKSUM_UNNECESSARY;
	अगर (p->rdes23.rx_wb_des23.err_summary) अणु
		चयन (p->rdes23.rx_wb_des23.err_l2_type) अणु
		हाल RX_GMII_ERR:
			status = -EINVAL;
			x->rx_code_gmii_err++;
			अवरोध;
		हाल RX_WATCHDOG_ERR:
			status = -EINVAL;
			x->rx_watchकरोg_err++;
			अवरोध;
		हाल RX_CRC_ERR:
			status = -EINVAL;
			x->rx_crc_err++;
			अवरोध;
		हाल RX_GAINT_ERR:
			status = -EINVAL;
			x->rx_gaपूर्णांक_pkt_err++;
			अवरोध;
		हाल RX_IP_HDR_ERR:
			*checksum = CHECKSUM_NONE;
			x->ip_hdr_err++;
			अवरोध;
		हाल RX_PAYLOAD_ERR:
			*checksum = CHECKSUM_NONE;
			x->ip_payload_err++;
			अवरोध;
		हाल RX_OVERFLOW_ERR:
			status = -EINVAL;
			x->overflow_error++;
			अवरोध;
		शेष:
			pr_err("Invalid Error type\n");
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (p->rdes23.rx_wb_des23.err_l2_type) अणु
		हाल RX_LEN_PKT:
			x->len_pkt++;
			अवरोध;
		हाल RX_MACCTL_PKT:
			x->mac_ctl_pkt++;
			अवरोध;
		हाल RX_DCBCTL_PKT:
			x->dcb_ctl_pkt++;
			अवरोध;
		हाल RX_ARP_PKT:
			x->arp_pkt++;
			अवरोध;
		हाल RX_OAM_PKT:
			x->oam_pkt++;
			अवरोध;
		हाल RX_UNTAG_PKT:
			x->untag_okt++;
			अवरोध;
		हाल RX_OTHER_PKT:
			x->other_pkt++;
			अवरोध;
		हाल RX_SVLAN_PKT:
			x->svlan_tag_pkt++;
			अवरोध;
		हाल RX_CVLAN_PKT:
			x->cvlan_tag_pkt++;
			अवरोध;
		हाल RX_DVLAN_OCVLAN_ICVLAN_PKT:
			x->dvlan_ocvlan_icvlan_pkt++;
			अवरोध;
		हाल RX_DVLAN_OSVLAN_ISVLAN_PKT:
			x->dvlan_osvlan_isvlan_pkt++;
			अवरोध;
		हाल RX_DVLAN_OSVLAN_ICVLAN_PKT:
			x->dvlan_osvlan_icvlan_pkt++;
			अवरोध;
		हाल RX_DVLAN_OCVLAN_ISVLAN_PKT:
			x->dvlan_ocvlan_icvlan_pkt++;
			अवरोध;
		शेष:
			pr_err("Invalid L2 Packet type\n");
			अवरोध;
		पूर्ण
	पूर्ण

	/* L3/L4 Pkt type */
	चयन (p->rdes23.rx_wb_des23.layer34_pkt_type) अणु
	हाल RX_NOT_IP_PKT:
		x->not_ip_pkt++;
		अवरोध;
	हाल RX_IPV4_TCP_PKT:
		x->ip4_tcp_pkt++;
		अवरोध;
	हाल RX_IPV4_UDP_PKT:
		x->ip4_udp_pkt++;
		अवरोध;
	हाल RX_IPV4_ICMP_PKT:
		x->ip4_icmp_pkt++;
		अवरोध;
	हाल RX_IPV4_UNKNOWN_PKT:
		x->ip4_unknown_pkt++;
		अवरोध;
	हाल RX_IPV6_TCP_PKT:
		x->ip6_tcp_pkt++;
		अवरोध;
	हाल RX_IPV6_UDP_PKT:
		x->ip6_udp_pkt++;
		अवरोध;
	हाल RX_IPV6_ICMP_PKT:
		x->ip6_icmp_pkt++;
		अवरोध;
	हाल RX_IPV6_UNKNOWN_PKT:
		x->ip6_unknown_pkt++;
		अवरोध;
	शेष:
		pr_err("Invalid L3/L4 Packet type\n");
		अवरोध;
	पूर्ण

	/* Filter */
	अगर (p->rdes23.rx_wb_des23.vlan_filter_match)
		x->vlan_filter_match++;

	अगर (p->rdes23.rx_wb_des23.sa_filter_fail) अणु
		status = -EINVAL;
		x->sa_filter_fail++;
	पूर्ण
	अगर (p->rdes23.rx_wb_des23.da_filter_fail) अणु
		status = -EINVAL;
		x->da_filter_fail++;
	पूर्ण
	अगर (p->rdes23.rx_wb_des23.hash_filter_pass)
		x->hash_filter_pass++;

	अगर (p->rdes23.rx_wb_des23.l3_filter_match)
		x->l3_filter_match++;

	अगर (p->rdes23.rx_wb_des23.l4_filter_match)
		x->l4_filter_match++;

	वापस status;
पूर्ण

/* Get own bit of context descriptor */
अटल पूर्णांक sxgbe_get_rx_ctxt_owner(काष्ठा sxgbe_rx_ctxt_desc *p)
अणु
	वापस p->own_bit;
पूर्ण

/* Set own bit क्रम context descriptor */
अटल व्योम sxgbe_set_ctxt_rx_owner(काष्ठा sxgbe_rx_ctxt_desc *p)
अणु
	p->own_bit = 1;
पूर्ण


/* Return the reception status looking at Context control inक्रमmation */
अटल व्योम sxgbe_rx_ctxt_wbstatus(काष्ठा sxgbe_rx_ctxt_desc *p,
				   काष्ठा sxgbe_extra_stats *x)
अणु
	अगर (p->tstamp_dropped)
		x->बारtamp_dropped++;

	/* ptp */
	अगर (p->ptp_msgtype == RX_NO_PTP)
		x->rx_msg_type_no_ptp++;
	अन्यथा अगर (p->ptp_msgtype == RX_PTP_SYNC)
		x->rx_ptp_type_sync++;
	अन्यथा अगर (p->ptp_msgtype == RX_PTP_FOLLOW_UP)
		x->rx_ptp_type_follow_up++;
	अन्यथा अगर (p->ptp_msgtype == RX_PTP_DELAY_REQ)
		x->rx_ptp_type_delay_req++;
	अन्यथा अगर (p->ptp_msgtype == RX_PTP_DELAY_RESP)
		x->rx_ptp_type_delay_resp++;
	अन्यथा अगर (p->ptp_msgtype == RX_PTP_PDELAY_REQ)
		x->rx_ptp_type_pdelay_req++;
	अन्यथा अगर (p->ptp_msgtype == RX_PTP_PDELAY_RESP)
		x->rx_ptp_type_pdelay_resp++;
	अन्यथा अगर (p->ptp_msgtype == RX_PTP_PDELAY_FOLLOW_UP)
		x->rx_ptp_type_pdelay_follow_up++;
	अन्यथा अगर (p->ptp_msgtype == RX_PTP_ANNOUNCE)
		x->rx_ptp_announce++;
	अन्यथा अगर (p->ptp_msgtype == RX_PTP_MGMT)
		x->rx_ptp_mgmt++;
	अन्यथा अगर (p->ptp_msgtype == RX_PTP_SIGNAL)
		x->rx_ptp_संकेत++;
	अन्यथा अगर (p->ptp_msgtype == RX_PTP_RESV_MSG)
		x->rx_ptp_resv_msg_type++;
पूर्ण

/* Get rx बारtamp status */
अटल पूर्णांक sxgbe_get_rx_ctxt_tstamp_status(काष्ठा sxgbe_rx_ctxt_desc *p)
अणु
	अगर ((p->tstamp_hi == 0xffffffff) && (p->tstamp_lo == 0xffffffff)) अणु
		pr_err("Time stamp corrupted\n");
		वापस 0;
	पूर्ण

	वापस p->tstamp_available;
पूर्ण


अटल u64 sxgbe_get_rx_बारtamp(काष्ठा sxgbe_rx_ctxt_desc *p)
अणु
	u64 ns;

	ns = p->tstamp_lo;
	ns |= ((u64)p->tstamp_hi) << 32;

	वापस ns;
पूर्ण

अटल स्थिर काष्ठा sxgbe_desc_ops desc_ops = अणु
	.init_tx_desc			= sxgbe_init_tx_desc,
	.tx_desc_enable_tse		= sxgbe_tx_desc_enable_tse,
	.prepare_tx_desc		= sxgbe_prepare_tx_desc,
	.tx_vlanctl_desc		= sxgbe_tx_vlanctl_desc,
	.set_tx_owner			= sxgbe_set_tx_owner,
	.get_tx_owner			= sxgbe_get_tx_owner,
	.बंद_tx_desc			= sxgbe_बंद_tx_desc,
	.release_tx_desc		= sxgbe_release_tx_desc,
	.clear_tx_ic			= sxgbe_clear_tx_ic,
	.get_tx_ls			= sxgbe_get_tx_ls,
	.get_tx_len			= sxgbe_get_tx_len,
	.tx_enable_tstamp		= sxgbe_tx_enable_tstamp,
	.get_tx_बारtamp_status	= sxgbe_get_tx_बारtamp_status,
	.tx_ctxt_desc_set_ctxt		= sxgbe_tx_ctxt_desc_set_ctxt,
	.tx_ctxt_desc_set_owner		= sxgbe_tx_ctxt_desc_set_owner,
	.get_tx_ctxt_owner		= sxgbe_tx_ctxt_desc_get_owner,
	.tx_ctxt_desc_set_mss		= sxgbe_tx_ctxt_desc_set_mss,
	.tx_ctxt_desc_get_mss		= sxgbe_tx_ctxt_desc_get_mss,
	.tx_ctxt_desc_set_tcmssv	= sxgbe_tx_ctxt_desc_set_tcmssv,
	.tx_ctxt_desc_reset_ostc	= sxgbe_tx_ctxt_desc_reset_ostc,
	.tx_ctxt_desc_set_ivlantag	= sxgbe_tx_ctxt_desc_set_ivlantag,
	.tx_ctxt_desc_get_ivlantag	= sxgbe_tx_ctxt_desc_get_ivlantag,
	.tx_ctxt_desc_set_vlantag	= sxgbe_tx_ctxt_desc_set_vlantag,
	.tx_ctxt_desc_get_vlantag	= sxgbe_tx_ctxt_desc_get_vlantag,
	.tx_ctxt_set_tstamp		= sxgbe_tx_ctxt_desc_set_tstamp,
	.बंद_tx_ctxt_desc		= sxgbe_tx_ctxt_desc_बंद,
	.get_tx_ctxt_cde		= sxgbe_tx_ctxt_desc_get_cde,
	.init_rx_desc			= sxgbe_init_rx_desc,
	.get_rx_owner			= sxgbe_get_rx_owner,
	.set_rx_owner			= sxgbe_set_rx_owner,
	.set_rx_पूर्णांक_on_com		= sxgbe_set_rx_पूर्णांक_on_com,
	.get_rx_frame_len		= sxgbe_get_rx_frame_len,
	.get_rx_fd_status		= sxgbe_get_rx_fd_status,
	.get_rx_ld_status		= sxgbe_get_rx_ld_status,
	.rx_wbstatus			= sxgbe_rx_wbstatus,
	.get_rx_ctxt_owner		= sxgbe_get_rx_ctxt_owner,
	.set_rx_ctxt_owner		= sxgbe_set_ctxt_rx_owner,
	.rx_ctxt_wbstatus		= sxgbe_rx_ctxt_wbstatus,
	.get_rx_ctxt_tstamp_status	= sxgbe_get_rx_ctxt_tstamp_status,
	.get_बारtamp			= sxgbe_get_rx_बारtamp,
पूर्ण;

स्थिर काष्ठा sxgbe_desc_ops *sxgbe_get_desc_ops(व्योम)
अणु
	वापस &desc_ops;
पूर्ण
