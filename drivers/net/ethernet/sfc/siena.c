<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2005-2006 Fen Systems Ltd.
 * Copyright 2006-2013 Solarflare Communications Inc.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/अक्रमom.h>
#समावेश "net_driver.h"
#समावेश "bitfield.h"
#समावेश "efx.h"
#समावेश "efx_common.h"
#समावेश "nic.h"
#समावेश "farch_regs.h"
#समावेश "io.h"
#समावेश "workarounds.h"
#समावेश "mcdi.h"
#समावेश "mcdi_pcol.h"
#समावेश "mcdi_port.h"
#समावेश "mcdi_port_common.h"
#समावेश "selftest.h"
#समावेश "siena_sriov.h"

/* Hardware control क्रम SFC9000 family including SFL9021 (aka Siena). */

अटल व्योम siena_init_wol(काष्ठा efx_nic *efx);


अटल व्योम siena_push_irq_moderation(काष्ठा efx_channel *channel)
अणु
	काष्ठा efx_nic *efx = channel->efx;
	efx_dword_t समयr_cmd;

	अगर (channel->irq_moderation_us) अणु
		अचिन्हित पूर्णांक ticks;

		ticks = efx_usecs_to_ticks(efx, channel->irq_moderation_us);
		EFX_POPULATE_DWORD_2(समयr_cmd,
				     FRF_CZ_TC_TIMER_MODE,
				     FFE_CZ_TIMER_MODE_INT_HLDOFF,
				     FRF_CZ_TC_TIMER_VAL,
				     ticks - 1);
	पूर्ण अन्यथा अणु
		EFX_POPULATE_DWORD_2(समयr_cmd,
				     FRF_CZ_TC_TIMER_MODE,
				     FFE_CZ_TIMER_MODE_DIS,
				     FRF_CZ_TC_TIMER_VAL, 0);
	पूर्ण
	efx_ग_लिखोd_page_locked(channel->efx, &समयr_cmd, FR_BZ_TIMER_COMMAND_P0,
			       channel->channel);
पूर्ण

व्योम siena_prepare_flush(काष्ठा efx_nic *efx)
अणु
	अगर (efx->fc_disable++ == 0)
		efx_mcdi_set_mac(efx);
पूर्ण

व्योम siena_finish_flush(काष्ठा efx_nic *efx)
अणु
	अगर (--efx->fc_disable == 0)
		efx_mcdi_set_mac(efx);
पूर्ण

अटल स्थिर काष्ठा efx_farch_रेजिस्टर_test siena_रेजिस्टर_tests[] = अणु
	अणु FR_AZ_ADR_REGION,
	  EFX_OWORD32(0x0003FFFF, 0x0003FFFF, 0x0003FFFF, 0x0003FFFF) पूर्ण,
	अणु FR_CZ_USR_EV_CFG,
	  EFX_OWORD32(0x000103FF, 0x00000000, 0x00000000, 0x00000000) पूर्ण,
	अणु FR_AZ_RX_CFG,
	  EFX_OWORD32(0xFFFFFFFE, 0xFFFFFFFF, 0x0003FFFF, 0x00000000) पूर्ण,
	अणु FR_AZ_TX_CFG,
	  EFX_OWORD32(0x7FFF0037, 0xFFFF8000, 0xFFFFFFFF, 0x03FFFFFF) पूर्ण,
	अणु FR_AZ_TX_RESERVED,
	  EFX_OWORD32(0xFFFEFE80, 0x1FFFFFFF, 0x020000FE, 0x007FFFFF) पूर्ण,
	अणु FR_AZ_SRM_TX_DC_CFG,
	  EFX_OWORD32(0x001FFFFF, 0x00000000, 0x00000000, 0x00000000) पूर्ण,
	अणु FR_AZ_RX_DC_CFG,
	  EFX_OWORD32(0x00000003, 0x00000000, 0x00000000, 0x00000000) पूर्ण,
	अणु FR_AZ_RX_DC_PF_WM,
	  EFX_OWORD32(0x000003FF, 0x00000000, 0x00000000, 0x00000000) पूर्ण,
	अणु FR_BZ_DP_CTRL,
	  EFX_OWORD32(0x00000FFF, 0x00000000, 0x00000000, 0x00000000) पूर्ण,
	अणु FR_BZ_RX_RSS_TKEY,
	  EFX_OWORD32(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF) पूर्ण,
	अणु FR_CZ_RX_RSS_IPV6_REG1,
	  EFX_OWORD32(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF) पूर्ण,
	अणु FR_CZ_RX_RSS_IPV6_REG2,
	  EFX_OWORD32(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF) पूर्ण,
	अणु FR_CZ_RX_RSS_IPV6_REG3,
	  EFX_OWORD32(0xFFFFFFFF, 0xFFFFFFFF, 0x00000007, 0x00000000) पूर्ण,
पूर्ण;

अटल पूर्णांक siena_test_chip(काष्ठा efx_nic *efx, काष्ठा efx_self_tests *tests)
अणु
	क्रमागत reset_type reset_method = RESET_TYPE_ALL;
	पूर्णांक rc, rc2;

	efx_reset_करोwn(efx, reset_method);

	/* Reset the chip immediately so that it is completely
	 * quiescent regardless of what any VF driver करोes.
	 */
	rc = efx_mcdi_reset(efx, reset_method);
	अगर (rc)
		जाओ out;

	tests->रेजिस्टरs =
		efx_farch_test_रेजिस्टरs(efx, siena_रेजिस्टर_tests,
					 ARRAY_SIZE(siena_रेजिस्टर_tests))
		? -1 : 1;

	rc = efx_mcdi_reset(efx, reset_method);
out:
	rc2 = efx_reset_up(efx, reset_method, rc == 0);
	वापस rc ? rc : rc2;
पूर्ण

/**************************************************************************
 *
 * PTP
 *
 **************************************************************************
 */

अटल व्योम siena_ptp_ग_लिखो_host_समय(काष्ठा efx_nic *efx, u32 host_समय)
अणु
	_efx_ग_लिखोd(efx, cpu_to_le32(host_समय),
		    FR_CZ_MC_TREG_SMEM + MC_SMEM_P0_PTP_TIME_OFST);
पूर्ण

अटल पूर्णांक siena_ptp_set_ts_config(काष्ठा efx_nic *efx,
				   काष्ठा hwtstamp_config *init)
अणु
	पूर्णांक rc;

	चयन (init->rx_filter) अणु
	हाल HWTSTAMP_FILTER_NONE:
		/* अगर TX बारtamping is still requested then leave PTP on */
		वापस efx_ptp_change_mode(efx,
					   init->tx_type != HWTSTAMP_TX_OFF,
					   efx_ptp_get_mode(efx));
	हाल HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
		init->rx_filter = HWTSTAMP_FILTER_PTP_V1_L4_EVENT;
		वापस efx_ptp_change_mode(efx, true, MC_CMD_PTP_MODE_V1);
	हाल HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
		init->rx_filter = HWTSTAMP_FILTER_PTP_V2_L4_EVENT;
		rc = efx_ptp_change_mode(efx, true,
					 MC_CMD_PTP_MODE_V2_ENHANCED);
		/* bug 33070 - old versions of the firmware करो not support the
		 * improved UUID filtering option. Similarly old versions of the
		 * application करो not expect it to be enabled. If the firmware
		 * करोes not accept the enhanced mode, fall back to the standard
		 * PTP v2 UUID filtering. */
		अगर (rc != 0)
			rc = efx_ptp_change_mode(efx, true, MC_CMD_PTP_MODE_V2);
		वापस rc;
	शेष:
		वापस -दुस्फल;
	पूर्ण
पूर्ण

/**************************************************************************
 *
 * Device reset
 *
 **************************************************************************
 */

अटल पूर्णांक siena_map_reset_flags(u32 *flags)
अणु
	क्रमागत अणु
		SIENA_RESET_PORT = (ETH_RESET_DMA | ETH_RESET_FILTER |
				    ETH_RESET_OFFLOAD | ETH_RESET_MAC |
				    ETH_RESET_PHY),
		SIENA_RESET_MC = (SIENA_RESET_PORT |
				  ETH_RESET_MGMT << ETH_RESET_SHARED_SHIFT),
	पूर्ण;

	अगर ((*flags & SIENA_RESET_MC) == SIENA_RESET_MC) अणु
		*flags &= ~SIENA_RESET_MC;
		वापस RESET_TYPE_WORLD;
	पूर्ण

	अगर ((*flags & SIENA_RESET_PORT) == SIENA_RESET_PORT) अणु
		*flags &= ~SIENA_RESET_PORT;
		वापस RESET_TYPE_ALL;
	पूर्ण

	/* no invisible reset implemented */

	वापस -EINVAL;
पूर्ण

#अगर_घोषित CONFIG_EEH
/* When a PCI device is isolated from the bus, a subsequent MMIO पढ़ो is
 * required क्रम the kernel EEH mechanisms to notice. As the Solarflare driver
 * was written to minimise MMIO पढ़ो (क्रम latency) then a periodic call to check
 * the EEH status of the device is required so that device recovery can happen
 * in a समयly fashion.
 */
अटल व्योम siena_monitor(काष्ठा efx_nic *efx)
अणु
	काष्ठा eeh_dev *eehdev = pci_dev_to_eeh_dev(efx->pci_dev);

	eeh_dev_check_failure(eehdev);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक siena_probe_nvconfig(काष्ठा efx_nic *efx)
अणु
	u32 caps = 0;
	पूर्णांक rc;

	rc = efx_mcdi_get_board_cfg(efx, efx->net_dev->perm_addr, शून्य, &caps);

	efx->समयr_quantum_ns =
		(caps & (1 << MC_CMD_CAPABILITIES_TURBO_ACTIVE_LBN)) ?
		3072 : 6144; /* 768 cycles */
	efx->समयr_max_ns = efx->type->समयr_period_max *
			    efx->समयr_quantum_ns;

	वापस rc;
पूर्ण

अटल पूर्णांक siena_dimension_resources(काष्ठा efx_nic *efx)
अणु
	/* Each port has a small block of पूर्णांकernal SRAM dedicated to
	 * the buffer table and descriptor caches.  In theory we can
	 * map both blocks to one port, but we करोn't.
	 */
	efx_farch_dimension_resources(efx, FR_CZ_BUF_FULL_TBL_ROWS / 2);
	वापस 0;
पूर्ण

/* On all Falcon-architecture NICs, PFs use BAR 0 क्रम I/O space and BAR 2(&3)
 * क्रम memory.
 */
अटल अचिन्हित पूर्णांक siena_mem_bar(काष्ठा efx_nic *efx)
अणु
	वापस 2;
पूर्ण

अटल अचिन्हित पूर्णांक siena_mem_map_size(काष्ठा efx_nic *efx)
अणु
	वापस FR_CZ_MC_TREG_SMEM +
		FR_CZ_MC_TREG_SMEM_STEP * FR_CZ_MC_TREG_SMEM_ROWS;
पूर्ण

अटल पूर्णांक siena_probe_nic(काष्ठा efx_nic *efx)
अणु
	काष्ठा siena_nic_data *nic_data;
	efx_oword_t reg;
	पूर्णांक rc;

	/* Allocate storage क्रम hardware specअगरic data */
	nic_data = kzalloc(माप(काष्ठा siena_nic_data), GFP_KERNEL);
	अगर (!nic_data)
		वापस -ENOMEM;
	nic_data->efx = efx;
	efx->nic_data = nic_data;

	अगर (efx_farch_fpga_ver(efx) != 0) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "Siena FPGA not supported\n");
		rc = -ENODEV;
		जाओ fail1;
	पूर्ण

	efx->max_channels = EFX_MAX_CHANNELS;
	efx->max_vis = EFX_MAX_CHANNELS;
	efx->max_tx_channels = EFX_MAX_CHANNELS;
	efx->tx_queues_per_channel = 4;

	efx_पढ़ोo(efx, &reg, FR_AZ_CS_DEBUG);
	efx->port_num = EFX_OWORD_FIELD(reg, FRF_CZ_CS_PORT_NUM) - 1;

	rc = efx_mcdi_init(efx);
	अगर (rc)
		जाओ fail1;

	/* Now we can reset the NIC */
	rc = efx_mcdi_reset(efx, RESET_TYPE_ALL);
	अगर (rc) अणु
		netअगर_err(efx, probe, efx->net_dev, "failed to reset NIC\n");
		जाओ fail3;
	पूर्ण

	siena_init_wol(efx);

	/* Allocate memory क्रम INT_KER */
	rc = efx_nic_alloc_buffer(efx, &efx->irq_status, माप(efx_oword_t),
				  GFP_KERNEL);
	अगर (rc)
		जाओ fail4;
	BUG_ON(efx->irq_status.dma_addr & 0x0f);

	netअगर_dbg(efx, probe, efx->net_dev,
		  "INT_KER at %llx (virt %p phys %llx)\n",
		  (अचिन्हित दीर्घ दीर्घ)efx->irq_status.dma_addr,
		  efx->irq_status.addr,
		  (अचिन्हित दीर्घ दीर्घ)virt_to_phys(efx->irq_status.addr));

	/* Read in the non-अस्थिर configuration */
	rc = siena_probe_nvconfig(efx);
	अगर (rc == -EINVAL) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "NVRAM is invalid therefore using defaults\n");
		efx->phy_type = PHY_TYPE_NONE;
		efx->mdio.prtad = MDIO_PRTAD_NONE;
	पूर्ण अन्यथा अगर (rc) अणु
		जाओ fail5;
	पूर्ण

	rc = efx_mcdi_mon_probe(efx);
	अगर (rc)
		जाओ fail5;

#अगर_घोषित CONFIG_SFC_SRIOV
	efx_siena_sriov_probe(efx);
#पूर्ण_अगर
	efx_ptp_defer_probe_with_channel(efx);

	वापस 0;

fail5:
	efx_nic_मुक्त_buffer(efx, &efx->irq_status);
fail4:
fail3:
	efx_mcdi_detach(efx);
	efx_mcdi_fini(efx);
fail1:
	kमुक्त(efx->nic_data);
	वापस rc;
पूर्ण

अटल पूर्णांक siena_rx_pull_rss_config(काष्ठा efx_nic *efx)
अणु
	efx_oword_t temp;

	/* Read from IPv6 RSS key as that's दीर्घer (the IPv4 key is just the
	 * first 128 bits of the same key, assuming it's been set by
	 * siena_rx_push_rss_config, below)
	 */
	efx_पढ़ोo(efx, &temp, FR_CZ_RX_RSS_IPV6_REG1);
	स_नकल(efx->rss_context.rx_hash_key, &temp, माप(temp));
	efx_पढ़ोo(efx, &temp, FR_CZ_RX_RSS_IPV6_REG2);
	स_नकल(efx->rss_context.rx_hash_key + माप(temp), &temp, माप(temp));
	efx_पढ़ोo(efx, &temp, FR_CZ_RX_RSS_IPV6_REG3);
	स_नकल(efx->rss_context.rx_hash_key + 2 * माप(temp), &temp,
	       FRF_CZ_RX_RSS_IPV6_TKEY_HI_WIDTH / 8);
	efx_farch_rx_pull_indir_table(efx);
	वापस 0;
पूर्ण

अटल पूर्णांक siena_rx_push_rss_config(काष्ठा efx_nic *efx, bool user,
				    स्थिर u32 *rx_indir_table, स्थिर u8 *key)
अणु
	efx_oword_t temp;

	/* Set hash key क्रम IPv4 */
	अगर (key)
		स_नकल(efx->rss_context.rx_hash_key, key, माप(temp));
	स_नकल(&temp, efx->rss_context.rx_hash_key, माप(temp));
	efx_ग_लिखोo(efx, &temp, FR_BZ_RX_RSS_TKEY);

	/* Enable IPv6 RSS */
	BUILD_BUG_ON(माप(efx->rss_context.rx_hash_key) <
		     2 * माप(temp) + FRF_CZ_RX_RSS_IPV6_TKEY_HI_WIDTH / 8 ||
		     FRF_CZ_RX_RSS_IPV6_TKEY_HI_LBN != 0);
	स_नकल(&temp, efx->rss_context.rx_hash_key, माप(temp));
	efx_ग_लिखोo(efx, &temp, FR_CZ_RX_RSS_IPV6_REG1);
	स_नकल(&temp, efx->rss_context.rx_hash_key + माप(temp), माप(temp));
	efx_ग_लिखोo(efx, &temp, FR_CZ_RX_RSS_IPV6_REG2);
	EFX_POPULATE_OWORD_2(temp, FRF_CZ_RX_RSS_IPV6_THASH_ENABLE, 1,
			     FRF_CZ_RX_RSS_IPV6_IP_THASH_ENABLE, 1);
	स_नकल(&temp, efx->rss_context.rx_hash_key + 2 * माप(temp),
	       FRF_CZ_RX_RSS_IPV6_TKEY_HI_WIDTH / 8);
	efx_ग_लिखोo(efx, &temp, FR_CZ_RX_RSS_IPV6_REG3);

	स_नकल(efx->rss_context.rx_indir_table, rx_indir_table,
	       माप(efx->rss_context.rx_indir_table));
	efx_farch_rx_push_indir_table(efx);

	वापस 0;
पूर्ण

/* This call perक्रमms hardware-specअगरic global initialisation, such as
 * defining the descriptor cache sizes and number of RSS channels.
 * It करोes not set up any buffers, descriptor rings or event queues.
 */
अटल पूर्णांक siena_init_nic(काष्ठा efx_nic *efx)
अणु
	efx_oword_t temp;
	पूर्णांक rc;

	/* Recover from a failed निश्चितion post-reset */
	rc = efx_mcdi_handle_निश्चितion(efx);
	अगर (rc)
		वापस rc;

	/* Squash TX of packets of 16 bytes or less */
	efx_पढ़ोo(efx, &temp, FR_AZ_TX_RESERVED);
	EFX_SET_OWORD_FIELD(temp, FRF_BZ_TX_FLUSH_MIN_LEN_EN, 1);
	efx_ग_लिखोo(efx, &temp, FR_AZ_TX_RESERVED);

	/* Do not enable TX_NO_EOP_DISC_EN, since it limits packets to 16
	 * descriptors (which is bad).
	 */
	efx_पढ़ोo(efx, &temp, FR_AZ_TX_CFG);
	EFX_SET_OWORD_FIELD(temp, FRF_AZ_TX_NO_EOP_DISC_EN, 0);
	EFX_SET_OWORD_FIELD(temp, FRF_CZ_TX_FILTER_EN_BIT, 1);
	efx_ग_लिखोo(efx, &temp, FR_AZ_TX_CFG);

	efx_पढ़ोo(efx, &temp, FR_AZ_RX_CFG);
	EFX_SET_OWORD_FIELD(temp, FRF_BZ_RX_DESC_PUSH_EN, 0);
	EFX_SET_OWORD_FIELD(temp, FRF_BZ_RX_INGR_EN, 1);
	/* Enable hash insertion. This is broken क्रम the 'Falcon' hash
	 * अगर IPv6 hashing is also enabled, so also select Toeplitz
	 * TCP/IPv4 and IPv4 hashes. */
	EFX_SET_OWORD_FIELD(temp, FRF_BZ_RX_HASH_INSRT_HDR, 1);
	EFX_SET_OWORD_FIELD(temp, FRF_BZ_RX_HASH_ALG, 1);
	EFX_SET_OWORD_FIELD(temp, FRF_BZ_RX_IP_HASH, 1);
	EFX_SET_OWORD_FIELD(temp, FRF_BZ_RX_USR_BUF_SIZE,
			    EFX_RX_USR_BUF_SIZE >> 5);
	efx_ग_लिखोo(efx, &temp, FR_AZ_RX_CFG);

	siena_rx_push_rss_config(efx, false, efx->rss_context.rx_indir_table, शून्य);
	efx->rss_context.context_id = 0; /* indicates RSS is active */

	/* Enable event logging */
	rc = efx_mcdi_log_ctrl(efx, true, false, 0);
	अगर (rc)
		वापस rc;

	/* Set destination of both TX and RX Flush events */
	EFX_POPULATE_OWORD_1(temp, FRF_BZ_FLS_EVQ_ID, 0);
	efx_ग_लिखोo(efx, &temp, FR_BZ_DP_CTRL);

	EFX_POPULATE_OWORD_1(temp, FRF_CZ_USREV_DIS, 1);
	efx_ग_लिखोo(efx, &temp, FR_CZ_USR_EV_CFG);

	efx_farch_init_common(efx);
	वापस 0;
पूर्ण

अटल व्योम siena_हटाओ_nic(काष्ठा efx_nic *efx)
अणु
	efx_mcdi_mon_हटाओ(efx);

	efx_nic_मुक्त_buffer(efx, &efx->irq_status);

	efx_mcdi_reset(efx, RESET_TYPE_ALL);

	efx_mcdi_detach(efx);
	efx_mcdi_fini(efx);

	/* Tear करोwn the निजी nic state */
	kमुक्त(efx->nic_data);
	efx->nic_data = शून्य;
पूर्ण

#घोषणा SIENA_DMA_STAT(ext_name, mcdi_name)			\
	[SIENA_STAT_ ## ext_name] =				\
	अणु #ext_name, 64, 8 * MC_CMD_MAC_ ## mcdi_name पूर्ण
#घोषणा SIENA_OTHER_STAT(ext_name)				\
	[SIENA_STAT_ ## ext_name] = अणु #ext_name, 0, 0 पूर्ण
#घोषणा GENERIC_SW_STAT(ext_name)				\
	[GENERIC_STAT_ ## ext_name] = अणु #ext_name, 0, 0 पूर्ण

अटल स्थिर काष्ठा efx_hw_stat_desc siena_stat_desc[SIENA_STAT_COUNT] = अणु
	SIENA_DMA_STAT(tx_bytes, TX_BYTES),
	SIENA_OTHER_STAT(tx_good_bytes),
	SIENA_DMA_STAT(tx_bad_bytes, TX_BAD_BYTES),
	SIENA_DMA_STAT(tx_packets, TX_PKTS),
	SIENA_DMA_STAT(tx_bad, TX_BAD_FCS_PKTS),
	SIENA_DMA_STAT(tx_छोड़ो, TX_PAUSE_PKTS),
	SIENA_DMA_STAT(tx_control, TX_CONTROL_PKTS),
	SIENA_DMA_STAT(tx_unicast, TX_UNICAST_PKTS),
	SIENA_DMA_STAT(tx_multicast, TX_MULTICAST_PKTS),
	SIENA_DMA_STAT(tx_broadcast, TX_BROADCAST_PKTS),
	SIENA_DMA_STAT(tx_lt64, TX_LT64_PKTS),
	SIENA_DMA_STAT(tx_64, TX_64_PKTS),
	SIENA_DMA_STAT(tx_65_to_127, TX_65_TO_127_PKTS),
	SIENA_DMA_STAT(tx_128_to_255, TX_128_TO_255_PKTS),
	SIENA_DMA_STAT(tx_256_to_511, TX_256_TO_511_PKTS),
	SIENA_DMA_STAT(tx_512_to_1023, TX_512_TO_1023_PKTS),
	SIENA_DMA_STAT(tx_1024_to_15xx, TX_1024_TO_15XX_PKTS),
	SIENA_DMA_STAT(tx_15xx_to_jumbo, TX_15XX_TO_JUMBO_PKTS),
	SIENA_DMA_STAT(tx_gtjumbo, TX_GTJUMBO_PKTS),
	SIENA_OTHER_STAT(tx_collision),
	SIENA_DMA_STAT(tx_single_collision, TX_SINGLE_COLLISION_PKTS),
	SIENA_DMA_STAT(tx_multiple_collision, TX_MULTIPLE_COLLISION_PKTS),
	SIENA_DMA_STAT(tx_excessive_collision, TX_EXCESSIVE_COLLISION_PKTS),
	SIENA_DMA_STAT(tx_deferred, TX_DEFERRED_PKTS),
	SIENA_DMA_STAT(tx_late_collision, TX_LATE_COLLISION_PKTS),
	SIENA_DMA_STAT(tx_excessive_deferred, TX_EXCESSIVE_DEFERRED_PKTS),
	SIENA_DMA_STAT(tx_non_tcpudp, TX_NON_TCPUDP_PKTS),
	SIENA_DMA_STAT(tx_mac_src_error, TX_MAC_SRC_ERR_PKTS),
	SIENA_DMA_STAT(tx_ip_src_error, TX_IP_SRC_ERR_PKTS),
	SIENA_DMA_STAT(rx_bytes, RX_BYTES),
	SIENA_OTHER_STAT(rx_good_bytes),
	SIENA_DMA_STAT(rx_bad_bytes, RX_BAD_BYTES),
	SIENA_DMA_STAT(rx_packets, RX_PKTS),
	SIENA_DMA_STAT(rx_good, RX_GOOD_PKTS),
	SIENA_DMA_STAT(rx_bad, RX_BAD_FCS_PKTS),
	SIENA_DMA_STAT(rx_छोड़ो, RX_PAUSE_PKTS),
	SIENA_DMA_STAT(rx_control, RX_CONTROL_PKTS),
	SIENA_DMA_STAT(rx_unicast, RX_UNICAST_PKTS),
	SIENA_DMA_STAT(rx_multicast, RX_MULTICAST_PKTS),
	SIENA_DMA_STAT(rx_broadcast, RX_BROADCAST_PKTS),
	SIENA_DMA_STAT(rx_lt64, RX_UNDERSIZE_PKTS),
	SIENA_DMA_STAT(rx_64, RX_64_PKTS),
	SIENA_DMA_STAT(rx_65_to_127, RX_65_TO_127_PKTS),
	SIENA_DMA_STAT(rx_128_to_255, RX_128_TO_255_PKTS),
	SIENA_DMA_STAT(rx_256_to_511, RX_256_TO_511_PKTS),
	SIENA_DMA_STAT(rx_512_to_1023, RX_512_TO_1023_PKTS),
	SIENA_DMA_STAT(rx_1024_to_15xx, RX_1024_TO_15XX_PKTS),
	SIENA_DMA_STAT(rx_15xx_to_jumbo, RX_15XX_TO_JUMBO_PKTS),
	SIENA_DMA_STAT(rx_gtjumbo, RX_GTJUMBO_PKTS),
	SIENA_DMA_STAT(rx_bad_gtjumbo, RX_JABBER_PKTS),
	SIENA_DMA_STAT(rx_overflow, RX_OVERFLOW_PKTS),
	SIENA_DMA_STAT(rx_false_carrier, RX_FALSE_CARRIER_PKTS),
	SIENA_DMA_STAT(rx_symbol_error, RX_SYMBOL_ERROR_PKTS),
	SIENA_DMA_STAT(rx_align_error, RX_ALIGN_ERROR_PKTS),
	SIENA_DMA_STAT(rx_length_error, RX_LENGTH_ERROR_PKTS),
	SIENA_DMA_STAT(rx_पूर्णांकernal_error, RX_INTERNAL_ERROR_PKTS),
	SIENA_DMA_STAT(rx_nodesc_drop_cnt, RX_NODESC_DROPS),
	GENERIC_SW_STAT(rx_nodesc_trunc),
	GENERIC_SW_STAT(rx_noskb_drops),
पूर्ण;
अटल स्थिर अचिन्हित दीर्घ siena_stat_mask[] = अणु
	[0 ... BITS_TO_LONGS(SIENA_STAT_COUNT) - 1] = ~0UL,
पूर्ण;

अटल माप_प्रकार siena_describe_nic_stats(काष्ठा efx_nic *efx, u8 *names)
अणु
	वापस efx_nic_describe_stats(siena_stat_desc, SIENA_STAT_COUNT,
				      siena_stat_mask, names);
पूर्ण

अटल पूर्णांक siena_try_update_nic_stats(काष्ठा efx_nic *efx)
अणु
	काष्ठा siena_nic_data *nic_data = efx->nic_data;
	u64 *stats = nic_data->stats;
	__le64 *dma_stats;
	__le64 generation_start, generation_end;

	dma_stats = efx->stats_buffer.addr;

	generation_end = dma_stats[efx->num_mac_stats - 1];
	अगर (generation_end == EFX_MC_STATS_GENERATION_INVALID)
		वापस 0;
	rmb();
	efx_nic_update_stats(siena_stat_desc, SIENA_STAT_COUNT, siena_stat_mask,
			     stats, efx->stats_buffer.addr, false);
	rmb();
	generation_start = dma_stats[MC_CMD_MAC_GENERATION_START];
	अगर (generation_end != generation_start)
		वापस -EAGAIN;

	/* Update derived statistics */
	efx_nic_fix_nodesc_drop_stat(efx,
				     &stats[SIENA_STAT_rx_nodesc_drop_cnt]);
	efx_update_dअगरf_stat(&stats[SIENA_STAT_tx_good_bytes],
			     stats[SIENA_STAT_tx_bytes] -
			     stats[SIENA_STAT_tx_bad_bytes]);
	stats[SIENA_STAT_tx_collision] =
		stats[SIENA_STAT_tx_single_collision] +
		stats[SIENA_STAT_tx_multiple_collision] +
		stats[SIENA_STAT_tx_excessive_collision] +
		stats[SIENA_STAT_tx_late_collision];
	efx_update_dअगरf_stat(&stats[SIENA_STAT_rx_good_bytes],
			     stats[SIENA_STAT_rx_bytes] -
			     stats[SIENA_STAT_rx_bad_bytes]);
	efx_update_sw_stats(efx, stats);
	वापस 0;
पूर्ण

अटल माप_प्रकार siena_update_nic_stats(काष्ठा efx_nic *efx, u64 *full_stats,
				     काष्ठा rtnl_link_stats64 *core_stats)
अणु
	काष्ठा siena_nic_data *nic_data = efx->nic_data;
	u64 *stats = nic_data->stats;
	पूर्णांक retry;

	/* If we're unlucky enough to पढ़ो statistics wduring the DMA, रुको
	 * up to 10ms क्रम it to finish (typically takes <500us) */
	क्रम (retry = 0; retry < 100; ++retry) अणु
		अगर (siena_try_update_nic_stats(efx) == 0)
			अवरोध;
		udelay(100);
	पूर्ण

	अगर (full_stats)
		स_नकल(full_stats, stats, माप(u64) * SIENA_STAT_COUNT);

	अगर (core_stats) अणु
		core_stats->rx_packets = stats[SIENA_STAT_rx_packets];
		core_stats->tx_packets = stats[SIENA_STAT_tx_packets];
		core_stats->rx_bytes = stats[SIENA_STAT_rx_bytes];
		core_stats->tx_bytes = stats[SIENA_STAT_tx_bytes];
		core_stats->rx_dropped = stats[SIENA_STAT_rx_nodesc_drop_cnt] +
					 stats[GENERIC_STAT_rx_nodesc_trunc] +
					 stats[GENERIC_STAT_rx_noskb_drops];
		core_stats->multicast = stats[SIENA_STAT_rx_multicast];
		core_stats->collisions = stats[SIENA_STAT_tx_collision];
		core_stats->rx_length_errors =
			stats[SIENA_STAT_rx_gtjumbo] +
			stats[SIENA_STAT_rx_length_error];
		core_stats->rx_crc_errors = stats[SIENA_STAT_rx_bad];
		core_stats->rx_frame_errors = stats[SIENA_STAT_rx_align_error];
		core_stats->rx_fअगरo_errors = stats[SIENA_STAT_rx_overflow];
		core_stats->tx_winकरोw_errors =
			stats[SIENA_STAT_tx_late_collision];

		core_stats->rx_errors = (core_stats->rx_length_errors +
					 core_stats->rx_crc_errors +
					 core_stats->rx_frame_errors +
					 stats[SIENA_STAT_rx_symbol_error]);
		core_stats->tx_errors = (core_stats->tx_winकरोw_errors +
					 stats[SIENA_STAT_tx_bad]);
	पूर्ण

	वापस SIENA_STAT_COUNT;
पूर्ण

अटल पूर्णांक siena_mac_reconfigure(काष्ठा efx_nic *efx, bool mtu_only __always_unused)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_SET_MCAST_HASH_IN_LEN);
	पूर्णांक rc;

	BUILD_BUG_ON(MC_CMD_SET_MCAST_HASH_IN_LEN !=
		     MC_CMD_SET_MCAST_HASH_IN_HASH0_OFST +
		     माप(efx->multicast_hash));

	efx_farch_filter_sync_rx_mode(efx);

	WARN_ON(!mutex_is_locked(&efx->mac_lock));

	rc = efx_mcdi_set_mac(efx);
	अगर (rc != 0)
		वापस rc;

	स_नकल(MCDI_PTR(inbuf, SET_MCAST_HASH_IN_HASH0),
	       efx->multicast_hash.byte, माप(efx->multicast_hash));
	वापस efx_mcdi_rpc(efx, MC_CMD_SET_MCAST_HASH,
			    inbuf, माप(inbuf), शून्य, 0, शून्य);
पूर्ण

/**************************************************************************
 *
 * Wake on LAN
 *
 **************************************************************************
 */

अटल व्योम siena_get_wol(काष्ठा efx_nic *efx, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा siena_nic_data *nic_data = efx->nic_data;

	wol->supported = WAKE_MAGIC;
	अगर (nic_data->wol_filter_id != -1)
		wol->wolopts = WAKE_MAGIC;
	अन्यथा
		wol->wolopts = 0;
	स_रखो(&wol->sopass, 0, माप(wol->sopass));
पूर्ण


अटल पूर्णांक siena_set_wol(काष्ठा efx_nic *efx, u32 type)
अणु
	काष्ठा siena_nic_data *nic_data = efx->nic_data;
	पूर्णांक rc;

	अगर (type & ~WAKE_MAGIC)
		वापस -EINVAL;

	अगर (type & WAKE_MAGIC) अणु
		अगर (nic_data->wol_filter_id != -1)
			efx_mcdi_wol_filter_हटाओ(efx,
						   nic_data->wol_filter_id);
		rc = efx_mcdi_wol_filter_set_magic(efx, efx->net_dev->dev_addr,
						   &nic_data->wol_filter_id);
		अगर (rc)
			जाओ fail;

		pci_wake_from_d3(efx->pci_dev, true);
	पूर्ण अन्यथा अणु
		rc = efx_mcdi_wol_filter_reset(efx);
		nic_data->wol_filter_id = -1;
		pci_wake_from_d3(efx->pci_dev, false);
		अगर (rc)
			जाओ fail;
	पूर्ण

	वापस 0;
 fail:
	netअगर_err(efx, hw, efx->net_dev, "%s failed: type=%d rc=%d\n",
		  __func__, type, rc);
	वापस rc;
पूर्ण


अटल व्योम siena_init_wol(काष्ठा efx_nic *efx)
अणु
	काष्ठा siena_nic_data *nic_data = efx->nic_data;
	पूर्णांक rc;

	rc = efx_mcdi_wol_filter_get_magic(efx, &nic_data->wol_filter_id);

	अगर (rc != 0) अणु
		/* If it failed, attempt to get पूर्णांकo a synchronised
		 * state with MC by resetting any set WoL filters */
		efx_mcdi_wol_filter_reset(efx);
		nic_data->wol_filter_id = -1;
	पूर्ण अन्यथा अगर (nic_data->wol_filter_id != -1) अणु
		pci_wake_from_d3(efx->pci_dev, true);
	पूर्ण
पूर्ण

/**************************************************************************
 *
 * MCDI
 *
 **************************************************************************
 */

#घोषणा MCDI_PDU(efx)							\
	(efx_port_num(efx) ? MC_SMEM_P1_PDU_OFST : MC_SMEM_P0_PDU_OFST)
#घोषणा MCDI_DOORBELL(efx)						\
	(efx_port_num(efx) ? MC_SMEM_P1_DOORBELL_OFST : MC_SMEM_P0_DOORBELL_OFST)
#घोषणा MCDI_STATUS(efx)						\
	(efx_port_num(efx) ? MC_SMEM_P1_STATUS_OFST : MC_SMEM_P0_STATUS_OFST)

अटल व्योम siena_mcdi_request(काष्ठा efx_nic *efx,
			       स्थिर efx_dword_t *hdr, माप_प्रकार hdr_len,
			       स्थिर efx_dword_t *sdu, माप_प्रकार sdu_len)
अणु
	अचिन्हित pdu = FR_CZ_MC_TREG_SMEM + MCDI_PDU(efx);
	अचिन्हित करोorbell = FR_CZ_MC_TREG_SMEM + MCDI_DOORBELL(efx);
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक inlen_dw = DIV_ROUND_UP(sdu_len, 4);

	EFX_WARN_ON_PARANOID(hdr_len != 4);

	efx_ग_लिखोd(efx, hdr, pdu);

	क्रम (i = 0; i < inlen_dw; i++)
		efx_ग_लिखोd(efx, &sdu[i], pdu + hdr_len + 4 * i);

	/* Ensure the request is written out beक्रमe the करोorbell */
	wmb();

	/* ring the करोorbell with a distinctive value */
	_efx_ग_लिखोd(efx, (__क्रमce __le32) 0x45789abc, करोorbell);
पूर्ण

अटल bool siena_mcdi_poll_response(काष्ठा efx_nic *efx)
अणु
	अचिन्हित पूर्णांक pdu = FR_CZ_MC_TREG_SMEM + MCDI_PDU(efx);
	efx_dword_t hdr;

	efx_पढ़ोd(efx, &hdr, pdu);

	/* All 1's indicates that shared memory is in reset (and is
	 * not a valid hdr). Wait क्रम it to come out reset beक्रमe
	 * completing the command
	 */
	वापस EFX_DWORD_FIELD(hdr, EFX_DWORD_0) != 0xffffffff &&
		EFX_DWORD_FIELD(hdr, MCDI_HEADER_RESPONSE);
पूर्ण

अटल व्योम siena_mcdi_पढ़ो_response(काष्ठा efx_nic *efx, efx_dword_t *outbuf,
				     माप_प्रकार offset, माप_प्रकार outlen)
अणु
	अचिन्हित पूर्णांक pdu = FR_CZ_MC_TREG_SMEM + MCDI_PDU(efx);
	अचिन्हित पूर्णांक outlen_dw = DIV_ROUND_UP(outlen, 4);
	पूर्णांक i;

	क्रम (i = 0; i < outlen_dw; i++)
		efx_पढ़ोd(efx, &outbuf[i], pdu + offset + 4 * i);
पूर्ण

अटल पूर्णांक siena_mcdi_poll_reboot(काष्ठा efx_nic *efx)
अणु
	काष्ठा siena_nic_data *nic_data = efx->nic_data;
	अचिन्हित पूर्णांक addr = FR_CZ_MC_TREG_SMEM + MCDI_STATUS(efx);
	efx_dword_t reg;
	u32 value;

	efx_पढ़ोd(efx, &reg, addr);
	value = EFX_DWORD_FIELD(reg, EFX_DWORD_0);

	अगर (value == 0)
		वापस 0;

	EFX_ZERO_DWORD(reg);
	efx_ग_लिखोd(efx, &reg, addr);

	/* MAC statistics have been cleared on the NIC; clear the local
	 * copies that we update with efx_update_dअगरf_stat().
	 */
	nic_data->stats[SIENA_STAT_tx_good_bytes] = 0;
	nic_data->stats[SIENA_STAT_rx_good_bytes] = 0;

	अगर (value == MC_STATUS_DWORD_ASSERT)
		वापस -EINTR;
	अन्यथा
		वापस -EIO;
पूर्ण

/**************************************************************************
 *
 * MTD
 *
 **************************************************************************
 */

#अगर_घोषित CONFIG_SFC_MTD

काष्ठा siena_nvram_type_info अणु
	पूर्णांक port;
	स्थिर अक्षर *name;
पूर्ण;

अटल स्थिर काष्ठा siena_nvram_type_info siena_nvram_types[] = अणु
	[MC_CMD_NVRAM_TYPE_DISABLED_CALLISTO]	= अणु 0, "sfc_dummy_phy" पूर्ण,
	[MC_CMD_NVRAM_TYPE_MC_FW]		= अणु 0, "sfc_mcfw" पूर्ण,
	[MC_CMD_NVRAM_TYPE_MC_FW_BACKUP]	= अणु 0, "sfc_mcfw_backup" पूर्ण,
	[MC_CMD_NVRAM_TYPE_STATIC_CFG_PORT0]	= अणु 0, "sfc_static_cfg" पूर्ण,
	[MC_CMD_NVRAM_TYPE_STATIC_CFG_PORT1]	= अणु 1, "sfc_static_cfg" पूर्ण,
	[MC_CMD_NVRAM_TYPE_DYNAMIC_CFG_PORT0]	= अणु 0, "sfc_dynamic_cfg" पूर्ण,
	[MC_CMD_NVRAM_TYPE_DYNAMIC_CFG_PORT1]	= अणु 1, "sfc_dynamic_cfg" पूर्ण,
	[MC_CMD_NVRAM_TYPE_EXP_ROM]		= अणु 0, "sfc_exp_rom" पूर्ण,
	[MC_CMD_NVRAM_TYPE_EXP_ROM_CFG_PORT0]	= अणु 0, "sfc_exp_rom_cfg" पूर्ण,
	[MC_CMD_NVRAM_TYPE_EXP_ROM_CFG_PORT1]	= अणु 1, "sfc_exp_rom_cfg" पूर्ण,
	[MC_CMD_NVRAM_TYPE_PHY_PORT0]		= अणु 0, "sfc_phy_fw" पूर्ण,
	[MC_CMD_NVRAM_TYPE_PHY_PORT1]		= अणु 1, "sfc_phy_fw" पूर्ण,
	[MC_CMD_NVRAM_TYPE_FPGA]		= अणु 0, "sfc_fpga" पूर्ण,
पूर्ण;

अटल पूर्णांक siena_mtd_probe_partition(काष्ठा efx_nic *efx,
				     काष्ठा efx_mcdi_mtd_partition *part,
				     अचिन्हित पूर्णांक type)
अणु
	स्थिर काष्ठा siena_nvram_type_info *info;
	माप_प्रकार size, erase_size;
	bool रक्षित;
	पूर्णांक rc;

	अगर (type >= ARRAY_SIZE(siena_nvram_types) ||
	    siena_nvram_types[type].name == शून्य)
		वापस -ENODEV;

	info = &siena_nvram_types[type];

	अगर (info->port != efx_port_num(efx))
		वापस -ENODEV;

	rc = efx_mcdi_nvram_info(efx, type, &size, &erase_size, &रक्षित);
	अगर (rc)
		वापस rc;
	अगर (रक्षित)
		वापस -ENODEV; /* hide it */

	part->nvram_type = type;
	part->common.dev_type_name = "Siena NVRAM manager";
	part->common.type_name = info->name;

	part->common.mtd.type = MTD_NORFLASH;
	part->common.mtd.flags = MTD_CAP_NORFLASH;
	part->common.mtd.size = size;
	part->common.mtd.erasesize = erase_size;

	वापस 0;
पूर्ण

अटल पूर्णांक siena_mtd_get_fw_subtypes(काष्ठा efx_nic *efx,
				     काष्ठा efx_mcdi_mtd_partition *parts,
				     माप_प्रकार n_parts)
अणु
	uपूर्णांक16_t fw_subtype_list[
		MC_CMD_GET_BOARD_CFG_OUT_FW_SUBTYPE_LIST_MAXNUM];
	माप_प्रकार i;
	पूर्णांक rc;

	rc = efx_mcdi_get_board_cfg(efx, शून्य, fw_subtype_list, शून्य);
	अगर (rc)
		वापस rc;

	क्रम (i = 0; i < n_parts; i++)
		parts[i].fw_subtype = fw_subtype_list[parts[i].nvram_type];

	वापस 0;
पूर्ण

अटल पूर्णांक siena_mtd_probe(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_mcdi_mtd_partition *parts;
	u32 nvram_types;
	अचिन्हित पूर्णांक type;
	माप_प्रकार n_parts;
	पूर्णांक rc;

	ASSERT_RTNL();

	rc = efx_mcdi_nvram_types(efx, &nvram_types);
	अगर (rc)
		वापस rc;

	parts = kसुस्मृति(hweight32(nvram_types), माप(*parts), GFP_KERNEL);
	अगर (!parts)
		वापस -ENOMEM;

	type = 0;
	n_parts = 0;

	जबतक (nvram_types != 0) अणु
		अगर (nvram_types & 1) अणु
			rc = siena_mtd_probe_partition(efx, &parts[n_parts],
						       type);
			अगर (rc == 0)
				n_parts++;
			अन्यथा अगर (rc != -ENODEV)
				जाओ fail;
		पूर्ण
		type++;
		nvram_types >>= 1;
	पूर्ण

	rc = siena_mtd_get_fw_subtypes(efx, parts, n_parts);
	अगर (rc)
		जाओ fail;

	rc = efx_mtd_add(efx, &parts[0].common, n_parts, माप(*parts));
fail:
	अगर (rc)
		kमुक्त(parts);
	वापस rc;
पूर्ण

#पूर्ण_अगर /* CONFIG_SFC_MTD */

अटल अचिन्हित पूर्णांक siena_check_caps(स्थिर काष्ठा efx_nic *efx,
				     u8 flag, u32 offset)
अणु
	/* Siena did not support MC_CMD_GET_CAPABILITIES */
	वापस 0;
पूर्ण

/**************************************************************************
 *
 * Revision-dependent attributes used by efx.c and nic.c
 *
 **************************************************************************
 */

स्थिर काष्ठा efx_nic_type siena_a0_nic_type = अणु
	.is_vf = false,
	.mem_bar = siena_mem_bar,
	.mem_map_size = siena_mem_map_size,
	.probe = siena_probe_nic,
	.हटाओ = siena_हटाओ_nic,
	.init = siena_init_nic,
	.dimension_resources = siena_dimension_resources,
	.fini = efx_port_dummy_op_व्योम,
#अगर_घोषित CONFIG_EEH
	.monitor = siena_monitor,
#अन्यथा
	.monitor = शून्य,
#पूर्ण_अगर
	.map_reset_reason = efx_mcdi_map_reset_reason,
	.map_reset_flags = siena_map_reset_flags,
	.reset = efx_mcdi_reset,
	.probe_port = efx_mcdi_port_probe,
	.हटाओ_port = efx_mcdi_port_हटाओ,
	.fini_dmaq = efx_farch_fini_dmaq,
	.prepare_flush = siena_prepare_flush,
	.finish_flush = siena_finish_flush,
	.prepare_flr = efx_port_dummy_op_व्योम,
	.finish_flr = efx_farch_finish_flr,
	.describe_stats = siena_describe_nic_stats,
	.update_stats = siena_update_nic_stats,
	.start_stats = efx_mcdi_mac_start_stats,
	.pull_stats = efx_mcdi_mac_pull_stats,
	.stop_stats = efx_mcdi_mac_stop_stats,
	.push_irq_moderation = siena_push_irq_moderation,
	.reconfigure_mac = siena_mac_reconfigure,
	.check_mac_fault = efx_mcdi_mac_check_fault,
	.reconfigure_port = efx_mcdi_port_reconfigure,
	.get_wol = siena_get_wol,
	.set_wol = siena_set_wol,
	.resume_wol = siena_init_wol,
	.test_chip = siena_test_chip,
	.test_nvram = efx_mcdi_nvram_test_all,
	.mcdi_request = siena_mcdi_request,
	.mcdi_poll_response = siena_mcdi_poll_response,
	.mcdi_पढ़ो_response = siena_mcdi_पढ़ो_response,
	.mcdi_poll_reboot = siena_mcdi_poll_reboot,
	.irq_enable_master = efx_farch_irq_enable_master,
	.irq_test_generate = efx_farch_irq_test_generate,
	.irq_disable_non_ev = efx_farch_irq_disable_master,
	.irq_handle_msi = efx_farch_msi_पूर्णांकerrupt,
	.irq_handle_legacy = efx_farch_legacy_पूर्णांकerrupt,
	.tx_probe = efx_farch_tx_probe,
	.tx_init = efx_farch_tx_init,
	.tx_हटाओ = efx_farch_tx_हटाओ,
	.tx_ग_लिखो = efx_farch_tx_ग_लिखो,
	.tx_limit_len = efx_farch_tx_limit_len,
	.tx_enqueue = __efx_enqueue_skb,
	.rx_push_rss_config = siena_rx_push_rss_config,
	.rx_pull_rss_config = siena_rx_pull_rss_config,
	.rx_probe = efx_farch_rx_probe,
	.rx_init = efx_farch_rx_init,
	.rx_हटाओ = efx_farch_rx_हटाओ,
	.rx_ग_लिखो = efx_farch_rx_ग_लिखो,
	.rx_defer_refill = efx_farch_rx_defer_refill,
	.rx_packet = __efx_rx_packet,
	.ev_probe = efx_farch_ev_probe,
	.ev_init = efx_farch_ev_init,
	.ev_fini = efx_farch_ev_fini,
	.ev_हटाओ = efx_farch_ev_हटाओ,
	.ev_process = efx_farch_ev_process,
	.ev_पढ़ो_ack = efx_farch_ev_पढ़ो_ack,
	.ev_test_generate = efx_farch_ev_test_generate,
	.filter_table_probe = efx_farch_filter_table_probe,
	.filter_table_restore = efx_farch_filter_table_restore,
	.filter_table_हटाओ = efx_farch_filter_table_हटाओ,
	.filter_update_rx_scatter = efx_farch_filter_update_rx_scatter,
	.filter_insert = efx_farch_filter_insert,
	.filter_हटाओ_safe = efx_farch_filter_हटाओ_safe,
	.filter_get_safe = efx_farch_filter_get_safe,
	.filter_clear_rx = efx_farch_filter_clear_rx,
	.filter_count_rx_used = efx_farch_filter_count_rx_used,
	.filter_get_rx_id_limit = efx_farch_filter_get_rx_id_limit,
	.filter_get_rx_ids = efx_farch_filter_get_rx_ids,
#अगर_घोषित CONFIG_RFS_ACCEL
	.filter_rfs_expire_one = efx_farch_filter_rfs_expire_one,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SFC_MTD
	.mtd_probe = siena_mtd_probe,
	.mtd_नाम = efx_mcdi_mtd_नाम,
	.mtd_पढ़ो = efx_mcdi_mtd_पढ़ो,
	.mtd_erase = efx_mcdi_mtd_erase,
	.mtd_ग_लिखो = efx_mcdi_mtd_ग_लिखो,
	.mtd_sync = efx_mcdi_mtd_sync,
#पूर्ण_अगर
	.ptp_ग_लिखो_host_समय = siena_ptp_ग_लिखो_host_समय,
	.ptp_set_ts_config = siena_ptp_set_ts_config,
#अगर_घोषित CONFIG_SFC_SRIOV
	.sriov_configure = efx_siena_sriov_configure,
	.sriov_init = efx_siena_sriov_init,
	.sriov_fini = efx_siena_sriov_fini,
	.sriov_wanted = efx_siena_sriov_wanted,
	.sriov_reset = efx_siena_sriov_reset,
	.sriov_flr = efx_siena_sriov_flr,
	.sriov_set_vf_mac = efx_siena_sriov_set_vf_mac,
	.sriov_set_vf_vlan = efx_siena_sriov_set_vf_vlan,
	.sriov_set_vf_spoofchk = efx_siena_sriov_set_vf_spoofchk,
	.sriov_get_vf_config = efx_siena_sriov_get_vf_config,
	.vचयनing_probe = efx_port_dummy_op_पूर्णांक,
	.vचयनing_restore = efx_port_dummy_op_पूर्णांक,
	.vचयनing_हटाओ = efx_port_dummy_op_व्योम,
	.set_mac_address = efx_siena_sriov_mac_address_changed,
#पूर्ण_अगर

	.revision = EFX_REV_SIENA_A0,
	.txd_ptr_tbl_base = FR_BZ_TX_DESC_PTR_TBL,
	.rxd_ptr_tbl_base = FR_BZ_RX_DESC_PTR_TBL,
	.buf_tbl_base = FR_BZ_BUF_FULL_TBL,
	.evq_ptr_tbl_base = FR_BZ_EVQ_PTR_TBL,
	.evq_rptr_tbl_base = FR_BZ_EVQ_RPTR,
	.max_dma_mask = DMA_BIT_MASK(FSF_AZ_TX_KER_BUF_ADDR_WIDTH),
	.rx_prefix_size = FS_BZ_RX_PREFIX_SIZE,
	.rx_hash_offset = FS_BZ_RX_PREFIX_HASH_OFST,
	.rx_buffer_padding = 0,
	.can_rx_scatter = true,
	.option_descriptors = false,
	.min_पूर्णांकerrupt_mode = EFX_INT_MODE_LEGACY,
	.समयr_period_max = 1 << FRF_CZ_TC_TIMER_VAL_WIDTH,
	.offload_features = (NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
			     NETIF_F_RXHASH | NETIF_F_NTUPLE),
	.mcdi_max_ver = 1,
	.max_rx_ip_filters = FR_BZ_RX_FILTER_TBL0_ROWS,
	.hwtstamp_filters = (1 << HWTSTAMP_FILTER_NONE |
			     1 << HWTSTAMP_FILTER_PTP_V1_L4_EVENT |
			     1 << HWTSTAMP_FILTER_PTP_V2_L4_EVENT),
	.rx_hash_key_size = 16,
	.check_caps = siena_check_caps,
	.sensor_event = efx_mcdi_sensor_event,
पूर्ण;
