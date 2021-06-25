<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c)  2019 Intel Corporation */

#समावेश "igc.h"
#समावेश "igc_tsn.h"

अटल bool is_any_launchसमय(काष्ठा igc_adapter *adapter)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
		काष्ठा igc_ring *ring = adapter->tx_ring[i];

		अगर (ring->launchसमय_enable)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/* Returns the TSN specअगरic रेजिस्टरs to their शेष values after
 * TSN offloading is disabled.
 */
अटल पूर्णांक igc_tsn_disable_offload(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा igc_hw *hw = &adapter->hw;
	u32 tqavctrl;
	पूर्णांक i;

	अगर (!(adapter->flags & IGC_FLAG_TSN_QBV_ENABLED))
		वापस 0;

	adapter->cycle_समय = 0;

	wr32(IGC_TXPBS, I225_TXPBSIZE_DEFAULT);
	wr32(IGC_DTXMXPKTSZ, IGC_DTXMXPKTSZ_DEFAULT);

	tqavctrl = rd32(IGC_TQAVCTRL);
	tqavctrl &= ~(IGC_TQAVCTRL_TRANSMIT_MODE_TSN |
		      IGC_TQAVCTRL_ENHANCED_QAV);
	wr32(IGC_TQAVCTRL, tqavctrl);

	क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
		काष्ठा igc_ring *ring = adapter->tx_ring[i];

		ring->start_समय = 0;
		ring->end_समय = 0;
		ring->launchसमय_enable = false;

		wr32(IGC_TXQCTL(i), 0);
		wr32(IGC_STQT(i), 0);
		wr32(IGC_ENDQT(i), NSEC_PER_SEC);
	पूर्ण

	wr32(IGC_QBVCYCLET_S, NSEC_PER_SEC);
	wr32(IGC_QBVCYCLET, NSEC_PER_SEC);

	adapter->flags &= ~IGC_FLAG_TSN_QBV_ENABLED;

	वापस 0;
पूर्ण

अटल पूर्णांक igc_tsn_enable_offload(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा igc_hw *hw = &adapter->hw;
	u32 tqavctrl, baset_l, baset_h;
	u32 sec, nsec, cycle;
	kसमय_प्रकार base_समय, systim;
	पूर्णांक i;

	अगर (adapter->flags & IGC_FLAG_TSN_QBV_ENABLED)
		वापस 0;

	cycle = adapter->cycle_समय;
	base_समय = adapter->base_समय;

	wr32(IGC_TSAUXC, 0);
	wr32(IGC_DTXMXPKTSZ, IGC_DTXMXPKTSZ_TSN);
	wr32(IGC_TXPBS, IGC_TXPBSIZE_TSN);

	tqavctrl = rd32(IGC_TQAVCTRL);
	tqavctrl |= IGC_TQAVCTRL_TRANSMIT_MODE_TSN | IGC_TQAVCTRL_ENHANCED_QAV;
	wr32(IGC_TQAVCTRL, tqavctrl);

	wr32(IGC_QBVCYCLET_S, cycle);
	wr32(IGC_QBVCYCLET, cycle);

	क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
		काष्ठा igc_ring *ring = adapter->tx_ring[i];
		u32 txqctl = 0;

		wr32(IGC_STQT(i), ring->start_समय);
		wr32(IGC_ENDQT(i), ring->end_समय);

		अगर (adapter->base_समय) अणु
			/* If we have a base_समय we are in "taprio"
			 * mode and we need to be strict about the
			 * cycles: only transmit a packet अगर it can be
			 * completed during that cycle.
			 */
			txqctl |= IGC_TXQCTL_STRICT_CYCLE |
				IGC_TXQCTL_STRICT_END;
		पूर्ण

		अगर (ring->launchसमय_enable)
			txqctl |= IGC_TXQCTL_QUEUE_MODE_LAUNCHT;

		wr32(IGC_TXQCTL(i), txqctl);
	पूर्ण

	nsec = rd32(IGC_SYSTIML);
	sec = rd32(IGC_SYSTIMH);

	systim = kसमय_set(sec, nsec);

	अगर (kसमय_compare(systim, base_समय) > 0) अणु
		s64 n;

		n = भाग64_s64(kसमय_sub_ns(systim, base_समय), cycle);
		base_समय = kसमय_add_ns(base_समय, (n + 1) * cycle);
	पूर्ण

	baset_h = भाग_s64_rem(base_समय, NSEC_PER_SEC, &baset_l);

	wr32(IGC_BASET_H, baset_h);
	wr32(IGC_BASET_L, baset_l);

	adapter->flags |= IGC_FLAG_TSN_QBV_ENABLED;

	वापस 0;
पूर्ण

पूर्णांक igc_tsn_offload_apply(काष्ठा igc_adapter *adapter)
अणु
	bool is_any_enabled = adapter->base_समय || is_any_launchसमय(adapter);

	अगर (!(adapter->flags & IGC_FLAG_TSN_QBV_ENABLED) && !is_any_enabled)
		वापस 0;

	अगर (!is_any_enabled) अणु
		पूर्णांक err = igc_tsn_disable_offload(adapter);

		अगर (err < 0)
			वापस err;

		/* The BASET रेजिस्टरs aren't cleared when writing
		 * पूर्णांकo them, क्रमce a reset अगर the पूर्णांकerface is
		 * running.
		 */
		अगर (netअगर_running(adapter->netdev))
			schedule_work(&adapter->reset_task);

		वापस 0;
	पूर्ण

	वापस igc_tsn_enable_offload(adapter);
पूर्ण
