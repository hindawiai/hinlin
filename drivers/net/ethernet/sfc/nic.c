<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2005-2006 Fen Systems Ltd.
 * Copyright 2006-2013 Solarflare Communications Inc.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/cpu_rmap.h>
#समावेश "net_driver.h"
#समावेश "bitfield.h"
#समावेश "efx.h"
#समावेश "nic.h"
#समावेश "ef10_regs.h"
#समावेश "farch_regs.h"
#समावेश "io.h"
#समावेश "workarounds.h"
#समावेश "mcdi_pcol.h"

/**************************************************************************
 *
 * Generic buffer handling
 * These buffers are used क्रम पूर्णांकerrupt status, MAC stats, etc.
 *
 **************************************************************************/

पूर्णांक efx_nic_alloc_buffer(काष्ठा efx_nic *efx, काष्ठा efx_buffer *buffer,
			 अचिन्हित पूर्णांक len, gfp_t gfp_flags)
अणु
	buffer->addr = dma_alloc_coherent(&efx->pci_dev->dev, len,
					  &buffer->dma_addr, gfp_flags);
	अगर (!buffer->addr)
		वापस -ENOMEM;
	buffer->len = len;
	वापस 0;
पूर्ण

व्योम efx_nic_मुक्त_buffer(काष्ठा efx_nic *efx, काष्ठा efx_buffer *buffer)
अणु
	अगर (buffer->addr) अणु
		dma_मुक्त_coherent(&efx->pci_dev->dev, buffer->len,
				  buffer->addr, buffer->dma_addr);
		buffer->addr = शून्य;
	पूर्ण
पूर्ण

/* Check whether an event is present in the eventq at the current
 * पढ़ो poपूर्णांकer.  Only useful क्रम self-test.
 */
bool efx_nic_event_present(काष्ठा efx_channel *channel)
अणु
	वापस efx_event_present(efx_event(channel, channel->eventq_पढ़ो_ptr));
पूर्ण

व्योम efx_nic_event_test_start(काष्ठा efx_channel *channel)
अणु
	channel->event_test_cpu = -1;
	smp_wmb();
	channel->efx->type->ev_test_generate(channel);
पूर्ण

पूर्णांक efx_nic_irq_test_start(काष्ठा efx_nic *efx)
अणु
	efx->last_irq_cpu = -1;
	smp_wmb();
	वापस efx->type->irq_test_generate(efx);
पूर्ण

/* Hook पूर्णांकerrupt handler(s)
 * Try MSI and then legacy पूर्णांकerrupts.
 */
पूर्णांक efx_nic_init_पूर्णांकerrupt(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_channel *channel;
	अचिन्हित पूर्णांक n_irqs;
	पूर्णांक rc;

	अगर (!EFX_INT_MODE_USE_MSI(efx)) अणु
		rc = request_irq(efx->legacy_irq,
				 efx->type->irq_handle_legacy, IRQF_SHARED,
				 efx->name, efx);
		अगर (rc) अणु
			netअगर_err(efx, drv, efx->net_dev,
				  "failed to hook legacy IRQ %d\n",
				  efx->pci_dev->irq);
			जाओ fail1;
		पूर्ण
		efx->irqs_hooked = true;
		वापस 0;
	पूर्ण

#अगर_घोषित CONFIG_RFS_ACCEL
	अगर (efx->पूर्णांकerrupt_mode == EFX_INT_MODE_MSIX) अणु
		efx->net_dev->rx_cpu_rmap =
			alloc_irq_cpu_rmap(efx->n_rx_channels);
		अगर (!efx->net_dev->rx_cpu_rmap) अणु
			rc = -ENOMEM;
			जाओ fail1;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/* Hook MSI or MSI-X पूर्णांकerrupt */
	n_irqs = 0;
	efx_क्रम_each_channel(channel, efx) अणु
		rc = request_irq(channel->irq, efx->type->irq_handle_msi,
				 IRQF_PROBE_SHARED, /* Not shared */
				 efx->msi_context[channel->channel].name,
				 &efx->msi_context[channel->channel]);
		अगर (rc) अणु
			netअगर_err(efx, drv, efx->net_dev,
				  "failed to hook IRQ %d\n", channel->irq);
			जाओ fail2;
		पूर्ण
		++n_irqs;

#अगर_घोषित CONFIG_RFS_ACCEL
		अगर (efx->पूर्णांकerrupt_mode == EFX_INT_MODE_MSIX &&
		    channel->channel < efx->n_rx_channels) अणु
			rc = irq_cpu_rmap_add(efx->net_dev->rx_cpu_rmap,
					      channel->irq);
			अगर (rc)
				जाओ fail2;
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	efx->irqs_hooked = true;
	वापस 0;

 fail2:
#अगर_घोषित CONFIG_RFS_ACCEL
	मुक्त_irq_cpu_rmap(efx->net_dev->rx_cpu_rmap);
	efx->net_dev->rx_cpu_rmap = शून्य;
#पूर्ण_अगर
	efx_क्रम_each_channel(channel, efx) अणु
		अगर (n_irqs-- == 0)
			अवरोध;
		मुक्त_irq(channel->irq, &efx->msi_context[channel->channel]);
	पूर्ण
 fail1:
	वापस rc;
पूर्ण

व्योम efx_nic_fini_पूर्णांकerrupt(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_channel *channel;

#अगर_घोषित CONFIG_RFS_ACCEL
	मुक्त_irq_cpu_rmap(efx->net_dev->rx_cpu_rmap);
	efx->net_dev->rx_cpu_rmap = शून्य;
#पूर्ण_अगर

	अगर (!efx->irqs_hooked)
		वापस;
	अगर (EFX_INT_MODE_USE_MSI(efx)) अणु
		/* Disable MSI/MSI-X पूर्णांकerrupts */
		efx_क्रम_each_channel(channel, efx)
			मुक्त_irq(channel->irq,
				 &efx->msi_context[channel->channel]);
	पूर्ण अन्यथा अणु
		/* Disable legacy पूर्णांकerrupt */
		मुक्त_irq(efx->legacy_irq, efx);
	पूर्ण
	efx->irqs_hooked = false;
पूर्ण

/* Register dump */

#घोषणा REGISTER_REVISION_FA	1
#घोषणा REGISTER_REVISION_FB	2
#घोषणा REGISTER_REVISION_FC	3
#घोषणा REGISTER_REVISION_FZ	3	/* last Falcon arch revision */
#घोषणा REGISTER_REVISION_ED	4
#घोषणा REGISTER_REVISION_EZ	4	/* latest EF10 revision */

काष्ठा efx_nic_reg अणु
	u32 offset:24;
	u32 min_revision:3, max_revision:3;
पूर्ण;

#घोषणा REGISTER(name, arch, min_rev, max_rev) अणु			\
	arch ## R_ ## min_rev ## max_rev ## _ ## name,			\
	REGISTER_REVISION_ ## arch ## min_rev,				\
	REGISTER_REVISION_ ## arch ## max_rev				\
पूर्ण
#घोषणा REGISTER_AA(name) REGISTER(name, F, A, A)
#घोषणा REGISTER_AB(name) REGISTER(name, F, A, B)
#घोषणा REGISTER_AZ(name) REGISTER(name, F, A, Z)
#घोषणा REGISTER_BB(name) REGISTER(name, F, B, B)
#घोषणा REGISTER_BZ(name) REGISTER(name, F, B, Z)
#घोषणा REGISTER_CZ(name) REGISTER(name, F, C, Z)
#घोषणा REGISTER_DZ(name) REGISTER(name, E, D, Z)

अटल स्थिर काष्ठा efx_nic_reg efx_nic_regs[] = अणु
	REGISTER_AZ(ADR_REGION),
	REGISTER_AZ(INT_EN_KER),
	REGISTER_BZ(INT_EN_CHAR),
	REGISTER_AZ(INT_ADR_KER),
	REGISTER_BZ(INT_ADR_CHAR),
	/* INT_ACK_KER is WO */
	/* INT_ISR0 is RC */
	REGISTER_AZ(HW_INIT),
	REGISTER_CZ(USR_EV_CFG),
	REGISTER_AB(EE_SPI_HCMD),
	REGISTER_AB(EE_SPI_HADR),
	REGISTER_AB(EE_SPI_HDATA),
	REGISTER_AB(EE_BASE_PAGE),
	REGISTER_AB(EE_VPD_CFG0),
	/* EE_VPD_SW_CNTL and EE_VPD_SW_DATA are not used */
	/* PMBX_DBG_IADDR and PBMX_DBG_IDATA are indirect */
	/* PCIE_CORE_INसूचीECT is indirect */
	REGISTER_AB(NIC_STAT),
	REGISTER_AB(GPIO_CTL),
	REGISTER_AB(GLB_CTL),
	/* FATAL_INTR_KER and FATAL_INTR_CHAR are partly RC */
	REGISTER_BZ(DP_CTRL),
	REGISTER_AZ(MEM_STAT),
	REGISTER_AZ(CS_DEBUG),
	REGISTER_AZ(ALTERA_BUILD),
	REGISTER_AZ(CSR_SPARE),
	REGISTER_AB(PCIE_SD_CTL0123),
	REGISTER_AB(PCIE_SD_CTL45),
	REGISTER_AB(PCIE_PCS_CTL_STAT),
	/* DEBUG_DATA_OUT is not used */
	/* DRV_EV is WO */
	REGISTER_AZ(EVQ_CTL),
	REGISTER_AZ(EVQ_CNT1),
	REGISTER_AZ(EVQ_CNT2),
	REGISTER_AZ(BUF_TBL_CFG),
	REGISTER_AZ(SRM_RX_DC_CFG),
	REGISTER_AZ(SRM_TX_DC_CFG),
	REGISTER_AZ(SRM_CFG),
	/* BUF_TBL_UPD is WO */
	REGISTER_AZ(SRM_UPD_EVQ),
	REGISTER_AZ(SRAM_PARITY),
	REGISTER_AZ(RX_CFG),
	REGISTER_BZ(RX_FILTER_CTL),
	/* RX_FLUSH_DESCQ is WO */
	REGISTER_AZ(RX_DC_CFG),
	REGISTER_AZ(RX_DC_PF_WM),
	REGISTER_BZ(RX_RSS_TKEY),
	/* RX_NODESC_DROP is RC */
	REGISTER_AA(RX_SELF_RST),
	/* RX_DEBUG, RX_PUSH_DROP are not used */
	REGISTER_CZ(RX_RSS_IPV6_REG1),
	REGISTER_CZ(RX_RSS_IPV6_REG2),
	REGISTER_CZ(RX_RSS_IPV6_REG3),
	/* TX_FLUSH_DESCQ is WO */
	REGISTER_AZ(TX_DC_CFG),
	REGISTER_AA(TX_CHKSM_CFG),
	REGISTER_AZ(TX_CFG),
	/* TX_PUSH_DROP is not used */
	REGISTER_AZ(TX_RESERVED),
	REGISTER_BZ(TX_PACE),
	/* TX_PACE_DROP_QID is RC */
	REGISTER_BB(TX_VLAN),
	REGISTER_BZ(TX_IPFIL_PORTEN),
	REGISTER_AB(MD_TXD),
	REGISTER_AB(MD_RXD),
	REGISTER_AB(MD_CS),
	REGISTER_AB(MD_PHY_ADR),
	REGISTER_AB(MD_ID),
	/* MD_STAT is RC */
	REGISTER_AB(MAC_STAT_DMA),
	REGISTER_AB(MAC_CTRL),
	REGISTER_BB(GEN_MODE),
	REGISTER_AB(MAC_MC_HASH_REG0),
	REGISTER_AB(MAC_MC_HASH_REG1),
	REGISTER_AB(GM_CFG1),
	REGISTER_AB(GM_CFG2),
	/* GM_IPG and GM_HD are not used */
	REGISTER_AB(GM_MAX_FLEN),
	/* GM_TEST is not used */
	REGISTER_AB(GM_ADR1),
	REGISTER_AB(GM_ADR2),
	REGISTER_AB(GMF_CFG0),
	REGISTER_AB(GMF_CFG1),
	REGISTER_AB(GMF_CFG2),
	REGISTER_AB(GMF_CFG3),
	REGISTER_AB(GMF_CFG4),
	REGISTER_AB(GMF_CFG5),
	REGISTER_BB(TX_SRC_MAC_CTL),
	REGISTER_AB(XM_ADR_LO),
	REGISTER_AB(XM_ADR_HI),
	REGISTER_AB(XM_GLB_CFG),
	REGISTER_AB(XM_TX_CFG),
	REGISTER_AB(XM_RX_CFG),
	REGISTER_AB(XM_MGT_INT_MASK),
	REGISTER_AB(XM_FC),
	REGISTER_AB(XM_PAUSE_TIME),
	REGISTER_AB(XM_TX_PARAM),
	REGISTER_AB(XM_RX_PARAM),
	/* XM_MGT_INT_MSK (note no 'A') is RC */
	REGISTER_AB(XX_PWR_RST),
	REGISTER_AB(XX_SD_CTL),
	REGISTER_AB(XX_TXDRV_CTL),
	/* XX_PRBS_CTL, XX_PRBS_CHK and XX_PRBS_ERR are not used */
	/* XX_CORE_STAT is partly RC */
	REGISTER_DZ(BIU_HW_REV_ID),
	REGISTER_DZ(MC_DB_LWRD),
	REGISTER_DZ(MC_DB_HWRD),
पूर्ण;

काष्ठा efx_nic_reg_table अणु
	u32 offset:24;
	u32 min_revision:3, max_revision:3;
	u32 step:6, rows:21;
पूर्ण;

#घोषणा REGISTER_TABLE_DIMENSIONS(_, offset, arch, min_rev, max_rev, step, rows) अणु \
	offset,								\
	REGISTER_REVISION_ ## arch ## min_rev,				\
	REGISTER_REVISION_ ## arch ## max_rev,				\
	step, rows							\
पूर्ण
#घोषणा REGISTER_TABLE(name, arch, min_rev, max_rev)			\
	REGISTER_TABLE_DIMENSIONS(					\
		name, arch ## R_ ## min_rev ## max_rev ## _ ## name,	\
		arch, min_rev, max_rev,					\
		arch ## R_ ## min_rev ## max_rev ## _ ## name ## _STEP,	\
		arch ## R_ ## min_rev ## max_rev ## _ ## name ## _ROWS)
#घोषणा REGISTER_TABLE_AA(name) REGISTER_TABLE(name, F, A, A)
#घोषणा REGISTER_TABLE_AZ(name) REGISTER_TABLE(name, F, A, Z)
#घोषणा REGISTER_TABLE_BB(name) REGISTER_TABLE(name, F, B, B)
#घोषणा REGISTER_TABLE_BZ(name) REGISTER_TABLE(name, F, B, Z)
#घोषणा REGISTER_TABLE_BB_CZ(name)					\
	REGISTER_TABLE_DIMENSIONS(name, FR_BZ_ ## name, F, B, B,	\
				  FR_BZ_ ## name ## _STEP,		\
				  FR_BB_ ## name ## _ROWS),		\
	REGISTER_TABLE_DIMENSIONS(name, FR_BZ_ ## name, F, C, Z,	\
				  FR_BZ_ ## name ## _STEP,		\
				  FR_CZ_ ## name ## _ROWS)
#घोषणा REGISTER_TABLE_CZ(name) REGISTER_TABLE(name, F, C, Z)
#घोषणा REGISTER_TABLE_DZ(name) REGISTER_TABLE(name, E, D, Z)

अटल स्थिर काष्ठा efx_nic_reg_table efx_nic_reg_tables[] = अणु
	/* DRIVER is not used */
	/* EVQ_RPTR, TIMER_COMMAND, USR_EV and अणुRX,TXपूर्ण_DESC_UPD are WO */
	REGISTER_TABLE_BB(TX_IPFIL_TBL),
	REGISTER_TABLE_BB(TX_SRC_MAC_TBL),
	REGISTER_TABLE_AA(RX_DESC_PTR_TBL_KER),
	REGISTER_TABLE_BB_CZ(RX_DESC_PTR_TBL),
	REGISTER_TABLE_AA(TX_DESC_PTR_TBL_KER),
	REGISTER_TABLE_BB_CZ(TX_DESC_PTR_TBL),
	REGISTER_TABLE_AA(EVQ_PTR_TBL_KER),
	REGISTER_TABLE_BB_CZ(EVQ_PTR_TBL),
	/* We can't reasonably पढ़ो all of the buffer table (up to 8MB!).
	 * However this driver will only use a few entries.  Reading
	 * 1K entries allows क्रम some expansion of queue count and
	 * size beक्रमe we need to change the version. */
	REGISTER_TABLE_DIMENSIONS(BUF_FULL_TBL_KER, FR_AA_BUF_FULL_TBL_KER,
				  F, A, A, 8, 1024),
	REGISTER_TABLE_DIMENSIONS(BUF_FULL_TBL, FR_BZ_BUF_FULL_TBL,
				  F, B, Z, 8, 1024),
	REGISTER_TABLE_CZ(RX_MAC_FILTER_TBL0),
	REGISTER_TABLE_BB_CZ(TIMER_TBL),
	REGISTER_TABLE_BB_CZ(TX_PACE_TBL),
	REGISTER_TABLE_BZ(RX_INसूचीECTION_TBL),
	/* TX_FILTER_TBL0 is huge and not used by this driver */
	REGISTER_TABLE_CZ(TX_MAC_FILTER_TBL0),
	REGISTER_TABLE_CZ(MC_TREG_SMEM),
	/* MSIX_PBA_TABLE is not mapped */
	/* SRM_DBG is not mapped (and is redundant with BUF_FLL_TBL) */
	REGISTER_TABLE_BZ(RX_FILTER_TBL0),
	REGISTER_TABLE_DZ(BIU_MC_SFT_STATUS),
पूर्ण;

माप_प्रकार efx_nic_get_regs_len(काष्ठा efx_nic *efx)
अणु
	स्थिर काष्ठा efx_nic_reg *reg;
	स्थिर काष्ठा efx_nic_reg_table *table;
	माप_प्रकार len = 0;

	क्रम (reg = efx_nic_regs;
	     reg < efx_nic_regs + ARRAY_SIZE(efx_nic_regs);
	     reg++)
		अगर (efx->type->revision >= reg->min_revision &&
		    efx->type->revision <= reg->max_revision)
			len += माप(efx_oword_t);

	क्रम (table = efx_nic_reg_tables;
	     table < efx_nic_reg_tables + ARRAY_SIZE(efx_nic_reg_tables);
	     table++)
		अगर (efx->type->revision >= table->min_revision &&
		    efx->type->revision <= table->max_revision)
			len += table->rows * min_t(माप_प्रकार, table->step, 16);

	वापस len;
पूर्ण

व्योम efx_nic_get_regs(काष्ठा efx_nic *efx, व्योम *buf)
अणु
	स्थिर काष्ठा efx_nic_reg *reg;
	स्थिर काष्ठा efx_nic_reg_table *table;

	क्रम (reg = efx_nic_regs;
	     reg < efx_nic_regs + ARRAY_SIZE(efx_nic_regs);
	     reg++) अणु
		अगर (efx->type->revision >= reg->min_revision &&
		    efx->type->revision <= reg->max_revision) अणु
			efx_पढ़ोo(efx, (efx_oword_t *)buf, reg->offset);
			buf += माप(efx_oword_t);
		पूर्ण
	पूर्ण

	क्रम (table = efx_nic_reg_tables;
	     table < efx_nic_reg_tables + ARRAY_SIZE(efx_nic_reg_tables);
	     table++) अणु
		माप_प्रकार size, i;

		अगर (!(efx->type->revision >= table->min_revision &&
		      efx->type->revision <= table->max_revision))
			जारी;

		size = min_t(माप_प्रकार, table->step, 16);

		क्रम (i = 0; i < table->rows; i++) अणु
			चयन (table->step) अणु
			हाल 4: /* 32-bit SRAM */
				efx_पढ़ोd(efx, buf, table->offset + 4 * i);
				अवरोध;
			हाल 8: /* 64-bit SRAM */
				efx_sram_पढ़ोq(efx,
					       efx->membase + table->offset,
					       buf, i);
				अवरोध;
			हाल 16: /* 128-bit-पढ़ोable रेजिस्टर */
				efx_पढ़ोo_table(efx, buf, table->offset, i);
				अवरोध;
			हाल 32: /* 128-bit रेजिस्टर, पूर्णांकerleaved */
				efx_पढ़ोo_table(efx, buf, table->offset, 2 * i);
				अवरोध;
			शेष:
				WARN_ON(1);
				वापस;
			पूर्ण
			buf += size;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * efx_nic_describe_stats - Describe supported statistics क्रम ethtool
 * @desc: Array of &काष्ठा efx_hw_stat_desc describing the statistics
 * @count: Length of the @desc array
 * @mask: Biपंचांगask of which elements of @desc are enabled
 * @names: Buffer to copy names to, or %शून्य.  The names are copied
 *	starting at पूर्णांकervals of %ETH_GSTRING_LEN bytes.
 *
 * Returns the number of visible statistics, i.e. the number of set
 * bits in the first @count bits of @mask क्रम which a name is defined.
 */
माप_प्रकार efx_nic_describe_stats(स्थिर काष्ठा efx_hw_stat_desc *desc, माप_प्रकार count,
			      स्थिर अचिन्हित दीर्घ *mask, u8 *names)
अणु
	माप_प्रकार visible = 0;
	माप_प्रकार index;

	क्रम_each_set_bit(index, mask, count) अणु
		अगर (desc[index].name) अणु
			अगर (names) अणु
				strlcpy(names, desc[index].name,
					ETH_GSTRING_LEN);
				names += ETH_GSTRING_LEN;
			पूर्ण
			++visible;
		पूर्ण
	पूर्ण

	वापस visible;
पूर्ण

/**
 * efx_nic_copy_stats - Copy stats from the DMA buffer in to an
 *	पूर्णांकermediate buffer. This is used to get a consistent
 *	set of stats जबतक the DMA buffer can be written at any समय
 *	by the NIC.
 * @efx: The associated NIC.
 * @dest: Destination buffer. Must be the same size as the DMA buffer.
 */
पूर्णांक efx_nic_copy_stats(काष्ठा efx_nic *efx, __le64 *dest)
अणु
	__le64 *dma_stats = efx->stats_buffer.addr;
	__le64 generation_start, generation_end;
	पूर्णांक rc = 0, retry;

	अगर (!dest)
		वापस 0;

	अगर (!dma_stats)
		जाओ वापस_zeroes;

	/* If we're unlucky enough to पढ़ो statistics during the DMA, रुको
	 * up to 10ms क्रम it to finish (typically takes <500us)
	 */
	क्रम (retry = 0; retry < 100; ++retry) अणु
		generation_end = dma_stats[efx->num_mac_stats - 1];
		अगर (generation_end == EFX_MC_STATS_GENERATION_INVALID)
			जाओ वापस_zeroes;
		rmb();
		स_नकल(dest, dma_stats, efx->num_mac_stats * माप(__le64));
		rmb();
		generation_start = dma_stats[MC_CMD_MAC_GENERATION_START];
		अगर (generation_end == generation_start)
			वापस 0; /* वापस good data */
		udelay(100);
	पूर्ण

	rc = -EIO;

वापस_zeroes:
	स_रखो(dest, 0, efx->num_mac_stats * माप(u64));
	वापस rc;
पूर्ण

/**
 * efx_nic_update_stats - Convert statistics DMA buffer to array of u64
 * @desc: Array of &काष्ठा efx_hw_stat_desc describing the DMA buffer
 *	layout.  DMA widths of 0, 16, 32 and 64 are supported; where
 *	the width is specअगरied as 0 the corresponding element of
 *	@stats is not updated.
 * @count: Length of the @desc array
 * @mask: Biपंचांगask of which elements of @desc are enabled
 * @stats: Buffer to update with the converted statistics.  The length
 *	of this array must be at least @count.
 * @dma_buf: DMA buffer containing hardware statistics
 * @accumulate: If set, the converted values will be added rather than
 *	directly stored to the corresponding elements of @stats
 */
व्योम efx_nic_update_stats(स्थिर काष्ठा efx_hw_stat_desc *desc, माप_प्रकार count,
			  स्थिर अचिन्हित दीर्घ *mask,
			  u64 *stats, स्थिर व्योम *dma_buf, bool accumulate)
अणु
	माप_प्रकार index;

	क्रम_each_set_bit(index, mask, count) अणु
		अगर (desc[index].dma_width) अणु
			स्थिर व्योम *addr = dma_buf + desc[index].offset;
			u64 val;

			चयन (desc[index].dma_width) अणु
			हाल 16:
				val = le16_to_cpup((__le16 *)addr);
				अवरोध;
			हाल 32:
				val = le32_to_cpup((__le32 *)addr);
				अवरोध;
			हाल 64:
				val = le64_to_cpup((__le64 *)addr);
				अवरोध;
			शेष:
				WARN_ON(1);
				val = 0;
				अवरोध;
			पूर्ण

			अगर (accumulate)
				stats[index] += val;
			अन्यथा
				stats[index] = val;
		पूर्ण
	पूर्ण
पूर्ण

व्योम efx_nic_fix_nodesc_drop_stat(काष्ठा efx_nic *efx, u64 *rx_nodesc_drops)
अणु
	/* अगर करोwn, or this is the first update after coming up */
	अगर (!(efx->net_dev->flags & IFF_UP) || !efx->rx_nodesc_drops_prev_state)
		efx->rx_nodesc_drops_जबतक_करोwn +=
			*rx_nodesc_drops - efx->rx_nodesc_drops_total;
	efx->rx_nodesc_drops_total = *rx_nodesc_drops;
	efx->rx_nodesc_drops_prev_state = !!(efx->net_dev->flags & IFF_UP);
	*rx_nodesc_drops -= efx->rx_nodesc_drops_जबतक_करोwn;
पूर्ण
