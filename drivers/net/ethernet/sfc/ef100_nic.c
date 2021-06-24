<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2018 Solarflare Communications Inc.
 * Copyright 2019-2020 Xilinx Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation, incorporated herein by reference.
 */

#समावेश "ef100_nic.h"
#समावेश "efx_common.h"
#समावेश "efx_channels.h"
#समावेश "io.h"
#समावेश "selftest.h"
#समावेश "ef100_regs.h"
#समावेश "mcdi.h"
#समावेश "mcdi_pcol.h"
#समावेश "mcdi_port_common.h"
#समावेश "mcdi_functions.h"
#समावेश "mcdi_filters.h"
#समावेश "ef100_rx.h"
#समावेश "ef100_tx.h"
#समावेश "ef100_netdev.h"

#घोषणा EF100_MAX_VIS 4096
#घोषणा EF100_NUM_MCDI_BUFFERS	1
#घोषणा MCDI_BUF_LEN (8 + MCDI_CTL_SDU_LEN_MAX)

#घोषणा EF100_RESET_PORT ((ETH_RESET_MAC | ETH_RESET_PHY) << ETH_RESET_SHARED_SHIFT)

/*	MCDI
 */
अटल u8 *ef100_mcdi_buf(काष्ठा efx_nic *efx, u8 bufid, dma_addr_t *dma_addr)
अणु
	काष्ठा ef100_nic_data *nic_data = efx->nic_data;

	अगर (dma_addr)
		*dma_addr = nic_data->mcdi_buf.dma_addr +
			    bufid * ALIGN(MCDI_BUF_LEN, 256);
	वापस nic_data->mcdi_buf.addr + bufid * ALIGN(MCDI_BUF_LEN, 256);
पूर्ण

अटल पूर्णांक ef100_get_warm_boot_count(काष्ठा efx_nic *efx)
अणु
	efx_dword_t reg;

	efx_पढ़ोd(efx, &reg, efx_reg(efx, ER_GZ_MC_SFT_STATUS));

	अगर (EFX_DWORD_FIELD(reg, EFX_DWORD_0) == 0xffffffff) अणु
		netअगर_err(efx, hw, efx->net_dev, "Hardware unavailable\n");
		efx->state = STATE_DISABLED;
		वापस -ENETDOWN;
	पूर्ण अन्यथा अणु
		वापस EFX_DWORD_FIELD(reg, EFX_WORD_1) == 0xb007 ?
			EFX_DWORD_FIELD(reg, EFX_WORD_0) : -EIO;
	पूर्ण
पूर्ण

अटल व्योम ef100_mcdi_request(काष्ठा efx_nic *efx,
			       स्थिर efx_dword_t *hdr, माप_प्रकार hdr_len,
			       स्थिर efx_dword_t *sdu, माप_प्रकार sdu_len)
अणु
	dma_addr_t dma_addr;
	u8 *pdu = ef100_mcdi_buf(efx, 0, &dma_addr);

	स_नकल(pdu, hdr, hdr_len);
	स_नकल(pdu + hdr_len, sdu, sdu_len);
	wmb();

	/* The hardware provides 'low' and 'high' (करोorbell) रेजिस्टरs
	 * क्रम passing the 64-bit address of an MCDI request to
	 * firmware.  However the dwords are swapped by firmware.  The
	 * least signअगरicant bits of the करोorbell are then 0 क्रम all
	 * MCDI requests due to alignment.
	 */
	_efx_ग_लिखोd(efx, cpu_to_le32((u64)dma_addr >> 32),  efx_reg(efx, ER_GZ_MC_DB_LWRD));
	_efx_ग_लिखोd(efx, cpu_to_le32((u32)dma_addr),  efx_reg(efx, ER_GZ_MC_DB_HWRD));
पूर्ण

अटल bool ef100_mcdi_poll_response(काष्ठा efx_nic *efx)
अणु
	स्थिर efx_dword_t hdr =
		*(स्थिर efx_dword_t *)(ef100_mcdi_buf(efx, 0, शून्य));

	rmb();
	वापस EFX_DWORD_FIELD(hdr, MCDI_HEADER_RESPONSE);
पूर्ण

अटल व्योम ef100_mcdi_पढ़ो_response(काष्ठा efx_nic *efx,
				     efx_dword_t *outbuf, माप_प्रकार offset,
				     माप_प्रकार outlen)
अणु
	स्थिर u8 *pdu = ef100_mcdi_buf(efx, 0, शून्य);

	स_नकल(outbuf, pdu + offset, outlen);
पूर्ण

अटल पूर्णांक ef100_mcdi_poll_reboot(काष्ठा efx_nic *efx)
अणु
	काष्ठा ef100_nic_data *nic_data = efx->nic_data;
	पूर्णांक rc;

	rc = ef100_get_warm_boot_count(efx);
	अगर (rc < 0) अणु
		/* The firmware is presumably in the process of
		 * rebooting.  However, we are supposed to report each
		 * reboot just once, so we must only करो that once we
		 * can पढ़ो and store the updated warm boot count.
		 */
		वापस 0;
	पूर्ण

	अगर (rc == nic_data->warm_boot_count)
		वापस 0;

	nic_data->warm_boot_count = rc;

	वापस -EIO;
पूर्ण

अटल व्योम ef100_mcdi_reboot_detected(काष्ठा efx_nic *efx)
अणु
पूर्ण

/*	MCDI calls
 */
अटल पूर्णांक ef100_get_mac_address(काष्ठा efx_nic *efx, u8 *mac_address)
अणु
	MCDI_DECLARE_BUF(outbuf, MC_CMD_GET_MAC_ADDRESSES_OUT_LEN);
	माप_प्रकार outlen;
	पूर्णांक rc;

	BUILD_BUG_ON(MC_CMD_GET_MAC_ADDRESSES_IN_LEN != 0);

	rc = efx_mcdi_rpc(efx, MC_CMD_GET_MAC_ADDRESSES, शून्य, 0,
			  outbuf, माप(outbuf), &outlen);
	अगर (rc)
		वापस rc;
	अगर (outlen < MC_CMD_GET_MAC_ADDRESSES_OUT_LEN)
		वापस -EIO;

	ether_addr_copy(mac_address,
			MCDI_PTR(outbuf, GET_MAC_ADDRESSES_OUT_MAC_ADDR_BASE));
	वापस 0;
पूर्ण

अटल पूर्णांक efx_ef100_init_datapath_caps(काष्ठा efx_nic *efx)
अणु
	MCDI_DECLARE_BUF(outbuf, MC_CMD_GET_CAPABILITIES_V7_OUT_LEN);
	काष्ठा ef100_nic_data *nic_data = efx->nic_data;
	u8 vi_winकरोw_mode;
	माप_प्रकार outlen;
	पूर्णांक rc;

	BUILD_BUG_ON(MC_CMD_GET_CAPABILITIES_IN_LEN != 0);

	rc = efx_mcdi_rpc(efx, MC_CMD_GET_CAPABILITIES, शून्य, 0,
			  outbuf, माप(outbuf), &outlen);
	अगर (rc)
		वापस rc;
	अगर (outlen < MC_CMD_GET_CAPABILITIES_V4_OUT_LEN) अणु
		netअगर_err(efx, drv, efx->net_dev,
			  "unable to read datapath firmware capabilities\n");
		वापस -EIO;
	पूर्ण

	nic_data->datapath_caps = MCDI_DWORD(outbuf,
					     GET_CAPABILITIES_OUT_FLAGS1);
	nic_data->datapath_caps2 = MCDI_DWORD(outbuf,
					      GET_CAPABILITIES_V2_OUT_FLAGS2);
	अगर (outlen < MC_CMD_GET_CAPABILITIES_V7_OUT_LEN)
		nic_data->datapath_caps3 = 0;
	अन्यथा
		nic_data->datapath_caps3 = MCDI_DWORD(outbuf,
						      GET_CAPABILITIES_V7_OUT_FLAGS3);

	vi_winकरोw_mode = MCDI_BYTE(outbuf,
				   GET_CAPABILITIES_V3_OUT_VI_WINDOW_MODE);
	rc = efx_mcdi_winकरोw_mode_to_stride(efx, vi_winकरोw_mode);
	अगर (rc)
		वापस rc;

	अगर (efx_ef100_has_cap(nic_data->datapath_caps2, TX_TSO_V3)) अणु
		काष्ठा net_device *net_dev = efx->net_dev;
		netdev_features_t tso = NETIF_F_TSO | NETIF_F_TSO6 | NETIF_F_GSO_PARTIAL |
					NETIF_F_GSO_UDP_TUNNEL | NETIF_F_GSO_UDP_TUNNEL_CSUM |
					NETIF_F_GSO_GRE | NETIF_F_GSO_GRE_CSUM;

		net_dev->features |= tso;
		net_dev->hw_features |= tso;
		net_dev->hw_enc_features |= tso;
		/* EF100 HW can only offload outer checksums अगर they are UDP,
		 * so क्रम GRE_CSUM we have to use GSO_PARTIAL.
		 */
		net_dev->gso_partial_features |= NETIF_F_GSO_GRE_CSUM;
	पूर्ण
	efx->num_mac_stats = MCDI_WORD(outbuf,
				       GET_CAPABILITIES_V4_OUT_MAC_STATS_NUM_STATS);
	netअगर_dbg(efx, probe, efx->net_dev,
		  "firmware reports num_mac_stats = %u\n",
		  efx->num_mac_stats);
	वापस 0;
पूर्ण

/*	Event handling
 */
अटल पूर्णांक ef100_ev_probe(काष्ठा efx_channel *channel)
अणु
	/* Allocate an extra descriptor क्रम the QMDA status completion entry */
	वापस efx_nic_alloc_buffer(channel->efx, &channel->eventq.buf,
				    (channel->eventq_mask + 2) *
				    माप(efx_qword_t),
				    GFP_KERNEL);
पूर्ण

अटल पूर्णांक ef100_ev_init(काष्ठा efx_channel *channel)
अणु
	काष्ठा ef100_nic_data *nic_data = channel->efx->nic_data;

	/* initial phase is 0 */
	clear_bit(channel->channel, nic_data->evq_phases);

	वापस efx_mcdi_ev_init(channel, false, false);
पूर्ण

अटल व्योम ef100_ev_पढ़ो_ack(काष्ठा efx_channel *channel)
अणु
	efx_dword_t evq_prime;

	EFX_POPULATE_DWORD_2(evq_prime,
			     ERF_GZ_EVQ_ID, channel->channel,
			     ERF_GZ_IDX, channel->eventq_पढ़ो_ptr &
					 channel->eventq_mask);

	efx_ग_लिखोd(channel->efx, &evq_prime,
		   efx_reg(channel->efx, ER_GZ_EVQ_INT_PRIME));
पूर्ण

अटल पूर्णांक ef100_ev_process(काष्ठा efx_channel *channel, पूर्णांक quota)
अणु
	काष्ठा efx_nic *efx = channel->efx;
	काष्ठा ef100_nic_data *nic_data;
	bool evq_phase, old_evq_phase;
	अचिन्हित पूर्णांक पढ़ो_ptr;
	efx_qword_t *p_event;
	पूर्णांक spent = 0;
	bool ev_phase;
	पूर्णांक ev_type;

	अगर (unlikely(!channel->enabled))
		वापस 0;

	nic_data = efx->nic_data;
	evq_phase = test_bit(channel->channel, nic_data->evq_phases);
	old_evq_phase = evq_phase;
	पढ़ो_ptr = channel->eventq_पढ़ो_ptr;
	BUILD_BUG_ON(ESF_GZ_EV_RXPKTS_PHASE_LBN != ESF_GZ_EV_TXCMPL_PHASE_LBN);

	जबतक (spent < quota) अणु
		p_event = efx_event(channel, पढ़ो_ptr);

		ev_phase = !!EFX_QWORD_FIELD(*p_event, ESF_GZ_EV_RXPKTS_PHASE);
		अगर (ev_phase != evq_phase)
			अवरोध;

		netअगर_vdbg(efx, drv, efx->net_dev,
			   "processing event on %d " EFX_QWORD_FMT "\n",
			   channel->channel, EFX_QWORD_VAL(*p_event));

		ev_type = EFX_QWORD_FIELD(*p_event, ESF_GZ_E_TYPE);

		चयन (ev_type) अणु
		हाल ESE_GZ_EF100_EV_RX_PKTS:
			efx_ef100_ev_rx(channel, p_event);
			++spent;
			अवरोध;
		हाल ESE_GZ_EF100_EV_MCDI:
			efx_mcdi_process_event(channel, p_event);
			अवरोध;
		हाल ESE_GZ_EF100_EV_TX_COMPLETION:
			ef100_ev_tx(channel, p_event);
			अवरोध;
		हाल ESE_GZ_EF100_EV_DRIVER:
			netअगर_info(efx, drv, efx->net_dev,
				   "Driver initiated event " EFX_QWORD_FMT "\n",
				   EFX_QWORD_VAL(*p_event));
			अवरोध;
		शेष:
			netअगर_info(efx, drv, efx->net_dev,
				   "Unhandled event " EFX_QWORD_FMT "\n",
				   EFX_QWORD_VAL(*p_event));
		पूर्ण

		++पढ़ो_ptr;
		अगर ((पढ़ो_ptr & channel->eventq_mask) == 0)
			evq_phase = !evq_phase;
	पूर्ण

	channel->eventq_पढ़ो_ptr = पढ़ो_ptr;
	अगर (evq_phase != old_evq_phase)
		change_bit(channel->channel, nic_data->evq_phases);

	वापस spent;
पूर्ण

अटल irqवापस_t ef100_msi_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा efx_msi_context *context = dev_id;
	काष्ठा efx_nic *efx = context->efx;

	netअगर_vdbg(efx, पूर्णांकr, efx->net_dev,
		   "IRQ %d on CPU %d\n", irq, raw_smp_processor_id());

	अगर (likely(READ_ONCE(efx->irq_soft_enabled))) अणु
		/* Note test पूर्णांकerrupts */
		अगर (context->index == efx->irq_level)
			efx->last_irq_cpu = raw_smp_processor_id();

		/* Schedule processing of the channel */
		efx_schedule_channel_irq(efx->channel[context->index]);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ef100_phy_probe(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_mcdi_phy_data *phy_data;
	पूर्णांक rc;

	/* Probe क्रम the PHY */
	efx->phy_data = kzalloc(माप(काष्ठा efx_mcdi_phy_data), GFP_KERNEL);
	अगर (!efx->phy_data)
		वापस -ENOMEM;

	rc = efx_mcdi_get_phy_cfg(efx, efx->phy_data);
	अगर (rc)
		वापस rc;

	/* Populate driver and ethtool settings */
	phy_data = efx->phy_data;
	mcdi_to_ethtool_linkset(phy_data->media, phy_data->supported_cap,
				efx->link_advertising);
	efx->fec_config = mcdi_fec_caps_to_ethtool(phy_data->supported_cap,
						   false);

	/* Default to Autonegotiated flow control अगर the PHY supports it */
	efx->wanted_fc = EFX_FC_RX | EFX_FC_TX;
	अगर (phy_data->supported_cap & (1 << MC_CMD_PHY_CAP_AN_LBN))
		efx->wanted_fc |= EFX_FC_AUTO;
	efx_link_set_wanted_fc(efx, efx->wanted_fc);

	/* Push settings to the PHY. Failure is not fatal, the user can try to
	 * fix it using ethtool.
	 */
	rc = efx_mcdi_port_reconfigure(efx);
	अगर (rc && rc != -EPERM)
		netअगर_warn(efx, drv, efx->net_dev,
			   "could not initialise PHY settings\n");

	वापस 0;
पूर्ण

अटल पूर्णांक ef100_filter_table_probe(काष्ठा efx_nic *efx)
अणु
	वापस efx_mcdi_filter_table_probe(efx, true);
पूर्ण

अटल पूर्णांक ef100_filter_table_up(काष्ठा efx_nic *efx)
अणु
	पूर्णांक rc;

	rc = efx_mcdi_filter_add_vlan(efx, EFX_FILTER_VID_UNSPEC);
	अगर (rc) अणु
		efx_mcdi_filter_table_करोwn(efx);
		वापस rc;
	पूर्ण

	rc = efx_mcdi_filter_add_vlan(efx, 0);
	अगर (rc) अणु
		efx_mcdi_filter_del_vlan(efx, EFX_FILTER_VID_UNSPEC);
		efx_mcdi_filter_table_करोwn(efx);
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम ef100_filter_table_करोwn(काष्ठा efx_nic *efx)
अणु
	efx_mcdi_filter_del_vlan(efx, 0);
	efx_mcdi_filter_del_vlan(efx, EFX_FILTER_VID_UNSPEC);
	efx_mcdi_filter_table_करोwn(efx);
पूर्ण

/*	Other
 */
अटल पूर्णांक ef100_reconfigure_mac(काष्ठा efx_nic *efx, bool mtu_only)
अणु
	WARN_ON(!mutex_is_locked(&efx->mac_lock));

	efx_mcdi_filter_sync_rx_mode(efx);

	अगर (mtu_only && efx_has_cap(efx, SET_MAC_ENHANCED))
		वापस efx_mcdi_set_mtu(efx);
	वापस efx_mcdi_set_mac(efx);
पूर्ण

अटल क्रमागत reset_type ef100_map_reset_reason(क्रमागत reset_type reason)
अणु
	अगर (reason == RESET_TYPE_TX_WATCHDOG)
		वापस reason;
	वापस RESET_TYPE_DISABLE;
पूर्ण

अटल पूर्णांक ef100_map_reset_flags(u32 *flags)
अणु
	/* Only perक्रमm a RESET_TYPE_ALL because we करोn't support MC_REBOOTs */
	अगर ((*flags & EF100_RESET_PORT)) अणु
		*flags &= ~EF100_RESET_PORT;
		वापस RESET_TYPE_ALL;
	पूर्ण
	अगर (*flags & ETH_RESET_MGMT) अणु
		*flags &= ~ETH_RESET_MGMT;
		वापस RESET_TYPE_DISABLE;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ef100_reset(काष्ठा efx_nic *efx, क्रमागत reset_type reset_type)
अणु
	पूर्णांक rc;

	dev_बंद(efx->net_dev);

	अगर (reset_type == RESET_TYPE_TX_WATCHDOG) अणु
		netअगर_device_attach(efx->net_dev);
		__clear_bit(reset_type, &efx->reset_pending);
		rc = dev_खोलो(efx->net_dev, शून्य);
	पूर्ण अन्यथा अगर (reset_type == RESET_TYPE_ALL) अणु
		rc = efx_mcdi_reset(efx, reset_type);
		अगर (rc)
			वापस rc;

		netअगर_device_attach(efx->net_dev);

		rc = dev_खोलो(efx->net_dev, शून्य);
	पूर्ण अन्यथा अणु
		rc = 1;	/* Leave the device बंदd */
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम ef100_common_stat_mask(अचिन्हित दीर्घ *mask)
अणु
	__set_bit(EF100_STAT_port_rx_packets, mask);
	__set_bit(EF100_STAT_port_tx_packets, mask);
	__set_bit(EF100_STAT_port_rx_bytes, mask);
	__set_bit(EF100_STAT_port_tx_bytes, mask);
	__set_bit(EF100_STAT_port_rx_multicast, mask);
	__set_bit(EF100_STAT_port_rx_bad, mask);
	__set_bit(EF100_STAT_port_rx_align_error, mask);
	__set_bit(EF100_STAT_port_rx_overflow, mask);
पूर्ण

अटल व्योम ef100_ethtool_stat_mask(अचिन्हित दीर्घ *mask)
अणु
	__set_bit(EF100_STAT_port_tx_छोड़ो, mask);
	__set_bit(EF100_STAT_port_tx_unicast, mask);
	__set_bit(EF100_STAT_port_tx_multicast, mask);
	__set_bit(EF100_STAT_port_tx_broadcast, mask);
	__set_bit(EF100_STAT_port_tx_lt64, mask);
	__set_bit(EF100_STAT_port_tx_64, mask);
	__set_bit(EF100_STAT_port_tx_65_to_127, mask);
	__set_bit(EF100_STAT_port_tx_128_to_255, mask);
	__set_bit(EF100_STAT_port_tx_256_to_511, mask);
	__set_bit(EF100_STAT_port_tx_512_to_1023, mask);
	__set_bit(EF100_STAT_port_tx_1024_to_15xx, mask);
	__set_bit(EF100_STAT_port_tx_15xx_to_jumbo, mask);
	__set_bit(EF100_STAT_port_rx_good, mask);
	__set_bit(EF100_STAT_port_rx_छोड़ो, mask);
	__set_bit(EF100_STAT_port_rx_unicast, mask);
	__set_bit(EF100_STAT_port_rx_broadcast, mask);
	__set_bit(EF100_STAT_port_rx_lt64, mask);
	__set_bit(EF100_STAT_port_rx_64, mask);
	__set_bit(EF100_STAT_port_rx_65_to_127, mask);
	__set_bit(EF100_STAT_port_rx_128_to_255, mask);
	__set_bit(EF100_STAT_port_rx_256_to_511, mask);
	__set_bit(EF100_STAT_port_rx_512_to_1023, mask);
	__set_bit(EF100_STAT_port_rx_1024_to_15xx, mask);
	__set_bit(EF100_STAT_port_rx_15xx_to_jumbo, mask);
	__set_bit(EF100_STAT_port_rx_gtjumbo, mask);
	__set_bit(EF100_STAT_port_rx_bad_gtjumbo, mask);
	__set_bit(EF100_STAT_port_rx_length_error, mask);
	__set_bit(EF100_STAT_port_rx_nodesc_drops, mask);
	__set_bit(GENERIC_STAT_rx_nodesc_trunc, mask);
	__set_bit(GENERIC_STAT_rx_noskb_drops, mask);
पूर्ण

#घोषणा EF100_DMA_STAT(ext_name, mcdi_name)			\
	[EF100_STAT_ ## ext_name] =				\
	अणु #ext_name, 64, 8 * MC_CMD_MAC_ ## mcdi_name पूर्ण

अटल स्थिर काष्ठा efx_hw_stat_desc ef100_stat_desc[EF100_STAT_COUNT] = अणु
	EF100_DMA_STAT(port_tx_bytes, TX_BYTES),
	EF100_DMA_STAT(port_tx_packets, TX_PKTS),
	EF100_DMA_STAT(port_tx_छोड़ो, TX_PAUSE_PKTS),
	EF100_DMA_STAT(port_tx_unicast, TX_UNICAST_PKTS),
	EF100_DMA_STAT(port_tx_multicast, TX_MULTICAST_PKTS),
	EF100_DMA_STAT(port_tx_broadcast, TX_BROADCAST_PKTS),
	EF100_DMA_STAT(port_tx_lt64, TX_LT64_PKTS),
	EF100_DMA_STAT(port_tx_64, TX_64_PKTS),
	EF100_DMA_STAT(port_tx_65_to_127, TX_65_TO_127_PKTS),
	EF100_DMA_STAT(port_tx_128_to_255, TX_128_TO_255_PKTS),
	EF100_DMA_STAT(port_tx_256_to_511, TX_256_TO_511_PKTS),
	EF100_DMA_STAT(port_tx_512_to_1023, TX_512_TO_1023_PKTS),
	EF100_DMA_STAT(port_tx_1024_to_15xx, TX_1024_TO_15XX_PKTS),
	EF100_DMA_STAT(port_tx_15xx_to_jumbo, TX_15XX_TO_JUMBO_PKTS),
	EF100_DMA_STAT(port_rx_bytes, RX_BYTES),
	EF100_DMA_STAT(port_rx_packets, RX_PKTS),
	EF100_DMA_STAT(port_rx_good, RX_GOOD_PKTS),
	EF100_DMA_STAT(port_rx_bad, RX_BAD_FCS_PKTS),
	EF100_DMA_STAT(port_rx_छोड़ो, RX_PAUSE_PKTS),
	EF100_DMA_STAT(port_rx_unicast, RX_UNICAST_PKTS),
	EF100_DMA_STAT(port_rx_multicast, RX_MULTICAST_PKTS),
	EF100_DMA_STAT(port_rx_broadcast, RX_BROADCAST_PKTS),
	EF100_DMA_STAT(port_rx_lt64, RX_UNDERSIZE_PKTS),
	EF100_DMA_STAT(port_rx_64, RX_64_PKTS),
	EF100_DMA_STAT(port_rx_65_to_127, RX_65_TO_127_PKTS),
	EF100_DMA_STAT(port_rx_128_to_255, RX_128_TO_255_PKTS),
	EF100_DMA_STAT(port_rx_256_to_511, RX_256_TO_511_PKTS),
	EF100_DMA_STAT(port_rx_512_to_1023, RX_512_TO_1023_PKTS),
	EF100_DMA_STAT(port_rx_1024_to_15xx, RX_1024_TO_15XX_PKTS),
	EF100_DMA_STAT(port_rx_15xx_to_jumbo, RX_15XX_TO_JUMBO_PKTS),
	EF100_DMA_STAT(port_rx_gtjumbo, RX_GTJUMBO_PKTS),
	EF100_DMA_STAT(port_rx_bad_gtjumbo, RX_JABBER_PKTS),
	EF100_DMA_STAT(port_rx_align_error, RX_ALIGN_ERROR_PKTS),
	EF100_DMA_STAT(port_rx_length_error, RX_LENGTH_ERROR_PKTS),
	EF100_DMA_STAT(port_rx_overflow, RX_OVERFLOW_PKTS),
	EF100_DMA_STAT(port_rx_nodesc_drops, RX_NODESC_DROPS),
	EFX_GENERIC_SW_STAT(rx_nodesc_trunc),
	EFX_GENERIC_SW_STAT(rx_noskb_drops),
पूर्ण;

अटल माप_प्रकार ef100_describe_stats(काष्ठा efx_nic *efx, u8 *names)
अणु
	DECLARE_BITMAP(mask, EF100_STAT_COUNT) = अणुपूर्ण;

	ef100_ethtool_stat_mask(mask);
	वापस efx_nic_describe_stats(ef100_stat_desc, EF100_STAT_COUNT,
				      mask, names);
पूर्ण

अटल माप_प्रकार ef100_update_stats_common(काष्ठा efx_nic *efx, u64 *full_stats,
					काष्ठा rtnl_link_stats64 *core_stats)
अणु
	काष्ठा ef100_nic_data *nic_data = efx->nic_data;
	DECLARE_BITMAP(mask, EF100_STAT_COUNT) = अणुपूर्ण;
	माप_प्रकार stats_count = 0, index;
	u64 *stats = nic_data->stats;

	ef100_ethtool_stat_mask(mask);

	अगर (full_stats) अणु
		क्रम_each_set_bit(index, mask, EF100_STAT_COUNT) अणु
			अगर (ef100_stat_desc[index].name) अणु
				*full_stats++ = stats[index];
				++stats_count;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!core_stats)
		वापस stats_count;

	core_stats->rx_packets = stats[EF100_STAT_port_rx_packets];
	core_stats->tx_packets = stats[EF100_STAT_port_tx_packets];
	core_stats->rx_bytes = stats[EF100_STAT_port_rx_bytes];
	core_stats->tx_bytes = stats[EF100_STAT_port_tx_bytes];
	core_stats->rx_dropped = stats[EF100_STAT_port_rx_nodesc_drops] +
				 stats[GENERIC_STAT_rx_nodesc_trunc] +
				 stats[GENERIC_STAT_rx_noskb_drops];
	core_stats->multicast = stats[EF100_STAT_port_rx_multicast];
	core_stats->rx_length_errors =
			stats[EF100_STAT_port_rx_gtjumbo] +
			stats[EF100_STAT_port_rx_length_error];
	core_stats->rx_crc_errors = stats[EF100_STAT_port_rx_bad];
	core_stats->rx_frame_errors =
			stats[EF100_STAT_port_rx_align_error];
	core_stats->rx_fअगरo_errors = stats[EF100_STAT_port_rx_overflow];
	core_stats->rx_errors = (core_stats->rx_length_errors +
				 core_stats->rx_crc_errors +
				 core_stats->rx_frame_errors);

	वापस stats_count;
पूर्ण

अटल माप_प्रकार ef100_update_stats(काष्ठा efx_nic *efx,
				 u64 *full_stats,
				 काष्ठा rtnl_link_stats64 *core_stats)
अणु
	__le64 *mc_stats = kदो_स्मृति(array_size(efx->num_mac_stats, माप(__le64)), GFP_ATOMIC);
	काष्ठा ef100_nic_data *nic_data = efx->nic_data;
	DECLARE_BITMAP(mask, EF100_STAT_COUNT) = अणुपूर्ण;
	u64 *stats = nic_data->stats;

	ef100_common_stat_mask(mask);
	ef100_ethtool_stat_mask(mask);

	efx_nic_copy_stats(efx, mc_stats);
	efx_nic_update_stats(ef100_stat_desc, EF100_STAT_COUNT, mask,
			     stats, mc_stats, false);

	kमुक्त(mc_stats);

	वापस ef100_update_stats_common(efx, full_stats, core_stats);
पूर्ण

अटल पूर्णांक efx_ef100_get_phys_port_id(काष्ठा efx_nic *efx,
				      काष्ठा netdev_phys_item_id *ppid)
अणु
	काष्ठा ef100_nic_data *nic_data = efx->nic_data;

	अगर (!is_valid_ether_addr(nic_data->port_id))
		वापस -EOPNOTSUPP;

	ppid->id_len = ETH_ALEN;
	स_नकल(ppid->id, nic_data->port_id, ppid->id_len);

	वापस 0;
पूर्ण

अटल पूर्णांक efx_ef100_irq_test_generate(काष्ठा efx_nic *efx)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_TRIGGER_INTERRUPT_IN_LEN);

	BUILD_BUG_ON(MC_CMD_TRIGGER_INTERRUPT_OUT_LEN != 0);

	MCDI_SET_DWORD(inbuf, TRIGGER_INTERRUPT_IN_INTR_LEVEL, efx->irq_level);
	वापस efx_mcdi_rpc_quiet(efx, MC_CMD_TRIGGER_INTERRUPT,
				  inbuf, माप(inbuf), शून्य, 0, शून्य);
पूर्ण

#घोषणा EFX_EF100_TEST 1

अटल व्योम efx_ef100_ev_test_generate(काष्ठा efx_channel *channel)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_DRIVER_EVENT_IN_LEN);
	काष्ठा efx_nic *efx = channel->efx;
	efx_qword_t event;
	पूर्णांक rc;

	EFX_POPULATE_QWORD_2(event,
			     ESF_GZ_E_TYPE, ESE_GZ_EF100_EV_DRIVER,
			     ESF_GZ_DRIVER_DATA, EFX_EF100_TEST);

	MCDI_SET_DWORD(inbuf, DRIVER_EVENT_IN_EVQ, channel->channel);

	/* MCDI_SET_QWORD is not appropriate here since EFX_POPULATE_* has
	 * alपढ़ोy swapped the data to little-endian order.
	 */
	स_नकल(MCDI_PTR(inbuf, DRIVER_EVENT_IN_DATA), &event.u64[0],
	       माप(efx_qword_t));

	rc = efx_mcdi_rpc(efx, MC_CMD_DRIVER_EVENT, inbuf, माप(inbuf),
			  शून्य, 0, शून्य);
	अगर (rc && (rc != -ENETDOWN))
		जाओ fail;

	वापस;

fail:
	WARN_ON(true);
	netअगर_err(efx, hw, efx->net_dev, "%s: failed rc=%d\n", __func__, rc);
पूर्ण

अटल अचिन्हित पूर्णांक ef100_check_caps(स्थिर काष्ठा efx_nic *efx,
				     u8 flag, u32 offset)
अणु
	स्थिर काष्ठा ef100_nic_data *nic_data = efx->nic_data;

	चयन (offset) अणु
	हाल MC_CMD_GET_CAPABILITIES_V8_OUT_FLAGS1_OFST:
		वापस nic_data->datapath_caps & BIT_ULL(flag);
	हाल MC_CMD_GET_CAPABILITIES_V8_OUT_FLAGS2_OFST:
		वापस nic_data->datapath_caps2 & BIT_ULL(flag);
	हाल MC_CMD_GET_CAPABILITIES_V8_OUT_FLAGS3_OFST:
		वापस nic_data->datapath_caps3 & BIT_ULL(flag);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/*	NIC level access functions
 */
#घोषणा EF100_OFFLOAD_FEATURES	(NETIF_F_HW_CSUM | NETIF_F_RXCSUM |	\
	NETIF_F_HIGHDMA | NETIF_F_SG | NETIF_F_FRAGLIST | NETIF_F_NTUPLE | \
	NETIF_F_RXHASH | NETIF_F_RXFCS | NETIF_F_TSO_ECN | NETIF_F_RXALL | \
	NETIF_F_HW_VLAN_CTAG_TX)

स्थिर काष्ठा efx_nic_type ef100_pf_nic_type = अणु
	.revision = EFX_REV_EF100,
	.is_vf = false,
	.probe = ef100_probe_pf,
	.offload_features = EF100_OFFLOAD_FEATURES,
	.mcdi_max_ver = 2,
	.mcdi_request = ef100_mcdi_request,
	.mcdi_poll_response = ef100_mcdi_poll_response,
	.mcdi_पढ़ो_response = ef100_mcdi_पढ़ो_response,
	.mcdi_poll_reboot = ef100_mcdi_poll_reboot,
	.mcdi_reboot_detected = ef100_mcdi_reboot_detected,
	.irq_enable_master = efx_port_dummy_op_व्योम,
	.irq_test_generate = efx_ef100_irq_test_generate,
	.irq_disable_non_ev = efx_port_dummy_op_व्योम,
	.push_irq_moderation = efx_channel_dummy_op_व्योम,
	.min_पूर्णांकerrupt_mode = EFX_INT_MODE_MSIX,
	.map_reset_reason = ef100_map_reset_reason,
	.map_reset_flags = ef100_map_reset_flags,
	.reset = ef100_reset,

	.check_caps = ef100_check_caps,

	.ev_probe = ef100_ev_probe,
	.ev_init = ef100_ev_init,
	.ev_fini = efx_mcdi_ev_fini,
	.ev_हटाओ = efx_mcdi_ev_हटाओ,
	.irq_handle_msi = ef100_msi_पूर्णांकerrupt,
	.ev_process = ef100_ev_process,
	.ev_पढ़ो_ack = ef100_ev_पढ़ो_ack,
	.ev_test_generate = efx_ef100_ev_test_generate,
	.tx_probe = ef100_tx_probe,
	.tx_init = ef100_tx_init,
	.tx_ग_लिखो = ef100_tx_ग_लिखो,
	.tx_enqueue = ef100_enqueue_skb,
	.rx_probe = efx_mcdi_rx_probe,
	.rx_init = efx_mcdi_rx_init,
	.rx_हटाओ = efx_mcdi_rx_हटाओ,
	.rx_ग_लिखो = ef100_rx_ग_लिखो,
	.rx_packet = __ef100_rx_packet,
	.rx_buf_hash_valid = ef100_rx_buf_hash_valid,
	.fini_dmaq = efx_fini_dmaq,
	.max_rx_ip_filters = EFX_MCDI_FILTER_TBL_ROWS,
	.filter_table_probe = ef100_filter_table_up,
	.filter_table_restore = efx_mcdi_filter_table_restore,
	.filter_table_हटाओ = ef100_filter_table_करोwn,
	.filter_insert = efx_mcdi_filter_insert,
	.filter_हटाओ_safe = efx_mcdi_filter_हटाओ_safe,
	.filter_get_safe = efx_mcdi_filter_get_safe,
	.filter_clear_rx = efx_mcdi_filter_clear_rx,
	.filter_count_rx_used = efx_mcdi_filter_count_rx_used,
	.filter_get_rx_id_limit = efx_mcdi_filter_get_rx_id_limit,
	.filter_get_rx_ids = efx_mcdi_filter_get_rx_ids,
#अगर_घोषित CONFIG_RFS_ACCEL
	.filter_rfs_expire_one = efx_mcdi_filter_rfs_expire_one,
#पूर्ण_अगर

	.get_phys_port_id = efx_ef100_get_phys_port_id,

	.rx_prefix_size = ESE_GZ_RX_PKT_PREFIX_LEN,
	.rx_hash_offset = ESF_GZ_RX_PREFIX_RSS_HASH_LBN / 8,
	.rx_ts_offset = ESF_GZ_RX_PREFIX_PARTIAL_TSTAMP_LBN / 8,
	.rx_hash_key_size = 40,
	.rx_pull_rss_config = efx_mcdi_rx_pull_rss_config,
	.rx_push_rss_config = efx_mcdi_pf_rx_push_rss_config,
	.rx_push_rss_context_config = efx_mcdi_rx_push_rss_context_config,
	.rx_pull_rss_context_config = efx_mcdi_rx_pull_rss_context_config,
	.rx_restore_rss_contexts = efx_mcdi_rx_restore_rss_contexts,

	.reconfigure_mac = ef100_reconfigure_mac,
	.reconfigure_port = efx_mcdi_port_reconfigure,
	.test_nvram = efx_new_mcdi_nvram_test_all,
	.describe_stats = ef100_describe_stats,
	.start_stats = efx_mcdi_mac_start_stats,
	.update_stats = ef100_update_stats,
	.pull_stats = efx_mcdi_mac_pull_stats,
	.stop_stats = efx_mcdi_mac_stop_stats,

	/* Per-type bar/size configuration not used on ef100. Location of
	 * रेजिस्टरs is defined by extended capabilities.
	 */
	.mem_bar = शून्य,
	.mem_map_size = शून्य,

पूर्ण;

स्थिर काष्ठा efx_nic_type ef100_vf_nic_type = अणु
	.revision = EFX_REV_EF100,
	.is_vf = true,
	.probe = ef100_probe_vf,
	.offload_features = EF100_OFFLOAD_FEATURES,
	.mcdi_max_ver = 2,
	.mcdi_request = ef100_mcdi_request,
	.mcdi_poll_response = ef100_mcdi_poll_response,
	.mcdi_पढ़ो_response = ef100_mcdi_पढ़ो_response,
	.mcdi_poll_reboot = ef100_mcdi_poll_reboot,
	.mcdi_reboot_detected = ef100_mcdi_reboot_detected,
	.irq_enable_master = efx_port_dummy_op_व्योम,
	.irq_test_generate = efx_ef100_irq_test_generate,
	.irq_disable_non_ev = efx_port_dummy_op_व्योम,
	.push_irq_moderation = efx_channel_dummy_op_व्योम,
	.min_पूर्णांकerrupt_mode = EFX_INT_MODE_MSIX,
	.map_reset_reason = ef100_map_reset_reason,
	.map_reset_flags = ef100_map_reset_flags,
	.reset = ef100_reset,
	.check_caps = ef100_check_caps,
	.ev_probe = ef100_ev_probe,
	.ev_init = ef100_ev_init,
	.ev_fini = efx_mcdi_ev_fini,
	.ev_हटाओ = efx_mcdi_ev_हटाओ,
	.irq_handle_msi = ef100_msi_पूर्णांकerrupt,
	.ev_process = ef100_ev_process,
	.ev_पढ़ो_ack = ef100_ev_पढ़ो_ack,
	.ev_test_generate = efx_ef100_ev_test_generate,
	.tx_probe = ef100_tx_probe,
	.tx_init = ef100_tx_init,
	.tx_ग_लिखो = ef100_tx_ग_लिखो,
	.tx_enqueue = ef100_enqueue_skb,
	.rx_probe = efx_mcdi_rx_probe,
	.rx_init = efx_mcdi_rx_init,
	.rx_हटाओ = efx_mcdi_rx_हटाओ,
	.rx_ग_लिखो = ef100_rx_ग_लिखो,
	.rx_packet = __ef100_rx_packet,
	.rx_buf_hash_valid = ef100_rx_buf_hash_valid,
	.fini_dmaq = efx_fini_dmaq,
	.max_rx_ip_filters = EFX_MCDI_FILTER_TBL_ROWS,
	.filter_table_probe = ef100_filter_table_up,
	.filter_table_restore = efx_mcdi_filter_table_restore,
	.filter_table_हटाओ = ef100_filter_table_करोwn,
	.filter_insert = efx_mcdi_filter_insert,
	.filter_हटाओ_safe = efx_mcdi_filter_हटाओ_safe,
	.filter_get_safe = efx_mcdi_filter_get_safe,
	.filter_clear_rx = efx_mcdi_filter_clear_rx,
	.filter_count_rx_used = efx_mcdi_filter_count_rx_used,
	.filter_get_rx_id_limit = efx_mcdi_filter_get_rx_id_limit,
	.filter_get_rx_ids = efx_mcdi_filter_get_rx_ids,
#अगर_घोषित CONFIG_RFS_ACCEL
	.filter_rfs_expire_one = efx_mcdi_filter_rfs_expire_one,
#पूर्ण_अगर

	.rx_prefix_size = ESE_GZ_RX_PKT_PREFIX_LEN,
	.rx_hash_offset = ESF_GZ_RX_PREFIX_RSS_HASH_LBN / 8,
	.rx_ts_offset = ESF_GZ_RX_PREFIX_PARTIAL_TSTAMP_LBN / 8,
	.rx_hash_key_size = 40,
	.rx_pull_rss_config = efx_mcdi_rx_pull_rss_config,
	.rx_push_rss_config = efx_mcdi_pf_rx_push_rss_config,
	.rx_restore_rss_contexts = efx_mcdi_rx_restore_rss_contexts,

	.reconfigure_mac = ef100_reconfigure_mac,
	.test_nvram = efx_new_mcdi_nvram_test_all,
	.describe_stats = ef100_describe_stats,
	.start_stats = efx_mcdi_mac_start_stats,
	.update_stats = ef100_update_stats,
	.pull_stats = efx_mcdi_mac_pull_stats,
	.stop_stats = efx_mcdi_mac_stop_stats,

	.mem_bar = शून्य,
	.mem_map_size = शून्य,

पूर्ण;

अटल पूर्णांक compare_versions(स्थिर अक्षर *a, स्थिर अक्षर *b)
अणु
	पूर्णांक a_major, a_minor, a_poपूर्णांक, a_patch;
	पूर्णांक b_major, b_minor, b_poपूर्णांक, b_patch;
	पूर्णांक a_matched, b_matched;

	a_matched = माला_पूछो(a, "%d.%d.%d.%d", &a_major, &a_minor, &a_poपूर्णांक, &a_patch);
	b_matched = माला_पूछो(b, "%d.%d.%d.%d", &b_major, &b_minor, &b_poपूर्णांक, &b_patch);

	अगर (a_matched == 4 && b_matched != 4)
		वापस +1;

	अगर (a_matched != 4 && b_matched == 4)
		वापस -1;

	अगर (a_matched != 4 && b_matched != 4)
		वापस 0;

	अगर (a_major != b_major)
		वापस a_major - b_major;

	अगर (a_minor != b_minor)
		वापस a_minor - b_minor;

	अगर (a_poपूर्णांक != b_poपूर्णांक)
		वापस a_poपूर्णांक - b_poपूर्णांक;

	वापस a_patch - b_patch;
पूर्ण

क्रमागत ef100_tlv_state_machine अणु
	EF100_TLV_TYPE,
	EF100_TLV_TYPE_CONT,
	EF100_TLV_LENGTH,
	EF100_TLV_VALUE
पूर्ण;

काष्ठा ef100_tlv_state अणु
	क्रमागत ef100_tlv_state_machine state;
	u64 value;
	u32 value_offset;
	u16 type;
	u8 len;
पूर्ण;

अटल पूर्णांक ef100_tlv_feed(काष्ठा ef100_tlv_state *state, u8 byte)
अणु
	चयन (state->state) अणु
	हाल EF100_TLV_TYPE:
		state->type = byte & 0x7f;
		state->state = (byte & 0x80) ? EF100_TLV_TYPE_CONT
					     : EF100_TLV_LENGTH;
		/* Clear पढ़ोy to पढ़ो in a new entry */
		state->value = 0;
		state->value_offset = 0;
		वापस 0;
	हाल EF100_TLV_TYPE_CONT:
		state->type |= byte << 7;
		state->state = EF100_TLV_LENGTH;
		वापस 0;
	हाल EF100_TLV_LENGTH:
		state->len = byte;
		/* We only handle TLVs that fit in a u64 */
		अगर (state->len > माप(state->value))
			वापस -EOPNOTSUPP;
		/* len may be zero, implying a value of zero */
		state->state = state->len ? EF100_TLV_VALUE : EF100_TLV_TYPE;
		वापस 0;
	हाल EF100_TLV_VALUE:
		state->value |= ((u64)byte) << (state->value_offset * 8);
		state->value_offset++;
		अगर (state->value_offset >= state->len)
			state->state = EF100_TLV_TYPE;
		वापस 0;
	शेष: /* state machine error, can't happen */
		WARN_ON_ONCE(1);
		वापस -EIO;
	पूर्ण
पूर्ण

अटल पूर्णांक ef100_process_design_param(काष्ठा efx_nic *efx,
				      स्थिर काष्ठा ef100_tlv_state *पढ़ोer)
अणु
	काष्ठा ef100_nic_data *nic_data = efx->nic_data;

	चयन (पढ़ोer->type) अणु
	हाल ESE_EF100_DP_GZ_PAD: /* padding, skip it */
		वापस 0;
	हाल ESE_EF100_DP_GZ_PARTIAL_TSTAMP_SUB_न_अंकO_BITS:
		/* Driver करोesn't support timestamping yet, so we don't care */
		वापस 0;
	हाल ESE_EF100_DP_GZ_EVQ_UNSOL_CREDIT_SEQ_BITS:
		/* Driver करोesn't support unsolicited-event credits yet, so
		 * we करोn't care
		 */
		वापस 0;
	हाल ESE_EF100_DP_GZ_NMMU_GROUP_SIZE:
		/* Driver करोesn't manage the NMMU (so we don't care) */
		वापस 0;
	हाल ESE_EF100_DP_GZ_RX_L4_CSUM_PROTOCOLS:
		/* Driver uses CHECKSUM_COMPLETE, so we करोn't care about
		 * protocol checksum validation
		 */
		वापस 0;
	हाल ESE_EF100_DP_GZ_TSO_MAX_HDR_LEN:
		nic_data->tso_max_hdr_len = min_t(u64, पढ़ोer->value, 0xffff);
		वापस 0;
	हाल ESE_EF100_DP_GZ_TSO_MAX_HDR_NUM_SEGS:
		/* We always put HDR_NUM_SEGS=1 in our TSO descriptors */
		अगर (!पढ़ोer->value) अणु
			netअगर_err(efx, probe, efx->net_dev,
				  "TSO_MAX_HDR_NUM_SEGS < 1\n");
			वापस -EOPNOTSUPP;
		पूर्ण
		वापस 0;
	हाल ESE_EF100_DP_GZ_RXQ_SIZE_GRANULARITY:
	हाल ESE_EF100_DP_GZ_TXQ_SIZE_GRANULARITY:
		/* Our TXQ and RXQ sizes are always घातer-of-two and thus भागisible by
		 * EFX_MIN_DMAQ_SIZE, so we just need to check that
		 * EFX_MIN_DMAQ_SIZE is भागisible by GRANULARITY.
		 * This is very unlikely to fail.
		 */
		अगर (!पढ़ोer->value || पढ़ोer->value > EFX_MIN_DMAQ_SIZE ||
		    EFX_MIN_DMAQ_SIZE % (u32)पढ़ोer->value) अणु
			netअगर_err(efx, probe, efx->net_dev,
				  "%s size granularity is %llu, can't guarantee safety\n",
				  पढ़ोer->type == ESE_EF100_DP_GZ_RXQ_SIZE_GRANULARITY ? "RXQ" : "TXQ",
				  पढ़ोer->value);
			वापस -EOPNOTSUPP;
		पूर्ण
		वापस 0;
	हाल ESE_EF100_DP_GZ_TSO_MAX_PAYLOAD_LEN:
		nic_data->tso_max_payload_len = min_t(u64, पढ़ोer->value, GSO_MAX_SIZE);
		efx->net_dev->gso_max_size = nic_data->tso_max_payload_len;
		वापस 0;
	हाल ESE_EF100_DP_GZ_TSO_MAX_PAYLOAD_NUM_SEGS:
		nic_data->tso_max_payload_num_segs = min_t(u64, पढ़ोer->value, 0xffff);
		efx->net_dev->gso_max_segs = nic_data->tso_max_payload_num_segs;
		वापस 0;
	हाल ESE_EF100_DP_GZ_TSO_MAX_NUM_FRAMES:
		nic_data->tso_max_frames = min_t(u64, पढ़ोer->value, 0xffff);
		वापस 0;
	हाल ESE_EF100_DP_GZ_COMPAT:
		अगर (पढ़ोer->value) अणु
			netअगर_err(efx, probe, efx->net_dev,
				  "DP_COMPAT has unknown bits %#llx, driver not compatible with this hw\n",
				  पढ़ोer->value);
			वापस -EOPNOTSUPP;
		पूर्ण
		वापस 0;
	हाल ESE_EF100_DP_GZ_MEM2MEM_MAX_LEN:
		/* Driver करोesn't use mem2mem transfers */
		वापस 0;
	हाल ESE_EF100_DP_GZ_EVQ_TIMER_TICK_न_अंकOS:
		/* Driver करोesn't currently use EVQ_TIMER */
		वापस 0;
	हाल ESE_EF100_DP_GZ_NMMU_PAGE_SIZES:
		/* Driver करोesn't manage the NMMU (so we don't care) */
		वापस 0;
	हाल ESE_EF100_DP_GZ_VI_STRIDES:
		/* We never try to set the VI stride, and we करोn't rely on
		 * being able to find VIs past VI 0 until after we've learned
		 * the current stride from MC_CMD_GET_CAPABILITIES.
		 * So the value of this shouldn't matter.
		 */
		अगर (पढ़ोer->value != ESE_EF100_DP_GZ_VI_STRIDES_DEFAULT)
			netअगर_dbg(efx, probe, efx->net_dev,
				  "NIC has other than default VI_STRIDES (mask "
				  "%#llx), early probing might use wrong one\n",
				  पढ़ोer->value);
		वापस 0;
	हाल ESE_EF100_DP_GZ_RX_MAX_RUNT:
		/* Driver करोesn't look at L2_STATUS:LEN_ERR bit, so we don't
		 * care whether it indicates runt or overlength क्रम any given
		 * packet, so we करोn't care about this parameter.
		 */
		वापस 0;
	शेष:
		/* Host पूर्णांकerface says "Drivers should ignore design parameters
		 * that they करो not recognise."
		 */
		netअगर_dbg(efx, probe, efx->net_dev,
			  "Ignoring unrecognised design parameter %u\n",
			  पढ़ोer->type);
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक ef100_check_design_params(काष्ठा efx_nic *efx)
अणु
	काष्ठा ef100_tlv_state पढ़ोer = अणुपूर्ण;
	u32 total_len, offset = 0;
	efx_dword_t reg;
	पूर्णांक rc = 0, i;
	u32 data;

	efx_पढ़ोd(efx, &reg, ER_GZ_PARAMS_TLV_LEN);
	total_len = EFX_DWORD_FIELD(reg, EFX_DWORD_0);
	netअगर_dbg(efx, probe, efx->net_dev, "%u bytes of design parameters\n",
		  total_len);
	जबतक (offset < total_len) अणु
		efx_पढ़ोd(efx, &reg, ER_GZ_PARAMS_TLV + offset);
		data = EFX_DWORD_FIELD(reg, EFX_DWORD_0);
		क्रम (i = 0; i < माप(data); i++) अणु
			rc = ef100_tlv_feed(&पढ़ोer, data);
			/* Got a complete value? */
			अगर (!rc && पढ़ोer.state == EF100_TLV_TYPE)
				rc = ef100_process_design_param(efx, &पढ़ोer);
			अगर (rc)
				जाओ out;
			data >>= 8;
			offset++;
		पूर्ण
	पूर्ण
	/* Check we didn't end halfway through a TLV entry, which could either
	 * mean that the TLV stream is truncated or just that it's corrupted
	 * and our state machine is out of sync.
	 */
	अगर (पढ़ोer.state != EF100_TLV_TYPE) अणु
		अगर (पढ़ोer.state == EF100_TLV_TYPE_CONT)
			netअगर_err(efx, probe, efx->net_dev,
				  "truncated design parameter (incomplete type %u)\n",
				  पढ़ोer.type);
		अन्यथा
			netअगर_err(efx, probe, efx->net_dev,
				  "truncated design parameter %u\n",
				  पढ़ोer.type);
		rc = -EIO;
	पूर्ण
out:
	वापस rc;
पूर्ण

/*	NIC probe and हटाओ
 */
अटल पूर्णांक ef100_probe_मुख्य(काष्ठा efx_nic *efx)
अणु
	अचिन्हित पूर्णांक bar_size = resource_size(&efx->pci_dev->resource[efx->mem_bar]);
	काष्ठा net_device *net_dev = efx->net_dev;
	काष्ठा ef100_nic_data *nic_data;
	अक्षर fw_version[32];
	पूर्णांक i, rc;

	अगर (WARN_ON(bar_size == 0))
		वापस -EIO;

	nic_data = kzalloc(माप(*nic_data), GFP_KERNEL);
	अगर (!nic_data)
		वापस -ENOMEM;
	efx->nic_data = nic_data;
	nic_data->efx = efx;
	net_dev->features |= efx->type->offload_features;
	net_dev->hw_features |= efx->type->offload_features;
	net_dev->hw_enc_features |= efx->type->offload_features;
	net_dev->vlan_features |= NETIF_F_HW_CSUM | NETIF_F_SG |
				  NETIF_F_HIGHDMA | NETIF_F_ALL_TSO;

	/* Populate design-parameter शेषs */
	nic_data->tso_max_hdr_len = ESE_EF100_DP_GZ_TSO_MAX_HDR_LEN_DEFAULT;
	nic_data->tso_max_frames = ESE_EF100_DP_GZ_TSO_MAX_NUM_FRAMES_DEFAULT;
	nic_data->tso_max_payload_num_segs = ESE_EF100_DP_GZ_TSO_MAX_PAYLOAD_NUM_SEGS_DEFAULT;
	nic_data->tso_max_payload_len = ESE_EF100_DP_GZ_TSO_MAX_PAYLOAD_LEN_DEFAULT;
	net_dev->gso_max_segs = ESE_EF100_DP_GZ_TSO_MAX_HDR_NUM_SEGS_DEFAULT;
	/* Read design parameters */
	rc = ef100_check_design_params(efx);
	अगर (rc) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "Unsupported design parameters\n");
		जाओ fail;
	पूर्ण

	/* we assume later that we can copy from this buffer in dwords */
	BUILD_BUG_ON(MCDI_CTL_SDU_LEN_MAX_V2 % 4);

	/* MCDI buffers must be 256 byte aligned. */
	rc = efx_nic_alloc_buffer(efx, &nic_data->mcdi_buf, MCDI_BUF_LEN,
				  GFP_KERNEL);
	अगर (rc)
		जाओ fail;

	/* Get the MC's warm boot count.  In case it's rebooting right
	 * now, be prepared to retry.
	 */
	i = 0;
	क्रम (;;) अणु
		rc = ef100_get_warm_boot_count(efx);
		अगर (rc >= 0)
			अवरोध;
		अगर (++i == 5)
			जाओ fail;
		ssleep(1);
	पूर्ण
	nic_data->warm_boot_count = rc;

	/* In हाल we're recovering from a crash (kexec), we want to
	 * cancel any outstanding request by the previous user of this
	 * function.  We send a special message using the least
	 * signअगरicant bits of the 'high' (करोorbell) रेजिस्टर.
	 */
	_efx_ग_लिखोd(efx, cpu_to_le32(1), efx_reg(efx, ER_GZ_MC_DB_HWRD));

	/* Post-IO section. */

	rc = efx_mcdi_init(efx);
	अगर (!rc && efx->mcdi->fn_flags &
		   (1 << MC_CMD_DRV_ATTACH_EXT_OUT_FLAG_NO_ACTIVE_PORT)) अणु
		netअगर_info(efx, probe, efx->net_dev,
			   "No network port on this PCI function");
		rc = -ENODEV;
	पूर्ण
	अगर (rc)
		जाओ fail;
	/* Reset (most) configuration क्रम this function */
	rc = efx_mcdi_reset(efx, RESET_TYPE_ALL);
	अगर (rc)
		जाओ fail;
	/* Enable event logging */
	rc = efx_mcdi_log_ctrl(efx, true, false, 0);
	अगर (rc)
		जाओ fail;

	rc = efx_get_pf_index(efx, &nic_data->pf_index);
	अगर (rc)
		जाओ fail;

	rc = efx_ef100_init_datapath_caps(efx);
	अगर (rc < 0)
		जाओ fail;

	efx->max_vis = EF100_MAX_VIS;

	rc = efx_mcdi_port_get_number(efx);
	अगर (rc < 0)
		जाओ fail;
	efx->port_num = rc;

	efx_mcdi_prपूर्णांक_fwver(efx, fw_version, माप(fw_version));
	netअगर_dbg(efx, drv, efx->net_dev, "Firmware version %s\n", fw_version);

	अगर (compare_versions(fw_version, "1.1.0.1000") < 0) अणु
		netअगर_info(efx, drv, efx->net_dev, "Firmware uses old event descriptors\n");
		rc = -EINVAL;
		जाओ fail;
	पूर्ण

	अगर (efx_has_cap(efx, UNSOL_EV_CREDIT_SUPPORTED)) अणु
		netअगर_info(efx, drv, efx->net_dev, "Firmware uses unsolicited-event credits\n");
		rc = -EINVAL;
		जाओ fail;
	पूर्ण

	rc = ef100_phy_probe(efx);
	अगर (rc)
		जाओ fail;

	करोwn_ग_लिखो(&efx->filter_sem);
	rc = ef100_filter_table_probe(efx);
	up_ग_लिखो(&efx->filter_sem);
	अगर (rc)
		जाओ fail;

	netdev_rss_key_fill(efx->rss_context.rx_hash_key,
			    माप(efx->rss_context.rx_hash_key));

	/* Don't fail init if RSS setup doesn't work. */
	efx_mcdi_push_शेष_indir_table(efx, efx->n_rx_channels);

	rc = ef100_रेजिस्टर_netdev(efx);
	अगर (rc)
		जाओ fail;

	वापस 0;
fail:
	वापस rc;
पूर्ण

पूर्णांक ef100_probe_pf(काष्ठा efx_nic *efx)
अणु
	काष्ठा net_device *net_dev = efx->net_dev;
	काष्ठा ef100_nic_data *nic_data;
	पूर्णांक rc = ef100_probe_मुख्य(efx);

	अगर (rc)
		जाओ fail;

	nic_data = efx->nic_data;
	rc = ef100_get_mac_address(efx, net_dev->perm_addr);
	अगर (rc)
		जाओ fail;
	/* Assign MAC address */
	स_नकल(net_dev->dev_addr, net_dev->perm_addr, ETH_ALEN);
	स_नकल(nic_data->port_id, net_dev->perm_addr, ETH_ALEN);

	वापस 0;

fail:
	वापस rc;
पूर्ण

पूर्णांक ef100_probe_vf(काष्ठा efx_nic *efx)
अणु
	वापस ef100_probe_मुख्य(efx);
पूर्ण

व्योम ef100_हटाओ(काष्ठा efx_nic *efx)
अणु
	काष्ठा ef100_nic_data *nic_data = efx->nic_data;

	ef100_unरेजिस्टर_netdev(efx);

	करोwn_ग_लिखो(&efx->filter_sem);
	efx_mcdi_filter_table_हटाओ(efx);
	up_ग_लिखो(&efx->filter_sem);
	efx_fini_channels(efx);
	kमुक्त(efx->phy_data);
	efx->phy_data = शून्य;
	efx_mcdi_detach(efx);
	efx_mcdi_fini(efx);
	अगर (nic_data)
		efx_nic_मुक्त_buffer(efx, &nic_data->mcdi_buf);
	kमुक्त(nic_data);
	efx->nic_data = शून्य;
पूर्ण
