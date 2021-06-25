<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*******************************************************************************
  This contains the functions to handle the enhanced descriptors.

  Copyright (C) 2007-2014  STMicroelectronics Ltd


  Author: Giuseppe Cavallaro <peppe.cavallaro@st.com>
*******************************************************************************/

#समावेश <linux/sपंचांगmac.h>
#समावेश "common.h"
#समावेश "descs_com.h"

अटल पूर्णांक enh_desc_get_tx_status(व्योम *data, काष्ठा sपंचांगmac_extra_stats *x,
				  काष्ठा dma_desc *p, व्योम __iomem *ioaddr)
अणु
	काष्ठा net_device_stats *stats = (काष्ठा net_device_stats *)data;
	अचिन्हित पूर्णांक tdes0 = le32_to_cpu(p->des0);
	पूर्णांक ret = tx_करोne;

	/* Get tx owner first */
	अगर (unlikely(tdes0 & ETDES0_OWN))
		वापस tx_dma_own;

	/* Verअगरy tx error by looking at the last segment. */
	अगर (likely(!(tdes0 & ETDES0_LAST_SEGMENT)))
		वापस tx_not_ls;

	अगर (unlikely(tdes0 & ETDES0_ERROR_SUMMARY)) अणु
		अगर (unlikely(tdes0 & ETDES0_JABBER_TIMEOUT))
			x->tx_jabber++;

		अगर (unlikely(tdes0 & ETDES0_FRAME_FLUSHED)) अणु
			x->tx_frame_flushed++;
			dwmac_dma_flush_tx_fअगरo(ioaddr);
		पूर्ण

		अगर (unlikely(tdes0 & ETDES0_LOSS_CARRIER)) अणु
			x->tx_losscarrier++;
			stats->tx_carrier_errors++;
		पूर्ण
		अगर (unlikely(tdes0 & ETDES0_NO_CARRIER)) अणु
			x->tx_carrier++;
			stats->tx_carrier_errors++;
		पूर्ण
		अगर (unlikely((tdes0 & ETDES0_LATE_COLLISION) ||
			     (tdes0 & ETDES0_EXCESSIVE_COLLISIONS)))
			stats->collisions +=
				(tdes0 & ETDES0_COLLISION_COUNT_MASK) >> 3;

		अगर (unlikely(tdes0 & ETDES0_EXCESSIVE_DEFERRAL))
			x->tx_deferred++;

		अगर (unlikely(tdes0 & ETDES0_UNDERFLOW_ERROR)) अणु
			dwmac_dma_flush_tx_fअगरo(ioaddr);
			x->tx_underflow++;
		पूर्ण

		अगर (unlikely(tdes0 & ETDES0_IP_HEADER_ERROR))
			x->tx_ip_header_error++;

		अगर (unlikely(tdes0 & ETDES0_PAYLOAD_ERROR)) अणु
			x->tx_payload_error++;
			dwmac_dma_flush_tx_fअगरo(ioaddr);
		पूर्ण

		ret = tx_err;
	पूर्ण

	अगर (unlikely(tdes0 & ETDES0_DEFERRED))
		x->tx_deferred++;

#अगर_घोषित STMMAC_VLAN_TAG_USED
	अगर (tdes0 & ETDES0_VLAN_FRAME)
		x->tx_vlan++;
#पूर्ण_अगर

	वापस ret;
पूर्ण

अटल पूर्णांक enh_desc_get_tx_len(काष्ठा dma_desc *p)
अणु
	वापस (le32_to_cpu(p->des1) & ETDES1_BUFFER1_SIZE_MASK);
पूर्ण

अटल पूर्णांक enh_desc_coe_rdes0(पूर्णांक ipc_err, पूर्णांक type, पूर्णांक payload_err)
अणु
	पूर्णांक ret = good_frame;
	u32 status = (type << 2 | ipc_err << 1 | payload_err) & 0x7;

	/* bits 5 7 0 | Frame status
	 * ----------------------------------------------------------
	 *      0 0 0 | IEEE 802.3 Type frame (length < 1536 octects)
	 *      1 0 0 | IPv4/6 No CSUM errorS.
	 *      1 0 1 | IPv4/6 CSUM PAYLOAD error
	 *      1 1 0 | IPv4/6 CSUM IP HR error
	 *      1 1 1 | IPv4/6 IP PAYLOAD AND HEADER errorS
	 *      0 0 1 | IPv4/6 unsupported IP PAYLOAD
	 *      0 1 1 | COE bypassed.. no IPv4/6 frame
	 *      0 1 0 | Reserved.
	 */
	अगर (status == 0x0)
		ret = llc_snap;
	अन्यथा अगर (status == 0x4)
		ret = good_frame;
	अन्यथा अगर (status == 0x5)
		ret = csum_none;
	अन्यथा अगर (status == 0x6)
		ret = csum_none;
	अन्यथा अगर (status == 0x7)
		ret = csum_none;
	अन्यथा अगर (status == 0x1)
		ret = discard_frame;
	अन्यथा अगर (status == 0x3)
		ret = discard_frame;
	वापस ret;
पूर्ण

अटल व्योम enh_desc_get_ext_status(व्योम *data, काष्ठा sपंचांगmac_extra_stats *x,
				    काष्ठा dma_extended_desc *p)
अणु
	अचिन्हित पूर्णांक rdes0 = le32_to_cpu(p->basic.des0);
	अचिन्हित पूर्णांक rdes4 = le32_to_cpu(p->des4);

	अगर (unlikely(rdes0 & ERDES0_RX_MAC_ADDR)) अणु
		पूर्णांक message_type = (rdes4 & ERDES4_MSG_TYPE_MASK) >> 8;

		अगर (rdes4 & ERDES4_IP_HDR_ERR)
			x->ip_hdr_err++;
		अगर (rdes4 & ERDES4_IP_PAYLOAD_ERR)
			x->ip_payload_err++;
		अगर (rdes4 & ERDES4_IP_CSUM_BYPASSED)
			x->ip_csum_bypassed++;
		अगर (rdes4 & ERDES4_IPV4_PKT_RCVD)
			x->ipv4_pkt_rcvd++;
		अगर (rdes4 & ERDES4_IPV6_PKT_RCVD)
			x->ipv6_pkt_rcvd++;

		अगर (message_type == RDES_EXT_NO_PTP)
			x->no_ptp_rx_msg_type_ext++;
		अन्यथा अगर (message_type == RDES_EXT_SYNC)
			x->ptp_rx_msg_type_sync++;
		अन्यथा अगर (message_type == RDES_EXT_FOLLOW_UP)
			x->ptp_rx_msg_type_follow_up++;
		अन्यथा अगर (message_type == RDES_EXT_DELAY_REQ)
			x->ptp_rx_msg_type_delay_req++;
		अन्यथा अगर (message_type == RDES_EXT_DELAY_RESP)
			x->ptp_rx_msg_type_delay_resp++;
		अन्यथा अगर (message_type == RDES_EXT_PDELAY_REQ)
			x->ptp_rx_msg_type_pdelay_req++;
		अन्यथा अगर (message_type == RDES_EXT_PDELAY_RESP)
			x->ptp_rx_msg_type_pdelay_resp++;
		अन्यथा अगर (message_type == RDES_EXT_PDELAY_FOLLOW_UP)
			x->ptp_rx_msg_type_pdelay_follow_up++;
		अन्यथा अगर (message_type == RDES_PTP_ANNOUNCE)
			x->ptp_rx_msg_type_announce++;
		अन्यथा अगर (message_type == RDES_PTP_MANAGEMENT)
			x->ptp_rx_msg_type_management++;
		अन्यथा अगर (message_type == RDES_PTP_PKT_RESERVED_TYPE)
			x->ptp_rx_msg_pkt_reserved_type++;

		अगर (rdes4 & ERDES4_PTP_FRAME_TYPE)
			x->ptp_frame_type++;
		अगर (rdes4 & ERDES4_PTP_VER)
			x->ptp_ver++;
		अगर (rdes4 & ERDES4_TIMESTAMP_DROPPED)
			x->बारtamp_dropped++;
		अगर (rdes4 & ERDES4_AV_PKT_RCVD)
			x->av_pkt_rcvd++;
		अगर (rdes4 & ERDES4_AV_TAGGED_PKT_RCVD)
			x->av_tagged_pkt_rcvd++;
		अगर ((rdes4 & ERDES4_VLAN_TAG_PRI_VAL_MASK) >> 18)
			x->vlan_tag_priority_val++;
		अगर (rdes4 & ERDES4_L3_FILTER_MATCH)
			x->l3_filter_match++;
		अगर (rdes4 & ERDES4_L4_FILTER_MATCH)
			x->l4_filter_match++;
		अगर ((rdes4 & ERDES4_L3_L4_FILT_NO_MATCH_MASK) >> 26)
			x->l3_l4_filter_no_match++;
	पूर्ण
पूर्ण

अटल पूर्णांक enh_desc_get_rx_status(व्योम *data, काष्ठा sपंचांगmac_extra_stats *x,
				  काष्ठा dma_desc *p)
अणु
	काष्ठा net_device_stats *stats = (काष्ठा net_device_stats *)data;
	अचिन्हित पूर्णांक rdes0 = le32_to_cpu(p->des0);
	पूर्णांक ret = good_frame;

	अगर (unlikely(rdes0 & RDES0_OWN))
		वापस dma_own;

	अगर (unlikely(!(rdes0 & RDES0_LAST_DESCRIPTOR))) अणु
		stats->rx_length_errors++;
		वापस discard_frame;
	पूर्ण

	अगर (unlikely(rdes0 & RDES0_ERROR_SUMMARY)) अणु
		अगर (unlikely(rdes0 & RDES0_DESCRIPTOR_ERROR)) अणु
			x->rx_desc++;
			stats->rx_length_errors++;
		पूर्ण
		अगर (unlikely(rdes0 & RDES0_OVERFLOW_ERROR))
			x->rx_gmac_overflow++;

		अगर (unlikely(rdes0 & RDES0_IPC_CSUM_ERROR))
			pr_err("\tIPC Csum Error/Giant frame\n");

		अगर (unlikely(rdes0 & RDES0_COLLISION))
			stats->collisions++;
		अगर (unlikely(rdes0 & RDES0_RECEIVE_WATCHDOG))
			x->rx_watchकरोg++;

		अगर (unlikely(rdes0 & RDES0_MII_ERROR))	/* GMII */
			x->rx_mii++;

		अगर (unlikely(rdes0 & RDES0_CRC_ERROR)) अणु
			x->rx_crc_errors++;
			stats->rx_crc_errors++;
		पूर्ण
		ret = discard_frame;
	पूर्ण

	/* After a payload csum error, the ES bit is set.
	 * It करोesn't match with the inक्रमmation reported पूर्णांकo the databook.
	 * At any rate, we need to understand अगर the CSUM hw computation is ok
	 * and report this info to the upper layers. */
	अगर (likely(ret == good_frame))
		ret = enh_desc_coe_rdes0(!!(rdes0 & RDES0_IPC_CSUM_ERROR),
					 !!(rdes0 & RDES0_FRAME_TYPE),
					 !!(rdes0 & ERDES0_RX_MAC_ADDR));

	अगर (unlikely(rdes0 & RDES0_DRIBBLING))
		x->dribbling_bit++;

	अगर (unlikely(rdes0 & RDES0_SA_FILTER_FAIL)) अणु
		x->sa_rx_filter_fail++;
		ret = discard_frame;
	पूर्ण
	अगर (unlikely(rdes0 & RDES0_DA_FILTER_FAIL)) अणु
		x->da_rx_filter_fail++;
		ret = discard_frame;
	पूर्ण
	अगर (unlikely(rdes0 & RDES0_LENGTH_ERROR)) अणु
		x->rx_length++;
		ret = discard_frame;
	पूर्ण
#अगर_घोषित STMMAC_VLAN_TAG_USED
	अगर (rdes0 & RDES0_VLAN_TAG)
		x->rx_vlan++;
#पूर्ण_अगर

	वापस ret;
पूर्ण

अटल व्योम enh_desc_init_rx_desc(काष्ठा dma_desc *p, पूर्णांक disable_rx_ic,
				  पूर्णांक mode, पूर्णांक end, पूर्णांक bfsize)
अणु
	पूर्णांक bfsize1;

	p->des0 |= cpu_to_le32(RDES0_OWN);

	bfsize1 = min(bfsize, BUF_SIZE_8KiB);
	p->des1 |= cpu_to_le32(bfsize1 & ERDES1_BUFFER1_SIZE_MASK);

	अगर (mode == STMMAC_CHAIN_MODE)
		ehn_desc_rx_set_on_chain(p);
	अन्यथा
		ehn_desc_rx_set_on_ring(p, end, bfsize);

	अगर (disable_rx_ic)
		p->des1 |= cpu_to_le32(ERDES1_DISABLE_IC);
पूर्ण

अटल व्योम enh_desc_init_tx_desc(काष्ठा dma_desc *p, पूर्णांक mode, पूर्णांक end)
अणु
	p->des0 &= cpu_to_le32(~ETDES0_OWN);
	अगर (mode == STMMAC_CHAIN_MODE)
		enh_desc_end_tx_desc_on_chain(p);
	अन्यथा
		enh_desc_end_tx_desc_on_ring(p, end);
पूर्ण

अटल पूर्णांक enh_desc_get_tx_owner(काष्ठा dma_desc *p)
अणु
	वापस (le32_to_cpu(p->des0) & ETDES0_OWN) >> 31;
पूर्ण

अटल व्योम enh_desc_set_tx_owner(काष्ठा dma_desc *p)
अणु
	p->des0 |= cpu_to_le32(ETDES0_OWN);
पूर्ण

अटल व्योम enh_desc_set_rx_owner(काष्ठा dma_desc *p, पूर्णांक disable_rx_ic)
अणु
	p->des0 |= cpu_to_le32(RDES0_OWN);
पूर्ण

अटल पूर्णांक enh_desc_get_tx_ls(काष्ठा dma_desc *p)
अणु
	वापस (le32_to_cpu(p->des0) & ETDES0_LAST_SEGMENT) >> 29;
पूर्ण

अटल व्योम enh_desc_release_tx_desc(काष्ठा dma_desc *p, पूर्णांक mode)
अणु
	पूर्णांक ter = (le32_to_cpu(p->des0) & ETDES0_END_RING) >> 21;

	स_रखो(p, 0, दुरत्व(काष्ठा dma_desc, des2));
	अगर (mode == STMMAC_CHAIN_MODE)
		enh_desc_end_tx_desc_on_chain(p);
	अन्यथा
		enh_desc_end_tx_desc_on_ring(p, ter);
पूर्ण

अटल व्योम enh_desc_prepare_tx_desc(काष्ठा dma_desc *p, पूर्णांक is_fs, पूर्णांक len,
				     bool csum_flag, पूर्णांक mode, bool tx_own,
				     bool ls, अचिन्हित पूर्णांक tot_pkt_len)
अणु
	अचिन्हित पूर्णांक tdes0 = le32_to_cpu(p->des0);

	अगर (mode == STMMAC_CHAIN_MODE)
		enh_set_tx_desc_len_on_chain(p, len);
	अन्यथा
		enh_set_tx_desc_len_on_ring(p, len);

	अगर (is_fs)
		tdes0 |= ETDES0_FIRST_SEGMENT;
	अन्यथा
		tdes0 &= ~ETDES0_FIRST_SEGMENT;

	अगर (likely(csum_flag))
		tdes0 |= (TX_CIC_FULL << ETDES0_CHECKSUM_INSERTION_SHIFT);
	अन्यथा
		tdes0 &= ~(TX_CIC_FULL << ETDES0_CHECKSUM_INSERTION_SHIFT);

	अगर (ls)
		tdes0 |= ETDES0_LAST_SEGMENT;

	/* Finally set the OWN bit. Later the DMA will start! */
	अगर (tx_own)
		tdes0 |= ETDES0_OWN;

	अगर (is_fs && tx_own)
		/* When the own bit, क्रम the first frame, has to be set, all
		 * descriptors क्रम the same frame has to be set beक्रमe, to
		 * aव्योम race condition.
		 */
		dma_wmb();

	p->des0 = cpu_to_le32(tdes0);
पूर्ण

अटल व्योम enh_desc_set_tx_ic(काष्ठा dma_desc *p)
अणु
	p->des0 |= cpu_to_le32(ETDES0_INTERRUPT);
पूर्ण

अटल पूर्णांक enh_desc_get_rx_frame_len(काष्ठा dma_desc *p, पूर्णांक rx_coe_type)
अणु
	अचिन्हित पूर्णांक csum = 0;
	/* The type-1 checksum offload engines append the checksum at
	 * the end of frame and the two bytes of checksum are added in
	 * the length.
	 * Adjust क्रम that in the framelen क्रम type-1 checksum offload
	 * engines.
	 */
	अगर (rx_coe_type == STMMAC_RX_COE_TYPE1)
		csum = 2;

	वापस (((le32_to_cpu(p->des0) & RDES0_FRAME_LEN_MASK)
				>> RDES0_FRAME_LEN_SHIFT) - csum);
पूर्ण

अटल व्योम enh_desc_enable_tx_बारtamp(काष्ठा dma_desc *p)
अणु
	p->des0 |= cpu_to_le32(ETDES0_TIME_STAMP_ENABLE);
पूर्ण

अटल पूर्णांक enh_desc_get_tx_बारtamp_status(काष्ठा dma_desc *p)
अणु
	वापस (le32_to_cpu(p->des0) & ETDES0_TIME_STAMP_STATUS) >> 17;
पूर्ण

अटल व्योम enh_desc_get_बारtamp(व्योम *desc, u32 ats, u64 *ts)
अणु
	u64 ns;

	अगर (ats) अणु
		काष्ठा dma_extended_desc *p = (काष्ठा dma_extended_desc *)desc;
		ns = le32_to_cpu(p->des6);
		/* convert high/sec समय stamp value to nanosecond */
		ns += le32_to_cpu(p->des7) * 1000000000ULL;
	पूर्ण अन्यथा अणु
		काष्ठा dma_desc *p = (काष्ठा dma_desc *)desc;
		ns = le32_to_cpu(p->des2);
		ns += le32_to_cpu(p->des3) * 1000000000ULL;
	पूर्ण

	*ts = ns;
पूर्ण

अटल पूर्णांक enh_desc_get_rx_बारtamp_status(व्योम *desc, व्योम *next_desc,
					    u32 ats)
अणु
	अगर (ats) अणु
		काष्ठा dma_extended_desc *p = (काष्ठा dma_extended_desc *)desc;
		वापस (le32_to_cpu(p->basic.des0) & RDES0_IPC_CSUM_ERROR) >> 7;
	पूर्ण अन्यथा अणु
		काष्ठा dma_desc *p = (काष्ठा dma_desc *)desc;
		अगर ((le32_to_cpu(p->des2) == 0xffffffff) &&
		    (le32_to_cpu(p->des3) == 0xffffffff))
			/* बारtamp is corrupted, hence करोn't store it */
			वापस 0;
		अन्यथा
			वापस 1;
	पूर्ण
पूर्ण

अटल व्योम enh_desc_display_ring(व्योम *head, अचिन्हित पूर्णांक size, bool rx,
				  dma_addr_t dma_rx_phy, अचिन्हित पूर्णांक desc_size)
अणु
	काष्ठा dma_extended_desc *ep = (काष्ठा dma_extended_desc *)head;
	dma_addr_t dma_addr;
	पूर्णांक i;

	pr_info("Extended %s descriptor ring:\n", rx ? "RX" : "TX");

	क्रम (i = 0; i < size; i++) अणु
		u64 x;
		dma_addr = dma_rx_phy + i * माप(*ep);

		x = *(u64 *)ep;
		pr_info("%03d [%pad]: 0x%x 0x%x 0x%x 0x%x\n",
			i, &dma_addr,
			(अचिन्हित पूर्णांक)x, (अचिन्हित पूर्णांक)(x >> 32),
			ep->basic.des2, ep->basic.des3);
		ep++;
	पूर्ण
	pr_info("\n");
पूर्ण

अटल व्योम enh_desc_get_addr(काष्ठा dma_desc *p, अचिन्हित पूर्णांक *addr)
अणु
	*addr = le32_to_cpu(p->des2);
पूर्ण

अटल व्योम enh_desc_set_addr(काष्ठा dma_desc *p, dma_addr_t addr)
अणु
	p->des2 = cpu_to_le32(addr);
पूर्ण

अटल व्योम enh_desc_clear(काष्ठा dma_desc *p)
अणु
	p->des2 = 0;
पूर्ण

स्थिर काष्ठा sपंचांगmac_desc_ops enh_desc_ops = अणु
	.tx_status = enh_desc_get_tx_status,
	.rx_status = enh_desc_get_rx_status,
	.get_tx_len = enh_desc_get_tx_len,
	.init_rx_desc = enh_desc_init_rx_desc,
	.init_tx_desc = enh_desc_init_tx_desc,
	.get_tx_owner = enh_desc_get_tx_owner,
	.release_tx_desc = enh_desc_release_tx_desc,
	.prepare_tx_desc = enh_desc_prepare_tx_desc,
	.set_tx_ic = enh_desc_set_tx_ic,
	.get_tx_ls = enh_desc_get_tx_ls,
	.set_tx_owner = enh_desc_set_tx_owner,
	.set_rx_owner = enh_desc_set_rx_owner,
	.get_rx_frame_len = enh_desc_get_rx_frame_len,
	.rx_extended_status = enh_desc_get_ext_status,
	.enable_tx_बारtamp = enh_desc_enable_tx_बारtamp,
	.get_tx_बारtamp_status = enh_desc_get_tx_बारtamp_status,
	.get_बारtamp = enh_desc_get_बारtamp,
	.get_rx_बारtamp_status = enh_desc_get_rx_बारtamp_status,
	.display_ring = enh_desc_display_ring,
	.get_addr = enh_desc_get_addr,
	.set_addr = enh_desc_set_addr,
	.clear = enh_desc_clear,
पूर्ण;
