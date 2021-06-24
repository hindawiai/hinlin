<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This contains the functions to handle the descriptors क्रम DesignWare databook
 * 4.xx.
 *
 * Copyright (C) 2015  STMicroelectronics Ltd
 *
 * Author: Alexandre Torgue <alexandre.torgue@st.com>
 */

#समावेश <linux/sपंचांगmac.h>
#समावेश "common.h"
#समावेश "dwmac4.h"
#समावेश "dwmac4_descs.h"

अटल पूर्णांक dwmac4_wrback_get_tx_status(व्योम *data, काष्ठा sपंचांगmac_extra_stats *x,
				       काष्ठा dma_desc *p,
				       व्योम __iomem *ioaddr)
अणु
	काष्ठा net_device_stats *stats = (काष्ठा net_device_stats *)data;
	अचिन्हित पूर्णांक tdes3;
	पूर्णांक ret = tx_करोne;

	tdes3 = le32_to_cpu(p->des3);

	/* Get tx owner first */
	अगर (unlikely(tdes3 & TDES3_OWN))
		वापस tx_dma_own;

	/* Verअगरy tx error by looking at the last segment. */
	अगर (likely(!(tdes3 & TDES3_LAST_DESCRIPTOR)))
		वापस tx_not_ls;

	अगर (unlikely(tdes3 & TDES3_ERROR_SUMMARY)) अणु
		अगर (unlikely(tdes3 & TDES3_JABBER_TIMEOUT))
			x->tx_jabber++;
		अगर (unlikely(tdes3 & TDES3_PACKET_FLUSHED))
			x->tx_frame_flushed++;
		अगर (unlikely(tdes3 & TDES3_LOSS_CARRIER)) अणु
			x->tx_losscarrier++;
			stats->tx_carrier_errors++;
		पूर्ण
		अगर (unlikely(tdes3 & TDES3_NO_CARRIER)) अणु
			x->tx_carrier++;
			stats->tx_carrier_errors++;
		पूर्ण
		अगर (unlikely((tdes3 & TDES3_LATE_COLLISION) ||
			     (tdes3 & TDES3_EXCESSIVE_COLLISION)))
			stats->collisions +=
			    (tdes3 & TDES3_COLLISION_COUNT_MASK)
			    >> TDES3_COLLISION_COUNT_SHIFT;

		अगर (unlikely(tdes3 & TDES3_EXCESSIVE_DEFERRAL))
			x->tx_deferred++;

		अगर (unlikely(tdes3 & TDES3_UNDERFLOW_ERROR))
			x->tx_underflow++;

		अगर (unlikely(tdes3 & TDES3_IP_HDR_ERROR))
			x->tx_ip_header_error++;

		अगर (unlikely(tdes3 & TDES3_PAYLOAD_ERROR))
			x->tx_payload_error++;

		ret = tx_err;
	पूर्ण

	अगर (unlikely(tdes3 & TDES3_DEFERRED))
		x->tx_deferred++;

	वापस ret;
पूर्ण

अटल पूर्णांक dwmac4_wrback_get_rx_status(व्योम *data, काष्ठा sपंचांगmac_extra_stats *x,
				       काष्ठा dma_desc *p)
अणु
	काष्ठा net_device_stats *stats = (काष्ठा net_device_stats *)data;
	अचिन्हित पूर्णांक rdes1 = le32_to_cpu(p->des1);
	अचिन्हित पूर्णांक rdes2 = le32_to_cpu(p->des2);
	अचिन्हित पूर्णांक rdes3 = le32_to_cpu(p->des3);
	पूर्णांक message_type;
	पूर्णांक ret = good_frame;

	अगर (unlikely(rdes3 & RDES3_OWN))
		वापस dma_own;

	अगर (unlikely(rdes3 & RDES3_CONTEXT_DESCRIPTOR))
		वापस discard_frame;
	अगर (likely(!(rdes3 & RDES3_LAST_DESCRIPTOR)))
		वापस rx_not_ls;

	अगर (unlikely(rdes3 & RDES3_ERROR_SUMMARY)) अणु
		अगर (unlikely(rdes3 & RDES3_GIANT_PACKET))
			stats->rx_length_errors++;
		अगर (unlikely(rdes3 & RDES3_OVERFLOW_ERROR))
			x->rx_gmac_overflow++;

		अगर (unlikely(rdes3 & RDES3_RECEIVE_WATCHDOG))
			x->rx_watchकरोg++;

		अगर (unlikely(rdes3 & RDES3_RECEIVE_ERROR))
			x->rx_mii++;

		अगर (unlikely(rdes3 & RDES3_CRC_ERROR)) अणु
			x->rx_crc_errors++;
			stats->rx_crc_errors++;
		पूर्ण

		अगर (unlikely(rdes3 & RDES3_DRIBBLE_ERROR))
			x->dribbling_bit++;

		ret = discard_frame;
	पूर्ण

	message_type = (rdes1 & ERDES4_MSG_TYPE_MASK) >> 8;

	अगर (rdes1 & RDES1_IP_HDR_ERROR)
		x->ip_hdr_err++;
	अगर (rdes1 & RDES1_IP_CSUM_BYPASSED)
		x->ip_csum_bypassed++;
	अगर (rdes1 & RDES1_IPV4_HEADER)
		x->ipv4_pkt_rcvd++;
	अगर (rdes1 & RDES1_IPV6_HEADER)
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

	अगर (rdes1 & RDES1_PTP_PACKET_TYPE)
		x->ptp_frame_type++;
	अगर (rdes1 & RDES1_PTP_VER)
		x->ptp_ver++;
	अगर (rdes1 & RDES1_TIMESTAMP_DROPPED)
		x->बारtamp_dropped++;

	अगर (unlikely(rdes2 & RDES2_SA_FILTER_FAIL)) अणु
		x->sa_rx_filter_fail++;
		ret = discard_frame;
	पूर्ण
	अगर (unlikely(rdes2 & RDES2_DA_FILTER_FAIL)) अणु
		x->da_rx_filter_fail++;
		ret = discard_frame;
	पूर्ण

	अगर (rdes2 & RDES2_L3_FILTER_MATCH)
		x->l3_filter_match++;
	अगर (rdes2 & RDES2_L4_FILTER_MATCH)
		x->l4_filter_match++;
	अगर ((rdes2 & RDES2_L3_L4_FILT_NB_MATCH_MASK)
	    >> RDES2_L3_L4_FILT_NB_MATCH_SHIFT)
		x->l3_l4_filter_no_match++;

	वापस ret;
पूर्ण

अटल पूर्णांक dwmac4_rd_get_tx_len(काष्ठा dma_desc *p)
अणु
	वापस (le32_to_cpu(p->des2) & TDES2_BUFFER1_SIZE_MASK);
पूर्ण

अटल पूर्णांक dwmac4_get_tx_owner(काष्ठा dma_desc *p)
अणु
	वापस (le32_to_cpu(p->des3) & TDES3_OWN) >> TDES3_OWN_SHIFT;
पूर्ण

अटल व्योम dwmac4_set_tx_owner(काष्ठा dma_desc *p)
अणु
	p->des3 |= cpu_to_le32(TDES3_OWN);
पूर्ण

अटल व्योम dwmac4_set_rx_owner(काष्ठा dma_desc *p, पूर्णांक disable_rx_ic)
अणु
	p->des3 |= cpu_to_le32(RDES3_OWN | RDES3_BUFFER1_VALID_ADDR);

	अगर (!disable_rx_ic)
		p->des3 |= cpu_to_le32(RDES3_INT_ON_COMPLETION_EN);
पूर्ण

अटल पूर्णांक dwmac4_get_tx_ls(काष्ठा dma_desc *p)
अणु
	वापस (le32_to_cpu(p->des3) & TDES3_LAST_DESCRIPTOR)
		>> TDES3_LAST_DESCRIPTOR_SHIFT;
पूर्ण

अटल पूर्णांक dwmac4_wrback_get_rx_frame_len(काष्ठा dma_desc *p, पूर्णांक rx_coe)
अणु
	वापस (le32_to_cpu(p->des3) & RDES3_PACKET_SIZE_MASK);
पूर्ण

अटल व्योम dwmac4_rd_enable_tx_बारtamp(काष्ठा dma_desc *p)
अणु
	p->des2 |= cpu_to_le32(TDES2_TIMESTAMP_ENABLE);
पूर्ण

अटल पूर्णांक dwmac4_wrback_get_tx_बारtamp_status(काष्ठा dma_desc *p)
अणु
	/* Context type from W/B descriptor must be zero */
	अगर (le32_to_cpu(p->des3) & TDES3_CONTEXT_TYPE)
		वापस 0;

	/* Tx Timestamp Status is 1 so des0 and des1'll have valid values */
	अगर (le32_to_cpu(p->des3) & TDES3_TIMESTAMP_STATUS)
		वापस 1;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम dwmac4_get_बारtamp(व्योम *desc, u32 ats, u64 *ts)
अणु
	काष्ठा dma_desc *p = (काष्ठा dma_desc *)desc;
	u64 ns;

	ns = le32_to_cpu(p->des0);
	/* convert high/sec समय stamp value to nanosecond */
	ns += le32_to_cpu(p->des1) * 1000000000ULL;

	*ts = ns;
पूर्ण

अटल पूर्णांक dwmac4_rx_check_बारtamp(व्योम *desc)
अणु
	काष्ठा dma_desc *p = (काष्ठा dma_desc *)desc;
	अचिन्हित पूर्णांक rdes0 = le32_to_cpu(p->des0);
	अचिन्हित पूर्णांक rdes1 = le32_to_cpu(p->des1);
	अचिन्हित पूर्णांक rdes3 = le32_to_cpu(p->des3);
	u32 own, ctxt;
	पूर्णांक ret = 1;

	own = rdes3 & RDES3_OWN;
	ctxt = ((rdes3 & RDES3_CONTEXT_DESCRIPTOR)
		>> RDES3_CONTEXT_DESCRIPTOR_SHIFT);

	अगर (likely(!own && ctxt)) अणु
		अगर ((rdes0 == 0xffffffff) && (rdes1 == 0xffffffff))
			/* Corrupted value */
			ret = -EINVAL;
		अन्यथा
			/* A valid Timestamp is पढ़ोy to be पढ़ो */
			ret = 0;
	पूर्ण

	/* Timestamp not पढ़ोy */
	वापस ret;
पूर्ण

अटल पूर्णांक dwmac4_wrback_get_rx_बारtamp_status(व्योम *desc, व्योम *next_desc,
						 u32 ats)
अणु
	काष्ठा dma_desc *p = (काष्ठा dma_desc *)desc;
	पूर्णांक ret = -EINVAL;

	/* Get the status from normal w/b descriptor */
	अगर (likely(le32_to_cpu(p->des3) & RDES3_RDES1_VALID)) अणु
		अगर (likely(le32_to_cpu(p->des1) & RDES1_TIMESTAMP_AVAILABLE)) अणु
			पूर्णांक i = 0;

			/* Check अगर बारtamp is OK from context descriptor */
			करो अणु
				ret = dwmac4_rx_check_बारtamp(next_desc);
				अगर (ret < 0)
					जाओ निकास;
				i++;

			पूर्ण जबतक ((ret == 1) && (i < 10));

			अगर (i == 10)
				ret = -EBUSY;
		पूर्ण
	पूर्ण
निकास:
	अगर (likely(ret == 0))
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम dwmac4_rd_init_rx_desc(काष्ठा dma_desc *p, पूर्णांक disable_rx_ic,
				   पूर्णांक mode, पूर्णांक end, पूर्णांक bfsize)
अणु
	dwmac4_set_rx_owner(p, disable_rx_ic);
पूर्ण

अटल व्योम dwmac4_rd_init_tx_desc(काष्ठा dma_desc *p, पूर्णांक mode, पूर्णांक end)
अणु
	p->des0 = 0;
	p->des1 = 0;
	p->des2 = 0;
	p->des3 = 0;
पूर्ण

अटल व्योम dwmac4_rd_prepare_tx_desc(काष्ठा dma_desc *p, पूर्णांक is_fs, पूर्णांक len,
				      bool csum_flag, पूर्णांक mode, bool tx_own,
				      bool ls, अचिन्हित पूर्णांक tot_pkt_len)
अणु
	अचिन्हित पूर्णांक tdes3 = le32_to_cpu(p->des3);

	p->des2 |= cpu_to_le32(len & TDES2_BUFFER1_SIZE_MASK);

	tdes3 |= tot_pkt_len & TDES3_PACKET_SIZE_MASK;
	अगर (is_fs)
		tdes3 |= TDES3_FIRST_DESCRIPTOR;
	अन्यथा
		tdes3 &= ~TDES3_FIRST_DESCRIPTOR;

	अगर (likely(csum_flag))
		tdes3 |= (TX_CIC_FULL << TDES3_CHECKSUM_INSERTION_SHIFT);
	अन्यथा
		tdes3 &= ~(TX_CIC_FULL << TDES3_CHECKSUM_INSERTION_SHIFT);

	अगर (ls)
		tdes3 |= TDES3_LAST_DESCRIPTOR;
	अन्यथा
		tdes3 &= ~TDES3_LAST_DESCRIPTOR;

	/* Finally set the OWN bit. Later the DMA will start! */
	अगर (tx_own)
		tdes3 |= TDES3_OWN;

	अगर (is_fs && tx_own)
		/* When the own bit, क्रम the first frame, has to be set, all
		 * descriptors क्रम the same frame has to be set beक्रमe, to
		 * aव्योम race condition.
		 */
		dma_wmb();

	p->des3 = cpu_to_le32(tdes3);
पूर्ण

अटल व्योम dwmac4_rd_prepare_tso_tx_desc(काष्ठा dma_desc *p, पूर्णांक is_fs,
					  पूर्णांक len1, पूर्णांक len2, bool tx_own,
					  bool ls, अचिन्हित पूर्णांक tcphdrlen,
					  अचिन्हित पूर्णांक tcppayloadlen)
अणु
	अचिन्हित पूर्णांक tdes3 = le32_to_cpu(p->des3);

	अगर (len1)
		p->des2 |= cpu_to_le32((len1 & TDES2_BUFFER1_SIZE_MASK));

	अगर (len2)
		p->des2 |= cpu_to_le32((len2 << TDES2_BUFFER2_SIZE_MASK_SHIFT)
			    & TDES2_BUFFER2_SIZE_MASK);

	अगर (is_fs) अणु
		tdes3 |= TDES3_FIRST_DESCRIPTOR |
			 TDES3_TCP_SEGMENTATION_ENABLE |
			 ((tcphdrlen << TDES3_HDR_LEN_SHIFT) &
			  TDES3_SLOT_NUMBER_MASK) |
			 ((tcppayloadlen & TDES3_TCP_PKT_PAYLOAD_MASK));
	पूर्ण अन्यथा अणु
		tdes3 &= ~TDES3_FIRST_DESCRIPTOR;
	पूर्ण

	अगर (ls)
		tdes3 |= TDES3_LAST_DESCRIPTOR;
	अन्यथा
		tdes3 &= ~TDES3_LAST_DESCRIPTOR;

	/* Finally set the OWN bit. Later the DMA will start! */
	अगर (tx_own)
		tdes3 |= TDES3_OWN;

	अगर (is_fs && tx_own)
		/* When the own bit, क्रम the first frame, has to be set, all
		 * descriptors क्रम the same frame has to be set beक्रमe, to
		 * aव्योम race condition.
		 */
		dma_wmb();

	p->des3 = cpu_to_le32(tdes3);
पूर्ण

अटल व्योम dwmac4_release_tx_desc(काष्ठा dma_desc *p, पूर्णांक mode)
अणु
	p->des0 = 0;
	p->des1 = 0;
	p->des2 = 0;
	p->des3 = 0;
पूर्ण

अटल व्योम dwmac4_rd_set_tx_ic(काष्ठा dma_desc *p)
अणु
	p->des2 |= cpu_to_le32(TDES2_INTERRUPT_ON_COMPLETION);
पूर्ण

अटल व्योम dwmac4_display_ring(व्योम *head, अचिन्हित पूर्णांक size, bool rx,
				dma_addr_t dma_rx_phy, अचिन्हित पूर्णांक desc_size)
अणु
	dma_addr_t dma_addr;
	पूर्णांक i;

	pr_info("%s descriptor ring:\n", rx ? "RX" : "TX");

	अगर (desc_size == माप(काष्ठा dma_desc)) अणु
		काष्ठा dma_desc *p = (काष्ठा dma_desc *)head;

		क्रम (i = 0; i < size; i++) अणु
			dma_addr = dma_rx_phy + i * माप(*p);
			pr_info("%03d [%pad]: 0x%x 0x%x 0x%x 0x%x\n",
				i, &dma_addr,
				le32_to_cpu(p->des0), le32_to_cpu(p->des1),
				le32_to_cpu(p->des2), le32_to_cpu(p->des3));
			p++;
		पूर्ण
	पूर्ण अन्यथा अगर (desc_size == माप(काष्ठा dma_extended_desc)) अणु
		काष्ठा dma_extended_desc *extp = (काष्ठा dma_extended_desc *)head;

		क्रम (i = 0; i < size; i++) अणु
			dma_addr = dma_rx_phy + i * माप(*extp);
			pr_info("%03d [%pad]: 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n",
				i, &dma_addr,
				le32_to_cpu(extp->basic.des0), le32_to_cpu(extp->basic.des1),
				le32_to_cpu(extp->basic.des2), le32_to_cpu(extp->basic.des3),
				le32_to_cpu(extp->des4), le32_to_cpu(extp->des5),
				le32_to_cpu(extp->des6), le32_to_cpu(extp->des7));
			extp++;
		पूर्ण
	पूर्ण अन्यथा अगर (desc_size == माप(काष्ठा dma_edesc)) अणु
		काष्ठा dma_edesc *ep = (काष्ठा dma_edesc *)head;

		क्रम (i = 0; i < size; i++) अणु
			dma_addr = dma_rx_phy + i * माप(*ep);
			pr_info("%03d [%pad]: 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n",
				i, &dma_addr,
				le32_to_cpu(ep->des4), le32_to_cpu(ep->des5),
				le32_to_cpu(ep->des6), le32_to_cpu(ep->des7),
				le32_to_cpu(ep->basic.des0), le32_to_cpu(ep->basic.des1),
				le32_to_cpu(ep->basic.des2), le32_to_cpu(ep->basic.des3));
			ep++;
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_err("unsupported descriptor!");
	पूर्ण
पूर्ण

अटल व्योम dwmac4_set_mss_ctxt(काष्ठा dma_desc *p, अचिन्हित पूर्णांक mss)
अणु
	p->des0 = 0;
	p->des1 = 0;
	p->des2 = cpu_to_le32(mss);
	p->des3 = cpu_to_le32(TDES3_CONTEXT_TYPE | TDES3_CTXT_TCMSSV);
पूर्ण

अटल व्योम dwmac4_get_addr(काष्ठा dma_desc *p, अचिन्हित पूर्णांक *addr)
अणु
	*addr = le32_to_cpu(p->des0);
पूर्ण

अटल व्योम dwmac4_set_addr(काष्ठा dma_desc *p, dma_addr_t addr)
अणु
	p->des0 = cpu_to_le32(lower_32_bits(addr));
	p->des1 = cpu_to_le32(upper_32_bits(addr));
पूर्ण

अटल व्योम dwmac4_clear(काष्ठा dma_desc *p)
अणु
	p->des0 = 0;
	p->des1 = 0;
	p->des2 = 0;
	p->des3 = 0;
पूर्ण

अटल व्योम dwmac4_set_sarc(काष्ठा dma_desc *p, u32 sarc_type)
अणु
	sarc_type <<= TDES3_SA_INSERT_CTRL_SHIFT;

	p->des3 |= cpu_to_le32(sarc_type & TDES3_SA_INSERT_CTRL_MASK);
पूर्ण

अटल पूर्णांक set_16kib_bfsize(पूर्णांक mtu)
अणु
	पूर्णांक ret = 0;

	अगर (unlikely(mtu >= BUF_SIZE_8KiB))
		ret = BUF_SIZE_16KiB;
	वापस ret;
पूर्ण

अटल व्योम dwmac4_set_vlan_tag(काष्ठा dma_desc *p, u16 tag, u16 inner_tag,
				u32 inner_type)
अणु
	p->des0 = 0;
	p->des1 = 0;
	p->des2 = 0;
	p->des3 = 0;

	/* Inner VLAN */
	अगर (inner_type) अणु
		u32 des = inner_tag << TDES2_IVT_SHIFT;

		des &= TDES2_IVT_MASK;
		p->des2 = cpu_to_le32(des);

		des = inner_type << TDES3_IVTIR_SHIFT;
		des &= TDES3_IVTIR_MASK;
		p->des3 = cpu_to_le32(des | TDES3_IVLTV);
	पूर्ण

	/* Outer VLAN */
	p->des3 |= cpu_to_le32(tag & TDES3_VLAN_TAG);
	p->des3 |= cpu_to_le32(TDES3_VLTV);

	p->des3 |= cpu_to_le32(TDES3_CONTEXT_TYPE);
पूर्ण

अटल व्योम dwmac4_set_vlan(काष्ठा dma_desc *p, u32 type)
अणु
	type <<= TDES2_VLAN_TAG_SHIFT;
	p->des2 |= cpu_to_le32(type & TDES2_VLAN_TAG_MASK);
पूर्ण

अटल व्योम dwmac4_get_rx_header_len(काष्ठा dma_desc *p, अचिन्हित पूर्णांक *len)
अणु
	*len = le32_to_cpu(p->des2) & RDES2_HL;
पूर्ण

अटल व्योम dwmac4_set_sec_addr(काष्ठा dma_desc *p, dma_addr_t addr, bool buf2_valid)
अणु
	p->des2 = cpu_to_le32(lower_32_bits(addr));
	p->des3 = cpu_to_le32(upper_32_bits(addr));

	अगर (buf2_valid)
		p->des3 |= cpu_to_le32(RDES3_BUFFER2_VALID_ADDR);
	अन्यथा
		p->des3 &= cpu_to_le32(~RDES3_BUFFER2_VALID_ADDR);
पूर्ण

अटल व्योम dwmac4_set_tbs(काष्ठा dma_edesc *p, u32 sec, u32 nsec)
अणु
	p->des4 = cpu_to_le32((sec & TDES4_LT) | TDES4_LTV);
	p->des5 = cpu_to_le32(nsec & TDES5_LT);
	p->des6 = 0;
	p->des7 = 0;
पूर्ण

स्थिर काष्ठा sपंचांगmac_desc_ops dwmac4_desc_ops = अणु
	.tx_status = dwmac4_wrback_get_tx_status,
	.rx_status = dwmac4_wrback_get_rx_status,
	.get_tx_len = dwmac4_rd_get_tx_len,
	.get_tx_owner = dwmac4_get_tx_owner,
	.set_tx_owner = dwmac4_set_tx_owner,
	.set_rx_owner = dwmac4_set_rx_owner,
	.get_tx_ls = dwmac4_get_tx_ls,
	.get_rx_frame_len = dwmac4_wrback_get_rx_frame_len,
	.enable_tx_बारtamp = dwmac4_rd_enable_tx_बारtamp,
	.get_tx_बारtamp_status = dwmac4_wrback_get_tx_बारtamp_status,
	.get_rx_बारtamp_status = dwmac4_wrback_get_rx_बारtamp_status,
	.get_बारtamp = dwmac4_get_बारtamp,
	.set_tx_ic = dwmac4_rd_set_tx_ic,
	.prepare_tx_desc = dwmac4_rd_prepare_tx_desc,
	.prepare_tso_tx_desc = dwmac4_rd_prepare_tso_tx_desc,
	.release_tx_desc = dwmac4_release_tx_desc,
	.init_rx_desc = dwmac4_rd_init_rx_desc,
	.init_tx_desc = dwmac4_rd_init_tx_desc,
	.display_ring = dwmac4_display_ring,
	.set_mss = dwmac4_set_mss_ctxt,
	.get_addr = dwmac4_get_addr,
	.set_addr = dwmac4_set_addr,
	.clear = dwmac4_clear,
	.set_sarc = dwmac4_set_sarc,
	.set_vlan_tag = dwmac4_set_vlan_tag,
	.set_vlan = dwmac4_set_vlan,
	.get_rx_header_len = dwmac4_get_rx_header_len,
	.set_sec_addr = dwmac4_set_sec_addr,
	.set_tbs = dwmac4_set_tbs,
पूर्ण;

स्थिर काष्ठा sपंचांगmac_mode_ops dwmac4_ring_mode_ops = अणु
	.set_16kib_bfsize = set_16kib_bfsize,
पूर्ण;
