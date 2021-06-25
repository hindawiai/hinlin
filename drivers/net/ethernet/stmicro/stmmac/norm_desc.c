<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*******************************************************************************
  This contains the functions to handle the normal descriptors.

  Copyright (C) 2007-2009  STMicroelectronics Ltd


  Author: Giuseppe Cavallaro <peppe.cavallaro@st.com>
*******************************************************************************/

#समावेश <linux/sपंचांगmac.h>
#समावेश "common.h"
#समावेश "descs_com.h"

अटल पूर्णांक ndesc_get_tx_status(व्योम *data, काष्ठा sपंचांगmac_extra_stats *x,
			       काष्ठा dma_desc *p, व्योम __iomem *ioaddr)
अणु
	काष्ठा net_device_stats *stats = (काष्ठा net_device_stats *)data;
	अचिन्हित पूर्णांक tdes0 = le32_to_cpu(p->des0);
	अचिन्हित पूर्णांक tdes1 = le32_to_cpu(p->des1);
	पूर्णांक ret = tx_करोne;

	/* Get tx owner first */
	अगर (unlikely(tdes0 & TDES0_OWN))
		वापस tx_dma_own;

	/* Verअगरy tx error by looking at the last segment. */
	अगर (likely(!(tdes1 & TDES1_LAST_SEGMENT)))
		वापस tx_not_ls;

	अगर (unlikely(tdes0 & TDES0_ERROR_SUMMARY)) अणु
		अगर (unlikely(tdes0 & TDES0_UNDERFLOW_ERROR)) अणु
			x->tx_underflow++;
			stats->tx_fअगरo_errors++;
		पूर्ण
		अगर (unlikely(tdes0 & TDES0_NO_CARRIER)) अणु
			x->tx_carrier++;
			stats->tx_carrier_errors++;
		पूर्ण
		अगर (unlikely(tdes0 & TDES0_LOSS_CARRIER)) अणु
			x->tx_losscarrier++;
			stats->tx_carrier_errors++;
		पूर्ण
		अगर (unlikely((tdes0 & TDES0_EXCESSIVE_DEFERRAL) ||
			     (tdes0 & TDES0_EXCESSIVE_COLLISIONS) ||
			     (tdes0 & TDES0_LATE_COLLISION))) अणु
			अचिन्हित पूर्णांक collisions;

			collisions = (tdes0 & TDES0_COLLISION_COUNT_MASK) >> 3;
			stats->collisions += collisions;
		पूर्ण
		ret = tx_err;
	पूर्ण

	अगर (tdes0 & TDES0_VLAN_FRAME)
		x->tx_vlan++;

	अगर (unlikely(tdes0 & TDES0_DEFERRED))
		x->tx_deferred++;

	वापस ret;
पूर्ण

अटल पूर्णांक ndesc_get_tx_len(काष्ठा dma_desc *p)
अणु
	वापस (le32_to_cpu(p->des1) & RDES1_BUFFER1_SIZE_MASK);
पूर्ण

/* This function verअगरies अगर each incoming frame has some errors
 * and, अगर required, updates the multicast statistics.
 * In हाल of success, it वापसs good_frame because the GMAC device
 * is supposed to be able to compute the csum in HW. */
अटल पूर्णांक ndesc_get_rx_status(व्योम *data, काष्ठा sपंचांगmac_extra_stats *x,
			       काष्ठा dma_desc *p)
अणु
	पूर्णांक ret = good_frame;
	अचिन्हित पूर्णांक rdes0 = le32_to_cpu(p->des0);
	काष्ठा net_device_stats *stats = (काष्ठा net_device_stats *)data;

	अगर (unlikely(rdes0 & RDES0_OWN))
		वापस dma_own;

	अगर (unlikely(!(rdes0 & RDES0_LAST_DESCRIPTOR))) अणु
		stats->rx_length_errors++;
		वापस discard_frame;
	पूर्ण

	अगर (unlikely(rdes0 & RDES0_ERROR_SUMMARY)) अणु
		अगर (unlikely(rdes0 & RDES0_DESCRIPTOR_ERROR))
			x->rx_desc++;
		अगर (unlikely(rdes0 & RDES0_SA_FILTER_FAIL))
			x->sa_filter_fail++;
		अगर (unlikely(rdes0 & RDES0_OVERFLOW_ERROR))
			x->overflow_error++;
		अगर (unlikely(rdes0 & RDES0_IPC_CSUM_ERROR))
			x->ipc_csum_error++;
		अगर (unlikely(rdes0 & RDES0_COLLISION)) अणु
			x->rx_collision++;
			stats->collisions++;
		पूर्ण
		अगर (unlikely(rdes0 & RDES0_CRC_ERROR)) अणु
			x->rx_crc_errors++;
			stats->rx_crc_errors++;
		पूर्ण
		ret = discard_frame;
	पूर्ण
	अगर (unlikely(rdes0 & RDES0_DRIBBLING))
		x->dribbling_bit++;

	अगर (unlikely(rdes0 & RDES0_LENGTH_ERROR)) अणु
		x->rx_length++;
		ret = discard_frame;
	पूर्ण
	अगर (unlikely(rdes0 & RDES0_MII_ERROR)) अणु
		x->rx_mii++;
		ret = discard_frame;
	पूर्ण
#अगर_घोषित STMMAC_VLAN_TAG_USED
	अगर (rdes0 & RDES0_VLAN_TAG)
		x->vlan_tag++;
#पूर्ण_अगर
	वापस ret;
पूर्ण

अटल व्योम ndesc_init_rx_desc(काष्ठा dma_desc *p, पूर्णांक disable_rx_ic, पूर्णांक mode,
			       पूर्णांक end, पूर्णांक bfsize)
अणु
	पूर्णांक bfsize1;

	p->des0 |= cpu_to_le32(RDES0_OWN);

	bfsize1 = min(bfsize, BUF_SIZE_2KiB - 1);
	p->des1 |= cpu_to_le32(bfsize1 & RDES1_BUFFER1_SIZE_MASK);

	अगर (mode == STMMAC_CHAIN_MODE)
		ndesc_rx_set_on_chain(p, end);
	अन्यथा
		ndesc_rx_set_on_ring(p, end, bfsize);

	अगर (disable_rx_ic)
		p->des1 |= cpu_to_le32(RDES1_DISABLE_IC);
पूर्ण

अटल व्योम ndesc_init_tx_desc(काष्ठा dma_desc *p, पूर्णांक mode, पूर्णांक end)
अणु
	p->des0 &= cpu_to_le32(~TDES0_OWN);
	अगर (mode == STMMAC_CHAIN_MODE)
		ndesc_tx_set_on_chain(p);
	अन्यथा
		ndesc_end_tx_desc_on_ring(p, end);
पूर्ण

अटल पूर्णांक ndesc_get_tx_owner(काष्ठा dma_desc *p)
अणु
	वापस (le32_to_cpu(p->des0) & TDES0_OWN) >> 31;
पूर्ण

अटल व्योम ndesc_set_tx_owner(काष्ठा dma_desc *p)
अणु
	p->des0 |= cpu_to_le32(TDES0_OWN);
पूर्ण

अटल व्योम ndesc_set_rx_owner(काष्ठा dma_desc *p, पूर्णांक disable_rx_ic)
अणु
	p->des0 |= cpu_to_le32(RDES0_OWN);
पूर्ण

अटल पूर्णांक ndesc_get_tx_ls(काष्ठा dma_desc *p)
अणु
	वापस (le32_to_cpu(p->des1) & TDES1_LAST_SEGMENT) >> 30;
पूर्ण

अटल व्योम ndesc_release_tx_desc(काष्ठा dma_desc *p, पूर्णांक mode)
अणु
	पूर्णांक ter = (le32_to_cpu(p->des1) & TDES1_END_RING) >> 25;

	स_रखो(p, 0, दुरत्व(काष्ठा dma_desc, des2));
	अगर (mode == STMMAC_CHAIN_MODE)
		ndesc_tx_set_on_chain(p);
	अन्यथा
		ndesc_end_tx_desc_on_ring(p, ter);
पूर्ण

अटल व्योम ndesc_prepare_tx_desc(काष्ठा dma_desc *p, पूर्णांक is_fs, पूर्णांक len,
				  bool csum_flag, पूर्णांक mode, bool tx_own,
				  bool ls, अचिन्हित पूर्णांक tot_pkt_len)
अणु
	अचिन्हित पूर्णांक tdes1 = le32_to_cpu(p->des1);

	अगर (is_fs)
		tdes1 |= TDES1_FIRST_SEGMENT;
	अन्यथा
		tdes1 &= ~TDES1_FIRST_SEGMENT;

	अगर (likely(csum_flag))
		tdes1 |= (TX_CIC_FULL) << TDES1_CHECKSUM_INSERTION_SHIFT;
	अन्यथा
		tdes1 &= ~(TX_CIC_FULL << TDES1_CHECKSUM_INSERTION_SHIFT);

	अगर (ls)
		tdes1 |= TDES1_LAST_SEGMENT;

	p->des1 = cpu_to_le32(tdes1);

	अगर (mode == STMMAC_CHAIN_MODE)
		norm_set_tx_desc_len_on_chain(p, len);
	अन्यथा
		norm_set_tx_desc_len_on_ring(p, len);

	अगर (tx_own)
		p->des0 |= cpu_to_le32(TDES0_OWN);
पूर्ण

अटल व्योम ndesc_set_tx_ic(काष्ठा dma_desc *p)
अणु
	p->des1 |= cpu_to_le32(TDES1_INTERRUPT);
पूर्ण

अटल पूर्णांक ndesc_get_rx_frame_len(काष्ठा dma_desc *p, पूर्णांक rx_coe_type)
अणु
	अचिन्हित पूर्णांक csum = 0;

	/* The type-1 checksum offload engines append the checksum at
	 * the end of frame and the two bytes of checksum are added in
	 * the length.
	 * Adjust क्रम that in the framelen क्रम type-1 checksum offload
	 * engines
	 */
	अगर (rx_coe_type == STMMAC_RX_COE_TYPE1)
		csum = 2;

	वापस (((le32_to_cpu(p->des0) & RDES0_FRAME_LEN_MASK)
				>> RDES0_FRAME_LEN_SHIFT) -
		csum);

पूर्ण

अटल व्योम ndesc_enable_tx_बारtamp(काष्ठा dma_desc *p)
अणु
	p->des1 |= cpu_to_le32(TDES1_TIME_STAMP_ENABLE);
पूर्ण

अटल पूर्णांक ndesc_get_tx_बारtamp_status(काष्ठा dma_desc *p)
अणु
	वापस (le32_to_cpu(p->des0) & TDES0_TIME_STAMP_STATUS) >> 17;
पूर्ण

अटल व्योम ndesc_get_बारtamp(व्योम *desc, u32 ats, u64 *ts)
अणु
	काष्ठा dma_desc *p = (काष्ठा dma_desc *)desc;
	u64 ns;

	ns = le32_to_cpu(p->des2);
	/* convert high/sec समय stamp value to nanosecond */
	ns += le32_to_cpu(p->des3) * 1000000000ULL;

	*ts = ns;
पूर्ण

अटल पूर्णांक ndesc_get_rx_बारtamp_status(व्योम *desc, व्योम *next_desc, u32 ats)
अणु
	काष्ठा dma_desc *p = (काष्ठा dma_desc *)desc;

	अगर ((le32_to_cpu(p->des2) == 0xffffffff) &&
	    (le32_to_cpu(p->des3) == 0xffffffff))
		/* बारtamp is corrupted, hence करोn't store it */
		वापस 0;
	अन्यथा
		वापस 1;
पूर्ण

अटल व्योम ndesc_display_ring(व्योम *head, अचिन्हित पूर्णांक size, bool rx,
			       dma_addr_t dma_rx_phy, अचिन्हित पूर्णांक desc_size)
अणु
	काष्ठा dma_desc *p = (काष्ठा dma_desc *)head;
	dma_addr_t dma_addr;
	पूर्णांक i;

	pr_info("%s descriptor ring:\n", rx ? "RX" : "TX");

	क्रम (i = 0; i < size; i++) अणु
		u64 x;
		dma_addr = dma_rx_phy + i * माप(*p);

		x = *(u64 *)p;
		pr_info("%03d [%pad]: 0x%x 0x%x 0x%x 0x%x",
			i, &dma_addr,
			(अचिन्हित पूर्णांक)x, (अचिन्हित पूर्णांक)(x >> 32),
			p->des2, p->des3);
		p++;
	पूर्ण
	pr_info("\n");
पूर्ण

अटल व्योम ndesc_get_addr(काष्ठा dma_desc *p, अचिन्हित पूर्णांक *addr)
अणु
	*addr = le32_to_cpu(p->des2);
पूर्ण

अटल व्योम ndesc_set_addr(काष्ठा dma_desc *p, dma_addr_t addr)
अणु
	p->des2 = cpu_to_le32(addr);
पूर्ण

अटल व्योम ndesc_clear(काष्ठा dma_desc *p)
अणु
	p->des2 = 0;
पूर्ण

स्थिर काष्ठा sपंचांगmac_desc_ops ndesc_ops = अणु
	.tx_status = ndesc_get_tx_status,
	.rx_status = ndesc_get_rx_status,
	.get_tx_len = ndesc_get_tx_len,
	.init_rx_desc = ndesc_init_rx_desc,
	.init_tx_desc = ndesc_init_tx_desc,
	.get_tx_owner = ndesc_get_tx_owner,
	.release_tx_desc = ndesc_release_tx_desc,
	.prepare_tx_desc = ndesc_prepare_tx_desc,
	.set_tx_ic = ndesc_set_tx_ic,
	.get_tx_ls = ndesc_get_tx_ls,
	.set_tx_owner = ndesc_set_tx_owner,
	.set_rx_owner = ndesc_set_rx_owner,
	.get_rx_frame_len = ndesc_get_rx_frame_len,
	.enable_tx_बारtamp = ndesc_enable_tx_बारtamp,
	.get_tx_बारtamp_status = ndesc_get_tx_बारtamp_status,
	.get_बारtamp = ndesc_get_बारtamp,
	.get_rx_बारtamp_status = ndesc_get_rx_बारtamp_status,
	.display_ring = ndesc_display_ring,
	.get_addr = ndesc_get_addr,
	.set_addr = ndesc_set_addr,
	.clear = ndesc_clear,
पूर्ण;
