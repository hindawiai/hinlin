<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2013 - 2018 Intel Corporation. */

#समावेश "fm10k_common.h"

/**
 *  fm10k_get_bus_info_generic - Generic set PCI bus info
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Gets the PCI bus info (speed, width, type) then calls helper function to
 *  store this data within the fm10k_hw काष्ठाure.
 **/
s32 fm10k_get_bus_info_generic(काष्ठा fm10k_hw *hw)
अणु
	u16 link_cap, link_status, device_cap, device_control;

	/* Get the maximum link width and speed from PCIe config space */
	link_cap = fm10k_पढ़ो_pci_cfg_word(hw, FM10K_PCIE_LINK_CAP);

	चयन (link_cap & FM10K_PCIE_LINK_WIDTH) अणु
	हाल FM10K_PCIE_LINK_WIDTH_1:
		hw->bus_caps.width = fm10k_bus_width_pcie_x1;
		अवरोध;
	हाल FM10K_PCIE_LINK_WIDTH_2:
		hw->bus_caps.width = fm10k_bus_width_pcie_x2;
		अवरोध;
	हाल FM10K_PCIE_LINK_WIDTH_4:
		hw->bus_caps.width = fm10k_bus_width_pcie_x4;
		अवरोध;
	हाल FM10K_PCIE_LINK_WIDTH_8:
		hw->bus_caps.width = fm10k_bus_width_pcie_x8;
		अवरोध;
	शेष:
		hw->bus_caps.width = fm10k_bus_width_unknown;
		अवरोध;
	पूर्ण

	चयन (link_cap & FM10K_PCIE_LINK_SPEED) अणु
	हाल FM10K_PCIE_LINK_SPEED_2500:
		hw->bus_caps.speed = fm10k_bus_speed_2500;
		अवरोध;
	हाल FM10K_PCIE_LINK_SPEED_5000:
		hw->bus_caps.speed = fm10k_bus_speed_5000;
		अवरोध;
	हाल FM10K_PCIE_LINK_SPEED_8000:
		hw->bus_caps.speed = fm10k_bus_speed_8000;
		अवरोध;
	शेष:
		hw->bus_caps.speed = fm10k_bus_speed_unknown;
		अवरोध;
	पूर्ण

	/* Get the PCIe maximum payload size क्रम the PCIe function */
	device_cap = fm10k_पढ़ो_pci_cfg_word(hw, FM10K_PCIE_DEV_CAP);

	चयन (device_cap & FM10K_PCIE_DEV_CAP_PAYLOAD) अणु
	हाल FM10K_PCIE_DEV_CAP_PAYLOAD_128:
		hw->bus_caps.payload = fm10k_bus_payload_128;
		अवरोध;
	हाल FM10K_PCIE_DEV_CAP_PAYLOAD_256:
		hw->bus_caps.payload = fm10k_bus_payload_256;
		अवरोध;
	हाल FM10K_PCIE_DEV_CAP_PAYLOAD_512:
		hw->bus_caps.payload = fm10k_bus_payload_512;
		अवरोध;
	शेष:
		hw->bus_caps.payload = fm10k_bus_payload_unknown;
		अवरोध;
	पूर्ण

	/* Get the negotiated link width and speed from PCIe config space */
	link_status = fm10k_पढ़ो_pci_cfg_word(hw, FM10K_PCIE_LINK_STATUS);

	चयन (link_status & FM10K_PCIE_LINK_WIDTH) अणु
	हाल FM10K_PCIE_LINK_WIDTH_1:
		hw->bus.width = fm10k_bus_width_pcie_x1;
		अवरोध;
	हाल FM10K_PCIE_LINK_WIDTH_2:
		hw->bus.width = fm10k_bus_width_pcie_x2;
		अवरोध;
	हाल FM10K_PCIE_LINK_WIDTH_4:
		hw->bus.width = fm10k_bus_width_pcie_x4;
		अवरोध;
	हाल FM10K_PCIE_LINK_WIDTH_8:
		hw->bus.width = fm10k_bus_width_pcie_x8;
		अवरोध;
	शेष:
		hw->bus.width = fm10k_bus_width_unknown;
		अवरोध;
	पूर्ण

	चयन (link_status & FM10K_PCIE_LINK_SPEED) अणु
	हाल FM10K_PCIE_LINK_SPEED_2500:
		hw->bus.speed = fm10k_bus_speed_2500;
		अवरोध;
	हाल FM10K_PCIE_LINK_SPEED_5000:
		hw->bus.speed = fm10k_bus_speed_5000;
		अवरोध;
	हाल FM10K_PCIE_LINK_SPEED_8000:
		hw->bus.speed = fm10k_bus_speed_8000;
		अवरोध;
	शेष:
		hw->bus.speed = fm10k_bus_speed_unknown;
		अवरोध;
	पूर्ण

	/* Get the negotiated PCIe maximum payload size क्रम the PCIe function */
	device_control = fm10k_पढ़ो_pci_cfg_word(hw, FM10K_PCIE_DEV_CTRL);

	चयन (device_control & FM10K_PCIE_DEV_CTRL_PAYLOAD) अणु
	हाल FM10K_PCIE_DEV_CTRL_PAYLOAD_128:
		hw->bus.payload = fm10k_bus_payload_128;
		अवरोध;
	हाल FM10K_PCIE_DEV_CTRL_PAYLOAD_256:
		hw->bus.payload = fm10k_bus_payload_256;
		अवरोध;
	हाल FM10K_PCIE_DEV_CTRL_PAYLOAD_512:
		hw->bus.payload = fm10k_bus_payload_512;
		अवरोध;
	शेष:
		hw->bus.payload = fm10k_bus_payload_unknown;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल u16 fm10k_get_pcie_msix_count_generic(काष्ठा fm10k_hw *hw)
अणु
	u16 msix_count;

	/* पढ़ो in value from MSI-X capability रेजिस्टर */
	msix_count = fm10k_पढ़ो_pci_cfg_word(hw, FM10K_PCI_MSIX_MSG_CTRL);
	msix_count &= FM10K_PCI_MSIX_MSG_CTRL_TBL_SZ_MASK;

	/* MSI-X count is zero-based in HW */
	msix_count++;

	अगर (msix_count > FM10K_MAX_MSIX_VECTORS)
		msix_count = FM10K_MAX_MSIX_VECTORS;

	वापस msix_count;
पूर्ण

/**
 *  fm10k_get_invariants_generic - Inits स्थिरant values
 *  @hw: poपूर्णांकer to the hardware काष्ठाure
 *
 *  Initialize the common invariants क्रम the device.
 **/
s32 fm10k_get_invariants_generic(काष्ठा fm10k_hw *hw)
अणु
	काष्ठा fm10k_mac_info *mac = &hw->mac;

	/* initialize GLORT state to aव्योम any false hits */
	mac->dglort_map = FM10K_DGLORTMAP_NONE;

	/* record maximum number of MSI-X vectors */
	mac->max_msix_vectors = fm10k_get_pcie_msix_count_generic(hw);

	वापस 0;
पूर्ण

/**
 *  fm10k_start_hw_generic - Prepare hardware क्रम Tx/Rx
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  This function sets the Tx पढ़ोy flag to indicate that the Tx path has
 *  been initialized.
 **/
s32 fm10k_start_hw_generic(काष्ठा fm10k_hw *hw)
अणु
	/* set flag indicating we are beginning Tx */
	hw->mac.tx_पढ़ोy = true;

	वापस 0;
पूर्ण

/**
 *  fm10k_disable_queues_generic - Stop Tx/Rx queues
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @q_cnt: number of queues to be disabled
 *
 **/
s32 fm10k_disable_queues_generic(काष्ठा fm10k_hw *hw, u16 q_cnt)
अणु
	u32 reg;
	u16 i, समय;

	/* clear tx_पढ़ोy to prevent any false hits क्रम reset */
	hw->mac.tx_पढ़ोy = false;

	अगर (FM10K_REMOVED(hw->hw_addr))
		वापस 0;

	/* clear the enable bit क्रम all rings */
	क्रम (i = 0; i < q_cnt; i++) अणु
		reg = fm10k_पढ़ो_reg(hw, FM10K_TXDCTL(i));
		fm10k_ग_लिखो_reg(hw, FM10K_TXDCTL(i),
				reg & ~FM10K_TXDCTL_ENABLE);
		reg = fm10k_पढ़ो_reg(hw, FM10K_RXQCTL(i));
		fm10k_ग_लिखो_reg(hw, FM10K_RXQCTL(i),
				reg & ~FM10K_RXQCTL_ENABLE);
	पूर्ण

	fm10k_ग_लिखो_flush(hw);
	udelay(1);

	/* loop through all queues to verअगरy that they are all disabled */
	क्रम (i = 0, समय = FM10K_QUEUE_DISABLE_TIMEOUT; समय;) अणु
		/* अगर we are at end of rings all rings are disabled */
		अगर (i == q_cnt)
			वापस 0;

		/* अगर queue enables cleared, then move to next ring pair */
		reg = fm10k_पढ़ो_reg(hw, FM10K_TXDCTL(i));
		अगर (!~reg || !(reg & FM10K_TXDCTL_ENABLE)) अणु
			reg = fm10k_पढ़ो_reg(hw, FM10K_RXQCTL(i));
			अगर (!~reg || !(reg & FM10K_RXQCTL_ENABLE)) अणु
				i++;
				जारी;
			पूर्ण
		पूर्ण

		/* decrement समय and रुको 1 usec */
		समय--;
		अगर (समय)
			udelay(1);
	पूर्ण

	वापस FM10K_ERR_REQUESTS_PENDING;
पूर्ण

/**
 *  fm10k_stop_hw_generic - Stop Tx/Rx units
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 **/
s32 fm10k_stop_hw_generic(काष्ठा fm10k_hw *hw)
अणु
	वापस fm10k_disable_queues_generic(hw, hw->mac.max_queues);
पूर्ण

/**
 *  fm10k_पढ़ो_hw_stats_32b - Reads value of 32-bit रेजिस्टरs
 *  @hw: poपूर्णांकer to the hardware काष्ठाure
 *  @addr: address of रेजिस्टर containing a 32-bit value
 *  @stat: poपूर्णांकer to काष्ठाure holding hw stat inक्रमmation
 *
 *  Function पढ़ोs the content of the रेजिस्टर and वापसs the delta
 *  between the base and the current value.
 *  **/
u32 fm10k_पढ़ो_hw_stats_32b(काष्ठा fm10k_hw *hw, u32 addr,
			    काष्ठा fm10k_hw_stat *stat)
अणु
	u32 delta = fm10k_पढ़ो_reg(hw, addr) - stat->base_l;

	अगर (FM10K_REMOVED(hw->hw_addr))
		stat->base_h = 0;

	वापस delta;
पूर्ण

/**
 *  fm10k_पढ़ो_hw_stats_48b - Reads value of 48-bit रेजिस्टरs
 *  @hw: poपूर्णांकer to the hardware काष्ठाure
 *  @addr: address of रेजिस्टर containing the lower 32-bit value
 *  @stat: poपूर्णांकer to काष्ठाure holding hw stat inक्रमmation
 *
 *  Function पढ़ोs the content of 2 रेजिस्टरs, combined to represent a 48-bit
 *  statistical value. Extra processing is required to handle overflowing.
 *  Finally, a delta value is वापसed representing the dअगरference between the
 *  values stored in रेजिस्टरs and values stored in the statistic counters.
 *  **/
अटल u64 fm10k_पढ़ो_hw_stats_48b(काष्ठा fm10k_hw *hw, u32 addr,
				   काष्ठा fm10k_hw_stat *stat)
अणु
	u32 count_l;
	u32 count_h;
	u32 count_पंचांगp;
	u64 delta;

	count_h = fm10k_पढ़ो_reg(hw, addr + 1);

	/* Check क्रम overflow */
	करो अणु
		count_पंचांगp = count_h;
		count_l = fm10k_पढ़ो_reg(hw, addr);
		count_h = fm10k_पढ़ो_reg(hw, addr + 1);
	पूर्ण जबतक (count_h != count_पंचांगp);

	delta = ((u64)(count_h - stat->base_h) << 32) + count_l;
	delta -= stat->base_l;

	वापस delta & FM10K_48_BIT_MASK;
पूर्ण

/**
 *  fm10k_update_hw_base_48b - Updates 48-bit statistic base value
 *  @stat: poपूर्णांकer to the hardware statistic काष्ठाure
 *  @delta: value to be updated पूर्णांकo the hardware statistic काष्ठाure
 *
 *  Function receives a value and determines अगर an update is required based on
 *  a delta calculation. Only the base value will be updated.
 **/
अटल व्योम fm10k_update_hw_base_48b(काष्ठा fm10k_hw_stat *stat, u64 delta)
अणु
	अगर (!delta)
		वापस;

	/* update lower 32 bits */
	delta += stat->base_l;
	stat->base_l = (u32)delta;

	/* update upper 32 bits */
	stat->base_h += (u32)(delta >> 32);
पूर्ण

/**
 *  fm10k_update_hw_stats_tx_q - Updates TX queue statistics counters
 *  @hw: poपूर्णांकer to the hardware काष्ठाure
 *  @q: poपूर्णांकer to the ring of hardware statistics queue
 *  @idx: index poपूर्णांकing to the start of the ring iteration
 *
 *  Function updates the TX queue statistics counters that are related to the
 *  hardware.
 **/
अटल व्योम fm10k_update_hw_stats_tx_q(काष्ठा fm10k_hw *hw,
				       काष्ठा fm10k_hw_stats_q *q,
				       u32 idx)
अणु
	u32 id_tx, id_tx_prev, tx_packets;
	u64 tx_bytes = 0;

	/* Retrieve TX Owner Data */
	id_tx = fm10k_पढ़ो_reg(hw, FM10K_TXQCTL(idx));

	/* Process TX Ring */
	करो अणु
		tx_packets = fm10k_पढ़ो_hw_stats_32b(hw, FM10K_QPTC(idx),
						     &q->tx_packets);

		अगर (tx_packets)
			tx_bytes = fm10k_पढ़ो_hw_stats_48b(hw,
							   FM10K_QBTC_L(idx),
							   &q->tx_bytes);

		/* Re-Check Owner Data */
		id_tx_prev = id_tx;
		id_tx = fm10k_पढ़ो_reg(hw, FM10K_TXQCTL(idx));
	पूर्ण जबतक ((id_tx ^ id_tx_prev) & FM10K_TXQCTL_ID_MASK);

	/* drop non-ID bits and set VALID ID bit */
	id_tx &= FM10K_TXQCTL_ID_MASK;
	id_tx |= FM10K_STAT_VALID;

	/* update packet counts */
	अगर (q->tx_stats_idx == id_tx) अणु
		q->tx_packets.count += tx_packets;
		q->tx_bytes.count += tx_bytes;
	पूर्ण

	/* update bases and record ID */
	fm10k_update_hw_base_32b(&q->tx_packets, tx_packets);
	fm10k_update_hw_base_48b(&q->tx_bytes, tx_bytes);

	q->tx_stats_idx = id_tx;
पूर्ण

/**
 *  fm10k_update_hw_stats_rx_q - Updates RX queue statistics counters
 *  @hw: poपूर्णांकer to the hardware काष्ठाure
 *  @q: poपूर्णांकer to the ring of hardware statistics queue
 *  @idx: index poपूर्णांकing to the start of the ring iteration
 *
 *  Function updates the RX queue statistics counters that are related to the
 *  hardware.
 **/
अटल व्योम fm10k_update_hw_stats_rx_q(काष्ठा fm10k_hw *hw,
				       काष्ठा fm10k_hw_stats_q *q,
				       u32 idx)
अणु
	u32 id_rx, id_rx_prev, rx_packets, rx_drops;
	u64 rx_bytes = 0;

	/* Retrieve RX Owner Data */
	id_rx = fm10k_पढ़ो_reg(hw, FM10K_RXQCTL(idx));

	/* Process RX Ring */
	करो अणु
		rx_drops = fm10k_पढ़ो_hw_stats_32b(hw, FM10K_QPRDC(idx),
						   &q->rx_drops);

		rx_packets = fm10k_पढ़ो_hw_stats_32b(hw, FM10K_QPRC(idx),
						     &q->rx_packets);

		अगर (rx_packets)
			rx_bytes = fm10k_पढ़ो_hw_stats_48b(hw,
							   FM10K_QBRC_L(idx),
							   &q->rx_bytes);

		/* Re-Check Owner Data */
		id_rx_prev = id_rx;
		id_rx = fm10k_पढ़ो_reg(hw, FM10K_RXQCTL(idx));
	पूर्ण जबतक ((id_rx ^ id_rx_prev) & FM10K_RXQCTL_ID_MASK);

	/* drop non-ID bits and set VALID ID bit */
	id_rx &= FM10K_RXQCTL_ID_MASK;
	id_rx |= FM10K_STAT_VALID;

	/* update packet counts */
	अगर (q->rx_stats_idx == id_rx) अणु
		q->rx_drops.count += rx_drops;
		q->rx_packets.count += rx_packets;
		q->rx_bytes.count += rx_bytes;
	पूर्ण

	/* update bases and record ID */
	fm10k_update_hw_base_32b(&q->rx_drops, rx_drops);
	fm10k_update_hw_base_32b(&q->rx_packets, rx_packets);
	fm10k_update_hw_base_48b(&q->rx_bytes, rx_bytes);

	q->rx_stats_idx = id_rx;
पूर्ण

/**
 *  fm10k_update_hw_stats_q - Updates queue statistics counters
 *  @hw: poपूर्णांकer to the hardware काष्ठाure
 *  @q: poपूर्णांकer to the ring of hardware statistics queue
 *  @idx: index poपूर्णांकing to the start of the ring iteration
 *  @count: number of queues to iterate over
 *
 *  Function updates the queue statistics counters that are related to the
 *  hardware.
 **/
व्योम fm10k_update_hw_stats_q(काष्ठा fm10k_hw *hw, काष्ठा fm10k_hw_stats_q *q,
			     u32 idx, u32 count)
अणु
	u32 i;

	क्रम (i = 0; i < count; i++, idx++, q++) अणु
		fm10k_update_hw_stats_tx_q(hw, q, idx);
		fm10k_update_hw_stats_rx_q(hw, q, idx);
	पूर्ण
पूर्ण

/**
 *  fm10k_unbind_hw_stats_q - Unbind the queue counters from their queues
 *  @q: poपूर्णांकer to the ring of hardware statistics queue
 *  @idx: index poपूर्णांकing to the start of the ring iteration
 *  @count: number of queues to iterate over
 *
 *  Function invalidates the index values क्रम the queues so any updates that
 *  may have happened are ignored and the base क्रम the queue stats is reset.
 **/
व्योम fm10k_unbind_hw_stats_q(काष्ठा fm10k_hw_stats_q *q, u32 idx, u32 count)
अणु
	u32 i;

	क्रम (i = 0; i < count; i++, idx++, q++) अणु
		q->rx_stats_idx = 0;
		q->tx_stats_idx = 0;
	पूर्ण
पूर्ण

/**
 *  fm10k_get_host_state_generic - Returns the state of the host
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @host_पढ़ोy: poपूर्णांकer to boolean value that will record host state
 *
 *  This function will check the health of the mailbox and Tx queue 0
 *  in order to determine अगर we should report that the link is up or not.
 **/
s32 fm10k_get_host_state_generic(काष्ठा fm10k_hw *hw, bool *host_पढ़ोy)
अणु
	काष्ठा fm10k_mbx_info *mbx = &hw->mbx;
	काष्ठा fm10k_mac_info *mac = &hw->mac;
	s32 ret_val = 0;
	u32 txdctl = fm10k_पढ़ो_reg(hw, FM10K_TXDCTL(0));

	/* process upstream mailbox in हाल पूर्णांकerrupts were disabled */
	mbx->ops.process(hw, mbx);

	/* If Tx is no दीर्घer enabled link should come करोwn */
	अगर (!(~txdctl) || !(txdctl & FM10K_TXDCTL_ENABLE))
		mac->get_host_state = true;

	/* निकास अगर not checking क्रम link, or link cannot be changed */
	अगर (!mac->get_host_state || !(~txdctl))
		जाओ out;

	/* अगर we somehow dropped the Tx enable we should reset */
	अगर (mac->tx_पढ़ोy && !(txdctl & FM10K_TXDCTL_ENABLE)) अणु
		ret_val = FM10K_ERR_RESET_REQUESTED;
		जाओ out;
	पूर्ण

	/* अगर Mailbox समयd out we should request reset */
	अगर (!mbx->समयout) अणु
		ret_val = FM10K_ERR_RESET_REQUESTED;
		जाओ out;
	पूर्ण

	/* verअगरy Mailbox is still खोलो */
	अगर (mbx->state != FM10K_STATE_OPEN)
		जाओ out;

	/* पूर्णांकerface cannot receive traffic without logical ports */
	अगर (mac->dglort_map == FM10K_DGLORTMAP_NONE) अणु
		अगर (mac->ops.request_lport_map)
			ret_val = mac->ops.request_lport_map(hw);

		जाओ out;
	पूर्ण

	/* अगर we passed all the tests above then the चयन is पढ़ोy and we no
	 * दीर्घer need to check क्रम link
	 */
	mac->get_host_state = false;

out:
	*host_पढ़ोy = !mac->get_host_state;
	वापस ret_val;
पूर्ण
