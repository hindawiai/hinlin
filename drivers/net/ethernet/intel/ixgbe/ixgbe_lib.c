<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#समावेश "ixgbe.h"
#समावेश "ixgbe_sriov.h"

#अगर_घोषित CONFIG_IXGBE_DCB
/**
 * ixgbe_cache_ring_dcb_sriov - Descriptor ring to रेजिस्टर mapping क्रम SR-IOV
 * @adapter: board निजी काष्ठाure to initialize
 *
 * Cache the descriptor ring offsets क्रम SR-IOV to the asचिन्हित rings.  It
 * will also try to cache the proper offsets अगर RSS/FCoE are enabled aदीर्घ
 * with VMDq.
 *
 **/
अटल bool ixgbe_cache_ring_dcb_sriov(काष्ठा ixgbe_adapter *adapter)
अणु
#अगर_घोषित IXGBE_FCOE
	काष्ठा ixgbe_ring_feature *fcoe = &adapter->ring_feature[RING_F_FCOE];
#पूर्ण_अगर /* IXGBE_FCOE */
	काष्ठा ixgbe_ring_feature *vmdq = &adapter->ring_feature[RING_F_VMDQ];
	पूर्णांक i;
	u16 reg_idx, pool;
	u8 tcs = adapter->hw_tcs;

	/* verअगरy we have DCB queueing enabled beक्रमe proceeding */
	अगर (tcs <= 1)
		वापस false;

	/* verअगरy we have VMDq enabled beक्रमe proceeding */
	अगर (!(adapter->flags & IXGBE_FLAG_SRIOV_ENABLED))
		वापस false;

	/* start at VMDq रेजिस्टर offset क्रम SR-IOV enabled setups */
	reg_idx = vmdq->offset * __ALIGN_MASK(1, ~vmdq->mask);
	क्रम (i = 0, pool = 0; i < adapter->num_rx_queues; i++, reg_idx++) अणु
		/* If we are greater than indices move to next pool */
		अगर ((reg_idx & ~vmdq->mask) >= tcs) अणु
			pool++;
			reg_idx = __ALIGN_MASK(reg_idx, ~vmdq->mask);
		पूर्ण
		adapter->rx_ring[i]->reg_idx = reg_idx;
		adapter->rx_ring[i]->netdev = pool ? शून्य : adapter->netdev;
	पूर्ण

	reg_idx = vmdq->offset * __ALIGN_MASK(1, ~vmdq->mask);
	क्रम (i = 0; i < adapter->num_tx_queues; i++, reg_idx++) अणु
		/* If we are greater than indices move to next pool */
		अगर ((reg_idx & ~vmdq->mask) >= tcs)
			reg_idx = __ALIGN_MASK(reg_idx, ~vmdq->mask);
		adapter->tx_ring[i]->reg_idx = reg_idx;
	पूर्ण

#अगर_घोषित IXGBE_FCOE
	/* nothing to करो अगर FCoE is disabled */
	अगर (!(adapter->flags & IXGBE_FLAG_FCOE_ENABLED))
		वापस true;

	/* The work is alपढ़ोy करोne अगर the FCoE ring is shared */
	अगर (fcoe->offset < tcs)
		वापस true;

	/* The FCoE rings exist separately, we need to move their reg_idx */
	अगर (fcoe->indices) अणु
		u16 queues_per_pool = __ALIGN_MASK(1, ~vmdq->mask);
		u8 fcoe_tc = ixgbe_fcoe_get_tc(adapter);

		reg_idx = (vmdq->offset + vmdq->indices) * queues_per_pool;
		क्रम (i = fcoe->offset; i < adapter->num_rx_queues; i++) अणु
			reg_idx = __ALIGN_MASK(reg_idx, ~vmdq->mask) + fcoe_tc;
			adapter->rx_ring[i]->reg_idx = reg_idx;
			adapter->rx_ring[i]->netdev = adapter->netdev;
			reg_idx++;
		पूर्ण

		reg_idx = (vmdq->offset + vmdq->indices) * queues_per_pool;
		क्रम (i = fcoe->offset; i < adapter->num_tx_queues; i++) अणु
			reg_idx = __ALIGN_MASK(reg_idx, ~vmdq->mask) + fcoe_tc;
			adapter->tx_ring[i]->reg_idx = reg_idx;
			reg_idx++;
		पूर्ण
	पूर्ण

#पूर्ण_अगर /* IXGBE_FCOE */
	वापस true;
पूर्ण

/* ixgbe_get_first_reg_idx - Return first रेजिस्टर index associated with ring */
अटल व्योम ixgbe_get_first_reg_idx(काष्ठा ixgbe_adapter *adapter, u8 tc,
				    अचिन्हित पूर्णांक *tx, अचिन्हित पूर्णांक *rx)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u8 num_tcs = adapter->hw_tcs;

	*tx = 0;
	*rx = 0;

	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_82598EB:
		/* TxQs/TC: 4	RxQs/TC: 8 */
		*tx = tc << 2; /* 0, 4,  8, 12, 16, 20, 24, 28 */
		*rx = tc << 3; /* 0, 8, 16, 24, 32, 40, 48, 56 */
		अवरोध;
	हाल ixgbe_mac_82599EB:
	हाल ixgbe_mac_X540:
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		अगर (num_tcs > 4) अणु
			/*
			 * TCs    : TC0/1 TC2/3 TC4-7
			 * TxQs/TC:    32    16     8
			 * RxQs/TC:    16    16    16
			 */
			*rx = tc << 4;
			अगर (tc < 3)
				*tx = tc << 5;		/*   0,  32,  64 */
			अन्यथा अगर (tc < 5)
				*tx = (tc + 2) << 4;	/*  80,  96 */
			अन्यथा
				*tx = (tc + 8) << 3;	/* 104, 112, 120 */
		पूर्ण अन्यथा अणु
			/*
			 * TCs    : TC0 TC1 TC2/3
			 * TxQs/TC:  64  32    16
			 * RxQs/TC:  32  32    32
			 */
			*rx = tc << 5;
			अगर (tc < 2)
				*tx = tc << 6;		/*  0,  64 */
			अन्यथा
				*tx = (tc + 4) << 4;	/* 96, 112 */
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * ixgbe_cache_ring_dcb - Descriptor ring to रेजिस्टर mapping क्रम DCB
 * @adapter: board निजी काष्ठाure to initialize
 *
 * Cache the descriptor ring offsets क्रम DCB to the asचिन्हित rings.
 *
 **/
अटल bool ixgbe_cache_ring_dcb(काष्ठा ixgbe_adapter *adapter)
अणु
	u8 num_tcs = adapter->hw_tcs;
	अचिन्हित पूर्णांक tx_idx, rx_idx;
	पूर्णांक tc, offset, rss_i, i;

	/* verअगरy we have DCB queueing enabled beक्रमe proceeding */
	अगर (num_tcs <= 1)
		वापस false;

	rss_i = adapter->ring_feature[RING_F_RSS].indices;

	क्रम (tc = 0, offset = 0; tc < num_tcs; tc++, offset += rss_i) अणु
		ixgbe_get_first_reg_idx(adapter, tc, &tx_idx, &rx_idx);
		क्रम (i = 0; i < rss_i; i++, tx_idx++, rx_idx++) अणु
			adapter->tx_ring[offset + i]->reg_idx = tx_idx;
			adapter->rx_ring[offset + i]->reg_idx = rx_idx;
			adapter->rx_ring[offset + i]->netdev = adapter->netdev;
			adapter->tx_ring[offset + i]->dcb_tc = tc;
			adapter->rx_ring[offset + i]->dcb_tc = tc;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

#पूर्ण_अगर
/**
 * ixgbe_cache_ring_sriov - Descriptor ring to रेजिस्टर mapping क्रम sriov
 * @adapter: board निजी काष्ठाure to initialize
 *
 * SR-IOV करोesn't use any descriptor rings but changes the शेष अगर
 * no other mapping is used.
 *
 */
अटल bool ixgbe_cache_ring_sriov(काष्ठा ixgbe_adapter *adapter)
अणु
#अगर_घोषित IXGBE_FCOE
	काष्ठा ixgbe_ring_feature *fcoe = &adapter->ring_feature[RING_F_FCOE];
#पूर्ण_अगर /* IXGBE_FCOE */
	काष्ठा ixgbe_ring_feature *vmdq = &adapter->ring_feature[RING_F_VMDQ];
	काष्ठा ixgbe_ring_feature *rss = &adapter->ring_feature[RING_F_RSS];
	u16 reg_idx, pool;
	पूर्णांक i;

	/* only proceed अगर VMDq is enabled */
	अगर (!(adapter->flags & IXGBE_FLAG_VMDQ_ENABLED))
		वापस false;

	/* start at VMDq रेजिस्टर offset क्रम SR-IOV enabled setups */
	pool = 0;
	reg_idx = vmdq->offset * __ALIGN_MASK(1, ~vmdq->mask);
	क्रम (i = 0; i < adapter->num_rx_queues; i++, reg_idx++) अणु
#अगर_घोषित IXGBE_FCOE
		/* Allow first FCoE queue to be mapped as RSS */
		अगर (fcoe->offset && (i > fcoe->offset))
			अवरोध;
#पूर्ण_अगर
		/* If we are greater than indices move to next pool */
		अगर ((reg_idx & ~vmdq->mask) >= rss->indices) अणु
			pool++;
			reg_idx = __ALIGN_MASK(reg_idx, ~vmdq->mask);
		पूर्ण
		adapter->rx_ring[i]->reg_idx = reg_idx;
		adapter->rx_ring[i]->netdev = pool ? शून्य : adapter->netdev;
	पूर्ण

#अगर_घोषित IXGBE_FCOE
	/* FCoE uses a linear block of queues so just assigning 1:1 */
	क्रम (; i < adapter->num_rx_queues; i++, reg_idx++) अणु
		adapter->rx_ring[i]->reg_idx = reg_idx;
		adapter->rx_ring[i]->netdev = adapter->netdev;
	पूर्ण

#पूर्ण_अगर
	reg_idx = vmdq->offset * __ALIGN_MASK(1, ~vmdq->mask);
	क्रम (i = 0; i < adapter->num_tx_queues; i++, reg_idx++) अणु
#अगर_घोषित IXGBE_FCOE
		/* Allow first FCoE queue to be mapped as RSS */
		अगर (fcoe->offset && (i > fcoe->offset))
			अवरोध;
#पूर्ण_अगर
		/* If we are greater than indices move to next pool */
		अगर ((reg_idx & rss->mask) >= rss->indices)
			reg_idx = __ALIGN_MASK(reg_idx, ~vmdq->mask);
		adapter->tx_ring[i]->reg_idx = reg_idx;
	पूर्ण

#अगर_घोषित IXGBE_FCOE
	/* FCoE uses a linear block of queues so just assigning 1:1 */
	क्रम (; i < adapter->num_tx_queues; i++, reg_idx++)
		adapter->tx_ring[i]->reg_idx = reg_idx;

#पूर्ण_अगर

	वापस true;
पूर्ण

/**
 * ixgbe_cache_ring_rss - Descriptor ring to रेजिस्टर mapping क्रम RSS
 * @adapter: board निजी काष्ठाure to initialize
 *
 * Cache the descriptor ring offsets क्रम RSS to the asचिन्हित rings.
 *
 **/
अटल bool ixgbe_cache_ring_rss(काष्ठा ixgbe_adapter *adapter)
अणु
	पूर्णांक i, reg_idx;

	क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
		adapter->rx_ring[i]->reg_idx = i;
		adapter->rx_ring[i]->netdev = adapter->netdev;
	पूर्ण
	क्रम (i = 0, reg_idx = 0; i < adapter->num_tx_queues; i++, reg_idx++)
		adapter->tx_ring[i]->reg_idx = reg_idx;
	क्रम (i = 0; i < adapter->num_xdp_queues; i++, reg_idx++)
		adapter->xdp_ring[i]->reg_idx = reg_idx;

	वापस true;
पूर्ण

/**
 * ixgbe_cache_ring_रेजिस्टर - Descriptor ring to रेजिस्टर mapping
 * @adapter: board निजी काष्ठाure to initialize
 *
 * Once we know the feature-set enabled क्रम the device, we'll cache
 * the रेजिस्टर offset the descriptor ring is asचिन्हित to.
 *
 * Note, the order the various feature calls is important.  It must start with
 * the "most" features enabled at the same समय, then trickle करोwn to the
 * least amount of features turned on at once.
 **/
अटल व्योम ixgbe_cache_ring_रेजिस्टर(काष्ठा ixgbe_adapter *adapter)
अणु
	/* start with शेष हाल */
	adapter->rx_ring[0]->reg_idx = 0;
	adapter->tx_ring[0]->reg_idx = 0;

#अगर_घोषित CONFIG_IXGBE_DCB
	अगर (ixgbe_cache_ring_dcb_sriov(adapter))
		वापस;

	अगर (ixgbe_cache_ring_dcb(adapter))
		वापस;

#पूर्ण_अगर
	अगर (ixgbe_cache_ring_sriov(adapter))
		वापस;

	ixgbe_cache_ring_rss(adapter);
पूर्ण

अटल पूर्णांक ixgbe_xdp_queues(काष्ठा ixgbe_adapter *adapter)
अणु
	वापस adapter->xdp_prog ? nr_cpu_ids : 0;
पूर्ण

#घोषणा IXGBE_RSS_64Q_MASK	0x3F
#घोषणा IXGBE_RSS_16Q_MASK	0xF
#घोषणा IXGBE_RSS_8Q_MASK	0x7
#घोषणा IXGBE_RSS_4Q_MASK	0x3
#घोषणा IXGBE_RSS_2Q_MASK	0x1
#घोषणा IXGBE_RSS_DISABLED_MASK	0x0

#अगर_घोषित CONFIG_IXGBE_DCB
/**
 * ixgbe_set_dcb_sriov_queues: Allocate queues क्रम SR-IOV devices w/ DCB
 * @adapter: board निजी काष्ठाure to initialize
 *
 * When SR-IOV (Single Root IO Virtualiztion) is enabled, allocate queues
 * and VM pools where appropriate.  Also assign queues based on DCB
 * priorities and map accordingly..
 *
 **/
अटल bool ixgbe_set_dcb_sriov_queues(काष्ठा ixgbe_adapter *adapter)
अणु
	पूर्णांक i;
	u16 vmdq_i = adapter->ring_feature[RING_F_VMDQ].limit;
	u16 vmdq_m = 0;
#अगर_घोषित IXGBE_FCOE
	u16 fcoe_i = 0;
#पूर्ण_अगर
	u8 tcs = adapter->hw_tcs;

	/* verअगरy we have DCB queueing enabled beक्रमe proceeding */
	अगर (tcs <= 1)
		वापस false;

	/* verअगरy we have VMDq enabled beक्रमe proceeding */
	अगर (!(adapter->flags & IXGBE_FLAG_SRIOV_ENABLED))
		वापस false;

	/* limit VMDq instances on the PF by number of Tx queues */
	vmdq_i = min_t(u16, vmdq_i, MAX_TX_QUEUES / tcs);

	/* Add starting offset to total pool count */
	vmdq_i += adapter->ring_feature[RING_F_VMDQ].offset;

	/* 16 pools w/ 8 TC per pool */
	अगर (tcs > 4) अणु
		vmdq_i = min_t(u16, vmdq_i, 16);
		vmdq_m = IXGBE_82599_VMDQ_8Q_MASK;
	/* 32 pools w/ 4 TC per pool */
	पूर्ण अन्यथा अणु
		vmdq_i = min_t(u16, vmdq_i, 32);
		vmdq_m = IXGBE_82599_VMDQ_4Q_MASK;
	पूर्ण

#अगर_घोषित IXGBE_FCOE
	/* queues in the reमुख्यing pools are available क्रम FCoE */
	fcoe_i = (128 / __ALIGN_MASK(1, ~vmdq_m)) - vmdq_i;

#पूर्ण_अगर
	/* हटाओ the starting offset from the pool count */
	vmdq_i -= adapter->ring_feature[RING_F_VMDQ].offset;

	/* save features क्रम later use */
	adapter->ring_feature[RING_F_VMDQ].indices = vmdq_i;
	adapter->ring_feature[RING_F_VMDQ].mask = vmdq_m;

	/*
	 * We करो not support DCB, VMDq, and RSS all simultaneously
	 * so we will disable RSS since it is the lowest priority
	 */
	adapter->ring_feature[RING_F_RSS].indices = 1;
	adapter->ring_feature[RING_F_RSS].mask = IXGBE_RSS_DISABLED_MASK;

	/* disable ATR as it is not supported when VMDq is enabled */
	adapter->flags &= ~IXGBE_FLAG_Fसूची_HASH_CAPABLE;

	adapter->num_rx_pools = vmdq_i;
	adapter->num_rx_queues_per_pool = tcs;

	adapter->num_tx_queues = vmdq_i * tcs;
	adapter->num_xdp_queues = 0;
	adapter->num_rx_queues = vmdq_i * tcs;

#अगर_घोषित IXGBE_FCOE
	अगर (adapter->flags & IXGBE_FLAG_FCOE_ENABLED) अणु
		काष्ठा ixgbe_ring_feature *fcoe;

		fcoe = &adapter->ring_feature[RING_F_FCOE];

		/* limit ourselves based on feature limits */
		fcoe_i = min_t(u16, fcoe_i, fcoe->limit);

		अगर (fcoe_i) अणु
			/* alloc queues क्रम FCoE separately */
			fcoe->indices = fcoe_i;
			fcoe->offset = vmdq_i * tcs;

			/* add queues to adapter */
			adapter->num_tx_queues += fcoe_i;
			adapter->num_rx_queues += fcoe_i;
		पूर्ण अन्यथा अगर (tcs > 1) अणु
			/* use queue beदीर्घing to FcoE TC */
			fcoe->indices = 1;
			fcoe->offset = ixgbe_fcoe_get_tc(adapter);
		पूर्ण अन्यथा अणु
			adapter->flags &= ~IXGBE_FLAG_FCOE_ENABLED;

			fcoe->indices = 0;
			fcoe->offset = 0;
		पूर्ण
	पूर्ण

#पूर्ण_अगर /* IXGBE_FCOE */
	/* configure TC to queue mapping */
	क्रम (i = 0; i < tcs; i++)
		netdev_set_tc_queue(adapter->netdev, i, 1, i);

	वापस true;
पूर्ण

अटल bool ixgbe_set_dcb_queues(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा net_device *dev = adapter->netdev;
	काष्ठा ixgbe_ring_feature *f;
	पूर्णांक rss_i, rss_m, i;
	पूर्णांक tcs;

	/* Map queue offset and counts onto allocated tx queues */
	tcs = adapter->hw_tcs;

	/* verअगरy we have DCB queueing enabled beक्रमe proceeding */
	अगर (tcs <= 1)
		वापस false;

	/* determine the upper limit क्रम our current DCB mode */
	rss_i = dev->num_tx_queues / tcs;
	अगर (adapter->hw.mac.type == ixgbe_mac_82598EB) अणु
		/* 8 TC w/ 4 queues per TC */
		rss_i = min_t(u16, rss_i, 4);
		rss_m = IXGBE_RSS_4Q_MASK;
	पूर्ण अन्यथा अगर (tcs > 4) अणु
		/* 8 TC w/ 8 queues per TC */
		rss_i = min_t(u16, rss_i, 8);
		rss_m = IXGBE_RSS_8Q_MASK;
	पूर्ण अन्यथा अणु
		/* 4 TC w/ 16 queues per TC */
		rss_i = min_t(u16, rss_i, 16);
		rss_m = IXGBE_RSS_16Q_MASK;
	पूर्ण

	/* set RSS mask and indices */
	f = &adapter->ring_feature[RING_F_RSS];
	rss_i = min_t(पूर्णांक, rss_i, f->limit);
	f->indices = rss_i;
	f->mask = rss_m;

	/* disable ATR as it is not supported when multiple TCs are enabled */
	adapter->flags &= ~IXGBE_FLAG_Fसूची_HASH_CAPABLE;

#अगर_घोषित IXGBE_FCOE
	/* FCoE enabled queues require special configuration indexed
	 * by feature specअगरic indices and offset. Here we map FCoE
	 * indices onto the DCB queue pairs allowing FCoE to own
	 * configuration later.
	 */
	अगर (adapter->flags & IXGBE_FLAG_FCOE_ENABLED) अणु
		u8 tc = ixgbe_fcoe_get_tc(adapter);

		f = &adapter->ring_feature[RING_F_FCOE];
		f->indices = min_t(u16, rss_i, f->limit);
		f->offset = rss_i * tc;
	पूर्ण

#पूर्ण_अगर /* IXGBE_FCOE */
	क्रम (i = 0; i < tcs; i++)
		netdev_set_tc_queue(dev, i, rss_i, rss_i * i);

	adapter->num_tx_queues = rss_i * tcs;
	adapter->num_xdp_queues = 0;
	adapter->num_rx_queues = rss_i * tcs;

	वापस true;
पूर्ण

#पूर्ण_अगर
/**
 * ixgbe_set_sriov_queues - Allocate queues क्रम SR-IOV devices
 * @adapter: board निजी काष्ठाure to initialize
 *
 * When SR-IOV (Single Root IO Virtualiztion) is enabled, allocate queues
 * and VM pools where appropriate.  If RSS is available, then also try and
 * enable RSS and map accordingly.
 *
 **/
अटल bool ixgbe_set_sriov_queues(काष्ठा ixgbe_adapter *adapter)
अणु
	u16 vmdq_i = adapter->ring_feature[RING_F_VMDQ].limit;
	u16 vmdq_m = 0;
	u16 rss_i = adapter->ring_feature[RING_F_RSS].limit;
	u16 rss_m = IXGBE_RSS_DISABLED_MASK;
#अगर_घोषित IXGBE_FCOE
	u16 fcoe_i = 0;
#पूर्ण_अगर

	/* only proceed अगर SR-IOV is enabled */
	अगर (!(adapter->flags & IXGBE_FLAG_SRIOV_ENABLED))
		वापस false;

	/* limit l2fwd RSS based on total Tx queue limit */
	rss_i = min_t(u16, rss_i, MAX_TX_QUEUES / vmdq_i);

	/* Add starting offset to total pool count */
	vmdq_i += adapter->ring_feature[RING_F_VMDQ].offset;

	/* द्विगुन check we are limited to maximum pools */
	vmdq_i = min_t(u16, IXGBE_MAX_VMDQ_INDICES, vmdq_i);

	/* 64 pool mode with 2 queues per pool */
	अगर (vmdq_i > 32) अणु
		vmdq_m = IXGBE_82599_VMDQ_2Q_MASK;
		rss_m = IXGBE_RSS_2Q_MASK;
		rss_i = min_t(u16, rss_i, 2);
	/* 32 pool mode with up to 4 queues per pool */
	पूर्ण अन्यथा अणु
		vmdq_m = IXGBE_82599_VMDQ_4Q_MASK;
		rss_m = IXGBE_RSS_4Q_MASK;
		/* We can support 4, 2, or 1 queues */
		rss_i = (rss_i > 3) ? 4 : (rss_i > 1) ? 2 : 1;
	पूर्ण

#अगर_घोषित IXGBE_FCOE
	/* queues in the reमुख्यing pools are available क्रम FCoE */
	fcoe_i = 128 - (vmdq_i * __ALIGN_MASK(1, ~vmdq_m));

#पूर्ण_अगर
	/* हटाओ the starting offset from the pool count */
	vmdq_i -= adapter->ring_feature[RING_F_VMDQ].offset;

	/* save features क्रम later use */
	adapter->ring_feature[RING_F_VMDQ].indices = vmdq_i;
	adapter->ring_feature[RING_F_VMDQ].mask = vmdq_m;

	/* limit RSS based on user input and save क्रम later use */
	adapter->ring_feature[RING_F_RSS].indices = rss_i;
	adapter->ring_feature[RING_F_RSS].mask = rss_m;

	adapter->num_rx_pools = vmdq_i;
	adapter->num_rx_queues_per_pool = rss_i;

	adapter->num_rx_queues = vmdq_i * rss_i;
	adapter->num_tx_queues = vmdq_i * rss_i;
	adapter->num_xdp_queues = 0;

	/* disable ATR as it is not supported when VMDq is enabled */
	adapter->flags &= ~IXGBE_FLAG_Fसूची_HASH_CAPABLE;

#अगर_घोषित IXGBE_FCOE
	/*
	 * FCoE can use rings from adjacent buffers to allow RSS
	 * like behavior.  To account क्रम this we need to add the
	 * FCoE indices to the total ring count.
	 */
	अगर (adapter->flags & IXGBE_FLAG_FCOE_ENABLED) अणु
		काष्ठा ixgbe_ring_feature *fcoe;

		fcoe = &adapter->ring_feature[RING_F_FCOE];

		/* limit ourselves based on feature limits */
		fcoe_i = min_t(u16, fcoe_i, fcoe->limit);

		अगर (vmdq_i > 1 && fcoe_i) अणु
			/* alloc queues क्रम FCoE separately */
			fcoe->indices = fcoe_i;
			fcoe->offset = vmdq_i * rss_i;
		पूर्ण अन्यथा अणु
			/* merge FCoE queues with RSS queues */
			fcoe_i = min_t(u16, fcoe_i + rss_i, num_online_cpus());

			/* limit indices to rss_i अगर MSI-X is disabled */
			अगर (!(adapter->flags & IXGBE_FLAG_MSIX_ENABLED))
				fcoe_i = rss_i;

			/* attempt to reserve some queues क्रम just FCoE */
			fcoe->indices = min_t(u16, fcoe_i, fcoe->limit);
			fcoe->offset = fcoe_i - fcoe->indices;

			fcoe_i -= rss_i;
		पूर्ण

		/* add queues to adapter */
		adapter->num_tx_queues += fcoe_i;
		adapter->num_rx_queues += fcoe_i;
	पूर्ण

#पूर्ण_अगर
	/* To support macvlan offload we have to use num_tc to
	 * restrict the queues that can be used by the device.
	 * By करोing this we can aव्योम reporting a false number of
	 * queues.
	 */
	अगर (vmdq_i > 1)
		netdev_set_num_tc(adapter->netdev, 1);

	/* populate TC0 क्रम use by pool 0 */
	netdev_set_tc_queue(adapter->netdev, 0,
			    adapter->num_rx_queues_per_pool, 0);

	वापस true;
पूर्ण

/**
 * ixgbe_set_rss_queues - Allocate queues क्रम RSS
 * @adapter: board निजी काष्ठाure to initialize
 *
 * This is our "base" multiqueue mode.  RSS (Receive Side Scaling) will try
 * to allocate one Rx queue per CPU, and अगर available, one Tx queue per CPU.
 *
 **/
अटल bool ixgbe_set_rss_queues(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा ixgbe_ring_feature *f;
	u16 rss_i;

	/* set mask क्रम 16 queue limit of RSS */
	f = &adapter->ring_feature[RING_F_RSS];
	rss_i = f->limit;

	f->indices = rss_i;

	अगर (hw->mac.type < ixgbe_mac_X550)
		f->mask = IXGBE_RSS_16Q_MASK;
	अन्यथा
		f->mask = IXGBE_RSS_64Q_MASK;

	/* disable ATR by शेष, it will be configured below */
	adapter->flags &= ~IXGBE_FLAG_Fसूची_HASH_CAPABLE;

	/*
	 * Use Flow Director in addition to RSS to ensure the best
	 * distribution of flows across cores, even when an Fसूची flow
	 * isn't matched.
	 */
	अगर (rss_i > 1 && adapter->atr_sample_rate) अणु
		f = &adapter->ring_feature[RING_F_Fसूची];

		rss_i = f->indices = f->limit;

		अगर (!(adapter->flags & IXGBE_FLAG_Fसूची_PERFECT_CAPABLE))
			adapter->flags |= IXGBE_FLAG_Fसूची_HASH_CAPABLE;
	पूर्ण

#अगर_घोषित IXGBE_FCOE
	/*
	 * FCoE can exist on the same rings as standard network traffic
	 * however it is preferred to aव्योम that अगर possible.  In order
	 * to get the best perक्रमmance we allocate as many FCoE queues
	 * as we can and we place them at the end of the ring array to
	 * aव्योम sharing queues with standard RSS on प्रणालीs with 24 or
	 * more CPUs.
	 */
	अगर (adapter->flags & IXGBE_FLAG_FCOE_ENABLED) अणु
		काष्ठा net_device *dev = adapter->netdev;
		u16 fcoe_i;

		f = &adapter->ring_feature[RING_F_FCOE];

		/* merge FCoE queues with RSS queues */
		fcoe_i = min_t(u16, f->limit + rss_i, num_online_cpus());
		fcoe_i = min_t(u16, fcoe_i, dev->num_tx_queues);

		/* limit indices to rss_i अगर MSI-X is disabled */
		अगर (!(adapter->flags & IXGBE_FLAG_MSIX_ENABLED))
			fcoe_i = rss_i;

		/* attempt to reserve some queues क्रम just FCoE */
		f->indices = min_t(u16, fcoe_i, f->limit);
		f->offset = fcoe_i - f->indices;
		rss_i = max_t(u16, fcoe_i, rss_i);
	पूर्ण

#पूर्ण_अगर /* IXGBE_FCOE */
	adapter->num_rx_queues = rss_i;
	adapter->num_tx_queues = rss_i;
	adapter->num_xdp_queues = ixgbe_xdp_queues(adapter);

	वापस true;
पूर्ण

/**
 * ixgbe_set_num_queues - Allocate queues क्रम device, feature dependent
 * @adapter: board निजी काष्ठाure to initialize
 *
 * This is the top level queue allocation routine.  The order here is very
 * important, starting with the "most" number of features turned on at once,
 * and ending with the smallest set of features.  This way large combinations
 * can be allocated अगर they're turned on, and smaller combinations are the
 * fallthrough conditions.
 *
 **/
अटल व्योम ixgbe_set_num_queues(काष्ठा ixgbe_adapter *adapter)
अणु
	/* Start with base हाल */
	adapter->num_rx_queues = 1;
	adapter->num_tx_queues = 1;
	adapter->num_xdp_queues = 0;
	adapter->num_rx_pools = 1;
	adapter->num_rx_queues_per_pool = 1;

#अगर_घोषित CONFIG_IXGBE_DCB
	अगर (ixgbe_set_dcb_sriov_queues(adapter))
		वापस;

	अगर (ixgbe_set_dcb_queues(adapter))
		वापस;

#पूर्ण_अगर
	अगर (ixgbe_set_sriov_queues(adapter))
		वापस;

	ixgbe_set_rss_queues(adapter);
पूर्ण

/**
 * ixgbe_acquire_msix_vectors - acquire MSI-X vectors
 * @adapter: board निजी काष्ठाure
 *
 * Attempts to acquire a suitable range of MSI-X vector पूर्णांकerrupts. Will
 * वापस a negative error code अगर unable to acquire MSI-X vectors क्रम any
 * reason.
 */
अटल पूर्णांक ixgbe_acquire_msix_vectors(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक i, vectors, vector_threshold;

	/* We start by asking क्रम one vector per queue pair with XDP queues
	 * being stacked with TX queues.
	 */
	vectors = max(adapter->num_rx_queues, adapter->num_tx_queues);
	vectors = max(vectors, adapter->num_xdp_queues);

	/* It is easy to be greedy क्रम MSI-X vectors. However, it really
	 * करोesn't do much good if we have a lot more vectors than CPUs. We'll
	 * be somewhat conservative and only ask क्रम (roughly) the same number
	 * of vectors as there are CPUs.
	 */
	vectors = min_t(पूर्णांक, vectors, num_online_cpus());

	/* Some vectors are necessary क्रम non-queue पूर्णांकerrupts */
	vectors += NON_Q_VECTORS;

	/* Hardware can only support a maximum of hw.mac->max_msix_vectors.
	 * With features such as RSS and VMDq, we can easily surpass the
	 * number of Rx and Tx descriptor queues supported by our device.
	 * Thus, we cap the maximum in the rare हालs where the CPU count also
	 * exceeds our vector limit
	 */
	vectors = min_t(पूर्णांक, vectors, hw->mac.max_msix_vectors);

	/* We want a minimum of two MSI-X vectors क्रम (1) a TxQ[0] + RxQ[0]
	 * handler, and (2) an Other (Link Status Change, etc.) handler.
	 */
	vector_threshold = MIN_MSIX_COUNT;

	adapter->msix_entries = kसुस्मृति(vectors,
					माप(काष्ठा msix_entry),
					GFP_KERNEL);
	अगर (!adapter->msix_entries)
		वापस -ENOMEM;

	क्रम (i = 0; i < vectors; i++)
		adapter->msix_entries[i].entry = i;

	vectors = pci_enable_msix_range(adapter->pdev, adapter->msix_entries,
					vector_threshold, vectors);

	अगर (vectors < 0) अणु
		/* A negative count of allocated vectors indicates an error in
		 * acquiring within the specअगरied range of MSI-X vectors
		 */
		e_dev_warn("Failed to allocate MSI-X interrupts. Err: %d\n",
			   vectors);

		adapter->flags &= ~IXGBE_FLAG_MSIX_ENABLED;
		kमुक्त(adapter->msix_entries);
		adapter->msix_entries = शून्य;

		वापस vectors;
	पूर्ण

	/* we successfully allocated some number of vectors within our
	 * requested range.
	 */
	adapter->flags |= IXGBE_FLAG_MSIX_ENABLED;

	/* Adjust क्रम only the vectors we'll use, which is minimum
	 * of max_q_vectors, or the number of vectors we were allocated.
	 */
	vectors -= NON_Q_VECTORS;
	adapter->num_q_vectors = min_t(पूर्णांक, vectors, adapter->max_q_vectors);

	वापस 0;
पूर्ण

अटल व्योम ixgbe_add_ring(काष्ठा ixgbe_ring *ring,
			   काष्ठा ixgbe_ring_container *head)
अणु
	ring->next = head->ring;
	head->ring = ring;
	head->count++;
	head->next_update = jअगरfies + 1;
पूर्ण

/**
 * ixgbe_alloc_q_vector - Allocate memory क्रम a single पूर्णांकerrupt vector
 * @adapter: board निजी काष्ठाure to initialize
 * @v_count: q_vectors allocated on adapter, used क्रम ring पूर्णांकerleaving
 * @v_idx: index of vector in adapter काष्ठा
 * @txr_count: total number of Tx rings to allocate
 * @txr_idx: index of first Tx ring to allocate
 * @xdp_count: total number of XDP rings to allocate
 * @xdp_idx: index of first XDP ring to allocate
 * @rxr_count: total number of Rx rings to allocate
 * @rxr_idx: index of first Rx ring to allocate
 *
 * We allocate one q_vector.  If allocation fails we वापस -ENOMEM.
 **/
अटल पूर्णांक ixgbe_alloc_q_vector(काष्ठा ixgbe_adapter *adapter,
				पूर्णांक v_count, पूर्णांक v_idx,
				पूर्णांक txr_count, पूर्णांक txr_idx,
				पूर्णांक xdp_count, पूर्णांक xdp_idx,
				पूर्णांक rxr_count, पूर्णांक rxr_idx)
अणु
	पूर्णांक node = dev_to_node(&adapter->pdev->dev);
	काष्ठा ixgbe_q_vector *q_vector;
	काष्ठा ixgbe_ring *ring;
	पूर्णांक cpu = -1;
	पूर्णांक ring_count;
	u8 tcs = adapter->hw_tcs;

	ring_count = txr_count + rxr_count + xdp_count;

	/* customize cpu क्रम Flow Director mapping */
	अगर ((tcs <= 1) && !(adapter->flags & IXGBE_FLAG_SRIOV_ENABLED)) अणु
		u16 rss_i = adapter->ring_feature[RING_F_RSS].indices;
		अगर (rss_i > 1 && adapter->atr_sample_rate) अणु
			cpu = cpumask_local_spपढ़ो(v_idx, node);
			node = cpu_to_node(cpu);
		पूर्ण
	पूर्ण

	/* allocate q_vector and rings */
	q_vector = kzalloc_node(काष्ठा_size(q_vector, ring, ring_count),
				GFP_KERNEL, node);
	अगर (!q_vector)
		q_vector = kzalloc(काष्ठा_size(q_vector, ring, ring_count),
				   GFP_KERNEL);
	अगर (!q_vector)
		वापस -ENOMEM;

	/* setup affinity mask and node */
	अगर (cpu != -1)
		cpumask_set_cpu(cpu, &q_vector->affinity_mask);
	q_vector->numa_node = node;

#अगर_घोषित CONFIG_IXGBE_DCA
	/* initialize CPU क्रम DCA */
	q_vector->cpu = -1;

#पूर्ण_अगर
	/* initialize NAPI */
	netअगर_napi_add(adapter->netdev, &q_vector->napi,
		       ixgbe_poll, 64);

	/* tie q_vector and adapter together */
	adapter->q_vector[v_idx] = q_vector;
	q_vector->adapter = adapter;
	q_vector->v_idx = v_idx;

	/* initialize work limits */
	q_vector->tx.work_limit = adapter->tx_work_limit;

	/* Initialize setting क्रम adaptive ITR */
	q_vector->tx.itr = IXGBE_ITR_ADAPTIVE_MAX_USECS |
			   IXGBE_ITR_ADAPTIVE_LATENCY;
	q_vector->rx.itr = IXGBE_ITR_ADAPTIVE_MAX_USECS |
			   IXGBE_ITR_ADAPTIVE_LATENCY;

	/* पूर्णांकialize ITR */
	अगर (txr_count && !rxr_count) अणु
		/* tx only vector */
		अगर (adapter->tx_itr_setting == 1)
			q_vector->itr = IXGBE_12K_ITR;
		अन्यथा
			q_vector->itr = adapter->tx_itr_setting;
	पूर्ण अन्यथा अणु
		/* rx or rx/tx vector */
		अगर (adapter->rx_itr_setting == 1)
			q_vector->itr = IXGBE_20K_ITR;
		अन्यथा
			q_vector->itr = adapter->rx_itr_setting;
	पूर्ण

	/* initialize poपूर्णांकer to rings */
	ring = q_vector->ring;

	जबतक (txr_count) अणु
		/* assign generic ring traits */
		ring->dev = &adapter->pdev->dev;
		ring->netdev = adapter->netdev;

		/* configure backlink on ring */
		ring->q_vector = q_vector;

		/* update q_vector Tx values */
		ixgbe_add_ring(ring, &q_vector->tx);

		/* apply Tx specअगरic ring traits */
		ring->count = adapter->tx_ring_count;
		ring->queue_index = txr_idx;

		/* assign ring to adapter */
		WRITE_ONCE(adapter->tx_ring[txr_idx], ring);

		/* update count and index */
		txr_count--;
		txr_idx += v_count;

		/* push poपूर्णांकer to next ring */
		ring++;
	पूर्ण

	जबतक (xdp_count) अणु
		/* assign generic ring traits */
		ring->dev = &adapter->pdev->dev;
		ring->netdev = adapter->netdev;

		/* configure backlink on ring */
		ring->q_vector = q_vector;

		/* update q_vector Tx values */
		ixgbe_add_ring(ring, &q_vector->tx);

		/* apply Tx specअगरic ring traits */
		ring->count = adapter->tx_ring_count;
		ring->queue_index = xdp_idx;
		set_ring_xdp(ring);

		/* assign ring to adapter */
		WRITE_ONCE(adapter->xdp_ring[xdp_idx], ring);

		/* update count and index */
		xdp_count--;
		xdp_idx++;

		/* push poपूर्णांकer to next ring */
		ring++;
	पूर्ण

	जबतक (rxr_count) अणु
		/* assign generic ring traits */
		ring->dev = &adapter->pdev->dev;
		ring->netdev = adapter->netdev;

		/* configure backlink on ring */
		ring->q_vector = q_vector;

		/* update q_vector Rx values */
		ixgbe_add_ring(ring, &q_vector->rx);

		/*
		 * 82599 errata, UDP frames with a 0 checksum
		 * can be marked as checksum errors.
		 */
		अगर (adapter->hw.mac.type == ixgbe_mac_82599EB)
			set_bit(__IXGBE_RX_CSUM_UDP_ZERO_ERR, &ring->state);

#अगर_घोषित IXGBE_FCOE
		अगर (adapter->netdev->features & NETIF_F_FCOE_MTU) अणु
			काष्ठा ixgbe_ring_feature *f;
			f = &adapter->ring_feature[RING_F_FCOE];
			अगर ((rxr_idx >= f->offset) &&
			    (rxr_idx < f->offset + f->indices))
				set_bit(__IXGBE_RX_FCOE, &ring->state);
		पूर्ण

#पूर्ण_अगर /* IXGBE_FCOE */
		/* apply Rx specअगरic ring traits */
		ring->count = adapter->rx_ring_count;
		ring->queue_index = rxr_idx;

		/* assign ring to adapter */
		WRITE_ONCE(adapter->rx_ring[rxr_idx], ring);

		/* update count and index */
		rxr_count--;
		rxr_idx += v_count;

		/* push poपूर्णांकer to next ring */
		ring++;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ixgbe_मुक्त_q_vector - Free memory allocated क्रम specअगरic पूर्णांकerrupt vector
 * @adapter: board निजी काष्ठाure to initialize
 * @v_idx: Index of vector to be मुक्तd
 *
 * This function मुक्तs the memory allocated to the q_vector.  In addition अगर
 * NAPI is enabled it will delete any references to the NAPI काष्ठा prior
 * to मुक्तing the q_vector.
 **/
अटल व्योम ixgbe_मुक्त_q_vector(काष्ठा ixgbe_adapter *adapter, पूर्णांक v_idx)
अणु
	काष्ठा ixgbe_q_vector *q_vector = adapter->q_vector[v_idx];
	काष्ठा ixgbe_ring *ring;

	ixgbe_क्रम_each_ring(ring, q_vector->tx) अणु
		अगर (ring_is_xdp(ring))
			WRITE_ONCE(adapter->xdp_ring[ring->queue_index], शून्य);
		अन्यथा
			WRITE_ONCE(adapter->tx_ring[ring->queue_index], शून्य);
	पूर्ण

	ixgbe_क्रम_each_ring(ring, q_vector->rx)
		WRITE_ONCE(adapter->rx_ring[ring->queue_index], शून्य);

	adapter->q_vector[v_idx] = शून्य;
	__netअगर_napi_del(&q_vector->napi);

	/*
	 * after a call to __netअगर_napi_del() napi may still be used and
	 * ixgbe_get_stats64() might access the rings on this vector,
	 * we must रुको a grace period beक्रमe मुक्तing it.
	 */
	kमुक्त_rcu(q_vector, rcu);
पूर्ण

/**
 * ixgbe_alloc_q_vectors - Allocate memory क्रम पूर्णांकerrupt vectors
 * @adapter: board निजी काष्ठाure to initialize
 *
 * We allocate one q_vector per queue पूर्णांकerrupt.  If allocation fails we
 * वापस -ENOMEM.
 **/
अटल पूर्णांक ixgbe_alloc_q_vectors(काष्ठा ixgbe_adapter *adapter)
अणु
	पूर्णांक q_vectors = adapter->num_q_vectors;
	पूर्णांक rxr_reमुख्यing = adapter->num_rx_queues;
	पूर्णांक txr_reमुख्यing = adapter->num_tx_queues;
	पूर्णांक xdp_reमुख्यing = adapter->num_xdp_queues;
	पूर्णांक rxr_idx = 0, txr_idx = 0, xdp_idx = 0, v_idx = 0;
	पूर्णांक err, i;

	/* only one q_vector अगर MSI-X is disabled. */
	अगर (!(adapter->flags & IXGBE_FLAG_MSIX_ENABLED))
		q_vectors = 1;

	अगर (q_vectors >= (rxr_reमुख्यing + txr_reमुख्यing + xdp_reमुख्यing)) अणु
		क्रम (; rxr_reमुख्यing; v_idx++) अणु
			err = ixgbe_alloc_q_vector(adapter, q_vectors, v_idx,
						   0, 0, 0, 0, 1, rxr_idx);

			अगर (err)
				जाओ err_out;

			/* update counts and index */
			rxr_reमुख्यing--;
			rxr_idx++;
		पूर्ण
	पूर्ण

	क्रम (; v_idx < q_vectors; v_idx++) अणु
		पूर्णांक rqpv = DIV_ROUND_UP(rxr_reमुख्यing, q_vectors - v_idx);
		पूर्णांक tqpv = DIV_ROUND_UP(txr_reमुख्यing, q_vectors - v_idx);
		पूर्णांक xqpv = DIV_ROUND_UP(xdp_reमुख्यing, q_vectors - v_idx);

		err = ixgbe_alloc_q_vector(adapter, q_vectors, v_idx,
					   tqpv, txr_idx,
					   xqpv, xdp_idx,
					   rqpv, rxr_idx);

		अगर (err)
			जाओ err_out;

		/* update counts and index */
		rxr_reमुख्यing -= rqpv;
		txr_reमुख्यing -= tqpv;
		xdp_reमुख्यing -= xqpv;
		rxr_idx++;
		txr_idx++;
		xdp_idx += xqpv;
	पूर्ण

	क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
		अगर (adapter->rx_ring[i])
			adapter->rx_ring[i]->ring_idx = i;
	पूर्ण

	क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
		अगर (adapter->tx_ring[i])
			adapter->tx_ring[i]->ring_idx = i;
	पूर्ण

	क्रम (i = 0; i < adapter->num_xdp_queues; i++) अणु
		अगर (adapter->xdp_ring[i])
			adapter->xdp_ring[i]->ring_idx = i;
	पूर्ण

	वापस 0;

err_out:
	adapter->num_tx_queues = 0;
	adapter->num_xdp_queues = 0;
	adapter->num_rx_queues = 0;
	adapter->num_q_vectors = 0;

	जबतक (v_idx--)
		ixgbe_मुक्त_q_vector(adapter, v_idx);

	वापस -ENOMEM;
पूर्ण

/**
 * ixgbe_मुक्त_q_vectors - Free memory allocated क्रम पूर्णांकerrupt vectors
 * @adapter: board निजी काष्ठाure to initialize
 *
 * This function मुक्तs the memory allocated to the q_vectors.  In addition अगर
 * NAPI is enabled it will delete any references to the NAPI काष्ठा prior
 * to मुक्तing the q_vector.
 **/
अटल व्योम ixgbe_मुक्त_q_vectors(काष्ठा ixgbe_adapter *adapter)
अणु
	पूर्णांक v_idx = adapter->num_q_vectors;

	adapter->num_tx_queues = 0;
	adapter->num_xdp_queues = 0;
	adapter->num_rx_queues = 0;
	adapter->num_q_vectors = 0;

	जबतक (v_idx--)
		ixgbe_मुक्त_q_vector(adapter, v_idx);
पूर्ण

अटल व्योम ixgbe_reset_पूर्णांकerrupt_capability(काष्ठा ixgbe_adapter *adapter)
अणु
	अगर (adapter->flags & IXGBE_FLAG_MSIX_ENABLED) अणु
		adapter->flags &= ~IXGBE_FLAG_MSIX_ENABLED;
		pci_disable_msix(adapter->pdev);
		kमुक्त(adapter->msix_entries);
		adapter->msix_entries = शून्य;
	पूर्ण अन्यथा अगर (adapter->flags & IXGBE_FLAG_MSI_ENABLED) अणु
		adapter->flags &= ~IXGBE_FLAG_MSI_ENABLED;
		pci_disable_msi(adapter->pdev);
	पूर्ण
पूर्ण

/**
 * ixgbe_set_पूर्णांकerrupt_capability - set MSI-X or MSI अगर supported
 * @adapter: board निजी काष्ठाure to initialize
 *
 * Attempt to configure the पूर्णांकerrupts using the best available
 * capabilities of the hardware and the kernel.
 **/
अटल व्योम ixgbe_set_पूर्णांकerrupt_capability(काष्ठा ixgbe_adapter *adapter)
अणु
	पूर्णांक err;

	/* We will try to get MSI-X पूर्णांकerrupts first */
	अगर (!ixgbe_acquire_msix_vectors(adapter))
		वापस;

	/* At this poपूर्णांक, we करो not have MSI-X capabilities. We need to
	 * reconfigure or disable various features which require MSI-X
	 * capability.
	 */

	/* Disable DCB unless we only have a single traffic class */
	अगर (adapter->hw_tcs > 1) अणु
		e_dev_warn("Number of DCB TCs exceeds number of available queues. Disabling DCB support.\n");
		netdev_reset_tc(adapter->netdev);

		अगर (adapter->hw.mac.type == ixgbe_mac_82598EB)
			adapter->hw.fc.requested_mode = adapter->last_lfc_mode;

		adapter->flags &= ~IXGBE_FLAG_DCB_ENABLED;
		adapter->temp_dcb_cfg.pfc_mode_enable = false;
		adapter->dcb_cfg.pfc_mode_enable = false;
	पूर्ण

	adapter->hw_tcs = 0;
	adapter->dcb_cfg.num_tcs.pg_tcs = 1;
	adapter->dcb_cfg.num_tcs.pfc_tcs = 1;

	/* Disable SR-IOV support */
	e_dev_warn("Disabling SR-IOV support\n");
	ixgbe_disable_sriov(adapter);

	/* Disable RSS */
	e_dev_warn("Disabling RSS support\n");
	adapter->ring_feature[RING_F_RSS].limit = 1;

	/* recalculate number of queues now that many features have been
	 * changed or disabled.
	 */
	ixgbe_set_num_queues(adapter);
	adapter->num_q_vectors = 1;

	err = pci_enable_msi(adapter->pdev);
	अगर (err)
		e_dev_warn("Failed to allocate MSI interrupt, falling back to legacy. Error: %d\n",
			   err);
	अन्यथा
		adapter->flags |= IXGBE_FLAG_MSI_ENABLED;
पूर्ण

/**
 * ixgbe_init_पूर्णांकerrupt_scheme - Determine proper पूर्णांकerrupt scheme
 * @adapter: board निजी काष्ठाure to initialize
 *
 * We determine which पूर्णांकerrupt scheme to use based on...
 * - Kernel support (MSI, MSI-X)
 *   - which can be user-defined (via MODULE_PARAM)
 * - Hardware queue count (num_*_queues)
 *   - defined by miscellaneous hardware support/features (RSS, etc.)
 **/
पूर्णांक ixgbe_init_पूर्णांकerrupt_scheme(काष्ठा ixgbe_adapter *adapter)
अणु
	पूर्णांक err;

	/* Number of supported queues */
	ixgbe_set_num_queues(adapter);

	/* Set पूर्णांकerrupt mode */
	ixgbe_set_पूर्णांकerrupt_capability(adapter);

	err = ixgbe_alloc_q_vectors(adapter);
	अगर (err) अणु
		e_dev_err("Unable to allocate memory for queue vectors\n");
		जाओ err_alloc_q_vectors;
	पूर्ण

	ixgbe_cache_ring_रेजिस्टर(adapter);

	e_dev_info("Multiqueue %s: Rx Queue count = %u, Tx Queue count = %u XDP Queue count = %u\n",
		   (adapter->num_rx_queues > 1) ? "Enabled" : "Disabled",
		   adapter->num_rx_queues, adapter->num_tx_queues,
		   adapter->num_xdp_queues);

	set_bit(__IXGBE_DOWN, &adapter->state);

	वापस 0;

err_alloc_q_vectors:
	ixgbe_reset_पूर्णांकerrupt_capability(adapter);
	वापस err;
पूर्ण

/**
 * ixgbe_clear_पूर्णांकerrupt_scheme - Clear the current पूर्णांकerrupt scheme settings
 * @adapter: board निजी काष्ठाure to clear पूर्णांकerrupt scheme on
 *
 * We go through and clear पूर्णांकerrupt specअगरic resources and reset the काष्ठाure
 * to pre-load conditions
 **/
व्योम ixgbe_clear_पूर्णांकerrupt_scheme(काष्ठा ixgbe_adapter *adapter)
अणु
	adapter->num_tx_queues = 0;
	adapter->num_xdp_queues = 0;
	adapter->num_rx_queues = 0;

	ixgbe_मुक्त_q_vectors(adapter);
	ixgbe_reset_पूर्णांकerrupt_capability(adapter);
पूर्ण

व्योम ixgbe_tx_ctxtdesc(काष्ठा ixgbe_ring *tx_ring, u32 vlan_macip_lens,
		       u32 fceof_saidx, u32 type_tucmd, u32 mss_l4len_idx)
अणु
	काष्ठा ixgbe_adv_tx_context_desc *context_desc;
	u16 i = tx_ring->next_to_use;

	context_desc = IXGBE_TX_CTXTDESC(tx_ring, i);

	i++;
	tx_ring->next_to_use = (i < tx_ring->count) ? i : 0;

	/* set bits to identअगरy this as an advanced context descriptor */
	type_tucmd |= IXGBE_TXD_CMD_DEXT | IXGBE_ADVTXD_DTYP_CTXT;

	context_desc->vlan_macip_lens	= cpu_to_le32(vlan_macip_lens);
	context_desc->fceof_saidx	= cpu_to_le32(fceof_saidx);
	context_desc->type_tucmd_mlhl	= cpu_to_le32(type_tucmd);
	context_desc->mss_l4len_idx	= cpu_to_le32(mss_l4len_idx);
पूर्ण

